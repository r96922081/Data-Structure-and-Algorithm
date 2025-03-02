package main

import "fmt"

func main() {
    fmt.Println("P914")
}

func getGcd(a, b uint) uint {
	if a%b == 0 {
		return b
	}

	return getGcd(b, a%b)
}

func hasGroupsSizeX(deck []int) bool {
	if len(deck) == 0 {
		return false
	}

	sort.Slice(deck, func(i, j int) bool {
		return deck[i] < deck[j]
	})

	prev := deck[0] - 1
	allCount := make([]int, 0)
	count := 0

	for _, v := range deck {
		if prev == v {
			count++
		} else {
			allCount = append(allCount, count)
			count = 1
			prev = v
		}
	}

	allCount = append(allCount, count)

	if len(allCount) == 1 {
		if allCount[0] > 1 {
			return true
		}
		return false
	}

	gcd := getGcd(uint(allCount[0]), uint(allCount[1]))
	for i := 2; i < len(allCount); i++ {
		gcd = getGcd(gcd, uint(allCount[i]))
	}

	if gcd >= 2 {
		return true
	}
	return false
}
