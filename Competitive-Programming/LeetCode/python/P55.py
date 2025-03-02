from typing import List


class Solution:
    def canJump(self, nums: List[int]) -> bool:
        farest = 0
        current = 0
        while current <= farest:
            if current >= len(nums) - 1:
                return True
            if nums[current] + current > farest:
                farest = nums[current] + current
            current += 1
        return False
    

s = Solution()
print(s.canJump([2,3,1,1,4]))

print(s.canJump([3,2,1,0,4]))

print(s.canJump([0]))
