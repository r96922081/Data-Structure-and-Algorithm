package main

import "fmt"

func main() {
    fmt.Println("P98")
}

func isValidBSTMain(first *bool, lastVal *int, node *TreeNode) bool {
	if node == nil {
		return true
	}

	if isValidBSTMain(first, lastVal, node.Left) == false {
		return false
	}
	if *first {
		*first = false
	} else {
		if node.Val <= *lastVal {
			return false
		}
	}
	*lastVal = node.Val
	if isValidBSTMain(first, lastVal, node.Right) == false {
		return false
	}

	return true
}

func isValidBST(root *TreeNode) bool {
	first := true
	lastVal := 0
	return isValidBSTMain(&first, &lastVal, root)
}
