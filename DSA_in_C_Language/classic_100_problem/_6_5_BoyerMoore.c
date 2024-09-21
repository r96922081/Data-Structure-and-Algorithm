#include "Util.h"

static int NaiveStringMatch(char* text, char* pattern) {
    int textLen = strlen(text);
    int patternLen = strlen(pattern);

    for (int i = 0; i <= textLen - patternLen; i++) {
        int j;
        for (j = 0; j < patternLen; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == patternLen) {
            return i;
        }
    }

    return -1;
}

static int BoyerMoore(char* text, char* pattern) {
    int jumpTable[256];

    int length = strlen(pattern);
    for (int i = 0; i < 256; i++) {
        int step = 1;
        for (; length - 1 - step >= 0; step++) {
            if (pattern[length - 1 - step] == (char)i) {
                break;
            }
        }
        jumpTable[i] = step;
    }

    int lastPatternIndex = strlen(pattern) - 1;

    while (lastPatternIndex < strlen(text)) {
        int i = 0;
        for (; i < length; i++) {
            if (text[lastPatternIndex - i] != pattern[length -1 -i]) {
                lastPatternIndex += jumpTable[text[lastPatternIndex]];
                break;
            }
        }

        if (i == length) {
            return lastPatternIndex - length + 1;
        }
    }
    return -1;
}

static void TestAlgorithm() {
    int diffCharSize = 3;
    int textSize = 5;    
    char* text = calloc(1, textSize + 1);
    char* pattern = calloc(1, textSize + 1);

    int count = 0;
    for (int value = 0; value < pow(diffCharSize, textSize); value++) {
        int temp_value = value;
        for (int i = 0; i < textSize; i++) {
            text[textSize - 1 - i] = 'a' + temp_value % 3;
            temp_value /= 3;
        }

        for (int patternSize = 1; patternSize <= textSize; patternSize++) {
            pattern[patternSize] = '\0';
            for (int value2 = 0; value2 < pow(diffCharSize, patternSize); value2++) {
                int temp_value2 = value2;
                for (int i = 0; i < patternSize; i++) {
                    pattern[patternSize - 1 - i] = 'a' + temp_value2 % 3;
                    temp_value2 /= 3;
                }
                check(NaiveStringMatch(text, pattern) == BoyerMoore(text, pattern));                
            }
        }
    }

    free(pattern);
    free(text);
}

int _6_5_BoyerMoore(char* s, char* key)
{
    check(BoyerMoore("acab", "ab") == 2);
    TestAlgorithm();
}