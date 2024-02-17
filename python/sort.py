import unittest
import random
import sys
from heap import heap,  heaptype
import copy

'''
Comparison based sorting algorithm: 
insert sort, merge sort, bubble sort, quick sort, heap sort

Non-comparison based sorting algorithm (sorting in linear time): 
counting sort, radix sort, bucket sort
'''

def merge_sort(A):
    merge_sort_with_range(A, 0, len(A) - 1)
    
def merge_sort_with_range(A, p, r):
    if p < r:
        q = (p + r) // 2
        merge_sort_with_range(A, p, q)
        merge_sort_with_range(A, q + 1, r)
        merge(A, p, q, r)
        
def merge(A, p, q, r):
    n1 = q - p + 1
    n2 = r - q
    L = []
    R = []
    for i in range(n1):
        L.append(A[p + i])
    for j in range(n2):
        R.append(A[q + j + 1])
    L.append(sys.maxsize)
    R.append(sys.maxsize)
    i = 0
    j = 0
    for k in range(p, r + 1):
        if L[i] <= R[j]:
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1

def insert_sort(A):
    for j in range(1, len(A)):
        key = A[j]
        i = j - 1
        while i >= 0 and A[i] > key:
            A[i + 1] = A[i]
            i -= 1
        A[i + 1] = key
    
def bubble_sort(A):
    for i in range(len(A)):
        for j in range(len(A) - 1, i - 1, -1):
            if A[j] < A[j - 1]:
                A[j], A[j-1] = A[j-1], A[j]

def quick_sort(A):
    quick_sort_with_range(A, 0, len(A) - 1)
    
def quick_sort_with_range(A, p, r):
    if p < r:
        q = partition(A, p, r)
        quick_sort_with_range(A, p, q - 1)
        quick_sort_with_range(A, q + 1, r)
        
def partition(A, p, r):
    x = A[r]
    i = p - 1
    for j in range(p, r):
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[i + 1], A[r] = A[r], A[i + 1]
    
    return i + 1

def heap_sort(A):
    h = heap(heaptype.max)
    for a in A:
        h.insert(a, a)
    h.heapsort()
    
    for i in range(len(A)):
        A[i] = h.A[i + 1].key

def counting_sort(A_keys, A_elements, k):
    max_int = 1000
    if k > max_int:
        raise Exception('support max int = ' + str(max_int))
        
    C = []
    for _ in range(k + 1):
        C.append(0)
        
    for a in A_keys:
        C[a] += 1
        
    for i in range(1, k + 1):
        C[i] = C[i] + C[i-1]
        
    B = []
    for _ in range(len(A_keys) + 1):
        B.append(None)
        
    for j in range(len(A_keys) - 1,  -1,  -1):
        B[C[A_keys[j]]] = A_elements[j]
        C[A_keys[j]] -= 1
        
    B.pop(0)
    for i in range(len(B)):
        A_elements[i] = B[i]

def radix_sort(A):
    max_int = max(A)
        
    i = 1
    while i <= max_int:
        keys = []
        for a in A:
            keys.append(a // i % 10)
        
        counting_sort(keys, A, 9)
        i *= 10
        
def bucket_sort(A):
    bucket_number = 10
    max_int = max(A)
    lead_max = 1
    while lead_max * 10 <= max_int:
        lead_max *= 10
    
    B = []
    for _ in range(bucket_number):
        B.append([])
    for a in A:
        B[a // lead_max].append(a)
  
    answer = []  
    for b in B:
        b.sort()
        answer += b
        
    for i in range(len(answer)):
        A[i] = answer[i]

class test_sorts(unittest.TestCase):
    def _test1(self):
        for _ in range(10):
            answer = []
            insert_sort_data = []
            merge_sort_data = []
            bubble_sort_data = []
            quick_sort_data = []
            heap_sort_data = []
            
            for _2 in range(20):
                n = random.randint(-sys.maxsize, sys.maxsize - 1)
                answer.append(n)
                insert_sort_data.append(n)
                merge_sort_data.append(n)
                bubble_sort_data.append(n)
                quick_sort_data.append(n)
                heap_sort_data.append(n)
                
            answer.sort()
            insert_sort(insert_sort_data)
            merge_sort(merge_sort_data)
            bubble_sort(bubble_sort_data)
            quick_sort(quick_sort_data)
            heap_sort(heap_sort_data)
            self.assertTrue(answer == insert_sort_data)
            self.assertTrue(answer == merge_sort_data)
            self.assertTrue(answer == bubble_sort_data)
            self.assertTrue(answer == quick_sort_data)
            self.assertTrue(answer == heap_sort_data)
            
    def test2(self):
        k = 1000
        for _ in range(100):            
            answer = []
            counting_sort_data = []
            radix_sort_data = []
            bucket_sort_data = []
            
            for _2 in range(20):
                n = random.randint(0, k)
                answer.append(n)
                counting_sort_data.append(n)
                radix_sort_data.append(n)
                bucket_sort_data.append(n)
                
            answer.sort()
            
            counting_sort_key_data = counting_sort_data
            counting_sort_element_data = copy.deepcopy(counting_sort_data)
            counting_sort(counting_sort_key_data, counting_sort_element_data, k)
            self.assertTrue(answer == counting_sort_element_data)
            
            radix_sort(radix_sort_data)
            self.assertTrue(answer == radix_sort_data)
            
            bucket_sort(bucket_sort_data)
            self.assertTrue(answer == bucket_sort_data)


if __name__ == '__main__':
    unittest.main()
