package main

func main() {
    fmt.Println("P306")
}


import "fmt"

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func BigIntAdd(a string, b string) string {
	sum := ""

	carry := 0
	for i := 0; i < len(a) || i < len(b); i++ {
		digitA := 0
		digitB := 0
		if i < len(a) {
			digitA = int(a[len(a)-1-i] - '0')
		}
		if i < len(b) {
			digitB = int(b[len(b)-1-i] - '0')
		}

		sumC := digitA + digitB + carry
		if sumC >= 10 {
			sumC -= 10
			carry = 1
		} else {
			carry = 0
		}

		sum = string(sumC+'0') + sum
	}

	if carry == 1 {
		sum = "1" + sum
	}

	return sum
}

func isAdditiveNumber2(num, n1, n2 string, startIndex int, first bool) bool {
	if startIndex == len(num) && !first {
		return true
	}

	if n2 != "0" && n2[0] == '0' {
		return false
	}

	for i := startIndex + 1; i <= len(num); i++ {
		if BigIntAdd(n1, n2) == num[startIndex:i] {
			return isAdditiveNumber2(num, n2, num[startIndex:i], i, false)
		}
	}

	return false
}

func isAdditiveNumber(num string) bool {
	if len(num) == 0 {
		return false
	}

	for i := 1; i < len(num); i++ {
		if num[0:i] != "0" && num[0] == '0' {
			continue
		}

		for j := i + 1; j < len(num); j++ {
			if isAdditiveNumber2(num, num[0:i], num[i:j], j, true) {
				return true
			}
		}
	}

	return false
}

func TestProblem306() {
	check(isAdditiveNumber("123") == true)
	check(isAdditiveNumber("112358") == true)
	check(isAdditiveNumber("199100199") == true)
	check(isAdditiveNumber("199100198") == false)
	check(isAdditiveNumber("1") == false)
	check(isAdditiveNumber("124") == false)
	check(isAdditiveNumber("") == false)
	check(isAdditiveNumber("112233") == true)
	check(isAdditiveNumber("1231124") == true)
	check(isAdditiveNumber("12") == false)
	check(isAdditiveNumber("198019823962") == true)
	check(isAdditiveNumber("101") == true)
	check(isAdditiveNumber("1001") == false)
	check(isAdditiveNumber("000") == true)
	check(isAdditiveNumber("011") == true)
}
