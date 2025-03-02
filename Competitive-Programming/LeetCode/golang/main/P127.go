package main


import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

type queueElement struct {
	index int
	len   int
}

func diff1(s1, s2 string) bool {
	if len(s1) != len(s2) {
		return false
	}

	diffCount := 0
	for i := 0; i < len(s1); i++ {
		if s1[i] != s2[i] {
			diffCount++
			if diffCount > 1 {
				return false
			}
		}
	}

	if diffCount <= 1 {
		return true
	}
	return false
}

func ladderLength(beginWord string, endWord string, wordList []string) int {
	queue := make([]queueElement, 0)
	used := make(map[int]bool)
	endIndex := -1

	for i := 0; i < len(wordList); i++ {
		used[i] = false
		if endWord == wordList[i] {
			endIndex = i
		}
	}

	if endIndex == -1 {
		return 0
	}

	edges := make([][]int, len(wordList))
	for i := 0; i < len(wordList); i++ {
		for j := i + 1; j < len(wordList); j++ {
			if diff1(wordList[i], wordList[j]) {
				edges[i] = append(edges[i], j)
				edges[j] = append(edges[j], i)
			}
		}
	}

	for i, s := range wordList {
		if diff1(beginWord, s) {
			if s == endWord {
				return 2
			}

			used[i] = true
			if beginWord == s {
				queue = append(queue, queueElement{i, 1})
			} else {
				queue = append(queue, queueElement{i, 2})
			}
		}
	}

	for len(queue) != 0 {
		prev := queue[0]
		queue = queue[1:]

		for i := 0; i < len(edges[prev.index]); i++ {
			nextIndex := edges[prev.index][i]
			if nextIndex == endIndex {
				return prev.len + 1
			}

			if used[nextIndex] == false {
				used[nextIndex] = true
				queue = append(queue, queueElement{nextIndex, prev.len + 1})
			}
		}

	}

	return 0
}

func main() {
	check(ladderLength("hit", "cog", []string{"hot", "dot", "dog", "lot", "log", "cog"}) == 5)
	check(ladderLength("hit", "cog", []string{"hot", "dot", "dog", "lot", "log"}) == 0)
	check(ladderLength("hit", "cog", []string{"hot", "cog"}) == 0)
	check(ladderLength("dot", "cog", []string{"cot", "cog"}) == 3)
	check(ladderLength("dot", "dog", []string{"dot", "dog"}) == 2)
	check(ladderLength("a", "c", []string{"a", "b", "c"}) == 2)
	check(ladderLength("dot", "cot", []string{}) == 0)
}
