package main

import "fmt"

func TwoSumHash(arr []int, k int) (int, int) {
	mpp := make(map[int]int)
	for i, ele := range arr {
		need := k - ele
		if index, ok := mpp[need]; ok {
			return index, i
		}
		mpp[ele] = i
	}
	return -1, -1
}

func main() {
	arr := []int{4, 7, 8, 1}
	fmt.Println(TwoSumHash(arr, 8))
}
