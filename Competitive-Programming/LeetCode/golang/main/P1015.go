package main

import "fmt"

func main() {
    fmt.Println("P1015")
}


func smallestRepunitDivByK(k int) int {
	previousRemainder := make(map[int]int)

	digitCount := 0
	remainder := 0

	for {
		digitCount++
		n := remainder*10 + 1
		remainder = n % k
		if remainder == 0 {
			return digitCount
		}

		_, existed := previousRemainder[remainder]
		if existed {
			return -1
		}

		previousRemainder[remainder] = 1
	}

	return -1
}

func TestProblem1015() {
	check(smallestRepunitDivByK(1) == 1)
	check(smallestRepunitDivByK(2) == -1)
	check(smallestRepunitDivByK(3) == 3)
}
