package dsa

import (
	"dsa/util"
	"fmt"
	"path/filepath"

	"github.com/google/uuid"
)

type BTreeKeyDisk interface {
	ToString() string
	Compare(k BTreeKeyDisk) int
}

type BTreeDisk struct {
	folder string
	Root   *BTreeNodeDisk
	Degree int
}

type BTreeNodeDisk struct {
	folder   string
	id       string
	IsLeaf   bool
	Keys     []BTreeKeyDisk
	Children []*BTreeNodeDisk
}

func NewBTreeDisk(degree int, folder string) *BTreeDisk {
	f := util.NewFileSerializer(folder)
	if f.FileExist() {
		fmt.Errorf("BTree %s already exists", folder)
		return nil
	}

	tree := &BTreeDisk{folder, nil, degree}
	tree.initBTreeFile()

	return tree
}

func (tree *BTreeDisk) NewBTreeNodeDisk() *BTreeNodeDisk {
	node := &BTreeNodeDisk{tree.folder, uuid.New().String(), false, make([]BTreeKeyDisk, 0), make([]*BTreeNodeDisk, 0)}
	node.initBTreeNodeFile()
	return node
}

func (tree *BTreeDisk) initBTreeFile() {
	f := util.NewFileSerializer(tree.folder)
	f.CreateDirIfNotExist()

	rootFile := filepath.Join(tree.folder, "tree")
	f = util.NewFileSerializer(rootFile)
	f.CreateFileIfNotExist()
	f.OpenForWriteTruncate()
	f.WriteInt(tree.Degree)
	f.Close()
}

func (node *BTreeNodeDisk) initBTreeNodeFile() {
	filepath.Join(node.folder, node.id)
	f := util.NewFileSerializer(filepath.Join(node.folder, node.id))
	f.CreateFileIfNotExist()
}

func (node *BTreeNodeDisk) writeToFile() {
	f := util.NewFileSerializer(filepath.Join(node.folder, node.id))

}

func (tree *BTreeDisk) Insert(key BTreeKeyDisk) {
	if tree.Root == nil {
		n := tree.NewBTreeNodeDisk()
		n.IsLeaf = true
		n.Keys = append(n.Keys, key)
		tree.Root = n
		return
	}

	splitedKey, leftChild, rightChild := tree.insert2(tree.Root, key)
	if splitedKey != nil {
		node := tree.NewBTreeNodeDisk()
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

func (tree *BTreeDisk) splitNode(node *BTreeNodeDisk) (BTreeKeyDisk, *BTreeNodeDisk, *BTreeNodeDisk) {
	left := tree.NewBTreeNodeDisk()
	right := tree.NewBTreeNodeDisk()
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
		return tree.splitNode(node)
	}
	return nil, nil, nil
}

func (tree *BTreeDisk) overFull(n *BTreeNodeDisk) bool {
	return len(n.Keys) >= tree.Degree*2
}
