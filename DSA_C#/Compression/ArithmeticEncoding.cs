using System;
using System.Collections.Generic;

public class ArithmeticEncoding
{
    public static string reachLimit = "Reach precision limit";

    public class Range
    {
        public char symbol;
        public double lowBound;
        public double highBound;

        public Range(char symbol, double lowBound, double highBound)
        {
            this.symbol = symbol;
            this.lowBound = lowBound;
            this.highBound = highBound;
        }
    }

    public static double Encode(Dictionary<char, Range> ranges, string message)
    {
        double low = 0.0, high = 1.0;

        for (int i = 0; i < message.Length; i++)
        {
            double range = high - low;
            char c = message[i];
            Range f = ranges[c];
            high = low + range * f.highBound;
            low = low + range * f.lowBound;

            //Console.WriteLine("Round {0}, char = {1}: {2} - {3}", i, c, low, high);
        }

        return (low + high) / 2;
    }

    public static string Decode(Dictionary<char, Range> frequencies, double encodedValue, int messageLength)
    {
        string decodedMessage = "";
        double low = 0.0, high = 1.0;

        for (int i = 0; i < messageLength; i++)
        {
            double range = high - low;
            double value = (encodedValue - low) / range;
            bool ok = false;
            foreach (var entry in frequencies)
            {
                Range f = entry.Value;
                if (value >= f.lowBound && value < f.highBound)
                {
                    decodedMessage += f.symbol;
                    high = low + range * f.highBound;
                    low = low + range * f.lowBound;
                    ok = true;
                    break;
                }
            }

            if (!ok)
                return reachLimit;

            //Console.WriteLine("Round {0}, value = {1}: {2} - {3}, symbol = {4}", i, value, low, high, decodedMessage[i]);
        }

        return decodedMessage;
    }

    public static Dictionary<char, Range> getRanges(string input)
    {
        Dictionary<char, Range> ranges = new Dictionary<char, Range>();

        Dictionary<char, int> charCount = new Dictionary<char, int>();
        foreach (char c in input)
        {
            if (charCount.ContainsKey(c))
                charCount[c]++;
            else
                charCount.Add(c, 1);
        }

        Dictionary<char, double> probability = new Dictionary<char, double>();
        foreach (char c in charCount.Keys)
        {
            probability.Add(c, (double)charCount[c] / (double)input.Length);
        }

        double prev = 0d;
        foreach (char c in charCount.Keys)
        {
            ranges.Add(c, new Range(c, prev, prev + probability[c]));
            prev += probability[c];
        }

        return ranges;
    }
}
