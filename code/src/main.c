
/* -*- mode: c; c-basic-offset: 2; indent-tabs-mode: nil; -*-
 *
 * Using the C-API of this library.
 *
 */
//sudo ./main --led-no-hardware-pulse --led-gpio-mapping=adafruit-hat
#include "led-matrix-c.h"
#include "led-panel.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    initialise_led_matrix(argc, argv);

    // fprintf(stderr, "Size: %dx%d. Hardware gpio mapping: %s\n",
    //         width, height, options.hardware_mapping);


    delete_matrix();

    return 0;
}
