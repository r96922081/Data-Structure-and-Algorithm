package main


import (
	"fmt"
	"math"
)

func checkPossibility(nums []int) bool {
	if len(nums) <= 1 {
		return true
	}

	nums2 := make([]int, 0)
	nums3 := make([]int, 0)

	nums = append(nums, math.MaxInt32)

	removed := false
	for i := 0; i < len(nums)-1; i++ {
		if nums[i] > nums[i+1] {
			if removed {
				return false
			}
			removed = true
			nums2 = append(nums2, nums[i])
			nums3 = append(nums3, nums[i+1])
			i++
			continue
		} else {
			nums2 = append(nums2, nums[i])
			nums3 = append(nums3, nums[i])
		}
	}

	ok2 := true
	for i := 0; i < len(nums2)-1; i++ {
		if nums2[i] > nums2[i+1] {
			ok2 = false
			break
		}
	}

	ok3 := true
	for i := 0; i < len(nums3)-1; i++ {
		if nums3[i] > nums3[i+1] {
			ok3 = false
			break
		}
	}

	return ok2 || ok3
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	check(checkPossibility([]int{4, 2, 1}) == false)
	check(checkPossibility([]int{-1, 4, 2, 3}) == true)
	check(checkPossibility([]int{2, 3, 3, 2, 4}) == true)
	check(checkPossibility([]int{1, 5, 4, 6, 7, 10, 8, 9}) == false)
}
