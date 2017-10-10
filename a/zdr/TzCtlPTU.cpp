/////////////////////////////////////////////////////////////////////////////
// Project TzCtl
//
// This is a part of the Zeidon Dynamic Rendering of GUI applications package.
// Copyright © 1995 - 2016 QuinSoft, Inc.
// All Rights Reserved.
//
// SUBSYSTEM:    tzctl.dll - ZDr Design Control implementations
// FILE:         tzctlptu.cpp
// AUTHOR:
//
// OVERVIEW
// ========
// Source file for implementation of C 'wrappers' for Painter's TZToolBar
// painter controls.

//
// CHANGE LOG - most recent first order
//
// 200y.mm.dd    xxx
//    Note ...
//
// 2002.07.25  FH
//    Use zMSG_REPAINTALLZEIDONWINDOWS for resize of dialog in dialog painter.
//
// 2001.04.19    DKS   Z10
//    Change to use MapRect units as base for conversion to dialog units.
//
// 2000.12.27    BL    Z10  RAD 54041
//    Modified Shortcut for Undo (Ctrl+Z, not Ctrl+U) and Redo (Ctrl+Y,
//    not Ctrl+D)
//
// 2000.09.21    BL    Z10  RAD 53746
//    Modified PainterCall for Menu Format in Dialog Painter
//    (=Format Controls)
//
// 2000.06.05    DKS   Z10
//    Load the Task LPLR view once (performance enhancement).
//
// 1999.11.22    DKS   Z10    QS999
//    Altered copy/paste logic to permit direct copies.
//
// 1999.03.10    DKS
//    UPDATEACTIVEWINDOWNAME uses the proper variable.
//
// 1999.02.10    DKS
//    Added zMSG_CLIPBOARD_COPY and zMSG_CLIPBOARD_PASTE cases to
//    PainterCall in support of Copy/Paste functionality.
//
// 1999.01.27    DKS
//    Removed "#if 0" code.
//
// 1999.01.21    DKS
//    Holding on to last window updated across update iterations.
//
// 1998.12.29    DKS
//    Added zMSG_ISREPORT case to PainterCall.
//
// 1998.09.23    DKS
//    New Window added to WindowList (TB 216).
//    Select active window in WindowList (TB 217).
//    Registered views and Operation Maintenance still available even
//    when all windows are closed (XC 249 & XC 261).
//
// 1998.08.13    DKS
//    Fix to Tab control acceptance by GroupBox (now warns)
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
// #define zTEST_UPDATED_FLAG

typedef zSHORT(POPERATION zFARPROC_PNTR)(zVIEW);

zLONG  OPERATION
PainterCall( zSHORT nMessage,
             zVIEW  vTZPNTROO,
             TZPainterBar *pPainterBar,
             zVIEW  vDialog,
             zPCHAR pchParm,
             zLONG  lMaxLth )
{
#ifdef DEBUG_ALL
   TraceLineI( "PainterCall msg: ", nMessage );
#endif

   TZPainterWindow *pPainterWindow;
   TZPainterWindow *pActivePainterWindow;
   zSHORT          nPos;
   zULONG          ulBlobMax;
// zVIEW           vWindow;
// zLONG           lZKey;
   zPCHAR          pchWindowName;
   zPCHAR          pchWindowPage;
   zPCHAR          pchWINDOWL_PAGEL;

   // Get the currently active dialog view.
   if ( pPainterBar && vDialog == 0 && nMessage != zMSG_UPDATE_COMMON_DETAIL )
      GetViewByName( &vDialog, szlTZWINDOW, pPainterBar->m_vSubtask, zLEVEL_TASK );

   if ( vTZPNTROO == 0 )
      GetViewByName( &vTZPNTROO, szlTZPNTROO, vDialog, zLEVEL_TASK );

   if ( pPainterBar == 0 && vTZPNTROO )
   {
      ulBlobMax = sizeof( zPVOID );
      GetBlobFromAttribute( &pPainterBar, &ulBlobMax, vTZPNTROO,
                            szlPalette, szlPointer );
   }

   if ( pPainterBar == 0 )
      return( 0 );

   if ( pPainterBar->m_fState & zTZCB_XSLT )
   {
      pchWindowPage = szlXSLT;
      pchWINDOWL_PAGEL = szlXSLTL;
   }
   else
   if ( pPainterBar->m_fState & zTZCB_REPORT )
   {
      pchWindowPage = szlPage;
      pchWINDOWL_PAGEL = szlPAGEL;
   }
   else
   {
      pchWindowPage = szlWindow;
      pchWINDOWL_PAGEL = szlTZWINDOWL;
   }

   switch ( nMessage )
   {
//    case zMSG_PUTTOOLBOXONTOP:
//       TraceLineS( "zMSG_PUTTOOLBOXONTOP is obsolete", "" );
//       break;

      case zMSG_DELETE_SELECTED:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - AlignSelectedCtrls for DeleteControls - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->DeleteSelectedCtrls( );

         break;

      case zMSG_GET_NEXT_SELECTED_CTRL:
      {
         if ( pPainterBar->m_pActivePainterWindow )
         {
            TZPainterCtrl *pCtrl;
            zSHORT nPos = *((zPSHORT) pchParm) + 1;

            *((zPSHORT) pchParm) = -1;
            while ( nPos < pPainterBar->m_pActivePainterWindow->m_nCtrlCnt )
            {
               pCtrl = pPainterBar->m_pActivePainterWindow->m_CtrlList[ nPos ];
               if ( pCtrl->IsSelected( ) )
               {
                  pCtrl->PositionOnZeidonCtrl( vDialog );
                  *((zPSHORT) pchParm) = nPos;
                  break;
               }

               nPos++;
            }

            if ( *((zPSHORT) pchParm) == -1 )
               pPainterBar->ResetSelectedMouseReleaseSwap( );
         }

         break;
      }

      case zMSG_ABUT_HORIZONTAL:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - AbutSelectedCtrls for AbutHorizontal - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->AbutSelectedCtrls( zABUT_HORIZONTAL );

         break;

      case zMSG_ABUT_VERTICAL:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - AbutSelectedCtrls for AbutVertical - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->AbutSelectedCtrls( zABUT_VERTICAL );

         break;

      case zMSG_EQUAL_SPACE_HORIZONTAL:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - EqualSpaceSelectedCtrls for EquiSpaceHorizontal - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->EqualSpaceSelectedCtrls( zEQUAL_HSPACE );

         break;

      case zMSG_EQUAL_SPACE_VERTICAL:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - EqualSpaceSelectedCtrls for EquiSpaceVertical - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->EqualSpaceSelectedCtrls( zEQUAL_VSPACE );

         break;

      case zMSG_SIZE_WIDTH_HEIGHT:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - SizeSelectedCtrls for EqualWidthAndHeight - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->SizeSelectedCtrls( zSIZE_BOTH );

         break;

      case zMSG_SIZE_WIDTH:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - SizeSelectedCtrls for EqualWidth - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->SizeSelectedCtrls( zSIZE_WIDTH );

         break;

      case zMSG_SIZE_HEIGHT:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - SizeSelectedCtrls for EqualHeight - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->SizeSelectedCtrls( zSIZE_HEIGHT );

         break;

      case zMSG_ALIGN_BOTTOM:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - AlignSelectedCtrls for AlignBottom - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->AlignSelectedCtrls( zALIGN_BOTTOM );

         break;

      case zMSG_ALIGN_TOP:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - AlignSelectedCtrls for AlignTop - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->AlignSelectedCtrls( zALIGN_TOP );

         break;

      case zMSG_ALIGN_LEFT:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - AlignSelectedCtrls for AlignLeft - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->AlignSelectedCtrls( zALIGN_LEFT );

         break;

      case zMSG_ALIGN_RIGHT:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - AlignSelectedCtrls for AlignRight - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->AlignSelectedCtrls( zALIGN_RIGHT );

         break;

      case zMSG_EMPTYALLPAINTERWINDOWS:
         pPainterBar->EmptyAllPainterWindows( pchParm );
         break;

      case zMSG_DELETEALLPAINTERWINDOWS:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - DeleteAllPainterWindows  - ", ObjectInstanceUpdated( vDialog ) );
         TraceLineI( "PainterCall - DeleteAllPainterWindows cnt: ", pPainterBar->m_nWndCnt );
#endif
         pPainterBar->DeleteAllPainterWindows( );
         if ( pchParm )
         {
            if ( pPainterBar->m_vTaskLPLR )
            {
               SfDropSubtask( pPainterBar->m_vTaskLPLR, 0 );
               pPainterBar->m_vTaskLPLR = 0;
               pPainterBar->m_csLPLR_Name = "";
            }
         }

         vDialog = 0; // for TraceLineI at Termination
         break;

      case zMSG_DELETECURRENTPAINTERWINDOW:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - DeleteCurrentPainterWindow - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->SendMessage( WM_CLOSE, 0, 0 );

         break;

      case zMSG_CREATEZEIDONWINDOW:    // Create and paint a painter window
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - CreateZeidonWindow - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( CheckExistenceOfEntity( vDialog, pchWindowPage ) == 0 )
         {
            zVIEW vDialogL;

            pPainterWindow = new TZPainterWindow( pPainterBar, vDialog, FALSE );
            if ( GetViewByName( &vDialogL, pchWINDOWL_PAGEL,
                                pPainterBar->m_vSubtask, zLEVEL_TASK ) > 0 &&
                 (vDialogL == vDialog ||
                  SetCursorFirstEntityByEntityCsr( vDialogL, pchWindowPage,
                                                   vDialog, pchWindowPage,
                                                   0 ) >= zCURSOR_SET) &&
                 GetSelectStateOfEntityForSet( vDialogL,
                                               pchWindowPage, 1 ) == 0 )
            {
               SetAllSelStatesForEntityForSet( vDialogL, pchWindowPage, 0, 1, 0 );
               SetSelectStateOfEntityForSet( vDialogL, pchWindowPage, 1, 1 );
//             TraceLineS( "TZPainterWindow::CREATEZEIDONWINDOW: ",
//                         "LoadWindowList" );
               pPainterBar->LoadWindowList( );
            }
         }

         break;

      case zMSG_REPAINTZEIDONCONTROL:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - RepaintZeidonCtrl - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
         {
            pPainterBar->m_pActivePainterWindow->RepaintZeidonCtrl( );
            pPainterBar->m_pActivePainterWindow->SetActiveWindow( );
         }

         break;

      case zMSG_UPDATEZEIDONWINDOW:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - UpdateZeidonWindow - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->UpdateZeidonWindow( );

         break;

      case zMSG_UPDATEALLZEIDONWINDOWS:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - UpdateAllZeidonWindows - ", ObjectInstanceUpdated( vDialog ) );
#endif
         for ( nPos = 0; nPos < pPainterBar->m_nWndCnt; nPos++ )
         {
            pPainterWindow = pPainterBar->m_PainterWindowList[ nPos ];
            pPainterWindow->UpdateZeidonWindow( );
         }

         break;

      case zMSG_ACTIVATEPAINTERWINDOW:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - ActivatePainterWindow", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
         {
            pPainterBar->m_pActivePainterWindow->SetActiveWindow( );
         }

         break;

      case zMSG_REPAINTZEIDONWINDOW:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - RepaintZeidonWindow - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->PaintZeidonWindow( pchParm ? TRUE : FALSE );

         break;

      case zMSG_REPAINTALLZEIDONWINDOWS:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - RepaintAllZeidonWindows - ", ObjectInstanceUpdated( vDialog ) );
#endif
         // Keep track of the active window.
         TZPainterWindow *m_pOldActivePainterWindow;

         m_pOldActivePainterWindow = pPainterBar->m_pActivePainterWindow;
         for ( nPos = 0; nPos < pPainterBar->m_nWndCnt; nPos++ )
         {
            if ( pPainterBar->m_pActivePainterWindow )
            {
               pPainterWindow = pPainterBar->m_PainterWindowList[ nPos ];
               pPainterWindow->PaintZeidonWindow( );
            }
         }

         // Reset to the active window.
         pPainterBar->m_pActivePainterWindow = m_pOldActivePainterWindow;

         break;

      case zMSG_REPAINTACTIONBAR:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - RepaintActionBar - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->PaintActionBar( );

         break;

      case zMSG_GETWINDOWBYNAME:
         pPainterWindow = 0;
         for ( nPos = 0; nPos < pPainterBar->m_nWndCnt; nPos++ )
         {
            pPainterWindow = pPainterBar->m_PainterWindowList[ nPos ];
            if ( zstrcmp( pPainterWindow->m_csWndTag.GetString(), pchParm ) == 0 )
               break;
         }

         return( (zLONG) pPainterWindow );

      case zMSG_UPDATEWINDOWBYNAME:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - UpdateWindowByName - ", ObjectInstanceUpdated( vDialog ) );
#endif
         pPainterWindow = 0;
         for ( nPos = 0; nPos < pPainterBar->m_nWndCnt; nPos++ )
         {
            pPainterWindow = pPainterBar->m_PainterWindowList[ nPos ];
            if ( zstrcmp( pPainterWindow->m_csWndTag.GetString(), pchParm ) == 0 )
            {
               pPainterBar->m_pActivePainterWindow = pPainterWindow;
               pPainterBar->m_pActivePainterWindow->SetActiveWindow( );
               break;
            }

            pPainterWindow = 0;
         }

         if ( pPainterWindow == 0 )
         {
            // Get the window list view.
            GetViewByName( &vDialog, pchWINDOWL_PAGEL, pPainterBar->m_vSubtask, zLEVEL_TASK );
            if ( SetCursorFirstEntityByString( vDialog, pchWindowPage, szlTag,
                                               pchParm, 0 ) == zCURSOR_SET )
            {
               // Create and paint a painter window.
               pPainterWindow = new TZPainterWindow( pPainterBar,
                                                     vDialog, TRUE );

               // Re-establish position.
               if ( SetCursorFirstEntityByString( vDialog, pchWindowPage,
                                                  szlTag, pchParm,
                                                  0 ) == zCURSOR_SET )
               {
                  SetAllSelStatesForEntityForSet( vDialog, pchWindowPage,
                                                  0, 1, 0 );
                  SetSelectStateOfEntityForSet( vDialog, pchWindowPage,
                                                1, 1 );
//                TraceLineS( "TZPainterWindow::UPDATEWINDOWBYNAME: ", "LoadWindowList" );
                  pPainterBar->LoadWindowList( );
               }

               return( 0 );
            }
            else
               return( -1 );
         }

         break;

      case zMSG_GETACTIVEWINDOWNAME:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - GetActiveWindowName - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            strcpy_s( pchParm, zTAG_LTH, pPainterBar->m_pActivePainterWindow->m_csWndTag );
         else
            pchParm[ 0 ] = 0;

         break;

      case zMSG_UPDATEACTIVEWINDOWNAME:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - UpdateActiveWindowName - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->m_csWndTag = pchParm;

         break;

      case zMSG_ENABLEPAINTERWINDOWS:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - EnablePainterWindows - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pchParm )
         {
            pPainterBar->EnablePainterWindows( 1 );
//          TraceLineS( "TZPainterWindow::ENABLEPAINTERWINDOWS: ",
//                      "LoadWindowList" );
            pPainterBar->LoadWindowList( );  // this sets the update flag for the dialog
         }
         else
            pPainterBar->EnablePainterWindows( 0 );

         if ( pPainterBar->m_pZSubtask && pPainterBar->m_pZSubtask->m_pZFWnd )
         {
            pPainterBar->m_pZSubtask->m_pZFWnd->Invalidate( );
            pPainterBar->m_pZSubtask->m_pZFWnd->PostMessage( WM_NCPAINT, 1 );
            pPainterBar->Invalidate( );
         }

         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->SetFocus( );

         break;

      case zMSG_REFRESHWINDOWLIST:
      {
//       TraceLineS( "TZPainterWindow::REFRESHWINDOWLIST: ",
//                   "LoadWindowList" );
         pPainterBar->LoadWindowList( );
         break;
      }

      case zMSG_CHANGESELECTEDCONTROLS:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - ChangeSelectedCtrls - ", ObjectInstanceUpdated( vDialog ) );
#endif
//         if ( pPainterBar->m_pActivePainterWindow )
//            pPainterBar->m_pActivePainterWindow->ChangeSelectedCtrls( );

         break;

      case zMSG_SYSTEMMINIMIZE:
      {
//       if ( vDialog )
//          TraceLineI( "PainterCall - SystemMinimize - ", ObjectInstanceUpdated( vDialog ) );
         pActivePainterWindow = pPainterBar->m_pActivePainterWindow;
         for ( nPos = 0; nPos < pPainterBar->m_nWndCnt; nPos++ )
         {
            pPainterWindow = pPainterBar->m_PainterWindowList[ nPos ];

            // Deselect all selected ctrls.
            if ( pPainterWindow->DeselectAllCtrls( ) )
               pPainterWindow->UpdateWindow( );

            pPainterWindow->SetWindowPos( 0, 0, 0, 0, 0,
                                          SWP_HIDEWINDOW | SWP_NOMOVE | SWP_NOSIZE );
         }

         pPainterBar->m_pActivePainterWindow = pActivePainterWindow;
//       TraceLineS( "(tzpntraa) Zeidon windows hidden!!","" );

         break;
      }

      case zMSG_SYSTEMRESTORE:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - SystemRestore - ", ObjectInstanceUpdated( vDialog ) );
#endif
         pActivePainterWindow = pPainterBar->m_pActivePainterWindow;
         for ( nPos = 0; nPos < pPainterBar->m_nWndCnt; nPos++ )
         {
            pPainterWindow = pPainterBar->m_PainterWindowList[ nPos ];
            pPainterWindow->SetWindowPos( 0, 0, 0, 0, 0,
                                  SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE );
         }

         if ( pActivePainterWindow )
            pActivePainterWindow->SetActiveWindow( );

         break;

      case zMSG_SELECTMODALPOINTER:
      {
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - SelectModalPointer - ", ObjectInstanceUpdated( vDialog ) );
#endif

         pPainterBar->SelectModalPointer( );
         break;
      }

      case zMSG_REPLACETOOLBARBUTTONS:
      {
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - ReplaceToolbarButtons - ", ObjectInstanceUpdated( vDialog ) );
#endif

//???    pPainterBar->m_wndPaletteBar.SetRedraw( FALSE );
         pPainterBar->CreatePaletteButtons( );
//???    pPainterBar->m_wndPaletteBar.SetRedraw( TRUE );
         break;
      }

      case zMSG_DELETETOOLBAR:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - DeleteToolbar - ", ObjectInstanceUpdated( vDialog ) );
#endif
         delete( pPainterBar );
         DropObjectInstance( vTZPNTROO );
         break;

      case zMSG_GETTABBING:
         return( (pPainterBar->m_fState & zTZCB_SHOWTABS) ? TRUE: FALSE );

      case zMSG_SHOWTABBING:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - ShowTabbing - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
         {
            pPainterBar->m_pActivePainterWindow->m_pPainterClient->ShowTabbing( );
         }

         break;

      case zMSG_REMOVETABBING:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - RemoveTabbing - ",
                        ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->m_pPainterClient->RemoveTabbing( );

         break;

      case zMSG_BUILDTZPNEVWO:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - BuildTZPNEVWO - ", ObjectInstanceUpdated( vDialog ) );
#endif
         if ( pPainterBar->m_pActivePainterWindow )
            pPainterBar->m_pActivePainterWindow->BuildTZPNEVWO( );

         break;

      case zMSG_SETSCROLLBARS:
         pPainterBar->SetScrollbars( pchParm ? TRUE : FALSE );
         break;

      case zMSG_SETGRID:
//       TraceLineS( "zMSG_SETGRID", "" );
         pPainterBar->SetGrid( pchParm ? TRUE : FALSE );
         break;

      case zMSG_INITPAINTER:
         // use the tests:
         //    if ( pPainterBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
         // or
         //    if ( (pPainterBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
         // to determine if we are doing dialog or report processing
         if ( pchParm != (zPCHAR) -1 )
         {
            pPainterBar->m_fState &= ~(zTZCB_REPORT | zTZCB_XSLT);
            if ( pchParm )
            {
               if ( (zLONG) pchParm & 2 )
                  pPainterBar->m_fState |= zTZCB_XSLT;
               else
                  pPainterBar->m_fState |= zTZCB_REPORT;
            }

            pPainterBar->m_fState |= zTZCB_INITIALIZED;
            pPainterBar->Initialization( );
         }

         break;

      case zMSG_ISREPORT:
         return( (pPainterBar->m_fState & zTZCB_REPORT) ? TRUE : FALSE );

      case zMSG_TERMPAINTER:
         if ( pchParm )
         {
            pPainterBar->m_fState &= ~zTZCB_INITIALIZED;
            if ( pPainterBar->m_pActivePainterWindow )
            {
               SetProfileStr( pPainterBar->m_vSubtask, "Design",
                         pPainterBar->m_pActivePainterWindow->m_csDlgTag,
                         "..Start", szlWindow,
                         pPainterBar->m_pActivePainterWindow->m_csWndTag );
               pPainterBar->m_pActivePainterWindow = 0;
            }
         }
         else
            pPainterBar->m_fState |= zTZCB_INITIALIZED; // cancel termination

         break;

      case zMSG_PAINTERINITIALIZED:
         if ( pPainterBar && (pPainterBar->m_fState & zTZCB_INITIALIZED) )
            return( 1 );
         else
            return( 0 );

      case zMSG_RESTORE_PLACEMENT:
      {
         zLONG  lFlags = fnGetProfileNbr( pPainterBar->m_pZSubtask, "ZDR", "ScrollBars" );
         CControlBarInfo CB_Info;

//       pPainterBar->m_wndPaletteBar.SetColumns( 2 );
//       pPainterBar->m_wndPaletteBar.Invalidate( );
//
//       m_pZSubtask->m_pZFWnd->SaveBarState( _T( "Control" ) );
//       m_pZSubtask->m_pZFWnd->SaveBarState( _T( "ToolBox" ) );
//       AfxGetApp()->WriteProfileInt(
//       _T("General"),_T("Columns"),m_wndPaletteBar.GetColumns());
//       AfxGetApp()->WriteProfileInt( _T("General"),_T("Color"),(m_bColor!=0));
//       AfxGetApp()->WriteProfileInt( _T("General"),_T("ToolTips"),(m_bToolTips!=0));

//       pPainterBar->GetBarInfo( &CB_Info );
         ReadToolBarPlacement( pPainterBar->m_pZSubtask, "ZDR", "ToolBar", &CB_Info );

         pPainterBar->SetBarInfo( &CB_Info, pPainterBar->m_pZSubtask->m_pZFWnd );
         pPainterBar->m_pZSubtask->m_pZFWnd->ShowControlBar( pPainterBar, TRUE, FALSE );

         // SaveBarState saves everything but the number of Columns in
         // the Palette ... we need to do that ourselves.

         zLONG lColumns = fnGetProfileNbr( pPainterBar->m_pZSubtask, "ZDR", "Columns" );
         if ( lColumns == 0 )
            lColumns = 1;

         pPainterBar->m_wndPaletteBar.SetColumns( (zSHORT) lColumns );

//       pPainterBar->m_wndPaletteBar.GetBarInfo( &CB_Info );
         ReadToolBarPlacement( pPainterBar->m_pZSubtask, "ZDR", "Palette", &CB_Info );

         if ( CB_Info.m_bFloating )
         {
            // need to create floating frame to match
            CMiniDockFrameWnd* pDockFrame =
               pPainterBar->m_pZSubtask->m_pZFWnd->CreateFloatingFrame( CB_Info.m_bHorz ? CBRS_ALIGN_TOP : CBRS_ALIGN_LEFT );
            ASSERT( pDockFrame );
            CRect rect( CB_Info.m_pointPos, CSize( 10, 10 ) );
            pDockFrame->CalcWindowRect( &rect );
            pDockFrame->SetWindowPos( 0, rect.left, rect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
            CDockBar* pDockBar = (CDockBar *) pDockFrame->GetDlgItem( AFX_IDW_DOCKBAR_FLOAT );
            ASSERT( pDockBar );
            ASSERT_KINDOF( CDockBar, pDockBar );
            CB_Info.m_pBar = pDockBar;
         }

         pPainterBar->m_wndPaletteBar.SetBarInfo( &CB_Info, pPainterBar->m_pZSubtask->m_pZFWnd );
         pPainterBar->m_pZSubtask->m_pZFWnd->ShowControlBar( &(pPainterBar->m_wndPaletteBar), TRUE, FALSE );

         return( (zSHORT) lFlags );
      }

      case zMSG_SAVE_PLACEMENT:
      {
         fnSetProfileNbr( pPainterBar->m_pZSubtask, "ZDR", "ScrollBars", pPainterBar->m_fState & zTZCB_SCROLLBARS );

         // SaveBarState saves everything but the number of Columns in
         // the Palette ... we need to do that ourselves.

         CControlBarInfo CB_Info;

         pPainterBar->GetBarInfo( &CB_Info );
         WriteToolBarPlacement( pPainterBar->m_pZSubtask, "ZDR", "ToolBar", &CB_Info );

         fnSetProfileNbr( pPainterBar->m_pZSubtask, "ZDR", "Columns", pPainterBar->m_wndPaletteBar.GetColumns( ) );

         pPainterBar->m_wndPaletteBar.GetBarInfo( &CB_Info );
         WriteToolBarPlacement( pPainterBar->m_pZSubtask, "ZDR", "Palette", &CB_Info );

         break;
      }

      case zMSG_GETCONTROLBAR:
      {
         TZPainterBar **pBar = (TZPainterBar **) pchParm;
         *pBar = pPainterBar;
         break;
      }

      case zMSG_GETCURRPAINTER:
      {
         TZPainterWindow **pWnd = (TZPainterWindow **) pchParm;
         *pWnd = pPainterBar->m_pActivePainterWindow;
         break;
      }

      case zMSG_SETCURRCTRL:
         if ( pPainterBar->m_pActivePainterWindow )
         {
            TZPainterCtrl *pCtrl;
            for ( zSHORT nPos = 0;
                  nPos < pPainterBar->m_pActivePainterWindow->m_nCtrlCnt;
                  nPos++ )
            {
               pCtrl = pPainterBar->m_pActivePainterWindow->m_CtrlList[ nPos ];
               if ( zstrcmp( pCtrl->m_csTag.GetString(), pchParm ) == 0 )
               {
                  pPainterBar->m_pActivePainterWindow->m_pCurrCtrl = pCtrl;
                  return( 0 );
               }
            }
         }

         pPainterBar->m_pActivePainterWindow->m_pCurrCtrl = 0;
         return( -1 );

      case zMSG_GETCURRCTRL:
         if ( pPainterBar->m_pActivePainterWindow &&
              pPainterBar->m_pActivePainterWindow->m_pCurrCtrl )
         {
            if ( vDialog )
            {
               // If the vDialog parameter is set, a request
               // is being made for an ActiveX ctrl.
               TZActiveX **pAtx = (TZActiveX **) pchParm;
               *pAtx = DYNAMIC_DOWNCAST( TZActiveX, pPainterBar->m_pActivePainterWindow->m_pCurrCtrl->m_pWndCtrl );
            }
            else
            {
               TZPainterCtrl **pCtrl = (TZPainterCtrl **) pchParm;
               *pCtrl = pPainterBar->m_pActivePainterWindow->m_pCurrCtrl;
            }
         }
         else
         {
            zPVOID *pv = (zPVOID *) pchParm;
            *pv = 0;
         }

         break;

      case zMSG_GETCURRCTRLWND:
         if ( pPainterBar->m_pActivePainterWindow && pPainterBar->m_pActivePainterWindow->m_pCurrCtrl )
         {
            CWnd **pWnd = (CWnd **) pchParm;
            if ( vDialog )
            {
               // If the vDialog parameter is set, a request
               // is being made for an ActiveX ctrl.
               TZActiveX *pAtx;
               pAtx = DYNAMIC_DOWNCAST( TZActiveX, pPainterBar->
                       m_pActivePainterWindow->m_pCurrCtrl->m_pWndCtrl );
               if ( pAtx )
                  *pWnd = pPainterBar->m_pActivePainterWindow->m_pCurrCtrl->m_pWndCtrl;
               else
                  *pWnd = 0;
            }
            else
            {
               *pWnd = pPainterBar->m_pActivePainterWindow->m_pCurrCtrl->m_pWndCtrl;
            }
         }
         else
         {
            zPVOID *pv = (zPVOID *) pchParm;
            *pv = 0;
         }

         break;

      case zMSG_UNDO:
         if ( pPainterBar &&
              pPainterBar->m_pActivePainterWindow &&
              pPainterBar->m_pActivePainterWindow->m_pUndoCurr )
         {
//          TraceLineS( "UNDO OK", "" );
            if ( pchParm == 0 )    // undo
            {
               pPainterBar->m_pActivePainterWindow->MoveToUndoRedo( FALSE );
            }
            else
         // if ( pchParm )    // asking for undo label
            {
               zSHORT nLth = (zSHORT) zstrlen( pPainterBar->m_pActivePainterWindow->m_pUndoCurr->m_szLabel );
               pPainterBar->m_pActivePainterWindow->m_pUndoCurr->m_szLabel[ 1 ] = 'U';
               pPainterBar->m_pActivePainterWindow->m_pUndoCurr->m_szLabel[ 2 ] = 'n';
               pPainterBar->m_pActivePainterWindow->m_pUndoCurr->m_szLabel[ nLth - 1 ] = 'Z';
               strcpy_s( pchParm, lMaxLth, pPainterBar->m_pActivePainterWindow->m_pUndoCurr->m_szLabel );
            }

            return( 0 );
         }

//       TraceLineS( "UNDO NOT OK", "" );
         if ( pchParm == 0 )    // not asking for undo label
            ::MessageBeep( MB_ICONQUESTION );

         return( -1 );

      case zMSG_REDO:
         if ( pPainterBar &&
              pPainterBar->m_pActivePainterWindow &&
              pPainterBar->m_pActivePainterWindow->m_pRedoCurr )
         {
//          TraceLineS( "REDO OK", "" );
            if ( pchParm == 0 )    // redo
            {
               pPainterBar->m_pActivePainterWindow->MoveToUndoRedo( TRUE );
            }
            else
         // if ( pchParm )    // asking for redo label
            {
               TZUndoRedo *pZUndoRedo = pPainterBar->m_pActivePainterWindow->m_pRedoCurr;
               while ( pZUndoRedo->m_pPrev && pZUndoRedo->m_nIdNbr == pZUndoRedo->m_pPrev->m_nIdNbr )
               {
                  pZUndoRedo = pZUndoRedo->m_pPrev;
               }

               zSHORT nLth = (zSHORT) zstrlen( pZUndoRedo->m_szLabel );
               pZUndoRedo->m_szLabel[ 1 ] = 'R';
               pZUndoRedo->m_szLabel[ 2 ] = 'e';
               pZUndoRedo->m_szLabel[ nLth - 1 ] = 'Y';
               strcpy_s( pchParm, lMaxLth, pZUndoRedo->m_szLabel );
            }

            return( 0 );
         }

//       TraceLineS( "REDO NOT OK", "" );
         if ( pchParm == 0 )    // not asking for redo label
            ::MessageBeep( MB_ICONQUESTION );

         return( -1 );

      case zMSG_CLIPBOARD_COPY:
         if ( pPainterBar &&
              pPainterBar->m_pActivePainterWindow &&
              pPainterBar->m_pActivePainterWindow->m_nSelectCnt > 0 &&
              pPainterBar->m_pActivePainterWindow->m_pLastSelected )
         {
            TZPainterCtrl *pCtrl;
            zVIEW vTaskLPLR;
            zCHAR  szViewName[ 64 ];
            TZPainterCtrl *pParentRequired = 0;

            if ( pchParm )    // asking if copy is valid
               return( 0 );

            pPainterWindow = pPainterBar->m_pActivePainterWindow;
            if ( pPainterBar->m_fState & zTZCB_XSLT )
               strcpy_s( szViewName, zsizeof( szViewName ), "__ClipboardXSLT_" );
            else
            if ( pPainterBar->m_fState & zTZCB_REPORT )
               strcpy_s( szViewName, zsizeof( szViewName ), "__ClipboardReport_" );
            else
               strcpy_s( szViewName, zsizeof( szViewName ), "__ClipboardDialog_" );

            // We need the LPLR name so we can correctly qualify the System level view name.
            GetViewByName( &vTaskLPLR, "TaskLPLR", pPainterBar->m_vSubtask, zLEVEL_TASK );
            GetStringFromAttribute( szViewName + 18, zsizeof( szViewName ) - 18, vTaskLPLR, "LPLR", szlName );

            if ( GetViewByName( &vDialog, szViewName, pPainterBar->m_vSubtask, zLEVEL_SYSTEM ) > 0 )
               DropObjectInstance( vDialog );

            // Force all ctrls to be applied to the OI.
            pPainterWindow->UpdateZeidonWindow( );

            if ( ActivateOI_FromOI_ForTask( &vDialog, pPainterWindow->m_vDialog, 0, zSINGLE | zLEVEL_SYSTEM ) < 0 )
            {
               return( -16 );
            }

            while ( ResetViewFromSubobject( vDialog ) == 0 )
            {
            }

            SetNameForView( vDialog, szViewName, 0, zLEVEL_SYSTEM );
         // TraceLineS( "COPY TO CLIPBOARD OK ", szViewName );

            if ( (pPainterBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
            {
               if ( CheckExistenceOfEntity( vDialog, "DfltWnd" ) == 0 )
                  ExcludeEntity( vDialog, "DfltWnd", zREPOS_AFTER );
            }

            // Go through and eliminate all windows except the active one.
            zSHORT nRC = SetCursorFirstEntity( vDialog, pchWindowPage, 0 );
            while ( nRC == zCURSOR_SET )
            {
               GetAddrForAttribute( &pchWindowName, vDialog, pchWindowPage, szlTag );
               if ( zstrcmp( pchWindowName, pPainterWindow->m_csWndTag.GetString() ) )
                  nRC = DeleteEntity( vDialog, pchWindowPage, zREPOS_NEXT );
               else
                  nRC = SetCursorNextEntity( vDialog, pchWindowPage, 0 );
            }

         // ::MessageBox( 0, "zMSG_CLIPBOARD_COPY view name after WindowDelete", szViewName, MB_OK );

            // Remove DfltWnd, WndEvents, DfltMenu, Menus and Hotkeys.
            if ( (pPainterBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
            {
               if ( CheckExistenceOfEntity( vDialog, "DfltMenu" ) == 0 )
                  ExcludeEntity( vDialog, "DfltMenu", zREPOS_AFTER );

               if ( CheckExistenceOfEntity( vDialog, "WndStyle" ) == 0 )
                  ExcludeEntity( vDialog, "WndStyle", zREPOS_AFTER );

               while ( SetCursorFirstEntity( vDialog, "WndEvent", 0 ) == zCURSOR_SET )
               {
                  DeleteEntity( vDialog, "WndEvent", zREPOS_AFTER );
               }

               while ( SetCursorFirstEntity( vDialog, szlMenu, 0 ) == zCURSOR_SET )
               {
                  DeleteEntity( vDialog, szlMenu, zREPOS_AFTER );
               }

               while ( SetCursorFirstEntity( vDialog, "Hotkey", 0 ) == zCURSOR_SET )
               {
                  DeleteEntity( vDialog, "Hotkey", zREPOS_AFTER );
               }
            }

            // First, all selected ctrls must have the same parent.
            for ( nPos = 0; nPos < pPainterWindow->m_nCtrlCnt; nPos++ )
            {
               pCtrl = pPainterWindow->m_CtrlList[ nPos ];
               if ( pCtrl->IsSelected( ) )
               {
                  if ( pCtrl->m_pCtrlParent != pPainterWindow->m_pLastSelected->m_pCtrlParent )
                  {
                     DropObjectInstance( vDialog );
                     MessageSend( pPainterWindow->m_pBar->m_vSubtask,
                                  0, "Zeidon Copy Error",
                                  "Selected controls must all have\n"
                                     "the same parent for Copy.",
                                  zMSGQ_MODAL_ERROR, FALSE );
                     return( -1 );
                  }
                  else
                  {
                     if ( pCtrl->m_vCtrl &&
                          CompareAttributeToString( pCtrl->m_vCtrl, "ControlDef", "RequiresParent", "Y" ) == 0 )
                     {
                        pParentRequired = pCtrl->m_pCtrlParent;
                     }
                  }
               }
            }

         // ::MessageBox( 0, "zMSG_CLIPBOARD_COPY view name before ControlDelete", szViewName, MB_OK );

            // Traverse the controls eliminating those not selected.
            fnDeleteUnselectedCtrls( vDialog, pPainterWindow );

         // ::MessageBox( 0, "zMSG_CLIPBOARD_COPY view name after ControlDelete", szViewName, MB_OK );
            // Use the first bit of the OptionFlags attribute to specify:
            //    0 - parent control is required
            //    1 - parent control is NOT required.
            if ( pParentRequired )
            {
               pParentRequired->PositionOnZeidonCtrl( vDialog );
               do
               {
                  SetAttributeFromInteger( vDialog, "Control", "OptionFlags", 0 );
               } while ( ResetViewFromSubobject( vDialog ) == 0 );
            }
            else
            {
               pParentRequired = pPainterWindow->m_pLastSelected->m_pCtrlParent;
               if ( pParentRequired )
               {
                  pParentRequired->PositionOnZeidonCtrl( vDialog );
                  do
                  {
                     SetAttributeFromInteger( vDialog, "Control", "OptionFlags", 1 );
                  } while ( ResetViewFromSubobject( vDialog ) == 0 );
               }
            }

         // ::MessageBox( 0, "zMSG_CLIPBOARD_COPY view name after ControlDelete2",
         //               szViewName, MB_OK );

            // Remove any unused Actions.
            if ( (pPainterBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
            {
               nRC = SetCursorFirstEntity( vDialog, "Action", "Dialog" );
               while ( nRC >= zCURSOR_SET )
               {
                  if ( CheckExistenceOfEntity( vDialog, "ActWndEvent" ) == 0 ||
                       CheckExistenceOfEntity( vDialog, "ActEvent" ) == 0 ||
                       CheckExistenceOfEntity( vDialog, "ActOpt" ) == 0 )
                  {
                     // being used ... don't delete
                     nRC = SetCursorNextEntity( vDialog, "Action", "Dialog" );
                  }
                  else
                     nRC = DeleteEntity( vDialog, "Action", zREPOS_NEXT );
               }
            }

            return( 0 );
         }

      // TraceLineS( "COPY TO CLIPBOARD NOT OK", "" );
         if ( pchParm == 0 )  // not asking if copy is valid
            ::MessageBeep( MB_ICONQUESTION );

         return( -1 );

      case zMSG_CLIPBOARD_PASTE:
      {
         if ( pPainterBar &&
              pPainterBar->m_pActivePainterWindow &&
              pPainterBar->m_pActivePainterWindow->m_nSelectCnt <= 1 )
         {
            zVIEW  vTaskLPLR;
            zCHAR  szViewName[ 64 ];
            zSHORT nRC;

            // We need the LPLR name so we can correctly qualify the System
            // level view name.
            if ( pPainterBar->m_fState & zTZCB_XSLT )
               strcpy_s( szViewName, zsizeof( szViewName ), "__ClipboardXSLT_" );
            else
            if ( pPainterBar->m_fState & zTZCB_REPORT )
               strcpy_s( szViewName, zsizeof( szViewName ), "__ClipboardReport_" );
            else
               strcpy_s( szViewName, zsizeof( szViewName ), "__ClipboardDialog_" );

            GetViewByName( &vTaskLPLR, "TaskLPLR", pPainterBar->m_vSubtask, zLEVEL_TASK );
            GetStringFromAttribute( szViewName + 18, zsizeof( szViewName ) - 18, vTaskLPLR, "LPLR", szlName );

            if ( GetViewByName( &vDialog, szViewName, pPainterBar->m_vSubtask, zLEVEL_SYSTEM ) > 0 )
            {
               zVIEW  vCtrlDef;

            // TraceLineS( "PASTE FROM CLIPBOARD OK ", szViewName );
               if ( pchParm )  // asking if paste is available (it still may
                  return( 0 ); // be invalid if wrong ctrl types are involved)

               GetViewByName( &vCtrlDef, szlTZPESRCO, pPainterBar->m_vSubtask, zLEVEL_TASK );

               // Force all ctrls to be applied to the OI.
               pPainterWindow = pPainterBar->m_pActivePainterWindow;
               pPainterWindow->UpdateZeidonWindow( );

               // We are ready to paste the ctrls from the Clipboard to
               // the current Dialog/Report.  First, determine where the
               // copied ctrls are to be placed.  If a ctrl is selected
               // in the active painter window. the ctrls will be copied
               // with the selected ctrl as parent.  Otherwise the ctrls
               // will be copied to the Window/Page if possible.
               if ( pPainterBar->m_fState & zTZCB_REPORT )
               {
                  if ( pPainterWindow->m_pLastSelected )
                  {
                  // zPCHAR pchEntity;
                     zLONG  lGroupSetCnt;
                     zLONG  lGroupCnt;
                     zVIEW  vTgtCtrl;

                     CreateViewFromViewForTask( &vTgtCtrl,
                                                pPainterWindow->m_vDialog,
                                                pPainterWindow->m_vDialog );
                     pPainterWindow->m_pLastSelected->PositionOnZeidonCtrl( vTgtCtrl );

                     lGroupSetCnt = CountEntitiesForView( vDialog, szlGroupSet );
                     lGroupCnt = CountEntitiesForView( vDialog, szlGroup );

                     if ( pPainterWindow->m_pLastSelected->m_chEntity == 'C' )
                     {
                        if ( lGroupSetCnt > 1 || lGroupCnt > 1 )
                        {
                           MessageSend( pPainterWindow->m_pBar->m_vSubtask,
                                        0, "Zeidon Paste Error",
                                        "Cannot paste controls from\n"
                                           "multiple GroupSets or Groups\n"
                                           "to the selected control.",
                                        zMSGQ_MODAL_ERROR, FALSE );
                           DropView( vTgtCtrl );
                           return( -1 );
                        }

                        TZPainterCtrl *pNewParent;
                        zVIEW  vParentDef;
                        zLONG  lType;

                        pNewParent = pPainterWindow->m_pLastSelected;
                        CreateViewFromViewForTask( &vParentDef, vCtrlDef,
                                                   pPainterWindow->m_vDialog );
                        SetCursorFirstEntityByInteger( vParentDef, szlControlDef,
                                                       szlKey, pNewParent->m_lType, 0 );

                        nRC = SetCursorFirstEntity( vDialog, szlControl, 0 );
                        while ( nRC == zCURSOR_SET )
                        {
                           GetIntegerFromAttribute( &lType, vDialog, szlControlDef, szlKey );
                           SetCursorFirstEntityByInteger( vCtrlDef, szlControlDef, szlKey, lType, 0 );

                           // CtrlValidate will return:
                           //   -1 - Create or move is invalid
                           //    0 - Create or move is valid and vParent
                           //        is a valid parent.
                           //    1 - Create or move is valid but vParent
                           //        is not a valid parent so create or
                           //        move vCtrl to the client area (if
                           //        the client is a valid parent).
                           if ( CtrlValidate( vCtrlDef, vParentDef, 0, zCTRL_VALID_PAINT ) != 0 )
                           {
                              MessageSend( pPainterWindow->m_pBar->m_vSubtask,
                                           0, "Zeidon Paste Error",
                                           "Selected control cannot accept\n"
                                              "the control(s) being pasted.",
                                           zMSGQ_MODAL_ERROR, FALSE );
                              DropView( vTgtCtrl );
                              return( -1 );
                           }

                           nRC = SetCursorNextEntity( vDialog, szlControl, 0 );
                        }

                     // pchEntity = szlControl;
                     }
                     else
                     if ( pPainterWindow->m_pLastSelected->m_chEntity == 'G' )
                     {
                        if ( lGroupSetCnt > 1 || lGroupCnt > 1 )
                        {
                           MessageSend( pPainterWindow->m_pBar->m_vSubtask,
                                        0, "Zeidon Paste Error",
                                        "Cannot paste controls from\n"
                                           "multiple GroupSets or Groups\n"
                                           "to the selected Group.",
                                        zMSGQ_MODAL_ERROR, FALSE );
                           DropView( vTgtCtrl );
                           return( -1 );
                        }

                     // pchEntity = szlGroup;
                     }
                     else
                  // if ( pPainterWindow->m_pLastSelected->m_chEntity == 'S' )
                     {
                        if ( lGroupSetCnt > 1 )
                        {
                           MessageSend( pPainterWindow->m_pBar->m_vSubtask, 0, "Zeidon Paste Error",
                                        "Cannot paste controls from\nmultiple GroupSets to a\nsingle GroupSet.",
                                        zMSGQ_MODAL_ERROR, FALSE );
                           DropView( vTgtCtrl );
                           return( -1 );
                        }

                     // pchEntity = szlGroupSet;
                     }

                     SetCursorFirstEntity( vDialog, szlControl, 0 );
                     if ( pPainterWindow->m_pLastSelected->m_chEntity == 'C' )
                     {
                        if ( fnMergeCtrls( pPainterWindow, pPainterWindow->m_vDialog,
                                           vDialog, vTgtCtrl, vTaskLPLR, vCtrlDef ) >= 0 )
                        {
                           pPainterWindow->PaintZeidonWindow( );
                        }
                     }
                     else
                     {
                        if ( fnMergeCtrls( pPainterWindow, 0, vDialog,
                                           vTgtCtrl, vTaskLPLR, vCtrlDef ) >= 0 )
                        {
                           pPainterWindow->PaintZeidonWindow( );
                        }
                     }

                  // DropView( vTgtCtrl );  dropped by MergeCtrls

                     return( 0 );
                  }
                  else
                  {
                     // This is the easiest case ... create new GroupSet(s)
                     // as needed and copy all subordinates.
                     SetCursorLastEntity( pPainterWindow->m_vDialog, "GroupSet", 0 );
                     nRC = SetCursorFirstEntity( vDialog, szlGroupSet, 0 );
                     while ( nRC == zCURSOR_SET )
                     {
                        pPainterWindow->
                           CreateMetaEntity( pPainterWindow->m_vDialog,
                                             szlGroupSet, zPOS_AFTER );
                        SetMatchingAttributesByName( pPainterWindow->m_vDialog,
                                                     szlGroupSet, vDialog, szlGroupSet,
                                                     zSET_NULL | zSET_NOTNULL );

                        nRC = SetCursorFirstEntity( vDialog, szlGroup, 0 );
                        while ( nRC == zCURSOR_SET )
                        {
                           pPainterWindow->
                              CreateMetaEntity( pPainterWindow->m_vDialog, szlGroup, zPOS_AFTER );
                           SetMatchingAttributesByName( pPainterWindow->m_vDialog,
                                                        szlGroup, vDialog, szlGroup,
                                                        zSET_NULL | zSET_NOTNULL );

                           if ( fnMergeCtrls( pPainterWindow, pPainterWindow->m_vDialog,
                                              vDialog, 0, vTaskLPLR, vCtrlDef ) >= 0 )
                           {
                              pPainterWindow->PaintZeidonWindow( );
                           }

                           nRC = SetCursorNextEntity( vDialog, szlGroup, 0 );
                        }

                        nRC = SetCursorNextEntity( vDialog, szlGroupSet, 0 );
                     }
                  }
               }
               else
            // if ( (pPainterBar->m_fState & zTZCB_REPORT) == 0 )
               {
                  zVIEW  vTgtCtrl = 0;

                  if ( pPainterWindow->m_pLastSelected )
                  {
                     TZPainterCtrl *pCtrl = pPainterWindow->m_pLastSelected->GetRealCtrl( );
                     CreateViewFromViewForTask( &vTgtCtrl,
                                                pPainterWindow->m_vDialog,
                                                pPainterWindow->m_vDialog );
                     pCtrl->PositionOnZeidonCtrl( vTgtCtrl );
                  }

                  SetCursorFirstEntity( vDialog, szlControl, 0 );
                  if ( fnMergeCtrls( pPainterWindow,
                                     pPainterWindow->m_vDialog, vDialog,
                                     vTgtCtrl, vTaskLPLR, vCtrlDef ) >= 0 )
                  {
                  // ::MessageBox( 0, "zMSG_CLIPBOARD_COPY view name after MergeCtrls", szViewName, MB_OK );
                     pPainterWindow->PaintZeidonWindow( );
                  }

               // if ( vTgtCtrl )
               //    DropView( vTgtCtrl );  dropped by MergeCtrls

                  return( 0 );
               }
            }
         }

      // TraceLineS( "PASTE FROM CLIPBOARD NOT OK", "" );
         if ( pchParm == 0 )  // not asking if paste is valid
            ::MessageBeep( MB_ICONQUESTION );

         return( -1 );
      }

      case zMSG_CLIPBOARD_COPY_MENU:
         if ( pPainterBar &&
              pPainterBar->m_pActivePainterWindow &&
              (pPainterBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
         {
            zVIEW vTaskLPLR;
            zCHAR  szViewName[ 64 ];
            zCHAR  szMenuTag[ zTAG_LTH ];

            pPainterWindow = pPainterBar->m_pActivePainterWindow;
            if ( CheckExistenceOfEntity( pPainterWindow->m_vDialog, szlMenu ) != 0 )
            {
               return( -1 );
            }

            if ( pchParm )    // asking if copy is valid
               return( 0 );

            GetStringFromAttribute( szMenuTag, zsizeof( szMenuTag ), pPainterWindow->m_vDialog, szlMenu, "Tag" );
            TraceLineS( "COPY MENU TO CLIPBOARD for Menu: ", szMenuTag );

            strcpy_s( szViewName, zsizeof( szViewName ), "__ClipboardMenu_" );

            // We need the LPLR name so we can correctly qualify the System
            // level view name.
            GetViewByName( &vTaskLPLR, "TaskLPLR", pPainterBar->m_vSubtask, zLEVEL_TASK );
            GetStringFromAttribute( szViewName + 16, zsizeof( szViewName ) - 16, vTaskLPLR, "LPLR", szlName );

            if ( GetViewByName( &vDialog, szViewName, pPainterBar->m_vSubtask, zLEVEL_SYSTEM ) > 0 )
               DropObjectInstance( vDialog );

            // Force all ctrls to be applied to the OI.
            pPainterWindow->UpdateZeidonWindow( );

            if ( ActivateOI_FromOI_ForTask( &vDialog, pPainterWindow->m_vDialog, 0, zSINGLE | zLEVEL_SYSTEM ) < 0 )
            {
               return( -16 );
            }

            while ( ResetViewFromSubobject( vDialog ) == 0 )
            {
            }

            SetNameForView( vDialog, szViewName, 0, zLEVEL_SYSTEM );

            if ( CheckExistenceOfEntity( vDialog, "DfltWnd" ) == 0 )
               ExcludeEntity( vDialog, "DfltWnd", zREPOS_AFTER );

            // Go through and eliminate all windows except the active one.
            zSHORT nRC = SetCursorFirstEntity( vDialog, pchWindowPage, 0 );
            while ( nRC == zCURSOR_SET )
            {
               GetAddrForAttribute( &pchWindowName, vDialog, pchWindowPage, szlTag );
               if ( zstrcmp( pchWindowName, pPainterWindow->m_csWndTag.GetString() ) )
                  nRC = DeleteEntity( vDialog, pchWindowPage, zREPOS_NEXT );
               else
                  nRC = SetCursorNextEntity( vDialog, pchWindowPage, 0 );
            }

         // ::MessageBox( 0, "zMSG_CLIPBOARD_COPY_MENU view name after WindowDelete", szViewName, MB_OK );

            // Remove DfltWnd, WndEvents, DfltMenu, Ctrls and Hotkeys.
            if ( CheckExistenceOfEntity( vDialog, "DfltMenu" ) == 0 )
               ExcludeEntity( vDialog, "DfltMenu", zREPOS_AFTER );

            if ( CheckExistenceOfEntity( vDialog, "WndStyle" ) == 0 )
               ExcludeEntity( vDialog, "WndStyle", zREPOS_AFTER );

            while ( SetCursorFirstEntity( vDialog, "WndEvent", 0 ) == zCURSOR_SET )
            {
               DeleteEntity( vDialog, "WndEvent", zREPOS_AFTER );
            }

            while ( SetCursorFirstEntity( vDialog, "Control", 0 ) == zCURSOR_SET )
            {
               DeleteEntity( vDialog, "Control", zREPOS_AFTER );
            }

            while ( SetCursorFirstEntity( vDialog, "Hotkey", 0 ) == zCURSOR_SET )
            {
               DeleteEntity( vDialog, "Hotkey", zREPOS_AFTER );
            }

            // Remove all menus except the specified one.  We have already
            // checked to ensure the specified one exists.
            nRC = SetCursorFirstEntity( vDialog, szlMenu, 0 );
            while ( nRC >= zCURSOR_SET )
            {
               zPCHAR pchMenuTag;

               GetAddrForAttribute( &pchMenuTag, vDialog, szlMenu, szlTag );
               if ( zstrcmp( szMenuTag, pchMenuTag ) == 0 )
                  nRC = SetCursorNextEntity( vDialog, szlMenu, 0 );
               else
                  nRC = DeleteEntity( vDialog, szlMenu, zREPOS_NEXT );
            }

            // Remove any unused Actions.
            nRC = SetCursorFirstEntity( vDialog, "Action", "Dialog" );
            while ( nRC >= zCURSOR_SET )
            {
               if ( CheckExistenceOfEntity( vDialog, "ActWndEvent" ) == 0 ||
                    CheckExistenceOfEntity( vDialog, "ActEvent" ) == 0 ||
                    CheckExistenceOfEntity( vDialog, "ActOpt" ) == 0 )
               {
                  // being used ... don't delete
                  nRC = SetCursorNextEntity( vDialog, "Action", "Dialog" );
               }
               else
                  nRC = DeleteEntity( vDialog, "Action", zREPOS_NEXT );
            }

            return( 0 );
         }

         TraceLineS( "COPY MENU TO CLIPBOARD NOT OK", "" );

         return( -1 );

      case zMSG_CLIPBOARD_PASTE_MENU:
      {
         if ( pPainterBar &&
              pPainterBar->m_pActivePainterWindow &&
              (pPainterBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
         {
            zVIEW  vTaskLPLR;
            zCHAR  szViewName[ 64 ];

            // We need the LPLR name so we can correctly qualify the System
            // level view name.
            strcpy_s( szViewName, zsizeof( szViewName ), "__ClipboardMenu_" );

            GetViewByName( &vTaskLPLR, "TaskLPLR", pPainterBar->m_vSubtask, zLEVEL_TASK );
            GetStringFromAttribute( szViewName + 16, zsizeof( szViewName ) - 16, vTaskLPLR, "LPLR", szlName );

            if ( GetViewByName( &vDialog, szViewName, pPainterBar->m_vSubtask, zLEVEL_SYSTEM ) > 0 )
            {
               zVIEW  vPE;

               TraceLineS( "PASTE MENU FROM CLIPBOARD OK ", szViewName );
               if ( pchParm )  // asking if paste is available
                  return( 0 );

               GetViewByName( &vPE, szlTZPESRCO, pPainterBar->m_vSubtask, zLEVEL_TASK );

               // Force all ctrls to be applied to the OI.
               pPainterWindow = pPainterBar->m_pActivePainterWindow;
               pPainterWindow->UpdateZeidonWindow( );

               // We are ready to paste the menu from the Clipboard to the current Dialog.

               if ( CheckExistenceOfEntity( vDialog, szlMenu ) == 0 &&
                    fnMergeMenu( pPainterBar->m_vSubtask,
                                 pPainterWindow,
                                 pPainterWindow->m_vDialog, vDialog,
                                 vTaskLPLR, vPE ) >= 0 )
               {
               // ::MessageBox( 0, "zMSG_CLIPBOARD_COPY_MENU view name after MergeMenu", szViewName, MB_OK );
                  pPainterWindow->PaintZeidonWindow( );

                  return( 0 );
               }
            }
         }

      // TraceLineS( "PASTE FROM CLIPBOARD NOT OK", "" );
         if ( pchParm == 0 )  // not asking if paste is valid
            ::MessageBeep( MB_ICONQUESTION );

         return( -1 );
      }

      case zMSG_GET_COMMON_DETAIL_FLAGS:
      {
         zPULONG pulCommonFlags = (zPULONG) pchParm;

         if ( pPainterBar && pPainterBar->m_pActivePainterWindow )
         {
            *pulCommonFlags =
                        pPainterBar->m_pActivePainterWindow->m_ulCommonFlags;
         }
         else
            *pulCommonFlags = 0;

         return( 0 );
      }
      case zMSG_SAVEDIALOG:
      {
         zFARPROC_PNTR lpfnDynRoutine;
         LPLIBRARY lpLibrary = 0;

         lpfnDynRoutine = (zFARPROC_PNTR)
         GetOperationDynamicCallAddress( pPainterBar->m_vSubtask,
                                         &lpLibrary,
                                         "tzpntrad", "SaveDialogFile",
                                         "(Save Dialog)" );
         if ( lpfnDynRoutine )
         {
            zSHORT nRC;

            nRC = (*lpfnDynRoutine)( pPainterBar->m_vSubtask );
            return( nRC );
         }
         return( 0 );
      }

      case zMSG_GENERATEJAVAJSP:
      {
         zFARPROC_PNTR lpfnDynRoutine;
         LPLIBRARY lpLibrary = 0;

         lpfnDynRoutine = (zFARPROC_PNTR)
         GetOperationDynamicCallAddress( pPainterBar->m_vSubtask,
                                         &lpLibrary,
                                         "tzpntrad", "GenerateJSPJava",
                                         "(JSP Generation)" );
         if ( lpfnDynRoutine )
         {
            zSHORT nRC;

            nRC = (*lpfnDynRoutine)( pPainterBar->m_vSubtask );
            return( nRC );
         }
         return( 0 );

      }

      case zMSG_GENERATEALLJAVAJSP:
      {
         zFARPROC_PNTR lpfnDynRoutine;
         LPLIBRARY lpLibrary = 0;

         lpfnDynRoutine = (zFARPROC_PNTR)
         GetOperationDynamicCallAddress( pPainterBar->m_vSubtask,
                                         &lpLibrary,
                                         "tzpntrad", "GenerateAllJSPJava",
                                         "(JSP Generation)" );
         if ( lpfnDynRoutine )
         {
            zSHORT nRC;

            nRC = (*lpfnDynRoutine)( pPainterBar->m_vSubtask );
            return( nRC );
         }
         return( 0 );

      }

      case zMSG_UPDATE_COMMON_DETAIL:
      {
         if ( pPainterBar && pPainterBar->m_pActivePainterWindow )
         {
            TZPainterCtrl *pCtrl;
            pPainterWindow = pPainterBar->m_pActivePainterWindow;
            zULONG ulCommonFlags = pPainterWindow->m_ulCommonFlags;
            zLONG  lCommonSubtype = (zLONG) pchParm;
            zLONG  lCommonSubtypeX = (zLONG) vDialog;
            zLONG  lSubtype;
            zSHORT nPos;

            if ( lCommonSubtype != 0xffffffff || lCommonSubtypeX != 0xffffffff )
            for ( nPos = 0; nPos < pPainterWindow->m_nCtrlCnt; nPos++ )
            {
               pCtrl = pPainterWindow->m_CtrlList[ nPos ];
               if ( pCtrl->IsSelected( ) )
               {
                  GetIntegerFromAttribute( &lSubtype, pCtrl->m_vCtrl,
                                           "Control", "Subtype" );
                  if ( ulCommonFlags & zCTRL_COMMON_SIZE_BORDER )
                  {
                     lSubtype &= ~zCONTROL_SIZEABLEBORDER;
                     lSubtype |= (zCONTROL_SIZEABLEBORDER & lCommonSubtype);
                  }

                  if ( ulCommonFlags & zCTRL_COMMON_INVISIBLE )
                  {
                     lSubtype &= ~zCONTROL_INVISIBLE;
                     lSubtype |= (zCONTROL_INVISIBLE & lCommonSubtype);
                  }

                  if ( ulCommonFlags & zCTRL_COMMON_DISABLED )
                  {
                     lSubtype &= ~zCONTROL_DISABLED;
                     lSubtype |= (zCONTROL_DISABLED & lCommonSubtype);
                  }

                  if ( ulCommonFlags & zCTRL_COMMON_NO_TAB )
                  {
                     lSubtype &= ~zCONTROL_NOTABSTOP;
                     lSubtype |= (zCONTROL_NOTABSTOP & lCommonSubtype);
                  }

                  if ( ulCommonFlags & zCTRL_COMMON_BORDER )
                  {
                     lSubtype &= ~zCONTROL_BORDEROFF;
                     lSubtype |= (zCONTROL_BORDEROFF & lCommonSubtype);
                  }

                  if ( (ulCommonFlags & zCTRL_COMMON_LEFT_JUSTIFY) ||
                       (ulCommonFlags & zCTRL_COMMON_CENTER_JUSTIFY) ||
                       (ulCommonFlags & zCTRL_COMMON_RIGHT_JUSTIFY) )
                  {
                     lSubtype &= ~(zCONTROL_CENTERJUSTIFY | zCONTROL_RIGHTJUSTIFY);
                     lSubtype |= ((zCONTROL_CENTERJUSTIFY |
                                   zCONTROL_RIGHTJUSTIFY) & lCommonSubtype);
                  }

                  SetAttributeFromInteger( pCtrl->m_vCtrl, "Control", "Subtype", lSubtype );

                  if ( (pPainterBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT)) == 0 )
                  {
                     GetIntegerFromAttribute( &lSubtype, pCtrl->m_vCtrl, "Control", "ExtendedStyle" );
                     if ( ulCommonFlags & zCTRL_COMMON_DISABLED_READONLY )
                     {
                        lSubtype &= ~zCONTROLX_DISABLE_READONLY;
                        lSubtype |=
                              (zCONTROLX_DISABLE_READONLY & lCommonSubtypeX);
                     }

                     SetAttributeFromInteger( pCtrl->m_vCtrl, "Control", "ExtendedStyle", lSubtype );
                  }
               }
            }

            pPainterBar->ResetSelectedMouseReleaseSwap( );
         }

         return( 0 );
      }

      default:
#ifdef zTEST_UPDATED_FLAG
         if ( vDialog )
            TraceLineI( "PainterCall - default - ", ObjectInstanceUpdated( vDialog ) );
#endif
         TraceLineI( "(tzpntraa) Unrecognized PainterCallMessage - ", (zLONG) nMessage );
         return( -1 );
   }

// if ( vDialog )
//    TraceLineI( "PainterCall Termination - ",
//                ObjectInstanceUpdated( vDialog ) );
   return( 0 );
}

extern "C"
{

AFX_EXT_API
CWnd * OPERATION
PainterControlBar( ZSubtask *pZSubtask,
                   CWnd     *pWndParent,
                   ZMapAct  *pzmaComposite,
                   zVIEW    vDialog,
                   zSHORT   nOffsetX,
                   zSHORT   nOffsetY,
                   zKZWDLGXO_Ctrl_DEF *pCtrlDef )
{
#ifdef DEBUG_ALL
   TraceLineS( "PainterControlBar", "" );
#endif

   return( new TZPainterBar( pZSubtask, pWndParent,
                             pzmaComposite, vDialog,
                             nOffsetX, nOffsetY, pCtrlDef ) );
}

}

typedef zSHORT (POPERATION zFARPROC_MERGECTRLS)( zVIEW, zVIEW, zVIEW, zVIEW, zVIEW, zVIEW, zBOOL );

typedef zSHORT (POPERATION zFARPROC_MERGEMENU)( zVIEW, zVIEW, zVIEW, zVIEW, zVIEW );

// Doc for MergeCtrl in tzpntrad.c ...
// One of vTgt and vTgtCtrl must be non-null (both may be non-null).
// If vTgt is null, use vTgtCtrl as the Top level view.  Otherwise if
// vTgtCtrl is not null, use vTgt as the Top level view and copy all
// of the source controls as children of the control pointed to by vTgtCtrl.
zSHORT
fnMergeCtrls( TZPainterWindow *pPainterWindow,
              zVIEW  vTgt,
              zVIEW  vSrc,
              zVIEW  vTgtCtrl,
              zVIEW  vSrcLPLR,
              zVIEW  vPE )
{
#ifdef DEBUG_ALL
   TraceLineS( "fnMergeCtrls", "" );
#endif

   zFARPROC_MERGECTRLS lpfnDynRoutine;
   LPLIBRARY lpLibrary = 0;

   lpfnDynRoutine = (zFARPROC_MERGECTRLS)
    GetOperationDynamicCallAddress( pPainterWindow->m_pBar->m_vSubtask,
                                    &lpLibrary, "tzpntrad", "MergeCtrls", "(tzctlptu Merge)" );
   if ( lpfnDynRoutine )
   {
      zSHORT nRC;
      zBOOL  bReport;

      if ( pPainterWindow->m_pBar->m_fState & (zTZCB_REPORT | zTZCB_XSLT) )
         bReport = TRUE;
      else
         bReport = FALSE;

      nRC = (*lpfnDynRoutine)( pPainterWindow->m_pBar->m_vSubtask,
                               vTgt, vSrc, vTgtCtrl, vSrcLPLR, vPE, bReport );
      return( nRC );
   }

   return( -1 );
}

zSHORT
fnMergeMenu( zVIEW  vSubtask,
             TZPainterWindow *pPainterWindow,
             zVIEW  vTgt,
             zVIEW  vSrc,
             zVIEW  vSrcLPLR,
             zVIEW  vPE )
{
#ifdef DEBUG_ALL
   TraceLineS( "fnMergeMenu", "" );
#endif

   zFARPROC_MERGEMENU lpfnDynRoutine;
   LPLIBRARY lpLibrary = 0;

   lpfnDynRoutine = (zFARPROC_MERGEMENU)
    GetOperationDynamicCallAddress( pPainterWindow->m_pBar->m_vSubtask,
                                    &lpLibrary, "tzpntrad", "MergeMenu", "(tzctlptu Merge)" );
   if ( lpfnDynRoutine )
   {
      zSHORT nRC = (*lpfnDynRoutine)( vSubtask, vTgt, vSrc, vSrcLPLR, vPE );
      return( nRC );
   }

   return( -1 );
}

// Traverse the controls eliminating those not selected.  At this point,
// we know that all selected controls have the same parent.
void
fnDeleteUnselectedCtrls( zVIEW vDialog,
                         TZPainterWindow *pPainterWindow )
{
#ifdef DEBUG_ALL
   TraceLineS( "fnDeleteUnselectedCtrls", "" );
#endif

   TZPainterCtrl *pCtrl;
   TZPainterCtrl *pCtrlParent;
   TZPainterCtrl *pPrevParentCtrl;
   TZPainterCtrl *pTempCtrl;
   zSHORT nPos;
   zPCHAR pchEntity;
   zVIEW  vCtrl;

   // Use the m_bCtrlKey flag to set the ctrls to be kept.
   for ( nPos = 0; nPos < pPainterWindow->m_nCtrlCnt; nPos++ )
   {
      pCtrl = pPainterWindow->m_CtrlList[ nPos ];
      pCtrl->m_bCtrlKey = FALSE;
   }

   // Mark all ctrls that have a parent that is SELECTED, as well as all
   // parents of the SELECTED parent.
   for ( nPos = 0; nPos < pPainterWindow->m_nCtrlCnt; nPos++ )
   {
      pCtrl = pPainterWindow->m_CtrlList[ nPos ];
      if ( pCtrl->IsSelected( ) )
      {
         while ( pCtrl )
         {
            pCtrl->m_bCtrlKey = TRUE;
            pCtrl = pCtrl->m_pCtrlParent;
         }
      }
      else
      if ( pCtrl->m_bCtrlKey == FALSE )
      {
         pCtrlParent = pCtrl->m_pCtrlParent;
         pPrevParentCtrl = pCtrlParent;
         while ( pCtrlParent )
         {
            if ( pCtrlParent->IsSelected( ) )
            {
               pTempCtrl = pCtrlParent->GetRealCtrl( );
               if ( pTempCtrl == pCtrlParent ||
                    pTempCtrl == pCtrl ||
                    pTempCtrl == pPrevParentCtrl )
               {
                  pCtrl->m_bCtrlKey = TRUE;
                  break;
               }
            }

            pPrevParentCtrl = pCtrlParent;
            pCtrlParent = pCtrlParent->m_pCtrlParent;
         }
      }
   }

// for ( nPos = 0; nPos < pPainterWindow->m_nCtrlCnt; nPos++ )
// {
//    pCtrl = pPainterWindow->m_CtrlList[ nPos ];
//    if ( pCtrl->m_bCtrlKey )
//       TraceLineS( "Marked ctrl: ", pCtrl->m_csTag );
//    else
//       TraceLineS( "UnMarked ctrl: ", pCtrl->m_csTag );
// }

   // The dirty work is done ... all ctrls to be kept have been marked.
   // Now locate and delete the Zeidon ctrls from the object instance
   // for those ctrls that are not marked.  Note that the object instance
   // from which the ctrls are deleted is not the instance corresponding
   // to the CtrlList!!!
   for ( nPos = 0; nPos < pPainterWindow->m_nCtrlCnt; nPos++ )
   {
      pCtrl = pPainterWindow->m_CtrlList[ nPos ];
      if ( pCtrl->m_bCtrlKey == FALSE )
      {
         // If this one is not marked, find its topmost unmarked parent
         // and delete it if present.
         while ( pCtrl->m_pCtrlParent && pCtrl->m_pCtrlParent->m_bCtrlKey == FALSE )
         {
            pCtrl = pCtrl->m_pCtrlParent;
         }

         if ( pCtrl->m_chEntity == 'C' )
            pchEntity = szlControl;
         else
         if ( pCtrl->m_chEntity == 'G' )
            pchEntity = szlGroup;
         else
      // if ( pCtrl->m_chEntity == 'S' )
            pchEntity = szlGroupSet;

         vCtrl = pCtrl->m_vCtrl;    // hold on to original view
         pCtrl->m_vCtrl = 0;        // prevent SetViewFromView
         if ( pCtrl->PositionOnZeidonCtrl( vDialog ) )
            DeleteEntity( vDialog, pchEntity, zREPOS_AFTER );

         pCtrl->m_vCtrl = vCtrl;    // restore value
         while ( ResetViewFromSubobject( vDialog ) == 0 )
         {
         }
      }
   }

   for ( nPos = 0; nPos < pPainterWindow->m_nCtrlCnt; nPos++ )
   {
      pCtrl = pPainterWindow->m_CtrlList[ nPos ];
      if ( pCtrl->m_bCtrlKey )
      {
         vCtrl = pCtrl->m_vCtrl;    // hold on to original view
         pCtrl->m_vCtrl = 0;        // prevent SetViewFromView
         if ( pCtrl->PositionOnZeidonCtrl( vDialog ) )
         {
            if ( pCtrl->m_chEntity == 'C' )
               pchEntity = szlControl;
            else
            if ( pCtrl->m_chEntity == 'G' )
               pchEntity = szlGroup;
            else
         // if ( pCtrl->m_chEntity == 'S' )
               pchEntity = szlGroupSet;

            if ( pCtrl->IsSelected( ) )
               SetAttributeFromInteger( vDialog, pchEntity, szlSyncKey, 0 );
            else
               SetAttributeFromInteger( vDialog, pchEntity, szlSyncKey, -1 );
         }

         pCtrl->m_vCtrl = vCtrl;    // restore value
         while ( ResetViewFromSubobject( vDialog ) == 0 )
         {
         }
      }
   }
}

// Is one rectangle "mostly" within the other rectangle?
zBOOL
fnRectMostlyWithinRect( CRect& rect1,
                        CRect& rect2 )
{
#ifdef DEBUG_ALL
   TraceLineS( "fnRectMostlyWithinRect", "" );
#endif

   zLONG  lOutside;
   zLONG  lOutsideSides;

   lOutside = 0;
   lOutsideSides = 0;
   if ( rect1.left < rect2.left )
   {
      lOutsideSides++;
      lOutside = (rect2.left - rect1.left);
   }

   if ( rect1.top < rect2.top )
   {
      lOutsideSides++;
      lOutside += (rect2.top - rect1.top);
   }

   if ( rect1.right > rect2.right )
   {
      lOutsideSides++;
      lOutside += (rect1.right - rect2.right);
   }

   if ( rect1.bottom > rect2.bottom )
   {
      lOutsideSides++;
      lOutside += (rect1.bottom - rect2.bottom);
   }

   if ( lOutsideSides == 0 )
   {
      return( 1 );
   }
   else
   {
      switch ( lOutsideSides )
      {
         case 1:
            if ( lOutside < 12 )
               return( 1 );

            break;

         case 2:
            if ( lOutside < 16 )
               return( 1 );

            break;

         case 3:
            if ( lOutside < 20 )
               return( 1 );

            break;

         case 4:
            if ( lOutside < 24 )
               return( 1 );

            break;
      }
   }

   return( 0 );
}

extern "C"
{

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION ShowInplaceControlOverCtrl
//
// DESCRIPTION: This function makes the inplace control visible over the
//              specified painter ctrl.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
ShowInplaceControlOverCtrl( zVIEW   vSubtask,
                            zVIEW   vControl,
                            zPVOID  pvCtrl,
                            zCPCHAR cpcInplaceTag )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcInplaceTag ) == 0 )
   {
   // CRect         rectPainter;
      TZPainterCtrl *pCtrl = (TZPainterCtrl *) pvCtrl;

   // pCtrl->ParentToPainterRect( rectPainter );
      SetNameForView( vControl, "TZCTLMAP2", vSubtask, zLEVEL_TASK );
      pzma->m_ulMapActFlags |= zMAPACT_VISIBLE;
      pzma->m_ulMapActFlag2 |= zMAPACT_INPLACE_VISIBLE;
      pzma->MapFromOI( );
      pzma->m_pCtrl->SetParent( pCtrl->m_pWndCtrl );
      pzma->m_pCtrl->SetWindowPos( &CWnd::wndTop,
                                   0, // rectPainter.left,
                                   0, // rectPainter.top,
                                // rectPainter.right - rectPainter.left,
                                // rectPainter.bottom - rectPainter.top,
                                   pCtrl->m_rectCtrl.right - pCtrl->m_rectCtrl.left,
                                   pCtrl->m_rectCtrl.bottom - pCtrl->m_rectCtrl.top,
                                   SWP_SHOWWINDOW );
      pzma->m_pWndLastFocus = pzma->m_pCtrl->SetFocus( );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION CallPainterForSelectedControls
//
// DESCRIPTION: This function calls back to an application operation for
//              each selected control.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
CallPainterForSelectedControls( zVIEW   vSubtask,
                                zCPCHAR cpcDLL,
                                zCPCHAR cpcOperation,
                                zVIEW   vDialogReport,
                                zVIEW   vExtra,
                                zLONG   lType,
                                zPVOID  pvData,
                                zLONG   lFlags )
{
   ZSubtask *pZSubtask;
   zVIEW    vTZPNTROO;

   // Get the currently active dialog view.
   GetViewByName( &vTZPNTROO, szlTZPNTROO, vSubtask, zLEVEL_TASK );
   if ( vTZPNTROO && GetWindowAndCtrl( &pZSubtask, 0, vSubtask, 0 ) == 0 )
   {
      TZPainterBar *pPainterBar;
      zULONG ulBlobMax = sizeof( zPVOID );

      GetBlobFromAttribute( &pPainterBar, &ulBlobMax, vTZPNTROO, szlPalette, szlPointer );

      if ( pPainterBar && pPainterBar->m_pActivePainterWindow )
      {
         zFARPROC_PAINTER lpfnDynRoutine = (zFARPROC_PAINTER)
           GetOperationDynamicCallAddress( pZSubtask->m_vDialog, (LPLPLIBRARY) &(pZSubtask->m_hLibrary),
                                           cpcDLL, cpcOperation, "(CallPainterForSelectedControls)" );
         if ( lpfnDynRoutine )
         {
            TZPainterCtrl *pCtrl;
            zLONG  lRC = 0;
            zSHORT nPos;

            if ( pPainterBar->m_pActivePainterWindow->m_nSelectCnt == 0 &&
                 pPainterBar->m_pActivePainterWindow->m_pCurrCtrl )
            {
               pCtrl = pPainterBar->m_pActivePainterWindow->m_pCurrCtrl;
               pCtrl->PositionOnZeidonCtrl( pPainterBar->m_pActivePainterWindow->m_vDialog );
               lRC = (*lpfnDynRoutine)( vSubtask, vDialogReport, vExtra, pCtrl->m_vCtrl, pCtrl, lType, pvData, lFlags );

            }
            else
            for ( nPos = 0; nPos < pPainterBar->m_pActivePainterWindow->m_nCtrlCnt; nPos++ )
            {
               pCtrl = pPainterBar->m_pActivePainterWindow->m_CtrlList[ nPos ];
               if ( pCtrl->IsSelected( ) )
               {
                  pCtrl->PositionOnZeidonCtrl( pPainterBar->m_pActivePainterWindow->m_vDialog );
                  lRC = (*lpfnDynRoutine)( vSubtask, vDialogReport, vExtra, pCtrl->m_vCtrl, pCtrl, lType, pvData, lFlags );
                  if ( lRC < 0 )
                     break;
               }
            }

            return( lRC );
         }
      }
   }

   return( -1 );
}

zOPER_EXPORT zSHORT OPERATION
GetNextCtrlAtPoint( zVIEW vSubtask, zSHORT nPos,
                    zPCHAR pchCurrentCtrl, zLONG lFlag )
{
   ZSubtask *pZSubtask;
   zVIEW    vTZPNTROO;

   // Get the currently active dialog view.
   GetViewByName( &vTZPNTROO, szlTZPNTROO, vSubtask, zLEVEL_TASK );
   if ( vTZPNTROO && GetWindowAndCtrl( &pZSubtask, 0, vSubtask, 0 ) == 0 )
   {
      TZPainterBar *pPainterBar;
      zULONG ulBlobMax = sizeof( zPVOID );

      GetBlobFromAttribute( &pPainterBar, &ulBlobMax, vTZPNTROO, szlPalette, szlPointer );

      if ( pPainterBar && pPainterBar->m_pActivePainterWindow )
      {
         TZPainterCtrl *pCtrl;
         CRect rect;

         nPos++;
         while ( nPos < pPainterBar->m_pActivePainterWindow->m_nCtrlCnt )
         {
            pCtrl = pPainterBar->m_pActivePainterWindow->m_CtrlList[ nPos ];
            if ( pCtrl->m_chEntity == 'C' || // 'C' - Ctrl
                 (pCtrl->m_chEntity == 'G' && (lFlag & 0x00000001)) || // 'G' - Group
                 (pCtrl->m_chEntity == 'S' && (lFlag & 0x00000002)) )  // 'S' - groupSet
            {
               pCtrl->ParentToPainterRect( rect );
               if ( pPainterBar->m_pActivePainterWindow->m_pt.x >= rect.left  &&
                    pPainterBar->m_pActivePainterWindow->m_pt.x <= rect.right &&
                    pPainterBar->m_pActivePainterWindow->m_pt.y >= rect.top   &&
                    pPainterBar->m_pActivePainterWindow->m_pt.y <= rect.bottom )
               {
                  strcpy_s( pchCurrentCtrl, zTAG_LTH, pCtrl->m_csTag );
                  return( nPos );
               }
            }

            nPos++;
         }
      }
   }

   return( -1 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION PainterSnapRect
//
// DESCRIPTION: This function snaps a rectangle based on a snap value
//              coming in or the snap value in the painter itself.
//
/////////////////////////////////////////////////////////////////////////////
void OPERATION
PainterSnapRect( TZPainterBar *pPainterBar,
                 CRect *lpNewRect, CRect *lpOldRect,
                 zSHORT nCharSnapValueX, zSHORT nCharSnapValueY )
{
#ifdef DEBUG_ALL
   TraceLineS( "PainterSnapRect", "" );
#endif

   zSHORT nSnapValueX;
   zSHORT nSnapValueY;
   zSHORT nSnapFudgeFactor;

   if ( nCharSnapValueX < 0 || nCharSnapValueY < 0 )
   {
      if ( pPainterBar->m_bUseMapDlgUnits )
      {
         if ( lpNewRect->right - lpNewRect->left < mConvertMapDlgToPixelX( 20 ) )
            lpNewRect->right = lpNewRect->left + mConvertMapDlgToPixelX( 40 );

         if ( lpNewRect->bottom - lpNewRect->top < mConvertMapDlgToPixelY( 11 ) )
            lpNewRect->bottom = lpNewRect->top + mConvertMapDlgToPixelY( 11 ) + 1;
      }
      else
      {
         if ( lpNewRect->right - lpNewRect->left < mConvertDlgUnitToPixelX( 20 ) )
            lpNewRect->right = lpNewRect->left + mConvertDlgUnitToPixelX( 40 );

         if ( lpNewRect->bottom - lpNewRect->top < mConvertDlgUnitToPixelY( 11 ) )
            lpNewRect->bottom = lpNewRect->top + mConvertDlgUnitToPixelY( 11 ) + 1;
      }

      return;
   }

   // Set snap value based on the snap value for the painter window.
   if ( nCharSnapValueX )
      nSnapValueX = (zSHORT) (TextMetrics.tmAveCharWidth / nCharSnapValueX);
   else
      nSnapValueX = 0;

   // Set snap value based on the snap value for the painter window
   if ( nCharSnapValueY )
      nSnapValueY = (zSHORT) (TextMetrics.tmHeight / nCharSnapValueY);
   else
      nSnapValueY = 0;

   // If nSnapValue ends up 0, get out (m_nSnap set too high).
   if ( nSnapValueX == 0 && nSnapValueY == 0 )
      return;

   // Set Fudging factor to
   nSnapFudgeFactor = (zSHORT) (2 * TextMetrics.tmDescent) + 2;

   // if the control is smaller than necessary to handle one line of
   // characters, then make it big enough to handle one line.
   if ( nSnapValueY )
   {
      if ( nSnapValueY == TextMetrics.tmHeight &&
           (lpNewRect->bottom - lpNewRect->top) < (TextMetrics.tmHeight + nSnapFudgeFactor) )
      {
         lpNewRect->bottom = lpNewRect->top + TextMetrics.tmHeight;
         lpNewRect->bottom += nSnapFudgeFactor;
      }
      else
      {
         zLONG  lMod;

         // The control is big enough, if an old rect was passed, round up
         // if the new rect is bigger than the old rect, round down if the
         // new rect is smaller than the old rect. Otherwise round to the
         // closest character size.
         lMod = 0;
         lMod = (lpNewRect->bottom - lpNewRect->top);
   //    if ( nSnapValueY == TextMetrics.tmHeight )
         if ( lMod > TextMetrics.tmHeight )
         {
            lMod -= nSnapFudgeFactor;
         }

         lMod = lMod % nSnapValueY;
         if ( lMod )
         {
            if ( lpOldRect )
            {
               if ( (lpNewRect->bottom - lpNewRect->top) > (lpOldRect->bottom - lpOldRect->top) )
               {
                  lpNewRect->bottom += (nSnapValueY - lMod);
               }
               else
               {
                  lpNewRect->bottom -= lMod;
               }
            }
            else
            {
               if ( lMod > (nSnapValueY / 2) )
                  lpNewRect->bottom += (nSnapValueY - lMod);
               else
                  lpNewRect->bottom -= lMod;
            }
         }
      }
   }

   // If the control is smaller than necessary in width, set the control
   // to the minimum width.
   if ( nSnapValueX )
   {
      if ( nCharSnapValueX == 1 &&
           (lpNewRect->right - lpNewRect->left) < (TextMetrics.tmHeight + nSnapFudgeFactor) )
      {
         lpNewRect->right  = lpNewRect->left + TextMetrics.tmHeight;
         lpNewRect->right  += nSnapFudgeFactor;
      }
      else
      {
         zLONG  lMod;
         // The control is big enough, if an old rect was passed, round up
         // if the new rect is bigger than the old rect, round down if the
         // new rect is smaller than the old rect. Otherwise round to the
         // closest character size.
         lMod = (lpNewRect->right - lpNewRect->left);
         lMod -= nSnapFudgeFactor;
         lMod = lMod % nSnapValueX;
         if ( lMod )
         {
            if ( lpOldRect )
            {
               if ( (lpNewRect->right - lpNewRect->left) > (lpOldRect->right - lpOldRect->left) )
               {
                  lpNewRect->right += (nSnapValueX - lMod);
               }
               else
               {
                  lpNewRect->right -= lMod;
               }
            }
            else
            {
               if ( lMod > (nSnapValueX / 2) )
                  lpNewRect->right += (nSnapValueX - lMod);
               else
                  lpNewRect->right -= lMod;
            }
         }
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    CtrlValidate
//
// PURPOSE:  This Operation is called by the painter to validate the
//           creating, changing and moving of controls in the painter
//           dialog.
//
// PARAMETERS:  vCtrl     - A view to the control being created, moved
//                          or changed.
//              vParent   - A view to the parent control under which vCtrl
//                          is being painted or changed (null if the parent
//                          is the client).
//              vChgCtrl  - A view to the control that vCtrl is to be
//                          changed into (null if vCtrl is being
//                          created or moved).
//              nValidate - An indicator that lets CtrlValidate know which
//                          type of validation is occurring. The values are:
//
//                             1 - Paint (create) Control (zCTRL_VALID_PAINT)
//                             2 - Move Control (zCTRL_VALID_MOVE)
//                             3 - Change Control (zCTRL_VALID_CHANGE)
//
// RETURN CODES:  -1 - Create, move or change is invalid
//                 0 - Create, move or change is valid and vParent
//                     is a valid parent.
//                 1 - Create, move or change is valid but vParent
//                     is not a valid parent so create or move vCtrl
//                     to the client area (if the client is a valid parent).
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
CtrlValidate( zVIEW  vCtrl,
              zVIEW  vParent,
              zVIEW  vChgCtrl,
              zSHORT nValidate )
{
#ifdef DEBUG_ALL
   TraceLineS( "CtrlValidate", "" );
#endif

   zSHORT nRC;

   // Creating or moving the ctrl pointed to by vCtrl?
   if ( nValidate == zCTRL_VALID_PAINT ||
        nValidate == zCTRL_VALID_MOVE )
   {
      // If vParent is null then determine if vCtrl requires a parent.  If
      // it does then vCtrl cannot be created or moved onto the client.
      if ( vParent == 0 )
      {
         if ( CompareAttributeToString( vCtrl, "ControlDef", "RequiresParent", "Y" ) == 0 )
         {
            // Requires a parent (other than the client area).
            return( -1 );
         }

         // Client area is a valid parent.
         return( 0 );
      }
      else
      // vParent is not null, so check if vCtrl can be created or moved onto this vParent.
      {
         // If nValidate is zCTRL_VALID_PAINT (create) and vParent is the
         // same control as vCtrl (being painted onto itself) then determine
         // if there is a specific control that is to be created (not
         // vCtrl) and position the cursor onto this new control.
         if ( nValidate == zCTRL_VALID_PAINT &&
              CompareEntityToEntity( vCtrl, "ControlDef", vParent, "ControlDef" ) == 0 )
         {
            // There is a child ctrl to which vCtrl should be converted.
            if ( CheckExistenceOfEntity( vCtrl, "ConvertsSelfToChild" ) == 0 )
            {
               SetCursorFirstEntityByEntityCsr( vCtrl, "ControlDef", vCtrl, "ConvertsSelfToChild", 0 );
               return( 0 );
            }
         }

      // DisplayEntityInstance( vCtrl, "ControlDef" );
      // DisplayEntityInstance( vParent, "ControlDef" );

         if ( CompareAttributeToString( vCtrl, "ControlDef", "AcceptsAllParents", "Y" ) == 0 )
         {
            // Determine if vParent accepts vCtrl as child.
            nRC = SetCursorFirstEntityByEntityCsr( vParent, "ValidChild", vCtrl, "ControlDef", 0 );

            if ( nRC == zCURSOR_SET ||
                 CompareAttributeToString( vParent, "ControlDef", "AcceptsAllChildren", "Y" ) == 0 )
            {
               // vParent accepts vCtrl as a child.
               return( 0 );
            }
            else
            {
               if ( CompareAttributeToString( vCtrl, "ControlDef", "RequiresParent", "Y" ) == 0 )
               {
                  // A parent is required but vParent will not allow vCtrl as its child.
                  return( -1 );
               }
               else
               {
                  // vCtrl can be painted on the client.
                  return( 1 );
               }
            }
         }

         // Determine if vParent is a valid parent?
         if ( CheckExistenceOfEntity( vCtrl, "ValidParent" ) == 0 )
         {
            nRC = SetCursorFirstEntityByEntityCsr( vCtrl, "ValidParent", vParent, "ControlDef", 0 );

            // vParent is a valid parent, so return OK.
            if ( nRC == zCURSOR_SET )
            {
               // Check if vParent accepts vCtrl as child.
               nRC = SetCursorFirstEntityByEntityCsr( vParent, "ValidChild", vCtrl, "ControlDef", 0 );

               if ( nRC >= zCURSOR_UNCHANGED ||
                    CompareAttributeToString( vParent, "ControlDef", "AcceptsAllChildren", "Y" ) == 0 )
               {
                  // vParent accepts vCtrl as a child.
                  return( 0 );
               }
            }
         }

         // Does this ctrl require a parent?
         if ( CompareAttributeToString( vCtrl, "ControlDef", "RequiresParent", "Y" ) == 0 )
         {
            // Requires a parent, and vParent and client are not it.
            return( -1 );
         }

         // vParent is not a valid parent but the client is.
         return( 1 );
      }
   }
   else
// if ( nValidate == zCTRL_VALID_CHANGE )  Changing ctrl pointed to by vCtrl
   {
      // If there are no ConvertableFrom entities for vChgCtrl then
      // vCtrl can not change into vChgCtrl.
      if ( CheckExistenceOfEntity( vChgCtrl, "ConvertableFrom" ) != 0 ||
           SetCursorFirstEntityByEntityCsr( vChgCtrl, "ConvertableFrom", vCtrl, "ControlDef", 0 ) < zCURSOR_SET )
      {
         ::MessageBeep( MB_ICONQUESTION );
         return( -1 );
      }

      // Update the control's view with the new control.
      SetViewFromView( vCtrl, vChgCtrl );

      // Return the results of a paint request.
      return( CtrlValidate( vCtrl, vParent, 0, zCTRL_VALID_PAINT ) );
   }
}

} // end of extern "C"

void
TraceControlCnt( zCPCHAR      cpcMsg,
                 TZPainterBar *pPainterBar )
{
#ifdef DEBUG_ALL
   TraceLineS( "TraceControlCnt", "" );
#endif

   TZPainterWindow *pPainterWindow;
   TZPainterCtrl   *pCtrl;
   zSHORT nCtrlWndCnt = 0;
   zSHORT nEdtObjCnt = 0;
   zSHORT nSelCnt = 0;
   int    nCtrlCnt;
   zSHORT nPos;

   for ( nPos = 0; nPos < pPainterBar->m_nWndCnt; nPos++ )
   {
      pPainterWindow = pPainterBar->m_PainterWindowList[ nPos ];
      nCtrlCnt = pPainterWindow->m_nCtrlCnt;
      nCtrlWndCnt += nCtrlCnt;
      while ( nCtrlCnt-- )
      {
         pCtrl = pPainterWindow->m_CtrlList[ nCtrlCnt ];
         if ( pCtrl->m_pCtrlCover )
            nEdtObjCnt++;

         if ( pCtrl->IsSelected( ) )
            nSelCnt++;
      }
   }

   zCHAR szCountMsg[ 256 ];
   wsprintf( szCountMsg, " Ptr %d - Ctrl %d - Edt %d - Sel %d",
             pPainterBar->m_nWndCnt, nCtrlWndCnt, nEdtObjCnt, nSelCnt );
   TraceLineS( cpcMsg, szCountMsg );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
