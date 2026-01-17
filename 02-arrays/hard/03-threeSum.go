package main

import (
	"fmt"
	"slices"
)

type Set[T comparable] map[T]struct{}

func (s Set[T]) Add(v T) {
	s[v] = struct{}{}
}

func (s Set[T]) Delete(v T) {
	delete(s, v)
}

func (s Set[T]) Contains(v T) bool {
	_, ok := s[v]
	return ok
}

func ThreeSumHash(arr []int) [][]int {
	n := len(arr)
	res := make([][]int, 0)
	for i := 0; i < n; i++ {
		set := make(Set[int])
		for j := i + 1; j < n; j++ {
			thrid := -(arr[i] + arr[j])
			if set.Contains(thrid) {
				temp := []int{arr[i], arr[j], thrid}
				slices.Sort(temp)
				res = append(res, temp)
			}
			set.Add(arr[j])
		}
	}
	return res
}

func ThreeSumTwoPointer(arr []int) [][]int {
	n := len(arr)
	res := make([][]int, 0)
	slices.Sort(arr)
	for i := 0; i < n; i++ {
		if i > 0 && arr[i] == arr[i-1] {
			continue
		}
		j := i + 1
		k := n - 1

		for j < k {
			sum := arr[i] + arr[j] + arr[k]
			if sum > 0 {
				k--
			} else if sum < 0 {
				j++
			} else {
				temp := []int{arr[i], arr[j], arr[k]}
				res = append(res, temp)
				j++
				k--
				for j < k && arr[j-1] == arr[j] {
					j++
				}
				for j < k && arr[k] == arr[k+1] {
					k--
				}
			}
		}
	}
	return res
}

func main() {
	arr := []int{-1, 0, 1, 2, -1, -4}
	res := ThreeSumTwoPointer(arr)
	for _, v := range res {
		fmt.Println(v)
	}
}
