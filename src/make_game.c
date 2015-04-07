#include "make_game.h"
#include "dbg.h"

/*This function takes in the dimensions of the room in char, returns an int pointer*/
int *getRoomSize(char *size, int roomNum) { // rows x columns
    int row, col;
    char strRow[5], strCol[5];
    int *roomSize = malloc(sizeof(int) * 2);

    check(roomNum < 7 && roomNum > 0, "Invalid room to be drawn");

    /*Convert string to int*/
    strcpy(strRow, strtok(size, "X"));
    strcpy(strCol, strtok(NULL, "X"));
    row = atoi(strRow);
    col = atoi(strCol);

    roomSize[0] = row;
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
        pos[0] = 4;
        pos[1] = 1;
        break;
    case 2:
        pos[0] = 4;
        pos[1] = 30;
        break;
    case 3:
        pos[0] = 4;
        pos[1] = 59;
        break;
    case 4:
        pos[0] = 27;
        pos[1] = 1;
        break;
    case 5:
        pos[0] = 27;
        pos[1] = 30;
        break;
    case 6:
        pos[0] = 27;
        pos[1] = 59;
        break;
    default:
        break;
    }

    return pos;
}

/*Tokenizes the room line, sends buffer to get drawn*/
void tokenizeRoom(char *item, int roomNum) {
    char *buffer = malloc(sizeof(char) * 150);
    char *saved = NULL;

    /*Loop through each room item*/
    for (buffer = strtok_r(item, " ", &saved); buffer; buffer = strtok_r(NULL, " ", &saved)) {
        drawRoomElements(buffer, roomNum);
    }
    free(buffer);

}

/*Draws the actual room elements ie gold*/
void drawRoomElements(char *element, int roomNum) {
    char item = '\0';
    int *itemPos = NULL;
    int *placePos = NULL;
    int placeRow = 0, placeCol = 0;

    if (element[0] != 'd') {
        item = element[0];
        item = getRogueChar(item);
        itemPos = getItemLoc(element);

        /*Find where to place the item*/
        placePos = getStartDrawPos(roomNum);
        placeRow = placePos[0] + itemPos[0];
        placeCol = placePos[1] + itemPos[1];

        if (mvinch(placeRow, placeCol) == '.') mvaddch(placeRow, placeCol, item);

    } else {
        // call door function
    }

    free(itemPos);
    free(placePos);
    findHero(); // put the cursor on the hero
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

void findHero() {
    int i, j;

    for (i = 0; i < 80; i++) {
        for (j = 0; j < 80; j++) {
            if (mvinch(i, j) == '@') return;
        }
    }
}
