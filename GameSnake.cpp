#include "SnakeGame.hpp"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h> 
#include <stdlib.h>

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5

void mode_raw(int activer) {
	static struct termios cooked;
	static int raw_actif = 0;
	if (raw_actif == activer) {return;}
	if (activer) {
		struct termios raw;
		tcgetattr(STDIN_FILENO, &cooked);
		raw = cooked;
		cfmakeraw(&raw);
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	}
	else {tcsetattr(STDIN_FILENO, TCSANOW, &cooked);}
	raw_actif = activer;
}

char ReadKey(void) {
	char c;
	mode_raw(1);
	c = getchar();
	mode_raw(0);
	return c;
}

void* readInputThread(void* arg) {
	while(1) {
		char input = ReadKey();
		if(input == 'p') {
			std::cout << "Pause" << std::endl;
		}
		else if(input == 'r') {
			SnakeGame game(BOARD_ROWS, BOARD_COLS);
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    initscr();
    refresh();
    noecho();
    curs_set(0);
    
    pthread_t ptid;
    pthread_create(&ptid, NULL, &readInputThread, NULL);
    pthread_join(ptid, NULL);
	
    getchar();
    endwin();
	
    return 0;
}