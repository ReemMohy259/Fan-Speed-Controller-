/*
 ============================================================================
 Name        : fan_control.c
 Author      : Reem Mohy
 Description : Fan Controller system
 Date        : 9/10/2022
 ============================================================================
 */

#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"

int main(void)
{
	uint8 temp_value = 0;

	/*Create configuration structure for ADC driver use internal Vref=2.56V and prescaler=8*/
	ADC_ConfigType s_adcData = {INTERNAL_VREF,F_CPU_8};

	LCD_init();      /* initialize LCD driver */
	ADC_init(& s_adcData);      /* initialize ADC driver */
	DcMotor_init();  /* initialize DC-Motor driver */

	/*Display this string once*/
	LCD_displayStringRowColumn(0,1,"=>FAN is ");
	LCD_displayStringRowColumn(1,2,"*TEMP = ");
	LCD_displayStringRowColumn(1,13,"C*");

	while(1)
	{
		temp_value = LM35_getTemperature();  /*read the current temperature from sensor*/

		/*display temperature value on the screen*/
		LCD_moveCursor(1,10);

		if(temp_value >= 100)
		{
			LCD_intgerToString(temp_value);
		}
		else
		{
			LCD_intgerToString(temp_value);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

		/*control the speed of DC-Motor as required according to temperature value*/
		if(temp_value < 30)
		{
			LCD_displayStringRowColumn(0,10,"OFF");;
			/*stop the DC-Motor*/
			DcMotor_rotate(STOP,0);
		}
		else if(temp_value < 60)
		{
			LCD_displayStringRowColumn(0,10,"ON ");
			/*rotate the DC-Motor by 25% from its maximum speed*/
			DcMotor_rotate(CLOCK_WISE,25);
		}
		else if(temp_value < 90)
		{
			LCD_displayStringRowColumn(0,10,"ON ");
			/*rotate the DC-Motor by 50% from its maximum speed*/
			DcMotor_rotate(CLOCK_WISE,50);
		}
		else if(temp_value < 120)
		{
			LCD_displayStringRowColumn(0,10,"ON ");
			/*rotate the DC-Motor by 75% from its maximum speed*/
			DcMotor_rotate(CLOCK_WISE,75);
		}
		else
		{
			LCD_displayStringRowColumn(0,10,"ON ");
			/*rotate the DC-Motor by 100% from its maximum speed*/
			DcMotor_rotate(CLOCK_WISE,100);
		}
	}
}
