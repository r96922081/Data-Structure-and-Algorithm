using System.Diagnostics;

public class CustomClass4 : IBPlusTreePagedData
{
    public int value = 0;

    public CustomClass4()
    {

    }

    public CustomClass4(int value)
    {
        this.value = value;
    }

    public override IComparable GetKey()
    {
        return value;
    }

    public override IBPlusTreePagedData CloneKeyOnly()
    {
        return new CustomClass4(value);
    }

    public override object GetData()
    {
        return value;
    }

    public override void Save(BPlusTreePagedPageController pc)
    {
        RecordStreamWriter writer = pc.GetRecordStreamWriter(rid);
        writer.WriteBool(leftDataRid != null);
        writer.WriteRecord(leftDataRid);
        writer.WriteBool(rightDataRid != null);
        writer.WriteRecord(rightDataRid);

        // data
        writer.WriteInt(value);
    }

    public override IBPlusTreePagedData Load(BPlusTreePagedPageController pc)
    {
        CustomClass4 ret = new CustomClass4();
        RecordStreamReader reader = pc.GetRecordStreamReader(rid);
        bool hasLeftData = reader.ReadBool();
        if (hasLeftData)
            ret.leftDataRid = reader.ReadRecord();
        bool hasRightData = reader.ReadBool();
        if (hasRightData)
            ret.rightDataRid = reader.ReadRecord();

        // data
        ret.value = reader.ReadInt();

        return ret;
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
        BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);

        BPlusTreePaged tree = new BPlusTreePaged(2, pc);
        for (int i = 1; i >= 1; i--)
            tree.Insert(new CustomClass4(1));

        List<IBPlusTreePagedData> found = tree.Find(1);
        Check(found.Count == 1);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);

        pc.Close();
    }

    private static void Find2()
    {
        BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pc);
        for (int i = 3; i >= 1; i--)
            tree.Insert(new CustomClass4(1));

        List<IBPlusTreePagedData> found = tree.Find(1);
        Check(found.Count == 3);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);

        pc.Close();
    }

    private static void Find3()
    {
        BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pc);
        for (int i = 4; i >= 1; i--)
            tree.Insert(new CustomClass4(1));

        List<IBPlusTreePagedData> found = tree.Find(1);
        Check(found.Count == 4);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);

        pc.Close();
    }

    private static void Find4()
    {
        BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pc);
        for (int i = 100; i >= 1; i--)
            tree.Insert(new CustomClass4(1));

        List<IBPlusTreePagedData> found = tree.Find(1);
        Check(found.Count == 100);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);

        pc.Close();
    }

    private static void Find5()
    {
        BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pc);

        for (int i = 5; i < 15; i++)
            for (int j = 0; j < 6; j++)
                tree.Insert(new CustomClass4(i));

        //Console.WriteLine(tree);

        for (int i = 5; i < 15; i++)
        {
            List<IBPlusTreePagedData> found = tree.Find(i);
            Check(found.Count == 6);
            Check(found[0].GetKey().CompareTo(i) == 0);
        }

        pc.Close();
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
            BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);
            BPlusTreePaged tree = new BPlusTreePaged(t, pc);
            for (int i = 0; i < dataCount; i++)
                tree.Insert(new CustomClass4(i));

            for (int i = 0; i < dataCount; i++)
            {
                int count = tree.Delete(i);
                //Console.WriteLine(tree);
                Check(count == 1);
                CheckBPlusTreePagedValidity(tree, dataCount - i - 1);
            }

            Check(tree.root == null);
            pc.Close();
        }
        else if (order == DeleteOrder.Descending)
        {
            BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);
            BPlusTreePaged tree = new BPlusTreePaged(t, pc);
            for (int i = 0; i < dataCount; i++)
                tree.Insert(new CustomClass4(i));

            for (int i = dataCount - 1; i >= 0; i--)
            {
                int count = tree.Delete(i);
                //Console.WriteLine(tree);
                Check(count == 1);
                CheckBPlusTreePagedValidity(tree, i);
            }

            Check(tree.root == null);
            pc.Close();
        }
        else if (order == DeleteOrder.Random)
        {
            for (int randomCount = 0; randomCount < 1000 * 100; randomCount += 1000)
            {
                BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);
                //Console.WriteLine("iteration = " + iteration++);

                BPlusTreePaged tree = new BPlusTreePaged(t, pc);
                for (int i = 0; i < dataCount; i++)
                    tree.Insert(new CustomClass4(i));

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

                Check(tree.root == null);

                pc.Close();
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
        BPlusTreePagedPageController pc = new BPlusTreePagedPageController("../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin", 2);
        BPlusTreePaged tree = new BPlusTreePaged(2, pc);

        List<int> values = new List<int>();

        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 2; j++)
                values.Add(i);

        Random random = new Random(0);
        while (values.Count > 0)
        {
            int valueIndex = random.Next() % values.Count;
            tree.Insert(new CustomClass4(values[valueIndex]));
            values.RemoveAt(valueIndex);
        }

        //Console.WriteLine(tree);

        CheckBPlusTreePagedValidity(tree, 200);
        pc.Close();
    }

    private static void CheckBPlusTreePagedValidity(BPlusTreePaged tree, int dataCount)
    {
        if (tree.root == null)
            return;

        CheckBPlusTreePagedValidity1_KeyAndChildCount(tree);
        CheckBPlusTreePagedValidity2_leafDepth(tree);
        CheckBPlusTreePagedValidity3_CheckOrder(tree);
        CheckBPlusTreePagedValidity4_CheckLink(tree, dataCount);
    }

    private static void CheckBPlusTreePagedValidity1_KeyAndChildCount(BPlusTreePaged tree)
    {
        foreach (BPlusTreePagedNode n in tree.root.children)
            CheckBPlusTreePagedValidity1_KeyAndChildCountInternal(tree, n);
    }

    private static void CheckBPlusTreePagedValidity1_KeyAndChildCountInternal(BPlusTreePaged tree, BPlusTreePagedNode n)
    {
        if (n == null)
            return;

        if (n != tree.root)
            Check(tree.t - 1 <= n.keys.Count && n.keys.Count <= 2 * tree.t - 1);

        if (n.children.Count != 0)
            Check(n.keys.Count + 1 == n.children.Count);

        foreach (BPlusTreePagedNode child in n.children)
            CheckBPlusTreePagedValidity1_KeyAndChildCountInternal(tree, child);
    }

    private static void CheckBPlusTreePagedValidity2_leafDepthInternal(BPlusTreePagedNode n, int prevLeafDepth, int FirstLeafDepth)
    {
        if (n.IsLeaf())
            Check(prevLeafDepth == FirstLeafDepth);
        else
        {
            foreach (BPlusTreePagedNode child in n.children)
                CheckBPlusTreePagedValidity2_leafDepthInternal(child, prevLeafDepth + 1, FirstLeafDepth);
        }
    }

    private static void CheckBPlusTreePagedValidity2_leafDepth(BPlusTreePaged tree)
    {
        if (tree.root == null)
            return;

        BPlusTreePagedNode firstChild = tree.root;
        int depth = 0;
        while (firstChild.children.Count != 0)
        {
            firstChild = firstChild.children[0];
            depth++;
        }

        CheckBPlusTreePagedValidity2_leafDepthInternal(tree.root, 0, depth);
    }

    private static IBPlusTreePagedData CheckBPlusTreePagedValidity3_CheckOrderInternal(BPlusTreePagedNode node, IBPlusTreePagedData prevValue)
    {
        for (int i = 0; i < node.children.Count; i++)
        {
            if (node.IsInternal())
                prevValue = CheckBPlusTreePagedValidity3_CheckOrderInternal(node.children[i], prevValue);

            if (i < node.keys.Count)
            {
                Check(node.keys[i].GetKey().CompareTo(prevValue.GetKey()) >= 0);
                prevValue = node.keys[i];
            }
        }

        return prevValue;
    }


    private static void CheckBPlusTreePagedValidity4_CheckLink(BPlusTreePaged tree, int dataCount)
    {
        if (tree.root == null)
            return;

        BPlusTreePagedNode firstLeaf = tree.root;
        while (firstLeaf.children.Count != 0)
            firstLeaf = firstLeaf.children[0];

        IBPlusTreePagedData currentData = firstLeaf.keys[0];
        IBPlusTreePagedData prevData = null;

        for (int i = 0; i < dataCount; i++)
        {
            if (i == 0)
                Check(currentData.leftData == null);
            else if (i == dataCount - 1)
                Check(currentData.rightData == null);

            if (i != 0)
            {
                Check(currentData.leftData == prevData);
                Check(currentData.leftData.GetKey().CompareTo(currentData.GetKey()) <= 0);
            }

            prevData = currentData;
            currentData = currentData.rightData;
        }
    }

    private static void CheckBPlusTreePagedValidity3_CheckOrder(BPlusTreePaged tree)
    {
        CheckBPlusTreePagedValidity3_CheckOrderInternal(tree.root, new CustomClass4(-1));
    }

    private static string filePath = "../../../Ut/BTreeUt/UtFiles/B+TreePagedUt.bin";

    private static void TestPage1()
    {
        BPlusTreePagedPageController pc = new BPlusTreePagedPageController(filePath, 2);
        BPlusTreePaged tree = pc.CreateTree(2);
        tree.Save(pc);
        pc.Close();

        pc = new BPlusTreePagedPageController(filePath, 2);
        tree = BPlusTreePaged.LoadTree(pc);
        Check(tree.t == 2);
        Check(tree.root == null);
        pc.Close();
    }

    private static void TestPage2()
    {
        BPlusTreePagedPageController pc = new BPlusTreePagedPageController(filePath, 2);
        BPlusTreePaged tree = pc.CreateTree(2);
        tree.Save(pc);
        pc.Close();

        pc = new BPlusTreePagedPageController(filePath, 2);
        tree = BPlusTreePaged.LoadTree(pc);
        Check(tree.t == 2);
        Check(tree.root == null);
        pc.Close();
    }

    private static void TestPage()
    {
        TestPage1();
        TestPage2();
    }

    public static void Ut()
    {
        TestPage();
        TestBPlusTreePagedInsert();
        TestBPlusTreePagedFind();
        TestBPlusTreePagedDelete();
    }
}