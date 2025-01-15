CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

all: strace_0 strace_1 strace_2 strace_3

strace_0: strace_0.c
	$(CC) $(CFLAGS) -o $@ $^

strace_1: strace_1.c
	$(CC) $(CFLAGS) -o $@ $^

strace_2: strace_2.c
	$(CC) $(CFLAGS) -o $@ $^

strace_3: strace_3.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f all

.PHONY: clean all
