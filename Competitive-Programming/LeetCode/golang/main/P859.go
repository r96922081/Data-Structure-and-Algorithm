package main


import (
	"fmt"
	"strings"
)

func buddyStrings(A string, B string) bool {
	if len(A) != len(B) {
		return false
	}

	if strings.Compare(A, B) == 0 {
		used := make(map[byte]int)
		for i := 0; i < len(A); i++ {
			_, existed := used[A[i]]
			if existed {
				return true
			}
			used[A[i]] = 1
		}
		return false
	}

	diffCount := 0
	diff1 := -1
	diff2 := -2
	for i := 0; i < len(A); i++ {
		if A[i] != B[i] {
			if diffCount == 0 {
				diff1 = i
			} else if diffCount == 1 {
				diff2 = i
			}
			diffCount++
		}
	}

	if diffCount != 2 {
		return false
	}

	if (A[diff1] == B[diff2]) && (A[diff2] == B[diff1]) {
		return true
	}
	return false
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	check(buddyStrings("ab", "ba") == true)
	check(buddyStrings("ab", "bc") == false)
	check(buddyStrings("aa", "aa") == true)
	check(buddyStrings("ab", "ab") == false)
	check(buddyStrings("", "ab") == false)
}
