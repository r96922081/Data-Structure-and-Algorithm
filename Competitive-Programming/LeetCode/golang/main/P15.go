package main


import (
	"fmt"
	"sort"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

type valueCount struct {
	value int
	count int
}

func threeSum(nums []int) [][]int {
	answer := make([][]int, 0)

	zeroCount := 0
	for _, v := range nums {
		if v == 0 {
			zeroCount++
			if zeroCount == 3 {
				answer = append(answer, []int{0, 0, 0})
				break
			}
		}
	}

	numMap := make(map[int]int)
	for i := 0; i < len(nums); i++ {
		v, ok := numMap[nums[i]]
		if ok {
			numMap[nums[i]] = v + 1
		} else {
			numMap[nums[i]] = 1
		}
	}

	nums2 := make([]valueCount, 0)
	for key, value := range numMap {
		nums2 = append(nums2, valueCount{key, value})
	}

	sort.SliceStable(nums2, func(i, j int) bool {
		return nums2[i].value < nums2[j].value
	})

	for _, v := range nums2 {
		if v.count >= 2 && v.value != 0 {
			v3 := 0 - (v.value * 2)
			_, ok := numMap[v3]
			if ok {
				answer = append(answer, []int{v.value, v.value, v3})
			}
		}
	}

	for i := 0; i < len(nums2); i++ {
		for j := i + 1; j < len(nums2); j++ {
			v1 := nums2[i].value
			v2 := nums2[j].value
			v3 := 0 - v1 - v2
			if v3 <= v2 {
				continue
			}
			_, ok := numMap[v3]
			if ok {
				answer = append(answer, []int{v1, v2, v3})
			}
		}
	}

	return answer
}

func main() {
	threeSum([]int{-1, 0, 1, 2, -1, -4})
	threeSum([]int{0, 0})
}
