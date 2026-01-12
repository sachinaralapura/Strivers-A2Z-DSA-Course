package main

import "fmt"

func MissingBinarySearch(arr []int) int {
	a := arr[0]
	n := len(arr)

	d := (arr[n-1] - a) / n
	low := 0
	high := n - 1

	for low <= high {
		mid := (low + high) / 2
		if arr[mid]-arr[mid-1] != d {
			return arr[mid] - d // arr[mid -1] + d;
		} else if arr[mid+1]-arr[mid] != d {
			return arr[mid] + d
		} else if (a + arr[mid]*d) < arr[mid] {
			high = mid - 1
		} else {
			low = mid + 1
		}
	}
	return -1
}

func main() {
	arr := []int{2, 4, 6, 10, 12, 14}
	res := MissingBinarySearch(arr)
	fmt.Println(res)
}
