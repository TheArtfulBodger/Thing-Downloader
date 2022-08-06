#!/bin/bash

find . -type d \( -path ./_build -o -path ./ext -o -path ./.git \) -prune -o -type f -print \
    | grep -P '\.(c|h)(pp)?$' \
    | xargs clang-format -i