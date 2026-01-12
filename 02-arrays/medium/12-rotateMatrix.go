package main

import "fmt"

type Matrix[T comparable] [][]T

func RotateMatrix[T comparable](matrix Matrix[T]) Matrix[T] {
	n := len(matrix)
	result := make(Matrix[T], n, n)
	for i := range result {
		result[i] = make([]T, n)
	}
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			result[j][n-i-1] = matrix[i][j]
		}
	}
	return result
}

func RotateMatrixTranspose[T comparable](matrix Matrix[T]) {
	n := len(matrix)
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			temp := matrix[i][j]
			matrix[i][j] = matrix[j][i]
			matrix[j][i] = temp
		}
	}
	for i := 0; i < n; i++ {
		reverse[T](matrix[i])
	}
}

func reverse[T comparable](arr []T) {
	i := 0
	j := len(arr) - 1
	for i < j {
		arr[i], arr[j] = arr[j], arr[i]
		i++
		j--
	}
}

func main() {
	matrix := Matrix[int]{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
	for _, v := range matrix {
		fmt.Println(v)
	}
	res := RotateMatrix(matrix)
	fmt.Println()
	for _, v := range res {
		fmt.Println(v)
	}
	fmt.Println()

	RotateMatrixTranspose(matrix)
	for _, v := range matrix {
		fmt.Println(v)
	}
}
