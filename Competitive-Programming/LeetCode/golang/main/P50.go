package main


import (
	"fmt"
)

func maxSubArray(nums []int) int {
	prevMax := 0
	max := int(int32(-1) - 0x7FFFFFFF)

	for i := 0; i < len(nums); i++ {
		currentSum := nums[i] + prevMax
		if currentSum > max {
			max = currentSum
		}

		if currentSum > 0 {
			prevMax = currentSum
		} else {
			prevMax = 0
		}
	}

	return max
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	check(maxSubArray([]int{1, 2}) == 3)
	check(maxSubArray([]int{1, 2, 3}) == 6)
	check(maxSubArray([]int{1, 2, -1}) == 3)
	check(maxSubArray([]int{-1, 2}) == 2)
	check(maxSubArray([]int{-2, 1, -3, 4, -1, 2, 1, -5, 4}) == 6)
}
