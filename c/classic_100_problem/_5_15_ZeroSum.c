#include "Util.h"

void _5_15_ZeroSum() {
    int a[] = {1, -99, 2, 3, -5, 4};
    int count = sizeof(a) / sizeof(int);
    int prefixSum[6] = {NULL};

    int end = 0;
    for (int i = 0; i < count && !end; i++) {
        int value = a[i];
        for (int j = 0; j < i && !end; j++) {
            prefixSum[j] += value;
            if (prefixSum[j] == 0) {
                for (int z =j ; z <= i; z++) {
                    if (z != j)
                        printf(", ");
                    printf("%d", a[z]);
                }
                printf("\n");
                end = 1;
            }
        }
        prefixSum[i] = value;
    }
}