public class MinPriorityQueueUT
{
    private static void Check(bool b)
    {
        if (!b)
            throw new Exception();
    }

    private enum Order
    {
        Ascending,
        Descending,
        Random
    }

    private static void Ut1Internal(Order order, int count)
    {
        MinPriorityQueue<int> q = new MinPriorityQueue<int>();

        if (order == Order.Ascending)
        {
            for (int i = 0; i < count; i++)
                q.Insert(i);

            for (int i = 0; i < count; i++)
                Check(q.ExtractMin() == i);
        }
        else if (order == Order.Descending)
        {
            for (int i = count - 1; i >= 0; i--)
                q.Insert(i);

            for (int i = 0; i < count; i++)
                Check(q.ExtractMin() == i);
        }
        else if (order == Order.Random)
        {
            for (int randomSeed = 0; randomSeed < 1000 * 100; randomSeed += 1000)
            {
                List<int> values = new List<int>();
                for (int i = 0; i < count; i++)
                    values.Add(i);
                Random random = new Random(randomSeed);

                while (values.Count > 0)
                {
                    int valueIndex = random.Next() % values.Count;
                    q.Insert(values[valueIndex]);
                    values.RemoveAt(valueIndex);
                }

                for (int i = 0; i < count; i++)
                    Check(q.ExtractMin() == i);
            }
        }
    }

    private static void Ut1()
    {
        Ut1Internal(Order.Ascending, 100);
        Ut1Internal(Order.Descending, 100);
        Ut1Internal(Order.Random, 100);
    }

    private class MyKey : IComparable<MyKey>
    {
        public int id = -1;

        public MyKey(int id)
        {
            this.id = id;
        }

        public override bool Equals(object obj)
        {
            return ReferenceEquals(this, obj);
        }

        public override int GetHashCode()
        {
            return System.Runtime.CompilerServices.RuntimeHelpers.GetHashCode(this);
        }

        public int CompareTo(MyKey? other)
        {
            if (other == null)
                return -1;
            return id.CompareTo(other.id);
        }
    }

    private static void Ut2DecreaseKey()
    {
        MinPriorityQueue<MyKey> q = new MinPriorityQueue<MyKey>();

        List<MyKey> keys = new List<MyKey>();

        for (int i = 0; i < 100; i++)
        {
            MyKey key = new MyKey(i);
            keys.Add(key);
            q.Insert(key);
        }

        for (int i = 50; i < 100; i++)
        {
            keys[i].id -= 1000;
            q.DecreaseKey(keys[i]);
        }

        for (int i = 0; i < 50; i++)
            Check(q.ExtractMin().id == 50 + i - 1000);

        for (int i = 0; i < 50; i++)
            Check(q.ExtractMin().id == i);
    }

    private static void Ut2IncreaseKey()
    {
        MinPriorityQueue<MyKey> q = new MinPriorityQueue<MyKey>();

        List<MyKey> keys = new List<MyKey>();

        for (int i = 0; i < 100; i++)
        {
            MyKey key = new MyKey(i);
            keys.Add(key);
            q.Insert(key);
        }

        for (int i = 0; i < 50; i++)
        {
            keys[i].id += 1000;
            q.IncreaseKey(keys[i]);
        }

        for (int i = 0; i < 50; i++)
            Check(q.ExtractMin().id == 50 + i);

        for (int i = 0; i < 50; i++)
            Check(q.ExtractMin().id == 1000 + i);
    }

    private static void Ut2()
    {
        Ut2DecreaseKey();
        Ut2IncreaseKey();
    }

    public static void Ut()
    {
        Ut1();
        Ut2();
    }
}

