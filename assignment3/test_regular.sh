#1/bin/bash

if ! ./compile.sh; then
    exit 1
fi

echo "Program starting"

OUTPUT=`./salary.out << EOF
R 80000 0
R 0 9
R 80000 4.5
q
EOF`

echo "Program finished"

echo "$OUTPUT" | grep "Faculty" > filtered.txt

STATUS=0

if diff -u filtered.txt expected_regular_output.txt > /dev/null; then
    echo "Test Passed"
else
    STATUS=1
    echo "Test Failed"
    echo "Expected output:"
    cat expected_regular_output.txt
    echo "Actual output:"
    cat filtered.txt
fi

rm filtered.txt

exit $STATUS
