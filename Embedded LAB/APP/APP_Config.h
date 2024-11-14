/*
 * APP_Config.h
 *
 *  Created on: Nov 8, 2024
 *      Author: ad
 */

#ifndef APP_APP_CONFIG_H_
#define APP_APP_CONFIG_H_



/*************************** Car Pins ****************************/
#define Car_PORT           				DIO_u8PortB
#define Car_PIN0           				DIO_u8PIN0
#define Car_PIN1           				DIO_u8PIN1
#define Car_PIN2           				DIO_u8PIN2
#define Car_PIN3          				DIO_u8PIN3
/*****************************************************************/


/************************ UltraSonic Pins ************************/
#define ultraSonic_ECHO_PORT			DIO_u8PortC
#define ultraSonic_ECHO_PIN				DIO_u8PIN0

#define ultraSonic_TRIG_PORT			DIO_u8PortC
#define ultraSonic_TRIG_PIN				DIO_u8PIN1
/*****************************************************************/

// Minimum distance to an obstacle in cm
#define OBSTACLE_DISTANCE_THRESHOLD 65

// Maximum sensing distance
#define MAX_DISTANCE 				200

// Duration for turning (adjust as needed)
#define TURN_DURATION_MS 			700




#endif /* APP_APP_CONFIG_H_ */
