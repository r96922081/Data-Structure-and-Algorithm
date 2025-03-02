from typing import List

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        prev_num = -101
        occurrence = -1
        replace_index = 0

        for v in nums:
            if v != prev_num:
                prev_num = v
                occurrence = 1
            else:
                occurrence += 1
            if occurrence <= 2:
                nums[replace_index] = v
                replace_index += 1

        return replace_index


nums = [1,1,2,2,2,3]
s = Solution()
ret = s.removeDuplicates(nums)
pass
        