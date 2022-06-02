# Original script: https://github.com/Newer-Team/NewerSMBW/blob/cw/extractCW.sh
mkdir -p cw

cabextract -F Data1.cab CW55xx_v2_10_SE.exe

cabextract -F lmgr11.dll -p Data1.cab >cw/lmgr11.dll
cabextract -F _44CD8EA541F44E56801091477F3DC9AA -p Data1.cab >cw/license.dat
cabextract -F _4C8ADA37887647F5955B4FB0F716277F -p Data1.cab >cw/mwcceppc.exe

rm Data1.cab
