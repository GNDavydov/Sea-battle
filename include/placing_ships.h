// Copyright 2021 GNDavydov

#ifndef HOMEWORK_2_PLACING_SHIPS_H
#define HOMEWORK_2_PLACING_SHIPS_H

#include "params.h"


class placing_ships {
private:
    const int height_ = field_params::height;
    const int width_ = field_params::width;
    const int start_x_ = 0;
    const int start_y_ = 0;
    const int ships[10] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    std::array<std::array<char, 10>, 10> square_;
    int curr_x_ = 0;
    int curr_y_ = 0;
    WINDOW *win_;

    void move_up();

    void move_down();

    void move_left();

    void move_right();

    void place_ship(int len, bool position);

    bool check_ship(int len, bool position) const;


public:
    placing_ships(int start_x, int start_y) noexcept;

    void display() const;

    bool place_ships();

    std::array<std::array<char, 10>, 10> get_square() const;

    ~placing_ships() noexcept;
};

#endif //HOMEWORK_2_PLACING_SHIPS_H
