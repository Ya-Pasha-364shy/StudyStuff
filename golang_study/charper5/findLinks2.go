package main

import (
	"os"
	"fmt"
	// "charper5/html"
	"golang.org/x/net/html"
)

func main() {
	// используется под pipe-ом
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "findlinks1: %v\n", err)
		os.Exit(1)
	}
	for _, link := range visit(nil, doc) {
		fmt.Println(link)
	}
}

// visit добавляет в links все ссылки,
// найденные в п, и возвращает результат.
func visit(links []string, n *html.Node) []string {
	// рекурсивный случай
	if n.Type == html.ElementNode && n.Data == "a" {
		for _, a := range n.Attr {
			if a.Key == "href" {
				links = append(links, a.Val)
			}
		}
	}

	// сначала детей всех
	if n.FirstChild != nil {
		links = visit(links, n.FirstChild)
	}
	// каждый ребенок смотрит своего соседа
	if n.NextSibling != nil {
		links = visit(links, n.NextSibling)
	}
	return links
}