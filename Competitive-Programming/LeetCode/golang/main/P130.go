package main

import "fmt"

func main() {
    fmt.Println("P130")
}

var diffX = []int{1, -1, 0, 0}
var diffY = []int{0, 0, 1, -1}

func floodFill(board [][]byte, x, y int) {
	if x < 0 || x == len(board) || y < 0 || y == len(board[0]) || board[x][y] != 'O' {
		return
	}

	board[x][y] = '-'
	for i := 0; i < 4; i++ {
		floodFill(board, x+diffX[i], y+diffY[i])
	}
}

func solve(board [][]byte) {
	if len(board) == 0 {
		return
	}
	for i := 0; i < len(board[0]); i++ {
		floodFill(board, 0, i)
		floodFill(board, len(board)-1, i)
	}

	for i := 0; i < len(board); i++ {
		floodFill(board, i, 0)
		floodFill(board, i, len(board[0])-1)
	}

	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[0]); j++ {
			if board[i][j] == 'O' {
				board[i][j] = 'X'
			}
		}
	}

	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[0]); j++ {
			if board[i][j] == '-' {
				board[i][j] = 'O'
			}
		}
	}
}
