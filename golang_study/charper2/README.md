# Структура программы

## Ключевые слова

### Константы

```
true false iota nil
```

### Типы

```
int int8 int16 int32 int64 uint uint8 uint16 uint32 uint64 uintptr float32 float64 complex64 bool byte rune string error
```

### Функции

```
make len cap new append copy close delete complex real imag panic recover
```

Эти имена не являются зарезервированными, так что можно использовать их в объявлениях.

*Словом, чем больше об­ласть видимости имени, тем длиннее и значимее оно должно быть.*

ис­ пользование внутренних заглавных букв предпочтительнее внутренних подчеркива­ний

Буквы сокращений наподобие ASCII и HTML всег­ да отображаются в одном и том же регистре, поэтому функция может быть названа **htmlEscape**, **HTMLEscape** или **escapeHTML**, но не **escapeHtml**

Если некая сущность объявлена внутри функции, она является локальной для дан­ной функции. Если сущность объявлена вне функции, она видна во всех файлах па­кета, к которому она принадлежит. Регистр первой буквы имени определяет его види­мость через границы пакета. Если имя начинается с прописной буквы, оно экспорти­руемое - это означает, что оно видимо и доступно за пределами собственного пакета и к нему могут обращаться другие части программы, как в случае функции Printf из пакета fmt. Сами имена пакетов всегда состоят из строчных букв.

## Объявления

```go
// Boiling выводит температуру кипения воды,
package main
import "fmt"

const boilingF = 212.0 // это константа является объявлением переменной **уровня пакета**
                       // имя каждой сущности уровня пакета является видимым не только в данном файле, но и во всём пакете в целомф

func main() {
    var f = boilingF // эти переменные локальные для функции main
    var с = (f - 32) * 5 / 9
    fmt.Printf("Температура кипения = %g°F или %g°C\n"j f, c)
    // Вывод:
    // Температура кипения = 212°F или 100°C
}
```

```go
// fToc выводит результаты преобразования двух температур
// по Фаренгейту в температуру по Цельсию,

package main
import "fmt"


func main() {
    const freezingF, boilingF = 32.0, 212.0
    fmt.Printf("%g°F = %g°C\nH", freezingF, fToc(freezingF))
    // "32°F = 0°C"
    fmt .Printf ("%g°F = %g°C\n", boilingF, fToc(boilingF))
    // "212°F = 100°C"
}

func fToc(f float64) float64 {
    return (f - 32) * 5 / 9
}
```

## Переменные

```go
var name type = expression
```

`var` - создаёт переменую типа и присваивает ей начальное значение
`type` и `= expression` могут быть опущены, **но не обе вместе** !

в Go **не существует** такого понятия, как неинициализированная переменная.

В одном объявлении можно объявлять и (необязательно) инициализировать не­ сколько переменных, используя соответствующий список выражений. Пропущенный тип позволяет объявлять несколько переменных разных типов.

```go
var i, j, k int // объявили три перемемнные одного типа. Они все инициализированы нулём
var b, f, s = true, 2.3, "four" // объявили три переменные, все они разного типа: bool, float, string
```

Инициализаторы (то, что идёт после =) могут быть как литеральными выражениями, так и произвольными.
Переменные уровня пакета инициализируются до начала выполнения функции main, а локальные инициализируются по мере того, как в функции встречаются их объявления.

Множество переменных может быть также инициализировано с помощью вызова функции:

```go
var f, err = os.Open(name) // возвращает файл и ошибку
```

В функции для объявления и инициализации локальных переменных может ис­пользоваться альтернативная форма объявления, именуемая **кратким объявлением переменной**.
Она имеет вид:
```go
name := expression
``` 

Тип переменной `name` опреде­ляется как тип выражения `expression`.

**Объявление `var`, как правило, резервируется для локальных переменных, требующих явного указания типа, который отличается от выражения инициализатора, или когда значение пере­менной будет присвоено позже, а его начальное значение не играет роли**.

**Не забывайте, что объявление — это `:=`, а `=`— это присваивание.**

Один тонкий, но важный момент: краткое объявление переменной **не обязательно объявляет все переменные в своей левой части**. **Если некоторые из них уже были объ­явлены в том же лексическом блоке, то для этих переменных краткие объявления действуют как присваивания**.

```go
in, err := os.Open(infile)
// ...
out, err := os.Create(outfile)
```
Но:
```go
f, err := os.Open(infile)
// ...
f, err := os.Create(outfile) // Ошибка: нет новой переменной, надо заменить на `=`
```

## Указатели 

Если переменная объявлена как `var x int`, то выражение `&x` даст нам адрес переменной `x`

``` go
х := 1
// р имеет тип *int и указывает на х
р := &х
// "1"
fmt.Println(*p)
// Эквивалентно присваиванию х = 2
*р = 2
// "2"
fmt.Println(x)
```

Каждый компонент переменной составного типа — поле структуры или элемент массива — также является переменной, а значит, имеет свой адрес.
Указатели можно сравнивать:

```go
var х, у int
fmtPrintln(&x == &х, &x == &y, &x == nil) // "true false false"
```

Функция совершенно безопасно может вернуть адрес локальной переменной. На­пример, в приведенном ниже коде локальная переменная `v`, созданная этим конкрет­ным вызовом f, будет существовать даже после возврата из функции, и указатель `р` будет по-прежнему указывать на нее:

```go
var р = f() // здесь будет храниться адрес переменной v в функции f

func f() *int {
    v := 1
    return &v // это типо динамическое выделение памяти (4 байта в данном случае)
}
```

**НО** Все вызовы f возвращают различные значения 0_0:
```go
fmt.Println(f() == f()) // "false"
```

### Функция `new`

Выражение `new` создает **неименнованную переменную** типа T, инициализирует её нулевым значением типа T и возвращает **её адрес**, который представляет собой значение типа `*T`

```go example1
func newlnt() *int {
    return new(int)
}
```

```go example2
func newlnt() *int {
    var dummy int
    return Sdummy
}
```

В приведённых выше примерах example1.go эквивалентен example2.go

## время жизни переменной

Время жизни переменной уровня пакета = времени работы всей программы 

Локальные переменные имеют динамическое время жизни: новый экземпляр создаётся всякий раз, когда выполняется оператор объявления, и живёт до тех пор, пока она становится недоступной

### Когда компилятор выбирает где выделить память для переменной: на стеке или в куче ?

```go example3
var global *int
func f() {
    var x int
    x = 1
    global = &x
}
```

```go example4
func g() {
    y := new(int)
    *y = 1
}
```

В варианте `example4` **память выделяется на стеке**, так как переменная `y` никуда не сбегает от `g()`, а в программе `example3` память для `x` **выделяется в куче**, так как `x` сбегает от `f()` через `global` - внешнюю переменную.

Совет: сохранение ненужных указателей на короткоживущие объекты внутри долгоживущих объектов, например, в глобальных переменных, мешает сборщику мусора освобождать память, выделенную для короткоживущих объектов.


## присваивания кортежу

данная форма присваиваний позволяет выполнять присваивание значений нескольким переменным одновременно.

пример:
```go
x, y = y, x
a[i], a[j] = a[j], a[i]
```

однако, чтобы соблюдать стиль, следует избегать присваивание кортежам при наличии сложных выражений.

## Присваиваемость или неявные присваивания

Вызов функции неявно присваивает значения аргументов соотвествующим переменным; инструкция return тоже нечвно присваивает операнды return соотвествующим результирующим переменным

Например, срез неявно присваивает 0,1,2 элементу следующие значения:
```go
medals := []string{"gold", "silver", "bronze"}
```
выражение выше аналогично нижнему:
```go
medals[0] = "gold"
medals[1] = "silver"
medals[2] = "bronze"
```

Присваивание, явное или неяное, всегда корректно, если типы правой части и левой части совпадают

## Объявление типов (именованные типы)

```go
type имя базовый_тип
```

Рассмотрим пример:
```go
// Пакет tempconv выполняет вычисления температур
// по Цельсию (Celsius) и по Фаренгейту (Fahrenheit),
package tempconv

import "fmt"

type Celsius float64
type Fahrenheit float64

const (
    AbsoluteZeroC Celsius = -273.15
    FreezingC     Celsius = 0
    BoilingC      Celsius = 100
)

func CToF(c Celsius) Fahrenheit { return Fahrenheit(c*9/5 + 32) }
func FToC(f Fahrenheit) Celsius { return Celsius((f - 32)*5/9) }
```

Несмотря на то, что они оба имеют один и тот же базовый тип, float64, сами они являются разными типами и поэтому *не могут сравниваться или объединяться в арифметических выражениях* !

В таких случаях, когда возвращаемый тип получается с базовым типом, а ожидаемое возвращаемое - производного от базового типа, то необходимо **явное** преобразование.

Преобразование одного типа к другому разрешено, если **они имеют общий базовый тип** или **если они - неименованные указатели на переменные одного и того же базового типа**.


### Перегрузка функции вывода

Приведенное далее объявление, в котором параметра `c` типа `Celsius` **метод с именем `String`**, который возвращает числовое знпчение c, за которомы следуют символы `°С`: то есть преобразование строки в число посредством метода, принмающего число.

```go
func (c Celsius) String() string { return fmt.Sprintf("%g°С", c) }
```

пример использования:
```go
с := FToC(212.0)
fmt.PrintIn(с.String()) // "100°С"
fmt.Printf("%v\n", с) //  ”100°С" явный вызов String не нужен
fmt.Printf("%s\n", с) // "100°С"
fmt.Println(c)        // ”100°С"
fmt.Printf("%g\n", c) // "100"; не вызывает String
fmt.Println(float64(c)) // "100"; ”100"; не вызывает String
```

## Пакеты и файлы

Пакеты в Go служат тем же целям, что и библиотеки или модули в других языках программирования, поддерживая модульность, инкапсуляцию, раздельную компиля­цию и повторное использование. Исходный текст пакета располагается в одном или нескольких файлах `.go` , обычно в каталоге, имя которого является окончанием пути импорта, например файлы пакета `gopl.io/ch1/helloworld` располагаются в ката­логе `$GOPATH/src/gopl.io/ch1/helloworld`.

За подробной инструкцией, стоит обратиться сюда:
https://go.dev/doc/tutorial/create-module
и потом сюда https://go.dev/doc/tutorial/call-module-code


### Инициализация пакетов

Инициализация пакета начинается с инициализации переменных уровня пакета - в том порядке, в котором они объявлены, с тем исключением, что первыми разрешаются зависимости:

```go
var a = b + c // инициализируется третьей и = 3
var b = f()   // инициализируется второй и  = 2
var c = 1     // инициализируется первой и  = 1

func f() int { return с + 1 }
```

Если пакет состоит из нескольких файлов, то они будут инициализироваться последовательно, а именно в **отсортированном по имени порядку**.

В случае, когда у нас есть **сложная структура данных**, которую необходимо проинициализировать начальным значением, существует механизм `init`, который позволяет проинициализировать что-то комплексное.

Пример:
```go 
package popcount


var pc[256] byte // 256 - потому что это максимальное число, которое может быть представлено с помощью байта

func init() {
    for i := range pc { // здесь мы опустили получение значения, нас интересует только индекс
        pc[i] = pc[i/2] + byte(i&1)
    }
}

// PopCount возвращает степень заполнения -
// количество установленных битов значения x
func PopCount(x uint64) int {
    return int(pc[byte(x>>(0*8))] +
               pc[byte(x>>(1*8))] +
               pc[byte(x>>(2*8))] +
               pc[byte(x>>(3*8))] +
               pc[byte(x>>(4*8))] +
               pc[byte(x>>(5*8))] +
               pc[byte(x>>(6*8))] +
               pc[byte(x>>(7*8))])
}
```

**Инициализация выполняется по одному пакету** за раз в порядке объявлений импорта в программе. Поэтому пакет p, импортирующий пакет q, **уверен**, что q уже полностью инициализирован.

