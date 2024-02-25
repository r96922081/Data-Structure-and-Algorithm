package tree

import (
	"fmt"
)

type biggerThanFunc func(v1 interface{}, v2 interface{}) bool

type BinarySearchTree struct {
	Root           *BinaryTreeNode
	biggerThanFunc biggerThanFunc
}

func NewBinarySearchTree(biggerThanFunc biggerThanFunc) *BinarySearchTree {
	bst := new(BinarySearchTree)
	bst.biggerThanFunc = biggerThanFunc

	return bst
}

func (bst *BinarySearchTree) insert2(insertedNode *BinaryTreeNode, comparedNode *BinaryTreeNode) {
	if bst.biggerThanFunc(insertedNode.Value, comparedNode.Value) {
		if comparedNode.Right == nil {
			comparedNode.Right = insertedNode
			insertedNode.Parent = comparedNode
		} else {
			bst.insert2(insertedNode, comparedNode.Right)
		}
	} else {
		if comparedNode.Left == nil {
			comparedNode.Left = insertedNode
			insertedNode.Parent = comparedNode
		} else {
			bst.insert2(insertedNode, comparedNode.Left)
		}
	}
}

func (bst *BinarySearchTree) Insert(v interface{}) {
	node := new(BinaryTreeNode)
	node.Value = v

	if bst.Root == nil {
		bst.Root = node
		return
	}

	bst.insert2(node, bst.Root)
}

func (bst *BinarySearchTree) transplant(n1 *BinaryTreeNode, n2 *BinaryTreeNode) {
	if n2 != nil {
		n2.Parent = n1.Parent
	}

	if n1 == bst.Root {
		bst.Root = n2
		return
	}

	if n1.Parent.Left == n1 {
		n1.Parent.Left = n2
	} else {
		n1.Parent.Right = n2
	}
}

func (bst *BinarySearchTree) delete2(node *BinaryTreeNode) {
	if node.Left == nil && node.Right == nil {
		bst.transplant(node, nil)
	} else if node.Left == nil && node.Right != nil {
		bst.transplant(node, node.Right)
	} else if node.Right == nil && node.Left != nil {
		bst.transplant(node, node.Left)
	} else {
		left := node.Left
		if left.Right == nil {
			if node.Right != nil {
				node.Right.Parent = left
				left.Right = node.Right
			}
			bst.transplant(node, left)
		} else {
			max := left.Right
			for max.Right != nil {
				max = max.Right
			}
			node.Value = max.Value
			bst.delete2(max)
		}
	}
}

func (bst *BinarySearchTree) Delete(v interface{}) {
	node := bst.search3(bst.Root, v)
	if node == nil {
		return
	}

	bst.delete2(node)
}

func (bst *BinarySearchTree) max2(node *BinaryTreeNode) interface{} {
	for node.Right != nil {
		node = node.Right
	}

	return node.Value
}

func (bst *BinarySearchTree) Max() interface{} {
	return bst.max2(bst.Root)
}

func (bst *BinarySearchTree) min2(node *BinaryTreeNode) interface{} {
	for node.Left != nil {
		node = node.Left
	}

	return node.Value
}

func (bst *BinarySearchTree) Min() interface{} {
	return bst.min2(bst.Root)
}

func (bst *BinarySearchTree) search3(node *BinaryTreeNode, key interface{}) *BinaryTreeNode {
	if node == nil {
		return nil
	}

	if !bst.biggerThanFunc(node.Value, key) && !bst.biggerThanFunc(key, node.Value) {
		return node
	} else if bst.biggerThanFunc(node.Value, key) {
		return bst.search3(node.Left, key)
	} else {
		return bst.search3(node.Right, key)
	}
}

func (bst *BinarySearchTree) search2(node *BinaryTreeNode, key interface{}) interface{} {
	ret := bst.search3(node, key)
	if ret == nil {
		return nil
	}
	return ret.Value
}

func (bst *BinarySearchTree) Search(v interface{}) interface{} {
	return bst.search2(bst.Root, v)
}

func (bst *BinarySearchTree) Predecessor(v interface{}) interface{} {
	node := bst.search3(bst.Root, v)
	if node == nil {
		return nil
	}

	if node.Left != nil {
		return bst.max2(node.Left)
	}

	if node.Parent == nil {
		return nil
	}

	if node.Parent.Right == node {
		return node.Parent.Value
	}

	p := node.Parent
	for p.Parent != nil {
		if p.Parent.Left == p {
			p = p.Parent
		} else {
			return p.Parent.Value
		}
	}

	return nil
}

func (bst *BinarySearchTree) Successor(v interface{}) interface{} {
	node := bst.search3(bst.Root, v)
	if node == nil {
		return nil
	}

	if node.Right != nil {
		return bst.min2(node.Right)
	}

	if node.Parent == nil {
		return nil
	}

	if node.Parent.Left == node {
		return node.Parent.Value
	}

	p := node.Parent
	for p.Parent != nil {
		if p.Parent.Right == p {
			p = p.Parent
		} else {
			return p.Parent.Value
		}
	}

	return nil
}

func inorder(node *BinaryTreeNode) {
	if node == nil {
		return
	}

	inorder(node.Left)
	fmt.Print(node.Value, " ")
	inorder(node.Right)

	return
}
