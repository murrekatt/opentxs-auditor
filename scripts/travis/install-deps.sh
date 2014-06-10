#!/usr/bin/env bash

# Install cppcheck on Ubuntu from source since we need a recent version.
# Will not be needed once travis is updated to Ubuntu 14.04.
install_cppcheck()
{
    git clone https://github.com/danmar/cppcheck.git
    cd cppcheck
    git checkout 1.65
    make SRCDIR=build CFGDIR=/usr/share/cppcheck HAVE_RULES=no -j2
    sudo make install
    # On travis cppcheck ignores CFGDIR. Instead, it looks in $PWD. Compare
    # strace output.
    sudo install -m644 ./cfg/* ../
}

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo add-apt-repository -y ppa:apokluda/boost1.53
sudo apt-get -qq update
sudo apt-get -qq install g++-4.8
sudo apt-get install libboost1.53-all-dev scons
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
install_cppcheck
