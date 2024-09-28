#!/bin/bash

if ! ./compile.sh; then
    exit 1
fi

echo

STATUS=0

for FILENAME in $(ls test_*.sh)
do
    if [[ "$FILENAME" == "test_all.sh" ]]; then
        continue
    fi

    echo "Running $FILENAME"

    if ! bash "$FILENAME" >> /dev/null; then
        echo "$FILENAME failed"
        STATUS=1
        continue
    fi

    echo "$FILENAME passed"
    echo
done

if [[ $STATUS -eq 0 ]]; then
    echo "All tests passed"
else
    echo "Some test(s) failed"
fi

exit $STATUS

