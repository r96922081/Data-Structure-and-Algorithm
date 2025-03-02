package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func findPairs(nums []int, k int) int {
	if len(nums) == 0 {
		return 0
	}

	quickSort(nums)
	if k == 0 {
		pairs := 0
		firstSame := true
		for i := 1; i < len(nums); i++ {
			if nums[i] == nums[i-1] {
				if firstSame {
					firstSame = false
					pairs++
				}
			} else {
				firstSame = true
			}
		}
		return pairs
	}

	nums2 := make([]int, 0)
	nums2 = append(nums2, nums[0])
	for i := 1; i < len(nums); i++ {
		if nums[i] != nums[i-1] {
			nums2 = append(nums2, nums[i])
		}
	}

	pairs := 0
	for i := range nums2 {
		for j := i + 1; j < len(nums2); j++ {
			if nums2[j]-nums2[i] == k {
				pairs++
			} else if nums2[j]-nums2[i] > k {
				break
			}
		}
	}

	return pairs
}

func quickSort2(input []int, l int, r int) {
	if r < l {
		return
	}
	l2 := l + 1
	r2 := r
	pivot := input[l]
	for l2 <= r2 {
		for ; l2 <= r && input[l2] <= pivot; l2++ {
		}
		for ; input[r2] > pivot; r2-- {
		}
		if l2 < r2 {
			input[l2], input[r2] = input[r2], input[l2]
		}
	}
	input[l], input[r2] = input[r2], input[l]
	quickSort2(input, l, r2-1)
	quickSort2(input, r2+1, r)
}

func quickSort(input []int) {
	quickSort2(input, 0, len(input)-1)
}

func main() {
	/*
		rand.Seed(0)
		length := 100
		input := make([]int, length)
		for i := 0; i < length; i++ {
			input[i] = rand.Intn(100)
		}

		quickSort(input)

		for i := 0; i < length-1; i++ {
			check(input[i] <= input[i+1])
		}
	*/
	check(findPairs([]int{1, 1, 1, 1}, 0) == 1)
	check(findPairs([]int{1, 1, 2, 3, 3, 3, 4, 4, 4, 5}, 0) == 3)
}
