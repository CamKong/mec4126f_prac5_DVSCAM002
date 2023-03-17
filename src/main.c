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

// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{


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




