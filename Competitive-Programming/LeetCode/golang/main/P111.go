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

func minDepth(root *TreeNode) int {
	if root == nil {
		return 0
	}

	if root.Left == nil && root.Right == nil {
		return 1
	}

	leftHeight := math.MaxInt32
	rightHeight := math.MaxInt32

	if root.Left != nil {
		leftHeight = minDepth(root.Left)
	}

	if root.Right != nil {
		rightHeight = minDepth(root.Right)
	}

	return int(math.Min(float64(leftHeight), float64(rightHeight))) + 1
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
}
