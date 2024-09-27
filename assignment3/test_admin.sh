#!/bin/bash

if ! ./compile.sh; then
    exit 1
fi

echo "Program starting"

OUTPUT=`./salary.out << EOF
A 100000 10
A
A ten
A 100000
A 120000
A 60000
q
EOF`

echo "Program finished"

echo "$OUTPUT" | grep -v "Enter employee salary:" > filtered.txt

STATUS=0

if diff -u filtered.txt expected_admin_output.txt > /dev/null; then
    echo "Test Passed"
else
    STATUS=1
    echo "Test Failed"
    echo "Expected output:"
    cat expected_admin_output.txt
    echo "Actual output:"
    cat filtered.txt
fi

rm filtered.txt

exit $STATUS
