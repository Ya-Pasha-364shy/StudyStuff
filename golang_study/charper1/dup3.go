// Эта программа производит чтение данных пачкой, затем находит дубликаты и считает количество их повторений

package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func main() {
	counts := make(map[string]int)
	for _, filename := range os.Args[1:] {
		data, err := ioutil.ReadFile(filename) // врзвращает байтовый срез, который можно будет преобразовать к типу 
		if err != nil {
			fmt.Fprintf(os.Stderr, "[%s] error: %v\n", os.Args[0], err)
			continue
		}
		for _, line := range strings.Split(string(data), "\n") {
			counts[line]++
		}
	}
	for str, dups := range counts {
		fmt.Printf("%s:\t%d\n", str, dups)
	}
}