using System.Diagnostics;

public class CustomClass3 : IBPlusTreeData
{
    public int value = 0;

    public CustomClass3()
    {

    }

    public CustomClass3(int value)
    {
        this.value = value;
    }

    public override IComparable GetKey()
    {
        return value;
    }

    public override IBPlusTreeData CloneKeyOnly()
    {
        return new CustomClass3(value);
    }

    public override object GetData()
    {
        return value;
    }

    public int CompareTo(IBPlusTreeData? other)
    {
        if (other == null)
            return 0;

        if (value < ((CustomClass3)other).value)
            return -1;
        else if (value == ((CustomClass3)other).value)
            return 0;
        else
            return 1;
    }

    public override string ToString()
    {
        return "" + value;
    }
}

public class BPlusTreeUt
{
    private static void Check(bool b)
    {
        Trace.Assert(b);
    }

    private static void Find1()
    {
        BPlusTree tree = new BPlusTree(2);
        for (int i = 1; i >= 1; i--)
            tree.Insert(new CustomClass3(1));

        List<IBPlusTreeData> found = tree.Find(1);
        Check(found.Count == 1);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);
    }

    private static void Find2()
    {
        BPlusTree tree = new BPlusTree(2);
        for (int i = 3; i >= 1; i--)
            tree.Insert(new CustomClass3(1));

        List<IBPlusTreeData> found = tree.Find(1);
        Check(found.Count == 3);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);
    }

    private static void Find3()
    {
        BPlusTree tree = new BPlusTree(2);
        for (int i = 4; i >= 1; i--)
            tree.Insert(new CustomClass3(1));

        List<IBPlusTreeData> found = tree.Find(1);
        Check(found.Count == 4);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);
    }

    private static void Find4()
    {
        BPlusTree tree = new BPlusTree(2);
        for (int i = 100; i >= 1; i--)
            tree.Insert(new CustomClass3(1));

        List<IBPlusTreeData> found = tree.Find(1);
        Check(found.Count == 100);
        found = tree.Find(0);
        Check(found.Count == 0);
        found = tree.Find(2);
        Check(found.Count == 0);
    }

    private static void Find5()
    {
        BPlusTree tree = new BPlusTree(2);

        for (int i = 5; i < 15; i++)
            for (int j = 0; j < 6; j++)
                tree.Insert(new CustomClass3(i));

        //Console.WriteLine(tree);

        for (int i = 5; i < 15; i++)
        {
            List<IBPlusTreeData> found = tree.Find(i);
            Check(found.Count == 6);
            Check(found[0].GetKey().CompareTo(i) == 0);
        }
    }

    private static void TestBPlusTreeFind()
    {
        Find1();
        Find2();
        Find3();
        Find4();
        Find5();
    }

    private static void TestBPlusTreeInsert()
    {
        BPlusTree tree2 = new BPlusTree(2);
        tree2.Insert(new CustomClass3(1));
        tree2.Insert(new CustomClass3(2));
        tree2.Insert(new CustomClass3(3));
        tree2.Insert(new CustomClass3(4));

        BPlusTree tree = new BPlusTree(2);

        List<int> values = new List<int>();

        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 2; j++)
                values.Add(i);

        Random random = new Random(0);
        while (values.Count > 0)
        {
            int valueIndex = random.Next() % values.Count;
            tree.Insert(new CustomClass3(values[valueIndex]));
            values.RemoveAt(valueIndex);
        }

        //Console.WriteLine(tree);

        CheckBPlusTreeValidity(tree);

        // check link
        List<IBPlusTreeData> min = tree.Find(0);

        IBPlusTreeData d = min[1];
        d = d.rightData;
        for (int i = 1; i < 100; i++)
        {
            d = d.rightData;
            Check(d.GetKey().CompareTo(i) == 0);
            d = d.rightData;
            Check(d.GetKey().CompareTo(i) == 0);
        }

        Check(d.rightData == null);
    }

    private static void CheckBPlusTreeValidity(BPlusTree tree)
    {
        if (tree.root == null)
            return;

        CheckBPlusTreeValidity1_KeyAndChildCount(tree);
        CheckBPlusTreeValidity2_leafDepth(tree);
        CheckBPlusTreeValidity3_CheckOrder(tree);
    }

    private static void CheckBPlusTreeValidity1_KeyAndChildCount(BPlusTree tree)
    {
        foreach (BPlusTreeNode n in tree.root.children)
            CheckBPlusTreeValidity1_KeyAndChildCountInternal(tree, n);
    }

    private static void CheckBPlusTreeValidity1_KeyAndChildCountInternal(BPlusTree tree, BPlusTreeNode n)
    {
        if (n == null)
            return;

        Check(tree.t - 1 <= n.keys.Count && n.keys.Count <= 2 * tree.t - 1);

        if (n.children.Count != 0)
            Check(n.keys.Count + 1 == n.children.Count);
    }

    private static int CheckBPlusTreeValidity2_leafDepthInternal(BPlusTreeNode n, int prevLeafDepth, int FirstLeafDepth)
    {
        if (n.IsLeaf())
        {
            if (FirstLeafDepth != -1)
                Check(prevLeafDepth + 1 == FirstLeafDepth);

            return prevLeafDepth + 1;
        }
        else
        {
            foreach (BPlusTreeNode n2 in n.children)
                FirstLeafDepth = CheckBPlusTreeValidity2_leafDepthInternal(n2, prevLeafDepth + 1, FirstLeafDepth);

            return FirstLeafDepth;
        }

    }

    private static void CheckBPlusTreeValidity2_leafDepth(BPlusTree tree)
    {
        CheckBPlusTreeValidity2_leafDepthInternal(tree.root, 0, -1);
    }

    private static IBPlusTreeData CheckBPlusTreeValidity3_CheckOrderInternal(BPlusTreeNode node, IBPlusTreeData prevValue)
    {
        for (int i = 0; i < node.keys.Count; i++)
        {
            if (node.IsInternal())
                prevValue = CheckBPlusTreeValidity3_CheckOrderInternal(node.children[i], prevValue);

            Check(node.keys[i].GetKey().CompareTo(prevValue.GetKey()) >= 0);
            prevValue = node.keys[i];
        }

        return prevValue;
    }

    private static void CheckBPlusTreeValidity3_CheckOrder(BPlusTree tree)
    {
        CheckBPlusTreeValidity3_CheckOrderInternal(tree.root, new CustomClass3(-1));
    }

    public static void Ut()
    {
        TestBPlusTreeInsert();
        TestBPlusTreeFind();
    }

}
