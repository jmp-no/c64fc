CC=gcc
CFLAGS=-Wall -O2
OBJS=main.o
TARGET=cmd64
LIBS=../libc64fc/libc64fc.a `libusb-config --libs`

.c.o:	$(CC) -c $*.c

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

