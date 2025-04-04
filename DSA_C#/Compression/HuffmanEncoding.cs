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
        public char c = '\0';
        public HuffmanNode left = null;
        public HuffmanNode right = null;
        public int count = 0;

    }

    public static HuffmanNode BuildHuffmanTree(string input)
    {
        Dictionary<char, HuffmanNode> charCount = new Dictionary<char, HuffmanNode>();
        List<HuffmanNode> nodes = new List<HuffmanNode>();

        foreach (char c in input)
        {
            if (charCount.ContainsKey(c))
                charCount[c].count++;
            else
            {
                HuffmanNode n = new HuffmanNode();
                n.c = c;
                n.count = 1;
                charCount.Add(c, n);
                nodes.Add(n);
            }
        }

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

    public static void Traverse(Dictionary<char, string> map, HuffmanNode n, string prefix)
    {
        if (n == null)
            return;

        if (n.c != '\0')
        {
            map.Add(n.c, prefix);
            return;
        }

        Traverse(map, n.left, prefix + "0");
        Traverse(map, n.right, prefix + "1");
    }

    public static Dictionary<char, string> GetEncodeBit(HuffmanNode root)
    {
        Dictionary<char, string> map = new Dictionary<char, string>();
        Traverse(map, root, "");

        return map;
    }

    public static string Encode(Dictionary<char, string> map, string input)
    {
        System.Text.StringBuilder sb = new System.Text.StringBuilder();
        foreach (char c in input)
            sb.Append(map[c]);

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

    public static Tuple<List<byte>, int> Encode(string input, Dictionary<char, string> encodeBits)
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

            if (n.c != '\0')
            {
                output.Append(n.c);
                n = root;
            }
        }

        return output.ToString();
    }
}