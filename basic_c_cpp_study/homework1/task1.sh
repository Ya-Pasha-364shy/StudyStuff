#!/bin/bash

# Description:
#
# Дан файл `/opt/hw1/datasets.tar.gz`, содержащий файлы queries.txt и features.txt
# Заголовок файла queries.txt: (здесь между частями <query> могут быть пробелы)
# <query>    <qid>
# Заголовок файла features.txt:
# <qid>    <f1>    <f2>    <f3>    <f4>
# Требуется вывести на stdin объединение этих файлов со следующими колонками, отсортированное по qid.
# <query>    <qid>    <f2>    <f3>

### Решение в лоб

BASE_PATH='/home/k1r4/EDU/basic_cpp/homework1'
EXTRACT_PATH=`mktemp -p $BASE_PATH -d`

tar -xf $BASE_PATH'/datasets.tar.gz' -C $EXTRACT_PATH

QUERIES_OUTPUT=`cat $EXTRACT_PATH/queries.txt`

# убираем лишние пробелы между элементами `query`. Последний пробел - это идентификатор раздела `query` и `qid`
# затем 

awk '{print $2, $1}' queries_stripped.txt > queries_tmp.txt
sort queries_tmp.txt > queries_tmp_sorted.txt
join queries_tmp_sorted.txt features.txt > result.txt

# здесь будет формат:
# <qid>    <query>    <f1>    <f2>    <f3>    <f4>
# с помощью AWK обрежем и поменяем местами

# результат:
# sha256sum result.txt