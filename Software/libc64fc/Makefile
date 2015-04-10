CC=gcc
CFLAGS=-Wall -O2
OBJS=hiddata.o main.o
TARGET=libc64fc.a
AR=ar -r
DELETE=rm -f

.c.o:	$(CC) -c $*.c

$(TARGET):	$(OBJS)
	$(AR) $(TARGET) $(OBJS)

all:	$(TARGET)

clean:	
	$(DELETE) $(OBJS) $(TARGET)

