//
// MODULE NAME:  KZOENETA  -  Object services Network Handling Operations
// DESCRIPTION:  This is the source file which contains Object services
//               operations for all network functions.  These functions make
//               calls to the OS and network specific Network Handler.
// OPERATIONS:   All OPERATIONS which do network handling (eg Net...)
// **********************************************************************
// * Copyright (c) 1993-2016 QuinSoft, Inc. All rights reserved. *
// * Confidential and Proprietary material subject to license -         *
// * do not reproduce or disclose. This material is an unpublished      *
// * work and is considered a trade secret belonging to the             *
// * copyright holder.                                                  *
// **********************************************************************
//  AUTHOR:  D.G. Christensen
//  DATE:    3/22/96
//  API:     NONE
//  ENVIRONMENT: ANY
//

/*
CHANGE LOG

2002.12.04  DGC
   Added code for Linux support (defines of VA_ARG_... ).

2002.02.11 DGC  10b
   Small change in connection re-try code.

2001.02.14 DGC  10b
   Implemented HH's change for parent/thread tasks.

2000.08.18 DGC  10b
   Backed out Hartmut's changes.

2000.07.18  HH
   Hold Connection implemented.

2000.06.15  DGC  Z2000
   Fixed bug reported by Phil.  Attribute flags were not being reset during
   merge of OI returned from the server with the original OI.  They are now
   being copied.

2000.06.15  DGC  Z2000
   Changed a message.

2000.04.19  RG   Z2000
    Fix in fnSendMessageObject: remove ')' at line 651

2000.04.13  DGC  Z10
   Changed MSGQ logic to name the message queue at the task level instead of
   the application level.

2000.03.15  US  all
   Fixed bug reported by Phil.  fnSetLinkBuffer( ) wasn't correctly building
   the relink buffer.  Added a break.

2000.03.15  US  all
   seperated a definition of an zDECIMAL and the assignment with
   a va_arg( ) function in two seperate lines due to a compiler
   error of the AS400 compiler

2000.01.06  DGC 10b
   We no longer trace out the LinkBuffer unless network tracing is 1.

2000.01.26  HH 10a
   Host systems: use longjmp to solve the "out of memory" problem.
1999.11.29  DGC
   Added code to fnAllocDataspace( ) to help find leaks.

1999.10.19  HH  10a
   Correct "Send the control value for the view", in NetCommitOI.
   According to the network handler interface, messages must
   be written and read synchronously.

1999.10.12  HH  10a
   Correct some casts to make module compile under MVS.

1999.05.17  DGC  10a
   Fixed bug in fnDeleteMsgObj( ) that was deleting the wrong entity.

1999.04.21  DGC  10a  ApplA
   Lot's of changes dealing with ApplA stuff.

1999.04.14  DGC  10a
   Added tracing of local host name during startup.

1999.04.07  DGC  10a
   Set flag so we don't show messages during SysGetProc( ) calls.

1999.03.26  DGC
   Fixed bug reported by TMV--don't call activate constraints while activating
   off the network.

1999.03.11  DGC
   Fixed pessimistic locking problems that occurred when using networking.

1999.03.11  DGC
   On my birthday I fixed a bug that had the server always dropping pessimistic
   locks when the server OI was dropped.

1999.02.18  DGC
   Started making changes to reflect changes in ApplA.

1999.01.08  DGC
   Fixed problem in calling a remote transformation--we weren't using the
   right subtask.

-----------------------------------------------------------------------------

Some notes for the future:

   o  To make everything a little faster, we could store some of the view
      pointers in the LPTASK structure.  For example, the LAD and ClientGroup
      views could be stored in the task structure.  This would mean that we
      wouldn't have to retrieve the view using GetViewByName.
*/

#include "kzoephdr.h"
#include <stdarg.h>
#include <ctype.h>
#include <setjmp.h>

#if defined( _WINDOWS ) && defined( DEBUG )
#pragma optimize( "", off )                  // Turn off all optimizations.
#endif

#define DROPSUBTASK( v )                                    \
{                                                           \
   LPSUBTASK lpDropSubtask = zGETPTR( (v)->hSubtask );      \
                                                            \
   fnDropSubtask( zGETPTR( lpDropSubtask->hTask ),          \
                  lpDropSubtask, 0 );                       \
}

//#define CREATESUBTASK( v, s ) SfCreateSubtask( (v), 0, (s) )
//#define CREATESUBTASK( v, s ) SfCreateSubtask( (v), (AnchorBlock->hMainTask->hFirstView), (s) )

#define zSENDFILE_BUFFER            5000
#define zAPPL_NAME_LTH              33    // Length + null-terminator.

#define L_TRACE_SWITCH_MSG           6
#define L_TIMESTAMP_MSG             18

#define zTYPE_TRAN                  "T"
#define zTYPE_GOPER                 "G"

// Error messages returned from a Zeidon server.
#define zNETERR_INVALIDAPP           1
#define zNETERR_INVALIDOD            2
#define zNETERR_OUTOFMEMORY          3
#define zNETERR_BADACTIVATE          4
#define zNETERR_BADMESSAGE           5
#define zNETERR_SENDOI               6
#define zNETERR_RECEIVEOI            7
#define zNETERR_NOEXECUTABLE         8
#define zNETERR_NOOPER               9
#define zNETERR_NOAUTHORITY         10

#ifndef VA_ARG_CHAR
   #define VA_ARG_CHAR               char
#endif

#ifndef VA_ARG_SHORT
   #define VA_ARG_SHORT              short
#endif

#define DEFAULT_NETWORK              "*default*"

//////////// structure prototypes ///////////////

typedef zLONG (POPERATION LPFN_CALLTRAN)( zPCHAR, zVIEW, zPVIEW[] );
typedef zLONG (POPERATION LPFN_CALLOPER)( zVIEW, zPVIEW[] );

typedef struct DataStrPacketStruct zDataStrPacket;
typedef struct DataStrPacketStruct *LPSTRPACKET;
struct DataStrPacketStruct
{
   zCHAR  cPacketType;
   zCHAR  szPacketData[ 9 ];
};

#define zCURRENT_PROTOCOL_VERSION "1b"

// Used by NetActivate...
typedef struct ActivatePacketStruct zActivatePacket;
typedef struct ActivatePacketStruct *LPACTPACKET;
struct ActivatePacketStruct
{
   zCHAR  szVersion[ 3 ];              // Version of protocol.
   zCHAR  szObjectDef[ 32 ];           // Name of OD we want to activate.
   zCHAR  szControl[ 9 ];              // Activate flags.
   zCHAR  cUseQualification;           // 'Y' if there is a qualification obj.
   zCHAR  szAppName[ zAPPL_NAME_LTH ]; // Name of application requesting OI.
   zCHAR  szUserName[ 33 ];            // User name.
   zCHAR  szPassword[ 33 ];            // Password.
   zCHAR  szFileNameLth[ 3 ];          // Lth of fname for NetActivateOI_FromF.
};

// Used by NetCommit...
typedef struct CommitPacketStruct zCommitPacket;
typedef struct CommitPacketStruct *LPCOMMITPACKET;
struct CommitPacketStruct
{
   zCHAR  szVersion[ 3 ];              // Version of protocol.
   zCHAR  szObjectDef[ 32 ];           // Name of OD we want to commit (if only 1).
   zCHAR  szAppName[ zAPPL_NAME_LTH ]; // Name of application requesting OI.
   zCHAR  szControl[ 9 ];              // Commit flags for NetCommitOI_ToFile.
   zCHAR  szUserName[ 33 ];            // User name.
   zCHAR  szPassword[ 33 ];            // Password.
   zCHAR  szViewCount[ 3 ];            // Number of views to commit.
   zCHAR  szObjectNameLth[ 4 ];        // Lth of object names.
   zCHAR  szFileNameLth[ 4 ];          // Lth of f'name for NetCommitOI_ToFile.
   zCHAR  szLinkBufferLth[ 4 ];        // Lth of link info buffer.
};

// Used by SfActivate/Commit to/from stream.
typedef struct ActivateStruct ActivateRecord;
typedef struct ActivateStruct *LPACTIVATE;
struct ActivateStruct
{
   LPNETWORK lpNetwork;
   zPVOID    *ppvConn;
   zLONG     lLineCount;
};

// Used by NetSendFile
typedef struct SendFileStruct SendFileRecord;
typedef struct SendFileStruct *LPSENDFILE;
struct SendFileStruct
{
   zCHAR  szAppName[ zAPPL_NAME_LTH ]; // Name of application requesting OI.
   zCHAR  szFileNameLth[ 3 ];          // Lth of filename.
   zCHAR  bBinaryFile;                 // 'Y' if file is a binary file.
};

//////////// Global variables ///////////////
// Use '_' to avoid conflicts with names with the same spelling but different
// capitalization e.g. szlAPPLICATION.
zCHAR szlApplA[]                 = "ApplA";
zCHAR szlAddress[]               = "Address";
zCHAR _szlApplication[]          = "Application";
zCHAR szlArgument[]              = "Argument";
zCHAR szlDataServer[]            = "DataServer";
zCHAR szlDefaultServer[]         = "DefaultServer";
zCHAR szlLOD[]                   = "LOD";
zCHAR szlNetworkError[]          = "Zeidon Network Error";
zCHAR szlOverrideLOD[]           = "OverrideLOD";
zCHAR szlOverrideLOD_Server[]    = "OverrideLOD_Server";
zCHAR szlOverrideOper[]          = "OverrideOper";
zCHAR szlOverrideOperServer[]    = "OverrideOperServer";
zCHAR szlFalse[]                 = "F";         // "F" for FALSE
zCHAR szlTrue[]                  = "T";         // "T" for TRUE
zCHAR szlTranDataServer[]        = "TranDataServer";
zCHAR szlTransformation[]        = "Transformation";
zCHAR szlTranUserGroup[]         = "TranUserGroup";
zCHAR szlUserGroup[]             = "UserGroup";

/* jump buffer for emergency exit
 */
jmp_buf jbEmergencyExit;

//////////// Function prototypes ///////////////

zSHORT LOCALOPER fnProcessActivateOI( zVIEW lpTaskView, LPNETWORK lpNetwork, zPVOID * ppvConn );
zSHORT LOCALOPER fnProcessCommitOI( zVIEW lpTaskView, LPNETWORK lpNetwork, zPVOID * ppvConn );
zSHORT LOCALOPER fnProcessActivateOI_FromFile( LPNETWORK lpNetwork, zPVOID * ppvConn );
zSHORT LOCALOPER fnProcessCommitOI_ToFile( LPNETWORK lpNetwork, zPVOID * ppvConn );
zSHORT LOCALOPER fnProcessOperation( zVIEW lpTaskView, LPNETWORK lpNetwork, zPVOID * ppvConn );
zSHORT LOCALOPER fnProcessSendFile( zVIEW lpTaskView, LPNETWORK lpNetwork, zPVOID * ppvConn );
zSHORT LOCALOPER fnProcessTraceSwitches( LPNETWORK lpNetwork, zPVOID *ppvConn, LPTASK lpTask );
zSHORT LOCALOPER fnProcessTimestamp( LPNETWORK lpNetwork, zPVOID *ppvConn, LPTASK lpTask );

zSHORT LOCALOPER fnSendOI( zPVOID      *ppvConn,
                           LPNETWORK   lpNetwork,
                           zVIEW       vOI,
                           zLONG       lControl );

zSHORT OPERATION
fnSendOI_Data( zVIEW   lpTaskView,
               zPVOID  lpvData,
               zPCHAR  pchBuffer,
               zULONG  uLth,
               zCHAR   cDataType );

zSHORT LOCALOPER fnReceiveOI( zPVOID      *ppvConn,
                              LPNETWORK   lpNetwork,
                              zPVIEW      pvOI,
                              zVIEW       vSubtask,
                              zPCHAR      pchObjectDef,
                              zLONG       lControl );

zSHORT OPERATION
fnReadDataFromNet( zVIEW   lpView,
                   zPVOID  pvData,
                   zPPCHAR ppchReturnBuffer,
                   zULONG  uLth,
                   zSHORT  nErrorNum );

zSHORT TestMsgObjDef ( zVIEW vMsg);

zSHORT LOCALOPER
fnSendHeaderPacket( LPNETWORK lpNetwork,
                    zPVOID    *ppvConn,
                    zCHAR     cPacketType,
                    zPCHAR    szAppName );

/////////////////////////////////////////////////////////////////////////////

LPNETWORK LOCALOPER
fnFindNetwork( LPTASK lpTask,
               zPCHAR pchNetworkName,
               zBOOL  bShowError )
{
   LPNETWORK lpNetwork;

   zLONG  lProcessID   = SysGetProcessID( 0 );

   zLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   // Find the network pointer that matches the network name.
   for ( lpNetwork = zGETPTR( AnchorBlock->hFirstNetwork );
         lpNetwork;
         lpNetwork = zGETPTR( lpNetwork->hNextNetwork ) )
   {
      if ( lpNetwork->lProcessID != lProcessID )
         continue;

      if ( zstrcmp( lpNetwork->szNetworkName, pchNetworkName ) != 0 )
         continue;

      // If we get here we found the network we are looking for.
      break;
   }

   zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   if ( lpNetwork == 0 && bShowError )
   {
      zCHAR szMsg[ 200 ];

      sprintf_s( szMsg, zsizeof( szMsg ), "Cannot find network '%s'", pchNetworkName );
      fnSysMessageBox( lpTask, szlNetworkError, szMsg, 1 );
   }

   return( lpNetwork );

} // fnFindNetwork

// Retrieve the App name for a view.  Note that vSubtask does NOT have to be
// a subtask view...any view will do.
zVOID LOCALOPER
fnRetrieveAppName( zVIEW vSubtask, zPCHAR pchAppName )
{
   LPAPP lpApp;

   fnGetApplicationForSubtask( &lpApp, vSubtask );
   if ( lpApp )
      strcpy_s( pchAppName, zsizeof( lpApp->szName ), lpApp->szName );
   else
      pchAppName[ 0 ] = 0;
}

zSHORT
LoadNetworkOperations( LPTASK lpTask, LPNETWORK lpNetwork )
{
   LPLIBRARY hLibrary;
   LPTASK    lpSystemTask = zGETPTR( AnchorBlock->hMainTask );
// zVIEW     vTask = zGETPTR( lpSystemTask->hFirstView );
   zVIEW     vTask = zGETPTR( lpTask->hFirstView );

   if ( vTask == 0 )
      vTask = zGETPTR( lpSystemTask->hFirstView );

   hLibrary = SysLoadLibraryWithErrFlag( vTask, lpNetwork->szFileName, FALSE );
   if ( hLibrary )
   {
      lpNetwork->hServDirLib = hLibrary;
      lpNetwork->lpfnServDirInit = (zLPFN_SERVDIRINIT) SysGetProc( hLibrary, "zServerDirInit" );
      lpNetwork->lpfnServDirClose = (zLPFN_SERVDIRCLOSE) SysGetProc( hLibrary, "zServerDirClose" );
      lpNetwork->lpfnServDirGetAddr = (zLPFN_SERVDIRADDR) SysGetProc( hLibrary, "zServerDirGetAddr" );

      if ( lpNetwork->lpfnServDirInit == 0 || lpNetwork->lpfnServDirClose == 0 || lpNetwork->lpfnServDirGetAddr == 0 )
      {
         zCHAR szMsg[ 200 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Can't find Server Directory functions in '%s'. "
                    "See trace for more.", lpNetwork->szFileName );
         fnSysMessageBox( lpTask, "Zeidon Network Error", szMsg, 1 );
         return( zCALL_ERROR );
      }
   }

   return( 0 );
}

// This function calls the Server Directory DLL to retrieve the server
// address that will handle the activate/commit.
zSHORT LOCALOPER
fnGetApplAddress( LPTASK    lpTask,
                  LPNETWORK lpNetwork,
                  zLONG     lType,
                  zPVOID    pvData,
                  zPCHAR    pchReturnAddress,
                  zLONG     lReturnMaxLth,
                  zPCHAR    pchUserAddress,
                  zLONG     lUserMaxLth )
{
   zCHAR szGroup[ 4096 ];

   // If we have a server directory function, use it.
   if ( lpNetwork->lpfnServDirGetAddr )
   {
      zLONG lProcessID = SysGetProcessID( 0 ); // we didn't do this in 10B
      LPLIBRARY lpLibrary = zGETPTR( lpNetwork->hServDirLib );
      if ( lpLibrary == 0 || lProcessID != lpLibrary->lProcessID )
         LoadNetworkOperations( lpTask, lpNetwork );
   }

   if ( lpNetwork->lpfnServDirGetAddr )
   {
      return( (*lpNetwork->lpfnServDirGetAddr)( lpTask, pchReturnAddress,
                                                &lpNetwork->pvServDirData,
                                                lType, pvData ) );
   }

   // Default is to allow only one attempt.
   if ( lType & zAPPLREQ_RETRY )
      return( zNETWORK_ERROR );

   // If the user supplied an address, then just use that.
   if ( pchUserAddress && pchUserAddress[ 0 ] )
   {
      strcpy_s( pchReturnAddress, lReturnMaxLth, pchUserAddress );
      return( 0 );
   }

   // The default is to read the server address from the INI file
   // using the network name.
   sprintf_s( szGroup, zsizeof( szGroup ), "[%s]", lpNetwork->szNetworkName );
   SysReadZeidonIni( -1, szGroup, "ApplServer", pchReturnAddress, lReturnMaxLth );

   return( 0 );

} // fnGetApplAddress

// Add the connection to the connection list for the current network.  If
// bCallOpen is TRUE, then also call the network handler to open a connection
// to a remote host.  If bCallOpen is FALSE, then it is assumed that the
// connection is already open--probably created during a listen.
zSHORT LOCALOPER
fnAddConnectionToNetwork( LPTASK    lpTask,
                          LPNETWORK lpNetwork,
                          zPCHAR    pchServerAddress,
                          zPVOID    ppvConn,
                          zBOOL     bCallOpen,
                          zLONG     lRequest,
                          zPVOID    pvRequestInfo,
                          zVIEW     vSubtask )
{
   LPNETCONN lpNetConn;
   zPVOID    hNetConn;

   zLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   // Do we need to call the network handler to open a connection?
   if ( bCallOpen )
   {
      zCHAR  szServer[ 256 ];
      zSHORT nRC;

      if ( lpNetwork->nTraceLevel > 0 )
         TraceLineI( "(kzoeneta) ** Opening a connection. Current connections = ", lpNetwork->nConnCount );

      // Try to open connections and keep trying until we get an open conn or an error.
      do
      {
         // Get address of data server.
         nRC = fnGetApplAddress( lpTask, lpNetwork, lRequest, pvRequestInfo,
                                 szServer, zsizeof( szServer ), pchServerAddress, 0 );
         if ( nRC < 0 )
            return( zNETWORK_ERROR );

         // Try to open the connection.  Return codes:
         //    0 - Connection opened.
         //   -1 - Connection failed (timed out).
         //   zCALL_ERROR - unrecoverable error.
         nRC = (*lpNetwork->lpfnOpenConn)( (zPPVOID) &lpNetwork->pNetworkHandle,
                                           (zPPVOID) ppvConn, szServer, vSubtask );
         if ( nRC )
         {
            TraceLineS( "(kzoeneta) ** Open connection failed, hostaddress=",
                        pchServerAddress );

            if ( nRC == zCALL_ERROR )
               return( zNETWORK_ERROR );

            // We will try to open the connection again.  Turn on a flag to
            // tell the appl server logic that we are trying again.
            lRequest |= zAPPLREQ_RETRY;
         }

      } while ( nRC );

   } // if ( bCallOpen )...

   hNetConn = fnAllocDataspace( lpTask->hFirstDataHeader,
                                sizeof( NetConnectionRecord ), TRUE, 0, 0 );
   lpNetConn = zGETPTR( hNetConn );
   lpNetConn->pvConn = ppvConn;

   lpNetConn->hNextNetConn = lpNetwork->hFirstNetConn;
   lpNetwork->nConnCount++;
   lpNetwork->hFirstNetConn = hNetConn;

   zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   return( 0 );

} // fnAddConnectionToNetwork

zSHORT LOCALOPER
fnRemoveConnectionFromNetwork( LPNETWORK lpNetwork,
                               zPVOID    ppvConn,
                               zBOOL     bCallClose )
{
   LPNETCONN lpNetConn;
   LPNETCONN lpPrevNetConn;
   zSHORT    nRC;

   zLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   lpPrevNetConn = 0;
   for ( lpNetConn = zGETPTR( lpNetwork->hFirstNetConn );
         lpNetConn && lpNetConn->pvConn != ppvConn;
         lpNetConn = zGETPTR( lpNetConn->hNextNetConn ) )
   {
      lpPrevNetConn = lpNetConn;
   }

   if ( lpNetConn == 0 )
   {
      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      lpNetConn = zGETPTR( lpNetwork->hFirstNetConn );
      SysMessageBox( 0, szlNetworkError, "Couldn't find lpNetConn!", -1 );
      return( zCALL_ERROR );
   }

   if ( lpPrevNetConn == 0 )
      lpNetwork->hFirstNetConn = lpNetConn->hNextNetConn;
   else
      lpPrevNetConn->hNextNetConn = lpNetConn->hNextNetConn;

   nRC = 0;
   if ( bCallClose )
   {
      if ( (*lpNetwork->lpfnCloseConn)( (zPPVOID) &lpNetwork->pNetworkHandle,
                                        (zPPVOID) ppvConn ) != 0 )
      {
         nRC = zCALL_ERROR;
      }
   }

   fnFreeDataspace( lpNetConn );
   lpNetwork->nConnCount--;

   zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   return( nRC );

} // fnRemoveConnectionFromNetwork

/*
   If network handler contains the BufferEnd function, then call it to flush
   the buffer.  Otherwise call the Send routine with null values to indicate
   that we want to flush the send buffer.
*/
zSHORT LOCALOPER
fnFlushBuffer( LPNETWORK lpNetwork, zPVOID *ppvConn )
{
   if ( lpNetwork->lpfnBufferEnd )
      return(*lpNetwork->lpfnBufferEnd)( &lpNetwork->pNetworkHandle, ppvConn );
   else
      return(*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn, 0, 0, zTYPE_BLOB );
} // fnFlushBuffer


zSHORT LOCALOPER
fnSendDataPacket( LPNETWORK lpNetwork,
                  zPVOID    *ppvConn,
                  zCHAR     cPacketType,
                  zLONG     lPacketData )
{
   zSHORT nRC;

   if ( lpNetwork->lpfnSendPacket )
   {
      // If the network handler supplied us a SendPacket routine then use it.
      nRC = (*lpNetwork->lpfnSendPacket)( &lpNetwork->pNetworkHandle,
                                          ppvConn, cPacketType, lPacketData );
   }
   else
   {
      zDataStrPacket Packet;

      zmemset( &Packet, 0, zSTRPACKETLTH );
      Packet.cPacketType = cPacketType;

      if ( lPacketData < 0 )
      {
         // Convert negative integer to positive and prepend '-' sign.
         Packet.szPacketData[ 0 ] = '-';
         lPacketData = -lPacketData;
         zltox( lPacketData, Packet.szPacketData + 1, zsizeof( Packet.szPacketData ) - 1 );
      }
      else
         zltox( lPacketData, Packet.szPacketData, zsizeof( Packet.szPacketData ) );

      nRC = (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn,
                                    &Packet, zSTRPACKETLTH, zTYPE_STRING );
   }

   if ( cPacketType == zPACKET_ERROR )
      fnFlushBuffer( lpNetwork, ppvConn );

   return( nRC );

} // fnSendDataPacket

zSHORT LOCALOPER
fnReceiveDataPacket( LPNETWORK lpNetwork,
                     zPVOID    *ppvConn,
                     zPCHAR    pcPacketType,
                     zPLONG    plPacketData )
{
   zPVOID   pDummy;

   // Keep looping until we receive a valid packet.
   while ( TRUE )
   {
      if ( lpNetwork->lpfnRecvPacket )
      {
         // If the network handler supplied us a ReceivePacket routine
         // then use it.
         if ( (*lpNetwork->lpfnRecvPacket)( &lpNetwork->pNetworkHandle,
                                            ppvConn, pcPacketType, plPacketData ) != 0 )
         {
            return( zCALL_ERROR );
         }
      }
      else
      {
         LPSTRPACKET lpPacket;

         if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle,
                                         ppvConn, &lpPacket, zSTRPACKETLTH,
                                         zTYPE_STRING ) != 0 )
         {
            return( zCALL_ERROR );
         }

         *pcPacketType = lpPacket->cPacketType;
         *plPacketData = zxtol( lpPacket->szPacketData );
      }

      // If we've retrieved any packet type other than zPACKET_HEADER then
      // return.  If we've received a header packet, then we want to skip it
      // (the header is for some server application).
      if ( *pcPacketType != zPACKET_HEADER )
         return( 0 );

      // Suck up the bytes that make up the header.
      if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                      &pDummy, *plPacketData, zTYPE_STRING ) != 0 )
      {
         return( zCALL_ERROR );
      }

   } // for (;;)...

} // fnReceiveDataPacket

zSHORT LOCALOPER
fnSendHeaderPacket( LPNETWORK lpNetwork,
                    zPVOID    *ppvConn,
                    zCHAR     cPacketType,
                    zPCHAR    pchAppName )
{
   zCHAR         szHeaderStr[ 50 ];
   zLONG         lLth;

   szHeaderStr[ 0 ] = cPacketType;
   strcpy_s( szHeaderStr + 1, zsizeof( szHeaderStr ) - 1, pchAppName );
   lLth = zstrlen( szHeaderStr ) + 1;

   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_HEADER, lLth ) != 0 )
      return( zCALL_ERROR );

   // Send server the header string.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn,
                                szHeaderStr, lLth, zTYPE_STRING ) != 0 )
   {
      return( zCALL_ERROR );
   }

   return( 0 );

} // fnSendHeaderPacket

zVIEW LOCALOPER
fnCreateMsgObj( zVIEW vSubtask )
{
   zVIEW  vMsgQ;
   zLONG  lTask;

   GetViewByName( &vMsgQ, "__MSGQ", vSubtask, zLEVEL_TASK );
   if ( vMsgQ == 0 )
   {
      LPAPP lpApp;

      if ( ActivateEmptyObjectInstance( &vMsgQ, "KZMSGQOO", vSubtask, zMULTIPLE ) < 0 )
      {
         zCHAR szMsg[ 512 ];

         strcpy_s( szMsg, zsizeof( szMsg ), "Cannot load Message Object: " );
         strcat_s( szMsg, zsizeof( szMsg ), "KZMSGQOO" );
         SysMessageBox( vSubtask, "System Error", szMsg, 1 );
         return( 0 );
      }

      SetNameForView( vMsgQ, "__MSGQ", vSubtask, zLEVEL_TASK );
      CreateEntity( vMsgQ, "Task", zPOS_FIRST );
      lTask = SysGetTaskFromView( vSubtask );
      SetAttributeFromInteger( vMsgQ, "Task", "Id", lTask );

      fnGetApplicationForSubtask( &lpApp, vSubtask );
      SetAttributeFromString( vMsgQ, "Task", "Client", lpApp->szName );
   }

   return( vMsgQ );
}

zSHORT LOCALOPER
fnSendMessageObject( LPNETWORK lpNetwork,
                     zPVOID    *ppvConn,
                     zVIEW     vSubtask )
{
   zVIEW  vMessage = 0;
   zVIEW  vMsgQ;
   zSHORT nRC;

   GetViewByName( &vMsgQ, szl__MSGQ, vSubtask, zLEVEL_TASK );
   if ( vMsgQ )
   {
      // The message object contains the messages for all tasks that belong
      // to the same application.  Since we only want to send the messages
      // for the current task, we will create a temp message object to send
      // to the client with just the messages for the current task.  We only
      // care about it if messages (or DBH error messages) exist.

      zSHORT nNewMsgObj = TestMsgObjDef( vMsgQ );

      if ( CheckExistenceOfEntity( vMsgQ, "QMsg" ) == zCURSOR_SET ||
           (nNewMsgObj &&
            CheckExistenceOfEntity( vMsgQ, "DBH_Error" ) == zCURSOR_SET) )
      {
         ActivateOI_FromOI_ForTask( &vMessage, vMsgQ, 0, zSINGLE );

         // Now that we have the messages in a temp OI, delete the messages out
         // of the original OI.
         for ( nRC = SetCursorFirstEntity( vMsgQ, "QMsg", 0 );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntity( vMsgQ, "QMsg", 0 ) )
         {
            DeleteEntity( vMsgQ, "QMsg", zREPOS_NONE );
         }

         if ( nNewMsgObj )
         {
            for ( nRC = SetCursorFirstEntity( vMsgQ, "DBH_Error", 0 );
                  nRC >= zCURSOR_SET;
                  nRC = SetCursorNextEntity( vMsgQ, "DBH_Error", 0 ) )
            {
               DeleteEntity( vMsgQ, "DBH_Error", zREPOS_NONE );
            }
         }
      }
   }

   if ( vMessage )
   {
      // Send flag to indicate we are sending a message object.
      if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn, szlTrue, 1, zTYPE_STRING ) != 0 )
      {
         fnDropView( vMessage );
         return( zCALL_ERROR );
      }

      if ( fnSendOI( ppvConn, lpNetwork, vMessage, 0 ) == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Unable to send message object!", "" );
         fnDropView( vMessage );
         return( zCALL_ERROR );
      }

      // Since we don't need it anymore, drop the temp message OI.
      DropObjectInstance( vMessage );
   }
   else
   {
      // Send flag to indicate that there is no message object.
      if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn,
                                   szlFalse, 1, zTYPE_STRING ) != 0 )
      {
         return( zCALL_ERROR );
      }
   }

   return( 0 );

} // fnSendMessageObject

zSHORT LOCALOPER
fnSendTraceObj( LPNETWORK lpNetwork,
                zPVOID    *ppvConn,
                zVIEW     vSubtask )
{
   zVIEW  vTrace = 0;

   GetViewByName( &vTrace, "KZTRACEO", vSubtask, zLEVEL_TASK );

   if ( vTrace )
   {
      zCHAR szDateTime[ 18 ];

      SysGetDateTime( szDateTime, zsizeof( szDateTime ) ); // DateTime yyyymmddhhmmssttt
      SetAttributeFromVariable( vTrace, "Trace", "TraceEnd",
                                szDateTime, zTYPE_STRING, 17, "DateTime", 0 );

      // Send flag to indicate we are sending a Trace object.
      if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn, szlTrue, 1, zTYPE_STRING ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Unable to send Trace Object Flag", "" );
         return( zCALL_ERROR );
      }

      if ( fnSendOI( ppvConn, lpNetwork, vTrace, 0 ) == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Unable to send Trace object!", "" );
         return( zCALL_ERROR );
      }
   }
   else
   {
      // Send flag to indicate that there is no Trace object.
      if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn, szlFalse, 1, zTYPE_STRING ) != 0 )
      {
         return( zCALL_ERROR );
      }
   }

   return( 0 );

} // fnSendTraceObj

zSHORT LOCALOPER
fnSendMsgAndTraceObj( LPNETWORK lpNetwork,
                     zPVOID     *ppvConn,
                     zVIEW      vSubtask )
{
  zSHORT nRC1, nRC2;
  nRC1 = fnSendMessageObject( lpNetwork, ppvConn, vSubtask );
  nRC2 = fnSendTraceObj( lpNetwork, ppvConn, vSubtask );
  return( nRC1 == 0 ? nRC2 : nRC1 );
}

/*
 * TestMsgObjDef
 * Test if the message Object is of "new" type,
 * that is : it contains the Entity DBH_Error.
 * return 1/0 = Yes/No
 */
zSHORT
TestMsgObjDef( zVIEW vMsg )
{
   LPVIEWOD lpViewOD;
   LPVIEWENTITY lpViewEntity;

   // Does the Object definition contain the entity "DBH_Error"?
   lpViewOD = zGETPTR( vMsg->hViewOD );
   for ( lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
         lpViewEntity;
         lpViewEntity = zGETPTR( lpViewEntity->hNextHier ) )
   {
      // Is the entity the DBH_Error?
      if ( zstrcmp( lpViewEntity->szName, "DBH_Error" ) == 0 )
         return( 1 );
   }

   return( 0 );
}

zSHORT LOCALOPER
fnRetrieveMessageObject( LPNETWORK lpNetwork,
                         zPVOID    *ppvConn,
                         zVIEW     vSubtask )
{
   zPCHAR pchFlag;
   zVIEW  vMessage, vLocalMsg;
   zSHORT nRC;

   // Retrieve the 1-byte flag indicating whether a message object was sent.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &pchFlag, 1, zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve Message flag.", "" );
      return( zCALL_ERROR );
   }

   // If the flag indicates that a message object was sent, then retrieve it.
   if ( pchFlag[ 0 ] == szlTrue[ 0 ] )
   {
      zVIEW vCopy = 0;

      if ( fnReceiveOI( ppvConn, lpNetwork, &vMessage, vSubtask, "kzmsgqoo",
                        zSINGLE ) == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Couldn't retrieve Message object.", "" );
         return( zCALL_ERROR );
      }

      nRC = MessagePresent( vSubtask, 0, vMessage );

      // Copy the DBH_Error entities to the local message Object.
      vLocalMsg = fnCreateMsgObj( vSubtask );
      if ( TestMsgObjDef( vLocalMsg ) != 0 &&
           CreateViewFromViewForTask( &vCopy, vLocalMsg, 0 ) >= 0 )
      {
         zSHORT nc;
         zLONG  lc;

         // Copy over all the DBH_Error entities.
         nc = SetCursorFirstEntity( vMessage, "DBH_Error", 0 );
         while ( nc >= zCURSOR_SET )
         {
            if ( CreateEntity( vCopy, "DBH_Error", zPOS_LAST ) < 0 )
               break;

            SetMatchingAttributesByName( vCopy, "DBH_Error", vMessage, "DBH_Error", zSET_ALL );
            nc = SetCursorNextEntity( vMessage, "DBH_Error", 0 );
         }

         // Make sure that there are not more than 100 DBH_Error's.
         lc = CountEntitiesForView( vCopy, "DBH_Error") - 100;
         if ( lc > 0 )
         {
            SetCursorFirstEntity( vCopy, "DBH_Error", 0 );

            while ( lc > 0 )
            {
               DeleteEntity( vCopy, "DBH_Error", zREPOS_FIRST );
               lc--;
            }
         }

         DropView( vCopy );
      }

      DropObjectInstance( vMessage );
      return( nRC );
   }

   return( 0 );

} // fnRetrieveMessageObject

zSHORT LOCALOPER
fnRetrieveTraceObj( LPNETWORK lpNetwork,
                    zPVOID    *ppvConn,
                    zVIEW     vSubtask )
{
   zPCHAR pchFlag;
   zVIEW  vTrace;
   zSHORT nRC;

   // Retrieve the 1-byte flag indicating whether a trace object was sent.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn, &pchFlag, 1, zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve Trace flag.", "" );
      return( zCALL_ERROR );
   }

   // If the flag indicates that a message object was sent, then retrieve it.
   if ( pchFlag[ 0 ] == szlTrue[ 0 ] )
   {
      if ( fnReceiveOI( ppvConn, lpNetwork, &vTrace, vSubtask, "KZTRACEO",
                        zSINGLE | zACTIVATE_SYSTEM ) == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Couldn't retrieve Trace object.", "" );
         return( zCALL_ERROR );
      }

      nRC = SetCursorFirstEntity ( vTrace, "Line", "Trace" );
      if ( nRC == zCURSOR_SET )
      {
         zCHAR szDTime[ 32 ];
         GetStringFromAttribute( szDTime, zsizeof( szDTime ), vTrace,"Trace", "TraceStart" );
         TraceLineS( "(kzoeneta) ** Start Server Trace: ", szDTime );
         while ( nRC == zCURSOR_SET )
         {
           zCHAR szLine[ 255 ];
           szLine[ 0 ] = 0;
           GetStringFromAttribute( szLine, zsizeof( szLine ), vTrace, "Line", "Line" );
           if ( szLine[ 0 ] )
              TraceLineS( "(kzoeneta) ** Line: ", szLine );

           nRC = SetCursorNextEntity( vTrace, "Line", "Trace" );
         } // while

         GetStringFromAttribute( szDTime, zsizeof( szDTime ), vTrace,"Trace", "TraceEnd" );
         TraceLineS( "(kzoeneta) ** End Server Trace: ", szDTime );
      }

      DropObjectInstance( vTrace );
   }

   return( 0 );

} // fnRetrieveTraceObj

zSHORT LOCALOPER
fnRetrieveMsgAndTraceObj( LPNETWORK lpNetwork,
                          zPVOID    *ppvConn,
                          zVIEW     vSubtask )
{
   zSHORT nRC1, nRC2;
   nRC1 = fnRetrieveMessageObject( lpNetwork, ppvConn, vSubtask );
   nRC2 = fnRetrieveTraceObj( lpNetwork, ppvConn, vSubtask );
   return( nRC1 == 0 ? nRC2 : nRC1 );
}

// Returns TRUE if lpViewOI points to an empty object instance.
zBOOL LOCALOPER
fnEmptyOI( zVIEW lpView )
{
   LPVIEWCSR         lpViewCsr = zGETPTR( lpView->hViewCsr );
   LPVIEWOI          lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   LPENTITYINSTANCE  lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );

   if ( lpEntityInstance == 0 )
      return( TRUE );

   if ( lpEntityInstance->u.nInd.bHidden == FALSE )
      return( FALSE );

   while ( lpEntityInstance->hNextTwin )
   {
      lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );
      if ( lpEntityInstance->u.nInd.bHidden == FALSE )
         break;
   }

   if ( lpEntityInstance->u.nInd.bHidden &&
        (lpEntityInstance->u.nInd.bCreated || lpEntityInstance->u.nInd.bDeleted == FALSE) )

   {
      return( TRUE );
   }

   return( FALSE );

} // fnEmptyOI

//
// Determine Trace switches and send them to the server
// We send a 3 * 2 character message, 6 ascii numbers
// xxyyzz means:
// server core tracelevel = xx
// server DBHandler tracelevel = yy
// server network tracelevel = zz
//
zSHORT LOCALOPER
fnSendTraceSwitches( LPNETWORK lpNetwork,
                     zPVOID    *ppvConn,
                     LPTASK    lpTask )
{
   zCHAR  szTraceSwitch[ L_TRACE_SWITCH_MSG + 1 ];

   sprintf_s( szTraceSwitch, zsizeof( szTraceSwitch ), "%2.2hd", lpNetwork->nServerCoreTraceLevel );
// sprintf_s( szTraceSwitch + 2, zsizeof( szTraceSwitch ) - 2, "%2.2hd", lpTask->nDBHandlerTraceLevel );
   sprintf_s( szTraceSwitch + 2, zsizeof( szTraceSwitch ) - 2, "%2.2hd", lpNetwork->nServerDBHTraceLevel );
   sprintf_s( szTraceSwitch + 4, zsizeof( szTraceSwitch ) - 4, "%2.2hd", lpNetwork->nServerNetTraceLevel );

   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_TRACESWITCH, L_TRACE_SWITCH_MSG  ) != 0 )
   {
      return( zCALL_ERROR );
   }

   // Send server the trace switch message.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn,
                                szTraceSwitch, L_TRACE_SWITCH_MSG, zTYPE_STRING ) != 0 )
   {
      return( zCALL_ERROR );
   }

   return( 0 );

} // fnSendTraceSwitches

zSHORT LOCALOPER
fnSendTimestamp( LPNETWORK lpNetwork,
                 zPVOID    *ppvConn,
                 LPTASK    lpTask )
{
   zCHAR  szTimestamp[ L_TIMESTAMP_MSG + 1 ];

   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_TIMESTAMP, L_TIMESTAMP_MSG  ) != 0 )
   {
      return( zCALL_ERROR );
   }

   // Send server the timestamp message.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, ppvConn,
                                szTimestamp, L_TRACE_SWITCH_MSG, zTYPE_STRING ) != 0 )
   {
      return( zCALL_ERROR );
   }

   return( 0 );

} // fnSendTimestamp

zSHORT LOCALOPER
fnNetActivateOI( LPTASK    lpTask,
                 LPNETWORK lpNetwork,
                 zPCHAR    pchAddress,
                 zPVIEW    pvReturnView,
                 zPCHAR    pchObjName,
                 zVIEW     vSubtask,
                 zVIEW     vQual,
                 zLONG     lControl )
{
   zCHAR   cPacketType;
   zLONG   lPacketData;
   zPVOID  pvConn = 0;
   zCHAR   szAppName[ zZEIDON_NAME_LTH + 1 ];
   zSHORT  nRC = zCALL_ERROR;

   zActivatePacket       ActPacket = { 0 };
   ServDirActivateRecord ActivateInfo = { 0 };

   fnRetrieveAppName( vSubtask, szAppName );

   // Set up info for activate request.
   ActivateInfo.pszNetworkName         = lpNetwork->szNetworkName;
   ActivateInfo.vSubtask               = vSubtask;
   ActivateInfo.lControl               = lControl;
   ActivateInfo.pszViewOD_Name         = pchObjName;
   ActivateInfo.vQualView              = vQual;
   ActivateInfo.pszUserSuppliedAddress = pchAddress;

   // Open connection.
   if ( fnAddConnectionToNetwork( lpTask, lpNetwork, pchAddress,
                                  &pvConn, TRUE, zAPPLREQ_ACTIVATE,
                                  &ActivateInfo, vSubtask ) < 0 )
   {
      return( zNETWORK_ERROR );
   }

   if ( lpNetwork->nTraceLevel > 1 )
      TraceLineS( "(kzoeneta) ** Sending RequestOI packet", "" );

   *pvReturnView = 0;

   //=======================================================================
   // Transmitting data.
   //
   // Until further notice, the following code only SENDS data over the
   // network.
   //=======================================================================

   // First send the header for the server driver and then the regular
   // packet for the function structure.
   if ( fnSendHeaderPacket( lpNetwork, &pvConn,
                            zPACKET_REQUESTOI, szAppName ) != 0 )
   {
      goto EndOfFunction;
   }

   if ( fnSendTraceSwitches( lpNetwork, &pvConn, lpTask) != 0 )
      goto EndOfFunction;

   if ( fnSendDataPacket( lpNetwork, &pvConn, zPACKET_REQUESTOI, 0 ) != 0 )
      goto EndOfFunction;

   // Set up the activate information.  We initialize the structure to 0's so
   // that the network stack can better compress the data.
   zmemset( &ActPacket, 0, sizeof( zActivatePacket ) );
   strcpy_s( ActPacket.szVersion, zsizeof( ActPacket.szVersion ), zCURRENT_PROTOCOL_VERSION );
   zltox( lControl, ActPacket.szControl, zsizeof( ActPacket.szControl ) );
   strcpy_s( ActPacket.szObjectDef, zsizeof( ActPacket.szObjectDef ), pchObjName );
   if ( vQual )
      ActPacket.cUseQualification = 'Y';
   else
      ActPacket.cUseQualification = 'N';

   strcpy_s( ActPacket.szAppName, zsizeof( ActPacket.szAppName ), szAppName );
   SysGetUserID( vSubtask, ActPacket.szUserName, zsizeof( ActPacket.szUserName ), ActPacket.szPassword, zsizeof( ActPacket.szPassword ) );

   if ( lpNetwork->nTraceLevel > 1 )
   {
      TraceLine( "(kzoeneta) ** Sending Activate Packet ... ApplName: %s  Object Def: %s  User Name: %s",
                 ActPacket.szAppName, ActPacket.szObjectDef, ActPacket.szUserName );
   }

   // Send server activate info.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn,
                                &ActPacket, sizeof( zActivatePacket ), zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   // If we have a qualification object, then send it.
   if ( vQual )
   {
      if ( lpNetwork->nTraceLevel > 0 )
         TraceLineS( "(kzoeneta) ** Sending qualification OI", "" );

      if ( fnSendOI( &pvConn, lpNetwork, vQual, 0 ) == zCALL_ERROR )
         goto EndOfFunction;
   }

   // Tell network handler to flush the send buffer.
   if ( fnFlushBuffer( lpNetwork, &pvConn ) != 0 )
      goto EndOfFunction;

   //=======================================================================
   // Receiving data.
   //
   // From here until we close the connection we will only RECEIVE data over
   // the network.
   //=======================================================================

   // Wait for Ack.
   if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
      goto EndOfFunction;
   }

   switch ( cPacketType )
   {
      case zPACKET_ACK:
         // We got an ACK, so continue OK.
         if ( lpNetwork->nTraceLevel > 0 )
         {
            TraceLineS( "(kzoeneta) ** Received Act ACK - proceeding with Act", "" );
            TraceLineS( "(kzoeneta) ** Receiving activated OI.", "" );
         }

         nRC = fnReceiveOI( &pvConn, lpNetwork, pvReturnView, vSubtask, pchObjName, lControl );
         break;

      case zPACKET_EMPTYOI:
         // This means that the server didn't find anything to activate and
         // is returning an empty OI.  Instead of actually returning it from
         // the server (and wasting time on the network), we'll just activate it here.
         ActivateEmptyObjectInstance( pvReturnView, pchObjName, vSubtask, lControl );
         break;

      case zPACKET_ERROR:
         TraceLineI( "(kzoeneta) ** Network error #", lPacketData );
         if ( lPacketData == zNETERR_INVALIDAPP )
         {
            fnSysMessageBox( lpTask, "Application not defined on Server", ActPacket.szAppName, 0 );
         }
         else
         if ( lPacketData == zNETERR_OUTOFMEMORY )
         {
            fnSysMessageBox( lpTask, "Server Transaction Crash ", "*Out Of Memory*", 1 );
         }
         else
            fnRetrieveMsgAndTraceObj( lpNetwork, &pvConn, vSubtask );

         goto EndOfFunction;

      case zPACKET_RC:
         // If we received the RC packet, then there was an error activating
         // the OI on the server.  Get the return code and go to the end of the function.
         if ( lpNetwork->nTraceLevel > 0 )
            TraceLineS( "(kzoeneta) ** Received RC - error in Commit", "" );

         if ( fnRetrieveMsgAndTraceObj( lpNetwork, &pvConn, vSubtask ) < 0 )
            goto EndOfFunction;

         nRC = (zSHORT) lPacketData;
         goto EndOfFunction;

      default:
         TraceLineS( "(kzoeneta) ** Received unknown Packet!", "" );
         goto EndOfFunction;
   }

   // Get return code.
   if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   if ( cPacketType != zPACKET_RC )
   {
      TraceLineS( "(kzoeneta) ** No return code for Commit!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   nRC = (zSHORT) lPacketData;

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineI( "(kzoeneta) ** RC from activate = ", nRC );
   }

   if ( fnRetrieveMsgAndTraceObj( lpNetwork, &pvConn, vSubtask ) < 0 )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

EndOfFunction:
   fnRemoveConnectionFromNetwork( lpNetwork, &pvConn, TRUE );

   return( nRC );

} // fnNetActivateOI

//./ ADD NAME=NetStartup
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetStartup
//
//  PURPOSE:     To initialize a network protocol.
//
//  DESCRIPTION: Starts up a network for a task.  This op opens the
//               network handler executable and checks that it has all
//               necessary functions.  If it does, it then calls zNetStart
//               in the network handler.
//
//               Some network information is stored in a linked list
//               off of the task.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               pchExecutable  - Name of Network Handler executable.
//
//  RETURNS:     0           - Network started OK.
//               zCALL_ERROR - Error starting network.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT OPERATION
NetStartup( zVIEW    lpTaskView,
            zPCHAR   pchNetworkName,
            zPCHAR   pchExecutable )
{
   LPTASK           lpTask;
   LPTASK           lpSystemTask = zGETPTR( AnchorBlock->hMainTask );
   zVIEW            vSystemView = zGETPTR( lpSystemTask->hFirstView );
   LPNETWORK        lpNetwork;
   zPVOID           hNetwork;
   zCHAR            szFileName[ zMAX_FILENAME_LTH + 1 ];
   zPVOID           lpvNetHandle;
   LPLIBRARY        hLibrary;
   zCHAR            szGroup[ 4096 ];
   zCHAR            szServerDirApp[ 4096 ];
   zCHAR            szTraceLevel[ 20 ];
   zCHAR            szDefaultNetwork[ 4096 ];
   zCHAR            szExecutableName[ zMAX_FILENAME_LTH + 1 ];
// zBOOL            bOldTrace;
   zLPFN_NETSTART   lpfnInit;
   zLPFN_NETCLOSE   lpfnClose;
   zLPFN_NETLISTEN  lpfnListen;
   zLPFN_NETCLOSE   lpfnStopListen;
   zLPFN_NETOPCONN  lpfnOpenConn;
   zLPFN_NETCLCONN  lpfnCloseConn;
   zLPFN_NETGETADDR lpfnGetAddress;
   zLPFN_NETIO      lpfnSend;
   zLPFN_NETIO      lpfnReceive;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetStartup, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   // If network name isn't supplied, use the default.
   if ( pchNetworkName == 0 || *pchNetworkName == 0 )
   {
      SysReadZeidonIni( -1, "[Zeidon]", "DefaultNetwork", szDefaultNetwork, zsizeof( szDefaultNetwork ) );
      if ( szDefaultNetwork[ 0 ] == 0 )
      {
         SysMessageBox( lpTaskView, szlNetworkError, "No default network for NetStartup", 1 );
         fnOperationReturn( iNetStartup, lpTask );
         return( zCALL_ERROR );
      }

      pchNetworkName = szDefaultNetwork;

      SysReadZeidonIni( -1, "[Zeidon]", "DefaultNetworkExec", szExecutableName, zsizeof( szExecutableName ) );
      if ( szExecutableName[ 0 ] == 0 )
      {
         // If no exec name give, use network name for executable too.
         strcpy_s( szExecutableName, zsizeof( szExecutableName ), szDefaultNetwork);
      }

      pchExecutable = szExecutableName;
   }

   // Since networks are chained off the system task we need to protect
   // ourselves from other threads.
   zLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   // Check to make sure that the network name doesn't already exist.
   if ( fnFindNetwork( lpTask, pchNetworkName, FALSE ) != 0 )
   {
      fnOperationReturn( iNetStartup, lpTask );
      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      return( 0 );
   }

   if ( zstrchr( pchNetworkName, cDirSep ) == 0 )
   {
      SysGetLocalDirectory( szFileName );
      strcat_s( szFileName, zsizeof( szFileName ), pchExecutable );
   }
   else
      strcpy_s( szFileName, zsizeof( szFileName ), pchExecutable );

   // Try loading the library.
   hLibrary = SysLoadLibrary( vSystemView, szFileName );
   if ( hLibrary == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Can't find library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   // Make sure that the Network Handler contains all the necessary operations.
   lpfnInit = (zLPFN_NETSTART) SysGetProc( hLibrary, "zNetStart" );
   if ( lpfnInit == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Can't find operation zNetStart in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   lpfnClose = (zLPFN_NETCLOSE) SysGetProc( hLibrary, "zNetClose" );
   if ( lpfnClose == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Can't find operation zNetClose in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   lpfnListen = (zLPFN_NETLISTEN) SysGetProc( hLibrary, "zNetListen" );
   if ( lpfnListen == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Can't find operation zNetListen in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   lpfnStopListen = (zLPFN_NETCLOSE) SysGetProc( hLibrary, "zNetStopListen" );
   if ( lpfnStopListen == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Can't find operation zNetStopListen in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   lpfnOpenConn = (zLPFN_NETOPCONN) SysGetProc( hLibrary, "zNetOpenConnection" );
   if ( lpfnOpenConn == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Can't find operation zNetOpenConnection in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   lpfnCloseConn = (zLPFN_NETCLCONN) SysGetProc( hLibrary, "zNetCloseConnection" );
   if ( lpfnCloseConn == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Can't find operation zNetCloseConnection in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   lpfnSend = (zLPFN_NETIO) SysGetProc( hLibrary, "zNetSend" );
   if ( lpfnSend == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Can't find operation zNetSend in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   lpfnReceive = (zLPFN_NETIO) SysGetProc( hLibrary, "zNetReceive" );
   if ( lpfnReceive == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Cannot find operation zNetReceive in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   lpfnGetAddress = (zLPFN_NETGETADDR) SysGetProc( hLibrary, "zNetGetHostAddress" );
   if ( lpfnGetAddress == 0 )
   {
      zCHAR szMsg[ 200 ];

      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      sprintf_s( szMsg, zsizeof( szMsg ), "Cannot find operation zNetGetLocalHostAddress in library '%s'", pchExecutable );
      SysMessageBox( lpTaskView, "Zeidon Network Error", szMsg, 1 );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   // We got here, so the DLL contains all the operations it needs, so
   // call init operation.
   TraceLineS( "(kzoeneta) ** Starting network ", szFileName );
   if ( (*lpfnInit)( pchNetworkName, &lpvNetHandle ) != 0 )
   {
      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      SysFreeLibrary( vSystemView, hLibrary );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   // If we get here then we're in business.  Create the network buffer and
   // add the network to the network chain.
   hNetwork = (LPNETWORK) fnAllocDataspace( (LPDATAHEADER) lpSystemTask->hFirstDataHeader,
                                            sizeof( NetworkRecord ), TRUE, 0, 0 );
   lpNetwork = zGETPTR( hNetwork );
   if ( lpNetwork == 0 )
   {
      zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
      SysMessageBox( lpTaskView, szlNetworkError, "Out of memory for network", 1 );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   zmemset( lpNetwork, 0, sizeof( NetworkRecord ) );

// Following functions are NOT necessary.  Turn off tracing flag so we
   // don't show warning messages.
// bOldTrace = lpTask->bTrace;
// lpTask->bTrace = FALSE;
//
// lpNetwork->lpfnBufferEnd  = 0;//(zLPFN_NETCLCONN) SysGetProc( hLibrary, "zNetBufferEnd" );
// lpNetwork->lpfnSendPacket = 0;//(zLPFN_NETSENDPKT)SysGetProc( hLibrary, "zNetSendPacket" );
// lpNetwork->lpfnRecvPacket = 0;//(zLPFN_NETRECVPKT)SysGetProc( hLibrary, "zNetReceivePacket" );
// lpNetwork->lpfnSetMode    = 0;//(zLPFN_NETSETM)   SysGetProc( hLibrary, "zNetSetMode" );
//
// lpTask->bTrace = bOldTrace;

   strcpy_s( lpNetwork->szNetworkName, zsizeof( lpNetwork->szNetworkName ), pchNetworkName );
   strcpy_s( lpNetwork->szExecutable, zsizeof( lpNetwork->szExecutable ), pchExecutable );
   lpNetwork->nConnCount     = 0;
   lpNetwork->lProcessID     = SysGetProcessID( 0 );
   lpNetwork->bListen        = FALSE;
   lpNetwork->pNetworkHandle = lpvNetHandle;
   lpNetwork->hLibrary       = hLibrary;
   lpNetwork->lpfnClose      = lpfnClose;
   lpNetwork->lpfnOpenConn   = lpfnOpenConn;
   lpNetwork->lpfnCloseConn  = lpfnCloseConn;
   lpNetwork->lpfnSend       = lpfnSend;
   lpNetwork->lpfnReceive    = lpfnReceive;
   lpNetwork->lpfnListen     = lpfnListen;
   lpNetwork->lpfnStopListen = lpfnStopListen;
   lpNetwork->lpfnGetAddress = lpfnGetAddress;

   sprintf_s( szGroup, zsizeof( szGroup ), "[%s]", pchNetworkName );
   SysReadZeidonIni( -1, szGroup, "TraceLevel", szTraceLevel, zsizeof( szTraceLevel ) );
   lpNetwork->nTraceLevel = (zSHORT) zatol( szTraceLevel );
   SysReadZeidonIni( -1, szGroup, "ServerCoreTraceLevel", szTraceLevel, zsizeof( szTraceLevel ) );
   lpNetwork->nServerCoreTraceLevel = (zSHORT) zatol( szTraceLevel );
   SysReadZeidonIni( -1, szGroup, "ServerNetTraceLevel", szTraceLevel, zsizeof( szTraceLevel ) );
   lpNetwork->nServerNetTraceLevel = (zSHORT) zatol( szTraceLevel );
   SysReadZeidonIni( -1, szGroup, "ServerDBHTraceLevel", szTraceLevel, zsizeof( szTraceLevel ) );
   lpNetwork->nServerDBHTraceLevel = (zSHORT) zatol( szTraceLevel );

   lpNetwork->hNextNetwork = AnchorBlock->hFirstNetwork;
   AnchorBlock->hFirstNetwork = hNetwork;

   zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

#if 0
   // Following functions are NOT necessary.  Turn off tracing flag so we
   // don't show warning messages.
   bOldTrace = lpTask->bTrace;
   lpTask->bTrace = FALSE;

   lpNetwork->lpfnBufferEnd  = (zLPFN_NETCLCONN) SysGetProc( hLibrary, "zNetBufferEnd" );
   lpNetwork->lpfnSendPacket = (zLPFN_NETSENDPKT) SysGetProc( hLibrary, "zNetSendPacket" );
   lpNetwork->lpfnRecvPacket = (zLPFN_NETRECVPKT) SysGetProc( hLibrary, "zNetReceivePacket" );
   lpNetwork->lpfnSetMode    = (zLPFN_NETSETM) SysGetProc( hLibrary, "zNetSetMode" );

   lpTask->bTrace = bOldTrace;
#endif

   if ( lpNetwork->nTraceLevel > 0 )
   {
      zCHAR szLocalName[ 300 ];

      NetGetLocalHostAddress( lpTaskView, pchNetworkName, szLocalName );
      TraceLineS( "(kzoeneta) ** Local host address = ", szLocalName );
   }

   //
   // Now load the server directory functions.
   //

   SysReadZeidonIni( -1, szGroup, "ServerDirApp", szServerDirApp, zsizeof( szServerDirApp ) );
   if ( szServerDirApp[ 0 ] == 0 )
      strcpy_s( szServerDirApp, zsizeof( szServerDirApp ), "zSimpDir" );

   if ( zstrchr( szServerDirApp, cDirSep ) == 0 )
   {
      SysGetLocalDirectory( lpNetwork->szFileName );
      strcat_s( lpNetwork->szFileName, zsizeof( lpNetwork->szFileName ), szServerDirApp );
   }
   else
      strcpy_s( lpNetwork->szFileName, zsizeof( lpNetwork->szFileName ), szServerDirApp );

   // Try loading the library.
   if ( LoadNetworkOperations( (LPTASK) zGETPTR( lpTaskView->hTask ), lpNetwork ) == 0 )
   {
      (*lpNetwork->lpfnServDirInit)( lpTask, pchNetworkName, &lpNetwork->pvServDirData, 0 );
   }
   else
   {
      NetClose( lpTaskView, pchNetworkName );
      fnOperationReturn( iNetStartup, lpTask );
      return( zCALL_ERROR );
   }

   fnOperationReturn( iNetStartup, lpTask );
   return( 0 );

} // NetStartup

//./ ADD NAME=NetClose
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetClose
//
//  PURPOSE:     To close a network.
//
//  DESCRIPTION: This operation closes a network started with the
//               NetStartup operation.  It calls the network handler
//               zNetClose operation and then removes the network
//               information from the task chain.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//
//  RETURNS:     0           - Network closed OK.
//               zCALL_ERROR - Error closing network.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
NetClose( zVIEW lpTaskView, zPCHAR pchNetworkName )
{
   LPTASK      lpTask;
   LPTASK      lpSystemTask = zGETPTR( AnchorBlock->hMainTask );
   LPNETWORK   lpPrevNetwork;
   LPNETWORK   lpSrchNetwork;
   LPNETWORK   lpNetwork;
   LPLIBRARY   lpLibrary;
   zLONG       lProcessID;
   zSHORT      nRC = 0;

   TraceLineS( "(kzoeneta) ** NetClose for Network: ", pchNetworkName );

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetClose, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   zLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetClose, lpTask );
      return( zCALL_ERROR );
   }

   if ( lpNetwork->bListen &&
        NetStopListen( lpTaskView, lpNetwork->szNetworkName ) == zCALL_ERROR )
   {
      // Error trying to stop a listen, but we keep trying to close the network.
      nRC = zCALL_ERROR;
   }

   // Try closing any open connections.
   while ( lpNetwork->hFirstNetConn )
   {
      LPNETCONN lpNetConn = zGETPTR( lpNetwork->hFirstNetConn );

      fnRemoveConnectionFromNetwork( lpNetwork, lpNetConn->pvConn, TRUE );
   }

   lProcessID = SysGetProcessID( 0 );
// if ( lpNetwork->lpfnServDirClose )
// {
//    lpLibrary = zGETPTR( lpNetwork->hServDirLib );
//    if ( lProcessID != lpLibrary->lProcessID )
//       LoadNetworkOperations( lpTask, lpNetwork );
// }

   if ( lpNetwork->lpfnServDirClose &&
        LoadNetworkOperations( lpTask, lpNetwork ) == 0 &&
        (*lpNetwork->lpfnServDirClose)( lpTask, &lpNetwork->pvServDirData, 0 ) != 0 )
   {
      nRC = zCALL_ERROR;
   }

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Closing network ", lpNetwork->szNetworkName );

   if ( lpNetwork->lpfnClose &&
        (*lpNetwork->lpfnClose)( lpTaskView, &lpNetwork->pNetworkHandle ) != 0 )
   {
      nRC = zCALL_ERROR;
   }

   if ( lpNetwork->hLibrary )
   {
      lpLibrary = zGETPTR( lpNetwork->hLibrary );
      if ( lProcessID == lpLibrary->lProcessID )
         SysFreeLibrary( lpTaskView, lpNetwork->hLibrary );
   }

   if ( lpNetwork->lpfnServDirClose &&
        (*lpNetwork->lpfnServDirClose)( lpTask, &lpNetwork->pvServDirData, 0 ) != 0 )
   {
      nRC = zCALL_ERROR;
   }

   if ( lpNetwork->hServDirLib )
   {
      SysFreeLibrary( lpTaskView, lpNetwork->hServDirLib );
      lpNetwork->hServDirLib = 0;
   }

   // Remove the network from the chain.
   lpPrevNetwork = 0;
   for ( lpSrchNetwork = zGETPTR( AnchorBlock->hFirstNetwork );
         lpSrchNetwork != lpNetwork;
         lpSrchNetwork = zGETPTR( lpSrchNetwork->hNextNetwork ) )
   {
      lpPrevNetwork = lpSrchNetwork;
   }

   if ( lpPrevNetwork )
      lpPrevNetwork->hNextNetwork = lpNetwork->hNextNetwork;
   else
      AnchorBlock->hFirstNetwork = lpNetwork->hNextNetwork;

   zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

   fnFreeDataspace( lpNetwork );

   fnOperationReturn( iNetClose, lpTask );
   return( nRC );

} // NetClose

//./ ADD NAME=NetListen
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetListen
//
//  PURPOSE:     To initiate a "listen" on the network.  This means that
//               the current task can then accept Zeidon messages.
//
//  DESCRIPTION: This operation calls the network handler func zNetListen
//               to initiate the listen.  The network handler then
//               calls NetProcessMessage when it receives a message.  There
//               is only one listen allowed per task.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//
//  RETURNS:     0           - Network listen OK
//               zCALL_ERROR - Error on listen.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
NetListen( zVIEW lpTaskView, zPCHAR pchNetworkName )
{
   LPTASK      lpTask;
   LPNETWORK   lpNetwork;
   zSHORT      nRC = 0;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetListen, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetListen, lpTask );
      return( zCALL_ERROR );
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Starting NetListen for network ", lpNetwork->szNetworkName );
   }

   if ( lpNetwork->bListen )
   {
      TraceLineS( "(kzoeneta) ** Network already listening!", lpNetwork->szNetworkName );
      fnOperationReturn( iNetListen, lpTask );
      return( 0 );
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Starting listen for network ", lpNetwork->szNetworkName );
   }

   if ( (*lpNetwork->lpfnListen)( &lpNetwork->pNetworkHandle, 0, lpTaskView ) != 0 )
   {
      fnOperationReturn( iNetListen, lpTask );
      return( zCALL_ERROR );
   }

   lpNetwork->bListen = TRUE;

   fnOperationReturn( iNetListen, lpTask );
   return( nRC );

} // NetListen

//./ ADD NAME=NetStopListen
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetStopListen
//
//  PURPOSE:     To stop (or close) a listen initiated with NetListen.
//
//  DESCRIPTION: This operation calls the network handler function
//               zNetStopListen to close listen.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//
//  RETURNS:     0           - Network listen stopped OK
//               zCALL_ERROR - Error on stop listen.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
NetStopListen( zVIEW lpTaskView, zPCHAR pchNetworkName )
{
   LPTASK      lpTask;
   LPNETWORK   lpNetwork;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetStopListen, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetStopListen, lpTask );
      return( zCALL_ERROR );
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Stopping listen for network ", lpNetwork->szNetworkName );
   }

   if ( lpNetwork->bListen == FALSE )
   {
      TraceLineS( "(kzoeneta) ** Network not listening!", lpNetwork->szNetworkName );
      fnOperationReturn( iNetStopListen, lpTask );
      return( 0 );
   }

   if ( (*lpNetwork->lpfnStopListen)( lpTaskView, &lpNetwork->pNetworkHandle ) != 0 )
   {
      fnOperationReturn( iNetStopListen, lpTask );
      return( zCALL_ERROR );
   }

   lpNetwork->bListen = FALSE;

   fnOperationReturn( iNetStopListen, lpTask );
   return( 0 );

} // NetStopListen

//./ ADD NAME=NetProcessMessage
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetProcessMessage
//
//  PURPOSE:     To process messages received from the network after a
//               listen has been started.
//
//  DESCRIPTION: This operation is only called from the network handler
//               executable after (a) a listen has been started and (b) a
//               message has been received from another workstation.  This
//               operation assumes the following:
//
//               o The message HAS NOT yet been retrieved.  Calling this
//                 operation indicates that a message is available.
//
//               o A connection between the remote and current computers
//                 has already been created.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//
//  RETURNS:     Depends on message.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
NetProcessMessage( zVIEW lpTaskView, zPCHAR pchNetworkName, zPVOID *ppvConn )
{
   zCHAR       *pchTemp;
   LPTASK      lpTask;
   zCHAR       cPacketType;
   zLONG       lPacketData;
   LPNETWORK   lpNetwork;
   zVIEW       vTrace = 0;
   zSHORT      nRC = 0;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetProcessMessage, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   TraceLineS( "(kzoeneta) ** Inside NetProcessMessage( ) network: ", pchNetworkName );

   // Set flag indicating that the current task is a server for a client
   // request.
   lpTask->bServer = TRUE;

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      TraceLineS( "(kzoeneta) ** Cannot find network NetProcessMessage( ) network: ", pchNetworkName );
      fnOperationReturn( iNetProcessMessage, lpTask );
      lpTask->bServer = FALSE;
      return( zCALL_ERROR );
   }

   // A connection should have been created and passed to us via ppvConn so
   // we'll just add it to our connection list.
   fnAddConnectionToNetwork( lpTask, lpNetwork, 0, ppvConn, FALSE, 0, 0, lpTaskView );

// if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Received message for network ", lpNetwork->szNetworkName );

   // This seems to continue looping if the data packet if a TRACESWITCH or TIMESTAMP. Not really sure
   // when that would be used.
   while ( TRUE )
   {
      if ( fnReceiveDataPacket( lpNetwork, ppvConn, &cPacketType, &lPacketData ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error receiving message!", "" );
         nRC = zCALL_ERROR;
      }

      if ( cPacketType == zPACKET_TRACESWITCH )
      {
         if ( fnProcessTraceSwitches( lpNetwork, ppvConn, lpTask ) != 0 )
         {
            TraceLineS( "(kzoeneta) ** Error receiving Trace Switches", "" );
            nRC = zCALL_ERROR;
         }
      }
      else
      if ( cPacketType == zPACKET_TIMESTAMP )
      {
         fnProcessTimestamp( lpNetwork, ppvConn, lpTask );
      }
      else
         break;
   }

   if ( nRC )
   {
      TraceLineS( "(kzoeneta) ** Error ... removing connection from network!", "" );
      fnRemoveConnectionFromNetwork( lpNetwork, ppvConn, FALSE );
      fnOperationReturn( iNetProcessMessage, lpTask );
      lpTask->bServer = FALSE;
      return( zCALL_ERROR );
   }

   // Create Trace Object
   nRC = SfActivateSysEmptyOI( &vTrace, "KZTRACEO", lpTaskView, zSINGLE );
   if ( nRC == 0 )
      nRC = SetNameForView( vTrace, "KZTRACEO", lpTaskView, zLEVEL_TASK );

   if ( nRC == 0 )
      nRC = SfLockView( vTrace );

   if ( nRC == 0 )
   {
      zCHAR szDateTime[ 18 ];

      nRC = CreateEntity( vTrace, "Trace", zPOS_AFTER );
      SetAttributeFromInteger( vTrace, "Trace", "nLine", 0 );
      SysGetDateTime( szDateTime, zsizeof( szDateTime ) ); // DateTime yyyymmddhhmmssttt
      SetAttributeFromVariable( vTrace, "Trace", "TraceStart", szDateTime, zTYPE_STRING, 17, "DateTime", 0 );
   }

   switch ( cPacketType )
   {
      case zPACKET_REQUESTOIFROMFILE:
         pchTemp = "Request OI From File";
         break;

      case zPACKET_REQUESTOI:
         pchTemp = "Request OI";
         break;

      case zPACKET_COMMITOITOFILE:
         pchTemp = "Commit OI to File";
         break;

      case zPACKET_COMMITOI:
         pchTemp = "Commit OI";
         break;

      case zPACKET_SENDFILE:
         pchTemp = "Send File";
         break;

      case zPACKET_CALLOPERATION:
         pchTemp = "Call Operation";
         break;

      default:
         pchTemp = "BAD_MESSAGE";
         break;
   }

   TraceLineS( "(kzoeneta) ** Message Type == ", pchTemp );

   if ( setjmp( jbEmergencyExit ) == 0 )
   {
      // Check to see if the client requested an OI.
      switch ( cPacketType )
      {
         case zPACKET_REQUESTOIFROMFILE:
            nRC = fnProcessActivateOI_FromFile( lpNetwork, ppvConn );
            break;

         case zPACKET_REQUESTOI:
            nRC = fnProcessActivateOI( lpTaskView, lpNetwork, ppvConn );
            break;

         case zPACKET_COMMITOITOFILE:
            nRC = fnProcessCommitOI_ToFile( lpNetwork, ppvConn );
            break;

         case zPACKET_COMMITOI:
            nRC = fnProcessCommitOI( lpTaskView, lpNetwork, ppvConn );
            break;

         case zPACKET_SENDFILE:
            nRC = fnProcessSendFile( lpTaskView, lpNetwork, ppvConn );
            break;

         case zPACKET_CALLOPERATION:
            nRC = fnProcessOperation( lpTaskView, lpNetwork, ppvConn );
            break;

         default:
            nRC = zCALL_ERROR;
            TraceLineI( "(kzoeneta) ** Bad message = ", cPacketType );
            if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_BADMESSAGE ) != 0 )
            {
               TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
            }

            break;
      }
   }
   else
   {
      // We get here on a return from longjmp.
      // At that point, the system is highly instable (Out Of Memory).
      fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR,
                        zNETERR_OUTOFMEMORY );
      nRC = -1;
   }

   // Delete Trace Object
   if ( vTrace )
      DropObjectInstance( vTrace );

   // The connection should be closed as soon as we return soooo...
   fnRemoveConnectionFromNetwork( lpNetwork, ppvConn, FALSE );

   fnOperationReturn( iNetProcessMessage, lpTask );
   lpTask->bServer = FALSE;
   TraceLine( "(kzoeneta) ** Leaving NetProcessMessage( ) network: %s  RC: %d", pchNetworkName, nRC );

   return( nRC );

} // NetProcessMessage

//./ ADD NAME=fnConvertIS_Clause
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       fnConvertIS_Clause
//
//  PURPOSE:     To convert the "IS" clause in the qualfication object.
//
//  DESCRIPTION: The "IS" clause causes qualfication of an entity by
//               matching it's keys with another entity.  This is usually
//               done at SQL build time but it requires the source view.
//               Since we don't pass the source view to the server we will
//               have to change the "IS" clause into the corresponding
//               'key1 = value1 AND key2 = value2...) qualfication.
//
//  PARAMETERS:  plpQualView - The original qualification view.           If
//                        there is an "IS" clause this view will be changed.
//
//  RETURNS:     zCALL_ERROR - Error.
//               0 - OK.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT LOCALOPER
fnConvertIS_Clause( zPVIEW plpQualView )
{
   zVIEW             lpOrigQual = *plpQualView;
   zVIEW             lpNewQual = 0;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;
   LPENTITYINSTANCE  lpEntityInstance;
   LPVIEWENTITY      lpQualViewEntity;
   LPVIEWENTITYCSR   lpQualViewEntityCsr;
   LPVIEWENTITY      lpSubQualViewEntity;
   LPVIEWENTITYCSR   lpSubQualViewEntityCsr;

   ActivateOI_FromOI_ForTask( &lpNewQual, lpOrigQual, 0, zMULTIPLE );
   *plpQualView = lpNewQual;

   lpViewCsr = zGETPTR( lpNewQual->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

   lpQualViewEntity = fnValidViewEntity( &lpQualViewEntityCsr, lpNewQual, "QualAttrib", 0 );
   lpSubQualViewEntity = fnValidViewEntity( &lpSubQualViewEntityCsr, lpNewQual, "SubQualAttrib", 0 );

   // Loop through each of the entities in the and look for QualAttribs and SubQualAttribs.
   for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
   {
      LPVIEWENTITY    lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
      LPVIEWENTITY    lpSrcViewEntity;
      LPVIEWATTRIB    lpViewAttrib;
      LPVIEWENTITYCSR lpViewEntityCsr;
      LPVIEWENTITYCSR lpTempViewEntityCsr;
      zVIEW           lpSrcView;
      zCHAR           szSrcViewName[ zZEIDON_NAME_LTH + 1 ];
      zCHAR           szTargetEntity[ zZEIDON_NAME_LTH + 1 ];
      zCHAR           szSourceEntity[ zZEIDON_NAME_LTH + 1 ];
      zPCHAR          pchEntityName;
      zBOOL           bFirstTime;

      // Find if the current EI is a QualAttrib or a SubQualAttrib.
      if ( lpViewEntity == lpQualViewEntity )
         lpViewEntityCsr = lpQualViewEntityCsr;
      else
      if ( lpViewEntity == lpSubQualViewEntity )
         lpViewEntityCsr = lpSubQualViewEntityCsr;
      else
         continue;      // Skip non-QualAttrib entities.

      fnEstablishViewForInstance( lpNewQual, lpViewEntityCsr,
                                  lpEntityInstance );

      pchEntityName = lpViewEntity->szName;

      // Skip over entities where the Oper is not "IS".
      if ( CompareAttributeToString( lpNewQual, pchEntityName, "Oper", "IS" ) != 0 )
      {
         continue;
      }

      // Get the source view.entity and the target entity.
      GetStringFromAttribute( szSrcViewName, zsizeof( szSrcViewName ), lpNewQual, pchEntityName, "SourceViewName" );
      if ( szSrcViewName && szSrcViewName[ 0 ] )
         GetViewByName( &lpSrcView, szSrcViewName, lpOrigQual, zLEVEL_TASK );
      else
         GetIntegerFromAttribute( (zPLONG) &lpSrcView, lpNewQual, pchEntityName, "SourceViewID" );
      GetStringFromAttribute( szSourceEntity, zsizeof( szSourceEntity ), lpNewQual, pchEntityName, "SourceEntityName" );
      GetStringFromAttribute( szTargetEntity, zsizeof( szTargetEntity ), lpNewQual, pchEntityName, "EntityName" );

      // Now change the "IS" to "(key1 = value1 & key2 = value2...)"

      // Replace the "IS" with open paren.
      SetAttributeFromString( lpNewQual, pchEntityName, "Oper", "(" );
      SetAttributeFromString( lpNewQual, pchEntityName, "SourceViewName", "" );
      SetAttributeFromString( lpNewQual, pchEntityName, "SourceViewID", "" );
      SetAttributeFromString( lpNewQual, pchEntityName, "SourceEntityName", "" );
      SetAttributeFromString( lpNewQual, pchEntityName, "EntityName", "" );

      // Add a QualAttrib for each key.
      lpSrcViewEntity = fnValidViewEntity( &lpTempViewEntityCsr, lpSrcView, szSourceEntity, 0 );
      bFirstTime = TRUE;
      for ( lpViewAttrib = zGETPTR( lpSrcViewEntity->hFirstOD_Attrib );
            lpViewAttrib;
            lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
      {
         if ( lpViewAttrib->bKey == FALSE )
            continue;

         if ( bFirstTime )
            bFirstTime = FALSE;
         else
         {
            // Create the "AND" oper.
            CreateEntity( lpNewQual, pchEntityName, zPOS_NEXT );
            SetAttributeFromString( lpNewQual, pchEntityName, "Oper", "AND" );
         }

         // Create the key compare.
         CreateEntity( lpNewQual, pchEntityName, zPOS_NEXT );
         SetAttributeFromString( lpNewQual, pchEntityName, "EntityName", szTargetEntity );
         SetAttributeFromString( lpNewQual, pchEntityName, "AttributeName", lpViewAttrib->szName );
         SetAttributeFromString( lpNewQual, pchEntityName, "Oper", "=" );
         SetAttributeFromAttribute( lpNewQual, pchEntityName, "Value", lpSrcView, szSourceEntity,
                                    lpViewAttrib->szName );
      } // for ( lpViewAttrib )...

      // Create the closing paren.
      CreateEntity( lpNewQual, pchEntityName, zPOS_NEXT );
      SetAttributeFromString( lpNewQual, pchEntityName, "Oper", ")" );

      // We've just created a number of QualAttribs that we know don't contain
      // the "IS" oper so set lpEntityInstance to skip over the new entities.
      lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );

   } // for ( lpEntityInstance )...

   return( 0 );

} // fnConvertIS_Clause

//./ ADD NAME=NetActivateOI
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetActivateOI
//
//  PURPOSE:     To activate an OI from a remote computer.
//
//  DESCRIPTION: This operation activates an OI across the network.
//               Other than pchNetworkName, this operation is used exactly
//               like ActivateObjectInstance.
//
//               NOTE: This operation is currently assumed to be an
//               internal operation (e.g. it is called only from Core) and
//               therefore does NO validity checking.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               pchAddress     - Address of server.
//
//               For a description of the rest of the arguments, see
//               ActivateObjectInstance.
//
//  RETURNS:     zCALL_ERROR - Error activating object.
//               Otherwise see return codes for ActivateObjectInstance.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zSHORT OPERATION
NetActivateOI( zPCHAR  pchNetworkName,
               zPCHAR  pchAddress,
               zPVIEW  pvReturnView,
               zPCHAR  pchViewOD_Name,
               zVIEW   vSubtask,
               zVIEW   lpQualView,
               zLONG   lControl    )
{
   LPTASK         lpTask;
   LPNETWORK      lpNetwork;
   zSHORT         nRC = 0;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetActivateOI, vSubtask, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetActivateOI, lpTask );
      return( zCALL_ERROR );
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLine( "(kzoeneta) ** Starting activate for network: %s   OD Name: %s",
                 lpNetwork->szNetworkName, pchViewOD_Name );
   }

   // Check to see if the qualification object uses the "IS" clause.  If it
   // does we need to change the "IS" clause into it's seperate key
   // components.
   if ( lpQualView )
   {
      if ( fnConvertIS_Clause( &lpQualView ) == zCALL_ERROR )
      {
         fnOperationReturn( iNetActivateOI, lpTask );
         return( zCALL_ERROR );
      }
   }

   nRC = fnNetActivateOI( lpTask, lpNetwork, pchAddress, pvReturnView,
                          pchViewOD_Name, vSubtask, lpQualView, lControl );

   // fnConvertIS_Clause( ) created a new qualification object so we must
   // drop it.
   if ( lpQualView )
      fnDropView( lpQualView );

   fnOperationReturn( iNetActivateOI, lpTask );
   return( nRC );

} // NetActivateOI

//./ ADD NAME=NetActivateOI_FromFile
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetActivateOI_FromFile
//
//  PURPOSE:     To activate an OI from a file on a remote computer.
//
//  DESCRIPTION: This operation activates an OI across the network.
//               Other than pchNetworkName, this operation is used exactly
//               like ActivateObjectInstance.
//
//               NOTE: This operation is currently assumed to be an
//               internal operation (e.g. it is called only from Core) and
//               therefore does NO validity checking.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               pchAddress     - Address of server.  If 0 then use LAD.
//
//               For a description of the rest of the arguments, see
//               ActivateOI_FromFile.
//
//  RETURNS:     zCALL_ERROR - Error activating object.
//               Otherwise see return codes for ActivateOI_FromFile.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zSHORT OPERATION
NetActivateOI_FromFile( zPCHAR  pchNetworkName,
                        zPCHAR  pchAddress,
                        zPVIEW  pvReturnView,
                        zPCHAR  pchViewOD_Name,
                        zVIEW   vSubtask,
                        zPCHAR  pchFileName,
                        zLONG   lControl )
{
   return( 0 );

// 2001.06.28
// DGC Not supported at the moment (security risk).
#if 0
   LPTASK          lpTask;
   LAD_InfoRecord  LAD_Info;
   zCHAR           cPacketType;
   zLONG           lPacketData;
   LPNETWORK       lpNetwork;
   zPVOID          pvConn = 0;
   zActivatePacket ActPacket;
   zSHORT          nRC = zCALL_ERROR;

   zmemset( &LAD_Info, 0, zsizeof( LAD_Info ) );

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetActivateOI_FromFile ... )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetActivateOI_FromFile, lpTask );
      return( zCALL_ERROR );
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLine( "(kzoeneta) ** Starting activate for network: %s  OD Name: %s",
                 lpNetwork->szNetworkName, pchViewOD_Name );
   }

   LAD_Info.lpTask     = lpTask;
   LAD_Info.lpNetwork  = lpNetwork;
   LAD_Info.vSubtask   = vSubtask;
   LAD_Info.nObjType   = zLADTYPE_LOD_ACTIVATE_FILE;
   LAD_Info.pchObjName = pchViewOD_Name;
   SysGetUserID( vSubtask, LAD_Info.szUserName, zsizeof( LAD_Info.szUserName ), LAD_Info.szPassword, zsizeof( LAD_Info.szPassword ) );
   fnRetrieveAppName( vSubtask, LAD_Info.szAppName );

   if ( fnGetApplAddress( &LAD_Info, pchAddress ) == zCALL_ERROR )
   {
      fnOperationReturn( iNetActivateOI_FromFile, lpTask );
      return( zCALL_ERROR );
   }

   // Open connection.
   if ( fnAddConnectionToNetwork( &LAD_Info, &pvConn, TRUE, vSubtask ) < 0 )  not used
   {
      fnOperationReturn( iNetActivateOI_FromFile, lpTask );
      return( zNETWORK_ERROR );
   }

   if ( lpNetwork->nTraceLevel > 1 )
      TraceLineS( "(kzoeneta) ** Sending RequestOI packet", "" );

   //=======================================================================
   // Transmitting data.
   //
   // Until further notice, the following code only SENDS data over the
   // network.
   //=======================================================================

   // First send the header for the server driver and then the regular
   // packet for the function structure.
   if ( fnSendHeaderPacket( lpNetwork, &pvConn, zPACKET_REQUESTOIFROMFILE,
                            LAD_Info.szAppName ) != 0 )
      goto EndOfFunction;

   if ( fnSendTraceSwitches( lpNetwork, &pvConn, lpTask) != 0)
      goto EndOfFunction;

   if ( fnSendDataPacket( lpNetwork, &pvConn,
                          zPACKET_REQUESTOIFROMFILE, 0 ) != 0 )
      goto EndOfFunction;

   // Set up the activate information.  We initialize the structure to 0's so
   // that the network stack can better compress the data.
   zmemset( &ActPacket, 0, zsizeof( zActivatePacket ) );
   strcpy_s( ActPacket.szVersion, zCURRENT_PROTOCOL_VERSION );
   zltox( lControl, ActPacket.szControl );
   strcpy_s( ActPacket.szObjectDef, pchViewOD_Name );
   ActPacket.cUseQualification = 'N';
   zltox( (zLONG) zstrlen( pchFileName ) + 1, ActPacket.szFileNameLth );

   strcpy_s( ActPacket.szAppName, LAD_Info.szAppName );
   SysGetUserID( vSubtask, ActPacket.szUserName, zsizeof( ActPacket.szUserName ), ActPacket.szPassword, zsizeof( ActPacket.szPassword ) );

   if ( lpNetwork->nTraceLevel > 1 )
   {
      TraceLine( "(kzoeneta) ** Sending Activate File Packet Appl Name: %s  ",
                   "Object Def: %s  User Name: %s  FileName: %s",
                 ActPacket.szAppName, ActPacket.szObjectDef,
                 ActPacket.szUserName, pchFileName );
   }

   // Send server activate info.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle,
                                &pvConn, &ActPacket, zsizeof( zActivatePacket ),
                                zTYPE_STRING ) != 0 )
      goto EndOfFunction;

   // Send file name.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn,
                                pchFileName,
                                zstrlen( pchFileName ) + 1,
                                zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   // Tell network handler to flush the send buffer.
   if ( fnFlushBuffer( lpNetwork, &pvConn ) != 0 )
      goto EndOfFunction;

   //=======================================================================
   // Receiving data.
   //
   // From here until we close the connection we will only RECEIVE data over
   // the network.
   //=======================================================================

   // Wait for Ack.
   if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
      goto EndOfFunction;
   }

   if ( cPacketType == zPACKET_ERROR )
   {

      TraceLineI( "(kzoeneta) ** Network error #", lPacketData );
      if ( lPacketData == zNETERR_OUTOFMEMORY )
      {
         SysMessageBox( "Server Transaction Crash ",
                        "*Out Of Memory*", 1 );
      }
      goto EndOfFunction;
   }
   else
   if ( cPacketType == zPACKET_RC )
   {
      // If we received the RC packet, then there was an error activating
      // the OI on the server.  Get the return code and go to the end of the
      // function.
      if ( lpNetwork->nTraceLevel > 0 )
         TraceLineS( "(kzoeneta) ** Received RC - error in Commit", "" );

      nRC = (zSHORT) lPacketData;
      goto EndOfFunction;
   }
   else
   if ( cPacketType != zPACKET_ACK )
   {
      TraceLineS( "(kzoeneta) ** Received bytes but no ACK!", "" );
      goto EndOfFunction;
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Received Act ACK - proceeding with Act ... "
                  "Receiving activated OI." );
   }

   fnReceiveOI( &pvConn, lpNetwork, pvReturnView, vSubtask,
                pchViewOD_Name, zMULTIPLE );

   // Get return code.
   if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
      goto EndOfFunction;
   }

   if ( cPacketType != zPACKET_RC )
   {
      TraceLineS( "(kzoeneta) ** No return code for Commit!", "" );
      goto EndOfFunction;
   }

   nRC = (zSHORT) lPacketData;

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineI( "(kzoeneta) ** RC from activate = ", nRC );

   if ( fnRetrieveMsgAndTraceObj( lpNetwork, &pvConn, vSubtask ) < 0 )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

EndOfFunction:

   if ( fnRemoveConnectionFromNetwork( lpNetwork, &pvConn, TRUE ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
   }

   fnOperationReturn( iNetActivateOI_FromFile, lpTask );
   return( nRC );
#endif

} // NetActivateOI_FromFile

LPENTITYINSTANCE LOCALOPER
fnFindEntityInstanceByHierCount( LPENTITYINSTANCE lpEntityInstance,
                                 zLONG            lHierCount )
{
   LPENTITYINSTANCE lpNextTwin;

   while ( lpEntityInstance )
   {
      // If the EI is dead then skip it and it's children.
      if ( fnEntityInstanceIsDead( lpEntityInstance ) )
      {
         if ( lpEntityInstance->hNextTwin )
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );
         else
         {
            zSHORT nLevel = lpEntityInstance->nLevel;

            for ( lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier );
                  lpEntityInstance && lpEntityInstance->nLevel > nLevel;
                  lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
            {
               // Nothing needs to be done here.
            }
         }

         continue;
      }

      if ( lpEntityInstance->lHierCount == lHierCount )
         return( lpEntityInstance );

      // Try a shortcut...see if the next twin (if there is one) has a hier
      // count < the one we're looking for.
      lpNextTwin = zGETPTR( lpEntityInstance->hNextTwin );

      // Just in case the next twin stuff doesn't work out we'll set
      // lpEntityInstance to point to the next EI hierarchically.
      lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier );

      while ( lpNextTwin )
      {
         if ( lpNextTwin->lHierCount <= lHierCount && !fnEntityInstanceIsDead( lpNextTwin ) )
         {
            lpEntityInstance = lpNextTwin;
         }

         lpNextTwin = zGETPTR( lpNextTwin->hNextTwin );
      }
   }

   return( 0 );  // If we get here then we didn't find it.

} // fnFindEntityInstanceByHierCount

/*

   Creates a buffer with a list of all inter-OI entity links.  The info in the buffer looks like:

   (OI-idx:EI-hier#/OI-idx:EI-her#/...)(...)...

*/
#define LINK_BUFFER_SIZE 30000

zSHORT LOCALOPER
fnSetLinkBuffer( LPTASK  lpTask,
                 zVIEW   lpViewArray[],
                 zSHORT  nViewCount,
                 zPPCHAR ppchLinkBuffer,
                 zPLONG  plLinkBufferLth )
{
   zPCHAR           pchLinkBuffer;
   zSHORT           k;
   zPCHAR           pchBufferEnd;
   zLONG            lHierCount;
   zBOOL            bInterlinking = FALSE;
   LPENTITYINSTANCE lpEntityInstance;
   LPVIEWOI         lpViewOI;
   LPVIEWCSR        lpViewCsr;
   zCHAR            cOI_Linked[ 400 ];  // We can handle 400 OIs.

   *ppchLinkBuffer  = 0;
   *plLinkBufferLth = 0;

   // If we have only 1 view there can't be any interlinking...
   if ( nViewCount <= 1 )
      return( 0 );

   // First set the hier count for all the EIs.  Also check to make sure that
   // there is interlinking between OIs.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewArray[ k ] == 0 )
         continue;

      lHierCount = 0;
      lpViewCsr  = zGETPTR( lpViewArray[ k ]->hViewCsr );
      lpViewOI   = zGETPTR( lpViewCsr->hViewOI );
      for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         LPENTITYINSTANCE lpLinked;

         if ( fnEntityInstanceIsDead( lpEntityInstance ) )
            continue;

         lpEntityInstance->lHierCount = lHierCount++;

         // Check to see if the current EI is linked with an EI in one of the
         // other OIs.  If bInterlinking is TRUE then we already know that
         // there is interlinking between the OIs so skip it.  (We still need
         // to loop through the entity instances to set their hier #)
         if ( bInterlinking || lpEntityInstance->hNextLinked == 0 )
            continue;

         // Loop through each of the linked instances and see if there is
         // any interlinking.  Stop looping if we find that there is
         // interlinking.
         for ( lpLinked = zGETPTR( lpEntityInstance->hNextLinked );
               lpLinked != lpEntityInstance && bInterlinking == FALSE;
               lpLinked = zGETPTR( lpLinked->hNextLinked ) )
         {
            zSHORT j;

            // Don't look at EI's that are part of the same OI.
            if ( lpLinked->hViewOI == lpViewCsr->hViewOI )
               continue;

            // See if the linked instance belongs to another OI.
            for ( j = 0; j < nViewCount; j++ )
            {
               LPVIEWCSR lpTempViewCsr;

               if ( lpViewArray[ j ] == 0 )
                  continue;

               lpTempViewCsr = zGETPTR( lpViewArray[ j ]->hViewCsr );
               if ( lpTempViewCsr->hViewOI == lpLinked->hViewOI )
               {
                  // We have a match--set flag and get out.
                  bInterlinking = TRUE;
                  break;
               }

            } // for ( j...)...

         } // for ( lpLinked...)...

      } // for ( lpEntityInstance...)...

   } // for ( k...)...

   // If there is no interlinking between the OIs then there's nothing more to do.
   if ( bInterlinking == FALSE )
      return( 0 );

   // We now know that there is interlinking between the OIs.  Create the
   // buffer and set it so we can re-link the instances later.

   pchLinkBuffer = (zPCHAR) fnAllocDataspace( lpTask->hFirstDataHeader,
                                              LINK_BUFFER_SIZE, FALSE, 0, 0 );
   if ( pchLinkBuffer == 0 )
      return( zCALL_ERROR );

   pchLinkBuffer   = zGETPTR( pchLinkBuffer );
   *ppchLinkBuffer = pchBufferEnd = pchLinkBuffer;

   // Loop through all the EI's again.  This time we'll start adding link info.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewArray[ k ] == 0 )
         continue;

      lpViewCsr  = zGETPTR( lpViewArray[ k ]->hViewCsr );
      lpViewOI   = zGETPTR( lpViewCsr->hViewOI );
      for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         zSHORT           nLinkInfo;
         zPCHAR           pchSave;
         LPENTITYINSTANCE lpLinked;

         // Don't bother with an entity that isn't linked.
         if ( lpEntityInstance->hNextLinked == 0 )
            continue;

         // Don't bother with a dead entity.
         if ( fnEntityInstanceIsDead( lpEntityInstance ) )
            continue;

         // Assume that we don't have to create link information for the
         // current EI.  nLinkInfo can be:
         //   0 - Means that no interlinks have been found.
         //   1 - Interlink has been found--add info to link buffer.
         //   2 - A link has been found but it belongs to an OI that we've
         //       already searched.  This means that info has already been
         //       added to the link buffer for the current EI.
         // pchSave saves the current position of pchBufferEnd in case we have
         // to go back to it.
         nLinkInfo = 0;
         pchSave   = pchBufferEnd;

         // Set table to all 0's to indicate that for this linked-list chain
         // we haven't linked any OIs yet.
         zmemset( cOI_Linked, 0, zsizeof( cOI_Linked ) );

         // Loop through each of the linked instances and see if there is
         // any interlinking.  Stop looping if we find that there is interlinking.
         for ( lpLinked = zGETPTR( lpEntityInstance->hNextLinked );
               lpLinked != lpEntityInstance;
               lpLinked = zGETPTR( lpLinked->hNextLinked ) )
         {
            zSHORT j;

            // Don't look at EI's that are part of the same OI.
            if ( lpLinked->hViewOI == lpViewCsr->hViewOI )
               continue;

            // See if the linked instance belongs to another OI.
            for ( j = 0; j < nViewCount; j++ )
            {
               LPVIEWCSR lpTempViewCsr;

               if ( lpViewArray[ j ] == 0 )
                  continue;

               // If lpLinked is not part of the OI specified by lpViewArray[ j ] then skip it.
               lpTempViewCsr = zGETPTR( lpViewArray[ j ]->hViewCsr );
               if ( lpTempViewCsr->hViewOI != lpLinked->hViewOI )
                  continue;

               // At this point 'k' is the index pointing to the lpView for
               // lpEntityInstance and 'j' is the index pointing to the lpView that lpLinked is part of.
               if ( j < k )
               {
                  // We've found an interlink but lpLinked belongs to an
                  // OI that we've already searched.  This means that we've
                  // already added info to the link buffer and doesn't need
                  // to be done for the current set of linked instances.
                  nLinkInfo = 2;
                  break;
               }

               // Check to see if we've already found a linked EI in this view.  We only need to
               // find 1 since all the linked EIs in the OI are already linked together.
               if ( cOI_Linked[ j ] == TRUE )
                  break;

               // Set flag to indicate we've linked this OI.
               cOI_Linked[ j ] = TRUE;

               // If this is the first EI that we've found add a paren to start things and then add lpEntityInstance.
               if ( nLinkInfo == 0 )
               {
                  *pchBufferEnd++ = '(';
                  sprintf_s( pchBufferEnd, LINK_BUFFER_SIZE - (pchBufferEnd - pchLinkBuffer), "%x:%lx", k, lpEntityInstance->lHierCount );
                  pchBufferEnd += zstrlen( pchBufferEnd );
               }

               // Add a slash to seperate EI data.
               *pchBufferEnd++ = '/';

               // Set flag to indicate that we've found interlinking and that we're adding it to the buffer.
               nLinkInfo = 1;

               //
               sprintf_s( pchBufferEnd, LINK_BUFFER_SIZE - (pchBufferEnd - pchLinkBuffer), "%x:%lx", j, lpLinked->lHierCount );
               pchBufferEnd += zstrlen( pchBufferEnd );

            } // for ( j...)...

            if ( nLinkInfo == 2 )
               break;

         } // for ( lpLinked...)...

         // If nLinkInfo is 2 then we don't need to add information to the link buffer for the current entity so reset pchBufferEnd.
         if ( nLinkInfo == 2 )
            pchBufferEnd = pchSave;
         else
         if ( nLinkInfo == 1 )
            *pchBufferEnd++ = ')';

      } // for ( lpEntityInstance...)...

   } // for ( k...)...

   *pchBufferEnd++ = 0;

   *plLinkBufferLth = (zLONG) (pchBufferEnd - pchLinkBuffer);
// TraceBuffer( "(kzoeneta) ** LinkBuffer = ", pchLinkBuffer,
//              (zSHORT) *plLinkBufferLth );

   return( 0 );

} // fnSetLinkBuffer

/*

   This op tries to merge a view located on the local machine with a view
   returned from a server.

   We can't just drop the old view because that will invalidate all other views to the OI referenced
   by vOld.  In addition, all the names for vOld will be dropped.  Lastly, it will not "update" any linked instances.

   If we merge the changes from vNew to vOld then all the views to the OI will still be valid,
   the view names will be preserved, and the linked instances will also be "updated".

*/
zSHORT LOCALOPER
fnMergeViews( zVIEW vNew, zVIEW vOld )
{
   LPVIEWCSR         lpOldViewCsr = zGETPTR( vOld->hViewCsr );
   LPVIEWOI          lpOldViewOI  = zGETPTR( lpOldViewCsr->hViewOI );
   LPVIEWCSR         lpNewViewCsr = zGETPTR( vNew->hViewCsr );
   LPVIEWOI          lpNewViewOI  = zGETPTR( lpNewViewCsr->hViewOI );
   LPENTITYINSTANCE  lpNew;
   LPENTITYINSTANCE  lpOld;
   zBOOL             bGetNextOld;

#ifdef DEBUG
   LPVIEWOD          lpViewOD = zGETPTR( vNew->hViewOD );
#endif

   // Loop through each entity instance and merge data from new to old.

   // Loop through all the old instances and try to merge the new instances.
   lpNew = zGETPTR( lpNewViewOI->hRootEntityInstance );
   for ( lpOld = zGETPTR( lpOldViewOI->hRootEntityInstance );
         lpOld;
         lpOld = (bGetNextOld ? zGETPTR( lpOld->hNextHier ) : lpOld) )
   {
      LPVIEWENTITY lpViewEntity;
      LPVIEWATTRIB lpViewAttrib;

      // We'll assume here that the next iteration of the 'for' loop should get the next lpOld.
      bGetNextOld = TRUE;

      // Skip old entity instances if they are "dead".  If they are dead then
      // they were not sent to the server so they won't show up in the new OI.
      while ( lpOld && fnEntityInstanceIsDead( lpOld ) )
         lpOld = zGETPTR( lpOld->hNextHier );

      if ( lpOld == 0 )
         break;

      // Compare the tag of the new instance with the pointer of the old
      // instance.  If they are not the same then something happened:
      // o  A commit object operation on the server created or deleted an
      //    entity.
      if ( (zLONG) lpOld != lpNew->lTag )
      {
         zLONG lSomethingNeedsToBeDoneHere;

         // We'll worry about handling server commit operations that create/delete entities later.
         // For now we'll just assume that lpOld wasn't sent to the server...so skip it.

         // NOTE: We can determine if the lpNew entity was created on the server by checking the value
         // of lpNew->lTag.  If it is 0 then the entity was created on the server.

         lpViewEntity = zGETPTR( lpOld->hViewEntity );
         TraceLineS( "(merge) Tags don't match! Old entity = ", lpViewEntity->szName );
         lpViewEntity = zGETPTR( lpNew->hViewEntity );
         TraceLineS( "(merge) Tags don't match! New entity = ", lpViewEntity->szName );
         TraceLineX( "(merge) lpOld       = ", (zLONG) lpOld );
         TraceLineX( "(merge) lpNew->lTag = ", lpNew->lTag );

         continue;
      }

      // If we get here then the tag for the new entity matches the pointer for the old entity.  They must be the same instance.
      lpViewEntity = zGETPTR( lpOld->hViewEntity );
      if ( lpViewEntity->bDerived == FALSE &&
           lpViewEntity->bDerivedPath == FALSE &&
           lpViewEntity->bHasDB_Oper == FALSE ) // added Phil/Doug 2005.10.17
      {
         // Copy each of the attribute values.
         for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
               lpViewAttrib;
               lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
         {
            zPVOID        lpValue;
            zULONG        uLth;
            LPATTRIBFLAGS lpOldAttribFlags;
            LPATTRIBFLAGS lpNewAttribFlags;

            if ( lpViewAttrib->bPersist == FALSE )
               continue;

            fnGetAttrAddrFromEntityInstance( (zCOREMEM) &lpValue, &uLth, lpNew, lpViewAttrib );
            fnStoreValueInEntityInstance( lpOld, lpViewEntity, lpViewAttrib, lpValue, uLth );

            lpNewAttribFlags = fnGetAttribFlagsPtr( lpNew, lpViewAttrib );
            lpOldAttribFlags = fnGetAttribFlagsPtr( lpOld, lpViewAttrib );
            lpOldAttribFlags->u.uFlags = lpNewAttribFlags->u.uFlags;

         } // for...
      }

      lpOld->u.nIndicators = lpNew->u.nIndicators;

      lpNew = zGETPTR( lpNew->hNextHier );
      if ( lpNew == 0 )
         break;

   } // for ( lpOld )...

   if ( lpNew )
   {
      zLONG        lSomethingNeedsToBeDoneHereToo;
      LPVIEWENTITY lpViewEntity;

      // If we get here then we've gone through all the old entities but we
      // still have new entities left.  This means that some entities were
      // created on the server.  We should merge them in.
      lpViewEntity = zGETPTR( lpNew->hViewEntity );
      TraceLineS( "(merge) Extra New entity! = ", lpViewEntity->szName );
      TraceLineX( "(merge) lpNew->lTag = ", lpNew->lTag );
   }

   // Now loop through again but just copy the EI flags.

   lpNew = zGETPTR( lpNewViewOI->hRootEntityInstance );
   for ( lpOld = zGETPTR( lpOldViewOI->hRootEntityInstance );
         lpOld;
         lpOld = ( bGetNextOld ? zGETPTR( lpOld->hNextHier ) : lpOld ) )
   {
      // We'll assume here that the next iteration of the 'for' loop should
      // get the next lpOld.
      bGetNextOld = TRUE;

      while ( lpOld && fnEntityInstanceIsDead( lpOld ) )
         lpOld = zGETPTR( lpOld->hNextHier );

      if ( lpOld == 0 )
         break;

      // Compare the tag of the new instance with the pointer of the old
      // instance.  If they are not the same then one of two things happened:
      // o  For some reason lpOld wasn't sent to the server--maybe it's
      //    dead.
      // o  A commit object operation on the server created or deleted an
      //    entity.
      if ( (zLONG) lpOld != lpNew->lTag )
         continue;

      // If we get here then the tag for the new entity matches the pointer
      // for the old entity.  They must be the same instance.

      lpOld->u.nIndicators = lpNew->u.nIndicators;

      lpNew = zGETPTR( lpNew->hNextHier );
      if ( lpNew == 0 )
         break;

   } // for ( lpOld )...

   return( 0 );

} // fnMergeViews

//./ ADD NAME=NetCommitOI
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetCommitOI
//
//  PURPOSE:     To commit an OI to a remote computer.
//
//  DESCRIPTION: This operation commits an OI across the network.
//               Other than pchNetworkName, this operation is used exactly
//               like CommitObjectInstance.
//
//               NOTE: This operation is currently assumed to be an
//               internal operation (e.g. it is called only from Core) and
//               therefore does NO validity checking.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               pchAddress     - Address of server.
//
//               We have lpViewCluster so that we know the control values
//               for each of the views but we use lpViewArray because it
//               contains a list of the views that we need to send--we don't
//               send OIs that haven't been changed, for example.
//
//               For a description of the rest of the arguments, see
//               CommitObjectInstance.
//
//  RETURNS:     zCALL_ERROR - Error activating object.
//               Otherwise see return codes for CommitObjectInstance.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zSHORT OPERATION
NetCommitOI( zPCHAR        pchNetworkName,
             zPCHAR        pchAddress,
             LPVIEWCLUSTER lpViewCluster,
             zVIEW         lpViewArray[],
             zSHORT        nViewCount,
             zPSHORT       pnViewErrorIdx,
             zLONG         lControl )
{
   zSHORT        nRC = zCALL_ERROR;
   zSHORT        k;
   zVIEW         vSubtask = 0;
   zCHAR         cPacketType;
   zLONG         lPacketData;
   LPNETWORK     lpNetwork;
   zPVOID        pvConn = 0;
   LPVIEWOD      lpReferenceViewOD;
   LPVIEWOD      lpViewOD;
   LPVIEWCSR     lpViewCsr;
   zCommitPacket CommitPacket;
   LPTASK        lpTask;
   zVIEW         vReferenceView = 0;
   zVIEW         lpTaskView = 0;
   zPCHAR        pchObjectNameBuffer = 0;
   zPCHAR        pch;
   zSHORT        nObjectNameLth;
   zBOOL         bConnectionMade = FALSE;
   zPVIEW        lpNewViewArray = 0;
   zPCHAR        pchLinkBuffer = 0;
   zLONG         lLinkBufferLth;
   zCHAR         szServer[ 256 ] = "";
   zCHAR         szAppName[ zZEIDON_NAME_LTH + 1 ];
   ServDirCommitRecord CommitInfo;

   // Find a view that can be used as the task view.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewArray[ k ] )
      {
         lpTaskView = lpViewArray[ k ];
         break;
      }
   }

   // No views to commit? Just return.
   if ( lpTaskView == 0 )
      return( 0 );

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetCommitOI, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetCommitOI, lpTask );
      return( zCALL_ERROR );
   }

   // Create a buffer to store object names.  We'll arbitrarily allocate 32000 bytes.
   pchObjectNameBuffer = (zPCHAR) fnAllocDataspace( lpTask->hFirstDataHeader, 32000, TRUE, 0, 0 );
   pchObjectNameBuffer = zGETPTR( pchObjectNameBuffer );
   pch = pchObjectNameBuffer;

   // The reference view is just the last valid view in the array.
   for ( k = 0; k < nViewCount; k++ )
   {
      LPENTITYINSTANCE lpEntityInstance;
      LPVIEWOI         lpViewOI;
      zBOOL            bChanged;

      if ( lpViewArray[ k ] == 0 )
      {
         // Store a 0 for the object name.
         if ( nViewCount > 1 )
            *pch++ = 0;

         continue;
      }

      lpViewOD  = zGETPTR( lpViewArray[ k ]->hViewOD );
      lpViewCsr = zGETPTR( lpViewArray[ k ]->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      // If OI hasn't been updated then forget about it UNLESS...
      // there is pessimistic locking.  Then we need to continue so that any
      // pessimistic locks are dropped.
      if ( (lpViewOI->lActivateControl & zACTIVATE_WITH_LOCKING) == 0 )
      {
         bChanged  = FALSE;
         if ( lpViewOI->bUpdated )
         {
            // Make sure that the OI really is changed.
            for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
                  lpEntityInstance;
                  lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
            {
               // If the entity is created AND deleted then the OI really
               // hasn't changed.
               if ( lpEntityInstance->u.nInd.bCreated  &&
                    lpEntityInstance->u.nInd.bDeleted )
               {
                  continue;
               }

               // If the entity is included AND excluded then the OI really
               // hasn't changed.
               if ( lpEntityInstance->u.nInd.bIncluded && lpEntityInstance->u.nInd.bExcluded )
               {
                  continue;
               }

               if ( lpEntityInstance->u.nInd.bUpdated  ||
                    lpEntityInstance->u.nInd.bCreated  ||
                    lpEntityInstance->u.nInd.bDeleted  ||
                    lpEntityInstance->u.nInd.bIncluded ||
                    lpEntityInstance->u.nInd.bExcluded )
               {
                  bChanged = TRUE;
                  break;
               }
            } // for...
         } // if ( lpViewOI->bUpdated )...

         if ( bChanged == FALSE )
         {
            // View isn't really changed so forget it.
            lpViewArray[ k ] = 0;

            // Store a 0 for the object name.
            if ( nViewCount > 1 )
               *pch++ = 0;

            // Get rid of entity instances that are dead--instances that
            // have been created AND deleted, etc.
            fnReclaimHiddenInstances( lpViewOI );

            lpViewOI->bUpdated = lpViewOI->bUpdatedFile = FALSE;

            continue;
         }
      }

      if ( vReferenceView == 0 )
      {
         vReferenceView    = lpViewArray[ k ];
         lpReferenceViewOD = lpViewOD;
      }

      // Store the object name.
      pch = zstrcpyp( pch, 32000 - (pch - pchObjectNameBuffer), lpViewOD->szName );
      pch++;  // Skip past null terminator.

      // Get rid of entity instances that are dead--instances that
      // have been created AND deleted, etc.
      fnReclaimHiddenInstances( lpViewOI );
   }

   // If vReferenceView is 0 then we didn't find any OIs that have changes so
   // we can forget about committing anything.
   if ( vReferenceView == 0 )
   {
      nRC = 0;
      goto EndOfFunction;
   }

   fnRetrieveAppName( vReferenceView, szAppName );
   SfCreateSubtask( &vSubtask, vReferenceView, szAppName );

   // Set up info for commit request.
   CommitInfo.pszNetworkName         = lpNetwork->szNetworkName;
   CommitInfo.vOI                    = vReferenceView;
   CommitInfo.lControl               = lControl;
   CommitInfo.pszUserSuppliedAddress = pchAddress;

   // Open connection.
   if ( fnAddConnectionToNetwork( lpTask, lpNetwork, szServer, &pvConn, TRUE,
                                  zAPPLREQ_COMMIT, &CommitInfo, lpTaskView ) < 0 )
   {
      nRC = zNETWORK_ERROR;
      goto EndOfFunction;
   }

   bConnectionMade = TRUE;

   if ( lpNetwork->nTraceLevel > 1 )
      TraceLineS( "(kzoeneta) ** Sending Commit OI packet", "" );

   //=======================================================================
   // Transmitting data.
   //
   // Until further notice, the following code only SENDS data over the
   // network.
   //=======================================================================

   // First send the header for the server driver and then the regular
   // packet for the function structure.
   if ( fnSendHeaderPacket( lpNetwork, &pvConn, zPACKET_COMMITOI, szAppName ) != 0 )
   {
      goto EndOfFunction;
   }

   if ( fnSendTraceSwitches( lpNetwork, &pvConn, lpTask ) != 0 )
      goto EndOfFunction;

   if ( fnSendDataPacket( lpNetwork, &pvConn, zPACKET_COMMITOI, 0 ) != 0 )
      goto EndOfFunction;

   // Set up the commit information.  We initialize the structure to 0's so
   // that the network stack can better compress the data.
   zmemset( &CommitPacket, 0, sizeof( zCommitPacket ) );
   strcpy_s( CommitPacket.szVersion, zsizeof( CommitPacket.szVersion ), zCURRENT_PROTOCOL_VERSION );
   strcpy_s( CommitPacket.szAppName, zsizeof( CommitPacket.szAppName ), szAppName );
   SysGetUserID( lpTaskView, CommitPacket.szUserName, zsizeof( CommitPacket.szUserName ), CommitPacket.szPassword, zsizeof( CommitPacket.szPassword ) );
   zltox( nViewCount, CommitPacket.szViewCount, zsizeof( CommitPacket.szViewCount ) );
   zltox( lControl, CommitPacket.szControl, zsizeof( CommitPacket.szControl ) );

   nObjectNameLth = (zSHORT) (pch - pchObjectNameBuffer);
   zltox( (zLONG) nObjectNameLth, CommitPacket.szObjectNameLth, zsizeof( CommitPacket.szObjectNameLth ) );

   // Set up the link buffer.  This buffer contains a list of all entity
   // instances that are linked with each other in lpViewArray.
   fnSetLinkBuffer( lpTask, lpViewArray, nViewCount, &pchLinkBuffer, &lLinkBufferLth );

   zltox( lLinkBufferLth, CommitPacket.szLinkBufferLth, zsizeof( CommitPacket.szLinkBufferLth ) );

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLine( "(kzoeneta) ** Appl Name: %s  User Name: %s ", CommitPacket.szAppName, CommitPacket.szUserName );
      if ( nViewCount > 1 )
      {
         TraceLine( "(kzoeneta) ** View Count: %s  OD Name Lth: %d", CommitPacket.szViewCount, nObjectNameLth );
         TraceBuffer( "(kzoeneta) ** OD Names: ", pchObjectNameBuffer, nObjectNameLth );
      }

      TraceLineS( "(kzoeneta) ** LB Lth: ", CommitPacket.szLinkBufferLth );
   }

   // Send server commit info.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn, &CommitPacket,
                                sizeof( zCommitPacket ), zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   // Send the object names.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn, pchObjectNameBuffer,
                                nObjectNameLth, zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   // Send the link buffer info if we have any.
   if ( lLinkBufferLth > 0 )
   {
      if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn,
                                   pchLinkBuffer, lLinkBufferLth, zTYPE_STRING ) != 0 )
      {
         goto EndOfFunction;
      }
   }

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Sending OIs to commit", "" );

   // Send the OIs to the server to be committed.  Send entity tags so we can
   // compare/merge later.
   for ( k = 0; k < nViewCount; k++ )
   {
      zCHAR szControl[ 10 ];
      zCHAR szLth[ 5 ];
      zLONG lLth;

      if ( lpViewArray[ k ] == 0 )
         continue;

      if ( fnSendOI( &pvConn, lpNetwork, lpViewArray[ k ],
                     zINCREMENTAL | zENTITY_TAGS ) == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Error sending OI for Commit!", "" );
         goto EndOfFunction;
      }

      // Send the control value for the view.  We'll store the length of the
      // string containing the control value in the first 2 bytes.  We'll assume
      // that the length can be sent as a 2-digit hex value.
      zltox( lpViewCluster[ k ].lControl, szControl + 2, zsizeof( szControl ) - 2 );
      lLth = zstrlen( &szControl[ 2 ] ) + 1;
      zltox( lLth, szLth, zsizeof( szLth ) );
      szControl[ 0 ] = szLth[ 0 ];  // Copy lth to first two bytes.
      szControl[ 1 ] = szLth[ 1 ];

      // First, send the length, then the data.
      //  The strings must be written and read synchronously.
      //  According to network handler interface, you cannot write
      //  length + data information in one message and retrieve it
      //  in two messages.
      if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn,
                                   szControl, 2, zTYPE_STRING ) != 0 )
      {
         goto EndOfFunction;
      }

      if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn,
                                   szControl + 2, lLth, zTYPE_STRING ) != 0 )
      {
         goto EndOfFunction;
      }
   }

   // Tell network handler to flush the send buffer.
   if ( fnFlushBuffer( lpNetwork, &pvConn ) != 0 )
      goto EndOfFunction;

   //=======================================================================
   // Receiving data.
   //
   // From here until we close the connection we will only RECEIVE data over
   // the network.
   //=======================================================================

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Waiting for returned OI", "" );

   // Wait for Ack.
   if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
      goto EndOfFunction;
   }

   if ( cPacketType == zPACKET_RC )
   {
      // If we received the RC packet, then there was an error committing
      // the OIs on the server.  Get the return code and go to the end of the
      // function.
      if ( lpNetwork->nTraceLevel > 0 )
         TraceLineS( "(kzoeneta) ** Received RC - error in Commit", "" );

      nRC = (zSHORT) lPacketData;

      // Get the index that indicates what view wasn't committed.
      if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      if ( pnViewErrorIdx )
         *pnViewErrorIdx = (zSHORT) lPacketData;

      goto EndOfFunction;
   }

   // Allocate an array for the incoming views.
   lpNewViewArray = (zPVIEW) fnAllocDataspace( lpTask->hFirstDataHeader,
                                               sizeof( zVIEW ) * (zULONG) nViewCount,
                                               TRUE, 0, 0 );
   lpNewViewArray = zGETPTR( lpNewViewArray );

   // Retrieve all the views.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewArray[ k ] == 0 )
         continue;

      lpViewOD = zGETPTR( lpViewArray[ k ]->hViewOD );

      if ( cPacketType == zPACKET_EMPTYOI )
      {
         // Nothing needs to be done here.
         // The server committed the OI but the root must have been deleted
         // because the resulting OI is empty.  Since we don't want to send an
         // empty OI back we'll just skip it.
      }
      else
      if ( cPacketType == zPACKET_ACK )
      {
         // The server committed the OI and now must send back the resulting OI.
         if ( fnReceiveOI( &pvConn, lpNetwork, &lpNewViewArray[ k ],
                           lpViewArray[ k ], lpViewOD->szName,
                           zMULTIPLE ) == zCALL_ERROR )
         {
            TraceLineS( "(kzoeneta) ** Error receiving OI after commit!", "" );
            goto EndOfFunction;
         }
      }
      else
      {
         TraceLineS( "(kzoeneta) ** Received bytes but no ACK!", "" );
         goto EndOfFunction;
      }

      // Get the next packet.
      if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
         goto EndOfFunction;
      }

   } // for ( k...)...

   if ( cPacketType != zPACKET_RC )
   {
      TraceLineS( "(kzoeneta) ** No return code for Commit!", "" );
      goto EndOfFunction;
   }

   nRC = (zSHORT) lPacketData;

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineI( "(kzoeneta) ** RC from commit = ", nRC );

   //=======================================================================
   // We have sent the user's OIs (lpViewArray) to the server and they've been
   // committed and sent back to us (as lpNewViewArray).  We must now merge the
   // changes from new to lpView.  We can't just drop lpView because that will
   // invalidate all other views to the OI referenced by lpView.  In addition,
   // all the names for lpView will be dropped.  Lastly, it will not "update"
   // any linked instances.
   //
   // If we merge the changes from vNew to lpView, then all the views to
   // the OI will still be valid, the view names will be preserved, and the
   // linked instances will also be "updated".
   //=======================================================================

   for ( k = 0; k < nViewCount; k++ )
   {
      LPVIEWCSR lpViewCsr;
      LPVIEWOI  lpViewOI;
      LPVIEWOI  lpNewViewOI;

      if ( lpNewViewArray[ k ] == 0 )
         continue;

      if ( fnMergeViews( lpNewViewArray[ k ],
                         lpViewArray[ k ] ) == zCALL_ERROR )
      {
         nRC = zCALL_ERROR;
         continue;
      }

      // Call operation to clean up the OI. This will also drop
      // all the deleted/excluded entity instances.
      fnCleanupInstance( lpViewArray[ k ], 1 );

      // Turn off the update flags.
      lpViewCsr = zGETPTR( lpViewArray[ k ]->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
      lpViewOI->bUpdated = lpViewOI->bUpdatedFile = FALSE;

      lpViewCsr   = zGETPTR( lpNewViewArray[ k ]->hViewCsr );
      lpNewViewOI = zGETPTR( lpViewCsr->hViewOI );
      lpViewOI->bIsLocked = lpNewViewOI->bIsLocked;

   } // for k...

EndOfFunction:
   if ( vSubtask && bConnectionMade &&
        fnRetrieveMsgAndTraceObj( lpNetwork, &pvConn, vReferenceView ) < 0 )
   {
      nRC = zCALL_ERROR;
   }

   if ( bConnectionMade &&
        fnRemoveConnectionFromNetwork( lpNetwork, &pvConn, TRUE ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
   }

   if ( vSubtask )
      DROPSUBTASK( vSubtask );

   if ( pchObjectNameBuffer )
      fnFreeDataspace( pchObjectNameBuffer );

   if ( pchLinkBuffer )
      fnFreeDataspace( pchLinkBuffer );

   if ( lpNewViewArray )
   {
      for ( k = 0; k < nViewCount; k++ )
      {
         LPVIEWOI lpViewOI;

         if ( lpNewViewArray[ k ] == 0 )
            continue;

         lpViewCsr = zGETPTR( lpNewViewArray[ k ]->hViewCsr );
         lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

         // To keep any possible pessimistic locks from being dropped let's
         // turn off the bIsLocked flag.  Note that this only happens if the
         // user indicated that locks are to be left in place after the commit.
         lpViewOI->bIsLocked = 0;

         fnDropView( lpNewViewArray[ k ] );
      }

      fnFreeDataspace( lpNewViewArray );
   }

   fnOperationReturn( iNetCommitOI, lpTask );
   return( nRC );

} // NetCommitOI

//./ ADD NAME=NetCommitOI_ToFile
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetCommitOI_ToFile
//
//  PURPOSE:     To commit an OI to a remote computer.
//
//  DESCRIPTION: This operation commits an OI to a file across the network.
//               Other than pchNetworkName, this operation is used exactly
//               like CommitOI_ToFile.
//
//               NOTE: This operation is currently assumed to be an
//               internal operation (e.g. it is called only from Core) and
//               therefore does NO validity checking.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               pchAddress     - Address of server.  If 0 then use LAD.
//
//               For a description of the rest of the arguments, see
//               CommitOI_ToFile.
//
//  RETURNS:     zCALL_ERROR - Error activating object.
//               Otherwise see return codes for CommitOI_ToFile.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zSHORT OPERATION
NetCommitOI_ToFile( zPCHAR  pchNetworkName,
                    zPCHAR  pchAddress,
                    zVIEW   lpView,
                    zPCHAR  pchFileName,
                    zLONG   lControl )
{
   return( 0 );

// 2001.06.28
// DGC Not supported at the moment (security risk).
#if 0
   zSHORT        nRC = zCALL_ERROR;
   zCHAR         cPacketType;
   zLONG         lPacketData;
   LPNETWORK     lpNetwork;
   zPVOID        pvConn = 0;
   zCommitPacket CommitPacket;
   LPTASK        lpTask;
   LPVIEWOD      lpViewOD;
   LAD_InfoRecord LAD_Info;

   zmemset( &LAD_Info, 0, zsizeof( LAD_Info ) );

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetCommitOI_ToFile ... )) == 0 )
      return( zCALL_ERROR );

   if ( fnValidView( lpTask, lpView ) == 0 )
   {
      fnOperationReturn( iNetCommitOI_ToFile, lpTask );
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetCommitOI_ToFile, lpTask );
      return( zCALL_ERROR );
   }

   lpViewOD = zGETPTR( lpView->hViewOD );

   LAD_Info.lpTask     = lpTask;
   LAD_Info.lpNetwork  = lpNetwork;
   LAD_Info.nObjType   = zLADTYPE_LOD_COMMIT_FILE;
   LAD_Info.pchObjName = lpViewOD->szName;
   fnRetrieveAppName( lpView, LAD_Info.szAppName );
   SysGetUserID( lpView, LAD_Info.szUserName, zsizeof( LAD_Info.szUserName ), LAD_Info.szPassword, zsizeof( LAD_Info.szPassword ) );

   if ( fnGetApplAddress( &LAD_Info, pchAddress ) == zCALL_ERROR )
   {
      fnOperationReturn( iNetCommitOI_ToFile, lpTask );
      return( zCALL_ERROR );
   }

   // Open connection.
   if ( fnAddConnectionToNetwork( &LAD_Info, &pvConn, TRUE, lpView ) == zCALL_ERROR )  not used
   {
      fnOperationReturn( iNetCommitOI_ToFile, lpTask );
      return( zCALL_ERROR );
   }

   if ( lpNetwork->nTraceLevel > 1 )
      TraceLineS( "(kzoeneta) ** Sending Commit OI packet", "" );

   //=======================================================================
   // Transmitting data.
   //
   // Until further notice, the following code only SENDS data over the
   // network.
   //=======================================================================

   // First send the header for the server driver and then the regular
   // packet for the function structure.
   if ( fnSendHeaderPacket( lpNetwork, &pvConn, zPACKET_COMMITOITOFILE,
                            LAD_Info.szAppName ) != 0 )
   {
      goto EndOfFunction;
   }

   if ( fnSendTraceSwitches( lpNetwork, &pvConn, lpTask) != 0)
      goto EndOfFunction;

   if ( fnSendDataPacket( lpNetwork, &pvConn, zPACKET_COMMITOITOFILE, 0 ) != 0 )
      goto EndOfFunction;

   // Set up the commit information.  We initialize the structure to 0's so
   // that the network stack can better compress the data.
   zmemset( &CommitPacket, 0, zsizeof( zCommitPacket ) );
   strcpy_s( CommitPacket.szVersion, zCURRENT_PROTOCOL_VERSION );
   strcpy_s( CommitPacket.szObjectDef, lpViewOD->szName );
   zltox( lControl, CommitPacket.szControl );
   zltox( (zLONG) zstrlen( pchFileName ) + 1, CommitPacket.szFileNameLth );
   strcpy_s( CommitPacket.szAppName, LAD_Info.szAppName );
   SysGetUserID( lpView, CommitPacket.szUserName, zsizeof( CommitPacket.szUserName ), CommitPacket.szPassword, zsizeof( CommitPacket.szPassword ) );

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Appl Name: %s  Object Def: %s  "
                    "User Name: %s  File Name: %s",
                  CommitPacket.szAppName, CommitPacket.szObjectDef,
                  CommitPacket.szUserName, pchFileName );
   }

   // Send server commit info.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn,
                                &CommitPacket, zsizeof( zCommitPacket ),
                                zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   // Send server file name.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn,
                                pchFileName, zstrlen( pchFileName ) + 1,
                                zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Sending OI to commit file", "" );

   // Send the OI to the server to be committed.
   if ( fnSendOI( &pvConn, lpNetwork, lpView, zINCREMENTAL ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Error sending OI for Commit!", "" );
      goto EndOfFunction;
   }

   // Tell network handler to flush the send buffer.
   if ( fnFlushBuffer( lpNetwork, &pvConn ) != 0 )
      goto EndOfFunction;

   //=======================================================================
   // Receiving data.
   //
   // From here until we close the connection we will only RECEIVE data over
   // the network.
   //=======================================================================

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Waiting for ACK", "" );

   // Wait for return code.
   if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
      goto EndOfFunction;
   }

   if ( cPacketType != zPACKET_RC )
   {
      TraceLineS( "(kzoeneta) ** No return code for CommitOI_ToFile!", "" );
      goto EndOfFunction;
   }

   nRC = (zSHORT) lPacketData;

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineI( "(kzoeneta) ** RC from commit OI to file = ", nRC );

   if ( fnRetrieveMsgAndTraceObj( lpNetwork, &pvConn, lpView ) < 0 )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

EndOfFunction:
   if ( fnRemoveConnectionFromNetwork( lpNetwork, &pvConn,
                                       TRUE ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
   }

   fnOperationReturn( iNetCommitOI_ToFile, lpTask );
   return( nRC );
#endif

} // NetCommitOI_ToFile

//./ ADD NAME=NetCallOperation
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetCallOperation
//
//  PURPOSE:     To call a transformation on a remote computer.
//
//  DESCRIPTION:
//
//               NOTE: This operation is currently assumed to be an
//               internal operation (e.g. it is called only from Core) and
//               therefore does NO validity checking.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               pchAddress     - Address of server.
//               vSubtask       - Subtask view pointing to application.
//               bTransformation - If TRUE then oper is a transformation.
//               pchInfo        - If bTransformation is TRUE, then this
//                                is the LOD name otherwise it is the DLL
//                                name of the operation.
//               pchOperName    - Name of the operation.
//               plRC           - Return code from operation.
//               pchArgList     - Description of args for operation.  The
//                                first one describes the return type.  It is
//                                a string describing the the type of each
//                                arg with the following values:
//                                  a - String containing Host address.
//                                  l - String containing local address.
//                                  S - Any string.
//                                  Y - Byte.
//                                  L - Long integer.
//                                  M, R - Decimal.
//                                  N - Short integer.
//                                  O - (for return type only) No return value.
//                                  F - Float.
//                                  T - Timestamp (NOT SUPPORTED YET).
//                                  D - Date (NOT SUPPORTED YET).
//                                  H - Time (NOT SUPPORTED YET).
//                                  B - Blob (NOT SUPPORTED YET).
//                                  V - Any view.
//                                If any of these values are prefixed by a
//                                'p' then the argument is a pointer to the
//                                type.
//
//               ...            - Additional args (if any) described by
//                                pchArgList.
//
//  RETURNS:     zCALL_ERROR - Error activating object.
//               Otherwise see return codes for CommitOI_ToFile.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zSHORT VARYOPER
NetCallOperation( zPCHAR   pchNetworkName,
                  zPCHAR   pchAddress,
                  zVIEW    vSubtask,
                  zBOOL    bTransformation,
                  zPCHAR   pchInfo,
                  zPCHAR   pchOperName,
                  zPVOID   pvReturn,
                  zPCHAR   pchArgList, ... )
{
   LPNETWORK     lpNetwork;
   zPVOID        pvConn = 0;
   LPTASK        lpTask;
   zCHAR         szReturnType[ 2 ];
   zVIEW         vArgs = 0;
   va_list       vaList;
   zCHAR         cPacketType;
   zCHAR         szAppName[ zZEIDON_NAME_LTH + 1 ];
   zCHAR         szServer[ 256 ];
   ServDirOperRecord OperInfo;
   zLONG         lRC;
   zSHORT        nReturnCode = zCALL_ERROR;
   zSHORT        nRC = 0;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetCallOperation, vSubtask, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetCallOperation, lpTask );
      return( zCALL_ERROR );
   }

   //
   // Try creating the argument object from the argument list.
   //

   SfActivateSysEmptyOI( &vArgs, "kztranwo", vSubtask, zSINGLE );
   if ( vArgs == 0 )
   {
      fnOperationReturn( iNetCallOperation, lpTask );
      return( zCALL_ERROR );
   }

   fnRetrieveAppName( vSubtask, szAppName );

   CreateEntity( vArgs, "Operation", zPOS_AFTER );
   SetAttributeFromString( vArgs, "Operation", "ApplicationName", szAppName );
   SetAttributeFromString( vArgs, "Operation", "OperName", pchOperName );
   if ( bTransformation )
   {
      SetAttributeFromString( vArgs, "Operation", "OperationType", zTYPE_TRAN );
      SetAttributeFromString( vArgs, "Operation", "ObjectName", pchInfo );
   }
   else
   {
      SetAttributeFromString( vArgs, "Operation", "OperationType", zTYPE_GOPER );
      if ( pchInfo && *pchInfo )
         SetAttributeFromString( vArgs, "Operation", "DLL_Name", pchInfo );
   }

   // First value in the arg list is the return type.
   szReturnType[ 0 ] = *pchArgList++;
   szReturnType[ 1 ] = 0;
   SetAttributeFromString( vArgs, "Operation", "ReturnType", szReturnType );

   // Loop through each of the arguments and add them to vArg.
   va_start( vaList, pchArgList );
   while ( *pchArgList )
   {
      zCHAR  szDataType[ 2 ];
      zPVOID pvoid;
      zBOOL  bPointer;

      CreateEntity( vArgs, szlArgument, zPOS_AFTER );

      if ( *pchArgList == 'p' )
      {
         bPointer = TRUE;
         pchArgList++;
         SetAttributeFromString( vArgs, szlArgument, "ReturnArgument", "Y" );
         pvoid = va_arg( vaList, zPVOID );
         SetAttributeFromBlob( vArgs, szlArgument, "PointerValue",
                               &pvoid, sizeof( pvoid ) );
         if ( pvoid )
            SetAttributeFromString( vArgs, szlArgument, "SendArgument", "Y" );
      }
      else
         bPointer = FALSE;

      szDataType[ 0 ] = *pchArgList;
      szDataType[ 1 ] = 0;
      SetAttributeFromString( vArgs, szlArgument, "DataType", szDataType );

      switch ( *pchArgList++ )
      {
         case 'l':      // Local address
            // The argument to the transformation is the local address, but to
            // keep anyone from cheating we don't send the address.  We'll set
            // the argument type to 'l' and let the server retrieve the local
            // address via the network.
            break;

         case 'S':      // String
         {
            zPCHAR pch = va_arg( vaList, zPCHAR );
            SetAttributeFromString( vArgs, szlArgument, "Value", pch );
            break;
         }

         case 'Y':      // Byte
            if ( bPointer )
            {
               zPCHAR pc = (zPCHAR) pvoid;
               if ( pc )
                  SetAttributeFromInteger( vArgs, szlArgument, "Value", *pc );
            }
            else
            {
               zCHAR c = (zCHAR) va_arg( vaList, VA_ARG_CHAR );
               SetAttributeFromInteger( vArgs, szlArgument, "Value", c );
            }

            break;

         case 'L':      // Long integer
            if ( bPointer )
            {
               zPLONG pl = (zPLONG) pvoid;
               if ( pl )
                  SetAttributeFromInteger( vArgs, szlArgument, "Value", *pl );
            }
            else
            {
               zLONG l = va_arg( vaList, zLONG );
               SetAttributeFromInteger( vArgs, szlArgument, "Value", l );
            }

            break;

         case zTYPE_DECIMAL:      // Decimal
         case 'R':      // ??? Real ???
            if ( bPointer )
            {
               zPDECIMAL pd = (zPDECIMAL) pvoid;

               if ( pd )
                  SetAttributeFromDecimal( vArgs, szlArgument, "Value", *pd );
            }
            else
            {
               zDECIMAL d;

               d = va_arg( vaList, zDECIMAL );
               SetAttributeFromDecimal( vArgs, szlArgument, "Value", d );
            }

            break;

         case 'N':      // Short integer
            if ( bPointer )
            {
               zPSHORT ps = (zPSHORT) pvoid;

               if ( ps )
                  SetAttributeFromInteger( vArgs, szlArgument, "Value", (zLONG) *ps );
            }
            else
            {
               zSHORT n = (zSHORT) va_arg( vaList, VA_ARG_SHORT );

               SetAttributeFromInteger( vArgs, szlArgument, "Value", n );
            }

            break;

         case 'F':      // Float
            break;

         case 'D':      // Date
            break;

         case 'H':      // Time
            break;

         case 'B':      // Blob
            break;

         case 'V':      // View
            if ( bPointer )
            {
               zPVIEW   pv = (zPVIEW) pvoid;
               LPVIEWOD lpViewOD;

               // If the view is empty, then set flag to indicate we are NOT
               // sending the OI.
               if ( *pv == 0 )
                  SetAttributeFromString( vArgs, szlArgument, "SendArgument", "N" );
               else
               {
                  // Make sure the view is valid.
                  if ( fnValidView( lpTask, *pv ) == 0 )
                     goto EndOfFunction;

                  lpViewOD = zGETPTR( (*pv)->hViewOD );
                  SetAttributeFromString( vArgs, szlArgument, "ObjectName", lpViewOD->szName );
                  SetAttributeFromString( vArgs, szlArgument, "SendArgument", "Y" );
               }
            }
            else
            {
               zVIEW v = va_arg( vaList, zVIEW );

               if ( v == 0 )
               {
                  SetAttributeFromString( vArgs, szlArgument, "SendArgument", "N" );
               }
               else
               // Check to see if view is a subtask view.
               if ( v->hSubtask )
               {
                  LPSUBTASK lpSubtask = zGETPTR( v->hSubtask );
                  LPAPP     lpApp     = zGETPTR( lpSubtask->hApp );

                  // We've got a subtask view--there is no OI to send but there
                  // is an application name.
                  SetAttributeFromString( vArgs, szlArgument, "SubtaskView", "Y" );
                  SetAttributeFromString( vArgs, szlArgument, "ApplicationName", lpApp->szName );
                  SetAttributeFromString( vArgs, szlArgument, "SendArgument", "N" );
               }
               else
               {
                  zCHAR    szTempAppName[ zAPPL_NAME_LTH ];
                  LPVIEWOD lpViewOD;

                  if ( fnValidView( lpTask, v ) == 0 )
                  {
                     va_end( vaList );
                     goto EndOfFunction;
                  }

                  lpViewOD = zGETPTR( v->hViewOD );

                  // Check to see if the app name for the view matches the
                  // "global" app name for this transformation.  If it doesn't
                  // then we need to set the application name for the view.
                  fnRetrieveAppName( v, szTempAppName );
                  if ( zstrcmp( szTempAppName, szAppName ) != 0 )
                  {
                     SetAttributeFromString( vArgs, szlArgument, "ApplicationName", szTempAppName );
                  }

                  SetAttributeFromBlob( vArgs, szlArgument, "PointerValue", &v, zsizeof( v ) );
                  SetAttributeFromString( vArgs, szlArgument, "SendArgument", "Y" );
                  SetAttributeFromString( vArgs, szlArgument, "ObjectName", lpViewOD->szName );
               }
            }

            break;

      } // switch ( *pchArgList++ )...

   } // while ( *pchArgList )...

   va_end( vaList );

   // Set up info for activate request.
   OperInfo.pszNetworkName         = lpNetwork->szNetworkName;
   OperInfo.vSubtask               = vSubtask;
   OperInfo.lControl               = 0;
   OperInfo.pszUserSuppliedAddress = pchAddress;
   OperInfo.pszOperName            = pchOperName;

   // Open connection.
   if ( fnAddConnectionToNetwork( lpTask, lpNetwork, szServer, &pvConn, TRUE,
                                  zAPPLREQ_OPER, &OperInfo, vSubtask ) < 0 )
   {
      nReturnCode = zNETWORK_ERROR;
      goto EndOfFunction;
   }

   if ( lpNetwork->nTraceLevel > 1 )
      TraceLineS( "(kzoeneta) ** Sending Transformation Call", "" );

   //=======================================================================
   // Transmitting data.
   //
   // Until further notice, the following code only SENDS data over the
   // network.
   //=======================================================================
   // First send the header for the server driver and then the regular
   // packet for the function structure.
   if ( fnSendHeaderPacket( lpNetwork, &pvConn, zPACKET_CALLOPERATION,
                            szAppName ) != 0 )
   {
      goto EndOfFunction;
   }

   if ( fnSendTraceSwitches( lpNetwork, &pvConn, lpTask) != 0 )
      goto EndOfFunction;

   if ( fnSendDataPacket( lpNetwork, &pvConn, zPACKET_CALLOPERATION, 0 ) != 0 )
      goto EndOfFunction;

   // Send the app name.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn,
                                szAppName, zAPPL_NAME_LTH, zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   // Send the Argument list OI to the server to be committed.
   if ( fnSendOI( &pvConn, lpNetwork, vArgs, 0 ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Error sending Arg OI!", "" );
      goto EndOfFunction;
   }

   // Loop through each of the arguments looking for views.  If one is found
   // send it to the server.
   for ( nRC = SetCursorFirstEntityByString( vArgs, szlArgument, "DataType", "V", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntityByString( vArgs, szlArgument, "DataType", "V", 0 ) )
   {
      zVIEW  vSendView;

      // If view is a Subtask View then we don't need to send anything.
      if ( CompareAttributeToString( vArgs, szlArgument, "SubtaskView", "Y" ) == 0 )
      {
         continue;
      }

      // If we're not sending the view, skip it.
      if ( CompareAttributeToString( vArgs, szlArgument, "SendArgument", "N" ) == 0 )
      {
         continue;
      }

      if ( CompareAttributeToString( vArgs, szlArgument, "ReturnArgument", "Y" ) == 0 )
      {
         zPVIEW pv;

         GetBlobFromAttribute( &pv, 0, vArgs, szlArgument, "PointerValue" );
         vSendView = *pv;
      }
      else
         GetBlobFromAttribute( &vSendView, 0, vArgs, szlArgument, "PointerValue" );

      // We need to send the view to the server...
      if ( fnSendOI( &pvConn, lpNetwork, vSendView, zINCREMENTAL | zSAVE_CURSORS ) == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Error sending argument OI!", "" );
         goto EndOfFunction;
      }

   } // for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 )...

   // Tell network handler to flush the send buffer.
   if ( fnFlushBuffer( lpNetwork, &pvConn ) != 0 )
      goto EndOfFunction;

   // We don't need it anymore so...
   fnDropView( vArgs );
   vArgs = 0;

   //=======================================================================
   // Receiving data.
   //
   // From here until we close the connection we will only RECEIVE data over
   // the network.
   //=======================================================================

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Waiting for ACK", "" );

   // Wait for return code.
   if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lRC ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving OI ACK!", "" );
      goto EndOfFunction;
   }

   if ( cPacketType != zPACKET_RC )
   {
      TraceLineS( "(kzoeneta) ** No return code for NetCallOperation!", "" );
      goto EndOfFunction;
   }

   if ( fnReceiveOI( &pvConn, lpNetwork, &vArgs, vSubtask, "kztranwo",
                     zSINGLE | zACTIVATE_SYSTEM ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Not able to retrieve Arg List!", "" );
      goto EndOfFunction;
   }

   // Set the return value.
   switch ( szReturnType[ 0 ] )
   {
      case zTYPE_INTEGER:
         GetIntegerFromAttribute( (zPLONG) pvReturn, vArgs, "Operation", "ReturnValue" );
         break;

      case 'N':  // Short integer.
      {
         zLONG l;

         GetIntegerFromAttribute( &l, vArgs, "Operation", "ReturnValue" );
         *((zPSHORT) pvReturn) = (zSHORT) l;
         break;
      }

      case zTYPE_DATETIME:  // Date/time returned as a string.
      case zTYPE_STRING:
         GetStringFromAttribute( (zPCHAR) pvReturn, 20, vArgs, "Operation", "ReturnValue" );
         break;

      case 'R':
      case zTYPE_DECIMAL:
         GetDecimalFromAttribute( (zPDECIMAL) pvReturn, vArgs, "Operation", "ReturnValue" );
         break;
   }

   for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vArgs, szlArgument, 0 ) )
   {
      zPVIEW pvView;
      zPCHAR pchObjName;

      // If the argument is not a view, then don't worry about it.
      if ( CompareAttributeToString( vArgs, szlArgument, "DataType", "V" ) != 0 )
      {
         continue;
      }

      // If view is a Subtask View then we don't need to retrieve anything.
      if ( CompareAttributeToString( vArgs, szlArgument, "SubtaskView", "Y" ) == 0 )
      {
         continue;
      }

      GetBlobFromAttribute( &pvView, 0, vArgs, szlArgument, "PointerValue" );
      GetAddrForAttribute( &pchObjName, vArgs, szlArgument, "ObjectName" );

      // If the view is flagged as empty, then activate an empty OI.
      if ( CompareAttributeToString( vArgs, szlArgument, "ViewReturned", "E" ) == 0 )
      {

         ActivateEmptyObjectInstance( pvView, pchObjName, vSubtask, zMULTIPLE );
         continue;
      }

      // If the view is flagged as being returned, retrieve it.
      if ( CompareAttributeToString( vArgs, szlArgument, "ViewReturned", "Y" ) == 0 )
      {
         if ( fnReceiveOI( &pvConn, lpNetwork, pvView, vSubtask,
                           pchObjName, zMULTIPLE ) == zCALL_ERROR )
         {
            TraceLineS( "(kzoeneta) ** Not able to retrieve new view!", "" );
            goto EndOfFunction;
         }
      }

   } // for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 )...

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineI( "(kzoeneta) ** RC from transaction = ", nRC );

   if ( fnRetrieveMsgAndTraceObj( lpNetwork, &pvConn, vSubtask ) < 0 )
      goto EndOfFunction;

   // If we got here, then everything's OK.
   nReturnCode = 0;

EndOfFunction:
   if ( pvConn && fnRemoveConnectionFromNetwork( lpNetwork, &pvConn, TRUE ) == zCALL_ERROR )
   {
      nReturnCode = zCALL_ERROR;
   }

   if ( vArgs )
      fnDropView( vArgs );

   fnOperationReturn( iNetCallOperation, lpTask );
   return( nReturnCode );

} // NetCallOperation

//./ ADD NAME=NetSendFile
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetSendFile
//
//  PURPOSE:     Sends a file to a server.
//
//  DESCRIPTION: This operation opens the file specified by pchFileName.  If
//               the file name is not qualified, then this operation
//               qualifies it using the local Zeidon/Bin/Sys directory.  The
//               file is then sent line by line to the Zeidon Bootstrap
//               server.  Since the Bootstrap Server can only accept boot
//               strap files, we don't bother sending any message packets.
//               We send each line by first sending a 2-digit hex length of
//               the line (this makes a total of 3 bytes with the null
//               terminator) and then the line.
//
//               NOTE that we first send the file name.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               pchAddress     - Address of server.  If 0 then use LAD.
//
//  RETURNS:     0           - Network listen OK
//               zCALL_ERROR - Error on listen.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 9
zSHORT OPERATION
NetSendFile( zPCHAR pchNetworkName,
             zPCHAR pchAddress,
             zPCHAR pchLocalFileName,
             zPCHAR pchServerDirectory,
             zPCHAR pchServerFileName,
             zBOOL  bBinaryFile,
             zVIEW  vSubtask )
{
   return( 0 );

// 2001.06.28
// DGC Not supported at the moment (security risk).
#if 0
   zSHORT      nRC = zCALL_ERROR;
   zULONG      usBytesRead;
   zSHORT      iLineCount;
   zSHORT      nFileNameLth;
   zLONG       hFile = -1;
   LPNETWORK   lpNetwork;
   zPVOID      pvConn = 0;
   zPCHAR      pchLine = 0;
   zPCHAR      pchBuffer = 0;
   zBOOL       bConnOpen = FALSE;
   zCHAR       cDataType;
   zCHAR       cPacketType;
   zLONG       lPacketData;
   LPTASK      lpTask;
   SendFileRecord sf;
   LAD_InfoRecord LAD_Info;

   zmemset( &LAD_Info, 0, zsizeof( LAD_Info ) );

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetSendFile ... )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
      goto EndOfFunction;

   fnRetrieveAppName( vSubtask, sf.szAppName );
   nFileNameLth = zstrlen( pchServerFileName ) +
                           zstrlen( pchServerDirectory ) + 2;
   zltox( nFileNameLth, sf.szFileNameLth );

   // Try opening the file.
   hFile = SysOpenFile( vSubtask, pchLocalFileName, COREFILE_READ );
   if ( hFile == -1 )
   {
      TraceLineS( "(kzoeneta) ** Can't open file ", pchLocalFileName );
      SysMessageBox( szlNetworkError, "Can't open file for NetSendFile", 1 );
      goto EndOfFunction;
   }

   LAD_Info.lpTask     = lpTask;
   LAD_Info.lpNetwork  = lpNetwork;
   LAD_Info.vSubtask   = vSubtask;
   LAD_Info.nObjType   = zLADTYPE_SEND_FILE;
   SysGetUserID( vSubtask, LAD_Info.szUserName, zsizeof( LAD_Info.szUserName ), LAD_Info.szPassword, zsizeof( LAD_Info.szPassword ) );

   if ( fnGetApplAddress( &LAD_Info, pchAddress ) == zCALL_ERROR )
   {
      fnOperationReturn( iNetSendFile, lpTask );
      return( zCALL_ERROR );
   }

   // Open connection.
   if ( fnAddConnectionToNetwork( &LAD_Info, &pvConn, TRUE, vSubtask ) == zCALL_ERROR )
   {
      goto EndOfFunction;
   }

   bConnOpen = TRUE;

   if ( lpNetwork->nTraceLevel > 1 )
      TraceLineS( "(kzoeneta) ** Sending file ", pchLocalFileName );

   // If we're sending a binary file then we need to set up a buffer.
   if ( bBinaryFile )
   {
      pchLine = (zPCHAR) fnAllocDataspace( lpTask->hFirstDataHeader, zSENDFILE_BUFFER, TRUE, 0, 0 );
      pchLine = (zPCHAR) zGETPTR( pchLine );
      if ( pchLine == 0 )
         goto EndOfFunction;

      sf.bBinaryFile = 'Y';
      cPacketType = zPACKET_SENDLTHB;
      cDataType   = zTYPE_BLOB;
   }
   else
   {
      sf.bBinaryFile = 'N';
      cPacketType = zPACKET_SENDLTHS;
      cDataType   = zTYPE_STRING;
   }

   //=======================================================================
   // Transmitting data.
   //
   // Until further notice, the following code only SENDS data over the
   // network.
   //
   //=======================================================================

   // First send the header for the server driver and then the regular
   // packet for the function structure.
   if ( fnSendHeaderPacket( lpNetwork, &pvConn, zPACKET_SENDFILE, sf.szAppName ) != 0 )
   {
      goto EndOfFunction;
   }

   if ( fnSendTraceSwitches( lpNetwork, &pvConn, lpTask) != 0 )
      goto EndOfFunction;

   if ( fnSendDataPacket( lpNetwork, &pvConn, zPACKET_SENDFILE, 0 ) != 0 )
      goto EndOfFunction;

   // Send the file information.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn, (zPCHAR) &sf, zsizeof( sf ), zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   // Send the directory/filename.
   pchBuffer = (zPCHAR) fnAllocDataspace( lpTask->hFirstDataHeader, nFileNameLth, TRUE, 0, 0 );
   pchBuffer = (zPCHAR) zGETPTR( pchBuffer );
   strcpy_s( pchBuffer, pchServerDirectory );
   strcpy_s( &pchBuffer[ zstrlen( pchBuffer ) + 1 ], pchServerFileName );
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn, pchBuffer, nFileNameLth, zTYPE_STRING ) != 0 )
   {
      goto EndOfFunction;
   }

   // Now send each line of the file.
   iLineCount = 0;
   while ( TRUE )
   {
      if ( bBinaryFile )
      {
         usBytesRead = SysReadFile( vSubtask, hFile, pchLine, zSENDFILE_BUFFER );
         if ( usBytesRead == 0 )
            break;
      }
      else
      {
         if ( SysReadLine( vSubtask, (zCOREMEM) &pchLine, hFile ) != 1 )
            break;

         usBytesRead = zstrlen( pchLine ) + 1;
      }

      iLineCount++;

      // Send the length of the line.
      if ( fnSendDataPacket( lpNetwork, &pvConn, cPacketType, usBytesRead ) != 0 )
         goto EndOfFunction;

      // Send the line.
      if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, &pvConn, pchLine, usBytesRead, cDataType ) != 0 )
      {
         // Send 0 "length" to indicate we are done.
         fnSendDataPacket( lpNetwork, &pvConn, cPacketType, 0 );
         goto EndOfFunction;
      }

      // If we're reading a binary file then check to see if we are at the end of the file.
      if ( bBinaryFile )
      {
         if ( usBytesRead < zSENDFILE_BUFFER )
            break;
      }

   } // for (;;)...

   // Send 0 "length" to indicate we are done.
   if ( fnSendDataPacket( lpNetwork, &pvConn, cPacketType, 0 ) != 0 )
      goto EndOfFunction;

   // Tell network handler to flush the send buffer.
   if ( fnFlushBuffer( lpNetwork, &pvConn ) != 0 )
      goto EndOfFunction;

   //=======================================================================
   // Receiving data.
   //
   // From here until we close the connection we will only RECEIVE data over the network.
   //=======================================================================

   // Now wait for ack.
   if ( fnReceiveDataPacket( lpNetwork, &pvConn, &cPacketType, &lPacketData ) != 0 )
      goto EndOfFunction;

   if ( cPacketType != zPACKET_RC )
   {
      TraceLineI( "(kzoeneta) ** Network error #", lPacketData );
      if ( lPacketData == zNETERR_OUTOFMEMORY )
      {
         SysMessageBox( "Server Transaction Crash ", "*Out Of Memory*", 1 );
      }
   }
   else
   if ( lPacketData != iLineCount )
      TraceLineS( "(kzoeneta) ** Lines don't match up!", "" );
   else
      // If we get here then everything's OK.
      nRC = 0;

   if ( fnRetrieveMsgAndTraceObj( lpNetwork, &pvConn, vSubtask ) < 0 )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

EndOfFunction:
   if ( nRC == zCALL_ERROR )
   {
      zCHAR szMsg[ zMAX_FILENAME_LTH + 40 ];

      sprintf_s( szMsg, zsizeof( szMsg ), "Error sending file '%s' to server.", pchLocalFileName );
      SysMessageBox( szlNetworkError, szMsg, 1 );
   }

   if ( bConnOpen && fnRemoveConnectionFromNetwork( lpNetwork, &pvConn, TRUE ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
   }

   if ( pchBuffer )
      fnFreeDataspace( pchBuffer );

   if ( hFile != -1 )
      SysCloseFile( vSubtask, hFile, 0 );

   if ( pchLine && bBinaryFile )
      fnFreeDataspace( pchLine );

   fnOperationReturn( iNetSendFile, lpTask );
   return( nRC );
#endif

} // NetSendFile

//./ ADD NAME=NetSetTraceLevel
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetSetTraceLevel
//
//  PURPOSE:     Set the network trace level.
//
//  DESCRIPTION: Although how the trace level is used could be different
//               for each network handler, the trace level should
//               be used as follows:
//
//                   0 - No messages except error messages.
//                   1 - Same as 0 but with some messages.
//                   2 - Same as 1 but with dumps of network transmissions.
//                   3 - Same as 2 but with displays of all OI transmitted.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               nTraceLevel    - New trace level.
//
//  RETURNS:     0           - Trace level set.
//               zCALL_ERROR - Error setting level.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
NetSetTraceLevel( zVIEW lpTaskView, zPCHAR pchNetworkName, zSHORT nTraceLevel )
{
   LPTASK         lpTask;
   LPNETWORK      lpNetwork;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetSetTraceLevel, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetSetTraceLevel, lpTask );
      return( zCALL_ERROR );
   }

   lpNetwork->nTraceLevel = nTraceLevel;
   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineI( "(kzoeneta) ** Setting Net trace level to ", nTraceLevel );
   }

   fnOperationReturn( iNetSetTraceLevel, lpTask );
   return( 0 );

} // NetSetTraceLevel

//./ ADD NAME=NetGetTraceLevel
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetGetTraceLevel
//
//  PURPOSE:     Retrieves the current trace level for the specified
//               network.
//
//  DESCRIPTION: See NetSetTraceLevel for a desription of the different
//               trace levels.
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//
//  RETURNS:     zCALL_ERROR - Error retrieving trace level.
//               otherwise returns trace level.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
NetGetTraceLevel( zVIEW lpTaskView, zPCHAR pchNetworkName )
{
   LPTASK         lpTask;
   LPNETWORK      lpNetwork;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetGetTraceLevel, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetGetTraceLevel, lpTask );
      return( zCALL_ERROR );
   }

   fnOperationReturn( iNetGetTraceLevel, lpTask );
   return( lpNetwork->nTraceLevel );

} // NetGetTraceLevel

//./ ADD NAME=NetStatus
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetStatus
//
//  PURPOSE:     Returns via bit codes the current status of the network.
//
//  DESCRIPTION:
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                               network.
//
//  RETURNS:     0 - Network not started.
//
//               Otherwise following bits are returned:
//
//                 zNETSTAT_STARTED        - Network started.
//                 zNETSTAT_OPENCONNECTION - At least one active connection
//                 zNETSTAT_LISTEN         - Network listening for messages
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
NetStatus( zVIEW lpTaskView, zPCHAR pchNetworkName )
{
   LPTASK         lpTask;
   LPNETWORK      lpNetwork;
   zSHORT         nStatus;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetStatus, lpTaskView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, FALSE )) == 0 )
   {
      if ( pchNetworkName == 0 )
         pchNetworkName = DEFAULT_NETWORK;

      TraceLineS( "(kzoeneta) ** Network status: no network running for ", pchNetworkName );
      fnOperationReturn( iNetStatus, lpTask );
      return( 0 );
   }

   nStatus = zNETSTAT_STARTED;
   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Network status for network: ", lpNetwork->szNetworkName );
      TraceLineS( "(kzoeneta)         ** Network running", "" );
   }

   if ( lpNetwork->nConnCount > 0 )
   {
      nStatus |= zNETSTAT_OPENCONNECTION;

      if ( lpNetwork->nTraceLevel > 0 )
      {
         TraceLineI( "(kzoeneta)         ** Connections running: ", lpNetwork->nConnCount );
      }
   }

   if ( lpNetwork->bListen )
   {
      nStatus |= zNETSTAT_LISTEN;

      if ( lpNetwork->nTraceLevel > 0 )
      {
         TraceLineS( "(kzoeneta)         ** Network listening", "" );
      }
   }

   fnOperationReturn( iNetStatus, lpTask );
   return( nStatus );

} // NetStatus

//./ ADD NAME=NetGetLocalHostAddress
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       NetGetLocalHostAddress
//
//  PURPOSE:     Returns the network address of the local node.
//
//  DESCRIPTION:
//
//  PARAMETERS:  pchNetworkName - Unique internal 'Zeidon' name of the
//                                network.
//               pchHostAddress - Return buffer.
//
//  RETURNS:     0 - Address returned OK.
//               zCALL_ERROR - oops.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT OPERATION
NetGetLocalHostAddress( zVIEW  lpView,
                        zPCHAR pchNetworkName,
                        zPCHAR pchHostAddress )
{
   LPTASK         lpTask;
   LPNETWORK      lpNetwork;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpTask = fnOperationCall( iNetGetLocalHostAddress, lpView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( (lpNetwork = fnFindNetwork( lpTask, pchNetworkName, TRUE )) == 0 )
   {
      fnOperationReturn( iNetStatus, lpTask );
      return( 0 );
   }

   if ( (*lpNetwork->lpfnGetAddress)( lpView, &lpNetwork->pNetworkHandle,
                                      0, 'L', pchHostAddress ) != 0 )
   {
      fnOperationReturn( iNetStatus, lpTask );
      return( zCALL_ERROR );
   }

   fnOperationReturn( iNetGetLocalHostAddress, lpTask );
   return( 0 );

} // NetGetLocalHostAddress

// fnReadDataFromNet
//
// Used as part of SfActivateOI_FromStream to retrieve an OI from the network.
// This operation retrieves the next line from the network.
//
// Returns: 1 - Retrieved data, more data to come.
//          0 - No more data.
zSHORT OPERATION
fnReadDataFromNet( zVIEW   lpView,
                   zPVOID  pvData,
                   zPPCHAR ppchReturnBuffer,
                   zULONG  uLth,
                   zSHORT  nErrorNum )
{
   LPACTIVATE  lpAct = (LPACTIVATE) pvData;
   LPNETWORK   lpNetwork = lpAct->lpNetwork;
   zPVOID      *ppvConn = lpAct->ppvConn;
   zCHAR       cDataType;
   zCHAR       cPacketType;
   zLONG       lPacketData;

   // If nErrorNum is not 0, then flash the error message and get out.
   if ( nErrorNum )
   {
      zCHAR szMsg[ 500 ];

      zPCHAR pchExtraData = (zPCHAR) ppchReturnBuffer;

      TraceLineI( "(kzoeneta) ** Read Data error = ", nErrorNum );
      switch ( nErrorNum )
      {
         case 74:
            // "KZOEE074 - Invalid Entity name on line "
            sprintf_s( szMsg, zsizeof( szMsg ), "Invalid Entity name = %s", pchExtraData );
            break;

         case 75:
            // "KZOEE075 - Invalid Entity level on line "
            sprintf_s( szMsg, zsizeof( szMsg ), "Invalid Entity level = %s", pchExtraData );
            break;

         case 90:
            // "KZOEE090 - Maximum number of entites in portable file exceeded"
            strcpy_s( szMsg, zsizeof( szMsg ), "Maximum number of entities in stream exceeded" );
            break;

         case 104:
            // "KZOEE104 - Invalid Attribute name for Entity"
            sprintf_s( szMsg, zsizeof( szMsg ), "Invalid Attr name for Entity = %s",
                      pchExtraData );
            break;

      } // switch ( nErrorNum )

      SysMessageBox( lpView, szlNetworkError, szMsg, 1 );
      return( 0 );

   } // if ( nErrorNum )...

   // The first few bytes should be the Zeidon network packet indicating the
   // length of the incoming line or that there is no more incoming data.
   if ( fnReceiveDataPacket( lpNetwork, ppvConn, &cPacketType, &lPacketData ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving SENDLTH!", "" );
      return( zCALL_ERROR );
   }

   if ( cPacketType == zPACKET_END )
   {
      if ( lpNetwork->nTraceLevel > 0 )
         TraceLineS( "(kzoeneta) ** Received OI END message", "" );

      if ( lPacketData != lpAct->lLineCount )
      {
         LPTASK lpTask = zGETPTR( lpView->hTask );
         // "KZOEE400 - Error transmitting lines. "
         fnIssueCoreError( lpTask, lpView, 16, 400, 0,
                           "Error transmitting OI -- some lines lost.", 0 );
         return( zCALL_ERROR );
      }

      return( 0 );
   }

   if ( cPacketType == zPACKET_ERROR )
   {
      TraceLineI( "(kzoeneta) ** Received Packet ERROR code = ", lPacketData );
      return( 0 );
   }

   if ( cPacketType == zPACKET_SENDLTHS )
      cDataType = zTYPE_STRING;
   else
   if ( cPacketType == zPACKET_SENDLTHB )
      cDataType = zTYPE_BLOB;
   else
   {
      TraceLineS( "(kzoeneta) ** Invalid packet type--expecting SENDLTH!", "" );
      return( 0 );
   }

   if ( lpNetwork->nTraceLevel > 1 )
   {
      TraceLineI( "(kzoeneta) ** Received SENDLTH packet. Lth = ", lPacketData );
   }

   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   ppchReturnBuffer, lPacketData, cDataType ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error receiving data", "" );
      return( zCALL_ERROR );
   }

   lpAct->lLineCount++;

   return( 1 );

} // fnReadDataFromNet

// Retrieves an OI from the network.
// ASSUMES: That the next bytes of data belong to the OI.
// Returns: Return code from SfActivateOI_FromStream.
zSHORT LOCALOPER
fnReceiveOI( zPVOID      *ppvConn,
             LPNETWORK   lpNetwork,
             zPVIEW      pvOI,
             zVIEW       vSubtask,
             zPCHAR      pchObjectDef,
             zLONG       lControl )
{
   ActivateRecord ar;
   zSHORT      nRC = 0;

   ar.lpNetwork  = lpNetwork;
   ar.ppvConn    = ppvConn;
   ar.lLineCount = 0;

   if ( lpNetwork->nTraceLevel > 1 )
   {
      TraceLineS( "(kzoeneta) ** Initiating receive of OI", "" );
   }

   lControl |= zACTIVATE_NOCONSTRAINTS;

   nRC = SfActivateOI_FromStream( pvOI, pchObjectDef, vSubtask, lControl, fnReadDataFromNet, &ar );
   if ( nRC != zCALL_ERROR )
   {
      if ( lpNetwork->nTraceLevel > 0 )
      {
         TraceLineS( "(kzoeneta) ** Receive OI OK.  Sending ack.", "" );
      }
   }
   else
   {
      nRC = zCALL_ERROR;
      TraceLineS( "(kzoeneta) ** Error receiving OI.  Sending error packet.", "" );
   }

   return( nRC );

} // fnReceiveOI

// fnSendOI_Data
//
// Used as part of SfWriteOI_ToStream to send an OI across the network.
// This operation sends a line.
//
// Returns: 0           - Line sent OK.
//          zCALL_ERROR - Error.
zSHORT OPERATION
fnSendOI_Data( zVIEW   lpTaskView,
               zPVOID  lpvData,
               zPCHAR  pchBuffer,
               zULONG  uLth,
               zCHAR   cDataType )
{
   zCHAR       cPacketType;
   LPACTIVATE  lpAct = (LPACTIVATE) lpvData;
   LPNETWORK   lpNetwork = lpAct->lpNetwork;

   if ( uLth == 0 )
      uLth = zstrlen( pchBuffer ) + 1;

   if ( cDataType == zTYPE_STRING )
      cPacketType = zPACKET_SENDLTHS;
   else
      cPacketType = zPACKET_SENDLTHB;

   // Send the length packet.
   if ( fnSendDataPacket( lpNetwork, lpAct->ppvConn, cPacketType, uLth ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error sending zPACKET_SENDLTH", "" );
      return( zCALL_ERROR );
   }

   // Send the actual data.
   if ( (*lpNetwork->lpfnSend)( &lpNetwork->pNetworkHandle, lpAct->ppvConn,
                                pchBuffer, uLth, cDataType ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Error sending data line", "" );
      return( zCALL_ERROR );
   }

   lpAct->lLineCount++;

   return( 0 );
}

zCHAR g_chNetSendCompressed = 0;

// Sends an OI over the network.
// ASSUMES: That socket 'sock' is a blocking socket.
//          That receiving socket is ready for data.
zSHORT LOCALOPER
fnSendOI( zPVOID      *ppvConn,
          LPNETWORK   lpNetwork,
          zVIEW       vOI,
          zLONG       lControl )
{
   zSHORT         nRC = 0;
   ActivateRecord ar;

   ar.lpNetwork  = lpNetwork;
   ar.ppvConn    = ppvConn;
   ar.lLineCount = 0;

   if ( g_chNetSendCompressed == 0 )
   {
      zCHAR szCompressed[ 10 ];

      SysReadZeidonIni( -1, "[Zeidon]", "NetSendCompressed", szCompressed, zsizeof( szCompressed ) );
      g_chNetSendCompressed = ztoupper( szCompressed[ 0 ] ) == 'N' ? 'N' : 'Y';
   }

   if ( g_chNetSendCompressed != 'N' )
      lControl |= zCOMPRESSED;
   else
   {
      LPVIEWOD lpViewOD = zGETPTR( vOI->hViewOD );
      if ( lpViewOD->bNetCompress )
         lControl |= zCOMPRESSED;
   }

   nRC = SfWriteOI_ToStream( vOI, "NETACT", lControl, fnSendOI_Data, (zPVOID) &ar );

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Sending END packet.", "" );
   }

   // Send a message to say we're done sending the OI
   if ( nRC != zCALL_ERROR )
   {
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_END, ar.lLineCount ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
         return( zCALL_ERROR );
      }
   }
   else
   {
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_SENDOI ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
         return( zCALL_ERROR );
      }
   }

   return( 0 );

} // fnSendOI

/*
   We got a message from another PC (the client) that it wants to activate
   an OI off of the current PC (the server).  Process the activate and send
   the activated OI back to the client.
*/
//=fnProcessActivateOI( LPNETWORK lpNetwork, zPVOID *ppvConn )
zSHORT LOCALOPER
fnProcessActivateOI( zVIEW lpTaskView, LPNETWORK lpNetwork, zPVOID *ppvConn )
{
   LPTASK         lpTask = 0;
   zVIEW          vSubtask = 0;
   zVIEW          vQual = 0;
   zVIEW          vOI = 0;
   zLONG          lControl;
   zBOOL          bFlushNeeded = FALSE;
   zActivatePacket ActPacket;
   LPACTPACKET    lpActPacket;
   zSHORT         nRC = zCALL_ERROR;

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Received Activate OI message.", "" );
      TraceLineS( "(kzoeneta) ** Retrieving Activate info.", "" );
   }

   //=======================================================================
   // Receiving data.
   //
   // Until noted below, we will only RECEIVE data over the network.
   //=======================================================================

   // First thing to do is retrieve the activate info.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &lpActPacket, sizeof( zActivatePacket ),
                                   zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve Act info", "" );
      goto EndOfFunction;
   }

   // Store the info locally -- as soon as we perform the next network IO
   // operation we aren't assured that lpActPacket points to valid data.
   zmemcpy( &ActPacket, lpActPacket, sizeof( zActivatePacket ) );
   lControl = zxtol( ActPacket.szControl );

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLine( "(kzoeneta) ** User Name: %s  App Name: %s  Object Def: %s",
                 ActPacket.szUserName, ActPacket.szAppName, ActPacket.szObjectDef );
   }

   // Try to create a subtask view using the application name passed.
   if ( SfCreateSubtask( &vSubtask, lpTaskView, ActPacket.szAppName ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Invalid App name = ", ActPacket.szAppName );
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_INVALIDAPP ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
      }

      bFlushNeeded = TRUE;
      goto EndOfFunction;
   }

   lpTask = fnOperationCall( iNetActivateOI, vSubtask, 0 );
   fnCreateMsgObj( vSubtask );

   // Make sure request is for valid OD.
   if ( ActivateViewObject( vSubtask, ActPacket.szObjectDef, FALSE ) == 0 )
   {
      TraceLineS( "(kzoeneta) ** Invalid OD name = ", ActPacket.szObjectDef );
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_INVALIDOD ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
      }

      bFlushNeeded = TRUE;
      goto EndOfFunction;
   }

   if ( ActPacket.cUseQualification == 'Y' )
   {
      if ( lpNetwork->nTraceLevel > 0 )
      {
         TraceLineS( "(kzoeneta) ** Receiving Qual OI.", "" );
      }

      if ( fnReceiveOI( ppvConn, lpNetwork, &vQual, vSubtask, "KZDBHQUA",
                        zMULTIPLE | zACTIVATE_SYSTEM ) == zCALL_ERROR )
      {
         goto EndOfFunction;
      }
   }

   //=======================================================================
   // Transmitting data.
   //
   // Until we close the connection, the following code only SENDS data over
   // the network.
   //=======================================================================

   bFlushNeeded = TRUE;

   // For now we don't want to execute activate constraints on the server.
   lControl |= zACTIVATE_NOCONSTRAINTS;

   // Force activate to be local.
   lControl |= zACTIVATE_LOCAL;

   // Activate the OI but force the activate to occur locally.
   nRC = ActivateObjectInstance( &vOI, ActPacket.szObjectDef, vSubtask, vQual, lControl );

   if ( vOI )
   {
      if ( nRC < 0 )
      {
         // If we have an object instance (vOI is not 0) but the return code was
         // less than 0, there was nothing on the DB to activate so the OI is
         // empty.  Instead of sending an empty OI across the network we'll
         // just send an indication that we have an empty OI and we'll let the
         // client activate an empty OI on its side.
         if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_EMPTYOI, 0 ) != 0 )
         {
            TraceLineS( "(kzoeneta) ** Not able to indicate empty OI!", "" );
            nRC = zCALL_ERROR;
            goto EndOfFunction;
         }
      }
      else
      {
         // Send Ack to signal we got this far.
         if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ACK, 0 ) != 0 )
         {
            TraceLineS( "(kzoeneta) ** Not able to ACK request of OI!", "" );
            nRC = zCALL_ERROR;
            goto EndOfFunction;
         }

         if ( lpNetwork->nTraceLevel > 0 )
         {
            TraceLineS( "(kzoeneta) ** Sending Activated OI.", "" );
         }

         // Now send the oi.
         if ( fnSendOI( ppvConn, lpNetwork, vOI, zINCREMENTAL ) == zCALL_ERROR )
         {
            nRC = zCALL_ERROR;
            goto EndOfFunction;
         }
      }
   }

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineI( "(kzoeneta) ** Sending RC packet. RC = ", nRC );

   // Send return code.
   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_RC, nRC ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Not able send Return code!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   // If we get here then everything's OK and we already sent the return code
   // back to the client so let's set it to 0.
   nRC = 0;

EndOfFunction:
   if ( vSubtask &&
        fnSendMsgAndTraceObj( lpNetwork, ppvConn, vSubtask ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
   }

   if ( bFlushNeeded && fnFlushBuffer( lpNetwork, ppvConn ) != 0 )
   {
      nRC = zCALL_ERROR;
   }

   if ( vOI )
   {
      LPVIEWCSR lpViewCsr = zGETPTR( vOI->hViewCsr );
      LPVIEWOI  lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      // It's possible that we've activated the OI with pessimistic locking.
      // This means that there are records in the DB to lock out the OI.  But
      // Core automatically deletes those records when the OI is dropped.  This
      // is not good because the client that requested this OI obviously wants
      // the locks left in place.  To keep the locks we'll turn off the flag
      // that says the OI has pessimistic locking.  This will keep Core from
      // deleting the locks when we drop the view.
      lpViewOI->bIsLocked = 0;

      fnDropView( vOI );
   }

   if ( vQual )
      fnDropView( vQual );

   if ( vSubtask )
      DROPSUBTASK( vSubtask );

   if ( lpTask )
      fnOperationReturn( iNetActivateOI, lpTask );

   return( nRC );

} // fnProcessActivateOI

/*
   We got a message from another PC (the client) that it wants to activate
   an OI from a file off the current PC (the server).  Process the activate
   and send the activated OI back to the client.
*/
zSHORT LOCALOPER
fnProcessActivateOI_FromFile( LPNETWORK lpNetwork, zPVOID *ppvConn )
{
   TraceLineS( "(kzoeneta) ** ", "fnProcessActivateOI_FromFile( ) is deprecated" );
   return( 0 );

#if 0
   zSHORT nRC;
   zBOOL  bFlushNeeded = FALSE;
   zVIEW  vSubtask = 0;
   zVIEW  vOI = 0;
   zLONG  lControl;
   zCHAR  szFileName[ zMAX_FILENAME_LTH + 1 ];
   zPCHAR pch;
   zSHORT nFileNameLth;
   zActivatePacket ActPacket;
   LPACTPACKET     lpActPacket;

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Received Activate OI From File message.", "" );
      TraceLineS( "(kzoeneta) ** Retrieving Activate info.", "" );
   }

   //=======================================================================
   // Receiving data.
   //
   // Until noted below, we will only RECEIVE data over the network.
   //=======================================================================

   // First thing to do is retrieve the activate info.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &lpActPacket, zsizeof( zActivatePacket ),
                                   zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve Act info", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   // Store the info locally -- as soon as we perform the next network IO
   // operation we aren't assured that lpActPacket points to valid data.
   zmemcpy( &ActPacket, lpActPacket, zsizeof( zActivatePacket ) );
   lControl = zxtol( ActPacket.szControl );

   // Retrieve the file name.  Use a dummy pointer to get the file name and
   // then copy it into the allocated buffer.
   nFileNameLth = (zSHORT) zxtol( ActPacket.szFileNameLth );
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &pch, nFileNameLth, zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve file name.", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   strcpy_s( szFileName, zsizeof( szFileName ), pch );

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLine( "(kzoeneta) ** User Name: %s  App Name: %s  "
                   "Object Def: %s  File Name: %s",
                 ActPacket.szUserName, ActPacket.szAppName,
                 ActPacket.szObjectDef, szFileName );
   }

   //=======================================================================
   // Transmitting data.
   //
   // Until we close the connection, the following code only SENDS data over
   // the network.
   //=======================================================================

   bFlushNeeded = TRUE;

   // Try to create a subtask view using the application name passed.
   if ( CREATESUBTASK( &vSubtask, ActPacket.szAppName ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Invalid App name = ", ActPacket.szAppName );
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR,
                             zNETERR_INVALIDAPP ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
      }

      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   fnCreateMsgObj( vSubtask );

   // Make sure request is for valid OD.
   if ( ActivateViewObject( vSubtask, ActPacket.szObjectDef, FALSE ) == 0 )
   {
      TraceLineS( "(kzoeneta) ** Invalid OD name = ", ActPacket.szObjectDef );
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR,
                             zNETERR_INVALIDOD ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
      }

      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   if ( fnCheckForClientAuthority( ppvConn, lpNetwork, ActPacket.szAppName,
                                   ActPacket.szUserName, ActPacket.szPassword,
                                   ActPacket.szObjectDef,
                                   zLADTYPE_LOD_ACTIVATE_FILE ) < 0 )
   {
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR,
                              zNETERR_NOAUTHORITY ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_ERROR", "" );
      }

      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   // For right now we will assume that activated files are in the Bin dir
   // of the application.

   // Activate the OI.
   nRC = ActivateOI_FromFile( &vOI, ActPacket.szObjectDef, vSubtask,
                              szFileName, lControl );

   if ( vOI )
   {
      // Send Ack to signal we got this far.
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ACK, 0 ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Not able to ACK request of OI!", "" );
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      if ( lpNetwork->nTraceLevel > 0 )
         TraceLineS( "(kzoeneta) ** Sending Activated OI.", "" );

      if ( fnSendOI( ppvConn, lpNetwork, vOI,
                     zINCREMENTAL | zSAVE_CURSORS ) == zCALL_ERROR )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineI( "(kzoeneta) ** Sending RC packet. RC = ", nRC );
   }

   // Send return code.
   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_RC, nRC ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Not able send Return code!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   nRC = 0;

EndOfFunction:
   if ( vSubtask &&
        fnSendMsgAndTraceObj( lpNetwork, ppvConn, vSubtask ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
   }

   if ( bFlushNeeded && fnFlushBuffer( lpNetwork, ppvConn ) != 0 )
   {
      nRC = zCALL_ERROR;
   }

   if ( vOI )
      fnDropView( vOI );

   if ( vSubtask )
      DROPSUBTASK( vSubtask );

   return( nRC );
#endif

} // fnProcesssActivateOI_FromFile

/*
   Relinks OIs using information in a buffer.  The info in
   the buffer looks like:

   (OI-idx:EI-hier#/OI-idx:EI-her#/...)(...)...
*/
void LOCALOPER
fnRelinkOIs( LPTASK        lpTask,
             LPVIEWCLUSTER lpViewCluster,
             zSHORT        nViewCount,
             zPCHAR        pchLinkBuffer )
{
   zLONG             lHierCount;
   zLONG             hBuffer = 0;
   LPENTITYINSTANCE  lpEntityInstance;
   LPENTITYINSTANCE  lpLastEI;
   LPVIEWCSR         *plpViewCsr;
   LPVIEWOI          *plpViewOI;
   zPCHAR            pchBuffer;
   zPCHAR            pch;
   zSHORT            k;

   // First allocate enough space to save some pointers.
   hBuffer = SysAllocMemory( &pchBuffer, nViewCount * sizeof( LPVIEWOI ) * 2,
                             0, zCOREMEM_ALLOC, 0 );
   if ( hBuffer == 0 )
      return;

   zmemset( pchBuffer, 0, nViewCount * sizeof( LPVIEWOI ) * 2 );

   plpViewCsr = (LPVIEWCSR *) pchBuffer;
   plpViewOI  = (LPVIEWOI *) (pchBuffer + sizeof( LPVIEWCSR ) * nViewCount);

   // First thing is to set the hier # for all the entity instances.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewCluster[ k ].vOI == 0 )
         continue;

      // Get ViewCsrs/ViewOIs for all the views.
      plpViewCsr[ k ] = zGETPTR( lpViewCluster[ k ].vOI->hViewCsr );
      plpViewOI[ k ]  = zGETPTR( plpViewCsr[ k ]->hViewOI );

      lHierCount = 0;
      for ( lpEntityInstance = zGETPTR( plpViewOI[ k ]->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         if ( fnEntityInstanceIsDead( lpEntityInstance ) )
            continue;

         lpEntityInstance->lHierCount = lHierCount++;
      }
   }

   // Now go through the link buffer.  The first char had better be a '('.
   // (OI-idx:EI-hier#/OI-idx:EI-her#/...)(...)...
   pch = pchLinkBuffer;
   if ( *pch++ != '(' )
   {
      fnSysMessageBox( lpTask, szlNetworkError, "Link buffer doesn't start with a '('", 1 );
      goto EndOfFunction;
   }

   lpLastEI = 0;

   // Loop through the link buffer and try to link up EIs.
   while ( *pch )
   {
      zSHORT nOI_Idx;

      // Skip opening paren if it's there -- they're harmless.
      if ( *pch == '(' )
         pch++;

      if ( !zisalnum( *pch ) )
      {
         fnSysMessageBox( lpTask, szlNetworkError, "Link buffer: expecting hex digit.", 1 );
         goto EndOfFunction;
      }

      // Get the OI idx;  pch then contains the char that stopped the scan.
      nOI_Idx = (zSHORT) zstrtol( pch, &pch, 16 );

      // The next char had better be a ':'!
      if ( *pch++ != ':' )
      {
         fnSysMessageBox( lpTask, szlNetworkError, "Link buffer: expecting ':' after OI tag.", 1 );
         goto EndOfFunction;
      }

      if ( nOI_Idx == nViewCount )
      {
         fnSysMessageBox( lpTask, szlNetworkError, "Link buffer: Could find OI matching Tag.", 1 );
         goto EndOfFunction;
      }

      if ( !zisalnum( *pch ) )
      {
         fnSysMessageBox( lpTask, szlNetworkError,
                          "Link buffer: expecting hex digit(2).", 1 );
         goto EndOfFunction;
      }

      // Get the hier number.
      lHierCount = zstrtol( pch, &pch, 16 );

      // The next char had better be a ')' or a '/'!
      if ( *pch != ')' && *pch != '/' )
      {
         fnSysMessageBox( lpTask, szlNetworkError, "Link buffer: expecting ')/' after Hier Num.", 1 );
         goto EndOfFunction;
      }

      // Find the entity instance that matches lHierCount.
      lpEntityInstance = zGETPTR( plpViewOI[ nOI_Idx ]->hRootEntityInstance );
      lpEntityInstance = fnFindEntityInstanceByHierCount( lpEntityInstance, lHierCount );
      if ( lpEntityInstance == 0 )
      {
         fnSysMessageBox( lpTask, szlNetworkError, "Link buffer: Could find EI matching Hier Count.", 1 );
         goto EndOfFunction;
      }

      if ( lpLastEI )
      {

#ifdef DEBUG
         LPVIEWENTITY lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
         LPVIEWENTITY lpLastViewEntity = zGETPTR( lpLastEI->hViewEntity );

         if ( lpViewEntity->lEREntTok != lpLastViewEntity->lEREntTok )
         {
            fnSysMessageBox( lpTask, szlNetworkError, "Link buffer: Link EIs don't have matching tokens.", 1 );
            goto EndOfFunction;
         }

#endif
         fnRelinkInstanceToInstance( lpLastEI, lpEntityInstance );

      } // if ( lpLastEI )...

      // Set lpLastEI so that the next EI we read can be linked to
      // it.
      lpLastEI = lpEntityInstance;

      // If pch point to a close paren then we just linked the last EI in the
      // current EI list.  Set lpLastEI to 0 to indicate that the
      // next EI we read is the first in a linked chain.
      if ( *pch == ')' )
         lpLastEI = 0;

      pch++;

   } // while ( *pch )...

EndOfFunction:

   SysFreeMemory( hBuffer );

} // fnRelinkOIs

/* =fnProcessCommitOI

   We got a message from another PC (the client) that it wants to commit
   an OI on the current PC (the server).  Process the commit and send
   the committed OI back to the client.
*/
zSHORT LOCALOPER
fnProcessCommitOI( zVIEW lpTaskView, LPNETWORK lpNetwork, zPVOID *ppvConn )
{
   LPTASK            lpTask;
   zVIEW             vSubtask = 0;
   ViewClusterRecord lpViewCluster[ 100 ] = { 0 };
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;
   zCommitPacket     CommitPacket;
   LPCOMMITPACKET    lpCommitPacket;
   zPCHAR            pchOD_Names = 0;
   zPCHAR            pch;
   zPCHAR            pchLinkBuffer = 0;
   zLONG             lLinkBufferLth;
   zLONG             lCommitControl = 0;
   zBOOL             bFlushNeeded = FALSE;
   zSHORT            nOD_NameLth;
   zSHORT            nViewErrorIdx;
   zSHORT            nViewCount = 0;
   zSHORT            k;
   zSHORT            nRC = zCALL_ERROR;

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Received Commit OI message.", "" );
      TraceLineS( "(kzoeneta) ** Retrieving Commit packet.", "" );
   }

   //=======================================================================
   // Receiving data.
   //
   // Until noted below, we will only RECEIVE data over the network.
   //=======================================================================

   // First thing to do is retrieve the commit info.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &lpCommitPacket, sizeof( zCommitPacket ),
                                   zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve Commit info", "" );
      goto EndOfFunction;
   }

   // Store the info locally -- as soon as we perform the next network IO
   // operation we aren't assured that lpCommitPacket points to valid data.
   zmemcpy( &CommitPacket, lpCommitPacket, sizeof( zCommitPacket ) );

   nViewCount     = (zSHORT) zxtol( CommitPacket.szViewCount );
   nOD_NameLth    = (zSHORT) zxtol( CommitPacket.szObjectNameLth );
   lLinkBufferLth = zxtol( CommitPacket.szLinkBufferLth );
   lCommitControl = zxtol( CommitPacket.szControl );

   // Get the list of object names.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &pch, nOD_NameLth, zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve the object names.", "" );
      goto EndOfFunction;
   }

   // Try to create a subtask view using the application name passed.
   if ( SfCreateSubtask( &vSubtask, lpTaskView, CommitPacket.szAppName ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Invalid App name = ", CommitPacket.szAppName );
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_INVALIDAPP ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
      }

      bFlushNeeded = TRUE;
      goto EndOfFunction;
   }

   lpTask = fnOperationCall( iNetCommitOI, vSubtask, 0 );
   pchOD_Names = fnAllocDataspace( lpTask->hFirstDataHeader, nOD_NameLth, TRUE, 0, 0 );
   if ( pchOD_Names == 0 )
      goto EndOfFunction;

   pchOD_Names = zGETPTR( pchOD_Names );
   zmemcpy( pchOD_Names, pch, nOD_NameLth );

   if ( lLinkBufferLth > 0 )
   {
      pchLinkBuffer = fnAllocDataspace( lpTask->hFirstDataHeader, lLinkBufferLth, TRUE, 0, 0 );
      if ( pchLinkBuffer == 0 )
         goto EndOfFunction;

      pchLinkBuffer = zGETPTR( pchLinkBuffer );

      if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                      &pch, lLinkBufferLth, zTYPE_STRING ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Couldn't retrieve the link buffer.", "" );
         goto EndOfFunction;
      }

      zmemcpy( pchLinkBuffer, pch, (zSHORT) lLinkBufferLth );

      if ( lpNetwork->nTraceLevel > 0 )
         TraceBuffer( "(kzoeneta) ** Link Buffer = ", pch, (zSHORT) lLinkBufferLth );
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLine( "(kzoeneta) ** App Name: %s  Object Def: %s  User Name: %s",
                 CommitPacket.szAppName, CommitPacket.szObjectDef, CommitPacket.szUserName );
      if ( nViewCount > 1 )
      {
         TraceLine( "(kzoeneta) ** View Count: %s  OD Name Lth: %d", CommitPacket.szViewCount, nOD_NameLth );
         TraceBuffer( "(kzoeneta) ** OD Names: ", pchOD_Names, nOD_NameLth );
      }
   }

   fnCreateMsgObj( vSubtask );

   // Make sure request is for valid ODs.
   for ( k = 0, pch = pchOD_Names; k < nViewCount; k++ )
   {
      if ( k > 0 )
      {
         // Skip to the beginning of the next name.
         while ( *pch++ )
            ;
      }

      // If *pch is 0 then there is no OD name.  If there is no OD name then
      // this particular view is skipped.
      if ( pch[ 0 ] == 0 )
         continue;

      if ( ActivateViewObject( vSubtask, pch, FALSE ) == 0 )
      {
         TraceLineS( "(kzoeneta) ** Invalid OD name = ", pch );
         if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_INVALIDOD ) != 0 )
         {
            TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
         }

         bFlushNeeded = TRUE;
         goto EndOfFunction;
      }
   }

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Receiving OIs to commit.", "" );

   // Retrieve the OIs we need to commit.
   for ( k = 0, pch = pchOD_Names; k < nViewCount; k++ )
   {
      zCHAR  szLth[ 5 ];
      zPCHAR pch2;
      zLONG  lLth;

      if ( k > 0 )
      {
         // Skip to the beginning of the next name.
         while ( *pch++ )
            ;
      }

      // If *pch is 0 then there is no OD name.  If there is no OD name then
      // this particular view is skipped.
      if ( pch[ 0 ] == 0 )
         continue;

      // Retrieve the OI.
      if ( fnReceiveOI( ppvConn, lpNetwork, &lpViewCluster[ k ].vOI, vSubtask,
                        pch, zMULTIPLE ) == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Not able to retrieve OIs for commit!", "" );
         goto EndOfFunction;
      }

      // Get the *length* of the control value for the view.
      if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                      &pch2, 2, zTYPE_STRING ) != 0 )
      {
         goto EndOfFunction;
      }

      szLth[ 0 ] = *pch2++;
      szLth[ 1 ] = *pch2;
      szLth[ 2 ] = 0;
      lLth = zxtol( szLth );

      // Get the *length* of the control value for the view.
      if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                      &pch2, lLth, zTYPE_STRING ) != 0 )
      {
         goto EndOfFunction;
      }

      lpViewCluster[ k ].lControl = zxtol( pch2 );

      // Turn on the flag to commit the OI on the current pc.
      lpViewCsr = zGETPTR( lpViewCluster[ k ].vOI->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
      lpViewOI->lActivateControl |= zACTIVATE_LOCAL;
   }

#ifdef DGC
   if ( lpNetwork->nTraceLevel > 0 )
   {
      zCHAR szTempFileName[ zMAX_FILENAME_LTH + 1 ];

      SysGetEnvVar( szTempFileName, "TEMP", zMAX_FILENAME_LTH + 1 );
      SysAppendcDirSep( szTempFileName );
      strcat_s( szTempFileName, zsizeof( szTempFileName ), "commitoi.por" );
      CommitOI_ToFile( vOI, szTempFileName, zINCREMENTAL );
   }
#endif

   //=======================================================================
   // Transmitting data.
   //
   // Until we close the connection, the following code only SENDS data over
   // the network.
   //=======================================================================

   bFlushNeeded = TRUE;

   // For now we won't execute constraints on the server.
   lCommitControl |= zCOMMIT_NOCONSTRAINTS;

   // If we received any link information we must now do relinking.
   if ( lLinkBufferLth > 0 )
      fnRelinkOIs( lpTask, lpViewCluster, nViewCount, pchLinkBuffer );

   // Tell commit that we don't want to clean up the OI and to leave the
   // entity flags.
   lCommitControl |= zCOMMIT_NOCLEANUP;

   // Commit the OI but tell Core not to clean up the deleted/excluded
   // instances.  We do this so that when we send the OI back to the client,
   // it can merge the committed OI with the original OI.
   nRC = CommitMultipleOIs( lpViewCluster, nViewCount, &nViewErrorIdx, lCommitControl );

   // Turn off the flag to commit the OI on the current pc.
   lpViewOI->lActivateControl &= ~zACTIVATE_LOCAL;

   if ( nRC == 0 )
   {
      for ( k = 0; k < nViewCount; k++ )
      {
         if ( lpViewCluster[ k ].vOI == 0 )
            continue;

         if ( lpNetwork->nTraceLevel > 0 )
            TraceLineI( "(kzoeneta) ** Sending committed OI #", k );

         if ( fnEmptyOI( lpViewCluster[ k ].vOI ) )
         {
            if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_EMPTYOI, 0 ) != 0 )
            {
               TraceLineS( "(kzoeneta) ** Not able to ACK request of OI!", "" );
               nRC = zCALL_ERROR;
               goto EndOfFunction;
            }
         }
         else
         {
            // Send Ack to signal we got this far.
            if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ACK, 0 ) != 0 )
            {
               TraceLineS( "(kzoeneta) ** Not able to ACK request of OI!", "" );
               nRC = zCALL_ERROR;
               goto EndOfFunction;
            }

            if ( fnSendOI( ppvConn, lpNetwork, lpViewCluster[ k ].vOI, zINCREMENTAL ) == zCALL_ERROR )
            {
               nRC = zCALL_ERROR;
               goto EndOfFunction;
            }
         }
      } // for...
   }

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineI( "(kzoeneta) ** Sending RC packet.  RC = ", nRC );

   // Send return code.
   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_RC, nRC ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Not able send Return code!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   // If we got an error then send the error idx.
   if ( nRC < 0 &&
        fnSendDataPacket( lpNetwork, ppvConn, zPACKET_RC, nViewErrorIdx ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Not able send Error Idx code!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   nRC = 0;

EndOfFunction:
   if ( vSubtask &&
        fnSendMsgAndTraceObj( lpNetwork, ppvConn, vSubtask ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
   }

   if ( bFlushNeeded && fnFlushBuffer( lpNetwork, ppvConn ) != 0 )
   {
      nRC = zCALL_ERROR;
   }

   if ( pchOD_Names )
      fnFreeDataspace( pchOD_Names );

   if ( pchLinkBuffer )
      fnFreeDataspace( pchLinkBuffer );

   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewCluster[ k ].vOI == 0 )
         continue;

      lpViewCsr = zGETPTR( lpViewCluster[ k ].vOI->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      // It's possible that we've activated the OI with pessimistic locking.
      // This means that there are records in the DB to lock out the OI.  But
      // Core automatically deletes those records when the OI is dropped.  This
      // is not good because the client that requested this OI obviously wants
      // the locks left in place.  To keep the locks we'll turn off the flag
      // that says the OI has pessimistic locking.  This will keep Core from
      // deleting the locks when we drop the view.
      lpViewOI->bIsLocked = 0;

      fnDropView( lpViewCluster[ k ].vOI );
   }

   if ( vSubtask )
      DROPSUBTASK( vSubtask );

   fnOperationReturn( iNetCommitOI, lpTask );
   return( nRC );

} // fnProcesssCommitOI

/*
   We got a message from another PC (the client) that it wants to commit
   an OI on the current PC (the server).  Process the commit and send
   the committed OI back to the client.
*/
zSHORT LOCALOPER
fnProcessCommitOI_ToFile( LPNETWORK lpNetwork, zPVOID *ppvConn )
{
   TraceLineS( "(kzoeneta) ** ", "fnProcessCommitOI_ToFile( ) is Deprecated" );
   return( 0 );

#if 0
   zSHORT nRC = 0;
   zBOOL  bFlushNeeded = FALSE;
   zVIEW  vSubtask = 0;
   zVIEW  vOI = 0;
   zPCHAR pch;
   zSHORT nFileNameLth;
   zBOOL  bSystem;
   zLONG  lControl;
   zCHAR  szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCommitPacket  CommitPacket;
   LPCOMMITPACKET lpCommitPacket;

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Received Commit OI message.", "" );
      TraceLineS( "(kzoeneta) ** Retrieving Commit packet.", "" );
   }

   //=======================================================================
   // Receiving data.
   //
   // Until noted below, we will only RECEIVE data over the network.
   //=======================================================================

   // First thing to do is retrieve the commit info.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &lpCommitPacket, zsizeof( zCommitPacket ),
                                   zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve Commit info", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   // Store the info locally -- as soon as we perform the next network IO
   // operation we aren't assured that lpCommitPacket points to valid data.
   zmemcpy( &CommitPacket, lpCommitPacket, zsizeof( zCommitPacket ) );
   lControl = zxtol( CommitPacket.szControl );

   // Retrieve the file name.
   nFileNameLth = (zSHORT) zxtol( CommitPacket.szFileNameLth );
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &pch, nFileNameLth,
                                   zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve file name.", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   strcpy_s( szFileName, zsizeof( szFileName ), pch );

#if 0
   /* this code doesn't work unless client changed, HH, 08.11.1996
   */
   strcpy_s( szFileName, zsizeof( szFileName ), vSubtask->hSubtask->hApp->hObjectDir );
   SysAppendcDirSep( szFileName );
   strcat_s( szFileName, zsizeof( szFileName ), pch );
#endif

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLine( "(kzoeneta) ** User Name: %s  App Name: %s  "
                   "Object Def: %s  File Name: %s",
                 CommitPacket.szUserName, CommitPacket.szAppName,
                 CommitPacket.szObjectDef, pch );
   }

   // Try to create a subtask view using the application name passed.
   if ( CREATESUBTASK( &vSubtask, CommitPacket.szAppName ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Invalid App name = ", CommitPacket.szAppName );
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR,
                             zNETERR_INVALIDAPP ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
      }

      nRC = zCALL_ERROR;
      bFlushNeeded = TRUE;
      goto EndOfFunction;
   }

   fnCreateMsgObj( vSubtask );

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Full name  = ", szFileName );

   // Make sure request is for valid OD.
   if ( lControl & zACTIVATE_SYSTEM )
      bSystem = TRUE;
   else
      bSystem = FALSE;
   if ( ActivateViewObject( vSubtask, CommitPacket.szObjectDef, bSystem ) == 0 )
   {
      TraceLineS( "(kzoeneta) ** Invalid OD name = ", CommitPacket.szObjectDef );
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR,
                             zNETERR_INVALIDOD ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
      }

      nRC = zCALL_ERROR;
      bFlushNeeded = TRUE;
      goto EndOfFunction;
   }

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Receiving OI to commit.", "" );
   }

   // Retrieve the OI we need to commit.  Add the zACTIVATE_SYSTEM flag if it
   // is specified in lControl.
   nRC = fnReceiveOI( ppvConn, lpNetwork, &vOI, vSubtask,
                      CommitPacket.szObjectDef,
                      zMULTIPLE | ( lControl & zACTIVATE_SYSTEM ) );
   if ( nRC == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Not able to retrieve OI for commit!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   //=======================================================================
   // Transmitting data.
   //
   // Until we close the connection, the following code only SENDS data over
   // the network.
   //=======================================================================

   bFlushNeeded = TRUE;

   if ( fnCheckForClientAuthority( ppvConn, lpNetwork,
                                   CommitPacket.szAppName,
                                   CommitPacket.szUserName,
                                   CommitPacket.szPassword,
                                   CommitPacket.szObjectDef,
                                   zLADTYPE_LOD_COMMIT_FILE ) < 0 )
   {
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR,
                              zNETERR_NOAUTHORITY ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_ERROR", "" );
      }

      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   SetNameForView( vOI, "__NetCommitWIP", 0, zLEVEL_TASK );

   // For right now we will assume that we commit files to the Bin dir
   // of the application.

   // Commit the OI but force the activate to occur locally.
   nRC = CommitOI_ToFile( vOI, szFileName, lControl | zACTIVATE_LOCAL );

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineI( "(kzoeneta) ** Sending RC packet.  RC = ", nRC );

   // Send return code.
   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_RC, nRC ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Not able send Return code!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   nRC = 0;

EndOfFunction:
   if ( vSubtask &&
        fnSendMsgAndTraceObj( lpNetwork, ppvConn, vSubtask ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
   }

   if ( bFlushNeeded && fnFlushBuffer( lpNetwork, ppvConn ) != 0 )
   {
      nRC = zCALL_ERROR;
   }

   if ( vOI )
      fnDropView( vOI );

   if ( vSubtask )
      DROPSUBTASK( vSubtask );

   return( nRC );
#endif

} // fnProcesssCommitOI_ToFile

/*
   We got a message from another PC (the client) that it wants to send a file
   to the current PC (the server).  Retrieve the file.
*/
zSHORT LOCALOPER
fnProcessSendFile( zVIEW lpTaskView, LPNETWORK lpNetwork, zPVOID *ppvConn )
{
   zVIEW  vSubtask = 0;
   zPCHAR pch;
   zSHORT nFileNameLth;
   zLONG  f = -1;
   zCHAR  szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR  cDataType;
   SendFileRecord sf;
   LPSENDFILE     lpSendFile;
   zSHORT iLineCount;
   zSHORT nRC = 0;

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Received Send File message.", "" );

   //=======================================================================
   // Receiving data.
   //
   // Until noted below, we will only RECEIVE data over the network.
   //=======================================================================

   // First thing to do is retrieve the commit info.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &lpSendFile, sizeof( sf ), zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve send file info", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   // Store the info locally -- as soon as we perform the next network IO
   // operation we aren't assured that lpCommitPacket points to valid data.
   zmemcpy( &sf, lpSendFile, sizeof( sf ) );

   // Retrieve the file name.
   nFileNameLth = (zSHORT) zxtol( sf.szFileNameLth );
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &pch, nFileNameLth, zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve file name.", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   // Store the filename to a more static location.
   strcpy_s( szFileName, zsizeof( szFileName ), pch );
   SysAppendcDirSep( szFileName );
   strcat_s( szFileName, zsizeof( szFileName ), &pch[ zstrlen( pch ) + 1 ] );

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLine( "(kzoeneta) ** App Name: %s  File Name: %s", sf.szAppName, szFileName );
   }

   // Try to create a subtask view using the application name passed.
   if ( SfCreateSubtask( &vSubtask, lpTaskView, sf.szAppName ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Invalid App name = ", sf.szAppName );
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR,
                             zNETERR_INVALIDAPP ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
      }

      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   fnCreateMsgObj( vSubtask );

   f = SysOpenFile( vSubtask, szFileName, COREFILE_WRITE );
   if ( f == -1 )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Receiving file.", "" );

   if ( sf.bBinaryFile == 'Y' )
   {
      cDataType = zTYPE_BLOB;
   }
   else
      cDataType = zTYPE_STRING;

   iLineCount = 0;
   while ( TRUE )
   {
      zCHAR   cPacketType;
      zULONG  lPacketData;
      zPCHAR  pchLine;

      if ( fnReceiveDataPacket( lpNetwork, ppvConn, &cPacketType, (zPLONG) &lPacketData ) != 0 )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      // lPacketData is the length of the line.  If it is 0, then we're at the
      // end of the file.
      if ( lPacketData == 0 )
         break;

      iLineCount++;

      if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                      &pchLine, lPacketData, cDataType ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Couldn't retrieve send file line", "" );
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      if ( sf.bBinaryFile == 'Y' )
      {
         if ( SysWriteFile( vSubtask, f, (zCPCHAR) pchLine, lPacketData ) < lPacketData )
         {
            TraceLineS( "(kzoeneta) ** Error writing line to file.", "" );
            nRC = zCALL_ERROR;
            goto EndOfFunction;
         }
      }
      else
      {
         if ( SysWriteLine( vSubtask, f, (zCPCHAR) pchLine ) < 0 )
         {
            TraceLineS( "(kzoeneta) ** Error writing line to file.", "" );
            nRC = zCALL_ERROR;
            goto EndOfFunction;
         }
      }

   } // while ( TRUE )...

   //=======================================================================
   // Transmitting data.
   //
   // Until we close the connection, the following code only SENDS data over
   // the network.
   //=======================================================================

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineI( "(kzoeneta) ** Sending # of lines.  Lines = ", iLineCount );
   }

   // Send number of lines received.
   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_RC, iLineCount ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Not able send line count!", "" );
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   if ( fnSendMsgAndTraceObj( lpNetwork, ppvConn, vSubtask ) == zCALL_ERROR )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   if ( fnFlushBuffer( lpNetwork, ppvConn ) != 0 )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   nRC = 0;

EndOfFunction:
   if ( f != -1 )
      SysCloseFile( vSubtask, f, 0 );

   if ( vSubtask )
      DROPSUBTASK( vSubtask );

   return( nRC );

} // fnProcesssSendFile

/*
   We got a message from another PC (the client) that it wants to initiate
   a transformation on the current PC (the server).  Call the transformation
   and return any changed arguments back to the client.
*/
zSHORT LOCALOPER
fnProcessOperation( zVIEW lpTaskView, LPNETWORK lpNetwork, zPVOID *ppvConn )
{
   LPTASK    lpTask;
   zBOOL     bFlushNeeded = FALSE;
   zBOOL     bTransformation;
   zLONG     lRC;
   zVIEW     vSubtask = 0;
   zVIEW     vArgs = 0;
   zCHAR     szAppName[ zAPPL_NAME_LTH ];
   zPCHAR    pchAppName;
   zPCHAR    pchObjectName;
   zPCHAR    pchUserName;
   zPCHAR    pchPassword;
   zPCHAR    pchOperName;
   zPCHAR    pchDLL_Name;
   zVIEW     vViewList[ 40 ];        // Max 40 views passed to transformation.
   zPVIEW    pvViewList[ 40 ];
   zSHORT    nViewCount = -1;
   zCHAR     szName[ zMAX_FILENAME_LTH + 1 ];
   LPAPP     lpApp;
   LPVIEWOD  lpViewOD;
   LPLIBRARY hLibrary;
   LPFN_CALLOPER pfnOper;
   zSHORT    nReturnCode = zCALL_ERROR;
   zSHORT    nRC;
   zSHORT    k;

   if ( lpNetwork->nTraceLevel > 0 )
   {
      TraceLineS( "(kzoeneta) ** Received Transformation message.", "" );
      TraceLineS( "(kzoeneta) ** Retrieving the Argument OI.", "" );
   }

   zmemset( vViewList, 0, zsizeof( vViewList ) );

   //=======================================================================
   // Receiving data.
   //
   // Until noted below, we will only RECEIVE data over the network.
   //=======================================================================
   // First retrieve the app name.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &pchAppName, zAPPL_NAME_LTH, zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve app name.", "" );
      goto EndOfFunction;
   }

   strcpy_s( szAppName, zsizeof( szAppName ), pchAppName );

   if ( SfCreateSubtask( &vSubtask, lpTaskView, szAppName ) == zCALL_ERROR )
      goto EndOfFunction;

   lpTask = fnOperationCall( iNetCallOperation, vSubtask, 0 );
   fnCreateMsgObj( vSubtask );

   if ( fnReceiveOI( ppvConn, lpNetwork, &vArgs, vSubtask, "kztranwo",
                     zSINGLE | zACTIVATE_SYSTEM ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Not able to retrieve Arg List!", "" );
      goto EndOfFunction;
   }

   bTransformation = (CompareAttributeToString( vArgs, "Operation", "OperationType", zTYPE_TRAN ) == 0);

   // Make sure it's a valid object.
   if ( bTransformation )
   {
      GetAddrForAttribute( &pchObjectName, vArgs, "Operation", "ObjectName" );
      lpViewOD = ActivateViewObject( vSubtask, pchObjectName, FALSE );
      if ( lpViewOD == 0 )
      {
         if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_INVALIDOD ) != 0 )
         {
            TraceLineS( "(kzoeneta) ** Error sending zPACKET_END", "" );
         }

         bFlushNeeded = TRUE;
         goto EndOfFunction;
      }
   }

   // Loop through each of the arguments looking for views.  If one is found
   // check to see if it was sent to us.  If so, retrieve it.
   for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vArgs, szlArgument, 0 ) )
   {
      zPCHAR pchApplName;
      zVIEW  vViewSubtask;

      // If the DataType is 'l', then this argument represents the client's
      // address ('l' for local).  To keep people from cheating, we will
      // retrieve the client address directly from the network.
      if ( CompareAttributeToString( vArgs, szlArgument, "DataType", "l" ) == 0 )
      {
         zCHAR szClientAddress[ 200 ];

         // Call network handler to get address of the remote node.
         if ( (*lpNetwork->lpfnGetAddress)( vSubtask, &lpNetwork->pNetworkHandle,
                                            ppvConn, 'R', szClientAddress ) != 0 )
         {
            goto EndOfFunction;
         }

         SetAttributeFromString( vArgs, szlArgument, "Value", szClientAddress );
         continue;
      }

      // If the argument is not a view, then don't worry about it.
      if ( CompareAttributeToString( vArgs, szlArgument, "DataType", "V" ) != 0 )
      {
         continue;
      }

      nViewCount++;
      vViewList[ nViewCount ] = 0;

      GetAddrForAttribute( &pchApplName, vArgs, szlArgument, "ApplicationName" );

      // If SubtaskView is 'Y', then the view is a subtask view so nothing
      // was sent but we do need to set up a subtask view.
      if ( CompareAttributeToString( vArgs, szlArgument, "SubtaskView", "Y" ) == 0 )
      {
         // ** Not Sure Which VIEW to use -----------------------\/
         SfCreateSubtask( &vViewList[ nViewCount ], lpTaskView, pchApplName );
         continue;
      }

      // If the client didn't send the argument, then continue.  The view
      // in vViewList has already been set to 0.
      if ( CompareAttributeToString( vArgs, szlArgument, "SendArgument", "N" ) == 0 )
      {
         continue;
      }

      // If application name was supplied then the current view argument is
      // for an object def from another application.  Create a temporary
      // subtask view for that application.
      if ( pchApplName && *pchApplName )
         SfCreateSubtask( &vViewSubtask, vSubtask, pchApplName );
      else
         vViewSubtask = vSubtask;  // Use "global" subtask.

      // Try retrieving the view from the network.
      GetAddrForAttribute( &pchObjectName, vArgs, szlArgument, "ObjectName" );
      nRC = fnReceiveOI( ppvConn, lpNetwork, &vViewList[ nViewCount ],
                         vViewSubtask, pchObjectName, zSINGLE );

      // If we created a temp subtask drop it.
      if ( pchApplName && *pchApplName )
         DROPSUBTASK( vViewSubtask );

      // Check return code from fnReceiveOI.
      if ( nRC == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Not able to retrieve Arg List!", "" );
         goto EndOfFunction;
      }

   } // for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 )...

   //=======================================================================
   // Transmitting data.
   //
   // Until we close the connection, the following code only SENDS data over
   // the network.
   //=======================================================================

   bFlushNeeded = TRUE;

   GetAddrForAttribute( &pchUserName, vArgs, "Operation", "UserName" );
   GetAddrForAttribute( &pchPassword, vArgs, "Operation", "Password" );
   GetAddrForAttribute( &pchOperName, vArgs, "Operation", "OperName" );

   SfGetApplicationForSubtask( &lpApp, vSubtask );

   // Set up the view pointer list.
   for ( k = 0; k < nViewCount; k++ )
      pvViewList[ k ] = &vViewList[ k ];

   pvViewList[ k ] = 0;
   strcpy_s( szName, zsizeof( szName ), lpApp->szLibraryDir );
   SysAppendcDirSep( szName );

   if ( bTransformation )
   {
      SfGetApplicationForSubtask( &lpApp, vSubtask );

      strcpy_s( szName, zsizeof( szName ), lpApp->szLibraryDir );
      SysAppendcDirSep( szName );
      pchDLL_Name = lpViewOD->szOperLibname;
      strcat_s( szName, zsizeof( szName ), lpViewOD->szOperLibname );
   }
   else
   {
      // Call the global operation.
      GetAddrForAttribute( &pchDLL_Name, vArgs, "Operation", "DLL_Name" );
      if ( pchDLL_Name && *pchDLL_Name )
      {
         strcat_s( szName, zsizeof( szName ), pchDLL_Name );
      }
   }

   hLibrary = SysLoadLibrary( vSubtask, szName );
   if ( hLibrary == 0 )
   {
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_NOEXECUTABLE ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_ERROR", "" );
      }

      TraceLineS( "(kzoeneta) ** Global operation library = ", szName );
      SysMessageBox( vSubtask, szlNetworkError,
                     "Can't find global oper lib.", 1 );
      goto EndOfFunction;
   }

   sprintf_s( szName, zsizeof( szName ), "_zCall_%s", pchOperName );
   pfnOper = (LPFN_CALLOPER) SysGetProc( hLibrary, szName );
   if ( pfnOper == 0 )
   {
      if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_ERROR, zNETERR_NOOPER ) != 0 )
      {
         TraceLineS( "(kzoeneta) ** Error sending zPACKET_ERROR", "" );
      }

      TraceLineS( "(kzoeneta) ** Global operation = ", szName );
      SysMessageBox( vSubtask, szlNetworkError, "Can't find _zCall... func.", 1 );
      SysFreeLibrary( vSubtask, hLibrary );
      goto EndOfFunction;
   }

   // Set up the view pointer list.
   for ( k = 0; k < nViewCount; k++ )
      pvViewList[ k ] = &vViewList[ k ];

   pvViewList[ k ] = 0;

   // Ok, boys, this is it--call the transformation shell.
   lRC = (*pfnOper)( vArgs, pvViewList );

   SysFreeLibrary( vSubtask, hLibrary );

   // Loop through each of the arguments looking for views that need to be
   // returned.  Later on we'll send the arg list object back to the client.
   // To save transmission time we'll null out the values of arguments that
   // we don't have to send back.
   k = -1;
   for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vArgs, szlArgument, 0 ) )
   {
      LPVIEWOD  lpWkViewOD;
      LPVIEWCSR lpViewCsr;
      LPVIEWOI  lpViewOI;

      // If the argument is not a view, then don't worry about it.
      if ( CompareAttributeToString( vArgs, szlArgument, "DataType", "V" ) != 0 )
      {
         // If we aren't sending the argument back then set it to null.
         if ( CompareAttributeToString( vArgs, szlArgument, "ReturnArgument", "Y" ) != 0 )
         {
            SetAttributeFromString( vArgs, szlArgument, "Value", "" );
         }

         continue;
      }

      k++; // Keep track of number of views.

      // If the view is not flagged as a returned view, forget it.
      nRC = CompareAttributeToString( vArgs, szlArgument, "ReturnArgument", "Y" );
      if ( nRC )
         continue;

      // Don't bother sending back the view if it is null.
      if ( vViewList[ k ] == 0 || vViewList[ k ]->hViewCsr == 0 )
         continue;

      lpWkViewOD = zGETPTR( vViewList[ k ]->hViewOD );
      SetAttributeFromString( vArgs, szlArgument, "ObjectName", lpWkViewOD->szName );

      lpViewCsr = zGETPTR( vViewList[ k ]->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      // If there is no root entity instance, then the OI is empty.
      if ( lpViewOI->hRootEntityInstance == 0 )
      {
         SetAttributeFromString( vArgs, szlArgument, "ViewReturned", "E" );
         continue;
      }

      // Set flag to indicate we are returning the view.
      SetAttributeFromString( vArgs, szlArgument, "ViewReturned", "Y" );

   } // for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 )...

   // Send return code.
   GetIntegerFromAttribute( &lRC, vArgs, "Operation", "ReturnValue" );
   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineI( "(kzoeneta) ** Sending RC packet.  RC = ", lRC );

   if ( fnSendDataPacket( lpNetwork, ppvConn, zPACKET_RC, lRC ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Not able send Return code!", "" );
      goto EndOfFunction;
   }

   // Send the vArgs view back to the client.
   if ( fnSendOI( ppvConn, lpNetwork, vArgs, 0 ) == zCALL_ERROR )
   {
      TraceLineS( "(kzoeneta) ** Not able send vArgs back to client!", "" );
      goto EndOfFunction;
   }

   // Loop through each of the arguments looking for views we need to send
   // back to the client.
   k = -1;
   for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vArgs, szlArgument, 0 ) )
   {
      // If the argument is not a view, then don't worry about it.
      if ( CompareAttributeToString( vArgs, szlArgument,
                                     "DataType", "V" ) != 0 )
         continue;

      k++;

      // Don't worry about the view if we're not sending it back.
      nRC = CompareAttributeToString( vArgs, szlArgument, "ViewReturned", "Y" );
      if ( nRC )
         continue;

#ifdef DGC
      if ( lpNetwork->nTraceLevel > 0 )
      {
         zCHAR szTempFileName[ zMAX_FILENAME_LTH + 1 ];

         SysGetEnvVar( szTempFileName, "TEMP", zMAX_FILENAME_LTH + 1 );
         SysAppendcDirSep( szTempFileName );
         strcat_s( szTempFileName, zsizeof( szTempFileName ), "tranoi.por" );
         CommitOI_ToFile( vViewList[ k ], szTempFileName,
                          zINCREMENTAL | zSAVE_CURSORS );
      }
#endif

      // Send the vArgs view back to the client.
      if ( fnSendOI( ppvConn, lpNetwork, vViewList[ k ], zINCREMENTAL | zSAVE_CURSORS ) == zCALL_ERROR )
      {
         TraceLineS( "(kzoeneta) ** Not able send view argument back to client!", "" );
         goto EndOfFunction;
      }

   } // for ( nRC = SetCursorFirstEntity( vArgs, szlArgument, 0 )...

   // If we get here then everything's fine...
   nReturnCode = 0;

EndOfFunction:
   if ( vSubtask &&
        fnSendMsgAndTraceObj( lpNetwork, ppvConn, vSubtask ) == zCALL_ERROR )
   {
      nReturnCode = zCALL_ERROR;
   }

   if ( bFlushNeeded && fnFlushBuffer( lpNetwork, ppvConn ) != 0 )
      nReturnCode = zCALL_ERROR;

   for ( k = 0; k <= nViewCount; k++ )
   {
      if ( vViewList[ k ] )
      {
         if ( vViewList[ k ]->hSubtask )
         {
            DROPSUBTASK( vViewList[ k ] );
         }
         else
            fnDropView( vViewList[ k ] );
      }
   }

   if ( vArgs )
      fnDropView( vArgs );

   if ( vSubtask )
      DROPSUBTASK( vSubtask );

   fnOperationReturn( iNetCallOperation, lpTask );
   return( nReturnCode );

} // fnProcesssOperation

// Retrieve Trace switch message and set the trace levels.
zSHORT LOCALOPER
fnProcessTraceSwitches( LPNETWORK lpNetwork, zPVOID *ppvConn, LPTASK lpTask )
{
   zCHAR szTraceSwitch[ L_TRACE_SWITCH_MSG + 1 ];
   zPCHAR pch;
   zSHORT k;

   // Retrieve the trace switch message.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &pch, L_TRACE_SWITCH_MSG, zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve Trace Switch Message", "" );
      return( zCALL_ERROR );
   }

   zmemcpy( &szTraceSwitch, pch, L_TRACE_SWITCH_MSG );
   szTraceSwitch[ L_TRACE_SWITCH_MSG ] = 0;
   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Received Trace Switch message.", szTraceSwitch );

   // server network tracelevel
   k = (zSHORT) zatol( szTraceSwitch + 4 );
   if ( k > lpNetwork->nTraceLevel )
      lpNetwork->nTraceLevel = k;

   // server DBHandler tracelevel
   szTraceSwitch[ 4 ] = 0;
   k = (zSHORT) zatol( szTraceSwitch + 2 );
   if ( k > lpTask->nDBHandlerTraceLevel )
      lpTask->nDBHandlerTraceLevel = k;

   // server core tracelevel
   szTraceSwitch[ 2 ] = 0;
   k = (zSHORT) zatol( szTraceSwitch );
   if ( k > 0 )
      lpTask->bTrace = TRUE;

   return( 0 );

} // fnProcessTraceSwitches

// Retrieve Timestamp message and set the task timestamp.
zSHORT LOCALOPER
fnProcessTimestamp( LPNETWORK lpNetwork, zPVOID *ppvConn, LPTASK lpTask )
{
   zPCHAR pch;

   // Retrieve the timestamp message.
   if ( (*lpNetwork->lpfnReceive)( &lpNetwork->pNetworkHandle, ppvConn,
                                   &pch, L_TIMESTAMP_MSG, zTYPE_STRING ) != 0 )
   {
      TraceLineS( "(kzoeneta) ** Couldn't retrieve Timestamp Message", "" );
      return( zCALL_ERROR );
   }

   // Set task timestamp from Server timestamp.
   zmemcpy( lpTask->szTimeStamp, pch, L_TIMESTAMP_MSG );
   lpTask->szTimeStamp[ L_TIMESTAMP_MSG ] = 0;
   if ( lpNetwork->nTraceLevel > 0 )
      TraceLineS( "(kzoeneta) ** Received Timestamp message.", lpTask->szTimeStamp );

   return( 0 );

} // fnProcessTimestamp

//./ ADD NAME=SfStartNetworks
// Source Module=kzoeneta.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       SfStartNetworks
//
//  PURPOSE:     To start all networks for the current task.
//
//  DESCRIPTION: Reads the Zeidon.INI file for the [Networks] group and
//               looks for keys matching "Network#=...".  For all matches
//               it reads the network group and sees if we need to start
//               the network.
//
//  PARAMETERS:  lControl - Reserved for future use.
//
//  RETURNS:     0           - Networks started OK.
//               zCALL_ERROR - Error starting networks.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
SfStartNetworks( zVIEW lpView, zLONG lControl )
{
   zCHAR  szValue[ 61 ];
   zCHAR  szStartup[ 61 ];
   zCHAR  szNetName[ 61 ];
   zCHAR  szGroupName[ 61 ];
   zCHAR  szExecName[ 61 ];
   int   k;

   // If user has specified a startup network, then start it up.
   TraceLineS( "(kzoeneta) ** Trying to startup networks", "" );

   szValue[ 0 ] = 0;
   szNetName[ 0 ] = 0;

   // Try starting all the networks.  They will be listed in the [network]
   // group as:
   //    [Network]
   //    Network1=zWinSock
   //    Network2=zNetBuei
   //    etc...
   for ( k = 1; TRUE; k++ )
   {
      sprintf_s( szNetName, zsizeof( szNetName ), "Network%d", k );
   // TraceLineS( "(kzoeneta) ** Looking for Net = ", szNetName );

      szValue[ 0 ] = 0;
      SysReadZeidonIni( -1, "[Network]", szNetName, szValue, zsizeof( szValue ) );
      if ( szValue[ 0 ] == 0 )
         break;               // No network# item so break loop.

      strcpy_s( szNetName, zsizeof( szNetName ), szValue );
      sprintf_s( szGroupName, zsizeof( szGroupName ), "[%s]", szValue );
      SysReadZeidonIni( -1, szGroupName, "Startup", szStartup, zsizeof( szStartup ) );
      if ( szValue[ 0 ] == 0 )
         continue;

      TraceLineS( "(kzoeneta) ** Startup = ", szStartup );

      // If Startup is NO, 0, or FALSE don't start it.
      if ( ztoupper( szStartup[ 0 ] ) == 'N' || szStartup[ 0 ] == '0' ||
           ztoupper( szStartup[ 0 ] ) == 'F' )
      {
         continue;
      }

      SysReadZeidonIni( -1, szGroupName, "ExecName", szExecName, zsizeof( szExecName ) );
      if ( szExecName[ 0 ] == 0 )
         strcpy_s( szExecName, zsizeof( szExecName ), szNetName );

      // If network is started see if we need to do a listen.
      if ( NetStartup( lpView, szNetName, szExecName ) != zCALL_ERROR )
      {
         SysReadZeidonIni( -1, szGroupName, "TraceLevel", szValue, zsizeof( szValue ) );
         if ( szValue[ 0 ] )
            NetSetTraceLevel( lpView, szNetName, (zSHORT) zatol( szValue ) );

         // TODO: CHANGE THIS
         // (BC) Not sure why this is Here, Listen is called in NetStartup
         //        so no need for it here

         // We only automatically start a listen for the main task.
         if ( ztoupper( szStartup[ 0 ] ) == 'L' &&
              (AnchorBlock->hMainTask == 0 ||
               AnchorBlock->hMainTask == lpView->hTask) )
         {
            TraceLineS( "(kzoeneta) *MainTask* Starting Listen", "" );
            if ( NetListen( lpView, szNetName ) == zCALL_ERROR )
            {
               TraceLineS( "(kzoeneta) ** Error calling NetListen", "" );
               NetClose( lpView, szNetName );
               return( zCALL_ERROR );
            }
         }/**/
      }
     else
        TraceLineS( "(kzoeneta) ** Error calling NetStartup!! ", "" );


   } // for k...

   TraceLineS( "(kzoeneta) ** Startup networks successful", "" );

   return( 0 );

} // SfStartNetworks
