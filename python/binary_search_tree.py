import unittest
import random

from utility import binary_tree_node, binary_tree

'''
binary search tree with following opeartiopns:
insert, search, delete, maximum, minimum, predecessor, successor
'''

class binary_search_tree_node(binary_tree_node):
    def __init__(self, tree, key):
        super().__init__(tree)
        self.key = key
    
    def get_key(self):
        return self.key
    
    def __str__(self):
        return str(self.key)

class binary_search_tree(binary_tree):
    def __init__(self):
        super().__init__()
        
    def insert(self, key):
        z = binary_search_tree_node(self, key)
        y = None
        x = self.root
        while x != None:
            y = x
            if z.get_key() < x.get_key():
                x = x.left
            else:
                x = x.right
        z.parent = y
        if y == None:
            self.root = z
        elif z.get_key() < y.get_key():
            y.left = z
        else:
            y.right = z
            
        return z
    
    def transplant(self, u, v):
        if u.parent == None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        
        if v != None:
            v.parent = u.parent
            
    def delete_by_node(self, z):
        if z.left == None:
            self.transplant(z, z.right)
        elif z.right == None:
            self.transplant(z, z.left)
        else:
            y = self.minimum(z.right)
            if y.parent != z:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            self.transplant(z, y)
            y.left = z.left
            y.left.parent = y          
            
    def delete(self, key):
        z = self.search(key)
        if z == None:
            return
            
        self.delete_by_node(z)
    
    def search(self, key):
        return self.search_aux(self.root, key)
    
    def search_aux(self, x, key):
        if x == None or key == x.get_key():
            return x
        if key < x.get_key():
            return self.search_aux(x.left, key)
        else:
            return self.search_aux(x.right, key)
        
    def minimum(self,  x):
        while x.left != None:
            x = x.left
        return x
        
    def maximum(self, x):
        while x.right != None:
            x = x.right
        return x
    
    def successor(self, x):
        if x.right != None:
            return self.minimum(x.right)
        y = x.parent
        while y != None and x == y.right:
            x = y
            y = y.parent
            
        return y
        
    def predecessor(self, x):
        if x.left != None:
            return self.maximum(x.left)
        y = x.parent
        while y != None and x == y.left:
            x = y
            y = y.parent
            
        return y
    
    def get_printed_tree(self):
        if self.root != None:
            return self.root.get_printed_tree()
        else:
            return ''
        
class binary_search_tree_test(unittest.TestCase):    
    def inorder(self, node, result):  
        if node == None:
            return
        self.inorder(node.left, result)
        result.append(node.get_key())
        self.inorder(node.right, result)
    
    def test_insert(self):
        test_count = 30
        for _ in range(test_count):
            t = binary_search_tree()
            count = 100
            for i in range(count):
                t.insert(random.randint(1, 99))
            
            self.check_bst_property(t)      
        
    def test_delete(self):
        test_count = 30
        for _ in range(test_count):
            t = binary_search_tree()
            count = 30
            min = 1
            max = 30
            for i in range(count):
                n = random.randint(min, max)
                t.insert(n)
                
            for i in range(count):
                t.delete(random.randint(min, max))
                    
            self.check_bst_property(t)
            
    def check_bst_property(self, t):
        inorder_result = []
        self.inorder(t.root, inorder_result)
        for i in range(1, len(inorder_result)):
            self.assertTrue(inorder_result[i] >= inorder_result[i-1])
        
    def test_min_max(self):  
        test_count = 100

        for _ in range(test_count):
            min_value = 99999999
            max_value = 0
            node_count = 30
            t = binary_search_tree()
            for _ in range(node_count):
                n = random.randint(1, 1000)
                min_value = min(min_value,  n)
                max_value = max(max_value,  n)
                t.insert(n)
                
            self.assertTrue(t.minimum(t.root).get_key() == min_value)
            self.assertTrue(t.maximum(t.root).get_key() == max_value)
            
    def test_successor(self):
        test_count = 100
        for _ in range(test_count):
            node_count = 30
            t = binary_search_tree()
            node_list = []
            for _ in range(node_count):
                n = random.randint(1, 1000)
                t.insert(n)
                node_list.append(n)
            
            node_list.sort()
            node_list_from_tree = []
                     
            current_node = t.minimum(t.root)    
            while current_node != None:
                node_list_from_tree.append(current_node.get_key())
                current_node = t.successor(current_node)
                
            for i in range(len(node_list)):
                self.assertTrue(node_list[i] == node_list_from_tree[i])
                
    def test_predecessor(self):
        test_count = 100
        for _ in range(test_count):
            node_count = 30
            t = binary_search_tree()
            node_list = []
            for _ in range(node_count):
                n = random.randint(1, 1000)
                t.insert(n)
                node_list.append(n)
            
            node_list.sort()
            node_list_from_tree = []
                     
            current_node = t.maximum(t.root)    
            while current_node != None:
                node_list_from_tree.insert(0, current_node.get_key())
                current_node = t.predecessor(current_node)
                
            for i in range(len(node_list)):
                self.assertTrue(node_list[i] == node_list_from_tree[i])
                
    def test_print(self):
        t = binary_search_tree()
        count = 10
        for i in range(count):
            t.insert(random.randint(1, 99))
        
        t.get_printed_tree()
        #print(t.get_printed_tree()) 
                
if __name__ == '__main__':
    unittest.main()
