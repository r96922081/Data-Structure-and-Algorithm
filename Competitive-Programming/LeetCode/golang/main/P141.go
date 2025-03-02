package main


import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func hasCycle(head *ListNode) bool {
	traversed := make(map[*ListNode]bool)

	for head != nil {
		_, existed := traversed[head]
		if existed {
			return true
		}

		traversed[head] = true
		head = head.Next
	}

	return false
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	n1 := &ListNode{3, nil}
	n2 := &ListNode{2, nil}
	n3 := &ListNode{0, nil}
	n4 := &ListNode{4, nil}
	n1.Next = n2
	n2.Next = n3
	n3.Next = n4
	n4.Next = n2
	hasCycle(n1)
}
