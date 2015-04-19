#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <usb.h>
#include "hiddata.h"
#include "../usbconfig.h"
#include "c64fc.h"


usbDevice_t *dev = NULL;
unsigned char buffer[129];

int OpenDevice() {
	unsigned char vendor_id[2] = { USB_CFG_VENDOR_ID };
	unsigned char product_id[2] = { USB_CFG_DEVICE_ID };
	char vendorName[] = { USB_CFG_VENDOR_NAME, 0 };
	char productName[] = { USB_CFG_DEVICE_NAME, 0 };
	int vid = vendor_id[0] + 256*vendor_id[1];
	int pid = product_id[0] + 256*product_id[1];
	int status;
	status = usbhidOpenDevice( &dev, vid, "jmp.no", pid, "C64FC-16", 0 );
	if (status == 0) return status;
	status = usbhidOpenDevice( &dev, vid, "jmp.no", pid, "C64FC-08", 0 );
	if (status == 0) return status;
	status = usbhidOpenDevice( &dev, vid, "jmp.no", pid, "C64FC", 0 );
	return( status );
}

void CloseDevice() {
	if( dev ) usbhidCloseDevice( dev );
	dev = NULL;
}

int Reset() {
	memset( buffer, 0, sizeof( buffer ));
	buffer[0] = C64FC_RESET;
	return( usbhidSetReport( dev, (char *) buffer, 1 ));
}

void SetAddress( unsigned short addr ) {
	int err=0;
	buffer[0] = C64FC_SETADDR;
	buffer[1] = (addr>>8)&0xff;
	buffer[2] = (addr&0xff);
	err = usbhidSetReport( dev, (char *) buffer, 129);
//	printf( "SetAddr=$%04x sent, response=%d\n", addr, err );
}


void Set8KMode() {
	int err = 0;
	buffer[0] = C64FC_8K;
	err = usbhidSetReport( dev, (char *) buffer, 1);
	printf( "SetCartMode=%d, res=%d", 8, err );
	Reset();
}

void Set16KMode() {
	int err = 0;
	buffer[0] = C64FC_16K;
	err = usbhidSetReport( dev, (char *) buffer, 1);
	printf( "SetCartMode=%d, res=%d", 16, err );
	Reset();
}

void SetMode(uint8_t mode) {
	/* Sets the GAME / EXROM pins on the C64
	 * Change is done without rebooting C64
	 * Parameter is the enum C64_MODE
	 */
	int err = 0;
	buffer[0] = C64FC_SETMODE;
	buffer[1] = mode;
	err = usbhidSetReport( dev, (char *) buffer, 1);
	printf( "SetCartMode=%d, res=%d", mode, err );
	Reset();
}
// Forslag til rewrite av WriteData...    
int WriteData( unsigned short address, unsigned char *data, int size ) {
	int err = 0;
	int chunk_no=0;
	int offset=0;

	if( !dev ) OpenDevice();
	SetAddress( address );

	while( size > 0 ) {

		int chunk_size = (size>=128)?128:size;
		memcpy( buffer+1, data+offset, chunk_size );
		buffer[0] = C64FC_DATA;
		printf( "Sending chunk %d (%d bytes) to $%04x..\n", chunk_no, chunk_size, address );
		//err = usbhidSetReport( dev, (char *) buffer, 129);
		err = usbhidSetReport( dev, (char *) buffer, chunk_size+1);  // <-- len is set to chunk_size+1.. wee need to remember the first reportid char... 
//		printf( "Sent\n" );
		if( err != 0 ) return( err );
		size -= chunk_size;
		address += chunk_size;
		offset += chunk_size;
		chunk_no++;
	}
	return( 0 );

}

int getFubar(char *buff) {
	char buffer[6];
	int len = 0x80;
	int err = 0;
    if((err = usbhidGetReport(dev, 0x01, (char *)buffer, &len)) != 0){
        //fprintf(stderr, "error reading data: %s\n", usbErrorMessage(err));
        printf("usb error of some kind");
        return 0;
    }else{
            memcpy(buff, buffer+1,len-1);
    }
    //printf("d: %s", buffer);
    return len-1;
}

int getData(uint16_t address, char *data, uint8_t size) {
	/*

		NB! size needs to be 128 or less.... usb cant return any lager bulks by default....

	*/
	char buffer[129];		// Max result size - 1
	int len = size+1;
	int err = 0;
	SetAddress( address );

    if((err = usbhidGetReport(dev, C64FC_READDATA, (char *)buffer, &len)) != 0){
        //fprintf(stderr, "error reading data: %s\n", usbErrorMessage(err));
        printf("usb error of some kind");
        return 0;
    }else{
            memcpy(data, buffer+1,len-1);
    }
    //printf("d: %s", buffer);
    return len-1;
}

unsigned int GetRamSize() {
	char buffer[11];
	int len = 10;
	int err = 0;
    if((err = usbhidGetReport(dev, C64FC_GETSIZE, (char *)buffer, &len)) != 0){
        //fprintf(stderr, "error reading data: %s\n", usbErrorMessage(err));
        printf("usb error of some kind");
        return 0x0;
    }
    //printf("d: %x", buffer[1]);
    return (unsigned int)buffer[1];

}


void EnterBootloader() {
	int err = 0;
	buffer[0] = C64FC_BOOTLOADER;
	err = usbhidSetReport( dev, (char *) buffer, 1);
	printf( "EnterBootloader=%d, res=%d", 16, err );
}

