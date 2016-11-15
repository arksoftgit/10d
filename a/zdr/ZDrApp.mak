# Microsoft Developer Studio Generated NMAKE File, Based on ZDrApp.dsp
!IF "$(CFG)" == ""
CFG=ZDrApp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ZDrApp - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ZDrApp - Win32 Release" && "$(CFG)" != "ZDrApp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZDrApp.mak" CFG="ZDrApp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZDrApp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ZDrApp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ZDrApp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\w\bin\ZDrApp.dll"

!ELSE 

ALL : "JpegLib - Win32 Release" "..\..\w\bin\ZDrApp.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"JpegLib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\ZDrAct.obj"
	-@erase "$(INTDIR)\ZDrApp.obj"
	-@erase "$(INTDIR)\ZDrApp.pch"
	-@erase "$(INTDIR)\ZDrApp.res"
	-@erase "$(INTDIR)\ZDrAxLst.obj"
	-@erase "$(INTDIR)\ZDRCCDLG.obj"
	-@erase "$(INTDIR)\ZDrCmdLN.obj"
	-@erase "$(INTDIR)\ZDRCMPRS.obj"
	-@erase "$(INTDIR)\ZDrComm.obj"
	-@erase "$(INTDIR)\ZDrCoolB.obj"
	-@erase "$(INTDIR)\ZDrCtl.obj"
	-@erase "$(INTDIR)\ZDrDebug.obj"
	-@erase "$(INTDIR)\ZDrDIB.obj"
	-@erase "$(INTDIR)\ZDrDlgA.obj"
	-@erase "$(INTDIR)\ZDrDlgC.obj"
	-@erase "$(INTDIR)\ZDrDlgM.obj"
	-@erase "$(INTDIR)\ZDrDlgO.obj"
	-@erase "$(INTDIR)\ZDrDlgP.obj"
	-@erase "$(INTDIR)\ZDrDlgW.obj"
	-@erase "$(INTDIR)\ZDrDoc.obj"
	-@erase "$(INTDIR)\ZDrFlatB.obj"
	-@erase "$(INTDIR)\ZDrFont.obj"
	-@erase "$(INTDIR)\ZDrFrame.obj"
	-@erase "$(INTDIR)\ZDrMapAc.obj"
	-@erase "$(INTDIR)\ZDrMenu.obj"
	-@erase "$(INTDIR)\ZDrMisc.obj"
	-@erase "$(INTDIR)\ZDrMsgHK.obj"
	-@erase "$(INTDIR)\ZDrMsgQ.obj"
	-@erase "$(INTDIR)\ZDrOle.obj"
	-@erase "$(INTDIR)\ZDrOpt.obj"
	-@erase "$(INTDIR)\ZDrPalHK.obj"
	-@erase "$(INTDIR)\ZDrParse.obj"
	-@erase "$(INTDIR)\ZDrPrint.obj"
	-@erase "$(INTDIR)\ZDrPrtC.obj"
	-@erase "$(INTDIR)\ZDrSTask.obj"
	-@erase "$(INTDIR)\ZDrTask.obj"
	-@erase "$(INTDIR)\ZDrTwain.obj"
	-@erase "$(INTDIR)\ZDrUtil.obj"
	-@erase "$(INTDIR)\ZDrVCtrl.obj"
	-@erase "$(INTDIR)\ZDrView.obj"
	-@erase "$(INTDIR)\ZDrVStr.obj"
	-@erase "..\..\w\bin\ZDrApp.dll"
	-@erase "..\..\w\libr\ZDrApp.exp"
	-@erase "..\..\w\libr\ZDrApp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo  /W3 /EHsc /O2 /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "NDEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS"  /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /Fp"$(INTDIR)\ZDrApp.pch" /Yu"ZDr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ZDrApp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ZDrApp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=vfw32.lib kzoengaa.lib Activeds.lib Adsiid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:".\Debug\ZDrApp.pdb" /machine:I386 /def:".\ZDrApp.def" /out:"..\..\w\bin\ZDrApp.dll" /implib:"..\..\w\libr\ZDrApp.lib" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" 
DEF_FILE= \
	".\ZDrApp.def"
LINK32_OBJS= \
	"$(INTDIR)\ZDrAct.obj" \
	"$(INTDIR)\ZDrApp.obj" \
	"$(INTDIR)\ZDrAxLst.obj" \
	"$(INTDIR)\ZDRCCDLG.obj" \
	"$(INTDIR)\ZDrCmdLN.obj" \
	"$(INTDIR)\ZDRCMPRS.obj" \
	"$(INTDIR)\ZDrComm.obj" \
	"$(INTDIR)\ZDrCoolB.obj" \
	"$(INTDIR)\ZDrCtl.obj" \
	"$(INTDIR)\ZDrDebug.obj" \
	"$(INTDIR)\ZDrDIB.obj" \
	"$(INTDIR)\ZDrDlgA.obj" \
	"$(INTDIR)\ZDrDlgC.obj" \
	"$(INTDIR)\ZDrDlgM.obj" \
	"$(INTDIR)\ZDrDlgO.obj" \
	"$(INTDIR)\ZDrDlgP.obj" \
	"$(INTDIR)\ZDrDlgW.obj" \
	"$(INTDIR)\ZDrDoc.obj" \
	"$(INTDIR)\ZDrFlatB.obj" \
	"$(INTDIR)\ZDrFont.obj" \
	"$(INTDIR)\ZDrFrame.obj" \
	"$(INTDIR)\ZDrMapAc.obj" \
	"$(INTDIR)\ZDrMenu.obj" \
	"$(INTDIR)\ZDrMisc.obj" \
	"$(INTDIR)\ZDrMsgHK.obj" \
	"$(INTDIR)\ZDrMsgQ.obj" \
	"$(INTDIR)\ZDrOle.obj" \
	"$(INTDIR)\ZDrOpt.obj" \
	"$(INTDIR)\ZDrPalHK.obj" \
	"$(INTDIR)\ZDrParse.obj" \
	"$(INTDIR)\ZDrPrint.obj" \
	"$(INTDIR)\ZDrPrtC.obj" \
	"$(INTDIR)\ZDrSTask.obj" \
	"$(INTDIR)\ZDrTask.obj" \
	"$(INTDIR)\ZDrTwain.obj" \
	"$(INTDIR)\ZDrUtil.obj" \
	"$(INTDIR)\ZDrVCtrl.obj" \
	"$(INTDIR)\ZDrView.obj" \
	"$(INTDIR)\ZDrVStr.obj" \
	"$(INTDIR)\ZDrApp.res" \
	"..\..\w\libr\JpegLib.lib"

"..\..\w\bin\ZDrApp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\w\bin\ZDrApp.dll" "$(OUTDIR)\ZDr.bsc"

!ELSE 

ALL : "JpegLib - Win32 Debug" "..\..\w\bin\ZDrApp.dll" "$(OUTDIR)\ZDr.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"JpegLib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\ZDrAct.obj"
	-@erase "$(INTDIR)\ZDrAct.sbr"
	-@erase "$(INTDIR)\ZDrApp.obj"
	-@erase "$(INTDIR)\ZDrApp.pch"
	-@erase "$(INTDIR)\ZDrApp.res"
	-@erase "$(INTDIR)\ZDrApp.sbr"
	-@erase "$(INTDIR)\ZDrAxLst.obj"
	-@erase "$(INTDIR)\ZDrAxLst.sbr"
	-@erase "$(INTDIR)\ZDRCCDLG.obj"
	-@erase "$(INTDIR)\ZDRCCDLG.SBR"
	-@erase "$(INTDIR)\ZDrCmdLN.obj"
	-@erase "$(INTDIR)\ZDrCmdLN.sbr"
	-@erase "$(INTDIR)\ZDRCMPRS.obj"
	-@erase "$(INTDIR)\ZDRCMPRS.SBR"
	-@erase "$(INTDIR)\ZDrComm.obj"
	-@erase "$(INTDIR)\ZDrComm.sbr"
	-@erase "$(INTDIR)\ZDrCoolB.obj"
	-@erase "$(INTDIR)\ZDrCoolB.sbr"
	-@erase "$(INTDIR)\ZDrCtl.obj"
	-@erase "$(INTDIR)\ZDrCtl.sbr"
	-@erase "$(INTDIR)\ZDrDebug.obj"
	-@erase "$(INTDIR)\ZDrDebug.sbr"
	-@erase "$(INTDIR)\ZDrDIB.obj"
	-@erase "$(INTDIR)\ZDrDIB.sbr"
	-@erase "$(INTDIR)\ZDrDlgA.obj"
	-@erase "$(INTDIR)\ZDrDlgA.sbr"
	-@erase "$(INTDIR)\ZDrDlgC.obj"
	-@erase "$(INTDIR)\ZDrDlgC.sbr"
	-@erase "$(INTDIR)\ZDrDlgM.obj"
	-@erase "$(INTDIR)\ZDrDlgM.sbr"
	-@erase "$(INTDIR)\ZDrDlgO.obj"
	-@erase "$(INTDIR)\ZDrDlgO.sbr"
	-@erase "$(INTDIR)\ZDrDlgP.obj"
	-@erase "$(INTDIR)\ZDrDlgP.sbr"
	-@erase "$(INTDIR)\ZDrDlgW.obj"
	-@erase "$(INTDIR)\ZDrDlgW.sbr"
	-@erase "$(INTDIR)\ZDrDoc.obj"
	-@erase "$(INTDIR)\ZDrDoc.sbr"
	-@erase "$(INTDIR)\ZDrFlatB.obj"
	-@erase "$(INTDIR)\ZDrFlatB.sbr"
	-@erase "$(INTDIR)\ZDrFont.obj"
	-@erase "$(INTDIR)\ZDrFont.sbr"
	-@erase "$(INTDIR)\ZDrFrame.obj"
	-@erase "$(INTDIR)\ZDrFrame.sbr"
	-@erase "$(INTDIR)\ZDrMapAc.obj"
	-@erase "$(INTDIR)\ZDrMapAc.sbr"
	-@erase "$(INTDIR)\ZDrMenu.obj"
	-@erase "$(INTDIR)\ZDrMenu.sbr"
	-@erase "$(INTDIR)\ZDrMisc.obj"
	-@erase "$(INTDIR)\ZDrMisc.sbr"
	-@erase "$(INTDIR)\ZDrMsgHK.obj"
	-@erase "$(INTDIR)\ZDrMsgHK.sbr"
	-@erase "$(INTDIR)\ZDrMsgQ.obj"
	-@erase "$(INTDIR)\ZDrMsgQ.sbr"
	-@erase "$(INTDIR)\ZDrOle.obj"
	-@erase "$(INTDIR)\ZDrOle.sbr"
	-@erase "$(INTDIR)\ZDrOpt.obj"
	-@erase "$(INTDIR)\ZDrOpt.sbr"
	-@erase "$(INTDIR)\ZDrPalHK.obj"
	-@erase "$(INTDIR)\ZDrPalHK.sbr"
	-@erase "$(INTDIR)\ZDrParse.obj"
	-@erase "$(INTDIR)\ZDrParse.sbr"
	-@erase "$(INTDIR)\ZDrPrint.obj"
	-@erase "$(INTDIR)\ZDrPrint.sbr"
	-@erase "$(INTDIR)\ZDrPrtC.obj"
	-@erase "$(INTDIR)\ZDrPrtC.sbr"
	-@erase "$(INTDIR)\ZDrSTask.obj"
	-@erase "$(INTDIR)\ZDrSTask.sbr"
	-@erase "$(INTDIR)\ZDrTask.obj"
	-@erase "$(INTDIR)\ZDrTask.sbr"
	-@erase "$(INTDIR)\ZDrTwain.obj"
	-@erase "$(INTDIR)\ZDrTwain.sbr"
	-@erase "$(INTDIR)\ZDrUtil.obj"
	-@erase "$(INTDIR)\ZDrUtil.sbr"
	-@erase "$(INTDIR)\ZDrVCtrl.obj"
	-@erase "$(INTDIR)\ZDrVCtrl.sbr"
	-@erase "$(INTDIR)\ZDrView.obj"
	-@erase "$(INTDIR)\ZDrView.sbr"
	-@erase "$(INTDIR)\ZDrVStr.obj"
	-@erase "$(INTDIR)\ZDrVStr.sbr"
	-@erase "$(OUTDIR)\ZDr.bsc"
	-@erase "$(OUTDIR)\ZDrApp.pdb"
	-@erase "..\..\w\bin\ZDrApp.dll"
	-@erase "..\..\w\bin\ZDrApp.ilk"
	-@erase "..\..\w\libr\ZDrApp.exp"
	-@erase "..\..\w\libr\ZDrApp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo  /W3 /WX /Gm /EHsc /ZI /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "_DEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ZDrApp.pch" /Yu"ZDr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ZDrApp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ZDr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ZDrAct.sbr" \
	"$(INTDIR)\ZDrApp.sbr" \
	"$(INTDIR)\ZDrAxLst.sbr" \
	"$(INTDIR)\ZDRCCDLG.SBR" \
	"$(INTDIR)\ZDrCmdLN.sbr" \
	"$(INTDIR)\ZDRCMPRS.SBR" \
	"$(INTDIR)\ZDrComm.sbr" \
	"$(INTDIR)\ZDrCoolB.sbr" \
	"$(INTDIR)\ZDrCtl.sbr" \
	"$(INTDIR)\ZDrDebug.sbr" \
	"$(INTDIR)\ZDrDIB.sbr" \
	"$(INTDIR)\ZDrDlgA.sbr" \
	"$(INTDIR)\ZDrDlgC.sbr" \
	"$(INTDIR)\ZDrDlgM.sbr" \
	"$(INTDIR)\ZDrDlgO.sbr" \
	"$(INTDIR)\ZDrDlgP.sbr" \
	"$(INTDIR)\ZDrDlgW.sbr" \
	"$(INTDIR)\ZDrDoc.sbr" \
	"$(INTDIR)\ZDrFlatB.sbr" \
	"$(INTDIR)\ZDrFont.sbr" \
	"$(INTDIR)\ZDrFrame.sbr" \
	"$(INTDIR)\ZDrMapAc.sbr" \
	"$(INTDIR)\ZDrMenu.sbr" \
	"$(INTDIR)\ZDrMisc.sbr" \
	"$(INTDIR)\ZDrMsgHK.sbr" \
	"$(INTDIR)\ZDrMsgQ.sbr" \
	"$(INTDIR)\ZDrOle.sbr" \
	"$(INTDIR)\ZDrOpt.sbr" \
	"$(INTDIR)\ZDrPalHK.sbr" \
	"$(INTDIR)\ZDrParse.sbr" \
	"$(INTDIR)\ZDrPrint.sbr" \
	"$(INTDIR)\ZDrPrtC.sbr" \
	"$(INTDIR)\ZDrSTask.sbr" \
	"$(INTDIR)\ZDrTask.sbr" \
	"$(INTDIR)\ZDrTwain.sbr" \
	"$(INTDIR)\ZDrUtil.sbr" \
	"$(INTDIR)\ZDrVCtrl.sbr" \
	"$(INTDIR)\ZDrView.sbr" \
	"$(INTDIR)\ZDrVStr.sbr"

"$(OUTDIR)\ZDr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=vfw32.lib kzoengaa.lib Activeds.lib Adsiid.lib jpeglib.lib tapi32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ZDrApp.pdb" /debug /machine:I386 /def:".\ZDrApp.def" /out:"..\..\w\bin\ZDrApp.dll" /implib:"..\..\w\libr\ZDrApp.lib" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" 
DEF_FILE= \
	".\ZDrApp.def"
LINK32_OBJS= \
	"$(INTDIR)\ZDrAct.obj" \
	"$(INTDIR)\ZDrApp.obj" \
	"$(INTDIR)\ZDrAxLst.obj" \
	"$(INTDIR)\ZDRCCDLG.obj" \
	"$(INTDIR)\ZDrCmdLN.obj" \
	"$(INTDIR)\ZDRCMPRS.obj" \
	"$(INTDIR)\ZDrComm.obj" \
	"$(INTDIR)\ZDrCoolB.obj" \
	"$(INTDIR)\ZDrCtl.obj" \
	"$(INTDIR)\ZDrDebug.obj" \
	"$(INTDIR)\ZDrDIB.obj" \
	"$(INTDIR)\ZDrDlgA.obj" \
	"$(INTDIR)\ZDrDlgC.obj" \
	"$(INTDIR)\ZDrDlgM.obj" \
	"$(INTDIR)\ZDrDlgO.obj" \
	"$(INTDIR)\ZDrDlgP.obj" \
	"$(INTDIR)\ZDrDlgW.obj" \
	"$(INTDIR)\ZDrDoc.obj" \
	"$(INTDIR)\ZDrFlatB.obj" \
	"$(INTDIR)\ZDrFont.obj" \
	"$(INTDIR)\ZDrFrame.obj" \
	"$(INTDIR)\ZDrMapAc.obj" \
	"$(INTDIR)\ZDrMenu.obj" \
	"$(INTDIR)\ZDrMisc.obj" \
	"$(INTDIR)\ZDrMsgHK.obj" \
	"$(INTDIR)\ZDrMsgQ.obj" \
	"$(INTDIR)\ZDrOle.obj" \
	"$(INTDIR)\ZDrOpt.obj" \
	"$(INTDIR)\ZDrPalHK.obj" \
	"$(INTDIR)\ZDrParse.obj" \
	"$(INTDIR)\ZDrPrint.obj" \
	"$(INTDIR)\ZDrPrtC.obj" \
	"$(INTDIR)\ZDrSTask.obj" \
	"$(INTDIR)\ZDrTask.obj" \
	"$(INTDIR)\ZDrTwain.obj" \
	"$(INTDIR)\ZDrUtil.obj" \
	"$(INTDIR)\ZDrVCtrl.obj" \
	"$(INTDIR)\ZDrView.obj" \
	"$(INTDIR)\ZDrVStr.obj" \
	"$(INTDIR)\ZDrApp.res" \
	"..\..\w\libr\JpegLib.lib"

"..\..\w\bin\ZDrApp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ZDrApp.dep")
!INCLUDE "ZDrApp.dep"
!ELSE 
!MESSAGE Warning: cannot find "ZDrApp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ZDrApp - Win32 Release" || "$(CFG)" == "ZDrApp - Win32 Debug"
SOURCE=.\ZDrAct.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrAct.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrAct.obj"	"$(INTDIR)\ZDrAct.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrApp.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"

CPP_SWITCHES=/nologo  /W3 /EHsc /O2 /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "NDEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS"  /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /Fp"$(INTDIR)\ZDrApp.pch" /Yc"ZDr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ZDrApp.obj"	"$(INTDIR)\ZDrApp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"

CPP_SWITCHES=/nologo  /W3 /WX /Gm /EHsc /ZI /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /D "_DEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS"  /D "__WIN32__" /D "QUINSOFT" /D "_NOANCHOR" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ZDrApp.pch" /Yc"ZDr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ZDrApp.obj"	"$(INTDIR)\ZDrApp.sbr"	"$(INTDIR)\ZDrApp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ZDrApp.rc

"$(INTDIR)\ZDrApp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ZDrAxLst.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrAxLst.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrAxLst.obj"	"$(INTDIR)\ZDrAxLst.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDRCCDLG.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDRCCDLG.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDRCCDLG.obj"	"$(INTDIR)\ZDRCCDLG.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrCmdLN.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrCmdLN.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrCmdLN.obj"	"$(INTDIR)\ZDrCmdLN.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDRCMPRS.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDRCMPRS.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDRCMPRS.obj"	"$(INTDIR)\ZDRCMPRS.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrComm.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrComm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrComm.obj"	"$(INTDIR)\ZDrComm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrCoolB.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrCoolB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrCoolB.obj"	"$(INTDIR)\ZDrCoolB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrCtl.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrCtl.obj"	"$(INTDIR)\ZDrCtl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDebug.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDebug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDebug.obj"	"$(INTDIR)\ZDrDebug.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDIB.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDIB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDIB.obj"	"$(INTDIR)\ZDrDIB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDlgA.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDlgA.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDlgA.obj"	"$(INTDIR)\ZDrDlgA.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDlgC.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDlgC.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDlgC.obj"	"$(INTDIR)\ZDrDlgC.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDlgM.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDlgM.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDlgM.obj"	"$(INTDIR)\ZDrDlgM.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDlgO.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDlgO.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDlgO.obj"	"$(INTDIR)\ZDrDlgO.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDlgP.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDlgP.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDlgP.obj"	"$(INTDIR)\ZDrDlgP.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDlgW.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDlgW.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDlgW.obj"	"$(INTDIR)\ZDrDlgW.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrDoc.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrDoc.obj"	"$(INTDIR)\ZDrDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrFlatB.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrFlatB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrFlatB.obj"	"$(INTDIR)\ZDrFlatB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrFont.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrFont.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrFont.obj"	"$(INTDIR)\ZDrFont.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrFrame.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrFrame.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrFrame.obj"	"$(INTDIR)\ZDrFrame.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrMapAc.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrMapAc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrMapAc.obj"	"$(INTDIR)\ZDrMapAc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrMenu.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrMenu.obj"	"$(INTDIR)\ZDrMenu.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrMisc.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrMisc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrMisc.obj"	"$(INTDIR)\ZDrMisc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrMsgHK.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrMsgHK.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrMsgHK.obj"	"$(INTDIR)\ZDrMsgHK.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrMsgQ.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrMsgQ.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrMsgQ.obj"	"$(INTDIR)\ZDrMsgQ.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrOle.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrOle.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrOle.obj"	"$(INTDIR)\ZDrOle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrOpt.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrOpt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrOpt.obj"	"$(INTDIR)\ZDrOpt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrPalHK.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrPalHK.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrPalHK.obj"	"$(INTDIR)\ZDrPalHK.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrParse.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrParse.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrParse.obj"	"$(INTDIR)\ZDrParse.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrPrint.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrPrint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrPrint.obj"	"$(INTDIR)\ZDrPrint.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrPrtC.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrPrtC.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrPrtC.obj"	"$(INTDIR)\ZDrPrtC.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrSTask.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrSTask.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrSTask.obj"	"$(INTDIR)\ZDrSTask.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrTask.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrTask.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrTask.obj"	"$(INTDIR)\ZDrTask.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrTwain.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrTwain.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrTwain.obj"	"$(INTDIR)\ZDrTwain.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrUtil.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrUtil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrUtil.obj"	"$(INTDIR)\ZDrUtil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrVCtrl.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrVCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrVCtrl.obj"	"$(INTDIR)\ZDrVCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrView.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrView.obj"	"$(INTDIR)\ZDrView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

SOURCE=.\ZDrVStr.cpp

!IF  "$(CFG)" == "ZDrApp - Win32 Release"


"$(INTDIR)\ZDrVStr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"


"$(INTDIR)\ZDrVStr.obj"	"$(INTDIR)\ZDrVStr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ZDrApp.pch"


!ENDIF 

!IF  "$(CFG)" == "ZDrApp - Win32 Release"

"JpegLib - Win32 Release" : 
   cd ".\JPegLib"
   $(MAKE) /$(MAKEFLAGS) /F .\JPegLib.mak CFG="JpegLib - Win32 Release" 
   cd ".."

"JpegLib - Win32 ReleaseCLEAN" : 
   cd ".\JPegLib"
   $(MAKE) /$(MAKEFLAGS) /F .\JPegLib.mak CFG="JpegLib - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "ZDrApp - Win32 Debug"

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

