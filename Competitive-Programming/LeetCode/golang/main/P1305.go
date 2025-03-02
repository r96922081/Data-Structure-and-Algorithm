package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Print("check failed!")
	}
}

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func pop(stack *[]*TreeNode) *TreeNode {
	ret := (*stack)[len(*stack)-1]
	*stack = (*stack)[:len(*stack)-1]
	return ret
}

func push(stack *[]*TreeNode, n1 *TreeNode) {
	*stack = append(*stack, n1)
}

func getAllElements(root1 *TreeNode, root2 *TreeNode) []int {
	ret := make([]int, 0)

	stack1 := make([]*TreeNode, 0)
	stack2 := make([]*TreeNode, 0)

	n1 := root1
	n2 := root2

	sentinal_value := 100001

	push(&stack1, &TreeNode{sentinal_value, nil, nil})
	push(&stack2, &TreeNode{sentinal_value, nil, nil})

	for n1 != nil {
		push(&stack1, n1)
		n1 = n1.Left
	}

	for n2 != nil {
		push(&stack2, n2)
		n2 = n2.Left
	}

	n1 = pop(&stack1)
	n2 = pop(&stack2)

	for n1.Val != sentinal_value || n2.Val != sentinal_value {
		if n1.Val < n2.Val {
			ret = append(ret, n1.Val)
			n1 = n1.Right
			for n1 != nil {
				push(&stack1, n1)
				n1 = n1.Left
			}
			n1 = pop(&stack1)
		} else {
			ret = append(ret, n2.Val)
			n2 = n2.Right
			for n2 != nil {
				push(&stack2, n2)
				n2 = n2.Left
			}
			n2 = pop(&stack2)
		}
	}

	return ret
}

func main() {
	n1 := &TreeNode{1, nil, nil}
	n2 := &TreeNode{2, nil, nil}
	n4 := &TreeNode{4, nil, nil}
	n2.Left = n1
	n2.Right = n4

	n0 := &TreeNode{0, nil, nil}
	n1b := &TreeNode{1, nil, nil}
	n3 := &TreeNode{3, nil, nil}
	n1b.Left = n0
	n1b.Right = n3

	ret := getAllElements(n2, n1b)
	answer := []int{0, 1, 1, 2, 3, 4}

	for i := 0; i < 6; i++ {
		check(ret[i] == answer[i])
	}
}
