# Microsoft Developer Studio Project File - Name="tzedvmld" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=tzedvmld - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "tzedvmld.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "tzedvmld.mak" CFG="tzedvmld - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "tzedvmld - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tzedvmld - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "tzedvmld"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tzedvmld - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "tzedvmld_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /I "$(KZD):\$(KZV)\a\zdr" /I "..\tzaxctl" /D "_RELEASE" /D "_WINDLL" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "_USE_DATASET_" /FD /TP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tzvmledt.lib ZdCtl.lib ZdrApp.lib kzoengaa.lib tzctl.lib tzlodopr.lib tzvmpopr.lib tzvmlopr.lib tzvmlip.lib /nologo /dll /incremental:yes /debug /machine:I386 /out:"..\..\w\bin\tzedvmld.dll" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" /libpath:".\release"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "tzedvmld - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "tzedvmld___Win32_Debug"
# PROP BASE Intermediate_Dir "tzedvmld___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /I "$(KZD):\$(KZV)\a\zdr" /I "..\tzaxctl" /D "_RELEASE" /D "_WINDLL" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WIN32__" /D "_USE_DATASET_" /FD /TP /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "$(KZD):\$(KZV)\w\incz" /I "$(KZD):\$(KZV)\w\incr" /I "$(KZD):\$(KZV)\a\incz" /I "$(KZD):\$(KZV)\a\incr" /I "$(KZD):\$(KZV)\a\zdr" /I "..\tzaxctl" /D "_DEBUG" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "__WIN32__" /D "_USE_DATASET_" /D "_NOANCHOR" /FR /FD /TP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZdCtl.lib ZdrApp.lib kzoengaa.lib truegrid.lib tzctl.lib tzlodopr.lib /nologo /dll /incremental:yes /debug /machine:I386 /out:"..\..\w\bin\tzedvmld.dll" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" /libpath:".\release"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 tzvmledt.lib ZdCtl.lib ZdrApp.lib kzoengaa.lib tzctl.lib tzlodopr.lib tzvmpopr.lib tzvmlopr.lib /nologo /dll /incremental:yes /debug /machine:I386 /def:"..\..\w\tz\tzedvmld.def" /out:"..\..\w\bin\tzedvmld.dll" /libpath:"$(KZD):\$(KZV)\w\libz" /libpath:"$(KZD):\$(KZV)\w\libr" /libpath:".\release"
# SUBTRACT LINK32 /pdb:none

!ENDIF

# Begin Target

# Name "tzedvmld - Win32 Release"
# Name "tzedvmld - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\a\tz\tzedvmld.C
# End Source File
# Begin Source File

SOURCE=..\..\w\tz\tzedvmld.def

!IF  "$(CFG)" == "tzedvmld - Win32 Release"

!ELSEIF  "$(CFG)" == "tzedvmld - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Zeidon"

# PROP Default_Filter "mak, PWD, LOD"
# Begin Source File

SOURCE=.\tzedvmld.mak
# End Source File
# Begin Source File

SOURCE=..\..\a\bin\sys\tzedvmld.PWD
# End Source File
# End Group
# End Target
# End Project
