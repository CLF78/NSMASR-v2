..\cw\mwcceppc -i . -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o build/kamekLoader.o kamekLoader.cpp
..\cw\mwcceppc -i . -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o build/nsmbw.o nsmbw.cpp

Kamek build/kamekLoader.o build/nsmbw.o -externals=externals-nsmbw.txt -static=0x800046E4 -output-code=build/loader.bin -output-riiv=build/loader.xml
