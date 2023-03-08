#ifndef LED_PADDLE_H
#define LED_PADDLE_H
#include "led-matrix-c.h"
#include <string.h>

extern int width, height;

int initialise_led_matrix(int argc, char **argv);

void set_pixel(int x, int y, int R, int G, int B);

void matrix_clear();

void actualize();

void delete_matrix();

#endif //LED_PADDLE_H