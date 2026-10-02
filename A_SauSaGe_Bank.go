package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var t int
	if _, err := fmt.Fscan(reader, &t); err != nil {
		return
	}

	for i := 0; i < t; i++ {
		var n, k int
		fmt.Fscan(reader, &n, &k)
		ans := (int64(1) << (n - k + 1)) + int64(2*(k-1))
		fmt.Fprintln(writer, ans)
	}
}
