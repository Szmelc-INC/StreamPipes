.RECIPEPREFIX := >
SUBDIRS = asciibuffer shortlog syspeek gpt
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

all:
>for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

install: all
>install -d $(DESTDIR)$(BINDIR)
>for dir in $(SUBDIRS); do install -m755 $$dir/$$dir $(DESTDIR)$(BINDIR)/$$dir; done

clean:
>for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

.PHONY: all install clean
