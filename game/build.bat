..\cw\mwcceppc -I- -i ../include -nostdinc -Cpp_exceptions off -enum int -O4 -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o 1-nsmbw-osreport.o 1-nsmbw-osreport.cpp
Kamek 1-nsmbw-osreport.o -dynamic -externals=externals-nsmbw.txt -versions=versions-nsmbw.txt -output-kamek=1-dynamic.$KV$.bin
