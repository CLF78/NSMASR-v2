@echo off
SETLOCAL EnableDelayedExpansion

:: Make build folder
IF exists build\ (
	rmdir /Q /S build
)
mkdir build

:: CPP compilation settings
SET CC="..\cw\mwcceppc.exe"
SET CFLAGS="-i . -I- -i ../include -nostdinc -Cpp_exceptions off -RTTI off -once -O4 -use_lmw_stmw on -fp fmadd -rostr -sdata 0 -sdata2 0"
SET CPPFILES="kamekLoader nsmbw"

SET OBJECTS=""

:: Compile CPP
FOR %%H IN (%CPPFILES%) DO (
    echo "Compiling %%H.cpp..."
    %CC% %CFLAGS% -c -o build\%%H.o %%H.cpp"
    if %ErrorLevel% neq 0 (
        goto end
    ) else (
        SET OBJECTS="%OBJECTS% build\%%H.o"
    )
)

:: Link
echo Linking...
Kamek %OBJECTS% -externals=externals-nsmbw.txt -static=0x800046E4 -output-code=build\loader.bin -output-riiv=build\loader.xml

ENDLOCAL
