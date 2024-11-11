/******** Include Section ********/
#include "APP/APP.h"
#include <avr/io.h>
#include <util/delay.h>

/***********************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif



int main(){
    /******* UltraSonic init *******/
    ultraSonic_t ultraSonic_Sensor;

    ultraSonic_Sensor.ECHO_PORT = ultraSonic_ECHO_PORT;
    ultraSonic_Sensor.ECHO_PIN  = ultraSonic_ECHO_PIN;
    ultraSonic_Sensor.TRIG_PORT = ultraSonic_TRIG_PORT;
    ultraSonic_Sensor.TRIG_PIN  = ultraSonic_TRIG_PIN;

    ultraSonic_enuInit(ultraSonic_Sensor); // Pass pointer correctly
    /*******************/

    /******** Car init *********/
    Car_voidInit();
    /*******************/

    while(1){
        // Center the servo
        servo_SetAngle(90, 'A');
        _delay_ms(500); // Allow servo to stabilize

        // Get distance ahead
        ultraSonic_u16GetDistance(&ultraSonic_Sensor);
        uint16_t distance = ultraSonic_Sensor.measuredDistance_InCm;

        if(distance >= OBSTACLE_DISTANCE_THRESHOLD && distance <= MAX_DISTANCE){
            // Path is clear, move forward
            Car_voidMoveForward();
        } else {
            // Obstacle detected, stop and decide direction
            Car_voidMoveStop();

            //! Decide which direction to turn
            char turnDirection = Car_charCheckDirection(&ultraSonic_Sensor);

            switch (turnDirection) {

            	case 'L':
                    Car_voidTurnLeft(TURN_DURATION_MS);
                    break;

                case 'R':
                    Car_voidTurnRight(TURN_DURATION_MS);
                    break;

                case 'B':
                    Car_voidMoveBackward();
                    break;

                default:
                    Car_voidTurnLeft(TURN_DURATION_MS);
                    break;
            }

            // After turning, move forward for a while
            Car_voidMoveForward();
            _delay_ms(500); // Adjust the duration as needed
        }

        // Small delay to prevent rapid looping
        _delay_ms(250);
    }

    return 0;
}


