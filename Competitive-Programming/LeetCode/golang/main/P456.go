package main


import (
	"container/list"
	"fmt"
	"math"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

const (
	dirUp   = iota
	dirDown = iota
)

type segStruct struct {
	max int
	min int
}

func checkIfInRange(segList *list.List, n int, dir int) bool {
	if dir == dirUp {
		for ptr := segList.Back(); ptr != nil; {
			seg := ptr.Value.(*segStruct)
			if n < seg.min {
				ptr = ptr.Prev()
				continue
			} else if n > seg.min {
				if n < seg.max {
					return true
				}
				removed := ptr
				ptr = ptr.Prev()
				segList.Remove(removed)
			} else {
				ptr = ptr.Prev()
				continue
			}
		}
		return false
	} else {
		seg := segList.Back().Value.(*segStruct)
		if n > seg.min && n < seg.max {
			return true
		}
		return false
	}
}

func find132pattern(nums []int) bool {
	prev := math.MaxInt32
	prevDir := dirDown
	segMin := 0
	segList := list.New()

	for _, n := range nums {
		if n > prev {
			if prevDir == dirDown {
				segMin = prev
				prevDir = dirUp
			}
			if checkIfInRange(segList, n, dirUp) {
				return true
			}
		} else if n < prev {
			if prevDir == dirUp {
				segList.PushBack(&segStruct{prev, segMin})
				if checkIfInRange(segList, n, dirDown) {
					return true
				}
				prevDir = dirDown
			}
		}
		prev = n
	}

	return false
}

func main() {
	check(find132pattern([]int{1, 2, 3, 4}) == false)
	check(find132pattern([]int{3, 1, 4, 2}) == true)
	check(find132pattern([]int{-1, 3, 2, 0}) == true)
	check(find132pattern([]int{20, 15, 10, 25, 5}) == false)
	check(find132pattern([]int{6, 10, 25, 5}) == false)
	check(find132pattern([]int{20, 10, 5, 25, 15}) == true)
	check(find132pattern([]int{20, 10, 5, 25, 15}) == true)
	check(find132pattern([]int{35, 30, 25, 20, 10, 5, 15}) == false)
}
