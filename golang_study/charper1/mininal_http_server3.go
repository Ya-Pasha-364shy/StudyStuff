// эта программа показывает минимальный HTTP-сервер, способный отвечать на
// запросы клиентов по методу GET.
// ВАЖНО: каждая функция-обработчик запускается в отдельном потоке (go-подпрограмме). Сколько одновременных запросов, столько же и потоков (go-подпрограмм)

package main

import (
	"fmt"
	"log"
	"net/http"
	"sync"
	"os"
)

var mutex sync.Mutex
var count uint

func main() {
	fmt.Println("Server in the listen state")

	http.HandleFunc("/", handler) // каждый запрос вызывает обработчик коллбеком - связываем handler с входящим URL, который начинается с  "/"
	http.HandleFunc("/count", count_handler)
	log.Fatal(http.ListenAndServe("localhost:8000", nil)) // запускаем сервер, прослушивающий порт 8000 в ожидании входящих запросов
}

// обработчик возвращает компонент пути из URL запроса
func handler(w http.ResponseWriter, r *http.Request) {
	mutex.Lock()
	count++
	mutex.Unlock()
	fmt.Fprintf(w, "%s %s %s\n", r.Method, r.URL, r.Proto)
	for k, v := range r.Header {
		fmt.Fprintf(w, "\tHeader[%q] = %q\n", k, v)
	}
	fmt.Fprintf(w, "Host = %q\n", r.Host)
	fmt.Fprintf(w, "RemoteAddr = %q\n", r.RemoteAddr)
	// объединение переменной, вложенной в if уменьшает область видимости переменной "err"
	if err := r.ParseForm(); err != nil {
		log.Print(err)
		os.Exit(0)
	}
	for k, v := range r.Form {
		fmt.Fprintf(w, "Form[%q] = %q\n", k, v)
	}
}

func count_handler(w http.ResponseWriter, r *http.Request) {
	mutex.Lock()
	fmt.Fprintf(w, "counter = %d\n", count)
	mutex.Unlock()
}