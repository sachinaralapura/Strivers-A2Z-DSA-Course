package main

import "fmt"

func RemoveDuplicateSorted(arr []int) int {
	ptr := 0
	for i := range arr {
		if arr[ptr] != arr[i] {
			ptr++
			arr[ptr] = arr[i]
		}
	}
	return ptr + 1
}

func main() {
	arr := []int{1, 1, 2, 2, 3, 3, 4, 5, 5, 6}
	n := RemoveDuplicateSorted(arr)
	fmt.Print(arr[:n])
}
