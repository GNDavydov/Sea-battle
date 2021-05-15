// Copyright 2021 GNDavydov

#ifndef HOMEWORK_2_AI_H
#define HOMEWORK_2_AI_H

#include "params.h"

class AI {
private:
    int curr_x;
    int curr_y;
    char direction;
    int hit_x;
    int hit_y;
    bool hit;
    std::array<std::array<char, 10>, 10> square_;

    void place_ship(int x, int y, int len, bool position);

    bool check_ship(int x, int y, int len, bool position) const;

public:
    AI() noexcept;

    void adjustment(const std::array<std::array<char, 10>, 10> &square);

    void generate_square();

    std::array<std::array<char, 10>, 10> get_square() const;

    int get_x() const;

    int get_y() const;

    ~AI() noexcept;
};

#endif //HOMEWORK_2_AI_H
