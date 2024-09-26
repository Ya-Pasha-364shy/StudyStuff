package main

import (
	"fmt"
)

/*
 * напишите функцию reverse, которая принимает в качестве параметра - указатель на массив, а не срез
 */
func reverse(s *[5]int) {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
}

/*
 * Напишите функцию, которая без выделения дополнительной па­мяти
 * удаляет все смежные дубликаты в срезе []string.
 */

// "first a fixed"	
// a b a a c c d
// a b d a c c a
// a b d c c a a
// "first b fixed"
// a b d c c a a
// "first d fixed"
// a b d c c a a
// "first c fixed"
// a b d c c a a - произошла замена, невидимая нам, потому что c и c стоят рядом
// "all characters was be fixed" !

func remdup(slice []string) []string {
	var dups_count int
	var slice_length = len(slice)

	for i := 0; i+dups_count < slice_length-1; i++ {
		for j := 0; j < slice_length-dups_count; j++ {
			if i == j {
				continue
			} else if slice[i] == slice[j] {

				dups_count++
				k := slice_length - dups_count
				slice[j], slice[k] = slice[k], slice[j]
			}
		}
	}

	return slice[:slice_length-dups_count]
}

func main() {
	test1 := [...]int{1, 2, 3, 4, 5}
	reverse(&test1)
	fmt.Printf("test1 = %d\n", test1)

	test2 := []string{"hello", "hello", "world"}
	fmt.Println("test2 =", remdup(test2))

	test3 := []string{"a", "b", "a", "a", "c", "c", "d"}
	fmt.Println("test3 =", remdup(test3))

}
