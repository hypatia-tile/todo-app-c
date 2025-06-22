CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c17 -g -Iinclude
LDFLAGS = -lncurses
SRC = src/main.c src/task.c
DIST = dist
out = $(DIST)/todo
CPPCHECKFLAGS = --enable=all --inconclusive --std=c17 --language=c --force
REPORT = cppcheck_report.txt

all:
	@mkdir -p $(DIST)
	$(CC) $(CFLAGS) $(SRC) -o $(out) $(LDFLAGS)

run: all
	./$(out)

clean:
	rm -f $(out)

check:
	cppcheck $(CPPCHECKFLAGS) src include 2> $(REPORT)


.PHONY: all run clean check