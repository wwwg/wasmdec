SRC=$(wildcard src/*.cc src/convert/*.cc)
OBJS=$(SRC:.cc=.o)
OUT=wdis
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
	rm -f *.o wdis
	rm -f src/*.o

# To build binaryen
binaryen:
	cd src/binaryen; cmake .; make