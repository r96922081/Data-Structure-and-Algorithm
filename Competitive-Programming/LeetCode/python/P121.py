from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        profit = 0
        min = 100000
        for n in prices:
            if n < min:
                min = n
            elif n - min > profit:
                profit = n - min
        return profit

            

s = Solution()

prices = [7,1,5,3,6,4]
a = s.maxProfit(prices)

prices = [5,4,3,2]
a = s.maxProfit(prices)
        