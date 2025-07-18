#!/bin/bash

# out of tree
# mkdir -p .build
# pushd .build
# pwd
# if [[ ! -e  config.mk ]] then
#     echo configuring
#     ../configure.sh
#     echo '*' > .gitignore
# fi
# make "$@"
# popd

# in tree

make "$@"

make test