#include <QWidget>
#include <QFile>
#include "PSID.h"

bool PSID::Validate( QString filename ) {
	QFile file( filename );
	if( ! file.open( QIODevice::ReadOnly ))
		return( false );

	file.read( (char *) &this->fileData, sizeof( psid_t ) );
	file.close();

	if( memcmp( (char *) &this->fileData, "PSID", 4 ) == 0 ) {
		return( true );
	} else if( memcmp( (char *) &this->fileData, "RSID", 4 ) == 0 ) {
		return( true );
	}

	return( false );
}

unsigned char *PSID::Data() {
	return( this->fileData.data );
}

unsigned short PSID::SwapBytes( unsigned short value ) {
#ifdef __ORDER_BIG_ENDIAN__
	return( ((value>>8)&0xff)|((value&0xff)<<8) );
#else
	return( value );
#endif
}

unsigned short PSID::LoadAddress() {
	if( this->fileData.load_addr == 0 ) {
		BYTE lo = this->fileData.data[0];
		BYTE hi = this->fileData.data[1];
#ifdef __ORDER_BIG_ENDIAN__
		return( (hi<<8)|lo );
#else
		return( (lo<<8)|hi  );
#endif
	} else {
		return( SwapBytes( this->fileData.load_addr ));
	}
}

unsigned short PSID::InitAddress() {
	return( SwapBytes( this->fileData.init_addr ) );
}

unsigned short PSID::PlayAddress() {
	return( SwapBytes( this->fileData.play_addr ) );
}

char *PSID::Name() {
	return( (char *) this->fileData.name );
}

int PSID::Version() {
	printf( "# songs: %d\n", SwapBytes( this->fileData.songs ) );
	printf( "start songs: %d\n", SwapBytes( this->fileData.start_song ) );
	return( (int) SwapBytes( this->fileData.version ) );
}

/*
00000000  50 53 49 44 00 02 00 7c  00 00 10 00 10 03 00 01  |PSID...|........|
00000010  00 01 00 00 00 00 57 65  6c 63 6f 6d 65 20 4d 61  |......Welcome Ma|
00000020  76 65 72 69 63 6b 20 28  70 61 72 74 20 32 29 00  |verick (part 2).|
00000030  00 00 00 00 00 00 4a 6f  20 47 75 6e 6e 61 72 73  |......Jo Gunnars|
00000040  68 61 75 67 20 28 43 6f  64 65 78 29 00 00 00 00  |haug (Codex)....|
00000050  00 00 00 00 00 00 31 39  38 38 20 4e 65 74 77 6f  |......1988 Netwo|
00000060  72 6b 2f 48 6f 61 78 65  72 73 00 00 00 00 00 00  |rk/Hoaxers......|
00000070  00 00 00 00 00 00 00 00  00 00 00 00 00 10 4c 08  |..............L.|
*/
