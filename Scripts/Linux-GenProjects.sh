#!/bin/bash

# Move to the project root directory
pushd "$(dirname "$0")/../" > /dev/null
cmake -S . -B build -G "Ninja"
popd > /dev/null
