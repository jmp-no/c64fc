#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "hiddata.h"
#include "../firmware/usbconfig.h"

/* ------------------------------------------------------------------------- */
usbDevice_t *dev;

static char *usbErrorMessage(int errCode)
{
static char buffer[80];

    switch(errCode){
        case USBOPEN_ERR_ACCESS:      return "Access to device denied";
        case USBOPEN_ERR_NOTFOUND:    return "The specified device was not found";
        case USBOPEN_ERR_IO:          return "Communication error with device";
        default:
            sprintf(buffer, "Unknown USB error %d", errCode);
            return buffer;
    }
    return NULL;    /* not reached */
}

static usbDevice_t  *openDevice(void) {
usbDevice_t     *dev = NULL;
unsigned char   rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
char            vendorName[] = {USB_CFG_VENDOR_NAME, 0}, productName[] = {USB_CFG_DEVICE_NAME, 0};
int             vid = rawVid[0] + 256 * rawVid[1];
int             pid = rawPid[0] + 256 * rawPid[1];
int             err;

    if((err = usbhidOpenDevice(&dev, vid, vendorName, pid, productName, 0)) != 0){
        fprintf(stderr, "error finding %s: %s\n", productName, usbErrorMessage(err));
        return NULL;
    }
    return dev;
}

/* ------------------------------------------------------------------------- */

static void usage(char *myName)
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  %s read\n", myName);
    fprintf(stderr, "  %s write <listofbytes>\n", myName);
}

void PrepareTransfer() {
	unsigned char buffer[129];
	int err;
        memset(buffer, 0, sizeof(buffer));
	buffer[0] = 0x10;
	if ((err = usbhidSetReport(dev, buffer, 1)) != 0)
		fprintf(stderr, "error writing data: %s\n", usbErrorMessage(err));
}


void ResetC64() {
	unsigned char        buffer[129];    /* room for dummy report ID */
int         err;
        memset(buffer, 0, sizeof(buffer));
	buffer[0] = 0xf0;	// CMDRESET
	//if ((err = usbhidSetReport(dev, buffer, sizeof(buffer))) != 0)
	if ((err = usbhidSetReport(dev, buffer, 1)) != 0)
		fprintf(stderr, "error writing data: %s\n", usbErrorMessage(err));
	printf( "C64 reset.\n" );
}

void SendFile( char *filename ) {
int         err;
	unsigned char        buffer[129];    /* room for dummy report ID */
        memset(buffer, 0, sizeof(buffer));


	FILE *fp = fopen( filename, "rb" );
	if( !fp ) {
		printf( "Fuck dat shit\n" );
		return;
	}

	fseek( fp, 0L, SEEK_END );
	int size = ftell(fp);
	rewind( fp );

	unsigned char tmp[128];
	fread( tmp, 80, 1, fp );

	if( strncmp( (char *) tmp, "C64 CARTRIDGE   ", 16 ) == 0 ) {
		printf( "VICE header found, skipping it...\n" );
		size -= 80;
	} else {
		printf( "Looks like a plain CRT file\n" );
		rewind( fp );
	}

	PrepareTransfer();

	unsigned short address = 0;
	int chunk_no=0;

	while( size > 0 ) {
		int chunk_size = (size>=128)?128:size;
		(void) fread( buffer+1, chunk_size, 1, fp );


		buffer[0] = (unsigned char) 0xcc;	// CMDPROG

		if ((err = usbhidSetReport(dev, buffer, sizeof(buffer) )) != 0)
			fprintf(stderr, "error writing data: %s\n", usbErrorMessage(err));

		size -= chunk_size;
		address += chunk_size;

	}

	fclose( fp );

	ResetC64();

}

int main(int argc, char **argv)
{

    if(argc < 2){
        usage(argv[0]);
        exit(1);
    }
    if((dev = openDevice()) == NULL)
        exit(1);
    if(strcasecmp(argv[1], "reset") == 0){
	ResetC64();
    }else if(strcasecmp(argv[1], "write") == 0){
	SendFile( argv[2] );
    }else{
        usage(argv[0]);
        exit(1);
    }
    usbhidCloseDevice(dev);
    return 0;
}

/* ------------------------------------------------------------------------- */
