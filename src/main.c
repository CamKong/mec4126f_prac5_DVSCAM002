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
void init_switches();
void delay(unsigned int ms);
uint8_t readSwitches();
uint8_t SW1Pressed();
uint8_t SW2Pressed();

// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{	init_LEDs();
	init_switches();
	init_LCD();
	char count=0;


	while(1) {
		delay(50000);
		if (SW1Pressed()){
			count+=1;
		}
		if (SW2Pressed()){
			count-=1;
		};

		display_on_LCD(count);
		display_on_LEDs(count);



	}
}
// OTHER FUNCTIONS -----------------------------------------------------------|

void display_on_LCD(uint8_t num){
	lcd_command(CLEAR);  //function to intiate LED
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

void init_switches(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->PUPDR |= (
				 GPIO_PUPDR_PUPDR1_0|
				 GPIO_PUPDR_PUPDR2_0);
}

uint8_t readSwitches(){
	 return GPIOA-> IDR & 0b110;
}

uint8_t SW1Pressed(){
	readSwitches();
	return readSwitches() & 0b010 ? 0:1;

 }

uint8_t SW2Pressed(){
	readSwitches();
	return readSwitches() & 0b100 ? 0:1;

 }

