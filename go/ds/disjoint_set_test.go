package ds

/*
func TestUnion(t *testing.T) {
	e1 := NewDisjointSetElement(1)
	algutil.AssertTrue(t, e1.parent == e1)
	e2 := NewDisjointSetElement(2)
	e3 := NewDisjointSetElement(3)
	e1.Union(e2)
	algutil.AssertTrue(t, e1.rank == 1)
	algutil.AssertTrue(t, e2.parent == e1)
	e1.Union(e3)
	algutil.AssertTrue(t, e3.parent == e1)
}

func TestFind(t *testing.T) {
	e1 := NewDisjointSetElement(1)
	e2 := NewDisjointSetElement(2)
	e3 := NewDisjointSetElement(3)
	e4 := NewDisjointSetElement(4)
	e1.Union(e2)
	e3.Union(e4)
	e1.Union(e3)
	algutil.AssertTrue(t, e1.Find() == e1)
	algutil.AssertTrue(t, e2.Find() == e1)
	algutil.AssertTrue(t, e3.Find() == e1)
	algutil.AssertTrue(t, e4.Find() == e1)
}

func TestFindConnectedComponent(t *testing.T) {
	edges := []graph.Edge{{1, 2, 1}, {1, 3, 1}, {4, 5, 1}}
	vertex := make([]int, 6)
	for i := 0; i < 6; i++ {
		vertex[i] = i + 1
	}

	connectedComponent := FindConnectComponentByDisjointSet(vertex, edges)

	algutil.AssertTrue(t, connectedComponent.Len() == 3)

	for e := connectedComponent.Front(); e != nil; e = e.Next() {
		aConnectedComponent := e.Value.(*list.List)
		if aConnectedComponent.Len() == 1 {
			e2 := aConnectedComponent.Front().Value.(*DisjointSetElement)
			algutil.AssertTrue(t, e2.Value == 6)
		} else if aConnectedComponent.Len() == 2 {
			aConnectedComponent := e.Value.(*list.List)
			answer := make([]int, 2)
			e2 := aConnectedComponent.Front()
			answer[0] = e2.Value.(*DisjointSetElement).Value.(int)
			e2 = e2.Next()
			answer[1] = e2.Value.(*DisjointSetElement).Value.(int)

			if answer[0] > answer[1] {
				answer[0], answer[1] = answer[1], answer[0]
			}

			algutil.AssertTrue(t, answer[0] == 4)
			algutil.AssertTrue(t, answer[1] == 5)

		} else if aConnectedComponent.Len() == 3 {
			aConnectedComponent := e.Value.(*list.List)
			answer := make([]int, 3)
			e2 := aConnectedComponent.Front()
			answer[0] = e2.Value.(*DisjointSetElement).Value.(int)
			e2 = e2.Next()
			answer[1] = e2.Value.(*DisjointSetElement).Value.(int)
			e2 = e2.Next()
			answer[2] = e2.Value.(*DisjointSetElement).Value.(int)

			if answer[0] > answer[1] {
				answer[0], answer[1] = answer[1], answer[0]
			}

			if answer[1] > answer[2] {
				answer[1], answer[2] = answer[2], answer[1]
			}

			if answer[0] > answer[1] {
				answer[0], answer[1] = answer[1], answer[0]
			}

			algutil.AssertTrue(t, answer[0] == 1)
			algutil.AssertTrue(t, answer[1] == 2)
			algutil.AssertTrue(t, answer[2] == 3)
		} else {
			algutil.AssertTrue(t, false)
		}
	}
}
*/
