// данная программа делает GET-запрос на сразу несколько url-адресов.
// Также осуществляет запись в канал синхронно благодаря блокирующему механизму канала (chan) 

package main

import (
	"fmt"
	"io"
	// "io/ioutil"
	"net/http"
	"os"
	"time"
	"strings"
)

func main() {
	start := time.Now()
	ch    := make(chan string) // чан - двусторонний блокирующий канал, позволяет синхронно читать только после записи.
								// он также блокирует остальные подпрограммы на запись до тех пор, пока данные не будут прочитаны
	for _, url := range os.Args[1:] {
		if false == strings.HasPrefix(url, "http://") {
			url = "http://" + url
		}
		go fetch(url, ch)      // инструкция go запускает подпрограмму в новой ните исполнения
	}
	for range os.Args[1:] {
		fmt.Println(<-ch) // читаем из канала - даём какой-то из остального количество подропрограмм записать своё
	}
	fmt.Printf("%.2fsec elapsed\n", time.Since(start).Seconds())
}

func fetch(url string, ch chan<- string) {
	start := time.Now()
	resp, err := http.Get(url) // делает GET запрос к заданному адресу и при отсутствии ошибок возвращает нам ответ
	if err != nil {
		fmt.Fprintf(os.Stderr, "[%s] error#1: %v", os.Args[0], err)
		return
	}

	f, err := os.OpenFile("http_fetchall_rs.txt", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		fmt.Fprintf(os.Stderr, "[%s] error#2: %v", os.Args[0], err)
		return
	} 

	nbytes, err := io.Copy(f, resp.Body)
	resp.Body.Close()
	f.Close()

	if err != nil {
		ch <- fmt.Sprintf("[%s] while reading %s: %v", os.Args[0], url, err)
		return
	}
	secs := time.Since(start).Seconds()
	ch <- fmt.Sprintf("%.2fsec %7d %s", secs, nbytes, url)
}