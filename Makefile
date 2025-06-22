CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c17 -g -Iinclude -lncurses
SRC = src/main.c
out = todo

all:
	$(CC) $(CFLAGS) $(SRC) -o $(out)

clean:
	rm -f $(out)
