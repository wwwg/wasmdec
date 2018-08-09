#!/bin/bash

# hacky test script for wasmdec
# make sure you have wasmdec installed before running (run "make install" in the root dir)
WASMDEC=wasmdec

do_test () {
	if $(WASMDEC) -i $1 -o test.c -e -d; then
		# test succeeded!
	else
		echo "test $1 failed horribly"
		exit 1
	fi
}

do_test("wasm/emcc.wast");