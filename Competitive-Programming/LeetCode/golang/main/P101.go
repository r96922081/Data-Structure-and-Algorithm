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

func copyTreeSymmetricaly(copyTo *TreeNode, beCopyed *TreeNode) {
	copyTo.Val = beCopyed.Val
	if beCopyed.Right != nil {
		copyTo.Left = new(TreeNode)
		copyTreeSymmetricaly(copyTo.Left, beCopyed.Right)
	}

	if beCopyed.Left != nil {
		copyTo.Right = new(TreeNode)
		copyTreeSymmetricaly(copyTo.Right, beCopyed.Left)
	}
}

func isSymmetric(root *TreeNode) bool {
	if root == nil {
		return true
	}

	if root.Left == nil && root.Right == nil {
		return true
	}

	if root.Left == nil && root.Right != nil {
		return false
	}

	if root.Right == nil && root.Left != nil {
		return false
	}

	rightSymmericalTree := new(TreeNode)
	copyTreeSymmetricaly(rightSymmericalTree, root.Right)

	return isSameTree(rightSymmericalTree, root.Left)
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {

}
