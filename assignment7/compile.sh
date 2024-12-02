#!/bin/bash

if gcc -g -lm -fno-stack-protector -rdynamic -o rpg_gen.out rpg_gen.c; then
    echo "Compilation successful"
else
    echo "Compilation failed"
    exit 1
fi

