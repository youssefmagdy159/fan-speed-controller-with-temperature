 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: youssef magdy
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*********************** functions *********************
 */
void ADC_init(const ADC_ConfigType *Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 *
	 * insert the required voltage reference in the last two pits ( REFS0 , REFS1 )
	 * of ADMUX register
	 */
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<6);

	/* ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (ADMUX & 0xE0);

	/* ADCSRA Register Bits Description:
	 *
	 * insert the required prescaler in the first three pits ( ADPS0 , ADPS1 , ADPS2 )
	 * of ADCSRA register -->  ADC must operate in range 50-200Khz
	 */
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);

	/* ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 */
	ADCSRA |= (1<<ADEN);
}

uint16 ADC_readChannel(uint8 channel_num)
{
	 /* Input channel number must be from 0 --> 7 */
	 /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);

	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
