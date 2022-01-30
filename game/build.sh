#!/bin/bash

AS="../cw/mwasmeppc.exe"
ASMFLAGS='-I- -i ../include'
ASMFILES=''

CC="../cw/mwcceppc.exe"
CFLAGS='-I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0'
CPPFILES='1-nsmbw-osreport'

OBJECTS=''

for i in $CPPFILES; do
    echo "Compiling $i.cpp..."
    wine $CC $CFLAGS -c -o $i.o $i.cpp
    if [ $? != 0 ]; then
        exit 1
    else
        OBJECTS="$OBJECTS $i.o"
    fi
done

for i in $ASMFILES; do
    echo "Assembling $i.S..."
    wine $AS $ASMFLAGS -c -o $i.o $i.S
    if [ $? != 0 ]; then
        exit 1
    else
        OBJECTS="$OBJECTS $i.o"
    fi
done

if [ $? == 0 ]; then
    echo 'Linking...'
    Kamek $OBJECTS -dynamic -externals=externals-nsmbw.txt -versions=versions-nsmbw.txt -output-kamek=code\$KV\$.bin
fi
