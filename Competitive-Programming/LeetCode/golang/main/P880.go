package main


import (
	"fmt"
	"strconv"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

type seg struct {
	str            string
	repeat         int
	completeStrLen int
}

func decodeAtIndex(s string, k int) string {
	index := k - 1
	str := ""

	allSeg := make([]seg, 0)
	zeroSeg := seg{"", 0, 0}
	allSeg = append(allSeg, zeroSeg)
	maxLen := 0

	for i := 0; i < len(s); i++ {
		if '1' <= s[i] && s[i] <= '9' {
			count, _ := strconv.ParseInt(string(s[i]), 10, 32)
			prevSeg := &allSeg[len(allSeg)-1]
			if str != "" {
				completeStrLen := len(str) + prevSeg.completeStrLen*prevSeg.repeat
				s := seg{str, int(count), completeStrLen}
				allSeg = append(allSeg, s)
				maxLen = completeStrLen * int(count)
			} else {
				currentSeg := prevSeg
				currentSeg.repeat = currentSeg.repeat * int(count)
				maxLen = currentSeg.completeStrLen * currentSeg.repeat
			}

			if index < maxLen {
				segIndex := len(allSeg)
				currentSeg := seg{}
				prevSeg := seg{}
				prevLen := maxLen
				for index < prevLen {
					segIndex--
					currentSeg = allSeg[segIndex]
					prevSeg = allSeg[segIndex-1]
					index %= currentSeg.completeStrLen
					prevLen = prevSeg.completeStrLen * prevSeg.repeat
				}

				return string(currentSeg.str[index-prevLen])
			}

			str = ""
		} else {
			str += string(s[i])
			lastSeg := allSeg[len(allSeg)-1]
			if lastSeg.completeStrLen*lastSeg.repeat+len(str)-1 == index {
				return string(s[i])
			}

		}
	}

	return ""
}

func main() {
	check(decodeAtIndex("vzpp636m8y", 2920) == "z")
	check(decodeAtIndex("abc", 1) == "a")
	check(decodeAtIndex("ab2cd3", 6) == "d")
	check(decodeAtIndex("leet2code3", 10) == "o")
	check(decodeAtIndex("a2bcd3ef4", 24) == "a")
	check(decodeAtIndex("ha22", 5) == "h")
	check(decodeAtIndex("a2345678999999999999999", 1) == "a")
	check(decodeAtIndex("a2bcd3ef4", 24) == "a")
	check(decodeAtIndex("a2bcd3ef4", 25) == "b")
	check(decodeAtIndex("a2bcd3ef4", 26) == "c")
	check(decodeAtIndex("a2bcd3ef4", 27) == "d")
	check(decodeAtIndex("a2bcd3ef4", 10) == "d")
	check(decodeAtIndex("a2bcd3ef4", 33) == "e")
	check(decodeAtIndex("a2bcd3ef4", 34) == "f")
	check(decodeAtIndex("a2bcd3ef4", 68) == "f")
	check(decodeAtIndex("a2", 1) == "a")

}
