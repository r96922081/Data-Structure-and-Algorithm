package graph

import (
	"container/list"
	"fmt"
	"math"
	"math/rand"
	"testing"
	"time"
)

type AdjacencyList []*list.List
type AdjacencyMatrix [][]int
type StronglyConnectedComponent = list.List

type Edge struct {
	Src  int
	Dest int
	Len  int
}

func NewAdjList(vertexCount int) AdjacencyList {
	ret := make([]*list.List, vertexCount)

	for i := range ret {
		ret[i] = list.New()
	}

	return ret
}

func NewAdjMatrix(vertexCount int) AdjacencyMatrix {
	ret := make([][]int, vertexCount)

	for i := 0; i < vertexCount; i++ {
		ret[i] = make([]int, vertexCount)
	}

	return ret
}

// GenerateGraphInAdjacencyList : edgePercent is the expected (edge count)/(complete graph edge count)
func GenerateGraphInAdjacencyList(vertexCount int, edgePercent int, directed bool, weighted bool, maxLength int) AdjacencyList {

	ret := NewAdjList(vertexCount)

	if directed {
		for i := range ret {
			for j := 0; j < vertexCount; j++ {
				if float64(rand.Int()%(vertexCount*vertexCount)) < float64(edgePercent)/100.0*float64(vertexCount*vertexCount) {
					e := Edge{i, j, 1}
					if weighted {
						e.Len = rand.Int()%maxLength + 1
					}
					ret[i].PushBack(e)
				}
			}
		}
	} else {
		for i := range ret {
			for j := i; j < vertexCount; j++ {
				if float64(rand.Int()%(vertexCount*vertexCount)) < float64(edgePercent)/100.0*float64(vertexCount*vertexCount) {
					e := Edge{i, j, 1}
					if weighted {
						e.Len = rand.Int()%maxLength + 1
					}
					ret[i].PushBack(e)

					e2 := e
					e2.Src, e2.Dest = e2.Dest, e2.Src
					if i != j {
						ret[j].PushBack(e2)
					}
				}
			}
		}
	}

	return ret
}

// GenerateGraphInAdjacencyMatrix : edgePercent is the expected (edge count)/(complete graph edge count)
func GenerateGraphInAdjacencyMatrix(vertexCount int, edgePercent int, directed bool, weighted bool, maxLength int) *AdjacencyMatrix {

	adjList := GenerateGraphInAdjacencyList(vertexCount, edgePercent, directed, weighted, maxLength)

	return adjList.ConvertToMatrix()
}

func (a AdjacencyMatrix) Print() {
	vertexCount := len(a)
	maxWidth := 0
	maxVertexWidth := 1
	for i := vertexCount; i/10 != 0; i /= 10 {
		maxVertexWidth++
	}
	maxEdgeWidth := 0
	for i := range a {
		for j := range a[i] {
			width := 1
			for k := a[i][j]; k/10 != 0; k /= 10 {
				width++
			}
			maxEdgeWidth = int(math.Max(float64(maxEdgeWidth), float64(width)))
		}
	}

	maxWidth = int(math.Max(float64(maxVertexWidth), float64(maxEdgeWidth)))

	for i := 0; i < maxWidth+1; i++ {
		fmt.Print(" ")
	}

	for i := range a {
		fmt.Printf(" %*d ", maxWidth, i)
	}
	fmt.Print("\n")

	width := maxWidth*(vertexCount+1) + (vertexCount)*2

	for i := 0; i <= width; i++ {
		fmt.Print("_")
	}
	fmt.Print("\n")

	for i := range a {
		fmt.Printf(" %*d| ", maxWidth, i)
		for j := 0; j < len(a[i]); j++ {
			if j != 0 {
				fmt.Print("| ")
			}
			fmt.Printf("%*d", maxWidth, a[i][j])
		}
		fmt.Print("|\n")
	}

	for i := 0; i <= width; i++ {
		fmt.Print("_")
	}
	fmt.Print("\n")
}

func (a AdjacencyList) Print() {
	for i := range a {
		fmt.Printf("%d: ", i)
		l := a[i]
		for e := l.Front(); e != nil; e = e.Next() {
			if e != l.Front() {
				fmt.Print(", ")
			}

			edge := e.Value.(Edge)

			fmt.Printf("%d(%d)", edge.Dest, edge.Len)
		}

		fmt.Print("\n")
	}
}

func (a AdjacencyList) ConvertToMatrix() *AdjacencyMatrix {
	vertexCount := len(a)
	ret := NewAdjMatrix(vertexCount)

	for i := range a {
		l := a[i]
		for e := l.Front(); e != nil; e = e.Next() {
			edge := e.Value.(Edge)
			ret[edge.Src][edge.Dest] = edge.Len
		}
	}

	return &ret
}

func BFS(adjList AdjacencyList, src int) *list.List {
	bfsOrder := list.New()
	visited := make([]bool, len(adjList))

	visitingQueue := list.New()
	visitingQueue.PushBack(src)

	for visitingQueue.Len() != 0 {
		vertex := visitingQueue.Front().Value.(int)
		visitingQueue.Remove(visitingQueue.Front())
		if visited[vertex] {
			continue
		}
		visited[vertex] = true
		bfsOrder.PushBack(vertex)

		for e := adjList[vertex].Front(); e != nil; e = e.Next() {
			neighbor := e.Value.(Edge).Dest
			if visited[neighbor] == false {
				visitingQueue.PushBack(neighbor)
			}
		}
	}

	return bfsOrder
}

func dfs2(adjList AdjacencyList, src int, visited []bool, dfsOrder *list.List) {
	if visited[src] {
		return
	}

	visited[src] = true

	for e := adjList[src].Front(); e != nil; e = e.Next() {
		dfs2(adjList, e.Value.(Edge).Dest, visited, dfsOrder)
	}

	dfsOrder.PushBack(src)
}

func DFS(adjList AdjacencyList, src int) *list.List {
	dfsOrder := list.New()
	visited := make([]bool, len(adjList))
	dfs2(adjList, src, visited, dfsOrder)

	return dfsOrder
}

func getTransposedAdjList(adjList AdjacencyList, vertexCount int) *AdjacencyList {
	transposedAdjList := NewAdjList(vertexCount)

	for i := range adjList {
		list := adjList[i]
		for e := list.Front(); e != nil; e = e.Next() {
			j := e.Value.(Edge).Dest
			len := e.Value.(Edge).Len
			transposedAdjList[j].PushBack(Edge{j, i, len})
		}
	}

	return &transposedAdjList
}

func traverseByReversedOrder(dfsOrder *list.List, adjMatrix *AdjacencyMatrix) *list.List {
	for e := dfsOrder.Back(); e != nil; {
		scc := list.New()
		e2 := e
		e = e.Prev()
		dfsOrder.Remove(e2)
	}

	return scc
}

func GetStronglyConnectedComponent(adjList AdjacencyList) *StronglyConnectedComponent {
	vertexCount := len(adjList)
	scc := list.New()

	transposedAdjList := getTransposedAdjList(adjList, vertexCount)
	transposedMatrix := transposedAdjList.ConvertToMatrix()

	remainingVertex := make(map[int]int)
	for index := 0; index < vertexCount; index++ {
		remainingVertex[index] = 1
	}

	for len(remainingVertex) != 0 {
		currentVertex := 0
		for key := range remainingVertex {
			currentVertex = key
			break
		}

		dfsOrder := DFS(adjList, currentVertex)

		for dfsOrder.Len() != 0 {
			oneScc := list.New()

			traverseByReversedOrder(dfsOrder, transposedMatrix)
			scc.PushBack(oneScc)

			for e := oneScc.Front(); e != nil; e = e.Next() {
				vertex2 := e.Value.(int)
				delete(remainingVertex, vertex2)
				for i := 0; i < len(*transposedMatrix); i++ {
					(*transposedMatrix)[i][vertex2] = 0
				}
			}
		}
	}

	return scc
}

func TestStronglyConnectedComponentUndirected(t *testing.T) {
	seed := time.Now().Unix()
	fmt.Print("Seed = ", seed, "\n")
	rand.Seed(1523155566)
	vertexCount := 4
	adjList := GenerateGraphInAdjacencyList(vertexCount, 50, true, false, 0)

	adjList.Print()
	fmt.Print("================\n\n")
	scc := GetStronglyConnectedComponent(adjList)

	for list1 := scc.Front(); list1 != nil; list1 = list1.Next() {
		for list2 := list1.Value.(*list.List).Front(); list2 != nil; list2 = list2.Next() {
			fmt.Print(list2.Value.(int), " ")
		}
		fmt.Print("\n---\n")
	}
}
