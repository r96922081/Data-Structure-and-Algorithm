package main


import (
	"fmt"
	"strconv"
	"strings"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func validIPAddress(ip string) string {
	if strings.Count(ip, ".") == 3 {
		tokens := strings.Split(ip, ".")
		for _, token := range tokens {
			if len(token) > 3 {
				return "Neither"
			}

			i, err := strconv.ParseInt(token, 10, 32)
			if err != nil {
				return "Neither"
			}

			if i <= 9 && len(token) > 1 {
				return "Neither"
			}

			if i <= 99 && len(token) > 2 {
				return "Neither"
			}

			if i < 0 || i > 255 {
				return "Neither"
			}
		}
		return "IPv4"
	} else if strings.Count(ip, ":") == 7 {
		tokens := strings.Split(ip, ":")
		for _, token := range tokens {
			if len(token) > 4 || len(token) == 0 {
				return "Neither"
			}

			for i := 0; i < len(token); i++ {
				b := token[i]
				if !(('0' <= b && b <= '9') || ('a' <= b && b <= 'f') ||
					('A' <= b && b <= 'F')) {
					return "Neither"
				}
			}
		}
		return "IPv6"
	}

	return "Neither"
}

func main() {
	check(validIPAddress("172.16.254.1") == "IPv4")
	check(validIPAddress("172.16.254.01") == "Neither")
	check(validIPAddress("172.16.054.01") == "Neither")
	check(validIPAddress("17211111111111111.16.254.1") == "Neither")
	check(validIPAddress("2001:0db8:85a3:0:0:8A2E:370:34") == "IPv6")
	check(validIPAddress("2001:0db8:85a3:0::8A2E:370:34") == "Neither")
	check(validIPAddress("256.256.256.256") == "Neither")
}
