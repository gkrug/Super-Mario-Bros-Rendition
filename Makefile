all: main

main: main_mario.cpp Game.h
	g++ main_mario.cpp -w -lSDL2 -lSDL2_image -g

clean:
	rm a.out
