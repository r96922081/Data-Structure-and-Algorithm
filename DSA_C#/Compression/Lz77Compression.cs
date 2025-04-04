using System.Text;

public class Lz77Compression
{
    public static int windowSize = 1024 * 32;
    public static int lookAheadBufferSize = 16;

    public class Lz77Output
    {
        public ushort offset;
        public byte length;
        public char nextChar;
    }

    private class LookAheadBuffer
    {
        string input = "";
        int lookAheadBufferCursor = 0;
        public StringBuilder buffer = new StringBuilder();

        public LookAheadBuffer(string input, int cursor)
        {
            this.input = input;
            lookAheadBufferCursor = cursor;
            buffer.Length = 0;
        }

        public void ReadNextLookAheadBuffer()
        {
            if (lookAheadBufferCursor >= input.Length)
                return;

            int length = lookAheadBufferCursor + lookAheadBufferSize < input.Length ?
                lookAheadBufferSize : input.Length - lookAheadBufferCursor;

            buffer.Append(input.Substring(lookAheadBufferCursor, length));

            lookAheadBufferCursor += length;
        }

        public bool IsEndOfInput()
        {
            return lookAheadBufferCursor >= input.Length;
        }
    }

    private static Lz77Output BruteForceFindMatch(string input, int cursor)
    {
        LookAheadBuffer lookAheadBuffer = new LookAheadBuffer(input, cursor);
        lookAheadBuffer.ReadNextLookAheadBuffer();

        Lz77Output match = null;

        for (int i = 1; i <= (windowSize < cursor ? windowSize : cursor); i++)
        {
            int length = 0;
            for (length = 0; length < 256; length++)
            {
                if (length >= lookAheadBuffer.buffer.Length)
                    if (lookAheadBuffer.IsEndOfInput())
                        break;
                    else
                        lookAheadBuffer.ReadNextLookAheadBuffer();

                if (input[cursor - i + length] != lookAheadBuffer.buffer[length])
                    break;
            }

            if (length != 0)
            {
                if (match == null || length > match.length)
                {
                    match = new Lz77Output();
                    match.offset = (ushort)i;
                    match.length = (byte)length;
                    match.nextChar = length < lookAheadBuffer.buffer.Length ? lookAheadBuffer.buffer[length] : '\0';
                }
            }
        }

        if (match == null)
        {
            match = new Lz77Output();
            match.offset = 0;
            match.length = 0;
            match.nextChar = lookAheadBuffer.buffer[0];
        }

        return match;
    }

    public static List<Lz77Output> Lz77Encode(string input)
    {
        List<Lz77Output> encodedResult = new List<Lz77Output>();

        int cursor = 0;
        while (cursor < input.Length)
        {
            Lz77Output match = BruteForceFindMatch(input, cursor);
            encodedResult.Add(match);
            cursor += match.length + 1;
        }

        return encodedResult;
    }

    public static string Lz77Decode(List<Lz77Output> encoded)
    {
        StringBuilder sb = new StringBuilder();

        foreach (Lz77Output match in encoded)
        {
            if (match.length == 0)
            {
                sb.Append(match.nextChar);
            }
            else
            {
                int start = sb.Length - match.offset;
                for (int i = 0; i < match.length; i++)
                {
                    sb.Append(sb[start + i]);
                }

                if (match.nextChar != '\0')
                    sb.Append(match.nextChar);
            }
        }

        return sb.ToString();
    }
}