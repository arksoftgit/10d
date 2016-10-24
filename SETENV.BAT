@echo off
if '%1' == 'DBG' GoTo Debug
if '%1' == 'dbg' GoTo Debug
GoTo StartBat

:Debug
echo on
shift

:StartBat

where /q nmake
if errorlevel 1 (
  echo nmake not found.  Run this in Developer Command prompt or run vcvarsall.bat.
  echo ^(Look in C:\Program Files ^(x86^)\Microsoft Visual Studio 14.0\^).
  exit /b 1
)

if "%kzd%" == "" set kzd=c
if "%kzv%" == "" set kzv=10d
set qpath=%kzd%:\%kzv%\utils\bat
set buildos=win32
set rootdir=%kzd%:\%kzv%
set qbat=%rootdir%\utils\bat
set qbin=%rootdir%\utils\bin

if "%zeidon%" == "" set ZEIDON=%rootdir%\ZApp32

where /q cds.bat
if %errorlevel% == 0 goto :SkipUtilsPath
echo Setting up path
set PATH=%PATH%;%rootdir%\utils\bat;%rootdir%\utils\bin;%rootdir%\w\bin
echo PATH="%path%"

:SkipUtilsPath

if "%kztt%" == "" set kztt=a
if "%kzt%" == "" set kzt=w

set KZL=l
set KZLB=d
set KZP=w
set KZS=zdr
set KZTT=a
set KZVP=%kzv%

:: Compiler environment vars.  If kzoengaa.h can be found in the include dirs then
:: we'll assume we've set them all up.
where /q $include:kzoengaa.h
if %errorlevel% == 0 goto :SkipCompilerEnvVars
set INCLUDE=%include%;%rootdir%\a\incr;%rootdir%\w\incr;%rootdir%\a\incz;%rootdir%\w\incz
set LIB=%lib%;%rootdir%\w\libr;%rootdir%\w\libz
echo INCLUDE=%include%
:SkipCompilerEnvVars

