#!/bin/sh

set -e

echo "=== Updating submodules =================================="
git submodule update --init --recursive
git submodule update --recursive
echo "=== Building submodules =================================="
cd deps/jsonrpc-cpp/jsoncpp
scons
cd ..
scons
cd ../websocketpp
scons
cd ../..

echo "=== Configuring and Building ============================="
srcdir="$(dirname $0)"
cd "$srcdir"
pwd
autoreconf -vif -Wall
