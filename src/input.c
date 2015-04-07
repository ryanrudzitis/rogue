#include "input.h"

void getInput(char input) {
    int row, col;
    int x, y;

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

    if (mvinch(y, x) != '|' && mvinch(y, x) != '-') {
        return;
    } else {
        move(row, col);
    }
}
