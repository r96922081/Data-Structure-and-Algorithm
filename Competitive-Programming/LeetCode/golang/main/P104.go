package main


import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func calculateDepth(node *TreeNode, level int) int {
	if node == nil {
		return level
	}

	leftLevel := calculateDepth(node.Left, level+1)
	rightLevel := calculateDepth(node.Right, level+1)

	if leftLevel > rightLevel {
		return leftLevel
	}

	return rightLevel
}

func maxDepth(root *TreeNode) int {
	return calculateDepth(root, 0)
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {

}
