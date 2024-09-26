// программа, печатающая строки командной строки через ForEach

package main

import (
	"fmt"
	"os"
)

func main() {
	var s, sep string
	for _, arg := range os.Args[1:] { // range производит пару значений: индекс и значение элемента с этим индексом
		s += sep + arg
		sep = " "
	}
	fmt.Println(s)
}