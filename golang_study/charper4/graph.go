package main

import (
	"fmt"
)

// хэш пар "строка-хэш таблица", где "хэш-таблица" - это пары "строка-булево значение".
// [a]={[b]=true,[c]=true},[b]={[a]=true,[d]=true}, ... 
var graph = make(map[string]map[string]bool)

func addEdge(from, to string) {
	edges := graph[from]
	if edges == nil {
		edges = make(map[string]bool)
		graph[from] = edges
	}
	edges[to] = true
}

func hasEdge(from, to string) bool {
	return graph[from][to]
}

func main() {
	
}