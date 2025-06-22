CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c17 -g -Iinclude
LDFLAGS = -lncurses
SRC = src/main.c src/task.c
DIST = dist
out = $(DIST)/todo

all:
	@mkdir -p $(DIST)
	$(CC) $(CFLAGS) $(SRC) -o $(out) $(LDFLAGS)

run: all
	./$(out)

clean:
	rm -f $(out)
