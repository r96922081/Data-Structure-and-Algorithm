package priorityqueue

type biggerThanFunc func(v1 interface{}, v2 interface{}) bool

type Element struct {
	index int
	Value interface{}
}

type PriorityQueue struct {
	a              []*Element
	biggerThanFunc biggerThanFunc
}

func New(biggerThanFunc biggerThanFunc) *PriorityQueue {
	ret := new(PriorityQueue)
	ret.a = make([]*Element, 0)
	ret.biggerThanFunc = biggerThanFunc

	return ret
}

func (q *PriorityQueue) Empty() bool {
	return len(q.a) == 0
}

func (q *PriorityQueue) ExtractMax() interface{} {
	max := q.a[0].Value
	v := q.a[len(q.a)-1].Value
	q.a = q.a[:len(q.a)-1]
	if q.Empty() {
		return max
	}

	idx := 0
	left := 1
	right := 2
	for left < len(q.a) {
		maxChild := left
		if right < len(q.a) && q.biggerThanFunc(q.a[right].Value, q.a[left].Value) {
			maxChild = right
		}

		if !q.biggerThanFunc(q.a[maxChild].Value, v) {
			break
		}

		q.a[idx].Value = q.a[maxChild].Value
		idx = maxChild
		left = (idx+1)*2 - 1
		right = left + 1
	}

	q.a[idx].Value = v

	return max
}

func (q *PriorityQueue) maxHeapifyBottomUp(e *Element) {
	v := e.Value
	idx := e.index
	for ; idx > 0; idx = (idx - 1) / 2 {
		parent := q.a[(idx-1)/2]
		if q.biggerThanFunc(parent.Value, v) {
			break
		}
		q.a[idx].Value = parent.Value
	}
	q.a[idx].Value = v
}

func (q *PriorityQueue) Insert(v interface{}) {
	e := new(Element)
	e.index = len(q.a)
	e.Value = v
	q.a = append(q.a, e)
	q.maxHeapifyBottomUp(e)
}
