CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic

all: todo_api_0 todo_api_1 todo_api_2 todo_api_3 todo_api_4 todo_api_5

todo_api_0: todo_api_0.c helpers.c todo_api.h
	$(CC) $(CFLAGS) -o todo_api_0 todo_api_0.c helpers.c

todo_api_1: todo_api_1.c helpers.c todo_api.h
	$(CC) $(CFLAGS) -o todo_api_1 todo_api_1.c helpers.c

todo_api_2: todo_api_2.c helpers.c todo_api.h
	$(CC) $(CFLAGS) -o todo_api_2 todo_api_2.c helpers.c

todo_api_3: todo_api_3.c helpers.c todo_api.h
	$(CC) $(CFLAGS) -o todo_api_3 todo_api_3.c helpers.c

todo_api_4: todo_api_4.c helpers.c todo_api.h
	$(CC) $(CFLAGS) -o todo_api_4 todo_api_4.c helpers.c

todo_api_5: todo_api_5.c helpers.c todo_api.h
	$(CC) $(CFLAGS) -o todo_api_5 todo_api_5.c helpers.c

clean:
	rm -f todo_api_0 todo_api_1 todo_api_2 todo_api_3 todo_api_4 todo_api_5

.PHONY: all clean
