#include "filein.h"
#include "dbg.h"
#include "make_game.h"
#include "input.h"

int main(int argc, char const *argv[])
{
    FILE *fp = NULL;
    char *buffer = malloc(sizeof(char) * 150);
    char roomElements[150] = {0};
    char *roomSize = NULL;
    int i = 1;
    int *size = NULL; // does this need to be malloced?
    char input = '\0';

    check(argc == 2, "Please enter two arguments");

    fp = openFile((char*)argv[1], "r");

    initscr();
    noecho();

    /*Draws rooms and items*/
    while (fgets(buffer, 150, fp)) {
        removeNewLine(buffer);
        strcpy(roomElements, strchr(buffer, ' '));
        roomSize = strtok(buffer, " "); // get the room size
        size     = getRoomSize(roomSize, i); // convert room size to int pointer
        drawRoom(size, i); // draw the room
        tokenizeRoom(roomElements, i); // draw the elements
        i++;
        free(size);
    }

    /*This is the user input loop*/
    do {
        input = getch();
        getInput(input);
    } while (input != 'q');

    free(buffer);
    fclose(fp);
    endwin();

    return 0;
error:
    return -1;
}
