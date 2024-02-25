package tree

type BinaryTreeNode struct {
	Left   *BinaryTreeNode
	Right  *BinaryTreeNode
	Parent *BinaryTreeNode
	Value  interface{}
}
