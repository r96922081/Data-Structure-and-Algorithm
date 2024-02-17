import unittest
from utility import empty, create_random_graph, get_adjacency_list_from_matrix,  matrix
import sys
from operator import attrgetter
from disjoint_set import disjoint_set_node, find_set, union

'''
Graph algorithm demo:
1. breadth-first search
2. deep-first search
3. Find strongly-connected component
4. topological sorting
'''

def bfs(G, s_index):
    ''' Pass G in matrix type'''
    vertices = []
    for i in range(G.row()):
        vertices.append(empty())
        vertices[i].index = i
    s = vertices[s_index]
    for u in vertices:
        if u != s:
            u.color = 'white'
            u.d = sys.maxsize
            u.p = None
    s.color = 'gray'
    s.d = 0
    s.p = None
    q = []
    q.append(s_index)
    adj_lists = get_adjacency_list_from_matrix(G)
    while len(q) != 0:
        u_index = q[0]
        u = vertices[u_index]
        q.pop(0)
        for edge in adj_lists[u_index]:
            v_index = edge.dst
            v = vertices[v_index]
            if v.color == 'white':
                v.color = 'gray'
                v.d = u.d + G[u_index][v_index]
                v.p = u
                q.append(v_index)
        u.color = 'black'
        
    return vertices

# same time complexity with BFS
def is_reachable(E, src, dst):
    vertices = bfs(E, src)
    if vertices[dst].d != sys.maxsize:
        return True
    else:
        return False

def dfs(G):
    ''' Pass G in matrix type'''
    vertices = []
    for _ in range(G.row()):
        vertices.append(empty())  
    
    for index in range(len(vertices)):
        u = vertices[index]
        u.color = 'white'
        u.p = None
        u.index = index
        
    adj_lists = get_adjacency_list_from_matrix(G)
    time_obj = empty()
    time_obj.time = 0
    for u_index in range(len(vertices)):
        if vertices[u_index].color == 'white':
            dfs_visit(adj_lists, vertices, u_index, time_obj)
            
    return vertices
            
def dfs_visit(adj_lists, vertices, u_index, time_obj):
    time_obj.time += 1
    u = vertices[u_index]
    u.d = time_obj.time
    u.color = 'gray'
    for edge in adj_lists[u_index]:
        v_index = edge.dst
        v = vertices[v_index]
        if v.color == 'white':
            v.p = u
            dfs_visit(adj_lists, vertices, v_index, time_obj)
    u.color = 'black'
    time_obj.time += 1
    u.f = time_obj.time
    
def get_forest_from_dfs(vertices):
    nodes = []
    for v in vertices:
        nodes.append(disjoint_set_node(v.index))
        
    for v in vertices:
        if v.p != None:
            if find_set(nodes[v.index]) != find_set(nodes[v.p.index]):
                union(find_set(nodes[v.index]),  find_set(nodes[v.p.index]))
    
    all_scc_1 = []
    for _ in range(len(vertices)):
        all_scc_1.append([])
    
    for n in nodes:
        all_scc_1[find_set(n).key].append(n.key)
        
    all_scc_2 = []
    for scc in all_scc_1:
        if len(scc) != 0:
            all_scc_2.append(scc)
    
    return all_scc_2
    
def find_scc(G):
    vertices = dfs(G)
    G_t = matrix(G.row(), G.row())
    
    for i in range(G.row()):
        for j in range(G.row()):
            G_t[i][j] = G[j][i]
            
    return find_scc_2(G_t, vertices)
    
def find_scc_2(G, vertices):
    ''' sligtly modify from dfs'''
    time_obj = empty()
    time_obj.time = 0
    
    sorted_vertices = sorted(vertices, key=attrgetter('f'))
    vertices2 = []
    for i in range(G.row()):
        v = empty()
        v.color ='white'
        v.p = None
        v.index = i
        vertices2.append(v)  
    
    adj_lists = get_adjacency_list_from_matrix(G)
    for u in range(len(sorted_vertices) - 1, -1, -1):
        u_index = sorted_vertices[u].index
        if vertices2[u_index].color == 'white':
            find_scc_visit(adj_lists, vertices2, u_index, time_obj)
            
    all_scc = get_forest_from_dfs(vertices2)
    return all_scc            
            
def find_scc_visit(adj_lists, vertices, u_index, time_obj):
    ''' sligtly modify from dfs_visit'''
    u = vertices[u_index]
    u.color = 'gray'
    for edge in adj_lists[u_index]:
        v_index = edge.dst
        v = vertices[v_index]
        if v.color == 'white':
            v.p = u
            find_scc_visit(adj_lists, vertices, v_index, time_obj)
    u.color = 'black'
    
def has_cycle(E):
    all_sccs = find_scc(E)
    node_count = E.row()
    
    if len(all_sccs) == node_count:
        return False
    else:
        return True
    
def topological_sort(G):
    vertices = []
    for _ in range(G.row()):
        vertices.append(empty())  
    
    for index in range(len(vertices)):
        u = vertices[index]
        u.color = 'white'
        
    topological_order = []
    for u_index in range(len(vertices)):
        if vertices[u_index].color == 'white':
            topological_sort_visit(G, vertices, u_index, topological_order)
            
    return topological_order
            
def topological_sort_visit(G, vertices, u_index, topological_order):
    u = vertices[u_index]
    u.color = 'gray'
    for v_index in range(len(vertices)):
        if v_index != u_index and G[u_index][v_index] != sys.maxsize:
            v = vertices[v_index]
            if v.color == 'white':
                topological_sort_visit(G, vertices, v_index, topological_order)
    u.color = 'black'
    topological_order.insert(0, u_index)
    
class TestMe(unittest.TestCase):    
    def test_bfs(self):
        max_size = 10
        directed = True
        for size in range(1, max_size):
            V, E = create_random_graph(size, size * 5,  directed)
            if directed == True:
                directed = False
            else:
                directed = True
                
            for j in range(size):
                vertices = bfs(E, j)
                for i in range(size):
                    if i == j:
                        continue
                        
                    if vertices[i].d == sys.maxsize:
                        self.assertTrue(vertices[i].p == None)
                    else:
                        p = vertices[i]
                        while p != vertices[j]:
                            p = p.p
                        
    def test_dfs(self):
        max_size = 10
        directed = True
        for size in range(1, max_size):
            V, E = create_random_graph(size, size * 5,  directed)
            if directed == True:
                directed = False
            else:
                directed = True
                
            vertices = dfs(E)
            
            for i in range(size):
                u = vertices[i]
                for j in range(size):
                    if i == j:
                        continue
                    v = vertices[j]
                    if u.d < v.d and v.d < u.f:
                        p = v
                        while p != v:
                            p = p.p
                        
    def test_strongly_connected_component(self):
        directed = True
        for _ in range(100):
            size = 7
            V, E = create_random_graph(size, size * 2,  directed)
            if directed == True:
                directed = False
            else:
                directed = True
                
            all_scc = find_scc(E)
            vertices_list = []
            
            for i in range(size):
                vertices_list.append(bfs(E, i))
                
            for scc in all_scc:
                for u in scc:
                    for v in range(size):
                        if v == u:
                            continue
                        if v in scc:
                            self.assertTrue(vertices_list[u][v].d != sys.maxsize)
                        else:
                            self.assertTrue(vertices_list[u][v].d == sys.maxsize or
                            (vertices_list[u][v].d != sys.maxsize and vertices_list[v][u].d == sys.maxsize))
    
if __name__ == '__main__':
    unittest.main()
