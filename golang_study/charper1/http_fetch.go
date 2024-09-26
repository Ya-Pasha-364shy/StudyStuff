// данная программа делает GET-запрос на указанный URL и выводит содержимое HTML, как curl

package main

import (
	"fmt"
	"io/ioutil"
	// "io"
	"net/http"
	"os"
	"strings"
)

func main() {
	for _, url := range os.Args[1:] {

		if false == strings.HasPrefix(url, "http://") {
			url = "http://" + url
		}

		resp, err := http.Get(url) // делает GET запрос к заданному адресу и при отсутствии ошибок возвращает нам ответ
		if err != nil {
			fmt.Fprintf(os.Stderr, "[%s] error1: %v", os.Args[0], err)
			continue;
		}
		b, err := ioutil.ReadAll(resp.Body) // считваем весь результат из resp, оохраняем прочитанное в последовательность байт
		resp.Body.Close()
		if err != nil {
			fmt.Fprintf(os.Stderr, "[%s] error2: %v", os.Args[0], err)
			os.Exit(1)
		}
		fmt.Printf("%s\n", b) // печатаем ответ-набор байт как строку 
		fmt.Printf("STATUS: %s\n", resp.Status)

		// _, err = io.Copy(os.Stdout, resp.Body)
		// if err != nil {
		// 	fmt.Fprintf(os.Stderr, "[%s] error2: %v", os.Args[0], err)
		// 	os.Exit(1)
		// }
	}
}