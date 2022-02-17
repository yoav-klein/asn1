#!/bin/bash

set -e

autoreconf -iv
./configure
make
make install
