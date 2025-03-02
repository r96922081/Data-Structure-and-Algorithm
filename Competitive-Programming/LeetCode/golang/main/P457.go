package main

import "fmt"

func main() {
    fmt.Println("P457")
}

func circularArrayLoop(nums []int) bool {
	startIndex := 0
	currentIndex := 0
	roundValue := 1001
	positive := true

	for true {
		for ; startIndex < len(nums) && nums[startIndex] > 1000; startIndex++ {
		}

		if startIndex == len(nums) {
			return false
		}
		roundValue++
		currentIndex = startIndex
		currentValue := nums[currentIndex]
		if currentValue > 0 {
			positive = true
		} else {
			positive = false
		}

		for true {
			currentValue = nums[currentIndex]
			if currentValue == roundValue {
				return true
			} else if nums[currentIndex] > 1000 {
				break
			}

			if currentValue > 0 {
				if !positive {
					break
				}
			} else {
				if positive {
					break
				}
			}
			nums[currentIndex] = roundValue

			step := int(math.Abs(float64(currentValue)))
			step %= len(nums)

			if step == 0 {
				break
			}

			if positive {
				currentIndex = (currentIndex + step) % len(nums)
			} else {
				if step <= currentIndex {
					currentIndex -= step
				} else {
					currentIndex = len(nums) - (step - currentIndex)
				}
			}
		}

	}

	return false
}
