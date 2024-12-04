CC = gcc
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -static-libasan
CFLAGS = -Wall -Wextra -Werror


SRCS = $(wildcard *.c) # выбрать все сурсы

TARGETS = taskA taskB

all: taskA taskB

taskA: clang-format-check
	$(CC) $(CFLAGS) taskA.c -o $@

taskB: clang-format-check
	$(CC) $(CLAGS) taskB.c -o $@	

clang-format-check:
	clang-format --dry-run -Werror $(SRCS)

clean:
	rm -f $(TARGETS)

