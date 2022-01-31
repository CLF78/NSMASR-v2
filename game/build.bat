..\cw\mwcceppc -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o build/profile.o profile.cpp
Kamek build/profile.o -dynamic -externals=externals-nsmbw.txt -versions=versions-nsmbw.txt -output-kamek=build/code$KV$.bin
