#!/bin/bash

LEX_SOURCE="lex.l"
LEX_OUTPUT="lex.yy.c"
OUTPUT="trans.out"

CC="gcc"

while getopts "rtc" opt; do
    case $opt in
        r)
            flex -o $LEX_OUTPUT $LEX_SOURCE
            $CC $LEX_OUTPUT -o $OUTPUT
            ;;
        t)
            TEST_FILES=("tests/test1.in" "tests/test2.in" "tests/test3.in" "tests/test4.in" "tests/test5.in")
            EXPECT_FILES=("tests/expect1.out" "tests/expect2.out" "tests/expect3.out" "tests/expect4.out" "tests/expect5.out")

            SCORE=0

            # Run tests
            for (( i=0; i<${#TEST_FILES[@]}; i++ )); do
                TEST_FILE=${TEST_FILES[$i]}
                EXPECT_FILE=${EXPECT_FILES[$i]}
                OUTPUT_FILE="${TEST_FILE%.*}.out"
                ./$OUTPUT < $TEST_FILE > $OUTPUT_FILE
                if diff -q $OUTPUT_FILE $EXPECT_FILE > /dev/null; then
                    SCORE=$(($SCORE+20))
                    echo -e "\033[0;32mTest $((i+1)): PASSED\033[0m"
                else
                    echo -e "\033[0;31mTest $((i+1)): FAILED\033[0m"
                fi
            done

            echo "Final score: $SCORE/100"
            ;;
        c)
            rm -f $OUTPUT $LEX_OUTPUT
            rm -f tests/test*.out
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done

if [ $OPTIND -eq 1 ]; then
    echo "Usage: $0 [-rtc]"
    echo "  -r: Compile the Lex source file"
    echo "  -t: Run tests"
    echo "  -c: Clean up generated files"
fi
