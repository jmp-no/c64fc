# c64fc
All software related to the C64FC (Commodore 64 Flash Cart)

-> Firmware:

Holds the source code to build and flash the firmware.

USBaspLoader  USB boot loader for the AVR.
c64firmware   firmware sourcecode.

-> Hardware:

Hardware schematics of the C64FC card in brd/sch format.	
	
- > Software:

Qt64          QT GUI frontend to handle upload/download of c64 images.
SIDPlay 	    QT GUI frontend to handle SID playing.
cmd64         Command tools to upload/download/reset/set bootloader.	
libc64fc 	    libc64fc library. Needed for all above as dep.

C64 images needs to be placed under:

cmd64: ./Software/cmd64/ROMs
qt64: ./Software/Qt64/ROMs

C64 SID needs to be placed under:

c64fc/Software/SIDPlay/C64Music
