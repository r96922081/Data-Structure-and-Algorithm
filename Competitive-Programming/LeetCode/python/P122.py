from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        profit = 0
        for i in range(1, len(prices), 1):
            if prices[i] - prices[i-1] > 0:
                profit += prices[i] - prices[i-1]
        return profit

            

s = Solution()

prices = [7,1,5,3,6,4]
a = s.maxProfit(prices)

prices = [5,4,3,2]
a = s.maxProfit(prices)

pass
        