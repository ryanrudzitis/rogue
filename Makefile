all:
	gcc -std=c99 -Wall src/main.c src/input.c src/filein.c src/make_game.c -g -O0 -Iinclude -o bin/rogue -lncurses
