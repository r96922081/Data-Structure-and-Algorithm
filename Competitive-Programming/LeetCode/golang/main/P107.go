package main


import (
	"fmt"
	"sort"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func traverse(node *TreeNode, level int, levelOrderMap map[int][]int) {
	if node == nil {
		return
	}

	slice, ok := levelOrderMap[level]
	if !ok {
		slice = make([]int, 0)
		levelOrderMap[level] = slice
	}

	slice = append(slice, node.Val)
	levelOrderMap[level] = slice

	traverse(node.Left, level+1, levelOrderMap)
	traverse(node.Right, level+1, levelOrderMap)
}

func levelOrderBottom(root *TreeNode) [][]int {
	levelOrderMap := make(map[int][]int)

	traverse(root, 0, levelOrderMap)
	keys := make([]int, 0)
	for key := range levelOrderMap {
		keys = append(keys, key)
	}

	sort.Ints(keys)

	ret := make([][]int, 0)
	for i := len(keys) - 1; i >= 0; i-- {
		ret = append(ret, levelOrderMap[keys[i]])
	}

	return ret
}

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func main() {
	n1 := &TreeNode{3, nil, nil}
	n2 := &TreeNode{9, nil, nil}
	n3 := &TreeNode{20, nil, nil}
	n4 := &TreeNode{15, nil, nil}
	n5 := &TreeNode{7, nil, nil}
	n1.Left = n2
	n1.Right = n3
	n3.Left = n4
	n3.Right = n5

	levelOrderBottom(n1)
}
