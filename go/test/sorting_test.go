package test

import (
	"dsa/dsa"
	"fmt"
	"math/rand"
	"testing"
)

func generateRandomIntSlice(size int, max int, min int) []int {
	SetSeed()
	randomIntSlice := make([]int, size)
	for i := 0; i < size; i++ {
		randomIntSlice[i] = rand.Int()%(max-min+1) + min
	}

	return randomIntSlice
}

func TestInsertionSort(t *testing.T) {
	fmt.Println("TestInsertionSort")
	a := generateRandomIntSlice(100, 30, -40)
	dsa.InsertionSort(a)
	for i := 1; i < len(a); i++ {
		AssertTrue(t, a[i-1] <= a[i])
	}
}

func TestBubbleSort(t *testing.T) {
	fmt.Println("TestBubbleSort")
	a := generateRandomIntSlice(100, 30, -40)
	b := make([]int, len(a))
	copy(b, a)

	dsa.InsertionSort(b)
	dsa.BubbleSort(a)

	for i := 0; i < len(a); i++ {
		AssertTrue(t, a[i] == b[i])
	}
}

func TestMergeSort(t *testing.T) {
	fmt.Println("TestMergeSort")
	for i := 1; i < 100; i++ {
		for size := 1; size < 18; size++ {
			a := generateRandomIntSlice(size, 30, -40)
			b := make([]int, len(a))
			copy(b, a)

			dsa.InsertionSort(b)
			dsa.MergeSort(a)

			for i := 0; i < len(a); i++ {
				AssertTrue(t, a[i] == b[i])
			}
		}
	}
}

func TestQuickSort(t *testing.T) {
	fmt.Println("TestQuickSort")
	for i := 1; i < 100; i++ {
		for size := 1; size < 40; size++ {
			a := generateRandomIntSlice(size, 30, -40)
			b := make([]int, len(a))
			copy(b, a)

			dsa.InsertionSort(b)
			dsa.QuickSort(a)

			for j := 0; j < len(a); j++ {
				AssertTrue(t, a[j] == b[j])
			}
		}
	}
}

func TestRadixSort(t *testing.T) {
	fmt.Println("TestRadixSort")
	for i := 1; i < 20; i++ {
		for size := 1; size < 15; size++ {
			a := generateRandomIntSlice(size, 66, -66)
			b := make([]int, len(a))
			copy(b, a)

			dsa.InsertionSort(b)
			dsa.RadixSort(a)

			for j := 0; j < len(a); j++ {
				AssertTrue(t, a[j] == b[j])
			}
		}
	}
}

func TestCountingSort(t *testing.T) {
	fmt.Println("TestCountingSort")
	for i := 0; i < 20; i++ {
		for size := 1; size < 30; size++ {
			a := generateRandomIntSlice(size, 66, -66)
			b := make([]int, len(a))
			unsortedA := make([]int, len(a))
			copy(b, a)
			copy(unsortedA, a)

			dsa.InsertionSort(b)
			order := dsa.CountingSort(a)

			for j := 0; j < len(a); j++ {
				AssertTrue(t, a[j] == b[j])
			}

			for i, v := range order {
				AssertTrue(t, unsortedA[i] == a[v])
			}
		}
	}
}

func TestHeapSort(t *testing.T) {
	fmt.Println("TestHeapSort")
	for i := 0; i < 20; i++ {
		for size := 1; size < 30; size++ {
			a := generateRandomIntSlice(size, 66, -66)
			b := make([]int, len(a))
			copy(b, a)

			dsa.InsertionSort(b)
			dsa.HeapSort(a)

			for j := 0; j < len(a); j++ {
				AssertTrue(t, a[j] == b[j])
			}
		}
	}
}

func TestBucketSort(t *testing.T) {
	fmt.Println("TestBucketSort")
	for i := 0; i < 20; i++ {
		for size := 1; size < 30; size++ {
			min := -66
			max := 66
			a := generateRandomIntSlice(size, max, min)
			b := make([]int, len(a))
			copy(b, a)

			dsa.InsertionSort(b)
			dsa.BucketSort(a, max, min)

			for j := 0; j < len(a); j++ {
				AssertTrue(t, a[j] == b[j])
			}
		}
	}
}
