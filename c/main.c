#include "Util.h"

void RunC100() {
    _5_1_InsertSortBinarySearch();
    _5_2_ShellSort();
    _5_3_QuickSort();
    _5_4_StableQuickSort();
    _5_5_IterativeQuickSort();
    _5_6_FindMedian();
    _5_7_HeapSort();
    _5_8_HeapSort2();
    _5_9_MergeSort(); 
    _5_10_BucketSort();  
    _5_11_SingleDuplicate();
    _5_12_EvenDuplicate();
    _5_13_HeapMerge();
    _5_14_Unique();
    _5_15_ZeroSum();
    _5_16_DominateSet();
    _5_17_MaxVisitor();
    _5_18_Contain();
    _6_1_ParenthesesMatch();
    _6_2_Postfix();
    _6_5_BoyerMoore();
    _8_1_MagicSquareOdd(5);
    _8_5_EightQueen();
    _8_6_KnightTour(5, 5);    
    _8_7_HamiltonCycle();
    _8_8_EulerTrial();
    _8_9_HonoiTower(4);  
    _8_10_GameOfLife(6, 5);
}

void RunUt() {
    Ut();
}

int main() { 
    Ut();   
    RunC100();

    // bug
    //_6_3_Prefix();

    
    
    printf("main() ended\n");
}