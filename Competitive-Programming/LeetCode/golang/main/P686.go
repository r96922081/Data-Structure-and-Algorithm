package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

// Must try all case, for example: A: baaba, B: abaab
//     B:     abaab
// case1:   baababaaba, wrong
// case2: baababaaba,  OK
func repeatedStringMatch(A string, B string) int {
	for i := 0; i < len(A); i++ {
		repeatCount := 1
		compareCount := len(A) - i
		if len(B) < compareCount {
			compareCount = len(B)
		}

		if A[i:i+compareCount] == B[0:compareCount] {
			subB := B[compareCount:]
			noSolution := false

			for subB != "" && !noSolution {
				compareCount := len(A)
				if len(subB) < compareCount {
					compareCount = len(subB)
				}
				j := 0
				for ; j < compareCount; j++ {
					if A[j] != subB[j] {
						noSolution = true
						break
					}
				}

				subB = subB[j:]
				repeatCount++
			}

			if !noSolution {
				return repeatCount
			}

		}
	}
	return -1
}

func main() {
	check(repeatedStringMatch("abcd", "cdabcdab") == 3)
	check(repeatedStringMatch("abcba", "bc") == 1)
	check(repeatedStringMatch("abcba", "bce") == -1)

	check(repeatedStringMatch("baaba", "abaab") == 2)
}
