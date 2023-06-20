#!/bin/bash
gcc -Wall -Wextra -Werror -pendantic -c -fPIC *.c
gcc shared -o liball.so *.o
export LD_LIBRARY_PATH.:$LD_LIBRARY_PATH