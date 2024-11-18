#pragma once
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "Drawable.hpp"
#include "Board.hpp"
#include <pthread.h>
class PlayingBoard : public Board {
    public: 
        PlayingBoard() {
            // std::cout << "PlayingBoard" <<std::endl;
            construct(0, 0);
        }
        PlayingBoard(int height, int width) {
            // std::cout << "PlayingBoard" << std::endl;
            construct(height, width);
        }

        void initialize() {
            clear();
            refresh();
        }

        void add(Drawable drawable) {
            addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
        }

        void addAt(int y, int x, chtype ch) {
            mvwaddch(window, y, x, ch);
        }

        chtype getInput() {
            return wgetch(window);
        }

        chtype getCharAt(int y, int x) {
            return mvwinch(window, y, x);
        }

        void getEmptyCoordinates(int& y, int& x) {
            while((mvwinch(window, y = rand() % height, x = rand() % width)) != ' ')
                ;
        }

        int getStartRow() {
            return start_row;
        }

        int getStartCol() {
            return start_col;
        }

    private:
        int height, width, start_row, start_col;
        void construct(int height, int width) {
            int xMax, yMax;
            getmaxyx(stdscr, yMax, xMax);
            this->height = height;
            this->width  = width;

            start_row = (yMax / 2) - (height / 2);
            start_col = (xMax / 2) - (width / 2);

            window = newwin(height, width, start_row, start_col);

            wtimeout(window, 100);
        }
};