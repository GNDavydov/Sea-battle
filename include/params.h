// Copyright 2021 GNDavydov

#ifndef HOMEWORK_2_PARAMS_H
#define HOMEWORK_2_PARAMS_H

#include <array>
#include <curses.h>

namespace field_params {
    const int height = 23;
    const int width = 42;
}

namespace symbols {
    const char unknown = '~';
    const char miss = 'X';
    const char ship = 'B';
    const char injured = 'I';
    const char killed = 'U';
}

#endif //HOMEWORK_2_PARAMS_H
