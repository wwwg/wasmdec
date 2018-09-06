SRC=$(wildcard src/*.cc src/**/*.cc !(src/wasm_api.cc))
EMCC_SRC=$(wildcard src/*.cc src/**/*.cc !(src/wasmdec.cc))
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
	make wasmBinaryen
	EMCC_DEBUG=1 em++ $(EMCC_SRC) external/binaryen/lib/libbinaryen.so \
		-std=c++14 -Iexternal/binaryen/src -Iexternal/cxxopts/include -Wall -g3 \
		-Wall -o wasmdec.js \
		-s EXPORTED_FUNCTIONS='["_wasmdec_decompile"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
	mkdir -p emcc_out
	mv wasmdec.js wasmdec.wasm emcc_out/

clean:
	rm -f *.o wasmdec
	rm -f src/*.o
	rm -f src/**/*.o

# To build binaryen
binaryen:
	cd external/binaryen && cmake . && make
# To build binaryen as a webassembly library
wasmBinaryen:
	cd external/binaryen && emconfigure cmake . && emmake make

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
