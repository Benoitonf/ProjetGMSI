
/* -*- mode: c; c-basic-offset: 2; indent-tabs-mode: nil; -*-
 *
 * Using the C-API of this library.
 *
 */
//sudo ./main --led-no-hardware-pulse --led-gpio-mapping=adafruit-hat
#include "led-matrix-c.h"
#include "led-panel.h"
#include "ultrasonic_sensor.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    wiringPiSetupGpio();
    initialise_led_matrix(argc, argv);
    initialise_sensors();

    // fprintf(stderr, "Size: %dx%d. Hardware gpio mapping: %s\n",
    //         width, height, options.hardware_mapping);

    while(1) {
        float L_dist = getDistance(LEFT_SENSOR_PIN_ECHO, LEFT_SENSOR_PIN_TRIGGER);
        float R_dist = getDistance(RIGHT_SENSOR_PIN_ECHO, RIGHT_SENSOR_PIN_TRIGGER);

        if (L_dist > 0 && L_dist < 20) {
            set_pixel(0, 0, 255, 255, 255);
        }

        if (R_dist > 0 && R_dist < 20) {
            set_pixel(31, 0, 255, 255, 255);
        }
        actualize();
    }

    delete_matrix();

    return 0;
}
