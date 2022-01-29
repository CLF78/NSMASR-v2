..\cw\mwcceppc -i . -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o kamekLoader.o kamekLoader.cpp
..\cw\mwcceppc -i . -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o nsmbw.o nsmbw.cpp

Kamek kamekLoader.o nsmbw.o -externals=addresses.txt -static=0x800046E4 -output-code=loader.bin -output-riiv=loader.xml
