CC := gcc

CFLAGS := -Wall -Werror -Wextra -pedantic

NAME := hnm

SRC := $(wildcard *.c)

all: $(NAME)

$(NAME):
		$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
		rm -f $(NAME)
