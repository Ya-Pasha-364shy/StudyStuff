package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"unicode"
)

// 4.8 - измените charcount так, чтобы программа подсчитывала коли­чество букв, цифр и
//       прочих категорий Unicode с использованием функций наподобие Unicode.IsLetter.

func main() {
	var invalid int
	numbers := make(map[rune]int)
	letters := make(map[rune]int)
	spaces  := make(map[rune]int)

	in := bufio.NewReader(os.Stdin)
	for {
		r, n, err := in.ReadRune() // возврат руны, числа байт руны, ошибки
		if err == io.EOF {
			break
		} else if err != nil {
			fmt.Fprintf(os.Stderr, "charcount: %v\n", err)
			os.Exit(1)
		}
		if r == unicode.ReplacementChar && n == 1 {
			invalid++
			continue
		}
		
		if unicode.IsNumber(r) {
			numbers[r]++
		} else if unicode.IsLetter(r) {
			letters[r]++
		} else if unicode.IsSpace(r) {
			spaces[r]++
		}
	}
	fmt.Printf("numbers\tcount\n")
	for c, n := range numbers {
		fmt.Printf("%q\t%d\n", c, n)
	}
	fmt.Printf("letters\tcount\n")
	for c, n := range letters {
		fmt.Printf("%q\t%d\n", c, n)
	}
	fmt.Printf("spaces\tcount\n")
	for c, n := range spaces {
		fmt.Printf("%q\t%d\n", c, n)
	}

	if invalid > 0 {
		fmt.Printf("\n%d неверных символов UTF-8\n", invalid)
	}
}