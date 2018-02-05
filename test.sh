#!/bin/bash
[ $# -ne 1 ] && {
    echo "test.sh requires only 1 parameter (directory of the problem)"
    exit 1
}
OLD_PATH=`pwd`
TEST_PATH="$1"
[ -d "$TEST_PATH" ] || {
    echo "$TEST_PATH is not a directory"
    exit 2
}
[ -f "$TEST_PATH/main.cpp" ] || {
    echo "$TEST_PATH does not contains any main.cpp"
    exit 3
}
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
