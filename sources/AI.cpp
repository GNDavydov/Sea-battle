// Copyright 2021 GNDavydov

#include "AI.h"

AI::AI() noexcept: curr_x(rand() % 10), curr_y(rand() % 10), direction('u'), hit_x(0), hit_y(0), hit(false) {
    for (size_t i = 0; i < 10; ++i) {
        std::fill(square_[i].begin(), square_[i].end(), symbols::unknown);
    }
}

void AI::adjustment(const std::array<std::array<char, 10>, 10> &square) {
    if (hit) {
        if (square[curr_x][curr_y] == symbols::miss) {
            if (direction == 'u') {
                curr_x = hit_x;
                curr_y = hit_y;
                try {
                    if (square.at(curr_x + 1).at(curr_y) == symbols::unknown) {
                        ++curr_x;
                        return;
                    }
                } catch (std::out_of_range &e) {}
                try {
                    if (square.at(curr_x - 1).at(curr_y) == symbols::unknown) {
                        --curr_x;
                        return;
                    }
                } catch (std::out_of_range &e) {}
                try {
                    if (square.at(curr_x).at(curr_y + 1) == symbols::unknown) {
                        ++curr_y;
                        return;
                    }
                } catch (std::out_of_range &e) {}
                try {
                    if (square.at(curr_x).at(curr_y - 1) == symbols::unknown) {
                        --curr_y;
                        return;
                    }
                } catch (std::out_of_range &e) {}
            } else if (direction == 'h') {
                if (curr_x > hit_x) {
                    while (square[curr_x][curr_y] != symbols::unknown) {
                        --curr_x;
                    }
                } else {
                    while (square[curr_x][curr_y] != symbols::unknown) {
                        ++curr_x;
                    }
                }
            } else {
                if (curr_y > hit_y) {
                    while (square[curr_x][curr_y] != symbols::unknown) {
                        --curr_y;
                    }
                } else {
                    while (square[curr_x][curr_y] != symbols::unknown) {
                        ++curr_y;
                    }
                }
            }
        } else if (square[curr_x][curr_y] == symbols::injured) {
            if (curr_x > hit_x) {
                direction = 'h';
                hit_x = curr_x;
                try {
                    if (square.at(curr_x + 1).at(curr_y) == symbols::unknown) {
                        ++curr_x;
                        return;
                    }
                } catch (std::out_of_range &e) {}
                while (square[curr_x][curr_y] != symbols::unknown) {
                    --curr_x;
                }
            } else if (curr_x < hit_x) {
                direction = 'h';
                hit_x = curr_x;
                try {
                    if (square.at(curr_x - 1).at(curr_y) == symbols::unknown) {
                        --curr_x;
                        return;
                    }
                } catch (std::out_of_range &e) {}
                while (square[curr_x][curr_y] != symbols::unknown) {
                    ++curr_x;
                }
            } else if (curr_y > hit_y) {
                direction = 'v';
                hit_y = curr_y;
                try {
                    if (square.at(curr_x).at(curr_y + 1) == symbols::unknown) {
                        ++curr_y;
                        return;
                    }
                } catch (std::out_of_range &e) {}
                while (square[curr_x][curr_y] != symbols::unknown) {
                    --curr_y;
                }
            } else {
                direction = 'v';
                hit_y = curr_y;
                try {
                    if (square.at(curr_x).at(curr_y - 1) == symbols::unknown) {
                        --curr_y;
                        return;
                    }
                } catch (std::out_of_range &e) {}
                while (square[curr_x][curr_y] != symbols::unknown) {
                    ++curr_y;
                }
            }
        } else {
            hit = false;
            direction = 'u';
            do {
                curr_x = rand() % 10;
                curr_y = rand() % 10;
            } while (square[curr_x][curr_y] != symbols::unknown);
        }
    } else {
        if (square[curr_x][curr_y] == symbols::miss || square[curr_x][curr_y] == symbols::killed) {
            do {
                curr_x = rand() % 10;
                curr_y = rand() % 10;
            } while (square[curr_x][curr_y] != symbols::unknown);
        } else if (square[curr_x][curr_y] == symbols::injured) {
            hit = true;
            hit_x = curr_x;
            hit_y = curr_y;
            try {
                if (square.at(curr_x + 1).at(curr_y) == symbols::unknown) {
                    ++curr_x;
                    return;
                }
            } catch (std::out_of_range &e) {}
            try {
                if (square.at(curr_x - 1).at(curr_y) == symbols::unknown) {
                    --curr_x;
                    return;
                }
            } catch (std::out_of_range &e) {}
            try {
                if (square.at(curr_x).at(curr_y + 1) == symbols::unknown) {
                    ++curr_y;
                    return;
                }
            } catch (std::out_of_range &e) {}
            try {
                if (square.at(curr_x).at(curr_y - 1) == symbols::unknown) {
                    --curr_y;
                    return;
                }
            } catch (std::out_of_range &e) {}
        }
    }
}

void AI::place_ship(const int x, const int y, const int len, const bool position) {
    if (position) {
        for (size_t i = x; i < x + len; ++i) {
            square_[i][y] = symbols::ship;
        }
        for (size_t i = x; i < x + len + 2; ++i) {
            try {
                square_.at(i - 1).at(y + 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
            try {
                square_.at(i - 1).at(y - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        try {
            square_.at(x - 1).at(y) = symbols::miss;
        } catch (std::out_of_range &e) {}
        try {
            square_.at(x + len).at(y) = symbols::miss;
        } catch (std::out_of_range &e) {}
    } else {
        for (size_t i = y; i < y + len; ++i) {
            square_[x][i] = symbols::ship;
        }
        for (size_t i = y; i < y + len + 2; ++i) {
            try {
                square_.at(x + 1).at(i - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
            try {
                square_.at(x - 1).at(i - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        try {
            square_.at(x).at(y - 1) = symbols::miss;
        } catch (std::out_of_range &e) {}
        try {
            square_.at(x).at(y + len) = symbols::miss;
        } catch (std::out_of_range &e) {}
    }
}

bool AI::check_ship(const int x, const int y, const int len, const bool position) const {
    if (position) {
        if (len + x <= 10) {
            for (size_t i = x; i < x + len; ++i) {
                if (square_[i][y] == symbols::ship || square_[i][y] == symbols::miss) {
                    return false;
                }
            }
            return true;
        }
    } else {
        if (len + y <= 10) {
            for (size_t i = y; i < y + len; ++i) {
                if (square_[x][i] == symbols::ship || square_[x][i] == symbols::miss) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void AI::generate_square() {
    const int ships[10] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    int x;
    int y;
    bool position;

    for (size_t i = 0; i < 10; ++i) {
        do {
            x = rand() % 10;
            y = rand() % 10;
            position = rand() % 2;
        } while (!check_ship(x, y, ships[i], position));
        place_ship(x, y, ships[i], position);
    }
}

std::array<std::array<char, 10>, 10> AI::get_square() const {
    return square_;
}

int AI::get_x() const {
    return curr_x;
}

int AI::get_y() const {
    return curr_y;
}

AI::~AI() noexcept = default;
