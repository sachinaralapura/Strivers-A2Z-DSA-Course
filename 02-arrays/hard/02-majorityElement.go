package main

import "fmt"

func MajorityElements(arr []int) (int, int) {
	mpp := make(map[int]int)
	mini := (len(arr) / 3) + 1
	res := make([]int, 0, 2)
	for _, v := range arr {
		mpp[v] += 1
		if mpp[v] == mini {
			res = append(res, v)
		}
		if len(res) > 2 {
			break
		}
	}
	return res[0], res[1]
}

func main() {
	arr := []int{11, 33, 33, 11, 33, 11}
	i, j := MajorityElements(arr)
	fmt.Println(i)
	fmt.Println(j)
}
