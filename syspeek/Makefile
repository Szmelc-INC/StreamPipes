.RECIPEPREFIX := >
CC?=gcc
CFLAGS+=-Wall -Wextra $(shell pkg-config fuse3 --cflags)
LDFLAGS+=$(shell pkg-config fuse3 --libs)

all: syspeek

syspeek: syspeek.c
>$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
>rm -f syspeek

.PHONY: all clean
