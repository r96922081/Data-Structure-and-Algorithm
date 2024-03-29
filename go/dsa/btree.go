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

	splitedKey, leftChild, rightChild := tree.insert2(tree.Root, key)
	if splitedKey != nil {
		node := NewBTreeNode()
		node.Keys = append(node.Keys, splitedKey)

		node.Children = append(node.Children, leftChild)
		node.Children = append(node.Children, rightChild)

		tree.Root = node
	}
}

func (tree *BTree) Find(key BTreeKey) []BTreeKey {
	ret := make([]BTreeKey, 0)

	if tree.Root == nil {
		return ret
	}
	tree.Root.find2(key, &ret)
	return ret
}

func (node *BTreeNode) find2(key BTreeKey, ret *[]BTreeKey) {
	startChild := 0
	for ; startChild < len(node.Keys); startChild++ {
		if key.Compare(node.Keys[startChild]) <= 0 {
			break
		}
	}

	endChild := startChild + 1
	for ; endChild < len(node.Keys); endChild++ {
		if key.Compare(node.Keys[endChild]) < 0 {
			break
		}
	}

	for keyIndex := startChild; keyIndex < len(node.Keys) && keyIndex < endChild; keyIndex++ {
		if key.Compare(node.Keys[keyIndex]) == 0 {
			*ret = append(*ret, node.Keys[keyIndex])
		}
	}

	if !node.IsLeaf {
		for child := startChild; child < len(node.Children); child++ {
			node.Children[child].find2(key, ret)
		}
	}
}

func copyKeySlice(src []BTreeKey) []BTreeKey {
	ret := make([]BTreeKey, len(src))
	copy(ret, src)
	return ret
}

func copyNodeSlice(src []*BTreeNode) []*BTreeNode {
	ret := make([]*BTreeNode, len(src))
	copy(ret, src)
	return ret
}

func (node *BTreeNode) splitNode() (BTreeKey, *BTreeNode, *BTreeNode) {
	left := NewBTreeNode()
	right := NewBTreeNode()
	left.IsLeaf = node.IsLeaf
	right.IsLeaf = node.IsLeaf

	middleKeyIndex := len(node.Keys) / 2
	middleKey := node.Keys[middleKeyIndex]

	left.Keys = copyKeySlice(node.Keys[:middleKeyIndex])
	right.Keys = copyKeySlice(node.Keys[middleKeyIndex+1:])

	if !node.IsLeaf {
		left.Children = copyNodeSlice(node.Children[:middleKeyIndex+1])
		right.Children = copyNodeSlice(node.Children[middleKeyIndex+1:])
	}

	return middleKey, left, right
}

func (node *BTreeNode) insertSplitedKey(childIndex int, key BTreeKey, left *BTreeNode, right *BTreeNode) {
	tempKeysLeft := copyKeySlice(node.Keys[:childIndex])
	tempKeysRight := copyKeySlice(node.Keys[childIndex:])

	node.Keys = append(tempKeysLeft, key)
	node.Keys = append(node.Keys, tempKeysRight...)

	if node.IsLeaf {
		return
	}

	if childIndex == len(node.Children)-1 {
		node.Children[childIndex] = left
		node.Children = append(node.Children, right)
	} else {
		tempChildrenLeft := copyNodeSlice(node.Children[:childIndex])
		tempChildrenRight := copyNodeSlice(node.Children[childIndex+1:])

		node.Children = append(tempChildrenLeft, left)
		node.Children = append(node.Children, right)
		node.Children = append(node.Children, tempChildrenRight...)
	}
}

func (tree *BTree) insert2(node *BTreeNode, key BTreeKey) (BTreeKey, *BTreeNode, *BTreeNode) {
	childIndex := 0
	for ; childIndex < len(node.Keys); childIndex++ {
		if key.Compare(node.Keys[childIndex]) < 0 {
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
