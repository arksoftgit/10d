//KZOEP1AA.H - Ring 1 prototypes

// Start of prototypes internal to Object Services and Zeidon tools

//========================================================================

//KZOEIPAA.H - Prototypes and defines for internal OPERATIONS for
//             use by Zeidon tools and not end-user applications
//

/*
CHANGE LOG

2003.04.10  DGC
   Added stuff for WriteSubobjectToXML().

2002.10.04  DGC
   Added iStoreString/ValueInDerivedAttribute().

2002.03.29  DGC
   Added SysCreateTempFileName().

2002.01.07  HH
   change signature of SysValidDirOrFile so that it can be called from VML.

2001.08.22  DGC
   Started adding stuff for local memory version of Core.

2001.07.27  DGC  10b
   Added SysSetFileDateTime().

2001.05.30  DGC  10b
   Added stuff for NetA changes.

2001.04.18  DGC  10b
   Added code for DropViewObject() logic.

2001.04.13  PAS
   Added zXML_KEYATTRIBSASIDENT.

2001.04.09  US
   Added two new functions SysMalloc() and SysFree().
   These two functions should replace the win16 based functions
   SysAllocMemory() and SysFreeMemory() with the handle overhead.

2001.02.15  DGC
   Added zXML_UPDATEDONLY.

2001.01.23  HH
   SysParseLine: 3. parameter is not const

2000.12.04  BL
   const char change SysStartHelp

2000.11.28  HH
   const char change StoreStringInRecord,SysCopyFile,SysParseLine,
   SysStartHelp.

2000.09.19  DGC
   Added COREFILE_CREATE_NEW.

2000.07.25  HH
   Hold Connection implemented.

2000.05.04  DGC  all
   Added StoreBytesInRecord().

2000.03.16  US all
   prototyp of SysCheckTaskMemory( void ) "void" added due to
   compiler warnings

2000.02.17  DGC  10b
   Added WriteMultipleOIs_ToXML().

2000.01.07  DGC  10b
   More XML stuff.

1999.12.14  DGC  10b
   Started adding stuff for XML processing.

1999.06.02  DGC  10a
   Added GetAttributeFlags() stuff.
   Added GetTracingFlags().

1999.05.26  DGC  10a
   Removed references to zCOREMEM_REALLOC and zCOREMEM_SHARED.

1999.04.19  RS
        Commentlines required for Rose.

1999.03.02  DGC
   Added SysConvertEnvironmentString() as an exported operation.

1999.02.11  DGC
   Started adding attribute flag stuff.
   Added stuff for calling global operations from a client.

*/

// Don't remove the following commentlines. They are required for Rose.
//#include <kzoeenaa.h> //required for Rose
//#include <kzoengaa.h> //required for Rose
//#include <kzoessaa.h> //required for Rose

// typedefs copied from kzoestaa.h so they can be referenced by
// ActivateViewObject, SysCloseFile, and SysLoadLibrary respectively

#define zsizeof _countof

typedef struct ProcessStruct ProcessRecord;
typedef ProcessRecord *LPPROCESS;

typedef struct TaskStruct TaskRecord;
typedef TaskRecord *LPTASK;

typedef struct MutexStruct MutexRecord;
typedef MutexRecord *LPMUTEX;

typedef struct DebugChangeStruct DebugChangeRecord;
typedef DebugChangeRecord *LPDEBUGCHANGE;

#ifndef LPLIBRARY_DEF
typedef struct LibraryStruct LibraryRecord;
typedef LibraryRecord *LPLIBRARY;
typedef LPLIBRARY *LPLPLIBRARY;
#define LPLIBRARY_DEF
#endif

#ifndef LPAPP_DEF
typedef struct AppStruct AppRecord;
typedef AppRecord *LPAPP;
#define LPAPP_DEF
#endif

#ifndef LPVIEWOD_DEF
typedef struct ViewOD_Struct ViewOD_Record;
typedef ViewOD_Record *LPVIEWOD;
#define LPVIEWOD_DEF
#endif

#ifndef LPDOMAIN_DEF
typedef struct DomainStruct DomainRecord;
typedef DomainRecord *LPDOMAIN;
#define LPDOMAIN_DEF
#endif

#ifndef LPTASKDOMAIN_DEF
typedef struct TaskDomainStruct TaskDomainRecord;
typedef TaskDomainRecord *LPTASKDOMAIN;
#define LPTASKDOMAIN_DEF
#endif

#ifndef LPTABLEENTRY_DEF
typedef struct TableEntryStruct TableEntryRecord;
typedef TableEntryRecord * LPTABLEENTRY;
#define LPTABLEENTRY_DEF
#endif

#ifndef LPNLSTABLEENTRY_DEF
typedef struct NLS_TableEntryStruct NLS_TableEntryRecord;
typedef NLS_TableEntryRecord * LPNLSTABLEENTRY;
#define LPNLSTABLEENTRY_DEF
#endif

#ifndef LPREGEXPRESSION_DEF
typedef struct RegExpressionStruct RegExpressionRecord;
typedef RegExpressionRecord * LPREGEXPRESSION;
#define LPREGEXPRESSION_DEF
#endif

#ifndef LPVIEWENTITY_DEF
typedef struct ViewEntityStruct ViewEntityRecord;
typedef ViewEntityRecord *LPVIEWENTITY;
#define LPVIEWENTITY_DEF
#endif

#ifndef LPVIEWATTRIB_DEF
typedef struct ViewAttribStruct ViewAttribRecord;
typedef ViewAttribRecord *LPVIEWATTRIB;
#define LPVIEWATTRIB_DEF
#endif

#ifndef LPCONTEXT_DEF
typedef struct ContextStruct ContextRecord;
typedef ContextRecord * zLPCONTEXT;
#define LPCONTEXT_DEF
#endif

#ifndef LPDATETIME_DEF
typedef struct { zCHAR zDateTime[ 6 ]; } DateTimeRecord;
typedef DateTimeRecord *LPDATETIME;
#define LPDATETIME_DEF
#endif

/***************** Network Prototypes ******************/

#define zNETSTAT_STARTED         0x0001
#define zNETSTAT_OPENCONNECTION  0x0002
#define zNETSTAT_LISTEN          0x0004

typedef struct NetConnectionStruct NetConnectionRecord;
typedef NetConnectionRecord *LPNETCONN;

typedef struct NetworkStruct NetworkRecord;
typedef NetworkRecord *LPNETWORK;

#if 0
// Following is a hack so that Tags will work with the zLPFN... stuff.
#define zLPFN_NETSTART       dummy
#define zLPFN_NETCLOSE       dummy
#define zLPFN_NETLISTEN      dummy
#define zLPFN_NETOPCONN      dummy
#define zLPFN_NETCLCONN      dummy
#define zLPFN_NETGETADDR     dummy
#define zLPFN_NETIO          dummy
#define zLPFN_NETSETM        dummy
#define zLPFN_NETSENDPKT     dummy
#define zLPFN_NETRECVPKT     dummy
#define LPFN_GETSTREAM       dummy
#define LPFN_PUTSTREAM       dummy

#define zLPFN_SERVDIRINIT    dummy
#define zLPFN_SERVDIRCLOSE   dummy
#define zLPFN_SERVDIRADDR    dummy
#endif

typedef zSHORT (POPERATION zLPFN_NETSTART)( zPCHAR, zPPVOID );
typedef zSHORT (POPERATION zLPFN_NETCLOSE)( zVIEW, zPPVOID );
typedef zSHORT (POPERATION zLPFN_NETLISTEN)( zPPVOID, zPCHAR, zVIEW );
typedef zSHORT (POPERATION zLPFN_NETOPCONN)( zPPVOID, zPPVOID,
                                             zPCHAR, zVIEW );
typedef zSHORT (POPERATION zLPFN_NETCLCONN)( zPPVOID, zPPVOID );
typedef zSHORT (POPERATION zLPFN_NETGETADDR)( zVIEW, zPPVOID, zPPVOID,
                                              zCHAR, zPCHAR );
typedef zSHORT (POPERATION zLPFN_NETIO)( zPPVOID, zPPVOID, zPVOID,
                                         zULONG, zCHAR );
typedef zSHORT (POPERATION zLPFN_NETSETM)( zPPVOID, zPPVOID, zCHAR );
typedef zSHORT (POPERATION zLPFN_NETSENDPKT)( zPPVOID, zPPVOID, zCHAR, zLONG );
typedef zSHORT (POPERATION zLPFN_NETRECVPKT)( zPPVOID, zPPVOID,
                                              zPCHAR, zPLONG );

typedef zSHORT (POPERATION LPFN_GETSTREAM)( zVIEW, zPVOID, zPPCHAR,
                                            zULONG, zSHORT );
typedef zSHORT (POPERATION LPFN_PUTSTREAM)( zVIEW, zPVOID, zPCHAR,
                                            zULONG, zCHAR );

typedef zSHORT (POPERATION zLPFN_SERVDIRINIT)( LPTASK, zPCHAR, zPPVOID, zLONG );
typedef zSHORT (POPERATION zLPFN_SERVDIRCLOSE)( LPTASK, zPPVOID, zLONG );
typedef zSHORT (POPERATION zLPFN_SERVDIRADDR)( LPTASK, zPCHAR, zPPVOID,
                                               zLONG, zPVOID );

//
// stuff for network handler and host OE
//

#define zSTRPACKETLTH            sizeof( zDataStrPacket )
#define zHDRPACKETLTH            sizeof( zHeaderPacket )

#define zPACKET_HEADER            'H'  // Indicates that packet is header pckt.
#define zPACKET_SENDLTHS          'S'  // Sending the length of a string.
#define zPACKET_SENDLTHB          'B'  // Sending the lth of a blob.
#define zPACKET_ACK               'K'  // Acknowledge of some process.
#define zPACKET_END               'E'  // End of OI.
#define zPACKET_ERROR             '*'  // Sending an error code.
#define zPACKET_RC                '#'  // Returning an RC from act/commit.
#define zPACKET_EMPTYOI           'e'  // Returning an empty OI.

// Following messages received by a server from a client.
#define zPACKET_REQUESTOI         'R'  // Client is req'ing an OI.
#define zPACKET_REQUESTOIFROMFILE 'F'  // Client is req'ing an OI from file.
#define zPACKET_COMMITOI          'C'  // Client is committing an OI.
#define zPACKET_COMMITOITOFILE    'W'  // Client is writing an OI to file.
#define zPACKET_CALLOPERATION     'O'  // Call operation on server.
#define zPACKET_SENDBOOTSTRAP     'b'  // Client is sending a bootstrap file.
#define zPACKET_REQUESTDISTFILE   'r'  // Client is req'ing dist file.
#define zPACKET_SENDFILE          's'  // Client is sending a file to server.
#define zPACKET_TRACESWITCH       '+'  // Client is sending trace switches.
#define zPACKET_TIMESTAMP         'T'  // Client is req'ing server timestamp.

#define zPACKET_STOP              '9'  // STOP message
#define zPACKET_VERSION           'V'  // Version Identification

typedef struct HeaderPacketStruct zHeaderPacket;
typedef struct HeaderPacketStruct *LPHDRPACKET;
struct HeaderPacketStruct
{
   char  cHeaderIndicator;    // Indicates that packet is a header.
   char  cPacketType;         // Indicates client request.
   char  szAppName[ 32 ];     // Name of application sending msg.
};

#define zAPPLREQ_ACTIVATE   0x00000001
#define zAPPLREQ_COMMIT     0x00000002
#define zAPPLREQ_OPER       0x00000004
#define zAPPLREQ_RETRY      0x00010000

typedef struct ServDirActivateStruct
{
   zPCHAR   pszNetworkName;
   zPCHAR   pszUserSuppliedAddress;
   zLONG    lControl;
   zVIEW    vSubtask;
   zPCHAR   pszViewOD_Name;
   zVIEW    vQualView;
} ServDirActivateRecord, * LPSERVDIRACTIVATE;

typedef struct ServDirCommitStruct
{
   zPCHAR   pszNetworkName;
   zPCHAR   pszUserSuppliedAddress;
   zLONG    lControl;
   zVIEW    vOI;
} ServDirCommitRecord, * LPSERVDIRCOMMIT, * LPSERVDIRBASE;

typedef struct ServDirOperStruct
{
   zPCHAR   pszNetworkName;
   zPCHAR   pszUserSuppliedAddress;
   zLONG    lControl;
   zVIEW    vSubtask;
   zPCHAR   pszOperName;
} ServDirOperRecord, * LPSERVDIROPER;

// *************** Start of XML stuff *********************

// Following are flags to WriteOI_ToXML()
#define zXML_ZEIDONINFO           0x00000001
#define zXML_INCREFLAGS           0x00000002
#define zXML_UPDATEDONLY          0x00000004
#define zXML_ENTITYKEYS           0x00000008    // Write entity keys.
#define zXML_KEYATTRIBSASIDENT    0x00000010    // Write key attributes as Identifiers.
#define zXML_ROOTONLY             0x00000020
#define zXML_SAVECURSORPOSITION   0x00000040

// Following are sent to XMLWRITE function.
#define zXML_STARTOI       0x00000001
#define zXML_ENDOI         0x00000002
#define zXML_STARTENTITY   0x00000004
#define zXML_ENDENTITY     0x00000008
#define zXML_STARTATTRIB   0x00000010
#define zXML_ENDATTRIB     0x00000020
#define zXML_ATTRIBVALUE   0x00000040

#if 0
   #define LPFN_XMLWRITE dummy
   #define LPFN_XMLREAD  dummy
#endif

typedef zSHORT (POPERATION LPFN_XMLWRITE)( zVIEW, zULONG, zPCHAR,
                                           zULONG, zSHORT, zPVOID );
typedef zSHORT (POPERATION LPFN_XMLREAD)( zVIEW, zPPCHAR, zPULONG, zPVOID );

// *************** START OF PROTECTED SYSTEM PROTOTYPES

/*************** File Open Flags ***********************/
#define COREFILE_READ                0x0080
#define COREFILE_WRITE               0x0040
#define COREFILE_UPDATE              (COREFILE_READ | COREFILE_WRITE)
#define COREFILE_CREATE              0x0020
#define COREFILE_DELETE              0x0008
#define COREFILE_RENAME              0x0010
#define COREFILE_EXIST               0x0004
#define COREFILE_EXISTS              0x0004
#define COREFILE_WRITELINE_BUFFERED  0x0001
#define COREFILE_APPEND             (0x0100 | COREFILE_UPDATE)
#define COREFILE_BACKUP              0x1000
#define COREFILE_CREATE_NEW         (0x0200 | COREFILE_CREATE)

/*************** File Close Flags ***********************/
#define CLOSEFILE_ABORT_BACKUP       0x00000001

/*************** Memory allocation flags ***************/
#ifndef zCOREMEM
#define zCOREMEM zCHAR * *
#endif
#define zCOREMEM_ALLOC      0x8000
#define zCOREMEM_FLAG1      0x0100   // Used for debugging
#define zCOREMEM_FLAG2      0x0200   // Used for debugging
#define zCOREMEM_FLAG3      0x0400   // Used for debugging
#define zCOREMEM_FLAG4      0x0800   // Used for debugging


// * Start of Operation Prototypes

zSHORT OPERATION
RegisterZeidonApplication( zPVIEW   pSubtask,
                           zLONG    lSystemAnchorBlock,
                           zLONG    hMainWnd,
                           zLONG    lMsg,
                           zCPCHAR  cpcAppString,
                           zCPCHAR  cpcControl,
                           zLONG    lControl );

//zSHORT OPERATION
//RegisterZeidonAppForThread( LPTASK   lpTask,
//                            zPVIEW   pSubtask,
//                            zCPCHAR  cpcAppString,
//                            zCPCHAR  cpcControl,
//                            zLONG    lControl );

zSHORT OPERATION
ProcessZeidonMessage( zLONG lParm1, zLONG lParm2 );

zSHORT  OPERATION
UnregisterZeidonApplication( zVIEW vTaskView );

// Prototypes from source module kzoedmaa.c

zSHORT OPERATION
TableEntryForInternalValue( zVIEW      lpView,
                            LPDOMAIN   lpDomain,
                            zCPCHAR    cpcContextName,
                            zCPVOID    lpInputValue );

zSHORT OPERATION
TableEntryIntToExt( zPCHAR     pchReturnValue,
                    zVIEW      lpView,
                    LPDOMAIN   lpDomain,
                    zCPCHAR    cpcContext,
                    zCPVOID    lpInternalValue );

zSHORT OPERATION
TableEntryExtToInt( zPVOID     lpReturnValue,
                    zVIEW      lpView,
                    LPDOMAIN   lpDomain,
                    zCPCHAR    cpcContext,
                    zCPCHAR    cpcExternalValue );

zSHORT OPERATION
GetContext( zLPCONTEXT *lpReturnContext, LPDOMAIN lpDomain,
            zCPCHAR cpcContextName );

zSHORT OPERATION
GetDefaultContext( zLPCONTEXT *lpReturnContext, LPDOMAIN lpDomain );

// Prototypes from source module kzoeeraa.c

zSHORT OPERATION
SendDomainError( zVIEW     lpView,
                 LPDOMAIN  lpDomain,
                 zSHORT    nSeverity,
                 zLONG     lMessageID,
                 zLONG     lInfo,
                 zCPCHAR   cpcInfo1,
                 zCPCHAR   cpcInfo2 );

// Prototypes from source module kzoesyaa.c

zLONG OPERATION
fnAllocOperIdx( LPTASK lpTask );

zLONG OPERATION
fnFreeOperIdx( LPTASK lpTask );

zPVOID OPERATION
fnReuseEntity( zPVOID lpViewEntityCsr );

int OPERATION
SysAddressMemory( zLONG hMemory );

// Obsolete ... don't use in new code, use SysMalloc instead.
zLONG OPERATION
SysAllocMemory( zCOREMEM Memory,  zLONG Bytes,
                zLONG    hMemory, unsigned int uMemFlags,
                zCPCHAR  cpcShareName );

zSHORT OPERATION
SysAppendcDirSep( zPCHAR pchString );

zSHORT OPERATION
SysSetFocusToWebCtrl( zVIEW v, zCPCHAR cpcDialog, zCPCHAR cpcWindow,
                      zCPCHAR cpcEntity, zCPCHAR cpcCtrlTag );
zSHORT OPERATION
SysMakeWebFileName( zPCHAR pchReturnName, zLONG lMaxLth, zVIEW v, zLONG lFlags );

zSHORT OPERATION
SysSetWebBannerName( zVIEW v, zCPCHAR cpcDialog, zCPCHAR cpcBannerName );

zSHORT OPERATION
SysGetWebBannerName( zVIEW v, zCPCHAR cpcDialog, zPCHAR pchBannerName, zLONG lMaxLth );

zLONG OPERATION
SysCheckTaskMemory( void );

int   OPERATION
fnSysCloseFile( LPTASK lpTask, zLONG hFile, LPTASK lpOwningTask );
int   OPERATION
SysCloseFile( zVIEW lpTaskView, zLONG hFile, LPTASK lpOwningTask );

zSHORT OPERATION
fnSysCloseFileWithControl( LPTASK lpTask, zLONG lFileHandle,
                           LPTASK lpOwningTask, zLONG lControl );
zSHORT OPERATION
SysCloseFileWithControl( zVIEW lpTaskView, zLONG lFileHandle,
                         LPTASK lpOwningTask, zLONG lControl );

void OPERATION
SysConvertANSI_String( zPCHAR pchAnsiString );

void OPERATION
SysConvertEnvironmentString( zPCHAR pchTarget, zLONG lMaxLth, zCPCHAR pchSource );

zSHORT OPERATION
fnSysCopyFile( LPTASK lpTask, zCPCHAR cpcFileSpecFrom,
               zCPCHAR cpcFileSpecTo, zBOOL bOverwrite );
zSHORT OPERATION
SysCopyFile( zVIEW lpTaskView, zCPCHAR cpcFileSpecFrom,
             zCPCHAR cpcFileSpecTo, zBOOL bOverwrite );

zSHORT OPERATION
SysCreateTempFileName( zPCHAR pchTargetName );

int OPERATION
SysDiagnosticMessage( zVIEW lpTaskView, zCPCHAR cpcTitle,
                      zCPCHAR cpcMessage, int nBeep );

zVOID OPERATION
SysElapsedTimer( zUSHORT idx, zPCHAR pchMsg );

// This function should replace the now deprecated SysFreeMemory.
zVOID OPERATION
SysFree( zPVOID pvMemory );

int  OPERATION
fnSysFreeLibrary( LPTASK lpTask, LPLIBRARY hLibrary, zBOOL bAllUses );
int  OPERATION
SysFreeLibrary( zVIEW lpTaskView, LPLIBRARY hLibrary );

// Obsolete ... don't use in new code, use SysFree instead.
zLONG OPERATION
SysFreeMemory( zLONG hMemory );

void OPERATION
SysGetDateTime( zPCHAR pchReturnDateTime, zLONG lMaxLth );

void OPERATION
SysGetServerDateTime( zVIEW  vSubtask,
                      zPCHAR pchReturnDateTime,
                      zLONG  lMaxLth );
zSHORT OPERATION
SysGetDateTimeDifference( zPLONG  plDiff,
                          zPCHAR  pchEarlyDate,
                          zPCHAR  pchLaterDate,
                          zSHORT  nDiffType );
int OPERATION
SysGetDB_UserID( zVIEW lpView, zPCHAR pchUserID, zLONG lUserLth, zPCHAR pchPassword, zLONG lPasswordLth );

zSHORT  OPERATION
SysGetDomainMessage( zPCHAR pchReturnString, zLONG lMsgID, zSHORT nMaxLth );

zSHORT OPERATION
SysGetEnvVar( zPCHAR pchReturnEnv, zCPCHAR cpcEnvName, zLONG lMaxLth );

void OPERATION
SysGetFileDateTime( zLONG hFile, zPCHAR pchDateTime, zLONG lMaxLth );

zULONG OPERATION
SysGetFilePosition( zLONG  hFile );

zULONG OPERATION
SysGetFileSize( zLONG  hFile );

zPVOID OPERATION
SysGetHandleFromPointer( zPVOID pHandle );

zSHORT OPERATION
SysGetLanguageCode( zPSHORT lpnCountryCode );

int  OPERATION
SysGetLocalDirectory( zPCHAR pchReturnDir );

int  OPERATION
SysGetLocalSysDirectory( zPCHAR pchReturnDir );

void OPERATION
SysGetLongDateFormat( zPCHAR pchReturnString );

zSHORT OPERATION
SysGetNumberFormat( zPCHAR pchReturnThou, zPCHAR pchReturnDecPt,
                    zPLONG plPrecision );

zLONG OPERATION
SysGetOS_Info( zPLONG plSubVersion );

zPVOID OPERATION
SysGetPointerFromHandle( zPVOID pHandle );

zLONG OPERATION
SysGetInstance( LPLIBRARY hLibrary );

zPVOID OPERATION
SysGetProc( LPLIBRARY hLibrary, zCPCHAR cpcProcName );

zLONG OPERATION
SysGetProcessID( zPLONG plThreadID );

zLONG OPERATION
SysGetTaskFromView( zVIEW lpView );

//zLONG OPERATION
//SetTaskAsTransient( zVIEW vSubtask, zLONG lFlag );

zLONG OPERATION
SetTransientTaskProcess( zCPCHAR cpcSessionId, zVIEW vSubtask,
                         zBOOL bOn, zCPCHAR cpcTitle );

void OPERATION
SysGetShortDateFormat( zPCHAR pchReturnString );

zULONG OPERATION
SysGetTickCount( void );

void OPERATION
SysGetTimeFormat( zPCHAR pchReturnString );

int OPERATION
SysGetUserID( zVIEW lpView, zPCHAR pchUserID, zLONG lUserLth, zPCHAR pchPassword, zLONG lPasswordLth );

LPLIBRARY  OPERATION
fnSysLoadLibrary( LPTASK lpTask, zCPCHAR cpcLibraryName );

LPLIBRARY  OPERATION
SysLoadLibrary( zVIEW lpView, zCPCHAR cpcLibraryName );

LPLIBRARY  OPERATION
fnSysLoadLibraryWithErrFlag( LPTASK lpTask, zCPCHAR cpcLibraryName,
                             zLONG lErrFlag );
LPLIBRARY  OPERATION
SysLoadLibraryWithErrFlag( zVIEW lpView, zCPCHAR cpcLibraryName,
                           zLONG lErrFlag );

// This function should replace the now deprecated SysAllocMemory.
zPVOID OPERATION
SysMalloc( zLONG lSize );

zULONG OPERATION
SysMemSize( zPVOID pMemory );

void OPERATION
SysMessageBeep( void );

int OPERATION
fnSysMessageBox( LPTASK lpTask, zCPCHAR cpcTitle,
                 zCPCHAR cpcMessage, int nBeep );
int OPERATION
SysMessageBox( zVIEW lpTaskView, zCPCHAR cpcTitle,
               zCPCHAR cpcMessage, int nBeep );

int OPERATION
SysMessageList( zCPCHAR cpcMessage );

zLONG OPERATION
fnSysOpenFile( LPTASK lpTask, zCPCHAR cpcFileName, int Flags );
zLONG OPERATION
SysOpenFile( zVIEW lpTaskView, zCPCHAR cpcFileName, int Flags );

void  OPERATION
SysParseLine( zPCHAR PortName, zLONG lPortNameLth, zCOREMEM PortValue, zPCHAR InputString );

zLONG OPERATION
SysPositionFile( zLONG hFile, zLONG lPosition );

unsigned int OPERATION
fnSysReadFile( LPTASK lpTask, zLONG lFileHandle,
               zPCHAR pchBuffer, zULONG uMaxlth );
unsigned int OPERATION
SysReadFile( zVIEW lpTaskView, zLONG lFileHandle,
             zPCHAR pchBuffer, zULONG uMaxlth );

int OPERATION
fnSysReadLine( LPTASK lpTask, zCOREMEM lpReturnLine,
               zLONG lFileHandle, zPVOID *ppvFile );
int OPERATION
SysReadLine( zVIEW lpTaskView, zCOREMEM lpReturnLine, zLONG lFileHandle );

zSHORT OPERATION
fnSysReadLineLth( LPTASK lpTask, zCOREMEM lpReturnLine,
                  zLONG lFileHandle, zPVOID *ppvFile, zULONG ulLth );
zSHORT OPERATION
SysReadLineLth( zVIEW lpTaskView, zCOREMEM lpReturnLine,
                zLONG lFileHandle, zULONG ulLth );

// zLONG  OPERATION
// fnSysReadZeidonIni( LPTASK lpTask, zLONG hFile, zCPCHAR cpcGroup,
//                     zPCHAR pchParameter, zPCHAR pchValue );
zLONG  OPERATION
SysReadZeidonIni( zLONG hFile, zCPCHAR cpcGroup,
                  zPCHAR pchParameter, zPCHAR pchValue, zLONG lMaxLth );

zSHORT OPERATION
fnSysRenameFile( LPTASK lpTask, zPCHAR pchFileSpecFrom,
                 zPCHAR pchFileSpecTo, zBOOL bOverwrite );
zSHORT OPERATION
SysRenameFile( zVIEW lpTaskView, zPCHAR pchFileSpecFrom,
               zPCHAR pchFileSpecTo, zBOOL bOverwrite );

zLONG  OPERATION
SysSendOE_Message( zLONG wParam, zLONG lParam );

zSHORT OPERATION
SysSetFileTime( zCPCHAR cpcFileName, zCPCHAR cpcDateTime, zLONG lControl );

int OPERATION
SysSetDB_UserID( zVIEW lpView, zCPCHAR cpcUserID, zCPCHAR cpcPassword );

zSHORT OPERATION
SysSetDefaultTaskForProcess( zVIEW vTaskView );

zSHORT OPERATION
SysSetLanguageCode( zSHORT lpnCountryCode );

int OPERATION
SysSetUserID( LPTASK lpTask, zCPCHAR cpcUserID, zCPCHAR cpcPassword );

zSHORT OPERATION
SysStartHelp( zCPCHAR cpcHelpFile, zCPCHAR cpcHelpID );

zVOID OPERATION
SysStartTimer( zUSHORT idx );

void OPERATION
SysTranslateString( zPCHAR pchString, char cUpperLower );

int  OPERATION
fnSysTruncateFile( LPTASK lpTask, zLONG  hFile );
int  OPERATION
SysTruncateFile( zVIEW lpTaskView, zLONG  hFile );

// void  OPERATION
// fnSysUpdateZeidonIni( LPTASK lpTask, zCPCHAR cpcGroup,
//                       zCPCHAR cpcParameter, zCPCHAR cpcValue );
void  OPERATION
SysUpdateZeidonIni( zCPCHAR cpcGroup,
                    zCPCHAR cpcParameter, zCPCHAR cpcValue );

int OPERATION
SysValidAddress( zPVOID lpAddress, zLONG lLth, zBOOL bWrite );

zSHORT OPERATION
SysValidDirOrFile( zPCHAR pchPath, zSHORT bDirectory,
                   zSHORT bCheckCreate, zSHORT nMaxPathLth );

void OPERATION
SysWait( zUSHORT uMilliseconds );

zULONG OPERATION
fnSysWriteFile( LPTASK lpTask, zLONG lFileHandle,
                zCPCHAR cpcBuffer, zULONG  ulLth );
zULONG OPERATION
SysWriteFile( zVIEW lpTaskView, zLONG lFileHandle,
              zCPCHAR cpcBuffer, zULONG  ulLth );

int OPERATION
fnSysWriteLine( LPTASK lpTask, zLONG lFileHandle,
                zPVOID *ppvFile, zCPCHAR cpcLine );
int OPERATION
SysWriteLine( zVIEW lpTaskView, zLONG lFileHandle, zCPCHAR cpcLine );

int OPERATION
fnSysWriteLineLth( LPTASK lpTask, zLONG lFileHandle, zPVOID *ppvFile,
                   zCPCHAR cpcLine, zULONG ulLth, zBOOL bAppend );
int OPERATION
SysWriteLineLth( zVIEW lpTaskView, zLONG lFileHandle, zCPCHAR cpcLine,
                 zULONG ulLth, zBOOL bAppend );

zSHORT OPERATION
SysStartBrowseOfTaskList( zVIEW vSubtask );
void OPERATION
SysEndBrowseOfTaskList( );

zUSHORT OPERATION
SysGetClientMessage( );

zLONG OPERATION
SysInitApplicationWindow( zLONG   hInstance,
                          zCPCHAR cpcClassName,
                          zCPCHAR cpcWindowTitle );

// Prototypes from source module kzoeataa.c

zSHORT OPERATION
GetAddrForAttribute( zCOREMEM  lpReturnAddr,
                     zVIEW     lpView,
                     zCPCHAR   cpcEntityName,
                     zCPCHAR   cpcAttributeName );

zSHORT OPERATION
StoreValueInRecord( zVIEW        lpView,
                    LPVIEWENTITY lpViewEntity,
                    LPVIEWATTRIB lpViewAttribute,
                    zPVOID       lpValue,
                    zULONG       uLength );

zSHORT OPERATION
StoreBytesInRecord( zVIEW        lpView,
                    LPVIEWATTRIB lpViewAttrib,
                    zPVOID       lpValue,
                    zULONG       uLength,
                    zPCHAR       lpRecord );

zSHORT OPERATION
StoreStringInDerivedAttribute( zVIEW        lpView,
                               zPCHAR       pchEntityName,
                               zPCHAR       pchAttribName,
                               zPCHAR       pchStr );

zSHORT OPERATION
StoreValueInDerivedAttribute( zVIEW        lpView,
                              zPCHAR       pchEntityName,
                              zPCHAR       pchAttribName,
                              zPVOID       lpValue,
                              zULONG       uLength );

zSHORT OPERATION
GetValueFromRecord( zVIEW        lpView,
                    LPVIEWENTITY lpViewEntity,
                    LPVIEWATTRIB lpViewAttribute,
                    zCOREMEM     lpReturnAddr,
                    zPCHAR       pcReturnType,
                    zPULONG      puReturnLength );

zSHORT OPERATION
StoreStringInRecord( zVIEW        lpView,
                     LPVIEWENTITY lpViewEntity,
                     LPVIEWATTRIB lpViewAttribute,
                     zCPCHAR      cpcString );

zSHORT OPERATION
GetStringFromRecord( zVIEW        lpView,
                     LPVIEWENTITY lpViewEntity,
                     LPVIEWATTRIB lpViewAttribute,
                     zPCHAR       pchReturnString,
                     zULONG       uMaxLength );

zVOID OPERATION
ConvertDecimalToString( zPCHAR       pchReturnString,
                        LPVIEWATTRIB lpViewAttrib,
                        zDECIMAL     dDecimal,
                        zCPCHAR      cpcContext );

zSHORT OPERATION
GetAttributeFlags( LPATTRIBFLAGS * plpAttribFlags,
                   zVIEW           lpView,
                   LPVIEWENTITY    lpViewEntity,
                   LPVIEWATTRIB    lpViewAttrib );


// Prototypes from source module kzoeneta.c

zSHORT OPERATION
SfStartNetworks( zVIEW vTaskView, zLONG lControl );

// Prototypes from source module kzoeoiaa.c

zSHORT      OPERATION
SfActivateSysOI_FromFile( zPVIEW   lpReturnView,
                          zCPCHAR  cpcViewOD_Name,
                          zVIEW    lpAppQualView,
                          zCPCHAR  cpcFileName,
                          zLONG    lControl    );

zSHORT      OPERATION
SfActivateSysEmptyOI( zPVIEW  lpReturnView,
                      zCPCHAR cpcViewOD_Name,
                      zVIEW   lpAppQualView,
                      zLONG   lControl );

zSHORT OPERATION
SfWriteOI_ToStream( zVIEW          lpView,
                    zCPCHAR        cpcHeaderName,
                    zLONG          lControl,
                    LPFN_PUTSTREAM lpfnStreamFunc,
                    zPVOID         lpvData );

zSHORT OPERATION
SfActivateOI_FromStream( zPVIEW         lpReturnView,
                         zCPCHAR        cpcViewOD_Name,
                         zVIEW          lpAppQualView,
                         zLONG          lControl,
                         LPFN_GETSTREAM lpfnStreamFunc,
                         zPVOID         lpvData );

// Prototypes from source module kzoeoaaa.c

LPVIEWOD OPERATION
ActivateViewObject( zVIEW  lpView,
                    zCPCHAR cpcViewOD_Name, zBOOL bSystemObject );

zSHORT OPERATION
DropViewObject( zVIEW   lpView,
                zCPCHAR cpcViewOD_Name,
                zBOOL   bSystemObject );

// Prototypes from source module kzoetmaa.c


zSHORT OPERATION
SfCreateSubtask( zPVIEW pvReturnView, zVIEW lpView,
                 zCPCHAR cpcAppName );

zBOOL OPERATION
SfCurrentTaskIsServer( zVIEW );

zSHORT OPERATION
SfCreateSystemSubtask( zPVIEW pvReturnView, zVIEW lpView,
                       zCPCHAR cpcAppName );

zSHORT OPERATION
SfDropSubtask( zVIEW zSubtaskView, zSHORT nCleanup );

zSHORT OPERATION
SfAllocTaskMemory( zVIEW vTaskView, zCOREMEM Memory, zLONG lBytes );
zSHORT OPERATION
SfReAllocTaskMemory( zVIEW vTaskView, zCOREMEM Memory, zLONG lBytes );
zSHORT OPERATION
SfFreeTaskMemory( zPVOID Memory );
zLONG OPERATION
SfGetTaskMemoryLength( zPVOID Address );
zPVOID OPERATION
SfLockTaskMemory( zPVOID Memory );
zPVOID OPERATION
SfUnlockTaskMemory( zPVOID Memory );

zBOOL  OPERATION
SfIsObjectServicesTask( zLONG hTask );

#define  zTASKFLAG_AUDIT  0x0001
#define  zTASKFLAG_DEBUG  0x0002
#define  zTASKFLAG_TRACE  0x0004
#define  zSET_ON   1
#define  zSET_OFF  0

zSHORT OPERATION
SfSetTaskFlag( zVIEW lpView, zSHORT nFlag, zSHORT nSet );

zSHORT OPERATION
SfCloseTaskDatabases( zVIEW vTaskView );

// Prototypes from source module kzoeufaa.c

zSHORT OPERATION
UfDateTimeToString( LPDATETIME lpDateTime, zPCHAR pchReturnString,
                    zSHORT nMaxLth );

zSHORT OPERATION
UfStringToDateTime( zCPCHAR cpcDateTimeString, LPDATETIME lpDateTime );

zSHORT   OPERATION
UfCompareDateTimeToDateTime( LPDATETIME lpDateTime1,
                             LPDATETIME lpDateTime2 );

zSHORT OPERATION
UfAddToDateTime( LPDATETIME   lpDateTime,
                 zLONG        lAmount,
                 zSHORT       nAmountType );

zSHORT OPERATION
UfDateTimeDiff( zPLONG      plDiff,
                LPDATETIME  lpDateTime1,
                LPDATETIME  lpDateTime2,
                zSHORT      nDiffType );

zSHORT OPERATION
UfJulianToGregorian( zCPCHAR cpcJulian, zPCHAR pchGregorian );

zLONG OPERATION
UfGetDayOfWeek( zCPCHAR cpcDateTime );

zLONG OPERATION
UfGetDayOfYear( zCPCHAR cpcDateTime );

zLONG OPERATION
UfGetWeekOfYear( zCPCHAR cpcDateTime );

// Prototypes from source module kzoevlaa.c

zPCHAR OPERATION
TrueName( zCPCHAR cpcName, zSHORT nControl );

zSHORT OPERATION
NameForZKey( zPCHAR pchReturnString, zLONG lZKey );

// Prototypes from source module kzoevmaa.c

zSHORT OPERATION
SfSetSubtaskView( zVIEW lpView, zVIEW vSubtask );

zSHORT OPERATION
SfGetFirstSubtaskView( zPVIEW pvReturnSubtask, zVIEW vTaskView );

zSHORT OPERATION
SfGetNextSubtaskView( zPVIEW pvReturnView, zVIEW vSubtask );

zSHORT OPERATION
SfSetApplicationTask( zVIEW lpTaskView, zLONG lFlags );

zSHORT OPERATION
SfGetUserIdForTask( zVIEW lpTaskView, zPCHAR pchUserId );

zSHORT OPERATION
SfSetUserIdForTask( zVIEW lpTaskView, zCPCHAR cpcUserId );

zSHORT OPERATION
SfTransferView( zVIEW lpView, zVIEW zAppQualView, zSHORT nScope );

zSHORT OPERATION
SfSetApplicationForSubtask( zVIEW vSubtask, LPAPP lpApp );

zSHORT OPERATION
SfGetApplicationForSubtask( LPAPP *lpApp, zVIEW vAnyView );

zSHORT OPERATION
SfGetDefaultContextForDomain( zLPCONTEXT *lpReturnContext,
                              zVIEW      lpView,
                              zCPCHAR    cpcDomainName );
LPTASK OPERATION
SfGetNextTask( LPTASK );

LPTASK OPERATION
SfGetCurrentTask( zVIEW );

zSHORT OPERATION
SfGetTaskInfo( zPCHAR pchReturnString, zLONG lMaxLth, zSHORT nInfoRequest, LPTASK lpTask );

zSHORT OPERATION
SfLockView( zVIEW lpView );

zSHORT OPERATION
SfGetFirstNamedView( zPVIEW  pvReturnView,
                     zPCHAR  pchReturnName,
                     zVIEW   lpView,
                     zSHORT  nLevel );

zSHORT OPERATION
SfGetNextNamedView( zPVIEW   pvReturnView,
                    zPCHAR   pchReturnName,
                    zVIEW    lpView,
                    zSHORT   nLevel );

// Prototypes from source module kzoeneta.c

LPTRACINGFLAGS OPERATION
GetTracingFlags( void );

// Prototypes from source module kzoexmla.c
zSHORT OPERATION
WriteSubobjectToXML( zVIEW         vOI,
                     zCPCHAR       cpcEntityName,
                     zLONG         lControl,
                     LPFN_XMLWRITE lpfnWrite,
                     zPVOID        lpPtr );

zSHORT OPERATION
WriteOI_ToXML( zVIEW         vOI,
               zLONG         lControl,
               LPFN_XMLWRITE lpfnWrite,
               zPVOID        lpPtr );

zSHORT OPERATION
WriteMultipleOIs_ToXML( zVIEW         vOI[],
                        zSHORT        nViewCount,
                        zLONG         lControl,
                        LPFN_XMLWRITE lpfnWrite,
                        zPVOID        lpPtr );

zSHORT OPERATION
ActivateOI_FromXML( zPVIEW       lppView,
                    zPCHAR       pchOD_Name,
                    zVIEW        vSubtask,
                    zLONG        lControl,
                    LPFN_XMLREAD pfnRead,
                    zPVOID       lpPtr );


zSHORT OPERATION
SfCheckOI_Integrity( zVIEW lpView, zLONG lControl );

// *************** END   OF PROTECTED SYSTEM PROTOTYPES
