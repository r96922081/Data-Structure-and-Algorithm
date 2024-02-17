import unittest
import random
import threading
from utility import matrix, random_seed

'''
Demo multi-threaded algorithm by matrix multiplication
'''

def matrix_multiply_vec_multithreaded(A, x):
    row = A.row()
    y = matrix(row, 1)
    
    threads = []    
    
    def mul_row(A, x, y, i):
        col = A.col()
        for j in range(col):
            y[i][0] += A[i][j] * x[j][0]
            
    for i in range(row):
        t = threading.Thread(target = mul_row, args = [A, x, y, i])
        t.start()
        threads.append(t)
        
    for t in threads:
        t.join()
        
    return y

def matrix_multiply_matrix_multithreaded_1(A, B):
    row = A.row()
    col = B.col()
    C = matrix(row, col)
    
    threads = []
    
    def row_mul_col(A, B, C, i, j):
        for k in range(A.col()):
            C[i][j] += A[i][k] * B[k][j]
            
    def row_mul_matrix(A, B, C, i):
        for j in range(B.col()):
            t = threading.Thread(target = row_mul_col, args = [A, B, C, i, j])
            t.start()
            threads.append(t)
  
    for i in range(row):
        t = threading.Thread(target = row_mul_matrix, args = [A, B, C, i])
        t.start()
        threads.append(t)    

    for t in threads:
        t.join()
        
    return C

def square_matrix_multiply_multithreaded_2(A, B):
    n = A.row()
    C = matrix(n, n)
    square_matrix_multiply_multithreaded_2_with_offset(n, C, 0, 0, A, 0, 0, B, 0, 0)
    return C

def square_matrix_multiply_multithreaded_2_with_offset(n, C, C_row_offset, C_col_offset, A, A_row_offset, A_col_offset, B, B_row_offset, B_col_offset):
    if n == 1:
        C[C_row_offset][C_col_offset] = A[A_row_offset][A_col_offset] * B[B_row_offset][B_col_offset]
    else:
        #Declare T11, T12, T21, T22 takes Θ(n^2). Need to find a better way to partition T,
        #Otherwise the span of this algorithm will be bounded by that
        T11 = matrix(n//2, n//2)
        T12 = matrix(n//2, n//2)
        T21 = matrix(n//2, n//2)
        T22 = matrix(n//2, n//2)

        t1 = threading.Thread(target = square_matrix_multiply_multithreaded_2_with_offset, args=[n//2, C, C_row_offset, C_col_offset, A, A_row_offset, A_col_offset, B, B_row_offset, B_col_offset])
        t1.start()
        t2 = threading.Thread(target = square_matrix_multiply_multithreaded_2_with_offset, args=[n//2, C, C_row_offset, C_col_offset + n//2, A, A_row_offset, A_col_offset, B, B_row_offset, B_col_offset + n//2])
        t2.start()
        t3 = threading.Thread(target = square_matrix_multiply_multithreaded_2_with_offset, args=[n//2, C, C_row_offset + n//2, C_col_offset, A, A_row_offset + n//2, A_col_offset, B, B_row_offset, B_col_offset])
        t3.start()
        t4 = threading.Thread(target = square_matrix_multiply_multithreaded_2_with_offset, args=[n//2, C, C_row_offset + n//2, C_col_offset + n//2, A, A_row_offset + n//2, A_col_offset, B, B_row_offset, B_col_offset + n//2])
        t4.start()
        t5 = threading.Thread(target = square_matrix_multiply_multithreaded_2_with_offset, args=[n//2, T11, 0, 0, A, A_row_offset, A_col_offset + n//2, B, B_row_offset + n//2, B_col_offset])
        t5.start()
        t6 = threading.Thread(target = square_matrix_multiply_multithreaded_2_with_offset, args=[n//2, T12, 0, 0, A, A_row_offset, A_col_offset + n//2, B, B_row_offset + n//2, B_col_offset + n//2])
        t6.start()
        t7 = threading.Thread(target = square_matrix_multiply_multithreaded_2_with_offset, args=[n//2, T21, 0, 0, A, A_row_offset + n//2, A_col_offset + n//2, B, B_row_offset + n//2, B_col_offset])
        t7.start()
        square_matrix_multiply_multithreaded_2_with_offset(n//2, T22, 0, 0, A, A_row_offset + n//2, A_col_offset + n//2, B, B_row_offset + n//2, B_col_offset + n//2)
        t1.join()
        t2.join()
        t3.join()
        t4.join()
        t5.join()
        t6.join()
        t7.join()
        
        threads = []
        def add_element(i, j):
            if i < n//2:
                if j < n//2:
                    T = T11
                else:
                    T = T12
            else:
                if j < n//2:
                    T = T21
                else:
                    T = T22               
                    
            i2 = i
            j2 = j
            if i >= n//2:
                i2 -= n//2
            if j >= n//2:
                j2 -= n//2
                    
            C[C_row_offset + i][C_col_offset + j] += T[i2][j2]
            
        def add_row(i):
            for j in range(n):
                t = threading.Thread(target = add_element, args=[i, j])
                t.start()
                threads.append(t)
                
        for i in range(n):
            t = threading.Thread(target = add_row, args=[i])
            t.start()
            threads.append(t)
    
        for t in threads:
            t.join()

def merge_sort_multithreaded(A):    
    n = len(A)
    p = 0
    r = n - 1
    if n != 0:
        merge_sort_multithreaded_2(A, p, r, A, 0)

def merge_sort_multithreaded_2(A, p, r, sorted, sorted_start_index):
    n = r - p + 1
    if n == 1:
        sorted[sorted_start_index] = A[p]
    else:
        T = [0] * n
        q = (p + r) // 2
        q2 = q - p + 1
        t1 = threading.Thread(target = merge_sort_multithreaded_2, args=[A, p, q, T, 0])
        t1.start()        
        merge_sort_multithreaded_2(A, q + 1, r, T, q2)
        t1.join()
        
        merge_multithreaded(T, 0, q2 - 1, q2, n - 1, sorted, sorted_start_index)

def merge_multithreaded(T, p1, r1, p2, r2, A, p3):
    n1 = r1 - p1 + 1
    n2 = r2 - p2 + 1
    if n1 < n2:
        p1, p2 = p2, p1
        r1, r2 = r2, r1
        n1, n2 = n2, n1
    if n1 == 0:
        return
    else:
        q1 = (p1 + r1) // 2
        q2 = modified_binary_search_for_merge(T[q1], T, p2, r2)
        q3 = p3 + q1 - p1 + q2 - p2
        A[q3] = T[q1]
        t1 = threading.Thread(target = merge_multithreaded, args=[T, p1, q1-1, p2, q2-1, A, p3])
        t1.start()
        merge_multithreaded(T, q1+1, r1, q2, r2, A, q3+1)
        t1.join()

def modified_binary_search_for_merge(x, T, p, r):
    if p > r:
        return p
    
    low = p
    high =  r + 1
    while low < high:
        mid = (low + high) // 2
        if x <= T[mid]:
            high = mid
        else:
            low = mid + 1
    return high

class multithreaded_algorithm_test(unittest.TestCase):
    def create_random_matrix(self, col, row):
        A = matrix(col, row)
        for i in range(col):
            for j in range(row):
                A[i][j] = random.randint(-100, 100)
        return A
    
    def test_matrix_multiply_vec(self):
        for _ in range(30):
            random_seed(False)
            row = random.randint(1, 10)
            col = random.randint(1, 10)
            A = self.create_random_matrix(row, col)
            x = self.create_random_matrix(col, 1)
            B1 = A * x
            B2 = matrix_multiply_vec_multithreaded(A, x)
            self.assertTrue(B1 == B2)
            
    def test_matrix_multiply_matrix_1(self):
        for _ in range(30):
            random_seed(False)
            row = random.randint(1, 10)
            col = random.randint(1, 10)
            col2 = random.randint(1, 10)
            A = self.create_random_matrix(row, col)
            B = self.create_random_matrix(col, col2)
            C1 = A * B
            C2 = matrix_multiply_matrix_multithreaded_1(A, B)
            self.assertTrue(C1 == C2)
            
    def test_matrix_multiply_matrix_2(self):
        for _ in range(10):
            random_seed(False)
            n = 2 ** random.randint(0, 3)
            A = self.create_random_matrix(n, n)
            B = self.create_random_matrix(n, n)
            C1 = A * B
            C2 = square_matrix_multiply_multithreaded_2(A, B)
            self.assertTrue(C1 == C2)
            
    def test_merge_sort_multithreaded(self):
        for n in range(30):
            random_seed(False)
            A = []
            golden = []
            for i in range(n):
                value = random.randint(1, 100)
                golden.append(value)  
                A.append(value)
            
            merge_sort_multithreaded(A)
            golden.sort()
            self.assertTrue(A == golden)
        
        
if __name__ == '__main__':
    unittest.main()
