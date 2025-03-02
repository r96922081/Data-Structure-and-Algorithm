package main


import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func getDigitCount(n int) int {
	if n == 0 {
		return 1
	}
	return int(math.Floor(math.Log(float64(n))/math.Log(float64(10)))) + 1
}

func intToString(i int) string {
	base := 10
	return strconv.FormatInt(int64(i), base)
}

func removeKdigits(num string, k int) string {
	if num == "0" {
		return "0"
	}
	for i := 0; i < k; i++ {
		if len(num) <= 1 {
			return "0"
		}

		found := false
		for j := 0; j < len(num)-1 && !found; j++ {
			if num[j] > num[j+1] {
				found = true
				num = num[:j] + num[j+1:]
			}
		}

		if !found {
			num = num[:len(num)-1]
		}

		num = strings.TrimLeft(num, "0")
	}

	if num == "" {
		return "0"
	}

	return num
}

func stringToInt(s string) int {
	base := 10
	ret, err := strconv.ParseInt(s, base, 32)
	if err != nil {
		panic(err)
	}
	return int(ret)
}

func stringToInt2(s string) int {
	if s == "" {
		return 0
	}

	return stringToInt(s)
}

func exhaustedTest() {
	for num := 1; num <= 10002; num++ {
		digitCount := getDigitCount(num)
		answers := make([]int, digitCount+1)

		for k := 0; k <= digitCount; k++ {
			answers[k] = stringToInt2(removeKdigits(intToString(num), k))
		}

		for i := 0; i < int(math.Pow(2, float64(digitCount))); i++ {
			ones := make([]int, 0)
			for j := 1; j < 20; j++ {
				if i&(1<<uint(j)) != 0 {
					ones = append(ones, j-1)
				}
			}

			strI := intToString(num)
			for i, v := range ones {
				strI = strI[:v-i] + strI[v-i+1:]
				check(stringToInt2(strI) >= answers[len(ones)])
			}
		}
	}
}

func main() {
	check(removeKdigits("1432219", 3) == "1219")
	check(removeKdigits("10200", 1) == "200")
	check(removeKdigits("123", 1) == "12")
	check(removeKdigits("198", 1) == "18")
	check(removeKdigits("556", 1) == "55")
	check(removeKdigits("554", 1) == "54")
	check(removeKdigits("55779", 1) == "5577")
	check(removeKdigits("55776", 1) == "5576")
	check(removeKdigits("55777", 0) == "55777")
	check(removeKdigits("55777", 5) == "0")
	check(removeKdigits("55777", 6) == "0")
	check(removeKdigits("10", 1) == "0")
	exhaustedTest()
}
