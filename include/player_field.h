// Copyright 2021 GNDavydov

#ifndef HOMEWORK_2_PLAYER_FIELD_H
#define HOMEWORK_2_PLAYER_FIELD_H

#include "params.h"


class player_field {
private:
    const int height_ = field_params::height;
    const int width_ = field_params::width;
    const int start_x_ = 0;
    const int start_y_ = 0;
    std::array<std::array<char, 10>, 10> square_;
    WINDOW *win_;

    bool is_dead(int x, int y) const;

    void dead(int x, int y);

public:
    explicit player_field(int start_x, int start_y, const std::array<std::array<char, 10>, 10> &square) noexcept;

    void display() const;

    bool is_end() const;

    bool shot(int x, int y);

    std::array<std::array<char, 10>, 10> get_square() const;

    ~player_field() noexcept;

};


#endif //HOMEWORK_2_PLAYER_FIELD_H
