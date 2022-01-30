#!/bin/bash

if [ -d 'build' ]; then
	rm -rf 'build'
fi
mkdir -p 'build'

CC="../cw/mwcceppc.exe"
CPPFILES='kamekLoader nsmbw'
CFLAGS='-i . -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0'

for i in $CPPFILES; do
    echo Compiling $i.cpp...
    wine $CC $CFLAGS -c -o build/$i.o $i.cpp
    if [ $? != 0 ]; then
        exit 1
    fi
done

echo 'Linking...'
Kamek build/kamekLoader.o build/nsmbw.o -externals=externals-nsmbw.txt -static=0x800046E4 -output-code=build/loader.bin -output-riiv=build/loader.xml
