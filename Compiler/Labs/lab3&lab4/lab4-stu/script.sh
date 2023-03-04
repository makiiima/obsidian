#!/bin/bash

LEX_SOURCE="calc.l"
LEX_OUTPUT="lex.yy.c"
YACC_SOURCE="calc.y"
YACC_OUTPUT="calc.tab.c"
YACC_OUTPUT_HEADER="calc.tab.h"
OUTPUT="calc"

CC="gcc"
CFLAGS="-lm"  # -lm is for math library

while getopts "rtc" opt; do
    case $opt in
        r)
            flex -o $LEX_OUTPUT $LEX_SOURCE
            bison -d -o $YACC_OUTPUT $YACC_SOURCE
            $CC $LEX_OUTPUT $YACC_OUTPUT $CFLAGS  -o $OUTPUT
            ;;
        t)
            TEST_FILE="tests/test.in"
            EXPECT_FILE="tests/expect.out"
            OUTPUT_FILE="tests/test.out"
            SCORE=0

            # Run tests
            ./$OUTPUT < $TEST_FILE > $OUTPUT_FILE
            i=0
            while IFS= read -r line1 && IFS= read -r line2 <&3; do
                i=$(($i+1))
                if [ "$line1" = "$line2" ]; then
                    SCORE=$(($SCORE+20))
                    echo -e "\033[0;32mTest $i: PASSED\033[0m"
                else
                    echo -e "\033[0;31mTest $i: FAILED\033[0m"
                fi
            done < $OUTPUT_FILE 3< $EXPECT_FILE

            echo "Final score: $SCORE/"$((20*$i))
            ;;
        c)
            rm -f $LEX_OUTPUT $YACC_OUTPUT $YACC_OUTPUT_HEADER
            rm -f $OUTPUT
            rm -f tests/test.out
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done

if [ $OPTIND -eq 1 ]; then
    echo "Usage: $0 [-rtc]"
    echo "  -r: Compile the source file"
    echo "  -t: Run tests"
    echo "  -c: Clean up generated files"
fi
