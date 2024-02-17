from enum import Enum
import unittest
import copy
import random
import utility

class Equality(Enum):
    equal = 0
    less = 1
    less_equal = 2
    bigger = 3
    bigger_equal = 4
    none = 5

class poly_item:
    def __init__(self, var, coef):
        self.var =var
        self.coef = coef
        
    def __str__(self):
        ret = ''
        coef = self.coef
        if coef != 0:
            if coef > 0:
                ret += '+ '
            else:
                ret += '- '
            if abs(coef) != 1:
                ret += str(abs(coef))
            ret += '(' + self.var + ')'
        return ret

class polynomial:
    def __init__(self, items, equality, constant):
        self.items = items
        self.equality = equality
        self.constant = constant
        
    def __str__(self):
        ret = ''
        for item in self.items:
            ret += str(item) + ' '
        if self.equality == Equality.none:
            return ret
        elif self.equality == Equality.equal:
            ret += '= '
        elif self.equality == Equality.less:
            ret += '< '
        elif self.equality == Equality.less_equal:
            ret += '<= '
        elif self.equality == Equality.bigger:
            ret += '> '
        elif self.equality == Equality.bigger_equal:
            ret+= '>= '     
            
        ret += str(self.constant)
        
        return ret
                
        
class ObjectiveGoal(Enum):
    max = 0
    min = 1
        
# linear program with constarints with only <=, =, >= can be transform to standard form
# constarint with < or > cannot be trasnformed
class linear_program:
    def __init__(self, objective_function, objective_goal, constraints):
        self.objective_function = objective_function
        self.objective_goal = objective_goal
        self.constraints = constraints
        
    def is_std_form(self):
        if self.objective_goal != ObjectiveGoal.max:
            return False
            
        if not self.valid_nonnegativity_constraints():
            return False
            
        for constraint in self.constraints:
            if not self.is_nonnegative_constraint(constraint):
                if constraint.equality != Equality.less_equal:
                    return False
            
        return True
        
    def valid_nonnegativity_constraints(self):
        lack = self.get_lack_of_nonnegativity_constraints()
        if len(lack) == 0:
            return True
        else:
            return False
        
    def get_all_vars(self):
        vars = set()
        for constraint in self.constraints:
            for item in constraint.items:
                vars.add(item.var)
                
        return vars
        
    def is_nonnegativity_constraint(self, constraint):
        if constraint.equality == Equality.bigger_equal and constraint.constant == 0 and len(constraint.items) == 1:
            return True
        else:
            return False
        
    def get_lack_of_nonnegativity_constraints(self):      
        lack_nonnegativity_vars = self.get_all_vars()
        
        for constraint in self.constraints:
            if self.is_nonnegativity_constraint(constraint):
                lack_nonnegativity_vars.remove(constraint.items[0].var)
                
        return lack_nonnegativity_vars
        
    def get_var_str_and_index(self, var):
        s = var
        index = -1
        for i in range(len(var)):
            if '0' <= var[i] and var[i] <= '9':
                s = var[:i]
                index = int(var[i:])
        return s, index
        
    def get_next_var(self, var):
        s, max_index = self.get_var_str_and_index(var)
        for var in self.get_all_vars():
            s2, index2 = self.get_var_str_and_index(var)
            if s == s2 and index2 > max_index:
                max_index = index2
        return s + str(max_index + 1)        
        
    def is_nonnegative_constraint(self, constraint):
        has_one_coef_1 = False
        for i in range(len(constraint.items)):
            coef = constraint.items[i].coef                
            if coef != 0 and coef != 1:
                return False
            if coef == 1:
                if has_one_coef_1 == True:
                    return False
                else:
                    has_one_coef_1 = True
                    
        if constraint.constant != 0:
            return False
            
        if constraint.equality != Equality.bigger_equal:
            return False
            
        return True
                    
    def to_std_form(self):
        if self.is_std_form():
            return
            
        #set objective to max
        if self.objective_goal == ObjectiveGoal.min:
            self.objective_goal = ObjectiveGoal.max
            for item in self.objective_function.items:
                item.coef *= -1
                
        #add nonnegativity constraints
        if not self.valid_nonnegativity_constraints():
            lack_of_nonnegativity = self.get_lack_of_nonnegativity_constraints()
            for var in lack_of_nonnegativity:
                next_var = self.get_next_var(var)
                for constraint in self.constraints:
                    items_to_add = []
                    for item in constraint.items:
                        if item.var == var:
                            items_to_add.append(poly_item(next_var, item.coef * -1))
                    constraint.items += items_to_add
                
                self.constraints.append(polynomial([poly_item(next_var, 1)], Equality.bigger_equal, 0))
                
                items_to_add = []
                for item in self.objective_function.items:
                    if item.var == var:
                        items_to_add.append(poly_item(next_var, item.coef * -1 ))
                self.objective_function.items += items_to_add
                
                self.constraints.append(polynomial([poly_item(var, 1)], Equality.bigger_equal, 0))
                
        # convert equality to inequality
        new_constraints = []
        for constraint in self.constraints:
            if self.is_nonnegative_constraint(constraint):
                continue
            if constraint.equality == Equality.equal:
                constraint.equality = Equality.bigger_equal
            
                new_constraint = copy.deepcopy(constraint)
                new_constraint.equality = Equality.less_equal
                new_constraints.append(new_constraint)
            
        self.constraints = self.constraints + new_constraints
        
        # convert >= to <=
        for constraint in self.constraints:
            if self.is_nonnegative_constraint(constraint):
                continue
                
            if constraint.equality == Equality.bigger_equal:
                constraint.equality = Equality.less_equal
                for item in constraint.items:
                    item.coef *= -1
                constraint.constant *= -1
        
    def get_slack_form(self):
        if not self.is_std_form():
            self.to_std_form()
            
        constraints = []
        for constraint in self.constraints:
            if not self.is_nonnegativity_constraint(constraint):
                constraints.append(constraint)
                
        max_index = 0
        all_vars = self.get_all_vars()
        for var in all_vars:
            var2, index = self.get_var_str_and_index(var)
            max_index = max(max_index, index)
        
                
        var_count = len(constraints) + max_index + 1
            
        slack = slack_form()
        slack.z = 'z'
        slack.v = self.objective_function.constant
        
        slack.N = []
        for var in self.get_all_vars():
            var2, index = self.get_var_str_and_index(var)
            slack.N.append(index)
            
        slack.N.sort()
        
        slack.B = []
        index = max_index
        for i in constraints:
            index += 1
            slack.B.append(index)  
        
        slack.c = [0] * var_count
        for j in range(len(self.objective_function.items)):
            item = self.objective_function.items[j]
            var, index = self.get_var_str_and_index(item.var)
            slack.c[index] = item.coef 
                
        slack.b = [0] * var_count   
        for i in range(len(constraints)):
            slack.b[var_count - len(constraints) + i] = constraints[i].constant
        
        slack.A = utility.matrix(var_count, var_count)
        for i in range(len(constraints)):
            constraint = constraints[i]
            for j in range(len(constraint.items)):
                item = constraint.items[j]
                var2, index = self.get_var_str_and_index(item.var)
                slack.A[var_count - len(constraints) + i][index] = item.coef
                        
        return slack
        
    def __str__(self):
        ret = ''
        indention = 10
        if self.objective_goal == ObjectiveGoal.max:
            goal_str = 'maximize'
        elif self.objective_goal == ObjectiveGoal.min:
            goal_str = 'minimize'
            
        ret += goal_str
        for _ in range(len(goal_str), indention):
            ret += ' '
        ret += str(self.objective_function)
        ret += '\n'
        ret += 'subject to\n'
        
        for constraint in self.constraints:
            ret += str(constraint)
            ret += '\n'
            
        return ret
        
class slack_form:
    def __init__(self):
        self.v = 0
        self.z = ''
        self.c = []
        self.B = []
        self.N = []
        self.b = []
        self.A = utility.matrix(0, 0)
        
    def __str__(self):
        ret = ''
        ret += 'z = ' + str(self.v) 
        
        self.N.sort()
        for n in self.N:
            ret += ' ' + str(poly_item('X' + str(n), self.c[n]))
        ret += '\n'   
        
        self.B.sort()
        for b in self.B:
            ret += str(poly_item('X' + str(b), 1)) + ' = ' + str(self.b[b]) + ' '
            for n in self.N:
                ret += ' ' + str(poly_item('X' + str(n), self.A[b][n] * -1))
            ret += '\n'
        
        return ret

class test_poly(unittest.TestCase):
    def test_print_polynomial(self):
        print(polynomial([poly_item('X0', 1), poly_item('X1', 1)], Equality.none, 1))
        print(polynomial([poly_item('X0', 4), poly_item('X1', 1)], Equality.less_equal, 8))
        print(polynomial([poly_item('X0', 0), poly_item('X1', -3)], Equality.less_equal, 8))
        print(polynomial([poly_item('X0', 1)], Equality.bigger_equal, 0))
        
    def _test_print_linear_program(self):
        obj = polynomial([poly_item('X0', 1), poly_item('X1', 1)], Equality.none, 0)
        constraint1 = polynomial([poly_item('X0', 4), poly_item('X1', -1)], Equality.less_equal, 8)
        constraint2 = polynomial([poly_item('X0', 2), poly_item('X1', 1)], Equality.less_equal, 10)
        constraint3 = polynomial([poly_item('X0', 5), poly_item('X1', -2)], Equality.bigger_equal, -2)
        constraint4 = polynomial([poly_item('X0', 1)], Equality.bigger_equal, 0)
        constraint5 = polynomial([poly_item('X1', 1)], Equality.bigger_equal, 0)
        lp1 = linear_program(obj, ObjectiveGoal.max, [constraint1,  constraint2,  constraint3,  constraint4,  constraint5])
        print(lp1)
        
    def test_is_std_form(self):
        t = self.assertTrue
        obj = polynomial([poly_item('X0', 1), poly_item('X1', 1)], Equality.none, 0)
        lp1 = linear_program(obj, ObjectiveGoal.min, [])
        t(lp1.is_std_form() == False)
        constraint2 = polynomial([poly_item('X0', 1), poly_item('X1', 1)], Equality.bigger, 1)
        lp1 = linear_program(obj, ObjectiveGoal.max, [constraint2])
        t(lp1.is_std_form() == False)    
        
        constraint2 = polynomial([poly_item('X0', 1), poly_item('X1', 1)], Equality.less_equal, 1)
        constraint3 = polynomial([poly_item('X0', 1)], Equality.bigger_equal, 0) 
        constraint4 = polynomial([poly_item('X1', 1)], Equality.bigger_equal, 0) 
        lp1 = linear_program(obj, ObjectiveGoal.max, [constraint2, constraint3])
        t(lp1.is_std_form() == False)        
        lp1 = linear_program(obj, ObjectiveGoal.max, [constraint2, constraint3, constraint4])
        t(lp1.is_std_form() == True)
        lp1 = linear_program(obj, ObjectiveGoal.max, [constraint3, constraint4])
        t(lp1.is_std_form() == True)        
        
        constraint1 = polynomial([poly_item('X0', 1)], Equality.bigger_equal, 0) 
        constraint2 = polynomial([poly_item('X0', 0), poly_item('X1', 1)], Equality.bigger, 0) 
        lp1 = linear_program(obj, ObjectiveGoal.max, [constraint1, constraint2])
        t(lp1.is_std_form() == False)           
        
    def test_to_std_form1(self):
        obj = polynomial([poly_item('X0', -2), poly_item('X1', 3)], Equality.none, 0)
        constraint1 = polynomial([poly_item('X0', 1), poly_item('X1', 1)], Equality.equal, 7)
        constraint2 = polynomial([poly_item('X0', 1), poly_item('X1', -2)], Equality.less_equal, 4)
        constraint3 = polynomial([poly_item('X0', 1)], Equality.bigger_equal, 0)
        lp1 = linear_program(obj, ObjectiveGoal.min, [constraint1,  constraint2,  constraint3]) 
        lp1.to_std_form()
        self.assertTrue(lp1.is_std_form())
        
    def gen_linear_program(self, min, max, var_count, constraint_count):
        def n():
            nonlocal min
            nonlocal max
            return random.randint(min, max)
            
        def e():
            n = random.randint(0, 2)
            if n == 0:
                return Equality.equal
            elif n == 1:
                return Equality.bigger_equal
            elif n == 2:
                return Equality.less_equal
            return None
        
        poly_items = []
        for i in range(var_count):
            poly_items.append(poly_item('X'+ str(i), n()))
        
        obj = polynomial(poly_items, Equality.none, 0)
            
        constraints = []
        for i in range(constraint_count):
            vars = []
            for j in range(var_count):
                vars.append(poly_item('X'+ str(j), n()))
            constraints.append(polynomial(vars, e(), n()))
        
        goal = ObjectiveGoal.min
        if random.randint(0, 1) == 0:
            goal = ObjectiveGoal.max
        
        return linear_program(obj, goal, constraints)  
 
    def test_to_std_form2(self):     
        for _ in range(10):
            lp1 = self.gen_linear_program(-100, 100, 5, 5)
            lp1.to_std_form()
            self.assertTrue(lp1.is_std_form())
            #print(lp1)
            slack1 = lp1.get_slack_form()
            #print(slack1)
        
class test_slack_form(unittest.TestCase):
    def _test1(self):
        obj = polynomial([poly_item('X0', 2), poly_item('X1', -3)], Equality.none, 0)
        constraint1 = polynomial([poly_item('X0', 1), poly_item('X1', 1)], Equality.equal, 7)
        constraint2 = polynomial([poly_item('X0', 1), poly_item('X1', -2)], Equality.less_equal, 4)
        constraint3 = polynomial([poly_item('X0', 1)], Equality.bigger_equal, 0)
        lp1 = linear_program(obj, ObjectiveGoal.max, [constraint1,  constraint2,  constraint3]) 
        lp1.to_std_form()
        print(lp1)
        slack1 = lp1.get_slack_form()
        print(slack1)
        
if __name__ == '__main__':
    unittest.main()
