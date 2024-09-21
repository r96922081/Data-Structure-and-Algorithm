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

static int KMP(char* text, char* pattern) {
    int patternSize = strlen(pattern);

    // build prefixTable
    int* prefixTable = (int*)calloc(1, patternSize * sizeof(int));

    for (int i = patternSize - 1; i > 0; i--) {
        int ok = 1;
        int j = i - 1;
        int diff = i - j;
        for (;j >= 0; j--) {
            if (pattern[j] != pattern[j + diff]) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            prefixTable[i] = diff;
        } else {
            prefixTable[i] = i + 1;
        }
            
    }

    for (int i = 0; i < patternSize; i++)
        printf("%d\n", prefixTable[i]);


    free(prefixTable);
    
    return -1;
}

static void TestAlgorithm() {
    int diffCharSize = 3;
    int textSize = 5;    
    char* text = calloc(1, textSize + 1);
    char* pattern = calloc(1, textSize + 1);

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
                printf("text = %s  pattern = %s\n", text, pattern);
                check(NaiveStringMatch(text, pattern) == KMP(text, pattern));                
            }
        }
    }
    
    free(pattern);
    free(text);
}



void _6_4_KMP() {
    //TestAlgorithm();
    KMP("", "abaaba");
}