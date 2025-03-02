package main


import (
	"fmt"
	"math/big"
)

func permutation(n int, m int) uint64 {
	if m == 0 {
		return 1
	}

	numerator := big.NewInt(1)
	denumerator1 := big.NewInt(1)
	denumerator2 := big.NewInt(1)
	temp := big.NewInt(1)

	for i := int(1); i <= n; i++ {
		temp.SetInt64(int64(i))
		numerator.Mul(numerator, temp)
	}

	for i := int(1); i <= m; i++ {
		temp.SetInt64(int64(i))
		denumerator1.Mul(denumerator1, temp)
	}

	for i := int(1); i <= n-m; i++ {
		temp.SetInt64(int64(i))
		denumerator2.Mul(denumerator2, temp)
	}

	numerator.Div(numerator, denumerator1)
	numerator.Div(numerator, denumerator2)
	return numerator.Uint64()
}

func climbStairs(n int) int {
	ret := uint64(0)

	for i := 0; i <= n; i += 2 {
		countOf2 := i / 2
		ret2 := permutation(int(n-countOf2), int(countOf2))
		ret += ret2
	}

	return int(ret)
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	check(climbStairs(1) == 1)
	check(climbStairs(2) == 2)
	check(climbStairs(3) == 3)
	check(climbStairs(5) == 8)
	check(climbStairs(35) == 14930352)
	check(climbStairs(44) == 1134903170)
}
