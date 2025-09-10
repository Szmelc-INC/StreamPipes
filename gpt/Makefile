.RECIPEPREFIX := >
CC?=gcc
CFLAGS+=-Wall -Wextra $(shell pkg-config fuse3 --cflags)
LDFLAGS+=$(shell pkg-config fuse3 --libs)

all: gpt

gpt: gpt.c
>$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
>rm -f gpt

.PHONY: all clean
