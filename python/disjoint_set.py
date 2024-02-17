import unittest
import random
from utility import create_random_graph

'''
disjoint set with find & union opeartions
'''

class disjoint_set_node:
    def __init__(self, key):
        self.key = key
        self.p = self
        self.rank = 0
    
def find_set(x):
    if x != x.p:
        x.p = find_set(x.p)
    return x.p
    
def union(x, y):
    link(find_set(x), find_set(y))

def link(x, y):
    if x.rank > y.rank:
        y.p = x
    elif y.rank > x.rank:
        x.p = y
    else:
        x.p = y
        y.rank == 1

class TestMe(unittest.TestCase):
    def test1(self):
        t = self.assertTrue
        max = 100
        node_list = []        
        golden_set_list = []        
        for i in range(max):          
            n = disjoint_set_node(i)
            node_list.append(n)
            golden_set_list.append(set([i]))
            
        for i in range(max//2):
            a = node_list[random.randint(0, max - 1)]
            b = node_list[random.randint(0, max - 1)]
            if find_set(a) != find_set(b):
                union(find_set(a), find_set(b))
                
                s1 = None
                s2 = None
                for s in golden_set_list:
                    if a.key in s:
                        s1 = s
                    if b.key in s:
                        s2 = s
                golden_set_list.remove(s1)
                golden_set_list.remove(s2)
                golden_set_list.append(s1.union(s2))
                
        for n in node_list:
            key = n.key
            root_key = find_set(n).key
            
            for s in golden_set_list:
                if key in s:
                    t(root_key in s)

    def _test_has_cycle(self):
        V, E = create_random_graph(6, 6, True)
        print('has cycle?')
        print(E)
        print(has_cycle(V, E))        

                    
if __name__ == '__main__':
    unittest.main()
