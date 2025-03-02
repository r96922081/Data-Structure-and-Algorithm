package main

import "fmt"

func main() {
    fmt.Println("P65")
}

// 0, 123, 10001
func eNumSeqAfterDotState(s string, i int, firstDigit bool) bool {
	if firstDigit {
		if s[i] < '0' || '9' < s[i] {
			return false
		}
		i++
	}
	for ; i < len(s); i++ {
		c := s[i]
		if '0' <= c && c <= '9' {
			continue
		} else if c == 'e' {
			return eState(s, i)
		}
		return false
	}

	return true
}

func noIntBeforeDotState(s string, i int) bool {
	i++
	if i == len(s) {
		return false
	}

	return eNumSeqAfterDotState(s, i, true)
}

func dotState(s string, i int) bool {
	i++
	if i == len(s) {
		return true
	}

	return eNumSeqAfterDotState(s, i, false)
}

// 0, 123, 10001
func eNumSeqState(s string, i int) bool {
	if i == len(s) {
		return false
	}

	if s[i] < '0' || '9' < s[i] {
		return false
	}
	i++

	for ; i < len(s); i++ {
		c := s[i]
		if '0' <= c && c <= '9' {
			continue
		}
		return false
	}

	return true
}

func eState(s string, i int) bool {
	i++
	if i == len(s) {
		return false
	}

	if s[i] == '+' || s[i] == '-' {
		i++
	}

	return eNumSeqState(s, i)
}

// 0, 123, 10001
func numSeqIntPartState(s string, i int) bool {
	if i == len(s) {
		return false
	}

	if s[i] < '0' || '9' < s[i] {
		return false
	}
	i++

	for ; i < len(s); i++ {
		c := s[i]
		if '0' <= c && c <= '9' {
			continue
		}
		if c == 'e' {
			return eState(s, i)
		}
		if c == '.' {
			return dotState(s, i)
		}

		return false
	}

	return true
}

func signState(s string, i int) bool {
	i++
	if s[i] == '.' {
		return noIntBeforeDotState(s, i)
	}
	return numSeqIntPartState(s, i)
}

func beginState(s string) bool {
	i := 0
	if s[i] == '+' || s[i] == '-' {
		return signState(s, 0)
	}

	if s[i] == '.' {
		return noIntBeforeDotState(s, i)
	}

	return numSeqIntPartState(s, i)
}

func isNumber(s string) bool {
	s = strings.TrimLeft(s, " ")
	s = strings.TrimRight(s, " ")
	if len(s) == 0 {
		return false
	}
	return beginState(s)
}
