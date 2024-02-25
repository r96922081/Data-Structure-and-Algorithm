package test

import (
	"dsa/algutil"
	"dsa/dsa"
	"math/rand"
	"testing"
)

func TestHuffmanCode1(t *testing.T) {
	input1 := make([]*dsa.HuffmanCodeInput, 0)
	a := new(dsa.HuffmanCodeInput)
	a.Count = 45
	a.Value = 'a'
	input1 = append(input1, a)
	input1[0] = a
	b := new(dsa.HuffmanCodeInput)
	b.Count = 13
	b.Value = 'b'
	input1 = append(input1, b)
	c := new(dsa.HuffmanCodeInput)
	c.Count = 12
	c.Value = 'c'
	input1 = append(input1, c)
	d := new(dsa.HuffmanCodeInput)
	d.Count = 16
	d.Value = 'd'
	input1 = append(input1, d)
	e := new(dsa.HuffmanCodeInput)
	e.Count = 9
	e.Value = 'e'
	input1 = append(input1, e)
	f := new(dsa.HuffmanCodeInput)
	f.Count = 5
	f.Value = 'f'
	input1 = append(input1, f)

	output := dsa.GenHuffmanCode(input1)

	//answer a = 0, c = 100, b = 101, f = 1100, e = 1101, d = 111
	for i, v1 := range output {
		for j, v2 := range output {
			v1Count := 0
			v2Count := 0
			for _, v3 := range input1 {
				if v3.Value == v1.Value {
					v1Count = v3.Count
				} else if v3.Value == v2.Value {
					v2Count = v3.Count
				}
			}
			if i != j {
				if v1Count > v2Count {
					algutil.AssertTrue(t, len(v1.Code) <= len(v2.Code))
				} else if v2Count > v1Count {
					algutil.AssertTrue(t, len(v2.Code) <= len(v1.Code))
				}

				if len(v1.Code) <= len(v2.Code) {
					algutil.AssertTrue(t, v1.Code != v2.Code[:len(v1.Code)])
				} else {
					algutil.AssertTrue(t, v2.Code != v1.Code[:len(v2.Code)])
				}

			}
		}
	}
}

func TestHuffmanCode2(t *testing.T) {
	for ti := 0; ti < 100; ti++ {
		input := make([]*dsa.HuffmanCodeInput, 0)
		for i := 0; i < 26; i++ {
			a := new(dsa.HuffmanCodeInput)
			a.Count = rand.Int() % 20
			a.Value = 'a' + i
			input = append(input, a)
		}

		output := dsa.GenHuffmanCode(input)

		for i, v1 := range output {
			for j, v2 := range output {
				v1Count := 0
				v2Count := 0
				for _, v3 := range input {
					if v3.Value == v1.Value {
						v1Count = v3.Count
					} else if v3.Value == v2.Value {
						v2Count = v3.Count
					}
				}
				if i != j {
					if v1Count > v2Count {
						algutil.AssertTrue(t, len(v1.Code) <= len(v2.Code))
					} else if v2Count > v1Count {
						algutil.AssertTrue(t, len(v2.Code) <= len(v1.Code))
					}

					if len(v1.Code) <= len(v2.Code) {
						algutil.AssertTrue(t, v1.Code != v2.Code[:len(v1.Code)])
					} else {
						algutil.AssertTrue(t, v2.Code != v1.Code[:len(v2.Code)])
					}

				}
			}
		}
	}
}
