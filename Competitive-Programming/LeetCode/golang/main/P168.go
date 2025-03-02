package main


import (
	"fmt"
	"math"
)

func convertToTitle(n int) string {
	nDigitMaxCount := make([]int, 0)
	nDigitMaxCount = append(nDigitMaxCount, 0)

	maxCount := 0
	digitCount := 0
	for maxCount < n {
		maxCount += int(math.Pow(float64(26), float64(digitCount+1)))
		nDigitMaxCount = append(nDigitMaxCount, maxCount)
		digitCount++
	}

	ret := ""

	for i := digitCount; i > 0; i-- {
		n2 := n
		n2 -= nDigitMaxCount[i-1]
		val := int(math.Ceil(float64(n2) / math.Pow(float64(26), float64(i-1))))
		ret += string('A' + val - 1)
		n -= val * int(math.Pow(float64(26), float64(i-1)))
	}

	return ret
}

func Check(b bool) {
	if !b {
		fmt.Println("Error!")
	}
}

func main() {
	Check(convertToTitle(1) == "A")
	Check(convertToTitle(26) == "Z")
	Check(convertToTitle(26*1+1) == "AA")
	Check(convertToTitle(26*26+26) == "ZZ")
	Check(convertToTitle(701) == "ZY")
	Check(convertToTitle(26*26*26+26*26+26) == "ZZZ")
	Check(convertToTitle(26*26*26+26*2+3) == "ZBC")
}
