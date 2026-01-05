package main

import (
	"fmt"
	"strings"
)

func reverseSentenceShort(s string) string {
	words := strings.Fields(s)                            // Step 1
	for i, j := 0, len(words)-1; i < j; i, j = i+1, j-1 { // Step 2
		words[i], words[j] = words[j], words[i] // Step 3
	}
	return strings.Join(words, " ") // Step 4
}

func main() {
	input := "hello world this is golang"
	result := reverseSentenceShort(input)
	fmt.Println(result)
}
