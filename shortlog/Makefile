.RECIPEPREFIX := >
CC?=gcc
CFLAGS+=-Wall -Wextra $(shell pkg-config fuse3 --cflags)
LDFLAGS+=$(shell pkg-config fuse3 --libs)

all: shortlog

shortlog: shortlog.c
>$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
>rm -f shortlog

.PHONY: all clean
