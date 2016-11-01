COMPILER=gcc
CFLAGS=-ggdb -O2 -Wall -Wextra -Isrc -DNDEBUG -Xlinker --verbose -c $(OPTFLAGS)
LDFLAGS=$(OPTLIBS) -lcurl -ljansson

SRCDIR=src
SOURCES=$(wildcard src/**/*.c src/*.c)
TARGET=build/libhggrab.a
LIBDIR=build
BINDIR=bin
OBJECTS=$(wildcard %.c, %.o)
OBJ_FILES = $(patsubst src/%.c,build/%.o,$(SOURCES))


all: build
#$(COMPILER) $(CFLAGS) $(SRCDIR)/basic_curl.c $(LDFLAGS) -o $(LIBDIR)/basic_curl.o
	$(COMPILER) $(CFLAGS) $(SOURCES) $(LDFLAGS)
	mv *.o $(LIBDIR)/

#$(OBJECTS):
#	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)

build:
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p headers

clean:
	@rm -rf build
	@rm -rf bin
	@rm -rf headers

binary: build all
	gcc -o $(BINDIR)/keyneyloggins main.c $(OBJ_FILES) $(LDFLAGS)



#gcc main.c build/$(OBJECTS) $(LDFLAGS)
#gcc main.c build/basic_curl.o -lcurl
#gcc -o bin/fetchy main.c $(OBJECTS) $(LDFLAGS)
