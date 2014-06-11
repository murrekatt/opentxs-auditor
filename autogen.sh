#!/bin/sh

set -e

[ ! -d .gitmodules ] || {
    echo "=== Updating submodules =================================="
    git submodule init
    git submodule update
    echo "=== Building submodules =================================="
    cd submodules && cd jsoncpp && scons platform=linux-gcc && cd ../jsonrpc-cpp && scons && cd ../websocketpp && scons && cd ../..
}

echo "=== Configuring and Building ============================="
srcdir="$(dirname $0)"
cd "$srcdir"
pwd
autoreconf -vif -Wall
