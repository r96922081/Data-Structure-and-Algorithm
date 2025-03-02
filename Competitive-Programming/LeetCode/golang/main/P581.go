package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

// There maybe multiple segment that contains decreasing subsequence
// 1. Find l: the first decreasing pair's left. after l is found,
//    start tracking allSegMin, allSegMax
// 2. scan to right until find nums[i] > allSegMax, r = i - 1
// 3. If there is another decreasing subsequence, repeat 1, 2
// 4. after r is fixed, find l until nums[l] <= allSegMin

func findUnsortedSubarray(nums []int) int {
	l := -1
	r := -1
	maxInput := 10000
	minInput := 1
	allSegMin := maxInput + 1
	allSegMax := minInput - 1
	inSeg := false

	for i := 1; i < len(nums); i++ {
		if nums[i-1] > nums[i] {
			if l == -1 {
				l = i - 1
				allSegMin = nums[i]
				allSegMax = nums[i-1]
			}
			inSeg = true
		}

		if l != -1 {
			if nums[i] > allSegMax {
				allSegMax = nums[i]
			}
			if nums[i] < allSegMin {
				allSegMin = nums[i]
			}
		}

		if inSeg && nums[i] >= allSegMax {
			r = i - 1
			inSeg = false
		}
	}

	if l == -1 {
		return 0
	}

	if inSeg {
		r = len(nums) - 1
	}

	for ; (l > 0) && nums[l-1] > allSegMin; l-- {
	}
	return r - l + 1
}

func main() {
	check(findUnsortedSubarray([]int{}) == 0)
	check(findUnsortedSubarray([]int{3}) == 0)
	check(findUnsortedSubarray([]int{2, 1}) == 2)
	check(findUnsortedSubarray([]int{1, 2}) == 0)
	check(findUnsortedSubarray([]int{3, 2, 1}) == 3)
	check(findUnsortedSubarray([]int{1, 2, 3}) == 0)
	check(findUnsortedSubarray([]int{2, 6, 4}) == 2)
	check(findUnsortedSubarray([]int{2, 6, 4, 8, 10, 9, 15}) == 5)
	check(findUnsortedSubarray([]int{2, 6, 4, 8, 10, 9}) == 5)
	check(findUnsortedSubarray([]int{6, 4, 8, 10, 9}) == 5)
	check(findUnsortedSubarray([]int{6, 4, 8, 10, 9, 29}) == 5)
	check(findUnsortedSubarray([]int{4, 5, 8, 6, 3, 9}) == 5)
	check(findUnsortedSubarray([]int{5, 8, 6, 3, 9}) == 4)
}
