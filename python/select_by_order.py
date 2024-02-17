import unittest
from utility import random_seed
import sys
import random
from sort import insert_sort

'''
Select nth element in random elements array in O(n) time
'''

def get_maximum(input):
    if len(input) == 0:
        return None
    
    maximum = input[0]
    for i in range(1, len(input)):
        maximum = max(maximum, input[i])
        
    return maximum
    
def get_minimum(input):
    if len(input) == 0:
        return None
    
    minimum = input[0]
    for i in range(1, len(input)):
        minimum = min(minimum, input[i])
        
    return minimum
    
def get_maximum_minimum(input):
    if len(input) == 0:
        return None, None
    
    if len(input) == 1:
        return input[0], input[0]
    
    last = None
    if len(input) % 2 != 0:
        last = input[-1]
    
    maximum = -sys.maxsize
    minimum = sys.maxsize
    
    for i in range(0, len(input) - 1, 2):
        a = input[i]
        b = input[i + 1]
        
        if a < b:
            a, b = b, a
        maximum = max(maximum, a)
        minimum = min(minimum, b)
        
    if last != None:
        maximum = max(maximum, last)
        minimum = min(minimum, last)
        
    return maximum, minimum
      
def partition(input, p, r):
    x = input[r]
    i = p - 1
    for j in range(p, r):
        if input[j] <= x:
            i = i + 1
            input[i], input[j] = input[j], input[i]
            
    input[i + 1], input[r] = input[r], input[i + 1]
    return i + 1
      
def randomized_partition(input, p, r):
    i = random.randint(p, r)
    input[r], input[i] = input[i], input[r]
    return partition(input, p, r)
      
def random_select_by_order(input, order):
    if len(input) == 0:
        return None
        
    return random_select_by_order_with_range(input, 0, len(input) - 1, order)
    
def random_select_by_order_with_range(input, p, r, order):
    if p == r:
        return input[p]
        
    q = randomized_partition(input, p, r)
    k = q - p
    if order == k:
        return input[q]
    elif order < k:
        return random_select_by_order_with_range(input, p, q - 1, order)
    else:
        return random_select_by_order_with_range(input, q + 1, r, order - k - 1)        
            
def select_by_order(input, order):
    if len(input) == 0:
        return None
        
    return select_by_order_with_range(input, 0, len(input) - 1, order)
    
def select_by_order_with_range(input, p, r, order):
    if r - p == 0:
        return input[r]
        
    groups = []
    group = []
    count = 0
    
    # step 1. deivide into n/5 groups
    for i in range(r - p + 1):
        group.append(input[i])
        count += 1
        if count == 5:
            groups.append(group)
            count = 0
            group = []
            
    if len(group) != 0:
        groups.append(group)
        
    # step2. find median of each n/5 groups by insertion sort
    for group in groups:
        insert_sort(group)
        
    # step 3 find median of medians
    medians = []
    for group in groups:
        medians.append(group[len(group) // 2])
        
    median_of_medians = select_by_order(medians, len(medians) // 2)
    
    # step 4 partition arround the median-of-medians
    for i in range(p, r + 1):
        if input[i] == median_of_medians:
            input[i], input[r] = input[r], input[i]
            break
            
    q = partition(input, p, r)
    
    # step 5
    k = q - p
    if order == k:
        return input[q]
    elif order < k:
        return select_by_order_with_range(input, p, q - 1, order)
    else:
        return select_by_order_with_range(input, q + 1, r, order - k - 1)   
        
            
class order_statistics_test(unittest.TestCase):
    def test1(self):
        for _ in range(100):
            random_seed(False)
            input = []
            input2 = []
            size = random.randint(0, 10)
            for _2 in range(size):
                x = random.randint(-sys.maxsize + 1,  sys.maxsize - 1)
                input.append(x)
                input2.append(x)
                
            input.sort()
            if size == 0:
                self.assertTrue(None == get_maximum(input2))
                self.assertTrue(None == get_minimum(input2))
                self.assertTrue((None, None) == get_maximum_minimum(input2))
            else:
                self.assertTrue(input[-1] == get_maximum(input2))
                self.assertTrue(input[0] == get_minimum(input2))
                self.assertTrue((input[-1], input[0]) == get_maximum_minimum(input2))
                
    def test2(self):
        for _ in range(100):
            random_seed(False)
            input = []
            input2 = []
            size = random.randint(0, 10)
            for _2 in range(size):
                x = random.randint(-sys.maxsize + 1,  sys.maxsize - 1)
                input.append(x)
                input2.append(x)
                
            input.sort()
            if size == 0:
                self.assertTrue(None == random_select_by_order(input2, 0))
            else:
                for i in range(size):
                    self.assertTrue(input[i] == random_select_by_order(input2, i))
                    
    def test3(self):
        for _ in range(50):
            random_seed(False)
            input = []
            input2 = []
            size = random.randint(0, 50)
            for _2 in range(size):
                x = random.randint(-sys.maxsize + 1,  sys.maxsize - 1)
                input.append(x)
                input2.append(x)
                
            input.sort()
            if size == 0:
                self.assertTrue(None == select_by_order(input2, 0))
            else:
                for i in range(size):
                    self.assertTrue(input[i] == select_by_order(input2, i))
        
if __name__ == '__main__':
    unittest.main()
