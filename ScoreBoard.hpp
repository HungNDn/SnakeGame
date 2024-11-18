#pragma once
#include <ncurses.h>
#include "Board.hpp"

class ScoreBoard : public Board {

public:
    ScoreBoard() {;}
    
    ScoreBoard(int width, int y, int x) {
        // std::cout << "ScoreBoard" << std::endl;
        window = newwin(2, width, y, x);
    }

    void initialize() {
        clear();
        mvwprintw(window, 0, 0, "Score:");
        updateScore(0);
        refresh();
    }

    void updateScore(int score) {
        mvwprintw(window, 0, getmaxx(window) - 3, "%3llu", score);
    }
};