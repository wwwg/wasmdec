SRC=$(wildcard src/*.cc src/*.cpp src/convert/*.cc src/convert/*.cpp)
OBJS=$(SRC:.cc=.o)
OUT=wdis
CC=clang++
CCOPTS=-g -std=c++14 -Isrc/binaryen/src -c -Wall
LDOPTS=-Lsrc/binaryen/lib -lbinaryen

all: $(SRC) $(OUT)
$(OUT): $(OBJS) 
	$(CC) $(LDOPTS) $(OBJS) -o $@
.cc.o:
	 $(CC) $(CCOPTS) $< -o $@

# To build binaryen
binaryen:
	cd src/binaryen; cmake .; make