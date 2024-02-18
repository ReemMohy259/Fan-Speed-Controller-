/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the AVR ADC driver
 *
 * Author: Reem Mohy
 *
 *******************************************************************************/

#include <avr/io.h> /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros in some operations */


/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/*Insert the required reference voltage in ADMUX register in RERS1:0 bits*/
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt) <<6);

	/* ADMUX Register Bits Description:
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX &= 0xC0;

	/*Insert the required ADC_Prescaler in ADCSRA register in ADPS2:0 bits */
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 */
	ADCSRA |= (1<<ADEN);
}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(const uint8 a_channelNum)
{
	ADMUX = (ADMUX & 0xE0) | (a_channelNum & 0x07); /* Choose the correct channel by setting the channel number in MUX4:0 bits */

	SET_BIT(ADCSRA,ADSC); /* Start conversion */

	/*Polling*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, until Flag(ADIF) becomes '1' */

	SET_BIT(ADCSRA,ADIF); /* Clear the flag(ADIF) by write logic '1' to it */

	return ADC; /* Read the digital value from the data register */
}
