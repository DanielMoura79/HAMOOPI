#!/bin/bash

INC=`allegro-config --static --cppflags`
LIB=`allegro-config --static --libs`
g++ -c HAMOOPI.cpp -o HAMOOPI.o $INC $LIB
g++ HAMOOPI.o -o HAMOOPI.exe $INC $LIB