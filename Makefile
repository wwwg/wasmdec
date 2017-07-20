SRC=$(wildcard src/*.cc)
OUT=./out
CC=clang++
OPTS=-g -std=c++14 -Isrc/binaryen/src -Lsrc/binaryen/lib -lbinaryen

default:
	$(CC) $(OPTS) $(SRC) -o $(OUT)
binaryen:
	cd src/binaryen; cmake .; make