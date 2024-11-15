#!/bin/bash

if gcc -g -lm -fno-stack-protector -rdynamic -o my_wc.out my_wc.c; then
    echo "Compilation successful"
else
    echo "Compilation failed"
    exit 1
fi

