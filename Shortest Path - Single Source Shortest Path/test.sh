#!/bin/bash
OLD_PATH=`pwd`
TEST_PATH=`echo "$0" | sed "s/\/test.sh//g"`
cd "$TEST_PATH"
g++ main.cpp && {
    echo "Compilation OK"
    for TEST_FILE in *.data
    do
        echo "Testing $TEST_FILE..."
        RESULT_FILE=`echo "$TEST_FILE" | sed "s/\.data/\.result/g"`
        [ -f "$RESULT_FILE" ] || {
            echo "  $RESULT_FILE doesn't exists. Please create it"
            continue
        }
        RESULT=`./a.out < $TEST_FILE` || {
            echo "  Execution fails"
            continue
        }
        diff "$RESULT_FILE" <(echo "$RESULT") >> /dev/null
        [ $? -eq 0 ] && {
            echo "  [OK]"
        } || {
            echo "  [KO] Expecting:"
            cat "$RESULT_FILE" | sed "s/^/        > /g"
            echo "       Found: "
            echo "$RESULT" | sed "s/^/        > /g"
        }
    done
}
rm -f a.out
cd "$OLD_PATH"
