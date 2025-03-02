package main


import (
	"fmt"
)

type LinkedListNode struct {
	Val  int
	Next *LinkedListNode
	Prev *LinkedListNode
}

type MyLinkedList struct {
	Root *LinkedListNode
	Tail *LinkedListNode
	Len  int
}

/** Initialize your data structure here. */
func Constructor() MyLinkedList {
	return MyLinkedList{}
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
func (this *MyLinkedList) Get(index int) int {
	if this.Root == nil {
		return -1
	}

	if index < 0 || this.Len <= index {
		return -1
	}

	node := this.Root
	i := 0
	for i < index {
		node = node.Next
		i++
	}

	return node.Val

}

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
func (this *MyLinkedList) AddAtHead(val int) {
	node := &LinkedListNode{val, nil, nil}
	if this.Root == nil {
		this.Tail = node
	} else {
		this.Root.Prev = node
		node.Next = this.Root
	}
	this.Root = node
	this.Len++
}

/** Append a node of value val to the last element of the linked list. */
func (this *MyLinkedList) AddAtTail(val int) {
	node := &LinkedListNode{val, nil, nil}
	if this.Root == nil {
		this.Root = node
	} else {
		node.Prev = this.Tail
		this.Tail.Next = node
	}
	this.Tail = node
	this.Len++
}

/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
func (this *MyLinkedList) AddAtIndex(index int, val int) {
	if index > this.Len || index < 0 {
		return
	}

	if index == this.Len {
		this.AddAtTail(val)
		return
	}

	if index == 0 {
		this.AddAtHead(val)
		return
	}

	added := &LinkedListNode{val, nil, nil}
	node := this.Root
	i := 0
	for i < index {
		node = node.Next
		i++
	}

	added.Next = node
	added.Prev = node.Prev
	node.Prev.Next = added
	node.Prev = added
	this.Len++
}

/** Delete the index-th node in the linked list, if the index is valid. */
func (this *MyLinkedList) DeleteAtIndex(index int) {
	if this.Len == 0 {
		return
	}
	if index >= this.Len || index < 0 {
		return
	}
	if index == 0 {
		if this.Len == 1 {
			this.Root = nil
			this.Tail = nil
			return
		}

		this.Root.Next.Prev = nil
		this.Root = this.Root.Next
	} else if index == this.Len-1 {
		if this.Len == 1 {
			this.Root = nil
			this.Tail = nil
			return
		}
		this.Tail.Prev.Next = nil
		this.Tail = this.Tail.Prev
	} else {
		node := this.Root
		i := 0
		for i < index {
			node = node.Next
			i++
		}
		node.Prev.Next = node.Next
		node.Next.Prev = node.Prev
	}

	this.Len--
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	obj := Constructor()
	obj.AddAtHead(1)
	obj.AddAtTail(3)
	obj.AddAtIndex(1, 2)
	param1 := obj.Get(1)
	check(param1 == 2)
	obj.DeleteAtIndex(1)
	param2 := obj.Get(1)
	check(param2 == 3)

	obj2 := Constructor()
	obj2.AddAtHead(1)
	obj2.AddAtIndex(1, 2)
	param21 := obj2.Get(1)
	check(param21 == 2)
	param22 := obj2.Get(0)
	check(param22 == 1)
	param23 := obj2.Get(2)
	check(param23 == -1)
}
