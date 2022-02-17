#!/bin/bash

if ! [ -d build ]; then
    mkdir build
fi
cd build

cp ../* .
asn1c -no-gen-example rectangle.asn1
make -f encode.mk
make -f decode.mk

cp encode ../
cp decode ../
cd ..