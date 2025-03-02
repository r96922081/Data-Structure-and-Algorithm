package main


import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func hasPathSum2(node *TreeNode, targetSum int, currentSum int) bool {
	if node.Left != nil {
		if hasPathSum2(node.Left, targetSum, currentSum+node.Val) {
			return true
		}
	}

	if node.Right != nil {
		if hasPathSum2(node.Right, targetSum, currentSum+node.Val) {
			return true
		}
	}

	if node.Left == nil && node.Right == nil {
		if currentSum+node.Val == targetSum {
			return true
		}
	}

	return false
}

func hasPathSum(root *TreeNode, sum int) bool {
	if root == nil {
		return false
	}
	return hasPathSum2(root, sum, 0)
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
}
