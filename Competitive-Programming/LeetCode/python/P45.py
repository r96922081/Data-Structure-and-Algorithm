from typing import List


class Solution:
    def jump(self, nums: List[int]) -> int:
        min = 0
        max = 0
        step = 0

        while max < len(nums) - 1:
            min2 = min
            max2 = max
            min = max + 1
            for i in range(min2, max2 + 1):
                if i + nums[i] > max:
                    max = i + nums[i]
            step += 1
        return step
    

s = Solution()

print(s.jump([1,2,1,1,1]))

print(s.jump([2,3,1,1,4]))

print(s.jump([2,3,0,1,4]))

print(s.jump([0]))
