public class ArithmeticEncodingUt
{
    private static void Check(bool b)
    {
        if (!b)
            throw new Exception();
    }

    private static string GetRandomString(int length)
    {
        Random random = new Random();
        string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return new string(Enumerable.Repeat(chars, length).Select(s => s[random.Next(s.Length)]).ToArray());
    }

    public static void Ut()
    {
        for (int inputLength = 1; inputLength < 30; inputLength++)
        {
            string input = GetRandomString(inputLength);

            Console.WriteLine("input = " + input + ", length = " + inputLength);

            Dictionary<char, ArithmeticEncoding.Range> ranges = ArithmeticEncoding.getRanges(input);
            double result = ArithmeticEncoding.Encode(ranges, input);
            string decoded = ArithmeticEncoding.Decode(ranges, result, inputLength);

            if (decoded == ArithmeticEncoding.reachLimit)
            {
                Console.WriteLine(ArithmeticEncoding.reachLimit + "\n");
                continue;
            }


            int diffCount = 0;
            for (int i = 0; i < input.Length; i++)
            {
                if (input[i] != decoded[i])
                    diffCount++;
            }

            if (diffCount == 0)
                Console.WriteLine("Decoded without losing data\n");
            else
                Console.WriteLine("Decoded, but diffCount = {0}, Decoded message: {1}\n", decoded, diffCount);
        }
    }
}



