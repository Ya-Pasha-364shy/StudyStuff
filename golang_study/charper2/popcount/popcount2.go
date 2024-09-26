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

// упражнение 2.3: через цикл

// PopCount возвращает степень заполнения -
// количество установленных битов значения x
/*
func PopCount(x uint64) int {
	var count int 
	for i := 0; i < 8; i++ {
		count += int(pc[byte(x>>(i*8))])
	}
	return count
}
*/

// упражнение 2.4: через сдвиг аргумента по всем 64 позициям
/*
func PopCount(x uint64) int {
	var sum int 
	for i := 0; i < 64; i++ {
		sum += int((x >> i) & 1)
	}
	return sum
}
*/

// упражнение 2.5: через сброс крайнего правого бита посредством выражения x & (x - 1)
func PopCount(x uint64) int {
	var sum int;
	for i := 0; i < 64; i++ {
		if x & (x - 1) != 0 || x & 1 != 0 {
			sum++
		}
		x >>= 1
	}
	return sum
}

/*
 TODO: оценить производительность каждого из методов
*/

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