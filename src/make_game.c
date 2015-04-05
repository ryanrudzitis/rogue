#include "make_game.h"
#include "dbg.h"

/*This function takes in the dimensions of the room in char, returns an int pointer*/
int *getRoomSize(char *size, int roomNum) { // rows x columns
    int rows, col;
    char strRow[5], strCol[5];
    char buffer[10];
    int i;
    int *roomSize = malloc(sizeof(int) * 2);

    check(roomNum < 7 && roomNum > 0, "Invalid room to be drawn"); // check if room is valid

    strcpy(strRow, strtok(size, "X"));
    rows = atoi(strRow);

    strcpy(strCol, strtok(NULL, "X"));
    col = atoi(strCol);

    roomSize[0] = rows;
    roomSize[1] = col;

    return roomSize;

error:
    free(roomSize);
    exit(0);
}

/*Actually draws the rooms minus the items*/
void drawRoom(int *size, int roomNum) {
    int i, j;
    int *startPos = NULL;

    startPos = getStartDrawPos(roomNum);

    /*Rows*/
    for (i = startPos[1]; i <= startPos[1] + size[1] + 1; i++) {
        mvaddch(startPos[0], i, '-');
        mvaddch(startPos[0] + size[0] + 1 , i, '-');
    }

    /*Cols*/
    for (i = startPos[0]; i <= startPos[0] + size[0] + 1; i++) {
        mvaddch(i, startPos[1], '|');
        mvaddch(i, startPos[1] + size[1] + 1, '|');
    }

    /*Rest of room*/
    for (i = startPos[1] + 1; i < startPos[1] + size[1] + 1; i++) {
        for (j = startPos[0] + 1; j < startPos[0] + size[0] + 1; j++) {
            mvaddch(j, i, '.');
        }
    }

    free(startPos);
}

int *getStartDrawPos(int roomNum) {
    int *pos = malloc(sizeof(int) * 2);

    switch (roomNum) {
    case 1:
        pos[1] = 1;
        pos[0] = 4;
        break;
    case 2:
        pos[1] = 30;
        pos[0] = 4;
        break;
    case 3:
        pos[1] = 59;
        pos[0] = 4;
        break;
    case 4:
        pos[1] = 1;
        pos[0] = 27;
        break;
    case 5:
        pos[1] = 30;
        pos[0] = 27;
        break;
    case 6:
        pos[1] = 59;
        pos[0] = 27;
        break;
    default:
        break;
    }

    return pos;
}
