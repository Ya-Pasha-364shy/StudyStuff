CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

SRCS = $(filter-out src/seminar_main.c,$(wildcard src/*.c))
OBJS = $(patsubst %.c, %.o, $(SRCS))

TEST_SRCS = $(filter-out src/home_main.c,$(SRCS) $(wildcard tests/*.c))
TEST_OBJS = $(patsubst %.c, %.o, $(TEST_SRCS))

TARGET = home_program
TARGET_TEST = test_home_program

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test: $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $(TARGET_TEST)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

install: $(TARGET)
	cp $(TARGET) -t bin

uninstall:
	rm -f bin/$(TARGET)

clean:
	rm -f $(OBJS) $(TEST_OBJS) bin/$(TARGET) $(TARGET_TEST)
