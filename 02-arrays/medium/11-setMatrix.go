package main

import "fmt"

func SetMatrix(matrix [][]int) {
	rows := len(matrix)
	cols := len(matrix[0])

	top := make([]int, cols)
	side := make([]int, rows)

	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if matrix[i][j] == 0 {
				side[i] = 1
				top[j] = 1
			}
		}
	}

	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if side[i] == 1 || top[j] == 1 {
				matrix[i][j] = 0
			}
		}
	}

}

func main() {
	matrix := [][]int{
		{1, 1, 1, 1},
		{1, 0, 1, 1},
		{1, 1, 0, 1},
		{1, 1, 0, 1},
		{1, 1, 1, 1},
	}

	SetMatrix(matrix)
	for _, rows := range matrix {
		fmt.Println(rows)
	}
}
