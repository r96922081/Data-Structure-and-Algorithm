package main


import (
	"fmt"
	"math"
	"strings"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func validDigit(d byte) bool {
	if '0' <= d && d <= '9' {
		return true
	}
	return false
}

func myAtoi(str string) int {
	str = strings.Trim(str, " ")
	if str == "" {
		return 0
	}

	positive := true

	if str[0] != '+' && str[0] != '-' && !validDigit(str[0]) {
		return 0
	}

	strIndex := 0
	if str[0] == '+' {
		strIndex++
	} else if str[0] == '-' {
		strIndex++
		positive = false
	}

	str = str[strIndex:]
	str = strings.TrimLeft(str, "0")
	str2 := ""
	for i := 0; i < len(str); i++ {
		if !validDigit(str[i]) {
			break
		} else {
			str2 += string(str[i])
		}
	}

	if len(str2) == 0 {
		return 0
	}

	if len(str2) > 10 {
		if positive {
			return math.MaxInt32
		}
		return math.MinInt32

	}

	ret := int64(0)
	j := 0

	for i := len(str2) - 1; i >= 0; i-- {
		v := int(math.Pow10(j)) * int((str2[i] - '0'))
		if positive {
			ret += int64(v)
		} else {
			ret -= int64(v)
		}
		j++
	}

	if ret > math.MaxInt32 {
		return math.MaxInt32
	}

	if ret < math.MinInt32 {
		return math.MinInt32
	}

	return int(ret)
}

func main() {
	myAtoi("  0000000000012345678")
}
