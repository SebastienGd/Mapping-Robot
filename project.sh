#!/bin/bash

if [ "$1" = "debug" ] && [ "$2" = "app1" ]; then
    echo "Running the script in debug mode for app1."
    cd lib
    make
    cd ../app1
    make debug
elif [ "$1" = "debug" ] && [ "$2" = "app2" ]; then
    echo "Running the script in debug mode for app2."
    cd lib
    make
    cd ../app2
    make debug    
elif [ "$1" = "install" ] && [ "$2" = "app1" ]; then
    echo "Running the script in install mode for app1."
    cd lib
    make 
    cd ../app1
    make install
elif [ "$1" = "install" ] && [ "$2" = "app2" ]; then
    echo "Running the script in install mode for app2."
    cd lib
    make 
    cd ../app2
    make install
elif [ "$1" = "clean" ]; then
    echo "Cleaning the project."
    cd lib
    make clean
    cd ../app1
    make clean
    cd ../app2
    make clean
else 
    echo -e "Invalid command\n"
    exit 1
fi
