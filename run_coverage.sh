#!/usr/bin/env bash

failed=0

for file in homework5/build/coverage_*.txt
do
    echo $file
    python3 check_coverage.py "$file"
    rc=$?
  
    if [ $rc -ne 0 ]
    then
        (( failed = failed + 1 ))
    fi
done

if [ $failed -eq 0 ]
then 
    exit 0
else
    exit 1
fi
