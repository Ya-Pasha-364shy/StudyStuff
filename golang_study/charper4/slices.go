package main

import (
	"fmt"
)

/*
 * nonempty возвращает срез, содержащий только непустые строки
 * содержимое базового массива меняется.
*/
func nonempty(strings []string) []string {
	i := 0
	for _, s := range strings {
		if s != "" {
			strings[i] = s;
			i++
		}
	}
	return strings[:i]
}

/*
 * nonempty2 не изменяет базовый срез
*/
func nonempty2(strings []string) []string {
	out := strings[:0]
	for _, s := range strings {
		if s != "" {
			out = append(out, s)
		}
	}
	return out
}

func main() {
	data := []string{"one", "", "three"}
	fmt.Printf("[nonempty] result = %q; base = %q\n", nonempty(data), data)

	another := []string{"two", "fourth", ""}
	fmt.Printf("[nonempty2] result = %q; another = %q\n", nonempty2(another), another)
}