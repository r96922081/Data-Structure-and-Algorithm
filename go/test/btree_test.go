package test

import (
	"dsa/dsa"
	"math/rand"
	"strconv"
	"testing"
)

type MyKey struct {
	key     int
	content string
}

func (n1 *MyKey) Compare(k dsa.BTreeKey) int {
	n2 := k.(*MyKey)
	if n1.key < n2.key {
		return -1
	} else if n1.key == n2.key {
		return 0
	} else {
		return 1
	}
}

func (n *MyKey) ToString() string {
	return "" + strconv.Itoa(n.key) + "(" + n.content + ")"
}

//  1. Every node x has the following attributes:
//     x.key1 <= x.key2 <= … <= x.keyn
//  2. If ki is “any” key stored in x.ci, then k1 <= x.key1 <= k2 <= … <= x.key(x.n) <= k(x.n + 1)
func checkPropertyValueInOrder(t *testing.T, tree *dsa.BTree) {
	keys := traverse(tree)
	for i := 0; i < len(keys)-1; i++ {
		AssertTrue(t, keys[i].Compare(keys[i+1]) <= 0)
	}
}

// Every node other than root: t - 1 <= # of keys
// Every node: # of keys <= 2t - 1
func checkDegree(t *testing.T, tree *dsa.BTree, node *dsa.BTreeNode) {
	if node != tree.Root {
		AssertTrue(t, tree.Degree-1 <= len(node.Keys))
	}

	AssertTrue(t, len(node.Keys) <= tree.Degree*2-1)

	if !node.IsLeaf {
		for _, child := range node.Children {
			checkDegree(t, tree, child)
		}
	}
}

func checkLeafDepth2(t *testing.T, tree *dsa.BTree, node *dsa.BTreeNode, depth int, leafDepth int) {
	if node.IsLeaf {
		AssertTrue(t, depth == leafDepth)
	} else {
		AssertTrue(t, depth < leafDepth)
		for _, child := range node.Children {
			checkLeafDepth2(t, tree, child, depth+1, leafDepth)
		}
	}
}

// All leaves have the same depth
func checkLeafDepth(t *testing.T, tree *dsa.BTree) {
	leafDepth := 0

	node := tree.Root

	for len(node.Children) != 0 {
		node = node.Children[0]
		leafDepth++
	}

	checkLeafDepth2(t, tree, tree.Root, 0, leafDepth)
}

func checkBTreeProperties(t *testing.T, tree *dsa.BTree) {
	checkPropertyValueInOrder(t, tree)
	checkDegree(t, tree, tree.Root)
	checkLeafDepth(t, tree)
}

func getPrintedTree(tree *dsa.BTree) string {
	return getPrintedTree2(tree, tree.Root)
}

func getPrintedTree2(tree *dsa.BTree, node *dsa.BTreeNode) string {
	ret := ""
	nodes := make([]*dsa.BTreeNode, 0)
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
				nodes = append(nodes, child)
				levels = append(levels, currentLevel+1)
			}
		}
	}

	return ret
}

func traverse(tree *dsa.BTree) []dsa.BTreeKey {
	keys := make([]dsa.BTreeKey, 0)
	if tree.Root == nil {
		return keys
	}

	traverse2(tree.Root, &keys)
	return keys
}

func traverse2(node *dsa.BTreeNode, keys *[]dsa.BTreeKey) {
	i := 0
	for ; i < len(node.Keys); i++ {
		if !node.IsLeaf {
			traverse2(node.Children[i], keys)
		}
		*keys = append(*keys, node.Keys[i])
	}
	if !node.IsLeaf {
		traverse2(node.Children[i], keys)
	}
}

func TestBTreeInsert(t *testing.T) {
	rand.Seed(0)

	for degree := 2; degree < 4; degree++ {
		tree := dsa.NewBTree(degree)
		for count := 0; count < 15; count++ {
			for i := 0; i < count; i++ {
				tree.Insert(&MyKey{rand.Intn(10), ""})
				//fmt.Println(getPrintedTree(tree))
				//fmt.Println("=============")
				checkBTreeProperties(t, tree)
			}
		}
	}
}

func TestBTreeFind(t *testing.T) {
	tree := dsa.NewBTree(2)
	for i := 0; i < 100; i++ {
		if i%2 == 0 {
			tree.Insert(&MyKey{i, ""})
			tree.Insert(&MyKey{i, ""})
		}
	}

	for i := 0; i < 100; i++ {
		if i%2 == 0 {
			AssertTrue(t, tree.Find(&MyKey{i, ""}) != nil)
		} else {
			AssertTrue(t, tree.Find(&MyKey{i, ""}) == nil)
		}
	}
}
