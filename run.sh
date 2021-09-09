#! /bin/bash
cmd=$1
if [ $cmd == 'build' ]
then
    cd build/
    cmake .. 
    cmake --build .
    cp os_programming os.dbg
    strip --only-keep-debug os.dbg
    strip os_programming
elif [ $cmd == "run" ]
then
    ./build/os_programming
fi