#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "dpram.h"
#include <string.h>    // Used for memcpy


/*
PORTD:
  7: LED
  6: CE
  5: RESET
  4: OE
  3: RW
  2: VUSB+
  1: VUSB-2
  0: VUSB-

*/

#define CE_HIGH PORTD |=  0b01000000
#define CE_LOW  PORTD &= ~0b01000000
//#define CE_LOW  PORTD &=  0b10111111

#define RW_HIGH PORTD |=  0b00001000
#define RW_LOW  PORTD &= ~0b00001000
//#define RW_LOW  PORTD &=  0b11110111

#define OE_HIGH PORTD |=  0b00010000
#define OE_LOW  PORTD &= ~0b00010000
//#define OE_LOW  PORTD &=  0b11101111

#define D_IN    DDRA   =  0b00000000
#define D_OUT   DDRA   =  0b11111111


void DPRAM_init() {
	DDRC  = 0b11111111;	// A0..A7 as output
// 	DDRB |= 0b00111111;	// A8..A13 as output
	DDRB  = 0b11111111;	// EXROM+GAME (PB7+PB6) and A8..A13 as output
	DDRA  = 0b00000000;	// D0..D7 as input
	DDRD |= 0b11111000;	// CE, OE, RW as output

	CE_LOW;
	OE_LOW;
	RW_HIGH;			// RW_HIGH is Read, RW_LOW is Write
}

/*
void DPRAM_setaddress(uint16_t addr) {
	PORTB &= 0b11000000;
	PORTB |= (addr >> 8) & 0b00111111;
	PORTC = addr & 0xff;

}*/

void DPRAM_clear(uint16_t addr, uint16_t len) {
	/* Clears the DPRAM by writeing 0x0 to every address specified..
	 */
	uint16_t a = 0;
	for( a=addr; a<addr+len; a++ )
		DPRAM_write( a, 0 );
}

void DPRAM_write( uint16_t addr, uint8_t byte ) {
	/* Nifty function to write a address to the RAM.
	 * Changes position to requested address and writes data to the chip..
	 * After data is written DATA pins is changed back to INPUT
	 * Don't know if timing is 100%.. migth need to bee tunes..
	 */
//	CE_HIGH;
	OE_LOW;
	D_OUT;
	PORTA = byte;

	// MABY:   PORTB = (PORTB & 0b11000000) | ((addr >> 8) & 0b00111111);
	//   OR:   PORTB = (PORTB & 0xC0) | ((addr >> 8) & 0x3F);
	PORTB &= 0b11000000;
	PORTB |= (addr >> 8) & 0b00111111;
	PORTC = addr & 0xff;
	//DPRAM_setaddress(addr);
	RW_LOW;
	_delay_us(35);
//	CE_HIGH;
	RW_HIGH;
	OE_HIGH;
//	CE_LOW;
	_delay_us(30);
	D_IN;
}

uint8_t DPRAM_read( uint16_t addr) {
	/* Nifty function to read a address from the RAM.
	 * Changes position to requested address and reads out data
	 * Don't know if timing is 100%.. migth need to bee tunes..
	 */
	uint8_t buff;

	// MABY:   PORTB = (PORTB & 0b11000000) | ((addr >> 8) & 0b00111111);
	//   OR:   PORTB = (PORTB & 0xC0) | ((addr >> 8) & 0x3F);
	PORTB &= 0b11000000;
	PORTB |= (addr >> 8) & 0b00111111;
	PORTC = addr & 0xff;
	//DPRAM_setaddress(addr);
//	CE_LOW;
	OE_LOW;
	_delay_us(35);
	buff = PINA;
	OE_HIGH;
//	CE_HIGH;
	_delay_us(30);

	return buff;

}

uint8_t DPRAM_verify(uint16_t addr, uint16_t len) {
	/* Last four bits of address is written as data to the address.
	 * Verify checks all adresses after every byte is written and returns 0 if  an error is detected
	 * There is no check for "END OF RAM", so if you write after the end it will wrap over to begining of ram
	 */
	uint16_t a = addr;
	for( a=addr; a<addr+len; a++ )
		DPRAM_write( a,  a & 0x0F);

	for( a=addr; a<len; a++ )
		if (DPRAM_read(a) != (a & 0x0F) )
			return 0;
	return 1;
}

uint16_t DPRAM_size() {
	/* Check size of DPRAM chip, function writes to 0x0 on chip and checkes if that value exists in 0x2000.
	 * If it does, the check is done again with another value to rule out old data on that address..
	 * function returns the size in bytes.  
	 * supported ram sizes: 
	 *   16k(0x4000) and 
	 *    8k(0x2000) 
	 * After size is calculated the original value is written back to address 0x0 
	 */
	uint8_t old_data = DPRAM_read(0x0);		// Save old value
	DPRAM_write(0x0, 0x0);               	// Clear address



	uint16_t size = 0x4000;					// Mark ram as largest value.. in this case 16K

	// Check if ram is 8k
	DPRAM_write(0x0, 0xAB);					// Write test value to 0x0
	if (DPRAM_read(0x2000) == 0xAB) {		// Try to read test value from 0x2000 
		DPRAM_write(0x0, 0xCD);				// If test suxeeds, write new value to 0x0 and test again.. 
		if (DPRAM_read(0x2000) == 0xCD)		// Try to read new test value from 0x2000.
			size = 0x2000;					// Mark ram as 8k
	}


	DPRAM_write(0x0, old_data);
	return size;
}