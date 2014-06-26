#!/usr/bin/env bash
set -e

os="$1"
if [[ -z "$1" ]] ; then
    os="linux"
fi

dir="opentxs-auditor"
mkdir -p ${dir}/bin

# collect files
cp -rf build/bin/opentxs-auditor ${dir}/bin/

# create package
version=`cat VERSION`
compiler=${CXX}
package="opentxs-auditor-${version}-${os}-${compiler}.tar.gz"

echo "Creating package ${package}"
tar -vpczf ${package} ${dir}

mkdir s3
cp ${package} s3/
cp VERSION s3/
