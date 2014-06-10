#!/usr/bin/env bash

# The goal is to remove the suppressed checks stepwise and fix the issues
# in the same commit. Use cppcheck --inline-suppr for false positives.
suppress_warn="--suppress=uninitMemberVar"
suppress_perf="--suppress=passedByValue"
suppress="$suppress_warn $suppress_perf"
enabled="--enable=warning --enable=performance --enable=information \
         --enable=portability --enable=missingInclude --enable=style"
# Exit code '1' is returned if arguments are not valid or if no input
# files are provided. Compare 'cppcheck --help'.
cppcheck -f -q --error-exitcode=2 $enabled $suppress "$@"
