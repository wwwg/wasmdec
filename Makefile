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
	# make wasmBinaryen
	mkdir -p emcc_out
	EMCC_DEBUG=1 em++ external/binaryen/lib/libbinaryen.so $(EMCC_SRC) \
		-std=c++14 -Iexternal/binaryen/src -Iexternal/cxxopts/include -Wall -O3 \
		-Wall -o emcc_out/wasmdec.js \
		-s EXPORTED_FUNCTIONS='["_wasmdec_create_decompiler", "_wasmdec_decompile", "_wasmdec_get_decompiled_code", "_wasmdec_destroy_decompiler"]' \
		-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "addOnPostRun"]' -s ASSERTIONS=1 -s SAFE_HEAP=1
	cp emcc_out/wasmdec.wasm wasmdec.js/
	echo "(function(){" > wasmdec.js/wasmdec.wasm.js
	cat emcc_out/wasmdec.js >> wasmdec.js/wasmdec.wasm.js
	sed -i -e 's/rrides={};/rrides={};window\.Wasmdec\.Module=Module;/g' wasmdec.js/wasmdec.wasm.js
	echo "})();" >> wasmdec.js/wasmdec.wasm.js

clean:
	rm -f *.o wasmdec
	rm -f src/*.o
	rm -f src/**/*.o

# To build binaryen
binaryen:
	cd external/binaryen && cmake . && make
# To build binaryen as a webassembly library
wasmBinaryen:
	cd external/binaryen && EMCC_DEBUG=1 em++ src/*.cpp src/**/*.cpp -I/home/p/wasmdec/external/binaryen/src -std=c++11 -o lib/libinaryen.bc

# To install binaryen
installBinaryen:
	make installBinaryen`(uname -s)`

installBinaryenLinux:
	if [ -d "/usr/lib64" ]; then cp external/binaryen/lib/libbinaryen.so /usr/lib64/; else cp external/binaryen/lib/libbinaryen.so /usr/lib/; fi

installBinaryenDarwin:
	cp external/binaryen/lib/libbinaryen.dylib /usr/local/lib/

# To install wasmdec
install:
	cp ./wasmdec /usr/bin

# To build and install everything
all:
	make binaryen
	make installBinaryen
	make default
	make install
