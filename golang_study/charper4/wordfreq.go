// эта программа - часть exercises_maps.go
// вычисляет частоту каждого слова из входного текста

package main

import (
	"os"
	"fmt"
	"bufio"
)

func main() {
	wordfreq := map[string]int{}

	if len(os.Args[1:]) != 0 {
		for _, arg := range os.Args[1:] {
			f, err := os.Open(arg) // os.Open возвращает два значения - это сам открытый файл, из которого мы дальше читаем и код ошибки
			if err != nil {
				fmt.Fprintf(os.Stderr, "[%s] error: %v\n", os.Args[0], err) // "%v" преобразовывает значение ошибки в текст
				continue
			}
			
			input := bufio.NewScanner(f)
			input.Split(bufio.ScanWords)

			for input.Scan() {
				wordfreq[input.Text()]++
			}

			f.Close()
		}
	}
	for word, frequency := range wordfreq {
		fmt.Printf("%s:\t%d\n", word, frequency)
	}
}