/////////////////////////////////////////////////////////////////////////////
//
// MODULE NAME:  KZOENGWA  -  Object services Windows Program
// DESCRIPTION:  This is a Windows program which initializes the Object
//               services DLL and creates the list window for all Object
//               services tracing.
//
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright © 1993 - 2016 QuinSoft, Inc.          All rights reserved.
//    Confidential and Proprietary material subject to license - do not
//    reproduce or disclose.  This material is an unpublished work and
//    is considered a trade secret belonging to the copyright holder.
//
/////////////////////////////////////////////////////////////////////////////
//
//  AUTHOR:  Gig Kirk + D.G. Christensen
//  DATE:    3/1/96
//  API:     Windows 3.x
//  ENVIRONMENT: DOS 5.0
//
/////////////////////////////////////////////////////////////////////////////
/*
CHANGE LOG

Running the Object Engine as a Service

Preliminaries
To run the Object Engine as a service a set of tools is used which are shipped
with the Windows NT 4.0 Resource Kit (also available for Windows NT 2000).

SRVANY.EXE: a utility to run Windows NT applications as services
INSTSRV.EXE: a command-line utility which installs and uninstalls services and assigns names to them, or
SRVINSTW.EXE: Service Installation Wizard which guides the user through the installation of a service.

Installation
To install the Object Engine as a service the tool INSTSRV.EXE is applied.

<DIRECTORY>\instsrv ZeidonOE <DIRECTORY>\srvany.exe installs a service named "ZeidonOE" and calls
RVANY.EXE when the service is started (DIRECTORY specifies the fully qualified path to the
Windows NT Resource Kit installation path).

Use the registry editor to provide additional information SRVANY.EXE needs to wrap an application
as a service,

 - add a subkey "Parameters" under HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ZeidonOE\

 - create an "Application" value entry of type REG_SZ and specify the full path to the Zeidon Object
   Engine (usually: C:\TBeller\Zeidon\bin\KZOENGWA.EXE )

 - create an "AppDirectory" value entry of type REG_SZ and specify the working directory for the
   Zeidon Object Engine (usually: C:\TBeller\Zeidon\bin )

Open the Service Control Manager (Start \ Settings \ Control Panel \ Services). Click the service you
specified (ZeidonOE) and open the Startup Dialog Box. Select the Startup Type (usually: "Automatic").
In the "Log On As" Group Box please choose "System Account".

You may start the service either by using the Service Control Manager or through the command
"net start ZeidonOE".

Restriction
Using the Object Engine as a service is only recommended for a Remote Object Engine in an Engine-to-Engine
communication scenario. If the Object Engine is started as described on a workstation it is not possible to
launch an application which accesses the Object Engine on the same machine. This would fail and the Object
Engine would issue some errors to notify that the creation of some mutexes were not successfull.

When the ZeidonOE Service is started and the Object Service window appears this window has to remain open.
Closing this window or a user logoff will terminate the Object Engine, the ZeidonOE Service will remain in
"Started" mode, nonetheless.

The ZEIDON environment variable has to be defined at system-level. The PATH environment variable defined
at system-level has to contain the "<InstallationDirectory>\Zeidon\bin" directory to locate all DLLs.

*/

// #define  STRICT    // See how we pass windows 3.1 strict test

#if defined( _WINDOWS ) && defined( DEBUG )
#pragma optimize( "", off )
#endif

#include <windows.h>
#include <stdio.h>
#include <commctrl.h>

#include "kzoeswrc.h"   // Object Service Window Resources

// Windows 3.0 and 3.1 compatibility
#ifndef UINT
typedef unsigned int     UINT;
#endif

#define  KZOESYS_INCL
#include <kzoengaa.h>     // Object Services public prototypes

#define zGLOBAL_DATA
#include <kzoengaa.hg>

#include <math.h>         // for atof conversion

#include <stdlib.h>

#ifdef __WIN32__
   #include <process.h>
   #undef zGETPTR
   #undef zGETHNDL
   #define zGETPTR( a )  SysGetPointerFromHandle( (a) )
   #define zGETHNDL( a )  SysGetHandleFromPointer( (a) )
#else
   #undef zGETPTR
   #define zGETPTR( a )  (a)
   #include <toolhelp.h>
#endif

#include <kzoengwa.h>   // Object Service Window Functions

HANDLE hInst;                           // current instance
UINT g_uTraceLineLimit = 4000;          // limit of list box items
HWND g_hWndMainFrame;                   // handle to the main frame window
char g_chScrollTrace = 0;               // scroll trace
char g_chTraceOE_Warning = 0;           // trace OE Warnings
char g_chTraceZDrActions = 0;           // trace ZDr Actions
char g_chTraceWebActions = 0;           // trace Web Actions
char g_chTraceMemory = 0;
char g_szZeidonEnvDirectory[ MAX_PATH + 1 ];// Zeidon environment used via commandline
char g_szFindString[ 256 ];
char g_szCopyBuffer[ 512 ];
char g_chPrintPreview = 0;
char g_chPrintDialog = 0;
UINT g_wOENG_Message = 0;               // memory management message
char szClassName[ ] = "KZOENGWAWClass"; // name used in call to CreateWindow
char szThreadClassName[ ] = "KZOENGWAW_Thread_Class";

// Zeidon Client Timeout variables
zCHAR        g_szTimeStamp[ 20 ] = { 0 };
zLONG        g_lTimeOut = 0;
UINT         g_uIdleTimerId = 0;
UINT         g_uKillTimerId = 0;
int          g_nIdIdleEvt = 14;
int          g_nIdKillEvt = 15;

HWND g_hWndLB;                          // handle to the OE client window listbox

// We keep a circular list of listboxes for the trace window.
#define MAX_TRACE_WINDOWS  20
// definitions for using systray
#define zWM_NOTIFYICON       (WM_APP + 100)
#define zTRAY_MESSAGE       1
#define zTRAY_MESSAGE_SHOW  zTRAY_MESSAGE + 1

HWND g_hwndTraceWindow[ MAX_TRACE_WINDOWS ];
UINT g_nTraceWindowCnt;
UINT g_nTraceWindowHead;
UINT g_nTraceWindowDisplayed;

typedef int (POPERATION zFARPROC_CALLBACK)( HWND, UINT, WPARAM, LPARAM );

zFARPROC_CALLBACK fpAbout;
zFARPROC_CALLBACK fpLogon;
zFARPROC_CALLBACK fpSetTrace;
zFARPROC_CALLBACK fpLogTrace;
zFARPROC_CALLBACK fpTraceList;
zFARPROC_CALLBACK fpLineLimit;
zFARPROC_CALLBACK fpFindString;
zFARPROC_CALLBACK fpShowDLL;
zFARPROC_CALLBACK fpSqlServerErrHandler;
zFARPROC_CALLBACK fpSqlServerMsgHandler;
zFARPROC_CALLBACK fpDfltListWndProc;

long    g_hLogFile = -1;
const char szZeidonParmName[ ] = "ZEIDON";  // Zeidon Parameter name used via command line
char    szLogFileName[ 256 ] = "";
char    szlWorkstation[] = "[Workstation]";
char    szlUserID[]      = "UserID";
char    szlPassword[]    = "Password";
char    szlINTL[]        = "Intl";
char    szPlaceFormat[]  = "%u,%u,%d,%d,%d,%d,%d,%d,%d,%d";
char    szMark[] = "|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-"
                   "|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|";
zLONG    g_lMark = 0;
LPANCHOR AnchorBlock = 0;
zVIEW    g_vSystemTaskView = 0;

zBOOL ReadWindowPlacement( LPTASK lpTask, LPWINDOWPLACEMENT pwp );
zBOOL CheckWindowPos( LPWINDOWPLACEMENT pwp );

#ifdef __WIN32__
   zBOOL  g_bThreadStarted = FALSE;
   zULONG g_hThread;
   zULONG g_dwThreadID;
   HWND   g_hThreadWnd;

unsigned __stdcall fnThreadProc( zPVOID p )
{
   MSG msg;

   g_hThreadWnd = CreateWindow(
      szThreadClassName,              // see RegisterClass( ) call
      "Zeidon Object Services",       // text for window title bar
      0,                              // window style
      0,                              // default horizontal position
      0,                              // default vertical position
      0,                              // default width
      0,                              // default height
      0,                              // overlapped windows have no parent
      0,                              // menu for trace window
      hInst,                          // this instance owns this window
      0                               // pointer not needed
   );

   g_bThreadStarted = TRUE;

   // Acquire and dispatch messages until a WM_QUIT message is received
   while ( GetMessage( &msg,          // message structure
                       g_hThreadWnd,  // handle of window receiving the message
                       0,             // lowest message to examine
                       0 ) )          // highest message to examine
   {
      if ( !TranslateAccelerator( g_hThreadWnd, 0, &msg ) )
      {
         TranslateMessage( &msg );    // Translate message
         DispatchMessage( &msg );     // Dispatches message to window
      }
   }
   return( 0 );
}

long zPASCAL
MainThrdWndProc( HWND   hWnd,         // window handle
                 UINT   uMsg,         // type of message
                 WPARAM wParam,       // additional information
                 LPARAM lParam )      // additional information
{
   switch ( uMsg )
   {
      case WM_DESTROY:                // message: window being destroyed
         PostQuitMessage( 0 );
         break;

      case WM_TIMER:
      {
         zCHAR szFileName[ zMAX_FILENAME_LTH + 1 ];
         zCHAR szTempName[ zMAX_FILENAME_LTH + 1 ];
         UINT uIdTimer = wParam;

      // TraceLine( "WM_TIMER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! %d  Wnd: 0x%08x", uIdTimer, hWnd );

         if ( uIdTimer == g_uIdleTimerId )
         {
            zLONG lDiffSeconds;
            zCHAR szDateTime[ 20 ];

         // TraceLine( "App idle for count %d", lCount );

            SysGetDateTime( szDateTime, zsizeof( szDateTime ) );
            SysGetDateTimeDifference( &lDiffSeconds, g_szTimeStamp, szDateTime, zDT_SECOND );
            if ( g_uKillTimerId == 0 && lDiffSeconds > g_lTimeOut )
            {
               int nRC;

               TraceLine( "OE Setting Kill Timer for hWnd: 0x%08x   g_hWndMainFrame: 0x%08x  Id: %d",
                          hWnd, g_hWndMainFrame, g_nIdKillEvt );
               g_uKillTimerId = SetTimer( hWnd, g_nIdKillEvt, 60000, 0 );  // 60000 ==> one minute
               nRC = MessageBox( hWnd, "Due to inactivity, your Zencas session will\n"
                                   "be timed out in one minute. Click OK if you\n"
                                   "want to continue using Zencas.",
                                 "Zencas Timeout", MB_OK | MB_ICONSTOP | MB_TOPMOST | MB_APPLMODAL );
               if ( nRC == IDOK )
               {
                  if ( g_uKillTimerId )
                  {
                     KillTimer( hWnd, g_uKillTimerId );
                     g_uKillTimerId = 0;
                  }

                  SysGetDateTime( g_szTimeStamp, zsizeof( g_szTimeStamp ) );
               }
            }

            return( 0 );  // an application should return zero if it processes this message
         }

         if ( uIdTimer == g_uKillTimerId )
         {
            KillTimer( g_hWndMainFrame, g_uKillTimerId );
            g_uKillTimerId = 0;

            SysReadZeidonIni( -1, "[ObjectEngine]", "KillZeidon", szTempName, zsizeof( szTempName ) );
            SysConvertEnvironmentString( szFileName, zsizeof( szFileName ), szTempName );
            TraceLineS( "KillZeidon: ", szFileName );
            if ( szFileName[ 0 ] )
            {
               TraceLineS( "KillZeidon: ", szFileName );
               Sleep( 5000 );
               WinExec( szFileName, SW_SHOWNORMAL );
            }

            return( 0 );  // an application should return zero if it processes this message
         }

         return( 1 ); // we did not process the timer message
      }

      case WM_CLOSE:
         PostMessage( g_hWndMainFrame, WM_CLOSE, 0, 0 );
         return( 0 ); // do not call DefWindProc
                      // Hartmut:
                      // I think, I solved the problem.  It is triggered
                      // by "DropEngineIfNoTasks".  The invisible
                      // "Thread Main Window" gets WM_CLOSE and promotes
                      // the WM_CLOSE to the visible main window.  It
                      // should NOT call DefWndProc (which sends
                      // WM_DESTROY), which causes the problem of
                      // extremely slow shutdown ... probably due to a
                      // race condition (MUTEX) between the 2 threads.
      // break;

      case WM_COMMAND:
         return( MainWndProc( hWnd, uMsg, wParam, lParam ) );

      default:
         if ( uMsg == g_wOENG_Message )
            fnProcessOENG_Message( hWnd, uMsg, wParam, lParam );
   }

   return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
}

#endif

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:     WinMain
//  PURPOSE:   Establish message queue and create object services window
//
/////////////////////////////////////////////////////////////////////////////
int WINAPI
WinMain( HINSTANCE hInstance,
         HINSTANCE hPrevInstance,
         LPSTR lpCmdLine,
         int nCmdShow )
{
   MSG    msg;        // message
   HACCEL hAccel;
   HMENU  hMenu;
   zCHAR  szWork[ MAX_PATH + 1 ];

#ifdef __WIN32__
   char szCmdLineBuffer[ 3 * MAX_PATH ];
   HANDLE hMutex1 = 0;
   HANDLE hMutex2 = 0;
   HANDLE hServicesStarted;

   LPSTR pchZeidonDir = NULL;
   LPSTR pchSrc = NULL;
   LPSTR pchTgt = NULL;

   memset( szCmdLineBuffer, 0, 3 * MAX_PATH );
   memset( g_szZeidonEnvDirectory, 0, MAX_PATH + 1 );
   pchSrc = lpCmdLine;
   pchTgt = szCmdLineBuffer;

   // convert everything to uppercase
   while( *pchSrc )
   {
      *pchTgt = toupper( *pchSrc );
      pchSrc++;
      pchTgt++;
   }

   // search for "ZEIDON" token
   pchZeidonDir = strstr( szCmdLineBuffer, szZeidonParmName );
   while( pchZeidonDir && *pchZeidonDir != '=' )
      pchZeidonDir++;

   // skip '='
   if ( pchZeidonDir && *pchZeidonDir == '=' )
      pchZeidonDir++;

   // eliminate leading whitespaces
   while ( pchZeidonDir && isspace( *pchZeidonDir ) )
      pchZeidonDir++;

   // if current char is a " we have to copy anything up to the next " char
   if ( pchZeidonDir && *pchZeidonDir == '"' )
   {
      pchZeidonDir++;
      pchTgt = g_szZeidonEnvDirectory;
      while( *pchZeidonDir != '"' && *pchZeidonDir )
      {
         *pchTgt = *pchZeidonDir;
         pchTgt++;
         pchZeidonDir++;
      }
   }
   else // otherwise we copy anything up to the next whitespace
   {
      pchTgt = g_szZeidonEnvDirectory;
      while( pchZeidonDir && *pchZeidonDir && ! isspace( *pchZeidonDir ) )
      {
         *pchTgt = *pchZeidonDir;
         pchTgt++;
         pchZeidonDir++;
      }
   }

   // Make sure only one copy of kzoengwa is running.  Start by creating
   // a mutex to protect process of checking.
   if ( (hMutex1 = CreateMutex( NULL, FALSE, "KZOENGWA - INIT" )) == 0 )
   {
      SysMessageBox( 0, "Zeidon Object Engine", "Can't create init mutex", 1 );
      return( FALSE );
   }

   // Lock mutex.
   WaitForSingleObject( hMutex1, INFINITE );

   // Now see if a second mutex has already been created.  If it has then
   // KZOENGWA has already been started.
   if ( (hMutex2 = OpenMutex( MUTEX_ALL_ACCESS, FALSE, "KZOENGWA - INIT 2!!!" )) != 0 )
   {
      // Close all the mutexes and get out.
      CloseHandle( hMutex2 );
      ReleaseMutex( hMutex1 );
      CloseHandle( hMutex1 );

      SysMessageBox( 0, "Zeidon Object Engine", "Only one instance of KZOENGWA can exist at once.", 1 );

      return( FALSE );
   }

   // If we get here then this is the only instance of KZOENGWA so
   // create the second mutes.  Note that we DON'T lock it.
   hMutex2 = CreateMutex( NULL, FALSE, "KZOENGWA - INIT 2!!!" );

   // We don't need it anymore so dump the first mutex.
   ReleaseMutex( hMutex1 );
   CloseHandle( hMutex1 );

   if ( InitApplication( hInstance ) == 0 ) // Initialize shared things
   {
      CloseHandle( hMutex2 );    // Get rid of the instance mutex
      return( FALSE );           // Exits if unable to initialize
   }

#else
   if ( hPrevInstance == 0 )     // Other instances of app running?
   {
      // If we need to increase the size of the message queue, here is where
      // it will need to be done.  We need to do this to prevent the loss
      // of TraceLine messages.

      zSHORT nMsg = 32;  // the maximum size is 120, the default size is 8

      while ( nMsg > 8 && SetMessageQueue( nMsg ) == 0 )
         nMsg -= 8;


      // run in enhanced or protected mode only - not in real mode
      if ( (GetWinFlags( ) & WF_PMODE) != WF_PMODE )
      {
         MessageBox( GetActiveWindow( ),
                     "Zeidon cannot be executed in real mode",
                     "Zeidon", MB_ICONSTOP | MB_OK );
         return( FALSE );
      }

      if ( InitApplication( hInstance ) == 0 ) // Initialize shared things
         return( FALSE );                      // Exits if unable to initialize
   }
   else
   {
      AnchorBlock = SysGetAnchorBlock( );
      if ( AnchorBlock )
         SetActiveWindow( (HWND) AnchorBlock->lOE_hMainWnd );

      return( FALSE );
   }
#endif

   // Perform initializations that apply to a specific instance
   if ( InitInstance( hInstance, nCmdShow ) == 0 )
   {
#ifdef __WIN32__
      // Get rid of the second instance mutex.
      CloseHandle( hMutex2 );
#endif
      return( FALSE );
   }

#ifdef __WIN32__
   TraceLineS( "Engine started for Win32", "" );
#endif

   hAccel = LoadAccelerators( hInstance, "TRACE_ACCEL" );

#ifndef ALLOC_FREE_TRACE
   hMenu = GetMenu( g_hWndMainFrame );
   if ( hMenu )
   {
      hMenu = GetSubMenu( hMenu, 1 );
   // DeleteMenu( hMenu, IDM_SETMEMORYTRACE, MF_BYCOMMAND );
      RemoveMenu( hMenu, 9, MF_BYPOSITION );
      DrawMenuBar( g_hWndMainFrame );
   }
#endif

#ifndef LOAD_FREE_TRACE
   hMenu = GetMenu( g_hWndMainFrame );
   if ( hMenu )
   {
      hMenu = GetSubMenu( hMenu, 1 );
   // DeleteMenu( hMenu, IDM_SETLOADTRACE, MF_BYCOMMAND );
      RemoveMenu( hMenu, 13, MF_BYPOSITION );
      DrawMenuBar( g_hWndMainFrame );
   }
#endif

   AnchorBlock->nStatus = AnchorInitialized; // Flag init as complete

   // Open a Win32 event so we can signal to everybody that we're done.
   hServicesStarted = CreateEvent( NULL, TRUE, FALSE, "Zeidon - Object Services Init" );
   SetEvent( hServicesStarted );
   CloseHandle( hServicesStarted );

   SysReadZeidonIni( -1, "[ObjectEngine]", "TimeOut", szWork, zsizeof( szWork ) );
   if ( szWork[ 0 ] && (g_lTimeOut = zatol( szWork )) != 0 )
   {
      SysReadZeidonIni( -1, "[ObjectEngine]", "KillZeidon", szWork, zsizeof( szWork ) );
      if ( szWork[ 0 ] )
         SysGetDateTime( g_szTimeStamp, zsizeof( g_szTimeStamp ) );
      else
      {
         MessageBox( 0, "TimeOut requires KillZeidon specification", "Object Services", MB_OK );
         g_lTimeOut = 0;
      }
   }

   // Acquire and dispatch messages until a WM_QUIT message is received
   while ( GetMessage( &msg,     // message structure
                       0,        // handle of window receiving the message
                       0,        // lowest message to examine
                       0 ) )     // highest message to examine
   {
      if ( !TranslateAccelerator( g_hWndMainFrame, hAccel, &msg ) )
      {
         TranslateMessage( &msg );  // Translate message
         DispatchMessage( &msg );   // Dispatches message to window
      }
   }

#ifdef __WIN32__
   // Get rid of the second instance mutex.
   CloseHandle( hMutex2 );
#endif

   return( msg.wParam );         // Returns the value from PostQuitMessage
}

void
WriteTraceToLog( LPTASK lpTask )
{
   char   szTraceText[ 512 ];
   zPVOID ppvFile = 0;
   zSHORT idx;
   WORD   wItem;
   WORD   wItemCnt;
   UINT   k;

   // The file has been opened, get all text from all the
   // list boxes and write it to the trace file
   for ( k = 0; k < g_nTraceWindowCnt; k++ )
   {
      idx = (g_nTraceWindowHead + k + 1) % g_nTraceWindowCnt;
      wItemCnt = (WORD) SendMessage( g_hwndTraceWindow[ idx ], LB_GETCOUNT, 0, 0L );
      for ( wItem = 0; wItem < wItemCnt; wItem++ )
      {
         SendMessage( g_hwndTraceWindow[ idx ], LB_GETTEXT, wItem, (LONG)(LPSTR) szTraceText );
         fnSysWriteLine( lpTask, g_hLogFile, &ppvFile, szTraceText );
      }
   }
}

void OPERATION
fnListDataspaceLeak( LPANCHOR lpAnchorBlock, zPVOID hTask, zSHORT nFlag );

/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: MainWndProc(HWND, unsigned, MPARAM, MPARAM )
//
//  PURPOSE:  Processes messages for Object Services
//
//  MESSAGES:
//
//  COMMENTS:
//
/////////////////////////////////////////////////////////////////////////////
long zPASCAL
MainWndProc( HWND   hWnd,                // window handle
             UINT   uMsg,                // type of message
             WPARAM wParam,              // additional information
             LPARAM lParam )             // additional information
{
   RECT   rect;

   switch ( uMsg )
   {
      //entry for systray notifications
      case zWM_NOTIFYICON:
         if (lParam == WM_RBUTTONDOWN )
         {
            POINT point;

            GetCursorPos( &point );
            HandlePopupMenu( hWnd, point );
         }

         break;

      case WM_SYSCOMMAND:
         //if ( (wParam & 0xFFF0) == SC_MINIMIZE )
         //   return( 0 );

         return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );

      case WM_SIZE:
      {
         UINT i;

         GetClientRect( hWnd, &rect );

         for ( i = 0; i < g_nTraceWindowCnt; i++ )
            MoveWindow( g_hwndTraceWindow[ i ], rect.left, rect.top,
                        rect.right - rect.left, rect.bottom - rect.top, TRUE );
         break;
      }

      case WM_COMMAND:
      {
         WORD wCommand;
#ifdef __WIN32__
         wCommand = LOWORD( wParam ); // command identifier
#else
         wCommand = wParam;         // command identifier
#endif
//       TraceLineI( "OE WM_COMMAND wCommand: ", wCommand );
         if ( wCommand == IDM_SHOWTRACE )
         {
            ShowWindow( g_hWndMainFrame, SW_RESTORE );
         }
         else
         if ( wCommand == IDM_LOGON )
         {
            DialogBox( hInst, MAKEINTRESOURCE( IDD_LOGON ), hWnd, fpLogon );
         }
         else
         if ( wCommand == IDM_LOGTRACE )
         {
            DialogBox( hInst, MAKEINTRESOURCE( IDD_LOGTRACE ), hWnd, fpLogTrace );
         }
         else
         if ( wCommand == IDM_SHOWDLL )
         {
            DialogBox( hInst, MAKEINTRESOURCE( IDD_SHOWDLL ), hWnd, fpShowDLL );
         }
         else
         if ( wCommand == IDM_LINELIMIT )
         {
            DialogBox( hInst, MAKEINTRESOURCE( IDD_LINELIMIT ), hWnd, fpLineLimit );
            if ( g_uTraceLineLimit == 0 )
            {
               SendMessage( g_hWndLB, LB_RESETCONTENT, 0, 0L );
               AnchorBlock->bTraceCnt = FALSE;
            }
            else
               AnchorBlock->bTraceCnt = TRUE;
         }
         else
         if ( wCommand == IDM_FINDSTRING || wCommand == IDM_FINDNEXT || wCommand == IDM_FINDPREV )
         {
            if ( wCommand == IDM_FINDSTRING )
            {
               if ( DialogBox( hInst, MAKEINTRESOURCE( IDD_FINDSTRING ), hWnd, fpFindString ) != IDOK )
               {
                  break;
               }
            }

            if ( g_szFindString[ 0 ] == 0 )
               break;
            else
            {
               char szFindString[ 512 ];
               char szText[ 512 ];
               int  nFound = 0;
               HWND hwndTrace = g_hwndTraceWindow[ g_nTraceWindowDisplayed ];
               WORD wItemCnt = (WORD) SendMessage( hwndTrace, LB_GETCOUNT, 0, 0 );
               WORD wCurSel = (WORD) SendMessage( hwndTrace, LB_GETCURSEL, 0, 0L );
               WORD k;

               strcpy_s( szFindString, zsizeof( szFindString ), g_szFindString );
               SysTranslateString( szFindString, 'L' );
               if ( wCommand == IDM_FINDPREV )
               {
                  if ( wCurSel <= 0 )
                  {
                     wCurSel = wItemCnt;
                     k = wItemCnt - 1;
                  }
                  else
                  {
                     k = wCurSel - 1;
                  }
               }
               else
               {
                  if ( wCurSel > wItemCnt - 1 || wCurSel == (WORD) -1 )
                  {
                     wCurSel = (WORD) -1;
                     k = 0;
                  }
                  else
                  {
                     k = wCurSel + 1;
                  }
               }

               while ( wItemCnt )
               {
                  if ( k < wItemCnt )
                  {
                     SendMessage( hwndTrace, LB_GETTEXT, k, (LPARAM) szText );
                     SysTranslateString( szText, 'L' );
                     if ( zstrstr( szText, szFindString ) )
                     {
                        SendMessage( hwndTrace, LB_SETCURSEL, k, 0L );
                        SetFocus( hwndTrace );
                        nFound++;
                        break;
                     }
                  }

                  if ( k == wCurSel )
                     break;
                  else
                  if ( wCommand == IDM_FINDPREV )
                  {
                     if ( k <= 0 )
                     {
                        if ( wCurSel == wItemCnt )
                           break;       // no need to wrap
                        else
                        if ( MessageBox( hWnd, "Wrap to continue search?",
                                         "Zeidon Object Services",
                                         MB_ICONQUESTION | MB_YESNO | MB_APPLMODAL ) == IDNO )
                        {
                           SetFocus( hwndTrace );
                           nFound = 1;  // pretend we found one
                           break;       // don't keep looking
                        }

                        k = wItemCnt - 1;
                     }
                     else
                     {
                        k--;
                     }
                  }
                  else
                  {
                     if ( k >= wItemCnt - 1 )
                     {
                        if ( wCurSel == -1 )
                           break;       // no need to wrap
                        else
                        if ( MessageBox( hWnd, "Wrap to continue search?",
                                         "Zeidon Object Services",
                                         MB_ICONQUESTION | MB_YESNO | MB_APPLMODAL ) == IDNO )
                        {
                           SetFocus( hwndTrace );
                           nFound = 1;  // pretend we found one
                           break;       // don't keep looking
                        }

                        k = 0;
                     }
                     else
                     {
                        k++;
                     }
                  }
               }

               if ( nFound == 0 )
               {
                  strcpy_s( szText, zsizeof( szText ), "Search string not found - " );
                  strcat_s( szText, zsizeof( szText ), g_szFindString );
                  MessageBox( hWnd, szText, "Zeidon Object Engine", MB_OK | MB_ICONINFORMATION );
               }
            }
         }
         else
         if ( wCommand == IDM_COPYSTRING || wCommand == IDM_CUTSTRING )
         {
            WORD wCurSel = (WORD) SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ],
                                               LB_GETCURSEL, 0, 0 );
            zLONG lTextLth = SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ],
                                          LB_GETTEXTLEN, wCurSel, 0L );
            if ( lTextLth < zsizeof( g_szCopyBuffer ) )
            {
               SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ],
                            LB_GETTEXT, wCurSel, (LPARAM) g_szCopyBuffer );
            }
            else
            {
               char *pchMem;

               SfAllocTaskMemory( g_vSystemTaskView, (zCOREMEM) &pchMem, lTextLth + 1 );
               SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_GETTEXT, wCurSel, (LPARAM) pchMem );
               pchMem[ zsizeof( g_szCopyBuffer ) - 1 ] = 0;
               strcpy_s( g_szCopyBuffer, zsizeof( g_szCopyBuffer ), pchMem );
               SfFreeTaskMemory( pchMem );
            }

            if ( OpenClipboard( hWnd ) ) 
            {
               HGLOBAL hglbCopy; 
               LPTSTR  lptstrCopy; 

               EmptyClipboard(); 
               hglbCopy = GlobalAlloc( GMEM_MOVEABLE, (lTextLth + 1) * sizeof( TCHAR ) ); 
               if ( hglbCopy ) 
               { 
                  lptstrCopy = GlobalLock( hglbCopy ); 
                  memcpy( lptstrCopy, g_szCopyBuffer, (lTextLth + 1) * sizeof( TCHAR ) );
                  lptstrCopy[ lTextLth ] = (TCHAR) 0;    // null character 
                  GlobalUnlock( hglbCopy ); 

                  // Place the handle on the clipboard. 
                  SetClipboardData( CF_TEXT, hglbCopy ); 
               }
               CloseClipboard(); 
            }

            if ( wCommand == IDM_CUTSTRING )
            {
               SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_DELETESTRING, wCurSel, 0L );
               SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_SETCURSEL, wCurSel, 0L );
            }
         }
         else
         if ( wCommand == IDM_PASTESTRING )
         {
            WORD wCurSel = (WORD) SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_GETCURSEL, 0, 0 );
            SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_INSERTSTRING, wCurSel + 1, (LPARAM) g_szCopyBuffer );
            SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_SETCURSEL, wCurSel + 1, 0L );
         }
         else
         if ( wCommand == IDM_DELETESELECTED )
         {
            WORD wCurSel = (WORD) SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_GETCURSEL, 0, 0 );
            SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_DELETESTRING, wCurSel, 0L );
            SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_SETCURSEL, wCurSel, 0L );
         }
         else
         if ( wCommand == IDM_INSERTMARKER )
         {
            WORD wCurSel = (WORD) SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], LB_GETCURSEL, 0, 0 );
            zSHORT nLth = zsizeof( szMark ) - 1;
            zLONG  j, k;

            g_lMark++;
            k = g_lMark;
            while ( k )
            {
               nLth--;
               j = k % 10;
               szMark[ nLth ] = (char) (j + '0');
               k /= 10;
            }

            SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ],
                         LB_INSERTSTRING,  wCurSel + 1, (LPARAM) szMark );
            SendMessage( g_hwndTraceWindow[ g_nTraceWindowDisplayed ],
                         LB_SETCURSEL, wCurSel + 1, 0L );
         }
         else
         if ( wCommand == IDM_PRINTPREVIEW || wCommand == IDM_PREVIEW_ZOOMOUT ||
              wCommand == IDM_PREVIEW_ZOOM || wCommand == IDM_PREVIEW_ZOOMIN )
         {
            HMENU hMenu = GetMenu( hWnd );

            CheckMenuItem( hMenu, IDM_PRINTPREVIEW, MF_BYCOMMAND | MF_UNCHECKED );
            CheckMenuItem( hMenu, IDM_PREVIEW_ZOOMOUT, MF_BYCOMMAND | MF_UNCHECKED );
            CheckMenuItem( hMenu, IDM_PREVIEW_ZOOM, MF_BYCOMMAND | MF_UNCHECKED );
            CheckMenuItem( hMenu, IDM_PREVIEW_ZOOMIN, MF_BYCOMMAND | MF_UNCHECKED );
            switch ( wCommand )
            {
               case IDM_PREVIEW_ZOOMOUT:
                  g_chPrintPreview = '0';
                  CheckMenuItem( hMenu, IDM_PREVIEW_ZOOMOUT, MF_BYCOMMAND | MF_CHECKED );
                  break;

               case IDM_PREVIEW_ZOOM:
                  g_chPrintPreview = '1';
                  CheckMenuItem( hMenu, IDM_PREVIEW_ZOOM, MF_BYCOMMAND | MF_CHECKED );
                  break;

               case IDM_PREVIEW_ZOOMIN:
                  g_chPrintPreview = '2';
                  CheckMenuItem( hMenu, IDM_PREVIEW_ZOOMIN, MF_BYCOMMAND | MF_CHECKED );
                  break;

               case IDM_PRINTPREVIEW:
               default:
                  g_chPrintPreview = 0;
                  CheckMenuItem( hMenu, IDM_PRINTPREVIEW, MF_BYCOMMAND | MF_CHECKED );
                  break;
            }

            if ( g_chPrintPreview )
            {
               g_chPrintDialog = 0;
               CheckMenuItem( hMenu, IDM_PRINTDIALOG, MF_BYCOMMAND | MF_UNCHECKED );
            }
         }
         else
         if ( wCommand == IDM_PRINTDIALOG )
         {
            HMENU hMenu = GetMenu( hWnd );
            g_chPrintDialog = g_chPrintDialog ? 0 : 'Y';
            CheckMenuItem( hMenu, IDM_PRINTDIALOG, MF_BYCOMMAND | (g_chPrintDialog ? MF_CHECKED : MF_UNCHECKED) );
            if ( g_chPrintDialog == 'Y' )
            {
               g_chPrintPreview = 0;
               CheckMenuItem( hMenu, IDM_PRINTPREVIEW, MF_BYCOMMAND | MF_CHECKED );
               CheckMenuItem( hMenu, IDM_PREVIEW_ZOOMOUT, MF_BYCOMMAND | MF_UNCHECKED );
               CheckMenuItem( hMenu, IDM_PREVIEW_ZOOM, MF_BYCOMMAND | MF_UNCHECKED );
               CheckMenuItem( hMenu, IDM_PREVIEW_ZOOMIN, MF_BYCOMMAND | MF_UNCHECKED );
            }
         }
         else
         if ( wCommand == IDM_SHOWTASKID )
         {
            HMENU hMenu = GetMenu( hWnd );
            if ( AnchorBlock->bShowTaskID )
            {
               AnchorBlock->bShowTaskID = 0;
               CheckMenuItem( hMenu, IDM_SHOWTASKID, MF_BYCOMMAND | MF_UNCHECKED );
            }
            else
            {
               AnchorBlock->bShowTaskID = 1;
               CheckMenuItem( hMenu, IDM_SHOWTASKID, MF_BYCOMMAND | MF_CHECKED );
            }
         }
         else
         if ( wCommand == IDM_ABOUT )
         {
            DialogBox( hInst, MAKEINTRESOURCE( IDD_ABOUT ), hWnd, fpAbout );
         }
         else
         if ( wCommand == IDM_HIDEWINDOW )   // If launched in systray mode
         {                                   // a different menu is loaded
            ShowWindow( hWnd, SW_HIDE );     // having no Exit option but a hide Window
         }
         else
         if ( wCommand == IDM_EXITPROGRAM )   // F3 Exit
         {
         // SendMessage( (HWND) AnchorBlock->lOE_hMainWnd, // hWnd,
         //              WM_COMMAND, (WPARAM) IDM_LISTTASKS, 10000L );
            PostMessage( hWnd, WM_CLOSE, 0, 0L );
            break;
         }
         else
         if ( wCommand == IDM_KILLZEIDON )   // Kill Zeidon
         {
            LPTASK hTask;
            LPTASK lpTask;
            int nResponse = IDYES;

            // See if any tasks are active.
            hTask = AnchorBlock->hFirstTask;
            lpTask = zGETPTR( hTask );

            while ( lpTask )
            {
               if ( hTask != AnchorBlock->hMainTask && IsWindow( (HWND) lpTask->hMainWnd ) )
               {
                  break;
               }

               lpTask = zGETPTR( lpTask->hNextTask );
            }

            if ( lpTask )
            {
               nResponse = MessageBox( hWnd,
                                       "Zeidon Applications are still active.\n"
                                       "If you continue, you will lose unsaved data.\n"
                                       "Do you still want to kill Zeidon?",
                                       "Zeidon Object Services",
                                       MB_ICONEXCLAMATION | MB_YESNO | MB_TASKMODAL );
            }

            if ( nResponse == IDYES )
            {
               zCHAR szFileName[ zMAX_FILENAME_LTH + 1 ];
               zCHAR szTempName[ zMAX_FILENAME_LTH + 1 ];

               SysReadZeidonIni( -1, "[ObjectEngine]", "KillZeidon", szTempName, zsizeof( szTempName ) );
               SysConvertEnvironmentString( szFileName, zsizeof( szFileName ), szTempName );
               if ( szFileName[ 0 ] )
                  WinExec( szFileName, SW_SHOWNORMAL );
            }

            break;
         }
         else
         if ( wCommand == IDM_SHOWINTL )
         {
            LPINTERNATIONAL lpIntl = zGETPTR( AnchorBlock->hInternational );
            if ( lpIntl )
            {
               TraceLineI( "(wa) nCountry :    ", lpIntl->nCountry );
               TraceLineS( "(wa) lpCountry :   ", lpIntl->szCountry );
               TraceLineS( "(wa) lpLanguage :  ", lpIntl->szLanguage );
               TraceLineS( "(wa) lpList :      ", lpIntl->szList );
               TraceLineI( "(wa) nMeasure :    ", lpIntl->nMeasure );
               TraceLineI( "(wa) nTime :       ", lpIntl->nTime );
               TraceLineS( "(wa) lpTime :      ", lpIntl->szTime );
               TraceLineS( "(wa) lp1159 :      ", lpIntl->sz1159 );
               TraceLineS( "(wa) lp2359 :      ", lpIntl->sz2359 );
               TraceLineI( "(wa) nTLZero :     ", lpIntl->nTLZero );
               TraceLineS( "(wa) lpShortDate : ", lpIntl->hShortDate );
               TraceLineS( "(wa) lpLongDate :  ", lpIntl->hLongDate );
               TraceLineS( "(wa) lpTimeFmt :   ", lpIntl->hTimeFmt );
               TraceLineS( "(wa) lpCurrency :  ", lpIntl->szCurrency );
               TraceLineI( "(wa) nCurrency :   ", lpIntl->nCurrency );
               TraceLineI( "(wa) nCurrDigits : ", lpIntl->nCurrDigits );
               TraceLineI( "(wa) nNegCurr :    ", lpIntl->nNegCurr );
               TraceLineS( "(wa) lpThousand :  ", lpIntl->szThousand );
               TraceLineS( "(wa) lpDecimal :   ", lpIntl->szDecimal );
               TraceLineI( "(wa) nDigits :     ", lpIntl->nDigits );
               TraceLineI( "(wa) nLZero :      ", lpIntl->nLZero );
            }
            else
               TraceLineS( "(wa) No international information ", "is available" );
            break;
         }
         else
         if ( wCommand == IDM_CLEARTRACE )    // Empty all trace windows
         {
            UINT k;

            ShowWindow( g_hwndTraceWindow[ g_nTraceWindowDisplayed ],
                        SW_HIDE );
            for ( k = 0; k < g_nTraceWindowCnt; k++ )
               SendMessage( g_hwndTraceWindow[ k ], LB_RESETCONTENT, 0, 0 );

            ShowWindow( g_hwndTraceWindow[ 0 ], SW_SHOW );
            g_nTraceWindowHead      = 0;
            g_nTraceWindowDisplayed = 0;
         }
         else
         if ( wCommand == IDM_SETDBHTRACE )   // Set DBHandler trace level
         {
            DialogBox( hInst, MAKEINTRESOURCE( IDD_SETTRACE ), hWnd, fpSetTrace );
         }
         else
         if ( wCommand == IDM_SETOETRACE )   // Set OE Warning trace
         {
            g_chTraceOE_Warning = g_chTraceOE_Warning ? 0 : 'Y';
            CheckMenuItem( GetMenu( hWnd ), IDM_SETOETRACE,
                           MF_BYCOMMAND | (g_chTraceOE_Warning == 0 ? MF_UNCHECKED : MF_CHECKED) );
         }
         else
         if ( wCommand == IDM_SETZDRTRACE )   // Set ZDr Action trace
         {
            g_chTraceZDrActions = g_chTraceZDrActions ? 0 : 'Y';
            CheckMenuItem( GetMenu( hWnd ), IDM_SETZDRTRACE,
                           MF_BYCOMMAND | (g_chTraceZDrActions == 0 ? MF_UNCHECKED : MF_CHECKED) );
         }
         else
         if ( wCommand == IDM_SETWEBTRACE )   // Set ZDr Action trace
         {
            g_chTraceWebActions = g_chTraceWebActions ? 0 : 'Y';
            CheckMenuItem( GetMenu( hWnd ), IDM_SETWEBTRACE,
                           MF_BYCOMMAND | (g_chTraceWebActions == 0 ? MF_UNCHECKED : MF_CHECKED) );
         }
#ifdef ALLOC_FREE_TRACE
         else
         if ( wCommand == IDM_SETMEMORYTRACE )   // Set Memory trace
         {
            g_chTraceMemory = g_chTraceMemory ? 0 : 'Y';
            AnchorBlock->bTraceMem = g_chTraceMemory ? TRUE : FALSE;
            CheckMenuItem( GetMenu( hWnd ), IDM_SETMEMORYTRACE,
                           MF_BYCOMMAND | (g_chTraceMemory == 0 ? MF_UNCHECKED : MF_CHECKED) );
         }
         else
         if ( wCommand == IDM_TRACEMEMORYALLOCATIONS )
         {
            if ( AnchorBlock->bTraceMem )
               fnListDataspaceLeak( AnchorBlock, 0, 1 );
         }
         else
         if ( wCommand == IDM_TRACEMEMORYDATA )
         {
            if ( AnchorBlock->bTraceMem )
               fnListDataspaceLeak( AnchorBlock, 0, 2 );
         }
         else
         if ( wCommand == IDM_CLEARMEMORYALLOCATIONS )
         {
            if ( AnchorBlock->bTraceMem )
               fnListDataspaceLeak( AnchorBlock, 0, -1 );
         }
#endif
#ifdef LOAD_FREE_TRACE
         else
         if ( wCommand == IDM_SETLOADTRACE )   // Set Load trace
         {
            g_chTraceLoad = g_chTraceLoad ? 0 : 'Y';
            AnchorBlock->bTraceLoad = g_chTraceLoad ? TRUE : FALSE;
            CheckMenuItem( GetMenu( hWnd ), IDM_SETLOADTRACE,
                           MF_BYCOMMAND | (g_chTraceLoad == 0 ? MF_UNCHECKED :  MF_CHECKED) );
         }
         else
         if ( wCommand == IDM_TRACELOADALLOCATIONS )
         {
            if ( AnchorBlock->bTraceLoad )
               fnListDataspaceLeak( AnchorBlock, 0, 1 );
         }
         else
         if ( wCommand == IDM_TRACELOADDATA )
         {
            if ( AnchorBlock->bTraceLoad )
               fnListDataspaceLeak( AnchorBlock, 0, 2 );
         }
         else
         if ( wCommand == IDM_CLEARLOADALLOCATIONS )
         {
            if ( AnchorBlock->bTraceLoad )
               fnListDataspaceLeak( AnchorBlock, 0, -1 );
         }
#endif
         else
         if ( wCommand == IDM_SCROLLTRACE )   // Scroll trace
         {
            g_chScrollTrace = g_chScrollTrace ? 0 : 'Y';
            CheckMenuItem( GetMenu( hWnd ), IDM_SCROLLTRACE,
                           MF_BYCOMMAND | (g_chScrollTrace ? MF_CHECKED : MF_UNCHECKED) );
         }
         else
         if ( wCommand == IDM_TRACEDATASPACE )
         {
            MiListOE_Memory( 0, -1 );  // toggle dataspace alloc/free tracing
         }
         else
         if ( wCommand == IDM_LISTTASKS )   // Display task information
         {
            if ( AnchorBlock )
            {
            // LPTASK lpTask;
            // LPTASK hTask;
               char   szMessage[ 512 ];

#if 1  // DGC 6/13/97  Can't print allocated memory right now.
               LPDATAHEADER    lpDataHeader;
               FreespaceRecord *lpFreespace;
               zULONG ulAlloc;
               zULONG ulUsed;
               zULONG ulFree;

               // Get System available memory
            // lFree = GlobalCompact( 0 );
            // lFree = (lFree / 1024) + 10000;
            // strcpy_s( szMessage, zsizeof( szMessage ), "System Memory Available:" );
            // zltoa( lFree, szMessage + 200, zsizeof( szMessage ) - 200 );
            // strcat_s( szMessage, zsizeof( szMessage ), szMessage + 201 );
            // strcat_s( szMessage, zsizeof( szMessage ), "K" );
            // SysMessageList( szMessage );

               // Display Anchor block memory utilization
               lpDataHeader = (LPDATAHEADER) AnchorBlock;
               ulFree  = 0;
               ulUsed  = 0;
               ulAlloc = lpDataHeader->ulUseableSize; // used memory spaces
               lpFreespace = &lpDataHeader->Freespace;
               while ( lpFreespace )
               {
                  ulFree += lpFreespace->ulFreeLth;
                  lpFreespace = zGETPTR( lpFreespace->hNextFreespace );
               }

               strcpy_s( szMessage, zsizeof( szMessage ), "Anchor Block Alloc: " );
               ulUsed = ulAlloc - ulFree;
               zltoa( ulAlloc, szMessage + 200, zsizeof( szMessage ) - 200 );
               strcat_s( szMessage, zsizeof( szMessage ), szMessage + 200 );
               strcat_s( szMessage, zsizeof( szMessage ), "  Used: " );
               zltoa( ulUsed, szMessage + 200, zsizeof( szMessage ) - 200 );
               strcat_s( szMessage, zsizeof( szMessage ), szMessage + 200 );
               strcat_s( szMessage, zsizeof( szMessage ), "  Free: " );
               zltoa( ulFree, szMessage + 200, zsizeof( szMessage ) - 200 );
               strcat_s( szMessage, zsizeof( szMessage ), szMessage + 200 );
               SysMessageList( szMessage );
#endif

#if 1
               // Display open files.
               DisplayOpenFiles( "ListTasks:", 0 );
#else

            //xTraceDataHeader( (LPDATAHEADER) AnchorBlock, TRUE );

               // Display Tasks and memory utilization.
            // fnStartBrowseOfTaskList( -1, FALSE );  should do this, but can't
               hTask = AnchorBlock->hFirstTask;
               while ( hTask )
               {
               // LPTASKDOMAIN lpTaskDomain;
                  LPTASK       hNextTask;
                  LPSUBTASK    lpSubtask;
               // LPOPENFILE   lpOpenFile;
                  int          nError;

                  lpTask = zGETPTR( hTask );
                  hNextTask = lpTask->hNextTask;
                  if ( lpTask->hNextTask )
                     zsprintf( szMessage, "Task (0x%08x", hTask );
                  else
                     zsprintf( szMessage, "Main Task (0x%08x", hTask );

                  strcat_s( szMessage, ") - Status:" );

                  // Make sure tasks window is still active.
                  nError = 0;
                  if ( lpTask->bShutdown )
                  {
                     strcat_s( szMessage, "SHUTDOWN" );
                  }
                  else
               // if ( IsWindow( (HWND) lpTask->hMainWnd ) )
                  {
                     strcat_s( szMessage, "OK" );
                  }
#if 0
                  else
                  {
#ifdef __WIN32__
                     DWORD dw;

                     strcat_s( szMessage, "ERROR/" );
                     if ( !GetExitCodeProcess( (HANDLE) lpTask, //???
                                               &dw ) ||
                          dw != STILL_ACTIVE )
#else
                     strcat_s( szMessage, "ERROR/" );
                     if ( IsTask( (HTASK) lpTask->lTaskID ) )
#endif
                     {
                        strcat_s( szMessage, "INVALID WINDOW HANDLE!" );
                     }
                     else
                     {
                        strcat_s( szMessage, "DELETED" );
                        nError = 1;
                     }
                  }
#endif

                  SysMessageList( szMessage );
                  strcpy_s( szMessage, zsizeof( szMessage ), "     Title: '" );
                  if ( lpTask->szTaskTitle[ 0 ] )
                     strcat_s( szMessage, zsizeof( szMessage ), lpTask->szTaskTitle );

                  strcat_s( szMessage, zsizeof( szMessage ), "'" );

                  if ( lpTask->szUserId[ 0 ] )
                  {
                     strcat_s( szMessage, zsizeof( szMessage ), "  UserId: " );
                     strcat_s( szMessage, zsizeof( szMessage ), lpTask->szUserId );
                  }

                  SysMessageList( szMessage );

                  if ( nError == 1 )
                  {
                     DeleteTask( lpTask );
                  }
                  else
                  {
                     // Display subtask list.
                     lpSubtask = zGETPTR( lpTask->hFirstSubtask );
                     while ( lpSubtask )
                     {
#if 0  // Change to 1 to get subtask info.  NOT TESTED!
                        LPSUBTASK lpTempSubtask;
                        LPAPP     lpTempApp;

                        strcpy_s( szMessage, zsizeof( szMessage ), "     Subtask:'" );

                        lpSubtaskView = zGETPTR( lpSubtask->hFirstView );
                        while( lpSubtaskView )
                        {
                           if ( lpSubtaskView->hSubtask )
                              break;

                           lpSubtaskView = zGETPTR( lpSubtaskView->hNextView );
                        }

                        lpTempSubtask = zGETPTR( lpSubtaskView->hSubtask );
                        lpTempApp     = zGETPTR( lpTempSubtask->hApp );

                        if ( lpSubtaskView && lpSubtaskView->hViewName )
                        {
                           strcat_s( szMessage, zsizeof( szMessage ), zGETPTR( lpSubtaskView->hViewName ) );
                           strcat_s( szMessage, zsizeof( szMessage ), "'" );
                        }
                        else
                           strcat_s( szMessage, zsizeof( szMessage ), "(unnamed)'" );

                        strcat_s( szMessage, zsizeof( szMessage ), ", Application:'" );
                        strcat_s( szMessage, zsizeof( szMessage ), zGETPTR( lpTempApp->hName ) );
                        strcat_s( szMessage, zsizeof( szMessage ), "'" );
                        SysMessageList( szMessage );

                        // Now report on views
                        lpSubtaskView = zGETPTR( lpSubtask->hFirstView );
                        while( lpSubtaskView )
                        {
                           strcpy_s( szMessage, zsizeof( szMessage ), "        View:'" );
                           if ( lpSubtaskView->hSubtaskView == 0 )
                           {
                              if ( lpSubtaskView->hViewName )
                              {
                                 strcat_s( szMessage, zsizeof( szMessage ), zGETPTR( lpSubtaskView->hViewName ) );
                                 strcat_s( szMessage, zsizeof( szMessage ), "'" );
                              }
                              else
                                 strcat_s( szMessage, zsizeof( szMessage ), "(unnamed)'" );

                              if ( lpSubtaskView->hViewCsr )
                              {
                                 LPVIEWCSR lpViewCsr = zGETPTR( lpSubtaskView->hViewCsr );
                                 LPVIEWOI  lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
                                 LPVIEWOD  lpViewOD  = zGETPTR( lpViewOI->hViewOD );

                                 strcat_s( szMessage, ", zsizeof( szMessage ), Object:'" );
                                 strcat_s( szMessage, zsizeof( szMessage ), lpViewOD->szName );
                                 strcat_s( szMessage, zsizeof( szMessage ), "'" );
                              }

                              SysMessageList( szMessage );
                           }

                           lpSubtaskView = zGETPTR( lpSubtaskView->hNextView );
                        }
#endif
                        lpSubtask = zGETPTR( lpSubtask->hNextSubtask );
                     }

                     // Display open files.
                     DisplayOpenFiles( "ListTasks:", hTask );

#if 0  // DGC 6/13/97  Can't print allocated memory right now.
                     // Display memory utilization.
                     lpDataHeader = zGETPTR( lpTask->hFirstDataHeader );
                     lFree  = 0;
                     lUsed  = 0;
                     lAlloc = 0;
                     while ( lpDataHeader )
                     {
                        lAlloc += lpDataHeader->lCurrentNumberOfEntries;
                        lpFreespace = &lpDataHeader->Freespace;
                        while ( lpFreespace )
                        {
                           lFree += lpFreespace->lFreeLth;
                           lpFreespace = lpFreespace->hNextFreespace;
                        }

                        lpDataHeader = lpDataHeader->hNextDataHeader;
                     }

                     strcpy_s( szMessage, zsizeof( szMessage ), "     Memory Alloc:" );
                     lUsed = lAlloc - lFree;
                     zltoa( lAlloc, szMessage + 200, zsizeof( szMessage ) - 200 );
                     strcat_s( szMessage, zsizeof( szMessage ), szMessage + 200 );
                     strcat_s( szMessage, zsizeof( szMessage ), ", Used:" );
                     zltoa( lUsed, szMessage + 200, zsizeof( szMessage ) - 200 );
                     strcat_s( szMessage, zsizeof( szMessage ), szMessage + 200 );
                     strcat_s( szMessage, zsizeof( szMessage ), ", Free:" );
                     zltoa( lFree, szMessage + 200, zsizeof( szMessage ) - 200 );
                     strcat_s( szMessage, zsizeof( szMessage ), szMessage + 200 );
                     SysMessageList( szMessage );
#endif
                  }

#if 0  //x
                  // Display task domains.
                  strcpy_s( szMessage, zsizeof( szMessage ), "     Domains:" );
                  SysMessageList( szMessage );
                  for ( lpTaskDomain = zGETPTR( lpTask->hFirstTaskDomain );
                        lpTaskDomain;
                        lpTaskDomain = zGETPTR( lpTaskDomain->hNextTaskDomainForTask ) )
                  {
                     LPDOMAIN lpDomain = zGETPTR( lpTaskDomain->hDomain );

                     if ( lpDomain )
                     {
                        char sz[ 20 ];

                        strcpy_s( szMessage, "         Domain Name : " );
                        strcat_s( szMessage, lpDomain->szName );
                        SysMessageList( szMessage );
                        if ( *lpDomain->szDomainOper )
                        {
                           strcpy_s( szMessage, "         Domain Oper : " );
                           strcat_s( szMessage, lpDomain->szDomainOper );
                           SysMessageList( szMessage );
                        }

                        zltoa( lpDomain->lApDmTok, sz, zsizeof( sz ) );
                        strcpy_s( szMessage, "         Domain Token: " );
                        strcat_s( szMessage, sz );
                        SysMessageList( szMessage );
                        zltoa( (zLONG) lpDomain, sz, zsizeof( sz ) );
                        strcpy_s( szMessage, "         Domain Ptr  : " );
                        strcat_s( szMessage, sz );
                        SysMessageList( szMessage );
                        SysMessageList( " " );
                     }
                  }
#endif
                  // Look for another task.
                  hTask = hNextTask;
               }

            // fnEndBrowseOfTaskList( FALSE );  should do this but can't
#endif
            }
         }
         else
         if ( wCommand == IDM_LISTMUTEXSTATUS )
         {
            char szMsg[ 4000 ];

            SysMutexQueryStatus( );
            TraceLineS( "", "" );
            MiListOE_Memory( 0, 0 );
            SysDescribeZeidonPageTable( szMsg, zsizeof( szMsg ) );
            TraceLineS( " Page table info - ", szMsg );
         }
         else
         if ( wCommand == IDM_LISTVOBJS )   // Display objects
         {
            if ( AnchorBlock )
            {
               LPAPP    lpApp;
               LPVIEWOD lpViewOD;
               char szMessage[ 160 ];

               lpApp = zGETPTR( AnchorBlock->hFirstApp );
               while ( lpApp )
               {
                  strcpy_s( szMessage, zsizeof( szMessage ), "Application:'" );
                  if ( *lpApp->szName )
                     strcat_s( szMessage, zsizeof( szMessage ), lpApp->szName );

                  strcat_s( szMessage, zsizeof( szMessage ), "'" );
                  SysMessageList( szMessage );
                  lpViewOD = zGETPTR( lpApp->hFirstViewOD );
                  while ( lpViewOD )
                  {
                     strcpy_s( szMessage, zsizeof( szMessage ), "  View Object:'" );
                     if ( *lpViewOD->szName )
                        strcat_s( szMessage, zsizeof( szMessage ), lpViewOD->szName );

                     strcat_s( szMessage, zsizeof( szMessage ), "'" );
                     SysMessageList( szMessage );
                     lpViewOD = zGETPTR( lpViewOD->hNextViewOD );
                  }

                  lpApp = zGETPTR( lpApp->hNextApp );
               }
            }
         }
         else
         if ( wCommand == IDM_RESETTIMEOUT )
         {
            if ( g_lTimeOut )
               SysGetDateTime( g_szTimeStamp, zsizeof( g_szTimeStamp ) );

            return( 0 );
         }
         else
         if ( wCommand == IDM_IDLE )
         {
            if ( g_lTimeOut && g_uIdleTimerId == 0 )
            {
               SysGetDateTime( g_szTimeStamp, zsizeof( g_szTimeStamp ) );
               TraceLine( "OE Setting Idle Timer for hWnd: 0x%08x   g_hWndMainFrame: 0x%08x  Id: %d",
                          hWnd, g_hWndMainFrame, g_nIdIdleEvt );
               g_uIdleTimerId = SetTimer( hWnd, g_nIdIdleEvt, 30000, 0 );  // 30000 ==> 30 seconds
            }

            return( 0 );
         }
         else
         if ( wCommand == IDM_GETOEWARNINGTRACE )
            return( (zLONG) g_chTraceOE_Warning );
         else
         if ( wCommand == IDM_GETACTIONTRACE )
            return( (zLONG) g_chTraceZDrActions );
         else
         if ( wCommand == IDM_GETWEBTRACE )
            return( (zLONG) g_chTraceWebActions );
         else
         if ( wCommand == IDM_GETMEMORYTRACE )
            return( (zLONG) g_chTraceMemory );
         else
         if ( wCommand == IDM_GETTRACELOGFILE )
            return( (zLONG) g_hLogFile );
         else
         if ( wCommand == IDM_GETOEMAINHWND )
            return( (zLONG) g_hWndMainFrame );
         else
         if ( wCommand == IDM_GETOELISTHWND )
            return( (zLONG) g_hwndTraceWindow[ g_nTraceWindowHead ] );
         else
         if ( wCommand == IDM_GETTRACELIMIT )
            return( (zLONG) g_uTraceLineLimit );
         else
         if ( wCommand == IDM_GETSCROLLTRACE )
            return( (zLONG) g_chScrollTrace );
         else
         if ( wCommand == IDM_GETPRINTPREVIEW )
            return( (zLONG) g_chPrintPreview );
         else
         if ( wCommand == IDM_GETPRINTDIALOG )
            return( (zLONG) g_chPrintDialog );
         else
         if ( wCommand == IDM_GETFINDSTRING )
         {
            strcpy_s( (zPCHAR) lParam, zsizeof( g_szFindString ), g_szFindString );
            return( zstrlen( g_szFindString ) );
         }
         else
         if ( wCommand >= IDM_TRACEWINDOW01 && wCommand <= IDM_TRACEWINDOW20 )
         {
            UINT idx = wCommand - IDM_TRACEWINDOW01;
            UINT iDiff;
            UINT nNewTraceWindow;
            UINT nOldTraceWindow;

            nNewTraceWindow = (g_nTraceWindowHead + g_nTraceWindowCnt - idx) % g_nTraceWindowCnt;

            // If user selected the window already displayed then don't do anything.
            if ( nNewTraceWindow == g_nTraceWindowDisplayed )
               break;

            // Find the difference between the displayed window and the head.
            iDiff = ( g_nTraceWindowDisplayed + g_nTraceWindowCnt - g_nTraceWindowHead ) % g_nTraceWindowCnt;

            // Determine the old trace window index.
            nOldTraceWindow = ( g_nTraceWindowCnt - iDiff ) % g_nTraceWindowCnt;

            // Turn off the check mark...we will no longer be displaying the current window.
            CheckMenuItem( GetMenu( hWnd ), IDM_TRACEWINDOW01 + nOldTraceWindow,  MF_BYCOMMAND | MF_UNCHECKED );

            // Make the current window invisible.
            ShowWindow( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], SW_HIDE );

            // Turn on the check for the window the user wants.
            CheckMenuItem( GetMenu( hWnd ), wCommand, MF_BYCOMMAND | MF_CHECKED );

            g_nTraceWindowDisplayed = nNewTraceWindow;

            // Make the new current window visible.
            ShowWindow( g_hwndTraceWindow[ g_nTraceWindowDisplayed ], SW_SHOW );
         }

         break;
      }

      case WM_QUERYENDSESSION:
      case WM_CLOSE:
         // Close message, if any zeidon tasks are still registered,
         // prompt whether to send a close message to each one and
         // try and bring it down. If either the user says no to
         // automatically closing tasks or any tasks rejects the close
         // message, reject the close and set focus to the first
         // remaining active task.
         // When we receive a WM_QUERYENDSESSION, the user is shutting
         // down Windows.  If any Zeidon tasks are still active, then
         // don't permit Windows to shut down.
         if ( szLogFileName[ 0 ] )
            SysUpdateZeidonIni( szlWorkstation, "LogFile", szLogFileName );

         if ( AnchorBlock )       // Anchor block OK?
         {
            LPTASK hTask;
            LPTASK lpTask;
            LPTASK lpTaskTemp;
            int nResponse = IDNO;
            HANDLE hTermMutex;

            // Create a mutex.  Code in kzoesyaa.c will check to see if this
            // mutex exists during registration.  If it does then Core will
            // fail the registration.  This makes sure that core is completely
            // shut down before the registration can start.  Note that we'll
            // let the Win32 OS clean up the mutex for us when we shut down.
            hTermMutex = CreateMutex( NULL, FALSE, "KZOENGWA - Termination" );

            // First, see if any tasks are active
            hTask = AnchorBlock->hFirstTask;
            lpTask = zGETPTR( hTask );

            // If the logfile is still open then close it.
            if ( lpTask && g_hLogFile != -1 )
            {
               fnSysCloseFile( lpTask, g_hLogFile, 0 );
               g_hLogFile = -1;
            }

            while ( lpTask )
            {
               if ( hTask != AnchorBlock->hMainTask &&
                    IsWindow( (HWND) lpTask->hMainWnd ) )
               {
                  break;
               }

               lpTask = zGETPTR( lpTask->hNextTask );
            }

            if ( lpTask == 0 )
               lpTaskTemp = zGETPTR( AnchorBlock->hFirstTask );
            else
               lpTaskTemp = lpTask;

            if ( uMsg == WM_CLOSE )
            {
               char  szIniName[ 260 ];
               char  szFileName[ 260 ];
               char  szTempName[ 260 ];
               char  szBuffer[ zsizeof( "-2147483647," ) * 10 ];
               WINDOWPLACEMENT wp;

               wp.length = sizeof( wp );
               if ( GetWindowPlacement( hWnd, &wp ) )
               {
                  // write window placement to Zeidon.ini file.

                  wsprintf( szBuffer, szPlaceFormat,
                            wp.flags, wp.showCmd,
                            wp.ptMinPosition.x, wp.ptMinPosition.y,
                            wp.ptMaxPosition.x, wp.ptMaxPosition.y,
                            wp.rcNormalPosition.left,
                            wp.rcNormalPosition.top,
                            wp.rcNormalPosition.right,
                            wp.rcNormalPosition.bottom );
               }
               else
                  szBuffer[ 0 ] = 0;

            // SysReadZeidonIni( -1, szlWorkstation, "LocalDir", szTempName );
               GetEnvironmentVariable( "ZEIDON", szIniName, zsizeof( szIniName ) );
               strcat_s( szIniName, zsizeof( szIniName ), "\\zeidon.ini" );
               GetPrivateProfileString( "Workstation", "LocalDir", "", szTempName, zsizeof( szTempName ), szIniName );
               SysConvertEnvironmentString( szFileName, zsizeof( szFileName ), szTempName );
               if ( szFileName[ 0 ] )
               {
                  SysAppendcDirSep( szFileName );
                  strcat_s( szFileName, zsizeof( szFileName ), "ZeidonRT.ini" );
               }
               else
                  strcpy_s( szFileName, zsizeof( szFileName ), szIniName );

               WritePrivateProfileString( "ObjectEngine", // section name
                                          "WindowPos",    // key name
                                          szBuffer,       // string to add
                                          szFileName );   // ini filename
               zltoa( g_uTraceLineLimit, szBuffer, zsizeof( szBuffer ) );
               WritePrivateProfileString( "ObjectEngine", "LineLimit", szBuffer, szFileName );
               WritePrivateProfileString( "ObjectEngine", "FindString", g_szFindString, szFileName );
               szBuffer[ 1 ] = 0;
               szBuffer[ 0 ] = g_chScrollTrace;
               WritePrivateProfileString( "ObjectEngine", "ScrollTrace", szBuffer, szFileName );
               szBuffer[ 0 ] = g_chPrintPreview;
               WritePrivateProfileString( "ObjectEngine", "PrintPreview", szBuffer, szFileName );
               szBuffer[ 0 ] = g_chPrintDialog;
               WritePrivateProfileString( "ObjectEngine", "PrintDialog", szBuffer, szFileName );
               szBuffer[ 0 ] = g_chTraceOE_Warning;
               WritePrivateProfileString( "ObjectEngine", "TraceOE_Warning", szBuffer, szFileName );
               szBuffer[ 0 ] = g_chTraceZDrActions;
               WritePrivateProfileString( "ObjectEngine", "TraceAction", szBuffer, szFileName );
               szBuffer[ 0 ] = g_chTraceWebActions;
               WritePrivateProfileString( "ObjectEngine", "TraceWeb", szBuffer, szFileName );
               if ( AnchorBlock && AnchorBlock->bShowTaskID )
                  szBuffer[ 0 ] = 'Y';
               else
                  szBuffer[ 0 ] = 0;

               WritePrivateProfileString( "ObjectEngine", "ShowTaskID", szBuffer, szFileName );
            }

            if ( uMsg == WM_QUERYENDSESSION )
            {
               if ( lpTask )
               {
                  // There are Zeidon tasks running.  Determine if the user
                  // really wants to shut down.
                  nResponse = MessageBox( hWnd,
                                          "Zeidon Applications are still active.\n"
                                          "Do you still want to shut down?",
                                          "Zeidon Object Services",
                                          MB_ICONEXCLAMATION | MB_YESNO | MB_TASKMODAL );
                  if ( nResponse == IDNO )
                  {
                     ReleaseMutex( hTermMutex );
                     CloseHandle( hTermMutex );
                     return( FALSE );  // User doesn't want to shut down.
                  }
               }

               return( TRUE );   // Allow shutdown.
            }

#define zZEIDON_DRIVER_MSG                                   0x4000
#define zZEIDON_COMMUNICATE_OE              (zZEIDON_DRIVER_MSG + 1)
#define zZEIDON_POSTED_CLOSE                (zZEIDON_DRIVER_MSG + 2)

            // If any tasks are active, prompt for shutdown
            if ( lpTask )
            {
               MessageBeep( 0 );
#if 0
               nResponse = IDYES;
               MessageBox( hWnd,
                           "Zeidon Applications are still active.\n"
                           "Please close them before exiting!",
                           "Zeidon Object Services",
                           MB_TASKMODAL | MB_ICONEXCLAMATION | MB_OK );
#else
               nResponse = MessageBox( hWnd,
                                       "Zeidon Applications are still active.\n"
                                       "Do you wish to try and close them?",
                                       "Zeidon Object Services",
                                       MB_ICONQUESTION | MB_YESNO | MB_TASKMODAL | MB_DEFBUTTON2 );
               if ( nResponse == IDYES )
               {
                  nResponse = IDNO;
                  lpTask = zGETPTR( AnchorBlock->hFirstTask );
                  while ( TRUE )
                  {
                     LPTASK lpTask2;

                     if ( lpTask == 0 )
                        break;

                     // Chain forward 1 so close can remove this task
                     lpTask2 = zGETPTR( lpTask->hNextTask );
                     if ( zGETHNDL( lpTask ) != AnchorBlock->hMainTask && IsWindow( (HWND) lpTask->hMainWnd ) &&
                          SendMessage( (HWND) lpTask->hMainWnd, zZEIDON_COMMUNICATE_OE, 0, -1L ) == -1 )
                     {
                        nResponse = IDYES;
                     // TraceLineI( "OE IDYES for Task: ", lpTask->lTaskID );
                        PostMessage( (HWND) lpTask->hMainWnd, zZEIDON_POSTED_CLOSE, 0, 0L );
                     }
                  // else
                  //    TraceLineI( "OE IDNO for Task: ", lpTask->lTaskID );

                     lpTask = lpTask2;
                  }
               }
               else
               {
                  ReleaseMutex( hTermMutex );
                  CloseHandle( hTermMutex );
                  SetActiveWindow( (HWND) lpTask->hMainWnd );
                  return( 1 );
               }
#endif
            }

            // If an attempt was made to close applications, then see if all applications have left.
            lpTask = zGETPTR( AnchorBlock->hFirstTask );
            if ( nResponse == IDYES )
            {
               // We stay up so other tasks have time to come down cleanly
// Stay up!    PostMessage( hWnd, WM_CLOSE, 0, 0L );
               return( 0 );
            }
         }

         break;

      case WM_DESTROY:                  // message: window being destroyed
      {
         LPTASK lpTask = zGETPTR( AnchorBlock->hFirstTask );
         // It's OK to leave, Shutdown Object Services

         if ( g_uKillTimerId )
            KillTimer( hWnd, g_uKillTimerId );

#ifdef __WIN32__
         DetachSysTray( ); // remove Icon from systray
         DestroyWindow( g_hThreadWnd );
#endif

         FreeProcInstance( fpAbout );
         FreeProcInstance( fpLogon );
         FreeProcInstance( fpSetTrace );
         FreeProcInstance( fpLogTrace );
         FreeProcInstance( fpTraceList );
         FreeProcInstance( fpLineLimit );
         FreeProcInstance( fpFindString );
         FreeProcInstance( fpShowDLL );
         FreeProcInstance( fpSqlServerErrHandler );
         FreeProcInstance( fpSqlServerMsgHandler );

         lpTask->bOE_TaskShutdown = TRUE;
         FreeAnchorBlock( lpTask );
         AnchorBlock = 0;

         PostQuitMessage( 0 );
         break;
      }

      case WM_WININICHANGE:
         // If multiple sections or the Intl section of the win.ini
         // file has been updated, go rebuild the international info
         if ( lParam == 0L || zstrcmpi( szlINTL, (zPCHAR) lParam ) == 0 )
         {
            zPVOID            hNewInt;
            LPINTERNATIONAL   lpOldInt;

            // Get possible changes
            if ( (hNewInt = SysCreateInternational( )) != 0 )
            {
               TraceLineS( "(wa) changing international info - ", (zPCHAR) lParam );

               // switch pointers
               lpOldInt = zGETPTR( AnchorBlock->hInternational );
               AnchorBlock->hInternational = hNewInt;

               // free old values
               SysFreeInternational( lpOldInt );
            }
         }

         break;

      case WM_WRITELOG:
         {
            SYSTEMTIME SysTime;
            LPTASK hTask;
            LPTASK lpTask;
            char szFileName[ 256 ];
            long hLogFile = g_hLogFile;

            GetLocalTime( &SysTime );

            // szFileName looks like this:  YYYYMMDDhhmmss
            sprintf_s( szFileName, zsizeof( szFileName ), "%04d%02d%02d%02d%02d%02d.log",
                       SysTime.wYear, SysTime.wMonth,
                       SysTime.wDay, SysTime.wHour,
                       SysTime.wMinute, SysTime.wSecond );

            // First, see if any tasks are active
            hTask = AnchorBlock->hFirstTask;
            lpTask = zGETPTR( hTask );

            if ( lpTask && szFileName[ 0 ] )
            {
               if ( (g_hLogFile = fnSysOpenFile( lpTask, szFileName, COREFILE_CREATE )) != -1 )
               {
                  char szTraceText[ 512 ];

                  // Send message that log file opened.
                  strcpy_s( szTraceText, zsizeof( szTraceText ), "(ng) Log file Opened '" );
                  strcat_s( szTraceText, zsizeof( szTraceText ), szFileName );
                  strcat_s( szTraceText, zsizeof( szTraceText ), "'" );
                  SysMessageList( szTraceText );

                  WriteTraceToLog( lpTask );
               }
            }

            g_hLogFile = hLogFile;
         }

         return( 0 );

      case WM_QUERYALIVE:
         return( -1 );   // yup ... we're still here

      default:
         if ( uMsg == g_wOENG_Message )
            fnProcessOENG_Message( hWnd, uMsg, wParam, lParam );

         break; // return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
}

/////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: fnProcessOENG_Message
//
// PURPOSE:  Process messages from Object Engine DLL to allocate
//           memory from the main task and ??????????
//
/////////////////////////////////////////////////////////////////////////////
void
fnProcessOENG_Message( HWND hWnd, unsigned uMsg,
                       WPARAM wParam, LPARAM lParam )
{
#ifdef __WIN32__

   // We'll let core handle it.
   ProcessZeidonMessage( wParam, lParam );
   return;

#else

   // The only thing we handle in Win 3.x is conversion from decimal to string.

   zPDECIMAL pdDecimal  = (zPDECIMAL) lParam;
   zSHORT    nPrecision = (zSHORT) wParam;
   zCHAR     szStr[ 100 ] = "abcdefghijklmnopqrstuvwxyz";
   zPCHAR    pszReturn;

// SysMessageBox( "DGC", "processing message", 1 );

   pszReturn = (zPCHAR) ((zLONG) lParam + zsizeof( zPDECIMAL ));

   if ( nPrecision > 0 )
      zsprintf( szStr, "%*Lf", (int) wParam, *pdDecimal );
   else
      zsprintf( szStr, "%Lf", *pdDecimal );

   strcpy_s( pszReturn, szStr );

#endif
}

/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION : AboutDlgProc (HWND, unsigned, MPARAM, MPARAM )
//
//  PURPOSE  : Dialog function for the "About..." menu item dialog.
//
/////////////////////////////////////////////////////////////////////////////
long zPASCAL
AboutDlgProc( HWND hDlg,                // window handle
              unsigned uMsg,            // type of message
              WPARAM   wParam,          // additional information
              LPARAM   lParam )         // additional information
{
   switch ( uMsg )
   {
      case WM_COMMAND:
         EndDialog( hDlg, TRUE );

         // fall through

      case WM_INITDIALOG:
         return( TRUE );

      default:
         return( FALSE );
   }
}

/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:  InitApplication( HANDLE hInatsnce )
//
//  PURPOSE:  Saves instance handle and creates main window
//
/////////////////////////////////////////////////////////////////////////////
BOOL
InitApplication( HANDLE hInstance )     // current instance
{
    WNDCLASS  wc;

    // Fill in window class structure with parameters that describe the main window.

    wc.style = 0;                     // Class style(s).
    wc.lpfnWndProc = MainWndProc;     // Function to retrieve messages for
                                      // windows of this class.
    wc.cbClsExtra = 0;                // No per-class extra data.
    wc.cbWndExtra = 0;                // No per-window extra data.
    wc.hInstance = hInstance;         // Application that owns the class.
    wc.hIcon = LoadIcon( hInstance, "ZEIDON" );
    wc.hCursor = LoadCursor( 0, IDC_ARROW );
    wc.hbrBackground = GetStockObject( WHITE_BRUSH );
    wc.lpszMenuName =  0;             // Name of menu resource in .RC file.
    wc.lpszClassName = szClassName;   // Name used in call to CreateWindow.

#ifdef __WIN32__
   // For Win32 we need to create an invisible window to handle Zeidon msgs.

   if ( !RegisterClass( &wc ) )
      return( FALSE );

    wc.style = 0;                       // Class style(s).
    wc.lpfnWndProc = MainThrdWndProc;   // Function to retrieve messages.
    wc.cbClsExtra = 0;                  // No per-class extra data.
    wc.cbWndExtra = 0;                  // No per-window extra data.
    wc.hInstance  = hInstance;          // Application that owns the class.
    wc.hIcon      = 0;
    wc.lpszMenuName =  0;               // Name of menu resource in .RC file.
    wc.lpszClassName = szThreadClassName; // Name used in call to CreateWindow.

#endif

    // Register the window class and return success/failure code.

    return( RegisterClass( &wc ));
}

/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:  InitInstance( HANDLE, int )
//
//  PURPOSE:  Saves instance handle and creates main window
//
//  COMMENTS:
//
//      This function is called at initialization time for every instance of
//      this application.  This function performs initialization tasks that
//      cannot be shared by multiple instances.
//
//      In this case, we save the instance handle in a static variable and
//      create and display the main program window.
//
/////////////////////////////////////////////////////////////////////////////
HWND
InitInstance( HANDLE hInstance, // Current instance identifier.
              int  nCmdShow )   // Param for first ShowWindow( ) call.
{
   zVIEW        vDbhWork;
   RECT         rect;
   HDC          hDC;  // handle to the context display
   TEXTMETRIC   txtm; // characteristics of text chars
   UINT         i;
   int          nHeight, nPosY;
   int          nWidth, nPosX;
// FARPROC      lpFarProc[ 2 ];
   LPTASK       lpTask;
   HMENU        hMenu;
   HWND         hProcessWnd;
   WINDOWPLACEMENT wp;
   char         szFileName[ zMAX_FILENAME_LTH + 1 ];
   char         szTempName[ zMAX_FILENAME_LTH + 1 ];
   char         szBuffer[ 256 ];
   LPTRACINGFLAGS lpTraceFlags;
   DWORD dwStyle = 0;

   // Save the instance handle in static variable, which will be used in
   // many subsequence calls from this application to Windows.

   hInst = hInstance;
   zmemset( szFileName, 0, zMAX_FILENAME_LTH + 1 );

   // Get the dimensions of the screen.
   nWidth = (GetSystemMetrics( SM_CXSCREEN ) * 3) / 4;
   nHeight = (GetSystemMetrics( SM_CYSCREEN ) * 3) / 4;
   nPosX =  GetSystemMetrics( SM_CXSCREEN ) / 8;
   nPosY =  GetSystemMetrics( SM_CYSCREEN ) / 8;

   // Create a main window for this application instance.
   hMenu = LoadMenu( hInstance, "KZOENGWA" );
   g_hWndMainFrame = CreateWindow(
      szClassName,                    // see RegisterClass( ) call
      "Zeidon Object Services",       // text for window title bar
      WS_OVERLAPPEDWINDOW,            // window style
      nPosX,                          // default horizontal position
      nPosY,                          // default vertical position
      nWidth,                         // default width
      nHeight,                        // default height
      0,                              // overlapped windows have no parent
      hMenu,                          // menu for trace window
      hInstance,                      // this instance owns this window
      0 );                            // pointer not needed

   // If window could not be created, return "failure".
   if ( g_hWndMainFrame == 0 )
      return( FALSE );

   GetClientRect( g_hWndMainFrame, &rect );

   // First, create the listbox that will receive TraceLine messages from core.

#if 0
   g_hWndLB = CreateWindow( WC_LISTVIEW,
                            "Trace Window",
                         // WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
                            WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CAPTION | LVS_SINGLESEL,
      rect.left,                      // default horizontal position
      rect.top,                       // default vertical position
      (rect.right - rect.left),       // default width
      (rect.bottom - rect.top),       // default height
      g_hWndMainFrame,                // parent Window
      0,                              // use the window class menu
      hInstance,                      // this instance owns this window
                         // 0, 0,
                         // rcClient.right - rcClient.left,
                         // rcClient.bottom - rcClient.top,
                         // hwndParent,
                         // (HMENU)IDM_CODE_SAMPLES,
                         // g_hInst,
                            0 );

#else

   g_hWndLB = CreateWindow(
      "ListBox",                      // see RegisterClass( ) call
      "Trace Window",                 // text for window title bar
      WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CAPTION | LBS_NOINTEGRALHEIGHT,
      rect.left,                      // default horizontal position
      rect.top,                       // default vertical position
      (rect.right - rect.left),       // default width
      (rect.bottom - rect.top),       // default height
      g_hWndMainFrame,                // parent Window
      0,                              // use the window class menu
      hInstance,                      // this instance owns this window
      0                               // pointer not needed
   );
#endif

   if ( strlen( g_szZeidonEnvDirectory ) > 0 )
      SetEnvironmentVariable( "ZEIDON", g_szZeidonEnvDirectory );

   GetEnvironmentVariable( "ZEIDON", szFileName, zMAX_FILENAME_LTH + 1 );
   strcat_s( szFileName, zsizeof( szFileName ), "\\zeidon.ini" );
   g_nTraceWindowCnt = GetPrivateProfileInt( "ObjectEngine", "TraceWindows", 2, szFileName );
   if ( g_nTraceWindowCnt < 1 )
      g_nTraceWindowCnt = 2;
   else
   if ( g_nTraceWindowCnt > MAX_TRACE_WINDOWS )
      g_nTraceWindowCnt = MAX_TRACE_WINDOWS;

   // Create the trace windows in the circuluar list.
   for ( i = 0; i < g_nTraceWindowCnt; i++ )
   {
      g_hwndTraceWindow[ i ] = CreateWindow(
         "ListBox",                      // see RegisterClass( ) call
         "Trace Window",                 // text for window title bar
         WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CAPTION | LBS_NOINTEGRALHEIGHT,
         rect.left,                      // default horizontal position
         rect.top,                       // default vertical position
         (rect.right - rect.left),       // default width
         (rect.bottom - rect.top),       // default height
         g_hWndMainFrame,                // parent Window
         0,                              // use the window class menu
         hInstance,                      // this instance owns this window
         0                               // pointer not needed
      );

      SendMessage( g_hwndTraceWindow[ i ], WM_SETFONT, (WPARAM) GetStockObject( SYSTEM_FIXED_FONT ), 0 );

      hDC = GetDC( g_hwndTraceWindow[ i ] );         // get the display context
      GetTextMetrics( hDC, &txtm );
      ReleaseDC ( g_hwndTraceWindow[ i ], hDC );     // free the resource
      SendMessage( g_hwndTraceWindow[ i ], LB_SETHORIZONTALEXTENT, txtm.tmMaxCharWidth * 256, 0L );
   }

   hMenu = GetMenu( g_hWndMainFrame );

   // Delete the unused menu items.
   for ( i = g_nTraceWindowCnt; i < MAX_TRACE_WINDOWS; i++ )
      DeleteMenu( hMenu, IDM_TRACEWINDOW01 + i, MF_BYCOMMAND );

   ShowWindow( g_hwndTraceWindow[ 0 ], SW_SHOW );
   g_nTraceWindowHead      = 0;
   g_nTraceWindowDisplayed = 0;

   CheckMenuItem( hMenu, IDM_TRACEWINDOW01, MF_BYCOMMAND | MF_CHECKED );

   // Make proc instances for message procedures
   fpAbout = (zFARPROC_CALLBACK) MakeProcInstance( (FARPROC) AboutDlgProc, hInstance );
   fpLogon = (zFARPROC_CALLBACK) MakeProcInstance( (FARPROC) LogonDlgProc, hInstance );
   fpSetTrace = (zFARPROC_CALLBACK) MakeProcInstance( (FARPROC) SetTraceDlgProc, hInstance );
   fpLogTrace = (zFARPROC_CALLBACK) MakeProcInstance( (FARPROC) LogTraceDlgProc, hInstance );
   fpTraceList = (zFARPROC_CALLBACK) MakeProcInstance( (FARPROC) TraceListWndProc, hInstance );
   fpLineLimit = (zFARPROC_CALLBACK) MakeProcInstance( (FARPROC) LimitDlgProc, hInstance );
   fpFindString = (zFARPROC_CALLBACK) MakeProcInstance( (FARPROC) FindStringDlgProc, hInstance );
   fpShowDLL = (zFARPROC_CALLBACK)  MakeProcInstance( (FARPROC) ShowDLLDlgProc, hInstance );

   // Change the WndProc for the list window so we can trap LB_ADDSTRING
   // messages and write them to the trace log (if open)
   fpDfltListWndProc = (zFARPROC_CALLBACK) SetWindowLong( g_hWndLB, GWL_WNDPROC, (DWORD) TraceListWndProc );

   // Register message of Object Services.
   g_wOENG_Message = RegisterWindowMessage( "KZOESRVC" );

#ifdef __WIN32__
   // We need to start up the message loop thread.
   g_bThreadStarted = FALSE;

   // security, stack size, start address, arglist, initflag, thread address
   g_hThread = _beginthreadex( NULL, 0, fnThreadProc, 0, 0, &g_dwThreadID );
   if ( g_hThread )
      CloseHandle( (HANDLE) g_hThread );

   // Now wait until the thread has finished its initialization.
   while ( g_bThreadStarted == FALSE )
      Sleep( 10 );

   hProcessWnd = g_hThreadWnd;
#else
   hProcessWnd = g_hWndMainFrame;
#endif

   // Initialize Object services anchor block
   AnchorBlock = InitializeAnchorBlock( (zLONG) hInstance,
                                        (zLONG) hProcessWnd,
                                        (zLONG) g_hWndLB,
                                        (zLONG) g_wOENG_Message );

   // If initialization failed, destroy the instance and return.
   if ( AnchorBlock == 0 || AnchorBlock == (LPANCHOR) zCALL_ERROR )
   {
      DestroyWindow( g_hWndMainFrame );
      return( 0 );
   }

   AnchorBlock->OS_Data.hMainWindow = (zLONG) g_hWndMainFrame;
   lpTask            = zGETPTR( AnchorBlock->hMainTask );
   g_vSystemTaskView = zGETPTR( lpTask->hFirstView );

   TraceLineS( "----Zeidon configuration file: ", szFileName );
   SysReadZeidonIni( -1, szlWorkstation, "LocalDir", szTempName, zsizeof( szTempName ) );
   SysConvertEnvironmentString( szFileName, zsizeof( szFileName ), szTempName );
   if ( szFileName[ 0 ] )
   {
      SysAppendcDirSep( szFileName );
      strcat_s( szFileName, zsizeof( szFileName ), "ZeidonRT.ini" );
      TraceLineS( "--LocalDir configuration file: ", szFileName );
      GetPrivateProfileString( "ObjectEngine", "LineLimit", "", szBuffer, zsizeof( szBuffer ), szFileName );
      if ( szBuffer[ 0 ] )
      {
         g_uTraceLineLimit = atoi( szBuffer );
         if ( g_uTraceLineLimit == 0 )
         {
            AnchorBlock->bTraceCnt = FALSE;
            SendMessage( g_hWndLB, LB_RESETCONTENT, 0, 0L );
         }
      }

      GetPrivateProfileString( "ObjectEngine", "FindString", "", szBuffer, zsizeof( szBuffer ), szFileName );
      strcpy_s( g_szFindString, zsizeof( g_szFindString ), szBuffer );
      GetPrivateProfileString( "ObjectEngine", "ScrollTrace", "", szBuffer, zsizeof( szBuffer ), szFileName );
      if ( szBuffer[ 0 ] )
         g_chScrollTrace = szBuffer[ 0 ];

      GetPrivateProfileString( "ObjectEngine", "PrintPreview", "", szBuffer, zsizeof( szBuffer ), szFileName );
      if ( szBuffer[ 0 ] )
      {
         g_chPrintPreview = szBuffer[ 0 ];
         if ( g_chPrintPreview == 'Y' )
            g_chPrintPreview = '0';
      }

      GetPrivateProfileString( "ObjectEngine", "PrintDialog", "", szBuffer, zsizeof( szBuffer ), szFileName );
      if ( szBuffer[ 0 ] )
         g_chPrintDialog = szBuffer[ 0 ];

      GetPrivateProfileString( "ObjectEngine", "TraceOE_Warning", "", szBuffer, zsizeof( szBuffer ), szFileName );
      if ( szBuffer[ 0 ] )
         g_chTraceOE_Warning = szBuffer[ 0 ];

      GetPrivateProfileString( "ObjectEngine", "TraceAction", "", szBuffer, zsizeof( szBuffer ), szFileName );
      if ( szBuffer[ 0 ] )
         g_chTraceZDrActions = szBuffer[ 0 ];

      GetPrivateProfileString( "ObjectEngine", "TraceWeb", "", szBuffer, zsizeof( szBuffer ), szFileName );
      if ( szBuffer[ 0 ] )
         g_chTraceWebActions = szBuffer[ 0 ];

      GetPrivateProfileString( "ObjectEngine", "ShowTaskID", "", szBuffer, zsizeof( szBuffer ), szFileName );
      if ( szBuffer[ 0 ] )
         AnchorBlock->bShowTaskID = 1;

      lpTraceFlags = GetTracingFlags( );

      GetPrivateProfileString( "ObjectEngine", "ShowOpenFile", "", szBuffer, zsizeof( szBuffer ), szFileName );
      lpTraceFlags->bOpenFile = (toupper( szBuffer[ 0 ] ) == 'Y') ? TRUE : FALSE;

      GetPrivateProfileString( "ObjectEngine", "ShowOI_Times", "", szBuffer, zsizeof( szBuffer ), szFileName );
      lpTraceFlags->bOI_Times = (toupper( szBuffer[ 0 ] ) == 'Y') ? TRUE : FALSE;

      GetPrivateProfileString( "ObjectEngine", "ShowTaskMsgs", "", szBuffer, zsizeof( szBuffer ), szFileName );
      lpTraceFlags->bTaskMsgs = (toupper( szBuffer[ 0 ] ) == 'Y') ? TRUE : FALSE;
   }
   else
   {
      SysReadZeidonIni( -1, "[ObjectEngine]", "LineLimit", szBuffer, zsizeof( szBuffer ) );
      if ( szBuffer[ 0 ] )
      {
         g_uTraceLineLimit = atoi( szBuffer );
         if ( g_uTraceLineLimit == 0 )
         {
            AnchorBlock->bTraceCnt = FALSE;
            SendMessage( g_hWndLB, LB_RESETCONTENT, 0, 0L );
         }
      }

      SysReadZeidonIni( -1, "[ObjectEngine]", "FindString", szBuffer, zsizeof( szBuffer ) );
      strcpy_s( g_szFindString, zsizeof( g_szFindString ), szBuffer );
      SysReadZeidonIni( -1, "[ObjectEngine]", "ScrollTrace", szBuffer, zsizeof( szBuffer ) );
      if ( szBuffer[ 0 ] )
         g_chScrollTrace = szBuffer[ 0 ];

      SysReadZeidonIni( -1, "[ObjectEngine]", "PrintPreview", szBuffer, zsizeof( szBuffer ) );
      if ( szBuffer[ 0 ] )
      {
         g_chPrintPreview = szBuffer[ 0 ];
         if ( g_chPrintPreview == 'Y' )
            g_chPrintPreview = '0';
      }

      SysReadZeidonIni( -1, "[ObjectEngine]", "PrintDialog", szBuffer, zsizeof( szBuffer ) );
      if ( szBuffer[ 0 ] )
         g_chPrintDialog = szBuffer[ 0 ];

      SysReadZeidonIni( -1, "[ObjectEngine]", "TraceOE_Warning", szBuffer, zsizeof( szBuffer ) );
      if ( szBuffer[ 0 ] )
         g_chTraceOE_Warning = szBuffer[ 0 ];

      SysReadZeidonIni( -1, "[ObjectEngine]", "TraceAction", szBuffer, zsizeof( szBuffer ) );
      if ( szBuffer[ 0 ] )
         g_chTraceZDrActions = szBuffer[ 0 ];

      SysReadZeidonIni( -1, "[ObjectEngine]", "TraceWeb", szBuffer, zsizeof( szBuffer ) );
      if ( szBuffer[ 0 ] )
         g_chTraceWebActions = szBuffer[ 0 ];

      SysReadZeidonIni( -1, "[ObjectEngine]", "ShowTaskID", szBuffer, zsizeof( szBuffer ) );
      if ( szBuffer[ 0 ] )
         AnchorBlock->bShowTaskID = 1;

      lpTraceFlags = GetTracingFlags( );

      SysReadZeidonIni( -1, "[ObjectEngine]", "ShowOpenFile", szBuffer, zsizeof( szBuffer ) );
      lpTraceFlags->bOpenFile = (toupper( szBuffer[ 0 ] ) == 'Y') ? TRUE : FALSE;

      SysReadZeidonIni( -1, "[ObjectEngine]", "ShowOI_Times", szBuffer, zsizeof( szBuffer ) );
      lpTraceFlags->bOI_Times = (toupper( szBuffer[ 0 ] ) == 'Y') ? TRUE : FALSE;

      SysReadZeidonIni( -1, "[ObjectEngine]", "ShowTaskMsgs", szBuffer, zsizeof( szBuffer ) );
      lpTraceFlags->bTaskMsgs = (toupper( szBuffer[ 0 ] ) == 'Y') ? TRUE : FALSE;
   }

   // Retrieve WindowStartup parameter and show window in hidden, systray or normal mode.
   SysReadZeidonIni( -1, "[ObjectEngine]", "WindowStartup", szBuffer, zsizeof( szBuffer ) );
   if ( _stricmp( szBuffer, "Hidden" ) == 0 )
   {
      ShowWindow( g_hWndMainFrame, SW_HIDE );
   }
   else
   if ( _stricmp( szBuffer, "SysTray" ) == 0 )
   {
      if ( ReadWindowPlacement( lpTask, &wp ) && CheckWindowPos( &wp ) )
         SetWindowPlacement( g_hWndMainFrame, &wp );

      ShowWindow( g_hWndMainFrame, SW_HIDE );
      SetupSysTray( hInstance );
      hMenu = GetMenu( g_hWndMainFrame );
      if ( hMenu )
         DestroyMenu( hMenu );

      // Load Systray specific menu.
      hMenu = LoadMenu( hInst, MAKEINTRESOURCE( ID_KZOENGWA_MNU ));
      // Delete the unused menu items.
      for ( i = g_nTraceWindowCnt; i < MAX_TRACE_WINDOWS; i++ )
         DeleteMenu( hMenu, IDM_TRACEWINDOW01 + i, MF_BYCOMMAND );

      SetMenu( g_hWndMainFrame, hMenu );
   }
   else
   if ( ReadWindowPlacement( lpTask, &wp ) && CheckWindowPos( &wp ) )
      SetWindowPlacement( g_hWndMainFrame, &wp );
   else
      ShowWindow( g_hWndMainFrame, SW_SHOW );  // Show the window

   SysReadZeidonIni( -1, "ObjectEngine", "DropEngineIfNoTasks", szBuffer, zsizeof( szBuffer ) );
   if ( ztoupper( *szBuffer ) == 'Y' )
      AnchorBlock->bDropEngineIfNoTasks = TRUE;

   CheckMenuItem( hMenu, IDM_SCROLLTRACE, MF_BYCOMMAND | (g_chScrollTrace ? MF_CHECKED : MF_UNCHECKED) );
   CheckMenuItem( hMenu, IDM_PRINTPREVIEW, MF_BYCOMMAND | (g_chPrintPreview ? MF_UNCHECKED : MF_CHECKED) );
   CheckMenuItem( hMenu, IDM_PREVIEW_ZOOMOUT, MF_BYCOMMAND | (g_chPrintPreview == '0' ? MF_CHECKED : MF_UNCHECKED) );
   CheckMenuItem( hMenu, IDM_PREVIEW_ZOOM, MF_BYCOMMAND | (g_chPrintPreview == '1' ? MF_CHECKED : MF_UNCHECKED) );
   CheckMenuItem( hMenu, IDM_PREVIEW_ZOOMIN, MF_BYCOMMAND | (g_chPrintPreview == '2' ? MF_CHECKED : MF_UNCHECKED) );
   CheckMenuItem( hMenu, IDM_PRINTDIALOG, MF_BYCOMMAND | (g_chPrintDialog ? MF_CHECKED : MF_UNCHECKED) );
   CheckMenuItem( hMenu, IDM_SHOWTASKID, MF_BYCOMMAND | (AnchorBlock->bShowTaskID ? MF_CHECKED : MF_UNCHECKED) );
   CheckMenuItem( hMenu, IDM_SETOETRACE, MF_BYCOMMAND | (g_chTraceOE_Warning == 0 || g_chTraceOE_Warning == 'n' ||
                                                         g_chTraceOE_Warning == 'N' ? MF_UNCHECKED : MF_CHECKED) );
   CheckMenuItem( hMenu, IDM_SETZDRTRACE, MF_BYCOMMAND | (g_chTraceZDrActions == 0 || g_chTraceZDrActions == 'n' ||
                                                          g_chTraceZDrActions == 'N' ? MF_UNCHECKED : MF_CHECKED) );
   CheckMenuItem( hMenu, IDM_SETWEBTRACE, MF_BYCOMMAND | (g_chTraceWebActions == 0 || g_chTraceWebActions == 'n' ||
                                                          g_chTraceWebActions == 'N' ? MF_UNCHECKED : MF_CHECKED) );

#if ( 1 )
   // Try and retrieve the workstation userid;
   {
      HANDLE hNetApi;
      FARPROC lpfnNetWkstaGetInfo;
      char    *Buffer[ 20 ];
      char    szLanUser[ 32 ] = { 'x' };
      char    szIniUser[ 32 ] = { 'y' };
      char    szIniPassword[ 32 ] = { 'z' };
      char    szPassword[ 32 ] = { 'X' };
      char    szUser[ 32 ] = { 'Y' };
      char    szEncrypted[ 1 ] = { 0 };
      USHORT  uReturnLth = 5;
      USHORT  uLth = 6;
      USHORT  uRC = 7;

      SysReadZeidonIni( -1, szlWorkstation, szlUserID, szIniUser, zsizeof( szIniUser ) );
      SysReadZeidonIni( -1, szlWorkstation, szlPassword, szIniPassword, zsizeof( szIniPassword ) );
      szLanUser[ 0 ] = 0;
      if ( (hNetApi = GetModuleHandle( "NETAPI" )) != 0 )
      {
         if ( (lpfnNetWkstaGetInfo = GetProcAddress( hNetApi, "NetWkstaGetInfo" )) != 0 )
         {
            uRC = (*lpfnNetWkstaGetInfo)( (zPCHAR) NULL, (zUSHORT) 10,
                                          (zPCHAR) &Buffer[ 0 ],
                                          (zUSHORT) 80,
                                          (zPUSHORT) &uReturnLth );
            if ( uRC == 0 )
               strcpy_s( szLanUser, zsizeof( szLanUser ), Buffer[ 1 ] );
         }
      }

      if ( szLanUser[ 0 ] || szIniUser[ 0 ] )
      {
         SysReadZeidonIni( -1, szlWorkstation, "Encrypted", szEncrypted, zsizeof( szEncrypted ) );

         if ( szIniUser[ 0 ] == 0 )
            strcpy_s( szIniUser, zsizeof( szIniUser ), szLanUser );

         if ( szEncrypted[ 0 ] == 'E' || szEncrypted[ 0 ] == 'e' )
         {
         /*
            UfEncryptString( szUser, "sa", 26 );
            TraceLineS( "----Encrypted Username: ", szUser );
            UfEncryptString( szPassword, "sql!4ever&ever", 26 );
            TraceLineS( "----Encrypted Password: ", szPassword );

            UfDecryptString( szIniUser, szUser,  26 );
            TraceLineS( "----Decrypted Username: ", szIniUser );
            UfDecryptString( szIniPassword, szPassword, 26 );
            TraceLineS( "----Decrypted Password: ", szIniPassword );
         */

            uLth = (USHORT) zstrlen( szIniUser );
            UfDecryptString( szUser, szIniUser, uLth );
         // TraceLineS( "----Decrypted Username2: ", szUser );
            uLth = (USHORT) zstrlen( szIniPassword );
            UfDecryptString( szPassword, szIniPassword, uLth );
         // TraceLineS( "----Decrypted Password2: ", szPassword );
         }
         else
         {
            strcpy_s( szUser, zsizeof( szUser ), szIniUser );
            strcpy_s( szPassword, zsizeof( szPassword ), szIniPassword );
         }

      // if ( zstrlen( szIniPassword ) == 26 )
      //    UfDecryptString( szPassword, szIniPassword, 26 );
      // else
      //    strcpy_s( szPassword, zsizeof( szPassword ), szIniPassword );

         SysSetUserID( lpTask, szUser, szPassword );
      }
      else
      {
         // Throw up the Logon dialog box
         DialogBox( hInst, MAKEINTRESOURCE( IDD_LOGON ), g_hWndMainFrame, fpLogon );
      }
   }
#endif

   // Create the DBH work object and name the view for later use.
   GetViewByName( &vDbhWork, zDBHANDLER_WORK_VIEW_NAME, g_vSystemTaskView, zLEVEL_SYSTEM );
   if ( vDbhWork == 0 )
   {
      SfActivateSysEmptyOI( &vDbhWork, "KZDBHWOB", g_vSystemTaskView, zSINGLE );
      SfLockView( vDbhWork );
      CreateEntity( vDbhWork, "ROOT", zPOS_AFTER );
      SetNameForView( vDbhWork, zDBHANDLER_WORK_VIEW_NAME, g_vSystemTaskView, zLEVEL_SYSTEM );
   }

   // Just a way to test if we are opening the right INI file.
   SysReadZeidonIni( -1, "[Debug]", "StartMessage", szBuffer, zsizeof( szBuffer ) );
   if ( szBuffer[ 0 ] )
      fnSysMessageBox( lpTask, "Object Engine Start Message", szBuffer, 0 );

   // Now automatically start all networks.
   SfStartNetworks( g_vSystemTaskView, 0 );

#if 0 // moving to RegisterZeidon  2005.04.18  dks

   // Check to see if there is an application update function.
   SysReadZeidonIni( -1, "[Zeidon]", "ApplicationUpdate", szBuffer );
   if ( *szBuffer )
   {
      zSHORT (POPERATION pfn )( void );
      LPLIBRARY hLibrary = SysLoadLibrary( vDbhWork, szBuffer );

      if ( hLibrary )
      {
         pfn = SysGetProc( hLibrary, "PerformApplicationUpdate" );
         if ( pfn )
            (*pfn)( );

         fnSysFreeLibrary( lpTask, hLibrary, FALSE );
      }
   }

#endif

   // If we were activated by a RegisterZeidonApplication, then some other
   // window is probably active and wants focus. Check to see if another
   // task exists and set focus to it after the logon is complete.
   if ( lpTask && zGETHNDL( lpTask ) != AnchorBlock->hMainTask )
   {
      SetActiveWindow( (HWND) lpTask->hMainWnd );
   }

   // Make the window visible; update its client area; and return "success"
   return( g_hWndMainFrame );         // Returns the value from PostQuitMessage
}

////////////////////// Start of dialog procedure ////////////////////////////
long zPASCAL
LogonDlgProc( HWND hWndDlg, unsigned uMsg,
              WPARAM wParam, LPARAM lParam )
{
   char szUserID[ 32 ];
   char szPassword[ 32 ];
   char szEncrypt[ 32 ];

   switch ( uMsg )
   {
      case WM_COMMAND:
         if ( wParam == IDC_OK )
         {
            GetDlgItemText( hWndDlg, IDC_USERID, szUserID, zsizeof( szUserID ) );
            GetDlgItemText( hWndDlg, IDC_PASSWORD, szPassword, zsizeof( szPassword ) );

            if ( szUserID[ 0 ] )
            {
               // Set global Userid and password in CORE
               SysSetUserID( 0, szUserID, szPassword );
               // See if the save button is checked
               if ( SendDlgItemMessage( hWndDlg, IDC_SAVEUSERID, BM_GETCHECK, 0, 0L ) )
               {
                  SysUpdateZeidonIni( szlWorkstation, szlUserID, szUserID );
                  UfEncryptString( szEncrypt, szPassword, 26 );
                  SysUpdateZeidonIni( szlWorkstation, szlPassword, szEncrypt );
               }

               EndDialog( hWndDlg, TRUE );
            }
            else
               return( FALSE );
         }
         else
         if ( wParam == IDC_CANCEL )
            EndDialog( hWndDlg, TRUE );
         else
            return( FALSE );

         // fall through

      case WM_INITDIALOG:
         SysGetUserID( 0, szUserID, zsizeof( szUserID ), szPassword, zsizeof( szPassword ) );
         SetDlgItemText( hWndDlg, IDC_USERID, szUserID );
         SetDlgItemText( hWndDlg, IDC_PASSWORD, szPassword );
         return( TRUE );

      default:
         return( FALSE );
   }
}

////////////////////// Start of dialog procedure ////////////////////////////
long zPASCAL
FindStringDlgProc( HWND hWndDlg, unsigned uMsg,
                   WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {
      case WM_COMMAND:
         if ( wParam == IDC_OK )
         {
            GetDlgItemText( hWndDlg, IDC_FINDSTRING, g_szFindString, zsizeof( g_szFindString ) );
            EndDialog( hWndDlg, IDOK );
         }
         else
         if ( wParam == IDC_CANCEL )
            EndDialog( hWndDlg, IDCANCEL );
         else
            return( FALSE );

         return( TRUE );

      case WM_INITDIALOG:
         SendDlgItemMessage( hWndDlg, IDC_FINDSTRING, EM_LIMITTEXT, zsizeof( g_szFindString ), 0L );
         SetDlgItemText( hWndDlg, IDC_FINDSTRING, g_szFindString );
         return( TRUE );

      default:
         return( FALSE );
   }
}

////////////////////// Start of dialog procedure ////////////////////////////
long zPASCAL
SetTraceDlgProc( HWND hWndDlg, unsigned uMsg,
                 WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {
      case WM_COMMAND:
         if ( wParam == IDC_OK )
         {
            int iTraceLevel = -1;

            if ( SendDlgItemMessage( hWndDlg, IDC_TRACE0, BM_GETCHECK, 0, 0 ) )
               iTraceLevel = 0;
            else
            if ( SendDlgItemMessage( hWndDlg, IDC_TRACE1, BM_GETCHECK, 0, 0 ) )
               iTraceLevel = 1;
            else
            if ( SendDlgItemMessage( hWndDlg, IDC_TRACE2, BM_GETCHECK, 0, 0 ) )
               iTraceLevel = 2;
            else
            if ( SendDlgItemMessage( hWndDlg, IDC_TRACE3, BM_GETCHECK, 0, 0 ) )
               iTraceLevel = 3;

            if ( iTraceLevel >= 0 )
            {
               LPTASK lpTask;

               for ( lpTask = zGETPTR( AnchorBlock->hFirstTask );
                     lpTask;
                     lpTask = zGETPTR( lpTask->hNextTask ) )
               {
                  lpTask->nDBHandlerTraceLevel = iTraceLevel;
               }

               TraceLineI( "(kzoengwa) DBH Trace Level for all tasks set to ", (zLONG) iTraceLevel );
            }

            EndDialog( hWndDlg, TRUE );
         }
         else
         if ( wParam == IDC_CANCEL )
            EndDialog( hWndDlg, TRUE );
         else
            return( FALSE );

         return( TRUE );

      case WM_INITDIALOG:
         return( FALSE );

      default:
         return( FALSE );
   }
}

////////////////////// Start of dialog procedure ////////////////////////////
long zPASCAL
LimitDlgProc( HWND hWndDlg, unsigned uMsg,
              WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {
      case WM_COMMAND:
         if ( wParam == IDC_OK )
         {
            BOOL nTransFlag;
            g_uTraceLineLimit = GetDlgItemInt( hWndDlg, IDC_LINELIMIT, &nTransFlag, 0 );
            EndDialog( hWndDlg, TRUE );
         }
         else
         if ( wParam == IDC_CANCEL )
            EndDialog( hWndDlg, TRUE );
         else
            return( FALSE );

         // fall through

      case WM_INITDIALOG:
         SetDlgItemInt( hWndDlg, IDC_LINELIMIT, g_uTraceLineLimit, 0 );
         SetDlgItemInt( hWndDlg, IDC_LINEUSAGE, (WORD) SendMessage( g_hWndLB, LB_GETCOUNT, 0, 0 ), 0 );
         return( TRUE );

      default:
         return( FALSE );
   }
}

////////////////////// Start of dialog procedure ////////////////////////////
long zPASCAL
ShowDLLDlgProc( HWND hWndDlg, unsigned uMsg,
                WPARAM wParam, LPARAM lParam )
{
#ifdef __WIN32__
   return( 0 );
#else
   WORD  wLBIndex;
   WORD  wCheckState;

   switch ( uMsg )
   {
      case WM_COMMAND:
#if 0
         {
            zCHAR szWorkString[ 256 ];

            strcpy_s( szWorkString, zsizeof( szWorkString ), "DLLDlg WM_COMMAND Message " );

            zltoa( (zLONG) (unsigned) uMsg, (szWorkString + zstrlen( szWorkString )), zsizeof( szWorkString ) - zstrlen( szWorkString ) );
            strcat_s( szWorkString, zsizeof( szWorkString ), "(" );
            zltox( (zLONG) (unsigned) uMsg, (szWorkString + zstrlen( szWorkString )), zsizeof( szWorkString ) - zstrlen( szWorkString ) );

            strcat_s( szWorkString, zsizeof( szWorkString ), ") wParam " );
            zltoa( (zLONG) wParam, (szWorkString + zstrlen( szWorkString )), zsizeof( szWorkString ) - zstrlen( szWorkString ) );
            strcat_s( szWorkString, zsizeof( szWorkString ), "(" );
            zltoa( (zLONG) wParam, (szWorkString + zstrlen( szWorkString )), zsizeof( szWorkString ) - zstrlen( szWorkString ) );

            strcat_s( szWorkString, zsizeof( szWorkString ), ") lParam " );
            zltoa( lParam, (szWorkString + zstrlen( szWorkString )), zsizeof( szWorkString ) - zstrlen( szWorkString ) );
            strcat_s( szWorkString, zsizeof( szWorkString ), "(" );
            zltoa( lParam, (szWorkString + zstrlen( szWorkString )), zsizeof( szWorkString ) - zstrlen( szWorkString ) );
            strcat_s( szWorkString, zsizeof( szWorkString ), ")" );

            SendMessage( g_hWndLB, LB_ADDSTRING, 0, (zLONG)(zPCHAR) szWorkString );
         }
#endif
         switch ( wParam )
         {
            case IDC_OK:
            {
               wLBIndex = (WORD) SendDlgItemMessage( hWndDlg, IDC_DLLLB,
                                                     LB_GETCURSEL, 0, 0L );
               if ( wLBIndex != LB_ERR )
               {
                  wCheckState = (WORD) SendDlgItemMessage( hWndDlg,
                                                           IDC_FREEDLL,
                                                           BM_GETCHECK,
                                                           0, 0L );
#if 0
                  if ( wCheckState == 1 )
                  {
                     WORD  hModHandle;
                     zCHAR szWorkString[ 256 ];

                     strcpy_s( szWorkString, zsizeof( szWorkString ), "Selected item: " );
                     SendDlgItemMessage( hWndDlg, IDC_DLLLB, LB_GETTEXT,
                                         wLBIndex,
                                         (zLONG)(zPCHAR)
                                         (szWorkString + zstrlen( szWorkString )));
                     strcat_s( szWorkString, zsizeof( szWorkString ), " Handle: " );
                     hModHandle = LOWORD( (LPARAM) SendDlgItemMessage
                                            ( hWndDlg, IDC_DLLLB,
                                              LB_GETITEMDATA, wLBIndex, 0L ) );
                     _ltoa( (zLONG) (WORD) hModHandle, (szWorkString + zstrlen( szWorkString )), 16 );
                     SendMessage( g_hWndLB, LB_ADDSTRING, 0,
                                  (zLONG)(zPCHAR) szWorkString );
                     FreeLibrary( hModHandle );
                  }
#endif
               }

               EndDialog( hWndDlg, TRUE );
               return( FALSE );
            }

            case IDC_CANCEL:
               EndDialog( hWndDlg, TRUE );
               return( FALSE );

            case IDC_FREEDLL:
               return( FALSE );

            case IDC_DLLLB:
               return( FALSE );

            default:
               return( FALSE );
         }

         // fall through

      case WM_INITDIALOG:
      {
         zCHAR       szLBItem[ 80 ];
         GLOBALENTRY ge;
         WORD        wFlags = GLOBAL_ALL;
         BOOL        bOkay;
         UINT        nShow = WM_USER;
#if 0
         zltoa( (zLONG) nShow, szLBItem, zsizeof( szLBItem ) );
         SendMessage( g_hWndLB, LB_ADDSTRING, 0, (zLONG)(zPCHAR) szLBItem );
#endif
         zmemset( (zPCHAR) &ge, 0, zsizeof( ge ) );
         ge.dwSize = zsizeof( GLOBALENTRY );
         bOkay = GlobalFirst( &ge, wFlags );
         while ( bOkay )
         {
            if ( ge.wType == GT_MODULE )
            {
               int   nCCount, iLth;
               char  ModuleName[ 13 ];
               WORD  wSel;
               WORD  wModNamePtr_Offset = 38; // offset in modules segment
               WORD  wModName_Offset;
               WORD  wLoadCount_Offset = 2;  // offset in modules segment
               WORD  wHandle_Offset = 82;    // offset in modules segment
               WORD  far *lpwLoadCount;
               WORD  far *lpwModuleNamePtr;
               char  far *lpcModuleName;
               WORD  far *lpwHandle;

               wSel = GlobalHandleToSel( ge.hOwner );

               lpwModuleNamePtr = MAKELP( wSel, wModNamePtr_Offset );
               wModName_Offset = *lpwModuleNamePtr;
               lpcModuleName = MAKELP( wSel, wModName_Offset );
               lpwLoadCount = MAKELP( wSel, wLoadCount_Offset );
               lpwHandle = MAKELP( wSel, wHandle_Offset );

               nCCount = *lpcModuleName++;
               for ( iLth = 0; iLth < nCCount; iLth++ )
                  ModuleName[ iLth ] = *lpcModuleName++;

               ModuleName[ iLth ] = 0;

               strcpy_s( szLBItem, zsizeof( szLBItem ), ModuleName );
               iLth = zstrlen( szLBItem );
               while ( iLth < 9 )
                  szLBItem[ iLth++ ] = ' ';

               szLBItem[ iLth ] = 0;

               // show load count for module
               zltoa( *lpwLoadCount, szLBItem + iLth, zsizeof( szLBItem ) - iLth );

               //  add name and count to listbox
               wLBIndex = (WORD) SendDlgItemMessage( hWndDlg, IDC_DLLLB,
                                                 LB_ADDSTRING, 0,
                                                 (zLONG)(zPCHAR) szLBItem );
               // save handle of library
               SendDlgItemMessage( hWndDlg, IDC_DLLLB, LB_SETITEMDATA,
                                   wLBIndex, MAKELPARAM( *lpwHandle, 0 ) );
            }

            bOkay = GlobalNext( &ge, wFlags );
         }

         return( TRUE );
      }

      default:
         return( FALSE );
   }
#endif
}

////////////////////// Start of dialog procedure ////////////////////////////
long zPASCAL
TraceListWndProc( HWND hWnd, unsigned uMsg,
                  WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {
      case WM_COPYDATA:
      {
         COPYDATASTRUCT * lpData = (COPYDATASTRUCT *) lParam;

         if ( lpData->dwData != LB_ADDSTRING )
            return fpDfltListWndProc( hWnd, uMsg, wParam, lParam );

         lParam = (LPARAM) lpData->lpData;
      }

         // Yes...fall through.

      case LB_ADDSTRING:              // Trace going to list box
      {
         WORD nItemCount;

         if ( g_hLogFile != -1 )
         {
            LPTASK lpTask = zGETPTR( AnchorBlock->hFirstTask );
            fnSysWriteLine( lpTask, g_hLogFile, 0, (zPCHAR) lParam );
         }

         // If g_uTraceLineLimit is 0 then don't add lines to trace window.
         if ( g_uTraceLineLimit == 0 )
            return( 0 );

         // Add the trace line to the trace listbox.  If the line we added
         // puts the listbox over the limit start filling the next listbox.
         nItemCount = (WORD) SendMessage( g_hwndTraceWindow[ g_nTraceWindowHead ], LB_ADDSTRING, 0, lParam );
         if ( nItemCount >= g_uTraceLineLimit )
         {
            UINT nOldHead = g_nTraceWindowHead;

            // Set head to next window.
            g_nTraceWindowHead = ( g_nTraceWindowHead + 1 ) % g_nTraceWindowCnt;

            // Clear the new listbox.
            SendMessage( g_hwndTraceWindow[ g_nTraceWindowHead ], LB_RESETCONTENT, 0, 0 );

            // Change the listbox that is displayed unless the head listbox
            // is not the one currently being displayed.
            if ( nOldHead == g_nTraceWindowDisplayed )
            {
               ShowWindow( g_hwndTraceWindow[ nOldHead ], SW_HIDE );
               ShowWindow( g_hwndTraceWindow[ g_nTraceWindowHead ], SW_SHOW );
               g_nTraceWindowDisplayed = g_nTraceWindowHead;
            }
            else
            {
               // OK...user is looking at an older trace window.  We will keep
               // the user on this trace window but we need to change the
               // checkboxes.
               WORD wCmd;
               UINT iDiff;

               // Find the difference between the displayed window and the head.
               iDiff = (g_nTraceWindowDisplayed + g_nTraceWindowCnt - nOldHead) % g_nTraceWindowCnt;

               // Determine the old trace window index.
               wCmd = (g_nTraceWindowCnt - iDiff) % g_nTraceWindowCnt + IDM_TRACEWINDOW01;

               // Turn off the check mark...we will no longer be displaying the current window.
               CheckMenuItem( GetMenu( g_hWndMainFrame ), wCmd, MF_BYCOMMAND | MF_UNCHECKED );

               wCmd++;
               if ( wCmd >= IDM_TRACEWINDOW01 + g_nTraceWindowCnt )
                  wCmd = IDM_TRACEWINDOW01;

               // Turn the next one on.
               CheckMenuItem( GetMenu( g_hWndMainFrame ), wCmd, MF_BYCOMMAND | MF_CHECKED );

            }
         }
         else
         if ( g_chScrollTrace )
            SendMessage( g_hwndTraceWindow[ g_nTraceWindowHead ], LB_SETCURSEL, nItemCount, 0L );

         return( nItemCount );
      }

      default:
         return( fpDfltListWndProc( hWnd, uMsg, wParam, lParam ) );
   }
}

////////////////////// Start of dialog procedure ////////////////////////////
long zPASCAL
LogTraceDlgProc( HWND hWndDlg, unsigned uMsg,
                 WPARAM  wParam, LPARAM lParam )
{
   switch ( uMsg )
   {
      case WM_COMMAND:
         if ( wParam == IDC_OPEN ) // open pushbutton
         {
            LPTASK lpTask = zGETPTR( AnchorBlock->hFirstTask );
            GetDlgItemText( hWndDlg, IDC_LOGFILE, szLogFileName, zsizeof( szLogFileName ) );
            if ( (g_hLogFile = fnSysOpenFile( lpTask, szLogFileName, COREFILE_CREATE )) == -1 )
            {
               MessageBox( GetActiveWindow( ), "Error opening trace file!",
                           "Zeidon Object Services", MB_ICONSTOP | MB_OK );
            }
            else
            {
               char szTraceText[ 512 ];

               // Send message that log file opened.
               strcpy_s( szTraceText, zsizeof( szTraceText ), "(ng) Log file Opened '" );
               strcat_s( szTraceText, zsizeof( szTraceText ), szLogFileName );
               strcat_s( szTraceText, zsizeof( szTraceText ), "'" );
               SysMessageList( szTraceText );

               WriteTraceToLog( lpTask );

               EndDialog( hWndDlg, TRUE );
            }
         }
         else
         if ( wParam == IDC_CLOSE )
         {
            LPTASK lpTask = zGETPTR( AnchorBlock->hFirstTask );
            SysMessageList( "(ng) End of Log" );
            fnSysCloseFile( lpTask, g_hLogFile, 0 );
            g_hLogFile = -1;
            EndDialog( hWndDlg, TRUE );
         }
         else
         if ( wParam == IDC_CANCEL )
            EndDialog( hWndDlg, TRUE );
         else
            return( FALSE );

         // fall through

      case WM_INITDIALOG:
         if ( g_hLogFile != -1 )
         {
            EnableWindow( GetDlgItem( hWndDlg, IDC_OPEN ), FALSE );
            SetDlgItemText( hWndDlg, IDC_LOGFILE, szLogFileName );
            SendDlgItemMessage( hWndDlg, IDC_CLOSE, BM_SETSTYLE, (WORD) BS_DEFPUSHBUTTON, 1L );
            SetFocus( GetDlgItem( hWndDlg, IDC_CLOSE ) );
            EnableWindow( GetDlgItem( hWndDlg, IDC_LOGFILE ), FALSE );
         }
         else
         {
            EnableWindow( GetDlgItem( hWndDlg, IDC_CLOSE ), FALSE );
            SendDlgItemMessage( hWndDlg, IDC_OPEN, BM_SETSTYLE, (WORD) BS_DEFPUSHBUTTON, 1L );
            if ( szLogFileName[ 0 ] == 0 )
            {
               SysReadZeidonIni( -1, szlWorkstation, "LogFile", szLogFileName, zsizeof( szLogFileName ) );
               if ( szLogFileName[ 0 ] == 0 )
               {
                  if ( AnchorBlock->szZeidonLoc[ 0 ] )
                     strcpy_s( szLogFileName, zsizeof( szLogFileName ), AnchorBlock->szZeidonLoc );
                  else
                     strcpy_s( szLogFileName, zsizeof( szLogFileName ), "\\" );

                  strcat_s( szLogFileName, zsizeof( szLogFileName ), "ZEIDON00.LOG" );
               }
            }

            SetWindowText( GetDlgItem( hWndDlg, IDC_LOGFILE ), szLogFileName );
         }

         return( TRUE );

      default:
         return( FALSE );
   }
}

/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:  CheckWindowPos
//  PURPOSE:   Determine if window position is within physical screen
//
/////////////////////////////////////////////////////////////////////////////
zBOOL
CheckWindowPos( LPWINDOWPLACEMENT pwp )
{
   zUSHORT uSquareX = GetSystemMetrics( SM_CXICON );
   zUSHORT uSquareY = GetSystemMetrics( SM_CYICON );
   zUSHORT uSizeX = GetSystemMetrics( SM_CXSCREEN ) - uSquareX;
   zUSHORT uSizeY = GetSystemMetrics( SM_CYSCREEN ) - uSquareY;

   // If the restored position is not visible, let default positioning occur.
// TraceRect( "CheckWindowPos Rect:", wp->rcNormalPosition );
// TraceLineI( "uSizeX: ", uSizeX );
// TraceLineI( "uSizeY: ", uSizeY );
   if ( pwp->rcNormalPosition.top > uSizeY ||
        pwp->rcNormalPosition.left > uSizeX ||
        pwp->rcNormalPosition.bottom <= uSquareY ||
        pwp->rcNormalPosition.right <= uSquareX )
   {
      return( FALSE );
   }

   return( TRUE );
}

zBOOL
ReadWindowPlacement( LPTASK lpTask, LPWINDOWPLACEMENT pwp )
{
   WINDOWPLACEMENT wp;
   char szFileName[ 260 ];
   char szTempName[ 260 ];
   char szBuffer[ 256 ];
   int nRead = 0;

   SysReadZeidonIni( -1, szlWorkstation, "LocalDir", szTempName, zsizeof( szTempName ) );
   SysConvertEnvironmentString( szFileName, zsizeof( szFileName ), szTempName );
   if ( szFileName[ 0 ] )
   {
      SysAppendcDirSep( szFileName );
      strcat_s( szFileName, zsizeof( szFileName ), "ZeidonRT.ini" );
      GetPrivateProfileString( "ObjectEngine",     // section name
                               "WindowPos",        // key name
                               "",                 // default string
                               szBuffer,           // destination buffer
                               zsizeof( szBuffer ), // size of destination buffer
                               szFileName );       // ini filename
   }
   else
      SysReadZeidonIni( -1, "[ObjectEngine]", "WindowPos", szBuffer, zsizeof( szBuffer ) );

   if ( szBuffer[ 0 ] )
   {
   // nRead = scanf( szBuffer, szPlaceFormat,
   //                &wp.flags, &wp.showCmd,
   //                &wp.ptMinPosition.x, &wp.ptMinPosition.y,
   //                &wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
   //                &wp.rcNormalPosition.left,
   //                &wp.rcNormalPosition.top,
   //                &wp.rcNormalPosition.right,
   //                &wp.rcNormalPosition.bottom );
      zPCHAR pch = szBuffer;
      zPCHAR pchComma;
      zLONG  lValue;

      while ( pch )
      {
         pchComma = zstrchr( pch, ',' );
         if ( pchComma )
         {
            *pchComma = 0;
            pchComma++;
         }

         lValue = zatol( pch );
         nRead++;
         if ( nRead == 1 )
            wp.flags = lValue;
         else
         if ( nRead == 2 )
            wp.showCmd = lValue;
         else
         if ( nRead == 3 )
            wp.ptMinPosition.x = lValue;
         else
         if ( nRead == 4 )
            wp.ptMinPosition.y = lValue;
         else
         if ( nRead == 5 )
            wp.ptMaxPosition.x = lValue;
         else
         if ( nRead == 6 )
            wp.ptMaxPosition.y = lValue;
         else
         if ( nRead == 7 )
            wp.rcNormalPosition.left = lValue;
         else
         if ( nRead == 8 )
            wp.rcNormalPosition.top = lValue;
         else
         if ( nRead == 9 )
            wp.rcNormalPosition.right = lValue;
         else
         if ( nRead == 10 )
            wp.rcNormalPosition.bottom = lValue;

         pch = pchComma;
      }
   }

   if ( nRead != 10 )
      return( FALSE );

   wp.length = sizeof( wp );
   *pwp = wp;
   return( TRUE );
}

//./ ADD NAME=TrayMessage
// Source Module=kzoengwa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       TrayMessage
//                                            4/9/2001Modified
//  PURPOSE:     Add/modify or remove Icons or messages to systray
//
//  PARAMETERS:  DWORD dwMessage - Add/Modify/Remove Flag see NIM_XXX constants
//               UINT uID        - additional
//               HICON hIcon     - Icon to display in systray
//               LPCSTR pszTip   - Tooltip to display in systray
/////////////////////////////////////////////////////////////////////////////
//./END + 2
zBOOL
TrayMessage( DWORD dwMessage, UINT uID, HICON hIcon, LPCSTR pszTip )
{
   zBOOL res;

   NOTIFYICONDATA tnd;

   tnd.cbSize      = sizeof( NOTIFYICONDATA );
   tnd.hWnd        = g_hWndMainFrame;
   tnd.uID         = uID;

   tnd.uFlags      = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   tnd.uCallbackMessage = zWM_NOTIFYICON;// notification message for message loop
   tnd.hIcon      = hIcon;
   if ( pszTip )
   {
      lstrcpyn( tnd.szTip, pszTip, zsizeof( tnd.szTip ) );
   }
   else
   {
      tnd.szTip[ 0 ] = 0;
   }

   res = Shell_NotifyIcon(dwMessage, &tnd);

   if ( hIcon )
      DestroyIcon( hIcon );

   return( res );
}

//./ ADD NAME=SetupSysTray
// Source Module=kzoengwa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SetupSysTray
//                                            4/9/2001Modified
//  PURPOSE:    to setup Systray for Object Service Window
//
//  PARAMETERS: HANDLE hInstance - Instance Handle
/////////////////////////////////////////////////////////////////////////////
//./END + 2
zBOOL
SetupSysTray( HANDLE hInstance )
{
   zBOOL bReturn = FALSE;
   HICON hIcon = NULL;
   char szTip[ 128 ];

   hIcon = LoadIcon( hInstance, "ZEIDON" );
   GetWindowText( g_hWndMainFrame, szTip, 127 );
   bReturn = TrayMessage( NIM_ADD, zTRAY_MESSAGE_SHOW, hIcon, szTip );

   return bReturn;
}

//./ ADD NAME=DetachSysTray
// Source Module=kzoengwa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       DetachSysTray
//                                            4/9/2001Modified
//  PURPOSE:     Remove setting from systray
//
//  PARAMETERS:
/////////////////////////////////////////////////////////////////////////////
//./END + 2
void
DetachSysTray( )
{
   TrayMessage( NIM_DELETE, zTRAY_MESSAGE_SHOW, NULL, NULL);
}

//./ ADD NAME=HandlePopupMenu
// Source Module=kzoengwa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       HandlePopupMenu
//                                            4/9/2001Modified
//  PURPOSE:     Create a popup menu for on systray notification
//
//  PARAMETERS:  HWND  hwnd -
//               POINT point -
/////////////////////////////////////////////////////////////////////////////
//./END + 2
void
APIENTRY HandlePopupMenu( HWND hwnd, POINT point )
{

   HMENU hMenu;
   HMENU hMenuTrackPopup;
   BOOL bIsVisible;
   // Get the menu for the windows
   hMenu = LoadMenu( hInst, MAKEINTRESOURCE( ID_SYSTRAY_MNU ) );

   if ( hMenu == 0 )
      return;

   // Get the first menu in it which we will use for the call to
   // TrackPopup( ). This could also have been created on the fly using
   // CreatePopupMenu and then we could have used InsertMenu( ) or
   // AppendMenu.
   hMenuTrackPopup = GetSubMenu( hMenu, 0 );

   CheckMenuItem( hMenu, IDM_SHOWTASKID, MF_BYCOMMAND | (AnchorBlock->bShowTaskID ? MF_CHECKED : MF_UNCHECKED) );
   CheckMenuItem( hMenu, IDM_SETOETRACE, MF_BYCOMMAND | (g_chTraceOE_Warning == 0 || g_chTraceOE_Warning == 'n' ||
                                                         g_chTraceOE_Warning == 'N' ? MF_UNCHECKED : MF_CHECKED) );
   CheckMenuItem( hMenu, IDM_SETZDRTRACE, MF_BYCOMMAND | (g_chTraceZDrActions == 0 || g_chTraceZDrActions == 'n' ||
                                                          g_chTraceZDrActions == 'N' ? MF_UNCHECKED : MF_CHECKED) );
   CheckMenuItem( hMenu, IDM_SETWEBTRACE, MF_BYCOMMAND | (g_chTraceWebActions == 0 || g_chTraceWebActions == 'n' ||
                                                          g_chTraceWebActions == 'N' ? MF_UNCHECKED : MF_CHECKED) );

   // This is required when using a notify icon -- see KB article
   // PRB: Menus for Notification Icons Don't Work Correctly
   SetForegroundWindow( hwnd );

   bIsVisible = IsWindowVisible( hwnd );
   EnableMenuItem( hMenu, IDM_SHOWTRACE, bIsVisible ? MF_GRAYED : MF_ENABLED );
   EnableMenuItem( hMenu, IDM_HIDEWINDOW, bIsVisible ? MF_ENABLED : MF_GRAYED );


   TrackPopupMenu( hMenuTrackPopup, TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL );

   // This is required when using a notify icon -- see KB article
   // PRB: Menus for Notification Icons Don't Work Correctly
   PostMessage( hwnd, WM_USER, 0, 0 );
}
