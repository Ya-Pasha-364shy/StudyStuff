package main

import (
	"os"
	"fmt"
	// "charper5/html"
	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
	fmt.Fprintf(os.Stderr, "outline: %v\n", err)
		os.Exit(1)
	}

	outline(nil, doc)
}

func outline(stack []string, n *html.Node) []string {
	// hte
	if n.Type == html.ElementNode {
		stack = append(stack, n.Data) // Внесение дескриптора в стек
		fmt.Println(stack)
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		/**
		 * Обратите внимание на одну тонкость: хотя outline “заталкивает” элемент в
		   stack, соответствующей функции для снятия элемента со стека нет. Когда функ­
		   ция outline рекурсивно вызывает саму себя, вызываемая функция получает копию
		   stack. Хотя вызываемая функция может добавлять элементы в этот срез, изменяя ба­
		   зовый массив, и, возможно, даже выделяет новый массив, она не изменяет исходные
		   элементы, видимые вызывающей функции. Поэтому при возврате из функции stack
		   вызывающей функции остается таким же, как и до вызова
		*/
		outline(stack, c)
	}
	return stack
}