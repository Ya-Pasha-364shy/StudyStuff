// программа проверяет, были ли указаны аргументы командной строки
// если да, то считывает файлы и находит в них число повторяющихся строк, запоминая каждую строку и её число повторений
// если нет, то считывает строки из стандартного потока ввода Stdin и делает всё то же самое, что с файлами.

package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	counts := make(map[string]int)
	files_counts := make(map[string]int) // если используется анализ файлов, имена которых переданы с помощью параметров cmd, то используется эта функция

	if len(os.Args[1:]) == 0 {
		// если аргументов командной строки нет, то мы ожидаем ввод из stdin
		countLines(os.Stdin, counts, "", files_counts)
	} else {
		// если аргументы есть - значит файлы указаны, мы открываем каждый файл и заполяем хэш-таблицу (отображение)
		for _, arg := range os.Args[1:] {
			f, err := os.Open(arg) // os.Open возвращает два значения - это сам открытый файл, из которого мы дальше читаем и код ошибки
			if err != nil {
				fmt.Fprintf(os.Stderr, "[%s] error: %v\n", os.Args[0], err) // "%v" преобразовывает значение ошибки в текст
				continue
			}
			countLines(f, counts, arg, files_counts)
			f.Close()
		}
	}

	if len(files_counts) != 0 {
		for filename, dups := range files_counts {
			fmt.Printf("%s:\t%d\n", filename, dups) // печатает совокупное количество строк-дубликатов в файле, а также анализирует, есть ли такие строки в предыдущих файлах
		}
	} else {
		for str, n := range counts {
			if n > 1 {
				fmt.Printf("%d\t%s\n", n, str)
			}
		}
	}
}

func countLines(f *os.File, counts map[string]int, filename string, files_counts map[string]int) {

	if filename == "" {
		input := bufio.NewScanner(f)
		for input.Scan() { // пока не EOF (Ctrl+D)
			if input.Text() == "" { // или пока не выполняется это условие
				continue
			}
			counts[input.Text()]++ // считаем число строк
		}
	} else {
		input := bufio.NewScanner(f)
		for input.Scan() {
			if input.Text() == "" { // или пока не выполняется это условие
				continue
			}
			counts[input.Text()]++
			if counts[input.Text()] > 1 {
				files_counts[filename]++
			}
		}
	}
}
