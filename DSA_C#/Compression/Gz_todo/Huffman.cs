using System.Text;

public class HuffmanEncoding
{
    public class MinHeap
    {
        private List<HuffmanNode> heap = new List<HuffmanNode>();

        public int GetSize()
        {
            return heap.Count;
        }

        public void Add(HuffmanNode node)
        {
            heap.Add(node);
            HeapifyUp(heap.Count - 1);
        }

        public HuffmanNode Remove()
        {
            HuffmanNode root = heap[0];
            heap[0] = heap[heap.Count - 1];
            heap.RemoveAt(heap.Count - 1);
            HeapifyDown(0);
            return root;
        }

        private void HeapifyUp(int index)
        {
            int parentIndex = (index - 1) / 2;

            while (index > 0 && heap[index].count < heap[parentIndex].count)
            {
                Swap(index, parentIndex);
                index = parentIndex;
                parentIndex = (index - 1) / 2;
            }
        }

        private void HeapifyDown(int index)
        {
            int smallest = index;
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;

            if (leftChild < heap.Count && heap[leftChild].count < heap[smallest].count)
                smallest = leftChild;

            if (rightChild < heap.Count && heap[rightChild].count < heap[smallest].count)
                smallest = rightChild;

            if (smallest != index)
            {
                Swap(index, smallest);
                HeapifyDown(smallest);
            }
        }

        private void Swap(int i, int j)
        {
            HuffmanNode temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
        }
    }

    public class HuffmanNode
    {
        public int bit = 0;
        public string s = "";
        public HuffmanNode left = null;
        public HuffmanNode right = null;
        public int count = 0;

    }

    public static HuffmanNode BuildHuffmanTree(string input)
    {
        List<string> stringList = new List<string>();
        foreach (char c in input)
            stringList.Add(c.ToString());

        Dictionary<string, HuffmanNode> stringCount = new Dictionary<string, HuffmanNode>();
        List<HuffmanNode> nodes = new List<HuffmanNode>();

        foreach (string s in stringList)
        {
            if (stringCount.ContainsKey(s))
                stringCount[s].count++;
            else
            {
                HuffmanNode n = new HuffmanNode();
                n.s = s;
                n.count = 1;
                stringCount.Add(s, n);
                nodes.Add(n);
            }
        }

        return BuildHuffmanTreeInternal(nodes);
    }

    public static HuffmanNode BuildHuffmanTreeInternal(List<HuffmanNode> nodes)
    {
        MinHeap h = new MinHeap();
        foreach (HuffmanNode n in nodes)
            h.Add(n);

        while (true)
        {
            if (h.GetSize() == 1)
                break;

            HuffmanNode n1 = h.Remove();
            HuffmanNode n2 = h.Remove();

            HuffmanNode newNode = new HuffmanNode();
            newNode.count = n1.count + n2.count;
            newNode.left = n1;
            newNode.right = n2;
            n1.bit = 0;
            n2.bit = 1;

            h.Add(newNode);
        }

        HuffmanNode root = h.Remove();

        return root;
    }

    public static void Traverse(Dictionary<string, string> map, HuffmanNode n, string prefix)
    {
        if (n == null)
            return;

        if (n.s != "")
        {
            map.Add(n.s, prefix);
            return;
        }

        Traverse(map, n.left, prefix + "0");
        Traverse(map, n.right, prefix + "1");
    }

    public static Dictionary<string, string> GetEncodeBit(HuffmanNode root)
    {
        Dictionary<string, string> map = new Dictionary<string, string>();
        Traverse(map, root, "");

        return map;
    }

    public static string Encode(Dictionary<string, string> map, string input)
    {
        System.Text.StringBuilder sb = new System.Text.StringBuilder();
        foreach (char c in input)
            sb.Append(map["" + c]);

        return sb.ToString();
    }

    public static List<byte> ConvertStringToByte(string binaryString)
    {
        while (binaryString.Length % 8 != 0)
            binaryString += "0";

        List<byte> bytes = new List<byte>();

        for (int i = 0; i < binaryString.Length; i += 8)
            bytes.Add(Convert.ToByte(binaryString.Substring(i, 8), 2));

        return bytes;
    }

    public static Tuple<List<byte>, int> Encode(string input, Dictionary<string, string> encodeBits)
    {
        // for easy of development, convert to string first, then convert to byte
        string encoded = Encode(encodeBits, input);
        List<byte> encodedBytes = ConvertStringToByte(encoded);

        return Tuple.Create(encodedBytes, encoded.Length);
    }

    public static string Decode(List<byte> encodedBytes, int encodedLength, HuffmanNode root)
    {
        string result = "";
        foreach (byte b in encodedBytes)
            result += Convert.ToString(b, 2).PadLeft(8, '0');

        StringBuilder output = new StringBuilder();
        HuffmanNode n = root;

        for (int i = 0; i < encodedLength; i++)
        {
            if (result[i] == '0')
                n = n.left;
            else
                n = n.right;

            if (n.s != "")
            {
                output.Append(n.s);
                n = root;
            }
        }

        return output.ToString();
    }

    public static string GetRandomString(int length)
    {
        Random random = new Random();
        string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return new string(Enumerable.Repeat(chars, length).Select(s => s[random.Next(s.Length)]).ToArray());
    }

    public static void TestCompression(string input)
    {
        HuffmanNode root = BuildHuffmanTree(input);
        Dictionary<string, string> encodeBits = GetEncodeBit(root);

        Tuple<List<byte>, int> ret = Encode(input, encodeBits);
        List<byte> encodedBytes = ret.Item1;
        int encodedLength = ret.Item2;

        string decodedString = Decode(encodedBytes, encodedLength, root);

        if (input != decodedString)
            throw new Exception("Test failed");

        /*
        Console.WriteLine("original input = " + input);
        Console.WriteLine("");

        Console.Write("encoded bytes = ");
        Console.WriteLine(BitConverter.ToString(encodedBytes.ToArray()));
        Console.WriteLine("");

        Console.WriteLine("decoded output = " + decodedString);
        Console.WriteLine("");*/

        Console.WriteLine("original byte count = " + input.Length + ", encoded byte count = " + encodedBytes.Count);
        Console.WriteLine("Compression Rate = " + ((double)encodedBytes.Count / (double)input.Length));
    }

    public static void Main2(string[] args)
    {
        string input = GetRandomString(200);

        TestCompression(input);

        string aliceAdventure = File.ReadAllText("alice29.txt");

        TestCompression(aliceAdventure);
    }
}