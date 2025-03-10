package main

import "fmt"

func main() {
    fmt.Println("P278")
}

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        if (isBadVersion(1)) {
            return 1;
        }
        
        int left = 1;
        int right = n;
        
        while (left + 1 != right)
        {
            int mid = left + (right-left)/2;
            if (isBadVersion(mid))
                right = mid;
            else
                left = mid;
        }
        
        return right;
    }
};
