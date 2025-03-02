package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

type ListNode struct {
	Val  int
	Next *ListNode
}

func rotateRight(head *ListNode, k int) *ListNode {
	if head == nil {
		return nil
	}

	listLen := 0
	tail := new(ListNode)
	for node := head; node != nil; node = node.Next {
		listLen++
		tail = node
	}

	k %= listLen
	if k == 0 {
		return head
	}
	node := head

	for i := 1; i <= (listLen-1)-k; i++ {
		node = node.Next
	}

	tail.Next = head
	head = node.Next
	node.Next = nil

	return head
}

func exhaustedTest() {

}

func main() {
	count := 10

	for i := 0; i < count; i++ {
		nodes := make([]*ListNode, count)
		for i := 0; i < count; i++ {
			nodes[i] = &ListNode{i, nil}
		}
		for i := 0; i < count-1; i++ {
			nodes[i].Next = nodes[i+1]
		}

		head := rotateRight(nodes[0], i)
		check(head.Val == (count-i)%count)
		node := head
		for j := 0; j < count-1; j++ {
			if node.Next.Val != 0 {
				check(node.Val < node.Next.Val)
			}
		}
	}
}
