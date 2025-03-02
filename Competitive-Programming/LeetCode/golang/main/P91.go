package main


import (
	"fmt"
	"strconv"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func numDecodings2(s string, count int) int {
	if len(s) == 0 {
		return 1
	}

	if s[0] == '0' {
		return 0
	}

	if len(s) == 1 {
		return 1
	}

	temp := s[0:2]
	n, _ := strconv.ParseInt(temp, 10, 32)

	if n == 10 || n == 20 {
		return numDecodings2(s[2:], count)
	} else if n > 26 {
		return numDecodings2(s[1:], count)
	} else {
		return numDecodings2(s[1:], count) + numDecodings2(s[2:], count)
	}
}

func numDecodings(s string) int {
	if s[0] == '0' {
		return 0
	}
	return numDecodings2(s, 1)
}

func main() {
	check(numDecodings("12") == 2)
	check(numDecodings("226") == 3)
	check(numDecodings("012") == 0)
	check(numDecodings("128") == 2)
	check(numDecodings("101") == 1)
	check(numDecodings("1001") == 0)
	check(numDecodings("201") == 1)
	check(numDecodings("301") == 0)
	check(numDecodings("0") == 0)
	check(numDecodings("00") == 0)
	check(numDecodings("110") == 1)
}
