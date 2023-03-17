// Description----------------------------------------------------------------|
/*
 *
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#define STM32F051												   //COMPULSORY
#include "stm32f0xx.h"											   //COMPULSORY
#include "lcd_stm32f0.h"
#include <stdio.h>

// GLOBAL VARIABLES ----------------------------------------------------------|




// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);
void display_on_LCD(uint8_t num);
void init_LEDs(void);
void display_on_LEDs(uint8_t val);

// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{	init_LEDs();
	display_on_LEDs(2);


	while(1)
	{

	}
}
// OTHER FUNCTIONS -----------------------------------------------------------|

void display_on_LCD(uint8_t num){ //function to intiate LED
	char str[3];
	sprintf(str,"%d",num);
	lcd_putstring(str);
}

void init_LEDs(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= (
				 GPIO_MODER_MODER0_0|
				 GPIO_MODER_MODER1_0|
				 GPIO_MODER_MODER2_0|
				 GPIO_MODER_MODER3_0|
				 GPIO_MODER_MODER4_0|
				 GPIO_MODER_MODER5_0|
				 GPIO_MODER_MODER6_0|
				 GPIO_MODER_MODER7_0);
}

void display_on_LEDs(uint8_t val){
	GPIOB-> ODR = val;
}



