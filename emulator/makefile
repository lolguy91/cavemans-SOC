CC=clang
CFLAGS=-Isrc
LDFLAGS=
source_files := $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) $(wildcard src/*/*/*/*.c) $(wildcard src/*/*/*/*/*.c) $(wildcard src/*/*/*/*/*/*.c)
header_files := $(wildcard src/*.h) $(wildcardsrc/ */*.h) $(wildcard src/*/*/*.h) $(wildcard src/*/*/*/*.h) $(wildcard src/*/*/*/*/*.h) $(wildcard src/*/*/*/*/*/*.h)

object_files := $(source_files:.c=.o)

%.o: %.c
	$(CC) -Werror -c -g -o $@ $< $(CFLAGS)
	

build: $(object_files)
	$(CC) -o bin/emu $(LDFLAGS) $(object_files)

run : build
	./bin/emu rom.bin