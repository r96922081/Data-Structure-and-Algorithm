package main


import (
	"fmt"
)

func rotate(nums []int, k int) {
	if len(nums) == 0 {
		return
	}

	step := k % len(nums)

	for i := 0; i < step; i++ {
		temp1 := nums[len(nums)-1]
		for j := 0; j < len(nums); j++ {
			temp2 := nums[j]
			nums[j] = temp1
			temp1 = temp2
		}
	}
}
func Check(b bool) {
	if !b {
		fmt.Println("Error!")
	}
}

func main() {
	rotate([]int{1, 2, 3}, 5)
}
