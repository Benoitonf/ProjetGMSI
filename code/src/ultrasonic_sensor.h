#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gpiod.h>

#define LEFT_SENSOR_PIN_ECHO 15
#define LEFT_SENSOR_PIN_TRIGGER 14

#define RIGHT_SENSOR_PIN_ECHO 7
#define RIGHT_SENSOR_PIN_TRIGGER 8

extern struct gpiod_line *Left_trigger_line, *Left_echo_line, *Right_trigger_line, *Right_echo_line;

void initialise_sensors(struct gpiod_chip *chip);

float getDistance(struct gpiod_line *echo, struct gpiod_line *trigger);

#endif