SRC=$(wildcard src/*.cc src/convert/*.cc)
OBJS=$(SRC:.cc=.o)
OUT=wasmdec
CC=clang++
CCOPTS=-g -std=c++14 -Isrc/binaryen/src -c -Wall
LDOPTS=-Lsrc/binaryen/lib -lbinaryen

all: $(SRC) $(OUT)

$(OUT): $(OBJS) 
	@echo -n "Link "
	@echo $@
	$(CC) $(LDOPTS) $(OBJS) -o $@

.cc.o:
	@echo -n "Build source "
	@echo $<
	$(CC) $(CCOPTS) $< -o $@

clean:
	rm -f *.o wasmdec
	rm -f src/*.o

# To build binaryen
binaryen:
	cd src/binaryen && cmake . && make
# To install binaryen
installBinaryen:
	if [ -d "/usr/lib64" ]; then cp src/binaryen/lib/libbinaryen.so /usr/lib64/; else cp src/binaryen/lib/libbinaryen.so /usr/lib/; fi