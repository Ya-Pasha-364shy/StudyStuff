CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

SRCS = $(wildcard src/*.c) # выбрать все сурсы
TEST_SRCS = $(wildcard test/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS)) # создать имена объектников
TEST_OBJS = $(patsubst %.c, %.o, $(TEST_SRCS))

TARGET = hello
TEST_TARGET = hello_test

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $(TEST_TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	cp hello -t bin/

uninstall:
	rm -f bin/hello

clean:
	rm -f hello hello_test $(OBJS) $(TEST_OBJS)
