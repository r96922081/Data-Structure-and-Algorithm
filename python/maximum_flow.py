from utility import create_random_graph, empty, matrix
import unittest
import sys
from all_pair_shortest_path import floyd_warshall
from graph_algorithm import bfs
import random   
import copy

'''
Demo how to calculate maximum flow by
1. Ford-Fulkerson Method
2. Push-relabel algorithm
3. Relabel-to-front algorithm
'''

def create_maximum_flow_graph(node_count):
    # find source loop
    while True:
        
        # find sink loop
        while True:
            V, E = create_random_graph(node_count, node_count ** 2, True)
            sink = 0
            
            for i in range(node_count):
                E[sink][i] = sys.maxsize
            
            for i in range(node_count):
                for j in range(i + 1,  node_count):
                    if E[i][j] != sys.maxsize:
                        E[j][i] = sys.maxsize
            
            floyd_answer, floyd_p = floyd_warshall(E)
            
            valid = True
            for i in range(node_count):
                if i == sink:
                    continue
                if floyd_answer[i][sink] == sys.maxsize:
                    valid = False
                    break
                    
            if valid:
                break
            
        valid_source_sink_pair = None
        for source in range(node_count):
            if source == sink:
                continue
            valid_source = True
            for i in range(node_count):
                if i != source and i != sink:
                    if floyd_answer[source][i] == sys.maxsize:
                        valid_source = False
                        break
            if valid_source:
                valid_source_sink_pair = (source, sink)
            break

        if valid_source_sink_pair != None:
            break
            
    return E, valid_source_sink_pair[0], valid_source_sink_pair[1]

def ford_fulkerson(E, s, t):
    F = matrix(E.row(), E.row())
    
    for i in range(E.row()):
        for j in range(E.row()):
            F[i][j] = 0
            
    Gf = copy.deepcopy(E)
                
    vertices = bfs(Gf, s)
    while_count = 0
    while vertices[t].d != sys.maxsize:
        while_count += 1
        f = sys.maxsize
        v = t
        while v != s:
            u = vertices[v].p.index
            f = min(f, vertices[v].d - vertices[u].d)
            v = u
            
        v = t
        while v != s:
            u = vertices[v].p.index
            if E[u][v] != sys.maxsize:
                F[u][v] += f
            else:
                F[v][u] -= f
                
            Gf[u][v] -= f
            if Gf[u][v] == 0:
                Gf[u][v] = sys.maxsize        
                
            if Gf[v][u] == sys.maxsize:
                Gf[v][u] = 0
            Gf[v][u] += f 
            v = u
        vertices = bfs(Gf, s)
                
    return F

def get_valid_push(Gf, push_relabel_list, s, t):
    for u in range(len(push_relabel_list)):
        if u == s or u == t:
            continue        
        if push_relabel_list[u].e > 0:
            for v in range(len(push_relabel_list)):
                if u != v and Gf[u][v] != sys.maxsize and push_relabel_list[u].h == push_relabel_list[v].h + 1:
                    return u, v
    return None, None                  

def push(E, Gf, F, push_relabel_list, u, v):
    ''' E, Gf, F are matrix'''
    f = min(push_relabel_list[u].e, Gf[u][v])
    if E[u][v] != sys.maxsize:
        F[u][v] += f
    else:
        F[v][u] -= f
        
    Gf[u][v] -= f
    if Gf[u][v] == 0:
        Gf[u][v] = sys.maxsize        
        
    if Gf[v][u] == sys.maxsize:
        Gf[v][u] = 0
    Gf[v][u] += f 
        
    push_relabel_list[u].e -= f
    push_relabel_list[v].e += f
    
def get_valid_relabel(Gf, push_relabel_list, s, t):
    for u in range(len(push_relabel_list)):
        if u == s or u == t:
            continue
        if push_relabel_list[u].e > 0:
            valid = True
            for v in range(len(push_relabel_list)):
                if u != v and Gf[u][v] != sys.maxsize:
                    if push_relabel_list[u].h > push_relabel_list[v].h:
                        valid = False
                        break
                    
            if valid:
                return u
    return None   
    
def relabel(Gf, push_relabel_list, u):
    push_relabel_list[u].h = sys.maxsize
    for v in range(len(push_relabel_list)):
        if v != u and Gf[u][v] != sys.maxsize:
            push_relabel_list[u].h = min(push_relabel_list[u].h, push_relabel_list[v].h + 1)

def push_relabel(E, s, t):          
    # begin of init preflow
    Gf = copy.deepcopy(E)    
    
    push_relabel_list = []
    for _ in range(E.row()):
        v = empty()
        v.h = 0
        v.e = 0
        push_relabel_list.append(v)
        
    F = matrix(E.row(), E.row())
    for i in range(E.row()):
        for j in range(E.row()):
            F[i][j] = 0   
            
    push_relabel_list[s].h = E.row()
    for v in range(E.row()):
        if v == s or E[s][v] == sys.maxsize:
            continue
        F[s][v] = E[s][v]
        push_relabel_list[v].e = E[s][v]
        push_relabel_list[s].e -= E[s][v]
        Gf[s][v] = sys.maxsize
        Gf[v][s] = E[s][v]
    # end of init preflow
    
    while True:
        valid_push_u, valid_push_v = get_valid_push(Gf, push_relabel_list, s, t)
        if valid_push_u != None:
            push(E, Gf, F, push_relabel_list, valid_push_u, valid_push_v)
            continue
        
        valid_relabel_u = get_valid_relabel(Gf, push_relabel_list, s, t)
        if valid_relabel_u != None:
            relabel(Gf, push_relabel_list, valid_relabel_u)
        else:
            break
            
    return F
    
def discharge(E, Gf, F, push_relabel_list, u):
    current = 0
    while push_relabel_list[u].e > 0:
        if current < len(push_relabel_list[u].N):
            v = push_relabel_list[u].N[current]
        else:
            v = None
        if v == None:
            relabel(Gf, push_relabel_list, u)
            current = 0
        elif Gf[u][v] != sys.maxsize and push_relabel_list[u].h == push_relabel_list[v].h + 1:
            push(E, Gf, F, push_relabel_list, u, v)
        else:
            current += 1
    
def relabel_to_front(E, s, t):   
    # begin of init preflow
    Gf = copy.deepcopy(E)    
    
    push_relabel_list = []
    for _ in range(E.row()):
        v = empty()
        v.h = 0
        v.e = 0
        push_relabel_list.append(v)
        
    F = matrix(E.row(), E.row())
    for i in range(E.row()):
        for j in range(E.row()):
            F[i][j] = 0   
            
    push_relabel_list[s].h = E.row()
    for v in range(E.row()):
        if v == s or E[s][v] == sys.maxsize:
            continue
        F[s][v] = E[s][v]
        push_relabel_list[v].e = E[s][v]
        push_relabel_list[s].e -= E[s][v]
        Gf[s][v] = sys.maxsize
        Gf[v][s] = E[s][v]
    # end of init preflow
    
    L = []
    for i in range(E.row()):
        if i != s and i != t:
            L.append(i)
            
    for u in range(len(push_relabel_list)):
        push_relabel_list[u].N = []
        for i in range(E.row()):
            if i == u:
               continue
            if E[i][u] != 0 or E[u][i] != 0:
                push_relabel_list[u].N.append(i)
                
    L_current = 0
    while L_current < len(L):
        u = L[L_current]        
        old_height = push_relabel_list[u].h
        discharge(E, Gf, F, push_relabel_list, u)
        if push_relabel_list[u].h > old_height:
            del L[L_current]
            L.insert(0, u)
            L_current = 1
        else:
            L_current += 1
            
    return F            
    
class MyTest(unittest.TestCase):
    def test_ford_fulkerson(self):   
        for _ in range(100):
            node_count = 10
            E, s, t = create_maximum_flow_graph(node_count)
            E2 = ford_fulkerson(E, s, t)
            
            flow_out = 0
            flow_in = 0
            for i in range(node_count):
                if i != s:
                    flow_out += E2[s][i]
                if i != t:
                    flow_in += E2[i][t]
            self.assertTrue(flow_out == flow_in)
            
    def test_push_relabel_against_ford_fulkerson(self):            
            for _ in range(300):
                seed = random.randint(0, sys.maxsize)
                #print(seed)
                random.seed(seed)                
                node_count = 8
                E, s, t = create_maximum_flow_graph(node_count)
                E1 = ford_fulkerson(E, s, t)
                E2 = push_relabel(E, s, t)
                flow_in_1 = 0
                flow_in_2 = 0
                
                for i in range(node_count):
                    if i != t:
                        flow_in_1 += E1[i][t]
                        flow_in_2 += E2[i][t]
                        
                self.assertTrue(flow_in_1 == flow_in_2)  
          
    def test_relabel_to_front(self):
        for _ in range(300):
            seed = random.randint(0, sys.maxsize)
            #print(seed)
            random.seed(seed)                
            node_count = 8
            E, s, t = create_maximum_flow_graph(node_count)
            E1 = push_relabel(E, s, t)
            E2 = relabel_to_front(E, s, t)
            flow_in_1 = 0
            flow_in_2 = 0
            
            for i in range(node_count):
                if i != t:
                    flow_in_1 += E1[i][t]
                    flow_in_2 += E2[i][t]
                    
            self.assertTrue(flow_in_1 == flow_in_2)              

if __name__ == '__main__':
    unittest.main()
