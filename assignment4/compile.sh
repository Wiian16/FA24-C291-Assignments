#!/bin/bash

if gcc -g -lm -fno-stack-protector -rdynamic -o payroll.out payroll.c; then
    echo "Compilation successful"
else
    echo "Compilation failed"
    exit 1
fi
