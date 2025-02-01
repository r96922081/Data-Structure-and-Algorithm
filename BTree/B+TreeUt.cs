using System.Diagnostics;

public class CustomClass3 : IBPlusTreeValue
{
    public int value = 0;

    public CustomClass3()
    {

    }

    public CustomClass3(int value)
    {
        this.value = value;
    }

    public IComparable GetKey()
    {
        return value;
    }

    public object GetData()
    {
        return value;
    }

    public int CompareTo(IBPlusTreeValue? other)
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

    public string ToString()
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



    private static void TestBPlusTreeInsert()
    {
        BPlusTree tree = new BPlusTree(2);
        for (int i = 4; i >= 1; i--)
            tree.Insert(new CustomClass3(i));

        Console.Write(tree);

        /*
        CheckBTreeValidity(tree);
        Check(tree.KeyCount() == 30);
        

        tree = new BPlusTree<CustomClass3>(3);
        for (int i = 100; i >= 1; i--)
        {
            tree.Insert(new CustomClass3(i));
            tree.Insert(new CustomClass3(i));
            tree.Insert(new CustomClass3(i));
        }

        //CheckBTreeValidity(tree);
        Check(tree.KeyCount() == 300);*/

    }

    public static void Ut()
    {
        TestBPlusTreeInsert();
    }

}
