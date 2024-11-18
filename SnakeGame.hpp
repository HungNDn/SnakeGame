#pragma once
#include "PlayingBoard.hpp"
#include "Apple.hpp"
#include "Empty.hpp"
#include "Snake.hpp"
#include "ScoreBoard.hpp"
#include <pthread.h>
#include <unistd.h>

class SnakeGame {
    public: 
        SnakeGame(int height, int width) {
            // std::cout << "SnakeGame" << std::endl;
            playingBoard = new PlayingBoard(height, width);

            int sb_row = playingBoard->getStartRow() + height;
            int sb_col = playingBoard->getStartCol();

            scoreBoard = new ScoreBoard(width, sb_row, sb_col);
            snake = new Snake();

            initialize();
            
            pthread_create(&ptid, NULL, run, this);  
            pthread_join(ptid, NULL); 
        }

        ~SnakeGame() {
            // std::cout << "~SnakeGame" << std::endl;
            delete apple;
            delete scoreBoard;
            delete playingBoard;
            delete snake;
        }

        void createApple() {
            int y, x;
            playingBoard->getEmptyCoordinates(y, x);
            apple = new Apple(y, x);
            playingBoard->add(*apple);
        }

        void handleNextPiece(SnakePiece next) {

            if(apple != NULL) {
                switch (playingBoard->getCharAt(next.getY(), next.getX()))
                {
                case 'A':
                    eatApple();
                    break;
                case ' ': {
                    int emptyRow = snake->tail().getY();
                    int emptyCol = snake->tail().getX();
                    playingBoard->add(Empty(emptyRow, emptyCol));
                    snake->removePiece();
                    break;
                }
                default:
                    game_over = true;
                    std::cout << std::endl;
	                std::cout << "Game Over" << std::endl;
                    break;
                }
            }
            
            playingBoard->add(next);
            snake->addPiece(next);
        }

        void initialize() {
            apple = NULL;
            playingBoard->initialize();
            scoreBoard->initialize();
            game_over = false; 
            score = 0;
            
            snake->setDirection(DOWN);
            handleNextPiece(SnakePiece(1, 1));
            handleNextPiece(snake->nextHead());
            handleNextPiece(snake->nextHead());

            snake->setDirection(RIGHT);
            handleNextPiece(snake->nextHead());

            if(apple == NULL) {
                createApple();
            }
        }
        
        void processInput() {
            chtype input = playingBoard->getInput();
            switch (input)
            {
            case KEY_UP:
            case 'w': 
                snake->setDirection(UP);
                break;
            case KEY_DOWN:
            case 's':
                snake->setDirection(DOWN);
                break;
            case KEY_LEFT:
            case 'a':
                snake->setDirection(LEFT);
                break;
            case KEY_RIGHT:
            case 'd':
                snake->setDirection(RIGHT);
                break;
            }
        }

        void eatApple() {
            score += 100;
            scoreBoard->updateScore(score);
            delete apple;
            apple = NULL;
        }

        static void* run(void* arg) {
            while (!((SnakeGame *)arg)->isOver()) {
                ((SnakeGame *)arg)->processInput();
                ((SnakeGame *)arg)->updateState();		 
                ((SnakeGame *)arg)->redraw();
            }
            pthread_exit(NULL);
        }

        void updateState() {
            SnakePiece next = snake->nextHead();
            handleNextPiece(next);

            if(apple == NULL) { 
               createApple();
            }
        }

        void redraw() {
            playingBoard->refresh();
            scoreBoard->refresh();
        }

        bool isOver() {
            return game_over;
        }

    private:
        PlayingBoard* playingBoard = nullptr;
        ScoreBoard* scoreBoard = nullptr;
        Snake* snake = nullptr;
        Apple* apple;
        int score;
        bool game_over;
        pthread_t ptid;
};