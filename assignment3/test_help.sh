#!/bin/bash

if ./compile.sh; then
    printf "\n"
else
    exit 1
fi

echo "Program Started"

OUTPUT=`./salary.out << EOF
?
q
EOF`

echo "Program Finished"

echo "$OUTPUT" | grep -v "Enter employee salary:" > filtered.txt

STATUS=0

if diff -u filtered.txt expected_help_output.txt > /dev/null; then
    echo "Test passed"
else
    STATUS=1
    echo "Test failed"
    echo "Expected output:"
    cat expected_help_output.txt
    echo "Actual output:"
    cat filtered.txt
fi

rm filtered.txt

exit $STATUS
