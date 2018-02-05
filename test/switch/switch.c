/*
    Simple test for switch expressions in wasm
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    volatile int a = 42;
    switch (a) {
        case 1:
            printf("one\n");
            break;
        case 2:
            printf("two\n");
            break;
        case 42:
            printf("forty two!\n");
            break;
        default:
            printf("default\n");
            break;
    }
    return 0;
}