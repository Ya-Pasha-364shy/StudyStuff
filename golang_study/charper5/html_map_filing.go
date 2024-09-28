package main

import (
	"fmt"
	"os"
	"net/http"

	"golang.org/x/net/html"
)

func main() {
	for _, url := range os.Args[1:] {
		err := fetch(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "%s: %v\n", os.Args[0], err)
			continue
		}
	}
}

func fetch(url string) error {
	resp, err := http.Get(url)
	if err != nil {
		return err
	}
	if resp.StatusCode != http.StatusOK {
		resp.Body.Close()
		return fmt.Errorf("получение %s: %s\n", url, resp.Status)
	}
	// *html.Node, error
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return fmt.Errorf("анализ %s как HTML: %v", url, err)
	}
	tags_map := map[string]int{}
	fillingHTMLMap(doc, &tags_map)
	printHTMLMap(url, &tags_map)

	return nil
}

func fillingHTMLMap(node *html.Node, tags_map *map[string]int) {
	if node.Type == html.ElementNode {
		(*tags_map)[node.Data]++
	}
	for c := node.FirstChild; c != nil; c = c.NextSibling {
		fillingHTMLMap(c, tags_map)
	}
}

func printHTMLMap(url string, tags_map *map[string]int) {
	fmt.Printf("Printing stats about %s tags\n", url)

	for tag, value := range (*tags_map) {
		fmt.Printf("%s: %d\n", tag, value)
	}
}