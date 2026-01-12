package main

import "fmt"

func nCr(n, r int) int64 {
	var res int64 = 1
	for i := 0; i < r; i++ {
		res = res * int64((n - i))
		res = res / int64((i + 1))
	}
	return res
}

func PascalTriangleRow(n int, ch chan<- int64) {
	for i := 1; i <= n; i++ {
		// fmt.Print(nCr(n-1, i-1), " ")
		ch <- nCr(n-1, i-1)
	}
}

func main() {
	n := 10
	for i := 0; i < n; i++ {
		ch := make(chan int64)
		go PascalTriangleRow(i, ch)
		for range i {
			fmt.Print(<-ch, " ")
		}
		fmt.Println()
	}
}
