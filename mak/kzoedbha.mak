# CHANGE LOG
#
# 2001.03.27  DKS
#     Added correct path for kzhgenky.def file.
#
# 2001.02.07  RG
#     Set variable blddbh so we can use zdctl.lib in file
#     commw32.hnm
# 2001.01.11  RG
#     build *.pdb-files everytime
# 1998.08.21  DGC
#     Added dummy dbhandler (kzhsqlxx.???)
#
# 1998.08.26  DGC
#     Added Win32 SqlBase dbhandler for TMV.
#
# 1998.10.15  DGC
#     Removed references to win95.
#
# 1998.10.16  DGC
#     Changed reference of ODBC library.
#
# 1998.11.10  DGC
#     Added kzhsqlga.obj to make of kzhsqldb.dll
#
# 1998.11.23  DGC
#     Fixed problem introduced in ODBC make.

blddbh = y
!INCLUDE \$(KZV)\MAK\KZVERS.HNM
!INCLUDE \$(KZV)\MAK\KZCOMMON.HNM
blddbh =
kz_srca = $(kz_basea)\oe

!if "$(cl)"=="cl"
!if "$(BUILDOS)"=="win"
dllspec = -FPc $(CL)
exespec = -FPc $(CL)
!else
dllspec = $(CL)
exespec = $(CL)
!endif
!endif

!if "$(BUILDOS)"=="win"
TARGETS = $(kz_bin)\kzhdbvaa.dll \
          $(kz_bin)\kzhdbvab.dll \
          $(kz_obj)\kzhsqlga.obj \
          $(kz_bin)\kzhsqlsa.dll \
          $(kz_bin)\kzhsqlsb.dll \
          $(kz_bin)\kzhsqlmb.dll \
          $(kz_bin)\kzhsqllb.dll \
          $(kz_bin)\kzhsqlba.dll \
          $(kz_bin)\kzhsqlbb.dll \
          $(kz_bin)\kzhsqldb.dll \
          $(kz_bin)\kzhgenky.dll
!else

TARGETS = $(kz_obj)\kzhsqlga.obj \
          $(kz_bin)\kzhgenky.dll

!ifndef NO_ACCESS
TARGETS = $(TARGETS) $(kz_bin)\kzhsqlab.dll
!endif

!ifndef NO_ODBC
TARGETS = $(TARGETS) $(kz_bin)\kzhsqloa.dll
TARGETS = $(TARGETS) $(kz_bin)\kzhsqlob.dll
!endif

!ifdef DB2SDK
TARGETS = $(TARGETS) $(kz_bin)\kzhsqlda.dll
!endif

!ifndef NO_DB2SDK
TARGETS = $(TARGETS) $(kz_bin)\kzhsqldb.dll
!endif

!ifdef SQLBASESDK
TARGETS = $(TARGETS) $(kz_bin)\kzhsqlba.dll
!endif

!ifndef NO_SQLSERVER
TARGETS = $(TARGETS) $(kz_bin)\kzhsqlsb.dll
!endif

!ifndef NO_SQLPOSTGRESQL
TARGETS = $(TARGETS) $(kz_bin)\kzhsqlpb.dll
!endif

!ifndef NO_MYSQL
TARGETS = $(TARGETS) $(kz_bin)\kzhsqlmb.dll $(kz_bin)\kzhsqllb.dll
!endif

!ifndef NO_DUMMY
TARGETS = $(TARGETS) $(kz_bin)\kzhsqlxx.dll
!endif

!endif

DLLFLAG = $(DLLFLAG) -DQUINSOFT

ALL : $(TARGETS)

#============================================================================
#================= kzhdbvaa.dll =============================================
#============================================================================

$(kz_obj)\kzhdbvaa.obj : {$(kz_src_concat)}kzhdbvaa.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   qspawn $(kz_srca)\$(@B).err $(cl) @<<
$(cl) $(DLLFLAG) /Fd$(kz_basew)\bin\kzhdbvaa.pdb
-I\$(KZV)\w\incz\rdm321
$(kz_base)\a\oe\kzhdbvaa.c
<<

$(kz_bin)\kzhdbvaa.dll : $(kz_obj)\kzhdbvaa.obj \
                         $(kz_src)\kzhdbvaa.def \
                         \$(KZV)\w\libr\zdrapp.lib
   $(linker) @<<
$(kz_obj)\kzhdbvaa.obj +
$(linkopt)
$(kz_bin)\kzhdbvaa.dll
/PDB:$(kz_bin)\kzhdbvaa.pdb
kzhdbvaa.map
$(linkdlls) kzoengaa zdrapp \$(KZV)\w\libz\rdm321\vista
$(kz_src)\kzhdbvaa.def
<<

$(kz_obj)\kzhdbvab.obj : {$(kz_src_concat)}kzhdbvab.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   qspawn $(kz_base)\a\oe\kzhdbvab.err $(cl) @<<
$(DLLFLAG) /Fd$(kz_basew)\bin\kzhdbvab.pdb
-I\$(KZV)\a\tz
$(kz_base)\a\oe\kzhdbvab.c
<<

$(kz_bin)\kzhdbvab.dll : $(kz_obj)\kzhdbvab.obj \
                         $(kz_src)\kzhdbvab.def
   qspawn $(kz_base)\a\oe\kzhdbvab.ler $(linker) @<<
$(kz_obj)\kzhdbvab.obj +
$(linkopt)
$(kz_bin)\kzhdbvab.dll
/PDB:$(kz_bin)\kzhdbvab.pdb
kzhdbvab.map
$(linkdlls) kzoengaa zdrapp
$(kz_src)\kzhdbvab.def
<<

#============================================================================
#================= kzhsqlga.obj =============================================
#============================================================================

$(kz_obj)\kzhsqlga.obj : {$(kz_src_concat)}kzhsqlga.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlga.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_srca)\$(@B).err $(cl) @<<
$(DLLFLAG)
$(kz_base)\a\oe\kzhsqlga.c
<<

#============================================================================
#================= kzhsqlba.dll =============================================
#================= kzhsqlbb.dll =============================================
#============================================================================

$(kz_obj)\kzhsqlba.obj : {$(kz_src_concat)}kzhsqlxa.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlba.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqlba.err $(cl) @<<
$(DLLFLAG) -DSQLBASE /Fd$(kz_basew)\bin\kzhsqlba.pdb
-I\$(KZV)\w\incz\sqlbase
$(kz_base)\a\oe\kzhsqlxa.c
<<

$(kz_bin)\kzhsqlba.dll : $(kz_obj)\kzhsqlba.obj \
                         $(kz_src)\kzhsqlxa.def \
                         $(kz_obj)\kzhsqlga.obj
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlba.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 SQLBASE=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\$(@B).def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\$(@B).dll
/PDB:$(kz_bin)\kzhsqlba.pdb
/MAP:$(@B).map
/DEF:$(TEMP)\$(@B).def
$(kz_obj)\$(@B).obj $(kz_obj)\kzhsqlga.obj $(SQLBASESDK)\SQLAPIW.lib $(linkdlls)
<<
!else
   qpreproc SQLBASE=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\kzhsqlba.def
   qspawn $(kz_base)\a\oe\kzhsqlba.ler $(linker) @<<
$(kz_obj)\kzhsqlba.obj +
$(kz_obj)\kzhsqlga.obj +
$(linkopt)
$(kz_bin)\kzhsqlba.dll
kzhsqlba.map
$(linkdlls) kzoengaa \$(KZV)\w\libz\sqlbase\sqlapiw
$(TEMP)\kzhsqlba.def
<<
!endif

$(kz_obj)\kzhsqlbb.obj : {$(kz_src_concat)}kzhsqlxb.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlbb.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqlbb.err $(cl) @<<
$(DLLFLAG) -DSQLBASE /Fd$(kz_basew)\bin\kzhsqlbb.pdb
-I\$(KZV)\a\tz
$(kz_base)\a\oe\kzhsqlxb.c
<<

$(kz_bin)\kzhsqlbb.dll : $(kz_obj)\kzhsqlbb.obj \
                         $(kz_src)\kzhsqlxb.def
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlbb.dll ---------------------------
   @echo --------------------------------------------------------
   qpreproc SQLBASE=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlbb.def
   qspawn $(kz_base)\a\oe\kzhsqlbb.ler $(linker) @<<
$(kz_obj)\kzhsqlbb.obj +
$(linkopt)
$(kz_bin)\kzhsqlbb.dll
/PDB:$(kz_bin)\kzhsqlbb.pdb
kzhsqlbb.map
$(linkdlls) kzoengaa
$(TEMP)\kzhsqlbb.def
<<

#============================================================================
#================= kzhsqlab.dll =============================================
#============================================================================
$(kz_obj)\kzhsqlab.obj : {$(kz_src_concat)}kzhsqlxb.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlab.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqlab.err $(cl) @<<
$(DLLFLAG) -DACCESS /Fd$(kz_basew)\bin\kzhsqlab.pdb
$(kz_base)\a\oe\kzhsqlxb.c
<<

$(kz_bin)\kzhsqlab.dll : $(kz_obj)\kzhsqlab.obj \
                         $(kz_src)\kzhsqlxb.def
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlab.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 ACCESS=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlab.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqlab.dll
/MAP:kzhsqlab.map
/PDB:$(kz_bin)\kzhsqlab.pdb
/DEF:$(TEMP)\kzhsqlab.def
$(kz_obj)\kzhsqlab.obj $(linkdlls)
<<
!else
   qpreproc ACCESS=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlab.def
   qspawn $(kz_base)\a\oe\kzhsqlab.ler $(linker) @<<
$(kz_obj)\kzhsqlab.obj +
$(linkopt)
$(kz_bin)\kzhsqlab.dll
kzhsqlab.map
$(linkdlls) kzoengaa
$(TEMP)\kzhsqlab.def
<<
!endif

#============================================================================
#================= kzhsqloa.dll =============================================
#============================================================================
$(kz_obj)\kzhsqloa.obj : {$(kz_src_concat)}kzhsqlxa.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqloa.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_srca)\$(@B).err $(cl) @<<
$(DLLFLAG) -DODBC /Fd$(kz_basew)\bin\kzhsqloa.pdb
$(kz_base)\a\oe\kzhsqlxa.c
<<

$(kz_bin)\kzhsqloa.dll : $(kz_obj)\kzhsqloa.obj \
                         $(kz_src)\kzhsqlxa.def \
                         $(kz_obj)\kzhsqlga.obj
   @echo --------------------------------------------------------
   @echo --------------- kzhsqloa.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 ODBC=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\kzhsqloa.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqloa.dll
/PDB:$(kz_bin)\kzhsqloa.pdb
/MAP:kzhsqloa.map
/DEF:$(TEMP)\kzhsqloa.def
$(kz_obj)\kzhsqloa.obj $(kz_obj)\kzhsqlga.obj ODBC32.lib $(linkdlls) kzoedbga.lib
<<
#$(kz_obj)\kzhsqloa.obj $(kz_obj)\kzhsqlga.obj ODBC32.lib $(linkdlls) kzoedbga.lib NTWDBLIB.lib
!else
   qpreproc ODBC=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\kzhsqloa.def
   qspawn $(kz_base)\a\oe\kzhsqloa.ler $(linker) @<<
$(kz_obj)\kzhsqloa.obj +
$(kz_obj)\kzhsqlga.obj +
$(linkopt)
$(kz_bin)\kzhsqloa.dll
kzhsqloa.map
$(linkdlls) $(DB2SDK)\LIB\DB2API.lib ODBC32.lib kzoengaa
$(TEMP)\kzhsqloa.def
<<
!endif

$(kz_obj)\kzhsqlob.obj : {$(kz_src_concat)}kzhsqlxb.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlob.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqlob.err $(cl) @<<
$(DLLFLAG) -DODBC /Fd$(kz_basew)\bin\kzhsqlob.pdb
$(kz_base)\a\oe\kzhsqlxb.c
<<

$(kz_bin)\kzhsqlob.dll : $(kz_obj)\kzhsqlob.obj \
                         $(kz_src)\kzhsqlxb.def
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlob.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 ODBC=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlob.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqlob.dll
/PDB:$(kz_bin)\kzhsqlob.pdb
/MAP:kzhsqlob.map
/DEF:$(TEMP)\kzhsqlob.def
$(kz_obj)\kzhsqlob.obj $(linkdlls)
<<
!else
   qpreproc ODBC=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlob.def
   qspawn $(kz_base)\a\oe\kzhsqlob.ler $(linker) @<<
$(kz_obj)\kzhsqlob.obj +
$(linkopt)
$(kz_bin)\kzhsqlob.dll
kzhsqlob.map
$(linkdlls) kzoengaa
$(TEMP)\kzhsqlob.def
<<
!endif

#============================================================================
#================= kzhsqlda.dll =============================================
#============================================================================

$(kz_obj)\kzhsqlda.obj : {$(kz_src_concat)}kzhsqlxa.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlda.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_srca)\$(@B).err $(cl) @<<
$(DLLFLAG)  -DDB2WIN -DDB2 /Fd$(kz_basew)\bin\kzhsqlda.pdb
-I$(DB2SDK)\include
$(kz_base)\a\oe\kzhsqlxa.c
<<

$(kz_bin)\kzhsqlda.dll : $(kz_obj)\kzhsqlda.obj \
                         $(kz_src)\kzhsqlxa.def \
                         $(kz_obj)\kzhsqlga.obj
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlda.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 DB2=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\kzhsqlda.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqlda.dll
/PDB:$(kz_bin)\kzhsqlda.pdb
/MAP:kzhsqlda.map
/DEF:$(TEMP)\kzhsqlda.def
$(kz_obj)\kzhsqlda.obj $(kz_obj)\kzhsqlga.obj $(DB2SDK)\LIB\DB2CLI.lib $(linkdlls)
<<
!else
   qpreproc DB2=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\kzhsqlda.def
   qspawn $(kz_base)\a\oe\kzhsqlda.ler $(linker) @<<
$(kz_obj)\kzhsqlda.obj +
$(kz_obj)\kzhsqlga.obj +
$(linkopt)
$(kz_bin)\kzhsqlda.dll
kzhsqlda.map
$(linkdlls) $(DB2SDK)\LIB\DB2API.lib $(DB2SDK)\LIB\DB2CLI.lib kzoengaa
$(TEMP)\kzhsqlda.def
<<
!endif

$(kz_obj)\kzhsqldb.obj : {$(kz_src_concat)}kzhsqlxb.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqldb.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqldb.err $(cl) @<<
$(DLLFLAG) -DDB2 /Fd$(kz_basew)\bin\kzhsqldb.pdb
$(kz_base)\a\oe\kzhsqlxb.c
<<

$(kz_bin)\kzhsqldb.dll : $(kz_obj)\kzhsqldb.obj \
                         $(kz_obj)\kzhsqlga.obj \
                         $(kz_src)\kzhsqlxb.def
   @echo --------------------------------------------------------
   @echo --------------- kzhsqldb.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 DB2=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqldb.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqldb.dll
/PDB:$(kz_bin)\kzhsqldb.pdb
/MAP:kzhsqldb.map
/DEF:$(TEMP)\kzhsqldb.def
$(kz_obj)\kzhsqldb.obj $(kz_obj)\kzhsqlga.obj $(linkdlls)
<<
!else
   qpreproc DB2=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqldb.def
   qspawn $(kz_base)\a\oe\kzhsqldb.ler $(linker) @<<
$(kz_obj)\kzhsqldb.obj +
$(linkopt)
$(kz_bin)\kzhsqldb.dll
kzhsqldb.map
$(linkdlls) kzoengaa
$(TEMP)\kzhsqldb.def
<<
!endif

#============================================================================
#================= kzhsqlmb.dll =============================================
#============================================================================
$(kz_obj)\kzhsqlmb.obj : {$(kz_src_concat)}kzhsqlxb.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlmb.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqlmb.err $(cl) @<<
$(DLLFLAG) -DMYSQL /Fd$(kz_basew)\bin\kzhsqlmb.pdb
-I\$(KZV)\a\tz
$(kz_base)\a\oe\kzhsqlxb.c
<<

$(kz_bin)\kzhsqlmb.dll : $(kz_obj)\kzhsqlmb.obj \
                         $(kz_src)\kzhsqlxb.def
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlmb.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 MYSQL=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlmb.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqlmb.dll
/PDB:$(kz_bin)\kzhsqlmb.pdb
/MAP:kzhsqlmb.map
/DEF:$(TEMP)\kzhsqlmb.def
$(kz_obj)\kzhsqlmb.obj $(linkdlls)
<<
!else
   qpreproc MYSQL=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlmb.def
   qspawn $(kz_base)\a\oe\kzhsqlmb.ler $(linker) @<<
$(kz_obj)\kzhsqlmb.obj +
$(linkopt)
$(kz_bin)\kzhsqlmb.dll
kzhsqlmb.map
$(linkdlls) kzoengaa
$(TEMP)\kzhsqlmb.def
<<
!endif


#============================================================================
#================= kzhsqllb.dll (Sqlite) ====================================
#============================================================================
$(kz_obj)\kzhsqllb.obj : {$(kz_src_concat)}kzhsqlxb.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqllb.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqllb.err $(cl) @<<
$(DLLFLAG) -DSQLITE /Fd$(kz_basew)\bin\kzhsqllb.pdb
-I\$(KZV)\a\tz
$(kz_base)\a\oe\kzhsqlxb.c
<<

$(kz_bin)\kzhsqllb.dll : $(kz_obj)\kzhsqllb.obj \
                         $(kz_src)\kzhsqlxb.def
   @echo --------------------------------------------------------
   @echo --------------- kzhsqllb.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 SQLITE=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqllb.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqllb.dll
/PDB:$(kz_bin)\kzhsqllb.pdb
/MAP:kzhsqllb.map
/DEF:$(TEMP)\kzhsqllb.def
$(kz_obj)\kzhsqllb.obj $(linkdlls)
<<
!else
   qpreproc SQLITE=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqllb.def
   qspawn $(kz_base)\a\oe\kzhsqllb.ler $(linker) @<<
$(kz_obj)\kzhsqllb.obj +
$(linkopt)
$(kz_bin)\kzhsqllb.dll
kzhsqllb.map
$(linkdlls) kzoengaa
$(TEMP)\kzhsqllb.def
<<
!endif


#============================================================================
#================= kzhsqlsa.dll =============================================
#================= kzhsqlsb.dll =============================================
#============================================================================

$(kz_obj)\kzhsqlsa.obj : {$(kz_src_concat)}kzhsqlxa.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlsa.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqlsa.err $(cl) @<<
$(DLLFLAG) -DSQLSERVER /Fd$(kz_basew)\bin\kzhsqlsa.pdb
-I\$(KZV)\w\incz\sqlsrvr
$(kz_base)\a\oe\kzhsqlxa.c
<<

$(kz_bin)\kzhsqlsa.dll : $(kz_obj)\kzhsqlsa.obj \
                         $(kz_src)\kzhsqlxa.def \
                         $(kz_obj)\kzhsqlga.obj
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlsa.dll ---------------------------
   @echo --------------------------------------------------------
   qpreproc SQLSERVER=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\kzhsqlsa.def
   qspawn $(kz_base)\a\oe\kzhsqlsa.ler $(linker) @<<
$(kz_obj)\kzhsqlsa.obj +
$(kz_obj)\kzhsqlga.obj +
$(linkopt)
$(kz_bin)\kzhsqlsa.dll
/PDB:$(kz_bin)\kzhsqlsa.pdb
kzhsqlsa.map
$(linkdlls) kzoengaa \$(KZV)\w\libz\sqlsrvr\w3dblib
$(TEMP)\kzhsqlsa.def
<<

$(kz_obj)\kzhsqlsb.obj : {$(kz_src_concat)}kzhsqlxb.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlsb.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqlsb.err $(cl) @<<
$(DLLFLAG) -DSQLSERVER /Fd$(kz_basew)\bin\kzhsqlsb.pdb
-I\$(KZV)\a\tz
$(kz_base)\a\oe\kzhsqlxb.c
<<

$(kz_bin)\kzhsqlsb.dll : $(kz_obj)\kzhsqlsb.obj \
                         $(kz_src)\kzhsqlxb.def
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlsb.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 SQLSERVER=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlsb.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqlsb.dll
/PDB:$(kz_bin)\kzhsqlsb.pdb
/MAP:kzhsqlsb.map
/DEF:$(TEMP)\kzhsqlsb.def
$(kz_obj)\kzhsqlsb.obj $(linkdlls)
<<
!else
   qpreproc SQLSERVER=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlsb.def
   qspawn $(kz_base)\a\oe\kzhsqlsb.ler $(linker) @<<
$(kz_obj)\kzhsqlsb.obj +
$(linkopt)
$(kz_bin)\kzhsqlsb.dll
kzhsqlsb.map
$(linkdlls) kzoengaa
$(TEMP)\kzhsqlsb.def
<<
!endif

#============================================================================
#================= kzhsqlpb.dll =============================================
#============================================================================

$(kz_obj)\kzhsqlpb.obj : {$(kz_src_concat)}kzhsqlxb.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlpb.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_base)\a\oe\kzhsqlpb.err $(cl) @<<
$(DLLFLAG) -DPOSTGRESQL /Fd$(kz_basew)\bin\kzhsqlsb.pdb
-I\$(KZV)\a\tz
$(kz_base)\a\oe\kzhsqlxb.c
<<

$(kz_bin)\kzhsqlpb.dll : $(kz_obj)\kzhsqlpb.obj \
                         $(kz_src)\kzhsqlxb.def
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlpb.dll ---------------------------
   @echo --------------------------------------------------------
   qpreproc __WIN32__=1 POSTGRESQL=1 $(kz_src)\kzhsqlxb.def > $(TEMP)\kzhsqlpb.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqlpb.dll
/PDB:$(kz_bin)\kzhsqlpb.pdb
/MAP:kzhsqlpb.map
/DEF:$(TEMP)\kzhsqlpb.def
$(kz_obj)\kzhsqlpb.obj $(linkdlls)
<<

#============================================================================
#================= kzhsqlxx.dll =============================================
#============================================================================

$(kz_obj)\kzhsqlxx.obj : {$(kz_src_concat)}kzhsqlxa.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlxx.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_srca)\$(@B).err $(cl) @<<
$(DLLFLAG)  -DDUMMY /Fd$(kz_basew)\bin\kzhsqlxx.pdb
$(kz_base)\a\oe\kzhsqlxa.c
<<

$(kz_bin)\kzhsqlxx.dll : $(kz_obj)\kzhsqlxx.obj \
                         $(kz_src)\kzhsqlxa.def \
                         $(kz_obj)\kzhsqlga.obj
   @echo --------------------------------------------------------
   @echo --------------- kzhsqlxx.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 DUMMY=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\kzhsqlxx.def
   qspawn $(kz_srca)\$(@B).ler $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhsqlxx.dll
/PDB:$(kz_bin)\kzhsqlxx.pdb
/MAP:kzhsqlxx.map
/DEF:$(TEMP)\kzhsqlxx.def
$(kz_obj)\kzhsqlxx.obj $(kz_obj)\kzhsqlga.obj $(linkdlls)
<<
!else
   qpreproc DUMMY=1 $(kz_src)\kzhsqlxa.def > $(TEMP)\kzhsqlxx.def
   qspawn $(kz_base)\a\oe\kzhsqlxx.ler $(linker) @<<
$(kz_obj)\kzhsqlxx.obj +
$(kz_obj)\kzhsqlga.obj +
$(linkopt)
$(kz_bin)\kzhsqlxx.dll
kzhsqlxx.map
$(linkdlls) kzoengaa
$(TEMP)\kzhsqlxx.def
<<
!endif

#============================================================================
#================= kzhgenky.dll =============================================
#============================================================================

$(kz_obj)\kzhgenky.obj : {$(kz_src_concat)}kzhgenky.c \
                         {$(kz_inc_concat)}kzoemeaa.h
   @echo --------------------------------------------------------
   @echo --------------- kzhgenky.obj ---------------------------
   @echo --------------------------------------------------------
   qspawn $(kz_srca)\$(@B).err $(cl) @<<
$(DLLFLAG) /Fd$(kz_basew)\bin\kzhgenky.pdb
$(kz_base)\a\oe\kzhgenky.c
<<

$(kz_bin)\kzhgenky.dll : $(kz_obj)\kzhgenky.obj \
                         $(kz_src)\kzhgenky.def
   @echo --------------------------------------------------------
   @echo --------------- kzhgenky.dll ---------------------------
   @echo --------------------------------------------------------
!if "$(BUILDOS)"=="win32"
   qpreproc __WIN32__=1 $(kz_src)\kzhgenky.def > $(TEMP)\kzhgenky.def
   $(linker) @<<
$(linkopt) $(linkoptdll)
/OUT:$(kz_bin)\kzhgenky.dll
/PDB:$(kz_bin)\kzhgenky.pdb
/MAP:kzhgenky.map
/DEF:$(TEMP)\kzhgenky.def
$(kz_obj)\kzhgenky.obj $(linkdlls)
<<
!else
   qpreproc kzhgenky.def > $(TEMP)\kzhgenky.def
   $(linker) @<<
$(kz_obj)\kzhgenky.obj +
$(linkopt)
$(kz_bin)\kzhgenky.dll
kzhgenky.map
$(linkdlls)
$(TEMP)\kzhgenky.def
<<
!endif

CLEAN:
   -del $(kz_bin)\kzh*.dll
   -del $(kz_bin)\kzh*.ilk
   -del $(kz_bin)\kzh*.pdb
   -del $(kz_bin)\kzh*.exp
   -del $(kz_bin)\kzh*.lib
   -del $(kz_obj)\kzh*.obj
   -del $(kz_srca)\kzh*.err
   -del $(kz_srca)\kzh*.ler
   -del $(kz_srcw)\kzh*.map
