CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

SRCS = $(filter-out src/main.c,$(wildcard src/*.c))
OBJS = $(patsubst %.c, %.o, $(SRCS))

MAIN_SRCS = $(wildcard src/*.c)
MAIN_OBJS = $(patsubst %.c, %.o, $(MAIN_SRCS))

TEST_SRCS_longest_sentence = $(SRCS) tests/sentence_counter_test.c
TEST_SRCS_count_words = $(SRCS) tests/words_counter_test.c

TEST_SRCS_longest_sentence_OBJS = $(patsubst %.c, %.o, $(TEST_SRCS_longest_sentence))
TEST_SRCS_count_words_OBJS = $(patsubst %.c, %.o, $(TEST_SRCS_count_words))

TARGET = longest_sentence_in_file_main
TEST_TARGET_longest_sentence = longest_sentence_in_file_test
TEST_TARGET_count_words = count_words_in_sentence_test

CHECK_SUPPRESS = missingIncludeSystem
SUPPRESS_FLAGS = $(foreach suppress,$(CHECK_SUPPRESS),--suppress=$(suppress))

.PHONY: clean check format

all: check $(MAIN_OBJS)
	$(CC) $(MAIN_OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET_longest_sentence) $(TEST_TARGET_count_words)

$(TEST_TARGET_count_words): $(TEST_SRCS_count_words_OBJS)
	$(CC) $(TEST_SRCS_count_words_OBJS) -lcmocka -o $(TEST_TARGET_count_words)

$(TEST_TARGET_longest_sentence): $(TEST_SRCS_longest_sentence_OBJS)
	$(CC) $(TEST_SRCS_longest_sentence_OBJS) -lcmocka -Wl,--wrap=read_lines -o $(TEST_TARGET_longest_sentence)

check: format
	cppcheck --enable=all $(SUPPRESS_FLAGS) --error-exitcode=1 -Iinclude src include

format: $(TEST_SRC) $(MAIN_SRC) $(INC)
	clang-format --dry-run -Werror -i src/* include/*

clean:
	rm -f $(TARGET) $(TEST_TARGET_longest_sentence) $(TEST_TARGET_count_words) src/*.o tests/*.o