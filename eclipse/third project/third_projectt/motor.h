/*
 * motor.h
 *
 *  Created on: Oct 11, 2022
 *      Author: youssef magdy
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"


#define MOTOR_PORT_ID  PORTB_ID
#define MOTOR_PIN1_ID  PIN1_ID
#define MOTOR_PIN0_ID  PIN0_ID

typedef enum{
	CW, A_CW, OFF
}DcMotor_State;

void DcMotor_Init(void);

  void DcMotor_Rotate(DcMotor_State state,uint8 speed);



#endif /* MOTOR_H_ */
