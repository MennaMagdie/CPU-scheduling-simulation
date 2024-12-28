#!/bin/bash

TEST_DIR="testcases"
PASSED=0
FAILED=0

echo "Running tests..."

for input_file in "$TEST_DIR"/*-input.txt; do

    base_name=$(basename "$input_file" -input.txt)
    expected_output_file="$TEST_DIR/${base_name}-output.txt"

    diff_output=$(cat "$input_file" | ./lab6 | diff - "$expected_output_file")
    
    if [ $? -eq 0 ]; then
        echo "Test $base_name: PASSED"
        PASSED=$((PASSED + 1))
    else
        echo
        echo "Test $base_name: FAILED"
        echo "Differences:"
        echo "$diff_output"
        FAILED=$((FAILED + 1))
        echo
    fi
done

echo
echo "Test Summary:"
echo "-------------"
echo "Passed: $PASSED"
echo "Failed: $FAILED"
