from typing import List

class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        last_num1 = m - 1
        last_num2 = n - 1
        sorted_list_head = m + n - 1
        while sorted_list_head >= 0:
            if last_num1 >= 0 and last_num2 >= 0:
                if nums1[last_num1] <= nums2[last_num2]:
                     nums1[sorted_list_head] = nums2[last_num2]
                     last_num2 -= 1
                else:
                     nums1[sorted_list_head] = nums1[last_num1]
                     last_num1 -= 1
            elif last_num2 >= 0:
                nums1[sorted_list_head] = nums2[last_num2]
                last_num2 -= 1
            else:
                break                
            sorted_list_head -= 1

s = Solution()

nums1 = [1,2,3,0,0,0]
nums2 = [2,5,6]
s.merge(nums1, len(nums1) - len(nums2), nums2, len(nums2))
pass
        