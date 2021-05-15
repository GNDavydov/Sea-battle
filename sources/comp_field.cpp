// Copyright 2021 GNDavydov

#include "comp_field.h"

comp_field::comp_field(int start_x, int start_y, const std::array<std::array<char, 10>, 10> &square) noexcept: start_x_
                                                                                                                       (start_x),
                                                                                                               start_y_(
                                                                                                                       start_y),
                                                                                                               win_(newwin(
                                                                                                                       height_,
                                                                                                                       width_,
                                                                                                                       start_y_,
                                                                                                                       start_x_)) {
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            if (square[i][j] == symbols::miss) {
                square_[i][j] = symbols::unknown;
            } else {
                square_[i][j] = square[i][j];
            }
        }
    }
}

void comp_field::move_up() {
    if (curr_x_ != 0) {
        --curr_x_;
    }
}

void comp_field::move_down() {
    if (curr_x_ != 9) {
        ++curr_x_;
    }
}

void comp_field::move_left() {
    if (curr_y_ != 0) {
        --curr_y_;
    }
}

void comp_field::move_right() {
    if (curr_y_ != 9) {
        ++curr_y_;
    }
}

void comp_field::display() const {
    std::array<std::array<char, 10>, 10> square;
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            if (square_[i][j] == symbols::ship) {
                square[i][j] = symbols::unknown;
            } else {
                square[i][j] = square_[i][j];
            }
        }
    }

    refresh();
    box(win_, 0, 0);
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            if (i == curr_x_ && j == curr_y_) {
                start_color();
                init_pair(1, COLOR_CYAN, COLOR_BLACK);
                wattron(win_, COLOR_PAIR(1));
                mvwprintw(win_, 2 * i + 2, 4 * j + 2, "%c", square[i][j]);
                wattroff(win_, COLOR_PAIR(1));
                use_default_colors();
            } else {
                mvwprintw(win_, 2 * i + 2, 4 * j + 2, "%c", square[i][j]);
            }
        }
    }
    wrefresh(win_);
}

bool comp_field::is_dead() const {
    int curr_x = curr_x_;
    int curr_y = curr_y_;
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
    curr_y = curr_y_;
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
    curr_y = curr_y_;
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
    curr_x = curr_x_;
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

void comp_field::dead() {
    int curr_x = curr_x_;
    int curr_y = curr_y_;
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
                if (square_.at(curr_x).at(curr_y) == symbols::unknown ||
                    square_.at(curr_x).at(curr_y) == symbols::miss) {
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
    } else {
        for (int i = -1; i < 2; ++i) {
            try {
                square_.at(curr_x + i).at(curr_y - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        while (true) {
            try {
                if (square_.at(curr_x).at(curr_y) == symbols::unknown ||
                    square_.at(curr_x).at(curr_y) == symbols::miss) {
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

bool comp_field::is_end() const {
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            if (square_[i][j] == symbols::ship) {
                return false;
            }
        }
    }
    return true;
}

bool comp_field::shot() {
    if (square_[curr_x_][curr_y_] == symbols::ship) {
        square_[curr_x_][curr_y_] = symbols::injured;
        if (is_dead()) {
            dead();
        }
        display();
        return true;
    }
    if (square_[curr_x_][curr_y_] == symbols::injured || square_[curr_x_][curr_y_] == symbols::killed ||
        square_[curr_x_][curr_y_] == symbols::miss) {
        return true;
    }
    square_[curr_x_][curr_y_] = symbols::miss;
    display();
    return false;
}

bool comp_field::move() {
    while (true) {
        display();
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                move_up();
                break;
            case KEY_DOWN:
                move_down();
                break;
            case KEY_LEFT:
                move_left();
                break;
            case KEY_RIGHT:
                move_right();
                break;
            case KEY_F(1):
                if (!shot()){
                    return true;
                }
                break;
            case KEY_BACKSPACE:
                clear();
                return false;
            default:
                break;
        }
    }
}

comp_field::~comp_field() noexcept {
    delwin(win_);
}