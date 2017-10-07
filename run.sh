#!/bin/bash
make
./zappy_server -p $1 -f 10&
cd ./Zappy_Unity
./Zappy.x86_64&
cd ..
sleep 20
./zappy_graphic -p $1
