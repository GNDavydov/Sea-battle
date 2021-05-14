// Copyright 2021 GNDavydov

#include "placing_ships.h"

placing_ships::placing_ships(const int start_x, const int start_y) noexcept: start_x_(start_x), start_y_(start_y),
                                                                             win_(newwin(height_, width_, start_y_,
                                                                                         start_x_)) {
    for (size_t i = 0; i < 10; ++i) {
        std::fill(square_[i].begin(), square_[i].end(), symbols::unknown);
    }
}

void placing_ships::move_up() {
    if (curr_x_ != 0) {
        --curr_x_;
    }
}

void placing_ships::move_down() {
    if (curr_x_ != 9) {
        ++curr_x_;
    }
}

void placing_ships::move_left() {
    if (curr_y_ != 0) {
        --curr_y_;
    }
}

void placing_ships::move_right() {
    if (curr_y_ != 9) {
        ++curr_y_;
    }
}

bool placing_ships::check_ship(const int len, const bool position) const {
    if (position) {
        if (len + curr_x_ <= 10) {
            for (size_t i = curr_x_; i < curr_x_ + len; ++i) {
                if (square_[i][curr_y_] == symbols::ship || square_[i][curr_y_] == symbols::miss) {
                    return false;
                }
            }
            return true;
        }
    } else {
        if (len + curr_y_ <= 10) {
            for (size_t i = curr_y_; i < curr_y_ + len; ++i) {
                if (square_[curr_x_][i] == symbols::ship || square_[curr_x_][i] == symbols::miss) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void placing_ships::place_ship(const int len, const bool position) {
    if (position) {
        for (size_t i = curr_x_; i < curr_x_ + len; ++i) {
            square_[i][curr_y_] = symbols::ship;
        }
        for (size_t i = curr_x_; i < curr_x_ + len + 2; ++i) {
            try {
                square_.at(i - 1).at(curr_y_ + 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
            try {
                square_.at(i - 1).at(curr_y_ - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        try {
            square_.at(curr_x_ - 1).at(curr_y_) = symbols::miss;
        } catch (std::out_of_range &e) {}
        try {
            square_.at(curr_x_ + len).at(curr_y_) = symbols::miss;
        } catch (std::out_of_range &e) {}
    } else {
        for (size_t i = curr_y_; i < curr_y_ + len; ++i) {
            square_[curr_x_][i] = symbols::ship;
        }
        for (size_t i = curr_y_; i < curr_y_ + len + 2; ++i) {
            try {
                square_.at(curr_x_ + 1).at(i - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
            try {
                square_.at(curr_x_ - 1).at(i - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        try {
            square_.at(curr_x_).at(curr_y_ - 1) = symbols::miss;
        } catch (std::out_of_range &e) {}
        try {
            square_.at(curr_x_).at(curr_y_ + len) = symbols::miss;
        } catch (std::out_of_range &e) {}
    }
}

bool placing_ships::place_ships() {
    bool position = true;
    for (size_t i = 0; i < 10;) {
        clear();
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
                if (check_ship(ships[i], position)) {
                    place_ship(ships[i], position);
                    ++i;
                }
                break;
            case KEY_F(2):
                position = !position;
                break;
            case KEY_BACKSPACE:
                clear();
                return false;
            default:
                break;
        }
    }
    clear();
    return true;
}

void placing_ships::display() const {
    refresh();
    box(win_, 0, 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == curr_x_ && j == curr_y_) {
                start_color();
                init_pair(1, COLOR_CYAN, COLOR_BLACK);
                wattron(win_, COLOR_PAIR(1));
                mvwprintw(win_, 2 * i + 2, 4 * j + 2, "%c", square_[i][j]);
                wattroff(win_, COLOR_PAIR(1));
                use_default_colors();
            } else {
                mvwprintw(win_, 2 * i + 2, 4 * j + 2, "%c", square_[i][j]);
            }
        }
    }
    wrefresh(win_);
}

std::array<std::array<char, 10>, 10> placing_ships::get_square() const {
    return square_;
}

placing_ships::~placing_ships() noexcept {
    delwin(win_);
}
