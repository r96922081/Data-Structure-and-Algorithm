import unittest
import math
from utility import random_seed
import random

'''
string matching by 
1. Rabin karp algorithm
2. Finite state automation
3. KMP algorithm
'''

def is_prime(n):
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

def get_prime(max_n):
    for i in range(max_n, 2, -1):
        if is_prime(i):
            break
    return i
    
def rabin_karp_matcher_for_ascii(T, P):
    d = 255
    max_q = 2 ** 32 // d
    q = get_prime(max_q)
    return rabin_karp_matcher_for_ascii_main(T, P, d, q)
    
def rabin_karp_matcher_for_ascii_main(T, P, d, q):
    n = len(T)
    m = len(P)
    if n < m:
        return []
    
    h = (d ** (m - 1)) % q
    p = 0
    t = [0] * (n - m + 1)
    shift = []
    for i in range(m):
        p = (d*p + ord(P[i]))%q
        t[0] = (d*t[0] + ord(T[i]))%q
        
    for s in range(n - m + 1):
        if p == t[s]:
            if P == T[s:s+m]:
                shift.append(s)
        if s < n - m:
            t[s+1] = (d*(t[s] - ord(T[s])*h) + ord(T[s+m])) % q
            
    return shift

def compute_transition_function(P, alphabet):
    m = len(P)
    transition_function = {}
        
    for q in range(m + 1):
        transition_function[q] = {}
        for a in alphabet:
            k = min(m + 1, q + 2)
            while True:
                k = k - 1
                if k == 0:
                    break
                if P[:k] == (P[:q] + a)[-k:]:
                    break
            transition_function[q][a] = k
            
    return transition_function
            
def finite_automation_matcher_ascii(T, P):
    alphabet = []
    for i in range(256):
        alphabet.append(chr(i))
        
    n = len(T)
    m = len(P)
    q = 0
    shift = []
    transition_function = compute_transition_function(P, alphabet)
    for i in range(n):
        q = transition_function[q][T[i]]
        if q == m:
            shift.append(i - m + 1)
    return shift

def compute_prefix_function(P):
    m = len(P)
    prefix_function = [0] * (m + 1)
    prefix_function[1] = 0
    k = 0
    for q in range(2, m+1):
        if P[k] == P[q - 1]:
            k = k + 1
        else:
            while k > 0 and P[k] != P[q-1]:
                k = prefix_function[k]
            if P[k] == P[q - 1]:
                k = k + 1
        prefix_function[q] = k
    return prefix_function

def kmp_matcher(T, P):
    n = len(T)
    m = len(P)
    prefix_function = compute_prefix_function(P)
    q = 0
    shift = []
    for i in range(n):
        while q > 0 and P[q] != T[i]:
            q = prefix_function[q]
        if P[q] == T[i]:
            q = q + 1
        if q == m:
            shift.append(i - m + 1)
            q = prefix_function[q]
    return shift

def matching_by_lib(t, p):
    shifts = []
    start = 0
    
    while True:
        offset = t.find(p, start)
        if offset == -1:
            break
        else:
            shifts.append(offset)
            start = offset + 1
            
    return shifts

def naive_string_matcher(t, p):
    n = len(t)
    m = len(p)
    shifts = []
    for s in range(n - m + 1):
        if p == t[s:s+m]:
            shifts.append(s)
    return shifts

class string_matching_test(unittest.TestCase):
    def get_random_t_p(self):
        t_len = random.randint(0, 15)
        p_len = random.randint(1, 5)
        t = ''
        p = ''
        chars = ['a', 'b', 'c', 'd', 'e']
        
        for i in range(t_len):
            t += random.choice(chars)
        for i in range(p_len):
            p += random.choice(chars)
            
        return t, p
        
    def test_matching_by_lib(self):
        shifts = matching_by_lib('abcbbcabc', 'bc')
        self.assertTrue(shifts == [1, 4, 7])
        
    def test_naive_string_matcher(self):
        for _ in range(100):
            random_seed(False)
            t, p = self.get_random_t_p()
            shift1 = naive_string_matcher(t, p)
            shift2 = matching_by_lib(t, p)
            self.assertTrue(shift1 == shift2)
        
    def test_rabin_karp_matcher_for_ascii(self):
        for _ in range(100):
            random_seed(False)
            t, p = self.get_random_t_p()
            shift1 = rabin_karp_matcher_for_ascii(t, p)
            shift2 = matching_by_lib(t, p)
            self.assertTrue(shift1 == shift2)
        
    def test_finite_automation_matcher_ascii(self):
        for _ in range(100):
            random_seed(False)
            t, p = self.get_random_t_p()
            shift1 = finite_automation_matcher_ascii(t, p)
            shift2 = matching_by_lib(t, p)
            self.assertTrue(shift1 == shift2)

    def test_kmp_matcher(self):      
        for _ in range(100):
            random_seed(False)
            t, p = self.get_random_t_p()
            shift1 = kmp_matcher(t, p)
            shift2 = matching_by_lib(t, p)
            self.assertTrue(shift1 == shift2)                                            

if __name__ == '__main__':
    unittest.main()
