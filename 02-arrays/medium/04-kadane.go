package main

import (
	"fmt"
	"math"
)

func SubarraySum(arr []int) (int, []int) {
	sum := 0
	maxi := math.MinInt
	start := 0
	end := 0
	for i := 0; i < len(arr); i++ {
		if sum == 0 {
			start = i
		}
		sum += arr[i]
		if sum > maxi {
			maxi = sum
			end = i
		}
		if sum < 0 {
			sum = 0
		}
	}
	return maxi, arr[start : end+1]
}

func main() {
	arr := []int{6, -2, -3, 2, -1, 4, -1, -2, 1, 5, -3}
	max, maxarr := SubarraySum(arr)
	fmt.Println(max)
	fmt.Println(maxarr)

}
