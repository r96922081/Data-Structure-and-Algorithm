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

type checkFunctionType func(n int) bool

func enumeratePalindrome(left int, right int, digitCount int, digit int, currentNum int, checkFunction checkFunctionType) int {
	if digit == int(math.Ceil(float64(digitCount)/2)) {
		if digitCount%2 == 1 {
			for i := 0; i <= 9; i++ {
				v := int(math.Pow10(digit-1)) * i
				currentNum += v
				if checkFunction(currentNum) && currentNum >= left && currentNum <= right && currentNum != 1 {
					return currentNum
				}
				currentNum -= v
			}
		} else {
			for i := 0; i <= 9; i++ {
				v1 := int(math.Pow10(digit-1)) * i
				v2 := int(math.Pow10(digitCount-(digit-1)-1)) * i
				currentNum += v1 + v2
				if checkFunction(currentNum) && currentNum >= left && currentNum <= right && currentNum != 1 {
					return currentNum
				}
				currentNum -= v1 + v2
			}
		}
		return -1
	}

	for i := 0; i <= 9; i++ {
		v1 := int(math.Pow10(digit-1)) * i
		v2 := int(math.Pow10(digitCount-(digit-1)-1)) * i
		currentNum += v1 + v2
		ret := enumeratePalindrome(left, right, digitCount, digit+1, currentNum, checkFunction)
		if ret != -1 {
			return ret
		}
		currentNum -= v1 + v2
	}

	return -1
}

// Calculate a ^ b % n
func modExp(a int, b int, n int) int {
	if n == 0 {
		return 0
	}

	ret := 1

	for i := 31; i >= 0; i-- {
		if (b & (1 << uint(i))) == 0 {
			ret = ret * ret % n
		} else {
			ret = ret * ret * a % n
		}
	}

	return ret
}

func primePalindrome(N int) int {
	left := uint64(N)
	right := left * 10

	// Fermat's theorem:
	// If p is prime, then a ^(p-1) = 1 (mod p) for all a, such that gcd(a,p) = 1
	// PseudoPrimalityTest:
	// If we take a as 2, then if 2 ^ (p - 1) != 1 (mod p), then it's definitely a composite
	// else it SHOULD be a prime with very low error rate
	checkByPseudoPrimality := func(n int) bool {
		if modExp(2, n-1, n) == 1 {
			return true
		}
		return false
	}

	// false = prime, true = composite number
	allNum := make([]bool, 0)

	checkBySieve := func(n int) bool {
		if allNum[n] == false {
			return true
		}
		return false
	}

	for {
		var checkFunc checkFunctionType
		if N <= 1000000 {
			allNum = make([]bool, 200000000)
			checkFunc = checkBySieve
			for i := uint64(2); i <= uint64(math.Sqrt(float64(right))); i++ {
				if allNum[i] == true {
					continue
				}
				for j := uint64(2); ; j++ {
					product := i * j
					if product >= right {
						break
					}
					allNum[product] = true
				}
			}
		} else {
			checkFunc = checkByPseudoPrimality
		}
		digitCount := int(math.Floor(math.Log10(float64(right))) + 1)
		ret := enumeratePalindrome(int(left), int(right), digitCount-1, 1, 0, checkFunc)
		if ret != -1 {
			return ret
		}
		ret = enumeratePalindrome(int(left), int(right), digitCount, 1, 0, checkFunc)
		if ret != -1 {
			return ret
		}

		right *= 10
		if right > 200000000 {
			right = 200000000
		}
	}
}

func main() {
	modExp(2, 11, 5)
	check(primePalindrome(13832) == 13931)
	check(primePalindrome(798) == 919)
	check(primePalindrome(1) == 2)
	check(primePalindrome(6) == 7)
	check(primePalindrome(8) == 11)
	check(primePalindrome(13) == 101)
	check(primePalindrome(1234000) == 1235321)
	check(primePalindrome(9989900) == 100030001)
}
