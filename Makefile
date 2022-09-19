CC=g++

## Para a biblioteca GLAD
INCLUDEGL=-I./glad/include/ -I./glad/include/KHR/ -I./
GLSRC=./glad/src/

## Para a carga de imagem
STB=-I./stb/
WI=-I./workImage/

## Para Mesh
MSH=-I./Mesh/

## Para Triangle Strips
TRGSTR=-I./TriangleStrip/

## Para OpenGL Mathematics
GLM=-I./glm/


all: glad.o workImage.o trgl

glad.o: ${GLSRC}glad.c
	${CC} $(shell pkg-config --cflags glfw3) ${INCLUDEGL} -c ${GLSRC}glad.c $(shell pkg-config --static --libs glfw3) -o glad.o

workImage.o: workImage/workImage.cpp workImage/workImage.h
	${CC} ${STB} ${WI} -c workImage/workImage.cpp -o workImage.o

trgl: trgl.cpp trgl.h
	${CC} $(shell pkg-config --cflags glfw3) ${INCLUDEGL} ${STB} ${WI} ${MSH} ${TRGSTR} ${GLM} workImage.o glad.o trgl.cpp $(shell pkg-config --static --libs glfw3) -o trgl

clean:
	rm glad.o workImage.o trgl

