package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Print("check failed!")
	}
}

type node struct {
	row int
	col int
}

func isNext(grid [][]int, row, col, rowCount, colCount, nodeType int) bool {
	if row < 0 || row >= rowCount || col < 0 || col >= colCount {
		return false
	}

	if grid[row][col] == nodeType {
		return true
	}

	return false
}

func walk(grid [][]int, curRow, curCol, rowCount, colCount, destRow, destCol, stepCount, emptyCount int) int {
	rowMove := [4]int{0, 0, 1, -1}
	colMove := [4]int{1, -1, 0, 0}

	answer := 0

	for i := 0; i < 4; i++ {
		nextRow := curRow + rowMove[i]
		nextCol := curCol + colMove[i]

		if isNext(grid, nextRow, nextCol, rowCount, colCount, 2) {
			if stepCount == emptyCount {
				return 1
			}
		} else if isNext(grid, nextRow, nextCol, rowCount, colCount, 0) {
			grid[nextRow][nextCol] = -2
			answer += walk(grid, nextRow, nextCol, rowCount, colCount, destRow, destCol, stepCount+1, emptyCount)
			grid[nextRow][nextCol] = 0
		}
	}

	return answer
}

func uniquePathsIII(grid [][]int) int {
	src := node{}
	dest := node{}
	emptyCount := 0

	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[i]); j++ {
			if grid[i][j] == 1 {
				src.row = i
				src.col = j
			} else if grid[i][j] == 2 {
				dest.row = i
				dest.col = j
			} else if grid[i][j] == 0 {
				emptyCount++
			}
		}
	}

	return walk(grid, src.row, src.col, len(grid), len(grid[0]), dest.row, dest.col, 0, emptyCount)
}

func new2DInt(n, m int) [][]int {
	ret := make([][]int, n)
	for i := 0; i < len(ret); i++ {
		ret[i] = make([]int, m)
	}
	return ret
}

func main() {
	grid := new2DInt(2, 2)
	grid[0][0] = 1
	grid[1][0] = -1
	grid[1][1] = 2
	check(uniquePathsIII(grid) == 1)

	grid = new2DInt(2, 2)
	grid[0][0] = 1
	grid[1][1] = 2
	check(uniquePathsIII(grid) == 0)

	grid = new2DInt(3, 3)
	grid[0][0] = 1
	grid[1][1] = 2
	check(uniquePathsIII(grid) == 2)
}
