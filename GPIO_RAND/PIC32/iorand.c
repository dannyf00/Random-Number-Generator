#include "iorand.h"

//hardware configuration
//end hardware configuration

//global defines
#define GET_TMR()		(TMR1)		//the free running timer is TMR1

//global variables

//initialize the pins
void iorand_init(void) {
	//pin idles low, as output
	IO_CLR(IORAND_PORT, IORAND_PIN); IO_OUT(IORAND_DDR, IORAND_PIN);
	//weak pull-up enabled - alternatively use an external pull-up
	CNPUB |= IORAND_PIN;
	
	//reset the timer
	tmr1_init(TMR1_PS_1x, 0);			//free running timer, top at 0xffff
	//timer1 running now
	
}

//generate 1-bit random output
char iorand1(void) {	
	char tmp;
	
	//starts to charge up the capacitor
	IO_IN(IORAND_DDR, IORAND_PIN);
	while (IO_GET(IORAND_PORT, IORAND_PIN) == 0) continue;	//wait until the pin is fully charged up
	tmp = GET_TMR();					//get the timer's lsb
	IO_OUT(IORAND_DDR, IORAND_PIN);	//discharge the pin
	while (IO_GET(IORAND_PORT, IORAND_PIN)) continue;		//wait until the pin is fully discharged
	return tmp & 0x01;
}	

//generate 8-bit random output
uint8_t iorand8(void) {
	uint8_t tmp = 0, mask = 0x01;
	
	do {
		if (iorand1()) tmp |= mask;
	} while (mask = mask << 1);
	return tmp;
}
		
//generate 16-bit random output
uint16_t iorand16(void) {
	uint16_t tmp = 0, mask = 0x01;
	
	do {
		if (iorand1()) tmp |= mask;
	} while (mask = mask << 1);
	return tmp;
}

//generate 8-bit random output
uint32_t iorand32(void) {
	uint32_t tmp = 0, mask = 0x01;
	
	do {
		if (iorand1()) tmp |= mask;
	} while (mask = mask << 1);
	return tmp;
}
