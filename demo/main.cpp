// Copyright 2021 GNDavydov

#include "menu.h"


int main() {
    if (!initscr()) {
        fprintf(stderr, "Error initialising ncurses.\n");
        return 0;
    }

    srand(time(0));
    initscr();
    keypad(stdscr, true);
    noecho();

    const int x = (COLS - 50) / 2;
    const int y = (LINES - 30) / 2;

    menu Menu(x, y);
    Menu.select_mode();

    endwin();
}