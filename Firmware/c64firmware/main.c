#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "usbdrv.h"

#include "c64.h"
#include "dpram.h"
#include "bootloader.h"
#include <string.h>    // Used for memcpy

#define C64FC_16K		0x16
#define C64FC_8K		0x08
#define C64FC_GETSIZE   0x20

#define C64FC_RESET		0xf0
#define C64FC_WRITEDATA	0xcc
#define C64FC_READDATA	0xcd
#define C64FC_SETADDR	0x64

#define C64FC_BOOTLOADER 0xFE



#define LED_ON	PORTD |=  (1 << 7)
#define LED_OFF PORTD &= ~(1 << 7)
/*#define LED_ON	PORTD |= 0b10000000
#define LED_OFF PORTD &= 0b01111111*/

typedef struct __attribute__((packed)){
   uint16_t address;
   char len;
   char data[128];  
} dataBlock;

uint16_t address = 0;

uint8_t dataINFunction  = 0;
uint8_t dataOUTFunction = 0;
/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

PROGMEM const char usbHidReportDescriptor[22] = {    /* USB report descriptor */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8) 0x08
    0x95, 0x80,                    //   REPORT_COUNT (128)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};
/* Since we define only one feature report, we don't use report-IDs (which
 * would be the first byte of the report). The entire report consists of 128
 * opaque data bytes.
 */

/* The following va1iables store the status of the current data transfer */
static uchar    bytesRemaining;
//static uint8_t enter_bootloader = 0;

/* ------------------------------------------------------------------------- */

/* usbFunctionRead() is called when the host requests a chunk of data from
 * the device. For more information see the documentation in usbdrv/usbdrv.h.
 */
uchar   usbFunctionRead(uchar *data, uchar len)
{
    if(len > bytesRemaining)
        len = bytesRemaining;
    bytesRemaining -= len;

    return len;
}

/* usbFunctionWrite() is called when the host sends a chunk of data to the
 * device. For more information see the documentation in usbdrv/usbdrv.h.
 */


/* Jeg må bare innse at denne ikke kjøres for hver "packet", men deles opp utenfor min kontroll. */

uchar   usbFunctionWrite(uchar *data, uchar len)
{
	uint8_t i=0;
	LED_ON;

	if(bytesRemaining == 0)
		return 1;               // end of transfer 

	if(len > bytesRemaining)
		len = bytesRemaining;

	switch( dataINFunction ) {
		case 1:
			for( i = 0; i<len; i++ )
				DPRAM_write( address+i, (unsigned char) data[i] );
			address += len;
			break;
		case 2:
			address = ((unsigned char)data[0] << 8)|(unsigned char)data[1];
			break;
		default:
			break;
	}

	bytesRemaining -= len;
	LED_OFF;
	return bytesRemaining == 0; // return 1 if this was the last chunk 
}

/* ------------------------------------------------------------------------- */

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t    *rq = (void *)data;

	uint8_t retval = USB_NO_MSG;

	LED_ON;

	if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
		if(rq->bRequest == USBRQ_HID_SET_REPORT){
			uint8_t command = rq->wValue.bytes[0];
			switch( command ) {
				case C64FC_8K:
					/* 0x08 8k mode
					 * Makes the C64FC enter 8k mode 
					 * Then reboots the C64 to load data from C64FC
					 */
					C64_EXROM(0);
					C64_GAME(1);
					C64_Reset();
					LED_OFF;
					retval = 1;
					bytesRemaining = 0;
					break;
				case C64FC_16K:
					/* 0x16 16k mode
					 * Makes the C64FC enter 16k mode 
					 * Then reboots the C64 to load data from C64FC
					 */
					C64_EXROM(0);
					C64_GAME(0);
					C64_Reset();
					LED_OFF;
					retval = 1;
					bytesRemaining = 0;
					break;
				case C64FC_WRITEDATA:
					/* 0xCC Send Data
					 * Data sent from pc to the C64FC
					 * Uses usbFunctionWrite to save recieved data to RAM
					 * Saves data to address set with C64FC_SETADDR
					 */
					bytesRemaining = rq->wLength.bytes[0];
					dataINFunction = 1;
					break;
				case C64FC_SETADDR:
					/* 0x64 Set Address
					 * Sets the address for the next read/write operation
					 * Uses usbFunctionWrite to get the address
					 */
					//bytesRemaining = rq->wLength.bytes[0];  // This did'nt work.. :( dont know if its because of S64FC or client software...)
					dataINFunction = 2;
					bytesRemaining = 2;

					break;
				case C64FC_RESET:
					/* 0xF0 Reset C64
					 * Resets the C64 
					 */
					//address = 0;
					C64_Reset();
					LED_OFF;
					retval = 1;
					bytesRemaining = 0;
					break;
				case C64FC_BOOTLOADER:
					/* 0xFE Enter Bootloader
					 * Puts the C64FC in bootloader mode.
					 * C64FC will be stuck in UsbASPloader until MCUCSR != 0 or avrdude sends a exit command.
					 * 
					 */
					 wdt_disable();
					MCUCSR = 0;
					bootloader_jump();		// This needs to be moved... bootloader_jump is creating a "Broken pipe on the host.."
										// Create a var and check for it in main:for(;;)  then execute bootloader_jump() before the next usb_poll.
					//enter_bootloader = 1;
					
					break;
			}
		} else if(rq->bRequest == USBRQ_HID_GET_REPORT){
			uint8_t command = rq->wValue.bytes[0];
			//uint8_t index0 = rq->wIndex.bytes[0];
			//uint8_t index1 = rq->wIndex.bytes[1];
			static uchar smallReturnBuffer[10];
			static uchar largeReturnBuffer[128];

			switch ( command ) {			
				case 0x01: ;
					/* 0x01 Return fubar to PC
					 * only for testing.. :)
					 *  --runar
					 */
					LED_OFF;
					retval = 6;
					static uchar pointer[5] = "fiske";
					usbMsgPtr = pointer;
					DPRAM_write(0x00, (uint8_t)'f');
					DPRAM_write(0x01, (uint8_t)'u');
					DPRAM_write(0x02, (uint8_t)'b');
					DPRAM_write(0x03, (uint8_t)'a');
					DPRAM_write(0x04, (uint8_t)'r');
					pointer[0] = DPRAM_read(0x00);
					pointer[1] = DPRAM_read(0x01);
					pointer[2] = DPRAM_read(0x02);
					pointer[3] = DPRAM_read(0x03);
					pointer[4] = DPRAM_read(0x04);
					pointer[4] = rq->wLength.bytes[0];
					LED_OFF;
					break;
				case C64FC_GETSIZE:	;
					/* 0x20 Get size of DPRAM
					 * Calculates the size of your DPRAM chip.
					 * supports 8k and 16k.
					 * Writes to 0x0 and compares with value at 0x2000.
					 * Se DPRAM_size in dpram.c for more info
					 */
					if (DPRAM_size() == 0x2000)
						smallReturnBuffer[0] =  8;
					else
						smallReturnBuffer[0] = 16;
					retval=10;				// Retval on GET request is number of bytes returned
					usbMsgPtr = smallReturnBuffer;
					LED_OFF;
					break;
				case C64FC_READDATA: ;
					/* 0xCD Read data from device
					 * Reads data from address set by C64FC_SETADDR
					 * 
					 */
					uint8_t i;
					for( i = 0; i<rq->wLength.bytes[0]; i++ ) {
						largeReturnBuffer[i] = DPRAM_read( address+i );
					}
					address  += rq->wLength.bytes[0];	// Address is incremented for next read...
					retval    = rq->wLength.bytes[0];	// Retval on GET request is number of bytes returned
					usbMsgPtr = largeReturnBuffer;
					LED_OFF;
					break;
			}

		}
	}
	return( retval );
}

/* ------------------------------------------------------------------------- */

int main(void) {
uchar   i;

	C64_init();
	DPRAM_init();
	DPRAM_clear(0x0,0x4000);

	wdt_enable(WDTO_1S);
	usbInit();
	usbDeviceDisconnect();

	DDRD |= (1 << 7);    // LED init
//	DDRD |= (0b10000000);    // LED init
	LED_ON;
	i = 0;
	while(--i){
		wdt_reset();
		_delay_ms(1);
	}
	LED_OFF;

	usbDeviceConnect();
	sei();

	DPRAM_init();

// 8k mode
	C64_EXROM(1);
	C64_GAME(1);
	C64_Reset();

	for(;;) {                /* main event loop */
		wdt_reset();
		usbPoll();

/*		if (enter_bootloader > 0)
			enter_bootloader++;
			if (enter_bootloader <= 1000) {
				wdt_disable();
				MCUCSR = 0;
				bootloader_jump();		// This needs to be moved... bootloader_jump is creating a "Broken pipe on the host.."
										// Create a var and check for it in main:for(;;)  then execute bootloader_jump() before the next usb_poll.
			}*/
	}
	return 0;
}



