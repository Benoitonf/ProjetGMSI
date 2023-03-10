#include "ultrasonic_sensor.h"

void initialise_sensors() {
    pinMode(RIGHT_SENSOR_PIN_TRIGGER, OUTPUT);
    pinMode(RIGHT_SENSOR_PIN_ECHO, INPUT);
    digitalWrite(RIGHT_SENSOR_PIN_TRIGGER, LOW);

    pinMode(LEFT_SENSOR_PIN_TRIGGER, OUTPUT);
    pinMode(LEFT_SENSOR_PIN_ECHO, INPUT);
    digitalWrite(LEFT_SENSOR_PIN_TRIGGER, LOW);
}

float getDistance(int echo, int trigger) {
    
    int i=0;
    
    digitalWrite(trigger, HIGH);
    usleep(10);
    digitalWrite(trigger, LOW);

    struct timespec StartTime, StopTime, diff_echo;

    while(digitalRead(echo) == LOW && i<10000) {
        clock_gettime(CLOCK_REALTIME, &StartTime);
        i++;
    }
    
    i=0;
    
    while(digitalRead(echo) == HIGH && i<10000) {
        clock_gettime(CLOCK_REALTIME, &StopTime);
        i++;
    }
    if ((StopTime.tv_nsec - StartTime.tv_nsec) < 0){
            diff_echo.tv_sec = StopTime.tv_sec - StartTime.tv_sec - 1;
            diff_echo.tv_nsec = 1000000000 + StopTime.tv_nsec - StartTime.tv_sec;
    } else {
            diff_echo.tv_sec = StopTime.tv_sec - StartTime.tv_sec;
            diff_echo.tv_nsec = StopTime.tv_nsec - StartTime.tv_nsec;
    }
    double echo_time = ((diff_echo.tv_sec * 1000000000) + (diff_echo.tv_nsec));
    echo_time /= 1000000000;
    //calcul dist cm
    double distance = (echo_time * 17150);

    return distance;
}
