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

    private enum DeleteOrder
    {
        Ascending,
        Descending,
        Random
    }

    private static void DeleteInternal(int t, int dataCount, DeleteOrder order)
    {
        BPlusTree tree = new BPlusTree(t);
        for (int i = 0; i < dataCount; i++)
            tree.Insert(new CustomClass3(i));

        Console.WriteLine(tree);

        if (order == DeleteOrder.Ascending)
        {
            for (int i = 0; i < dataCount; i++)
            {
                int count = tree.Delete(i);
                Check(count == 1);
                CheckBPlusTreeValidity(tree, dataCount - i - 1);
            }
        }
        else if (order == DeleteOrder.Descending)
        {
            for (int i = dataCount - 1; i >= 0; i--)
            {
                int count = tree.Delete(i);
                Console.WriteLine(tree);
                Check(count == 1);
                CheckBPlusTreeValidity(tree, i);
            }
        }
        else if (order == DeleteOrder.Random)
        {
            List<int> values = new List<int>();
            for (int i = 0; i < dataCount; i++)
                values.Add(i);
            Random random = new Random(0);

            int tempDataCount = dataCount;

            while (values.Count > 0)
            {
                int valueIndex = random.Next() % values.Count;
                int count = tree.Delete(values[valueIndex]);
                tempDataCount--;
                Check(count == 1);
                values.RemoveAt(valueIndex);
                CheckBPlusTreeValidity(tree, tempDataCount);
            }
        }

        Check(tree.root == null);
    }

    private static void TestBPlusTreeDelete()
    {
        DeleteInternal(2, 1, DeleteOrder.Ascending);
        DeleteInternal(2, 4, DeleteOrder.Ascending);
        DeleteInternal(2, 5, DeleteOrder.Ascending);
        DeleteInternal(2, 100, DeleteOrder.Ascending);

        DeleteInternal(2, 1, DeleteOrder.Descending);
        DeleteInternal(2, 4, DeleteOrder.Descending);
        DeleteInternal(2, 5, DeleteOrder.Descending);
        DeleteInternal(2, 100, DeleteOrder.Descending);
    }

    private static void TestBPlusTreeInsert()
    {
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

        CheckBPlusTreeValidity(tree, 200);
    }

    private static void CheckBPlusTreeValidity(BPlusTree tree, int dataCount)
    {
        if (tree.root == null)
            return;

        CheckBPlusTreeValidity1_KeyAndChildCount(tree);
        CheckBPlusTreeValidity2_leafDepth(tree);
        CheckBPlusTreeValidity3_CheckOrder(tree);
        CheckBPlusTreeValidity4_CheckLink(tree, dataCount);
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

        if (n != tree.root)
            Check(tree.t - 1 <= n.keys.Count && n.keys.Count <= 2 * tree.t - 1);

        if (n.children.Count != 0)
            Check(n.keys.Count + 1 == n.children.Count);

        foreach (BPlusTreeNode child in n.children)
            CheckBPlusTreeValidity1_KeyAndChildCountInternal(tree, child);
    }

    private static void CheckBPlusTreeValidity2_leafDepthInternal(BPlusTreeNode n, int prevLeafDepth, int FirstLeafDepth)
    {
        if (n.IsLeaf())
            Check(prevLeafDepth == FirstLeafDepth);
        else
        {
            foreach (BPlusTreeNode child in n.children)
                CheckBPlusTreeValidity2_leafDepthInternal(child, prevLeafDepth + 1, FirstLeafDepth);
        }
    }

    private static void CheckBPlusTreeValidity2_leafDepth(BPlusTree tree)
    {
        if (tree.root == null)
            return;

        BPlusTreeNode firstChild = tree.root;
        int depth = 0;
        while (firstChild.children.Count != 0)
        {
            firstChild = firstChild.children[0];
            depth++;
        }

        CheckBPlusTreeValidity2_leafDepthInternal(tree.root, 0, depth);
    }

    private static IBPlusTreeData CheckBPlusTreeValidity3_CheckOrderInternal(BPlusTreeNode node, IBPlusTreeData prevValue)
    {
        for (int i = 0; i < node.children.Count; i++)
        {
            if (node.IsInternal())
                prevValue = CheckBPlusTreeValidity3_CheckOrderInternal(node.children[i], prevValue);

            if (i < node.keys.Count)
            {
                Check(node.keys[i].GetKey().CompareTo(prevValue.GetKey()) >= 0);
                prevValue = node.keys[i];
            }
        }

        return prevValue;
    }


    private static void CheckBPlusTreeValidity4_CheckLink(BPlusTree tree, int dataCount)
    {
        if (tree.root == null)
            return;

        BPlusTreeNode firstLeaf = tree.root;
        while (firstLeaf.children.Count != 0)
            firstLeaf = firstLeaf.children[0];

        IBPlusTreeData currentData = firstLeaf.keys[0];
        IBPlusTreeData prevData = null;

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

    private static void CheckBPlusTreeValidity3_CheckOrder(BPlusTree tree)
    {
        CheckBPlusTreeValidity3_CheckOrderInternal(tree.root, new CustomClass3(-1));
    }

    public static void Ut()
    {
        TestBPlusTreeInsert();
        TestBPlusTreeFind();
        TestBPlusTreeDelete();
    }

}
