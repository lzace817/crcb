#!/bin/bash

mkdir -p .build
pushd .build
pwd
if [[ ! -e  config.mk ]] then
    echo configuring
    ../configure.sh
    echo '*' > .gitignore
fi
make "$@"
popd