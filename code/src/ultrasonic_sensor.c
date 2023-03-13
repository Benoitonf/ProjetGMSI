#include "ultrasonic_sensor.h"

struct gpiod_line *Left_trigger_line, *Left_echo_line, *Right_trigger_line, *Right_echo_line;

void initialise_sensors(struct gpiod *chip) {
    Left_trigger_line = gpiod_chip_get_line(chip, LEFT_SENSOR_PIN_TRIGGER);
    Left_echo_line = gpiod_chip_get_line(chip, LEFT_SENSOR_PIN_ECHO);

    Right_trigger_line = gpiod_chip_get_line(chip, RIGHT_SENSOR_PIN_TRIGGER);
    Right_echo_line = gpiod_chip_get_line(chip, RIGHT_SENSOR_PIN_ECHO);

    gpiod_line_request_output(Left_trigger_line, "Trigger Gauche", 0);
    gpiod_line_request_input(Left_echo_line, "Echo Gauche");

    gpiod_line_request_output(Right_trigger_line, "Trigger Droite", 0);
    gpiod_line_request_input(Right_echo_line, "Echo Droite");
}

float getDistance(struct gpiod_line *echo, struct gpiod_line *trigger) {
    
    gpiod_line_set_value(trigger, 1);
    usleep(10);
    gpiod_line_set_value(trigger, 0);

    struct timespec StartTime, StopTime, diff_echo;

    while(gpiod_line_get_value(echo) == 0) {
        clock_gettime(CLOCK_REALTIME, &StartTime);
    }

    while(gpiod_line_get_value(echo) == 1) {
        clock_gettime(CLOCK_REALTIME, &StopTime);
    }
    
    double diff_time = (((double)end.tv_sec + 1.0e-9*end.tv_nsec) -  ((double)start.tv_sec + 1.0e-9*start.tv_nsec));

    //calcul dist cm
    double distance = (diff_time * 17150);

    return distance;
}
