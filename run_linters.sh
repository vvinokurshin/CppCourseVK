#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN clang-tidy"
check_log "clang-tidy homework5/*.cpp homework5/src/*.hpp -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus* -warnings-as-errors=* -extra-arg=-std=c++17 -- -Ihomework5/src" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=hpp homework5/src/*.hpp homework5/tests/*.cpp" "Can't open for reading"

print_header "SUCCESS"
