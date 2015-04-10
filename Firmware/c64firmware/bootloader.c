#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "bootloader.h"


#define BOOTLOADER_SIZE     2048
#define FLASH_SIZE          (FLASHEND + 1L)
#define BOOTLOADER_START    (FLASH_SIZE - BOOTLOADER_SIZE)
//#define BOOTLOADER_START    3800

void bootloader_jump(void) {

/* 
   This bootloader jumper is ported from the tmk_keyboard project 
   Handydandy modded by runborg... dono if this thing works.. :P

*/
    cli();

    // This makes custom USBasploader come up.
    MCUCSR = 0;    // MCUCSR on atmega16... other MCUSR

    // initialize ports
    PORTB = 0; 
    PORTC = 0; 
    PORTD = 0;
    DDRB  = 0; 
    DDRC  = 0; 
    DDRD  = 0;

    // disable interrupts
    //EIMSK  = 0; // not on atmega16
    EECR   = 0; 
    SPCR   = 0;
    ACSR   = 0; 
    SPMCR = 0; 
    WDTCR = 0; 
    //PCICR = 0;
    TIMSK = 0; 
    //TIMSK1 = 0; 
    //TIMSK2 = 0;
    ADCSRA = 0; 
    TWCR = 0; 
    UCSRB = 0;

    // This is compled into 'icall', address should be in word unit, not byte.
    //((void (*)(void))(BOOTLOADER_START/2))();
    asm volatile ("  jmp 0x3800  ");
}
