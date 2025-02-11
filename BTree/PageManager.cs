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

public class Page : IComparable<Page>
{
    public int type = -1;
    public int index = -1;
    public int pageSize = -1;
    public int recordCount = -1;
    public int recordSize = -1;
    public int freeSlotCount = -1;
    public long pageAge = -1;
    public static long pageAgeCounter = 0;
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
        pageAge = pageAgeCounter++;
        for (int i = 0; i < slotFreeArray.Length; i++)
        {
            if (slotFreeArray[i])
            {
                slotFreeArray[i] = false;
                freeSlotCount--;
                dirty = true;
                return i;
            }
        }

        throw new Exception();
    }

    public void ReleaseSlot(int slotId)
    {
        pageAge = pageAgeCounter++;
        if (slotFreeArray[slotId] == true)
            throw new Exception();
        slotFreeArray[slotId] = true;
        freeSlotCount++;
        dirty = true;
    }

    public RecordStreamWriter GetRecordStreamWriter(int slotId)
    {
        pageAge = pageAgeCounter++;
        dirty = true;
        return new RecordStreamWriter(buffer, headerSize + slotId * recordSize, recordSize);
    }

    public RecordStreamReader GetRecordStreamReader(int slotId)
    {
        pageAge = pageAgeCounter++;
        return new RecordStreamReader(buffer, headerSize + slotId * recordSize, recordSize);
    }

    private int WriteIntToHeader(int pos, int v)
    {
        byte[] bytes = BitConverter.GetBytes(v);
        Buffer.BlockCopy(bytes, 0, buffer, pos, bytes.Length);
        return bytes.Length;
    }

    private int WriteBoolToHeader(int pos, bool v)
    {
        if (v)
            buffer[pos] = 1;
        else
            buffer[pos] = 0;

        return 1;
    }

    private int ReadIntFromHeader(int pos, ref int v)
    {
        byte[] bytes = new byte[4];
        Buffer.BlockCopy(buffer, pos, bytes, 0, bytes.Length);
        v = BitConverter.ToInt32(bytes, 0);

        return bytes.Length;
    }

    private int ReadBoolFromHeader(int pos, ref bool v)
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
        pos += WriteIntToHeader(pos, type);
        pos += WriteIntToHeader(pos, index);
        pos += WriteIntToHeader(pos, pageSize);
        pos += WriteIntToHeader(pos, recordCount);
        pos += WriteIntToHeader(pos, recordSize);
        pos += WriteIntToHeader(pos, freeSlotCount);

        for (int i = 0; i < slotFreeArray.Length; i++)
            WriteBoolToHeader(buffer.Length - 1 - i, slotFreeArray[i]);
    }

    public static Page ReadFromBuffer(byte[] buffer)
    {
        Page p = new Page(buffer);

        int pos = 0;
        pos += p.ReadIntFromHeader(pos, ref p.type);
        pos += p.ReadIntFromHeader(pos, ref p.index);
        pos += p.ReadIntFromHeader(pos, ref p.pageSize);
        pos += p.ReadIntFromHeader(pos, ref p.recordCount);
        pos += p.ReadIntFromHeader(pos, ref p.recordSize);
        pos += p.ReadIntFromHeader(pos, ref p.freeSlotCount);

        p.slotFreeArray = new bool[p.recordCount];
        for (int i = 0; i < p.slotFreeArray.Length; i++)
            p.ReadBoolFromHeader(buffer.Length - 1 - i, ref p.slotFreeArray[i]);

        return p;
    }

    public override bool Equals(object obj)
    {
        return ReferenceEquals(this, obj);
    }

    public override int GetHashCode()
    {
        return System.Runtime.CompilerServices.RuntimeHelpers.GetHashCode(this);
    }

    public int CompareTo(Page? other)
    {
        if (other == null)
            return -1;
        return pageAge.CompareTo(other.pageAge);
    }
}

// a.k.a. BufferPool
public class PageManager
{
    private BinaryWriter bw;
    private BinaryReader br;
    private FileStream fs;

    private int headerSize = 1024;
    private int pageSize = -1;
    private int pageCount = 0;
    private int pageCacheCount = 0;
    private Dictionary<int, Page> cachedPage = new Dictionary<int, Page>();
    private MinPriorityQueue<Page> pageAgePriorityQueue = new MinPriorityQueue<Page>();
    private Dictionary<int, PageType> pageTypes = new Dictionary<int, PageType>();


    /*
     PM header:
     
     int headerSize
     int pageCount
     int pageCacheCount
     int pageSize
     int pageTypeCount
     (
     int type;
     int recordSize; 
     ) * pageTypeCount

     page * pageCount

     */

    public static PageManager Create(string filePath, int pageSize, int pageCacheCount, List<PageType> pageTypes)
    {
        PageManager pm = new PageManager();
        pm.fs = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.ReadWrite);
        pm.bw = new BinaryWriter(pm.fs, System.Text.Encoding.UTF8, leaveOpen: true);
        pm.br = new BinaryReader(pm.fs, System.Text.Encoding.UTF8, leaveOpen: true);
        pm.pageSize = pageSize;
        pm.pageCacheCount = pageCacheCount;

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

    public static PageManager Load(string filePath)
    {
        PageManager pm = new PageManager();
        pm.fs = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.ReadWrite);
        pm.bw = new BinaryWriter(pm.fs, System.Text.Encoding.UTF8, leaveOpen: true);
        pm.br = new BinaryReader(pm.fs, System.Text.Encoding.UTF8, leaveOpen: true);

        pm.br.BaseStream.Seek(0, SeekOrigin.Begin);
        pm.headerSize = pm.br.ReadInt32();
        pm.pageCount = pm.br.ReadInt32();
        pm.pageCacheCount = pm.br.ReadInt32();
        pm.pageSize = pm.br.ReadInt32();

        int pageTypeCount = pm.br.ReadInt32();
        Dictionary<int, PageType> pageTypes = new Dictionary<int, PageType>();
        for (int i = 0; i < pageTypeCount; i++)
        {
            int type = pm.br.ReadInt32();
            int size = pm.br.ReadInt32();
            pageTypes.Add(type, new PageType(type, size));
        }

        return pm;
    }

    public void FlushPage(Page p)
    {
        p.WriteToBuffer();
        bw.Seek(headerSize + p.index * pageSize, SeekOrigin.Begin);
        bw.Write(p.buffer, 0, p.pageSize);
        p.dirty = false;
    }

    private void WriteHeader()
    {
        bw.BaseStream.Seek(0, SeekOrigin.Begin);
        bw.Write(headerSize);
        bw.Write(pageCount);
        bw.Write(pageCacheCount);
        bw.Write(pageSize);
        bw.Write(pageTypes.Count);

        foreach (PageType type in pageTypes.Values)
        {
            bw.Write(type.type);
            bw.Write(type.recordSize);
        }
    }

    public void Close()
    {
        WriteHeader();

        for (int i = 0; i < cachedPage.Count; i++)
        {
            Page page = cachedPage[i];
            if (page.dirty == false)
                continue;
            FlushPage(page);
        }

        bw.Close();
        br.Close();
        fs.Close();
    }

    public RecordId AllocateRecord(int type)
    {
        foreach (Page p in cachedPage.Values)
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
        Page p = cachedPage[id.pageId];
        p.ReleaseSlot(id.slotId);
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
        if (cachedPage.ContainsKey(pageId))
            return cachedPage[pageId];

        return ReadPageFromFile(pageId);
    }

    private Page ReadPageFromFile(int pageId)
    {
        fs.Seek(headerSize + pageId * pageSize, SeekOrigin.Begin);
        byte[] buffer = br.ReadBytes(pageSize);
        return Page.ReadFromBuffer(buffer);
    }

    private Page NewPage(int pageType)
    {
        PageType type = pageTypes[pageType];

        Page page = new Page(pageType, pageCount, pageSize, type.recordSize);
        cachedPage.Add(page.index, page);

        byte[] zeros = new byte[pageSize];
        fs.Seek(0, SeekOrigin.End);
        fs.Write(zeros, 0, zeros.Length);

        pageCount++;

        return page;
    }
}