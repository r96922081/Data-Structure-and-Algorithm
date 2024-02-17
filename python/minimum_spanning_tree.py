from utility import  create_random_graph, edge, get_adjacency_list_from_matrix
import unittest
from disjoint_set import find_set, union, disjoint_set_node
import operator
from graph_algorithm import find_scc
import sys
from fib_heap import fib_heap, fib_heap_node

'''
Minimum spanning tree algorithm
1. Kruskal
2. Prim
'''

def kruskal_for_undirected_graph(V, E):
    A = []
    nodes = []
    for v in V:
        nodes.append(disjoint_set_node(v))
    
    edges = []
    for i in range(E.row()):
        for j in range(E.col()):
            if E[i][j] != 0 and E[i][j]  != sys.maxsize:
                edges.append(edge(i, j, E[i][j]))
            
    edges.sort(key=operator.attrgetter('len'))
    for e in edges:
        if find_set(nodes[e.src]) != find_set(nodes[e.dst]):
            A.append(e)
            union(find_set(nodes[e.src]), find_set(nodes[e.dst]))
    return A

def prims_for_undirected_graph(V, E, r):
    Q = fib_heap()
    all_V = []
    for u in V:
        u2 = fib_heap_node(sys.maxsize)
        u2.index = u
        u2.parent = None
        u2.in_heap = True
        if u == r:
            u2.key = 0
        Q.insert(u2) 
        all_V.append(u2)
        
    adj_list = get_adjacency_list_from_matrix(E)

    while Q.min != None:
        u = Q.extract_min()
        u.in_heap = False
        for e in adj_list[u.index]:
            v = all_V[e.dst]
            if v.in_heap and e.len < v.key:
                v.parent = u.index
                Q.decrease_key(v, e.len)

    edges = []
    for v in all_V:
        if v.index != r:
            edges.append(edge(v.index, v.parent, E[v.index][v.parent]))
    return edges
        
def all_connected(E):
    s = find_scc(E)
    if len(s) == 1:
        return True
    else:
        return False

class test_kruskal_algorithm(unittest.TestCase):
    def _test1(self):
        while True:
            V, E = create_random_graph(6, 6 ** 2, False)
            if all_connected(E):
                break
        print('adjance-matrix = \n' + str(E))
        A = kruskal_for_undirected_graph(V, E)
        print('MST edges by Kruskal = ')
        for e in A:
            print(e)
        print('================')

class test_prims_algorihtm(unittest.TestCase):
    def _test1(self):
        while True:
            V, E = create_random_graph(6, 6 ** 2, False)
            if all_connected(E):
                break
        print('adjance-matrix = \n' + str(E))
        A = prims_for_undirected_graph(V, E, 0)
        print('MST edges by Prim''s= ')
        for e in A:
            print(e)
        print('================')

class test_kruskal_against_prims(unittest.TestCase):
    def test1(self):
        for _ in range(100):
            node_count = 6
            while True:
                V, E = create_random_graph(node_count, node_count ** 2, False)
                if all_connected(E):
                    break
            A1 = kruskal_for_undirected_graph(V, E)
            A1.sort(key=operator.attrgetter('len'))
            A2 = prims_for_undirected_graph(V, E, 0)
            A2.sort(key=operator.attrgetter('len'))
            
            self.assertTrue(len(A1) == len(A2))

            for i in range(len(A1)):
                self.assertTrue(A1[i].len == A2[i].len)

            v = []
            for i in range(node_count):
                v.append(False)
            for e in A1:
                v[e.src] = True
                v[e.dst] = True
            for v2 in v:
                self.assertTrue(v2 == True)

            v.clear()
            for i in range(node_count):
                v.append(False)
            for e in A2:
                v[e.src] = True
                v[e.dst] = True
            for v2 in v:
                self.assertTrue(v2 == True)

if __name__ == '__main__':
    unittest.main()
