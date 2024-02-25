package dsa

import (
	"container/list"
	"math"
)

func InsertionSort(a []int) {
	for i := 1; i < len(a); i++ {
		j := i
		key := a[j]
		for ; j > 0 && key < a[j-1]; j-- {
			a[j] = a[j-1]
		}
		a[j] = key
	}
}

func BubbleSort(a []int) {
	for i := 0; i < len(a); i++ {
		for j := 0; j < len(a)-i-1; j++ {
			if a[j] > a[j+1] {
				a[j], a[j+1] = a[j+1], a[j]
			}
		}
	}
}

func merge(src []int, dest []int, left int, mid int, right int) {
	leftIndex := left
	rightIndex := mid + 1
	destIndex := left

	for leftIndex <= mid || rightIndex <= right {
		choice := 0 // 0 left, 1 right

		if leftIndex > mid {
			choice = 1
		} else if rightIndex > right {
			choice = 0
		} else {
			if src[leftIndex] <= src[rightIndex] {
				choice = 0
			} else {
				choice = 1
			}
		}

		if choice == 0 {
			dest[destIndex] = src[leftIndex]
			leftIndex++
		} else {
			dest[destIndex] = src[rightIndex]
			rightIndex++
		}

		destIndex++
	}
}

func MergeSort(a0 []int) {
	a1 := make([]int, len(a0))
	copy(a1, a0)
	i := 1

	for ; int(math.Pow(2, float64(i-1))) < len(a0); i++ {
		size := int(math.Pow(2, float64(i)))
		for j := 0; j < len(a0); j += size {
			left := j
			mid := j + size/2 - 1

			if mid >= len(a0) {
				mid = len(a0) - 1
			}

			right := mid + size/2
			if right >= len(a0) {
				right = len(a0) - 1
			}

			if i%2 == 1 {
				merge(a0, a1, left, mid, right)
			} else {
				merge(a1, a0, left, mid, right)
			}
		}
	}

	if i%2 == 0 {
		copy(a0, a1)
	}

}

func quickSort2(a []int, leftOriginal int, rightOriginal int) {
	if leftOriginal >= rightOriginal {
		return
	}

	left := leftOriginal + 1
	right := rightOriginal
	pivot := a[leftOriginal]

	for left <= right {
		if pivot <= a[right] {
			right--
		} else {
			a[left], a[right] = a[right], a[left]
			left++
		}
	}

	a[leftOriginal], a[right] = a[right], a[leftOriginal]
	quickSort2(a, leftOriginal, right-1)
	quickSort2(a, right+1, rightOriginal)
}

func QuickSort(a []int) {
	quickSort2(a, 0, len(a)-1)
}

func RadixSort(a []int) {
	positiveA := make([]int, len(a))
	pIndex := 0
	negativeA := make([]int, len(a))
	nIndex := 0

	for _, v := range a {
		if v >= 0 {
			positiveA[pIndex] = v
			pIndex++
		} else {
			negativeA[nIndex] = -v
			nIndex++
		}
	}

	positiveA = positiveA[:pIndex]
	negativeA = negativeA[:nIndex]

	radixSort2(positiveA)
	radixSort2(negativeA)

	aIndex := 0
	for i := len(negativeA) - 1; i >= 0; i-- {
		a[aIndex] = -negativeA[i]
		aIndex++
	}

	for i := 0; i < len(positiveA); i++ {
		a[aIndex] = positiveA[i]
		aIndex++
	}
}

func radixSort2(a []int) {
	var list0 [2]*list.List
	var list1 [2]*list.List

	list0[0] = list.New()
	list0[1] = list.New()

	for _, v := range a {
		list0[0].PushBack(v)
	}

	var srcList *[2]*list.List
	var destList *[2]*list.List

	i := 0
	for ; ; i++ {
		bitCompare := int(math.Pow(2, float64(i)))
		bitCompareIsMax := true
		if i%2 == 0 {
			srcList = &list0
			destList = &list1
		} else {
			srcList = &list1
			destList = &list0
		}

		(*destList)[0] = list.New()
		(*destList)[1] = list.New()

		var currentList *list.List

		for j := 0; j < 2; j++ {
			currentList = (*srcList)[j]
			for e := currentList.Front(); e != nil; e = e.Next() {
				v := e.Value.(int)
				if v > bitCompare {
					bitCompareIsMax = false
				}
				if v&bitCompare == 0 {
					(*destList)[0].PushBack(v)
				} else {
					(*destList)[1].PushBack(v)
				}
			}
		}

		if bitCompareIsMax {
			break
		}
	}

	var answerList *[2]*list.List
	if i%2 == 0 {
		answerList = &list1
	} else {
		answerList = &list0
	}

	aIndex := 0
	for i := 0; i < 2; i++ {
		currentList := (*answerList)[i]
		for e := currentList.Front(); e != nil; e = e.Next() {
			v := e.Value.(int)
			a[aIndex] = v
			aIndex++
		}
	}
}

func CountingSort(a []int) []int {
	minN := int((^uint(0)) >> 1)
	maxN := -minN

	for _, v := range a {
		maxN = int(math.Max(float64(v), float64(maxN)))
		minN = int(math.Min(float64(v), float64(minN)))
	}

	order := make([]int, len(a))
	a2 := make([]int, len(a))
	count := make([]int, maxN-minN+1)
	offset := -minN

	copy(a2, a)

	for _, v := range a {
		count[v+offset]++
	}

	for i := 1; i < len(count); i++ {
		count[i] += count[i-1]
	}

	for i := len(a) - 1; i >= 0; i-- {
		v := a2[i]
		theOrder := count[v+offset] - 1
		count[v+offset]--
		order[i] = theOrder
		a[theOrder] = v
	}

	return order
}

func heapLeft(i int) int {
	return (i+1)*2 - 1
}

func heapRight(i int) int {
	return heapLeft(i) + 1
}

func heapify(a []int, i int) {
	lastIndex := len(a) - 1
	l := heapLeft(i)
	r := heapRight(i)
	maxValue := a[i]
	maxIndex := i

	if l <= lastIndex && maxValue < a[l] {
		maxIndex = l
		maxValue = a[l]
	}

	if r <= lastIndex && maxValue < a[r] {
		maxIndex = r
		maxValue = a[r]
	}

	if maxIndex != i {
		a[maxIndex] = a[i]
		a[i] = maxValue
		heapify(a, maxIndex)
	}
}

func HeapSort(a []int) {
	// build heap
	for i := len(a) / 2; i >= 0; i-- {
		heapify(a, i)
	}

	for i := len(a) - 1; i >= 1; i-- {
		a[i], a[0] = a[0], a[i]
		a = a[:len(a)-1]
		heapify(a, 0)
	}

	a = a[:cap(a)]
}

func InsertionSortForList(l *list.List) {
	if l.Len() < 2 {
		return
	}

	for i := l.Front().Next(); i != nil; i = i.Next() {
		j := i
		key := j.Value.(int)
		for ; j.Prev() != nil && key < j.Prev().Value.(int); j = j.Prev() {
			j.Value = j.Prev().Value
		}
		j.Value = key
	}
}

func BucketSort(a []int, max int, min int) {
	var bucket [10]*list.List

	for i := 0; i < 10; i++ {
		bucket[i] = list.New()
	}

	valueRange := max - min + 1
	for _, v := range a {
		bucket[(v-min)*10/valueRange].PushBack(v)
	}

	aIndex := 0
	for i := 0; i < 10; i++ {
		l := bucket[i]
		InsertionSortForList(l)
		for e := l.Front(); e != nil; e = e.Next() {
			a[aIndex] = e.Value.(int)
			aIndex++
		}
	}
}
