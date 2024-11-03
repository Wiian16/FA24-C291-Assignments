#!/bin/bash

if gcc -g -lm -fno-stack-protector -rdynamic -o string_index.out string_index.c; then
    echo "Compilation successful"
else
    echo "Compilation failed"
    exit 1
fi

