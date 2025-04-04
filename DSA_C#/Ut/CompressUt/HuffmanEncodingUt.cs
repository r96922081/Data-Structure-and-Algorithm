using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static HuffmanEncoding;

public class HuffmanEncodingUt
{
    private static void Check(bool b)
    {
        if (!b)
            throw new Exception();
    }

    public static void TestCompression(string input)
    {
        HuffmanNode root = BuildHuffmanTree(input);
        Dictionary<char, string> encodeBits = GetEncodeBit(root);

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

    public static void Ut()
    {
        string aliceAdventure = File.ReadAllText("../../../Ut/UtFiles/alice29.txt");

        TestCompression(aliceAdventure);
    }
}

