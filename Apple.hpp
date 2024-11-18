#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Apple : public Drawable {
    public:
        Apple(int y, int x) {
            // std::cout << "Apple" << std::endl;
            this->y = y;
            this->x = x;
            this->icon = 'A';
        }
};