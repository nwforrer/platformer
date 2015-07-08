OBJS = build/Game.o

CC = g++

CFLAGS  = -std=c++11 -g -Wall -Werror `sdl2-config --cflags`

LDFLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = build/platformer

all: main.o $(OBJS)
	$(CC) build/main.o $(OBJS) $(LDFLAGS) -o $(OBJ_NAME)

main.o: source/main.cpp
	$(CC) -c $(CFLAGS) source/main.cpp -o build/main.o

$(OBJS): build/%.o : source/%.cpp source/%.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -fv build/*.o $(OBJ_NAME)
