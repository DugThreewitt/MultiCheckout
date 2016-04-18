# Makefile for Sieve program
# Dug Threewitt - dstgh6
# CS2750 - Mon / Wed

CC = gcc
CFLAGS = -g 
TARGET = checkout
OBJS = checkout.o func.o queue.o multiC.o types.h proto.h queue.h multiC.h

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	/bin/rm -f *.o *~
