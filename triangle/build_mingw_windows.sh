#!/bin/sh

set -xe

PKGS="--static sdl2 glew"
CFLAGS="-Wall -Wextra -pedantic -ggdb -DGLEW_STATIC `pkg-config --cflags $PKGS` -Isrc -Dassert(expression)=((void)0) "
LIBS="-lm -lopengl32 `pkg-config --libs $PKGS`"
SRC="main.c"
OBJ=$(echo "$SRC" | sed "s/\.c/\.o/g")
OBJ=$(echo "$OBJ" | sed "s/src\// /g")

# wget "https://raw.githubusercontent.com/tsoding/minirent/master/minirent.h" -P /src
gcc -std=c11 $CFLAGS -c $SRC


