import unittest
import copy
import random
import sys
from binary_search_tree import binary_search_tree
from utility import point, random_seed
import math
        
'''
Demo computational geometry algirhtm

1. segement intersection
2. Finding convex hull by graham scan
3. Finding convex hull by jarvis march
4. Finding closet pair
'''

class segment:
    def __init__(self, left, right):
        if left.x < right.x :
            self.left = left
            self.right = right
        elif left.x == right.x:
            if left.y < right.y:
                self.left = left
                self.right = right
            else:
                self.left = right
                self.right = left               
        else:
            self.left = right
            self.right = left           
        
    def __str__(self):
        return '(' + str(self.left)+ ',' + str(self.right) + ')'
        
    def __repr__(self):
        return self.__str__()
        
    def __eq__(self, p):
        return (self.left == p.left and self.right == p.right) or (self.left == p.right and self.right == p.left)
        
    def __lt__(self, s2):
        p1 = self.right - self.left
        p2 = s2.left - self.left
        if p1.x * p2.y - p1.y * p2.x < 0:
            return True
        else:
            return False
   
class interset_segments:
    def __init__(self, seg1, seg2):
        self.seg1 = seg1
        self.seg2 = seg2
        
    def __eq__(self, p):
        return (self.seg1 == p.seg1 and self.seg2 == p.seg2) or (self.seg1 == p.seg2 and self.seg2 == p.seg1)
        
def direction(pi, pj, pk):
    return (pk - pi) * (pj - pi)
    
def on_segment(pi, pj, pk):
    if direction(pi, pj, pk) != 0:
        return False
    if (min(pi.x, pj.x) <= pk.x and pk.x <= max(pi.x, pj.x)) and \
    (min(pi.y, pj.y) <= pk.y and pk.y <= max(pi.y, pj.y)):
        return True
    else:
        return False
    
def segments_intersect(p1, p2, p3, p4):
    d1 = direction(p3, p4, p1)
    d2 = direction(p3, p4, p2)
    d3 = direction(p1, p2, p3)
    d4 = direction(p1, p2, p4)
    
    if ((d1 > 0 and d2 < 0) or (d1 <0 and d2 > 0)) and \
    ((d3 > 0 and d4 < 0) or (d3 < 0 and d4 > 0)):
        return True
    elif on_segment(p3, p4, p1):
       return True 
    elif on_segment(p3, p4, p2):
       return True   
    elif on_segment(p1, p2, p3):
       return True
    elif on_segment(p1, p2, p4):
       return True
    else:
        return False
        
def segments_intersect_s(s1, s2):
    return segments_intersect(s1.left, s1.right,  s2.left,  s2.right)
    
def brute_force_any_interset(S):
    ret = []
    for i in range(len(S)):
        for j in range(i + 1, len(S)):
            if segments_intersect_s(S[i], S[j]):
                ret.append(S[i])
                ret.append(S[j])
    return ret
    
class segment_bst_node_pair:
    def __init__(self, segment, bst_node):
        self.segment = segment
        self.bst_node = bst_node
 
class point_segment_bst_node_pair_pair:
    def __init__(self, point, segment_bst_node_pair):
        self.segment_bst_node_pair = segment_bst_node_pair
        self.point = point

    #def __eq__(self, b):
    #    return self.segment == b.segment and self.point == b.point
    def __str__(self):
        return '((' + str(self.point)+ '),(' + str(self.segment_bst_node_pair.segment) + ')'
    
    def __repr__(self):
        return self.__str__()        

def sort_point(S):
    for i in range(1, len(S)):
        for j in range(i, 0, -1):
            if S[j].point.x < S[j - 1].point.x:
                S[j - 1], S[j] = S[j], S[j - 1]
            elif S[j - 1].point.x == S[j].point.x:
                if S[j].point is S[j].segment_bst_node_pair.segment.left and S[j - 1].point is S[j-1].segment_bst_node_pair.segment.right:
                    S[j - 1], S[j] = S[j], S[j - 1]
                elif S[j].point is S[j].segment_bst_node_pair.segment.right and S[j - 1] is S[j-1].segment_bst_node_pair.segment.left:
                    break
                else:
                    if S[j].point.y < S[j - 1].point.y:
                        S[j - 1], S[j] = S[j], S[j - 1]
                    else:
                        break
            else:
                break
    
def any_segments_intersect(S):
    endpoints = []
    for s in S:
        if s.left.x > s.right.x:
            s.left, s.right = s.right, s.left        
            
        s_bst = segment_bst_node_pair(s,  None)
        endpoints.append(point_segment_bst_node_pair_pair(s.left, s_bst))
        endpoints.append(point_segment_bst_node_pair_pair(s.right, s_bst))
    sort_point(endpoints)
    sorted_endpoints = endpoints
    print(sorted_endpoints)
    
    bst= binary_search_tree()
        
    for endpoint in sorted_endpoints:
        p = endpoint.point
        s = endpoint.segment_bst_node_pair.segment
        if p == s.left:
            
            # check if 2 nodes intersect at endpoint
            node = bst.root
            while node != None:
                if s.left == node.key.left or s.left == node.key.right or s.right == node.key.left or s.right == node.key.right:
                    return True
                if s < node.key:
                    node = node.left
                else:
                    node = node.right
            
            endpoint.segment_bst_node_pair.bst_node = bst.insert(s)
            bst.print()
            bst_node = endpoint.segment_bst_node_pair.bst_node
            above = bst.predecessor(bst_node)
            below = bst.successor(bst_node)            
            if ( above != None and segments_intersect_s(above.key,  s)) or \
            ( below != None and segments_intersect_s(below.key,  s)):
                return True
                
        if p == s.right:
            bst_node = endpoint.segment_bst_node_pair.bst_node
            above = bst.predecessor(bst_node)
            below = bst.successor(bst_node)            
            if above != None and  below != None and segments_intersect_s(above.key,  below.key):
                return True
            bst.delete_by_node(bst_node)
            
    return False
            
def get_polar_angle(respectPoint, v):
    v2 = copy.deepcopy(v)
    v2.x = v2.x - respectPoint.x
    v2.y = v2.y - respectPoint.y
    v2_r = math.sqrt(v2.x ** 2 + v2.y ** 2)
    
    # angle in radius
    angle = math.asin(v2.y/v2_r)
    
    # angle
    angle = angle / math.pi * 180
    
    if v2.y >= 0:
        if v2.x < 0:
            angle = 180 - angle
    else:
        if v2.x > 0:
            angle = 360 + angle
        else:
            angle = 180 + (0 - angle)
    
    return angle
            
def get_norm(respect_point, p):
    p2 = p - respect_point
    norm = math.sqrt(p2.x ** 2 + p2.y ** 2)
    return norm
            
def graham_scan(Q_param):
    Q = copy.deepcopy(Q_param)
    p0 = point(sys.maxsize, sys.maxsize)
    for p in Q:
        if p.y < p0.y:
            p0 = p
        elif p.y == p0.y and p.x < p0.x:
            p0 = p
    Q.remove(p0)

    Q2 = Q
    Q = []
    
    for p in Q2:
        insert = True
        insert_pos = len(Q)
        p_angle = get_polar_angle(p0, p)
        
        for i in range(len(Q) - 1,  -1,  -1):
            p2_angle = get_polar_angle(p0, Q[i])
            # == case
            if math.fabs(p_angle - p2_angle) < 0.00000001:
                insert = False
                p_norm = get_norm(p0, p)
                p2_norm = get_norm(p0, Q[i])
                if p_norm > p2_norm:
                    Q[i] = p
                break
            elif p2_angle > p_angle:
                insert_pos = i
            else:
                break        
        if insert:
            Q.insert(insert_pos, p)
        
    if len(Q) == 1:
        return [p0, Q[0]]
    
    S = [p0, Q[0], Q[1]]
    
    for i in range(2, len(Q)):
        while len(Q) > 2:
            p0 = S[len(S) - 2]
            p1 = S[len(S) - 1]
            p2 = Q[i]
            
            seg1 = p0 - p1            
            seg2 = p1 - p2
     
            if seg1 * seg2 <= 0:
                S.pop()
            else:
                break
        S.append(Q[i])
          
    return S
    
def jarvis_march(Q_param):
    Q = copy.deepcopy(Q_param)
    lowest = point(0, sys.maxsize)
    highest = point(0, -sys.maxsize)
    for p in Q:
        if p.y < lowest.y or (p.y == lowest.y and p.x < lowest.x):
            lowest = p
            
        if p.y > highest.y or (p.y == highest.y and p.x > highest.x):
            highest = p     
                  
    S = [lowest]
    respect_point = lowest
    Q.remove(lowest)
    
    right_chain = True
    first_time = True
    
    while True:
        polar_angle = 361
        next_p = None
        prev_norm = -sys.maxsize
        if respect_point == highest:
            right_chain = False
        for p in Q:
            if right_chain:
                if p.y < respect_point.y or (p.y == respect_point.y and p.x < respect_point.x):
                    continue
            else:
                if p.y > respect_point.y or (p.y == respect_point.y and p.x > respect_point.x):
                    continue      
            next_angle = get_polar_angle(respect_point, p)
            norm = get_norm(respect_point, p)
            
            # next_angle == polar_angle
            if math.fabs(next_angle - polar_angle) < 0.000000001:
                if norm > prev_norm:
                    polar_angle = next_angle
                    next_p = p
                    prev_norm = norm
            elif next_angle < polar_angle:
                polar_angle = next_angle
                next_p = p
                prev_norm = norm
                
        if next_p == lowest:
           break
        else:
            respect_point = next_p
            S.append(next_p)
            Q.remove(next_p)
            
        if first_time:
            first_time = False
            Q.append(lowest)
            
    return S
    
def get_distance_square(p1, p2):
    p3 = p1 - p2
    return p3.x ** 2 + p3.y ** 2
    
def closest_pair_brute_force(points):
    return closest_pair_brute_force_with_range(points, 0, len(points) - 1)
    
def closest_pair_brute_force_with_range(points, left, right):
    closest_pair_list = []
    closest_distance = sys.maxsize
    
    for i in range(len(points) - 1):
        for j in range(i + 1, len(points)):
            distance = get_distance_square(points[i], points[j])         
            if distance < closest_distance:
                closest_pair_list.clear()
                closest_distance = distance
                closest_pair_list.append(segment(points[i], points[j]))
            elif distance == closest_distance:
                closest_pair_list.append(segment(points[i], points[j]))   
                
    return closest_pair_list, closest_distance    
    
def closest_pair_divide_and_conquer(points):
    points.sort()
    #print(points)
    return closest_pair_divide_and_conquer_with_sorted_points_and_range(points, 0, len(points) - 1)

def closest_pair_divide_and_conquer_with_sorted_points_and_range(points, left, right):
    closest_distance_square = sys.maxsize    
    if right - left == 0:
        return closest_distance_square
    elif right - left == 1:
        closest_distance_square = min(closest_distance_square, get_distance_square(points[left], points[right]))
        return closest_distance_square
    elif right - left == 2:
        closest_distance_square = min(closest_distance_square, get_distance_square(points[left], points[left + 1]))
        closest_distance_square = min(closest_distance_square, get_distance_square(points[left], points[left + 2]))
        closest_distance_square = min(closest_distance_square, get_distance_square(points[left + 1], points[left + 2]))
        return closest_distance_square        
        
    mid = (left + right) // 2
    closest_distance_square_1 = closest_pair_divide_and_conquer_with_sorted_points_and_range(points, left, mid)
    closest_distance_square_2 = closest_pair_divide_and_conquer_with_sorted_points_and_range(points, mid + 1, right)
    closest_distance_square = min(closest_distance_square_1, closest_distance_square_2)
    
    for i in range(left,  mid + 1):
        right_most_index = min(right, i + 7)
        for j in range(i + 1, right_most_index + 1):
            closest_distance_square = min(closest_distance_square, get_distance_square(points[i], points[j]))
            
    return closest_distance_square
    
class computational_geomertry_test(unittest.TestCase):
    def _test_equal(self):    
        self.assertTrue((point(1, 2) == point(1, 2)) == True)
        self.assertTrue((point(2, 2) == point(1, 2)) == False)        
        
        self.assertTrue((segment(point(2, 2),  point(1, 2)) == segment(point(2, 2),  point(1, 2))) == True)
        self.assertTrue((segment(point(1, 2),  point(2, 2)) == segment(point(2, 2),  point(1, 2))) == True)
        self.assertTrue((segment(point(2, 2),  point(2, 2)) == segment(point(2, 2),  point(1, 2))) == False)
        
        seg1 = segment(point(2, 2),  point(1, 2))
        seg2 = segment(point(1, 2),  point(1, 2))
        seg3 = segment(point(1, 2), point(2, 3))        
        
        self.assertTrue((interset_segments(seg1, seg2) == interset_segments(seg1, seg2)) == True)
        self.assertTrue((interset_segments(seg1, seg2) == interset_segments(seg2, seg1)) == True)
        self.assertTrue((interset_segments(seg1, seg2) == interset_segments(seg2, seg3)) == False)
    
    def _test_segments_intersect(self):
        p1 = point(0, 5)
        p2 = point(5, 0)
        p3 = point(0, 0)
        p4 = point(5, 5)
        self.assertTrue(segments_intersect(p1, p2, p3, p4) == True)

        p1 = point(0, 0)
        p2 = point(5, 0)
        p3 = point(2, 0)
        p4 = point(2, 5)
        self.assertTrue(segments_intersect(p1, p2, p3, p4) == True)

        p1 = point(0, 0)
        p2 = point(5, 0)
        p3 = point(2, 1)
        p4 = point(2, 5)
        self.assertTrue(segments_intersect(p1, p2, p3, p4) == False)

        p1 = point(0, 0)
        p2 = point(5, 0)
        p3 = point(6, 0)
        p4 = point(6, 5)
        self.assertTrue(segments_intersect(p1, p2, p3, p4) == False)
    
    #  fail to pass
    def _test_any_segments_interset(self):
        for _ in range(100):
            seed = random.randint(0, sys.maxsize)
            seed = 1945193185
            print(seed)
            random.seed(seed)             
            max = 4
            count = 3
            S = []
            for _ in range(count):
                p1 = point(random.randint(0, max), random.randint(0, max))
                p2 = point(random.randint(0, max), random.randint(0, max))
                while p2.x == p1.x:
                    p2 = point(random.randint(0, max), random.randint(0, max))
                S.append(segment(p1, p2))
                
            intersets = brute_force_any_interset(S)
            interset = any_segments_intersect(S)
            
            if interset == False:
                self.assertTrue(len(intersets) == 0)
            else:
                self.assertTrue(len(intersets) != 0)

    def test_graham_scan_against_jarvis_march(self):
        for _ in range(100):
            point_count = 10
            random.seed(False)        
            points = []
            max_range = 20
            for x in range(point_count):
                p = point(random.randint(0, max_range), random.randint(0, max_range))
                while p in points:
                    p = point(random.randint(0, max_range), random.randint(0, max_range))
                points.append(p)
                
            hull1 = graham_scan(points)  
            hull2 = jarvis_march(points)
            hull1.sort()
            hull2.sort()         
            #print(hull1)
            #print(hull2)
            
            self.assertTrue(hull1 == hull2)
            
    def test_closest_pair(self):
        for i in range(10):
            point_count = 50
            random.seed(False)          
            points = []
            max_int = 1000
            for j in range(point_count):
                p = point(random.randint(0, max_int), random.randint(0, max_int))
                while p in points:
                    p = point(random.randint(0, max_int), random.randint(0, max_int))
                points.append(p)
            
            closest_pair_list, closest_distance_square = closest_pair_brute_force(points)
            closest_distance_square2 = closest_pair_divide_and_conquer(points)
            #print(closest_pair_list)
            #print(closest_distance_square)
            self.assertTrue(closest_distance_square == closest_distance_square2)
            
if __name__ == '__main__':
    unittest.main()
