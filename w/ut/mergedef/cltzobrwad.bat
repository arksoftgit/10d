cl /MDd -DDEBUG -D_DEBUG -Od /c /GS /TP /analyze- /W3 /Zc:wchar_t /ZI /Gm /sdl /Zc:inline /fp:precise  /D "_CRT_SECURE_NO_WARNINGS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL"  /D "tzobrwad_EXPORTS" /D "_WINDLL" /D "ZEIDON" /D "__WIN32__" /D "_UNICODE" /D "UNICODE"  /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd  /EHsc /nologo  /Fp"tzobrwad.pch" /Fd"vc140.pdb"  \10d\a\tz\tzobrwad.c -Fotzobrwad.obj
link zdrapp.lib zdctl.lib tzctl.lib /MANIFEST /NXCOMPAT /DYNAMICBASE /PDB:tzobrwad.PDB /debug:full "tzlodopr.lib" "kzoengaa.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DLL /MACHINE:X86 /INCREMENTAL  /SUBSYSTEM:WINDOWS  /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ManifestFile:"Debug\tzobrwad.dll.intermediate.manifest" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1 /OUT:tzobrwad.dll /DEF:tzobrwad.def /IMPLIB:tzobrwad.lib  tzobrwad.obj

dumpbin /exports tzobrwad.DLL > tzobrwad.DXX
mergedef tzobrwad.def tzobrwad.DXX