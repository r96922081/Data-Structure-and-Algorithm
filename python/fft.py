import math

from polynomial import *

'''
Fast Fourier transform
Multiplying two polynomials of coefficient form takes Θ(n^2), FFT can reduce the time to Θ(nlgn)
'''

def get_root_of_unity(n):
    ret = []
    for i in range(n):
        ret.append(complex(math.cos(2*math.pi*i/n), math.sin(2*math.pi*i/n)))
    return ret

def get_root_of_unity2(n):
    ret = []
    for i in range(n):
        ret.append(math.e ** (complex(0, 2 * math.pi * i / n)))
    return ret

def round_complex(c, n):
    return complex(round(c.real, n), round(c.imag, n))

def round_complex_list(l, n):
    ret = copy.deepcopy(l)
    for i in range(len(l)):
        ret[i] = round_complex(l[i],  n)
    return ret


def Recursive_FFT(a):
    n = len(a)
    if n == 1:
        return a
    
    Wn = math.e ** (complex(0, 2 * math.pi / n))
    W = 1
    a0 = []
    a1 = []
    for i in range(len(a)):
        if i % 2 == 0:
            a0.append(a[i])
        else:
            a1.append(a[i])
            
    y0 = Recursive_FFT(a0)
    y1 = Recursive_FFT(a1)    
    y = [0] * n
    for k in range(0, int(n/2)):
        y[k] = y0[k] + W * y1[k]
        y[k + int(n/2)] = y0[k] - W * y1[k]
        W = W * Wn
    return y

def Recursive_Inverse_FFT(a):
    n = len(a)
    ret = Recursive_Inverse_FFT_main(a)
    for i in range(n):
        ret[i] /= n
    return ret

def Recursive_Inverse_FFT_main(a):
    n = len(a)
    if n == 1:
        return a
    
    Wn = math.e ** (complex(0, -2 * math.pi / n))
    W = 1
    a0 = []
    a1 = []
    for i in range(len(a)):
        if i % 2 == 0:
            a0.append(a[i])
        else:
            a1.append(a[i])
            
    y0 = Recursive_Inverse_FFT_main(a0)
    y1 = Recursive_Inverse_FFT_main(a1)    
    y = [0] * n
    for k in range(0, int(n/2)):
        y[k] = y0[k] + W * y1[k]
        y[k + int(n/2)] = y0[k] - W * y1[k]
        W = W * Wn
    return y
 
def Bit_Reverse(n, bit_count):
    ret = 0
    for i in range(int(bit_count)):
        bit = n & (1 << i)
        if bit > 0:
            bit = 1
        ret += bit  * (2 ** (bit_count - i - 1))
    return int(ret)
 
def Bit_Reverse_Copy(a):
    n = len(a)
    ret = [0] * n
    for k in range(n):
        pos = Bit_Reverse(k, math.log(len(a), 2))
        ret[pos] = a[k]
    return ret

def Iterative_FFT(a):    
    A = Bit_Reverse_Copy(a)
    n = len(A)
    for s in range(1, int(math.log(n, 2)) + 1):
        m = 2 ** s
        Wm = math.e ** (complex(0, 2 * math.pi / m))
        for k in range(0, n,  m):
            W = 1
            for j in range(int(m/2)):
                t = W * A[k+j + int(m/2)]
                u = A[k+j]
                A[k+j] = u + t
                A[k+j+int(m/2)] = u -t
                W = W * Wm
            
    return A
    
import unittest

class test_polynomial(unittest.TestCase):
    def setUp(self):
        self.A = polynomial([1, 2, 3, 4, 5, 6, 7, 8])
        self.B = polynomial([5, 6, 7, 8, 9, 10, 11, 12])
        
    def test_Recursive_FFT(self):   
        n = len(self.A)
        roots = get_root_of_unity(n)
        y = []
        for r in roots:
            y.append(self.A.evaluate(r))
        y = round_complex_list(y, 3)

        dft = Recursive_FFT(self.A.a)
        dft = round_complex_list(dft, 3)          
        self.assertTrue(y == dft)
        n = len(self.B)
        roots = get_root_of_unity(n)
        y = []
        for r in roots:
            y.append(self.B.evaluate(r))            
        y = round_complex_list(y, 3)

        dft = Iterative_FFT(self.B.a)
        dft = round_complex_list(dft, 3) 
        self.assertTrue(y == dft)

    def test_Recursive_Inverse_FFT(self):
        dftA=Recursive_FFT(self.A)
        A2 = round_complex_list(Recursive_Inverse_FFT(dftA),  3)
        self.assertTrue(A2 == self.A)

        dftB=Recursive_FFT(self.B)
        B2 = round_complex_list(Recursive_Inverse_FFT(dftB),  3)
        self.assertTrue(B2 == self.B)

    def test_poly_mul_by_FFT(self):
        C = self.A * self.B
        for i in range(len(self.A)):
            self.A.a.append(0)
            self.B.a.append(0)
            
        dftA = Recursive_FFT(self.A)
        dftB = Recursive_FFT(self.B)
        
        dftC = copy.deepcopy(dftA)
        for i in range(len(dftC)):
            dftC[i] *= dftB[i]
        
        result_C = round_complex_list(Recursive_Inverse_FFT(dftC),  3)
        result_C = result_C[:-1]
        self.assertTrue(C == result_C)

    def test_Bit_Reverse(self):
        n = Bit_Reverse(5, 3)
        self.assertTrue(n == 5)
        n = Bit_Reverse(1, 3)
        self.assertTrue(n == 4)        
        n = Bit_Reverse(3, 3)
        self.assertTrue(n == 6)  
        
    def test_Iterative_FFT(self):
        n = len(self.A)
        roots = get_root_of_unity(n)
        y = []
        for r in roots:
            y.append(self.A.evaluate(r))
        y = round_complex_list(y, 3)

        dft2 = Iterative_FFT(self.A.a)
        dft2 = round_complex_list(dft2, 3) 
        self.assertTrue(y == dft2)

        n = len(self.B)
        roots = get_root_of_unity(n)
        y = []
        for r in roots:
            y.append(self.B.evaluate(r))            
        y = round_complex_list(y, 3)

        dft2 = Iterative_FFT(self.B.a)
        dft2 = round_complex_list(dft2, 3) 
        self.assertTrue(y == dft2) 
        
    def test_Bit_Reverse_Copy(self):
        a =[0, 1, 2, 3, 4, 5, 6, 7]
        ret = Bit_Reverse_Copy(a)
        self.assertTrue(ret == [0, 4, 2, 6, 1, 5, 3, 7])         
        
if __name__ == '__main__':
    unittest.main()
