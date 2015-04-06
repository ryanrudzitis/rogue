#include "make_game.h"
#include "dbg.h"

/*This function takes in the dimensions of the room in char, returns an int pointer*/
int *getRoomSize(char *size, int roomNum) { // rows x columns
    int rows, col;
    char strRow[5], strCol[5];
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

/*Gets starting drawing position for each room*/
int *getStartDrawPos(int roomNum) {
    int *pos = malloc(sizeof(int) * 2);

    /*Switch these below*/
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

/*Tokenizes the room line, sends buffer to get drawn*/
void tokenizeRoom(char *item, int roomNum) {
    char *buffer = malloc(sizeof(char) * 150);
    char *saved;

    for (buffer = strtok_r(item, " ", &saved); buffer; buffer = strtok_r(NULL, " ", &saved)) {
        drawRoomElements(buffer, roomNum);
    }

    free(buffer);
}

void drawRoomElements(char *element, int roomNum) {
    char item;
    int *pos;
    int placeRow, placeCol;

    if (element[0] != 'd') {
        item = element[0];
        item = getRogueChar(item);
        pos = getItemLoc(element);

        placeRow = getStartDrawPos(roomNum)[0] + pos[0];
        placeCol = getStartDrawPos(roomNum)[1] + pos[1];

        if (mvinch(placeRow, placeCol) == '.') mvaddch(placeRow, placeCol, item);

    } else {
        // call door function
    }
}

int *getItemLoc(char *element) {
    int *loc = malloc(sizeof(int) * 2);
    char *buffer = malloc(sizeof(char) * 5);
    int i;
    char *tempRow, *tempCol;

    for (i = 0; i < strlen(element); i++) {
        element[i] = element[i + 1];
    }

    element[strlen(element)] = '\0';

    tempRow = strtok(element, ",");
    tempCol = strtok(NULL, ",");

    loc[0] = atoi(tempRow);
    loc[1] = atoi(tempCol);

    free(buffer);
    return loc;

}

char getRogueChar(char item) {
    char rogueChar = '\0';

    switch (item) {
    case 'h':
        rogueChar = '@';
        break;
    case 'g':
        rogueChar = '*';
        break;
    case 'w':
        rogueChar = ')';
        break;
    case 'p':
        rogueChar = '!';
        break;
    case 'm':
        rogueChar = '?';
        break;
    case 's':
        rogueChar = '%';
        break;
    default:
        rogueChar = item;
        break;
    }

    return rogueChar;
}

void removeNewLine(char string[150]) {
    int i;
    for (i = 0; i < strlen(string); i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
        }
    }
}
