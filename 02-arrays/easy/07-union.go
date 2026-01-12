package main

import "fmt"

type Set[T comparable] map[T]struct{}

func (s Set[T]) Add(v T) {
	s[v] = struct{}{}
}

// func (s Set[T]) Delete(v T) {
// 	delete(s, v)
// }

// func (s Set[T]) Contains(v T) bool {
// 	_, ok := s[v]
// 	return ok
// }

func Union[T comparable](arr1, arr2 []T) []T {
	set := make(Set[T])
	arr := make([]T, 0)
	for _, i := range arr1 {
		set.Add(i)
	}
	for _, i := range arr2 {
		set.Add(i)
	}

	for v := range set {
		arr = append(arr, v)
	}
	return arr
}

func main() {
	arr1 := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	arr2 := []int{7, 8, 9, 10, 11, 12}
	res := Union[int](arr1, arr2)
	fmt.Println(res)
}
