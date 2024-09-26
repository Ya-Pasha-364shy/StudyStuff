package html
import (
	"io"
)

type NodeType int32

type Node struct {
	Type NodeType
	Data string
	Attr []Attribute
	FirstChild, NextSibling *Node
}

const (
	ErrorNode NodeType = iota
	TextNode
	DocumentNode
	ElementNode
	CommentNode
	DoctypeNode
)

type Attribute struct {
	Key, Val string
}

// эта функция может быть реализована на другом языке
func Parse(r io.Reader) (*Node, error)