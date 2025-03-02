from typing import List

class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        last_removed = len(nums) - 1
        current = 0
        while current <= last_removed:
            if nums[current] == val:
                nums[current], nums[last_removed] = nums[last_removed], nums[current]
                last_removed -= 1
            else:
                current += 1

        return last_removed + 1


nums = [0,1,2,2,3,0,4,2]

val = 2
s = Solution()
ret = s.removeElement(nums, val)
pass
        