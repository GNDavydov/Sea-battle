// Copyright 2021 GNDavydov

#include "menu.h"

menu::menu(const int start_x, const int start_y) noexcept: start_x_(start_x), start_y_(start_y),
                                                           win_(newwin(height_, width_, start_y_, start_x_)) {}

void menu::move_up() {
    if (curr_x_ != 2) {
        --curr_x_;
    }
}

void menu::move_down() {
    if (curr_x_ != 4) {
        ++curr_x_;
    }
}

void menu::game() const {
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
            if (compField.move()) {
                do {
                    usleep(1000000);
                    ai.adjustment(playerField.get_square());
                } while (playerField.shot(ai.get_x(), ai.get_y()));
            } else {
                break;
            }
        }
    }
    getch();
    clear();
}

void menu::display_instructions() const {
    WINDOW *window = newwin(20, 81, start_y_, start_x_);
    refresh();
    box(window, 0, 0);
    mvwprintw(window, 1, 1, "--------------------------------------HELP-------------------------------------");
    mvwprintw(window, 2, 1, "There are two fields in the game:");
    mvwprintw(window, 3, 1, "the left one is the user field, the right one is the computer");
    mvwprintw(window, 4, 1, "There are also 4 types of ships in the game:");
    mvwprintw(window, 5, 1, "1 - BBBB");
    mvwprintw(window, 6, 1, "2 - BBB");
    mvwprintw(window, 7, 1, "3 - BB");
    mvwprintw(window, 8, 1, "4 - B");
    mvwprintw(window, 9, 1, "-----------------------------------SYMBOLS-------------------------------------");
    mvwprintw(window, 10, 1, "~ - sea");
    mvwprintw(window, 11, 1, "B - ship");
    mvwprintw(window, 12, 1, "I - injured ship");
    mvwprintw(window, 13, 1, "K - killed ship");
    mvwprintw(window, 14, 1, "X - miss");
    mvwprintw(window, 15, 1, "--------------------------------------KEYS-------------------------------------");
    mvwprintw(window, 16, 1, "F1 - Ship placement and strike");
    mvwprintw(window, 17, 1, "F2 - Turning ships");
    wrefresh(window);
    getch();
    delwin(window);
    clear();
}

void menu::select_mode() {
    clear();
    while (true) {
        display_menu();
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                move_up();
                break;
            case KEY_DOWN:
                move_down();
                break;
            case KEY_F(1):
                clear();
                if (curr_x_ == 2) {
                    game();
                } else if (curr_x_ == 3) {
                    display_instructions();
                } else {
                    return;
                }
            default:
                break;
        }
    }
}

void menu::display_menu() const {
    refresh();
    box(win_, 0, 0);

    const std::array<std::string, 5> strings = {"Sea battle",
                                                "Written by Davydov Grigori IU8-21",
                                                "Play game",
                                                "Instructions",
                                                "Exit"};

    for (size_t i = 0; i < strings.size(); ++i) {
        start_color();
        const size_t pos = (width_ - strings[i].size()) / 2;
        if (i == curr_x_) {
            init_pair(30, COLOR_YELLOW, COLOR_BLACK);
            wattron(win_, COLOR_PAIR(30));
            mvwprintw(win_, 5 + i * 4, pos, strings[i].data());
            wattroff(win_, COLOR_PAIR(30));
        } else {
            mvwprintw(win_, 5 + i * 4, pos, strings[i].data());
        }
        use_default_colors();
    }
    wrefresh(win_);
}

menu::~menu() noexcept {
    delwin(win_);
}
