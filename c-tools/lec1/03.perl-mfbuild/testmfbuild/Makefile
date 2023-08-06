# Standard Declarations for mfbuild

CC	=	gcc
CFLAGS	=	-g -Wall
BUILD	=	testlist

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core a.out .nfs*

testlist.o:	testlist.c intlist.h

intlist.o:	intlist.c intlist.h

OBJS	=	 testlist.o intlist.o

testlist:		$(OBJS)
	$(CC) $(OBJS) -o testlist $(LDFLAGS)
