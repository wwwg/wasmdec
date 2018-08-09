#!/bin/bash

# hacky test script for wasmdec
# make sure you have wasmdec installed before running (run "make install" in the root dir)
WASMDEC=wasmdec

do_test () {
	WASMDEC -i $1 -o test.c -e -d
	if [ $? -eq 0 ]; then
		# test succeeded!
		echo "TEST SUCCESS: test $1 passed"
	else
		# test fail
		echo "TEST FAIL: test $1 failed horribly"
		exit 1
	fi
}

do_test "wasm/emcc.wast"