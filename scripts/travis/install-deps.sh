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

sudo echo 'deb http://llvm.org/apt/precise/ '\
    'llvm-toolchain-precise-3.4 main' >>/etc/apt/sources.list
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get -qq update
sudo apt-get -qq install g++-4.8
sudo apt-get install cmake
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -
sudo apt-get -qq install clang-format-3.4
install_cppcheck
