package test

import (
	"dsa/dsa"
	"fmt"
	"math/rand"
	"testing"
	"time"
)

func TestPriorityQueue(t *testing.T) {
	fmt.Println("TestPriorityQueue")
	seed := time.Now().Unix()
	rand.Seed(seed)

	biggerThanFunc := func(v1 interface{}, v2 interface{}) bool {
		return v1.(int) > v2.(int)
	}

	for i := 0; i < 20; i++ {
		q := dsa.NewPriorityQueue(biggerThanFunc)
		for size := 1; size < 30; size++ {
			q.Insert(rand.Int() % 30)
		}

		prev := 1000
		for !q.Empty() {
			e := q.ExtractMax()
			AssertTrue(t, prev >= e.(int))
			prev = e.(int)
		}
	}
}
