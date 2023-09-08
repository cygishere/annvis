.POSIX:
CC = cc
CFLAGS := -Wall -Wextra -std=c11 -pedantic
CFLAGS += -g3 -DDEBUG
LIBS := -fsanitize=address

SRC := ../src

.PHONY: all
all: run

main.out: main.o
	$(CC) $(LIBS) -o $@ $^

main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $<

.PHONY: run
run: main.out
	./main.out

.PHONY: clean
clean:
	rm *.o *.out
