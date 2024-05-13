CFLAGS=-lGL -Wall -Wextra -ggdb -lGLEW 
CFLAGS+=`pkg-config sdl2 --cflags` 
LDLIBS=`pkg-config sdl2 --libs`

main: main.o opengl_c.o
	gcc -o main main.o opengl_c.o $(LDLIBS) $(CFLAGS)

main.o: main.c
	gcc -c main.c

opengl_c.o:
	gcc -c opengl_c.c

clean:
	rm -f *.o triangle
.PHONY: all clean
