#!/bin/sh

set -e

[ ! -d .gitmodules ] || {
    echo "autogen.sh: updating git submodules"
    git submodule init
    git submodule update
}

# build submodules
cd submodules && cd jsoncpp && scons platform=linux-gcc && cd ../jsonrpc-cpp && scons && cd ../websocketpp && scons && cd ../..

srcdir="$(dirname $0)"
cd "$srcdir"
autoreconf -vif -Wall
