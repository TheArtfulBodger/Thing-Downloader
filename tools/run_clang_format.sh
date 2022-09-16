#!/bin/bash

find . -type d \( -path ./_build -o -path ./ext -o -path ./.git -o -path ./frontend \) -prune -o -type f -print \
    | grep -P '\.(c|h)(pp)?$' \
    | xargs clang-format -i