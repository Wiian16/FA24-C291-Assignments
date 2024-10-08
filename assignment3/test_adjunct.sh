#!/bin/bash

if ! ./compile.sh; then
    exit 1
fi

echo "Program starting"

OUTPUT=`./salary.out << EOF
J 0
J 1
J 3
J 4
J 6
J 10 10
J 9
J 10
q
EOF`

echo "Program finished"

echo "$OUTPUT" | grep "Adjunct" > filtered.txt

STATUS=0

if diff -u filtered.txt expected_adjunct_output.txt > /dev/null; then
    echo "Test Passed"
else
    STATUS=1
    echo "Test Failed"
    echo "Expected output:"
    cat expected_adjunct_output.txt
    echo "Actual output:"
    cat filtered.txt
fi

rm filtered.txt

exit $STATUS
