#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int *getRoomSize(char *size, int roomNum);
void drawRoom(int *size, int roomNum);
int *getStartDrawPos(int roomNum);
