# wdis
wdis is a program that converts Web Assembly binaries to pseudo-C code.

# Building
To build, run `make binaryen && make`.
If the executable fails to locate `libbinaryen.so`, move / copy `src/binaryen/lib/libbinaryen.so` to `/usr/lib64`.