@echo off
SETLOCAL EnableDelayedExpansion

:: Make build folder
IF exists build\ (
	rmdir /Q /S build
)
mkdir build

::Hardcoded because yes
mkdir build\tileset

:: ASM compilation settings
SET AS="..\cw\mwasmeppc.exe"
SET ASMFLAGS="-i . -I- -i ../include"
SET ASMFILES=""

:: CPP compilation settings
SET CC="..\cw\mwcceppc.exe"
SET CFLAGS="-i . -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -RTTI off -once -O4,s -use_lmw_stmw on -fp fmadd -rostr -sdata 0 -sdata2 0"
SET CPPFILES="audio effectspawner flagpole levelwarp powerup profile rotcontroller savefile system tilegod tileset\anim tileset\grass tileset\profoverride tileset\rand tileset\common zone"

:: Destination (change as necessary)
SET DEST="%USERPROFILE%\Documents\Dolphin Emulator\Load\Riivolution\NSMASR\code"

:: Set regions from input arguments or fallback to default
IF "%1" == "" (
	SET REGIONS="%1"
) ELSE (
    SET REGIONS="P1;P2;E1;E2;J1;J2;K;W"
)

FOR %%G IN (%REGIONS%) DO (
    SET OBJECTS=""

    :: Compile CPP
    FOR %%H IN (%CPPFILES%) DO (
        echo "Compiling %%H.cpp..."
        %CC% %CFLAGS% "-DREGION_$region -c -o build\%%H.o %%H.cpp"
        if %ErrorLevel% neq 0 (
            goto end
        ) else (
            SET OBJECTS="%OBJECTS% build\%%H.o"
        )
    )

    :: Compile ASM
    FOR %%I IN (%ASMFILES%) DO (
        echo "Compiling %%I.S..."
        %AS% %ASMFLAGS% "-DREGION_$region -c -o build\%%I.o %%I.S"
        if %ErrorLevel% neq 0 (
            goto end
        ) else (
            SET OBJECTS="%OBJECTS% build\%%I.o"
        )
    )

    :: Link
    echo Linking...
    Kamek %OBJECTS% -dynamic -externals=externals-nsmbw.txt -versions=versions-nsmbw.txt -select-version=%%G -output-kamek=build\code%%G.bin
    if %ErrorLevel% equ 0 (
        move /Y build\code%%G.bin %DEST%
    )
)

:end
ENDLOCAL
