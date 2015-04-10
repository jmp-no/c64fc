#set this to 8 or 16 based on size of the EEPROM used
C64FC_EEPROM_SIZE = 16

DEVICE = atmega16
AVRDUDE = avrdude -c usbasp  -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -Iusbdrv -I. -mmcu=$(DEVICE) -DF_CPU=12000000 -DC64FC_EEPROM_SIZE=$(C64FC_EEPROM_SIZE) #-DDEBUG_LEVEL=2
OBJECTS = usbdrv/usbdrv.o usbdrv/usbdrvasm.o usbdrv/oddebug.o main.o c64.o dpram.o bootloader.o

all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i
	echo "send 0xFF 0xFF 0xFF 0xFF" | $(AVRDUDE) -c usbasp -p atmega16 -t

fuse:
	$(AVRDUDE) -U lfuse:w:0xef:m -U hfuse:w:0xd9:m


clean:
	rm -f main.hex main.lst main.obj main.cof main.list main.map main.eep.hex main.bin *.o usbdrv/*.o main.s usbdrv/oddebug.s usbdrv/usbdrv.s

main.bin:	$(OBJECTS)
	$(COMPILE) -o main.bin $(OBJECTS)

main.hex:	main.bin
	rm -f main.hex main.eep.hex
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex

disasm:	main.bin
	avr-objdump -d main.bin

cpp:
	$(COMPILE) -E main.c

