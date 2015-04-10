extern int OpenDevice();
extern void CloseDevice();
extern void Set8KMode();
extern void Set16KMode();
extern int Reset();
extern int WriteData( unsigned short, unsigned char *, int );
extern int SetAddress( unsigned short );
extern void EnterBootloader();
extern int getFubar(char *);
extern int getData(uint16_t, char *, uint8_t);

extern unsigned int GetRamSize();