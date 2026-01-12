package main

import "fmt"

func Insertion(arr []int) {
	n := len(arr)
	for i := 1; i < n; i++ {
		j := i
		for {
			if arr[j] < arr[j-1] {
				arr[j], arr[j-1] = arr[j-1], arr[j]
			} else {
				break
			}
			j--
			if j <= 0 {
				break
			}
		}
	}
}

func main() {
	arr := []int{14, 9, 15, 12, 6, 8, 13}
	Insertion(arr)
	fmt.Print(arr)
}
