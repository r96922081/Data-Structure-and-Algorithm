package main


import (
	"fmt"
)

func isPalindrome(s string) bool {
	if len(s) == 0 {
		return true
	}

	newS := ""
	a := 'a'
	z := 'z'
	capA := 'A'
	capZ := 'Z'
	zero := '0'
	nine := '9'

	for _, rune := range s {
		if capA <= rune && rune <= capZ {
			rune -= capA - a
		}

		if (a <= rune && rune <= z) || (zero <= rune && rune <= nine) {
			newS += string(rune)
		}
	}

	for i := 0; i < len(newS)/2; i++ {
		if newS[i] != newS[len(newS)-1-i] {
			return false
		}
	}

	return true
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	check(isPalindrome("0P") == false)
	check(isPalindrome("A man, a plan, a canal: Panama") == true)
	check(isPalindrome("race a car") == false)
}
