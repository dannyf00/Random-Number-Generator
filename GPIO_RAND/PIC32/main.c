#include "config.h"						//configuration words
#include "gpio.h"
#include "delay.h"						//we use software delays
#include "tmr1.h"						//we use tmr1
#include "iorand.h"						//use gpio to generate a random number

//hardware configuration
#define LED_PORT			LATB
#define LED_DDR				TRISB
#define LED					(1<<7)
#define LED_DLY				40000		//cycles to be wasted -> to manage main loop update frequency
//end hardware configuration

//global defines

//global variables
//flip the led
void led_flp(void) {
	IO_FLP(LED_PORT, LED);
}

char uRAM[40]="uart0 = \n\r";

int main(void) {
	uint16_t i=0, i1;
	uint32_t tmp, cnt=0;

	mcu_init();						//reset the mcu

	IO_OUT(LED_DDR, LED);			//led as output
	
	//tmr1_init(TMR1_PS_8x, 0);		//reset tmr1
	//i=TMR1;							//reset tmr1
	
	iorand_init();					//reset the io pin
	while (1) {
		//if ((uint16_t) (TMR1 - i) > LED_DLY) {
		//	i += LED_DLY;
		//	IO_FLP(LED_PORT, LED);		//flip the led
		//}

		//set or clear an led based on a random bit
		if (iorand1()) IO_SET(LED_PORT, LED);
		else IO_CLR(LED_PORT, LED);
		delay_ms(20);				//waste sometime
	}
}
