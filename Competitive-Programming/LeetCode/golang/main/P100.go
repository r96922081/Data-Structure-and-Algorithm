package main


import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func isSameTree(p *TreeNode, q *TreeNode) bool {
	if p == nil && q == nil {
		return true
	}

	if p == nil && q != nil {
		return false
	}

	if p != nil && q == nil {
		return false
	}

	if p.Val != q.Val {
		return false
	}

	if isSameTree(p.Left, q.Left) == false {
		return false
	}

	if isSameTree(p.Right, q.Right) == false {
		return false
	}

	return true
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {

}
