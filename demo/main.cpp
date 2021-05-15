// Copyright 2021 GNDavydov

#include <unistd.h>

#include "AI.h"
#include "comp_field.h"
#include "player_field.h"
#include "placing_ships.h"


int main() {
    if (!initscr()) {
        fprintf(stderr, "Error initialising ncurses.\n");
        return 0;
    }

    srand(time(0));
    initscr();
    keypad(stdscr, true);
    noecho();

    const int x = (COLS - field_params::width) / 2;
    const int y = (LINES - field_params::height) / 2;

    placing_ships place(x, y);


    if (place.place_ships()) {
        AI ai;
        ai.generate_square();
        comp_field compField(50, 0, ai.get_square());
        player_field playerField(0, 0, place.get_square());

        playerField.display();
        compField.display();

        while (!playerField.is_end()) {
            if (compField.move() && !compField.is_end()){
                do {
                    usleep(1000000);
                    ai.adjustment(playerField.get_square());
                } while (playerField.shot(ai.get_x(), ai.get_y()));
            }
            else {
                break;
            }
        }
    }
    getch();
    endwin();
}