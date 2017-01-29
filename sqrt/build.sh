#!/bin/sh

x=0
for var in "$@"
do
  if [ $var == "-x" ]; then
    x=1
  fi
done

echo Cleaning...
rm -rf CMakeFiles CMakeCache.txt Makefile sqrt *.cmake

if [ $x -eq 1 ]; then
  echo Building Xcode project ...
  rm -rf build-xcode/*
  cd build-xcode
  cmake .. -G Xcode  -DCMAKE_BUILD_TYPE=Debug  -DCMAKE_OSX_SYSROOT="$(xcode-select --print-path)/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk" -DCMAKE_OSX_ARCHITECTURES=x86_64
cd ..
fi

echo Generating Makefile with cmake ...
cmake ./ 

echo Building ...
make
