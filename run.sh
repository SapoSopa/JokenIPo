#!/bin/sh

if [ ! -d build ]
then
    mkdir build    
fi

cd build
cmake ..
make

mv jokenipo ../
cd ..

chmod +x jokenipo
./jokenipo

# Path: CMakeLists.txt