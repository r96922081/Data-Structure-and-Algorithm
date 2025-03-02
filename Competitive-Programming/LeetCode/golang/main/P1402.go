package main

import "fmt"

func main() {
    fmt.Println("P1402")
}

func maxSatisfaction(input []int) int {
	sort.Ints(input)
	selection := make([]int, 0)
	positiveSum := 0
	negativeSum := 0

	for i := len(input) - 1; i >= 0; i-- {
		value := input[i]
		if value >= 0 {
			selection = append(selection, value)
			positiveSum += value
		} else {
			if value+positiveSum+negativeSum >= 0 {
				selection = append(selection, value)
				negativeSum += value
			}
		}
	}

	answer := 0
	for i := 0; i < len(selection); i++ {
		answer += selection[i] * (len(selection) - i)
	}

	return answer
}