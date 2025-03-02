from typing import List

class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        diff = []
        for i in range(len(gas)):
            diff.append(gas[i] - cost[i])

        for i in range(len(gas)):
            isPass = True
            current_gas = 0
            current_station = i
            for j in range(len(gas)):
                current_gas += diff[current_station]
                if current_gas < 0:
                    isPass = False
                    break              
                current_station = (current_station + 1) % len(gas)  
            if isPass:
                return i
            
        return -1


s = Solution()
print(s.canCompleteCircuit([1,2,3,4,5], [3,4,5,1,2]))
print(s.canCompleteCircuit([2,3,4], [3,4,3]))
print(s.canCompleteCircuit([5,1,2,3,4], [4,4,1,5,1]))