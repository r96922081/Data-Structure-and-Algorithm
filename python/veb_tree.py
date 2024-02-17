import unittest
import math

''''
Demo complex van Emde Boas Tree
it supports search, insert, delete, minimum(maximum), successor (predecessor) in O(lglgn) and O(lglgu)
n = count, u is largest element value
'''

class veb_node:
    def __init__(self, u, min, max):
        self.u = u
        self.min = min
        self.max = max
        self.is_summary = False
        self.print_new_line = False
        
        self.summary = None   
        self.cluster = []
        cluster_count = self.cluster_count()
        if u > 2:
            for _ in range(cluster_count):
                self.cluster.append(veb_node(self.child_u(), None, None))
            self.summary = veb_node(cluster_count, None, None)
            
    def cluster_count(self):
        return 2 ** (math.ceil(math.log2(self.u)/2))
        
    def child_u(self):
        return 2 ** (math.floor(math.log2(self.u)/2))
            
    def minimum(self):
        return self.min
        
    def maximum(self):
        return self.max
            
    def member(self, x):
        if x == self.min or x == self.max:
            return True
        elif self.u == 2:
            return False
        else:
            return self.cluster[self.high(x)].member(self.low(x))
            
    def empty_insert(self, x):
        self.min = x
        self.max = x
        
    def insert(self, x):
        if self.min == None:
            self.empty_insert(x)
        else:
            if x < self.min:
                x, self.min = self.min, x
            if self.u > 2:
                if self.cluster[self.high(x)].minimum() == None:
                    self.summary.insert(self.high(x))
                    self.cluster[self.high(x)].empty_insert(self.low(x))
                else:
                    self.cluster[self.high(x)].insert(self.low(x))
            if x > self.max:
                self.max = x
            
    def high(self, x):
        return math.floor(x/self.child_u())
            
    def low(self, x):
        return x % self.child_u()
        
    def index(self, x, y):
        return x * self.child_u() + y
        
        
    def successor(self, x):
        if self.u == 2:
            if x == 0 and self.max == 1:
                return 1
            else:
                return None
        elif self.min != None and x < self.min:
            return self.min
        else:
            max_low = self.cluster[self.high(x)].maximum()
            if max_low != None and self.low(x) < max_low:
                offset = self.cluster[self.high(x)].successor(self.low(x))
                return self.index(self.high(x), offset)
            else:
                succ_cluster = self.summary.successor(self.high(x))
                if succ_cluster == None:
                    return None
                else:
                    offset = self.cluster[succ_cluster].minimum()
                    return self.index(succ_cluster, offset)
                    
    def predecessor(self, x):
        if self.u == 2:
            if x == 1 and self.min == 0:
                return 0
            else:
                return None
        elif self.max != None and x > self.max:
            return self.max
        else:
            min_low = self.cluster[self.high(x)].minimum()
            if min_low != None and self.low(x) > min_low:
                offset = self.cluster[self.high(x)].predecessor(self.low(x))
                return self.index(self.high(x), offset)
            else:
                pred_cluster = self.summary.predecessor(self.high(x))
                if pred_cluster == None:
                    if self.min != None and x > self.min:
                        return self.min
                    else:
                        return None
                else:
                    offset = self.cluster[pred_cluster].maximum()
                    return self.index(pred_cluster,  offset)
                    
            
    def delete(self, x):
        if self.min == self.max:
            self.min = None
            self.max = None
        elif self.u == 2:
            if x == 0:
                self.min = 1
            else:
                self.min = 0
            self.max = self.min
        else:
            if x == self.min:
                first_cluster = self.summary.minimum()
                x = self.index(first_cluster, self.cluster[first_cluster].minimum())
                self.min = x
            self.cluster[self.high(x)].delete(self.low(x))
            if self.cluster[self.high(x)].minimum() == None:
                self.summary.delete(self.high(x))
                if x == self.max:
                    summary_max = self.summary.maximum()
                    if summary_max == None:
                        self.max = self.min
                    else:
                        self.max = self.index(summary_max, self.cluster[summary_max].maximum())
            elif x == self.max:
                self.max = self.index(self.high(x), self.cluster[self.high(x)].maximum())
        
    def __str__(self):
        ret = ''
        q = [self]
        
        while len(q) != 0:
            n = q[0]
            q.pop(0)
            if n.is_summary:
                ret += '(summary)'
                
            ret += '['
            ret += 'u=' + str(n.u) + ',min=' + str(n.min) + ',max=' + str(n.max)
            if n.print_new_line:
                ret += ']\n'
                if n.u > 2:
                    n.cluster[-1].print_new_line = True
            else:
                ret += '] '
                   
            if n.u > 2:
                n.summary.is_summary = True
                q.append(n.summary)
                for i in range(len(n.cluster)):
                    q.append(n.cluster[i])
                
            n.print_new_line = False
            
        return ret
        

class test_veb_tree(unittest.TestCase):
    def test_print(self):
        # 1 = 2 ** 0
        n1 = veb_node(1, 0, 0)
        n1.print_new_line = True
        self.assertTrue(str(n1) == '[u=1,min=0,max=0]\n')
        n1 = veb_node(1, None, None)
        n1.print_new_line = True
        self.assertTrue(str(n1) == '[u=1,min=None,max=None]\n')
        
        # 2 = 2 ** 1
        n1 = veb_node(2, 1, 1)
        n1.print_new_line = True
        self.assertTrue(str(n1) == '[u=2,min=1,max=1]\n')
        n1 = veb_node(2, 0, 1)
        n1.print_new_line = True
        self.assertTrue(str(n1) == '[u=2,min=0,max=1]\n')     
        n1 = veb_node(2, None, None)
        n1.print_new_line = True
        self.assertTrue(str(n1) == '[u=2,min=None,max=None]\n')   
      
        # 4 = 2 ** 2
        n1 = veb_node(4, 2, 3)
        n1.print_new_line = True
        s1 = veb_node(2, 1, 1)
        n1.summary = s1
        n2 = veb_node(2, None, None)
        n3 = veb_node(2, 0, 1)
        n1.cluster[0] = n2
        n1.cluster[1] = n3
        self.assertTrue(str(n1) == '[u=4,min=2,max=3]\n(summary)[u=2,min=1,max=1] [u=2,min=None,max=None] [u=2,min=0,max=1]\n')
        
        # 8 = 2 ** 3
        n1 = veb_node(8, 3, 3)
        n1.print_new_line = True
        s1 = veb_node(4, 1, 2)
        n1.summary = s1
        s1_1 = veb_node(2, 0, 1)
        n_s1_1 = veb_node(2, 1, 1)
        n_s1_2 = veb_node(2, 0, 0)
        s1.summary = s1_1
        s1.cluster[0] = n_s1_1
        s1.cluster[1] = n_s1_2
        n2 = veb_node(4, 3, 3)
        n1.cluster[0] = n2
        s2 = veb_node(2, 1, 1)
        n2.summary = s2
        n3 = veb_node(2, None, None)
        n4 = veb_node(2, 1, 1)
        n2.cluster[0] = n3
        n2.cluster[1] = n4
        
        n5 = veb_node(4, None, None)
        n1.cluster[1] = n5
        s5 = veb_node(2, None, None)
        n5.summary = s5
        n6 = veb_node(2, None, None)
        n7 = veb_node(2, None, None)
        n5.cluster[0] = n6
        n5.cluster[1]= n7
        
        n8 = veb_node(4, None, None)
        n1.cluster[2] = n8
        s8 = veb_node(2, None, None)
        n8.summary = s8
        n9 = veb_node(2, None, None)
        n10 = veb_node(2, None, None)
        n8.cluster[0] = n9
        n8.cluster[1] = n10

        n11 = veb_node(4, None, None)
        n1.cluster[3] = n11
        s11 = veb_node(2, None, None)
        n11.summary = s11
        n12 = veb_node(2, None, None)
        n13 = veb_node(2, None, None)
        n11.cluster[0] = n12
        n11.cluster[1] = n13        
        
        #print(n1)
        
    def test_insert(self):
        t = self.assertTrue
        
        for i in range(1, 8):
            u = 2 ** i
            n = veb_node(u, None, None)
            for j in range(u):
                if j % 2 == 0:
                    n.insert(j)
                    
            for j in range(u):
                if j % 2 == 0:
                    t(n.member(j) == True)
                
    def test_construct(self):
        for i in range(1, 8):
            u = 2 ** i
            n = veb_node(u, None, None)
            for j in range(u):
                self.assertTrue(n.member(j) == False)
                
    def test_successor(self):
        t = self.assertTrue
        
        for i in range(1, 7):
            u = 2 ** i
            n = veb_node(u, None, None)
            for j in range(u):
                if j % 2 == 1:
                    n.insert(j)
                    
            for j in range(u):
                if j % 2 == 0:
                    t(n.successor(j) == (j + 1))        
              
            for j in range(u - 1):
                if j % 2 == 1:
                    t(n.successor(j) == (j + 2))
                    
            t(n.successor(u-1) == None)
            
    def test_predecessor(self):
        t = self.assertTrue
        
        for i in range(1, 7):
            u = 2 ** i
            n = veb_node(u, None, None)
            for j in range(u):
                if j % 2 == 1:
                    n.insert(j)
                    
            for j in range(2, u):
                if j % 2 == 0:
                    t(n.predecessor(j) == (j - 1))        
              
            for j in range(2, u):
                if j % 2 == 1:
                    t(n.predecessor(j) == (j - 2))
                    
            t(n.predecessor(1) == None)
            
    def test_delete(self):
        t = self.assertTrue
        
        for i in range(1, 7):
            u = 2 ** i
            n = veb_node(u, None, None)
            for j in range(u):
                    n.insert(j)
                    
            for j in range(u):
                if j % 2 == 0:
                    n.delete(j)
                    
            for j in range(u):
                if j % 2 == 0:
                    t(n.member(j) == False)
                else:
                    t(n.member(j) == True)

if __name__ == '__main__':
    unittest.main()
