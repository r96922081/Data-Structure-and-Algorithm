from collections import deque
from enum import Enum
import unittest
import sys

'''
1. Heapsort by heap
2. priority queue with insert and extract operations
'''

class heaptype(Enum):
    max = 1
    min = 2

class heap():
    def __init__(self, type):
        self.A = []
        self.A.append(-1) # root starts from 1
        self.heapsize = 0
        self.type = type
        
    def insert(self, key, element):
        n = heap_node(key, element)
        self.A.append(n)
        self.heapsize += 1
        # starts from 1
        n.heap_index = self.heapsize
        return n
        
    def parent(self, i):
        return i//2
        
    def left(self, i):
        return i * 2
        
    def has_left(self, i):
        if self.left(i) <= self.heapsize:
            return True
        else:
            return False
            
    def has_right(self, i):
        if self.right(i) <= self.heapsize:
            return True
        else:
            return False        
        
    def right(self,  i):
        return i * 2 + 1
        
    def heapify(self, i):
        left = self.left(i)
        right = self.right(i)
        
        if self.type == heaptype.max:
            if left <= self.heapsize and self.A[left].key > self.A[i].key:
                largest = left
            else:
                largest = i
            if right <= self.heapsize and self.A[right].key > self.A[largest].key:
                largest = right
        else:
            if left <= self.heapsize and self.A[left].key < self.A[i].key:
                largest = left
            else:
                largest = i
            if right <= self.heapsize and self.A[right].key < self.A[largest].key:
                largest = right            
            
        if largest != i:
            self.exchange_place(i, largest)
            self.heapify(largest)
            
    def exchange_place(self, index_1, index_2):
        self.A[index_1].heap_index, self.A[index_2].heap_index = self.A[index_2].heap_index, self.A[index_1].heap_index
        self.A[index_1], self.A[index_2] = self.A[index_2], self.A[index_1]        
        
            
    def build_heap(self):
        for i in range(self.heapsize//2, 0, -1):
            self.heapify(i)
        
    def get_indention(self, indentions, node, indention_count, keysize):
        if self.has_left(node):
            indention_count = self.get_indention(indentions, self.left(node), indention_count, keysize)
            
        indentions[node] = indention_count
        indention_count += keysize
        
        if self.has_right(node):
            indention_count = self.get_indention(indentions, self.right(node), indention_count, keysize)
            
        return indention_count
        
    def __str__(self):
        ret = ''
        indentions = []
        last_node_for_its_level = []
        for i in self.A:
            indentions.append(-1)
            last_node_for_its_level.append(False)
            
        keysize = 0
        for node in self.A[1:]:
            keysize = max(keysize, len(str(node)))
            
        self.get_indention(indentions, 1, 0, keysize)
        nodes= deque([])
        nodes.append((1, 1))
        
        indention_count = 0        
        while len(nodes) != 0:
            node_level = nodes.popleft()
            node = node_level[0]
            level = node_level[1]
            value = str(self.A[node])

            last_in_this_level = False
            if len(nodes) == 0 or level != nodes[0][1]:
                last_in_this_level = True

            for i in range(indentions[node]  - indention_count) :
                ret += ' '
                indention_count += 1   
            
            ret += value
            indention_count += keysize
            
            if last_in_this_level:
                ret += '\n'
                indention_count = 0
            
            if self.has_left(node):
                nodes.append((self.left(node), level + 1))
            if self.has_right(node):
                nodes.append((self.right(node), level + 1)) 
                
        return ret
                
    def heapsort(self):
        self.build_heap()
        original_heapsize = self.heapsize
        for i in range(original_heapsize, 1, -1):
            self.exchange_place(1, i)
            self.heapsize -= 1
            self.heapify(1)
        self.heapsize = original_heapsize
        
    def __len__(self):
        return len(self.A) - 1
        
class priority_queue(heap):
    def __init__(self, type, dummy_max, dummy_min):
        super().__init__(type)
        self.dummy_max = dummy_max
        self.dummy_min = dummy_min
        
    def insert(self, key, element):
        if self.type == heaptype.max:
            n = super().insert(self.dummy_min, element)
            self.increase_key_by_index(self.heapsize, key)
        else:
            n = super().insert(self.dummy_max, element)
            self.decrease_key_by_index(self.heapsize, key)
        return n
       
    def increase_key_by_node(self, node, key):
        self.increase_key_by_index(node.heap_index, key)
        
    def increase_key_by_index(self, i, key):
        if key < self.A[i].key:
            raise Exception('increase key error')
        self.A[i].key = key
        while i > 1 and self.A[self.parent(i)].key < self.A[i].key:
            super().exchange_place(i, self.parent(i))
            i = self.parent(i)

    def decrease_key_by_node(self, node, key):
        self.decrease_key_by_index(node.heap_index, key)

    def decrease_key_by_index(self, i, key):        
        if key > self.A[i].key:
            raise Exception('decrease key error')
        self.A[i].key = key
        while i > 1 and self.A[self.parent(i)].key > self.A[i].key:
            super().exchange_place(i, self.parent(i))
            i = self.parent(i)            
        
    def extract(self):
        if self.heapsize < 1:
            raise Exception('heap underflow')
        key = self.A[1]
        self.A[1] = self.A[self.heapsize]
        self.A[1].heap_index = 1
        self.A.pop()
        self.heapsize -= 1
        self.heapify(1)
        return key
    
class heap_node():
    def __init__(self, key, element):
        self.key = key
        self.element = element
        self.heap_index = -1
        
    def __str__(self):
        return str(self.element)
    
class heap_test(unittest.TestCase):        
    def _test_demo(self):
        print('==========')
        h = heap(heaptype.max)
        for i in range(1, 7, 1):
            h.insert(i, i)
        h.build_heap()
        print(h)
        h.heapsort()
        print(h)
   
        print('==========')
        q = priority_queue(heaptype.min, sys.maxsize, -sys.maxsize + 1)
        for i in range(6):
            q.insert(i, i)

        for i in range(10, 5, -1):
            q.insert(i, i)
            
        while q.heapsize > 0:
            print(q.extract(),  end = ', ')
        print('\n============') 
        
    def test_heapsort(self):
        h = heap(heaptype.max)
        for i in range(1, 7, 1):
            h.insert(i, i)
        h.build_heap()
        h.heapsort()
        
        for i in range(1, h.heapsize):
            self.assertTrue(h.A[i].key < h.A[i + 1].key)
            
        h = heap(heaptype.min)
        for i in range(7, 0, -1):
            h.insert(i, i)
        h.build_heap()
        h.heapsort()    
        for i in range(1, h.heapsize):
            self.assertTrue(h.A[i].key > h.A[i + 1].key)
            self.assertTrue(i == h.A[i].heap_index)  
        
    def test_priorityqueue(self):
        q = priority_queue(heaptype.max, sys.maxsize, -sys.maxsize + 1)
        for i in range(6):
            q.insert(i, i)

        for i in range(10, 5, -1):
            q.insert(i, i)
            
        prev = heap_node(sys.maxsize, sys.maxsize)
        while q.heapsize > 0:
            current = q.extract()
            self.assertTrue(current.key < prev.key)
            prev = current
        
        q = priority_queue(heaptype.min, sys.maxsize, -sys.maxsize + 1)
        for i in range(6):
            q.insert(i, i)

        for i in range(10, 5, -1):
            q.insert(i, i)
            
        prev = heap_node(-sys.maxsize - 1, -sys.maxsize - 1)
        while q.heapsize > 0:
            current = q.extract()
            self.assertTrue(current.key > prev.key)
            prev = current
        
if __name__ == '__main__':
    unittest.main()
        


