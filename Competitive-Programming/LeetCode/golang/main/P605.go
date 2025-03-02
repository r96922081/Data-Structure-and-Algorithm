package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func canPlaceFlowers(flowerbed []int, n int) bool {
	if n == 0 {
		return true
	}

	count := 0

	for i := 0; i < len(flowerbed); i++ {
		left := i - 1
		right := i + 1
		if flowerbed[i] == 1 {
			continue
		}
		if left >= 0 && flowerbed[left] == 1 {
			continue
		}
		if right < len(flowerbed) && flowerbed[right] == 1 {
			continue
		}
		flowerbed[i] = 1
		count++

		if count == n {
			return true
		}
	}

	return false
}

func main() {
	canPlaceFlowers([]int{1, 0, 0, 0, 0, 1}, 2)
}
