CC := gcc

CFLAGS := -Wall -Werror -Wextra -pedantic

NAME := 0-hreadelf

SRC := $(wildcard *.c)

all: $(NAME)

$(NAME):
		$(CC) $(CFLAGS) $(SRC) -o $@

clean:
		rm -f $(NAME)
