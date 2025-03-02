
// run current file by right click -> run ...
public class P1758 {
    static class Solution {
        public int minOperations(String s) {
            int countOfZeroHead = 0;
            int countofOneHead = 0;

            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (i % 2 == 0) {
                    if (c == '1')
                        countOfZeroHead++;
                    else if (c == '0')
                        countofOneHead++;
                } else {
                    if (c == '0')
                        countOfZeroHead++;
                    else if (c == '1')
                        countofOneHead++;
                }
            }

            return Math.min(countOfZeroHead, countofOneHead);
        }

        public static void check(boolean b) {
            if (!b)
                throw new Error("check failed!");
        }
        public static void main(String[] args) {
            check(new Solution().minOperations("0100") == 11);
            check(new Solution().minOperations("10") == 0);
            check(new Solution().minOperations("1111") == 2);
        }
    }
}
