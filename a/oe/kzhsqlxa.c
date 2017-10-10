/////////////////////////////////////////////////////////////////////////////
//
// KZHSQLXA.C - Database handler for all databases.
//
///////////////////////////// DEFINES ///////////////////////////////////////

/*
CHANGE LOG

2003.02.10  DGC
   Gave all DBHandlers the same DBH_MsgProc name.

2002.12.31  DGC
   Minor changes to get it working on Linux.

2002.11.28  HH
   Did not compile for DB2.

2002.10.20  DGC  Z10
   Added functionality to select entities from a qual list.

2002.03.22  DGC  Z10
   Fixed mem leak reported by Phil.  A problem with AutoLoadFromParent.

2002.03.21  FH
   Get rid of one more compiler warning by doing a cast on (SQLHANDLE) in
   line 6012.

2002.03.20  FH
   Move the definition of SQLHANDLE into the "#if (DB2CLI_VER < 0x0300)" block
   to get rid of compiler warnings.

2001.12.19  DGC  Z10
   Fixed a bug reported by Phil.  Join processing was not correctly handling
   entities that had only keys.

2001.12.12  DGC  Z10
   Added code to retrieve schema information from the database.

2001.11.12  DGC  Z10
   Fixed type reported by HH.

2001.09.26  DGC  Z10
   Made change requested by Phil: fnSetEntityByKey was made faster by adding
   awareness of whether an entity was joined with it's child.

2001.06.27  DGC  Z10
   Fixed a bug found by Phil -- not correctly handling joins with zSINGLE.

   Fixed a bug found by Phil -- attributes with DB_Opers were not loaded
   correctly.

   Fixed a bug reported by Don/Jeff.  Using autoload with a m-to-m relationship
   caused a crash.

   Put in a diagnostic check to make sure XODs were saved with the correct
   JOIN information.

2001.05.29  DGC  Z10
  Very minor change to TraceLine.

2001.04.25  DGC  Z10
   Fixed bug reported by Jeff.  We were creating an extra coorespondence
   table if an entity was flagged as created and included.

2001.03.15  DGC  Z10
   First start on JOIN processing.

2001.02.13  DGC  Z10
   First attempt at fixing MS Access latency problem.

2001.01.10  DGC  Z10
   Module now compiles under DB2.

2001.01.08  DGC  Z10
   Fixed bug in previous change.  I was using SQL_LONGVARCHAR instead of
   SQL_VARCHAR.

2001.01.02  DGC  Z10
   Final implementation of SQL change to re-use parsed statements.  There will
   probably be some DB2 fixes coming.

2000.11.14  DGC  Z10
   Made change to keep DBH from crashing if ODBC DBH data is not set in the
   XOD.

2000.10.13  DGC  Z10
   Fixed bug.  The dbhandler keeps track of qualification objects during a
   single activate so that it can re-use them if possible.  The code could
   only handle 20 different quals and didn't check to make sure that more
   than 20 were used.  This caused a crash.  The DBH now checks to make sure
   we don't run over any boundaries.

2000.07.17  DGC  Z10
   Handled new message from OI...DBH_Object | DBH_NewObject.

2000.06.26  DGC  Z10
   Made short term fix.  We don't use joins if the qualification uses a
   restricting clause.

2000.06.13  DGC  Z10
   Made fix so that hanging FKs work with joins.

2000.05.04  DGC  Z10
   Change signature of LoadEntity.

2000.04.21  DGC  Z10
   Made changes to set more reasonable max lths for SQL buffers.

2000.04.13  DGC  Z10
   Changed MSGQ logic to name the message queue at the task level instead of
   the application level.

2000.01.26  DGC  Z10
   Made change to how decimals are read from the database.  Once we get the
   decimal value (as a string) we now do:
      StoreStringInRecord( )
      GetStringFromRecord( )
      StoreStringInRecord( )
   This allows the decimal domain to look over the decimal value.  Sometimes
   the decimal value on the database is not exactly what was stored--because
   of rounding problems.

1999.12.16  RG  Z9J,Z2000
   For DB2: if we have DB2 with decimal comma we have to change the
   comma into decimal point

1999.12.15  RG  Z9J,Z2000
   Bugfix: A date from a DB2 database which wasn't entered by Zeidon
   has been shown wrong. Fix: Before test the date with function:
   UfEditFormatDateTime Postfix a dummy time.

1999.10.14  DGC  Z10
   Started coding for joins.

1999.10.06  DGC 10a
   Fixed bug in activate--nRowCount was a short and now a long.

1999.09.29  DGC 10a
   Fixed but in ODBC that was inserting an extra character for long var chars
   (strings only, not blobs).

1999.06.10  HH  10a
   added some #if (DB2CLI_VER < 0x0300) to make it compile with DB2 3.x .

1999.06.10  DGC  10a
   Changed ODBC messages to always use MessageSend( ) instead of TraceLineS( ).

1999.05.18  DGC  10a
   Added mutex to protect changing the dbh work object.

1999.05.03  DGC  10a
   Fixed small bug reported by Bounds Checker.  A call to sprintf( ) didn't
   have enough arguments.

1999.03.08  DGC  10a
   Changed previous change to store dates (and just dates) as a date column
   for ODBC.

1999.03.08  DGC
   Made change to ODBC DB-Handler to store timestamps as a string.

1999.01.19  DGC
   GetWorkObject( ) was ignoring the return code when opening a DB connection.
   Fixed that.

*/

#if defined( _WINDOWS ) && defined( DEBUG )
#pragma optimize( "", off )
#endif

#ifdef __UNIX__
#else
   #include <windows.h>
#endif

#define  KZSYSSVC_INCL
#define  KZMETA_INCL
#include "kzoengaa.h"
#include <stdio.h>
#include "kzhsqlgp.h"
#include "kzhsqlxa.h"

#define TABLE_BUFFER_LTH            32000
#define MAX_COLUMNS                 300
#define MAX_OPEN_DATABASES          10
#define MAX_QUALIFICATIONS          20
#define MAX_BOUND_PARAMETERS        500
#define MAX_ENTITIES_IN_LOD         500
#define MAX_LODS_IN_ONE_ACTIVATE    20

#define CONVERSION_AREA_LTH         100

#define DELETEHACK
#define zFETCH_OK         0   // A fetch returned a row.
#define zFETCH_NO_DATA    1   // End of fetching.

// Define following to use JOIN statements when loading 1-to-1 tables.
#define USE_JOINS
#ifndef USE_JOINS
   // OK...it's a little bit of a hack but it works great
   #undef  zSQLCALLBACK_USEJOIN
   #define zSQLCALLBACK_USEJOIN       0x00000000
#endif

#define BUILD_SELECT    'S'
#define BUILD_CREATE    'C'
#define BUILD_UPDATE    'U'
#define BUILD_DELETE    'D'
#define BUILD_INCLUDE   'I'
#define BUILD_EXCLUDE   'X'

typedef struct _KeyData * LPKEYDATA;
typedef struct _KeyData
{
   LPVIEWENTITY lpLoadEntity;
   LPVIEWATTRIB lpViewAttrib;
   LPDATAFIELD  lpDataField;
   zPVOID       lpPtr;
} KeyData;

#if defined( DB2 )
   #include <sqlcli1.h>

   #define  zSQL_type      'D'
   #define  DBHANDLER_NAME "KZHSQLDA"

   #define SQL_RC( a, b, c, d, e )  fnSqlRC( a, b, c, d, e, lpConnection )
   #define RC_SUCCESSFUL( rc ) ( rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO )

#if (DB2CLI_VER < 0x0300)
   #define  SQL_NO_DATA    SQL_NO_DATA_FOUND
   #define SQL_HANDLE_ENV  2
   #define SQL_HANDLE_DBC  1

   #define  SQLHANDLE      zPVOID
   SQLRETURN SQLFreeHandle( zSHORT nHandleType, SQLHANDLE hndl );
#endif
   #define SQL_HANDLE_STMT 3


   // Following defines all callback functions handled by the callback oper.
   #define zCB_FUNCS       zSQLCALLBACK_CONVERTSTRING | \
                           zSQLCALLBACK_GETATTRVALUE  | \
                           zSQLCALLBACK_UPDATEDONLY   | \
                           zSQLCALLBACK_USEJOIN       | \
                           zSQLCALLBACK_GETCOLUMNNAME

   // Following used to keep track of ODs opened by DB2.
   typedef struct OD_ListStruct OD_ListRecord;
   typedef OD_ListRecord *LPOD_LIST;
   struct OD_ListStruct
   {
      LPVIEWOD     lpViewOD;
      zLONG        hMem;
      LPOD_LIST    lpNextOD;
      unsigned int bOpenConn    : 1,   // We have an open connection.
                   bNeedsCommit : 1;   // ViewOD part of current transaction.

      LPLIBRARY    hStaticLibrary;

      // Following needed because Zeidon drops ViewODs when an application
      // is closed.
      zCHAR  szOD_Name[ zZEIDON_NAME_LTH + 1 ];

      zSHORT (POPERATION pfnCommit)( zSHORT );
      zSHORT (POPERATION pfnRollback)( zSHORT );
   };

   typedef struct CallbackInfoStruct
   {
      zCHAR cBuildFunction;
   } CallbackInfoRecord, * LPCALLBACKINFO;

   // Following indicates whether we should hold onto prepared statement
   // handles during an activate.
   zBOOL g_bHoldStmtHandles = 'X';  // 'X' means it needs to be initialized.

   // Used to hold on to prepared statements during activation.
   typedef struct EntityHandlesStruct
   {
      HSTMT        hstmt;
      zPCHAR       pchSqlCmd;
      zPCHAR       pchInputBuffer;
      zPPCHAR      ppchBufferPtr;
      zULONG       ulInputLth;
      zPCHAR       pchOutputBuffer;
      LPBOUNDLIST  lpBoundList;
      unsigned int bLoadFromParent : 1;
   } EntityHandlesRecord, * LPSTMTHANDLES;

   typedef struct SelectHandlesStruct
   {
      LPVIEWOD       lpViewOD;
      LPSTMTHANDLES  lpStmtHandles;    // Contains the hstmt for each entity.
   } SelectHandlesRecord, * LPHANDLES;

   /* Decimal for DB2 */
   /* Meaning :
    *  0 = not initialized
    *  1 = no comma, use point
    *  2 = comma, decimal points must be converted
    */
   unsigned char g_ucDB2_Comma = 0;

#elif defined( DUMMY )

   #define  zSQL_type      'X'
   #define  DBHANDLER_NAME "KZHSQLXX"

   #define SQL_RC( a, b, c, d, e )  fnSqlRC( a, b, c, d, e, lpConnection )
   #define RC_SUCCESSFUL( rc ) ( rc == 1 )

   #define  SQL_NO_DATA    0

   // Following defines all callback functions handled by the callback oper.
   #define zCB_FUNCS       zSQLCALLBACK_UPDATEDONLY   | \
                           zSQLCALLBACK_ALWAYSALIAS   | \
                           zSQLCALLBACK_USEJOIN

#elif defined( ODBC )

   #include <sql.h>
   #include <sqlext.h>

   // Following indicates whether we should hold on to prepared statement
   // handles during an activate.
   zBOOL g_bHoldStmtHandles = 'X';  // 'X' means it needs to be initialized.

   ODBC_ObjectDataRecord g_DefaultODBC_Data = { 3, 'N', 3 };

   // Used to hold on to prepared statements during activation.
   typedef struct EntityHandlesStruct
   {
      HSTMT        hstmt;
      zPCHAR       pchSqlCmd;
      zPCHAR       pchInputBuffer;
      zPPCHAR      ppchBufferPtr;
      zULONG       ulInputLth;
      zPCHAR       pchOutputBuffer;
      LPBOUNDLIST  lpBoundList;
      unsigned int bLoadFromParent : 1;
   } EntityHandlesRecord, * LPSTMTHANDLES;

   typedef struct SelectHandlesStruct
   {
      LPVIEWOD       lpViewOD;
      LPSTMTHANDLES  lpStmtHandles;    // Contains the hstmt for each entity.
   } SelectHandlesRecord, * LPHANDLES;

   #define  zSQL_type      'O'
   #define  DBHANDLER_NAME "KZHSQLOA"

   #define SQL_RC( a, b, c, d, e )  fnSqlRC( a, b, c, d, e, lpConnection )
   #define RC_SUCCESSFUL( rc ) ( rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO )

   // Following defines all callback functions handled by the callback oper.
   #define zCB_FUNCS       zSQLCALLBACK_CONVERTSTRING | \
                           zSQLCALLBACK_UPDATEDONLY   | \
                           zSQLCALLBACK_GETCOLLISTPOS | \
                           zSQLCALLBACK_USEJOIN       | \
                           zSQLCALLBACK_GETATTRVALUE

   typedef struct CallbackInfoStruct
   {
      zCHAR             cBuildFunction;
      LPODBC_OBJECTDATA lpObjectData;
   } CallbackInfoRecord, * LPCALLBACKINFO;

   // Following is info shared by all ODBC tasks.
   typedef struct _ODBC_SYSTEM_INFO
   {
      zLONG  lLastCommitTask;  // Task ID of last task to change the DB.
      zULONG lLastCommitTime;  // Time of last change.
      zULONG lCommitLatency;   // Time we want to wait after a commit.
   } ODBC_SYSTEM_INFO, * LPODBC_SYSTEM_INFO;

   LPODBC_SYSTEM_INFO g_lpOdbcSystemInfo = 0;

#elif defined( SQLBASE )

   SQL Base no longer supported as a seperate database.

#elif defined( SQLSERVER )

   SQLServer no longer supported as a seperate database.

#endif

///////////////////////////// TYPEDEF'S /////////////////////////////////////

typedef struct DatabaseConnectionRecord DatabaseConnection;
typedef DatabaseConnection *LPDBCONNECTION;
struct DatabaseConnectionRecord
{
   zCHAR        szDatabaseName[ 50 ];
   unsigned     bValidConnection :1;

   // Define db connection handle.
#if defined( DB2 )
   SQLHDBC         hdbc;
#elif defined( ODBC )
   HDBC         hdbc;
#endif

};

typedef struct ConnectionArea ConnectionRecord;
typedef ConnectionRecord *LPCONNECTION;
struct ConnectionArea
{
   zCHAR          szDebug1[ 20 ];
   zVIEW          lpAppView;
   zVIEW          vDbhWork;

   // We can now have multiple qualfications during a transaction.  Keep a
   // list of the qualification views and their corresponding list of
   // QualEntities.  Note that lpFirstQualEntity should point to the "current"
   // QualEntity.
   zVIEW          vQualList[ MAX_QUALIFICATIONS ];
   LPQUALENTITY   lpQualEntityList[ MAX_QUALIFICATIONS ];
   zSHORT         nQualCount;
   LPQUALENTITY   lpFirstQualEntity;

   zPCHAR         pchConnSqlCmd;
   zLONG          hCmdMem;
   zPCHAR         pchGlobalTableBuffer;
   zLONG          lTblSize;
   zLONG          hTblMem;
   zSHORT         nTraceLevel;
   zSHORT         nOpenDatabaseCount;
   zSHORT         nCurrentDB;
   DatabaseConnection DBConnection[ MAX_OPEN_DATABASES ];
   unsigned int   bMultipleDatabases : 1,

                  // Used to indicate if the DB was changed by a transaction.
                  bDatabaseChanged   : 1,
                  bDeleteAll   : 1;

   // DB session handles.
#if defined( DB2 )

   // Following table used for binding long parameters.
   SQLINTEGER     nStrLth[ MAX_BOUND_PARAMETERS ];
   SQLHENV        henv;
   SQLHDBC        hdbc;
   SQLHSTMT       hstmt;
   SQLHSTMT       hGeneralStmt;

   // We need a table to keep track of all the stmt handles for activates.
   LPHANDLES      lpHandles[ MAX_LODS_IN_ONE_ACTIVATE ];

   // Following used to keep track of LODs loaded using static SQL.
   LPOD_LIST      lpFirstOD_List;

#elif defined( DUMMY )

   zLONG          lIntegerCount;
   zLONG          lDecimalCount;
   zLONG          lStringCount;

#elif defined( ODBC )

   // Following table used for binding long parameters.
   SQLINTEGER     nStrLth[ MAX_BOUND_PARAMETERS ];

   HENV           henv;
   HDBC           hdbc;
   HSTMT          hstmt;
   HSTMT          hGeneralStmt;

   // We need a table to keep track of all the stmt handles for activates.
   LPHANDLES      lpHandles[ MAX_LODS_IN_ONE_ACTIVATE ];

#endif

   // Used by dbhandlers that allow children to be loaded via joins.
   zPCHAR         pchEntityJoinTable;
   zLONG          lProcessID;

   zCHAR          szDebug2[ 20 ];
};

typedef struct DataFieldLoopStruct DataFieldLoopInfo;
typedef DataFieldLoopInfo *LPLOOPINFO;
struct DataFieldLoopStruct
{
   zBOOL          bOpenSQL;
   zBOOL          bKeysOnly;
   zSHORT         nDataFieldIdx;
   LPQUALENTITY   lpQualEntity;
   LPQUALENTITY   lpFirstQualEntity;
   LPVIEWENTITY   lpViewEntity;
   LPVIEWENTITY   lpChildEntity;
   LPDATAFIELD    lpDataField;
   zLONG          lControl;
   LPBOUNDLIST    lpBoundList;

   // Some DB's (ODBC for instance) require two passes when looping through
   // datafields.  This keeps track.
   zBOOL          bFirstPass;

};

zLONG g_lCurrentProcessID;

/////////////////////////// FUNCTION PROTYPES //////////////////////////////

void
fnSqlRC( zPCHAR       pchRoutine,
         zSHORT       nRC,
         zPCHAR       pchInfo1,
         zPCHAR       pchInfo2,
         zSHORT       nTrcLvl,
         LPCONNECTION lpConnection );

void
DisplayCommand( zPCHAR       pchRoutine,
                zSHORT       nRC,
                LPCONNECTION lpConnection );

void DBH_Error( zVIEW lpView, zPCHAR pchErrorMsg, int nRC, zPCHAR pchInfo );

zSHORT WriteLongChar( LPCONNECTION lpConnection,
                      LPBOUNDLIST  lpBoundList );

zSHORT OPERATION
fnDBH_Callback( zULONG      nCommand,
                zVIEW       lpView,
                LPBOUNDLIST lpBoundList,
                LPDATAFIELD lpDataField,
                zPVOID      pInfo,
                zPCHAR      pchTarget );

zSHORT LOCALOPER
fnClearDBHandlerError( zVIEW vTask );

zSHORT LOCALOPER
fnSetDBHandlerError( zVIEW vTask,
                     zLONG lCode,
                     zPCHAR szState,
                     zPCHAR szMsg );

zSHORT LOCALOPER
fnOpenDatabaseConnection( zVIEW        lpView,
                          LPVIEWOD     lpViewOD,
                          LPVIEWENTITY lpViewEntity,
                          LPCONNECTION lpConnection );

// If ulLth is zero, the memory will be freed (no allocation).
zSHORT LOCALOPER
fnAllocateConnectionMemory( zVIEW        lpView,
                            LPCONNECTION lpConnection,
                            zBOOL        bSqlCmd,
                            zULONG       ulLth )
{
   if ( bSqlCmd )
   {
   // TraceLine( "fnAllocateConnectionMemory (PRE ) for Task: 0x%08x   Connection.CmdMem.SqlCmd: 0x%08x.0x%08x.0x%08x  SQL Lth: %d",
   //            SysGetTaskFromView( lpView ), lpConnection, lpConnection->hCmdMem, lpConnection->pchConnSqlCmd, ulLth ); // dks debug

      if ( lpConnection->hCmdMem )
      {
         SysFreeMemory( lpConnection->hCmdMem );
         lpConnection->hCmdMem = 0;
         lpConnection->pchConnSqlCmd = 0;
      }

      if ( ulLth )
      {
         lpConnection->hCmdMem = SysAllocMemory( &lpConnection->pchConnSqlCmd,
                                                 ulLth, 0, zCOREMEM_ALLOC, 0 );
         lpConnection->lProcessID = SysGetProcessID( 0 );
      }

   // TraceLine( "fnAllocateConnectionMemory (POST) for Task: 0x%08x   Connection.CmdMem.SqlCmd: 0x%08x.0x%08x.0x%08x  SQL Lth: %d",
   //            SysGetTaskFromView( lpView ), lpConnection, lpConnection->hCmdMem, lpConnection->pchConnSqlCmd, ulLth ); // dks debug
   }
   else
   {
   // TraceLine( "fnAllocateConnectionMemory (PRE ) for Task: 0x%08x   Connection.TblMem.Buffer: 0x%08x.0x%08x.0x%08x  TBL Lth: %d",
   //            SysGetTaskFromView( lpView ), lpConnection, lpConnection->hTblMem, lpConnection->pchGlobalTableBuffer, ulLth ); // dks debug
      if ( lpConnection->hTblMem )
      {
         SysFreeMemory( lpConnection->hTblMem );
         lpConnection->hTblMem = 0;
         lpConnection->pchGlobalTableBuffer = 0;
         lpConnection->lTblSize = 0;
      }

      if ( ulLth )
      {
         lpConnection->hTblMem =
                     SysAllocMemory( &lpConnection->pchGlobalTableBuffer,
                                     ulLth, 0, zCOREMEM_ALLOC, 0 );
         lpConnection->lTblSize = ulLth;
         lpConnection->lProcessID = SysGetProcessID( 0 );
      }

   // TraceLine( "fnAllocateConnectionMemory (POST) for Task: 0x%08x   Connection.TblMem.Buffer: 0x%08x.0x%08x.0x%08x  TBL Lth: %d",
   //            SysGetTaskFromView( lpView ), lpConnection, lpConnection->hTblMem, lpConnection->pchGlobalTableBuffer, ulLth ); // dks debug
   }

   return( 0 );
}

//=========================================================================
//       DATBASE-SPECIFIC FUNCTIONS
//=========================================================================

#if defined ( DB2 )

LPOD_LIST
fnFindOD( LPVIEWOD lpViewOD, LPCONNECTION lpConnection )
{
   LPOD_LIST lpOD;

   for ( lpOD = lpConnection->lpFirstOD_List;
         lpOD;
         lpOD = lpOD->lpNextOD )
   {
      if ( lpOD->lpViewOD == lpViewOD )
         return( lpOD );
   }

   return( 0 );
}

LPOD_LIST
fnAddOD( LPVIEWOD lpViewOD, LPCONNECTION lpConnection )
{
   zLONG     hMem;
   LPOD_LIST lpOD;

   hMem = SysAllocMemory( (zCOREMEM) &lpOD, zsizeof( OD_ListRecord ), 0,
                          zCOREMEM_ALLOC, 0 );
   zmemset( lpOD, 0, zsizeof( OD_ListRecord ) );
   lpOD->lpViewOD = lpViewOD;
   lpOD->hMem     = hMem;
   strcpy_s( lpOD->szOD_Name, lpViewOD->szName );

   lpOD->lpNextOD = lpConnection->lpFirstOD_List;
   lpConnection->lpFirstOD_List = lpOD;

   return( lpOD );
}

void
fnFreeOD_List( LPCONNECTION lpConnection )
{
   LPOD_LIST lpOD;
   LPOD_LIST lpNextOD;

   for ( lpOD = lpConnection->lpFirstOD_List;
         lpOD;
         lpOD = lpNextOD )
   {
      lpNextOD = lpOD->lpNextOD;
      SysFreeMemory( lpOD->hMem );
   }

   lpConnection->lpFirstOD_List = 0;
}

#endif

#if defined ( DB2 ) || defined( ODBC )

void
fnFreeStmtHandles( LPCONNECTION lpConnection )
{
   zSHORT k, j;
   zSHORT nRC;

   if ( lpConnection->hGeneralStmt )
   {
#if defined( DB2 )
      nRC = SQLFreeHandle( SQL_HANDLE_STMT,
                           (SQLHANDLE) lpConnection->hGeneralStmt );
      SQL_RC( "SQLFreeHandle", nRC, "Closing stmt handle", 0, 2 );
#else
      nRC = SQLFreeHandle( SQL_HANDLE_STMT, lpConnection->hGeneralStmt );
      SQL_RC( "SQLFreeHandle", nRC, "Closing stmt handle", 0, 2 );
#endif

      lpConnection->hGeneralStmt = 0;
      lpConnection->hstmt = 0;
   }

   // If we're not using multiple handles then there's nothing else to free.
   if ( g_bHoldStmtHandles == FALSE )
      return;

   for ( k = 0; lpConnection->lpHandles[ k ]; k++ )
   {
      LPHANDLES     lpHandles = lpConnection->lpHandles[ k ];
      LPSTMTHANDLES lpStmtHandle = lpHandles->lpStmtHandles;

      for ( j = 1; j <= lpHandles->lpViewOD->uEntities; j++ )
      {
         if ( lpStmtHandle[ j ].hstmt == 0 )
            continue;

         // Close the handle.
#if defined( DB2 )
         nRC = SQLFreeHandle( SQL_HANDLE_STMT,
                              (SQLHANDLE) lpStmtHandle[ j ].hstmt );
         SQL_RC( "SQLFreeHandle", nRC, "Closing stmt handle", 0, 2 );
#else
         nRC = SQLFreeHandle( SQL_HANDLE_STMT, lpStmtHandle[ j ].hstmt );
         SQL_RC( "SQLFreeHandle", nRC, "Closing stmt handle", 0, 2 );
#endif

         // Free up memory.
         if ( lpStmtHandle[ j ].pchSqlCmd )
         {
            free( lpStmtHandle[ j ].pchSqlCmd );
            lpStmtHandle[ j ].pchSqlCmd = 0;
         }

         if ( lpStmtHandle[ j ].pchInputBuffer )
         {
            free( lpStmtHandle[ j ].pchInputBuffer );
            lpStmtHandle[ j ].pchInputBuffer = 0;
         }

         if ( lpStmtHandle[ j ].pchOutputBuffer )
         {
            free( lpStmtHandle[ j ].pchOutputBuffer );
            lpStmtHandle[ j ].pchOutputBuffer = 0;
         }

         if ( lpStmtHandle[ j ].ppchBufferPtr )
         {
            free( lpStmtHandle[ j ].ppchBufferPtr );
            lpStmtHandle[ j ].ppchBufferPtr = 0;
         }

         SqlFreeBoundAttrList( lpStmtHandle[ j ].lpBoundList );
         lpStmtHandle[ j ].lpBoundList = 0;

      } // for j...

      free( lpHandles->lpStmtHandles );
      lpHandles->lpStmtHandles = 0;

      free( lpConnection->lpHandles[ k ] );
      lpConnection->lpHandles[ k ] = 0;
      lpConnection->hstmt = 0;
      lpConnection->pchGlobalTableBuffer = 0;

   } // for k...

   if ( lpConnection->pchEntityJoinTable )
   {
      SysFree( lpConnection->pchEntityJoinTable );
      lpConnection->pchEntityJoinTable = 0;
   }
}

#endif

//=========================================================================
//       ENTITY FUNCTIONS
//=========================================================================

///////////////////////////////////////////////////////////////////////
//   InitDatabase
////////////////////////////////////////////////////////////////////////
zSHORT
InitDatabase( zVIEW lpView )
{
   zCHAR        szStr[ 2 ];
   zVIEW        vDbhWork;
   zSHORT       nRC;

   static zBOOL bShowDateTime = TRUE;

   g_lCurrentProcessID = SysGetProcessID( 0 );

   GetViewByName( &vDbhWork, zDBHANDLER_WORK_VIEW_NAME, lpView, zLEVEL_SYSTEM );
   if ( vDbhWork == 0 )
   {
      DBH_Error( lpView, "Can't find DB-Handler work view.", 0, 0 );
      return( zCALL_ERROR );
   }

   SysMutexLock( lpView, "Zeidon DBH", 0, 0 );

   szStr[ 0 ] = zSQL_type;
   szStr[ 1 ] = 0;

   nRC = SetCursorFirstEntityByString( vDbhWork, "Type", "Type", szStr, "" );
   if ( nRC != zCURSOR_SET )
   {
      CreateEntity( vDbhWork, "Type", zPOS_AFTER );
      SetAttributeFromString( vDbhWork, "Type", "Type", szStr );

      // One-time-only DB initialization routines.
#if defined( ODBC )
      // Set up information shared by all ODBC tasks.
      {
         zCHAR            szValue[ 256 ] = "";
         ODBC_SYSTEM_INFO OdbcSystemInfo = { 0 };

         SysReadZeidonIni( -1, "[kzhsqloa]", "CommitLatency", szValue, zsizeof( szValue ) );
         OdbcSystemInfo.lCommitLatency = (zULONG) zatol( szValue );

         SetAttributeFromBlob( vDbhWork, "Type", "TypeEnvBlob",
                               &OdbcSystemInfo, sizeof( OdbcSystemInfo ) );

      }

#endif
   }

   // Once-per-task initialization.
#if defined( DB2 ) || defined( ODBC )

   if ( g_bHoldStmtHandles == 'X' )
   {
      zCHAR szValue[ 256 ] = "";

      SysReadZeidonIni( -1, "[kzhsqloa]", "HoldStmtHandles", szValue, zsizeof( szValue ) );
      switch ( ztoupper( szValue[ 0 ] ) )
      {
         case 'F':
         case 'N':
         case '0':
            g_bHoldStmtHandles = FALSE;
            break;

         case 'T':
         case 'Y':
         case '1':
            g_bHoldStmtHandles = TRUE;
            break;

         default:
            // We'll default DB2 to off until we can fix the problems.
            #if defined( DB2 )
               g_bHoldStmtHandles = FALSE;
            #else
               g_bHoldStmtHandles = TRUE;
            #endif

            break;
      }

      #if defined( ODBC )
         GetAddrForAttribute( (zCOREMEM) &g_lpOdbcSystemInfo,
                              vDbhWork, "Type", "TypeEnvBlob" );
      #endif
   }

#endif

   SysMutexUnlock( lpView, "Zeidon DBH", 0 );

   if ( bShowDateTime )
   {
      TraceLineS( "Compile date/time for " DBHANDLER_NAME " is ",
                  __DATE__ " " __TIME__ );
      bShowDateTime = FALSE;
   }

   return( 0 );

}  /* InitDatabase */

////////////////////////////////////////////////////////////////////////
//
//  CloseDatabase
//
//  Frees any memory allocate by the db-handler and closes all databases.
//
////////////////////////////////////////////////////////////////////////
zSHORT
CloseDatabase( zVIEW lpView, int Indicators )
{
   LPCONNECTION lpConnection;
   zCHAR        szLogicalName[ 64 ];
   zCHAR        szStr[ 2 ];
   zVIEW        vDbhWork;
   LPTASK       hTask;
// zLONG        lProcessID;
   zSHORT       nRC2 = 0;
   zSHORT       nRC;

   GetViewByName( &vDbhWork, zDBHANDLER_WORK_VIEW_NAME, lpView, zLEVEL_SYSTEM );
   if ( vDbhWork == 0 )
   {
      DBH_Error( lpView, "Can't find DB-Handler work view.", 0, 0 );
      return( zCALL_ERROR );
   }

   if ( lpView == 0 )
      lpView = vDbhWork;

   SysMutexLock( lpView, "Zeidon DBH", 0, 0 );

   szStr[ 0 ] = zSQL_type;
   szStr[ 1 ] = 0;

   nRC = SetCursorFirstEntityByString( vDbhWork, "Type", "Type", szStr, "" );
   if ( nRC != zCURSOR_SET )
   {
      zCHAR szMsg[ 256 ];

      SysMutexUnlock( lpView, "Zeidon DBH", 0 );
      sprintf_s( szMsg, zsizeof( szMsg ),
                 "Internal error -- cannot find DB Base type (%s) in db-handler work object.",
                 szStr );
      DBH_Error( vDbhWork, szMsg, 0, 0 );
      DropView( vDbhWork );
      return( zCALL_ERROR );
   }

   hTask = (LPTASK) SysGetTaskFromView( lpView );
   sprintf_s( szLogicalName, zsizeof( szLogicalName ), "0x%08x:%08x", (zULONG) hTask, SysGetProcessID( 0 ) );
   nRC = SetCursorFirstEntityByString( vDbhWork, "Connection",
                                       "LogicalUserName", szLogicalName, "" );
   if ( nRC != zCURSOR_SET )
   {
      zPCHAR pch;
      zLONG  lLth = zstrlen( szLogicalName );

      nRC = SetCursorFirstEntity( vDbhWork, "Connection", 0 );
      while ( nRC >= zCURSOR_SET )
      {
         GetAddrForAttribute( &pch, vDbhWork, "Connection", "LogicalUserName" );
         if ( zstrncmp( szLogicalName, pch, lLth ) == 0 )
            break;

         nRC = SetCursorNextEntity( vDbhWork, "Connection", 0 );
      }
   }

   if ( nRC != zCURSOR_SET )
   {
      zCHAR szMsg[ 256 ];

      SysMutexUnlock( lpView, "Zeidon DBH", 0 );
      sprintf_s( szMsg, zsizeof( szMsg ),
                 "TaskID not found for Task:TaskID %s",
                 szLogicalName );

      TraceLineS( "ERROR ********** CloseDatabase ", szMsg );
      DisplayObjectInstance( vDbhWork, 0, 0 );
      TraceLineS( "", "" );
      // Removing this message since we were getting it when all tasks have
      // been deleted.  dks/don 2007.01.05
   // MessageBox( 0, szMsg, "CloseDatabase Error", MB_OK );
      return( 0 );
   }

   GetAddrForAttribute( (zPVOID) &lpConnection, vDbhWork,
                        "Connection", "ConnectionBlob" );
   if ( lpConnection )
   {
      zSHORT k;

      // Free connection memory (last parm zero).
      fnAllocateConnectionMemory( lpView, lpConnection, TRUE, 0 );
      fnAllocateConnectionMemory( lpView, lpConnection, FALSE, 0 );

      // Free up qual data.
      for ( k = 0; k < lpConnection->nQualCount; k++ )
         SqlFreeQualEntity( &lpConnection->lpQualEntityList[ k ] );

      lpConnection->nQualCount = 0;

      // Only perform the disconnect if there was a valid connection.
      for ( k = 0; k < lpConnection->nOpenDatabaseCount; k++ )
      {
         if ( lpConnection->DBConnection[ k ].bValidConnection == FALSE )
            continue;

         // DB disconnect routines.

#if defined( DB2 )

         nRC = SQLDisconnect( lpConnection->DBConnection[ k ].hdbc );
         SQL_RC( "SQLDisconnect", nRC, "Disconnecting handle for database ",
                 lpConnection->DBConnection[ k ].szDatabaseName, 2 );

         nRC = SQLFreeHandle( SQL_HANDLE_DBC,
                          (SQLHANDLE) lpConnection->DBConnection[ k ].hdbc );

         SQL_RC( "SQLFreeHandle", nRC, "Closing handle for database ",
                 lpConnection->DBConnection[ k ].szDatabaseName, 2 );
         if ( nRC != SQL_SUCCESS )
            nRC = zCALL_ERROR;

#elif defined( ODBC )

         nRC = SQLDisconnect( lpConnection->DBConnection[ k ].hdbc );
         SQL_RC( "SQLDisconnect", nRC, "Disconnecting handle for database ",
                 lpConnection->DBConnection[ k ].szDatabaseName, 2 );

         nRC = SQLFreeHandle( SQL_HANDLE_DBC,
                          (SQLHANDLE) lpConnection->DBConnection[ k ].hdbc );
         SQL_RC( "SQLFreeHandle", nRC, "Closing handle for database ",
                 lpConnection->DBConnection[ k ].szDatabaseName, 2 );
         if ( nRC != SQL_SUCCESS )
            nRC2 = zCALL_ERROR;

#endif

         lpConnection->DBConnection[ k ].bValidConnection = FALSE;

      } // for ( k = 0; ... )

      //
      // Session disconnect routines.
      //

#if defined( DB2 )
   {
      LPOD_LIST lpOD;

      for ( lpOD = lpConnection->lpFirstOD_List;
            lpOD;
            lpOD = lpOD->lpNextOD )
      {
         if ( lpOD->bOpenConn )
         {
#if 0
            zSHORT (POPERATION pfnClose)( zSHORT );
            zCHAR  szFuncName[ 200 ];

            sprintf_s( szFuncName, zsizeof( szFuncName ), "%s_CloseConnection", lpOD->szOD_Name );
            pfnClose = SysGetProc( lpOD->hStaticLibrary, szFuncName );
            nRC = (*pfnClose) ( lpConnection->nTraceLevel );
#endif
            SysFreeLibrary( lpView, lpOD->hStaticLibrary );
         }
      }

      fnFreeOD_List( lpConnection );

      if ( lpConnection->henv )
      {
         nRC = SQLFreeHandle( SQL_HANDLE_ENV,
                              (SQLHANDLE) lpConnection->henv );
         SQL_RC( "SQLFreeHandle", nRC, "Closing henv", 0, 2 );
      }
   }

#elif defined( ODBC )

      nRC = SQLFreeHandle( SQL_HANDLE_ENV,
                           (SQLHANDLE) lpConnection->henv );
      SQL_RC( "SQLFreeHandle", nRC, "Closing henv", 0, 2 );

#endif

      SfDropSubtask( lpConnection->lpAppView, 0 );

   } // if ( lpConnection )...

   SetAttributeFromBlob( vDbhWork, "Connection", "ConnectionBlob", 0, 0 );
   DeleteEntity( vDbhWork, "Connection", zREPOS_AFTER );  // blew on this line 2006.06.30 dks

// TraceLineS( "After CloseDatabase for Task:TaskID ", szLogicalName );
// DisplayObjectInstance( vDbhWork, 0, 0 );
// TraceLineS( "", "" );

   SysMutexUnlock( lpView, "Zeidon DBH", 0 );

   return( nRC2 );

}  // CloseDatabase

////////////////////////////////////////////////////////////////////////
//
//  BeginTransaction
//
//  Checks to see if the database has already been opened and opens it
//  if needed.
//
////////////////////////////////////////////////////////////////////////
zSHORT
BeginTransaction( int          Indicators,
                  LPVIEWOD     lpViewOD,
                  zVIEW        lpView,
                  zVIEW        lpQualView,
                  LPCONNECTION lpConnection )
{
   if ( lpConnection->nTraceLevel > 0 )
   {
      zSHORT  k;

      TraceLineS( "####################################################", "" );
      TraceLineS( "##################  BEGIN TRANSACTION ##############", "" );
      TraceLineS( "####################################################", "" );
      if ( Indicators == ( Indicators & DBH_StoreOI ) )
         TraceLineS( "Storing Objects", "" );
      else
         TraceLineS( "Activating Object Def ", lpViewOD->szName );

      for ( k = 0; k < lpConnection->nOpenDatabaseCount; k++ )
         TraceLineS( "Database name = ",
                     lpConnection->DBConnection[ k ].szDatabaseName );

   }

#if 0  // Following not needed yet but could be someday.
   // Check to see if multiple databases are used.
   lpConnection->bMultipleDatabases = FALSE;
   lpViewEntity = lpViewOD->hFirstOD_Entity;
   while ( lpViewEntity )
   {
      if ( lpViewEntity->szDBName[ 0 ] )
         lpConnection->bMultipleDatabases = TRUE;

      lpViewEntity = lpViewEntity->hNextHier;
   }
#endif

   //==============================================================
   //
   // Transaction Begin code.
   //
   //==============================================================

   // Indicate that the database has not yet been changed by this transaction.
   lpConnection->bDatabaseChanged = FALSE;

#if defined ( DB2 )
   /* if we have DB2, determine the decimal "comma or point"
    *  switch in zeidon.ini .
    *  Comma is indicated by "DB2COMMA=Y"
    */
   if ( g_ucDB2_Comma == 0 )
   {
      zCHAR szValue[ 256 ] ;

      szValue[ 0 ] = 0;
      SysReadZeidonIni( -1, "[Zeidon]", "DB2COMMA", szValue, zsizeof( szValue ) );
      if( szValue[ 0 ] == 'Y' || szValue[ 0 ] == 'y' ||
          szValue[ 0 ] == 'J' || szValue[ 0 ] == 'j' )
         g_ucDB2_Comma = 2;
      else
         g_ucDB2_Comma = 1;
   }

#elif defined( DUMMY )

   lpConnection->lIntegerCount = 1;
   lpConnection->lDecimalCount = 1;
   lpConnection->lStringCount  = 1;

#elif defined( ODBC )

   // For MS Access we need to wait a short bit of time if another task has
   // done a commit.  This gives a chance for the database changes to be
   // seen by other tasks.
   if ( g_lpOdbcSystemInfo->lCommitLatency > 0   &&  // If 0 we don't need to wait
        g_lpOdbcSystemInfo->lLastCommitTask != 0 &&  // 0 means nothing committed yet
        (Indicators & DBH_LoadOI ) != 0          &&  // Only wait before Activate
        g_lpOdbcSystemInfo->lLastCommitTask !=
              SysGetTaskFromView( lpView ) ) // Don't need to wait for current task.
   {
      zULONG ulTimeSinceLastCommit = SysGetTickCount( ) -
                                          g_lpOdbcSystemInfo->lLastCommitTime;

      if ( ulTimeSinceLastCommit < g_lpOdbcSystemInfo->lCommitLatency )
      {
         zULONG lWait;


         lWait = g_lpOdbcSystemInfo->lCommitLatency - ulTimeSinceLastCommit;
         if ( lpConnection->nTraceLevel > 0 )
            TraceLineI( "ODBC Latency...waiting... milliseconds = ", lWait );

         SysWait( (zUSHORT) lWait );
      }
   }

#endif

   fnClearDBHandlerError( lpQualView ? lpQualView : lpView );

   if ( lpConnection->vDbhWork )
   {
      DropView( lpConnection->vDbhWork );
      lpConnection->vDbhWork = 0;
   }

   return( 0 );

}  /* BeginTransaction */

/////////////////////////////////////////////////////////////////////////////
//
//    CommitTransaction
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
CommitTransaction( zVIEW        lpView,
                   int          Indicators,
                   LPCONNECTION lpConnection )
{
   zSHORT k;
   zSHORT nReturnCode = 0;
   zSHORT nRC = 0;

   // Do any object ordering as necessary.
   if ( Indicators & DBH_LoadOI )
      OrderOI_ByDefaultAttribs( lpView );

   if ( lpConnection == 0 )
   {
      TraceLineS( "lpConnection is null!!!!!!", "" );
      return( zCALL_ERROR );
   }

   if ( lpConnection->nTraceLevel > 0 )
   {
      TraceLineS( "####################################################", "" );
      TraceLineS( "#################  COMMIT TRANSACTION ##############", "" );
      TraceLineS( "####################################################", "" );
   }

   // Free up qual data.
   for ( k = 0; k < lpConnection->nQualCount; k++ )
      SqlFreeQualEntity( &lpConnection->lpQualEntityList[ k ] );

   lpConnection->nQualCount = 0;

#if 0 // Following not needed...yet.
   for ( k = 0; k < lpConnection->nOpenDatabaseCount; k++ )
   {
      if ( lpConnection->DBConnection[ k ].bDBUpdated )
      {
      }
   }
#endif

   //==============================================================
   //
   // Transaction Commit code.
   //
   //==============================================================

#if defined( DB2 )

{
   LPOD_LIST lpOD;

   for ( lpOD = lpConnection->lpFirstOD_List;
         lpOD;
         lpOD = lpOD->lpNextOD )
   {
      if ( lpOD->bNeedsCommit == FALSE )
         continue;

      if ( lpOD->pfnCommit == 0 )
      {
         zCHAR szProcName[ 100 ];

         sprintf_s( szProcName, zsizeof( szProcName ), "%s_Commit", lpOD->lpViewOD->szName );
         lpOD->pfnCommit = SysGetProc( lpOD->hStaticLibrary, szProcName );
      }

      nRC = (*lpOD->pfnCommit)( lpConnection->nTraceLevel );
      lpOD->bNeedsCommit = FALSE;
   }

   if ( lpConnection->hstmt )
   {
      fnFreeStmtHandles( lpConnection );

      nRC = SQLTransact( lpConnection->henv, lpConnection->hdbc, SQL_ROLLBACK );
      SQL_RC( "SQLEndTran", nRC, "Rollback DB ", 0, 1 );

      if ( nRC != SQL_SUCCESS )
         nReturnCode = zCALL_ERROR;
   }
}

#elif defined( ODBC )

   // If the current transaction has changed the database, we may need to set
   // some flags so subsequent activates have a chance to reflect the changes.
   if ( lpConnection->bDatabaseChanged &&
        g_lpOdbcSystemInfo->lCommitLatency > 0 )
   {
      g_lpOdbcSystemInfo->lLastCommitTask = SysGetTaskFromView( lpView );
      g_lpOdbcSystemInfo->lLastCommitTime = SysGetTickCount( );
   }

   nRC = SQLEndTran( SQL_HANDLE_DBC, lpConnection->hdbc, SQL_COMMIT );
   SQL_RC( "SQLEndTran", nRC, "Commit DB ", 0, 1 );

   if ( nRC != SQL_SUCCESS )
      nReturnCode = zCALL_ERROR;

   fnFreeStmtHandles( lpConnection );

#endif

   if ( lpConnection->vDbhWork )
   {
      DropView( lpConnection->vDbhWork );
      lpConnection->vDbhWork = 0;
   }

   return( nReturnCode );

}  /* CommitTransaction */

/////////////////////////////////////////////////////////////////////////////
//
//    RollbackTransaction
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
RollbackTransaction( int Indicators, LPCONNECTION lpConnection )
{
   zSHORT k;
   zSHORT nReturnCode = 0;
   zSHORT nRC = 0;

   if ( lpConnection == 0 )
   {
      TraceLineS( "lpConnection is null!!!!!!", "" );
      return( 0 );
   }

   if ( lpConnection->nTraceLevel > 0 )
   {
      TraceLineS( "####################################################", "" );
      TraceLineS( "################ ROLLBACK TRANSACTION ##############", "" );
      TraceLineS( "####################################################", "" );
   }

   // Free up qual data.
   for ( k = 0; k < lpConnection->nQualCount; k++ )
      SqlFreeQualEntity( &lpConnection->lpQualEntityList[ k ] );
   lpConnection->nQualCount = 0;

   //==============================================================
   //
   // Transaction Rollback code.
   //
   //==============================================================

#if defined( DB2 )

{
   LPOD_LIST lpOD;

   for ( lpOD = lpConnection->lpFirstOD_List;
         lpOD;
         lpOD = lpOD->lpNextOD )
   {
      if ( lpOD->bNeedsCommit == FALSE )
         continue;

      if ( lpOD->pfnRollback == 0 )
      {
         zCHAR szProcName[ 100 ];

         sprintf_s( szProcName, zsizeof( szProcName ), "%s_Rollback", lpOD->lpViewOD->szName );
         lpOD->pfnRollback = SysGetProc( lpOD->hStaticLibrary, szProcName );
      }

      nRC = (*lpOD->pfnRollback)( lpConnection->nTraceLevel );
      lpOD->bNeedsCommit = FALSE;
   }

   if ( lpConnection->hstmt )
   {
      fnFreeStmtHandles( lpConnection );

      nRC = SQLTransact( lpConnection->henv, lpConnection->hdbc, SQL_ROLLBACK );
      SQL_RC( "SQLEndTran", nRC, "Rollback DB ", 0, 1 );

      if ( nRC != SQL_SUCCESS )
         nReturnCode = zCALL_ERROR;
   }
}

#elif defined( ODBC )

   nRC = SQLEndTran( SQL_HANDLE_DBC, lpConnection->hdbc, SQL_ROLLBACK );
   SQL_RC( "SQLEndTran", nRC, "Rollback DB ", 0, 1 );

   if ( nRC != SQL_SUCCESS )
      nReturnCode = zCALL_ERROR;

   fnFreeStmtHandles( lpConnection );

#endif

   return( nReturnCode );

}  /* RollbackTransaction */

//=========================================================================
//       ENTITY FUNCTIONS
//=========================================================================

// ================================================================
// fnCancelQuery
// ================================================================

void
fnCancelQuery( LPCONNECTION lpConnection )
{
   return;
}

zBOOL LOCALOPER
fnFindNextJoinedChild( LPVIEWENTITY lpParent,
                       LPVIEWENTITY *plpChildEntity,
                       zPCHAR       pchEntityJoinTable )
{
   if ( *plpChildEntity == 0 )
      *plpChildEntity = lpParent;

   // DBHandler has said there might be more children so look for them.
   *plpChildEntity = zGETPTR( (*plpChildEntity)->hNextHier );
   while ( *plpChildEntity )
   {
      if ( *plpChildEntity == 0 ||
           (*plpChildEntity)->nLevel <= lpParent->nLevel )
      {
         return( FALSE );
      }

      // If the child was not joined, skip it.
      if ( (pchEntityJoinTable[ (*plpChildEntity)->nHierNbr ] &
                                       zSELECT_JOINEDWITHPARENT) == 0 )
      {
         zSHORT nLevel;

         // This entity was not joined so skip it.  We also want to skip all
         // its children.
         if ( (*plpChildEntity)->hNextSibling )
         {
            (*plpChildEntity) = zGETPTR( (*plpChildEntity)->hNextSibling );
            continue;
         }

         // (*plpChildEntity) has no siblings.  Find the next entity by trolling
         // through the children hierachically.
         nLevel = (*plpChildEntity)->nLevel;
         while ( (*plpChildEntity) && (*plpChildEntity)->nLevel >= nLevel )
         {
            while ( (*plpChildEntity)->hNextSibling )
               (*plpChildEntity) = zGETPTR( (*plpChildEntity)->hNextSibling );

            (*plpChildEntity) = zGETPTR( (*plpChildEntity)->hNextHier );
         }

         continue;
      }

      // If we get here then we've found what we're looking for.
      return( TRUE );
   }

   // If we get here then *plpChildEntity must be 0 so return FALSE.
   return( FALSE );
}

// We have two different lists
// of data fields that we might be traversing.  The first is just the
// normal data field list.  The second is the table of data fields
// generated as part of an OpenSQL statement.  This list is stored
// sequentially in a table.
LPDATAFIELD LOCALOPER
fnGetNextDataField( LPLOOPINFO lpLoopInfo )
{
   // Loop until we find the next valid datafield.
   while ( TRUE )
   {
      LPVIEWATTRIB lpViewAttrib;

      if ( lpLoopInfo->lpDataField == 0 )
      {
         // First time this is called...initialize some stuff.
         lpLoopInfo->nDataFieldIdx = 0;
         lpLoopInfo->lpChildEntity = 0;

         if ( lpLoopInfo->bOpenSQL )
            lpLoopInfo->lpDataField =
              lpLoopInfo->lpQualEntity->lpDataField[ lpLoopInfo->nDataFieldIdx++ ];
         else
         {
            LPDATARECORD lpDataRecord =
                           zGETPTR( lpLoopInfo->lpViewEntity->hFirstDataRecord );

            lpLoopInfo->lpDataField = zGETPTR( lpDataRecord->hFirstDataField );
         }
      }
      else
      {
         // Get the 'next' data field.
         if ( lpLoopInfo->bOpenSQL )
         {
            lpLoopInfo->lpDataField =
              lpLoopInfo->lpQualEntity->lpDataField[ lpLoopInfo->nDataFieldIdx++ ];
         }
         else
         {
            lpLoopInfo->lpDataField =
                        zGETPTR( lpLoopInfo->lpDataField->hNextDataField );

#ifdef USE_JOINS
            if ( (lpLoopInfo->lpBoundList->lFuncs & zSQLCALLBACK_USEJOIN) &&
                 lpLoopInfo->lpDataField == 0 &&
                 (lpLoopInfo->lControl & zACTIVATE_ROOTONLY) == 0 )
            {
               // See if there are any child entities that have been included
               // as part of a join.
               if ( fnFindNextJoinedChild( lpLoopInfo->lpViewEntity,
                                           &lpLoopInfo->lpChildEntity,
                                           lpLoopInfo->
                                              lpBoundList->pchEntityJoinTable ) )
               {
                  LPDATARECORD lpDataRecord;

                  // We have one.  Let's loop through it's data fields.
                  lpDataRecord =
                        zGETPTR( lpLoopInfo->lpChildEntity->hFirstDataRecord );
                  lpLoopInfo->lpDataField = zGETPTR( lpDataRecord->hFirstDataField );
               }
            }
#endif // USE_JOINS

         }
      }

      // If the data field is 0 then we're done.
      if ( lpLoopInfo->lpDataField == 0 )
      {
#ifdef ODBC
         if ( lpLoopInfo->bFirstPass )
         {
            lpLoopInfo->bFirstPass  = FALSE;
            lpLoopInfo->lpDataField = 0;
            continue;
         }
#endif

         return( 0 );
      }

      lpViewAttrib = zGETPTR( lpLoopInfo->lpDataField->hViewAttrib );

      // If we aren't using OpenSQL, then we might want to ignore certain
      // attributes.
      if ( lpLoopInfo->bOpenSQL == FALSE )
      {
         LPVIEWENTITY lpLoadViewEntity;

         // If we only want the keys and the attrib/datafield is not a key,
         // continue.
         if ( lpLoopInfo->bKeysOnly && lpViewAttrib->bKey == FALSE )
            continue;

         // Ignore hidden attributes that aren't keys.
         if ( lpViewAttrib->bHidden &&
              lpViewAttrib->bKey == FALSE &&
              lpViewAttrib->bForeignKey == FALSE &&
              lpViewAttrib->bAutoSeq == FALSE )
         {
            continue;
         }

         lpLoadViewEntity = zGETPTR( lpViewAttrib->hViewEntity );

         // If the entity has a db operation, then skip attributes that don't
         // have a db operation.
         if ( lpLoadViewEntity->bHasDB_Oper && lpViewAttrib->cDB_Oper == 0 )
            continue;
      }

#ifdef ODBC
      if ( lpLoopInfo->bFirstPass )
      {
         if ( lpLoopInfo->lpDataField->cFldType == zTYPE_BLOB ||
              lpLoopInfo->lpDataField->cFldType == 'V' )
         {
            // Skip long fields on the first pass.
            continue;
         }
      }
      else
      {
         if ( lpLoopInfo->lpDataField->cFldType != zTYPE_BLOB &&
              lpLoopInfo->lpDataField->cFldType != 'V' )
         {
            // Skip NON-long fields on the second pass.
            continue;
         }
      }
#endif

      // If we get here then we've found our man.
      return( lpLoopInfo->lpDataField );

   } // while ( TRUE )...

   // We will never get here but this line in here so we don't get any
   // compiler warnings.
   return( lpLoopInfo->lpDataField );
}

/*

   The user has qualified a SELECT by using a list of keys.  We will take the
   list of keys and populate a table with the key values.  Then the SELECT stmt
   will use "SELECT cols FROM table WHERE key IN ( SELECT key FROM keytable )".

*/
zSHORT LOCALOPER
fnCreateKeyList( zLONG        hTask,
                 LPCONNECTION lpConnection,
                 LPBOUNDLIST  lpBoundList,
                 LPQUALENTITY lpQualEntity )
{
   LPQUALATTRIB lpQualAttrib;

   // Find the qual attrib with the key list.
   for ( lpQualAttrib = lpQualEntity->lpFirstQualAttrib;
         lpQualAttrib->lpKeyList == 0;
         lpQualAttrib = lpQualAttrib->lpNextQualAttrib )
   {
      // Nothing needs to be done here.
   }

#if defined( DB2 ) || defined( ODBC )
   {
      HSTMT          hstmt;
      zSHORT         nRC;
      zSHORT         k;
      SQLSMALLINT    nC_DataType;
      SQLSMALLINT    nSQL_Type;
      SQLUINTEGER    nColumnSize;
      SQLINTEGER     nParmLth;
      SQLINTEGER     iBufferLth;
      SQLINTEGER     lKey;
      zPLONG         lKeyList;
      zCHAR          szCmd[ 300 ];

      // If we are holding stmt handles then we can use the "general" stmt
      // handle because each SELECT gets its own handle.  If we are not
      // holding handles then we have to create a temp one because the
      // general hstmt is being used by the current SELECT command.
      if ( g_bHoldStmtHandles )
         hstmt = lpConnection->hGeneralStmt;
      else
      {
         nRC = SQLAllocHandle( SQL_HANDLE_STMT, lpConnection->hdbc, &hstmt );
         SQL_RC( "SQLAllocHandle", nRC, "Allocate HSTMT", 0, 2 );
         if ( nRC != SQL_SUCCESS )
            return( zCALL_ERROR );
      }

      sprintf_s( szCmd, zsizeof( szCmd ),
                "INSERT INTO ZEIDONKEYLIST ( TASKID, INTVALUE ) VALUES ( %ld, ? )",
                hTask );
      nRC = SQLPrepare( hstmt, szCmd, SQL_NTS );
      SQL_RC( "SQLPrepare insert", nRC, 0, 0, 3 );

      nC_DataType = SQL_C_SLONG;
      nSQL_Type   = SQL_INTEGER;
      iBufferLth  = sizeof( zLONG );
      nColumnSize = sizeof( zLONG );
      nParmLth    = sizeof( zLONG );

      nRC = SQLBindParameter( hstmt, 1, SQL_PARAM_INPUT,
                              nC_DataType, nSQL_Type, nColumnSize, 0,
                              (SQLPOINTER) &lKey, iBufferLth,
                              &nParmLth );
      SQL_RC( "SQLBindParameter", nRC, "Column = ", "IntValue", 3 );
      if ( lpConnection->nTraceLevel > 2 )
      {
         TraceLineI( "nC_DataType = ", nC_DataType );
         TraceLineI( "nSQL_Type   = ", nSQL_Type );
         TraceLineI( "nColumnSize = ", nColumnSize );
      }

      lKeyList = (zPLONG) lpQualAttrib->lpKeyList;
      for ( k = 0; k < lpQualAttrib->lKeyCount; k++ )
      {
         lKey = lKeyList[ k ];

         nRC = SQLExecute( hstmt );
         SQL_RC( "SQLExecute", nRC, "Allocate HSTMT", 0, 2 );
      }

      // If we created a temp statement handle we need to free it.
      if ( g_bHoldStmtHandles == FALSE )
         SQLFreeHandle( SQL_HANDLE_STMT, (SQLHANDLE) hstmt );
   }
#endif

   return( 0 );
}

/*
   Set the cursor to match the keys listed in lpKeyData.  If an entity
   doesn't exist that matches the keys, one is created and the keys
   attributes are set.

   Returns: 1     - An entity was created.
            0     - A match was found, no entity created.
           -1     - No match found, but the entity is the root and we can
                    only create 1 root because bCreateMultipleRoots is FALSE.
*/
zSHORT LOCALOPER
fnSetEntityByKeys( zVIEW        lpView,
                   LPKEYDATA    lpKeyData,
                   zSHORT       nEntityKeyCnt,
                   zBOOL        bEntityCreatedList[],
                   zLONG        lRootLimit,
                   zLONG        lRootCnt,
                   LPBOUNDLIST  lpBoundList )
{
   LPDATAFIELD  lpDataField;
   LPVIEWATTRIB lpViewAttrib;
   LPVIEWENTITY lpLoadEntity;
   LPVIEWENTITY lpSearchEntity;
   zPVOID       lpPtr;
   zBOOL        bKeysMatch;
   zBOOL        bSearchNeeded;
   zSHORT       nKeyCnt;
   zSHORT       nRC;

   if ( nEntityKeyCnt == 0 )
      return( 0 );

   lpLoadEntity = lpKeyData[ 0 ].lpLoadEntity;

   // If a table has been joined with other tables, then it's possible for
   // the data for an entity to show up more than once.  To check for this,
   // we will search the entities to see if the entity already exists.
   // However, we don't need to do this if:
   //    o  The table wasn't joined
   //    o  The table was only joined with entities that have a x-to-1
   //       relationship.
   if ( lpBoundList->pchEntityJoinTable )
   {
      zPCHAR pchEntityJoinTable = lpBoundList->pchEntityJoinTable;

      bSearchNeeded = FALSE;

      for ( lpSearchEntity = lpLoadEntity;
            lpSearchEntity;
            lpSearchEntity = zGETPTR( lpSearchEntity->hParent ) )
      {
         // If entity has been flagged with MULTICHILD, then search is needed
         // and we can stop our loop.
         if ( (pchEntityJoinTable[ lpSearchEntity->nHierNbr ] &
                                           zSELECT_JOINEDWITHMULTCHILD) != 0 )
         {
            bSearchNeeded = TRUE;
            break;
         }

         // If entity hasn't been joined with a parent, we can stop checking.
         if ( (pchEntityJoinTable[ lpSearchEntity->nHierNbr ] &
                                           zSELECT_JOINEDWITHPARENT) == 0 )
         {
            break;
         }
      }
   }
   else
      bSearchNeeded = TRUE;

   if ( bSearchNeeded )
   {
      zLONG        lControl   = zQUAL_ATTR_HIDDEN | zQUAL_EQUAL;
      zCPVOID      pQualValue = (zCPVOID) lpKeyData[ 0 ].lpPtr;
      LPVIEWATTRIB lpLoopViewAttrib;

   // TraceLineS( "DGC", " Doing Search" );

      lpLoopViewAttrib = lpKeyData[ 0 ].lpViewAttrib;

      switch ( lpKeyData[ 0 ].lpDataField->cFldType )
      {
         case zTYPE_INTEGER:
            lControl |= zQUAL_INTEGER;
            break;

         case zTYPE_STRING:
            lControl |= zQUAL_STRING;
            break;

         case zTYPE_DECIMAL:
            lControl |= zQUAL_DECIMAL;
            break;

         default:
            SysMessageBox( lpView, "DBHandler Error",
                           "Key type not supported", 0 );
            bKeysMatch = FALSE;
            break;
      }

      // See if there is an entity that matches all the key values.
      for ( nRC = SetEntityCursor( lpView, lpLoadEntity->szName,
                                   lpLoopViewAttrib->szName,
                                   lControl | zPOS_FIRST, pQualValue, 0, 0,
                                   0, 0, 0 );
            nRC >= zCURSOR_SET;
            nRC = SetEntityCursor( lpView, lpLoadEntity->szName,
                                   lpLoopViewAttrib->szName,
                                   lControl | zPOS_NEXT, pQualValue, 0, 0,
                                   0, 0, 0 ) )
      {
         // Go through each of the keys and see if the current entity
         // matches the keys.  If not, try with the next entity.
         // Assume that the keys will match.
         bKeysMatch = TRUE;
         for ( nKeyCnt = 1; nKeyCnt < nEntityKeyCnt; nKeyCnt++ )
         {
            zCHAR        chType;
            zULONG       ulLth;

            lpDataField  = lpKeyData[ nKeyCnt ].lpDataField;
            lpViewAttrib = lpKeyData[ nKeyCnt ].lpViewAttrib;
            lpPtr        = lpKeyData[ nKeyCnt ].lpPtr;

            switch ( lpDataField->cFldType )
            {
               case zTYPE_INTEGER:
               {
                  zPLONG plKeyValue;

                  GetValueFromRecord( lpView, lpLoadEntity, lpViewAttrib,
                                      (zCOREMEM) &plKeyValue, &chType, &ulLth );

                  // Compare the attribute value with the one we got from
                  // the database.
                  if ( *plKeyValue != *((zPLONG) lpPtr) )
                     bKeysMatch = FALSE;

                  break;
               }

               case zTYPE_STRING:
               {
                  zPCHAR pchKeyValue;

                  GetValueFromRecord( lpView, lpLoadEntity, lpViewAttrib,
                                      (zCOREMEM) &pchKeyValue, &chType, &ulLth );

                  // Compare the attribute value with the one we
                  // got from the database.
                  if ( zstrcmp( pchKeyValue, (zPCHAR) lpPtr ) != 0 )
                     bKeysMatch = FALSE;

                  break;
               }

               case zTYPE_DECIMAL:
               {
                  // We retrieve the value from the database as a string.  Call
                  // CompareAttributeToString( ) so that we use domain processing.
                  if ( CompareAttributeToString( lpView, lpLoadEntity->szName,
                                                 lpViewAttrib->szName,
                                                 (zPCHAR) lpPtr ) != 0 )
                     bKeysMatch = FALSE;

                  break;
               }

               default:
                  SysMessageBox( lpView, "DBHandler Error", "Key type not supported", 0 );
                  bKeysMatch = FALSE;
                  break;

            } // switch ( lpDataField->cFldType )...

            // If we found a key that doesn't match, break loop and try
            // with the next entity.
            if ( bKeysMatch == FALSE )
               break;

         } // for ( nKeyCnt... )

         // If we get here and bKeysMatch is TRUE, then all the
         // keys for this entity matched, so we found the one we
         // want.  Stop looping through the entities.
         if ( bKeysMatch )
            return( 0 );       // Entity not created.

      } // for each lpLoadEntity...

   } // if ( lpBoundList->pchEntityJoinTable[ lpLoadEntity->nHierNbr ] != 0 )

   // If we get here, then we didn't find an entity whose keys matched those
   // in lpKeyData[], so we need to create one.

   // If hParent is null, then we are about to create a root.  Make sure we
   // haven't reached the limit yet.
   if ( lpLoadEntity->hParent == 0 && lRootCnt >= lRootLimit )
      return( -1 );

   LoadEntity( lpView, lpLoadEntity->szName, zPOS_LAST, 0 );

   // Loop through the keys and set the attribute values.
   for ( nKeyCnt = 0; nKeyCnt < nEntityKeyCnt; nKeyCnt++ )
   {
      lpDataField  = lpKeyData[ nKeyCnt ].lpDataField;
      lpViewAttrib = lpKeyData[ nKeyCnt ].lpViewAttrib;
      lpPtr   = lpKeyData[ nKeyCnt ].lpPtr;

      switch ( lpDataField->cFldType )
      {
         case zTYPE_DATETIME:
         case zTYPE_DATE:
         case zTYPE_TIME:
            StoreStringInRecord( lpView, lpLoadEntity, lpViewAttrib, lpPtr );
            break;

         case zTYPE_DECIMAL:
         {
            zCHAR szDecimal[ 100 ];

            StoreStringInRecord( lpView, lpLoadEntity, lpViewAttrib, lpPtr );

            // Retrieve decimal value and copy it back into the attribute.
            // This will cause the Format routines to be called so that
            // the decimal gets rounded/truncated correctly.
            GetStringFromRecord( lpView, lpLoadEntity, lpViewAttrib,
                                 szDecimal, zsizeof( szDecimal ) );
            StoreStringInRecord( lpView, lpLoadEntity, lpViewAttrib,
                                 szDecimal );

            break;
         }

         default:
            // Note that length is only used for blob attributes, so we will always pass 0.
            StoreValueInRecord( lpView, lpLoadEntity, lpViewAttrib, lpPtr, 0 );
            break;

      } // switch ( lpDataField->cFldType )...

   } // for ( nKeyCnt... )

   if ( bEntityCreatedList )
      bEntityCreatedList[ lpLoadEntity->nHierNbr ] = TRUE;

   // We created an entity so return 1.
   return( 1 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  Load
//
//  Loads entities of type lpViewEntity from the database.
//
//  Returns:    2 - Load worked--multi-root limit reached.
//              1 - Load worked--multiple roots found but only 1 loaded
//                  because Indicators = zSINGLE.
//              0 - Load worked--entity(-ies) loaded.
//             -1 - Load worked but couldn't find anything to load.
//    zCALL_ERROR - Call error
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
Load( LPVIEWENTITY lpViewEntity,
      zVIEW        lpView,
      LPVIEWOD     lpViewOD,
      zVIEW        lpQualView,
      LPCONNECTION lpConnection,
      int          Indicators )
{
   LPQUALENTITY      lpQualEntity;
   LPVIEWATTRIB      lpViewAttrib;
   LPDATARECORD      lpDataRecord;
   LPDATAFIELD       lpDataField;
   LPRELRECORD       lpRelRecord;
   LPATTRIBFLAGS     lpAttribFlags;
   LPBOUNDLIST       lpBoundList = 0;
   DataFieldLoopInfo LoopInfo;
   KeyData           lpKeyData[ 50 ];
   zPVOID            pvDBH_Data = 0;
   zPVOID            lpMem;
   zPCHAR            ppchBufferPtrArea[ MAX_COLUMNS ] = { 0 };
   zPPCHAR           ppchBufferPtr = ppchBufferPtrArea;
   zPCHAR            lpPtr;
   zULONG            ulTotalLth;
   zLONG             lRowCount;
   zLONG             lRootCnt;
   zLONG             lRootLimit;
   zLONG             hMem = 0;
   zLONG             lMemLth;
   zLONG             lFuncs;
   zBOOL             bKeyListCreated = FALSE;
   zBOOL             bCursorOpened = FALSE;
   zBOOL             bKeysOnly;
   zBOOL             bOpenSQL = FALSE;
   zBOOL             bCreateMultipleRoots = ((Indicators & zMULTIPLE) != 0);
   zBOOL             bRootLimitReached = FALSE;
   zSHORT            nEntityKeyCnt = 0;
   zSHORT            nColumnCnt;
   zSHORT            nReturnCode = zCALL_ERROR;
   zSHORT            nRC;

#if defined( DB2 )

   LPHANDLES      lpHandles = 0;
   LPSTMTHANDLES  lpStmtHandle = 0;

   // Define statements needed to load BLOB/CLOB columns.
   SQLHSTMT     hBlobStmt    = 0;
   SQLHSTMT     hLocatorStmt = 0;

   // Get a pointer to the dbh-specific data for DB2.
   CallbackInfoRecord CallbackInfo = { 0 };

   LPDB2_OBJECTDATA lpDB2_Data =
                           (LPDB2_OBJECTDATA) zGETPTR( lpViewOD->hDBH_Data );

   pvDBH_Data = &CallbackInfo;
   CallbackInfo.cBuildFunction = BUILD_SELECT;

#elif defined( ODBC )

   LPHANDLES          lpHandles = 0;
   LPSTMTHANDLES      lpStmtHandle = 0;
   CallbackInfoRecord CallbackInfo = { 0 };

   pvDBH_Data = &CallbackInfo;

   // Get a pointer to the dbh-specific data for ODBC.  We'll pass this info
   // around via the lpBoundList structure.
   CallbackInfo.lpObjectData = zGETPTR( lpViewOD->hDBH_Data );
   CallbackInfo.cBuildFunction = BUILD_SELECT;

#endif

   lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );
   lpRelRecord  = zGETPTR( lpDataRecord->hFirstRelRecord );

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "", "" );
      TraceLineS( "================= Performing load ===================", "" );
      TraceLineS( "  Entity name: ", lpViewEntity->szName );
      TraceLineS( "  Table name: ", lpDataRecord->szRecordName );
   }

#ifdef USE_JOINS
   // If we are loading only the root entities then we don't want to use a
   // join to load any children.
   lFuncs = zCB_FUNCS;
   if ( Indicators & zACTIVATE_ROOTONLY )
      lFuncs &= ~zSQLCALLBACK_USEJOIN;

   // Check to see if the entity was already loaded via a join.
   if ( lpConnection->pchEntityJoinTable == 0 )
   {
      // We haven't yet allocated the table to indicate what has been joined
      // so do it now.
      lpConnection->pchEntityJoinTable = SysMalloc( lpViewOD->uEntities + 1 );
   }
   else
   {
      // pchEntityJoinTable is an array of chars, one char for each entity in
      // the XOD.  If the bit for the current entity is non-zero, then the
      // entity has already been loaded via a join.
      if ( (lpConnection->pchEntityJoinTable[ lpViewEntity->nHierNbr ] &
                                            zSELECT_JOINEDWITHPARENT) != 0 )
      {
         if ( lpConnection->nTraceLevel > 1 )
            TraceLineS( "  Table loaded earlier as part of a join. Entity = ",
                        lpViewEntity->szName );

         nReturnCode = 0;

         // If the entity has hanging FKeys then we need to check to see if the
         // entity was loaded.  If not we want to return a -1 so that core knows
         // it should check to see if the entity has a hanging FK.
         if ( lpViewEntity->bHangingFKey )
         {
            if ( CheckExistenceOfEntity( lpView,
                                         lpViewEntity->szName ) != zCURSOR_SET )
               nReturnCode = -1;  // Indicates that entity doesn't exist.
         }

         goto EndOfFunction;
      }
   }

#ifdef DEBUG
   // DGC 6/22/2001
   // Put in a check to make sure that keys are sorted first.  This shouldn't
   // be necessary after everybody moves to new join code.
   lpDataField  = zGETPTR( lpDataRecord->hFirstDataField );
   lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );
   if ( lpViewAttrib->bKey == FALSE )
   {
      zCHAR szMsg[ 500 ];

      sprintf_s( szMsg, zsizeof( szMsg ), "XOD '%s' needs to be saved with new JOIN code. "
                 "Keys must be first for entity: %s.",
                 lpViewOD->szName, lpViewEntity->szName );
      SysMessageBox( lpView, "DBHandler Warning", szMsg, 0 );
   }
#endif

#endif

   SqlInitBoundAttrList( &lpBoundList, lpConnection->pchEntityJoinTable,
                         fnDBH_Callback, lFuncs, pvDBH_Data );

   // Until further notice we will return zCALL_ERROR if we exit early.

   if ( lpQualView )
   {
      zSHORT k;

      // Check to see if we've already stored the qual OI.  Start by looking
      // for lpQualView in the qualification list.
      for ( k = 0; k < lpConnection->nQualCount; k++ )
      {
         if ( lpConnection->vQualList[ k ] == lpQualView )
            break;
      }

      // If k = nQualCount then we didn't find lpQualView so we must extract
      // the OI to a QualEntity list.  If lpViewEntity is the root entity
      // then we'll reload the qualfication OI if lpQualView was found.
      if ( k == lpConnection->nQualCount || lpViewEntity->hParent == 0 )
      {
         // If there already is a lpQualEntity then we need to free up the
         // old one so we can create a new one.
         if ( lpConnection->lpQualEntityList[ k ] )
            SqlFreeQualEntity( &lpConnection->lpQualEntityList[ k ] );

         // Copy the contents of lpQualView to memory.
         nRC = SqlRetrieveQualObject( lpView, lpQualView, lpViewOD,
                                      &lpConnection->lpQualEntityList[ k ],
                                      lpBoundList );
         if ( nRC < 0 )
            goto EndOfFunction;

         // If this is a new view we must bump up our count.
         if ( k == lpConnection->nQualCount )
         {
            // Make sure that nQualCount doesn't get bigger than our max
            // count.  We have to subtract one from MAX_QUALIFICATIONS for
            // comparison because nQualCount can never be equal to
            // MAX_QUALIFICATIONS.
            if ( lpConnection->nQualCount < MAX_QUALIFICATIONS - 1 )
               lpConnection->nQualCount++;

            lpConnection->vQualList[ k ] = lpQualView;
         }
      }

      lpConnection->lpFirstQualEntity = lpConnection->lpQualEntityList[ k ];
   }
   else
   {
      // No qual entity so blank it out.
      lpConnection->lpFirstQualEntity = 0;
   }

   nRC = 0;
   bKeysOnly = FALSE;

   lpQualEntity = SqlEntityIsQualified( lpConnection->lpFirstQualEntity,
                                        lpViewEntity );

   if ( lpConnection->nTraceLevel > 2 )
   {
      if ( lpConnection->lpFirstQualEntity )
         TraceLineS( "  Table IS qualified.", "" );
      else
         TraceLineS( "  Table is not qualified.", "" );

      if ( lpViewEntity->hParent )
      {
         LPVIEWENTITY lpParent = zGETPTR( lpViewEntity->hParent );

         DisplayEntityInstance( lpView, lpParent->szName );
      }
   }

   if ( lpQualEntity && lpConnection->nTraceLevel > 2 )
      SqlDisplayQualEntity( lpQualEntity, FALSE );

#if defined( DB2 )
{
   LPOD_LIST lpOD = fnFindOD( lpViewOD, lpConnection );

   // Check for static bind.
   if ( lpDB2_Data && lpDB2_Data->bUseStaticSQL )
   {
      // Load static library if not already loaded.
      if ( lpOD->hStaticLibrary == 0 )
      {
         lpOD->hStaticLibrary = SysLoadLibrary( lpView,
                                                lpDB2_Data->szStaticSQL_DLL );
         if ( lpOD->hStaticLibrary == 0 )
            goto EndOfFunction;
      }

      if ( lpQualEntity == 0 )
      {
         zSHORT (POPERATION pfnFunc)( zVIEW, LPVIEWOD, LPVIEWENTITY,
                                      int, zSHORT );
         zCHAR  szFuncName[ 200 ];

         lpOD->bNeedsCommit = TRUE;

         // We have static binding so call the static function.
         sprintf_s( szFuncName, zsizeof( szFuncName ), "SQL_%s_%s_Select", lpOD->lpViewOD->szName,
                   lpViewEntity->szName );
         pfnFunc = SysGetProc( lpOD->hStaticLibrary, szFuncName );

         nRC = (*pfnFunc)( lpView, lpViewOD, lpViewEntity, Indicators,
                           lpConnection->nTraceLevel );

         nReturnCode = nRC;
         goto EndOfFunction;
      }
      else
      if ( lpQualEntity->bUniqueQualification )
      {
         zSHORT (POPERATION pfnFunc)( zVIEW, LPVIEWOD, LPVIEWENTITY,
                                      LPQUALENTITY, int, zSHORT );
         zCHAR  szFuncName[ 200 ];

         lpOD->bNeedsCommit = TRUE;

         // We have static binding so call the static function.
         sprintf_s( szFuncName, zsizeof( szFuncName ), "SQL_%s_%s_SelectUnique", lpOD->lpViewOD->szName,
                    lpViewEntity->szName );
         pfnFunc = SysGetProc( lpOD->hStaticLibrary, szFuncName );

         nRC = (*pfnFunc)( lpView, lpViewOD, lpViewEntity, lpQualEntity,
                           Indicators, lpConnection->nTraceLevel );

         nReturnCode = nRC;
         goto EndOfFunction;
      }

      // We have to use dynamic SQL so open a connection using it.
      fnOpenDatabaseConnection( lpView, lpViewOD, lpViewEntity, lpConnection );
   }
}
#endif

#if defined( DB2 ) || defined( ODBC )

   // Check to see if we've already generated/prepared the SQL for this
   // entity.
   if ( g_bHoldStmtHandles )
   {
      zSHORT rc;
      zSHORT k;

      // Find the handle info for this LOD.
      for ( k = 0; lpConnection->lpHandles[ k ]; k++ )
      {
         if ( lpConnection->lpHandles[ k ]->lpViewOD == lpViewOD )
            break;
      }

      // We need to allocate handles (and other info) for each of the entities
      // in the LOD.  If lpHandles is 0 we need to allocate it now.
      if ( lpConnection->lpHandles[ k ] == 0 )
      {
         zLONG lLth;

         lpConnection->lpHandles[ k ] = malloc( sizeof( SelectHandlesRecord ) );
         zmemset( lpConnection->lpHandles[ k ], 0, sizeof( SelectHandlesRecord ) );

         // It's just easier to allocate one extra record instead of worrying
         // about converting hier # to an offset.
         lLth = sizeof( EntityHandlesRecord ) * (lpViewOD->uEntities + 1);

         // We didn't find one so create space to store the handles.
         lpConnection->lpHandles[ k ]->lpViewOD = lpViewOD;
         lpConnection->lpHandles[ k ]->lpStmtHandles = malloc( lLth );
         zmemset( lpConnection->lpHandles[ k ]->lpStmtHandles, 0, lLth );
      }

      lpHandles    = lpConnection->lpHandles[ k ];
      lpStmtHandle = &lpHandles->lpStmtHandles[ lpViewEntity->nHierNbr ];

      // Check to see if a handle has been created for this entity.
      if ( lpStmtHandle->hstmt )
      {
         // Use the old bound list.  Free up the current one since we don't
         // need it anymore.
         SqlFreeBoundAttrList( lpBoundList );
         lpBoundList = lpStmtHandle->lpBoundList;

         // If we are using autoload, then we are only activating the keys,
         // so set the flag.
         if ( lpViewEntity->bAutoLoadFromParent )
            bKeysOnly = TRUE;

         if ( lpStmtHandle->bLoadFromParent )
         {
            // We can load this guy from the parent so do it now.
            nRC = SqlAutoLoadFromParent( lpView, lpViewOD, lpViewEntity,
                                         lpConnection->lpFirstQualEntity,
                                         lpConnection->pchConnSqlCmd, lpBoundList );
            if ( nRC < 0 )
               goto EndOfFunction;
            else
            {
               nReturnCode = 0;
               goto EndOfFunction;
            }
         }

         lpConnection->hstmt = lpStmtHandle->hstmt;
         lpConnection->pchGlobalTableBuffer = lpStmtHandle->pchOutputBuffer;
         ppchBufferPtr = lpStmtHandle->ppchBufferPtr;

         // Skip the prepare/bind step.
         goto ExecuteCommand;
      }

      // No statement handle so we must create one and prepare the SQL.
#if defined( DB2 )

      rc = SQLAllocStmt( lpConnection->hdbc, &lpStmtHandle->hstmt );
      SQL_RC( "SQLAllocStmt", rc, "Allocate HSTMT", 0, 2 );
      if ( rc != SQL_SUCCESS )
         goto EndOfFunction;

#elif defined( ODBC )

      rc = SQLAllocHandle( SQL_HANDLE_STMT, lpConnection->hdbc,
                           &lpStmtHandle->hstmt );
      SQL_RC( "SQLAllocHandle", rc, "Allocate HSTMT", 0, 2 );
      if ( rc != SQL_SUCCESS )
         goto EndOfFunction;

#endif

      lpConnection->hstmt = lpStmtHandle->hstmt;
   }
   else
      lpConnection->hstmt = lpConnection->hGeneralStmt;

#endif

   // AutoLoad:
   // When the parent has the imbedded keys for the child and the
   // only attributes in the child are those imbedded keys.
   // Autoload is defined (for Phil) from the object for performance reasons.
   if ( lpViewEntity->bAutoLoadFromParent )
   {
      if ( lpConnection->nTraceLevel > 1 )
      {
         TraceLineS( "", "" );
         TraceLineS( "Loading entity from parent using AutoLoadFromParent; ",
                     "SQL might not be needed." );
         TraceLineS( "Entity name = ", lpViewEntity->szName );
      }

      // Return codes from SqlAutoLoadFromParent are:
      //    0 - Nothing done. Perform normal SQL code.
      //    1 - Entity created using info from parent.
      //    2 - A SQL command was created and needs to be executed.  In this
      //        case only the keys need to be loaded for the entity.
      nRC = SqlAutoLoadFromParent( lpView, lpViewOD, lpViewEntity,
                                   lpConnection->lpFirstQualEntity,
                                   lpConnection->pchConnSqlCmd, lpBoundList );
      if ( nRC < 0 )
         goto EndOfFunction;
      else
      if ( nRC == 0 )
      {
         nRC = SqlBuildSelect( lpView, lpViewOD, lpViewEntity,
                               lpConnection->lpFirstQualEntity,
                               lpConnection->pchConnSqlCmd, lpBoundList );
         if ( nRC == zCALL_ERROR )
            goto EndOfFunction;
      }
      else
      if ( nRC == 1 )
      {
         nReturnCode = 0;

#if defined( DB2 ) || defined( ODBC )
         // We have to indicate that this entity is loaded from the parent
         // instead of the database.
         if ( g_bHoldStmtHandles )
         {
            lpStmtHandle->bLoadFromParent = TRUE;
            lpStmtHandle->lpBoundList = lpBoundList;
         }
#endif

         goto EndOfFunction;
      }
      else
      if ( nRC == 2 )
      {
         bKeysOnly = TRUE;
         nRC = 0;
      }
   }
   else
   {
      nRC = SqlBuildSelect( lpView, lpViewOD, lpViewEntity,
                            lpConnection->lpFirstQualEntity,
                            lpConnection->pchConnSqlCmd, lpBoundList );
      if ( nRC == zCALL_ERROR )
         goto EndOfFunction;
   }

   // If the '2' bit is set then multiple tables where joined together.
   nRC &= ~((zSHORT) 0x0002); // turn off the join flag

   // If nRC == 1, then some of the foreign keys are null, which means that
   // there are no children.

#if defined( DB2 ) || defined( ODBC )

   // If we're holding on to stmt handles we will ignore the nRC == 1 return
   // code because we still want to prepare the stmt for later use.
   if ( nRC == 1 && g_bHoldStmtHandles )
      nRC = 0;

#endif

   if ( nRC == 1 )
   {
      if ( lpConnection->nTraceLevel > 1 )
      {
         TraceLineS( "Foreign key is null, so following command was not ",
                     "executed." );
         SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
         TraceLineI( "Number of rows selected = ", (zLONG) 0 );
      }

      nReturnCode = 0;
      goto EndOfFunction;
   }

   // Check to see if the current select was built using OpenSQL.
   if ( lpQualEntity && lpQualEntity->pszOpenSQL )
      bOpenSQL = TRUE;

   // ================================================================
   // Set up incoming buffer area.
   // ================================================================

   // First get the attribute lengths.
   LoopInfo.bOpenSQL          = bOpenSQL;
   LoopInfo.bKeysOnly         = bKeysOnly;
   LoopInfo.bFirstPass        = TRUE;
   LoopInfo.lpQualEntity      = lpQualEntity;
   LoopInfo.lpFirstQualEntity = lpConnection->lpFirstQualEntity;
   LoopInfo.lpViewEntity      = lpViewEntity;
   LoopInfo.lpDataField       = 0;
   LoopInfo.lControl          = Indicators;
   LoopInfo.lpBoundList       = lpBoundList;
   nColumnCnt                 = 0;
   ulTotalLth                 = 0;

   for ( lpDataField = fnGetNextDataField( &LoopInfo );
         lpDataField;
         lpDataField = fnGetNextDataField( &LoopInfo ) )
   {
      lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );
      nColumnCnt++;

      // ================================================================
      // Get column length.
      // ================================================================

#if defined( DB2 ) || defined( ODBC )
      {
      SWORD        fSqlType;
      UDWORD       ulLth;

      // We need space for the incoming length.
      ulTotalLth += sizeof( SQLINTEGER );

      switch ( lpViewAttrib->cType )
      {
         case zTYPE_BLOB:
#if defined( ODBC )
            // We don't want to bind blobs because we are going to use
            // SQLGetData( ) to retrieve the data.
            continue;
#else
            fSqlType = SQL_C_BLOB_LOCATOR;
#endif
            ulLth = sizeof( SQLINTEGER );
            break;

         case zTYPE_DATETIME:
         case zTYPE_TIME:
         case zTYPE_DATE:
            fSqlType = SQL_C_CHAR;
            ulLth = CONVERSION_AREA_LTH; // We'll retrieve the date as a string
                                         // and then convert it.
            break;

         case 'X':
            // TimeStampEx.
            fSqlType = SQL_C_CHAR;
            ulLth = CONVERSION_AREA_LTH;
            break;

         case zTYPE_INTEGER:
            fSqlType = SQL_C_SLONG;
            ulLth = sizeof( zLONG );
            break;

         case zTYPE_DECIMAL:
            fSqlType = SQL_C_CHAR;
            ulLth = CONVERSION_AREA_LTH; // We'll retrieve the date as a string
                                         // and then convert it.
            break;

         case zTYPE_STRING:
            switch ( lpDataField->cFldType )
            {
               case 'V':
#if defined( DB2 )
                  fSqlType = SQL_C_CLOB_LOCATOR;
                  ulLth = zsizeof( SQLINTEGER );
#else
                  // We don't want to bind varchar because we are going to use
                  // SQLGetData( ) to retrieve the data.
                  continue;
#endif
                  break;

               default:
                  fSqlType = SQL_C_CHAR;
                  ulLth = lpDataField->uFldLth + 1;
                  break;
            }

            break;

         default:
            DBH_Error(lpView, "Unknown Data Type", 0, 0 );
            nRC = zCALL_ERROR;
            break;
      }

      ulTotalLth += ulLth;

      }

#endif

   } // for ( lpDataField )...

   // Allocate the buffer.
#if defined( DB2 ) || defined( ODBC )

   if ( g_bHoldStmtHandles )
   {
      // We need to add one more to column count to account for the difference
      // between the count and offsets.
      nColumnCnt++;

      lpStmtHandle->pchOutputBuffer = malloc( ulTotalLth + 1 );
      lpConnection->pchGlobalTableBuffer = lpStmtHandle->pchOutputBuffer;
      lpStmtHandle->ppchBufferPtr = malloc( sizeof( zPCHAR ) * nColumnCnt );
      ppchBufferPtr = lpStmtHandle->ppchBufferPtr;
      zmemset( ppchBufferPtr, 0, sizeof( zPCHAR ) * nColumnCnt );
      lpStmtHandle->lpBoundList = lpBoundList;
   }
#endif

   // ================================================================
   // Compile/prepare SQL.
   // ================================================================

#if defined( DB2 ) || defined( ODBC )

   nRC = SQLPrepare( lpConnection->hstmt, lpConnection->pchConnSqlCmd, SQL_NTS );
   DisplayCommand( "SQLPrepare", nRC, lpConnection );
   if ( nRC != SQL_SUCCESS )
      goto EndOfFunction;

#elif defined( DUMMY )

   DisplayCommand( "Compile SQL", nRC, lpConnection );
   if ( nRC )
      goto EndOfFunction;

#endif

   // Set the select buffer for each data field.
   LoopInfo.bOpenSQL          = bOpenSQL;
   LoopInfo.bKeysOnly         = bKeysOnly;
   LoopInfo.bFirstPass        = TRUE;
   LoopInfo.lpQualEntity      = lpQualEntity;
   LoopInfo.lpFirstQualEntity = lpConnection->lpFirstQualEntity;
   LoopInfo.lpViewEntity      = lpViewEntity;
   LoopInfo.lpDataField       = 0;
   LoopInfo.lControl          = Indicators;
   LoopInfo.lpBoundList       = lpBoundList;
   nColumnCnt = 0;
   lpPtr = lpConnection->pchGlobalTableBuffer;

   for ( lpDataField = fnGetNextDataField( &LoopInfo );
         lpDataField;
         lpDataField = fnGetNextDataField( &LoopInfo ) )
   {
      lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );
      nColumnCnt++;

      // ================================================================
      // Bind columns.
      // ================================================================

#if defined( DB2 ) || defined( ODBC )
      {
      SWORD        fSqlType;
      UDWORD       ulLth;
      zPCHAR       lpDataPtr;

      ppchBufferPtr[ nColumnCnt ] = lpPtr;

      // lpDataPtr points to the area that is to hold the data returned from the database.
      lpDataPtr = lpPtr + sizeof( SQLINTEGER );
      *(SQLINTEGER *) lpPtr = 0;

      switch ( lpViewAttrib->cType )
      {
         case zTYPE_BLOB:
#if defined( ODBC )
            // We don't want to bind blobs because we are going to use SQLGetData( ) to retrieve the data.
            continue;
#else
            fSqlType = SQL_C_BLOB_LOCATOR;
#endif
            ulLth = sizeof( SQLINTEGER );
            break;

         case zTYPE_DATETIME:
         case zTYPE_TIME:
         case zTYPE_DATE:
            fSqlType = SQL_C_CHAR;
            ulLth = CONVERSION_AREA_LTH; // We'll store the date as a string and then convert it.
            break;

         case 'X':
            // TimeStampEx.
            fSqlType = SQL_C_CHAR;
            ulLth = CONVERSION_AREA_LTH;
            break;

         case zTYPE_INTEGER:
            fSqlType = SQL_C_SLONG;
            ulLth = sizeof( zLONG );
            break;

         case zTYPE_DECIMAL:
            fSqlType = SQL_C_CHAR;
            ulLth = CONVERSION_AREA_LTH; // We'll retrieve the decimal as a string and then convert it.
            break;

         case zTYPE_STRING:
            switch ( lpDataField->cFldType )
            {
               case 'V':
#if defined( DB2 )
                  fSqlType = SQL_C_CLOB_LOCATOR;
                  ulLth = zsizeof( SQLINTEGER );
#else
                  // We don't want to bind varchar because we are going to use SQLGetData( ) to retrieve the data.
                  continue;
#endif
                  break;

               default:
                  fSqlType = SQL_C_CHAR;
                  ulLth = lpDataField->uFldLth + 1;
                  break;
            }

            break;

         default:
            DBH_Error(lpView, "Unknown Data Type", 0, 0 );
            nRC = zCALL_ERROR;
            break;
      }


      nRC = SQLBindCol( lpConnection->hstmt, nColumnCnt, fSqlType,
                        (SQLPOINTER) lpDataPtr, ulLth, (SQLINTEGER *) lpPtr );
      SQL_RC( "SQLBindCol", nRC, "Attr = ", lpViewAttrib->szName, 2 );

      if ( lpConnection->nTraceLevel >= 2 )
      {
         zCHAR sz[ 2 ] = " ";

         TraceLineI( "Column Count         = ", nColumnCnt );
         TraceLineS( "Column Name          = ", lpDataField->szFldName );
         sz[ 0 ] = lpViewAttrib->cType;
         TraceLineS( "ViewAttrib data type = ", sz );
         sz[ 0 ] = lpDataField->cFldType;
         TraceLineS( "DataField data type  = ", sz );
      }

      if ( !RC_SUCCESSFUL( nRC ) )
         goto EndOfFunction;

      lpPtr += ulLth + sizeof( SQLINTEGER );

      }

#endif

   } // for ( lpDataField )...

#if defined( DB2 ) || defined( ODBC )

   // Save the SQL command and statement handle.
   if ( g_bHoldStmtHandles )
   {
      zLONG lLth = zstrlen( lpConnection->pchConnSqlCmd );

      lpStmtHandle->pchSqlCmd = malloc( lLth + 1 );
      strcpy_s( lpStmtHandle->pchSqlCmd, lLth + 1, lpConnection->pchConnSqlCmd );

      lpStmtHandle->hstmt = lpConnection->hstmt;

      // Check to make sure that there is a buffer to hold the input variables.
      if ( lpBoundList->lpFirstBoundAttr )
      {
         LPBOUNDATTR  lpBoundAttr;
         zPCHAR       pchBufferPos;
         SQLUSMALLINT nParmCount;

         // Go through the bind variable list and determine how big the buffer
         // needs to be.
         lpStmtHandle->ulInputLth = 0;
         for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
               lpBoundAttr;
               lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
         {
            // We need to keep an area to specify the attribute length.
            lpStmtHandle->ulInputLth += sizeof( SQLINTEGER );

            // Now set aside the buffer area.
            lpViewAttrib = zGETPTR( lpBoundAttr->lpDataField->hViewAttrib );
            lpStmtHandle->ulInputLth += lpViewAttrib->ulLth;
         }

         lpStmtHandle->pchInputBuffer = malloc( lpStmtHandle->ulInputLth + 1 );

         // Now call BindParamter to set up the input buffer.
         nParmCount   = 0;
         pchBufferPos = lpStmtHandle->pchInputBuffer;
         for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
               lpBoundAttr;
               lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
         {
            LPDATAFIELD    lpDataField  = lpBoundAttr->lpDataField;
            SQLSMALLINT    nC_DataType;
            SQLSMALLINT    nSQL_Type;
            SQLSMALLINT    nDecDigits;
            SQLUINTEGER    nColumnSize;
            SQLINTEGER *   lpnParmLth;
            SQLINTEGER     iBufferLth;

            lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );

            nParmCount++;

            if ( lpConnection->nTraceLevel > 1 )
            {
               TraceLineS( "(KZHSQLBA) Binding attributename = ",
                           lpViewAttrib->szName );
               TraceLineI( "nParmCount = ", nParmCount );
            }

            lpnParmLth = (SQLINTEGER *) pchBufferPos;
            pchBufferPos += sizeof( SQLINTEGER );

            switch ( lpViewAttrib->cType )
            {
               case zTYPE_STRING:
                  nC_DataType = SQL_C_CHAR;
                  nSQL_Type   = SQL_VARCHAR;
                  iBufferLth  = lpViewAttrib->ulLth;
                  nColumnSize = lpViewAttrib->ulLth;
                  *lpnParmLth = SQL_NTS;
                  nDecDigits = 0;
                  break;

               case zTYPE_INTEGER:
                  nC_DataType = SQL_C_SLONG;
                  nSQL_Type   = SQL_INTEGER;
                  iBufferLth  = sizeof( zLONG );
                  nColumnSize = sizeof( zLONG );
                  *lpnParmLth = sizeof( zLONG );
                  nDecDigits = 0;
                  break;
            }

            nRC = SQLBindParameter( lpConnection->hstmt, nParmCount, SQL_PARAM_INPUT,
                                    nC_DataType, nSQL_Type, nColumnSize, nDecDigits,
                                    (SQLPOINTER) pchBufferPos, iBufferLth,
                                    lpnParmLth );
            SQL_RC( "SQLBindParameter", nRC, "Column = ", lpDataField->szFldName, 3 );

            if ( lpConnection->nTraceLevel > 2 )
            {
               TraceLineI( "nC_DataType = ", nC_DataType );
               TraceLineI( "nSQL_Type   = ", nSQL_Type );
               TraceLineI( "nColumnSize = ", nColumnSize );
               TraceLineI( "nDecDigits  = ", nDecDigits );
            }

            if ( !RC_SUCCESSFUL( nRC ) )
               goto EndOfFunction;

            pchBufferPos += iBufferLth;

         } // for...

      } // if ( lpStmtHandle->pchInputBuffer == 0 )...

   } // if ( g_bHoldStmtHandles )...

#endif

   // ================================================================
   // Execute generated SQL
   // ================================================================

   // Following is kind of a hack to keep from getting warning messages that
   // the label ExecuteCommand is unused.
   goto ExecuteCommand;

// I know goto statements are lousy but it is much easier to code when
// dealing with all the conditional compiling.
ExecuteCommand:

   // If the qualification uses a key list then we need to add the keys to
   // the key list table.
   if ( lpQualEntity && lpQualEntity->bContainsKeyList )
   {
      zLONG hTask = SysGetTaskFromView( lpView );
      if ( fnCreateKeyList( hTask, lpConnection, lpBoundList, lpQualEntity ) < 0 )
         goto EndOfFunction;

      bKeyListCreated = TRUE;
   }

#if defined( DB2 ) || defined( ODBC )

   // OK, if there are any bound attributes we need to copy the attribute
   // values into the input buffer.
   if ( lpBoundList && lpBoundList->lpFirstBoundAttr )
   {
      LPBOUNDATTR  lpBoundAttr;
      zPCHAR       pchBufferPos;

      // Go through the bind variable list and determine how big the buffer needs to be.
      pchBufferPos = lpStmtHandle->pchInputBuffer;
      for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
            lpBoundAttr;
            lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
      {
         LPDATAFIELD    lpDataField  = lpBoundAttr->lpDataField;
         LPVIEWENTITY   lpBoundEntity;
         SQLINTEGER     *lpnLth;
         zPCHAR         lpValue;
         zCHAR          chType;
         zULONG         ulLth;

         lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );
         lpBoundEntity = zGETPTR( lpViewAttrib->hViewEntity );

         lpnLth = (SQLINTEGER *) pchBufferPos;
         pchBufferPos += sizeof( SQLINTEGER );

         if ( GetValueFromRecord( lpBoundAttr->lpView,
                                  lpBoundEntity, lpViewAttrib, (zPVOID) &lpValue,
                                  &chType, &ulLth ) == zCALL_ERROR )
         {
            // Oops, error.  Get out of function.
            goto EndOfFunction;
         }

         switch ( lpViewAttrib->cType )
         {
            case zTYPE_STRING:
            // Length is always SQL_NTS.
               //*lpnLth = (SQLINTEGER) ulLth;
               strcpy_s( pchBufferPos, lpStmtHandle->ulInputLth + 1 - (pchBufferPos - lpStmtHandle->pchInputBuffer), lpValue );
               pchBufferPos += lpViewAttrib->ulLth;
               break;

            case zTYPE_INTEGER:
               *((zPLONG) pchBufferPos) = *((zPLONG) lpValue);
               pchBufferPos += sizeof( zLONG );
               break;
         }
      }
   }

   // Execute the sql command.
   nRC = SQLExecute( lpConnection->hstmt );
   SQL_RC( "SQLExecute", nRC, 0, 0, 2 );
   if ( nRC != SQL_SUCCESS && nRC != SQL_SUCCESS_WITH_INFO )
   {
      // If the trace level is 0 then let's trace the SQL to help debugging.
      if ( lpConnection->nTraceLevel == 0 )
         SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );

      goto EndOfFunction;
   }

#endif

   // Following is kind of a hack to keep from getting warning messages that
   // the label StartOfFetches is unused.
   goto StartOfFetches;

StartOfFetches:

#ifdef DELETEHACK
   // If OpenSQL has been specified but there are no data fields then we'll
   // assume that OpenSQL has been used for DELETE processing.  For delete
   // processing we obviously don't need to do a fetch so return now.
   if ( bOpenSQL && lpQualEntity->lpDataField[ 0 ] == 0 )
   {
      nReturnCode = -1;  // Indicates nothing was loaded.
      goto EndOfFunction;
   }
#endif

   // ================================================================
   // Fetch first row from the table.
   // ================================================================

   lRowCount  = 0;
   lRootCnt = 0;

   if ( bCreateMultipleRoots == FALSE && lpViewEntity->hParent == 0 )
      lRootLimit = 1;
   else
   {
      lRootLimit = lpViewEntity->lActivateLimit;
      if ( lRootLimit == 0 )
         lRootLimit = 0x7FFFFFFF;
   }

#if defined( DB2 ) || defined( ODBC )

   bCursorOpened = TRUE;

   nRC = SQLFetch( lpConnection->hstmt );
   SQL_RC( "SQLFetch", nRC, 0, 0, 2 );
   switch ( nRC )
   {
      case SQL_SUCCESS:
      case SQL_SUCCESS_WITH_INFO:
         nRC = zFETCH_OK;
         break;

      case SQL_NO_DATA:
         nRC = zFETCH_NO_DATA;
         break;

      default:
         // Oops, error.
         goto EndOfFunction;
   }

#elif defined( DUMMY )

   // If the entity supports hanging keys then let's pretend we didn't find
   // any.
   if ( lpViewEntity->bHangingFKey )
      nRC = zFETCH_NO_DATA;
   else
      nRC = zFETCH_OK;

#endif

   hMem    = 0;
   lMemLth = 0;
   lpMem   = 0;

   // If a row was fetched, copy the table data into a newly created entity.
   if ( nRC == zFETCH_OK )
   {
      // The following is a list of booleans, one for each entity in the
      // lpViewOD.  It keeps track of whether the entity was created
      // (added to the OI) since the last fetch.
      zBOOL bEntityCreatedList[ 500 ];

      // Reset all the flags to not-created.
      zmemset( bEntityCreatedList, 0, zsizeof( bEntityCreatedList ) );

      nReturnCode = 0;

      // For each row, create an entity instance and copy the attribute
      // values from the table to the entity.
      do
      {
         LPVIEWENTITY lpLastCreatedEntity;
         zBOOL        bNewEntity;
#if defined( DUMMY )

         LPVIEWENTITY lpCreatedEntity = 0;

         // Dummy DBH doesn't load children via a join.
         lRootCnt++;

#endif
         lRowCount++;

         if ( lpConnection->nTraceLevel >= 1 && (lRowCount % 1000) == 0 )
            TraceLineI( "(xa) Number of rows currently read = ", lRowCount );

         // Loop through each of the attributes and get the column values
         // from the currently fetched row.

         LoopInfo.bOpenSQL          = bOpenSQL;
         LoopInfo.bKeysOnly         = bKeysOnly;
         LoopInfo.bFirstPass        = TRUE;
         LoopInfo.lpQualEntity      = lpQualEntity;
         LoopInfo.lpFirstQualEntity = lpConnection->lpFirstQualEntity;
         LoopInfo.lpViewEntity      = lpViewEntity;
         LoopInfo.lpDataField       = 0;
         LoopInfo.lControl          = Indicators;
         LoopInfo.lpBoundList       = lpBoundList;
         lpLastCreatedEntity        = 0;
         bNewEntity                 = FALSE;
         nColumnCnt = 0;
         for ( lpDataField = fnGetNextDataField( &LoopInfo );
               lpDataField;
               lpDataField = fnGetNextDataField( &LoopInfo ) )
         {
            LPVIEWENTITY lpLoadEntity;

#if defined( DB2 )

            zPCHAR       lpPtr;
            SQLINTEGER   nLth;
            SQLINTEGER   nInd;

#elif defined( ODBC )

            zCHAR        sz[ 50 ];
            zPCHAR       lpPtr;
            SQLINTEGER   nLth;

#endif

            lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );
            lpLoadEntity = zGETPTR( lpViewAttrib->hViewEntity );

            if ( lpLoadEntity != lpLastCreatedEntity )
               bNewEntity = TRUE;
            else
               bNewEntity = FALSE;

            nColumnCnt++;

            // When dealing with joins, we need to make sure we don't create
            // duplicate entities.  The only way to do this is to compare the
            // key for the current row and see if it already exists in the
            // entity list.  So first we need to store the keys for the current
            // row.  If we find an attribute that is NOT a key, then we've
            // retrieved and stored the keys for the current entity in the
            // current row.  Call fnSetEntityByKeys to see if the entity
            // already exists.
            // The second part of the 'if' is to handle the situation where
            // an entity has only keys.  If nEntityKeyCnt is > 0, then we
            // know we've stored some key values.  If the 'lpLoadEntity' for
            // the key is different from the current lpLoadEntity, then we're
            // onto a new entity and we must create the previous entity.
            if ( lpViewAttrib->bKey == FALSE ||
                 (nEntityKeyCnt > 0 &&
                  lpKeyData[ 0 ].lpLoadEntity != lpLoadEntity) )
            {
               // If nEntityKeyCnt is > 0, then the current lpDataField is
               // not a key and the previous lpDataField was a key.  Use the
               // keys stored in lpKeyData to see if we need to create an
               // entity.
               if ( nEntityKeyCnt > 0 )
               {
                  nRC = fnSetEntityByKeys( lpView, lpKeyData, nEntityKeyCnt,
                                           bEntityCreatedList, lRootLimit,
                                           lRootCnt, lpBoundList );
                  if ( nRC == -1 )
                  {
                     // We found a new root entity but we have reached our
                     // root limit.  Set flag and break to fetch the next row.
                     nEntityKeyCnt = 0;
                     bRootLimitReached = TRUE;
                     break;
                  }
                  else
                  if ( nRC == 1 )
                  {
                     // Keep track of the number of root entities created.
                     if ( lpLoadEntity == lpViewEntity )
                        lRootCnt++;
                  }
                  else
                  {
                     if ( lpConnection->nTraceLevel > 1 )
                     {
                        TraceLineS( "Duplicate row found, entity = ",
                                    lpLoadEntity->szName );
                     }
                  }

                  // We just created an entity (or at least positioned on the
                  // right one) so set lpLastCreatedEntity.
                  lpLastCreatedEntity = lpLoadEntity;

                  // Reset nEntityKeyCnt so we don't try this on the following
                  // non-key attributes.
                  nEntityKeyCnt = 0;

               } // if ( nEntityKeyCnt > 0 )...
               else
               if ( lpLoadEntity->bHasDB_Oper )
               {
                  if ( bNewEntity )
                  {
                     LoadEntity( lpView, lpLoadEntity->szName, zPOS_LAST, 0 );
                     lpLastCreatedEntity = lpLoadEntity;
                     bEntityCreatedList[ lpLoadEntity->nHierNbr ] = TRUE;
                  }
               }

               // If the DataField is not a key and the entity was not created
               // during the current FETCH, it was loaded on a previous fetch
               // and we don't need to copy the attributes.
               if ( lpViewAttrib->bKey == FALSE &&
                    bEntityCreatedList[ lpLoadEntity->nHierNbr ] == FALSE )
               {
                  continue; // Continue on with the next lpDataField.
               }

            } // if ( !lpViewAttrib->bKey || ...

            // ================================================================
            // Retrieve column value and store it as an attribute in the entity.
            // ================================================================

#if defined( DB2 ) || defined( ODBC )

            lpPtr = ppchBufferPtr[ nColumnCnt ];
            nLth = *((SQLINTEGER *) lpPtr);
            lpPtr += sizeof( SQLINTEGER );

            // If attribute is a blob or long string, then the value must be
            // retrieved from a long varchar.
            if ( lpDataField->cFldType == zTYPE_BLOB ||
                 lpDataField->cFldType == 'V' )
            {
#ifdef DB2
               SQLINTEGER  cLocator = *((SQLINTEGER *) lpPtr);
               SQLSMALLINT iSqlType;
               SQLSMALLINT iCType;

               if ( lpDataField->cFldType == zTYPE_BLOB )
               {
                  iSqlType = SQL_C_BLOB_LOCATOR;
                  iCType   = SQL_C_BINARY;
               }
               else
               {
                  iSqlType = SQL_C_CLOB_LOCATOR;
                  iCType   = SQL_C_CHAR;
               }

               if ( hBlobStmt == 0 )
               {
                  nRC = SQLAllocStmt( lpConnection->hdbc, &hBlobStmt );
                  SQL_RC( "SQLAllocStmt", nRC, "Allocate Temp HSTMT", 0, 2 );
                  if ( nRC != SQL_SUCCESS )
                     goto EndOfFunction;

                  nRC = SQLAllocStmt( lpConnection->hdbc, &hLocatorStmt );
                  SQL_RC( "SQLAllocStmt", nRC, "Allocate Temp HSTMT", 0, 2 );
                  if ( nRC != SQL_SUCCESS )
                     goto EndOfFunction;
               }

               // NOTE: There doesn't seem to be a way to find out if the
               // BLOB/CLOB is null (checking for SQL_NULL doesn't work)
               // so SQLGetLength( ) will return an error if the attribute
               // is null.
               nRC = SQLGetLength( hBlobStmt, iSqlType, cLocator, &nLth, &nInd );
               SQL_RC( "SQLGetLength", nRC, "Getting length of column ",
                       lpDataField->szFldName, 2 );

               // If the length is 0, then there is nothing to be read.
               if ( nLth > 0 )
               {
                  // If memory needs to be allocated, then allocate it.
                  if ( hMem == 0 || lMemLth <= nLth )
                  {
                     if ( hMem != 0 )
                        SysFreeMemory( hMem );

                     // Make sure that the length of the buffer is a least
                     // 1000 and always at least 1 greater then the length of
                     // the column value.
                     lMemLth = ( nLth < 1000 ) ? 1001 : nLth + 1;
                     hMem = SysAllocMemory( (zPVOID) &lpMem, lMemLth, 0,
                                            zCOREMEM_ALLOC, 0 );
                     if ( lpMem == 0 )
                        goto EndOfFunction;
                  }

                  nRC = SQLGetSubString( hBlobStmt, iSqlType, cLocator, 1, nLth,
                                         iCType, (SQLPOINTER) lpMem,
                                         lMemLth,  &nInd, &nInd );
                  SQL_RC( "SQLGetSubString", nRC, 0, 0, 3 );
                  if ( nRC != SQL_SUCCESS )
                     goto EndOfFunction;

                  StoreValueInRecord( lpView, lpLoadEntity, lpViewAttrib,
                                      lpMem, (zULONG) nLth );

                  // Now set the attribute flags.
                  GetAttributeFlags( &lpAttribFlags, lpView,
                                     lpLoadEntity, lpViewAttrib );
                  lpAttribFlags->u.bFlags.bActivated = TRUE;
                  lpAttribFlags->u.bFlags.bUpdated  = FALSE;

                  nRC = SQLFreeStmt( hBlobStmt, SQL_CLOSE );
                  SQL_RC( "SQLFreeStmt", nRC, "Freeing temp handle?", 0, 3 );


                  nRC = SQLSetParam( hLocatorStmt, 1, SQL_C_CLOB_LOCATOR,
                                     SQL_CLOB_LOCATOR, 0, 0, &cLocator, 0 );
                  SQL_RC( "SQLSetParam", nRC, "About to free locator.", 0, 3 );

                  nRC = SQLExecDirect( hLocatorStmt, "FREE LOCATOR ?", SQL_NTS );
                  SQL_RC( "SQLExecDirect", nRC, "Freeing locator.", 0, 3 );

               } // if ( nLth > 0 )...
               else
                  nRC = 0;

#else   // i.e. #ifdef ODBC

               // Get the length of the column.
               nRC = SQLGetData( lpConnection->hstmt, nColumnCnt,
                                 SQL_C_DEFAULT, (SQLPOINTER) sz, 0, &nLth );
               SQL_RC( "SQLGetData", nRC, "Getting length for ",
                       lpDataField->szFldName, 2 );

               if ( lpConnection->nTraceLevel >= 2 )
               {
                  TraceLineI( "Column number = ", nColumnCnt );
                  TraceLineI( "Returned lth for column = ", nLth );
               }

               if ( !RC_SUCCESSFUL( nRC ) )
                  goto EndOfFunction;

               if ( nLth > 0 )
               {
                  // If memory needs to be allocated, then allocate it.
                  if ( hMem == 0 || lMemLth <= nLth )
                  {
                     if ( hMem != 0 )
                        SysFreeMemory( hMem );

                     // Make sure that the length of the buffer is a least
                     // 1000 and always at least 1 greater then the length of
                     // the column value.
                     lMemLth = ( nLth < 1000 ) ? 1001 : nLth + 1;
                     hMem = SysAllocMemory( (zPVOID) &lpMem, lMemLth, 0,
                                            zCOREMEM_ALLOC, 0 );
                     if ( lpMem == 0 )
                        goto EndOfFunction;
                  }

                  // Now retrieve the data.
                  nRC = SQLGetData( lpConnection->hstmt, nColumnCnt,
                                    SQL_C_DEFAULT, (SQLPOINTER) lpMem,
                                    lMemLth, &nLth );
                  SQL_RC( "SQLGetData", nRC, "Getting data ", 0, 2 );

                  if ( lpConnection->nTraceLevel >= 2 )
                     TraceLineI( "Returned lth for column = ", nLth );

                  if ( !RC_SUCCESSFUL( nRC ) )
                     goto EndOfFunction;

                  StoreValueInRecord( lpView, lpLoadEntity, lpViewAttrib,
                                      lpMem, (zULONG) nLth );

                  // Now set the attribute flags.
                  GetAttributeFlags( &lpAttribFlags, lpView,
                                     lpLoadEntity, lpViewAttrib );
                  lpAttribFlags->u.bFlags.bActivated = TRUE;
                  lpAttribFlags->u.bFlags.bUpdated  = FALSE;
               }
#endif

            } // if ( lpDataField->cFldType == zTYPE_BLOB || ... )...
            else
            {
               zCHAR szDateTime[ 100 ];

               // Check to see if the column is null.  If it is skip it.
               if ( nLth == SQL_NULL_DATA )
               {
                  // Check to see if this attribute is a DB_Oper.  If it is,
                  // then the table must not exist because the oper would have
                  // a value.  If this is the first attribute we have found for
                  // this entity, we must drop the just-created entity.
                  if ( lpViewAttrib->cDB_Oper != 0 && bNewEntity )
                     DropEntity( lpView, lpLoadEntity->szName, zREPOS_LAST );

                  continue;
               }

               // If the attribute is a DateTime field, then the string must be
               // "unformatted".
               if ( lpDataField->cFldType == zTYPE_DATETIME ||
                    lpDataField->cFldType == zTYPE_DATE     ||
                    lpDataField->cFldType == zTYPE_TIME )
               {
                  szDateTime[ 0 ] = 0;
#ifdef DB2
                  if ( lpDataField->cFldType == zTYPE_TIME )
                     // lpPtr points to "HH:MM:SS".  Prefix dummy date.
                     strcpy_s( szDateTime, zsizeof( szDateTime ), "1900-01-01 " );
#endif

                  strcat_s( szDateTime, zsizeof( szDateTime), lpPtr );

#ifdef DB2
                  if ( lpDataField->cFldType == zTYPE_DATE )
                     // lpPtr points to "YYYY-MM-DD".  Postfix dummy time
                     strcat_s( szDateTime, zsizeof( szDateTime ), " 00:00:00" );
#endif

                  // Convert datetime to YYYYMMDDHHmmSS.
                  if ( UfEditFormatDateTime( szDateTime, zsizeof( szDateTime ), "YYYY-MM-DD HH:MI:SS" ) == 0 )
                     ; // Do nothing...szDateTime converted OK.
                  else
                  if ( UfEditFormatDateTime( szDateTime, zsizeof( szDateTime ), "M/D/YYYY H:MI:SS AM" ) == 0 )
                     ; // Do nothing...szDateTime converted OK.

                  // For date and time formats we need to change unused part to 0's.
                  switch ( lpDataField->cFldType )
                  {
                     case zTYPE_DATE:
                        strcpy_s( szDateTime + 8, zsizeof( szDateTime ) - 8, "000000000" );
                        break;

                     case zTYPE_TIME:
                        zmemcpy( szDateTime, "19000101", 8 );
                        break;
                  }

                  // Copy szDateTime back into the buffer.
                  strcpy_s( lpPtr, zsizeof( szDateTime ), szDateTime ); // this should always be safe even though we don't know the size of lpPtr at this point
               }
#ifdef DB2
               else
               if ( lpDataField->cFldType == zTYPE_DECIMAL )
               {
                  if ( g_ucDB2_Comma == 2)
                  {
                     /* If the Database uses decimal comma instead of point ..., but the functions
                      * in decari use only '.', therefore we have to change the ',' into '.'
                      */
                     zPCHAR pch = strchr( lpPtr, ',') ;

                     if ( pch )
                        *pch = '.';
                  }
               }
#endif

               if ( lpViewAttrib->bKey )
               {
                  // Store the key value for now.  When we reach the end of the keys we will use them to
                  // determine if the entity has been created yet.
                  lpKeyData[ nEntityKeyCnt ].lpDataField  = lpDataField;
                  lpKeyData[ nEntityKeyCnt ].lpPtr        = lpPtr;
                  lpKeyData[ nEntityKeyCnt ].lpViewAttrib = lpViewAttrib;
                  lpKeyData[ nEntityKeyCnt ].lpLoadEntity = lpLoadEntity;
                  nEntityKeyCnt++;

                  // Try next lpDataField.
                  continue;

               } // if ( lpViewAttrib->bKey )...

               // At this point lpPtr points to the datbase value. Copy the value into the attribute.
               switch ( lpDataField->cFldType )
               {
                  case zTYPE_DATETIME:
                  case zTYPE_DATE:
                  case zTYPE_TIME:
                     StoreStringInRecord( lpView, lpLoadEntity, lpViewAttrib, lpPtr );
                     break;

                  case zTYPE_DECIMAL:
                     StoreStringInRecord( lpView, lpLoadEntity, lpViewAttrib, lpPtr );

                     // Retrieve decimal value and copy it back into the attribute.
                     // This will cause the Format routines to be called so that
                     // the decimal gets rounded/truncated correctly.
                     // Use szDateTime as a dummy buffer.
                     GetStringFromRecord( lpView, lpLoadEntity, lpViewAttrib, szDateTime, zsizeof( szDateTime ) );
                     StoreStringInRecord( lpView, lpLoadEntity, lpViewAttrib, szDateTime );
                     break;

                  default:
                     // Note that length is only used for blob attributes, so we
                     // will always pass 0.
                     StoreValueInRecord( lpView, lpLoadEntity, lpViewAttrib,
                                         lpPtr, 0 );
                     break;
               }

               // Now set the attribute flags.
               GetAttributeFlags( &lpAttribFlags, lpView, lpLoadEntity, lpViewAttrib );
               lpAttribFlags->u.bFlags.bActivated = TRUE;
               lpAttribFlags->u.bFlags.bUpdated  = FALSE;

            } // if ( lpDataField->cFldType == zTYPE_BLOB || ... )...else...

#elif defined( DUMMY )

#ifdef USE_JOINS
            // Check to see if the entity corresponding to the lpDataField
            // is the same as the entity we are activating.  If it is NOT, then
            // we must be loading attributes from a child entity that has
            // been selected as part of a join.  This happens for children
            // that have a x-to-1 relationship.  In any case, we need to
            // create a new entity.
            if ( lpCreatedEntity ==  0  ||
                 (lpLoadEntity != lpCreatedEntity &&
                  lpLoadEntity->nHierNbr > lpCreatedEntity->nHierNbr) )
            {
               LoadEntity( lpView, lpLoadEntity->szName, zPOS_AFTER, 0 );
               lpCreatedEntity = lpLoadEntity;
            }
#endif

            // We'll just create dummy values.
            switch ( lpViewAttrib->cType )
            {
               case zTYPE_INTEGER:
               {
                  zLONG lTemp = lpConnection->lIntegerCount++;

                  StoreValueInRecord( lpView, lpLoadEntity, lpViewAttrib, &lTemp, 0 );
                  break;
               }

               case zTYPE_STRING:
               {
                  zCHAR szTemp[ 30 ];

                  sprintf_s( szTemp, zsizeof( szTemp ), "TempString%ld", lpConnection->lStringCount++ );
                  StoreValueInRecord( lpView, lpLoadEntity, lpViewAttrib, (zPVOID) szTemp, 0 );
                  break;
               }

               case zTYPE_DECIMAL:
               {
                  zDECIMAL dTemp;

                  SysConvertDoubleToDecimal( (double) (lpConnection->lDecimalCount++ * 1.1), &dTemp );
                  StoreValueInRecord( lpView, lpLoadEntity, lpViewAttrib, (zPVOID) &dTemp, 0 );
                  break;
               }

               case zTYPE_DATETIME:
               {
                  zCHAR szDateTime[ 20 ];

                  SysGetDateTime( szDateTime, zsizeof( szDateTime ) );
                  StoreStringInRecord( lpView, lpLoadEntity, lpViewAttrib, szDateTime );
                  break;
               }

               // Now set the attribute flags.
               GetAttributeFlags( &lpAttribFlags, lpView, lpLoadEntity, lpViewAttrib );
               lpAttribFlags->u.bFlags.bActivated = TRUE;
               lpAttribFlags->u.bFlags.bUpdated  = FALSE;
            }
#endif

         } // for ( lpDataField... )

         // ================================================================
         // Fetch the next row.
         // ================================================================

         // Since we're about to fetch a new row, reset all the flags to
         // not-created.
         zmemset( bEntityCreatedList, 0, zsizeof( bEntityCreatedList ) );

#if defined( DB2 ) || defined( ODBC )

         // We're about to fetch a new row, but we need to check if all the
         // entities were created from the previous fetch.  If nEntityKeyCnt
         // is not 0, then the last entity that is part of the fetch is made
         // up of only keys.  It may need to be created.
         if ( nEntityKeyCnt > 0 )
         {
            fnSetEntityByKeys( lpView, lpKeyData, nEntityKeyCnt, 0,
                               lRootLimit, lRootCnt, lpBoundList );
            nEntityKeyCnt = 0;
         }

         nRC = SQLFetch( lpConnection->hstmt );
         SQL_RC( "SQLFetch", nRC, 0, 0, 2 );
         switch ( nRC )
         {
            case SQL_SUCCESS:
            case SQL_SUCCESS_WITH_INFO:
               nRC = zFETCH_OK;
               break;

            case SQL_NO_DATA:
               nRC = zFETCH_NO_DATA;
               break;

            default:
               // Oops, error.
               nReturnCode = zCALL_ERROR;
               goto EndOfFunction;
         }

#elif defined( DUMMY )

         // If CardMax of the entity is 1 then we'll pretend we didn't find any more entities.
         if ( lpViewEntity->uCardMax == 1 )
            nRC = zFETCH_NO_DATA;
         else
         if ( lRootCnt == 2 )
            nRC = zFETCH_NO_DATA;
         else
            nRC = zFETCH_OK;

#endif
         // If we didn't fetch a row this time and if we only fetched 1 row then set the return
         // code to 0 and break loop.
         if ( nRC == zFETCH_NO_DATA && lRootCnt == 1 )
         {
            nReturnCode = 0;
            break;
         }

      } while ( nRC == zFETCH_OK );

   } // if ( nRC == zFETCH_OK )...
   else
      nReturnCode = -1;   // Indicate that no rows were fetched.

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineI( "Number of roots retrieved = ", lRootCnt );
      TraceLineI( "Number of rows  retrieved = ", lRowCount );
   }

   if ( nReturnCode == 0 && bRootLimitReached )
   {
      if ( lRootLimit > 1 )
         nReturnCode = 2; // We must have reached the activate limit.
      else
         nReturnCode = 1; // Set RC to indicate we only got one root but that more than one was found.
   }

EndOfFunction:

#if defined( DB2 )
   if ( hBlobStmt )
   {
      // Free statements needed to load BLOB columns.
      nRC = SQLFreeStmt( hBlobStmt, SQL_DROP );
      SQL_RC( "SQLFreeStmt", nRC, "Freeing BLOB hstmt", 0, 2 );

      nRC = SQLFreeStmt( hLocatorStmt, SQL_DROP );
      SQL_RC( "SQLFreeStmt", nRC, "Freeing locator hstmt2", 0, 2 );
   }

   nRC = SQLFreeStmt(lpConnection->hstmt, SQL_UNBIND);
   SQL_RC( "SQLFreeStmt", nRC, "Unbinding stmt handle", 0, 2 );

   nRC = SQLFreeStmt(lpConnection->hstmt, SQL_RESET_PARAMS);
   SQL_RC( "SQLFreeStmt", nRC, "Resetting params", 0, 2 );

   if ( bKeyListCreated )
   {
      zCHAR szDeleteCmd[ 300 ];

      sprintf_s( szDeleteCmd, zsizeof( szDeleteCmd ),
                 "DELETE FROM ZEIDONKEYLIST WHERE TASKID = %ld",
                 SysGetTaskFromView( lpView ) );

      nRC = SQLPrepare( lpConnection->hGeneralStmt, szDeleteCmd, SQL_NTS );
      SQL_RC( "Prepare", nRC, "Deleting KeyList", 0, 2 );

      nRC = SQLExecute( lpConnection->hGeneralStmt );
      SQL_RC( "SQLExecute", nRC, "Delete keys", 0, 2 );
   }

   nRC = SQLFreeStmt(lpConnection->hstmt, SQL_CLOSE);
   SQL_RC( "SQLFreeStmt", nRC, "Closing stmt handle", 0, 2 );

#elif defined( ODBC )
   if ( bCursorOpened )
   {
      zSHORT nRC2;

      nRC2 = SQLCloseCursor( lpConnection->hstmt );
      SQL_RC( "SQLCloseCursor", nRC2, 0, 0, 2 );
   }

   if ( bKeyListCreated )
   {
      zCHAR szDeleteCmd[ 300 ];

      sprintf_s( szDeleteCmd, zsizeof( szDeleteCmd ),
                 "DELETE FROM ZEIDONKEYLIST WHERE TASKID = %ld",
                 SysGetTaskFromView( lpView ) );

      nRC = SQLPrepare( lpConnection->hGeneralStmt, szDeleteCmd, SQL_NTS );
      SQL_RC( "Prepare", nRC, "Deleting KeyList", 0, 2 );

      nRC = SQLExecute( lpConnection->hGeneralStmt );
      SQL_RC( "SQLExecute", nRC, "Delete keys", 0, 2 );
   }

   if ( g_bHoldStmtHandles == FALSE )
   {
      zSHORT nRC2;

      nRC2 = SQLFreeStmt( lpConnection->hstmt, SQL_UNBIND );
      SQL_RC( "SQLFreeStmt", nRC2, "Unbinding stmt handle", 0, 2 );
   }
   else
   {
      // We're holding on to the handles so we don't want to free the
      // current lpBoundList so hold on to it.  Setting it to null means
      // it won't be freed (we saved the value earlier).
      lpBoundList = 0;
   }

#endif

   SqlFreeBoundAttrList( lpBoundList );

   // If hMem is not zero, then free the memory allocated.
   if ( hMem )
      SysFreeMemory( hMem );

   return( nReturnCode );

}  /* Load */

/////////////////////////////////////////////////////////////////////////////
//
//    Insert
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
Insert( LPVIEWENTITY lpViewEntity,
        zVIEW        lpView,
        LPVIEWOD     lpViewOD,
        zSHORT       bAutoSeqOnly,
        LPCONNECTION lpConnection )
{
   LPDATARECORD    lpDataRecord;
   LPRELRECORD     lpRelRecord;
   LPBOUNDLIST     lpBoundList;
   zPVOID          pvDBH_Data = 0;
   zPCHAR          pchRecordName;
   zSHORT          nBuildRC;
   zSHORT          nRC = 0;

#if defined( DB2 ) || defined( ODBC )
   CallbackInfoRecord CallbackInfo = { 0 };

   pvDBH_Data = &CallbackInfo;
   CallbackInfo.cBuildFunction = BUILD_CREATE;

#if defined( ODBC )
      // Get a pointer to the dbh-specific data for ODBC.  We'll pass this
      // info around via the lpBoundList structure.
      CallbackInfo.lpObjectData = zGETPTR( lpViewOD->hDBH_Data );
#endif

#endif

   SqlInitBoundAttrList( &lpBoundList, 0,
                         fnDBH_Callback, zCB_FUNCS, pvDBH_Data );

   lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );
   lpRelRecord  = zGETPTR( lpDataRecord->hFirstRelRecord );
   pchRecordName = lpDataRecord->szRecordName;

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "", "" );
      TraceLineS( "========== Insert ==========", "" );
      TraceLineS( "Inserting entity ", lpViewEntity->szName );
      TraceLineS( "Inserting record ", lpDataRecord->szRecordName );
      if ( lpConnection->nTraceLevel > 2 )
         DisplayEntityInstance( lpView, lpViewEntity->szName );
   }

   // Build SQL for insert.  If nBuildRC == 1 after build, then there are some
   // long var chars that need to be bound.
   nBuildRC = SqlBuildInsert( lpView, lpViewOD, lpViewEntity,
                              lpConnection->pchConnSqlCmd, lpBoundList );
   if ( nBuildRC == zCALL_ERROR )
   {
      SqlFreeBoundAttrList( lpBoundList );
      return( zCALL_ERROR );
   }

   // ================================================================
   // Prepare/compile insert statement
   // ================================================================

#if defined( DB2 ) || defined( ODBC )

   lpConnection->hstmt = lpConnection->hGeneralStmt;

   nRC = SQLPrepare( lpConnection->hstmt, lpConnection->pchConnSqlCmd, SQL_NTS );
   DisplayCommand( "SQLPrepare", nRC, lpConnection );

#endif

   if ( nRC )
   {
      SqlFreeBoundAttrList( lpBoundList );
      return( zCALL_ERROR );
   }

   // If needed, bind any long varchars.
   nRC = WriteLongChar( lpConnection, lpBoundList );
   if ( nRC < 0 )
   {
      SqlFreeBoundAttrList( lpBoundList );
      return( zCALL_ERROR );
   }

   // ================================================================
   // Insert table.
   // ================================================================

#if defined( DB2 ) || defined( ODBC )

   nRC = SQLExecute( lpConnection->hstmt );
   SqlFreeBoundAttrList( lpBoundList );
// lpBoundList = 0;

   if ( nRC != SQL_SUCCESS && nRC != SQL_SUCCESS_WITH_INFO )
   {
      // If the trace level is 0 then let's trace the SQL to help debugging.
      if ( lpConnection->nTraceLevel == 0 )
         SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
   }

   if ( nRC == 805 && lpViewEntity->hParent == 0 )
   {
      SQL_RC( "SQLExecute", nRC, "Duplicate root", 0, 2 );
      nRC = zDUPLICATE_ROOT;
      return( zDUPLICATE_ROOT );
   }
   else
   {
      SQL_RC( "SQLExecute", nRC, 0, 0, 2 );
      if ( nRC != SQL_SUCCESS && nRC != SQL_SUCCESS_WITH_INFO )
         return( zCALL_ERROR );
   }

#elif defined( DUMMY )

   if ( lpConnection->nTraceLevel > 0 )
   {
      TraceLineS( "", "" );
      SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
   }

#endif

   lpConnection->bDatabaseChanged = TRUE;

   return( 0 );
}  /* Insert */

/////////////////////////////////////////////////////////////////////////////
//
//    InsertRel
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
InsertRel( LPVIEWENTITY lpViewEntity,
           zVIEW        lpView,
           LPVIEWOD     lpViewOD,
           LPCONNECTION lpConnection )
{
   LPDATARECORD    lpDataRecord;
   LPRELRECORD     lpRelRecord;
   LPBOUNDLIST     lpBoundList;
   zPVOID          pvDBH_Data = 0;
   zPCHAR          pchRecordName;
   zSHORT          nRC;

#if defined( DB2 ) || defined( ODBC )
   CallbackInfoRecord CallbackInfo = { 0 };

   pvDBH_Data = &CallbackInfo;
   CallbackInfo.cBuildFunction = BUILD_INCLUDE;

   #if defined( ODBC )
      // Get a pointer to the dbh-specific data for ODBC.  We'll pass this
      // info around via the lpBoundList structure.
      CallbackInfo.lpObjectData = zGETPTR( lpViewOD->hDBH_Data );
   #endif

#endif

   SqlInitBoundAttrList( &lpBoundList, 0,
                         fnDBH_Callback, zCB_FUNCS, pvDBH_Data );

   lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );
   lpRelRecord  = zGETPTR( lpDataRecord->hFirstRelRecord );
   pchRecordName = lpDataRecord->szRecordName;

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "", "" );
      TraceLineS( "========== Insert Rel ==========", "" );
      TraceLineS( "Inserting rel for entity ", lpViewEntity->szName );
      TraceLineS( "Inserting rel for record ", lpDataRecord->szRecordName );

      if ( lpConnection->nTraceLevel > 2 )
      {
         LPVIEWENTITY lpParent = zGETPTR( lpViewEntity->hParent );

         TraceLineS( "PARENT:", "" );
         DisplayEntityInstance( lpView, lpParent->szName );

         TraceLineS( "CHILD:", "" );
         DisplayEntityInstance( lpView, lpViewEntity->szName );
      }
   }

   // The only thing that needs to be done is to insert the correspondence
   // table if the relationship is many-to-many.
   if ( lpRelRecord->cOwnerMember == zDBH_MANY_TO_MANY )
   {
      nRC = SqlBuildInsertCorrTable( lpView, lpViewOD, lpViewEntity,
                                     lpConnection->pchConnSqlCmd, lpBoundList );
      SqlFreeBoundAttrList( lpBoundList );
   // lpBoundList = 0;
      if ( nRC == zCALL_ERROR )
         return( zCALL_ERROR );

      // ================================================================
      // Insert correspondence table.
      // ================================================================

#if defined( DB2 ) || defined( ODBC )

      lpConnection->hstmt = lpConnection->hGeneralStmt;

      nRC = SQLExecDirect( lpConnection->hstmt, lpConnection->pchConnSqlCmd,
                           SQL_NTS );
      DisplayCommand( "SQLExecDirect", nRC, lpConnection );
      if ( nRC != SQL_SUCCESS )
         return( zCALL_ERROR );

#elif defined( DUMMY )

      if ( lpConnection->nTraceLevel > 0 )
      {
         TraceLineS( "", "" );
         SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
      }

#endif

      lpConnection->bDatabaseChanged = TRUE;
   }

   return( 0 );

}  /* InsertRel */

/////////////////////////////////////////////////////////////////////////////
// Delete
/////////////////////////////////////////////////////////////////////////////
zSHORT
Delete( LPVIEWENTITY lpViewEntity,
        zVIEW        lpView,
        LPVIEWOD     lpViewOD,
        LPCONNECTION lpConnection )
{
   LPDATARECORD    lpDataRecord;
   LPRELRECORD     lpRelRecord;
   LPBOUNDLIST     lpBoundList;
   zPVOID          pvDBH_Data = 0;
   zBOOL           bDeleteRequired = TRUE;  // dks ... 2006.01.25
   zSHORT          nRC;

#if defined( DB2 ) || defined( ODBC )
   CallbackInfoRecord CallbackInfo = { 0 };

   pvDBH_Data = &CallbackInfo;
   CallbackInfo.cBuildFunction = BUILD_DELETE;

   #if defined( ODBC )
      // Get a pointer to the dbh-specific data for ODBC.  We'll pass this
      // info around via the lpBoundList structure.
      CallbackInfo.lpObjectData = zGETPTR( lpViewOD->hDBH_Data );
   #endif

#endif

   SqlInitBoundAttrList( &lpBoundList, 0,
                         fnDBH_Callback, zCB_FUNCS, pvDBH_Data );

   lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );
   lpRelRecord  = zGETPTR( lpDataRecord->hFirstRelRecord );

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "", "" );
      TraceLineS( "========== Delete ==========", "" );
      TraceLineS( "Deleting entity ", lpViewEntity->szName );
      TraceLineS( "Deleting record ", lpDataRecord->szRecordName );
      if ( lpConnection->nTraceLevel > 2 )
         DisplayEntityInstance( lpView, lpViewEntity->szName );
   }

   // ================================================================
   // Delete table.
   // ================================================================

   // Start dks ... 2006.01.25
   if ( lpConnection->bDeleteAll )
   {
      if ( SqlBuildDeleteAll( lpView, lpViewOD, lpViewEntity,
                              lpConnection->pchConnSqlCmd, lpBoundList ) == 0 )
      {
         TraceLineS( "SqlBuildDeleteAll SQL: ", lpConnection->pchConnSqlCmd );
         bDeleteRequired = FALSE;
      }

      lpConnection->bDeleteAll = FALSE;
   }
   // End dks ... 2006.01.25

   if ( bDeleteRequired )
   {
      nRC = SqlBuildDelete( lpView, lpViewOD, lpViewEntity,
                            lpConnection->pchConnSqlCmd, lpBoundList );
   }

   SqlFreeBoundAttrList( lpBoundList );
// lpBoundList = 0;
   if ( nRC == zCALL_ERROR )
      return( zCALL_ERROR );

#if defined( DB2 ) || defined( ODBC )

   lpConnection->hstmt = lpConnection->hGeneralStmt;

   nRC = SQLExecDirect( lpConnection->hstmt, lpConnection->pchConnSqlCmd, SQL_NTS );
   DisplayCommand( "SQLExecDirect", nRC, lpConnection );
   if ( nRC != SQL_SUCCESS )
      return( zCALL_ERROR );

#elif defined( DUMMY )

   if ( lpConnection->nTraceLevel > 0 )
   {
      TraceLineS( "", "" );
      SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
   }

#endif

   lpConnection->bDatabaseChanged = TRUE;

   return( 0 );
}  /* Delete */

/////////////////////////////////////////////////////////////////////////////
//  DeleteRel
/////////////////////////////////////////////////////////////////////////////
zSHORT
DeleteRel( LPVIEWENTITY lpViewEntity,
           zVIEW        lpView,
           LPVIEWOD     lpViewOD,
           LPCONNECTION lpConnection )
{
   LPDATARECORD    lpDataRecord;
   LPRELRECORD     lpRelRecord;
   LPBOUNDLIST     lpBoundList;
   zPVOID          pvDBH_Data = 0;
   zSHORT          nRC;

#if defined( DB2 ) || defined( ODBC )
   CallbackInfoRecord CallbackInfo = { 0 };

   pvDBH_Data = &CallbackInfo;
   CallbackInfo.cBuildFunction = BUILD_EXCLUDE;

   #if defined( ODBC )
      // Get a pointer to the dbh-specific data for ODBC.  We'll pass this
      // info around via the lpBoundList structure.
      CallbackInfo.lpObjectData = zGETPTR( lpViewOD->hDBH_Data );
   #endif

#endif

   SqlInitBoundAttrList( &lpBoundList, 0,
                         fnDBH_Callback, zCB_FUNCS, pvDBH_Data );

   lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );
   lpRelRecord  = zGETPTR( lpDataRecord->hFirstRelRecord );

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "", "" );
      TraceLineS( "========== Delete Rel ==========", "" );
      TraceLineS( "Deleting entity ", lpViewEntity->szName );
      TraceLineS( "Deleting record ", lpDataRecord->szRecordName );
      if ( lpConnection->nTraceLevel > 2 )
         DisplayEntityInstance( lpView, lpViewEntity->szName );
   }

   // The only thing that needs to be done is to delete the correspondence
   // table if the relationship is many-to-many.
   if ( lpRelRecord->cOwnerMember == zDBH_MANY_TO_MANY )
   {
      nRC = SqlBuildDeleteCorrTable( lpView, lpViewOD, lpViewEntity,
                                     lpConnection->pchConnSqlCmd, lpBoundList );
      SqlFreeBoundAttrList( lpBoundList );
   // lpBoundList = 0;
      if ( nRC == zCALL_ERROR )
         return( zCALL_ERROR );

      // ================================================================
      // Delete correspondence table.
      // ================================================================

#if defined( DB2 ) || defined( ODBC )

      lpConnection->hstmt = lpConnection->hGeneralStmt;

      nRC = SQLExecDirect( lpConnection->hstmt, lpConnection->pchConnSqlCmd,
                           SQL_NTS);
      DisplayCommand( "SQLExecDirect", nRC, lpConnection );
      if ( nRC )
         return( zCALL_ERROR );

#elif defined( DUMMY )

      if ( lpConnection->nTraceLevel > 0 )
      {
         TraceLineS( "", "" );
         SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
      }

#endif

      lpConnection->bDatabaseChanged = TRUE;
   }

   return( 0 );
}  /* DeleteRel */

/////////////////////////////////////////////////////////////////////////////
//  Update
/////////////////////////////////////////////////////////////////////////////
zSHORT
Update( LPVIEWENTITY lpViewEntity,
        zVIEW        lpView,
        LPVIEWOD     lpViewOD,
        zSHORT       bAutoSeqOnly,
        LPCONNECTION lpConnection )
{
   LPDATARECORD    lpDataRecord;
   LPRELRECORD     lpRelRecord;
   LPBOUNDLIST     lpBoundList;
   zPVOID          pvDBH_Data = 0;
   zSHORT          nRC, nBuildRC;

#if defined( DB2 ) || defined( ODBC )
   CallbackInfoRecord CallbackInfo = { 0 };

   pvDBH_Data = &CallbackInfo;
   CallbackInfo.cBuildFunction = BUILD_UPDATE;

   #if defined( ODBC )
      // Get a pointer to the dbh-specific data for ODBC.  We'll pass this
      // info around via the lpBoundList structure.
      CallbackInfo.lpObjectData = zGETPTR( lpViewOD->hDBH_Data );
   #endif

#endif

   SqlInitBoundAttrList( &lpBoundList, 0,
                         fnDBH_Callback, zCB_FUNCS, pvDBH_Data );

   lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "", "" );
      TraceLineS( "========== Update ==========", "" );
      TraceLineS( "Updating entity ", lpViewEntity->szName );
      TraceLineS( "Updating record ", lpDataRecord->szRecordName );
      if ( lpConnection->nTraceLevel > 2 )
         DisplayEntityInstance( lpView, lpViewEntity->szName );
   }

   nBuildRC = SqlBuildUpdate( lpView, lpViewOD, lpViewEntity, bAutoSeqOnly,
                              lpConnection->pchConnSqlCmd, lpBoundList );
   if ( nBuildRC == zCALL_ERROR )
   {
      SqlFreeBoundAttrList( lpBoundList );
      return( zCALL_ERROR );
   }

   // ================================================================
   // Prepare/compile Update statement.
   // ================================================================

   // If nBuildRC is -1 then none of the attributes where updated so don't
   // update the table.
   if ( nBuildRC != -1 )
   {

#if defined( DB2 ) || defined( ODBC )

      lpConnection->hstmt = lpConnection->hGeneralStmt;

      nRC = SQLPrepare( lpConnection->hstmt, lpConnection->pchConnSqlCmd, SQL_NTS );
      DisplayCommand( "SQLPrepare", nRC, lpConnection );
      if ( nRC != SQL_SUCCESS )
      {
         SqlFreeBoundAttrList( lpBoundList );
         return( zCALL_ERROR );
      }

#elif defined( DUMMY )

      if ( lpConnection->nTraceLevel > 0 )
      {
         TraceLineS( "", "" );
         SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
      }

#endif

      nRC = WriteLongChar( lpConnection, lpBoundList );
      if ( nRC < 0 )
      {
         SqlFreeBoundAttrList( lpBoundList );
         return( zCALL_ERROR );
      }

      // ================================================================
      // Execute Update statement.
      // ================================================================
#if defined( DB2 ) || defined( ODBC )

      nRC = SQLExecute( lpConnection->hstmt );
      SQL_RC( "SQLExecute", nRC, 0, 0, 2 );
      if ( nRC != SQL_SUCCESS )
      {
         // If the trace level is 0 then let's trace the SQL to help debugging.
         if ( lpConnection->nTraceLevel == 0 )
            SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );

         SqlFreeBoundAttrList( lpBoundList );
         return( zCALL_ERROR );
      }

#endif

   } // if ( nBuildRC != -1 )...

   // We don't need it any more...
   SqlFreeBoundAttrList( lpBoundList );
// lpBoundList = 0;

   // If the entity has auto seq attributes, then the corr table might have
   // to be updated.  This will only happen if the current entity has a parent
   // and if the relationship is many-to-many.
   lpRelRecord = zGETPTR( lpDataRecord->hFirstRelRecord );
   if ( lpViewEntity->bAutoSeq && lpViewEntity->hParent &&
        lpRelRecord->cOwnerMember == zDBH_MANY_TO_MANY )
   {
      nRC = SqlBuildUpdateCorrTable( lpView, lpViewOD, lpViewEntity,
                                     lpConnection->pchConnSqlCmd, lpBoundList );
      SqlFreeBoundAttrList( lpBoundList );
   // lpBoundList = 0;
      if ( nRC == zCALL_ERROR )
         return( zCALL_ERROR );

      // ================================================================
      // Update correspondence table.
      // ================================================================

      // If nBuildRC is -1 then none of the attributes where updated so don't
      // update the table.
      if ( nRC != -1 )
      {
#if defined( DB2 ) || defined( ODBC )

         lpConnection->hstmt = lpConnection->hGeneralStmt;

         nRC = SQLExecDirect( lpConnection->hstmt, lpConnection->pchConnSqlCmd,
                              SQL_NTS );
         DisplayCommand( "SQLExecDirect", nRC, lpConnection );
         if ( nRC )
            return( zCALL_ERROR );

#elif defined( DUMMY )

         if ( lpConnection->nTraceLevel > 0 )
         {
            TraceLineS( "", "" );
            SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
         }

#endif
      } // if ( nBuildRC != -1 )...
   }

   lpConnection->bDatabaseChanged = TRUE;

   return( 0 );
}  /* Update */


//=========================================================================
//       UTILITY FUNCTIONS -- in alphabetical order
//=========================================================================


/////////////////////////////////////////////////////////////////////////////
//   DBH_Error
/////////////////////////////////////////////////////////////////////////////
void
DBH_Error( zVIEW lpView, zPCHAR pchErrorMsg, int nRC, zPCHAR pchInfo )
{
   TraceLineS( "===== DBH_Entry Error =====", "" );
   TraceLineS( "Msg=> ", pchErrorMsg );

   if ( nRC )
      TraceLineI( "nRC=> ", nRC );

   if ( pchInfo )
      TraceLineS( pchInfo, "" );

   MessageSend( lpView, "KZH0101", DBHANDLER_NAME " DBH Error",
                pchErrorMsg,
                zMSGQ_SYSTEM_ERROR, 0 );

}  /* DBH_Error */

#if defined( DB2 ) || defined( ODBC )

zPCHAR
fnRC_Text( zSHORT nRC )
{
   static zCHAR szReturn[ 100 ];

   switch ( nRC )
   {
      case SQL_SUCCESS:
         sprintf_s( szReturn, zsizeof( szReturn ), "%d (SQL_SUCCESS)", nRC );
         break;

      case SQL_SUCCESS_WITH_INFO:
         sprintf_s( szReturn, zsizeof( szReturn ), "%d (SQL_SUCCESS_WITH_INFO)", nRC );
         break;

      case SQL_ERROR:
         sprintf_s( szReturn, zsizeof( szReturn ), "%d (SQL_ERROR)", nRC );
         break;

      case SQL_INVALID_HANDLE:
         sprintf_s( szReturn, zsizeof( szReturn ), "%d (SQL_INVALID_HANDLE)", nRC );
         break;

      case SQL_NEED_DATA:
         sprintf_s( szReturn, zsizeof( szReturn ), "%d (SQL_NEED_DATA)", nRC );
         break;

#ifdef DB2
      case SQL_NO_DATA_FOUND:
         sprintf_s( szReturn, zsizeof( szReturn ), "%d (SQL_NO_DATA_FOUND)", nRC );
         break;
#else
      #if (ODBCVER >= 0x0300)
         case SQL_NO_DATA:
            sprintf_s( szReturn, zsizeof( szReturn ), "%d (SQL_NO_DATA)", nRC );
            break;
#endif

      case SQL_STILL_EXECUTING:
         sprintf_s( szReturn, zsizeof( szReturn ), "%d (SQL_STILL_EXECUTING)", nRC );
         break;
#endif

      default:
         sprintf_s( szReturn, zsizeof( szReturn ), "%d (unknown)", nRC );
         break;
   }

   return( szReturn );
}

#endif

/////////////////////////////////////////////////////////////////////////////
//  DisplayCommand
/////////////////////////////////////////////////////////////////////////////

#if defined( DB2 )

void
DisplayCommand( zPCHAR       pchRoutine,
                zSHORT       nRC,
                LPCONNECTION lpConnection )
{
   SQLHDBC     hdbc;
   SQLHSTMT    hstmt;
   SQLINTEGER  iSqlCode;
   SQLSMALLINT sLength;
   zCHAR       szText[ SQL_MAX_MESSAGE_LENGTH + 1 ];
   zCHAR       szSqlState[ SQL_SQLSTATE_SIZE + 1 ];

   if ( lpConnection->nTraceLevel == 0 && nRC == SQL_SUCCESS )
      return;

   if ( lpConnection->bMultipleDatabases )
   {
      TraceLineS( "", "" );
      TraceLineS( "Database name = ",
                  lpConnection->DBConnection[ lpConnection->nCurrentDB ].szDatabaseName );
   }

   TraceLineS( "", "" );

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "DB2 Call : ", pchRoutine );
      SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
      TraceLineS( "Return Code :", fnRC_Text( nRC ) );
   }
   else
      SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );

   if ( nRC != SQL_SUCCESS )
   {
      if ( lpConnection->hstmt )
         hstmt = lpConnection->hstmt;
      else
         hstmt = SQL_NULL_HSTMT;

      if ( lpConnection->hdbc )
         hdbc = lpConnection->hdbc;
      else
         hdbc = SQL_NULL_HDBC;

      if ( nRC != SQL_SUCCESS_WITH_INFO && nRC != SQL_NO_DATA_FOUND )
         TraceLineS( "===== SQL DB2 Error ===== rc = ", fnRC_Text( nRC ) );
      else
         TraceLineS( "===== SQL DB2 Info ===== rc = ", fnRC_Text( nRC ) );

      while ( SQLError( lpConnection->henv, hdbc, hstmt, szSqlState, &iSqlCode,
                        szText, SQL_MAX_MESSAGE_LENGTH + 1,
                        &sLength ) == SQL_SUCCESS )
      {
         TraceLineS( "SQL State = ", szSqlState );
         TraceLineI( "Native Error Code = ", (zLONG) iSqlCode );
         MessageSend( lpConnection->lpAppView, "KZH0102", "DB2 DBH Error",
                      szText, zMSGQ_SYSTEM_ERROR, 0 );
      }
   }

}  /* DisplayCommand */

#elif defined( DUMMY )

void
DisplayCommand( zPCHAR       pchRoutine,
                zSHORT       nRC,
                LPCONNECTION lpConnection )
{
   if ( lpConnection->nTraceLevel == 0 && nRC == 0 )
      return;

   if ( lpConnection->bMultipleDatabases )
   {
      TraceLineS( "", "" );
      TraceLineS( "Database name = ",
       lpConnection->DBConnection[ lpConnection->nCurrentDB ].szDatabaseName );
   }

   TraceLineS( "", "" );

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "Dummy Call : ", pchRoutine );
      SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
      TraceLineI( "Return Code :", nRC );
   }
   else
      SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );

}  /* DisplayCommand */

#elif defined( ODBC )

void
DisplayCommand( zPCHAR       pchRoutine,
                zSHORT       nRC,
                LPCONNECTION lpConnection )
{
   zCHAR   szText[ 2000 ];
   zCHAR   szText2[ 50 ];
   zCHAR   szSQLState[ 6 ];

   if ( lpConnection->nTraceLevel == 0 && nRC == SQL_SUCCESS )
      return;

   if ( lpConnection->bMultipleDatabases )
   {
      TraceLineS( "", "" );
      TraceLineS( "Database name = ",
       lpConnection->DBConnection[ lpConnection->nCurrentDB ].szDatabaseName );
   }

   TraceLineS( "", "" );

   if ( lpConnection->nTraceLevel > 1 )
   {
      TraceLineS( "ODBC Call : ", pchRoutine );
      SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );
      TraceLineS( "Return Code :", fnRC_Text( nRC ) );
   }
   else
      SqlDisplayCommand( lpConnection->pchConnSqlCmd, 0 );

   if ( nRC != SQL_SUCCESS )
   {
      SQLHANDLE   hSql;
      SQLSMALLINT iHandleType;
      SDWORD      sdNumRecs;
      SQLSMALLINT k;
      SDWORD      sdNativeError;
      SQLSMALLINT nTextLength;

      if ( lpConnection->hstmt )
      {
         hSql = lpConnection->hstmt;
         iHandleType = SQL_HANDLE_STMT;
      }
      else
      if ( lpConnection->hdbc )
      {
         hSql = lpConnection->hdbc;
         iHandleType = SQL_HANDLE_DBC;
      }
      else
      {
         hSql = lpConnection->henv;
         iHandleType = SQL_HANDLE_ENV;
      }

      SQLGetDiagField( iHandleType, hSql, 0, SQL_DIAG_NUMBER, &sdNumRecs,
                       sizeof( sdNumRecs ), 0 );

      if ( nRC != SQL_SUCCESS_WITH_INFO )
         TraceLineS( "===== SQL ODBC Error ===== rc = ", fnRC_Text( nRC ) );
      else
         TraceLineS( "===== SQL ODBC Info ===== rc = ", fnRC_Text( nRC ) );

      for ( k = 1; k <= sdNumRecs && k < 5; k++ )
      {
         SQLGetDiagRec( iHandleType, hSql, k, szSQLState, &sdNativeError,
                        szText, zsizeof( szText ), &nTextLength );
         sprintf_s( szText2, zsizeof( szText2 ), "[ODBC] SQLState = %s, Err=", szSQLState );
         TraceLineS( szText2, szText );

         MessageSend( lpConnection->lpAppView, "KZH0102", "ODBC DBH Error",
                      szText, zMSGQ_SYSTEM_ERROR, 0 );
      }
   }

}  /* DisplayCommand */

#endif

zSHORT LOCALOPER
fnOpenDatabaseConnection( zVIEW        lpView,
                          LPVIEWOD     lpViewOD,
                          LPVIEWENTITY lpViewEntity,
                          LPCONNECTION lpConnection )
{
   zCHAR  szUserID[ 50 ];
   zCHAR  szPassword[ 50 ];
   zPCHAR lpDBName;
   zPCHAR pchPtr = 0;
   zSHORT k;
   zSHORT nRC = 0;

#if defined( DB2 ) || defined( ODBC )

   if ( lpConnection->henv == 0 )
   {
      nRC = SQLAllocEnv( &lpConnection->henv );
      SQL_RC( "SQLAllocEnv", nRC, 0, 0, 2 );
      if ( nRC != SQL_SUCCESS )
         return( zCALL_ERROR );
   }

#elif defined( ODBC )

   if ( lpConnection->henv == 0 )
   {
      nRC = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE,
                            &lpConnection->henv );
      SQL_RC( "SQLAllocHandle", nRC, 0, 0, 2 );
      if ( nRC != SQL_SUCCESS )
         return( zCALL_ERROR );
   }

#endif

   if ( lpViewOD == 0 && lpViewEntity == 0 )
      return( 0 );

   // Get the database name.
   if ( lpViewEntity && lpViewEntity->szDBName[ 0 ] )
      lpDBName = lpViewEntity->szDBName;
   else
      lpDBName = lpViewOD->szDfltDBName;

   // Loop through all the open database names, looking for one that
   // matches the database we're supposed to use.  If we find one, set
   // the current hSqlCsr to the cursor of the database.
   for ( k = 0; k < lpConnection->nOpenDatabaseCount; k++ )
   {
      if ( zstrcmpi( lpConnection->DBConnection[ k ].szDatabaseName,
                     lpDBName ) == 0 )
      {
         //==============================================================
         // Copy opened DB information to 'common' information.
         //==============================================================

#if defined( DB2 ) || defined( ODBC )

         lpConnection->hdbc = lpConnection->DBConnection[ k ].hdbc;

#endif
         break;
      }
   }

   lpConnection->nCurrentDB = k;
   if ( k >= lpConnection->nOpenDatabaseCount ||
        lpConnection->DBConnection[ k ].bValidConnection == FALSE )
   {
      if ( k >= MAX_OPEN_DATABASES )
      {
         DBH_Error( lpView, "Too many open databases for 1 session.", 0, 0 );
         return( zCALL_ERROR );
      }

      // If k >= DBCount, then we need to open a new database.
      // Otherwise we will try to re-open a database that failed earlier.
      if ( k >= lpConnection->nOpenDatabaseCount )
      {
         lpConnection->nOpenDatabaseCount++;
         strcpy_s( lpConnection->DBConnection[ k ].szDatabaseName, 64, lpDBName );
      }

      SysGetDB_UserID( lpView, szUserID, zsizeof( szUserID ), szPassword, zsizeof( szPassword ) );

      //==============================================================
      // Open database.
      //==============================================================

#if defined( DB2 ) || defined( ODBC )

      nRC = SQLAllocConnect( lpConnection->henv, &lpConnection->hdbc );
      SQL_RC( "SQLAllocConnect", nRC, 0, 0, 2 );
      if ( nRC != SQL_SUCCESS )
         return( zCALL_ERROR );

      nRC = SQLConnect( lpConnection->hdbc, lpDBName, SQL_NTS,
                        szUserID, SQL_NTS, szPassword, SQL_NTS );
      SQL_RC( "SQLConnect", nRC, "Database = ", lpDBName, 1 );
      if ( !RC_SUCCESSFUL( nRC ) )
      {
         zCHAR szText[ 200 ];

         sprintf_s( szText, zsizeof( szText ), "Error connecting to DB %s", lpDBName );
         MessageSend( lpConnection->lpAppView, "KZH0102", "ODBC DBH Error",
                      szText, zMSGQ_SYSTEM_ERROR, 0 );

         SQLFreeHandle( SQL_HANDLE_DBC, (SQLHANDLE) lpConnection->hdbc );
         lpConnection->hdbc = 0;
         return( zCALL_ERROR );
      }

#if defined( ODBC )
      nRC = SQLSetConnectAttr( lpConnection->hdbc, SQL_ATTR_AUTOCOMMIT,
                               SQL_AUTOCOMMIT_OFF, 0 );
      SQL_RC( "SQLSetConnectAttr", nRC, "Turning AutoCommit off", 0, 2 );
#endif

      lpConnection->DBConnection[ k ].hdbc = lpConnection->hdbc;

#endif

      lpConnection->DBConnection[ k ].bValidConnection = TRUE;

   } // if ( k >= lpConnection->nOpenDatabaseCount ||...

#if defined( DB2 )

   if ( lpConnection->hGeneralStmt == 0 )
   {
      nRC = SQLAllocStmt( lpConnection->hdbc, &lpConnection->hGeneralStmt );
      SQL_RC( "SQLAllocStmt", nRC, "Allocate HSTMT", 0, 2 );
      if ( nRC != SQL_SUCCESS )
         return( zCALL_ERROR );
   }

#elif defined( ODBC )

   if ( lpConnection->hGeneralStmt == 0 )
   {
      nRC = SQLAllocHandle( SQL_HANDLE_STMT, lpConnection->hdbc,
                            &lpConnection->hGeneralStmt );
      SQL_RC( "SQLAllocHandle", nRC, "Allocate HSTMT", 0, 2 );
      if ( nRC != SQL_SUCCESS )
         return( zCALL_ERROR );
   }

#endif

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    GetWorkObjectView
//
//    Returns: 0 - OK
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
GetWorkObjectView( LPTASK       hTask,
                   zVIEW        lpView,
                   LPVIEWOD     lpViewOD,
                   LPVIEWENTITY lpViewEntity,
                   zPPVOID      ppvWorkPtr,
                   LPCONNECTION *lppConnection )
{
   LPCONNECTION     lpConnection;
   zVIEW            vDbhWork;
   zCHAR            szLogicalName[ 200 ];
   zCHAR            szStr[ 20 ];
   zLONG            lProcessID;
   zSHORT           nRC;

   // If vDbhWorkPTr points to a null pointer then we haven't yet initialized
   // the work pointer--so do it.
   if ( *ppvWorkPtr == 0 )
   {
      ConnectionRecord ConnRec;
      zSHORT           nTraceLevel = 0;

      GetViewByName( &vDbhWork, zDBHANDLER_WORK_VIEW_NAME, lpView, zLEVEL_SYSTEM );
      if ( vDbhWork == 0 )
      {
         DBH_Error( lpView, "Can't find DB-Handler work view.", 0, 0 );
         return( zCALL_ERROR );
      }

      SysMutexLock( lpView, "Zeidon DBH", 0, 0 );

      CreateViewFromViewForTask( &vDbhWork, vDbhWork, lpView );

      szStr[ 0 ] = zSQL_type;
      szStr[ 1 ] = 0;

      nRC = SetCursorFirstEntityByString( vDbhWork, "Type", "Type", szStr, 0 );
      if ( nRC != zCURSOR_SET )
      {
         CreateEntity( vDbhWork, "Type", zPOS_LAST );
         SetAttributeFromString( vDbhWork, "Type", "Type", szStr );
      }

#if 1
      {
         zVIEW v = GetDefaultViewForActiveTask( );
         zLONG lTask;

         if ( v && (LPTASK) (lTask = SysGetTaskFromView( v )) != hTask )
         {
            TraceLine( "GetWorkObjectView RESETTING task from: 0x%08x  to: 0x%08x",
                       hTask, lTask );
            hTask = (LPTASK) lTask;
         }
      }
#endif

      lProcessID = SysGetProcessID( 0 );
   // zltoa( (zLONG) hTask, szLogicalName );
      sprintf_s( szLogicalName, zsizeof( szLogicalName ), "0x%08x:%08x", (zULONG) hTask, lProcessID );

   // sprintf_s( szLogicalName, zsizeof( szLogicalName ), "0x%08x", (zULONG) SysGetTaskFromView( lpView ) );

      nRC = SetCursorFirstEntityByString( vDbhWork, "Connection",
                                          "LogicalUserName", szLogicalName, "" );
      if ( nRC != zCURSOR_SET )
      {
         CreateEntity( vDbhWork, "Connection", zPOS_AFTER );
         SetAttributeFromString( vDbhWork, "Connection",
                                 "LogicalUserName", szLogicalName );
      // TraceLineS( "GetWorkObjectView adding Connection =======================>",
      //             szLogicalName );   // dks debug
         SetAttributeFromInteger( vDbhWork, "Connection",
                                  "TaskID", (zLONG) hTask );

         zmemset( (zPVOID) &ConnRec, 0, sizeof( ConnRec ) );
#ifdef DEBUG
         strcpy_s( ConnRec.szDebug1, 16, "Conn BEGIN" );
         strcpy_s( ConnRec.szDebug2, 16, "Conn END" );
#endif

         SetAttributeFromBlob( vDbhWork, "Connection", "ConnectionBlob",
                               (zPVOID) &ConnRec, sizeof( ConnectionRecord ) );

         GetAddrForAttribute( (zPVOID) lppConnection, vDbhWork,
                              "Connection", "ConnectionBlob" );

         lpConnection = *lppConnection;
         lpConnection->vDbhWork = vDbhWork;

         // Allocate space for SQL commands and the column buffer.
         fnAllocateConnectionMemory( lpView, *lppConnection, TRUE, MAX_SQLCMD_LENGTH );
         if ( lpConnection->hCmdMem == 0 )
         {
            SysMutexUnlock( lpView, "Zeidon DBH", 0 );
            DropView( vDbhWork );
            return( zCALL_ERROR );
         }

         fnAllocateConnectionMemory( lpView, *lppConnection, FALSE, TABLE_BUFFER_LTH );
         if ( lpConnection->hTblMem == 0 )
         {
            SysMutexUnlock( lpView, "Zeidon DBH", 0 );

            // Free connection memory (last parm zero).
            fnAllocateConnectionMemory( lpView, *lppConnection, TRUE, 0 );
            DropView( vDbhWork );
            return( zCALL_ERROR );
         }

      }  // if ( nRC != zCURSOR_SET )...
      else
      {
         GetAddrForAttribute( (zPVOID) lppConnection, vDbhWork,
                              "Connection", "ConnectionBlob" );
         lpConnection = *lppConnection;
         lpConnection->vDbhWork = vDbhWork;
      }

      if ( lpView )
         nTraceLevel = GetTaskDBHandlerTraceLevel( lpView );

      if ( nTraceLevel == 0 )
      {
         zCHAR  szStr[ 20 ];

         // Get the default trace level from the INI file.
         SysReadZeidonIni( -1, "[" DBHANDLER_NAME "]", "TraceLevel", szStr, zsizeof( szStr ) );
         if ( szStr[ 0 ] )
            nTraceLevel = (zSHORT) zatol( szStr );
      }

      lpConnection->nTraceLevel = nTraceLevel;

      *ppvWorkPtr = (zPVOID) *lppConnection;

      // Create a subtask view so we can reference the application.
      if ( lpConnection->lpAppView == 0 )
         SfCreateSubtask( &lpConnection->lpAppView, lpView, 0 );

      SysMutexUnlock( lpView, "Zeidon DBH", 0 );

   } // if ( *ppvWorkPtr == 0 )...
   else
   {
      *lppConnection = (LPCONNECTION) *ppvWorkPtr;
      lpConnection = *lppConnection;
   }

#if defined ( DB2 )
{
   LPOD_LIST lpOD = fnFindOD( lpViewOD, lpConnection );

   if ( lpOD == 0 )
      lpOD = fnAddOD( lpViewOD, lpConnection );
}
#endif

   nRC = fnOpenDatabaseConnection( lpView, lpViewOD, lpViewEntity, lpConnection );
   return( nRC );

}  /* GetWorkObjectView */

/////////////////////////////////////////////////////////////////////////////
//   fnSqlRC
/////////////////////////////////////////////////////////////////////////////

#if defined( DB2 )

void
fnSqlRC( zPCHAR       pchRoutine,
         zSHORT       nRC,
         zPCHAR       pchInfo1,
         zPCHAR       pchInfo2,
         zSHORT       nTrcLvl,
         LPCONNECTION lpConnection )
{
   SQLHDBC     hdbc;
   SQLHSTMT    hstmt;
   SQLINTEGER  iSqlCode;
   SQLSMALLINT sLength;
   zCHAR       szText[ SQL_MAX_MESSAGE_LENGTH + 1 ];
   zCHAR       szSqlState[ SQL_SQLSTATE_SIZE + 1 ];

   if ( (nRC == SQL_SUCCESS || nRC == SQL_NO_DATA_FOUND) &&
        (lpConnection->nTraceLevel < nTrcLvl ||
         lpConnection->nTraceLevel == 0) )
   {
      return;
   }

   TraceLineS( "", "" );
   if ( !RC_SUCCESSFUL( nRC ) && nRC != SQL_NO_DATA_FOUND )
      TraceLineS( "===== DB2 Error =====", "" );

   TraceLineS( "DB2 Call : ", pchRoutine );
   TraceLineS( "RC       : ", fnRC_Text( nRC ) );

   if ( pchInfo1 )
   {
      if ( pchInfo2 )
         TraceLineS( pchInfo1, pchInfo2 );
      else
         TraceLineS( pchInfo1, "" );
   }

   if ( nRC != SQL_SUCCESS )
   {
      if ( lpConnection->hstmt )
         hstmt = lpConnection->hstmt;
      else
         hstmt = SQL_NULL_HSTMT;

      if ( lpConnection->hdbc )
         hdbc = lpConnection->hdbc;
      else
         hdbc = SQL_NULL_HDBC;

      if ( nRC != SQL_SUCCESS_WITH_INFO && nRC != SQL_NO_DATA_FOUND )
         TraceLineS( "===== SQL DB2 Error ===== rc = ", fnRC_Text( nRC ) );
      else
         TraceLineS( "===== SQL DB2 Info ===== rc = ", fnRC_Text( nRC ) );

      while ( SQLError( lpConnection->henv, hdbc, hstmt, szSqlState, &iSqlCode,
                        szText, SQL_MAX_MESSAGE_LENGTH + 1,
                        &sLength ) == SQL_SUCCESS )
      {
         fnSetDBHandlerError( lpConnection->lpAppView, (zLONG) iSqlCode,
                              szSqlState, szText );

         TraceLineS( "SQL State = ", szSqlState );
         TraceLineI( "Native Error Code = ", (zLONG) iSqlCode );
         MessageSend( lpConnection->lpAppView, "KZH0102", "DB2 DBH Error",
                      szText, zMSGQ_SYSTEM_ERROR, 0 );
      }
   }
}  /* fnSqlRC */

#elif defined( ODBC )

void
fnSqlRC( zPCHAR       pchRoutine,
         zSHORT       nRC,
         zPCHAR       pchInfo1,
         zPCHAR       pchInfo2,
         zSHORT       nTrcLvl,
         LPCONNECTION lpConnection )
{
   zCHAR  szText[ 2000 ];
   zCHAR  szText2[ 50 ];
   zBOOL bCmdOK = FALSE;

   if ( RC_SUCCESSFUL( nRC ) &&
        (lpConnection->nTraceLevel < nTrcLvl ||
         lpConnection->nTraceLevel == 0) )
   {
      return;
   }

   // In certain cases a return code is OK.
   if ( zstrcmp( pchRoutine, "SQLFetch" ) == 0 )
   {
      if ( nRC == SQL_NO_DATA )
      {
         // The return code is OK so get out if we're not tracing out RCs
         // that worked OK.
         if ( lpConnection->nTraceLevel < nTrcLvl ||
              lpConnection->nTraceLevel == 0 )
         {
            return;
         }

         bCmdOK = TRUE;
      }
   }

   TraceLineS( "", "" );
   if ( !RC_SUCCESSFUL( nRC ) && bCmdOK == FALSE )
      TraceLineS( "===== ODBC Error =====", "" );

   TraceLineS( "ODBC Call : ", pchRoutine );
   TraceLineS( "RC        : ", fnRC_Text( nRC ) );

   if ( pchInfo1 )
   {
      if ( pchInfo2 )
         TraceLineS( pchInfo1, pchInfo2 );
      else
         TraceLineS( pchInfo1, "" );
   }

   if ( nRC != SQL_SUCCESS && bCmdOK == FALSE )
   {
      SQLHANDLE   hSql;
      SQLSMALLINT iHandleType;
      SDWORD      sdNumRecs;
      SQLSMALLINT k;
      SDWORD      sdNativeError;
      SQLSMALLINT nTextLength;
      zCHAR       szSQLState[ 6 ];

      if ( lpConnection->hstmt )
      {
         hSql = lpConnection->hstmt;
         iHandleType = SQL_HANDLE_STMT;
      }
      else
      if ( lpConnection->hdbc )
      {
         hSql = lpConnection->hdbc;
         iHandleType = SQL_HANDLE_DBC;
      }
      else
      {
         hSql = lpConnection->henv;
         iHandleType = SQL_HANDLE_ENV;
      }

      SQLGetDiagField( iHandleType, hSql, 0, SQL_DIAG_NUMBER, &sdNumRecs,
                       sizeof( sdNumRecs ), 0 );

      for ( k = 1; k <= sdNumRecs && k < 5; k++ )
      {
         SQLGetDiagRec( iHandleType, hSql, k, szSQLState, &sdNativeError,
                        szText, zsizeof( szText ), &nTextLength );
         sprintf_s( szText2, zsizeof( szText2 ), "[ODBC] SQLState = %s, Err=", szSQLState );
         TraceLineS( szText2, szText );

         fnSetDBHandlerError( lpConnection->lpAppView, (zLONG) sdNativeError,
                              szSQLState, szText );

         if ( k == 1 && nRC != SQL_SUCCESS_WITH_INFO )
         {
            MessageSend( lpConnection->lpAppView, "KZH0102", "ODBC DBH Error",
                         szText, zMSGQ_SYSTEM_ERROR, 0 );
         }
      }
   }
}  /* fnSqlRC */

#endif

#ifdef DB2
#if (DB2CLI_VER < 0x0300)
SQLRETURN
SQLFreeHandle( zSHORT    nHandleType,
               SQLHANDLE hndl )
#else
SQLRETURN SQL_API_FN
SQLFreeHandle( SQLSMALLINT nHandleType,
               SQLHANDLE hndl )
#endif
{
   switch ( nHandleType )
   {
      case SQL_HANDLE_DBC:
         return( SQLFreeConnect( (SQLHDBC) hndl ) );

      case SQL_HANDLE_ENV:
         return( SQLFreeEnv( (SQLHENV) hndl ) );

      case SQL_HANDLE_STMT:
         return( SQLFreeStmt( (SQLHSTMT) hndl, SQL_DROP ) );
   }

   return( 0 );
}
#endif

/////////////////////////////////////////////////////////////////////////////
//   WriteLongChar
/////////////////////////////////////////////////////////////////////////////

#if defined( DB2 ) || defined( ODBC )

zSHORT
WriteLongChar( LPCONNECTION lpConnection,
               LPBOUNDLIST  lpBoundList )
{
   LPBOUNDATTR  lpBoundAttr;
   zCHAR        chType;
   zPVOID       lpValue;
   zULONG       ulLth;
   zUSHORT      nParmCount;
   zSHORT       nRC;

   // If there are no attributes to be bound, then return.
   if ( lpBoundList->lpFirstBoundAttr == 0 )
      return( 0 );

   // Loop through each bound attribute and write it to the database.
   nParmCount = 0;
   for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
         lpBoundAttr;
         lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
   {
      LPDATAFIELD    lpDataField  = lpBoundAttr->lpDataField;
      LPVIEWATTRIB   lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );
      LPVIEWENTITY   lpViewEntity = zGETPTR( lpViewAttrib->hViewEntity );
      SQLSMALLINT    nValueType;
      SQLSMALLINT    nParmType;
      SQLSMALLINT    nDecDigits;
      SQLUINTEGER    nColumnSize;
      SQLINTEGER     nLth;

      nParmCount++;

      if ( lpConnection->nTraceLevel > 1 )
      {
         TraceLineS( "(KZHSQLBA) WriteLongChar attributename = ",
                     lpViewAttrib->szName );
         TraceLineI( "nParmCount = ", nParmCount );
      }

      // Get pointer to var and get length.
      GetValueFromRecord( lpBoundAttr->lpView,
                          lpViewEntity, lpViewAttrib, (zPVOID) &lpValue,
                          &chType, &ulLth );

      switch ( lpViewAttrib->cType )
      {
         case zTYPE_BLOB:
            nValueType = SQL_C_BINARY;
#ifdef DB2
            nParmType  = SQL_BLOB;
#else
            nParmType  = SQL_LONGVARBINARY;
#endif
            nLth = (SQLINTEGER) ulLth;

            if ( nLth == 0 )
               lpConnection->nStrLth[ nParmCount - 1 ] = SQL_NULL_DATA;
            else
               lpConnection->nStrLth[ nParmCount - 1 ] = nLth;

            break;

         case zTYPE_STRING:
            nValueType = SQL_C_CHAR;
            nParmType  = SQL_LONGVARCHAR;

            // ulLth includes the null-terminator.  If ulLth == 1 then string
            // is empty.
            if ( ulLth <= 1 )
            {
               lpConnection->nStrLth[ nParmCount - 1 ] = SQL_NULL_DATA;
               nLth = 0;
            }
            else
            {
               nLth = (SQLINTEGER) ulLth;
               lpConnection->nStrLth[ nParmCount - 1 ] = SQL_NTS;
            }
            break;
      }

      nColumnSize = nLth;
      nDecDigits = 0;

#if 0
      nRC = SQLDescribeParam( lpConnection->hstmt, nParmCount, &nParmType,
                              &nColumnSize, &nDecDigits, &nNullable );
      SQL_RC( "SQLDescribeParam", nRC, "Column = ", lpDataField->szFldName, 3 );
#endif

      nRC = SQLBindParameter( lpConnection->hstmt, nParmCount, SQL_PARAM_INPUT,
                              nValueType, nParmType, nColumnSize, nDecDigits,
                              (SQLPOINTER) lpValue, nLth,
                              &lpConnection->nStrLth[ nParmCount - 1 ] );
      SQL_RC( "SQLBindParameter", nRC, "Column = ", lpDataField->szFldName, 3 );

      if ( lpConnection->nTraceLevel > 2 )
      {
         TraceLineI( "nValueType  = ", nValueType );
         TraceLineI( "nParmType   = ", nParmType );
         TraceLineI( "nColumnSize = ", nColumnSize );
         TraceLineI( "nDecDigits  = ", nDecDigits );
         TraceLineI( "nLth        = ", nLth );
      }

      if ( !RC_SUCCESSFUL( nRC ) )
         return( zCALL_ERROR );

   } // for...

   return( 0 );

}  /* WriteLongChar */

#elif defined( DUMMY )

zSHORT
WriteLongChar( LPCONNECTION lpConnection,
               LPBOUNDLIST  lpBoundList )
{
   return( 0 );
}

#endif

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnClearDBHandlerError
//
//  PURPOSE:    Clear all dbhandler warnings/errors for the task.
//
//              This operation deletes all instances of DBH_Error in
//              KZMSGQOO.
//              The info is only deleted, if the KZSMGQOO has a DBH_Error
//              Entity.  If not, the operation returns zCALL_ERROR.
//
//  RETURNS:    0           - KZMSGQOO cleared
//              zCALL_ERROR - Error on call
//
/////////////////////////////////////////////////////////////////////////////
zSHORT LOCALOPER
fnClearDBHandlerError( zVIEW lpView )
{
   LPVIEWOD     lpViewOD;
   LPVIEWENTITY lpViewEntity;
   zVIEW        vMsgQNamed;
   zVIEW        vMsgQ;
   zLONG        lTask;
   zSHORT       nRC;

   lTask = SysGetTaskFromView( lpView );

   // Does Named View exist?
   GetViewByName( &vMsgQNamed, "__MSGQ", lpView, zLEVEL_TASK );
   if ( vMsgQNamed == 0 )
      return( 0 );    // nothing need to be done

   // Has Named View the entity DBH_Error in its definition?
   lpViewOD = (LPVIEWOD) MiGetViewEntityForView( vMsgQNamed, 0 );
   for ( lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
         lpViewEntity;
         lpViewEntity = zGETPTR( lpViewEntity->hNextHier ) )
   {
      // Is the entity the DBH_Error?
      if ( zstrcmp( lpViewEntity->szName, "DBH_Error" ) == 0 )
        break;
   }

   // If DBH_Error not exist, we have an old KZMSGQOO.
   if ( lpViewEntity == 0 )
      return( zCALL_ERROR );

   CreateViewFromViewForTask( &vMsgQ, vMsgQNamed, 0 );

   // Determine if task entity instance exists for our task.
   nRC = SetCursorFirstEntityByInteger( vMsgQ, "Task", "Id", lTask, 0 );
   if ( nRC < 0 )
   {
      // Clean up view ... nothing needs to be done.
      DropView( vMsgQ );
      return( 0 );
   }

   // Delete all former error codes from earlier call.
   for ( nRC = SetCursorFirstEntity( vMsgQ, "DBH_Error", 0 );
         nRC >= zCURSOR_SET;
         nRC = DeleteEntity( vMsgQ, "DBH_Error", zREPOS_NEXT ) )
   {
      // Nothing needs to be done here.
   }

   DropView( vMsgQ );

   return( 0 );

} /* fnClearDBHandlerError */

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnSetDBHandlerError
//
//  PURPOSE:    To set a dbhandler warning/error info for the task.
//
//              This operation creates a new instance of DBH_Error in
//              KZMSGQOO.
//              The info is only set, if the KZSMGQOO has a DBH_Error
//              Entity. If not, the operation returns zCALL_ERROR.
//
//  RETURNS:    0           - info wrote to KZMSGQOO
//              zCALL_ERROR - Error on call
//
/////////////////////////////////////////////////////////////////////////////
zSHORT LOCALOPER
fnSetDBHandlerError( zVIEW  lpView,
                     zLONG  lCode,
                     zPCHAR szState,
                     zPCHAR szMsg )
{
   LPVIEWOD     lpViewOD;
   LPVIEWENTITY lpViewEntity;
   zVIEW        vMsgQNamed;
   zVIEW        vMsgQ;
   zLONG        lTask;
   zSHORT       nRC = zCALL_ERROR;

   lTask = SysGetTaskFromView( lpView );

   // Does Named View exist?
   GetViewByName( &vMsgQNamed, "__MSGQ", lpView, zLEVEL_TASK );
   if ( vMsgQNamed == 0 )
   {
      // if not, create it
      if ( ActivateEmptyObjectInstance( &vMsgQNamed, "KZMSGQOO", lpView,
                                        zMULTIPLE ) >= 0 )
      {
         CreateEntity( vMsgQNamed, "Task", zPOS_FIRST );
      }
      else
      {
         // ERROR out of here ... we will not go far without this object!!!
         return( zCALL_ERROR );
      }

      // Give it a global name
      SetNameForView( vMsgQNamed, "__MSGQ", lpView, zLEVEL_TASK );
   }

   // Has Named View the entity DBH_Error in its definition?
   lpViewOD = (LPVIEWOD) MiGetViewEntityForView( vMsgQNamed, 0 );
   for ( lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
         lpViewEntity;
         lpViewEntity = zGETPTR( lpViewEntity->hNextHier ) )
   {
      // is the entity the DBH_Error?
      if ( zstrcmp( lpViewEntity->szName, "DBH_Error" ) == 0 )
         break;
   }

   // if DBH_Error not exist, we have an old KZMSGQOO
   if ( lpViewEntity == 0 )
     return( zCALL_ERROR );

   // Create private copy, cause we change our cursors
   CreateViewFromViewForTask( &vMsgQ, vMsgQNamed, 0 );

   // check, if task entity instance exists for our task
   if ( SetCursorFirstEntityByInteger( vMsgQ, "Task", "Id", lTask, 0 ) < 0 )
   {
      // if not, create it
      CreateEntity( vMsgQ, "Task", zPOS_LAST );
      SetAttributeFromVariable( vMsgQ, "Task", "Id",
                                &lTask, zTYPE_INTEGER, 0, 0, 0 );
      SetAttributeFromVariable( vMsgQ, "Task", "Client",
                                "Zeidon", zTYPE_STRING, 0, 0, 0 );
   }

   // set cursor on our task entity
   if ( SetCursorFirstEntityByInteger( vMsgQ, "Task", "Id", lTask, 0 ) < 0 )
      goto EndOfFunction;

   // if max. entries reached, delete the oldest one
   if ( CountEntitiesForView( vMsgQ, "DBH_Error" ) >= 100L )
   {
      SetCursorFirstEntity( vMsgQ, "DBH_Error", 0 );
      DeleteEntity( vMsgQ, "DBH_Error", zREPOS_FIRST );
   }

   // create new entry
   if ( CreateEntity( vMsgQ, "DBH_Error", zPOS_LAST ) < 0 )
      goto EndOfFunction;

   SetAttributeFromInteger( vMsgQ, "DBH_Error", "Code", lCode );
   SetAttributeFromVariable( vMsgQ, "DBH_Error", "State",
                             szState, zTYPE_STRING, 5, 0, 0 );
   SetAttributeFromVariable( vMsgQ, "DBH_Error", "Msg",
                             szMsg, zTYPE_STRING, 512, 0, 0 );

   // If we get here then everything's ok.
   nRC = 0;

EndOfFunction:
   if ( vMsgQ )
      DropView( vMsgQ );

   return( nRC );

} /* fnSetDBHandlerError */

/////////////////////////////////////////////////////////////////////////////
//
// DBH_MsgProc
//
// The entry point for the db-handler.  All calls go through here.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT OPERATION
DBH_MsgProc( LPTASK       hTask,
             zUSHORT      Message,      // Message indicating function, etc.
             int          Indicators,   // Indicators for function.
             LPVIEWOD     lpViewOD,     // Target/Source object defintion.
             LPVIEWENTITY lpViewEntity, // Target/Source entity.
             zVIEW        lpView,       // Target/Source view.
             zVIEW        lpQualView,   // Qualification view.
             zPVOID       ppvWorkPtr )  // Work pointer.
{
   LPCONNECTION lpConnection;
   zSHORT       nRC;

   // Execute a function according to the message passed.
// TraceLineX( "DBH_MsgProc Message: ", Message );
   if ( Message & DBH_Entity )
   {

#if Timer
      lEntityMessageCount++;
#endif

      nRC = GetWorkObjectView( hTask, lpView, lpViewOD, lpViewEntity,
                               ppvWorkPtr, &lpConnection );
      if ( nRC == zCALL_ERROR )
         goto EndOfFunction;

      if ( Message & DBH_Load )
         nRC = Load( lpViewEntity, lpView, lpViewOD, lpQualView, lpConnection,
                     Indicators );
      else
      if ( Message & DBH_Insert )
         nRC = Insert( lpViewEntity, lpView, lpViewOD, FALSE, lpConnection );
      else
      if ( Message & DBH_InsertRel )
         nRC = InsertRel( lpViewEntity, lpView, lpViewOD, lpConnection );
      else
      if ( Message & DBH_Delete )
      {
         if ( Message & DBH_DeleteAll )
            lpConnection->bDeleteAll = TRUE;

         nRC = Delete( lpViewEntity, lpView, lpViewOD, lpConnection );
      // lpConnection->bDeleteAll = FALSE;  turned off in Delete call
      }
      else
      if ( Message & DBH_DeleteRel )
         nRC = DeleteRel( lpViewEntity, lpView, lpViewOD, lpConnection );
      else
      if ( Message & DBH_Update )
         nRC = Update( lpViewEntity, lpView, lpViewOD, FALSE, lpConnection );
      else
      if ( Message & DBH_UpdateSeq )
         nRC = Update( lpViewEntity, lpView, lpViewOD, TRUE, lpConnection );

      if ( nRC == zCALL_ERROR )
      {
         TraceLineS( "", "" );
         if ( Message & DBH_Load )
            TraceLineS( "Error performing Load for OD: ", lpViewOD->szName );
         else
         if ( Message & DBH_Insert )
            TraceLineS( "Error performing Insert for OD: ", lpViewOD->szName );
         else
         if ( Message & DBH_InsertRel )
            TraceLineS( "Error performing InsertRel for OD: ", lpViewOD->szName );
         else
         if ( Message & DBH_Delete )
            TraceLineS( "Error performing Delete for OD: ", lpViewOD->szName );
         else
         if ( Message & DBH_DeleteRel )
            TraceLineS( "Error performing DeleteRel for OD: ", lpViewOD->szName );
         else
         if ( Message & DBH_Update )
            TraceLineS( "Error performing Update for OD: ", lpViewOD->szName );

         if ( lpViewEntity->hParent )
         {
            LPVIEWENTITY lpParent = zGETPTR( lpViewEntity->hParent );

            TraceLineS( "PARENT:", "" );
            DisplayEntityInstance( lpView, lpParent->szName );
            TraceLineS( "", "" );
            TraceLineS( "CHILD:", "" );
         }

         DisplayEntityInstance( lpView, lpViewEntity->szName );

         if ( lpQualView )
         {
            TraceLineS( "Qualification View:", "" );
            DisplayObjectInstance( lpQualView, 0, 0 );
         }
      }
   }
   else
   if ( Message & DBH_Object )
   {
      nRC = GetWorkObjectView( hTask, lpView, lpViewOD, lpViewEntity,
                               ppvWorkPtr, &lpConnection );
      if ( nRC == zCALL_ERROR )
         goto EndOfFunction;

      if ( Message & DBH_TranBegin )
         nRC = BeginTransaction( Indicators, lpViewOD, lpView, lpQualView,
                                 lpConnection );
      else
      if ( Message & DBH_Commit )
         nRC = CommitTransaction( lpView, Indicators, lpConnection );
      else
      if ( Message & DBH_Rollback )
         nRC = RollbackTransaction( Indicators, lpConnection );
      else
      if ( Message & DBH_NewObject )
      {
         if ( lpConnection->nTraceLevel > 0 )
         {
            TraceLineS( "---------------------------------", "" );
            TraceLineS( "Committing object ", lpViewOD->szName );
            TraceLineS( "---------------------------------", "" );
         }
      }
   }
   else
   if ( Message & DBH_Init )
      nRC = InitDatabase( lpView );
   else
   if ( Message & (DBH_Term | DBH_TaskCloseAll) )
      nRC = CloseDatabase( lpQualView ? lpQualView : lpView, Indicators );

EndOfFunction:

   return( nRC );

} // fnDBH_MsgProc

/*
   See description of callbacks in the generator .h file (kzhsqlgp.h)
*/
zSHORT OPERATION
fnDBH_Callback( zULONG      nCommand,
                zVIEW       lpView,
                LPBOUNDLIST lpBoundList,
                LPDATAFIELD lpDataField,
                zPVOID      pInfo,
                zPCHAR      pchTarget )
{
   LPVIEWENTITY lpViewEntity;
   LPVIEWATTRIB lpViewAttrib;

#if defined( DB2 )

   LPCALLBACKINFO    lpCallbackInfo = (LPCALLBACKINFO) lpBoundList->pvPtr;

#elif defined( ODBC )

   LPCALLBACKINFO    lpCallbackInfo = (LPCALLBACKINFO) lpBoundList->pvPtr;
   LPODBC_OBJECTDATA lpObjectData   = lpCallbackInfo->lpObjectData;

   if ( lpObjectData == 0 )
      lpObjectData = &g_DefaultODBC_Data;

#endif

   if ( lpDataField )
   {
      lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );
      lpViewEntity = zGETPTR( lpViewAttrib->hViewEntity );
   }

   switch ( nCommand )
   {
      // ==========================================================
      case zSQLCALLBACK_INITSELECT:
         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_GETNULLSTRING:

         // If we get here then nobody handled the message so return FALSE.
         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_CHECKNULL:

         // If we get here then nobody handled the message so return FALSE.
         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_CONVERTSTRING:
      {

#if defined( DB2 )

         // We only need to worry about date/times.
         if ( lpViewAttrib->cType == zTYPE_DATETIME )
         {
            zPCHAR pch;
            zCHAR  szDateTime1[ 30 ], szDateTime2[ 30 ];

            // Get date-time from szSource as an unformatted string --
            // yyyymmddhhmmsss.
            strcpy_s( szDateTime1, zsizeof( szDateTime1 ), (zPCHAR) pInfo );

            // Make sure that the DateTime doesn't contain any spaces.
            pch = szDateTime1;
            while ( *pch )
            {
               if ( *pch == ' ' )
                  *pch = '0';

               pch++;
            }

            // Convert DateTime string to a formatted string that ODBC/DB2
            // understands.
            switch ( lpDataField->cFldType )
            {
               case zTYPE_TIME:
                  UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "HH.MI.SS" );
                  break;

               case zTYPE_DATE:
                  UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "YYYY-mm-DD" );

                  break;

               default:
                  UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "YYYY-mm-DD-HH.MI.SS.999" );
            }

            // Date string must start with a quote.
            *pchTarget++ = '\'';

            // Copy formatted date-time string to szTarget and terminate
            // with a quote.
            strcpy_s( pchTarget, szDateTime2 );
            strcat_s( pchTarget, "'" );

            return( TRUE ); // Return code indicating we handled it ok.

         } // if...

#elif defined( ODBC )

         zBOOL bAddEscapeSequence;
         zCHAR szEscapeCode[ 3 ];

         // We only need to worry about date/times.
         if ( lpViewAttrib->cType == zTYPE_DATETIME )
         {
            zPCHAR pch;
            zCHAR  szDateTime1[ 30 ], szDateTime2[ 30 ];

            // Get date-time from szSource as an unformatted string --
            // yyyymmddhhmmsss.
            strcpy_s( szDateTime1, zsizeof( szDateTime1 ), (zPCHAR) pInfo );

            // Make sure that the DateTime doesn't contain any spaces.
            pch = szDateTime1;
            while ( *pch )
            {
               if ( *pch == ' ' )
                  *pch = '0';

               pch++;
            }

            bAddEscapeSequence = FALSE;

            // Convert DateTime string to a formatted string that ODBC/DB2
            // understands.
            switch ( lpDataField->cFldType )
            {
               case zTYPE_TIME:
                  if ( lpObjectData->bStoreTimestampAsString )
                     UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "HHMISS" );
                  else
                  {
                     bAddEscapeSequence = TRUE;
                     strcpy_s( szEscapeCode, zsizeof( szEscapeCode ), "t" );
                     UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "HH:MI:SS" );
                  }

                  break;

               case zTYPE_DATE:
#if 0  // Dates are always stored as date/time columns.
                  if ( lpObjectData->bStoreTimestampAsString )
                     UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "YYYYmmDD" );
                  else
#endif
                  {
                     bAddEscapeSequence = TRUE;
                     strcpy_s( szEscapeCode, zsizeof( szEscapeCode ), "d" );
                     UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "YYYY-mm-DD" );
                  }

                  break;

               case zTYPE_DATETIME:
                  if ( lpObjectData->bStoreTimestampAsString == FALSE )
                  {
                     bAddEscapeSequence = TRUE;
                     strcpy_s( szEscapeCode, zsizeof( szEscapeCode ), "ts" );
                  }

                  // The precision of timestamps has been given to us.  Format
                  // the timestamp according to the precision.

                  if ( lpObjectData->nTimestampPrecision == 0 )
                  {
                     if ( lpObjectData->bStoreTimestampAsString )
                        UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "YYYYmmDDHHMISS" );
                     else
                        UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, "YYYY-mm-DD HH:MI:SS" );
                  }
                  else
                  {
                     zPCHAR pchFormat;
                     zSHORT idx;

                     if ( lpObjectData->bStoreTimestampAsString )
                     {
                        idx = 14; // Index of first '9' in szFormat.
                        pchFormat = "YYYYmmDDHHMISS999999999999999";
                     }
                     else
                     {
                        idx = 20; // Index of first '9' in szFormat.
                        pchFormat = "YYYY-mm-DD HH:MI:SS.999999999999999";
                     }

                     // We're being a little tricky here but all we're doing is
                     // making sure that the precision in szFormat matches
                     // nTimestampPrecision.

                     // First turn one of the 9's into a null-terminator.
                     pchFormat[ idx + lpObjectData->nTimestampPrecision ] = 0;

                     UfFormatDateTime( szDateTime2, zsizeof( szDateTime2 ), szDateTime1, pchFormat );

                     // Now change the null-terminator back to a 9.
                     pchFormat[ idx + lpObjectData->nTimestampPrecision ] = '9';
                  }

                  break;

            } // switch ( lpDataField->cFldType )...

            if ( bAddEscapeSequence )
            {
               // Add escape sequence.
               *pchTarget++ = '{';

               strcpy_s( pchTarget, zsizeof( szEscapeCode ), szEscapeCode ); // this should always be safe even though we don't know the size of pchTarget at this point
               pchTarget += zstrlen( szEscapeCode );

               *pchTarget++ = ' ';
            }

            // Date string must start with a quote.
            *pchTarget++ = '\'';

            // Copy formatted date-time string to szTarget and terminate with a quote.
            strcpy_s( pchTarget, zsizeof( szDateTime2 ), szDateTime2 ); // this should always be safe even though we don't know the size of pchTarget at this point
            strcat_s( pchTarget, 2, "'" );  // this should always be safe even though we don't know the size of pchTarget at this point

            if ( bAddEscapeSequence )
            {
               // Terminate escape sequence.
               pchTarget = pchTarget + zstrlen( pchTarget );
               *pchTarget++ = ' ';
               *pchTarget++ = '}';
               *pchTarget++ = 0;
            }

            return( TRUE ); // Return code indicating we handled it ok.

         } // if...

#endif
         // If we get here then nobody handled the message so return FALSE.
         return( FALSE );
      }

      // ==========================================================
      case zSQLCALLBACK_GETATTRVALUE:

#if defined( DB2 ) || defined( ODBC )

         // We only need to worry about blobs/varchars.
         if ( (g_bHoldStmtHandles &&
               lpCallbackInfo->cBuildFunction == BUILD_SELECT) ||
              lpDataField->cFldType == zTYPE_BLOB ||
              lpDataField->cFldType == 'V' )
         {
            // For LONG VARCHAR variables, create a bind variable.
            SqlAddBoundAttr( lpBoundList, lpDataField, lpView, 0, 0 );
            strcat_s( pchTarget, 2, "?" );  // this should always be safe even though we don't know the size of pchTarget at this point

            return( TRUE ); // Return code indicating we handled it ok.
         }

#endif
         // If we get here then nobody handled the message so return FALSE.
         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_GETCOLUMNNAME:

#if defined ( DB2 )

      {
         LPVIEWATTRIB lpViewAttrib;

         // If pInfo is 0 then we are getting the column name for a
         // SELECT statement.  We can use the default processing for non
         // SELECT statements.
         if ( pInfo )
            return( FALSE );

         lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );

         // For the 'COUNT' command we have to insert 'DISTINCT'.
         if ( lpViewAttrib->cDB_Oper == 'C' )
            strcat_s( pchTarget, " DISTINCT " );

         // We'll return FALSE even if we've done something here because we
         // want the dbhandler to tack on the column name.
         return( FALSE );
      }

#endif

         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_USEINTO:
         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_GETINTONAME:
         return( FALSE );

      case zSQLCALLBACK_GETCOLLISTPOS:
#ifdef ODBC
         if ( lpDataField->cFldType == zTYPE_BLOB ||
              lpDataField->cFldType == 'V' )
            return( TRUE );
         else
            return( FALSE );
#else
         return( FALSE );
#endif

   } // switch ( nCommand )...

   // If we get here then we didn't handle the request so return FALSE.
   return( FALSE );

} // fnDBH_Callback


#define STR_LEN 255

zSHORT OPERATION
RetrieveSchema( zVIEW  vDTE, zPVIEW pvDB )
{
   ConnectionRecord cr = { 0 };
   LPCONNECTION lpConnection = &cr;

   zVIEW  vDB;
   zCHAR  szUserID[ 50 ];
   zCHAR  szPassword[ 50 ];
   zPCHAR pchPtr = 0;
   zPCHAR pchDBName;

   zCHAR  szTableName[ STR_LEN + 1 ];
   zCHAR  szColumnName[ STR_LEN + 1 ];
   zCHAR  szIndexName[ STR_LEN + 1 ];

#if defined( DB2 ) || defined( ODBC )
   zCHAR       szDataTypeName[ STR_LEN + 1 ];
   zCHAR       szIndexQual[ STR_LEN + 1 ];
   SQLINTEGER  cbTableNameLth, cbColumnNameLth, cbIndexNameLth, cbCardinality;
   SQLINTEGER  iColLth;
   SQLINTEGER  iCardinality;
   SQLSMALLINT sDataType;
   SQLSMALLINT sNullable;
#else
   zLONG       iColLth = 0;
#endif
   zSHORT nRC = 0;

// lpConnection->nTraceLevel = 1;
   lpConnection->lpAppView = vDTE;

   if ( *pvDB == 0 )
   {
      ActivateEmptyObjectInstance( pvDB, "TZTENVRO", vDTE, zSINGLE );
      CreateEntity( *pvDB, "TE_DB_Environ", zPOS_LAST );
      CreateEntity( *pvDB, "TE_DBMS_Source", zPOS_LAST );
   }

   vDB = *pvDB;  // Just to make things easier.

   // Get the database name.
   GetAddrForAttribute( &pchDBName, vDTE, "TE_DBMS_Source", "Name" );

   SysGetDB_UserID( vDTE, szUserID, zsizeof( szUserID ), szPassword, zsizeof( szPassword ) );

   //==============================================================
   // Open database.
   //==============================================================

#if defined( DB2 ) || defined( ODBC )

   nRC = SQLAllocEnv( &lpConnection->henv );
   SQL_RC( "SQLAllocEnv", nRC, 0, 0, 2 );
   if ( nRC != SQL_SUCCESS )
      return( zCALL_ERROR );

   nRC = SQLAllocConnect( lpConnection->henv, &lpConnection->hdbc );
   SQL_RC( "SQLAllocConnect", nRC, 0, 0, 2 );
   if ( nRC != SQL_SUCCESS )
      return( zCALL_ERROR );

   nRC = SQLConnect( lpConnection->hdbc, pchDBName, SQL_NTS,
                     szUserID, SQL_NTS, szPassword, SQL_NTS );
   SQL_RC( "SQLConnect", nRC, "Database = ", pchDBName, 1 );
   if ( !RC_SUCCESSFUL( nRC ) )
   {
      zCHAR szText[ 200 ];

      sprintf_s( szText, zsizeof( szText ), "Error connecting to DB %s", pchDBName );
      MessageSend( lpConnection->lpAppView, "KZH0102", "ODBC DBH Error",
                   szText, zMSGQ_SYSTEM_ERROR, 0 );

      SQLFreeHandle( SQL_HANDLE_DBC, (SQLHANDLE) lpConnection->hdbc );
      lpConnection->hdbc = 0;
      return( zCALL_ERROR );
   }

#if defined( DB2 )

   nRC = SQLAllocStmt( lpConnection->hdbc, &lpConnection->hstmt );
   SQL_RC( "SQLAllocStmt", nRC, "Allocate HSTMT", 0, 2 );
   if ( nRC != SQL_SUCCESS )
      return( zCALL_ERROR );

#else

   nRC = SQLSetConnectAttr( lpConnection->hdbc, SQL_ATTR_AUTOCOMMIT,
                            SQL_AUTOCOMMIT_OFF, 0 );
   SQL_RC( "SQLSetConnectAttr", nRC, "Turning AutoCommit off", 0, 2 );

   nRC = SQLAllocHandle( SQL_HANDLE_STMT, lpConnection->hdbc,
                         &lpConnection->hstmt );
   SQL_RC( "SQLAllocHandle", nRC, "Allocate HSTMT", 0, 2 );
   if ( nRC != SQL_SUCCESS )
      return( zCALL_ERROR );

#endif

   nRC = SQLTables( lpConnection->hstmt, 0, 0, 0, 0, 0, 0,
                    "TABLE", SQL_NTS );
   SQL_RC( "SQLTables", nRC, "Get table list", 0, 1 );

   SQLBindCol( lpConnection->hstmt, 3, SQL_C_CHAR, szTableName,
               STR_LEN, &cbTableNameLth );

#endif

   // Load tables.
   while ( TRUE )
   {
#if defined( DB2 ) || defined( ODBC )

      nRC = SQLFetch( lpConnection->hstmt );
      SQL_RC( "SQLFetch", nRC, "Fetch table name", 0, 1 );
      if ( !RC_SUCCESSFUL( nRC ) )
         break;

      // We have to ignore some system tables.
      if ( zstrcmpi( szTableName, "dtproperties" ) == 0 )
         continue;

#endif

      CreateEntity( vDB, "TE_TablRec", zPOS_LAST );
      SetAttributeFromString( vDB, "TE_TablRec", "Name", szTableName );

   } // Load tables...

   // Clean up after getting tables.
#if defined( DB2 ) || defined( ODBC )

   nRC = SQLCloseCursor( lpConnection->hstmt );
   SQL_RC( "SQLCloseCursor", nRC, 0, 0, 2 );

#endif

   // Load columns.
   for ( nRC = SetCursorFirstEntity( vDB, "TE_TablRec", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vDB, "TE_TablRec", 0 ) )
   {
      GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDB, "TE_TablRec", "Name" );

#if defined( DB2 ) || defined( ODBC )
      nRC = SQLColumns( lpConnection->hstmt, 0, 0, 0, 0, szTableName,
                        SQL_NTS, 0, 0 );
      SQL_RC( "SQLColumns", nRC, "Get column list", 0, 1 );

      SQLBindCol( lpConnection->hstmt, 4, SQL_C_CHAR,
                  szColumnName, STR_LEN, &cbColumnNameLth );
      SQLBindCol( lpConnection->hstmt, 5, SQL_C_SSHORT, &sDataType, 0, 0 );
      SQLBindCol( lpConnection->hstmt, 6, SQL_C_CHAR,
                  szDataTypeName, STR_LEN, &cbColumnNameLth );
      SQLBindCol( lpConnection->hstmt, 7, SQL_C_SLONG, &iColLth, 0, 0 );
      SQLBindCol( lpConnection->hstmt, 11, SQL_C_SSHORT, &sNullable, 0, 0 );
#endif

      while ( TRUE )
      {
         zCHAR szDataType[ 20 ];

#if defined( DB2 ) || defined( ODBC )

         nRC = SQLFetch( lpConnection->hstmt );
         SQL_RC( "SQLFetch", nRC, "Fetch column name", 0, 1 );
         if ( !RC_SUCCESSFUL( nRC ) )
            break;

         switch ( sDataType )
         {
            case SQL_CHAR:
               szDataType[ 0 ] = zTYPE_FIXEDCHAR;
               break;

            case SQL_VARCHAR:
               szDataType[ 0 ] = zTYPE_STRING;
               break;

            case SQL_LONGVARCHAR:
            case -9:   // No idea what it is, but it's returned by SqlServer.
            case -10:  // Returned by SqlServer, says its an ntext.
               szDataType[ 0 ] = 'V';
               break;

            case SQL_INTEGER:
            case SQL_SMALLINT:
               szDataType[ 0 ] = zTYPE_INTEGER;
               iColLth = 4;
               break;

            case -6:  // SQL_TINYINT
               szDataType[ 0 ] = zTYPE_INTEGER;
               iColLth = 1;
               break;

            case -5:  // SQL_BIGINT
               szDataType[ 0 ] = zTYPE_INTEGER;
               iColLth = 8;
               break;

            case SQL_REAL:
            case SQL_FLOAT:
            case SQL_DOUBLE:
               szDataType[ 0 ] = zTYPE_DECIMAL;
               iColLth = 40;
               break;

            case SQL_TYPE_DATE:
            case SQL_DATE:
               szDataType[ 0 ] = zTYPE_DATE;
               iColLth = 4;
               break;

            case SQL_TYPE_TIME:
            case SQL_TIME:
               szDataType[ 0 ] = zTYPE_TIME;
               iColLth = 4;
               break;

            case SQL_TYPE_TIMESTAMP:
            case SQL_TIMESTAMP:
               szDataType[ 0 ] = zTYPE_DATETIME;
               iColLth = 4;
               break;

            case SQL_BINARY:
            case SQL_VARBINARY:
            case SQL_LONGVARBINARY:
               szDataType[ 0 ] = zTYPE_BLOB;
               break;

            default:
               TraceLineS( "Unknown datatype = ", szDataTypeName );
               TraceLineI( "Datatype number = ", sDataType );
               TraceLineS( "Table Name = ", szTableName );
               TraceLineS( "ColumnName = ", szColumnName );
               SysMessageBox( vDTE, "DGC", "Unhandled data type", 1 );
               break;
         }

         // Add null terminator.
         szDataType[ 1 ] = 0;

#endif

      CreateEntity( vDB, "TE_FieldDataRel", zPOS_LAST );
      SetAttributeFromString( vDB, "TE_FieldDataRel", "Name",
                              szColumnName );
      SetAttributeFromInteger( vDB, "TE_FieldDataRel", "Length",
                               iColLth );
      SetAttributeFromString( vDB, "TE_FieldDataRel", "DataType",
                              szDataType );
   }

#if defined( DB2 ) || defined( ODBC )

      nRC = SQLCloseCursor( lpConnection->hstmt );
      SQL_RC( "SQLCloseCursor", nRC, 0, 0, 2 );

#endif

   } // For each Table

   // Load Indexes.
   for ( nRC = SetCursorFirstEntity( vDB, "TE_TablRec", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vDB, "TE_TablRec", 0 ) )
   {
      GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDB, "TE_TablRec", "Name" );

#if defined( DB2 ) || defined( ODBC )
      nRC = SQLStatistics( lpConnection->hstmt, 0, 0, 0, 0, szTableName,
                        SQL_NTS, SQL_INDEX_ALL, 0 );
      SQL_RC( "SQLStatistics", nRC, "Get index list", 0, 1 );

      SQLBindCol( lpConnection->hstmt, 5, SQL_C_CHAR, szIndexQual,
                  STR_LEN, &cbTableNameLth );
      SQLBindCol( lpConnection->hstmt, 6, SQL_C_CHAR, szIndexName,
                  STR_LEN, &cbIndexNameLth );
      SQLBindCol( lpConnection->hstmt, 9, SQL_C_CHAR, szColumnName,
                  STR_LEN, &cbColumnNameLth );
      SQLBindCol( lpConnection->hstmt, 11, SQL_C_SLONG, &iCardinality,
                  0, &cbCardinality );

#endif

      while ( TRUE )
      {
#if defined( DB2 ) || defined( ODBC )

         nRC = SQLFetch( lpConnection->hstmt );
         SQL_RC( "SQLFetch", nRC, "Fetch column name", 0, 1 );
         if ( !RC_SUCCESSFUL( nRC ) )
            break;

         // If index name is null, then the current row is a "stat" table
         // so we'll ignore it.
         if ( cbIndexNameLth == SQL_NULL_DATA )
            continue;
#endif

         // Does the index already exist?
         if ( SetCursorFirstEntityByString( vDB, "TE_TablRecKey", "IndexName",
                                            szIndexName, 0 ) < zCURSOR_SET )
         {
            CreateEntity( vDB, "TE_TablRecKey", zPOS_LAST );
            SetAttributeFromString( vDB, "TE_TablRecKey", "IndexName", szIndexName );
            SetAttributeFromString( vDB, "TE_TablRecKey", "Name",
                                    "Retrieved From DB" );
         }

         // Find the column in the column list.
         if ( SetCursorFirstEntityByString( vDB, "TE_FieldDataRel", "Name",
                                            szColumnName, 0 ) >= zCURSOR_SET )
         {
            IncludeSubobjectFromSubobject( vDB, "TE_FieldDataRelKey",
                                           vDB, "TE_FieldDataRel", zPOS_LAST );
         }
      }

#if defined( DB2 ) || defined( ODBC )

      nRC = SQLCloseCursor( lpConnection->hstmt );
      SQL_RC( "SQLCloseCursor", nRC, 0, 0, 2 );

#endif

   } // For each Table

#if defined( DB2 ) || defined( ODBC )

   SQLFreeHandle( SQL_HANDLE_STMT, (SQLHANDLE) lpConnection->hstmt );
   SQLFreeHandle( SQL_HANDLE_DBC,  (SQLHANDLE) lpConnection->hdbc );
   SQLFreeHandle( SQL_HANDLE_ENV,  (SQLHANDLE) lpConnection->henv);

#endif

   return( 0 );
}
