#ifndef GAME_H
#define GAME_H

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define WINDOW_WIDTH 32
#define WINDOW_HEIGHT 64
#define FPS 60
#define NBRASTEROID 10
#define TAILLE_VAISSEAU 9

struct rgb {
    int r, g, b, a;
};

void init_game();
void drawGame();
void gameLoop();


#endif