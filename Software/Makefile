all: 
	make -C libc64fc
	make -C cmd64
	cd Qt64 && qmake
	make -C Qt64
	cd SIDPlay && qmake
	make -C SIDPlay

clean:
	make -C libc64fc clean
	make -C cmd64 clean
	-make -C Qt64 clean
	rm -f Qt64/Makefile 
	-make -C SIDPlay clean
	rm -f SIDPlay/Makefile
