// Copyright 2021 GNDavydov

#ifndef HOMEWORK_2_MENU_H
#define HOMEWORK_2_MENU_H

#include <string>
#include <unistd.h>

#include "AI.h"
#include "params.h"
#include "comp_field.h"
#include "player_field.h"
#include "placing_ships.h"

class menu {
private:
    const int height_ = 30;
    const int width_ = 50;
    const int start_x_ = 0;
    const int start_y_ = 0;
    int curr_x_ = 2;
    WINDOW *win_;

    void move_up();

    void move_down();

public:
    menu(int start_x, int start_y) noexcept;

    void select_mode();

    void display_menu() const;

    void display_instructions() const;

    void game() const;

    ~menu() noexcept;
};

#endif //HOMEWORK_2_MENU_H
