package main


import (
	"fmt"
	"math"
	"sort"
)

func check(b bool) {
	if !b {
		fmt.Println("error")
	}
}

func findRadius(houses []int, heaters []int) int {
	sort.Ints(houses)
	sort.Ints(heaters)
	heaters2 := make([]int, len(heaters)+2)
	heaters2[0] = math.MinInt32
	for i := 0; i < len(heaters); i++ {
		heaters2[1+i] = heaters[i]
	}
	heaters2[len(heaters2)-1] = math.MaxInt32
	heaterIndex := 1

	maxOfMin := 0
	for _, v := range houses {
		for heaters2[heaterIndex] <= v {
			heaterIndex++
		}
		prevHeater := heaters2[heaterIndex-1]
		nextHeater := heaters2[heaterIndex]
		min := v - prevHeater
		if nextHeater-v < min {
			min = nextHeater - v
		}

		if min > maxOfMin {
			maxOfMin = min
		}
	}

	return maxOfMin
}

func main() {
	findRadius([]int{1, 2, 3, 4}, []int{1, 4})
}
