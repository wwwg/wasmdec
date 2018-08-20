SRC=$(wildcard src/*.cc src/**/*.cc)
OBJS=$(SRC:.cc=.o)
OUT=wasmdec
CC=g++
CCOPTS=-std=c++14 -Iexternal/binaryen/src -c -Wall -g
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

clean:
	rm -f *.o wasmdec
	rm -f src/*.o
	rm -f src/**/*.o

# To build binaryen
binaryen:
	cd src/binaryen && cmake . && make

# To install binaryen
installBinaryen:
	if [ -d "/usr/lib64" ]; then cp src/binaryen/lib/libbinaryen.so /usr/lib64/; else cp src/binaryen/lib/libbinaryen.so /usr/lib/; fi

# To install wasmdec
install:
	cp ./wasmdec /usr/bin

# To build and install everything
all:
	make binaryen
	make installBinaryen
	make default
	make install
