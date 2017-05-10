/////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:  This is the source file which contains Windows specific
//               system services for use by the other DLL programs
//               which are non-operating system dependent. It
//               also contains all the startup shutdown operations
//               for Object services clients.
//
// OPERATIONS:   All Operations beginning with Sys
//               RegisterZeidonApplication
//               UnregisterZeidonApplication
//               InitializeAnchorBlock
//               FreeAnchorBlock
//               ProcessZeidonMessage
//
/////////////////////////////////////////////////////////////////////////////
//    Copyright © 1993 - 2016 QuinSoft, Inc.          All rights reserved.
//    Confidential and Proprietary material subject to license - do not
//    reproduce or disclose.  This material is an unpublished work and
//    is considered a trade secret belonging to the copyright holder.
/////////////////////////////////////////////////////////////////////////////
//
//  AUTHOR:  Gig Kirk
//  DATE:    3/31/92
//  API:     Win32
//  ENVIRONMENT: Win32
//
/////////////////////////////////////////////////////////////////////////////

//#define _CRT_SECURE_NO_WARNINGS 0

#include <windows.h>
#include <process.h>
#include "MeterSec.h"
#include "kzoedbga.h"

// Following calls asm to get the CPU clock cycles from a Pentium+ CPU.
// _VAR is a LARGE_INTEGER.
#define GET_CPU_TIME(_VAR)         \
   _asm                            \
   {                               \
       _asm push eax               \
       _asm push edx               \
       _asm _emit 0Fh              \
       _asm _emit 31h              \
       _asm mov _VAR.LowPart, eax  \
       _asm mov _VAR.HighPart, edx \
       _asm pop edx                \
       _asm pop eax                \
   }

#define KZOESYS_INCL
#define zGLOBAL_DATA
#include <kzoengaa.h>     // Object Services public prototypes

//#ifndef _CRT_SECURE_NO_WARNINGS
//#pragma message("after kzoengaa.h was not defined ===> " VAR_NAME_VALUE(_CRT_SECURE_NO_WARNINGS))
//#endif
//#pragma message("after kzoengaa.h ===> " VAR_NAME_VALUE(_CRT_SECURE_NO_WARNINGS))

#include <kzoengaa.hg>    // EXE and DLL globals
#include <kzoeltaa.hg>    // DLL only literals
#include <kzoemsaa.hg>    // Object Engine and Domain base messages
#include <zdecimal.h>     // Definitions for decimal interface.

zSHORT LOCALOPER
fnDropTaskOperation( LPTASK lpTask, LPTASKOPER lpTaskOperation );

#include <stdio.h>      // for lseek SEEK_SET definition
#if !defined( __IBMCPP__ )
   #include <dos.h>        // for SysGetDateTime
#endif
#include <direct.h>     // for _getcwd
#include <stdlib.h>     // for free( )
#include <malloc.h>     // for free( )
#include <sys\TimeB.h>  // For _ftime( )
#include <sys\stat.h>   // For stat( )
#include <Time.h>       // for _ftime( )
#include <string.h>     // for strstr( )
#include <io.h>
#include <math.h>
#include <htmlhelp.h>

#ifdef DEBUG
#define DEBUG_PAGETABLE
#endif

#define zZEIDON_DRIVER_MSG                           0x4000
#define zZEIDON_COMMUNICATE_OE      (zZEIDON_DRIVER_MSG + 1)
#define zZEIDON_POSTED_CLOSE        (zZEIDON_DRIVER_MSG + 2)

UINT g_wOENG_Message = 0;     // Memory management message
unsigned g_wClientMessage = 0;

zVOID LOCALOPER
fnTraceCompileTime( void );

// Comment out the following line to use Win32 mutexes instead of metered sections.
//#define __METERED_SECTION__

#define MUTEX_TIMEOUT   1000 * 60 * 10    // 10 minutes.

// Keep a global to indicate whether we have a Win95/98 or Win NT OS.
zBOOL    g_bWin95 = TRUE;

zINTEGER g_ZeidonMutexLockCnt[ zMUTEX_COUNT ] = { 0 };

CRITICAL_SECTION g_ZeidonCritTable[ zMUTEX_COUNT ];

// Critical sections.
CRITICAL_SECTION g_csSysLoadLibrary;
CRITICAL_SECTION g_csReuseEntity;

LPMUTEX LOCALOPER fnMutexFind( LPTASK lpTask, zCPCHAR cpcMutexName );
LPMUTEX LOCALOPER fnMutexCreate( LPTASK lpTask, zCPCHAR cpcMutexName,
                                 zLONG lControl, zBOOL bSkipSettingMutex );

// #define SHARED_MEM_TRACE
#ifdef SHARED_MEM_TRACE
   void LOCALOPER fnTraceSharedMemory( zCPCHAR cpcTitle );
#endif

// The instance handle for the current executable.  Set by DLLMain( ).
HINSTANCE g_hInstance = 0;

// The TLS ID for setting/getting the thread storage pointer.
DWORD g_hThreadInfo;

// If the following is TRUE then the current process has performed a
// RegisterZeidonApplication and hasn't unregistered yet.
zBOOL g_bProcessRegistered = FALSE;

// Task pointer for the current process.  When the current process is
// registered this will be non-zero.  Note this is a pointer NOT a handle.
// LPTASK g_lpCurrentTask = 0;

zCHAR szlNT_ThreadClassName[] = "ZeidonNT_ThreadClass";

// Process info is kept in a table.  Following is the idx for the current
// process in that table.
zLONG  g_lProcessIdx = -1;
zLONG  g_lCurrentProcessID;

// global variable defined in kzoeufaa.c
extern zPVOID g_pProbeArea;

#ifdef __MUTEX_DEBUG__

struct DbgMutexInfo * g_MutexInfoTable = 0;
HANDLE g_hMutexDbg     = 0;
HANDLE g_hMutexMemFile = 0;

void
fnPrintMutexInfo( zCHAR  cLock,
                  zLONG  lMutex,
                  zPCHAR pchFile,
                  zLONG  lLine )
{
#if 1 // dks debug
// return;
   if ( AnchorBlock && AnchorBlock->hFirstSysMutex )
      TraceLine( "%c   Mutex: %s (%d)   File: %s   Line: %d",
                 cLock, g_ZeidonMutexName[ lMutex ], lMutex, pchFile, lLine );
#else
   // Write mutex stuff to shared memory so another task can read it.
   zLARGE_INTEGER lNano;
   short          k;
   short          nOpenSlot;
   zLONG          lTaskID = SysGetProcessID( 0 );

   GET_CPU_TIME( lNano );

   // Single thread following code.
   WaitForSingleObject( g_hMutexDbg, INFINITE );

   if ( g_hMutexMemFile == 0 )
   {
      zBOOL bInit;
      zLONG lBytes = zsizeof( struct DbgMutexInfo );
      long  lLastError;

      // Allocate space for an extra mutex to handle SendMessage( ) as a mutex.
      lBytes *= zMUTEX_COUNT + 1;
      g_hMutexMemFile = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
                                           0, lBytes, MUTEXDBG_MEMNAME );

      lLastError = GetLastError( );
      if ( g_hMutexMemFile && lLastError != ERROR_ALREADY_EXISTS )
         bInit = TRUE;
      else
         bInit = FALSE;

      g_MutexInfoTable = MapViewOfFile( (HANDLE) g_hMutexMemFile,
                                        FILE_MAP_ALL_ACCESS, 0, 0, 0 );

      if ( bInit )
         zmemset( g_MutexInfoTable, 0, lBytes );
   }

   nOpenSlot = g_MutexInfoTable[ lMutex ].lLastTaskIdx;

   // See if we already have info for the current task.
   for ( k = 0; k < g_MutexInfoTable[ lMutex ].lLastTaskIdx; k++ )
   {
      if ( g_MutexInfoTable[ lMutex ].TaskInfo[ k ].lTaskID == lTaskID )
         break; // We have info for the current task so break.

      // Check to see if a "slot" is not being used.
      if ( g_MutexInfoTable[ lMutex ].TaskInfo[ k ].lTaskID == 0 )
         nOpenSlot = k;
   }

   // If we didn't find task info for the current task then create a new one
   // using the open slot we found.
   if ( k == g_MutexInfoTable[ lMutex ].lLastTaskIdx )
   {
      k = nOpenSlot;
      g_MutexInfoTable[ lMutex ].TaskInfo[ k ].lTaskID = lTaskID;

      if ( k == g_MutexInfoTable[ lMutex ].lLastTaskIdx )
         g_MutexInfoTable[ lMutex ].lLastTaskIdx++;
   }

   if ( pchFile )
   {
      zPCHAR pch;

      // Use just the file name (not the directory).
      for ( pch = pchFile + zstrlen( pchFile );
            pch >= pchFile && *pch != '\\';
            pch-- )
      {
         // Nothing needs to be done here.
      }

      pch++;
      strcpy_s( g_MutexInfoTable[ lMutex ].TaskInfo[ k ].szLockingFile,
                zsizeof( g_MutexInfoTable[ lMutex ].TaskInfo[ k ].szLockingFile ), pch );
      g_MutexInfoTable[ lMutex ].TaskInfo[ k ].lLockingLine = lLine;
   }

   g_MutexInfoTable[ lMutex ].TaskInfo[ k ].cStatus      = cLock;
   g_MutexInfoTable[ lMutex ].TaskInfo[ k ].lTimeRequest = lNano;

   if ( cLock == 'L' )
      g_MutexInfoTable[ lMutex ].nLockCount++;
   else
   if ( cLock == 'U' )
      g_MutexInfoTable[ lMutex ].nLockCount--;

   ReleaseMutex( g_hMutexDbg );
#endif
}

#endif //__MUTEX_DEBUG__

#define stat _stat

zPVOID LOCALOPER
fnMapFile( HANDLE  *phHandle,
           zLONG   lBytes,
           zPLONG  plPageTableIndex,
           zCPCHAR cpcShareName );

#define KZOEE001  1
#define KZOEE002  2
#define KZOEE003  3
#define KZOEE004  4
#define KZOEE005  5
#define KZOEE006  6
#define KZOEE007  7
#define KZOEE008  8
#define KZOEE009  9

#define IDM_LISTTASKS       112
#define IDM_GETWEBTRACE     214
#define IDM_GETMEMORYTRACE  217

#define fnLogAllocMem( cpcText, lSize, lHandle, lTaskID )
#define fnLogFreeMem( cpcText, lHandle )

zVOID
fnSetProcessIdx( zCPCHAR cpcText, LPPROCESSLIST *ppProcessList )
{
   LPANCHOROS_RECORD pOS_Record = &AnchorBlock->OS_Data;

   if ( g_lProcessIdx == -1 )
   {
      // Find an open cell in the Process record.
      for ( g_lProcessIdx = 0;
            pOS_Record->ProcessList[ g_lProcessIdx ].lProcessID != 0;
            g_lProcessIdx++ )
      {
         if ( g_lProcessIdx >= zMAX_PROCESSES )
         {
            SysMessageBox( 0, szlOE_SystemError, "Exceeded Process Limit ... Contact Zeidon Support", -1 );
            break;
         }
      }

      // pOS_Record->lProcessCount keeps track of the highest process idx.
      if ( g_lProcessIdx >= pOS_Record->lProcessCount )
         pOS_Record->lProcessCount = g_lProcessIdx + 1;
   }

   *ppProcessList = &pOS_Record->ProcessList[ g_lProcessIdx ];
   (*ppProcessList)->lProcessID = GetCurrentProcessId( );

// TraceLine( "%s:  fnSetProcessIdx =======================>>>>> ProcessIdx: %d   CurrentProcess: %d",
//            cpcText, g_lProcessIdx, (*ppProcessList)->lProcessID );
}

//./ ADD NAME=FindWebSubtask
// Source Module=kzoesyaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   FindWebSubtask
//
//  PURPOSE:    To locate the task/subtask using the session id.
//
//  PARAMETERS: cpcSessionId - Unique task session id from Tomcat.
//
//  RETURNS:    zVIEW    - Web Subtask for the task
//              0 (NULL) - Could not find the task
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zVIEW  OPERATION
FindWebSubtask( zCPCHAR cpcSessionId )
{
   LPTASK lpTask;

   if ( AnchorBlock == 0 )
      return( 0 );

   // Make sure nobody else is creating/deleting a task.
   fnStartBrowseOfTaskList( AnchorBlock->hFirstTask, FALSE );

   lpTask = zGETPTR( AnchorBlock->hFirstTask );
   while ( lpTask )
   {
      if ( lpTask->bTransientTask && lpTask->bShutdown == FALSE &&
           zstrcmp( lpTask->szSessionId, cpcSessionId ) == 0 )
      {
         break;
      }

      lpTask = zGETPTR( lpTask->hNextTask );
   }

   fnEndBrowseOfTaskList( FALSE );

   if ( lpTask )
      return( lpTask->vWebSubtask );
   else
      return( 0 );
}

//./ ADD NAME=SysGetProcessID
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetProcessID
//
//  PURPOSE:    To get the unique identifier of the current process
//
//  PARAMETERS: NONE
//
//  RETURNS:    A number representing a unique identifier
//              for the current process
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG OPERATION
SysGetProcessID( zPLONG plThreadID )
{
   zLONG lProcessID = (zLONG) GetCurrentProcessId( );
   if ( plThreadID )
      *plThreadID = (zLONG) GetCurrentThreadId( );

   return( lProcessID );
}

//./ ADD NAME=SysGetTaskFromView
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetTaskFromView
//
//  PURPOSE:    To get the unique identifier of the current task
//
//  PARAMETERS: NONE
//
//  RETURNS:    A number representing a unique identifier
//              for the current task
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG OPERATION
SysGetTaskFromView( zVIEW lpView )
{
   if ( lpView )
      return( (zLONG) lpView->hTask );
   else
      return( 0 );
}

zSHORT OPERATION
SysSetDefaultTaskForProcess( zVIEW vTaskView )
{
   SysMessageBox( vTaskView, "Zeidon Object Services",
                  "SysSetDefaultTaskForProcess Deprecated", 0 );
   return( zCALL_ERROR );

   if ( g_vDefaultTaskView && vTaskView )
   {
      SysMessageBox( vTaskView, "Zeidon Object Services",
                     "Process already has a default task view", 0 );
      return( zCALL_ERROR );
   }

   g_vDefaultTaskView = vTaskView;
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// Tomcat runs each of the clients in a separate thread, all in the same
// process.  This was why we need to make the changes that led to 10c:
// 10b expected each Zeidon task to run in its own process.  10c can have
// multiple Zeidon tasks all run under the same process.  In fact, they can
// all run under the same thread.  Since Zeidon tasks can run under the
// same process they can share the handlers, operations, etc. that you
// listed without any problems.
//
// The mutexes will work regardless of whether Zeidon tasks are in one
// process or multiple processes.  They are inefficient if all Zeidon tasks
// are under one process but it should be ok.
//
// The concern regarding mutexes is "double-checked" locking.  Say we have a
// global variarable that points to a view.  We'd initialize it to null and
// then check it when we want to use it.  Something like this:
//
// zVIEW g_vGlobalView = NULL;
//
// void SomeFunction
// {
//         if ( g_vGlobalView == NULL )
//         {
//                 // initialize g_vGlobalView
//         }
// }
//
// If SomeFunction can be called by multiple threads at the same time, we
// have to put a mutex around it to make sure g_vGlobalView doesn't get
// initialized twice:
//
// void SomeFunction
// {
//    LOCK_MUTEX( mutex-name );
//    if ( g_vGlobalView == NULL )
//    {
//       // initialize g_vGlobalView
//    }
//    UNLOCK_MUTEX( mutex-name );
// }
//
// The problem is that mutexes are expensive and we want to avoid them, so
// we "double check" the view pointer:
//
// void SomeFunction
// {
//    if ( g_vGlobalView == NULL )
//    {
//       LOCK_MUTEX( mutex-name );
//       if ( g_vGlobalView == NULL )
//       {
//          // initialize g_vGlobalView
//       }
//       UNLOCK_MUTEX( mutex-name );
//    }
// }
//
// This way we lock the mutex very rarely.  This generally works.  The
// problem is that the compiler might store the value of g_vGlobalView in a
// register and BOTH 'if' checks use the same value.  In other words the
// value of g_vGlobalView isn't re-loaded for the second 'if' statement.
// To protect against this, g_vGlobalView needs to be declared with the
// 'volatile' keyword:
//
// volatile zVIEW g_vGlobalView = NULL;
//
// This tells the compiler to reload the value of g_vGlobalView *every*
// time it gets used.  You can see the trade-off: depending on how often
// g_vGlobalView is used it could slow down processing because it is
// reloaded every single time it's used.  If it's used all over the place
// it would probably be better to *not* double-check the value when
// entering the mutex.
//
// I'm pretty sure that core uses double-checked locking in a few places.
// You might want to look through the code for all the places we lock a
// mutex and possibly fix it.  If you do a google on "double-checked"
// you'll find some more info on the problem.
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zLONG OPERATION
SetTransientTaskProcess( zCPCHAR cpcSessionId, zVIEW vSubtask, zBOOL bOn, zCPCHAR cpcTitle )
{
   LPTASK lpTask;
   zLONG  lProcessID;
   zLONG  lThreadID;

   lProcessID = SysGetProcessID( &lThreadID );
   if ( vSubtask == 0 )
   {
      TraceLine( "Session Id: %s  ==> %s (%s)  Thread: %d ... null Subtask",
                 cpcSessionId, bOn ? "ON " : "OFF", cpcTitle, lThreadID );
      return( -1 );
   }

   lpTask = zGETPTR( vSubtask->hTask );
   if ( lpTask->bWebTrace )
   {
      TraceLine( "STP S/V/T: %s/0x%08x/0x%08x  ==> %s (%s)  Thread: %d",
                 cpcSessionId, vSubtask, vSubtask->hTask, bOn ? "ON " : "OFF", cpcTitle, lThreadID );
   }

   if ( zstrcmp( cpcSessionId, lpTask->szSessionId ) != 0 )
   {
      TraceLine( "STP S/V/T: %s/0x%08x/0x%08x  ==> Conflict with Task Session Id: %s  (%s)  Thread: %d",
                 cpcSessionId, vSubtask, vSubtask->hTask, lpTask->szSessionId, cpcTitle, lThreadID );
   // SysMessageBox( vSubtask, "SetTransientTaskProcess", "Conflicting Session Id's", -1 );
   }

   if ( bOn )
   {
      // Lock critical section so other threads don't muck stuff.
      EnterCriticalSection( (LPCRITICAL_SECTION) lpTask->pcsCriticalSection );
   // TraceLine( "EnterCriticalSection STP S/V/T: %s/0x%08x/0x%08x  ==> %s (%s)  Thread: %d",
   //            cpcSessionId, vSubtask, vSubtask->hTask, bOn ? "ON " : "OFF", cpcTitle, lThreadID );
#if 1
      SysGetDateTime( lpTask->szTimeStamp, zsizeof( lpTask->szTimeStamp ) );
#else
      if ( FindWebSubtask( cpcSessionId ) == vSubtask )
      {
         SysGetDateTime( lpTask->szTimeStamp, zsizeof( lpTask->szTimeStamp ) );
      }
      else
      {
      // LeaveCriticalSection( (LPCRITICAL_SECTION) lpTask->pcsCriticalSection );
         return( -1 );
      }
#endif
   }
   else
   {
#if 0 // The task is running as a thread within the process, so the resources should be
      // good to go.
      fnCloseTaskNetworkModules( lpTask );
      fnDropTaskHandlers( lpTask );
      fnCloseTaskOpenFiles( lpTask );
      fnDropTaskDomains( lpTask );
      fnFreeTaskModules( lpTask );
      fnDropTaskOperations( lpTask );
      fnDropTaskMutexes( lpTask );
#endif

   // TraceLine( "LeaveCriticalSection STP S/V/T: %s/0x%08x/0x%08x  ==> %s (%s)  Thread: %d",
   //            cpcSessionId, vSubtask, vSubtask->hTask, bOn ? "ON " : "OFF", cpcTitle, lThreadID );
      LeaveCriticalSection( (LPCRITICAL_SECTION) lpTask->pcsCriticalSection );

   // SysSetDefaultTaskForProcess( 0 );
   }

   return( 0 );
}

zSHORT OPERATION
SysMakeWebFileName( zPCHAR pchReturnName, zLONG lMaxLth, zVIEW v, zLONG lFlags )
{
   LPAPP  lpApp;
   LPTASK lpTask;
   zCHAR  szName[ 64 ];

   SfGetApplicationForSubtask( &lpApp, v );

   pchReturnName[ 0 ] = 0;
   if ( lFlags & 0x00000001 )  // use Application
   {
      if ( lpApp )
         strcpy_s( pchReturnName, zMAX_FILESPEC_LTH, lpApp->szLocalDir );
   }
   else
   if ( lFlags & 0x00000002 )  // use Ini WebDirectory
   {
      if ( lpApp )
      {
         strcpy_s( szName, zsizeof( szName ), "[App." );
         strcpy_s( szName + 5, zsizeof( szName ) - 5, lpApp->szName );
         strcat_s( szName, zsizeof( szName ), "]" );
         SysReadZeidonIni( -1, szName, "WebDirectory", pchReturnName, lMaxLth );
      }

      if ( pchReturnName[ 0 ] == 0 )
         SysReadZeidonIni( -1, "[Workstation]", "WebDirectory", pchReturnName, lMaxLth );
   }

   if ( pchReturnName[ 0 ] )
      SysAppendcDirSep( pchReturnName );

   lpTask = zGETPTR( v->hTask );
   if ( lpTask->szSessionId[ 0 ] )
   {
      szName[ 0 ] = 's';
      szName[ 1 ] = 'i';
      strcpy_s( szName + 2, zsizeof( szName ) - 2, lpTask->szSessionId );
   }
   else
   {
      sprintf_s( szName, zsizeof( szName ), "0x%08x", (zULONG) v );
   }

   strcat_s( pchReturnName, zMAX_FILESPEC_LTH, szName );
// TraceLineS( "SysMakeWebFileName: ", pchReturnName );
   return( (zSHORT) zstrlen( pchReturnName ) );
}

zSHORT OPERATION
SysSetFocusToWebCtrl( zVIEW v, zCPCHAR cpcDialog, zCPCHAR cpcWindow,
                      zCPCHAR cpcEntity, zCPCHAR cpcCtrlTag )
{
   zVIEW      vKZXMLPGO;

   GetViewByName( &vKZXMLPGO, "KZXMLPGO", v, zLEVEL_TASK );
   if ( vKZXMLPGO )
   {
      zCHAR szFullCtrlTag[ 64 ];

      if ( SetCursorFirstEntityByString( vKZXMLPGO, "Dialog", "DialogName",
                                         cpcDialog, "" ) < zCURSOR_SET )
      {
         CreateEntity( vKZXMLPGO, "Dialog", zPOS_FIRST );
         SetAttributeFromString( vKZXMLPGO, "Dialog", "DialogName", cpcDialog );
      }

      if ( SetCursorFirstEntityByString( vKZXMLPGO, "Window", "WindowName",
                                         cpcWindow, "" ) < zCURSOR_SET )
      {
         CreateEntity( vKZXMLPGO, "Window", zPOS_FIRST );
         SetAttributeFromString( vKZXMLPGO, "Window", "WindowName", cpcWindow );
      }

      if ( cpcEntity && cpcEntity[ 0 ] )
      {
         zLONG  lKey = GetEntityKey( v, cpcEntity );
         zLONG  lLth;

         szFullCtrlTag[ 0 ] = '@';
         strcpy_s( szFullCtrlTag + 1, zsizeof( szFullCtrlTag ) - 1, cpcCtrlTag );
         lLth = zstrlen( szFullCtrlTag );
         szFullCtrlTag[ lLth++ ] = '#';
         zltoa( lKey, szFullCtrlTag + lLth, zsizeof( szFullCtrlTag ) - lLth );
      }
      else
         strcpy_s( szFullCtrlTag, zsizeof( szFullCtrlTag ), cpcCtrlTag );

      SetAttributeFromString( vKZXMLPGO, "Window", "FocusCtrl", szFullCtrlTag );

      return( 0 );
   }

   return( zCALL_ERROR );
}

zSHORT OPERATION
SysSetWebBannerName( zVIEW v, zCPCHAR cpcDialog, zCPCHAR cpcBannerName )
{
   zVIEW      vKZXMLPGO;

   GetViewByName( &vKZXMLPGO, "KZXMLPGO", v, zLEVEL_TASK );
   if ( vKZXMLPGO )
   {
      if ( SetCursorFirstEntityByString( vKZXMLPGO, "DynamicBannerName", "DialogName",
                                         cpcDialog, "" ) < zCURSOR_SET )
      {
         CreateEntity( vKZXMLPGO, "DynamicBannerName", zPOS_FIRST );
         SetAttributeFromString( vKZXMLPGO, "DynamicBannerName", "DialogName", cpcDialog );
      }

      SetAttributeFromString( vKZXMLPGO, "DynamicBannerName", "BannerName", cpcBannerName );

      return( 0 );
   }

   return( zCALL_ERROR );
}

zSHORT OPERATION
SysGetWebBannerName( zVIEW v, zCPCHAR cpcDialog, zPCHAR pchBannerName, zLONG lMaxLth )
{
   zVIEW      vKZXMLPGO;

   pchBannerName[ 0 ] = 0;
   GetViewByName( &vKZXMLPGO, "KZXMLPGO", v, zLEVEL_TASK );
   if ( vKZXMLPGO )
   {
      if ( SetCursorFirstEntityByString( vKZXMLPGO, "DynamicBannerName", "DialogName", cpcDialog, "" ) >= zCURSOR_SET )
      {
         GetStringFromAttribute( pchBannerName, lMaxLth, vKZXMLPGO, "DynamicBannerName", "DialogName" );
      }

      return( 0 );
   }

   return( zCALL_ERROR );
}

//./ ADD NAME=RegisterZeidonApplication
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:     RegisterZeidonApplication
//
//  PURPOSE:   This Operation Initializes the use of the Object Engine
//             executables.  It is used by the driver and any user written
//             programs to start CORE for processing a requested application.
//
//  PARAMETERS: AnchorBlock - void pointer to system anchor block
//              hMainWnd    - Handle to main window to which the
//                            Engine can pass a massage which
//                            the window in turn passes back to the
//                            Object Engine for task management
//              lMsg        - Application defined message which
//                            when received should result in a call
//                            to the operation ProcessZeidonMessage
//
//              ApplicationString - The application init string
//              is in the format:
//
//              {\\Application Name{\Dialog Name\User ID\Password command}}
//
//                Note that the application init string parameter separator
//                is now taken to be the first character encountered in the
//                parameter.
//
//              where:
//
//                Application Name - is an valid installed application name
//                                   defined to the zeidon system in the
//                                   file zeidon.pap which is located in
//                                   the directory referenced by the
//                                   ZEIDON environment variable. Note: if
//                                   the application name is a NULL pointer
//                                   OR a NULL string, then the register
//                                   will create a subtask for the system
//                                   application.
//
//                Dialog Name - is an optional starting Dialog name when
//                            invoking the driver. This parameter is
//                            ignored when the starting program is not
//                            the driver.
//
//                User ID - is an optional User ID for the application
//                          instance.
//
//                Password - is an optional Password associated with the
//                           UserID.
//
//                command - is an optional command string for the
//                          application to process.
//
// PROCESS:   If the object services executable KZOENG?A has not been started,
//            then it is started by the operation SysStartObjectServices.
//
// RETURNS:   0 - Task registered successfully
//  zCALL_ERROR - Task registration error
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 8
zSHORT  OPERATION
RegisterZeidonApplication( zPVIEW    pvSubtask,
                           zLONG     lSystemInstance,
                           zLONG     lMainWnd,
                           zLONG     lMsg,
                           zCPCHAR   cpcAppString,
                           zCPCHAR   cpcControlData,
                           zLONG     lControl )
{
   char   szTaskTitle[ 256 ];
   char   szAppName[ 64 ];
   char   szUserID[ 64 ];
   char   szDialog[ 64 ];
   char   szPassword[ 64 ];
   char   szCommand[ 256 ];
   LPAPP  lpApp;
   LPTASK lpTask;
   HWND   hWndMain = (HWND) lMainWnd;
   HANDLE hMutex;
   zLONG  lProcessID = 0;
   zLONG  lThreadID = 0;
   zSHORT k;
   zSHORT nRC;

   SysDescribeZeidonPageTable( szTaskTitle, zsizeof( szTaskTitle ) );
// SysMalloc( -2 );  // initialize memory usage (debug)

   // Check to see if the "termination" mutex is defined.  If it is then
   // KZOENGWA.EXE is in the process of shutting down so fail the request.
   if ( (hMutex = OpenMutex( MUTEX_ALL_ACCESS, FALSE, "KZOENGWA - Termination" )) != 0 )
   {
      // Close all the mutexes and get out.
      CloseHandle( hMutex );

      MessageBox( GetActiveWindow( ),
                  "The Zeidon Object Engine hasn't finished shutting down. "
                  "Please wait for the engine to shut down and restart.",
                  szlOE_SystemError, MB_ICONSTOP | MB_OK | MB_TASKMODAL );

      return( zCALL_ERROR );
   }

   // Parse the Application string passed in from the client
   fnParseAppString( szAppName, szDialog, szUserID,  szPassword, szCommand, cpcAppString );

   if ( szDialog[ 0 ] )
      strcpy_s( szTaskTitle, zsizeof( szTaskTitle ), szDialog );
   else
      szTaskTitle[ 0 ] = 0;

   zLOCK_MUTEX( zMUTEX_INITTERM );

   // See if we can initialize OE.
   k = SysStartObjectServices( lMsg, lMainWnd );
   if ( k )
   {
      zUNLOCK_MUTEX( zMUTEX_INITTERM );
      return( k );  // return if start not successful
   }

#ifdef ALLOC_FREE_TRACE
   AnchorBlock->bTraceMem = (zBOOL) SysSendOE_Message( IDM_GETMEMORYTRACE, 0 );
#endif

   nRC = zCALL_ERROR;   // Default nRC to bad (zCALL_ERROR)
   if ( (lpTask = fnCreateTask( lSystemInstance, (zLONG) hWndMain, lMsg, szTaskTitle )) != 0 )
   {
      // Current process has performed RegisterZeidonApp( ) so ...
      g_bProcessRegistered = TRUE;
   // g_lpCurrentTask = lpTask;

      zLOCK_MUTEX( zMUTEX_ANCHORBLOCK );

      lpApp = fnCreateApp( lpTask, szAppName );
      if ( lpApp )
      {
         LPSUBTASK lpFirstSubtask = zGETPTR( lpTask->hFirstSubtask );

         // Now point the application task to the application.
         lpTask->hApp = zGETHNDL( lpApp );
         lpFirstSubtask->hApp = lpTask->hApp;

         if ( szDialog && szDialog[ 0 ] )
            strcpy_s( lpTask->szDialog, zsizeof( lpTask->szDialog ), szDialog );
         else
            strcpy_s( lpTask->szDialog, zsizeof( lpTask->szDialog ), lpApp->szDefaultDialog );

         if ( szCommand[ 0 ] )
         {
            lpTask->hCommand = fnStoreStringInDataspace( (LPDATAHEADER) g_hAnchorBlock, szCommand );
         }
         else
            lpTask->hCommand = 0;

         // Task is now ready to go.

         if ( lControl & 0x00000001 )
         {
            zCHAR  chWebTrace;

            lpTask->bTransientTask = TRUE;
            lProcessID = SysGetProcessID( &lThreadID );

            TraceLineS( "InitCriticalSection: " , cpcControlData );

            lpTask->pcsCriticalSection = calloc( sizeof( CRITICAL_SECTION ), 1 );
            InitializeCriticalSection( (LPCRITICAL_SECTION) lpTask->pcsCriticalSection );
            EnterCriticalSection( (LPCRITICAL_SECTION) lpTask->pcsCriticalSection );
            chWebTrace = (zCHAR) SysSendOE_Message( IDM_GETWEBTRACE, 0 );
            if ( chWebTrace == 'Y' || chWebTrace == 'y' )
               lpTask->bWebTrace = TRUE;
         }

         lpTask->bDisable = FALSE;

         ActivateViewObject( zGETPTR( lpTask->hFirstView ), szlMessageObject, 0 );
         *pvSubtask = zGETPTR( lpTask->hFirstView );

         if ( lControl & 0x00000001 )
         {
            if ( cpcControlData && zstrlen( cpcControlData ) < zsizeof( lpTask->szSessionId ) )
            {
               strcpy_s( lpTask->szTaskTitle, zsizeof( lpTask->szTaskTitle ), cpcControlData );
               strcpy_s( lpTask->szSessionId, zsizeof( lpTask->szSessionId ), cpcControlData );
            }

            lpTask->vWebSubtask = *pvSubtask;
            SysGetDateTime( lpTask->szTimeStamp, zsizeof( lpTask->szTimeStamp ) );
         }

         SetViewFlags( *pvSubtask, zVF_MESSAGEONDROP );

      // {
      //    zPVOID p = zGETHNDL( lpTask );
      //
      //    TraceLine( "RegisterZeidonApplication for Task: 0x%08x (%d)", p, p );
      // }

         nRC = 0;
      }
      else
      {
         DeleteTask( lpTask );

         // Current process has performed RegisterZeidonApp( ) so ...
         g_bProcessRegistered = FALSE;
      // g_lpCurrentTask = 0;
      }

      zUNLOCK_MUTEX( zMUTEX_ANCHORBLOCK );
   }

   // Check nRC and do a task release on anchor block if init failed.
   if ( nRC )
   {
      if ( g_hAnchorBlock )
         fnFreeSharedMemory( 0, g_hAnchorBlock );
   }
   else
// if ( nRC == 0 )
      SfStartNetworks( *pvSubtask, 0 );

   if ( lControl & 0x00000001 )
   {
      if ( lpTask->bWebTrace )
      {
         TraceLine( "RegisterZeidonApplication ===============> %s   V/Task: 0x%08x / 0x%08x  Process: %d   Thread: %d",
                    cpcAppString, *pvSubtask, (*pvSubtask)->hTask, lProcessID, lThreadID );
      }
   }

   zUNLOCK_MUTEX( zMUTEX_INITTERM );

   TraceLine( "RegisterZeidonApplication ===============> %s   Process: %d   Thread: %d   Memory: %s   Wnd: 0x%08x=%d",
               cpcAppString, GetCurrentProcessId( ), GetCurrentThreadId( ), szTaskTitle, lMainWnd, lMainWnd );

   return( nRC );  // return the result
}

//./ ADD NAME=UnregisterZeidonApplication
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UnregisterZeidonApplication
//
//  PURPOSE:    To end Object Processing by a client, generally this
//              operation is called when a client done processing
//              and is going to end. However, this operation may
//              be used to disconnect from zeidon at any time and
//              free up task memory.
//
//  PARAMETERS: NONE
//
//  RETURNS:    0 - Task unregistered successfully
//             zCALL_ERROR - Task unregistration failed (Task not found)
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT  OPERATION
UnregisterZeidonApplication( zVIEW vTaskView )
{
   DWORD     dw;
   HWND      hMainWnd;
   HINSTANCE hInstance;

   LPTASK lpTask;
   zSHORT nRC;

   lpTask = zGETPTR( vTaskView->hTask );

   zLOCK_MUTEX( zMUTEX_INITTERM );

   hInstance = (HINSTANCE) lpTask->lHab;

   if ( lpTask->bTransientTask )
   {
      LeaveCriticalSection( (LPCRITICAL_SECTION) lpTask->pcsCriticalSection );
      DeleteCriticalSection( (LPCRITICAL_SECTION) lpTask->pcsCriticalSection );
      free( lpTask->pcsCriticalSection );
   }

   if ( AnchorBlock->TraceFlags.bTaskMsgs )
   {
      TraceLine( "(Unr) Cleaning up Registered S/Task: 0x%08x / 0x%08x (%d)   Process: %d   Thread: %d  %s",
                 vTaskView, vTaskView->hTask, lpTask, GetCurrentProcessId( ),
                 GetCurrentThreadId( ), lpTask->szSessionId );
   // {
   //    zVIEW        vDbhWork;
   //
   //    GetViewByName( &vDbhWork, zDBHANDLER_WORK_VIEW_NAME,
   //                   vTaskView, zLEVEL_SYSTEM );
   //    if ( vDbhWork )
   //    {
   //       DisplayObjectInstance( vDbhWork, 0, 0 );
   //       TraceLineS( "", "" );
   //    }
   // }
   }

   // Check to see if we should drop the object engine if there are no other
   // tasks.  We'll do the check now because DeleteTask drops the AnchorBlock.
   hMainWnd = 0;
   if ( AnchorBlock->bDropEngineIfNoTasks )
   {
      LPTASK lpSearchTask;
      zLONG  lCount = 0;

      // Count the number of tasks.
      for ( lpSearchTask = zGETPTR( AnchorBlock->hFirstTask );
            lpSearchTask;
            lpSearchTask = zGETPTR( lpSearchTask->hNextTask ) )
      {
         // We only care if there are 2 or fewer.
         if ( lCount++ > 1 )
            break;
      }

      // If there are only 2 tasks that means only the current one and the
      // system task are running.  Set the HWND so we'll know to drop the
      // engine later.
      if ( lCount <= 2 )
         hMainWnd = (HWND) AnchorBlock->lOE_hMainWnd;
   }

   nRC = DeleteTask( lpTask );

   // If hMainWnd is not 0 then we need to drop the engine.
   if ( hMainWnd )
      PostMessage( hMainWnd, WM_CLOSE, 0, 0 );

   zUNLOCK_MUTEX( zMUTEX_INITTERM );

   if ( !UnregisterClass( szlNT_ThreadClassName, hInstance ) )
      dw = GetLastError( );

   // Current thread has performed UnregisterZeidonApp( ) so ...
   g_bProcessRegistered = FALSE;
// g_lpCurrentTask = 0;

// SysMalloc( -1 );  // report memory usage (debug)

#ifdef __MUTEX_DEBUG__
   if ( g_MutexInfoTable )
   {
      zLONG  lTaskID = SysGetProcessID( 0 );
      zSHORT k, j;

      for ( k = 0; k < zMUTEX_COUNT; k++ )
      {
         for ( j = 0; j < g_MutexInfoTable[ k ].lLastTaskIdx; j++ )
         {
            if ( g_MutexInfoTable[ k ].TaskInfo[ j ].lTaskID != lTaskID )
               continue;

            g_MutexInfoTable[ k ].TaskInfo[ j ].lTaskID = 0;
            break;
         }
      }
   }
#endif

   return( nRC );
}

//./ ADD NAME=SysFreeInternational
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysFreeInternational
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zVOID OPERATION
SysFreeInternational( LPINTERNATIONAL lpInternational )
{
   if ( lpInternational &&
        lpInternational->nTableID == iInternational )
   {
      fnFreeDataspace( zGETPTR( lpInternational->hShortDate ) );
      fnFreeDataspace( zGETPTR( lpInternational->hLongDate ) );
      fnFreeDataspace( zGETPTR( lpInternational->hTimeFmt ) );
      fnFreeDataspace( lpInternational );
   }
}

//./ ADD NAME=fnConvertToZeidonFormat
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnConvertToZeidonFormat
//
//  PURPOSE:    Convert short or long date from WIN.INI to zeidon date
//              format.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zBOOL
fnConvertToZeidonFormat( zPCHAR pchFormat )
{
   zPCHAR   pch1;
   zPCHAR   pch2;
   zCHAR    sz[ 256 ];
   zBOOL    bError = 0;
   zBOOL    bImbedding = 0;
   zCHAR    cDelimiter = 0;

   pch1 = pchFormat;
   pch2 = sz;

   while ( *pch1 )
   {
      if ( cDelimiter )
      {
         if ( *pch1 == cDelimiter )
         {
            cDelimiter = 0;
            *pch2++ = *pch1++;
         }
         else
            *pch2++ = *pch1++;
      }
      else
      switch ( *pch1 )
      {
       case 'd':
       case 'D':
         if ( bImbedding )
         {
            *pch2++ = '\"';
            bImbedding = 0;
         }

         if ( zstrncmpi( (pch1 + 1), "DDD", 3 ) == 0 )
         {
            *pch2++ = 'D';
            zmemcpy( pch2, "ddd", 3 );
            pch1 += 4;
            pch2 += 3;
         }
         else
         if ( zstrncmpi( (pch1 + 1), "DD", 2 ) == 0 )
         {
            *pch2++ = 'D';
            *pch2++ = 'd';
            *pch2++ = 'd';
            pch1 += 3;
         }
         else
         if ( *(pch1 + 1) == 'D' ||
              *(pch1 + 1) == 'd' )
         {
            *pch2++ = 'D';
            *pch2++ = 'd';
            pch1 += 2;
         }
         else
         {
            *pch2++ = 'D';
            pch1++;
         }

         break;

       case 'm':
       case 'M':
         if ( bImbedding )
         {
            *pch2++ = '\"';
            bImbedding = 0;
         }

         if ( zstrncmpi( (pch1 + 1), "MMM", 3 ) == 0 )
         {
            *pch2++ = 'M';
            zmemcpy( pch2, "mmm", 3 );
            pch2 += 3;
            pch1 += 4;
         }
         else
         if ( zstrncmpi( (pch1 + 1), "MM", 2 ) == 0 )
         {
            *pch2++ = 'M';
            zmemcpy( pch2, "mm", 2 );
            pch2 += 2;
            pch1 += 3;
         }
         else
         if ( *(pch1 + 1) == 'M' ||
              *(pch1 + 1) == 'm' )
         {
            *pch2++ = 'M';
            *pch2++ = 'm';
            pch1 +=2;
         }
         else
         {
            *pch2++ = 'M';
            pch1++;
         }

         break;

       case 'y':
       case 'Y':
         if ( zstrncmpi( (pch1 + 1), "YYY", 3 ) == 0 )
         {
            if ( bImbedding )
            {
               *pch2++ = '\"';
               bImbedding = 0;
            }

            zmemcpy( pch2, "YYYY", 4 );
            pch2 += 4;
            pch1 += 4;
         }
         else
         if ( *(pch1 + 1) == 'Y' || *(pch1 + 1) == 'y' )
         {
            if ( bImbedding )
            {
               *pch2++ = '\"';
               bImbedding = 0;
            }

            *pch2++ = 'Y';
            *pch2++ = 'Y';
            pch1 += 2;
         }
         else
         if ( bImbedding )
            *pch2++ = *pch1++;
         else
            bError = 1;

         break;

       case '\"':  // quote
         if ( bImbedding )
         {
            bImbedding = 0;
            cDelimiter = *pch1++;
            break;
         }

       case '\'':  // apostrophe
         cDelimiter = *pch1;
         *pch2++ = *pch1++;
         break;

       case '(':   // left paren
       case ')':   // right paren
       case ':':   // colon
       case ',':   // comma
       case '-':   // dash
       case '/':   // slash
       case '.':   // period
       case ' ':   // space
         *pch2++ = *pch1++;
         break;

       default:
         if ( !bImbedding )
         {
            bImbedding = 1;
            *pch2++ = '\"';
         }

         *pch2++ = *pch1++;
      }

      if ( bError )
         break;
   }

   *pch2 = 0; // terminate the string.

   if ( bError == FALSE )
      strcpy_s( pchFormat, 512, sz );   // return the zeidon format

   if ( cDelimiter && bError == FALSE )
   {
      zCHAR sz[ 2 ];

      sz[ 0 ] = cDelimiter;
      sz[ 1 ] = 0;

      // "KZOEE360 - Missing ending delimiter "
      fnSysMessageBox( 0, "Zeidon Error", "Missing ending delimiter", 0 );
   // fnIssueCoreError( 0, lpView, 16, 360, 0, sz, "from WIN.INI" );
   }

   return( bError );
}

//./ ADD NAME=SysCreateInternational
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:      SysCreateInternational
//
// OS/2 documentation
// ==================
// Initialization files include information about printers, queues,
// and system preferences set by the user from the control panel.
// Applications can query this information by using the
// PrfQueryProfileData, PrfQueryProfileInt, PrfQueryProfileSize,
// and PrfQueryProfileString functions.
//
// All data in initialization files is accessed by a two-level
// hierarchy of application name, and key name within an application.
// Presentation Manager system data is keyed off "applications" that
// have names starting with PM_.
//
// The application name/key name combinations that applications may
// need to use are listed below, together with the definition of the
// corresponding data.
//
// Note:  Information that is prefixed with PM_SPOOLERxxxx cannot always
//        be modified directly:  The spooler validates all attempts to
//        write information to the INI file that it depends on.
//
//
//    Application name      "PM_ControlPanel"
//    Key name              "Beep"
//    Type                  integer
//    Content/value         1 or 0.
//
//    Application name      "PM_ControlPanel"
//    Key name              "LogoDisplayTime"
//    Type                  integer
//    Content/value         -1 <= time <= 32767 milliseconds.
//
//            Indefinite display  -1
//            No display           0
//            Timed display       >0
//
//    Application name      "PM_ControlPanel"
//    Key name              "cxDoubleClick"
//    Type                  integer
//    Content/value         SV_CXDBLCLK size in pels.
//
//    Application name      "PM_ControlPanel"
//    Key name              "cyDoubleClick"
//    Type                  integer
//    Content/value         SV_CYDBLCLK size in pels.
//
//    Application name      "PM_ControlPanel"
//    Key name              "cxMotionStart"
//    Type                  integer
//    Content/value         SV_CXMOTIONSTART size in pels.
//
//    Application name      "PM_ControlPanel"
//    Key name              "cyMotionStart"
//    Type                  integer
//    Content/value         SV_CYMOTIONSTART size in pels.
//
//    Application name      "PM_National"
//    Key name              "iCountry"
//    Type                  integer
//    Content/value         country code:
//
//       Arabic                 785
//       Australian              61
//       Belgian                 32
//       Canadian-French          2
//       Danish                  45
//       Finnish                358
//       French                  33
//       German                  49
//       Hebrew                 972
//       Italian                 39
//       Japanese                81
//       Korean                  82
//       Latin-American           3
//       Netherlands             31
//       Norwegian               47
//       Portuguese             351
//       Simpl. Chinese          86
//       Spanish                 34
//       Swedish                 46
//       Swiss                   41
//       Trad. Chinese           88
//       UK-English              44
//       US-English               1
//       Other country            0
//
//    Application name      "PM_National"
//    Key name              "iDate"
//    Type                  integer
//    Content/value         0=MDY; 1=DMY; 2=YMD.
//
//    Application name      "PM_National"
//    Key name              "iCurrency"
//    Type                  integer
//    Content/value         Values have the following meanings:
//
//            0   Prefix, no separator
//            1   Suffix, no separator
//            2   Prefix, 1 character separator
//            3   Suffix, 1 character separator.
//
//    Application name      "PM_National"
//    Key name              "iDigits"
//    Type                  integer
//    Content/value         n = number of decimal digits.
//
//    Application name      "PM_National"
//    Key name              "iTime"
//    Type                  integer
//    Content/value         0 = 12-hour clock; 1 = 24-hour clock.
//
//    Application name      "PM_National"
//    Key name              "iLZero"
//    Type                  integer
//    Content/value         0 = no leading zero; 1 = leading zero.
//
//    Application name      "PM_National"
//    Key name              "s1159"
//    Type                  string
//    Content/value         "am" for example. 3 chars max.
//
//    Application name      "PM_National"
//    Key name              "s2359"
//    Type                  string
//    Content/value         "pm" for example. 3 chars max.
//
//    Application name      "PM_National"
//    Key name              "sCurrency"
//    Type                  string
//    Content/value         "$" for example. 3 chars max.
//
//    Application name      "PM_National"
//    Key name              "sThousand"
//    Type                  string
//    Content/value         "," for example. 1 char max.
//
//    Application name      "PM_National"
//    Key name              "sDecimal"
//    Type                  string
//    Content/value         "." for example. 1 char max.
//
//    Application name      "PM_National"
//    Key name              "sDate"
//    Type                  string
//    Content/value         "/" for example. 1 char max.
//
//    Application name      "PM_National"
//    Key name              "sTime"
//    Type                  string
//    Content/value         ":" for example. 1 char max.
//
//    Application name      "PM_National"
//    Key name              "sList"
//    Type                  string
//    Content/value         "," for example. 1 char max.
//
//    Application name      PM_Fonts
//    Key name              <Font module name>
//    Type                  string
//    Content/value         fully-qualified drive:\path\filename.ext.
//
//    Application name      "PM_SPOOLER"
//    Key name              "QUEUE"
//    Type                  string
//    Content/value         <Queue name>;
//
//                          where: <Queue name> is the name of the default
//                                 queue (might be NULL).  This must be a
//                                 key name for the PM_SPOOLER_QUEUE
//                                 application.
//
//    Application name      "PM_SPOOLER"
//    Key name              " PRINTER"
//    Type                  string
//    Content/value         <Printer name>;
//
//                          where: <Printer name> is the name of the default
//                                 printer (might be NULL).
//
// Note:  Use the SplQueryDevice and SplQueryQueue functions to
//        retrieve the spooler configuration data.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
LPINTERNATIONAL OPERATION
SysCreateInternational( zVOID )
{
   LPINTERNATIONAL   lpInternational;
   zPVOID            hInternational;
   zCHAR             sz[ 512 ];

   hInternational =
      fnAllocDataspace( AnchorBlock->hMainFirstDataHeader,
                        sizeof( InternationalRecord ), 1, 0, iInternational );
   if ( hInternational == 0 )
      return( 0 );

   lpInternational = zGETPTR( hInternational );

   // Get country code, default to US
   lpInternational->nCountry = GetProfileInt( szlINTL, szlICOUNTRY, 1 );

   // Selected country name, no default
   GetProfileString( szlINTL, szlSCOUNTRY, szNullS, sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->szCountry, zsizeof( lpInternational->szCountry ), sz );

   // Get selected language code, default U.S. English
   GetProfileString( szlINTL, szlSLANGUAGE, "ENU", sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->szLanguage, zsizeof( lpInternational->szLanguage ), sz );

   // DGC: ????????????????? OS/2 ?????????? DKS 2/21/96 ?????????
   // Hard code the language code from the language string.
   // 0 - No default defined.
   if ( zstrcmpi( sz, "ENU" ) == 0 )
      lpInternational->nLanguage = 1;
   else
   if ( zstrcmpi( sz, "DEU" ) == 0 )
      lpInternational->nLanguage = 49;
   else
   if ( zstrcmpi( sz, "FRC" ) == 0 )
      lpInternational->nLanguage = 2;
   else
   if ( zstrcmpi( sz, "POR" ) == 0 ) // Portuguese 351
      lpInternational->nLanguage = 351;
   else
   if ( zstrcmpi( sz, "SPA" ) == 0 ) // Spanish 34
      lpInternational->nLanguage = 34;
   else
      lpInternational->nLanguage = 1; // lpInternational->nLanguage = 0;

   // List separator, default comma
   GetProfileString( szlINTL, szlSLIST, ",", sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->szList, zsizeof( lpInternational->szList ), sz );

   // Measurement system, default English
   // Time format, default 12 hour
   // Time Separator, default ":"
   lpInternational->nMeasure = GetProfileInt( szlINTL, szlIMEASURE, 1 );
   lpInternational->nTime = GetProfileInt( szlINTL, szlITIME, 0 );
   GetProfileString( szlINTL, szlSTIME, ":", sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->szTime, zsizeof( lpInternational->szTime ), sz );

   // Trailing string for AM, default "AM"
   GetProfileString( szlINTL, szlS1159, "AM", sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->sz1159, zsizeof( lpInternational->sz1159 ), sz );

   // Trailing string for PM, default "PM"
   GetProfileString( szlINTL, szlS2359, "PM", sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->sz2359, zsizeof( lpInternational->sz2359 ), sz );

   // Time leading zeros for hours, default yes
   // Picture for short date, default "mm/dd/yy"
   lpInternational->nTLZero = GetProfileInt( szlINTL, szlITLZERO, 1 );
   GetProfileString( szlINTL, szlSSHORTDATE, "mm/dd/yy", sz, zsizeof( sz ) - 1 );

   fnConvertToZeidonFormat( sz );
   lpInternational->hShortDate = fnStoreStringInDataspace( AnchorBlock->hMainFirstDataHeader, sz );

   // Picture for long date, default "mmm dd, yyyy"
   GetProfileString( szlINTL, szlSLONGDATE, "mmm dd, yyyy", sz, zsizeof( sz ) - 1 );

   fnConvertToZeidonFormat( sz );
   lpInternational->hLongDate = fnStoreStringInDataspace( AnchorBlock->hMainFirstDataHeader, sz );

   // Currency symbol, default "$"
   GetProfileString( szlINTL, szlSCURRENCY, "$", sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->szCurrency, zsizeof( lpInternational->szCurrency ), sz );

   // Current code format, default 0
   //
   // 0 - Currency symbol prefix with no separation ( $1 )
   // 1 - Currency symbol suffix with no separation ( 1$ )
   // 2 - Currency symbol prefix with one character separation ( $ 1 )
   // 3 - Currency symbol suffix with one character separation ( 1 $ )
   //

   // Number of digits used for the fractional part of a currency amount,
   // default 2.

   // Negative currency format code default 0
   //
   // 0  ($1)
   // 1  -$1
   // 2  $-1
   // 3  $1-
   // 4  (1$)
   // 5  -1$
   // 6  1-$
   // 7  1$-
   // 8  -1 $
   // 9  -$ 1
   // 10 $ 1-
   //

   // Symbol used to separate thousands in numbers with more than 3 digits,
   // default ","
   lpInternational->nCurrency = GetProfileInt( szlINTL, szlICURRENCY, 0 );
   lpInternational->nCurrDigits = GetProfileInt( szlINTL, szlICURRDIGITS, 2 );
   lpInternational->nNegCurr = GetProfileInt( szlINTL, szlINEGCURR, 0 );
   GetProfileString( szlINTL, szlSTHOUSAND, ",", sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->szThousand, zsizeof( lpInternational->szThousand ), sz );

   // Symbol used to separate the integer part from the fractional part
   // of a number, default "."
   GetProfileString( szlINTL, szlSDECIMAL, ".", sz, zsizeof( sz ) - 1 );

   strcpy_s( lpInternational->szDecimal, zsizeof( lpInternational->szDecimal ), sz );

   // Value defining the number of decimal digits that should be used in a
   // number, default 2

   // Value specifying whether a decimal value less than 1.0 (and greater
   // than -1.0) should contain a leading zero, as follows:
   //
   //  0    Do not use a leading zero (.7)
   //  1    Use a leading zero (0.7)
   //
   // Default is 1.
   lpInternational->nDigits = GetProfileInt( szlINTL, szlIDIGITS, 2 );
   lpInternational->nLZero = GetProfileInt( szlINTL, szlILZERO, 1 );

   // construct zeidon intl time format from the other indicators
   if ( lpInternational->nTLZero )
      strcpy_s( sz, zsizeof( sz ), "HH" );
   else
      strcpy_s( sz, zsizeof( sz ), "H" );

   strcat_s( sz, zsizeof( sz ), "\"" );
   strcat_s( sz, zsizeof( sz ), lpInternational->szTime );
   strcat_s( sz, zsizeof( sz ), "\"" );
   strcat_s( sz, zsizeof( sz ), "MI" );
   if ( lpInternational->nTime == 0 )
      strcat_s( sz, zsizeof( sz ), " AM" );

   lpInternational->hTimeFmt =
      fnStoreStringInDataspace( AnchorBlock->hMainFirstDataHeader, sz );

   return( hInternational );
}

//./ ADD NAME=SysGetLanguageCode
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetLanguageCode
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
SysGetLanguageCode( zPSHORT lpnLanguageCode )
{
   LPINTERNATIONAL   lpInternational;

   // Follow the chain from the AnchorBlock to the International Language
   // pointer to the International Language Code.  Then return the Code.

   lpInternational = zGETPTR( AnchorBlock->hInternational );
   *lpnLanguageCode = lpInternational->nLanguage;

   return( 0 );
}

//./ ADD NAME=SysSetLanguageCode
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysSetLanguageCode
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
SysSetLanguageCode( zSHORT nLanguageCode )
{
   LPINTERNATIONAL lpInternational;

   lpInternational = zGETPTR( AnchorBlock->hInternational );
   lpInternational->nLanguage = nLanguageCode;

   return( 0 );
}

zSHORT OPERATION
SysGetNumberFormat( zPCHAR pchReturnThou,
                    zPCHAR pchReturnDecPt,
                    zPLONG plPrecision )
{
   if ( AnchorBlock && AnchorBlock->hInternational )
   {
      LPINTERNATIONAL lpInternational;

      lpInternational = zGETPTR( AnchorBlock->hInternational );
      strcpy_s( pchReturnThou, 10, lpInternational->szThousand );
      strcpy_s( pchReturnDecPt, 10, lpInternational->szDecimal );
      *plPrecision = (zLONG) lpInternational->nDigits;
      return( 0 );
   }
   else
      return( zCALL_ERROR );
}

void OPERATION
SysGetTimeFormat( zPCHAR pchReturnString )
{
   *pchReturnString = 0;

   if ( AnchorBlock && AnchorBlock->hInternational )
   {
      LPINTERNATIONAL lpInternational = zGETPTR( AnchorBlock->hInternational );

      if ( lpInternational->hTimeFmt )
         strcpy_s( pchReturnString, 256, zGETPTR( lpInternational->hTimeFmt ) );
   }
}

void OPERATION
SysGetLongDateFormat( zPCHAR pchReturnString )
{
   *pchReturnString = 0;

   if ( AnchorBlock && AnchorBlock->hInternational )
   {
      LPINTERNATIONAL lpInternational = zGETPTR( AnchorBlock->hInternational );

      if ( lpInternational->hLongDate )
         strcpy_s( pchReturnString, 256, zGETPTR( lpInternational->hLongDate ) );
   }
}

void OPERATION
SysGetShortDateFormat( zPCHAR pchReturnString )
{
   *pchReturnString = 0;

   if ( AnchorBlock && AnchorBlock->hInternational )
   {
      LPINTERNATIONAL lpInternational = zGETPTR( AnchorBlock->hInternational );

      if ( lpInternational->hShortDate )
         strcpy_s( pchReturnString, 256, zGETPTR( lpInternational->hShortDate ) );
   }
}

// Converts environment strings in pchSource.
//   For example:            %kzd%:%kzv%\bin
//   Could be converted to:  c:\10d\bin
void LOCALOPER
fnConvertEnvironmentString( zPCHAR pchTarget, zLONG lMaxLth, zCPCHAR cpcSource )
{
   zPCHAR  pch;
   zPCHAR  pos;
   zPCHAR  pchCopy;
   
   pchCopy = SysMalloc( lMaxLth );
   strcpy_s( pchCopy, lMaxLth, cpcSource );
   pch = pchCopy;
   while ( *pch )
   {
      // If char is not % then just copy it to target string and continue.
      if ( *pch != '%' )
      {
         *pchTarget++ = *pch++;
         continue;
      }

      // Bump up pch to skip past %.
      pch++;

      // Look for final %.
      for ( pos = pch; *pos && *pos != '%'; pos++ )
         ; // Nothing needs to be done here.

      if ( *pos == 0 )
      {
         // Error -- no terminating %.
         SysMessageBox( 0, szlOE_SystemError, "No terminating '%' in ZEIDON.APP", -1 );

         // Try to get out as gracefully as possible.
         *pchTarget++ = '%';
         strcpy_s( pchTarget, lMaxLth, pch );
         return;
      }

      // Temporarily change '%' to null-terminator.
      *pos = 0;

      // Expand env var in the target string.
      SysGetEnvVar( pchTarget, pch, lMaxLth );

      // Change null-terminator back to '%'.
      *pos = '%';

      // Move pchTarget to point to null-terminator.
      while ( *pchTarget )
         pchTarget++;

      pch = pos + 1;

   } // while ( *pch )...

   // Terminate result.
   *pchTarget = 0;

   SysFree( pchCopy );

} // fnConvertEnvironmentString

void OPERATION
SysConvertEnvironmentString( zPCHAR pchTarget, zLONG lMaxLth, zCPCHAR cpcSource )
{
   fnConvertEnvironmentString( pchTarget, lMaxLth, cpcSource );
}

zSHORT
fnBuildZeidonIni( zPCHAR pchFileName, zSHORT nMaxLth )
{
   zSHORT nLth;

   SysGetEnvVar( pchFileName, szlZEIDON, nMaxLth );
   if ( pchFileName[ 0 ] )
   {
      SysAppendcDirSep( pchFileName );
      nLth = (zSHORT) zstrlen( pchFileName );
      strcpy_s( pchFileName + nLth, nMaxLth - nLth, "zeidon.ini" );
   }
   else
      nLth = 0;

   return( nLth );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      InitializeAnchorBlock
//
//  PURPOSE:    To create the main anchor block segment for
//              the Object Services. This operation is called
//              by KZOENGWA on startup to create the main Object
//              services task.
//
//  PARAMETERS: Object Services PM HAB
//              Object Services Main Window Handle
//              Object Services List/Trace Window Handle
//              Object Services Message for task Management (WM_USER)
//
//  RETURNS:    0 - Anchor block initialized successfully
//              zCALL_ERROR - Anchor block not initialized successfully
//
/////////////////////////////////////////////////////////////////////////////
LPANCHOR OPERATION
InitializeAnchorBlock( zLONG  OE_AnchorBlock,
                       zLONG  lOE_hMainWnd,
                       zLONG  lOE_hListWnd,
                       zLONG  lOE_Msg )
{
   zPVOID pvFile;
   char   szTaskTitle[ 256 ];
   char   szZeidonEnv[ 256 ];
   char   szSize[ 256 ];
   LPTASK lpMainTask;
   zLONG  lTaskAllocSize = zSHARED_ALLOC;
   zLONG  lSize = 16384;

   zmemset( szZeidonEnv, 0, zsizeof( szZeidonEnv ) );

   // Validate that environment variable ZEIDON set, NOTE: This
   // is done both here and in SysStartObjectServices on purpose
   // because ObjectServices can be started either alone or by
   // a client's RegisterZeidonApplication call.

   // Validate that environment variable ZEIDON set, NOTE: This
   // is done both here and in SysStartObjectServices on purpose
   // because ObjectServices can be started either alone or by
   // a client's RegisterZeidonApplication call.
   SysGetEnvVar( szZeidonEnv, szlZEIDON, zsizeof( szZeidonEnv ) );
   if ( szZeidonEnv[ 0 ] == 0 )
   {
      char szMessage[ 256 ];

      // {2,"KZOEE002 - ZEIDON environment variable not set"},
      SysGetBaseMessage( szMessage, KZOEE002, zsizeof( szMessage ) );
      SysMessageBox( 0, szlOE_SystemError, szMessage, -1 );

      return( (LPANCHOR) zCALL_ERROR );   // Error initializing anchor
   }

   {
      zCHAR szFileName[ zMAX_FILENAME_LTH + 1 ];

      fnBuildZeidonIni( szFileName, zsizeof( szFileName ) );
      lTaskAllocSize = GetPrivateProfileInt( "Zeidon", "AllocSize",
                                             lTaskAllocSize, szFileName );

      // Make sure size is at leask 64K
      if ( lTaskAllocSize < 64000 )
         lTaskAllocSize = zSHARED_ALLOC; // 262000L
   }

   // Edit the zeidon environment and make sure it ends with a
   // directory separator.
   SysAppendcDirSep( szZeidonEnv );

   zLOCK_MUTEX( zMUTEX_ANCHORINIT );

   // Allocate the main shared table space for the Anchor Block
#ifdef ALLOC_FREE_TRACE
   lSize += 3 * ALLOC_FREE_TRACE * sizeof( zPVOID );
#endif

   g_hAnchorBlock = fnInitializeDataspace( 0, (zCOREMEM) &AnchorBlock,
                                           iAnchor, "OE Anchor",
                                           lSize - sizeof( DataHeaderRecord ),
                                           szlShareSeg );

// TraceLineX( "Initialize AnchorBlock = ", (zLONG) AnchorBlock );

   // Reserve space for Anchor Block Information which occurs after the
   // Table Header and the Freespace record in the first Dataspace
   // suballocation.
// if ( g_bServerMode == FALSE )
   {
      fnAllocDataspace( (LPDATAHEADER) g_hAnchorBlock,
                        sizeof( AnchorRecord ) - (sizeof( DataHeaderRecord ) +
                                  sizeof( FreespaceRecord )),
                        1, 0, iAnchor );
   }

   if ( AnchorBlock == 0 )
   {
      zUNLOCK_MUTEX( zMUTEX_ANCHORINIT );
      return( 0 );
   }

   AnchorBlock->nStatus          = AnchorUninitialized;  // Init is pending
// AnchorBlock->lMainTaskID      = 0; // SysGetTaskID( );

#ifdef ALLOC_FREE_TRACE
   AnchorBlock->bTraceMem = (zBOOL) SysSendOE_Message( IDM_GETMEMORYTRACE, 0 );
#endif

   AnchorBlock->lTaskAllocSize   = lTaskAllocSize - sizeof( DataHeaderRecord );
   AnchorBlock->lHab             = OE_AnchorBlock;
   AnchorBlock->lOE_hMainWnd     = lOE_hMainWnd;
   AnchorBlock->lOE_hListWnd     = lOE_hListWnd;
   AnchorBlock->lOE_Msg          = lOE_Msg;
   AnchorBlock->hFirstTask       = 0;
   AnchorBlock->hMainTask        = 0;
   AnchorBlock->hSystemApp       = 0;
   AnchorBlock->hMainFirstDataHeader = 0;
   AnchorBlock->hFirstApp        = 0;
   AnchorBlock->hFirstTask       = 0;
// AnchorBlock->hFirstOpenFile   = 0; moved to Task
// AnchorBlock->hFirstProcLib    = 0; moved to Task
   strcpy_s( AnchorBlock->szZeidonLocal, zsizeof( AnchorBlock->szZeidonLocal ), szZeidonEnv );
   AnchorBlock->szZeidonBin[ 0 ] = 0;
   AnchorBlock->szZeidonSys[ 0 ] = 0;
   AnchorBlock->szZeidonLoc[ 0 ] = 0;
   AnchorBlock->szZeidonShr[ 0 ] = 0;
   AnchorBlock->szUserID[ 0 ]    = 0;
   AnchorBlock->szPassword[ 0 ]  = 0;
   AnchorBlock->hFirstViewName   = 0;
   AnchorBlock->nBrowseTaskListCounter = 0;
   AnchorBlock->bShowTaskID      = FALSE;
   AnchorBlock->bTraceCnt        = TRUE;
   AnchorBlock->bDropEngineIfNoTasks = FALSE;
   AnchorBlock->bDeleteTaskInProgress = FALSE;
   AnchorBlock->lpParentTask     = 0;
   AnchorBlock->hInternational   = 0;
   AnchorBlock->hFirstSysMutex   = 0;
   AnchorBlock->hFirstDebugChange = 0;
// AnchorBlock->TraceFlags       = 0;
   AnchorBlock->nMemoryTraceThreshold = 0;
   AnchorBlock->nMemoryCeiling   = 0;

   // Get Title of Main Task.
   GetWindowText( (HWND) lOE_hMainWnd, szTaskTitle, zsizeof( szTaskTitle ) - 1 );

   lpMainTask = fnCreateTask( OE_AnchorBlock, lOE_hMainWnd,
                              lOE_Msg, szTaskTitle );

   // Task is now ready to go.
   lpMainTask->bDisable = FALSE;

// g_lpCurrentTask = lpMainTask;

   AnchorBlock->hMainFirstDataHeader = lpMainTask->hFirstDataHeader;
   AnchorBlock->hMainTask = zGETHNDL( lpMainTask );
   if ( AnchorBlock->hMainTask )
   {
      LPPROCESSLIST lpProcessList;
      LPSUBTASK lpFirstSubtask;
      zPCHAR    pchLine;
      zLONG     hFile;
      int       nEOF;

      // Now that we have allocated the AnchorBlock's memory, we can
      // set the process index for the main task.
      fnSetProcessIdx( "InitAnchor", &lpProcessList );
      lpProcessList->uAppOE_Msg = (zUSHORT) lOE_Msg;
      lpProcessList->hWndAppOE_Msg = lOE_hMainWnd;

      // Now that we have created the main task, see if we can open
      // the zeidon applications file and get the directory pointers
      // for the zeidon exe directory and the zeidon system directory.
      strcat_s( szZeidonEnv, zsizeof( szZeidonEnv ), szlAppFile );
      hFile = fnSysOpenFile( lpMainTask, szZeidonEnv, COREFILE_READ );
      if ( hFile == -1 )
      {
         char szMessage[ 256 ];

         // {9,"KZOEE009 - Error opening application definition file"},
         SysGetBaseMessage( szMessage, KZOEE009, 255 );
         strcat_s( szMessage, zsizeof( szMessage ), " '" );
         strcat_s( szMessage, zsizeof( szMessage ), szZeidonEnv );
         strcat_s( szMessage, zsizeof( szMessage ), "'" );

         // Free the shared segment for KZOENGWA
         AnchorBlock->nStatus = AnchorCorrupt; // mark AnchorBlock as no good
         fnFreeSharedMemory( lpMainTask, g_hAnchorBlock ); // free for KZOENGAA.DLL

         // NULL AnchorBlock handle and pointer
         g_hAnchorBlock = 0;
         AnchorBlock  = 0;
         g_lProcessIdx = -1;

         fnSysMessageBox( lpMainTask, szlOE_SystemError, szMessage, 1 );
         zUNLOCK_MUTEX( zMUTEX_ANCHORINIT );
         return( 0 );
      }

      pvFile = 0;
      nEOF = fnSysReadLine( lpMainTask, &pchLine, hFile, &pvFile );
      while ( nEOF > 0 )
      {
         SysParseLine( szZeidonEnv, zsizeof( szZeidonEnv ), &pchLine, pchLine + 1 );
         if ( zstrcmp( szZeidonEnv, szlZEIDON_BIN ) == 0 )
         {
            fnConvertEnvironmentString( szZeidonEnv, zsizeof( szZeidonEnv ), pchLine );
            SysAppendcDirSep( szZeidonEnv );
            strcpy_s( AnchorBlock->szZeidonBin, zsizeof( AnchorBlock->szZeidonBin ), szZeidonEnv );
         }
         else
         if ( zstrcmp( szZeidonEnv, szlZEIDON_SYS ) == 0 )
         {
            fnConvertEnvironmentString( szZeidonEnv, zsizeof( szZeidonEnv ), pchLine );
            SysAppendcDirSep( szZeidonEnv );
            strcpy_s( AnchorBlock->szZeidonSys, zsizeof( AnchorBlock->szZeidonSys ), szZeidonEnv );
         }
         else
         if ( zstrcmp( szZeidonEnv, szlZEIDON_LOC ) == 0 )
         {
            fnConvertEnvironmentString( szZeidonEnv, zsizeof( szZeidonEnv ), pchLine );
            SysAppendcDirSep( szZeidonEnv );
            strcpy_s( AnchorBlock->szZeidonLoc, zsizeof( AnchorBlock->szZeidonLoc ), szZeidonEnv );
         }
         else
         if ( zstrcmp( szZeidonEnv, szlZEIDON_SHR ) == 0 )
         {
            fnConvertEnvironmentString( szZeidonEnv, zsizeof( szZeidonEnv ), pchLine );
            SysAppendcDirSep( szZeidonEnv );
            strcpy_s( AnchorBlock->szZeidonShr, zsizeof( AnchorBlock->szZeidonShr ), szZeidonEnv );
         }

         nEOF = fnSysReadLine( lpMainTask, &pchLine, hFile, &pvFile );
         if ( zstrncmp( pchLine + 1, szlAPPLICATION, zstrlen( szlAPPLICATION ) ) == 0 )
         {
            break;
         }
      }

      fnSysCloseFile( lpMainTask, hFile, 0 );
      if ( AnchorBlock->szZeidonBin[ 0 ] == 0 || AnchorBlock->szZeidonSys[ 0 ] == 0 )
      {
         char szMessage[ 256 ];

         // {8,"KZOEE008 - Application definition file missing ZEIDON_BIN or ZEIDON_SYS"},
         SysGetBaseMessage( szMessage, KZOEE008, 255 );
         strcat_s( szMessage, zsizeof( szMessage ), ", " );
         strcat_s( szMessage, zsizeof( szMessage ), AnchorBlock->szZeidonLocal );
         strcat_s( szMessage, zsizeof( szMessage ), szlAppFile );
         fnSysMessageBox( lpMainTask, szlOE_SystemError, szMessage, 1 );
      }
      else
      {
         LPAPP lpApp = fnCreateApp( lpMainTask, 0 );  // Create sys app
         AnchorBlock->hSystemApp = zGETHNDL( lpApp );
      }

      if ( AnchorBlock->szZeidonLoc[ 0 ] == 0 )
      {
         SysGetEnvVar( szZeidonEnv, "TEMP", zsizeof( szZeidonEnv ) );
         if ( szZeidonEnv[ 0 ] == 0 )
            SysGetEnvVar( szZeidonEnv, "TMP", zsizeof( szZeidonEnv ) );

         if ( szZeidonEnv[ 0 ] )
         {
            zCHAR sz[ zMAX_FILENAME_LTH + 1 ];

            fnConvertEnvironmentString( sz, zsizeof( sz ), szZeidonEnv );
            SysAppendcDirSep( sz );
            strcpy_s( AnchorBlock->szZeidonLoc, zsizeof( AnchorBlock->szZeidonLoc ), sz );
         }
      }

      lpMainTask->hApp = AnchorBlock->hSystemApp;
      lpFirstSubtask = zGETPTR( lpMainTask->hFirstSubtask );
      lpFirstSubtask->hApp = AnchorBlock->hSystemApp;
   }

   // If First task initialization failed, issue error and leave
   if ( !AnchorBlock->hMainTask || !AnchorBlock->hSystemApp )
   {
      // Free the shared segment for KZOENGWA
      AnchorBlock->nStatus = AnchorCorrupt;  // mark AnchorBlock as no good
      fnFreeSharedMemory( lpMainTask, g_hAnchorBlock ); // free for KZOENGAA.DLL

      // NULL AnchorBlock handle and pointer
      g_hAnchorBlock = 0;
      AnchorBlock    = 0;
      g_lProcessIdx  = -1;

      zUNLOCK_MUTEX( zMUTEX_ANCHORINIT );
      return( 0 );
   }

   // create international info from win.ini
   AnchorBlock->hInternational = SysCreateInternational( );

   SysReadZeidonIni( -1, "[ObjectEngine]", "MemoryTraceThreshold", szSize, zsizeof( szSize ) );
   AnchorBlock->nMemoryTraceThreshold = atoi( szSize );
   SysReadZeidonIni( -1, "[ObjectEngine]", "MemoryCeiling", szSize, zsizeof( szSize ) );
   AnchorBlock->nMemoryCeiling = atoi( szSize );

   zUNLOCK_MUTEX( zMUTEX_ANCHORINIT );

#ifdef __MUTEX_DEBUG__
   // We use 'zMUTEX_COUNT' as an ID for SendMessage.
   fnPrintMutexInfo( 's', zMUTEX_COUNT, __FILE__, __LINE__ );
#endif

   {

   COPYDATASTRUCT cd;

   cd.dwData = LB_ADDSTRING;
   cd.lpData = "Object Services Initialization complete...";
   cd.cbData = zstrlen( (zPCHAR) cd.lpData ) + 1;

   // Use WM_COPYDATA to send the message so we don't have any memory leaks.
   SendMessage( (HWND) AnchorBlock->lOE_hListWnd, WM_COPYDATA, 0, (LPARAM) &cd );
   if ( g_bServerMode )
      cd.lpData = "Object Services Running in Server Mode...";
   else
      cd.lpData = "Object Services Running in Shared Mode...";

   cd.cbData = zstrlen( (zPCHAR) cd.lpData ) + 1;
   SendMessage( (HWND) AnchorBlock->lOE_hListWnd, WM_COPYDATA, 0, (LPARAM) &cd );
   }

#ifdef __MUTEX_DEBUG__
   // We use 'zMUTEX_COUNT' as an ID for SendMessage.
   fnPrintMutexInfo( 'S', zMUTEX_COUNT, __FILE__, __LINE__ );
#endif

   fnTraceCompileTime( );
   MiListOE_Memory( 0, -1 );
   return( AnchorBlock );

}   // End of InitializeAnchorBlock

// This function is used to drop the local task's reference to the anchor
// block.  Should not be called from the main system task!
void LOCALOPER
fnFreeLocalAnchorBlock( zBOOL bWebTask )
{
   zLONG lPageTableIndex;

   // If we're in Server Mode or a Web Task, then there's no anchor block
   // to free.
   if ( g_bServerMode || bWebTask )
   {
      SysFree( AnchorBlock );
      return;
   }
   else
   {
      if ( g_bWin95 )
         lPageTableIndex = 1;
      else
#ifdef DEBUG_PAGETABLE
         lPageTableIndex = 128;
#else
         lPageTableIndex = 1;
#endif

#ifdef SHARED_MEM_TRACE
      fnTraceSharedMemory( "Unmapping anchor block" );
#endif

      TraceLine( "fnFreeLocalAnchorBlock Page Table UNmapping at Index: %x   0x%08x   Process: 0x%08x",
                 lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );

      UnmapViewOfFile( g_ZeidonPageTable[ lPageTableIndex ] );
      CloseHandle( (HANDLE) g_FileMappingHandles[ lPageTableIndex ] );
      g_ZeidonPageTable[ lPageTableIndex ] = 0;
      g_FileMappingHandles[ lPageTableIndex ] = 0;
   }

   g_hAnchorBlock = 0;
   AnchorBlock    = 0;
   g_lProcessIdx  = -1;
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      FreeAnchorBlock
//
//  PURPOSE:    To release the main anchor block segment for
//              the Object Services. This operation is called
//              by KZOENGWA on ending when all tasks have ended.
//
//  PARAMETERS: NONE
//
//  RETURNS:    0 - Anchor block freed successfully
//             zCALL_ERROR - Anchor block not freed successfully
//
/////////////////////////////////////////////////////////////////////////////
zSHORT  OPERATION
FreeAnchorBlock( LPTASK lpTask )
{
   // free Probe Area
   if ( g_pProbeArea )
      SysFree( g_pProbeArea );

// TraceLineX( "FreeAnchorBlock AnchorBlock ", g_hAnchorBlock );
   // if AnchorBlock not initialized, return zCALL_ERROR.
   if ( AnchorBlock == 0 )
      return( zCALL_ERROR );

   // If the caller is not the main task, return zCALL_ERROR.
   if ( lpTask == 0 ||
        zGETHNDL( lpTask ) != AnchorBlock->hMainTask )
   {
      return( zCALL_ERROR );
   }

   // Delete the main Task.
   if ( lpTask->bOE_TaskShutdown == FALSE )
      DeleteTask( lpTask );  // dks 2006.09.18 error while cleaning up client OE

   // Current process has performed RegisterZeidonApp( ) so ...
   g_bProcessRegistered = FALSE;
// g_lpCurrentTask = 0;

   // Free the shared segment for KZOENGWA
   AnchorBlock->nStatus = AnchorCorrupt;     // mark AnchorBlock as no good
   if ( g_bServerMode )
   {
      SysFree( AnchorBlock );
   }
// else
//    fnFreeSharedMemory( lpTask, g_hAnchorBlock ); // free for KZOENGAA.DLL

   // NULL AnchorBlock handle and pointer
   g_hAnchorBlock = 0;
   AnchorBlock = 0;
   g_lProcessIdx = -1;

   return( 0 );

}   // End of FreeAnchorBlock

#ifdef LOAD_FREE_TRACE

zLONG PrimeTable[ 8 ] = { 1009, 5009, 10009, 20011, 50021, 100003, 200003, 500009 };
zULONG SizeTable[ 8 ] = { 0 };
zPVOID AddressTable[ 8 ] = { 0 };
static zLONG lBomb = 0;

void
fnTraceLibrary( LPLIBRARY lpLibrary, zSHORT nFlag )
{

}

#endif

//./ ADD NAME=ProcessZeidonMessage
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ProcessZeidonMessage
//
//  PURPOSE:    To receive user messages under the appropriate task ids to
//              do memory sharing and freeing and any other system services
//              which require a task switch.  The requesting task sends its
//              task address to the target task with a Request ID for the
//              target task to fullfill.  This operation MUST be called by
//              all clients of object services when they receive the user
//              message they defined at RegisterZeidonApplication time.
//
//              For example, if the register call in the client is:
//
//                RegisterZeidonApplication(
//                               hab,                 // My HAB
//                               (zLONG) hwndFrame,   // Main Window
//                               (zLONG) WM_USER,     // Message for Zeidon
//                               "\\\\Myapp\\" )      // My App Name
//
//              The message loop for the main window should have
//              the following case statement for Zeidon messages:
//
//                case WM_USER:
//                   ProcessZeidonMessage( (WPARAM) wParam, (LPARAM) lParam );
//
//  PARAMETERS: wParam  - Task view
//              lParam  - Process index - address of the requesting task.
//
//  RETURNS:    0 - Message processed successfully
//             zCALL_ERROR - Message not processed successfully
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
ProcessZeidonMessage( zLONG wParam, zLONG lParam )
{
   LPPROCESSLIST lpRequestProcess;
   LPTASK        lpTask = 0;
   zLONG         lProcessIdx = lParam;
   DWORD         dwCurrentProcess = GetCurrentProcessId( );
   zSHORT        nRequest;

//#ifdef DEBUG
   if ( g_bServerMode )
   {
      SysMessageBox( (zVIEW) wParam, szlOE_SystemError,
                     "Received a message while in Server Mode", -1 );
      return( 0 );
   }
//#endif

   if ( AnchorBlock == 0 )
      return( zCALL_ERROR );  // failure ... get out!

   // Get address of requesting process.
   if ( lProcessIdx == -1 )
   {
      nRequest = TASKREQ_FREEALL;
      lpTask = zGETPTR( wParam );
      lpRequestProcess = 0;
   }
   else
   {
      lpRequestProcess = &AnchorBlock->OS_Data.ProcessList[ lProcessIdx ];
      if ( lpRequestProcess == 0 )
      {
         SysMessageBox( (zVIEW) wParam, "Zeidon Object Engine",
                        "Internal Error - lpRequestProcess is null", -1 );
         return( zCALL_ERROR );  // Failure get out
      }

      nRequest = lpRequestProcess->nOE_Request;

#ifdef SHARED_MEM_TRACE
      TraceLine( "ProcessZeidonMessage CurrentProcess: %d   "
                    "ProcessIdx: %d   Request CurrentProcess: %d   %s",
                 dwCurrentProcess, lProcessIdx, lpRequestProcess->lProcessID,
                 lpRequestProcess->nOE_Request == TASKREQ_SHARE ? "TASKREQ_SHARE" :
                 lpRequestProcess->nOE_Request == TASKREQ_ALLOC ? "TASKREQ_ALLOC" : "TASKREQ_FREE" );
#endif
   }

   // The requesting task is valid, process the message.
   switch ( nRequest )
   {
      case TASKREQ_SHARE:  // get here from fnGetAnchorBlock's task
                           // switch to main task
      {
         // Share a single block of the requesting task's memory.

         // We should only get this message for the main task.  Another task
         // has just started and needs to share all file mappings.  Go
         // through the table of file mappings and return some info.
         // lParam contains the last index into the process table with which
         // the calling process has shared memory.

         // OK to lose original ProcessID.
         lpRequestProcess->lProcessID = dwCurrentProcess;
         lpRequestProcess->lPageTableIndex++;
         lpRequestProcess->hMemHandle = 0;  // no more blocks to share

#ifdef SHARED_MEM_TRACE
         TraceLine( "TASKREQ_SHARE Process: 0x%08x   PageTableIndex: %d",
                    lpRequestProcess->lProcessID, lpRequestProcess->lPageTableIndex );
#endif

         while ( lpRequestProcess->lPageTableIndex < zSHR_MAX_PAGES )
         {
            if ( g_ZeidonPageTable[ lpRequestProcess->lPageTableIndex ] )
            {
               // We found a used file mapping.  Copy the handle to parm2 and break loop.
               lpRequestProcess->hMemHandle = g_FileMappingHandles[ lpRequestProcess->lPageTableIndex ];
               break;
            }

            lpRequestProcess->lPageTableIndex++;
         }

         break;
      }

      case TASKREQ_ALLOC:  // get here from fnAllocSharedMemory and fnGetAnchorBlock
      {
         // Allocate shared memory.
         // Some other task wants to allocate shared memory and has already
         // created a file mapping.  Open a view to that file mapping.
         HANDLE hOwnerTask;
         HANDLE hOwnerMem  = (HANDLE) lpRequestProcess->hMemHandle;
         HANDLE hCurrentMem;
         HANDLE hCurrentProcess = GetCurrentProcess( );  // intentionally
         zLONG  lPageTableIndex = lpRequestProcess->lPageTableIndex;

#ifdef SHARED_MEM_TRACE
         TraceLine( "TASKREQ_ALLOC Page Table mapping at Index: %x   0x%08x   Process: (%d) %d",
                    lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], hCurrentProcess, GetCurrentProcessId( ) );
#endif

         // Creates a windows object handle from the current process to the
         // process specified by lpRequestProcess->lProcessID.
         hOwnerTask = OpenProcess( PROCESS_ALL_ACCESS, 0, lpRequestProcess->lProcessID );

         if ( !DuplicateHandle( hOwnerTask, hOwnerMem, hCurrentProcess,
                                &hCurrentMem, 0, TRUE, DUPLICATE_SAME_ACCESS ) )
         {
            zLONG  lRC = (zLONG) GetLastError( );
            zLONG  lRC2;
            zPCHAR lpMsg;
            DWORD  dw;

            if ( !GetHandleInformation( hOwnerTask, &dw ) )
               lRC2 = GetLastError( );

            if ( !GetHandleInformation( hOwnerMem, &dw ) )
               lRC2 = GetLastError( );

            if ( !GetHandleInformation( hCurrentProcess, &dw ) )
               lRC2 = GetLastError( );

            FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL, lRC, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT),
                           (LPTSTR) &lpMsg, 0, NULL );

            TraceLineI( "(sy) DuplicateHandle RC = ", lRC );
            TraceLineS( "(sy) DuplicateHandle Failed: ", lpMsg );
            SysMessageBox( 0, szlOE_SystemError, "Internal error -- DuplicateHandle failed!", -1 );
            CloseHandle( hOwnerTask );
            LocalFree( (LPVOID) lpMsg );
            return( zCALL_ERROR );
         }

         fnMapFile( &hCurrentMem, 0, &lPageTableIndex, 0 );
         CloseHandle( hOwnerTask );
         break;
      }

      case TASKREQ_FREEALL:
      {
         LPTASK lpSearchTask;

         // The task is shutting down ... free requesting task's hold on
         // all memory "owned" by other tasks.

         // If the task is a thread task then we don't need to free memory --
         // it will be handled by the process task.
         if ( lpTask->bThreadTask )
            break;

         // Make sure nobody is currently deleting a task.
         fnStartBrowseOfTaskList( lpTask, FALSE );

         for ( lpSearchTask = zGETPTR( AnchorBlock->hFirstTask );
               lpSearchTask;
               lpSearchTask = zGETPTR( lpSearchTask->hNextTask ) )
         {
            LPDATAHEADER lpDataHeader;

            // Don't bother for the current task.
            if ( lpSearchTask == lpTask )
               continue;

            // Free all memory allocated for the task.
            lpDataHeader = zGETPTR( lpSearchTask->hFirstDataHeader );
            if ( lpDataHeader )
            {
               while ( lpDataHeader->hNextDataHeader )
                  lpDataHeader = zGETPTR( lpDataHeader->hNextDataHeader );

               while ( TRUE )
               {
                  if ( lpDataHeader->lNextDataHandle )
                  {
                     zLONG lPageTableIndex;

                     if ( g_bWin95 )
                        lPageTableIndex = (zLONG) *((zPLONG) lpDataHeader->lNextDataHandle - 1);
                     else
                        lPageTableIndex = (zLONG) ((zULONG) lpDataHeader->lNextDataHandle >> 24);

#ifdef SHARED_MEM_TRACE
                     fnTraceSharedMemory( "TASKREQ_FREEALL: freeing memory owned by other tasks." );
#endif

                  // if ( lPageTableIndex == 134 )
                  // {
                  //    TraceLine( "UnmapViewOfFile1 Page Table at Index: %x   0x%08x   Process: 0x%08x",
                  //               lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );
                  // }

                     UnmapViewOfFile( g_ZeidonPageTable[ lPageTableIndex ] );
                     CloseHandle( (HANDLE) g_FileMappingHandles[ lPageTableIndex ] );
                     g_ZeidonPageTable[ lPageTableIndex ] = 0;
                     g_FileMappingHandles[ lPageTableIndex ] = 0;
                  }

                  lpDataHeader = zGETPTR( lpDataHeader->hPrevDataHeader );
                  if ( lpDataHeader == 0 )
                     break;
               }
            }

            if ( lpSearchTask->hFirstDataHandle )
            {
               zLONG lPageTableIndex;

               if ( g_bWin95 )
                  lPageTableIndex = (zLONG) *((zPLONG) lpSearchTask->hFirstDataHandle - 1);
               else
                  lPageTableIndex = (zLONG) ((zULONG) lpSearchTask->hFirstDataHandle >> 24);

#ifdef SHARED_MEM_TRACE
               fnTraceSharedMemory( "TASKREQ_FREEALL: Freeing last page table." );
#endif

            // if ( lPageTableIndex == 134 )
            // {
            //    TraceLine( "UnmapViewOfFile2 Page Table at Index: %x   0x%08x   Process: 0x%08x",
            //               lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );
            // }

               UnmapViewOfFile( g_ZeidonPageTable[ lPageTableIndex ] );
               CloseHandle( (HANDLE) g_FileMappingHandles[ lPageTableIndex ] );
               g_ZeidonPageTable[ lPageTableIndex ] = 0;
               g_FileMappingHandles[ lPageTableIndex ] = 0;
            }
         }

         fnEndBrowseOfTaskList( FALSE );
         break;

      } // TASKREQ_FREEALL

      case TASKREQ_FREE:
      {
         // Free a particular chunk of memory.

         zLONG lPageTableIndex = lpRequestProcess->lPageTableIndex;

#ifdef SHARED_MEM_TRACE
         fnTraceSharedMemory( "TASKREQ_FREE:  Freeing a current page." );
         TraceLine( "TASKREQ_FREE Page Table UNmapping at Index: %x   0x%08x   Process: %d",
                    lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );
#endif

      // if ( lPageTableIndex == 134 )
      // {
      //    TraceLine( "UnmapViewOfFile3 Page Table at Index: %x   0x%08x   Process: 0x%08x",
      //               lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );
      // }

         UnmapViewOfFile( g_ZeidonPageTable[ lPageTableIndex ] );
         CloseHandle( (HANDLE) g_FileMappingHandles[ lPageTableIndex ] );
         g_ZeidonPageTable[ lPageTableIndex ] = 0;
         g_FileMappingHandles[ lPageTableIndex ] = 0;
         break;
      }

      case TASKREQ_FREELIB:
      {
         LPLIBRARY lpLibrary = zGETPTR( lpRequestProcess->hMemHandle );
      // TraceLineS( "(sy) TASKREQ_FREELIB: freeing library ",
      //             lpLibrary->szName );
      // fnTraceLibrary( lpLibrary, 0 );
         FreeLibrary( (HMODULE) lpLibrary->hLibrary );
         break;
      }

      case TASKREQ_FREEMUTEX:
      {
         LPMUTEX lpMutex = zGETPTR( lpRequestProcess->hMemHandle );
         if ( CloseHandle( (HANDLE) lpMutex->Info.hMutexOS ) == 0 )
         {
            char szMsg[ 100 ];

            sprintf_s( szMsg, zsizeof( szMsg ), "Error destroying mutex: %s", lpMutex->szName );
            TraceLineS( szMsg, "" );
            fnSysMessageBox( lpTask, szlOE_SystemError, szMsg, 1 );
         }

         break;
      }

      default:
      {
         SysMessageBox( (zVIEW) wParam, "Zeidon Object Engine", "Unknown message", -1 );
         return( zCALL_ERROR ); // Failure
      }
   }

   return( 0 );  // ok ... get out

} // end of:  ProcessZeidonMessage

//./ ADD NAME=fnAllocSharedMemory
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:     fnAllocSharedMemory
//
// PURPOSE:  This system dependent operation allocates shared memory for
//           the specified number of bytes.
//
// RETURNS:  The memory handle to Allocated memory as well as the pointer
//           to the memory.
//
//    NOTE: if the allocate of memory fails, the memory pointer passed
//          is nulled and the return value is zero.
//
// OS/2 notes:
//
// Memory allocated by Task A using DosAllocSharedMem is freed when
// Task A terminates (either normally or abnormally) if no other task
// "gets" the shared memory.  A shared memory counter is incremented
// differently for "named" vs. "unnamed" shared memory.  Unnamed shared
// memory counters are incremented on a task basis ... a task may "get"
// unnamed shared memory as many times as it wants with the result being
// that the counter is incremented only once (so the task only has to
// free the memory once even if it "gets" the memory multiple times).
// Named shared memory counters are incremented everytime a task "gets"
// the memory (and therefore must be freed a corresponding number of times).
// Shared memory is not freed until all (sharing) tasks have explicitly
// freed the memory or until all (sharing) tasks have terminated.
//
// It may be that we need another zCOREMEM flag (perhaps zCOREMEM_GLOBAL)
// to indicate that the memory to be allocated is not to be owned by the
// task allocating the memory, rather by OE (we may also then need a way
// to free such memory).
//
// Architecture:
//
// fnAllocSharedMemory allocates shared (based on a parameter) memory handles.
// Each shared memory handle will be "get"ed by each active task and each
// new task will "get" all shared memory.  fnFreeSharedMemory is called to free
// shared memory ... which requests each task in turn to free the memory
// (releasing the memory back to the operating system).
//
// As each task terminates, it will free all shared memory.  There are two
// cases of shared memory that need to be considered ... task owned and
// "other" task owned.  When a task terminates, all task owned shared memory
// is first freed by all other tasks and then freed by the owning task (thus
// freeing this memory back to the operating system).  All shared memory
// owned by tasks other than the terminating task is freed only by the
// terminating task (and thus still available for use by non-terminating
// tasks).
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zLONG LOCALOPER
fnAllocSharedMemory( zCOREMEM ppvMemory,
                     LPTASK   lpTask,
                     zLONG    lBytes,
                     zCPCHAR  cpcShareName )
{
   HANDLE hMemory = 0;
   zLONG  lPageTableIndex = 0;

   *ppvMemory = 0;

   // If more space is requested than is available, return error.
   if ( lBytes <= 0 )
      return( 0 );

   if ( g_bServerMode )
   {
      *ppvMemory = SysMalloc( lBytes );
      return (zLONG) *ppvMemory;
   }

// TraceLine( "fnAllocSharedMemory1   Process: 0x%08x", SysGetProcessID( 0 ) );

   zLOCK_MUTEX( zMUTEX_SHAREDMEM );

   // If the memory is shared, then we must send a message to each
   // registered zeidon application.
   //
   // If AnchorBlock is zero then we haven't finished initialization yet so
   // there are no messages to send.

   if ( AnchorBlock && AnchorBlock->hMainTask )
   {
      LPPROCESSLIST lpProcessList;
      zLONG     k;
      zLONG     lRC;

      // Create a new file mapping.
      *ppvMemory = fnMapFile( &hMemory, lBytes, &lPageTableIndex, 0 );
      if ( hMemory == 0 )
      {
         zUNLOCK_MUTEX( zMUTEX_SHAREDMEM );
         return( 0 );
      }

      fnSetProcessIdx( "AllocShared", &lpProcessList );
      lpProcessList->nOE_Request     = TASKREQ_ALLOC; // tell OE to share Memory
      lpProcessList->lPageTableIndex = lPageTableIndex;
      lpProcessList->hMemHandle      = (zLONG) g_FileMappingHandles[ lPageTableIndex ];

      // Send each task a message to open the same file mapping.
      k = AnchorBlock->OS_Data.lProcessCount;
   // TraceLine( "fnAllocSharedMemory should SendMessage from ProcessIndex: %d  to %d processes", g_lProcessIdx, k );
      while ( k > 0 )
      {
         k--;
         lpProcessList = &AnchorBlock->OS_Data.ProcessList[ k ];
      // TraceLine( "fnAllocSharedMemory SendMessage ALLOC %x Wnd: 0x%08x  Handle: 0x%08x  ProcessIdx: %d  Process: %d",
      //            lPageTableIndex, lpProcessList->hWndAppOE_Msg, lpProcessList->hMemHandle, k, lpProcessList->lProcessID );

         if ( k == g_lProcessIdx )
            continue;  // don't bother sending a message to ourselves

         if ( IsWindow( (HWND) lpProcessList->hWndAppOE_Msg ) == 0 )
            continue;

         lRC = SendMessage( (HWND) lpProcessList->hWndAppOE_Msg,
                            lpProcessList->uAppOE_Msg, 0, g_lProcessIdx );
      // TraceLine( "fnAllocSharedMemory SendMessage ****** %s ****** Wnd: 0x%08x  ProcessIdx: %d",
      //            lRC ? "Failure" : "Success" , lpProcessList->hWndAppOE_Msg, g_lProcessIdx );
         if ( lRC )
         {
            MessageBox( GetActiveWindow( ), "Error Calling SendMsg( )",
                        "Zeidon Internal Error",
                        MB_ICONSTOP | MB_OK | MB_TASKMODAL );
         }
      }
   }
   else
   {
      // Create a new file mapping.
      *ppvMemory = fnMapFile( &hMemory, lBytes, &lPageTableIndex, cpcShareName );
   }

   zUNLOCK_MUTEX( zMUTEX_SHAREDMEM );

#ifdef SHARED_MEM_TRACE
   TraceLine( "fnAllocSharedMemory (Task: 0x%08x) at Index: %x   0x%08x   Process: 0x%08x",
              zGETHNDL( lpTask ), lPageTableIndex,
              g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );
#endif

   return( (zLONG) hMemory );
}

zPVOID
CheckPointer( zVIEW lpView, zLONG lPageTableIndex, zPVOID pHandle )
{
   // Get high order byte from handle.
   zLONG  k = (zLONG) ((zULONG) pHandle >> 24);
   if ( k == lPageTableIndex )
   {
      LPVIEWOD lpViewOD;

      if ( lpView )
         lpViewOD = zGETPTR( lpView->hViewOD );
      else
         lpViewOD = 0;

      TraceLine( "Check Pointer Error for TableIndex: %d   ViewOD Name: %s",
                 lPageTableIndex, lpViewOD ? lpViewOD->szName : "No view" );
      SysMessageBox( 0, "Zeidon Core", "Check Pointer Error for TableIndex!", -1 );
   }

   return( zGETPTR( pHandle ) );
}

//#define CHECK_MEMORY
#ifdef CHECK_MEMORY
void
CheckMemory( zLONG lPageTableIndex )
{
   zVIEW     lpView;
   LPVIEWCSR lpViewCsr;
   LPVIEWOI  lpViewOI;
   LPENTITYINSTANCE lpEntityInstance;
   LPENTITYINSTANCE lpNextEntityInstance;
   LPVIEWENTITY lpViewEntity;
   zPCHAR       lpRecord;
   LPTASK lpTask = CheckPointer( 0, lPageTableIndex, AnchorBlock->hFirstTask );

   while ( lpTask )
   {
      lpView = CheckPointer( 0, lPageTableIndex, lpTask->hFirstView );
      while ( lpView )
      {
         lpEntityInstance = 0;
         lpViewCsr = CheckPointer( lpView, lPageTableIndex, lpView->hViewCsr );
         if ( lpViewCsr )
         {
            lpViewOI = CheckPointer( lpView, lPageTableIndex, lpViewCsr->hViewOI );
            if ( lpViewOI )
            {
               lpEntityInstance = CheckPointer( lpView, lPageTableIndex,
                                                lpViewOI->hRootEntityInstance );
            }
         }

         while ( lpEntityInstance )
         {
            lpNextEntityInstance = CheckPointer( lpView, lPageTableIndex,
                                                 lpEntityInstance->hNextHier );
            lpViewEntity = CheckPointer( lpView, lPageTableIndex,
                                         lpEntityInstance->hViewEntity );

            // In the next line, if there is an error from CheckPointer, we
            // know that if the record is included, we should just drop the
            // pointer to the pesist record since it belongs to the page in
            // the g_ZeidonPageTable that we are freeing.
            lpRecord = CheckPointer( lpView, lPageTableIndex,
                                     lpEntityInstance->hPersistRecord );
            lpRecord = CheckPointer( lpView, lPageTableIndex,
                                     lpEntityInstance->hNonPersistRecord );
            lpEntityInstance = lpNextEntityInstance;
         }

         lpView = CheckPointer( lpView, lPageTableIndex, lpView->hNextView );
      }

      lpTask = CheckPointer( lpView, lPageTableIndex, lpTask->hNextTask );
   }
}
#endif

//./ ADD NAME=fnFreeSharedMemory
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnFreeSharedMemory
//
//  PURPOSE:    To free the shared usage of the specified memory block
//              for all tasks (known to OE).
//
//  PARAMETERS: The handle to the memory ... in some systems this may be
//              the address of the memory itself.
//
//  RETURNS:     0  - Memory freed
//              otw - Memory not freed
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG LOCALOPER
fnFreeSharedMemory( LPTASK lpTask, zLONG hMemory )
{
   LPPROCESSLIST lpProcessList;
   LPPROCESSLIST lpTgtProcess;
   zLONG         lPageTableIndex;
   zLONG         k;

   if ( g_bServerMode )
   {
      SysFree( (zPVOID) hMemory );
      return( 0 );
   }

#ifdef DEBUG_PAGETABLE
   // Make sure that the highest bit is set.
   if ( ((zLONG) hMemory & 0x80000000) == 0 )
   {
      char szMessage[ 256 ];
   // k = 0;
      sprintf_s( szMessage, zsizeof( szMessage ), "Invalid pointer handle for free: hi-bit not set: 0x%08x", hMemory );
      TraceLineS( szMessage, "" );
      SysMessageBox( 0, szlOE_SystemError, szMessage, -1 );
#if 0
      SysReadZeidonIni( -1, "[Debug]", "BombZDr", szMessage, zsizeof( szMessage ) );
      if ( szMessage[ 0 ] == 'Y' )
         k /= k;
#endif
      return( hMemory );
   }
#endif

   if ( g_bWin95 )
      lPageTableIndex = (zLONG) *((zPLONG) hMemory - 1);
   else
      lPageTableIndex = (zLONG) ((zULONG) hMemory >> 24);

// TraceLine( "fnFreeSharedMemory at Index: %x   0x%08x   Process: 0x%08x",
//            lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );

   // Make sure we have a valid task.  If not then we should be freeing the
   // anchor block so do it.
   if ( lpTask == 0 )
   {
#if defined SHARED_MEM_TRACE
      fnTraceSharedMemory( "fnFreeSharedMemory" );
#endif

   // if ( lPageTableIndex == 134 )
   // {
   //    TraceLine( "fnFreeSharedMemory1 Page Table at Index: %x   0x%08x   Process: 0x%08x",
   //               lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );
   // }

      UnmapViewOfFile( g_ZeidonPageTable[ lPageTableIndex ] );
      CloseHandle( (HANDLE) g_FileMappingHandles[ lPageTableIndex ] );
      g_ZeidonPageTable[ lPageTableIndex ] = 0;
      g_FileMappingHandles[ lPageTableIndex ] = 0;
      return( 0 );
   }

   zLOCK_MUTEX( zMUTEX_SHAREDMEM );

#ifdef CHECK_MEMORY // check for memory references that will soon become invalid
   CheckMemory( lPageTableIndex );
#endif

   lpProcessList = &AnchorBlock->OS_Data.ProcessList[ g_lProcessIdx ];
   lpProcessList->nOE_Request     = TASKREQ_FREE;  // tell OE to do free
   lpProcessList->lPageTableIndex = lPageTableIndex;

   // Make sure nobody is currently deleting a task.
   fnStartBrowseOfTaskList( lpTask, FALSE );

   // Use SysSendTaskMsg to send a message to all tasks to free the memory.
   // We do this in reverse order so as not to blow out the anchor block ???
   // before we're finished with it.                                     ???
   k = AnchorBlock->OS_Data.lProcessCount;
// TraceLineI( "fnFreeSharedMemory should SendMessage to process count: ", k );
   while ( k > 0 )
   {
      k--;
      lpTgtProcess = &AnchorBlock->OS_Data.ProcessList[ k ];

      if ( lpTgtProcess->hWndAppOE_Msg && IsWindow( (HWND) lpTgtProcess->hWndAppOE_Msg ) )
      {
         SendMessage( (HWND) lpTgtProcess->hWndAppOE_Msg, lpTgtProcess->uAppOE_Msg, 0, g_lProcessIdx );
      }
   // SysSendTaskMsg( lpCurrentTask, lpTask );
   }

   if ( hMemory != g_hAnchorBlock )
   {
   // if ( lPageTableIndex == 134 )
   // {
   //    TraceLine( "fnFreeSharedMemory2 Page Table at Index: %x   0x%08x   Process: 0x%08x",
   //               lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );
   // }

      UnmapViewOfFile( g_ZeidonPageTable[ lPageTableIndex ] );
      CloseHandle( (HANDLE) g_FileMappingHandles[ lPageTableIndex ] );
      g_ZeidonPageTable[ lPageTableIndex ] = 0;
      g_FileMappingHandles[ lPageTableIndex ] = 0;

   // TraceLine( "fnFreeSharedMemory2 at Index: %x   0x%08x   Process: 0x%08x",
   //            lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );
   }

   fnEndBrowseOfTaskList( FALSE );

   zUNLOCK_MUTEX( zMUTEX_SHAREDMEM );

   return( 0 );

} // end of:  fnFreeSharedMemory.

//./ ADD NAME=SysMalloc
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:     SysMalloc
//
// PROTOTYPE: zPVOID OPERATION
//            SysMalloc( zLONG  lSize );
//
// PURPOSE:   Returns memory with the standard C runtime function malloc and
//            initialize it with zero.
//            This function replaces the old Win16 designed function SysAllocMemory
//
// RETURNS:   The pointer to the allocated memory or zero if the memory could
//            not be allocated.
//
/////////////////////////////////////////////////////////////////////////////
//./ END
zPVOID OPERATION
SysMalloc( zLONG lSize )
{
   zPVOID pvMemory;

#ifdef DEBUG_MALLOC
   zLONG  k;

   if ( lSize <= -2 )
   {
      TraceLine( "SysMalloc Initializing Memory Usage ===============================> Size: %d", lSize );
      g_lHighWaterMark = -1;
   }

   if ( g_lHighWaterMark == -1 )
   {
      for ( k = 0; k < zMAX_ALLOC_TEST; k++ )
         g_pvAlloc[ k ] = 0;
   }

   if ( lSize <= 0 )
   {
      TraceLine( "SysMalloc Reporting Memory Usage ===============================> High Water Mark: %d", g_lHighWaterMark );
      for ( k = 0; k < g_lHighWaterMark; k += 2 )
      {
         if ( g_pvAlloc[ k ] )
         {
            TraceLine( "== %06d ============> Mem: 0x%08x  Size: %d",
                       k, g_pvAlloc[ k ], g_pvAlloc[ k + 1 ] );
         }
      }

   // g_lHighWaterMark = -1;
      return( 0 );
   }

   for ( k = 0; k < zMAX_ALLOC_TEST; k += 2 )
   {
      if ( g_pvAlloc[ k ] == 0 )
         break;
   }

#endif

   pvMemory = calloc( lSize, 1 );  // allocate the memory!!!

#ifdef DEBUG_MALLOC

   if ( lSize == 262000 )
      TraceLine( "SysMalloc Size: %d   Mem: 0x%08x", lSize, pvMemory );

   if ( k == 18 || k == 12 || k == 14 || k == 16 )
      TraceLine( "SysMalloc (%d) Size: %d   Mem: 0x%08x", k, lSize, pvMemory );

   if ( k >= zMAX_ALLOC_TEST )
      MessageBox( 0, "SysMalloc Error", "Memory Test Error", MB_OK );
   else
   {
      if ( g_lHighWaterMark < k )
         g_lHighWaterMark = k;

      g_pvAlloc[ k ] = pvMemory;
      g_pvAlloc[ k + 1 ] = (HANDLE) lSize;
   }

#endif

   return( pvMemory );
}

//./ ADD NAME=SysFree
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:     SysFree
//
// PROTOTYPE:
//
//      zVOID OPERATION
//      SysFree( zPVOID pMemory );
// PURPOSE:
//      free the memory allocated with SysAlloc( )
//      This function replace the old win16 designed function SysFreeMemory
//
// RETURNS:
//
/////////////////////////////////////////////////////////////////////////////
//./ END
zVOID OPERATION
SysFree( zPVOID pvMemory )
{
#ifdef DEBUG_MALLOC
   zLONG  k;

// TraceLine( "SysFree Mem: 0x%08x", pvMemory );
#endif

   if ( pvMemory )
   {

#ifdef DEBUG_MALLOC
      for ( k = 0; k < zMAX_ALLOC_TEST; k += 2 )
      {
         if ( g_pvAlloc[ k ] == pvMemory )
         {
            g_pvAlloc[ k ] = 0;
            g_pvAlloc[ k + 1 ] = 0;
            break;
         }
      }

      if ( k >= zMAX_ALLOC_TEST )
      {
         TraceLine( "SysFree Error ... Memory Not Found: 0x%08x", pvMemory );
      // MessageBox( 0, "SysFree Error", "Memory Not Found", MB_OK );
      }
#endif

      free( pvMemory );
   }
}

//./ ADD NAME=SysMemSize
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:     SysMemSize
//
// PROTOTYPE:
//
//      zVOID OPERATION
//      SysMemSize( zPVOID pMemory );
// PURPOSE:
//      free the memory allocated with SysAlloc( )
//      This function replace the old win16 designed function SysFreeMemory
//
// RETURNS:
//
/////////////////////////////////////////////////////////////////////////////
//./ END
zULONG OPERATION
SysMemSize( zPVOID pMemory )
{
   return( (zULONG) _msize( pMemory ) );
}

//./ ADD NAME=SysAllocMemory
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:     SysAllocMemory
//
// PROTOTYPE:
//
//      long OPERATION
//      SysAllocMemory( zCOREMEM Memory, long Bytes,
//                      zLONG hMemory, unsigned int uMemFlags,
//                      zCPCHAR szShareName )
//
// !!! IMPORTANT !!! This function is obsolete, use SysMalloc( ) instead!
//
// PURPOSE:  This system dependent operation allocates memory.  A pointer
//           to a pointer to memory is passed along with the number of
//           bytes requested, the current handle to the memory (if any),
//           and the uMemFlags identifying what to do.
//
//           The flag values are:
//
//           zCOREMEM_ALLOC      0x8000
//           zCOREMEM_SHARED     0x0080
//
// RETURNS:
//
//      The memory handle to Allocated memory as well as the pointer to
//      the memory.  The share name is for an optional named share segment
//      in OS/2.  Note that the memory handle is just that ... a handle.
//      The pointer to the memory usable by the application is returned
//      in the Memory parameter.
//
//      NOTE: If the allocate of memory fails, the memory pointer passed
//            is nulled and the handle returned is zero.
//
//            When an application requests lBytes of memory, additional
//            memory is allocated to handle the request so that the OE
//            can track the application's memory usage (and inform the
//            application if memory is overwritten or not freed).  For
//            each application memory allocation request, 4 guard-byte
//            pointers, a length (zLONG), and a pointer to next are allocated
//            in addition to the application requested memory (which is
//            rounded up to the nearest 8-byte boundary).
//
//            So the memory layout for an application requested memory
//            allocation is as follows:
//
//        |||||||| |||||||| |||||||| ............ |||||||| |||||||| ||||||||
//         guard    length   guard    app memory   guard     next    guard
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zLONG OPERATION
SysAllocMemory( zCOREMEM ppvMemory, zLONG lBytes,
                zLONG hMemory, unsigned int uMemFlags,
                zCPCHAR cpcShareName )
{
   *ppvMemory = SysMalloc( lBytes );
   hMemory = (zLONG) *ppvMemory;

   // If an error occurred, tell operator about it, NOTE we do not call
   // fnIssueCoreError because out of memory is a very delicate situation
   // to be in!!.
   if ( hMemory == 0 )
   {
      char szMsg[ 60 ];

      // offset ...... 1234567890123456789212345678931234567894123456
      strcpy_s( szMsg, zsizeof( szMsg ), "KZOE0012 - Error allocating memory for length " );
      zltoa( lBytes, szMsg + 46, zsizeof( szMsg ) - 46 );
      SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
   }

   // Return the handle to the memory allocated.
   return( hMemory );
}

//./ ADD NAME=SysFreeMemory
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysFreeMemory
//
// !!! IMPORTANT !!! This function is obsolete, use SysMalloc( ) and SysFree( )
//                   instead!
//
//  PURPOSE:    To free the current task's use of a memory block,
//              if the current task is the last task using it and
//              the last count for the task using it, the memory
//              is returned to the system.
//
//  PARAMETERS: The handle to the memory ... in some systems this may be
//              the address of the memory itself.
//
//  RETURNS:      0   - Memory freed
//              non-zero - Memory not freed
//
//            So the memory layout for an application requested memory
//            allocation is as follows:
//
//        |||||||| |||||||| |||||||| ............ |||||||| |||||||| ||||||||
//         guard    length   guard    app memory   guard     next    guard
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG OPERATION
SysFreeMemory( zLONG hMemory )
{
   if ( hMemory == 0 )
      return( zCALL_ERROR );

   SysFree( (zPVOID) hMemory );
   return( 0 );
}

//./ ADD NAME=SysAddressMemory
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysAddressMemory
//
//  PURPOSE:    To give the current task access to a memory block.
//
//  PARAMETERS: hMemory - the handle to the memory block
//
//  RETURNS:      0   - Access allowed
//              non-zero - Access not allowed
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int OPERATION
SysAddressMemory( zLONG hMemory )
{
   if ( hMemory == g_hAnchorBlock )  // we share the anchor block by name
   {
//    TraceLineX( "SysAddressMemory hAnchorBlock ", (zLONG) hMemory );
      return( 0 );
   }

   // Do nothing for addressing since GlobalLock does not seem to
   // increment the memory lock count and all memory is shareable in
   // windows. Therefore, we never attempt to increase the lock count
   // and also never free memory unless the main task requests the free
   // (see SysFreeMemory).
   return( 0 );
}

//./ ADD NAME=SysValidAddress
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysValidAddress
//
//  PURPOSE:    To validate an address for either read or write access
//
//  PARAMETERS: lpAddress - the Address to be validated
//              lLth      - the length to validate for
//              bWrite    - is for write access
//
//  RETURNS:    non-zero - Access allowed
//                0   - Access not allowed
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
int OPERATION
SysValidAddress( zPVOID lpAddress,
                 zLONG  lLth,
                 zBOOL  bWrite )
{
   if ( bWrite )
      return( !(IsBadWritePtr( lpAddress, (zUSHORT) lLth )) );
   else
      return( !(IsBadReadPtr( lpAddress, (zUSHORT) lLth )) );
}

//./ ADD NAME=SysCheckTaskMemory
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysCheckTaskMemory
//
//  PURPOSE:    To check the current task's memory usage.
//
//  PARAMETERS: None
//
//  RETURNS:    amount of memory currently allocated by the application
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG OPERATION
SysCheckTaskMemory( void )
{
   return( 0 );
}

// If the anchor block was created by another task then it should have been
// named.  Try to retrieve the anchor block by name.
//
// If we can get the anchor block then we need to share all the memory created
// by other tasks so that the current task has access to them.
zSHORT LOCALOPER
fnGetAnchorBlock( zLONG lAppOE_Msg,
                  zLONG hWndAppOE )
{
   LPPROCESSLIST lpProcessList;
   zLONG  lPageTableIndex;
   zLONG  hSaveAnchorBlock;
   zBOOL  bValidWindow;

   // In server mode, the anchor block has been allocated using local memory
   // so we don't need to do anything.
   if ( g_bServerMode || AnchorBlock )
      return( 0 );

   if ( g_bWin95 )
      lPageTableIndex = 1;
   else
#ifdef DEBUG_PAGETABLE
      // When we are debugging we start with page 128 so that the high bit in
      // the resulting handle will always be set.
      lPageTableIndex = 128;
#else
      // We start with page one (instead of zero) so that a handle will always
      // be non-zero.
      lPageTableIndex = 1;
#endif

   // Here is where the current task gets addressability to the AnchorBlock
   // by opening a view to the (named) shared memory mapping file.
   g_hAnchorBlock = (zLONG) OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, szlShareSeg );
   if ( g_hAnchorBlock == 0 )
      return( 0 );

   // We found the anchor block!  Now map it.
#ifdef SHARED_MEM_TRACE
   fnTraceSharedMemory( "Mapping view of anchor block" );
#endif
   AnchorBlock = MapViewOfFile( (HANDLE) g_hAnchorBlock, FILE_MAP_ALL_ACCESS, 0, 0, 0 );
   if ( AnchorBlock == 0 )
      return( -1 );

   // We successfully gained addressability to the AnchorBlock!

   // Lock the anchor init mutex.  Once we get it we know that the anchor
   // has finished initializing so we can unlock it and go on our merry way.
   zLOCK_MUTEX( zMUTEX_ANCHORINIT );
   zUNLOCK_MUTEX( zMUTEX_ANCHORINIT );

   // We now have the anchor block but we still need to set the global
   // paging table values.  Note that the page table index had better
   // be the first one.
   g_ZeidonPageTable[ lPageTableIndex ] = AnchorBlock;
   g_FileMappingHandles[ lPageTableIndex ] = (zLONG) g_hAnchorBlock;

   TraceLine( "fnGetAnchorBlock Page Table mapping at Index: %x   0x%08x   Process: 0x%08x",
              lPageTableIndex, g_ZeidonPageTable[ lPageTableIndex ], SysGetProcessID( 0 ) );

//#ifdef DEBUG
   if ( g_lProcessIdx != -1 )
   {
      SysMessageBox( 0, "DGC", "g_lProcessIdx != -1", -1 );
      return( 0 );
   }
//#endif

   // Point to the correct structure in the AnchorBlock's ProcessList and set
   // g_lProcessIdx and the CurrentProcessId data element at the same time.
   fnSetProcessIdx( "GetAnchor", &lpProcessList );
   lpProcessList->uAppOE_Msg = (zUSHORT) lAppOE_Msg;
   lpProcessList->hWndAppOE_Msg = hWndAppOE;

   if ( g_bWin95 )
   {
      // To mirror what happens in fnAllocSharedMemory we have to store the
      // index of g_hAnchorBlock in the first few bytes of the memory.
      *((zPLONG) AnchorBlock)++ = lPageTableIndex;
      hSaveAnchorBlock = (zLONG) AnchorBlock;
   }
   else
      hSaveAnchorBlock = (zLONG) ((zULONG) lPageTableIndex << 24);

   // For the moment we'll change g_hAnchorBlock to be zero.  This will keep
   // some things (for example TraceLineX) from doing something it shouldn't.
   g_hAnchorBlock = 0;

// TraceLineI( "Register AnchorBlock = ", (zLONG) AnchorBlock );

   // We now have to open views to all shared mapping files created by other
   // tasks.  To do this we will send a message to the main task and ask for
   // the handle of each shared mapping file.  When the returned handle is
   // zero, then there are no more mapping files.

   // Init to first PageTable entry ... used in inter-process communication
   // to permit each shared mapping handle to be processed.
   lpProcessList->lPageTableIndex = lPageTableIndex;

   if ( IsWindow( (HWND) AnchorBlock->OS_Data.hMainWindow ) )
      bValidWindow = TRUE;
   else
      bValidWindow = FALSE;

   while ( bValidWindow )
   {
      lpProcessList->nOE_Request = TASKREQ_SHARE;  // we want to share handles

#ifdef __MUTEX_DEBUG__
      // We use 'zMUTEX_COUNT' as an ID for SendMessage.
      fnPrintMutexInfo( 's', zMUTEX_COUNT, __FILE__, __LINE__ );
#endif

      SendMessage( (HWND) AnchorBlock->OS_Data.hMainWindow,
                   g_wOENG_Message, 0, g_lProcessIdx );

#ifdef __MUTEX_DEBUG__
      // We use 'zMUTEX_COUNT' as an ID for SendMessage.
      fnPrintMutexInfo( 'S', zMUTEX_COUNT, __FILE__, __LINE__ );
#endif

      // Check the returned handle.  If it's zero, then there are no more file mappings.
      if ( lpProcessList->hMemHandle == 0 )
         break;

      // Now call ProcessZeidonMessage to take the handle returned from the
      // system task and open it for the current task.
      lpProcessList->nOE_Request = TASKREQ_ALLOC; // we want to open a file mapping
      ProcessZeidonMessage( 0, g_lProcessIdx );
   }

   // Last thing is to change g_hAnchorBlock from zero to a Zeidon handle.
   g_hAnchorBlock = hSaveAnchorBlock;
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetAnchorBlock
//
//  PURPOSE:    To return the anchor block address
//
//  PARAMETERS: NONE
//
//  RETURNS:    LPANCHOR
//
/////////////////////////////////////////////////////////////////////////////
LPANCHOR  OPERATION
SysGetAnchorBlock( void )
{
   return( AnchorBlock );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetAnchorBlockData
//
//  PURPOSE:    To return the anchor block address
//
//  PARAMETERS: lFlag - 1 ==> get hSystemApp
//                      2 ==>     hMainTask
//                      3 ==>     lOE_hMainWnd
//                      4 ==>     lOE_hListWnd
//
//  RETURNS:    LPANCHOR
//
/////////////////////////////////////////////////////////////////////////////
zPVOID  OPERATION
SysGetAnchorBlockData( zLONG lFlag )
{
   if ( AnchorBlock )
   {
      switch ( lFlag & 0x0FFFFFFF )
      {
         case 1:
            if ( lFlag & 0x80000000 )
               return( zGETPTR( AnchorBlock->hSystemApp ) );
            else
               return( AnchorBlock->hSystemApp );

         case 2:
            if ( lFlag & 0x80000000 )
               return( zGETPTR( AnchorBlock->hMainTask ) );
            else
               return( AnchorBlock->hMainTask );

         case 3:
            return( (zPVOID) AnchorBlock->lOE_hMainWnd );

         case 4:
            return( (zPVOID) AnchorBlock->lOE_hListWnd );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysStartObjectServices
//
//  PURPOSE:    To check that object services is started and is
//              initialized OK as part of RegisterZeidonApplication.
//              If object services is not started, attempt to start
//              it and make sure it came up AOK!.
//
//  PARAMETERS: NONE
//
//  RETURNS:    0 - Services up and running
//             -1 - Error in services, get out gracefully
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
SysStartObjectServices( zLONG lAppOE_Msg,
                        zLONG hWndAppOE )
{
   char szProgramName[ zMAX_FILESPEC_LTH + 1 ];  // prevent overflow in
   char szTemp[ zMAX_FILESPEC_LTH + 1 ];         // fnConvertEnvironnentString
   zPCHAR pchOS_Name;

   // Validate that environment variable ZEIDON set
   SysGetEnvVar( szProgramName, szlZEIDON, zsizeof( szProgramName ) - 1 );
   if ( szProgramName[ 0 ] == 0 )
   {
      char szMessage[ 256 ];

      // {2,"KZOEE002 - ZEIDON environment variable not set"},
      SysGetBaseMessage( szMessage, KZOEE002, 255 );
      SysMessageBox( 0, szlOE_SystemError, szMessage, -1 );
      return( -1 );
   }

   // Let's see if the anchor block is already initialized.  If it is then
   // some other process has created shared memory and named it.  Look for it.
   if ( g_hAnchorBlock == 0 && fnGetAnchorBlock( lAppOE_Msg, hWndAppOE ) == -1 )
      return( -1 );

   // Build qualified program name.
   // The ZEIDON environment variable must point to a directory
   // containing the ZEIDON.APP file.  From there we retrieve the
   // name of the Zeidon executable directory.
   if ( AnchorBlock == 0 && g_bServerMode == FALSE )
   {
      zLONG               hFile;
      zCHAR               szLine[ 1000 ];
      zPCHAR              pchPtr;
      int                 k;
      HANDLE              hServicesStarted;
      STARTUPINFO         Startup;
      PROCESS_INFORMATION PInfo;

      // See if we can open the zeidon applications file.
      SysAppendcDirSep( szProgramName );
      strcat_s( szProgramName, zsizeof( szProgramName ), szlAppFile );

      hFile = (zLONG) CreateFile( szProgramName, GENERIC_READ, FILE_SHARE_READ, 0,
                                  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );

      if ( hFile == -1 )
      {
         char szMessage[ 256 ];

         // {9,"KZOEE009 - Error opening application definition file"},
         SysGetBaseMessage( szMessage, KZOEE009, 255 );
         strcat_s( szMessage, zsizeof( szMessage ), " '" );
         strcat_s( szMessage, zsizeof( szMessage ), szProgramName );
         strcat_s( szMessage, zsizeof( szMessage ), "'" );
      // SysMessageBox( 0, szlOE_SystemError, szMessage, -1 );  causes bomb if called
         fnSysMessageBox( 0, szlOE_SystemError, szMessage, -1 );

         return( -1 );
      }

      // Read the first 1000 bytes of the file.  We are going to assume that
      // the specification of the zeidon bin dir is in that first 1000 chars.
      {
         ULONG ulBytes;

         ReadFile( (HANDLE) hFile, szLine, zsizeof( szLine ), &ulBytes, 0 );
         CloseHandle( (HANDLE) hFile );
      }

      szLine[ zsizeof( szLine ) - 1 ] = 0;   // ensure buffer is terminated
      pchPtr = zstrstr( szLine, szlZEIDON_BIN );
      if ( !pchPtr )
      {
         fnSysMessageBox( 0, szlOE_SystemError, "Couldn't find ZEIDON_BIN specification.", -1 );
         return( -1 );
      }

      // We found the zeidon bin specification.  Now bump up pchPtr to point
      // to the first non-blank char after zeidon bin.
      pchPtr += strlen( szlZEIDON_BIN );
      while ( *pchPtr == ' ' )
         pchPtr++;

      // Copy directory to szProgramName up to the line terminator.
      k = 0;
      while ( *pchPtr >= ' ' )
         szTemp[ k++ ] = *pchPtr++;

      szTemp[ k ] = 0;

      // Convert name using environment vars.
      fnConvertEnvironmentString( szProgramName, zsizeof( szProgramName ), szTemp );

      // Create a Win32 event so we'll know when OE is up.
      hServicesStarted = CreateEvent( NULL, TRUE, FALSE, "Zeidon - Object Services Init" );

      // Start Object Services program asynchronously
      SysAppendcDirSep( szProgramName );
      strcat_s( szProgramName, zsizeof( szProgramName ), szObjectEngineName );

      zmemset( &PInfo, 0, sizeof( PInfo ) );
      zmemset( &Startup, 0, sizeof( Startup ) );
      Startup.cb          = sizeof( Startup );
      Startup.dwFlags     = STARTF_USESHOWWINDOW;
      Startup.wShowWindow = SW_MINIMIZE;
      if ( CreateProcess( szProgramName, 0, 0, 0, 0, 0, 0, 0, &Startup, &PInfo ) == 0 )
      {
         char  szMessage[ 256 ];
         DWORD l = GetLastError( );

         // {3,"KZOEE003 - Error starting Object Services"},
         SysGetBaseMessage( szMessage, KZOEE003, 255 );
         strcat_s( szMessage, zsizeof( szMessage ), " - " );
         strcat_s( szMessage, zsizeof( szMessage ), szProgramName );
         fnSysMessageBox( 0, szlOE_SystemError, szMessage, -1 );
         return( -1 );
      }

      // Wait for the services to start.
      WaitForSingleObject( hServicesStarted, INFINITE );
      CloseHandle( hServicesStarted );
      if ( fnGetAnchorBlock( lAppOE_Msg, hWndAppOE ) == -1 )
         return( -1 );
   }
   else
   if ( AnchorBlock == 0 && g_bServerMode )
   {
      AnchorBlock = InitializeAnchorBlock( (zLONG) g_hInstance, 0, 0, 0 );
   }
   else
   {
      // If AnchorBlock is corrupt, free it and issue a bad RC
      if ( AnchorBlock->nStatus  == AnchorCorrupt ||
           AnchorBlock->nTableID != iAnchor ||
           !IsWindow( (HWND) AnchorBlock->lOE_hMainWnd ) )
      {
         char szMessage[ 256 ];

         // {7,"KZOEE007 - Internal Anchor block error, system restart recommended"},
         SysGetBaseMessage( szMessage, KZOEE007, 255 );
         fnSysMessageBox( 0, szlOE_SystemError, szMessage, -1 );

         fnFreeSharedMemory( 0, g_hAnchorBlock );
         g_hAnchorBlock = 0;
         AnchorBlock  = 0;
         g_lProcessIdx = -1;
         return( -1 );
      }
   }

   switch ( SysGetOS_Info( 0 ) )
   {
      case zOS_WINDOWS:
         pchOS_Name = "MS Windows 3.x";
         break;

      case zOS_WINDOWS95:
         pchOS_Name = "MS Windows 95/98";
         break;

      case zOS_WINDOWSNT:
         pchOS_Name = "MS Windows NT/XP";
         break;

      case zOS_OS2:
         pchOS_Name = "IBM OS/2";
         break;
   }

   // If we get here, we must have been successful.
   TraceLineS( "(sy) SysStartObjectServices started for ", pchOS_Name );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// The page tables are used by Zeidon to share memory across processes.
// When Tomcat registers the first Zeidon app we start up the OE.  The OE
// runs as a separate process so whenever a Zeidon task running under Tomcat
// needs more memory it allocates it and then sends a message to the OE and
// tells it how to get access to it.  Once the OE does its thing (by calling
// fnMapFile) then both processes can use it.
//
// All the Zeidon tasks running under Tomcat automatically have access to
// this memory because the memory is shared for the entire process.  The
// Zeidon tasks run under separate threads so nothing really needs to be
// done for them.
//
// As long as that block of memory is enough to hold all the data needed by
// the Zeidon apps running under Tomcat we're good.  But if more memory is
// needed another block will be allocated, along with another message sent
// to the OE.  When a new task is created it is given its own block of
// memory.  Even though all the other tasks running under Tomcat can access
// it, a message still needs to be sent to the OE.
//
// When a block of memory is no longer needed it will be freed.  Just like
// allocation, the freeing needs to be coordinated between the two processes.
// Since every task is given its own block to play with, when a task goes
// away the block is freed.
//
// Here's where some of the confusion may be: every process that runs
// Zeidon (i.e. every process that calls RegisterZeidonApp) needs to
// keep a list of all the blocks of memory.  To do this it keeps two
// tables: one is a list of handles, the other a list of pointers.  It
// doesn't matter how many threads or Zeidon tasks there are, the process
// needs to keep only one table.  What's more, these tables must be kept in
// sync with all the other processes that are running Zeidon.  Whenever a
// new block is added to the tables a message must be sent to all the other
// processes to keep their tables in sync.
//
// Let's do an example:  Assume we have two processes, Tomcat (process T)
// and the OE (process O).  Each process will have two tables, a handle
// table (tables HT and HO) of memory blocks, and pointer tables (PT and
// PO).  Here's the order as I remember:
//
// 1) Tomcat starts.  Tables HT, PT are empty.
// 2) Tomcat calls RegisterZeidonApp. Core allocates a block of shared memory
// and the handle to this memory is stored in the first cell of HT.  The
// address of the memory is stored in PT. I'll just make up handle values
// and prefix them with 'h', addresses with 'x':
//   HT      PT    HO       PO
// +---+   +---+  +---+   +---+
// | h4|   |x0f|  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
//
// 3) A message now needs to be sent to all other Zeidon processes.  Tomcat
// sends a message to the OE telling it what the handle is and the index of
// the handle.  The OE takes the handle and stores it in HO and then "opens"
// a mapping to the shared memory.  Note that the address of the shared
// memory is different for the OE than for tomcat:
//
//   HT      PT    HO       PO
// +---+   +---+  +---+   +---+
// | h4|   |x0f|  | h4|   |xd3|
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
//
// Now both processes have access to the memory.  If the OE allocates memory
// then the process is reversed.  The OE first allocates shared memory and
// stores the values in its tables:
//
//   HT      PT    HO       PO
// +---+   +---+  +---+   +---+
// | h4|   |x0f|  | h4|   |xd3|
// +---+   +---+  +---+   +---+
// |   |   |   |  | h1|   |xfe|
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
//
// And then sends a message to Tomcat.  The result looks like:
//
//   HT      PT    HO       PO
// +---+   +---+  +---+   +---+
// | h4|   |x0f|  | h4|   |xd3|
// +---+   +---+  +---+   +---+
// | h1|   |x14|  | h1|   |xfe|
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
// |   |   |   |  |   |   |   |
// +---+   +---+  +---+   +---+
//
// When memory is freed, the tables need to be erased.
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifdef SHARED_MEM_TRACE
void LOCALOPER
fnTraceSharedMemory( zCPCHAR cpcTitle )
{
#if 0  // not good under Tomcat
   zCHAR szMsg[ 1000 ];
   zLONG lProcessID = SysGetProcessID( 0 );

   OutputDebugString( "\n============ Map/Unmap =============\n" );
   sprintf_s( szMsg, zsizeof( szMsg ), "%s     ProcessID: %d\n", cpcTitle, lProcessID );
   OutputDebugString( szMsg );
   zDumpStack( );
   OutputDebugString( "=============== End ================\n" );
#else
// TraceLine( "fnTraceSharedMemory %s   Process: %d", cpcTitle, SysGetProcessID( 0 ) );
#endif
}
#endif

zPVOID LOCALOPER
fnSysGetPointerFromHandleServerMode( zPVOID pHandle )
{
   return( pHandle );
}

zPVOID LOCALOPER
fnSysGetPointerFromHandleShared( zPVOID pHandle )
{
   zBYTE  k;
   zLONG  lOffset;

   if ( pHandle == 0 )
      return( 0 );

   // Following is for Instance handles.  Instance handles can be:
   // zero (no instance), one (unset cursor), or a valid handle.
   if ( pHandle == (zPVOID) 1 )
      return( (zPVOID) 1 );

#ifdef DEBUG_PAGETABLE
   // Make sure that the highest bit is set.
   if ( ((zLONG) pHandle & 0x80000000) == 0 )
   {
      char szMessage[ 256 ];

      sprintf_s( szMessage, zsizeof( szMessage ), "Invalid pointer handle (get) : hi-bit not set: 0x%08x", (zULONG) pHandle );
      TraceLineS( szMessage, "" );
      if ( AnchorBlock->bDebugLeak == FALSE )
      {
         MessageBox( GetActiveWindow( ), szMessage,
                     szlOE_SystemError, MB_ICONSTOP | MB_OK | MB_TASKMODAL );
      }
#if 0
      SysReadZeidonIni( -1, "[Debug]", "BombZDr", szMessage, zsizeof( szMessage ) );
      if ( szMessage[ 0 ] == 'Y' )
      {
         k = 0;
         k /= k;
      }
#endif
      return( 0 );
   }
#endif

   // Get high order byte from handle.
   k = (zBYTE) ((zULONG) pHandle >> 24);

   if ( g_ZeidonPageTable[ k ] == 0 )
   {
      char szMessage[ 256 ];  // dks 2006.09.18 error while cleaning up client OE (k=134)

      sprintf_s( szMessage, zsizeof( szMessage ), "Invalid pointer handle (null) at Index: %x for pointer 0x%08x", k, (zULONG) pHandle );
      TraceLineS( szMessage, "" );
      if ( AnchorBlock->bDebugLeak == FALSE )
      {
         MessageBox( GetActiveWindow( ), szMessage, szlOE_SystemError, MB_ICONSTOP | MB_OK | MB_TASKMODAL );
      }
#if 0
      SysReadZeidonIni( -1, "[Debug]", "BombZDr", szMessage, zsizeof( szMessage ) );
      if ( szMessage[ 0 ] == 'Y' )
      {
         k /= k - k;
      }
#endif
      return( 0 );
   }

   // Get page offset from 3 low-order bytes.
   lOffset = (zLONG) pHandle & 0x00FFFFFF;

   // Get pointer value by adding offset to page table address.
   pHandle = (zPVOID) ((zLONG) g_ZeidonPageTable[ k ] + lOffset);
   return( pHandle );
}

zPVOID OPERATION
SysGetPointerFromHandle( zPVOID pHandle )
{
   return( (*g_pfnGetPtr)( pHandle ) );
}

zPVOID LOCALOPER
fnSysGetHandleFromPointerServerMode( zPVOID pPointer )
{
   return( pPointer );
}

zPVOID LOCALOPER
fnSysGetHandleFromPointerShared( zPVOID pPointer )
{
   LPFREESPACE lpFreespace;

   if ( pPointer == 0 )
      return( 0 );

#ifdef DEBUG_PAGETABLE
   // Make sure that the highest bit is NOT set (this means it's a handle).
   if ( ((zLONG) pPointer & 0x80000000) != 0 )
   {
   // char szMessage[ 16 ];
   // int k = 0;
      MessageBox( GetActiveWindow( ), "Invalid pointer: hi-bit set!!",
                  szlOE_SystemError, MB_ICONSTOP | MB_OK | MB_TASKMODAL );
#if 0
      SysReadZeidonIni( -1, "[Debug]", "BombZDr", szMessage, zsizeof( szMessage ) );
      if ( szMessage[ 0 ] == 'Y' )
         k /= k;
#endif
      return( 0 );
   }
#endif

   lpFreespace = (LPFREESPACE) pPointer;
   lpFreespace--;

   return( lpFreespace->hFreespace );
}

zPVOID OPERATION
SysGetHandleFromPointer( zPVOID pPointer )
{
   return( (*g_pfnGetHndl)( pPointer ) );
}

zPVOID LOCALOPER
fnSysCreateHandle( LPDATAHEADER lpDataHeader,
                   zPVOID       pPointer )
{
   zPBYTE pbBase;
   zLONG  lOffset;

   // For Win95 apps we just return the pointer back.
   if ( g_bWin95 )
      return( pPointer );

#ifdef DEBUG_PAGETABLE
   // Make sure that the highest bit is NOT set (this means it's a handle).
   if ( ((zLONG) pPointer & 0x80000000) != 0 )
   {
   // char szMessage[ 16 ];
   // int k = 0;
      MessageBox( GetActiveWindow( ), "Invalid pointer: hi-bit not set!!",
                  szlOE_SystemError, MB_ICONSTOP | MB_OK | MB_TASKMODAL );
#if 0
      SysReadZeidonIni( -1, "[Debug]", "BombZDr", szMessage, zsizeof( szMessage ) );
      if ( szMessage[ 0 ] == 'Y' )
         k /= k;
#endif
      return( 0 );
   }
#endif

   // Get base address of dataspace.
   pbBase = zGETPTR( (zPVOID) lpDataHeader->hDataHandle );

   // Compute the offset of the pointer from the base address.
   lOffset = (zLONG) pPointer - (zLONG) pbBase;

   // New handle consists of the handle of the dataspace (first byte of lHandle)
   // and the offset in the last three bytes.
   pPointer = (zPVOID) (lpDataHeader->hDataHandle | lOffset);
   return( pPointer );
}

zPVOID LOCALOPER
fnMapFile( HANDLE  *phHandle,
           zLONG   lBytes,
           zPLONG  plPageTableIndex,
           zCPCHAR cpcShareName )
{
   zPVOID pv;

   // If the handle is zero then we need to create one.
   if ( *phHandle == 0 )
   {
      zLONG  k;
      zLONG  lStartIdx;

      // Start off by finding an empty (or open) page table entry.

      if ( g_bWin95 )
         lStartIdx = 1;
      else
      {
#ifdef DEBUG_PAGETABLE
         // When we are debugging we start with page 128 so that the high bit
         // in the resulting handle will always be set.
         lStartIdx = 128;
#else
         // We start with page one (instead of zero) so that a handle will always
         // be non-zero.
         lStartIdx = 1;
#endif
      }

      for ( k = lStartIdx; k < zSHR_MAX_PAGES; k++ )
      {
         // If we find an empty page break loop.
         if ( g_ZeidonPageTable[ k ] == 0 )
            break;
      }

      if ( k >= zSHR_MAX_PAGES )
      {
         SysMessageBox( 0, szlOE_SystemError, "Out of memory pages!", -1 );
         return( 0 );
      }

      if ( g_bWin95 )
      {
         // Take into account that we have to store the index of the currently
         // allocated block of memory in the first few bytes of the memory.
         lBytes += sizeof( zLONG );
      }

      *plPageTableIndex = k;

   // TraceLine( "fnMapFile Page Table mapped at Index: %x   0x%08x   Process: %d",
   //            *plPageTableIndex, g_ZeidonPageTable[ *plPageTableIndex ], SysGetProcessID( 0 ) );

      *phHandle = CreateFileMapping( (HANDLE) -1, NULL, PAGE_READWRITE, 0, lBytes, cpcShareName );
      if ( *phHandle == 0 )
         return( 0 );
   }
   else
   {
      if ( g_ZeidonPageTable[ *plPageTableIndex ] )
      {
         TraceLine( "fnMapFile Page Table conflict at Index: %x   0x%08x   Process: %d",
                    *plPageTableIndex, g_ZeidonPageTable[ *plPageTableIndex ], SysGetProcessID( 0 ) );
      // SysMessageBox( 0, szlOE_SystemError, "Page Table conflict!", -1 );
         return( 0 );
      }
   }

#ifdef SHARED_MEM_TRACE
   fnTraceSharedMemory( "fnMapFile" );
#endif
   pv = MapViewOfFile( *phHandle, FILE_MAP_WRITE, 0, 0, 0 );

   g_ZeidonPageTable[ *plPageTableIndex ] = pv;
   g_FileMappingHandles[ *plPageTableIndex ] = (zLONG) *phHandle;

#ifdef SHARED_MEM_TRACE
   TraceLine( "fnMapFile Page Table mapped at Index: %x   0x%08x   Process: %d",
              *plPageTableIndex, g_ZeidonPageTable[ *plPageTableIndex ], SysGetProcessID( 0 ) );
#endif

   // Create a handle.
   if ( g_bWin95 )
   {
      // Store the index of the shared memory in the first couple of bytes of
      // the shared memory.
      *((zPLONG) pv)++ = *plPageTableIndex;
      *phHandle = (HANDLE) pv;
   }
   else
   {
      if ( g_bWin95 )
         *phHandle = (HANDLE) g_ZeidonPageTable[ *plPageTableIndex ];
      else
         *phHandle = (HANDLE) ((zULONG) *plPageTableIndex << 24);
   }

   return( pv );
}

//#define DEBUG_MALLOC
#ifdef DEBUG_MALLOC
#define zMAX_ALLOC_TEST  64000
zPVOID *g_pvAlloc[ zMAX_ALLOC_TEST + 1 ];
zLONG  g_lHighWaterMark = -1;
#endif

//./ ADD NAME=SysGetEnvVar
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetEnvVar
//
//  PURPOSE:    To get the address of the environment variable
//              named in the parameter envname.
//
//  PARAMETERS: EnvName environment variable to find. should be
//              all capitalized.
//
//  RETURNS:    0  - Environment variable found
//             -1  - Environment variable not found
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
SysGetEnvVar( zPCHAR pchReturnEnv, zCPCHAR cpcEnvName, zLONG lMaxLth )
{
   *pchReturnEnv = 0;

   if ( GetEnvironmentVariable( cpcEnvName, pchReturnEnv, lMaxLth ) == 0 )
      return( 1 );
   else
      return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysWait
//
//  PURPOSE:    To wait while something else finishes
//
//  PARAMETERS: uMilliseconds to wait
//
//  RETURNS:    Yes, but only after waiting
//
/////////////////////////////////////////////////////////////////////////////
void OPERATION
SysWait( zUSHORT uMilliseconds )
{
   Sleep( (DWORD) uMilliseconds );
}

//./ ADD NAME=SysDiagnosticMessage
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysDiagnosticMessage
//
//  PURPOSE:    Send an error box to the user (internal OPERATION) if
//              the "Diagnostic" flag is not 'N' in the Zeidon.ini file.
//
//  PARAMETERS: Title
//              Message
//              0 No beep, 1 beep at user
//
//  RETURNS:    Return value from message sent
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int OPERATION
SysDiagnosticMessage( zVIEW lpTaskView, zCPCHAR cpcTitle,
                      zCPCHAR cpcMessage, int nBeep )
{
   char szDiagnostic[ 2 ];

   SysReadZeidonIni( -1, "[Debug]", "Diagnostic", szDiagnostic, zsizeof( szDiagnostic ) );
   if ( szDiagnostic[ 0 ] != 'N' && szDiagnostic[ 0 ] != 'n' )
      return( SysMessageBox( lpTaskView, cpcTitle, cpcMessage, nBeep ) );

   SysMessageList( cpcMessage );
   return( 0 );
}

//./ ADD NAME=SysMessageBox
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysMessageBox
//
//  PURPOSE:    Send an error box to the user
//
//  PARAMETERS: Title
//              Message
//              0 - No beep (MB_OK)     (0)
//              1 - beep at user
//              2 - MB_ABORTRETRYIGNORE (2)
//              3 - MB_YESNOCANCEL      (3)
//              4 - MB_YESNO            (4)
//              5 - MB_RETRYCANCEL      (5)
//              6 - MB_OKCANCEL         (1)
//
//  RETURNS:    Return value from message sent
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
int OPERATION
fnSysMessageBox( LPTASK lpTask, zCPCHAR cpcTitle,
                 zCPCHAR cpcMessage, int nBeep )
{
   unsigned uRC;
   static zCHAR cShowPopup = ' ';

   // If we are connected to OE, print in message list.
   if ( AnchorBlock && AnchorBlock->lOE_hListWnd )
      SysMessageList( cpcMessage );

   // If we are a server app then we don't wan't to actually pop up a message.
   if ( AnchorBlock )
   {
      if ( cShowPopup == ' ' )
      {
         if ( lpTask == 0 )
            lpTask = zGETPTR( AnchorBlock->hMainTask );

      // if ( lpTask && lpTask->bServer )  don't care if server or not
         if ( lpTask )
         {
            zCHAR sz[ zMAX_FILENAME_LTH ];

            // Check a flag in the Zeidon INI to see if we should pop up the msg.
            SysReadZeidonIni( -1, "[Debug]", "ServerDebug", sz, zsizeof( sz ) );
            if ( *sz == 0 || ((*sz && *(sz + 1) == 0) && (*sz == 'Y' || *sz == 'y' || *sz == '1')) )
            {
               cShowPopup = 'Y';
            }
            else
            {
               cShowPopup = 'N';
               if ( *sz && *(sz + 1) )  // assume log file name
               {
                  zCHAR szLogFileName[ zMAX_FILENAME_LTH ];
                  zLONG hLogFile;

                  SysConvertEnvironmentString( szLogFileName, zsizeof( szLogFileName ), sz );
                  if ( (hLogFile = fnSysOpenFile( lpTask, szLogFileName, COREFILE_APPEND )) != -1 )
                  {
                     fnSysWriteLine( lpTask, hLogFile, 0, cpcMessage );
                     fnSysCloseFile( lpTask, hLogFile, 0 );
                  }
                  else
                  {
                     TraceLine( "Message Handler Error opening log file (%s) for message: %s",
                                szLogFileName, cpcMessage );
                  }
               }
            }
         }
         else
            cShowPopup = 'Y';
      }

      if ( cShowPopup == 'N' )
         return( 0 );
   }

// if ( nBeep )                   the beep is generated by MB_ICONSTOP in the
//    MessageBeep( MB_ICONSTOP ); call to MessageBox below ... dks 2005.04.28

   if ( nBeep <= 1 || nBeep > 6 )
      nBeep = 0;
   else
   if ( nBeep == 6 )
      nBeep = 1;

   uRC = MessageBox( GetActiveWindow( ), cpcMessage, cpcTitle,
                     MB_ICONSTOP | MB_OK | MB_TASKMODAL | nBeep );
   return( uRC );
}

int OPERATION
SysMessageBox( zVIEW lpTaskView, zCPCHAR cpcTitle,
               zCPCHAR cpcMessage, int nBeep )
{
   zCHAR  sz[ 10 ];

   SysReadZeidonIni( -1, "[ObjectEngine]", "WebUserErrorMessages", sz, zsizeof( sz ) );
   if ( sz[ 0 ] == 'Y' || sz[ 0 ] == 'y' )
   {
      TraceLine( "SysMessageBox Title: %s   Error: %s", cpcTitle, cpcMessage );
      return( -1 );
   }
   else
   {
      if ( nBeep == -1 )  // no valid tasks/view exist
      {
         MessageBox( GetActiveWindow( ), cpcMessage, cpcTitle, MB_ICONSTOP | MB_OK | MB_TASKMODAL );
         return( MB_OK );
      }
      else
      {
         LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

         return( fnSysMessageBox( lpTask, cpcTitle, cpcMessage, nBeep ) );
      }
   }
}

//./ ADD NAME=SysMessageList
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysMessageList
//
//  PURPOSE:    Write a line in the object services trace window
//              (internal OPERATION).  The memory used to pass the
//              message to the trace window must be global since
//              a task switch occurs.
//
//  PARAMETERS: Message
//
//  RETURNS:    0   - Message sent to list box
//            non-zero - Error sending message to list box
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int OPERATION
SysMessageList( zCPCHAR cpcMessage )
{
   int    nRC = zCALL_ERROR;  // Default rc to zCALL_ERROR
   zPCHAR pchMsg;

#define zTRACE_LTH  65535
   char g_szMessage[ zTRACE_LTH + 1 ];  // SysMessageList

   if ( AnchorBlock && AnchorBlock->bTraceCnt == FALSE )
      return( 0 );

   pchMsg = g_szMessage;
   *pchMsg = *cpcMessage;

   pchMsg[ 1 ] = 0;  // force null termination of message
   if ( AnchorBlock && AnchorBlock->bShowTaskID )
   {
      static zCHAR szLastDateTime[ 20 ] = "";
      zCHAR szCurrentDateTime[ 20 ];
      zCHAR szFormattedDateTime[ 30 ];
      zLONG hTask = 0;
      zVIEW v = GetDefaultViewForActiveTask( );

      if ( v )
         hTask = (zLONG) v->hTask;

      if ( hTask == 0 )
         hTask = (zLONG) AnchorBlock->hMainTask;

      SysGetDateTime( szCurrentDateTime, zsizeof( szCurrentDateTime ) );
      if ( zstrncmp( szLastDateTime, szCurrentDateTime, 6 ) == 0 )
      {
         // Current date matches last date so we'll just display the time.
         UfFormatDateTime( szFormattedDateTime, zsizeof( szFormattedDateTime ), szCurrentDateTime, "HH:MI:SS.999" );
      }
      else
      {
         // Current date is different from the date of the last message.
         // Print the date and time.
         UfFormatDateTime( szFormattedDateTime, zsizeof( szFormattedDateTime ), szCurrentDateTime, "YYYY-MM-DD HH:MI:SS.999" );
         strcpy_s( szLastDateTime, zsizeof( szLastDateTime ), szCurrentDateTime );
      }

      sprintf_s( pchMsg, zsizeof( g_szMessage ), "%s Task(%x) : ", szFormattedDateTime, hTask );
      strncat_s( pchMsg, zsizeof( g_szMessage ), (zPCHAR) cpcMessage, zsizeof( g_szMessage ) - (zstrlen( pchMsg ) + 1) );
   }
   else
   if ( *cpcMessage )
   {
      strncat_s( pchMsg + 1, zsizeof( g_szMessage ) - 1, cpcMessage + 1, zsizeof( g_szMessage ) - 2 );
   }

   if ( AnchorBlock && AnchorBlock->lOE_hListWnd )
   {
      COPYDATASTRUCT cd;

      cd.dwData = LB_ADDSTRING;
      cd.lpData = pchMsg;
      cd.cbData = zstrlen( (zPCHAR) cd.lpData ) + 1;

#ifdef __MUTEX_DEBUG__
      // We use 'zMUTEX_COUNT' as an ID for SendMessage.
   // fnPrintMutexInfo( 's', zMUTEX_COUNT, __FILE__, __LINE__ ); recursion
#endif

      // Use WM_COPYDATA to send the message so we don't have any memory leaks.
      SendMessage( (HWND) AnchorBlock->lOE_hListWnd, WM_COPYDATA, 0, (LPARAM) &cd );

#ifdef __MUTEX_DEBUG__
      // We use 'zMUTEX_COUNT' as an ID for SendMessage.
     // fnPrintMutexInfo( 'S', zMUTEX_COUNT, __FILE__, __LINE__ ); recursion
#endif

      nRC = 0;
   }
   else
      SysMessageBox( 0, "OE Trace Unavailable", pchMsg, -1 );

   return( nRC );
}

//./ ADD NAME=SysSetUserID
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysSetUserID
//
//  PURPOSE:    Set UserID and password for the user
//              If the current task is the main task then the default
//              User for the system is set, if the current task is
//              not the main task, then the user for the current
//              task alone is set.
//
//  PARAMETERS: UserID and Password
//
//  RETURNS:    0   - Message sent to list box
//            non-zero - Error sending message to list box
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int OPERATION
SysSetUserID( LPTASK lpTask, zCPCHAR cpcUserID, zCPCHAR cpcPassword )
{
   char szMsg[ 80 ];

   if ( AnchorBlock == 0 )
      return( zCALL_ERROR );

   if ( lpTask && zGETHNDL( lpTask ) != AnchorBlock->hMainTask )
   {
      lpTask->hUserID = fnFreeDataspace( zGETPTR( lpTask->hUserID ) );
      lpTask->hPassword = fnFreeDataspace( zGETPTR( lpTask->hPassword ) );
      if ( cpcUserID[ 0 ] )
      {
         lpTask->hUserID = fnStoreStringInDataspace( (LPDATAHEADER) g_hAnchorBlock, cpcUserID );
      }

      if ( cpcPassword[ 0 ] )
      {
         lpTask->hPassword = fnStoreStringInDataspace( (LPDATAHEADER) g_hAnchorBlock, cpcPassword );
      }
   }
   else
   {
      // These next two lines don't seem to do a lot, but leaving them cuz they've been here since 10a ... dks 2015.11.17
      strcpy_s( AnchorBlock->szUserID, zsizeof( AnchorBlock->szUserID ), AnchorBlock->szUserID );
      strcpy_s( AnchorBlock->szPassword, zsizeof( AnchorBlock->szPassword ), AnchorBlock->szPassword );
      if ( cpcUserID[ 0 ] )
         strcpy_s( AnchorBlock->szUserID, zsizeof( AnchorBlock->szUserID ), cpcUserID );

      if ( cpcPassword[ 0 ] )
         strcpy_s( AnchorBlock->szPassword, zsizeof( AnchorBlock->szPassword ), cpcPassword );
   }

   // Send UserID to list box
   strcpy_s( szMsg, zsizeof( szMsg ), "(sy) Logon Userid=" );
   strcat_s( szMsg, zsizeof( szMsg ), (zPCHAR) cpcUserID );
   SysMessageList( szMsg );
   return( 0 );
}

//./ ADD NAME=SysSetDB_UserID
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysSetDB_UserID
//
//  PURPOSE:    Set the database User ID and password for a user, this
//              may be used to set a user id and password for use
//              by database handlers if the database user id is to be
//              different from the standard userid.
//
//  PARAMETERS: UserID and Password
//
//  RETURNS:    0   - Message sent to list box
//            non-zero - Error sending message to list box
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int OPERATION
SysSetDB_UserID( zVIEW lpView, zCPCHAR cpcUserID, zCPCHAR cpcPassword )
{
   LPTASK lpTask;

   if ( AnchorBlock == 0 )
      return( zCALL_ERROR );

   lpTask = zGETPTR( lpView->hTask );
   if ( lpTask )
   {
      lpTask->hDBUserID = fnFreeDataspace( zGETPTR( lpTask->hDBUserID ) );
      lpTask->hDBPassword = fnFreeDataspace( zGETPTR( lpTask->hDBPassword ) );
      if ( cpcUserID[ 0 ] )
      {
         lpTask->hDBUserID = fnStoreStringInDataspace( (LPDATAHEADER) g_hAnchorBlock, cpcUserID );
      }

      if ( cpcPassword[ 0 ] )
      {
         lpTask->hDBPassword = fnStoreStringInDataspace( (LPDATAHEADER) g_hAnchorBlock, cpcPassword );
      }
   }

   return( 0 );
}

//./ ADD NAME=SysGetUserID
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetUserID
//
//  PURPOSE:    Get UserID and password for the user.  If there is a
//              UserID for the current task, it and its password is
//              returned.  If there is no UserID for the current task
//              return the UserID (if present) for the system.
//
//  PARAMETERS: returned UserID and returned Password
//
//  RETURNS:
//                 0 - UserID and Password returned (could be null)
//       zCALL_ERROR - Core not up or application not registered.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int OPERATION
SysGetUserID( zVIEW lpView, zPCHAR pchUserID, zLONG lUserLth, zPCHAR pchPassword, zLONG lPasswordLth )
{
   LPTASK lpTask;

   // Initialize in case of early errors.
   pchUserID[ 0 ] = 0;
   pchPassword[ 0 ] = 0;

   // OE not up, get out.
   if ( AnchorBlock == 0 )
      return( zCALL_ERROR );

   if ( lpView == 0 )
      lpTask = zGETPTR( AnchorBlock->hMainTask );
   else
      lpTask = zGETPTR( lpView->hTask );

   // No task for this caller, gonzo.
   if ( lpTask == 0 )
      return( zCALL_ERROR );

   // first check for a userid at the task level.
   if ( zGETHNDL( lpTask ) != AnchorBlock->hMainTask && lpTask->hUserID )
   {
      // return the userid
      strcpy_s( pchUserID, lUserLth, zGETPTR( lpTask->hUserID ) );

      // return password, if present.
      if ( lpTask->hPassword )
         strcpy_s( pchPassword, lPasswordLth, zGETPTR( lpTask->hPassword ) );
   }
   else
   {
      // Next, check the system level for a userid
      if ( *AnchorBlock->szUserID )
      {
         // return the system userid
         strcpy_s( pchUserID, lUserLth, AnchorBlock->szUserID );

         // return the system password
         if ( *AnchorBlock->szPassword )
            strcpy_s( pchPassword, lPasswordLth, AnchorBlock->szPassword );
      }
   }

   return( 0 );
}

//./ ADD NAME=SysGetDB_UserID
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetDB_UserID
//
//  PURPOSE:    Get the Database User ID and password. This operation
//              retrieves the database userid and password if one has been
//              set with SysSetDB_UserID, otherwise it returns the standard
//              userid and password
//
//  PARAMETERS: returned UserID and returned Password
//
//  RETURNS:
//                 0 - UserID and Password returned (could be null)
//       zCALL_ERROR - Core not up or application not registered.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int OPERATION
SysGetDB_UserID( zVIEW lpView, zPCHAR pchUserID, zLONG lUserLth, zPCHAR pchPassword, zLONG lPasswordLth )
{
   LPTASK lpTask;

   // Initialize in case of early errors.
   pchUserID[ 0 ] = 0;
   pchPassword[ 0 ] = 0;

   // OE not up, get out.
   if ( AnchorBlock == 0 )
      return( zCALL_ERROR );

   lpTask = zGETPTR( lpView->hTask );

   // No task for this caller, gonzo.
   if ( lpTask == 0 )
      return( zCALL_ERROR );

   // first check for a userid at the task level.
   if ( lpTask->hDBUserID )
   {
      // return the userid
      strcpy_s( pchUserID, lUserLth, zGETPTR( lpTask->hDBUserID ) );

      // return password, if present.
      if ( lpTask->hDBPassword )
         strcpy_s( pchPassword, lPasswordLth, zGETPTR( lpTask->hDBPassword ) );
   }
   else
   {
      SysGetUserID( lpView, pchUserID, lUserLth, pchPassword, lPasswordLth );
   }

   return( 0 );
}

//./ ADD NAME=SysCreateTempFileName
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysCreateTempFileName
//
// PROTOTYPE:
//
//     zSHORT OPERATION
//     SysCreateTempFileName( zPCHAR pchFrom, zPCHAR pchTo, zBOOL bOverwrite )
//
//   PURPOSE: Creates a temporary file name in the Zeidon Temp directory.
//
//   RETURN VALUE: 0 - Name created OK.  The only possible error is that the
//                     Zeidon object engine is not running.
//                 zCALL_ERROR - other error.
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT OPERATION
SysCreateTempFileName( zPCHAR pchTargetName )
{
   zLONG  lTime;
   zULONG ulTask;
   *pchTargetName = 0;

   ulTask = (zULONG) GetCurrentProcessId( );
   lTime = SysGetTickCount( );
   sprintf_s( pchTargetName, zMAX_FILENAME_LTH + 1, "%sZTF_%lx_%lx.TMP",
              AnchorBlock->szZeidonLoc, ulTask, lTime );
   return( 0 );
}

#define COPY_BUFFER_LTH 10000

//./ ADD NAME=SysCopyFile
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysCopyFile
//
// PROTOTYPE:
//
//     zSHORT OPERATION
//     SysCopyFile( zCPCHAR cpcFrom, zCPCHAR cpcTo, zBOOL bOverwrite )
//
//   PURPOSE: To copy a file.  If bOverwrite = FALSE, don't copy file if
//            destination file already exists.
//
//   RETURN VALUE:  1 - Copy OK.
//                 -1 - Target already exists.
//                 -2 - Source file not found.
//                 zCALL_ERROR - other error.
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT OPERATION
fnSysCopyFile( LPTASK  lpTask,
               zCPCHAR cpcFileSpecFrom,
               zCPCHAR cpcFileSpecTo,
               zBOOL   bOverwrite )
{
   zLONG    hFileTo;
   zLONG    hFileFrom;
   zSHORT   k;
   zLONG    hMem = 0;
   zPCHAR   pchBuffer;

   if ( bOverwrite == FALSE &&
        fnSysOpenFile( lpTask, cpcFileSpecTo, COREFILE_EXIST ) == 0 )
   {
      return( -1 );
   }

   hFileFrom = fnSysOpenFile( lpTask, cpcFileSpecFrom, COREFILE_READ );
   if ( hFileFrom <= 0 )
      return( -2 );

   hFileTo = fnSysOpenFile( lpTask, cpcFileSpecTo, COREFILE_WRITE );
   if ( hFileTo <= 0 )
   {
      fnSysCloseFile( lpTask, hFileFrom, 0 );
      return( zCALL_ERROR );
   }

   hMem = SysAllocMemory( &pchBuffer, COPY_BUFFER_LTH, 0, zCOREMEM_ALLOC, 0 );
   if ( pchBuffer == 0 )
   {
      fnSysCloseFile( lpTask, hFileFrom, 0 );
      fnSysCloseFile( lpTask, hFileTo, 0 );
      return( zCALL_ERROR );
   }

   for ( ; ; )
   {
      k = fnSysReadFile( lpTask, hFileFrom, pchBuffer, COPY_BUFFER_LTH );
      if ( k > 0 )
         fnSysWriteFile( lpTask, hFileTo, pchBuffer, k );
      else
         break;
   }

   SysFreeMemory( hMem );
   fnSysCloseFile( lpTask, hFileFrom, 0 );
   fnSysCloseFile( lpTask, hFileTo, 0 );
   return( 1 );
}

zSHORT OPERATION
SysCopyFile( zVIEW   lpTaskView,
             zCPCHAR cpcFileSpecFrom,
             zCPCHAR cpcFileSpecTo,
             zBOOL   bOverwrite )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysCopyFile( lpTask, cpcFileSpecFrom, cpcFileSpecTo, bOverwrite ) );
}

//./ ADD NAME=SysRenameFile
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysRenameFile
//
// PROTOTYPE:
//
//     zSHORT OPERATION
//     SysRenameFile( zPCHAR pchFrom, zPCHAR pchTo, zBOOL bOverwrite )
//
//   PURPOSE: To rename a file.  If bOverwrite = FALSE, don't rename file if
//            destination name already exists.
//
//   RETURN VALUE:  1 - Rename OK.
//                 -1 - Target already exists.
//                 -2 - Source file not found.
//                 zCALL_ERROR - other error.
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT OPERATION
fnSysRenameFile( LPTASK  lpTask,
                 zPCHAR  pchFileSpecFrom,
                 zPCHAR  pchFileSpecTo,
                 zBOOL   bOverwrite )
{
   if ( fnSysOpenFile( lpTask, pchFileSpecFrom, COREFILE_EXIST ) < 0 )
      return( -1 );

   if ( fnSysOpenFile( lpTask, pchFileSpecTo, COREFILE_EXIST ) >= 0 )
   {
      if ( bOverwrite == FALSE )
         return( -1 );

      // Delete the new name if it already exists.
   // if ( fnSysOpenFile( lpTask, pchFileSpecTo, COREFILE_DELETE ) == -1 )
      if ( fnSysOpenFile( lpTask, pchFileSpecTo, COREFILE_DELETE ) == zCALL_ERROR )
         return( zCALL_ERROR );
   }

   if ( !MoveFile( pchFileSpecFrom, pchFileSpecTo ) )
   {
      zPCHAR pchMsg;
      DWORD dw = GetLastError( );

      FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                     0, dw, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (zPCHAR) &pchMsg, 0, 0 );
      TraceLine( "SysRenameFile MoveFile RC: %ld   FileSpecFrom: %s   FileSpecTo: %s   Error: %s",
                 dw, pchFileSpecFrom, pchFileSpecTo, pchMsg );
      fnSysMessageBox( lpTask, "Zeidon MoveFile Error", pchMsg, 1 );

      LocalFree( pchMsg ); // free the buffer
      return( zCALL_ERROR );
   }

   return( 1 );
}

zSHORT OPERATION
SysRenameFile( zVIEW   lpTaskView,
               zPCHAR  pchFileSpecFrom,
               zPCHAR  pchFileSpecTo,
               zBOOL   bOverwrite )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysRenameFile( lpTask, pchFileSpecFrom, pchFileSpecTo, bOverwrite ) );
}

//./ ADD NAME=SysOpenFile
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysOpenFile
//
// PROTOTYPE:
//
//     zLONG OPERATION
//     SysOpenFile( zVIEW lpTaskView, zCPCHAR cpcFileName, int Flags )
//
//   PURPOSE: To open a file based on the filename using the flag passed
//            to indicate the type of open to be done.  The flag values
//            are:
//
//        COREFILE_READ                0x0080
//        COREFILE_WRITE               0x0040
//        COREFILE_UPDATE              COREFILE_READ | COREFILE_WRITE
//        COREFILE_CREATE              0x0020
//        COREFILE_DELETE              0x0008
//        COREFILE_RENAME              0x0010
//        COREFILE_EXIST               0x0004
//        COREFILE_WRITELINE_BUFFERED  0x0001
//        COREFILE_APPEND              0x0100 | COREFILE_UPDATE
//        COREFILE_BACKUP              0x1000
//
//   For COREFILE_RENAME/COPY, the old name is followed by the new name in
//   cpcFileName, separated by a null terminator.  Example:
//
//       SysOpenFile( lpTaskView, "oldname.txt\0newname.txt", COREFILE_RENAME );
//
//   RETURN VALUE: A handle to the file opened or -1 if the file could not be
//                 opened, NOTE the return value of a COREFILE_EXIST/DELETE/RENAME
//                 call cannot be subsequently used in other file requests!!!
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG OPERATION
fnSysOpenFile( LPTASK lpTask, zCPCHAR cpcFileName, int nFlags )
{
   zCHAR      szTempFileName[ 2 * zMAX_FILESPEC_LTH + 1 ];
   HANDLE     hFile = (HANDLE) -1;
   LPOPENFILE lpOpenFile;
   LPTASK     lpMainTask;
   zSHORT     nTrys = 0;

// TraceLine( "fnSysOpenFile %s  Task: 0x%08x   Process: 0x%08x", cpcFileName, lpTask, lProcessID );

   while ( (lpMainTask = zGETPTR( AnchorBlock->hMainTask )) == 0 && nTrys < 100 )
   {
      SysWait( 100 );
      nTrys++;
   }

   if ( lpMainTask == 0 || lpTask == 0 )
   {
      if ( lpTask == 0 )
      {
         TraceLine( "SysOpenFile for file: %s failed due to invalid view (null task)", cpcFileName );
      }

      return( -1 );
   }

   strcpy_s( szTempFileName, zsizeof( szTempFileName ), cpcFileName );

   // Check to see if we are going to write the file to a backup file first.
   if ( nFlags & COREFILE_BACKUP )
   {
      zCHAR  szExtension[ 10 ];
      zPCHAR pch = szTempFileName + zstrlen( szTempFileName ) - 1;

      // Backup until we find the period.
      while ( pch > szTempFileName && *pch != '.' )
         pch--;

      // Save the extension for later use.
      if ( pch > szTempFileName )
         strcpy_s( szExtension, zsizeof( szExtension ), pch );

      // Backup until we find the first directory separator.
      while ( pch > szTempFileName && *pch != cDirSep )
         pch--;

      // Make sure we don't lose the dir separator.
      if ( *pch == cDirSep )
         pch++;

      // Create a temp file name using the current task ID.
      sprintf_s( pch, zsizeof( szTempFileName ) - (pch - szTempFileName), "0x%08x%s", (zULONG) zGETHNDL( lpTask ), szExtension );
   }

   if ( nFlags & COREFILE_READ )
   {
      if ( nFlags & COREFILE_WRITE )
      {
         hFile = CreateFile( szTempFileName, GENERIC_WRITE | GENERIC_READ,
                             FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
         if ( hFile == INVALID_HANDLE_VALUE )
            hFile = (HANDLE) -1;

         if ( (zLONG) hFile != -1 )
         {
            if ( (nFlags & COREFILE_APPEND) == COREFILE_APPEND )
            {
               SetFilePointer( hFile, 0, 0, FILE_END );
            }
         }
      }
      else
      {
         hFile = CreateFile( szTempFileName, GENERIC_READ,
                             FILE_SHARE_READ, 0, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL, 0 );
      }
   }
   else
   if ( (nFlags & COREFILE_WRITE) || (nFlags & COREFILE_CREATE) )
   {
      if ( (nFlags & COREFILE_CREATE_NEW) == COREFILE_CREATE_NEW )
         hFile = CreateFile( szTempFileName, GENERIC_WRITE,
                             FILE_SHARE_READ, 0, CREATE_NEW,
                             FILE_ATTRIBUTE_NORMAL, 0 );
      else
         hFile = CreateFile( szTempFileName, GENERIC_WRITE,
                             FILE_SHARE_READ, 0, CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL, 0 );
   }
   else
   if ( nFlags & COREFILE_EXIST )
   {
      zCHAR  szPath[ 2 * zMAX_FILESPEC_LTH + 1 ];
      zCHAR  szFN[ 2 * zMAX_FILESPEC_LTH + 1 ];
      zCHAR  szResult[ 10 ];
      zPCHAR pch;

      // Find the last directory separator.
      strcpy_s( szPath, zsizeof( szPath ), szTempFileName );
      pch = &szPath[ zstrlen( szPath ) - 1 ];
      while ( pch >= szPath && *pch != cDirSep && *pch != ':' )
         pch--;

      // Copy the filename and extension.
      strcpy_s( szFN, zsizeof( szFN ), pch + 1 );

      // Set null terminator in szPath to remove filename and extension.
      pch[ 1 ] = 0;

      // Note that the " 9, szResult, &pch" arguments are really dummy args.
      if ( SearchPath( szPath, szFN, 0, 9, szResult, &pch ) > 0 )
         return( 1 ); // File exists.
      else
         return( -1 );
   }
   else
   if ( nFlags & COREFILE_DELETE )
   {
      zLONG lRC = DeleteFile( szTempFileName );
      if ( lRC == 0 )
      {
         zPCHAR pchMsg;
         DWORD  dw = GetLastError( );

         FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                        0, dw, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (zPCHAR) &pchMsg, 0, 0 );
         TraceLine( "SysDeleteFile Error: %s   File: %s   RC: %d",
                    pchMsg, szTempFileName, dw );
      // fnSysMessageBox( lpTask, "Zeidon DeleteFile Error", pchMsg, 1 );
         LocalFree( pchMsg ); // free the buffer
         return( -1 );
      }
      else
         return( 0 );
   }
   else
   if ( nFlags & COREFILE_RENAME )
   {
      zPCHAR pchNew = (zPCHAR) &cpcFileName[ zstrlen( cpcFileName ) + 1 ];

      // Call fnSysRenameFile.
      return( fnSysRenameFile( lpTask, (zPCHAR) cpcFileName, pchNew, TRUE ) );
   }

   if ( hFile == (HANDLE) -1 )
   {
      // The following statement was added and the lines
      // above commented out because getcwd was abending.
      // This should be reversed when getcwd is ok.
      TraceLineS( "(sy) Could not open file: ", szTempFileName );
      TraceLineI( "(sy) Reason code = ", GetLastError( ) );
      return( -1 );
   }

   // If we got here, then a file open was successful.
   // Create an open file record on the AnchorBlock chain.
   {
      zPVOID hOpenFile;

      // We need to allocate and initialize an OpenFile record and then
      // chain it to the task block.
      hOpenFile = fnAllocDataspace( lpTask->hFirstDataHeader, sizeof( OpenFileRecord ), 1, 0, iOpenFile );
      if ( hOpenFile )
      {
         zLONG lProcessID = SysGetProcessID( 0 );
         zBOOL bMutexLocked;

         lpOpenFile = zGETPTR( hOpenFile );

         if ( zGETHNDL( lpTask ) == AnchorBlock->hMainTask )
         {
            bMutexLocked = TRUE;
            zLOCK_MUTEX( zMUTEX_ANCHORBLOCK );
         }
         else
            bMutexLocked = FALSE;

         // Now chain the OpenFile record to the task block.
         lpOpenFile->hNextOpenFile = lpTask->hFirstOpenFile;
         lpTask->hFirstOpenFile    = hOpenFile;
         lpOpenFile->lProcessID    = lProcessID;
         lpOpenFile->nFlags        = nFlags;
         lpOpenFile->lFileHandle   = (zLONG) hFile;
         strcpy_s( lpOpenFile->szFileName, zsizeof( lpOpenFile->szFileName ), cpcFileName );
         strcpy_s( lpOpenFile->szTempFileName, zsizeof( lpOpenFile->szTempFileName ), szTempFileName );

         if ( bMutexLocked )
            zUNLOCK_MUTEX( zMUTEX_ANCHORBLOCK );
      }
   }

// TraceLine( "fnSysOpenFile %s   Handle: 0x%08x   Task: 0x%08x",
//            cpcFileName, hFile, lpTask );

   return( (zLONG) hFile );  // return the handle to the file
}

zLONG OPERATION
SysOpenFile( zVIEW lpTaskView, zCPCHAR cpcFileName, int nFlags )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysOpenFile( lpTask, cpcFileName, nFlags ) );
}

//./ ADD NAME=SysReadFile
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysReadFile
//
// PROTOTYPE:
//
// This example opens or creates and opens a file named "DOSTEST.DAT",
// writes to it, reads from it, and finally closes the file.
//
// #define INCL_DOSFILEMGR          // File Manager values
// #define INCL_DOSERRORS           // DOS Error values
// #include <os2.h>
// #include <stdio.h>
// #include <string.h>
//
// int main( void )
// {
//    zLONG  hfFileHandle   = 0;  // Handle for file being manipulated
//    ULONG  ulAction       = 0;  // Action taken by DosOpen
//    ULONG  ulBytesRead    = 0;  // Number of bytes read by DosRead
//    ULONG  ulWrote        = 0;  // Number of bytes written by DosWrite
//    ULONG  ulLocal        = 0;  // File pointer position after DosSetFilePtr
//    UCHAR  uchFileName[20]  = "dostest.dat",  // Name of file
//           uchFileData[100] = " ";            // Data to write to file
//    APIRET rc             = NO_ERROR;         // Return code
//
//    // Open the file dostest.dat. Use an existing file or create a new
//    // one if it doesn't exist.
//    rc = DosOpen( uchFileName,                 // File path name
//                  &hfFileHandle,               // File handle
//                  &ulAction,                   // Action taken
//                  100L,                        // File primary allocation
//                  FILE_ARCHIVED | FILE_NORMAL, // File attribute
//                  OPEN_ACTION_CREATE_IF_NEW |
//                  OPEN_ACTION_OPEN_IF_EXISTS,  // Open function type
//                  OPEN_FLAGS_NOINHERIT |
//                  OPEN_SHARE_DENYNONE  |
//                  OPEN_ACCESS_READWRITE,       // Open mode of the file
//                  0L );                        // No extended attribute
//
//    if ( rc != NO_ERROR )
//    {
//       printf( "DosOpen error: return code = %u\n", rc );
//       return( 1 );
//    }
//    else
//    {
//      printf( "DosOpen: Action taken = %ld\n", ulAction );
//    }
//
//    // Write a string to the file
//    strcpy( uchFileData, "testing...\n1...\n2...\n3\n" );
//
//    rc = DosWrite( hfFileHandle,         // File handle
//                   (PVOID) uchFileData,  // String to be written
//                   zsizeof (uchFileData), // Size of string to be written
//                   &ulWrote );           // Bytes actually written
//
//    if ( rc != NO_ERROR )
//    {
//       printf( "DosWrite error: return code = %u\n", rc );
//       return( 1 );
//    }
//    else
//    {
//       printf( "DosWrite: Bytes written = %u\n", ulWrote );
//    }
//
//    // Move the file pointer back to the beginning of the file
//    rc = DosSetFilePtr( hfFileHandle,  // File Handle
//                        0L,            // Offset
//                        FILE_BEGIN,    // Move from BOF
//                        &ulLocal );    // New location address
//    if ( rc != NO_ERROR )
//    {
//       printf( "DosSetFilePtr error: return code = %u\n", rc );
//       return( 1 );
//    }
//
//    // Read the first 100 bytes of the file
//    rc = DosRead( hfFileHandle,    // File Handle
//                  uchFileData,     // String to be read
//                  100L,            // Length of string to be read
//                  &ulBytesRead );  // Bytes actually read
//
//    if ( rc != NO_ERROR )
//    {
//       printf( "DosRead error: return code = %u\n", rc );
//       return( 1 );
//    }
//    else
//    {
//       printf( "DosRead: Bytes read = %u\n%s\n", ulBytesRead, uchFileData );
//    }
//
//    rc = DosClose( hfFileHandle );     // Close the file
//
//    if ( rc != NO_ERROR )
//    {
//       printf( "DosClose error: return code = %u\n", rc );
//       return( 1 );
//    }
//
//    return( NO_ERROR );
// }
//
//   DosOpen returns one of the following values:
//
//       0         NO_ERROR
//       2         ERROR_FILE_NOT_FOUND
//       3         ERROR_PATH_NOT_FOUND
//       4         ERROR_TOO_MANY_OPEN_FILES
//       5         ERROR_ACCESS_DENIED
//       12        ERROR_INVALID_ACCESS
//       26        ERROR_NOT_DOS_DISK
//       32        ERROR_SHARING_VIOLATION
//       36        ERROR_SHARING_BUFFER_EXCEEDED
//       82        ERROR_CANNOT_MAKE
//       87        ERROR_INVALID_PARAMETER
//       99        ERROR_DEVICE_IN_USE
//       108       ERROR_DRIVE_LOCKED
//       110       ERROR_OPEN_FAILED
//       112       ERROR_DISK_FULL
//       206       ERROR_FILENAME_EXCED_RANGE
//       231       ERROR_PIPE_BUSY
//
//
//     DosRead returns one of the following values:
//
//       0         NO_ERROR
//       5         ERROR_ACCESS_DENIED
//       6         ERROR_INVALID_HANDLE
//       26        ERROR_NOT_DOS_DISK
//       33        ERROR_LOCK_VIOLATION
//       109       ERROR_BROKEN_PIPE
//       234       ERROR_MORE_DATA
//
//
//     unsigned int OPERATION
//     SysReadFile( zLONG lFileHandle )
//
// PURPOSE:  To read a block of data from an opened file
//
// RETURNS:  Number of bytes read
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
unsigned int OPERATION
fnSysReadFile( LPTASK  lpTask,
               zLONG   lFileHandle,
               zPCHAR  pchBuffer,
               zULONG  ulMaxLth )
{
   ULONG ulBytes;

   if ( ReadFile( (HANDLE) lFileHandle, pchBuffer, ulMaxLth, &ulBytes, 0 ) )
      return( ulBytes );
   else
      return( 0 );
}

unsigned int OPERATION
SysReadFile( zVIEW   lpTaskView,
             zLONG   lFileHandle,
             zPCHAR  pchBuffer,
             zULONG  ulMaxLth )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysReadFile( lpTask, lFileHandle, pchBuffer, ulMaxLth ) );
}

//./ ADD NAME=SysReadLine
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysReadLine
//
// PROTOTYPE:
//
//     int OPERATION
//     SysReadLine( (zCOREMEM) lpReturnLine, zLONG lFileHandle )
//
// PURPOSE:  To read a line of information from a file
//
// RETURNS:  1 - line read successful
//           0 - End of file reached
//          zCALL_ERROR - Error in processing
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
int OPERATION
fnSysReadLine( LPTASK   lpTask,
               zCOREMEM lpReturnLine,
               zLONG    lFileHandle,
               zPVOID   *ppvFile )
{
   unsigned int  uPos;
   unsigned int  uEnd;
   LPOPENFILE lpOpenFile = 0;
   zPCHAR   lpBuffer;

   *lpReturnLine = 0;
   if ( ppvFile && *ppvFile )
   {
      lpOpenFile = (LPOPENFILE) *ppvFile;
      if ( lpOpenFile->lFileHandle != lFileHandle )
      {
         lpOpenFile = 0;
      }
   }

   if ( lpOpenFile == 0 )
   {
      lpOpenFile = zGETPTR( lpTask->hFirstOpenFile );
      while ( lpOpenFile )
      {
         if ( lpOpenFile->lFileHandle == lFileHandle )
            break;

         lpOpenFile = zGETPTR( lpOpenFile->hNextOpenFile );
      }
   }

   if ( lpOpenFile == 0 )
   {
      zVIEW vTask = zGETPTR( lpTask->hFirstView );

      fnStartBrowseOfTaskList( zGETHNDL( lpTask ), FALSE );
      DisplayOpenFiles( "SysReadLine null OpenFile", zGETHNDL( lpTask ) );
      fnEndBrowseOfTaskList( FALSE );
      IssueError( vTask, 0, 0, "SysReadLine ... no open files" );
      return( zCALL_ERROR );
   }

   // File found ... get a file read buffer if necessary.
   if ( ppvFile )
      *ppvFile = lpOpenFile;

   if ( lpOpenFile->uReadBufferSize == 0 )
   {
      if ( lpOpenFile->uReadBufferPos != 0 )
      {
         // it seems to me that the read position would have to be zero if the buffer size is zero ... dks 2015.12.11
         fnSysMessageBox( 0, "Zeidon Error", "Error in buffered file position", 0 );
         return( zCALL_ERROR );
      }

      lpOpenFile->uReadBufferSize = 32770;   // 32768 + 2;
      while ( lpOpenFile->uReadBufferSize > 1026 )
      {
         lpOpenFile->hReadBuffer = fnAllocDataspace( lpTask->hFirstDataHeader, lpOpenFile->uReadBufferSize, 0, 0, 0 );
         if ( lpOpenFile->hReadBuffer )
            break;

         lpOpenFile->uReadBufferSize -= 1024;
      }

      if ( lpOpenFile->hReadBuffer == 0 )  // if buffer acquisition failed
      {
         zVIEW vTask = zGETPTR( lpTask->hFirstView );

         IssueError( vTask, 0, 0, "SysReadLine ... buffer acquisition failure" );
         lpOpenFile->uReadBufferSize = 0;
         return( zCALL_ERROR );
      }

      // Bump size down by 2 so we can safely null terminate lines.
      lpOpenFile->uReadBufferSize -= 2;

      lpBuffer = zGETPTR( lpOpenFile->hReadBuffer );

      // Read the first block of information into the buffer.
      lpOpenFile->uReadBufferUsed = fnSysReadFile( lpTask,
                                                   lpOpenFile->lFileHandle,
                                                   lpBuffer,
                                                   lpOpenFile->uReadBufferSize );
   }
   else
   // See if it is time to read more of the file in before continuing.
   if ( lpOpenFile->uReadBufferUsed == lpOpenFile->uReadBufferSize &&
        lpOpenFile->uReadBufferPos > (lpOpenFile->uReadBufferSize - (lpOpenFile->uReadBufferSize / 10)) )
   {
      lpBuffer = zGETPTR( lpOpenFile->hReadBuffer );

      // Copy remaining unprocessed buffer to beginning of buffer.
      if ( lpOpenFile->uReadBufferPos < lpOpenFile->uReadBufferSize )
      {
         zmemcpy( lpBuffer,
                  &lpBuffer[ lpOpenFile->uReadBufferPos ],
                  lpOpenFile->uReadBufferSize - lpOpenFile->uReadBufferPos );
      }

      // Adjust the position and used values.
      lpOpenFile->uReadBufferUsed -= lpOpenFile->uReadBufferPos;
      lpOpenFile->uReadBufferPos  = 0;

      // Read another chunk of the file data.
      lpOpenFile->uReadBufferUsed +=
       fnSysReadFile( lpTask,
                      lpOpenFile->lFileHandle,
                      (zPCHAR) (lpBuffer + lpOpenFile->uReadBufferUsed),
                      (zULONG) (lpOpenFile->uReadBufferSize - lpOpenFile->uReadBufferUsed) );
   }
   else
   {
      lpBuffer = zGETPTR( lpOpenFile->hReadBuffer );
   }

   // If we get here, we're ready to proceed ahead in getting a line to return.
   uPos = lpOpenFile->uReadBufferPos;
   uEnd = lpOpenFile->uReadBufferUsed;

   // If current pos is end of file, and we're at the end of file, skip the rest of the data.
   if ( lpBuffer[ uPos ] == '\x1a' )
   {
      // If followed by a crlf or new-line, also skip that.
      if ( (uPos + 1) >= uEnd ||
           (lpBuffer[ uPos + 1 ] == '\n' && uPos + 2 >= uEnd) ||
           (lpBuffer[ uPos + 1 ] == '\r' && lpBuffer[ uPos + 2 ] == '\n' && uPos + 3 >= uEnd) )
      {
         uPos = uEnd;
      }
   }

   // If nothing to return to the user, set position to end.
   if ( uPos >= uEnd )
   {
      lpOpenFile->uReadBufferPos = lpOpenFile->uReadBufferUsed;
      return( 0 );
   }

   // Now that beginning of line is found, search for end and put a null character there.
   *lpReturnLine = &lpBuffer[ uPos ];
   while( uPos < uEnd &&
          lpBuffer[ uPos ] != '\r' &&
          lpBuffer[ uPos ] != '\n' &&
          lpBuffer[ uPos ] != '\x1a' )
   {
      uPos++;
   }

   if ( (lpBuffer[ uPos ] == '\r' && lpBuffer[ uPos + 1 ] == '\n') ||
        (lpBuffer[ uPos ] == '\n' && lpBuffer[ uPos + 1 ] == '\r') )
   {
      lpBuffer[ uPos++ ] = 0;  // null end of line and skip \r or \n
   }

   lpBuffer[ uPos++ ] = 0;            // null end of line
   lpOpenFile->uReadBufferPos = uPos; // set new uPos
   return( 1 );                       // everything is AOK
}

int OPERATION
SysReadLine( zVIEW    lpTaskView,
             zCOREMEM lpReturnLine,
             zLONG    lFileHandle )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysReadLine( lpTask, lpReturnLine, lFileHandle, 0 ) );
}

//./ ADD NAME=SysReadLineLth
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysReadLineLth
//
// PROTOTYPE:
//
//     int OPERATION
//     SysReadLineLth( (zCOREMEM) lpReturnLine,
//                     zLONG   lFileHandle,
//                     zULONG  ulLth )
//
// PURPOSE:  To read a Blob of data while doing Readline processing
//           on a file.
//
// RETURNS:  1 - line read successful
//           0 - End of file reached
//          zCALL_ERROR - Error in processing
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT OPERATION
fnSysReadLineLth( LPTASK   lpTask,
                  zCOREMEM lpReturnLine,
                  zLONG    lFileHandle,
                  zPVOID   *ppvFile,
                  zULONG   ulLth )
{
   LPOPENFILE    lpOpenFile = 0;
   zPCHAR        lpNewBuffer;
   zPCHAR        lpReadBuffer;

   *lpReturnLine = 0;

   if ( ppvFile && *ppvFile )
   {
      lpOpenFile = (LPOPENFILE) *ppvFile;
      if ( lpOpenFile->lFileHandle != lFileHandle )
         lpOpenFile = 0;
   }

   if ( lpOpenFile == 0 )
   {
      lpOpenFile = zGETPTR( lpTask->hFirstOpenFile );
      while ( lpOpenFile )
      {
         if ( lpOpenFile->lFileHandle == lFileHandle )
            break;

         lpOpenFile = zGETPTR( lpOpenFile->hNextOpenFile );
      }
   }

   if ( lpOpenFile == 0 )
      return( zCALL_ERROR );

   // File found, get a file read buffer if necessary.
   if ( lpOpenFile->uReadBufferSize == 0 )
   {
      if ( lpOpenFile->uReadBufferPos != 0 )
      {
         // it seems to me that the read position would have to be zero if the buffer size is zero ... dks 2015.12.11
         fnSysMessageBox( 0, "Zeidon Error", "Error in buffered file position", 0 );
         return( zCALL_ERROR );
      }

      lpOpenFile->uReadBufferSize = 8192;
      while ( lpOpenFile->uReadBufferSize > 2040 )
      {
         lpOpenFile->hReadBuffer = fnAllocDataspace( lpTask->hFirstDataHeader,
                                                     lpOpenFile->uReadBufferSize, 0, 0, 0 );

         if ( lpOpenFile->hReadBuffer )
            break;

         lpOpenFile->uReadBufferSize /= 2;
      }

      if ( lpOpenFile->hReadBuffer == 0 )  // if buffer acquisition failed
      {
         lpOpenFile->uReadBufferSize = 0;
         return( zCALL_ERROR );
      }

      lpReadBuffer = zGETPTR( lpOpenFile->hReadBuffer );

      // Bump size down by 2 so we can safely null terminate lines.
      lpOpenFile->uReadBufferSize -= 2;

      // Read the first block of information into the buffer
      lpOpenFile->uReadBufferUsed = fnSysReadFile( lpTask,
                                                   lpOpenFile->lFileHandle,
                                                   lpReadBuffer,
                                                   lpOpenFile->uReadBufferSize );
   }
   else
   {
      lpReadBuffer = zGETPTR( lpOpenFile->hReadBuffer );
   }

   // See if buffer we are using is big enough to hold the blob we want to
   // read, if not, we're in big trouble.
   if ( lpOpenFile->uReadBufferSize < ulLth )
   {
      zPVOID hNewBuffer;

      hNewBuffer = fnAllocDataspace( lpTask->hFirstDataHeader, ulLth, 0, 0, 0 );
      if ( hNewBuffer == 0 )
         return( zCALL_ERROR );

      lpNewBuffer = zGETPTR( hNewBuffer );

      zmemcpy( lpNewBuffer, lpReadBuffer, lpOpenFile->uReadBufferSize );
      fnFreeDataspace( zGETPTR( lpOpenFile->hReadBuffer ) );
      lpReadBuffer = lpNewBuffer;
      lpOpenFile->hReadBuffer = hNewBuffer;
      lpOpenFile->uReadBufferSize = ulLth;
      lpOpenFile->uReadBufferUsed +=
            fnSysReadFile( lpTask, lpOpenFile->lFileHandle,
                           (zPCHAR) (lpReadBuffer + lpOpenFile->uReadBufferUsed),
                           (zULONG) (lpOpenFile->uReadBufferSize - lpOpenFile->uReadBufferUsed) );
   }

   // See if it is time to read more of the file in before continuing.
   if ( lpOpenFile->uReadBufferUsed == lpOpenFile->uReadBufferSize &&
        (lpOpenFile->uReadBufferSize - lpOpenFile->uReadBufferPos) < ulLth )
   {
      // Copy remaining unprocessed buffer to beginning of buffer.
      if ( lpOpenFile->uReadBufferPos < lpOpenFile->uReadBufferSize )
      {
         zmemcpy( lpReadBuffer,
                  &lpReadBuffer[ lpOpenFile->uReadBufferPos ],
                  lpOpenFile->uReadBufferSize - lpOpenFile->uReadBufferPos );
      }

      // Adjust the position and used values.
      lpOpenFile->uReadBufferUsed -= lpOpenFile->uReadBufferPos;
      lpOpenFile->uReadBufferPos = 0;

      // Read another chunk of the file data.
      lpOpenFile->uReadBufferUsed +=
         fnSysReadFile( lpTask, lpOpenFile->lFileHandle,
                        (zPCHAR) ((zPCHAR) zGETPTR( lpOpenFile->hReadBuffer ) + lpOpenFile->uReadBufferUsed),
                        (zULONG) (lpOpenFile->uReadBufferSize - lpOpenFile->uReadBufferUsed) );
   }

   // Now that beginning of line is found, search for end and
   // put a null character there.
   *lpReturnLine = &lpReadBuffer[ lpOpenFile->uReadBufferPos ];
   lpOpenFile->uReadBufferPos += ulLth; // set new uPos
   return( 1 );                         // everything is AOK
}

zSHORT OPERATION
SysReadLineLth( zVIEW    lpTaskView,
                zCOREMEM lpReturnLine,
                zLONG    lFileHandle,
                zULONG   ulLth )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysReadLineLth( lpTask, lpReturnLine, lFileHandle, 0, ulLth ) );
}

//./ ADD NAME=SysWriteFile
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysWriteFile
//
// PROTOTYPE:
//
//      int OPERATION
//      SysWriteFile( zLONG   lFileHandle,
//                    zCPCHAR szBuffer,
//                    int nLth )
//
// PURPOSE:  To write a block of data to an opened file
//
// RETURNS:  Number of bytes written
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zULONG OPERATION
fnSysWriteFile( LPTASK  lpTask,
                zLONG   lFileHandle,
                zCPCHAR cpcBuffer,
                zULONG  ulLth )
{
   zULONG ulWritten;

   WriteFile( (HANDLE) lFileHandle, cpcBuffer, ulLth, &ulWritten, 0 );

   if ( ulWritten != ulLth )
   {
      LPOPENFILE  lpOpenFile;

      lpOpenFile = zGETPTR( lpTask->hFirstOpenFile );
      while ( lpOpenFile )
      {
         if ( lpOpenFile->lFileHandle == lFileHandle )
            break;

         lpOpenFile = zGETPTR( lpOpenFile->hNextOpenFile );
      }

      if ( lpOpenFile )
      {
         // "KZOEE022 - Error writing file"
         fnIssueCoreError( lpTask, 0, 8, 22, 0, lpOpenFile->szFileName, 0 );
      }
   }

   return( ulWritten );
}

zULONG OPERATION
SysWriteFile( zVIEW   lpTaskView,
              zLONG   lFileHandle,
              zCPCHAR cpcBuffer,
              zULONG  ulLth )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysWriteFile( lpTask, lFileHandle, cpcBuffer, ulLth ) );
}

//./ ADD NAME=SysWriteLine
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysWriteLine
//
// PROTOTYPE:
//
//      int OPERATION
//      SysWriteLine( zLONG   lFileHandle,
//                    zCPCHAR cpcLine );
//
// PURPOSE:  To write a line into a buffered file
//
// RETURNS:  0 if OK.
//           zCALL_ERROR otherwise.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
int OPERATION
fnSysWriteLine( LPTASK   lpTask,
                zLONG    lFileHandle,
                zPVOID   *ppvFile,
                zCPCHAR  cpcLine )
{
   zLONG      lLth;
   zPCHAR     lpWriteBuffer;
   LPOPENFILE lpOpenFile = 0;

   // Get the task an match up the file handle passed with an
   // OpenFile record. If the record is not found, return a zCALL_ERROR;
   if ( lpTask == 0 )
      return( zCALL_ERROR );

   if ( ppvFile && *ppvFile )
   {
      lpOpenFile = (LPOPENFILE) *ppvFile;
      if ( lpOpenFile->lFileHandle != lFileHandle )
         lpOpenFile = 0;
   }

   if ( lpOpenFile == 0 )
   {
      lpOpenFile = zGETPTR( lpTask->hFirstOpenFile );
      while ( lpOpenFile )
      {
         if ( lpOpenFile->lFileHandle == lFileHandle )
            break;

         lpOpenFile = zGETPTR( lpOpenFile->hNextOpenFile );
      }
   }

   if ( lpOpenFile == 0 )
      return( zCALL_ERROR );

   // Check to see if buffered WriteLines desired, if not, write it.
   if ( (lpOpenFile->nFlags & COREFILE_WRITELINE_BUFFERED) == 0 )
   {
      fnSysWriteFile( lpTask, lFileHandle, cpcLine, zstrlen( cpcLine ) );
      fnSysWriteFile( lpTask, lFileHandle, "\r\n", 2 );
      return( 0 );
   }

   // File found, get a file read buffer if necessary.
   if ( lpOpenFile->uWriteBufferSize == 0 )
   {
      if ( lpOpenFile->uWriteBufferPos != 0 )
      {
         // it seems to me that the write position would have to be zero if the buffer size is zero ... dks 2015.12.11
         fnSysMessageBox( 0, "Zeidon Error", "Error in buffered file position", 0 );
         return( zCALL_ERROR );
      }

      lpOpenFile->uWriteBufferSize = 8192;
      while ( lpOpenFile->uWriteBufferSize > 2040 )
      {
         lpOpenFile->hWriteBuffer = fnAllocDataspace( lpTask->hFirstDataHeader, lpOpenFile->uWriteBufferSize, 0, 0, 0 );
         if ( lpOpenFile->hWriteBuffer )
            break;

         lpOpenFile->uWriteBufferSize /= 2;
      }

      if ( lpOpenFile->hWriteBuffer == 0 )  // if buffer acquisition failed
      {
         lpOpenFile->uWriteBufferSize = 0;
         return( zCALL_ERROR );
      }

      // Bump size down by 2 so we can safely null terminate lines.
      lpOpenFile->uWriteBufferSize -= 2;
   }

   lpWriteBuffer = zGETPTR( lpOpenFile->hWriteBuffer );

   // Get the length of the line to be written.
   lLth = zstrlen( cpcLine );

   // If there is not buffer room to write this line, write out the buffer and reset position.
   if ( (zULONG) (lpOpenFile->uWriteBufferSize - lpOpenFile->uWriteBufferPos) <= (zULONG) (lLth + 3) )  // 2 for the crlf and 1 for the null terminator ... dks 2015.12.11
   {
      fnSysWriteFile( lpTask, lFileHandle, lpWriteBuffer, lpOpenFile->uWriteBufferPos );
      lpOpenFile->uWriteBufferPos = 0;
   }

   // Copy the new line into the Buffer.
   strcpy_s( lpWriteBuffer + lpOpenFile->uWriteBufferPos, lpOpenFile->uWriteBufferSize - lpOpenFile->uWriteBufferPos, cpcLine );
   lpOpenFile->uWriteBufferPos += lLth;
   strcpy_s( lpWriteBuffer + lpOpenFile->uWriteBufferPos, lpOpenFile->uWriteBufferSize - lpOpenFile->uWriteBufferPos, "\r\n" );
   lpOpenFile->uWriteBufferPos += 2;

   return( 0 );
}

int OPERATION
SysWriteLine( zVIEW   lpTaskView,
              zLONG   lFileHandle,
              zCPCHAR cpcLine )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysWriteLine( lpTask, lFileHandle, 0, cpcLine ) );
}

//./ ADD NAME=SysWriteLineLth
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysWriteLineLth
//
// PROTOTYPE:
//
//      int OPERATION
//      SysWriteLineLth( zLONG   lFileHandle,
//                       zCPCHAR cpcLine,
//                       zULONG  ulLth,
//                       zBOOL   bAppend );
//
// PURPOSE:  To write a line into a buffered file
//
// RETURNS:  0 if OK.
//           zCALL_ERROR otherwise.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 6
int OPERATION
fnSysWriteLineLth( LPTASK   lpTask,
                   zLONG    lFileHandle,
                   zPVOID   *ppvFile,
                   zCPCHAR  cpcLine,
                   zULONG   ulLth,
                   zBOOL    bAppend )
{
   zPCHAR        lpWriteBuffer;
   LPOPENFILE    lpOpenFile = 0;

   if ( ppvFile && *ppvFile )
   {
      lpOpenFile = (LPOPENFILE) *ppvFile;
      if ( lpOpenFile->lFileHandle != lFileHandle )
         lpOpenFile = 0;
   }

   if ( lpOpenFile == 0 )
   {
      lpOpenFile = zGETPTR( lpTask->hFirstOpenFile );
      while ( lpOpenFile )
      {
         if ( lpOpenFile->lFileHandle == lFileHandle )
            break;

         lpOpenFile = zGETPTR( lpOpenFile->hNextOpenFile );
      }
   }

   if ( lpOpenFile == 0 )
      return( zCALL_ERROR );

   // Check to see if buffered WriteLines desired.  If not, write it and get out.
   if ( (lpOpenFile->nFlags & COREFILE_WRITELINE_BUFFERED) == 0 )
   {
      fnSysWriteFile( lpTask, lFileHandle, cpcLine, ulLth );
      if ( bAppend )
         fnSysWriteFile( lpTask, lFileHandle, "\r\n", 2 );

      return( 0 );
   }

   // File found, get a file buffer if necessary.
   if ( lpOpenFile->uWriteBufferSize == 0 )
   {
      if ( lpOpenFile->uWriteBufferPos != 0 )
      {
         // it seems to me that the write position would have to be zero if the buffer size is zero ... dks 2015.12.11
         fnSysMessageBox( 0, "Zeidon Error", "Error in buffered file position", 0 );
         return( zCALL_ERROR );
      }

      lpOpenFile->uWriteBufferSize = 8192;
      while ( lpOpenFile->uWriteBufferSize > 2040 )
      {
         lpOpenFile->hWriteBuffer = fnAllocDataspace( lpTask->hFirstDataHeader, lpOpenFile->uWriteBufferSize, 0, 0, 0 );
         if ( lpOpenFile->hWriteBuffer )
            break;

         lpOpenFile->uWriteBufferSize /= 2;
      }

      if ( lpOpenFile->hWriteBuffer == 0 )  // if buffer acquisition failed
      {
         lpOpenFile->uWriteBufferSize = 0;
         return( zCALL_ERROR );
      }

      // Bump size down by 2 so we can safely null terminate lines.
      lpOpenFile->uWriteBufferSize -= 2;
   }

   lpWriteBuffer = zGETPTR( lpOpenFile->hWriteBuffer );

   // If there is not buffer room to write this line, write out buffer and reset position.
   if ( (lpOpenFile->uWriteBufferSize - lpOpenFile->uWriteBufferPos) < ulLth + 3 )  // 2 for the crlf and 1 for the null terminator ... dks 2015.12.11
   {
      fnSysWriteFile( lpTask, lFileHandle, lpWriteBuffer, lpOpenFile->uWriteBufferPos );
      lpOpenFile->uWriteBufferPos = 0;
   }

   // If the write to be done is bigger than the buffer, simply write the line passed and (if appending) put a crlf in the buffer.
   if ( lpOpenFile->uWriteBufferSize < ulLth + 2 )
   {
      fnSysWriteFile( lpTask, lFileHandle, cpcLine, ulLth );
   }
   else
   {
      // Copy the new line into the Buffer.
      zmemcpy( lpWriteBuffer + lpOpenFile->uWriteBufferPos, cpcLine, ulLth );
      lpOpenFile->uWriteBufferPos += ulLth;
   }

   if ( bAppend )
   {
      strcpy_s( lpWriteBuffer + lpOpenFile->uWriteBufferPos,
                lpOpenFile->uWriteBufferSize - lpOpenFile->uWriteBufferPos, "\r\n" );
      lpOpenFile->uWriteBufferPos += 2;
   }

   return( 0 );
}

int OPERATION
SysWriteLineLth( zVIEW   lpTaskView,
                 zLONG   lFileHandle,
                 zCPCHAR cpcLine,
                 zULONG  ulLth,
                 zBOOL   bAppend )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysWriteLineLth( lpTask, lFileHandle, 0, cpcLine, ulLth, bAppend ) );
}

//./ ADD NAME=SysCloseFile
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysCloseFile
//
// PROTOTYPE:
//
//     long OPERATION
//     SysCloseFile( zLONG lFileHandle, LPTASK lpOwningTask )
//
// RETURNS:  0 - OK.
//           zCALL_ERROR
//
// PURPOSE:  To close a previously opened file
//
//           The owning application task should be passed as 0 for
//           ALL cases EXCEPT DeleteTask when ObjectServices may
//           be calling to clean up a task gone south
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT OPERATION
fnSysCloseFileWithControl( LPTASK lpTask,
                           zLONG  lFileHandle,
                           LPTASK lpOwningTask,
                           zLONG  lControl )
{
   LPOPENFILE  lpOpenFile;
   LPOPENFILE  lpPrevOpenFile;
   zSHORT      nRC;

   nRC = zCALL_ERROR;

// TraceLine( "fnSysCloseFileWithControl ??   Handle: 0x%08x   Task: 0x%08x   Process: 0x%08x",
//            lFileHandle, lpTask, lProcessID );

   // Get the task and match up the file handle passed with an
   // OpenFile record. If the record is not found, return a zCALL_ERROR;
   if ( lpTask == 0 )
      return( zCALL_ERROR );

   if ( lpOwningTask == 0 )
      lpOwningTask = lpTask;

   zLOCK_MUTEX( zMUTEX_ANCHORBLOCK );

   // Find open file and prev open file.
   for ( lpPrevOpenFile = 0, lpOpenFile = zGETPTR( lpTask->hFirstOpenFile );
         lpOpenFile;
         lpPrevOpenFile = lpOpenFile, lpOpenFile = zGETPTR( lpOpenFile->hNextOpenFile ) )
   {
      if ( lpOpenFile->lFileHandle == lFileHandle )
         break;
   }

   if ( lpOpenFile == 0 )
   {
      zUNLOCK_MUTEX( zMUTEX_ANCHORBLOCK );
      return( zCALL_ERROR );
   }

   if ( lpPrevOpenFile )
      lpPrevOpenFile->hNextOpenFile = lpOpenFile->hNextOpenFile;
   else
      lpTask->hFirstOpenFile = lpOpenFile->hNextOpenFile;

   zUNLOCK_MUTEX( zMUTEX_ANCHORBLOCK );

   // If the file has been used for buffered writes, write it out now.
   if ( lpOpenFile->nFlags & COREFILE_WRITELINE_BUFFERED )
   {
      if ( lpOwningTask == lpTask && lpOpenFile->hWriteBuffer && lpOpenFile->uWriteBufferPos )
      {
         fnSysWriteFile( lpTask, lpOpenFile->lFileHandle,
                         zGETPTR( lpOpenFile->hWriteBuffer ),
                         lpOpenFile->uWriteBufferPos );
      }
   }

   // Open file record cleaned up, close the file
   // Note: Although the close may fail, keeping the open
   // file record around is probably of little value.
   // Note: We only close when called by application, not
   // when called by a task cleanup from object services because
   // the handle may have been reused by another task
   // after the owning task bombed.
   nRC = 0;
   if ( lpOwningTask == lpTask )
   {
      zLONG lProcessID = SysGetProcessID( 0 );
/*
      if ( lpTask != zGETPTR( AnchorBlock->hMainTask ) ) // this trace causes problems when starting OE
      {
         TraceLine( "fnSysCloseFileWithControl %s   Handle: 0x%08x   Task: 0x%08x   Process: 0x%08x:0x%08x",
                    lpOpenFile->szFileName, lFileHandle, lpTask, lProcessID, lpOpenFile->lProcessID );
      }
*/
      if ( lpOpenFile->lProcessID == lProcessID )
         nRC = CloseHandle( (HANDLE) lFileHandle ) ? 0 : zCALL_ERROR;
   }

   // If the file was opened with the backup option then we need to rename
   // the backup file to the original file.
   if ( lpOpenFile->nFlags & COREFILE_BACKUP )
   {
      // Don't rename the file if the abort option was set.
      if ( (lControl & CLOSEFILE_ABORT_BACKUP) == 0 )
      {
// DGC 2000.11.06 Following code creates backups.  Taken out for more
// consideration.
#if 0
         zCHAR szBackup[ zMAX_FILENAME_LTH + 1 ];

         // Rename the original file to a .BAK file.
         strcpy_s( szBackup, zsizeof( szBackup ), lpOpenFile->szFileName );
         strcat_s( szBackup, zsizeof( szBackup ), ".BAK" );
         if ( SysRenameFile( lpOpenFile->szFileName, szBackup, TRUE ) == zCALL_ERROR )
         {
            nRC = zCALL_ERROR;
         }
#endif

         if ( fnSysRenameFile( lpOwningTask, lpOpenFile->szTempFileName,
                               lpOpenFile->szFileName, TRUE ) == zCALL_ERROR )
         {
            nRC = zCALL_ERROR;
         }
      }
   }

   fnFreeDataspace( zGETPTR( lpOpenFile->hReadBuffer ) );
   fnFreeDataspace( zGETPTR( lpOpenFile->hWriteBuffer ) );
   fnFreeDataspace( lpOpenFile );
   return( nRC );
}

zSHORT OPERATION
SysCloseFileWithControl( zVIEW  lpTaskView,
                         zLONG  lFileHandle,
                         LPTASK lpOwningTask,
                         zLONG  lControl )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysCloseFileWithControl( lpTask, lFileHandle, lpOwningTask, lControl ) );
}

int   OPERATION
fnSysCloseFile( LPTASK lpTask,
                zLONG  lFileHandle,
                LPTASK lpOwningTask )
{
   return( fnSysCloseFileWithControl( lpTask, lFileHandle, lpOwningTask, 0 ) );
}

int   OPERATION
SysCloseFile( zVIEW  lpTaskView,
              zLONG  lFileHandle,
              LPTASK lpOwningTask )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysCloseFileWithControl( lpTask, lFileHandle, lpOwningTask, 0 ) );
}

#define CONVERT_2_DIGITS( pch ) ((*(pch) - '0') * 10 + *(pch + 1) - '0')

//./ ADD NAME=SysSetFileTime
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:      SysSetFileTime
//
// PURPOSE:  To change the "last written/modified" date of a file.
//
// PROTOTYPE:
//
//     zSHORT OPERATION
//     SysSetFileTime( zCPCHAR cpcFileName, zCPCHAR cpcDateTime, zLONG lControl )
//
// PARAMETERS:
//      cpcFileName - Name of file.  Must be fully qualified.
//      cpcDateTime - New datetime for file.  In the form of YYYYMMDDHHMMSSmmm
//      lControl    - Not currently used.
//
// RETURNS:  0 - OK.
//           zCALL_ERROR
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
SysSetFileTime( zCPCHAR cpcFileName, zCPCHAR cpcDateTime, zLONG lControl )
{
   FILETIME   ftTime;
   SYSTEMTIME SysTime;
   HANDLE     hFile;
   zCHAR      szTemp[ 10 ];
   zCHAR      szFileName[ zMAX_FILESPEC_LTH + 1 ];

   strncpy_s( szTemp, zsizeof( szTemp ), cpcDateTime, 4 );
   szTemp[ 4 ] = 0;
   SysTime.wYear         = (WORD) atoi( szTemp );
   SysTime.wMonth        = CONVERT_2_DIGITS( cpcDateTime + 4 );
   SysTime.wDay          = CONVERT_2_DIGITS( cpcDateTime + 6 );
   SysTime.wHour         = CONVERT_2_DIGITS( cpcDateTime + 8 );
   SysTime.wMinute       = CONVERT_2_DIGITS( cpcDateTime + 10 );
   SysTime.wSecond       = CONVERT_2_DIGITS( cpcDateTime + 12 );
   SysTime.wMilliseconds = (WORD) atoi( cpcDateTime + 14 );
   SystemTimeToFileTime( &SysTime, &ftTime );

   SysConvertEnvironmentString( szFileName, zsizeof( szFileName ), cpcFileName );
   hFile = CreateFile( szFileName, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
   if ( hFile == INVALID_HANDLE_VALUE )
   {
      TraceLineS( "SysSetFileTime: Couldn't open file ", szFileName );
      return( zCALL_ERROR );
   }

   SetFileTime( hFile, 0, 0, &ftTime );
   CloseHandle( hFile );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetBaseMessage
//
// PROTOTYPE:
//
//     int  OPERATION
//     SysGetBaseMessage( zPCHAR pchReturnString, long lMessageID, int nMaxLth )
//
// PURPOSE:  To return a base object engine message from the base
//           message table.
//
// RETURNS: The length of the message returned
//
/////////////////////////////////////////////////////////////////////////////
zSHORT  OPERATION
SysGetBaseMessage( zPCHAR pchReturnString, zLONG lID, zSHORT nMaxLth )
{
   zSHORT k;
   zSHORT nLth;

   for ( k = 0;
         BaseMsgTable[ k ].nID != lID && BaseMsgTable[ k ].nID != 9999;
         k++ )
   {
   }

   nLth = (zSHORT) zstrlen( BaseMsgTable[ k ].szMsg );

   if ( BaseMsgTable[ k ].nID == lID )
   {
      if ( nLth >= nMaxLth )
         nLth = nMaxLth - 1;

      strncpy_s( pchReturnString, nMaxLth, BaseMsgTable[ k ].szMsg, nLth );
      pchReturnString[ nLth ] = 0;
      return( nLth );
   }
   else
   {
      pchReturnString[ 0 ] = 0;
      return( 0 );
   }
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetOperationMessage
//
// PROTOTYPE:
//
//     int  OPERATION
//     SysGetOperationMessage( zPCHAR pchReturnString, zLONG lMessageID, int nMaxLth )
//
// PURPOSE:  To return a base object engine message from the base
//           message table.
//
// RETURNS: The length of the message returned
//
/////////////////////////////////////////////////////////////////////////////
zSHORT  OPERATION
SysGetOperationMessage( zPCHAR pchReturnString, zLONG lID, zSHORT nMaxLth )
{
   zSHORT k;
   zSHORT nLth;

   for ( k = 0;
         OperationMsgTable[ k ].nID != lID && OperationMsgTable[ k ].nID != 9999;
         k++ )
   {
   }

   nLth = (zSHORT) zstrlen( OperationMsgTable[ k ].szMsg );

   if ( OperationMsgTable[ k ].nID == lID )
   {
      if ( nLth >= nMaxLth )
         nLth = nMaxLth - 1;

      strncpy_s( pchReturnString, nMaxLth, OperationMsgTable[ k ].szMsg, nLth );
      pchReturnString[ nLth ] = 0;
      return( nLth );
   }
   else
   {
      pchReturnString[ 0 ] = 0;
      return( 0 );
   }
}

//./ ADD NAME=SysPositionFile
/////////////////////////////////////////////////////////////////////////////
//
//   ENTRY:    SysPositionFile
//
//   PROTOTYPE:
//        zLONG OPERATION
//        SysPositionFile( zLONG  hFile, zLONG lPosition )
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG OPERATION
SysPositionFile( zLONG  hFile,
                 zLONG  lPosition )
{
   return( SetFilePointer( (HANDLE) hFile, lPosition, 0, FILE_BEGIN ) );
}

//./ ADD NAME=SysGetFilePosition
/////////////////////////////////////////////////////////////////////////////
//
//   ENTRY:    SysGetFilePosition
//
//   PROTOTYPE:
//        zLONG OPERATION
//        SysGetFilePosition( zLONG  hFile, zLONG lPosition )
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zULONG OPERATION
SysGetFilePosition( zLONG  hFile )
{
   return( SetFilePointer( (HANDLE) hFile, 0, 0, FILE_CURRENT ) );
}

//./ ADD NAME=SysGetFileSize
/////////////////////////////////////////////////////////////////////////////
//
//   ENTRY:    SysGetFileSize
//
//   PROTOTYPE:
//        zLONG OPERATION
//        SysGetFileSize( zLONG  hFile )
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zULONG OPERATION
SysGetFileSize( zLONG  hFile )
{
   return( GetFileSize( (HANDLE) hFile, 0 ) );
}

//./ ADD NAME=SysTruncateFile
/////////////////////////////////////////////////////////////////////////////
//
//   ENTRY:    SysTruncateFile
//
//   PROTOTYPE:
//        int  OPERATION
//        SysTruncateFile( zLONG  hFile )
//
//   RETURNS:   0   - AOK
//            non-zero - Error
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int  OPERATION
fnSysTruncateFile( LPTASK lpTask, zLONG hFile )
{
   SysPositionFile( hFile, 0 );
   return( fnSysWriteFile( lpTask, hFile, "", 0 ) );
}

int  OPERATION
SysTruncateFile( zVIEW lpTaskView, zLONG hFile )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   return( fnSysTruncateFile( lpTask, hFile ) );
}

//./ ADD NAME=SysParseLine
/////////////////////////////////////////////////////////////////////////////
//    ENTRY:   SysParseLine
//
//    PURPOSE: This routine parses a line from a Portable or INI file.
//
//    DESCRIPTION: This routine attempts to find and return two
//    sub-strings from InputString.  The first of the two, PortName,
//    has no embedded blanks.  PortValue, however, may. If there
//    is nothing in InputString, both are returned as null strings.
//    If only one sub-string is found, it is returned in PortName
//    and PortValue is returned null.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
void  OPERATION
SysParseLine( zPCHAR    pchPortName,
              zLONG     lPortNameLth,
              zCOREMEM  PortValue,
              zPCHAR    pchInputString )
{
   if ( pchInputString )
   {
      int  k;
      int  iInputLth;
      int  iStartPos;

      k = -1;
      iInputLth = zstrlen( pchInputString );

      // look for begining of first parm
      do
         k++;
      while ( (pchInputString[ k ] == ' ') && (k < iInputLth) );
      iStartPos = k;

      // if no parms
      if ( iStartPos >= iInputLth )
      {
         pchPortName[ 0 ] = 0;
         *PortValue = szNullS;
      }
      else  // at least one parm
      {
         // look for end of first parm
         do
            k++;
         while ( pchInputString[ k ] != ' ' && pchInputString[ k ] != '=' && k < iInputLth );

         strncpy_s( pchPortName, lPortNameLth, pchInputString + iStartPos, k - iStartPos );
         pchPortName[ k - iStartPos ] = 0;

         // if Only one parm created set PortValue to null and return
         if ( k > iInputLth )
         {
            *PortValue = szNullS;
            return;
         }

         // Set StartPos to the greater of k + 1 or 11
         k++;
         if ( k > 10 || pchInputString[ k ] != ' ' )
            iStartPos = k;
         else
            iStartPos = 10;

         // look for begining of second parm
         while ( (pchInputString[ k ] == ' ') && (k <= iInputLth) )
            k++;

         // if only one parm
         if ( k >= iInputLth )
         {
            *PortValue = szNullS;
         }
         else     // there is a second parm
         {
            if ( k < 11 )
               iStartPos = k;

            *PortValue = (zPCHAR) (pchInputString + iStartPos);

            // if needed, get rid of trailing blanks
            k = zstrlen( *PortValue ) - 1;
            while ( k > 0 )
            {
               if ( (*PortValue)[ k ] == ' ' )
                  (*PortValue)[ k-- ] = 0;
               else
                  break;
            }
         }
      }
   }
}  // End of SysParseLine

//./ ADD NAME=SysGetLocalDirectory
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetLocalDirectory
//
// PROTOTYPE:
//     int  OPERATION
//     SysGetLocalDirectory( zPCHAR pchReturnDir )
//
// PURPOSE:  To get the Zeidon Bin directory.
//
// RETURNS:  The local directory name, suffixed with the
//           directory separator character
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int  OPERATION
SysGetLocalDirectory( zPCHAR pchReturnDir )
{
   // Temporarily return the Zeidon Bin directory.
   if ( AnchorBlock )
   {
      strcpy_s( pchReturnDir, zMAX_FILENAME_LTH + 1, AnchorBlock->szZeidonBin );
      return( 0 );
   }

   *pchReturnDir = 0;
   return( -1 );
}

//./ ADD NAME=SysGetLocalSysDirectory
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetLocalSysDirectory
//
// PROTOTYPE:
//     int  OPERATION
//     SysGetLocalSysDirectory( zPCHAR pchReturnDir )
//
// PURPOSE:  To get the Zeidon Bin/Sys directory.
//
// RETURNS:  The local directory name, suffixed with the
//           directory separator character
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int  OPERATION
SysGetLocalSysDirectory( zPCHAR pchReturnDir )
{
   // Temporarily return the Zeidon Sys directory.
   if ( AnchorBlock )
   {
      strcpy_s( pchReturnDir, zMAX_FILENAME_LTH + 1, AnchorBlock->szZeidonSys );
      return( 0 );
   }

   *pchReturnDir = 0;
   return( -1 );
}

//./ ADD NAME=SysGetFileDateTime
/////////////////////////////////////////////////////////////////////////////
//
//   FUNCTION:   SysGetFileDateTime
//
//   PROTOTYPE:
//      void  OPERATION
//      SysGetFileDateTime( zLONG hFile, zPCHAR DateTime )
//
//   RETURNS:    DateTime - yyyymmddhhmmssttt
//
//   PURPOSE: This gets the Date and Time stamp for an Open file.
//
//   DESCRIPTION:  This function retrieves information about a specific
//                 file.  The file information is based on the most
//                 recent call to the DosClose or the DosBufReset
//                 function.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
void  OPERATION
SysGetFileDateTime( zLONG  hFile,
                    zPCHAR pchDateTime,
                    zLONG  lMaxLth )
{
   FILETIME   LastWriteTime;
   SYSTEMTIME ST;             // SystemTime

   pchDateTime[ 0 ] = 0;

   if ( GetFileTime( (HANDLE) hFile, 0, 0, &LastWriteTime ) )
   {
      FileTimeToSystemTime( &LastWriteTime, &ST );
      sprintf_s( pchDateTime, lMaxLth, "%4d%02d%02d%02d%02d%02d%03d",
                 (int) ST.wYear, (int) ST.wMonth, (int) ST.wDay, (int) ST.wHour,
                 (int) ST.wMinute, (int) ST.wSecond, (int) ST.wMilliseconds );
   }
   else
      strcpy_s( pchDateTime, lMaxLth, "???????????????" );
}

//./ ADD NAME=SysGetEpochTime
/////////////////////////////////////////////////////////////////////////////
//
//   FUNCTION:   SysGetEpochTime
//
//   PROTOTYPE:
//      zLONG  OPERATION
//      SysGetEpochTime()
//
//   RETURNS:    Time since 1970 in seconds.
//
//   PURPOSE: Return Posix epoch time.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG OPERATION
SysGetEpochTime()
{
   time_t ltime;
   time( &ltime );
   return( (zLONG) ltime );
}

//./ ADD NAME=SysGetDateTime
/////////////////////////////////////////////////////////////////////////////
//
//   FUNCTION:   SysGetDateTime
//
//   PROTOTYPE:
//      void  OPERATION
//      SysGetDateTime( zPCHAR pchDateTime )
//
//   RETURNS:    DateTime yyyymmddhhmmssttt
//
//   PURPOSE: This gets the System Date and Time.
//
//   DESCRIPTION:  This function gets the system date and time. For DOS
//                 (MS Windows) the dos_getdate and dos_gettime functions
//                 are used because localtime cannot be called from a
//                 Windows DLL due to the DS != SS problem.  For OS2 and
//                 other systems (hopefully), the time/localtime version
//                 of the code can be activated.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void  OPERATION
SysGetDateTime( zPCHAR pchDateTime, zLONG lMaxLth )
{
   SYSTEMTIME ST;

   GetLocalTime( &ST );
   sprintf_s( pchDateTime, lMaxLth, "%4d%02d%02d%02d%02d%02d%03d",
              (int) ST.wYear, (int) ST.wMonth, (int) ST.wDay, (int) ST.wHour,
              (int) ST.wMinute, (int) ST.wSecond, (int) ST.wMilliseconds );
}

zSHORT OPERATION
_zCall_GetDateTime( zVIEW  vArgs,
                    zPVIEW pvViewList[] )
{
   zCHAR szDateTime[ 32 ];

   SysGetDateTime( szDateTime, zsizeof( szDateTime ) );
   SetAttributeFromString( vArgs, "Operation", "ReturnValue", szDateTime );
   return( 0 );
}

void  OPERATION
SysGetServerDateTime( zVIEW lpView, zPCHAR pchDateTime, zLONG lMaxLth )
{
   LPVIEWOD lpViewOD;

   pchDateTime[ 0 ] = 0;

   // First make sure the network is active.
   if ( lpView &&
        (lpViewOD = zGETPTR( lpView->hViewOD )) != 0 &&
        lpViewOD->szNetwork[ 0 ] &&
        NetStatus( lpView, lpViewOD->szNetwork ) != 0 )
   {
      zVIEW  vSystem;
      zSHORT nRC;

      SfCreateSystemSubtask( &vSystem, lpView, "Zeidon System" );
      nRC = NetCallOperation( "zWinSock", 0, vSystem, FALSE,
                              "kzoengaa", "GetDateTime", pchDateTime, "T" );
      SfDropSubtask( vSystem, 0 );
   }
   else
      SysGetDateTime( pchDateTime, lMaxLth );
}

//./ ADD NAME=SysGetDateTimeDifference
// Source Module=kzoesyaa.c
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:      SysGetDateTimeDifference
//
// PARAMETERS:
//             plDiff       - pointer to variable returning difference
//             pchEarlyDate - First Timestamp
//             pchLaterDate - Second Timestamp
//             nDiffType    - unit for difference (zDT_SECOND, ...)
//
// RETURNS:     0 - Success
//             -1 - overflow
//    zCALL_ERROR - Validation error during call (invalid Date Type)
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT OPERATION
SysGetDateTimeDifference( zPLONG  plDiff,
                          zPCHAR  pchEarlyDate,
                          zPCHAR  pchLaterDate,
                          zSHORT  nDiffType )
{
   DateTimeRecord EarlyDate;
   DateTimeRecord LaterDate;
   zSHORT         nRC;

   nRC = UfStringToDateTime( pchEarlyDate, &EarlyDate );
   if ( nRC < 0 )
   {
      TraceLineS( "SysGetDateTimeDifference: ",  "Invalid type for Early Date" );
      return( zCALL_ERROR );
   }

   nRC = UfStringToDateTime( pchLaterDate, &LaterDate );
   if ( nRC < 0 )
   {
      TraceLineS( "SysGetDateTimeDifference: ",  "Invalid type for Later Date" );
      return( zCALL_ERROR );
   }

   // Subtract the values.
   nRC = UfDateTimeDiff( plDiff, &EarlyDate, &LaterDate, nDiffType );

   return( nRC );
}

//./ ADD NAME=SysTranslateString
/////////////////////////////////////////////////////////////////////////////
//
//   ENTRY:    SysTranslateString
//
//   PROTOTYPE:
//        void OPERATION
//        SysTranslateString( zPCHAR pchString, char cUpperLower )
//
//   PURPOSE:  This system dependent Operation translates a string to
//             either upper case or lower case depending on the
//             upper or lower character value passed ('U' or 'L').
//
//   RETURNS:
//
//////////////////////////////////////////////////////////////////////////////
//./ END + 2
void OPERATION
SysTranslateString( zPCHAR pchString, char cUpperLower )
{
   if ( cUpperLower == 'L' )
      CharLower( pchString );
   else
      CharUpper( pchString );
}

//./ ADD NAME=SysLoadLibraryWithErrFlag
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysLoadLibraryWithErrFlag
//
// PROTOTYPE:
//
//     LPLIBRARY  OPERATION
//     SysLoadLibraryWithErrFlag( zVIEW   lpTaskView,
//                                zCPCHAR szLibraryName,
//                                zCPCHAR szErrFlag )
//
// PURPOSE:  To load a DLL or shared library into memory, passing a flag to
//           indicate whether an error message should be sent if the DLL
//           cannot be opened.
//
//           If szLibraryName is fully qualified, SysLoadLibrary will change
//           the CWD to the qualification path and then try loading the
//           unqualified library.
//
//           If szLibraryName is not fully qualified, SysLoadLibrary will
//           change the CWD to the application bin directory and then try
//           loading the unqualified library.
//
// ARGUMENTS:
//           lpTaskView - Subtask view that specifies the application.  If
//                lpTaskView is NULL, then the system application is assumed.
//           cpcLibraryName - Name of library to load.  May be qualified
//                or unqualified, but should not include the extension
//                (e.g. ".dll").
//           lErrFlag - 0 indicates message will not be sent if DLL cannot
//                        be loaded.
//                      1 indicates error message will be sent.
//
// RETURNS:  0 - Library not found
//           LPLIBRARY - Object Services handle to module
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
LPLIBRARY  OPERATION
SysLoadLibraryWithErrFlag( zVIEW   lpTaskView,
                           zCPCHAR cpcLibraryName,
                           zLONG   lFlag )
{
   LPTASK     lpTask;
   LPAPP      lpApp;
   LPLIBRARY  hLibrary;
   LPLIBRARY  lpLibrary;
   zLONG      lLibOS;
   char       szFileName[ zMAX_FILENAME_LTH + 1 ];
   char       szCurrentDir[ zMAX_FILENAME_LTH + 1 ];
   char       *pchUnqualifiedName;
   zBOOL      bQualified;
   zSHORT     nUnqualLth;
   zLONG      lProcessID = SysGetProcessID( 0 );

   // If AnchorBlock or application task does not exist, return zero.
   if ( AnchorBlock == 0 || lpTaskView == 0 || (lpTask = zGETPTR( lpTaskView->hTask )) == 0 )
   {
      return( 0 );
   }

   if ( lpTaskView )
   {
      if ( fnValidView( lpTask, lpTaskView ) == 0 )
         return( 0 );

      if ( fnGetApplicationForSubtask( &lpApp, lpTaskView ) != 0 )
         return( 0 );
   }
   else
   {
      lpApp = zGETPTR( lpTask->hApp );
      if ( lpApp == 0 )
         lpApp = zGETPTR( AnchorBlock->hSystemApp );
   }

   strcpy_s( szFileName, zsizeof( szFileName ), cpcLibraryName );
   SysTranslateString( szFileName, 'L' );

   // Check to see if library name is qualified.
   pchUnqualifiedName = zstrrchr( szFileName, cDirSep );
   if ( pchUnqualifiedName )
   {
      bQualified = TRUE;
      pchUnqualifiedName++;         // point to file name
   }
   else
   {
      bQualified = FALSE;
      pchUnqualifiedName = szFileName;
   }

   nUnqualLth = (zSHORT) zstrlen( pchUnqualifiedName );

   // If module is already loaded for this application task, get out quick!
   lpLibrary = zGETPTR( lpTask->hFirstLibrary );
   while ( lpLibrary )
   {
      // Name and flags must match!
      if ( zstrcmp( pchUnqualifiedName, lpLibrary->szName ) == 0 &&
           (lFlag & zLOADLIB_RESOURCES) == (lpLibrary->lFlag & zLOADLIB_RESOURCES) &&
           lpLibrary->lProcessID == lProcessID )
      {
         lpLibrary->ulUseCnt++;
         return( zGETHNDL( lpLibrary ) );
      }

      lpLibrary = zGETPTR( lpLibrary->hNextLibrary );
   }

   // Environment specific code begins here =================================

   // Set the current working directory.
   GetCurrentDirectory( zMAX_FILENAME_LTH + 1, szCurrentDir );
   SetCurrentDirectory( lpApp->szLibraryDir );

   strcat_s( szFileName, zsizeof( szFileName ), ".dll" );

   if ( lFlag & zLOADLIB_RESOURCES )
      lLibOS = (zLONG) LoadLibraryEx( szFileName, NULL, LOAD_LIBRARY_AS_DATAFILE );
   else
      lLibOS = (zLONG) LoadLibraryEx( szFileName, NULL, 0 );

   SetCurrentDirectory( szCurrentDir );

   if ( lLibOS == 0 )
   {
      TraceLine( "(sy) SysLoadLibrary failed to load file: \"%s\"  with error code = %d  using Current directory: %s",
                 szFileName, (zLONG) GetLastError( ), lpApp->szLibraryDir );
      if ( lFlag & zLOADLIB_WITHERR )
      {
         char  szMsg[ 256 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Load failed for: %s (%s)", cpcLibraryName, szFileName );
         MessageSend( lpTaskView, "SY00101", "System Services", szMsg, zMSGQ_SYSTEM_ERROR, 1 );
      }

      // Trace the dll name always on failure!!!
      TraceLine( "Load failed for: %s (%s)", cpcLibraryName, szFileName );

      return( 0 );
   }

// TraceLine( "LoadLibrary Task (0x%08x) successful for: %s (%s)",
//            zGETHNDL( lpTask ), cpcLibraryName, szFileName );

   // Environment specific code ends here ===================================

   // Allocate a Library record for the current task.
   hLibrary = fnAllocDataspace( lpTask->hFirstDataHeader, sizeof( LibraryRecord ), 1, 0, iLibrary );
   if ( hLibrary )
   {
      zBOOL bMutexLocked;

      lpLibrary = zGETPTR( hLibrary );
      lpLibrary->lFlag    = lFlag;
      lpLibrary->hLibrary = lLibOS;
      lpLibrary->ulUseCnt = 1;
      lpLibrary->lProcessID = lProcessID;

      pchUnqualifiedName[ nUnqualLth ] = 0;
      strcpy_s( lpLibrary->szName, zsizeof( lpLibrary->szName ), pchUnqualifiedName );

   // fnTraceLibrary( lpLibrary, 1 );
      if ( zGETHNDL( lpTask ) == AnchorBlock->hMainTask )
      {
         bMutexLocked = TRUE;
         zLOCK_MUTEX( zMUTEX_ANCHORBLOCK );
      }
      else
         bMutexLocked = FALSE;

      lpLibrary->hNextLibrary = lpTask->hFirstLibrary;
      lpTask->hFirstLibrary = hLibrary;

      if ( bMutexLocked )
         zUNLOCK_MUTEX( zMUTEX_ANCHORBLOCK );
   }

   return( hLibrary );
}

//./ ADD NAME=SysLoadLibrary
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:   SysLoadLibrary
//
// PROTOTYPE:
//     LPLIBRARY  OPERATION
//     SysLoadLibrary( zVIEW lpTaskView, zCPCHAR szLibraryName )
//
// PURPOSE:  To load a DLL or shared library into memory
//
//           If szLibraryName is fully qualified, SysLoadLibrary will try to
//           load the library IF IT EXISTS.  If it doesn't exist, then
//           SysLoadLibrary will try loading the unqualified library.
//
//           If szLibraryName is not fully qualified, SysLoadLibrary will try
//           to load the library from the application bin directory.  If the
//           library doesn't exist in the app bin dir, then SysLoadLibrary
//           will try loading the unqualified library.
//
// ARGUMENTS:
//           lpTaskView - Subtask view that specifies the application.  If lpTaskView
//                    is NULL, then the system application is assumed.
//           szLibraryName - Name of library to load.  May be qualified or
//                    unqualified.
//
// RETURNS:  0 - Library not found
//           LPLIBRARY - Object Services handle to module
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
LPLIBRARY  OPERATION
SysLoadLibrary( zVIEW lpTaskView, zCPCHAR cpcLibraryName )
{
   return( SysLoadLibraryWithErrFlag( lpTaskView, cpcLibraryName, zLOADLIB_WITHERR ) );
}

//./ ADD NAME=SysGetProc
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetProc
//
// PROTOTYPE:
//     zPVOID OPERATION
//     SysGetProc( LPLIBRARY lpLibrary, zCPCHAR szProcName )
//
// PURPOSE:  To get a function address from a DLL given the function name
//
// RETURNS:    0   - Free OK
//           non-zero - error
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zPVOID OPERATION
SysGetProc( LPLIBRARY hLibrary, zCPCHAR cpcProcName )
{
   LPLIBRARY lpLibrary = zGETPTR( hLibrary );
   zPVOID    pfReturn;

   if ( cpcProcName == 0 || cpcProcName[ 0 ] == 0 || lpLibrary == 0 )
      pfReturn = 0;
   else
   {
      pfReturn = GetProcAddress( (HMODULE) lpLibrary->hLibrary, cpcProcName );
      if ( pfReturn == 0 )
      {
#if 0
         char szMessage[ 16 ];

         SysReadZeidonIni( -1, "[Debug]", "BombZDr", szMessage, zsizeof( szMessage ) );
         if ( szMessage[ 0 ] == 'Y' )
         {
            zSHORT k = 0;
            k /= k;
         }
#endif
         TraceLine( "(sy) SysGetProc failed with error code: %d   DLL: %s   Function: %s",
                    (zLONG) GetLastError( ), lpLibrary->szName, cpcProcName );
      }
   }

   return( pfReturn );
}

//./ ADD NAME=SysGetInstance
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysGetInstance
//
// PROTOTYPE:
//
//     zLONG  OPERATION
//     SysGetInstance( LPLIBRARY hLibrary )
//
// PURPOSE:  To get an instance pointer for a DLL.
//
// RETURNS:  hInstance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zLONG OPERATION
SysGetInstance( LPLIBRARY hLibrary )
{
   LPLIBRARY lpLibrary = zGETPTR( hLibrary );

   if ( lpLibrary )
      return( (zLONG) lpLibrary->hLibrary );
   else
      return( 0 );
}

//./ ADD NAME=fnSysFreeLibrary
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    fnSysFreeLibrary
//
// PURPOSE:  To free a DLL for a task
//
// RETURNS:  0 - all libraries freed for this task
//           1 - library freed for this task
//           2 - library freed and can be freed again (use count > 0) for task
//         < 0 - error
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int  OPERATION
fnSysFreeLibrary( LPTASK lpTask, LPLIBRARY hLibrary, zBOOL bAllUses )
{
   LPLIBRARY  lpPrevSearchLibrary;
   LPLIBRARY  lpSearchLibrary;
   LPLIBRARY  lpLibrary = zGETPTR( hLibrary );
   zLONG      lProcessID;
   HMODULE    hModule;

   // If no AnchorBlock return error.
   if ( AnchorBlock == 0 )
      return( zCALL_ERROR );

   // If task is not active, return error.
   if ( lpTask == 0 )
      return( zCALL_ERROR );

   // Lock critical section so other threads don't muck stuff.
   EnterCriticalSection( &g_csSysLoadLibrary );

   // Find Library passed from caller.
   lProcessID = SysGetProcessID( 0 );
   lpPrevSearchLibrary = 0;
   lpSearchLibrary = zGETPTR( lpTask->hFirstLibrary );
   while ( lpSearchLibrary )
   {
   // TraceLineS( "fnSysFreeLibrary checking library: ",
   //             lpSearchLibrary->szName );
      if ( lpSearchLibrary == lpLibrary || lpLibrary == 0 )
      {
         lpLibrary = lpSearchLibrary;  // ensure non-null library
         break;  // we found the Library record
      }

      lpPrevSearchLibrary = lpSearchLibrary;
      lpSearchLibrary = zGETPTR( lpSearchLibrary->hNextLibrary );
   }

   // Check to see if Library record found for task.
   if ( lpSearchLibrary == 0 )
   {
      LeaveCriticalSection( &g_csSysLoadLibrary );
      return( 0 );  // library already freed for this task
   }

// TraceLine( "Free Library (0x%08x) %s - UseCount: %d   Task 0x%08x",
//            lpLibrary, lpLibrary->szName,
//            lpLibrary ? lpLibrary->ulUseCnt : 0, zGETHNDL( lpTask ) );

   // Decrement the use count.  If the use count is greater than zero, then
   // the module has been loaded multiple times, so don't free it yet.
   if ( lpSearchLibrary->ulUseCnt )
      lpSearchLibrary->ulUseCnt--;

   if ( lpSearchLibrary->ulUseCnt && bAllUses == FALSE )
   {
      LeaveCriticalSection( &g_csSysLoadLibrary );
      return( 2 );  // it is freed and can be freed again for this task
   }

   hModule = (HMODULE) lpLibrary->hLibrary;

   // We have a zero use count for this module, so we want to remove
   // the Library record from the ProcLib Library chain.
   if ( lpPrevSearchLibrary )
      lpPrevSearchLibrary->hNextLibrary = lpLibrary->hNextLibrary;
   else
      lpTask->hFirstLibrary = lpLibrary->hNextLibrary;

   // Environment specific code begins here.

   if ( lpLibrary->lProcessID == lProcessID )
   {
   // fnTraceLibrary( lpLibrary, 0 );
      FreeLibrary( hModule );
   }
   else
   {
      // Send a message to the other process specified by
      // lpLibrary->lProcessID to free the hLibrary.
      zSHORT nProcessIdx;
      LPANCHOROS_RECORD pOS_Record = &AnchorBlock->OS_Data;
      LPPROCESSLIST lpProcessList;

      // Find the process that loaded the library.
      for ( nProcessIdx = (zSHORT) AnchorBlock->OS_Data.lProcessCount - 1;
            pOS_Record->ProcessList[ nProcessIdx ].lProcessID != lProcessID;
            nProcessIdx-- )
      {
         // Nothing needs to be done here.
      }

      if ( nProcessIdx > 0 )
      {
         lpProcessList = &pOS_Record->ProcessList[ nProcessIdx ];
         lpProcessList->nOE_Request  = TASKREQ_FREELIB;
         lpProcessList->hMemHandle   = (zULONG) zGETHNDL( lpLibrary );

         // Send the message.
         SendMessage( (HWND) lpProcessList->hWndAppOE_Msg,
                      lpProcessList->uAppOE_Msg, 0, nProcessIdx );
         TraceLine( "FreeLibrary sent message (0x%08x) for Module: %s - Task: 0x%08x",
                    lpLibrary, lpLibrary->szName, zGETHNDL( lpTask ) );
      }
      else
      {
         TraceLine( "FreeLibrary did not free (0x%08x) Module: %s - Task: 0x%08x",
                    lpLibrary, lpLibrary->szName, zGETHNDL( lpTask ) );
      }

      // Environment specific code ends here.
   }

   fnFreeDataspace( lpLibrary );
   LeaveCriticalSection( &g_csSysLoadLibrary );
   return( 1 );  // this library freed for this task
}

//./ ADD NAME=SysFreeLibrary
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    SysFreeLibrary
//
// PURPOSE:  To free a DLL for a task
//
// RETURNS:  >= 0 - Free OK
//            otw - error
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
int  OPERATION
SysFreeLibrary( zVIEW lpTaskView, LPLIBRARY hLibrary )
{
   LPTASK lpTask = lpTaskView ? zGETPTR( lpTaskView->hTask ) : 0;

   int nRC = fnSysFreeLibrary( lpTask, hLibrary, FALSE );
   if ( nRC > 0 )
      nRC = 0;

   return( nRC );
}

//./ ADD NAME=fnReuseEntity
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    fnReuseEntity
//
// PURPOSE:  To locate a hidden entity and return it if found.
//
// RETURNS:  0  - not found
//          otw - pointer to hidden entity
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zPVOID OPERATION
fnReuseEntity( zPVOID lpViewEntityCsr )
{
   LPENTITYINSTANCE  lpEntityInstance;

   EnterCriticalSection( &g_csReuseEntity );

   lpEntityInstance = zGETPTR( ((LPVIEWENTITYCSR) lpViewEntityCsr)->hEntityInstance );
   while ( lpEntityInstance )
   {
      if ( lpEntityInstance->u.nInd.bHidden )
      {
         lpEntityInstance->u.nInd.bHidden = FALSE;
         LeaveCriticalSection( &g_csReuseEntity );
         return( lpEntityInstance );
      }

      lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );
   }

   LeaveCriticalSection( &g_csReuseEntity );
   return( 0 );
}

//./ ADD NAME=SysReadZeidonIni
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:      SysReadZeidonIni
//
// PURPOSE:    This Operation retrieves a specified parameter in the
//             Zeidon.Ini file.
//
// PARAMETERS: hFile - File handle for reading all parameters in a
//                     Group (see description below).
//             Group - Group name which contains desired parameter
//                     (NOTE: Group names are NOT case sensitive,
//                            [Workstation] is equal to [WORKSTATION])
//             Parameter - Parameter name to be read or NULZ string
//                         when reading all parameters in a Group
//                         (NOTE: Parameter names are NOT case sensitive,
//                                UserID is equal to USERID)
//             Value - Parameter value returned
//
// DESCRIPTION: The ZEIDON.INI file is located in the home directory
//             on the workstation.  When running under MicroSoft
//             Windows, the home directory is the Windows directory
//             containing WIN.COM and WIN.INI.  To retrieve the
//             Windows directory, the System function SysGetLocalDirectory
//             is used.
//
//             A sample ZEIDON.INI file might look like:
//             ....+....1....+....2....+....3....+....4...+....5
//
//             [Zeidon]
//
//             [Workstation]
//             DefaultApp=Zeidon
//             UserID=gkirk
//             Password=zeidon
//
//             [Core]
//             Network=N
//
//             ....+....1....+....2....+....3....+....4...+....5
//             where bracketed items ([Zeidon], [Workstation], and
//             [Core]) are group names and unbracketed items
//             (DefaultApp=Zeidon, etc.) are parameters and values
//             within a group.
//
//
//             SysReadZeidonIni operates in two modes. In the first
//             mode, the caller attempts to read a single parameter
//             in a Group by passing a Group name (including the
//             brackets) and a Parameter Name. An example of a call
//             to read the UserID in the [Workstation] group would be
//
//             SysReadZeidonIni( -1, "[Workstation]", "UserId",
//                               pchReturnString );
//
//             The return string would then contain the value
//             "gkirk" after this call.  NOTE: The file handle
//             should always be passed as -1 in this type of call.
//
//             In the second mode of operation, all parameters in a
//             group may be read by passing a Group name and a null
//             string for the parameter name until a -1 value is returned
//             meaning no more parameters exist in the group.
//
//             In this mode, the parameter name retrieved is returned
//             in the parameter parm after each call.
//
//             An example of a multi-read loop is as follows:
//
//             hFileName = -1;         // Do First Call with invalid file
//             szParameter[ 0 ] = 0;   // Null Parameter for multi read
//             for ( ; ; )             // Loop for awhile
//             {
//                if ( (hFileName = SysReadZeidonIni( hFileName,
//                                     "[Workstation]", szParameter,
//                                     szValue, zsizeof( szValue ) )) == -1 )
//                {
//                   break;   // End of Group Parameter List
//                }
//
//                / ** Process parameter received ** /
//                if ( zstrcmpi( szParameter, "DefaultApp" ) == 0 )
//                {
//                   .
//                   .
//                   .
//                }
//                else
//                if ( zstrcmpi( szParameter, "UserID" ) == 0 )
//                {
//                   .
//                   .
//                   .
//                }
//
//                / * Re-initialize parameter before next read so
//                    SysReadZeidonIni does not look for last
//                    parameter retrieved again!!.              * /
//                szParameter[ 0 ] = 0;
//             }  / ** End Read loop for zeidon.ini group ** /
//
//             NOTE: In the call sequences above, the first call
//                   would return the file handle to Zeidon.ini and
//                   the parameter "DefaultApp" with the value
//                   "Zeidon". The second and third calls would return
//                   the parameters "UserID" and "Password" respectively
//                   and the fourth call would return a file handle of -1
//                   indicating the file was closed and no more parameters
//                   exist in the group.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zLONG  OPERATION
SysReadZeidonIni( zLONG   hFile,
                  zCPCHAR cpcGroup,
                  zPCHAR  pchParameter,
                  zPCHAR  pchValue,
                  zLONG   lMaxLth )
{
   LPTASK lpTask = zGETPTR( AnchorBlock->hMainTask );
   zPVOID pvFile;
   char   szParseName[ 128 ];
   char   szGroup[ 128 ];
   zPCHAR pchLine;   // SysReadLine will allocate the buffer
   zPCHAR pchParseValue;
   zPCHAR pchLineValue;
   int    k;

   // Initialize output value to null.
   pchValue[ 0 ] = 0;

   // If Anchor block doesn't exist, abandon.
   if ( AnchorBlock == 0 || lpTask == 0 )
      return( -1 );

   // Add [] if not supplied.
   if ( cpcGroup[ 0 ] != '[' )
      sprintf_s( szGroup, zsizeof( szGroup ), "[%s]", cpcGroup );
   else
      strcpy_s( szGroup, zsizeof( szGroup ), cpcGroup );

   // If this is not a repeated read, open the file.
   if ( hFile == -1 )
   {
      char szFileName[ zMAX_FILENAME_LTH + 1 ];
      int nTrys = 0;

      fnBuildZeidonIni( szFileName, zsizeof( szFileName ) );
      hFile = fnSysOpenFile( lpTask, szFileName, COREFILE_READ );
      if ( hFile == -1 )
         return( hFile );

      // Find the group to be processed.
      pvFile = 0;
      szParseName[ 0 ] = 0;
      while ( ((k = fnSysReadLine( lpTask, &pchLine, hFile, &pvFile )) == zCALL_ERROR || pchLine == 0) && nTrys < 5 )
      {
         nTrys++;
      }

      if ( k == zCALL_ERROR || pchLine == 0 )
      {
         // Some kind of error ... maybe task not "alive" yet.
         fnSysCloseFile( lpTask, hFile, 0 );
         return( -1 );
      }

      while ( k > 0 && zstrcmpi( szParseName, szGroup ) != 0 )
      {
         SysParseLine( szParseName, zsizeof( szParseName ), &pchParseValue, pchLine );
         k = fnSysReadLine( lpTask, &pchLine, hFile, &pvFile );
      }

      // If the Group was not found, close the file and return.
      if ( k == 0 )
      {
         fnSysCloseFile( lpTask, hFile, 0 );
         pvFile = 0;
         return( -1 );
      }
      else
      if ( k == zCALL_ERROR )
         {
         // Some kind of error ... maybe task not "alive" yet.
         fnSysCloseFile( lpTask, hFile, 0 );
         return(-1);
      }
   }
   else
   {
      // Read the next line if processing an already opened file.
      k = fnSysReadLine( lpTask, &pchLine, hFile, &pvFile );
   }

   // The Group has been located and we have read the first line
   // following the Group identifier, look for the specified parameter.
   while ( k )
   {
      SysParseLine( szParseName, zsizeof( szParseName ), &pchParseValue, pchLine );

      // Remove blanks before Parse Value.
      while ( pchParseValue[ 0 ] == ' ' )
         pchParseValue++;

      // If the parameter name was not delimited by an equal sign '=',
      // search for an equal and bump past it.
      if ( pchParseValue[ 0 ] == '=' )
      {
         pchLineValue = pchLine;

         // Find first non-blank in line.
         while ( pchLineValue[ 0 ] == ' ' )
            pchLineValue++;

         // Find first blank or '=' in line after first non-blank.
         while ( pchLineValue[ 0 ] != ' ' && pchLineValue[ 0 ] != '=' )
            pchLineValue++;

         // If a space occurred after the parameter name and before the
         // '=' sign, then increment pchParseValue after the equal sign.
         if ( pchLineValue[ 0 ] != '=' )
         {
            pchParseValue++;

            // Remove blanks before Parse Value.
            while ( pchParseValue[ 0 ] == ' ' )
               pchParseValue++;
         }
      }

      // If a new group was found, close file and return invalid file.
      if ( szParseName[ 0 ] == '[' )
      {
         fnSysCloseFile( lpTask, hFile, 0 );
         return( -1 );
      }

      // If no parameter was passed and a parameter was found or
      // a parameter was passed and it matches the name found
      // select this parameter to return to the caller.
      if ( (pchParameter[ 0 ] == 0 && szParseName[ 0 ]) ||
           (szParseName[ 0 ] && zstrcmpi( szParseName, pchParameter ) == 0) )
      {
         strcpy_s( pchValue, lMaxLth, pchParseValue );
         if ( pchParameter[ 0 ] == 0 )
            strcpy_s( pchParameter, lMaxLth, szParseName );
         else
         {
            fnSysCloseFile( lpTask, hFile, 0 );
            hFile = -1;
         }

         return( hFile );
      }

      // Get the next line from the zeidon.ini file.
      k = fnSysReadLine( lpTask, &pchLine, hFile, &pvFile );
   }

   // No luck finding the parameter, quit.
   fnSysCloseFile( lpTask, hFile, 0 );
   return( -1 );
}

//./ ADD NAME=SysUpdateZeidonIni
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:       SysUpdateZeidonIni
//
// PURPOSE:     This Operation updates a parameter in a group in the
//              Zeidon Ini file.
//
// PARAMETERS:  Group - The Group to be updated (e.g.  "[Workstation]")
//              Parameter - The Parameter to be updated (e.g.  "UserID")
//              Value - The Value to be set for the parameter
//                      (e.g.  "gkirk")
//
// DESCRIPTION: The Parameter and the Value passed are concatenated
//              together with the character '=' and placed in the
//              group specified by the group parameter.  Note that the
//              group parameter must be placed in brackets
//              (e.g.  "[Workstation]").
//
//              If the group and parameter are found in the file, the
//              parameter is updated.  Otherwise the group is created
//              if necessary and the parameter is added to the group
//              parameter list.  See SysReadZeidonIni above for more
//              information on the zeidon.ini file.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
void  OPERATION
SysUpdateZeidonIni( zCPCHAR cpcGroup,
                    zCPCHAR cpcParameter,
                    zCPCHAR cpcValue )
{
   LPTASK lpTask = zGETPTR( AnchorBlock->hMainTask );
   zPVOID pvFileIn;
   zPVOID pvFileOut;
   char   szParmString[ 2 * (zMAX_FILENAME_LTH  + 1) ];
   char   szFileName[ zMAX_FILENAME_LTH + 1 ];
   char   szFileNameTmp[ zMAX_FILENAME_LTH  + 1 ];
   char   szParseName[ 128 ];
   char   szGroup[ 80 ];
   zPCHAR pchLine;
   zPCHAR pchParseValue;
   zLONG  hFIn;
   zLONG  hFOut;
   int    k;

   // build the parameter to be written into ZEIDON.INI
   sprintf_s( szParmString, zsizeof( szParmString ), "%s=%s", cpcParameter, cpcValue );

   k = fnBuildZeidonIni( szFileName, zsizeof( szFileName ) );
   strcpy_s( szFileNameTmp, zsizeof( szFileNameTmp ), szFileName );
   strcpy_s( szFileNameTmp + k, zsizeof( szFileNameTmp ) - k, "zeidon.in~" );
   hFIn = fnSysOpenFile( lpTask, szFileName, COREFILE_READ );

   // Add [] if not supplied.
   if ( cpcGroup[ 0 ] != '[' )
      sprintf_s( szGroup, zsizeof( szGroup ), "[%s]", cpcGroup );
   else
      strcpy_s( szGroup, zsizeof( szGroup ), cpcGroup );

   // If the file does not exist, create one
   if ( hFIn == -1 )
   {
      pvFileOut = 0;

      hFOut = fnSysOpenFile( lpTask, szFileName, COREFILE_CREATE | COREFILE_WRITELINE_BUFFERED );
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, "[Zeidon]" );
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, "" );
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, "[Encyclopedia]" );
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, "" );
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, "[Workstation]" );
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, "" );
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, "[Object Services]" );
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, "" );
      fnSysCloseFile( lpTask, hFOut, 0 );

      hFIn = fnSysOpenFile( lpTask, szFileName, COREFILE_READ );
   }

   // Perform the Update to the temp file
   if ( hFIn != -1 )
   {
      hFOut = fnSysOpenFile( lpTask, szFileNameTmp,
                             COREFILE_CREATE | COREFILE_WRITELINE_BUFFERED );

      if ( hFOut == -1 )
      {
         fnSysCloseFile( lpTask, hFIn, 0 );
         return;
      }

      pvFileIn = 0;
      pvFileOut = 0;
      szParseName[ 0 ] = 0;
      k = fnSysReadLine( lpTask, &pchLine, hFIn, &pvFileIn );

      while ( k && zstrcmpi( szParseName, szGroup ) != 0 )
      {
         SysParseLine( szParseName, zsizeof( szParseName ), &pchParseValue, pchLine );
         fnSysWriteLine( lpTask, hFOut, &pvFileOut, pchLine );
         k = fnSysReadLine( lpTask, &pchLine, hFIn, &pvFileIn );
      }

      // If the Group was not found, create it.
      if ( k == 0 )
      {
         fnSysWriteLine( lpTask, hFOut, &pvFileOut, "" ); // write blank line
         fnSysWriteLine( lpTask, hFOut, &pvFileOut, szGroup );
      }
      else
      while ( k )
      {
         // Group line has been found and rewritten, search for parameter
         // in the group.
         SysParseLine( szParseName, zsizeof( szParseName ), &pchParseValue, pchLine );
         if ( zstrcmpi( szParseName, cpcParameter ) == 0 )
            break;
         else
         if ( szParseName[ 0 ] == '[' )  // keep an eye out for another group
         {
            fnSysWriteLine( lpTask, hFOut, &pvFileOut, szParmString );  // create new parm
            fnSysWriteLine( lpTask, hFOut, &pvFileOut, "" );            // write blank after parm
            strcpy_s( szParmString, zsizeof( szParmString ), pchLine );    // set string to nxt grp
            break;
         }

         // Don't rewrite blank lines while searching for parameter
         if ( szParseName[ 0 ] )
            fnSysWriteLine( lpTask, hFOut, &pvFileOut, pchLine );

         k = fnSysReadLine( lpTask, &pchLine, hFIn, &pvFileIn );

      } // while ( k )...

      // Add parameter or rewrite next group line depending on the
      // outcome of parameter search above
      fnSysWriteLine( lpTask, hFOut, &pvFileOut, szParmString );
      while ( k > 0 )
      {
         k = fnSysReadLine( lpTask, &pchLine, hFIn, &pvFileIn );
         if ( k )
            fnSysWriteLine( lpTask, hFOut, &pvFileOut, pchLine );
      }

      // Close Zeidon ini file
      fnSysCloseFile( lpTask, hFOut, 0 );
      fnSysCloseFile( lpTask, hFIn, 0 );
   }

   // replace old ZEIDON.INI with updated temp ZEIDON.IN~
   fnSysOpenFile( lpTask, szFileName, COREFILE_DELETE );
   strcpy_s( szParmString, zsizeof( szParmString ), szFileNameTmp );
   strcpy_s( szParmString + zstrlen( szParmString ) + 1, zsizeof( szParmString ) - zstrlen( szParmString ) - 1, szFileName );
   fnSysOpenFile( lpTask, szParmString, COREFILE_RENAME );

} // SysUpdateZeidonIni

void
SfListTasks( void )
{
   PostMessage( (HWND) AnchorBlock->lOE_hMainWnd,
                WM_COMMAND, (WPARAM) IDM_LISTTASKS, (LPARAM) 10000L );
}

//./ ADD NAME=SysMessageBeep
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:       SysMessageBeep
//
// PURPOSE:     Sound the alarm.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void OPERATION
SysMessageBeep( void )
{
   MessageBeep( 0 );       // ring the buzzer...
}

//./ ADD NAME=SysAppendcDirSep
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:       SysAppendcDirSep
//
// PURPOSE:     Append the cDirSep delimiter to the end of a string.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
SysAppendcDirSep( zPCHAR pchString )
{
   zLONG  lLth;

   lLth = zstrlen( pchString );
   if ( lLth > 1 && pchString[ lLth - 1 ] != cDirSep )
   {
      pchString[ lLth++ ] = cDirSep;
      pchString[ lLth ] = 0;
   }

   return( (zSHORT) lLth );
}

//./ ADD NAME=SysValidDirOrFile
/////////////////////////////////////////////////////////////////////////////
//
// This function checks for the existence of the specified file/directory.
// If it is a check for a valid file, that's all we do.  For a directory,
// if the directory does not exist (and bCheckCreate is TRUE) the user
// is given an opportunity to permit the directory to be created.
//
// Note that the full path is returned in pchPath (including drive, etc.)
//
// Return:
//   TRUE  - the directory exists (or was created)
//   FALSE - the directory does not exist or was not specified
//           or could not be created
//
// use zSHORT (compatible with "BOOL") rather than zBOOL
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT OPERATION
SysValidDirOrFile( zPCHAR pchPath,
                   zSHORT bDirectory,
                   zSHORT bCheckCreate,
                   zSHORT nMaxPathLth )
{
   zPCHAR pch;
   zCHAR  szFullPath[ zMAX_FILESPEC_LTH + 1 ];
   DWORD  dwAttr;

// TraceLineS( "Checking dir = ", pchPath );

   if ( pchPath == 0 || *pchPath == 0 )
      return( FALSE );     // no directory was specified

   if ( GetFullPathName( pchPath, nMaxPathLth, szFullPath, &pch ) == 0 )
   {
      // "KZOEE025 - Error in directory specification"
      fnSysMessageBox( 0, "Zeidon Error", "Error in directory specification", 0 );
   // fnIssueCoreError( 0, lpView, 16, 25, 0, pchPath, 0 );
      return( FALSE );
   }

   strncpy_s( pchPath, nMaxPathLth, szFullPath, nMaxPathLth - 1 );
   pchPath[ nMaxPathLth - 1 ] = 0;              // Make sure null-term is there.

   dwAttr = GetFileAttributes( szFullPath );
   if ( dwAttr != -1 )
   {
      // Found a file or directory.  Is this what the user wants?
      if ( bDirectory )
         return( dwAttr & FILE_ATTRIBUTE_DIRECTORY ) != 0;
      else
         return( dwAttr & FILE_ATTRIBUTE_DIRECTORY ) == 0;
   }

   // If we get here then the file/dir doesn't exist.  If the user is looking
   // for a file then just return.
   if ( bDirectory == FALSE )
      return( FALSE );

   // We looked for a directory and it doesn't exist.  If user doesn't want us
   // to create it, return FALSE.
   if ( bCheckCreate == FALSE )
      return( FALSE );

   if ( CreateDirectory( szFullPath, 0 ) ) // created it so let's get out
      return( TRUE );

   // If we get here then there was an error trying to create the directory.
   // Pop up a message.
   // "KZOEE026 - Error creating directory "
   fnSysMessageBox( 0, "Zeidon Error", "Error creating directory", 0 );
// fnIssueCoreError( 0, lpView, 16, 26, 0, szFullPath, 0 );
   return( FALSE );
}

//./ ADD NAME=SysStartHelp
/////////////////////////////////////////////////////////////////////////////
//
// This function starts the operating system's help facility.
//
// Under MS-Windows, the .HLP will be added if it's not in the file name.
//
// HtmlHelp wants to be called differently for starting at the table
// of contents as opposed to in a context-sensitive mode. If pchContextID
// is passed in as a null string, we know to open help at the table of
// contents. Otherwise, we start help in context-sensitive mode.
//
//
// Return:
//   0           - OK.
//   zCALL_ERROR - otherwise
//
/////////////////////////////////////////////////////////////////////////////
zSHORT OPERATION
SysStartHelp( zCPCHAR pchHelpFile,
              zCPCHAR pchContextID )
{
   char  szFileName[ 300 ];
   zLONG lContextID;
   HWND  hwnd;

   if ( zstrcmp( pchHelpFile, "SYSTEM HELP" ) == 0 )
   {
      // Build the file name for the help file.
      strcpy_s( szFileName, zsizeof( szFileName ), "winhelp.hlp" );

      // For calling HelpOnHelp use function Winhelp because there is
      // no compressed Helpfile for this available.
      if ( pchContextID == 0  )
      {
         if ( WinHelp( 0, szFileName, HELP_CONTENTS, 0  ) == 0 )
         {
            return( zCALL_ERROR );
         }
      }
      else
      {
         lContextID = zatol( pchContextID );
         if ( WinHelp( 0, szFileName, HELP_CONTEXT, lContextID  ) == 0 )
         {
            return( zCALL_ERROR );
         }
      }
   }
   else
   {
      // Build the file name for the help file.
      strcpy_s( szFileName, zsizeof( szFileName ), pchHelpFile );
      _strupr_s( szFileName, zsizeof( szFileName ) );
      if ( zstrstr( szFileName, ".CHM" ) == 0 )
         strcat_s( szFileName, zsizeof( szFileName ), ".CHM" );

      strcat_s( szFileName, zsizeof( szFileName ), ">mainwin");

      // If entering help at the table of contents ...
      if ( pchContextID == 0  )
      {
         TraceLineS( "(sy) Starting help with: ", szFileName );
         hwnd = HtmlHelp( GetDesktopWindow( ), (LPCSTR) szFileName, HH_DISPLAY_TOPIC, (DWORD) 0 );
         if ( hwnd == NULL )
         {
            return( zCALL_ERROR );
         }
      }
      // ... otherwise, start context-sensitive help.
      else
      {
         TraceLineS( "(sy) Starting context-sensitive help with: ",
                     szFileName );
         lContextID = zatol( pchContextID );

         HtmlHelp( GetDesktopWindow( ), szFileName, HH_HELP_CONTEXT, lContextID);
         hwnd = HtmlHelp( GetDesktopWindow( ), szFileName, HH_GET_WIN_HANDLE, (DWORD) "MyWindowType" );
         if ( hwnd == NULL )
         {
            return( zCALL_ERROR );
         }
      }
   }

   return( 0 );
} // SysStartHelp

/////////////////////////////////////////////////////////////////////////////
//
// SYSTEM OPERATION: SysSetAnchorBlock
//
// PROTOTYPE:
//
//      void OPERATION
//      SysSetAnchorBlock( void far *AnchorBlock )
//
// PURPOSE:  This system dependent Operation does any Application
//           start-up anchor block processing necessary for the
//           run-time environment.  It is called from
//           RegisterZeidonApplication with the AnchorBlock pointer
//           passed in the register call.
//
//           This function is NOT USED in MicroSoft Windows.
//
//           In OS2/PM the HAB Anchor block must be passed for
//           setting the Application Instance Anchor Block to be
//           used by PM/API functions.
//
// RETURNS:
//
/////////////////////////////////////////////////////////////////////////////
void OPERATION
SysSetAnchorBlock( zPVOID pvAnchorBlock )
{
   // Windows does not require any Anchor Block in RegisterZeidonApplication
}

//./ ADD NAME=SysGetTickCount
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:       SysGetTickCount
//
// PURPOSE:     Returns an OS-dependent timing value.  zTICKS_PER_SECOND
//              represents the number of ticks per second.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zULONG OPERATION
SysGetTickCount( void )
{
   return( (zULONG) GetTickCount( ) );
}

zULONG g_lTable[ 10 ];

zVOID OPERATION
SysStartTimer( zUSHORT idx )
{
   g_lTable[ idx ] = GetTickCount( );
}

zVOID OPERATION
SysElapsedTimer( zUSHORT idx, zPCHAR pchMsg )
{
   zCHAR sz[ 20 ];

   sprintf_s( sz, zsizeof( sz ), " = %lf seconds", (double) (GetTickCount( ) - g_lTable[ idx ]) / zTICKS_PER_SECOND);
   TraceLineS( pchMsg, sz );
}

//./ ADD NAME=SysGetOS_Info
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:       SysGetOS_Info
//
// PURPOSE:     Returns a value indicating the current operating system.
//
// PARAMETERS:  plSubVersion - If not zero the sub-version of the OS will
//                             be returned.  Currently always zero.
//
// RETURNS:     Code indicating current OS.  Valid values are:
//
//                    zOS_WINDOWS                1
//                    zOS_WINDOWS95              2
//                    zOS_WINDOWSNT              3
//                    zOS_OS2                    4
//                    zOS_MVS                    5
//                    zOS_UNIX                   6
//
/////////////////////////////////////////////////////////////////////////////
zLONG OPERATION
SysGetOS_Info( zPLONG plSubVersion )
{
   // For now we just return zero for sub-version.
   if ( plSubVersion )
      *plSubVersion = 0;

   if ( g_bWin95 )
      return( zOS_WINDOWS95 );
   else
      return( zOS_WINDOWSNT );
}

//./ ADD NAME=SysConvertANSI_String
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:       SysConvertANSI_String
//
// PURPOSE:     Translates an ANSI character set string to the OEM
//              character set.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void OPERATION
SysConvertANSI_String( zPCHAR pchAnsiString )
{
}

//./ ADD NAME=SysSendOE_Message
// Source Module=kzoesyaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:   SysSendOE_Message
//
//  PURPOSE: Communicate OE .INI values.  Currently defined requests are:
//    wParam: IDM_GETOEMAINHWND   = 200  lParam: 0  Returns: hWndMain
//    wParam: IDM_GETOELISTHWND   = 201  lParam: 0  Returns: hWndList
//    wParam: IDM_GETTRACELIMIT   = 202  lParam: 0  Returns: lTraceLineLimit
//    wParam: IDM_GETSCROLLTRACE  = 203  lParam: 0  Returns: bScrollTrace
//    wParam: IDM_GETACTIONTRACE  = 204  lParam: 0  Returns: bTraceAction
//    wParam: IDM_GETFINDSTRING   = 205  lParam: pointer to 256-byte buffer
//    wParam: IDM_GETPRINTPREVIEW = 206  lParam: 0  Returns: bPrintPreview
//    wParam: IDM_GETPRINTDIALOG  = 207  lParam: 0  Returns: bPrintDialog
//    wParam: IDM_GETWEBTRACE     = 214  lParam: 0  Returns: bTraceAction
//      into which the find string is copied.      Returns: FindString length
//    wParam: IDM_GETOEWARNINGTRACE = 215 lParam: 0  Returns: bOE_Warning
//    wParam: IDM_GETMEMORYTRACE  = 217 lParam: 0  Returns: bMemoryTrace
//    wParam: IDM_RESETTIMEOUT    = 218 lParam: 0  Returns: 0
//    wParam: IDM_IDLE            = 219 lParam: IdleCnt Returns: 0
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zLONG  OPERATION
SysSendOE_Message( zLONG  wParam,
                   zLONG  lParam )
{
#ifdef __MUTEX_DEBUG__
   // We use 'zMUTEX_COUNT' as an ID for SendMessage.
   fnPrintMutexInfo( 's', zMUTEX_COUNT, __FILE__, __LINE__ );
#endif

   return( SendMessage( (HWND) AnchorBlock->lOE_hMainWnd, WM_COMMAND, wParam, lParam ) );

#ifdef __MUTEX_DEBUG__
   // We use 'zMUTEX_COUNT' as an ID for SendMessage.
   fnPrintMutexInfo( 'S', zMUTEX_COUNT, __FILE__, __LINE__ );
#endif
}

zSHORT OPERATION
SysDescribeZeidonPageTable( zPCHAR pchResults, zLONG lMaxLth )
{
   zSHORT nLth;
   zSHORT nCnt;
   zSHORT k;

   pchResults[ 0 ] = 0;
   nLth = 0;
   nCnt = 0;

   for ( k = 0; k < 256; k++ )
   {
      if ( g_ZeidonPageTable[ k ] == 0 )
         continue;

      nCnt++;
      if ( nLth > 0 )
      {
         pchResults[ nLth++ ] =  ',';
         pchResults[ nLth++ ] =  ' ';
      }

      zltox( k, pchResults + nLth, lMaxLth - nLth );
      nLth += (zSHORT) zstrlen( pchResults + nLth );
   }

// fnPrintMutexInfo( 'S', zMUTEX_COUNT, __FILE__, __LINE__ );
   return( nCnt );
}

// The default decimal operation.  Even though not technically exported,
// we declare it as OPERATION so that its signature matches zDECOPER
// declaration.

zSHORT OPERATION
fnDecimalOperation( void  *pvReturn,
                    void  *pvDecimal,
                    void  *pvInfo,
                    zLONG lControl )
{
   static double g_dNull = -99999999999999.9;

   zLONG  lCommand = lControl & zDEC_CMD;

   switch ( lCommand )
   {
      case zDEC_CMD_INIT:
         TraceLineS( "(ZDecimal) Using default zDecimalOperation( )", "" );
         TraceLineI( "(ZDecimal) Precision (in bits) = ", (zLONG) (sizeof( double ) * 8) );
         return( 0 );

      case zDEC_CMD_ASSIGNDEC:
         // Copy from 1 decimal to another.
         *((double *) pvReturn) = *(double *) pvDecimal;
         return( 0 );

      case zDEC_CMD_ASSIGNNULL:
         // Assign NULL to a decimal.
         *((double *) pvReturn) = g_dNull;
         return( 0 );

      case zDEC_CMD_COMPAREDEC:
         if ( *((double *) pvDecimal) < *(double *) pvInfo )
            return( -1 );
         else
         if ( *((double *) pvDecimal) > *(double *) pvInfo )
            return( 1 );
         else
            return( 0 );

      case zDEC_CMD_COMPARENULL:
         if ( *((double *) pvDecimal) == g_dNull )
            return( 0 );
         else
            return( 1 );

      case zDEC_CMD_COMPAREDOUBLE:
         if ( *((double *) pvDecimal) < (long double) *((double *) pvInfo) )
            return( -1 );
         else
         if ( *((double *) pvDecimal) > (long double) *((double *) pvInfo) )
            return( 1 );
         else
            return( 0 );

      case zDEC_CMD_STRINGTODEC:
         // Convert string to double.
         *(double *) pvReturn = atof( (char *) pvInfo );
         return( 0 );

      case zDEC_CMD_DECTOSTRING:
      {
         short nPrecision = *((short *) pvInfo);

         // Convert double to string.

         if ( nPrecision > 0 )
            sprintf_s( (char *) pvReturn, 256, "%.*f", nPrecision, *((double *) pvDecimal) );
         else
            sprintf_s( (char *) pvReturn, 256, "%f", *((double *) pvDecimal) );

         // sprintf is defined to return a empty string if dDecimal is 0.0.
         if ( *((char *) pvReturn) == 0 )
            strcpy_s( (char *) pvReturn, 256, "0.0" );

         return( 0 );
      }

      case zDEC_CMD_DECTOLONG:
         // Convert double to long.
         *((long *) pvReturn) = (zLONG) *((double *) pvDecimal);
         return( 0 );

      case zDEC_CMD_LONGTODEC:
         *((double *) pvReturn) = (double) *((long *) pvInfo);
         return( 0 );

      case zDEC_CMD_DECTODOUBLE:
         // Convert long double to double.
         *((double *) pvReturn) = (double) *((double *) pvDecimal);
         return( 0 );

      case zDEC_CMD_DOUBLETODEC:
         // Convert double to decimal.
         *((double *) pvReturn) = (double) *((double *) pvInfo);
         return( 0 );

      case zDEC_CMD_MULTDEC:
         *((double *) pvReturn) = *((double *) pvDecimal) * *((double *) pvInfo);
         return( 0 );

      case zDEC_CMD_DIVDEC:
         *((double *) pvReturn) = *((double *) pvDecimal) / *((double *) pvInfo);
         return( 0 );

      case zDEC_CMD_SUBDEC:
         *((double *) pvReturn) = *((double *) pvDecimal) - *((double *) pvInfo);
         return( 0 );

      case zDEC_CMD_ADDDEC:
         *((double *) pvReturn) = *((double *) pvDecimal) + *((double *) pvInfo);
         return( 0 );

      case zDEC_CMD_ROUND:
      {
         zSHORT nPrecision = *((zSHORT *) pvInfo);
         int    iSign = 1;
         zSHORT n;
         double d, d2;

         if ( nPrecision < 0 )
            return( 0 );

         d = *((double *) pvDecimal);
         if ( d == 0.0 )
            return( 0 );

         if ( d < 0.0 )
         {
            d = -d;
            iSign = -1;
         }

         for ( n = 0; n < nPrecision; n++ )
            d += 10;

         d2 = floor( d );
         if ( d - d2 >= 0.5 )
            d2 += 1.0;

         for ( n = 0; n < nPrecision; n++ )
            d2 /= 10;

         d2 = d2 * iSign;
         *((double *) pvDecimal) = d2;

         return( 0 );
      }
   }

   return( -1 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifdef __METERED_SECTION__

zVOID LOCALOPER
fnSysCreateCoreMutex( zLONG lMutex )
{
   if ( g_bServerMode )
   {
      InitializeCriticalSection( &g_ZeidonCritTable[ lMutex ] );
   }
   else
   {
      if ( g_ZeidonMutexTable[ lMutex ] )
      {
         zCHAR szMsg[ 100 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Mutex '%s' already created", g_ZeidonMutexName[ lMutex ] );
         SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
      }
      else
      {
         // Use call in MeterSec.C to create the metered section.
         g_ZeidonMutexTable[ lMutex ] = CreateMeteredSection( 1, 1,
                                                              g_ZeidonMutexName[ lMutex ] );
         if ( g_ZeidonMutexTable[ lMutex ] == 0 )
         {
            zCHAR szMsg[ 100 ];

            sprintf_s( szMsg, zsizeof( szMsg ), "Error creating mutex %s", g_ZeidonMutexName[ lMutex ] );
            SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
         }
      }
   }
}

zVOID LOCALOPER
fnSysDestroyCoreMutex( zLONG  lMutex )
{
   if ( g_bServerMode )
   {
      DeleteCriticalSection( &g_ZeidonCritTable[ lMutex ] );
   }
   else
   {
      if ( g_ZeidonMutexTable[ lMutex ] == 0 )
      {
         zCHAR szMsg[ 100 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Trying to destroy NULL Mutex %s", g_ZeidonMutexName[ lMutex ] );
         SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
         return;
      }

      CloseMeteredSection( g_ZeidonMutexTable[ lMutex ] );
      g_ZeidonMutexTable[ lMutex ] = 0;
   }
}

zVOID LOCALOPER
#ifdef __MUTEX_DEBUG__
fnSysLockCoreMutex( zLONG lMutex, zPCHAR pchFile, zLONG lLine )
#else
fnSysLockCoreMutex( zLONG lMutex )
#endif
{
#ifdef __MUTEX_DEBUG__
   fnPrintMutexInfo( 'l', lMutex, pchFile, lLine );
#endif

   if ( g_bServerMode )
   {
      EnterCriticalSection( &g_ZeidonCritTable[ lMutex ] );
   }
   else
   {
      // We only enter the mutex on the first one.  We'll increment a use
      // count for all the others.
      if ( g_ZeidonMutexLockCnt[ lMutex ] == 0 )
      {
         if ( EnterMeteredSection( g_ZeidonMutexTable[ lMutex ],
                                   MUTEX_TIMEOUT ) == WAIT_TIMEOUT )
         {
            MessageBox( GetActiveWindow( ), "Timeout with Metered Section",
                        szlOE_SystemError,
                        MB_ICONSTOP | MB_OK | MB_TASKMODAL );
         }
      }

      // Bump up use count.
      g_ZeidonMutexLockCnt[ lMutex ]++;
   }

#ifdef __MUTEX_DEBUG__
   fnPrintMutexInfo( 'L', lMutex, pchFile, lLine );
#endif
}

zVOID LOCALOPER
#ifdef( __MUTEX_DEBUG__
fnSysUnlockCoreMutex( zLONG lMutex, zPCHAR pchFile, zLONG lLine )
#else
fnSysUnlockCoreMutex( zLONG lMutex )
#endif
{
#ifdef __MUTEX_DEBUG__
   fnPrintMutexInfo( 'u', lMutex, pchFile, lLine );
#endif

   if ( g_bServerMode )
   {
      LeaveCriticalSection( &g_ZeidonCritTable[ lMutex ] );
   }
   else
   {
      if ( g_ZeidonMutexLockCnt[ lMutex ] == 0 )
      {
         SysMessageBox( 0, szlOE_SystemError, "Mutex not locked!", -1 );
      }
      else
      {
         // We only release the last mutex.
         if ( g_ZeidonMutexLockCnt[ lMutex ] == 1 )
         {
            if ( !LeaveMeteredSection( g_ZeidonMutexTable[ lMutex ], 1, 0 ) )
            {
               zCHAR szMsg[ 100 ];

               sprintf_s( szMsg, zsizeof( szMsg ), "Error releasing mutex %s", g_ZeidonMutexName[ lMutex ] );
               SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
               return;
            }
         }

         // Decrement the use count.
         g_ZeidonMutexLockCnt[ lMutex ]--;
      }
   }

#ifdef __MUTEX_DEBUG__
   fnPrintMutexInfo( 'U', lMutex, pchFile, lLine );
#endif
}

#else  // __METERED_SECTION__

zVOID LOCALOPER
fnSysCreateCoreMutex( zLONG lMutex )
{
   if ( g_bServerMode )
   {
      InitializeCriticalSection( &g_ZeidonCritTable[ lMutex ] );
   }
   else
   {
      if ( g_ZeidonMutexTable[ lMutex ] )
      {
         zCHAR szMsg[ 100 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Mutex '%s' already created", g_ZeidonMutexName[ lMutex ] );
         SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
      }
      else
      {
         g_ZeidonMutexTable[ lMutex ] = CreateMutex( NULL, FALSE, g_ZeidonMutexName[ lMutex ] );

         if ( g_ZeidonMutexTable[ lMutex ] == 0 )
         {
            zCHAR szMsg[ 100 ];

            sprintf_s( szMsg, zsizeof( szMsg ), "Error creating mutex %s", g_ZeidonMutexName[ lMutex ] );
            SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
         }
      }
   }
}

zVOID LOCALOPER
fnSysDestroyCoreMutex( zLONG lMutex )
{
   if ( g_bServerMode )
   {
      DeleteCriticalSection( &g_ZeidonCritTable[ lMutex ] );
   }
   else
   {
      if ( g_ZeidonMutexTable[ lMutex ] == 0 )
      {
         zCHAR szMsg[ 100 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Trying to destroy NULL Mutex %s", g_ZeidonMutexName[ lMutex ] );
         SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
         return;
      }

      if ( !CloseHandle( g_ZeidonMutexTable[ lMutex ] ) )
      {
         zCHAR szMsg[ 100 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Error destroying mutex %s", g_ZeidonMutexName[ lMutex ] );
         SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
         return;
      }

      g_ZeidonMutexTable[ lMutex ] = 0;
   }
}

zVOID LOCALOPER
#ifdef __MUTEX_DEBUG__
fnSysLockCoreMutex( zLONG lMutex, zPCHAR pchFile, zLONG lLine )
#else
fnSysLockCoreMutex( zLONG lMutex )
#endif
{
#ifdef __MUTEX_DEBUG__
   fnPrintMutexInfo( 'l', lMutex, pchFile, lLine );
#endif

   if ( g_bServerMode )
   {
      EnterCriticalSection( &g_ZeidonCritTable[ lMutex ] );
   }
   else
   {
#ifdef __MUTEX_DEBUG__
      DWORD dwRC;
#endif
      if ( g_ZeidonMutexTable[ lMutex ] == 0 )
      {
         zCHAR szMsg[ 100 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Trying to lock NULL Mutex %s", g_ZeidonMutexName[ lMutex ] );
         SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
         return;
      }

#ifdef __MUTEX_DEBUG__
      dwRC = WaitForSingleObject( g_ZeidonMutexTable[ lMutex ], 30000 );
      if ( dwRC == WAIT_FAILED )
      {
         switch ( GetLastError( ) )
         {
            case WAIT_ABANDONED:
               // This means that another thread terminated without unlocking
               // its mutex.  We'll consider this OK.
               break;

            case WAIT_TIMEOUT:
               dwRC /= dwRC - dwRC;
               break;

            default:
               break;
         }
      }
#else
      WaitForSingleObject( g_ZeidonMutexTable[ lMutex ], INFINITE );
#endif
   }

#ifdef __MUTEX_DEBUG__
   fnPrintMutexInfo( 'L', lMutex, pchFile, lLine );
#endif
}

zVOID LOCALOPER
#ifdef __MUTEX_DEBUG__
fnSysUnlockCoreMutex( zLONG lMutex, zPCHAR pchFile, zLONG lLine )
#else
fnSysUnlockCoreMutex( zLONG lMutex )
#endif
{
#ifdef __MUTEX_DEBUG__
   fnPrintMutexInfo( 'u', lMutex, pchFile, lLine );
#endif

   if ( g_bServerMode )
   {
      LeaveCriticalSection( &g_ZeidonCritTable[ lMutex ] );
   }
   else
   if ( g_ZeidonMutexTable[ lMutex ] == 0 )
   {
      zCHAR szMsg[ 100 ];

      sprintf_s( szMsg, zsizeof( szMsg ), "Trying to unlock NULL Mutex %s", g_ZeidonMutexName[ lMutex ] );
      SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
   }
   else
   if ( ReleaseMutex( g_ZeidonMutexTable[ lMutex ] ) == 0 )
   {
      zCHAR szMsg[ 100 ];

      sprintf_s( szMsg, zsizeof( szMsg ), "Error releasing mutex %s", g_ZeidonMutexName[ lMutex ] );
      SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
   }

#ifdef __MUTEX_DEBUG__
   fnPrintMutexInfo( 'U', lMutex, pchFile, lLine );
#endif
}

#endif   // __METERED_SECTION__

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// DG ... I think we can make the mutex code much simpler.  There are two
// kinds of mutex functions in core.  The fnSysXxxxCoreMutex() functions
// are used strictly by core.  I don't think you have to change them.  Their
// info is stored in global tables and they are initialized during DllMain().
//
// The MutexXxxx() functions are for use by the applications.  I'm not sure
// why I didn't give our mutex functions a name starting with "Sys".  It
// might be a good idea to do that.
//
// The easiest thing to do is to make MutexCreate(), MutexLock(), etc. a
// wrapper for Windows mutex functions (CreateMutex, WaitForSingleObject, etc.).
// Windows mutex functions can take a name.  Since all app mutex functions
// also take a name, it's a simple matter of getting the Windows mutex using
// that name.  So the functions would now look something like:
//
// Pretty easy and we don't need to keep track of anything.  The only problem
// with this is when core is running in server mode:  mutexes aren't the most
// efficient way to protect across threads in a single process (they are for
// protecting across processes).  In server mode we only have one process.
//
// On the server we want to use critical sections.  If you look at the
// existing code for fnSysLockCoreMutex() you'll see we check g_bServerMode
// and use critical sections if it is true.  This makes things more difficult
// because we have to store the critical section info somewhere, probably a
// linked list off the AnchorBlock.  Every time someone created a new app
// mutex we'd create a critsec and initialize it.
//
// I'd probably suggest you first implement the Windows mutex functions and
// get that working.  In the future, if more performance is needed (but how
// often do apps use mutexes?) we can add support for critsecs.
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Creates a hash number from a string.  Note that his number will NOT be
// unique for all strings.  The hash is only used to make comparison of
// strings quicker.
zLONG LOCALOPER
fnHashName( zCPCHAR cpcName )
{
   zLONG  nLth = zstrlen( cpcName );
   zLONG  lHash;

   // If the string is long enough we'll skip the first 2 bytes of the string
   // and create a hash value from two long variables.
   if ( nLth >= 2 + 2 * sizeof( zLONG ) )
   {
      lHash = *(zPLONG) &cpcName[ 2 ] +
              // Since all the chars are < 128 (in ASCII anyway) we'll shift
              // the the second long value over 1 bit.
              (*(zPLONG) &cpcName[ 2 + sizeof( zLONG ) ] << 1);

      return( lHash );
   }

   lHash = nLth << (8 * (sizeof( zLONG ) - sizeof( zSHORT )));

   if ( nLth >= sizeof( zLONG ) )
   {
      lHash += *(zPLONG) cpcName;
      return( lHash );
   }

   while ( nLth > 0 )
   {
      ((zPCHAR) &lHash)[ nLth ] += cpcName[ nLth - 1 ];
      nLth--;
   }

   return( lHash );

} // fnHashName

LPMUTEX LOCALOPER
fnMutexFind( LPTASK lpTask, zCPCHAR cpcMutexName )
{
   zLONG   lHash = fnHashName( cpcMutexName );
   LPMUTEX lpMutex;
   zLONG   lProcessID;

   if ( lpTask == 0 )
   {
      SysMessageBox( 0, "MutexFind", "Null task", -1 );
      return( 0 );
   }

   if ( lpTask == (LPTASK) -1 )  // processing system mutex list
   {
      zLOCK_MUTEX( zMUTEX_MUTEX );
      lpMutex = zGETPTR( AnchorBlock->hFirstSysMutex );
      lProcessID = 0;  // system mutexes are "process ignorant"
   }
   else
   {
      lpMutex = zGETPTR( lpTask->hFirstMutex );
      lProcessID = SysGetProcessID( 0 );
   }

   // Try finding the mutex.
   for ( ;
         lpMutex;
         lpMutex = zGETPTR( lpMutex->hNextMutex ) )
   {
      if ( lpMutex->lNameHash != lHash )
         continue;

      // Don't qualify on ProcessID if it is a system mutex.
#if 0
      if ( lProcessID == 0 )  // processing system mutex list
      {
         // We don't care about process ID match.
      }
      else
      {
         // We do care about process ID match.
         if ( lpMutex->lProcessID != lProcessID )
            continue;
      }
#else
      if ( lProcessID && lpMutex->lProcessID != lProcessID )
         continue;
#endif

      if ( zstrcmp( lpMutex->szName, cpcMutexName ) != 0 )
         continue;

      // If we get here we found the right mutex.
      break;
   }

   if ( lpTask == (LPTASK) -1 )
      zUNLOCK_MUTEX( zMUTEX_MUTEX );

   return( lpMutex );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// It looks like we gots to keep track of the handles ourself ... otw
// we get mutex handle leaks!   dks  2004.08.24

// #define TRACE_MUTEX

//
// Application mutex functions.
//
LPMUTEX LOCALOPER
fnMutexCreate( LPTASK lpTask, zCPCHAR cpcMutexName,
               zLONG lControl, zBOOL bSkipSettingMutex )
{
   LPMUTEX lpMutex;
   LPMUTEX hMutex;
   LPMUTEX lpSysMutex;
   LPMUTEX hSysMutex;
   zLONG   lProcessID;

   if ( zstrlen( cpcMutexName ) > zZEIDON_NAME_LTH * 2 )
   {
      // "KZOEE032 - Invalid mutex name"
   // fnIssueCoreError( lpTask, lpView, 16, 32, 0, 0, 0 );
      TraceLineS( "fnMutexCreate Invalid mutex name: ", cpcMutexName );
      return( 0 );
   }

   // Look for the mutex. If it is found just return it.
   lpMutex = fnMutexFind( lpTask, cpcMutexName );
   if ( lpMutex )
      return( lpMutex );

   lProcessID = SysGetProcessID( 0 );

   // If the mutex wasn't found in the task list then try looking for it
   // in the system list.  We put a mutex around it so we only create the
   // system mutex once.
   if ( bSkipSettingMutex == FALSE )
      zLOCK_MUTEX( zMUTEX_MUTEX );

   lpSysMutex = fnMutexFind( (LPTASK) -1, cpcMutexName );
   if ( lpSysMutex == 0 )
   {
      // We need to create the system mutex.
      hSysMutex = fnAllocDataspace( (LPDATAHEADER) g_hAnchorBlock, sizeof( MutexRecord ), 1, 0, iMutex );
      lpSysMutex = zGETPTR( hSysMutex );
      strcpy_s( lpSysMutex->szName, zsizeof( lpSysMutex->szName ), cpcMutexName );
      lpSysMutex->lNameHash = fnHashName( cpcMutexName );
   // lpSysMutex->lProcessID = lProcessID; we don't care what process created the system mutex
      lpSysMutex->lProcessID = 0;

      // Right now, I don't know why we want to create the OS mutex for
      // a "system" mutex ... so let's disable it.  // dks  2006.02.24
   // if ( fnMutexCreateOS( 0, lpSysMutex, lControl ) != 0 )
   // {
   //    if ( bSkipSettingMutex == FALSE )
   //       zUNLOCK_MUTEX( zMUTEX_MUTEX );
   //
   //    fnFreeDataspace( hSysMutex );
   //    return( 0 );
   // }

      lpSysMutex->hNextMutex = AnchorBlock->hFirstSysMutex;
      AnchorBlock->hFirstSysMutex = hSysMutex;
   }
   else
      hSysMutex = zGETHNDL( lpSysMutex );

   // lpMutex must be null, or else we'd be out of here.
   // Create the task mutex.
   hMutex = fnAllocDataspace( lpTask->hFirstDataHeader, sizeof( MutexRecord ), 1, 0, iMutex );
   lpMutex = zGETPTR( hMutex );
   strcpy_s( lpMutex->szName, zsizeof( lpMutex->szName ), cpcMutexName );
   lpMutex->hSysMutex = hSysMutex;
   lpMutex->lNameHash = lpSysMutex->lNameHash;
   lpMutex->lProcessID = lProcessID;

   if ( fnMutexCreateOS( lpTask, lpMutex, lControl ) != 0 )
   {
      if ( bSkipSettingMutex == FALSE )
         zUNLOCK_MUTEX( zMUTEX_MUTEX );

      fnFreeDataspace( hMutex );
      return( 0 );
   }

   lpMutex->hNextMutex = lpTask->hFirstMutex;
   lpTask->hFirstMutex = hMutex;

   if ( bSkipSettingMutex == FALSE )
      zUNLOCK_MUTEX( zMUTEX_MUTEX );

#ifdef TRACE_MUTEX
// if ( zstrcmp( lpMutex->szName, "ZDrSS" ) != 0 )
   TraceLine( "fnMutexCreate  (Created:) Task: 0x%08x   Mutex: 0x%08x  Handle: %d  %s  Process: 0x%08x  SysMutex: 0x%08x",
              zGETHNDL( lpTask ), lpMutex, lpMutex->Info.hMutexOS,
              lpMutex->szName, SysGetProcessID( 0 ), lpMutex->hSysMutex );
#endif

   return( lpMutex );
}

zSHORT LOCALOPER
fnMutexCreateOS( LPTASK lpTask, LPMUTEX lpMutex, zLONG lControl )
{
   lpMutex->Info.bCriticalSection = FALSE;

   lpMutex->Info.hMutexOS = (zLONG) CreateMutex( NULL, FALSE, lpMutex->szName );
   if ( lpMutex->Info.hMutexOS == 0 )
   {
      zCHAR szMsg[ 100 ];
      DWORD dw = GetLastError( );
      sprintf_s( szMsg, zsizeof( szMsg ), "Error creating mutex %s", lpMutex->szName );
      SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
      return( zCALL_ERROR );
   }

   return( 0 );
}

zLONG  OPERATION
SysMutexCreate( zVIEW lpTaskView, zCPCHAR cpcMutexName, zLONG lControl )
{
   LPTASK  lpTask;

   if ( lpTaskView == 0 || (lpTask = zGETPTR( lpTaskView->hTask )) == 0 )
      return( zCALL_ERROR );

   if ( fnMutexCreate( lpTask, cpcMutexName, lControl, FALSE ) == 0 )
      return( zCALL_ERROR );

   return( 0 );

} // SysMutexCreate

//./ ADD NAME=SysMutexLock
// Source Module=kzoesyaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysMutexLock
//
//  PURPOSE:    To lock an application mutex.
//
//  PARAMETERS: lpTaskView   - View to identify the current task
//              cpcMutexName - Name of the mutex.
//              ulTimeout    - Timeout of mutex in milliseconds.
//              ulControl    - Reserved for future use.
//
//  RETURNS:    Number of locks current task had before this call.
//             -1           - Timeout error.
//             zCALL_ERROR  - Error.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT LOCALOPER
fnSysMutexLock( LPTASK lpTask, LPMUTEX lpMutex,
                zULONG ulTimeout, zLONG lControl )
{
   zSHORT nRC = 0;

#ifdef TRACE_MUTEX
// if ( zstrcmp( lpMutex->szName, "ZDrSS" ) != 0 )
   TraceLine( "fnSysMutexLock (WaitLock) Task: 0x%08x   Mutex: 0x%08x  Handle: %d  %s  Process: 0x%08x",
              zGETHNDL( lpTask ), lpMutex, lpMutex->Info.hMutexOS,
              lpMutex->szName, SysGetProcessID( 0 ) );
#endif
   if ( ulTimeout == 0 )
      ulTimeout = INFINITE;

   if ( WaitForSingleObject( (HANDLE) lpMutex->Info.hMutexOS, ulTimeout ) == WAIT_FAILED )
   {
      switch ( GetLastError( ) )
      {
         case WAIT_ABANDONED:
            // This means that another thread terminated without unlocking
            // its mutex.  We'll consider this OK.
            nRC = 1;
            break;

         case WAIT_TIMEOUT:
            nRC = -1;
            break;

         default:
            nRC = zCALL_ERROR;
            break;
      }
   }

#ifdef TRACE_MUTEX
// if ( zstrcmp( lpMutex->szName, "ZDrSS" ) != 0 )
   TraceLine( "fnSysMutexLock (Acquired) Task: 0x%08x   Mutex: 0x%08x  Handle: %d  %s  Process: 0x%08x   RC: %d",
              zGETHNDL( lpTask ), lpMutex, lpMutex->Info.hMutexOS,
              lpMutex->szName, SysGetProcessID( 0 ), nRC );
#endif

   if ( nRC == 1 )
      nRC = 0;

   return( nRC );
}

zSHORT OPERATION
SysMutexLock( zVIEW   lpTaskView,
              zCPCHAR cpcMutexName,
              zULONG  ulTimeout,
              zLONG   lControl )
{
   LPTASK  lpTask;
   LPMUTEX lpMutex;
   zSHORT  nRC;

   if ( lpTaskView == 0 || (lpTask = zGETPTR( lpTaskView->hTask )) == 0 )
      return( zCALL_ERROR );

   // If the mutex hasn't been created yet, try to create it.
   lpMutex = fnMutexCreate( lpTask, cpcMutexName, lControl, 0 );
   if ( lpMutex == 0 )
      return( zCALL_ERROR );

   // Check to see if the mutex is already locked for this task.
   if ( lpMutex->nLockCount )
      return( lpMutex->nLockCount++ );

   lpMutex->bWaiting = TRUE;

   nRC = fnSysMutexLock( lpTask, lpMutex, ulTimeout, lControl );

   lpMutex->bWaiting = FALSE;

   if ( nRC == 0 )
   {
      LPMUTEX lpSysMutex = zGETPTR( lpMutex->hSysMutex );

      lpSysMutex->lLockedTaskID = GetCurrentProcessId( );
      return( ++lpMutex->nLockCount );  // pre-increment intended
   }
   else
   {
      TraceLineS( "(tm) Error trying to lock mutex ", cpcMutexName );
      SysMessageBox( lpTaskView, "Error", "Error locking mutex", 0 );
      nRC /= nRC - nRC;

      return( zCALL_ERROR );
   }

} // SysMutexLock

//./ ADD NAME=SysMutexUnlock
// Source Module=kzoesyaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysMutexUnlock
//
//  PURPOSE:    To unlock an application mutex.
//
//  PARAMETERS: lpTaskView   - View to identify the current task
//              cpcMutexName - Name of the mutex.
//              ulControl    - Reserved for future use.
//
//  RETURNS:    Number of locks still held by current task.
//             -1           - Mutex wasn't locked.
//             zCALL_ERROR  - Error.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT LOCALOPER
fnSysMutexUnlock( LPTASK lpTask, LPMUTEX lpMutex )
{
#if 0
   if ( lpMutex->Info.bCriticalSection )
   {
      // If the current mutex is for a thread task, then lpParentMutex will
      // point to the mutex structure for the parent task.  We want to use
      // the parent mutex to leave the critical section.
      if ( lpMutex->Info.hParentMutex )
         lpMutex = zGETPTR( lpMutex->Info.hParentMutex );

      LeaveCriticalSection( (LPCRITICAL_SECTION) lpMutex->Info.CritSection );
   }
   else
#endif
   {
      if ( ReleaseMutex( (HANDLE) lpMutex->Info.hMutexOS ) == 0 )
      {
         zCHAR szMsg[ 100 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Error releasing mutex %s", lpMutex->szName );
         TraceLineS( szMsg, "" );
         SysMessageBox( 0, szlOE_SystemError, szMsg, -1 );
         return( zCALL_ERROR );
      }
   }

#ifdef TRACE_MUTEX
// if ( zstrcmp( lpMutex->szName, "ZDrSS" ) != 0 )
   TraceLine( "fnSysMutexUnlock (Unlock) Task: 0x%08x   Mutex: 0x%08x  Handle: %d  %s  Process: 0x%08x",
              zGETHNDL( lpTask ), lpMutex, lpMutex->Info.hMutexOS,
              lpMutex->szName, SysGetProcessID( 0 ) );
#endif

   return( 0 );
}

zSHORT OPERATION
SysMutexUnlock( zVIEW lpTaskView, zCPCHAR cpcMutexName, zLONG lControl )
{
   LPTASK  lpTask;
   LPMUTEX lpMutex;
   LPMUTEX lpSysMutex;

   if ( lpTaskView == 0 || (lpTask = zGETPTR( lpTaskView->hTask )) == 0 )
      return( zCALL_ERROR );

   if ( (lpMutex = fnMutexFind( lpTask, cpcMutexName )) == 0 )
      return( zCALL_ERROR );

   if ( lpMutex->nLockCount == 0 )
      return( -1 );

   if ( lpMutex->nLockCount > 1 )
      return( --lpMutex->nLockCount );  // pre-decrement intended

   // We'll reset the lLockedTaskID even though we haven't actually locked
   // it yet.  This protects us from having two tasks change the ID at the
   // same time.
   lpSysMutex = zGETPTR( lpMutex->hSysMutex );
   lpSysMutex->lLockedTaskID = 0;

   if ( fnSysMutexUnlock( lpTask, lpMutex ) != 0 )
      return( zCALL_ERROR );

   lpMutex->nLockCount = 0;
   return( 0 );

} // SysMutexUnlock

zLONG  OPERATION
SysMutexClose( zLONG hMutexOS )
{
   return( CloseHandle( (HANDLE) hMutexOS ) );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zSHORT LOCALOPER
fnSysMutexDestroy( LPTASK lpTask, LPMUTEX lpMutex )
{
   zLONG lProcessID = SysGetProcessID( 0 );
#ifdef TRACE_MUTEX
   TraceLine( "fnSysMutexDestroy Task: 0x%08x  Handle: %d  %s  Mutex ProcessID %d   ProcessID %d",
              zGETHNDL( lpTask ), lpMutex ? lpMutex->Info.hMutexOS : 0, lpMutex ? lpMutex->szName : "",
              lpMutex->lProcessID, lProcessID );
#endif

// if ( lpTask == 0 || lpMutex == 0 || lpMutex->Info.hMutexOS == 0 )
//    return( 0 );


   // If lpTask is zero, we are destroying a system mutex ... which does
   // not have a valid mutex handle, so skip this part of the destroy.
   if ( lpTask && lpMutex->lProcessID != lProcessID )
   {
      // Send a message to the other process specified by
      // lpMutex->lProcessID to free the mutex.
      zSHORT nProcessIdx;
      LPANCHOROS_RECORD pOS_Record = &AnchorBlock->OS_Data;
      LPPROCESSLIST lpProcessList;

      // Find the process that created the mutex.
      for ( nProcessIdx = (zSHORT) AnchorBlock->OS_Data.lProcessCount - 1;
            pOS_Record->ProcessList[ nProcessIdx ].lProcessID != lProcessID;
            nProcessIdx-- )
      {
         // Nothing needs to be done here.
      }

      if ( nProcessIdx > 0 )
      {
         lpProcessList = &pOS_Record->ProcessList[ nProcessIdx ];
         lpProcessList->nOE_Request  = TASKREQ_FREEMUTEX;
         lpProcessList->hMemHandle   = (zULONG) zGETHNDL( lpMutex );

         // Send the message.
         SendMessage( (HWND) lpProcessList->hWndAppOE_Msg,
                      lpProcessList->uAppOE_Msg, 0, nProcessIdx );
      }

      return( 0 );
   }

   if ( lpMutex->Info.hMutexOS )
   {
      // We don't need to do the following code since the "System Mutex" is
      // only used to track the lLockedTaskID.  The Info.hMutexOS should not
      // be set for the system mutexes.
   // if ( lpTask )
   // {
   //    LPMUTEX lpSysMutex = fnMutexFind( (LPTASK) -1, lpMutex->szName );
   //    if ( lpSysMutex && lpSysMutex->Info.hMutexOS == lpMutex->Info.hMutexOS )
   //       lpSysMutex->Info.hMutexOS = 0;
   // }

      if ( CloseHandle( (HANDLE) lpMutex->Info.hMutexOS ) == 0 )
      {
         char szMsg[ 100 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Error destroying mutex: %s", lpMutex->szName );
         TraceLineS( szMsg, "" );
         fnSysMessageBox( lpTask, szlOE_SystemError, szMsg, 1 );
         return( zCALL_ERROR );
      }

      lpMutex->Info.hMutexOS = 0;
   }

   return( 0 );
}

//./ ADD NAME=SysMutexQueryLock
// Source Module=kzoesyaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysMutexQueryLock
//
//  PURPOSE:    Checks if a mutex is locked for the system task ONLY.
//
//  PARAMETERS: cpcMutexName - Name of the mutex.
//
//  RETURNS:    Number of times mutex is concurrently locked by the
//                 current task.
//              zCALL_ERROR  - Mutex not created.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
SysMutexQueryLock( zCPCHAR cpcMutexName )
{
   LPMUTEX lpMutex;
   LPTASK  lpTask = zGETPTR( AnchorBlock->hFirstTask );
   zSHORT  nLockCount = 0;

   while ( lpTask )
   {
      lpMutex = fnMutexFind( lpTask, cpcMutexName );
      if ( lpMutex )
         nLockCount += lpMutex->nLockCount;

      lpTask = zGETPTR( lpTask->hNextTask );
   }

   return( nLockCount );

} // SysMutexQueryLock

//./ ADD NAME=SysMutexQueryStatus
// Source Module=kzoesyaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SysMutexQueryStatus
//
//  PURPOSE:    Traces out status of locks.  Note that this function is NOT
//              protected by mutexes and could display erroneous information.
//
//  PARAMETERS: none
//
//  RETURNS:    0 - OK.
//              zCALL_ERROR
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
SysMutexQueryStatus( )
{
   zCHAR   szMsg[ 1000 ];
   LPMUTEX lpMutex;
   LPTASK  lpTask = zGETPTR( AnchorBlock->hFirstTask );
   DWORD   dwRC;
   zSHORT  k;

   TraceLineS( " ---- MUTEX LIST ---- ", "" );

   for ( k = 0; k < zMUTEX_COUNT; k++ )
   {
      TraceLine( "MutexQueryStatus %s -- Checking ...", g_ZeidonMutexName[ k ] );
      dwRC = WaitForSingleObject( g_ZeidonMutexTable[ k ], 2000 );
      if ( dwRC == WAIT_FAILED )
      {
         switch ( GetLastError( ) )
         {
            case WAIT_ABANDONED:
               // This means that another thread terminated without unlocking
               // its mutex.  We'll consider this OK.
               dwRC = 0;
               break;

            case WAIT_TIMEOUT:
               dwRC = 1;
               break;

            default:
               dwRC = 2;
               break;
         }
      }
      else
         dwRC = 0;

      if ( dwRC )
      {
         TraceLine( "MutexQueryStatus %s -- FAILED (%d)", g_ZeidonMutexName[ k ], dwRC );
      }
      else
      {
         ReleaseMutex( g_ZeidonMutexTable[ k ] );
         TraceLine( "MutexQueryStatus %s -- OK", g_ZeidonMutexName[ k ] );
      }
   }

   if ( lpTask == 0 )
      return( zCALL_ERROR );

   // Set lock to make sure nobody's changing the mutex chains.
   zLOCK_MUTEX( zMUTEX_MUTEX );

   for ( lpMutex = zGETPTR( AnchorBlock->hFirstSysMutex );
         lpMutex;
         lpMutex = zGETPTR( lpMutex->hNextMutex ) )
   {
      if ( lpMutex->lLockedTaskID )
      {
         sprintf_s( szMsg, zsizeof( szMsg ), "Mutex '%s' locked by Task: %d    ProcessID: %d",
                   lpMutex->szName, lpMutex->lLockedTaskID, lpMutex->lProcessID );
      }
      else
      {
         sprintf_s( szMsg, zsizeof( szMsg ), "Mutex '%s' is unlocked     ProcessID: %d",
                   lpMutex->szName, lpMutex->lProcessID );
      }

      TraceLineS( szMsg, "" );
   }

   fnStartBrowseOfTaskList( zGETHNDL( lpTask ), FALSE );

   for ( lpTask = zGETPTR( AnchorBlock->hFirstTask );
         lpTask;
         lpTask = zGETPTR( lpTask->hNextTask ) )
   {
      for ( lpMutex = zGETPTR( lpTask->hFirstMutex );
            lpMutex;
            lpMutex = zGETPTR( lpMutex->hNextMutex ) )
      {
         // We only care about tasks waiting for a mutex.
         if ( lpMutex->bWaiting == FALSE )
            continue;

         sprintf_s( szMsg, zsizeof( szMsg ), "Task 0x%08x (process id:%d) is waiting on mutex '%s'     Lock Count: %d",
                   (zULONG) lpTask, lpMutex->lProcessID, lpMutex->szName, SysMutexQueryLock( lpMutex->szName ) );
      }
   }

   fnEndBrowseOfTaskList( FALSE );

   zUNLOCK_MUTEX( zMUTEX_MUTEX );

   return( 0 );

} // SysMutexQueryStatus

zSHORT OPERATION
SysStartBrowseOfTaskList( zVIEW lpTaskView )
{
   return( fnStartBrowseOfTaskList( lpTaskView->hTask, FALSE ) );
}

void OPERATION
SysEndBrowseOfTaskList( )
{
   fnEndBrowseOfTaskList( FALSE );
}

zUSHORT OPERATION
SysGetClientMessage( )
{
   if ( g_wClientMessage == 0 )
      g_wClientMessage = RegisterWindowMessage( "KZOESYAA" );

   return( g_wClientMessage );
}

zULONG OPERATION
SysGetRandomLong()
{
   zULONG x = rand() & 0xff;
   x |= (rand() & 0xff) << 8;
   x |= (rand() & 0xff) << 16;
   x |= (rand() & 0xff) << 24;
   return x;
}

/////////////////////////////////////////////////////////////////////////////
//
// DLLs, Processes, and Threads Technical Articles
// Multiple Threads in the User Interface
//
// Nancy Winnick Cluts
// Microsoft Developer Network Technology Group
//
// Created: November 24, 1993
//
// Abstract --
// The Microsoft® Win32® Application Programming Interface (API) has given us
// the ability to use multiple threads within applications. Many programmers
// for Microsoft Windows® are now looking for ways to add threads to their
// applications. Although there are some excellent reasons to add threads to
// an application, there are also times when threads are unnecessary and will
// only add to the complexity of a program. In this technical article, I will
// explain the ramifications of adding multiple threads to the user interface,
// including the following:
//
//  - Why and where (and why not and where not) to use multiple threads
//  - The cost of adding multiple threads to the user interface
//  - How threads affect message routing
//  - How multiple user-interface threads affect window management
//  - Alternatives to multiple threads
//  - How to avoid message deadlocking
//  - New functions for handling multiple threads
//
// Introduction --
// So you already have an application written for Microsoft® Windows® version
// 3.1 that you have decided to port to Windows NT®. Since Windows NT has these
// new things called threads that are supposed to make applications faster,
// you're interested in putting these in your application. The first thing you
// do is look up the functions that you need to create and use threads, and you
// jump right in, adding threads to all of the "slow" areas in your application
// and creating a thread for each new window that you create. After you finally
// get your application to build (passing NULL as a parameter every time you
// were asked for a security descriptor), you find to your utter horror that
// not only is your application not faster, but it doesn't work correctly
// anymore! At this point you begin to wonder if threads are such a great idea
// after all.
//
// Perhaps the problem isn't with the threads, but with where you have decided
// to add your threads. When threads are used and placed correctly in an
// application, you can gain some excellent benefits in speed, but when they
// are placed inappropriately, you may well end up with a complex application
// that is no faster than it was originally and much harder to debug.
//
// Why Use Multiple Threads in the User Interface? --
// When you think of multithreading, some tasks immediately come to mind, such
// as data calculations, database queries, and input gathering. These
// activities, most often thought of as "background" tasks, do not directly
// involve the user interface or window management. Does this mean that there
// are no places that you can incorporate threads in your user interface?
// Certainly not. In general, if there are places in your application that do
// not need to be serialized, you can add threads. For instance, it does not
// make sense to distribute input to threads because all input is implicitly
// serialized by USER. It also does not make sense to distribute output to
// threads because output devices, such as a printer, are inherently
// single-threaded.
//
// Where? --
// Let's say you have an application that creates one window that displays
// current stock quotes and another window that allows you to enter requests
// for buying or selling stock. Within your application, you have two discrete
// tasks to complete that do not depend upon one another for information: (1)
// Displaying current stock quotes and (2) Placing a buy or sell order. These
// tasks do not affect each other in any way. One way to improve the performance
// of your application would be to create a thread for each window, thereby
// creating a more modular application.
//
// Another situation in which multiple threads would benefit the user interface
// would be in an application in which one window displays a spinning cube and
// another window receives input from the user on how fast to spin the cube, the
// coordinates of the cube, and its angle. (Since we're just dreaming this up,
// let's make it three-dimensional.) You can fairly cleanly break down the tasks
// each window needs to complete - one window displays the spinning cube while the
// other window is gathering input. The big difference between this example and
// the previous one is that here you need to have one thread communicate some
// information (the new speed, coordinates, or angle) to the other thread. The
// first thread can continue to display the cube while the second thread is
// gathering new input. In other words, you use one thread for input and one
// for output.
//
// Where Not? --
// Because I like to be as evenhanded as possible, let me give you a couple of
// examples of situations in which multiple threads would be a detriment to the
// user interface. Let's say you have an application that relies upon getting
// some type of input before it can continue processing, such as a dialog box
// that accepts logon information. Would it be a good idea to create a thread
// to gather that input? Probably not. If you are creating a thread to accomplish
// something that needs to be synchronous, you are making things needlessly
// complex for almost no benefit, plus there are costs to adding threads, which
// I will discuss in the next section.
//
// Another poor multithreading candidate is creating a thread for a nonreentrant
// window or dialog box. If this window has some global data, and if another thread
// calls it more than once, your global data can become corrupted. You can work
// around this problem by ensuring that you keep your data on a per-thread basis
// rather than a per-process basis. For example, let's say you have a dialog box
// that you use to open a file, but the data you keep in the thread for the pointer
// to file or the filename is kept in global data, rather than per-thread data. In
// this case, if the dialog box is called twice, the pointer and the filename will
// become corrupted and, when you try to access the file via the pointer in the
// first thread, you will be accessing the wrong file. This is not the functionality
// you want. Bear in mind that this situation is not specifically a USER issue - it
// is a general Windows NT multithreading issue. In any Windows NT-based application,
// you need to take care with data that you use on a per-thread basis.
//
// Costs of Creating Threads --
// Just as there is no such thing as a free lunch, there is also no such thing as
// a free thread. Before creating threads, you must keep the costs in mind. In
// many cases, you may find that the cost is low compared to the benefit. The
// following list enumerates some of the costs incurred when creating multiple
// threads in your process.
//
// Memory is needed for the structures required by threads.
// An application that has a large number of threads consumes extra CPU time in
// keeping track of those threads.
// An application is responsible for synchronizing access to shared resources by
// multiple threads. This is true for system resources (such as communications
// ports or disk drives), handles to resources shared by multiple processes (such
// as file or pipe handles), or the resources of a single process (such as global
// variables accessed by multiple threads). If you don't synchronize multiple
// threads properly (in the same or in different processes), you can run into
// some nasty problems, including the dreaded deadlock and race conditions.
// Because all threads of a process share the same address space and can access
// the process's global variables, an application must also synchronize access to
// these global variables. This means that the developer must decide what data can
// be process-specific and what data is thread-specific.
//
// How Multiple Threads Affect Window Management --
// A Windows NT-based application can have multiple threads of execution, and each
// thread can create windows by calling the CreateWindow function. An application
// must remove and process messages posted to the message queues of its threads. A
// single-threaded application uses a message loop in its WinMain function to
// remove and send messages to the appropriate window procedures for processing.
//
// Changes to the Message Loop --
// Applications with multiple threads must include a message loop in each thread
// that creates a window. The message loop and window procedure for a window must
// be processed by the thread that created the window. If the message loop does not
// reside in the same thread that created the window, the DispatchMessage function
// will not get messages for the window. As a result, the window will appear but
// won't show activation and won't repaint, be moved, receive mouse messages, or
// generally work as you expect it to.
//
// Enumerating Your Thread's Windows --
// If you have a need in your application to affect all of the windows created by
// a particular thread, you can use the new EnumThreadWindows function to enumerate
// the windows created by a particular thread. For example, let's say you have an
// application that displays all movie times for a movie theater in a window and
// creates a window for each theater. The windows created are dependent on the general
// location the user entered, and you spin off a thread to create all of the windows
// for the theaters for that location. When the user refines the search to a smaller
// area, you may want to enumerate the windows in your thread to determine whether
// or not you need to close down one of the windows containing information about
// theaters outside of the specified area. This saves you from having to search for
// information you have already displayed.
//
// The EnumThreadWindows function is much like the EnumChildWindows function in
// that the application developer can specify enumeration of the windows and provide
// a callback function to effect the necessary changes. This function passes the
// handle of each thread's window, in turn, to an application-defined callback
// function. The GetWindowThreadProcessId function returns the identifier of the
// thread that created a particular window.
//
// Finding a Window; or, Am I Here Yet? --
// Another common window management job that is affected by multiple threads is
// determining whether or not a previous instance of the application is already
// running. A common method used by applications to determine whether or not their
// application has started is to use the FindWindow function specifying the class
// and window name. If FindWindow returns NULL, the application assumes that it has
// not been started already. Unfortunately, this is not an entirely reliable method.
// It is possible for a second instance of an application to be started and to
// execute the FindWindow call before the first instance has created its window.
//
// An alternative method for determining whether an instance of your application
// is running is to use any named object (mutex, semaphore, event, named shared
// memory). That is, when you start your application, check for a particular named
// semaphore (the name is your choice, so be creative) and, if the semaphore does
// not exist, go about starting up your application as usual; if the semaphore does
// exist, task-switch to your application. The following example is a function that
// checks to see if a unique semaphore was already created. If the semaphore exists,
// the function calls FindWindow to find the application, and sets that window to
// foreground. If it does not exist, the function returns FALSE. The function uses
// the CreateSemaphore function to illustrate a named-object creation operation
// that fails if the object already exists.
//
// BOOL DoIExist(LPSTR lpszSemName, LPSTR lpszClassName, LPSTR lpszWindowTitle)
// {
//
//     HANDLE hSem;
//     HWND hWndMe;
//
//     /* Create or open a named semaphore. */
//     hSem = CreateSemaphore(
//         NULL,         /* Security attributes */
//         0,            /* Initial count       */
//         1,            /* Maximum count       */
//         lpszSemName); /* Semaphore name      */
//
//     /* Close handle, and return NULL if existing semaphore opened. */
//     if (hSem != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
//     {
//         CloseHandle(hSem);
//         hWndMe = FindWindow(lpszClassName, lpszWindowName);
//         if (hWndMe)
//             SetForegroundWindow(hWndMe);
//         return TRUE;
//     }
//
//     /* If new semaphore was created, return FALSE. */
//     return FALSE;
// }
//
// The Effects of Multiple Threads on Message Routing --
// Windows uses two methods to route messages to a window procedure: (1) posting
// messages to a first-in, first-out queue called a message queue, which is a
// system-defined memory object that temporarily stores messages; and (2) sending
// messages directly to a window procedure. Messages posted to a message queue
// are called queued messages. They are primarily the result of user input via
// the mouse or keyboard, such as WM_MOUSEMOVE, WM_LBUTTONDOWN, WM_KEYDOWN, and
// WM_CHAR messages. Other queued messages include the timer, paint, and quit
// messages: WM_TIMER, WM_PAINT, and WM_QUIT. Most other messages are sent directly
// to a window procedure and are called, surprisingly enough, nonqueued messages.
//
// Queued Messages --
// Windows NT maintains a single system-message queue and any number of
// thread-message queues, one for each thread. Whenever the user moves the
// mouse, clicks the mouse buttons, or types at the keyboard, the device
// driver for the mouse or keyboard converts the input into messages and
// places them in the system-message queue. Windows removes the messages,
// one at a time, from the system-message queue, examines them to determine
// the destination window, and then posts them to the message queue of the
// thread that created the destination window. A thread's message queue
// receives all mouse and keyboard messages for the windows created by the
// thread. The thread removes messages from its queue and directs Windows
// NT to send them to the appropriate window procedure for processing. The
// system posts a message to a thread's message queue by filling an MSG
// structure and then copying it to the message queue. Information in the
// MSG structure includes the handle of the window for which the message
// is intended, the message identifier, the two message parameters, the
// message time, and the mouse-cursor position. A thread can post a message
// to its own message queue or to the queue of another thread by using the
// PostMessage or PostThreadMessage function.
//
// Nonqueued Messages --
// Nonqueued messages are sent immediately to the destination window procedure,
// bypassing the system-message queue and thread-message queue. Windows
// typically sends nonqueued messages to notify a window of events that
// affect it. For example, when the user activates a new application window,
// Windows sends the window a series of messages, including WM_ACTIVATE,
// WM_SETFOCUS, and WM_SETCURSOR. These messages notify the window that it
// has been activated, that keyboard input is being directed to the window,
// and that the mouse cursor has been moved within the borders of the window.
// Certain Windows function calls can prompt nonqueued messages. For example,
// Windows sends the WM_WINDOWPOSCHANGED message after an application uses the
// SetWindowPos function to move a window.
//
// Window Focus and Activation Considerations --
// The addition of multiple windows owned by multiple threads in the system
// has brought to the forefront some changes in the concept of focus and
// activation in the system. These changes affect all applications regardless
// of whether the application is single- or multithreaded. Remember that each
// application runs in its own process and when that new process is created,
// a thread is created for that process. Each thread has its own input state
// that is not shared, by default, with other threads. As a result, when this
// new process creates its first window, that window will belong to a different
// thread from any other window in the system. This "separate thread" concept
// rears its ugly head if your application tries to set the input focus to
// another application. Because the windows were created in different threads,
// the call to SetFocus will fail. I will describe a way around this problem
// and, since we all know that ignorance is not bliss when programming for
// Windows, I will detail the three concepts of focus, activation, and
// foreground and background windows in Win32®.
//
//
// Figure 1. The focus window, MDI 3
//
// The Focus Window --
// Windows NT posts keyboard messages to the message queue of the thread that
// created the window with the keyboard focus. The keyboard focus is a temporary
// property of a window. Windows shares the keyboard among all windows on the
// display by shifting the keyboard focus, at the user's direction, from one
// window to another. The window that has the keyboard focus receives (from the
// message queue of the thread that created it) all keyboard messages until the
// focus changes to a different window. A thread can call the GetFocus function
// to determine which of its windows (if any) currently has the keyboard focus.
// A thread can give the keyboard focus to one of its windows by calling the
// SetFocus function. When the keyboard focus changes from one window to another,
// the system sends a WM_KILLFOCUS message to the window that has lost the focus,
// and then sends a WM_SETFOCUS message to the window that has gained the focus.
// In Figure 1, the focus window is the window entitled "MDI 3."
//
// The Active Window --
// The concept of an active window is probably old hat to many of you reading
// this article, but I am including the information in the spirit of being
// complete. The concept of keyboard focus is related to that of the active
// window. The active window is the top-level window the user is currently
// working with. The window with the keyboard focus is either the active
// window itself or a child window of the active window. So that the user
// can easily identify the active window, the system places it at the top
// of the z-order and highlights its title bar (if it has one) and border.
// The user can activate a top-level window by clicking it, by selecting it
// using the ALT+TAB or ALT+ESC key combination, or by selecting it from the
// Task List. A thread can activate a top-level window by using the
// SetActiveWindow function. It can determine whether a top-level window it
// created is active by using the GetActiveWindow function.
//
// In Figure 1, the active window is the window entitled "MDI Demonstration."
// You might think that the "MDI 3" window was the active one, but remember,
// the active window is always a top-level window and the focus window can
// be either the active window or a child of the active window. Thus, in this
// case, the focus window is "MDI 3" and the active window is its parent,
// "MDI Demonstration."
//
// When one window is deactivated and another activated, Windows sends the
// WM_ACTIVATE message first to the window being deactivated and then to the
// window being activated. The low-order word of the wParam parameter is zero
// if the window is being deactivated and nonzero if it is being activated.
// When the default window procedure receives the WM_ACTIVATE message, it sets
// the keyboard focus to the active window.
//
// Let's say you try to set the focus to a window that resides in another thread
// by using SetFocus without calling AttachThreadInput. The call will fail,
// right? Right. But then what happens to the focus and activation states? I'm
// glad you asked.
//
// One window can have the focus while another window is active.
// A situation can arise in Windows NT when one window has the input focus while
// another window is active. This mainly occurs when a console window attempts
// to set the focus via SetFocus to a GUI window, and the call to SetFocus fails.
// When this happens, the console window has lost the keyboard focus, but still
// remains the active window. The window that gains the focus is dependent on
// which window in the z-order was next to get the focus. When this happens,
// the user cannot figure out why the proper window is no longer getting the
// keyboard input he or she is typing in. Luckily, the person running the software
// will usually have the presence of mind to click the mouse over the window he
// or she wants to have the input focus, and the focus will then be set to the
// correct window. To avoid this problem, call SetForegroundWindow, rather than
// SetFocus, to reset the focus between unattached windows created in different
// threads.
//
// Foreground and Background Windows --
// In Windows NT, each process can have multiple threads of execution, and as we
// saw before, each thread can create windows. The thread that created the window
// with which the user is currently working is called the foreground thread, and
// the window is called the foreground window. All other threads are background
// threads, and the windows created by background threads are called - you guessed
// it - background windows.
//
// The foreground thread gets more CPU time --
// Each thread has a priority level that determines the amount of CPU time the
// thread receives. Although an application can set the priority level of its
// threads, normally the foreground thread has a slightly higher priority level
// than the background threads. Because it has a higher priority, the foreground
// thread receives more CPU time than the background threads. The foreground
// thread has a normal base priority of 9; a background thread has a normal
// base priority of 7. The user sets the foreground window by clicking a window
// or by using the ALT+TAB or ALT+ESC key combination. An application sets the
// foreground window by using the SetForegroundWindow function. If the new
// foreground window is a top-level window, Windows activates it; otherwise,
// Windows activates the associated top-level window. An application retrieves
// the handle of the foreground window by using the GetForegroundWindow function.
// One interesting point to note here is that the user can change this behavior
// somewhat by opening the Tasking dialog box in the System applet found in the
// Control Panel. This dialog box allows the user to set the relative
// foreground/background responsiveness to one of the following:
//
// Best Foreground Application Response Time --
// Foreground Application More Responsive than Background
// Foreground and Background Applications Equally Responsive
// Don't starve your threads!
// It is important to remember that the priority boost the foreground thread
// receives from the system can leave you open to starving your other threads
// or other threads in the system if you are not careful. Some developers
// incorrectly assume that because Windows NT has multiple threads of execution
// and asynchronous input queues, they no longer have to worry about their
// application taking over the system for long periods of time or starving
// other application's threads in the system. That is not true. Windows NT
// will not hang - you will still be able to task-switch away from the offending
// task, and the scheduler will time-slice the foreground thread out every so
// often; however, "hogging" the input queue will still cause the system to be
// unresponsive and is considered to be bad programming practice. If you have
// an unresponsive situation in your application, remember to call PeekMessage
// or another function that will give up the CPU time to the rest of the system.
// For instance, let's say that your application needs to populate a list box
// containing the phone numbers of all persons with the last name Jones. Querying
// for this will most likely take a very long time, but your application really
// cannot do anything else because it needs to list those names before it can go
// on. In this case, if you were to generate this list in response to a sent
// message, you would need to ensure that you call PeekMessage during your
// generation so you don't starve the rest of the threads in your application.
//
// Bringing a Window to the Foreground --
// If you have an application that currently uses SetFocus to bring a window
// created by another thread to the foreground, and you are porting this
// application to Win32, you have already noticed that SetFocus no longer
// sets the focus and returns NULL. Luckily, there is no reason to panic;
// you can still set the focus by using SetForegroundWindow instead. In
// Figure 1, if you want to programmatically switch the focus from the
// "MDI Demonstration" window to the Notepad window, you would use
// SetForegroundWindow to do so rather than SetFocus because the windows
// were created in different threads.
//
// By default, each thread has an independent input state (its own active
// window, its own focus window, and so forth). SetActiveWindow always
// logically sets a thread's active window state. To force a window to the
// foreground, however, use SetForegroundWindow. SetForegroundWindow activates
// a window and forces the window into the foreground. SetActiveWindow brings
// the active window into the foreground only if the thread is the foreground
// thread.
//
// Applications can call AttachThreadInput to allow a set of threads to share
// the same input state. By sharing input state, the threads share their concept
// of the active window. By doing this, one thread can always activate another
// thread's window. This function is also useful for sharing focus state, mouse
// capture state, keyboard state, and window z-order state among windows created
// by different threads whose input state is shared.
//
// Avoiding Message Deadlocking --
// SendMessage works differently under Windows NT than it does under Windows
// version 3.1. Under Windows version 3.1, SendMessage calls the window procedure
// corresponding to the window handle that it is passed. Under Windows NT, only
// the thread that created a window may process the window's messages. A thread
// that calls the SendMessage function to send a message to another thread
// cannot continue executing until the window procedure that receives the
// message returns. If the receiving thread yields control while processing
// the message, the sending thread cannot continue executing because it is
// waiting for SendMessage to return. This situation is called a deadlock.
// So, if a thread sends a message via SendMessage to a window that was created
// by a different thread, the first thread must wait for the second thread to
// be in a receiving state and handle the message for it.
//
//   *
//   /\
//  ~~~~
//  {**}
//   ^^
// /^^^^\
//   <>
//   /\
// _/  \_
//
//   T1
//
//
//  T1. My batteries in my hearing aid must be dead.  I'd better send a letter to
//  the hearing aid company to get a new battery, and wait for them to reply.
//
//  T2. I just received a letter from Mr. Thread1.  He needs a new battery for his
//  hearing aid, but he doesn't specify the size.  I'll phone him and wait until
//  he responds before filling the order.
//
//  T1. Still no reply letter from Mr. Thread2.  I guess I'll have to wait.
//
//  T2. Mr. Thread1 doesn't respond.  I'll keep waiting until he answers the phone.
//
//
// Figure 2. A deadlock condition
//
// In the previous illustration, Mr. Thread-one cannot respond to Mr. Thread-two
// because Mr. Thread-two has not given Mr. Thread-one the batteries he needs.
// And Mr. Thread-two cannot send the batteries back to Mr. Thread-one because
// Mr. Thread-two doesn't know what size batteries to send.
//
// (Please note: Any resemblance to any company's customer services is purely
// coincidental.)
//
// The previous deadlock condition may be prevented by using SendNotifyMessage.
// SendNotifyMessage behaves much like SendMessage except that it returns
// immediately. In fact, if you call SendNotifyMessage to communicate between two
// windows created in the same thread, SendNotifyMessage acts exactly like
// SendMessage. This may be an advantage if it is not important that the sent
// message be completed before the sending thread continues. Note that because
// SendNotifyMessage is asynchronous, pointers to any local variables must not
// be passed along because they will no longer be valid by the time the receiving
// thread attempts to look at them. This would result in a general protection (GP)
// violation when the receiving thread accesses the pointer.
//
// The following functions can be called by the receiving thread to yield control:
//
// DialogBox
// DialogBoxIndirect
// DialogBoxIndirectParam
// DialogBoxParam
// GetMessage
// MessageBox
// PeekMessage
// As mentioned above, if a window procedure yields control when processing a
// message sent by another thread, a message deadlock may result. To determine
// whether a message received was sent by another thread, call the InSendMessage
// function. If it returns TRUE, the window procedure must call the ReplyMessage
// function. By calling this ReplyMessage, the window procedure that receives the
// message allows the thread that called SendMessage to continue to run as though
// the thread receiving the message had returned control. The thread that calls
// the ReplyMessage function also continues to run. If the message was not sent
// through the SendMessage function or if the message was sent by the same thread,
// ReplyMessage has no effect. This is shown in the following example.
//
// case WM_USER + 105:
//     // If this was sent by another thread, call ReplyMessage to
//     // avoid a deadlock when calling DialogBox.
//     if (InSendMessage())
//         ReplyMessage(TRUE);
//
//     DialogBox(hInst, "MyDialogBox", hwndMain, (DLGPROC) MyDlgProc);
//     break;
//
// New Functions --
// Windows NT includes some new functions that are designed to manage the changes
// in functionality and window management when including multiple threads in the
// user interface. These new functions will help you get around deadlocking
// problems and will allow you to share different information, such as key state
// and focus, among threads in the same process. Table 1 lists these functions
// and indicates whether each is supported in Win32s. The sections following the
// table give descriptions of each new function, including any known problems. I
// have not included the new functions that don't involve window management or
// basic thread manipulation. For detailed information about general thread
// management, please refer to the "Multithreading for Rookies" technical article
// by Ruediger Asche in the Development Library.
//
// Table 1. Win32s Support for New Win32 Functions Used for Window Management or
// Thread Manipulation
//
// Function Win32s Support
// SendNotifyMessage No
// PostThreadMessage Yes
// SendMessageTimeout No
// SendMessageCallback No
// SendAsyncProc No
// EnumThreadWindows Yes
// EnumThreadWndProc Yes
// GetWindowThreadProcessId Yes
// AttachThreadInput No
//
// SendNotifyMessage --
// As we just saw, the SendNotifyMessage function sends the specified message to
// the given window. This function is identical to SendMessage if it is used to
// send a message to a window that was created in the current thread - it sends
// the message and does not return until the window procedure has processed the
// message. In the case of an interthread call, the send does not wait for a reply
// from the receiver; it simply returns a Boolean value indicating success or
// failure.
//
// PostThreadMessage --
// The PostThreadMessage function places (posts) a message in the message queue
// of the given thread and then returns without waiting for the thread to process
// the message.
//
// This function replaces the PostAppMessage function. In fact, in Win32,
// PostAppMessage is prototyped to be PostThreadMessage. New Win32 applications
// should use PostThreadMessage instead. The thread to which the message is posted
// retrieves the message by calling the GetMessage or PeekMessage function. The
// hwnd member of the returned MSG structure is NULL.
//
// SendMessageTimeout --
// The SendMessageTimeout function synchronously sends the specified message to
// the given window or windows. The function sends the message to the given window
// and does not return until the window procedure has processed the message or the
// specified time-out period has elapsed. If the window receiving the message does
// not belong to the same message queue as the current thread, the appropriate
// thread to receive the message is awakened and this function waits for a reply.
// If the thread does not respond or if the time-out value is exceeded, this
// function fails. If the window receiving the message belongs to the same message
// queue as the current thread, the time-out is ignored and the functionality is
// the same as it would be if SendMessage were called instead.
//
// In the following example, if the child window procedure (ChildWindowProc) were
// to execute the SendMessageTimeout and the parent window procedure
// (ParentWindowProc) called SendMessage to send a message to its child,
// ChildWindowProc would still be able to process the message because the
// SMTO_NORMAL flag is specified. The SMTO_NORMAL flag indicates that the
// calling thread can process other requests while waiting for SendMessageTimeout
// to return.
//
// ChildWindowProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
// {
//       ...
//       case <xxx>:
//          ...
//          SendMessageTimeout( hWndParent,   // Window handle
//                               WM_USER+100, // Message to send
//                                  wParam,   // First message parameter
//                                  lParam,   // Second message parameter
//                             SMTO_NORMAL,   // Flag *
//                                     100,   // Time-out (in ms)
//                                    &ret ); // Return value
//       ...
//          break;
//
//       case WM_USER+101:
//       <time-consuming procedure>
//          break;
// }
//
// ParentWindowProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
// {
//       ...
//       case WM_USER+100:
//          ...
//          SendMessage( hWndChild,    // Window handle
//                       WM_USER+101,  // Message to send
//                          wParam,    // First message parameter
//                          lParam );  // Second message parameter
//          AFunction();
//          ...
//          break;
// }
//
// If the processing of the message sent by SendMessageTimeout is interrupted,
// the countdown to the time-out will be suspended. Once a message or another
// system event is received and processed, the time-out will be restarted. In
// the above example, the receipt of the message WM_USER+101 by ChildWindowProc
// will cause the time-out to restart after the WM_USER+101 is processed.
//
// In the above example, if the function executed by ParentWindowProc takes
// longer than 100 milliseconds to return and awaken the thread that created
// the child window, the call to SendMessageTimeout will time-out and return.
// This means that any value that was to be returned to ChildWindowProc will
// not be returned.
//
// SendMessageCallback
// The SendMessageCallback function sends the specified message to the given
// window or windows. The function sends the message to the given window and
// returns immediately. After the window procedure processes the message, the
// system calls the specified callback function, passing the result of the
// message processing and an application-defined value to the callback function.
//
// SendAsyncProc
// A SendAsyncProc function is an application-defined callback function that
// the operating system calls when the SendMessageCallback function is called.
// The system passes the message to the callback function after passing the
// message to the destination window procedure. A value of type SENDASYNCPROC
// is a pointer to such a function. SendAsyncProc is a placeholder for an
// application-defined function name. A SendAsyncProc function is installed for
// calling by passing a SENDASYNCPROC pointer to the SendMessageCallback function.
// This callback function does not return a value.
//
// EnumThreadWindows
// The EnumThreadWindows function enumerates all windows associated with a thread
// by passing the handle of each window, in turn, to an application-defined
// callback function. EnumThreadWindows continues until the last window is
// enumerated or the callback function returns FALSE.
//
// Note that the EnumTaskWindows function is now obsolete. It has been replaced
// by the EnumThreadWindows function. To maintain compatibility for older
// applications, EnumTaskWindows has been replaced with a macro that calls
// EnumThreadWindows. Older applications may continue to call EnumTaskWindows,
// but new applications should use EnumThreadWindows.
//
// EnumThreadWndProc
// The EnumThreadWndProc function is an application-defined callback function
// that receives the window handles associated with a thread as a result of a
// call to the EnumThreadWindows function. The callback function can carry out
// any desired task. An application must register this callback function by
// passing its address to the EnumThreadWindows function. EnumThreadWndProc is
// a placeholder for the application-defined function name. To continue
// enumeration, the callback function must return TRUE; to stop enumeration,
// it must return FALSE.
//
// GetWindowThreadProcessId
// The GetWindowThreadProcessId function retrieves the identifier of the thread
// that created the given window and, optionally, the identifier of the process
// that created the window. The return value is the identifier of the thread that
// created the window. The GetWindowTask function is now obsolete. It has been
// replaced by the GetWindowThreadProcessId function. To maintain compatibility
// for older applications, GetWindowTask has been replaced with a macro that calls
// GetWindowThreadProcessId. Older applications may continue to call GetWindowTask,
// but new applications should use GetWindowThreadProcessId. The macro that maps
// GetWindowTask to GetWindowThreadProcessId is:
//    #define GetWindowTask(hwnd) ((HANDLE) GetWindowThreadProcessId(hwnd, NULL))
//
// AttachThreadInput
// The AttachThreadInput function allows a thread to synchronize its input
// processing with another thread. Normally, windows created in different
// threads process input independently of each other, and they are not
// synchronized with the input processing of other threads. By using this
// function, a thread can attach its input processing to another thread. This
// allows a thread to share its input states and, for example, to call the SetFocus
// function to set the keyboard focus to a window of a different thread. In
// Windows 3.1, this capability is not possible.
//
// Creating a window can force an implicit AttachThreadInput when the parent
// windows of the window being created in the second thread were created in
// the first thread. When windows are created or set with a parent-child
// relationship between threads, the mouse and keyboard queues are attached.
//
// Because this function synchronizes input processing, you cannot use
// AttachThreadInput to attach to the Task Manager. The Task Manager must
// remain unsynchronized at all times in order to allow the user to bring
// an application to the foreground and to kill an application. In addition
// to the Task Manager, shell and system threads cannot be attached.
//
// As mentioned above, a call to AttachThreadInput allows, among other things,
// the sharing of key state information between two threads. It is important
// to note that the key state, which can be ascertained by calls to GetKeyState
// or GetKeyboardState, is reset after a call to AttachThreadInput. It is also
// important to note that AttachThreadInput does not take over the input queue
// from another thread. This means that the two threads still have separate
// input, and a call to AttachThreadInput will not force all window messages
// to filter into the same queue. If you need to pass all window messages from
// one message loop to another message loop, you will need to pass those messages
// on manually by sending the message yourself.
//
// Known Problems --
// Currently, if you start an application that calls AttachThreadInput to a thread
// in another process and reset the keyboard state via SetKeyboardState after
// detaching the threads, the call to SetKeyboardState will return TRUE, indicating
// success, but the key state is not successfully set. If the thread is in the same
// process, however, the call to SetKeyboardState does succeed and works as
// expected. This occurs because, when one thread is attached to another thread,
// the system creates a temporary message queue to keep a copy of the current key
// state information of the queue to which you are attaching. If you then set the
// key state, only the temporary queue key state is updated and the function call
// succeeds. Once you detach input processing, the temporary queue is removed and
// the key state change information is lost - it reverts to what it was before the
// attach. To work around this problem, you can either stay attached or use hooks.
// Microsoft is currently looking into a fix for this problem.
//
// The Final Word --
// I have created Table 2 as a quick reference to summarize the different methods
// of sending messages between threads. The first column lists the Win32 function,
// the second column lists the equivalent (or closely equivalent) Windows 3.1
// function, and the third column lists the differences between the Win32 function
// and the Windows 3.1 function. In cases where no equivalent is applicable, the
// item is listed as such. In all cases, if you are writing a new application for
// Win32, you should use the new Win32 function rather than the Windows 3.1 function.
//
// Table 2. Win32 Messaging Functions and the Windows 3.1 Equivalents
//
// Win32 Function Windows 3.1 Equivalent Differences/Suggestions
// AttachThreadInput Not applicable Because all windows are created in the same
// thread under Windows 3.1, input is inherently synchronized, so this function
// does not have a Windows 3.1 equivalent.
//
// EnumThreadWindows EnumTaskWindows Tasks no longer exist under Win32. Use
//    EnumThreadWindows for Win32 applications. The call will be mapped to
//    EnumTaskWindows if your application is running under Windows 3.1.
// GetWindowThreadProcessId GetWindowTask Tasks no longer exist under Win32.
//    Use GetWindowThreadProcessId for Win32 and Win32s applications. The call
//    will be mapped to GetWindowTask if your application is running under Windows 3.1.
// PostMessage PostMessage No changes necessary.
// PostThreadMessage PostAppMessage Use PostThreadMessage for Win32 and Win32s
//    applications. The call will be mapped to PostAppMessage if your application
//    is running under Windows 3.1.
// SendMessage SendMessage No changes necessary.
// SendMessageCallback PostMessage with the receiving window procedure posting
//    back a reply. There is really no exact equivalent to SendMessageCallback in
//    Windows 3.1. SendMessageCallback allows an application to asynchronously
//    send a message and call a callback function when the message is fully processed.
// SendMessageTimeout SendMessage  There is no exact equivalent to SendMessageTimeout
//    in Windows 3.1. SendMessageTimeout allows an application to synchronously send
//    a message and also to specify a time-out period for the message to be fully
//    processed. This allows the application to be a bit more responsive than if it
//    had to rely on SendMessage.
// SendNotifyMessage SendMessage for windows in the same thread. PostMessage for
//    inter-thread messaging. There is no exact equivalent to SendNotifyMessage
//    in Windows 3.1. SendNotifyMessage allows the application to send a message
//    synchronously if the receiving and sending window are in the same thread
//    and to send the message asynchronously if the windows are in different
//    threads. This call is used to avoid a deadlock situation.
//
// Now that you understand the implications of threads on window management,
// you can make your decision on where threads are appropriate to your application.
// Remember to weigh the benefits versus the costs of the threads, and remember,
// too, that adding threads can add complexity to your application. You will find
// that there may be areas in your application that will really benefit from
// processing in a thread, while other places may benefit from the use of
// synchronization objects instead. You may even find that, in looking for
// appropriate places to use threads, you can speed up execution of your
// application or make it more responsive by doing a bit of tidying up in your
// code. (I was going to say "tying up loose threads" instead of "tidying up" -
// aren't you glad I showed some restraint?)
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: SysMainWndProc( HWND, UINT, WPARAM, LPARAM )
//
//  PURPOSE:  Processes messages for Object Services
//
/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK
SysMainWndProc( HWND    hWnd,
                UINT    uMsg,
                WPARAM  wParam,
                LPARAM  lParam )
{
   TraceLineI( "SysMainWndProc for Tomcat session Wnd: ", (zLONG) hWnd );
   switch ( uMsg )
   {
      case WM_DESTROY:        // message: window being destroyed
         PostQuitMessage( 0 );
         break;

      default:
         if ( uMsg == g_wClientMessage )
         {
            TraceLineI( "SysMainWndProc for Tomcat session Wnd: ", (zLONG) hWnd );
            ProcessZeidonMessage( wParam, lParam );
         }

         break;
   }

   return( DefWindowProc( hWnd, uMsg, wParam, lParam ));
}

/////////////////////////////////////////////////////////////////////////////
//
//  PURPOSE:  Saves instance handle and creates main window
//
//  Applications with multiple threads must include a message loop in each
//  thread that creates a window. The message loop and window procedure for
//  a window must be processed by the thread that created the window. If the
//  message loop does not reside in the same thread that created the window,
//  the DispatchMessage function will not get messages for the window. As a
//  result, the window will appear but won't show activation and won't repaint,
//  be moved, receive mouse messages, or generally work as you expect it to.
//
/////////////////////////////////////////////////////////////////////////////
zLONG OPERATION
SysInitApplicationWindow( zLONG   hInstance,
                          zCPCHAR cpcClassName,
                          zCPCHAR cpcWindowTitle )
{
   WNDCLASS  wc;

   // Fill in window class structure with parameters that describe the main window.
   wc.style = 0;                       // class style(s)
   wc.lpfnWndProc = SysMainWndProc;    // function to retrieve messages for
                                       //   windows of this class
   wc.cbClsExtra = 0;                  // no per-class extra data
   wc.cbWndExtra = 0;                  // no per-window extra data
   wc.hInstance = (HANDLE) hInstance;  // application that owns the class
   wc.hIcon = LoadIcon( 0, IDI_APPLICATION );
   wc.hCursor = LoadCursor( 0, IDC_ARROW );
   wc.hbrBackground = GetStockObject( WHITE_BRUSH );
   wc.lpszMenuName = 0;                // name of menu resource in .RC file
   wc.lpszClassName = cpcClassName;    // name used in call to CreateWindow

   // Register the window class and return success/failure code.
   if ( RegisterClass( &wc ) )
   {
      HWND   hMainWnd;
      int    nHeight, nPosY;
      int    nWidth, nPosX;

      // Get the dimensions of the screen ... we don't really care since this
      // window is hidden anyway.
      nWidth = GetSystemMetrics( SM_CXSCREEN );
      nHeight = GetSystemMetrics( SM_CYSCREEN );
      nWidth /= 2;
      nHeight /= 2;
      nWidth -= 40;
      nHeight -= 20;
      nPosX = nWidth / 2;
      nPosY = nHeight / 2;
      nPosX -= 8; // so it doesn't occupy same space as object services
      nPosY -= 8;

      // Create a main window for this application instance.
      hMainWnd = CreateWindow( cpcClassName,        // see RegisterClass( ) call
                               cpcWindowTitle,      // text for window title bar
                               WS_OVERLAPPEDWINDOW, // window style
                               nPosX,               // default horizontal position
                               nPosY,               // default vertical position
                               nWidth,              // default width
                               nHeight,             // default height
                               0,                   // overlapped windows have no parent
                               0,                   // menu for trace window
                            // 0,                   // use default menu
                               (HANDLE) hInstance,  // this instance owns this window
                               0 );                 // pointer not needed
      {
         char szMsg[ 256 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "SysInitApplicationWindow Class: %s    Title: %s  hWnd: 0x%08x=%d",
                    cpcClassName, cpcWindowTitle, (zULONG) hMainWnd, (int) hMainWnd );
         TraceLineS( szMsg, "" );
      // SysMessageBox( 0, "CreateWindow", szMsg, -1 );
      }

      // If window is created, return "success".
      if ( hMainWnd )
      {
         ShowWindow( hMainWnd, SW_HIDE ); // hide the window
         return( (zLONG) hMainWnd );      // return "success"
      }
   }

   return( 0 ); // return "failure"
}

/////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:    DllMain
//
// INPUTS:      hDLL       - handle of DLL
//              dwReason   - indicates why DLL called
//              lpReserved - reserved
//
// RETURNS:     TRUE (always, in this example.)
//
//              Note that the retuRn value is used only when
//              dwReason = DLL_PROCESS_ATTACH.
//
//              Normally the function would return TRUE if DLL initial-
//              ization succeeded, or FALSE it it failed.
//
// GLOBAL VARS: ghMod - handle of DLL (initialized when PROCESS_ATTACHes)
//
// COMMENTS:    The function will display a dialog box informing user of
//              each notification message & the name of the attaching/
//              detaching process/thread. For more information see
//              "DllMain" in the Win32 API reference.
//
/////////////////////////////////////////////////////////////////////////////
BOOL WINAPI
DllMain( HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved )
{
  switch ( dwReason )
  {
      case DLL_PROCESS_ATTACH:
      {
         zSHORT        k;
         zCHAR         szFileName[ zMAX_FILENAME_LTH + 1 ];
         zCHAR         szServerMode[ 10 ];

         /* Seed the random-number generator with current time so that
             * the numbers will be different every time we run.
             */
         srand( (unsigned)time( NULL ) );

         g_lCurrentProcessID = SysGetProcessID( 0 );
         g_hInstance = hDLL;

#ifdef DEBUG_MALLOC
         SysMalloc( -2 );
#endif
         // Register message of Object Services.
         g_wOENG_Message = RegisterWindowMessage( "KZOESRVC" );

         // Check the ServerMode flag in Zeidon.ini.  Since the OE is not running
         // yet, we have to use GetPrivateProfileString( ).
         k = fnBuildZeidonIni( szFileName, zsizeof( szFileName ) );
         if ( k == 0 )
         {
            char szMessage[ 256 ];

            // {2,"KZOEE002 - ZEIDON environment variable not set"},
            SysGetBaseMessage( szMessage, KZOEE002, zsizeof( szMessage ) );

            // We can't use SysMessageBox because it will try to read from
            // Zeidon INI and will bomb because AnchorBlock isn't set.
            MessageBox( GetActiveWindow( ), szMessage, szlOE_SystemError,
                        MB_ICONSTOP | MB_OK | MB_TASKMODAL );

            return( 1 );
         }

         GetPrivateProfileString( "ObjectEngine", "ServerMode", "N", szServerMode,
                                  zsizeof( szServerMode ), szFileName );
         if ( toupper( szServerMode[ 0 ] ) == 'Y' )
            g_bServerMode = TRUE;

         // We need to set up the handle/pointer conversion function.  In
         // Win95, handle and pointers are the same thing.  Note that in
         // server mode, handles and pointers are the same as well, so we'll
         // use the same conversion functions.
         if ( g_bServerMode == FALSE )
         {
            g_bWin95 = FALSE;
            g_pfnGetPtr = fnSysGetPointerFromHandleShared;
            g_pfnGetHndl = fnSysGetHandleFromPointerShared;
         }
         else
         {
            g_pfnGetPtr = fnSysGetPointerFromHandleServerMode;
            g_pfnGetHndl = fnSysGetHandleFromPointerServerMode;
         }

#ifdef __MUTEX_DEBUG__
         g_hMutexDbg = CreateMutex( NULL, FALSE, MUTEXDBG_NAME );
#endif

         for ( k = 0; k < zMUTEX_COUNT; k++ )
            zCREATE_MUTEX( k );

         // Initialize critical sections used in this file.
         InitializeCriticalSection( &g_csSysLoadLibrary );
         InitializeCriticalSection( &g_csReuseEntity );

         break;
      }

      case DLL_PROCESS_DETACH:
      {
         zLONG     k;

         if ( AnchorBlock )
         {
            LPPROCESSLIST lpProcessList;
            LPTASK     lpSystemTask = zGETPTR( AnchorBlock->hMainTask );
            zVIEW      vSystemView = zGETPTR( lpSystemTask->hFirstView );
            LPTASK     lpTask;
            LPNETWORK  lpNetwork;
            LPNETWORK  lpNextNetwork;
            LPTASKOPER lpTaskOperation;
            LPTASKOPER lpNextTaskOperation;
            LPLIBRARY  hLibrary;
            LPLIBRARY  lpLibrary;
            LPLIBRARY  hNextLibrary;
            LPMUTEX    hMutex;
            LPMUTEX    lpMutex;
            LPMUTEX    lpPrevMutex;
            LPMUTEX    hNextMutex;
            zLONG      lProcessID = GetCurrentProcessId( );

            if ( vSystemView )
            {
               zLOCK_MUTEX( zMUTEX_NETWORKCHAIN );

               lpNextNetwork = 0;
               for ( lpNetwork = zGETPTR( AnchorBlock->hFirstNetwork );
                     lpNetwork;
                     lpNetwork = lpNextNetwork )
               {
                  lpNextNetwork = zGETPTR( lpNetwork->hNextNetwork );

                  if ( lpNetwork->lProcessID != lProcessID )
                     continue;

                  NetClose( vSystemView, lpNetwork->szNetworkName );
               }

               zUNLOCK_MUTEX( zMUTEX_NETWORKCHAIN );
            }

            zLOCK_MUTEX( zMUTEX_ANCHORBLOCK );

            // Get a 'write' lock on the task list.  We pass in -1 for the
            // task to indicate that we have no task.  It is used by Browse
            // for information only.
            fnStartBrowseOfTaskList( (LPTASK) -1, FALSE );

            for ( lpTask = zGETPTR( AnchorBlock->hFirstTask );
                  lpTask;
                  lpTask = zGETPTR( lpTask->hNextTask ) )
            {
               for ( lpTaskOperation = zGETPTR( lpTask->hFirstTaskOperation );
                     lpTaskOperation;
                     lpTaskOperation = lpNextTaskOperation )
               {
                  lpNextTaskOperation = zGETPTR( lpTaskOperation->hNextTaskOperationForTask );

                  if ( lpTaskOperation->lProcessID == g_lCurrentProcessID )
                  {
                     fnDropTaskOperation( lpTask, lpTaskOperation );
                  }
               }

               hLibrary = lpTask->hFirstLibrary;
               while ( hLibrary )
               {
                  lpLibrary = zGETPTR( hLibrary );
                  hNextLibrary = lpLibrary->hNextLibrary;
                  if ( lProcessID == lpLibrary->lProcessID )
                     fnSysFreeLibrary( lpTask, hLibrary, TRUE );

                  hLibrary = hNextLibrary;
               }

               fnDropTaskDomains( lpTask );

            // zLOCK_MUTEX( zMUTEX_MUTEX );    // protected by zMUTEX_ANCHORBLOCK
               lpPrevMutex = 0;
               hMutex = lpTask->hFirstMutex;
               while ( hMutex )
               {
                  lpMutex = zGETPTR( hMutex );
                  hNextMutex = lpMutex->hNextMutex;
                  if ( lProcessID == lpMutex->lProcessID )
                  {
                     if ( lpMutex->nLockCount )
                     {
                        // First set nLockCount to 1 so that the next call to
                        // fnSysMutexUnlock actually unlocks the mutex.
                        lpMutex->nLockCount = 1;
                        fnSysMutexUnlock( lpTask, lpMutex );
                     }

                     fnSysMutexDestroy( lpTask, lpMutex );
                     if ( lpPrevMutex )
                        lpPrevMutex->hNextMutex = hNextMutex;
                     else
                        lpTask->hFirstMutex = hNextMutex;

                     fnFreeDataspace( lpMutex );
                  }
                  else
                     lpPrevMutex = lpMutex;

                  hMutex = hNextMutex;
               }

            // zUNLOCK_MUTEX( zMUTEX_MUTEX );
            }

            fnEndBrowseOfTaskList( FALSE );
            zUNLOCK_MUTEX( zMUTEX_ANCHORBLOCK );

            for ( k = 0; k < AnchorBlock->OS_Data.lProcessCount; k++ )
            {
               lpProcessList = &AnchorBlock->OS_Data.ProcessList[ k ];
               if ( lpProcessList->lProcessID == lProcessID )
               {
                  lpProcessList->lProcessID = 0;
                  break;
               }
            }
         }

         for ( k = 0; k < zMUTEX_COUNT; k++ )
            zDESTROY_MUTEX( k );

#ifdef __MUTEX_DEBUG__
         if ( g_hMutexDbg )
            CloseHandle( g_hMutexDbg );

         if ( g_hMutexMemFile )
            CloseHandle( g_hMutexMemFile );
#endif

         // Delete critical sections used in this file.
         DeleteCriticalSection( &g_csSysLoadLibrary );
         DeleteCriticalSection( &g_csReuseEntity );

         break;
      }
   }

   return( TRUE );
}
