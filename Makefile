all : setvmode

setvmode : setvmode.c
	arm-linux-gnueabihf-gcc -Wall -O setvmode.c -o setvmode -g
	arm-linux-gnueabihf-strip setvmode

clean :
	rm -f setvmode
