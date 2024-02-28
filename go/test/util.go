package test

import (
	"fmt"
	"math/rand"
	"testing"
	"time"

	"github.com/stretchr/testify/assert"
)

var seed = int64(0)

func SetSeedTo1() {
	seed = 1
	rand.Seed(seed)
}

func SetSeed() {
	if seed != 0 {
		return
	}

	seed = time.Now().UTC().UnixNano()
	rand.Seed(seed)
	fmt.Print("Set seed to ", seed, "\n")
}

func AssertTrue(t *testing.T, exp bool) {
	assert.True(t, exp)
}
