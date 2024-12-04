CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -static-libasan

SRCS = $(wildcard *.c) # выбрать все сурсы

all: taskA taskB

taskA: clang-format-check
	$(CC) $(CFLAGS) taskA.c -o $@

taskB: clang-format-check
	$(CC) $(CLAGS) taskB.c -o $@	

clang-format-check:
	clang-format --dry-run -Werror $(SRCS)

clean:
	rm -f taskA taskB
