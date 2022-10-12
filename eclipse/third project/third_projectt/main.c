/*
 * main.c
 *
 *  Created on: Oct 11, 2022
 *      Author: youssef magdy
 */


#include "adc.h"
#include "lcd.h"
#include "motor.h"
#include "lm35_sensor.h"

int main(void)
{
    uint8 temp;

	ADC_ConfigType adc_config = {INTERNAL, F_CPU_8}; /* Create configuration structure for ADC driver */
    ADC_init(&adc_config);                           /* initialize ADC driver */
	LCD_init();                                      /* initialize LCD driver */
	DcMotor_Init();                                  /* initialize MOTOR driver */

	/* Display this string "FAN is " only once on LCD at the first row */
	LCD_moveCursor(0,5);
	LCD_displayString("FAN is ");

	/* Display this string "Temp =   C" only once on LCD at the second row */
	LCD_moveCursor(1,5);
	LCD_displayString("Temp =     C");
	while (1)
	{
		temp = LM35_getTemperature();
				/* Display the temperature value every time at same position */
				LCD_moveCursor(1,13);
				if(temp >= 100)
				{
					LCD_intgerToString(temp);
				}
				else
				{
					LCD_intgerToString(temp);
					/* In case the digital value is two or one digits print space in the next digit place */
					LCD_displayCharacter(' ');
				}

				/*
				 * Display the fan state every time at same position.
				 * Depends on the temperature value change the motor speed and state every time.
				 */
				LCD_moveCursor(0,12);
				if (temp < 30)
				{
		            LCD_displayString("OFF");
					DcMotor_Rotate(OFF,0);      /*turn motor off and no speed*/
				}
				else if (temp >= 30 && temp < 60)
				{
					LCD_displayString("ON");
					DcMotor_Rotate(CW,25);      /*turn motor on with 25% of it's speed*/
				}
				else if (temp >=60 && temp < 90)
				{
					LCD_displayString("ON");
					DcMotor_Rotate(CW,50);      /*turn motor on with 50% of it's speed*/
				}
				else if (temp >=90 && temp < 120)
				{
					LCD_displayString("ON");
					DcMotor_Rotate(CW,75);      /*turn motor on with 75% of it's speed*/
				}
				else if (temp >=120)
				{
					LCD_displayString("ON");
					DcMotor_Rotate(CW,100);     /*turn motor on with 100% of it's speed*/
				}
			}
	}



