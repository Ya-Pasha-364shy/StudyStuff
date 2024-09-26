/**
 * программа смотрит на строку test и ищет в ней префикс, суффикс и подстроку
*/
package main

import (
	"fmt"
)

func HasPrefix(s, prefix string) bool {
	return len(s) >= len(prefix) && s[:len(prefix)] == prefix
}

func HasSuffix(s, suffix string) bool {
	return len(s) >= len(suffix) && s[len(s) - len(suffix):] == suffix
}

func Contains(s, substr string) bool {
	for i := 0; i < len(s); i++ {
		// первым аргументом в вызов функции мы передаём строковый срез,
		// но несмотря на это, это работает, так как срез трактуется как строка.
		if HasPrefix(s[i:], substr) {
			return true
		}
	}
	return false
}

func main() {
	var test string =  "hello world !"

	if HasPrefix(test, "hello") {
		fmt.Println("\"hello\" is prefix of \"test\" variable !")
	}

	if HasSuffix(test, "!") {
		fmt.Println("\"!\" is suffix of \"test\" variable !")
	}

	if Contains(test, "world !") {
		fmt.Println("\"world !\" is substring of \"test\" variable !")
	}
}