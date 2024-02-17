import unittest
import random
import copy
from utility import *
import sys
from binary_search_tree import binary_search_tree
import math

'''
Demo dynamic programming by 4 examples
1. Rod cutting
2. Matrix chain
3. Longest common subsequence
4. Optimal binary search tree

'''

def rod_cut_bruce_force(prices):
    return rod_cut_bruce_force_with_len(prices,  len(prices))

def rod_cut_bruce_force_with_len(prices, n):
    if n == 0:
        return 0
        
    optimal_value = -1
    for i in range(n):
        optimal_value = max(optimal_value,  prices[i] + rod_cut_bruce_force_with_len(prices, n - (i + 1)))
        
    return optimal_value
        
def rod_cut_top_down(prices):
    n = len(prices)
    table = [-1] * (n + 1)
    return rod_cut_top_down_with_size_table(prices, n, table)
        
def rod_cut_top_down_with_size_table(prices, n, table):
    if n == 0:
        return 0
        
    if (table[n] != -1):
        return table[n]
        
    optimal_value = -1
    for i in range(1, n + 1):
        optimal_value = max(optimal_value,  prices[i - 1] + rod_cut_top_down_with_size_table(prices, n - i, table))
        
    table[n] = optimal_value
        
    return optimal_value

def rod_cut_bottom_up(prices):
    n = len(prices)
    opt_value = copy.deepcopy(prices)
    opt_value.insert(0, 0)
    selection = [-1] * (n + 1)

    for i in range(1, n + 1):
        selection[i] = i        
        for j in range(i):
            temp = opt_value[i-j] + opt_value[j]
            if opt_value[i] < temp:
                opt_value[i] = temp
                selection[i] = j
                
    return opt_value[n],  selection
    
def print_selection(selection, n):
    first_time = True
    while n > 0:
        if not first_time:
            print(', ',  end = '')
        
        first_time = False
        print(selection[n],  end = '')
        n -= selection[n]
    print('')
            
def matrix_chain_top_down(dims):
    n = len(dims) - 1
    table = []
    selection = []
    for i in range(n + 1):
        table.append([])
        selection.append([])
        for j in range(n + 1):
            if i == j:
                table[i].append(0)
                selection[i].append(i)
            else:
                table[i].append(sys.maxsize)
                selection[i].append(0)
        
    return matrix_chain_top_down_with_range(dims, table, selection, 1, n)
    
def matrix_chain_top_down_with_range(dims, table, selection, i, j):
    if i == j:
        return table, selection
    
    if table[i][j] != sys.maxsize:
        return table, selection
    
    for k in range(i, j):
        table1, selection1 = matrix_chain_top_down_with_range(dims, table, selection, i, k)
        table2, selection2 = matrix_chain_top_down_with_range(dims, table, selection, k+1, j)
        q = table1[i][k] + \
              table2[k+1][j] + \
              dims[i-1] * dims[k] * dims[j]
              
        if q < table[i][j]:
            table[i][j] = q
            selection[i][j] = k
                               
    return table, selection
    
def matrix_chain_bottom_up(dims):
    n = len(dims) - 1
    table = []
    selection = []
    for i in range(n + 1):
        table.append([])
        selection.append([])
        for j in range(n + 1):
            if i == j:
                table[i].append(0)
                selection[i].append(i)
            else:
                table[i].append(sys.maxsize)
                selection[i].append(0)
             
    for length in range(2, n + 1):
        for i in range(1, n-length+2):
            for j in range(i, i + length - 1):
                q = table[i][j] + table[j + 1][i+length - 1] + dims[i-1] * dims[j] * dims[i+length - 1]
                if table[i][i + length - 1] > q:
                    table[i][i + length - 1] = q
                    selection[i][i+length-1] = j
                    
    return table, selection
  
def print_parenthesis(selection):
    print_parenthesis_with_range(selection, 1, len(selection) - 1)
    print('')
  
def print_parenthesis_with_range(selection, i, j):
    if i == j:
        print(i, end= '')
    else:
        print('(',  end = '')
        print_parenthesis_with_range(selection, i, selection[i][j])
        print_parenthesis_with_range(selection, selection[i][j] + 1, j)
        print(')',  end = '')
            
            
def lcs_top_down(x, y):
    m = len(x)
    n = len(y)
    
    c = []
    selection = []
    
    for i in range(m + 1):
        c.append([])
        selection.append([])
        for j in range(n + 1):
            c[i].append(-sys.maxsize)
            selection[i].append('')
            
    for i in range(m + 1):
        c[i][0] = 0
        
    for i in range(n + 1):
        c[0][i] = 0
            
    lcs = lcs_top_down_with_index(x, y, m, n, c, selection)
    return lcs, selection
        
def lcs_top_down_with_index(x, y, m, n, c, selection):    
    if c[m][n] != -sys.maxsize:
        return c[m][n]
    
    if m == 0 or n == 0:
        return 0            
    elif x[m - 1] == y[n - 1]:
        c[m][n] = lcs_top_down_with_index(x, y, m - 1, n - 1, c, selection) + 1
        selection[m][n] = 'topleft'
    else:
        top_lcs = lcs_top_down_with_index(x, y, m - 1, n, c, selection)
        left_lcs = lcs_top_down_with_index(x, y, m, n - 1, c, selection)
        if left_lcs > top_lcs:
            c[m][n] = left_lcs
            selection[m][n] = 'left'
        else:
            c[m][n] = top_lcs
            selection[m][n] = 'top'
            
    return c[m][n]

def lcs_bottom_up(x, y):
    m = len(x)
    n = len(y)
    
    x = ' ' + x
    y = ' ' + y
    
    c = []
    selection = []
    
    for i in range(m + 1):
        c.append([])
        selection.append([])
        for j in range(n + 1):
            c[i].append(0)   
            selection[i].append('')
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if x[i] == y[j]:
                c[i][j] = c[i - 1][j - 1] + 1
                selection[i][j] = 'topleft'
            else:
                left = c[i][j-1]
                up = c[i-1][j]
                
                if left > up:
                    c[i][j] = left
                    selection[i][j] = 'left'
                else:
                    c[i][j] = up
                    selection[i][j] = 'up'
                
    return c[m][n], selection
       
def get_lcs_string(x, y, selection):
    return get_lcs_string2(x, y, len(x), len(y), selection)
       
def get_lcs_string2(x, y, m, n, selection):
    if m == 0 or n == 0:
        return ''
        
    if selection[m][n] == 'topleft':
        return get_lcs_string2(x, y, m -1,  n - 1,  selection) + x[m-1]
    elif selection[m][n] == 'left':
        return get_lcs_string2(x, y, m,  n - 1,  selection)
    else:
        return get_lcs_string2(x, y, m -1,  n,  selection)
            
def sum_of_probablity(p, q, i, j):
    sum = 0
    for k in range(i, j + 1):
        sum += p[k]
    for k in range(i - 1,  j + 1):
        sum += q[k]
    return sum

def optimal_bst_top_down2(p, q, e, w, selection, i, j):
    if j == i - 1:
        return q[i-1]
     
    if e[i][j] != sys.maxsize:
        return e[i][j]
           
    for r in range(i,  j + 1):
        if w[i][j] == sys.maxsize:
            w[i][j] = sum_of_probablity(p, q, i, j)
            
        temp = optimal_bst_top_down2(p, q, e, w, selection, i, r - 1) + \
                    optimal_bst_top_down2(p, q, e, w, selection, r + 1, j) + \
                    w[i][j]
            
        if temp < e[i][j]:
            e[i][j] = temp
            selection[i][j] = r
                    
    return e[i][j]

def optimal_bst_top_down(p, q):
    j = len(p) - 1
    e = []
    w = []
    selection = []
    for i in range(j + 1):
        e.append([])
        w.append([])
        selection.append([])
        for j in range(j + 1):
            e[i].append(sys.maxsize)
            w[i].append(sys.maxsize)
            selection[i].append(sys.maxsize)
            
    return optimal_bst_top_down2(p, q, e, w, selection, 1, j), selection
           
def optimal_bst_bottom_up(p, q):
    m = len(p) - 1
    e = []
    selection = []
    for i in range(m + 2):
        e.append([])
        for j in range(m + 2):
            if j == i - 1:
                e[i].append(q[i-1])
            else:
                e[i].append(sys.maxsize)
                
    for i in range(m + 1):
        selection.append([])
        for j in range(m + 1):
            selection[i].append(0)
            
    for length in range(1, m + 1):
        for i in range(1, m - length + 2):
            for j in range(i, i + length):
                temp = e[i][j - 1] + e[j + 1][i + length - 1] + sum_of_probablity(p, q, i, i + length - 1)
                if e[i][i + length - 1] > temp:
                    e[i][i + length - 1] = temp
                    selection[i][i + length - 1] = j
    
    return e[1][m], selection
            
            
class dynamic_programming_test(unittest.TestCase):
    def test_rod_cut(self):
        for _ in range(100):
            random_seed(False)
            count = 10
            prices = [0] * count
            for i in range(count):
                prices[i] = random.randint(1, 10)
                if i > 0:
                    prices[i] += prices[i - 1]
                    
            opt_value1 = rod_cut_bruce_force(prices)
            opt_value2 = rod_cut_top_down(prices)
            opt_value3, selection = rod_cut_bottom_up(prices)
            self.assertTrue(opt_value1 == opt_value2)
            self.assertTrue(opt_value1 == opt_value3)
            
            #print_selection(selection, len(prices))     
            
    def test_matrix_chain1(self):
        dims = ([30, 35, 15, 5, 10, 20, 25])
        n = len(dims) - 1
        table1, selection1 = matrix_chain_top_down(dims)
        self.assertTrue(table1[1][n] == 15125)   
        table2, selection2 = matrix_chain_bottom_up(dims)
        self.assertTrue(table2[1][n] == 15125)   
        self.assertTrue(selection1 == selection2)
        #print_parenthesis(selection2)

    def test_matrix_chain2(self):
        for _ in range(10):
            random_seed(False)
            dims = []
            for i in range(random.randint(2, 10)):
                for j in range(i + 1):
                    dims.append(random.randint(2, 10))

            n = len(dims) - 1
            table1, selection1 = matrix_chain_top_down(dims)
            table2, selection2 = matrix_chain_bottom_up(dims)
            self.assertTrue(table1[1][n] == table2[1][n])   
            self.assertTrue(selection1 == selection2)
            #print_parenthesis(selection2)
            
    def check_lcs_string(self, lcs_string, x, y):
        x_index = 0
        y_index = 0
        for i in range(len(lcs_string)):
            char = lcs_string[i]
            while x[x_index] != char:
                x_index += 1
                self.assertTrue(x_index < len(x))
            while y[y_index] != char:
                y_index += 1
                self.assertTrue(y_index < len(y))
            
    def test_lcs1(self):
        x = 'ABCBDAB' 
        y = 'BDCABA'
        lcs1, selection1 = lcs_top_down(x, y)
        self.assertTrue(lcs1 == 4)  
        lcs_string1 = get_lcs_string(x, y, selection1)
        self.check_lcs_string(lcs_string1, x, y)
        #print(lcs_string1)
        
        lcs2, selection2 = lcs_bottom_up(x, y)
        self.assertTrue(lcs2 == 4)
        lcs_string2 = get_lcs_string(x, y, selection2)
        self.check_lcs_string(lcs_string2, x, y)
        #print(lcs_string2)
        
    def test_lcs2(self):
        for _ in range(10):
            random_seed(False)
            char_set = ['A', 'B', 'C', 'D']
            x_len = random.randint(5, 20)
            y_len = random.randint(5, 20)
            x = '' 
            for i in range(x_len):
                x += random.choice(char_set)
            y = ''
            for i in range(y_len):
                y += random.choice(char_set)        
            
            lcs1, selection1 = lcs_top_down(x, y)
            lcs_string1 = get_lcs_string(x, y, selection1)
            self.check_lcs_string(lcs_string1, x, y)
            #print(lcs_string1)
            
            lcs2, selection2 = lcs_bottom_up(x, y)
            lcs_string2 = get_lcs_string(x, y, selection2)
            self.check_lcs_string(lcs_string2, x, y)
            #print(lcs_string2)
            
            self.assertTrue(lcs1 == lcs2)
            
    def build_bst_with_range(self, bst, selection, i, j):
        if i > j:
            return            
        r = selection[i][j]
        bst.insert(r)
        self.build_bst_with_range(bst, selection, i, r - 1)    
        self.build_bst_with_range(bst, selection, r + 1, j)
        
    def build_bst(self, selection):
        bst = binary_search_tree()
        self.build_bst_with_range(bst, selection, 1, len(selection) -1)
        return bst
        
    def get_bst_value(self, bst, p, q, r, level):
        value = p[r.key] * (1 + level)
        if r.left == bst.null:
            value += q[r.key - 1] * (level + 2)
        else:
            value += self.get_bst_value(bst, p, q, r.left, level + 1)
            
        if r.right == bst.null:
            value += q[r.key] * (level + 2)
        else:
            value += self.get_bst_value(bst, p, q, r.right, level + 1)
            
        return value
       
    def check_bst(self, bst, p, q, value):
        value2 = self.get_bst_value(bst, p, q, bst.root, 0)
        self.assertTrue(math.fabs(value - value2) < 0.00000001)
        
    def test_optimal_bst_1(self):
        p = [0, 0.15, 0.1, 0.05, 0.1, 0.2]
        q = [0.05, 0.1, 0.05, 0.05, 0.05, 0.1]
        
        value1, selection1 = optimal_bst_top_down(p, q)
        self.assertTrue(math.fabs(value1 -  2.75) < 0.00000001)
        bst1 = self.build_bst(selection1)
        self.check_bst(bst1, p, q, value1)
        #print(bst1.get_printed_tree())
        
        value2, selection2 = optimal_bst_bottom_up(p, q)
        self.assertTrue(math.fabs(value2 - 2.75) < 0.00000001)
        bst2 = self.build_bst(selection2)
        self.check_bst(bst2, p, q, value2)
        #print(bst2.get_printed_tree())
    
if __name__ == '__main__':
    unittest.main()
