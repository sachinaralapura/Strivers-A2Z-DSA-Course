package main

import "fmt"

func reverse(arr []int) {
	i := 0
	j := len(arr) - 1
	for i < j {
		arr[i], arr[j] = arr[j], arr[i]
		i++
		j--
	}
}

func NextPermutation(arr []int) bool {
	n := len(arr)
	dip_index := -1

	for i := n - 2; i >= 0; i-- {
		if arr[i] < arr[i+1] {
			dip_index = i
			break
		}
	}

	if dip_index == -1 {
		reverse(arr[0:])
		return false
	}

	// find least great index that is after dip_index;
	for i := n - 1; i > dip_index; i-- {
		if arr[i] > arr[dip_index] {
			arr[i], arr[dip_index] = arr[dip_index], arr[i]
			break
		}
	}
	// reverse from dip_index + 1 to last
	reverse(arr[dip_index+1:])
	return true
}

func main() {
	arr := []int{2, 1, 5, 4, 3, 0, 0}
	NextPermutation(arr)
	fmt.Println(arr)

	arr = []int{1, 2, 3, 4, 5, 6}
	for NextPermutation(arr) {
		fmt.Println(arr)
	}
}
