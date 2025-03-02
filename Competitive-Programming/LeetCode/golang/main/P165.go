package main


import (
	"fmt"
	"strconv"
	"strings"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func compareVersion(version1 string, version2 string) int {
	tokens1 := strings.Split(version1, ".")
	tokens2 := strings.Split(version2, ".")

	maxLen := len(tokens1)
	if len(tokens2) > maxLen {
		maxLen = len(tokens2)
	}

	for i := 0; i < maxLen; i++ {
		v1 := 0
		v2 := 0
		if i < len(tokens1) {
			v1, _ = strconv.Atoi(tokens1[i])
		}

		if i < len(tokens2) {
			v2, _ = strconv.Atoi(tokens2[i])
		}

		if v1 > v2 {
			return 1
		}

		if v2 > v1 {
			return -1
		}
	}

	return 0
}

func main() {
	check(compareVersion("1.0.1", "1") == 1)
	check(compareVersion("7.5.2.4", "7.5.3") == -1)
	check(compareVersion("1.01", "1.001") == 0)
	check(compareVersion("1.0", "1.0.0") == 0)
	check(compareVersion("0", "0.0.0") == 0)
	check(compareVersion("1.0.0", "1.0") == 0)
}
