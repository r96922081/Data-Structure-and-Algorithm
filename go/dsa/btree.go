package dsa

type BTreeKey interface {
	ToString() string
	Compare(k BTreeKey) int
}

type BTree struct {
	Root   *BTreeNode
	Degree int
}

type BTreeNode struct {
	IsLeaf   bool
	Keys     []BTreeKey
	Children []*BTreeNode
}

func NewBTree(degree int) *BTree {
	return &BTree{nil, degree}
}

func NewBTreeNode() *BTreeNode {
	return &BTreeNode{false, make([]BTreeKey, 0), make([]*BTreeNode, 0)}
}

func (tree *BTree) Insert(key BTreeKey) {
	if tree.Root == nil {
		n := NewBTreeNode()
		n.IsLeaf = true
		n.Keys = append(n.Keys, key)
		tree.Root = n
		return
	}

	tree.insert2(tree.Root, key)
}

func (node *BTreeNode) splitNode() (BTreeKey, *BTreeNode, *BTreeNode) {
	left := NewBTreeNode()
	right := NewBTreeNode()
	left.IsLeaf = node.IsLeaf
	right.IsLeaf = node.IsLeaf

	middleKeyIndex := len(node.Keys) / 2
	middleKey := node.Keys[middleKeyIndex]

	left.Keys = node.Keys[:middleKeyIndex]
	right.Keys = node.Keys[middleKeyIndex+1:]

	if !node.IsLeaf {
		left.Children = node.Children[:middleKeyIndex+1]
		right.Children = node.Children[middleKeyIndex+1:]
	}

	return middleKey, left, right
}

func (node *BTreeNode) insertSplitedKey(childIndex int, key BTreeKey, left *BTreeNode, right *BTreeNode) {
	tempNodeLeft := node.Keys[:childIndex]
	tempNodeRight := node.Keys[childIndex:]
	node.Keys = append(tempNodeLeft, key)
	node.Keys = append(node.Keys, tempNodeRight...)

	if node.IsLeaf {
		return
	}

	if childIndex == len(node.Children)-1 {
		node.Children[childIndex] = left
		node.Children = append(node.Children, right)
	} else {
		tempChildrenLeft := node.Children[:childIndex]
		tempChildrenRight := node.Children[childIndex:]
		node.Children = append(tempChildrenLeft, left)
		node.Children = append(tempChildrenLeft, right)
		node.Children = append(tempChildrenLeft, tempChildrenRight...)
	}
}

func (tree *BTree) insert2(node *BTreeNode, key BTreeKey) (BTreeKey, *BTreeNode, *BTreeNode) {
	childIndex := 0
	for ; childIndex < len(node.Keys); childIndex++ {
		if key.Compare(node.Keys[len(node.Keys)-1]) < 0 {
			break
		}
	}

	var splitedKey BTreeKey = nil
	var leftChild *BTreeNode = nil
	var rightChild *BTreeNode = nil

	if node.IsLeaf {
		splitedKey = key
	} else {
		splitedKey, leftChild, rightChild = tree.insert2(node.Children[childIndex], key)
	}

	if splitedKey != nil {
		node.insertSplitedKey(childIndex, splitedKey, leftChild, rightChild)
	}

	if tree.overFull(node) {
		return node.splitNode()
	}
	return nil, nil, nil
}

func (tree *BTree) overFull(n *BTreeNode) bool {
	return len(n.Keys) >= tree.Degree*2
}

func (tree *BTree) Traverse() []BTreeKey {
	keys := make([]BTreeKey, 0)
	if tree.Root == nil {
		return keys
	}

	tree.Root.traverse2(&keys)
	return keys
}

func (node *BTreeNode) traverse2(keys *[]BTreeKey) {
	i := 0
	for ; i < len(node.Keys); i++ {
		*keys = append(*keys, node.Keys[i])
		if !node.IsLeaf {
			node.Children[i].traverse2(keys)
		}
	}
	if !node.IsLeaf {
		node.Children[i].traverse2(keys)
	}
}
