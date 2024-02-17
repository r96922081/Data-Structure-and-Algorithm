import unittest
import random
import sys
from utility import matrix
import copy

'''
divide and conqueror algorithm with 2 demo example

1. maximum subarray problem
2. Strassen matrix multiplication algorithm

'''

def brute_force_max_profit(array):
    max_profit = -sys.maxsize
    left = -1
    right = -1
    
    for i in range(0, len(array) - 1):
        for j in range(i + 1, len(array)):
            if array[j] - array[i] > max_profit:
                left = i
                right = j
                max_profit = array[j] - array[i]
            
    return max_profit, left, right

def divide_and_conquer_maximum_subarray(array):
    diff_array = [-sys.maxsize]
    for i in range(1, len(array)):
        diff_array.append(array[i] - array[i-1])
    
    return divide_and_conquer_maximum_subarray_with_range(diff_array, 0, len(diff_array) - 1)   

def divide_and_conquer_maximum_subarray_with_range(array, low, high):
    if high == low:
        return array[low], low, high
    else:
        mid = (low + high) // 2
        left_sum, left_low, left_high  = divide_and_conquer_maximum_subarray_with_range(array, low, mid)
        right_sum, right_low, right_high  = divide_and_conquer_maximum_subarray_with_range(array, mid + 1, high)
        cross_sum, cross_low, cross_high  = find_maximum_crossing_subarray(array, low, mid, high)
        
        if left_sum >= right_sum and left_sum >= cross_sum:
            return left_sum, left_low, left_high
        elif right_sum >= left_sum and right_sum >= cross_sum:
            return right_sum, right_low, right_high
        else:
            return cross_sum, cross_low, cross_high
        
def find_maximum_crossing_subarray(diff_array, low, mid, high):
    left_sum = -sys.maxsize
    sum = 0
    max_left = mid + 1
    max_right = mid
    for i in range(mid, low - 1, -1):
        sum = sum + diff_array[i]
        if sum > left_sum:
            left_sum = sum
            max_left = i
    right_sum = -sys.maxsize
    sum = 0
    for i in range(mid + 1, high + 1):
        sum = sum + diff_array[i]
        if sum > right_sum:
            right_sum = sum
            max_right = i
            
    return left_sum + right_sum, max_left, max_right
    
def divide_matrix_by_2(m):
    if m.row() % 2 != 0:
        raise Exception('size must be the multiple of 2')
        
    size = m.row() // 2
    m11 = matrix(size, size)
    m12 = matrix(size, size)
    m21 = matrix(size, size)
    m22 = matrix(size, size)
    for i in range(0, size):
        for j in range(0, size):
            m11[i][j] = m[i][j]
            m12[i][j] = m[i][j+size]
        for j in range(0, size):
            m21[i][j] = m[i+size][j]
            m22[i][j] = m[i+size][j+size]
            
    return m11, m12, m21, m22
        
def merge_matrix_to_size_multiple_2(m11, m12, m21, m22):
    size = m11.row()
    m = matrix(size * 2, size* 2)
    for i in range(0, size):
        for j in range(0, size):
            m[i][j] = m11[i][j]
            m[i][j+size] = m12[i][j]
        for j in range(0, size):
            m[i+size][j] = m21[i][j]
            m[i+size][j+size] = m22[i][j]
    return m
        
def strassen(m1, m2):
    if m1.row() % 2 != 0 or m2.row() % 2 != 0:
        raise Exception('size must be the multiple of 2')
   
    A11, A12, A21, A22 = divide_matrix_by_2(m1)
    B11, B12, B21, B22 = divide_matrix_by_2(m2)

    S1 = B12 - B22
    S2 = A11 + A12
    S3 = A21 + A22
    S4 = B21 - B11
    S5 = A11 + A22
    S6 = B11 + B22
    S7 = A12 - A22
    S8 = B21 + B22
    S9 = A11 - A21
    S10 = B11 +B12

    P1 = A11 * S1
    P2 = S2 * B22
    P3 = S3 * B11
    P4 = A22 * S4
    P5 = S5 * S6
    P6 = S7 * S8
    P7 = S9 * S10

    C11 = P5 + P4 - P2 + P6
    C12 = P1 + P2
    C21 = P3 + P4
    C22 = P5 + P1 - P3 - P7
    
    C = merge_matrix_to_size_multiple_2(C11, C12, C21, C22)
    return C

class mytest(unittest.TestCase):
    def _test_maximum_subarray(self): 
        for i in range(2, 10):
            array = []
            for j in range(0, i):
                array.append(10 - j)
        
            ans1, left1, right1 = brute_force_max_profit(array)
            ans2, left2, right2 = divide_and_conquer_maximum_subarray(array)
            self.assertTrue(ans1 == ans2)
        
        for _ in range(1000):
            array_len = 8
            seed = random.randint(0, sys.maxsize)
            #seed = 4708997593913070297
            #print(seed)
            random.seed(seed)          
            array = []
            for _ in range(array_len):
                array.append(random.randint(0, 100))  
                
            ans1, left1, right1 = brute_force_max_profit(array)
            ans2, left2, right2 = divide_and_conquer_maximum_subarray(array)
            self.assertTrue(ans1 == ans2)
            
    def test_strassen_algorithm(self):
        max_value = 10
        for i in range(1, 10):
            size = i * 2
            m1 = matrix(size, size)
            m2 = matrix(size, size)
            for j in range(0, size):
                for k in range(0, size):
                    m1[j][k] = random.randint(-max_value,  max_value)
                    m2[j][k] = random.randint(-max_value,  max_value)
            
            m3 = m1 * m2
            m4 = strassen(m1, m2)
            self.assertTrue(m3, m4)
            

if __name__ == '__main__':
    unittest.main()
