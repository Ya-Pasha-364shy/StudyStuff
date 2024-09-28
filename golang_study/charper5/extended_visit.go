package main

import (
	"fmt"
	"os"
	"net/http"

	"golang.org/x/net/html"
)

func main() {
	for _, url := range os.Args[1:] {
		links, err := getLinksAndImages(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "%s: %v\n", os.Args[0], err)
			continue
		}
		fmt.Printf("Printing links and images paths for %s\n", url)
		for _, link := range links {
			fmt.Println(link)
		}
		fmt.Println("Stop")
	}
}

func getLinksAndImages(url string) ([]string, error) {
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	if resp.StatusCode != http.StatusOK {
		resp.Body.Close()
		return nil, fmt.Errorf("получение %s: %s\n", url, resp.Status)
	}
	// *html.Node, error
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return nil, fmt.Errorf("анализ %s как HTML: %v", url, err)
	}
	var links_and_paths []string
	return evisit(links_and_paths, doc), nil
}

func evisit(links_and_paths []string, node *html.Node) []string {
	if node.Type == html.ElementNode || node.Type == html.TextNode {
		if node.Data == "a" {
			checkTagAndAppend(node, "href", &links_and_paths)
		} else if node.Data == "img" {
			checkTagAndAppend(node, "src", &links_and_paths)
		} else if node.Data == "div" {
			checkTagAndAppend(node, "style", &links_and_paths)
		} else if node.Data == "section" {
			checkTagAndAppend(node, "style", &links_and_paths)
		}
	}
	for c := node.FirstChild; c != nil; c = c.NextSibling {
		links_and_paths = evisit(links_and_paths, c)
	}
	return links_and_paths
}

func checkTagAndAppend(node *html.Node, key string, slice *[]string) {
	for _, attr := range node.Attr {
		if attr.Key == key {
			*slice = append(*slice, attr.Val)
		}
	}
}