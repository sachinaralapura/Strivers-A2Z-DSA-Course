package main

import "fmt"

func MissingNumberSum(arr []int) int {
	n := len(arr) + 1
	sum1 := (n * (n + 1)) / 2
	sum2 := 0
	for _, i := range arr {
		sum2 += i
	}
	return sum1 - sum2
}

func MissingNumberXor(arr []int) int {
	n := len(arr)
	xor1 := 0
	xor2 := 0
	for i, ele := range arr {
		xor1 = xor1 ^ (i + 1)
		xor2 = xor2 ^ ele
	}
	xor1 = xor1 ^ n + 1
	return xor1 ^ xor2
}

func main() {
	arr := []int{1, 3, 4, 5}
	res := MissingNumberSum(arr)
	fmt.Println(res)
}
