CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -static-libasan
# CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard *.c) # выбрать все сурсы

TARGETS = taskA taskA1 taskB taskC taskD

all: taskA taskA1 taskB taskC taskD

taskA: clang-format-check
	$(CC) $(CFLAGS) taskA.c -o $@

taskA1: clang-format-check
	$(CC) $(CFLAGS) taskA1.c -o $@

taskB: clang-format-check
	$(CC) $(CFLAGS) taskB.c -o $@

taskC: clang-format-check
	$(CC) $(CFLAGS) taskC.c -o $@

taskD: clang-format-check
	$(CC) $(CFLAGS) taskD.c -o $@

clang-format-check:
	clang-format --dry-run -Werror $(SRCS)

clean:
	rm -f $(TARGETS)

