package main

import "fmt"

// Given an array of size n, write a program to check if the given
// array is sorted in (ascending / Increasing / Non-decreasing) order or not.
// If the array is sorted then return True, Else return False.
func Check(arr []int) bool {
	for i := 1; i < len(arr); i++ {
		if arr[i-1] > arr[i] {
			return false
		}
	}
	return true
}

func main() {
	arr := []int{1, 2, 3, 2, 4, 5, 5, 6}
	fmt.Print(Check(arr))
}
