#!/bin/bash

# Make build folder
if [ -d 'build' ]; then
    rm -rf 'build'
fi
mkdir -p 'build'

# Hardcoded because yes
mkdir -p 'build/tileset'

# ASM compilation settings
AS='../cw/mwasmeppc.exe'
ASMFLAGS='-i . -I- -i ../include'
ASMFILES=''

# CPP compilation settings
CC='../cw/mwcceppc.exe'
CFLAGS='-i . -I- -i ../include -nostdinc -Cpp_exceptions off -RTTI off -once -O4,s -use_lmw_stmw on -fp fmadd -rostr -sdata 0 -sdata2 0'
CPPFILES='audio levelwarp powerup profile savefile system tileset/anim tileset/grass tileset/profoverride tileset/rand tileset/common'

# Destination
DEST=~/.local/share/dolphin-emu/Load/Riivolution/NSMASR/Code

# Set regions from input arguments or fallback to default
REGIONS=''
if [ $# != 0 ]; then
    REGIONS="$@"
else
    REGIONS='P1 P2 E1 E2 J1 J2 K W'
fi

for region in $REGIONS; do
    OBJECTS=''

    # Compile CPP
    for i in $CPPFILES; do
        echo "Compiling $i.cpp..."
        wine $CC $CFLAGS -DREGION_$region -c -o build/$i.o $i.cpp
        if [ $? != 0 ]; then
            exit 1
        else
            OBJECTS="$OBJECTS build/$i.o"
        fi
    done

    # Compile ASM
    for i in $ASMFILES; do
        echo "Assembling $i.S..."
        wine $AS $ASMFLAGS -DREGION_$region -c -o build/$i.o $i.S
        if [ $? != 0 ]; then
            exit 1
        else
            OBJECTS="$OBJECTS build/$i.o"
        fi
    done

    # Link
    echo 'Linking...'
    Kamek $OBJECTS -dynamic -externals=externals-nsmbw.txt -versions=versions-nsmbw.txt -select-version=$region -output-kamek=build/code\$KV\$.bin
    if [ $? == 0 ]; then
        mv build/code$region.bin $DEST
    fi
done
