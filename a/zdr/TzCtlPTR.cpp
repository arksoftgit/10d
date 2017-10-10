/////////////////////////////////////////////////////////////////////////////
// Project TzCtl
//
// This is a part of the Zeidon Dynamic Rendering of GUI applications package.
// Copyright © 1995 - 2016 QuinSoft, Inc.
// All Rights Reserved.
//
// SUBSYSTEM:    tzctl.dll - ZDr Design Control implementations
// FILE:         tzctlptr.cpp
// AUTHOR:
//
// OVERVIEW
// ========
// Source file for implementation of Zeidon Painter ctrl.
//

//
// CHANGE LOG - most recent first order
//
// 200y.mm.dd    xxx
//    Note ...
//
// 2001.11.26    DKS   Rosi
//    Fixed stack problem when comparing controls for HeapSort to
//    implement SetOverlapVisibility.
//
// 2001.06.28    DKS   Z10
//    Fixed painting of ruler.
//
// 2001.04.19    DKS   Z10
//    Change to use MapRect units as base for conversion to dialog units.
//
// 2001.3.14     DKS   53434
//    Fix to speed of arrow key sizing of controls.
//
// 2001.3.12     TMV   ActiveX
//    Uncomment call to WritePersitProperties() in
//    TZPainterWindow::UpdateZeidonWindow( )
//
// 2001.03.07    BL    GRID
//    Modified TZPainterWindow::PaintCtrl for Grid in GroupBox.
//
// 2001.01.02    DKS   TB53981
//    Undo/Redo fix.
//
// 2000.09.05    BL    Z10
//    Modified OnMenuSelection: Added CreateTemporalSubobjectVersion.
//
// 2000.03.27    DKS   TB1013
//    Paint ctrls in the correct position when primary window is scrolled.
//
// 2000.03.15    DKS   Enhance
//    Use Alt+Shift+Arrow to permit new parent when moving ctrl(s).
//
// 1999.11.24    BL    Z10    new menu structure
//    Modified TZPainterWindow::OnSetFocus for refresh menu list, action
//    list and shortcut list (= modeless Subwindows)
//
// 1999.11.08    DKS   Z10    ActiveX
//    Fix view to dialog bug introduced by ActiveX implementation.
//
// 1999.07.23    DKS   Z10    QS999
//    Refresh Painter window after dropping a page (tab) from the notebook.
//
// 1999.05.11    DKS   Z10    ActiveX
//    Fixed caption (side effect of ActiveX using one Document).
//
// 1999.03.10  DKS
//    Altered the Profile functions to remove name conflict.
//
// 1999.02.12    DKS
//    Support Ctrl+C and Ctrl+V for Copy/Paste and
//            Ctrl+Z and Ctrl+Y for Undo/Redo.
//
// 1999.02.05    DKS
//    Implemented support of abut ctrls.
//
// 1999.01.27    DKS
//    Consolidated code for deletion of a ctrl in preparation for the
//    implementation of Undo/Redo.
//
// 1999.01.25    DKS
//    Failed attempt to reduce painting at initialization.
//
// 1999.01.23    DKS
//    Fixed sporadic bug caused by saving a window without updating it
//    when auto-sizeable ctrls existed on the window.  This fix caused
//    naming changes throughout tzctlpt*.cpp.
//
// 1999.01.21    DKS
//    Holding on to scroll position across update iterations.
//
// 1998.12.14    DKS
//    Ruler painting now performed on return from sub-window.
//
// 1998.10.12    DKS
//    Modified Dialog conversion to set the size of the Relative Pos/Size
//    area properly.
//
// 1998.09.23    DKS
//    Select active window in WindowList (TB 217)
//
// 1998.08.13    DKS
//    Fix to Tab ctrl acceptance by GroupBox (now warns)
//

#include "zstdafx.h"

#define TZCTL_CLASS AFX_EXT_CLASS
#include "ZDr.h"

#include "TzCtl.h"
#include "TzCtlGbl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// #define DEBUG_ALL
// #define zDEBUG_CTRL

#define zPAINTER_MENUITEM_ID  10001

IMPLEMENT_DYNAMIC( TZPainterWindow, CFrameWnd )

BEGIN_MESSAGE_MAP( TZPainterWindow, CFrameWnd )
   ON_WM_SYSKEYDOWN( )
   ON_WM_KEYDOWN( )
   ON_WM_KEYUP( )
   ON_WM_INITMENU( )
   ON_WM_INITMENUPOPUP( )
   ON_WM_SETFOCUS( )
   ON_WM_KILLFOCUS( )
   ON_WM_CREATE( )
   ON_WM_CLOSE( )
   ON_WM_PAINT( )
   ON_WM_NCPAINT( )
   ON_WM_NCACTIVATE( )
// ON_WM_NCDESTROY( )
   ON_WM_WINDOWPOSCHANGED( )
   ON_WM_ERASEBKGND( )
   ON_COMMAND( zPAINTER_MENUITEM_ID, OnMenuSelection )
// ON_WM_COMMAND( )
END_MESSAGE_MAP( )

// CLASS IMPLEMENTATION : TZPainterWindow
TZPainterWindow::TZPainterWindow( TZPainterBar *pPainterBar,
                                  zVIEW  vDialog, zBOOL bPaintWindow )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::ctor", "" );
#endif

   CRect   rectWork;

   // Initialize class variables
   m_pBar = pPainterBar;
   m_nSelectCnt = 0;
   m_pCurrCtrl = 0;
   m_pLastSelected = 0;
   m_pDirectModeCtrl = 0;
   m_nMaxTabIdNbr = 0;
   m_pPaintParent = 0;
   m_nSnap = 0;         // was 2 for half-height snapping
   m_lMaxZKey = 0;
   m_vDialog = vDialog;
   m_fWndState = zTZPW_UPDATEABLE | zTZPW_INITIALIZING;
   m_uSizeX = 0;
   m_uSizeY = 0;
   m_pMenu = 0;
   m_pPainterClient = 0;
   m_lScrollUnitsX = 0;
   m_lScrollUnitsY = 0;
   m_ulZOrder = 0;

   m_lTopMargin = 0;
   m_lLeftMargin = 0;
   m_lRptSizeX = 0;
   m_lRptSizeY = 0;

   m_pLastGroupSet = 0;
   m_lHScrollMax = 0;
   m_lVScrollMax = 0;
   m_lUnit = zTZPTR_256THS_INCH;
   m_nGranularity = (zSHORT) mConvertPixelTo256thInchX( 1 );
   m_lPrintFlags = 0;

   m_pActiveX = 0;
   m_pUndoRedo = 0;
   m_pUndoCurr = 0;
   m_pRedoCurr = 0;

   m_CtrlList.SetSize( 20, 10 );
   m_nCtrlCnt = 0;

   // Create the painter window using the complete size of the parents
   // client area.
   pPainterBar->m_pZSubtask->m_pZFWnd->GetWindowRect( rectWork );
   rectWork.top += ::GetSystemMetrics( SM_CYCAPTION );
   rectWork.top += ::GetSystemMetrics( SM_CYMENU );
   rectWork.top += (2 * ::GetSystemMetrics( SM_CYSIZEFRAME ));
   rectWork.top += ::GetSystemMetrics( SM_CYICON );
   rectWork.top += 28;  // a fudge factor
   rectWork.bottom = ::GetSystemMetrics( SM_CYSCREEN );
   rectWork.bottom -= GetSystemMetrics( SM_CYICONSPACING );

   Attr.Style = WS_CAPTION | WS_THICKFRAME | WS_VISIBLE | WS_CLIPSIBLINGS |
                WS_VSCROLL | WS_HSCROLL;
   Attr.X = rectWork.left;
   Attr.Y = rectWork.top;
   Attr.W = rectWork.right - rectWork.left;
   Attr.H = rectWork.bottom - rectWork.top;

   m_pBar->m_PainterWindowList.SetAtGrow( m_pBar->m_nWndCnt++, this );
// TraceLineI( "TZPainterWindow::ctor WndCnt: ", m_pBar->m_nWndCnt );
   m_pBar->m_pActivePainterWindow = this;

   // If a view to a window has been passed, create a new view from that
   // view, lock it and store it in our class.
   if ( vDialog )
   {
      zPCHAR  pchTag;

      if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      {
         GetIntegerFromAttribute( &m_lPrintFlags, vDialog,
                                  szlReport, "PrintFlags" );
         GetIntegerFromAttribute( &m_lUnit, vDialog, szlReport, "Unit" );
         GetAddrForAttribute( &pchTag, vDialog, szlReport, szlTag );
         m_csDlgTag = pchTag;
         GetAddrForAttribute( &pchTag, vDialog, szlPage, szlTag );
         m_csWndTag = pchTag;
      }
      else
      {
         GetAddrForAttribute( &pchTag, vDialog, szlDialog, szlTag );
         m_csDlgTag = pchTag;
         GetAddrForAttribute( &pchTag, vDialog, szlWindow, szlTag );
         m_csWndTag = pchTag;
      }

      CreateViewFromViewForTask( &m_vDialog, vDialog, vDialog );
      SfLockView( m_vDialog );
      SetNameForView( m_vDialog, szlTZWINDOW, 0, zLEVEL_TASK );
      LoadFrame( IDR_MAINFRAME );   // Create( );

#if 0 // this is all taken care of by the CFrameWnd dtor
      if ( m_hWnd && mIs_hWnd( m_hWnd ) )
      {
         HMENU hMenu = ::GetMenu( m_hWnd );
         ::SetMenu( m_hWnd, 0 );
         if ( hMenu )
            ::DestroyMenu( hMenu );

         m_hMenuDefault = 0;
      }
#endif

//    if ( bPaintWindow )        // This breaks Ctrl+E processing, so I
//       PaintZeidonWindow( );   // guess we will have to live with the
//    else                       // double paint on initialization.
//    {
//       ShowWindow( SW_HIDE );
//       return;
//    }

      PaintZeidonWindow( );
   }
   else
   {
      // This should never happen!
      MessageSend( m_pBar->m_vSubtask, 0,
                   "Error - Contact Zeidon Development",
                   "TZPainterWindow::ctor Missing view in painter",
                   zMSGQ_MODAL_ERROR, FALSE );
//   else
//      LoadFrame( IDR_MAINFRAME );   // Create( );
   }

   // Clear the text in the DIL of the PainterBar
   SetDIL_Text( );

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      m_pPainterClient->m_pRuler = new TZRuler( this );

   // We are going to restrict the number of open painter windows to be
   // 6 or less so that we (hopefully) do not reach the maximum window
   // resource limitation.
   if ( m_pBar->m_nWndCnt > 6 )
   {
      TZPainterWindow *pPainterWindow;

      pPainterWindow = m_pBar->m_PainterWindowList[ 0 ];
      pPainterWindow->SendMessage( WM_CLOSE, 0, 0 );
   }

   if ( MiValidView( m_vDialog ) )
   {
      zVIEW vTZWINDOWL;
      zPCHAR pchWindowPage;

      if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      {
         pchWindowPage = szlPage;
         GetViewByName( &vTZWINDOWL, szlPAGEL, m_vDialog, zLEVEL_TASK );
      }
      else
      {
         pchWindowPage = szlWindow;
         GetViewByName( &vTZWINDOWL, szlTZWINDOWL, m_vDialog, zLEVEL_TASK );
      }

      SetAllSelStatesForEntityForSet( vTZWINDOWL, pchWindowPage, 0, 1, 0 );
      SetCursorFirstEntityByEntityCsr( vTZWINDOWL, pchWindowPage,
                                       m_vDialog, pchWindowPage, 0 );
      SetSelectStateOfEntityForSet( vTZWINDOWL, pchWindowPage, 1, 1 );
//    TraceLineS( "TZPainterWindow::ctor: ", "LoadWindowList" );
      m_pBar->LoadWindowList( );
   }

   // Finally, show the window.
   ShowWindow( SW_SHOW );
   UpdateWindow( );
}

/////////////////////////////////////////////////////////////////////////////
// TZPainterWindow message handlers

BOOL
TZPainterWindow::PreCreateWindow( CREATESTRUCT& cs )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::PreCreateWindow", "" );
#endif

   // TODO: Modify the Window class or styles here by modifying
   // the CREATESTRUCT cs.
   cs.hwndParent = m_pBar->m_pZSubtask->m_pZFWnd->m_hWnd;

// CRect rect;
// m_pBar->m_pZSubtask->m_pZFWnd->GetWindowRect( rect );
//
// cs.x += rect.left;
// cs.y += rect.top;

   return( CFrameWnd::PreCreateWindow( cs ) );
}

int
TZPainterWindow::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnCreate: ", m_csWndTag );
#endif

// m_hWndOwner = m_pBar->m_pZSubtask->m_pZFWnd->m_hWnd;
//
   if ( CFrameWnd::OnCreate( lpCreateStruct ) == -1 )
      return( -1 );

   WINDOWPLACEMENT wp;

   if ( (m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
   {
      if ( ReadWindowPlacement( m_vDialog, "Design",
                                m_csDlgTag, m_csWndTag, &wp ) &&
           CheckWindowPos( &wp ) )
      {
//       if ( (lpCreateStruct->style & WS_THICKFRAME) == 0 )
//       {
//          wp.rcNormalPosition.right =
//                               wp.rcNormalPosition.left + lpCreateStruct->cx;
//          wp.rcNormalPosition.bottom =
//                               wp.rcNormalPosition.top + lpCreateStruct->cy;
//       }
//
//       // Retain designed sizes and last used positions.
//       wp.rcNormalPosition.right = wp.rcNormalPosition.left + Attr.W;
//       wp.rcNormalPosition.bottom = wp.rcNormalPosition.top + Attr.H;
//       TraceRect( "TZPainterWindow::OnCreate wp.rect", wp.rcNormalPosition );

         SetWindowPlacement( &wp );
      }
   }

   SetActiveWindow( );
   ModifyStyle( WS_OVERLAPPED | WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                WS_THICKFRAME | WS_POPUPWINDOW | WS_CAPTION );
   ModifyStyleEx( WS_EX_APPWINDOW, WS_EX_CONTROLPARENT );

   return( 0 );
}

BOOL
TZPainterWindow::OnCreateClient( LPCREATESTRUCT lpcs,
                                 CCreateContext *pContext )
{
   ASSERT( m_hWnd );
   ASSERT( mIs_hWnd( m_hWnd ) );

#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnCreateClient", "" );
#endif

   // Note: can be a CWnd with PostNcDestroy self cleanup.
   new TZPainterClient( this, pContext ); // PainterClient sets m_pPainterClient
   if ( m_pPainterClient == 0 )
   {
      TraceLineS( "TZPainterWindow::CreateView failed", "" );
      return( FALSE );
   }

   if ( /* afxData.bWin4 && */   // Need to get Windows version for this
        (m_pPainterClient->GetExStyle( ) & WS_EX_CLIENTEDGE) )
   {
      // Remove the 3d style from the frame, since the view is providing it.
      // Make sure to recalc the non-client area.
      ModifyStyleEx( WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED );
   }

   return( TRUE );
}

// TZPainterWindow - paint window ... to paint the background sizing rect.
// Can't do it since the painter window itself is a Driver window.
//    COLOR_3DSHADOW - Gray, RGB(192,192,192)
//    COLOR_3DFACE - Lt Gray, RGB(223,223,223)
void
TZPainterWindow::OnPaint( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnPaint: ", m_csWndTag );
#endif

#if 0
   CRect rect;
   if ( GetUpdateRect( rect, FALSE ) )
   {
   CPaintDC dc( this );   // a paint DC calls Begin and End Paint
// CRect& rect = *(CRect *) &dc.m_ps.rcPaint;
   CBrush brush( ::GetSysColor( COLOR_BTNFACE ) );
   COLORREF colorShadow( ::GetSysColor( COLOR_BTNSHADOW ) );
   CPen penGray( PS_INSIDEFRAME, 3, colorShadow );
   CPen *pPenOld = dc.SelectObject( &penGray );
   zLONG lWidth = rect.Width( );
   zLONG lHeight = rect.Height( );
   zLONG lMarginX;
   zLONG lMarginY;

   // Draw the background.
   dc.FillRect( rect, &brush );
   lMarginX = (lWidth - 1024) / 2;
   lMarginY = (lHeight - 768) / 2;

   if ( lMarginX > 0 || lMarginY > 0 )
   {
      if ( lMarginX > 0 )
      {
         rect.left += lMarginX;
         rect.right -= lMarginX;
      }

      if ( lMarginY > 0 )
      {
         rect.top += lMarginY;
         rect.bottom -= lMarginY;
      }

      dc.Rectangle( rect );
   }

   lMarginX = (lWidth - 800) / 2;
   lMarginY = (lHeight - 600) / 2;

   if ( lMarginX > 0 || lMarginY > 0 )
   {
      if ( lMarginX > 0 )
      {
         rect.left += lMarginX;
         rect.right -= lMarginX;
      }

      if ( lMarginY > 0 )
      {
         rect.top += lMarginY;
         rect.bottom -= lMarginY;
      }

      dc.Rectangle( rect );
   }

   lMarginX = (lWidth - 640) / 2;
   lMarginY = (lHeight - 480) / 2;

   if ( lMarginX > 0 || lMarginY > 0 )
   {
      if ( lMarginX > 0 )
      {
         rect.left += lMarginX;
         rect.right -= lMarginX;
      }

      if ( lMarginY > 0 )
      {
         rect.top += lMarginY;
         rect.bottom -= lMarginY;
      }

      dc.Rectangle( rect );
   }

   if ( pPenOld )
      dc.SelectObject( pPenOld );
   }
   else
#endif
      CFrameWnd::OnPaint( );
}

void
TZPainterWindow::OnNcPaint( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnNcPaint: ", m_csWndTag );
#endif

   CFrameWnd::OnNcPaint( );
}

BOOL
TZPainterWindow::OnNcActivate( BOOL bActive )
{
#ifdef DEBUG_ALL
// TraceLineI( "TZPainterWindow::OnNcActivate bActive: ", bActive );
#endif
// bActive = CFrameWnd::OnNcActivate( bActive );
   PostMessage( WM_NCPAINT, 1 );   // paint myself
   return( CFrameWnd::OnNcActivate( bActive ) );
// return( bActive );
}

BOOL
TZPainterWindow::OnEraseBkgnd( CDC *pDC )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnEraseBkgnd", "" );
#endif

   return( TRUE );   // the view will erase/paint itself
// return( CFrameWnd::OnEraseBkgnd( pDC ) );
}

void
TZPainterWindow::OnClose( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnClose ", "======================>" );
#endif

   if ( m_pBar && MiValidView( m_vDialog ) )
   {
      WINDOWPLACEMENT wp;
      wp.length = sizeof( wp );
      if ( GetWindowPlacement( &wp ) )
      {
      // TraceRect( "TZPainterWindow::OnClose wp.rect", wp.rcNormalPosition );
         wp.flags = 0;
         if ( IsZoomed( ) )
            wp.flags |= WPF_RESTORETOMAXIMIZED;

         // and write it to the .INI file
         WriteWindowPlacement( m_vDialog, "Design",
                               m_csDlgTag, m_csWndTag, &wp );

         CPoint ptScrollPos = m_pPainterClient->GetDeviceScrollPosition( );
         SetProfileNbr( m_vDialog, "Design", m_csDlgTag, m_csWndTag,
                        "ScrollX", ptScrollPos.x );
         SetProfileNbr( m_vDialog, "Design", m_csDlgTag, m_csWndTag,
                        "ScrollY", ptScrollPos.y );
         if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
         {
            SetProfileNbr( m_vDialog, "Design", "_Report", "_Painter",
                           "LeftMargin", m_lLeftMargin );
         }
      }
   }

   UpdateZeidonWindow( );
   EmptyPainterWindow( );
   m_pLastSelected = 0;

   SetDIL_Text( );

   // Detach from the list of painter windows.
   if ( m_pBar )
   {
      zVIEW  vTZWINDOWL;
      zPCHAR pchWindowPage;

      if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      {
         pchWindowPage = szlPage;
         GetViewByName( &vTZWINDOWL, szlPAGEL, m_vDialog, zLEVEL_TASK );
      }
      else
      {
         pchWindowPage = szlWindow;
         GetViewByName( &vTZWINDOWL, szlTZWINDOWL, m_vDialog, zLEVEL_TASK );
      }

      if ( m_pBar->m_pActivePainterWindow == this )
      {
      // fnSetProfileString( m_vDialog, "Design", m_csDlgTag, "..Start",
      //                     "Window", m_csWndTag );
         m_pBar->m_pActivePainterWindow = 0;
      }

      zSHORT nPos = m_pBar->m_nWndCnt;
      while ( nPos-- )
      {
         if ( m_pBar->m_PainterWindowList[ nPos ] == this )
         {
            m_pBar->m_nWndCnt--;
            m_pBar->m_PainterWindowList.RemoveAt( nPos );
//          TraceLineI( "TZPainterWindow::OnClose Post cnt: ",
//                      m_pBar->m_nWndCnt );
            nPos = m_pBar->m_nWndCnt;
         }
         else
         if ( m_pBar->m_pActivePainterWindow == 0 )
         {
            // Ensure that some window is active.
            m_pBar->m_pActivePainterWindow =
                                  m_pBar->m_PainterWindowList[ nPos ];
            SetNameForView( m_pBar->m_pActivePainterWindow->m_vDialog,
                            szlTZWINDOW, 0, zLEVEL_TASK );
            SetAllSelStatesForEntityForSet( vTZWINDOWL, pchWindowPage,
                                            0, 1, 0 );
            SetCursorFirstEntityByEntityCsr( vTZWINDOWL, pchWindowPage,
                      m_pBar->m_pActivePainterWindow->m_vDialog,
                                             pchWindowPage, 0 );
            SetSelectStateOfEntityForSet( vTZWINDOWL, pchWindowPage, 1, 1 );
//          TraceLineS( "TZPainterWindow::OnClose1: ", "LoadWindowList" );
            m_pBar->LoadWindowList( );
         }
      }

      if ( m_pBar->m_pActivePainterWindow == 0 )
      {
         zVIEW  vTZWINDOW;

         if ( GetViewByName( &vTZWINDOW, szlTZWINDOW, m_vDialog, zLEVEL_TASK ) > 0 )
            DropNameForView( vTZWINDOW, szlTZWINDOW, m_vDialog, zLEVEL_TASK );

         if ( vTZWINDOWL )
            SetAllSelStatesForEntityForSet( vTZWINDOWL, pchWindowPage, 0, 1, 0 );

//       TraceLineS( "TZPainterWindow::OnClose2: ", "LoadWindowList" );
         m_pBar->LoadWindowList( );
      }

      m_pBar = 0;
   }

   if ( MiValidView( m_vDialog ) )
   {
      DropView( m_vDialog );
      m_vDialog = 0;
   }

   CFrameWnd::OnClose( );
}

#if 0  // all this should be done by OnClose
void
TZPainterWindow::OnNcDestroy( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnNcDestroy", "" );
#endif

   // Detach from the list of painter windows.
   if ( m_pBar )
   {
      AfxMessageBox( "TZPainterWindow::OnNcDestroy" );
      zSHORT nPos = m_pBar->m_nWndCnt;
      while ( nPos-- )
      {
         if ( m_pBar->m_PainterWindowList[ nPos ] == this )
         {
            m_pBar->m_nWndCnt--;
            m_pBar->m_PainterWindowList.RemoveAt( nPos );
            TraceLineI( "TZPainterWindow::OnNcDestroy - ",
                        m_pBar->m_nWndCnt );
            break;
         }
      }

      m_pBar = 0;
   }

   CFrameWnd::OnNcDestroy( );
}
#endif

BOOL
TZPainterWindow::DestroyWindow( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::DestroyWindow", "" );
#endif

   m_pCurrCtrl = 0;
   if ( m_pBar )
   {
      AfxMessageBox( "TZPainterWindow::DestroyWindow" );

      // Delete all the ctrls and the menu bar in the painter window.
      EmptyPainterWindow( );

      // mDeleteInit( m_pPainterClient ); this should happen all by itself
   }

   return( CFrameWnd::DestroyWindow( ) );
}

// Painter window destructor
TZPainterWindow::~TZPainterWindow( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::dtor", "" );
#endif

   if ( mIs_hWnd( m_hWnd ) )
      TraceLineS( "TZPainterWindow dtor - unexpected ", "hWnd" );

   if ( m_pMenu )
      TraceLineS( "TZPainterWindow dtor - unexpected ", "Menu" );

   if ( MiValidView( m_vDialog ) )
   {
      DropView( m_vDialog );
      m_vDialog = 0;
   }
}

// This method empties the Zeidon window of ctrls and removes the menu bar.
void
TZPainterWindow::EmptyPainterWindow( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::EmptyPainterWindow", "" );
#endif

   if ( mIs_hWnd( m_hWnd ) )
   {
      // Turn off redraw until after clear.
      SetRedraw( FALSE );

      // Kill the action bar.
      SetMenu( 0 );
   }

   m_pCurrCtrl = 0;
   mDeleteInit( m_pMenu );

   m_lHScrollMax = 0;
   m_lVScrollMax = 0;

   FinalizeUndoRedo( );

   // Delete all the ctrls in the painter window.
   while ( m_nCtrlCnt )
   {
      Remove( m_CtrlList[ m_nCtrlCnt - 1 ] );

      // Remove calls itself recursively, we don't know how many
      // items are removed from the list in one call to Remove ...
      // m_nCtrlCnt is appropriately maintained.
   }

   // Turn redraw back on.
   if ( mIs_hWnd( m_hWnd ) )
   {
      SetRedraw( TRUE );
      Invalidate( );
   }
}

void
TZPainterWindow::MoveAllSelectedFramesToTop( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::MoveAllSelectedFramesToTop", "" );
#endif

   TZPainterCtrl *pCtrl;
   for ( zSHORT nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) )
      {
         pCtrl->m_pCtrlCover->SetWindowPos( &wndTop, 0, 0, 0, 0,
                                            SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW );
         pCtrl->m_pCtrlCover->m_pSelectCover->SetWindowPos( &wndTop, 0, 0, 0, 0,
                                                            SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW );
      }
   }

   SetFocus( );
}

void
TZPainterWindow::RepaintSelectedCtrls( CWindowDC *pDC )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::RepaintSelectedCtrls", "" );
#endif

   TZSelectCover *pCtrl = m_pPainterClient->m_pHeadSelect;
   TZSelectCover *pCtrlNext;

   m_pPainterClient->m_pHeadSelect = 0;
   while ( pCtrl )
   {
      pCtrlNext = pCtrl->m_pNextSelect;
      pCtrl->m_pNextSelect = 0;
      if ( pCtrl->m_pCtrl->m_pCtrlCover->m_pSelectCover->m_pTracker )
      {
      // TraceRect( "TZPainterWindow::RepaintSelectedCtrls rect", pCtrl->m_pCtrl->m_pCtrlCover->m_pSelectCover->m_pTracker->m_rect );
         pCtrl->m_pCtrl->m_pCtrlCover->m_pSelectCover->m_pTracker->Draw( pDC );
      }

      pCtrl = pCtrlNext;
   }
}

/////////////////////////////////////////////////////////////////////////////
//
//  METHOD: SetOverlapVisibility
//
//  DESCRIPTION: This method sets the visibility of ctrl's that are
//               visible, but are hidden because a sibling ctrl is
//               visible at the same position and size.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT OPERATION
fnCompareCtrlPosSize( CArray<TZPainterCtrl *, TZPainterCtrl *> *pca,
                      zLONG  lLeft,
                      zLONG  lLargest,
                      zPVOID pvSortData )
{
   TZPainterCtrl *pCtrl1 = pca->GetAt( lLeft - 1 );
   TZPainterCtrl *pCtrl2 = pca->GetAt( lLargest - 1 );
   TZPainterCtrl *pCtrlParent;
   TZPainterCtrl *pCtrl;

   if ( pCtrl1 == 0 || pCtrl2 == 0 )
   {
      if ( pCtrl1 == 0 && pCtrl2 == 0 )
         return( 0 );
      else
      if ( pCtrl1 == 0 )
         return( -1 );
      else
   // if ( pCtrl2 == 0 )
         return( 1 );
   }

// zLONG  k = 0;
// if ( zstrncmp( pCtrl1->m_csTag, "Radio", 5 ) == 0 ||
//      zstrncmp( pCtrl2->m_csTag, "Radio", 5 ) == 0 )
// {
//    k++;
// }

   // If one ctrl is an ancestor (parent, grandparent, etc.) of the other
   // ctrl, the one that is an ancestor must be earlier in the order.
   pCtrlParent = pCtrl1->m_pCtrlParent;
   while ( pCtrlParent )
   {
      if ( pCtrlParent == pCtrl2 )
         return( 1 );

      pCtrlParent = pCtrlParent->m_pCtrlParent;
   }

   pCtrlParent = pCtrl2->m_pCtrlParent;
   while ( pCtrlParent )
   {
      if ( pCtrlParent == pCtrl1 )
         return( -1 );

      pCtrlParent = pCtrlParent->m_pCtrlParent;
   }

   // Locate the "youngest" common ancestor and determine position from
   // that ctrl ... return based on position and then size.
   pCtrl = pCtrl1;
   pCtrlParent = 0;
   while ( pCtrl )
   {
      pCtrlParent = pCtrl2;
      while ( pCtrlParent )
      {
         if ( pCtrlParent == pCtrl )
         {
            pCtrl = 0;  // to break out of the outer loop
            break;
         }

         pCtrlParent = pCtrlParent->m_pCtrlParent;
      }

      if ( pCtrl )
         pCtrl = pCtrl->m_pCtrlParent;
   }

   CRect rect1 = pCtrl1->m_rectCtrl;
   pCtrl = pCtrl1;
   while ( pCtrl && pCtrl->m_pCtrlParent &&
           pCtrl->m_pCtrlParent != pCtrlParent )
   {
      pCtrl = pCtrl->m_pCtrlParent;
      rect1.top += pCtrl->m_rectCtrl.top;
      rect1.left += pCtrl->m_rectCtrl.left;
      rect1.bottom += pCtrl->m_rectCtrl.top;
      rect1.right += pCtrl->m_rectCtrl.left;
   }

   CRect rect2 = pCtrl2->m_rectCtrl;
   pCtrl = pCtrl2;
   while ( pCtrl && pCtrl->m_pCtrlParent &&
           pCtrl->m_pCtrlParent != pCtrlParent )
   {
      pCtrl = pCtrl->m_pCtrlParent;
      rect2.top += pCtrl->m_rectCtrl.top;
      rect2.left += pCtrl->m_rectCtrl.left;
      rect2.bottom += pCtrl->m_rectCtrl.top;
      rect2.right += pCtrl->m_rectCtrl.left;
   }

   zSHORT nRC;

   if ( rect1.top < rect2.top )
      nRC = -1;
   else
   if ( rect1.top > rect2.top )
      nRC = 1;
   else
   if ( rect1.left < rect2.left )
      nRC = -1;
   else
   if ( rect1.left > rect2.left )
      nRC = 1;
   else
   if ( rect1.bottom < rect2.bottom )
      nRC = -1;
   else
   if ( rect1.bottom > rect2.bottom )
      nRC = 1;
   else
   if ( rect1.right < rect2.right )
      nRC = -1;
   else
   if ( rect1.right > rect2.right )
      nRC = 1;
   else
   if ( pCtrl1->m_uVisible < pCtrl2->m_uVisible )
      nRC = -1;
   else
   if ( pCtrl1->m_uVisible > pCtrl2->m_uVisible )
      nRC = 1;
   else
   if ( pCtrl1->m_ulZOrder < pCtrl2->m_ulZOrder )
      nRC = -1;
   else
   if ( pCtrl1->m_ulZOrder > pCtrl2->m_ulZOrder )
      nRC = 1;
   else
      nRC = 0;

   return( nRC );
}

void
TZPainterWindow::SetOverlapVisibility( )
{
// return;  // not quite up to snuff yet!

   TZPainterCtrl *pCtrl1;
   TZPainterCtrl *pCtrl2;
   zSHORT        nPos;
   zSHORT        k;

#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::SetOverlapVisibility", "" );

   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl1 = m_CtrlList[ nPos ];
      TraceCtrl( "TZPainterWindow::SetOverlapVisibility", pCtrl1 );
   }
#endif

   HeapSortArray( (CArray<void *, void *> *) &m_CtrlList,
                  (zFARPROC_COMPARE) fnCompareCtrlPosSize,
                  m_nCtrlCnt, "DKS SortData" );

   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl1 = m_CtrlList[ nPos ];
      pCtrl1->m_uVisible &= 0xFF0F;
   }

   for ( nPos = 0; nPos < m_nCtrlCnt - 1; nPos++ )
   {
      pCtrl1 = m_CtrlList[ nPos ];
      for ( k = nPos + 1; k < m_nCtrlCnt; k++ )
      {
         pCtrl2 = m_CtrlList[ k ];
         if ( pCtrl1->m_pCtrlParent == pCtrl2->m_pCtrlParent &&
              pCtrl1->m_rectCtrl == pCtrl2->m_rectCtrl )
         {
         // pCtrl2->m_uVisible |= 0x0010;
            pCtrl2->SetVisibility( 0x0010, 0, 1 );
            SetChildOverlapVisibility( pCtrl2, FALSE );
         // if ( (pCtrl1->m_uVisible & 0x00F0) == 0 )
            {
            // pCtrl1->m_uVisible |= 0x0080;  // visible, exact overlap
               pCtrl1->SetVisibility( 0x0080, 0, 1 );
            }
         }
      }
   }

#ifdef DEBUG_ALL
   zCHAR szMsg[ 256 ];

   TraceLineI( "TZPainterWindow::SetOverlapVisibility cnt: ",
               m_nCtrlCnt );
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl1 = m_CtrlList[ nPos ];
   // while ( pCtrl1 )
      {
      // if ( pCtrl->m_pCtrlParent &&
      //      zstrcmp( pCtrl->m_pCtrlParent->m_csTag, "Candidates" ) == 0 )
      //      zstrcmp( pCtrl1->m_csTag, "ClientActivity" ) == 0 )
         {
      //    pCtrl1 = m_CtrlList[ nPos ];
            sprintf_s( szMsg, zsizeof( szMsg ), " %3d.%s%-32s %-32s%s0x%04x:", nPos + 1,
                      pCtrl1->IsSelected( ) ? "*" : " ",
                      pCtrl1->m_pCtrlParent ?
                                    pCtrl1->m_pCtrlParent->m_csTag : "<null>",
                      pCtrl1->m_csTag,
                      (pCtrl1->m_pWndCtrl && mIs_hWnd( pCtrl1->m_pWndCtrl->m_hWnd )) ? " " : "~",
                      pCtrl1->m_uVisible );
            TraceRect( szMsg, pCtrl1->m_rectCtrl );
         // break;
         }

      // pCtrl1 = pCtrl1->m_pCtrlParent;
      }
   }
#endif
}

void
TZPainterWindow::SetChildOverlapVisibility( TZPainterCtrl *pCtrlParent,
                                            zBOOL bRemove )
{
   TZPainterCtrl *pCtrl;
   zSHORT        nPos;

   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->m_pCtrlParent == pCtrlParent )
      {
         if ( bRemove )
         {
         // pCtrl->m_uVisible &= ~0x0020;
            pCtrl->SetVisibility( 0x0020, 0, -1 );
            if ( pCtrl->m_uVisible & 0x0010 )
               SetChildOverlapVisibility( pCtrl, FALSE );
            else
               SetChildOverlapVisibility( pCtrl, TRUE );
         }
         else
         {
         // pCtrl->m_uVisible |= 0x0020;
            pCtrl->SetVisibility( 0x0020, 0, 1 );
            SetChildOverlapVisibility( pCtrl, FALSE );
         }
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
//
//  METHOD: GenerateTag
//
//  DESCRIPTION: This method takes in a tag prefix and generates a unique
//               tag by suffixing the control def tag with a digit.
void
TZPainterWindow::GenerateTag( zPCHAR pchTagReturn,
                              zLONG lType,
                              zBOOL bUnique )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::GenerateTag", "" );
#endif

   zVIEW       vTZPESRCO;
   TZPainterCtrl *pCtrl;
   zSHORT      nPos;
   zSHORT      nWork;
   zCHAR       szWork[ 6 ];
   CString     csTag;

   if ( pchTagReturn[ 0 ] == 0 )
   {
      if ( lType &&
           GetViewByName( &vTZPESRCO, szlTZPESRCO, m_vDialog, zLEVEL_TASK ) > 0 &&
           SetCursorFirstEntityByInteger( vTZPESRCO, szlControlDef, szlKey, lType, 0 ) == zCURSOR_SET )
      {
         GetStringFromAttribute( pchTagReturn, zTAG_LTH, vTZPESRCO, szlControlDef, szlTag );
      }

      if ( pchTagReturn[ 0 ] == 0 )
      {
         strcpy_s( pchTagReturn, zTAG_LTH, m_pBar->m_PaletteBarItems[ m_pBar->m_uSelectedPaletteItem ].szTag );
      }
   }

   csTag = pchTagReturn;
   if ( bUnique )
   {
      zBOOL bTagFound = FALSE;
      for ( nWork = 1; nWork < 1000; nWork++ )
      {
         _ltoa_s( nWork, szWork, zsizeof( szWork ), 10 );
         csTag = pchTagReturn;
         csTag += szWork;

         // Now make sure that the tag is unique.
         for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
         {
            pCtrl = m_CtrlList[ nPos ];
            bTagFound = FALSE;
//          if ( pCtrl->m_csTag == csTag )
            if ( zstrcmp( pCtrl->m_csTag.GetString(), csTag.GetString() ) == 0 )
            {
               bTagFound = TRUE;
               break;
            }
         }

         if ( bTagFound == FALSE )
            break;
      }
   }

   strcpy_s( pchTagReturn, zTAG_LTH, csTag );
}

// Select a ctrl.
zBOOL
TZPainterWindow::Select( TZPainterCtrl *pCtrlSelect,
                         zBOOL  bClear )        // default is TRUE
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::Select", "" );
#endif

   TZPainterCtrl *pCtrl;
   zBOOL bReturn = FALSE;

   if ( m_pDirectModeCtrl )
   {
      pCtrl = m_pDirectModeCtrl;
      if ( pCtrl )
      {
         CRect     rect;

         pCtrl->m_pCtrlCover->GetClientRect( &rect );
         pCtrl->m_pCtrlCover->ClientToScreen( &rect );
         m_pPainterClient->ScreenToClient( &rect );
      // pCtrl->m_pCtrlCover->ShowWindow( SW_SHOW );
         pCtrl->m_pCtrlCover->
                   SetWindowPos( &CWnd::wndTop, 0, 0, 0, 0,
                                 SWP_NOSIZE | SWP_NOMOVE |
                                 SWP_NOREDRAW | SWP_SHOWWINDOW );

         rect.InflateRect( 4, 4 );
         m_pPainterClient->InvalidateRect( rect );
         m_pDirectModeCtrl = 0;
      }
   }

   if ( bClear )
   {
      for ( zSHORT nPos = 0; nPos < m_nCtrlCnt; nPos++ )
      {
         pCtrl = m_CtrlList[ nPos ];
         if ( pCtrl == pCtrlSelect )
         {
            bReturn = pCtrl->Select( );
         }
         else
         {
            pCtrl->Deselect( );
         }
      }
   }
   else
   if ( pCtrlSelect )
   {
      bReturn = pCtrlSelect->Select( );
//?   pCtrl->m_pCtrlCover->Invalidate( );
//?   pCtrl->m_pCtrlCover->SetWindowPos( &CWnd::wndTop, 0, 0, 0, 0,
//?                                      SWP_NOSIZE | SWP_NOMOVE |
//?                                      SWP_DRAWFRAME | SWP_FRAMECHANGED );
   }

   return( bReturn );
}

// Deselect a ctrl.
zBOOL
TZPainterWindow::Deselect( TZPainterCtrl *pCtrl )
{
   ASSERT( pCtrl );

#ifdef DEBUG_ALL
// TraceLineS( "TZPainterWindow::Deselect", "" );
#endif

   pCtrl->Deselect( );
   return( 0 );
}

// Remove a ctrl and its children (recursively) from the list.
zBOOL
TZPainterWindow::Remove( TZPainterCtrl *pCtrl )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::Remove: ", pCtrl->m_csTag );
#endif

   zSHORT  nPos;

   if ( pCtrl == m_pCurrCtrl )
      m_pCurrCtrl = 0;

   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      if ( pCtrl == m_CtrlList[ nPos ] )
         break;
   }

   if ( nPos < m_nCtrlCnt )
   {
      if ( pCtrl->IsSelected( ) )
      {
         Deselect( pCtrl );
      }

   // m_CtrlList.RemoveAt( nPos );  we are going to let the ctrl dtor do this

      if ( pCtrl->m_nChildren )
      {
         for ( nPos = 0; nPos < m_nCtrlCnt; )
         {
            if ( m_CtrlList[ nPos ]->m_pCtrlParent == pCtrl )
            {
               Remove( m_CtrlList[ nPos ] );
               nPos = 0;

               // When we go recursive, the count is reset appropriately.
            }
            else
               nPos++;
         }
      }

      if ( pCtrl->m_pCtrlParent )
      {
         for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
         {
            if ( pCtrl->m_pCtrlParent == m_CtrlList[ nPos ] )
            {
               if ( pCtrl->m_pCtrlParent->m_nChildren > 0 )
                  pCtrl->m_pCtrlParent->m_nChildren--;
            }
         }
      }

   // m_nCtrlCnt--;  // done by dtor
      delete( pCtrl );
   }

   return( 0 );
}

// Recursive function for painting submenu.
void
PaintRecurseSubOptions( zVIEW vSubMeta,
                        CMenu *pMenu )
{
#ifdef DEBUG_ALL
   TraceLineS( "PaintRecurseSubOptions( zVIEW ", "" );
#endif

   zCHAR   szOptionText[ 256 ];
   zCHAR   szSeparator[ 2 ];
   CMenu   *pSubMenu;
   zSHORT  nRC = zCURSOR_SET;

   // Note that existence of the Option entity has already been determined.
   while ( nRC > zCURSOR_UNCHANGED )        // Loop for each Option entity
   {
      GetStringFromAttribute( szSeparator, zsizeof( szSeparator ), vSubMeta,
                              szlOption, szlSeparator );
      if ( szSeparator[ 0 ] == 'Y' )
         pMenu->AppendMenu( MF_SEPARATOR );

      GetStringFromAttribute( szOptionText, zsizeof( szOptionText ), vSubMeta, szlOption, szlText );
      if ( CheckExistenceOfEntity( vSubMeta, szlOptOpt ) > zCURSOR_UNCHANGED )
      {
         pSubMenu = new CMenu( );
         pSubMenu->CreateMenu( );
         SetViewToSubobject( vSubMeta, szlOptOpt );
         PaintRecurseSubOptions( vSubMeta, pSubMenu );
         ResetViewFromSubobject( vSubMeta );

         pMenu->AppendMenu( MF_POPUP | MF_STRING,
                            (UINT) pSubMenu->Detach( ),
                            szOptionText );
         delete( pSubMenu );
      }
      else
      {
         pMenu->AppendMenu( MF_STRING, zPAINTER_MENUITEM_ID, szOptionText );
      }

      nRC = SetCursorNextEntity( vSubMeta, szlOption, 0 );

   }  // end of:  while ( nRC > zCURSOR_UNCHANGED ) .. Loop for each Option
}

void
TZPainterWindow::PaintActionBar( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::PaintActionBar", "" );
#endif

   // Kill the previous action bar, if any.
   SetMenu( 0 );
   mDeleteInit( m_pMenu );

   if ( MiValidView( m_vDialog ) == FALSE )
      return;

   // If no window to paint, get out.
   if ( (m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) ||
        CheckExistenceOfEntity( m_vDialog, szlDfltMenu ) != zCURSOR_SET )
   {
      return;
   }
   else
   {
      SetCursorFirstEntityByEntityCsr( m_vDialog, szlMenu,
                                       m_vDialog, szlDfltMenu, 0 );
   }

   if ( CheckExistenceOfEntity( m_vDialog, szlOption ) != zCURSOR_SET )
      return;

   // Build and paint the menu.
   zVIEW vSubobject;

   CreateViewFromViewForTask( &vSubobject, m_vDialog, m_vDialog );
   m_pMenu = new CMenu( );
   m_pMenu->CreateMenu( );
   PaintRecurseSubOptions( vSubobject, m_pMenu );
   DropView( vSubobject );

   SetMenu( m_pMenu );
}

//  Used to send a ctrl type a message for a return code as to whether
//  the action being requested is valid.
zLONG
TZPainterWindow::SendCtrlMsg( zSHORT  nMessage,
                              zVIEW   vCtrl,
                              zLONG   lType,         // type from PPE
                              zLONG   lParentType,
                              zBOOL   bPlaceHolder,
                              CRect   *rectNew,
                              zLONG   lZKey,
                              TZPainterCtrl *pCtrl,
                              zLONG   lCtrlID,
                              zLONG   lTabStopNbr,
                              zPCHAR  pchTag,
                              zPCHAR  pchText,
                              CWnd    *pWndParent )
{
#ifdef DEBUG_ALL
   TraceLineI( "TZPainterWindow::SendCtrlMsg: ", nMessage );
#endif

   LPLIBRARY    lpLibrary;
   zVIEW        vTZPESRCO;
   zVIEW        vParent;
   zCONTROLCALL lpfnControl;
   zPCHAR       pchDLL;
   zPCHAR       pchCOP;
   zCHAR        szParentName[ zTAG_LTH ];
   zLONG        lRC;

   // To prevent unrecoverable errors ...
   if ( lType == 0 )
      return( 0 );

   // If the mouse button has been double clicked, go to the appropriate
   // ctrl update window.
   if ( GetViewByName( &vTZPESRCO, szlTZPESRCO, m_vDialog, zLEVEL_TASK ) > 0 &&
        SetCursorFirstEntityByInteger( vTZPESRCO, szlControlDef,
                                       szlKey, lType, 0 ) >= zCURSOR_SET )
   {
      GetAddrForAttribute( &pchDLL, vTZPESRCO,
                           szlControlDef, szlPainterDLL_Name );
      GetAddrForAttribute( &pchCOP, vTZPESRCO,
                           szlControlDef, szlPainterC_OperationName );
      lpLibrary = 0;
      lpfnControl = (zCONTROLCALL)
         GetOperationDynamicCallAddress( vTZPESRCO, &lpLibrary,
                                         pchDLL, pchCOP, 0 );
      if ( lpfnControl )
      {
         lRC = (*lpfnControl)( nMessage, this, lParentType,
                               pWndParent, vCtrl, rectNew, pCtrl,
                               lType, bPlaceHolder, lZKey, lCtrlID, lTabStopNbr,
                               pchTag, pchText );

         // If a ctrl is being painted send a message to the ctrls
         // parent, unless the parent is Window.
         if ( nMessage == zCTRLMSG_CREATE_ZEIDON )
         {
            // Get parent name.
            MiGetParentEntityNameForView( szParentName, vCtrl, "Control" );

            // If parent is not Window (or Page) then send a message.
            if ( ((m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) &&
                  (zstrcmp( szParentName, szlGroupSet ) != 0 &&
                   zstrcmp( szParentName, szlGroup ) != 0 &&
                   zstrcmp( szParentName, szlPage ) != 0)) ||
                 ((m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 &&
                  zstrcmp( szParentName, szlWindow ) != 0) )
            {
               CreateViewFromViewForTask( &vParent, vCtrl, m_vDialog );
               ResetViewFromSubobject( vParent );
               GetAddrForAttribute( &pchDLL, vParent,
                                    szlControlDef, szlPainterDLL_Name );
               GetAddrForAttribute( &pchCOP, vParent, szlControlDef,
                                    szlPainterC_OperationName );
               lpLibrary = 0;
               lpfnControl = (zCONTROLCALL)
                  GetOperationDynamicCallAddress( vTZPESRCO, &lpLibrary,
                                                  pchDLL, pchCOP, 0 );
               if ( lpfnControl )
               {
                  if ( pCtrl && pCtrl->m_pCtrlParent )
                     pCtrl = pCtrl->m_pCtrlParent;
                  else
                     pCtrl = 0;

                  (*lpfnControl)( zCTRLMSG_NOTIFY_PARENT, this,
                                  lParentType, pWndParent,
                                  vCtrl, rectNew, pCtrl,
                                  lType, pCtrl->m_bPlaceHolder,
                                  lZKey, lCtrlID,
                                  lTabStopNbr, pchTag, pchText );
               }

               DropView( vParent );
            }
         }

         return( lRC );
      }
   }
   else
   {
      TraceLineI( "TZPainterWindow::SendCtrlMsg type NOT found - type: ",
                  lType );
      MessageBox( "TZPainterWindow::SendCtrlMsg type NOT found" );
   }

   return( 0 );
}

// Used to paint ctrls from Zeidon object and by PaintToolBoxCtrl
// to paint a new ctrl.
TZPainterCtrl *
TZPainterWindow::PaintCtrl( TZPainterCtrl *pCtrlParent,
                            zCPCHAR cpcEntityName,
                            zVIEW   vCtrl,
                            zLONG   lType,
                            CRect   *prectPaint,
                            zPCHAR  pchTag,
                            zPCHAR  pchText,
                            zLONG   lZKey,
                            zBOOL   bSelect )
{
#ifdef DEBUG_ALL
// TraceLineS( "TZPainterWindow::PaintCtrl", "" );
#endif

   TZPainterCtrl *pCtrl;
   zVIEW         vTZPESRCO;
   CWnd          *pWndParent;
   zLONG         lParentType;
   zLONG         lPosX, lPosY, lTabStopNbr;
   zLONG         lSizeX, lSizeY;
   zCHAR         szWkTag[ 34 ];
   zCHAR         szPlaceHolder[ 2 ];
   zBOOL         bPlaceHolder;
   CRect         rectPaint;
   zCHAR         chEntity;

   // Copy rect values if passed.
   if ( prectPaint )
      rectPaint = *prectPaint;

   chEntity = cpcEntityName[ 0 ];
   if ( chEntity == 'G' && cpcEntityName[ 5 ] )
      chEntity = 'S';

   // Get painting attributes from Zeidon object if they exist and the
   // size has not been overridden.
   lTabStopNbr = 9999;
   if ( vCtrl && lType == 0 )
   {
      if ( chEntity == 'C' )
      {
         if ( SetCursorFirstEntity( vCtrl, szlControlDef, 0 ) == zCURSOR_SET )
         {
            GetIntegerFromAttribute( &lType, vCtrl, szlControlDef, szlKey );
         }
      }
      else
      {
         GetIntegerFromAttribute( &lType, vCtrl, cpcEntityName, "PPE_Type" );
      }

      if ( lZKey == 0 )
      {
         GetIntegerFromAttribute( &lZKey, vCtrl, cpcEntityName, szlZKey );
         if ( lZKey == 0 )
         {
            if ( m_lMaxZKey < 20000 )
               m_lMaxZKey = 20000;

            lZKey = ++m_lMaxZKey;
            SetAttributeFromInteger( vCtrl, cpcEntityName, szlZKey, lZKey );
         }
      }

      GetIntegerFromAttribute( &lPosX, vCtrl, cpcEntityName, szlPSDLG_X );
      GetIntegerFromAttribute( &lPosY, vCtrl, cpcEntityName, szlPSDLG_Y );
      GetIntegerFromAttribute( &lSizeX, vCtrl, cpcEntityName, szlSZDLG_X );
      GetIntegerFromAttribute( &lSizeY, vCtrl, cpcEntityName, szlSZDLG_Y );

      GetAddrForAttribute( &pchTag, vCtrl, cpcEntityName, szlTag );
      GetAddrForAttribute( &pchText, vCtrl, cpcEntityName, szlText );

#if 0
      if ( chEntity == 'S' &&
           zstrcmp( pchTag, "FinancialAcctTransaction" ) == 0 )
      {
         zCHAR szMsg[ 256 ];

         sprintf_s( szMsg, zsizeof( szMsg ), " PX %ld PY %ld SX %ld SY %ld",
                   lPosX, lPosY, lSizeX, lSizeY );
         TraceLineS( "TZPainterWindow::PaintCtrl: FinancialAcctTransaction",
                     szMsg );
      }
#endif

#if 0
      if ( zstrcmp( pchTag, "Rpt_Shape2" ) == 0 )
         ::MessageBox( 0, pchTag, pchTag, MB_OK );
      if ( zstrcmp( pchTag, "Rpt_Shape3" ) == 0 )
         ::MessageBox( 0, pchTag, pchTag, MB_OK );
#endif

#ifdef DEBUG_ALL
      zCHAR szBuffer[ 256 ];
      CRect rect( lPosX, lPosY, lPosX + lSizeX, lPosY + lSizeY );
      strcpy_s( szBuffer, zsizeof( szBuffer ), "TZPainterWindow::PaintCtrl " );
      strcat_s( szBuffer, zsizeof( szBuffer ), pchTag );
      TraceRect( szBuffer, rect );
#endif

      if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      {
         if ( m_lUnit == 0 )
         {
            lPosX = mConvert16thInchToPixelX( lPosX );
            lPosY = mConvert16thInchToPixelY( lPosY );
            lSizeX = mConvert16thInchToPixelX( lSizeX );
            lSizeY = mConvert16thInchToPixelY( lSizeY );
         }
         else
         {
            lPosX = mConvert256thInchToPixelX( lPosX );
            lPosY = mConvert256thInchToPixelY( lPosY );
            lSizeX = mConvert256thInchToPixelX( lSizeX );
            lSizeY = mConvert256thInchToPixelY( lSizeY );
         }

#if 0
         if ( chEntity == 'S' &&
              zstrcmp( pchTag, "FinancialAcctTransaction" ) == 0 )
         {
            zCHAR szMsg[ 256 ];

            sprintf_s( szMsg, zsizeof( szMsg ), " PX %ld PY %ld SX %ld SY %ld",
                      lPosX, lPosY, lSizeX, lSizeY );
            TraceLineS( "TZPainterWindow::PaintCtrl2 FinancialAcctTransaction",
                        szMsg );
            lPosX = mConvertPixelTo256thInchX( lPosX );
            lPosY = mConvertPixelTo256thInchY( lPosY );
            lSizeX = mConvertPixelTo256thInchX( lSizeX );
            lSizeY = mConvertPixelTo256thInchY( lSizeY );

            lPosX = mConvert256thInchToPixelX( lPosX );
            lPosY = mConvert256thInchToPixelY( lPosY );
            lSizeX = mConvert256thInchToPixelX( lSizeX );
            lSizeY = mConvert256thInchToPixelY( lSizeY );

         }
#endif

         if ( chEntity == 'C' )
         {
            if ( pCtrlParent == 0 || pCtrlParent->m_chEntity != 'C' )
               lPosX += m_lLeftMargin - 8;   // 8 for GroupSet + Group indent
         }
         else
         {
            lPosY += m_lTopMargin;
            lPosX = 4;       // GroupSets and Groups are indented 4 each
            lSizeX = m_lLeftMargin + mConvert256thInchToPixelX( m_lRptSizeX );
         }
      }
      else
      {
         zLONG lStyleEx;

         GetIntegerFromAttribute( &lStyleEx, vCtrl,
                                  szlControl, "ExtendedStyle" );

         if ( lStyleEx & zCONTROLX_ABSOLUTE_PIXEL_POS )
         {
         // lPosX = lPosX;
         // lPosY = lPosY;
         }
         else
         {
            if ( m_pBar->m_bUseMapDlgUnits )
            {
               lPosX = mConvertMapDlgToPixelX( lPosX );
               lPosY = mConvertMapDlgToPixelY( lPosY );
            }
            else
            {
               lPosX = mConvertDlgUnitToPixelX( lPosX );
               lPosY = mConvertDlgUnitToPixelY( lPosY );
            }
         }

         if ( lStyleEx & zCONTROLX_ABSOLUTE_PIXEL_SIZE )
         {
         // lSizeX = lSizeX;
         // lSizeY = lSizeY;
         }
         else
         {
            if ( m_pBar->m_bUseMapDlgUnits )
            {
               lSizeX = mConvertMapDlgToPixelX( lSizeX );
               lSizeY = mConvertMapDlgToPixelY( lSizeY );
            }
            else
            {
               lSizeX = mConvertDlgUnitToPixelX( lSizeX );
               lSizeY = mConvertDlgUnitToPixelY( lSizeY );
            }
         }
      }

#ifdef DEBUG_ALL
//    TraceLineI( "TZPainterWindow::PaintCtrl top: ", lPosY );
#endif

      GetIntegerFromAttribute( &lTabStopNbr, vCtrl,
                               cpcEntityName, szlSyncKey );
      if ( lTabStopNbr <= 0 || lTabStopNbr > 9999 )
         lTabStopNbr = 9999;

      if ( lTabStopNbr < 9999 && lTabStopNbr > m_nMaxTabIdNbr )
         m_nMaxTabIdNbr = (zSHORT) lTabStopNbr;

      rectPaint.left   = (zSHORT) lPosX;
      rectPaint.top    = (zSHORT) lPosY;
      rectPaint.right  = (zSHORT) (lPosX + lSizeX);
      rectPaint.bottom = (zSHORT) (lPosY + lSizeY);
   }

   CPoint ptScrollPos = m_pPainterClient->GetDeviceScrollPosition( );

   // Update max synckey if synckey greater than current.
   if ( lZKey > m_lMaxZKey )
      m_lMaxZKey = lZKey;

   if ( pCtrlParent )
   {
      lParentType = pCtrlParent->m_lType;
      pWndParent = pCtrlParent->m_pWndCtrl;
   }
   else
   {
      lParentType = 0;
      pWndParent = m_pPainterClient;
   }

   // If a tag does not exist for the ctrl, generate one.
   if ( pchTag == 0 || pchTag[ 0 ] == 0 )
   {
      szWkTag[ 0 ] = 0;
      GenerateTag( szWkTag, lType );
      pchTag = szWkTag;

      // Assign tag to the ctrl if a Zeidon Control entity exists.
      if ( vCtrl && (m_fWndState & zTZPW_UPDATEABLE) )
      {
         SetAttributeFromString( vCtrl, cpcEntityName, szlTag, szWkTag );
      }
   }

// TraceLineS("Tag is : ", pchTag );
   if ( pchText[ 0 ] == 0 && vCtrl == 0 )
      pchText = pchTag;

// TraceLineI( "CTRLMSG_PAINT IdNbr ", lType );
// TraceRect( "CTRLMSG_PAINT Rect:", rectPaint );

   GetViewByName( &vTZPESRCO, szlTZPESRCO, m_vDialog, /* vCtrl, */ zLEVEL_TASK );
   SetCursorFirstEntityByInteger( vTZPESRCO, szlControlDef, szlKey, lType, 0 );
   GetStringFromAttribute( szPlaceHolder, zsizeof( szPlaceHolder ), vTZPESRCO, szlControlDef, "PlaceHolder" );
   bPlaceHolder = (szPlaceHolder[ 0 ] == 'Y') ? TRUE : FALSE;

   zBOOL bFirstTime = TRUE;
   while ( bFirstTime )
   {
      try
      {
//       TraceLineI( "try items = ", m_nCtrlCnt );
         pCtrl = (TZPainterCtrl *) SendCtrlMsg( zCTRLMSG_CREATE_GUI,
                                                vCtrl, lType,
                                                lParentType,
                                                bPlaceHolder,
                                                &rectPaint, lZKey,
                                                pCtrlParent,
                                                0, lTabStopNbr,
                                                pchTag, pchText,
                                                pWndParent );

         if ( pCtrl == 0 )
            TraceLine( "TZPainterWindow::SendCtrlMsg failed for type: %d   tag: %s   text: %s",
                       lType, pchTag, pchText );

      // TraceLine( "TZPainterWindow::SendCtrlMsg %s for type: %d   tag: %s   text: %s",
      //            (pCtrl == 0) ? "failed" : "successful", lType, pchTag, pchText );

         break;  // we were successful (at least no exceptions)
      }
      catch( CException *e )
      {
         bFirstTime = FALSE;
         pCtrl = 0;

//       TraceLineI( "catch items = ", m_nCtrlCnt );

         // If we have trouble creating a ctrl, we will try removing
         // other painter window(s) to minimize the number of resources
         // utilized by the painter and then retry the ctrl creation.
         TZPainterWindow *pPainterWindow;
         zSHORT nPos;

         while ( m_pBar->m_nWndCnt > 1 )
         {
            for ( nPos = 0; nPos < m_pBar->m_nWndCnt; nPos++ )
            {
               pPainterWindow = m_pBar->m_PainterWindowList[ nPos ];
               if ( pPainterWindow != this )
               {
                  bFirstTime = TRUE;
                  pPainterWindow->SendMessage( WM_CLOSE, 0, 0 );
#if 0
                  pPainterWindow->UpdateZeidonWindow( );
                  pPainterWindow->EmptyPainterWindow( );
                  pPainterWindow->m_pLastSelected = 0;
                  m_pBar->m_pActivePainterWindow = 0;
                  if ( pPainterWindow->m_vDialog )
                  {
                     DropView( pPainterWindow->m_vDialog );
                     pPainterWindow->m_vDialog = 0;
                  }

                  m_pBar->m_nWndCnt--;
                  m_pBar->m_PainterWindowList.RemoveAt( nPos );
                  pPainterWindow->m_pBar = 0;
                  pPainterWindow->DestroyWindow( );
#endif
               }
            }
         }

         if ( bFirstTime == FALSE )
         {
            zCHAR szMsg[ 256 ];

            e->GetErrorMessage( szMsg, zsizeof( szMsg ) );
            MessageSend( m_pBar->m_vSubtask, 0,
                         "Zeidon Dialog", szMsg,
                         zMSGQ_MODAL_ERROR, FALSE );
            pCtrl = 0;
         }
      }
   }

   // If we get here, we attempted to paint a ctrl, add the ctrl to the painter.
   if ( pCtrl )
   {
#if 0
      if ( pCtrl->m_chEntity == 'S' &&
           zstrcmp( pCtrl->m_csTag, "FinancialAcctTransaction" ) == 0 )
      {
         zCHAR szMsg[ 256 ];

         sprintf_s( szMsg, zsizeof( szMsg ), " PX %ld PY %ld SX %ld SY %ld",
                   pCtrl->m_rectCtrl.left, pCtrl->m_rectCtrl.top,
                   pCtrl->m_rectCtrl.right - pCtrl->m_rectCtrl.left,
                   pCtrl->m_rectCtrl.bottom - pCtrl->m_rectCtrl.top );
         TraceLineS( "TZPainterWindow::PaintCtrl3 FinancialAcctTransaction",
                     szMsg );
      }
#endif

      if ( (pCtrl->GetVisibility( )) <= 1 )  // visible or selectable
      {
         if ( pCtrl->m_pCtrlCover == 0 )
         {
            // m_pCtrlCover is set by the TZCtrlCover ctor.
            new TZCtrlCover( this, pCtrl, pchTag );
         }

         if ( pCtrl->m_rectPainter.right > m_lHScrollMax )
            m_lHScrollMax = pCtrl->m_rectPainter.right;

         if ( pCtrl->m_rectPainter.bottom > m_lVScrollMax )
            m_lVScrollMax = pCtrl->m_rectPainter.bottom;

         if ( bSelect )
            pCtrl->Select( );

//       TraceLineI( "Visible ctrl cnt: ", m_nCtrlCnt );
      }
      else
      {
//       TraceLineI( "NOT visible cnt:  ", m_nCtrlCnt );
      }

      if ( vCtrl && pCtrl->m_chEntity == 'C' &&
           SetCursorFirstEntity( vCtrl, szlCtrlCtrl, 0 ) == zCURSOR_SET )
      {
         CRect rectWork;
         SetViewToSubobject( vCtrl, szlCtrlCtrl );
         do
         {
            zLONG lCnt = 0;
            while ( lCnt < 50 && mIs_hWnd( pCtrl->m_pWndCtrl->m_hWnd ) == 0 )
            {
               lCnt++;
               SysWait( 20 );
            }

            if ( mIs_hWnd( pCtrl->m_pWndCtrl->m_hWnd ) == 0 ||
                 PaintCtrl( pCtrl, szlControl, vCtrl, 0, &rectWork, 0, 0 ) == 0 )
            {
               break;
            }

         } while ( SetCursorNextEntity( vCtrl, szlControl, 0 ) == zCURSOR_SET );
         ResetViewFromSubobject( vCtrl );
      }

      return( pCtrl );
   }
   else
   {
      TraceLineI( "Unable to create painter ctrl type: ", lType );
      return( 0 );
   }
}

// Used to erase and paint Zeidon ctrls defined in a dialog window.
void
TZPainterWindow::PaintZeidonCtrls( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::PaintZeidonCtrls", "" );
#endif

   TZPainterCtrl *pCtrl;

   // Delete all the ctrls in the painter window, if any.
   while ( m_nCtrlCnt )
   {
      pCtrl = m_CtrlList[ m_nCtrlCnt - 1 ];
      Remove( pCtrl );
   }

   // If no ctrls to paint, get out.
   if ( MiValidView( m_vDialog ) == FALSE ||
        (((m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) &&
          CheckExistenceOfEntity( m_vDialog, szlPage ) != zCURSOR_SET) ||
         ((m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 &&
          CheckExistenceOfEntity( m_vDialog, szlWindow ) != zCURSOR_SET)) )
   {
      return;
   }

   // Paint all the ctrls.
   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
   {
      TZPainterCtrl *pGroupSetCtrl;
      TZPainterCtrl *pGroupCtrl;

      zSHORT nRC = SetCursorFirstEntity( m_vDialog, szlGroupSet, 0 );
      while ( nRC == zCURSOR_SET )
      {
         pGroupSetCtrl = PaintCtrl( 0, szlGroupSet, m_vDialog,
                                    0, 0, 0, 0 );

         nRC = SetCursorFirstEntity( m_vDialog, szlGroup, 0 );
         while ( pGroupSetCtrl && nRC == zCURSOR_SET )
         {
            pGroupCtrl = PaintCtrl( pGroupSetCtrl,
                                    szlGroup, m_vDialog, 0, 0, 0, 0 );

            // In a report, tab order is ignored, paint according to
            // position.
            OrderEntityForView( m_vDialog, szlControl,
                                "PSDLG_Y A PSDLG_X A" );
            nRC = SetCursorFirstEntity( m_vDialog, szlControl, 0 );
            while ( pGroupCtrl && nRC == zCURSOR_SET )
            {
               if ( PaintCtrl( pGroupCtrl, szlControl,
                               m_vDialog, 0, 0, 0, 0 ) == 0 )
               {
                  return;
               }

               nRC = SetCursorNextEntity( m_vDialog, szlControl, 0 );
            }

            nRC = SetCursorNextEntity( m_vDialog, szlGroup, 0 );
         }

         nRC = SetCursorNextEntity( m_vDialog, szlGroupSet, 0 );
      }
   }
   else
   {
      zSHORT nRC = SetCursorFirstEntity( m_vDialog, szlControl, 0 );
      while ( nRC == zCURSOR_SET )
      {
         if ( PaintCtrl( 0, szlControl, m_vDialog, 0, 0, 0, 0 ) == 0 )
            return;

         nRC = SetCursorNextEntity( m_vDialog, szlControl, 0 );
      }
   }
}

// This method repaints a single Zeidon ctrl after update.
void
TZPainterWindow::RepaintZeidonCtrl( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::RepaintZeidonCtrl", "" );
#endif

   zVIEW         vDialog;
   zBOOL         bSelected;
   zLONG         lZKey;
   zSHORT        nPos;
   TZPainterCtrl *pCtrl;
   CRect         rectWork;

   // Hold on to current select state of ctrl.
   bSelected = 0;

   // Get the view for the ctrl just updated.
   if ( GetViewByName( &vDialog, szlTZCONTROL, m_vDialog, zLEVEL_TASK ) <= 0 )
      vDialog = m_vDialog;

   // Create a work view for repainting.
   CreateViewFromViewForTask( &vDialog, vDialog, m_vDialog );

   // Reset view to top ctrl.
   while ( ResetViewFromSubobject( vDialog ) == 0 )
   {
   }

   // Repaint the requested ctrl.
   GetIntegerFromAttribute( &lZKey, vDialog, szlControl, szlZKey );

   // Find the ctrl and delete it if it exists.
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->m_lZKey == lZKey )
      {
         bSelected = pCtrl->IsSelected( );
         Remove( pCtrl );
         break;
      }
   }

   if ( PaintCtrl( 0, szlControl, vDialog, 0,
                   &rectWork, 0, 0, lZKey, bSelected ) )
   {
      ValidateCtrlTags( );
   }

   // Drop the work view created.
   DropView( vDialog );
}

// This method clears out the current painter window and repaints based
// on the current view.
void
TZPainterWindow::PaintZeidonWindow( zBOOL bReset )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::PaintZeidonWindow", "" );
#endif

   zPCHAR pchWindowPage;

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      pchWindowPage = szlPage;
   else
      pchWindowPage = szlWindow;

   // Make sure there is something to do.
   while ( ResetViewFromSubobjectWithoutError( m_vDialog ) == 0 )
   {
   }

   if ( MiValidView( m_vDialog ) == FALSE ||
        CheckExistenceOfEntity( m_vDialog, pchWindowPage ) != zCURSOR_SET )
   {
      return;
   }

   zBOOL bLock = LockWindowUpdate( );  // SetRedraw( FALSE );
   m_pPainterClient->m_bPaintWindow = TRUE;

   // Set the updateable indicator.
   if ( MiGetUpdateForView( m_vDialog ) > 0 )
      m_fWndState |= zTZPW_UPDATEABLE;
   else
      m_fWndState &= ~zTZPW_UPDATEABLE;

   // Make sure the window is empty first!  Then guarantee position on
   // Window/Page.
   EmptyPainterWindow( );
   while ( ResetViewFromSubobject( m_vDialog ) == 0 )
   {
   }

   GetIntegerFromAttribute( &m_lZKey, m_vDialog, pchWindowPage, szlZKey );

   zLONG lPosX;
   zLONG lPosY;
   zLONG lSizeX;
   zLONG lSizeY;

   // Size and Position the window based on the window/report attributes.
   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
   {
      if ( bReset || m_lLeftMargin < 8 ||
           m_lLeftMargin > mConvert256thInchToPixelX( 1024 ) ) // four inches
      {
         m_lLeftMargin = GetProfileNbr( m_vDialog, "Design",
                                        "_Report", "_Painter", "LeftMargin" );
      }

      // Set sizes ... report instance records X and Y sizes in terms of
      // sixteenths of an inch.
      m_lTopMargin = mConvert256thInchToPixelY( 96 );    // 3/8 inch
      if ( m_lLeftMargin < 8 ||
           m_lLeftMargin > mConvert256thInchToPixelX( 1024 ) )  // four inches
      {
         m_lLeftMargin = mConvert256thInchToPixelX( 512 );  // two inches
      }

      lPosX = 1;
      lPosY = 1;
      if ( bReset || m_lRptSizeX == 0 || m_lRptSizeY == 0 )
      {
         m_lRptSizeX = 2176;  // 8 1/2 inches == 2176 256ths of an inch
         m_lRptSizeY = 2816;  // 11 inches == 2816 256ths of an inch

         GetIntegerFromAttribute( &lSizeX, m_vDialog, pchWindowPage, szlSizeX );
         GetIntegerFromAttribute( &lSizeY, m_vDialog, pchWindowPage, szlSizeY );
         if ( m_lUnit == 0 )
         {
            lSizeX <<= 4;  // convert from sixteenths to 256ths
            lSizeY <<= 4;  // convert from sixteenths to 256ths
         }

         if ( lSizeX == 0 )
         {
            m_lRptSizeX = 2176;  // 8 1/2 inches == 2176 256ths of an inch
         }
         else
         {
            m_lRptSizeX = lSizeX;
         }

         if ( m_lPrintFlags & zREPORT_LANDSCAPE )
         {
            if ( m_lRptSizeX < 2816 )
               m_lRptSizeX = 2816;  // 11 inches == 2816 256ths of an inch
         }
         else
         {
            if ( m_lRptSizeX <= 2176 )
               m_lRptSizeX = 2176;  // 8 1/2 inches == 2176 256ths of an inch
            else
            if ( m_lRptSizeX > 16384 )
               m_lRptSizeX = 16384;  // 16384 = 64 inches
         }

         lSizeX = (2 * m_lLeftMargin) + mConvert256thInchToPixelX( m_lRptSizeX );

         if ( lSizeY == 0 )
         {
            lSizeY = m_lTopMargin + mConvert256thInchToPixelY( m_lRptSizeY );
         }
         else
         {
            lSizeY = m_lTopMargin + mConvert256thInchToPixelY( lSizeY );
         }
      }
      else
      {
         lSizeX = m_lRptSizeX;
         lSizeY = m_lRptSizeY;
      }

      zLONG  k;
      k = GetSystemMetrics( SM_CXSCREEN ) - GetSystemMetrics( SM_CXVSCROLL );
      if ( Attr.X + lSizeX > k )
         lSizeX = k - Attr.X;

      k = GetSystemMetrics( SM_CYSCREEN ) - GetSystemMetrics( SM_CYHSCROLL );
      if ( Attr.Y + lSizeY > k )
         lSizeY = k - Attr.Y;

      // Set scroll units to 1/2 inch in X direction ... 1 inch in Y direction.
      if ( bReset )
      {
         m_lScrollUnitsX = mConvert256thInchToPixelX( 128 );
         m_lScrollUnitsY = mConvert256thInchToPixelY( 256 );
      }
   }
   else
   {
      GetIntegerFromAttribute( &lPosX, m_vDialog, pchWindowPage, szlPSDLG_X );
      GetIntegerFromAttribute( &lPosY, m_vDialog, pchWindowPage, szlPSDLG_Y );
      GetIntegerFromAttribute( &lSizeX, m_vDialog, pchWindowPage, szlSZDLG_X );

      // If the window size has not been set by a WM_WINDOWPOSCHANGED message,
      // then force the window size to be set.
      if ( m_uSizeX == 0 && HIWORD( lSizeX ) == 0 )
         m_uSizeX = 1;

      GetIntegerFromAttribute( &lSizeY, m_vDialog, pchWindowPage, szlSZDLG_Y );
      if ( m_pBar->m_bUseMapDlgUnits )
      {
         lPosX = mConvertMapDlgToPixelX( lPosX );
         lPosY = mConvertMapDlgToPixelY( lPosY );
         lSizeX = mConvertMapDlgToPixelX( LOWORD( lSizeX ) );
         lSizeY = mConvertMapDlgToPixelY( LOWORD( lSizeY ) );
      }
      else
      {
         lPosX = mConvertDlgUnitToPixelX( lPosX );
         lPosY = mConvertDlgUnitToPixelY( lPosY );
         lSizeX = mConvertDlgUnitToPixelX( LOWORD( lSizeX ) );
         lSizeY = mConvertDlgUnitToPixelY( LOWORD( lSizeY ) );
      }

      m_lScrollUnitsX = 32;
      m_lScrollUnitsY = 16;
   }

   m_fWndState &= ~zTZPW_INITIALIZING;

// zCHAR szBuffer[ 64 ];
// strcpy_s( szBuffer, zsizeof( szBuffer ), m_csWndTag );
// strcat_s( szBuffer, zsizeof( szBuffer ), " lSizeY: " );
// TraceLineI( "TZPainterWindow::PaintZeidonWindow lSizeX: ", lSizeX );
// TraceLineI( szBuffer, lSizeY );
   SetWindowPos( 0, lPosX, lPosY, lSizeX, lSizeY, SWP_NOMOVE | SWP_NOZORDER );

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
   {
      zCHAR szCaption[ 256 ];

      strcpy_s( szCaption, zsizeof( szCaption ), "Report - " );
      GetStringFromAttribute( szCaption + 9, zsizeof( szCaption ) - 9, m_vDialog, pchWindowPage, szlTag );
      SetWindowText( szCaption );
      GetIntegerFromAttribute( &m_lReportTextSize, m_vDialog, "Report", "ReportTextSize" );
      if ( m_lUnit == 0 )
         m_lReportTextSize *= 10;
   }
   else
   {
      zCHAR szCaption[ 256 ];

      // Set the Caption for the window.
      GetStringFromAttribute( szCaption, zsizeof( szCaption ), m_vDialog, pchWindowPage, szlTag );
      strcat_s( szCaption, zsizeof( szCaption ), " - " );
      GetStringFromAttribute( szCaption + 64, zsizeof( szCaption ) - 64, m_vDialog, pchWindowPage, szlCaption );
      strcat_s( szCaption, zsizeof( szCaption ), szCaption + 64 );
      SetWindowText( szCaption );

      // Now that sizing and positioning are out of the way, paint the action bar for the window.
      PaintActionBar( );
   }

   // Now paint the window ctrls.
   m_pPainterClient->ScrollToPosition( CPoint( 0, 0 ) );
   PaintZeidonCtrls( );

   TZPainterCtrl *pCtrl;
   for ( zSHORT nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
//    TraceLineX( "  ======> list ctrl ", (zLONG) pCtrl );
      pCtrl = m_CtrlList[ nPos ];
      pCtrl->EndPaint( );
   }

   m_pPainterClient->m_bPaintWindow = FALSE;

   CRect rect;

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
   {
      m_pPainterClient->AdjustGroupSets( );
      if ( m_pPainterClient->m_pRuler &&
           mIs_hWnd( m_pPainterClient->m_pRuler->m_hWnd ) )
      {
         m_pPainterClient->m_pRuler->Invalidate( 0 );
      }

      WINDOWPLACEMENT wp;
      zPCHAR pchTag;

      GetAddrForAttribute( &pchTag, m_vDialog, szlReport, szlTag );

      if ( ReadWindowPlacement( m_vDialog, "Design",
                                pchTag, m_csWndTag, &wp ) &&
           CheckWindowPos( &wp ) )
      {
      // TraceRect( "TZPainterWindow::PaintZeidonWindow wp.rect",
      //            wp.rcNormalPosition );

         SetWindowPlacement( &wp );
         rect = wp.rcNormalPosition;
      }
      else
         GetClientRect( rect );

      SetActiveWindow( );
      m_pPainterClient->SetScrollSizes( MM_TEXT,
                                        CSize( m_lHScrollMax + 200,
                                               m_lVScrollMax + 200 ),
                                        CSize( rect.right, rect.bottom ),
                                        CSize( m_lScrollUnitsX,
                                               m_lScrollUnitsY ) );
   }
   else
   {
      if ( m_pBar->m_fState & zTZCB_SCROLLBARS )
      {
         GetClientRect( rect );
         m_pPainterClient->SetScrollSizes( MM_TEXT,
                                           CSize( m_lHScrollMax + 200,
                                                  m_lVScrollMax + 200 ),
                                           CSize( rect.right, rect.bottom ),
                                           CSize( m_lScrollUnitsX,
                                                  m_lScrollUnitsY ) );
      }
      else
      {
         m_pPainterClient->SetScrollSizes( MM_TEXT, CSize( 0, 0 ) );
      }
   }

   zLONG lScrollX;
   zLONG lScrollY;

   if ( bReset )
   {
      lScrollX = GetProfileNbr( m_vDialog, "Design",
                                m_csDlgTag, m_csWndTag, "ScrollX" );
      lScrollY = GetProfileNbr( m_vDialog, "Design",
                                m_csDlgTag, m_csWndTag, "ScrollY" );
      if ( lScrollY < m_lTopMargin )
         lScrollY = 0;
   }
   else
   {
      lScrollX = 0;
      lScrollY = 0;
   }

   m_pPainterClient->ScrollToPosition( CPoint( lScrollX, lScrollY ) );

   if ( (m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) && m_lUnit == 0 )
      UpdateZeidonWindow( );

   if ( bLock )
      UnlockWindowUpdate( );  // SetRedraw( TRUE );

   SetOverlapVisibility( );

// TraceLineS( "TZPainterWindow::PaintZeidonWindow", " Invalidate" );
// m_pPainterClient->Invalidate( TRUE );
// ::MessageBox( 0, "TZPainterWindow", "After Invalidate", MB_OK );
}

// This method updates the Controls in the Zeidon Window entity from the
// painter's TZPainterCtrl objects.
void
TZPainterWindow::UpdateZeidonWindow( )
{
#ifdef DEBUG_ALL
// TraceLineS( "TZPainterWindow::UpdateZeidonWindow", "" );
#endif

   zVIEW   vCtrl;
   TZPainterCtrl *pCtrl;
   TZPainterCtrl *pCtrlParent;
   zLONG   lPosX, lPosY, lSizeX, lSizeY;
   zPCHAR  pchWindowPage;
   zPCHAR  pchEntity;

   if ( MiValidView( m_vDialog ) == FALSE )
      return;

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
   {
      pchWindowPage = szlPage;
      if ( m_lUnit == 0 )
      {
         m_lUnit = zTZPTR_256THS_INCH;

         SetAttributeFromInteger( m_vDialog, szlReport, "Unit", m_lUnit );
         SetAttributeFromInteger( m_vDialog, szlReport,
                                  "ReportTextSize", m_lReportTextSize );
         GetIntegerFromAttribute( &lSizeX, m_vDialog, pchWindowPage, szlSizeX );
         GetIntegerFromAttribute( &lSizeY, m_vDialog, pchWindowPage, szlSizeY );
         lSizeX <<= 4;  // convert from sixteenths to 256ths
         lSizeY <<= 4;  // convert from sixteenths to 256ths
         SetAttributeFromInteger( m_vDialog, pchWindowPage, szlSizeX, lSizeX );
         SetAttributeFromInteger( m_vDialog, pchWindowPage, szlSizeY, lSizeY );
      }
   }
   else
   {
      pchWindowPage = szlWindow;
   }

   // Make sure there is something to do.
   while ( ResetViewFromSubobject( m_vDialog ) == 0 )
   {
   }

   if ( (m_fWndState & zTZPW_UPDATEABLE) == 0 ||
        CheckExistenceOfEntity( m_vDialog, pchWindowPage ) != zCURSOR_SET )
   {
      return;
   }

   FinalizeUndoRedo( );
   CreateViewFromViewForTask( &vCtrl, m_vDialog, m_vDialog );

   // Make an initial pass and set the parent tabbing ID's to the lowest of
   // the child tab ids so tabbing is as close to what was defined as possible.
   zSHORT nPos;
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      pCtrlParent = pCtrl->m_pCtrlParent;
      while ( pCtrlParent )
      {
         if ( pCtrlParent->m_nTabStopNbr > pCtrl->m_nTabStopNbr )
            pCtrlParent->m_nTabStopNbr = pCtrl->m_nTabStopNbr;

         pCtrlParent = pCtrlParent->m_pCtrlParent;
      }
   }

   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      lPosX = pCtrl->m_rectCtrl.left;
      lPosY = pCtrl->m_rectCtrl.top;
      lSizeX = pCtrl->m_rectCtrl.right - pCtrl->m_rectCtrl.left;
      lSizeY = pCtrl->m_rectCtrl.bottom - pCtrl->m_rectCtrl.top;

#if 0
      if ( pCtrl->m_chEntity == 'S' &&
           zstrcmp( pCtrl->m_csTag, "FinancialAcctTransaction" ) == 0 )
      {
         zCHAR szMsg[ 256 ];

         sprintf_s( szMsg, zsizeof( szMsg ), " PX %ld PY %ld SX %ld SY %ld",
                   lPosX, lPosY, lSizeX, lSizeY );
         TraceLineS( "TZPainterWindow::UpdateZeidonWindow: FinancialAcctTransaction",
                     szMsg );
      }
#endif

      // Position on the ctrl in the Zeidon object, note that this will
      // automatically create the ctrl if necessary.
      pCtrl->PositionOnZeidonCtrl( vCtrl );

      if ( pCtrl->m_chEntity == 'C' )
      {
         pchEntity = szlControl;
         if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
         {
            if ( pCtrl->m_pCtrlParent &&
                 pCtrl->m_pCtrlParent->m_chEntity == 'G' )
            {
               lPosX -= m_lLeftMargin - 8;   // 8 for GroupSet + Group indent
            }

            lPosX = mConvertPixelTo256thInchX( lPosX );
            lPosY = mConvertPixelTo256thInchY( lPosY );
            lSizeX = mConvertPixelTo256thInchX( lSizeX );
            lSizeY = mConvertPixelTo256thInchY( lSizeY );
         }
         else
         {
            zLONG lStyleEx;

            GetIntegerFromAttribute( &lStyleEx, vCtrl,
                                     szlControl, "ExtendedStyle" );

            if ( lStyleEx & zCONTROLX_ABSOLUTE_PIXEL_POS )
            {
            // lPosX = lPosX;
            // lPosY = lPosY;
            }
            else
            {
               if ( m_pBar->m_bUseMapDlgUnits )
               {
                  lPosX = mConvertPixelToMapDlgX( lPosX );
                  lPosY = mConvertPixelToMapDlgY( lPosY );
               }
               else
               {
                  lPosX = mConvertPixelToDlgUnitX( lPosX );
                  lPosY = mConvertPixelToDlgUnitY( lPosY );
               }
            }

            if ( lStyleEx & zCONTROLX_ABSOLUTE_PIXEL_SIZE )
            {
            // lSizeX = lSizeX;
            // lSizeY = lSizeY;
            }
            else
            {
               if ( m_pBar->m_bUseMapDlgUnits )
               {
                  lSizeX = mConvertPixelToMapDlgX( lSizeX );
                  lSizeY = mConvertPixelToMapDlgY( lSizeY );
               }
               else
               {
                  lSizeX = mConvertPixelToDlgUnitX( lSizeX );
                  lSizeY = mConvertPixelToDlgUnitY( lSizeY );
               }
            }
         }
      }
      else
      {
         lPosX = 0;
         lPosY -= m_lTopMargin;
         lPosY =  mConvertPixelTo256thInchY( lPosY );
         lSizeX = m_lRptSizeX;  // X report size in 256ths of an inch
         lSizeY = mConvertPixelTo256thInchY( lSizeY );

         if ( pCtrl->m_chEntity == 'G' )
            pchEntity= szlGroup;
         else
//       if ( pCtrl->m_chEntity == 'S' )
            pchEntity= szlGroupSet;
      }

#ifdef DEBUG_ALL
      zCHAR szBuffer[ 256 ];
      CRect rect( lPosX, lPosY, lPosX + lSizeX, lPosY + lSizeY );
      strcpy_s( szBuffer, zsizeof( szBuffer ), "TZPainterWindow::UpdateZeidonWindow " );
      strcat_s( szBuffer, zsizeof( szBuffer ), pCtrl->m_csTag );
      TraceRect( szBuffer, rect );
      TraceLineI( "TZPainterWindow::UpdateZeidonWindow top: ",
                  pCtrl->m_rectCtrl.top );

      if ( pCtrl->m_chEntity == 'S' &&
           zstrcmp( pCtrl->m_csTag, "FinancialAcctTransaction" ) == 0 )
      {
         zCHAR szMsg[ 256 ];

         sprintf_s( szMsg, zsizeof( szMsg ), " PX %ld PY %ld SX %ld SY %ld",
                   lPosX, lPosY, lSizeX, lSizeY );
         TraceLineS( "TZPainterWindow::UpdateZeidonWindow2 FinancialAcctTransaction",
                     szMsg );
      }
#endif

      SetAttributeFromInteger( vCtrl, pchEntity, szlPSDLG_X, lPosX );
      SetAttributeFromInteger( vCtrl, pchEntity, szlPSDLG_Y, lPosY );
      SetAttributeFromInteger( vCtrl, pchEntity, szlSZDLG_X, lSizeX );
      SetAttributeFromInteger( vCtrl, pchEntity, szlSZDLG_Y, lSizeY );
      SetAttributeFromInteger( vCtrl, pchEntity, szlSyncKey,
                               pCtrl->m_nTabStopNbr );
      pCtrl->WritePersistProperties( );   // uncommented TMV 2001.12.03

      // If this ctrl has a parent and this is the last ctrl in
      // the ctrl list who has this parent, sort this ctrl and
      // its twins under the parent object.
      if ( pCtrl->m_pCtrlParent &&
           pCtrl->m_pCtrlParent->m_chEntity == 'C' )
      {
         // If no more children of this parent remain in the list, sort
         // the Zeidon subctrls now.
         zSHORT        nPos2;
         TZPainterCtrl *pCtrl2;
         for ( nPos2 = nPos + 1; nPos2 < m_nCtrlCnt; nPos2++ )
         {
            pCtrl2 = m_CtrlList[ nPos2 ];
            if ( pCtrl2->m_pCtrlParent == pCtrl->m_pCtrlParent )
            {
               nPos2 = nPos;   // Flag that another child found
               break;
            }
         }

         // If no later child found, sort the subctrls now.
         if ( nPos2 >= m_nCtrlCnt )
         {
            ResetViewFromSubobject( vCtrl );
            OrderEntityForView( vCtrl, szlCtrlCtrl,
                                "SyncKey A PSDLG_Y A PSDLG_X A" );
//          zgSortEntityWithinParent( zASCENDING, vCtrl,
//                                    szlCtrlCtrl, szlPSDLG_Y, szlPSDLG_X );
         }
      }
   }

   // Get back to the top level view.
   while ( ResetViewFromSubobject( vCtrl ) == 0 )
   {
   }

   // Now that the window has been updated, sort all the ctrls
   // in ascending order.
   OrderEntityForView( vCtrl, szlControl, "SyncKey A PSDLG_Y A PSDLG_X A" );

   // Drop the temporary ctrl view.
   DropView( vCtrl );
}

// This method sets the position of the window in the Zeidon Object based
// on the current position of the window on the screen.
void
TZPainterWindow::SetZeidonWindowPosition( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::SetZeidonWindowPosition", "" );
#endif

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      return;

   if ( MiValidView( m_vDialog ) )
   {
      if ( OperatorPrompt( m_pBar->m_pZSubtask->m_vDialog,
                           "Reposition Window",
                           "OK to reposition Window?", 0, zBUTTONS_YESNO,
                           zRESPONSE_YES, 0 ) == zRESPONSE_YES )
      {
         CRect  rectWindow;
         zLONG  lPosX;
         zLONG  lPosY;

         GetWindowRect( rectWindow );
         if ( m_pBar->m_bUseMapDlgUnits )
         {
            lPosX = mConvertPixelToMapDlgX( rectWindow.left );
            lPosY = mConvertPixelToMapDlgY( rectWindow.top );
         }
         else
         {
            lPosX = mConvertPixelToDlgUnitX( rectWindow.left );
            lPosY = mConvertPixelToDlgUnitY( rectWindow.top );
         }

         SetAttributeFromInteger( m_vDialog, szlWindow, szlPSDLG_X, lPosX );
         SetAttributeFromInteger( m_vDialog, szlWindow, szlPSDLG_Y, lPosY );
         SetDIL_Text( );
      }
   }
}

// This method moves the window to the position as defined in the
// Zeidon object.
void
TZPainterWindow::ShowZeidonWindowPosition( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::ShowZeidonWindowPosition", "" );
#endif

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      return;

   if ( MiValidView( m_vDialog ) )
   {
      zLONG lPosX;
      zLONG lPosY;

      GetIntegerFromAttribute( &lPosX, m_vDialog, szlWindow, szlPSDLG_X );
      GetIntegerFromAttribute( &lPosY, m_vDialog, szlWindow, szlPSDLG_Y );
      if ( m_pBar->m_bUseMapDlgUnits )
      {
         lPosX = mConvertMapDlgToPixelX( lPosX );
         lPosY = mConvertMapDlgToPixelY( lPosY );
      }
      else
      {
         lPosX = mConvertDlgUnitToPixelX( lPosX );
         lPosY = mConvertDlgUnitToPixelY( lPosY );
      }

      SetWindowPos( 0, lPosX, lPosY, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
   }
}

// This method displays the information about the selected ctrl in
// the DIL line.
void
TZPainterWindow::SetDIL_Text( TZPainterCtrl *pCtrl,
                              zBOOL bPosOnly )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::SetDIL_Text", "" );
#endif

   zLONG   lWork;
   zCHAR   szDilMsg[ 1024 ];
   zPCHAR  pchAttr;
   zPCHAR  pchEntity;
   zSHORT  nLth;

   // If there is no painter or if we are within AdjustGroupSets ... return.
   if ( m_pBar == 0 || m_pPainterClient->m_nMultiMoveSize > 1 )
      return;

   szDilMsg[ 0 ] = 0;
   if ( pCtrl == 0 && m_nSelectCnt )
      pCtrl = m_pLastSelected;

   if ( pCtrl )
   {
      zVIEW vDialog;

      CreateViewFromViewForTask( &vDialog, m_vDialog, m_vDialog );
      if ( pCtrl->m_lZKey == 0 ||
           pCtrl->PositionOnZeidonCtrl( vDialog ) == 0 )
      {
         if ( vDialog )
         {
            DropView( vDialog );
            vDialog = 0;
         }
      }

      if ( pCtrl->m_chEntity == 'C' )
      {
         pchEntity = szlControl;
      }
      else
      if ( pCtrl->m_chEntity == 'G' )
      {
         pchEntity = szlGroup;
      }
      else
//    if ( pCtrl->m_chEntity == 'S' )
      {
         pchEntity = szlGroupSet;
      }

      if ( bPosOnly == FALSE )
      {
         strcpy_s( szDilMsg, zsizeof( szDilMsg ), pchEntity );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), ": " );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), pCtrl->m_csTag );
      // if ( pCtrl->m_lZKey && pCtrl->PositionOnZeidonCtrl( vDialog ) )
         if ( vDialog )
         {
            GetAddrForAttribute( &pchAttr, vDialog, pchEntity, szlText );
            if ( pchAttr[ 0 ] )
            {
               strcat_s( szDilMsg, zsizeof( szDilMsg ), ".." );
               strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );
            }

            if ( pCtrl->m_chEntity == 'C' )
            {
               if ( CheckExistenceOfEntity( vDialog, "EventAct" ) == 0 )
               {
                  GetIntegerFromAttribute( &lWork, vDialog, "EventAct", "Type" );
                  nLth = (zSHORT) zstrlen( szDilMsg );
                  szDilMsg[ nLth++ ] = ' ';
                  szDilMsg[ nLth++ ] = '[';
                  GetStringFromAttribute( szDilMsg + nLth, zsizeof( szDilMsg ) - nLth, vDialog, "EventAct", "Tag" );
                  nLth = (zSHORT) zstrlen( szDilMsg );
                  szDilMsg[ nLth++ ] = ']';
                  szDilMsg[ nLth++ ] = ' ';
                  strcpy_s( szDilMsg + nLth, zsizeof( szDilMsg ) - nLth, GetActionString( lWork ) );

                  GetAddrForAttribute( &pchAttr, vDialog, "EventAct", "DialogName" );    // borrow pointers for
                  GetAddrForAttribute( &pchEntity, vDialog, "EventAct", "WindowName" );  // Dialog and Window
                  if ( pchEntity[ 0 ] )  // Window
                  {
                     nLth = (zSHORT) zstrlen( szDilMsg );
                     sprintf_s( szDilMsg + nLth, zsizeof( szDilMsg ) - nLth, " ==> %s.%s", pchAttr, pchEntity );
                  }
               }
            }
         }

         MB_SetMessage( m_pBar->m_vSubtask, 1, szDilMsg );
      }

   // TraceRect( "TZPainterWindow::SetDIL_Text rect", pCtrl->m_rectCtrl );
      strcpy_s( szDilMsg, zsizeof( szDilMsg ), "Pos(" );

      if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      {
         lWork = mConvertPixelTo256thInchX( pCtrl->m_rectCtrl.left );
         if ( pCtrl->m_chEntity == 'C' )
            lWork -= mConvertPixelTo256thInchX( m_lLeftMargin - 8 );   // 8 for GroupSet + Group indent

         ltoa( lWork, szDilMsg + 90, 10 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
         lWork = mConvertPixelTo256thInchY( pCtrl->m_rectCtrl.top );
         ltoa( lWork, szDilMsg + 90, 10 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );

         strcat_s( szDilMsg, zsizeof( szDilMsg ), "), Size(" );
         lWork = mConvertPixelTo256thInchX( (pCtrl->m_rectCtrl.right -
                                             pCtrl->m_rectCtrl.left) );
         ltoa( lWork, szDilMsg + 90, 10 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
         lWork = mConvertPixelTo256thInchY( (pCtrl->m_rectCtrl.bottom - pCtrl->m_rectCtrl.top) );
         ltoa( lWork, szDilMsg + 90, 10 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
      }
      else
      {
         if ( m_pBar->m_bUseMapDlgUnits )
            lWork = mConvertPixelToMapDlgX( pCtrl->m_rectCtrl.left );
         else
            lWork = mConvertPixelToDlgUnitX( pCtrl->m_rectCtrl.left );

         ltoa( lWork, szDilMsg + 90, 10 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
         if ( m_pBar->m_bUseMapDlgUnits )
            lWork = mConvertPixelToMapDlgY( pCtrl->m_rectCtrl.top );
         else
            lWork = mConvertPixelToDlgUnitY( pCtrl->m_rectCtrl.top );

         ltoa( lWork, szDilMsg + 90, 10 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), "), Size(" );
         if ( m_pBar->m_bUseMapDlgUnits )
            lWork = mConvertPixelToMapDlgX( (pCtrl->m_rectCtrl.right - pCtrl->m_rectCtrl.left) );
         else
            lWork = mConvertPixelToDlgUnitX( (pCtrl->m_rectCtrl.right - pCtrl->m_rectCtrl.left) );

         ltoa( lWork, szDilMsg + 90, 10 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
         if ( m_pBar->m_bUseMapDlgUnits )
            lWork = mConvertPixelToMapDlgY( (pCtrl->m_rectCtrl.bottom - pCtrl->m_rectCtrl.top) );
         else
            lWork = mConvertPixelToDlgUnitY( (pCtrl->m_rectCtrl.bottom - pCtrl->m_rectCtrl.top) );

         ltoa( lWork, szDilMsg + 90, 10 );
         strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
      }

   // TraceLineS( "TZPainterWindow::SetDIL_Text msg: ", szDilMsg );
      strcat_s( szDilMsg, zsizeof( szDilMsg ), ")" );
      MB_SetMessage( m_pBar->m_vSubtask, 2, szDilMsg );
      if ( bPosOnly == FALSE && pCtrl->m_chEntity == 'C' )
      {
         strcpy_s( szDilMsg, zsizeof( szDilMsg ), "Map(" );
      // if ( pCtrl->m_lZKey )
         if ( vDialog )
         {
            if ( CheckExistenceOfEntity( vDialog, szlCtrlMapER_Attribute ) == zCURSOR_SET )
            {
               GetAddrForAttribute( &pchAttr, vDialog, szlCtrlMapView, szlName );
               if ( pchAttr == 0 || pchAttr[ 0 ] == 0 )
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), szlNULL );
               else
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );

               strcat_s( szDilMsg, zsizeof( szDilMsg ), "." );
               GetAddrForAttribute( &pchAttr, vDialog, szlCtrlMapRelatedEntity, szlName );
               if ( pchAttr == 0 || pchAttr[ 0 ] == 0 )
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), szlNULL );
               else
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );

               strcat_s( szDilMsg, zsizeof( szDilMsg ), "." );
               GetAddrForAttribute( &pchAttr, vDialog, szlCtrlMapER_Attribute, szlName );
               if ( pchAttr == 0 || pchAttr[ 0 ] == 0 )
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), szlNULL );
               else
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );
            }
            else
            if ( CheckExistenceOfEntity( vDialog, szlCtrlMapLOD_Entity ) == zCURSOR_SET &&
                 CheckExistenceOfEntity( vDialog, szlCtrlMapView ) == zCURSOR_SET )
            {
               GetAddrForAttribute( &pchAttr, vDialog, szlCtrlMapView, szlName );
               if ( pchAttr == 0 || pchAttr[ 0 ] == 0 )
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), szlNULL );
               else
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );

               strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
               GetAddrForAttribute( &pchAttr, vDialog, szlCtrlMapLOD_Entity, szlName );
               if ( pchAttr == 0 || pchAttr[ 0 ] == 0 )
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), szlNULL );
               else
                  strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );

               strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
               strcat_s( szDilMsg, zsizeof( szDilMsg ), szlNULL );
            }
            else
            {
               strcat_s( szDilMsg, zsizeof( szDilMsg ), "Null,Null,Null" );
            }

            // Reset the view
         // while ( ResetViewFromSubobject( m_vDialog ) == 0 )
         // {
         // }

            strcat_s( szDilMsg, zsizeof( szDilMsg ), ")" );
         }
         else
         {
            strcat_s( szDilMsg, zsizeof( szDilMsg ), "Null,Null,Null)" );
         }
      }
      else
      {
         szDilMsg[ 0 ] = 0;
      }

      if ( vDialog )
      {
         DropView( vDialog );
         vDialog = 0;
      }

      MB_SetMessage( m_pBar->m_vSubtask, 3, szDilMsg );
   }
   else
   if ( bPosOnly == FALSE )
   {
      // If we have nothing to say about a ctrl, display information
      // about the window.
      if ( MiValidView( m_vDialog ) && (m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
      {
         zPCHAR  pchWindowPage;

         if ( m_pBar->m_fState & zTZCB_XSLT )
            pchWindowPage = szlXSLT;
         else
         if ( m_pBar->m_fState & zTZCB_REPORT )
            pchWindowPage = szlPage;
         else
            pchWindowPage = szlWindow;

         if ( CheckEntityInView( m_vDialog, pchWindowPage ) == 0 )
         {
            strcpy_s( szDilMsg, zsizeof( szDilMsg ), "Window:" );
            GetAddrForAttribute( &pchAttr, m_vDialog, pchWindowPage, szlTag );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );
            GetAddrForAttribute( &pchAttr, m_vDialog, pchWindowPage, szlCaption );
            if ( pchAttr[ 0 ] )
            {
               strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
               strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );
            }

            MB_SetMessage( m_pBar->m_vSubtask, 1, szDilMsg );
            strcpy_s( szDilMsg, zsizeof( szDilMsg ), "Pos(" );
            GetIntegerFromAttribute( &lWork, m_vDialog, pchWindowPage, szlPSDLG_X );
            itoa( (zSHORT) lWork, szDilMsg + 90, 10 );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
            GetIntegerFromAttribute( &lWork, m_vDialog, pchWindowPage, szlPSDLG_Y );
            itoa( (zSHORT) lWork, szDilMsg + 90, 10 );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), "), Size(" );
            GetIntegerFromAttribute( &lWork, m_vDialog, pchWindowPage, szlSZDLG_X );
            itoa( (zSHORT) lWork, szDilMsg + 90, 10 );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), "," );
            GetIntegerFromAttribute( &lWork, m_vDialog, pchWindowPage, szlSZDLG_Y );
            itoa( (zSHORT) lWork, szDilMsg + 90, 10 );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), szDilMsg + 90 );
            strcat_s( szDilMsg, zsizeof( szDilMsg ), ")" );
            MB_SetMessage( m_pBar->m_vSubtask, 2, szDilMsg );

            strcpy_s( szDilMsg, zsizeof( szDilMsg ), "Dialog Desc:" );
            if ( m_pBar->m_fState & zTZCB_XSLT )
               GetAddrForAttribute( &pchAttr, m_vDialog, szlXSLT, szlDesc );
            else
            if ( m_pBar->m_fState & zTZCB_REPORT )
               GetAddrForAttribute( &pchAttr, m_vDialog, szlReport, szlDesc );
            else
               GetAddrForAttribute( &pchAttr, m_vDialog, szlDialog, szlDesc );

            strcat_s( szDilMsg, zsizeof( szDilMsg ), pchAttr );
            MB_SetMessage( m_pBar->m_vSubtask, 3, szDilMsg );
         }
      }
      else
      {
         MB_SetMessage( m_pBar->m_vSubtask, 1, szDilMsg );
         MB_SetMessage( m_pBar->m_vSubtask, 2, szDilMsg );
         MB_SetMessage( m_pBar->m_vSubtask, 3, szDilMsg );
      }
   }
}

// This function snaps a rectangle based on a snap value coming in or
// the snap value in the painter itself.
void
TZPainterWindow::SnapRect( CRect *lpNewRect, CRect *lpOldRect,
                           zSHORT nForceSnap )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::SnapRect", "" );
#endif

   // If snapping is not on, skip outta here.
   if ( nForceSnap )
      PainterSnapRect( m_pBar, lpNewRect, lpOldRect, nForceSnap, nForceSnap );
   else
   if ( m_nSnap )
      PainterSnapRect( m_pBar, lpNewRect, lpOldRect, m_nSnap, m_nSnap );
}

void
TZPainterWindow::AbutSelectedCtrls( zSHORT nAbut )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::AbutSelectedCtrls", "" );
#endif

   if ( m_pLastSelected == 0 || m_nSelectCnt < 2 )
      return;

   TZPainterCtrl *pCtrl;
   TZOrderCtrl   *pOrderHead = 0;
   TZOrderCtrl   *pOrderCtrl;
   CRect         rectCtrl;
   zSHORT        nSelected = 0;
   zSHORT        nIdNbr;
   zSHORT        nPos;

   if ( m_pUndoCurr )
      nIdNbr = m_pUndoCurr->m_nIdNbr + 1;
   else
      nIdNbr = 1;

   // To abut selected ctrls, we get the top-most (or left-most) selected
   // ctrl to use as foundation and then abut the other selected ctrls to
   // the first selected ctrl.

   zSHORT nSnapSave = m_nSnap;
   m_nSnap = 0;   // turn off snapping for abut

   zBOOL  bNext;

   // Locate and order the selected ctrls.
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) )
      {
         nSelected++;
         pCtrl->ParentToPainterRect( rectCtrl );
         pOrderCtrl = new TZOrderCtrl( pCtrl, nPos, rectCtrl );
         if ( pOrderHead == 0 )
         {
            pOrderHead = pOrderCtrl;
         }
         else
         {
            while ( pOrderHead )  // pOrderHead will not become 0!
            {
               if ( nAbut == zABUT_HORIZONTAL )
               {
                  if ( rectCtrl.left >= pOrderHead->m_rectCtrl.left )
                     bNext = TRUE;
                  else
                     bNext = FALSE;
               }
               else
            // if ( nAbut == zABUT_VERTICAL )
               {
                  if ( rectCtrl.top >= pOrderHead->m_rectCtrl.top )
                     bNext = TRUE;
                  else
                     bNext = FALSE;
               }

               if ( bNext )
               {
                  if ( pOrderHead->m_pNext )
                  {
                     pOrderHead = pOrderHead->m_pNext;
                  }
                  else
                  {
                     pOrderCtrl->m_pNext = pOrderHead->m_pNext;
                     pOrderHead->m_pNext = pOrderCtrl;
                     pOrderCtrl->m_pPrev = pOrderHead;
                     break;
                  }
               }
               else
               {
                  if ( pOrderHead->m_pPrev )
                  {
                     pOrderHead = pOrderHead->m_pPrev;
                     if ( nAbut == zABUT_HORIZONTAL )
                     {
                        if ( rectCtrl.left >= pOrderHead->m_rectCtrl.left )
                           bNext = TRUE;
                        else
                           bNext = FALSE;
                     }
                     else
                  // if ( nAbut == zABUT_VERTICAL )
                     {
                        if ( rectCtrl.top >= pOrderHead->m_rectCtrl.top )
                           bNext = TRUE;
                        else
                           bNext = FALSE;
                     }

                     if ( bNext )
                     {
                        pOrderCtrl->m_pNext = pOrderHead->m_pNext;
                        pOrderHead->m_pNext = pOrderCtrl;
                        pOrderCtrl->m_pPrev = pOrderHead;
                        break;
                     }
                  }
                  else
                  {
                     pOrderCtrl->m_pNext = pOrderHead;
                     pOrderHead->m_pPrev = pOrderCtrl;
                     break;
                  }
               }
            }
         }
      }
   }

   if ( nSelected < 2 || pOrderHead == 0 )
   {
      TraceLineI( "<tzctlptr> Unexpected select count for Abut Controls ",
                  nSelected );
      mDeleteInit( pOrderHead );
      return;
   }

   while ( pOrderHead->m_pPrev )  // get back to the beginning
      pOrderHead = pOrderHead->m_pPrev;

   // Abut each ctrl except for the top-most (or left-most) ctrl to the
   // prior ctrl.

   zLONG lDiff;

   pOrderCtrl = pOrderHead->m_pNext;
   rectCtrl = pOrderHead->m_rectCtrl;

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
   {
      if ( nAbut == zABUT_HORIZONTAL )
      {
         lDiff = mConvertPixelTo256thInchX( rectCtrl.right );
         rectCtrl.right = mConvert256thInchToPixelX( lDiff );
      }
      else
      {
         lDiff = mConvertPixelTo256thInchX( rectCtrl.bottom );
         rectCtrl.bottom = mConvert256thInchToPixelX( lDiff );
      }

      if ( pOrderHead->m_rectCtrl.EqualRect( rectCtrl ) == FALSE )
      {
         pCtrl = pOrderHead->m_pCtrl;
         pCtrl->m_pCtrlCover->MoveCtrl( rectCtrl, (TZPainterCtrl *) -1,
                                        nIdNbr,
                                        "&xxdo Abut selected\tCtrl+x" );
      }
   }

   while ( pOrderCtrl )
   {
      pCtrl = pOrderCtrl->m_pCtrl;
      if ( nAbut == zABUT_HORIZONTAL )
      {
         lDiff = pOrderCtrl->m_rectCtrl.right - pOrderCtrl->m_rectCtrl.left;
         rectCtrl.left = rectCtrl.right;
         rectCtrl.right = rectCtrl.left + lDiff;
         if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
         {
            lDiff = mConvertPixelTo256thInchX( rectCtrl.right );
            rectCtrl.right = mConvert256thInchToPixelX( lDiff );
         }
      }
      else
   // if ( nAbut == zABUT_VERTICAL )
      {
         lDiff = pOrderCtrl->m_rectCtrl.bottom - pOrderCtrl->m_rectCtrl.top;
         rectCtrl.top = rectCtrl.bottom;
         rectCtrl.bottom = rectCtrl.top + lDiff;
         if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
         {
            lDiff = mConvertPixelTo256thInchX( rectCtrl.bottom );
            rectCtrl.bottom = mConvert256thInchToPixelX( lDiff );
         }
      }

      pCtrl->m_pCtrlCover->MoveCtrl( rectCtrl, (TZPainterCtrl *) -1,
                                     nIdNbr,
                                     "&xxdo Abut selected\tCtrl+x" );
      pOrderCtrl = pOrderCtrl->m_pNext;
   }

   mDeleteInit( pOrderHead );
   m_nSnap = nSnapSave;   // restore previous snapping position
   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      m_pPainterClient->AdjustGroupSets( );
}

void
TZPainterWindow::AlignSelectedCtrls( zSHORT nAlign )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::AlignSelectedCtrls", "" );
#endif

   TZPainterCtrl *pLastSelected;
   TZPainterCtrl *pCtrl;
   CRect         rectSelect;
   CRect         rectCtrl;
   zLONG         lSizeX;
   zLONG         lSizeY;
   zSHORT        nSnapSave;
   zSHORT        nPos;
   zSHORT        nIdNbr;

   // To align selected ctrls, we get the last selected ctrl to
   // use as a foundation and then align the other selected ctrls
   // to the last selected ctrl (which in turn will size the ctrl).
   if ( m_pLastSelected == 0 )
      return;

   if ( m_pUndoCurr )
      nIdNbr = m_pUndoCurr->m_nIdNbr + 1;
   else
      nIdNbr = 1;

   pLastSelected = m_pLastSelected;
   nSnapSave = m_nSnap;
   m_nSnap = 0;   // turn off snapping for alignment

   pLastSelected->ParentToPainterRect( rectSelect );
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) && pCtrl != pLastSelected )
      {
         pCtrl->ParentToPainterRect( rectCtrl );
         lSizeX = rectCtrl.right - rectCtrl.left;
         lSizeY = rectCtrl.bottom - rectCtrl.top;
         if ( nAlign == zALIGN_LEFT )
         {
            rectCtrl.left  = rectSelect.left;
            rectCtrl.right = rectCtrl.left + lSizeX;
         }
         else
         if ( nAlign == zALIGN_TOP )
         {
            rectCtrl.top = rectSelect.top;
            rectCtrl.bottom = rectCtrl.top + lSizeY;
         }
         else
         if ( nAlign == zALIGN_RIGHT )
         {
            rectCtrl.right = rectSelect.right;
            rectCtrl.left = rectCtrl.right - lSizeX;
         }
         else
         if ( nAlign == zALIGN_BOTTOM )
         {
            rectCtrl.bottom = rectSelect.bottom;
            rectCtrl.top = rectCtrl.bottom - lSizeY;
         }
         else
            break;

         pCtrl->m_pCtrlCover->MoveCtrl( rectCtrl, (TZPainterCtrl *) -1,
                                        nIdNbr,
                                        "&xxdo Align selected\tCtrl+x" );
      }
   }

   m_nSnap = nSnapSave;                // restore previous snapping flag
   m_pLastSelected = pLastSelected;    // restore last selected
   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      m_pPainterClient->AdjustGroupSets( );
}

void
TZPainterWindow::EqualSpaceSelectedCtrls( zSHORT nSpace )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::EqualSpaceSelectedCtrls", "" );
#endif

   TZPainterCtrl *pOrigLastSelected;
   TZPainterCtrl *pFirstSelected;
   TZPainterCtrl *pLastSelected;
   TZPainterCtrl *pCtrl;
   zSHORT        nSnapSave;      // Turn off snap for equal space
   zSHORT        nPos;

   if ( m_pLastSelected == 0 || m_nSelectCnt < 3 )
      return;

   // To equally space selected ctrls, we get the last selected ctrl
   // to use as a foundation and locate the first and last selected ctrls.
   pOrigLastSelected = pFirstSelected = pLastSelected = m_pLastSelected;

   nSnapSave = m_nSnap;
   m_nSnap = 0;   // turn off snapping for alignment

   zLONG  lTotalSize = 0;
   zSHORT nSelected = 0;

   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) )
      {
         pCtrl->m_bShiftKey = TRUE; // using this flag temporarily
                                    // so in the next loop, we
                                    // know who has been processed
         nSelected++;
         if ( nSpace == zEQUAL_VSPACE )
         {
            lTotalSize += pCtrl->m_rectCtrl.bottom - pCtrl->m_rectCtrl.top;
            if ( pCtrl->m_rectCtrl.top < pFirstSelected->m_rectCtrl.top )
               pFirstSelected = pCtrl;

            if ( pCtrl->m_rectCtrl.bottom > pLastSelected->m_rectCtrl.bottom )
               pLastSelected = pCtrl;
         }
         else
      // if ( nSpace == zEQUAL_HSPACE )
         {
            lTotalSize += pCtrl->m_rectCtrl.right -
                          pCtrl->m_rectCtrl.left;
            if ( pCtrl->m_rectCtrl.left < pFirstSelected->m_rectCtrl.left )
               pFirstSelected = pCtrl;

            if ( pCtrl->m_rectCtrl.right > pLastSelected->m_rectCtrl.right )
               pLastSelected = pCtrl;
         }
      }
      else
      {
         pCtrl->m_bShiftKey = FALSE;
      }
   }

   if ( nSelected < 3 )
   {
      TraceLineI( "<tzctlptr> Unexpected select count for Equal Spacing ",
                  nSelected );
      return;
   }

   zLONG  lSizeX;
   zLONG  lSizeY;
   zLONG  lSpacing;

   if ( nSpace == zEQUAL_VSPACE )
      lSpacing = pLastSelected->m_rectCtrl.bottom - pFirstSelected->m_rectCtrl.top;
   else
      lSpacing = pLastSelected->m_rectCtrl.right - pFirstSelected->m_rectCtrl.left;

   lSpacing -= lTotalSize;       // this may go negative
   lSpacing /= (nSelected - 1);  // e.g. if three are selected,
                                 // only 2 space areas are required

   // This is in pixels ... make it in terms of whole dialog units.
   if ( nSpace == zEQUAL_VSPACE )
   {
      lSizeY = lSpacing;
      if ( lSizeY < 0 )
         lSpacing = -lSpacing;

      if ( m_pBar->m_bUseMapDlgUnits )
      {
         lSpacing = mConvertPixelToMapDlgY( lSpacing );
         lSpacing = mConvertMapDlgToPixelY( lSpacing );
      }
      else
      {
         lSpacing = mConvertPixelToDlgUnitY( lSpacing );
         lSpacing = mConvertDlgUnitToPixelY( lSpacing );
      }

      if ( lSizeY < 0 )
         lSpacing = -lSpacing;
   }
   else
   {
      lSizeX = lSpacing;
      if ( lSizeX < 0 )
         lSpacing = -lSpacing;

      if ( m_pBar->m_bUseMapDlgUnits )
      {
         lSpacing = mConvertPixelToMapDlgX( lSpacing );
         lSpacing = mConvertMapDlgToPixelX( lSpacing );
      }
      else
      {
         lSpacing = mConvertPixelToDlgUnitX( lSpacing );
         lSpacing = mConvertDlgUnitToPixelX( lSpacing );
      }

      if ( lSizeX < 0 )
         lSpacing = -lSpacing;
   }

   // Don't move the top-most (or left-most) ctrls.  Process the loop
   // (nSelected - 1) times, looking for the top-most (or left-most) selected
   // ctrl.  Move that ctrl, resetting the pFirstSelected to be that ctrl.
   // Note that we would leave the bottom-most (or right-most) ctrl at its
   // original position, but to guarantee equal spacing, we have to let
   // it move (to make up for rounding in the above division).
   //
   TZPainterCtrl *pNextMove;
   CRect         rectCtrlFirst;
   CRect         rectCtrl;

   while ( pFirstSelected && nSelected-- > 1 )
   {
      // We don't want to adjust the position of the first ctrl.
      pFirstSelected->m_bShiftKey = FALSE;
      pNextMove = pLastSelected;
      for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
      {
         pCtrl = m_CtrlList[ nPos ];
         if ( pCtrl->m_bShiftKey )  // pCtrl->IsSelected( ) &&
                                    // pCtrl != pFirstSelected &&
                                    // pCtrl != pLastSelected )
         {
            if ( nSpace == zEQUAL_VSPACE )
            {
               if ( pCtrl->m_rectCtrl.top < pNextMove->m_rectCtrl.top )
                  pNextMove = pCtrl;
            }
            else
            {
               if ( pCtrl->m_rectCtrl.left < pNextMove->m_rectCtrl.left )
                  pNextMove = pCtrl;
            }
         }
      }

      if ( pNextMove && pNextMove != pFirstSelected )
      {
         pFirstSelected->ParentToPainterRect( rectCtrlFirst );
         pNextMove->ParentToPainterRect( rectCtrl );
         if ( nSpace == zEQUAL_VSPACE )
         {
            lSizeY = rectCtrl.bottom - rectCtrl.top;
            rectCtrl.top = rectCtrlFirst.bottom + lSpacing;
            rectCtrl.bottom = rectCtrl.top + lSizeY;
         }
         else
         {
            lSizeX = rectCtrl.right - rectCtrl.left;
            rectCtrl.left = rectCtrlFirst.right + lSpacing;
            rectCtrl.right = rectCtrl.left + lSizeX;
         }

         pNextMove->m_pCtrlCover->MoveCtrl( rectCtrl );
      }

      pFirstSelected = pNextMove;
   }

   m_nSnap = nSnapSave;   // restore previous snapping position
   m_pLastSelected = pOrigLastSelected;  // restore last selected
   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      m_pPainterClient->AdjustGroupSets( );
}

void
TZPainterWindow::SizeSelectedCtrls( zSHORT nSize )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::SizeSelectedCtrls", "" );
#endif

   TZPainterCtrl *pLastSelected;
   TZPainterCtrl *pCtrl;
   CRect         rectSelect;
   CRect         rectCtrl;
   zLONG         lSizeX;
   zLONG         lSizeY;
   zSHORT        nSnapSave;      // Turn off snap for resize
   zSHORT        nPos;
   zSHORT        nIdNbr;

   // To size selected ctrls, we get the last selected ctrl
   // to use as a foundation and then size the frame around the
   // other selected ctrls (which in turn will size the ctrl).
   if ( m_pLastSelected == 0 )
      return;

   if ( m_pUndoCurr )
      nIdNbr = m_pUndoCurr->m_nIdNbr + 1;
   else
      nIdNbr = 1;

   pLastSelected = m_pLastSelected;
   nSnapSave = m_nSnap;
   m_nSnap = 0;   // turn off snapping for alignment

   rectSelect = pLastSelected->m_rectCtrl;
   lSizeX = rectSelect.right - rectSelect.left;
   lSizeY = rectSelect.bottom - rectSelect.top;

   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) && pCtrl != pLastSelected )
      {
         pCtrl->ParentToPainterRect( rectCtrl );
         if ( (nSize == zSIZE_WIDTH) || (nSize == zSIZE_BOTH) )
         {
            rectCtrl.right = rectCtrl.left + lSizeX;
         }

         if ( (nSize == zSIZE_HEIGHT) || (nSize == zSIZE_BOTH) )
         {
            rectCtrl.bottom = rectCtrl.top + lSizeY;
         }

         pCtrl->m_pCtrlCover->MoveCtrl( rectCtrl, (TZPainterCtrl *) -1,
                                        nIdNbr,
                                        "&xxdo Size selected\tCtrl+x" );
      }
   }

   m_nSnap = nSnapSave;   // restore previous snapping position
   m_pLastSelected = pLastSelected;  // restore last selected
   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      m_pPainterClient->AdjustGroupSets( );
}

zSHORT
TZPainterWindow::DeleteCtrl( TZPainterCtrl *pCtrlParent,
                             zSHORT nIdNbr, zSHORT nTotalDeleteCnt )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::DeleteCtrl", "" );
#endif

   TZPainterCtrl *pCtrl;
   zCHAR         szLabel[ 64 ];
   zSHORT        nDeleteCnt = 0;
   zSHORT        nPos;
   zBOOL         bSelected;
   zSHORT        k;

   // First delete any children of selected parents, then the parents.
   for ( nPos = 0; nPos < m_nCtrlCnt; )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( (pCtrlParent && pCtrl->m_pCtrlParent == pCtrlParent) ||
           (pCtrlParent == 0 && (pCtrl->IsSelected( ) &&
            (pCtrl = pCtrl->IsDeletable( )) != 0)) )
      {
         bSelected = pCtrl->IsSelected( );
         if ( bSelected )
         {
            if ( pCtrl == m_pLastSelected )
               bSelected = -1;

            Deselect( pCtrl );
         }

         k = DeleteCtrl( pCtrl, nIdNbr, nTotalDeleteCnt );
         nTotalDeleteCnt += k;
         nDeleteCnt += k;

         // Relocate position since it may have changed during the deletion
         // of child ctrls.
         for ( k = 0; pCtrl && k < m_nCtrlCnt; k++ )
         {
            if ( pCtrl == m_CtrlList[ k ] )
            {
               m_CtrlList.RemoveAt( k );
               m_nCtrlCnt--;
               nTotalDeleteCnt++;
               nDeleteCnt++;
               sprintf_s( szLabel, zsizeof( szLabel ), "&xxdo Delete %d item%s\tCtrl+x",
                         nTotalDeleteCnt,
                         nTotalDeleteCnt == 1 ? "" : "s" );
               AddToUndo( pCtrl, nIdNbr, nPos, bSelected,
                          TZUndoRedo::eDelete, szLabel );

               break;
            }
         }

         // We just deleted the ctrl, so restart at the top of the
         // list since the current nPos may not be valid.
         nPos = 0;
      }
      else
         nPos++;
   }

   return( nDeleteCnt );
}

void
TZPainterWindow::DeleteSelectedCtrls( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::DeleteSelectedCtrls", "" );
#endif

   if ( m_nCtrlCnt )
      DeleteCtrl( 0, m_pUndoCurr ? m_pUndoCurr->m_nIdNbr + 1 : 1, 0 );
}

void
TZPainterWindow::EqualSizePosClassCtrls( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::EqualSizePosClassCtrls", "" );
#endif

   TZPainterWindow *pPainterWindow;
   TZPainterCtrl *pCtrl;
   zPCHAR        pchClass;
   zLONG         lPosX;
   zLONG         lPosY;
   zLONG         lSizeX;
   zLONG         lSizeY;
   zSHORT        nPosWnd;

   // To set selected ctrls, we get the last (only) selected ctrl to use
   // as a foundation and then set the selected ctrls Pos/Size/Class in
   // other visible painter windows to this selected ctrl.
   if ( m_pLastSelected == 0 || m_nSelectCnt > 1 )
   {
      OperatorPrompt( m_pBar->m_pZSubtask->m_vDialog,
                      "Equal size/position/class across Windows",
                      "Exactly one control must be selected in the active window",
                      0, zBUTTONS_OK, zRESPONSE_OK, 0 );
      return;
   }

   pCtrl = m_pLastSelected;
   if ( pCtrl->PositionOnZeidonCtrl( ) == 0 )
   {
      OperatorPrompt( m_pBar->m_pZSubtask->m_vDialog,
                      "Equal size/position/class across Windows",
                      "Cannot get Zeidon information for the selected control in the active window",
                      0, zBUTTONS_OK, zRESPONSE_OK, 0 );
      return;
   }

   GetIntegerFromAttribute( &lPosX, pCtrl->m_vCtrl, "Control", "PSDLG_X" );
   GetIntegerFromAttribute( &lPosY, pCtrl->m_vCtrl, "Control", "PSDLG_Y" );
   GetIntegerFromAttribute( &lSizeX, pCtrl->m_vCtrl, "Control", "SZDLG_X" );
   GetIntegerFromAttribute( &lSizeY, pCtrl->m_vCtrl, "Control", "SZDLG_Y" );
   GetAddrForAttribute( &pchClass, pCtrl->m_vCtrl, "Control", "CSS_Class" );
   TraceLine( "Source Ctrl: %s  Pos/Size: %d,%d/%d,%d  Class: %s",
              pCtrl->m_csTag, lPosX, lPosY, lSizeX, lSizeY, pchClass );
   pCtrl->Deselect( );

   for ( nPosWnd = 0; nPosWnd < m_pBar->m_nWndCnt; nPosWnd++ )
   {
      pPainterWindow = m_pBar->m_PainterWindowList[ nPosWnd ];
      pPainterWindow->UpdateZeidonWindow( );  // get Zeidon entities in sync with painter
      if ( pPainterWindow != this )
      {
         if ( pPainterWindow->m_nSelectCnt > 1 )
         {
            OperatorPrompt( m_pBar->m_pZSubtask->m_vDialog,
                            "Equal size/position/class across Windows",
                            "Only one control may be selected in each Window",
                            0, zBUTTONS_OK, zRESPONSE_OK, 0 );
            return;
         }

         pCtrl = pPainterWindow->m_pLastSelected;
         if ( pCtrl )
         {
            if ( pCtrl->PositionOnZeidonCtrl( ) )
            {
               SetNameForView( pCtrl->m_vCtrl, szlTZCONTROL, m_vDialog, zLEVEL_TASK );
               SetAttributeFromInteger( pCtrl->m_vCtrl, "Control", "PSDLG_X", lPosX );
               SetAttributeFromInteger( pCtrl->m_vCtrl, "Control", "PSDLG_Y", lPosY );
               SetAttributeFromInteger( pCtrl->m_vCtrl, "Control", "SZDLG_X", lSizeX );
               SetAttributeFromInteger( pCtrl->m_vCtrl, "Control", "SZDLG_Y", lSizeY );
               SetAttributeFromString( pCtrl->m_vCtrl, "Control", "CSS_Class", pchClass );
               TraceLine( "Setting Ctrl: %s  Pos/Size: %d,%d/%d,%d  Class: %s",
                          pCtrl->m_csTag, lPosX, lPosY, lSizeX, lSizeY, pchClass );
               pCtrl->Deselect( );
               pPainterWindow->RepaintZeidonCtrl( );
            // DropNameForView( pCtrl->m_vCtrl, szlTZCONTROL, m_vDialog, zLEVEL_TASK );
               while ( ResetViewFromSubobject( pPainterWindow->m_vDialog ) == 0 )
               {
               }
            }
         }
      }
   }

   while ( ResetViewFromSubobject( m_vDialog ) == 0 )
   {
   }

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      m_pPainterClient->AdjustGroupSets( );
}

void
TZPainterWindow::GroupBoxSelectedCtrls( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::GroupBoxSelectedCtrls", "" );
#endif

   TZPainterCtrl *pCtrlParent;
   TZPainterCtrl *pCtrl;
   CRect         rect;
   CRect         rectCtrl;
   zSHORT        nSelected = 0;
   zSHORT        nIdNbr;
   zSHORT        nPos;

   // First ensure parent of all selected controls is the same and get the
   // extent of the selected controls.
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) )
      {
         nSelected++;
         if ( nSelected == 1 )
         {
            pCtrlParent = pCtrl->m_pCtrlParent;
            rect = pCtrl->m_rectCtrl;
         }
         else
         if ( pCtrl->m_pCtrlParent == pCtrlParent )
         {
            if ( rect.top > pCtrl->m_rectCtrl.top )
               rect.top = pCtrl->m_rectCtrl.top;

            if ( rect.left > pCtrl->m_rectCtrl.left )
               rect.left = pCtrl->m_rectCtrl.left;

            if ( rect.bottom < pCtrl->m_rectCtrl.bottom )
               rect.bottom = pCtrl->m_rectCtrl.bottom;

            if ( rect.right < pCtrl->m_rectCtrl.right )
               rect.right = pCtrl->m_rectCtrl.right;
         }
         else
         {
            MessageSend( m_pBar->m_vSubtask, 0,
                         "Zeidon Dialog",
                         "All controls selected to be within a GroupBox must have the same parent",
                         zMSGQ_MODAL_ERROR, FALSE );
            return;
         }
      }
   }

   if ( nSelected == 0 )
   {
      MessageSend( m_pBar->m_vSubtask, 0,
                   "Zeidon Dialog",
                   "At least one control must be selected for groupbox",
                   zMSGQ_MODAL_ERROR, FALSE );
      return;
   }

   // Now create a new parent (groupbox) and move all selected controls within that parent.
   pCtrlParent = PaintCtrl( pCtrlParent, "Control", 0, 1090, &rect, "", "", 0, 0 );
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) )
      {
         if ( m_pUndoCurr )
            nIdNbr = m_pUndoCurr->m_nIdNbr + 1;
         else
            nIdNbr = 1;

         pCtrl->m_pCtrlCover->MoveCtrl( pCtrl->m_rectPainter, pCtrlParent, nIdNbr, "GroupBoxSelectedCtrls" );
      }
   }
}

void
TZPainterWindow::UngroupSelectedGroupCtrls( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::UngroupSelectedGroupCtrls", "" );
#endif

   TZPainterCtrl *pCtrlParent;
   TZPainterCtrl *pCtrl;
   CRect         rect;
   CRect         rectCtrl;
   zSHORT        nSelected = 0;
   zSHORT        nIdNbr;
   zSHORT        nPos;

   // First ensure only one control is selected.
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) && pCtrl->m_lType == zGROUPBOX_CONTROL )
      {
         nSelected++;
         pCtrlParent = pCtrl;
      }
   }

   if ( nSelected != 1 )
   {
      MessageSend( m_pBar->m_vSubtask, 0,
                   "Zeidon Dialog",
                   "Exactly one groupbox control must be selected to ungroup",
                   zMSGQ_MODAL_ERROR, FALSE );
      return;
   }

   // Now delete the selected ctrl (groupbox) and move all child controls
   // within the parent (if any) of the selected ctrl.
   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      if ( pCtrl->m_pCtrlParent == pCtrlParent )
      {
         if ( m_pUndoCurr )
            nIdNbr = m_pUndoCurr->m_nIdNbr + 1;
         else
            nIdNbr = 1;

         pCtrl->m_pCtrlCover->MoveCtrl( pCtrl->m_rectPainter, pCtrlParent->m_pCtrlParent,
                                        nIdNbr, "UngroupSelectedCtrls" );
      }
   }

   pCtrlParent->Select( );
   DeleteCtrl( 0, m_pUndoCurr ? m_pUndoCurr->m_nIdNbr + 1 : 1, 0 );
}

zBOOL
TZPainterWindow::DeselectAllCtrls( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::DeselectAllCtrls", "" );
#endif
   TZPainterCtrl *pCtrl;
   zSHORT        nCtrlPos;
   zBOOL         bSelected = FALSE;

   // Deselect all selected ctrls.
   for ( nCtrlPos = 0;
         nCtrlPos < m_nCtrlCnt;
         nCtrlPos++ )
   {
      pCtrl = m_CtrlList[ nCtrlPos ];
      if ( pCtrl->Deselect( ) == FALSE )
         bSelected = TRUE;
   }

   return( bSelected );
}

void
TZPainterWindow::AddToUndo( TZPainterCtrl *pCtrl, zSHORT nIdNbr,
                            zSHORT nArrayPos, zBOOL bSelected,
                            TZUndoRedo::eUNDO_REDO_TYPE eType,
                            zCPCHAR cpcLabel )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::AddToUndo", "" );
#endif
   if ( pCtrl == 0 )
      return;

   if ( m_pRedoCurr )
   {
      TZUndoRedo *pUndoCurr = m_pUndoCurr;
      TZUndoRedo *pUndoRedo = m_pUndoRedo;
      m_pUndoCurr = 0;
      m_pUndoRedo = 0;
      m_pRedoCurr->m_pPrev = 0; // break the chain
      FinalizeUndoRedo( ); // finalize those that are being orphaned
      m_pUndoCurr = pUndoCurr;
      m_pUndoRedo = pUndoRedo;
      ASSERT( m_pRedoCurr == 0 );
   }

   m_pUndoRedo = new TZUndoRedo( pCtrl, nIdNbr, nArrayPos,
                                 bSelected, eType, cpcLabel );
   if ( m_pUndoCurr )
   {
      m_pUndoCurr->m_pPrev = m_pUndoRedo;
      m_pUndoRedo->m_pNext = m_pUndoCurr;
   }

   m_pUndoCurr = m_pUndoRedo;
   if ( eType == TZUndoRedo::eDelete )
      pCtrl->UndoRedo( FALSE );
}

void
TZPainterWindow::MoveToUndoRedo( zBOOL bToRedo )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::MoveToUndoRedo", "" );
#endif

   if ( m_pUndoRedo )
   {
      TZPainterCtrl *pCtrl;
      zSHORT        nPos;
      zSHORT        nIdNbr;

      if ( bToRedo )
      {
         if ( m_pRedoCurr )
         {
            nIdNbr = m_pRedoCurr->m_nIdNbr;
            while ( m_pRedoCurr && nIdNbr == m_pRedoCurr->m_nIdNbr )
            {
               m_pUndoCurr = m_pRedoCurr;
               if ( m_pRedoCurr->m_eType == TZUndoRedo::eDelete )
               {
                  for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
                  {
                     pCtrl = m_CtrlList[ nPos ];
                     if ( pCtrl == m_pRedoCurr->m_pCtrl )
                     {
                        if ( m_pRedoCurr->m_bSelected )
                           Deselect( m_pRedoCurr->m_pCtrl );

                        m_CtrlList.RemoveAt( nPos );
                        m_nCtrlCnt--;
                        m_pRedoCurr->m_nArrayPos = nPos;
                        m_pRedoCurr->m_uVisible =
                                            m_pRedoCurr->m_pCtrl->m_uVisible;
                     // m_pRedoCurr->m_pCtrl->
                     //                    m_pWndCtrl->ShowWindow( SW_HIDE );

                        m_pRedoCurr->m_pCtrl->HideForUndo( TRUE );
                        break;
                     }
                  }
               }
               else
               if ( m_pRedoCurr->m_eType == TZUndoRedo::eCreate ||
                    m_pRedoCurr->m_eType == TZUndoRedo::eClone )
               {
                  if ( m_pRedoCurr->m_nArrayPos > m_nCtrlCnt )
                     m_pRedoCurr->m_nArrayPos = m_nCtrlCnt;

                  m_CtrlList.InsertAt( m_pRedoCurr->m_nArrayPos,
                                       m_pRedoCurr->m_pCtrl );
                  m_nCtrlCnt++;
                  m_pRedoCurr->m_pCtrl->m_uVisible = m_pRedoCurr->m_uVisible;
                  if ( m_pRedoCurr->m_pCtrl->GetVisibility( ) == 0 ) // visible
                  {
                     m_pRedoCurr->m_pCtrl->UndoRedo( TRUE );
                  // m_pRedoCurr->m_pCtrl->m_pWndCtrl->ShowWindow( SW_SHOW );
                     m_pRedoCurr->m_pCtrl->HideForUndo( FALSE );
                     if ( m_pRedoCurr->m_bSelected )
                        Select( m_pRedoCurr->m_pCtrl, FALSE );
                  }
               }
               else
            // if ( Move or Size )
               {
                  CRect rectCtrl( m_pRedoCurr->m_rect );
                  CRect rect( m_pRedoCurr->m_rectPainter );
                  TZPainterCtrl *pNewParent = m_pRedoCurr->m_pParent;

                  m_pRedoCurr->m_rect = m_pRedoCurr->m_pCtrl->m_rectCtrl;
                  m_pRedoCurr->m_rectPainter = m_pRedoCurr->m_pCtrl->m_rectPainter;
                  m_pRedoCurr->m_pParent = m_pRedoCurr->m_pCtrl->m_pCtrlParent;
                  m_pRedoCurr->m_pCtrl->m_pCtrlCover->MoveCtrl( rect, pNewParent );
               }

               m_pRedoCurr = m_pRedoCurr->m_pPrev;
            }
         }
      }
      else
      {
         if ( m_pUndoCurr )
         {
            nIdNbr = m_pUndoCurr->m_nIdNbr;
            while ( m_pUndoCurr && nIdNbr == m_pUndoCurr->m_nIdNbr )
            {
               m_pRedoCurr = m_pUndoCurr;
               if ( m_pRedoCurr->m_eType == TZUndoRedo::eDelete )
               {
                  if ( m_pRedoCurr->m_nArrayPos > m_nCtrlCnt )
                     m_pRedoCurr->m_nArrayPos = m_nCtrlCnt;

                  m_CtrlList.InsertAt( m_pRedoCurr->m_nArrayPos,
                                       m_pRedoCurr->m_pCtrl );
                  m_nCtrlCnt++;
                  m_pRedoCurr->m_pCtrl->m_uVisible = m_pRedoCurr->m_uVisible;
                  if ( m_pRedoCurr->m_pCtrl->GetVisibility( ) == 0 ) // visible
                  {
                  // m_pRedoCurr->m_pCtrl->m_pWndCtrl->ShowWindow( SW_SHOW );
                     m_pRedoCurr->m_pCtrl->HideForUndo( FALSE );
                     if ( m_pRedoCurr->m_bSelected )
                        Select( m_pRedoCurr->m_pCtrl, FALSE );
                  }
               }
               else
               if ( m_pRedoCurr->m_eType == TZUndoRedo::eCreate ||
                    m_pRedoCurr->m_eType == TZUndoRedo::eClone )
               {
                  for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
                  {
                     pCtrl = m_CtrlList[ nPos ];
                     if ( pCtrl == m_pRedoCurr->m_pCtrl )
                     {
                        if ( m_pRedoCurr->m_bSelected )
                           Deselect( m_pRedoCurr->m_pCtrl );

                        m_CtrlList.RemoveAt( nPos );
                        m_nCtrlCnt--;
                        m_pRedoCurr->m_nArrayPos = nPos;
                        m_pRedoCurr->m_uVisible =
                                            m_pRedoCurr->m_pCtrl->m_uVisible;
                     // m_pRedoCurr->m_pCtrl->
                     //                    m_pWndCtrl->ShowWindow( SW_HIDE );
                        m_pRedoCurr->m_pCtrl->HideForUndo( TRUE );
                        break;
                     }
                  }
               }
               else
            // if ( Move or Size )
               {
                  CRect rectCtrl( m_pRedoCurr->m_rect );
                  CRect rect( m_pRedoCurr->m_rectPainter );
                  TZPainterCtrl *pNewParent = m_pRedoCurr->m_pParent;

                  m_pRedoCurr->m_rect = m_pRedoCurr->m_pCtrl->m_rectCtrl;
                  m_pRedoCurr->m_rectPainter = m_pRedoCurr->m_pCtrl->m_rectPainter;
                  m_pRedoCurr->m_pParent = m_pRedoCurr->m_pCtrl->m_pCtrlParent;
                  m_pRedoCurr->m_pCtrl->m_pCtrlCover->MoveCtrl( rect, pNewParent );
                  if ( m_pRedoCurr->m_bSelected == -1 )
                     m_pLastSelected = m_pRedoCurr->m_pCtrl;
               }

               m_pUndoCurr = m_pUndoCurr->m_pNext;
            }
         }
      }
   }
}

void
TZPainterWindow::FinalizeUndoRedo( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::FinalizeUndoRedo", "" );
#endif

   TZPainterCtrl *pCtrl;
   zVIEW         vDialog;
   TZUndoRedo    *pRedoCurr;

// if ( m_pUndoRedo == 0 )
//    return;

   // Create a view for deletion of all ctrls in the Undo/Redo list.
   if ( MiValidView( m_vDialog ) )
      CreateViewFromViewForTask( &vDialog, m_vDialog, m_vDialog );

   while ( m_pRedoCurr )
   {
      if ( m_pRedoCurr->m_eType == TZUndoRedo::eCreate ||
           m_pRedoCurr->m_eType == TZUndoRedo::eClone )
      {
         pCtrl = m_pRedoCurr->m_pCtrl;

         // If the object is connected to a Zeidon ctrl, delete
         // the Zeidon ctrl.
         if ( pCtrl->m_lZKey )
         {
            if ( pCtrl->PositionOnZeidonCtrl( vDialog ) )
            {
               zPCHAR pchEntity;

               if ( pCtrl->m_chEntity == 'C' )
                  pchEntity = szlControl;
               else
               if ( pCtrl->m_chEntity == 'G' )
                  pchEntity = szlGroup;
               else
            // if ( pCtrl->m_chEntity == 'S' )
                  pchEntity = szlGroupSet;

               DeleteEntity( vDialog, pchEntity, zREPOS_NEXT );
            }
         }

         Remove( pCtrl );
      }

      pRedoCurr = m_pRedoCurr->m_pPrev;
      if ( m_pUndoRedo == 0 )
         delete( m_pRedoCurr );

      m_pRedoCurr = pRedoCurr;
   }

   while ( m_pUndoCurr )
   {
      if ( m_pUndoCurr->m_eType == TZUndoRedo::eDelete )
      {
         pCtrl = m_pUndoCurr->m_pCtrl;

         // If the object is connected to a Zeidon ctrl, delete
         // the Zeidon ctrl.
         if ( pCtrl->m_lZKey )
         {
            if ( pCtrl->PositionOnZeidonCtrl( vDialog ) )
            {
               zPCHAR pchEntity;

               if ( pCtrl->m_chEntity == 'C' )
                  pchEntity = szlControl;
               else
               if ( pCtrl->m_chEntity == 'G' )
                  pchEntity = szlGroup;
               else
            // if ( pCtrl->m_chEntity == 'S' )
                  pchEntity = szlGroupSet;

               DeleteEntity( vDialog, pchEntity, zREPOS_NEXT );
            }
         }

         Remove( pCtrl );
      }

      m_pUndoCurr = m_pUndoCurr->m_pNext;
   }

   while ( m_pUndoRedo )
   {
      m_pUndoCurr = m_pUndoRedo->m_pNext;
      delete( m_pUndoRedo );
      m_pUndoRedo = m_pUndoCurr;
   }

   // m_pRedoCurr and m_pUndoCurr and m_pUndoRedo are already null.

   // Now that we have deleted all ctrls in the Undo/Redo list, drop the view
   // we created for deleting ctrls.
   if ( MiValidView( m_vDialog ) )
      DropView( vDialog );
}

void
TZPainterWindow::ValidateCtrlTags( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::ValidateCtrlTags", "" );
#endif

   if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
      return;     // we don't care about tags for reports ... DKS 9-17-96

   zSHORT            nPos, nPos2;
   TZPainterCtrl     *pCtrl;
   TZPainterCtrl     *pCtrl2;
   zCHAR             szMessage[ 256 ];

   for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
   {
      pCtrl = m_CtrlList[ nPos ];
      for ( nPos2 = nPos + 1; nPos2 < m_nCtrlCnt; nPos2++ )
      {
         pCtrl2 = m_CtrlList[ nPos2 ];
//       if ( pCtrl->m_csTag == pCtrl2->csTag )
         if ( zstrcmp( pCtrl->m_csTag.GetString(), pCtrl2->m_csTag.GetString() ) == 0 )
         {
            strcpy_s( szMessage, zsizeof( szMessage ), "Duplicate tag '" );
            strcat_s( szMessage, zsizeof( szMessage ), pCtrl->m_csTag );
            strcat_s( szMessage, zsizeof( szMessage ), "' found!" );
            SysMessageBox( m_pBar->m_pZSubtask->m_vDialog, "Error", szMessage, 1 );
         }
      }
   }
}

BOOL
TZPainterWindow::OnCommand( WPARAM wParam, LPARAM lParam )
{
   TraceLineI( "TZActiveX::OnCommand: ", lParam );
   UINT uID = LOWORD( wParam );
   UINT uNotifyCode = HIWORD( wParam );
   HWND hWndCtrl = (HWND) lParam;

   if ( m_pActiveX && hWndCtrl == 0 )
   {
      m_pActiveX->OnMenuCommand( uID );
      m_pActiveX = 0;
      return( TRUE );  // we have processed the message
   }
   else
      return( CWnd::OnCommand( wParam, lParam ) );
}

// Message cracker for message WM_WINDOWPOSCHANGED
void
TZPainterWindow::OnWindowPosChanged( WINDOWPOS *pWindowPos )
{
#ifdef DEBUG_ALL
// TraceLineS( "TZPainterWindow::OnWindowPosChanged", "" );
#endif

   if ( m_pBar && (m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 &&
        m_vDialog && (m_fWndState & zTZPW_INITIALIZING) ==0 )
   {
      if ( (m_fWndState & zTZPW_UPDATEABLE) && m_uSizeX &&
           (m_uSizeX != pWindowPos->cx || m_uSizeY != pWindowPos->cy) )
      {
         zLONG  lSizeX;
         zLONG  lSizeY;
         CRect  rect;

         m_pPainterClient->GetClientRect( rect );
      // TraceLineI( "TZPainterWindow::OnWindowPosChanged width: ", pWindowPos->cx );
      // TraceLineI( "(rect follows)::OnWindowPosChanged height: ", pWindowPos->cy );
      // TraceRect( m_csWndTag, rect );
         if ( m_pBar->m_bUseMapDlgUnits )
         {
            lSizeX = MAKELONG( mConvertPixelToMapDlgX( pWindowPos->cx ),
                               mConvertPixelToMapDlgX( rect.right ) );
            lSizeY = MAKELONG( mConvertPixelToMapDlgY( pWindowPos->cy ),
                               mConvertPixelToMapDlgY( rect.bottom ) );
         }
         else
         {
            lSizeX = MAKELONG( mConvertPixelToDlgUnitX( pWindowPos->cx ),
                               mConvertPixelToDlgUnitX( rect.right ) );
            lSizeY = MAKELONG( mConvertPixelToDlgUnitY( pWindowPos->cy ),
                               mConvertPixelToDlgUnitY( rect.bottom ) );
         }

         SetAttributeFromInteger( m_vDialog, szlWindow, szlSZDLG_X, lSizeX );
         SetAttributeFromInteger( m_vDialog, szlWindow, szlSZDLG_Y, lSizeY );

      // SetAttributeFromInteger( m_vDialog, szlWindow, szlSZDLG_X,
      //                          mConvertPixelToDlgUnitX( pWindowPos->cx ) );
      // SetAttributeFromInteger( m_vDialog, szlWindow, szlSZDLG_Y,
      //                          mConvertPixelToDlgUnitY( pWindowPos->cy ) );
      //
      // zSHORT w = GetSystemMetrics( SM_CXVSCROLL );
      // zSHORT h = GetSystemMetrics( SM_CYHSCROLL );
      // rect.right -= rect.left;
      // rect.bottom -= rect.top;
      //
      // m_pVScroll->SetWindowPos( wndTop, rect.right - w, 0,
      //                           w, rect.bottom - h, SWP_SHOWWINDOW );
      // m_pHScroll->SetWindowPos( wndTop, 0, rect.bottom - h,
      //                           rect.right - w, h, SWP_SHOWWINDOW );
      //
      // TraceLineI( "Painter WindowPos rect.right = ", rect.right );
      // TraceLineI( "Painter WindowPos rect.bottom = ", rect.bottom );
      }

      m_uSizeX = pWindowPos->cx;
      m_uSizeY = pWindowPos->cy;
      SetDIL_Text( );
   }

   Default( );
}

void
TZPainterWindow::OnMenuSelection( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnMenuSelection", "" );
#endif

   zLONG lZKey;
   zVIEW vDialogOpt;

   // This view must exist or else we couldn't be here.
   GetViewByName( &vDialogOpt, szlTZWINDOW, m_vDialog, zLEVEL_TASK );
   SetViewFromView( vDialogOpt, m_vDialog );

   // Position on first Menu in window that is the same as DfltMenu.
   while ( ResetViewFromSubobject( vDialogOpt ) == 0 )
   {
   }

   if ( CheckExistenceOfEntity( vDialogOpt, "DfltMenu" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lZKey, vDialogOpt, "DfltMenu", "ZKey" );
      SetCursorFirstEntityByInteger( vDialogOpt, "Menu", "ZKey", lZKey, 0 );
   }

   CreateTemporalSubobjectVersion( vDialogOpt, szlMenu );
   m_pBar->ResetSelectedMouseReleaseSwap( );
   SetWindowActionBehavior( m_pBar->m_vSubtask,
                            zWAB_StartModalSubwindow,
                            szlTZPNTRAD, szlUPD_MENU );
   m_pBar->EnablePainterWindows( 0 );
   ProcessActionLoop( m_pBar->m_pZSubtask,
                      0, 0, 0, 0, FALSE, "(pntr menu)" );
}

// Message cracker for message WM_SETFOCUS
void
TZPainterWindow::OnSetFocus( CWnd *pWndLostFocus )
{
#ifdef DEBUG_ALL
// TraceLineS( "TZPainterWindow::OnSetFocus", "" );
#endif

// zVIEW vTZWND_LIST;
   zVIEW vTZWINDOWL;
   zVIEW vWindow;

   // WM_SETFOCUS set current painter pointer
   m_pBar->m_pActivePainterWindow = this;
   if ( MiValidView( m_vDialog ) )
   {
      zPCHAR  pchWindowPage;

      if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
         pchWindowPage = szlPage;
      else
         pchWindowPage = szlWindow;

      SetNameForView( m_vDialog, szlTZWINDOW, 0, zLEVEL_TASK );
//    if ( GetViewByName( &vTZWND_LIST, szlTZWND_LIST, m_vDialog, zLEVEL_TASK ) > 0 &&
      if ( GetViewByName( &vTZWINDOWL, szlTZWINDOWL, m_vDialog, zLEVEL_TASK ) > 0 )
      {
         zVIEW vDialog;

         CreateViewFromViewForTask( &vDialog, m_vDialog, m_vDialog );
         SetViewFromView( vDialog, m_vDialog );
         while ( ResetViewFromSubobject( vDialog ) == 0 )
         {
         }

         SetAllSelStatesForEntityForSet( vTZWINDOWL, pchWindowPage, 0, 1, 0 );
         SetCursorFirstEntityByEntityCsr( vTZWINDOWL, pchWindowPage,
                                          vDialog, pchWindowPage, 0 );
         DropView( vDialog );
         SetSelectStateOfEntityForSet( vTZWINDOWL, pchWindowPage, 1, 1 );

         //BL, 1999.11.24 Refresh Action List.
         if ( GetSubtaskForWindowName( m_pBar->m_vSubtask,
                                       &vWindow, "LIST_ACT" ) >= 0 )
         {
            RefreshWindow( vWindow );
         }

         // Refresh Shortcut List
         if ( GetSubtaskForWindowName( m_pBar->m_vSubtask,
                                       &vWindow, "LIST_HK" ) >= 0 )
         {
            RefreshWindow( vWindow );
         }

         // Refresh Menu List.
         if ( GetSubtaskForWindowName( m_pBar->m_vSubtask,
                                       &vWindow, "LIST_MENU" ) >= 0 )
         {
            RefreshWindow( vWindow );
         }

#if 0
         RefreshCtrl( vTZWND_LIST, "ListBox1" );
#else
         zPCHAR pchTag;

         GetAddrForAttribute( &pchTag, vTZWINDOWL, pchWindowPage, szlTag );
//       TraceLineS( "TZPainterWindow::OnSetFocus Window: ", pchTag );
         m_pBar->m_wndListWindows.SelectString( -1, pchTag );
         m_pBar->LoadActionList( pchTag );
#endif
      }
//    else
//       MessageBox( "SetFocus view not found", szlTZWINDOWL );
   }

   // I don't know why, but if the CFrameWnd::OnSetFocus handler is called
   // instead of Default, keystroke handling is screwed up for things such
   // as sizing and moving ctrls using the arrow keys.
// CFrameWnd::OnSetFocus( pWndLostFocus );
   Default( );
}

void
TZPainterWindow::OnKillFocus( CWnd *pWndGetFocus )
{
#ifdef DEBUG_ALL
// TraceLineS( "TZPainterWindow::OnKillFocus", "" );
#endif

   CFrameWnd::OnKillFocus( pWndGetFocus );
}

void
TZPainterWindow::BuildTZPNEVWO( )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::BuildTZPNEVWO", "" );
#endif

   zVIEW vTZPESRCO;
   zVIEW vCtrl;
   zVIEW vCtrlTemp;
   zVIEW vEvents;
   zLONG lType;
   zLONG lEventType;

   if ( GetViewByName( &vEvents, szlTZPNEVWO, m_vDialog, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vEvents );

   if ( GetViewByName( &vCtrl, szlTZCONTROL, m_vDialog, zLEVEL_TASK ) < 1 ||
        GetViewByName( &vTZPESRCO, szlTZPESRCO, m_vDialog, zLEVEL_TASK ) < 1 )
   {
      return;
   }

   if ( CheckExistenceOfEntity( vCtrl, szlControlDef ) <= zCURSOR_UNCHANGED )
      return;

// if ( m_pCurrCtrl == 0 )
   {
      TZPainterCtrl *pCtrl;
      zLONG  lZKey;
      zSHORT nPos;

      GetIntegerFromAttribute( &lZKey, vCtrl, szlControl, szlZKey );
      for ( nPos = 0; nPos < m_nCtrlCnt; )
      {
         pCtrl = m_CtrlList[ nPos ];
         if ( pCtrl->m_lZKey == lZKey )
            m_pCurrCtrl = pCtrl;
            break;
      }
   }

   CreateViewFromViewForTask( &vCtrlTemp, vCtrl, m_vDialog );
   while ( ResetViewFromSubobject( vCtrlTemp ) == 0 )
   {
   }

   ActivateEmptyObjectInstance( &vEvents, szlTZPNEVWO, m_vDialog, zMULTIPLE );
   SetNameForView( vEvents, szlTZPNEVWO, 0, zLEVEL_TASK );

   // Now copy all the events from the ctrl definition to the event work
   // object.
   GetIntegerFromAttribute( &lType, vCtrl, szlControlDef, szlKey );
   SetCursorFirstEntityByInteger( vTZPESRCO, szlControlDef,
                                  szlKey, lType, 0 );
   zSHORT nRC = SetCursorFirstEntity( vTZPESRCO, szlCtrlEventDef, 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      CreateEntity( vEvents, szlEvent, zPOS_AFTER );
      SetMatchingAttributesByName( vEvents, szlEvent,
                                   vTZPESRCO, szlCtrlEventDef, zSET_ALL );
   // DisplayEntityInstance( vEvents, szlEvent );
      CreateEntity( vEvents, szlEventAct, zPOS_AFTER );
      GetIntegerFromAttribute( &lEventType, vEvents, szlEvent, szlType );
      if ( SetCursorFirstEntityByInteger( vCtrl, szlEvent, szlType,
                                          lEventType, 0 ) > zCURSOR_UNCHANGED )
      {
         if ( CheckExistenceOfEntity( vCtrl,
                                      szlEventAct ) > zCURSOR_UNCHANGED )
         {
            SetMatchingAttributesByName( vEvents, szlEventAct,
                                         vCtrl, szlEventAct, zSET_ALL );
            SetCursorFirstEntityByEntityCsr( vCtrlTemp, szlAction,
                                             vCtrl, szlEventAct, "" );

            if ( CheckExistenceOfEntity( vCtrlTemp,
                                         "ActOper" ) > zCURSOR_UNCHANGED )
            {
               SetAttributeFromAttribute( vEvents, szlEventAct, "Operation",
                                          vCtrlTemp, "ActOper", szlName );
            }

         // DisplayEntityInstance( vEvents, szlEventAct );
         }
      }

      nRC = SetCursorNextEntity( vTZPESRCO, szlCtrlEventDef, 0 );
   }

   SetCursorFirstEntity( vTZPESRCO, szlCtrlEventDef, 0 );
   if ( CheckExistenceOfEntity( vEvents, szlEvent ) > zCURSOR_UNCHANGED )
      SetCursorFirstEntity( vEvents, szlEvent, 0 );

   DropView( vCtrlTemp );
// DisplayObjectInstance( vEvents, 0, 0 );
}

typedef zSHORT (POPERATION zFARPROC_CREATEMETAENTITY)( zVIEW, zVIEW, zPCHAR, zSHORT );

zSHORT
TZPainterWindow::CreateMetaEntity( zVIEW  vDlg,
                                   zPCHAR pchEntity,
                                   zSHORT nPos )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::CreateMetaEntity", "" );
#endif

   zFARPROC_CREATEMETAENTITY lpfnDynRoutine;
   LPLIBRARY lpLibrary = 0;
   zSHORT    nRC = -1;

   lpfnDynRoutine = (zFARPROC_CREATEMETAENTITY)
      GetOperationDynamicCallAddress( m_pBar->m_vSubtask, &lpLibrary,
                                      "tzlodopr", "CreateMetaEntity",
                                      "(tzctlptr Meta)" );
   if ( lpfnDynRoutine )
   {
      nRC = (*lpfnDynRoutine)( m_pBar->m_vSubtask, vDlg, pchEntity, nPos );
      if ( nRC >= 0 )
         return( nRC );
   }

   TraceLineS( "(ptr) Could not create entity ", pchEntity );
// MessageBox( "Could not create entity", pchEntity );  // debug only
   return( nRC );
}

// TZPainterWindow - menu pre-dropdown
void
TZPainterWindow::OnInitMenu( CMenu *pMenu )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnInitMenu", "" );
#endif

// This default handler disables menu items ... we want control of this ...
// so we do not call the default handler.
// CFrameWnd::OnInitMenu( hMenu );
}

void
TZPainterWindow::OnInitMenuPopup( CMenu *pPopupMenu,
                                  UINT nIndex, BOOL bSysMenu )
{
#ifdef DEBUG_ALL
   TraceLineI( "TZPainterWindow::OnInitMenuPopup bSysMenu: ", bSysMenu );
#endif

   if ( bSysMenu || pPopupMenu == 0 )
   {
      Default( );
      return;
   }

// This default handler disables menu items ... we want control of this ...
// so we do not call the default handler.
// CFrameWnd::OnInitMenuPopup( hPopupMenu, nIndex, bSysMenu );
}

BOOL
TZPainterWindow::PreTranslateMessage( MSG *pMsg )
{
#ifdef DEBUG_ALL
// TraceLineI( "TZPainterWindow::PreTranslateMessage: ", pMsg->message );
#endif

   // Try to dismiss the current "drag" or "new ctrl" operation.
   if ( pMsg->message == WM_SYSKEYDOWN || pMsg->message == WM_KEYDOWN )
   {
      if ( pMsg->wParam == VK_ESCAPE )
      {
      // TraceLineS( "TZPainterWindow::PreTranslateMessage ", "VK_ESCAPE" );
         if ( m_pCurrCtrl )
         {
            UINT   uModKeys = 0;
            LPARAM lParam;
            CPoint pt = m_pCurrCtrl->m_ptLastMouseMove;

            if ( m_pCurrCtrl->m_bShiftKey )
               uModKeys |= MK_SHIFT;

            if ( m_pCurrCtrl->m_bCtrlKey )
               uModKeys |= MK_CONTROL;

            lParam = MAKELPARAM( m_pCurrCtrl->m_ptMouseSelect.x,
                                 m_pCurrCtrl->m_ptMouseSelect.y );

            // Post a button-up to cancel the current move (0xFFFFFFFF).
            if ( m_pCurrCtrl->m_pCtrlCover )
            {
               m_pCurrCtrl->m_pCtrlCover->PostMessage( WM_MOUSEMOVE,
                                                       uModKeys, lParam );
               m_pCurrCtrl->m_pCtrlCover->PostMessage( WM_LBUTTONUP,
                                                       uModKeys, 0xFFFFFFFF );
            }

            lParam = MAKELPARAM( pt.x, pt.y );
            PostMessage( WM_MOUSEMOVE, uModKeys, lParam );
            return( TRUE ); // the message was translated and should not be dispatched
         }
      }

      if ( pMsg->message == WM_KEYDOWN &&
           (pMsg->wParam == 'Z' || pMsg->wParam == 'Y' || pMsg->wParam == 'S' || pMsg->wParam == 'J' ||
            pMsg->wParam == 'C' || pMsg->wParam == 'V' || pMsg->wParam == 'X' || pMsg->wParam == 'A') &&
           (GetKeyState( VK_CONTROL ) < 0) &&
           (GetKeyState( VK_MENU ) >= 0) &&
           (GetKeyState( VK_SHIFT ) >= 0) )
      {
         if (pMsg->wParam == 'S')
         {
            // KJS 5/23/17 - Ctrl+S, Saves the Dialog
            PainterCall(zMSG_SAVEDIALOG, 0, m_pBar, 0, 0, 0);
            return(TRUE); // the message was translated and should not be dispatched
         }
         if (pMsg->wParam == 'J')
         {
            // KJS 5/23/17 - Ctrl+J, calls GenerateJSPJava, generates the current window.
            PainterCall(zMSG_GENERATEJAVAJSP, 0, m_pBar, 0, 0, 0);
            return(TRUE); // the message was translated and should not be dispatched
         }
         if (pMsg->wParam == 'A')
         {
            // KJS 5/23/17 - Ctrl+A, calls GenerateAllJSPJava, generates all windows.
            PainterCall(zMSG_GENERATEALLJAVAJSP, 0, m_pBar, 0, 0, 0);
            return(TRUE); // the message was translated and should not be dispatched
         }

         if ( (pMsg->wParam == 'Z' || pMsg->wParam == 'Y') )
         {
         // TraceLineS( "tzctlptr Undo/Redo", "" );
            MoveToUndoRedo( (pMsg->wParam == 'Z') ? FALSE : TRUE );
            return( TRUE ); // the message was translated and should not be dispatched
         }
         else
         if ( (pMsg->wParam == 'C' || pMsg->wParam == 'V') )
         {
         // TraceLineS( "tzctlptr Copy/Paste", "" );
            zSHORT nMessage = (pMsg->wParam == 'C') ? zMSG_CLIPBOARD_COPY :
                                                      zMSG_CLIPBOARD_PASTE;
            PainterCall( nMessage, 0, m_pBar, 0, 0, 0 );
            return( TRUE ); // the message was translated and should not be dispatched
         }
      }
   }

   return( CFrameWnd::PreTranslateMessage( pMsg ) ); // process accelerators
}

// Message cracker for message WM_KEYDOWN
void
TZPainterWindow::OnKeyDown( UINT uKey, UINT uRepeatCnt, UINT uFlags )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnKeyDown", "" );
// if ( uKey != VK_CONTROL )
//    TraceLineS( "TZPainterWindow::OnKeyDown", "" );
#endif

   zBOOL bAlt = ((uFlags & KF_ALTDOWN) != 0);
   zBOOL bCtrlKey = (GetKeyState( VK_CONTROL ) < 0);
   zBOOL bShiftKey = (GetKeyState( VK_SHIFT ) < 0);

   m_fWndState &= ~(zTZPW_SHIFT_KEY | zTZPW_CTRL_KEY);
   if ( bShiftKey )
      m_fWndState |= zTZPW_SHIFT_KEY;

   if ( bCtrlKey )
      m_fWndState |= zTZPW_CTRL_KEY;

   if ( uKey == VK_SHIFT )
   {
      m_fWndState |= zTZPW_SHIFT_KEY;
   }
   else
   if ( uKey == VK_CONTROL )
   {
      m_fWndState |= zTZPW_CTRL_KEY;
   }
   else
   if ( uKey == 'R' )
   {
      if ( m_fWndState & zTZPW_CTRL_KEY )
      {
         SetZeidonWindowPosition( );
      }
   }
   else
   if ( uKey == 'P' )
   {
      if ( bAlt )
      {
         ShowZeidonWindowPosition( );
      }
      else
      if ( m_fWndState & zTZPW_CTRL_KEY )
      {
//       if ( OperatorPrompt( m_pBar->m_vSubtask,
//                            "Print Window",
//                            "OK to print Window?\n( Ctrl+R to reposition )",
//                            0, zBUTTONS_YESNO, zRESPONSE_YES,
//                            0 ) == zRESPONSE_YES )
//       {
            PrintActiveWindow( m_pBar->m_vSubtask );
//       }
      }
   }
   else
   if ( uKey == VK_DELETE )
   {
      // If the delete key has been struck, delete all selected ctrls.
      DeleteSelectedCtrls( );
   }
   else
// if ( ( uKey == VK_BACK || uKey == VK_TAB ) && m_vDialog )
   if ( uKey == VK_TAB && m_vDialog )
   {
      // If the user hits tab or backtab, go to the previous or
      // next active painter window.
      TZPainterWindow *m_pPainterWindow;
      zSHORT   nPos;
      for ( nPos = 0; nPos < m_pBar->m_nWndCnt; nPos++ )
      {
         if ( this == m_pBar->m_PainterWindowList[ nPos ] )
         {
            break;
         }
      }

//    if ( uKey == VK_BACK )
      if ( m_fWndState & zTZPW_SHIFT_KEY )
      {
         if ( nPos > 0 )
            nPos--;
         else
         {
            nPos = m_pBar->m_nWndCnt - 1;
            if ( nPos < 0 )
               nPos = 0;
         }
      }
      else
      {
         if ( nPos < m_pBar->m_nWndCnt - 1 )
            nPos++;
         else
            nPos = 0;
      }

      m_pPainterWindow = m_pBar->m_PainterWindowList[ nPos ];
      m_pBar->m_pActivePainterWindow = m_pPainterWindow;

      // Copy the shift and ctrl info from this window to the next window.
      if ( m_pPainterWindow != this )
      {
         if ( m_fWndState & zTZPW_CTRL_KEY )
         {
            m_pPainterWindow->m_fWndState |= zTZPW_CTRL_KEY;
            m_fWndState &= ~zTZPW_CTRL_KEY;
         }
         else
            m_pPainterWindow->m_fWndState &= ~zTZPW_CTRL_KEY;

         if ( m_fWndState & zTZPW_SHIFT_KEY )
         {
            m_pPainterWindow->m_fWndState |= zTZPW_SHIFT_KEY;
            m_fWndState &= ~zTZPW_SHIFT_KEY;
         }
         else
            m_pPainterWindow->m_fWndState &= ~zTZPW_SHIFT_KEY;

         m_pPainterWindow->SetActiveWindow( );
      }
   }
   else
   if ( (m_fWndState & (zTZPW_SHIFT_KEY | zTZPW_CTRL_KEY)) &&
        (uKey == VK_LEFT  || uKey == VK_UP ||
         uKey == VK_RIGHT || uKey == VK_DOWN) )
   {
   // TraceLineI( "TZPainterWindow::OnKeyDown m_nSelectCnt: ", m_nSelectCnt );
      if ( m_nSelectCnt )
      {
         zSHORT      nPos;
         zLONG       lPixels;
         TZPainterCtrl *pCtrl;
         CRect       rect;

         // prevent AdjustGroupSets until all have moved
         m_pPainterClient->m_nRecurse += 2;

         if ( m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
         {
            if ( uKey == VK_LEFT  || uKey == VK_RIGHT )
               lPixels = mConvert256thInchToPixelX( m_nGranularity );
            else
               lPixels = mConvert256thInchToPixelY( m_nGranularity );
         }
         else
         {
            if ( m_pBar->m_bUseMapDlgUnits )
            {
               if ( uKey == VK_LEFT  || uKey == VK_RIGHT )
                  lPixels = mConvertMapDlgToPixelX( 1 );
               else
                  lPixels = mConvertMapDlgToPixelY( 1 );
            }
            else
            {
               if ( uKey == VK_LEFT  || uKey == VK_RIGHT )
                  lPixels = mConvertDlgUnitToPixelX( 1 );
               else
                  lPixels = mConvertDlgUnitToPixelY( 1 );
            }
         }

         if ( (m_fWndState & zTZPW_SHIFT_KEY) &&
              (m_fWndState & zTZPW_CTRL_KEY) )
         {
            lPixels <<= 3;  // move 8 times as fast
         }

         for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
         {
            pCtrl = m_CtrlList[ nPos ];
            if ( pCtrl->IsSelected( ) )
            {
            // TraceLineI( "TZPainterWindow::OnKeyDown nPixels: ", nPixels );

               // Now get the new rect for the ctrl.
               pCtrl->ParentToPainterRect( rect );
            // TraceRect( "TZPainterWindow::OnKeyDown PainterRect:", rect );
               if ( uKey == VK_LEFT )
               {
                  if ( m_fWndState & zTZPW_SHIFT_KEY )
                  {
                     rect.left -= lPixels;
                     rect.right -= lPixels;
                  }
                  else
                     rect.right -= lPixels;
               }
               else
               if ( uKey == VK_UP )
               {
                  if ( m_fWndState & zTZPW_SHIFT_KEY )
                  {
                     rect.top -= lPixels;
                     rect.bottom -= lPixels;
                  }
                  else
                     rect.bottom -= lPixels;
               }
               else
               if ( uKey == VK_RIGHT )
               {
                  if ( m_fWndState & zTZPW_SHIFT_KEY )
                  {
                     rect.left += lPixels;
                     rect.right += lPixels;
                  }
                  else
                     rect.right += lPixels;
               }
               else
            // if ( uKey == VK_DOWN )
               {
                  if ( m_fWndState & zTZPW_SHIFT_KEY )
                  {
                     rect.top += lPixels;
                     rect.bottom += lPixels;
                  }
                  else
                     rect.bottom += lPixels;
               }

               // We now have the new position and dimensions of the ctrl.
            // TraceRect( "TZPainterWindow::OnKeyDown MoveRect:", rect );
               if ( bAlt )
               {
                  TZPainterCtrl *pNewParent =
                           pCtrl->ValidateParentObject( rect, pCtrl->m_lType,
                                                        zCTRL_VALID_MOVE );
                  pCtrl->m_pCtrlCover->MoveCtrl( rect, pNewParent );
               }
               else
               {
               // TraceLineS( "TZPainterWindow::OnKeyDown MoveCtrl", "" );
                  pCtrl->m_pCtrlCover->MoveCtrl( rect );
               }
            }
         }

         m_pPainterClient->m_nRecurse -= 2;  // permit AdjustGroupSets
         m_pPainterClient->AdjustGroupSets( );
      }
   }

   Default( );
}

// Message cracker for message WM_SYSKEYDOWN
void
TZPainterWindow::OnSysKeyDown( UINT uKey, UINT uRepeatCnt, UINT uFlags )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnSysKeyDown", "" );
#endif

   OnKeyDown( uKey, uRepeatCnt, uFlags );
}

// Message cracker for message WM_KEYUP
void
TZPainterWindow::OnKeyUp( UINT uKey, UINT uRepeatCnt, UINT uFlags )
{
#ifdef DEBUG_ALL
   TraceLineS( "TZPainterWindow::OnKeyUp", "" );
#endif

   if ( uKey == VK_SHIFT )
      m_fWndState &= ~zTZPW_SHIFT_KEY;
   else
   if ( uKey == VK_CONTROL )
      m_fWndState &= ~zTZPW_CTRL_KEY;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// If pCtrl is null, get the first child ctrl, else get the next child ctrl.
TZPainterCtrl *
TZPainterWindow::GetChildCtrl( TZPainterCtrl *pCtrlParent,
                               TZPainterCtrl *pCtrl )
{
   if ( pCtrlParent->m_nChildren )
   {
      for ( zSHORT nPos = 0; nPos < m_nCtrlCnt; nPos++ )
      {
         if ( m_CtrlList[ nPos ]->m_pCtrlParent == pCtrlParent )
         {
            if ( pCtrl == 0 )
            {
               pCtrl = m_CtrlList[ nPos ];
               return( pCtrl );
            }
            else
            if ( pCtrl == m_CtrlList[ nPos ] )
               pCtrl = 0;
         }
      }
   }

   return( 0 );
}
