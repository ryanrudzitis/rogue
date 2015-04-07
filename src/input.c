#include "/Users/ryanrudzitis/Documents/c_files/rogue/include/input.h"

void getInput(char input) {
    int row, col;
    int x, y;
    // char tempFloor;

    getyx(stdscr, row, col);
    getyx(stdscr, y, x);


    switch (input) {
    case 'w':
        y--;
        break;

    case 'a':
        x--;
        break;

    case 's':
        y++;
        break;

    case 'd':
        x++;
        break;

    default:
        //command not found need to print this
        break;
    }

    /*Check if the hero's movement is valid*/
    if (mvinch(y, x) != '|' && mvinch(y, x) != '-') {
        mvaddch(row, col, '.');
        mvaddch(y, x, '@');
        move(y, x);
        return;
    } else {
        move(row, col);
    }
}
