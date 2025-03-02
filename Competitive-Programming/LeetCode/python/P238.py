from typing import List


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        product_left_to_right = []
        product_right_to_left = []
        result = []

        product = 1
        for i in range(len(nums)):
            product *= nums[i]
            product_left_to_right.append(product)

        product = 1
        for i in range(len(nums) -1, -1, -1):
            product *= nums[i]
            product_right_to_left.append(product)  

        for i in range(len(nums)):
            product = 1
            left = i - 1
            if left >= 0:
                product *= product_left_to_right[left]
            right = len(nums) - 1 - i - 1
            if right >= 0:
                product *= product_right_to_left[right]
            result.append(product)

        return result
        
        

s = Solution()
print(s.productExceptSelf([1,2,3,4]))
print(s.productExceptSelf([-1,1,0,-3,3]))
