#TOOLDIR	=	$(HOME)/c-tools
INSTDIR	=	$(TOOLDIR)
BINDIR	=	$(INSTDIR)/bin
LIBDIR	=	$(INSTDIR)/lib
CBMANFILE	=	$(INSTDIR)/man/man1/cb.1
CRMANFILE	=	$(INSTDIR)/man/man1/cr.1
DEFS	=	$(INSTDIR)/lib/cbuilddefs

install:	cb
	install -c -m 0755 cb $(BINDIR)/cb
	install -c -m 0755 cr $(BINDIR)/cr
	install -c -m 0755 graphpairs $(BINDIR)/graphpairs
	install -c -m 0644 Rules.pm FindIncludes.pm $(LIBDIR)
	install -c -m 0644 cb.man $(CBMANFILE)
	install -c -m 0644 cr.man $(CRMANFILE)
	install -c -m 0644 cbuilddefs $(DEFS)

clean:
	( cd test1; cb clean)
	( cd test2; cb clean)
	( cd test3; cb clean)
	( cd test4; cb clean)
	( cd test5; cb clean)
	( cd test6nested; cb clean)
	( cd test7flattened; cb clean)
	( cd test8sillynested; cb clean)
	( cd test9clean-wo-cbuild; cb clean)

uninstall:
	rm -f $(BINDIR)/cb
	rm -f $(BINDIR)/graphpairs
	rm -f $(BINDIR)/Rules.pm
	rm -f $(BINDIR)/FindIncludes.pm
	rm -f $(MANFILE)
	rm -f $(DEFS)

