import unittest
import sys
import copy
from utility import create_random_graph, matrix
from single_source_shortest_path import dijkstra_for_nonnegative_wieght, bellman_ford

'''
All pair shortest path algorithm
1. Floyd Warshall algorithm
2. Johnson algorithm
'''

def extend_shortest_path(L, W):
    n = L.row()
    L2 = matrix(n, n)
    for i in range(n):
        for j in range(n):
            L2[i][j] = sys.maxsize
            for k in range(n):
                L2[i][j] = min(L2[i][j],  L[i][k] + W[k][j])
                
    return L2          

def all_pair_shortest_path(E):
    n = E.row()
    L = E
    m = 1
    while m < n - 1:
        L = extend_shortest_path(L, L)
        m *= 2
    return L
    
def floyd_warshall(E):
    n = E.row()
    D = copy.deepcopy(E)
    P = matrix(n, n)
    
    for i in range(n):
        for j in range(n):
            if E[i][j] == sys.maxsize or i == j:
                P[i][j] = None
            else:
                P[i][j] = i
    
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if D[i][j] > D[i][k] + D[k][j]:
                    D[i][j] = D[i][k] + D[k][j]
                    P[i][j] = P[k][j]
                
    return D, P

def johnson(E):
    s = E.row()
    E2 = matrix(E.row() + 1, E.row() + 1)
    for i in range(E.row()):
        E2[i][s] = sys.maxsize
        E2[s][i] = 0
        for j in range(E.col()):
            E2[i][j] = E[i][j]
            
    no_negative_cycle_reachable_from_src_1, nodes_in_shortest_paths_1 = bellman_ford(E2, s)
    if not no_negative_cycle_reachable_from_src_1:
        return False, None
        
    h = [0] * E2.row()
    for n in nodes_in_shortest_paths_1:
        h[n.index] = n.d
        
    for i in range(E2.row()):
        for j in range(E2.row()):
            if E2[i][j] != sys.maxsize:
                E2[i][j] = E2[i][j] + h[i] - h[j]
               
    D =  matrix(E.row(), E.row())     
              
    for u in range(s):
        nodes_in_shortest_paths_2 = dijkstra_for_nonnegative_wieght(E2, u)
        for v in nodes_in_shortest_paths_2:
            if v.index != s:
                D[u][v.index] = v.d + h[v.index] - h[u]
                
    return True, D
    

class MyTest(unittest.TestCase):
    def test_all_pair_shortest_path_against_dijkstra(self):
        for _ in range(100):
            node_count = 5
            V, E = create_random_graph(node_count, node_count * 2, True)
            dijkstra_answers = []
            for i in range(node_count):
                dijkstra_answers.append(dijkstra_for_nonnegative_wieght(E, i))
         
            E2 = all_pair_shortest_path(E)
            for row in range(node_count):
                dijkstra_answer = dijkstra_answers[row]
                for col in range(node_count):
                    self.assertTrue(dijkstra_answer[col].d == E2[row][col])
                    
    def test_floyd_warshall_against_all_pair_shortest_path(self):
        for _ in range(100):
            node_count = 7
            V, E = create_random_graph(node_count, node_count * 3, True) 
            all_pair_shortest_path_answer = all_pair_shortest_path(E)
            floyd_answer, floyd_p = floyd_warshall(E)
            
            for i in range(all_pair_shortest_path_answer.row()):
                for j in range(all_pair_shortest_path_answer.col()):
                    self.assertTrue(all_pair_shortest_path_answer[i][j] == floyd_answer[i][j])
                    if i == j:
                        continue
                        
                    shortest_path = floyd_answer[i][j]
                    if shortest_path == sys.maxsize:
                        self.assertTrue(floyd_p[i][j] == None)
                    else:
                        path = 0
                        p = j
                        while p != i:
                            next_p = floyd_p[i][p] 
                            path += floyd_answer[next_p][p]
                            p = next_p
                        self.assertTrue(path == shortest_path)   
                        
    def test_johnson_against_floyd(self):
        for _ in range(100):
            node_count = 6
            V, E = create_random_graph(node_count, node_count * 3, True)
            floyd_answer, floyd_p = floyd_warshall(E)
            has_negative_cycle, johnson_answer = johnson(E)
            for i in range(floyd_answer.row()):
                for j in range(johnson_answer.row()):
                    self.assertTrue(floyd_answer[i][j] == johnson_answer[i][j])

if __name__ == '__main__':
    unittest.main()
