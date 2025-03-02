package main


import (
	"fmt"
	"math"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func divide(dividend int, divisor int) int {
	if dividend == math.MinInt32 && divisor == -1 {
		return math.MaxInt32
	}
	d1 := int64(dividend)
	d2 := int64(divisor)

	negativeCount := 0
	if d1 < 0 {
		negativeCount++
		d1 = -d1
	}

	if d2 < 0 {
		negativeCount++
		d2 = -d2
	}

	if d2 == 1 {
		if negativeCount == 1 {
			return int(-d1)
		}
		return int(d1)
	}

	answer := 0
	remainder := d1
	for remainder >= d2 {
		tempD2 := d2
		prevD2 := d2
		q := 1
		prevQ := q
		for i := 0; tempD2 <= remainder; i++ {
			prevD2 = tempD2
			tempD2 += tempD2
			prevQ = q
			q += q
		}
		remainder -= prevD2
		answer += prevQ
	}

	if negativeCount == 1 {
		return int(-answer)
	}
	return int(answer)
}

func main() {
	check(divide(100, 18) == 5)
	check(divide(-100, 18) == -5)
	check(divide(3, -18) == 0)
	check(divide(21, 3) == 7)
	check(divide(987, 1) == 987)
	check(divide(-1, 1) == -1)
}
