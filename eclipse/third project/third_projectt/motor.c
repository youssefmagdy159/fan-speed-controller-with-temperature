/*
 * motor.c
 *
 *  Created on: Oct 11, 2022
 *      Author: youssef magdy
 */
#include "motor.h"
#include "gpio.h"
#include "pwm.h"

void DcMotor_Init(void){

	/*
	 * setup motor pins as output pins
	 */
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);

	/*
	 * make the motor at the first stop
	 */
	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);


}

  void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	PWM_Timer0_Start(speed);

	if (state == CW)
	{
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_HIGH);
			GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);

	}
	if (state == A_CW )
	{
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
			GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_HIGH);

	}

	else if (state == OFF)
	{
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
			GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);


	}
}
