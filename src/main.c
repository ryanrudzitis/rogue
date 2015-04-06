#include "filein.h"
#include "dbg.h"
#include "make_game.h"

int main(int argc, char const *argv[])
{
    FILE *fp = NULL;
    char buffer[150];
    char roomElements[150];
    char *roomSize;
    int i = 1;
    int *size = NULL; // does this need to be malloced?

    check(argc == 2, "Please enter two arguments");

    fp = openFile((char*)argv[1], "r");

    initscr();

    /*Draws rooms and items*/
    while (fgets(buffer, 150, fp)) {
        removeNewLine(buffer);
        strcpy(roomElements, strchr(buffer, ' '));
        roomSize = strtok(buffer, " "); // get the room size
        size = getRoomSize(roomSize, i); // convert room size to int pointer
        drawRoom(size, i); // draw the room
        tokenizeRoom(roomElements, i);
        i++;
        free(size);
    }

    getch();
    endwin();

    return 0;
error:
    return -1;
}
