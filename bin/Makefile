.POSIX:
CC = cc
CFLAGS := -Wall -Wextra -std=c11 -pedantic
CFLAGS += -g3 -DDEBUG
LIBS := -fsanitize=address

src := ../src

.PHONY: all
all: run

main.out: main.o ann.o layer.o
	$(CC) $(LIBS) -o $@ $^

main.o: $(src)/main.c $(src)/ann.h
	$(CC) $(CFLAGS) -c $<

ann.o: $(src)/ann.c $(src)/ann.h $(src)/layer.h
	$(CC) $(CFLAGS) -c $<

layer.o: $(src)/layer.c $(src)/layer.h
	$(CC) $(CFLAGS) -c $<

.PHONY: run
run: main.out
	./main.out

.PHONY: clean
clean:
	rm *.o *.out
