package main

import (
	"fmt"
	"os"
	"strconv"
)

var pc[256] byte // 256 - потому что это максимальное число, которое может быть представлено с помощью байта

func init() {
    for i := range pc { // здесь мы опустили получение значения, нас интересует только индекс
        pc[i] = pc[i/2] + byte(i&1)
    }
}

// PopCount возвращает степень заполнения -
// количество установленных битов значения x
func PopCount(x uint64) int {
    return int(pc[byte(x>>(0*8))] +
               pc[byte(x>>(1*8))] +
               pc[byte(x>>(2*8))] +
               pc[byte(x>>(3*8))] +
               pc[byte(x>>(4*8))] +
               pc[byte(x>>(5*8))] +
               pc[byte(x>>(6*8))] +
               pc[byte(x>>(7*8))])
}

func main() {
	for _, arg := range os.Args[1:] {
		u, err := strconv.ParseUint(arg, 10, 64)
		if err != nil {
			fmt.Fprintf(os.Stderr, "[%s] unable to convert \"%s\" to uint64: %v !\n", os.Args[0], arg, err)
			os.Exit(1)
		}
		fmt.Printf("Number of bits in \"%d\" number equals: %d\n", u, PopCount(u))
	}
}