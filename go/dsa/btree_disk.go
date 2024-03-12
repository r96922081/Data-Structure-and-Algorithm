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
	WriteToFile(f *util.FileSerializer)
	ReadFromFile(f *util.FileSerializer) BTreeKeyDisk
}

type BTreeDisk struct {
	Folder string
	Root   *BTreeNodeDisk
	RootId string
	Degree int

	dummyKey BTreeKeyDisk
}

type BTreeNodeDisk struct {
	Folder   string
	Id       string
	IsLeaf   bool
	Keys     []BTreeKeyDisk
	Children []*BTreeNodeDisk
}

func NewBTreeDisk(degree int, folder string, dummyKey BTreeKeyDisk) *BTreeDisk {
	f := util.NewFileSerializer(folder)
	if f.FileExist() {
		fmt.Errorf("BTree %s already exists", folder)
		return nil
	}

	tree := &BTreeDisk{folder, nil, "", degree, dummyKey}
	tree.writeFile()

	return tree
}

func ReadBTreeFromFile(folder string, dummyKey BTreeKeyDisk) *BTreeDisk {
	rootFile := filepath.Join(folder, "tree")
	f := util.NewFileSerializer(rootFile)
	f.OpenForRead()
	degree, _ := f.ReadInt()
	rootId, _ := f.ReadString()
	f.Close()

	var root *BTreeNodeDisk = nil
	tree := &BTreeDisk{folder, root, rootId, degree, dummyKey}

	if rootId != "" {
		tree.Root = tree.ReadBTreeNodeFromFile(folder, rootId)
	}

	f.Close()

	return tree
}

func (tree *BTreeDisk) Insert(key BTreeKeyDisk) {
	if tree.Root == nil {
		n := tree.newBTreeNodeDisk()
		n.IsLeaf = true
		n.Keys = append(n.Keys, key)
		tree.Root = n
		tree.RootId = n.Id
		n.writeFile()
		tree.writeFile()
		return
	}

	splitedKey, leftChild, rightChild := tree.insert2(tree.Root, key)
	if splitedKey != nil {
		node := tree.newBTreeNodeDisk()
		node.Keys = append(node.Keys, splitedKey)

		node.Children = append(node.Children, leftChild)
		node.Children = append(node.Children, rightChild)

		tree.Root = node
		tree.RootId = node.Id
		node.writeFile()
		tree.writeFile()
	}
}

func (tree *BTreeDisk) Find(key BTreeKeyDisk) []BTreeKeyDisk {
	ret := make([]BTreeKeyDisk, 0)

	if tree.Root == nil {
		return ret
	}
	tree.find2(tree.Root, key, &ret)
	return ret
}

func ___PublicFuncSeparator___() {}

func (tree *BTreeDisk) newBTreeNodeDisk() *BTreeNodeDisk {
	node := &BTreeNodeDisk{tree.Folder, uuid.New().String(), false, make([]BTreeKeyDisk, 0), make([]*BTreeNodeDisk, 0)}
	node.initBTreeNodeFile()
	return node
}

func (tree *BTreeDisk) writeFile() {
	f := util.NewFileSerializer(tree.Folder)
	f.CreateDirIfNotExist()

	rootFile := filepath.Join(tree.Folder, "tree")
	f = util.NewFileSerializer(rootFile)
	f.CreateFileIfNotExist()
	f.OpenForWriteTruncate()
	f.WriteInt(tree.Degree)
	f.WriteString(tree.RootId)
	f.Close()
}

func (tree *BTreeDisk) ReadBTreeNodeFromFile(folder string, id string) *BTreeNodeDisk {
	f := util.NewFileSerializer(filepath.Join(folder, id))
	f.OpenForRead()

	node := &BTreeNodeDisk{"", "", false, make([]BTreeKeyDisk, 0), make([]*BTreeNodeDisk, 0)}

	node.Folder, _ = f.ReadString()
	node.Id, _ = f.ReadString()
	isLeaf, _ := f.ReadInt()
	if isLeaf == 1 {
		node.IsLeaf = true
	} else {
		node.IsLeaf = false
	}

	count, _ := f.ReadInt()
	for i := 0; i < count; i++ {
		node.Keys = append(node.Keys, tree.dummyKey.ReadFromFile(f))
	}

	count, _ = f.ReadInt()
	for i := 0; i < count; i++ {
		node2 := &BTreeNodeDisk{"", "", false, make([]BTreeKeyDisk, 0), make([]*BTreeNodeDisk, 0)}
		node2.Folder, _ = f.ReadString()
		node2.Id, _ = f.ReadString()
		node.Children = append(node.Children, node2)
	}

	f.Close()

	return node
}

func (node *BTreeNodeDisk) removeFile() {
	filepath.Join(node.Folder, node.Id)
	f := util.NewFileSerializer(filepath.Join(node.Folder, node.Id))
	f.DeleteFileIfExist()
}

func (node *BTreeNodeDisk) initBTreeNodeFile() {
	filepath.Join(node.Folder, node.Id)
	f := util.NewFileSerializer(filepath.Join(node.Folder, node.Id))
	f.CreateFileIfNotExist()
}

func (node *BTreeNodeDisk) writeFile() {
	f := util.NewFileSerializer(filepath.Join(node.Folder, node.Id))
	f.OpenForWriteTruncate()

	f.WriteString(node.Folder)
	f.WriteString(node.Id)
	if node.IsLeaf {
		f.WriteInt(1)
	} else {
		f.WriteInt(0)
	}
	f.WriteInt(len(node.Keys))
	for _, k := range node.Keys {
		k.WriteToFile(f)
	}
	f.WriteInt(len(node.Children))
	for _, c := range node.Children {
		f.WriteString(c.Folder)
		f.WriteString(c.Id)
	}
	f.Close()
}

func (tree *BTreeDisk) find2(node *BTreeNodeDisk, key BTreeKeyDisk, ret *[]BTreeKeyDisk) {
	node = tree.ReadBTreeNodeFromFile(node.Folder, node.Id)

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
			tree.find2(node.Children[child], key, ret)
		}
	}
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
	left := tree.newBTreeNodeDisk()
	right := tree.newBTreeNodeDisk()
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

	left.writeFile()
	right.writeFile()
	node.removeFile()

	return middleKey, left, right
}

func (node *BTreeNodeDisk) insertSplitedKey(childIndex int, key BTreeKeyDisk, left *BTreeNodeDisk, right *BTreeNodeDisk) {
	tempKeysLeft := copyKeySliceDisk(node.Keys[:childIndex])
	tempKeysRight := copyKeySliceDisk(node.Keys[childIndex:])

	node.Keys = append(tempKeysLeft, key)
	node.Keys = append(node.Keys, tempKeysRight...)

	defer node.writeFile()

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

	if tree.overSize(node) {
		return tree.splitNode(node)
	}
	return nil, nil, nil
}

func (tree *BTreeDisk) overSize(n *BTreeNodeDisk) bool {
	return len(n.Keys) >= tree.Degree*2
}
