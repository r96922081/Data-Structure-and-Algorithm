package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func checkSubarraySum(nums []int, k int) bool {
	maxLen := len(nums)

	for i := 0; i < maxLen-1; i++ {
		prevSum := nums[i]
		for j := i + 1; j < maxLen; j++ {
			newSum := prevSum + nums[j]
			if k != 0 {
				if newSum%k == 0 {
					return true
				}
			} else {
				if newSum == 0 {
					return true
				}
			}
			prevSum = newSum
		}
	}

	return false
}

func main() {
	check(checkSubarraySum([]int{23, 2, 4, 6, 7}, 6) == true)
	check(checkSubarraySum([]int{23, 2, 4, 6, 7}, 9) == false)
	check(checkSubarraySum([]int{23, 2, 6, 4, 7}, 21) == true)
}
