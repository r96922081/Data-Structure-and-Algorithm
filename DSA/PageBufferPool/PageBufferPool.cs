public class RecordId
{
    public int pageId;
    public int slotId;

    public RecordId(int pageId, int slotId)
    {
        this.pageId = pageId;
        this.slotId = slotId;
    }

    public override bool Equals(object obj)
    {
        if (obj == null)
            return false;

        if (!(obj is RecordId))
            return false;

        return Equals((RecordId)obj);
    }

    public bool Equals(RecordId other)
    {
        return pageId == other.pageId && slotId == other.slotId;
    }

    public override int GetHashCode()
    {
        return pageId + 100000 + slotId;
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

    public void WriteBool(bool b)
    {
        buffer[currentPos++] = b ? (byte)1 : (byte)0;
    }

    public void WriteRecord(RecordId rid)
    {
        WriteBool(rid != null);

        if (rid != null)
        {
            WriteInt(rid.pageId);
            WriteInt(rid.slotId);
        }
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

    public bool ReadBool()
    {
        return buffer[currentPos++] == 1;
    }

    public RecordId ReadRecord()
    {
        if (ReadBool() == false)
            return null;

        int pageId = ReadInt();
        int slotId = ReadInt();
        return new RecordId(pageId, slotId);
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
        if (slotFreeArray[slotId] == true)
            throw new Exception();
        slotFreeArray[slotId] = true;
        freeSlotCount++;
        dirty = true;
    }

    public RecordStreamWriter GetRecordStreamWriter(int slotId)
    {
        dirty = true;
        return new RecordStreamWriter(buffer, headerSize + slotId * recordSize, recordSize);
    }

    public RecordStreamReader GetRecordStreamReader(int slotId)
    {
        return new RecordStreamReader(buffer, headerSize + slotId * recordSize, recordSize);
    }

    public void Age()
    {
        pageAge = pageAgeCounter++;
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

public class PageBufferPool
{
    private BinaryWriter bw;
    private BinaryReader br;
    private FileStream fs;

    private int headerSize = 1024;
    private int pageSize = -1;
    private int pageCount = 0;
    private int pageCacheCount = 0;
    private Dictionary<int, Page> cachedPages = new Dictionary<int, Page>();
    private MinPriorityQueue<Page> pagePriorityQueue = new MinPriorityQueue<Page>();
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

    public static PageBufferPool Create(string filePath, int pageSize, int pageCacheCount, List<PageType> pageTypes)
    {
        PageBufferPool pm = new PageBufferPool();
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

    public static PageBufferPool Load(string filePath)
    {
        PageBufferPool pm = new PageBufferPool();
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

        foreach (Page p in cachedPages.Values)
        {
            if (p.dirty == false)
                continue;
            FlushPage(p);
        }

        bw.Close();
        br.Close();
        fs.Close();
    }

    public RecordId AllocateRecord(int type)
    {
        Page p = null;

        foreach (Page p2 in cachedPages.Values)
        {
            if (p2.type == type && p2.freeSlotCount > 0)
            {
                p = p2;
                break;
            }
        }

        if (p == null)
            p = NewPage(type);

        p.dirty = true;
        p.Age();
        pagePriorityQueue.IncreaseKey(p);
        return new RecordId(p.index, p.AllocateSlot());
    }

    public void DeleteRecord(RecordId id)
    {
        GetPage(id.pageId).ReleaseSlot(id.slotId);
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
        Page p = null;
        if (cachedPages.ContainsKey(pageId))
            p = cachedPages[pageId];
        else
            p = ReadPageFromFile(pageId);
        p.Age();
        pagePriorityQueue.IncreaseKey(p);
        return p;
    }

    private Page ReadPageFromFile(int pageId)
    {
        fs.Seek(headerSize + pageId * pageSize, SeekOrigin.Begin);
        byte[] buffer = br.ReadBytes(pageSize);
        Page p = Page.ReadFromBuffer(buffer);
        ReplacePageInCache(p);
        return p;
    }

    private Page NewPage(int pageType)
    {
        PageType type = pageTypes[pageType];

        Page page = new Page(pageType, pageCount, pageSize, type.recordSize);

        byte[] zeros = new byte[pageSize];
        fs.Seek(0, SeekOrigin.End);
        fs.Write(zeros, 0, zeros.Length);

        pageCount++;
        ReplacePageInCache(page);

        return page;
    }

    private void ReplacePageInCache(Page p)
    {
        if (cachedPages.ContainsKey(p.index))
            return;

        // EvictPage
        if (cachedPages.Count >= pageCacheCount && cachedPages.Count != 0)
        {
            Page evictedPage = pagePriorityQueue.ExtractMin();
            cachedPages.Remove(evictedPage.index);

            if (evictedPage.dirty)
                FlushPage(evictedPage);
        }

        pagePriorityQueue.Insert(p);
        cachedPages.Add(p.index, p);

    }
}