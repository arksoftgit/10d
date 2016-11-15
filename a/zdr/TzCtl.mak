# Microsoft Developer Studio Generated NMAKE File, Based on TzCtl.dsp
!IF "$(CFG)" == ""
CFG=TzCtl - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TzCtl - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "TzCtl - Win32 Release" && "$(CFG)" != "TzCtl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TzCtl.mak" CFG="TzCtl - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TzCtl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TzCtl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TzCtl - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\w\bin\TzCtl.dll"

!ELSE 

ALL : "ZDrApp - Win32 Release" "ZdCtl - Win32 Release" "..\..\w\bin\TzCtl.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ZdCtl - Win32 ReleaseCLEAN" "ZDrApp - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\TzCtl.obj"
	-@erase "$(INTDIR)\TzCtl.pch"
	-@erase "$(INTDIR)\TzCtl.res"
	-@erase "$(INTDIR)\TzCtlATX.obj"
	-@erase "$(INTDIR)\TzCtlCVT.obj"
	-@erase "$(INTDIR)\TzCtlERD.obj"
	-@erase "$(INTDIR)\TzCtlERE.obj"
	-@erase "$(INTDIR)\TzCtlERL.obj"
	-@erase "$(INTDIR)\TzCtlERV.obj"
	-@erase "$(INTDIR)\TzCtlOPR.obj"
	-@erase "$(INTDIR)\TzCtlPTB.obj"
	-@erase "$(INTDIR)\TzCtlPTC.obj"
	-@erase "$(INTDIR)\TzCtlPTE.obj"
	-@erase "$(INTDIR)\TzCtlPTM.obj"
	-@erase "$(INTDIR)\TzCtlPTR.obj"
	-@erase "$(INTDIR)\TzCtlPTS.obj"
	-@erase "$(INTDIR)\TzCtlPTU.obj"
	-@erase "$(INTDIR)\TzCtlPTX.obj"
	-@erase "$(INTDIR)\TzCtlTAB.obj"
	-@erase "$(INTDIR)\TzCtlTBE.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TzCtl.map"
	-@erase "..\..\w\bin\TzCtl.dll"
	-@erase "..\..\w\libr\TzCtl.exp"
	-@erase "..\..\w\libr\TzCtl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /EHsc /O2 /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "NDEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /Fp"$(INTDIR)\TzCtl.pch" /Yu"TzCtl.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TzCtl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TzCtl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ZdCtl.lib ZDrApp.lib kzoengaa.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\TzCtl.pdb" /map:"$(INTDIR)\TzCtl.map" /machine:I386 /def:".\TzCtl.def" /out:"..\..\w\bin\TzCtl.dll" /implib:"..\..\w\libr\TzCtl.lib" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" 
DEF_FILE= \
	".\TzCtl.def"
LINK32_OBJS= \
	"$(INTDIR)\TzCtl.obj" \
	"$(INTDIR)\TzCtlATX.obj" \
	"$(INTDIR)\TzCtlCVT.obj" \
	"$(INTDIR)\TzCtlERD.obj" \
	"$(INTDIR)\TzCtlERE.obj" \
	"$(INTDIR)\TzCtlERL.obj" \
	"$(INTDIR)\TzCtlERV.obj" \
	"$(INTDIR)\TzCtlOPR.obj" \
	"$(INTDIR)\TzCtlPTB.obj" \
	"$(INTDIR)\TzCtlPTC.obj" \
	"$(INTDIR)\TzCtlPTE.obj" \
	"$(INTDIR)\TzCtlPTM.obj" \
	"$(INTDIR)\TzCtlPTR.obj" \
	"$(INTDIR)\TzCtlPTS.obj" \
	"$(INTDIR)\TzCtlPTU.obj" \
	"$(INTDIR)\TzCtlPTX.obj" \
	"$(INTDIR)\TzCtlTAB.obj" \
	"$(INTDIR)\TzCtlTBE.obj" \
	"$(INTDIR)\TzCtl.res" \
	"..\..\w\libr\ZdCtl.lib" \
	"..\..\w\libr\ZDrApp.lib"

"..\..\w\bin\TzCtl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\w\bin\TzCtl.dll" "$(OUTDIR)\ZDr.bsc"

!ELSE 

ALL : "ZDrApp - Win32 Debug" "ZdCtl - Win32 Debug" "..\..\w\bin\TzCtl.dll" "$(OUTDIR)\ZDr.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ZdCtl - Win32 DebugCLEAN" "ZDrApp - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\TzCtl.obj"
	-@erase "$(INTDIR)\TzCtl.pch"
	-@erase "$(INTDIR)\TzCtl.res"
	-@erase "$(INTDIR)\TzCtl.sbr"
	-@erase "$(INTDIR)\TzCtlATX.obj"
	-@erase "$(INTDIR)\TzCtlATX.sbr"
	-@erase "$(INTDIR)\TzCtlCVT.obj"
	-@erase "$(INTDIR)\TzCtlCVT.sbr"
	-@erase "$(INTDIR)\TzCtlERD.obj"
	-@erase "$(INTDIR)\TzCtlERD.sbr"
	-@erase "$(INTDIR)\TzCtlERE.obj"
	-@erase "$(INTDIR)\TzCtlERE.sbr"
	-@erase "$(INTDIR)\TzCtlERL.obj"
	-@erase "$(INTDIR)\TzCtlERL.sbr"
	-@erase "$(INTDIR)\TzCtlERV.obj"
	-@erase "$(INTDIR)\TzCtlERV.sbr"
	-@erase "$(INTDIR)\TzCtlOPR.obj"
	-@erase "$(INTDIR)\TzCtlOPR.sbr"
	-@erase "$(INTDIR)\TzCtlPTB.obj"
	-@erase "$(INTDIR)\TzCtlPTB.sbr"
	-@erase "$(INTDIR)\TzCtlPTC.obj"
	-@erase "$(INTDIR)\TzCtlPTC.sbr"
	-@erase "$(INTDIR)\TzCtlPTE.obj"
	-@erase "$(INTDIR)\TzCtlPTE.sbr"
	-@erase "$(INTDIR)\TzCtlPTM.obj"
	-@erase "$(INTDIR)\TzCtlPTM.sbr"
	-@erase "$(INTDIR)\TzCtlPTR.obj"
	-@erase "$(INTDIR)\TzCtlPTR.sbr"
	-@erase "$(INTDIR)\TzCtlPTS.obj"
	-@erase "$(INTDIR)\TzCtlPTS.sbr"
	-@erase "$(INTDIR)\TzCtlPTU.obj"
	-@erase "$(INTDIR)\TzCtlPTU.sbr"
	-@erase "$(INTDIR)\TzCtlPTX.obj"
	-@erase "$(INTDIR)\TzCtlPTX.sbr"
	-@erase "$(INTDIR)\TzCtlTAB.obj"
	-@erase "$(INTDIR)\TzCtlTAB.sbr"
	-@erase "$(INTDIR)\TzCtlTBE.obj"
	-@erase "$(INTDIR)\TzCtlTBE.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TzCtl.pdb"
	-@erase "$(OUTDIR)\ZDr.bsc"
	-@erase "..\..\w\bin\TzCtl.dll"
	-@erase "..\..\w\bin\TzCtl.ilk"
	-@erase "..\..\w\libr\TzCtl.exp"
	-@erase "..\..\w\libr\TzCtl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /EHsc /ZI /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "_DEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TzCtl.pch" /Yu"TzCtl.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TzCtl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ZDr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\TzCtl.sbr" \
	"$(INTDIR)\TzCtlATX.sbr" \
	"$(INTDIR)\TzCtlCVT.sbr" \
	"$(INTDIR)\TzCtlERD.sbr" \
	"$(INTDIR)\TzCtlERE.sbr" \
	"$(INTDIR)\TzCtlERL.sbr" \
	"$(INTDIR)\TzCtlERV.sbr" \
	"$(INTDIR)\TzCtlOPR.sbr" \
	"$(INTDIR)\TzCtlPTB.sbr" \
	"$(INTDIR)\TzCtlPTC.sbr" \
	"$(INTDIR)\TzCtlPTE.sbr" \
	"$(INTDIR)\TzCtlPTM.sbr" \
	"$(INTDIR)\TzCtlPTR.sbr" \
	"$(INTDIR)\TzCtlPTS.sbr" \
	"$(INTDIR)\TzCtlPTU.sbr" \
	"$(INTDIR)\TzCtlPTX.sbr" \
	"$(INTDIR)\TzCtlTAB.sbr" \
	"$(INTDIR)\TzCtlTBE.sbr"

"$(OUTDIR)\ZDr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ZdCtl.lib ZDrApp.lib kzoengaa.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\TzCtl.pdb" /debug /machine:I386 /def:".\TzCtl.def" /out:"..\..\w\bin\TzCtl.dll" /implib:"..\..\w\libr\TzCtl.lib" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" 
DEF_FILE= \
	".\TzCtl.def"
LINK32_OBJS= \
	"$(INTDIR)\TzCtl.obj" \
	"$(INTDIR)\TzCtlATX.obj" \
	"$(INTDIR)\TzCtlCVT.obj" \
	"$(INTDIR)\TzCtlERD.obj" \
	"$(INTDIR)\TzCtlERE.obj" \
	"$(INTDIR)\TzCtlERL.obj" \
	"$(INTDIR)\TzCtlERV.obj" \
	"$(INTDIR)\TzCtlOPR.obj" \
	"$(INTDIR)\TzCtlPTB.obj" \
	"$(INTDIR)\TzCtlPTC.obj" \
	"$(INTDIR)\TzCtlPTE.obj" \
	"$(INTDIR)\TzCtlPTM.obj" \
	"$(INTDIR)\TzCtlPTR.obj" \
	"$(INTDIR)\TzCtlPTS.obj" \
	"$(INTDIR)\TzCtlPTU.obj" \
	"$(INTDIR)\TzCtlPTX.obj" \
	"$(INTDIR)\TzCtlTAB.obj" \
	"$(INTDIR)\TzCtlTBE.obj" \
	"$(INTDIR)\TzCtl.res" \
	"..\..\w\libr\ZdCtl.lib" \
	"..\..\w\libr\ZDrApp.lib"

"..\..\w\bin\TzCtl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TzCtl.dep")
!INCLUDE "TzCtl.dep"
!ELSE 
!MESSAGE Warning: cannot find "TzCtl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TzCtl - Win32 Release" || "$(CFG)" == "TzCtl - Win32 Debug"
SOURCE=.\TzCtl.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /EHsc /O2 /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "NDEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /Fp"$(INTDIR)\TzCtl.pch" /Yc"TzCtl.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\TzCtl.obj"	"$(INTDIR)\TzCtl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /EHsc /ZI /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "_DEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TzCtl.pch" /Yc"TzCtl.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\TzCtl.obj"	"$(INTDIR)\TzCtl.sbr"	"$(INTDIR)\TzCtl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TzCtl.rc

"$(INTDIR)\TzCtl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\TzCtlATX.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlATX.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlATX.obj"	"$(INTDIR)\TzCtlATX.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlCVT.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlCVT.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlCVT.obj"	"$(INTDIR)\TzCtlCVT.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlERD.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlERD.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlERD.obj"	"$(INTDIR)\TzCtlERD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlERE.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlERE.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlERE.obj"	"$(INTDIR)\TzCtlERE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlERL.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlERL.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlERL.obj"	"$(INTDIR)\TzCtlERL.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlERV.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlERV.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlERV.obj"	"$(INTDIR)\TzCtlERV.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlOPR.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlOPR.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlOPR.obj"	"$(INTDIR)\TzCtlOPR.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlPTB.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlPTB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlPTB.obj"	"$(INTDIR)\TzCtlPTB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlPTC.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlPTC.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlPTC.obj"	"$(INTDIR)\TzCtlPTC.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlPTE.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlPTE.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlPTE.obj"	"$(INTDIR)\TzCtlPTE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlPTM.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlPTM.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlPTM.obj"	"$(INTDIR)\TzCtlPTM.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlPTR.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlPTR.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlPTR.obj"	"$(INTDIR)\TzCtlPTR.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlPTS.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlPTS.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlPTS.obj"	"$(INTDIR)\TzCtlPTS.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlPTU.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlPTU.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlPTU.obj"	"$(INTDIR)\TzCtlPTU.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlPTX.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlPTX.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlPTX.obj"	"$(INTDIR)\TzCtlPTX.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlTAB.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlTAB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlTAB.obj"	"$(INTDIR)\TzCtlTAB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

SOURCE=.\TzCtlTBE.cpp

!IF  "$(CFG)" == "TzCtl - Win32 Release"


"$(INTDIR)\TzCtlTBE.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"


"$(INTDIR)\TzCtlTBE.obj"	"$(INTDIR)\TzCtlTBE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TzCtl.pch"


!ENDIF 

!IF  "$(CFG)" == "TzCtl - Win32 Release"

"ZdCtl - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZdCtl.mak CFG="ZdCtl - Win32 Release" 
   cd "."

"ZdCtl - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZdCtl.mak CFG="ZdCtl - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"

"ZdCtl - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZdCtl.mak CFG="ZdCtl - Win32 Debug" 
   cd "."

"ZdCtl - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZdCtl.mak CFG="ZdCtl - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "TzCtl - Win32 Release"

"ZDrApp - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Release" 
   cd "."

"ZDrApp - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "TzCtl - Win32 Debug"

"ZDrApp - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Debug" 
   cd "."

"ZDrApp - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 

