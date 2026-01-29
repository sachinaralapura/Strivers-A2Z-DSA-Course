package main

import (
	"fmt"
	"math"
)

func secondMax(arr []int) int {
	maxi := math.MinInt
	second_max := math.MinInt

	for _, v := range arr {
		if v > maxi {
			second_max = maxi
			maxi = v
		}
		if v > second_max && v != maxi {
			second_max = v
		}
	}
	return second_max
}

func main() {
	arr := []int{1, 2, 3, 5}
	second_max := secondMax(arr)
	fmt.Println(second_max)
}
