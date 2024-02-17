import unittest
import random
import sys

'''
Fibonacci heap with insert, delete, union, extract_min operations
it's faster than heap in union operation.  Fib heap run O(1). heap run O(n)
'''

class fib_heap:
    def __init__(self):
        self.min = None
        self.n = 0
        
    def insert(self, x):
        x.degree = 0
        x.p = None
        x.child = None
        x.mark = False
        if self.min == None:
            self.min = x
        else:
            self.min.concate(x)
            if x.key < self.min.key:
                self.min = x
        self.n += 1
        
    def check_min(self):
        if self.min == None:
            return True
        else:
            root_list = self.min.get_list()
            if min(root_list) == self.min:
                return True
            else:
                return False
        return True
        
    def union(self, h2):
        h1 = self
        h = fib_heap()
        h.min = h1.min
        if h1.min == None:
            return h2
        elif h2.min == None:
            return h1
            
        h.min.concate(h2.min)
        if h1.min == None or (h2.min != None and h2.min < h1.min):
            h.min = h2.min
        h.n = h1.n + h2.n
        return h
        
    def check_n(self):
        node = self.min        
        if node == None:
            if self.n == 0:
                return True
            else:
                return False
        
        root_list = node.get_list()
        expected_n = 0
        stack = []
        stack.extend(root_list)
        
        while len(stack) != 0:
            node = stack.pop()
            expected_n += 1
            if node.child != None:
                stack.extend(node.child.get_list())
                
        if expected_n == self.n:
            return True
        else:
            return False
            
        return False
        
    def check_property(self):
        ret = self.check_min()
        if ret == False:
            return False
            
        ret = self.check_n()
        if ret == False:
            return False
            
        if self.min != None:
            root_list = self.min.get_list()
            for root in root_list:
                if root.check_min_heap() == False:
                    return False
            
        return True
        
    def print(self):
        if self.min != None:
            fake = fib_heap_node(-1)
            fake.just_for_print_node = True
            root_list = self.min.get_list()
            fake.child = root_list[0]
            for root in root_list:
                root.p = fake
            fake.print()
            
    def extract_min(self):
        z = self.min
        if z != None:
            if z.child != None:
                for x in z.child.get_list():
                    x.remove_from_sibling()
                    self.min.concate(x)
                    x.p = None
            
            z_next = z.next
            z.remove_from_sibling()
            if z_next == z:
                self.min = None
            else:
                self.min = z_next
                self.consolidate()
                
            self.n -=1            
        return z
        
    def consolidate(self):
        A = []
        for _ in range(self.n + 1):
            A.append(None)
        for w in self.min.get_list():
            x = w
            d = x.degree
            while A[d] != None:
                y = A[d]
                if x.key > y.key:
                    x, y = y, x
                self.link(y, x)
                A[d] = None
                d += 1
            A[d] = x
        self.min = None
        for i in range(self.n + 1):
            if A[i] != None:
                A[i].remove_from_sibling()
                if self.min == None:
                    self.min = A[i]
                else:
                    self.min.concate(A[i])
                    if A[i] < self.min:
                        self.min = A[i]
                        
    def link(self, y, x):
        y.remove_from_sibling()
        y.set_parent(x)
        y.mark = False
        
    def delete(self, x):
        self.decrease_key(x, -sys.maxsize - 1)
        self.extract_min()
        
    def decrease_key(self, x, k):
        if k > x.key:
            raise Exception('key is greater than current key')
        x.key = k
        y = x.p
        if y != None and x.key < y.key:
            self.cut(x, y)
            self.cascading_cut(y)
        if x.key < self.min.key:
            self.min = x
            
    def cut(self, x, y):
        x.remove_from_sibling()
        self.min.concate(x)
        x.p = None
        x.mark = False
        
    def cascading_cut(self, y):
        z = y.p
        if z != None:
            if y.mark == False:
                y.mark = True
            else:
                self.cut(y, z)
                self.cascading_cut(z)                    

class fib_heap_node:
    def __init__(self, key):
        self.key = key
        self.next = self
        self.prev = self
        self.p = None
        self.child = None
        self.mark = False
        self.degree = 0
        
        # for print
        self.just_for_print_node = False
        
    def concate(self, node):
        node.prev.next = self.next
        self.next.prev = node.prev
        self.next = node
        node.prev = self
        
    def remove_from_sibling(self):
        if self.next == self:
            if self.p != None:
                self.p.degree -= 1
                self.p.child = None            
                self.p = None
        else:
            if self.p != None:
                self.p.degree -= 1
                if self.p.child == self:
                    self.p.child = self.next
                self.p = None
            self.prev.next = self.next
            self.next.prev = self.prev
            self.next = self
            self.prev = self
        
    def set_parent(self, node):
        ''' fib_heap.n will not set accordingly'''            
        if node.child == None:        
            node.child = self
        node.child.concate(self)
        self.p = node
        self.p.degree += 1

    def get_list(self):
        ret = [self]
        next = self.next
        while next != self:
            ret.append(next)
            next = next.next
            
        return ret

    def _get_print_size(self, min_size, level):
        this_size = max(len(str(self)), min_size)
        if self.child == None:
            self.print_size = this_size
            self.level = level
            return self.print_size
        
        if self.child != None:
            children = self.child.get_list()
            children_size = 0
            for child in children:
                if child == children[0]:
                    children_size += child._get_print_size(this_size, level + 1)
                else:
                    children_size += child._get_print_size(0, level + 1)   
                
        self.print_size = max(this_size,  children_size)
        self.level = level
        return self.print_size
        
    def __lt__(self, other):
        return self.key < other.key

    def ___le__(self, other):
        return self.key <= other.key

    def __gt__(self, other):
        return self.key > other.key

    def __ge__(self, other):
        return self.key >= other.key
        
    def __str__(self):
        ret = str(self.key)
        if self.mark:
            ret += '(m)'
        ret += ' '
        return ret
        
    def print(self):
        self._get_print_size(0, 0)        
        prev_node = self
        print('')
        q = [self]
        last_normal_node_level = 0
        
        while len(q) != 0:
            n = q[0]
            q.pop(0)
            
            if n.just_for_print_node == False and last_normal_node_level < n.level:
                last_normal_node_level = n.level
                
            if n.level == last_normal_node_level + 2:
                continue
                
            if prev_node.level < n.level:
                print('')
                
            prev_node = n
            
            if n.child != None:
                children = n.child.get_list()
                q.extend(children) 
            else:
                dummy = fib_heap_node(-sys.maxsize -1)
                dummy.just_for_print_node = True
                dummy.print_size = n.print_size
                dummy.level = n.level + 1
                q.append(dummy)
            
            printed_size = 0
            if not n.just_for_print_node:
                printed_size = len(str(n))
                print(n,  end='')
                last_normal_node_level = n.level
            
            for _ in range(n.print_size - printed_size):
                print(' ',  end='')

        print('')
        
    def check_min_heap2(self, n):
        if n.child == None:
            return True
        else:
            children = n.child.get_list()
            if n > min(children):
                return False

            for child in children:
                if  self.check_min_heap2(child) == False:
                    return False
                
        return True
        
    def check_degree(self):
        if self.child == None:
            if self.degree != 0:
                return False
        else:
            children = self.child.get_list()
            if len(children) != self.degree:
                return False
                
            for child in children:
                if child.check_degree() == False:
                    return False
        return True
        
    def check_min_heap(self):
        if self.check_min_heap2(self) == False:
            return False
        if self.check_degree() == False:
            return False
        return True
        
n = fib_heap_node

class fib_heap_test(unittest.TestCase):
    def test_insert(self):
        t = self.assertTrue
        f = fib_heap()
        t(f.min == None)
        n1 = n(11)
        n2 = n(2)
        f.insert(n1)
        f.insert(n2)
        t(f.n == 2)
        t(f.min == n2)
        t(n1.next == n2)
        t(n2.next == n1)
        
        f = fib_heap()
        for _ in range(10):
            f.insert(n(random.randint(0, 10)))
        t(f.check_property())
        
    def test_union(self):
        t = self.assertTrue
        f1 = fib_heap()
        f2 = fib_heap()
        f = f1.union(f2)
        t(f.check_property())
        t(f.n == 0)
        
        f1 = fib_heap()
        f1.insert(n(1))
        f2 = fib_heap()
        f1.insert(n(2))
        f = f1.union(f2) 
        t(f.check_property())
        t(f.n == 2)
        
        f1 = fib_heap()
        n1 = n(1)
        f1.insert(n1)
        n(3).set_parent(n1)
        n(4).set_parent(n1)
        f1.n = 3
        
        f2 = fib_heap()
        n2 = n(2)
        f2.insert(n2)
        n(5).set_parent(n2)
        n(6).set_parent(n2)
        f2.n = 3
        
        f = f1.union(f2) 
        t(f.check_property())
        t(f.n == 6)
        
        #f.print()
        
    def test_extract_min(self):
        t = self.assertTrue
        f = fib_heap()
        n23 = n(23)
        n7 = n(7)
        n21 = n(21)
        n3 = n(3)
        f.insert(n3)
        n18 = n(18)
        n18.set_parent(n3)
        n39 = n(39)
        n39.set_parent(n18)
        n52 = n(52)
        n52.set_parent(n3)
        n38 = n(38)
        n38.set_parent(n3)
        n41 = n(41)
        n41.set_parent(n38)
        n17 = n(17)
        n30 = n(30)
        n30.set_parent(n17)
        n24 = n(24)
        n26 = n(26)
        n26.set_parent(n24)
        n35 = n(35)
        n35.set_parent(n26)
        n46 = n(46)
        n46.set_parent(n24)
        
        n3.concate(n23)
        n3.concate(n7)
        n3.concate(n21)
        n3.concate(n17)
        n3.concate(n24)
        f.n = 15
        
        extract_count = 0
        prev_min = n(-sys.maxsize - 1)
       
        while f.min != None:
            min = f.extract_min()
            t(prev_min < min)
            t(f.check_property())
            prev_min = min
            extract_count += 1
            
        t(extract_count == 15)
            
        
    def test_extract_min2(self):
        t = self.assertTrue
        count = 100
        f = fib_heap()
        for _ in range(count):
            f.insert(n(random.randint(0, count)))
            
        extract_count = 0
        prev_min = n(-sys.maxsize - 1)
       
        while f.min != None:
            min = f.extract_min()
            t(prev_min <= min)
            t(f.check_property())
            prev_min = min
            extract_count += 1
            
        t(extract_count == count)        
            
    def test_delete(self):
        t = self.assertTrue
        
        count2 = 1
        for _ in range(count2):
            f = fib_heap()
            count = 100
            all = []
            for _ in range(count):
                n1 = n(random.randint(0, count * 10))
                f.insert(n1)
                all.append(n1)
            while len(all) != 0:
                x = all[random.randint(0, len(all) - 1)]
                f.delete(x)
                t(f.check_property())
                all.remove(x)
            
            t(f.n == 0)        
        
    def test_check_min(self):
        t = self.assertTrue
        f = fib_heap()
        t(f.check_min())
        
        n1 = n(1)
        n2 = n(2)
        n3 = n(3)
        
        f.insert(n2)
        t(f.check_min())
        f.insert(n3)
        t(f.check_min())      
        n2.concate(n1)
        t(f.check_min() == False)
        
    def test_check_n(self):
        t = self.assertTrue
        n4 = n(4)
        n5 = n(5)
        n6 = n(6)
        n7 = n(7)
        n8 = n(8)
        f = fib_heap()
      
        f.insert(n4)      
        n5.set_parent(n4)
        n6.set_parent(n4)
        n7.set_parent(n5)
        n8.set_parent(n5)

        f.n = 5
        t(f.check_n())
        f.n = 3
        t(f.check_n() == False)

class fib_heap_node_test(unittest.TestCase):
    def test_concate(self):
        t = self.assertTrue
        n = fib_heap_node
        n1 = n(1)
        n2 = n(2)
        n3 = n(3)
        
        t(n1.next == n1)
        t(n1.prev == n1)
        
        n1.concate(n2)
        t(n1.next == n2)
        t(n2.prev == n1)
        t(n1.next.next == n1)        
        t(n1.prev.prev == n1)        
        
        n3.concate(n1)
        t(n3.next == n1)
        t(n1.next == n2)
        t(n2.next == n3)
        t(n1.next.next.next == n1)        
        t(n1.prev.prev.prev == n1)  
        
    def test_remove_from_sibling(self):
        t = self.assertTrue
        n1 = n(1)
        n2 = n(2)
        n3 = n(3)     
        
        n1.remove_from_sibling()
        self.assert_no_sibling(n1)
        
        n1.concate(n2)
        n2.remove_from_sibling()
        self.assert_no_sibling(n1)  
        self.assert_no_sibling(n2)
   
        n1.concate(n2)
        n2.concate(n3)
        n2.remove_from_sibling()
        t(n1.next == n3)
        t(n3.next == n1)
        t(n1.prev == n3)
        t(n3.prev == n1)
        n1.remove_from_sibling()
        self.assert_no_sibling(n1)  
        self.assert_no_sibling(n2)    
        self.assert_no_sibling(n3) 
        
    def test_remove_from_sibling2(self):
        t = self.assertTrue
        n1 = n(1)
        n2 = n(2)
        n2.set_parent(n1)
        n2.remove_from_sibling()
        t(n2.p == None)
        t(n1.child == None)
        
        n1 = n(1)
        n2 = n(2)
        n3 = n(3)
        
        n2.set_parent(n1)
        n3.set_parent(n1)
        n2.remove_from_sibling()
        t(n1.child == n3)
        
    def assert_no_sibling(self, node):
        self.assertTrue(node.next == node)
        self.assertTrue(node.prev == node)      
        
    def test_set_parent(self):
        t = self.assertTrue
        n1 = n(1)
        t(n1.p == None)
        
        n2 = n(2)
        n2.set_parent(n1)
        t(n1.child == n2)
        t(n2.p == n1)
        
        n3 = n(3)
        n3.set_parent(n1)
        t(n2.next == n3)
        
        n2.remove_from_sibling()
        t(n2.p == None)
        n3.remove_from_sibling()
        t(n3.p == None)
    
    def test_degree(self):
        t = self.assertTrue
        n1 = n(1)
        n2 = n(2)
        n3 = n(3)
        t(n1.degree == 0)
        n2.set_parent(n1)
        t(n1.degree == 1)
        n3.set_parent(n1)
        t(n1.degree == 2)
        n2.remove_from_sibling()
        t(n1.degree == 1)
        n3.remove_from_sibling()
        t(n1.degree == 0)
        
    def test_min_heap(self):
        t = self.assertTrue
        n1 = n(1)
        n2 = n(2)
        n3 = n(3)
        
        n3.set_parent(n1)
        n2.set_parent(n3)
        t(n1.check_min_heap() == False)
        
        n4 = n(4)
        n5 = n(5)
        n6 = n(6)     
        n5.set_parent(n4)
        n6.set_parent(n5)
        t(n4.check_min_heap())
        
        n7 = n(7)
        n8 = n(8)
        n9 = n(9)   
        n10 = n(10)  
        n8.set_parent(n7)
        n9.set_parent(n7)
        n10.set_parent(n8)
        t(n7.check_min_heap())            
        
        n7 = n(7)
        n8 = n(8)
        n9 = n(9)   
        n10 = n(10)  
        n8.set_parent(n7)
        n9.set_parent(n10)
        n10.set_parent(n7)
        t(n7.check_min_heap() == False)   
        
    
    def test_print(self):
        n = []
        for i in range(10):
            n.append(fib_heap_node(i))
            
        n[1].set_parent(n[0])
        n[2].set_parent(n[0])
        n[3].set_parent(n[0])
        n[4].set_parent(n[1])
        n[5].set_parent(n[1])
        n[6].set_parent(n[2])
        n[7].set_parent(n[2])
        n[8].set_parent(n[3])
        n[9].set_parent(n[3])
        n[3].mark = True
        n[6].mark = True
        #n[0].print()
        
        n = fib_heap_node
        n0 = n(0)
        n1 = n(1)
        n1.set_parent(n0)
        n2 = n(2)
        n2.set_parent(n0)
        n3 = n(3)
        n3.set_parent(n2)
        n4 = n(4)
        n4.set_parent(n3)
        #n0.print()
      
    
if __name__ == '__main__':
    unittest.main()
