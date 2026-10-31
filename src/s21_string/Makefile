CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SRCS = s21_string.c s21_string_test.c

all: strlen_tests strcmp_tests

strlen_tests:
	@mkdir -p ../../build
	$(CC) $(CFLAGS) $(SRCS) -o ../../build/Quest_6

strcmp_tests:
	@mkdir -p ../../build
	$(CC) $(CFLAGS) $(SRCS) -o ../../build/Quest_7

clean:
	rm -f ../../build/Quest_6 ../../build/Quest_7

rebuild: clean all

.PHONY: all strlen_tests strcmp_tests clean rebuild