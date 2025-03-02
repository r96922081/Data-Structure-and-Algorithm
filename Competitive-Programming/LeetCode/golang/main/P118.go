package main


import (
	"fmt"
)

func generate(numRows int) [][]int {
	ret := make([][]int, 0)

	if numRows == 0 {
		return ret
	}

	s := make([]int, 0)
	s = append(s, 1)
	ret = append(ret, s)

	if numRows == 1 {
		return ret
	}

	for i := 2; i <= numRows; i++ {
		s := make([]int, 0)
		s = append(s, 1)
		prevS := ret[i-2]

		for j := 1; j < i-1; j++ {
			s = append(s, prevS[j-1]+prevS[j])
		}

		s = append(s, 1)

		ret = append(ret, s)
	}

	return ret
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	generate(3)
}
