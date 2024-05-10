LDLIBS=$(shell sdl2-config --libs) -lGLEW $(EXTRA_LDLIBS)
CFLAGS=$(shell sdl2-config --cflags)  $(EXTRA_CFLAGS)
EXTRA_LDLIBS?=-lGL
EXTRA_CFLGAS?=-Wall -Wextra -ggdb

main: main.o opengl_c.o
	gcc -o main main.o opengl_c.o $(LDLIBS) $(CFLAGS) -ggdb

main.o: main.c
	gcc -c main.c

opengl_c.o:
	gcc -c opengl_c.c

clean:
	rm -f *.o triangle
.PHONY: all clean
