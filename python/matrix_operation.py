from utility import matrix
import copy
import unittest
from fractions import Fraction as r
import math
import random

'''
1. Solve equation by LUP matrix
2. LU decomposition
3. LUP decomposition
4. invert a matrix
'''

def solve_matrix(A, b):
    L, U, P = LUP_decomposition(A)
    return LUP_solve(L, U, P, b)
    
def LUP_solve(L, U, P, b):
    n = L.row()
    y = matrix(n, 1)
    x = matrix(n, 1)
    b2 = P * b
    for i in range(n):
        y[i][0] = b2[i][0]
        for j in range(0, i):
            y[i][0] -= L[i][j] * y[j][0]
    for i in range(n - 1, -1, -1):
        x[i][0] = y[i][0]
        for j in range(i + 1, n):	
            x[i][0] -= U[i][j] * x[j][0]
        x[i][0] /= U[i][i]
    return x

def LU_decomposition(m):
	A = copy.deepcopy(m)
	n = A.row()
	L = matrix(n, n)
	for i in range(n):
		L[i][i] = 1
	U = matrix(n, n)
	
	for k in range(0, n):
		U[k][k] = A[k][k]
		for i in range(k, n):
			L[i][k] = A[i][k] / A[k][k]
			U[k][i] = A[k][i]
		for i in range(k, n):
			for j in range(k, n):
				A[i][j] = A[i][j] - L[i][k] * U[k][j]
	
	return L, U

def LUP_decomposition(m):
	A = copy.deepcopy(m)
	n = A.row()
	P = matrix(n, n)
	for i in range(n):
		P[i][i] = 1
		
	k2 = 0
	for k in range(n):
		value = 0
		k2 = k
		for i in range(k, n):
			if math.fabs(A[i][k]) > value:
				value = math.fabs(A[i][k])
				k2 = i
		P = P.exchange_row(k, k2)
		A = A.exchange_row(k, k2)
		for i in range(k + 1, n):
			A[i][k] = A[i][k] / A[k][k]
			for j in range(k + 1, n):
				A[i][j] = A[i][j] - A[i][k] * A[k][j]
				
	L = matrix(n, n)
	for i in range(n):
		L[i][i] = 1
	U = matrix(n, n)
	for i in range(n):
		for j in range(n):
			if i > j:
				L[i][j] = A[i][j]
			else:
				U[i][j] = A[i][j]
	return L, U, P

def inverse_matrix(m):
	row = m.row()
	ret_matrix = matrix(row, row)
	if m.det() == 0:
		return None
	else:
		L, U, P = LUP_decomposition(m)
		for i in range(row):
			I = matrix(row, 1)
			I[i][0] = 1
			x = LUP_solve(L, U, P, I)
			for j in range(row):
				ret_matrix[j][i] = x[j][0]
	return ret_matrix

class matrix_operation_test(unittest.TestCase):
    def setUp(self):
        dummy_p = matrix(3, 3)
        dummy_p[0][0] = r(1)
        dummy_p[1][1] = r(1)       
        dummy_p[2][2] = r(1)

        self.A = matrix(3, 3)
        self.A[0] = [1, 2, 0]
        self.A[1] = [3, 4, 4]
        self.A[2] = [5, 6, 3]
        self.A = dummy_p * self.A # transform all A's element to rational
        
        self.b = matrix(3, 1)
        self.b[0][0] = 3
        self.b[1][0] = 7
        self.b[2][0] = 8
        self.b = dummy_p * self.b
        
        self.L = matrix(3, 3)
        self.L[0] = [1, 0, 0]
        self.L[1] = [r('0.2'), 1, 0]
        self.L[2] = [r('0.6'), r('0.5'), 1]  
        self.L = dummy_p * self.L
        
        self.U = matrix(3, 3)
        self.U[0] = [5, 6, 3]
        self.U[1] = [0, r('0.8'), r('-0.6')]
        self.U[2] = [0, 0, r('2.5')] 
        self.U = dummy_p * self.U
        
        self.P = matrix(3, 3)
        self.P[0] = [0, 0, 1]
        self.P[1] = [1, 0, 0]
        self.P[2] = [0, 1, 0] 
        self.P = dummy_p * self.P
        
        self.x = matrix(3, 1)
        self.x[0] = [r('-1.4')]
        self.x[1] = [r('2.2')]
        self.x[2] = [r('0.6')] 
        self.x = dummy_p * self.x      
        
    
    def test_LUP_solve(self):
        ans = LUP_solve(self.L, self.U, self.P, self.b)
        self.assertTrue(self.x == ans) 
        
    def test_LU_decomposition(self):
        L,  U = LU_decomposition(self.A)
        valid_L = True
        break_outer = False
        for i in range(len(L.matrix)):
            for j in range(i + 1,  len(L.matrix)):
                if L[i][j] != 0:
                    valid_L = False
                    break_outer = True
                    break
            if break_outer:
                break
        self.assertTrue(valid_L)            
                    
        valid_U = True
        for i in range(len(U.matrix)):
            for j in range(0,  i):
                if U[i][j] != 0:
                    valid_U = False
                    break_outer = True
                    break
            if break_outer:
                break
        self.assertTrue(valid_U)  
        self.assertTrue(L * U == self.A)
        
    def test_LUP_decomposition(self):
        for _ in range(10):
            dimension = 5
            m = matrix(dimension, dimension)
            for i in range(dimension):
                for j in range(dimension):
                    m[i][j] = random.randint(1, 9)
            
            if m.det != 0:
                L, U, P = LUP_decomposition(m)
                LU = L * U
                Pm = P * m
                
            for i in range(dimension):
                for j in range(dimension):
                    LU[i][j] = round(LU[i][j])
                    Pm[i][j] = round(Pm[i][j])
                    
            self.assertTrue(LU == Pm)  
                 
    def test_inverse_matrix(self):
        pass_count = 0
        dimension = 5
        while pass_count < 10:
            A = matrix(dimension, dimension)
            for i in range(dimension):
                for j in range(dimension):
                    A[i][j] = random.randint(1, 9)
            
            if A.det() == 0:
                continue
            
            inverse = inverse_matrix(A)
            I = A * inverse
            for i in range(dimension):
                for j in range(dimension):
                    I[i][j] = round(I[i][j])
                    if i == j:
                        self.assertTrue(I[i][j] == 1)
                    else:
                        self.assertTrue(I[i][j] == 0)                
                    
            pass_count += 1
                        
    def test_solve_matrix(self):
        pass_count = 0
        while pass_count < 10:
            dimension = 5
            A = matrix(dimension, dimension)
            for i in range(dimension):
                for j in range(dimension):
                    A[i][j] = random.randint(1, 9)
            
            if A.det() == 0:
                continue
                
            x = matrix(dimension, 1)
            for i in range(dimension):
                x[i][0] = random.randint(1, 9)
                
            b = A * x
            x2 = solve_matrix(A, b)
            for i in range(dimension):
                x2[i][0] = round(x2[i][0])
            
            self.assertTrue(x == x2)
                    
            pass_count += 1
            
    
    def tearDown(self):
        pass

if __name__ == '__main__':
    unittest.main()
    
    
    
