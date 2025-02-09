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

public class RecordBufferWriter
{
    public byte[] buffer;
    public int currentPos;
    public int size;

    public RecordBufferWriter(byte[] buffer, int currentPos, int size)
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
    public int id = -1;
    public int pageSize = -1;
    public int recordCount = -1;
    public int recordSize = -1;
    public int freeSlotCount = -1;
    public bool[] slotFreeArray = null;
    public byte[] buffer = null;
    public bool dirty = false;

    /*
     header:
     int type
     int id
     int recordCount
     int freeSlotCount

     record * recordCount
     ...
     
     tail:
     (bool isSlotFree) x recordCount
     */

    public Page(int pageType, int id, int pageSize, int recordSize)
    {
        type = pageType;
        this.id = id;
        this.pageSize = pageSize;
        buffer = new byte[pageSize];
        dirty = true;

        this.recordSize = recordSize;

        recordCount = (pageSize - 12) / (recordSize + 1); // 1 is (bool isSlotFree)
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

    public RecordBufferWriter GetWriter(int slotId)
    {
        int headerSize = 16;
        return new RecordBufferWriter(buffer, headerSize + slotId * recordSize, recordSize);
    }

    private int WriteInt(int pos, int v)
    {
        byte[] bytes = BitConverter.GetBytes(id);
        Buffer.BlockCopy(bytes, 0, buffer, pos, bytes.Length);
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

    public void Save(BinaryWriter w)
    {
        if (!dirty)
            return;
        dirty = false;

        int pos = 0;
        pos = WriteInt(pos, type);
        pos = WriteInt(pos, id);
        pos = WriteInt(pos, recordCount);
        pos = WriteInt(pos, freeSlotCount);

        for (int i = 0; i < slotFreeArray.Length; i++)
            WriteBool(buffer.Length - 1 - i, slotFreeArray[i]);

        w.Write(buffer, 0, buffer.Length);
    }
}

// a.k.a. BufferPool
public class PageManager
{
    private FileStream fs;
    private int streamStartPos;

    private int pageSize = -1;
    private int pageCount = -1;
    private List<Page> pages = new List<Page>();
    private Dictionary<int, PageType> pageTypes = new Dictionary<int, PageType>();

    /*

     header:
     int pageCount
     int pageSize
     int pageTypeCount
     (
     int type;
     int recordSize; 
     ) * pageTypeCount

     page * pageCount

     */

    public static PageManager Create(FileStream fs, int streamStartPos, int pageSize, List<PageType> pageTypes)
    {
        PageManager pm = new PageManager();
        pm.fs = fs;
        pm.streamStartPos = streamStartPos;
        pm.pageSize = pageSize;

        foreach (PageType p in pageTypes)
            pm.pageTypes.Add(p.type, p);

        return pm;
    }

    public static PageManager Load(FileStream fs, int streamStartPos)
    {
        PageManager pm = new PageManager();
        pm.fs = fs;
        pm.streamStartPos = streamStartPos;

        using (BinaryReader r = new BinaryReader(fs, System.Text.Encoding.UTF8, leaveOpen: true))
        {
            r.BaseStream.Position = streamStartPos;
            pm.pageCount = r.ReadInt32();
            pm.pageSize = r.ReadInt32();

            int pageTypeCount = r.ReadInt32();
            for (int i = 0; i < pageTypeCount; i++)
                pm.pages.Add(null);

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

    public void Close()
    {
        fs.Close();
    }

    public RecordId AllocateRecord(int type)
    {
        foreach (Page p in pages)
        {
            if (p.type == type && p.freeSlotCount > 0)
            {
                p.dirty = true;
                return new RecordId(p.id, p.AllocateSlot());
            }
        }

        Page p2 = NewPage(type);
        return new RecordId(p2.id, p2.AllocateSlot());
    }

    public void DeleteRecord(RecordId id)
    {
        Page p = pages[id.pageId];
        p.FreeSlot(id.slotId);
    }

    public RecordBufferWriter GetRecordBufferWriter(RecordId id)
    {
        Page p = pages[id.pageId];

        if (p == null)
        {
            TODO here
        }

        return p.GetWriter(id.slotId);
    }

    private Page NewPage(int pageType)
    {
        PageType type = pageTypes[pageType];

        Page page = new Page(pageType, pages.Count, pageSize, type.recordSize);
        pages.Add(page);
        pageCount++;

        return page;
    }

    public void Flush()
    {
        using (BinaryWriter w = new BinaryWriter(fs, System.Text.Encoding.UTF8, leaveOpen: true))
        {
            fs.Seek(streamStartPos, SeekOrigin.Begin);

            w.Write(pages.Count);
            w.Write(pageSize);
            w.Write(pageTypes.Count);
            foreach (PageType type in pageTypes.Values)
            {
                w.Write(type.type);
                w.Write(type.recordSize);
            }

            long beingPos = w.BaseStream.Position;

            for (int i = 0; i < pages.Count; i++)
            {
                Page page = pages[i];
                if (page.dirty == false)
                    continue;
                fs.Seek(beingPos + i * pageSize, SeekOrigin.Begin);
                page.Save(w);
            }
        }
    }

    public static void Test()
    {
        string filePath = "../../../UtFiles/PageManagerSave1.bin";

        using (FileStream fs = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.ReadWrite))
        {
            fs.WriteByte(0xAC);
            fs.WriteByte(0xCE);

            PageType t1 = new PageType(1, 10);
            PageType t2 = new PageType(2, 20);

            int pageSize = 160;
            PageManager pm = PageManager.Create(fs, 2, pageSize, new List<PageType>() { t1, t2 });
            RecordId r1 = pm.AllocateRecord(1);
            RecordBufferWriter w = pm.GetRecordBufferWriter(r1);
            w.WriteInt(7);
            w.WriteInt(8);
            w.WriteInt(9);

            RecordId r2 = pm.AllocateRecord(1);
            w = pm.GetRecordBufferWriter(r2);
            w.WriteInt(3);
            w.WriteInt(4);
            w.WriteInt(5);

            RecordId r3 = pm.AllocateRecord(2);
            w = pm.GetRecordBufferWriter(r3);
            w.WriteInt(4);
            w.WriteInt(5);
            w.WriteInt(6);

            pm.Flush();
        }

        using (FileStream fs = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.ReadWrite))
        {
            fs.WriteByte(0xAC);
            fs.WriteByte(0xCE);

            PageManager pm = PageManager.Load(fs, 2);
        }
    }
}