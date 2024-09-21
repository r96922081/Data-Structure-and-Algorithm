#include "Util.h"

int ReadIntFromFile(FILE* file, int* offset) {
    fseek(file, *offset, SEEK_SET);

    char buffer[100];
    if (fgets(buffer, sizeof(buffer), file) == NULL)
        return -1;

    *offset = ftell(file);
    return atoi(buffer);   
}

void Heapify(int *heap, int count) {
    for (int i = (count- 2) / 2; i >= 0; i--) {
        int parent = i;
        while (1) {
            int value = heap[parent];
            int left = i * 2 + 1;
            int right = i * 2 + 2;

            int leftValue = heap[left];
            int rightValue = 1000000;
            if (right < count ) {
                rightValue = heap[right];
            }

            int minChild = left;
            if (rightValue < leftValue) {
                minChild = right;
            }
            int minChildValue = heap[minChild];

            if (minChildValue < value) {
                heap[parent] = minChildValue;
                heap[minChild] = value;
            }
            if (parent == 0)
                break;

            parent /= 2;
        }
    }   
}

void FixHeap(int* heap, int heapSize) {
    int parent = 0;
    while (1) {
        int parentValue = heap[parent];
        int left = parent * 2 + 1;
        int right = parent * 2 + 2;

        int leftValue = 10000000; 
        if (left < heapSize)
            leftValue = heap[left];
        int rightValue = 10000000;
        if (right < heapSize)
            rightValue = heap[right];
        
        int minChild = left;
        int minValue = leftValue;
        if (rightValue < leftValue) {
            minChild = right;
            minValue = rightValue;
        }

        if (parentValue < minValue)
            break;

        heap[parent] = minValue;
        heap[minChild] = parentValue;
        parent = minChild;
    }
}

void _5_13_HeapMerge() {
    int count = 5;
    FILE* files[count];
    memset(files, 0, sizeof(FILE*) * count);

    for (int i = 0; i < count; i++) {
        char buf[100];
        sprintf(buf, "./input/_5_13_HeapMerge_%d.txt", i + 1);
        files[i] = fopen(buf, "r");
    }

    int heap[count];
    memset(heap, 0, sizeof(int) * count);

    int heapSize = count;
    int offset[count];
    int cache[count];
    memset(offset, 0, sizeof(int) * count);
    for (int i = 0; i < count; i++)
        cache[i] = -1;

    for (int i = 0; i < count; i++) {
        int value = ReadIntFromFile(files[i], offset + i);
        heap[i] = value;
    }

    for (int i = 0; i < count; i++) {
        cache[i] = ReadIntFromFile(files[i], offset + i);
    }    

    Heapify(heap, 5);
 

    while (1) {
        int minValue = 100000;
        int minIndex = -1;
        for (int i = 0; i < count; i++) {
            if (cache[i] != -1 && cache[i] < minValue) {
                minValue = cache[i];
                minIndex = i;
            }
        }
        if (minIndex == -1)
            break;

        cache[minIndex] = ReadIntFromFile(files[minIndex], offset + minIndex);
        printf("%d,", heap[0]);
        heap[0] = minValue;
        FixHeap(heap, count);
    }

    while (heapSize > 1) {
        printf("%d,", heap[0]);
        heap[0] = heap[heapSize - 1];
        heapSize--;
        FixHeap(heap, heapSize);
    }
    printf("%d\n", heap[0]);

    for (int i = 0; i < 5; i++)
        fclose(files[i]);
}