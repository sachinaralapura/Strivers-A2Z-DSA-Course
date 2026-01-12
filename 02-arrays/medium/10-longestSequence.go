package main

import "fmt"

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

func LongestSequence(arr []int) int {
	set := make(Set[int])
	max := 0
	for _, v := range arr {
		set.Add(v)
	}

	for i := 0; i < len(arr); i++ {
		if !set.Contains(arr[i] - 1) {
			count := 1
			x := arr[i]
			for set.Contains(x + 1) {
				x = x + 1
				count++
			}
			if count > max {
				max = count
			}
		}
	}
	return max
}

func main() {
	arr := []int{1, 1, 2, 3, 101, 1, 100, 4, 102}
	res := LongestSequence(arr)
	fmt.Println(res)
}
