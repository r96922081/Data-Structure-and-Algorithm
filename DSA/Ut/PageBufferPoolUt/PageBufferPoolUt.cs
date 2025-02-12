using System.Diagnostics;

public class PageBufferPoolUt
{
    private static void Check(bool b)
    {
        Trace.Assert(b);
    }

    private enum PageTypeEnum
    {
        type1,
        type2
    }

    private static void TestPage1()
    {
        int pageCacheCount = 10;
        int pageSize = 160;

        string filePath = "../../../Ut/PageBufferPoolUt/UtFiles/PageManagerSave1.bin";
        RecordStreamWriter w = null;
        RecordStreamReader r = null;

        PageType t1 = new PageType((int)PageTypeEnum.type1, 20);
        PageType t2 = new PageType((int)PageTypeEnum.type2, 30);


        PageBufferPool pm = PageBufferPool.Create(filePath, pageSize, pageCacheCount, new List<PageType>() { t1, t2 });
        RecordId rid1 = pm.AllocateRecord((int)PageTypeEnum.type1);
        w = pm.GetRecordStreamWriter(rid1);
        w.WriteInt(7);
        w.WriteInt(8);
        w.WriteInt(9);

        RecordId rid2 = pm.AllocateRecord((int)PageTypeEnum.type1);
        w = pm.GetRecordStreamWriter(rid2);
        w.WriteInt(3);
        w.WriteInt(4);
        w.WriteInt(5);

        RecordId rid3 = pm.AllocateRecord((int)PageTypeEnum.type2);
        w = pm.GetRecordStreamWriter(rid3);
        w.WriteInt(4);
        w.WriteInt(5);
        w.WriteInt(6);

        pm.Close();

        PageBufferPool pm2 = PageBufferPool.Load(filePath);
        r = pm2.GetRecordStreamReader(rid1);
        Check(r.ReadInt() == 7);
        Check(r.ReadInt() == 8);
        Check(r.ReadInt() == 9);
        r = pm2.GetRecordStreamReader(rid2);
        Check(r.ReadInt() == 3);
        Check(r.ReadInt() == 4);
        Check(r.ReadInt() == 5);
        r = pm2.GetRecordStreamReader(rid3);
        Check(r.ReadInt() == 4);
        Check(r.ReadInt() == 5);
        Check(r.ReadInt() == 6);

        pm2.Close();
    }

    private static void TestPage2()
    {
        int pageCacheCount = 10;
        int pageSize = 160;

        string filePath = "../../../Ut/PageBufferPoolUt/UtFiles/PageManagerSave2.bin";
        RecordStreamWriter w = null;
        RecordStreamReader r = null;

        PageType t1 = new PageType((int)PageTypeEnum.type1, 20);

        PageBufferPool pm = PageBufferPool.Create(filePath, pageSize, pageCacheCount, new List<PageType>() { t1 });
        RecordId rid1 = pm.AllocateRecord((int)PageTypeEnum.type1);
        w = pm.GetRecordStreamWriter(rid1);
        w.WriteInt(7);
        w.WriteInt(8);
        w.WriteInt(9);

        pm.DeleteRecord(rid1);
        RecordId rid2 = pm.AllocateRecord((int)PageTypeEnum.type1);
        w = pm.GetRecordStreamWriter(rid2);
        w.WriteInt(2);
        w.WriteInt(3);
        w.WriteInt(4);

        Check(rid1.pageId == rid2.pageId && rid1.slotId == rid2.slotId);
        r = pm.GetRecordStreamReader(rid1);
        Check(r.ReadInt() == 2);
        Check(r.ReadInt() == 3);
        Check(r.ReadInt() == 4);

        pm.Close();
    }

    private static void TestPage3_Cache()
    {
        int pageCacheCount = 10;
        int pageSize = 100;

        string filePath = "../../../Ut/PageBufferPoolUt/UtFiles/PageManagerSave3.bin";
        RecordStreamWriter w = null;
        RecordStreamReader r = null;

        PageType t1 = new PageType((int)PageTypeEnum.type1, 20);
        PageType t2 = new PageType((int)PageTypeEnum.type2, 30);

        PageBufferPool pm = PageBufferPool.Create(filePath, pageSize, pageCacheCount, new List<PageType>() { t1, t2 });
        List<RecordId> rids = new List<RecordId>();
        for (int i = 0; i < 100; i++)
        {
            rids.Add(pm.AllocateRecord((int)PageTypeEnum.type1));
            rids.Add(pm.AllocateRecord((int)PageTypeEnum.type2));
        }

        for (int i = 0; i < rids.Count; i++)
        {
            w = pm.GetRecordStreamWriter(rids[i]);
            w.WriteInt(i);
        }

        pm.Close();

        PageBufferPool pm2 = PageBufferPool.Load(filePath);
        for (int i = 0; i < rids.Count; i++)
        {
            r = pm2.GetRecordStreamReader(rids[i]);
            Check(r.ReadInt() == i);
        }

        pm2.Close();
    }


    public static void Ut()
    {
        TestPage1();
        TestPage2();
        TestPage3_Cache();
    }
}