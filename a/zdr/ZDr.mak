# Microsoft Developer Studio Generated NMAKE File, Based on ZDr.dsp
!IF "$(CFG)" == ""
CFG=ZDr - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ZDr - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ZDr - Win32 Release" && "$(CFG)" != "ZDr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZDr.mak" CFG="ZDr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZDr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ZDr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\w\bin\ZDr.exe"

!ELSE 

ALL : "JpegLib - Win32 Release" "ZSEMail - Win32 Release" "tzvmledt - Win32 Release" "truegrid - Win32 Release" "tzedvmld - Win32 Release" "Z2MP - Win32 Release" "tbedit - Win32 Release" "ZDrApp - Win32 Release" "ZdCtl - Win32 Release" "TzCtl - Win32 Release" "TzAxCtl - Win32 Release" "..\..\w\bin\ZDr.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"TzAxCtl - Win32 ReleaseCLEAN" "TzCtl - Win32 ReleaseCLEAN" "ZdCtl - Win32 ReleaseCLEAN" "ZDrApp - Win32 ReleaseCLEAN" "tbedit - Win32 ReleaseCLEAN" "Z2MP - Win32 ReleaseCLEAN" "tzedvmld - Win32 ReleaseCLEAN" "truegrid - Win32 ReleaseCLEAN" "tzvmledt - Win32 ReleaseCLEAN" "ZSEMail - Win32 ReleaseCLEAN" "JpegLib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\ZDr.obj"
	-@erase "$(INTDIR)\ZDr.res"
	-@erase "..\..\w\bin\ZDr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /EHsc /O2 /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ZDr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ZDr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ZDrApp.lib kzoengaa.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ZDr.pdb" /machine:I386 /out:"..\..\w\bin\ZDr.exe" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" 
LINK32_OBJS= \
	"$(INTDIR)\ZDr.obj" \
	"$(INTDIR)\ZDr.res" \
	"..\..\w\libr\TzAxCtl.lib" \
	"..\..\w\libr\TzCtl.lib" \
	"..\..\w\libr\ZdCtl.lib" \
	"..\..\w\libr\ZDrApp.lib" \
	"..\TZ\ax\_edit\Release\tbedit.lib" \
	"$(OUTDIR)\Z2MP.lib" \
	"..\..\W\TZ\Release\tzedvmld.lib" \
	"..\..\w\libz\tzvmledt.lib" \
	"$(OUTDIR)\ZSEMail.lib" \
	"..\..\w\libr\JpegLib.lib"

"..\..\w\bin\ZDr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\w\bin\ZDr.exe" "$(OUTDIR)\ZDr.bsc"

!ELSE 

ALL : "JpegLib - Win32 Debug" "ZSEMail - Win32 Debug" "tzvmledt - Win32 Debug" "truegrid - Win32 Debug" "tzedvmld - Win32 Debug" "Z2MP - Win32 Debug" "tbedit - Win32 Debug" "ZDrApp - Win32 Debug" "ZdCtl - Win32 Debug" "TzCtl - Win32 Debug" "TzAxCtl - Win32 Debug" "..\..\w\bin\ZDr.exe" "$(OUTDIR)\ZDr.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"TzAxCtl - Win32 DebugCLEAN" "TzCtl - Win32 DebugCLEAN" "ZdCtl - Win32 DebugCLEAN" "ZDrApp - Win32 DebugCLEAN" "tbedit - Win32 DebugCLEAN" "Z2MP - Win32 DebugCLEAN" "tzedvmld - Win32 DebugCLEAN" "truegrid - Win32 DebugCLEAN" "tzvmledt - Win32 DebugCLEAN" "ZSEMail - Win32 DebugCLEAN" "JpegLib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\ZDr.obj"
	-@erase "$(INTDIR)\ZDr.res"
	-@erase "$(INTDIR)\ZDr.sbr"
	-@erase "$(OUTDIR)\ZDr.bsc"
	-@erase "$(OUTDIR)\ZDr.pdb"
	-@erase "..\..\w\bin\ZDr.exe"
	-@erase "..\..\w\bin\ZDr.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /EHsc /ZI /Od /I "." /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ZDr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ZDr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ZDr.sbr"

"$(OUTDIR)\ZDr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ZDrApp.lib kzoengaa.lib kzrpsrco.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ZDr.pdb" /debug /machine:I386 /out:"..\..\w\bin\ZDr.exe" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" 
LINK32_OBJS= \
	"$(INTDIR)\ZDr.obj" \
	"$(INTDIR)\ZDr.res" \
	"..\..\w\libr\TzAxCtl.lib" \
	"..\..\w\libr\TzCtl.lib" \
	"..\..\w\libr\ZdCtl.lib" \
	"..\..\w\libr\ZDrApp.lib" \
	"..\TZ\ax\_edit\Debug\tbedit.lib" \
	"..\..\w\libr\Z2MP.lib" \
	"..\..\W\TZ\Debug\tzedvmld.lib" \
	"..\..\w\libz\tzvmledt.lib" \
	"..\..\w\libr\ZSEMail.lib" \
	"..\..\w\libr\JpegLib.lib"

"..\..\w\bin\ZDr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ZDr.dep")
!INCLUDE "ZDr.dep"
!ELSE 
!MESSAGE Warning: cannot find "ZDr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ZDr - Win32 Release" || "$(CFG)" == "ZDr - Win32 Debug"
SOURCE=.\ZDr.cpp

!IF  "$(CFG)" == "ZDr - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /EHsc /O2 /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ZDr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /EHsc /ZI /Od /I "." /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ZDr.obj"	"$(INTDIR)\ZDr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ZDr.rc

"$(INTDIR)\ZDr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "ZDr - Win32 Release"

"TzAxCtl - Win32 Release" : 
   cd "\10d\a\TZ\ax\tzaxctl"
   $(MAKE) /$(MAKEFLAGS) /F .\TzAxCtl.mak CFG="TzAxCtl - Win32 Release" 
   cd "..\..\..\zdr"

"TzAxCtl - Win32 ReleaseCLEAN" : 
   cd "\10d\a\TZ\ax\tzaxctl"
   $(MAKE) /$(MAKEFLAGS) /F .\TzAxCtl.mak CFG="TzAxCtl - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\zdr"

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"TzAxCtl - Win32 Debug" : 
   cd "\10d\a\TZ\ax\tzaxctl"
   $(MAKE) /$(MAKEFLAGS) /F .\TzAxCtl.mak CFG="TzAxCtl - Win32 Debug" 
   cd "..\..\..\zdr"

"TzAxCtl - Win32 DebugCLEAN" : 
   cd "\10d\a\TZ\ax\tzaxctl"
   $(MAKE) /$(MAKEFLAGS) /F .\TzAxCtl.mak CFG="TzAxCtl - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\zdr"

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"TzCtl - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\TzCtl.mak CFG="TzCtl - Win32 Release" 
   cd "."

"TzCtl - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\TzCtl.mak CFG="TzCtl - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"TzCtl - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\TzCtl.mak CFG="TzCtl - Win32 Debug" 
   cd "."

"TzCtl - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\TzCtl.mak CFG="TzCtl - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"ZdCtl - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZdCtl.mak CFG="ZdCtl - Win32 Release" 
   cd "."

"ZdCtl - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZdCtl.mak CFG="ZdCtl - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"ZdCtl - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZdCtl.mak CFG="ZdCtl - Win32 Debug" 
   cd "."

"ZdCtl - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZdCtl.mak CFG="ZdCtl - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"ZDrApp - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Release" 
   cd "."

"ZDrApp - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"ZDrApp - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Debug" 
   cd "."

"ZDrApp - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZDrApp.mak CFG="ZDrApp - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"tbedit - Win32 Release" : 
   cd "\10d\a\TZ\ax\_edit"
   $(MAKE) /$(MAKEFLAGS) /F .\tbedit.mak CFG="tbedit - Win32 Release" 
   cd "..\..\..\zdr"

"tbedit - Win32 ReleaseCLEAN" : 
   cd "\10d\a\TZ\ax\_edit"
   $(MAKE) /$(MAKEFLAGS) /F .\tbedit.mak CFG="tbedit - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\zdr"

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"tbedit - Win32 Debug" : 
   cd "\10d\a\TZ\ax\_edit"
   $(MAKE) /$(MAKEFLAGS) /F .\tbedit.mak CFG="tbedit - Win32 Debug" 
   cd "..\..\..\zdr"

"tbedit - Win32 DebugCLEAN" : 
   cd "\10d\a\TZ\ax\_edit"
   $(MAKE) /$(MAKEFLAGS) /F .\tbedit.mak CFG="tbedit - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\zdr"

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"Z2MP - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\Z2MP.mak CFG="Z2MP - Win32 Release" 
   cd "."

"Z2MP - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\Z2MP.mak CFG="Z2MP - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"Z2MP - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\Z2MP.mak CFG="Z2MP - Win32 Debug" 
   cd "."

"Z2MP - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\Z2MP.mak CFG="Z2MP - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"tzedvmld - Win32 Release" : 
   cd "\10d\W\TZ"
   $(MAKE) /$(MAKEFLAGS) /F .\tzedvmld.mak CFG="tzedvmld - Win32 Release" 
   cd "..\..\a\zdr"

"tzedvmld - Win32 ReleaseCLEAN" : 
   cd "\10d\W\TZ"
   $(MAKE) /$(MAKEFLAGS) /F .\tzedvmld.mak CFG="tzedvmld - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\a\zdr"

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"tzedvmld - Win32 Debug" : 
   cd "\10d\W\TZ"
   $(MAKE) /$(MAKEFLAGS) /F .\tzedvmld.mak CFG="tzedvmld - Win32 Debug" 
   cd "..\..\a\zdr"

"tzedvmld - Win32 DebugCLEAN" : 
   cd "\10d\W\TZ"
   $(MAKE) /$(MAKEFLAGS) /F .\tzedvmld.mak CFG="tzedvmld - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\a\zdr"

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"truegrid - Win32 Release" : 
   cd "\10d\a\TZ\ax\TrueGrid"
   $(MAKE) /$(MAKEFLAGS) /F .\truegrid.mak CFG="truegrid - Win32 Release" 
   cd "..\..\..\zdr"

"truegrid - Win32 ReleaseCLEAN" : 
   cd "\10d\a\TZ\ax\TrueGrid"
   $(MAKE) /$(MAKEFLAGS) /F .\truegrid.mak CFG="truegrid - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\zdr"

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"truegrid - Win32 Debug" : 
   cd "\10d\a\TZ\ax\TrueGrid"
   $(MAKE) /$(MAKEFLAGS) /F .\truegrid.mak CFG="truegrid - Win32 Debug" 
   cd "..\..\..\zdr"

"truegrid - Win32 DebugCLEAN" : 
   cd "\10d\a\TZ\ax\TrueGrid"
   $(MAKE) /$(MAKEFLAGS) /F .\truegrid.mak CFG="truegrid - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\zdr"

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"tzvmledt - Win32 Release" : 
   cd "\10d\a\TZ\ax\tzvmledt"
   $(MAKE) /$(MAKEFLAGS) /F .\tzvmledt.mak CFG="tzvmledt - Win32 Release" 
   cd "..\..\..\zdr"

"tzvmledt - Win32 ReleaseCLEAN" : 
   cd "\10d\a\TZ\ax\tzvmledt"
   $(MAKE) /$(MAKEFLAGS) /F .\tzvmledt.mak CFG="tzvmledt - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\zdr"

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"tzvmledt - Win32 Debug" : 
   cd "\10d\a\TZ\ax\tzvmledt"
   $(MAKE) /$(MAKEFLAGS) /F .\tzvmledt.mak CFG="tzvmledt - Win32 Debug" 
   cd "..\..\..\zdr"

"tzvmledt - Win32 DebugCLEAN" : 
   cd "\10d\a\TZ\ax\tzvmledt"
   $(MAKE) /$(MAKEFLAGS) /F .\tzvmledt.mak CFG="tzvmledt - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\zdr"

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"ZSEMail - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZSEMail.mak CFG="ZSEMail - Win32 Release" 
   cd "."

"ZSEMail - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZSEMail.mak CFG="ZSEMail - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

"ZSEMail - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZSEMail.mak CFG="ZSEMail - Win32 Debug" 
   cd "."

"ZSEMail - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\ZSEMail.mak CFG="ZSEMail - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "ZDr - Win32 Release"

"JpegLib - Win32 Release" : 
   cd ".\JPegLib"
   $(MAKE) /$(MAKEFLAGS) /F .\JPegLib.mak CFG="JpegLib - Win32 Release" 
   cd ".."

"JpegLib - Win32 ReleaseCLEAN" : 
   cd ".\JPegLib"
   $(MAKE) /$(MAKEFLAGS) /F .\JPegLib.mak CFG="JpegLib - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "ZDr - Win32 Debug"

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

