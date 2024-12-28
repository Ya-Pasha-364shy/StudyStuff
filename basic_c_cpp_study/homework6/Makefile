# Description:
# Необходимо написать Makefile, который поддержит следующие цели:
# - home_program (она же просто make)
# - clean (make clean)
# - install (make install)
# - uninstall (make uninstall)
# - test (make test)

# Загружаемый файл должен называться Makefile.c

# Структура проекта выглядит так:
# - bin/
# - include/
#     - home_header.h
#     - sem_header.h
# - src/
#     - home_main.c
#     - home_minus.c
#     - seminar_main.c
# - tests/
#     - home_test.c
#     - <какое-то имя>.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

SRCS = $(filter-out src/seminar_main.c,$(wildcard src/*.c))
OBJS = $(patsubst %.c, %.o, $(SRCS))

TEST_SRCS = $(filter-out src/home_main.c,$(SRCS) $(wildcard tests/*.c))
TEST_OBJS = $(patsubst %.c, %.o, $(TEST_SRCS))

TARGET = home_program
TARGET_TEST = test_home_program

# home_program
# Ожидается, что соберется программа из файлов `src/*.c`, кроме файла `src/seminar_main.c` (p.s. посмотрите встроенные make-функции wildcard и filter-out).
# Сборка должна содержать флаги "-Wall -Wextra -Werror", при чем флаги должны быть именно в таком порядке!
# Файлы `src/*.c` могут содержать `#include "home_header.h"`, нужно учесть это в компиляции.
# Итоговый бинарный файл должен называться home_program.

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# test
# Ожидается, что соберется программа тестов из файлов `tests/*.c` и `src/*.c`, кроме файлов  `src/seminar_main.c` и `src/home_main.c` (p.s. посмотрите встроенные make-функции wildcard и filter-out).
# Файлы `tests/*.c` и `src/*.c` могут содержать `#include "home_header.h"`, нужно учесть это в компиляции.
# Итоговый бинарный файл должен называться test_home_program.

test: $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $(TARGET_TEST)

# callback-цель для компиляции файлов в объектники 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# install
# Ожидается копирование итогового бинарного файла в директорию проекта `bin/`

install: $(TARGET)
	cp $(TARGET) -t bin

# uninstall
# Ожидается удаление итогового бинарного файла из директории проекта `bin/`

uninstall:
	rm -f bin/$(TARGET)

# clean
# Ожидается удаление всех `.o` файлов в проекте + удаление итогового бинарного файла, а также удаление тестового бинарно файла (см. make test).

clean:
	rm -f $(OBJS) $(TEST_OBJS) bin/$(TARGET) $(TARGET_TEST)
