CC=gcc
CFLAGS=-I.

SRCS = src/demo.c src/web/html_document.c

demo: $(SRCS)
	$(CC) $(CFLAGS) -o demo src/demo.c src/web/html_document.c

test: $(SRCS)
	$(CC) $(CFLAGS) -o test src/test.c src/web/html_document.c

runDemo: demo
	./demo

runTest: test
	./test

.PHONY: clean
clean:
	rm demo test