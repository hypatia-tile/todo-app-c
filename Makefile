CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c17 -g -Iinclude
LDFLAGS = -lncurses -lsqlite3
SRC = src/main.c src/task.c src/ui.c src/menu.c src/database.c
DIST = dist
out = $(DIST)/todo
CPPCHECKFLAGS = --enable=all --inconclusive --std=c17 --language=c --force
REPORT = cppcheck_report.txt

all:
	@mkdir -p $(DIST)
	$(CC) $(CFLAGS) $(SRC) -o $(out) $(LDFLAGS)

run: all
	./$(out)

doc:
	doxygen Doxyfile
clean:
	rm -f $(out)

check:
	cppcheck $(CPPCHECKFLAGS) src include 2> $(REPORT)

format:
	./format.sh

.PHONY: all run clean check format