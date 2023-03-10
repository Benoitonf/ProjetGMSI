#include "led-matrix-c.h"
#include "led-panel.h"
#include "game.h"
#include "ultrasonic_sensor.h"

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define LED_REFRESH_RATE 60 // Fréquence d'actualisation de l'écran

/**
 * Calcule la différence en secondes entre les deux structures timespec
 * @param start - le temps de départ
 * @param end - le temps de fin
 * @return la différence en secondes entre start et end
*/
double get_difftime(struct timespec start, struct timespec end) {
    return (((double)end.tv_sec + 1.0e-9*end.tv_nsec) -  ((double)start.tv_sec + 1.0e-9*start.tv_nsec));
}

void update_matrix_led(double time) {
    double rate = (1.0 / LED_REFRESH_RATE * 1e6); //µs
    double remaining_time = rate - time;

    if (remaining_time > 0) {
        usleep(remaining_time); //sleep 16.67ms : 1 / 60HZ = 0.016sec * 1e6 = 16670µs
    }
    else {
        // printf("Remaining_time : %fms | time: %fµs\n", remaining_time*1e-3, time);
    }

}

int main(int argc, char **argv)
{
    wiringPiSetupGpio();
    initialise_led_matrix(argc, argv);
    initialise_sensors();
    init_game();

    struct timespec start, end, allstart, allend;
    double diff_ms, total_ms = 0;
    int frame = 0;

    while(1) {
        clock_gettime(CLOCK_MONOTONIC, &allstart);
        clock_gettime(CLOCK_MONOTONIC, &start);
        double dist_L = getDistance(LEFT_SENSOR_PIN_ECHO, LEFT_SENSOR_PIN_TRIGGER);
        double dist_R = getDistance(RIGHT_SENSOR_PIN_ECHO, RIGHT_SENSOR_PIN_TRIGGER);
        printf("[Distance] Gauche: %.2f | Droite: %.2f\n", dist_L, dist_R);
        gameLoop();
        // usleep(1000);
        clock_gettime(CLOCK_MONOTONIC, &end);

        diff_ms = get_difftime(start, end) * 1e+3;
        // printf("Durée d'exécution : %2.0lf ms | start : %4ld sec : %3.3f nanos | end : %4ld sec : %3.3f nanos\n", 
        //     diff_ms, start.tv_sec, start.tv_nsec*1.0e-9, end.tv_sec, end.tv_nsec*1.0e-9);

        update_matrix_led(diff_ms * 1000);

        clock_gettime(CLOCK_MONOTONIC, &allend);
        diff_ms = get_difftime(allstart, allend) * 1e+3;

        // printf("Durée d'exécution : %2.0lf ms | start : %4ld sec : %3.3f nanos | end : %4ld sec : %3.3f nanos\n", 
        //     diff_ms, allstart.tv_sec, allstart.tv_nsec*1.0e-9, allend.tv_sec, allend.tv_nsec*1.0e-9);
        // printf("Durée: %.0lfms\n", diff_ms);
        frame++;
        total_ms += diff_ms;
        if (diff_ms < 0) {
            printf("Exit: >30ms, frame:%d\n", frame);
            return 1;
        }
        if (dist_L<20){
            moveVaisseau(-1);
        }
        if (dist_R<20){
            moveVaisseau(1);
        }
        if (frame % 60 == 0) {
            printf("frame: %4d | time: %2.2lfs | Moyen: %2.2lf\n", frame, total_ms*1e-3, frame / (total_ms*1e-3));
        }

    }

    delete_matrix();

    return 0;
}