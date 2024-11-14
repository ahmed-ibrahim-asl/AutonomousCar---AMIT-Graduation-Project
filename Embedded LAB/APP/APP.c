/*
 * APP.c
 *
 *  Created on: Nov 8, 2024
 *      Author: ad
 */
/************************ Include Section ************************/
#include "APP.h"
/*****************************************************************/



void Car_voidInit(void){

	/********************* Servo init *********************/
	servo_init();
	servo_SetAngle(90, 'a');
	_delay_ms(500); // Allow servo to stabilize
	/******************************************************/


	/********************** LCD init **********************/
	LCD_enuInit();

	//Any intial text
	LCD_u8SendString("Autonomous Car");
	/******************************************************/

	/*************** set car pins direction ****************/
	DIO_enuSetPinDirection(Car_PORT, Car_PIN0, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(Car_PORT, Car_PIN1, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(Car_PORT, Car_PIN2, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(Car_PORT, Car_PIN3, DIO_u8OUTPUT);
	/*******************************************************/

}

void Car_voidMoveForward(void){
    LCD_enuClearDisplay();
    LCD_u8SetPosXY(0, 1);
    LCD_u8SendString("Move Forward");

	DIO_enuSetPinValue(Car_PORT, Car_PIN0, DIO_u8HIGH);
	DIO_enuSetPinValue(Car_PORT, Car_PIN1, DIO_u8LOW);

	DIO_enuSetPinValue(Car_PORT, Car_PIN2, DIO_u8HIGH);
	DIO_enuSetPinValue(Car_PORT, Car_PIN3, DIO_u8LOW);
}

void Car_voidMoveBackward(void){
    LCD_enuClearDisplay();
    LCD_u8SetPosXY(0, 1);
    LCD_u8SendString("Move Backward");

	DIO_enuSetPinValue(Car_PORT, Car_PIN0, DIO_u8LOW);
	DIO_enuSetPinValue(Car_PORT, Car_PIN1, DIO_u8HIGH);

	DIO_enuSetPinValue(Car_PORT, Car_PIN2, DIO_u8LOW);
	DIO_enuSetPinValue(Car_PORT, Car_PIN3, DIO_u8HIGH);
}

void Car_voidMoveStop(void){
    LCD_enuClearDisplay();
    LCD_u8SetPosXY(0, 1);
    LCD_u8SendString("Car STOP");


	DIO_enuSetPinValue(Car_PORT, Car_PIN0, DIO_u8LOW);
	DIO_enuSetPinValue(Car_PORT, Car_PIN1, DIO_u8LOW);

	DIO_enuSetPinValue(Car_PORT, Car_PIN2, DIO_u8LOW);
	DIO_enuSetPinValue(Car_PORT, Car_PIN3, DIO_u8LOW);
}
////////


void Car_voidMoveRight(void){
	DIO_enuSetPinValue(Car_PORT, Car_PIN0, DIO_u8HIGH);
	DIO_enuSetPinValue(Car_PORT, Car_PIN1, DIO_u8LOW);

	DIO_enuSetPinValue(Car_PORT, Car_PIN2, DIO_u8LOW);
	DIO_enuSetPinValue(Car_PORT, Car_PIN3, DIO_u8HIGH);
}

void Car_voidMoveLeft(void){
	DIO_enuSetPinValue(Car_PORT, Car_PIN0, DIO_u8LOW);
	DIO_enuSetPinValue(Car_PORT, Car_PIN1, DIO_u8HIGH);

	DIO_enuSetPinValue(Car_PORT, Car_PIN2, DIO_u8HIGH);
	DIO_enuSetPinValue(Car_PORT, Car_PIN3, DIO_u8LOW);
}
////////


void Car_voidTurnLeft(uint16_t copy_u16Duration_ms){
    LCD_enuClearDisplay();
    LCD_u8SetPosXY(0, 1);
    LCD_u8SendString("Turning Left");

    // Perform left turn
    Car_voidMoveLeft();
    _delay_ms(copy_u16Duration_ms);
    Car_voidMoveStop();

    // Center the servo
    servo_SetAngle(90, 'A');
    _delay_ms(500);
}

void Car_voidTurnRight(uint16_t copy_u16Duration_ms){
    LCD_enuClearDisplay();
    LCD_u8SetPosXY(0, 1);
    LCD_u8SendString("Turning Right");

    // Perform right turn
    Car_voidMoveRight();
    _delay_ms(copy_u16Duration_ms);
    Car_voidMoveStop();

    // Center the servo
    servo_SetAngle(90, 'A');
    _delay_ms(500);
}
////////


char Car_charCheckDirection(ultraSonic_t* ultraSonic_Sensor){
    uint16_t Local_u16DistanceLeft, Local_u16DistanceRight;

    // Check Left
    servo_SetAngle(180, 'A');
    _delay_ms(500);
    ultraSonic_u16GetDistance(ultraSonic_Sensor);
    Local_u16DistanceLeft = ultraSonic_Sensor->measuredDistance_InCm;
    LCD_enuClearDisplay();
    LCD_enuIntegerToString(ultraSonic_Sensor->measuredDistance_InCm, 10);

    // Check Right
    servo_SetAngle(0, 'A');
    _delay_ms(500);
    ultraSonic_u16GetDistance(ultraSonic_Sensor);
    Local_u16DistanceRight = ultraSonic_Sensor->measuredDistance_InCm;
    LCD_enuClearDisplay();
    LCD_enuIntegerToString(ultraSonic_Sensor->measuredDistance_InCm, 10);

    // Center the servo after scanning
    servo_SetAngle(90, 'A');
    _delay_ms(500);


    // Car Logic
    if(Local_u16DistanceLeft >= OBSTACLE_DISTANCE_THRESHOLD && Local_u16DistanceRight >= OBSTACLE_DISTANCE_THRESHOLD){
        if(Local_u16DistanceLeft >= Local_u16DistanceRight){
            return 'L';

        } else {
            return 'R';

        }

    } else if(Local_u16DistanceLeft >= OBSTACLE_DISTANCE_THRESHOLD){
        return 'L';

    } else if(Local_u16DistanceRight >= OBSTACLE_DISTANCE_THRESHOLD){
        return 'R';

    } else {
        return 'B';

    }
}

