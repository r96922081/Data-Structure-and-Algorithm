package main


import (
	"fmt"
	"math"
	"strconv"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func findNthDigit(n int) int {
	startCount := 0
	endCount := 0
	digit := 0
	left := 0
	right := 0

	for ; endCount < n; digit++ {
		startCount = endCount + 1
		left = int(math.Pow10(digit))
		right = int(math.Pow10(digit+1) - 1)
		endCount += ((right - left + 1) * (digit + 1))
	}

	left2 := left
	right2 := right
	mid := left2 + (right2-left2)/2
	midLeft := startCount + (mid-left2)*digit
	midRight := midLeft + digit - 1

	for n < midLeft || midRight < n {
		if n < midLeft {
			right2 = mid - 1
		} else {
			left2 = mid + 1
		}
		mid = left2 + (right2-left2)/2
		midLeft = startCount + (mid-left)*digit
		midRight = midLeft + digit - 1
	}

	nString := strconv.Itoa(mid)

	ans := nString[n-midLeft] - '0'
	return int(ans)
}

func main() {
	check(findNthDigit(1) == 1)
	check(findNthDigit(2) == 2)
	check(findNthDigit(11) == 0)
	check(findNthDigit(6) == 6)
	check(findNthDigit(190) == 1)
	check(findNthDigit(191) == 0)
	check(findNthDigit(192) == 0)
	check(findNthDigit(193) == 1)
	check(findNthDigit(194) == 0)
	check(findNthDigit(195) == 1)
}
