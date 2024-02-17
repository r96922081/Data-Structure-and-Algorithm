import unittest
from red_black_tree import red_black_tree_node, red_black_tree, examine_red_black_tree_property
import random
import sys
from utility import random_seed

'''
Demo how to agument data structure
1. dynamic order tree augmenting red-black tree
2. interval tree augmenting red-black tree
'''

class dynamic_order_tree_node(red_black_tree_node):
    def __init__(self, tree, key):
        super().__init__(tree, key)
        self.size = 0
        
    def get_key(self):
        return self.key
        
    def __lt__(self, other):
        if self.get_key() < other.get_key():
            return True
        else:
            return False
            
    def __str__(self):
        ret = ''
        ret += str(self.get_key()) + '(' + str(self.size) + ')'
        return ret
        
    def __repr__(self):
        return self.__str__()
        
class dynamic_order_tree(red_black_tree):
    def __init__(self):
        super().__init__()
        
        null = dynamic_order_tree_node(self, None)  
        self.set_null(null)
        null.left = null
        null.right = null
        null.parent = null
        self.root = null
        
    def insert(self, z):
        super().insert_no_fixup(z)
        
        y = z
        while y != self.null:
            y.size += 1
            y = y.parent
            
        super().insert_fixup(z)
        
    def left_rotate(self, x):
        y = x.right
        if y != self.null:
            y.size = x.size
            
        super().left_rotate(x)
            
        x.size = 1
        if x.left != self.null:
            x.size += x.left.size
        if x.right != self.null:
            x.size += x.right.size
            
    def right_rotate(self, x):
        y = x.left
        if y != self.null:
            y.size = x.size
            
        super().right_rotate(x)
            
        x.size = 1
        if x.left != self.null:
            x.size += x.left.size
        if x.right != self.null:
            x.size += x.right.size     

    def decrease_size(self, z):
        if z == self.null:
            return
        
        y = z
        while y != self.null:
            y.size -= 1
            y = y.parent    
        
    def delete(self, z):
        if z.left == self.null or z.right == self.null:
            self.decrease_size(z)
        else:
            y = self.min(z.right)
            self.decrease_size(y)
            
        super().delete(z)
           
    def transplant(self, u, v):
        v.size = u.size
        super().transplant(u, v)
        
    def select(self, index):        
        return self.select_with_node(self.root, index)
        
    def select_with_node(self, x, i):
        if i < 1:
            return self.null
        elif x.size < i:
            return self.null
        
        r = x.left.size + 1
        if i == r:
            return x
        elif i < r:
            return self.select_with_node(x.left, i)
        else:
            return self.select_with_node(x.right, i - r)
            
    def rank(self, x):
        r = x.left.size + 1
        y = x
        while y != self.root:
            if y == y.parent.right:
                r = r + y.parent.left.size + 1
            y = y.parent
            
        return r

def examine_dynamic_order_tree_property(tree):
    if tree.root == tree.null:
        return True
    
    if examine_red_black_tree_property(tree) == False:
        return False
        
    def check_size(node):
        size = 1
        if node.left != tree.null:
            size += node.left.size
        if node.right != tree.null:
            size += node.right.size
            
        if node.size != size:
            return False
            
        if node.left != tree.null:
            if check_size(node.left) == False:
                return False
        if node.right != tree.null:
            if check_size(node.right) == False:
                return False
                
        return True
        
    return check_size(tree.root)
        
class interval_tree_node(red_black_tree_node):
    def __init__(self, tree, low, high):
        super().__init__(tree, low)
        self.low = low
        self.high = high
        self.max = high
        
    def get_key(self):
        return self.key
        
    def __lt__(self, other):
        if self.get_key() < other.get_key():
            return True
        else:
            return False
            
    def update_max(self):
       self.max = max(self.max, self.left.max, self.right.max)
       
    def reset_max(self):
        self.max = self.high
        self.update_max()
            
    def __str__(self):
        return '[' + str(self.low)  + ',' + str(self.high)+ '](' + str(self.max) + ')'
        
    def __repr__(self):
        return self.__str__()

class interval_tree(red_black_tree):
    def __init__(self):
        super().__init__()
        
        null = interval_tree_node(self, -sys.maxsize, -sys.maxsize)  
        self.set_null(null)
        null.left = null
        null.right = null
        null.parent = null
        self.root = null
        
    def reset_max_all_the_way_to_root(self, x):
        while x != self.null:
            x.reset_max()
            x = x.parent
        
    def insert(self, z):
        super().insert_no_fixup(z)
        self.reset_max_all_the_way_to_root(z)        
        super().insert_fixup(z)
        
    def left_rotate(self, x):
        super().left_rotate(x)
        x.reset_max()
        x.parent.reset_max()
            
    def right_rotate(self, x):
        super().right_rotate(x)
        x.reset_max()
        x.parent.reset_max()
        
    def delete(self, z):
        if z.left == self.null or z.right == self.null:
            self.reset_max_all_the_way_to_root(z)
        else:
            y = self.min(z.right)
            self.reset_max_all_the_way_to_root(y)
            
        super().delete(z)
           
    def transplant(self, u, v):
        v.max = u.max
        super().transplant(u, v)
        
    def search_interval(self, i):
        x = self.root
        while x != self.null and (i.high < x.low or x.high < i.low):
            if x.left != self.null and x.left.max >= i.low:
                x = x.left
            else:
                x = x.right
        return x
        
    def internal_search_multiple_interval(self, x, i, ret):
        if i.low <= x.high and x.low <= i.high:
            ret.append(x)
            
        if x.left != self.null and x.left.max >= i.low:
            self.internal_search_multiple_interval(x.left, i, ret)
            
        if x.right != self.null and x.right.max >= i.low:
            self.internal_search_multiple_interval(x.right, i, ret)      
        
    # it's not asympotatically fast than brute force
    def search_multiple_interval(self, i):
        ret = []
        self.internal_search_multiple_interval(self.root, i, ret)
        return ret


def examine_interval_tree_property(tree):
    if tree.root == tree.null:
        return True
    
    if examine_red_black_tree_property(tree) == False:
        return False
        
    check_result = True
        
    def check_max(node):
        nonlocal check_result
        if node == tree.null:
            return -sys.maxsize
            
        left_max = check_max(node.left)
        right_max = check_max(node.right)
        if node.max != max([node.max, left_max, right_max]):
            check_result = False
        
        return node.max
        
    check_max(tree.root)
        
    return check_result

class dynamic_order_tree_test(unittest.TestCase):
    def test_insert(self):
        test_count = 100
        for _ in range(test_count):
            random_seed(False)
            tree = dynamic_order_tree()
            node_count = 100
            for i in range(node_count):
                n = dynamic_order_tree_node(tree, random.randint(1, 99))
                tree.insert(n)

            #print(tree.get_printed_tree())
            self.assertTrue(examine_dynamic_order_tree_property(tree))
        
    def test_delete(self):
        test_count = 100
        for _ in range(test_count):
            random_seed(False)      
            tree = dynamic_order_tree()
            node_count = 10
            for i in range(node_count):
                n = dynamic_order_tree_node(tree, random.randint(1, 99))
                tree.insert(n)
                
            for i in range(node_count * 5):
                key = random.randint(1, 99)
                n = tree.search(key)
                if n != tree.null:
                    tree.delete(n)
                    
            self.assertTrue(examine_dynamic_order_tree_property(tree))
            
    def test_select(self):
        test_count = 100
        for _ in range(test_count):
            random_seed(False)
            tree = dynamic_order_tree()
            node_count = 100
            a = []
            shuffle_list = []
            for i in range(node_count):
                a.append(i + 1)
                
            while len(a) > 0:
                i = random.randint(0, len(a) - 1)
                shuffle_list.append(a[i])
                del a[i]
            
            for i in shuffle_list:
                tree.insert(dynamic_order_tree_node(tree, i))
                
            for i in range(1, node_count):
                n = tree.select(i)
                self.assertTrue(n.get_key() == i)
                
            self.assertTrue(tree.select(0) == tree.null)
            self.assertTrue(tree.select(node_count + 1) == tree.null)
            
    def test_rank(self):
        test_count = 1
        for _ in range(test_count):
            random_seed(False)
            tree = dynamic_order_tree()
            node_count = 100
            a = []
            for i in range(node_count):
                n = dynamic_order_tree_node(tree, i + 1)
                a.append(n)
                tree.insert(n)
            
            for n in a:
                self.assertTrue(tree.rank(n) == n.get_key())
  
class interval_tree_test(unittest.TestCase):
    def test_insert(self):
        test_count = 100
        for _ in range(test_count):
            random_seed(False)
            tree = interval_tree()
            node_count = 100
            for i in range(node_count):
                left = random.randint(1, 99)
                right = random.randint(1, 99)
                if right < left:
                    right, left = left, right
                n = interval_tree_node(tree, left, right)
                tree.insert(n)

            #print(tree.get_printed_tree())
            self.assertTrue(examine_interval_tree_property(tree))
            
    def test_delete(self):
        test_count = 100
        for _ in range(test_count):
            random_seed(False)    
            tree = interval_tree()
            node_count = 50
            for i in range(node_count):
                left = random.randint(1, 99)
                right = random.randint(1, 99)
                if right < left:
                    right, left = left, right
                n = interval_tree_node(tree, left, right)
                tree.insert(n)
                
            for i in range(node_count * 5):
                key = random.randint(1, 99)
                n = tree.search(key)
                if n != tree.null:
                    tree.delete(n)
                    
            #print(tree.get_printed_tree())
            self.assertTrue(examine_interval_tree_property(tree))
            
    def test_interval_search(self):
        
        class empty_class:
            pass
        
        tree = interval_tree()
        node_count = 100
        for i in range(node_count // 4):
            n = interval_tree_node(tree, i * 4, i * 4 + 1)
            tree.insert(n)
            
        for i in range(node_count):
            interval = empty_class()
            interval.low = i
            interval.high = i + 1
            if i % 4 == 2:
                self.assertTrue(tree.search_interval(interval) == tree.null)
            else:
                n = tree.search_interval(interval)
                self.assertTrue(interval.high >= n.low or interval.low <= n.high)
                
            interval = empty_class()
            interval.low =0
            interval.high = i
            
            intervals = tree.search_multiple_interval(interval)
            self.assertTrue(len(intervals) == (i // 4 + 1))
        
if __name__ == '__main__':
    unittest.main()
