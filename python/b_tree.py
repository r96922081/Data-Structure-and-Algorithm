import unittest
import random
import sys

'''
b-tree with search & insert operation
'''

class btree_node:
    def __init__(self, t):
        self.t = t
        self.keys = []
        self.children = []
        self.leaf = True

    def insert_key(self, key):
        self.keys.append(key)

    def insert_keys(self, keys):
        for key in keys:
            self.keys.append(key)
        
    def add_child(self, child):
        self.children.append(child)
        self.leaf = False

    def add_children(self, children):
        for child in children:
            self.children.append(child)
        self.leaf = False
        
    def key_len(self):
        return len(self.keys)
        
    def children_len(self):
        return len(self.children)
        
    def __str__(self):
        ret = '['
        ret += str(self.keys[0])
        for i in range(1, len(self.keys)):
            ret += ',' + str(self.keys[i])
        ret += ']'
        return ret
        
class btree:
    def __init__(self, t):
        self.t = t
        self.root = None
        self.leaf_height_for_check = -1
    
    def create(self):
        self.root = btree_node(self.t)
        return self.root
    
    def valid(self):
        def check1(node):
            if not node.leaf and (node.key_len() + 1 != node.children_len()):
                return False
            for child in node.children:
                if check1(child) == False:
                    return False
                
        if check1(self.root) == False:
            return False
            
        def check2(node, next_value):
            i = 0
            for key in node.keys:
                if key > next_value:
                    return False
                if not node.leaf and (check2(node.children[i], key) == False):
                    return False
                i += 1
                
            if not node.leaf:
                for key2 in node.children[i].keys:     
                    if key2 < key:
                        return False                        
                if check2(node.children[i], sys.maxsize) == False:
                    return False
                
            return True
                
        if check2(self.root, sys.maxsize) == False:
            return False
            
        def check3(node, height):
            if node.leaf:
                if self.leaf_height_for_check == -1:
                    self.leaf_height_for_check = height
                else:
                    if self.leaf_height_for_check != height:
                        return False
            else:
                for child in node.children:
                    if check3(child,  height + 1) == False:
                        return False
            return True
                        
        if check3(self.root, 1) == False:
            return False     
         
        def check4(node):
            if node != self.root and node.key_len() < self.t - 1:
                return False
            if node.key_len() > self.t * 2 - 1:
                return False
            for child in node.children:
                if check4(child) == False:
                    return False            
            return True
            
        if check4(self.root) == False:
            return False   
            
        return True
        
    def print(self):
        last_node_of_this_level = self.root
        q = [self.root]
        print('')
        while len(q) != 0:
            node = q[0]
            q.pop(0)
            for child in node.children:
                q.append(child)
            print(node,  end = ' ')
            
            if node == last_node_of_this_level:
                print('')
                if not node.leaf:
                    last_node_of_this_level = node.children[node.children_len() - 1]   
              
    def search(self, key):
        node_value_pair = self.search2(self.root, key)
        if node_value_pair == None:
            return None
        else:
            node = node_value_pair[0]
            return node
        
    def search2(self, x, key):
        i = 0
        while i < x.key_len() and key > x.keys[i]:
            i += 1
        if i < x.key_len() and key == x.keys[i]:
            return (x, i)
        elif x.leaf:
            return None
        else:
            return self.search2(x.children[i], key)
            
    def split_child(self, x, i):
        z = btree_node(self.t)
        y = x.children[i]
        z.leaf = y.leaf
        for j in range(self.t - 1):
            z.insert_key(y.keys[j + self.t])
        if not y.leaf:
            for j in range(self.t):
                z.add_child(y.children[j + self.t])
        split_key = y.keys[self.t - 1]
        y.keys = y.keys[:self.t - 1]
        y.children = y.children[:self.t]
        x.children.insert(i + 1, z)
        x.keys.insert(i, split_key)
    
    def insert(self, key):
        r = self.root
        if r == None:
            node = self.create()
            node.insert_key(key)
            return
        
        if r.key_len() == self.t * 2 - 1:
            s = btree_node(self.t)
            self.root = s
            s.leaf = False
            s.add_child(r)
            self.split_child(s, 0)
            self.insert_nonfull(s, key)
        else:
            self.insert_nonfull(r, key)
    
    def insert_nonfull(self, x, key):
        i = x.key_len() - 1
        if x.leaf:
            while i >= 0 and key < x.keys[i]:
                i -= 1
            x.keys.insert(i + 1,  key)
        else:
            while i >= 0 and key < x.keys[i]:
                i -= 1
            i += 1
            if x.children[i].key_len() == self.t * 2 - 1:
                self.split_child(x, i)
                if key > x.keys[i]:
                    i += 1
            self.insert_nonfull(x.children[i], key)
                
        

class test_btree(unittest.TestCase):
    def setUp(self):
        t = 2        
        tree = btree(t)
        self.tree = tree
        
        node1 = tree.create()
        node1.insert_key(4)
 
        node2 = btree_node(t)
        node2.insert_key(2)
        
        node3 = btree_node(t)
        node3.insert_keys([6, 8])
        node1.add_children([node2, node3])
        
        node4 = btree_node(t)
        node4.insert_key(1)
        node4.leaf = True
        
        node5 = btree_node(t)
        node5.insert_key(3)
        node5.leaf = True
        node2.add_children([node4, node5])
        
        node6 = btree_node(t)
        node6.insert_key(5)
        node6.leaf = True
        
        node7 = btree_node(t)
        node7.insert_key(7)
        node7.leaf = True
        
        node8 = btree_node(t)
        node8.insert_keys([9, 10])
        node8.leaf = True    
        node3.add_children([node6, node7, node8])
    
    def tearDown(self):
        self.tree = None
    
    def test_check_properties(self):
        self.assertTrue(self.tree.valid())        

    def _test_print(self):
        self.tree.print() 
        
    def test_search(self):
        node = self.tree.search(10)
        self.assertTrue(node.key_len() == 2)
        self.assertTrue(node.keys[0] == 9)
        self.assertTrue(node.keys[1] == 10)
        
        node = self.tree.search(4)
        self.assertTrue(node.key_len() == 1)
        self.assertTrue(node.keys[0] == 4)

        node = self.tree.search(3)
        self.assertTrue(node.key_len() == 1)
        self.assertTrue(node.keys[0] == 3)
        
        node = self.tree.search(999)
        self.assertTrue(node == None)
        
    def test_split1(self):
        t = 3        
        tree = btree(t)
        
        node1 = tree.create()
        node1.insert_key(6)
 
        node2 = btree_node(t)
        node2.insert_keys([1, 2, 3, 4, 5])
        node2.leaf = True

        node3 = btree_node(t)
        node3.insert_keys([7, 8])
        node3.leaf = True    
     
        node1.add_children([node2, node3])
        tree.split_child(node1, 0)
        
        self.assertTrue(node1.key_len() == 2)
        self.assertTrue(node1.keys[0] == 3)
        self.assertTrue(node1.keys[1] ==6)
        self.assertTrue(node1.leaf == False)
        
        node2 = node1.children[0]
        self.assertTrue(node2.key_len() == 2)
        self.assertTrue(node2.keys[0] == 1)
        self.assertTrue(node2.keys[1] ==2)   
        self.assertTrue(node2.leaf == True)
   
        node3 = node1.children[1]
        self.assertTrue(node3.key_len() == 2)
        self.assertTrue(node3.keys[0] == 4)
        self.assertTrue(node3.keys[1] ==5)   
        self.assertTrue(node3.leaf == True)  
        
        node4 = node1.children[2]
        self.assertTrue(node4.key_len() == 2)
        self.assertTrue(node4.keys[0] == 7)
        self.assertTrue(node4.keys[1] ==8) 
        self.assertTrue(node4.leaf == True)
        
        self.assertTrue(tree.valid())
        
    def test_split2(self):
        t = 2        
        tree = btree(t)
        
        node1 = tree.create()
        node1.insert_key(8)
 
        node2 = btree_node(t)
        node2.insert_keys([2, 4,6])

        node3 = btree_node(t)
        node3.insert_keys([10, 12])
     
        node1.add_children([node2, node3])
        
        node4 = btree_node(t)
        node4.insert_key(1) 
        node5 = btree_node(t)
        node5.insert_key(3)         
        node6 = btree_node(t)
        node6.insert_key(5)         
        node7 = btree_node(t)
        node7.insert_key(7) 
        
        node2.add_children([node4, node5, node6, node7])
        
        node8 = btree_node(t)
        node8.insert_key(9) 
        node9 = btree_node(t)
        node9.insert_key(11)         
        node10 = btree_node(t)
        node10.insert_key(13)   
        node3.add_children([node8, node9, node10])
        
        self.assertTrue(tree.valid())
        tree.split_child(node1, 0)
        self.assertTrue(tree.valid())
        
        self.assertTrue(node1.key_len() == 2)
        self.assertTrue(node1.keys[0] == 4)
        self.assertTrue(node1.keys[1] == 8)
        
        node2 = node1.children[0]
        self.assertTrue(node2.key_len() == 1)
        self.assertTrue(node2.keys[0] == 2)
        node4 = node2.children[0]
        self.assertTrue(node4.key_len() == 1)  
        self.assertTrue(node4.keys[0] == 1)   
   
        node3 = node1.children[1]
        self.assertTrue(node3.key_len() == 1)
        self.assertTrue(node3.keys[0] == 6) 
        node5 = node3.children[1]
        self.assertTrue(node5.key_len() == 1)  
        self.assertTrue(node5.keys[0] == 7) 
        
    def test_insert1(self):
        for t in range(2, 5):   
            tree = btree(t)
            for i in range(50):
                tree.insert(i)

            self.assertTrue(tree.valid())
            
    def test_insert2(self):
        for t in range(2, 5):   
            tree = btree(t)
            for i in range(50):
                tree.insert(random.randint(0, 100))

            self.assertTrue(tree.valid())

if __name__ == '__main__':
    unittest.main()
