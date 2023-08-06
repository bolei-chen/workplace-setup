#TOOLDIR	=	$(HOME)/c-tools
INSTDIR	=	$(TOOLDIR)
BINFILE	=	$(INSTDIR)/bin/$(ARCH)/mfbuild
MANFILE	=	$(INSTDIR)/man/man1/mfbuild.1
DEFS	=	$(INSTDIR)/lib/mfbuilddefs
CC	=	gcc
CFLAGS	=	-g -Wall -DLIBRDEFSFILENAME=\"$(DEFS)\"
BUILD	=	mfbuild
OBJS	=	mfbuild.o queue.o

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core a.out .nfs*

install:	$(BUILD)
	install -c -m 755 mfbuild $(BINFILE)
	install -c -m 644 mfbuild.man $(MANFILE)
	install -c -m 644 mfbuilddefs $(DEFS)

uninstall:
	rm -f $(BINFILE)
	rm -f $(MANFILE)
	rm -f $(DEFS)

mfbuild.o:	mfbuild.c queue.h
queue.o:	queue.c queue.h

mfbuild:		$(OBJS)
	$(CC) $(OBJS) -o mfbuild $(LDFLAGS)
