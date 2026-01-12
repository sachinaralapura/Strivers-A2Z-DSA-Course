package main

import "fmt"

func partition(arr []int, low int, high int) int {
	pivot := arr[low]
	i := low
	j := high
	for i < j {
		for arr[i] <= pivot && i <= high-1 {
			i++
		}
		for arr[j] >= pivot && j >= low+1 {
			j--
		}
		if i < j {
			arr[i], arr[j] = arr[j], arr[i]
		}
	}
	arr[low], arr[j] = arr[j], arr[low]
	return j
}

func QuickSort(arr []int, low int, high int) {
	if low < high {
		pivot := partition(arr, low, high)
		QuickSort(arr, low, pivot-1)
		QuickSort(arr, pivot+1, high)
	}
}

func main() {
	arr := []int{13, 46, 24, 52, 20, 0, -1, 1, 2, 4, 34, 344, 9}
	QuickSort(arr, 0, len(arr)-1)
	fmt.Print(arr)
}
