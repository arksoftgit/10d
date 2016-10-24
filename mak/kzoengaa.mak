#
# Change Log
#
# 2001.10.23  TMV
#      changed calls of qpreproc to use $(kz_srcw)\some_def_file.def
#      this gives us the chance to call nmake from anywhere
#
# 2001.09.25  DGC
#      Changed CLEAN to delete a few more files.
#
# 2001.09.14  DGC
#     Fixed a bug introduced by the previous change.
#
# 2001.08.28  DGC
#     Made the compile of some modules conditional on $debug and $quinsoft.
#
# 2001.04.02  US
#     Removed the delayload of the kzoedbga.dll due to link warnings
#
# 2001.01.12  RG  Z2000
#     Build *.pdb-files in Release Version too
#
# 2000.12.27  DKS Z2000
#     Added KZOEDGBA
#
# 2000.05.12  RG  Z2000
#     Changed option -Oselg --> -Od
#
# 1998.08.10  DGC
#    Added MeterSec.* to core.
#    Added TimeStamp file (kzoetsaa.c) to core.
#
# 1998.10.15  DGC
#     Removed references to win95.
#
# 1998.10.15  DGC
#     Removed references to kzbootst.
#
# 1998.12.23  DGC
#     Added kzoeinco.h as a dependent of OS dependent objs.
#
# 1998.12.23  DGC
#     Pretty'd up the output.
#
# 1999.03.09  DGC
#     Had to add a .cpp option.
#

usecompiler=msc

!INCLUDE \$(KZV)\MAK\KZVERS.HNM
!INCLUDE \$(KZV)\MAK\KZCOMMON.HNM
kz_srca = $(kz_basea)\oe
kz_inc  = $(kz_basew)\inc

ALL : \
!if "$(BUILDOS)"=="win"
      $(kz_src)\kzoephdr.pch  \
      $(kz_src)\kzoephco.pch  \
!endif
      $(kz_lib)r\zdllinst.obj \
      $(kz_bin)\zdecimal.dll  \
      $(kz_bin)\kzoedbga.dll  \
      $(kz_bin)\kzoengaa.dll  \
      $(kz_bin)\kzoengwa.exe  \
      $(kz_bin)\zsimpdir.dll  \
      $(kz_bin)\kzschedt.exe  \
!if $(debug)
      $(kz_bin)\kzoeclnt.exe  \
!endif
      $(kz_bin)\zwinsock.dll

# The following used to be on all the .obj's used in creating kzoengaa.dll,
# they have been removed because even though a change to one of the
# header files has occurred, a system(oe) recompile isn't really neccessary.
# If you are unsure and want to do the system recompile for oe, you may do
# so by specifing (in order) SIG1 and ALL as targets when invoking make
# with this file.
#
#   {$(kz_inc_concat)}kzoengaa.hg   \
#   {$(kz_inc_concat)}KZOELTAA.hg   \
#   {$(kz_inc_concat)}KZOEP0AA.h   \
#   {$(kz_inc_concat)}kzoep1aa.h   \
#   {$(kz_inc_concat)}kzoengaa.h

!if "$(BUILDOS)"=="win"
pc_hdr = -Yukzoephdr.h -Fpkzoephco.pch
!endif

kz_srcw = $(kz_basew)\oe

# ============================================================
# ====================== kzoengaa.dll ========================
# ============================================================

# All the non OS-dependent core objs go here
core_obj = $(kz_obj)\kzoeapaa.obj \
           $(kz_obj)\kzoeataa.obj \
           $(kz_obj)\kzoecmaa.obj \
           $(kz_obj)\kzoedmaa.obj \
           $(kz_obj)\kzoeeiaa.obj \
           $(kz_obj)\kzoeeraa.obj \
           $(kz_obj)\kzoemiaa.obj \
           $(kz_obj)\kzoemmaa.obj \
           $(kz_obj)\kzoemqaa.obj \
           $(kz_obj)\kzoeneta.obj \
           $(kz_obj)\kzoeodaa.obj \
           $(kz_obj)\kzoeoiaa.obj \
           $(kz_obj)\kzoesoaa.obj \
           $(kz_obj)\kzoetmaa.obj \
           $(kz_obj)\kzoetraa.obj \
           $(kz_obj)\kzoeufaa.obj \
           $(kz_obj)\kzoevlaa.obj \
           $(kz_obj)\kzoevmaa.obj \
           $(kz_obj)\kzoexmla.obj \
# DGC 11/2/95  Temporarily added for NLS support....
           $(kz_obj)\kzwdlgxo.obj

core_cpp_obj = $(kz_obj)\kzoedeca.obj

# All the OS-dependent core objs go here.
core_objo = $(kz_obj)\kzoesyaa.obj

!if "$(BUILDOS)"!="win"
core_objo = $(core_objo) $(kz_obj)\metersec.obj
!endif

# All the OS objs go here. (for example dll_init)
!if "$(usecompiler)"=="msc"
os_obj =
!else
os_obj = $(kz_obj_gbl)\alloc.obj \
         $(kz_obj_gbl)\dllinit.obj
!endif

all_core_objs = $(core_obj) $(core_cpp_obj) $(core_objo) $(os_obj)

$(kz_src)\kzoephdr.pch : $(kz_srca)\kzoephdr.c         \
                         {$(kz_inc_concat)}kzoephdr.h  \
                         {$(kz_inc_concat)}kzoengaa.h  \
                         {$(kz_inc_concat)}kzoeenaa.h  \
                         {$(kz_inc_concat)}kzoeidaa.h  \
                         {$(kz_inc_concat)}kzoetdaa.h  \
                         {$(kz_inc_concat)}kzoemeaa.h  \
                         {$(kz_inc_concat)}kzoessaa.h  \
                         {$(kz_inc_concat)}kzoep1aa.h  \
                         {$(kz_inc_concat)}kzoep0aa.h  \
                         {$(kz_inc_concat)}kzoemiaa.h  \
                         {$(kz_inc_concat)}kzoengaa.hg \
                         {$(kz_inc_concat)}kzoeltaa.hg \
                         $(kz_src)\kzoehdr1.sig
   qspawn $(kz_src)\kzoephdr.err $(cl) @<<
-c $(dll_model) $(win30dll)
-DWINVER=0x030A -W3 -Zp -G2 -Gw /D "ZEIDON"
-Od
-Fonul.obj $(io)
-Yckzoephdr.h-Fpkzoephdr.pch
$(kz_srca)\kzoephdr.c
<<

$(kz_src)\kzoephco.pch : $(kz_srca)\kzoephdr.c         \
                         {$(kz_inc_concat)}kzoephdr.h  \
                         {$(kz_inc_concat)}kzoengaa.h  \
                         {$(kz_inc_concat)}kzoeenaa.h  \
                         {$(kz_inc_concat)}kzoeidaa.h  \
                         {$(kz_inc_concat)}kzoetdaa.h  \
                         {$(kz_inc_concat)}kzoemeaa.h  \
                         {$(kz_inc_concat)}kzoessaa.h  \
                         {$(kz_inc_concat)}kzoep1aa.h  \
                         {$(kz_inc_concat)}kzoep0aa.h  \
                         {$(kz_inc_concat)}kzoemiaa.h  \
                         {$(kz_inc_concat)}kzoengaa.hg \
                         {$(kz_inc_concat)}kzoeltaa.hg \
                         $(kz_src)\kzoehdr1.sig
   qspawn $(kz_src)\kzoephco.err $(cl) @<<
-c $(dll_model) $(win30dll)
-DWINVER=0x030A -W3 -Zp -G2 -Gw /D "ZEIDON"
-DDEBUG -D_DEBUG -Od
-Fonul.obj $(io) $(dllspec)
-Yckzoephdr.h-FpKZOEPHCO.pch -Yd
$(kz_srca)\kzoephdr.c
<<

# ====================== .objs ========================
$(kz_obj):$(kz_src)\%.c

# Compile all the OS-INdependent stuff.
$(core_obj): $(kz_srca)\$(@B).c \
             {$(kz_inc_concat)}kzoemeaa.h\
             {$(kz_inc_concat)}kzoeenaa.h\
             {$(kz_inc_concat)}kzoemiaa.h\
             $(kz_src)\kzoehdr1.sig
   @echo ------------ $(@B).c ----------------
   @qspawn $(kz_srca)\$(@B).err $(cl) @<<
$(DLLFLAG)
$(pc_hdr)
$(kz_srca)\$(@B).c
-I $(kz_basew)\incz\expat
<<

# Compile all the OS-INdependent stuff.
$(core_cpp_obj): $(kz_srca)\$(@B).cpp \
                 {$(kz_inc_concat)}kzoedeca.h\
                 {$(kz_inc_concat)}kzoemeaa.h\
                 {$(kz_inc_concat)}kzoeenaa.h\
                 {$(kz_inc_concat)}kzoemiaa.h\
                 $(kz_src)\kzoehdr1.sig
   @echo ------------ $(@B).c ----------------
   @qspawn $(kz_srca)\$(@B).err $(cl) @<<
$(DLLFLAG) /Fd$(kz_basew)\bin\kzoengaa.pdb
$(kz_srca)\$(@B).cpp
<<

# Compile all the OS-dependent stuff.
$(core_objo): $(kz_srcw)\$(@B).c \
              {$(kz_inc_concat)}kzoemsaa.hg \
              {$(kz_inc_concat)}kzoengaa.hg \
              {$(kz_inc_concat)}kzoeltaa.hg \
              {$(kz_inc_concat)}kzoemeaa.h \
              {$(kz_inc_concat)}kzoeenaa.h \
              {$(kz_inc_concat)}kzoemiaa.h \
              {$(kz_inc_concat)}kzoeinco.h \
              $(kz_src)\kzoehdr1.sig
   @echo ------------ $(@B).c ----------------
   @qspawn $(kz_srcw)\$(@B).err $(cl) @<<
$(DLLFLAG) /Fd$(kz_basew)\bin\kzoengaa.pdb
$(kz_srcw)\$(@B).c
<<

# Compile the timestamp OBJ if any core OBJ's have been recompiled.
$(kz_obj)\kzoetsaa.obj : $(all_core_objs)
   @echo ------------ $(@B).c ----------------
   @qspawn $(kz_srcw)\$(@B).err $(cl) @<<
$(DLLFLAG) /Fd$(kz_basew)\bin\kzoengaa.pdb
$(kz_srca)\$(@B).c
<<

# ====================== .dll ========================

$(kz_bin)\kzoengaa.dll : $(all_core_objs)             \
                         $(kz_obj)\kzoetsaa.obj       \
#                        $(kz_base)\MAK\kzoengaa.mak  \
                         $(kz_src)\kzoengaa.def
   @echo ------------ kzoengaa.dll ----------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 $(kz_srcw)\kzoengaa.def > $(TEMP)\kzoengaa.def
   @qspawn $(kz_srcw)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzoengaa.dll
/MAP:kzoengaa.map
/PDB:$(kz_bin)\kzoengaa.pdb
/DEF:$(TEMP)\kzoengaa.def
/IMPLIB:$(kz_lib)r\kzoengaa.lib
$(linkdlls:kzoengaa.lib= )
$(all_core_objs) $(kz_obj)\kzoetsaa.obj
$(kz_lib)z\zdecimal.lib
$(kz_lib)z\expat\xmlparse.lib
DelayImp.lib kzoedbga.lib
/DelayLoad:xmlparse.dll
<<
#$(kz_srcw)\libz\expat
!else
   qpreproc $(kz_srcw)\kzoengaa.def > $(TEMP)\kzoengaa.def
   qspawn $(kz_srcw)\$(@B).ler $(linker) @<<
$(kz_obj)\kzoetsaa.obj +
$(all_core_objs: = +
) +
$(linkopt)
$(kz_bin)\kzoengaa.dll
kzoengaa.map
$(linkdlls:kzoengaa= ) SHELL
$(TEMP)\kzoengaa.def
<<
   implib $(kz_lib)r\kzoengaa.lib $(TEMP)\kzoengaa.def
   mapsym kzoengaa
!endif

# ============================================================
# ====================== zdllinst.obj ========================
# ============================================================
$(kz_lib)r\zdllinst.obj: {$(kz_src_concat)}zdllinst.c
   qspawn $(kz_srca)\$(@B).err $(cl) @<<
-c $(dll_model) $(opt) -Fo$(kz_lib)r\zdllinst.obj $(io) $(dllspec)
$(kz_srcw)\$(@B).c
<<

# ============================================================
# ====================== kzoengwa.exe ========================
# ============================================================

# ====================== .obj ========================
$(kz_obj)\kzoengwa.obj : {$(kz_src_concat)}kzoengwa.c    \
                         {$(kz_inc_concat)}kzoengwa.h   \
                         {$(kz_inc_concat)}kzoengaa.hg   \
                         {$(kz_inc_concat)}kzoemeaa.h   \
                         {$(kz_inc_concat)}kzoeenaa.h   \
                         {$(kz_inc_concat)}kzoemiaa.h   \
                         $(kz_src)\kzoehdr1.sig
   qspawn $(kz_basew)\oe\kzoengwa.err $(cl) @<<
$(EXEFLAG) /Fd$(kz_basew)\bin\kzoengwa.pdb
-I$(kz_basew)\incz\sqlsrvr
$(kz_srcw)\kzoengwa.c
<<

$(kz_obj)\kzoengwa.res  : $(kz_src)\kzoengwa.rc   \
                         {$(kz_inc_concat)}kzoengwa.h
!if "$(BUILDOS)"=="win32"
   rc -d__WIN32__ -I $(kz_src) /fo$(kz_obj)\kzoengwa.res $(kz_src)\kzoengwa.rc
!else
   rc -r $(kz_src)\kzoengwa.rc /fo$(kz_obj)\kzoengwa.res -I $(kz_src)
!if "$(BUILDOS)"=="win"
# Following needed because of a bug in windows RC.
   move $(kz_basew)\oe\kzoengwa.res $(kz_obj)\kzoengwa.res
!endif
!endif

$(kz_bin)\kzoengwa.exe : $(kz_obj)\kzoengwa.obj       \
                         $(kz_src)\kzoengwa.dfb       \
#                        $(kz_base)\MAK\kzoengaa.mak  \
                         $(kz_obj)\kzoengwa.res
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 $(kz_srcw)\kzoengwa.dfb > $(TEMP)\kzoengwa.def
   qspawn $(kz_basew)\oe\kzoengwa.ler $(linker) @<<
$(linkopt) $(linkoptexe)
/OUT:$(kz_bin)\kzoengwa.exe
/MAP:kzoengwa.map
/DEF:$(TEMP)\kzoengwa.def
/PDB:$(kz_basew)\bin\kzoengwa.pdb
$(linkexes)
$(kz_obj)\kzoengwa.obj $(kz_obj)\kzoengwa.res
<<
!else
   qpreproc $(kz_srcw)\kzoengwa.def > $(TEMP)\kzoengwa.def
   qspawn $(kz_basew)\oe\kzoengwa.ler $(linker) @<<
$(kz_obj)\kzoengwa.obj     +
$(linkopt)
$(kz_bin)\kzoengwa.exe
kzoengwa.map
$(linkexes) kzoengaa TOOLHELP
$(TEMP)\kzoengwa.def
<<
   rc  $(kz_obj)\kzoengwa.res $(kz_bin)\kzoengwa.exe
!endif

# ============================================================
# ====================== zWINSOCK.dll ========================
# ============================================================

!if "$(BUILDOS)"=="win32"
#WIN32 zwinsock is a C++ file.
$(kz_obj)\zwinsock.obj : {$(kz_src_concat)}zwinsock.cpp {$(kz_src_concat)}zwinsock.h
   qspawn $(kz_basew)\oe\zwinsock.err $(cl) @<<
$(DLLFLAG) $(CPPFLAG) -EHsc /Fd$(kz_basew)\bin\zwinsock.pdb
$(kz_basew)\oe\zwinsock.cpp
<<
!else
$(kz_obj)\zwinsock.obj : {$(kz_src_concat)}zwinsock.c
   qspawn $(kz_basew)\oe\zwinsock.err $(cl) @<<
$(DLLFLAG)
$(kz_basew)\oe\zwinsock.c
<<
!endif

$(kz_bin)\zwinsock.dll : $(kz_obj)\zwinsock.obj \
                         $(kz_src)\zwinsock.def
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 $(kz_srcw)\zwinsock.def > $(TEMP)\zwinsock.def
   qspawn $(kz_basew)\oe\zwinsock.ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\zwinsock.dll
/DEF:$(TEMP)\zwinsock.def
/MAP:zwinsock.map
/PDB:$(kz_basew)\bin\zwinsock.pdb
$(linkdlls) wsock32.lib
$(kz_obj)\zwinsock.obj
<<
#$(linkdlls) nafxcwd.lib wsock32.lib
!else
   qpreproc $(kz_srcw)\zwinsock.def > $(TEMP)\zwinsock.def
   qspawn $(kz_basew)\oe\zwinsock.ler $(linker) @<<
$(kz_obj)\zwinsock.obj +
$(linkopt)
$(kz_bin)\zwinsock.dll
zwinsock.map
$(linkdlls) WINSOCK
$(TEMP)\zwinsock.def
<<
!endif

# ============================================================
# ====================== kzoedbga.dll ========================
# ============================================================

# kzoedbga is a C++ file.
$(kz_obj)\kzoedbga.obj : {$(kz_src_concat)}kzoedbga.cpp {$(kz_src_concat)}kzoedbga.h
   qspawn $(kz_basew)\oe\kzoedbga.err $(cl) @<<
$(DLLFLAG) $(CPPFLAG) -EHsc -DKZOEDBGA_EXPORTS /Fd$(kz_basew)\bin\kzoedbga.pdb /D USING_V110_SDK71
$(kz_basew)\oe\kzoedbga.cpp
<<

$(kz_bin)\kzoedbga.dll : $(kz_obj)\kzoedbga.obj
   qspawn $(kz_basew)\oe\kzoedbga.ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzoedbga.dll
/IMPLIB:$(kz_basew)\libz\kzoedbga.lib
/MAP:kzoedbga.map
/PDB:$(kz_basew)\bin\kzoedbga.pdb
$(kz_obj)\kzoedbga.obj
<<

# ============================================================
# ====================== zsimpdir.dll ========================
# ============================================================

$(kz_obj)\zsimpdir.obj : {$(kz_src_concat)}zsimpdir.c
   qspawn $(kz_srca)\zsimpdir.err $(cl) @<<
$(DLLFLAG) -EHsc -DZSIMPDIR_EXPORTS /Fd$(kz_basew)\bin\zSimpDir.pdb
$(kz_srca)\zsimpdir.c
<<

$(kz_bin)\zsimpdir.dll : $(kz_obj)\zsimpdir.obj
   qspawn $(kz_basew)\oe\zsimpdir.ler $(linker) @<<
$(linkopt) $(linkoptdll) kzoengaa.lib
/DEF:$(kz_basew)\oe\zsimpdir.def
/OUT:$(kz_bin)\zsimpdir.dll
/IMPLIB:$(kz_basew)\libz\zsimpdir.lib
/MAP:zsimpdir.map
/PDB:$(kz_basew)\bin\zSimpDir.pdb
$(kz_obj)\zsimpdir.obj
<<

# ============================================================
# ====================== kzoeclnt.exe ========================
# ============================================================
$(kz_obj)\kzoeclnt.obj : {$(kz_src_concat)}kzoeclnt.c    \
                         {$(kz_inc_concat)}kzoengaa.h   \
                         {$(kz_inc_concat)}kzoemeaa.h   \
                         {$(kz_inc_concat)}kzoep1aa.h   \
                         $(kz_src)\kzoehdr1.sig
   qspawn $(kz_srcw)\$(@B).err $(cl) @<<
$(EXEFLAG) /Fd$(kz_basew)\bin\kzoeclnt.pdb
$(kz_srcw)\$(@B).c
<<

$(kz_obj)\kzoeclnt.res  : $(kz_src)\kzoeclnt.rc  $(kz_src)\kzoengwa.h
!if "$(BUILDOS)"=="win32"
   rc -d__WIN32__ -I $(kz_src) /fo$(kz_obj)\kzoeclnt.res $(kz_src)\kzoeclnt.rc
!else
   rc -r $(kz_src)\kzoeclnt.rc $(kz_obj)\kzoeclnt.res -I $(kz_src)
!if "$(BUILDOS)"=="win"
# Following needed because of a bug in windows RC.
   move $(kz_basew)\oe\kzoeclnt.res $(kz_obj)\kzoeclnt.res
!endif
!endif

$(kz_bin)\kzoeclnt.exe : $(kz_obj)\kzoeclnt.obj       \
                         $(kz_src)\kzoeclnt.def       \
#                        $(kz_base)\MAK\kzoengaa.mak  \
                         $(kz_obj)\kzoeclnt.res
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 $(kz_srcw)\kzoeclnt.def > $(TEMP)\kzoeclnt.def
   qspawn $(kz_basew)\oe\kzoeclnt.ler $(linker) @<<
$(linkopt) $(linkoptexe)
/OUT:$(kz_bin)\kzoeclnt.exe
/PDB:$(kz_basew)\bin\kzoeclnt.pdb
/MAP:kzoeclnt.map
/DEF:$(TEMP)\kzoeclnt.def
$(linkexes)
$(kz_obj)\kzoeclnt.obj $(kz_obj)\kzoeclnt.res
<<
!else
   qpreproc $(kz_srcw)\kzoeclnt.def > $(TEMP)\kzoeclnt.def
   qspawn $(kz_basew)\oe\kzoeclnt.ler $(linker) @<<
$(kz_obj)\kzoeclnt.obj     +
$(linkopt)
$(kz_bin)\kzoeclnt.exe
kzoeclnt.map
$(linkexes) kzoengaa
$(TEMP)\kzoeclnt.def
<<
   rc  $(kz_obj)\kzoeclnt.res $(kz_bin)\kzoeclnt.exe
!endif


# ============================================================
# ====================== kzschedt.exe ========================
# ============================================================
$(kz_obj)\kzschedt.obj : {$(kz_src_concat)}kzschedt.c    \
                         {$(kz_inc_concat)}kzoengaa.h   \
                         {$(kz_inc_concat)}kzoemeaa.h    \
                         {$(kz_inc_concat)}kzoep1aa.h    \
                         $(kz_src)\kzoehdr1.sig
   qspawn $(kz_srcw)\$(@B).err $(cl) @<<
$(EXEFLAG) /Fd$(kz_basew)\bin\kzschedt.pdb
$(kz_srcw)\$(@B).c
<<

$(kz_obj)\kzschedt.res  : $(kz_src)\kzschedt.rc  $(kz_src)\kzoengwa.h
!if "$(BUILDOS)"=="win32"
   rc -d__WIN32__ -I $(kz_src) /fo$(kz_obj)\kzschedt.res $(kz_src)\kzschedt.rc
!else
   rc -r $(kz_src)\kzschedt.rc $(kz_obj)\kzschedt.res -I $(kz_src)
!if "$(BUILDOS)"=="win"
# Following needed because of a bug in windows RC.
   move $(kz_basew)\oe\kzschedt.res $(kz_obj)\kzschedt.res
!endif
!endif

$(kz_bin)\kzschedt.exe : $(kz_obj)\kzschedt.obj       \
                         $(kz_src)\kzschedt.def       \
#                        $(kz_base)\MAK\kzoengaa.mak  \
                         $(kz_obj)\kzschedt.res
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 $(kz_srcw)\kzschedt.def > $(TEMP)\kzschedt.def
   qspawn $(kz_basew)\oe\kzschedt.ler $(linker) @<<
$(linkopt) $(linkoptexe)
/OUT:$(kz_bin)\kzschedt.exe
/PDB:$(kz_basew)\bin\kzschedt.pdb
/MAP:kzschedt.map
/DEF:$(TEMP)\kzschedt.def
$(linkexes)
$(kz_obj)\kzschedt.obj $(kz_obj)\kzschedt.res
<<
!else
   qpreproc $(kz_srcw)\kzschedt.def > $(TEMP)\kzschedt.def
   qspawn $(kz_basew)\oe\kzschedt.ler $(linker) @<<
$(kz_obj)\kzschedt.obj     +
$(linkopt)
$(kz_bin)\kzschedt.exe
kzschedt.map
$(linkexes) kzoengaa
$(TEMP)\kzschedt.def
<<
   rc  $(kz_obj)\kzschedt.res $(kz_bin)\kzschedt.exe
!endif


SIG1:
   -touch $(kz_src)\kzoehdr1.sig

CLEAN:
   -del /q $(kz_obj)\*.*
   -del $(kz_bin)\kzoe*.*
   -del $(kz_bin)\zsimp*.*
   -del $(kz_bin)\kzschedt.*
   -del $(kz_bin)\zwinsock.*
   -del $(kz_lib)z\kzoe*.*
   -del $(kz_lib)r\kzoe*.*
   -del $(kz_lib)r\kzoe*.exp
   -del $(kz_lib)r\zwinsock.*
   -del $(kz_src)\*.err
   -del $(kz_srcw)\*.map
   -del $(kz_srcw)\*.err
   -del $(kz_srcw)\*.ler
   -del $(kz_srcw)\*.pdb
   -del $(kz_srcw)\*.sbr
   -del $(kz_src)\kzoephdr.pch
   -del $(kz_src)\kzoephco.pch
   -del $(kz_lib)r\zdllinst.obj

CLEANPCH:
   -del $(kz_src)\kzoephdr.pch
   -del $(kz_src)\kzoephco.pch

$(kz_src)\kzoehdr1.sig:
   -touch $(kz_src)\kzoehdr1.sig
