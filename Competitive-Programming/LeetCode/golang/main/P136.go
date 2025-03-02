package main


import (
	"fmt"
)

func singleNumber(nums []int) int {
	ret := 0
	for i := range nums {
		ret ^= nums[i]
	}

	return ret
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
}
