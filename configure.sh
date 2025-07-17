#!/bin/bash
# very basic out of tree build

srcdir=$(dirname $0)
echo "srcdir := ${srcdir}" > config.mk
ln -s "${srcdir}/Makefile" Makefile