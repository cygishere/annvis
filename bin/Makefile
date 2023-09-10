.POSIX:
CC = cc
CFLAGS := -Wall -Wextra -std=c11 -pedantic
CFLAGS += -g3 -DDEBUG
LIBS := -fsanitize=address

src := ../src

.PHONY: all
all: test-render

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
test-render.out: test-render.o render.o
	$(CC) $(LIBS) -o $@ $^

test-render.o: $(src)/test-render.c $(src)/render.h
	$(CC) $(CFLAGS) -c $<

render.o: $(src)/render.c $(src)/render.h
	$(CC) $(CFLAGS) -c $<

.PHONY: test-render
test-render: test-render.out
	./test-render.out

# common targets
.PHONY: clean
clean:
	rm *.o *.out
