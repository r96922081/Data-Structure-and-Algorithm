from utility import matrix
from polynomial_utility  import polynomial, poly_item, Equality, linear_program, ObjectiveGoal, slack_form
from fractions import Fraction as r
import copy
import random
import sys
import unittest

'''
Demo how to solve linear programming problem by simplex algorithm
many problem can be transformed to linear programming problem
Check the linear programming definition online
'''

class unbounded_exception(Exception):
    pass

class infeasible_exception(Exception):
    pass
    
class algorithm_error_exception(Exception):
    pass

def pivot(s, l, e):
    #Compute the coefficients of the equation for new basic variable xe
    N = s.N
    B = s.B
    A = s.A
    b = s.b
    c = s.c
    v = s.v
    
    new_A = matrix(A.col(), A.col())
    new_b = [0] * len(b)    

    new_b[e] = b[l]/A[l][e]    
    for j in N:
        if j != e:
            new_A[e][j] = A[l][j]/A[l][e]
    new_A[e][l] = r(1)/A[l][e] 
    
    #Compute the coefficients of the remaining constraints
    for i in B:
        if i != l:
            new_b[i] = b[i] - A[i][e] * new_b[e]
            for j in N:
                if j != e:
                    new_A[i][j] = A[i][j] - A[i][e] * new_A[e][j]
            new_A[i][l] = A[i][e] * new_A[e][l] * -1
    
    #Compute the objective function
    new_v = v + c[e] * new_b[e]
    new_c = [0] * (A.row())
    for j in N:
        if j != e:
            new_c[j] = c[j] - c[e] * new_A[e][j]
            
    new_c[l] = c[e]  * -1 * new_A[e][l]
    
    new_N = copy.deepcopy(N)
    new_N.remove(e)
    new_N.append(l)
    
    new_B = copy.deepcopy(B)
    new_B.remove(l)
    new_B.append(e)
    
    s2 = slack_form()
    s2.N = new_N
    s2.B = new_B
    s2.A = new_A
    s2.b = new_b
    s2.c = new_c
    s2.v = new_v
    
    return s2    

def initialize_simplex(original_slack):
    k = -1
    min_value = sys.maxsize
         
    for i in original_slack.B:
        if original_slack.b[i] < min_value:
            k = i
            min_value = original_slack.b[i]
    if min_value >= 0:
        return original_slack
    else:        
        s = get_aux_slack(original_slack)
        l = k
        s = pivot(s, l, 0)
        
    #iterate the while loop of lines 3–12 of SIMPLEX until an optimal solution to Laux is found
    delta = [0] * (len(s.b))
    previous_v = s.v
    
    while True:
        if s.v < previous_v:
            raise  algorithm_error_exception()

        previous_v = s.v        
        N = s.N
        if not has_nonnegative_element(s.c, N):
            break
        
        for e in N:
            if s.c[e] > 0:
                for i in s.B:
                    if s.A[i][e] > 0:
                        delta[i] = s.b[i]/s.A[i][e]
                    else:
                        delta[i] = float("inf")
                min = float("inf")
                l = 0
                for i in s.B:
                    if delta[i] < min:
                        min = delta[i]
                        l = i
                if min == float("inf"):
                    raise unbounded_exception()
                else:
                    s = pivot(s, l, e)
                    break
                    
    if s.v == 0:
        if 0 in s.B:
            non_zero_non_basic = -1
            for e in s.N:
                if s.A[0][e] != 0:
                    non_zero_non_basic = e
                    break
            if non_zero_non_basic == -1:
                raise algorithm_error_exception()
            s = pivot(s, 0, non_zero_non_basic)
        s.N.remove(0)
            
        s.v = original_slack.v
        s.c = copy.deepcopy(original_slack.c)
        
        for b in s.B:            
            if s.c[b] != 0:
                s.v += s.c[b] * s.b[b]
                for j in range(s.A.col()):
                    s.c[j] += s.c[b] * s.A[b][j] * -1
        return s
    else:
        raise infeasible_exception()
            
            
def has_nonnegative_element(c, N):
        for j in N:
            if c[j] > 0:
                return True
        return False

def simplex(slack_form):
    s  = initialize_simplex(slack_form)
    delta = [0] * (len(s.b))
    previous_v = s.v
    
    while True:
        if s.v < previous_v:
            raise algorithm_error_exception()
            
        previous_v = s.v        
        N = s.N
        if not has_nonnegative_element(s.c, N):
            break
            
        for e in N:
            if s.c[e] > 0:
                for i in s.B:
                    if s.A[i][e] > 0:
                        delta[i] = s.b[i]/s.A[i][e]
                    else:
                        delta[i] = float("inf")
                min = float("inf")
                l = 0
                for i in s.B:
                    if delta[i] < min:
                        min = delta[i]
                        l = i
                if min == float("inf"):
                    raise unbounded_exception()
                else:
                    s = pivot(s, l, e)
                    break
    
    x = [0] * (len(s.b))
    for i in range(1, len(x)):
        if i in s.B:
            x[i] = s.b[i]
        else:
            x[i] = 0

    return s.v, x
    
def get_aux_slack(slack):
    slack_aux = copy.deepcopy(slack)
    
    slack_aux.N.append(0)
    
    for i in range(len(slack_aux.c)):
        slack_aux.c[i] = 0
    slack_aux.c[0] = -1
    
    for i in range(len(slack_aux.b)):
        if i in slack_aux.B:
            slack_aux.A[i][0] = -1
        
    return slack_aux

class test_simplex(unittest.TestCase):
    def test1(self):
        obj = polynomial([poly_item('X1', 3), poly_item('X2', 1), poly_item('X3', 2)], Equality.none, 0)
        constraint1 = polynomial([poly_item('X1', 1), poly_item('X2', 1), poly_item('X3', 3)], Equality.less_equal, 30)
        constraint2 = polynomial([poly_item('X1', 2), poly_item('X2', 2), poly_item('X3', 5)], Equality.less_equal, 24)
        constraint3 = polynomial([poly_item('X1', 4), poly_item('X2', 1), poly_item('X3', 2)], Equality.less_equal, 36)
        constraint4 = polynomial([poly_item('X1', 1)], Equality.bigger_equal, 0)
        constraint5 = polynomial([poly_item('X2', 1)], Equality.bigger_equal, 0)
        constraint6 = polynomial([poly_item('X3', 1)], Equality.bigger_equal, 0)
        lp1 = linear_program(obj, ObjectiveGoal.max, [constraint1,  constraint2,  constraint3,  constraint4,  constraint5,  constraint6]) 
        slack1 = lp1.get_slack_form()
        v, x = simplex(slack1)
        self.assertTrue(v == 28)
        
    def test2(self):
        ok_count = 0
        unbounded_count = 0
        infeasible_count = 0
            
        for _ in range(1000):            
            min = -10
            max = 10
            
            variable_count = 3
            poly_param = []
            for i in range(variable_count):
                poly_param.append(poly_item('X' + str(i + 1), random.randint(min, max)))
            obj = polynomial(poly_param, Equality.none, 0)
            
            all_constraints = []
            for i in range(variable_count):
                poly_param = []
                for j in range(variable_count):                    
                    poly_param.append(poly_item('X' + str(i + 1), random.randint(min, max)))
                all_constraints.append(polynomial(poly_param, Equality.less_equal, random.randint(min, max))) 
                all_constraints.append(polynomial([poly_item('X' + str(i + 1), 1)], Equality.bigger_equal, 0))
                
            lp1 = linear_program(obj, ObjectiveGoal.max, all_constraints) 
            slack1 = lp1.get_slack_form()       
            slack1_aux = get_aux_slack(slack1)

            try:
                 v, s = simplex(slack1)            
                 v2, s2 = simplex(slack1_aux)
                 self.assertTrue(v2 == 0)
                 ok_count += 1
            except unbounded_exception:
                v2, s2 = simplex(slack1_aux)             
                self.assertTrue(v2 == 0)
                unbounded_count +=1
            except infeasible_exception:
                infeasible_count +=1
                
if __name__ == '__main__':
    unittest.main()
            
        
    
