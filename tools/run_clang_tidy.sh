#!/bin/bash

find . -type d \( -path ./_build -o -path ./ext -o -path ./.git -o -path ./frontend \) -prune -o -type f -print \
    | grep -P '\.(c|h)(pp)?$' \
    | xargs -L1 -P$(nproc) clang-tidy \
    --quiet \
    -p="_build/" \
    --config-file=".clang-tidy" \
    --extra-arg-before=-DLINT \
    --extra-arg=-std=c++17