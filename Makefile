SRC=$(wildcard src/*.cc src/*.cpp src/convert/*.cc src/convert/*.cpp)
OUT=./wdis
CC=clang++
OPTS=-g -std=c++14 -Isrc/binaryen/src -Lsrc/binaryen/lib -lbinaryen

default:
	$(CC) $(OPTS) $(SRC) -o $(OUT)
binaryen:
	cd src/binaryen; cmake .; make