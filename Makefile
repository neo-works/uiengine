CC=gcc
CFLAGS=-I.

SRCS = src/demo.c src/web/html_document.c

demo: $(SRCS)
	$(CC) $(CFLAGS) -o demo src/demo.c src/web/html_document.c

.PHONY: clean
clean:
	rm demo