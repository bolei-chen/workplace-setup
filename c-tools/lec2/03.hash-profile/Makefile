CC	=	gcc
CFLAGS	=	-Wall #-pg
LDLIBS	=	#-pg
PROGS	=	testhash iterate

all:	$(PROGS)

clean:
	rm -f $(PROGS) *.o gmon.out

profile:	./iterate
	./iterate 10000
	gprof ./iterate gmon.out > profile.orig

testhash:	testhash.o hash.o
iterate:	iterate.o hash.o
testhash.o:	hash.h
hash.o:		hash.h
iterate.o:	hash.h
