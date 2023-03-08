#include "led-panel.h"

struct RGBLedMatrix *matrix;
struct LedCanvas *offscreen_canvas;
int width, height;

int initialise_led_matrix(int argc, char **argv) {
    struct RGBLedMatrixOptions options;
    memset(&options, 0, sizeof(options));
    options.rows = 32;
    options.chain_length = 2;
    options.brightness = 75;
    options.disable_hardware_pulsing = true;
    options.hardware_mapping = "adafruit-hat";

    /* This supports all the led commandline options. Try --led-help */
    matrix = led_matrix_create_from_options(&options, &argc, &argv);
    if (matrix == NULL)
        return 1;

    /* Let's do an example with double-buffering. We create one extra
     * buffer onto which we draw, which is then swapped on each refresh.
     * This is typically a good aproach for animations and such.
     */
    offscreen_canvas = led_matrix_create_offscreen_canvas(matrix);

    led_canvas_get_size(offscreen_canvas, &width, &height);

}

void set_pixel(int x, int y, int R, int G, int B) {
    x = (height - 1) - x;
    //Faire les tests de vérification
    led_canvas_set_pixel(offscreen_canvas, y, x, R, G, B);
}

void clear() {
    led_canvas_clear(offscreen_canvas);
}

void actualize() {
    /* Now, we swap the canvas. We give swap_on_vsync the buffer we
    * just have drawn into, and wait until the next vsync happens.
    * we get back the unused buffer to which we'll draw in the next
    * iteration.
    */
    offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);
}

void delete_matrix() {
    /*
     * Make sure to always call led_matrix_delete() in the end to reset the
     * display. Installing signal handlers for defined exit is a good idea.
     */
    led_matrix_delete(matrix);
}