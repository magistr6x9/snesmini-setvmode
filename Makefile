CC = arm-linux-gnueabihf-gcc-7
STRIP = arm-linux-gnueabihf-strip

CFLAGS = -Wall -O -g

src = $(wildcard *.c)
obj = $(src:.c=.o)

setvmode : $(obj)
	$(CC) -o $@ $^
	$(STRIP) $@

.PHONY: clean
clean :
	rm -f $(obj) setvmode
