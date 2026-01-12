package main

import (
	"fmt"
)

func LongestSubarraySum(arr []int, k int) int {
	n := len(arr)
	left := 0
	right := 0
	sum := arr[0]
	max := 0
	for right < n {
		for sum > k && left <= right {
			sum -= arr[left]
			left++
		}

		if sum == k {
			if max < right-left+1 {
				max = right - left + 1
			}
		}
		right++
		if right < n {
			sum += arr[right]
		}
	}
	return max
}

func LongestSubarraySumPrefix(arr []int, k int) int {
	n := len(arr)
	var sum int64 = 0
	max := 0
	prefixSum := make(map[int64]int)

	for i := 0; i < n; i++ {
		sum += int64(arr[i])
		if sum == int64(k) && max < i+1 {
			max = i + 1
		}
		var rem int64 = sum - int64(k)
		if index, ok := prefixSum[rem]; ok {
			if max < i-index {
				max = i - index
			}
		}
		if _, ok := prefixSum[sum]; !ok {
			prefixSum[sum] = i
		}
	}
	return max
}

func main() {
	arr := []int{10, 5, 2, 7, 1, 9}
	res := LongestSubarraySumPrefix(arr, 15)
	fmt.Println(res)
}
