package main

import (
	"fmt"
	"os"
	"strconv"
	"charper2/tempconv"
)

func main() {
	for _, arg := range os.Args[1:] {
		t, err := strconv.ParseFloat(arg, 64)
		if err != nil {
			fmt.Fprintf(os.Stderr, "[%s] error: %v\n", os.Args[0], err)
			os.Exit(1)
		}
		// преобразовываем переменную t к типам Fahrenheit, Celsius, Kelvin соотвественно
		f := tempconv.Fahrenheit(t)
		c := tempconv.Celsius(t)
		k := tempconv.Kelvin(t)

		// здесь используются методы, которые перегружают вывод так, что добавляют суффиксы °C, °F, °K соотвественно
		fmt.Printf("%s = %s, %s = %s, %s = %s\n", c, tempconv.CToK(c), f, tempconv.FToC(f), k, tempconv.KToC(k))
	}
}