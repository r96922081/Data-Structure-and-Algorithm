package main


import (
	"fmt"
)

func maxProfit(prices []int) int {
	if len(prices) <= 1 {
		return 0
	}

	min := prices[0]
	maxProfit := 0

	for i := 1; i < len(prices); i++ {
		thisPrice := prices[i]
		if thisPrice < min {
			min = thisPrice
		}

		thisProfit := thisPrice - min
		if thisProfit > maxProfit {
			maxProfit = thisProfit
		}
	}

	return maxProfit
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	check(maxProfit([]int{1, 2}) == 1)
	check(maxProfit([]int{3, 3, 5, 0, 0, 3, 1, 4}) == 4)
	check(maxProfit([]int{7, 1, 5, 3, 6, 4}) == 5)
}
