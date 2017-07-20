ASM=wasm-as
OUTDIR=../wasm/

all:
	mkdir -p $(OUTDIR)
	mkdir -p ../disasm/
	$(ASM) addTwo.wast -o $(OUTDIR)addTwo.wasm
	$(ASM) funcs.wast -o $(OUTDIR)funcs.wasm