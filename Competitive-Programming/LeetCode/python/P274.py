from typing import List


class Solution:
    # in this case, counting sort is slower than built-in sort()
    def sort(self, c: List[int]) -> List[int]:
        a = [0] * 5001
        ret = []
        for i in c:
            a[i] += 1
        for i in range(len(a)):
            for j in range(a[i]):
                ret.append(i)
        return ret



    def hIndex(self, citations: List[int]) -> int:
        c = self.sort(citations)
        for i in range(len(c) - 1, -1, -1):
            if c[len(c) - 1 - i] >= i + 1:
                return i + 1
        return 0
        

s = Solution()
print(s.hIndex([0]))
print(s.hIndex([1]))
print(s.hIndex([1,3,1]))
print(s.hIndex([3,0,6,1,5]))

