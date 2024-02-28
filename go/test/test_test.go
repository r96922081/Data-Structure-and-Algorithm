package test

import (
	"fmt"
	"testing"
)

func TestTest(t *testing.T) {
	fmt.Println("TestTest")
	AssertTrue(t, true)
}
