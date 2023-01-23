#!/usr/bin/env bash

. $(dirname "$0")/run.sh

print_header "RUN clang-format"
check_log "clang-format DoIt/main.cpp --dry-run --Werror" "Error (?:reading|while processing)"

print_header "RUN clang-tidy"
check_log "clang-tidy DoIt/main.cpp -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus* -warnings-as-errors=* -- -DDEBUG -I DoIt/database/ -std=c++17" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint DoIt/main.cpp" "Can't open for reading"

print_header "RUN cppcheck"
check_log "cppcheck DoIt/main.cpp -q -j4 --enable=performance,portability,warning --error-exitcode=1" "\(information\)"

print_header "RUN infer"
cd DoIt && mkdir -p build && cd build
check_log "infer run -- clang -c ../main.cpp -I ../database/ -std=c++17" "Error"
cd ../..

print_header "SUCCESS"
