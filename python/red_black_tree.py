import unittest
import random
from binary_search_tree import binary_search_tree_node, binary_search_tree
    
'''
red black tree with insert, delete, search, min opeartions
'''

class red_black_tree_node (binary_search_tree_node): 
    def __init__(self, tree, key):
        super().__init__(tree, key)
        self.color = 'b'
        self.parent = tree.null
        
    def __str__(self):
        return str(self.key) + '(' + self.color + ')'

class red_black_tree(binary_search_tree):
    def __init__(self):
        super().__init__()
        null = red_black_tree_node(self, None)  
        self.set_null(null)
        null.left = null
        null.right = null
        null.parent = null
        self.root = null
        
    def search(self, key):
        return self.search_node(key, self.root)
        
    def search_node(self, key, node):
        if node == self.null:
            return self.null
            
        if node.get_key() == key:
            return node
        elif node.get_key() > key:
            return self.search_node(key, node.left)
        else:
            return self.search_node(key, node.right)
        
    def min(self, node):
        while node.left != self.null:
            node = node.left
        return node
        
    def left_rotate(self, x):
        y = x.right
        x.right = y.left
        if y.left != self.null:
            y.left.parent = x
        y.parent = x.parent
        if x.parent == self.null:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left= x
        x.parent = y
        
    def right_rotate(self, x):
        y = x.left
        x.left = y.right
        if y.right!= self.null:
            y.right.parent = x
        y.parent = x.parent
        if x.parent == self.null:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right= x
        x.parent = y        
        
    def insert_no_fixup(self, z):
        y = self.null
        x = self.root
        while x != self.null:
            y = x
            if z.get_key() < x.get_key():
                x = x.left
            else:
                x = x.right
        z.parent = y
        if y == self.null:
            self.root = z
        elif z.get_key() < y.get_key():
            y.left = z
        else:
            y.right = z
        z.left = self.null
        z.right = self.null
        z.color = 'r'
        
    def insert(self, z):
        self.insert_no_fixup(z)
        self.insert_fixup(z)
        
    def insert_fixup(self, z):
        while z.parent.color == 'r':
            if z.parent == z.parent.parent.left:
                y = z.parent.parent.right
                if y.color == 'r':
                    z.parent.color = 'b'
                    y.color = 'b'
                    z.parent.parent.color = 'r'
                    z = z.parent.parent
                else:
                    if z == z.parent.right:
                        z = z.parent
                        self.left_rotate(z)
                    z.parent.color = 'b'
                    z.parent.parent.color = 'r'
                    self.right_rotate(z.parent.parent)
            else:
                y = z.parent.parent.left
                if y.color == 'r':
                    z.parent.color = 'b'
                    y.color = 'b'
                    z.parent.parent.color = 'r'
                    z = z.parent.parent
                else:
                    if z == z.parent.left:
                        z = z.parent
                        self.right_rotate(z)
                    z.parent.color = 'b'
                    z.parent.parent.color = 'r'
                    self.left_rotate(z.parent.parent)                       
        self.root.color = 'b'
        
    def transplant(self, u, v):
        if u.parent == self.null:
            self.root = v
        elif u == u.parent.left:
            u.parent.left= v
        else:
            u.parent.right = v
        v.parent = u.parent
        
    def delete(self, z):
        y = z
        y_original_color = z.color

        if z.left == self.null:
            x = z.right
            self.transplant(z, z.right)
        elif z.right == self.null:
            x = z.left
            self.transplant(z, z.left)
        else:
            y = self.min(z.right)
            y_original_color = y.color
            x = y.right
            if y.parent == z:
                x.parent = y
            else:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            self.transplant(z, y)
            y.left = z.left
            y.left.parent = y        
            y.color = z.color
        if y_original_color == 'b':
            self.delete_fixup(x)
            
        # 1. in x.parent = y, x can be null, which set null parent to non-null
        # 2. set null parent is mandatory for the use in delete_fixup(x), x may be passed in null
        self.null.parent = self.null
            
    def delete_fixup(self, x):
        while x != self.root and x.color == 'b':
            if x == x.parent.left:
                w = x.parent.right
                if w.color == 'r':
                    w.color = 'b'
                    x.parent.color = 'r'
                    self.left_rotate(x.parent)
                    w = x.parent.right
                if w.left.color == 'b' and w.right.color == 'b':
                    w.color = 'r'
                    x = x.parent
                else:
                    if w.right.color == 'b':
                        w.left.color = 'b'
                        w.color = 'r'
                        self.right_rotate(w)
                        w = x.parent.right
                    w.color = x.parent.color
                    x.parent.color = 'b'
                    w.right.color = 'b'
                    self.left_rotate(x.parent)
                    x = self.root
            else:
                w = x.parent.left
                if w.color == 'r':
                    w.color = 'b'
                    x.parent.color = 'r'
                    self.right_rotate(x.parent)
                    w = x.parent.left
                if w.right.color == 'b' and w.left.color == 'b':
                    w.color = 'r'
                    x = x.parent
                else:
                    if w.left.color == 'b':
                        w.right.color = 'b'
                        w.color = 'r'
                        self.left_rotate(w)
                        w = x.parent.left
                    w.color = x.parent.color
                    x.parent.color = 'b'
                    w.left.color = 'b'
                    self.right_rotate(x.parent)
                    x = self.root
        x.color = 'b'              

def examine_red_black_tree_property(rb_tree):
    black_count = 0
    #1
    def check1(node):
        if node == rb_tree.null:
            return True
            
        if check1(node.left) == False:
            return False
        if node.color != 'r' and node.color != 'b':
            return False
        if check1(node.right) == False:
            return False 
    if check1(rb_tree.root) == False:
        return False
    #2
    if rb_tree.root.color != 'b':
        return False
    #4
    def check4(node):
        if node == rb_tree.null:
            return True
            
        if check4(node.left) == False:
            return False
        if node.color == 'r':
            if node.left.color == 'r' or node.right.color == 'r': 
                return False
                
        if check4(node.right) == False:
            return False
        
    if check4(rb_tree.root) == False:
        return False
    
    #5
    def check5(node, black_count_param):
        nonlocal black_count
        if node == rb_tree.null:
            if black_count == -1:
                black_count = black_count_param
                return True
            else:
                if black_count == black_count_param:
                    return True
                else:
                    return False
                    
        if node.color == 'b':
            black_count += 1
        
        if check5(node.left, black_count) == False:
            return False
        if check5(node.right, black_count) == False:
            return False
            
        return True
        
    black_count = -1
    if check5(rb_tree.root, 0) == False:
        return False
       
    return True

class red_black_tree_test(unittest.TestCase):    
    def test_insert(self):
        test_count = 100

        for j in range(test_count):
            rb_tree = red_black_tree()
            node_count = 30
            for i in range(node_count):
                n = red_black_tree_node(rb_tree, random.randint(1, 99))
                rb_tree.insert(n)
            self.assertTrue(examine_red_black_tree_property(rb_tree))
            
    def test_delete(self):
        test_count = 1000

        for j in range(test_count):
            rb_tree = red_black_tree()
            node_count = 30
            for i in range(node_count):
                n = red_black_tree_node(rb_tree, random.randint(1, 99))
                rb_tree.insert(n)
                
            self.assertTrue(examine_red_black_tree_property(rb_tree))
                
            for i in range(node_count * 3):
                key = random.randint(1, 99)
                n = rb_tree.search(key)
                if n != rb_tree.null:
                    rb_tree.delete(n)
            self.assertTrue(examine_red_black_tree_property(rb_tree))
            
    def test_print(self):
        rb_tree = red_black_tree()
        node_count = 10
        for i in range(node_count):
            n = red_black_tree_node(rb_tree, random.randint(1, 99))
            rb_tree.insert(n)
        
        rb_tree.get_printed_tree()
        #print(rb_tree.get_printed_tree()) 

if __name__ == '__main__':
    unittest.main()

