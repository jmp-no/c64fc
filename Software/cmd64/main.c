#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "../libc64fc/externs.h"


static void hexdump(uint16_t startaddr, char *buffer, int len)
{
int     i;
int     newline = 1;

    for(i = 0; i < len; i++){
        if(i != 0){
            if(i % 16 == 0){
                printf("\n");
                newline = 1;
            }else{
            	if(i % 8 == 0) printf("   ");
                else printf(" ");
            }
        }
        if (newline) {
        	printf("%08x   ", startaddr);
        	newline = 0;
        }
        printf("%02x", buffer[i] & 0xff);
        startaddr++;
    }
    if(i != 0)
        printf("\n");
}


int main(int argc, char **argv) {
	if( argc != 2 && argc != 3 ) {
		printf( "Usage: c64 <command> [filename]\n" );
		printf( "Commands:\n" );
		printf( "     upload <filename>      - Uploads CRT image to C64FC\n" );
		printf( "     download <filename>    - Downloads image from C64FC (not implemented)\n");
		printf( "     reset                  - Resets the C64\n" );
		printf( "     clear                  - Clears the entire C64FC, writes 0x0 to every address\n");
		printf( "     hexdump                - Prints a hexdump of the entire cart\n");
		printf( "     bootloader             - Enters bootloader mode on cart\n");
		printf( "     ramsize                - Prints your EEPROM size\n");
		printf( "     chardump <fps>         - Takes stdout from pipe and dump it on screen\n");
		return( 1 );
	}

	if( OpenDevice() ) {
		printf( "C64FC not found\n" );
		return( 1 );
	}





	if( (strcasecmp( argv[1], "reset" ) == 0) && (argc == 2) ) {
		/* 
		 * Issues a Reset of the C64 
		 */
		Reset();


	} else 	if( (strcasecmp( argv[1], "bootloader" ) == 0) && (argc == 2) ) {
		/*
		 * Makes the cart enter bootloader mode, this mode needs a power cycle of the cart to exit from
		 */
		EnterBootloader();	


	} else if( (strcasecmp( argv[1], "upload" ) == 0) && (argc == 3) ) {
		/*
		 * Uploads data to the cart
		 */
		int skip = 0;
		FILE *fp = fopen( argv[2], "rb" );
		if( !fp ) {
			printf( "Can't open input file for reading\n" );
			return( 1 );
		}
		fseek( fp, 0L, SEEK_END );
		int len = ftell( fp );
		fseek( fp, 0L, SEEK_SET );
		unsigned char *array = malloc( len );
		fread( array, len, 1, fp );
		fclose( fp );
		if( array[0] == 'C' && array[1] == '6' && array[2] == '4' ) {
			skip = 80;
		}
		printf( "Sending data (%d bytes)..\n", len-skip );
		WriteData( 0, array+skip, len-skip );
		if( len-skip >= 8192 ) {
			Set16KMode();
		} else {
			Set8KMode();
		}
		printf( "Issuing reset..\n" );
		Reset();


	} else 	if( (strcasecmp( argv[1], "clear" ) == 0) && (argc == 2) ) {
		/*
		 * Clears the content of the entire C64FC
		 */



	} else if ((strcasecmp( argv[1], "fubar" ) == 0) && (argc == 2)) {
		/* 
		 * Runars test function
		 * Actually.. does nothing more than return fubar in hex to the user... :)
		 */
		char buff[10];
		int len = getFubar(buff);
		printf("getFubar: %s(%d)\n", buff, len);
		hexdump(0, buff, 10);

	} else if ((strcasecmp( argv[1], "hexdump" ) == 0) && (argc == 2)) {
		/* 
		 * Make a hexdump of the current register in the cart
		 */
		char buff[128];
		printf("Hexdump of cart:\n");
		int i;
		for (i = 0; i < 0x3FFF; i += 128) {
			memset(buff, 0x0, 128);
			int len = getData(i, buff,128);
			//printf("getData: %d(%d)\n", i, len);
			hexdump(i, buff, 128);
			//printf("\n");
		}

	} else if ((strcasecmp( argv[1], "ramsize" ) == 0) && (argc == 2)) {
		/* 
		 * Check if your cart is 8k or 16k..
		 * .. Thats it.. :) 
		 */
		unsigned int size = GetRamSize();
		printf("Your RAM is a %dkb chip\n", size);


	} else {
		/* 
		 * Command not understood... yea yea... 
		 */
		printf( "WHAT? WHAT\n" );
		return( 1 );
	}


	CloseDevice();
	return( 0 );

}



