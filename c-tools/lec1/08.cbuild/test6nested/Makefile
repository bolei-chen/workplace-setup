# Hand tweaked Makefile to work for nested includes
# mfbuild-perl generated the original version of this
# Makefile, but it didn't include person.o or name.o in OBJS,
# or person.h or name.h in the various dependencies.  That's
# because person.h was only included indirectly via plist.h,
# and name.h was only included even more indirectly via person.h

CC	=	gcc
CFLAGS	=	-g -Wall
BUILD	=	useplist
OBJS	=	useplist.o plist.o person.o name.o

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) $(OBJS) core a.out .nfs*

useplist:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o useplist $(LDLIBS)

useplist.o:	useplist.c plist.h person.h name.h
plist.o:	plist.c plist.h person.h name.h
person.o:	person.c person.h name.h
name.o:		name.c name.h
