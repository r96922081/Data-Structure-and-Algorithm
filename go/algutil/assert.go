package algutil

import "testing"

func AssertTrue(t *testing.T, exp bool) {
	if !exp {
		t.FailNow()
	}
}
