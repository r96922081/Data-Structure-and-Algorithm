package dsa

func inorderGenCode(node *BinaryTreeNode, code string, output *[]*HuffmanCodeOutput) {
	leaf := true
	if node.Left != nil {
		inorderGenCode(node.Left, code+"0", output)
		leaf = false
	}
	if node.Right != nil {
		inorderGenCode(node.Right, code+"1", output)
		leaf = false
	}

	if leaf {
		o := new(HuffmanCodeOutput)
		o.Code = code
		o.Value = node.Value
		*output = append(*output, o)
	}
}

type HuffmanCodeInput struct {
	Count int
	Value interface{}
}

type HuffmanCodeOutput struct {
	Code  string
	Value interface{}
}

func GenHuffmanCode(input []*HuffmanCodeInput) []*HuffmanCodeOutput {
	output := make([]*HuffmanCodeOutput, len(input))

	biggerThanFunc := func(v1 interface{}, v2 interface{}) bool {
		return v1.(*HuffmanCodeInput).Count < v2.(*HuffmanCodeInput).Count
	}
	q := NewPriorityQueue(biggerThanFunc)

	for _, v := range input {
		huffnode := new(HuffmanCodeInput)
		huffnode.Count = v.Count
		huffnode.Value = new(BinaryTreeNode)
		huffnode.Value.(*BinaryTreeNode).Value = v.Value
		q.Insert(huffnode)
	}

	for true {
		n1 := q.ExtractMax()
		if q.Empty() {
			output := make([]*HuffmanCodeOutput, 0)
			inorderGenCode(n1.(*HuffmanCodeInput).Value.(*BinaryTreeNode), "", &output)
			return output
		}
		n2 := q.ExtractMax()
		n3 := new(HuffmanCodeInput)
		n3.Count = n1.(*HuffmanCodeInput).Count + n2.(*HuffmanCodeInput).Count
		binaryNode := new(BinaryTreeNode)
		binaryNode.Left = n1.(*HuffmanCodeInput).Value.(*BinaryTreeNode)
		binaryNode.Right = n2.(*HuffmanCodeInput).Value.(*BinaryTreeNode)
		n3.Value = binaryNode

		q.Insert(n3)
	}

	return output
}
