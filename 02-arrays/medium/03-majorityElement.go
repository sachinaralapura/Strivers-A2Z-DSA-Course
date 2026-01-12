package main

import "fmt"

func MajorityElement(arr []int) int {
	element := arr[0]
	count := 0

	for i := 0; i < len(arr); i++ {
		if arr[i] == element {
			count++
		} else {
			count--
		}

		if count == 0 {
			count = 1
			element = arr[i]
		}
	}
	return element
}
func main() {
	arr := []int{2, 3, 3, 2, 1, 1, 3, 1, 2, 3, 2, 3, 3}
	res := MajorityElement(arr)
	fmt.Println(res)
}
