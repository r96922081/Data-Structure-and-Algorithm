package main


import (
	"fmt"
)

func merge(nums1 []int, m int, nums2 []int, n int) {
	nums3 := make([]int, m+n)
	nums3Len := 0
	i := 0
	j := 0

	for i < m || j < n {
		if i == m {
			nums3[nums3Len] = nums2[j]
			nums3Len++
			j++
			continue
		} else if j == n {
			nums3[nums3Len] = nums1[i]
			nums3Len++
			i++
			continue
		}

		if nums1[i] > nums2[j] {
			nums3[nums3Len] = nums2[j]
			nums3Len++
			j++
		} else {
			nums3[nums3Len] = nums1[i]
			nums3Len++
			i++
		}
	}

	for i := 0; i < nums3Len; i++ {
		nums1[i] = nums3[i]
	}
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	merge([]int{1, 2, 3, 0, 0, 0}, 3, []int{2, 5, 6}, 3)
}
