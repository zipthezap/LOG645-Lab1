#!/bin/bash

make clean
find . -maxdepth 1 -type d \( ! -name . \) \
     -exec bash -c "cd '{}' && make clean" \;
