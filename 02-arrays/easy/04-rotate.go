package main

import "fmt"

func RotateLeft(arr []int) {
	first := arr[0]
	n := len(arr)
	for i := 0; i < n-1; i++ {
		arr[i] = arr[i+1]
	}
	arr[n-1] = first
}

func RotateKRight(arr []int, k int) {
	n := len(arr)
	k = k % n
	if k == 0 {
		return
	}
	temp := make([]int, 0, k)
	for _, ele := range arr[n-k:] {
		temp = append(temp, ele)
	}
	for i := n - k - 1; i >= 0; i-- {
		arr[i+k] = arr[i]
	}
	for i := range k {
		arr[i] = temp[i]
	}
}

func RotateKRightOpt(arr []int, k int) {
	n := len(arr)
	k = k % n
	if k == 0 {
		return
	}
	reverse(arr)
	reverse(arr[0:k])
	reverse(arr[k:])
}

func reverse(arr []int) {
	i := 0
	j := len(arr) - 1
	for i < j {
		arr[i], arr[j] = arr[j], arr[i]
		i++
		j--
	}
}

func main() {
	arr := []int{1, 2, 3, 4, 5, 6}
	k := 2
	RotateKRightOpt(arr, k)
	fmt.Println(arr)
}
