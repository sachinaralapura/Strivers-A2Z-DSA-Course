package main

import "fmt"

func FindSingleMap(arr []int) int {
	mpp := make(map[int]int)
	for _, ele := range arr {
		mpp[ele]++
	}
	for i, v := range mpp {
		if v == 1 {
			return i
		}
	}
	return -1
}

func FindSingleXor(arr []int) int {
	xor := 0
	for _, ele := range arr {
		xor = xor ^ ele
	}
	return xor
}

func main() {
	arr := []int{2, 2, 3, 3, 1, 4, 5, 4, 5}
	res := FindSingleXor(arr)
	fmt.Println(res)
}
