SRC=$(wildcard *.c)
CC=emcc
OPT=-g -s WASM=1 -s SIDE_MODULE=1
OUT=../wasm/emcc.wasm

all:
	$(CC) $(OPT) $(SRC) -o $(OUT)
	rm -f *.map # No source maps needed
	rm -f ../wasm/*.map # No source maps needed