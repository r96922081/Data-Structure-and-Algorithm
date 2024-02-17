import unittest
from utility import create_random_graph, empty, get_adjacency_list_from_matrix
from graph_algorithm import has_cycle, find_scc, is_reachable, topological_sort
from heap import priority_queue, heaptype
import copy
import sys

'''
single source shortest path algorithm
1. Dijkstra (for no negative edge)
2. bellman ford algorithm (allow negative edge)
'''

def init_single_source(V, E, s):
    for v in V:
        v.d = sys.maxsize
        v.pi = None
    s.d = 0

def relax(u, v, len):
    if u.d != sys.maxsize and v.d > u.d + len:
        v.d = u.d + len
        v.pi = u

def bellman_ford(E, s):
    nodes = []
    node_count = E.row()
    for i in range(node_count):
        n = empty()
        n.index = i
        nodes.append(n)
    init_single_source(nodes, E, nodes[s])
    adj_list = get_adjacency_list_from_matrix(E)
    for _ in range(node_count):
        for e in adj_list:
            relax(nodes[e.src], nodes[e.dst], e.len)
    for e in adj_list:
        if nodes[e.dst].d != sys.maxsize and nodes[e.src].d != sys.maxsize and nodes[e.dst].d > nodes[e.src].d + e.len:
            return False,  None

    return True, nodes

def shortest_path_for_directed_acyclic_graph(E, s):
    topological_order = topological_sort(E)
    nodes = []
    for i in range(E.row()):
        n = empty()
        n.index = i
        nodes.append(n)
    init_single_source(nodes, E, nodes[s])
    adj_list = get_adjacency_list_from_matrix(E)
    for v in topological_order:
        for e in adj_list[v]:
            relax(nodes[e.src], nodes[e.dst], e.len)
            
    return nodes    

def dijkstra_for_nonnegative_wieght(E, s):
    node_count = E.row()
    q = priority_queue(heaptype.min, sys.maxsize, -sys.maxsize + 1) 
    index_to_heap_node_map = [None] * node_count
    
    for i in range(node_count):
        if i == s:
            n = q.insert(0, i)
        else:
            n = q.insert(sys.maxsize, i)
            
        n.pi = None
        index_to_heap_node_map[i] = n
    
    adj_list = get_adjacency_list_from_matrix(E)
    while q.heapsize > 0:
        heap_node = q.extract()
        key = heap_node.key
        index = heap_node.element
        
        for e in adj_list[index]:
            v = index_to_heap_node_map[e.dst]
            if key != sys.maxsize and v.key > key + e.len:
                q.decrease_key_by_node(v, key + e.len)
                
    nodes = []
    for i in range(len(index_to_heap_node_map)):
        n = empty()
        n.d = index_to_heap_node_map[i].key
        n.index = i
        nodes.append(n)

    return nodes        

class test_single_source_shortest_path(unittest.TestCase):    
    def test_BellmanFord_negative_cycle(self):
        for _ in range(20):
            node_count = 8
            V, E = create_random_graph(node_count, node_count ** 2, True)
            for v in range(len(V)):
                E[v][v] = 0 
            
            E2 = copy.deepcopy(E)
            src = 0
            no_negative_cycle_reachable_from_src_1, nodes_in_shortest_paths_1 = bellman_ford(E, src) 
            
            for i in range(E2.row()):
                for j in range(E.col()):
                    E2[i][j] *= -1
            no_negative_cycle_reachable_from_src_2, nodes_in_shortest_paths_2 = bellman_ford(E2, src) 
            
            has_cycle_reachable_from_src = False
            if has_cycle(E):
                all_sccs = find_scc(E)
                for scc in all_sccs:
                    if len(scc) != 1: # cycle
                        for v in scc:
                            if is_reachable(E, src, v):
                                has_cycle_reachable_from_src = True
            
            if has_cycle_reachable_from_src:
                self.assertTrue(no_negative_cycle_reachable_from_src_2 == False)
            else:
                self.assertTrue(no_negative_cycle_reachable_from_src_2)

    def test_shortest_path_for_directed_acyclic_graph_against_bellman_ford(self):
        for _ in range(20):
            node_count = 7
            cycle = True      
            
            while cycle:
                V, E = create_random_graph(node_count, 4 ** 2, True)        
                cycle = has_cycle(E)
               
            nodes_in_shortest_paths_1 = shortest_path_for_directed_acyclic_graph(E, 0)
            no_negative_cycle_reachable_from_src_1, nodes_in_shortest_paths_2 = bellman_ford(E, 0) 
        
            for i in range(len(nodes_in_shortest_paths_1)):
                self.assertTrue(nodes_in_shortest_paths_1[i].d == nodes_in_shortest_paths_2[i].d)
                
    def test_dijkstra_against_bellman_ford(self):
        for _ in range(20):
            node_count = 8
            V, E = create_random_graph(node_count, 4 ** 2, True)
            no_negative_cycle_reachable_from_src_1, nodes_in_shortest_paths_1 = bellman_ford(E, 0)
            nodes_in_shortest_paths_2 = dijkstra_for_nonnegative_wieght(E, 0)
            for i in range(len(nodes_in_shortest_paths_1)):
                self.assertTrue(nodes_in_shortest_paths_1[i].d == nodes_in_shortest_paths_2[i].d)

if __name__ == '__main__':
    unittest.main()
