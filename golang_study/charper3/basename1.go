/**
 * basename1 убирает компоненты каталога и расширение файла
 * a => a; a.go => a; a/b/c.go => c, a/b.c.go => b.c
*/
package main

import (
	"fmt"
	"strings"
)

func basename(s string) string {
	// отбрасываем последний символ '/' и суффикс типа файла 
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == '/' {
			s = s[i+1:]
			break
		}
	}
	// сохраняем всё до последней точки
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == '.' {
			s = s[:i]
			break
		}
	}
	return s
}

// эта функция делает то же самое, что и функция выше, но
// с той особенностью, что она использует библиотечные функции
func basenameLib(s string) string {
	slash := strings.LastIndex(s, "/") // -1, если слэш не найден
	s = s[slash+1:]
	if dot := strings.LastIndex(s, "."); dot >= 0 {
		s = s[:dot]
	}
	return s
}

func main() {
	if basename("/home/k1r4/.ssh/id_rsa.pub") == "id_rsa" {
		fmt.Println("\"/home/k1r4/.ssh/id_rsa.pub\" => \"id_rsa\"")
	}

	if (basenameLib("/home/k1r4/nginx_build.sh") == "nginx_build") {
		fmt.Println("\"/home/k1r4/nginx_build.sh\" => \"nginx_build\"")
	}
}