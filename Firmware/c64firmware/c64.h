#ifndef C64_H
#define C64_H 1

void C64_init();
void C64_Reset();
void C64_EXROM( uint8_t );
void C64_GAME( uint8_t );

void C64_NOCART();
void C64_8K();     
void C64_16K();    
void C64_ULTIMAX();

#define C64FC_DATA 0xcc
#define C64FC_SETADDR 0x64

#endif
