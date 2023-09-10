.POSIX:
CC = cc

CFLAGS := -Wall -Wextra -std=c11 -pedantic
CFLAGS += -g3 -DDEBUG
CFLAGS += $(shell pkg-config --cflags raylib)

LIBS := -fsanitize=address -lm
LIBS += $(shell pkg-config --libs raylib)

src := ../src

.PHONY: all
all: test-window

# test ann
test-ann.out: test-ann.o ann.o layer.o help.o
	$(CC) $(LIBS) -o $@ $^

test-ann.o: $(src)/test-ann.c $(src)/ann.h
	$(CC) $(CFLAGS) -c $<

ann.o: $(src)/ann.c $(src)/ann.h $(src)/layer.h
	$(CC) $(CFLAGS) -c $<

layer.o: $(src)/layer.c $(src)/layer.h $(src)/help.h
	$(CC) $(CFLAGS) -c $<

help.o: $(src)/help.c $(src)/help.h
	$(CC) $(CFLAGS) -c $<

.PHONY: test-ann
test-ann: test-ann.out
	./test-ann.out

# test render
test-window.out: test-window.o window.o
	$(CC) $(LIBS) -o $@ $^

test-window.o: $(src)/test-window.c $(src)/window.h
	$(CC) $(CFLAGS) -c $<

window.o: $(src)/window.c $(src)/window.h
	$(CC) $(CFLAGS) -c $<

.PHONY: test-window
test-window: test-window.out
	./test-window.out

# common targets
.PHONY: clean
clean:
	rm *.o *.out
