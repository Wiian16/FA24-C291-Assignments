#/bin/bash

echo "10/2024 1100 2 2200 15 3300 25 3400 12 6700 5" | ./run.sh >> output.txt

LINE=`cat output.txt | grep "MONTHLY STATEMENT"`
EXPECTED="MONTHLY STATEMENT (OCTOBER 2024)"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "MONTHLY SALES"`
EXPECTED="MONTHLY SALES: \$16700.00"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "MONTHLY PROFIT"`
EXPECTED="MONTHLY PROFIT: \$7515.00"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "Empl A:"`
EXPECTED="Empl A:    137.50       751.50      133.35       44.45       66.68     644.53"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "Empl B"`
EXPECTED="Empl B:    275.00       1127.25     210.34       70.11       105.17    1016.63"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "Empl C"`
EXPECTED="Empl C:    412.50       1503.00     287.33       95.78       143.66    1388.74"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "Empl D"`
EXPECTED="Empl D:    425.00       1127.25     232.84       77.61       116.42    1125.38"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "Empl E"`
EXPECTED="Empl E:    837.50       751.50      238.35       79.45       119.18    1152.03"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "Total"`
EXPECTED="Total      2087.50      5260.50     1102.21      367.40      551.11    5327.31"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

LINE=`cat output.txt | grep "Net Profit"`
EXPECTED="Net Profit (Profit - Bonus): 2254.50"

if [ "$LINE" != "$EXPECTED" ]; then
    echo "Test Failed"
    echo "Expected: "
    echo "  $EXPECTED"
    echo "Actual:"
    echo "  $LINE"
    rm output.txt
    exit 1
fi

echo "Test Passed";

rm output.txt
