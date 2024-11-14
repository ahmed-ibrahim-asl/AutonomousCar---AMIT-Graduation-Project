/******** Include Section ********/
#include "APP/APP.h"
#include <avr/io.h>
#include <util/delay.h>

/***********************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif



int main(){
    /******************* UltraSonic INIT *******************/
    ultraSonic_t ultraSonic_Sensor;

    ultraSonic_Sensor.ECHO_PORT = ultraSonic_ECHO_PORT;
    ultraSonic_Sensor.ECHO_PIN  = ultraSonic_ECHO_PIN;
    ultraSonic_Sensor.TRIG_PORT = ultraSonic_TRIG_PORT;
    ultraSonic_Sensor.TRIG_PIN  = ultraSonic_TRIG_PIN;

    ultraSonic_enuInit(ultraSonic_Sensor);
    /*******************************************************/

	/********************** Car INIT ***********************/
    Car_voidInit();
	/*******************************************************/


    uint16_t local_u16distance;

    while(1){

        // Get distance ahead
        ultraSonic_u16GetDistance(&ultraSonic_Sensor);
        local_u16distance = ultraSonic_Sensor.measuredDistance_InCm;


        if(local_u16distance >= OBSTACLE_DISTANCE_THRESHOLD && local_u16distance <= MAX_DISTANCE){
            // Path is clear, move forward
            Car_voidMoveForward();
        } else {
            // Obstacle detected, stop and decide direction
            Car_voidMoveStop();

            // Decide which direction to turn

            switch (Car_charCheckDirection(&ultraSonic_Sensor)) {
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


        }

        // Small delay to prevent rapid looping
        _delay_ms(100);
    }


    return 0;
}


