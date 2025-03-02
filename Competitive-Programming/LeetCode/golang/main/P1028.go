package main

import "fmt"

func main() {
    fmt.Println("P1028")
}

func getVal(s *string) int {
	i := 0
	for ; i < len(*s) && (*s)[i] != '-'; i++ {
	}
	val, _ := strconv.Atoi((*s)[:i])
	(*s) = (*s)[i:]
	return val
}

func getNext(s *string, node **TreeNode, level int) {
	if *s == "" {
		return
	}

	thisLevel := 0
	for i := 0; (*s)[i] == '-'; i++ {
		thisLevel++
	}

	if thisLevel != level+1 {
		return
	}

	*node = &TreeNode{}

	//-2--3
	(*s) = (*s)[thisLevel:]
	//2--3
	(*node).Val = getVal(s)
	//--3
	traverse(s, *node, thisLevel)
}

func traverse(s *string, node *TreeNode, level int) {
	getNext(s, &node.Left, level)
	getNext(s, &node.Right, level)
}

func recoverFromPreorder(s string) *TreeNode {
	if s == "" {
		return nil
	}

	root := &TreeNode{}
	root.Val = getVal(&s)
	traverse(&s, root, 0)

	return root
}