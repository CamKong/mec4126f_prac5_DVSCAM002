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
uint8_t SW3Pressed();
void init_external_interrupts(void);
void EXTI2_3_IRQHandler(void);
uint8_t SW3_count=0; // sets push button 3 count to 0

// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{	init_LEDs();
	init_switches();
	init_LCD();
	init_external_interrupts();
	uint8_t count=0;


	while(1)
	{

		if((SW3_count)%2 != 0) //checks to see if SW3 count is positive or negative, if negative..
			{

				display_on_LCD(count); //displays count on LCD
				delay(50000);
				if (SW1Pressed()) //checks if SW1 has been pressed
				{
					if (count==255); //ignores if higher than 255
					else{			//increments if value is less than 255
						count+=1;
					}
				}
				else if (SW2Pressed()){ //decrements count if SW2 is pressed
					count-=1;
				}

				display_on_LCD(count); //displays count on LCD
				display_on_LEDs(count); //displays count on LED

			}
		else{
			lcd_command(CLEAR);
		}
	}
}
// OTHER FUNCTIONS -----------------------------------------------------------|
//function to intiate LCD
void display_on_LCD(uint8_t num){
	lcd_command(CLEAR);
	char str[3];
	sprintf(str,"%d",num);
	lcd_putstring(str);


}

void init_LEDs(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;//activates the clock for GPIOB
	GPIOB->MODER |= (
				 GPIO_MODER_MODER0_0|	//sets all values of LED to output
				 GPIO_MODER_MODER1_0|
				 GPIO_MODER_MODER2_0|
				 GPIO_MODER_MODER3_0|
				 GPIO_MODER_MODER4_0|
				 GPIO_MODER_MODER5_0|
				 GPIO_MODER_MODER6_0|
				 GPIO_MODER_MODER7_0);
}

void display_on_LEDs(uint8_t val){ // sets output value of LED's to a given value (val)
	GPIOB-> ODR = val;
}

void init_switches(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;//activates the clock for GPIOA
	GPIOA->PUPDR |= (
				 GPIO_PUPDR_PUPDR1_0| // set pullup/pulldown resistor to pull up (read high when not pressed)
				 GPIO_PUPDR_PUPDR2_0|
				 GPIO_PUPDR_PUPDR3_0);
}

uint8_t readSwitches(){  // reads the state of push buttons 1 and 2
	 return GPIOA-> IDR & 0b1110;
}
//function to determine if push button 1 has been pressed
uint8_t SW1Pressed(){
	readSwitches();
	return readSwitches() & 0b010 ? 0:1; //when reading switch 1: if reads 0(then it means its been pressed) then so it will equate to false for the bitwise comparison
	                                     //but we want it to evaluate as true(the button has been pressed) when a false value is read from the comparison

 }
//function to determine if push button 2 has been pressed
uint8_t SW2Pressed(){
	readSwitches();
	return readSwitches() & 0b100 ? 0:1;

 }
//function to determine if push button 3 has been pressed
uint8_t SW3Pressed(){
	readSwitches();
	return readSwitches() & 0b1000 ? 0:1;

 }

void init_external_interrupts(void){
	RCC->APB2ENR|=RCC_APB2ENR_SYSCFGCOMPEN; //enable clock for sysconfig
	SYSCFG->EXTICR[0]|=SYSCFG_EXTICR1_EXTI3_PA; //route PA to EXTI3
	EXTI->IMR |=EXTI_IMR_IM3;					//unmask the interrupt on PA3
	EXTI->FTSR |=EXTI_FTSR_TR3;					//falling edge trigger

	NVIC_EnableIRQ(EXTI2_3_IRQn);				//enable the EXTI2_3 interrupt on NVIC


}

void EXTI2_3_IRQHandler(void){
	SW3_count+=1;		//increment the SW3 counter
	EXTI->PR|=EXTI_PR_PR3;// clear the interrupt pending bit by writing to it
}
