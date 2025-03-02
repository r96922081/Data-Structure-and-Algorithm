package main


import (
	"fmt"
	"math"
)

func countPrimes(n int) int {
	if n < 2 {
		return 0
	}

	allNumber := make([]int, n)
	for i := 0; i < n; i++ {
		allNumber[i] = i
	}

	allNumber[0] = -1
	allNumber[1] = -1
	maxFactor := int(math.Floor(math.Sqrt(float64(n))))

	for i := 2; i <= maxFactor; i++ {
		if allNumber[i] != -1 {
			product := i * 2
			for j := 3; product < n; j++ {
				allNumber[product] = -1
				product = i * j
			}
		}
	}

	count := 0
	for i := 2; i < len(allNumber); i++ {
		if allNumber[i] != -1 {
			count++
		}
	}

	return count
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	check(countPrimes(1) == 0)
	check(countPrimes(2) == 0)
	check(countPrimes(10) == 4)
}
