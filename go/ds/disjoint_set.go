package ds

/*
// DisjointSetElement : only set Value to your element
type DisjointSetElement struct {
	Value  interface{}
	rank   int
	parent *DisjointSetElement
}

func NewDisjointSetElement(value interface{}) *DisjointSetElement {
	ret := new(DisjointSetElement)
	ret.Value = value
	ret.parent = ret

	return ret
}

func (e *DisjointSetElement) Union(e2 *DisjointSetElement) {
	if e.rank >= e2.rank {
		e2.parent = e
		if e.rank == e2.rank {
			e.rank++
		}
	} else {
		e.parent = e2
	}
}

func (e *DisjointSetElement) Find() *DisjointSetElement {
	if e.parent == e {
		return e
	}

	e.parent = e.parent.Find()

	return e.parent
}

// FindConnectComponentByDisjointSet returns list of list (connected components)
func FindConnectComponentByDisjointSet(vertex []int, edges []graph.Edge) *list.List {
	connectComponents := list.New()

	disjointSetElementMap := make(map[int]*DisjointSetElement)

	for _, vertexIndex := range vertex {
		disjointSetElementMap[vertexIndex] = NewDisjointSetElement(vertexIndex)
	}

	for _, edge := range edges {
		disjointSetElement1 := disjointSetElementMap[edge.Src]
		disjointSetElement2 := disjointSetElementMap[edge.Dest]
		if disjointSetElement1.Find() != disjointSetElement2.Find() {
			disjointSetElement1.Union(disjointSetElement2)
		}
	}

	disjointSetMap := make(map[*DisjointSetElement]*list.List)
	for _, disjointSetElement := range disjointSetElementMap {
		_, ok := disjointSetMap[disjointSetElement.Find()]
		if !ok {
			disjointSetMap[disjointSetElement.Find()] = list.New()
		}
		list := disjointSetMap[disjointSetElement.Find()]
		list.PushBack(disjointSetElement)
	}

	for _, connectedComponent := range disjointSetMap {
		connectComponents.PushBack(connectedComponent)
	}

	return connectComponents
}
*/
