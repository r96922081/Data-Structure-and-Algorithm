from typing import List

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        k = 0
        prev_num = -101
        for v in nums:
            if v != prev_num:
                prev_num = v
                nums[k] = v
                k += 1
        return k


nums = [1,1,2]
s = Solution()
ret = s.removeDuplicates(nums)
pass
        