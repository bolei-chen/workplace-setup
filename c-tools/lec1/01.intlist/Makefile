CC	=	gcc
CFLAGS	=	-Wall
BUILD	=	testlist avgwordlen

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

testlist:	testlist.o intlist.o
avgwordlen:	avgwordlen.o intlist.o
intlist.o:	intlist.c intlist.h
testlist.o:	testlist.c intlist.h
avgwordlen.o:	avgwordlen.c intlist.h defns.h
