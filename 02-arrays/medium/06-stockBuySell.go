package main

import "math"

func StockBuySell(arr []int) int {
	n := len(arr)
	minPrice := math.MinInt
	maxProfit := 0
	for i := 0; i < n; i++ {
		if minPrice > arr[i] {
			minPrice = arr[i]
		}
		if arr[i]-minPrice > maxProfit {
			maxProfit = arr[i] - minPrice
		}
	}
	return maxProfit
}

func main() {

}
