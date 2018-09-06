SRC=$(wildcard src/*.cc src/**/*.cc !(src/wasm_api.cc))
OBJS=$(SRC:.cc=.o)
OUT=wasmdec
CC=g++
CCOPTS=-std=c++14 -Iexternal/binaryen/src -Iexternal/cxxopts/include -c -Wall -g
RELEASE_CCOPTS=-std=c++14 -Iexternal/binaryen/src -c -Wall -O3
LDOPTS=-Lexternal/binaryen/lib -lbinaryen -lpthread

default: $(SRC) $(OUT)

$(OUT): $(OBJS) 
	@echo -n "Link "
	@echo $@
	$(CC) $(OBJS) $(LDOPTS) -o $@

.cc.o:
	@echo -n "Build source "
	@echo $<
	$(CC) $(CCOPTS) $< -o $@
wasm:
	EMCC_DEBUG=1 em++ src/*.cc src/**/*.cc external/binaryen/lib/libbinaryen.so -Wall -o wasmdec.js

clean:
	rm -f *.o wasmdec
	rm -f src/*.o
	rm -f src/**/*.o

# To build binaryen
binaryen:
	cd external/binaryen && cmake . && make

# To install binaryen
installBinaryen:
	if [ -d "/usr/lib64" ]; then cp external/binaryen/lib/libbinaryen.so /usr/lib64/; else cp external/binaryen/lib/libbinaryen.so /usr/lib/; fi

# To install wasmdec
install:
	cp ./wasmdec /usr/bin

# To build and install everything
all:
	make binaryen
	make installBinaryen
	make default
	make install
