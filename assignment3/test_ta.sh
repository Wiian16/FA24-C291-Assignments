#!/bin/bash

if ! ./compile.sh; then
    exit 1
fi

echo "Program starting"

OUTPUT=`./salary.out << EOF
T
T 10
T 100 100 100
T 2 50
T 1 30
T 3 150
T 1 0
T 2 80
q
EOF`

echo "Program finished"

echo "$OUTPUT" | grep -v "Enter employee salary:" > filtered.txt

STATUS=0

if diff -u filtered.txt expected_ta_output.txt > /dev/null; then
    echo "Test Passed"
else
    STATUS=1
    echo "Test Failed"
    echo "Expected output:"
    cat expected_ta_output.txt
    echo "Actual output:"
    cat filtered.txt
fi

rm filtered.txt

exit $STATUS
