import unittest
from collections import deque
import copy
from fractions import Fraction as r
import random
import sys

class point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def __sub__(self, p):
        ret = copy.copy(self)
        ret.x -= p.x
        ret.y -= p.y
        return ret
        
    def __mul__(self, p):
        return self.x * p.y - p.x * self.y
        
    def __str__(self):
        return '(' + str(self.x) + ',' + str(self.y) + ')'
        
    def __repr__(self):
        return self.__str__()
        
    def __eq__(self, p):
        return self.x == p.x and self.y == p.y
        
    def __lt__(self, p2):
        if self.x < p2.x:
            return True
        elif self.x == p2.x and self.y < p2.y:
            return True
        else:
            return False

class binary_tree:
    def __init__(self):
        self.root = None
        self.null = None
        
    def get_null(self):
        return self.null
        
    def set_null(self, null):
        self.null = null
    

class binary_tree_node:   
    def __init__(self, tree):
        self.tree = tree
        self.parent = tree.get_null()
        self.left = tree.get_null()
        self.right = tree.get_null()

    def set_left(self, bt_node):
        self.left = bt_node
        bt_node.parent = self
        
    def set_right(self, bt_node):
        self.right = bt_node
        bt_node.parent = self  
  
    def get_left(self):
        return self.left
        
    def get_right(self):
        return self.right
        
    def get_indention_and_maxkeylen(self, node, indention_count, maxlen):
        ''' For initial call, pass indention_count = 0, maxlen = 0'''
        if node.get_left() != self.tree.get_null():
            indention_count, maxlen = self.get_indention_and_maxkeylen(node.get_left(), indention_count, maxlen)
            
        node.indention = indention_count
        indention_count += 1
        maxlen = max(maxlen, len(str(node)))
        
        if node.right != self.tree.get_null():
            indention_count, maxlen = self.get_indention_and_maxkeylen(node.right, indention_count, maxlen)
            
        return indention_count, maxlen
        
    def get_printed_tree(self):
        ret_str = ''
        indention_count, maxlen = self.get_indention_and_maxkeylen(self, 0, 0)

        q = deque([])
        
        class plainobject:
            pass
            
        q_element = plainobject()
        q_element.node = self
        q_element.level = 1
        q.append(q_element)
        
        printed_indention_count = 0        
        while len(q) != 0:
            q_element = q.popleft()
            node = q_element.node
            level = q_element.level

            last_in_this_level = False
            if len(q) == 0 or level != q[0].level:
                last_in_this_level = True

            for i in range(node.indention  - printed_indention_count) :
                for i in range(maxlen):
                    ret_str += ' '
                printed_indention_count += 1
            
            for i in range(maxlen - len(str(node))):
                ret_str += ' '
            ret_str += str(node)
            printed_indention_count += 1
            
            if last_in_this_level:
                ret_str += '\n'
                printed_indention_count = 0
            
            if node.get_left() != self.tree.get_null():
                q_element = plainobject()
                q_element.node = node.get_left()
                q_element.level =  level + 1
                q.append(q_element)
            if node.right != self.tree.get_null():
                q_element = plainobject()
                q_element.node = node.right
                q_element.level =  level + 1
                q.append(q_element)
                
        return ret_str

class matrix:
    def __init__(self, row, col):
        self.matrix = [[r(0)]]
        self.matrix[0] *= col
        for i in range(1, row):
            self.matrix.append(copy.copy(self.matrix[0]))
        
    def __str__(self):
        ret = ''
        display_space = 0
        for i in range(self.row()):
            for j in range(self.col()):
                if len(str(self[i][j])) > display_space:
                    display_space = len(str(self[i][j]))
        
        for i in range(self.row()):
            for j in range(self.col()):
                if j >= 1:
                    ret += ', '
                ret += str(self[i][j]).rjust(display_space)
            ret += '\n'
            
        return ret

    def row(self):
        return len(self.matrix)
        
    def col(self):
        return len(self.matrix[0])
        
    def __add__(self, m):
        if self.row() != m.row() or self.col() != m.col():
            raise Exception('Size not match for adding')
        ret_matrix = copy.deepcopy(self)
        for i in range(m.row()):
            for j in range(m.col()):
                    ret_matrix[i][j] += m[i][j]
        return ret_matrix
        
    def __sub__(self, m):
        if self.row() != m.row() or self.col() != m.col():
            raise Exception('Size not match for adding')
        ret_matrix = copy.deepcopy(self)
        for i in range(m.row()):
            for j in range(m.col()):
                    ret_matrix[i][j] -= m[i][j]
        return ret_matrix

    def __mul__(self, m):
        if self.col() != m.row():
            raise Exception('Two matrix are not compatible for multipling operation')
        ret_matrix = matrix(self.row(), m.col())
        for i in range(ret_matrix.row()):
            for j in range(ret_matrix.col()):
                for k in range(self.col()):
                    ret_matrix[i][j] += self[i][k] * m[k][j]
        return ret_matrix
        
    def __eq__(self, m):
        if self.row() != m.row() or self.col != self.col:
            return False
        for i in range(len(self.matrix)):
            if self.matrix[i] != m.matrix[i]:
                return False
        return True
        
    def __getitem__(self, index):
        return self.matrix[index] 
  
    def __setitem__(self, index, value):
        self.matrix[index] = value  

    def exchange_row(self, row1, row2):
        ret = copy.deepcopy(self)
        ret[row1], ret[row2] = ret[row2], ret[row1]
        return ret
        
    def delete_row(self, row):
        del self.matrix[row]

    def delete_col(self, col):
        for i in range(self.row()):
            del self[i][col]	        
        
    def det(self):
        if self.row() != self.col():
            raise Exception('only square matrix has determinant')
        if self.row() == 1 and self.col() == 1:
            return self[0][0]
            
        m = copy.deepcopy(self)
        first_row = copy.deepcopy(m[0])
        m.delete_row(0)

        determinant = 0
        sign = 1
        for i in range(len(first_row)):
            m2 = copy.deepcopy(m)
            m2.delete_col(i)
            determinant += sign * m2.det() * first_row[i]
            sign *= -1
        return determinant	
        
class empty:
    pass
    
def create_random_graph(node_count, edge_count, directed):
    V = []
    for i in range(node_count):
        V.append(i)
    E = matrix(node_count, node_count)
    
    for i in range(node_count):
        for j in range(node_count):
            E[i][j] = sys.maxsize
    
    for _ in range(edge_count):
        u = random.randint(0, node_count - 1)
        v = random.randint(0, node_count - 1)
        len = random.randint(1, edge_count)
        E[u][v] = len
        if not directed:
            E[v][u] = len
            
    for i in range(node_count):
        E[i][i] = 0
        
    return V, E
    


class edge:
    def __init__(self, src, dst, len):
        self.src = src
        self.dst = dst
        self.len = len
    
    def __str__(self):
        return '(' + str(self.src) + ', ' + str(self.dst) + ') = ' + str(self.len)

class adjacency_list:
    def __init__(self, vertex_count):
        self.adj_list = []
        self.current_node_iter = 0
        self.all_edge = []
        for _ in range(vertex_count):
            self.adj_list.append([])

    def add_edge(self, u, v, len):
        e = edge(u, v, len)
        self.adj_list[u].append(e)

    def __getitem__(self, index):
        return self.adj_list[index]

    def __len__(self):
        return len(self.adj_list)

    def __str__(self):
        ret = ''
        for i in range(len(self.adj_list)):
            ret += str(i)
            for edge in self.adj_list[i]:
                ret += ' -> '
                ret += str(edge.v)
                ret += '(' + str(edge.len) + ')'
            ret += '\n'
        return ret
        
    def __iter__(self):
        self.current_iter = 0
        self.all_edge = []
        for single_node_adj_list in self.adj_list:
            for edge in single_node_adj_list:
                self.all_edge.append(edge)     
        return self

    def __next__(self):
        if self.current_iter == len(self.all_edge):
            raise StopIteration
        else:
            self.current_iter += 1
            return self.all_edge[self.current_iter - 1]

def get_adjacency_list_from_matrix(m):
    adj_list = adjacency_list(m.row())
    for i in range(m.row()):
        for j in range(m.col()):
            if i != j and m[i][j] != sys.maxsize and m[i][j] != 0:
                adj_list.add_edge(i, j, m[i][j])
    return adj_list

def random_seed(print_seed):
    seed = random.randint(1, sys.maxsize)
    if print_seed:
        print(seed)
    random.seed(seed)

class binary_tree_test(unittest.TestCase):
    def test1(self):
        tree = binary_tree()
        n1 = binary_tree_node(tree)
        n2 = binary_tree_node(tree)
        n3 = binary_tree_node(tree)
        n1.set_left(n2)
        n1.set_right(n3)
        
        n1.get_printed_tree()
        #print(n1.get_printed_tree())

if __name__ == '__main__':
    unittest.main()
