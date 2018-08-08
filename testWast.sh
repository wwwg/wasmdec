# for testing parsing of *.wast files
make
./wasmdec -i test/wasm/emcc.wast -o out.c -e -d