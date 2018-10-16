#!/bin/bash
for wast in ../external/testsuite/*.wast; do
    out_file=${wast}.decompiled.c
    echo "test-spec.sh : decompiling '$wast' to '$out_file'"
    ../wasmdec $wast -d -e -o $out_file
    returned=$?
    if [ $returned -ne 0 ]; then
        echo "test-spec.sh : wasmdec failed on '$wast', abort"
        exit 1
    fi
done