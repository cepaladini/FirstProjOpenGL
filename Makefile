CC=g++

INCLUDEGL=-I./glad/include/ -I./glad/include/KHR/ -I./

GLSRC=./glad/src/

all: glad.o

glad.o: ${GLSRC}glad.c
	${CC} $(shell pkg-config --cflags glfw3) ${INCLUDEGL} -c ${GLSRC}glad.c $(shell pkg-config --static --libs glfw3) -o glad.o

clean:
	rm glad.o

