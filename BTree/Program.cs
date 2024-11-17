public class CustomClass : IComparable<CustomClass>
{
    public int value = 0;

    public CustomClass()
    {

    }

    public CustomClass(int value)
    {
        this.value = value;
    }

    public int CompareTo(CustomClass? other)
    {
        if (other == null)
            return 0;

        if (value < other.value)
            return -1;
        else if (value == other.value)
            return 0;
        else
            return 1;
    }

    public override string ToString()
    {
        return "" + value;
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        //Ut.Test();



        BTree<CustomClass> tree = new BTree<CustomClass>(2);

        for (int i = 0; i < 28; i++)
        {
            tree.Insert(new CustomClass(i));
        }
        Console.WriteLine(tree);

        for (int i = 0; i < 20; i++)
            tree.Insert(new CustomClass(i));

        Console.WriteLine(tree);

        Console.WriteLine(tree.Find(new CustomClass(11)).Count);
        tree.Delete(new CustomClass(11));
        Console.WriteLine(tree.Find(new CustomClass(11)).Count);

        Console.WriteLine(tree);
    }
}
