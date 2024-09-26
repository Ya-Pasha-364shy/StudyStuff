package main

import (
	"fmt"
	"bytes"
)

func intsToString(values []int) string {
	var buf bytes.Buffer
	buf.WriteByte('[')
	for i, v := range values {
		if i > 0 {
			buf.WriteString(", ")
		}
		fmt.Fprintf(&buf, "%d", v)
	}
	buf.WriteByte(']')
	return buf.String()
}


func main() {
	x := []int { 1, 2, 3 }
	fmt.Println(intsToString(x))
}