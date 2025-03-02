package main

import "fmt"

func main() {
    fmt.Println("P71")
}


func simplifyPath(path string) string {
	stack := make([]string, 0)
	readSlash := 0
	readChar := 1
	state := readSlash

	folderName := ""

	for i := 0; i < len(path); i++ {
		c := path[i]
		if state == readSlash {
			if c == '/' {
				continue
			} else {
				folderName += string(c)
				state = readChar
			}
		} else {
			if c != '/' {
				folderName += string(c)
			} else {
				state = readSlash

				if folderName == "." {

				} else if folderName == ".." {
					if len(stack) != 0 {
						stack = stack[:len(stack)-1]
					}
				} else {
					stack = append(stack, folderName)
				}

				folderName = ""
			}
		}
	}

	if folderName != "" {
		if folderName == "." {

		} else if folderName == ".." {
			if len(stack) != 0 {
				stack = stack[:len(stack)-1]
			}
		} else {
			stack = append(stack, folderName)
		}
	}

	if len(stack) == 0 {
		return "/"
	}

	ret := ""
	for _, p := range stack {
		ret += "/" + p
	}

	return ret
}

func TestProblem71() {
	check(simplifyPath("/home/") == "/home")
	check(simplifyPath("/../") == "/")
	check(simplifyPath("/home//foo/") == "/home/foo")
	check(simplifyPath("/a/./b/../../c/") == "/c")
	check(simplifyPath("/a/../../b/../c//.//") == "/c")
	check(simplifyPath("/a//b////c/d//././/..") == "/a/b/c")
	check(simplifyPath("/a/b") == "/a/b")
}
