#!/bin/bash

# Move to the project root directory
pushd "$(dirname "$0")/../" > /dev/null
Vendor/premake/binaries/premake5 gmake2
popd > /dev/null
