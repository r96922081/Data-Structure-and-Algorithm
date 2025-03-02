package main

import "fmt"

func main() {
    fmt.Println("P3")
}

func lengthOfLongestSubstring(s string) int {
	maxLen := 0
	prevPos := make([]int, 128)

	for i := 0; i < 128; i++ {
		prevPos[i] = -1
	}

	prevStart := 0

	for i := 0; i < len(s); i++ {
		c := s[i]
		if prevPos[c] >= prevStart {
			prevStart = prevPos[c] + 1
		} else {
			currentLen := i - prevStart + 1
			if currentLen > maxLen {
				maxLen = currentLen
			}
		}

		prevPos[c] = i
	}

	return maxLen
}
