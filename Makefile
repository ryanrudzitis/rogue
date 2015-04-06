all:
	gcc -std=c99 -Wall src/main.c src/filein.c src/make_game.c -Iinclude -o bin/rogue -lncurses
