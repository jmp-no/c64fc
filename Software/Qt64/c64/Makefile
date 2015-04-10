all:
	acme -f plain -o move8000to0801.bin move8000to0801.asm
	acme -f plain -o copymover.bin copymover.asm

#	echo "unsigned char copymover[] = {" > copymover.h
#	 hexdump -C copymover.bin |cut -b 11-58|sed -e 's/  / /g'|sed -e 's/ /,0x/g'|sed -e 's/^/0x/g'|sed -e 's/$$/,/g' | sed -e 's/0x,//g' >> copymover.h
#	echo "};" >> copymover.h
