SRC=$(wildcard src/*.cc)
LIB=$(wildcard src/binaryen/lib/*.a)
OUT=./out
CC=clang++
OPTS=-g -std=c++14 -Isrc/binaryen/src -Lsrc/binaryen/lib -lbinaryen

all:
	$(CC) $(OPTS) $(SRC) -o $(OUT)
run:
	make all
	./$(OUT)
binaryen:
	cd src/binaryen; cmake .; make