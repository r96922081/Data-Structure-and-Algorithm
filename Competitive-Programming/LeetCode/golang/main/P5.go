package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func isPalindrome(s string, start, end int) bool {
	if end <= start {
		return true
	}

	mid := (start + end) / 2
	even := true
	if (end-start+1)%2 == 1 {
		even = false
	}

	if even {
		for i := mid; i >= start; i-- {
			if s[i] != s[mid+1+(mid-i)] {
				return false
			}
		}
		return true
	}

	for i := mid - 1; i >= start; i-- {
		if s[i] != s[mid+(mid-i)] {
			return false
		}
	}
	return true
}

func longestPalindromeBruteForce(s string) string {
	if s == "" {
		return ""
	}

	sLen := len(s)
	maxPalindromeLen := 0
	maxPalindromeStr := ""

	for i := 0; i < sLen; i++ {
		for j := i; j < sLen; j++ {
			if isPalindrome(s, i, j) {
				thisLen := j - i + 1
				if thisLen > maxPalindromeLen {
					maxPalindromeLen = thisLen
					maxPalindromeStr = s[i : j+1]
				}
			}
		}
	}

	return maxPalindromeStr
}

func longestPalindrome(s string) string {
	if s == "" {
		return ""
	}

	maxPalindromeLen := 1
	maxPalindromeStr := string(s[0])
	sLen := len(s)

	for i := 0; i < sLen; i++ {
		// odd
		for pLen := 1; i-pLen >= 0 && i+pLen < sLen; pLen++ {
			if s[i-pLen] == s[i+pLen] {
				if pLen*2+1 > maxPalindromeLen {
					maxPalindromeLen = pLen*2 + 1
					maxPalindromeStr = s[i-pLen : i+pLen+1]
				}
			} else {
				break
			}
		}

		// even
		for pLen := 0; i-pLen >= 0 && i+1+pLen < sLen; pLen++ {
			if s[i-pLen] == s[i+1+pLen] {
				if pLen*2+2 > maxPalindromeLen {
					maxPalindromeLen = pLen*2 + 2
					maxPalindromeStr = s[i-pLen : i+pLen+1+1]
				}
			} else {
				break
			}
		}
	}

	return maxPalindromeStr
}

func main() {
	check(isPalindrome("abba", 0, 3) == true)
	check(isPalindrome("abba", 0, 0) == true)
	check(isPalindrome("abba", 0, 1) == false)
	check(isPalindrome("abba", 1, 2) == true)
	check(isPalindrome("abcba", 0, 4) == true)
	check(isPalindrome("abcba", 1, 3) == true)
	check(isPalindrome("abcba", 1, 2) == false)
	check(longestPalindrome("abcda") == "a")
	check(longestPalindrome("aaaa") == "aaaa")
	check(longestPalindrome("babad") == "bab")
	check(longestPalindrome("cbbd") == "bb")
	check(longestPalindrome("abc") == "a")
}
