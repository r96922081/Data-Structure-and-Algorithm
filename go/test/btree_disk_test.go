package test

import (
	"dsa/dsa"
	"dsa/util"
	"fmt"
	"math/rand"
	"strconv"
	"testing"
)

type MyKeyDisk struct {
	key     int
	content string
}

func (n1 MyKeyDisk) Compare(k dsa.BTreeKeyDisk) int {
	n2 := k.(MyKeyDisk)
	if n1.key < n2.key {
		return -1
	} else if n1.key == n2.key {
		return 0
	} else {
		return 1
	}
}

func (k MyKeyDisk) WriteToFile(f *util.FileSerializer) {
	f.WriteInt(k.key)
	f.WriteString(k.content)
}

func (k MyKeyDisk) ReadFromFile(f *util.FileSerializer) dsa.BTreeKeyDisk {
	key := MyKeyDisk{}
	key.key, _ = f.ReadInt()
	key.content, _ = f.ReadString()
	return key
}

func (n MyKeyDisk) ToString() string {
	return "" + strconv.Itoa(n.key) + "(" + n.content + ")"
}

//  1. Every node x has the following attributes:
//     x.key1 <= x.key2 <= … <= x.keyn
//  2. If ki is “any” key stored in x.ci, then k1 <= x.key1 <= k2 <= … <= x.key(x.n) <= k(x.n + 1)
func checkPropertyValueInOrderDisk(t *testing.T, tree *dsa.BTreeDisk) {
	keys := traverseDisk(tree)
	for i := 0; i < len(keys)-1; i++ {
		AssertTrue(t, keys[i].Compare(keys[i+1]) <= 0)
	}
}

// Every node other than root: t - 1 <= # of keys
// Every node: # of keys <= 2t - 1
func checkDegreeDisk(t *testing.T, tree *dsa.BTreeDisk, node *dsa.BTreeNodeDisk) {
	if node != tree.Root {
		AssertTrue(t, tree.Degree-1 <= len(node.Keys))
	}

	AssertTrue(t, len(node.Keys) <= tree.Degree*2-1)

	if !node.IsLeaf {
		for _, child := range node.Children {
			loadedChild := tree.ReadBTreeNodeFromFile(child.Folder, child.Id)
			checkDegreeDisk(t, tree, loadedChild)
		}
	}
}

func checkLeafDepth2Disk(t *testing.T, tree *dsa.BTreeDisk, node *dsa.BTreeNodeDisk, depth int, leafDepth int) {
	if node.IsLeaf {
		AssertTrue(t, depth == leafDepth)
	} else {
		AssertTrue(t, depth < leafDepth)
		for _, child := range node.Children {
			loadedChild := tree.ReadBTreeNodeFromFile(child.Folder, child.Id)
			checkLeafDepth2Disk(t, tree, loadedChild, depth+1, leafDepth)
		}
	}
}

// All leaves have the same depth
func checkLeafDepthDisk(t *testing.T, tree *dsa.BTreeDisk) {
	leafDepth := 0

	node := tree.Root

	for len(node.Children) != 0 {
		node = tree.ReadBTreeNodeFromFile(node.Children[0].Folder, node.Children[0].Id)
		leafDepth++
	}

	checkLeafDepth2Disk(t, tree, tree.Root, 0, leafDepth)
}

func checkBTreePropertiesDisk(t *testing.T, tree *dsa.BTreeDisk) {
	checkPropertyValueInOrderDisk(t, tree)
	checkDegreeDisk(t, tree, tree.Root)
	checkLeafDepthDisk(t, tree)
}

func getPrintedTreeDisk(tree *dsa.BTreeDisk) string {
	return getPrintedTree2Disk(tree, tree.Root)
}

func getPrintedTree2Disk(tree *dsa.BTreeDisk, node *dsa.BTreeNodeDisk) string {
	ret := ""
	nodes := make([]*dsa.BTreeNodeDisk, 0)
	levels := make([]int, 0)
	nodes = append(nodes, node)
	levels = append(levels, 0)

	currentLevel := 0

	for len(nodes) != 0 {
		node := nodes[0]
		nodes = nodes[1:]

		level := levels[0]
		levels = levels[1:]

		if currentLevel != level {
			ret += "\n"
			currentLevel += 1
		}

		ret += "["
		for i := 0; i < len(node.Keys); i++ {
			if i != 0 {
				ret += ", "
			}
			ret += node.Keys[i].ToString()
		}
		ret += "]"

		if !node.IsLeaf {
			for _, child := range node.Children {
				loadedChild := tree.ReadBTreeNodeFromFile(child.Folder, child.Id)
				nodes = append(nodes, loadedChild)
				levels = append(levels, currentLevel+1)
			}
		}
	}

	return ret
}

func TestBTreeDiskInsertDisk(t *testing.T) {
	rand.Seed(0)

	util.NewFileSerializer("btree_test_folder").DeleteFileIfExist()
	for degree := 2; degree < 4; degree++ {
		tree := dsa.NewBTreeDisk(degree, "btree_test_folder", MyKeyDisk{})
		for count := 0; count < 30; count++ {
			for i := 0; i < count; i++ {
				tree.Insert(MyKeyDisk{rand.Intn(10), ""})
				//fmt.Println(getPrintedTreeDisk(tree))
				//fmt.Println("=============")
				checkBTreePropertiesDisk(t, tree)
			}
		}
		util.NewFileSerializer("btree_test_folder").DeleteFileIfExist()
	}
}

func TestBTreeDiskFindDisk(t *testing.T) {
	util.NewFileSerializer("btree_test_folder").DeleteFileIfExist()

	tree := dsa.NewBTreeDisk(2, "btree_test_folder", MyKeyDisk{})
	for i := 0; i < 100; i++ {
		if i%2 == 0 {
			tree.Insert(MyKeyDisk{i, ""})
			tree.Insert(MyKeyDisk{i, ""})
		}
	}

	for i := 0; i < 100; i++ {
		if i%2 == 0 {
			AssertTrue(t, tree.Find(MyKeyDisk{i, ""}) != nil)
		} else {
			AssertTrue(t, tree.Find(MyKeyDisk{i, ""}) == nil)
		}
	}

	util.NewFileSerializer("btree_test_folder").DeleteFileIfExist()
}

func traverseDisk(tree *dsa.BTreeDisk) []dsa.BTreeKeyDisk {
	keys := make([]dsa.BTreeKeyDisk, 0)
	if tree.Root == nil {
		return keys
	}

	traverse2Disk(tree, tree.Root, &keys)
	return keys
}

func traverse2Disk(tree *dsa.BTreeDisk, node *dsa.BTreeNodeDisk, keys *[]dsa.BTreeKeyDisk) {
	i := 0
	for ; i < len(node.Keys); i++ {
		if !node.IsLeaf {
			child := tree.ReadBTreeNodeFromFile(node.Children[i].Folder, node.Children[i].Id)
			traverse2Disk(tree, child, keys)
		}
		*keys = append(*keys, node.Keys[i])
	}
	if !node.IsLeaf {
		child := tree.ReadBTreeNodeFromFile(node.Children[i].Folder, node.Children[i].Id)
		traverse2Disk(tree, child, keys)
	}
}

func TestBTreeIO_1(t *testing.T) {
	folder := "btree_test_folder"
	util.NewFileSerializer(folder).DeleteFileIfExist()

	_ = dsa.NewBTreeDisk(2, folder, MyKeyDisk{})

	tree := dsa.ReadBTreeFromFile(folder, MyKeyDisk{})
	AssertTrue(t, tree.RootId == "")
	AssertTrue(t, tree.Degree == 2)

	util.NewFileSerializer(folder).DeleteFileIfExist()
}

func TestBTreeIO_2(t *testing.T) {
	folder := "btree_test_folder"
	util.NewFileSerializer(folder).DeleteFileIfExist()

	tree := dsa.NewBTreeDisk(2, folder, MyKeyDisk{})
	tree.Insert(MyKeyDisk{1, ""})

	tree = dsa.ReadBTreeFromFile(folder, MyKeyDisk{})
	checkBTreePropertiesDisk(t, tree)
	AssertTrue(t, tree.Root.IsLeaf == true)
	fmt.Println(tree.Root.Keys[0].ToString())

	util.NewFileSerializer(folder).DeleteFileIfExist()
}

func TestBTreeIO_3(t *testing.T) {
	folder := "btree_test_folder"
	util.NewFileSerializer(folder).DeleteFileIfExist()

	tree := dsa.NewBTreeDisk(2, folder, MyKeyDisk{})
	for i := 0; i < 4; i++ {
		tree.Insert(MyKeyDisk{i, ""})
	}

	AssertTrue(t, tree.Find(MyKeyDisk{3, ""}) != nil)
	AssertTrue(t, tree.Find(MyKeyDisk{-1, ""}) == nil)

	tree = dsa.ReadBTreeFromFile(folder, MyKeyDisk{})
	checkBTreePropertiesDisk(t, tree)
	keys := traverseDisk(tree)

	for _, key := range keys {
		fmt.Print(key.ToString())
	}
	fmt.Println()

	fmt.Println(getPrintedTreeDisk(tree))
	fmt.Println("===============")

	util.NewFileSerializer(folder).DeleteFileIfExist()
}

func TestBTreeIO_4(t *testing.T) {
	folder := "btree_test_folder"
	util.NewFileSerializer(folder).DeleteFileIfExist()

	tree := dsa.NewBTreeDisk(2, folder, MyKeyDisk{})
	for i := 0; i < 50; i++ {
		tree.Insert(MyKeyDisk{i, ""})
	}

	AssertTrue(t, tree.Find(MyKeyDisk{3, ""}) != nil)
	AssertTrue(t, tree.Find(MyKeyDisk{-1, ""}) == nil)

	tree = dsa.ReadBTreeFromFile(folder, MyKeyDisk{})
	checkBTreePropertiesDisk(t, tree)

	keys := traverseDisk(tree)
	for _, key := range keys {
		fmt.Print(key.ToString())
	}
	fmt.Println()

	fmt.Println(getPrintedTreeDisk(tree))
	fmt.Println("===============")

	util.NewFileSerializer(folder).DeleteFileIfExist()
}
