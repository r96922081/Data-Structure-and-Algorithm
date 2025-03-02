package main


import (
	"fmt"
)

func getRow(rowIndex int) []int {
	ret := []int{1}

	if rowIndex == 0 {
		return ret
	}

	prevS := ret

	for i := 1; i <= rowIndex; i++ {
		s := make([]int, 0)
		s = append(s, 1)

		for j := 1; j < i; j++ {
			s = append(s, prevS[j-1]+prevS[j])
		}

		s = append(s, 1)

		if i == rowIndex {
			return s
		}

		prevS = s
	}

	return ret
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
}
