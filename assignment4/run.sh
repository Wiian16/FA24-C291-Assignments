#!/usr/bin/bash

if ./compile.sh; then
    printf "\n"
else
    exit 1
fi

./payroll.out