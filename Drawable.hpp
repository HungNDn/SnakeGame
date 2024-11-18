#pragma once 
#include <ncurses.h>
#include <iostream>
class Drawable {
    public:
        Drawable(){
            // std::cout << "Drawable" << std::endl;
            y = x = 0;
            icon = ' ';
        }

        virtual ~Drawable() {}

        Drawable(int y, int x, chtype ch) {
            // std::cout << "Drawable" << std::endl;
            this->y = y;
            this->x = x;
            this->icon = ch;
        }

        int getX() {
            return this->x;
        }

        int getY() {
            return this->y;
        }

        chtype getIcon() {
            return this->icon;
        }

    protected:  
        int y, x;
        chtype icon;
};