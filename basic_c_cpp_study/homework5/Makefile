taskA:
	clang-format --dry-run -Werror taskA.c
	gcc -std=c99 -DDEBUG -Wall -Wextra -Werror -fsanitize=address -static-libasan taskA.c -o taskA

clean:
	rm -f taskA