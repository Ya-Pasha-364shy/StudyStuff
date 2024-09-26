// эта программа показывает минимальный HTTP-сервер, способный отвечать на
// запросы клиентов по методу GET

package main

import (
	"fmt"
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/", handler) // каждый запрос вызывает обработчик коллбеком - связываем handler с входящим URL, который начинается с  "/"
	log.Fatal(http.ListenAndServe("localhost:8000", nil)) // запускаем сервер, прослушивающий порт 8000 в ожидании входящих запросов
}

// обработчик возвращает компонент пути из URL запроса
func handler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "URL.Path = %q\n", r.URL.Path) // делает эхо ответ
}