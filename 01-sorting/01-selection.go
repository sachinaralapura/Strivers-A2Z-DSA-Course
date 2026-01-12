package main

import "fmt"

func SelectionSort(arr []int) {
	n := len(arr)
	for i, _ := range arr {
		min := i
		// find min element
		for j := i + 1; j < n; j++ {
			if arr[j] < arr[min] {
				min = j
			}
		}
		arr[i], arr[min] = arr[min], arr[i]
	}
}

func main() {
	arr := []int{4, 2, 1, 6, 3, 5}
	SelectionSort(arr)
	fmt.Print(arr)
}
