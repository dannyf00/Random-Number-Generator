#include "config.h"						//configuration words
#include "gpio.h"                           //we use gpio functions
#include "delay.h"                          //we use software delays

//hardware configuration
#define IORAND_PORT			GPIO
#define IORAND_DDR			TRISIO
#define IORAND_PIN			(1<<0)			//io pin, active high
#define GET_TMR()			(TMR0)			//read timer

#define LED_PORT			GPIO
#define LED_DDR				TRISIO
#define LED					(1<<1)
//end hardware configuration

//global defines


//global variables

//initialize the io/timer
void ioRAND_init(void) {
	//initialize the gpio
	//idles low, output
	IO_CLR(IORAND_PORT, IORAND_PIN);
	IO_OUT(IORAND_DDR, IORAND_PIN);
	
	//activate pull-up
	WPU |= IORAND_PIN;						//1->weak pull-up enabled
	OPTION_REG &=~(1<<7);					//1->enable global weak-pullup
	
	//initialize tmr0
	OPTION_REG &=~0x07;						//psa=0b000->1:2 prescaler
	OPTION_REG &=~(1<<3);					//psa=0->prescaler to tmr0
	OPTION_REG &=~(1<<5);					//t0cs=0->clock to Fcy/4
	//tmr0 always runs
}

//generate 1-bit random number
char ioRAND_get1(void) {
	char tmp;
	
	IO_IN(IORAND_DDR, IORAND_PIN);			//as input, with pull-up
	//wait for the pin to go high
	while (IO_GET(IORAND_PORT, IORAND_PIN)==0) continue;
	tmp = GET_TMR() & 0x01;					//read the counter
	IO_OUT(IORAND_DDR, IORAND_PIN);			//pin goes output, low
	while (IO_GET(IORAND_PORT, IORAND_PIN)) continue;	//wait for the pin to go low
	return tmp;
}

//generate 8-bit random number
uint8_t ioRAND_get8(void) {
	uint8_t tmp=0, mask=0x01;
	
	do {
		if (ioRAND_get1()) tmp |= mask;
		//mask = mask << 1;
	} while (mask = mask << 1);
	return tmp;
}		

//generate 16-it
uint16_t ioRAND_get16(void) {
	uint16_t tmp = 0, mask = 0x01;
	
	do {
		if (ioRAND_get1()) tmp |= mask;
		//mask = mask << 1;
	} while (mask = mask << 1);
	return tmp;
}
		
//generate 32-bit random number
uint32_t ioRAND_get32(void) {
	uint32_t tmp = 0, mask = 0x01;
	
	do {
		if (ioRAND_get1()) tmp |= mask;
		//mask = mask << 1;
	} while (mask = mask << 1);
	return tmp;
}
		
int main(void) {
	
	mcu_init();							    //initialize the mcu
	ioRAND_init();							//reset the random pin
	IO_OUT(LED_DDR, LED);					//led as output
	while (1) {
		if (ioRAND_get1() & 0x01) IO_SET(LED_PORT, LED);
		else IO_CLR(LED_PORT, LED);
		
	}
}

