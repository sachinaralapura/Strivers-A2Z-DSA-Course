package main

func arrange(arr []int) {
	n := len(arr)
	np := 0
	nn := 0
	curr := true
	i := 0

	for i < n {
		for k := i; k < n; k++ {
			if arr[k] > 0 {
				np = k
				break
			}
		}
		for k := i; k < n; k++ {
			if arr[k] < 0 {
				nn = k
				break
			}
		}

		if curr && arr[i] < 0 {
			arr[i], arr[np] = arr[np], arr[i]
			i += 1
			curr = !curr
			continue
		}

		if !curr && arr[i] > 0 {
			arr[i], arr[nn] = arr[nn], arr[i]
			i += 1
			curr = !curr
			continue
		}
		i++
		curr = !curr
	}
}
