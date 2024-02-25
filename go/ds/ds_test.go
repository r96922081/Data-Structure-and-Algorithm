package ds

import (
	"dsa/algutil"
	"dsa/ds/priorityqueue"
	"dsa/ds/tree"
	"math"
	"math/rand"
	"sort"
	"testing"
	"time"
)

func TestPriorityQueue(t *testing.T) {
	seed := time.Now().Unix()
	//fmt.Print("Seed = ", seed, "\n")
	rand.Seed(seed)

	biggerThanFunc := func(v1 interface{}, v2 interface{}) bool {
		return v1.(int) > v2.(int)
	}

	for i := 0; i < 20; i++ {
		q := priorityqueue.New(biggerThanFunc)
		for size := 1; size < 30; size++ {
			q.Insert(rand.Int() % 30)
		}

		prev := 1000
		for !q.Empty() {
			e := q.ExtractMax()
			algutil.AssertTrue(t, prev >= e.(int))
			prev = e.(int)
		}
	}
}

func TestBinaryTree(t *testing.T) {
	algutil.AssertTrue(t, true)
}

func countNode(node *tree.BinaryTreeNode) int {
	if node == nil {
		return 0
	}

	count := countNode(node.Left)
	count++
	count += countNode(node.Right)

	return count
}

func TestBST_Min_Max_Search_Predecessor_Successor(t *testing.T) {
	seed := time.Now().Unix()
	//fmt.Print("Seed = ", seed, "\n")
	rand.Seed(seed)

	biggerThanFunc := func(v1 interface{}, v2 interface{}) bool {
		return v1.(int) > v2.(int)
	}

	for i := 0; i < 10; i++ {
		minKey := math.MaxInt32
		maxKey := math.MinInt32

		size := 10
		bst := tree.NewBinarySearchTree(biggerThanFunc)
		keyRange := size * 3
		all := make([]int, 0)

		for j := 1; j <= size; j++ {
			existed := true
			key := 0
			for existed {
				key = rand.Int() % (keyRange)
				left := 0
				right := len(all) - 1

				// practice binary search
				for left <= right {
					mid := (left + right) / 2
					midKey := all[mid]
					if midKey == key {
						break
					} else if key < midKey {
						right = mid - 1
					} else {
						left = mid + 1
					}
				}
				if left > right {
					existed = false
				}
			}

			all = append(all, key)
			k := len(all) - 1

			// practice insertion sort
			for ; k > 0; k-- {
				if key > all[k-1] {
					break
				}
				all[k] = all[k-1]
			}
			all[k] = key

			bst.Insert(key)
			if key < minKey {
				minKey = key
			}
			if key > maxKey {
				maxKey = key
			}
		}

		algutil.AssertTrue(t, maxKey == bst.Max().(int))
		algutil.AssertTrue(t, minKey == bst.Min().(int))

		for k := 0; k < keyRange; k++ {
			ret := sort.SearchInts(all, k)
			existed := ret < len(all) && all[ret] == k
			if existed {
				algutil.AssertTrue(t, bst.Search(k) != nil)
			} else {
				algutil.AssertTrue(t, bst.Search(k) == nil)
			}
		}

		algutil.AssertTrue(t, bst.Predecessor(all[0]) == nil)
		algutil.AssertTrue(t, bst.Successor(all[len(all)-1]) == nil)

		for k := 1; k < len(all); k++ {
			algutil.AssertTrue(t, bst.Predecessor(all[k]) == all[k-1])
		}

		for k := 0; k < len(all)-1; k++ {
			algutil.AssertTrue(t, bst.Successor(all[k]) == all[k+1])
		}
	}
}

func checkBstProperty(t *testing.T, node *tree.BinaryTreeNode, prevValue int, leftMostChecked *bool) int {
	if node == nil {
		return prevValue
	}

	prevValue = checkBstProperty(t, node.Left, prevValue, leftMostChecked)
	if *leftMostChecked == false {
		*leftMostChecked = true
	} else {
		algutil.AssertTrue(t, prevValue <= node.Value.(int))
	}

	prevValue = node.Value.(int)
	return checkBstProperty(t, node.Right, prevValue, leftMostChecked)
}

func TestBSTInsert(t *testing.T) {
	biggerThanFunc := func(v1 interface{}, v2 interface{}) bool {
		return v1.(int) > v2.(int)
	}

	for i := 0; i < 20; i++ {
		for size := 1; size < 10; size++ {
			bst := tree.NewBinarySearchTree(biggerThanFunc)
			for j := 1; j <= size; j++ {
				bst.Insert(rand.Int() % 10)
			}
			leftMostChecked := false
			checkBstProperty(t, bst.Root, 0, &leftMostChecked)
		}
	}
}

func TestBSTDelete(t *testing.T) {
	algutil.SetSeedTo1()
	biggerThanFunc := func(v1 interface{}, v2 interface{}) bool {
		return v1.(int) > v2.(int)
	}

	for i := 0; i < 100; i++ {
		for size := 1; size < 100; size++ {
			bst := tree.NewBinarySearchTree(biggerThanFunc)
			all := make([]int, size)

			for j := 1; j <= size; j++ {
				key := rand.Int() % 10
				bst.Insert(key)
				all[j-1] = key
			}

			for len(all) > 0 {
				idx := rand.Int() % len(all)
				bst.Delete(all[idx])
				leftMostChecked := false
				checkBstProperty(t, bst.Root, 0, &leftMostChecked)

				all = append(all[:idx], all[idx+1:]...)

				algutil.AssertTrue(t, countNode(bst.Root) == len(all))
			}
		}
	}
}
