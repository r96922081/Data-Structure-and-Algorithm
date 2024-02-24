#include "Util.h"
#include "time.h"

static int Pivot(int* a, int left, int right) {
    int originalLeft = left;
    int pivotValue = a[left];
    
    while (left <= right) {
        if (a[left] <= pivotValue) {
            left++;
        }
        if (pivotValue < a[right]) {
            right--;
        }

        if (left < right) {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
        }
    }

    a[originalLeft] = a[right];
    a[right] = pivotValue;

    return right;
}

static void QuickSort(int* a, int left, int right) {
    if (left >= right)
        return;

    int middle = Pivot(a, left, right);
    QuickSort(a, left, middle - 1);
    QuickSort(a, middle + 1, right);
}

void _5_3_QuickSort() {
    srand(time(NULL));

    int count = 20;
    int *a = malloc(count * sizeof(int));


    for (int i = 0; i < count; i++) {
        a[i] = rand() % 100 + 1;
    }

    for (int i = 0; i < count; i++) {
        if (i != 0)
            printf(", ");
        printf("%d", a[i]);
    }
    printf("\n");

    QuickSort(a, 0, count - 1);

    for (int i = 0; i < count; i++) {
        if (i != 0)
            printf(", ");
        printf("%d", a[i]);
    }
    printf("\n");    

    free(a);
}
