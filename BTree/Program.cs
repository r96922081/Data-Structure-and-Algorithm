public class CustomClass : IBTreeValue
{
    public int value = 0;

    public CustomClass()
    {

    }

    public CustomClass(int value)
    {
        this.value = value;
    }

    public int CompareTo(IBTreeValue? other)
    {
        if (other == null)
            return 0;

        if (value < ((CustomClass)other).value)
            return -1;
        else if (value == ((CustomClass)other).value)
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

public class Program
{
    public static void Main(string[] args)
    {
        MainUt.Ut();

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
