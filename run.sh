#!/bin/sh

if [ -e jokenipo ]
then
    rm jokenipo
fi

if [ ! -d build ]
then
    mkdir build    
fi

cd build
cmake ..
make

if [ -e jokenipo ]
then
    mv jokenipo ../
fi

cd ..

if [ -e jokenipo ]
then
    chmod +x jokenipo
    ./jokenipo

    rm jokenipo
fi

# Path: CMakeLists.txt