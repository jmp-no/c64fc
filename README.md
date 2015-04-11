# c64fc
All software related to the C64FC (Commodore 64 Flash Cart)

Firmware:

Holds the source code to build and flash the firmware.

USBaspLoader	USB boot loader for the AVR.
c64firmware	firmware sourcecode.

Hardware:

Contains Hardware schematics of the C64FC card in brd/sch format.	
	
Software:

Qt64	-	QT GUI frontend to handle upload/download of c64 images.
SIDPlay -	QT GUI frontend to handle SID playing.
cmd64	-	Command tools to upload/download/reset/set bootloader.	
libc64fc-	libc64fc library. Needed for all above as dep.

C64 images/sids needs to be placed under ROMs/C64Music.
