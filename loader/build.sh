#!/bin/bash

# Make build folder
if [ -d 'build' ]; then
	rm -rf 'build'
fi
mkdir -p 'build'

# CPP compilation settings
CC='../cw/mwcceppc.exe'
CPPFILES='kamekLoader nsmbw'
CFLAGS='-i . -I- -i ../include -nostdinc -Cpp_exceptions off -RTTI off -once -O4 -use_lmw_stmw on -fp fmadd -rostr -sdata 0 -sdata2 0'

# Compile CPP
for i in $CPPFILES; do
    echo Compiling $i.cpp...
    wine $CC $CFLAGS -c -o build/$i.o $i.cpp
    if [ $? != 0 ]; then
        exit 1
    fi
done

# Link
echo 'Linking...'
Kamek build/kamekLoader.o build/nsmbw.o -externals=externals-nsmbw.txt -static=0x800046E4 -output-code=build/Loader.bin -output-riiv=build/Loader.xml
