package main


import (
	"fmt"
)

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */

type ListNode struct {
	Val  int
	Next *ListNode
}

func deleteDuplicates(head *ListNode) *ListNode {
	if head == nil {
		return nil
	}

	used := make(map[int]int)

	prev := head
	used[head.Val] = head.Val

	for current := head.Next; current != nil; current = current.Next {
		_, duplicate := used[current.Val]
		if duplicate {
			prev.Next = nil
		} else {
			prev.Next = current
			used[current.Val] = current.Val
			prev = current
		}
	}

	return head
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
}
