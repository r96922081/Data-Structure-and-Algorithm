import random

class RandomizedSet:
    def __init__(self):
        self.valToPosDict = {}
        self.posToValDict = {}
        self.vector = []

    def insert(self, val: int) -> bool:
        if val in self.valToPosDict:
            return False
        self.valToPosDict[val] = len(self.vector)
        self.posToValDict[len(self.vector)] = val
        self.vector.append(val)
        return True
        

    def remove(self, val: int) -> bool:
        if val not in self.valToPosDict:
            return False

        pos = self.valToPosDict[val]
        del self.valToPosDict[val]   
        del self.posToValDict[pos]

        lastPos = len(self.vector) - 1
        if pos != lastPos:
            lastVal = self.vector[lastPos]
            del self.valToPosDict[lastVal]
            del self.posToValDict[lastPos]
            self.vector[pos] = lastVal
            self.valToPosDict[lastVal] = pos
            self.posToValDict[pos] = lastVal

        self.vector.pop()
        return True  

    def getRandom(self) -> int:
        return self.vector[random.randrange(0, len(self.vector))]
        


# Your RandomizedSet object will be instantiated and called as such:
obj = RandomizedSet()
p = obj.remove(0)
p = obj.remove(0)
p = obj.insert(0)
p = obj.getRandom()
p = obj.remove(0)
p = obj.insert(0)
pass