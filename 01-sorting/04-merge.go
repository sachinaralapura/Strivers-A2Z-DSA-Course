package main

import "fmt"

func merge(arr []int, low int, mid int, high int) {
	var temp []int
	left := low
	right := mid + 1

	for left <= mid && right <= high {
		if arr[left] <= arr[right] {
			temp = append(temp, arr[left])
			left++
		} else {
			temp = append(temp, arr[right])
			right++
		}
	}
	for left <= mid {
		temp = append(temp, arr[left])
		left++
	}
	for right <= high {
		temp = append(temp, arr[right])
		right++
	}
	for i := low; i <= high; i++ {
		arr[i] = temp[i-low]
	}
}

func MergeSort(arr []int, low int, high int) {
	if low >= high {
		return
	}
	mid := (low + high) / 2
	MergeSort(arr, low, mid)
	MergeSort(arr, mid+1, high)
	merge(arr, low, mid, high)
}

func main() {
	arr := []int{13, 46, 24, 52, 20, 0, -1, 1, 2, 4, 34, 344, 9}
	MergeSort(arr, 0, len(arr)-1)
	fmt.Print(arr)
}
