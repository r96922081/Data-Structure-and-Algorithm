package main

import (
	"dsa/dsa"
	"fmt"
)

func main() {
	_ = dsa.NewBTreeDisk(2, "tt")
	fmt.Println("main()")
}
