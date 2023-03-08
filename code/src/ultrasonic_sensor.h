#ifndef ULTRASONIC_SENSOR_H
#define U

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>

#define LEFT_SENSOR_PIN_ECHO 15
#define LEFT_SENSOR_PIN_TRIGGER 14

#define RIGHT_SENSOR_PIN_ECHO 7
#define RIGHT_SENSOR_PIN_TRIGGER 8

void initialise_sensors();

float getDistance(int echo, int trigger);

#endif