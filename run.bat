@echo off
if not exist build mkdir build

cd build
cmake ..
cmake --build .
move jokenipo.exe ..
cd ..

:: To execute the original executable
start jokenipo.exe