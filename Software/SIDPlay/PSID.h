#ifndef PSID_H
#define PSID_H 1

#include "PSID-header.h"

class PSID {
	public:
		PSID() {};
		virtual ~PSID() {};

		bool Validate( QString );
		unsigned char *Data();
		unsigned short LoadAddress();
		unsigned short InitAddress();
		unsigned short PlayAddress();
		int Version();
		char *Name();
	private:
		unsigned short SwapBytes( unsigned short );
		psid_t fileData;
};

#endif


