# Original script: https://github.com/Newer-Team/NewerSMBW/blob/cw/extractCW.sh
mkdir -p cw

cabextract -F Data1.cab CW55xx_v2_10_SE.exe

cabextract -F lmgr11.dll -p Data1.cab >cw/lmgr11.dll
cabextract -F lmgr8c.dll -p Data1.cab >cw/lmgr8c.dll
cabextract -F _44CD8EA541F44E56801091477F3DC9AA -p Data1.cab >cw/license.dat
cabextract -F _4C8ADA37887647F5955B4FB0F716277F -p Data1.cab >cw/mwcceppc.exe
cabextract -F _C63F22BC0503480DAFDCAFC394185CBA -p Data1.cab >cw/mwasmeppc.exe
cabextract -F _4901FAD667D24E13BCF700F695CDD6D7 -p Data1.cab >cw/mwldeppc.exe
cabextract -F _112A80A88B6147C590AE2CD9AE3F354F -p Data1.cab >cw/mwcceppc.txt
cabextract -F _39217B1AFC714B7083E6CB5CBB10FC83 -p Data1.cab >cw/mwasmeppc.txt
cabextract -F _312B4591741B497CB5EB342A632170BE -p Data1.cab >cw/mwldeppc.txt
cabextract -F _87844F06D94541B3B62E7A69C029A35D -p Data1.cab >cw/CLT_EABI_PPC_Tools_Notes.txt
cabextract -F _6F672001C92D4DF8B1893652C3B19743 -p Data1.cab >cw/CLT_Usage_Notes.txt

rm Data1.cab
