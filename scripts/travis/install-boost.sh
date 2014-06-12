#!/usr/bin/env bash

wget --no-verbose --output-document=boost-trunk.tar.bz2 http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.bz2/download
export BOOST_ROOT="$TRAVIS_BUILD_DIR/../boost-trunk"
mkdir -p $BOOST_ROOT
tar jxf boost-trunk.tar.bz2 --strip-components=1 -C $BOOST_ROOT

(cd $BOOST_ROOT; ./bootstrap.sh --with-libraries=date_time,filesystem,system,regex,thread,random,test)
(cd $BOOST_ROOT; sudo ./b2 threading=multi --prefix=/usr/local -d0 install)

sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/local.conf'

sudo ldconfig
