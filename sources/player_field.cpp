// Copyright 2021 GNDavydov

#include "player_field.h"

player_field::player_field(const int start_x, const int start_y,
                                    const std::array<std::array<char, 10>, 10> &square) noexcept: start_x_(start_x),
                                                                                                  start_y_(start_y),
                                                                                                  square_(square), win_(
                newwin(height_, width_, start_y_, start_x_)) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (square_[i][j] == symbols::miss) {
                square_[i][j] = symbols::unknown;
            }
        }
    }
}

void player_field::display() const {
    clear();
    refresh();
    box(win_, 0, 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            mvwprintw(win_, 2 * i + 2, 4 * j + 2, "%c", square_[i][j]);
        }
    }
    wrefresh(win_);
}

bool player_field::is_end() const {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (square_[i][j] == symbols::ship) {
                return false;
            }
        }
    }
    return true;
}

bool player_field::is_dead(const int x, const int y) const {
    int curr_x = x;
    int curr_y = y;
    while (true) {
        ++curr_y;
        try {
            if (square_.at(curr_x).at(curr_y) == symbols::unknown || square_.at(curr_x).at(curr_y) == symbols::miss) {
                break;
            }
            if (square_.at(curr_x).at(curr_y) == symbols::ship) {
                return false;
            }
        } catch (std::out_of_range &e) {
            break;
        }
    }
    curr_y = y;
    while (true) {
        --curr_y;
        try {
            if (square_.at(curr_x).at(curr_y) == symbols::unknown || square_.at(curr_x).at(curr_y) == symbols::miss) {
                break;
            }
            if (square_.at(curr_x).at(curr_y) == symbols::ship) {
                return false;
            }
        } catch (std::out_of_range &e) {
            break;
        }
    }
    curr_y = y;
    while (true) {
        --curr_x;
        try {
            if (square_.at(curr_x).at(curr_y) == symbols::unknown || square_.at(curr_x).at(curr_y) == symbols::miss) {
                break;
            }
            if (square_.at(curr_x).at(curr_y) == symbols::ship) {
                return false;
            }
        } catch (std::out_of_range &e) {
            break;
        }
    }
    curr_x = x;
    while (true) {
        ++curr_x;
        try {
            if (square_.at(curr_x).at(curr_y) == symbols::unknown || square_.at(curr_x).at(curr_y) == symbols::miss) {
                break;
            }
            if (square_.at(curr_x).at(curr_y) == symbols::ship) {
                return false;
            }
        } catch (std::out_of_range &e) {
            break;
        }
    }
    return true;
}

void player_field::dead(const int x, const int y) {
    int curr_x = x;
    int curr_y = y;
    bool direction = false;
    while (true) {
        --curr_y;
        try {
            if (square_.at(curr_x).at(curr_y) == symbols::unknown || square_.at(curr_x).at(curr_y) == symbols::miss) {
                break;
            }
        } catch (std::out_of_range &e) {
            break;
        }
    }
    ++curr_y;

    while (true) {
        --curr_x;
        try {
            if (square_.at(curr_x).at(curr_y) == symbols::unknown || square_.at(curr_x).at(curr_y) == symbols::miss) {
                break;
            }
        } catch (std::out_of_range &e) {
            break;
        }
    }
    ++curr_x;

    try {
        if (square_.at(curr_x + 1).at(curr_y) == symbols::injured) {
            direction = true;
        }
    } catch (std::out_of_range &e) {}
    if (direction) {
        for (int i = -1; i < 2; ++i) {
            try {
                square_.at(curr_x - 1).at(curr_y + i) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        while (true) {
            try {
                if (square_.at(curr_x).at(curr_y) == symbols::unknown || square_.at(curr_x).at(curr_y) == symbols::miss) {
                    break;
                }
            } catch (std::out_of_range &e) {
                break;
            }
            square_[curr_x][curr_y] = symbols::killed;
            try {
                square_.at(curr_x).at(curr_y + 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
            try {
                square_.at(curr_x).at(curr_y - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
            ++curr_x;
        }
        for (int i = -1; i < 2; ++i) {
            try {
                square_.at(curr_x).at(curr_y + i) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
    }
    else {
        for (int i = -1; i < 2; ++i) {
            try {
                square_.at(curr_x + i).at(curr_y - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        while (true) {
            try {
                if (square_.at(curr_x).at(curr_y) == symbols::unknown || square_.at(curr_x).at(curr_y) == symbols::miss) {
                    break;
                }
            } catch (std::out_of_range &e) {
                break;
            }
            square_[curr_x][curr_y] = symbols::killed;
            try {
                square_.at(curr_x + 1).at(curr_y) = symbols::miss;
            } catch (std::out_of_range &e) {}
            try {
                square_.at(curr_x - 1).at(curr_y) = symbols::miss;
            } catch (std::out_of_range &e) {}
            ++curr_y;
        }
        for (int i = -1; i < 2; ++i) {
            try {
                square_.at(curr_x + i).at(curr_y) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
    }

}

bool player_field::shot(const int x, const int y) {
    if (square_[x][y] == symbols::ship) {
        square_[x][y] = symbols::injured;
        if (is_dead(x, y)) {
            dead(x, y);
        }
        display();
        return true;
    }
    square_[x][y] = symbols::miss;
    display();
    return false;
}

std::array<std::array<char, 10>, 10> player_field::get_square() const {
    std::array<std::array<char, 10>, 10> square;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (square_[i][j] == symbols::ship) {
                square[i][j] = symbols::unknown;
            }
            else {
                square[i][j] = square_[i][j];
            }
        }
    }
    return square;
}

player_field::~player_field() noexcept {
    delwin(win_);
}