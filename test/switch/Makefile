SRC=$(wildcard *.c)
CC=emcc
OPT=-g -s WASM=1 -s SIDE_MODULE=1
OUT=../wasm/switch.wasm

default:
	$(CC) $(OPT) $(SRC) -o $(OUT)
	# No source maps needed
	rm -f *.map
	rm -f ../wasm/*.map