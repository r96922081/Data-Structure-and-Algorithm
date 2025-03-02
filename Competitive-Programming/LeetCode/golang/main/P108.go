package main


import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func sortedArrayToBST2(nums []int, node *TreeNode, mid int, left int, right int) {
	if mid > left {
		newMid := (left + mid - 1) / 2
		node.Left = &TreeNode{nums[newMid], nil, nil}
		sortedArrayToBST2(nums, node.Left, newMid, left, mid-1)
	}

	if mid < right {
		newMid := (right + mid + 1) / 2
		node.Right = &TreeNode{nums[newMid], nil, nil}
		sortedArrayToBST2(nums, node.Right, newMid, mid+1, right)
	}
}

func sortedArrayToBST(nums []int) *TreeNode {
	if len(nums) == 0 {
		return nil
	}
	left := 0
	right := len(nums) - 1
	mid := (left + right) / 2
	root := &TreeNode{nums[mid], nil, nil}
	sortedArrayToBST2(nums, root, mid, left, right)
	return root
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {

	sortedArrayToBST([]int{-10, -3, 0, 5, 9})
}
