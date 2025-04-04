using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class Lz77CompressionUt
{
    private static void Check(bool b)
    {
        if (!b)
            throw new Exception();
    }

    public static void Ut()
    {
        string input = File.ReadAllText("../../../Ut/UtFiles/alice29.txt");

        List<Lz77Compression.Lz77Output> encoded = Lz77Compression.Lz77Encode(input);
        string decompressed = Lz77Compression.Lz77Decode(encoded);
        if (input != decompressed)
            throw new Exception("Decompressed string is not equal to original string");

        int encodedSize = encoded.Count * 4;
        Console.WriteLine("lz77 original byte count = " + input.Length + ", encoded byte count = " + encodedSize);
        Console.WriteLine("lz77 compression Rate = " + ((double)encodedSize / (double)input.Length));
    }
}