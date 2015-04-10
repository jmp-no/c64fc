#include <avr/io.h>
#include <util/delay.h>

void C64_init() {
	DDRB |= 0b11000000;	     // EXROM+GAME (PB7+PB6)
	DDRD  |= 0b00100000;     // C64 RESET
}

void C64_Reset() {


	PORTD |= 0b00100000;	// reset line high (Q1 pulls it low)

	_delay_ms(50);

	PORTD &= ~0b00100000;	// draw reset line low
	//PORTD &= 0b11011111;	// draw reset line low
}





/*
NO CART  0kB                                     : GAME = 1, EXROM = 1   ????
Normal   8kB cartridge at $8000       (ROML)     : GAME = 1, EXROM = 0
Normal  16kB cartridge at $8000/$a000 (ROML,ROMH): GAME = 0, EXROM = 0
Ultimax 16kB cartridge at $8000/$e000 (ROML,ROMH): GAME = 0, EXROM = 1
source: http://markus.brenner.de/cartridge/
*/

void C64_EXROM( uint8_t state ) {
	/* Enables C64_EXROM pin*/
	//PORTB = (PORTB & (1 << 7)) | ((state & 0x1) << 7) 
	//			\ Clear bit 7       \only get last bit, and shift to 7

	if( state == 1 ) {
      //PORTB |= 0b10000000;
		PORTB |=  (1 << 7);
	} else {
      //PORTB &=  0b01111111;
		PORTB &= ~(1 << 7);
	}
}

void C64_GAME( uint8_t state ) {
	/* Enables C64 GAME pin */
	//PORTB = (PORTB & (1 << 6)) | ((state & 0x1) << 6) 
	//			\ Clear bit 7       \only get last bit, and shift to 6
	if( state == 1 ) {
		//PORTB |= 0b01000000;
		PORTB |= (1 << 6);
	} else {
	  //PORTB &=  0b10111111;
		PORTB &= ~(1 << 6);
	}
}

void C64_NOCART()  { C64_GAME(1); C64_EXROM(1); }
void C64_8K()      { C64_GAME(1); C64_EXROM(0); }
void C64_16K()     { C64_GAME(0); C64_EXROM(0); }
void C64_ULTIMAX() { C64_GAME(0); C64_EXROM(1); }