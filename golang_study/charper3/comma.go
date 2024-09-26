// comma вставляет запятые в строковое представление неотрицательного десятичного числа
package main

import (
	"fmt"
	"bytes"
)

func comma(s string) string {
	n := len(s)
	if n <= 3 {
		return s
	} else {
		return comma(s[:n-3]) + "," + s[n-3:]
	}
}

func commaNoRecursive(s string) string {
	var sign byte
	var float_point_exists, sign_exists bool
	var tmp_idx, float_point_index int
	var buf bytes.Buffer
	n := len(s)

	// check on float point or sign in number as string
	for i := 0; i < n; i++ {
		if s[i] == '.' {
			float_point_exists = true
			float_point_index = i
			break
		}
	}
	if s[0] == '+' || s[0] == '-' {
		sign = s[0]
		sign_exists = true

		s = s[1:]
		n -= 1
	}

	if float_point_exists {
 		n -= len(s[float_point_index:])
	}

	if n % 3 == 0 {
		if sign_exists {
			buf.WriteByte(sign)
		}

		for idx := 0; idx < n; idx++ {
			buf.WriteByte(byte(s[idx]))
			tmp_idx = idx+1
			if tmp_idx % 3 == 0 && tmp_idx != n {
				buf.WriteByte(',')
			}
		}
	} else {
		var tmp_string string
		for i := n-1; i >= 0; i-- {
			tmp_string += string(s[i])
		}
		for idx, symbol := range tmp_string {
			buf.WriteByte(byte(symbol))
			tmp_idx = idx+1
			if tmp_idx % 3 == 0 && tmp_idx != n {
				buf.WriteByte(',')
			}
		}
		tmp_string = buf.String()
		buf.Truncate(0)
		if sign_exists {
			buf.WriteByte(sign)
		}
		for i := len(tmp_string)-1; i >= 0; i-- {
			buf.WriteByte(tmp_string[i])
		}
	}

	if float_point_exists {
		buf.WriteString(s[float_point_index:])
	}

	return buf.String()
}



func main() {
	test1 := "123456781231231243"
	fmt.Println(comma(test1))
	fmt.Println(commaNoRecursive(test1))

	test2 := "1234.5655"
	fmt.Println(commaNoRecursive(test2))

	test3 := "112134.564"
	fmt.Println(commaNoRecursive(test3))

	test4 := "+.112134564"
	fmt.Println(commaNoRecursive(test4))

	test5 := "+12345678.112134564"
	fmt.Println(commaNoRecursive(test5))

	test6 := "-123456789.112134564"
	fmt.Println(commaNoRecursive(test6))

	// another stuff
	s := "abc"
	b := []byte(s) 
	fmt.Println(b) // [97 98 99]
	s2 := string(b) 
	fmt.Println(s2) // abc
}