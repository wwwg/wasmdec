SRC=$(wildcard src/*.cc)
LIB=$(wildcard src/binaryen/lib/*.a)
OUT=./out
CC=clang++
OPTS=-std=c++14 -Isrc/binaryen/src

all:
	$(CC) $(OPTS) $(SRC) $(LIB) -o $(OUT)
binaryen:
	cd src/binaryen; cmake .; make