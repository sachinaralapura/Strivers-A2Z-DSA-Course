package main

import "fmt"

func MaxOneCount(arr []int) int {
	maxi := 0
	count := 0
	for _, ele := range arr {
		if ele == 1 {
			count++
		} else {
			count = 0
		}
		if count > maxi {
			maxi = count
		}
	}
	return maxi
}

func main() {
	arr := []int{0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}
	res := MaxOneCount(arr)
	fmt.Println(res)
}
