/////////////////////////////////////////////////////////////////////////////
// Project ZDrApp
//
// This is a part of the Zeidon Dynamic Rendering of GUI applications package.
// Copyright © 1995 - 2016 QuinSoft, Inc.
// All Rights Reserved.
//
// SUBSYSTEM:    zdrapp.dll - ZDr Application
// FILE:         zdrstask.cpp
// AUTHOR:
//
// OVERVIEW
// ========
// Source file for implementation of class ZSubtask.
//

//
// CHANGE LOG - most recent first order
//
// 200y.mm.dd    xxx
//    Note ...
//
// 2002.10.22    DKS
//    Added zAUTOGRAY_ACTION_NOTNULL to auto gray functionality.
//
// 2002.07.31    DKS
//    Added splitter window functionality.
//
// 2002.07.10    HH
//    Fix Zeidon Web Bug in ZSubtask::EnableParentWindows.
//
// 2002.06.12    BL/DKS Z10
//    Initialized m_lRelxxxx data items for simple proportional resize.
//
// 2002.05.17    DKS    Z10
//    Implemented simple proportional resize when a "single" control is
//    marked as proportional resize.
//
// 2002.03.01    DKS    Z10
//    Added condition when invalid window name is requested.
//
// 2002.01.15    DKS    Z10
//    Attempt to (visually) set proper "default" push button.
//
// 2001.10.15    DKS    Z10
//    By default do not reset to status bar message to that of the last ctrl
//    with focus (after showing a fly-over message from another ctrl).
//
// 2001.10.10    DKS    Z10
//    Altered timing of initial Ctrl Mapping and setting of focus.
//
// 2001.10.02    DKS/HH
//    Initialized ZSubtask data to prevent crash when Dialog not found.
//
// 2001.09.25    DKS    Z10
//    Fixed setting of entry in global subtask list for ConversationalDialog.
//
// 2001.09.12    DKS    WEB
//    Give up and reshow all list data if MapFromOI occurs more than once
//    without a chance to transmit data to the Light Driver.
//
// 2001.08.08    DKS    R55618
//    Fix for Replace window with same window.
//
// 2001.06.25    DKS    Z10
//    Using Font=ZeidonSize in the [Workstation] .ini setting permits the
//    new fonts while retaining the old Window/Control sizes.
//
// 2001.06.15    DKS    WEB
//    Fix for Replace window with same window.
//
// 2001.06.08    DKS    Debug
//    Added debugging code to solve Action bug for TMV.
//
// 2001.05.31    DKS
//    Change location of define for zMAX_WINDOWCAPTION_LTH.
//
// 2001.05.27    BL
//    Change Window Caption Size from 64 to 254
//
// 2001.05.18    DKS    R54685
//    Changed algorithm to set the proper font when Workstation Font is
//    set in Zeidon.ini.
//
// 2001.05.10    DKS    Z10
//    Moved zWND_EVENT_ON_SETUP to after MapFromOI when the Frame Window
//    is guaranteed to be valid.
//
// 2001.05.03    DKS    WEB
//    Phase II of Delta Data.  One more phase left to implement.
//
// 2001.05.01    DKS    RemoteServer
// 2001.04.25    TMV    RemoteServer
//     change ZSubtask::SetCaptionTitle to copy the caption title
//     into the Caption Attribut of Wnd-Entity in KZXRA
//
// 2001.04.19    DKS    Z10
//    Change to use MapRect units as base for conversion to dialog units.
//
// 2001.04.11    DKS    RemoteServer
//    Set up for Delta Data project.
//
// 2001.03.19    DKS    Fonts
//    Added FontCtrl to permit override of ctrl font setting.
//
// 2001.01.04    DKS    Z10
//    Add a flag to the Window update dialog to permit the specification
//    of whether or not to select the first (edit or MLE) control on a window
//    on initial entry to the window.
//
// 2001.01.01    DKS    Z10
//    Permit focus to disabled controls if they are marked:
//    "disable as read only".
//
// 2000.02.24    BL     Z10    new PPE handling
//    Modified ZSubtask::ZSubtask for load XPE, 1. search in LPLR directory,
//    if not found, search in Zeidon/Bin/Sys directory.
//
// 1999.12.06    DKS    Z10    TB861
//    Fixed initial paint problems when repositioning to previous coordinates.
//
// 1999.10.12    DKS    Z10    QS9999
//    Runtime font size from .ini file set properly.
//
// 1999.10.01    DKS    Z10    QS9999
//    FlyBy delayed by one second when application sets message bar.
//
// 1999.09.15    DKS    Z10    ActiveX
//    Added Mapping List and mutex protection of global subtask list.
//
// 1999.07.28    DKS    Z10    FH999
//    Permit TAB to shift focus to a control outside of a composite.
//
// 1999.07.08    DKS    Z10    Enhance
//    Keep track of the list of subtasks in a view available to an
//    application (requested by FH).
//
// 1999.05.11    DKS    Z10    ActiveX
//    TBEditor now implemented as ActiveX control ... no special handling.
//
// 1999.03.10    DKS
//    Altered the TranslateColor function to remove name conflict.
//
// 1999.02.16    DKS
//    Used new option zLOADLIB_RESOURCES on SysLoadLibraryWithErrFlag.
//
// 1999.02.02    DKS
//    Added default font support for reports.
//
// 1998.12.31    DKS
//    Attempt to stop bleed through of non-parent (usually desktop) window
//    on return to parent.
//
// 1998.12.04    DKS
//    ReadWindowPlacement's new signature.
//    The "Font" may now reside in a user.ini file (redirected from
//    Zeidon.ini via the "LocalDir" value.
//
// 1998.10.30    DKS
//    Fixed in initialization problem for early error termination.
//
// 1998.10.12    DKS
//    Modified Dialog conversion to set the size of the Relative Pos/Size
//    area properly.
//
// 1998.10.05    DKS
//    Corrected algorithm for locating a Subtask across tasks.
//
// 1998.09.03    DKS
//    Attempted fix to SetWindowState DESTROY case.
//
// 1998.08.11    DKS
//    Fixed SetFocus Assertion problem for Frank
//

#include "zstdafx.h"

#define ZDRAPP_CLASS AFX_EXT_CLASS
#include "ZDr.h"
#include "zdrgbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// #define DEBUG_ALL
// #define DEBUG_RESIZE
// #define DEBUG_TASK
static zLONG g_lRel = (1L << 24) + (0L << 16) + ('a' << 8) + 1;

#define zMAX_WINDOWCAPTION_LTH  254

/////////////////////////////////////////////////////////////////////////////
//
// CFrameWnd automatically positions its view/client window (you must supply
// a view window) so that it is the same size as the client rectangle.  You
// can add additional decorations like toolbars and status lines to a window.
//
/////////////////////////////////////////////////////////////////////////////
//
// A GUI window object (derived from CWnd) and a ZSubtask object are always
// related 1:1 to each other (the ZSubtask is created first, so for a short
// while there is no CWnd object associated with the ZSubtask).  The two
// objects contain pointers to each other to permit information within each
// to be accessed by the other.
//
// The reason that the CWnd derived classes are not also derived from the
// ZSubtask is that there is information that must be determined in the
// ZSubtask so that the appropriate CWnd derived class can be instantiated.
//
/////////////////////////////////////////////////////////////////////////////
// ZSubtask - ctor

zLONG ZSubtask::g_lIdNbr = 1;
ZSubtask::ZSubtask( ZTask    *pZTask,      // Dr task object
                    ZSubtask *pZParent,    // Zeidon Parent
                    ZSubtask *pZOwner,     // Zeidon Owner
                    zVIEW    vSubtask,     // Zeidon subtask for this window
                    zVIEW    vNewSubtask,  // if 0, create new subtask, else use
                    zSHORT   fCreateModal, // create as a modal window
                    zCPCHAR  cpcDlgTag,    // Dialog to process
#ifdef zREMOTE_SERVER
                    zCPCHAR  cpcWndTag,    // Window to create (0 ==> dflt)
                    ZSocketTask *pZSocketTask,
                    zCPCHAR  cpcAppTag )   // Applicationname (default = 0)
#else
                    zCPCHAR  cpcWndTag )   // Window to create (0 ==> dflt)
#endif
{
   do
   {
      m_ulSubtaskIdNbr = g_pSubtaskList[ 0 ].ulSubtaskState++;
      m_ulSubtaskIdNbr++;

   } while ( m_ulSubtaskIdNbr != g_pSubtaskList[ 0 ].ulSubtaskState );

   if ( pZTask && (pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      TraceLine( "ZSubtask::ZSubtask::ctor (0x%08x): %d  %s", this, m_ulSubtaskIdNbr, cpcWndTag );
   }

   zPCHAR pch;
   zSHORT k;

   // initialize flags/pointers
   m_pZTask = pZTask;
   m_pZTask->m_uAppState &= ~zAPP_STATE_TERMINATED;
   m_pZTask->m_bDeletingSplitter = FALSE;
   m_pZParent = pZParent;
   m_pZOwner = pZOwner;
   m_pZFWnd = 0;
   m_pZView = 0;
   m_hMenuDefault = 0;
   m_hMenuDocTemplate = 0;
   m_bStopEvents = FALSE;
   m_lRelease = 0;
   m_vPE = 0;  // used only during construction

   if ( fCreateModal )
      m_ulSubtaskFlags = zSUBTASK_CREATED_MODAL;
   else
      m_ulSubtaskFlags = 0;

   if ( cpcDlgTag )
      m_pzsDlgTag = new CString( cpcDlgTag );
   else
      m_pzsDlgTag = new CString( "" );

   if ( cpcWndTag )
      m_pzsWndTag = new CString( cpcWndTag );
   else
      m_pzsWndTag = new CString( "" );

   m_pzsLastTag = 0;
   m_pzsLastCtrlTag = 0;
   m_pzsProfileViewName = 0;
   m_pchWindowPlacement = 0;
   m_nInvisible = m_nDisabled = 0;
   m_lExtentX = m_lExtentY = 0;
   m_pEventParms = 0;
// m_lActType = 0;
// m_pzsAction = 0;
// m_pzsActDlg = m_pzsActWnd = 0;
   m_pzsResumeAction = 0;
   m_nDrawMenuBar = 0;
   m_pZBinPopup = 0;
   m_pTrackMenu = 0;
   m_pzsPopupTag = 0;
   m_pZBinMenu = 0;
   m_pMenu = 0;
   m_pzsMenuTag = 0;
   m_pZMIXCtrl = 0;
   m_pDfltBtn = 0;
   m_pCurrDfltBtn = 0;
   m_pDIL = 0;
   m_pchEnabledAction = 0;
   m_pzsCaption = 0;
   m_pzsTitle = 0;
   m_pzmaFirstFocus = 0;
   m_pzmaLastFocus = 0;
   m_pzmaWithFocus = 0;
   m_pzmaLastFlyBy = 0;
   m_ulFlyByTickCnt = 0;
   m_pzmaAccel = 0;
   m_uMouseStatus = zMOUSE_STATUS_OFF;
   m_szActionName[ 0 ] = 0;
   m_pAccels = 0;
   m_nDIL_Items = 0;
   m_lMsgCmdId = 0;
   m_cpcCurrOper = 0;
   m_pZSubtaskProxy = 0;
   m_pZSubtaskGlobal = 0;
   m_pZSubtaskParent = 0;
   m_BarTipList.SetSize( 4, 4 );
   m_nBarTipCnt = 0;
   m_ulNextBarTipCmd = zZEIDON_FIRST_TOOLBAR_CMD;
   m_pSplitterView = 0;
   m_pZPrintout = 0;
   m_bLocked = FALSE;

#ifdef zREMOTE_SERVER

   m_lTID = (zLONG) AfxGetThread( )->m_nThreadID;
   m_pzsImageURL = 0;
   m_pzsRemoteWndTag = new CString( "unknown" );
   m_pZSocketTask = pZSocketTask;

   // Protect this with a semaphore!!!
   m_pZSocketTask->LockMutex( ?, TRUE, "ZSubtask::ctor" );

   if ( cpcAppTag == 0 )
   {
      if ( vNewSubtask )
      {
         zCHAR  szAppName[ zZEIDON_NAME_LTH + 1 ];

         GetApplDirectoryFromView( szAppName, vNewSubtask,
                                   zAPPL_NAME, zsizeof( szAppName ) );
         m_pzsAppTag = new CString( szAppName );
      }
      else
         m_pzsAppTag = new CString( *(pZSocketTask->m_pzsAppName) );
   }
   else
      m_pzsAppTag = new CString( cpcAppTag );

#else
   m_lTID = SysGetTaskFromView( vSubtask );
#endif

   m_vInterpSubtask = 0;
   m_hLibrary = 0;
   m_hLibRes = 0;
   m_hInstDLL = 0;
   m_hInstRes = 0;
   m_clrText = 0;
   m_clrErrText = zRGB( 255, 0, 0 ); // default to red
// m_clrBk = RGB( 0, 255, 255 ); teal test
   m_clrBk = ::GetSysColor( COLOR_BTNFACE );
   m_ulWndOper = 0;
   m_pzsDLL_Name = 0;
   m_vDialog = 0;
   m_vMsgQ = 0;
   m_pWndDef = 0;

   m_pFontWS = 0;
   m_pFontCtrl = 0;
   m_bUseMapDlgUnits = FALSE;

#ifdef zREMOTE_SERVER
   if ( m_pZSocketTask->m_pZSubtaskTop == 0 )
      m_pZSocketTask->m_pZSubtaskTop = this;
#else
   if ( m_pZTask->m_pZSubtaskTop == 0 )
      m_pZTask->m_pZSubtaskTop = this;
#endif

   if ( CreateWindowSubtask( &m_vDialog, vSubtask, vNewSubtask, cpcDlgTag, 0 ) )
   {
      MessageSend( m_vDialog, 0, "Zeidon Application", "Cannot create Zeidon subtask", zMSGQ_MODAL_ERROR, FALSE );

#ifdef zREMOTE_SERVER
      m_pZSocketTask->LockMutex( ?, FALSE, "ZSubtask::ctor" );
#endif

      ZSubtask::InitializeSubtaskState( this );
      ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_MARK_FOR_DELETE );
      return;     // error ... throw an exception here???
   }

   GetAddrForAttribute( (zPCHAR *) &pch, m_vDialog, szlDlg, szlTag );
   mDeleteInit( m_pzsDlgTag );
   m_pzsDlgTag = new CString( pch );

   // This is an application level object ... if the object already exists,
   // use it, otherwise activate it ... note that CORE will have already
   // loaded this definition so that the test for success/failure below is moot.
   zVIEW vMsgQ;

   if ( GetViewByName( &vMsgQ, szl__MSGQ, m_vDialog, zLEVEL_TASK ) != zLEVEL_TASK )
   {
      if ( ActivateEmptyObjectInstance( &vMsgQ, szlKZMSGQOO, m_vDialog, zMULTIPLE ) >= 0 )
      {
         SetNameForView( vMsgQ, szl__MSGQ, m_vDialog, zLEVEL_TASK );
      // CreateEntity( vMsgQ, szlTask, zPOS_LAST );
      }
      else
      {
         // ERROR out of here ... will not go far without this object!!!
         // Is this the correct way to handle this error condition???
         TraceLineS( "(drvr) Cannot load Message Object - ", szlKZMSGQOO );
         MessageSend( m_vDialog, 0, szlDrvr, "Cannot load Message Object", zMSGQ_MODAL_ERROR, FALSE );

#ifdef zREMOTE_SERVER
         m_pZSocketTask->LockMutex( ?, FALSE, "ZSubtask::ctor" );
#endif

         ZSubtask::InitializeSubtaskState( this );
         ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_MARK_FOR_DELETE );
         return;  // error ... throw an exception here???
      }
   }

   CreateViewFromViewForTask( &m_vMsgQ, vMsgQ, vSubtask );
   SfLockView( m_vMsgQ );  // we lock this view because it is
                           // unnamed ... to prevent the OE from
                           // automatically cleaning it up during
                           // the deletion of an OE subtask.

// TraceLineI( "Create MsgQ view for Task: ", m_lTID );
   if ( SetEntityCursor( m_vMsgQ, szlTask, szlId, zPOS_FIRST | zQUAL_INTEGER, &m_lTID, 0, 0, 0, 0, 0 ) < 0 )
   {
      zUSHORT uLth = sizeof( zLONG ) + 2 * sizeof( zSHORT ) + 10 * sizeof( zLONG );

      CreateEntity( m_vMsgQ, szlTask, zPOS_LAST );
      SetAttributeFromVariable( m_vMsgQ, szlTask, szlId, &m_lTID, zTYPE_INTEGER, 0, 0, 0 );
      SetAttributeFromVariable( m_vMsgQ, szlTask, szlClient, szlZeidon, zTYPE_STRING, 0, 0, 0 );

      pch = new char[ uLth ];
      *((zPSHORT) (pch + sizeof( zLONG ))) = 0;
      *((zPSHORT) (pch + sizeof( zLONG ) + sizeof( zSHORT ))) = 10;
      *((zPLONG) pch) = 0;
      SetAttributeFromBlob( m_vMsgQ, szlTask, szlStatus, pch, uLth );
   // TraceLineI( "STask Create MsgQ Status Attribute for Task: ", m_lTID );
      delete [] pch;
   }

// DisplayObjectInstance( m_vMsgQ, 0, 0 );

   // If there is no window name specified or if the specified window does
   // not exist within this dialog, go to the default processing -- first
   // try for the DfltWnd, which if not found, go to the first window in
   // the dialog.
// DisplayObjectInstance( m_vDialog, 0, 0 );

   zCHAR szRelease[ 32 ];

   if ( MiGetOI_ReleaseForView( m_vDialog, szRelease ) )
   {
      pch = zstrchr( szRelease, '.' );
      if ( pch )
      {
         *pch = 0;
         m_lRelease = zatol( szRelease );
         m_lRelease <<= 8;
         pch++;
         m_lRelease += zatol( pch );
         m_lRelease <<= 8;
         pch++;
         m_lRelease += *pch;
         m_lRelease <<= 8;
         pch++;
         m_lRelease += zatol( pch );
      }
   }

   if ( cpcWndTag && cpcWndTag[ 0 ] &&
        SetCursorFirstEntityByString( m_vDialog, szlWnd, szlTag,  cpcWndTag, 0 ) > zCURSOR_UNCHANGED )
   {
      mDeleteInit( m_pzsWndTag );
      m_pzsWndTag = new CString( cpcWndTag );
   }
   else
   {
      if ( cpcWndTag == 0 || cpcWndTag[ 0 ] == 0 )
      {
         GetAddrForAttribute( (zPCHAR *) &pch, m_vDialog, szlDlg, szlDfltWnd );
         if ( pch[ 0 ] && SetCursorFirstEntityByString( m_vDialog, szlWnd, szlTag, pch, 0 ) > zCURSOR_UNCHANGED )
         {
            mDeleteInit( m_pzsWndTag );
            m_pzsWndTag = new CString( pch );
         }
      }
      else
         mDeleteInit( m_pzsWndTag );
   }

   if ( m_pzsWndTag == 0 || **m_pzsWndTag == 0 )
   {
      zCHAR szMessage[ 256 ];
      zCHAR szWindowName[ zTAG_LTH ];

      strcpy_s( szMessage, zsizeof( szMessage ), "(drvr) Window name not found in Dialog: " );
      if ( cpcDlgTag )
         strcat_s( szMessage, zsizeof( szMessage ), cpcDlgTag );
      else
         strcat_s( szMessage, zsizeof( szMessage ), "<nul>" );

      if ( cpcWndTag && cpcWndTag[ 0 ] )
         strcpy_s( szWindowName, zsizeof( szWindowName ), cpcWndTag );
      else
         GetStringFromAttribute( szWindowName, zsizeof( szWindowName ), m_vDialog, szlDlg, szlDfltWnd );

      ZSubtask *pParent;
      if ( pZParent == 0 )
         pParent = this;
      else
         pParent = pZParent;

      if ( m_pzsWndTag == 0 || **m_pzsWndTag == 0 )
         strcat_s( szMessage, zsizeof( szMessage ), "\n Enter valid window name " );

      zLONG lFlags = 0x01000000;
      while ( m_pzsWndTag == 0 || **m_pzsWndTag == 0 )
      {
         if ( ConstructZeidonPrompt( pParent->m_vDialog, "Valid Window", szMessage,
                                     szWindowName, zsizeof( szWindowName ), &lFlags, "Window:", 0, 0 ) == IDOK )
         {
            if ( SetCursorFirstEntityByString( m_vDialog, szlWnd, szlTag, szWindowName, 0 ) > zCURSOR_UNCHANGED )
            {
               mDeleteInit( m_pzsWndTag );
               m_pzsWndTag = new CString( szWindowName );
            }
         }
         else
         {
            mDeleteInit( m_pzsWndTag );
            m_pzsWndTag = new CString( "" );

#ifdef zREMOTE_SERVER
            m_pZSocketTask->LockMutex( ?, FALSE, "ZSubtask::ctor" );
#endif

            ZSubtask::InitializeSubtaskState( this );
            ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_MARK_FOR_DELETE );
            return;
         }
      }
   }

#ifdef zREMOTE_SERVER
   CString cs = *m_pzsDlgTag;
   cs += ".";
   cs += *m_pzsWndTag;
   mDeleteInit( m_pzsRemoteWndTag );
   m_pzsRemoteWndTag = new CString( cs );
#endif

   ZSubtask::InitializeSubtaskState( this );
   CreateDefaultFont( );

#ifdef DEBUG_WAB
   TraceLineI( "===========> [drvr] Creating window m_vDialog = ",
               (zLONG) m_vDialog );
   TraceLineS( *m_pzsDlgTag, *m_pzsWndTag );
   if ( pZParent )
      TraceLineI( "Parent dialog = ", (zLONG) pZParent->m_vDialog );
   else
      TraceLineI( "Parent dialog = ", 0L );
#endif

   zVIEW   vHotkey = m_pZTask->m_vHK;
   zULONG  ulHotkeyLth;
   zULONG  ulGlobalHotkeyLth;

   GetAttributeLength( &ulGlobalHotkeyLth, vHotkey, szlApp, szlHotkey );
   GetAttributeLength( &ulHotkeyLth, m_vDialog, szlWnd, szlHotkey );

   // Check out RegisterHotKey and UnregisterHotKey???
   if ( ulHotkeyLth % sizeof( zACCEL_TABLE ) )
   {
      TraceLineI( "Hotkey length = ", ulHotkeyLth );
      TraceLineI( "zACCEL_ACTION = ", sizeof( zACCEL_TABLE ) );
      MessageSend( m_vDialog, 0, *m_pzsDlgTag, "Hotkey length error - please resave .PWD", zMSGQ_MODAL_ERROR, FALSE );
   }

   if ( ulGlobalHotkeyLth % sizeof( zACCEL_TABLE ) )
   {
      TraceLineI( "Hotkey global = ", ulGlobalHotkeyLth );
      TraceLineI( "zACCEL_ACTION = ", sizeof( zACCEL_TABLE ) );
      MessageSend( m_vDialog, 0, *m_pzsDlgTag, "Global Hotkey length error - please resave .HKY", zMSGQ_MODAL_ERROR, FALSE );
   }

// if ( ulHotkeyLth || ulGlobalHotkeyLth )
   {
      k = (zSHORT) (ulHotkeyLth / sizeof( zACCEL_TABLE ) + ulGlobalHotkeyLth / sizeof( zACCEL_TABLE ));
      mDeleteInit( m_pAccels );
      m_pAccels = new char[ (k + 1) * sizeof( zACCEL_TABLE ) ];
      GetBlobFromAttribute( m_pAccels, &ulHotkeyLth, m_vDialog, szlWnd, szlHotkey );
      GetBlobFromAttribute( m_pAccels + ulHotkeyLth, &ulGlobalHotkeyLth, vHotkey, szlApp, szlHotkey );
      LPACCEL_TABLE lpAT = (LPACCEL_TABLE) m_pAccels;
      lpAT[ k ].nID = -1;
//    while ( k > 0 )
//    {
//       TraceLine( "ZSubtask::ZSubtask::ctor: lpAT[%d].nID ===> %d  VK = 0x%x",
//                  k, lpAT[ k ].nID, lpAT[ k ].ac.uVK );
//       k--;
//    }
   }

   ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_IN_CONSTRUCTION );

   // Set the address to this C++ object in the Zeidon subtask object ...
   // this is our link back to the C++ object from the Zeidon subtask!
   CreateEntity( m_vDialog, szlSubtask, zPOS_AFTER );
   SetAttributeFromInteger( m_vDialog, szlSubtask, szlCPP, (zLONG) this );

   // If this is a modal sub-window, disable all parent windows of this
   // window ... as well as their descendents.  Note that fCreateModal
   // is negative if we are resuming from the painter.
   if ( fCreateModal == 1 || fCreateModal == -1 )
      EnableParentWindows( FALSE );

   // Get the structure of attributes for this window.
   mDeleteInit( m_pWndDef );
   m_pWndDef = new tagzKZWDLGXO_Wnd_DEF;
   m_pWndDef->CheckByte = 0xFE;
   m_pWndDef->lStructSize = sizeof( zKZWDLGXO_Wnd_DEF );
   GetStructFromEntityAttrs( (zPCHAR) m_pWndDef, m_vDialog, szlWnd );
   if ( m_pWndDef->CheckByte != 0xFE )
      MessageBox( 0, "WndDef Structure Length Error", "GetStructFromEntityAttrs", MB_OK );

   GetAddrForAttribute( (zPCHAR *) &pch, m_vDialog, szlWnd, szlD_Caption );
   if ( *pch )
      strcpy_s( m_pWndDef->Caption, zsizeof( m_pWndDef->Caption ), pch );

   if ( m_pWndDef->GeneralFlag & 0x00000001 )
      m_ulSubtaskFlags |= zSUBTASK_SCROLLBARS;

   if ( m_pWndDef->GeneralFlag & 0x00000002 )
      m_ulSubtaskFlags |= zSUBTASK_SELECT_FIRST_EDIT;

   if ( m_pWndDef->DfltMenu[ 0 ] == 0 )
      m_ulSubtaskFlags |= zSUBTASK_NO_MAIN_MENU;

#ifdef DEBUG_ALL
// TraceLineS( "=====================> WindowTag ", m_pWndDef->Tag );
// TraceLineS( "Tag ", m_pWndDef->Tag );
// TraceLineS( "Caption ", m_pWndDef->Caption );
// TraceLineI( "PSDLG_X ", m_pWndDef->PSDLG_X );
// TraceLineI( "PSDLG_Y ", m_pWndDef->PSDLG_Y );
// TraceLineI( "SZDLG_X ", m_pWndDef->SZDLG_X );
// TraceLineI( "SZDLG_Y ", m_pWndDef->SZDLG_Y );
// TraceLineI( "Style ", m_pWndDef->StyleEx );
// TraceLineI( "Style ", m_pWndDef->Style );
// TraceLineI( "ActCnt ", m_pWndDef->ActCnt );
#endif

// if ( m_pWndDef->Subtype & zWNDTYPE_3D )      // this needs to be accounted
      m_ulSubtaskFlags |= zSUBTASK_DIALOG_BOX;  // for with new 3D???

   if ( m_pWndDef->Subtype & zWNDTYPE_MDI )
      m_ulSubtaskFlags |= zSUBTASK_SUBWND_MDI_FRAME;
   else
      m_ulSubtaskFlags |= zSUBTASK_SUBWND_SDI_FRAME;

   if ( m_pWndDef->Subtype & zWNDTYPE_SINGLE_RELSIZE )
      m_ulSubtaskFlags |= zSUBTASK_SINGLE_RELSIZE;

   if ( pZParent )
      m_vInterpSubtask = pZParent->m_vInterpSubtask;
   else
      m_vInterpSubtask = pZTask->m_vInterpSubtask;

   mDeleteInitA( m_pchEnabledAction );
   m_pchEnabledAction = new char[ (zSHORT) (m_pWndDef->ActCnt + sizeof( zSHORT )) ];

   // Initialize all actions to be enabled as the default
   // how can we so non-chalantly unset ActCnt? ... because it appears
   // that ActCnt is never referenced again.
   zmemset( m_pchEnabledAction, zAUTO_ENABLE, (zSHORT) (m_pWndDef->ActCnt + sizeof( zSHORT )) );
   zSHORT *pn = (zSHORT *) m_pchEnabledAction;
   *pn = (zSHORT) m_pWndDef->ActCnt;

#ifdef DEBUG_ACTION
   TraceLineI( "zdrstask init lth: ", m_pWndDef->ActCnt + sizeof( zSHORT ) );
   TraceBlob( "zdrstask init:", m_pchEnabledAction + sizeof( zSHORT ), *((zSHORT *) m_pchEnabledAction) );
#endif

   if ( m_vInterpSubtask == 0 )   // not done if interpreting
   {
      // Get the DLL for this dialog and load the library.
      zPCHAR pch;

      GetAddrForAttribute( (zPCHAR *) &pch, m_vDialog, szlDlg, szlDLL );
      if ( *pch == 0 )
      {
         m_hLibrary = 0;
      }
      else
      {
      // m_hInstDll = LoadLibraryEx( szFileName, 0, LOAD_LIBRARY_AS_DATAFILE );

         mDeleteInit( m_pzsDLL_Name );
         m_pzsDLL_Name = new CString( pch );
         m_hLibrary = SysLoadLibraryWithErrFlag( m_vDialog, pch, 0 );
         m_hInstDLL = (HINSTANCE) SysGetInstance( m_hLibrary );
         m_hLibRes = SysLoadLibraryWithErrFlag( m_vDialog, pch, zLOADLIB_RESOURCES );
         m_hInstRes = (HINSTANCE) SysGetInstance( m_hLibRes );
      }
   }
   else
   {
      m_hLibrary = 0;
   }

   if ( m_bUseMapDlgUnits )
   {
      m_pWndDef->PSDLG_X = mConvertMapDlgToPixelX( m_pWndDef->PSDLG_X );
      m_pWndDef->PSDLG_Y = mConvertMapDlgToPixelY( m_pWndDef->PSDLG_Y );
      zSHORT nClientWidth = mConvertMapDlgToPixelX( zHIUSHORT( m_pWndDef->SZDLG_X ) );
      zSHORT nClientHeight = mConvertMapDlgToPixelY( zHIUSHORT( m_pWndDef->SZDLG_Y ) );
      m_pWndDef->SZDLG_X = mConvertMapDlgToPixelX( zLOUSHORT( m_pWndDef->SZDLG_X ) );
      m_pWndDef->SZDLG_Y = mConvertMapDlgToPixelY( zLOUSHORT( m_pWndDef->SZDLG_Y ) );

      Attr.X = m_pWndDef->PSDLG_X;
      Attr.Y = m_pWndDef->PSDLG_Y;
      Attr.W = m_pWndDef->SZDLG_X;
      Attr.H = m_pWndDef->SZDLG_Y;

      if ( m_ulSubtaskFlags & zSUBTASK_SINGLE_RELSIZE )
      {
         m_lRelLeft = m_lRelRight = 0;
         m_lRelTop = m_lRelBottom = 0;
         m_lOrigRelSizeX = nClientWidth;
         m_lOrigRelSizeY = nClientHeight;
      }
      else
      {
         m_lRelLeft = mConvertMapDlgToPixelX( zLOUSHORT( m_pWndDef->REL_X ) );
         m_lOrigRelSizeX = mConvertMapDlgToPixelX( zHIUSHORT( m_pWndDef->REL_X ) );
         m_lRelRight = nClientWidth - m_lOrigRelSizeX;
         m_lOrigRelSizeX -= m_lRelLeft;
         m_lRelTop = mConvertMapDlgToPixelY( zLOUSHORT( m_pWndDef->REL_Y ) );
         m_lOrigRelSizeY = mConvertMapDlgToPixelY( zHIUSHORT( m_pWndDef->REL_Y ) );
         m_lRelBottom = nClientHeight - m_lOrigRelSizeY;
         m_lOrigRelSizeY -= m_lRelTop;
      }
   }
   else
   {
      m_pWndDef->PSDLG_X = mConvertDlgUnitToPixelX( m_pWndDef->PSDLG_X );
      m_pWndDef->PSDLG_Y = mConvertDlgUnitToPixelY( m_pWndDef->PSDLG_Y );
      zSHORT nClientWidth = mConvertDlgUnitToPixelX( zHIUSHORT( m_pWndDef->SZDLG_X ) );
      zSHORT nClientHeight = mConvertDlgUnitToPixelY( zHIUSHORT( m_pWndDef->SZDLG_Y ) );
      m_pWndDef->SZDLG_X = mConvertDlgUnitToPixelX( zLOUSHORT( m_pWndDef->SZDLG_X ) );
      m_pWndDef->SZDLG_Y = mConvertDlgUnitToPixelY( zLOUSHORT( m_pWndDef->SZDLG_Y ) );

      Attr.X = m_pWndDef->PSDLG_X;
      Attr.Y = m_pWndDef->PSDLG_Y;
      Attr.W = m_pWndDef->SZDLG_X;
      Attr.H = m_pWndDef->SZDLG_Y;

      if ( m_ulSubtaskFlags & zSUBTASK_SINGLE_RELSIZE )
      {
         m_lRelLeft = m_lRelRight = 0;
         m_lRelTop = m_lRelBottom = 0;
         m_lOrigRelSizeX = nClientWidth;
         m_lOrigRelSizeY = nClientHeight;
      }
      else
      {
         m_lRelLeft = mConvertDlgUnitToPixelX( zLOUSHORT( m_pWndDef->REL_X ) );
         m_lOrigRelSizeX = mConvertDlgUnitToPixelX( zHIUSHORT( m_pWndDef->REL_X ) );
         m_lRelRight = nClientWidth - m_lOrigRelSizeX;
         m_lOrigRelSizeX -= m_lRelLeft;
         m_lRelTop = mConvertDlgUnitToPixelY( zLOUSHORT( m_pWndDef->REL_Y ) );
         m_lOrigRelSizeY = mConvertDlgUnitToPixelY( zHIUSHORT( m_pWndDef->REL_Y ) );
         m_lRelBottom = nClientHeight - m_lOrigRelSizeY;
         m_lOrigRelSizeY -= m_lRelTop;
      }
   }

   // Ensure that the original relative sizes are non-zero for later divide.
   if ( m_lOrigRelSizeX == 0 )
      m_lOrigRelSizeX = 1;

   if ( m_lOrigRelSizeY == 0 )
      m_lOrigRelSizeY = 1;

#ifdef DEBUG_RESIZE
   TraceLineS( "Window Caption ===================> ", m_pWndDef->Caption );

   TraceLineI( "  RelLeft: ", zLOUSHORT( m_pWndDef->REL_X ) );
   TraceLineI( "  RelRight: ", zHIUSHORT( m_pWndDef->REL_X ) );
   TraceLineI( "  RelTop: ", zLOUSHORT( m_pWndDef->REL_Y ) );
   TraceLineI( "  RelBottom: ", zHIUSHORT( m_pWndDef->REL_Y ) );

   TraceLineI( "PSDLG_X ", m_pWndDef->PSDLG_X );
   TraceLineI( "PSDLG_Y ", m_pWndDef->PSDLG_Y );
   TraceLineI( "SZDLG_X ", m_pWndDef->SZDLG_X );
   TraceLineI( "SZDLG_Y ", m_pWndDef->SZDLG_Y );

   TraceLineI( "nClientWidth ", nClientWidth );
   TraceLineI( "nClientHeight ", nClientHeight );

   TraceLineI( "m_lRelTop ", m_lRelTop );
   TraceLineI( "m_lRelBottom ", m_lRelBottom );
   TraceLineI( "m_lRelLeft ", m_lRelLeft );
   TraceLineI( "m_lRelRight ", m_lRelRight );
   TraceLineI( "m_lOrigRelSizeX ", m_lOrigRelSizeX );
   TraceLineI( "m_lOrigRelSizeY ", m_lOrigRelSizeY );
#if 0
   // We have the top-most/left-most positions of any fixed-position/
   // relative-size controls.  We also have the bottom-most/right-most
   // extents of any relative-size controls, or the bottom-most/
   // right-most top-left positions of any relative-position controls ...
   // whichever is bottom-most/right-most.

   // In the following example, we will show the algorithm for setting
   // up the proper relative positions and sizes of the three controls:
   // A, B, and C.  Things are not exactly to scale, but hopefully this
   // will give a meaningful picture.  The example is only for the Y
   // direction, but there is a parallel discussion for the X direction.
   // With respect to relative position and size, we are interested only
   // in the smallest box which encompasses all controls that have
   // relative position and/or relative size.  This original box is
   // determined by the conversion algorithm and we hold onto its size
   // using the variables m_lOrigRelSizeX and m_lOrigRelSizeY.  We also
   // keep track of the original border around this box using the
   // variables m_lRelTop, m_lRelLeft, m_lRelBottom, and m_lRelRight.
   // Fo convenience in this example, assume m_lRelTop, m_lRelLeft,
   // m_lRelBottom, and m_lRelRight are all 2.  Assume C is 12 units
   // high, A is 4 units high, and B is 4 units high.  A's y-position is
   // 5, B's y-position is 10, and C's y-position is of course 2.
   // Now let's assume that the window is resized in the Y direction from
   // a total of 16 units to a total of 24 units.  The new box containing
   // the relative position/size controls is now 20 units high.  The
   // ratio from old to new sizes in the box is 5/3 (12 * 5 / 3 == 20).
   //
   // The effect on C is the simplest.  Its y-position remains fixed at
   // 2 and its height changes from 12 to 20.
   //
   // The effect on B is also quite straight forward.  Multiplying its
   // relative position by 5/3, we get a new position of (10 - 2) * 5/3 =
   // 13 1/3, which in absolute terms is 15 1/3.  Multiplying its relative
   // size by 5/3, we get a new relative size of 4 * 5/3 == 6 2/3.
   //
   // A's y-position remains fixed at 5.  Its relative size is determined
   // by multiplying its relative bottom position of 7 by 5/3 which gives
   // us a relative size of 11 2/3.  From that we subtract the fixed
   // position of A within the relative box giving us 8 2/3.
   //
   // Adding up all the y-values (ignoring C), we have:
   //
   //    2        - m_lRelTop
   //    3        - A's fixed position in the relative box
   //    8 2/3    - A's relative size
   //    1 2/3    - space between A and B (original 1 * 5/3)
   //    6 2/3    - B's relative size
   //    2        - m_lRelBottom
   //  ÄÄÄÄÄÄÄ
   //   24
   //
   // The one case not covered is when there is a fixed size control
   // with relative position.  Everything is done the same as for
   // control B, but the position is determined by subtracting the
   // height from the bottom of the relative size rectangle.
   //
   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³ (m_lRelPsX, m_lRelPsY)      (m_lRelPsX, m_lRelPsY)         ³
   ³ |                            |                             ³
   ³ -----------------------------ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ - m_³
   ³ |                            ³C - fixed position     ³ | l ³
   ³ |                            ³    relative size      ³ | O ³
   ³ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿    ³                       ³ | r ³
   ³ ³A - fixed position     ³    ³                       ³ | i ³
   ³ ³    relative size      ³    ³                       ³ | g ³
   ³ ³                       ³    ³ m_lRelSzY             ³ | R ³
   ³ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ    ³                       ³ | e ³
   ³ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿    ³                       ³ | l ³
   ³ ³B - relative position  ³    ³                       ³ | S ³
   ³ ³    relative size      ³    ³                       ³ | i ³
   ³ ³       m_lRelSzX       ³    ³                       ³ | z ³
   ³ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ----ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ - e ³
   ³ |----------------------------------------------------|   Y ³
   ³                  m_lOrigRelSizeX                           ³
   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ


   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³ (m_lRelPsX, m_lRelPsY)      (m_lRelPsX, m_lRelPsY)         ³
   ³ |                            |                             ³
   ³ -----------------------------ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ -   ³
   ³ |                            ³C                      ³ |   ³
   ³ |                            ³                       ³ |   ³
   ³ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿    ³                       ³ |   ³
   ³ ³A                      ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³                       ³    ³ m_lRelSzY             ³ |   ³
   ³ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ    ³                       ³ |   ³
   ³ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿    ³                       ³ |   ³
   ³ ³B                      ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³                       ³    ³                       ³ |   ³
   ³ ³       m_lRelSzX       ³    ³                       ³ |   ³
   ³ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ----ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ -   ³
   ³ |----------------------------------------------------|     ³
   ³                  m_lOrigRelSizeX                           ³
   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

#endif
#endif

#if 0
   COLORREF cref;
   zLONG  rgb;

   k = 0;
   nRC = SetCursorFirstEntity( m_vDialog, szlWndColor, 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      GetIntegerFromAttribute( &rgb, m_vDialog, szlWndColor, szlRGB );
      cref = fnTranslateColor( rgb );
      switch ( k )
      {
         case 0:
            m_clrText = cref;       // window text color (0 ==> windows dflt)
            break;

         case 1:
            m_clrBk = cref;
            break;

         case 2:
            m_clrErrText = cref;
            break;

//???    case 3:
//          m_clrErrText = cref;
//          break;
      }

      k++;
      nRC = SetCursorNextEntity( m_vDialog, szlWndColor, 0 );
   }
#endif

   zVIEW vProfile;

   if ( m_pWndDef->ProfileView[ 0 ] &&
        GetViewByName( &vProfile, m_pWndDef->ProfileView, m_vDialog, zLEVEL_ANY ) > 0 )
   {
      m_pzsProfileViewName = new CString( m_pWndDef->ProfileView );
      RestoreWindowPlacement( m_vDialog, vProfile );
   }

   m_ulWndOper = *((zPLONG) m_pWndDef->OperCtrl);
   if ( fCreateModal < 0 )   // indicates we are resuming from the painter
      ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_PREBUILD_POSTCODE );
   else
      ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_PREBUILD_PRECODE );

   // Based on flags in the Dialog, do the right thing here (MDI/SDI, 3D)???
#pragma mMSG( Override OnUpdateFrameTitle for setting caption )
   if ( m_pWndDef->Caption[ 0 ] )
      SetCaptionTitle( m_pWndDef->Caption, 0, FALSE );

#ifdef zREMOTE_SERVER
   m_pZSocketTask->LockMutex( ?, FALSE, "ZSubtask::ctor" );
#endif
}

// ZSubtask - alternate ctor
ZSubtask::ZSubtask( ZTask  *pZTask,    // Driver C++ task object
                    CWnd   *pCWnd )    // Parent window (from existing app)
{
   m_ulSubtaskIdNbr = g_lIdNbr++;

   if ( pZTask && (pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      TraceLine( "ZSubtask::ZSubtask ALTERNATE ctor (0x%08x): %d", this, m_ulSubtaskIdNbr );
   }

   // initialize flags/pointers
   m_pZTask = pZTask;
   m_pZTask->m_uAppState &= ~zAPP_STATE_TERMINATED;
   m_pZTask->m_bDeletingSplitter = FALSE;
   m_pZParent = 0;
   m_pZOwner = 0;
   m_pZFWnd = 0;
   m_pZView = 0;
   m_hMenuDefault = 0;
   m_hMenuDocTemplate = 0;
   m_bStopEvents = FALSE;
   m_lRelease = 0;
   m_vPE = 0;  // used only during construction
   m_ulSubtaskFlags = zSUBTASK_INITIALIZE;   // no flags set yet

   if ( m_pZTask->m_szInitialDlgName[ 0 ] == 0 )          // DON
      m_pZTask->m_szInitialDlgName[ 0 ] = '.';

   m_pzsDlgTag = new CString( "." );
   m_pzsWndTag = new CString( "." );
   m_pzsLastTag = 0;
   m_pzsLastCtrlTag = 0;
   m_pzsProfileViewName = 0;
   m_pchWindowPlacement = 0;
   m_lExtentX = m_lExtentY = 0;
   m_nInvisible = m_nDisabled = 0;
   m_pEventParms = 0;
// m_lActType = 0;
// m_pzsAction = 0;
// m_pzsActDlg = m_pzsActWnd = 0;
   m_pzsResumeAction = 0;
   m_nDrawMenuBar = 0;
   m_pZBinPopup = 0;
   m_pTrackMenu = 0;
   m_pzsPopupTag = 0;
   m_pZBinMenu = 0;
   m_pMenu = 0;
   m_pzsMenuTag = 0;
   m_pZMIXCtrl = 0;
   m_pDfltBtn = 0;
   m_pCurrDfltBtn = 0;
   m_pDIL = 0;
   m_pchEnabledAction = 0;
   m_pzsCaption = 0;
   m_pzsTitle = 0;
   m_pzmaFirstFocus = 0;
   m_pzmaLastFocus = 0;
   m_pzmaWithFocus = 0;
   m_pzmaLastFlyBy = 0;
   m_ulFlyByTickCnt = 0;
   m_pzmaAccel = 0;
   m_uMouseStatus = zMOUSE_STATUS_OFF;
   m_szActionName[ 0 ] = 0;
   m_pAccels = 0;
   m_nDIL_Items = 0;
   m_lMsgCmdId = 0;
   m_cpcCurrOper = 0;
   m_BarTipList.SetSize( 4, 4 );
   m_nBarTipCnt = 0;
   m_ulNextBarTipCmd = zZEIDON_FIRST_TOOLBAR_CMD;
   m_pZSubtaskProxy = 0;
   m_pZSubtaskGlobal = 0;
   m_pZSubtaskParent = 0;
   m_pSplitterView = 0;
   m_pZPrintout = 0;
   m_vInterpSubtask = 0;
   m_hLibrary = 0;
   m_hLibRes = 0;
   m_hInstDLL = 0;
   m_hInstRes = 0;
   m_clrText = 0;
   m_clrErrText = zRGB( 255, 0, 0 ); // default to red
// m_clrBk = RGB( 0, 255, 255 ); teal test
   m_clrBk = ::GetSysColor( COLOR_BTNFACE );
   m_ulWndOper = 0;
   m_pzsDLL_Name = 0;
   m_vDialog = 0;
   m_vMsgQ = 0;
   m_pWndDef = 0;

   m_pFontWS = 0;
   m_pFontCtrl = 0;
   m_bUseMapDlgUnits = FALSE;

#ifdef zREMOTE_SERVER
   m_lTID = (zLONG) AfxGetThread( )->m_nThreadID;
#else
   m_lTID = SysGetTaskFromView( g_vRegister );
   if ( pZTask->m_pZSubtaskTop == 0 )
      pZTask->m_pZSubtaskTop = this;
#endif

   // Add this subtask to application and global lists.
   ZSubtask::InitializeSubtaskState( this );
   ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_EXTERNAL_APP );

   m_lRelLeft = 0;
   m_lRelRight = 0;
   m_lOrigRelSizeX = 0;
   m_lRelTop = 0;
   m_lRelBottom = 0;
   m_lOrigRelSizeY = 0;
}

// Recursive routine to guarantee the child controls are deleted before
// their parents.
void
fnDeleteCtrls( ZMultiIdxSet *pZMIXCtrl, ZMapAct *pzmaComposite )
{
   if ( pZMIXCtrl == 0 )
      return;

   ZMapAct *pzma;
   zLONG   k;

#if 0  // for debug only
   if ( pzmaComposite == 0 )
   {
      zCHAR szBuffer[ 256 ];
      for ( k = pZMIXCtrl->uNodeCnt - 1; k >= 0; k-- )
      {
         pzma = (ZMapAct *) *(pZMIXCtrl->pvNode + k);
         if ( pzma->m_pzmaComposite )
         {
            strcpy_s( szBuffer, zsizeof( szBuffer ), "Delete ctrl " );
            strcat_s( szBuffer, zsizeof( szBuffer ), *(pzma->m_pzsTag) );
            strcat_s( szBuffer, zsizeof( szBuffer ), " with composite " );
            TraceLineS( szBuffer, *(pzma->m_pzmaComposite->m_pzsTag) );
         }
         else
            TraceLineS( "Delete ctrl ", *(pzma->m_pzsTag) );
      }
   }
#endif

   for ( k = pZMIXCtrl->GetCount( ) - 1; k >= 0; k-- )
   {
      if ( *(pZMIXCtrl->m_pvNode + k) )
      {
         pzma = (ZMapAct *) *(pZMIXCtrl->m_pvNode + k);
         if ( pzmaComposite == 0 || (pzmaComposite && pzmaComposite == pzma->m_pzmaComposite) )
         {
         // TraceLineS( "fnDeleteCtrls child ", *(pzma->m_pzsTag) );
            fnDeleteCtrls( pZMIXCtrl, pzma );  // delete children first

            // mDeleteInit cannot be used in this case since a delete of
            // pzma->m_pCtrl causes the ZMapAct itself to be deleted
            // which in turn would make the reference to m_pCtrl (to
            // zero it out) through pzma invalid!!!
         // mDeleteInit( pzma->m_pCtrl );

            // Since the ZMapAct dtor is virtual, things will be dandy!
            if ( pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) )
               pzma->m_pCtrl->DestroyWindow( );

            // Null it out so it won't be processed again.
            *(pZMIXCtrl->m_pvNode + k) = 0;

            delete( pzma );
         }
      }
   }
}

// ZSubtask  - dtor
ZSubtask::~ZSubtask( )
{
   zULONG ulSubtaskState = ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_DELETED );

#ifdef zREMOTE_SERVER
   zCHAR szMsg[ 128 ];
   if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      sprintf_s( szMsg, zsizeof( szMsg ), "[S%ld.T%ld.t%ld.s%ld] ZSubtask::dtor #$# "
                       "state: %#06hx   Subtask: ",
                m_pZSocketTask,
                AfxGetThread( ),
                m_pZSocketTask->m_pWinThread,
                m_pZSocketTask->m_sock,
                ulSubtaskState );
      TraceLineX( szMsg, (zLONG) this );
   }
#endif

   if ( g_pSubtaskList && (ulSubtaskState & zSUBTASK_STATE_DELETED) == zSUBTASK_STATE_DELETED )
   {
      return;
   }

#ifdef DEBUG_ALL
   zLONG lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
   while ( lItemCnt )
   {
      if ( g_pSubtaskList[ lItemCnt ].pZSubtask == this )
         break;

      lItemCnt--;
   }

   TraceLine( "**********************> ZSubtask::dtor: [0x%08x]  IdNbr: %d  "
               "Task: 0x%08x  Dlg.Wnd: %s.%s   vDialog: 0x%08x  hWnd: 0x%08x",
              this, m_ulSubtaskIdNbr, m_pZTask, *m_pzsDlgTag, *m_pzsWndTag,
              m_vDialog, m_pZFWnd ? m_pZFWnd->m_hWnd : 0 );
   ListWindowsAndControls( this, "ZSubtask::dtor", 0 );
#endif

   if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      if ( m_pzsDlgTag && m_pzsWndTag )
         TraceLine( "ZSubtask::dtor [0x%08x] IdNbr: %d  %s.%s", this, m_ulSubtaskIdNbr, *m_pzsDlgTag, *m_pzsWndTag );
      else
         TraceLine( "ZSubtask::dtor [0x%08x] IdNbr: %d", this, m_ulSubtaskIdNbr );
   }

#ifdef zREMOTE_SERVER
// TraceLineI( "ZSubtask dtor: ", (zLONG) this );
   m_pZSocketTask->LockMutex( ?, TRUE, "ZSubtask::dtor" );

   mDeleteInit( m_pzsAppTag );
   if ( m_pZSocketTask && m_pZSocketTask->m_pCacheWndList )
   {
      SetRemoteWndAttribute( m_vDialog, "Closed", "Y" );
      sprintf_s( szMsg, zsizeof( szMsg ), "ZSubtask::dtor %s", *m_pzsRemoteWndTag );
      ZXRA_Item *pXRA = m_pZSocketTask->m_pCacheWndList->Find( *m_pzsRemoteWndTag, this, szMsg );
      if ( pXRA )
      {
         pXRA->m_pZSubtask = 0;

         // Get rid of definition + deltas ... reset to definition.
         mDropOI_Init( pXRA->m_vXRA );
         ActivateOI_FromOI_ForTask( &(pXRA->m_vXRA), pXRA->m_vXRA_Def, 0, zSINGLE );

         if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
         {
            CString cs = *m_pzsDlgTag;
            cs += *m_pzsWndTag;
            cs += "__XRA";
            SetNameForView( pXRA->m_vXRA, cs, m_vDialog, zLEVEL_TASK );
         }

         SetAttributeFromString( pXRA->m_vXRA, "App", "Definition", "" );
      }
   }

   mDeleteInit( m_pzsRemoteWndTag );
   mDeleteInit( m_pzsImageURL );

#endif

#if 0
   zVIEW vSubtask;

   if ( m_ulSubtaskFlags & zSUBTASK_APPLICATION_OPERATION ||
        GetViewByName( &vSubtask, "__ZDrSubtask", m_vDialog, zLEVEL_TASK ) > 0 )
   {
      MSG   msg;

      // Just wait until mapping has completed.  Dispatch all messages.
      TraceLineS( "(drvr) Waiting for Application Operation to complete ", "for ZSubtask destructor" );

      while ( m_ulSubtaskFlags & zSUBTASK_APPLICATION_OPERATION ||
              GetViewByName( &vSubtask, "__ZDrSubtask", m_vDialog, zLEVEL_TASK ) > 0 )
      {
         while ( ::PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
         {
            ::TranslateMessage( &msg );
            ::DispatchMessage( &msg );
         }
      }
   }
#endif

   // Throughout we are assuming that the interface element (GUI object)
   // invokes the deletion of the subtask ... if this is determined to
   // be untrue (there may be timing issues), this assumption and its
   // consequences may need to be re-examined.
   //
// if ( (m_ulSubtaskFlags & zSUBTASK_CREATED_MODAL) && m_pZFWnd )
//    m_pZTask->EndModal( 0 );

   // Delete any report (and associated resources)
//???   mDeleteInit( m_pZPrintout );

   ZDrFrame *pZFWnd;  // hold for Splitter processing
   ZSubtask *pZSubtaskMain = GetSplitterMainSubtask( );
   if ( pZSubtaskMain && pZSubtaskMain != this )
   {
      pZFWnd = (ZDrFrame *) pZSubtaskMain->m_pZFWnd;
//    pZFWnd = (ZDrFrame *) ::AfxGetMainWnd( );
   }
   else
   {
      pZFWnd = (ZDrFrame *) m_pZFWnd;
//    pZFWnd = (ZDrFrame *) ::AfxGetMainWnd( );
   }

   // This has to be done or else "late" size/move messages bomb.
   ZDrView *pZView = m_pZView;  // hold for Splitter processing
   if ( m_pZView )
   {
      m_pZView->m_pZSubtask = 0;
      m_pZView = 0;
   }

   CleanupBarTips( );

   // Delete GUI stuff associated with this window first.
   if ( m_pZMIXCtrl )
   {
      fnDeleteCtrls( m_pZMIXCtrl, 0 );
      mDeleteInit( m_pZMIXCtrl );
   }

   mDeleteInit( m_pFontWS );
   mDeleteInit( m_pFontCtrl );

   if ( m_pZFWnd && mIs_hWnd( m_pZFWnd->m_hWnd ) )
      m_pZFWnd->SetMenu( 0 );

   mDeleteInit( m_pMenu );
   mDeleteInit( m_pZBinMenu );
   mDeleteInit( m_pZBinPopup );
   mDeleteInit( m_pTrackMenu );

   // Unlink ties to the GUI objects.
   if ( m_pZFWnd )
   {
      m_pZFWnd->SetActiveView( 0 );
   // TraceLine( "ZSubtask dtor setting active view to null for ZFWnd: 0x%08x   Wnd: 0x%08x",
   //            m_pZFWnd, m_pZFWnd->m_hWnd );

      if ( m_hMenuDefault )
         m_pZFWnd->m_hMenuDefault = m_hMenuDefault;

//    m_pZFWnd->m_pZSubtask = 0;
      m_pZFWnd = 0;
   }

   mDeleteInit( m_pzsDlgTag );
   mDeleteInit( m_pzsDLL_Name );
   mDeleteInit( m_pzsWndTag );
   mDeleteInit( m_pzsProfileViewName );
   mDeleteInit( m_pWndDef );

   mDeleteInitA( m_pchWindowPlacement );
   mDeleteInitA( m_pAccels );

   mDeleteInitA( m_pchEnabledAction );

   mDeleteInit( m_pzsMenuTag );
   mDeleteInit( m_pzsPopupTag );
// mDeleteInit( m_pzsAction );
// mDeleteInit( m_pzsActDlg );
// mDeleteInit( m_pzsActWnd );
   mDeleteInit( m_pzsResumeAction );
   mDeleteInit( m_pzsCaption );
   mDeleteInit( m_pzsTitle );

// mDeleteInit( m_pMenu );    // done in ZDrFrame's dtor

   if ( m_pZTask )
      m_pZTask->DeleteZWnd( this );

   ZSubtask::TerminateSubtaskState( this );

   if ( m_vMsgQ )
      DropView( m_vMsgQ );

// if ( m_hLibrary )                   let object engine take care of this
//    SysFreeLibrary( m_vDialog, m_hLibrary );

// ListWindowsAndControls( this, "ZSubtask::dtor2", 0 );
   if ( pZView && pZView->m_pParentSplitterWnd && (m_ulSubtaskFlags & zSUBTASK_SUBWND_SPLITTER_PANE) )
   {
      zBOOL bPostQuit = FALSE;

      m_pZTask->m_bDeletingSplitter = TRUE;
#ifdef DEBUG_ALL
      if ( g_pSubtaskList[ lItemCnt ].pZSubtask &&
           g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag &&
           g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag )
      {
         TraceLine( "%d.%d Dlg.Wnd %s.%s   Task: 0x%08x   Subtask: 0x%08x  Wnd: 0x%08x [%s]",
                    lItemCnt, g_pSubtaskList[ lItemCnt ].pZSubtask->m_ulSubtaskIdNbr,
                    *(g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag),
                    *(g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag),
                    g_pSubtaskList[ lItemCnt ].pZSubtask->m_lTID,
                    g_pSubtaskList[ lItemCnt ].pZSubtask,
                    g_pSubtaskList[ lItemCnt ].hWnd, "SPLITTER_PANE" );
      }
      else
         TraceLine( "Subtask1 [0x%08x] deleted from global table at Item: %d",
                    g_pSubtaskList[ lItemCnt ].pZSubtask, lItemCnt );
#endif
      ASSERT( pZView->m_eQuad != ZDrView::eUndef );

      ZDrFrame *pMainFrame;
      if ( pZFWnd )
         pMainFrame = pZFWnd;
      else
         pMainFrame = (ZDrFrame *) AfxGetMainWnd( );

      ZSplitterWnd *pParentSplitterWnd = (ZSplitterWnd *) pZView->GetParent( );
      ASSERT( pParentSplitterWnd == pZView->m_pParentSplitterWnd );
      ZSplitterView *pParentSplitterView = DYNAMIC_DOWNCAST( ZSplitterView, pParentSplitterWnd->GetParent( ) );

      zSHORT nRow = (pZView->m_eQuad == ZDrView::eBottom) ? 1 : 0;
      zSHORT nCol = (pZView->m_eQuad == ZDrView::eRight) ? 1 : 0;
      zSHORT nRow2 = (pZView->m_eQuad == ZDrView::eTop) ? 1 : 0;
      zSHORT nCol2 = (pZView->m_eQuad == ZDrView::eLeft) ? 1 : 0;

      ZParentData  *pParentData;
      ZSplitterWnd *pSplitterWnd;

      if ( pZView->m_pParentSplitterView )
      {
#ifdef DEBUG_ALL
         if ( g_pSubtaskList[ lItemCnt ].pZSubtask &&
              g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag &&
              g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag )
         {
            TraceLine( "%d.%d Dlg.Wnd %s.%s   Task: 0x%08x   Subtask: 0x%08x  Wnd: 0x%08x [%s]",
                       lItemCnt, g_pSubtaskList[ lItemCnt ].pZSubtask->m_ulSubtaskIdNbr,
                       *(g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag),
                       *(g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag),
                       g_pSubtaskList[ lItemCnt ].pZSubtask->m_lTID,
                       g_pSubtaskList[ lItemCnt ].pZSubtask,
                       g_pSubtaskList[ lItemCnt ].hWnd, "SPLITTER_PANE2" );
         }
         else
            TraceLine( "Subtask2 [0x%08x] deleted from global table at Item: %d",
                       g_pSubtaskList[ lItemCnt ].pZSubtask, lItemCnt );
#endif
         ASSERT( pParentSplitterView == 0 || pParentSplitterView == pZView->m_pParentSplitterView );
         pParentSplitterView = pZView->m_pParentSplitterView;

         // We've got a splitter and a pane that need to be deleted, as well
         // as the corresponding splitter view (if any).
         // The "other" pane needs to be "re-parented" to the proper pane of
         // the parent splitter.
         // First find the "other" pane.

         pParentData = pZView->m_pParentSplitterView->m_pParentData;
         pZView->m_pParentSplitterView->m_pParentData = 0;
         if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
         {
#ifdef DEBUG_ALL
            if ( g_pSubtaskList[ lItemCnt ].pZSubtask &&
                 g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag &&
                 g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag )
            {
               TraceLine( "ZSubtask::dtor ParentData for Pane( %d, %d ):   "
                             "ParentSplitterView: 0x%08x  "
                              "ParentSplitterWnd: 0x%08x  SplitterView: 0x%08x",
                           pParentData->m_nRow,
                           pParentData->m_nCol,
                           pParentData->m_pParentSplitterView,
                           pParentData->m_pParentSplitterWnd,
                           pParentData->m_pSplitterView );
            }
            else
               TraceLine( "Subtask3 [0x%08x] deleted from global table at Item: %d",
                          g_pSubtaskList[ lItemCnt ].pZSubtask, lItemCnt );
#endif
         }

         // Just to shorten code a bit, address the splitter directly.
         pSplitterWnd = pParentData->m_pSplitterView->m_pSplitterWnd;
         ASSERT( pParentSplitterWnd == pSplitterWnd );

         pParentSplitterWnd = pParentData->m_pParentSplitterWnd;

         // The other "pane" may be either a ZDrView or a ZSplitterView.
         CView *pPane = (CView *) pSplitterWnd->GetPane( nRow2, nCol2 );
         if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
         {
            TraceLine( "ZSubtask::dtor ParentSplitterWnd: 0x%08x for Pane( %d, %d ): 0x%08x Pane( %d, %d ): 0x%08x",
                         pParentSplitterWnd, nRow, nCol, pZView, nRow2, nCol2, pPane );
         }

         pPane->SetParent( pParentSplitterWnd );
         pPane->SetDlgCtrlID( pParentSplitterWnd->IdFromRowCol( pParentData->m_nRow, pParentData->m_nCol ) );

         if ( pSplitterWnd->m_pZView )
         {
            pSplitterWnd->m_pZView->m_pParentSplitterWnd = 0;
            pSplitterWnd->m_pZView = 0;
         }

         // We have to re-parent the (Splitter or ZDr) View (done above) and reset
         // the corresponding structures to reflect the re-parenting.
         if ( pSplitterWnd->m_bSplitterView[ nRow2 ][ nCol2 ] ) // SplitterView
         {
            TraceLine( "ZSubtask::dtor for SplitterView (0x%08x): %d", pPane );
            ZSplitterView *pOtherView = (ZSplitterView *) pPane;

            pParentData->m_pParentSplitterWnd->m_bSplitterView[ pParentData->m_nRow ][ pParentData->m_nCol ] = TRUE;
            if ( pParentData->m_pParentSplitterWnd->m_pZSubtask1 == this )
            {
               pParentData->m_pParentSplitterWnd->m_pZSubtask1 =
                  pOtherView->m_pParentData->m_pParentSplitterView->m_pSplitterWnd->m_pZSubtask1;
            }
            else
            {
               pParentData->m_pParentSplitterWnd->m_pZSubtask2 =
                  pOtherView->m_pParentData->m_pParentSplitterView->m_pSplitterWnd->m_pZSubtask2;
            }

            pOtherView->m_pParentData->m_pParentSplitterView = pParentData->m_pParentSplitterView;
            pOtherView->m_pParentData->m_pParentSplitterWnd = pParentData->m_pParentSplitterWnd;
            pOtherView->m_pParentData->m_nRow = pParentData->m_nRow;
            pOtherView->m_pParentData->m_nCol = pParentData->m_nCol;
            pMainFrame->SetActiveView( pOtherView );
         }
         else
         {
            if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
               TraceLine( "ZSubtask::dtor for ZDrView (0x%08x): %d", pPane );

            ZDrView *pOtherPaneView = (ZDrView *) pPane;

            pParentData->m_pParentSplitterWnd->
                     m_bSplitterView[ pParentData->m_nRow ][ pParentData->m_nCol ] = FALSE;

            if ( pSplitterWnd->m_pZSubtask1 == this && pParentData->m_pParentSplitterWnd->m_pZSubtask2 == this )
            {
               pParentData->m_pParentSplitterWnd->m_pZSubtask2 = pSplitterWnd->m_pZSubtask2;
            }

            pOtherPaneView->m_pParentSplitterView = pParentData->m_pParentSplitterView;
            pOtherPaneView->m_pParentSplitterWnd = pParentSplitterWnd;
            if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
            {
               TraceLine( "ZSubtask::dtor OtherPaneView (0x%08x): has ParentSplitterWnd (0x%08x)",
                          pOtherPaneView, pOtherPaneView->m_pParentSplitterWnd );
            }

            if ( pParentData->m_nRow == 0 && pParentData->m_nCol == 0 )
            {
               int nRowCnt = pParentSplitterWnd->GetRowCount( );
               int nColCnt = pParentSplitterWnd->GetColumnCount( );
               if ( nRowCnt > nColCnt )
                  pOtherPaneView->m_eQuad = ZDrView::eTop;
               else
                  pOtherPaneView->m_eQuad = ZDrView::eLeft;
            }
            else
            if ( pParentData->m_nRow )
                 pOtherPaneView->m_eQuad = ZDrView::eBottom;
            else
            if ( pParentData->m_nCol )
                 pOtherPaneView->m_eQuad = ZDrView::eRight;

         // pOtherPaneView->SetParent( pParentSplitterWnd ); these cause improper behavior when
         // pParentSplitterWnd->SetParent( pMainFrame );     there are more than two frames
            pMainFrame->SetActiveView( pOtherPaneView );
         }

         pZView->DestroyWindow( );
         ASSERT( pSplitterWnd->DestroyWindow( ) );
         pParentData->m_pSplitterView->DestroyWindow( );
         mDeleteInit( pParentData );
         pParentSplitterWnd->RecalcLayout( );
         pMainFrame->RecalcLayout( );
         m_ulSubtaskFlags &= ~zSUBTASK_SUBWND_SPLITTER_PANE;
      }
      else  // of:  if ( pZView->m_pParentSplitterView )
      {
#ifdef DEBUG_ALL
         if ( g_pSubtaskList[ lItemCnt ].pZSubtask &&
              g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag &&
              g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag )
         {
            TraceLine( "%d.%d Dlg.Wnd %s.%s   Task: 0x%08x   Subtask: 0x%08x  Wnd: 0x%08x [%s]",
                       lItemCnt, g_pSubtaskList[ lItemCnt ].pZSubtask->m_ulSubtaskIdNbr,
                       *(g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag),
                       *(g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag),
                       g_pSubtaskList[ lItemCnt ].pZSubtask->m_lTID,
                       g_pSubtaskList[ lItemCnt ].pZSubtask,
                       g_pSubtaskList[ lItemCnt ].hWnd, "SPLITTER_PANE3" );
         }
         else
            TraceLine( "Subtask4 [0x%08x] deleted from global table at Item: %d",
                       g_pSubtaskList[ lItemCnt ].pZSubtask, lItemCnt );
#endif
         ZSubtask *pOtherSubtask;
         ZDrView  *pOtherView;

         pSplitterWnd = pZView->m_pParentSplitterWnd;
         if ( pSplitterWnd->m_pZSubtask1 == this )
         {
            if ( (ZSubtask::GetSubtaskState( pSplitterWnd->m_pZSubtask2 ) & zSUBTASK_STATE_MARK_FOR_DELETE) == 0 )
            {
               pOtherSubtask = pSplitterWnd->m_pZSubtask2;
            }
            else
               pOtherSubtask = (ZSubtask *) -1;
         }
         else
            pOtherSubtask = pSplitterWnd->m_pZSubtask1;

      // ASSERT( pSplitterWnd == pOtherView->m_pParentSplitterWnd );  can't!
      // ASSERT( m_ulSubtaskFlags & zSUBTASK_SPLITTER_MAIN_SUBTASK ); can't!

         m_ulSubtaskFlags &= ~zSUBTASK_SPLITTER_MAIN_SUBTASK;

         ZDrFrame *pOtherFWnd;
         if ( pOtherSubtask && pOtherSubtask != (ZSubtask *) -1 )
         {
            pOtherView = pOtherSubtask->m_pZView;
            pOtherSubtask->m_ulSubtaskFlags |= zSUBTASK_SPLITTER_MAIN_SUBTASK;
            pOtherFWnd = (ZDrFrame *) pOtherSubtask->m_pZFWnd;
         }
         else
         {
            if ( pOtherSubtask != (ZSubtask *) -1 )
               pOtherView = (ZDrView *) pSplitterWnd->GetPane( nRow2, nCol2 );
            else
               pOtherView = 0;

            pOtherFWnd = 0;
            bPostQuit = TRUE;
            TraceLineS( "ZSubtask destructor: ", "No subtask set for splitter pane" );
         }

         if ( pOtherView && pOtherView->m_pParentSplitterView )
         {
            // We've got a splitter (pSplitterWnd) and a subtask/view
            // (pZSubtask/pZView) that need to be deleted.  We also need to
            // delete the SplitterView (pOtherView->m_pParentSplitterView)
            // The other pane (pOtherView) needs to be "re-parented" to the
            // proper pane of the splitter that is the child of SplitterView.

            pParentData = pOtherView->m_pParentSplitterView->m_pParentData;
            pOtherView->m_pParentSplitterView->m_pParentData = 0;
            pParentSplitterWnd = pOtherView->m_pParentSplitterView->m_pSplitterWnd;
            pOtherView->m_pParentSplitterView->m_pSplitterWnd = 0;
            pParentSplitterView = pOtherView->m_pParentSplitterView;
            pOtherView->m_pParentSplitterView = 0;

            // The other "pane" may be either a ZDrView or a ZSplitterView.
            CView *pPane = (CView *) pSplitterWnd->GetPane( nRow2, nCol2 );
            ASSERT( pParentSplitterView == pPane );
            pParentSplitterView->SetDlgCtrlID( 0 );
            pParentSplitterView->ShowWindow( SW_HIDE );
            pParentSplitterView->SetParent( pZFWnd );

         // ASSERT( pParentSplitterWnd == pParentData->m_pParentSplitterWnd );

            TraceLine( "ZSubtask dtor ParentSplitterWnd: 0x%08x for Pane( %d, %d ): 0x%08x Pane( %d, %d ): 0x%08x\n",
                       pParentSplitterWnd, nRow, nCol, pZView, nRow2, nCol2, pPane );

            // Reset the pane's parent so we can delete the splitter and its view.
            CWnd *pParentWnd = pSplitterWnd->GetParent( );
            pParentSplitterWnd->SetParent( pParentWnd );
            pOtherView->SetParent( pParentSplitterWnd );
            pOtherView->SetDlgCtrlID( pParentSplitterWnd->IdFromRowCol( 0, 0 ) );

            if ( pMainFrame->IsChild( pOtherView ) )
               pMainFrame->SetActiveView( pOtherView );

            pZView->SetParent( pZFWnd );
            pZView->ShowWindow( SW_HIDE );
            pZView->SetDlgCtrlID( 0 );
         // pSplitterWnd->DestroyWindow( ); done below
            pZView->DestroyWindow( );
         // delete( pParentData->m_pSplitterView );
            mDeleteInit( pParentData );
         }
         else
         {
            pMainFrame->m_pSplitterWnd = 0;
            if ( ((ZDrFrame *) pZFWnd)->m_pSplitterWnd == pSplitterWnd )
               ((ZDrFrame *) pZFWnd)->m_pSplitterWnd = 0;

            if ( pOtherFWnd &&
                 ((ZDrFrame *) pOtherFWnd)->m_pSplitterWnd == pSplitterWnd )
            {
               ((ZDrFrame *) pOtherFWnd)->m_pSplitterWnd = 0;
            }

            if ( pParentSplitterWnd->m_pZView )
            {
               pParentSplitterWnd->m_pZView->m_pParentSplitterWnd = 0;
               pParentSplitterWnd->m_pZView = 0;
            }

            pParentSplitterWnd = 0;

            if ( pOtherView )
            {
               pOtherView->SetParent( pMainFrame );
               pOtherView->SetDlgCtrlID( pMainFrame->m_lPaneId );
               if ( pOtherView->m_pZSubtask )
                  pOtherView->m_pZSubtask->m_ulSubtaskFlags &= ~zSUBTASK_SUBWND_SPLITTER_PANE;

               pMainFrame->SetActiveView( pOtherView );
            }
         }

         m_ulSubtaskFlags &= ~zSUBTASK_SUBWND_SPLITTER_PANE;
         ASSERT( pZFWnd->m_pSplitterWnd == 0 || pZFWnd->m_pSplitterWnd == pSplitterWnd );
         pZFWnd->m_pSplitterWnd = 0;
         pSplitterWnd->m_pZView = 0;
         pSplitterWnd->DestroyWindow( );
         delete( pSplitterWnd );
      // pParentSplitterWnd->RecalcLayout( );

         pMainFrame->RecalcLayout( );
      }
#ifdef DEBUG_ALL
      if ( g_pSubtaskList[ lItemCnt ].pZSubtask &&
           g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag &&
           g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag )
      {
         TraceLine( "%d.%d Dlg.Wnd %s.%s   Task: 0x%08x   Subtask: 0x%08x  Wnd: 0x%08x [%s]",
                    lItemCnt, g_pSubtaskList[ lItemCnt ].pZSubtask->m_ulSubtaskIdNbr,
                    *(g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsDlgTag),
                    *(g_pSubtaskList[ lItemCnt ].pZSubtask->m_pzsWndTag),
                    g_pSubtaskList[ lItemCnt ].pZSubtask->m_lTID,
                    g_pSubtaskList[ lItemCnt ].pZSubtask,
                    g_pSubtaskList[ lItemCnt ].hWnd, "SPLITTER_PANE4" );
      }
      else
         TraceLine( "Subtask5 [0x%08x] deleted from global table at Item: %d",
                    g_pSubtaskList[ lItemCnt ].pZSubtask, lItemCnt );
#endif
      if ( pParentSplitterView )
      {
         ZSubtask *pZSubtask;
         zLONG lItem = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
         while ( lItem )
         {
            if ( g_pSubtaskList[ lItem ].pZSubtask && g_pSubtaskList[ lItem ].lTID == m_lTID &&
                 (g_pSubtaskList[ lItem ].ulSubtaskState & zSUBTASK_STATE_DELETED) != zSUBTASK_STATE_DELETED )
            {
               pZSubtask = g_pSubtaskList[ lItem ].pZSubtask;

            // CWnd *pFrameParent = pZSubtask->m_pZFWnd->GetParent( );
            // CWnd *pViewParent = pZSubtask->m_pZView->GetParent( );
            // CWnd *pSplitterViewParent = pZSubtask->m_pZView->m_pParentSplitterView ?
            //      pZSubtask->m_pZView->m_pParentSplitterView->GetParent( ) : 0;
            // CWnd *pSplitterWndParent = pZSubtask->m_pZView->m_pParentSplitterWnd ?
            //      pZSubtask->m_pZView->m_pParentSplitterWnd->GetParent( ) : 0;

               if ( pZSubtask->m_pZView && pZSubtask->m_pZView->m_pParentSplitterView &&
                    pZSubtask->m_pZView->m_pParentSplitterView->m_pParentData &&
                    pZSubtask->m_pZView->m_pParentSplitterView->m_pParentData->m_pParentSplitterView == pParentSplitterView )
               {
                  pZSubtask->m_pZView->m_pParentSplitterView->m_pParentData->m_pParentSplitterView = 0;
               }

               if ( pZSubtask->m_pZView &&
                    pZSubtask->m_pZView->m_pParentSplitterView == pParentSplitterView )
               {
                  pZSubtask->m_pZView->m_pParentSplitterView = 0;
               }
            }

            lItem--;
         }
      }

   // ListWindowsAndControls( this, "ZSubtask::dtor3", lItemCnt );
   // PumpMessages( m_vDialog );
      MSG   msg;

      while ( ::PeekMessage( &msg, 0, 0, 0, PM_NOREMOVE ) )
         m_pZTask->m_pZDrApp->PumpMessage( );

      m_pZTask->m_bDeletingSplitter = FALSE;
      if ( bPostQuit )
         AfxPostQuitMessage( 0 );
   }

   if ( m_vDialog )
   {
      if ( CheckExistenceOfEntity( m_vDialog, szlSubtask ) > zCURSOR_UNCHANGED )
         DeleteEntity( m_vDialog, szlSubtask, zPOS_AFTER );

      // the second parameter of SfDropSubtask is defined as:
      //    - 0 Bypass cleanup of Views
      //    - 1 For the Task of the subtask, drop all
      //        views that are NOT NAMED or NOT LOCKED.
      //    - 2 For the Task of the subtask, drop all
      //        views that are NOT NAMED or NOT LOCKED AND
      //        are also part of the same application.
      //
      if ( m_pZTask->m_vInterpSubtask )
         SfDropSubtask( m_vDialog, 2 );  // this may not be sufficient???
      else
         SfDropSubtask( m_vDialog, 2 );  // rather than 1 ... DG 10/22/96

      m_vDialog = 0;
   }

#ifdef zREMOTE_SERVER
   m_pZSocketTask->LockMutex( ?, FALSE, "ZSubtask::dtor" );
   if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      sprintf_s( szMsg, zsizeof( szMsg ), "[S%ld.T%ld.t%ld.s%ld] ZSubtask::dtor Termination: ",
                m_pZSocketTask,
                AfxGetThread( ),
                m_pZSocketTask->m_pWinThread,
                m_pZSocketTask->m_sock );
      TraceLineI( szMsg, (zLONG) this );
   }

// m_pZSocketTask = 0;
#endif
}

typedef zSHORT (POPERATION zFARPROC_CBAR)( CFrameWnd *, zCPCHAR, zBOOL );

/////////////////////////////////////////////////////////////////////////////
//
// This function permits the interface between the interpretor and the
// driver to function.  It is also germane to permitting a function to
// decide not to display the current window (e.g.  prebuild code may
// determine required information is not available).
//
/////////////////////////////////////////////////////////////////////////////
void
ZSubtask::RestartBuildWindow( zVIEW vAppSubtask )
{
// SysMutexLock( m_vDialog, "ZDw", 0, 0 );
   CWaitCursor wait;
   zULONG  ulSubtaskState = ZSubtask::GetSubtaskState( this );
   ZTask   *pZTask = m_pZTask;
   zLONG   lRC;

#ifdef zREMOTE_SERVER

   ZSocketTask *pZSocketTask = m_pZSocketTask;

   if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      zCHAR   szMsg[ 128 ];

      sprintf_s( szMsg, zsizeof( szMsg ), "[S%ld.T%ld.t%ld.s%ld] ZSubtask::RestartBuildWindow state: %#06hx  Subtask: ",
                 m_pZSocketTask, AfxGetThread( ), m_pZSocketTask->m_pWinThread, m_pZSocketTask->m_sock, ulSubtaskState );
      TraceLineI( szMsg, (zLONG) this );
   }
#endif

// TraceLine( "ZSubtask::RestartBuildWindow %s.%s *********** State: 0x%08x", *m_pzsDlgTag, *m_pzsWndTag, ulSubtaskState );

   if ( (ulSubtaskState & zSUBTASK_STATE_IN_CONSTRUCTION) == 0 || (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) )
   {
      TraceLineI( "RestartBuildWindow state error ", ulSubtaskState );
   // SysMutexUnlock( m_vDialog, "ZDw", 0 );
      return;     // we should not be here!!!
   }

   pZTask->m_pZSubtaskFocus = this;

   // This could almost be a nice case statement, but doesn't quite make
   // it because there are multiple cases that do not get to the goto's.
   ulSubtaskState &= 0x000000FF;
   if ( ulSubtaskState > zSUBTASK_STATE_PREBUILD_PRECODE )
   {
      if ( ulSubtaskState >= zSUBTASK_STATE_POSTBUILD_POSTCODE )
         goto POSTBUILD_POSTCODE_label;

      if ( ulSubtaskState >= zSUBTASK_STATE_POSTBUILD_PRECODE )
         goto POSTBUILD_PRECODE_label;

      if ( ulSubtaskState >= zSUBTASK_STATE_PREBUILD_POSTCODE )
         goto PREBUILD_POSTCODE_label;
   }

   if ( (m_ulWndOper & zWND_EVENT_PRE_BUILD) &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_PRE_BUILD, 0 ) > zCURSOR_UNCHANGED )
   {
      lRC = ProcessActionLoop( this, szlWndAct, 0, vAppSubtask, 0, TRUE, "PreBuild" );
      ulSubtaskState = ZSubtask::GetSubtaskState( this );

#ifdef zREMOTE_SERVER

      if ( pZSocketTask->m_lSocketState == -1 || (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) )
      {
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;
      }

#else

      if ( (pZTask->m_uAppState & zAPP_STATE_TERMINATED) || (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) )
      {
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;
      }

#endif

      if ( zHIUSHORT( lRC ) == 2 )
      {
         mDeleteInit( m_pzsResumeAction );
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;     // leave state at zSUBTASK_PREBUILD_PRECODE
      }

      vAppSubtask = 0;     // turn off debugger (if it was on)
   }

   ulSubtaskState = ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_PREBUILD_POSTCODE );

PREBUILD_POSTCODE_label:

   Attr.StyleEx = m_pWndDef->StyleEx;
   Attr.Style = m_pWndDef->Style;

#if 0 // def QUINSOFT
   {
   // Above existed... and added the following - PAS
   if ( m_pZTask->m_nOS_Version >= 60 &&
        m_pZTask->m_nOS_Version < 70 )
   {
   // Attr.Style = m_pWndDef->Style | 0x00030000; // looked good but minimizing,
                                                  // and restoring was a problem
                                                  // could have been the StyleEx was 1?
      Attr.Style = 0x00cf0000;   // hardcode like main menu
      Attr.StyleEx = 0;          // hardcode like main menu
   // if ( FALSE )
   // {
   //    Attr.Style = 0x00cf0000;  // resizeable and menu buttons
   //    Attr.Style = 0x00c80000;  // not resize and no menu buttons
   //    Attr.Style = 0x00cc0000;  // resize and no menu buttons
   //    Attr.Style = 0x80cf0000;  // resizeable and menu buttons
   //    Attr.Style = 0x80c80000;  // PAS quick test
   //    Attr.Style = 0x80cc0000;  // PAS quick test
   // }
   }
   }
#endif

#ifndef zREMOTE_SERVER
   if ( (m_ulSubtaskFlags & zSUBTASK_SUBWND_SPLITTER_PANE) == 0 )
   {
      if ( m_pZFWnd == 0 || mIs_hWnd( m_pZFWnd->m_hWnd ) == 0 )
         ulSubtaskState &= ~zSUBTASK_STATE_REPLACED_BY_SELF;

      if ( (ulSubtaskState & zSUBTASK_STATE_REPLACED_BY_SELF) == 0 )
         CreateZ( );

   // DragAcceptFiles( m_pZFWnd->m_hWnd, TRUE );
      SetCaptionTitle( 0, 0 );

#ifdef DEBUG_TASK
      TraceLine( "======================> [drvr] RestartBuildWindow Task: 0x%08x  Dlg.Wnd: %s.%s   vDialog: 0x%08x  hWnd: 0x%08x",
                 pZTask, *m_pzsDlgTag, *m_pzsWndTag, m_vDialog, m_pZFWnd->m_hWnd );
      ListWindowsAndControls( this, "RestartBuildWindow Create", 0 );
#endif
      if ( m_pZFWnd )
      {
         if ( m_bUseMapDlgUnits )
         {
            ((ZDrFrame *) m_pZFWnd)->m_nMinSizeX = mConvertMapDlgToPixelX( m_pWndDef->SZMIN_X );
            ((ZDrFrame *) m_pZFWnd)->m_nMinSizeY = mConvertMapDlgToPixelY( m_pWndDef->SZMIN_Y );
            ((ZDrFrame *) m_pZFWnd)->m_nMaxSizeX = mConvertMapDlgToPixelX( m_pWndDef->SZMAX_X );
            ((ZDrFrame *) m_pZFWnd)->m_nMaxSizeY = mConvertMapDlgToPixelY( m_pWndDef->SZMAX_Y );
         }
         else
         {
            ((ZDrFrame *) m_pZFWnd)->m_nMinSizeX = mConvertDlgUnitToPixelX( m_pWndDef->SZMIN_X );
            ((ZDrFrame *) m_pZFWnd)->m_nMinSizeY = mConvertDlgUnitToPixelY( m_pWndDef->SZMIN_Y );
            ((ZDrFrame *) m_pZFWnd)->m_nMaxSizeX = mConvertDlgUnitToPixelX( m_pWndDef->SZMAX_X );
            ((ZDrFrame *) m_pZFWnd)->m_nMaxSizeY = mConvertDlgUnitToPixelY( m_pWndDef->SZMAX_Y );
         }
      }
   }
#endif

   if ( (m_ulSubtaskFlags & zSUBTASK_SUBWND_MDI_FRAME) )
   {
      CMenu *pMenu = m_pZFWnd->GetMenu( );
      CreateZeidonMenu( m_pWndDef->DfltMenu );
      if ( pMenu )
      {
         ::DeleteMenu( (HMENU) *pMenu, 0, MF_BYPOSITION );
      }

//    m_pZFWnd->AssignMenu( MDI_MENU );
//    m_pZFWnd->Attr.AccelTable = MDI_MENU;
//    m_pZFWnd->SetMenuDescr( CMenuDescr( MDI_MENU ) );

      if ( (ulSubtaskState & zSUBTASK_STATE_REPLACED_BY_SELF) == 0 )
         CreateZeidonCtrls( m_vDialog, this, m_pZView, 0, 0, 0, FALSE );

      if ( m_pZMIXCtrl )
         m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnDisableCtrls, 0 );
   }
   else
   {
      if ( (ulSubtaskState & zSUBTASK_STATE_REPLACED_BY_SELF) == 0 )
      {
         if ( (m_ulSubtaskFlags & zSUBTASK_SUBWND_SPLITTER_PANE) == 0 )
            CreateZeidonMenu( m_pWndDef->DfltMenu );

         CreateZeidonCtrls( m_vDialog, this, m_pZView, 0, 0, 0, FALSE );
      }

#ifdef DEBUG_ALL
//    TraceLineS( "Begin Listing controls for window ======> ", *m_pzsWndTag );
//    m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnOrderedCtrls );
//    TraceLineS( "End Listing controls for window ========> ", *m_pzsWndTag );
#endif

      // Set a flag indicating that the receiver has requested keyboard
      // navigation (translation of keyboard input into control selections).
      // By default, the keyboard interface, which lets users use the tab and
      // arrow keys to move between the controls, is disabled for windows and
      // dialog boxes.
//x   if ( m_pZFWnd )
//x      m_pZFWnd->EnableKBHandler( ); // this turns off Alt key (menu selection
//x                                    // handling) ... if we do not enable
//x                                    // keyboard handling, we need to set
//x                                    // focus to the first control
//x
//?   m_pZFWnd->KeyboardHandling = false;

      // Run through the list of Child controls and disable as specified
      // in the common attributes in the PWD.
      if ( m_pZMIXCtrl )
      {
         m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnDisableCtrls, 0 );
      }
   }

   ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_POSTBUILD_PRECODE );
POSTBUILD_PRECODE_label:

   zBOOL bDoPlacement;

   // Moved placement stuff from here, but did not work ... dks  2006.01.04
   bDoPlacement = ((m_ulSubtaskFlags & zSUBTASK_SUBWND_SPLITTER_PANE) == 0 &&
                   m_pZFWnd && mIs_hWnd( m_pZFWnd->m_hWnd )) ? TRUE : FALSE;
   if ( bDoPlacement )
      DoPlacement( pZTask );

   FindFirstLastFocus( );  // Moved from after MapFromOI so that the
                           // application can set initial focus without
                           // being forced to use the ON_SETUP exit.
#if 0
   if ( zstrcmp( *m_pzsWndTag, "account" ) == 0 && m_pZMIXCtrl )
   {
      CString csSeek( "GridListAccount" );  // localize Tag for the seek
      ZMapAct *pzma = (ZMapAct *) m_pZMIXCtrl->SeekNode( &csSeek );
      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) )
      {
         zLONG lStyle = GetWindowLong( pzma->m_pCtrl->m_hWnd, GWL_STYLE );
         TraceLineX( "ZSubtask::Before Subtask PostBuild GridListAccount Style: ", lStyle );
      // #define WS_DISABLED         0x08000000L
         if ( lStyle & WS_DISABLED )
         {
            ::MessageBox( 0, "GridListAccount Disabled", "ZSubtask::Before Subtask PostBuild", MB_OK );
         }
      }
   }
#endif

   if ( m_lRelease > g_lRel && (m_ulWndOper & zWND_EVENT_POST_BUILD) &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_POST_BUILD, 0 ) > zCURSOR_UNCHANGED )
   {
      lRC = ProcessActionLoop( this, szlWndAct, 0, vAppSubtask, 0, TRUE, "PostBuild" );
      ulSubtaskState = ZSubtask::GetSubtaskState( this );

#ifdef zREMOTE_SERVER

      if ( pZSocketTask->m_lSocketState == -1 || (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) )
      {
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;
      }

#else

      if ( (pZTask->m_uAppState & zAPP_STATE_TERMINATED) || (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) )
      {
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;
      }

#endif

      if ( zHIUSHORT( lRC ) == 2 )
      {
         mDeleteInit( m_pzsResumeAction );
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;     // leave state at zSUBTASK_POSTBUILD_PRECODE
      }

      vAppSubtask = 0;     // turn off debugger (if it was on)
   }

   ZSubtask::SetSubtaskState( this, 0, zSUBTASK_STATE_POSTBUILD_POSTCODE );
POSTBUILD_POSTCODE_label:

   MapFromOI( zMAP_FIRST_TIME );  // do mapping for all controls

#if 0 //???
   if ( m_pCurrDfltBtn )
      m_pZView->SetDefaultId( m_pCurrDfltBtn->m_nIdNbr );
#endif

   ZSubtask::SetSubtaskState( this, zSUBTASK_STATE_REPLACED_BY_SELF | 0x000000FF, zSUBTASK_STATE_WELL_FORMED );

   zCPCHAR cpcEvent;
   zLONG   lEvent;

   if ( m_lRelease > g_lRel )
   {
      cpcEvent = "OnSetup";
      lEvent = zWND_EVENT_ON_SETUP;
   }
   else
   {
      cpcEvent = "PostBuild";
      lEvent = zWND_EVENT_POST_BUILD;
   }

   if ( (m_ulWndOper & lEvent) == (zULONG) lEvent &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, lEvent, 0 ) > zCURSOR_UNCHANGED )
   {
      lRC = ProcessActionLoop( this, szlWndAct, 0, vAppSubtask, 0, TRUE, cpcEvent );
      ulSubtaskState = ZSubtask::GetSubtaskState( this );

#ifdef zREMOTE_SERVER

      if ( pZSocketTask->m_lSocketState == -1 || (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) )
      {
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;
      }

#else

      if ( (pZTask->m_uAppState & zAPP_STATE_TERMINATED) || (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) )
      {
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;
      }

#endif

      if ( zHIUSHORT( lRC ) == 2 )
      {
         mDeleteInit( m_pzsResumeAction );
      // SysMutexUnlock( m_vDialog, "ZDw", 0 );
         return;     // leave state at zSUBTASK_POSTBUILD_PRECODE
      }

      vAppSubtask = 0;     // turn off debugger (if it was on)
   }

   if ( m_pzmaWithFocus && m_pzmaWithFocus->m_pCtrl && mIs_hWnd( m_pzmaWithFocus->m_pCtrl->m_hWnd ) )
   {
      ::SetFocus( m_pzmaWithFocus->m_pCtrl->m_hWnd );
   }

   if ( m_pZFWnd && mIs_hWnd( m_pZFWnd->m_hWnd ) )
   {
   // TraceLineS( "(stask) UpdateWindow for: ", *m_pzsWndTag );
   // m_pZFWnd->RecalcLayout( );
      if ( GetSplitterMainSubtask( ) == 0 )
         m_pZFWnd->UpdateWindow( );

      if ( m_pDIL )
         m_pZFWnd->ShowControlBar( m_pDIL, TRUE, FALSE );
   }

#ifdef DEBUG_LISTWND
   ListWindowsAndControls( this, "RestartBuildWindow End of Create Window", 0 );
#endif

// SysMutexUnlock( m_vDialog, "ZDw", 0 );
}

void
ZSubtask::DoPlacement( ZTask *pZTask )
{
// WINDOWPLACEMENT *pwp;
// pwp = (WINDOWPLACEMENT *) m_pchWindowPlacement;
// if ( m_pchWindowPlacement &&
//      pwp->length == sizeof( WINDOWPLACEMENT ) )
// {
//    m_pZFWnd->SetWindowPlacement( pwp );
//    m_pZFWnd->SetActiveWindow( );
// }

   WINDOWPLACEMENT wp;
   APPBARDATA abd;
   abd.cbSize = sizeof( abd );
   abd.hWnd = m_pZFWnd->m_hWnd;

   // Ignored members: uCallbackMessage, uEdge, rc, lParam.
   // abd.rc contains the rectangular location of the taskbar in
   // screen coordinates.
   if ( SHAppBarMessage( ABM_GETTASKBARPOS, &abd ) == FALSE )
   {
      abd.hWnd = ::GetDesktopWindow( );
      SHAppBarMessage( ABM_GETTASKBARPOS, &abd );
   }

   UINT uEdge = GetTaskbarEdge( abd.rc );

   if ( ReadWindowPlacement( m_vDialog, "ZDR", *m_pzsDlgTag, *m_pzsWndTag, &wp ) &&
        CheckWindowPos( &wp ) )
   {
      if ( m_pWndDef->Style == (WS_POPUP | WS_VISIBLE | WS_DLGFRAME) )
      {
         wp.rcNormalPosition.left = Attr.X;
         wp.rcNormalPosition.top = Attr.Y;
      }
      else
      {
         if ( wp.rcNormalPosition.top < 0 )
         {
            wp.rcNormalPosition.bottom += -wp.rcNormalPosition.top;
            wp.rcNormalPosition.top = 0;
         }

         if ( wp.rcNormalPosition.left < 0 )
         {
            wp.rcNormalPosition.right += -wp.rcNormalPosition.left;
            wp.rcNormalPosition.left = 0;
         }
      }

      if ( uEdge == ABE_TOP )
         wp.rcNormalPosition.top += (abd.rc.bottom - abd.rc.top);
      else
      if ( uEdge == ABE_LEFT )
         wp.rcNormalPosition.left += (abd.rc.right - abd.rc.left);

      if ( (m_pWndDef->Style & WS_THICKFRAME) == 0 )
      {
         wp.rcNormalPosition.right = wp.rcNormalPosition.left + Attr.W;
         wp.rcNormalPosition.bottom = wp.rcNormalPosition.top + Attr.H;
      }
      else
      if ( uEdge == ABE_TOP )
         wp.rcNormalPosition.bottom += (abd.rc.bottom - abd.rc.top);
      else
      if ( uEdge == ABE_LEFT )
         wp.rcNormalPosition.right += (abd.rc.right - abd.rc.left);

      m_pZFWnd->SetWindowPlacement( &wp );
//       TraceLineS( "Setting ACTIVE window ==============> ", *m_pzsWndTag );
      m_pZFWnd->SetActiveWindow( );
   }
   else
   {
   // if ( wp )
   //    TraceLineI( "Invalid window placement ", wp->length );

      if ( m_nInvisible < 0 )
         m_pZFWnd->ShowWindow( SW_HIDE );
      else
      {
         int iCmdShow;

         if ( pZTask->m_pZSubtaskFocus == this )
         {
            iCmdShow = SW_SHOW;
            pZTask->m_pZSubtaskFocus = 0;
         }
         else
            iCmdShow = SW_SHOWNA;

         if ( uEdge == ABE_TOP )
            m_pZFWnd->MoveWindow( Attr.X, Attr.Y + abd.rc.bottom, Attr.W, Attr.H, TRUE );
         else
         if ( uEdge == ABE_LEFT )
            m_pZFWnd->MoveWindow( Attr.X + abd.rc.right, Attr.Y, Attr.W, Attr.H, TRUE );
         else
         {
            if ( m_ulSubtaskFlags & zSUBTASK_SCROLLBARS )
               Attr.W++;  // force an OnSize event

            m_pZFWnd->MoveWindow( Attr.X, Attr.Y, Attr.W, Attr.H, TRUE );
         }

         m_pZFWnd->ShowWindow( iCmdShow );
      }
   }

   if ( Attr.W != (zSHORT) m_pWndDef->SZDLG_X || Attr.H != (zSHORT) m_pWndDef->SZDLG_Y )
   {
      // We are not building at the original design size, so inform all controls that a WM_SIZE has occurred.
      CRect rect;
      m_pZFWnd->GetClientRect( rect );
      CSize size( rect.right - rect.left, rect.bottom - rect.top );
      SendParentResize( 0, &size );
   }

   zCHAR szAppName[ zZEIDON_NAME_LTH + 1 ];
   GetApplDirectoryFromView( szAppName, m_vDialog, zAPPL_NAME, zsizeof( szAppName ) );
   CString csProfile( szAppName );
   csProfile += ".";
   csProfile += *m_pzsDlgTag;
   csProfile += ".";
   csProfile += *m_pzsWndTag;
   if ( ((ZDrFrame *) m_pZFWnd)->VerifyBarState( csProfile ) )
   {
      zFARPROC_CBAR lpfnDynRoutine;
      LPLIBRARY hLibrary = SysLoadLibraryWithErrFlag( m_vDialog, "zdctl", 0 );
      if ( hLibrary )
      {
         lpfnDynRoutine = (zFARPROC_CBAR) SysGetProc( hLibrary, "CBarLoadSaveState" );
         if ( lpfnDynRoutine )
         {
         // // You need to call EnableDocking before calling LoadBarState.
         // m_pZFWnd->EnableDocking( CBRS_ALIGN_ANY );
            (*lpfnDynRoutine)( m_pZFWnd, csProfile, FALSE );
#if 1
            // This is a hack to fix a problem in MFC that I know of no
            // other way to get around.  Do the calls to LoadBarState and
            // check to ensure things are OK prior to calling the "real"
            // LoadBarState below.
            zBOOL bError = FALSE;
            CDockState state;
            int i;

            state.LoadState( csProfile );
         // SetDockState( state );

            // This following code is a slightly modified (ASSERT free) version
            // of CFrameWnd::SetDockState in DOCKSTAT.CPP.

            // first pass through barinfo's sets the m_pBar member correctly
            // creating floating frames if necessary
            int iSize = state.m_arrBarInfo.GetSize();
            for (i = 0; i < state.m_arrBarInfo.GetSize(); i++)
            {
               CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
               if (pInfo == NULL)
               {
                  bError = TRUE;
                  break;
               }

               if ( pInfo->m_bFloating )
               {
                  // need to create floating frame to match
                  CMiniDockFrameWnd* pDockFrame = m_pZFWnd->CreateFloatingFrame( pInfo->m_bHorz ? CBRS_ALIGN_TOP : CBRS_ALIGN_LEFT );
                  if ( pDockFrame = NULL )
                  {
                     bError = TRUE;
                     break;
                  }

                  CRect rect( pInfo->m_pointPos, CSize( 10, 10 ) );
                  pDockFrame->CalcWindowRect( &rect );
                  pDockFrame->SetWindowPos( NULL, rect.left, rect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
                  CDockBar* pDockBar = (CDockBar*) pDockFrame->GetDlgItem( AFX_IDW_DOCKBAR_FLOAT );
                  if ( pDockBar == NULL )
                  {
                     bError = TRUE;
                     break;
                  }

               // ASSERT_KINDOF(CDockBar, pDockBar);
                  pInfo->m_pBar = pDockBar;
               }
               else // regular dock bar or toolbar
               {
                  pInfo->m_pBar = m_pZFWnd->GetControlBar(pInfo->m_nBarID);
                  if ( pInfo->m_pBar == NULL ) //toolbar id's probably changed
                  {
                     bError = TRUE;
                     break;
                  }
               }
               pInfo->m_pBar->m_nMRUWidth = pInfo->m_nMRUWidth;
            }

            // the second pass will actually dock all of the control bars and set everything correctly
            iSize = state.m_arrBarInfo.GetSize();
            for (i = 0; i < iSize && bError == FALSE; i++)
            {
               CControlBarInfo* pInfo = (CControlBarInfo*) state.m_arrBarInfo[i];
               if (pInfo)
               {
                  if ( pInfo->m_pBar)
                  {
                  // pInfo->m_pBar->SetBarInfo(pInfo, (ZDrFrame *) m_pZFWnd);
                     if (pInfo->m_bDocking)
                     {
                        if ( pInfo->m_pBar->m_pDockContext == NULL )
                        {
                           bError = TRUE;
                           break;
                        }
                     }
                  }
               }
               else
               {
                  bError = TRUE;
                  break;
               }
            }

            if ( bError == FALSE )
#endif
               m_pZFWnd->LoadBarState( csProfile );
         }
      }
   }
}

void
ZSubtask::SetCaptionTitle( zCPCHAR cpcCaption,
                           zCPCHAR cpcTitle,
                           zBOOL   bUpdateWindow )
{
   if ( cpcCaption )
   {
      mDeleteInit( m_pzsCaption );
      if ( cpcCaption[ 0 ] )
         m_pzsCaption = new CString( cpcCaption );
   }

   if ( cpcTitle )
   {
      mDeleteInit( m_pzsTitle );
      if ( cpcTitle[ 0 ] )
         m_pzsTitle = new CString( cpcTitle );
   }

   if ( bUpdateWindow )
   {
      CString cs;

      if ( m_pzsCaption )
      {
         cs = *m_pzsCaption;
         if ( m_pzsTitle )
         {
            cs += " - ";
            cs += *m_pzsTitle;
         }
      }
      else
      if ( m_pzsTitle )
         cs = *m_pzsTitle;
      else
         cs = "";

      if ( cs.GetLength( ) > zMAX_WINDOWCAPTION_LTH )
      {
         cs = cs.Mid( 0, zMAX_WINDOWCAPTION_LTH );
      }

      if ( m_pZFWnd )
         m_pZFWnd->SetWindowText( cs );  // or SetCaption???

#ifdef zREMOTE_SERVER
      if ( m_pZSocketTask )
      {
         SetRemoteWndAttribute( m_vDialog, "Caption", cs );
      }
#else
      if ( m_pZTask->m_pZSubtaskTop == this )
      {
         ::SetWindowText( m_pZTask->m_pZDrApp->m_hWndCommOE, cs );
      }
#endif
   }
}

// enable/disable the window ... overload the CWnd version
BOOL
ZSubtask::EnableWindow( BOOL bEnable )
{
   zBOOL bPrevState;

   // note that if nDisabled == 0 ==> control is enabled ... < 0 otw
   bPrevState = m_nDisabled == 0 ? TRUE : FALSE;
   if ( bEnable == TRUE && m_nDisabled < 0 )
      m_nDisabled++;
   else
   if ( bEnable == FALSE )
      m_nDisabled--;

#ifdef DEBUG_ALL
// if ( zstrcmp( "TZPNTRAD", *m_pzsWndTag ) == 0 )
   {
      if ( bEnable )
         TraceLine( "[drvr] ================> ENabling window %s.%s   nDisabled = %d", *m_pzsDlgTag, *m_pzsWndTag, m_nDisabled );
      else
         TraceLine( "[drvr] ================> DISabling window %s.%s  nDisabled = %d", *m_pzsDlgTag, *m_pzsWndTag, m_nDisabled );
   }
#endif

   if ( (bEnable == FALSE && m_nDisabled < 0) || (bEnable == TRUE && m_nDisabled == 0 && m_nInvisible == 0) )
   {
#ifdef zREMOTE_SERVER
      if ( m_pZSocketTask )
         SetRemoteWndAttribute( m_vDialog, "Enabled", bEnable ? "Y" : "N" );
#else
      if ( m_pZFWnd && mIs_hWnd( m_pZFWnd->m_hWnd ) )
         bPrevState = m_pZFWnd->EnableWindow( bEnable );
#endif
   }

   return( bPrevState );
}

void
ZSubtask::AutoGrayActions( )
{
   zKZWDLGXO_Act_DEF ActDef;
   zVIEW  vApp;
   zSHORT nRC;

   if ( (m_ulWndOper & zWND_EVENT_ACTION_AUTOGRAY) == 0 )
      return;

   ActDef.CheckByte = 0xFE;
   ActDef.lStructSize = sizeof( zKZWDLGXO_Act_DEF );

   nRC = SetCursorFirstEntity( m_vDialog, szlAct, 0 );
   while ( nRC >= zCURSOR_SET )
   {
      // Get the structure of attributes for this action.
      GetStructFromEntityAttrs( (zPCHAR) &ActDef, m_vDialog, szlAct );
      if ( ActDef.CheckByte != 0xFE )
         MessageBox( 0, "ActDef Structure Length Error", "GetStructFromEntityAttrs", MB_OK );

      while ( ActDef.AutoGray )  // purist's goto
      {
      // if ( zstrcmp( ActDef.VN, "TZERATLO" ) == 0 && zstrcmp( ActDef.EN, "ER_Attribute" ) == 0 )
      //    IssueError( m_vDialog, 0, 0, "Check object browser for TZERATLO ... ER_Attribute" );

      // TraceLineS( "ZSubtask::AutoGrayActions ViewName ", ActDef.VN );

         if ( ActDef.VN[ 0 ] )
            GetViewByName( &vApp, ActDef.VN, m_vDialog, zLEVEL_ANY );
         else
            vApp = 0;

         if ( (ActDef.AutoGray & zAUTOGRAY_ACTION_READONLY) )
         {
            if ( vApp == 0 || MiGetUpdateForView( vApp ) <= 0 )
            {
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_DISABLE );
               break; // it has been disabled, so no need for further checking
            }
            else
            {
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_ENABLE );
            // break;  we must check if any other flags would disable this action
            }
         }

         if ( (ActDef.AutoGray & zAUTOGRAY_ACTION_NULL) || (ActDef.AutoGray & zAUTOGRAY_ACTION_NOT_NULL) )
         {
            if ( vApp )
            {
               if ( CheckEntityInView( vApp, ActDef.EN ) == 0 )
               {
                  nRC = SetEntityCursor( vApp, ActDef.EN, 0, zPOS_FIRST | zTEST_CSR_RESULT, 0, 0, 0, 0, ActDef.Scope, 0 );
               }
               else
               {
                  nRC = zCALL_ERROR;
               }
            }
            else
               nRC = 0;

            if ( vApp && nRC >= 0 )
            {
               if ( ActDef.AutoGray & zAUTOGRAY_ACTION_NULL )
                  EnableAction( m_vDialog, ActDef.Tag, zAUTO_ENABLE );
               else
                  EnableAction( m_vDialog, ActDef.Tag, zAUTO_DISABLE );
            }
            else
            if ( nRC == zCALL_ERROR )
            {
               return;  // something bad has happened
            }
            else
            {
               if ( ActDef.AutoGray & zAUTOGRAY_ACTION_NULL )
                  EnableAction( m_vDialog, ActDef.Tag, zAUTO_DISABLE );
               else
                  EnableAction( m_vDialog, ActDef.Tag, zAUTO_ENABLE );
            }
         }
         else
         if ( ActDef.AutoGray & zAUTOGRAY_ACTION_NOT_SELECTED )
         {
            if ( vApp && GetSelectStateOfEntityForSet( vApp, ActDef.EN, 1 ) )
            {
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_ENABLE );
            }
            else
            {
            // TraceLineS( "ZSubtask::AutoGrayActions ", "ACTION_NOT_SELECTED" );
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_DISABLE );
            }
         }
         else
         if ( ActDef.AutoGray & zAUTOGRAY_ACTION_FIRST )
         {
            if ( vApp &&
                 SetEntityCursor( vApp, ActDef.EN, 0, zPOS_PREV | zTEST_CSR_RESULT, 0, 0, 0, 0, ActDef.Scope, 0 ) >= 0 )
            {
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_ENABLE );
            }
            else
            {
            // TraceLineS( "ZSubtask::AutoGrayActions ", "ACTION_FIRST" );
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_DISABLE );
            }
         }
         else
         if ( ActDef.AutoGray & zAUTOGRAY_ACTION_LAST )
         {
            if ( vApp &&
                 SetEntityCursor( vApp, ActDef.EN, 0, zPOS_NEXT | zTEST_CSR_RESULT, 0, 0, 0, 0, ActDef.Scope, 0 ) >= 0 )
            {
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_ENABLE );
            }
            else
            {
            // TraceLineS( "ZSubtask::AutoGrayActions ", "ACTION_LAST" );
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_DISABLE );
            }
         }
         else
         if ( ActDef.AutoGray & zAUTOGRAY_ACTION_BROWSE_ONLY )
         {
            if ( vApp && MiGetUpdateForViewEntityAttr( vApp, ActDef.EN, 0, 0 ) > 0 ) // ==> updateable
            {
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_ENABLE );
            }
            else
            {
            // TraceLineS( "ZSubtask::AutoGrayActions "BROWSE_ONLY", ActDef.Tag );
               EnableAction( m_vDialog, ActDef.Tag, zAUTO_DISABLE );
            }
         }

         break; // out of purist's goto
      }

      nRC = SetCursorNextEntity( m_vDialog, szlAct, 0 );
   }
}

void
ZSubtask::ResetFocus( ZMapAct *pzma )
{
// TraceLineS( "ZSubtask::ResetFocus ", *(pzma->m_pzsTag) );
   zLONG  lIdx;
   zLONG  k;

   if ( m_pZMIXCtrl == 0 || (lIdx = m_pZMIXCtrl->GetNodeIndex( pzma )) == 0 )
   {
      return;
   }

   k = lIdx + 1;
   while ( k != lIdx )
   {
      pzma = (ZMapAct *) m_pZMIXCtrl->GetAt( k );
      if ( pzma )
      {
         if ( (pzma->m_ulMapActFlags & zMAPACT_VISIBLE) && (pzma->m_ulMapActFlags & zMAPACT_ENABLED) &&
              (pzma->m_ulMapActFlags & zMAPACT_FOCUS_ENABLED) && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) )
         {
            pzma->ResetFocus( );
            return;
         }

         k++;
      }
      else
      {
         k = 1;
      }
   }
}

// Mapping from the object instance to the window controls.
zSHORT
ZSubtask::MapFromOI( WPARAM wFlag, zCPCHAR cpcCtrlTag )
{
   if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
      TraceLineS( "In MapFromOI: ", *m_pzsWndTag );

// CWaitRedraw wd;

   // Subtask MapFromOI in progress.
   zULONG ulSubtaskState = ZSubtask::GetSubtaskState( this );
   if ( (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) != 0 || m_pZMIXCtrl == 0 )
   {
      return( 0 );
   }

   if ( m_ulSubtaskFlags & zSUBTASK_MAPPING_FROM_OI )
   {
      TraceLineS( "(drvr) Recursive MapFromOI error", "" );
      return( 0 ); // this should never occur
   }

   if ( m_ulSubtaskFlags & zSUBTASK_CONTROL_DOMAINERR )
   {
      m_ulSubtaskFlags &= ~zSUBTASK_CONTROL_DOMAINERR;
      m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnClearCtrlErr, 0 );
   }

   if ( (m_ulWndOper & zWND_EVENT_ON_REFRESH) == zWND_EVENT_ON_REFRESH &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_ON_REFRESH, 0 ) > zCURSOR_UNCHANGED )
   {
      if ( ProcessActionLoop( this, szlWndAct, 0, 0, zACTION_DIALOG_CODE_ONLY, TRUE, "OnRefresh" ) > 0 )
      {
         return( 0 );
      }
   }

   m_ulSubtaskFlags |= zSUBTASK_MAPPING_FROM_OI;

#ifdef DEBUG_ALL
// TraceLineS( "Begin MapFromOI list ctrls for window ======> ", *m_pzsWndTag );
// m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnOrderedCtrls, 0 );
// TraceLineS( "End MapFromOI list ctrls for window ========> ", *m_pzsWndTag );
#endif

   zBOOL bLock = FALSE;

   if ( m_pZView && mIs_hWnd( m_pZView->m_hWnd ) )
   {
      m_pZView->Invalidate( );
      m_pZView->UpdateWindow( );
      bLock = m_pZView->LockWindowUpdate( );
   }

// TraceLineS( "ZSubtask::MapFromOI Locked: ", bLock ? "TRUE" : "FALSE" );

   // Run through the list of Child controls and request mapping.
   if ( m_pZMIXCtrl )
   {
      m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnMapCtrlsFromOI, 0, wFlag, (LPARAM) cpcCtrlTag );
   }

   m_ulSubtaskFlags &= ~zSUBTASK_MAPPING_FROM_OI;
#ifdef zREMOTE_SERVER
   m_ulSubtaskFlags |= zSUBTASK_MAPPED_SINCE_APPLYSTATE;
#endif

   // If action autogray is requested for this window, gray any actions for
   // which automatic graying is requested.
   if ( m_ulWndOper & zWND_EVENT_ACTION_AUTOGRAY )
      AutoGrayActions( );

   // Run through the list of Child controls and request mapping.
   if ( m_pZMIXCtrl )
   {
      m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnPostMapCtrlsFromOI, 0, wFlag, (LPARAM) cpcCtrlTag );
   }

   if ( bLock )
   {
      m_pZView->UnlockWindowUpdate( );
   // m_pZView->UpdateWindow( );
   // m_pZView->RedrawWindow( 0, 0, RDW_ALLCHILDREN | RDW_ERASENOW | /* RDW_UPDATENOW  |*/ RDW_INTERNALPAINT );
      m_pZView->Repaint( );
   }
   else
   {
      if ( m_pZView && mIs_hWnd( m_pZView->m_hWnd ) )
      {
         m_pZView->RedrawWindow( );
         m_pZView->UpdateWindow( );
      }
   }

   return( 0 );
}

// Mapping to the object instance from the window controls.
zSHORT
ZSubtask::MapToOI( )
{
   if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
      TraceLineS( "ZSubtask::MapToOI ", *m_pzsWndTag );

   zULONG ulSubtaskState = ZSubtask::GetSubtaskState( this );
   if ( ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE )
      return( 0 );

   // Run through the list of Child controls and request mapping.
   if ( m_pZMIXCtrl )
   {
      if ( m_ulSubtaskFlags & zSUBTASK_CONTROL_DOMAINERR )
      {
         m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnClearCtrlErr, 0 );
      }

      if ( (m_ulWndOper & zWND_EVENT_ON_MAPTOOI) == zWND_EVENT_ON_MAPTOOI &&
           SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_ON_MAPTOOI, 0 ) > zCURSOR_UNCHANGED )
      {
         if ( ProcessActionLoop( this, szlWndAct, 0, 0, zACTION_DIALOG_CODE_ONLY, TRUE, "OnMapToOI" ) > 0 )
         {
            return( 0 );
         }
      }

      fnPushMsgQ_State( m_vMsgQ, zMSGQ_MapToOI );
      m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnMapCtrlsToOI, 0 );
      fnPopMsgQ_State( m_vMsgQ );

      // pvNodeErr was initialized to 0 in VisitInorder.
      if ( m_pZMIXCtrl->m_pvNodeErr )
      {
         m_ulSubtaskFlags |= zSUBTASK_CONTROL_DOMAINERR;
         MessagePresent( m_vDialog, zMSGQ_AfterMapToOI, 0 );
         if ( ((ZMapAct *) (m_pZMIXCtrl->m_pvNodeErr))->m_pCtrl && mIs_hWnd( ((ZMapAct *) (m_pZMIXCtrl->m_pvNodeErr))->m_pCtrl->m_hWnd ) )
         {
            ((ZMapAct *) (m_pZMIXCtrl->m_pvNodeErr))->m_pCtrl->SetFocus( );
         }

         return( -1 );
      }
      else
         m_ulSubtaskFlags &= ~zSUBTASK_CONTROL_DOMAINERR;
   }

   return( 0 );
}

zBOOL
ZSubtask::InformDriverOfSetFocus( ZMapAct *pzmaReceivingFocus,
                                  zBOOL   bPushButton )
{
// TraceLineS( "InformDriverOfSetFocus = ", *(pzmaReceivingFocus->m_pzsTag) );

   if ( pzmaReceivingFocus->m_pzmaComposite )
   {
      if ( pzmaReceivingFocus->m_pzmaComposite->InformCompositeOfSetFocus( pzmaReceivingFocus ) == FALSE )
      {
         return( FALSE );  // this control did not want focus and has set focus to whichever control it wanted to receive focus
      }
   }

   if ( m_pZView )
   {
      if ( bPushButton )
      {
      // TraceLineS( "InformDriverOfSetFocus PushButton ", *(pzmaReceivingFocus->m_pzsTag) );
         m_pCurrDfltBtn = pzmaReceivingFocus;
      // m_pZView->SetDefID( pzmaReceivingFocus->m_nIdNbr );
         ::SendMessage( m_pZView->m_hWnd, DM_SETDEFID, pzmaReceivingFocus->m_nIdNbr, 0 );
#if 1
         if ( m_pCurrDfltBtn->m_pCtrl &&  mIs_hWnd( m_pCurrDfltBtn->m_pCtrl->m_hWnd ) )
         {
            UINT uStyle = ((CButton *) m_pCurrDfltBtn->m_pCtrl)->GetButtonStyle( );
            if ( (uStyle & BS_OWNERDRAW) != BS_OWNERDRAW )
            {
               uStyle = (uStyle & ~BS_PUSHBUTTON) | BS_DEFPUSHBUTTON;
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->SetButtonStyle( uStyle );
            // ((CButton *) m_pCurrDfltBtn->m_pCtrl)->SetState( TRUE );
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->Invalidate( );
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->UpdateWindow( );
            }
         }
#endif
      }
      else
      if ( m_pDfltBtn )
      {
      // TraceLineS( "InformDriverOfSetFocus DfltPushButton ", *(m_pDfltBtn->m_pzsTag) );
         m_pCurrDfltBtn = m_pDfltBtn;
      // m_pZView->SetDefID( m_pDfltBtn->m_nIdNbr );
         ::SendMessage( m_pZView->m_hWnd, DM_SETDEFID, m_pDfltBtn->m_nIdNbr, 0 );
#if 1
         if ( m_pCurrDfltBtn->m_pCtrl &&
              mIs_hWnd( m_pCurrDfltBtn->m_pCtrl->m_hWnd ) )
         {
            UINT uStyle = ((CButton *) m_pCurrDfltBtn->m_pCtrl)->GetButtonStyle( );
            if ( (uStyle & BS_OWNERDRAW) != BS_OWNERDRAW )
            {
               uStyle = (uStyle & ~BS_PUSHBUTTON) | BS_DEFPUSHBUTTON;
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->SetButtonStyle( uStyle );
            // ((CButton *) m_pCurrDfltBtn->m_pCtrl)->SetState( TRUE );
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->Invalidate( );
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->UpdateWindow( );
            }
         }
#endif
      }
      else
      {
#if 1
         if ( m_pCurrDfltBtn && m_pCurrDfltBtn->m_pCtrl && mIs_hWnd( m_pCurrDfltBtn->m_pCtrl->m_hWnd ) )
         {
         // TraceLineS( "InformDriverOfSetFocus CurrDfltPushButton (OFF): ", *(m_pCurrDfltBtn->m_pzsTag) );
            UINT uStyle = ((CButton *) m_pCurrDfltBtn->m_pCtrl)->GetButtonStyle( );
            if ( (uStyle & BS_OWNERDRAW) != BS_OWNERDRAW )
            {
               uStyle = (uStyle & ~BS_DEFPUSHBUTTON) | BS_PUSHBUTTON;
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->SetButtonStyle( uStyle );
            // ((CButton *) m_pCurrDfltBtn->m_pCtrl)->SetState( FALSE );
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->Invalidate( );
               ((CButton *) m_pCurrDfltBtn->m_pCtrl)->UpdateWindow( );
            }
         }
#endif
//       m_pZView->SetDefID( -1 );
         ::SendMessage( m_pZView->m_hWnd, DM_SETDEFID, -1, 0 );
         m_pCurrDfltBtn = 0;
      }
   }

   if ( m_pDIL && m_nAutoDIL )
   {
      zPCHAR pch;

      // This processing assumes that the first message in the list of DIL messages in the .XWD is "".
      if ( SetEntityCursor( m_vDialog, szlDIL, 0, zPOS_FIRST | zPOS_RELATIVE,
                            0, 0, 0, pzmaReceivingFocus->m_nDIL, 0, 0 ) >= zCURSOR_SET )
      {
         GetAddrForAttribute( &pch, m_vDialog, szlDIL, szlD_Msg );
      }
      else
         pch = "";

      SetStatusBarText( pch );    // message to default DIL item
   }

   m_pzmaWithFocus = pzmaReceivingFocus;

   if ( m_pzmaFirstFocus == 0 )
      m_pzmaFirstFocus = pzmaReceivingFocus;

   if ( m_pzmaLastFocus == 0 )
      m_pzmaLastFocus = pzmaReceivingFocus;

   if ( (m_ulWndOper & zWND_EVENT_CHILD_RECEIVE_FOCUS) &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_CHILD_RECEIVE_FOCUS, 0 ) > zCURSOR_UNCHANGED )
   {
      ProcessActionLoop( this, szlWndAct, 0, 0, zACTION_DIALOG_CODE_ONLY, TRUE, "ChildFocus" );
   }

   return( TRUE );
}

zBOOL
ZSubtask::InformDriverOfKillFocus( ZMapAct *pzmaLosingFocus )
{
// TraceLineS( "InformDriverOfKillFocus pzma = ", *(pzmaLosingFocus->m_pzsTag) );

   if ( pzmaLosingFocus->m_pzmaComposite )
   {
      if ( pzmaLosingFocus->m_pzmaComposite->InformCompositeOfKillFocus( pzmaLosingFocus ) == FALSE )
      {
         return( FALSE ); // this control wants to retain focus
      }
   }

   if ( (m_ulWndOper & zWND_EVENT_CHILD_LOSE_FOCUS) &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_CHILD_LOSE_FOCUS, 0 ) > zCURSOR_UNCHANGED )
   {
      ProcessActionLoop( this, szlWndAct, 0, 0, zACTION_DIALOG_CODE_ONLY, TRUE, "ChildLoseFocus" );
   }

   return( TRUE );
}

void
ZSubtask::InformDriverOfFlyBy( ZMapAct *pzma, zCPCHAR cpcMsg )
{
#if 0
   if ( pzma )
      TraceLine( "ZSubtask::InformDriverOfFlyBy Subtask: %s  Ctrl: %s", *m_pzsWndTag, *(pzma->m_pzsTag) );

   if ( pzma && ((pzma->m_ulMapActFlags & zMAPACT_VISIBLE) == 0 || (pzma->m_ulMapActFlags & zMAPACT_ENABLED) == 0) )
   {
      return;
   }
#endif

// if ( pzma == m_pzmaLastFlyBy )
//    return;

   m_pzmaLastFlyBy = pzma;

// if ( pzma == 0 )             by default do not return the message
//    pzma = m_pzmaWithFocus;   to the last control with focus

   if ( m_ulFlyByTickCnt && (SysGetTickCount( ) - m_ulFlyByTickCnt) < (zTICKS_PER_SECOND * 2) )
   {
      return;
   }

   m_ulFlyByTickCnt = 0;
   if ( m_pDIL && m_nAutoDIL )
   {
      if ( pzma )
      {
         if ( cpcMsg )
         {
            SetStatusBarText( cpcMsg, 0 );
         }
         else
         {
            zPCHAR pchMsg;

            // This processing assumes that the first message in the list of DIL messages in the .XWD is "".
            SetEntityCursor( m_vDialog, szlDIL, 0, zPOS_FIRST | zPOS_RELATIVE, 0, 0, 0, pzma->m_nDIL, 0, 0 );
            GetAddrForAttribute( &pchMsg, m_vDialog, szlDIL, szlD_Msg );
            SetStatusBarText( pchMsg );    // message to default DIL item
         }
      }
      else
      {
         SetStatusBarText( "", 0 );
      }
   }
}

ZMapAct *
ZSubtask::FindFirstLastFocus( zBOOL bSet )
{
   if ( m_pZMIXCtrl )
   {
      ZMapAct *pzmaWithFocus = m_pzmaWithFocus;
      m_pzmaFirstFocus = m_pzmaLastFocus = m_pzmaWithFocus = 0;
      m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnSetFirstLastFocus, 0 );
      if ( bSet == FALSE && pzmaWithFocus )
         m_pzmaWithFocus = pzmaWithFocus;
      else
      if ( m_pzmaWithFocus )
         m_pzmaWithFocus = m_pzmaWithFocus->GetRealFocus( );

      if ( m_pzmaWithFocus && m_pzmaWithFocus->m_pCtrl && mIs_hWnd( m_pzmaWithFocus->m_pCtrl->m_hWnd ) )
      {
         if ( bSet )
            m_pzmaWithFocus->m_pCtrl->SetFocus( );

         return( m_pzmaWithFocus );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// If there is no control that can receive focus within the specified
// composite, return 0, otherwise return the control that can receive focus.
//
// If the pzmaIn parameter passed in is zero, a GetFirst or GetLast
// effectively occurs (based on the value of bNext), otherwise, a GetNext
// or GetPrev occurs (based on the value of bNext).
//
// If pzmaCompositeIn is 0, attempt to determine the focus control at or
// above the level of pzmaIn which is not a descendent of pzmaIn.
//
/////////////////////////////////////////////////////////////////////////////
ZMapAct *
ZSubtask::GetFocusCtrlWithinComposite( ZMapAct *pzmaCompositeIn,
                                       ZMapAct *pzmaIn,
                                       zBOOL   bNext )
{
// TraceLineS( "ZSubtask::GetFocusCtrlWithinComposite ", "" );
   ZMapAct *pzmaComposite;
   ZSubtask *pZSubtask = this;  // localize to handle Splitters
   ZSubtask *pZSubtaskOrig = this;  // localize to handle Splitters
   ZMultiIdxSet *pZMIXCtrl = m_pZMIXCtrl;  // localize to handle Splitters
   zLONG   lIdxComposite;
   zLONG   lIdx;
   zLONG   lIdxOrig;
   zSHORT  nIncr = bNext ? 1 : -1;  // set the correct direction of search
   ZMapAct *pzma = pzmaIn;

   if ( pzma == 0 )
      pzma = pzmaCompositeIn;

   if ( pZMIXCtrl == 0 || (pzmaCompositeIn == 0 && pzma == 0) ||
        (pzmaCompositeIn && (lIdxComposite = pZMIXCtrl->GetNodeIndex( pzmaCompositeIn )) == 0) ||
        (pzma && (lIdx = pZMIXCtrl->GetNodeIndex( pzma )) == 0) )
   {
      return( 0 );
   }

   if ( pzmaCompositeIn == 0 )
      lIdxComposite = lIdx;

   zLONG k = lIdxOrig = lIdx;
   if ( bNext == FALSE && pzmaCompositeIn && pzmaIn == 0 )
   {
      // Find the last ctrl within the composite.
      zLONG lIdxSave = lIdx;

      while ( (pzma = (ZMapAct *) pZMIXCtrl->GetAt( k + 1 )) != 0 )
      {
         if ( pzma->m_pzmaComposite == pzmaCompositeIn )
            k++;
         else
            break;
      }

      if ( k > lIdx )
      {
         lIdx = k + 1;
         if ( lIdx > pZMIXCtrl->GetCount( ) )
            lIdx = 1;
      }
      else
         k--;
   }
   else
      k += nIncr;

   while ( k != lIdx )  // if we've gone thru the list, we gotta stop
   {
      pzma = (ZMapAct *) pZMIXCtrl->GetAt( k );
      if ( pzma )
      {
         pzmaComposite = pzma->m_pzmaComposite;

         if ( pzmaCompositeIn == 0 )
         {
            // Don't accept any control that is a descendent of pzmaIn.
            while ( pzmaComposite && pzmaComposite != pzmaCompositeIn )
            {
               if ( pzmaComposite == pzmaIn )
                  break;

               pzmaComposite = pzmaComposite->m_pzmaComposite;
            }

            if ( pzmaComposite )
            {
               // This control had an ancestor of pzmaIn ... skip it.
               k += nIncr;
               continue;
            }

            pzmaComposite = pzma->m_pzmaComposite;
         }

         while ( pzmaComposite && pzmaComposite != pzmaCompositeIn )
            pzmaComposite = pzmaComposite->m_pzmaComposite;

#if 0
         if ( zstrcmp( "LBPurchaseOrder", *(pzma->m_pzsTag) ) == 0 && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) )
         {
            TraceLineS( "GetFocusCtrlWithinComposite testing pzma = ", *(pzma->m_pzsTag) );
         }
#endif

      // if ( zstrcmp( *(pzma->m_pzsTag), "DKS" ) == 0 )
      //    TraceLineS( "", "" );

         // This will skip ctrls that have been auto-disabled unless they are also marked as ReadOnly!
         if ( (pzmaComposite == 0 || pzmaComposite == pzmaCompositeIn) &&
              (pzma->m_ulMapActFlags & zMAPACT_VISIBLE) &&
              ((pzma->m_ulMapActFlags & zMAPACT_ENABLED) ||
               (pzma->m_ulMapActFlags & zMAPACT_DISABLE_READONLY)) &&
              ((pzma->m_ulMapActFlags & zMAPACT_FOCUS_ENABLED) &&
               (pzma->m_ulMapActFlags & zMAPACT_AUTO_NOFOCUS) == 0) &&
              (pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd )) &&
              ((pzma->m_ulMapActFlags & zMAPACT_ASKPARENT_FOCUS) == 0 ||
               (pzma->m_pzmaComposite->IsFocusOKForChild( pzma ) == TRUE)) )
         {
         // TraceLineS( "GetFocusCtrlWithinComposite pzma = ", *(pzma->m_pzsTag) );
            return( pzma );
         }

         k += nIncr;
      }
      else
      {
         if ( bNext )
         {
            if ( k >= pZMIXCtrl->GetCount( ) )
            {
               // Do something special for splitters.
               if ( (pZSubtask->m_ulSubtaskFlags & zSUBTASK_SUBWND_SPLITTER_PANE) && (pZSubtask->m_pZView && pZSubtask->m_pZView->m_pNextView) )
               {
                  pZSubtask = pZSubtask->m_pZView->m_pNextView->m_pZSubtask;
                  pZMIXCtrl = pZSubtask->m_pZMIXCtrl;
                  if ( pZSubtask == pZSubtaskOrig )
                     lIdx = lIdxOrig;
                  else
                     lIdx = 0;
               }

               k = 1;
            }
            else
            {
               k++;
            }
         }
         else
         {
            if ( k > 1 && k <= pZMIXCtrl->GetCount( ) )
            {
               k--;
            }
            else
            {
               // Do something special for splitters.
               if ( (pZSubtask->m_ulSubtaskFlags & zSUBTASK_SUBWND_SPLITTER_PANE) && (pZSubtask->m_pZView && pZSubtask->m_pZView->m_pPrevView) )
               {
                  pZSubtask = pZSubtask->m_pZView->m_pPrevView->m_pZSubtask;
                  pZMIXCtrl = pZSubtask->m_pZMIXCtrl;
                  if ( pZSubtask == pZSubtaskOrig )
                     lIdx = lIdxOrig;
                  else
                     lIdx = 0;
               }

               k = pZMIXCtrl->GetCount( );
            }
         }
      }
   }

   return( 0 );
}

void
ZSubtask::RecalcLayout( HWND hWnd )
{
   if ( m_pZTask->m_bLocked && m_pZTask->m_pZFWndHidden )
      m_pZTask->m_pZFWndHidden->UnlockWindowUpdate( );

   m_pZTask->m_pZFWndHidden = 0;
   m_pZTask->m_bLocked = FALSE;

   ZSubtask *pZSubtaskMain = GetSplitterMainSubtask( );
   if ( pZSubtaskMain && pZSubtaskMain->m_pZFWnd &&
        mIs_hWnd( pZSubtaskMain->m_pZFWnd->m_hWnd ) )
   {
      pZSubtaskMain->m_pZFWnd->RecalcLayout( );

      if ( pZSubtaskMain->m_pZView && pZSubtaskMain->m_pZView->m_pParentSplitterWnd &&
           mIs_hWnd( pZSubtaskMain->m_pZView->m_pParentSplitterWnd->m_hWnd ) )
      {
         pZSubtaskMain->m_pZView->m_pParentSplitterWnd->RecalcLayout( );
         ZDrView *pZView = pZSubtaskMain->m_pZView->m_pNextView;

         while ( pZView && pZView->m_pZSubtask && pZView->m_pZSubtask != pZSubtaskMain )
         {
            if ( pZView->m_pParentSplitterWnd )
               pZView->m_pParentSplitterWnd->RecalcLayout( );

            pZView = pZView->m_pNextView;
         }

         pZSubtaskMain->m_pZView->m_pParentSplitterWnd->ShowWindow( SW_SHOW );
      }

      if ( pZSubtaskMain->m_pZView && mIs_hWnd( pZSubtaskMain->m_pZView->m_hWnd ) )
      {
      // pZSubtaskMain->m_pZFWnd->ShowWindow( SW_SHOW );
         pZSubtaskMain->m_pZView->ShowWindow( SW_SHOW );
      }

      //xpZSubtaskMain->m_pZFWnd->SetWindowPos( 0, 0, 0, 0, 0,
      //x                                       SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME | SWP_FRAMECHANGED );
      //xpZSubtaskMain->m_pZFWnd->ModifyStyleEx( 0, 0, SWP_FRAMECHANGED );
   }

   if ( mIs_hWnd( hWnd ) )
      ::ShowWindow( hWnd, SW_SHOW );
}

void
ZSubtask::SendParentResize( ZMapAct *pzma, CSize *pSize )
{
   if ( m_pZMIXCtrl )
   {
      m_pZMIXCtrl->VisitInorder( (fnVISIT_INORDER) fnSendCtrlsParentResize, 0, (WPARAM) pzma, (LPARAM) pSize );
   }
}

zLONG
ZSubtask::SendCtrlSelectAll( )
{
   if ( m_pzmaWithFocus )
   {
   // TraceLineS( "ZSubtask::SendCtrlSelectAll for Ctrl: ", *(m_pzmaWithFocus->m_pzsTag) );
      return( m_pzmaWithFocus->SelectAll( ) );
   }
   else
   {
   // TraceLineS( "ZSubtask::SendCtrlSelectAll ... no Control with Focus", "" );
   }

   return( -2 );
}

void
ZSubtask::SaveBarState( )
{
   if ( ZSubtask::GetSubtaskState( this ) & zSUBTASK_STATE_WELL_FORMED )
   {
      zCHAR szAppName[ zZEIDON_NAME_LTH + 1 ];
      GetApplDirectoryFromView( szAppName, m_vDialog, zAPPL_NAME, zsizeof( szAppName ) );
      CString csProfile( szAppName );
      csProfile += ".";
      csProfile += *m_pzsDlgTag;
      csProfile += ".";
      csProfile += *m_pzsWndTag;

      zFARPROC_CBAR lpfnDynRoutine;
      LPLIBRARY hLibrary = SysLoadLibraryWithErrFlag( m_vDialog, "zdctl", 0 );

      if ( hLibrary )
      {
         lpfnDynRoutine = (zFARPROC_CBAR) SysGetProc( hLibrary, "CBarLoadSaveState" );
         if ( lpfnDynRoutine )
         {
            (*lpfnDynRoutine)( m_pZFWnd, csProfile, TRUE );
            m_pZFWnd->SaveBarState( csProfile );
         }
      }
   }
}

ZMapAct *
ZSubtask::FindCtrlWithQuickKey( ZMapAct *pzmaComposite,
                                zCHAR   chKey )
{
   if ( m_pZMIXCtrl )
   {
      ZMapAct *pzma;
      zSHORT  k;
      for ( k = 1; k <= m_pZMIXCtrl->GetCount( ); k++ )
      {
         pzma = (ZMapAct *) m_pZMIXCtrl->GetAt( k );
         if ( chKey == pzma->m_chQuickKey )
         {
//          if ( (pzma->m_ulMapActFlags & zMAPACT_FOCUS_ENABLED) == 0 )
//             pzma = (ZMapAct *) m_pZMIXCtrl->GetAt( k + 1 );

            if ( pzma )
            {
               // Make sure we are somewhere within the specified composite.
               if ( pzmaComposite )
               {
                  ZMapAct *pzmaParent = pzma->m_pzmaComposite;
                  while ( pzmaParent && pzmaParent != pzmaComposite )
                  {
                     pzmaParent = pzmaParent->m_pzmaComposite;
                  }

                  if ( pzmaParent == 0 )
                     pzma = 0;
               }
            }
            else
               pzma = 0;

            return( pzma );
         }
      }
   }

   return( 0 );
}

zSHORT
ZSubtask::SetStatusBarText( zCPCHAR cpcMessage, zSHORT nItem )
{
   ZSubtask *pZSubtask = this;
   if ( m_ulSubtaskFlags & zSUBTASK_SUBWND_SPLITTER_PANE )
   {
      pZSubtask = GetSplitterMainSubtask( );
      if ( pZSubtask == 0 )
         pZSubtask = this;
   }

   if ( pZSubtask->m_pZSubtaskGlobal )
      pZSubtask = pZSubtask->m_pZSubtaskGlobal;

// TraceLine( "ZSubtask::SetStatusBarText: %s  for Item: %d", cpcMessage, nItem );
   if ( pZSubtask->m_pDIL && mIs_hWnd( pZSubtask->m_pDIL->m_hWnd ) )
   {
      if ( nItem == 0 )
      {
         if ( pZSubtask->m_nAutoDIL )
            nItem = pZSubtask->m_nAutoDIL;
         else
            return( -1 );
      }

      if ( nItem <= pZSubtask->m_nDIL_Items )
      {
         SysWait( 1 );

      // TraceLine( "ZSubtask::SettingStatusBarText: %s  for Item: %d", cpcMessage, nItem );
         zBOOL bRC = pZSubtask->m_pDIL->SetPaneText( nItem - 1, cpcMessage, TRUE );
      // TraceLine( "ZSubtask::SetStatusBarText Item: %d   RC: %s   Msg: %s", nItem, bRC ? "Yes" : "No", cpcMessage );
         pZSubtask->m_pDIL->UpdateWindow( );
      }
   }

   return( 0 );
}

zBOOL
ZSubtask::PostClose( WPARAM wParam )
{
   ZSubtask *pZSubtask = GetSplitterMainSubtask( );
   ZSubtask *pZSubtaskNext;
   ZDrView  *pZView;

   if ( m_pZTask && (m_pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      TraceLine( "ZSubtask::PostClose: [0x%08x] %s.%s  IdNbr: %d", this, *m_pzsDlgTag, *m_pzsWndTag, m_ulSubtaskIdNbr );
   }

   // A call to close all split windows by the application causes windows to
   // be closed in a "random" order.  When closing the entire SplitterWindow
   // (frame and all detail windows), the frame needs to be closed last.
   // The driver is now doing that, so the application no longer has to close
   // each frame individually (by calling CloseFrame for each frame).  Calls
   // to CloseFrame to close a detail window (frame) should still be called
   // as necessary.

   if ( wParam && pZSubtask && (pZSubtask->m_ulSubtaskFlags & zSUBTASK_SPLITTER_MAIN_SUBTASK) )
   {
   // int k = 0;
   // wParam /= k;
      pZView = pZSubtask->m_pZView->m_pNextView;
      pZView->m_pParentSplitterWnd = 0;
      pZSubtask = pZView->m_pZSubtask;
      pZSubtask->m_ulSubtaskFlags &= ~zSUBTASK_SUBWND_SPLITTER_PANE;
      pZView = pZSubtask->m_pZView->m_pNextView;
      pZSubtask->m_pZView->m_pNextView = 0;
      pZSubtaskNext = pZView->m_pZSubtask;
   }
   else
   {
      pZSubtask = this;
      if ( pZSubtask->m_pZView )
        pZSubtask->m_pZView->m_pNextView = 0;  // this should already be true

      pZSubtaskNext = 0;
   }

   while ( pZSubtask )
   {
      ZSubtask::SetSubtaskState( pZSubtask, 0, zSUBTASK_STATE_MARK_FOR_DELETE );
      if ( ((pZSubtask->m_ulSubtaskFlags & zSUBTASK_SPLITTER_MAIN_SUBTASK) ||
            (pZSubtask->m_ulSubtaskFlags & zSUBTASK_SUBWND_CONVERSATIONAL)) &&
           pZSubtask->m_pZFWnd && pZSubtask->m_pZFWnd->m_hWnd )
      {
      //xchar szWndTag[ zTAG_LTH ];

      // TraceLineI( "============ hWnd = ", (zLONG) pZSubtask->m_pZFWnd->m_hWnd );

      //xstrcpy_s( szWndTag, zsizeof( szWndTag ), *m_pzsWndTag );
      //xszWndTag[ 0 ] = '.';
      //xdelete( m_pzsWndTag );
      //xm_pzsWndTag = new CString( szWndTag );

         ZSubtask::SetSubtaskState( pZSubtask, 0, zSUBTASK_STATE_DELETE );
         if ( mIs_hWnd( pZSubtask->m_pZFWnd->m_hWnd ) )
         {
         // pZSubtask->m_pZFWnd->ShowWindow( SW_HIDE );
         //?pZSubtask->m_pZFWnd->UpdateWindow( );
            return( pZSubtask->m_pZFWnd->PostMessage( g_uMsgPostedClose, 0, (zLONG) pZSubtask ) );
         }
      }
      else
      {
         zULONG ulSubtaskState = ZSubtask::GetSubtaskState( pZSubtask );
         if ( ulSubtaskState & zSUBTASK_STATE_IN_CONSTRUCTION )
         {
            ZSubtask::SetSubtaskState( pZSubtask, 0, zSUBTASK_STATE_DELETE );
         }
         else
         {
            pZSubtask->m_pZTask->DeleteSubtask( pZSubtask );
         }
      }

      if ( wParam == 0 )
         break;

      pZSubtask = pZSubtaskNext;
      if ( pZSubtask )
      {
         pZSubtask->m_pZView->m_pParentSplitterWnd = 0;
         pZSubtask->m_ulSubtaskFlags &= ~zSUBTASK_SUBWND_SPLITTER_PANE;
         pZView = pZSubtask->m_pZView->m_pNextView;
         pZSubtaskNext = pZView->m_pZSubtask;
         pZSubtask->m_pZView->m_pNextView = 0;
      }
   }

   return( TRUE );
}

ZMapAct *
ZSubtask::GetMapActFromHWnd( HWND hWndCtrl )
{
   if ( m_pZMIXCtrl )
   {
      ZMapAct *pzma;
      zSHORT k = 1;
      while ( (pzma = (ZMapAct *) m_pZMIXCtrl->GetAt( k++ )) != 0 )
      {
         if ( pzma->m_pCtrl && pzma->m_pCtrl->m_hWnd == hWndCtrl )
            return( pzma );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: EnableParentWindows
//
// PURPOSE: This routine enables or disables parent windows of a window,
//          including children of the parents (excluding the current
//          window of course).
//
//          If bEnable == TRUE, the parent windows are enabled, otherwise,
//          they are disabled.
//
/////////////////////////////////////////////////////////////////////////////
void
ZSubtask::EnableParentWindows( zBOOL bEnable )
{
#if 1
   // TraceLineS( "ZSubtask::EnableParentWindows here we are!!!", "" );
      ZSubtask *pZSubtask;

   // while ( pZParent->m_pZParent )
   //    pZParent = pZParent->m_pZParent;

      zVIEW vSubtask = GetNextSubtaskWithinParent( m_vDialog, 0, 0 );
      while ( vSubtask )
      {
         GetWindowAndCtrl( &pZSubtask, 0, vSubtask, 0 );
         if ( pZSubtask && pZSubtask != this )
         {
         // TraceLine( "ZSubtask::EnableParentWindows %s Subtask [%ld.%s.%s]",
         //            bEnable ? "Enabling" : "Disabling", pZSubtask->m_ulSubtaskIdNbr,
         //            *(pZSubtask->m_pzsDlgTag), *(pZSubtask->m_pzsWndTag) );
            pZSubtask->EnableWindow( bEnable );
         }

         vSubtask = GetNextSubtaskWithinParent( m_vDialog, vSubtask, 0 );
      }

#else

   if ( m_pZParent )
   {
//    zULONG ulSubtaskState = ZSubtask::GetSubtaskState( this );
//    if ( (ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) )
      {
         m_pZParent->EnableParentWindows( bEnable );
         m_pZParent->EnableWindow( bEnable );
      }
   }

   // Run through the list of Child windows to find any that have this
   // window's parent as its parent ... enable/disable them if they exist.
   zLONG lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
   while ( lItemCnt )
   {
      if ( g_pSubtaskList[ lItemCnt ].pZSubtask && g_pSubtaskList[ lItemCnt ].lTID == m_lTID &&
           (g_pSubtaskList[ lItemCnt ].ulSubtaskState & zSUBTASK_STATE_MARK_FOR_DELETE) == 0 &&
           g_pSubtaskList[ lItemCnt ].pZSubtask != this &&
           g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZParent == m_pZParent )
      {
#ifdef zREMOTE_SERVER
         // No "if" in Zeidon web, because m_pZFWnd  can be 0.
         g_pSubtaskList[ lItemCnt ].pZSubtask->EnableWindow( bEnable );
#else
         if ( g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZFWnd &&
              mIs_hWnd( g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZFWnd->m_hWnd ) )
         {
            g_pSubtaskList[ lItemCnt ].pZSubtask->EnableWindow( bEnable );
         }
         else
         {
            TraceLineI( "ZSubtask::EnableParentWindows invalid window at: ", lItemCnt );
            ASSERT( FALSE );
         }
#endif
      }

      lItemCnt--;
   }

#endif

}

#if 0
class ZDR_CLASS ZSingleDocTemplate : public CSingleDocTemplate
{
public:
   ZSingleDocTemplate( UINT uID,
                                        CRuntimeClass *p1,
                                        CRuntimeClass *p2,
                                        CRuntimeClass *p3 );
   ZSingleDocTemplate( );
   virtual ~ZSingleDocTemplate( );

}; // class ZSingleDocTemplate

ZSingleDocTemplate::ZSingleDocTemplate( UINT uID,
                                        CRuntimeClass *p1,
                                        CRuntimeClass *p2,
                                        CRuntimeClass *p3 ) :
                    CSingleDocTemplate( uID, p1, p2, p3 )
{
}

ZSingleDocTemplate::~ZSingleDocTemplate( )
{
}
#endif

void
ZSubtask::CreateZ( )
{
   if ( (m_pZTask->m_uAppState & zAPP_STATE_INITIALIZED) == 0 )
   {
      m_pZTask->m_uAppState |= zAPP_STATE_INITIALIZED;
      m_pZTask->m_pZDrApp->m_pZSubtaskCurr = this;  // so we can connect
      CSingleDocTemplate *pDocTemplate =
         new CSingleDocTemplate( IDR_MAINFRAME, RUNTIME_CLASS( ZDrDoc ),
                                 RUNTIME_CLASS( ZDrFrame ), // main SDI frame window
                                 RUNTIME_CLASS( ZDrView ) );
      pDocTemplate->SetContainerInfo( IDR_CNTR_INPLACE );
      m_pZTask->m_pZDrApp->AddDocTemplate( pDocTemplate );
      m_pZTask->m_pZDrApp->m_nCmdShow = SW_HIDE;

      // Dispatch commands specified on the command line.
      m_pZTask->m_pCmdInfo->m_nShellCommand = CCommandLineInfo::FileNew;
      if ( m_pZTask->m_pZDrApp->ProcessShellCommand( *(m_pZTask->m_pCmdInfo) ) == 0 )
         m_pZTask->m_uAppState |= zAPP_STATE_TERMINATED;
      else
         m_pZFWnd = (ZDrFrame *) AfxGetMainWnd( );

      m_pZTask->m_pZDrApp->m_pZSubtaskCurr = 0;

      if ( mIs_hWnd( m_pZFWnd->m_hWnd ) == FALSE )
         m_pZTask->m_uAppState |= zAPP_STATE_TERMINATED;
      else
         ::SetWindowLong( m_pZTask->m_pZDrApp->m_hWndCommOE, GWL_USERDATA,
                          (zLONG) m_pZTask->m_pZDrApp->m_pMainWnd->m_hWnd );
   }
   else
   if ( m_ulSubtaskFlags & zSUBTASK_SUBWND_MDI_FRAME )
   {
      m_pZFWnd = new ZDrFrame( this );
      if ( m_pZFWnd->LoadFrame( IDR_MAINFRAME ) == 0 || m_pZFWnd->m_hWnd == 0 )
      {
         m_pZTask->m_uAppState |= zAPP_STATE_TERMINATED;
      }
   }
   else
   {
      m_pZFWnd = new ZDrFrame( this );
      if ( m_pZFWnd->LoadFrame( IDR_MAINFRAME ) == 0 || m_pZFWnd->m_hWnd == 0 )
      {
         m_pZTask->m_uAppState |= zAPP_STATE_TERMINATED;
      }
   }

// TraceLine( "ZSubtask::CreateZ %s.%s ************* MainWnd: %d   hWnd: %d",
//            *m_pzsDlgTag, *m_pzsWndTag,
//            m_pZTask->m_pZDrApp->m_pMainWnd,
//            m_pZTask->m_pZDrApp->m_pMainWnd->m_hWnd );

   // We are saving the default menu so that it can be restored at
   // the appropriate point (on the Frame window's destroy method).
   // This permits us to replace the default menu with our own
   // menu (in CreateZeidonMenu), so that when merging menus, MFC
   // chooses the right one to merge with (ours).
   m_hMenuDefault = m_pZFWnd->m_hMenuDefault;
   if ( (m_pZTask->m_uAppState & zAPP_STATE_TERMINATED) == 0 && m_pZTask->m_pZDrApp->m_pMainWnd == 0 )
   {
      m_pZTask->m_pZDrApp->m_pMainWnd = m_pZFWnd;
      ::SetWindowLong( m_pZTask->m_pZDrApp->m_hWndCommOE, GWL_USERDATA,
                       (zLONG) m_pZTask->m_pZDrApp->m_pMainWnd->m_hWnd );
   }
}

zLONG
ZSubtask::HandleEvent( zLONG lEvent )
{
#ifdef zREMOTE_SERVER
   if ( (m_ulWndOper & lEvent) &&
        (lEvent != zWND_EVENT_CLOSE ||
         zstrcmp( m_pZSocketTask->m_szActTag, "ESC" )) &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, lEvent, 0 ) > zCURSOR_UNCHANGED )
#else
   if ( (m_ulWndOper & lEvent) &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, lEvent, 0 ) > zCURSOR_UNCHANGED )
#endif
   {
      if ( ProcessActionLoop( this, szlWndAct, 0, 0, 0, TRUE, "SysEvent" ) > 0 || lEvent == zWND_EVENT_CLOSE )
      {
         // Handled by application ... otw process default.
         return( zACTIVEX_EVENT_COMPLETED );
      }
   }
   else
   if ( lEvent == zWND_EVENT_CLOSE )   // NO close action specified
   {
      if ( m_pAccels )
      {
         LPACCEL_TABLE lpAT = (LPACCEL_TABLE) m_pAccels;
#ifdef zREMOTE_SERVER
         zBOOL bESC;
         if ( zstrcmp( m_pZSocketTask->m_szActTag, "ESC" ) == 0 )
            bESC = TRUE;
         else
            bESC = FALSE;

         while ( lpAT->nID != -1 )
         {
            if ( (m_pZParent == 0 && bESC == FALSE && // If there is no
                  lpAT->ac.uVK == VK_F4 &&            // parent, Close
                  lpAT->ac.fAlt == 1 &&               // is treated as
                  lpAT->ac.fCtrl == 0 &&              // an OK.
                  lpAT->ac.fShift == 0) ||
                 ((m_pZParent || bESC) &&                       // If there is a
                  lpAT->ac.uVK == VK_ESCAPE &&        // parent, Close
                  lpAT->ac.fAlt == 0 &&               // is treated as
                  lpAT->ac.fCtrl == 0 &&              // a Cancel.
                  lpAT->ac.fShift == 0) )
#else
         while ( lpAT->nID != -1 )
         {
            if ( (m_pZParent == 0 &&                  // If there is no
                  lpAT->ac.uVK == VK_F4 &&            // parent, Close
                  lpAT->ac.fAlt == 1 &&               // is treated as
                  lpAT->ac.fCtrl == 0 &&              // an OK.
                  lpAT->ac.fShift == 0) ||
                 (m_pZParent &&                       // If there is a
                  lpAT->ac.uVK == VK_ESCAPE &&        // parent, Close
                  lpAT->ac.fAlt == 0 &&               // is treated as
                  lpAT->ac.fCtrl == 0 &&              // a Cancel.
                  lpAT->ac.fShift == 0) )
#endif
            {
#ifdef zREMOTE_SERVER
               if ( lpAT->chType == zACCEL_ACTION )
               {
               // m_pZFWnd->PostMessage( zZEIDON_PROCESS_ACTION, 0, lpAT->nID );
                  if ( SetEntityCursor( m_vDialog, szlAct, 0, zPOS_FIRST | zPOS_RELATIVE, 0, 0, 0, lpAT->nID, 0, 0 ) > zCURSOR_UNCHANGED )
                  {
                     zPCHAR pch;

                     GetAddrForAttribute( &pch, m_vDialog, szlAct, szlTag );
                     ProcessActionLoop( this, pch, 0, 0, 0, FALSE, szlHotkey );
                  }
               }
               else
               if ( lpAT->chType == zACCEL_HOTKEY )
               {
               // m_pZFWnd->PostMessage( zZEIDON_PROCESS_HOTKEY, 0, lpAT->nID );
                  zFARPROC_DRIVER lpfnDynRoutine;
                  LPLIBRARY hHotkeyLibrary = 0;
                  zCHAR  szDLL_Name[ 9 ];
                  zCHAR  szOperName[ zTAG_LTH ];
                  zVIEW  vHotkey = m_pZTask->m_vHK;

                  // Get access to hotkey object instance ... it must exist.
                  SetEntityCursor( vHotkey, szlHotkey, 0, zPOS_FIRST | zPOS_RELATIVE, 0, 0, 0, lpAT->nID, 0, 0 );
                  GetStringFromAttribute( szDLL_Name, zsizeof( szDLL_Name ), vHotkey, szlHotkey, szlDLL );
                  GetStringFromAttribute( szOperName, zsizeof( szOperName ), vHotkey, szlHotkey, szlCOP );

                  lpfnDynRoutine = (zFARPROC_DRIVER) GetOperationDynamicCallAddress( m_vDialog, (LPLPLIBRARY) &hHotkeyLibrary,
                                                                                     szDLL_Name, szOperName, "(drvr hotkey)" );
                  if ( lpfnDynRoutine )
                  {
                     CWaitCursor wait;
                     (*lpfnDynRoutine)( m_vDialog );
                  }
               }
#else
               if ( lpAT->chType == zACCEL_ACTION )
                  m_pZFWnd->PostMessage( zZEIDON_PROCESS_ACTION, 0, lpAT->nID );
               else
               if ( lpAT->chType == zACCEL_HOTKEY )
                  m_pZFWnd->PostMessage( zZEIDON_PROCESS_HOTKEY, 0, lpAT->nID );
#endif
               // Handled by application ... otw process default.
               return( zACTIVEX_EVENT_COMPLETED );
            }

            lpAT++;
         }
      }

      if ( OperatorPrompt( m_vDialog, "No close action specified", "Permit close?",
                          TRUE, zBUTTONS_YESNO, zRESPONSE_NO, zICON_QUESTION ) == zRESPONSE_YES )
      {
         PostClose( 0 );
      }

      // Handled by application ... otw process default.
      return( zACTIVEX_EVENT_COMPLETED );
   }

   if ( lEvent == zWND_EVENT_MINIMIZE && (m_ulSubtaskFlags & zSUBTASK_CREATED_MODAL) )
   {
      ZSubtask *pZSubtaskParent = m_pZParent;
      while ( pZSubtaskParent )
      {
         if ( pZSubtaskParent->m_pZFWnd )
         {
            pZSubtaskParent->m_pZFWnd->ShowWindow( SW_MINIMIZE );
            pZSubtaskParent->m_ulSubtaskFlags |= zSUBTASK_MINIMIZED_MODAL;
         }

         pZSubtaskParent = pZSubtaskParent->m_pZParent;
      }

      m_ulSubtaskFlags |= zSUBTASK_MINIMIZED_MODAL;
   }

   if ( lEvent == zWND_EVENT_RESTORE && (m_ulSubtaskFlags & zSUBTASK_CREATED_MODAL) )
   {
      ZSubtask *pZSubtaskParent = m_pZParent;
      while ( pZSubtaskParent )
      {
         if ( pZSubtaskParent->m_pZFWnd && (pZSubtaskParent->m_ulSubtaskFlags & zSUBTASK_MINIMIZED_MODAL) )
         {
            pZSubtaskParent->m_ulSubtaskFlags &= ~zSUBTASK_MINIMIZED_MODAL;
            pZSubtaskParent->m_pZFWnd->ShowWindow( SW_RESTORE );
         }

         pZSubtaskParent = pZSubtaskParent->m_pZParent;
      }

      m_ulSubtaskFlags &= ~zSUBTASK_MINIMIZED_MODAL;
      m_pZFWnd->ShowWindow( SW_RESTORE );
      return( zACTIVEX_EVENT_COMPLETED ); // don't do default processing
   }

   // Let default processing occur.
   return( zACTIVEX_EVENT_CONTINUE );
}

/////////////////////////////////////////////////////////////////////////////
// Check for async processing and drag/drop processing.
void
ZSubtask::CheckMouseMove( UINT uModKeys, CPoint pt )
{
   if ( m_uMouseStatus == zMOUSE_ASYNC_DISABLE )
   {
   // CRect rect;
   // m_pZFWnd->GetWindowRect( rect );
   // if ( rect.PtInRect( pt ) )
   // {
   // }
   // else
   // {
   // }
   //
      TraceLineS( "ZSubtask::CheckMouseMove: ", "Why here?" );
      return;
   }

   m_ZMsg.wParam = uModKeys;
   m_ZMsg.lParam = (LPARAM) &pt;
   if ( (m_uMouseStatus & zMOUSE_CAPTURE) == zMOUSE_CAPTURE )
   {
      m_uMouseStatus |= zMOUSE_DRAG;
      if ( (m_uMouseStatus & zMOUSE_DRAG_LEFT) == zMOUSE_DRAG_LEFT )
      {
         if ( (m_ulWndOper & zWND_EVENT_LBUTTON_DRAG) == zWND_EVENT_LBUTTON_DRAG &&
              SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_LBUTTON_DRAG, 0 ) > zCURSOR_UNCHANGED )
         {
            if ( ProcessActionLoop( this, szlWndAct, 0, 0, zACTION_DIALOG_CODE_ONLY, TRUE, "OnLMouseDrag" ) > 0 )
            {
               return;
            }
         }
      }
      else
      if ( (m_uMouseStatus & zMOUSE_DRAG_RIGHT) == zMOUSE_DRAG_RIGHT )
      {
         if ( (m_ulWndOper & zWND_EVENT_RBUTTON_DRAG) == zWND_EVENT_RBUTTON_DRAG &&
              SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_RBUTTON_DRAG, 0 ) > zCURSOR_UNCHANGED )
         {
            if ( ProcessActionLoop( this, szlWndAct, 0, 0, zACTION_DIALOG_CODE_ONLY, TRUE, "OnRMouseDrag" ) > 0 )
            {
               return;
            }
         }
      }
   }

   if ( (m_ulWndOper & zWND_EVENT_MOUSE_MOVE) == zWND_EVENT_MOUSE_MOVE &&
        SetCursorFirstEntityByInteger( m_vDialog, szlWndEvent, szlType, zWND_EVENT_MOUSE_MOVE, 0 ) > zCURSOR_UNCHANGED )
   {
      if ( ProcessActionLoop( this, szlWndAct, 0, 0, zACTION_DIALOG_CODE_ONLY, TRUE, "OnMouseMove" ) > 0 )
      {
         return;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
//
// Create a font using specifications from the Zeidon.ini file
//
// HFONT CreateFont( int nHeight, // logical height of font
//                   int nWidth, // logical average character width
//                   int nEscapement, // angle of escapement
//                   int nOrientation, // base-line orientation angle
//                   int fnWeight, // font weight
//                   DWORD fdwItalic, // italic attribute flag
//                   DWORD fdwUnderline, // underline attribute flag
//                   DWORD fdwStrikeOut, // strikeout attribute
//                   DWORD fdwCharSet, // character set identifier
//                   DWORD fdwOutputPrecision, // output precision
//                   DWORD fdwClipPrecision, // clipping precision
//                   DWORD fdwQuality, // output quality
//                   DWORD fdwPitchAndFamily, // pitch and family
//                   LPCTSTR lpszFace // pointer to typeface name string
//                 );
//
/////////////////////////////////////////////////////////////////////////////
void
ZSubtask::CreateDefaultFont( )
{
   zCHAR  szFaceName[ 32 ];  // LF_FACENAME == 32
   zLONG  lFontSize;
   zSHORT nFont;

   GetWorkstationApplicationValues( m_vDialog, "Font", szFaceName, zsizeof( szFaceName ), &lFontSize, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
   if ( szFaceName[ 0 ] == 'Z' && (zstrcmp( szFaceName, "ZeidonOld" ) == 0 || zstrcmp( szFaceName, "ZeidonSize" ) == 0) )
   {
      if ( szFaceName[ 6 ] == 'S' )    // "ZeidonSize"
         nFont = -1;
      else
         nFont = 1;
   }
   else
   if ( szFaceName[ 0 ] && lFontSize )
   {
      nFont = 1;
      if ( lFontSize < 0 )
         lFontSize = -lFontSize;

      LOGFONT logFont;
      zmemset( &logFont, 0, sizeof( LOGFONT ) );
      logFont.lfCharSet = DEFAULT_CHARSET;
      logFont.lfHeight = lFontSize;
      strcpy_s( logFont.lfFaceName, zsizeof( logFont.lfFaceName ), szFaceName );
      HDC hDC = ::GetDC( NULL );

      ::ReleaseDC( NULL, hDC );

      m_pFontWS = new CFont;  // font override for Workstation
      if ( m_pFontWS->CreateFontIndirect( &logFont ) == 0 )
      {
         mDeleteInit( m_pFontWS );
      }
   }
   else
   {
      nFont = 0;
      m_pFontWS = 0;
   }

   GetWorkstationApplicationValues( m_vDialog, "FontCtrl", szFaceName, zsizeof( szFaceName ), &lFontSize, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
   mDeleteInit( m_pFontCtrl );
   m_pFontCtrl = new CFont;  // font override for controls
   if ( szFaceName[ 0 ] && lFontSize )
   {
      if ( m_pFontCtrl->CreatePointFont( lFontSize, szFaceName ) == 0 )
      {
         mDeleteInit( m_pFontCtrl );
      }
   }
   else
   {
      if ( nFont > 0 )
      {
         mDeleteInit( m_pFontCtrl );
      }
      else
      {
         zBOOL bRC = m_pFontCtrl->CreatePointFont( 80, _T( "MS Sans Serif" ) );
         if ( bRC == 0 )
         {
            mDeleteInit( m_pFontCtrl );
         }
         else
         if ( nFont == 0 )
         {
            m_bUseMapDlgUnits = TRUE;
         }
      }
   }

// SYSTEM_FONT
// DEFAULT_GUI_FONT
// m_hFont = (HFONT) ::GetStockObject( SYSTEM_FONT );
}

#if 0  // redefinition of 0-based entry
typedef struct ZFindDialog_tag
{
   ZSubtask *pZSubtask;     // Item count
   zPVOID   pvDialog;
   zLONG    lTID; // Lock type: 0-none; 1-read/update; 2-create; 3-delete
   HWND     hWnd;
   zCHAR    DlgN[ zTAG_LTH ];
   zCHAR    WndN[ zTAG_LTH ];
   zULONG   ulSubtaskState; // Lock count

} ZFindDialog;
#endif

#if 1
#define fnStartBrowseOfSubtaskList( a )
#define fnEndBrowseOfSubtaskList( a )
#else
//./ ADD NAME=fnStartBrowseOfSubtaskList
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnStartBrowseOfSubtaskList
//
//  PURPOSE:    To protect processes that are going through the list of
//              subtasks.  This function prevents another process from
//              deleting a subtask.
//
//  PARAMETERS: None.
//
//  DESCRIPTION:  When the current process is searching through the list of
//                subtasks it is possible that a subtask is being deleted by
//                another process.  This could cause the current process to
//                crash if it tries to access a deleted subtask pointer after it
//                has been deleted.  To keep this from happening we will set
//                up a semaphore using only code--we will avoid using a
//                system mutex for speed.  This code will allow any number
//                of processes to browse the subtask list unless one of the
//                processes is deleting a subtask and then no process is allowed.
//                This function will wait until it's OK to browse.
//
//  RETURNS:    0  - Everythink OK.
//              zCALL_ERROR - Error on call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT
fnStartBrowseOfSubtaskList( zLONG lType )
{
   return( 0 );
   if ( lType > 1 )
   {
      while ( TRUE )
      {
         // See note below about locking the 'write' mutex to find out
         // why we use a global variable instead of a regular mutex.
         SysMutexLock( g_vRegister, "ZDrSS", 0, 0 );
         if ( g_pSubtaskList[ 0 ].pvDialog == 0 )
         {
            g_pSubtaskList[ 0 ].pvDialog = lType;
            SysMutexUnlock( g_vRegister, "ZDrSS", 0 );
            break;
         }

         SysMutexUnlock( g_vRegister, "ZDrSS", 0 );
         SysWait( 0 );
      }
   }
   else
   {
      // Lock the 'browse' mutex.
      SysMutexLock( g_vRegister, "ZDrSS", 0, 0 );

      // Bump up the counter that keeps track of all the tasks that are
      // reading the subtask list.
      g_pSubtaskList[ 0 ].lTID++;

      // If the counter is 1 then this means no other tasks are currently
      // reading the subtask list and so we need to make sure no other task
      // has the 'write' mutex locked.
      if ( g_pSubtaskList[ 0 ].lTID == 1 )
      {
         // NOTE
         // We need to lock the 'write' mutex to keep another task from
         // acquiring a 'write' lock while we are reading the subtask list.
         // Since the 'write' mutex can be locked by one task and then
         // unlocked by another task we will use a global variable to indicate
         // that the 'write' mutex is locked.  If g_pSubtaskList[ 0 ].pvDialog is
         // not 0 then the mutex is locked.
         while ( TRUE )
         {
            SysMutexLock( g_vRegister, "ZDrSS", 0, 0 );
            if ( g_pSubtaskList[ 0 ].pvDialog == 0 )
            {
               g_pSubtaskList[ 0 ].pvDialog = lType;
               SysMutexUnlock( g_vRegister, "ZDrSS", 0 );
               break;
            }

            SysMutexUnlock( g_vRegister, "ZDrSS", 0 );
            SysWait( 0 );
         }
      }

      SysMutexUnlock( g_vRegister, "ZDrSS", 0 );
   }

   // If we get here everything's OK and the current task can now browse the subtask list.
   return( 0 );
}

void
fnEndBrowseOfSubtaskList( zLONG lType )
{
   return;
   if ( lType > 1 )
   {
      // See NOTE in fnStartBrowseOfSubtaskList( ) for an explanation of why we use a global variable.
      SysMutexLock( g_vRegister, "ZDrSS", 0, 0 );
      g_pSubtaskList[ 0 ].pvDialog = 0;
      SysMutexUnlock( g_vRegister, "ZDrSS", 0 );
   }
   else
   {
      // Lock the 'browse' mutex.
      SysMutexLock( g_vRegister, "ZDrSS", 0, 0 );

      // Decrement the counter that keeps track of all the subtasks that are reading the subtask list.
      g_pSubtaskList[ 0 ].lTID--;

      // If the counter is 0 then this means no other tasks are currently
      // reading the subtask list and the 'write' lock can be freed.
      if ( g_pSubtaskList[ 0 ].lTID == 0 )
      {
         // See NOTE in fnStartBrowseOfSubtaskList( ) for an explanation of why we use a global variable.
         SysMutexLock( g_vRegister, "ZDrSS", 0, 0 );
         g_pSubtaskList[ 0 ].pvDialog = 0;
         SysMutexUnlock( g_vRegister, "ZDrSS", 0 );
      }

      SysMutexUnlock( g_vRegister, "ZDrSS", 0 );
   }
}
#endif

// This assumes a SysMutexLock on ZDrSS has been done!
zLONG
ZSubtask::GetSubtaskStateIndex( ZSubtask *pZSubtask )
{
   if ( pZSubtask && g_pSubtaskList )
   {
      zLONG lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
      while ( lItemCnt > 0 )
      {
         if ( g_pSubtaskList[ lItemCnt ].pZSubtask && pZSubtask == g_pSubtaskList[ lItemCnt ].pZSubtask && pZSubtask->m_lTID == g_pSubtaskList[ lItemCnt ].lTID )
         {
            return( lItemCnt );
         }

         lItemCnt--;
      }
   }

   return( -1 );
}

zLONG
ZSubtask::GetSubtaskCount( zLONG lId )
{
   zLONG lCnt = 0;
   zLONG lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
   while ( g_pSubtaskList && lItemCnt > 0 )
   {
      if ( g_pSubtaskList[ lItemCnt ].pZSubtask && (lId == 0 || lId == g_pSubtaskList[ lItemCnt ].lTID) )
      {
         lCnt++;
      }

      lItemCnt--;
   }

   return( lCnt );
}

void
ZSubtask::InitializeSubtaskState( ZSubtask *pZSubtask, HWND hWnd )
{
   zLONG lItemCnt;

   if ( pZSubtask == 0 || g_pSubtaskList == 0 )
      return;

   // Protect this with a semaphore!!!
   fnStartBrowseOfSubtaskList( 2 );
// TraceLineS( "ZSubtask::InitializeSubtaskState Lock Mutex ZDrSS", "" );

   // Protect this with a semaphore!!!
   if ( pZSubtask->m_vDialog )
      SysMutexLock( pZSubtask->m_vDialog, "ZDrSS", 0, 0 );

// TraceLineS( "ZSubtask::InitializeSubtaskState Lock Mutex ZDrSS", "" );

   if ( pZSubtask && pZSubtask->m_pZTask &&
        (pZSubtask->m_pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      zCHAR  szMsg[ 128 ];

      sprintf_s( szMsg, zsizeof( szMsg ), "ZSubtask::ctor %s.%s ItemCnt before attach: ",
                 (*(pZSubtask->m_pzsDlgTag)).GetString(), (*(pZSubtask->m_pzsWndTag)).GetString() );
      TraceLineI( szMsg, ZSubtask::GetSubtaskCount( 0 ) );

      lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
      while ( lItemCnt > 0 )
      {
         if ( g_pSubtaskList[ lItemCnt ].pZSubtask )
         {
#ifdef zREMOTE_SERVER
            sprintf_s( szMsg, zsizeof( szMsg ), " [S%ld.T%ld.t%ld.s%ld] Dlg: %s Wnd: %s vSubtask: %#010hx  Subtask: ",
                      g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZSocketTask, AfxGetThread( ),
                      g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZSocketTask->m_pWinThread,
                      g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZSocketTask->m_sock,
                      g_pSubtaskList[ lItemCnt ].DlgN,
                      g_pSubtaskList[ lItemCnt ].WndN,
                      g_pSubtaskList[ lItemCnt ].pvDialog );
#else
            sprintf_s( szMsg, zsizeof( szMsg ), " Dlg: %s Wnd: %s vSubtask: %#010hx  Subtask: ",
                      g_pSubtaskList[ lItemCnt ].DlgN,
                      g_pSubtaskList[ lItemCnt ].WndN,
                      (zULONG) g_pSubtaskList[ lItemCnt ].pvDialog );
#endif
            TraceLineX( szMsg, (zLONG) g_pSubtaskList[ lItemCnt ].pZSubtask );
         }

         lItemCnt--;
      }
   }

   zPVOID pvDialog = SysGetHandleFromPointer( pZSubtask->m_vDialog );
   zVIEW  vZDrSystem;

   zLONG lPos = ZSubtask::GetSubtaskStateIndex( pZSubtask );
   if ( lPos > 0 && hWnd == 0 )
   {
      TraceLineS( "ZSubtask::InitializeSubtaskState: ", "Subtask unexpectedly located!!!" );
   }
   else
   if ( lPos <= 0 )
   {
      lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
      for ( lPos = 1; lPos <= lItemCnt; lPos++ )
      {
         if ( g_pSubtaskList[ lPos ].pZSubtask == 0 )
            break;
      }

      if ( lPos > lItemCnt )
      {
         lItemCnt++;
         lPos = lItemCnt;
         g_pSubtaskList[ 0 ].pZSubtask = (ZSubtask *) lItemCnt;
      }
   }

   g_pSubtaskList[ lPos ].ulSubtaskState = zSUBTASK_STATE_INIT;
   g_pSubtaskList[ lPos ].pZSubtask = pZSubtask;
   g_pSubtaskList[ lPos ].pvDialog = pvDialog;
   g_pSubtaskList[ lPos ].hWnd = hWnd;
#ifdef zREMOTE_SERVER
// g_pSubtaskList[ lPos ].lTID = (zLONG) AfxGetThread( )->m_nThreadID;
#else
   g_pSubtaskList[ lPos ].lTID = SysGetTaskFromView( pZSubtask->m_vDialog );
#endif
   g_pSubtaskList[ lPos ].lTID = pZSubtask->m_lTID;
   strcpy_s( g_pSubtaskList[ lPos ].DlgN, zsizeof( g_pSubtaskList[ lPos ].DlgN ), *(pZSubtask->m_pzsDlgTag) );
   strcpy_s( g_pSubtaskList[ lPos ].WndN, zsizeof( g_pSubtaskList[ lPos ].WndN ), *(pZSubtask->m_pzsWndTag) );

// TraceLineS( "ZSubtask::ctor Lock Mutex ZDrSS", "" );

   if ( GetViewByName( &vZDrSystem, "__ZDrSystem", pZSubtask->m_pZTask->m_pZDrApp->m_vSubtask, zLEVEL_SYSTEM ) > 0 )
   {
      CreateViewFromViewForTask( &vZDrSystem, vZDrSystem, pZSubtask->m_vDialog );
      SetCursorFirstEntityByInteger( vZDrSystem, "Task", "Handle", (zLONG) pZSubtask->m_pZTask, 0 );
      CreateEntity( vZDrSystem, "Subtask", zPOS_FIRST );
      SetAttributeFromString( vZDrSystem, "Subtask", "DlgTag", *(pZSubtask->m_pzsDlgTag) );
      SetAttributeFromString( vZDrSystem, "Subtask", "WndTag", *(pZSubtask->m_pzsWndTag) );
      SetAttributeFromInteger( vZDrSystem, "Subtask", "Handle", (zLONG) pvDialog );
   // TraceLine( "ZSubtask::InitializeSubtaskState for Dialog: 0x%08x", pvDialog );
      DropView( vZDrSystem );
   }

   if ( pZSubtask && pZSubtask->m_pZTask &&
        (pZSubtask->m_pZTask->m_nTraceAction & 0x72) == 0x72 )
   {
      zCHAR  szMsg[ 256 ];
      sprintf_s( szMsg, zsizeof( szMsg ), "ZSubtask::ctor %s.%s ItemCnt: after attach: ",
                 (*(pZSubtask->m_pzsDlgTag)).GetString(), (*(pZSubtask->m_pzsWndTag)).GetString() );
      TraceLineI( szMsg, ZSubtask::GetSubtaskCount( 0 ) );
      lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
      while ( lItemCnt > 0 )
      {
         if ( g_pSubtaskList[ lItemCnt ].pZSubtask )
         {
#ifdef zREMOTE_SERVER
            sprintf_s( szMsg, zsizeof( szMsg ), " [S%ld.T%ld.t%ld.s%ld] Dlg: %s Wnd: %s vSubtask: %#010hx  Subtask: ",
                       g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZSocketTask, AfxGetThread( ),
                       g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZSocketTask->m_pWinThread,
                       g_pSubtaskList[ lItemCnt ].pZSubtask->m_pZSocketTask->m_sock,
                       g_pSubtaskList[ lItemCnt ].DlgN, g_pSubtaskList[ lItemCnt ].WndN,
                       g_pSubtaskList[ lItemCnt ].pvDialog );
#else
            sprintf_s( szMsg, zsizeof( szMsg ), " Dlg: %s Wnd: %s vSubtask: %#010hx  Subtask: ",
                       g_pSubtaskList[ lItemCnt ].DlgN, g_pSubtaskList[ lItemCnt ].WndN,
                       (zULONG) g_pSubtaskList[ lItemCnt ].pvDialog );
#endif
            TraceLineX( szMsg, (zLONG) g_pSubtaskList[ lItemCnt ].pZSubtask );
         }

         lItemCnt--;
      }
   }

// TraceLineS( "ZSubtask::InitializeSubtaskState Unlock Mutex ZDrSS", "" );
// fnEndBrowseOfSubtaskList( 2 );

// TraceLineS( "ZSubtask::InitializeSubtaskState Unlock Mutex ZDrSS", "" );
   if ( pZSubtask->m_vDialog )
      SysMutexUnlock( pZSubtask->m_vDialog, "ZDrSS", 0 );
}

zULONG
ZSubtask::GetSubtaskState( ZSubtask *pZSubtask )
{
   zULONG ulSubtaskState = zSUBTASK_STATE_ERROR;

   if ( pZSubtask && g_pSubtaskList )
   {
      // Protect this with a semaphore!!! Protect as a "read" operation!
      fnStartBrowseOfSubtaskList( 1 );

      zLONG lItemCnt = ZSubtask::GetSubtaskStateIndex( pZSubtask );
      if ( lItemCnt > 0 )
         ulSubtaskState = g_pSubtaskList[ lItemCnt ].ulSubtaskState;

   // TraceLineS( "GetSubtaskState Unlock Mutex ZDrSS", "" );
      fnEndBrowseOfSubtaskList( 1 );
   }

   return( ulSubtaskState );
}

// Return the state of the Subtask prior to the change!
// Note that Remove is performed prior to Add.
zULONG
ZSubtask::SetSubtaskState( ZSubtask *pZSubtask,
                           zULONG   ulStateRemove,
                           zULONG   ulStateAdd )
{
   zULONG ulSubtaskState = zSUBTASK_STATE_ERROR;

   if ( pZSubtask && g_pSubtaskList )
   {
      // Protect this with a semaphore!!! Protect as a "read" operation!
      fnStartBrowseOfSubtaskList( 1 );
   // TraceLineS( "SetSubtaskState Lock Mutex ZDrSS", "" );

      zLONG lItemCnt = ZSubtask::GetSubtaskStateIndex( pZSubtask );
      if ( lItemCnt > 0 )
      {
         ulSubtaskState = g_pSubtaskList[ lItemCnt ].ulSubtaskState;
         g_pSubtaskList[ lItemCnt ].ulSubtaskState &= ~ulStateRemove;
         g_pSubtaskList[ lItemCnt ].ulSubtaskState |= ulStateAdd;
      }

   // TraceLineS( "SetSubtaskState Unlock Mutex ZDrSS", "" );
      fnEndBrowseOfSubtaskList( 1 );

      if ( (ulStateAdd & zSUBTASK_STATE_MARK_FOR_DELETE) && lItemCnt > 0 && mIs_hWnd( g_pSubtaskList[ lItemCnt ].hWnd ) )
      {
         ::SendMessage( g_pSubtaskList[ lItemCnt ].hWnd, zZEIDON_POSTED_MARK_DELETE, 1, 0 );
      }
   }

   return( ulSubtaskState );
}

void
ZSubtask::TerminateSubtaskState( ZSubtask *pZSubtask )
{
   if ( pZSubtask == 0 || g_pSubtaskList == 0 )
      return;

   zVIEW vSubtask = pZSubtask->m_vDialog;

   // Protect this with a semaphore!!!
   fnStartBrowseOfSubtaskList( 3 );
// TraceLineS( "ZSubtask::TerminateSubtaskState Lock Mutex ZDrSS", "" );

   zLONG lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
   zLONG lPos = ZSubtask::GetSubtaskStateIndex( pZSubtask );
   if ( lPos > 0 )
   {
      zPVOID pvDialog = SysGetHandleFromPointer( pZSubtask->m_vDialog );
      zVIEW  vZDrSystem;

      if ( pZSubtask && pZSubtask->m_pZTask && (pZSubtask->m_pZTask->m_nTraceAction & 0x72) == 0x72 )
      {
#ifdef zREMOTE_SERVER
         zCHAR  szMsg[ 256 ];
         TraceLineI( "ZSubtask::TerminateSubtaskState Item Count before detach: ",
                     ZSubtask::GetSubtaskCount( 0 ) );

         zLONG  lTemp = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
         while ( lTemp > 0 )
         {
            if ( g_pSubtaskList[ lTemp ].pZSubtask )
            {
               sprintf_s( szMsg, zsizeof( szMsg ), " [S%ld.T%ld.t%ld.s%ld] Dlg: %s Wnd: %s vSubtask: %#010hx  Subtask: ",
                         g_pSubtaskList[ lTemp ].pZSubtask->m_pZSocketTask, AfxGetThread( ),
                         g_pSubtaskList[ lTemp ].pZSubtask->m_pZSocketTask->m_pWinThread,
                         g_pSubtaskList[ lTemp ].pZSubtask->m_pZSocketTask->m_sock,
                         g_pSubtaskList[ lTemp ].DlgN,
                         g_pSubtaskList[ lTemp ].WndN,
                         g_pSubtaskList[ lTemp ].pvDialog );
            }

            lTemp--;
         }
#else
      // ListWindowsAndControls( pZSubtask, "ZSubtask::TerminateSubtaskState Start", 0 );
#endif
      }

      if ( GetViewByName( &vZDrSystem, "__ZDrSystem", pZSubtask->m_pZTask->m_pZDrApp->m_vSubtask, zLEVEL_SYSTEM ) > 0 )
      {
         CreateViewFromViewForTask( &vZDrSystem, vZDrSystem, pZSubtask->m_vDialog );
         if ( SetCursorFirstEntityByInteger( vZDrSystem, "Task", "Handle", (zLONG) pZSubtask->m_pZTask, 0 ) == zCURSOR_SET &&
              SetCursorFirstEntityByInteger( vZDrSystem, "Subtask", "Handle", (zLONG) pvDialog, 0 ) == zCURSOR_SET )
         {
         // TraceLine( "ZSubtask::TerminateSubtaskState for Dialog: 0x%08x", pvDialog );
            DeleteEntity( vZDrSystem, "Subtask", zREPOS_FIRST );
         }

         DropView( vZDrSystem );
      }

      // Make this one of the last things we do.
      g_pSubtaskList[ lPos ].pZSubtask = 0;

   // lItemCnt = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;     don't do this
   // while ( g_pSubtaskList[ lItemCnt ].pZSubtask == 0 )   unless we protect
   //    lItemCnt--;                                        with a mutex

   // g_pSubtaskList[ 0 ].pZSubtask = (ZSubtask *) lItemCnt;

      if ( pZSubtask && pZSubtask->m_pZTask && (pZSubtask->m_pZTask->m_nTraceAction & 0x72) == 0x72 )
      {
#ifdef zREMOTE_SERVER
         zCHAR  szMsg[ 256 ];
         TraceLineI( "ZSubtask::TerminateSubtaskState Item Count: after detach: ", ZSubtask::GetSubtaskCount( 0 ) );
         zLONG  lTemp = (zLONG) g_pSubtaskList[ 0 ].pZSubtask;
         while ( lTemp > 0 )
         {
            if ( g_pSubtaskList[ lTemp ].pZSubtask )
            {
               sprintf_s( szMsg, zsizeof( szMsg ), " [S%ld.T%ld.t%ld.s%ld] Dlg: %s Wnd: %s vSubtask: %#010hx  Subtask: ",
                         g_pSubtaskList[ lTemp ].pZSubtask->m_pZSocketTask, AfxGetThread( ),
                         g_pSubtaskList[ lTemp ].pZSubtask->m_pZSocketTask->m_pWinThread,
                         g_pSubtaskList[ lTemp ].pZSubtask->m_pZSocketTask->m_sock,
                         g_pSubtaskList[ lTemp ].DlgN,
                         g_pSubtaskList[ lTemp ].WndN,
                         g_pSubtaskList[ lTemp ].pvDialog );
               TraceLineX( szMsg, (zLONG) g_pSubtaskList[ lTemp ].pZSubtask );
            }

            lTemp--;
         }
#else
      // ListWindowsAndControls( pZSubtask, "ZSubtask::TerminateSubtaskState Start", 0 );
#endif
      }
   }

// TraceLineS( "ZSubtask::TerminateSubtaskState Unlock Mutex ZDrSS", "" );
   fnEndBrowseOfSubtaskList( 3 );
}

void
ZSubtask::RefreshSplitters( )
{
   if ( m_ulSubtaskFlags & zSUBTASK_SUBWND_SPLITTER_PANE )
   {
      ZDrView *pZView = m_pZView->m_pNextView;
      while ( pZView && pZView != m_pZView )
      {
         if ( pZView->m_pZSubtask )
         {
            if ( (pZView->m_pZSubtask->m_ulSubtaskFlags & zSUBTASK_STATE_PREVENT_REFRESH) == 0 )
               pZView->m_pZSubtask->MapFromOI( );
         }

         pZView = pZView->m_pNextView;
      }
   }

   if ( (m_ulSubtaskFlags & zSUBTASK_STATE_PREVENT_REFRESH) == 0 )
      MapFromOI( );
}

ZSubtask *
ZSubtask::GetSplitterMainSubtask( )
{
   ZDrView  *pZView = m_pZView;

   while ( pZView )
   {
      if ( pZView->m_pZSubtask && (pZView->m_pZSubtask->m_ulSubtaskFlags & zSUBTASK_SPLITTER_MAIN_SUBTASK) )
      {
         return( pZView->m_pZSubtask );
      }

      pZView = pZView->m_pNextView;
      if ( pZView == m_pZView )
         break;
   }

   return( 0 );
}

zBOOL
ZSubtask::IsValidCtrl( ZMapAct *pzma )
{
   if ( m_pZMIXCtrl == 0 || pzma == 0 || m_pZMIXCtrl->GetNodeIndex( pzma ) == 0 )
   {
      return( FALSE );
   }

   return( TRUE );
}
