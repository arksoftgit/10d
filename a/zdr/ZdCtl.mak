# Microsoft Developer Studio Generated NMAKE File, Based on ZdCtl.dsp
!IF "$(CFG)" == ""
CFG=ZdCtl - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ZdCtl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ZdCtl - Win32 Release" && "$(CFG)" != "ZdCtl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZdCtl.mak" CFG="ZdCtl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZdCtl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ZdCtl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ZdCtl - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\w\bin\ZdCtl.dll"

!ELSE 

ALL : "JpegLib - Win32 Release" "ZDrApp - Win32 Release" "..\..\w\bin\ZdCtl.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ZDrApp - Win32 ReleaseCLEAN" "JpegLib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\ZdCtl.obj"
	-@erase "$(INTDIR)\ZdCtl.pch"
	-@erase "$(INTDIR)\ZdCtl.res"
	-@erase "$(INTDIR)\ZdCtlATX.obj"
	-@erase "$(INTDIR)\ZdCtlBar.obj"
	-@erase "$(INTDIR)\ZdCtlBMB.obj"
	-@erase "$(INTDIR)\ZdCtlBMP.obj"
	-@erase "$(INTDIR)\ZdCtlBTN.obj"
	-@erase "$(INTDIR)\ZdCtlCal.obj"
	-@erase "$(INTDIR)\ZdCtlCHK.obj"
	-@erase "$(INTDIR)\ZdCtlCMB.obj"
	-@erase "$(INTDIR)\ZdCtlDIL.obj"
	-@erase "$(INTDIR)\ZdCtlDT.obj"
	-@erase "$(INTDIR)\ZdCtlEDT.obj"
	-@erase "$(INTDIR)\ZdCtlGBX.obj"
	-@erase "$(INTDIR)\ZdCtlHD.obj"
	-@erase "$(INTDIR)\ZdCtlHDN.obj"
	-@erase "$(INTDIR)\ZdCtlHot.obj"
	-@erase "$(INTDIR)\ZdCtlICO.obj"
	-@erase "$(INTDIR)\ZdCtlLBH.obj"
	-@erase "$(INTDIR)\ZdCtlLBX.obj"
	-@erase "$(INTDIR)\ZdCtlMLE.obj"
	-@erase "$(INTDIR)\ZdCtlMST.obj"
	-@erase "$(INTDIR)\ZdCtlO.obj"
	-@erase "$(INTDIR)\ZdCtlOLB.obj"
	-@erase "$(INTDIR)\ZdCtlRB.obj"
	-@erase "$(INTDIR)\ZdCtlRTE.obj"
	-@erase "$(INTDIR)\ZdCtlRTO.obj"
	-@erase "$(INTDIR)\ZdCtlSS.obj"
	-@erase "$(INTDIR)\ZdCtlSSU.obj"
	-@erase "$(INTDIR)\ZdCtlTAB.obj"
	-@erase "$(INTDIR)\ZdCtlTim.obj"
	-@erase "$(INTDIR)\ZdCtlTXT.obj"
	-@erase "$(INTDIR)\ZdCtlVWG.obj"
	-@erase "..\..\w\bin\ZdCtl.dll"
	-@erase "..\..\w\libr\ZdCtl.exp"
	-@erase "..\..\w\libr\ZdCtl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /EHsc /O2 /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "NDEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /Fp"$(INTDIR)\ZdCtl.pch" /Yu"ZdCtl.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ZdCtl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ZdCtl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ZDrApp.lib kzoengaa.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ZdCtl.pdb" /machine:I386 /def:".\ZdCtl.def" /out:"..\..\w\bin\ZdCtl.dll" /implib:"..\..\w\libr\ZdCtl.lib" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" 
DEF_FILE= \
	".\ZdCtl.def"
LINK32_OBJS= \
	"$(INTDIR)\ZdCtl.obj" \
	"$(INTDIR)\ZdCtlATX.obj" \
	"$(INTDIR)\ZdCtlBar.obj" \
	"$(INTDIR)\ZdCtlBMB.obj" \
	"$(INTDIR)\ZdCtlBMP.obj" \
	"$(INTDIR)\ZdCtlBTN.obj" \
	"$(INTDIR)\ZdCtlCal.obj" \
	"$(INTDIR)\ZdCtlCHK.obj" \
	"$(INTDIR)\ZdCtlCMB.obj" \
	"$(INTDIR)\ZdCtlDIL.obj" \
	"$(INTDIR)\ZdCtlDT.obj" \
	"$(INTDIR)\ZdCtlEDT.obj" \
	"$(INTDIR)\ZdCtlGBX.obj" \
	"$(INTDIR)\ZdCtlHD.obj" \
	"$(INTDIR)\ZdCtlHDN.obj" \
	"$(INTDIR)\ZdCtlHot.obj" \
	"$(INTDIR)\ZdCtlICO.obj" \
	"$(INTDIR)\ZdCtlLBH.obj" \
	"$(INTDIR)\ZdCtlLBX.obj" \
	"$(INTDIR)\ZdCtlMLE.obj" \
	"$(INTDIR)\ZdCtlMST.obj" \
	"$(INTDIR)\ZdCtlO.obj" \
	"$(INTDIR)\ZdCtlOLB.obj" \
	"$(INTDIR)\ZdCtlRB.obj" \
	"$(INTDIR)\ZdCtlRTE.obj" \
	"$(INTDIR)\ZdCtlRTO.obj" \
	"$(INTDIR)\ZdCtlSS.obj" \
	"$(INTDIR)\ZdCtlSSU.obj" \
	"$(INTDIR)\ZdCtlTAB.obj" \
	"$(INTDIR)\ZdCtlTim.obj" \
	"$(INTDIR)\ZdCtlTXT.obj" \
	"$(INTDIR)\ZdCtlVWG.obj" \
	"$(INTDIR)\ZdCtl.res" \
	"..\..\w\libr\ZDrApp.lib" \
	"..\..\w\libr\JpegLib.lib"

"..\..\w\bin\ZdCtl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\w\bin\ZdCtl.dll" "$(OUTDIR)\ZDr.bsc"

!ELSE 

ALL : "JpegLib - Win32 Debug" "ZDrApp - Win32 Debug" "..\..\w\bin\ZdCtl.dll" "$(OUTDIR)\ZDr.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ZDrApp - Win32 DebugCLEAN" "JpegLib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\ZdCtl.obj"
	-@erase "$(INTDIR)\ZdCtl.pch"
	-@erase "$(INTDIR)\ZdCtl.res"
	-@erase "$(INTDIR)\ZdCtl.sbr"
	-@erase "$(INTDIR)\ZdCtlATX.obj"
	-@erase "$(INTDIR)\ZdCtlATX.sbr"
	-@erase "$(INTDIR)\ZdCtlBar.obj"
	-@erase "$(INTDIR)\ZdCtlBar.sbr"
	-@erase "$(INTDIR)\ZdCtlBMB.obj"
	-@erase "$(INTDIR)\ZdCtlBMB.sbr"
	-@erase "$(INTDIR)\ZdCtlBMP.obj"
	-@erase "$(INTDIR)\ZdCtlBMP.sbr"
	-@erase "$(INTDIR)\ZdCtlBTN.obj"
	-@erase "$(INTDIR)\ZdCtlBTN.sbr"
	-@erase "$(INTDIR)\ZdCtlCal.obj"
	-@erase "$(INTDIR)\ZdCtlCal.sbr"
	-@erase "$(INTDIR)\ZdCtlCHK.obj"
	-@erase "$(INTDIR)\ZdCtlCHK.sbr"
	-@erase "$(INTDIR)\ZdCtlCMB.obj"
	-@erase "$(INTDIR)\ZdCtlCMB.sbr"
	-@erase "$(INTDIR)\ZdCtlDIL.obj"
	-@erase "$(INTDIR)\ZdCtlDIL.sbr"
	-@erase "$(INTDIR)\ZdCtlDT.obj"
	-@erase "$(INTDIR)\ZdCtlDT.sbr"
	-@erase "$(INTDIR)\ZdCtlEDT.obj"
	-@erase "$(INTDIR)\ZdCtlEDT.sbr"
	-@erase "$(INTDIR)\ZdCtlGBX.obj"
	-@erase "$(INTDIR)\ZdCtlGBX.sbr"
	-@erase "$(INTDIR)\ZdCtlHD.obj"
	-@erase "$(INTDIR)\ZdCtlHD.sbr"
	-@erase "$(INTDIR)\ZdCtlHDN.obj"
	-@erase "$(INTDIR)\ZdCtlHDN.sbr"
	-@erase "$(INTDIR)\ZdCtlHot.obj"
	-@erase "$(INTDIR)\ZdCtlHot.sbr"
	-@erase "$(INTDIR)\ZdCtlICO.obj"
	-@erase "$(INTDIR)\ZdCtlICO.sbr"
	-@erase "$(INTDIR)\ZdCtlLBH.obj"
	-@erase "$(INTDIR)\ZdCtlLBH.sbr"
	-@erase "$(INTDIR)\ZdCtlLBX.obj"
	-@erase "$(INTDIR)\ZdCtlLBX.sbr"
	-@erase "$(INTDIR)\ZdCtlMLE.obj"
	-@erase "$(INTDIR)\ZdCtlMLE.sbr"
	-@erase "$(INTDIR)\ZdCtlMST.obj"
	-@erase "$(INTDIR)\ZdCtlMST.sbr"
	-@erase "$(INTDIR)\ZdCtlO.obj"
	-@erase "$(INTDIR)\ZdCtlO.sbr"
	-@erase "$(INTDIR)\ZdCtlOLB.obj"
	-@erase "$(INTDIR)\ZdCtlOLB.sbr"
	-@erase "$(INTDIR)\ZdCtlRB.obj"
	-@erase "$(INTDIR)\ZdCtlRB.sbr"
	-@erase "$(INTDIR)\ZdCtlRTE.obj"
	-@erase "$(INTDIR)\ZdCtlRTE.sbr"
	-@erase "$(INTDIR)\ZdCtlRTO.obj"
	-@erase "$(INTDIR)\ZdCtlRTO.sbr"
	-@erase "$(INTDIR)\ZdCtlSS.obj"
	-@erase "$(INTDIR)\ZdCtlSS.sbr"
	-@erase "$(INTDIR)\ZdCtlSSU.obj"
	-@erase "$(INTDIR)\ZdCtlSSU.sbr"
	-@erase "$(INTDIR)\ZdCtlTAB.obj"
	-@erase "$(INTDIR)\ZdCtlTAB.sbr"
	-@erase "$(INTDIR)\ZdCtlTim.obj"
	-@erase "$(INTDIR)\ZdCtlTim.sbr"
	-@erase "$(INTDIR)\ZdCtlTXT.obj"
	-@erase "$(INTDIR)\ZdCtlTXT.sbr"
	-@erase "$(INTDIR)\ZdCtlVWG.obj"
	-@erase "$(INTDIR)\ZdCtlVWG.sbr"
	-@erase "$(OUTDIR)\ZdCtl.pdb"
	-@erase "$(OUTDIR)\ZDr.bsc"
	-@erase "..\..\w\bin\ZdCtl.dll"
	-@erase "..\..\w\bin\ZdCtl.ilk"
	-@erase "..\..\w\libr\ZdCtl.exp"
	-@erase "..\..\w\libr\ZdCtl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /EHsc /ZI /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "_DEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ZdCtl.pch" /Yu"ZdCtl.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ZdCtl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ZDr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ZdCtl.sbr" \
	"$(INTDIR)\ZdCtlATX.sbr" \
	"$(INTDIR)\ZdCtlBar.sbr" \
	"$(INTDIR)\ZdCtlBMB.sbr" \
	"$(INTDIR)\ZdCtlBMP.sbr" \
	"$(INTDIR)\ZdCtlBTN.sbr" \
	"$(INTDIR)\ZdCtlCal.sbr" \
	"$(INTDIR)\ZdCtlCHK.sbr" \
	"$(INTDIR)\ZdCtlCMB.sbr" \
	"$(INTDIR)\ZdCtlDIL.sbr" \
	"$(INTDIR)\ZdCtlDT.sbr" \
	"$(INTDIR)\ZdCtlEDT.sbr" \
	"$(INTDIR)\ZdCtlGBX.sbr" \
	"$(INTDIR)\ZdCtlHD.sbr" \
	"$(INTDIR)\ZdCtlHDN.sbr" \
	"$(INTDIR)\ZdCtlHot.sbr" \
	"$(INTDIR)\ZdCtlICO.sbr" \
	"$(INTDIR)\ZdCtlLBH.sbr" \
	"$(INTDIR)\ZdCtlLBX.sbr" \
	"$(INTDIR)\ZdCtlMLE.sbr" \
	"$(INTDIR)\ZdCtlMST.sbr" \
	"$(INTDIR)\ZdCtlO.sbr" \
	"$(INTDIR)\ZdCtlOLB.sbr" \
	"$(INTDIR)\ZdCtlRB.sbr" \
	"$(INTDIR)\ZdCtlRTE.sbr" \
	"$(INTDIR)\ZdCtlRTO.sbr" \
	"$(INTDIR)\ZdCtlSS.sbr" \
	"$(INTDIR)\ZdCtlSSU.sbr" \
	"$(INTDIR)\ZdCtlTAB.sbr" \
	"$(INTDIR)\ZdCtlTim.sbr" \
	"$(INTDIR)\ZdCtlTXT.sbr" \
	"$(INTDIR)\ZdCtlVWG.sbr"

"$(OUTDIR)\ZDr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ZDrApp.lib kzoengaa.lib jpeglib.lib msimg32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ZdCtl.pdb" /debug /machine:I386 /def:".\ZdCtl.def" /out:"..\..\w\bin\ZdCtl.dll" /implib:"..\..\w\libr\ZdCtl.lib" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" 
DEF_FILE= \
	".\ZdCtl.def"
LINK32_OBJS= \
	"$(INTDIR)\ZdCtl.obj" \
	"$(INTDIR)\ZdCtlATX.obj" \
	"$(INTDIR)\ZdCtlBar.obj" \
	"$(INTDIR)\ZdCtlBMB.obj" \
	"$(INTDIR)\ZdCtlBMP.obj" \
	"$(INTDIR)\ZdCtlBTN.obj" \
	"$(INTDIR)\ZdCtlCal.obj" \
	"$(INTDIR)\ZdCtlCHK.obj" \
	"$(INTDIR)\ZdCtlCMB.obj" \
	"$(INTDIR)\ZdCtlDIL.obj" \
	"$(INTDIR)\ZdCtlDT.obj" \
	"$(INTDIR)\ZdCtlEDT.obj" \
	"$(INTDIR)\ZdCtlGBX.obj" \
	"$(INTDIR)\ZdCtlHD.obj" \
	"$(INTDIR)\ZdCtlHDN.obj" \
	"$(INTDIR)\ZdCtlHot.obj" \
	"$(INTDIR)\ZdCtlICO.obj" \
	"$(INTDIR)\ZdCtlLBH.obj" \
	"$(INTDIR)\ZdCtlLBX.obj" \
	"$(INTDIR)\ZdCtlMLE.obj" \
	"$(INTDIR)\ZdCtlMST.obj" \
	"$(INTDIR)\ZdCtlO.obj" \
	"$(INTDIR)\ZdCtlOLB.obj" \
	"$(INTDIR)\ZdCtlRB.obj" \
	"$(INTDIR)\ZdCtlRTE.obj" \
	"$(INTDIR)\ZdCtlRTO.obj" \
	"$(INTDIR)\ZdCtlSS.obj" \
	"$(INTDIR)\ZdCtlSSU.obj" \
	"$(INTDIR)\ZdCtlTAB.obj" \
	"$(INTDIR)\ZdCtlTim.obj" \
	"$(INTDIR)\ZdCtlTXT.obj" \
	"$(INTDIR)\ZdCtlVWG.obj" \
	"$(INTDIR)\ZdCtl.res" \
	"..\..\w\libr\ZDrApp.lib" \
	"..\..\w\libr\JpegLib.lib"

"..\..\w\bin\ZdCtl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ZdCtl.dep")
!INCLUDE "ZdCtl.dep"
!ELSE 
!MESSAGE Warning: cannot find "ZdCtl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ZdCtl - Win32 Release" || "$(CFG)" == "ZdCtl - Win32 Debug"
SOURCE=.\ZdCtl.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /EHsc /O2 /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "NDEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /Fp"$(INTDIR)\ZdCtl.pch" /Yc"ZdCtl.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ZdCtl.obj"	"$(INTDIR)\ZdCtl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /EHsc /ZI /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "_DEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ZdCtl.pch" /Yc"ZdCtl.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ZdCtl.obj"	"$(INTDIR)\ZdCtl.sbr"	"$(INTDIR)\ZdCtl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ZdCtl.rc

"$(INTDIR)\ZdCtl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ZdCtlATX.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlATX.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlATX.obj"	"$(INTDIR)\ZdCtlATX.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlBar.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlBar.obj"	"$(INTDIR)\ZdCtlBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlBMB.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlBMB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlBMB.obj"	"$(INTDIR)\ZdCtlBMB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlBMP.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlBMP.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlBMP.obj"	"$(INTDIR)\ZdCtlBMP.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlBTN.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlBTN.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlBTN.obj"	"$(INTDIR)\ZdCtlBTN.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlCal.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlCal.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlCal.obj"	"$(INTDIR)\ZdCtlCal.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlCHK.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlCHK.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlCHK.obj"	"$(INTDIR)\ZdCtlCHK.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlCMB.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlCMB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlCMB.obj"	"$(INTDIR)\ZdCtlCMB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlDIL.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlDIL.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlDIL.obj"	"$(INTDIR)\ZdCtlDIL.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlDT.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlDT.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlDT.obj"	"$(INTDIR)\ZdCtlDT.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlEDT.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlEDT.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlEDT.obj"	"$(INTDIR)\ZdCtlEDT.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlGBX.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlGBX.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlGBX.obj"	"$(INTDIR)\ZdCtlGBX.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlHD.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlHD.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlHD.obj"	"$(INTDIR)\ZdCtlHD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlHDN.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlHDN.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlHDN.obj"	"$(INTDIR)\ZdCtlHDN.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlHot.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlHot.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlHot.obj"	"$(INTDIR)\ZdCtlHot.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlICO.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlICO.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlICO.obj"	"$(INTDIR)\ZdCtlICO.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlLBH.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlLBH.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlLBH.obj"	"$(INTDIR)\ZdCtlLBH.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlLBX.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlLBX.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlLBX.obj"	"$(INTDIR)\ZdCtlLBX.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlMLE.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlMLE.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlMLE.obj"	"$(INTDIR)\ZdCtlMLE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlMST.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlMST.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlMST.obj"	"$(INTDIR)\ZdCtlMST.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlO.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlO.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlO.obj"	"$(INTDIR)\ZdCtlO.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlOLB.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlOLB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlOLB.obj"	"$(INTDIR)\ZdCtlOLB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlRB.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlRB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlRB.obj"	"$(INTDIR)\ZdCtlRB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlRTE.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlRTE.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlRTE.obj"	"$(INTDIR)\ZdCtlRTE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlRTO.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlRTO.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlRTO.obj"	"$(INTDIR)\ZdCtlRTO.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlSS.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlSS.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlSS.obj"	"$(INTDIR)\ZdCtlSS.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlSSU.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlSSU.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlSSU.obj"	"$(INTDIR)\ZdCtlSSU.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlTAB.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlTAB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlTAB.obj"	"$(INTDIR)\ZdCtlTAB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlTim.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlTim.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlTim.obj"	"$(INTDIR)\ZdCtlTim.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlTXT.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlTXT.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlTXT.obj"	"$(INTDIR)\ZdCtlTXT.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

SOURCE=.\ZdCtlVWG.cpp

!IF  "$(CFG)" == "ZdCtl - Win32 Release"


"$(INTDIR)\ZdCtlVWG.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"


"$(INTDIR)\ZdCtlVWG.obj"	"$(INTDIR)\ZdCtlVWG.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZdCtl.pch"


!ENDIF 

!IF  "$(CFG)" == "ZdCtl - Win32 Release"

"ZDrApp - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Release" 
   cd "."

"ZDrApp - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"

"ZDrApp - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Debug" 
   cd "."

"ZDrApp - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "ZdCtl - Win32 Release"

"JpegLib - Win32 Release" : 
   cd ".\JPegLib"
   $(MAKE) /$(MAKEFLAGS) /F .\JPegLib.mak CFG="JpegLib - Win32 Release" 
   cd ".."

"JpegLib - Win32 ReleaseCLEAN" : 
   cd ".\JPegLib"
   $(MAKE) /$(MAKEFLAGS) /F .\JPegLib.mak CFG="JpegLib - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "ZdCtl - Win32 Debug"

"JpegLib - Win32 Debug" : 
   cd ".\JPegLib"
   $(MAKE) /$(MAKEFLAGS) /F .\JPegLib.mak CFG="JpegLib - Win32 Debug" 
   cd ".."

"JpegLib - Win32 DebugCLEAN" : 
   cd ".\JPegLib"
   $(MAKE) /$(MAKEFLAGS) /F .\JPegLib.mak CFG="JpegLib - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

