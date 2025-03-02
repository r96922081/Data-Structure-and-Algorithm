from typing import List


class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        import math
        n = len(nums)
        k %= n
        if k == 0:
            return
        
        count = 0
        for start_index in range(k):
            next_index = (start_index + k) % n
            prev_value = nums[start_index]
            while next_index != start_index:
                nums[next_index], prev_value = prev_value, nums[next_index]
                next_index = (next_index + k) % n
                count += 1
            nums[next_index] = prev_value
            count += 1
            if count == n:
                break
            

s = Solution()

nums = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54]
s.rotate(nums, 45)

nums = [1,2,3,4,5,6,7]
s.rotate(nums, 3)

nums = [0,1,2,3,4,5]
s.rotate(nums, 4)

nums = [0,1,2,3,4,5]
s.rotate(nums, 3)

nums = [0,1,2,3,4,5]
s.rotate(nums, 2)


nums = [0,1,2,3,4,5,6]
s.rotate(nums, 3)

nums = [0,1,2,3,4,5]
s.rotate(nums, 3)



pass
        