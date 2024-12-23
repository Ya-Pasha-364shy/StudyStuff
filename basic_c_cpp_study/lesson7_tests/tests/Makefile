all:
	gcc -o test_b file_reader.c CMocka_example_sources_B.c CMocka_example_tests_B.c -lcmocka -Wl,--wrap=read_line

clean:
	rm -f test_b