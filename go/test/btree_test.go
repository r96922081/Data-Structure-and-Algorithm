package test

import (
	"dsa/dsa"
	"fmt"
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
	keys := tree.Traverse()
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

func TestBTree(t *testing.T) {
	rand.Seed(0)

	tree := dsa.NewBTree(2)

	for i := 0; i < 12; i++ {
		tree.Insert(&MyKey{rand.Intn(100), ""})
		//fmt.Println(tree.PrintTree())
		//tree.Insert(&MyKey{0, ""})
		checkBTreeProperties(t, tree)
	}

	keys := tree.Traverse()
	for i := 0; i < len(keys); i++ {
		fmt.Printf(keys[i].ToString() + ", ")
	}
	fmt.Println()

	fmt.Println(tree.PrintTree())

	checkBTreeProperties(t, tree)
}
