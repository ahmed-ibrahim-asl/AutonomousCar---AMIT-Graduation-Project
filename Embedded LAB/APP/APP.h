/*
 * APP.h
 *
 *  Created on: Nov 8, 2024
 *      Author: ad
 */

#ifndef APP_APP_H_
#define APP_APP_H_

/************************ Include Section ************************/
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/LCD/LCD_HAL_interface.h"
#include "../HAL/servoMotor/servo_interface.h"
#include "../HAL/ultraSonic/ultraSonic_interface.h"
#include "APP_Config.h"
#include <util/delay.h>
/*****************************************************************/


/************************** Car Movment **************************/
void Car_voidInit(void);
void Car_voidMoveForward(void);
void Car_voidMoveBackward(void);
void Car_voidMoveStop(void);

void Car_voidMoveRight(void);
void Car_voidMoveLeft(void);

void Car_voidTurnLeft(uint16_t copy_u16Duration_ms);
void Car_voidTurnRight(uint16_t copy_u16Duration_ms);
///////////

char Car_charCheckDirection(ultraSonic_t* ultraSonic_Sensor);


#ifndef F_CPU
	#define F_CPU 16000000
#endif


#endif /* APP_APP_H_ */
