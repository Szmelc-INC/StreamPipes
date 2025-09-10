.RECIPEPREFIX := >
CC?=gcc
CFLAGS+=-Wall -Wextra $(shell pkg-config fuse3 --cflags)
LDFLAGS+=$(shell pkg-config fuse3 --libs)

all: asciibuffer

asciibuffer: asciibuffer.c
>$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
>rm -f asciibuffer

.PHONY: all clean
