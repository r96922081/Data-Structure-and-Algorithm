package main


import (
	"fmt"
)

func thirdMax(nums []int) int {
	allMax := 0
	max := 0
	newLen := len(nums)

	indexOfMax := 1
	for ; indexOfMax <= 3 && newLen != 0; indexOfMax++ {
		max = nums[0]
		for i := 1; i < newLen; i++ {
			if nums[i] > max {
				max = nums[i]
			}
		}

		if indexOfMax == 1 {
			allMax = max
		}

		left := 0
		right := newLen - 1
		for left <= right {
			for ; nums[left] != max; left++ {

			}
			for ; right >= 0 && nums[right] == max; right-- {

			}
			if left < right {
				nums[left], nums[right] = nums[right], nums[left]
			}
		}

		newLen = left
	}

	if indexOfMax == 4 {
		return max
	} else {
		return allMax
	}

}

func Check(b bool) {
	if !b {
		fmt.Println("Error!")
	}
}

func main() {
	Check(thirdMax([]int{2, 2, 3, 1}) == 1)
	Check(thirdMax([]int{1, 2, 2}) == 2)
	Check(thirdMax([]int{1, 1, 1}) == 1)
	Check(thirdMax([]int{1}) == 1)
	Check(thirdMax([]int{1, 2}) == 2)
	Check(thirdMax([]int{1, 1, 2}) == 2)
}
