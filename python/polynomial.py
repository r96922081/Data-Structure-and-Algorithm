import copy

class polynomial:
    def __init__(self, a):
        self.a = a
        
    def set(self, a):
        self.a = a
        
    def evaluate(self, x):
        value = 0
        for i in range(len(self.a)):
            value += self.a[i] * (x ** i)
        return value
        
    def __add__(self, A2):
        if len(self) > len(A2):
            result = copy.deepcopy(self)
            for i in range(len(A2)):
                result[i] += A2[i]
        else:
            result = copy.deepcopy(A2)
            for i in range(len(self)):
                result[i] += self.a[i]
        
        return result
        
    def __mul__(self, A2):
        result = polynomial([0] * (len(self) + len(A2) - 1))
            
        for i in range(len(A2)):
            for j in range(len(self)):
                result[i + j] += self[j] * A2[i]
        
        return result
        
    def __len__(self):
        return len(self.a)
        
    def __getitem__(self, n):
        return self.a[n]

    def __setitem__(self, n, v):
        self.a[n] = v
        
    def __str__(self):
        return str(self.a)

    def __eq__(self, A2):
        if type(A2) == type([]):
            return self.a == A2
        elif  isinstance(A2, polynomial):
            return self.a == A2.a

import unittest

class test_polynomial(unittest.TestCase):
    def setUp(self):
        self.A = polynomial([1, 2, 3])
        self.B = polynomial([4, 5, 6, 7])

    def test_evaluate(self):   
        self.assertTrue(self.A.evaluate(2) == 17)
    
    def test_add(self):   
        C = self.A + self.B
        self.assertTrue(C == [5, 7, 9, 7])
        D = self.B + self.A
        self.assertTrue(D == [5, 7, 9, 7])

    def test_mul(self):   
        C = self.A * self.B
        self.assertTrue(C == [4, 13, 28, 34, 32, 21])
        C = self.B * self.A
        self.assertTrue(C == [4, 13, 28, 34, 32, 21])
        
if __name__ == '__main__':
    unittest.main()
