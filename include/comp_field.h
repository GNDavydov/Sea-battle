// Copyright 2021 GNDavydov

#ifndef HOMEWORK_2_COMP_FIELD_H
#define HOMEWORK_2_COMP_FIELD_H

#include <params.h>

class comp_field {
private:
    const int height_ = field_params::height;
    const int width_ = field_params::width;
    const int start_x_ = 0;
    const int start_y_ = 0;
    int curr_x_ = 0;
    int curr_y_ = 0;
    std::array<std::array<char, 10>, 10> square_;
    WINDOW *win_;

    void move_up();

    void move_down();

    void move_left();

    void move_right();

    void dead();

    bool shot();

    bool is_dead() const;

public:
    comp_field(int start_x, int start_y, const std::array<std::array<char, 10>, 10> &square) noexcept;

    bool is_end() const;

    bool move();

    void display() const;

    ~comp_field() noexcept;
};

#endif //HOMEWORK_2_COMP_FIELD_H
