using System.Diagnostics;

public class CustomClass2 : IBTreeValue, IComparable<CustomClass2>
{
    public int value = 0;

    public CustomClass2()
    {

    }

    public CustomClass2(int value)
    {
        this.value = value;
    }

    public IComparable GetKey()
    {
        return value;
    }

    public string ToString()
    {
        return "" + value;
    }

    public int CompareTo(CustomClass2? other)
    {
        if (other == null)
            return -1;
        return value.CompareTo(other.value);
    }
}

public class BTreeUt
{
    private static void Check(bool b)
    {
        Trace.Assert(b);
    }

    private static void TestBTreeInsert()
    {
        BTree<CustomClass2> tree = new BTree<CustomClass2>(2);
        for (int i = 30; i >= 1; i--)
            tree.Insert(new CustomClass2(i));

        CheckBTreeValidity(tree);
        Check(tree.KeyCount() == 30);

        tree = new BTree<CustomClass2>(3);
        for (int i = 100; i >= 1; i--)
        {
            tree.Insert(new CustomClass2(i));
            tree.Insert(new CustomClass2(i));
            tree.Insert(new CustomClass2(i));
        }

        CheckBTreeValidity(tree);
        Check(tree.KeyCount() == 300);

    }

    private static void TestBTreeFind()
    {
        BTree<CustomClass2> tree = new BTree<CustomClass2>(2);

        for (int i = 30; i >= 1; i--)
            tree.Insert(new CustomClass2(i));

        for (int i = 0; i < 10; i++)
        {
            tree.Insert(new CustomClass2(20));
        }

        Check(tree.Find(new CustomClass2(30)).Count == 1);
        Check(tree.Find(new CustomClass2(20)).Count == 11);
        Check(tree.Find(new CustomClass2(31)).Count == 0);
    }

    private static void TestBTreeDelete()
    {
        BTree<CustomClass2> tree = new BTree<CustomClass2>(2);

        for (int i = 0; i < 20; i++)
            tree.Insert(new CustomClass2(i));

        for (int i = -1; i < 21; i++)
        {
            tree.Delete(new CustomClass2(i));
            CheckBTreeValidity(tree);
        }

        for (int i = 0; i < 20; i++)
            tree.Insert(new CustomClass2(i));
        CheckBTreeValidity(tree);

        for (int i = 21; i >= -1; i--)
        {
            tree.Delete(new CustomClass2(i));
            CheckBTreeValidity(tree);
        }

        for (int seed = 0; seed < 500; seed++)
        {
            tree = new BTree<CustomClass2>(3);

            List<int> keys = new List<int>();
            for (int i = 0; i < 500; i++)
            {
                tree.Insert(new CustomClass2(i));
                tree.Insert(new CustomClass2(i));
                keys.Add(i);
            }

            Random rand = new Random(seed * 1000);
            while (tree.root != null)
            {
                int index = rand.Next() % keys.Count;
                int key = keys[index];
                keys.RemoveAt(index);
                tree.Delete(new CustomClass2(key));
            }
        }
    }

    private static void CheckBTreeValidity1_KeyAndChildCount(BTree<CustomClass2> tree)
    {
        CheckBTreeValidity1_KeyAndChildCountInternal(tree, tree.root);
    }

    private static void CheckBTreeValidity1_KeyAndChildCountInternal(BTree<CustomClass2> tree, BTreeNode<CustomClass2> n)
    {
        if (n == null)
            return;

        if (n != tree.root)
            Check(tree.t - 1 <= n.keys.Count && n.keys.Count <= 2 * tree.t - 1);

        if (n.children.Count != 0)
            Check(n.keys.Count + 1 == n.children.Count);

        foreach (BTreeNode<CustomClass2> child in n.children)
            CheckBTreeValidity1_KeyAndChildCountInternal(tree, child);
    }

    private static void CheckBTreeValidity2_leafDepthInternal(BTreeNode<CustomClass2> n, int prevLeafDepth, int FirstLeafDepth)
    {
        if (n.IsLeaf())
            Check(prevLeafDepth == FirstLeafDepth);
        else
        {
            foreach (BTreeNode<CustomClass2> child in n.children)
                CheckBTreeValidity2_leafDepthInternal(child, prevLeafDepth + 1, FirstLeafDepth);
        }
    }

    private static void CheckBTreeValidity2_leafDepth(BTree<CustomClass2> tree)
    {
        if (tree.root == null)
            return;

        BTreeNode<CustomClass2> firstChild = tree.root;
        int depth = 0;
        while (firstChild.children.Count != 0)
        {
            firstChild = firstChild.children[0];
            depth++;
        }

        CheckBTreeValidity2_leafDepthInternal(tree.root, 0, depth);
    }

    private static CustomClass2 CheckBTreeValidity3_CheckOrderInternal(BTreeNode<CustomClass2> node, CustomClass2 prevValue)
    {
        for (int i = 0; i < node.children.Count; i++)
        {
            if (node.IsInternal())
                prevValue = CheckBTreeValidity3_CheckOrderInternal(node.children[i], prevValue);

            if (i < node.keys.Count)
            {
                Check(node.keys[i].GetKey().CompareTo(prevValue.GetKey()) >= 0);
                prevValue = node.keys[i];
            }
        }

        return prevValue;
    }

    private static void CheckBTreeValidity3_CheckOrder(BTree<CustomClass2> tree)
    {
        CheckBTreeValidity3_CheckOrderInternal(tree.root, new CustomClass2(-1));
    }

    private static void CheckBTreeValidity(BTree<CustomClass2> tree)
    {
        if (tree.root == null)
            return;

        CheckBTreeValidity1_KeyAndChildCount(tree);
        CheckBTreeValidity2_leafDepth(tree);
        CheckBTreeValidity3_CheckOrder(tree);
    }

    public static void Ut()
    {
        TestBTreeInsert();
        TestBTreeFind();
        TestBTreeDelete();
    }
}
