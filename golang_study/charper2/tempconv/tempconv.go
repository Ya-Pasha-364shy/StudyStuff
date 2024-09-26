// этот пакет выполняет преобразование температур
package tempconv

import "fmt"

type Kelvin     float64
type Celsius    float64
type Fahrenheit float64

const (
	AbsoluteZero Celsius = -273.15
	FreezingC    Celsius = 0
	BollingC     Celsius = 100
)

// это методы, которые преобразуют число типа Celsius или Fahrenheit в строку посредством "Sprintf"
// глагол %g используется для длинных чисел с плавающей точкой
func (c Celsius) String() string { return fmt.Sprintf("%g°C", c) }
func (f Fahrenheit) String() string { return fmt.Sprintf("%g℉", f) }
func (k Kelvin) String() string { return fmt.Sprintf("%g°K", k) }