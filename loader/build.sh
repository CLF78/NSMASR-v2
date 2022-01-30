#!/bin/bash

CC="../cw/mwcceppc.exe"
CPPFILES='kamekLoader nsmbw'
CFLAGS='-i . -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0'

for i in $CPPFILES; do
    echo Compiling $i.cpp...
    wine $CC $CFLAGS -c -o $i.o $i.cpp
    if [ $? != 0 ]; then
        exit 1
    fi
done

if [ $? == 0 ]; then
    echo 'Linking...'
    Kamek kamekLoader.o nsmbw.o -externals=addresses.txt -static=0x800046E4 -output-code=loader.bin -output-riiv=loader.xml
fi
