import unittest
import sys
from heap import priority_queue, heaptype
from utility import binary_tree, binary_tree_node, random_seed
import random

'''
Create huffman code
'''

class huffman_node(binary_tree_node):
    def __init__(self, tree, freq, key):
        super().__init__(tree)
        self.freq = freq
        self.key = key
        self.code = ''

    def __str__(self):
        ret = '('
        ret += str(self.key)
        ret += ',' + str(self.freq)
        ret += ',' + str(self.code)
        ret += ')'
        
        return ret

def set_code(node, code):
    node.code = code
    if node.left != None:
        set_code(node.left, code + '0')
    if node.right != None:
        set_code(node.right, code + '1') 

def get_codes(huffman_root):
    huffman_code = {}
    q = [huffman_root]
    
    while len(q) != 0:
        n = q.pop()
        if n.left != None:
            q.insert(0, n.left)
        if n.right != None:
            q.insert(0, n.right)
            
        if n.key != '':
            huffman_code[n.key] = n.code
            
    return huffman_code

def get_huffman_code(data):
    huffman_tree = binary_tree()
    q = priority_queue(heaptype.min, sys.maxsize, -sys.maxsize + 1)
    for key in data:
        freq = data[key]
        q.insert(freq, huffman_node(huffman_tree, freq, key))

    n = len(data)
    
    for i in range(n - 1):
        x = q.extract()
        x2 = x.element
        y = q.extract()
        y2 = y.element  
        z = huffman_node(huffman_tree, x2.freq + y2.freq, '')
        z.set_left(x2)
        z.set_right(y2)
        q.insert(z.freq, z)
        
    z = q.extract()
    huffman_root = z.element
    set_code(huffman_root, '')
    #print(huffman_root.get_printed_tree())
    
    return get_codes(huffman_root)

class huffman_test(unittest.TestCase):
    def check_huffman_code(self, huffman_code, data):
        for key1 in huffman_code:
            for key2 in huffman_code:
                if key1 == key2:
                    continue
                
                if data[key1] < data[key2]:
                    code1 = huffman_code[key1]
                    code2 = huffman_code[key2]
                    self.assertTrue(len(code1) >= len(code2))
                    self.assertTrue(not code1.startswith(code2))
                
    
    def test1(self):
        data = {}
        data['a'] = 45
        data['b'] = 13
        data['c'] = 12
        data['d'] = 16
        data['e'] = 9
        data['f'] = 5
        
        huffman_code = get_huffman_code(data)
        self.check_huffman_code(huffman_code,  data)
        print(huffman_code)
        
    def test2(self):
        for _ in range(100):
            random_seed(False)
            data = {}
            for i in range(10):
                data[chr(97 + i)] = random.randint(1, 1000)

            huffman_code = get_huffman_code(data)
            self.check_huffman_code(huffman_code,  data)
        
if __name__ == '__main__':
    unittest.main()
