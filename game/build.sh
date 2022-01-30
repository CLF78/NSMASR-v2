#!/bin/bash

if [ -d 'build' ]; then
	rm -rf 'build'
fi
mkdir -p 'build'

AS="../cw/mwasmeppc.exe"
ASMFLAGS='-I- -i ../include'
ASMFILES=''

CC="../cw/mwcceppc.exe"
CFLAGS='-I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0'
CPPFILES='1-nsmbw-osreport'

MYREGION='P1'

OBJECTS=''

for i in $CPPFILES; do
    echo "Compiling $i.cpp..."
    wine $CC $CFLAGS -c -o build/$i.o $i.cpp
    if [ $? != 0 ]; then
        exit 1
    else
        OBJECTS="$OBJECTS build/$i.o"
    fi
done

for i in $ASMFILES; do
    echo "Assembling $i.S..."
    wine $AS $ASMFLAGS -c -o build/$i.o $i.S
    if [ $? != 0 ]; then
        exit 1
    else
        OBJECTS="$OBJECTS build/$i.o"
    fi
done

echo 'Linking...'
Kamek $OBJECTS -dynamic -externals=externals-nsmbw.txt -versions=versions-nsmbw.txt -output-kamek=build/code\$KV\$.bin
if [ $? == 0 ]; then
    mv build/code$MYREGION.bin ~/.local/share/dolphin-emu/Load/Riivolution/nsmb
fi
