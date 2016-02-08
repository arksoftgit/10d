///////////////////////////////////////////////////////////////////////////
// File:    ZCrystalEditView.cpp
// Version: 1.0.0.0
// Created: 29-Dec-1998
//
// Copyright:  Stcherbatchenko Andrei
// E-mail:     windfall@gmx.de
//
// Implementation of the ZCrystalEditView class, a part of the Crystal Edit -
// syntax coloring text editor.
//
// You are free to use or modify this code to the following restrictions:
// - Acknowledge me somewhere in your about box, simple "Parts of code by.."
// will be enough. If you can't (or don't want to), contact me personally.
// - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// 21-Feb-99
//    Paul Selormey, James R. Twine:
// +  FEATURE: description for Undo/Redo actions
// +  FEATURE: multiple MSVC-like bookmarks
// +  FEATURE: 'Disable backspace at beginning of line' option
// +  FEATURE: 'Disable drag-n-drop editing' option
//
// +  FEATURE: Auto indent
// +  FIX: ResetView() was overriden to provide cleanup
////////////////////////////////////////////////////////////////////////////


#include "zstdafx.h"

#define ZDCTL_CLASS AFX_EXT_CLASS
#include "ZDr.h"

#include "ZdCtl.h"
#include "ZdCtlGbl.h"
#include "ZdCtlEVW.h"

#ifndef __AFXPRIV_H__
#pragma message("Include <afxpriv.h> in your stdafx.h to avoid this message")
#include <afxpriv.h>
#endif
#ifndef __AFXOLE_H__
#pragma message("Include <afxole.h> in your stdafx.h to avoid this message")
#include <afxole.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DRAG_BORDER_X   5
#define DRAG_BORDER_Y   5

/*
OnDragEnter - Drop operations to occur in the window. Called when the cursor first enters the window.
OnDragLeave - Special behavior when the drag operation leaves the specified window.
OnDragOver - Drop operations to occur in the window. Called when the cursor is being dragged across the window.
OnDrop - Handling of data being dropped into the specified window.
OnScrollBy - Special behavior for when scrolling is necessary in the target window.
*/

/////////////////////////////////////////////////////////////////////////////
// ZEditDropTargetImpl class declaration

class ZEditDropTargetImpl : public COleDropTarget
{
private:
   ZCrystalEditView *m_pOwner;
public:
   ZEditDropTargetImpl(ZCrystalEditView *pOwner) { m_pOwner = pOwner; };

   virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
   virtual void OnDragLeave(CWnd* pWnd);  //
   virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);  //
   virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);  //
   virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);
//?virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, DROPEFFECT dropList, CPoint point);
};


HINSTANCE ZCrystalEditView::s_hResourceInst = NULL;

BEGIN_MESSAGE_MAP(ZCrystalEditView, CView)
   //{{AFX_MSG_MAP(ZCrystalEditView)
   ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
   ON_COMMAND(ID_EDIT_CUT, OnEditCut)
   ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
   ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
   ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
   ON_WM_CHAR()
   ON_COMMAND(ID_EDIT_DELETE_BACK, OnEditDeleteBack)
   ON_COMMAND(ID_EDIT_UNTAB, OnEditUntab)
   ON_COMMAND(ID_EDIT_TAB, OnEditTab)
   ON_COMMAND(ID_EDIT_SWITCH_OVRMODE, OnEditSwitchOvrmode)
   ON_UPDATE_COMMAND_UI(ID_EDIT_SWITCH_OVRMODE, OnUpdateEditSwitchOvrmode)
   ON_WM_CREATE()
   ON_WM_DESTROY()
   ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
   ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
   ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
   ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
   ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
   ON_WM_SYSKEYDOWN( )
   ON_WM_SYSKEYUP( )
   ON_WM_KEYDOWN( )
   ON_WM_KEYUP( )

   ON_WM_DESTROY()
   ON_WM_ERASEBKGND()
   ON_WM_SIZE()
   ON_WM_VSCROLL()
   ON_WM_MOUSEWHEEL( )
   ON_WM_SETCURSOR()
   ON_WM_LBUTTONDOWN()
   ON_WM_SETFOCUS()
   ON_WM_HSCROLL()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_TIMER()
   ON_WM_KILLFOCUS()
   ON_WM_LBUTTONDBLCLK()
   ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
   ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
   ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
   ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
   ON_WM_RBUTTONDOWN()
   ON_WM_SYSCOLORCHANGE()
   ON_WM_CREATE()
   ON_COMMAND(ID_EDIT_FIND, OnEditFind)
   ON_COMMAND(ID_EDIT_REPEAT, OnEditRepeat)
   ON_UPDATE_COMMAND_UI(ID_EDIT_REPEAT, OnUpdateEditRepeat)
   ON_COMMAND(ID_EDIT_FIND_PREVIOUS, OnEditFindPrevious)
   ON_UPDATE_COMMAND_UI(ID_EDIT_FIND_PREVIOUS, OnUpdateEditFindPrevious)
   //}}AFX_MSG_MAP

   ON_UPDATE_COMMAND_UI(ID_EDIT_INDICATOR_READ, OnUpdateIndicatorRead)
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateIndicatorOvr)
   ON_UPDATE_COMMAND_UI(ID_EDIT_INDICATOR_COL, OnUpdateIndicatorCol)

   ON_COMMAND(ID_EDIT_CHAR_LEFT, OnCharLeft)
   ON_COMMAND(ID_EDIT_EXT_CHAR_LEFT, OnExtCharLeft)
   ON_COMMAND(ID_EDIT_CHAR_RIGHT, OnCharRight)
   ON_COMMAND(ID_EDIT_EXT_CHAR_RIGHT, OnExtCharRight)
   ON_COMMAND(ID_EDIT_WORD_LEFT, OnWordLeft)
   ON_COMMAND(ID_EDIT_EXT_WORD_LEFT, OnExtWordLeft)
   ON_COMMAND(ID_EDIT_WORD_RIGHT, OnWordRight)
   ON_COMMAND(ID_EDIT_EXT_WORD_RIGHT, OnExtWordRight)
   ON_COMMAND(ID_EDIT_LINE_UP, OnLineUp)
   ON_COMMAND(ID_EDIT_EXT_LINE_UP, OnExtLineUp)
   ON_COMMAND(ID_EDIT_LINE_DOWN, OnLineDown)
   ON_COMMAND(ID_EDIT_EXT_LINE_DOWN, OnExtLineDown)
   ON_COMMAND(ID_EDIT_SCROLL_UP, ScrollUp)
   ON_COMMAND(ID_EDIT_SCROLL_DOWN, ScrollDown)
   ON_COMMAND(ID_EDIT_PAGE_UP, OnPageUp)
   ON_COMMAND(ID_EDIT_EXT_PAGE_UP, OnExtPageUp)
   ON_COMMAND(ID_EDIT_PAGE_DOWN, OnPageDown)
   ON_COMMAND(ID_EDIT_EXT_PAGE_DOWN, OnExtPageDown)
   ON_COMMAND(ID_EDIT_LINE_END, OnLineEnd)
   ON_COMMAND(ID_EDIT_EXT_LINE_END, OnExtLineEnd)
   ON_COMMAND(ID_EDIT_HOME, OnHome)
   ON_COMMAND(ID_EDIT_EXT_HOME, OnExtHome)
   ON_COMMAND(ID_EDIT_TEXT_BEGIN, OnTextBegin)
   ON_COMMAND(ID_EDIT_EXT_TEXT_BEGIN, OnExtTextBegin)
   ON_COMMAND(ID_EDIT_TEXT_END, OnTextEnd)
   ON_COMMAND(ID_EDIT_EXT_TEXT_END, OnExtTextEnd)
   // Standard printing commands
   ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
   ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
   // Status
   ON_UPDATE_COMMAND_UI(ID_EDIT_INDICATOR_CRLF, OnUpdateIndicatorCRLF)
   ON_UPDATE_COMMAND_UI(ID_EDIT_INDICATOR_POSITION, OnUpdateIndicatorPosition)
   // Bookmarks
   ON_COMMAND_RANGE(ID_EDIT_TOGGLE_BOOKMARK0, ID_EDIT_TOGGLE_BOOKMARK9, OnToggleBookmark)
   ON_COMMAND_RANGE(ID_EDIT_GO_BOOKMARK0, ID_EDIT_GO_BOOKMARK9, OnGoBookmark)
   ON_COMMAND(ID_EDIT_CLEAR_BOOKMARKS, OnClearBookmarks)
   // More Bookmarks
   ON_COMMAND(ID_EDIT_TOGGLE_BOOKMARK,     OnToggleBookmark)
   ON_COMMAND(ID_EDIT_GOTO_NEXT_BOOKMARK,  OnNextBookmark)
   ON_COMMAND(ID_EDIT_GOTO_PREV_BOOKMARK,  OnPrevBookmark)
   ON_COMMAND(ID_EDIT_CLEAR_ALL_BOOKMARKS, OnClearAllBookmarks)
   ON_UPDATE_COMMAND_UI(ID_EDIT_GOTO_NEXT_BOOKMARK,  OnUpdateNextBookmark)
   ON_UPDATE_COMMAND_UI(ID_EDIT_GOTO_PREV_BOOKMARK,  OnUpdatePrevBookmark)
   ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL_BOOKMARKS, OnUpdateClearAllBookmarks)
END_MESSAGE_MAP()

#define EXPAND_PRIMITIVE(impl, func)   \
   void ZCrystalEditView::On##func() { impl(FALSE); } \
   void ZCrystalEditView::OnExt##func() { impl(TRUE); }
   EXPAND_PRIMITIVE(MoveLeft, CharLeft)
   EXPAND_PRIMITIVE(MoveRight, CharRight)
   EXPAND_PRIMITIVE(MoveWordLeft, WordLeft)
   EXPAND_PRIMITIVE(MoveWordRight, WordRight)
   EXPAND_PRIMITIVE(MoveUp, LineUp)
   EXPAND_PRIMITIVE(MoveDown, LineDown)
   EXPAND_PRIMITIVE(MovePgUp, PageUp)
   EXPAND_PRIMITIVE(MovePgDn, PageDown)
   EXPAND_PRIMITIVE(MoveHome, Home)
   EXPAND_PRIMITIVE(MoveEnd, LineEnd)
   EXPAND_PRIMITIVE(MoveCtrlHome, TextBegin)
   EXPAND_PRIMITIVE(MoveCtrlEnd, TextEnd)
#undef EXPAND_PRIMITIVE

//Virtual bool Initialize();

#define DEBUG_ALL

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView

IMPLEMENT_DYNAMIC(ZCrystalEditView, CView)  // IMPLEMENT_DYNCREATE(ZCrystalEditView, CView)

//
//  CONSTRUCTOR: HD_Diagram
//
ZCrystalEditView::ZCrystalEditView( ZSubtask *pZSubtask,
                                    CWnd     *pWndParent,
                                    ZMapAct  *pzmaComposite,
                                    zVIEW    vDialog,
                                    zSHORT   nOffsetX,
                                    zSHORT   nOffsetY,
                                    zKZWDLGXO_Ctrl_DEF *pCtrlDef ) :
                  CView( ),
                  ZMapAct( pZSubtask,          // base class ctor
                           pzmaComposite,
                           pWndParent,
                           this,
                           vDialog,
                           nOffsetX,
                           nOffsetY,
                           pCtrlDef,
                           "Editor" )
{
// AFX_ZERO_INIT_OBJECT(ZCrystalEditView); ==>   memset(&object, 0, sizeof(ZCrystalEditView));
   m_pTextBuffer = NULL;
   m_bAutoIndent = TRUE;
   m_pOleDropTarget = NULL;

   m_bOvrMode = FALSE;
   m_bDropPosVisible = FALSE;
   m_ptSavedCaretPos = {0,0};
   m_ptDropPos = {0,0};
   m_bSelectionPushed = FALSE;
   m_ptSavedSelStart = {0,0};
   m_ptSavedSelEnd = {0,0};
   m_bAutoIndent = FALSE;

   m_bDisableBSAtSOL = FALSE;

   // AFX_ZERO_INIT_OBJECT(CView);  ==>  memset (&object, 0, sizeof(object));

   int k;

   m_pDropTarget = NULL;

   m_bLastSearch = FALSE;
   m_dwLastSearchFlags = 0;
   m_pszLastFindWhat = NULL;
   m_bMultipleSearch = FALSE;

   m_bCursorHidden = FALSE;

   // Painting caching bitmap
   m_pCacheBitmap = NULL;

   // Line/character dimensions
   m_nLineHeight = -1;
   m_nCharWidth = -1;


   // Text attributes
   m_nTabSize = 0;
   m_bViewTabs = FALSE;
   m_bSelMargin = FALSE;

   // Amount of lines/characters that completely fits the client area
   m_nScreenLines = 0;
   m_nScreenChars = 0;

   m_nMaxLineLength = 0;
   m_nIdealCharPos = 0;

   m_bFocused = FALSE;
   m_ptAnchor = {0,0};
   memset(&m_lfBaseFont, 0, sizeof(m_lfBaseFont));

   for (k = 0; k < 4; k++)
   {
      m_apFonts[k] = NULL;
   }

   // Parsing stuff
   m_pdwParseCookies = NULL;
   m_nParseArraySize = 0;

   // Pre-calculated line lengths (in characters)
   m_nActualLengthArraySize = 0;
   m_pnActualLineLength = NULL;
   m_bPreparingToDrag = FALSE;
   m_bDraggingText = FALSE;
   m_bDragSelection = FALSE;
   m_bWordSelection = FALSE;
   m_bLineSelection = FALSE;
   m_nDragSelTimer = 0;

   m_ptDrawSelStart = {0, 0};
   m_ptDrawSelEnd = {0,0};
   m_ptCursorPos = {0,0};
   m_ptSelStart = {0,0};
   m_ptSelEnd = {0,0};

   m_bBookmarkExist = FALSE;     // More bookmarks
   m_pIcons = NULL;
   
   m_hAccel = NULL;
   m_bVertScrollBarLocked = FALSE;
   m_bHorzScrollBarLocked = FALSE;
   m_ptDraggedTextBegin = {0,0};
   m_ptDraggedTextEnd = {0,0};

   m_bShowInactiveSelection = FALSE;
   m_bDisabledDragAndDrop = FALSE;

   // Printing
   m_nPrintPages = 0;
   m_pnPages = NULL;
   m_pPrintFont = NULL;
   m_nPrintLineHeight = 0;
   m_bPrintHeader = FALSE;
   m_bPrintFooter = FALSE;
   m_ptPageArea = {0, 0, 0, 0};
   m_rcPrintArea = {0, 0, 0, 0};

   m_nTopLine = 0;
   m_nOffsetChar = 0;

   SetDisableDragAndDrop( 0 );

   ResetView();


   Attr.Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_HSCROLL | WS_VSCROLL;
   if ( pCtrlDef->Subtype & zCONTROL_SIZEABLEBORDER )
      Attr.Style |= WS_THICKFRAME;
   else
      Attr.Style |= WS_BORDER;

// if ( m_pzsVName == 0 )
//    return;

   // Always create an Editor ... should never have a parent control!
   CreateZ( );
 }

void
ZCrystalEditView::CreateZ( )
{
   if ( m_ulMapActFlags & zMAPACT_VISIBLE )
      Attr.Style |= WS_VISIBLE;
   else
      Attr.Style &= ~WS_VISIBLE;

   if ( m_ulMapActFlags & zMAPACT_ENABLED )
      Attr.Style &= ~WS_DISABLED;
   else
      Attr.Style |= WS_DISABLED;

#ifdef zREMOTE_SERVER
   m_ulMapActFlag2 |= zMAPACT_CREATE_CHILDREN | zMAPACT_CREATED1;
#else
   if ( mIs_hWnd( m_hWnd ) ||
        (m_pWndParent && mIs_hWnd( m_pWndParent->m_hWnd ) &&
         CreateEx( WS_EX_CLIENTEDGE, "ZeidonCustomCtrl", *m_pzsText,
                   Attr.Style, Attr.X, Attr.Y, Attr.W, Attr.H,
                   m_pWndParent->m_hWnd, (HMENU) m_nIdNbr )) )
   {
      m_ulMapActFlag2 |= zMAPACT_CREATE_CHILDREN | zMAPACT_CREATED1;
   }
#endif
}

/*
BOOL
ZCrystalEditView::DestroyWindow( )
{
   return( CView::DestroyWindow( ) );
}
*/

//
//  DESTRUCTOR: ZCrystalEditView
//

ZCrystalEditView::~ZCrystalEditView()
{
   ASSERT(m_hAccel == NULL);
   ASSERT(m_pCacheBitmap == NULL);
   ASSERT(m_pTextBuffer == NULL);      // Must be correctly detached
   if (m_pszLastFindWhat != NULL)
      free(m_pszLastFindWhat);
   if (m_pdwParseCookies != NULL)
      delete m_pdwParseCookies;
   if (m_pnActualLineLength != NULL)
      delete m_pnActualLineLength;

// TraceLineS( "ZCrystalEditView::~ZCrystalEditView", "" );
   if ( mIs_hWnd( m_hWnd ) )
      DestroyWindow( );
}


/////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView message handlers

BOOL ZCrystalEditView::QueryEditable()
{
   return (m_pTextBuffer && m_pTextBuffer->GetReadOnly() == FALSE);
}

void ZCrystalEditView::OnEditPaste()
{
   Paste();
}

void ZCrystalEditView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(TextInClipboard());
}

void ZCrystalEditView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(IsSelection());
}

void ZCrystalEditView::OnEditCut()
{
   Cut();
}

BOOL ZCrystalEditView::DeleteCurrentSelection()
{
   if (IsSelection())
   {
      CPoint ptSelStart, ptSelEnd;
      GetSelection(ptSelStart, ptSelEnd);

      CPoint ptCursorPos = ptSelStart;
      ASSERT_VALIDTEXTPOS(ptCursorPos);
      SetAnchor(ptCursorPos);
      SetSelection(ptCursorPos, ptCursorPos);
      SetCursorPos(ptCursorPos);
      EnsureVisible(ptCursorPos);

      // [JRT]:
      m_pTextBuffer->DeleteText(this, ptSelStart.y, ptSelStart.x, ptSelEnd.y, ptSelEnd.x, CE_ACTION_DELSEL);
      return TRUE;
   }
   return FALSE;
}

BOOL ZCrystalEditView::CanPaste()
{
   if (! QueryEditable())
      return FALSE;
   return TRUE;
}

void ZCrystalEditView::Paste()
{
   CString text;
   if (CanPaste() && GetFromClipboard(text))
   {
      m_pTextBuffer->BeginUndoGroup();

      DeleteCurrentSelection();

      CPoint ptCursorPos = GetCursorPos();
      ASSERT_VALIDTEXTPOS(ptCursorPos);
      int x, y;
      m_pTextBuffer->InsertText(this, ptCursorPos.y, ptCursorPos.x, text, y, x, CE_ACTION_PASTE); //  [JRT]
      ptCursorPos.x = x;
      ptCursorPos.y = y;
      ASSERT_VALIDTEXTPOS(ptCursorPos);
      SetAnchor(ptCursorPos);
      SetSelection(ptCursorPos, ptCursorPos);
      SetCursorPos(ptCursorPos);
      EnsureVisible(ptCursorPos);

      m_pTextBuffer->FlushUndoGroup(this);
   }
}

void ZCrystalEditView::Cut()
{
   if (! QueryEditable())
      return;
   if (m_pTextBuffer == NULL)
      return;
   if (! IsSelection())
      return;

   CPoint ptSelStart, ptSelEnd;
   GetSelection(ptSelStart, ptSelEnd);
   CString text;
   GetText(ptSelStart, ptSelEnd, text);
   PutToClipboard(text);

   CPoint ptCursorPos = ptSelStart;
   ASSERT_VALIDTEXTPOS(ptCursorPos);
   SetAnchor(ptCursorPos);
   SetSelection(ptCursorPos, ptCursorPos);
   SetCursorPos(ptCursorPos);
   EnsureVisible(ptCursorPos);

   m_pTextBuffer->DeleteText(this, ptSelStart.y, ptSelStart.x, ptSelEnd.y, ptSelEnd.x, CE_ACTION_CUT); // [JRT]
}

void ZCrystalEditView::OnEditDelete()
{
   Delete();
}

void ZCrystalEditView::Delete()
{
   if (! QueryEditable())
      return;

   CPoint ptSelStart, ptSelEnd;
   GetSelection(ptSelStart, ptSelEnd);
   if (ptSelStart == ptSelEnd)
   {
      if (ptSelEnd.x == GetLineLength(ptSelEnd.y))
      {
         if (ptSelEnd.y == GetLineCount() - 1)
            return;
         ptSelEnd.y++;
         ptSelEnd.x = 0;
      }
      else
         ptSelEnd.x++;
   }

   CPoint ptCursorPos = ptSelStart;
   ASSERT_VALIDTEXTPOS(ptCursorPos);
   SetAnchor(ptCursorPos);
   SetSelection(ptCursorPos, ptCursorPos);
   SetCursorPos(ptCursorPos);
   EnsureVisible(ptCursorPos);

   m_pTextBuffer->DeleteText(this, ptSelStart.y, ptSelStart.x, ptSelEnd.y, ptSelEnd.x, CE_ACTION_DELETE); // [JRT]
}

void ZCrystalEditView::OnSysKeyDown( UINT uKey, UINT uRepeatCnt, UINT uFlags )
{
#ifdef DEBUG_ALL
   TraceLine( "ZEditor::OnSysKeyDown: %d   for tag: %s", uKey, *m_pzsTag );
#endif
#if 0
   zLONG lRC = 0;

   m_ulLastKey = uKey;
   if ( uKey != VK_SHIFT && uKey != VK_CONTROL && uKey != VK_MENU )
      lRC = ProcessImmediateEvent( this, zEDITBOX_KeyDown, (zPVOID) uFlags );

   if ( lRC == zNO_APPLICATION_EVENT || (zSHORT) zLOUSHORT( lRC ) >= 0 )
   {
      m_bLastKeyWasDelete = (VK_DELETE == uKey);
      m_bLastKeyWasBackspace = (VK_BACK == uKey);
      CView::OnSysKeyDown( uKey, uRepeatCnt, uFlags );
}
#else
   if ( uKey != VK_SHIFT && uKey != VK_CONTROL && uKey != VK_MENU )
   {
   }
   else
   {
   }
   CView::OnSysKeyDown( uKey, uRepeatCnt, uFlags );
#endif
}

void ZCrystalEditView::OnSysKeyUp( UINT uKey, UINT uRepeatCnt, UINT uFlags )
{
#ifdef DEBUG_ALL
   TraceLine( "ZEditor::OnSysKeyUp: %d   for tag: %s", uKey, *m_pzsTag );
#endif
#if 0
   zLONG lRC = 0;

   m_ulLastKey = uKey;
   if ( uKey != VK_SHIFT && uKey != VK_CONTROL && uKey != VK_MENU )
      lRC = ProcessImmediateEvent( this, zEDITBOX_KeyUp, (zPVOID) uFlags );

   if ( lRC == zNO_APPLICATION_EVENT || (zSHORT) zLOUSHORT( lRC ) >= 0 )
   {
      CView::OnSysKeyUp( uKey, uRepeatCnt, uFlags );
   }
#else
   if (uKey != VK_SHIFT && uKey != VK_CONTROL && uKey != VK_MENU)
   {
   }
   else
   {
   }
   CView::OnSysKeyUp( uKey, uRepeatCnt, uFlags );
#endif
}

void ZCrystalEditView::OnKeyDown( UINT uKey, UINT uRepeatCnt, UINT uFlags )
{
#ifdef DEBUG_ALL
   TraceLine( "ZEditor::OnKeyDown: %d   for tag: %s", uKey, *m_pzsTag );
#endif
#if 0
   m_ulLastKey = uKey;
   zLONG lRC = ProcessImmediateEvent( this, zEDITBOX_KeyDown, (zPVOID) uFlags );
   if ( lRC == zNO_APPLICATION_EVENT || (zSHORT) zLOUSHORT( lRC ) >= 0 )
   {
      m_bLastKeyWasDelete = (VK_DELETE == uKey);
      m_bLastKeyWasBackspace = (VK_BACK == uKey);
      ZCrystalEditView::OnKeyDown( uKey, uRepeatCnt, uFlags );
   }
#else
   BOOL bCtrlKey = (::GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
// BOOL bShiftKey = (::GetAsyncKeyState(VK_RBUTTON) & VK_SHIFT) != 0;
   if (bCtrlKey)
   {
   }
   else
   {
      if (uKey == VK_BACK)
      {
         // delete the previous character
         OnEditDeleteBack();
      }
      else
      if ( uKey == VK_UP || uKey == VK_DOWN || uKey == VK_LEFT || uKey == VK_RIGHT )
      {
         CPoint ptCursorPos = GetCursorPos();
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         int x = ptCursorPos.x;
         int y = ptCursorPos.y;
         int w = GetLineLength(y);
         int h = GetLineCount() - 1;
         if ( uKey == VK_UP )
         {
            if ( y > 0 )
            {
               y--;
               if ( x == w || x > GetLineLength( y ) )
                 x = GetLineLength(y);
            }
         }
         else
         if ( uKey == VK_DOWN )
         {
            if ( y < h )
            {
               y++;
               if ( x == w || x > GetLineLength( y ) )
                  x = GetLineLength(y);
            }
         }
         else
         if ( uKey == VK_LEFT )
         {
            if ( x > 0 )
               x--;
            else
            if ( y > 0 )
            {
               y--;
               x = GetLineLength(y);
            }
         }
         else
         if ( uKey == VK_RIGHT )
         {
            if ( x < w )
               x++;
            else
            if ( y < h )
            {
               y++;
               x = 0;
            }
         }

         ptCursorPos.x = x;
         ptCursorPos.y = y;
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         SetSelection(ptCursorPos, ptCursorPos);
         SetAnchor(ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);
      }
      else
      if ( uKey == VK_HOME )
      {
         CPoint ptCursorPos = GetCursorPos();
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         ptCursorPos.x = 0;
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         SetSelection(ptCursorPos, ptCursorPos);
         SetAnchor(ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);
      }
      else
      if ( uKey == VK_END )
      {
         CPoint ptCursorPos = GetCursorPos();
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         ptCursorPos.x = GetLineLength( ptCursorPos.y );
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         SetSelection(ptCursorPos, ptCursorPos);
         SetAnchor(ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);
      }
      else
      if ( uKey == VK_DELETE )
      {
         if ( IsSelection() )
         {
            OnEditDeleteBack();
         }
         else
         {
            BOOL bDelete = 0;
            CPoint ptCursorPos = GetCursorPos();
            ASSERT_VALIDTEXTPOS(ptCursorPos);

            if ( ptCursorPos.x < GetLineLength( ptCursorPos.y ) )
            {
               bDelete = 1;
               ptCursorPos.x++;
            }
            else
            if (ptCursorPos.y < GetLineCount() - 1)
            {
               bDelete = 1;
               ptCursorPos.x = 0;
               ptCursorPos.y++;
            }

            if ( bDelete )
            {
               ASSERT_VALIDTEXTPOS(ptCursorPos);
               SetSelection(ptCursorPos, ptCursorPos);
               SetAnchor(ptCursorPos);
               SetCursorPos(ptCursorPos);
               EnsureVisible(ptCursorPos);
               // delete the previous character
               OnEditDeleteBack();
            }
         }
      }
   }

   CView::OnKeyDown( uKey, uRepeatCnt, uFlags );

#endif
}

void ZCrystalEditView::OnKeyUp( UINT uKey, UINT uRepeatCnt, UINT uFlags )
{
#ifdef DEBUG_ALL
   TraceLine( "ZEditor::OnKeyUp: %d   for tag: %s", uKey, *m_pzsTag );
#endif
#if 0
   m_ulLastKey = uKey;
   zLONG lRC = ProcessImmediateEvent( this, zEDITBOX_KeyUp, (zPVOID) uFlags );
   if ( lRC == zNO_APPLICATION_EVENT || (zSHORT) zLOUSHORT( lRC ) >= 0 )
   {
      CView::OnKeyUp( uKey, uRepeatCnt, uFlags );
   }
#else
/*
   BOOL bCtrlKey = (::GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
// BOOL bShiftKey = (::GetAsyncKeyState(VK_RBUTTON) & VK_SHIFT) != 0;
   if (bCtrlKey)
   {
      if (uKey == 'Y')
      {
         OnEditRedo();
         return;
      }
    else
      if (uKey == 'Z')
      {
         OnEditUndo();
         return;
      }
   }
*/
#endif

   CView::OnKeyUp( uKey, uRepeatCnt, uFlags );
}

void ZCrystalEditView::OnChar(UINT nChar, UINT uRepeatCnt, UINT uFlags)
{
#ifdef DEBUG_ALL
   TraceLine( "ZEditor::OnChar: %d   for tag: %s", nChar, *m_pzsTag );
#endif
   CView::OnChar(nChar, uRepeatCnt, uFlags);

   if ((::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0 || (::GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0)
      return;

   BOOL bTranslated = FALSE;
   if (nChar == VK_RETURN)
   {
      if (m_bOvrMode)
      {
         CPoint ptCursorPos = GetCursorPos();
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         if (ptCursorPos.y < GetLineCount() - 1)
         {
            ptCursorPos.x = 0;
            ptCursorPos.y++;

            ASSERT_VALIDTEXTPOS(ptCursorPos);
            SetSelection(ptCursorPos, ptCursorPos);
            SetAnchor(ptCursorPos);
            SetCursorPos(ptCursorPos);
            EnsureVisible(ptCursorPos);
            return;
         }
      }

      m_pTextBuffer->BeginUndoGroup();

      if (QueryEditable())
      {
         DeleteCurrentSelection();

         CPoint ptCursorPos = GetCursorPos();
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         const static TCHAR pszText[3] = _T("\r\n");

         int x, y;
         m_pTextBuffer->InsertText(this, ptCursorPos.y, ptCursorPos.x, pszText, y, x, CE_ACTION_TYPING); // [JRT]
         ptCursorPos.x = x;
         ptCursorPos.y = y;
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         SetSelection(ptCursorPos, ptCursorPos);
         SetAnchor(ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);
      }

      m_pTextBuffer->FlushUndoGroup(this);
      return;
   }

   if (nChar > 31)
   {
      if (QueryEditable())
      {
         m_pTextBuffer->BeginUndoGroup(nChar != _T(' '));

         CPoint ptSelStart, ptSelEnd;
         GetSelection(ptSelStart, ptSelEnd);
         CPoint ptCursorPos;
         if (ptSelStart != ptSelEnd)
         {
            ptCursorPos = ptSelStart;
            DeleteCurrentSelection();
         }
         else
         {
            ptCursorPos = GetCursorPos();
            if (m_bOvrMode && ptCursorPos.x < GetLineLength(ptCursorPos.y))
               m_pTextBuffer->DeleteText(this, ptCursorPos.y, ptCursorPos.x, ptCursorPos.y, ptCursorPos.x + 1, CE_ACTION_TYPING); // [JRT]
         }

         ASSERT_VALIDTEXTPOS(ptCursorPos);

         char pszText[2];
         pszText[0] = (char) nChar;
         pszText[1] = 0;

         int x, y;
         USES_CONVERSION;
         m_pTextBuffer->InsertText(this, ptCursorPos.y, ptCursorPos.x, A2T(pszText), y, x, CE_ACTION_TYPING); // [JRT]
         ptCursorPos.x = x;
         ptCursorPos.y = y;
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         SetSelection(ptCursorPos, ptCursorPos);
         SetAnchor(ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);

         m_pTextBuffer->FlushUndoGroup(this);
      }
   }
}


//
// [JRT]: Added Support For "Disable Backspace At Start Of Line"
//
void ZCrystalEditView::OnEditDeleteBack()
{
   if (IsSelection())
   {
      OnEditDelete();
      return;
   }

   if (! QueryEditable())
      return;

   CPoint ptCursorPos = GetCursorPos();
   CPoint ptCurrentCursorPos = ptCursorPos;
   bool  bDeleted = false;

   if( !( ptCursorPos.x ) )                  // If At Start Of Line
   {
      if( !m_bDisableBSAtSOL )               // If DBSASOL Is Disabled
      {
         if( ptCursorPos.y > 0 )             // If Previous Lines Available
         {
            ptCursorPos.y--;                 // Decrement To Previous Line
            ptCursorPos.x = GetLineLength( ptCursorPos.y );  // Set Cursor To End Of Previous Line
            bDeleted = true;                 // Set Deleted Flag
         }
      }
   }
   else                                      // If Caret Not At SOL
   {
      ptCursorPos.x--;                       // Decrement Position
      bDeleted = true;                       // Set Deleted Flag
   }
/*
   if (ptCursorPos.x == 0)
   {
      if (ptCursorPos.y == 0)
         return;
      ptCursorPos.y--;
      ptCursorPos.x = GetLineLength(ptCursorPos.y);
   }
   else
      ptCursorPos.x--;
*/
   ASSERT_VALIDTEXTPOS(ptCursorPos);
   SetAnchor(ptCursorPos);
   SetSelection(ptCursorPos, ptCursorPos);
   SetCursorPos(ptCursorPos);
   EnsureVisible(ptCursorPos);

   if (bDeleted)
   {
      m_pTextBuffer->DeleteText(this, ptCursorPos.y, ptCursorPos.x, ptCurrentCursorPos.y, ptCurrentCursorPos.x, CE_ACTION_BACKSPACE); // [JRT]
   }
   return;
}

void ZCrystalEditView::OnEditTab()
{
   if (! QueryEditable())
      return;

   BOOL bTabify = FALSE;
   CPoint ptSelStart, ptSelEnd;
   if (IsSelection())
   {
      GetSelection(ptSelStart, ptSelEnd);
      bTabify = ptSelStart.y != ptSelEnd.y;
   }

   if (bTabify)
   {
      m_pTextBuffer->BeginUndoGroup();

      int nStartLine = ptSelStart.y;
      int nEndLine = ptSelEnd.y;
      ptSelStart.x = 0;
      if (ptSelEnd.x > 0)
      {
         if (ptSelEnd.y == GetLineCount() - 1)
         {
            ptSelEnd.x = GetLineLength(ptSelEnd.y);
         }
         else
         {
            ptSelEnd.x = 0;
            ptSelEnd.y++;
         }
      }
      else
         nEndLine--;
      SetSelection(ptSelStart, ptSelEnd);
      SetCursorPos(ptSelEnd);
      EnsureVisible(ptSelEnd);

      // Shift selection to right
      m_bHorzScrollBarLocked = TRUE;
      static const TCHAR pszText[] = _T("\t");
      for (int L = nStartLine; L <= nEndLine; L++)
      {
         int x, y;
         m_pTextBuffer->InsertText(this, L, 0, pszText, y, x, CE_ACTION_INDENT); // [JRT]
      }
      m_bHorzScrollBarLocked = FALSE;
      RecalcHorzScrollBar();

      m_pTextBuffer->FlushUndoGroup(this);
      return;
   }

   if (m_bOvrMode)
   {
      CPoint ptCursorPos = GetCursorPos();
      ASSERT_VALIDTEXTPOS(ptCursorPos);

      int nLineLength = GetLineLength(ptCursorPos.y);
      LPCTSTR pszLineChars = GetLineChars(ptCursorPos.y);
      if (ptCursorPos.x < nLineLength)
      {
         int nTabSize = GetTabSize();
         int nChars = nTabSize - CalculateActualOffset(ptCursorPos.y, ptCursorPos.x) % nTabSize;
         ASSERT(nChars > 0 && nChars <= nTabSize);

         while (nChars > 0)
         {
            if (ptCursorPos.x == nLineLength)
               break;
            if (pszLineChars[ptCursorPos.x] == _T('\t'))
            {
               ptCursorPos.x++;
               break;
            }
            ptCursorPos.x++;
            nChars--;
         }
         ASSERT(ptCursorPos.x <= nLineLength);
         ASSERT_VALIDTEXTPOS(ptCursorPos);

         SetSelection(ptCursorPos, ptCursorPos);
         SetAnchor(ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);
         return;
      }
   }

   m_pTextBuffer->BeginUndoGroup();

   DeleteCurrentSelection();

   CPoint ptCursorPos = GetCursorPos();
   ASSERT_VALIDTEXTPOS(ptCursorPos);

   static const TCHAR pszText[] = _T("\t");
   int x, y;
   m_pTextBuffer->InsertText(this, ptCursorPos.y, ptCursorPos.x, pszText, y, x, CE_ACTION_TYPING); // [JRT]
   ptCursorPos.x = x;
   ptCursorPos.y = y;
   ASSERT_VALIDTEXTPOS(ptCursorPos);
   SetSelection(ptCursorPos, ptCursorPos);
   SetAnchor(ptCursorPos);
   SetCursorPos(ptCursorPos);
   EnsureVisible(ptCursorPos);

   m_pTextBuffer->FlushUndoGroup(this);
}

void ZCrystalEditView::OnEditUntab()
{
   if (! QueryEditable())
      return;

   BOOL bTabify = FALSE;
   CPoint ptSelStart, ptSelEnd;
   if (IsSelection())
   {
      GetSelection(ptSelStart, ptSelEnd);
      bTabify = ptSelStart.y != ptSelEnd.y;
   }

   if (bTabify)
   {
      m_pTextBuffer->BeginUndoGroup();

      CPoint ptSelStart, ptSelEnd;
      GetSelection(ptSelStart, ptSelEnd);
      int nStartLine = ptSelStart.y;
      int nEndLine = ptSelEnd.y;
      ptSelStart.x = 0;
      if (ptSelEnd.x > 0)
      {
         if (ptSelEnd.y == GetLineCount() - 1)
         {
            ptSelEnd.x = GetLineLength(ptSelEnd.y);
         }
         else
         {
            ptSelEnd.x = 0;
            ptSelEnd.y++;
         }
      }
      else
         nEndLine--;
      SetSelection(ptSelStart, ptSelEnd);
      SetCursorPos(ptSelEnd);
      EnsureVisible(ptSelEnd);

      // Shift selection to left
      m_bHorzScrollBarLocked = TRUE;
      for (int L = nStartLine; L <= nEndLine; L++)
      {
         int nLength = GetLineLength(L);
         if (nLength > 0)
         {
            LPCTSTR pszChars = GetLineChars(L);
            int nPos = 0, nOffset = 0;
            while (nPos < nLength)
            {
               if (pszChars[nPos] == _T(' '))
               {
                  nPos++;
                  if (++ nOffset >= GetTabSize())
                     break;
               }
               else
               {
                  if (pszChars[nPos] == _T('\t'))
                     nPos++;
                  break;
               }
            }

            if (nPos > 0)
               m_pTextBuffer->DeleteText(this, L, 0, L, nPos, CE_ACTION_INDENT); // [JRT]
         }
      }
      m_bHorzScrollBarLocked = FALSE;
      RecalcHorzScrollBar();

      m_pTextBuffer->FlushUndoGroup(this);
   }
   else
   {
      CPoint ptCursorPos = GetCursorPos();
      ASSERT_VALIDTEXTPOS(ptCursorPos);
      if (ptCursorPos.x > 0)
      {
         int nTabSize = GetTabSize();
         int nOffset = CalculateActualOffset(ptCursorPos.y, ptCursorPos.x);
         int nNewOffset = nOffset / nTabSize * nTabSize;
         if (nOffset == nNewOffset && nNewOffset > 0)
            nNewOffset -= nTabSize;
         ASSERT(nNewOffset >= 0);

         LPCTSTR pszChars = GetLineChars(ptCursorPos.y);
         int nCurrentOffset = 0;
         int k = 0;
         while (nCurrentOffset < nNewOffset)
         {
            if (pszChars[k] == _T('\t'))
               nCurrentOffset = nCurrentOffset / nTabSize * nTabSize + nTabSize;
            else
               nCurrentOffset++;
            k++;
         }

         ASSERT(nCurrentOffset == nNewOffset);

         ptCursorPos.x = k;
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         SetSelection(ptCursorPos, ptCursorPos);
         SetAnchor(ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);
      }
   }
}

void ZCrystalEditView::OnUpdateIndicatorCol(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(FALSE);
}

void ZCrystalEditView::OnUpdateIndicatorOvr(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_bOvrMode);
}

void ZCrystalEditView::OnUpdateIndicatorRead(CCmdUI* pCmdUI)
{
   if (m_pTextBuffer == NULL)
      pCmdUI->Enable(FALSE);
   else
      pCmdUI->Enable(m_pTextBuffer->GetReadOnly());
}

void ZCrystalEditView::OnEditSwitchOvrmode()
{
   m_bOvrMode = ! m_bOvrMode;
}

void ZCrystalEditView::OnUpdateEditSwitchOvrmode(CCmdUI* pCmdUI)
{
   pCmdUI->SetCheck(m_bOvrMode ? 1 : 0);
}

DROPEFFECT ZEditDropTargetImpl::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
   if (! pDataObject->IsDataAvailable(CF_TEXT))
   {
      m_pOwner->HideDropIndicator();
      return DROPEFFECT_NONE;
   }
   m_pOwner->ShowDropIndicator(point);
   if (dwKeyState & MK_CONTROL)
      return DROPEFFECT_COPY;
   return DROPEFFECT_MOVE;
}

void ZEditDropTargetImpl::OnDragLeave(CWnd* pWnd)
{
   m_pOwner->HideDropIndicator();
}

DROPEFFECT ZEditDropTargetImpl::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
/*
   if (! pDataObject->IsDataAvailable(CF_TEXT))
   {
      m_pOwner->HideDropIndicator();
      return DROPEFFECT_NONE;
   }
*/
   //
   // [JRT]
   //
   bool bDataSupported = false;

   if ((!m_pOwner) ||                           // If No Owner
       (!( m_pOwner->QueryEditable())) ||       // Or Not Editable
       (m_pOwner->GetDisableDragAndDrop()))     // Or Drag And Drop Disabled
   {
      m_pOwner -> HideDropIndicator();          // Hide Drop Caret
      return DROPEFFECT_NONE;                   // Return DE_NONE
   }
// if ((pDataObject->IsDataAvailable( CF_TEXT )) ||  // If Text Available
//     (pDataObject -> IsDataAvailable( xxx )) ||    // Or xxx Available
//     (pDataObject -> IsDataAvailable( yyy )))      // Or yyy Available
   if (pDataObject->IsDataAvailable(CF_TEXT))  // If Text Available
   {
      bDataSupported = true;                    // Set Flag
   }
   if (!bDataSupported)                         // If No Supported Formats Available
   {
      m_pOwner->HideDropIndicator();                   // Hide Drop Caret
      return DROPEFFECT_NONE;                          // Return DE_NONE
   }
   m_pOwner->ShowDropIndicator(point);
   if (dwKeyState & MK_CONTROL)
      return DROPEFFECT_COPY;
   return DROPEFFECT_MOVE;
}

BOOL ZEditDropTargetImpl::OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
   //
   // [JRT]          ( m_pOwner -> GetDisableDragAndDrop() ) )    // Or Drag And Drop Disabled
   //
   bool bDataSupported = false;

   m_pOwner->HideDropIndicator();                // Hide Drop Caret
   if ((!m_pOwner) ||                            // If No Owner
       (!(m_pOwner->QueryEditable())) ||         // Or Not Editable
       (m_pOwner->GetDisableDragAndDrop()))      // Or Drag And Drop Disabled
   {
      return DROPEFFECT_NONE;                    // Return DE_NONE
   }
// if ((pDataObject->IsDataAvailable( CF_TEXT )) || // If Text Available
//     (pDataObject->IsDataAvailable( xxx )) ||     // Or xxx Available
//     (pDataObject->IsDataAvailable( yyy )) )      // Or yyy Available
   if (pDataObject->IsDataAvailable(CF_TEXT))  // If Text Available
   {
      bDataSupported = true;                       // Set Flag
   }
   if (!bDataSupported)                         // If No Supported Formats Available
   {
      return DROPEFFECT_NONE;                       // Return DE_NONE
   }
   return (m_pOwner->DoDropText(pDataObject, point));     // Return Result Of Drop
}

DROPEFFECT ZEditDropTargetImpl::OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point)
{
   ASSERT(m_pOwner == pWnd);
   m_pOwner->DoDragScroll(point);

   if (dwKeyState & MK_CONTROL)
      return DROPEFFECT_COPY;
   return DROPEFFECT_MOVE;
}

void ZCrystalEditView::DoDragScroll(const CPoint &point)
{
   CRect rcClientRect;
   GetClientRect(rcClientRect);
   if (point.y < rcClientRect.top + DRAG_BORDER_Y)
   {
      HideDropIndicator();
      ScrollUp();
      UpdateWindow();
      ShowDropIndicator(point);
      return;
   }
   if (point.y >= rcClientRect.bottom - DRAG_BORDER_Y)
   {
      HideDropIndicator();
      ScrollDown();
      UpdateWindow();
      ShowDropIndicator(point);
      return;
   }
   if (point.x < rcClientRect.left + GetMarginWidth() + DRAG_BORDER_X)
   {
      HideDropIndicator();
      ScrollLeft();
      UpdateWindow();
      ShowDropIndicator(point);
      return;
   }
   if (point.x >= rcClientRect.right - DRAG_BORDER_X)
   {
      HideDropIndicator();
      ScrollRight();
      UpdateWindow();
      ShowDropIndicator(point);
      return;
   }
}

BOOL ZCrystalEditView::IsDraggingText() const
{
   return m_bDraggingText;
}

BOOL ZCrystalEditView::DoDropText(COleDataObject *pDataObject, const CPoint &ptClient)
{
   HGLOBAL hData = pDataObject->GetGlobalData(CF_TEXT);
   if (hData == NULL)
      return FALSE;

   CPoint ptDropPos = ClientToText(ptClient);
   if (IsDraggingText() && IsInsideSelection(ptDropPos))
   {
      SetAnchor(ptDropPos);
      SetSelection(ptDropPos, ptDropPos);
      SetCursorPos(ptDropPos);
      EnsureVisible(ptDropPos);
      return FALSE;
   }

   LPSTR pszText = (LPSTR) ::GlobalLock(hData);
   if (pszText == NULL)
      return FALSE;

   int x, y;
   USES_CONVERSION;
   m_pTextBuffer->InsertText(this, ptDropPos.y, ptDropPos.x, A2T(pszText), y, x, CE_ACTION_DRAGDROP); // [JRT]
   CPoint ptCurPos(x, y);
   ASSERT_VALIDTEXTPOS(ptCurPos);
   SetAnchor(ptDropPos);
   SetSelection(ptDropPos, ptCurPos);
   SetCursorPos(ptCurPos);
   EnsureVisible(ptCurPos);

   ::GlobalUnlock(hData);
   return TRUE;
}

int ZCrystalEditView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
// if (ZCrystalEditView::OnCreate(lpCreateStruct) == -1)
//    return -1;

//?SetFontOverride( );
   memset(&m_lfBaseFont, 0, sizeof(m_lfBaseFont));
   lstrcpy(m_lfBaseFont.lfFaceName, _T("Consolas "));
   m_lfBaseFont.lfHeight = 0;
   m_lfBaseFont.lfWeight = FW_NORMAL;
   m_lfBaseFont.lfItalic = FALSE;
   m_lfBaseFont.lfCharSet = DEFAULT_CHARSET;
   m_lfBaseFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
   m_lfBaseFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
   m_lfBaseFont.lfQuality = DEFAULT_QUALITY;
   m_lfBaseFont.lfPitchAndFamily = DEFAULT_PITCH;

   if (CView::OnCreate(lpCreateStruct) == -1)
      return -1;

   ASSERT(m_hAccel == NULL);
   m_hAccel = ::LoadAccelerators(GetResourceHandle(), MAKEINTRESOURCE(IDR_DEFAULT_ACCEL));
   ASSERT(m_hAccel != NULL);
// return 0;

   ASSERT(m_pOleDropTarget == NULL);
   m_pOleDropTarget = new ZEditDropTargetImpl(this);
   if (! m_pOleDropTarget->Register(this))
   {
      TRACE0("Warning: Unable to register drop target for ZCrystalEditView.\n");
      delete m_pOleDropTarget;
      m_pOleDropTarget = NULL;
   }
   else
   {
      TRACE("Register successful for drop target for ZCrystalEditView hWnd: %d\n", m_hWnd );
   }
   ::SetFocus( m_hWnd );
   return 0;
}

void ZCrystalEditView::OnDestroy()
{
   if (m_pOleDropTarget != NULL)
   {
      m_pOleDropTarget->Revoke();
      delete m_pOleDropTarget;
      m_pOleDropTarget = NULL;
   }

   DetachFromBuffer();
   m_hAccel = NULL;

   CView::OnDestroy();
   int k;
   for (k = 0; k < 4; k++)
   {
      if (m_apFonts[k] != NULL)
      {
         m_apFonts[k]->DeleteObject();
         delete m_apFonts[k];
         m_apFonts[k] = NULL;
      }
   }
   if (m_pCacheBitmap != NULL)
   {
      delete m_pCacheBitmap;
      m_pCacheBitmap = NULL;
   }
}


void ZCrystalEditView::ShowDropIndicator(const CPoint &point)
{
   if (! m_bDropPosVisible)
   {
      HideCursor();
      m_ptSavedCaretPos = GetCursorPos();
      m_bDropPosVisible = TRUE;
      ::CreateCaret(m_hWnd, (HBITMAP) 1, 2, GetLineHeight());
   }
   m_ptDropPos = ClientToText(point);
   if (m_ptDropPos.x >= m_nOffsetChar)
   {
      SetCaretPos(TextToClient(m_ptDropPos));
      ShowCaret();
   }
   else
   {
      HideCaret();
   }
}

void ZCrystalEditView::HideDropIndicator()
{
   if (m_bDropPosVisible)
   {
      SetCursorPos(m_ptSavedCaretPos);
      ShowCursor();
      m_bDropPosVisible = FALSE;
   }
}

DROPEFFECT ZCrystalEditView::GetDropEffect()
{
   return DROPEFFECT_COPY | DROPEFFECT_MOVE;
// return DROPEFFECT_COPY;
}

void ZCrystalEditView::OnDropSource(DROPEFFECT de)
{
   ASSERT(de == DROPEFFECT_COPY || de == DROPEFFECT_MOVE);
   if (! IsDraggingText())
      return;

   ASSERT_VALIDTEXTPOS(m_ptDraggedTextBegin);
   ASSERT_VALIDTEXTPOS(m_ptDraggedTextEnd);

   if (de == DROPEFFECT_MOVE)
   {
      m_pTextBuffer->DeleteText(this, m_ptDraggedTextBegin.y, m_ptDraggedTextBegin.x, m_ptDraggedTextEnd.y,
                                m_ptDraggedTextEnd.x, CE_ACTION_DRAGDROP); // [JRT]
   }
}

void ZCrystalEditView::UpdateView(ZCrystalEditView *pSource, ZUpdateContext *pContext, DWORD dwFlags, int nLineIndex /*= -1*/)
{
// ZCrystalEditView::UpdateView(pSource, pContext, dwFlags, nLineIndex);

   if (dwFlags & UPDATE_RESET)
   {
      ResetView();
      RecalcVertScrollBar();
      RecalcHorzScrollBar();
      return;
   }

   int nLineCount = GetLineCount();
   ASSERT(nLineCount > 0);
   ASSERT(nLineIndex >= -1 && nLineIndex < nLineCount);
   if ((dwFlags & UPDATE_SINGLELINE) != 0)
   {
      ASSERT(nLineIndex != -1);
      // All text below this line should be reparsed
      if (m_pdwParseCookies != NULL)
      {
         ASSERT(m_nParseArraySize == nLineCount);
         memset(m_pdwParseCookies + nLineIndex, 0xff, sizeof(DWORD) * (m_nParseArraySize - nLineIndex));
      }
      // This line'th actual length must be recalculated
      if (m_pnActualLineLength != NULL)
      {
         ASSERT(m_nActualLengthArraySize == nLineCount);
         m_pnActualLineLength[nLineIndex] = -1;
      }
      // Repaint the lines
      InvalidateLines(nLineIndex, -1, TRUE);
   }
   else
   {
      if (nLineIndex == -1)
         nLineIndex = 0;      // Refresh all text
      // All text below this line should be reparsed
      if (m_pdwParseCookies != NULL)
      {
         if (m_nParseArraySize != nLineCount)
         {
            // Reallocate cookies array
            DWORD *pdwNewArray = new DWORD[nLineCount];
            if (nLineIndex > 0)
               memcpy(pdwNewArray, m_pdwParseCookies, sizeof(DWORD) * nLineIndex);
            delete m_pdwParseCookies;
            m_nParseArraySize = nLineCount;
            m_pdwParseCookies = pdwNewArray;
         }
         memset(m_pdwParseCookies + nLineIndex, 0xff, sizeof(DWORD) * (m_nParseArraySize - nLineIndex));
      }
      // Recalculate actual length for all lines below this
      if (m_pnActualLineLength != NULL)
      {
         if (m_nActualLengthArraySize != nLineCount)
         {
            // Reallocate actual length array
            int *pnNewArray = new int[nLineCount];
            if (nLineIndex > 0)
               memcpy(pnNewArray, m_pnActualLineLength, sizeof(int) * nLineIndex);
            delete m_pnActualLineLength;
            m_nActualLengthArraySize = nLineCount;
            m_pnActualLineLength = pnNewArray;
         }
         memset(m_pnActualLineLength + nLineIndex, 0xff, sizeof(DWORD) * (m_nActualLengthArraySize - nLineIndex));
      }
      // Repaint the lines
      InvalidateLines(nLineIndex, -1, TRUE);
   }

   // All those points must be recalculated and validated
   if (pContext != NULL)
   {
      pContext->RecalcPoint(m_ptCursorPos);
      pContext->RecalcPoint(m_ptSelStart);
      pContext->RecalcPoint(m_ptSelEnd);
      pContext->RecalcPoint(m_ptAnchor);
      ASSERT_VALIDTEXTPOS(m_ptCursorPos);
      ASSERT_VALIDTEXTPOS(m_ptSelStart);
      ASSERT_VALIDTEXTPOS(m_ptSelEnd);
      ASSERT_VALIDTEXTPOS(m_ptAnchor);
      if (m_bDraggingText)
      {
         pContext->RecalcPoint(m_ptDraggedTextBegin);
         pContext->RecalcPoint(m_ptDraggedTextEnd);
         ASSERT_VALIDTEXTPOS(m_ptDraggedTextBegin);
         ASSERT_VALIDTEXTPOS(m_ptDraggedTextEnd);
      }
      CPoint ptTopLine(0, m_nTopLine);
      pContext->RecalcPoint(ptTopLine);
      ASSERT_VALIDTEXTPOS(ptTopLine);
      m_nTopLine = ptTopLine.y;
      UpdateCaret();
   }

   // Recalculate vertical scrollbar, if needed
   if ((dwFlags & UPDATE_VERTRANGE) != 0)
   {
      if (! m_bVertScrollBarLocked)
         RecalcVertScrollBar();
   }

   // Recalculate horizontal scrollbar, if needed
   if ((dwFlags & UPDATE_HORZRANGE) != 0)
   {
      m_nMaxLineLength = -1;
      if (! m_bHorzScrollBarLocked)
         RecalcHorzScrollBar();
   }


   if (m_bSelectionPushed && pContext != NULL)
   {
      pContext->RecalcPoint(m_ptSavedSelStart);
      pContext->RecalcPoint(m_ptSavedSelEnd);
      ASSERT_VALIDTEXTPOS(m_ptSavedSelStart);
      ASSERT_VALIDTEXTPOS(m_ptSavedSelEnd);
   }
}

void ZCrystalEditView::OnEditReplace()
{
   if (! QueryEditable())
      return;

   CWinApp *pApp = AfxGetApp();
   ASSERT(pApp != NULL);

   ZEditReplaceDlg dlg(this);

   // Take search parameters from registry
   dlg.m_bMatchCase = pApp->GetProfileInt(REG_REPLACE_SUBKEY, REG_MATCH_CASE, FALSE);
   dlg.m_bWholeWord = pApp->GetProfileInt(REG_REPLACE_SUBKEY, REG_WHOLE_WORD, FALSE);
   dlg.m_sText = pApp->GetProfileString(REG_REPLACE_SUBKEY, REG_FIND_WHAT, _T(""));
   dlg.m_sNewText = pApp->GetProfileString(REG_REPLACE_SUBKEY, REG_REPLACE_WITH, _T(""));

   if (IsSelection())
   {
      GetSelection(m_ptSavedSelStart, m_ptSavedSelEnd);
      m_bSelectionPushed = TRUE;

      dlg.m_nScope = 0; // Replace in current selection
      dlg.m_ptCurrentPos = m_ptSavedSelStart;
      dlg.m_bEnableScopeSelection = TRUE;
      dlg.m_ptBlockBegin = m_ptSavedSelStart;
      dlg.m_ptBlockEnd = m_ptSavedSelEnd;
   }
   else
   {
      dlg.m_nScope = 1; // Replace in whole text
      dlg.m_ptCurrentPos = GetCursorPos();
      dlg.m_bEnableScopeSelection = FALSE;
   }

   // Execute Replace dialog
   m_bShowInactiveSelection = TRUE;
   dlg.DoModal();
   m_bShowInactiveSelection = FALSE;

   // Restore selection
   if (m_bSelectionPushed)
   {
      SetSelection(m_ptSavedSelStart, m_ptSavedSelEnd);
      m_bSelectionPushed = FALSE;
   }

   // Save search parameters to registry
   pApp->WriteProfileInt(REG_REPLACE_SUBKEY, REG_MATCH_CASE, dlg.m_bMatchCase);
   pApp->WriteProfileInt(REG_REPLACE_SUBKEY, REG_WHOLE_WORD, dlg.m_bWholeWord);
   pApp->WriteProfileString(REG_REPLACE_SUBKEY, REG_FIND_WHAT, dlg.m_sText);
   pApp->WriteProfileString(REG_REPLACE_SUBKEY, REG_REPLACE_WITH, dlg.m_sNewText);
}

BOOL ZCrystalEditView::ReplaceSelection(LPCTSTR pszNewText)
{
   ASSERT(pszNewText != NULL);
   if (! IsSelection())
      return FALSE;

   DeleteCurrentSelection();

   CPoint ptCursorPos = GetCursorPos();
   ASSERT_VALIDTEXTPOS(ptCursorPos);
   int x, y;
   m_pTextBuffer->InsertText(this, ptCursorPos.y, ptCursorPos.x, pszNewText, y, x, CE_ACTION_REPLACE); //   [JRT]
   CPoint ptEndOfBlock = CPoint(x, y);
   ASSERT_VALIDTEXTPOS(ptCursorPos);
   ASSERT_VALIDTEXTPOS(ptEndOfBlock);
   SetAnchor(ptEndOfBlock);
   SetSelection(ptCursorPos, ptEndOfBlock);
   SetCursorPos(ptEndOfBlock);
   EnsureVisible(ptEndOfBlock);
   return TRUE;
}

void ZCrystalEditView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
   BOOL bCanUndo = CanUndo();
   pCmdUI->Enable(bCanUndo);

   // Since we need text only for menus...
   if (pCmdUI->m_pMenu != NULL)
   {
      // Tune up 'resource handle'
      HINSTANCE hOldResHandle = AfxGetResourceHandle();
      AfxSetResourceHandle(GetResourceHandle());

      CString menu;
      if (bCanUndo)
      {
         // Format menu item text using the provided item description
         CString desc;
         m_pTextBuffer->GetUndoDescription(desc);
         menu.Format(IDS_MENU_UNDO_FORMAT, desc);
      }
      else
      {
         // Just load default menu item text
         menu.LoadString(IDS_MENU_UNDO_DEFAULT);
      }

      // Restore original handle
      AfxSetResourceHandle(hOldResHandle);

      // Set menu item text
      pCmdUI->SetText(menu);
   }
}

BOOL ZCrystalEditView::CanUndo()
{
   return (m_pTextBuffer != NULL && m_pTextBuffer->CanUndo());
}

void ZCrystalEditView::OnEditUndo()
{
   Undo();
}

void ZCrystalEditView::Undo()
{
   if (CanUndo())
   {
      CPoint ptCursorPos;
      if (m_pTextBuffer->Undo(ptCursorPos))
      {
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         SetAnchor(ptCursorPos);
         SetSelection(ptCursorPos, ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);
      }
   }
}

// [JRT]
void ZCrystalEditView::SetDisableBSAtSOL(BOOL bDisableBSAtSOL)
{
   m_bDisableBSAtSOL = bDisableBSAtSOL;
}

BOOL ZCrystalEditView::CanRedo()
{
   return (m_pTextBuffer != NULL && m_pTextBuffer->CanRedo());
}

void ZCrystalEditView::OnEditRedo()
{
   Redo();
}

void ZCrystalEditView::Redo()
{
   if (CanRedo())
   {
      CPoint ptCursorPos;
      if (m_pTextBuffer->Redo(ptCursorPos))
      {
         ASSERT_VALIDTEXTPOS(ptCursorPos);
         SetAnchor(ptCursorPos);
         SetSelection(ptCursorPos, ptCursorPos);
         SetCursorPos(ptCursorPos);
         EnsureVisible(ptCursorPos);
      }
   }
}

void ZCrystalEditView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
   BOOL bCanRedo = m_pTextBuffer != NULL && m_pTextBuffer->CanRedo();
   pCmdUI->Enable(bCanRedo);

   // Since we need text only for menus...
   if (pCmdUI->m_pMenu != NULL)
   {
      // Tune up 'resource handle'
      HINSTANCE hOldResHandle = AfxGetResourceHandle();
      AfxSetResourceHandle(GetResourceHandle());

      CString menu;
      if (bCanRedo)
      {
         // Format menu item text using the provided item description
         CString desc;
         m_pTextBuffer->GetRedoDescription(desc);
         menu.Format(IDS_MENU_REDO_FORMAT, desc);
      }
      else
      {
         // Just load default menu item text
         menu.LoadString(IDS_MENU_REDO_DEFAULT);
      }

      // Restore original handle
      AfxSetResourceHandle(hOldResHandle);

      // Set menu item text
      pCmdUI->SetText(menu);
   }
}

void ZCrystalEditView::OnEditOperation(int nAction, LPCTSTR pszText)
{
   if (m_bAutoIndent)
   {
      // Analyse last action...
      if (nAction == CE_ACTION_TYPING && _tcscmp(pszText, _T("\r\n")) == 0 && ! m_bOvrMode)
      {
         // Enter stroke!
         CPoint ptCursorPos = GetCursorPos();
         ASSERT(ptCursorPos.y > 0);

         // Take indentation from the previos line
         int nLength = m_pTextBuffer->GetLineLength(ptCursorPos.y - 1);
         LPCTSTR pszLineChars = m_pTextBuffer->GetLineChars(ptCursorPos.y - 1);
         int nPos = 0;
         while (nPos < nLength && isspace(pszLineChars[nPos]))
            nPos++;

         if (nPos > 0)
         {
            // Insert part of the previos line
            TCHAR *pszInsertStr = (TCHAR *) _alloca(sizeof(TCHAR) * (nLength + 1));
            strncpy_s(pszInsertStr, sizeof(TCHAR) * (nLength + 1), pszLineChars, nPos);
            pszInsertStr[nPos] = 0;

            int x, y;
            m_pTextBuffer->InsertText(NULL, ptCursorPos.y, ptCursorPos.x, pszInsertStr, y, x, CE_ACTION_AUTOINDENT);
            CPoint pt(x, y);
            SetCursorPos(pt);
            SetSelection(pt, pt);
            SetAnchor(pt);
            EnsureVisible(pt);
         }
      }
   }
}


#define TAB_CHARACTER            _T('\xBB')
#define SPACE_CHARACTER          _T('\x95')
#define DEFAULT_PRINT_MARGIN     1000           // 10 millimeters

#define SMOOTH_SCROLL_FACTOR     6
#define CRYSTAL_TIMER_DRAGSEL    1001

////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView

/////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView construction/destruction

//ZCrystalEditView::s_hResourceInst( NULL );

BOOL ZCrystalEditView::PreCreateWindow(CREATESTRUCT& cs)
{
   CWnd *pParentWnd = CWnd::FromHandlePermanent(cs.hwndParent);
   if (pParentWnd == NULL || ! pParentWnd->IsKindOf(RUNTIME_CLASS(CSplitterWnd)))
   {
      // View must always create its own scrollbars,
      // if only it's not used within splitter
      cs.style |= (WS_HSCROLL | WS_VSCROLL);
   }
   cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS);
   return CView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView drawing

void ZCrystalEditView::GetSelection(CPoint &ptStart, CPoint &ptEnd)
{
   PrepareSelBounds();
   ptStart = m_ptDrawSelStart;
   ptEnd = m_ptDrawSelEnd;
}

ZCrystalTextBuffer *ZCrystalEditView::LocateTextBuffer()
{
   return NULL;
}

int ZCrystalEditView::GetLineActualLength(int nLineIndex)
{
   int nLineCount = GetLineCount();
   ASSERT(nLineCount > 0);
   ASSERT(nLineIndex >= 0 && nLineIndex < nLineCount);
   if (m_pnActualLineLength == NULL)
   {
      m_pnActualLineLength = new int[nLineCount];
      memset(m_pnActualLineLength, 0xff, sizeof(int) * nLineCount);
      m_nActualLengthArraySize = nLineCount;
   }

   if (m_pnActualLineLength[nLineIndex] >= 0)
      return m_pnActualLineLength[nLineIndex];

   // Actual line length is not determined yet, let's calculate a little
   int nActualLength = 0;
   int nLength = GetLineLength(nLineIndex);
   if (nLength > 0)
   {
      LPCTSTR pszLine = GetLineChars(nLineIndex);
      LPTSTR pszChars = (LPTSTR) _alloca(sizeof(TCHAR) * (nLength + 1));
      memcpy(pszChars, pszLine, sizeof(TCHAR) * nLength);
      pszChars[nLength] = 0;
      LPTSTR pszCurrent = pszChars;

      int nTabSize = GetTabSize();
      for (;;)
      {
#ifdef _UNICODE
         LPTSTR psz = wcschr(pszCurrent, L'\t');
#else
         LPTSTR psz = strchr(pszCurrent, '\t');
#endif
         if (psz == NULL)
         {
            nActualLength += (pszChars + nLength - pszCurrent);
            break;
         }

         nActualLength += (psz - pszCurrent);
         nActualLength += (nTabSize - nActualLength % nTabSize);
         pszCurrent = psz + 1;
      }
   }

   m_pnActualLineLength[nLineIndex] = nActualLength;
   return nActualLength;
}

void ZCrystalEditView::ScrollToChar(int nNewOffsetChar, BOOL bNoSmoothScroll /*= FALSE*/, BOOL bTrackScrollBar /*= TRUE*/)
{
   // For now, ignoring bNoSmoothScroll and m_bSmoothScroll
   if (m_nOffsetChar != nNewOffsetChar)
   {
      int nScrollChars = m_nOffsetChar - nNewOffsetChar;
      m_nOffsetChar = nNewOffsetChar;
      CRect rcScroll;
      GetClientRect(&rcScroll);
      rcScroll.left += GetMarginWidth();
      ScrollWindow(nScrollChars * GetCharWidth(), 0, &rcScroll, &rcScroll);
      UpdateWindow();
      if (bTrackScrollBar)
         RecalcHorzScrollBar(TRUE);
   }
}

void ZCrystalEditView::ScrollToLine(int nNewTopLine, BOOL bNoSmoothScroll /*= FALSE*/, BOOL bTrackScrollBar /*= TRUE*/)
{
   if (m_nTopLine != nNewTopLine)
   {
      if (bNoSmoothScroll || ! m_bSmoothScroll)
      {
         int nScrollLines = m_nTopLine - nNewTopLine;
         m_nTopLine = nNewTopLine;
         ScrollWindow(0, nScrollLines * GetLineHeight());
         UpdateWindow();
         if (bTrackScrollBar)
            RecalcVertScrollBar(TRUE);
      }
      else
      {
         // Do smooth scrolling
         int nLineHeight = GetLineHeight();
         if (m_nTopLine > nNewTopLine)
         {
            int nIncrement = (m_nTopLine - nNewTopLine) / SMOOTH_SCROLL_FACTOR + 1;
            while (m_nTopLine != nNewTopLine)
            {
               int nTopLine = m_nTopLine - nIncrement;
               if (nTopLine < nNewTopLine)
                  nTopLine = nNewTopLine;
               int nScrollLines = nTopLine - m_nTopLine;
               m_nTopLine = nTopLine;
               ScrollWindow(0, - nLineHeight * nScrollLines);
               UpdateWindow();
               if (bTrackScrollBar)
                  RecalcVertScrollBar(TRUE);
            }
         }
         else
         {
            int nIncrement = (nNewTopLine - m_nTopLine) / SMOOTH_SCROLL_FACTOR + 1;
            while (m_nTopLine != nNewTopLine)
            {
               int nTopLine = m_nTopLine + nIncrement;
               if (nTopLine > nNewTopLine)
                  nTopLine = nNewTopLine;
               int nScrollLines = nTopLine - m_nTopLine;
               m_nTopLine = nTopLine;
               ScrollWindow(0, - nLineHeight * nScrollLines);
               UpdateWindow();
               if (bTrackScrollBar)
                  RecalcVertScrollBar(TRUE);
            }
         }
      }
   }
}

void ZCrystalEditView::ExpandChars(LPCTSTR pszChars, int nOffset, int nCount, CString &line)
{
   if (nCount <= 0)
   {
      line = _T("");
      return;
   }

   int nTabSize = GetTabSize();
   int nActualOffset = 0;
   int k;
   for (k = 0; k < nOffset; k++)
   {
      if (pszChars[k] == _T('\t'))
         nActualOffset += (nTabSize - nActualOffset % nTabSize);
      else
         nActualOffset++;
   }

   pszChars += nOffset;
   int nLength = nCount;

   int nTabCount = 0;
   for (k = 0; k < nLength; k++)
   {
      if (pszChars[k] == _T('\t'))
         nTabCount++;
   }

   LPTSTR pszBuf = line.GetBuffer(nLength + nTabCount * (nTabSize - 1) + 1);
   int nCurPos = 0;
   if (nTabCount > 0 || m_bViewTabs)
   {
      for (k = 0; k < nLength; k++)
      {
         if (pszChars[k] == _T('\t'))
         {
            int nSpaces = nTabSize - (nActualOffset + nCurPos) % nTabSize;
            if (m_bViewTabs)
            {
               pszBuf[nCurPos++] = TAB_CHARACTER;
               nSpaces--;
            }
            while (nSpaces > 0)
            {
               pszBuf[nCurPos++] = _T(' ');
               nSpaces--;
            }
         }
         else
         {
            if (pszChars[k] == _T(' ') && m_bViewTabs)
               pszBuf[nCurPos] = SPACE_CHARACTER;
            else
               pszBuf[nCurPos] = pszChars[k];
            nCurPos++;
         }
      }
   }
   else
   {
      memcpy(pszBuf, pszChars, sizeof(TCHAR) * nLength);
      nCurPos = nLength;
   }
   pszBuf[nCurPos] = 0;
   line.ReleaseBuffer();
}

void ZCrystalEditView::DrawLineHelperImpl(CDC *pdc, CPoint &ptOrigin, const CRect &rcClip,
                            LPCTSTR pszChars, int nOffset, int nCount)
{
   ASSERT(nCount >= 0);
   if (nCount > 0)
   {
      CString line;
      ExpandChars(pszChars, nOffset, nCount, line);
      int nWidth = rcClip.right - ptOrigin.x;
      if (nWidth > 0)
      {
         int nCharWidth = GetCharWidth();
         int nCount = line.GetLength();
         int nCountFit = nWidth / nCharWidth + 1;
         if (nCount > nCountFit)
            nCount = nCountFit;
#ifdef _DEBUG
         //CSize sz = pdc->GetTextExtent(line, nCount);
         //ASSERT(sz.cx == m_nCharWidth * nCount);
#endif
         /*
         CRect rcBounds = rcClip;
         rcBounds.left = ptOrigin.x;
         rcBounds.right = rcBounds.left + GetCharWidth() * nCount;
         pdc->ExtTextOut(rcBounds.left, rcBounds.top, ETO_OPAQUE, &rcBounds, NULL, 0, NULL);
         */
         VERIFY(pdc->ExtTextOut(ptOrigin.x, ptOrigin.y, ETO_CLIPPED, &rcClip, line, nCount, NULL));
      }
      ptOrigin.x += GetCharWidth() * line.GetLength();
   }
}

void ZCrystalEditView::DrawLineHelper(CDC *pdc, CPoint &ptOrigin, const CRect &rcClip, int nColorIndex,
                            LPCTSTR pszChars, int nOffset, int nCount, CPoint ptTextPos)
{
   if (nCount > 0)
   {
      if (m_bFocused || m_bShowInactiveSelection)
      {
         int nSelBegin = 0, nSelEnd = 0;
         if (m_ptDrawSelStart.y > ptTextPos.y)
         {
            nSelBegin = nCount;
         }
         else
         if (m_ptDrawSelStart.y == ptTextPos.y)
         {
            nSelBegin = m_ptDrawSelStart.x - ptTextPos.x;
            if (nSelBegin < 0)
               nSelBegin = 0;
            if (nSelBegin > nCount)
               nSelBegin = nCount;
         }
         if (m_ptDrawSelEnd.y > ptTextPos.y)
         {
            nSelEnd = nCount;
         }
         else
         if (m_ptDrawSelEnd.y == ptTextPos.y)
         {
            nSelEnd = m_ptDrawSelEnd.x - ptTextPos.x;
            if (nSelEnd < 0)
               nSelEnd = 0;
            if (nSelEnd > nCount)
               nSelEnd = nCount;
         }

         ASSERT(nSelBegin >= 0 && nSelBegin <= nCount);
         ASSERT(nSelEnd >= 0 && nSelEnd <= nCount);
         ASSERT(nSelBegin <= nSelEnd);

         // Draw part of the text before selection
         if (nSelBegin > 0)
         {
            DrawLineHelperImpl(pdc, ptOrigin, rcClip, pszChars, nOffset, nSelBegin);
         }
         if (nSelBegin < nSelEnd)
         {
            COLORREF crOldBk = pdc->SetBkColor(GetColor(COLORINDEX_SELBKGND));
            COLORREF crOldText = pdc->SetTextColor(GetColor(COLORINDEX_SELTEXT));
            DrawLineHelperImpl(pdc, ptOrigin, rcClip, pszChars, nOffset + nSelBegin, nSelEnd - nSelBegin);
            pdc->SetBkColor(crOldBk);
            pdc->SetTextColor(crOldText);
         }
         if (nSelEnd < nCount)
         {
            DrawLineHelperImpl(pdc, ptOrigin, rcClip, pszChars, nOffset + nSelEnd, nCount - nSelEnd);
         }
      }
      else
      {
         DrawLineHelperImpl(pdc, ptOrigin, rcClip, pszChars, nOffset, nCount);
      }
   }
}

void ZCrystalEditView::GetLineColors(int nLineIndex, COLORREF &crBkgnd,
               COLORREF &crText, BOOL &bDrawWhitespace)
{
   DWORD dwLineFlags = GetLineFlags(nLineIndex);
   bDrawWhitespace = TRUE;
   crText = RGB(255, 255, 255);
   if (dwLineFlags & LF_EXECUTION)
   {
      crBkgnd = RGB(0, 128, 0);
      return;
   }
   if (dwLineFlags & LF_BREAKPOINT)
   {
      crBkgnd = RGB(255, 0, 0);
      return;
   }
   if (dwLineFlags & LF_INVALID_BREAKPOINT)
   {
      crBkgnd = RGB(128, 128, 0);
      return;
   }
   crBkgnd = CLR_NONE;
   crText = CLR_NONE;
   bDrawWhitespace = FALSE;
}

DWORD ZCrystalEditView::GetParseCookie(int nLineIndex)
{
   int nLineCount = GetLineCount();
   if (m_pdwParseCookies == NULL)
   {
      m_nParseArraySize = nLineCount;
      m_pdwParseCookies = new DWORD[nLineCount];
      memset(m_pdwParseCookies, 0xff, nLineCount * sizeof(DWORD));
   }

   if (nLineIndex < 0)
      return 0;
   if (m_pdwParseCookies[nLineIndex] != (DWORD) -1)
      return m_pdwParseCookies[nLineIndex];

   int k = nLineIndex;
   while (k >= 0 && m_pdwParseCookies[k] == (DWORD) -1)
      k--;
   k++;

   int nBlocks;
   while (k <= nLineIndex)
   {
      DWORD dwCookie = 0;
      if (k > 0)
         dwCookie = m_pdwParseCookies[k - 1];
      ASSERT(dwCookie != (DWORD) -1);
      m_pdwParseCookies[k] = ParseLine(dwCookie, k, NULL, nBlocks);
      ASSERT(m_pdwParseCookies[k] != (DWORD) -1);
      k++;
   }

   return m_pdwParseCookies[nLineIndex];
}

void ZCrystalEditView::DrawSingleLine(CDC *pDC, const CRect &rc, int nLineIndex)
{
   ASSERT(nLineIndex >= -1 && nLineIndex < GetLineCount());

   if (nLineIndex == -1)
   {
      // Draw line beyond the text
      pDC->FillSolidRect(rc, GetColor(COLORINDEX_WHITESPACE));
      return;
   }

   // Acquire the background color for the current line
   BOOL bDrawWhitespace = FALSE;
   COLORREF crBkgnd, crText;
   GetLineColors(nLineIndex, crBkgnd, crText, bDrawWhitespace);
   if (crBkgnd == CLR_NONE)
      crBkgnd = GetColor(COLORINDEX_BKGND);

   int nLength = GetLineLength(nLineIndex);
   if (nLength == 0)
   {
      // Draw the empty line
      CRect rect = rc;
      if ((m_bFocused || m_bShowInactiveSelection) && IsInsideSelBlock(CPoint(0, nLineIndex)))
      {
         pDC->FillSolidRect(rect.left, rect.top, GetCharWidth(), rect.Height(), GetColor(COLORINDEX_SELBKGND));
         rect.left += GetCharWidth();
      }
      pDC->FillSolidRect(rect, bDrawWhitespace ? crBkgnd : GetColor(COLORINDEX_WHITESPACE));
      return;
   }

   // Parse the line
   LPCTSTR pszChars = GetLineChars(nLineIndex);
   DWORD dwCookie = GetParseCookie(nLineIndex - 1);
   TEXTBLOCK *pBuf = (TEXTBLOCK *) _alloca(sizeof(TEXTBLOCK) * nLength * 3);
   int nBlocks = 0;
   m_pdwParseCookies[nLineIndex] = ParseLine(dwCookie, nLineIndex, pBuf, nBlocks);
   ASSERT(m_pdwParseCookies[nLineIndex] != (DWORD) -1);

   // Draw the line text
   CPoint origin(rc.left - m_nOffsetChar * GetCharWidth(), rc.top);
   pDC->SetBkColor(crBkgnd);
   if (crText != CLR_NONE)
      pDC->SetTextColor(crText);
   BOOL bColorSet = FALSE;

   if (nBlocks > 0)
   {
      int k;
      ASSERT(pBuf[0].m_nCharPos >= 0 && pBuf[0].m_nCharPos <= nLength);
      if (crText == CLR_NONE)
         pDC->SetTextColor(GetColor(COLORINDEX_NORMALTEXT));
      pDC->SelectObject(GetFont(pDC, GetItalic(COLORINDEX_NORMALTEXT), GetBold(COLORINDEX_NORMALTEXT)));
      DrawLineHelper(pDC, origin, rc, COLORINDEX_NORMALTEXT, pszChars, 0, pBuf[0].m_nCharPos, CPoint(0, nLineIndex));
      for (k = 0; k < nBlocks - 1; k++)
      {
         ASSERT(pBuf[k].m_nCharPos >= 0 && pBuf[k].m_nCharPos <= nLength);
         if (crText == CLR_NONE)
            pDC->SetTextColor(GetColor(pBuf[k].m_nColorIndex));
         pDC->SelectObject(GetFont(pDC, GetItalic(pBuf[k].m_nColorIndex), GetBold(pBuf[k].m_nColorIndex)));
         DrawLineHelper(pDC, origin, rc, pBuf[k].m_nColorIndex, pszChars,
                     pBuf[k].m_nCharPos, pBuf[k + 1].m_nCharPos - pBuf[k].m_nCharPos,
                     CPoint(pBuf[k].m_nCharPos, nLineIndex));
      }
      ASSERT(pBuf[nBlocks - 1].m_nCharPos >= 0 && pBuf[nBlocks - 1].m_nCharPos <= nLength);
      if (crText == CLR_NONE)
         pDC->SetTextColor(GetColor(pBuf[nBlocks - 1].m_nColorIndex));
      pDC->SelectObject(GetFont(pDC, GetItalic(pBuf[nBlocks - 1].m_nColorIndex),
                     GetBold(pBuf[nBlocks - 1].m_nColorIndex)));
      DrawLineHelper(pDC, origin, rc, pBuf[nBlocks - 1].m_nColorIndex, pszChars,
                     pBuf[nBlocks - 1].m_nCharPos, nLength - pBuf[nBlocks - 1].m_nCharPos,
                     CPoint(pBuf[nBlocks - 1].m_nCharPos, nLineIndex));
   }
   else
   {
      if (crText == CLR_NONE)
         pDC->SetTextColor(GetColor(COLORINDEX_NORMALTEXT));
      pDC->SelectObject(GetFont(pDC, GetItalic(COLORINDEX_NORMALTEXT), GetBold(COLORINDEX_NORMALTEXT)));
      DrawLineHelper(pDC, origin, rc, COLORINDEX_NORMALTEXT, pszChars, 0, nLength, CPoint(0, nLineIndex));
   }

   // Draw whitespaces to the left of the text
   CRect frect = rc;
   if (origin.x > frect.left)
      frect.left = origin.x;
   if (frect.right > frect.left)
   {
      if ((m_bFocused || m_bShowInactiveSelection) && IsInsideSelBlock(CPoint(nLength, nLineIndex)))
      {
         pDC->FillSolidRect(frect.left, frect.top, GetCharWidth(), frect.Height(),
                                    GetColor(COLORINDEX_SELBKGND));
         frect.left += GetCharWidth();
      }
      if (frect.right > frect.left)
         pDC->FillSolidRect(frect, bDrawWhitespace ? crBkgnd : GetColor(COLORINDEX_WHITESPACE));
   }
}

COLORREF ZCrystalEditView::GetColor(int nColorIndex)
{
   switch (nColorIndex)
   {
   case COLORINDEX_WHITESPACE:
   case COLORINDEX_BKGND:
      return ::GetSysColor(COLOR_WINDOW);
   case COLORINDEX_NORMALTEXT:
      return ::GetSysColor(COLOR_WINDOWTEXT);
   case COLORINDEX_SELMARGIN:
      return ::GetSysColor(COLOR_SCROLLBAR);
   case COLORINDEX_PREPROCESSOR:
      return RGB(0, 128, 192);
   case COLORINDEX_COMMENT:
      return RGB( 46, 139, 87); // RGB(128, 128, 128);
   // [JRT]: Enabled Support For Numbers...
   case COLORINDEX_NUMBER:
      return RGB(0x80, 0x00, 0x00);
   // [JRT]: Support For C/C++ Operators
   case COLORINDEX_OPERATOR:
      return RGB(0x00, 0x00, 0x00);
   case COLORINDEX_KEYWORD:
      return RGB(0, 0, 255);
   case COLORINDEX_SELBKGND:
      return RGB(0, 0, 0);
   case COLORINDEX_SELTEXT:
      return RGB(255, 255, 255);
   }
   return RGB(255, 0, 0);
}

DWORD ZCrystalEditView::GetLineFlags(int nLineIndex)
{
   if (m_pTextBuffer == NULL)
      return 0;
   return m_pTextBuffer->GetLineFlags(nLineIndex);
}

void ZCrystalEditView::DrawMargin(CDC *pdc, const CRect &rect, int nLineIndex)
{
   if (! m_bSelMargin)
   {
      pdc->FillSolidRect(rect, GetColor(COLORINDEX_BKGND));
      return;
   }

   pdc->FillSolidRect(rect, GetColor(COLORINDEX_SELMARGIN));

   int nImageIndex = -1;
   if (nLineIndex >= 0)
   {
      DWORD dwLineFlags = GetLineFlags(nLineIndex);
      static const DWORD adwFlags[] =
      {
         LF_EXECUTION,
         LF_BREAKPOINT,
         LF_COMPILATION_ERROR,
         LF_BOOKMARK(1),
         LF_BOOKMARK(2),
         LF_BOOKMARK(3),
         LF_BOOKMARK(4),
         LF_BOOKMARK(5),
         LF_BOOKMARK(6),
         LF_BOOKMARK(7),
         LF_BOOKMARK(8),
         LF_BOOKMARK(9),
         LF_BOOKMARK(0),
         LF_BOOKMARKS,
         LF_INVALID_BREAKPOINT
      };
      int k;
      for (k = 0; k <= sizeof(adwFlags) / sizeof(adwFlags[0]); k++)
      {
         if ((dwLineFlags & adwFlags[k]) != 0)
         {
            nImageIndex = k;
            break;
         }
      }
   }

   if (nImageIndex >= 0)
   {
      if (m_pIcons == NULL)
      {
         m_pIcons = new CImageList;
         VERIFY(m_pIcons->Create(IDR_MARGIN_ICONS, 16, 16, RGB(255, 255, 255)));
      }
      CPoint pt(rect.left + 2, rect.top + (rect.Height() - 16) / 2);
      VERIFY(m_pIcons->Draw(pdc, nImageIndex, pt, ILD_TRANSPARENT));
   }
}

BOOL ZCrystalEditView::IsInsideSelBlock(CPoint ptTextPos)
{
   ASSERT_VALIDTEXTPOS(ptTextPos);
   if (ptTextPos.y < m_ptDrawSelStart.y)
      return FALSE;
   if (ptTextPos.y > m_ptDrawSelEnd.y)
      return FALSE;
   if (ptTextPos.y < m_ptDrawSelEnd.y && ptTextPos.y > m_ptDrawSelStart.y)
      return TRUE;
   if (m_ptDrawSelStart.y < m_ptDrawSelEnd.y)
   {
      if (ptTextPos.y == m_ptDrawSelEnd.y)
         return ptTextPos.x < m_ptDrawSelEnd.x;
      ASSERT(ptTextPos.y == m_ptDrawSelStart.y);
      return ptTextPos.x >= m_ptDrawSelStart.x;
   }
   ASSERT(m_ptDrawSelStart.y == m_ptDrawSelEnd.y);
   return ptTextPos.x >= m_ptDrawSelStart.x && ptTextPos.x < m_ptDrawSelEnd.x;
}

BOOL ZCrystalEditView::IsInsideSelection(const CPoint &ptTextPos)
{
   PrepareSelBounds();
   return IsInsideSelBlock(ptTextPos);
}

void ZCrystalEditView::PrepareSelBounds()
{
   if (m_ptSelStart.y < m_ptSelEnd.y || (m_ptSelStart.y == m_ptSelEnd.y && m_ptSelStart.x < m_ptSelEnd.x))
   {
      m_ptDrawSelStart = m_ptSelStart;
      m_ptDrawSelEnd = m_ptSelEnd;
   }
   else
   {
      m_ptDrawSelStart = m_ptSelEnd;
      m_ptDrawSelEnd = m_ptSelStart;
   }
}

void ZCrystalEditView::OnDraw(CDC *pdc)
{
   CRect rcClient;
   GetClientRect(rcClient);

   int nLineCount = GetLineCount();
   int nLineHeight = GetLineHeight();
   PrepareSelBounds();

   CDC cacheDC;
   VERIFY(cacheDC.CreateCompatibleDC(pdc));
   if (m_pCacheBitmap == NULL)
   {
      m_pCacheBitmap = new CBitmap;
      VERIFY(m_pCacheBitmap->CreateCompatibleBitmap(pdc, rcClient.Width(), nLineHeight));
   }
   CBitmap *pOldBitmap = cacheDC.SelectObject(m_pCacheBitmap);

   CRect rcLine;
   rcLine = rcClient;
   rcLine.bottom = rcLine.top + nLineHeight;
   CRect rcCacheMargin(0, 0, GetMarginWidth(), nLineHeight);
   CRect rcCacheLine(GetMarginWidth(), 0, rcLine.Width(), nLineHeight);

   int nCurrentLine = m_nTopLine;
   while (rcLine.top < rcClient.bottom)
   {
      if (nCurrentLine < nLineCount)
      {
         DrawMargin(&cacheDC, rcCacheMargin, nCurrentLine);
         DrawSingleLine(&cacheDC, rcCacheLine, nCurrentLine);
      }
      else
      {
         DrawMargin(&cacheDC, rcCacheMargin, -1);
         DrawSingleLine(&cacheDC, rcCacheLine, -1);
      }

      VERIFY(pdc->BitBlt(rcLine.left, rcLine.top, rcLine.Width(), rcLine.Height(), &cacheDC, 0, 0, SRCCOPY));

      nCurrentLine++;
      rcLine.OffsetRect(0, nLineHeight);
   }

   cacheDC.SelectObject(pOldBitmap);
   cacheDC.DeleteDC();
}

void ZCrystalEditView::ResetView()
{
   m_bAutoIndent = TRUE;
   m_bOvrMode = FALSE;

   m_bFocused = FALSE;
   m_bCursorHidden = FALSE;
   m_nTopLine = 0;
   m_nOffsetChar = 0;
   m_nLineHeight = -1;
   m_nCharWidth = -1;
   m_nTabSize = 4;
   m_nMaxLineLength = -1;
   m_nScreenLines = -1;
   m_nScreenChars = -1;
   m_nIdealCharPos = -1;
   m_ptAnchor.x = 0;
   m_ptAnchor.y = 0;
   if (m_pIcons != NULL)
   {
      delete m_pIcons;
      m_pIcons = NULL;
   }
   int k;
   for (k = 0; k < 4; k++)
   {
      if (m_apFonts[k] != NULL)
      {
         m_apFonts[k]->DeleteObject();
         delete m_apFonts[k];
         m_apFonts[k] = NULL;
      }
   }
   if (m_pdwParseCookies != NULL)
   {
      delete m_pdwParseCookies;
      m_pdwParseCookies = NULL;
   }
   if (m_pnActualLineLength != NULL)
   {
      delete m_pnActualLineLength;
      m_pnActualLineLength = NULL;
   }
   m_nParseArraySize = 0;
   m_nActualLengthArraySize = 0;
   m_ptCursorPos.x = 0;
   m_ptCursorPos.y = 0;
   m_ptSelStart = m_ptSelEnd = m_ptCursorPos;
   m_bDragSelection = FALSE;
   m_bVertScrollBarLocked = FALSE;
   m_bHorzScrollBarLocked = FALSE;
   if (::IsWindow(m_hWnd))
      UpdateCaret();
   m_bLastSearch = FALSE;
   m_bShowInactiveSelection = FALSE;
   m_bPrintHeader = FALSE;
   m_bPrintFooter = TRUE;

   m_hAccel = NULL;
   if ( m_pDropTarget )
   {
      m_pDropTarget->Revoke();
      delete m_pDropTarget;
      m_pDropTarget = NULL;
   }
   m_bBookmarkExist  = FALSE; // More bookmarks
   m_bMultipleSearch = FALSE; // More search
}

void ZCrystalEditView::UpdateCaret()
{
   ASSERT_VALIDTEXTPOS(m_ptCursorPos);
   if (m_bFocused && ! m_bCursorHidden &&
      CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x) >= m_nOffsetChar)
   {
      CreateSolidCaret(2, GetLineHeight());
      SetCaretPos(TextToClient(m_ptCursorPos));
      ShowCaret();
   }
   else
   {
      HideCaret();
   }
}

int ZCrystalEditView::GetTabSize()
{
   ASSERT(m_nTabSize >= 0 && m_nTabSize <= 64);
   return m_nTabSize;
}

void ZCrystalEditView::SetTabSize(int nTabSize)
{
   ASSERT(nTabSize >= 0 && nTabSize <= 64);
   if (m_nTabSize != nTabSize)
   {
      m_nTabSize = nTabSize;
      if (m_pnActualLineLength != NULL)
      {
         delete m_pnActualLineLength;
         m_pnActualLineLength = NULL;
      }
      m_nActualLengthArraySize = 0;
      m_nMaxLineLength = -1;
      RecalcHorzScrollBar();
      Invalidate();
      UpdateCaret();
   }
}

int ZCrystalEditView::GetFontSize( CDC *pDC, int nFontHeight )
{
   int nFontSize = 0;

/*   if ( nFontHeight < 0 )
   {
      nFontSize = -::MulDiv( nFontHeight, 72, pDC->GetDeviceCaps( LOGPIXELSY ) );
   }
   else
*/ {
      TEXTMETRIC tm;
      ::ZeroMemory( &tm, sizeof( TEXTMETRIC ) );
      pDC->GetTextMetrics( &tm );

      nFontSize = -::MulDiv( nFontHeight, 72, pDC->GetDeviceCaps( LOGPIXELSY ) ) - tm.tmInternalLeading;
   }

   return nFontSize;
}

CFont *ZCrystalEditView::GetFont(CDC *pDC, BOOL bItalic /*= FALSE*/, BOOL bBold /*= FALSE*/)
{
   int nIndex = 0;
   if (bBold)
      nIndex |= 1;
   if (bItalic)
      nIndex |= 2;

   if (m_apFonts[nIndex] == NULL)
   {
      m_apFonts[nIndex] = new CFont;
      m_lfBaseFont.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
      m_lfBaseFont.lfItalic = (BYTE) bItalic;
      strcpy_s( m_lfBaseFont.lfFaceName, sizeof( m_lfBaseFont.lfFaceName ), "Consolas" );
      m_lfBaseFont.lfHeight = GetFontSize( pDC, 16 );
   // m_lfBaseFont.lfWidth = 7;
      if (! m_apFonts[nIndex]->CreateFontIndirect(&m_lfBaseFont))
      {
         delete m_apFonts[nIndex];
         m_apFonts[nIndex] = NULL;
         return CView::GetFont();
      }

   }
   return m_apFonts[nIndex];
}

void ZCrystalEditView::CalcLineCharDim()
{
   CDC *pDC = GetDC();
   CFont *pOldFont = pDC->SelectObject(GetFont( pDC ));
   CSize szCharExt = pDC->GetTextExtent(_T("W"));
   m_nLineHeight = szCharExt.cy;
   if (m_nLineHeight < 1)
      m_nLineHeight = 1;
   m_nCharWidth = szCharExt.cx;
   /*
   TEXTMETRIC tm;
   if (pdc->GetTextMetrics(&tm))
      m_nCharWidth -= tm.tmOverhang;
   */
   pDC->SelectObject(pOldFont);
   ReleaseDC(pDC);
}

int ZCrystalEditView::GetLineHeight()
{
   if (m_nLineHeight == -1)
      CalcLineCharDim();
   return m_nLineHeight;
}

int ZCrystalEditView::GetCharWidth()
{
   if (m_nCharWidth == -1)
      CalcLineCharDim();
   return m_nCharWidth;
}

int ZCrystalEditView::GetMaxLineLength()
{
   if (m_nMaxLineLength == -1)
   {
      m_nMaxLineLength = 0;
      int nLineCount = GetLineCount();
      int k;
      for (k = 0; k < nLineCount; k++)
      {
         int nActualLength = GetLineActualLength(k);
         if (m_nMaxLineLength < nActualLength)
            m_nMaxLineLength = nActualLength;
      }
   }
   return m_nMaxLineLength;
}

ZCrystalEditView *ZCrystalEditView::GetSiblingView(int nRow, int nCol)
{
   CSplitterWnd *pSplitter = GetParentSplitter(this, FALSE);
   if (pSplitter == NULL)
      return NULL;
   CWnd *pWnd = CWnd::FromHandlePermanent(::GetDlgItem(pSplitter->m_hWnd, pSplitter->IdFromRowCol(nRow, nCol)));
   if (pWnd == NULL || ! pWnd->IsKindOf(RUNTIME_CLASS(ZCrystalEditView)))
      return NULL;
   return (ZCrystalEditView *) pWnd;
}

void ZCrystalEditView::OnInitialUpdate()
{
   CView::OnInitialUpdate();

   AttachToBuffer(NULL);

   CSplitterWnd *pSplitter = GetParentSplitter(this, FALSE);
   if (pSplitter != NULL)
   {
      // See CSplitterWnd::IdFromRowCol() implementation
      int nRow = (GetDlgCtrlID() - AFX_IDW_PANE_FIRST) / 16;
      int nCol = (GetDlgCtrlID() - AFX_IDW_PANE_FIRST) % 16;
      ASSERT(nRow >= 0 && nRow < pSplitter->GetRowCount());
      ASSERT(nCol >= 0 && nCol < pSplitter->GetColumnCount());

      if (nRow > 0)
      {
         ZCrystalEditView *pSiblingView = GetSiblingView(0, nCol);
         if (pSiblingView != NULL && pSiblingView != this)
         {
            m_nOffsetChar = pSiblingView->m_nOffsetChar;
            ASSERT(m_nOffsetChar >= 0 && m_nOffsetChar <= GetMaxLineLength());
         }
      }

      if (nCol > 0)
      {
         ZCrystalEditView *pSiblingView = GetSiblingView(nRow, 0);
         if (pSiblingView != NULL && pSiblingView != this)
         {
            m_nTopLine = pSiblingView->m_nTopLine;
            ASSERT(m_nTopLine >= 0 && m_nTopLine < GetLineCount());
         }
      }
   }
}


/////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView printing

void ZCrystalEditView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
   CView::OnPrepareDC(pDC, pInfo);

   if (pInfo != NULL)
   {
      pInfo->m_bContinuePrinting = TRUE;
      if (m_pnPages != NULL && (int) pInfo->m_nCurPage > m_nPrintPages)
         pInfo->m_bContinuePrinting = FALSE;
   }
}

BOOL ZCrystalEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
   return DoPreparePrinting(pInfo);
}

int ZCrystalEditView::PrintLineHeight(CDC *pdc, int nLine)
{
   ASSERT(nLine >= 0 && nLine < GetLineCount());
   ASSERT(m_nPrintLineHeight > 0);
   int nLength = GetLineLength(nLine);
   if (nLength == 0)
      return m_nPrintLineHeight;

   CString line;
   LPCTSTR pszChars = GetLineChars(nLine);
   ExpandChars(pszChars, 0, nLength, line);
   CRect rcPrintArea = m_rcPrintArea;
   pdc->DrawText(line, &rcPrintArea, DT_LEFT | DT_NOPREFIX | DT_TOP | DT_WORDBREAK | DT_CALCRECT);
   return rcPrintArea.Height();
}

void ZCrystalEditView::GetPrintHeaderText(int nPageNum, CString &text)
{
   ASSERT(m_bPrintHeader);
   text = _T("");
}

void ZCrystalEditView::GetPrintFooterText(int nPageNum, CString &text)
{
   ASSERT(m_bPrintFooter);
   text.Format(_T("Page %d/%d"), nPageNum, m_nPrintPages);
}

void ZCrystalEditView::PrintHeader(CDC *pdc, int nPageNum)
{
   CRect rcHeader = m_rcPrintArea;
   rcHeader.bottom = rcHeader.top;
   rcHeader.top -= (m_nPrintLineHeight + m_nPrintLineHeight / 2);

   CString text;
   GetPrintHeaderText(nPageNum, text);
   if (! text.IsEmpty())
      pdc->DrawText(text, &rcHeader, DT_CENTER | DT_NOPREFIX | DT_TOP | DT_SINGLELINE);
}

void ZCrystalEditView::PrintFooter(CDC *pdc, int nPageNum)
{
   CRect rcFooter = m_rcPrintArea;
   rcFooter.top = rcFooter.bottom;
   rcFooter.bottom += (m_nPrintLineHeight + m_nPrintLineHeight / 2);

   CString text;
   GetPrintFooterText(nPageNum, text);
   if (! text.IsEmpty())
      pdc->DrawText(text, &rcFooter, DT_CENTER | DT_NOPREFIX | DT_BOTTOM | DT_SINGLELINE);
}

void ZCrystalEditView::RecalcPageLayouts(CDC *pdc, CPrintInfo *pInfo)
{
   m_ptPageArea = pInfo->m_rectDraw;
   m_ptPageArea.NormalizeRect();

   m_nPrintLineHeight = pdc->GetTextExtent(_T("W")).cy;

   m_rcPrintArea = m_ptPageArea;
   CSize szTopLeft, szBottomRight;
   CWinApp *pApp = AfxGetApp();
   ASSERT(pApp != NULL);
   szTopLeft.cx = pApp->GetProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_LEFT, DEFAULT_PRINT_MARGIN);
   szBottomRight.cx = pApp->GetProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_RIGHT, DEFAULT_PRINT_MARGIN);
   szTopLeft.cy = pApp->GetProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_TOP, DEFAULT_PRINT_MARGIN);
   szBottomRight.cy = pApp->GetProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_BOTTOM, DEFAULT_PRINT_MARGIN);
   pdc->HIMETRICtoLP(&szTopLeft);
   pdc->HIMETRICtoLP(&szBottomRight);
   m_rcPrintArea.left += szTopLeft.cx;
   m_rcPrintArea.right -= szBottomRight.cx;
   m_rcPrintArea.top += szTopLeft.cy;
   m_rcPrintArea.bottom -= szBottomRight.cy;
   if (m_bPrintHeader)
      m_rcPrintArea.top += m_nPrintLineHeight + m_nPrintLineHeight / 2;
   if (m_bPrintFooter)
      m_rcPrintArea.bottom += m_nPrintLineHeight + m_nPrintLineHeight / 2;

   int nLimit = 32;
   m_nPrintPages = 1;
   m_pnPages = new int[nLimit];
   m_pnPages[0] = 0;

   int nLineCount = GetLineCount();
   int nLine = 1;
   int y = m_rcPrintArea.top + PrintLineHeight(pdc, 0);
   while (nLine < nLineCount)
   {
      int nHeight = PrintLineHeight(pdc, nLine);
      if (y + nHeight <= m_rcPrintArea.bottom)
      {
         y += nHeight;
      }
      else
      {
         ASSERT(nLimit >= m_nPrintPages);
         if (nLimit <= m_nPrintPages)
         {
            nLimit += 32;
            int *pnNewPages = new int[nLimit];
            memcpy(pnNewPages, m_pnPages, sizeof(int) * m_nPrintPages);
            delete m_pnPages;
            m_pnPages = pnNewPages;
         }
         ASSERT(nLimit > m_nPrintPages);
         m_pnPages[m_nPrintPages++] = nLine;
         y = m_rcPrintArea.top + nHeight;
      }
      nLine++;
   }
}

void ZCrystalEditView::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
   ASSERT(m_pnPages == NULL);
   ASSERT(m_pPrintFont == NULL);
   CFont *pDisplayFont = GetFont( pDC );

   LOGFONT lf;
   pDisplayFont->GetLogFont(&lf);

   CDC *pDisplayDC = GetDC();
   lf.lfHeight = MulDiv(lf.lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), pDisplayDC->GetDeviceCaps(LOGPIXELSY) * 2);
   lf.lfWidth = MulDiv(lf.lfWidth, pDC->GetDeviceCaps(LOGPIXELSX), pDisplayDC->GetDeviceCaps(LOGPIXELSX) * 2);
   ReleaseDC(pDisplayDC);

   m_pPrintFont = new CFont;
   if (! m_pPrintFont->CreateFontIndirect(&lf))
   {
      delete m_pPrintFont;
      m_pPrintFont = NULL;
      return;
   }

   pDC->SelectObject(m_pPrintFont);
}

void ZCrystalEditView::OnEndPrinting(CDC *pdc, CPrintInfo *pInfo)
{
   if (m_pPrintFont != NULL)
   {
      delete m_pPrintFont;
      m_pPrintFont = NULL;
   }
   if (m_pnPages != NULL)
   {
      delete m_pnPages;
      m_pnPages = NULL;
   }
   m_nPrintPages = 0;
   m_nPrintLineHeight = 0;
}

void ZCrystalEditView::OnPrint(CDC* pdc, CPrintInfo* pInfo)
{
   if (m_pnPages == NULL)
   {
      RecalcPageLayouts(pdc, pInfo);
      ASSERT(m_pnPages != NULL);
   }

   ASSERT(pInfo->m_nCurPage >= 1 && (int) pInfo->m_nCurPage <= m_nPrintPages);
   int nLine = m_pnPages[pInfo->m_nCurPage - 1];
   int nEndLine = GetLineCount();
   if ((int) pInfo->m_nCurPage < m_nPrintPages)
      nEndLine = m_pnPages[pInfo->m_nCurPage];
   TRACE(_T("Printing page %d of %d, lines %d - %d\n"), pInfo->m_nCurPage, m_nPrintPages,
                  nLine, nEndLine - 1);

   if (m_bPrintHeader)
      PrintHeader(pdc, pInfo->m_nCurPage);
   if (m_bPrintFooter)
      PrintFooter(pdc, pInfo->m_nCurPage);

   int y = m_rcPrintArea.top;
   for (; nLine < nEndLine; nLine++)
   {
      int nLineLength = GetLineLength(nLine);
      if (nLineLength == 0)
      {
         y += m_nPrintLineHeight;
         continue;
      }

      CRect rcPrintRect = m_rcPrintArea;
      rcPrintRect.top = y;
      LPCTSTR pszChars = GetLineChars(nLine);
      CString line;
      ExpandChars(pszChars, 0, nLineLength, line);
      y += pdc->DrawText(line, &rcPrintRect, DT_LEFT | DT_NOPREFIX | DT_TOP | DT_WORDBREAK);
   }
}


/////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView message handlers

int ZCrystalEditView::GetLineCount()
{
   if (m_pTextBuffer == NULL)
      return 1;      // Single empty line
   int nLineCount = m_pTextBuffer->GetLineCount();
   ASSERT(nLineCount > 0);
   return nLineCount;
}

int ZCrystalEditView::GetLineLength(int nLineIndex)
{
   if (m_pTextBuffer == NULL)
      return 0;
   return m_pTextBuffer->GetLineLength(nLineIndex);
}

LPCTSTR ZCrystalEditView::GetLineChars(int nLineIndex)
{
   if (m_pTextBuffer == NULL)
      return NULL;
   return m_pTextBuffer->GetLineChars(nLineIndex);
}

void ZCrystalEditView::AttachToBuffer(ZCrystalTextBuffer *pBuf /*= NULL*/)
{
   if (m_pTextBuffer != NULL)
      m_pTextBuffer->RemoveView(this);
   if (pBuf == NULL)
   {
      pBuf = LocateTextBuffer();
      // ...
   }
   m_pTextBuffer = pBuf;
   if (m_pTextBuffer != NULL)
      m_pTextBuffer->AddView(this);
   ResetView();

   // Init scrollbars
   CScrollBar *pVertScrollBarCtrl = GetScrollBarCtrl(SB_VERT);
   if (pVertScrollBarCtrl != NULL)
      pVertScrollBarCtrl->EnableScrollBar(GetScreenLines() >= GetLineCount() ?
                                 ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
   CScrollBar *pHorzScrollBarCtrl = GetScrollBarCtrl(SB_HORZ);
   if (pHorzScrollBarCtrl != NULL)
      pHorzScrollBarCtrl->EnableScrollBar(GetScreenChars() >= GetMaxLineLength() ?
                                 ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);

   // Update scrollbars
   RecalcVertScrollBar();
   RecalcHorzScrollBar();
}

void ZCrystalEditView::DetachFromBuffer()
{
   if (m_pTextBuffer != NULL)
   {
      m_pTextBuffer->RemoveView(this);
      m_pTextBuffer = NULL;
      ResetView();
   }
}

int ZCrystalEditView::GetScreenLines()
{
   if (m_nScreenLines == -1)
   {
      CRect rect;
      GetClientRect(&rect);
      m_nScreenLines = rect.Height() / GetLineHeight();
   }
   return m_nScreenLines;
}

BOOL ZCrystalEditView::GetItalic(int nColorIndex)
{
   return FALSE;
}

BOOL ZCrystalEditView::GetBold(int nColorIndex)
{
   return FALSE;
}

int ZCrystalEditView::GetScreenChars()
{
   if (m_nScreenChars == -1)
   {
      CRect rect;
      GetClientRect(&rect);
      m_nScreenChars = (rect.Width() - GetMarginWidth()) / GetCharWidth();
   }
   return m_nScreenChars;
}

BOOL ZCrystalEditView::OnEraseBkgnd(CDC *pdc)
{
   return TRUE;
}

void ZCrystalEditView::OnSize(UINT nType, int cx, int cy)
{
   CView::OnSize(nType, cx, cy);

   if (m_pCacheBitmap != NULL)
   {
      m_pCacheBitmap->DeleteObject();
      delete m_pCacheBitmap;
      m_pCacheBitmap = NULL;
   }
   m_nScreenLines = -1;
   m_nScreenChars = -1;
   RecalcVertScrollBar();
   RecalcHorzScrollBar();
}

void ZCrystalEditView::UpdateSiblingScrollPos(BOOL bHorz)
{
   CSplitterWnd *pSplitterWnd = GetParentSplitter(this, FALSE);
   if (pSplitterWnd != NULL)
   {
      // See CSplitterWnd::IdFromRowCol() implementation for details
      int nCurrentRow = (GetDlgCtrlID() - AFX_IDW_PANE_FIRST) / 16;
      int nCurrentCol = (GetDlgCtrlID() - AFX_IDW_PANE_FIRST) % 16;
      ASSERT(nCurrentRow >= 0 && nCurrentRow < pSplitterWnd->GetRowCount());
      ASSERT(nCurrentCol >= 0 && nCurrentCol < pSplitterWnd->GetColumnCount());

      if (bHorz)
      {
         int nCols = pSplitterWnd->GetColumnCount();
         for (int nCol = 0; nCol < nCols; nCol++)
         {
            if (nCol != nCurrentCol)   // We don't need to update ourselves
            {
               ZCrystalEditView *pSiblingView = GetSiblingView(nCurrentRow, nCol);
               if (pSiblingView != NULL)
                  pSiblingView->OnUpdateSibling(this, TRUE);
            }
         }
      }
      else
      {
         int nRows = pSplitterWnd->GetRowCount();
         for (int nRow = 0; nRow < nRows; nRow++)
         {
            if (nRow != nCurrentRow)   // We don't need to update ourselves
            {
               ZCrystalEditView *pSiblingView = GetSiblingView(nRow, nCurrentCol);
               if (pSiblingView != NULL)
                  pSiblingView->OnUpdateSibling(this, FALSE);
            }
         }
      }
   }
}

void ZCrystalEditView::OnUpdateSibling(ZCrystalEditView *pUpdateSource, BOOL bHorz)
{
   if (pUpdateSource != this)
   {
      ASSERT(pUpdateSource != NULL);
      ASSERT_KINDOF(ZCrystalEditView, pUpdateSource);
      if (bHorz)
      {
         ASSERT(pUpdateSource->m_nTopLine >= 0);
         ASSERT(pUpdateSource->m_nTopLine < GetLineCount());
         if (pUpdateSource->m_nTopLine != m_nTopLine)
         {
            ScrollToLine(pUpdateSource->m_nTopLine, TRUE, FALSE);
            UpdateCaret();
         }
      }
      else
      {
         ASSERT(pUpdateSource->m_nOffsetChar >= 0);
         ASSERT(pUpdateSource->m_nOffsetChar < GetMaxLineLength());
         if (pUpdateSource->m_nOffsetChar != m_nOffsetChar)
         {
            ScrollToChar(pUpdateSource->m_nOffsetChar, TRUE, FALSE);
            UpdateCaret();
         }
      }
   }
}

void ZCrystalEditView::RecalcVertScrollBar(BOOL bPositionOnly /*= FALSE*/)
{
   SCROLLINFO si;
   si.cbSize = sizeof(si);
   if (bPositionOnly)
   {
      si.fMask = SIF_POS;
      si.nPos = m_nTopLine;
   }
   else
   {
      if (GetScreenLines() >= GetLineCount() && m_nTopLine > 0)
      {
         m_nTopLine = 0;
         Invalidate();
         UpdateCaret();
      }
      si.fMask = SIF_DISABLENOSCROLL | SIF_PAGE | SIF_POS | SIF_RANGE;
      si.nMin = 0;
      si.nMax = GetLineCount() - 1;
      si.nPage = GetScreenLines();
      si.nPos = m_nTopLine;
   }
   VERIFY(SetScrollInfo(SB_VERT, &si));
}

void ZCrystalEditView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   CView::OnVScroll(nSBCode, nPos, pScrollBar);

   // Note we cannot use nPos because of its 16-bit nature
   SCROLLINFO si;
   si.cbSize = sizeof(si);
   si.fMask = SIF_ALL;
   VERIFY(GetScrollInfo(SB_VERT, &si));

   int nPageLines = GetScreenLines();
   int nLineCount = GetLineCount();

   int nNewTopLine;
   BOOL bDisableSmooth = TRUE;
   switch (nSBCode)
   {
   case SB_TOP:
      nNewTopLine = 0;
      bDisableSmooth = FALSE;
      break;
   case SB_BOTTOM:
      nNewTopLine = nLineCount - nPageLines + 1;
      bDisableSmooth = FALSE;
      break;
   case SB_LINEUP:
      nNewTopLine = m_nTopLine - 1;
      break;
   case SB_LINEDOWN:
      nNewTopLine = m_nTopLine + 1;
      break;
   case SB_PAGEUP:
      nNewTopLine = m_nTopLine - si.nPage + 1;
      bDisableSmooth = FALSE;
      break;
   case SB_PAGEDOWN:
      nNewTopLine = m_nTopLine + si.nPage - 1;
      bDisableSmooth = FALSE;
      break;
   case SB_THUMBPOSITION:
   case SB_THUMBTRACK:
      nNewTopLine = si.nTrackPos;
      break;
   default:
      return;
   }

   if (nNewTopLine < 0)
      nNewTopLine = 0;
   if (nNewTopLine >= nLineCount)
      nNewTopLine = nLineCount - 1;
   ScrollToLine(nNewTopLine, bDisableSmooth);
}

BOOL
ZCrystalEditView::OnMouseWheel( UINT uFlags, short nDelta, CPoint point )
{
   // A m_nRowsPerWheelNotch value less than 0 indicates that the mouse wheel scrolls whole pages, not just lines.
   int nRowsPerWheelNotch = 3;  // GetMouseScrollLines( ); // Get the number of lines per mouse wheel notch to scroll

   if ( nRowsPerWheelNotch == -1 )  // Get the number of lines per mouse wheel notch to scroll
   {
      int nPagesScrolled = nDelta / 120;

      if ( nPagesScrolled > 0 )
      {
         for ( int k = 0; k < nPagesScrolled; k++ )
         {
            PostMessage( WM_VSCROLL, SB_PAGEUP, 0 );
         }
      }
      else
      {
         for ( int k = 0; k > nPagesScrolled; k-- )
         {
            PostMessage( WM_VSCROLL, SB_PAGEDOWN, 0 );
         }
      }
   }
   else
   {
      int nRowsScrolled = nRowsPerWheelNotch * nDelta / 120;

      if ( nRowsScrolled > 0 )
      {
         for ( int k = 0; k < nRowsScrolled; k++ )
         {
            PostMessage( WM_VSCROLL, SB_LINEUP, 0 );
         }
      }
      else
      {
         for ( int k = 0; k > nRowsScrolled; k-- )
         {
            PostMessage( WM_VSCROLL, SB_LINEDOWN, 0 );
         }
      }
   }

   return( CWnd::OnMouseWheel( uFlags, nDelta, point ) );
}

void ZCrystalEditView::RecalcHorzScrollBar(BOOL bPositionOnly /*= FALSE*/)
{
   // Again, we cannot use nPos because it's 16-bit
   SCROLLINFO si;
   si.cbSize = sizeof(si);
   if (bPositionOnly)
   {
      si.fMask = SIF_POS;
      si.nPos = m_nOffsetChar;
   }
   else
   {
      if (GetScreenChars() >= GetMaxLineLength() && m_nOffsetChar > 0)
      {
         m_nOffsetChar = 0;
         Invalidate();
         UpdateCaret();
      }
      si.fMask = SIF_DISABLENOSCROLL | SIF_PAGE | SIF_POS | SIF_RANGE;
      si.nMin = 0;
      si.nMax = GetMaxLineLength() - 1;
      si.nPage = GetScreenChars();
      si.nPos = m_nOffsetChar;
   }
   VERIFY(SetScrollInfo(SB_HORZ, &si));
}

void ZCrystalEditView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   CView::OnHScroll(nSBCode, nPos, pScrollBar);

   SCROLLINFO si;
   si.cbSize = sizeof(si);
   si.fMask = SIF_ALL;
   VERIFY(GetScrollInfo(SB_HORZ, &si));

   int nPageChars = GetScreenChars();
   int nMaxLineLength = GetMaxLineLength();

   int nNewOffset;
   switch (nSBCode)
   {
   case SB_LEFT:
      nNewOffset = 0;
      break;
   case SB_BOTTOM:
      nNewOffset = nMaxLineLength - nPageChars + 1;
      break;
   case SB_LINEUP:
      nNewOffset = m_nOffsetChar - 1;
      break;
   case SB_LINEDOWN:
      nNewOffset = m_nOffsetChar + 1;
      break;
   case SB_PAGEUP:
      nNewOffset = m_nOffsetChar - si.nPage + 1;
      break;
   case SB_PAGEDOWN:
      nNewOffset = m_nOffsetChar + si.nPage - 1;
      break;
   case SB_THUMBPOSITION:
   case SB_THUMBTRACK:
      nNewOffset = si.nTrackPos;
      break;
   default:
      return;
   }

   if (nNewOffset >= nMaxLineLength)
      nNewOffset = nMaxLineLength - 1;
   if (nNewOffset < 0)
      nNewOffset = 0;
   ScrollToChar(nNewOffset, TRUE);
   UpdateCaret();
}

BOOL ZCrystalEditView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
   if (nHitTest == HTCLIENT)
   {
      CPoint pt;
      ::GetCursorPos(&pt);
      ScreenToClient(&pt);
      if (pt.x < GetMarginWidth())
      {
         ::SetCursor(::LoadCursor(GetResourceHandle(), IDC_IBEAM));
      }
      else
      {
         CPoint ptText = ClientToText(pt);
         PrepareSelBounds();
         if (IsInsideSelBlock(ptText))
         {
            // [JRT]:   Support For Disabling Drag and Drop...
            if (!m_bDisabledDragAndDrop)            // If Drag And Drop Not Disabled
               ::SetCursor(::LoadCursor(NULL, IDC_ARROW));  // Set To Arrow Cursor
         }
         else
            ::SetCursor(::LoadCursor(NULL, IDC_IBEAM));
      }
      return TRUE;
   }
   return CView::OnSetCursor(pWnd, nHitTest, message);
}

CPoint ZCrystalEditView::ClientToText(const CPoint &point)
{
   int nLineCount = GetLineCount();

   CPoint pt;
   pt.y = m_nTopLine + point.y / GetLineHeight();
   if (pt.y >= nLineCount)
      pt.y = nLineCount - 1;
   if (pt.y < 0)
      pt.y = 0;

   int nLength = 0;
   LPCTSTR pszLine = NULL;
   if (pt.y >= 0 && pt.y < nLineCount)
   {
      nLength = GetLineLength(pt.y);
      pszLine = GetLineChars(pt.y);
   }

   int nPos = m_nOffsetChar + (point.x - GetMarginWidth()) / GetCharWidth();
   if (nPos < 0)
      nPos = 0;

   int nIndex = 0, nCurPos = 0;
   int nTabSize = GetTabSize();
   while (nIndex < nLength)
   {
      if (pszLine[nIndex] == _T('\t'))
         nCurPos += (nTabSize - nCurPos % nTabSize);
      else
         nCurPos++;

      if (nCurPos > nPos)
         break;

      nIndex++;
   }

   ASSERT(nIndex >= 0 && nIndex <= nLength);
   pt.x = nIndex;
   return pt;
}

#ifdef _DEBUG
void ZCrystalEditView::AssertValidTextPos(const CPoint &point)
{
   if (GetLineCount() > 0)
   {
      ASSERT(m_nTopLine >= 0 && m_nOffsetChar >= 0);
      ASSERT(point.y >= 0 && point.y < GetLineCount());
      ASSERT(point.x >= 0 && point.x <= GetLineLength(point.y));
   }
}
#endif

CPoint ZCrystalEditView::TextToClient(const CPoint &point)
{
   ASSERT_VALIDTEXTPOS(point);
   int nLength = GetLineLength(point.y);
   LPCTSTR pszLine = GetLineChars(point.y);

   CPoint pt;
   pt.y = (point.y - m_nTopLine) * GetLineHeight();
   pt.x = 0;
   int nTabSize = GetTabSize();
   for (int nIndex = 0; nIndex < point.x; nIndex++)
   {
      if (pszLine[nIndex] == _T('\t'))
         pt.x += (nTabSize - pt.x % nTabSize);
      else
         pt.x++;
   }

   pt.x = (pt.x - m_nOffsetChar) * GetCharWidth() + GetMarginWidth();
   return pt;
}

void ZCrystalEditView::InvalidateLines(int nLine1, int nLine2, BOOL bInvalidateMargin /*= FALSE*/)
{
   bInvalidateMargin = TRUE;
   if (nLine2 == -1)
   {
      CRect rcInvalid;
      GetClientRect(&rcInvalid);
      if (! bInvalidateMargin)
         rcInvalid.left += GetMarginWidth();
      rcInvalid.top = (nLine1 - m_nTopLine) * GetLineHeight();
      InvalidateRect(&rcInvalid, FALSE);
   }
   else
   {
      if (nLine2 < nLine1)
      {
         int nTemp = nLine1;
         nLine1 = nLine2;
         nLine2 = nTemp;
      }
      CRect rcInvalid;
      GetClientRect(&rcInvalid);
      if (! bInvalidateMargin)
         rcInvalid.left += GetMarginWidth();
      rcInvalid.top = (nLine1 - m_nTopLine) * GetLineHeight();
      rcInvalid.bottom = (nLine2 - m_nTopLine + 1) * GetLineHeight();
      InvalidateRect(&rcInvalid, FALSE);
   }
}

void ZCrystalEditView::SetSelection(const CPoint &ptStart, const CPoint &ptEnd)
{
   ASSERT_VALIDTEXTPOS(ptStart);
   ASSERT_VALIDTEXTPOS(ptEnd);
   if (m_ptSelStart == ptStart)
   {
      if (m_ptSelEnd != ptEnd)
         InvalidateLines(ptEnd.y, m_ptSelEnd.y);
   }
   else
   {
      InvalidateLines(ptStart.y, ptEnd.y);
      InvalidateLines(m_ptSelStart.y, m_ptSelEnd.y);
   }
   m_ptSelStart = ptStart;
   m_ptSelEnd = ptEnd;
}

void ZCrystalEditView::AdjustTextPoint(CPoint &point)
{
   point.x += GetCharWidth() / 2;   //todo
}

void ZCrystalEditView::OnSetFocus(CWnd* pOldWnd)
{
   CView::OnSetFocus(pOldWnd);

   m_bFocused = TRUE;
   if (m_ptSelStart != m_ptSelEnd)
      InvalidateLines(m_ptSelStart.y, m_ptSelEnd.y);
   UpdateCaret();
}

DWORD ZCrystalEditView::ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems)
{
   return 0;
}

int ZCrystalEditView::CalculateActualOffset(int nLineIndex, int nCharIndex)
{
   int nLength = GetLineLength(nLineIndex);
   ASSERT(nCharIndex >= 0 && nCharIndex <= nLength);
   LPCTSTR pszChars = GetLineChars(nLineIndex);
   int nOffset = 0;
   int nTabSize = GetTabSize();
   int k;
   for (k = 0; k < nCharIndex; k++)
   {
      if (pszChars[k] == _T('\t'))
         nOffset += (nTabSize - nOffset % nTabSize);
      else
         nOffset++;
   }
   return nOffset;
}

int ZCrystalEditView::ApproxActualOffset(int nLineIndex, int nOffset)
{
   if (nOffset == 0)
      return 0;

   int nLength = GetLineLength(nLineIndex);
   LPCTSTR pszChars = GetLineChars(nLineIndex);
   int nCurrentOffset = 0;
   int nTabSize = GetTabSize();
   int k;
   for (k = 0; k < nLength; k++)
   {
      if (pszChars[k] == _T('\t'))
         nCurrentOffset += (nTabSize - nCurrentOffset % nTabSize);
      else
         nCurrentOffset++;
      if (nCurrentOffset >= nOffset)
      {
         if (nOffset <= nCurrentOffset - nTabSize / 2)
            return k;
         return k + 1;
      }
   }
   return nLength;
}

void ZCrystalEditView::EnsureVisible(CPoint pt)
{
   // Scroll vertically
   int nLineCount = GetLineCount();
   int nNewTopLine = m_nTopLine;
   if (pt.y >= nNewTopLine + GetScreenLines())
   {
      nNewTopLine = pt.y - GetScreenLines() + 1;
   }
   if (pt.y < nNewTopLine)
   {
      nNewTopLine = pt.y;
   }

   if (nNewTopLine < 0)
      nNewTopLine = 0;
   if (nNewTopLine >= nLineCount)
      nNewTopLine = nLineCount - 1;

   if (m_nTopLine != nNewTopLine)
   {
      ScrollToLine(nNewTopLine);
      UpdateSiblingScrollPos(TRUE);
   }

   // Scroll horizontally
   int nActualPos = CalculateActualOffset(pt.y, pt.x);
   int nNewOffset = m_nOffsetChar;
   if (nActualPos > nNewOffset + GetScreenChars())
   {
      nNewOffset = nActualPos - GetScreenChars();
   }
   if (nActualPos < nNewOffset)
   {
      nNewOffset = nActualPos;
   }

   if (nNewOffset >= GetMaxLineLength())
      nNewOffset = GetMaxLineLength() - 1;
   if (nNewOffset < 0)
      nNewOffset = 0;

   if (m_nOffsetChar != nNewOffset)
   {
      ScrollToChar(nNewOffset);
      UpdateCaret();
      UpdateSiblingScrollPos(FALSE);
   }
}

void ZCrystalEditView::OnKillFocus(CWnd* pNewWnd)
{
   CView::OnKillFocus(pNewWnd);

   m_bFocused = FALSE;
   UpdateCaret();
   if (m_ptSelStart != m_ptSelEnd)
      InvalidateLines(m_ptSelStart.y, m_ptSelEnd.y);
   if (m_bDragSelection)
   {
      ReleaseCapture();
      KillTimer(m_nDragSelTimer);
      m_bDragSelection = FALSE;
   }
}

void ZCrystalEditView::OnSysColorChange()
{
   CView::OnSysColorChange();
   Invalidate();
}

void ZCrystalEditView::GetText(const CPoint &ptStart, const CPoint &ptEnd, CString &text)
{
   if (m_pTextBuffer != NULL)
      m_pTextBuffer->GetText(ptStart.y, ptStart.x, ptEnd.y, ptEnd.x, text);
   else
      text = _T("");
}

HINSTANCE ZCrystalEditView::GetResourceHandle()
{
#ifdef CRYSEDIT_RES_HANDLE
   return CRYSEDIT_RES_HANDLE;
#else
   if (s_hResourceInst != NULL)
      return s_hResourceInst;

   LPLIBRARY hLibrary = SysLoadLibraryWithErrFlag( m_pZSubtask->m_vDialog, "ZdCtl", zLOADLIB_RESOURCES );
   s_hResourceInst = (HINSTANCE) SysGetInstance( hLibrary );
   return s_hResourceInst;
// return AfxGetResourceHandle();
#endif
}

void ZCrystalEditView::SetAnchor(const CPoint &ptNewAnchor)
{
   ASSERT_VALIDTEXTPOS(ptNewAnchor);
   m_ptAnchor = ptNewAnchor;
}

BOOL ZCrystalEditView::PreTranslateMessage(MSG *pMsg)
{
   if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
   {
      if (m_hAccel != NULL)
      {
         if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
            return TRUE;
      }
   }

   return CView::PreTranslateMessage(pMsg);
}

CPoint ZCrystalEditView::GetCursorPos()
{
   return m_ptCursorPos;
}

void ZCrystalEditView::SetCursorPos(const CPoint &ptCursorPos)
{
   ASSERT_VALIDTEXTPOS(ptCursorPos);
   m_ptCursorPos = ptCursorPos;
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   UpdateCaret();
}

void ZCrystalEditView::SetSelectionMargin(BOOL bSelMargin)
{
   if (m_bSelMargin != bSelMargin)
   {
      m_bSelMargin = bSelMargin;
      if (::IsWindow(m_hWnd))
      {
         m_nScreenChars = -1;
         Invalidate();
         RecalcHorzScrollBar();
      }
   }
}

void ZCrystalEditView::GetFont(LOGFONT &lf)
{
   lf = m_lfBaseFont;
}

void ZCrystalEditView::SetFont(const LOGFONT &lf)
{
   m_lfBaseFont = lf;
   m_nScreenLines = -1;
   m_nScreenChars = -1;
   m_nCharWidth = -1;
   m_nLineHeight = -1;
   if (m_pCacheBitmap != NULL)
   {
      m_pCacheBitmap->DeleteObject();
      delete m_pCacheBitmap;
      m_pCacheBitmap = NULL;
   }
   int k;
   for (k = 0; k < 4; k++)
   {
      if (m_apFonts[k] != NULL)
      {
         m_apFonts[k]->DeleteObject();
         delete m_apFonts[k];
         m_apFonts[k] = NULL;
      }
   }
   if (::IsWindow(m_hWnd))
   {
      RecalcVertScrollBar();
      RecalcHorzScrollBar();
      UpdateCaret();
      Invalidate();
   }
}

void ZCrystalEditView::OnUpdateIndicatorPosition(CCmdUI* pCmdUI)
{
   ASSERT_VALIDTEXTPOS(m_ptCursorPos);
   CString stat;
   stat.Format(_T("Ln %d, Col %d"), m_ptCursorPos.y + 1, m_ptCursorPos.x + 1);
   pCmdUI->SetText(stat);
}

void ZCrystalEditView::OnUpdateIndicatorCRLF(CCmdUI* pCmdUI)
{
   if (m_pTextBuffer != NULL)
   {
      int crlfMode = m_pTextBuffer->GetCRLFMode();
      switch (crlfMode)
      {
      case CRLF_STYLE_DOS:
         pCmdUI->SetText(_T("DOS"));
         pCmdUI->Enable(TRUE);
         break;
      case CRLF_STYLE_UNIX:
         pCmdUI->SetText(_T("UNIX"));
         pCmdUI->Enable(TRUE);
         break;
      case CRLF_STYLE_MAC:
         pCmdUI->SetText(_T("MAC"));
         pCmdUI->Enable(TRUE);
         break;
      default:
         pCmdUI->SetText(NULL);
         pCmdUI->Enable(FALSE);
      }
   }
   else
   {
      pCmdUI->SetText(NULL);
      pCmdUI->Enable(FALSE);
   }
}

void ZCrystalEditView::OnToggleBookmark(UINT nCmdID)
{
   int nBookmarkID = nCmdID - ID_EDIT_TOGGLE_BOOKMARK0;
   ASSERT(nBookmarkID >= 0 && nBookmarkID <= 9);
   if (m_pTextBuffer != NULL)
   {
      DWORD dwFlags = GetLineFlags(m_ptCursorPos.y);
      DWORD dwMask = LF_BOOKMARK(nBookmarkID);
      m_pTextBuffer->SetLineFlag(m_ptCursorPos.y, dwMask, (dwFlags & dwMask) == 0);
   }
}

void ZCrystalEditView::OnGoBookmark(UINT nCmdID)
{
   int nBookmarkID = nCmdID - ID_EDIT_GO_BOOKMARK0;
   ASSERT(nBookmarkID >= 0 && nBookmarkID <= 9);
   if (m_pTextBuffer != NULL)
   {
      int nLine = m_pTextBuffer->GetLineWithFlag(LF_BOOKMARK(nBookmarkID));
      if (nLine >= 0)
      {
         CPoint pt(0, nLine);
         ASSERT_VALIDTEXTPOS(pt);
         SetCursorPos(pt);
         SetSelection(pt, pt);
         SetAnchor(pt);
         EnsureVisible(pt);
      }
   }
}

void ZCrystalEditView::OnClearBookmarks()
{
   if (m_pTextBuffer != NULL)
   {
      for (int nBookmarkID = 0; nBookmarkID <= 9; nBookmarkID++)
      {
         int nLine = m_pTextBuffer->GetLineWithFlag(LF_BOOKMARK(nBookmarkID));
         if (nLine >= 0)
         {
            m_pTextBuffer->SetLineFlag(nLine, LF_BOOKMARK(nBookmarkID), FALSE);
         }
      }

   }
}

void ZCrystalEditView::ShowCursor()
{
   m_bCursorHidden = FALSE;
   UpdateCaret();
}

void ZCrystalEditView::HideCursor()
{
   m_bCursorHidden = TRUE;
   UpdateCaret();
}

HGLOBAL ZCrystalEditView::PrepareDragData()
{
   PrepareSelBounds();
   if (m_ptDrawSelStart == m_ptDrawSelEnd)
      return NULL;

   CString text;
   GetText(m_ptDrawSelStart, m_ptDrawSelEnd, text);
   HGLOBAL hData = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, lstrlen(text) + 1);
   if (hData == NULL)
      return NULL;

   LPSTR pszData = (LPSTR) ::GlobalLock(hData);
   USES_CONVERSION;
   strcpy_s(pszData, lstrlen(text) + 1, T2A(text.GetBuffer(0)));
   text.ReleaseBuffer();
   ::GlobalUnlock(hData);

   m_ptDraggedTextBegin = m_ptDrawSelStart;
   m_ptDraggedTextEnd = m_ptDrawSelEnd;
   return hData;
}

static int FindStringHelper(LPCTSTR pszFindWhere, LPCTSTR pszFindWhat, BOOL bWholeWord)
{
   ASSERT(pszFindWhere != NULL);
   ASSERT(pszFindWhat != NULL);
   int nCur = 0;
   int nLength = lstrlen(pszFindWhat);
   for (;;)
   {
#ifdef _UNICODE
      LPCTSTR pszPos = wcsstr(pszFindWhere, pszFindWhat);
#else
      LPCTSTR pszPos = strstr(pszFindWhere, pszFindWhat);
#endif
      if (pszPos == NULL)
         return -1;
      if (! bWholeWord)
         return nCur + (pszPos - pszFindWhere);
      if (pszPos > pszFindWhere && (isalnum(pszPos[-1]) || pszPos[-1] == _T('_')))
      {
         nCur += (pszPos - pszFindWhere);
         pszFindWhere = pszPos + 1;
         continue;
      }
      if (isalnum(pszPos[nLength]) || pszPos[nLength] == _T('_'))
      {
         nCur += (pszPos - pszFindWhere + 1);
         pszFindWhere = pszPos + 1;
         continue;
      }
      return nCur + (pszPos - pszFindWhere);
   }
   ASSERT(FALSE);    // Unreachable
   return -1;
}

BOOL ZCrystalEditView::HighlightText(const CPoint &ptStartPos, int nLength)
{
   ASSERT_VALIDTEXTPOS(ptStartPos);
   m_ptCursorPos = ptStartPos;
   m_ptCursorPos.x += nLength;
   ASSERT_VALIDTEXTPOS(m_ptCursorPos);    // Probably 'nLength' is bigger than expected...
   m_ptAnchor = m_ptCursorPos;
   SetSelection(ptStartPos, m_ptCursorPos);
   UpdateCaret();
   EnsureVisible(m_ptCursorPos);
   return TRUE;
}

BOOL ZCrystalEditView::FindText(LPCTSTR pszText, const CPoint &ptStartPos, DWORD dwFlags,
                                BOOL bWrapSearch, CPoint *pptFoundPos)
{
   int nLineCount = GetLineCount();
   return FindTextInBlock(pszText, ptStartPos, CPoint(0, 0),
                          CPoint(GetLineLength(nLineCount - 1), nLineCount - 1),
                          dwFlags, bWrapSearch, pptFoundPos);
}

BOOL ZCrystalEditView::FindTextInBlock(LPCTSTR pszText, const CPoint &ptStartPosition,
                                       const CPoint &ptBlockBegin, const CPoint &ptBlockEnd,
                                       DWORD dwFlags, BOOL bWrapSearch, CPoint *pptFoundPos)
{
   CPoint ptCurrentPos = ptStartPosition;

   ASSERT(pszText != NULL && lstrlen(pszText) > 0);
   ASSERT_VALIDTEXTPOS(ptCurrentPos);
   ASSERT_VALIDTEXTPOS(ptBlockBegin);
   ASSERT_VALIDTEXTPOS(ptBlockEnd);
   ASSERT(ptBlockBegin.y < ptBlockEnd.y || ptBlockBegin.y == ptBlockEnd.y &&
      ptBlockBegin.x <= ptBlockEnd.x);
   if (ptBlockBegin == ptBlockEnd)
      return FALSE;

   if (ptCurrentPos.y < ptBlockBegin.y || ptCurrentPos.y == ptBlockBegin.y &&
      ptCurrentPos.x < ptBlockBegin.x)
      ptCurrentPos = ptBlockBegin;

   CString what = pszText;
   if ((dwFlags & FIND_MATCH_CASE) == 0)
      what.MakeUpper();

   if (dwFlags & FIND_DIRECTION_UP)
   {
      // Let's check if we deal with whole text.
      // At this point, we cannot search *up* in selection
      ASSERT(ptBlockBegin.x == 0 && ptBlockBegin.y == 0);
      ASSERT(ptBlockEnd.x == GetLineLength(GetLineCount() - 1) && ptBlockEnd.y == GetLineCount() - 1);

      // Proceed as if we have whole text search.
      for (;;)
      {
         while (ptCurrentPos.y >= 0)
         {
            int nLineLength = GetLineLength(ptCurrentPos.y);
            nLineLength -= ptCurrentPos.x;
            if (nLineLength <= 0)
            {
               ptCurrentPos.x = 0;
               ptCurrentPos.y--;
               continue;
            }

            LPCTSTR pszChars = GetLineChars(ptCurrentPos.y);
            pszChars += ptCurrentPos.x;

            CString line;
            lstrcpyn(line.GetBuffer(nLineLength + 1), pszChars, nLineLength + 1);
            line.ReleaseBuffer();
            if ((dwFlags & FIND_MATCH_CASE) == 0)
               line.MakeUpper();

            int nPos = ::FindStringHelper(line, what, (dwFlags & FIND_WHOLE_WORD) != 0);
            if (nPos >= 0)    // Found text!
            {
               ptCurrentPos.x += nPos;
               *pptFoundPos = ptCurrentPos;
               return TRUE;
            }

            ptCurrentPos.x = 0;
            ptCurrentPos.y--;
         }

         // Beginning of text reached
         if (! bWrapSearch)
            return FALSE;

         // Start again from the end of text
         bWrapSearch = FALSE;
         ptCurrentPos = CPoint(0, GetLineCount() - 1);
      }
   }
   else
   {
      for (;;)
      {
         while (ptCurrentPos.y <= ptBlockEnd.y)
         {
            int nLineLength = GetLineLength(ptCurrentPos.y);
            nLineLength -= ptCurrentPos.x;
            if (nLineLength <= 0)
            {
               ptCurrentPos.x = 0;
               ptCurrentPos.y++;
               continue;
            }

            LPCTSTR pszChars = GetLineChars(ptCurrentPos.y);
            pszChars += ptCurrentPos.x;

            // Prepare necessary part of line
            CString line;
            lstrcpyn(line.GetBuffer(nLineLength + 1), pszChars, nLineLength + 1);
            line.ReleaseBuffer();
            if ((dwFlags & FIND_MATCH_CASE) == 0)
               line.MakeUpper();

            // Perform search in the line
            int nPos = ::FindStringHelper(line, what, (dwFlags & FIND_WHOLE_WORD) != 0);
            if (nPos >= 0)
            {
               ptCurrentPos.x += nPos;
               // Check of the text found is outside the block.
               if (ptCurrentPos.y == ptBlockEnd.y && ptCurrentPos.x >= ptBlockEnd.x)
                  break;

               *pptFoundPos = ptCurrentPos;
               return TRUE;
            }

            // Go further, text was not found
            ptCurrentPos.x = 0;
            ptCurrentPos.y++;
         }

         // End of text reached
         if (! bWrapSearch)
            return FALSE;

         // Start from the beginning
         bWrapSearch = FALSE;
         ptCurrentPos = ptBlockBegin;
      }
   }

   ASSERT(FALSE);    // Unreachable
   return FALSE;
}

void ZCrystalEditView::OnEditFind()
{
   CWinApp *pApp = AfxGetApp();
   ASSERT(pApp != NULL);

   ZFindTextDlg dlg(this);
   if (m_bLastSearch)
   {
      // Get the latest search parameters
      dlg.m_bMatchCase = (m_dwLastSearchFlags & FIND_MATCH_CASE) != 0;
      dlg.m_bWholeWord = (m_dwLastSearchFlags & FIND_WHOLE_WORD) != 0;
      dlg.m_nDirection = (m_dwLastSearchFlags & FIND_DIRECTION_UP) != 0 ? 0 : 1;
      if (m_pszLastFindWhat != NULL)
         dlg.m_sText = m_pszLastFindWhat;
   }
   else
   {
      // Take search parameters from registry
      dlg.m_bMatchCase = pApp->GetProfileInt(REG_FIND_SUBKEY, REG_MATCH_CASE, FALSE);
      dlg.m_bWholeWord = pApp->GetProfileInt(REG_FIND_SUBKEY, REG_WHOLE_WORD, FALSE);
      dlg.m_nDirection = 1;      // Search down
      dlg.m_sText = pApp->GetProfileString(REG_FIND_SUBKEY, REG_FIND_WHAT, _T(""));
   }

   // Take the current selection, if any
   if (IsSelection())
   {
      CPoint ptSelStart, ptSelEnd;
      GetSelection(ptSelStart, ptSelEnd);    if (ptSelStart.y == ptSelEnd.y)
      {
         LPCTSTR pszChars = GetLineChars(ptSelStart.y);
         int nChars = ptSelEnd.x - ptSelStart.x;
         lstrcpyn(dlg.m_sText.GetBuffer(nChars + 1), pszChars + ptSelStart.x, nChars + 1);
         dlg.m_sText.ReleaseBuffer();
      }
   }

   // Execute Find dialog
   dlg.m_ptCurrentPos = m_ptCursorPos;    // Search from cursor position
   m_bShowInactiveSelection = TRUE;
   dlg.DoModal();
   m_bShowInactiveSelection = FALSE;

   // Save search parameters for 'F3' command
   m_bLastSearch = TRUE;
   if (m_pszLastFindWhat != NULL)
      free(m_pszLastFindWhat);
#ifdef _UNICODE
   m_pszLastFindWhat = _wcsdup(dlg.m_sText);
#else
   m_pszLastFindWhat = _strdup(dlg.m_sText);
#endif

   m_dwLastSearchFlags = 0;
   if (dlg.m_bMatchCase)
      m_dwLastSearchFlags |= FIND_MATCH_CASE;
   if (dlg.m_bWholeWord)
      m_dwLastSearchFlags |= FIND_WHOLE_WORD;
   if (dlg.m_nDirection == 0)
      m_dwLastSearchFlags |= FIND_DIRECTION_UP;

   // Save search parameters to registry
   pApp->WriteProfileInt(REG_FIND_SUBKEY, REG_MATCH_CASE, dlg.m_bMatchCase);
   pApp->WriteProfileInt(REG_FIND_SUBKEY, REG_WHOLE_WORD, dlg.m_bWholeWord);
   pApp->WriteProfileString(REG_FIND_SUBKEY, REG_FIND_WHAT, dlg.m_sText);
}

void ZCrystalEditView::OnEditRepeat()
{
   if (m_bLastSearch)
   {
      CPoint ptFoundPos;
      if (! FindText(m_pszLastFindWhat, m_ptCursorPos, m_dwLastSearchFlags, TRUE, &ptFoundPos))
      {
         CString prompt;
         prompt.Format(IDS_EDIT_TEXT_NOT_FOUND, m_pszLastFindWhat);
         AfxMessageBox(prompt);
         return;
      }
      HighlightText(ptFoundPos, lstrlen(m_pszLastFindWhat));
      m_bMultipleSearch = TRUE;       // More search
   }
}

void ZCrystalEditView::OnUpdateEditRepeat(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_bLastSearch);
}

void ZCrystalEditView::OnEditFindPrevious()
{
   DWORD dwSaveSearchFlags = m_dwLastSearchFlags;
   if ((m_dwLastSearchFlags & FIND_DIRECTION_UP) != 0)
      m_dwLastSearchFlags &= ~FIND_DIRECTION_UP;
   else
      m_dwLastSearchFlags |= FIND_DIRECTION_UP;
   OnEditRepeat();
   m_dwLastSearchFlags = dwSaveSearchFlags;
}

void ZCrystalEditView::OnUpdateEditFindPrevious(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_bLastSearch);
}

void ZCrystalEditView::OnFilePageSetup()
{
   CWinApp *pApp = AfxGetApp();
   ASSERT(pApp != NULL);

   CPageSetupDialog dlg;
   dlg.m_psd.Flags &= ~PSD_INTHOUSANDTHSOFINCHES;
   dlg.m_psd.Flags |= PSD_INHUNDREDTHSOFMILLIMETERS | PSD_DISABLEORIENTATION | PSD_DISABLEPAPER;
   dlg.m_psd.rtMargin.left = pApp->GetProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_LEFT, DEFAULT_PRINT_MARGIN);
   dlg.m_psd.rtMargin.right = pApp->GetProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_RIGHT, DEFAULT_PRINT_MARGIN);
   dlg.m_psd.rtMargin.top = pApp->GetProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_TOP, DEFAULT_PRINT_MARGIN);
   dlg.m_psd.rtMargin.bottom = pApp->GetProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_BOTTOM, DEFAULT_PRINT_MARGIN);
   if (dlg.DoModal() == IDOK)
   {
      pApp->WriteProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_LEFT, dlg.m_psd.rtMargin.left);
      pApp->WriteProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_RIGHT, dlg.m_psd.rtMargin.right);
      pApp->WriteProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_TOP, dlg.m_psd.rtMargin.top);
      pApp->WriteProfileInt(REG_PAGE_SUBKEY, REG_MARGIN_BOTTOM, dlg.m_psd.rtMargin.bottom);
   }
}

void ZCrystalEditView::OnToggleBookmark()
{
   if (m_pTextBuffer != NULL)
   {
      DWORD dwFlags = GetLineFlags(m_ptCursorPos.y);
      DWORD dwMask  = LF_BOOKMARKS;
      m_pTextBuffer->SetLineFlag(m_ptCursorPos.y, dwMask, (dwFlags & dwMask) == 0, FALSE);
   }
   int nLine = m_pTextBuffer->GetLineWithFlag(LF_BOOKMARKS);
   if (nLine >= 0)
      m_bBookmarkExist = TRUE;
   else
      m_bBookmarkExist = FALSE;
}

void ZCrystalEditView::OnNextBookmark()
{
   if (m_pTextBuffer != NULL)
   {
      int nLine = m_pTextBuffer->FindNextBookmarkLine(m_ptCursorPos.y);
      if (nLine >= 0)
      {
         CPoint pt(0, nLine);
         ASSERT_VALIDTEXTPOS(pt);
         SetCursorPos(pt);
         SetSelection(pt, pt);
         SetAnchor(pt);
         EnsureVisible(pt);
      }
   }
}

void ZCrystalEditView::OnPrevBookmark()
{
   if (m_pTextBuffer != NULL)
   {
      int nLine = m_pTextBuffer->FindPrevBookmarkLine(m_ptCursorPos.y);
      if (nLine >= 0)
      {
         CPoint pt(0, nLine);
         ASSERT_VALIDTEXTPOS(pt);
         SetCursorPos(pt);
         SetSelection(pt, pt);
         SetAnchor(pt);
         EnsureVisible(pt);
      }
   }
}

void ZCrystalEditView::OnClearAllBookmarks()
{
   if (m_pTextBuffer != NULL)
   {
      int nLineCount = GetLineCount();
      int k;
      for (k = 0; k < nLineCount; k++)
      {
         if (m_pTextBuffer->GetLineFlags(k) & LF_BOOKMARKS)
            m_pTextBuffer->SetLineFlag(k, LF_BOOKMARKS, FALSE);
      }
      m_bBookmarkExist = FALSE;
   }
}

void ZCrystalEditView::OnUpdateNextBookmark(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_bBookmarkExist);
}

void ZCrystalEditView::OnUpdatePrevBookmark(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_bBookmarkExist);
}

void ZCrystalEditView::OnUpdateClearAllBookmarks(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_bBookmarkExist);
}

BOOL ZCrystalEditView::GetViewTabs()
{
   return m_bViewTabs;
}

void ZCrystalEditView::SetViewTabs(BOOL bViewTabs)
{
   if (bViewTabs != m_bViewTabs)
   {
      m_bViewTabs = bViewTabs;
      if (::IsWindow(m_hWnd))
         Invalidate();
   }
}

BOOL ZCrystalEditView::GetSelectionMargin()
{
   return m_bSelMargin;
}

int ZCrystalEditView::GetMarginWidth()
{
   return m_bSelMargin ? 20 : 1;
}

BOOL ZCrystalEditView::GetSmoothScroll() const
{
   return m_bSmoothScroll;
}

void ZCrystalEditView::SetSmoothScroll(BOOL bSmoothScroll)
{
   m_bSmoothScroll = bSmoothScroll;
}

// [JRT]
BOOL ZCrystalEditView::GetDisableDragAndDrop() const
{
   return m_bDisabledDragAndDrop;
}

// [JRT]
void ZCrystalEditView::SetDisableDragAndDrop(BOOL bDDAD)
{
   m_bDisabledDragAndDrop = bDDAD;
}

void ZCrystalEditView::MoveLeft(BOOL bSelect)
{
   PrepareSelBounds();
   if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
   {
      m_ptCursorPos = m_ptDrawSelStart;
   }
   else
   {
      if (m_ptCursorPos.x == 0)
      {
         if (m_ptCursorPos.y > 0)
         {
            m_ptCursorPos.y--;
            m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
         }
      }
      else
         m_ptCursorPos.x--;
   }
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveRight(BOOL bSelect)
{
   PrepareSelBounds();
   if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
   {
      m_ptCursorPos = m_ptDrawSelEnd;
   }
   else
   {
      if (m_ptCursorPos.x == GetLineLength(m_ptCursorPos.y))
      {
         if (m_ptCursorPos.y < GetLineCount() - 1)
         {
            m_ptCursorPos.y++;
            m_ptCursorPos.x = 0;
         }
      }
      else
         m_ptCursorPos.x++;
   }
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveWordLeft(BOOL bSelect)
{
   PrepareSelBounds();
   if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
   {
      MoveLeft(bSelect);
      return;
   }

   if (m_ptCursorPos.x == 0)
   {
      if (m_ptCursorPos.y == 0)
         return;
      m_ptCursorPos.y--;
      m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
   }

   LPCTSTR pszChars = GetLineChars(m_ptCursorPos.y);
   int nPos = m_ptCursorPos.x;
   while (nPos > 0 && isspace(pszChars[nPos - 1]))
      nPos--;

   if (nPos > 0)
   {
      nPos--;
      if (isalnum(pszChars[nPos]) || pszChars[nPos] == _T('_'))
      {
         while (nPos > 0 && (isalnum(pszChars[nPos - 1]) || pszChars[nPos - 1] == _T('_')))
            nPos--;
      }
      else
      {
         while (nPos > 0 && ! isalnum(pszChars[nPos - 1]) && pszChars[nPos - 1] != _T('_') && ! isspace(pszChars[nPos - 1]))
            nPos--;
      }
   }

   m_ptCursorPos.x = nPos;
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveWordRight(BOOL bSelect)
{
   PrepareSelBounds();
   if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
   {
      MoveRight(bSelect);
      return;
   }

   if (m_ptCursorPos.x == GetLineLength(m_ptCursorPos.y))
   {
      if (m_ptCursorPos.y == GetLineCount() - 1)
         return;
      m_ptCursorPos.y++;
      m_ptCursorPos.x = 0;
   }

   int nLength = GetLineLength(m_ptCursorPos.y);
   if (m_ptCursorPos.x == nLength)
   {
      MoveRight(bSelect);
      return;
   }

   LPCTSTR pszChars = GetLineChars(m_ptCursorPos.y);
   int nPos = m_ptCursorPos.x;
   if (isalnum(pszChars[nPos]) || pszChars[nPos] == _T('_'))
   {
      while (nPos < nLength && isalnum(pszChars[nPos]) || pszChars[nPos] == _T('_'))
         nPos++;
   }
   else
   {
      while (nPos < nLength && ! isalnum(pszChars[nPos]) && pszChars[nPos] != _T('_') && ! isspace(pszChars[nPos]))
         nPos++;
   }

   while (nPos < nLength && isspace(pszChars[nPos]))
      nPos++;

   m_ptCursorPos.x = nPos;
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveUp(BOOL bSelect)
{
   PrepareSelBounds();
   if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
      m_ptCursorPos = m_ptDrawSelStart;

   if (m_ptCursorPos.y > 0)
   {
      if (m_nIdealCharPos == -1)
         m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
      m_ptCursorPos.y--;
      m_ptCursorPos.x = ApproxActualOffset(m_ptCursorPos.y, m_nIdealCharPos);
      if (m_ptCursorPos.x > GetLineLength(m_ptCursorPos.y))
         m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
   }
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveDown(BOOL bSelect)
{
   PrepareSelBounds();
   if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
      m_ptCursorPos = m_ptDrawSelEnd;

   if (m_ptCursorPos.y < GetLineCount() - 1)
   {
      if (m_nIdealCharPos == -1)
         m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
      m_ptCursorPos.y++;
      m_ptCursorPos.x = ApproxActualOffset(m_ptCursorPos.y, m_nIdealCharPos);
      if (m_ptCursorPos.x > GetLineLength(m_ptCursorPos.y))
         m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
   }
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveHome(BOOL bSelect)
{
   int nLength = GetLineLength(m_ptCursorPos.y);
   LPCTSTR pszChars = GetLineChars(m_ptCursorPos.y);
   int nHomePos = 0;
   while (nHomePos < nLength && isspace(pszChars[nHomePos]))
      nHomePos++;
   if (nHomePos == nLength || m_ptCursorPos.x == nHomePos)
      m_ptCursorPos.x = 0;
   else
      m_ptCursorPos.x = nHomePos;
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveEnd(BOOL bSelect)
{
   m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MovePgUp(BOOL bSelect)
{
   int nNewTopLine = m_nTopLine - GetScreenLines() + 1;
   if (nNewTopLine < 0)
      nNewTopLine = 0;
   if (m_nTopLine != nNewTopLine)
   {
      ScrollToLine(nNewTopLine);
      UpdateSiblingScrollPos(TRUE);
   }

   m_ptCursorPos.y -= GetScreenLines() - 1;
   if (m_ptCursorPos.y < 0)
      m_ptCursorPos.y = 0;
   if (m_ptCursorPos.x > GetLineLength(m_ptCursorPos.y))
      m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos); //todo: no vertical scroll
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MovePgDn(BOOL bSelect)
{
   int nNewTopLine = m_nTopLine + GetScreenLines() - 1;
   if (nNewTopLine >= GetLineCount())
      nNewTopLine = GetLineCount() - 1;
   if (m_nTopLine != nNewTopLine)
   {
      ScrollToLine(nNewTopLine);
      UpdateSiblingScrollPos(TRUE);
   }

   m_ptCursorPos.y += GetScreenLines() - 1;
   if (m_ptCursorPos.y >= GetLineCount())
      m_ptCursorPos.y = GetLineCount() - 1;
   if (m_ptCursorPos.x > GetLineLength(m_ptCursorPos.y))
      m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos); //todo: no vertical scroll
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveCtrlHome(BOOL bSelect)
{
   m_ptCursorPos.x = 0;
   m_ptCursorPos.y = 0;
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::MoveCtrlEnd(BOOL bSelect)
{
   m_ptCursorPos.y = GetLineCount() - 1;
   m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
   m_nIdealCharPos = CalculateActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
   EnsureVisible(m_ptCursorPos);
   UpdateCaret();
   if (! bSelect)
      m_ptAnchor = m_ptCursorPos;
   SetSelection(m_ptAnchor, m_ptCursorPos);
}

void ZCrystalEditView::ScrollUp()
{
   if (m_nTopLine > 0)
   {
      ScrollToLine(m_nTopLine - 1);
      UpdateSiblingScrollPos(TRUE);
   }
}

void ZCrystalEditView::ScrollDown()
{
   if (m_nTopLine < GetLineCount() - 1)
   {
      ScrollToLine(m_nTopLine + 1);
      UpdateSiblingScrollPos(TRUE);
   }
}

void ZCrystalEditView::ScrollLeft()
{
   if (m_nOffsetChar > 0)
   {
      ScrollToChar(m_nOffsetChar - 1);
      UpdateCaret();
   }
}

void ZCrystalEditView::ScrollRight()
{
   if (m_nOffsetChar < GetMaxLineLength() - 1)
   {
      ScrollToChar(m_nOffsetChar + 1);
      UpdateCaret();
   }
}

CPoint ZCrystalEditView::WordToRight(CPoint pt)
{
   ASSERT_VALIDTEXTPOS(pt);
   int nLength = GetLineLength(pt.y);
   LPCTSTR pszChars = GetLineChars(pt.y);
   while (pt.x < nLength)
   {
      if (! isalnum(pszChars[pt.x]) && pszChars[pt.x] != _T('_'))
         break;
      pt.x++;
   }
   ASSERT_VALIDTEXTPOS(pt);
   return pt;
}

CPoint ZCrystalEditView::WordToLeft(CPoint pt)
{
   ASSERT_VALIDTEXTPOS(pt);
   LPCTSTR pszChars = GetLineChars(pt.y);
   while (pt.x > 0)
   {
      if (! isalnum(pszChars[pt.x - 1]) && pszChars[pt.x - 1] != _T('_'))
         break;
      pt.x--;
   }
   ASSERT_VALIDTEXTPOS(pt);
   return pt;
}

void ZCrystalEditView::SelectAllLines()
{
   int nLineCount = GetLineCount();
   m_ptCursorPos.x = GetLineLength(nLineCount - 1);
   m_ptCursorPos.y = nLineCount - 1;
   SetSelection(CPoint(0, 0), m_ptCursorPos);
   UpdateCaret();
}

void ZCrystalEditView::OnLButtonDown(UINT uFlags, CPoint point)
{
   CView::OnLButtonDown(uFlags, point);

   BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;
   BOOL bControl = GetKeyState(VK_CONTROL) & 0x8000;
   TRACE(_T("OnLButtonDown point.x = %d   MarginWidth = %d - %d\n"), point.x, GetMarginWidth());
   if (point.x < GetMarginWidth())
   {
      AdjustTextPoint(point);
      if (bControl)
      {
         SelectAllLines();
      }
      else
      {
         m_ptCursorPos = ClientToText(point);
         m_ptCursorPos.x = 0;          // Force beginning of the line
         if (! bShift)
            m_ptAnchor = m_ptCursorPos;

         CPoint ptStart, ptEnd;
         ptStart = m_ptAnchor;
         if (ptStart.y == GetLineCount() - 1)
            ptStart.x = GetLineLength(ptStart.y);
         else
         {
            ptStart.y++;
            ptStart.x = 0;
         }

         ptEnd = m_ptCursorPos;
         ptEnd.x = 0;

         m_ptCursorPos = ptEnd;
         UpdateCaret();
         EnsureVisible(m_ptCursorPos);
         SetSelection(ptStart, ptEnd);

         SetCapture();
         m_nDragSelTimer = SetTimer(CRYSTAL_TIMER_DRAGSEL, 100, NULL);
         ASSERT(m_nDragSelTimer != 0);
         m_bWordSelection = FALSE;
         m_bLineSelection = TRUE;
         m_bDragSelection = TRUE;
         TRACE(_T("OnLButtonDown setting m_bDragSelection - %d\n"), m_bDragSelection);
      }
   }
   else
   {
      CPoint ptText = ClientToText(point);
      PrepareSelBounds();
      TRACE(_T("OnLButtonDown checking DragAndDrop Disabled: %d\n"), m_bDisabledDragAndDrop);
      // [JRT]:   Support For Disabling Drag and Drop...
      if ((IsInsideSelBlock(ptText)) && (!m_bDisabledDragAndDrop))  // If Inside Selection Area ... and D&D Not Disabled
      {
         m_bPreparingToDrag = TRUE;
         TRACE(_T("OnLButtonDown setting m_bPreparingToDrag: %d   for hWnd: %d\n"), m_bPreparingToDrag, m_hWnd);
      }
      else
      {
         AdjustTextPoint(point);
         m_ptCursorPos = ClientToText(point);
         if (! bShift)
            m_ptAnchor = m_ptCursorPos;

         CPoint ptStart, ptEnd;
         if (bControl)
         {
            if (m_ptCursorPos.y < m_ptAnchor.y ||
               m_ptCursorPos.y == m_ptAnchor.y && m_ptCursorPos.x < m_ptAnchor.x)
            {
               ptStart = WordToLeft(m_ptCursorPos);
               ptEnd = WordToRight(m_ptAnchor);
            }
            else
            {
               ptStart = WordToLeft(m_ptAnchor);
               ptEnd = WordToRight(m_ptCursorPos);
            }
         }
         else
         {
            ptStart = m_ptAnchor;
            ptEnd = m_ptCursorPos;
         }

         m_ptCursorPos = ptEnd;
         UpdateCaret();
         EnsureVisible(m_ptCursorPos);
         SetSelection(ptStart, ptEnd);

         SetCapture();
         m_nDragSelTimer = SetTimer(CRYSTAL_TIMER_DRAGSEL, 100, NULL);
         ASSERT(m_nDragSelTimer != 0);
         m_bWordSelection = bControl;
         m_bLineSelection = FALSE;
         m_bDragSelection = TRUE;
      }
   }

   ASSERT_VALIDTEXTPOS(m_ptCursorPos);
}

void ZCrystalEditView::OnMouseMove(UINT uFlags, CPoint point)
{
   CView::OnMouseMove(uFlags, point);

// TRACE(_T("OnMouseMove m_bDragSelection - %d\n"), m_bDragSelection);

   if (m_bDragSelection)
   {
      BOOL bOnMargin = point.x < GetMarginWidth();

      AdjustTextPoint(point);
      CPoint ptNewCursorPos = ClientToText(point);

      CPoint ptStart, ptEnd;
      if (m_bLineSelection)
      {
         if (bOnMargin)
         {
            if (ptNewCursorPos.y < m_ptAnchor.y || (ptNewCursorPos.y == m_ptAnchor.y && ptNewCursorPos.x < m_ptAnchor.x))
            {
               ptEnd = m_ptAnchor;
               if (ptEnd.y == GetLineCount() - 1)
               {
                  ptEnd.x = GetLineLength(ptEnd.y);
               }
               else
               {
                  ptEnd.y++;
                  ptEnd.x = 0;
               }
               ptNewCursorPos.x = 0;
               m_ptCursorPos = ptNewCursorPos;
            }
            else
            {
               ptEnd = m_ptAnchor;
               ptEnd.x = 0;
               m_ptCursorPos = ptNewCursorPos;
               if (ptNewCursorPos.y == GetLineCount() - 1)
               {
                  ptNewCursorPos.x = GetLineLength(ptNewCursorPos.y);
               }
               else
               {
                  ptNewCursorPos.y++;
                  ptNewCursorPos.x = 0;
               }
               m_ptCursorPos.x = 0;
            }
            UpdateCaret();
            SetSelection(ptNewCursorPos, ptEnd);
            return;
         }

         // Moving to normal selection mode
         ::SetCursor(::LoadCursor(NULL, IDC_IBEAM));
         m_bLineSelection = m_bWordSelection = FALSE;
      }

      if (m_bWordSelection)
      {
         if (ptNewCursorPos.y < m_ptAnchor.y ||
            ptNewCursorPos.y == m_ptAnchor.y && ptNewCursorPos.x < m_ptAnchor.x)
         {
            ptStart = WordToLeft(ptNewCursorPos);
            ptEnd = WordToRight(m_ptAnchor);
         }
         else
         {
            ptStart = WordToLeft(m_ptAnchor);
            ptEnd = WordToRight(ptNewCursorPos);
         }
      }
      else
      {
         ptStart = m_ptAnchor;
         ptEnd = ptNewCursorPos;
      }

      m_ptCursorPos = ptEnd;
      UpdateCaret();
      SetSelection(ptStart, ptEnd);
   }

   if (m_bPreparingToDrag)
   {
      TRACE(_T("OnMouseMove m_bPreparingToDrag - %d   for hWnd: %d\n"), m_bPreparingToDrag, m_hWnd);
      m_bPreparingToDrag = FALSE;
      HGLOBAL hData = PrepareDragData();
      if (hData != NULL)
      {
         if (m_pTextBuffer != NULL)
            m_pTextBuffer->BeginUndoGroup();

         COleDataSource ds;
         ds.CacheGlobalData(CF_TEXT, hData);
         m_bDraggingText = TRUE;
         TRACE(_T("OnMouseMove m_bDraggingText1 - %d\n"), m_bDraggingText);
         DROPEFFECT de = ds.DoDragDrop(GetDropEffect());
         if (de != DROPEFFECT_NONE)
            OnDropSource(de);
         m_bDraggingText = FALSE;
         TRACE(_T("OnMouseMove m_bDraggingText2 - %d\n"), m_bDraggingText);

         if (m_pTextBuffer != NULL)
            m_pTextBuffer->FlushUndoGroup(this);
      }
   }

   ASSERT_VALIDTEXTPOS(m_ptCursorPos);
}

void ZCrystalEditView::OnLButtonUp(UINT uFlags, CPoint point)
{
   CView::OnLButtonUp(uFlags, point);
   TRACE(_T("OnLButtonUp m_bDragSelection - %d\n"), m_bDragSelection);
   if (m_bDragSelection)
   {
      AdjustTextPoint(point);
      CPoint ptNewCursorPos = ClientToText(point);

      CPoint ptStart, ptEnd;
      if (m_bLineSelection)
      {
         CPoint ptEnd;
         if (ptNewCursorPos.y < m_ptAnchor.y ||
            ptNewCursorPos.y == m_ptAnchor.y && ptNewCursorPos.x < m_ptAnchor.x)
         {
            ptEnd = m_ptAnchor;
            if (ptEnd.y == GetLineCount() - 1)
            {
               ptEnd.x = GetLineLength(ptEnd.y);
            }
            else
            {
               ptEnd.y++;
               ptEnd.x = 0;
            }
            ptNewCursorPos.x = 0;
            m_ptCursorPos = ptNewCursorPos;
         }
         else
         {
            ptEnd = m_ptAnchor;
            ptEnd.x = 0;
            if (ptNewCursorPos.y == GetLineCount() - 1)
            {
               ptNewCursorPos.x = GetLineLength(ptNewCursorPos.y);
            }
            else
            {
               ptNewCursorPos.y++;
               ptNewCursorPos.x = 0;
            }
            m_ptCursorPos = ptNewCursorPos;
         }
         EnsureVisible(m_ptCursorPos);
         UpdateCaret();
         SetSelection(ptNewCursorPos, ptEnd);
      }
      else
      {
         if (m_bWordSelection)
         {
            if (ptNewCursorPos.y < m_ptAnchor.y ||
               ptNewCursorPos.y == m_ptAnchor.y && ptNewCursorPos.x < m_ptAnchor.x)
            {
               ptStart = WordToLeft(ptNewCursorPos);
               ptEnd = WordToRight(m_ptAnchor);
            }
            else
            {
               ptStart = WordToLeft(m_ptAnchor);
               ptEnd = WordToRight(ptNewCursorPos);
            }
         }
         else
         {
            ptStart = m_ptAnchor;
            ptEnd = m_ptCursorPos;
         }

         m_ptCursorPos = ptEnd;
         EnsureVisible(m_ptCursorPos);
         UpdateCaret();
         SetSelection(ptStart, ptEnd);
      }

      ReleaseCapture();
      KillTimer(m_nDragSelTimer);
      m_bDragSelection = FALSE;
   }

   if (m_bPreparingToDrag)
   {
      m_bPreparingToDrag = FALSE;

      AdjustTextPoint(point);
      m_ptCursorPos = ClientToText(point);
      EnsureVisible(m_ptCursorPos);
      UpdateCaret();
      SetSelection(m_ptCursorPos, m_ptCursorPos);
   }

   ASSERT_VALIDTEXTPOS(m_ptCursorPos);
}

void ZCrystalEditView::OnTimer(UINT nIDEvent)
{
   CView::OnTimer(nIDEvent);
   TRACE(_T("OnTimer m_bDragSelection - %d\n"), m_bDragSelection);
   if (nIDEvent == CRYSTAL_TIMER_DRAGSEL)
   {
      ASSERT(m_bDragSelection);
      CPoint pt;
      ::GetCursorPos(&pt);
      ScreenToClient(&pt);
      CRect rcClient;
      GetClientRect(&rcClient);

      BOOL bChanged = FALSE;

      // Scroll vertically, if necessary
      int nNewTopLine = m_nTopLine;
      int nLineCount = GetLineCount();
      if (pt.y < rcClient.top)
      {
         nNewTopLine--;
         if (pt.y < rcClient.top - GetLineHeight())
            nNewTopLine -= 2;
      }
      else
      if (pt.y >= rcClient.bottom)
      {
         nNewTopLine++;
         if (pt.y >= rcClient.bottom + GetLineHeight())
            nNewTopLine += 2;
      }

      if (nNewTopLine < 0)
         nNewTopLine = 0;
      if (nNewTopLine >= nLineCount)
         nNewTopLine = nLineCount - 1;

      if (m_nTopLine != nNewTopLine)
      {
         ScrollToLine(nNewTopLine);
         UpdateSiblingScrollPos(TRUE);
         bChanged = TRUE;
      }

      // Scroll horizontally, if necessary
      int nNewOffsetChar = m_nOffsetChar;
      int nMaxLineLength = GetMaxLineLength();
      if (pt.x < rcClient.left)
         nNewOffsetChar--;
      else
      if (pt.x >= rcClient.right)
         nNewOffsetChar++;

      if (nNewOffsetChar >= nMaxLineLength)
         nNewOffsetChar = nMaxLineLength - 1;
      if (nNewOffsetChar < 0)
         nNewOffsetChar = 0;

      if (m_nOffsetChar != nNewOffsetChar)
      {
         ScrollToChar(nNewOffsetChar);
         UpdateCaret();
         UpdateSiblingScrollPos(FALSE);
         bChanged = TRUE;
      }

      // Fix changes
      if (bChanged)
      {
         AdjustTextPoint(pt);
         CPoint ptNewCursorPos = ClientToText(pt);
         if (ptNewCursorPos != m_ptCursorPos)
         {
            m_ptCursorPos = ptNewCursorPos;
            UpdateCaret();
         }
         SetSelection(m_ptAnchor, m_ptCursorPos);
      }
   }
}

void ZCrystalEditView::OnLButtonDblClk(UINT uFlags, CPoint point)
{
   CView::OnLButtonDblClk(uFlags, point);
   TRACE(_T("OnLButtonDblClk m_bDragSelection - %d\n"), m_bDragSelection);
   if (! m_bDragSelection)
   {
      AdjustTextPoint(point);

      m_ptCursorPos = ClientToText(point);
      m_ptAnchor = m_ptCursorPos;

      CPoint ptStart, ptEnd;
      if (m_ptCursorPos.y < m_ptAnchor.y ||
         m_ptCursorPos.y == m_ptAnchor.y && m_ptCursorPos.x < m_ptAnchor.x)
      {
         ptStart = WordToLeft(m_ptCursorPos);
         ptEnd = WordToRight(m_ptAnchor);
      }
      else
      {
         ptStart = WordToLeft(m_ptAnchor);
         ptEnd = WordToRight(m_ptCursorPos);
      }

      m_ptCursorPos = ptEnd;
      UpdateCaret();
      EnsureVisible(m_ptCursorPos);
      SetSelection(ptStart, ptEnd);

      SetCapture();
      m_nDragSelTimer = SetTimer(CRYSTAL_TIMER_DRAGSEL, 100, NULL);
      ASSERT(m_nDragSelTimer != 0);
      m_bWordSelection = TRUE;
      m_bLineSelection = FALSE;
      m_bDragSelection = TRUE;
   }
}

void ZCrystalEditView::OnEditCopy()
{
   Copy();
}

void ZCrystalEditView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(IsSelection());
}

void ZCrystalEditView::OnEditSelectAll()
{
   SelectAllLines();
}

void ZCrystalEditView::OnUpdateEditSelectAll(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(TRUE);
}

void ZCrystalEditView::OnRButtonDown(UINT uFlags, CPoint point)
{
   CPoint pt = point;
   AdjustTextPoint(pt);
   pt = ClientToText(pt);
   if (! IsInsideSelBlock(pt))
   {
      m_ptAnchor = m_ptCursorPos = pt;
      SetSelection(m_ptCursorPos, m_ptCursorPos);
      EnsureVisible(m_ptCursorPos);
      UpdateCaret();
   }

   CView::OnRButtonDown(uFlags, point);
}

BOOL ZCrystalEditView::IsSelection()
{
   return m_ptSelStart != m_ptSelEnd;
}

void ZCrystalEditView::Copy()
{
   if ( IsSelection() )
   {
      PrepareSelBounds();
      CString text;
      GetText(m_ptDrawSelStart, m_ptDrawSelEnd, text);
      PutToClipboard(text);
   }
}

BOOL ZCrystalEditView::TextInClipboard()
{
   return IsClipboardFormatAvailable(CF_TEXT);
}

BOOL ZCrystalEditView::PutToClipboard(LPCTSTR pszText)
{
   if (pszText == NULL || lstrlen(pszText) == 0)
      return FALSE;

   CWaitCursor wc;
   BOOL bOK = FALSE;
   if (OpenClipboard())
   {
      EmptyClipboard();
      HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, lstrlen(pszText) + 1);
      if (hData != NULL)
      {
         LPSTR pszData = (LPSTR) ::GlobalLock(hData);
         USES_CONVERSION;
         strcpy_s(pszData, lstrlen(pszText) + 1, T2A((LPTSTR) pszText));
         GlobalUnlock(hData);
         bOK = SetClipboardData(CF_TEXT, hData) != NULL;
      }
      CloseClipboard();
   }
   return bOK;
}

BOOL ZCrystalEditView::GetFromClipboard(CString &text)
{
   BOOL bSuccess = FALSE;
   if (OpenClipboard())
   {
      HGLOBAL hData = GetClipboardData(CF_TEXT);
      if (hData != NULL)
      {
         LPSTR pszData = (LPSTR) GlobalLock(hData);
         if (pszData != NULL)
         {
            text = pszData;
            GlobalUnlock(hData);
            bSuccess = TRUE;
         }
      }
      CloseClipboard();
   }
   return bSuccess;
}


////////////////////////////////////////////////////////////////////////////
// File:    ZCrystalTextBuffer.cpp
// Version: 1.0.0.0
// Created: 29-Dec-1998
//
// Author:     Stcherbatchenko Andrei
// E-mail:     windfall@gmx.de
//
// Implementation of the ZCrystalTextBuffer class, a part of Crystal Edit -
// syntax coloring text editor.
//
// You are free to use or modify this code to the following restrictions:
// - Acknowledge me somewhere in your about box, simple "Parts of code by.."
// will be enough. If you can't (or don't want to), contact me personally.
// - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// 17-Feb-99
// +  FIX: unnecessary 'HANDLE' in ZCrystalTextBuffer::SaveToFile
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// 21-Feb-99
//    Paul Selormey, James R. Twine:
// +  FEATURE: description for Undo/Redo actions
// +  FEATURE: multiple MSVC-like bookmarks
// +  FEATURE: 'Disable backspace at beginning of line' option
// +  FEATURE: 'Disable drag-n-drop editing' option
//
// +  FEATURE: changed layout of SUndoRecord. Now takes less memory
////////////////////////////////////////////////////////////////////////////


// Line allocation granularity
#define     CHAR_ALIGN              16
#define     ALIGN_BUF_SIZE(size)    ((size) / CHAR_ALIGN) * CHAR_ALIGN + CHAR_ALIGN;

#define     UNDO_BUF_SIZE           1024

const TCHAR crlf[] = _T("\r\n");

#ifdef _DEBUG
#define _ADVANCED_BUGCHECK 1
#endif


/////////////////////////////////////////////////////////////////////////////
// ZCrystalTextBuffer::SUndoRecord

void ZCrystalTextBuffer::SUndoRecord::SetText(LPCTSTR pszText)
{
   m_pszText = NULL;
   if (pszText != NULL && pszText[0] != _T('\0'))
   {
      int nLength = _tcslen(pszText);
      if (nLength > 1)
      {
         m_pszText = new TCHAR[(nLength + 1) * sizeof(TCHAR)];
         strcpy_s(m_pszText, nLength + 1, pszText);
      }
      else
      {
         m_szText[0] = pszText[0];
      }
   }
}

void ZCrystalTextBuffer::SUndoRecord::FreeText()
{
   if (HIWORD((DWORD) m_pszText) != 0)
      delete m_pszText;
}


/////////////////////////////////////////////////////////////////////////////
// ZCrystalTextBuffer::ZUpdateContext

void ZCrystalTextBuffer::ZInsertContext::RecalcPoint(CPoint &ptPoint)
{
   ASSERT(m_ptEnd.y > m_ptStart.y ||
      m_ptEnd.y == m_ptStart.y && m_ptEnd.x >= m_ptStart.x);
   if (ptPoint.y < m_ptStart.y)
      return;
   if (ptPoint.y > m_ptStart.y)
   {
      ptPoint.y += (m_ptEnd.y - m_ptStart.y);
      return;
   }
   if (ptPoint.x <= m_ptStart.x)
      return;
   ptPoint.y += (m_ptEnd.y - m_ptStart.y);
   ptPoint.x = m_ptEnd.x + (ptPoint.x - m_ptStart.x);
}

void ZCrystalTextBuffer::CDeleteContext::RecalcPoint(CPoint &ptPoint)
{
   ASSERT(m_ptEnd.y > m_ptStart.y ||
      m_ptEnd.y == m_ptStart.y && m_ptEnd.x >= m_ptStart.x);
   if (ptPoint.y < m_ptStart.y)
      return;
   if (ptPoint.y > m_ptEnd.y)
   {
      ptPoint.y -= (m_ptEnd.y - m_ptStart.y);
      return;
   }
   if (ptPoint.y == m_ptEnd.y && ptPoint.x >= m_ptEnd.x)
   {
      ptPoint.y = m_ptStart.y;
      ptPoint.x = m_ptStart.x + (ptPoint.x - m_ptEnd.x);
      return;
   }
   if (ptPoint.y == m_ptStart.y)
   {
      if (ptPoint.x > m_ptStart.x)
         ptPoint.x = m_ptStart.x;
      return;
   }
   ptPoint = m_ptStart;
}


/////////////////////////////////////////////////////////////////////////////
// ZCrystalTextBuffer

IMPLEMENT_DYNAMIC(ZCrystalTextBuffer, CCmdTarget)  // IMPLEMENT_DYNCREATE(ZCrystalTextBuffer, CCmdTarget)

ZCrystalTextBuffer::ZCrystalTextBuffer()
{
   m_bInit = FALSE;     // Text buffer not yet initialized ... must call InitNew or LoadFromFile early!
   m_bReadOnly = FALSE;
   m_bModified = FALSE;
   m_bCreateBackupFile = FALSE;
   m_nUndoPosition = 0;
}

ZCrystalTextBuffer::~ZCrystalTextBuffer()
{
   ASSERT(! m_bInit);         // You must call FreeAll() before deleting the object
}


BEGIN_MESSAGE_MAP(ZCrystalTextBuffer, CCmdTarget)
   //{{AFX_MSG_MAP(ZCrystalTextBuffer)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZCrystalTextBuffer message handlers

void ZCrystalTextBuffer::InsertLine(LPCTSTR pszLine, int nLength /*= -1*/, int nPosition /*= -1*/)
{
   if (nLength == -1)
   {
      if (pszLine == NULL)
         nLength = 0;
      else
         nLength = lstrlen(pszLine);
   }

   SLineInfo li;
   li.m_nLength = nLength;
   li.m_nMax = ALIGN_BUF_SIZE(li.m_nLength);
   ASSERT(li.m_nMax >= li.m_nLength);
   if (li.m_nMax > 0)
      li.m_pcLine = new TCHAR[li.m_nMax];
   if (li.m_nLength > 0)
      memcpy(li.m_pcLine, pszLine, sizeof(TCHAR) * li.m_nLength);

   if (nPosition == -1)
      m_aLines.Add(li);
   else
      m_aLines.InsertAt(nPosition, li);

#ifdef _DEBUG
   int nLines = m_aLines.GetSize();
   if (nLines % 5000 == 0)
      TRACE1("%d lines loaded!\n", nLines);
#endif
}

void ZCrystalTextBuffer::AppendLine(int nLineIndex, LPCTSTR pszChars, int nLength /*= -1*/)
{
   if (nLength == -1)
   {
      if (pszChars == NULL)
         return;
      nLength = lstrlen(pszChars);
   }

   if (nLength == 0)
      return;

   register SLineInfo &li = m_aLines[nLineIndex];
   int nBufNeeded = li.m_nLength + nLength;
   if (nBufNeeded > li.m_nMax)
   {
      li.m_nMax = ALIGN_BUF_SIZE(nBufNeeded);
      ASSERT(li.m_nMax >= li.m_nLength + nLength);
      TCHAR *pcNewBuf = new TCHAR[li.m_nMax];
      if (li.m_nLength > 0)
         memcpy(pcNewBuf, li.m_pcLine, sizeof(TCHAR) * li.m_nLength);
      delete li.m_pcLine;
      li.m_pcLine = pcNewBuf;
   }
   memcpy(li.m_pcLine + li.m_nLength, pszChars, sizeof(TCHAR) * nLength);
   li.m_nLength += nLength;
   ASSERT(li.m_nLength <= li.m_nMax);
}

void ZCrystalTextBuffer::FreeAll()
{
   // Free text
   int nCount = m_aLines.GetSize();
   int k;
   for (k = 0; k < nCount; k++)
   {
      if (m_aLines[k].m_nMax > 0)
         delete m_aLines[k].m_pcLine;
   }
   m_aLines.RemoveAll();

   // Free undo buffer
   int nBufSize = m_aUndoBuf.GetSize();
   for (k = 0; k < nBufSize; k++)
      m_aUndoBuf[k].FreeText();
   m_aUndoBuf.RemoveAll();

   m_bInit = FALSE;
}

BOOL ZCrystalTextBuffer::InitNew(int nCrlfStyle /*= CRLF_STYLE_DOS*/)
{
   ASSERT(! m_bInit);
   ASSERT(m_aLines.GetSize() == 0);
   ASSERT(nCrlfStyle >= 0 && nCrlfStyle <= 2);
   InsertLine(_T(""));
   m_bInit = TRUE;
   m_bReadOnly = FALSE;
   m_nCRLFMode = nCrlfStyle;
   m_bModified = FALSE;
   m_nSyncPosition = m_nUndoPosition = 0;
   m_bUndoGroup = m_bUndoBeginGroup = FALSE;
   m_nUndoBufSize = UNDO_BUF_SIZE;
   ASSERT(m_aUndoBuf.GetSize() == 0);
   UpdateViews(NULL, NULL, UPDATE_RESET);
   return TRUE;
}

BOOL ZCrystalTextBuffer::GetReadOnly() const
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   return m_bReadOnly;
}

void ZCrystalTextBuffer::SetReadOnly(BOOL bReadOnly /*= TRUE*/)
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   m_bReadOnly = bReadOnly;
}

static const char *crlfs[] =
{
   "\x0d\x0a",       // DOS/Windows style
   "\x0a\x0d",       // UNIX style
   "\x0a"            // Macintosh style
};

CString
ZCrystalTextBuffer::GetFileName()
{
   return m_csFileName;
}

BOOL ZCrystalTextBuffer::LoadFromFile(LPCTSTR pszFileName, int nCrlfStyle /*= CRLF_STYLE_AUTOMATIC*/)
{
   ASSERT(! m_bInit);
   ASSERT(m_aLines.GetSize() == 0);

   HANDLE hFile = NULL;
   int nCurrentMax = 256;
   char *pcLineBuf = new char[nCurrentMax];

   BOOL bSuccess = FALSE;
   __try
   {
      DWORD dwFileAttributes = ::GetFileAttributes(pszFileName);
      if (dwFileAttributes == (DWORD) -1)
         __leave;

      hFile = ::CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
         OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
      if (hFile == INVALID_HANDLE_VALUE)
         __leave;

      int nCurrentLength = 0;

      const DWORD dwBufSize = 32768;
      char *pcBuf = (char *) _alloca(dwBufSize);
      DWORD dwCurSize;
      if (! ::ReadFile(hFile, pcBuf, dwBufSize, &dwCurSize, NULL))
         __leave;

      if (nCrlfStyle == CRLF_STYLE_AUTOMATIC)
      {
         DWORD dw;
         // Try to determine current CRLF mode
         for (dw = 0; dw < dwCurSize; dw++)
         {
            if (pcBuf[dw] == _T('\x0a'))
               break;
         }
         if (dw == dwCurSize)
         {
            // By default (or in the case of empty file), set DOS style
            nCrlfStyle = CRLF_STYLE_DOS;
         }
         else
         {
            // Otherwise, analyse the first occurance of line-feed character
            if (dw > 0 && pcBuf[dw - 1] == _T('\x0d'))
            {
               nCrlfStyle = CRLF_STYLE_DOS;
            }
            else
            {
               if (dw < dwCurSize - 1 && pcBuf[dw + 1] == _T('\x0d'))
                  nCrlfStyle = CRLF_STYLE_UNIX;
               else
                  nCrlfStyle = CRLF_STYLE_MAC;
            }
         }
      }

      ASSERT(nCrlfStyle >= 0 && nCrlfStyle <= 2);
      m_nCRLFMode = nCrlfStyle;
      const char *crlf = crlfs[nCrlfStyle];

      m_aLines.SetSize(0, 4096);

      DWORD dwBufPtr = 0;
      int nCrlfPtr = 0;
      USES_CONVERSION;
      while (dwBufPtr < dwCurSize)
      {
         int c = pcBuf[dwBufPtr];
         dwBufPtr++;
         if (dwBufPtr == dwCurSize && dwCurSize == dwBufSize)
         {
            if (! ::ReadFile(hFile, pcBuf, dwBufSize, &dwCurSize, NULL))
               __leave;
            dwBufPtr = 0;
         }

         pcLineBuf[nCurrentLength] = (char) c;
         nCurrentLength++;
         if (nCurrentLength == nCurrentMax)
         {
            // Reallocate line buffer
            nCurrentMax += 256;
            char *pcNewBuf = new char[nCurrentMax];
            memcpy(pcNewBuf, pcLineBuf, nCurrentLength);
            delete pcLineBuf;
            pcLineBuf = pcNewBuf;
         }

         if ((char) c == crlf[nCrlfPtr])
         {
            nCrlfPtr++;
            if (crlf[nCrlfPtr] == 0)
            {
               pcLineBuf[nCurrentLength - nCrlfPtr] = 0;
               InsertLine(A2T(pcLineBuf));
               nCurrentLength = 0;
               nCrlfPtr = 0;
            }
         }
         else
            nCrlfPtr = 0;
      }

      pcLineBuf[nCurrentLength] = 0;
      InsertLine(A2T(pcLineBuf));

      ASSERT(m_aLines.GetSize() > 0);     // At least one empty line must present

      m_bInit = TRUE;
      m_bReadOnly = (dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0;
      m_bModified = FALSE;
      m_bUndoGroup = m_bUndoBeginGroup = FALSE;
      m_nUndoBufSize = UNDO_BUF_SIZE;
      m_nSyncPosition = m_nUndoPosition = 0;
      ASSERT(m_aUndoBuf.GetSize() == 0);
      bSuccess = TRUE;

      UpdateViews(NULL, NULL, UPDATE_RESET);
   }
   __finally
   {
      if (pcLineBuf != NULL)
         delete pcLineBuf;
      if (hFile != NULL)
         ::CloseHandle(hFile);
   }
   return bSuccess;
}

BOOL ZCrystalTextBuffer::SaveToFile(LPCTSTR pszFileName, int nCrlfStyle /*= CRLF_STYLE_AUTOMATIC*/, BOOL bClearModifiedFlag /*= TRUE*/)
{
   ASSERT(nCrlfStyle == CRLF_STYLE_AUTOMATIC || nCrlfStyle == CRLF_STYLE_DOS ||
          nCrlfStyle == CRLF_STYLE_UNIX || nCrlfStyle == CRLF_STYLE_MAC);
   ASSERT(m_bInit);
   HANDLE hTempFile = INVALID_HANDLE_VALUE;
   HANDLE hSearch = INVALID_HANDLE_VALUE;
   TCHAR szTempFileDir[_MAX_PATH + 1];
   TCHAR szTempFileName[_MAX_PATH + 1];
   TCHAR szBackupFileName[_MAX_PATH + 1];
   BOOL bSuccess = FALSE;
   __try
   {
      TCHAR drive[_MAX_PATH], dir[_MAX_PATH], name[_MAX_PATH], ext[_MAX_PATH];
#ifdef _UNICODE
      _wsplitpath(pszFileName, drive, dir, name, ext);
#else
      _splitpath_s(pszFileName, drive, dir, name, ext);
#endif
      lstrcpy(szTempFileDir, drive);
      lstrcat(szTempFileDir, dir);
      lstrcpy(szBackupFileName, pszFileName);
      lstrcat(szBackupFileName, _T(".bak"));

      if (::GetTempFileName(szTempFileDir, _T("CRE"), 0, szTempFileName) == 0)
         __leave;

      hTempFile = ::CreateFile(szTempFileName, GENERIC_WRITE, 0, NULL,
         CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
      if (hTempFile == INVALID_HANDLE_VALUE)
         __leave;

      if (nCrlfStyle == CRLF_STYLE_AUTOMATIC)
         nCrlfStyle = m_nCRLFMode;

      ASSERT(nCrlfStyle >= 0 && nCrlfStyle <= 2);
      const char *pszCRLF = crlfs[nCrlfStyle];
      int nCRLFLength = strlen(pszCRLF);

      int nLineCount = m_aLines.GetSize();
      USES_CONVERSION;
      for (int nLine = 0; nLine < nLineCount; nLine++)
      {
         int nLength = m_aLines[nLine].m_nLength;
         DWORD dwWrittenBytes;
         if (nLength > 0)
         {
            if (! ::WriteFile(hTempFile, T2A(m_aLines[nLine].m_pcLine), nLength, &dwWrittenBytes, NULL))
               __leave;
            if (nLength != (int) dwWrittenBytes)
               __leave;
         }
         if (nLine < nLineCount - 1)   // Last line must not end with CRLF
         {
            if (! ::WriteFile(hTempFile, pszCRLF, nCRLFLength, &dwWrittenBytes, NULL))
               __leave;
            if (nCRLFLength != (int) dwWrittenBytes)
               __leave;
         }
      }
      ::CloseHandle(hTempFile);
      hTempFile = INVALID_HANDLE_VALUE;

      if (m_bCreateBackupFile)
      {
         WIN32_FIND_DATA wfd;
         hSearch = ::FindFirstFile(pszFileName, &wfd);
         if (hSearch != INVALID_HANDLE_VALUE)
         {
            // File exist - create backup file
            ::DeleteFile(szBackupFileName);
            if (! ::MoveFile(pszFileName, szBackupFileName))
               __leave;
            ::FindClose(hSearch);
            hSearch = INVALID_HANDLE_VALUE;
         }
      }
      else
      {
         ::DeleteFile(pszFileName);
      }

      // Move temporary file to target name
      if (! ::MoveFile(szTempFileName, pszFileName))
         __leave;

      if (bClearModifiedFlag)
      {
         SetModified(FALSE);
         m_nSyncPosition = m_nUndoPosition;
      }
      bSuccess = TRUE;
   }
   __finally
   {
      if (hSearch != INVALID_HANDLE_VALUE)
         ::FindClose(hSearch);
      if (hTempFile != INVALID_HANDLE_VALUE)
         ::CloseHandle(hTempFile);
      ::DeleteFile(szTempFileName);
   }
   return bSuccess;
}

int ZCrystalTextBuffer::GetCRLFMode()
{
   return m_nCRLFMode;
}

void ZCrystalTextBuffer::SetCRLFMode(int nCRLFMode)
{
   ASSERT(nCRLFMode == CRLF_STYLE_DOS || nCRLFMode == CRLF_STYLE_UNIX || nCRLFMode == CRLF_STYLE_MAC);
   m_nCRLFMode = nCRLFMode;
}

int ZCrystalTextBuffer::GetLineCount()
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   return m_aLines.GetSize();
}

int ZCrystalTextBuffer::GetLineLength(int nLine)
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   return m_aLines[nLine].m_nLength;
}

LPTSTR ZCrystalTextBuffer::GetLineChars(int nLine)
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   return m_aLines[nLine].m_pcLine;
}

DWORD ZCrystalTextBuffer::GetLineFlags(int nLine)
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   return m_aLines[nLine].m_dwFlags;
}

static int FlagToIndex(DWORD dwFlag)
{
   int nIndex = 0;
   while ((dwFlag & 1) == 0)
   {
      dwFlag = dwFlag >> 1;
      nIndex++;
      if (nIndex == 32)
         return -1;
   }
   dwFlag = dwFlag & 0xFFFFFFFE;
   if (dwFlag != 0)
      return -1;
   return nIndex;

}

int ZCrystalTextBuffer::FindLineWithFlag(DWORD dwFlag)
{
   int nSize = m_aLines.GetSize();
   for (int L = 0; L < nSize; L++)
   {
      if ((m_aLines[L].m_dwFlags & dwFlag) != 0)
         return L;
   }
   return -1;
}

int ZCrystalTextBuffer::GetLineWithFlag(DWORD dwFlag)
{
   int nFlagIndex = ::FlagToIndex(dwFlag);
   if (nFlagIndex < 0)
   {
      ASSERT(FALSE);    // Invalid flag passed in
      return -1;
   }
   return FindLineWithFlag(dwFlag);
}

void ZCrystalTextBuffer::SetLineFlag(int nLine, DWORD dwFlag, BOOL bSet, BOOL bRemoveFromPreviousLine /*= TRUE*/)
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!

   int nFlagIndex = ::FlagToIndex(dwFlag);
   if (nFlagIndex < 0)
   {
      ASSERT(FALSE);    // Invalid flag passed in
      return;
   }

   if (nLine == -1)
   {
      ASSERT(! bSet);
      nLine = FindLineWithFlag(dwFlag);
      if (nLine == -1)
         return;
      bRemoveFromPreviousLine = FALSE;
   }

   DWORD dwNewFlags = m_aLines[nLine].m_dwFlags;
   if (bSet)
      dwNewFlags = dwNewFlags | dwFlag;
   else
      dwNewFlags = dwNewFlags & ~dwFlag;

   if (m_aLines[nLine].m_dwFlags != dwNewFlags)
   {
      if (bRemoveFromPreviousLine)
      {
         int nPrevLine = FindLineWithFlag(dwFlag);
         if (bSet)
         {
            if (nPrevLine >= 0)
            {
               ASSERT((m_aLines[nPrevLine].m_dwFlags & dwFlag) != 0);
               m_aLines[nPrevLine].m_dwFlags &= ~dwFlag;
               UpdateViews(NULL, NULL, UPDATE_SINGLELINE | UPDATE_FLAGSONLY, nPrevLine);
            }
         }
         else
         {
            ASSERT(nPrevLine == nLine);
         }
      }

      m_aLines[nLine].m_dwFlags = dwNewFlags;
      UpdateViews(NULL, NULL, UPDATE_SINGLELINE | UPDATE_FLAGSONLY, nLine);
   }
}

void ZCrystalTextBuffer::GetText(int nStartLine, int nStartChar, int nEndLine, int nEndChar, CString &text, LPCTSTR pszCRLF /*= NULL*/)
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   ASSERT(nStartLine >= 0 && nStartLine < m_aLines.GetSize());
   ASSERT(nStartChar >= 0 && nStartChar <= m_aLines[nStartLine].m_nLength);
   ASSERT(nEndLine >= 0 && nEndLine < m_aLines.GetSize());
   ASSERT(nEndChar >= 0 && nEndChar <= m_aLines[nEndLine].m_nLength);
   ASSERT(nStartLine < nEndLine || nStartLine == nEndLine && nStartChar < nEndChar);

   if (pszCRLF == NULL)
      pszCRLF = crlf;
   int nCRLFLength = lstrlen(pszCRLF);
   ASSERT(nCRLFLength > 0);

   int nBufSize = 0;
   int k;
   for (k = nStartLine; k <= nEndLine; k++)
   {
      nBufSize += m_aLines[k].m_nLength;
      nBufSize += nCRLFLength;
   }

   LPTSTR pszBuf = text.GetBuffer(nBufSize);
   LPTSTR pszCurPos = pszBuf;

   if (nStartLine < nEndLine)
   {
      int nCount = m_aLines[nStartLine].m_nLength - nStartChar;
      if (nCount > 0)
      {
         memcpy(pszBuf, m_aLines[nStartLine].m_pcLine + nStartChar, sizeof(TCHAR) * nCount);
         pszBuf += nCount;
      }
      memcpy(pszBuf, pszCRLF, sizeof(TCHAR) * nCRLFLength);
      pszBuf += nCRLFLength;
      for (k = nStartLine + 1; k < nEndLine; k++)
      {
         nCount = m_aLines[k].m_nLength;
         if (nCount > 0)
         {
            memcpy(pszBuf, m_aLines[k].m_pcLine, sizeof(TCHAR) * nCount);
            pszBuf += nCount;
         }
         memcpy(pszBuf, pszCRLF, sizeof(TCHAR) * nCRLFLength);
         pszBuf += nCRLFLength;
      }
      if (nEndChar > 0)
      {
         memcpy(pszBuf, m_aLines[nEndLine].m_pcLine, sizeof(TCHAR) * nEndChar);
         pszBuf += nEndChar;
      }
   }
   else
   {
      k = nEndChar - nStartChar;
      memcpy(pszBuf, m_aLines[nStartLine].m_pcLine + nStartChar, sizeof(TCHAR) * k);
      pszBuf += k;
   }
   pszBuf[0] = 0;
   text.ReleaseBuffer();
   text.FreeExtra();
}

void ZCrystalTextBuffer::AddView(ZCrystalEditView *pView)
{
   m_lpViews.AddTail(pView);
}

void ZCrystalTextBuffer::RemoveView(ZCrystalEditView *pView)
{
   POSITION pos = m_lpViews.GetHeadPosition();
   while (pos != NULL)
   {
      POSITION thispos = pos;
      ZCrystalEditView *pvw = m_lpViews.GetNext(pos);
      if (pvw == pView)
      {
         m_lpViews.RemoveAt(thispos);
         return;
      }
   }
   ASSERT(FALSE);
}

void ZCrystalTextBuffer::UpdateViews(ZCrystalEditView *pSource, ZUpdateContext *pContext, DWORD dwUpdateFlags, int nLineIndex /*= -1*/)
{
   POSITION pos = m_lpViews.GetHeadPosition();
   while (pos != NULL)
   {
      ZCrystalEditView *pView = m_lpViews.GetNext(pos);
      pView->UpdateView(pSource, pContext, dwUpdateFlags, nLineIndex);
   }
}

BOOL ZCrystalTextBuffer::InternalDeleteText(ZCrystalEditView *pSource, int nStartLine, int nStartChar, int nEndLine, int nEndChar)
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   ASSERT(nStartLine >= 0 && nStartLine < m_aLines.GetSize());
   ASSERT(nStartChar >= 0 && nStartChar <= m_aLines[nStartLine].m_nLength);
   ASSERT(nEndLine >= 0 && nEndLine < m_aLines.GetSize());
   ASSERT(nEndChar >= 0 && nEndChar <= m_aLines[nEndLine].m_nLength);
   ASSERT(nStartLine < nEndLine || nStartLine == nEndLine && nStartChar < nEndChar);
   if (m_bReadOnly)
      return FALSE;

   CDeleteContext context;
   context.m_ptStart.y = nStartLine;
   context.m_ptStart.x = nStartChar;
   context.m_ptEnd.y = nEndLine;
   context.m_ptEnd.x = nEndChar;
   if (nStartLine == nEndLine)
   {
      SLineInfo &li = m_aLines[nStartLine];
      if (nEndChar < li.m_nLength)
      {
         memcpy(li.m_pcLine + nStartChar, li.m_pcLine + nEndChar,
            sizeof(TCHAR) * (li.m_nLength - nEndChar));
      }
      li.m_nLength -= (nEndChar - nStartChar);

      UpdateViews(pSource, &context, UPDATE_SINGLELINE | UPDATE_HORZRANGE, nStartLine);
   }
   else
   {
      int nRestCount = m_aLines[nEndLine].m_nLength - nEndChar;
      LPTSTR pszRestChars = NULL;
      if (nRestCount > 0)
      {
         pszRestChars = new TCHAR[nRestCount];
         memcpy(pszRestChars, m_aLines[nEndLine].m_pcLine + nEndChar, nRestCount * sizeof(TCHAR));
      }

      int nDelCount = nEndLine - nStartLine;
      for (int L = nStartLine + 1; L <= nEndLine; L++)
         delete m_aLines[L].m_pcLine;
      m_aLines.RemoveAt(nStartLine + 1, nDelCount);

      // nEndLine is no more valid
      m_aLines[nStartLine].m_nLength = nStartChar;
      if (nRestCount > 0)
      {
         AppendLine(nStartLine, pszRestChars, nRestCount);
         delete pszRestChars;
      }

      UpdateViews(pSource, &context, UPDATE_HORZRANGE | UPDATE_VERTRANGE, nStartLine);
   }

   if (! m_bModified)
      SetModified(TRUE);
   return TRUE;
}

BOOL ZCrystalTextBuffer::InternalInsertText(ZCrystalEditView *pSource, int nLine, int nPos, LPCTSTR pszText, int &nEndLine, int &nEndChar)
{
   ASSERT(m_bInit);  // Text buffer not yet initialized.
                     // You must call InitNew() or LoadFromFile() first!
   ASSERT(nLine >= 0 && nLine < m_aLines.GetSize());
   ASSERT(nPos >= 0 && nPos <= m_aLines[nLine].m_nLength);
   if (m_bReadOnly)
      return FALSE;

   ZInsertContext context;
   context.m_ptStart.x = nPos;
   context.m_ptStart.y = nLine;

   int nRestCount = m_aLines[nLine].m_nLength - nPos;
   LPTSTR pszRestChars = NULL;
   if (nRestCount > 0)
   {
      pszRestChars = new TCHAR[nRestCount];
      memcpy(pszRestChars, m_aLines[nLine].m_pcLine + nPos, nRestCount * sizeof(TCHAR));
      m_aLines[nLine].m_nLength = nPos;
   }

   int nCurrentLine = nLine;
   BOOL bNewLines = FALSE;
   int nTextPos;
   for (;;)
   {
      nTextPos = 0;
      while (pszText[nTextPos] != 0 && pszText[nTextPos] != _T('\r'))
         nTextPos++;

      if (nCurrentLine == nLine)
      {
         AppendLine(nLine, pszText, nTextPos);
      }
      else
      {
         InsertLine(pszText, nTextPos, nCurrentLine);
         bNewLines = TRUE;
      }

      if (pszText[nTextPos] == 0)
      {
         nEndLine = nCurrentLine;
         nEndChar = m_aLines[nCurrentLine].m_nLength;
         AppendLine(nCurrentLine, pszRestChars, nRestCount);
         break;
      }

      nCurrentLine++;
      nTextPos++;

      if (pszText[nTextPos] == _T('\n'))
      {
         nTextPos++;
      }
      else
      {
         ASSERT(FALSE);       // Invalid line-end format passed
      }

      pszText += nTextPos;
   }

   if (pszRestChars != NULL)
      delete pszRestChars;

   context.m_ptEnd.x = nEndChar;
   context.m_ptEnd.y = nEndLine;

   if (bNewLines)
      UpdateViews(pSource, &context, UPDATE_HORZRANGE | UPDATE_VERTRANGE, nLine);
   else
      UpdateViews(pSource, &context, UPDATE_SINGLELINE | UPDATE_HORZRANGE, nLine);

   if (! m_bModified)
      SetModified(TRUE);
   return TRUE;
}

BOOL ZCrystalTextBuffer::CanUndo()
{
   ASSERT(m_nUndoPosition >= 0 && m_nUndoPosition <= m_aUndoBuf.GetSize());
   return m_nUndoPosition > 0;
}

BOOL ZCrystalTextBuffer::CanRedo()
{
   ASSERT(m_nUndoPosition >= 0 && m_nUndoPosition <= m_aUndoBuf.GetSize());
   return m_nUndoPosition < m_aUndoBuf.GetSize();
}

POSITION ZCrystalTextBuffer::GetUndoDescription(CString &desc, POSITION pos /*= NULL*/)
{
   ASSERT(CanUndo());      // Please call CanUndo() first
   ASSERT((m_aUndoBuf[0].m_dwFlags & UNDO_BEGINGROUP) != 0);

   int nPosition;
   if (pos == NULL)
   {
      // Start from beginning
      nPosition = m_nUndoPosition;
   }
   else
   {
      nPosition = (int) pos;
      ASSERT(nPosition > 0 && nPosition < m_nUndoPosition);
      ASSERT((m_aUndoBuf[nPosition].m_dwFlags & UNDO_BEGINGROUP) != 0);
   }

   // Advance to next undo group
   nPosition--;
   while ((m_aUndoBuf[nPosition].m_dwFlags & UNDO_BEGINGROUP) == 0)
      nPosition--;

   // Read description
   if (! GetActionDescription(m_aUndoBuf[nPosition].m_nAction, desc))
      desc.Empty();     // Use empty string as description

                        // Now, if we stop at zero position, this will be the last action,
                        // since we return (POSITION) nPosition
   return (POSITION) nPosition;
}

POSITION ZCrystalTextBuffer::GetRedoDescription(CString &desc, POSITION pos /*= NULL*/)
{
   ASSERT(CanRedo());      // Please call CanRedo() before!
   ASSERT((m_aUndoBuf[0].m_dwFlags & UNDO_BEGINGROUP) != 0);
   ASSERT((m_aUndoBuf[m_nUndoPosition].m_dwFlags & UNDO_BEGINGROUP) != 0);

   int nPosition;
   if (pos == NULL)
   {
      // Start from beginning
      nPosition = m_nUndoPosition;
   }
   else
   {
      nPosition = (int) pos;
      ASSERT(nPosition > m_nUndoPosition);
      ASSERT((m_aUndoBuf[nPosition].m_dwFlags & UNDO_BEGINGROUP) != 0);
   }

   // Read description
   if (! GetActionDescription(m_aUndoBuf[nPosition].m_nAction, desc))
      desc.Empty();     // Use empty string as description

                        // Advance to next undo group
   nPosition++;
   while (nPosition < m_aUndoBuf.GetSize() && (m_aUndoBuf[nPosition].m_dwFlags & UNDO_BEGINGROUP) == 0)
      nPosition--;

   if (nPosition >= m_aUndoBuf.GetSize())
      return NULL;   // No more redo actions!
   return (POSITION) nPosition;
}

BOOL ZCrystalTextBuffer::Undo(CPoint &ptCursorPos)
{
   ASSERT(CanUndo());
   ASSERT((m_aUndoBuf[0].m_dwFlags & UNDO_BEGINGROUP) != 0);
   for (;;)
   {
      m_nUndoPosition--;
      const SUndoRecord &ur = m_aUndoBuf[m_nUndoPosition];
      if (ur.m_dwFlags & UNDO_INSERT)
      {
#ifdef _ADVANCED_BUGCHECK
         // Try to ensure that we undoing correctly...
         // Just compare the text as it was before Undo operation
         CString text;
         GetText(ur.m_ptStartPos.y, ur.m_ptStartPos.x, ur.m_ptEndPos.y, ur.m_ptEndPos.x, text);
         ASSERT(lstrcmp(text, ur.GetText()) == 0);
#endif
         VERIFY(InternalDeleteText(NULL, ur.m_ptStartPos.y, ur.m_ptStartPos.x, ur.m_ptEndPos.y, ur.m_ptEndPos.x));
         ptCursorPos = ur.m_ptStartPos;
      }
      else
      {
         int nEndLine, nEndChar;
         VERIFY(InternalInsertText(NULL, ur.m_ptStartPos.y, ur.m_ptStartPos.x, ur.GetText(), nEndLine, nEndChar));
#ifdef _ADVANCED_BUGCHECK
         ASSERT(ur.m_ptEndPos.y == nEndLine);
         ASSERT(ur.m_ptEndPos.x == nEndChar);
#endif
         ptCursorPos = ur.m_ptEndPos;
      }
      if (ur.m_dwFlags & UNDO_BEGINGROUP)
         break;
   }
   if (m_bModified && m_nSyncPosition == m_nUndoPosition)
      SetModified(FALSE);
   if (! m_bModified && m_nSyncPosition != m_nUndoPosition)
      SetModified(TRUE);
   return TRUE;
}

BOOL ZCrystalTextBuffer::Redo(CPoint &ptCursorPos)
{
   ASSERT(CanRedo());
   ASSERT((m_aUndoBuf[0].m_dwFlags & UNDO_BEGINGROUP) != 0);
   ASSERT((m_aUndoBuf[m_nUndoPosition].m_dwFlags & UNDO_BEGINGROUP) != 0);
   for (;;)
   {
      const SUndoRecord &ur = m_aUndoBuf[m_nUndoPosition];
      if (ur.m_dwFlags & UNDO_INSERT)
      {
         int nEndLine, nEndChar;
         VERIFY(InternalInsertText(NULL, ur.m_ptStartPos.y, ur.m_ptStartPos.x, ur.GetText(), nEndLine, nEndChar));
#ifdef _ADVANCED_BUGCHECK
         ASSERT(ur.m_ptEndPos.y == nEndLine);
         ASSERT(ur.m_ptEndPos.x == nEndChar);
#endif
         ptCursorPos = ur.m_ptEndPos;
      }
      else
      {
#ifdef _ADVANCED_BUGCHECK
         CString text;
         GetText(ur.m_ptStartPos.y, ur.m_ptStartPos.x, ur.m_ptEndPos.y, ur.m_ptEndPos.x, text);
         ASSERT(lstrcmp(text, ur.GetText()) == 0);
#endif
         VERIFY(InternalDeleteText(NULL, ur.m_ptStartPos.y, ur.m_ptStartPos.x, ur.m_ptEndPos.y, ur.m_ptEndPos.x));
         ptCursorPos = ur.m_ptStartPos;
      }
      m_nUndoPosition++;
      if (m_nUndoPosition == m_aUndoBuf.GetSize())
         break;
      if ((m_aUndoBuf[m_nUndoPosition].m_dwFlags & UNDO_BEGINGROUP) != 0)
         break;
   }
   if (m_bModified && m_nSyncPosition == m_nUndoPosition)
      SetModified(FALSE);
   if (! m_bModified && m_nSyncPosition != m_nUndoPosition)
      SetModified(TRUE);
   return TRUE;
}

// [JRT] Support For Descriptions On Undo/Redo Actions
void ZCrystalTextBuffer::AddUndoRecord(BOOL bInsert, const CPoint &ptStartPos, const CPoint &ptEndPos, LPCTSTR pszText, int nActionType)
{
   // Forgot to call BeginUndoGroup()?
   ASSERT(m_bUndoGroup);
   ASSERT(m_aUndoBuf.GetSize() == 0 || (m_aUndoBuf[0].m_dwFlags & UNDO_BEGINGROUP) != 0);

   // Strip unnecessary undo records (edit after undo)
   int nBufSize = m_aUndoBuf.GetSize();
   if (m_nUndoPosition < nBufSize)
   {
      int k;
      for (k = m_nUndoPosition; k < nBufSize; k++)
         m_aUndoBuf[k].FreeText();
      m_aUndoBuf.SetSize(m_nUndoPosition);
   }

   // If undo buffer size is close to critical, remove the oldest records
   ASSERT(m_aUndoBuf.GetSize() <= m_nUndoBufSize);
   nBufSize = m_aUndoBuf.GetSize();
   if (nBufSize >= m_nUndoBufSize)
   {
      int nIndex = 0;
      for (;;)
      {
         m_aUndoBuf[nIndex].FreeText();
         nIndex++;
         if (nIndex == nBufSize || (m_aUndoBuf[nIndex].m_dwFlags & UNDO_BEGINGROUP) != 0)
            break;
      }
      m_aUndoBuf.RemoveAt(0, nIndex);
   }
   ASSERT(m_aUndoBuf.GetSize() < m_nUndoBufSize);

   // Add new record
   SUndoRecord ur;
   ur.m_dwFlags = bInsert ? UNDO_INSERT : 0;
   ur.m_nAction = nActionType;
   if (m_bUndoBeginGroup)
   {
      ur.m_dwFlags |= UNDO_BEGINGROUP;
      m_bUndoBeginGroup = FALSE;
   }
   ur.m_ptStartPos = ptStartPos;
   ur.m_ptEndPos = ptEndPos;
   ur.SetText(pszText);

   m_aUndoBuf.Add(ur);
   m_nUndoPosition = m_aUndoBuf.GetSize();

   ASSERT(m_aUndoBuf.GetSize() <= m_nUndoBufSize);
}

BOOL ZCrystalTextBuffer::InsertText(ZCrystalEditView *pSource, int nLine, int nPos, LPCTSTR pszText,
                                    int &nEndLine, int &nEndChar, int nAction)
{
   if (! InternalInsertText(pSource, nLine, nPos, pszText, nEndLine, nEndChar))
      return FALSE;

   BOOL bGroupFlag = FALSE;
   if (! m_bUndoGroup)
   {
      BeginUndoGroup();
      bGroupFlag = TRUE;
   }
   AddUndoRecord(TRUE, CPoint(nPos, nLine), CPoint(nEndChar, nEndLine), pszText, nAction);
   if (bGroupFlag)
      FlushUndoGroup(pSource);
   return TRUE;
}

BOOL ZCrystalTextBuffer::DeleteText(ZCrystalEditView *pSource, int nStartLine, int nStartChar,
                                    int nEndLine, int nEndChar, int nAction)
{
   CString sTextToDelete;
   GetText(nStartLine, nStartChar, nEndLine, nEndChar, sTextToDelete);

   if (! InternalDeleteText(pSource, nStartLine, nStartChar, nEndLine, nEndChar))
      return FALSE;

   BOOL bGroupFlag = FALSE;
   if (! m_bUndoGroup)
   {
      BeginUndoGroup();
      bGroupFlag = TRUE;
   }
   AddUndoRecord(FALSE, CPoint(nStartChar, nStartLine), CPoint(nEndChar, nEndLine), sTextToDelete, nAction);
   if (bGroupFlag)
      FlushUndoGroup(pSource);
   return TRUE;
}

BOOL ZCrystalTextBuffer::GetActionDescription(int nAction, CString &desc)
{
   HINSTANCE hOldResHandle = AfxGetResourceHandle();
#ifdef CRYSEDIT_RES_HANDLE
   AfxSetResourceHandle(CRYSEDIT_RES_HANDLE);
#else
   if (ZCrystalEditView::s_hResourceInst != NULL)
      AfxSetResourceHandle(ZCrystalEditView::s_hResourceInst);
#endif
   BOOL bSuccess = FALSE;
   switch (nAction)
   {
   case CE_ACTION_UNKNOWN:
      bSuccess = desc.LoadString(IDS_EDIT_OP_UNKNOWN);
      break;
   case CE_ACTION_PASTE:
      bSuccess = desc.LoadString(IDS_EDIT_OP_PASTE);
      break;
   case CE_ACTION_DELSEL:
      bSuccess = desc.LoadString(IDS_EDIT_OP_DELSELECTION);
      break;
   case CE_ACTION_CUT:
      bSuccess = desc.LoadString(IDS_EDIT_OP_CUT);
      break;
   case CE_ACTION_TYPING:
      bSuccess = desc.LoadString(IDS_EDIT_OP_TYPING);
      break;
   case CE_ACTION_BACKSPACE:
      bSuccess = desc.LoadString(IDS_EDIT_OP_BACKSPACE);
      break;
   case CE_ACTION_INDENT:
      bSuccess = desc.LoadString(IDS_EDIT_OP_INDENT);
      break;
   case CE_ACTION_DRAGDROP:
      bSuccess = desc.LoadString(IDS_EDIT_OP_DRAGDROP);
      break;
   case CE_ACTION_REPLACE:
      bSuccess = desc.LoadString(IDS_EDIT_OP_REPLACE);
      break;
   case CE_ACTION_DELETE:
      bSuccess = desc.LoadString(IDS_EDIT_OP_DELETE);
      break;
   case CE_ACTION_AUTOINDENT:
      bSuccess = desc.LoadString(IDS_EDIT_OP_AUTOINDENT);
      break;
   }
   AfxSetResourceHandle(hOldResHandle);
   return bSuccess;
}

void ZCrystalTextBuffer::SetModified(BOOL bModified /*= TRUE*/)
{
   m_bModified = bModified;
}

void ZCrystalTextBuffer::BeginUndoGroup(BOOL bMergeWithPrevious /*= FALSE*/)
{
   ASSERT(! m_bUndoGroup);
   m_bUndoGroup = TRUE;
   m_bUndoBeginGroup = m_nUndoPosition == 0 || ! bMergeWithPrevious;
}

void ZCrystalTextBuffer::FlushUndoGroup(ZCrystalEditView *pSource)
{
   ASSERT(m_bUndoGroup);
   if (pSource != NULL)
   {
      ASSERT(m_nUndoPosition == m_aUndoBuf.GetSize());
      if (m_nUndoPosition > 0)
      {
         m_bUndoBeginGroup = TRUE;
         pSource->OnEditOperation(m_aUndoBuf[m_nUndoPosition - 1].m_nAction, m_aUndoBuf[m_nUndoPosition - 1].GetText());
      }
   }
   m_bUndoGroup = FALSE;
}

int ZCrystalTextBuffer::FindNextBookmarkLine(int nCurrentLine)
{
   BOOL bWrapIt = TRUE;
   DWORD dwFlags = GetLineFlags(nCurrentLine);
   if ((dwFlags & LF_BOOKMARKS) != 0)
      nCurrentLine++;

   int nSize = m_aLines.GetSize();
   for (;;)
   {
      while (nCurrentLine < nSize)
      {
         if ((m_aLines[nCurrentLine].m_dwFlags & LF_BOOKMARKS) != 0)
            return nCurrentLine;
         // Keep going
         nCurrentLine++;
      }
      // End of text reached
      if (!bWrapIt)
         return -1;

      // Start from the beginning of text
      bWrapIt = FALSE;
      nCurrentLine = 0;
   }
   return -1;
}

int ZCrystalTextBuffer::FindPrevBookmarkLine(int nCurrentLine)
{
   BOOL bWrapIt = TRUE;
   DWORD dwFlags = GetLineFlags(nCurrentLine);
   if ((dwFlags & LF_BOOKMARKS) != 0)
      nCurrentLine--;

   int nSize = m_aLines.GetSize();
   for (;;)
   {
      while (nCurrentLine >= 0)
      {
         if ((m_aLines[nCurrentLine].m_dwFlags & LF_BOOKMARKS) != 0)
            return nCurrentLine;
         // Keep moving up
         nCurrentLine--;
      }
      // Beginning of text reached
      if (!bWrapIt)
         return -1;

      // Start from the end of text
      bWrapIt = FALSE;
      nCurrentLine = nSize - 1;
   }
   return -1;
}

BOOL ZCrystalTextBuffer::IsModified() const
{
   return m_bModified;
}

/////////////////////////////////////////////////////////////////////////////

BOOL ZCrystalEditView::GetOverwriteMode() const
{
   return m_bOvrMode;
}

void ZCrystalEditView::SetOverwriteMode(BOOL bOvrMode /*= TRUE*/)
{
   m_bOvrMode = bOvrMode;
}

BOOL ZCrystalEditView::GetDisableBSAtSOL() const
{
   return m_bDisableBSAtSOL;
}

BOOL ZCrystalEditView::GetAutoIndent() const
{
   return m_bAutoIndent;
}

void ZCrystalEditView::SetAutoIndent(BOOL bAutoIndent)
{
   m_bAutoIndent = bAutoIndent;
}

/////////////////////////////////////////////////////////////////////////////
// ZEditReplaceDlg dialog


ZEditReplaceDlg::ZEditReplaceDlg(ZCrystalEditView *pBuddy) : CDialog(ZEditReplaceDlg::IDD, NULL)
{
   ASSERT(pBuddy != NULL);
   m_pBuddy = pBuddy;
   //{{AFX_DATA_INIT(ZEditReplaceDlg)
   m_bMatchCase = FALSE;
   m_bWholeWord = FALSE;
   m_sText = _T("");
   m_sNewText = _T("");
   m_nScope = -1;
   //}}AFX_DATA_INIT
   m_bEnableScopeSelection = TRUE;
}


void ZEditReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ZEditReplaceDlg)
   DDX_Check(pDX, IDC_EDIT_MATCH_CASE, m_bMatchCase);
   DDX_Check(pDX, IDC_EDIT_WHOLE_WORD, m_bWholeWord);
   DDX_Text(pDX, IDC_EDIT_TEXT, m_sText);
   DDX_Text(pDX, IDC_EDIT_REPLACE_WITH, m_sNewText);
   DDX_Radio(pDX, IDC_EDIT_SCOPE_SELECTION, m_nScope);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZEditReplaceDlg, CDialog)
   //{{AFX_MSG_MAP(ZEditReplaceDlg)
   ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
   ON_BN_CLICKED(IDC_EDIT_REPLACE, OnEditReplace)
   ON_BN_CLICKED(IDC_EDIT_REPLACE_ALL, OnEditReplaceAll)
   ON_BN_CLICKED(IDC_EDIT_SKIP, OnEditSkip)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZEditReplaceDlg message handlers

void ZEditReplaceDlg::OnChangeEditText()
{
   CString text;
   GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(text);
   GetDlgItem(IDC_EDIT_SKIP)->EnableWindow(text != _T(""));
}

void ZEditReplaceDlg::OnCancel()
{
   VERIFY(UpdateData());

   CDialog::OnCancel();
}

BOOL ZEditReplaceDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   GetDlgItem(IDC_EDIT_SKIP)->EnableWindow(m_sText != _T(""));
   GetDlgItem(IDC_EDIT_SCOPE_SELECTION)->EnableWindow(m_bEnableScopeSelection);
   m_bFound = FALSE;

   return TRUE;
}

BOOL ZEditReplaceDlg::DoHighlightText()
{
   ASSERT(m_pBuddy != NULL);
   DWORD dwSearchFlags = 0;
   if (m_bMatchCase)
      dwSearchFlags |= FIND_MATCH_CASE;
   if (m_bWholeWord)
      dwSearchFlags |= FIND_WHOLE_WORD;

   BOOL bFound;
   if (m_nScope == 0)
   {
      // Searching selection only
      bFound = m_pBuddy->FindTextInBlock(m_sText, m_ptFoundAt, m_ptBlockBegin, m_ptBlockEnd,
         dwSearchFlags, FALSE, &m_ptFoundAt);
   }
   else
   {
      // Searching whole text
      bFound = m_pBuddy->FindText(m_sText, m_ptFoundAt, dwSearchFlags, FALSE, &m_ptFoundAt);
   }

   if (! bFound)
   {
      CString prompt;
      prompt.Format(IDS_EDIT_TEXT_NOT_FOUND, m_sText);
      AfxMessageBox(prompt);
      m_ptCurrentPos = m_nScope == 0 ? m_ptBlockBegin : CPoint(0, 0);
      return FALSE;
   }

   m_pBuddy->HighlightText(m_ptFoundAt, lstrlen(m_sText));
   return TRUE;
}

void ZEditReplaceDlg::OnEditSkip()
{
   if (! UpdateData())
      return;

   if (! m_bFound)
   {
      m_ptFoundAt = m_ptCurrentPos;
      m_bFound = DoHighlightText();
      return;
   }

   m_ptFoundAt.x += 1;
   m_bFound = DoHighlightText();
}

void ZEditReplaceDlg::OnEditReplace()
{
   if (! UpdateData())
      return;

   if (! m_bFound)
   {
      m_ptFoundAt = m_ptCurrentPos;
      m_bFound = DoHighlightText();
      return;
   }

   // We have highlighted text
   VERIFY(m_pBuddy->ReplaceSelection(m_sNewText));

   // Manually recalculate points
   if (m_bEnableScopeSelection)
   {
      if (m_ptBlockBegin.y == m_ptFoundAt.y && m_ptBlockBegin.x > m_ptFoundAt.x)
      {
         m_ptBlockBegin.x -= lstrlen(m_sText);
         m_ptBlockBegin.x += lstrlen(m_sNewText);
      }
      if (m_ptBlockEnd.y == m_ptFoundAt.y && m_ptBlockEnd.x > m_ptFoundAt.x)
      {
         m_ptBlockEnd.x -= lstrlen(m_sText);
         m_ptBlockEnd.x += lstrlen(m_sNewText);
      }
   }
   m_ptFoundAt.x += lstrlen(m_sNewText);
   m_bFound = DoHighlightText();
}

void ZEditReplaceDlg::OnEditReplaceAll()
{
   if (! UpdateData())
      return;

   if (! m_bFound)
   {
      m_ptFoundAt = m_ptCurrentPos;
      m_bFound = DoHighlightText();
   }

   while (m_bFound)
   {
      // We have highlighted text
      VERIFY(m_pBuddy->ReplaceSelection(m_sNewText));

      // Manually recalculate points
      if (m_bEnableScopeSelection)
      {
         if (m_ptBlockBegin.y == m_ptFoundAt.y && m_ptBlockBegin.x > m_ptFoundAt.x)
         {
            m_ptBlockBegin.x -= lstrlen(m_sText);
            m_ptBlockBegin.x += lstrlen(m_sNewText);
         }
         if (m_ptBlockEnd.y == m_ptFoundAt.y && m_ptBlockEnd.x > m_ptFoundAt.x)
         {
            m_ptBlockEnd.x -= lstrlen(m_sText);
            m_ptBlockEnd.x += lstrlen(m_sNewText);
         }
      }
      m_ptFoundAt.x += lstrlen(m_sNewText);
      m_bFound = DoHighlightText();
   }
}


/////////////////////////////////////////////////////////////////////////////
// ZFindTextDlg dialog

ZFindTextDlg::ZFindTextDlg(ZCrystalEditView *pBuddy) : CDialog(ZFindTextDlg::IDD, NULL)
{
   m_pBuddy = pBuddy;
   //{{AFX_DATA_INIT(ZFindTextDlg)
   m_nDirection = 1;
   m_bMatchCase = FALSE;
   m_bWholeWord = FALSE;
   m_sText = _T("");
   //}}AFX_DATA_INIT
   m_ptCurrentPos = CPoint(0, 0);
}


void ZFindTextDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ZFindTextDlg)
   DDX_Radio(pDX, IDC_EDIT_DIRECTION_UP, m_nDirection);
   DDX_Check(pDX, IDC_EDIT_MATCH_CASE, m_bMatchCase);
   DDX_Text(pDX, IDC_EDIT_TEXT, m_sText);
   DDX_Check(pDX, IDC_EDIT_WHOLE_WORD, m_bWholeWord);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZFindTextDlg, CDialog)
   //{{AFX_MSG_MAP(ZFindTextDlg)
   ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZFindTextDlg message handlers

void ZFindTextDlg::OnOK()
{
   if (UpdateData())
   {
      ASSERT(m_pBuddy != NULL);
      DWORD dwSearchFlags = 0;
      if (m_bMatchCase)
         dwSearchFlags |= FIND_MATCH_CASE;
      if (m_bWholeWord)
         dwSearchFlags |= FIND_WHOLE_WORD;
      if (m_nDirection == 0)
         dwSearchFlags |= FIND_DIRECTION_UP;

      CPoint ptTextPos;
      if (! m_pBuddy->FindText(m_sText, m_ptCurrentPos, dwSearchFlags, TRUE, &ptTextPos))
      {
         CString prompt;
         prompt.Format(IDS_EDIT_TEXT_NOT_FOUND, m_sText);
         AfxMessageBox(prompt);
         m_ptCurrentPos = CPoint(0, 0);
         return;
      }

      m_pBuddy->HighlightText(ptTextPos, lstrlen(m_sText));

      CDialog::OnOK();
   }
}

void ZFindTextDlg::OnChangeEditText()
{
   CString text;
   GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(text);
   GetDlgItem(IDOK)->EnableWindow(text != _T(""));
}

BOOL ZFindTextDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   GetDlgItem(IDOK)->EnableWindow(m_sText != _T(""));

   return TRUE;
}

void ZFindTextDlg::OnCancel()
{
   VERIFY(UpdateData());

   CDialog::OnCancel();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

AFX_EXT_API
CWnd * OPERATION
EditorControl( ZSubtask *pZSubtask,
               CWnd     *pWndParent,
               ZMapAct  *pzmaComposite,
               zVIEW    vDialog,
               zSHORT   nOffsetX,
               zSHORT   nOffsetY,
               zKZWDLGXO_Ctrl_DEF *pCtrlDef )
{
   return( new ZCrystalEditView( pZSubtask, pWndParent,
                                 pzmaComposite, vDialog,
                                 nOffsetX, nOffsetY, pCtrlDef ) );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
extern "C"
{

#define EDIT_CONTROL_NAME    "_ZeidonEditor"

zOPER_EXPORT zBOOL OPERATION
EDT_CanCopy( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal && pED_Crystal->IsSelection() )
      {
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_CanCopy ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_CanPaste( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal && pED_Crystal->CanPaste() )
      {
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_CanPaste ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_CanRedo( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal && pED_Crystal->CanRedo() )
      {
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_CanRedo ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_CanUndo( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal && pED_Crystal->CanUndo() )
      {
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_CanUndo ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_Undo( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->Undo();
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_Undo ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_Redo( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->Redo();
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_Redo ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_CopyText( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->Copy();
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_CopyText ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_CutText( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->Cut();
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_CutText ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_DeleteText( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->Delete();
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_DeleteText ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_DeleteTextRange( zVIEW vSubtask, zLONG lStartLine, zLONG lStartCol, zLONG lEndLine, zLONG lEndCol )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->m_pTextBuffer->DeleteText(pED_Crystal,lStartLine, lStartCol, lEndLine, lEndCol, CE_ACTION_DELETE);
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_DeleteTextRange ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_Deselect( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->DeleteCurrentSelection();
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_Deselect ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_FindTextPosition( zVIEW vSubtask, zCPCHAR cpcFind, zPLONG lLine, zPLONG lCol, zLONG lFlags )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CPoint ptCursorPos = pED_Crystal->GetCursorPos();
         *lLine = ptCursorPos.y;
         *lCol = ptCursorPos.x;
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_FindTextPosition ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zSHORT OPERATION
EDT_GetActualTextLine( zVIEW vSubtask, zPCHAR pchCurrentLine, zLONG lMaxLth )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CString text;
         CPoint ptCursorPos = pED_Crystal->GetCursorPos();
         pED_Crystal->m_pTextBuffer->GetText(ptCursorPos.y, 0, ptCursorPos.y, pED_Crystal->m_pTextBuffer->GetLineLength( ptCursorPos.y ), text);
         strcpy_s( pchCurrentLine, lMaxLth, text );
         return( text.GetLength() );
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetActualTextLine ", EDIT_CONTROL_NAME );
   }
   return( 0 );
}

zOPER_EXPORT zBOOL OPERATION
EDT_GetCursorPosition( zVIEW vSubtask, zPLONG plLine, zPLONG plCol )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CPoint ptCursorPos = pED_Crystal->GetCursorPos();
         *plCol = ptCursorPos.x;
         *plLine = ptCursorPos.y;
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetCursorPosition ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zLONG OPERATION
EDT_GetLineCount( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         return pED_Crystal->GetLineCount();
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetLineCount ", EDIT_CONTROL_NAME );
   }
   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
EDT_GetLineLength( zVIEW vSubtask, zLONG lLine )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         return pED_Crystal->m_pTextBuffer->GetLineLength( lLine );
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetLineLength ", EDIT_CONTROL_NAME );
   }
   return( 0 );
}

zOPER_EXPORT zBOOL OPERATION
EDT_CloseObject( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
      // return pED_Crystal->CloseObject();  not yet implemented
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_CloseObject ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_CloseSubWindow( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
      // return pED_Crystal->CloseSubWindow();  not yet implemented
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_CloseSubWindow ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_GetObjectName( zVIEW vSubtask, zPCHAR pchFileName, zLONG lMaxLth )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CString csFileName = pED_Crystal->m_pTextBuffer->GetFileName();
         strcpy_s( pchFileName, lMaxLth, csFileName );
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetObjectName ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_GetPositionByIndex( zVIEW vSubtask, zPLONG plLine, zPLONG plColumn )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
      // return pED_Crystal->EDT_GetPositionByIndex;   not yet implemented
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetPositionByIndex ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_GetSelectedText( zVIEW vSubtask, zPCHAR pchText, zLONG lMaxLth )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CPoint ptSelStart, ptSelEnd;
         CString text;
         pED_Crystal->GetSelection(ptSelStart, ptSelEnd);
         pED_Crystal->GetText(ptSelStart, ptSelEnd, text);
         strcpy_s( pchText, lMaxLth, text );
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetSelectedText ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_GetTextFromLineOfIndex( zVIEW vSubtask, zPCHAR pchBuffer, zLONG lMaxLth, zLONG lIndex )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
      // return pED_Crystal->EDT_GetTextFromLineOfIndex();    not yet implemented
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetTextFromLineOfIndex ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zLONG OPERATION
EDT_GetTextFromRange( zVIEW vSubtask, zPCHAR pchBuffer, zLONG lMaxLth, zLONG lStartLine, zLONG lStartCol, zLONG lEndLine, zLONG lEndCol )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CString text;
         pED_Crystal->m_pTextBuffer->GetText(lStartLine, lStartCol, lEndLine, lEndCol, text);
         if ( text.GetLength() >= lMaxLth )
            text.GetBufferSetLength( lMaxLth - 1 );
         strcpy_s( pchBuffer, lMaxLth, text );
         return text.GetLength();
      }

      TraceLineS( "drvr - Invalid control type for EDT_GetTextFromRange ", EDIT_CONTROL_NAME );
   }
   return( 0 );
}

zOPER_EXPORT zBOOL OPERATION
EDT_GotoWindow( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
      // return pED_Crystal->EDT_GotoWindow();  not yet implemented
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_GotoWindow ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_InsertItem( zVIEW vSubtask, zCPCHAR cpcInsertText )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         int x;
         int y;
         CPoint ptCursorPos = pED_Crystal->GetCursorPos();
         pED_Crystal->m_pTextBuffer->InsertText(pED_Crystal, ptCursorPos.y, ptCursorPos.x, cpcInsertText, y, x, CE_ACTION_TYPING);
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_InsertItem ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_IsCommentAtIndex( zVIEW vSubtask, zLONG lIndex )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
      // return pED_Crystal->EDT_IsCommentAtIndex();   not yet implemented
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_IsCommentAtIndex ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_IsObjectChanged( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal && pED_Crystal->m_pTextBuffer->IsModified() )
      {
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_IsObjectChanged ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_IsReadOnly( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal && pED_Crystal->m_pTextBuffer->GetReadOnly() )
      {
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_IsReadOnly ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_OpenObject( zVIEW vSubtask, zCPCHAR cpcFileName )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->m_pTextBuffer = new ZCrystalTextBuffer();
         return pED_Crystal->m_pTextBuffer->LoadFromFile(cpcFileName);
         pED_Crystal->OnInitialUpdate();
      }

      TraceLineS( "drvr - Invalid control type for EDT_OpenObject ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_PasteText( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->Paste();
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_PasteText ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_PrintObject( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->SendMessage( WM_COMMAND, ID_FILE_PRINT_PREVIEW, 0 );
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_PrintObject ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_PropertyDialog( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->MessageBox( "Property Dialog Not Implemented", "Zeidon Editor", MB_OK );
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_PropertyDialog ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_ReadOnlyMode( zVIEW vSubtask, zBOOL bReadOnly )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal && pED_Crystal->m_pTextBuffer )
      {
         pED_Crystal->m_pTextBuffer->SetReadOnly( bReadOnly ? 1 : 0 );
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_ReadOnlyMode ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_SaveObject( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         return pED_Crystal->m_pTextBuffer->SaveToFile(pED_Crystal->m_pTextBuffer->GetFileName());
      }

      TraceLineS( "drvr - Invalid control type for EDT_SaveObject ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_SaveObjectAs( zVIEW vSubtask, zCPCHAR cpcFileName )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         return pED_Crystal->m_pTextBuffer->SaveToFile(cpcFileName);
      }

      TraceLineS( "drvr - Invalid control type for EDT_SaveObjectAs ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_SelectAll( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         pED_Crystal->SelectAllLines();
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_SelectAll ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_SelectItem( zVIEW vSubtask, zLONG lLine, zLONG lCol, zCPCHAR cpcText )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CPoint pt( 0, lLine );
         CPoint ptReturn;
         return pED_Crystal->FindText(cpcText, pt, 0, FALSE, &ptReturn);
      }

      TraceLineS( "drvr - Invalid control type for EDT_SelectItem ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_SelectRange( zVIEW vSubtask, zLONG lLine, zLONG lCol, zLONG lCharCnt )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CPoint pt( lCol, lLine );
         return pED_Crystal->HighlightText( pt, lCharCnt );
      }

      TraceLineS( "drvr - Invalid control type for EDT_SelectRange ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_SetCursorPositionByLine( zVIEW vSubtask, zLONG lLine, zLONG lReturnedBuffSize )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
         CPoint pt( 0, lLine );
         pED_Crystal->SetCursorPos( pt );
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_SetCursorPositionByLine ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_WantKeystrokes( zVIEW vSubtask, zBOOL bOn )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal  )
      {
      // pED_Crystal->WantKeystrokes( bOn ); not yet implemented
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_WantKeystrokes ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_ZeidonSyntaxOn( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
      // pED_Crystal->EDT_ZeidonSyntaxOn();  // always on for now
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_ZeidonSyntaxOn ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

zOPER_EXPORT zBOOL OPERATION
EDT_SyntaxOff( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME ) == 0 )
   {
      ZCrystalEditView *pED_Crystal = DYNAMIC_DOWNCAST( ZCrystalEditView, pzma->m_pCtrl );
      if ( pED_Crystal )
      {
      // pED_Crystal->EDT_SyntaxOff();  // always on for now
         return( TRUE );
      }

      TraceLineS( "drvr - Invalid control type for EDT_SyntaxOff ", EDIT_CONTROL_NAME );
   }
   return( FALSE );
}

} // end: extern "C"