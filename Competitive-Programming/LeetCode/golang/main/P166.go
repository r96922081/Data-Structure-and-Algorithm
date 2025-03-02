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

func fractionToDecimal(numeratorOriginal int, denominatorOriginal int) string {
	numerator := int64(numeratorOriginal)
	denominator := int64(denominatorOriginal)
	if numerator == 0 {
		return "0"
	}
	remainder := int64(0)
	intPart := int64(0)
	recurringLeft := -1
	positive := true

	if numerator > 0 && denominator < 0 {
		positive = false
		denominator = -denominator
	} else if numerator < 0 && denominator > 0 {
		numerator = -numerator
		positive = false
	} else if numerator < 0 && denominator < 0 {
		numerator = -numerator
		denominator = -denominator
	}

	digitCount := int(math.Floor(math.Log10(float64(numerator))) + 1)
	for i := digitCount; i >= 1; i-- {
		digit := numerator % int64(math.Pow10(i)) / int64(math.Pow10(i-1))
		remainder = remainder*10 + digit
		intPart += remainder / denominator * int64(math.Pow10(i-1))
		if remainder >= denominator {
			remainder %= denominator
		}
	}

	fractionRemainder := make([]int64, 0)
	fraction := make([]int64, 0)
	for remainder != 0 {
		for i := range fractionRemainder {
			if fractionRemainder[i] == remainder {
				recurringLeft = i
			}
		}

		if recurringLeft != -1 {
			break
		}
		fractionRemainder = append(fractionRemainder, remainder)
		remainder = remainder * 10
		fraction = append(fraction, int64(remainder/denominator))
		remainder %= denominator
	}

	intPartString := strconv.FormatInt(intPart, 10)
	if len(fraction) == 0 {
		if positive == false {
			return "-" + intPartString
		}
		return intPartString
	}

	fractionString := ""
	for i := range fraction {
		if recurringLeft != -1 && recurringLeft == i {
			fractionString += "("
		}
		fractionString += strconv.FormatInt(fraction[i], 10)
	}

	if recurringLeft != -1 {
		fractionString += ")"
	}

	ret := intPartString + "." + fractionString
	if positive == false {
		ret = "-" + ret
	}
	return ret
}

func main() {
	check(fractionToDecimal(1, 3) == "0.(3)")
	check(fractionToDecimal(0, 2) == "0")
	check(fractionToDecimal(1, 2) == "0.5")
	check(fractionToDecimal(2, 1) == "2")
	check(fractionToDecimal(2, 3) == "0.(6)")
	check(fractionToDecimal(1, 7) == "0.(142857)")
	check(fractionToDecimal(100, 11) == "9.(09)")
	check(fractionToDecimal(1, -2) == "-0.5")
	check(fractionToDecimal(-2147483648, 1) == "-2147483648")
}
