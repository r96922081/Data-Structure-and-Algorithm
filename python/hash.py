import math
import random
import unittest
    
'''
Create perfect hash (no collision)
'''

def get_perfect_hash(keys):
        n = len(keys)
        m = n * n
        hashtable = []
        for i in range(n*n):
            hashtable.append(-1)
            
        max_key = max(keys)
        
        perfect_hash = None
        while True:        
            for i in range(m):
                hashtable[i] = -1
                
            ok = True    
            hash = universal_class(m, max_key).get_hash()
            for key in keys:
                hashvalue = hash(key)
                if hashtable[hashvalue] != -1:
                    ok = False
                    break
                else:
                    hashtable[hashvalue] = key
            if ok:
                perfect_hash = hash
                break
        return perfect_hash
    
def get_2_level_perfect_hash(level_1_table_size, keys):
        max_key = max(keys)
        level_1_hash = universal_class(level_1_table_size, max_key).get_hash()
        level_1_table = []
        level_2_hashes = []
        
        for i in range(level_1_table_size):
            level_1_table.append([])
            level_2_hashes.append(None)
            
        for key in keys:
            level_1_table[level_1_hash(key)].append(key)
    
        for i in range(len(level_1_table)):
            if len(level_1_table[i]) != 0:
                level_2_hashes[i] = get_perfect_hash(level_1_table[i]) 
            
        return level_1_hash,  level_2_hashes
    
    
class hash_function:
    def __init__(self, a, b, p, m):
        self.a = a
        self.b = b
        self.p = p
        self.m = m
        
    def __call__(self, k):
        return ((self.a * k + self.b) % self.p) % self.m
        
    def __str__(self):
        return '((' + str(self.a) + ' * key + ' + str(self.b) + ') % ' + str(self.p) + ') % ' + str(self.m)
    
class universal_class:
    def __init__(self, m, max_key):
        self.p = self.find_prime(max_key + 1)
        self.m = m
        
    def get_hash(self):        
        return hash_function(random.randint(0, self.p -1), random.randint(1, self.p -1), self.p, self.m)
        
    def find_prime(self, min):
        min = max(min, 3)
        while not self.is_prime(min):
            min += 1
        return min

    def is_prime(self, n):
        factors = []
        for i in range(int(math.sqrt(n)) + 1):
            factors.append(i)
            
        factors[0] = -1
        factors[1] = -1
        
        length = len(factors)
        for i in range(length):
            if factors[i] != -1:
                if n % i == 0:
                    return False
                i2 = i
                while i2 < length:
                    factors[i2] = -1
                    i2 += i
            
        return True

def select_distinct_keys(max_key, count):
    u = []
    for i in range(max_key):
        u.append(i)     
        
    keys = []
    
    while len(keys) < count:
        r = random.randint(0,  len(u) - 1)
        if u[r] != -1:
            keys.append(u[r])
            u[r] = -1        
            
    return keys

class hash_test(unittest.TestCase):
    # check if collision possibility < 1/m
    def _test_universal_hash(self):
        max_key = 1000
        m = 37

        hash = universal_class(m, max_key).get_hash()

        collision = 0
        count = 500
        for i in range(count):
            keys = self.select_keys(max_key, 2)
            k = keys[0]
            l = keys[1]
            if hash(k) == hash(l):
                collision += 1
                
        print('Test if collision < 1/m ? \ncollision % = ' + str(collision / count) + ', 1/m = ' + str(1/m))    
    
    def test_one_level_perfect_hash(self):
        for _ in range(10):
            max_key = 99
            n = 12
            keys = select_distinct_keys(max_key, n)
            perfect_hash = get_perfect_hash(keys)
                    
            slots = []
            for _2 in range(perfect_hash.m):
                slots.append(-1)
                
            for key in keys:
                hash_value = perfect_hash(key)
                self.assertTrue(slots[hash_value] == -1)
                slots[hash_value] = key
        
    def test_two_level_pefect_hash(self):
        for _ in range(10):
            level_1_table_size = 20
            max_key = 50
            key_count =  30
            keys = select_distinct_keys(max_key, key_count)
            level_1_hash,  level_2_hashes = get_2_level_perfect_hash(level_1_table_size, keys)
            
            slots_2d = []
            for i in range(len(level_2_hashes)):
                a = []
                slots_2d.append(a)
                level_2_hash = level_2_hashes[i]
                if level_2_hash != None:
                    for _ in range(level_2_hash.m):
                        a.append(-1)
                    
            for key in keys:
                hash_value1 = level_1_hash(key)
                hash_value2 = level_2_hashes[hash_value1](key)
                self.assertTrue(slots_2d[hash_value1][hash_value2] == -1)
                slots_2d[hash_value1][hash_value2] = key
        
if __name__ == '__main__':
    unittest.main()
