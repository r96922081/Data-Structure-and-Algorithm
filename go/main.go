package main

import (
	"dsa/dsa"
	"fmt"
)

func main() {
	_ = dsa.NewBTreeDisk(2, "tt", nil)
	fmt.Println("main()")
}
