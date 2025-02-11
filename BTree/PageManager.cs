public class RecordId
{
    public int pageId;
    public int slotId;

    public RecordId(int pageId, int slotId)
    {
        this.pageId = pageId;
        this.slotId = slotId;
    }
}

public class RecordStreamWriter
{
    public byte[] buffer;
    public int currentPos;
    public int size;

    public RecordStreamWriter(byte[] buffer, int currentPos, int size)
    {
        this.buffer = buffer;
        this.currentPos = currentPos;
        this.size = size;
    }

    public void WriteInt(int v)
    {
        byte[] bytes = BitConverter.GetBytes(v);
        Buffer.BlockCopy(bytes, 0, buffer, currentPos, bytes.Length);
        currentPos += bytes.Length;
    }
}

public class RecordStreamReader
{
    public byte[] buffer;
    public int currentPos;
    public int size;

    public RecordStreamReader(byte[] buffer, int currentPos, int size)
    {
        this.buffer = buffer;
        this.currentPos = currentPos;
        this.size = size;
    }

    public int ReadInt()
    {
        byte[] bytes = new byte[4];
        Buffer.BlockCopy(buffer, currentPos, bytes, 0, bytes.Length);
        currentPos += bytes.Length;

        return BitConverter.ToInt32(bytes, 0);
    }
}

public class PageType
{
    public int type = -1;
    public int recordSize = -1;

    public PageType(int type, int recordSize)
    {
        this.type = type;
        this.recordSize = recordSize;
    }
}

public class Page
{
    public int type = -1;
    public int index = -1;
    public int pageSize = -1;
    public int recordCount = -1;
    public int recordSize = -1;
    public int freeSlotCount = -1;
    public static int headerSize = 24;

    public bool[] slotFreeArray = null;
    public byte[] buffer = null;
    public bool dirty = false;

    /*
     header:
     int type
     int id
     int pageSize
     int recordCount
     int recordSize
     int freeSlotCount

     record * recordCount
     ...
     
     tail:
     (bool isSlotFree) x recordCount
     */

    public Page(byte[] buffer)
    {
        this.buffer = buffer;
    }

    public Page(int pageType, int id, int pageSize, int recordSize)
    {
        type = pageType;
        this.index = id;
        this.pageSize = pageSize;
        buffer = new byte[pageSize];
        dirty = true;

        this.recordSize = recordSize;

        recordCount = (pageSize - headerSize) / (recordSize + 1); // 1 is (bool isSlotFree)
        freeSlotCount = recordCount;

        slotFreeArray = new bool[recordCount];
        for (int i = 0; i < recordCount; i++)
            slotFreeArray[i] = true;
    }

    public int AllocateSlot()
    {
        for (int i = 0; i < slotFreeArray.Length; i++)
        {
            if (slotFreeArray[i])
            {
                slotFreeArray[i] = false;
                freeSlotCount--;
                return i;
            }
        }

        throw new Exception();
    }

    public void FreeSlot(int slotId)
    {
        if (slotFreeArray[slotId] == true)
            throw new Exception();
        slotFreeArray[slotId] = true;
        freeSlotCount++;
    }

    public RecordStreamWriter GetRecordStreamWriter(int slotId)
    {
        return new RecordStreamWriter(buffer, headerSize + slotId * recordSize, recordSize);
    }

    public RecordStreamReader GetRecordStreamReader(int slotId)
    {
        return new RecordStreamReader(buffer, headerSize + slotId * recordSize, recordSize);
    }

    private int WriteInt(int pos, int v)
    {
        byte[] bytes = BitConverter.GetBytes(v);
        Buffer.BlockCopy(bytes, 0, buffer, pos, bytes.Length);
        return bytes.Length;
    }

    private int ReadInt(int pos, ref int v)
    {
        byte[] bytes = new byte[4];
        Buffer.BlockCopy(buffer, pos, bytes, 0, bytes.Length);
        v = BitConverter.ToInt32(bytes, 0);

        return bytes.Length;
    }

    private int WriteBool(int pos, bool v)
    {
        if (v)
            buffer[pos] = 1;
        else
            buffer[pos] = 0;

        return 1;
    }

    private int ReadBool(int pos, ref bool v)
    {
        if (buffer[pos] == 1)
            v = true;
        else
            v = false;

        return 1;
    }

    public void WriteToBuffer()
    {
        if (!dirty)
            return;
        dirty = false;

        int pos = 0;
        pos += WriteInt(pos, type);
        pos += WriteInt(pos, index);
        pos += WriteInt(pos, pageSize);
        pos += WriteInt(pos, recordCount);
        pos += WriteInt(pos, recordSize);
        pos += WriteInt(pos, freeSlotCount);

        for (int i = 0; i < slotFreeArray.Length; i++)
            WriteBool(buffer.Length - 1 - i, slotFreeArray[i]);
    }

    public static Page ReadFromBuffer(byte[] buffer)
    {
        Page p = new Page(buffer);

        int pos = 0;
        pos += p.ReadInt(pos, ref p.type);
        pos += p.ReadInt(pos, ref p.index);
        pos += p.ReadInt(pos, ref p.pageSize);
        pos += p.ReadInt(pos, ref p.recordCount);
        pos += p.ReadInt(pos, ref p.recordSize);
        pos += p.ReadInt(pos, ref p.freeSlotCount);

        p.slotFreeArray = new bool[p.recordCount];
        for (int i = 0; i < p.slotFreeArray.Length; i++)
            p.ReadBool(buffer.Length - 1 - i, ref p.slotFreeArray[i]);

        return p;
    }
}

// a.k.a. BufferPool
public class PageManager
{
    private FileStream fs;

    private int pageSize = -1;
    private int pageCount = 0;
    private Dictionary<int, Page> pages = new Dictionary<int, Page>();
    private Dictionary<int, PageType> pageTypes = new Dictionary<int, PageType>();
    private int headerSize = -1;

    /*

     header:
     int headerSize
     int pageCount
     int pageSize
     int pageTypeCount
     (
     int type;
     int recordSize; 
     ) * pageTypeCount

     page * pageCount

     */

    public static PageManager Create(string filePath, int pageSize, List<PageType> pageTypes)
    {
        PageManager pm = new PageManager();
        pm.fs = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.ReadWrite);
        pm.pageSize = pageSize;

        pm.pageTypes.Add(-1, new PageType(-1, pageSize / 2));

        foreach (PageType p in pageTypes)
        {
            if (p.type < 0)
                throw new Exception("type < 0 are reserved");
            pm.pageTypes.Add(p.type, p);
        }

        pm.headerSize = 16 + 8 * pm.pageTypes.Count;

        return pm;
    }

    public void FlushPage(long beginPos, BinaryWriter bw, Page p)
    {
        p.WriteToBuffer();
        bw.Seek((int)beginPos + p.index * pageSize, SeekOrigin.Begin);
        bw.Write(p.buffer, 0, p.pageSize);
        p.dirty = false;
    }

    public void Close()
    {
        using (BinaryWriter bw = new BinaryWriter(fs, System.Text.Encoding.UTF8, leaveOpen: true))
        {
            bw.Seek(0, SeekOrigin.Begin);

            bw.Write(headerSize);
            bw.Write(pages.Count);
            bw.Write(pageSize);
            bw.Write(pageTypes.Count);
            foreach (PageType type in pageTypes.Values)
            {
                bw.Write(type.type);
                bw.Write(type.recordSize);
            }

            long beginPos = bw.BaseStream.Position;

            for (int i = 0; i < pages.Count; i++)
            {
                Page page = pages[i];
                if (page.dirty == false)
                    continue;

                FlushPage(beginPos, bw, page);
            }
        }

        fs.Close();
    }

    public static PageManager Load(string filePath)
    {
        PageManager pm = new PageManager();
        pm.fs = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.ReadWrite);

        using (BinaryReader r = new BinaryReader(pm.fs, System.Text.Encoding.UTF8, leaveOpen: true))
        {
            pm.headerSize = r.ReadInt32();
            pm.pageCount = r.ReadInt32();
            pm.pageSize = r.ReadInt32();

            int pageTypeCount = r.ReadInt32();
            Dictionary<int, PageType> pageTypes = new Dictionary<int, PageType>();
            for (int i = 0; i < pageTypeCount; i++)
            {
                int type = r.ReadInt32();
                int size = r.ReadInt32();
                pageTypes.Add(type, new PageType(type, size));
            }
        }

        return pm;
    }

    public RecordId AllocateRecord(int type)
    {
        foreach (Page p in pages.Values)
        {
            if (p.type == type && p.freeSlotCount > 0)
            {
                p.dirty = true;
                return new RecordId(p.index, p.AllocateSlot());
            }
        }

        Page p2 = NewPage(type);
        return new RecordId(p2.index, p2.AllocateSlot());
    }

    public void DeleteRecord(RecordId id)
    {
        Page p = pages[id.pageId];
        p.FreeSlot(id.slotId);
    }

    public RecordStreamWriter GetRecordStreamWriter(RecordId rid)
    {
        return GetPage(rid.pageId).GetRecordStreamWriter(rid.slotId);
    }

    public RecordStreamReader GetRecordStreamReader(RecordId rid)
    {
        return GetPage(rid.pageId).GetRecordStreamReader(rid.slotId);
    }

    private Page GetPage(int pageId)
    {
        if (pages.ContainsKey(pageId))
            return pages[pageId];

        return ReadPageFromFile(pageId);
    }

    private Page ReadPageFromFile(int pageId)
    {
        using (BinaryReader br = new BinaryReader(fs, System.Text.Encoding.UTF8, leaveOpen: true))
        {
            fs.Seek(headerSize + pageId * pageSize, SeekOrigin.Begin);
            byte[] buffer = br.ReadBytes(pageSize);
            return Page.ReadFromBuffer(buffer);
        }
    }

    private Page NewPage(int pageType)
    {
        PageType type = pageTypes[pageType];

        Page page = new Page(pageType, pageCount, pageSize, type.recordSize);
        pages.Add(page.index, page);
        byte[] zeros = new byte[pageSize];
        fs.Seek(0, SeekOrigin.End);
        fs.Write(zeros, 0, zeros.Length);

        pageCount++;

        return page;
    }
}