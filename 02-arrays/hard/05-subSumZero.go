package main

import "fmt"

func MaxLen(arr []int) int {
	n := len(arr)
	mpp := make(map[int]int)
	sum := 0
	maxi := 0
	for i := 0; i < n; i++ {
		sum += arr[i]
		if sum == 0 {
			maxi = i + 1
		} else if index, ok := mpp[sum]; ok {
			if i-index > maxi {
				maxi = i - index
			}
		} else {
			mpp[sum] = i
		}
	}
	return maxi
}

func main() {
	arr := []int{6, -2, 2, -8, 1, 7, 4, -10}
	res := MaxLen(arr)
	fmt.Println(res)
}
