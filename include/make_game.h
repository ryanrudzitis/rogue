#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _RRUDZITI_MAKEGAMEH
#define _RRUDZITI_MAKEGAMEH

int *getRoomSize(char *size, int roomNum);
void drawRoom(int *size, int roomNum);
int *getStartDrawPos(int roomNum);
void tokenizeRoom(char *item, int roomNum);
void drawRoomElements(char *element, int roomNum);
int *getItemLoc(char *element);
char getRogueChar(char item);
void removeNewLine(char string[150]);
void findHero();

#endif
