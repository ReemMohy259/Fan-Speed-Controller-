 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.c
 *
 * Description: Source file for the LM35 Temperature Sensor driver
 *
 * Author: Reem Mohy
 *
 *******************************************************************************/

#include "lm35_sensor.h"
#include "adc.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void)
{
	uint8 tempValue = 0;

	uint16 adcValue = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adcValue = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	tempValue = (uint8)(((uint32)adcValue*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return tempValue;
}

