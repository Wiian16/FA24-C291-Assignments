#!/bin/bash

if gcc -g -rdynamic -o salary.out salary.c; then
    echo "Compilation successful"
else
    echo "Compilation failed"
    exit 1
fi

