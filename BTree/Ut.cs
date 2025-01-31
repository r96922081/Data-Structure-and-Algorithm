using System.Diagnostics;



public class CustomClass2 : IBTreeValue
{
    public int value = 0;

    public CustomClass2()
    {

    }

    public CustomClass2(int value)
    {
        this.value = value;
    }

    public int CompareTo(IBTreeValue? other)
    {
        if (other == null)
            return 0;

        if (value < ((CustomClass2)other).value)
            return -1;
        else if (value == ((CustomClass2)other).value)
            return 0;
        else
            return 1;
    }

    public void Save(BinaryWriter bw)
    {

    }

    public IBTreeValue Load(BinaryReader br)
    {
        return null;
    }

    public string ToString()
    {
        return "" + value;
    }
}

public class Ut
{
    private static void Check(bool b)
    {
        Trace.Assert(b);
    }

    private static void TestInsert()
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

    private static void TestFind()
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

    private static void TestDelete()
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

        for (int seed = 0; seed < 1000; seed++)
        {
            tree = new BTree<CustomClass2>(3);

            List<int> keys = new List<int>();
            for (int i = 0; i < 1000; i++)
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

    private static void CheckBTreeValidity1_KeyAndChildCountInternal(BTree<CustomClass2> tree, BTreeNode<CustomClass2> n)
    {
        if (n == null)
            return;

        Check(tree.t - 1 <= n.keys.Count && n.keys.Count <= 2 * tree.t - 1);

        if (n.children.Count != 0)
            Check(n.keys.Count + 1 == n.children.Count);
    }

    private static void CheckBTreeValidity1_KeyAndChildCount(BTree<CustomClass2> tree)
    {
        foreach (BTreeNode<CustomClass2> n in tree.root.children)
            CheckBTreeValidity1_KeyAndChildCountInternal(tree, n);
    }

    private static int CheckBTreeValidity2_leafDepthInternal(BTreeNode<CustomClass2> n, int prevLeafDepth, int FirstLeafDepth)
    {
        if (n.IsLeaf())
        {
            if (FirstLeafDepth != -1)
                Check(prevLeafDepth + 1 == FirstLeafDepth);

            return prevLeafDepth + 1;
        }
        else
        {
            foreach (BTreeNode<CustomClass2> n2 in n.children)
                FirstLeafDepth = CheckBTreeValidity2_leafDepthInternal(n2, prevLeafDepth + 1, FirstLeafDepth);

            return FirstLeafDepth;
        }

    }

    private static void CheckBTreeValidity2_leafDepth(BTree<CustomClass2> tree)
    {
        CheckBTreeValidity2_leafDepthInternal(tree.root, 0, -1);
    }

    private static CustomClass2 CheckBTreeValidity3_CheckOrderInternal(BTreeNode<CustomClass2> node, CustomClass2 prevValue)
    {
        for (int i = 0; i < node.keys.Count; i++)
        {
            if (node.IsInternal())
                prevValue = CheckBTreeValidity3_CheckOrderInternal(node.children[i], prevValue);

            Check(node.keys[i].CompareTo(prevValue) >= 0);
            prevValue = node.keys[i];
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

    public class SaveLoadTest : IBTreeValue
    {
        public int intValue = 0;
        public string strValue = "";

        public SaveLoadTest()
        {

        }

        public SaveLoadTest(int intValue, string strValue)
        {
            this.intValue = intValue;
            this.strValue = strValue;
        }

        public int CompareTo(IBTreeValue? other)
        {
            if (other == null)
                return 0;

            if (intValue < ((SaveLoadTest)other).intValue)
                return -1;
            else if (intValue == ((SaveLoadTest)other).intValue)
                return strValue.CompareTo(((SaveLoadTest)other).strValue);
            else
                return 1;
        }

        public void Save(BinaryWriter bw)
        {
            bw.Write(intValue);
            bw.Write(strValue);
        }

        public IBTreeValue Load(BinaryReader br)
        {
            SaveLoadTest ret = new SaveLoadTest();
            ret.intValue = br.ReadInt32();
            ret.strValue = br.ReadString();

            return ret;
        }

        public string ToString()
        {
            return "" + intValue +"(" + strValue + ")";
        }
    }

    private static void TestSave()
    {
        BTree<SaveLoadTest> tree = new BTree<SaveLoadTest>(2);

        for (int i = 100; i >= 1; i--)
            tree.Insert(new SaveLoadTest(i, ((char)('A' + i)).ToString()));

        Console.WriteLine(tree.ToString());

        using (BinaryWriter bw = new BinaryWriter(File.Open("../../../SaveLoadUt.bt", FileMode.Create)))
        {
            tree.Save(bw);
        }

        BTree<SaveLoadTest> loadedTree;
        using (BinaryReader br = new BinaryReader(File.Open("../../../SaveLoadUt.bt", FileMode.Open)))
        {
            loadedTree = BTree<SaveLoadTest>.Load(br, new SaveLoadTest());
        }

        Check(tree.ToString() == loadedTree.ToString());

    }

    public static void Test()
    {
        TestInsert();
        TestFind();
        TestDelete();
        TestSave();
    }
}
