CC=gcc
CFLAGS=-I. -g

SRCS = src/demo.c \
	src/web/html_document.c	\
	src/mem/mem.c	\
	src/renderer/renderer.c	\
	src/renderer/render_node.c	\
	src/renderer/component/button.c	\
	src/renderer/backend/canvas/backend_canvas.c

TEST_SRCS = src/test.c src/web/html_document.c src/mem/mem.c

demo: $(SRCS)
	$(CC) $(CFLAGS) -o demo $(SRCS)

test: $(SRCS)
	$(CC) $(CFLAGS) -o test $(TEST_SRCS)

runDemo: demo
	./demo

runTest: test
	./test

.PHONY: clean
clean:
	rm demo test