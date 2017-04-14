#ifndef  KZOENGAA_DEF
#define  KZOENGAA_DEF

//KZOENGAA.H - Prototypes for documented end-user Object Services
//             Operations


/*
CHANGE LOG
2003.06.20  DonC
   Added InitWebSessionObject, InitWebPage and AddWebControlSubobject.

2002.10.20  DGC
   Added GenerateQualFromEntityList().

2002.06.21  DonC
   Added FormatSubobjectOnDocWithXRP.

2002.01.28  HH
   added SysRoundDecimal.

2002.01.23  RG
   Make available AcceptAllTemporalSubobjects and
   CancelAllTemporalSubobjects for VML

2002.01.15  HH
   Added SetDatabaseUser.

2001.12.06  DGC
   Added ActivateOI_FromXML_File.

2001.11.13  HH
   Added zDB_DEADLOCK.

2001.10.11  DGC  10b
   Added code for GetViewFlags().

2001.10.09  DGC
   Added MiHasPersistentChanges( zVIEW lpView )

2001.09.04  PAS
   added 7 UfZProbeXXXXX functions.

2001.08.07  HH
   Added SubobjectVersionUpdated.

2001.08.01  DGC  10b
   Added zOCE_STATE_MULTIPLE.

2001.07.23  DGC  10b
   Added SetBlobFromFile and WriteBlobToFile.

2001.07.05  DGC
   Added an error message number.

2001.05.15  DGC
   Added code for SetCursorFirstEntityByEntityKey().

2001.05.03  HH
   added AppendViewCluster.

2001.04.06  DGC
   Added a zQUAL_ATTR_HIDDEN flag.

2001.04.06  DGC
   Added GetEntityKey().

2001.03.29  PAS
   Added zENCODE_BLOBS and zNO_NULL_STRING_TERM to be used in CommitOI_ToFile

2001.02.28  DGC
   Added zSET_INCR_ATTR_UPDATED and zSET_INCR_ATTR_NOT_UPDATED.

2001.01.27  HH
   added CursorListener interface.

2001.01.17  HH
   added defines for euro sign, paragraph sign, at sign.

2000.11.28 - 2000.12.19 HH
   const char change ZeidonStringCompare, ZeidonStringConcat,
   ZeidonStringConvertFromNumber, ZeidonStringCopy,
   FormatSubobjectOnDoc, SysConvertStringToDecimal


2000.11.08  DGC 10b
   Added mutex flags.

2000.10.20  SR Z2000
    Included following defines:
   zSHORT_MESSAGE_LTH, zMAX_MESSAGE_LTH, zLONG_MESSAGE_LTH

2000.09.01  DGC 10b
   Added a flag zNEW_OBJECT_NAME.

2000.07.27  DGC 10b
   Added IncludeSubobjectFromSubobjectEx.

2000.05.04  DGC
   Changed signature of LoadEntity().

2000.05.02  DGC  10b
   Added MiGetActivateFlags().

2000.04.27 DGC  10b
   Added code to allow user to query mutex status.

2000.04.17  HH
   changed VML defines (TAB->zTAB).

1999.10.08  DGC  10a
   Added SetViewFlags().

1999.08.17  DGC  10a
   Added zSET_INCRE_DELETED flag.

1999.07.21  DGC  10a
   Made Commit cluster changes.

1999.06.01  DGC  10a
   Added GetAttributeFlags() stuff.

1999.05.25  DGC  10a
   Added GetEntityNameForHierarchicalCsr().

   Added zIGNORE_ERROR_358.  See code in SetCursorFirstEntityByString().

1999.05.07  DGC  10a
   Removed reference of zBINARY.

1999.04.07  DGC  10a
   Added definition of zDME_NOT_HANDLED, zDME_SET_ATTR_TO_ATTR.
   Removed definitions of NetSendBootstrapFile() and NetCallTransformation().

1999.01.19  DGC
   Started adding NetCallOperation() code.

*/

#ifdef __cplusplus
extern "C"
{
#endif

//#ifndef _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS  1 // remove "This function or variable may be unsafe." warnings
//#endif

/* definition to expand macro then apply to pragma message */
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

#include "kzoeenaa.h"
/*
#ifndef zstrcpy
   #error zstrcpy is not defined after kzoeenaa.h
#else
   #pragma message("after kzoeenaa.h ===> " VAR_NAME_VALUE(zstrcpy))
#endif
*/
#include "kzoegdef.h"
/*
#ifndef zstrcpy
   #error zstrcpy is not defined after kzoegdef.h
#else
   #pragma message("after kzoegdef.h ===> " VAR_NAME_VALUE(zstrcpy))
#endif
*/
#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

// Following define the space (in chars) needed to hold text for
// Message Boxes
// According to zMAX_FILENAME_LTH in kzoenaa.h the following includes
// should not include the null-terminator.
#define zSHORT_MESSAGE_LTH    256       /* Max lth for short msg.text  */
#define zMAX_MESSAGE_LTH      512       /* Max lth for normal msg.text */
#define zLONG_MESSAGE_LTH    1024       /* Max lth for long msg.text */

// defines for end user removing the LP specification from published
// core types (they do not care nor should they know whether a type
// is a pointer or not)
typedef struct ViewStruct ViewRecord;
typedef ViewRecord * zVIEW;
typedef zVIEW * zPVIEW;

typedef struct ViewClusterStruct ViewClusterRecord;
typedef ViewClusterRecord * LPVIEWCLUSTER;
struct ViewClusterStruct
{
   zVIEW vOI;
   zLONG lControl;
};

// * Start of Operation Prototypes

zSHORT OPERATION
DisableTask( zVIEW lpView );

zSHORT  OPERATION
EnableTask( zVIEW lpView );

#define  zTYPE_STRING    'S'
#define  zTYPE_INTEGER   'L'
#define  zTYPE_DECIMAL   'M'
#define  zTYPE_BLOB      'B'
#define  zTYPE_DATETIME  'T'
#define  zTYPE_PIC       'P'
#define  zTYPE_FIXEDCHAR 'F'

// The following are really physical data types--ie. used for storing data to
// a database.  Since almost all databases will support Dates and Times we
// include them here for completeness.  Core itself should never be using these
// values, just the DB-Handlers.
#define  zTYPE_DATE     'D'
#define  zTYPE_TIME     'I'

// VML Defines
#define  NEW_LINE        "\r\n"   // not removed for compatibility
#define  zNEW_LINE       "\r\n"
#define  QUOTES          "\""     // not removed for compatibility
#define  zQUOTES         "\""
#define  zTAB            "\t"
#define  zEURO_SIGN      "\x80"
#define  zPARAGRAPH_SIGN "\xa7"
#define  zAT_SIGN        "\x40"  // even DG understands "Klammeraffe"
#define  zPIPE           "\x7c"  // vml doubles the | character
#define  zSIZEOFLONG     sizeof( zLONG )

#define  zAPPL_NAME                   0
#define  zAPPL_DIR_LIB                1
#define  zAPPL_DIR_OBJECT             2
#define  zAPPL_DIR_LOCAL              3
#define  zAPPL_DIR_SHARED             4
#define  zAPPL_DIR_QLPLR              5
#define  zAPPL_DIR_SOURCE             6

#define  zTASK_DIALOG                 1
#define  zTASK_COMMAND                2

#define  zLEVEL_SUBTASK     0x0001
#define  zLEVEL_TASK        0x0002
#define  zLEVEL_APPLICATION 0x0004
#define  zLEVEL_SYSTEM      0x0008
#define  zLEVEL_ANY         0x000F
#define  zLEVEL_SAME        0x0400

#define  zNAME_AUTODROP     0x0040   // For SetNameFromView

// Activate flags.
#define  zSINGLE                 0x00000000L
#define  zMULTIPLE               0x00000100L
#define  zNOI_OKAY               0x00000200L
#define  zNOENQUEUE              0x00000400L
#define  zREADONLY               0x00000800L
#define  zIGNORE_ENTITY_ERRORS   0x00001000L
#define  zIGNORE_ATTRIB_ERRORS   0x00002000L
#define  zACTIVATE_OPTION        0x00004000L   // Meaning depends on other flags.
#define  zACTIVATE_OPTION2       0x00008000L   // Meaning depends on other flags.
#define  zACTIVATE_NOCONSTRAINTS 0x01000000L   // Don't execute activate constraints.
#define  zNEW_OBJECT_NAME        0x02000000L   // Used by SetOI_FromBlob.
#define  zSINGLE_FOR_UPDATE      0x04000000L   // For locking--activate w/ lock.
#define  zACTIVATE_CONTINUE      0x08000000L   // Continue previous activate.
#define  zACTIVATE_LOCAL         0x40000000L   // Forces act/commit to be local.
#define  zACTIVATE_SYSTEM        0x20000000L   // Activates a system object
#define  zACTIVATE_ROOTONLY      0x10000000L

#define  zIGNORE_ERRORS        (zIGNORE_ENTITY_ERRORS | zIGNORE_ATTRIB_ERRORS)
#define  zACTIVATE_ROOTONLY_MULTIPLE (zACTIVATE_ROOTONLY | zMULTIPLE)
#define  zACTIVATE_ROOTONLY_CONTINUE (zACTIVATE_ROOTONLY | zACTIVATE_CONTINUE | zMULTIPLE)
#define  zACTIVATE_MULTIPLE_CONTINUE (zACTIVATE_CONTINUE | zMULTIPLE)

// Following for internal use only.  It makes some code a little easier
// to understand.
#define  zACTIVATE_WITH_LOCKING      zSINGLE_FOR_UPDATE

#define zMAXEL  32  // max encrypt length

// Commit OI to file flags.
#define  zASCII                  0x00000000L
#define  zINCREMENTAL            0x00010000L
#define  zCOMPRESSED             0x00020000L   // Store in compressed form.
#define  zSAVE_CURSORS           0x00040000L   // Save cursor positions.
#define  zENTITY_TAGS            0x00080000L   // Write entity tags (pointers).
#define  zWRITE_KEYS_ONLY        0x00100000L   // Write key attrs only.
#define  zENTITY_KEYS            0x00200000L   // Write entity keys.
#define  zENCODE_BLOBS           0x00400000L   // Encode blobs from binary to ASCII
#define  zNO_NULL_STRING_TERM    0x00800000L   // Don't use null terminator for strings with length
#define  zUSE_OLD_LINK_CARDS     0x01000000L   // Use the old style 'link cards' to indicate linked EIs.

// Commit OI to DB flags.
#define  zCOMMIT_NOCLEANUP          0x00000100L   // Don't clean up deleted instances.
#define  zCOMMIT_FORCETRAN          0x00000400L   // Force commit to be it's own trans.
#define  zCOMMIT_DROPLOCKSONLY      0x00000800L   // Drop pessimistic locks only.
#define  zCOMMIT_KEEPLOCKS          0x00001000L   // Don't remove pessimistic locks.
#define  zCOMMIT_DROPVIEW           0x00002000L   // Drop the views during DropCluster
#define  zCOMMIT_DROPOBJECTINSTANCE 0x00004000L   // Drop the OI during DropCluster
#define  zCOMMIT_NOCONSTRAINTS      0x01000000L   // Don't execute commit constraints.

#define  zMSGQ_OBJECT_CONSTRAINT_INFORMATION 50
#define  zMSGQ_OBJECT_CONSTRAINT_WARNING  100
#define  zMSGQ_DOMAIN_ERROR               200
#define  zMSGQ_OBJECT_CONSTRAINT_ERROR    300
#define  zMSGQ_REQUIRED_DATA_ITEM_ERROR   400
#define  zMSGQ_MODAL_ERROR                500
#define  zMSGQ_SYSTEM_ERROR              1000

#define  zMSGQ_PROCESS_ACCEPT        1
#define  zMSGQ_PROCESS_COMMIT        2
#define  zMSGQ_PROCESS_DOMAIN        3

#define  zCURSOR_NULL               -3
#define  zCURSOR_UNDEFINED          -2
#define  zCURSOR_UNCHANGED          -1
#define  zCURSOR_SET                 0
#define  zCURSOR_SET_NEWPARENT       1
#define  zCURSOR_SET_RECURSIVECHILD  2

#define  zPOS_FIRST        ((zSHORT) 1)
#define  zPOS_LAST         ((zSHORT) 2)
#define  zPOS_NEXT         ((zSHORT) 3)
#define  zPOS_AFTER        ((zSHORT) 3)
#define  zPOS_PREV         ((zSHORT) 4)
#define  zPOS_BEFORE       ((zSHORT) 4)
#define  zPOS_ABS          ((zSHORT) 0x0007L)
#define  zPOS_RELATIVE     ((zSHORT) 0x0008L)

#define  zINCLUDE_WITHCOPY           0x00000001

#define  zREPOS_NONE                 0
#define  zREPOS_FIRST                1
#define  zREPOS_LAST                 2
#define  zREPOS_NEXT                 3
#define  zREPOS_AFTER                3
#define  zREPOS_PREV                 4
#define  zREPOS_BEFORE               4

#define  zDERIVED_SET                1
#define  zDERIVED_GET                2

#define  zDME_NOT_HANDLED                  -10
#define  zDME_SET_ATTRIBUTE                  1
#define  zDME_GET_VARIABLE                   2
#define  zDME_COMPARE_ATTRIBUTE              3
#define  zDME_GET_FIRST_TBL_ENT_FOR_ATTR     4
#define  zDME_GET_NEXT_TBL_ENT_FOR_ATTR      5
#define  zDME_SET_ATTRIBUTE_VALUE_NEXT       6
#define  zDME_SET_ATTRIBUTE_VALUE_PREV       7
#define  zDME_ADD_TO_ATTRIBUTE               8
#define  zDME_GET_COMPARE_VALUE              9
#define  zDME_VALIDATE_LPDATA               10
#define  zDME_SET_ATTR_FROM_ATTR            11
#define  zDME_SET_ATTR_TO_ATTR              12
#define  zDME_GET_ATTR_DISPLAY_LENGTH       13

#define  zDM_TYPE_TABLE       'T'
#define  zDM_TYPE_ALGORITHM   'A'
#define  zDM_TYPE_EXPRESSION  'E'
#define  zDM_TYPE_FORMAT      'F'

#define  zSET_NULL                0x00
#define  zSET_KEYS                0x01
#define  zSET_NOTNULL             0x02
#define  zSET_ALL                 zSET_NULL | zSET_KEYS | zSET_NOTNULL
#define  zSET_SRCNOTNULL          0x04

#define  zCALL_ERROR               -16
#define  zCONSTRAINT_VIOLATION     -12
#define  zCALL_MIN_INFORC          -10
#define  zDB_UNAVAIL               -2
#define  zDB_DEADLOCK              -3
#define  zDUPLICATE_ROOT           -4
#define  zOPTIMISTIC_LOCK_ERROR    -5
#define  zLOCK_ERROR               -5
#define  zNETWORK_ERROR            -6
#define  zMEMORY_LIMIT             -7

#define  zQUAL_EQUAL              0x00000010L
#define  zQUAL_GREATER_THAN       0x00000020L
#define  zQUAL_LESS_THAN          0x00000040L
#define  zQUAL_NOT                0x00000080L
#define  zQUAL_OPERATOR           0x000000F0L
#define  zQUAL_INTEGER            0x00000100L
#define  zQUAL_DECIMAL            0x00000200L
#define  zQUAL_STRING             0x00000400L
#define  zQUAL_DATETIME           0x00000800L
#define  zQUAL_ENTITYATTR         0x00001000L
#define  zQUAL_ENTITYCSR          0x00200000L
#define  zQUAL_ENTITYKEY          0x00800000L
#define  zQUAL_ATTR_NULL          0x00008000L
#define  zQUAL_ATTR_HIDDEN        0x01000000L
#define  zQUAL_OPERAND            0x00009F00L
#define  zQUAL_SELECTED           0x00002000L
#define  zQUAL_UNSELECTED         0x00004000L
#define  zTEST_CSR_RESULT         0x00010000L
#define  zRECURS                  0x00020000L
#define  zQUAL_ZKEYS              0x00040000L
#define  zQUAL_SCOPE_OI           0x00080000L
#define  zSPARENT_KEEPCHILDREN    0x00100000L
#define  zIGNORE_ERROR_358        0x00400000L
#define  zLBITS                   0xFFFFFFFFL

#define  zSCOPE_OI  (zPCHAR) 0x0001 // C autocasts to zCPCHAR just fine

#define  zSET_INCR_CREATED          0x0002
#define  zSET_INCR_PERSISTENT       0x0004
#define  zSET_INCR_UPDATED          0x0008
#define  zSET_INCR_NOT_UPDATED      0x0010
#define  zSET_INCR_INCLUDED         0x0020
#define  zSET_INCR_NOT_INCLUDED     0x0040
#define  zSET_INCR_CURSORPOS        0x0080
#define  zSET_INCR_OWNERSHIP        0x0100        // No longer used.
#define  zSET_INCR_HANGING_ENTITY   0x0800
#define  zSET_INCR_TEMPORAL_ENTITY  0x4000
#define  zSET_INCR_DELETED          0x8000
#define  zSET_INCR_ATTR_UPDATED     0x1000
#define  zSET_INCR_ATTR_NOT_UPDATED 0x2000

#define  zACCEPT_NULL_ENTITY       0x0001
//#define  zZKEYS_INPUT              0x0002       // No longer used.
#define  zVALIDATE                 0x0004
#define  zUSE_DEFAULT_CONTEXT      0x0008
#define  zIGNORE_KEYS              0x0010
#define  zUSE_TASK                 0x1000

#define  zSHOW_ZKEY                 1

#define  zVAR_SET                   0
#define  zVAR_NULL                  -1
#define  zENTITY_NULL               -2

#define  zECE_ACCEPT                1
#define  zECE_CANCEL                2
#define  zECE_CREATE                3
#define  zECE_DELETE                4
#define  zECE_EXCLUDE               5
#define  zECE_INCLUDE               6

#define  zOCE_ACTIVATE              1
#define  zOCE_ACTIVATE_EMPTY        2
#define  zOCE_COMMIT                3
#define  zOCE_DROPOI                4

#define  zOCE_STATE_FILE            0x0001
#define  zOCE_STATE_SHUTDOWN        0x0002
#define  zOCE_STATE_SYSTEM          0x0004
#define  zOCE_STATE_NOI             0x0008
#define  zOCE_STATE_MULTIPLE        0x0010

#define  zTES_NONE                  0
#define  zTES_SUBOBJECT_CHILD       1
#define  zTES_TEMPORAL              2
#define  zTES_SUBOBJECT_ROOT        3

#define  zDT_YEAR                   0
#define  zDT_MONTH                  1
#define  zDT_DAY                    2
#define  zDT_HOUR                   3
#define  zDT_MINUTE                 4
#define  zDT_SECOND                 5

#define  zZEIDON_NAME_LTH           32

// A list of all OS's supported by Zeidon.
#define  zOS_WINDOWS                1
#define  zOS_WINDOWS95              2
#define  zOS_WINDOWSNT              3
#define  zOS_OS2                    4
#define  zOS_MVS                    5
#define  zOS_UNIX                   6

// Mutex control values.
#define  zMUTEX_PROCESS             0x00000000
#define  zMUTEX_THREAD              0x00000001
#define  zMUTEX_SAMETASK            0x00000002
#define  zMUTEX_UNLOCK_DELETE       0x00001000

// View flags.
#define zVF_MESSAGEONDROP           0x00000001
#define zVF_TRACEONDROP             0x00000002

zSHORT OPERATION
GetApplDirectoryFromView( zPCHAR pchReturnDirectory,
                          zVIEW  lpView,
                          zSHORT nDirectory,
                          zSHORT nMaxLth );

zSHORT OPERATION
SetDatabaseUser( zVIEW lpView, zCPCHAR cpcUser, zCPCHAR cpcPasswd );

void OPERATION
OperationCount( zVIEW vTaskView, zSHORT nOpt );

void OPERATION
TraceLineI( zCPCHAR String, zLONG lValue );

void OPERATION
TraceLineX( zCPCHAR String, zULONG lValue );

void OPERATION
TraceBlob( zCPCHAR cpcMessage, zPVOID pvBlob, zLONG lBlobLth );

#define TraceLineV( s, v ) TraceLine( "%s 0x%08x", s, v );
#define TraceLineP( s, p ) TraceLine( "%s 0x%08x", s, p );

zSHORT OPERATION
DisplayEntityInstance( zVIEW lpView, zCPCHAR cpcEntityName );

zSHORT OPERATION
DisplayEntityInstancePath( zVIEW lpView, zCPCHAR cpcEntityName );

zSHORT OPERATION
DisplayObjectInstance( zVIEW lpView, zCPCHAR cpcScopeEntity,
                       zCPCHAR cpcEntityName );

void OPERATION
DisplayOpenFiles( zCPCHAR cpcTitle, zPVOID hTask );

void OPERATION
TraceLineS( zCPCHAR Title, zCPCHAR String );

void VARYOPER
TraceLine( zCPCHAR cpcFormat, ... );

void OPERATION
TraceBuffer( zCPCHAR cpcPrefix, zPVOID pvBuffer, zULONG uLth );

zSHORT OPERATION
DisplayObjectDef( zVIEW lpPtr, zSHORT nControl );

zSHORT OPERATION
IssueError( zVIEW     lpView,
            zSHORT    nSeverity,
            zSHORT    nID,
            zCPCHAR   cpcMessage );

zSHORT OPERATION
IssueOE_Error( zVIEW        lpView,
               zSHORT       nSeverity,
               zSHORT       nID,
               zLONG        lMsgType,
               zLONG        lLong,
               zCPCHAR      cpcMessage1,
               zCPCHAR      cpcMessage2 );
zSHORT OPERATION
ActivateEmptyObjectInstance( zPVIEW  lpReturnView,
                             zCPCHAR cpcViewOD_Name,
                             zVIEW   lpAppQualView,
                             zLONG   lControl );

zSHORT OPERATION
ActivateObjectInstance( zPVIEW  lpReturnView,
                        zCPCHAR cpcViewOD_Name,
                        zVIEW   lpAppQualView,
                        zVIEW   lpQualView,
                        zLONG   lControl );

zSHORT OPERATION
ActivateOI_FromFile( zPVIEW  lpReturnView,
                     zCPCHAR cpcViewOD_Name,
                     zVIEW   lpAppQualView,
                     zCPCHAR cpcFileName,
                     zLONG   lControl );

zSHORT OPERATION
ActivateOI_FromXML_File( zPVIEW  lpReturnView,
                         zCPCHAR cpcViewOD_Name,
                         zVIEW   lpAppQualView,
                         zCPCHAR cpcFileName,
                         zLONG   lControl );

zSHORT OPERATION
ActivateOI_FromOI( zPVIEW    lpReturnView,
                   zVIEW     lpActiveView,
                   zLONG     lControl );
zSHORT OPERATION
ActivateOI_FromOI_ForTask( zPVIEW    lpReturnView,
                           zVIEW     lpActiveView,
                           zVIEW     lpTaskView,
                           zLONG     lControl );

zSHORT OPERATION
CommitObjectInstance( zVIEW lpView );

zOPER_EXPORT zSHORT OPERATION
CommitMultipleOIs( LPVIEWCLUSTER lpViewCluster,
                   zSHORT        nViewCount,
                   zPSHORT       pnViewErrorIdx,
                   zLONG         lControl );

zSHORT OPERATION
CreateViewCluster( zVIEW vTaskView, zPLONG lpArray );

zSHORT OPERATION
DropViewCluster( zLONG lpArray );

zSHORT OPERATION
AddToViewCluster( zLONG lArray, zVIEW lpView, zLONG lControl );

zSHORT OPERATION
AppendViewCluster( zLONG lTargetArray, zLONG lSourceArray );

zSHORT OPERATION
AddViewToViewCluster( zLONG lArray, zVIEW lpView );

zSHORT OPERATION
CommitMultipleObjectInstances( zLONG lArray, zPLONG lpErrorIndex );

zSHORT OPERATION
CommitOI_ToFile( zVIEW lpView, zCPCHAR cpcFilename, zLONG lControl );

zSHORT OPERATION
CommitOI_ToXML_File( zVIEW lpView, zCPCHAR cpcFilename, zLONG lControl );

zSHORT OPERATION
CommitSubobjectToXML_File( zVIEW   vOI,
                           zCPCHAR cpcFileName,
                           zCPCHAR cpcSubobjectRoot,
                           zLONG   nFlags );

zSHORT  OPERATION
GenerateQualFromEntityList( zPVIEW pvQual,
                            zVIEW  vEntityList,
                            zPCHAR pchEntityName,
                            zPCHAR pchScoping,
                            zLONG  lControl );

zSHORT OPERATION
DropObjectInstance( zVIEW lpView );

zSHORT OPERATION
SetViewReadOnly( zVIEW  lpView );

zSHORT OPERATION
SetViewFlags( zVIEW  lpView, zLONG lControl );

zLONG OPERATION
GetViewFlags( zVIEW  lpView );

zSHORT OPERATION
SetViewUpdate( zVIEW  lpView );

zSHORT OPERATION
CreateViewFromView( zPVIEW lpReturnView, zVIEW lpSrcView );
zSHORT OPERATION
CreateViewFromViewForTask( zPVIEW lpReturnView, zVIEW lpSrcView, zVIEW lpTaskView );
zSHORT OPERATION
CreateViewTrace( zCPCHAR cpcMsg, zPVIEW lpReturnView, zVIEW lpSrcView, zVIEW lpTaskView );

zSHORT OPERATION
SfCreateSysViewFromView( zPVIEW lpReturnView, zVIEW  lpSrcView );

zSHORT OPERATION
SetViewFromView( zVIEW zTgtView, zVIEW zSrcView );

zVIEW OPERATION
SetDefaultViewForActiveTask( zVIEW vDefault, zLONG lFlag );
zVIEW OPERATION
GetDefaultViewForActiveTask( );

zSHORT OPERATION
GetViewByName( zPVIEW       zpReturnView,
               zCPCHAR      cpcName,
               zVIEW        lpView,
               zSHORT       nLevel );

zSHORT OPERATION
SetNameForView( zVIEW       lpView,
                zCPCHAR     cpcName,
                zVIEW       zSubtaskView,
                zSHORT      nLevel );

zVOID  OPERATION
GarbageCollectViews( zVIEW  lpTaskView,
                     zLONG  lpDropApp );

zSHORT OPERATION
DropNameForView( zVIEW      lpView,
                 zCPCHAR    cpcName,
                 zVIEW      zSubtaskView,
                 zSHORT     nLevel );

zSHORT OPERATION
CreateViewForSubtaskByName( zVIEW   zSrcView,
                            zVIEW   zSubtaskView,
                            zCPCHAR cpcName );

zSHORT OPERATION
GetNameForView( zPCHAR      pchReturnName,
                zVIEW       lpView,
                zVIEW       zSubtaskView,
                zSHORT      nLevel );

zSHORT OPERATION
DropView( zVIEW lpView );
zSHORT OPERATION
DropViewTrace( zCPCHAR cpcMsg, zVIEW lpView );

zSHORT OPERATION
SetViewToSubobject( zVIEW lpView, zCPCHAR cpcSubobjectEntityName );

zSHORT OPERATION
ResetViewFromSubobject( zVIEW lpView );

zSHORT OPERATION
ResetViewFromSubobjectTop( zVIEW lpView );

zSHORT OPERATION
ResetViewFromSubobjectWithoutError( zVIEW  lpView );

zSHORT OPERATION
ResetView( zVIEW lpView );

zSHORT OPERATION
ResetViewPositions( zVIEW  lpView );

zSHORT OPERATION
CheckExistenceOfEntity( zVIEW lpView, zCPCHAR cpcEntityName );

zSHORT OPERATION
CheckEntityInView( zVIEW lpView, zCPCHAR cpcEntityName );

zSHORT OPERATION
CompareEntitiesIgnoringAttrs( zVIEW lpTgtView, zCPCHAR cpcTgtEntityName,
                              zVIEW lpSrcView, zCPCHAR cpcSrcEntityName,
                              zPCHAR pchAttrList );
zSHORT OPERATION
CompareEntityToEntity( zVIEW lpTgtView, zCPCHAR cpcTgtEntityName,
                       zVIEW lpSrcView, zCPCHAR cpcSrcEntityName );

zSHORT OPERATION
CompareOI_ToOI( zVIEW lpTgtView, zVIEW lpSrcView );

zSHORT OPERATION
CreateEntity( zVIEW lpView, zCPCHAR cpcEntityName, zSHORT nPosition );

zULONG OPERATION
GetEntityKey( zVIEW lpView, zCPCHAR cpcEntityName );

zSHORT OPERATION
LoadEntity( zVIEW   lpView,
            zCPCHAR cpcEntityName,
            zSHORT  nPosition,
            zPPCHAR plpRecord );

zSHORT OPERATION
DeleteEntity( zVIEW lpView, zCPCHAR cpcEntityName, zSHORT nPosition );

zSHORT OPERATION
DropEntity( zVIEW lpView, zCPCHAR cpcEntityName, zSHORT nPosition );

zSHORT OPERATION
ExcludeEntity( zVIEW lpView, zCPCHAR cpcEntityName, zSHORT nPosition );


zSHORT OPERATION
CreateTemporalEntity( zVIEW lpView, zCPCHAR cpcEntityName, zSHORT nPosition );

zSHORT OPERATION
CreateTemporalSubobjectVersion( zVIEW   lpView,
                                zCPCHAR cpcEntityName );

zSHORT OPERATION
AcceptSubobject( zVIEW   lpView,
                 zCPCHAR cpcEntityName );

zOPER_EXPORT zSHORT OPERATION
AcceptAllTemporalSubobjects( zVIEW  lpView );

zSHORT OPERATION
CancelSubobject( zVIEW   lpView,
                 zCPCHAR cpcEntityName );

zOPER_EXPORT zSHORT OPERATION
CancelAllTemporalSubobjects( zVIEW  lpView );

zSHORT OPERATION
IncludeSubobjectFromSubobject( zVIEW   zTgtView,
                               zCPCHAR cpcTgtEntityName,
                               zVIEW   zSrcView,
                               zCPCHAR cpcSrcEntityName,
                               zSHORT  nPosition );

zSHORT OPERATION
IncludeSubobjectFromSubobjectEx( zVIEW   lpTgtView,
                                 zCPCHAR cpcTgtEntityName,
                                 zVIEW   lpSrcView,
                                 zCPCHAR cpcSrcEntityName,
                                 zSHORT  nPosition,
                                 zLONG   lControl );
zSHORT OPERATION
MoveSubobject( zVIEW   lpTgtView,
               zCPCHAR cpcTgtEntityName,
               zVIEW   lpSrcView,
               zCPCHAR cpcSrcEntityName,
               zSHORT  nPosition,
               zSHORT  nSrcPosition );

zSHORT OPERATION
SetIncrementalUpdateFlags( zVIEW   lpView,
                           zCPCHAR cpcEntityName,
                           zSHORT  nOption );

zSHORT OPERATION
GetIncrementalUpdateFlags( zVIEW   lpView,
                           zCPCHAR cpcEntityName,
                           zSHORT  nOption );

zSHORT OPERATION
SetCursorNextEntity( zVIEW    lpView,
                     zCPCHAR  cpcEntityName,
                     zCPCHAR  cpcScopingEntityName );

zSHORT OPERATION
SetCursorPrevEntity( zVIEW    lpView,
                     zCPCHAR  cpcEntityName,
                     zCPCHAR  cpcScopingEntityName );


zSHORT OPERATION
SetCursorFirstEntity( zVIEW    lpView,
                      zCPCHAR  cpcEntityName,
                      zCPCHAR  cpcScopingEntityName );

zSHORT OPERATION
SetCursorLastEntity( zVIEW     lpView,
                     zCPCHAR   cpcEntityName,
                     zCPCHAR   cpcScopingEntityName );
zSHORT OPERATION
SetCursorScopeOI( zVIEW   lpView,
                  zCPCHAR cpcEntityName,
                  zSHORT  nPos );

zSHORT OPERATION
SetCursorFirstEntityByString( zVIEW     lpView,
                              zCPCHAR   cpcEntityName,
                              zCPCHAR   cpcAttributeName,
                              zCPCHAR   cpcStringValue,
                              zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorNextEntityByString( zVIEW     lpView,
                             zCPCHAR   cpcEntityName,
                             zCPCHAR   cpcAttributeName,
                             zCPCHAR   cpcStringValue,
                             zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorFirstEntityByInteger( zVIEW     lpView,
                               zCPCHAR   cpcEntityName,
                               zCPCHAR   cpcAttributeName,
                               zINTEGER  lIntegerValue,
                               zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorNextEntityByInteger( zVIEW     lpView,
                              zCPCHAR   cpcEntityName,
                              zCPCHAR   cpcAttributeName,
                              zINTEGER  lIntegerValue,
                              zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorFirstEntityByDecimal( zVIEW     lpView,
                               zCPCHAR   cpcEntityName,
                               zCPCHAR   cpcAttributeName,
                               zDECIMAL  dDecimalValue,
                               zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorNextEntityByDecimal( zVIEW     lpView,
                              zCPCHAR   cpcEntityName,
                              zCPCHAR   cpcAttributeName,
                              zDECIMAL  dDecimalValue,
                              zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorFirstEntityByAttr( zVIEW     lpView,
                            zCPCHAR   cpcEntityName,
                            zCPCHAR   cpcAttributeName,
                            zVIEW     zSrcView,
                            zCPCHAR   cpcSrcEntityName,
                            zCPCHAR   cpcSrcAttributeName,
                            zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorNextEntityByAttr( zVIEW     lpView,
                           zCPCHAR   cpcEntityName,
                           zCPCHAR   cpcAttributeName,
                           zVIEW     zSrcView,
                           zCPCHAR   cpcSrcEntityName,
                           zCPCHAR   cpcSrcAttributeName,
                           zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorFirstEntityByEntityCsr( zVIEW     lpView,
                                 zCPCHAR   cpcEntityName,
                                 zVIEW     zSrcView,
                                 zCPCHAR   cpcSrcEntityName,
                                 zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetCursorNextEntityByEntityCsr( zVIEW     lpView,
                                zCPCHAR   cpcEntityName,
                                zVIEW     zSrcView,
                                zCPCHAR   cpcSrcEntityName,
                                zCPCHAR   cpcScopingEntityName );

zSHORT OPERATION
SetEntityCursor( zVIEW     lpView,
                 zCPCHAR   cpcEntityName,
                 zCPCHAR   cpcAttributeName,
                 zLONG     lControl,
                 zCPVOID   pQualValue,
                 zCPCHAR   cpcSrcEntityName,
                 zCPCHAR   cpcSrcAttributeName,
                 zLONG     lRelPosition,
                 zCPCHAR   cpcScopingEntityName,
                 zCPCHAR   cpcContextName );

zSHORT OPERATION
MiGetDateTimeForOI( zPCHAR  pchDateTime,
                    zVIEW   lpView );

zLONG OPERATION
MiGetERTokenForEntity( zVIEW     lpView,
                       zCPCHAR   cpcEntityName );

zSHORT OPERATION
MiGetParentEntityNameForView( zPCHAR   pchReturnString,
                              zVIEW    lpView,
                              zCPCHAR  cpcEntityName );

zLONG  OPERATION
MiGetInstanceID_ForView( zVIEW    lpView );

zSHORT OPERATION
MiGetKeyFromInstance( zPCHAR  pchReturnString,
                      zSHORT  nLth,
                      zVIEW   lpView,
                      zCPCHAR cpcEntityName );

zSHORT OPERATION
MiGetObjectNameForView( zPCHAR pchReturnName, zVIEW lpView );

zSHORT OPERATION
MiGetTemporalStateOfEntity( zVIEW    lpView,
                            zCPCHAR  cpcEntityName );

zSHORT OPERATION
MiGetUpdateForView( zVIEW    lpView );

zLONG  OPERATION
MiSetInstanceUpdateFlag( zVIEW lpView, zLONG lFlag );

zSHORT OPERATION
MiHasPersistentChanges( zVIEW lpView );

zSHORT OPERATION
MiGetOI_ReleaseForView( zVIEW   lpView,
                        zPCHAR  pchReturnRelease );
zSHORT OPERATION
MiSetOI_ReleaseForView( zVIEW    lpView,
                        zCPCHAR  cpcNewRelease );
zSHORT OPERATION
MiCompareOI_ToRelease( zVIEW   lpView,
                       zPCHAR  lpCompareRelease );

zLONG  OPERATION
MiGetActivateFlags( zVIEW   lpView );

zLONG  OPERATION
MiGetSetViewTaskAppFlags( zVIEW   lpView,
                          zLONG   lOption,
                          zPCHAR  pchTaskInfo,
                          zLONG   lFlag );

zSHORT OPERATION
MiValidView( zVIEW   lpView );

#define  zUPD_INCLUDE               1
#define  zUPD_NONPERSIST            2

zSHORT OPERATION
MiGetTypeForViewEntityAttr( zVIEW    lpView,
                            zCPCHAR  cpcEntityName,
                            zCPCHAR  cpcAttribName );
zSHORT OPERATION
MiGetUpdateForViewEntityAttr( zVIEW    lpView,
                              zCPCHAR  cpcEntityName,
                              zCPCHAR  cpcAttributeName,
                              zSHORT   nOption );

zSHORT OPERATION
MiGetCardinalityForEntity( zPUSHORT puCardMin,
                           zPUSHORT puCardMax,
                           zVIEW    lpView,
                           zCPCHAR  cpcEntityName );

zLONG  OPERATION
MiListOE_Memory( zVIEW lpVIEW, zSHORT nLevel );

zSHORT OPERATION
MiEntityVersioned( zVIEW     lpView,
                   zCPCHAR   cpcEntityName );
zSHORT OPERATION
SetCursorRelativeEntity( zVIEW     lpView,
                         zCPCHAR   cpcEntityName,
                         zLONG     lPositionChange,
                         zCPCHAR   cpcScopingEntityName );

zLONG  OPERATION
GetRelativeEntityNumber( zVIEW     lpView,
                         zCPCHAR   cpcEntityName,
                         zCPCHAR   cpcScopingEntityName,
                         zLONG     lFlag );

zSHORT OPERATION
SetCursorAbsolutePosition( zPCHAR   pchReturnEntityName,
                           zVIEW    lpView,
                           zLONG    lPosition );

zSHORT OPERATION
GetAbsolutePositionForEntity( zPLONG  plReturnPosition,
                              zVIEW   lpView,
                              zCPCHAR cpcEntityName );

zSHORT OPERATION
DefineHierarchicalCursor( zVIEW    lpView,
                          zCPCHAR  cpcEntityName );

zSHORT OPERATION
DropHierarchicalCursor( zVIEW  lpView );

zSHORT OPERATION
SetCursorNextEntityHierarchical( zPUSHORT pnReturnLevel,
                                 zPCHAR   pchReturnEntityName,
                                 zVIEW    lpView );

zSHORT OPERATION
GetEntityNameForHierarchicalCsr( zPUSHORT lpnReturnLevel,
                                 zPCHAR   pchReturnEntityName,
                                 zPULONG  pulAbsolutePosition,
                                 zVIEW    lpView );
zSHORT OPERATION
GetEntityKeyForHierarchicalCsr( zPULONG  pulReturnLevel,
                                zPCHAR   pchReturnEntityName,
                                zPULONG  pulEntityKey,
                                zVIEW    lpView );

zSHORT OPERATION
GetStringFromAttribute( zPCHAR   pchReturnString,
                        zLONG    lMaxLth,
                        zVIEW    lpView,
                        zCPCHAR  cpcEntityName,
                        zCPCHAR  cpcAttributeName );

zSHORT OPERATION
AttributeUpdated( zVIEW   lpView,
                  zPCHAR  pchEntityName,
                  zPCHAR  pchAttribName );

zSHORT OPERATION
GetStringFromAttributeByContext( zPCHAR   pchReturnString,
                                 zVIEW    lpView,
                                 zCPCHAR  cpcEntityName,
                                 zCPCHAR  cpcAttributeName,
                                 zCPCHAR  cpcContextName,
                                 zULONG   ulMaxStringLth );

zSHORT OPERATION
GetStructFromEntityAttrs( zPCHAR  lpReturnStruct,
                          zVIEW   lpView,
                          zCPCHAR cpcEntityName );

zSHORT OPERATION
SetAttributeFromString( zVIEW    lpView,
                        zCPCHAR  cpcEntityName,
                        zCPCHAR  cpcAttributeName,
                        zCPCHAR  cpcStringValue );

zSHORT OPERATION
GetViewFromAttribute( zPVIEW  pvReturnView,
                      zVIEW   lpView,
                      zCPCHAR cpcEntityName,
                      zCPCHAR cpcAttributeName );
zSHORT OPERATION
GetIntegerFromAttribute( zPLONG   lplReturnInteger,
                         zVIEW    lpView,
                         zCPCHAR  cpcEntityName,
                         zCPCHAR  cpcAttributeName );

zSHORT OPERATION
SetAttributeFromInteger( zVIEW    lpView,
                         zCPCHAR  cpcEntityName,
                         zCPCHAR  cpcAttributeName,
                         zLONG    lIntegerValue );
zSHORT OPERATION
SetAttributeFromView( zVIEW   lpView,
                      zCPCHAR cpcEntityName,
                      zCPCHAR cpcAttributeName,
                      zVIEW   vViewValue );
zSHORT OPERATION
GetDecimalFromAttribute( zPDECIMAL  lpdReturnDecimal,
                         zVIEW      lpView,
                         zCPCHAR    cpcEntityName,
                         zCPCHAR    cpcAttributeName );

zSHORT OPERATION
SetAttributeFromDecimal( zVIEW     lpView,
                         zCPCHAR   cpcEntityName,
                         zCPCHAR   cpcAttributeName,
                         zDECIMAL  dDecimalValue );

zSHORT OPERATION
GetBlobFromAttribute( zPVOID   pReturnBlob,
                      zPULONG  puMaxLth,
                      zVIEW    lpView,
                      zCPCHAR  cpcEntityName,
                      zCPCHAR  cpcAttributeName );

zSHORT OPERATION
SetAttributeFromBlob( zVIEW    lpView,
                      zCPCHAR  cpcEntityName,
                      zCPCHAR  cpcAttributeName,
                      zPVOID   pBlobValue,
                      zULONG   uLth );

zSHORT OPERATION
AddToAttributeFromInteger( zVIEW    lpView,
                           zCPCHAR  cpcEntityName,
                           zCPCHAR  cpcAttributeName,
                           zLONG    lIntegerValue );

zSHORT OPERATION
SetAttributeFromAttribute( zVIEW    zTgtView,
                           zCPCHAR  cpcTgtEntityName,
                           zCPCHAR  cpcTgtAttributeName,
                           zVIEW    zSrcView,
                           zCPCHAR  cpcSrcEntityName,
                           zCPCHAR  cpcSrcAttributeName );

zSHORT OPERATION
SetBlobAttributeFromAttribute( zVIEW    lpTgtView,
                               zCPCHAR  cpcTgtEntityName,
                               zCPCHAR  cpcTgtAttributeName,
                               zVIEW    lpSrcView,
                               zCPCHAR  cpcSrcEntityName,
                               zCPCHAR  cpcSrcAttributeName );

zSHORT OPERATION
SetBlobFromEntityAttributes( zVIEW    lpTgtView,
                             zCPCHAR  cpcTgtEntityName,
                             zCPCHAR  cpcAttributeName,
                             zVIEW    lpSrcView,
                             zCPCHAR  cpcSrcEntityName );

zSHORT OPERATION
SetBlobFromOI( zVIEW   lpTgtView,
               zCPCHAR cpcTgtEntityName,
               zCPCHAR cpcAttributeName,
               zVIEW   lpSrcView,
               zLONG   lControl );

zSHORT OPERATION
WriteBlobToFile( zVIEW   lpView,
                 zCPCHAR cpcEntityName,
                 zCPCHAR cpcAttributeName,
                 zCPCHAR cpcFileName );

zSHORT OPERATION
SetBlobFromFile( zVIEW   lpView,
                 zCPCHAR cpcEntityName,
                 zCPCHAR cpcAttributeName,
                 zCPCHAR cpcFileName );

zSHORT OPERATION
SetOI_FromBlob( zPVIEW  plpTgtView,
                zPCHAR  pchReturnViewOD_Name,
                zVIEW   vSubtask,
                zVIEW   lpSrcView,
                zCPCHAR cpcSrcEntityName,
                zCPCHAR cpcAttributeName,
                zLONG   lControl );

zSHORT OPERATION
SetEntityAttributesFromBlob( zVIEW    lpTgtView,
                             zCPCHAR  cpcTgtEntityName,
                             zVIEW    lpSrcView,
                             zCPCHAR  cpcSrcEntityName,
                             zCPCHAR  cpcAttributeName );

zSHORT OPERATION
AddToAttributeFromDecimal( zVIEW    lpView,
                           zCPCHAR  cpcEntityName,
                           zCPCHAR  cpcAttributeName,
                           zDECIMAL dDecimalValue );

zSHORT OPERATION
AddToAttributeFromAttribute( zVIEW    zTgtView,
                             zCPCHAR  cpcTgtEntityName,
                             zCPCHAR  cpcTgtAttributeName,
                             zVIEW    zSrcView,
                             zCPCHAR  cpcSrcEntityName,
                             zCPCHAR  cpcSrcAttributeName );

zSHORT OPERATION
CompareAttributeToAttribute( zVIEW    zTgtView,
                             zCPCHAR  cpcTgtEntityName,
                             zCPCHAR  cpcTgtAttributeName,
                             zVIEW    zSrcView,
                             zCPCHAR  cpcSrcEntityName,
                             zCPCHAR  cpcSrcAttributeName );

zSHORT OPERATION
CompareAttributeToString( zVIEW    lpView,
                          zCPCHAR  cpcEntityName,
                          zCPCHAR  cpcAttributeName,
                          zCPCHAR  cpcSrcString );

zSHORT OPERATION
CompareAttributeToInteger( zVIEW    lpView,
                           zCPCHAR  cpcEntityName,
                           zCPCHAR  cpcAttributeName,
                           zLONG    lSrcInteger );

zSHORT OPERATION
CompareAttributeToDecimal( zVIEW    lpView,
                           zCPCHAR  cpcEntityName,
                           zCPCHAR  cpcAttributeName,
                           zDECIMAL dSrcDecimal );


zSHORT OPERATION
GetAttributeLength( zPULONG   puReturnLth,
                    zVIEW     lpView,
                    zCPCHAR   cpcEntityName,
                    zCPCHAR   cpcAttributeName );


zSHORT OPERATION
GetAttributeDisplayLength( zPULONG    puReturnLth,
                           zVIEW      lpView,
                           zCPCHAR    cpcEntityName,
                           zCPCHAR    cpcAttributeName,
                           zCPCHAR    cpcContextName );


zSHORT OPERATION
GetActualAttributeLength( zPULONG   puReturnLth,
                          zVIEW     lpView,
                          zCPCHAR   cpcEntityName,
                          zCPCHAR   cpcAttributeName );


zSHORT OPERATION
SetMatchingAttributesByName( zVIEW    zTgtView,
                             zCPCHAR  cpcTgtEntityName,
                             zVIEW    zSrcView,
                             zCPCHAR  cpcSrcEntityName,
                             zSHORT   nControl );

zSHORT OPERATION
SetAttributeFromVariable( zVIEW     lpView,
                          zCPCHAR   cpcEntityName,
                          zCPCHAR   cpcAttributeName,
                          zCPVOID   lpVariable,
                          zCHAR     cVariableType,
                          zULONG    ulVariableLth,
                          zCPCHAR   cpcContextName,
                          zSHORT    nFlag);

zSHORT OPERATION
CompareAttributeToVariable( zVIEW   lpView,
                            zCPCHAR cpcEntityName,
                            zCPCHAR cpcAttributeName,
                            zCPVOID lpVariable,
                            zCHAR   cVariableType,
                            zULONG  ulVariableLth,
                            zCPCHAR cpcContextName,
                            zSHORT  nFlag );

zSHORT OPERATION
GetVariableFromAttribute( zPVOID    lpVariable,
                          zPULONG   pulReturnLth,
                          zCHAR     cVariableType,
                          zULONG    ulVariableLth,
                          zVIEW     lpView,
                          zCPCHAR   cpcEntityName,
                          zCPCHAR   cpcAttributeName,
                          zCPCHAR   cpcContextName,
                          zSHORT    nFlag );

zSHORT OPERATION
AddToAttributeFromVariable( zVIEW    lpView,
                            zCPCHAR  cpcEntityName,
                            zCPCHAR  cpcAttributeName,
                            zPVOID   lpVariable,
                            zCHAR    cVariableType,
                            zULONG   ulVariableLth,
                            zCPCHAR  cpcContextName );

zSHORT OPERATION
GetFirstTableEntryForAttribute( zPCHAR  pchReturnString,
                                zLONG   lMaxLth,
                                zVIEW   lpView,
                                zCPCHAR cpcEntityName,
                                zCPCHAR cpcAttributeName,
                                zCPCHAR cpcContextName,
                                zPLONG  pTablePosition );

zSHORT OPERATION
GetNextTableEntryForAttribute( zPCHAR   pchReturnString,
                               zLONG    lMaxLth,
                               zVIEW    lpView,
                               zCPCHAR  cpcEntityName,
                               zCPCHAR  cpcAttributeName,
                               zCPCHAR  cpcContextName,
                               zPLONG   pTablePosition );

zSHORT OPERATION
SetAttributeValueNext( zVIEW    lpView,
                       zCPCHAR  cpcEntityName,
                       zCPCHAR  cpcAttributeName,
                       zCPCHAR  cpcContextName );

zSHORT OPERATION
SetAttributeValuePrev( zVIEW    lpView,
                       zCPCHAR  cpcEntityName,
                       zCPCHAR  cpcAttributeName,
                       zCPCHAR  cpcContextName );

zSHORT OPERATION
SetSelectSetForView( zVIEW   lpView,
                     zSHORT  nSelectSetID );

zSHORT OPERATION
GetSelectStateOfEntityForSet( zVIEW   lpView,
                              zCPCHAR cpcEntityName,
                              zSHORT  nSelectSet );

zSHORT OPERATION
GetSelectStateOfEntity( zVIEW   zVIEW,
                        zCPCHAR cpcEntityName );

zSHORT OPERATION
SetCursorFirstSelectedEntity( zVIEW   zVIEW,
                              zCPCHAR cpcEntityName,
                              zCPCHAR cpcScopingEntityName );

zSHORT OPERATION
SetCursorNextSelectedEntity( zVIEW   zVIEW,
                             zCPCHAR cpcEntityName,
                             zCPCHAR cpcScopingEntityName );

zSHORT OPERATION
SetAllSelStatesForEntityForSet( zVIEW   lpView,
                                zCPCHAR cpcEntityName,
                                zSHORT  nState,
                                zSHORT  nSelectSet,
                                zCPCHAR cpcScopingEntityName );

zSHORT OPERATION
SetAllSelectStatesForEntity( zVIEW   zVIEW,
                             zCPCHAR cpcEntityName,
                             zSHORT  nState,
                             zCPCHAR cpcScopingEntityName );

zSHORT OPERATION
SetSelectStateOfEntityForSet( zVIEW   lpView,
                              zCPCHAR cpcEntityName,
                              zSHORT  nState,
                              zSHORT  nSelectSet );

zSHORT OPERATION
SetSelectStateOfEntity( zVIEW   zVIEW,
                        zCPCHAR cpcEntityName,
                        zSHORT  nState );

zSHORT OPERATION
RelinkAllSubobjectsForOI( zVIEW    zTgtView,
                          zCPCHAR  cpcTgtEntityName,
                          zVIEW    zSrcView,
                          zCPCHAR  cpcSrcEntityName );

zSHORT OPERATION
RelinkInstanceToInstance( zVIEW    zTgtView,
                          zCPCHAR  cpcTgtEntityName,
                          zVIEW    zSrcView,
                          zCPCHAR  cpcSrcEntityName );

zLONG OPERATION
CountEntitiesForView( zVIEW lpView, zCPCHAR cpcEntityName );

zLONG OPERATION
CountEntitiesForViewUnderParent( zVIEW   lpView,
                                 zCPCHAR cpcEntityName,
                                 zCPCHAR cpcScopingEntityName );

zSHORT OPERATION
ObjectInstanceUpdated( zVIEW    lpView );

zSHORT OPERATION
ObjectInstanceUpdatedFromFile( zVIEW    lpView );

zSHORT      OPERATION
SubobjectVersionUpdated( zVIEW   lpView,
                         zCPCHAR cpcEntityName,
                         zSHORT  bRootOnly );

zSHORT OPERATION
UfFormatDateTime( zPCHAR  pchReturnString,
                  zLONG   lMaxLth,
                  zCPCHAR cpcWorkString,
                  zCPCHAR cpcEditString );

zSHORT OPERATION
UfEditFormatDateTime( zPCHAR  pchDTString,
                      zLONG   lMaxLth,
                      zCPCHAR cpcEditString );

zSHORT OPERATION
UfEditFormatString( zPCHAR pchString, zCPCHAR cpcFormat );

zSHORT OPERATION
UfFormatString( zPCHAR pchString, zCPCHAR cpcFormat );

zSHORT OPERATION
UfEncryptString( zPCHAR  pchOut, zPCHAR pchIn, zUSHORT uLth );

zSHORT OPERATION
UfEncryptStringLong( zPCHAR  pchOut, zPCHAR pchIn, zPCHAR pchKey, zUSHORT uLth );

zSHORT OPERATION
UfDecryptString( zPCHAR  pchOut, zPCHAR pchIn, zUSHORT uLth );

zSHORT OPERATION
UfDecryptStringLong( zPCHAR  pchOut, zPCHAR pchIn, zPCHAR pchKey, zUSHORT uLth );

zSHORT OPERATION
UfEncryptStringUL( zPCHAR  pchOut, zPCHAR pchIn, zPCHAR pchKey, zUSHORT uLth );

zSHORT OPERATION
UfDecryptStringUL( zPCHAR  pchOut, zPCHAR pchIn, zPCHAR pchKey, zUSHORT uLth );

zSHORT OPERATION
UfCompressName( zPCHAR  pchLongName,
                zPCHAR  pchShortName,
                zLONG   lShortNameLth,
                zPCHAR  pchSpaceReplace,
                zPCHAR  pchUnderscoreMode,
                zPCHAR  pchLowerVowels,
                zPCHAR  pchOtherChars,
                zSHORT  nPhasesToForce );

zSHORT OPERATION
UfZProbeEnable( zBOOL   bEnable );

zSHORT OPERATION
UfZProbeInit( );

zSHORT OPERATION
UfZProbeOn( zSHORT nProbeNbr,
            zPCHAR pchDesc,
            zBOOL  bTurnPriorProbeOff );

zSHORT OPERATION
UfZProbeOff( zSHORT nProbeNbr,
             zPCHAR pchDesc );

zSHORT OPERATION
UfZProbeOnByDesc( zPCHAR pchDesc,
                  zBOOL  bTurnPriorProbeOff );

zSHORT OPERATION
UfZProbeOffByDesc( zPCHAR pchDesc );

zSHORT OPERATION
UfZProbeTrace( zPCHAR pchDesc );

zSHORT OPERATION
DisplayCursorInfo( zVIEW  lpView );


zSHORT OPERATION
GetTaskDBHandlerTraceLevel( zVIEW lpView );

zSHORT OPERATION
SetTaskDBHandlerTraceLevel( zVIEW lpView, zLONG lTraceLevel );

zSHORT OPERATION
SortEntitiesByAttribute( zVIEW lpView );

zSHORT OPERATION
OrderEntityForView( zVIEW    lpView,
                    zCPCHAR  cpcEntityName,
                    zCPCHAR  cpcOrderKeys );

zSHORT OPERATION
OrderEntitiesByDefaultAttribs( zVIEW  lpView,
                               zPCHAR pchEntityName );

zSHORT OPERATION
OrderOI_ByDefaultAttribs( zVIEW lpView );

zSHORT OPERATION
MessageSend( zVIEW    lpView,
             zCPCHAR  cpcMsgId,
             zCPCHAR  cpcTitle,
             zCPCHAR  cpcMsgText,
             zLONG    lMsgType,
             zSHORT   bBeep );

zSHORT OPERATION
MessagePrompt( zVIEW    lpView,
               zCPCHAR  cpcMsgId,
               zCPCHAR  cpcTitle,
               zCPCHAR  cpcMsgText,
               zSHORT   bBeep,
               zSHORT   nButtons,
               zSHORT   nDefaultButton,
               zSHORT   nIcon );

zSHORT OPERATION
MessagePromptForInput( zVIEW    lpView,
                       zCPCHAR  cpcMsgId,
                       zCPCHAR  cpcTitle,
                       zCPCHAR  cpcMsgText,
                       zSHORT   bBeep,
                       zPCHAR   lpchReturnBuffer,
                       zUSHORT  usBufferLth );

zSHORT OPERATION
MessagePresent( zVIEW    lpView,
                zLONG    lEventType,
                zVIEW    vMessage );

zSHORT OPERATION
ZeidonStringCopy( zPCHAR  pchTgtString,
                  zLONG   lTgtIndex,
                  zLONG   lMaxReceive,
                  zCPCHAR pchSrcString,
                  zLONG   lSrcIndex,
                  zLONG   lMaxCopy,
                  zLONG   lMaxTgtLength );
zSHORT OPERATION
ZeidonStringConcat( zPCHAR  pchTgtString,
                    zLONG   lTgtIndex,
                    zLONG   lMaxReceive,
                    zCPCHAR cpcSrcString,
                    zLONG   lSrcIndex,
                    zLONG   lMaxConcat,
                    zLONG   lMaxTgtLength );
zSHORT OPERATION
ZeidonStringCompare( zCPCHAR cpcTgtString,
                     zLONG   lTgtIndex,
                     zLONG   lMaxReceive,
                     zCPCHAR pchSrcString,
                     zLONG   lSrcIndex,
                     zLONG   lMaxCompare,
                     zLONG   lMaxTgtLth );
zSHORT OPERATION
ZeidonCopyWithinString( zPCHAR  pchTgtString,
                        zLONG   lTgtIdx,
                        zLONG   lSrcIdx,
                        zLONG   lMaxTgtLth );
zSHORT OPERATION
ZeidonStringFind( zCPCHAR cpcTgtString,
                  zSHORT  nTgtIdx,
                  zCPCHAR cpcSearch );
zSHORT OPERATION
ZeidonStringConvertFromNumber( zPCHAR   pchTgtString,
                               zLONG    lTgtIdx,
                               zLONG    lMaxReceive,
                               zLONG    lMaxTgtLth,
                               zLONG    lIntegerValue,
                               zDECIMAL dDecimalValue,
                               zCPCHAR  cpcNumberType );

zSHORT OPERATION
NetStartup( zVIEW    zTaskView,
            zPCHAR   pchNetworkName,
            zPCHAR   pchExecutable );

zSHORT OPERATION
NetClose( zVIEW vTaskView, zPCHAR pchNetworkName );

zSHORT OPERATION
NetListen( zVIEW vTaskView, zPCHAR pchNetworkName );

zSHORT OPERATION
NetStopListen( zVIEW vTaskView, zPCHAR pchNetworkName );

zSHORT OPERATION
NetGetLocalHostAddress( zVIEW vTaskView,
                        zPCHAR pchNetworkName,
                        zPCHAR pchHostAddress );

zSHORT OPERATION
NetActivateOI( zPCHAR  pchNetworkName,
               zPCHAR  pchAddress,
               zPVIEW  lpReturnView,
               zPCHAR  pchViewOD_Name,
               zVIEW   lpAppQualView,
               zVIEW   lpQualView,
               zLONG   lControl    );

zSHORT OPERATION
NetCommitOI( zPCHAR        pchNetworkName,
             zPCHAR        pchAddress,
             LPVIEWCLUSTER lpViewCluster,
             zVIEW         lpViewArray[],
             zSHORT        nViewCount,
             zPSHORT       pnViewErrorIdx,
             zLONG         lControl );

zSHORT OPERATION
NetActivateOI_FromFile( zPCHAR  pchNetworkName,
                        zPCHAR  pchHostAddress,
                        zPVIEW  lpReturnView,
                        zPCHAR  pchViewOD_Name,
                        zVIEW   vSubtask,
                        zPCHAR  pchFileName,
                        zLONG   lControl );

zSHORT OPERATION
NetCommitOI_ToFile( zPCHAR  pchNetworkName,
                    zPCHAR  pchHostAddress,
                    zVIEW   lpView,
                    zPCHAR  pchFileName,
                    zLONG   lControl );

zSHORT OPERATION
NetSendFile( zPCHAR pchNetworkName,
             zPCHAR pchServerAddress,
             zPCHAR pchLocalFileName,
             zPCHAR pchServerDirectory,
             zPCHAR pchServerFileName,
             zBOOL  bBinaryFile,
             zVIEW  vSubtask );

zSHORT VARYOPER
NetCallOperation( zPCHAR   pchNetworkName,
                  zPCHAR   pchAddress,
                  zVIEW    vSubtask,
                  zBOOL    bTransformation,
                  zPCHAR   pchInfo,
                  zPCHAR   pchOperName,
                  zPVOID   pvReturn,
                  zPCHAR   pchArgList, ... );

zSHORT OPERATION
NetProcessMessage( zVIEW    vTaskView,
                   zPCHAR   pchNetworkName,
                   zPVOID   *ppvConn );
zSHORT OPERATION
NetGetTraceLevel( zVIEW vTaskView, zPCHAR pchNetworkName );

zSHORT OPERATION
NetSetTraceLevel( zVIEW vTaskView, zPCHAR pchNetworkName, zSHORT nTraceLevel );

zSHORT OPERATION
NetStatus( zVIEW vTaskView, zPCHAR pchNetworkName );

zOPER_EXPORT zSHORT OPERATION
FormatSubobjectOnDoc( zVIEW     vSourceOI,
                      zCPCHAR   cpcSubobjectEntityName,
                      zVIEW     vSubtask,
                      zCPCHAR   cpcReportDefName,
                      zLONG     lPreviewFlag );
zOPER_EXPORT zSHORT OPERATION
FormatSubobjectOnDocWithXRP( zVIEW     vSourceOI,
                             zCPCHAR   cpcSubobjectEntityName,
                             zVIEW     vSubtask,
                             zCPCHAR   cpcReportDefName,
                             zVIEW     vReportDef,
                             zLONG     lPreviewFlag );
zOPER_EXPORT zSHORT OPERATION
FormatSubobjectForXSLT( zVIEW     vSourceOI,
                        zCPCHAR   cpcSubobjectEntityName,
                        zVIEW     vSubtask,
                        zCPCHAR   cpcReportDefName,
                        zLONG     lPreviewFlag );
zOPER_EXPORT zSHORT OPERATION
FormatSubobjectForXSLTWithXRP( zVIEW     vSourceOI,
                               zCPCHAR   cpcSubobjectEntityName,
                               zVIEW     vSubtask,
                               zCPCHAR   cpcReportDefName,
                               zVIEW     vReportDef,
                               zLONG     lPreviewFlag );
zOPER_EXPORT zSHORT OPERATION
ConvertXML_SpecialCharacters( zVIEW   vAnyView,
                              zPCHAR  pchReturnedString,
                              zPCHAR  pchSourceString,
                              zLONG   lReturnedStringLength );
zOPER_EXPORT zSHORT OPERATION
FormatWebReport( zVIEW     vSourceOI,
                 zCPCHAR   cpcSubobjectEntityName,
                 zVIEW     vSubtask,
                 zCPCHAR   cpcReportDefName,
                 zCPCHAR   cpcReportFileName,
                 zLONG     lFlag );
zOPER_EXPORT zSHORT OPERATION
InitWebSessionObject( zPVIEW  lpKZXMLWDO,
                      zVIEW   lpView,
                      zCPCHAR cpcUserID );
zOPER_EXPORT zSHORT OPERATION
InitWebPage( zVIEW   vKZXMLWDO,
             zCPCHAR  cpcDialogName,
             zCPCHAR  cpcWindowName );
zOPER_EXPORT zSHORT OPERATION
AddWebControlSubobject( zVIEW      vKZXMLWDO,
                        zCPCHAR    cpcControlName,
                        zCPCHAR    cpcControlType,
                        zCPCHAR    cpcControlContext,
                        zCPCHAR    cpcSourceViewName,
                        zCPCHAR    cpcSourceEntityName,
                        zCPCHAR    cpcSourceAttributeName,
                        zCPCHAR    cpcAutoComboBoxValue );
zSHORT OPERATION
SysAddDecimalToDecimal( zPDECIMAL pdResult,
                        zPDECIMAL pdDec1,
                        zPDECIMAL pdDec2 );
zSHORT OPERATION
SysAssignDecimalFromDecimal( zPDECIMAL pdTarget,
                             zPDECIMAL pdSource );
zSHORT OPERATION
SysAssignDecimalFromNull( zPDECIMAL pdTarget );
zSHORT OPERATION
SysCallDecimalOperation( zPVOID  pvReturn,
                         zPVOID  pvDecimal,
                         zPVOID  pvInfo,
                         zLONG   lControl );
zSHORT OPERATION
SysCompareDecimalToDecimal( zPDECIMAL pdTarget,
                            zPDECIMAL pdSource );
zSHORT OPERATION
SysCompareDecimalToDouble( zPDECIMAL pdTarget,
                           double    dSource );
zSHORT OPERATION
SysConvertDecimalToLong( zPDECIMAL pdDecimal,
                         zPLONG    plLong );
zSHORT OPERATION
SysCompareDecimalToNull( zPDECIMAL pdSource );

zSHORT OPERATION
SysConvertDecimalToDouble( zPDECIMAL pdDecimal,
                           double    *pdDouble );

zSHORT OPERATION
SysConvertDecimalToString( zPDECIMAL pdDecimal,
                           zPCHAR    pchString,
                           zSHORT    nPrecision );

zSHORT OPERATION
SysConvertDoubleToDecimal( double    dDouble,
                           zPDECIMAL pdDecimal );

zSHORT OPERATION
SysConvertLongToDecimal( zLONG     lLong,
                         zPDECIMAL pdDecimal );

zSHORT OPERATION
SysConvertStringToDecimal( zCPCHAR   cpcString,
                           zPDECIMAL pdDecimal );

zSHORT OPERATION
SysDivideDecimalByDecimal( zPDECIMAL pdResult,
                           zPDECIMAL pdDec1,
                           zPDECIMAL pdDec2 );

zSHORT OPERATION
SysMultiplyDecimalByDecimal( zPDECIMAL pdResult,
                             zPDECIMAL pdDec1,
                             zPDECIMAL pdDec2 );
zLONG  OPERATION
SysMutexClose( zLONG hMutexOS );

zLONG  OPERATION
SysMutexCreate( zVIEW lpTaskView, zCPCHAR cpcMutexName, zLONG lControl );

zSHORT OPERATION
SysMutexLock( zVIEW lpTaskView, zCPCHAR cpcMutexName,
              zULONG ulTimeout, zLONG lControl );

zSHORT OPERATION
SysMutexUnlock( zVIEW lpTaskView, zCPCHAR cpcMutexName, zLONG lControl );

zSHORT OPERATION
SysMutexQueryLock( zCPCHAR cpcMutexName );

zSHORT OPERATION
SysMutexQueryStatus( );

zSHORT OPERATION
SysRoundDecimal( zPDECIMAL pd,
                 zSHORT    nPrecision );

zSHORT OPERATION
SysSubtractDecimalFromDecimal( zPDECIMAL pdResult,
                               zPDECIMAL pdDec1,
                               zPDECIMAL pdDec2 );

typedef void (*CURSORLISTENER)( zVIEW, zCPCHAR, zPVOID );

zSHORT OPERATION
AddCursorListener( zVIEW, CURSORLISTENER, zPVOID );

zSHORT OPERATION
RemoveCursorListener( zVIEW, CURSORLISTENER, zPVOID );

zDECIMAL OPERATION
zdSUM( zVIEW   vView,
       zCPCHAR cpcEntityName,
       zCPCHAR cpcAttrName,
       zCPCHAR cpcScopingEntity );

zLONG OPERATION
ziSUM( zVIEW   vView,
       zCPCHAR cpcEntityName,
       zCPCHAR cpcAttrName,
       zCPCHAR cpcScopingEntity );


#ifdef KZSYSSVC_INCL
#ifndef KZMETA_INCL
#define KZMETA_INCL
#endif
#endif

#ifdef KZOESYS_INCL
#ifndef KZMETA_INCL
#define KZMETA_INCL
#endif
#ifndef KZSYSSVC_INCL
#define KZSYSSVC_INCL
#endif
#endif

#ifdef KZOESYS_INCL
#include "kzoeidaa.h"
#include "kzoetdaa.h"
#endif

#ifdef KZMETA_INCL
#include "kzoemeaa.h"
#endif

#ifdef KZSYSSVC_INCL
#include "kzoessaa.h"
#include "kzoep1aa.h"
#endif

#ifdef KZOESYS_INCL
#include "kzoep0aa.h"
#include "kzoemiaa.h"
#endif

#ifdef __cplusplus
}

// the following is needed for C++ and extern "C"
extern "C++"
{
#include "kzoedeca.h"
}

#endif

#endif // #ifndef KZOENGAA_DEF
