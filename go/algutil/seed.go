package algutil

import (
	"fmt"
	"math/rand"
	"time"
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
