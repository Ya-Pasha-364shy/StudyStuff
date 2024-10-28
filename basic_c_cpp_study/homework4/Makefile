taskA:
	clang-format --dry-run -Werror taskA.c
	gcc -std=c99 -Wall -Wextra -Werror taskA.c -o taskA

taskB:
	clang-format --dry-run -Werror taskB.c
	gcc -std=c99 -Wall -Wextra -Werror taskB.c -o taskB

clean:
	rm -f taskA taskB