#!/bin/bash

# hacky test script for wasmdec
# make sure you have wasmdec installed before running (run "make install" in the root dir)

do_test () {
	wasmdec -i $1 -o test.c -e -d
	if [ $? -eq 0 ]; then
		# test succeeded!
		echo "TEST SUCCESS: test $1 passed"
	else
		# test fail
		echo "TEST FAIL: test $1 failed horribly"
		exit 1
	fi
	rm -f test.c
}

# perform test for each binary

do_test "wasm/emcc.wast"
do_test "wasm/emcc.wasm"
do_test "wasm/funcs.wasm"
do_test "wasm/switch.wasm"
do_test "wasm/switch.wast"
do_test "wast-tests/addTwo.wast"
do_test "wast-tests/funcs.wast"