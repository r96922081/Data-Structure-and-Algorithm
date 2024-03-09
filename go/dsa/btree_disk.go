package dsa

type BTreeKeyDisk interface {
	ToString() string
	Compare(k BTreeKeyDisk) int
}

type BTreeDisk struct {
	Root   *BTreeNodeDisk
	Degree int
}

type BTreeNodeDisk struct {
	IsLeaf   bool
	Keys     []BTreeKeyDisk
	Children []*BTreeNodeDisk
}

func NewBTreeDisk(degree int) *BTreeDisk {
	return &BTreeDisk{nil, degree}
}

func NewBTreeNodeDisk() *BTreeNodeDisk {
	return &BTreeNodeDisk{false, make([]BTreeKeyDisk, 0), make([]*BTreeNodeDisk, 0)}
}

func (tree *BTreeDisk) Insert(key BTreeKeyDisk) {
	if tree.Root == nil {
		n := NewBTreeNodeDisk()
		n.IsLeaf = true
		n.Keys = append(n.Keys, key)
		tree.Root = n
		return
	}

	splitedKey, leftChild, rightChild := tree.insert2(tree.Root, key)
	if splitedKey != nil {
		node := NewBTreeNodeDisk()
		node.Keys = append(node.Keys, splitedKey)

		node.Children = append(node.Children, leftChild)
		node.Children = append(node.Children, rightChild)

		tree.Root = node
	}
}

func (tree *BTreeDisk) Find(key BTreeKeyDisk) BTreeKeyDisk {
	if tree.Root == nil {
		return nil
	}
	return tree.Root.find2(key)
}

func (node *BTreeNodeDisk) find2(key BTreeKeyDisk) BTreeKeyDisk {
	i := 0
	for ; i < len(node.Keys); i++ {
		key2 := node.Keys[i]
		if key.Compare(key2) == 0 {
			return key2
		} else if key.Compare(key2) < 0 {
			if node.IsLeaf {
				return nil
			}
			return node.Children[i].find2(key)
		}
	}

	if node.IsLeaf {
		return nil
	}
	return node.Children[i].find2(key)
}

func copyKeySliceDisk(src []BTreeKeyDisk) []BTreeKeyDisk {
	ret := make([]BTreeKeyDisk, len(src))
	copy(ret, src)
	return ret
}

func copyNodeSliceDisk(src []*BTreeNodeDisk) []*BTreeNodeDisk {
	ret := make([]*BTreeNodeDisk, len(src))
	copy(ret, src)
	return ret
}

func (node *BTreeNodeDisk) splitNode() (BTreeKeyDisk, *BTreeNodeDisk, *BTreeNodeDisk) {
	left := NewBTreeNodeDisk()
	right := NewBTreeNodeDisk()
	left.IsLeaf = node.IsLeaf
	right.IsLeaf = node.IsLeaf

	middleKeyIndex := len(node.Keys) / 2
	middleKey := node.Keys[middleKeyIndex]

	left.Keys = copyKeySliceDisk(node.Keys[:middleKeyIndex])
	right.Keys = copyKeySliceDisk(node.Keys[middleKeyIndex+1:])

	if !node.IsLeaf {
		left.Children = copyNodeSliceDisk(node.Children[:middleKeyIndex+1])
		right.Children = copyNodeSliceDisk(node.Children[middleKeyIndex+1:])
	}

	return middleKey, left, right
}

func (node *BTreeNodeDisk) insertSplitedKey(childIndex int, key BTreeKeyDisk, left *BTreeNodeDisk, right *BTreeNodeDisk) {
	tempKeysLeft := copyKeySliceDisk(node.Keys[:childIndex])
	tempKeysRight := copyKeySliceDisk(node.Keys[childIndex:])

	node.Keys = append(tempKeysLeft, key)
	node.Keys = append(node.Keys, tempKeysRight...)

	if node.IsLeaf {
		return
	}

	if childIndex == len(node.Children)-1 {
		node.Children[childIndex] = left
		node.Children = append(node.Children, right)
	} else {
		tempChildrenLeft := copyNodeSliceDisk(node.Children[:childIndex])
		tempChildrenRight := copyNodeSliceDisk(node.Children[childIndex+1:])

		node.Children = append(tempChildrenLeft, left)
		node.Children = append(node.Children, right)
		node.Children = append(node.Children, tempChildrenRight...)
	}
}

func (tree *BTreeDisk) insert2(node *BTreeNodeDisk, key BTreeKeyDisk) (BTreeKeyDisk, *BTreeNodeDisk, *BTreeNodeDisk) {
	childIndex := 0
	for ; childIndex < len(node.Keys); childIndex++ {
		if key.Compare(node.Keys[childIndex]) < 0 {
			break
		}
	}

	var splitedKey BTreeKeyDisk = nil
	var leftChild *BTreeNodeDisk = nil
	var rightChild *BTreeNodeDisk = nil

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

func (tree *BTreeDisk) overFull(n *BTreeNodeDisk) bool {
	return len(n.Keys) >= tree.Degree*2
}
