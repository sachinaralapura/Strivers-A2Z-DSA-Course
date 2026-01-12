package main

import "fmt"

func ZeroOneTwoCount(arr []int) {
	n := len(arr)
	l := 0
	m := 0
	h := n - 1

	for m <= h {
		if arr[m] == 0 {
			arr[l], arr[m] = arr[m], arr[l]
			m++
			l++
		} else if arr[m] == 1 {
			m++
		} else {
			arr[m], arr[h] = arr[h], arr[m]
			h--
		}

	}
}

func main() {
	arr := []int{2, 1, 1, 0, 0, 2, 1, 1, 2, 0, 1, 2, 2}
	ZeroOneTwoCount(arr)
	fmt.Println(arr)
}
