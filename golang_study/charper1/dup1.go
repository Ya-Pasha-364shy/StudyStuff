// поиск повторяющихся строк

package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	counts := make(map[string]int) // инициализруем хэш-таблицу string:int
	input  := bufio.NewScanner(os.Stdin) // инициализируем некоторый сканнер
	for input.Scan() != false { // пока есть входящие строки, Сканер считает эту строку и удалит символ перевода строки
		if input.Text() == "" {
			break
		} else {
			counts[input.Text()]++
			// можно было бы заменить инструкцию выше на следующие две:
			// line := input.Text()
			// counts[line] = counts[line] + 1
		}
	}
	for line, n := range counts {
		if n > 1 {
			fmt.Printf("%d\t%s\n", n, line)
		}
	}
}