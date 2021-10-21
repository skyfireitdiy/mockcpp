#!/bin/bash
# build and install

# there is a $xunit_home/include/gtest/gtest.h
xunit_home=$1
install_dir=$2

build_dir=build

mkdir -p $build_dir
cd $build_dir
cmake -DCMAKE_INSTALL_PREFIX=$install_dir -DMOCKCPP_XUNIT=gtest -DMOCKCPP_XUNIT_HOME=${xunit_home} ..
make -j
make install
cd ..
rm -rf $build_dir
