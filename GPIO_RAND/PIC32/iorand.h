#ifndef IORAND_H
#define IORAND_H

#include "gpio.h"						//we use gpio
#include "tmr1.h"						//we use tmr1


//hardware configuration
#define IORAND_PORT			PORTB
#define IORAND_DDR			TRISB
#define IORAND_PIN			(1<<5)
//end hardware configuration

//global defines
//#define IORAND_GET()		(TMR1 & 0x01)

//global variables

//initialize the pins
void iorand_init(void);

//generate 1-bit random output
char iorand1(void);

//generate 8-bit random output
uint8_t iorand8(void);
		
//generate 16-bit random output
uint16_t iorand16(void);

//generate 8-bit random output
uint32_t iorand32(void);

#endif