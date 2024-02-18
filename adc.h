 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the AVR ADC driver
 *
 * Author: Reem Mohy
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * Description:
 * Enumeration responsible for configuration of ADC reference voltage.
 */
typedef enum
{
	EXTERNAL_AREF,AVCC_5V,RESERVED,INTERNAL_VREF
}ADC_RefrenceVoltage;

/*
 * Description:
 * Enumeration responsible for configuration of ADC prescaler division factor.
 */
typedef enum
{
	F_CPU_2=1,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,\
	F_CPU_64,F_CPU_128
}ADC_Prescaler;

/*
 * Description:
 * Structure responsible for configuration of ADC init() function.
 */
typedef struct
{
	/*Member to configure the ADC reference voltage*/
	ADC_RefrenceVoltage ref_volt;

	/*Member to configure the ADC prescaler division factor*/
	ADC_Prescaler prescaler;

}ADC_ConfigType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

#define ADC_CHANNEL0_ID      0
#define ADC_CHANNEL1_ID      1
#define ADC_CHANNEL2_ID      2
#define ADC_CHANNEL3_ID      3
#define ADC_CHANNEL4_ID      4
#define ADC_CHANNEL5_ID      5
#define ADC_CHANNEL6_ID      6
#define ADC_CHANNEL7_ID      7

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType* Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(const uint8 a_channelNum);

/*
 * Description: Function to stop the ADC Driver
 */
void ADC_deInit(void);

#endif /* ADC_H_ */
