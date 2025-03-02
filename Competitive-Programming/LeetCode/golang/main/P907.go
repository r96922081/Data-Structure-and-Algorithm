package main


import (
	"fmt"
	"math"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func sumSubarrayMins(nums []int) int {
	maxLen := len(nums)
	sum := int64(0)

	for i := 0; i < maxLen; i++ {
		sum += int64(nums[i])
		min := int64(nums[i])
		for j := i + 1; j < maxLen; j++ {
			if int64(nums[j]) < min {
				min = int64(nums[j])
			}
			sum += min

			if sum > math.MaxInt64-30000 {
				sum %= int64(math.Pow10(9) + 7)
			}
		}
	}

	return int(sum % int64(math.Pow10(9)+7))
}

func main() {
	sumSubarrayMins([]int{3, 1, 2, 4})

}
