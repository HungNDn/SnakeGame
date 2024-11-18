#pragma once
#include <ncurses.h>
#include <iostream>
class Board
{
protected:
    WINDOW *window;
public:
    Board() {
        // std::cout << "Board" << std::endl;
    }
    virtual ~Board() {
        delwin(window);
    }

    void addBorder() {
        box(window, 0, 0);
    }

    void clear() {
        wclear(window);
        addBorder();
    }

    void refresh() {
        wrefresh(window);
    }

    virtual void initialize() = 0;
};
 