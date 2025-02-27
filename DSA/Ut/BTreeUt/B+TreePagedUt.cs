using System.Diagnostics;

public class CustomClass4 : IBPlusTreePagedData
{
    public RecordId rid = null;
    public int value = 0;
    public PageBufferPool pageBufferPool = null;

    private CustomClass4()
    {

    }

    public CustomClass4(PageBufferPool pageBufferPool, int value)
    {
        rid = pageBufferPool.AllocateRecord((int)BPlusTreePaged_PageTypeEnum.Data, this);
        this.pageBufferPool = pageBufferPool;
        this.value = value;
        Save(pageBufferPool);
    }

    public void Save(PageBufferPool pageBufferPool)
    {
        RecordStreamWriter writer = pageBufferPool.GetRecordStreamWriter(rid);
        writer.WriteInt(value);
    }

    public IBPlusTreePagedData Load(PageBufferPool pageBufferPool, RecordId rid)
    {
        CustomClass4 ret = new CustomClass4();
        ret.pageBufferPool = pageBufferPool;
        RecordStreamReader reader = pageBufferPool.GetRecordStreamReader(rid);
        ret.value = reader.ReadInt();

        return ret;
    }

    public IComparable GetComparableKey()
    {
        return value;
    }

    public IBPlusTreePagedData CloneKeyOnly()
    {
        return new CustomClass4(pageBufferPool, value);
    }

    public static CustomClass4 GetDummyData()
    {
        return new CustomClass4();
    }

    public RecordId GetRid()
    {
        return rid;
    }

    public object GetData()
    {
        return value;
    }

    public int CompareTo(IBPlusTreePagedData? other)
    {
        if (other == null)
            return 0;

        if (value < ((CustomClass4)other).value)
            return -1;
        else if (value == ((CustomClass4)other).value)
            return 0;
        else
            return 1;
    }

    public override string ToString()
    {
        return "" + value;
    }
}

public class BPlusTreePagedUt
{
    private static void Check(bool b)
    {
        Trace.Assert(b);
    }

    private static void Find1()
    {
        PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 1);

        BPlusTreePaged tree = new BPlusTreePaged(2, pageBufferPool, new CustomClass4(pageBufferPool, -1));
        for (int i = 1; i >= 1; i--)
        {
            CustomClass4 d = new CustomClass4(pageBufferPool, 1);
            tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
        }

        List<BPlusTreePagedKey> found = tree.Find(1);
        Check(found.Count == 1);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);

        pageBufferPool.Close();
    }

    private static void Find2()
    {
        PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pageBufferPool, CustomClass4.GetDummyData());
        for (int i = 3; i >= 1; i--)
        {
            CustomClass4 d = new CustomClass4(pageBufferPool, 1);
            tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
        }

        List<BPlusTreePagedKey> found = tree.Find(1);
        Check(found.Count == 3);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);

        pageBufferPool.Close();
    }

    private static void Find3()
    {
        PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pageBufferPool, CustomClass4.GetDummyData());
        for (int i = 4; i >= 1; i--)
        {
            CustomClass4 d = new CustomClass4(pageBufferPool, 1);
            tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
        }

        List<BPlusTreePagedKey> found = tree.Find(1);
        Check(found.Count == 4);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);

        pageBufferPool.Close();
    }

    private static void Find4()
    {
        PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pageBufferPool, CustomClass4.GetDummyData());
        for (int i = 100; i >= 1; i--)
        {
            CustomClass4 d = new CustomClass4(pageBufferPool, 1);
            tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
        }

        List<BPlusTreePagedKey> found = tree.Find(1);
        Check(found.Count == 100);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);

        pageBufferPool.Close();
    }

    private static void Find5()
    {
        PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pageBufferPool, CustomClass4.GetDummyData());

        for (int i = 5; i < 15; i++)
            for (int j = 0; j < 6; j++)
            {
                CustomClass4 d = new CustomClass4(pageBufferPool, i);
                tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
            }

        //Console.WriteLine(tree);

        for (int i = 5; i < 15; i++)
        {
            List<BPlusTreePagedKey> found = tree.Find(i);
            Check(found.Count == 6);
            Check(found[0].GetComparableKey().CompareTo(i) == 0);
        }

        pageBufferPool.Close();
    }

    private static void TestBPlusTreePagedFind()
    {
        Find1();
        Find2();
        Find3();
        Find4();
        Find5();
    }

    private enum DeleteOrder
    {
        Ascending,
        Descending,
        Random
    }

    private static void DeleteInternal(int t, int dataCount, DeleteOrder order)
    {
        if (order == DeleteOrder.Ascending)
        {
            PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 2);
            BPlusTreePaged tree = new BPlusTreePaged(t, pageBufferPool, CustomClass4.GetDummyData());
            for (int i = 0; i < dataCount; i++)
            {
                CustomClass4 d = new CustomClass4(pageBufferPool, i);
                tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
            }

            for (int i = 0; i < dataCount; i++)
            {
                int count = tree.Delete(i);
                //Console.WriteLine(tree);
                Check(count == 1);
                CheckBPlusTreePagedValidity(tree, dataCount - i - 1);
            }

            Check(tree.GetRootRid() == null);
            pageBufferPool.Close();
        }
        else if (order == DeleteOrder.Descending)
        {
            PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 2);
            BPlusTreePaged tree = new BPlusTreePaged(t, pageBufferPool, CustomClass4.GetDummyData());
            for (int i = 0; i < dataCount; i++)
            {
                CustomClass4 d = new CustomClass4(pageBufferPool, i);
                tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
            }

            for (int i = dataCount - 1; i >= 0; i--)
            {
                int count = tree.Delete(i);
                //Console.WriteLine(tree);
                Check(count == 1);
                CheckBPlusTreePagedValidity(tree, i);
            }

            Check(tree.GetRootRid() == null);
            pageBufferPool.Close();
        }
        else if (order == DeleteOrder.Random)
        {
            for (int randomCount = 0; randomCount < 1000 * 100; randomCount += 1000)
            {
                PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 2);
                //Console.WriteLine("iteration = " + iteration++);

                BPlusTreePaged tree = new BPlusTreePaged(t, pageBufferPool, CustomClass4.GetDummyData());
                for (int i = 0; i < dataCount; i++)
                {
                    CustomClass4 d = new CustomClass4(pageBufferPool, i);
                    tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
                }

                List<int> values = new List<int>();
                for (int i = 0; i < dataCount; i++)
                    values.Add(i);
                Random random = new Random(0);

                int tempDataCount = dataCount;

                while (values.Count > 0)
                {
                    int valueIndex = random.Next() % values.Count;
                    int count = tree.Delete(values[valueIndex]);
                    //Console.WriteLine(tree);
                    tempDataCount--;
                    Check(count == 1);
                    values.RemoveAt(valueIndex);
                    CheckBPlusTreePagedValidity(tree, tempDataCount);
                }

                Check(tree.GetRootRid() == null);

                pageBufferPool.Close();
            }
        }
    }

    private static void TestBPlusTreePagedDelete()
    {
        DeleteInternal(2, 1, DeleteOrder.Ascending);
        DeleteInternal(2, 4, DeleteOrder.Ascending);
        DeleteInternal(2, 5, DeleteOrder.Ascending);
        DeleteInternal(2, 10, DeleteOrder.Ascending);
        DeleteInternal(2, 100, DeleteOrder.Ascending);

        DeleteInternal(2, 1, DeleteOrder.Descending);
        DeleteInternal(2, 4, DeleteOrder.Descending);
        DeleteInternal(2, 5, DeleteOrder.Descending);
        DeleteInternal(2, 10, DeleteOrder.Descending);
        DeleteInternal(2, 100, DeleteOrder.Descending);

        DeleteInternal(2, 1, DeleteOrder.Random);
        DeleteInternal(2, 4, DeleteOrder.Random);
        DeleteInternal(2, 5, DeleteOrder.Random);
        DeleteInternal(2, 10, DeleteOrder.Random);
        DeleteInternal(2, 100, DeleteOrder.Random);
    }

    private static void TestBPlusTreePagedInsert()
    {
        PageBufferPool pageBufferPool = PageBufferPool.Create("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 1024, 1);
        BPlusTreePaged tree = new BPlusTreePaged(2, pageBufferPool, CustomClass4.GetDummyData());

        List<int> values = new List<int>();

        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 2; j++)
                values.Add(i);

        Random random = new Random(0);
        while (values.Count > 0)
        {
            int valueIndex = random.Next() % values.Count;
            CustomClass4 d = new CustomClass4(pageBufferPool, values[valueIndex]);
            tree.Insert(new BPlusTreePagedKey(pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
            values.RemoveAt(valueIndex);
        }

        //Console.WriteLine(tree);

        CheckBPlusTreePagedValidity(tree, 200);
        pageBufferPool.Close();
    }

    private static void CheckBPlusTreePagedValidity(BPlusTreePaged tree, int dataCount)
    {
        if (tree.GetRootRid() == null)
            return;

        CheckBPlusTreePagedValidity1_KeyAndChildCount(tree);
        CheckBPlusTreePagedValidity2_leafDepth(tree);
        CheckBPlusTreePagedValidity3_CheckOrder(tree);
        CheckBPlusTreePagedValidity4_CheckLink(tree, dataCount);
    }

    private static void CheckBPlusTreePagedValidity1_KeyAndChildCount(BPlusTreePaged tree)
    {
        for (int i = 0; i < tree.GetNode(tree.GetRootRid()).GetChildrenCount(); i++)
            CheckBPlusTreePagedValidity1_KeyAndChildCountInternal(tree, tree.GetNode(tree.GetRootRid()).GetChild(i));
    }

    private static void CheckBPlusTreePagedValidity1_KeyAndChildCountInternal(BPlusTreePaged tree, RecordId recordId)
    {
        BPlusTreePagedNode n = tree.GetNode(recordId);
        if (n == null)
            return;

        if (n.rid != tree.GetRootRid())
            Check(tree.GetT() - 1 <= n.GetKeyCount() && n.GetKeyCount() <= 2 * tree.GetT() - 1);

        if (n.GetChildrenCount() != 0)
            Check(n.GetKeyCount() + 1 == n.GetChildrenCount());

        for (int i = 0; i < n.GetChildrenCount(); i++)
            CheckBPlusTreePagedValidity1_KeyAndChildCountInternal(tree, n.GetChild(i));
    }

    private static void CheckBPlusTreePagedValidity2_leafDepthInternal(BPlusTreePaged tree, BPlusTreePagedNode n, int prevLeafDepth, int FirstLeafDepth)
    {
        if (n.IsLeaf())
            Check(prevLeafDepth == FirstLeafDepth);
        else
        {
            for (int i = 0; i < n.GetChildrenCount(); i++)
                CheckBPlusTreePagedValidity2_leafDepthInternal(tree, tree.GetNode(n.GetChild(i)), prevLeafDepth + 1, FirstLeafDepth);
        }
    }

    private static void CheckBPlusTreePagedValidity2_leafDepth(BPlusTreePaged tree)
    {
        if (tree.GetRootRid() == null)
            return;

        BPlusTreePagedNode firstChild = tree.GetNode(tree.GetRootRid());
        int depth = 0;
        while (firstChild.GetChildrenCount() != 0)
        {
            firstChild = tree.GetNode(firstChild.GetChild(0));
            depth++;
        }

        CheckBPlusTreePagedValidity2_leafDepthInternal(tree, tree.GetNode(tree.GetRootRid()), 0, depth);
    }

    private static BPlusTreePagedKey CheckBPlusTreePagedValidity3_CheckOrderInternal(BPlusTreePaged tree, BPlusTreePagedNode node, BPlusTreePagedKey prevValue)
    {
        for (int i = 0; i < node.GetChildrenCount(); i++)
        {
            if (node.IsInternal())
                prevValue = CheckBPlusTreePagedValidity3_CheckOrderInternal(tree, tree.GetNode(node.GetChild(i)), prevValue);

            if (i < node.GetKeyCount())
            {
                Check(tree.GetKey(node.GetKeyAt(i)).GetComparableKey().CompareTo(prevValue.GetComparableKey()) >= 0);
                prevValue = tree.GetKey(node.GetKeyAt(i));
            }
        }

        return prevValue;
    }


    private static void CheckBPlusTreePagedValidity4_CheckLink(BPlusTreePaged tree, int dataCount)
    {
        if (tree.GetRootRid() == null)
            return;

        BPlusTreePagedNode firstLeaf = tree.GetNode(tree.GetRootRid());
        while (firstLeaf.GetChildrenCount() != 0)
            firstLeaf = tree.GetNode(firstLeaf.GetChild(0));

        BPlusTreePagedKey currentData = tree.GetKey(firstLeaf.GetKeyAt(0));
        BPlusTreePagedKey prevData = null;

        for (int i = 0; i < dataCount; i++)
        {
            if (i == 0)
                Check(currentData.GetLeft() == null);
            else if (i == dataCount - 1)
                Check(currentData.GetRight() == null);

            if (i != 0)
            {
                Check(currentData.GetLeft() == prevData);
                Check(currentData.GetLeft().GetComparableKey().CompareTo(currentData.GetComparableKey()) <= 0);
            }

            prevData = currentData;
            currentData = currentData.GetRight();
        }
    }

    private static void CheckBPlusTreePagedValidity3_CheckOrder(BPlusTreePaged tree)
    {
        CustomClass4 d = new CustomClass4(tree.pageBufferPool, -1);
        CheckBPlusTreePagedValidity3_CheckOrderInternal(tree, tree.GetNode(tree.GetRootRid()), new BPlusTreePagedKey(tree.pageBufferPool, d.GetRid(), CustomClass4.GetDummyData()));
    }

    private static string filePath = "../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin";

    private static void TestPage1()
    {
        PageBufferPool pageBufferPool = PageBufferPool.Create(filePath, 1024, 1);
        pageBufferPool.AddPageType(BPlusTreePaged_PageTypeFactory.GetTreeType());
        pageBufferPool.AddPageType(BPlusTreePaged_PageTypeFactory.GetNodeType(2));
        pageBufferPool.AddPageType(BPlusTreePaged_PageTypeFactory.GetKeyType());
        pageBufferPool.AddPageType(BPlusTreePaged_PageTypeFactory.GetDataType(10));

        BPlusTreePaged tree = new BPlusTreePaged(2, pageBufferPool, CustomClass4.GetDummyData());
        pageBufferPool.Close();

        pageBufferPool = PageBufferPool.Load(filePath);
        tree = BPlusTreePaged.Load(pageBufferPool, CustomClass4.GetDummyData());
        Check(tree.GetT() == 2);
        Check(tree.GetRootRid() == null);
        pageBufferPool.Close();
    }

    private static void TestPage2()
    {
        PageBufferPool pageBufferPool = PageBufferPool.Create(filePath, 1024, 1);
        pageBufferPool.AddPageType(BPlusTreePaged_PageTypeFactory.GetTreeType());
        pageBufferPool.AddPageType(BPlusTreePaged_PageTypeFactory.GetNodeType(2));
        pageBufferPool.AddPageType(BPlusTreePaged_PageTypeFactory.GetKeyType());
        pageBufferPool.AddPageType(BPlusTreePaged_PageTypeFactory.GetDataType(10));

        BPlusTreePaged tree = new BPlusTreePaged(2, pageBufferPool, CustomClass4.GetDummyData());
        tree.Insert(new BPlusTreePagedKey(pageBufferPool, new CustomClass4(pageBufferPool, 1).GetRid(), CustomClass4.GetDummyData()));
        //tree.Insert(new BPlusTreePagedKey(pageBufferPool, new CustomClass4(pageBufferPool, 2).GetRid(), CustomClass4.GetDummyData()));
        pageBufferPool.Close();

        pageBufferPool = PageBufferPool.Load(filePath);
        tree = BPlusTreePaged.Load(pageBufferPool, CustomClass4.GetDummyData());
        Check(tree.GetT() == 2);
        Check(tree.GetRootRid() != null);
        BPlusTreePagedNode n = tree.GetNode(tree.GetRootRid());
        Console.WriteLine(tree);

        pageBufferPool.Close();
    }

    private static void TestPage()
    {
        //TestPage1();
        TestPage2();
    }

    public static void Ut()
    {
        TestPage();

        //TestBPlusTreePagedInsert();
        //TestBPlusTreePagedFind();
        //TestBPlusTreePagedDelete();
    }
}