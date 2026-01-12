package main

import "fmt"

func MoveZero(arr []int) {
	n := len(arr)
	i := 0
	j := 0
	for k := 0; k < n; k++ {
		if arr[k] == 0 {
			j = k
			break
		}
	}

	if j == -1 {
		return
	}
	i = j + 1
	for i < n {
		if arr[i] != 0 {
			arr[i], arr[j] = arr[j], arr[i]
			j++
		}
		i++
	}
}

func main() {
	arr := []int{1, 0, 2, 3, 2, 0, 0, 4, 5, 1}
	MoveZero(arr)
	fmt.Println(arr)
}
