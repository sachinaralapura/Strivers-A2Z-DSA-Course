package main

import "fmt"

func Bubble(arr []int) {
	n := len(arr)
	for i := n - 1; i >= 0; i-- {
		swap := false
		for j := 0; j < i; j++ {
			if arr[j] > arr[j+1] {
				arr[j], arr[j+1] = arr[j+1], arr[j]
				swap = true
			}
		}
		if !swap {
			break
		}
	}
}

func main() {
	arr := []int{13, 46, 24, 52, 20, 9}
	Bubble(arr)
	fmt.Print(arr)
}
