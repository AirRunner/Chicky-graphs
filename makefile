SOURCE = controller/*.c rendering/*.c data-layer/*.c
OUTPUT = build/Chicky
LIB = -lSDL2 -lSDL2_ttf -lSDL2_image -lm
OPT = -Wall -Werror -std=c99

CFLAGS= $(shell sdl2-config --cflags)
LDFLAGS= $(shell sdl2-config --libs)

all:
	gcc -g $(SOURCE) -o $(OUTPUT) $(CFLAGS) $(LDFLAGS) $(LIB) $(OPT) && cd build && ./Chicky && cd ..
