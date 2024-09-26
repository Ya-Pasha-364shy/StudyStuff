// эта программа показывает минимальный HTTP-сервер, способный отвечать на
// запросы клиентов по методу GET.
// ВАЖНО: каждая функция-обработчик запускается в отдельном потоке (go-подпрограмме). Сколько одновременных запросов, столько же и потоков (go-подпрограмм)

package main

import (
	"fmt"
	"log"
	"net/http"
	"sync"
)

var mutex sync.Mutex
var count uint

func main() {
	http.HandleFunc("/", handler) // каждый запрос вызывает обработчик коллбеком - связываем handler с входящим URL, который начинается с  "/"
	http.HandleFunc("/count", count_handler)
	log.Fatal(http.ListenAndServe("localhost:8000", nil)) // запускаем сервер, прослушивающий порт 8000 в ожидании входящих запросов
}

// обработчик возвращает компонент пути из URL запроса
func handler(w http.ResponseWriter, r *http.Request) {
	mutex.Lock()
	count++
	mutex.Unlock()
	fmt.Fprintf(w, "URL.Path = %q\n", r.URL.Path)
}

func count_handler(w http.ResponseWriter, r *http.Request) {
	mutex.Lock()
	fmt.Fprintf(w, "counter = %d\n", count)
	mutex.Unlock()
}