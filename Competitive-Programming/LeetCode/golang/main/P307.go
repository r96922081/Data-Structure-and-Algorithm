package main


import (
	"fmt"
	"math"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

type rangeSumNode struct {
	left       int
	right      int
	sum        int
	leftChild  *rangeSumNode
	rightChild *rangeSumNode
}

type NumArray struct {
	root *rangeSumNode
}

func buildRangeSumNode(left int, right int, nums []int) *rangeSumNode {
	if left > len(nums)-1 {
		return nil
	}

	if left == right {
		return &rangeSumNode{left, left, nums[left], nil, nil}
	}

	maxRight := right
	if maxRight > len(nums)-1 {
		maxRight = len(nums) - 1
	}
	node := &rangeSumNode{left, maxRight, 0, nil, nil}

	mid := (left + right) / 2

	node.leftChild = buildRangeSumNode(left, mid, nums)
	node.rightChild = buildRangeSumNode(mid+1, right, nums)
	node.sum = node.leftChild.sum
	if node.rightChild != nil {
		node.sum += node.rightChild.sum
	}

	return node
}

func Constructor(nums []int) NumArray {
	maxRight := int(math.Pow(2, math.Ceil(math.Log2(float64(len(nums)+1))))) - 1
	numArray := NumArray{}
	numArray.root = buildRangeSumNode(0, maxRight, nums)
	return numArray
}

func (this *rangeSumNode) Update2(i int, val int) int {
	if i == this.left && this.left == this.right {
		ret := val - this.sum
		this.sum = val
		return ret
	}

	ret := 0
	if i <= this.leftChild.right {
		ret = this.leftChild.Update2(i, val)
	} else {
		ret = this.rightChild.Update2(i, val)
	}

	this.sum += ret
	return ret
}

func (this *NumArray) Update(i int, val int) {
	this.root.Update2(i, val)
}

func (this *rangeSumNode) sumRange2(i int, j int) int {
	if i == this.left && j == this.right {
		return this.sum
	}

	if this.rightChild != nil && i >= this.rightChild.left {
		return this.rightChild.sumRange2(i, j)
	} else if j <= this.leftChild.right {
		return this.leftChild.sumRange2(i, j)
	}

	return this.leftChild.sumRange2(i, this.leftChild.right) +
		this.rightChild.sumRange2(this.rightChild.left, j)
}

func (this *NumArray) SumRange(i int, j int) int {
	return this.root.sumRange2(i, j)
}

func main() {
	for nodeCount := 1; nodeCount <= 16; nodeCount++ {
		nums := make([]int, 0)
		for i := 0; i < nodeCount; i++ {
			nums = append(nums, i)
		}

		numArray := Constructor(nums)
		for sumLen := 1; sumLen <= nodeCount; sumLen++ {
			for startIndex := 0; startIndex+sumLen <= nodeCount; startIndex++ {
				answer := 0
				for j := startIndex; j < startIndex+sumLen; j++ {
					answer += j
				}

				check(numArray.SumRange(startIndex, startIndex+sumLen-1) == answer)
			}
		}

		for i := 0; i < nodeCount; i++ {
			numArray.Update(i, i+1)
		}

		for sumLen := 1; sumLen <= nodeCount; sumLen++ {
			for startIndex := 0; startIndex+sumLen <= nodeCount; startIndex++ {
				answer := sumLen
				for j := startIndex; j < startIndex+sumLen; j++ {
					answer += j
				}

				check(numArray.SumRange(startIndex, startIndex+sumLen-1) == answer)
			}
		}
	}
}
