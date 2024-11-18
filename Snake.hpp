#pragma once
#include "Drawable.hpp"
#include <queue>

enum Direction {
    UP      = -1,
    DOWN    = 1,
    LEFT    = -2,
    RIGHT   = 2
};

class SnakePiece : public Drawable {
    public: 
        SnakePiece() {
            // std::cout << "SnakePiece No param" << std::endl;
            this->y = this->x = 0;
            this->icon = ' ';
        }

        SnakePiece(int y, int x) {
            // std::cout << "SnakePiece param" << std::endl;
            this->y = y;
            this->x = x;
            this->icon = '#';
        }
};

class Snake {
    public:
        Snake() {
            // std::cout << "Snake" << std::endl;
            cur_direction = DOWN;
        }

        void addPiece(SnakePiece piece) {
            snake.push(piece);
        }

        void removePiece() {
            snake.pop();
        }

        SnakePiece tail() {
            return snake.front();
        }

        SnakePiece head() {
            return snake.back();
        }

        Direction getDirection() {
            return cur_direction;
        }

        void setDirection(Direction d) {
            if(cur_direction + d != 0)
                cur_direction = d;
        } 

        SnakePiece nextHead() {
            int row = head().getY();
            int col = head().getX();

            switch (cur_direction)
            {
            case UP:
                row--;
                break;
            case DOWN:
                row++;
                break;
            case LEFT:
                col--;
                break;
            case RIGHT:
                col++;
                break;   
            }
            return SnakePiece(row, col);   
        }

    private:
        std::queue<SnakePiece> snake;
        Direction cur_direction;
};