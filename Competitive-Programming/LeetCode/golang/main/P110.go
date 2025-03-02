package main

import (
	"fmt"
	"math"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func isBalanced2(root *TreeNode) (bool, int) {
	leftHeight := 0
	rightHeight := 0
	b := false

	if root.Left != nil {
		b, leftHeight = isBalanced2(root.Left)
		if !b {
			return false, 0
		}
	}

	if root.Right != nil {
		b, rightHeight = isBalanced2(root.Right)
		if !b {
			return false, 0
		}
	}

	if int(math.Abs(float64(leftHeight-rightHeight))) > 1 {
		return false, 0
	}

	return true, int(math.Max(float64(leftHeight), float64(rightHeight))) + 1
}

func isBalanced(root *TreeNode) bool {
	if root == nil {
		return true
	}
	b, _ := isBalanced2(root)
	return b
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
}
