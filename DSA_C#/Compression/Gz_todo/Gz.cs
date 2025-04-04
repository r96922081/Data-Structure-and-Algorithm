using static HuffmanEncoding;
using static Lz77;

public class Gz
{
    public static string Encode(Dictionary<string, string> map, List<string> gzEncode)
    {
        System.Text.StringBuilder sb = new System.Text.StringBuilder();
        foreach (string s in gzEncode)
            sb.Append(map[s]);

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

    public static Tuple<List<byte>, int> Encode(List<string> gzEncode, Dictionary<string, string> encodeBits)
    {
        // for easy of development, convert to string first, then convert to byte
        string encoded = Encode(encodeBits, gzEncode);
        List<byte> encodedBytes = ConvertStringToByte(encoded);

        return Tuple.Create(encodedBytes, encoded.Length);
    }

    public static void Main(string[] args)
    {
        string input = File.ReadAllText("alice29.txt");

        List<Lz77Output> lz77OutputList = Lz77Encode(input);

        Dictionary<string, HuffmanNode> stringCount = new Dictionary<string, HuffmanNode>();
        List<HuffmanNode> nodes = new List<HuffmanNode>();

        // "a"
        // "2,3
        List<string> gzEncode = new List<string>();

        foreach (Lz77Output lz77Output in lz77OutputList)
        {
            string key = "";
            if (lz77Output.length == 0)
                key = "" + lz77Output.nextChar;
            else
                key = lz77Output.offset + "," + lz77Output.length;

            gzEncode.Add(key);

            if (stringCount.ContainsKey(key))
                stringCount[key].count++;
            else
            {
                HuffmanNode n = new HuffmanNode();
                n.s = key;
                n.count = 1;
                stringCount.Add(key, n);
                nodes.Add(n);
            }
        }

        HuffmanNode root = BuildHuffmanTreeInternal(nodes);
        Dictionary<string, string> encodeBits = GetEncodeBit(root);

        Tuple<List<byte>, int> ret = Encode(gzEncode, encodeBits);
        List<byte> encodedBytes = ret.Item1;
        int encodedLength = ret.Item2;

        //string decodedString = Decode(encodedBytes, encodedLength, root);

    }
}

