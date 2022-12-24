#! /bin/bash

find . -name "CMakeLists.txt" | grep -v "ext" | xargs -L1 cmake-format -i