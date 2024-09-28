#1/bin/bash

if ! ./compile.sh; then
    exit 1
fi

echo "Program starting"

OUTPUT=`./salary.out << EOF
S 40000 8
S
S 10
S 40000
S 40000 0
S 40000 100
S 40000 10
q
EOF`

echo "Program finished"

echo "$OUTPUT" | grep -v "Enter employee salary:" > filtered.txt

STATUS=0

if diff -u filtered.txt expected_staff_output.txt > /dev/null; then
    echo "Test Passed"
else
    STATUS=1
    echo "Test Failed"
    echo "Expected output:"
    cat expected_staff_output.txt
    echo "Actual output:"
    cat filtered.txt
fi

rm filtered.tx

exit $STATUS
