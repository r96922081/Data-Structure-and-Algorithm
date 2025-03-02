package main


import (
	"fmt"
)

func maxProfit(prices []int) int {
	if len(prices) <= 1 {
		return 0
	}

	maxProfit := 0
	boughtPrice := -1

	if prices[0] < prices[1] {
		boughtPrice = prices[0]
	}

	for i := 1; i < len(prices)-1; i++ {
		thisPrice := prices[i]
		nextPrice := prices[i+1]

		if nextPrice > thisPrice && boughtPrice == -1 {
			boughtPrice = thisPrice
		}

		if nextPrice < thisPrice && boughtPrice != -1 {
			maxProfit += thisPrice - boughtPrice
			boughtPrice = -1
		}
	}

	if boughtPrice != -1 {
		maxProfit += prices[len(prices)-1] - boughtPrice
		boughtPrice = -1
	}

	return maxProfit
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	check(maxProfit([]int{7, 1, 5, 3, 6, 4}) == 7)
	check(maxProfit([]int{1, 2, 3, 4, 5}) == 4)
}
