CC=gcc
CFLAGS=-I. -I/opt/homebrew/Cellar/sdl2/2.26.5/include -g

LIB=-lSDL2 -lSDL2main `sdl2-config --cflags --libs` -lpthread

SRCS = src/demo.c \
	src/web/html_document.c	\
	src/mem/mem.c	\
	src/renderer/renderer.c	\
	src/renderer/render_node.c	\
	src/renderer/component/button.c	\
	src/renderer/backend/sdl2/backend_sdl2.c

TEST_SRCS = src/test.c src/web/html_document.c src/mem/mem.c

demo: $(SRCS)
	$(CC) $(CFLAGS) -o demo $(SRCS) $(LIB)

test: $(SRCS)
	$(CC) $(CFLAGS) -o test $(TEST_SRCS)

runDemo: demo
	./demo

runTest: test
	./test

.PHONY: clean
clean:
	rm demo test