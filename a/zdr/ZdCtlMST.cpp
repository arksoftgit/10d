/////////////////////////////////////////////////////////////////////////////
// Project ZdCtl
//
// This is a part of the Zeidon Dynamic Rendering of GUI applications package.
// Copyright © 1995 - 2016 QuinSoft, Inc.
// All Rights Reserved.
//
// SUBSYSTEM:    zdctl.dll - ZDr Control implementations
// FILE:         zdctlmst.cpp
// AUTHOR:
//
// OVERVIEW
// ========
// Source file for implementation of Zeidon Tree (hierarchical tree)
// control.

//
// CHANGE LOG - most recent first order
//
// 200y.mm.dd    xxx
//    Note ...
//
// 2003.03.30    DKS    Z10
//    Did a bit of optimization on paint (using memory DC) and forcing
//    repaint of parent window prior to tree control.
//
// 2003.01.08    DKS    Z10
//    On MapFromOI, tried to maintain position on the original view.
//
// 2002.02.04    DKS    Z10
//    Setting code to permit deprecation of ZDCTLTRE.CPP.
//
// 2001.09.24    DKS    Bianca
//    Altered timing of NoteBook Ctrl Mapping.
//
// 2001.08.10    BL
//    ZMSTree::OnLButtonDown, fix for messagebox in SelChanging.
//
// 2001.04.28    BL     TREE
//    Added Parameter bEnsureVisible to SetTextItemColorText and
//    SetTxtItemColorText.
//
// 2001.04.28    BL     TREE
//    If somebody is using the Window Postbuild Event with a Tree Control,
//    the mapping will not be there and the Tree Function does not work.
//    Save Text Color for Tree Item in Array.
//    Added new Function OL_RemoveAllTextColorsForItemText.
//
// 2001.04.25    BL     TREE
//    Added new Function Added SetTextItemColorText.
//
// 2001.04.17    BL     TREE
//    Modified ExpandCollapseAll to improve performance.
//
// 2001.04.12    BL     TREE
//    Bugfix for Expand all and Collapse all for an Entity in a Lod with
//    recursive Entities.
//
// 2001.04.05    BL     TREE
//    Rename Event Right Button Down to Right Button on Item and added
//    Event Right Button on Background.
//
// 2001.03.27    DKS    QS999
//    Deleted images list in OnDestroy method (so tree can be used on
//    a NoteBook control).
//
// 2001.02.28    BL     TREE
//    Modified GetSelectedBitmap and GetDefaultBitmap for Return Bitmap
//    Name Length.
//
// 2001.02.08    BL
//    New Tree Control, implemented new functions.
//
// 2001.01.31    BL
//    Check In for HPF, Test OnPaint (Background and Text Color) for
//    Windows 2000.
//
// 2001.01.03    BL
//    New Tree Control under construction.
//
// 2000.12.27    BL
//    If Design Time load new Blob for Color, Font and Bitmaps
//
// 2000.11.18    BL
//    Completely maintained new Tree Control (ZMS Tree)
//
// 2000.04.26    TMV    Z10
//    Created
//

#include "zstdafx.h"

#define ZDCTL_CLASS AFX_EXT_CLASS
#include "ZDr.h"

#include "ZdCtl.h"
#include "ZdCtlMst.h"
#include "ZdCtlGbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// #define DEBUG_ALL

CString ZMSTree::m_csTreeNodeChildEntity = "TreeNodeTreeNode";
CString ZMSTree::m_csTreeNodeEntity      = "TreeNode";
CString ZMSTree::m_csTreeNodeTagAttr     = "Tag";
CString ZMSTree::m_csTreeNodeTextAttr    = "Text";
CString ZMSTree::m_csTreeSelectionEntity = "TreeSelectedItem";
CString ZMSTree::m_csTreeSelectionTag    = "Tag";
CString ZMSTree::m_csTree                = "Tree";

// Declare event constants corresponding to the PPE.
#define zTREE_EVENT_SELECT_CHANGE       1
#define zTREE_EVENT_DOUBLECLICK         2
#define zTREE_EVENT_EXPANDING           3
#define zTREE_EVENT_COLLAPSING          4
#define zTREE_EVENT_EXPANDED            5
#define zTREE_EVENT_COLLAPSED           6
#define zTREE_EVENT_PRESELECT_CHANGE    7
#define zTREE_EVENT_RBUTTON_ITEM        8
#define zTREE_EVENT_BEGIN_EDITLABEL     9
#define zTREE_EVENT_END_EDITLABEL      10
#define zTREE_EVENT_RBUTTON_BACKGROUND 11

#define zTREE_STATE_UNSELECTED_IMG   1  // one-based index to state image list
#define zTREE_STATE_SELECTED_IMG     2  // see Microsoft doc. using userdefined states

#define zTREE_STATE_CLOSE_IMG        0
#define zTREE_STATE_OPEN_IMG         1

#define zTREE_BitmapHeight           16
#define zTREE_BitmapWidth            16;

#define zTREE_Tag_ForDesignTime      "__Bootstrap"
#define zTREE_COLOR_GRAY             12632256

IMPLEMENT_DYNAMIC( ZOL_Node, CObject)
IMPLEMENT_DYNAMIC( ZMSTree, CTreeCtrl )

BEGIN_MESSAGE_MAP( ZMSTree, CTreeCtrl )
   //{{AFX_MSG_MAP(ZMSTree)
   ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
   ON_NOTIFY_REFLECT(NM_OUTOFMEMORY, OnOutOfMemory)
   ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
   ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
   ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
   ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginLabelEdit)
   ON_NOTIFY_REFLECT(TVN_BEGINRDRAG, OnBeginrdrag)
   ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteItem)
   ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
   ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
   ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
   ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
   ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelChanging)
   //}}AFX_MSG_MAP
   ON_WM_KILLFOCUS( )
   ON_WM_SETFOCUS( )
   ON_WM_CREATE( )
   ON_WM_LBUTTONDOWN( )
   ON_WM_RBUTTONDOWN( )
   ON_WM_KEYDOWN( )
   ON_WM_ERASEBKGND( )
   ON_WM_NCPAINT( )
   ON_WM_PAINT( )
   ON_WM_HSCROLL( )
   ON_WM_VSCROLL( )
END_MESSAGE_MAP( )

#define zTREE_SETFOCUS              zMAPACT_CTRL_SPECIFIC5
#define zTREE_RECURSIVESELCHANGE    zMAPACT_CTRL_SPECIFIC6
#define zTREE_RECURSIVESELECTPOS    zMAPACT_CTRL_SPECIFIC7

// Class ZOL_Node represents a node of a tree.
// It handles mapping information as well as structure information.
ZOL_Node::ZOL_Node( )
{
   Init( );
}

ZOL_Node::ZOL_Node( ZOL_Node *pNodeParent,
                    zCPCHAR  cpcEntityName )
{
   Init( );
   m_csEntityName = cpcEntityName;
// m_chChildren = zTREE_CHILDREN_NONE;
   SetParent( pNodeParent );
}

ZOL_Node::~ZOL_Node( )
{
   DeleteChildNodes( );   // remove all child nodes
}

void
ZOL_Node::Init( )
{
// m_csEntityName         = "";
// m_csAttributeName      = "";
// m_csContextName        = "";
// m_csDefaultBitmapFile  = "";
// m_csSelectedBitmapFile = "";
   m_bSelected            = FALSE;
   m_chChildren           = 0;
// m_bOpen                = FALSE;
   m_hAttributes          = 0;
// m_hEntityInstance      = 0;
   m_hItem                = 0;
   m_pParent              = 0;
   m_ulEntityKey          = 0;
   m_TextColor            = 0;
   m_lUseDefaultBitmap    = 0;
   m_lUseSelectedBitmap   = 0;
}

// Counts nodes that are ancestors.
zSHORT
ZOL_Node::GetNodeLevel( )
{
   zSHORT nNode = 0;
   ZOL_Node *pNode = this;
   ZOL_Node *pParent;

   for ( pParent = pNode->GetParent( ); pParent; nNode++ )
   {
   }

   return( nNode );
}

void
ZOL_Node::DeleteChildNodes( )
{
   ZOL_Node *pNode;

   while ( m_olChildren.IsEmpty( ) == FALSE )
   {
      pNode = (ZOL_Node *) m_olChildren.RemoveHead( );
      delete( pNode );
   }
}

void
ZOL_Node::SetParent( ZOL_Node *pParent )
{
   m_pParent = pParent;

   if ( m_pParent )
      m_pParent->AttachChild( this );
}

void
ZOL_Node::AttachChild( ZOL_Node *pChild )
{
   m_olChildren.AddTail( pChild );
}

void
ZOL_Node::DetachChild( ZOL_Node *pChild )
{
   POSITION pos = m_olChildren.Find( pChild );

   if ( pos )
      m_olChildren.RemoveAt( pos );
}

// To retrieve the values of all mapped attributes of the current entity
// separated by cDelimiter (default is \t).
CString
ZOL_Node::GetValues( zCHAR cDelimiter )
{
   CString csText;
   POSITION pos = m_cslValues.GetHeadPosition( );
   int k = 0;       // what is this int used for???

   while ( pos )
   {
      if ( k > 0 )  // something's fishy???
         csText += cDelimiter;

      csText += m_cslValues.GetNext( pos );
   }

   return( csText );
}

// To get only a specific attribute value of current entity.
CString
ZOL_Node::GetValue( int lPos )
{
   CString csText;

   csText.Empty( );

   if ( lPos >= 0 )
   {
      POSITION pos = m_cslValues.FindIndex( lPos );
      if ( pos )
         csText = m_cslValues.GetAt( pos );
   }

   return( csText );
}

// To set only a specific attribute value of current entity.
void
ZOL_Node::SetValue( CString csValue, int lPos )
{
   if ( lPos >= 0 )
   {
      POSITION pos = m_cslValues.FindIndex( lPos );
      if ( pos )
         m_cslValues.SetAt( pos, csValue );
   }
}

// Recursively check all nodes against its absolute
// position and return the match.
ZOL_Node *
ZOL_Node::FindNodeByEntityKey( zULONG ulKey )
{
#if 1

   if ( m_ulEntityKey == ulKey )
      return( this );

   ZOL_Node *pNode = 0;
   POSITION pos = GetFirstChildPosition( );
   while ( pos && pNode == 0 )
   {
      ZOL_Node *p = this->GetNextChild( pos );
      pNode = p->FindNodeByEntityKey( ulKey );
   }

   return( pNode );

#else

   ZOL_Node *pReturn = 0;

   if ( m_ulEntityKey == ulKey )
      pReturn = this;
   else
   {
      ZOL_Node *pNode = 0;

      POSITION pos = GetFirstChildPosition( );
      while ( pos && pNode == 0 )
      {
         ZOL_Node *p = this->GetNextChild( pos );
         pNode = p->FindNodeByEntityKey( ulKey );
      }

      pReturn = pNode;
   }

   return( pReturn );

#endif
}

ZOL_Node *
ZOL_Node::FindNodeByRelativePosition( zULONG ulKey, zCPCHAR cpcEntityName )
{
#if 1

   ZOL_Node *pReturn = FindNodeByEntityKey( ulKey );
// ASSERT( pReturn == 0 || pReturn->m_csEntityName == cpcEntityName );
   return( pReturn );

#else

   ZOL_Node *pReturn = 0;

   if ( m_ulEntityKey == ulKey && m_csEntityName == cpcEntityName )
      pReturn = this;
   else
   {
      ZOL_Node *pNode = 0;

      POSITION pos = GetFirstChildPosition( );
      while ( pos && pNode == 0 )
      {
         ZOL_Node *p = this->GetNextChild( pos );
         pNode = p->FindNodeByRelativePosition( ulKey, cpcEntityName );
      }

      pReturn = pNode;
   }

   return( pReturn );

#endif
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// SetItemState expects a state value and a state mask:
//
// UINT SetItemState( HTREEITEM hItem,        // Item to modify
//                    UINT      nState,       // New state value
//                    UINT      nStateMask ); // Which bits of nState to use
//
// The mask tells SetItemState which state flags you want to set. For example,
// TVIS_SELECTED indicates the selection state andTVIS_FOCUSED indicates the
// focus state. The state value contains the actual bit values for the flags
// specified in the mask. This is where people sometimes get into trouble.
// You might try writing:
//
//      SetItemState( hItem, TRUE, TVIS_SELECTED );
//
// to set the selection state on. If so, you would then beat your
// head against the wall trying to figure out why it doesn't work. The
// problem is that TRUE has value 0x0001, which does not coincide with
// TVIS_SELECTED. The nState parameter is a bitfield, not a Boolean value.
// Every bit of nState matters. The correct way to select an item (turn on
// the TVIS_SELECTED bit) is:
//
//      SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
//
// To turn the bits off, use
//
//      SetItemState( hItem, 0, TVIS_SELECTED );
//
// Code calls SetItemState to change the TVIS_SELECTED state, but call
// CTreeCtrl::SelectItem to set the focus item because that's the easiest
// (and most future-compatible) way.
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

ZMSTree::ZMSTree( ZSubtask *pZSubtask,
                  CWnd     *pWndParent,
                  ZMapAct  *pzmaComposite,
                  zVIEW    vDialog,
                  zSHORT   nOffsetX,
                  zSHORT   nOffsetY,
                  zKZWDLGXO_Ctrl_DEF *pCtrlDef ) :
         CTreeCtrl( ),
         ZMapAct( pZSubtask,            // base class ctor
                  pzmaComposite,
                  pWndParent,
                  this,
                  vDialog,
                  nOffsetX,
                  nOffsetY,
                  pCtrlDef,
                  "Tree" )
{
#ifdef DEBUG_ALL
   TraceLineI( "In ctor for ZMSTree", (zLONG) this );
   TraceLineS( "ZMSTree::ctor ", *m_pzsTag );
#endif

   m_vApp                     = 0;
// m_csLabelEditOldValue      = "";
// m_csExpandingEntity        = "";
// m_csCollapsingEntity       = "";
// m_csLastExpandedEntity     = "";
// m_csLastCollapsedEntity    = "";
   m_csTreeViewName           = "_";
   m_pchCtrlBOI               = 0;
   m_pchFontColorBitmapBlob   = 0;
   m_lFontColorBitmapBlobSize = 0;
   m_pRootEntry               = 0;
   m_nType                    = -1;
   m_dwStyle                  = 0;
   m_bPreSelectChangeAlreadyDone = FALSE;
   m_bExpandInMapFromOI       = FALSE;
   m_bCreateTree              = TRUE;
   m_bSetMultiSelection       = FALSE;
   m_bLabelEdit               = FALSE;
   m_bLabelEditESC            = FALSE;
   m_bLabelEditRemoveFlag     = FALSE;
   m_bFontColor               = FALSE;
   m_lLabelEditTextLth        = 0;
   m_clrBackground            = -1;
   m_clrBackgroundOld         = -1;
   m_lBitmapHeight            = zTREE_BitmapHeight;
   m_lBitmapWidth             = zTREE_BitmapWidth;
   m_clrItemBk                = ::GetSysColor( COLOR_HIGHLIGHT );
   m_pBitmap1 = 0;
   m_pBitmap2 = 0;
   m_ulKeyLast = 0;
   m_hDIB = 0;

   m_szLastAccEntity[ 0 ] = 0;

   mDeleteInit( m_pzsText );
   m_pzsText = new CString( pCtrlDef->Text );
   strcpy_s( m_szClass, zsizeof( m_szClass ), "ZeidonOL" );

   // DM - Commenting out unneeded stuff assuming that there is no subtype.
   Attr.Style = WS_CHILD;

   if ( pCtrlDef->Subtype & zCONTROL_SIZEABLEBORDER )
      Attr.Style |= WS_THICKFRAME;
   else
   if ( (pCtrlDef->Subtype & zCONTROL_BORDEROFF) == 0 )
      Attr.Style |= WS_BORDER;

   if ( (pCtrlDef->Subtype & zCONTROL_NOTABSTOP) == 0 )
      Attr.Style |= WS_TABSTOP;

   if ( (pCtrlDef->Subtype & zCONTROL_INVISIBLE) == 0 )
      Attr.Style |= WS_VISIBLE;

   if ( pCtrlDef->Subtype & zTREES_MULTISEL )
      Attr.Style |= zTREES_MULTISEL;
   else
   if ( pCtrlDef->Subtype & zTREES_SINGLEEXPAND )
      m_dwStyle |= TVS_SINGLEEXPAND;
   else
      m_dwStyle &= ~TVS_SINGLEEXPAND;

   if ( pCtrlDef->Subtype & zTREES_OPENALLCHILDREN )
      Attr.Style |= zTREES_OPENALLCHILDREN;
   else
      Attr.Style |= zTREES_OPENROOTCHILDREN;

   if ( pCtrlDef->Subtype & zTREES_NOSHOW_ENTITY )
      Attr.Style |= zTREES_NOSHOW_ENTITY;

   m_lStyle = Attr.Style;

   if ( pCtrlDef->Subtype & zCONTROLX_DISABLE_READONLY )
      m_dwStyle &= ~TVS_EDITLABELS;
   else
      m_dwStyle |= TVS_EDITLABELS;

   if ( pCtrlDef->Subtype & zTREES_HASBUTTONS )
      m_dwStyle |= TVS_HASBUTTONS;

   if ( pCtrlDef->Subtype & zTREES_HASLINES )
      m_dwStyle |= TVS_HASLINES;

   if ( pCtrlDef->Subtype & zTREES_LINESATROOT )
      m_dwStyle |= TVS_LINESATROOT;

   if ( pCtrlDef->Subtype & zTREES_NOBITMAPS )
      m_bNoImage = TRUE;
   else
      m_bNoImage = FALSE;

   // Set Background Color, Text Color, Text Font and Bitmaps.
   GetColorFontBitmap( vDialog );

   zULONG ulLth = 0;

   GetAttributeLength( &ulLth, vDialog, szlCtrl, szlCtrlBOI );
   if ( ulLth == 0 )
      return;

   m_pchCtrlBOI = new char[ ulLth ];
   GetBlobFromAttribute( m_pchCtrlBOI, &ulLth, vDialog, szlCtrl, szlCtrlBOI );

   // Stuff in the view to the current (runtime) Dialog ... note that
   // vDialog is giving us current position within the Dialog, but it is not
   // guaranteed to exist (since it is only used for positioning and since
   // sub-controls may move position, etc., a non-persistent view may be
   // passed to sub-controls).  Therefore, we use the view from the Subtask
   // (which is guaranteed to persist as long as the subtask exists).

   *((zVIEW *) m_pchCtrlBOI) = pZSubtask->m_vDialog;
   m_vSubtask = pZSubtask->m_vDialog;

   zPCHAR pch = m_pchCtrlBOI + sizeof( zVIEW ); // skip Dialog view

   // Skip past the operation and DLL name if they are specified.
   if ( pch[ 0 ] )
   {
      pch += zstrlen( pch ) + 1;
      pch += zstrlen( pch ) + 1;
   }
   else
      pch++;

   m_csAppViewName = pch;  // this is the view name

   // Setup a unique view name to be traversed by the tree.
   m_csTreeViewName = "__" + m_csAppViewName;

   // Get recursive view.
   pch += m_csAppViewName.GetLength( ) + 1;  // skip past bottom view name
   if ( *pch )
   {
      m_csRecursiveView = pch;
      pch += m_csRecursiveView.GetLength( ) + 1;  // skip past top view name
   }
   else
   {
      m_csRecursiveView = m_csAppViewName + ".PreRecurse";
      pch++;    // skip past (absent) top view name
   }

   // Tree type 0 ==> MultiRoot ... 1 ==> SingleRoot
   // If m_nType is 0, then a root tree entity is created that displays
   // the tree text.  If m_nType is 1, then the tree just starts
   // with the first view entity.
   m_nType = (zSHORT) *((zPLONG) pch);

   pch += sizeof( zLONG ); // now pointing to tree text
   m_csTreeText = pch;
   pch += m_csTreeText.GetLength( ) + 1;

   // pch is now pointing to the first entity item struct.
   m_nFirstEntityOffset = pch - m_pchCtrlBOI;

   if ( m_bNoImage == FALSE )
   {
      HINSTANCE hInst = AfxGetResourceHandle( );
      AfxSetResourceHandle( g_hInstanceDLL );

      if ( IsDesignTime( FALSE ) )
      {
         if ( m_ImageList.Create( m_lBitmapWidth, m_lBitmapHeight, ILC_MASK, 3, 3 ) )
         {
            m_ImageList.Add( AfxGetApp( )->LoadIcon( IDI_FOLDERCLOSE ) );
            m_ImageList.Add( AfxGetApp( )->LoadIcon( IDI_FOLDEROPEN ) );
            m_ImageList.Add( AfxGetApp( )->LoadIcon( IDI_FOLDERSELECT ) );
         }
      }
      else
      {
         if ( m_ImageList.Create( m_lBitmapWidth, m_lBitmapHeight,
                                  ILC_MASK, 2, 2 ) )
         {
            m_ImageList.Add( AfxGetApp( )->LoadIcon( IDI_FOLDERCLOSE ) );
            m_ImageList.Add( AfxGetApp( )->LoadIcon( IDI_FOLDEROPEN ) );
         }
      }

      AfxSetResourceHandle( hInst );
   }

#ifndef zREMOTE_SERVER
   if ( pzmaComposite == 0 ||
        (pzmaComposite->m_ulMapActFlag2 & zMAPACT_CREATE_CHILDREN) )
#endif
   {
      CreateZ( );
   }
}

void
TreeCursorListener( zVIEW pView,
                    zCPCHAR cpcEntityName,
                    zPVOID pvInstance )
{
   ((ZMSTree *) pvInstance)->CursorListener( pView, cpcEntityName );
}

void
ZMSTree::CursorListener( zVIEW pView, zCPCHAR cpcEntityName )
{
   if ( cpcEntityName && pView == m_vApp && IsMappedEntity( cpcEntityName ) )
      strncpy_s( m_szLastAccEntity, zsizeof( m_szLastAccEntity ), cpcEntityName, zsizeof( m_szLastAccEntity ) - 1 );
}

ZMSTree::~ZMSTree( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::dtor", *m_pzsTag );
#endif
   if ( MiValidView( m_vApp ) )
      RemoveCursorListener( m_vApp, TreeCursorListener, this );

   mDeleteInit( m_pBitmap1 );
   mDeleteInit( m_pBitmap2 );
   mDeleteInitA( m_pchCtrlBOI );
   mDeleteInit( m_pRootEntry );
   m_arrItemColorText.RemoveAll( );

   // Delete ImageList.
   if ( m_ImageList )
      m_ImageList.DeleteImageList( );

   mDeleteInitA( m_pchFontColorBitmapBlob );
}

int
ZMSTree::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnCreate ", *m_pzsTag );
#endif

   int nRC = (int) Default( );
   if ( nRC == -1 )
      return( -1 );

   m_ulMapActFlag2 |= zMAPACT_CREATE_CHILDREN | zMAPACT_CREATED1;

   SetWindowText( *m_pzsText );
   SetFontOverride( );
   ModifyStyleEx( 0, WS_EX_NOPARENTNOTIFY );    // | WS_EX_CLIENTEDGE );

   if ( m_bNoImage == FALSE )
   {
      if ( IsDesignTime( ) )
         SetImageList( &m_ImageList, TVSIL_STATE );
      else
         SetImageList( &m_ImageList, TVSIL_NORMAL );
   }

   return( nRC );
}

BOOL
ZMSTree::DestroyWindow( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::DestroyWindow ", *m_pzsTag );
#endif

   // Delete ImageList
// if ( m_ImageList )
//    m_ImageList.DeleteImageList( );

   mDeleteInit( m_pRootEntry );
   m_ulMapActFlag2 &= ~(zMAPACT_MAPPED_FROM_OI |
                        zMAPACT_CREATE_CHILDREN | zMAPACT_CREATED);
   return( CTreeCtrl::DestroyWindow( ) );
}

void
ZMSTree::CreateZ( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::CreateZ", *m_pzsTag );
#endif
   m_dwStyle |= WS_BORDER | TVS_SHOWSELALWAYS | TVS_NOTOOLTIPS | TVS_DISABLEDRAGDROP | TVS_LINESATROOT;

   if ( m_ulMapActFlags & zMAPACT_VISIBLE )
      m_dwStyle |= WS_VISIBLE;
   else
      m_dwStyle &= ~WS_VISIBLE;

   if ( m_ulMapActFlags & zMAPACT_ENABLED )
      m_dwStyle &= ~WS_DISABLED;
   else
      m_dwStyle |= WS_DISABLED;

   CRect rect( Attr.X, Attr.Y, Attr.X + Attr.W, Attr.Y + Attr.H );

#ifdef zREMOTE_SERVER
   m_ulMapActFlag2 |= zMAPACT_CREATE_CHILDREN | zMAPACT_CREATED1;
#else
   if ( mIs_hWnd( m_hWnd ) == 0 && mIs_hWnd( m_pWndParent->m_hWnd ) )
   {
      Create( m_dwStyle, rect, m_pWndParent, 1 );
      // We may have to add some code to load images from a different location.
   }
#endif
}

zSHORT
ZMSTree::MapFromOI( WPARAM wFlag )
{
   zVIEW vApp;

#ifdef DEBUG_ALL

// if ( zstrcmp( *m_pzsTag, "OLCPList" ) == 0 )
      TraceLine( "ZMSTree::MapFromOI %s       View: %s   Entity: %s",
                 *m_pzsTag, m_csAppViewName, *m_pzsEName );

   if ( GetViewByName( &vApp, m_csAppViewName, m_vSubtask, zLEVEL_ANY ) <= 0 )
      vApp = m_vApp;

   if ( vApp )
      DisplayEntityInstance( vApp, *m_pzsEName );
#endif

   // If the control is not Visible, do not do mapping.
   if ( IsVisibleForMapFromOI( ) == FALSE )
      return( 0 );

   GetViewByName( &vApp, m_csAppViewName,
                  m_pZSubtask->m_vDialog, zLEVEL_ANY );
   // The outliner view in the painter that displays the views takes a long
   // time to rebuild. If the vApp and m_vApp are the same and the
   // outliner we are rebuilding is TZZOVEAO, then don't rebuild.
   // This always rebuilds when opening a dialog, just not when drilling down
   // for a control or window properties and then coming back.
   // KJS 06/29/17 - change.
   if (vApp == m_vApp && m_csAppViewName == "TZZOVEAO")
   {
      // KJS 11/28/16 - Trying not to rebuild every time.
      return (0);
   }
   else
   {
      m_szLastAccEntity[0] = 0;
      m_vApp = vApp;
   }

// TraceLineS( "ZMSTree::MapFromOI ", *m_pzsTag );
   zULONG ulTopEntityKey = 0;

// CWaitRedraw wd;  this is too much
   SetRedraw( FALSE );
   zLONG lCount = -1;
   m_ulMapActFlag2 |= zMAPACT_MAPPING_FROM_OI;
   m_ulKeyLast = 0;

   // Save the last current Entity.
   if ( IsDesignTime( ) )
      SaveCurrentEntity( );
   else
   if ( m_szLastAccEntity[ 0 ] )
   {
      if ( m_vApp == 0 ||
           (m_vApp &&
            SetCursorFirstSelectedEntity( m_vApp, m_szLastAccEntity,
                                          zSCOPE_OI ) < zCURSOR_SET) )
      {
         m_szLastAccEntity[ 0 ] = 0;
      }
   }

   // Create Array to save current Expand State.
   CArray <zULONG, zULONG> hOpenEntityKey;
   if ( m_pRootEntry )
      ulTopEntityKey = SaveExpandState( hOpenEntityKey );
   else
      lCount = 0;

#ifndef zREMOTE_SERVER
   SelectItem( 0 );    // turn off selections prior to deleting all items
   DeleteAllItems( );
// DisplayEntityInstance( m_vApp, *m_pzsEName );
#endif

   // This must be after DeleteAllItems since DeleteAllItems causes
   // an OnSelChanging event (if an item is selected).
   if ( m_pRootEntry )
   {
      ZOL_Node *pRootEntry = m_pRootEntry;
      m_pRootEntry = 0;
      delete( pRootEntry );
   }

   m_csRecursiveView.Empty( );

   m_ulMapActFlag2 |= zMAPACT_MAPPED_FROM_OI1;

   if ( m_pchCtrlBOI )
   {
      // MapTreeFromOI maps all the instance data into the tree.
      if ( MapTreeFromOI( ) < 0 )
      {
         SetRedraw( TRUE );
         m_ulMapActFlag2 &= ~zMAPACT_MAPPING_FROM_OI;
         return( TRUE );
      }

      // If Design Time, load new Blob for Color, Font and Bitmaps.
      if ( IsDesignTime( ) )
      {
         zVIEW  vSubtask;
         CreateViewFromViewForTask( &vSubtask, m_vSubtask,
                                    m_pZSubtask->m_vDialog );
         if ( SetCursorFirstEntityByString( vSubtask, szlCtrl, "Tag",
                                            zTREE_Tag_ForDesignTime, "" )
                                            >= zCURSOR_SET )
         {
            GetColorFontBitmap( vSubtask );
         }

         DropView( vSubtask );
      }

      // If View is read only, set Gray for Background Color.
      if ( m_vApp && MiGetUpdateForView( m_vApp ) <= 0 )
         SetBackgroundColor( zTREE_COLOR_GRAY );

      PopulateTree( );

      if ( hOpenEntityKey.GetSize( ) > 0 )
         lCount = SetExpandState( hOpenEntityKey, ulTopEntityKey );

      if ( lCount == 0 && m_lStyle & zTREES_OPENALLCHILDREN )
         ExpandCollapseAll( 0, TVE_EXPAND );

      SetAllTextColorsForItemText( );
   }

   HTREEITEM hItem = SelectCurrentEntity( ); // moved from after SetRedraw (dks)

   if ( m_pRootEntry && ulTopEntityKey )
   {
      ZOL_Node *pNode = m_pRootEntry->FindNodeByEntityKey( ulTopEntityKey );
      if ( pNode && pNode->m_hItem )
      {
         Select( pNode->m_hItem, TVGN_FIRSTVISIBLE );

      // CString csItemText = GetItemText( pNode->m_hItem );
      // TraceLine( "ZMSTree::MapFromOI selecting first visible item: 0x%08x       Key: %d   Entity: %s   Text: %s",
      //            pNode->m_hItem, pNode->m_ulEntityKey, pNode->m_csEntityName, csItemText );
      }
   }

// if ( hItem )
//    Select( hItem, TVGN_CARET );
   if ( hItem )            // this is prior to taking out the MAPPING bit
      SelectItem( hItem ); // below to prevent OnSelChanging and
                           // OnSelChanged! /// dks 2003/10/20

   m_ulMapActFlag2 &= ~zMAPACT_MAPPING_FROM_OI;
   SetRedraw( TRUE );
   GetParent( )->UpdateWindow( ); // this is necessary to keep the tree
                                  // control from being drawn before its
                                  // parent /// dks 2003/01/30
// ListAllItems( " =================> MapFromOI" );
   return( 0 );
}

zSHORT
ZMSTree::PostMapFromOI( WPARAM wFlag )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::PostMapFromOI ", *m_pzsTag );
#endif

   return( 0 );
}

zSHORT
ZMSTree::MapToOI( zLONG lFlag )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::MapToOI ", *m_pzsTag );
#endif

   // If the control is not Visible and Enabled, do not do mapping.
   if ( IsVisibleForMapToOI( ) == 0 )  // note ... don't check view name here!
      return( 0 );

#ifdef zREMOTE_SERVER
   // Handle state information is all we can do.
   HandleRemoteState( );
#endif
   return( 0 );
}

void
ZMSTree::SetItemFont( HTREEITEM hItem, LOGFONT& logfont )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::SetItemFont", *m_pzsTag );
#endif
   ItemColorFontImage cfi;

   if ( m_mapItemColorFontImage.Lookup( hItem, cfi ) == 0 )
   {
      cfi.color = CLR_INVALID;
      cfi.lImageListIdx = -1;  // invalid image index
      cfi.csBitmapFile.Empty( );
   }

   cfi.logfont = logfont;
   m_mapItemColorFontImage[ hItem ] = cfi;
   if ( logfont.lfFaceName[ 0 ] )
      m_bFontColor = TRUE;
}

void
ZMSTree::SetItemBold( HTREEITEM hItem, BOOL bBold )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::SetItemBold", *m_pzsTag );
#endif
   SetItemState( hItem, bBold ? TVIS_BOLD : 0, TVIS_BOLD );
   if ( bBold )
      m_bFontColor = TRUE;
}

void
ZMSTree::SetItemColor( HTREEITEM hItem, COLORREF clrFont )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::SetItemColor", *m_pzsTag );
#endif
   ItemColorFontImage cfi;

   if ( m_mapItemColorFontImage.Lookup( hItem, cfi ) == 0 )
   {
      cfi.logfont.lfFaceName[ 0 ] = 0;
      cfi.lImageListIdx = -1;  // invalid image index
      cfi.csBitmapFile.Empty( );
   }

   cfi.color = clrFont;
   m_mapItemColorFontImage[ hItem ] = cfi;
   if ( clrFont && clrFont != CLR_INVALID )
      m_bFontColor = TRUE;
}

zBOOL
ZMSTree::GetItemFont( HTREEITEM hItem, LOGFONT *plogfont )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetItemFont", *m_pzsTag );
#endif
   ItemColorFontImage cfi;

   if ( m_mapItemColorFontImage.Lookup( hItem, cfi ) == 0 )
      return( FALSE );

   if ( cfi.logfont.lfFaceName[ 0 ] == 0 )
      return( FALSE );

   *plogfont = cfi.logfont;

   return( TRUE );
}

zBOOL
ZMSTree::GetItemBold( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetItemBold", *m_pzsTag );
#endif
   return( GetItemState( hItem, TVIS_BOLD ) & TVIS_BOLD );
}

COLORREF
ZMSTree::GetItemColor( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetItemColor", *m_pzsTag );
#endif
   // Returns CLR_INVALID if color was not set.
   ItemColorFontImage cfi;

   if ( m_mapItemColorFontImage.Lookup( hItem, cfi ) )
      return( cfi.color );
   else
      return( CLR_INVALID );
}

void
ZMSTree::GetColorFontBitmap( zVIEW vDialog )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetColorFontBitmap", *m_pzsTag );
#endif
   zULONG ulLth = 0;

   m_lFontColorBitmapBlobSize = 0;
   GetAttributeLength( &ulLth, vDialog, szlCtrl, szlProperties );

   if ( ulLth > 0 )
   {
      zPCHAR pchFontColorBitmapBlob = new char[ ulLth ];
      GetBlobFromAttribute( pchFontColorBitmapBlob, &ulLth, vDialog,
                            szlCtrl, szlProperties );

      // Get Background Color.
      zmemcpy( (zPLONG) &m_clrBackground,
               pchFontColorBitmapBlob, sizeof( zLONG ) );
      if ( m_clrBackground == -1 )
         m_clrBackground = ::GetSysColor( COLOR_WINDOW );

      // Get Bitmap Height.
      zmemcpy( (zPLONG) &m_lBitmapHeight,
               pchFontColorBitmapBlob + sizeof( zLONG ), sizeof( zLONG ) );

      if ( m_lBitmapHeight <= 0 )
         m_lBitmapHeight = zTREE_BitmapHeight;

      // Get Bitmap Width.
      zmemcpy( (zPLONG) &m_lBitmapWidth,
               pchFontColorBitmapBlob + 2 * sizeof( zLONG ), sizeof( zLONG ) );

      if ( m_lBitmapWidth <= 0 )
         m_lBitmapWidth = zTREE_BitmapHeight;

      // Get Text Color, Font and Bitmap Blob.
      if ( ulLth > sizeof( zLONG ) )
      {
         m_lFontColorBitmapBlobSize = ulLth - 3 * sizeof( zLONG );
         mDeleteInitA( m_pchFontColorBitmapBlob );
         m_pchFontColorBitmapBlob = new char[ m_lFontColorBitmapBlobSize ];
         zmemcpy( m_pchFontColorBitmapBlob,
                  pchFontColorBitmapBlob + 3 * sizeof( zLONG ),
                  m_lFontColorBitmapBlobSize );
      }

      delete [] pchFontColorBitmapBlob;
   }
   else
   {
      m_lBitmapHeight = zTREE_BitmapHeight;
      m_lBitmapWidth  = zTREE_BitmapWidth;
      m_clrBackground = ::GetSysColor( COLOR_WINDOW );
   }
}

zBOOL
ZMSTree::IsDesignTime( zBOOL bCheckWnd )

{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::IsDesignTime", *m_pzsTag );
#endif
   zBOOL    bDesignTime = FALSE;
   ZMapAct  *pzma;
   ZSubtask *pZSubtask;
   zSHORT   nTrace = m_pZSubtask->m_pZTask->m_nTraceAction;

   m_pZSubtask->m_pZTask->m_nTraceAction = 0;  // turn off tracing for this
   if ( GetWindowAndCtrl( &pZSubtask, &pzma, m_vSubtask,
                          zTREE_Tag_ForDesignTime ) == 0 )
   {
      if ( pzma && pzma->m_pCtrl && (bCheckWnd == FALSE || mIs_hWnd( pzma->m_pCtrl->m_hWnd )) &&
           zstrcmp( (*(pzma->m_pzsTag)).GetString(), zTREE_Tag_ForDesignTime ) == 0 )
      {
         bDesignTime = TRUE;
      }
   }

   m_pZSubtask->m_pZTask->m_nTraceAction = nTrace;  // reset tracing level
   return( bDesignTime );
}

zBOOL
ZMSTree::IsMappedEntity( CString csEntityName )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::IsMappedEntity", *m_pzsTag );
#endif
   zLONG             lSize = -1;
   zPCHAR            pchItemColorFontImage;
   zLPOL_COLOR_FONT  OL_ItemColorFontImage;

   pchItemColorFontImage = m_pchFontColorBitmapBlob;

   while ( lSize < m_lFontColorBitmapBlobSize - 1 )
   {
      OL_ItemColorFontImage = (zLPOL_COLOR_FONT) pchItemColorFontImage;

      if ( OL_ItemColorFontImage->szEntityName[ 0 ] &&
           OL_ItemColorFontImage->szEntityName == csEntityName )
      {
         return( TRUE );
      }

      pchItemColorFontImage += sizeof( zTREE_COLOR_FONT );
      lSize += sizeof( zTREE_COLOR_FONT );

   } // end:  while ( lSize < m_lFontColorBitmapBlobSize - 1 )

   return( FALSE );
}

void
ZMSTree::SaveCurrentEntity( )
{
#ifdef DEBUG_ALL
   TraceLine( "ZMSTree::SaveCurrentEntity Tag: %s", *m_pzsTag );
#endif
   // Save the last current Entity.
   m_ulCurrentKey = -1;
   m_csCurrentEntity = "";
   zBOOL bMultiSelect = CanMultiSelect( );

   if ( GetViewByName( &m_vApp, m_csTreeViewName, m_vSubtask, zLEVEL_SUBTASK ) < 0 )
      return;

   if ( IsDesignTime( ) || bMultiSelect )
   {
      m_ulCurrentKey = GetSelectedNodeEntityKey( );
      if ( m_ulCurrentKey >= 0 )
      {
         HTREEITEM hItem = GetSelectedItem( );
         if ( hItem )
         {
            ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );
            m_csCurrentEntity = pNode->m_csEntityName;
         }
      }
   }
   else
   {
      // If Single Selection.
      if ( bMultiSelect == FALSE )
      {
         LPVIEWOD lpViewOD = (LPVIEWOD) zGETPTR( m_vApp->hViewOD );
         LPVIEWENTITY lpViewEntity = 0;

         // Get Entity with last cursor changes.
         if ( m_szLastAccEntity[ 0 ] )
         {
            m_csCurrentEntity = m_szLastAccEntity;
         }
         else
         {
            lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewOD->hFirstOD_Entity );
            while ( lpViewEntity && m_csCurrentEntity.IsEmpty( ) )
            {
               // If Entity mapped to View.
               if ( IsMappedEntity( lpViewEntity->szName ) )
                  m_csCurrentEntity = lpViewEntity->szName;

               lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewEntity->hNextHier );
            }
         }

         // Remove all Selections.
         if ( m_csCurrentEntity.IsEmpty( ) == FALSE )
         {
            lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewOD->hFirstOD_Entity );
            while ( lpViewEntity )
            {
               // If Entity mapped to View, remove select flag.
               if ( IsMappedEntity( lpViewEntity->szName ) )
               {
                  SetAllSelectStatesForEntity( m_vApp, lpViewEntity->szName,
                                               FALSE, zSCOPE_OI );
               }

               lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewEntity->hNextHier );
            }

            // Select current Entity.
            if ( CheckExistenceOfEntity( m_vApp, m_csCurrentEntity ) >= zCURSOR_SET )
            {
               SetSelectStateOfEntity( m_vApp, m_csCurrentEntity, TRUE );
            // DisplayEntityInstance( m_vApp, m_csCurrentEntity );
               OL_GetCurrentEntityNumber( m_vApp, m_csCurrentEntity,
                                          &m_ulCurrentKey );
            }
         } // end:  if ( m_csCurrentEntity.IsEmpty( ) == FALSE )
      } // end:  if ( CanMultiSelect( ) == FALSE )
   }

#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SaveCurrentEntity ", m_csCurrentEntity );
#endif
}

HTREEITEM
ZMSTree::SelectCurrentEntity( zBOOL bReset )
{
#ifdef DEBUG_ALL
   TraceLine( "ZMSTree::SelectCurrentEntity Tag: %s       LastEntity: %s",
              *m_pzsTag, m_szLastAccEntity );
#endif

   zBOOL     bFound = FALSE;
   HTREEITEM hItem  = 0;

   // Try to reposition at previous position.
   if ( GetViewByName( &m_vApp, m_csTreeViewName, m_vSubtask, zLEVEL_SUBTASK ) < 0 )
      return( 0 );

   m_bPreSelectChangeAlreadyDone = TRUE;

   // Get Entity with last cursor changes.
   if ( m_szLastAccEntity[ 0 ] )
   {
      if ( CheckExistenceOfEntity( m_vApp, m_szLastAccEntity ) >= zCURSOR_SET )
      {
         zULONG ulEntityKey;

         OL_GetCurrentEntityNumber( m_vApp, m_szLastAccEntity, &ulEntityKey );
         if ( ulEntityKey )
         {
            ZOL_Node *pNode = m_pRootEntry->FindNodeByEntityKey( ulEntityKey );
            if ( pNode )
            {
               hItem = pNode->m_hItem;
               if ( hItem )
               {
               // ListAllItems( "ZMSTree::SelectCurrentEntity1", hItem );

                  if ( GetSelectStateOfEntity( m_vApp, m_szLastAccEntity ) )
                  {
                  // TraceLine( "ZMSTree::SelectCurrentEntity Item: 0x%08x       Key: %d   Entity: %s   Attrib: %s   Text: %s",
                  //            hItem, pNode->m_ulEntityKey, pNode->m_csEntityName, pNode->m_csAttributeName, csItemText );
                     SelectItem( hItem );
                  }
                  else
                  {
                  // TraceLineS( "ZMSTree::SelectCurrentEntity 0       Text: ", csItemText );
                     SelectItem( 0 );
                  }

                  bFound = TRUE;
               }
            }
         }
      }
   } // endif ( m_szLastAccEntity[ 0 ] )

   if ( bFound == FALSE )
   {
      hItem = GetSelectedItem( );
      if ( hItem == 0 )
      {
         hItem = GetFirstSelectedItem( );

         if ( hItem == 0 && CanMultiSelect( ) == FALSE )
            hItem = GetRootItem( );

         if ( hItem )
         {
         // ListAllItems( "ZMSTree::SelectCurrentEntity2", hItem );
            SelectItem( hItem );
         }
      }
   }

   m_ulKeyLast = 0;
   m_hItemFirstSel = 0;
   if ( hItem )
   {
   // ListAllItems( "ZMSTree::SelectCurrentEntity3", hItem );
      EnsureVisible( hItem );
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );
      if ( pNode && m_vApp )
      {
         CString csEntity = pNode->m_csEntityName;
         m_ulKeyLast = pNode->m_ulEntityKey;
         m_hItemFirstSel = hItem;

         // Make sure all entities are in view.
         if ( bReset )
         {
         // ResetViewPositions( m_vApp ); // Need to reset select states here!
            ResetViewForDefaultSelectSet( m_vApp );
                                          // Because of a bug in OE when using
                                          // zQUAL_ENTITYKEY, some entity
                                          // positions are not reset properly
                                          // when recursive, so we need to call
                                          // ResetViewPositions instead of just
                                          // ResetViewFromSubobject.
            DeselectAllEntities( );
         }
         else
         {
            ResetViewPositions( m_vApp ); // Because of a bug in OE when using
                                          // zQUAL_ENTITYKEY, some entity
                                          // positions are not reset properly
                                          // when recursive, so we need to call
                                          // ResetViewPositions instead of just
                                          // ResetViewFromSubobject.
         }

      // if ( CheckExistenceOfEntity( m_vApp, csEntity ) == 0 )
         {
            if ( SetEntityCursor( m_vApp, csEntity, 0,
                                  zQUAL_ENTITYKEY | zPOS_FIRST | zRECURS,
                                  (zCPVOID) &m_ulKeyLast,
                                  0, 0, 0, 0, 0 ) >= zCURSOR_SET )
            {
            // SetAllSelectStatesForEntity( m_vApp, csEntity, 0, "" );
               SetSelectStateOfEntity( m_vApp, csEntity, 1 );
            // SelectItems( hItem, hItem );
            // SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
            // SelectItem( hItem );

               CString csItemText = GetItemText( hItem );

            // TraceLine( "ZMSTree::SelectCurrentEntity Item: 0x%08x       Key: %d   View %s   Entity: %s   Text: %s",
            //            hItem, m_ulKeyLast, *m_pzsVName, csEntity, csItemText );
               Select( hItem, TVGN_CARET );
            }
         }
      }
#ifdef DEBUG_ALL
      TraceLine( "ZMSTree::SelectCurrentEntity Tag: %s      Item: (%d) %s",
                 *m_pzsTag,
                 pNode ? pNode->m_ulEntityKey : 0,
                 (zCPCHAR) (hItem ? GetItemText( hItem ) : "") );

      ListAllItems( "ZMSTree::SelectCurrentEntity" );
#endif
   }

   m_bPreSelectChangeAlreadyDone = FALSE;
   return( hItem );
}

void
ZMSTree::ListAllItems( zCPCHAR cpcMsg, HTREEITEM hItem )
{
   ZOL_Node *pNode;
   UINT uSelState;

   if ( hItem )
   {
         pNode = (ZOL_Node *) GetItemData( hItem );
         uSelState = (GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED) ?
                                                           TVIS_SELECTED : 0;
         TraceLine( "%s: (0x%08x) %sKey: %d  %s", cpcMsg, hItem,
                    uSelState ? "*" : " ", pNode ? pNode->m_ulEntityKey : 0,
                    (zCPCHAR) GetItemText( hItem ) );
   }
   else
   {
      zLONG lNbr = 0;

      TraceLine( "ZMSTree::ListAllItems Tag: %s       %s", *m_pzsTag, cpcMsg );
      for ( hItem = GetRootItem( ); hItem; hItem = GetNextItemPhysical( hItem ) )
      {
         lNbr++;
         uSelState = (GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED) ?
                                                           TVIS_SELECTED : 0;
         pNode = (ZOL_Node *) GetItemData( hItem );
         TraceLine( "  %sItem Idx: %d  (0x%08x)  Key: %d  %s", uSelState ? "*" : " ",
                    lNbr, hItem, pNode ? pNode->m_ulEntityKey : 0,
                    (zCPCHAR) GetItemText( hItem ) );
      }
   }
}

void
ZMSTree::SetAllTextColorsForItemText( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetAllTextColorsForItemText", *m_pzsTag );
#endif
   if ( m_arrItemColorText.GetSize( ) > 0 )
   {
      ItemColorText ct;
      for ( int k = 0; k < m_arrItemColorText.GetSize( ); k++ )
      {
         ct = m_arrItemColorText.GetAt( k );
         SetTxtItemColorText( ct.csItemText, ct.clrTextColor, FALSE );
      }
   }
}

zLONG
ZMSTree::SetExpandState( CArray <zULONG, zULONG> &hOpenEntityKey,
                         zULONG ulTopEntityKey )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::SetExpandState: ", *m_pzsTag );
#endif
   zLONG lCount = 0;
   zBOOL bFound;
// HTREEITEM hItemTop = 0;

// ListAllItems( " =================> ZMSTree::SetExpandState" );
// for ( int k = 0; k < hOpenEntityKey.GetSize( ); k++ )
//     TraceLineI( "List OpenKey: ", hOpenEntityKey[ k ] );

   m_bExpandInMapFromOI = TRUE;

   for ( HTREEITEM hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
   // bFound = FALSE;
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );
      if ( pNode && pNode->m_ulEntityKey )
      {
      // if ( pNode->m_ulEntityKey == ulTopEntityKey )
      //    hItemTop = hItem;

         for ( int k = 0; k < hOpenEntityKey.GetSize( ); k++ )
         {
            if ( pNode->m_ulEntityKey == hOpenEntityKey[ k ] )
            {
               lCount++;
               ItemExpand( hItem, TVE_EXPAND );
            // hOpenEntityKey.RemoveAt( k );
            // ListAllItems( "ResetState Located Open Node: ", hItem );
            // TraceLineI( "ResetState Located Open Node: ", pNode->m_ulEntityKey );
               bFound = TRUE;
               break;
            }
         }

         if ( bFound == FALSE )
         {
         // ListAllItems( "ResetState did NOT locate Node: ", hItem );
         // TraceLineI( "ResetState did NOT locate Node: ", pNode->m_ulEntityKey );
         }
      }
   }

   m_bExpandInMapFromOI = FALSE;
   hOpenEntityKey.RemoveAll( );

// if ( hItemTop )
// {
//     TraceLineI( "ResetState TopEntityKey: ", ulTopEntityKey );
// // Select( hItemTop, TVGN_FIRSTVISIBLE );  // EnsureVisible( hItemTop );
// }

   return( lCount );
}

zULONG
ZMSTree::SaveExpandState( CArray <zULONG, zULONG> &hOpenEntityKey )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SaveExpandState", *m_pzsTag );
#endif
   zULONG ulTopEntityKey = 0;

   if ( GetCount( ) > 0 )
   {
      HTREEITEM hItem = GetFirstVisibleItem( );
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );
      if ( pNode )
         ulTopEntityKey = pNode->m_ulEntityKey;

      for ( hItem = GetRootItem( );
            hItem;
            hItem = GetNextItemPhysical( hItem ) )
      {
         pNode = (ZOL_Node *) GetItemData( hItem );
         if ( pNode && pNode->m_ulEntityKey )
         {
         // if ( pNode->m_bOpen )
            if ( (GetItemState( hItem, TVIS_EXPANDED )) & TVIS_EXPANDED )
            {
               hOpenEntityKey.Add( pNode->m_ulEntityKey );
            // ListAllItems( "SaveState Adding Open Node: ", hItem );
            // TraceLineI( "SaveState Adding Open Node: ", pNode->m_ulEntityKey );
            }
            else
            {
            // ListAllItems( "SaveState Omitting Node: ", hItem );
            // TraceLineI( "SaveState Omitting Node: ", pNode->m_ulEntityKey );
            }
         }
      }
   }

// TraceLineI( "SaveState TopEntityKey: ", ulTopEntityKey );
   return( ulTopEntityKey );
}

UINT
ZMSTree::OnGetDlgCode( )
{
   return( DLGC_WANTARROWS | DLGC_WANTCHARS );
}

void
ZMSTree::OnSetFocus( CWnd *pWndLostFocus )
{
   m_clrItemBk = ::GetSysColor( COLOR_HIGHLIGHT );

#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnSetFocus ", *m_pzsTag );
#endif

// m_pZSubtask->InformDriverOfSetFocus( this );
   if ( m_pZSubtask->InformDriverOfSetFocus( this ) )
   {
      m_ulMapActFlags |= zTREE_SETFOCUS;
      Default( );             // pass it along to parent
      m_ulMapActFlags &= ~zTREE_SETFOCUS;
   }
}

void
ZMSTree::OnKillFocus( CWnd *pWndGetFocus )
{
   m_clrItemBk = ::GetSysColor( COLOR_INACTIVECAPTION );

#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::OnKillFocus ", *m_pzsTag );
#endif

// m_pZSubtask->InformDriverOfKillFocus( this );
   if ( m_pZSubtask->InformDriverOfKillFocus( this ) )
   {
      Default( );             // pass it along to parent
      Invalidate( );
   }
}

CString
ZMSTree::TreeMakeFullName( zCPCHAR  cpcEntity,
                           zCPCHAR  cpcEntityLabel )
{
   CString csText;

   if ( (m_lStyle & zTREES_NOSHOW_ENTITY) == 0 )
   {
      csText = cpcEntity;
      if ( cpcEntityLabel && *cpcEntityLabel )
      {
         if ( csText.IsEmpty( ) == FALSE )
            csText += " ";
      }
   }

   csText += cpcEntityLabel;
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::TreeMakeFullName: ", csText );
#endif
   return( csText );
}

void
ZMSTree::ReadFontColorBitmap( ZOL_Node *pNode,
                              zPCHAR   pchEntityName )
{
   zLONG            lSize  = -1;
   zBOOL            bFound = FALSE;
   zPCHAR           pchItemColorFontImage;
   zLPOL_COLOR_FONT OL_ItemColorFontImage;
   LOGFONT          logfont;

   // Use window font.
   CFont *pFont = GetFont( );
   pFont->GetLogFont( &logfont );

   pNode->m_TextFont  = logfont;
   pNode->m_TextColor = 0;

   // Set bitmaps.
   pNode->m_lUseDefaultBitmap    = 0;
   pNode->m_lUseSelectedBitmap   = 0;
   pNode->m_csDefaultBitmapFile  = "";
   pNode->m_csSelectedBitmapFile = "";

   if ( m_pchFontColorBitmapBlob )
      pchItemColorFontImage = m_pchFontColorBitmapBlob;

   while ( bFound == FALSE && lSize < m_lFontColorBitmapBlobSize - 1 )
   {
      OL_ItemColorFontImage = (zLPOL_COLOR_FONT) pchItemColorFontImage;
      if ( zstrcmp( OL_ItemColorFontImage->szEntityName, pchEntityName ) == 0 )
      {
         bFound = TRUE;

         // Set Text Color and Font.
         pNode->m_TextColor = OL_ItemColorFontImage->clrTextColor;
         pNode->m_TextFont  = OL_ItemColorFontImage->fntTextFont;

         // Set Bitmaps
         pNode->m_lUseDefaultBitmap    = OL_ItemColorFontImage->lUseDefaultBitmap;
         pNode->m_lUseSelectedBitmap   = OL_ItemColorFontImage->lUseSelectedBitmap;
         pNode->m_csDefaultBitmapFile  = OL_ItemColorFontImage->szDefaultBitmapFile;
         pNode->m_csSelectedBitmapFile = OL_ItemColorFontImage->szSelectedBitmapFile;
      }

      pchItemColorFontImage += sizeof( zTREE_COLOR_FONT );
      lSize += sizeof( zTREE_COLOR_FONT );

   } // endwhile ( bFound && lSize < m_lFontColorBitmapBlobSize - 1 )
}

LPENTITYINSTANCE
ZMSTree::GetEntityInstanceHandle( zVIEW vApp, zPCHAR pchEntityName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetEntityInstanceHandle: ", pchEntityName );
#endif
   LPVIEWOD          lpViewOD;
   LPVIEWCSR         lpViewCsr;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWENTITYCSR   lpViewEntityCsr;

   // Get the view csr for the view.
   lpViewCsr = (LPVIEWCSR) zGETPTR( vApp->hViewCsr );

   // Get the view object definition for the view.
   lpViewOD = (LPVIEWOD) zGETPTR( vApp->hViewOD );

   // Validate that the entity exists.
   lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewOD->hFirstOD_Entity );
   lpViewEntityCsr = (LPVIEWENTITYCSR) zGETPTR( lpViewCsr->hRootViewEntityCsr );

   // If the root cursor is not the first cursor, skip ViewEntities
   // until we get to the entity matching the root cursor.
   // If the view is positioned on a subobject, then
   // hFirstOD_EntityCsr = root of object (example TZWDLGSO: Dialog)
   // hRootViewEntityCsr = root of subobject (example TZWDLGSO: Control)

   if ( lpViewEntityCsr != (LPVIEWENTITYCSR) zGETPTR( lpViewCsr->hFirstOD_EntityCsr ) )
   {
      LPVIEWENTITYCSR lpSearchViewEntityCsr;

      lpSearchViewEntityCsr = (LPVIEWENTITYCSR) zGETPTR( lpViewCsr->hFirstOD_EntityCsr );
      while ( lpSearchViewEntityCsr != lpViewEntityCsr )
      {
         lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewEntity->hNextHier );
         lpSearchViewEntityCsr++;
      }
   }

   while ( lpViewEntityCsr &&
           zstrcmp( lpViewEntity->szName, pchEntityName ) != 0 )
   {
      lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewEntity->hNextHier );
      lpViewEntityCsr = (LPVIEWENTITYCSR) zGETPTR( lpViewEntityCsr->hNextHier );
   }

   // If entity not found return error.
   if ( lpViewEntityCsr )
      return( lpViewEntityCsr->hEntityInstance );
   else
      return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:   BuildTreeDataStruct
//
//  PURPOSE: This function loops through the execution CtrlBOI
//           recursively retrieves the mapping information and
//           uses that information to create the data into the
//           tree.
//
/////////////////////////////////////////////////////////////////////////////
void
ZMSTree::BuildTreeDataStruct( zVIEW      vApp,
                              ZOL_Node   *pParentNode,
                              zLPOL_ITEM OL_Item,
                              zSHORT     nRecurse )
{
#ifdef DEBUG_ALL
// TraceLine( "ZMSTree::BuildTreeDataStruct: %s       Recurse: %d",
//            *m_pzsTag, nRecurse );
#endif
   ZOL_Node *pNode;
   CString  csLabel;
   CString  csText;
   CString  csSelectedEntity;
   zPCHAR   pch;
   zULONG   ulEntityKeyForSelectedEntity = 0;
   zULONG   ulEntityKey = 0;
   zBOOL    bSibling = TRUE;
   zSHORT   nItemSize = HIWORD( OL_Item->lFlags );
   zSHORT   nRC, nRC1;

   ASSERT( nItemSize == 0 || nItemSize == sizeof( zTREE_ITEM ) );

   // bSibling indicates whether there is another entity to be displayed
   // on the tree at the same level as the previous entity.
   while ( bSibling )
   {
      // Loop through the tree's application instance and get its data.
      // nRecurse is set only when we are in this function recursively.
      // If we are, we want the scoping entity to be the recursive child's
      // parent, otherwise let normal scoping occur.
      if ( nRecurse > 0 )
      {
         nRC = SetCursorFirstEntity( vApp, OL_Item->szRecursiveEntity,
                                           OL_Item->szEntityName );
      }
      else
      if ( nRecurse == 0 )  // if nRecurse == 0, first time in
      {
         if ( zstrcmp( OL_Item->szScopeEntity, "zSCOPE_OI" ) == 0 )
            nRC = SetEntityCursor( vApp, OL_Item->szEntityName, 0,
                                   zQUAL_SCOPE_OI | zPOS_FIRST, 0, 0, 0, 0, zSCOPE_OI, 0 );
         else
            nRC = SetCursorFirstEntity( vApp, OL_Item->szEntityName,
                                        OL_Item->szScopeEntity );
      }
      else
      {
         nRC = CheckExistenceOfEntity( vApp, OL_Item->szEntityName );
         if ( nRC > zCURSOR_UNCHANGED )
         {
            if ( CanMultiSelect( ) == FALSE )
            {
               OL_GetCurrentEntityNumber( vApp, OL_Item->szEntityName,
                                          &ulEntityKey );
            }
         }
         else
            nRecurse = 0;  // prevent code following the while from executing
      }

      while ( nRC > zCURSOR_UNCHANGED )
      {
         if ( nRecurse > 0 )
            SetViewToSubobject( vApp, OL_Item->szRecursiveEntity );

      // pNode = new ZOL_Node( );
      // pNode->SetParent( pParentNode );
      // pNode->m_csEntityName = OL_Item->szEntityName;
         pNode = new ZOL_Node( pParentNode, OL_Item->szEntityName );
         pNode->m_bSelected =
               (zBOOL) GetSelectStateOfEntity( vApp, OL_Item->szEntityName );
      // pNode->m_hEntityInstance =
      //              GetEntityInstanceHandle( vApp, OL_Item->szEntityName );
         OL_GetCurrentEntityNumber( vApp, OL_Item->szEntityName,
                                    &(pNode->m_ulEntityKey) );
         zBOOL bRecurse = FALSE;

         // If this entity in the tree's application instance
         // is selected, then set it as selected on the tree.
         if ( pNode->m_bSelected )
         {
            csSelectedEntity = OL_Item->szEntityName;
            ulEntityKeyForSelectedEntity = pNode->m_ulEntityKey;
            bRecurse = (OL_Item->lFlags & zTREE_RECURSIVE) ? TRUE : FALSE;
         }

         // Set Text Color and Font.
         if ( IsDesignTime( ) == FALSE )
         {
            zCHAR szEntityName[ zTAG_LTH ];

            strcpy_s( szEntityName, zsizeof( szEntityName ), OL_Item->szEntityName );
            GetRealEntityName( vApp, szEntityName );
            ReadFontColorBitmap( pNode, szEntityName );
         }

         // Process the attributes for the tree item.
         if ( OL_Item->lAttributeOffset )
         {
            pch = m_pchCtrlBOI + OL_Item->lAttributeOffset;
            while ( *pch )
            {
               zULONG ulDisplayLength = 0;
               CString csAttribute = pch;  // get the attribute name
               pch += csAttribute.GetLength( ) + 1;
               pNode->m_csAttributeName = csAttribute;

               CString csContext = pch;  // get the context
               pch += csContext.GetLength( ) + 1;
               pNode->m_csContextName = csContext;

               GetAttributeDisplayLength( &ulDisplayLength, vApp,
                                          OL_Item->szEntityName,
                                          csAttribute,
                                          csContext.IsEmpty( ) ? (zCPCHAR) csContext : 0 );

               zPCHAR szLabel = csText.GetBufferSetLength( ulDisplayLength + 1 );

               GetVariableFromAttribute( szLabel, 0,
                                         zTYPE_STRING, ulDisplayLength + 1,
                                         vApp, OL_Item->szEntityName,
                                         csAttribute, csContext,
                                         csContext.IsEmpty( ) ? zUSE_DEFAULT_CONTEXT : 0 );

               // Set Text Color and Font.
               if ( IsDesignTime( ) )
                  ReadFontColorBitmap( pNode, szLabel );

               csLabel = TreeMakeFullName( OL_Item->szEntityName, szLabel );

#if 0
               ZOL_Node *pTempNode = pNode;
               zCHAR szBlanks[ 256 ];
               zSHORT nLevel = 0;

               while ( pTempNode )
               {
                  szBlanks[ nLevel++ ] = ' ';
                  pTempNode = pTempNode->m_pParent;
               }

               szBlanks[ nLevel ] = 0;

               TraceLine( "ZMSTree::BuildTreeDataStruct Key: %d       %sLabel: %s",
                          pNode->m_ulEntityKey, szBlanks, csLabel );
#endif
               csText.ReleaseBuffer( );
               pNode->AddValue( csLabel );
            }
         }

         // If there are child entities to be displayed on the
         // tree, then display them.  lChildEntityOffset
         // is set in ConvertTree (tzctlcvt.cpp).
         if ( OL_Item->lChildEntityOffset )
         {
            zLPOL_ITEM olChild = (zLPOL_ITEM) (m_pchCtrlBOI + OL_Item->lChildEntityOffset);
            BuildTreeDataStruct( vApp, pNode, olChild, 0 );
         }

         // If the current entity is recursive then loop recursively to
         // set the data in the tree.
         if ( (OL_Item->lFlags & zTREE_RECURSIVE) &&
              CheckExistenceOfEntity( vApp, OL_Item->szRecursiveEntity ) == zCURSOR_SET )
         {
            BuildTreeDataStruct( vApp, pNode, OL_Item, 1 );
         }

         if ( nRecurse > 0 )
         {
            ResetViewFromSubobject( vApp );
            nRC = SetCursorNextEntity( vApp, OL_Item->szRecursiveEntity,
                                       OL_Item->szEntityName );
         }
         else
         if ( nRecurse == 0 )
         {
            nRC = SetCursorNextEntity( vApp, OL_Item->szEntityName,
                                       OL_Item->szScopeEntity );
         }
         else
            nRC = zCURSOR_UNCHANGED;

      } // while ( nRC > zCURSOR_UNCHANGED )

      if ( nRecurse != -2 && OL_Item->lSiblingEntityOffset ) // ==> MultiRoot
      {
         OL_Item = (zLPOL_ITEM) (m_pchCtrlBOI + OL_Item->lSiblingEntityOffset);
         continue;
      }
      else
      if ( nRecurse == -2 )  // ==> MultiRoot
      {
         if ( zstrcmp( OL_Item->szScopeEntity, "zSCOPE_OI" ) == 0 )
            nRC1 = SetEntityCursor( vApp, OL_Item->szEntityName, 0,
                                    zQUAL_SCOPE_OI | zPOS_NEXT,
                                    0, 0, 0, 0, zSCOPE_OI, 0 );
         else
            nRC1 = SetCursorNextEntity( vApp, OL_Item->szEntityName,
                                        OL_Item->szScopeEntity );
         if ( nRC1 >= zCURSOR_SET )
            continue;
         else
            bSibling = FALSE;
      }

      // Indicate whether there is another entity to be displayed in the
      // tree at the same level as the current entity.
      if ( bSibling == FALSE && OL_Item->lSiblingEntityOffset )
      {
         OL_Item = (zLPOL_ITEM) (m_pchCtrlBOI + OL_Item->lSiblingEntityOffset);

         if ( nRecurse == -2 )
         {
            if ( zstrcmp( OL_Item->szScopeEntity, "zSCOPE_OI" ) == 0 )
               nRC1 = SetEntityCursor( vApp, OL_Item->szEntityName, 0,
                                       zQUAL_SCOPE_OI | zPOS_FIRST,
                                       0, 0, 0, 0, zSCOPE_OI, 0 );
            else
               nRC1 = SetCursorFirstEntity( vApp, OL_Item->szEntityName,
                                            OL_Item->szScopeEntity );
            if ( nRC1 >= zCURSOR_SET )
               bSibling = TRUE;
            else
               break;
         }

         continue;
      }

      if ( nRecurse != -2 && OL_Item->lSiblingEntityOffset == 0 )
         bSibling = FALSE;

   }  // while ( bSibling );

   if ( IsDesignTime( ) == FALSE && m_bCreateTree &&
        csSelectedEntity != "" && ulEntityKeyForSelectedEntity )
   {
      OL_SetCursorByEntityNumber( m_vApp, csSelectedEntity,
                                  ulEntityKeyForSelectedEntity );
      m_bCreateTree = FALSE;
   }
}

zSHORT
ZMSTree::MapTreeFromOI( )
{
#ifdef DEBUG_ALL
// if ( zstrcmp( *m_pzsTag, "OLCPList" ) == 0 )
      TraceLineS( "ZMSTree::MapTreeFromOI ", *m_pzsTag );
#endif

// Already checked by calling function
// if ( m_pchCtrlBOI == 0 )
//    return( -1 );
//
// mDeleteInit( m_pRootEntry );

   if ( GetViewByName( &m_vApp, m_csAppViewName, m_vSubtask, zLEVEL_ANY ) <= 0 )
   {
      TraceLineS( "Unable to load view for Tree - ", m_csAppViewName );
      return( -1 );  // application view not found
   }

   AddCursorListener( m_vApp, TreeCursorListener, this );

   // Name the view to make sure it's not dropped by some garbage collection.
   SetNameForView( m_vApp, m_csTreeViewName, m_vSubtask, zLEVEL_SUBTASK );

// TraceLine( "ZMSTree::MapTreeFromOI Tag: %s       ViewName: %s",
//            *m_pzsTag, m_csAppViewName );
// DisplayEntityInstance( m_vApp, *m_pzsEName );

   if ( IsDesignTime( ) == FALSE )
      SaveCurrentEntity( );

   zVIEW vApp;
   CreateViewFromViewForTask( &vApp, m_vApp, m_pZSubtask->m_vDialog );
   SetNameForView( vApp, m_csTreeViewName + "_Map", m_vSubtask, zLEVEL_SUBTASK );

   // This is a change ... it used to be prior to the CreateViewFromViewForTask above
   // and the ResetView was applied to m_vApp.  This caused loss of position
   // problems, so the ResetView is only being applied to the new view, leaving
   // the original view alone. (dks)
// ResetViewPositions( vApp );  // reset's top entity positions
   while ( ResetViewFromSubobject( vApp ) == 0 )
   {
      // don't reset top entity positions!
   }

   // Skip to first entity item struct.
   zPCHAR pch = m_pchCtrlBOI + m_nFirstEntityOffset;
   zLPOL_ITEM pOL_Item = (zLPOL_ITEM) pch;

   // Create a dummy root entry that will never be displayed.
   // We only use it to have a single entry for recursive calls
   // to BuildTreeDataStruct.
// m_pRootEntry = new ZOL_Node( );
// m_pRootEntry->m_csEntityName = m_csAppViewName;
// m_pRootEntry->SetParent( 0 );
   m_pRootEntry = new ZOL_Node( 0, m_csAppViewName );

   // Set the title of the tree with the tree text if specified,
   // otherwise the view name is the default.
   if ( *m_pzsText )
      m_csRootItemLabel = *m_pzsText;

   m_pRootEntry->AddValue( m_csRootItemLabel );
   m_pRootEntry->m_ulEntityKey = 0;

   // If m_nType is 0, then a root tree entity is created that displays
   // the tree text.  If m_nType is 1, then the tree just starts
   // with the first view entity.
   if ( m_nType == zTREE_TYPE_MULTIROOT )
   {
      // When building a MultiRoot tree, it makes sense to me to reset the
      // cursor position to the first entity with object scope.
      SetEntityCursor( vApp, pOL_Item->szEntityName, 0,
                       zQUAL_SCOPE_OI | zPOS_FIRST, 0, 0, 0, 0,
                       zSCOPE_OI, 0 );
      BuildTreeDataStruct( vApp, m_pRootEntry, pOL_Item, -2 ); // MultiRoot
   }
   else
   {
      BuildTreeDataStruct( vApp, m_pRootEntry, pOL_Item, -1 ); // SingleRoot
   }

// m_pRootEntry->Display( );

   DropView( vApp );
   return( 0 );
}

#ifdef zREMOTE_SERVER
zLONG
ZMSTree::PopulateTree( ZOL_Node *pNode, zVIEW vRoot )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::PopulateTree ", *m_pzsTag );
#endif
   zLONG lRC = 0;

   // check against default parameters
   if ( pNode == 0 )
   {
      // An empty node means this is the tree's root entry.
      pNode = m_pRootEntry;
   }

   if ( vRoot == 0 )
   {
      vRoot = SetupRemoteObject( );
      if ( vRoot == 0 )
      {
         CString csMsg = "Failed to retrieve Remote Object.  "
                         "Control cannot be handled";
         TraceLineS( csMsg, *m_pzsTag );
         lRC = -1;
      }
      else
      {
         if ( pNode )
         {
            // We know the root entry is a dummy so we ignore it, but we do not
            // ignore its children.  They are valid!
            if ( pNode != m_pRootEntry )
            {
               CString csText = pNode->GetValue( ); // get the first value
               zLONG   lHelp = pNode->m_ulEntityKey;

               zSHORT nRC = CreateEntity( vRoot, m_csTreeNodeEntity, zPOS_AFTER );
               if ( nRC == 0 )
               {
                  SetAttributeFromString( vRoot,
                                          m_csTreeNodeEntity,
                                          m_csTreeNodeTextAttr,
                                          csText );

                  SetAttributeFromInteger( vRoot,
                                           m_csTreeNodeEntity,
                                           m_csTreeNodeTagAttr,
                                           lHelp );

                  // providing State information
                  UINT uiState = 0;
                  if ( pNode->m_bSelected )
                  {
                     nRC = CreateEntity( vRoot, m_csTreeSelectionEntity, zPOS_AFTER );
                     if ( nRC == 0 )
                     {
                        SetAttributeFromInteger( vRoot,
                                                 m_csTreeSelectionEntity,
                                                 m_csTreeSelectionTag,
                                                 lHelp );
                     }
                     else
                     {
                        CString csMsg = "Failed to create entity %s. "
                                        "Invalid state information will be passed for ";
                        csMsg.Format( csMsg, m_csTreeSelectionEntity );
                        TraceLineS( csMsg, *m_pzsTag );
                     }
                  }

                  POSITION pos = pNode->GetFirstChildPosition( );
                  while ( pos )
                  {
                     ZOL_Node *pChildNode = pNode->GetNextChild( pos );

                     SetViewToSubobject( vRoot, m_csTreeNodeChildEntity );
                     PopulateTree( pChildNode, vRoot );
                     ResetViewFromSubobject( vRoot );
                  }
               }
            }
            else
            {
               POSITION pos = pNode->GetFirstChildPosition( );
               while ( pos )
               {
                  ZOL_Node *pChildNode = pNode->GetNextChild( pos );
                  PopulateTree( pChildNode );
               }
            }
         }
      }
   }

   return( lRC );
}

#else  // #ifdef zREMOTE_SERVER

zLONG
ZMSTree::PopulateTree( ZOL_Node *pNode, HTREEITEM hRoot )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::PopulateTree ", *m_pzsTag );
#endif
   zLONG   lRC = 0;
   TV_INSERTSTRUCT tvis;
   tvis.item.state = 0;

   UINT uiTreeMask = TVIF_PARAM | // the lParam member is valid
                         TVIF_TEXT  | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

   // Check against default parameters.
   if ( pNode )
   {
      tvis.hParent = hRoot; // doesn't matter if it's null
   }
   else
   {
      // An empty node means this is the tree's root entry.
      pNode = m_pRootEntry;
      tvis.hParent = TVI_ROOT;
   }

   if ( pNode )
   {
      // We know the root entry is a dummy so we ignore it, but we do not
      // ignore its children.  They are valid!
      if ( pNode != m_pRootEntry )
      {
         // Setup structure defaults.
         tvis.hInsertAfter = TVI_LAST;
         tvis.item.mask = uiTreeMask;
         tvis.item.lParam = (LPARAM) pNode;

         CString csText = pNode->GetValue( ); // get the first value
         tvis.item.pszText = _T( (LPSTR)(LPCSTR) csText );

         HTREEITEM hItem = InsertItem( &tvis );
         if ( hItem )
         {
            // Associate our node pointer with the window element
            // to make navigation a lot easier later on.
            SetItemData( hItem, (DWORD) pNode );
            UINT uiState = 0;

            if ( pNode->m_bSelected )
            {
               uiState = INDEXTOSTATEIMAGEMASK( zTREE_STATE_SELECTED_IMG );
               if ( IsDesignTime( ) == FALSE )
                  SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
            }
            else
            {
               uiState = INDEXTOSTATEIMAGEMASK( zTREE_STATE_UNSELECTED_IMG );
               SetItemState( hItem, 0, TVIS_SELECTED );
            }

            // Save Item from the last current Entity.
            if ( IsDesignTime( ) )
            {
               SetItemState( hItem, uiState, TVIS_STATEIMAGEMASK );

               if ( m_csCurrentEntity != "" && m_ulCurrentKey > 0 &&
                    pNode->m_csEntityName == m_csCurrentEntity &&
                    pNode->m_ulEntityKey == m_ulCurrentKey )
               {
                  SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
               }
            }

            // Set Item Handle.
            pNode->m_hItem = hItem;

            // Set Text Color and Text Font.
            SetItemColor( hItem, pNode->m_TextColor );
            SetItemFont( hItem, pNode->m_TextFont );

            // If not Design Time, set Bitmaps.
            if ( m_bNoImage == FALSE && IsDesignTime( ) == FALSE )
               SetItemBitmap( hItem, pNode );

            POSITION pos = pNode->GetFirstChildPosition( );
            while ( pos ) // if there is a pos, there is a child
            {
               ZOL_Node *pChildNode = pNode->GetNextChild( pos );
               PopulateTree( pChildNode, hItem );
            }
         }
      }
      else
      {
         POSITION pos = pNode->GetFirstChildPosition( );
         while ( pos ) // if there is a pos, there is a child
         {
            ZOL_Node *pChildNode = pNode->GetNextChild( pos );
            PopulateTree( pChildNode );
         }
      }
   }

   return( lRC );
}
#endif

zLONG
ZMSTree::SetBitmapFileToImageList( CString csBitmapFile )
{
#ifdef DEBUG_ALL
   TraceLine( "ZMSTree::SetBitmapFileToImageList: %s       File: %s",
              *m_pzsTag, csBitmapFile );
#endif
   HINSTANCE hInst;
   zPCHAR    pchDLL_Name;
   HICON     hIcon;
   zLONG     lImageListIdx;
   FileImage fi;

   if ( m_mapFileImage.Lookup( csBitmapFile, fi ) )
      return( fi.lImageListIdx );

   // Get the DLL name.
   GetAddrForAttribute( &pchDLL_Name, m_vSubtask, "Dlg", "DLL" );
   if ( *pchDLL_Name )
   {
      LPLIBRARY hLibrary = SysLoadLibraryWithErrFlag( m_vSubtask, pchDLL_Name,
                                                      zLOADLIB_RESOURCES );
      hInst = (HINSTANCE) SysGetInstance( hLibrary );
   }
   else
      hInst = 0;

   hIcon = ::ExtractIcon( hInst, csBitmapFile, 0 );  // try exactly as specified

   // Bitmap not found, load with ResourcePath.
   if ( hIcon == 0 || hIcon == (HICON) 1 )
   {
      // Not found ... prepend resource path and try again.
      zCHAR  szZeidonPath[ zMAX_FILENAME_LTH ];
      zCHAR  szWorkString[ zMAX_FILENAME_LTH ];

      SysReadZeidonIni( -1, "[Workstation]", "ResourcePath", szZeidonPath, zsizeof( szZeidonPath ) );

      if ( szZeidonPath[ 0 ] )
      {
         SysAppendcDirSep( szZeidonPath );
         strcat_s( szZeidonPath, zsizeof( szZeidonPath ), csBitmapFile );
         SysConvertEnvironmentString( szWorkString, zsizeof( szWorkString ), szZeidonPath );

         csBitmapFile = szWorkString;
         if ( m_mapFileImage.Lookup( csBitmapFile, fi ) )
            return( fi.lImageListIdx );

         HICON hIcon1 = ::ExtractIcon( hInst, szWorkString, 0 );
         if ( hIcon1 && hIcon1 != (HICON) 1 )
            hIcon = hIcon1;

         if ( hIcon == (HICON) 1 )
         {
            hIcon = 0;
            TraceLineS( "Invalid bitmap file1 ", szWorkString );
         }
         else
         if ( hIcon == 0 )
         {
            TraceLineS( "Cannot access bitmap file1 ", szWorkString );
         }
      }

      if ( hIcon == (HICON) 1 )
      {
         hIcon = 0;
         TraceLineS( "Invalid bitmap file2 ", csBitmapFile );
      }
      else
      if ( hIcon == 0 )
      {
         TraceLineS( "Cannot access bitmap file2 ", csBitmapFile );
      }
   }

   if ( hIcon )
   {
      m_ImageList.Add( hIcon );
      DestroyIcon( hIcon );
      lImageListIdx = m_ImageList.GetImageCount( ) - 1;
      fi.lImageListIdx = lImageListIdx;
      m_mapFileImage[ csBitmapFile ] = fi;
   }
   else
   {
      TraceLineS( "ZMSTree::SetBitmapFileToImageList INVALID File: ", csBitmapFile );
   }

   return( lImageListIdx );
}

zLONG
ZMSTree::GetBitmapIdFromImageList( HTREEITEM hCurrentItem,
                                   CString   csBitmapFile,
                                   zBOOL     bSelected )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetBitmapIdFromImageList ", *m_pzsTag );
#endif
   zLONG      lImageListIdx = -1;
   ItemColorFontImage cfi_current;
   ItemColorFontImage cfi;
   zBOOL      bFound = FALSE;

   // Set default values for Item.

   if ( (bSelected == FALSE && m_mapItemColorFontImage.Lookup( hCurrentItem, cfi_current ) == 0) ||
        (bSelected && m_mapItemColorFontImageSelected.Lookup( hCurrentItem, cfi_current ) == 0) )
   {
      cfi_current.color = CLR_INVALID;
      cfi_current.logfont.lfFaceName[ 0 ] = 0;
      cfi_current.csBitmapFile.Empty( );
      cfi_current.lImageListIdx = -1;  // invalid image index
   }

#if 0  // we shouldn't need this check

   // Does an Item exist with this Bitmap File?  If so, use this Bitmap ID.
   for ( HTREEITEM hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      if ( ((bSelected == FALSE && m_mapItemColorFontImage.Lookup( hItem, cfi )) ||
            (bSelected && m_mapItemColorFontImageSelected.Lookup( hItem, cfi ))) &&
           cfi.csBitmapFile == csBitmapFile && cfi.lImageListIdx != -1 )
      {
         lImageListIdx = cfi.lImageListIdx;
         bFound = TRUE;
         break;
      }
   }
#endif

   // Bitmap does not exist ... add to ImageList.
   if ( bFound == FALSE )
   {
      // We need to keep track of the association of the FileName
      // and the index to the ImageList.
      lImageListIdx = SetBitmapFileToImageList( csBitmapFile );
   }

   cfi_current.lImageListIdx = lImageListIdx;
   cfi_current.csBitmapFile = csBitmapFile;

   if ( bSelected )
      m_mapItemColorFontImageSelected[ hCurrentItem ] = cfi_current;
   else
      m_mapItemColorFontImage[ hCurrentItem ] = cfi_current;

   return( lImageListIdx );
}

void
ZMSTree::SetItemBitmap( HTREEITEM hItem, ZOL_Node *pNode )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::SetItemBitmap ", *m_pzsTag );
#endif
   zLONG  lImageListIdx = -1;
   zLONG  lSelectedImage;

   if ( m_bNoImage )
      return;

   HINSTANCE hInstance = AfxGetResourceHandle( );
   AfxSetResourceHandle( g_hInstanceDLL );

   // Set Default Bitmap.
   if ( pNode->m_lUseDefaultBitmap == 1 ||
        pNode->m_csDefaultBitmapFile.IsEmpty( ) )
   {
      lImageListIdx = zTREE_STATE_CLOSE_IMG;
   }
   else
   {
      lImageListIdx = GetBitmapIdFromImageList( hItem, pNode->m_csDefaultBitmapFile, FALSE );
      if ( lImageListIdx < 0 )
         lImageListIdx = zTREE_STATE_CLOSE_IMG;
   }

   lSelectedImage = lImageListIdx;

   if ( IsDesignTime( ) == FALSE )
   {
      if ( pNode->m_lUseSelectedBitmap == 1 ||
           pNode->m_csSelectedBitmapFile.IsEmpty( ) )
      {
         lSelectedImage = zTREE_STATE_OPEN_IMG;
      }
      else
      {
         lSelectedImage = GetBitmapIdFromImageList( hItem, pNode->m_csSelectedBitmapFile, TRUE );
         if ( lSelectedImage < 0 )
            lImageListIdx = zTREE_STATE_OPEN_IMG;
      }
   }

   if ( lImageListIdx >= 0 )
      SetItemImage( hItem, lImageListIdx, lSelectedImage );

   AfxSetResourceHandle( hInstance );
}

void
ZMSTree::SetColorAndFont( CDC *pMemDC )
{
   // Set Text Color and Text Font.
   HTREEITEM hItem = GetFirstVisibleItem( );

   zLONG lCnt = GetVisibleCount( ) + 1;

   while ( hItem && lCnt-- )
   {
      CRect rect;

      // Do not meddle with selected items or drop highlighted items.
      UINT uSelFlag = TVIS_DROPHILITED | TVIS_SELECTED;
      ItemColorFontImage cfi;

      if ( m_mapItemColorFontImage.Lookup( hItem, cfi ) )
      {
         CFont   *pFontOld;
         CFont   fontDC;
         LOGFONT logfont;
         CString csItemText = GetItemText( hItem );

#ifdef DEBUG_ALL
         TraceLineS( "ZMSTree::SetColorAndFont: ", csItemText );
#endif

         if ( cfi.logfont.lfFaceName[ 0 ] )
         {
            logfont = cfi.logfont;
         }
         else
         {
            // No font specified, so use window font.
            CFont *pFont = GetFont( );
            pFont->GetLogFont( &logfont );
         }

         if ( GetItemBold( hItem ) )
            logfont.lfWeight = FW_BOLD;

         fontDC.CreateFontIndirect( &logfont );
         pFontOld = pMemDC->SelectObject( &fontDC );

         if ( GetItemState( hItem, uSelFlag ) & uSelFlag )
         {
            pMemDC->SetTextColor( ::GetSysColor( COLOR_HIGHLIGHTTEXT ) );
         }
         else
         {
            if ( cfi.color != CLR_INVALID )
               pMemDC->SetTextColor( cfi.color );
            else
               pMemDC->SetTextColor( ::GetSysColor( COLOR_WINDOWTEXT ) );
         }

         GetItemRect( hItem, &rect, TRUE );
         pMemDC->FillRect( rect, &CBrush( m_clrBackground ) );

         if ( GetItemState( hItem, uSelFlag ) & uSelFlag )
            pMemDC->SetBkColor( ::GetSysColor( m_clrItemBk ) );
         else
            pMemDC->SetBkColor( m_clrBackground );

         pMemDC->TextOut( rect.left + 2, rect.top + 1, csItemText );
         pMemDC->SelectObject( pFontOld );
      }

      hItem = GetNextVisibleItem( hItem );
   }
}

zLONG
ZMSTree::GetBackgroundColor( )
{
   return( m_clrBackground );
}

zLONG
ZMSTree::LoadBitmapWithResourcePath( HTREEITEM hItem,
                                     zCPCHAR   cpcBitmapFileName,
                                     zBOOL     bSelected )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::LoadBitmapWithResourcePath ", *m_pzsTag );
#endif
   zLONG    lImageListIdx = -1;
   zCHAR    szZeidonPath[ zMAX_FILENAME_LTH ];
   zCHAR    szWorkString[ zMAX_FILENAME_LTH + 40 ];

   // Load Bitmap with Resource Path.
   SysReadZeidonIni( -1, "[Workstation]", "ResourcePath", szZeidonPath, zsizeof( szZeidonPath ) );

   if ( szZeidonPath[ 0 ] )
   {
      SysAppendcDirSep( szZeidonPath );
      strcat_s( szZeidonPath, zsizeof( szZeidonPath ), cpcBitmapFileName );
      SysConvertEnvironmentString( szWorkString, zsizeof( szWorkString ), szZeidonPath );
      lImageListIdx = GetBitmapIdFromImageList( hItem, szWorkString, bSelected );
   }

   return( lImageListIdx );
}

zLONG
ZMSTree::GetSelectedBitmap( zCPCHAR cpcEntityName,
                            zPCHAR  pchBitmapFileName,
                            zULONG  ulMaxReturnBitmapNameLength )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetSelectedBitmap ", *m_pzsTag );
#endif
   zLPOL_COLOR_FONT OL_ItemColorFontImage;
   CString          csEntityName;
   zPCHAR           pchItemColorFontImage;
   zLONG            lSize = -1;
   zLONG            lRC = -1;

   pchBitmapFileName[ 0 ] = 0;  // initialize return value

   // If cpcEntityName is null, set Entity Name from current Entity.
   if ( cpcEntityName == 0 || cpcEntityName[ 0 ] == 0 )
      csEntityName = GetCurrentEntityName( );
   else
      csEntityName = cpcEntityName;

   if ( m_pchFontColorBitmapBlob )
      pchItemColorFontImage = m_pchFontColorBitmapBlob;

   while ( lRC && lSize < m_lFontColorBitmapBlobSize - 1 )
   {
      OL_ItemColorFontImage = (zLPOL_COLOR_FONT) pchItemColorFontImage;

      if ( zstrcmp( OL_ItemColorFontImage->szEntityName, csEntityName.GetString() ) == 0 )
      {
         lRC = 0;
         if ( OL_ItemColorFontImage->lUseSelectedBitmap != 1 )
         {
            strncat_s( pchBitmapFileName, ulMaxReturnBitmapNameLength,
                       OL_ItemColorFontImage->szSelectedBitmapFile, ulMaxReturnBitmapNameLength - 1 );
         }
      }

      pchItemColorFontImage += sizeof( zTREE_COLOR_FONT );
      lSize += sizeof( zTREE_COLOR_FONT );

   } // end: while ( lRC && lSize < m_lFontColorBitmapBlobSize - 1 )

   return( lRC );
}

zLONG
ZMSTree::GetDefaultBitmap( zCPCHAR cpcEntityName, zPCHAR pchBitmapFileName,
                           zULONG  ulMaxReturnBitmapNameLength )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetDefaultBitmap: ", *m_pzsTag );
#endif
   zLPOL_COLOR_FONT OL_ItemColorFontImage;
   CString          csEntityName;
   zPCHAR           pchItemColorFontImage;
   zLONG            lSize = -1;
   zLONG            lRC = -1;

   pchBitmapFileName[ 0 ] = 0;  // initialize return value

   // If cpcEntityName is null, set Entity Name from current Entity.
   if ( cpcEntityName == 0 || cpcEntityName[ 0 ] == 0 )
      csEntityName = GetCurrentEntityName( );
   else
      csEntityName = cpcEntityName;

   if ( m_pchFontColorBitmapBlob )
      pchItemColorFontImage = m_pchFontColorBitmapBlob;

   while ( lRC && lSize < m_lFontColorBitmapBlobSize - 1 )
   {
      OL_ItemColorFontImage = (zLPOL_COLOR_FONT) pchItemColorFontImage;

      if ( zstrcmp( OL_ItemColorFontImage->szEntityName, csEntityName.GetString() ) == 0 )
      {
         lRC = 0;
         if ( OL_ItemColorFontImage->lUseDefaultBitmap != 1 )
         {
            strncat_s( pchBitmapFileName, ulMaxReturnBitmapNameLength,
                       OL_ItemColorFontImage->szDefaultBitmapFile, ulMaxReturnBitmapNameLength - 1 );
         }
      }

      pchItemColorFontImage += sizeof( zTREE_COLOR_FONT );
      lSize += sizeof( zTREE_COLOR_FONT );

   } // end: while ( lRC && lSize < m_lFontColorBitmapBlobSize - 1 )

   return( lRC );
}

zLONG
ZMSTree::SetDefaultBitmap( zCPCHAR cpcEntityName,
                           zCPCHAR cpcBitmapFileName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetDefaultBitmap: ", *m_pzsTag );
#endif
   if ( m_bNoImage )
      return( -1 );

   // If someone is using the Window Postbuild Event with a Tree Control,
   // then the mapping will not be there and the Tree Function will not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   HINSTANCE hInstance = AfxGetResourceHandle( );
   AfxSetResourceHandle( g_hInstanceDLL );

   HTREEITEM hItem        = 0;
   ZOL_Node  *pNode       = 0;
   ZOL_Node  *pNodeFound  = 0;
   CString   csEntityName;
   zLONG     lImageListIdx = -1;
   zLONG     lSelImageIdx = -1;
   zLONG     lRC          = -1;

   // If cpcEntityName is null, set Entity Name from current Entity.
   if ( cpcEntityName == 0 || cpcEntityName[ 0 ] == 0 )
      csEntityName = GetCurrentEntityName( );
   else
      csEntityName = cpcEntityName;

   // If Bitmap File Name is null, set Zeidon Default Bitmap.
   if ( cpcBitmapFileName == 0 || cpcBitmapFileName[ 0 ] == 0 )
      lImageListIdx = zTREE_STATE_CLOSE_IMG;

   if ( mIs_hWnd( m_hWnd ) )
   {
      for ( hItem = GetRootItem( );
            hItem;
            hItem = GetNextItemPhysical( hItem ) )
      {
         pNode = (ZOL_Node *) GetItemData( hItem );
         if ( pNode && pNode->m_csEntityName == csEntityName )
         {
            if ( lImageListIdx != zTREE_STATE_CLOSE_IMG )
            {
               if ( lImageListIdx == -1 )
               {
                  lImageListIdx = GetBitmapIdFromImageList( hItem, cpcBitmapFileName, FALSE );
                  if ( lImageListIdx < 0 )
                  {
                     lImageListIdx = LoadBitmapWithResourcePath( hItem, cpcBitmapFileName, FALSE );
                     if ( lImageListIdx < 0 )
                        break;
                  }
               }

               pNode->m_lUseDefaultBitmap = 0;
               pNode->m_csDefaultBitmapFile = cpcBitmapFileName;
            }
            else
            {
               pNode->m_lUseDefaultBitmap = 1;
               pNode->m_csDefaultBitmapFile = "";
            }

            if ( lSelImageIdx == -1 )
            {
               if ( pNode->m_lUseSelectedBitmap == 1 ||
                    pNode->m_csSelectedBitmapFile.IsEmpty( ) )
               {
                  lSelImageIdx = zTREE_STATE_OPEN_IMG;
               }
               else
               {
                  lSelImageIdx = GetBitmapIdFromImageList( hItem,
                                                           pNode->m_csSelectedBitmapFile, TRUE );
               }
            }

            SetItemImage( hItem, lImageListIdx, lSelImageIdx );
            pNodeFound = pNode;
         } // end:  if ( pNode && pNode->m_csEntityName == csEntityName )
      } // end:  for ( hItem = GetRootItem( )

      if ( pNodeFound )
      {
         lRC = 0;
         SetNewFontColorBitmapBlob( pNodeFound, csEntityName );
         Invalidate( TRUE );
      }

      if ( (hItem = GetSelectedItem( )) != 0 )
         EnsureVisible( hItem );
   }

   AfxSetResourceHandle( hInstance );
   return( lRC );
}

zLONG
ZMSTree::SetSelectedBitmap( zCPCHAR cpcEntityName,
                            zCPCHAR cpcBitmapFileName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetSelectedBitmap: ", *m_pzsTag );
#endif
   if ( m_bNoImage )
      return( -1 );

   // If someone is using the Window Postbuild Event with a Tree Control,
   // then the mapping will not be there and the Tree Function will not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   HINSTANCE hInstance = AfxGetResourceHandle( );
   AfxSetResourceHandle( g_hInstanceDLL );

   HTREEITEM hItem        = 0;
   ZOL_Node  *pNode       = 0;
   ZOL_Node  *pNodeFound  = 0;
   CString   csEntityName = "";
   zLONG     lImageListIdx = -1;
   zLONG     lSelImageIdx = -1;
   zLONG     lRC          = -1;

   // If cpcEntityName is null, set Entity Name from current Entity.
   if ( cpcEntityName == 0 || cpcEntityName[ 0 ] == 0 )
      csEntityName = GetCurrentEntityName( );
   else
      csEntityName = cpcEntityName;

   // If Bitmap File Name is null, set Zeidon Default Bitmap.
   if ( cpcBitmapFileName == 0 || cpcBitmapFileName[ 0 ] == 0 )
      lSelImageIdx = zTREE_STATE_OPEN_IMG;

   if ( mIs_hWnd( m_hWnd ) )
   {
      for ( hItem = GetRootItem( );
            hItem;
            hItem = GetNextItemPhysical( hItem ) )
      {
         pNode = (ZOL_Node *) GetItemData( hItem );
         if ( pNode && pNode->m_csEntityName == csEntityName )
         {
            if ( lSelImageIdx != zTREE_STATE_OPEN_IMG )
            {
               if ( lSelImageIdx == -1 )
               {
                  lSelImageIdx = GetBitmapIdFromImageList( hItem, cpcBitmapFileName, TRUE );
                  if ( lSelImageIdx < 0 )
                  {
                     lSelImageIdx = LoadBitmapWithResourcePath( hItem, cpcBitmapFileName, TRUE );
                     if ( lSelImageIdx < 0 )
                        break;
                  }
               }

               pNode->m_lUseSelectedBitmap = 0;
               pNode->m_csSelectedBitmapFile = cpcBitmapFileName;
            }
            else
            {
               pNode->m_lUseSelectedBitmap = 1;
               pNode->m_csSelectedBitmapFile = "";
            }

            if ( lImageListIdx == -1 )
            {
               if ( pNode->m_lUseDefaultBitmap == 1 ||
                    pNode->m_csDefaultBitmapFile.IsEmpty( ) )
               {
                  lImageListIdx = zTREE_STATE_CLOSE_IMG;
               }
               else
               {
                  lImageListIdx = GetBitmapIdFromImageList( hItem,
                                                            pNode->m_csDefaultBitmapFile, FALSE );
               }
            }

            SetItemImage( hItem, lImageListIdx, lSelImageIdx );
            pNodeFound = pNode;
         } // end:  if ( pNode && pNode->m_csEntityName == csEntityName )
      } // end:  for ( hItem = GetRootItem( )

      if ( pNodeFound )
      {
         lRC = 0;
         SetNewFontColorBitmapBlob( pNodeFound, csEntityName );
         Invalidate( TRUE );
      }

      if ( hItem = GetSelectedItem( ) )
         EnsureVisible( hItem );
   }

   AfxSetResourceHandle( hInstance );
   return( lRC );
}

zLONG
ZMSTree::SetBackgroundColor( COLORREF clrBackground )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetBackgroundColor: ", *m_pzsTag );
#endif
   zLONG clrBackgroundOld = m_clrBackground;

   m_clrBackground = clrBackground;
   Invalidate( TRUE );

   return( clrBackgroundOld );
}

zLONG
ZMSTree::SetTextColorForCurrentItem( COLORREF clrTextColor )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetTextColorForCurrentItem: ", *m_pzsTag );
#endif
   HTREEITEM hItem = GetSelectedItem( );

   if ( hItem )
   {
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );

      if ( pNode == 0 )
         return( -1 );

      pNode->m_TextColor = clrTextColor;

      SetItemColor( hItem, clrTextColor );
      CString csItemText = GetItemText( hItem );

      zLONG lOldColor = SetNewFontColorBitmapBlob( pNode, csItemText );

      Invalidate( TRUE );
      return( lOldColor );
   }

   return( -1 );
}

zLONG
ZMSTree::GetTextColorForEntity( zCPCHAR cpcEntityName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetTextColorForEntity: ", *m_pzsTag );
#endif
   zLONG     lColor       = -1;
   CString   csEntityName = "";

   csEntityName = cpcEntityName;

   if ( IsDesignTime( ) )
   {
      HTREEITEM hItem = GetSelectedItem( );
      if ( hItem )
         lColor = GetItemColor( hItem );

      return( lColor );
   }

   zPCHAR           pchItemColorFontImage;
   zLONG            lSize  = -1;
   zBOOL            bFound = FALSE;
   zLPOL_COLOR_FONT OL_ItemColorFontImage;

   // If cpcEntityName is null, set Entity Name from current Entity.
   if ( cpcEntityName == 0 || cpcEntityName[ 0 ] == 0 )
      csEntityName = GetCurrentEntityName( );
   else
      csEntityName = cpcEntityName;

   if ( m_pchFontColorBitmapBlob )
      pchItemColorFontImage = m_pchFontColorBitmapBlob;

   while ( bFound == FALSE && lSize < m_lFontColorBitmapBlobSize - 1 )
   {
      OL_ItemColorFontImage = (zLPOL_COLOR_FONT) pchItemColorFontImage;
      if ( zstrcmp( OL_ItemColorFontImage->szEntityName, csEntityName.GetString() ) == 0 )
      {
         bFound = TRUE;
         lColor = OL_ItemColorFontImage->clrTextColor;
      }

      pchItemColorFontImage += sizeof( zTREE_COLOR_FONT );
      lSize += sizeof( zTREE_COLOR_FONT );

   } // endwhile ( bFound && lSize < m_lFontColorBitmapBlobSize - 1 )

   return( lColor );
}

zLONG
ZMSTree::SetTxtItemColorText( zCPCHAR cpcItemText,
                                 COLORREF clrTextColor,
                                 zBOOL bEnsureVisible )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetTxtItemColorText: ", *m_pzsTag );
#endif
   zLONG     lOldColor = -1;
   CString   csItemText;
   HTREEITEM hItem;
   ZOL_Node  *pNode;

   // If someone is using the Window Postbuild Event with a Tree Control,
   // then the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   for ( hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      csItemText = GetItemText( hItem );
      if ( csItemText == cpcItemText )
      {
         pNode = (ZOL_Node *) GetItemData( hItem );
         pNode->m_TextColor = clrTextColor;
         SetItemColor( hItem, clrTextColor );
         lOldColor = 1;

         if ( bEnsureVisible )
            EnsureVisible( hItem );
       }
   }

   if ( hItem = GetSelectedItem( ) )
      EnsureVisible( hItem );

   if ( lOldColor == 1 )
      Invalidate( TRUE );

   return( lOldColor );
}

void
ZMSTree::RemoveAllTextColorsForItemText( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::RemoveAllTextColorsForItemText: ", *m_pzsTag );
#endif
   if ( m_arrItemColorText.GetSize( ) > 0 )
   {
      zLONG            lSize  = -1;
      zPCHAR           pchItemColorFontImage;
      zLPOL_COLOR_FONT OL_ItemColorFontImage;

      if ( m_pchFontColorBitmapBlob )
         pchItemColorFontImage = m_pchFontColorBitmapBlob;

      while ( lSize < m_lFontColorBitmapBlobSize - 1 )
      {
         OL_ItemColorFontImage = (zLPOL_COLOR_FONT) pchItemColorFontImage;
         SetTextColorForEntity( OL_ItemColorFontImage->szEntityName,
                                OL_ItemColorFontImage->clrTextColor );

         pchItemColorFontImage += sizeof( zTREE_COLOR_FONT );
         lSize += sizeof( zTREE_COLOR_FONT );
      }
   }

   m_arrItemColorText.RemoveAll( );
}

// lFlags - 0 - first remove all select states
//          1 - do not remove all select states
//          2 - do not map
//          4 - reset hilite based on select states
//          8 - turn off hilite for specified entity
//         16 - cause current item to be re-selected
//         32 - refresh control and select item associated
//              with entity's current cursor pos.
//         64 - close all nodes except the specified item
zSHORT
ZMSTree::SelectItemAtPosForEntity( zCPCHAR cpcEntityName, zLONG lFlags )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SelectItemAtPosForEntity: ", *m_pzsTag );
#endif

   // Do not permit recursive calls to this method.
   if ( mIs_hWnd( m_hWnd ) == 0 ||
        GetViewByName( &m_vApp, m_csTreeViewName,
                       m_vSubtask, zLEVEL_SUBTASK ) <= 0 ||
        ((cpcEntityName && *cpcEntityName) &&
         (IsMappedEntity( cpcEntityName ) == FALSE ||
          CheckExistenceOfEntity( m_vApp, cpcEntityName ) < zCURSOR_SET)) )
   {
      return( -1 );
   }

   if ( lFlags & 0x00000020 )
   {
      zULONG ulKey = GetEntityKey( m_vApp, cpcEntityName );
      zULONG ulMapActFlags = m_ulMapActFlags;
      mDeleteInit( m_pRootEntry );
      m_ulMapActFlag2 |= zMAPACT_MAPPING_FROM_OI; // trick OnSel to skip processing
      MapFromOI( );
      ResetViewForDefaultSelectSet( m_vApp );
      DeselectAllEntities( );
      OL_SetCursorByEntityNumber( m_vApp, cpcEntityName, ulKey );
      ZOL_Node *pNode = m_pRootEntry->FindNodeByEntityKey( ulKey );
      if ( pNode && pNode->m_hItem )
      {
      // TraceLine( "ZMSTree::SelectItemAtPosForEntity selecting hItem: 0x%08x",
      //            pNode->m_hItem );
         Select( pNode->m_hItem, TVGN_CARET );
      }

      if ( lFlags & 0x00000040 )
      {
         ExpandCollapseAll( 0, TVE_COLLAPSE );

         // After ExpandCollapseAl, we could lose the node/hItem relationship,
         // so we need to be sure we can relocate the node we had.
         pNode = m_pRootEntry->FindNodeByEntityKey( ulKey );
         if ( pNode && pNode->m_hItem )
            ItemExpand( pNode->m_hItem, TVE_EXPAND );
      }

      m_ulMapActFlags = ulMapActFlags;
      return( 0 );
   }

   if ( (lFlags & 1) == 0 )
   {
      if ( cpcEntityName && *cpcEntityName )
         SetAllSelectStatesForEntity( m_vApp, cpcEntityName, 0, "" );

      if ( lFlags & 4 )
      {
         // This can be time consuming for very large trees.
         for ( HTREEITEM hItem = GetRootItem( );
               hItem;
               hItem = GetNextItemPhysical( hItem ) )
         {
            SetItemState( hItem, 0, TVIS_SELECTED );
         }
      }
   }

   if ( cpcEntityName && *cpcEntityName )
   {
      zBOOL bSelect = (lFlags & 8) ? FALSE : TRUE;
      SetSelectStateOfEntity( m_vApp, cpcEntityName, bSelect );
      zULONG ulKey = GetEntityKey( m_vApp, cpcEntityName );
      if ( ulKey )
      {
         UINT uState = bSelect ? TVIS_SELECTED : 0;
         ZOL_Node *pNode = m_pRootEntry->FindNodeByEntityKey( ulKey );
         if ( pNode )
         {
            if ( SetItemState( pNode->m_hItem, uState, TVIS_SELECTED ) == 0 )
            {
               ASSERT( GetItemState( pNode->m_hItem, TVIS_SELECTED ) == uState );
            }
         }
      }
   }

   if ( lFlags & 0x00000010 )
   {
      HTREEITEM hItem = GetSelectedItem( );
      if ( hItem )
         Select( hItem, TVGN_CARET );
   }

   if ( (lFlags & 2) == 0 )
   {
      mDeleteInit( m_pRootEntry );
      MapFromOI( );
   }

   return( 0 );
}

zLONG
ZMSTree::SetTextForCurrentItem( zCPCHAR cpcItemText )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetTextForCurrentItem: ", *m_pzsTag );
#endif

// HTREEITEM hItem = GetSelectedItem( );
   zULONG ulEntityKey = GetSelectedNodeEntityKey( );
   BOOL bRC = -1;

   if ( ulEntityKey > 0 )
   {
      bRC = 1;
      for ( HTREEITEM hItem = GetRootItem( );
            hItem;
            hItem = GetNextItemPhysical( hItem ) )
      {
         ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );
         if ( pNode && pNode->m_ulEntityKey == ulEntityKey )
         {
         // CString csItemText = GetItemText( hItem );
         // TraceLine( "ZMSTree::SetTextForCurrentItem Old Text: %s      Text: %s   Key: %d  Entity: %s",
         //            csItemText, cpcItemText, ulEntityKey, pNode->m_csEntityName );

            bRC = !SetItemText( hItem, cpcItemText );
            if ( bRC )
               break;  // some kind of error has occurred
         }
      }
   }

   return( bRC );
}

zLONG
ZMSTree::SetTextItemColorText( zCPCHAR     cpcItemText,
                                  COLORREF clrTextColor,
                                  zBOOL    bEnsureVisible )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetTextItemColorText: ", *m_pzsTag );
#endif
   zLONG         lOldColor  = -1;
   zBOOL         bTextFound = FALSE;
   ItemColorText ct;

   lOldColor = SetTxtItemColorText( cpcItemText, clrTextColor, bEnsureVisible );

   // Search Text in Array.
   if ( m_arrItemColorText.GetSize( ) > 0 )
   {
      for ( int k = 0; k < m_arrItemColorText.GetSize( ); k++ )
      {
         ct = m_arrItemColorText.GetAt( k );
         if ( ct.csItemText == cpcItemText )
         {
            bTextFound = TRUE;
            ct.clrTextColor = clrTextColor;
            m_arrItemColorText.SetAt( k, ct );
         }
      }
   }

   if ( bTextFound == FALSE )
   {
      // save Color for Item Text
      ct.csItemText = cpcItemText;
      ct.clrTextColor = clrTextColor;
      m_arrItemColorText.Add( ct );
   }

   return( lOldColor );
}

zLONG
ZMSTree::SetTextColorForEntity( zCPCHAR cpcEntityName, COLORREF clrTextColor )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetTextColorForEntity: ", *m_pzsTag );
#endif
   zLONG     lOldColor    = -1;
   HTREEITEM hItem;
   ZOL_Node  *pNode;
   ZOL_Node  *pNodeFound  = 0;
   CString   csEntityName = "";

   // If somebody using the Window Postbuild Event with a Tree Control,
   // than the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   csEntityName = cpcEntityName;

   if ( IsDesignTime( ) )
   {
      lOldColor = SetTextColorForCurrentItem( clrTextColor );
      return( lOldColor );
   }

   // If cpcEntityName is null, set Entity Name from current Entity.
   if ( cpcEntityName == 0 || cpcEntityName[ 0 ] == 0 )
      csEntityName = GetCurrentEntityName( );
   else
      csEntityName = cpcEntityName;

   for ( hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      pNode = (ZOL_Node *) GetItemData( hItem );
      if ( pNode && pNode->m_csEntityName == csEntityName )
      {
         pNode->m_TextColor = clrTextColor;
         SetItemColor( hItem, clrTextColor );
         pNodeFound = pNode;
      }
   }

   if ( pNodeFound )
   {
      lOldColor = SetNewFontColorBitmapBlob( pNodeFound, csEntityName );
      Invalidate( TRUE );
   }

   if ( hItem = GetSelectedItem( ) )
      EnsureVisible( hItem );

   return( lOldColor );
}

zLONG
ZMSTree::SetNewFontColorBitmapBlob( ZOL_Node *pNode, CString csEntityName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetNewFontColorBitmapBlob: ", *m_pzsTag );
#endif
   CString          csText;
   zPCHAR           pchItemColorFontImage;
   zLONG            lSize     = -1;
   zLONG            lOldColor = -1;
   zLPOL_COLOR_FONT OL_ItemColorFontImage;

   pchItemColorFontImage = m_pchFontColorBitmapBlob;

   while ( lSize < m_lFontColorBitmapBlobSize -1 )
   {
      OL_ItemColorFontImage = (zLPOL_COLOR_FONT) pchItemColorFontImage;
      csText.Empty( );

      if ( IsDesignTime( ) )
      {
         // If Option Show Entity Name active.
         if ( (m_lStyle & zTREES_NOSHOW_ENTITY) == 0 )
         {
            csText = pNode->m_csEntityName;
            if ( !csText.IsEmpty( ) )
               csText += " ";
         }
      }

      csText += OL_ItemColorFontImage->szEntityName;

      if ( zstrcmp( csText.GetString(), csEntityName.GetString() ) == 0 )
      {
         lOldColor = OL_ItemColorFontImage->clrTextColor;
         OL_ItemColorFontImage->clrTextColor = pNode->m_TextColor;
         OL_ItemColorFontImage->fntTextFont = pNode->m_TextFont;
         OL_ItemColorFontImage->lUseDefaultBitmap = pNode->m_lUseDefaultBitmap;
         OL_ItemColorFontImage->lUseSelectedBitmap = pNode->m_lUseSelectedBitmap;
         strcpy_s( OL_ItemColorFontImage->szDefaultBitmapFile, zsizeof( OL_ItemColorFontImage->szDefaultBitmapFile ), pNode->m_csDefaultBitmapFile );
         strcpy_s( OL_ItemColorFontImage->szSelectedBitmapFile, zsizeof( OL_ItemColorFontImage->szSelectedBitmapFile ), pNode->m_csSelectedBitmapFile );
      }

      pchItemColorFontImage += sizeof( zTREE_COLOR_FONT );
      lSize += sizeof( zTREE_COLOR_FONT );
   } // endwhile ( bFound && pchItemColorFontImage )

   return( lOldColor );
}

zLONG
ZMSTree::SetSingleExpand( zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetSingleExpand: ", *m_pzsTag );
#endif
   zLONG lRC = -1;

   // if MultiSelect active, do not set SingleExpand
   if ( ulValue && CanMultiSelect( ) )
      return( lRC );

   // If somebody using the Window Postbuild Event with a Tree Control,
   // than the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   HTREEITEM hSelItem = 0;

   // Save selected Item and Collapse all Tree Items.
   if ( ulValue )
   {
      m_lStyle &= ~zTREES_OPENALLCHILDREN;
      m_dwStyle |= TVS_SINGLEEXPAND;
      hSelItem = GetSelectedItem( );
      ExpandCollapseAll( 0, TVE_COLLAPSE );
   }
   else
   {
      m_dwStyle &= ~TVS_SINGLEEXPAND;
   }

   lRC = SetNewStyle( TVS_SINGLEEXPAND, ulValue );

   // Open current Tree Item.
   if ( ulValue && hSelItem )
   {
      EnsureVisible( hSelItem );
      if ( IsDesignTime( ) )
      {
         SetSelectionForDesignTime( 0, hSelItem );
      }
      else
      {
         SetItemSelState( hSelItem, TVIS_SELECTED, TVIS_SELECTED );
         SelectItem( hSelItem );
      }
   }

   return( lRC );
}

zLONG
ZMSTree::SetExpand( zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetExpand: ", *m_pzsTag );
#endif
   // If somebody using the Window Postbuild Event with a Tree Control,
   // than the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   zLONG     lRC = -1;
   HTREEITEM hSelItem = GetSelectedItem( );

   if ( hSelItem == 0 )
   {
      hSelItem = GetFirstSelectedItem( );
      if ( hSelItem == 0 )
         return( lRC );
   }

   if ( ulValue )
      lRC = ItemExpand( hSelItem, TVE_EXPAND );
   else
      lRC = ItemExpand( hSelItem, TVE_COLLAPSE );

   return( lRC );
}

zLONG
ZMSTree::SetExpandAll( zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetExpandAll: ", *m_pzsTag );
#endif
   zLONG lRC = -1;

   // If somebody using the Window Postbuild Event with a Tree Control,
   // than the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   lRC = (m_lStyle & zTREES_OPENALLCHILDREN);

   if ( ulValue )
   {
      m_lStyle |= zTREES_OPENALLCHILDREN;
      m_dwStyle &= ~TVS_SINGLEEXPAND;
      SetSingleExpand( FALSE );
      ExpandCollapseAll( 0, TVE_EXPAND );
   }
   else
   {
      m_lStyle &= ~zTREES_OPENALLCHILDREN;
      ExpandCollapseAll( 0, TVE_COLLAPSE );
   }

   HTREEITEM hItem = GetSelectedItem( );
   if ( hItem )
      EnsureVisible( hItem );

   return( lRC );
}

zLONG
ZMSTree::SetShowEntity( zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetShowEntity: ", *m_pzsTag );
#endif
   zLONG lRC = -1;

   lRC = (m_lStyle & zTREES_NOSHOW_ENTITY);

   if ( ulValue )
      m_lStyle |= zTREES_NOSHOW_ENTITY;
   else
      m_lStyle &= ~zTREES_NOSHOW_ENTITY;

   mDeleteInit( m_pRootEntry );
   MapFromOI( );

   return( lRC );
}

zLONG
ZMSTree::SetMultipleRoot( zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetMultipleRoot: ", *m_pzsTag );
#endif
   zLONG lRC = 0;

   // Tree type 0 ==> MultiRoot ... 1 ==> SingleRoot
   if ( m_nType == zTREE_TYPE_MULTIROOT )
      lRC = 1;

   if ( ulValue )
      m_nType = zTREE_TYPE_MULTIROOT;
   else
      m_nType = zTREE_TYPE_SINGLEROOT;

   mDeleteInit( m_pRootEntry );
   MapFromOI( );

   return( lRC );
}

zLONG
ZMSTree::SetMultiSelect( zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetMultiSelect: ", *m_pzsTag );
#endif
   zLONG lRC = 0;

   lRC = (m_lStyle & zTREES_MULTISEL);

   if ( ulValue )
   {
      m_lStyle |= zTREES_MULTISEL;
      m_dwStyle &= ~TVS_SINGLEEXPAND;
      SetSingleExpand( FALSE );
   }
   else
   {
      m_lStyle &= ~zTREES_MULTISEL;
   }

   return( lRC );
}

HTREEITEM
ZMSTree::GetItemHandle( zVIEW vApp, zCPCHAR cpcEntityName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetItemHandle: ", *m_pzsTag );
#endif
   HTREEITEM hItem = 0;
   zULONG    ulEntityKey = 0;

   OL_GetCurrentEntityNumber( vApp, cpcEntityName, &ulEntityKey );
   if ( ulEntityKey )
   {
      ZOL_Node *pNode = m_pRootEntry->FindNodeByEntityKey( ulEntityKey );

      if ( pNode )
         hItem = pNode->m_hItem;
   }

   return( hItem );
}

// Sort the item in reverse alphabetical order.
static int CALLBACK
SortCompareAlphaDescending( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
   // lParamSort contains a pointer to the tree control.
   // The lParam of an item is the ZOL_Node pointer.
   ZMSTree *pTree = (ZMSTree *) lParamSort;
   ZOL_Node    *pNode1 = (ZOL_Node *) lParam1;
   ZOL_Node    *pNode2 = (ZOL_Node *) lParam2;
   CString     csItem1 = pTree->GetItemText( pNode1->m_hItem );
   CString     csItem2 = pTree->GetItemText( pNode2->m_hItem  );

// TraceLine( "Sorting Item1 (0x%08x): %s   Item2 (0x%08x): %s: ",
//            pNode1->m_hItem, csItem1, pNode2->m_hItem, csItem2 );
   return( zstrcmp( csItem2.GetString(), csItem1.GetString() ) );
}

//  ulFlag - 0 deselect specified item
//         - 1 select specified item
//         - 2 close tree prior to select
//         - 4 sort ascending within parent item
//         - 8 sort descending within parent item
zLONG
ZMSTree::SelectEntityItem( zCPCHAR cpcEntityName,
                           zULONG ulEntityKey, zULONG ulFlag )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SelectEntityItem: ", *m_pzsTag );
#endif
   // If somebody is using the Window Postbuild Event with a Tree Control,
   // then the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   if ( GetViewByName( &m_vApp, m_csTreeViewName,
                       m_vSubtask, zLEVEL_SUBTASK ) < 0 ||
        IsMappedEntity( cpcEntityName ) == FALSE ||
        CheckExistenceOfEntity( m_vApp, cpcEntityName ) < zCURSOR_SET )
   {
      return( -1 );
   }

   HTREEITEM hItem = 0; // GetItemHandle( m_vApp, cpcEntityName );
   ZOL_Node *pNode = m_pRootEntry->FindNodeByEntityKey( ulEntityKey );
   if ( pNode )
      hItem = pNode->m_hItem;

   if ( hItem == 0 )
      return( -1 );

   HTREEITEM hRootItem = GetRootItem( );
   if ( hRootItem && (ulFlag & 0x00000002) ) // root item must exist, but ...
      Expand( hRootItem, TVE_COLLAPSE );

   if ( IsCancelByPreSelChangeAction( hItem ) )
      return( -1 );

   if ( ulFlag & 0x00000001 )
   {
      SelectSetFirstVisible( hItem );
   }
   else
   {
      SelectItem( 0 );
   }

   if ( ulFlag & 0x0000000C )
   {
      HTREEITEM hParentItem = GetParentItem( hItem );

      if ( ulFlag & 0x00000004 )
      {
         if ( hParentItem == 0 )
            hParentItem = TVI_ROOT;

         SortChildren( hParentItem );
      }
      else
   // if ( ulFlag & 0x00000008 )
      {
         TVSORTCB tvs;
         if ( hParentItem )
         {
            tvs.hParent = hParentItem;
            CString csItem = GetItemText( hParentItem );
         // TraceLineS( "Sorting Tree on Parent item: ", csItem );
         // ListAllItems( "ZMSTree::SelectEntityItem Parent Item:", hParentItem );
         }
         else
         {
            tvs.hParent = TVI_ROOT;
         // TraceLineS( "Sorting Tree on ROOT item", "" );
         }

      // ListAllItems( "ZMSTree::SelectEntityItem Sorting" );

         // Sort the tree control's items using callback procedure.
         tvs.lpfnCompare = SortCompareAlphaDescending;  // callback
         tvs.lParam = (LPARAM) this;

         SortChildrenCB( &tvs );
      }

      Invalidate( );
   }

   return( 0 );
}

zLONG
ZMSTree::SelectItemByAttribute( zCPCHAR cpcEntityName,
                                zCPCHAR cpcAttribName,
                                zCPCHAR cpcFindString,
                                zULONG  ulEntityKey,
                                zULONG  ulFlag )
{
   // If somebody is using the Window Postbuild Event with a Tree Control,
   // then the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   HTREEITEM hItem = 0;
   ZOL_Node *pNode = 0;
   zPCHAR pch;
   zPCHAR pchComma;
   zPCHAR pchValue;
   zBOOL  bFound = FALSE;

   if ( (ulFlag & 0x00000001) && ulEntityKey )
   {
      pNode = m_pRootEntry->FindNodeByEntityKey( ulEntityKey );
      if ( pNode )
         hItem = GetNextItemPhysical( pNode->m_hItem );
   }

   if ( hItem == 0 )
      hItem = GetRootItem( );

   while ( hItem )
   {
      pNode = (ZOL_Node *) GetItemData( hItem );
      if ( SetEntityCursor( m_vApp, cpcEntityName, 0,
                            zQUAL_ENTITYKEY | zPOS_FIRST | zRECURS,
                            (zCPVOID) &(pNode->m_ulEntityKey),
                            0, 0, 0, 0, 0 ) >= zCURSOR_SET )
      {
         pch = (zPCHAR) cpcAttribName;
         while ( pch )
         {
            pchComma = zstrchr( pch, ',' );
            if ( pchComma )
               *pchComma = 0;

            GetAddrForAttribute( &pchValue, m_vApp, cpcEntityName, pch );
            if ( *pchValue && zstrstr( pchValue, cpcFindString ) )
            {
               if ( pchComma )
                  *pchComma = ',';

            // SelectEntityItem( cpcEntityName, pNode->m_ulEntityKey, 1 );
            // SelectItemAtPosForEntity( cpcEntityName, 2 + 4 + 16 + 32 );
               return( pNode->m_ulEntityKey );
            }

            if ( pchComma )
            {
               *pchComma = ',';
               pch = pchComma + 1;
            }
            else
               pch = 0;
         }
      }

      hItem = GetNextItemPhysical( hItem );
   }

   return( 0 );
}

zLONG
ZMSTree::GetExpandState( zCPCHAR cpcEntityName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetExpandState: ", *m_pzsTag );
#endif
   if ( GetViewByName( &m_vApp, m_csTreeViewName,
                       m_vSubtask, zLEVEL_SUBTASK ) < 0 ||
        IsMappedEntity( cpcEntityName ) == FALSE )
   {
      return( -1 );
   }

   if ( CheckExistenceOfEntity( m_vApp, cpcEntityName ) >= zCURSOR_SET )
   {
      HTREEITEM hItem = GetItemHandle( m_vApp, cpcEntityName );

      if ( hItem )
         return( (GetItemState( hItem, TVIS_EXPANDED ) & TVIS_EXPANDED) ? TRUE : FALSE );
   }

   return( -1 );
}

zLONG
ZMSTree::SetExpandStatusForEntity( zCPCHAR cpcEntityName, zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetExpandStatusForEntity: ", *m_pzsTag );
#endif
   HTREEITEM hItem;
   ZOL_Node  *pNode;
   zLONG     lRC = -1;
   zULONG    ulExpand;

   if ( ulValue == zEXPANDALL )
      ulExpand = TVE_EXPAND;
   else
      ulExpand = TVE_COLLAPSE;

   for ( hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      pNode = (ZOL_Node *) GetItemData( hItem );
      if ( pNode && pNode->m_csEntityName == cpcEntityName )
      {
         lRC = (zLONG) ItemExpand( hItem, ulExpand );
      }
   }

   if ( hItem = GetSelectedItem( ) )
      EnsureVisible( hItem );

   return( lRC );
}

zLONG
ZMSTree::ExpandEntity( zCPCHAR cpcEntityName, zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::ExpandEntity: ", *m_pzsTag );
#endif
   // If somebody using the Window Postbuild Event with a Tree Control,
   // than the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   if ( GetViewByName( &m_vApp, m_csTreeViewName,
                       m_vSubtask, zLEVEL_SUBTASK ) < 0 ||
        IsMappedEntity( cpcEntityName ) == FALSE )
   {
      return( -1 );
   }

   zLONG  lRC = -1;

   switch ( ulValue )
   {
      case zEXPAND:
      case zCOLLAPSE:
      {
         if ( CheckExistenceOfEntity( m_vApp, cpcEntityName ) >= zCURSOR_SET )
         {
            HTREEITEM hItem = GetItemHandle( m_vApp, cpcEntityName );

            if ( ulValue == zEXPAND )
               lRC = (zLONG) ItemExpand( hItem, TVE_EXPAND );
            else
               lRC = (zLONG) ItemExpand( hItem, TVE_COLLAPSE );
         }

         break;
      }
      case zEXPANDALL:
      case zCOLLAPSEALL:
      {
         lRC = SetExpandStatusForEntity( cpcEntityName, ulValue );
         break;
      }
      default:
         lRC = -1;
   }

   return( lRC );
}

zLONG
ZMSTree::SetZCtrlState( zLONG lStatusType, zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetZCtrlState ", *m_pzsTag );
   TraceLineX( "ZMSTree::SetZCtrlState lStatusType: ", lStatusType );
#endif

   zLONG lRC = 0;

   switch ( lStatusType )
   {
      case zCONTROL_STATUS_DISABLE_READONLY:
         lRC = SetNewStyle( TVS_EDITLABELS, !ulValue );
         break;

      case zCONTROL_STATUS_HASBUTTONS:
         lRC = SetNewStyle( TVS_HASBUTTONS, ulValue );
         break;

      case zCONTROL_STATUS_HASLINES:
         lRC = SetNewStyle( TVS_HASLINES, ulValue );
         break;

      case zCONTROL_STATUS_LINESATROOT:
         lRC = SetNewStyle( TVS_LINESATROOT, ulValue );
         break;

      case zCONTROL_STATUS_DISABLEDRAGDROP:
         lRC = SetNewStyle( TVS_DISABLEDRAGDROP, ulValue );
         break;

      case zCONTROL_STATUS_SINGLEEXPAND:
         lRC = SetSingleExpand( ulValue );
         break;

      case zCONTROL_STATUS_EXPAND:
         lRC = SetExpand( ulValue );
         break;

      case zCONTROL_STATUS_EXPANDALL:
         lRC = SetExpandAll( ulValue );
         break;

      case zCONTROL_STATUS_NOSHOW_ENTITY:
         lRC = SetShowEntity( ulValue );
         break;

      case zCONTROL_STATUS_MULTIPLEROOT:
         lRC = SetMultipleRoot( ulValue );
         break;

      case zCONTROL_STATUS_MULTISELECT:
         lRC = SetMultiSelect( ulValue );
         break;

      case zCONTROL_STATUS_BACKGROUND_COLOR:
         lRC = SetBackgroundColor( ulValue );
         break;

      case zCONTROL_STATUS_ENABLED:
         if ( ulValue == 0 )
         {
            if ( m_clrBackgroundOld != zTREE_COLOR_GRAY )
               m_clrBackgroundOld = m_clrBackground;

            SetBackgroundColor( zTREE_COLOR_GRAY ); // set gray to Background color
         }
         else
         if ( m_clrBackgroundOld != -1 )
            SetBackgroundColor( m_clrBackgroundOld );

      default:
         return( ZMapAct::SetZCtrlState( lStatusType, ulValue ) );
   }

   return( lRC );
}

zLONG
ZMSTree::GetZCtrlState( zLONG lStatusType )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetZCtrlState ", *m_pzsTag );
   TraceLineX( "ZMSTree::GetZCtrlState lStatusType: ", lStatusType );
#endif

   switch ( lStatusType )
   {
      case zCONTROL_STATUS_DISABLE_READONLY:
         return( (m_dwStyle & TVS_EDITLABELS) ? TRUE : FALSE );

      case zCONTROL_STATUS_HASBUTTONS:
         return( (m_dwStyle & TVS_HASBUTTONS) ? TRUE : FALSE );

      case zCONTROL_STATUS_HASLINES:
         return( (m_dwStyle & TVS_HASLINES) ? TRUE : FALSE );

      case zCONTROL_STATUS_LINESATROOT:
         return( (m_dwStyle & TVS_LINESATROOT) ? TRUE : FALSE );

      case zCONTROL_STATUS_DISABLEDRAGDROP:
         return( (m_dwStyle & TVS_DISABLEDRAGDROP) ? TRUE : FALSE );

      case zCONTROL_STATUS_SINGLEEXPAND:
         return( (m_dwStyle & TVS_SINGLEEXPAND) ? TRUE : FALSE );

      case zCONTROL_STATUS_EXPAND:
      {
         HTREEITEM hItem = GetSelectedItem( );
         if ( hItem == 0 )
         {
            hItem = GetFirstSelectedItem( );
            if ( hItem == 0 )
               return( -1 );
         }

         return( (GetItemState( hItem, TVIS_EXPANDED ) & TVIS_EXPANDED) ? TRUE : FALSE );
      }

      case zCONTROL_STATUS_EXPANDALL:
         return( (m_lStyle & zTREES_OPENALLCHILDREN) ? TRUE : FALSE );

      case zCONTROL_STATUS_NOSHOW_ENTITY:
         return( (m_lStyle & zTREES_NOSHOW_ENTITY) ? TRUE : FALSE );

      case zCONTROL_STATUS_MULTIPLEROOT:
         return( (m_nType == zTREE_TYPE_MULTIROOT) ? TRUE : FALSE );

      case zCONTROL_STATUS_MULTISELECT:
         return( (m_lStyle & zTREES_MULTISEL) ? TRUE : FALSE );

      case zCONTROL_STATUS_BACKGROUND_COLOR:
         return( m_clrBackground );

      default:
        return( ZMapAct::GetZCtrlState( lStatusType ) );
   }
}

zLONG
ZMSTree::SetNewStyle( zLONG lStyleMask, zULONG ulValue )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetNewStyle: ", *m_pzsTag );
#endif
   zLONG lStyleOld;

   lStyleOld = GetWindowLong( m_hWnd, GWL_STYLE );
   lStyleOld &= ~lStyleMask;
   m_dwStyle &= ~lStyleMask;

   if ( ulValue )
   {
      lStyleOld |= lStyleMask;
      m_dwStyle |= lStyleMask;
   }

   SetWindowLong( m_hWnd, GWL_STYLE, lStyleOld );

   return( 0 );
}

zLONG
ZMSTree::SetTextFontForEntity( zCPCHAR cpcEntityName,
                               zLONG   lSize,
                               zLONG   lBold,
                               zLONG   lItalic,
                               zLONG   lUnderline,
                               zLONG   lStrikeout,
                               zLONG   lTextColor,
                               zLONG   lEscapement,
                               zPCHAR  pchFaceName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetTextFontForEntity: ", *m_pzsTag );
#endif
   zLONG    lRC, lRC1;
   LOGFONT  fntTextFont;

   // max Font Size = 16
   if ( lSize > 16 )
      lSize = 16;

   fntTextFont.lfHeight      = - lSize;
   fntTextFont.lfWidth       = 0;
   fntTextFont.lfEscapement  = lEscapement;
   fntTextFont.lfOrientation = 0;
   fntTextFont.lfWeight      = lBold ? FW_BOLD : FW_NORMAL;
   fntTextFont.lfItalic      = ( zCHAR ) lItalic;
   fntTextFont.lfUnderline   = ( zCHAR ) lUnderline;
   fntTextFont.lfStrikeOut   = ( zCHAR ) lStrikeout;
   fntTextFont.lfCharSet     = ANSI_CHARSET;
   fntTextFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
   fntTextFont.lfQuality       = PROOF_QUALITY;

   if ( pchFaceName )
      strcpy_s( fntTextFont.lfFaceName, zsizeof( fntTextFont.lfFaceName ), pchFaceName );

   lRC  = SetTxtFontForEntity( cpcEntityName, fntTextFont );
   lRC1 = SetTextColorForEntity( cpcEntityName, lTextColor );

   if ( lRC < 0 || lRC1 < 0 )
      return( -1 );
   else
      return( lRC1 );
}

zLONG
ZMSTree::GetTextFontForEntity( zCPCHAR  cpcEntityName,
                               zPLONG   plSize,
                               zPLONG   plBold,
                               zPLONG   plItalic,
                               zPLONG   plUnderline,
                               zPLONG   plStrikeout,
                               zPLONG   plTextColor,
                               zPLONG   plEscapement,
                               zPCHAR   pchFaceName )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetTextFontForEntity: ", *m_pzsTag );
#endif
   CString          csEntityName = "";
   LOGFONT          fntTextFont;
   zPCHAR           pchItemColorFontImage;
   zLONG            lSize  = -1;
   zBOOL            bFound = FALSE;
   zLPOL_COLOR_FONT OL_ItemColorFontImage;

   // If cpcEntityName is null, set Entity Name from current Entity.
   if ( cpcEntityName == 0 || cpcEntityName[ 0 ] == 0 )
      csEntityName = GetCurrentEntityName( );
   else
      csEntityName = cpcEntityName;

   if ( m_pchFontColorBitmapBlob )
      pchItemColorFontImage = m_pchFontColorBitmapBlob;

   while ( bFound == FALSE && lSize < m_lFontColorBitmapBlobSize - 1 )
   {
      OL_ItemColorFontImage = (zLPOL_COLOR_FONT) pchItemColorFontImage;

      if ( zstrcmp( OL_ItemColorFontImage->szEntityName, csEntityName.GetString() ) == 0 )
      {
         bFound = TRUE;
         fntTextFont = OL_ItemColorFontImage->fntTextFont;
         *plTextColor = OL_ItemColorFontImage->clrTextColor;
      }

      pchItemColorFontImage += sizeof( zTREE_COLOR_FONT );
      lSize += sizeof( zTREE_COLOR_FONT );

   } // endwhile ( bFound && lSize < m_lFontColorBitmapBlobSize - 1 )

   if ( bFound )
   {
      if ( zstrcmp( fntTextFont.lfFaceName, "" ) == 0 )
      {
         // Use window font.
         CFont *pFont = GetFont( );
         pFont->GetLogFont( &fntTextFont );
         fntTextFont.lfHeight = -fntTextFont.lfHeight;
      }

      *plSize       = -fntTextFont.lfHeight;
      *plItalic     = (zLONG) fntTextFont.lfItalic;
      *plUnderline  = (zLONG) fntTextFont.lfUnderline;
      *plStrikeout  = (zLONG) fntTextFont.lfStrikeOut;
      *plEscapement = fntTextFont.lfEscapement;

      if ( fntTextFont.lfWeight == FW_BOLD )
         *plBold = TRUE;
      else
         *plBold = FALSE;

      strcpy_s( pchFaceName, 32, fntTextFont.lfFaceName );

      return( 0 );
   }

   return( -1 );
}

CString
ZMSTree::GetCurrentEntityName( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetCurrentEntityName: ", *m_pzsTag );
#endif
   ZOL_Node  *pNode       = 0;
   CString   csEntityName = "";
   zBOOL     bFound       = FALSE;

   // Try to reposition at previous position
   if ( GetViewByName( &m_vApp, m_csTreeViewName, m_vSubtask, zLEVEL_SUBTASK ) < 0 )
      return( csEntityName );

   // Get Entity with last cursor changes.
   if ( m_szLastAccEntity[ 0 ] )
   {
      if ( CheckExistenceOfEntity( m_vApp, m_szLastAccEntity ) >= zCURSOR_SET )
      {
         zULONG ulEntityKey;

         OL_GetCurrentEntityNumber( m_vApp, m_szLastAccEntity, &ulEntityKey );
         if ( ulEntityKey )
         {
            ZOL_Node *pNode = m_pRootEntry->FindNodeByEntityKey( ulEntityKey );

            if ( pNode )
            {
               csEntityName = pNode->m_csEntityName;
               bFound = TRUE;
            }
         }
      }
   } // endif ( m_szLastAccEntity[ 0 ] )

   if ( bFound == FALSE )
   {
      HTREEITEM hItem = GetSelectedItem( );

      if ( hItem == 0 )
         hItem = GetFirstSelectedItem( );

      if ( hItem )
      {
         pNode = (ZOL_Node *) GetItemData( hItem );

         if ( pNode )
            csEntityName = pNode->m_csEntityName;
      }
   }

   return( csEntityName );
}

zLONG
ZMSTree::SetTxtFontForEntity( zCPCHAR cpcEntityName, LOGFONT fntTextFont )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetTxtFontForEntity: ", *m_pzsTag );
#endif
   zLONG     lOldColor = -1;
   HTREEITEM hItem;
   ZOL_Node  *pNode;
   ZOL_Node  *pNodeFound = 0;
   CString   csEntityName = "";

   // If somebody using the Window Postbuild Event with a Tree Control,
   // than the mapping will not be there and the Tree Function does not work.
   // Create Mapping.
   if ( m_pRootEntry == 0 )
      MapFromOI( );

   if ( IsDesignTime( ) )
   {
      lOldColor = SetTxtFontForCurrentItem( fntTextFont );
      return( lOldColor );
   }

   // If cpcEntityName is null, set Entity Name from current Entity.
   if ( cpcEntityName == 0 || cpcEntityName[ 0 ] == 0 )
      csEntityName = GetCurrentEntityName( );
   else
      csEntityName = cpcEntityName;

   for ( hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      pNode = (ZOL_Node *) GetItemData( hItem );
      if ( pNode && pNode->m_csEntityName == csEntityName )
      {
         pNode->m_TextFont = fntTextFont;
         SetItemFont( hItem, fntTextFont );
         pNodeFound = pNode;
      }
   }

   if ( pNodeFound )
   {
      lOldColor = SetNewFontColorBitmapBlob( pNodeFound, csEntityName );
      Invalidate( TRUE );
   }

   if ( hItem = GetSelectedItem( ) )
      EnsureVisible( hItem );

   return( lOldColor );
}

zLONG
ZMSTree::SetTxtFontForCurrentItem( LOGFONT fntTextFont )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetTxtFontForCurrentItem: ", *m_pzsTag );
#endif
   zLONG     lOldColor = -1;
   HTREEITEM hItem = GetSelectedItem( );

   if ( hItem )
   {
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );

      if ( pNode == 0 )
         return( -1 );

      pNode->m_TextFont = fntTextFont;

      SetItemFont( hItem, fntTextFont );
      CString csItemText = GetItemText( hItem );

      lOldColor = SetNewFontColorBitmapBlob( pNode, csItemText );

      Invalidate( TRUE );
      return( lOldColor );
   }

   return( -1 );
}

/////////////////////////////////////////////////////////////////////////////
// KRMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// This class implements a memory Device Context

class KRMemDC : public CDC
{
private:
   CBitmap *m_pBitmap;
   CBitmap *m_pOldBitmap;
   CDC     *m_pDC;
   CRect   m_rectBounds;
public:
   KRMemDC( CDC *pDC, const CRect& rectBounds ) : CDC( )
   {
      CreateCompatibleDC( pDC );
      m_pBitmap = new CBitmap;
      m_pBitmap->CreateCompatibleBitmap( pDC, rectBounds.Width( ),
                                         rectBounds.Height( ) );
      m_pOldBitmap = SelectObject( m_pBitmap );
      m_pDC = pDC;
      m_rectBounds = rectBounds;
   }

   ~KRMemDC( )
   {
      m_pDC->BitBlt( m_rectBounds.left, m_rectBounds.top,
                     m_rectBounds.Width( ), m_rectBounds.Height( ),
                    this, m_rectBounds.left, m_rectBounds.top, SRCCOPY );
      SelectObject( m_pOldBitmap );
      if ( m_pBitmap )
         delete( m_pBitmap );
   }

   KRMemDC * operator->()
   {
      return( this );
   }
};

#if 0
void
ZMSTree::OnPaint( )
{
   if ( (m_ulMapActFlag2 & zMAPACT_MAPPING_FROM_OI) || m_bSetMultiSelection )
      return;

// BLZ if Window 98, do not set colors (this is a workaround).
   OSVERSIONINFO  osvi;
   osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
   GetVersionEx( &osvi );
   zBOOL bIsWindows98orLater = (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
                               (osvi.dwMinorVersion > 0);

   if ( bIsWindows98orLater )
   {
      CTreeCtrl::OnPaint( );
      return;
   }
// End BLZ

   CPaintDC dc( this );

#if 0
   // Create a memory DC compatible with the paint DC.
   CDC memDC;
   CDC memDC_BkColor;
   memDC.CreateCompatibleDC( &dc );
   memDC_BkColor.CreateCompatibleDC( &dc );
#endif

   CRect rectClip;
   CRect rectClient;
   dc.GetClipBox( &rectClip );
   GetClientRect( &rectClient );
   KRMemDC memDC( &dc, rectClient );

#ifdef DEBUG_ALL
// TraceRect( "ZMSTree::OnPaint (before) Clip: ", rectClip );
#endif

#if 0
   // Select a compatible bitmap into the memory DC.
   if ( m_pBitmap1 == 0 )
   {
      m_pBitmap1 = new CBitmap;
      m_pBitmap1->CreateCompatibleBitmap( &dc, rectClient.Width( ),
                                          rectClient.Height( ) );
   }

   if ( m_pBitmap2 == 0 )
   {
      m_pBitmap2 = new CBitmap;
      m_pBitmap2->CreateCompatibleBitmap( &dc, rectClient.Width( ),
                                          rectClient.Height( ) );
   }

   CBitmap *pOldBitmap1 = memDC.SelectObject( m_pBitmap1 );
   CBitmap *pOldBitmap2 = memDC_BkColor.SelectObject( m_pBitmap2 );

   // Set clip region to be same as that in paint DC
   CRgn rgn;
   rgn.CreateRectRgnIndirect( &rectClip );
   memDC.SelectClipRgn( &rgn );
   rgn.DeleteObject( );
#endif

   // First let the control do its default drawing.
   CWnd::DefWindowProc( WM_PAINT, (WPARAM) memDC.m_hDC, 0 );

#if 0
   // Now create a mask
   CDC maskDC;
   maskDC.CreateCompatibleDC( &dc );
   CBitmap maskBitmap;

   // Create monochrome bitmap for the mask
   maskBitmap.CreateBitmap( rectClip.Width( ), rectClip.Height( ),
                            1, 1, 0 );
   maskDC.SelectObject( &maskBitmap );
   memDC.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );

   // Create the mask from the memory DC
   maskDC.BitBlt( 0, 0, rectClip.Width( ), rectClip.Height( ), &memDC,
                  rectClip.left, rectClip.top, SRCCOPY );

   // Fill the background with custom color
// ::PumpMessages( m_pZSubtask->m_vDialog );
   TraceLineS( "OnPaint: ", "Before FillRect" );
// ::MessageBox( 0, "OnPaint", "Before FillRect", MB_OK );
// SysWait( 10 );
   memDC_BkColor.FillRect( rectClip, &CBrush( m_clrBackground ) );
   TraceLineS( "OnPaint: ", "After FillRect" );
// ::MessageBox( 0, "OnPaint", "After FillRect", MB_OK );

   // Set Text Color and Text Font
   SetColorAndFont( &memDC );
   TraceLineS( "OnPaint: ", "After SetColorAndFont" );
// ::MessageBox( 0, "OnPaint", "After SetColorAndFont", MB_OK );

   // Copy the image in memDC_BkColor
   memDC_BkColor.MaskBlt( rectClip.left, rectClip.top,
                          rectClip.Width( ), rectClip.Height( ), &memDC,
                          rectClip.left, rectClip.top, maskBitmap, 0, 0,
                          MAKEROP4( SRCAND,SRCCOPY ) );
   dc.BitBlt( rectClip.left, rectClip.top,
              rectClip.Width( ), rectClip.Height( ),
              &memDC_BkColor, rectClip.left, rectClip.top, SRCCOPY );

   TraceLineS( "OnPaint", "After BitBlt" );
// ::MessageBox( 0, "OnPaint", "After BitBlt", MB_OK );
   memDC.SelectObject( pOldBitmap1 );
   memDC_BkColor.SelectObject( pOldBitmap2 );
   memDC.DeleteDC( );
   memDC_BkColor.DeleteDC( );
   maskDC.DeleteDC( );
#endif

#ifdef DEBUG_ALL
// TraceRect( "ZMSTree::OnPaint (after) Client: ", rectClient );
#endif
}

#else

#if 0
void
ZMSTree::OnPaint( )
{
   if ( (m_ulMapActFlag2 & zMAPACT_MAPPING_FROM_OI) || m_bSetMultiSelection )
      return;

// BLZ if Window 98, do not set colors (this is a workaround).
   OSVERSIONINFO  osvi;
   osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
   GetVersionEx( &osvi );
   zBOOL bIsWindows98orLater = (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
                               (osvi.dwMinorVersion > 0);

   if ( bIsWindows98orLater )
   {
      CTreeCtrl::OnPaint( );
      return;
   }
// End BLZ

   CPaintDC dc( this );

   // Create a memory DC compatible with the paint DC
   CDC memDC;
   memDC.CreateCompatibleDC( &dc );

   CRect rectClip;
   CRect rectClient;
   dc.GetClipBox( &rectClip );
   GetClientRect( &rectClient );

   // Select a compatible bitmap into the memory DC.
   CBitmap bitmap;
   bitmap.CreateCompatibleBitmap( &dc, rectClient.Width( ),
                                  rectClient.Height( ) );
   CBitmap *pBitmapOrigDC = memDC.SelectObject( &bitmap );

   // Set clip region to be same as that in paint DC.
   CRgn rgn;
   rgn.CreateRectRgnIndirect( &rectClip );
   memDC.SelectClipRgn( &rgn );
   rgn.DeleteObject( );

   // First let the control do its default drawing.
   CWnd::DefWindowProc( WM_PAINT, (WPARAM) memDC.m_hDC, 0 );

   UINT   selFlag = TVIS_DROPHILITED | TVIS_SELECTED;
   ItemColorFontImage cfi;
   CRect  rect;
   HTREEITEM hItem = GetFirstVisibleItem( );
   zSHORT k = GetVisibleCount( ) + 1;
   while ( hItem && k-- )
   {
      // Do not meddle with selected items or drop highlighted items
      if ( (GetItemState( hItem, selFlag ) & selFlag) == 0 &&
           m_mapItemColorFontImage.Lookup( hItem, cfi ) )
      {
         CFont   *pFontOld;
         CFont   fontDC;
         LOGFONT logfont;

         if ( cfi.logfont.lfFaceName[ 0 ] )
         {
            logfont = cfi.logfont;
         }
         else
         {
            // No font specified, so use window font.
            CFont *pFont = GetFont( );
            pFont->GetLogFont( &logfont );
         }

         if ( GetItemBold( hItem ) )
            logfont.lfWeight = FW_BOLD;

         pFontDC->CreateFontIndirect( &logfont );
         pFontOld = memDC.SelectObject( &fontDC );

         if ( cfi.color != (COLORREF) - 1 )
            memDC.SetTextColor( cfi.color );

         CString csItem = GetItemText( hItem );

         GetItemRect( hItem, &rect, TRUE );
         memDC.SetBkColor( GetSysColor( COLOR_WINDOW ) );
         memDC.TextOut( rect.left + 2, rect.top + 1, csItem );

         memDC.SelectObject( pFontOld );
      }

      hItem = GetNextVisibleItem( hItem );
   }

   dc.BitBlt( rectClip.left, rectClip.top,
              rectClip.Width( ), rectClip.Height( ), &memDC,
              rectClip.left, rectClip.top, SRCCOPY );

   memDC.SelectObject( pBitmapOrigDC );
}

#else

void
ZMSTree::OnNcPaint( )
{
#ifdef DEBUG_ALL
// if ( zstrcmp( *m_pzsTag, "OLTreeDisplayAttributes" ) == 0 )
      TraceLineS( "ZMSTree::OnNcPaint ", *m_pzsTag );
#endif

   Default( );
}

void
ZMSTree::OnPaint( )
{
#ifdef DEBUG_ALL
// if ( zstrcmp( *m_pzsTag, "OLTreeDisplayAttributes" ) == 0 )
      TraceLineS( "ZMSTree::OnPaint ", *m_pzsTag );
#endif

   if ( (m_ulMapActFlag2 & zMAPACT_MAPPING_FROM_OI) || m_bSetMultiSelection )
      return;

// BLZ if Window 98, do not set colors (this is a workaround).
   OSVERSIONINFO  osvi;
   osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
   GetVersionEx( &osvi );
   zBOOL bIsWindows98orLater = (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
                               (osvi.dwMinorVersion > 0);

   if ( bIsWindows98orLater )
   {
      CTreeCtrl::OnPaint( );
      return;
   }
// End BLZ

   CPaintDC dc( this );

   // Create a memory DC compatible with the paint DC.
   CDC memDC;
   memDC.CreateCompatibleDC( &dc );

   CRect rectClip;
   CRect rectClient;
   dc.GetClipBox( &rectClip );
   GetClientRect( &rectClient );

   // Select a compatible bitmap into the memory DC.
   CBitmap bitmap;
   bitmap.CreateCompatibleBitmap( &dc, rectClient.Width( ),
                                  rectClient.Height( ) );
   CBitmap *pBitmapOrigDC = memDC.SelectObject( &bitmap );

   // Set clip region to be same as that in paint DC.
   CRgn rgn;
   rgn.CreateRectRgnIndirect( &rectClip );
   memDC.SelectClipRgn( &rgn );
   rgn.DeleteObject( );

   // First let the control do its default drawing.
   CWnd::DefWindowProc( WM_PAINT, (WPARAM) memDC.m_hDC, 0 );

   if ( m_bFontColor )
   {
   // HTREEITEM hRootItem = GetRootItem( );
      CString  csItemText;
      UINT  uItemState;
      zBOOL bColorFontImage;
      zBOOL bFirstItem = TRUE;
      CRect rect;
      ItemColorFontImage cfi;
      zBOOL bFocus;
      zBOOL bBold;
      zBOOL bLogFont;
      LOGFONT logfont;
      COLORREF clrText;
      HTREEITEM hItem = GetFirstVisibleItem( );
      zSHORT k = GetVisibleCount( ) + 1;
      while ( hItem && k-- )
      {
         uItemState = GetItemState( hItem, TVIS_DROPHILITED | TVIS_SELECTED );
         if ( uItemState & TVIS_DROPHILITED )
         {
            // Do not meddle with drop highlighted items.
            hItem = GetNextVisibleItem( hItem );
            continue;
         }

         bColorFontImage = m_mapItemColorFontImage.Lookup( hItem, cfi ) ? TRUE : FALSE;

         if ( bColorFontImage && cfi.logfont.lfFaceName[ 0 ] )
         {
            logfont = cfi.logfont;
            bLogFont = TRUE;
         }
         else
         {
            // No font specified, so use window font.
            CFont *pFont = GetFont( );
            pFont->GetLogFont( &logfont );
            bLogFont = FALSE;
            cfi.color = CLR_INVALID;
         }

         if ( (bColorFontImage && logfont.lfWeight >= FW_BOLD) ||
              GetItemBold( hItem ) )
         {
            bBold = TRUE;
            logfont.lfWeight = FW_BOLD;
         }
         else
         {
            bBold = FALSE;
            logfont.lfWeight = FW_NORMAL;
         }

         if ( bBold || bLogFont )
         {
            // Clear out current drawing.
            GetItemRect( hItem, &rect, TRUE );
         // if ( bFirstItem )
         //    rect.bottom--;

            memDC.FillRect( rect, &CBrush( GetSysColor( COLOR_WINDOW ) ) );
         }

         bFocus = FALSE;
         clrText = CLR_INVALID;
         if ( uItemState & TVIS_SELECTED )
         {
            if ( GetFocus( ) == this )
            {
               bFocus = TRUE;
               memDC.SetBkColor( GetSysColor( COLOR_HIGHLIGHT ) );
               clrText = memDC.SetTextColor( GetSysColor( COLOR_CAPTIONTEXT ) );
            }
            else
            {
               memDC.SetBkColor( GetSysColor( COLOR_BTNFACE ) );
               clrText = memDC.SetTextColor( GetSysColor( COLOR_BTNTEXT ) );
            }
         }
         else
         {
            if ( cfi.color != CLR_INVALID )
               clrText = memDC.SetTextColor( cfi.color );
            else
               clrText = memDC.SetTextColor( GetSysColor( COLOR_WINDOWTEXT ) );

            memDC.SetBkColor( GetSysColor( COLOR_WINDOW ) );
         }

         CFont *pFontOld;
         CFont *pFontDC = new CFont( );

         csItemText = GetItemText( hItem );

         pFontDC->CreateFontIndirect( &logfont );
         pFontOld = memDC.SelectObject( pFontDC );

         GetItemRect( hItem, &rect, TRUE );
         memDC.TextOut( rect.left + 2, rect.top + 1, csItemText );

         if ( bFocus )  // must be true ==> && (uItemState & TVIS_SELECTED) )
         {
            CRect rectFocus = rect;
            CSize sizeExtent = memDC.GetTextExtent( csItemText );
            rectFocus.right = rectFocus.left + sizeExtent.cx + 2;
            rectFocus.bottom = rectFocus.top + sizeExtent.cy + 2;
            rectFocus.top++;
            rectFocus.left++;
            rectFocus.right++;
         // if ( hItem != hRootItem )
         // if ( bFirstItem )
         //    rectFocus.bottom--;

            memDC.DrawFocusRect( rectFocus );
         }

         if ( clrText != CLR_INVALID )
            memDC.SetTextColor( clrText );

         memDC.SelectObject( pFontOld );
         delete( pFontDC );

      // bFirstItem = FALSE;
         hItem = GetNextVisibleItem( hItem );
      }
   }

   dc.BitBlt( rectClip.left, rectClip.top,
              rectClip.Width( ), rectClip.Height( ), &memDC,
              rectClip.left, rectClip.top, SRCCOPY );

   // Restore original bitmap to DC.
   memDC.SelectObject( pBitmapOrigDC );
}

#endif
#endif

BOOL
ZMSTree::OnEraseBkgnd( CDC *pDC )
{
#ifdef DEBUG_ALL
// if ( zstrcmp( *m_pzsTag, "OLTreeDisplayAttributes" ) == 0 )
      TraceLineS( "ZMSTree::OnEraseBkgnd ", *m_pzsTag );
#endif

   EnableScrollBar( SB_BOTH, ESB_DISABLE_BOTH ); // trying to cause repaint of non-client area
   EnableScrollBar( SB_BOTH, ESB_ENABLE_BOTH ); // trying to cause repaint of non-client area

   // To prevent flickering when using non-default bkcolor.
   return( FALSE );
}

// To expand or collapse all entries.
void
ZMSTree::ExpandCollapseAll( HTREEITEM hItem, UINT uFlag )
{
#ifdef zREMOTE_SERVER
   return;
#else
   // If a null Handle is passed start with root.
   if ( hItem == 0 )
   {
      hItem = GetRootItem( );
   // if ( uFlag == TVE_COLLAPSE )  // this doesn't work
   // {
   //    ItemExpand( hItem, uFlag );
   //    return;
   // }
   }

   for ( ; hItem; hItem = GetNextItemPhysical( hItem ) )
   {
      ItemExpand( hItem, uFlag );
   }

#endif
}

void
ZMSTree::SetMultipleSelectionWithCtrl( UINT nFlags, CPoint pt )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetMultipleSelectionWithCtrl: ", *m_pzsTag );
#endif
   // Ctrl key is down.
   UINT        flag;
   HTREEITEM   hItem = HitTest( pt, &flag );

   if ( hItem )
   {
      // Toggle selection state ... note the result is inverted.
      UINT uSelState = (GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED) ?
                                                             0 : TVIS_SELECTED;

      // Get old selected (focus) item and state.
      HTREEITEM hItemOld = GetSelectedItem( );

      UINT uOldSelState = hItemOld ?
                          GetItemState( hItemOld, TVIS_SELECTED ) : 0;

      // Select new item.
      if ( GetSelectedItem( ) == hItem )
         SelectItem( 0 );      // to prevent edit

      // Restore state of old selected item.
      if ( hItemOld && hItemOld != hItem )
      {
         if ( CanMultiSelect( ) )
            SetItemSelState( hItemOld, uOldSelState, TVIS_SELECTED );
         else
            SetItemSelState( hItemOld, 0, TVIS_SELECTED );
      }

      SetItemSelState( hItem, uSelState, TVIS_SELECTED );
      if ( uSelState )
      {
         if ( m_hItemFirstSel == 0 )
            m_hItemFirstSel = hItem;
      }
      else
         m_hItemFirstSel = GetSelectedItem( );

      Invalidate( );
      ProcessImmediateEvent( this, zTREE_EVENT_SELECT_CHANGE );
   }
}

void
ZMSTree::SetMultipleSelectionWithShift( UINT nFlags, CPoint pt )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetMultipleSelectionWithShift: ", *m_pzsTag );
#endif
   UINT uFlag;

   // Shift key is down
   HTREEITEM hItem = HitTest( pt, &uFlag );

   // Initialize the reference item if this is the first shift selection
// if ( m_hItemFirstSel == 0 )
//    m_hItemFirstSel = GetSelectedItem( );  dks ???

// hItem = HitTest( pt, &uFlag );

   if ( m_hItemFirstSel )
   {
   // CString cs = GetItemText( m_hItemFirstSel );
   // cs = GetItemText( hItem );
      SelectItems( m_hItemFirstSel, hItem );
   }
   else
      m_hItemFirstSel = hItem;

   SetItemSelState( hItem, TVIS_SELECTED, TVIS_SELECTED );
   ProcessImmediateEvent( this, zTREE_EVENT_SELECT_CHANGE );
}

void
ZMSTree::SetSelectionForDesignTime( UINT nFlags, HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetSelectionForDesignTime: ", *m_pzsTag );
#endif
   if ( nFlags & MK_CONTROL )
   {
      UINT uNewSelState = GetItemState( hItem, TVIS_STATEIMAGEMASK );

      UINT uiState = 0;
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );

      if ( pNode == 0 )
         return;

      if ( uNewSelState & INDEXTOSTATEIMAGEMASK( zTREE_STATE_UNSELECTED_IMG ) )
         pNode->m_bSelected = 1;
      else
         pNode->m_bSelected = 0;

      ToggleSelection( hItem );
      SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
   }
   else
   {
      SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
      SelectItem( hItem );
   }
}

void
ZMSTree::ResetViewForDefaultSelectSet( zVIEW v )
{
// TraceLineS( "ZMSTree::ResetViewForDefaultSelectSet", "" );

// ResetViewPositions( v ); // do not reset select states here!

   // Do not reset top entity positions here!
   while ( ResetViewFromSubobject( v ) == 0 )
   {
   }

// DisplayObjectInstance( v, 0, 0 );
   SetAllSelStatesForEntityForSet( v, 0, // Entity
                                   0,    // State
                                   1,    // default SelectSet
                                   0 );  // Scope
}

void
ZMSTree::OnLButtonDown( UINT nFlags, CPoint pt )
{
   UINT       uFlag  = 0;
   HTREEITEM  hItem = HitTest( pt, &uFlag );

   // Set focus to control since focus is not automatically given to control
   // on LButtonDown.
   SetFocus( );

   // If Button Click.  TVHT_ONITEMBUTTON  0x0010   TVS_SINGLEEXPAND 0x0400
   if ( (uFlag & TVHT_ONITEMBUTTON) &&
        ((m_dwStyle & TVS_SINGLEEXPAND) == 0 ||
         (GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED)) )
   {
      CTreeCtrl::OnLButtonDown( nFlags, pt );
      return;
   }

   if ( hItem == 0 ||
        ((uFlag & TVHT_ONITEM) == 0 && (uFlag & TVHT_ONITEMBUTTON) == 0) )
   {
      return;
   }

   if ( IsCancelByPreSelChangeAction( hItem ) )
      return;

   HWND hWnd = m_hWnd;
   hItem = HitTest( pt, &uFlag );

#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnLButtonDown: ", *m_pzsTag );
   CString cs1 = GetItemText( hItem );
   TraceLineS( "Current ItemText: ", cs1 );
#endif

#ifdef DEBUG_ALL

   ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );
   if ( pNode )
   {
      TraceLine( "ZMSTree::OnLButtonDown (0x%08x) Entity: %s      Attribute: %s  "
                    "Data: %s  Selected: %s",
                 pNode->m_ulEntityKey,
                 (LPCTSTR) pNode->m_csEntityName,
                 (LPCTSTR) pNode->m_csAttributeName,
                 (LPCTSTR) pNode->GetValues( ' ' ),
                 pNode->m_bSelected ? "Y" : "N" );
  }

#endif

   if ( (nFlags & MK_CONTROL) && CanMultiSelect( ) )
   {
      SetMultipleSelectionWithCtrl( nFlags, pt );
   }
   else
   if ( (nFlags & MK_SHIFT) && CanMultiSelect( ) )
   {
      SetMultipleSelectionWithShift( nFlags, pt );
   }
   else
   {
      // Normal - remove all selection and let default handler do the rest.
      ClearSelection( );
      m_hItemFirstSel = 0;

      if ( IsDesignTime( ) )
         SetSelectionForDesignTime( nFlags, hItem );
      else
         SetItemSelState( hItem, TVIS_SELECTED, TVIS_SELECTED );

   // CTreeCtrl::OnLButtonDown( nFlags, pt ) DOES NOT WORK here

#ifdef DEBUG_ALL
      CString cs = GetItemText( hItem );
      TraceLineS( "ItemText: ", cs );
#endif

      SelectItem( hItem );
      if ( mIs_hWnd( hWnd ) )
      {
         m_hItemFirstSel = hItem;
         if ( (m_dwStyle & TVS_EDITLABELS) &&
              m_bLabelEdit == FALSE && m_bLabelEditRemoveFlag == FALSE )
         {
            EditLabel( hItem );
         }
      }
   }

// CTreeCtrl::OnLButtonDown( nFlags, pt );
   if ( mIs_hWnd( hWnd ) )
      Invalidate( );
}

zLONG
ZMSTree::EditItem( zULONG ulTextLength )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::EditItem: ", *m_pzsTag );
#endif
   zLONG     lRC   = -1;
   HTREEITEM hItem = GetSelectedItem( );

   if ( hItem == 0 )
      return( lRC );

   SetNewStyle( TVS_EDITLABELS, TRUE );

   m_lLabelEditTextLth = ulTextLength;
   m_csLabelEditOldValue.Empty( );

   SetFocus( );
   CEdit *pEdit = EditLabel( hItem );

   if ( pEdit == 0 )
   {
      SetNewStyle( TVS_EDITLABELS, FALSE );
      return( lRC );
   }

   m_bLabelEditRemoveFlag = TRUE;

   return( 0 );
}

zBOOL
ZMSTree::IsCancelByPreSelChangeAction( HTREEITEM hItem )
{
   zBOOL bRC;
   zLONG lRC = ProcessImmediateEvent( this, zTREE_EVENT_PRESELECT_CHANGE );

// if ( lRC && lRC != zNO_APPLICATION_EVENT )
   if ( lRC != zNO_APPLICATION_EVENT && (zSHORT) zLOUSHORT( lRC ) < 0 )
   {
      bRC = TRUE;
   }
   else
   {
      m_bPreSelectChangeAlreadyDone = TRUE;

      HTREEITEM hItemPrev = GetSelectedItem( );
      if ( hItemPrev && hItemPrev == hItem )  // we are on the same item
      {
      // TraceLineS( "IsCancel On SAME item", " PRIOR" );
         Select( hItem, TVGN_CARET );
      // SelectItem( hItem );
         ProcessImmediateEvent( this, zTREE_EVENT_SELECT_CHANGE );
      // TraceLineS( "IsCancel On SAME item", " POST" );
      }

   // PumpMessages( m_pZSubtask->m_vDialog );
   // TraceLineS( "IsCancel item ==========>", " Pumped" );
      bRC = FALSE;
   }

#ifdef DEBUG_ALL
   ZOL_Node *pNodeOld;
   ZOL_Node *pNodeNew;

   if ( m_ulKeyLast )
      pNodeOld = m_pRootEntry->FindNodeByEntityKey( m_ulKeyLast );
   else
      pNodeOld = 0;

   if ( hItem )
      pNodeNew = (ZOL_Node *) GetItemData( hItem );
   else
      pNodeNew = 0;

   TraceLine( "ZMSTree::IsCancelByPreSelChangeAction Tag: %s      OldItem: (%d) %s   NewItem: (%d) %s   RC: %s",
              *m_pzsTag,
              m_ulKeyLast,
              (zCPCHAR) (pNodeOld && pNodeOld->m_hItem ? GetItemText( pNodeOld->m_hItem ) : ""),
              pNodeNew ? pNodeNew->m_ulEntityKey : 0,
              (zCPCHAR) (pNodeNew && pNodeNew->m_hItem ? GetItemText( pNodeNew->m_hItem ) : ""),
              bRC ? "TRUE" : "FALSE" );
#endif

   return( bRC );
}

void
ZMSTree::SetSelectionForSystemKey( UINT nChar )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetSelectionForSystemKey: ", *m_pzsTag );
#endif
   if ( IsCancelByPreSelChangeAction( GetSelectedItem( ) ) )
      return;

   // Initialize the reference item if this is the first shift selection.
   if ( m_hItemFirstSel == 0 )
   {
      m_hItemFirstSel = GetSelectedItem( );
      ClearSelection( );
   }

   // Find which item is currently selected.
   HTREEITEM hItemPrevSel = GetSelectedItem( );

   HTREEITEM hItemNext;
   if ( nChar == VK_UP )
      hItemNext = GetPrevVisibleItem( hItemPrevSel );
   else
      hItemNext = GetNextVisibleItem( hItemPrevSel );

   if ( hItemNext )
   {
      if ( IsDesignTime( ) )
      {
         SelectItem( hItemNext );
         SetItemState( hItemNext, TVIS_SELECTED, TVIS_SELECTED );
         ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItemNext );
         if ( pNode )
            ToggleSelection( hItemNext );

         return;
      }

      // Determine if we need to reselect previously selected item
      // (note the inverted result).
      BOOL bReselect = (GetItemState( hItemNext, TVIS_SELECTED ) &
                                               TVIS_SELECTED) ? FALSE : TRUE;

      // Select the next item - this will also deselect the previous item.
      m_bSetMultiSelection = TRUE;
      SelectItem( hItemNext );

      // Reselect the previously selected item
      if ( bReselect && CanMultiSelect( ) )
         SetItemSelState( hItemPrevSel, TVIS_SELECTED, TVIS_SELECTED );
      else
         SetItemSelState( hItemPrevSel, 0, TVIS_SELECTED );

      SetItemSelState( hItemNext, TVIS_SELECTED, TVIS_SELECTED );

      m_bSetMultiSelection = FALSE;

      ProcessImmediateEvent( this, zTREE_EVENT_SELECT_CHANGE );
   }
}

void
ZMSTree::SetSelectionForMultipleSelect( UINT nChar, UINT nRepCnt, UINT nFlags )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetSelectionForMultipleSelect: ", *m_pzsTag );
#endif
   if ( IsCancelByPreSelChangeAction( GetSelectedItem( ) ) )
      return;

   // Initialize the reference item if this is the first shift selection
   if ( m_hItemFirstSel == 0 )
      m_hItemFirstSel = GetSelectedItem( );

   m_bSetMultiSelection = TRUE;
   CTreeCtrl::OnKeyDown( nChar, nRepCnt, nFlags );

   // Find which item is currently selected
   HTREEITEM hItemNextSel = GetSelectedItem( );

   if ( m_hItemFirstSel )
      SelectItems( m_hItemFirstSel, hItemNextSel );

   SetItemSelState( hItemNextSel, TVIS_SELECTED, TVIS_SELECTED );
   m_bSetMultiSelection = FALSE;
}

void
ZMSTree::CollapseForSingleExpand( HTREEITEM hItem, HTREEITEM hSelItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::CollapseForSingleExpand: ", *m_pzsTag );
#endif
   zBOOL bExpand = FALSE;

   while ( bExpand == FALSE && hItem )
   {
      if ( hSelItem != hItem &&
           (GetItemState( hItem, TVIS_EXPANDED ) & TVIS_EXPANDED) )
      {
         bExpand = Expand( hItem, TVE_COLLAPSE );
         if ( ItemHasChildren ( hItem ) )
         {
            HTREEITEM hChild = GetChildItem( hItem );
            while ( hChild )
            {
               if ( GetItemState( hChild, TVIS_EXPANDED ) & TVIS_EXPANDED )
               {
                  if ( ItemHasChildren ( hChild ) )
                     CollapseForSingleExpand( hChild, hSelItem );

                  ItemExpand( hChild, TVE_COLLAPSE );
               }

               hChild = GetNextSiblingItem( hChild );
            }
         }
       }
       hItem = GetNextSiblingItem( hItem );
   }
}

void
ZMSTree::SetSelectionForSingleSelect( UINT nChar )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetSelectionForSingleSelect: ", *m_pzsTag );
#endif
   HTREEITEM hItem = GetSelectedItem( );

   if ( hItem == 0 )
      return;

   if ( IsDesignTime( ) )
   {
      SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );

      if ( pNode )
         ToggleSelection( pNode );
   }
   else
   {
      if ( GetFirstSelectedItem( ) == 0 )
         SetItemSelState( hItem, TVIS_SELECTED, TVIS_SELECTED );

      // Single Expand does not work with keybord shortcut,
      // you have to implement it by your own
      if ( (m_dwStyle & TVS_SINGLEEXPAND) && nChar == VK_RIGHT )
      {
         HTREEITEM hItem1 = GetParentItem( hItem);
         hItem1 = GetChildItem( hItem1 );

         // collaps old expanded Item
         if ( hItem1 )
            CollapseForSingleExpand( hItem1, hItem );

         // expand new item
         ItemExpand( hItem, TVE_EXPAND );
      }
   }
}

// The code in OnKeyDown will allow user to use the shift-up arrow and the
// shift-down arrow keys to create and modify the selection. If the key pressed
// is any other non control character, then the selection is cleared.
void
ZMSTree::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnKeyDown: ", *m_pzsTag );
#endif
   if ( (nChar == VK_UP || nChar == VK_DOWN) &&
        ((GetKeyState( VK_SHIFT ) & 0x8000) ||
         (GetKeyState( VK_CONTROL ) & 0x8000)) )
   {
      SetSelectionForSystemKey( nChar );
   }
   else
   if ( CanMultiSelect( ) &&
        (nChar == VK_HOME ||  nChar == VK_END ||
         nChar == VK_NEXT || nChar == VK_PRIOR) &&
        (GetKeyState( VK_SHIFT ) & 0x8000) )
   {
      SetSelectionForMultipleSelect( nChar, nRepCnt, nFlags );
   }
   else
   if ( nChar >= VK_SPACE )
   {
      m_hItemFirstSel = 0;
      ClearSelection( );

      CTreeCtrl::OnKeyDown( nChar, nRepCnt, nFlags );
      SetSelectionForSingleSelect( nChar );
   }
}

// This function is called very often. Every time a user clicks on the tree view
// control without the shift or the control key pressed, this function gets called.
// The function as given below is very simple. It scans through all the items in
// the tree view control and deselects them individually. If the tree holds a lot
// of items, then this function can prove to be too slow.

// GetNextItemPhysical - Get next item as if tree was completely expanded
// Returns - The item immediately below the reference item
// hItem - The reference item
HTREEITEM
ZMSTree::GetNextItemPhysical( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::GetNextItem: ", *m_pzsTag );
#endif
   HTREEITEM hti;

   if ( ItemHasChildren( hItem ) )
      return( GetChildItem( hItem ) );      // return first child
   else
   {
      // return next sibling item
      // Go up the tree to find a parent's sibling if needed.
      while ( (hti = GetNextSiblingItem( hItem )) == 0 )
      {
         if ( (hItem = GetParentItem( hItem )) == 0 )
            return( 0 );
      }
   }

   return( hti );
}

void
ZMSTree::ClearSelection( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::ClearSelection: ", *m_pzsTag );
#endif
   ZOL_Node *pNode;

#if 0
   zVIEW    vApp;

   GetViewByName( &vApp, m_csTreeViewName,
                  m_vSubtask, zLEVEL_SUBTASK );
   if ( vApp )
      ResetViewForDefaultSelectSet( vApp ); // resetting select states here!

   DeselectAllEntities( );
#endif

   // This can be time consuming for very large trees
   // and is called every time the user does a normal selection
   // If performance is an issue, it may be better to maintain
   // a list of selected items
   for ( HTREEITEM hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      if ( IsDesignTime( ) )
      {
         SetItemState( hItem, 0, TVIS_SELECTED );
         pNode = (ZOL_Node *) GetItemData( hItem );
         if ( pNode )
            ToggleSelection( pNode );
      }
      else
      {
         SetItemState( hItem, 0, TVIS_SELECTED );      //???
         pNode = (ZOL_Node *) GetItemData( hItem );
         if ( pNode && pNode->m_bSelected )            //???
         {
            pNode->m_bSelected = 0;
            ToggleSelection( pNode );                  //???
         }
      }
   }
}

zBOOL
ZMSTree::SetItemSelState( HTREEITEM hItem, UINT uState, UINT uStateMask )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SetItemSelState: ", *m_pzsTag );
#endif

   if ( hItem && uStateMask == TVIS_SELECTED )
   {
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );

      if ( pNode )
         pNode->m_bSelected = uState;

      ToggleSelection( hItem );
   }

   return( CTreeCtrl::SetItemState( hItem, uState, uStateMask ) );
}

// This function is used when the user shift-clicks on an item. It takes
// care of removing selection from items not within the range and selects the items
// inside the range.

// SelectItems    - Selects items from hItemFrom to hItemTo. Does not
//                - select child item if parent is collapsed. Removes
//                - selection from all other items
// hItemFrom      - item to start selecting from
// hItemTo        - item to end selection at.
zBOOL
ZMSTree::SelectItems( HTREEITEM hItemFrom, HTREEITEM hItemTo )
{
   HTREEITEM hItem = GetRootItem( );

#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::SelectItems: ", *m_pzsTag );
   CString cs = GetItemText( hItemFrom );
   TraceLineS( "SelectItems From: ", cs );
   cs = GetItemText( hItemTo );
   TraceLineS( "SelectItems To: ", cs );
#endif

   // Clear selection up to the first item.
   while ( hItem )
   {
   // cs = GetItemText( hItem );
      if ( hItem == hItemFrom || hItem == hItemTo )
         break;

      SetItemSelState( hItem, 0, TVIS_SELECTED );
      hItem = GetNextVisibleItem( hItem );
   }

   if ( hItem == 0 )
      return( FALSE );   // Item is not visible

   SetItemSelState( hItemTo, TVIS_SELECTED, TVIS_SELECTED );

   // Rearrange hItemFrom and hItemTo so that the first is at the top.
   if ( hItem == hItemTo )
   {
      hItemTo = hItemFrom;
      hItemFrom = hItem;
   }

   // Go through remaining visible items.
   zBOOL bSelect = TRUE;
   while ( hItem )
   {
      // Select or remove selection depending on whether item
      // is still within the range.
      SetItemSelState( hItem, bSelect ? TVIS_SELECTED : 0, TVIS_SELECTED );

      // Do we need to start removing selection?
      if ( hItem == hItemTo )
         bSelect = FALSE;

      hItem = GetNextVisibleItem( hItem );

      if ( hItem == hItemFrom )
         bSelect = FALSE;  // this should not happen!!!
   }

   return( TRUE );
}

// Provide utility functions to query on the first selected item and to traverse
// the list of selected items in either the forward direction or the reverse
// direction. Again, like the ClearSelection( ) function, these functions can be
// time consuming for large trees.

zLONG
ZMSTree::GetSelectedCount( )
{
   zLONG lCnt = 0;
   for ( HTREEITEM hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
         lCnt++;
   }

   return( lCnt );
}

HTREEITEM
ZMSTree::GetFirstSelectedItem( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetFirstSelectedItem: ", *m_pzsTag );
#endif
   for ( HTREEITEM hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
         return( hItem );
   }

   return( 0 );
}

HTREEITEM
ZMSTree::GetNextSelectedItem( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetNextSelectedItem: ", *m_pzsTag );
#endif
   for ( hItem = GetNextItemPhysical( hItem );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
         return( hItem );
   }

   return( 0 );
}

// GetPrevItemPhysical  - Get previous item as if tree was completely expanded
// Returns              - The item immediately above the reference item
// hItem                - The reference item
HTREEITEM
ZMSTree::GetPrevItemPhysical( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetPrevItem: ", *m_pzsTag );
#endif
   HTREEITEM  hti;

   hti = GetPrevSiblingItem( hItem );

   if ( hti == 0 )
      hti = GetParentItem( hItem );
   else
      hti = GetLastItemPhysical( hti );

   return( hti );
}

HTREEITEM
ZMSTree::GetLastVisibleItem( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetLastVisibleItem: ", *m_pzsTag );
#endif
   // Last child of the last child of the last child ...
   HTREEITEM htiNext;

   if ( hItem == 0 )
   {
      // Get the last item at the top level
      htiNext = GetRootItem( );
      while ( htiNext )
      {
         hItem = htiNext;
         htiNext = GetNextVisibleItem( htiNext );
      }
   }

   while ( ItemHasChildren( hItem ) )
   {
      htiNext = GetChildItem( hItem );
      while ( htiNext )
      {
         hItem = htiNext;
         htiNext = GetNextVisibleItem( htiNext );
      }
   }

   return( hItem );
}

// GetLastItemPhysical - Gets last item in the branch
// Returns - Last item
// hItem - Node identifying the branch.  Null will return the last item in tree.
HTREEITEM
ZMSTree::GetLastItemPhysical( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetLastItemPhysical: ", *m_pzsTag );
#endif
   // Last child of the last child of the last child ...
   HTREEITEM htiNext;

   if ( hItem == 0 )
   {
      // Get the last item at the top level
      htiNext = GetRootItem( );
      while ( htiNext )
      {
         hItem = htiNext;
         htiNext = GetNextSiblingItem( htiNext );
      }
   }

   while ( ItemHasChildren( hItem ) )
   {
      htiNext = GetChildItem( hItem );
      while ( htiNext )
      {
         hItem = htiNext;
         htiNext = GetNextSiblingItem( htiNext );
      }
   }

   return( hItem );
}

HTREEITEM
ZMSTree::GetPrevSelectedItem( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetPrevSelectedItem: ", *m_pzsTag );
#endif
   for ( hItem = GetPrevItemPhysical( hItem );
         hItem;
         hItem = GetPrevItemPhysical( hItem ) )
   {
      if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
         return( hItem );
   }

   return( 0 );
}

void
ZMSTree::ToggleSelection( ZOL_Node *pNode )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::ToggleSelection: ", *m_pzsTag );
#endif
   CString csText;

   if ( pNode )
   {
      zSHORT nRC  = -1;
      zULONG ulKey = pNode->m_ulEntityKey;

      // promote changes to the view
      if ( ulKey &&
           GetViewByName( &m_vApp, m_csTreeViewName,
                          m_vSubtask, zLEVEL_SUBTASK ) >= 0 )
      {
         nRC = OL_SetCursorByEntityNumber( m_vApp, pNode->m_csEntityName,
                                           ulKey );
         if ( nRC >= zCURSOR_SET )
         {
            zCHAR szEntityName[ zTAG_LTH ];

            strcpy_s( szEntityName, zsizeof( szEntityName ), pNode->m_csEntityName );
            GetRealEntityName( m_vApp, szEntityName );

            SetSelectStateOfEntity( m_vApp, szEntityName, pNode->m_bSelected );
         }
      }
   }
}

void
ZMSTree::ToggleSelection( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::ToggleSelection: ", *m_pzsTag );
#endif
   ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );

   if ( pNode )
   {
      UINT uState;
      // promote changes to the view
      ToggleSelection( pNode );

      if ( IsDesignTime( ) )
      {
         // update tree control
         if ( pNode->m_bSelected )
            uState = INDEXTOSTATEIMAGEMASK( zTREE_STATE_SELECTED_IMG );
         else
            uState = INDEXTOSTATEIMAGEMASK( zTREE_STATE_UNSELECTED_IMG );

         SetItemState( hItem, uState, TVIS_STATEIMAGEMASK );
      }
   }
}

void
ZMSTree::OnDblclk( NMHDR *pNMHDR, LRESULT *pResult )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnDblclk: ", *m_pzsTag );
#endif
   // TODO: Add your control notification handler code here

   ProcessEvent( this, zTREE_EVENT_DOUBLECLICK );

//   *pResult = 0;
}

void
ZMSTree::OnOutOfMemory( NMHDR *pNMHDR, LRESULT *pResult )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnOutOfMemory: ", *m_pzsTag );
#endif
   // TODO: Add your control notification handler code here

   *pResult = 0;
}

void
ZMSTree::OnRButtonDown( UINT nFlags, CPoint pt )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnRButtonDown: ", *m_pzsTag );
#endif
   UINT uFlags;
   HTREEITEM hItem = HitTest( pt, &uFlags );

// ZOL_Node *pNode = 0;
// CString cs1;
// if ( hItem )
// {
//    pNode = (ZOL_Node *) GetItemData( hItem );
//    cs1 = GetItemText( hItem );
// }
//
// TraceLine( "ZMSTree::OnRButtonDown1 x=%d, y=%d      Item (0x%08x)  Key: %d  text: %s  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
//            pt.x, pt.y, hItem, pNode ? pNode->m_ulEntityKey : 0, cs1 );

   if ( hItem == 0 ||
        ((uFlags & TVHT_ONITEM) == 0 && (uFlags & TVHT_ONITEMBUTTON) == 0) )
   {
      // If Error by Edit Label.
      if ( (m_dwStyle & TVS_EDITLABELS && m_bLabelEdit) == 0 )
         ProcessImmediateEvent( this, zTREE_EVENT_RBUTTON_BACKGROUND );

      return;
   }

   if ( IsCancelByPreSelChangeAction( hItem ) )
      return;

#ifdef DEBUG_ALL
   TracePoint( "ZMSTree::OnRButtonDown", pt );
#endif

   BOOL bSelectItem = FALSE;
   UINT uSelState;

   // We will let right mouse button select but not de-select the
   // item over which the mouse is pressed.  If the item is not
   // selected, it will be selected and all other items will be
   // de-selected.  If the item is selected, it and all others
   // will remain selected in the multi-select case.
#if 1
   hItem = HitTest( pt, &uFlags );

// pNode = 0;
// cs1 = "";
// if ( hItem )
// {
//    pNode = (ZOL_Node *) GetItemData( hItem );
//    cs1 = GetItemText( hItem );
// }
//
// TraceLine( "ZMSTree::OnRButtonDown2 x=%d, y=%d      Item (0x%08x)  Key: %d  text: %s",
//            pt.x, pt.y, hItem, pNode ? pNode->m_ulEntityKey : 0, cs1 );

   if ( hItem )
      uSelState = GetItemState( hItem, TVIS_SELECTED );
   else
      uSelState = 0;

   if ( CanMultiSelect( ) )
   {
      if ( hItem )
      {
         bSelectItem = TRUE;
         if ( (uSelState & TVIS_SELECTED) == 0 )
         {
            ClearSelection( );
         }
         else
         {
            if ( m_hItemFirstSel )
               hItem = m_hItemFirstSel;
         }
      }
      else
      {
         ClearSelection( );
      }
   }
   else
   {
      ClearSelection( );
      if ( hItem )
         bSelectItem = TRUE;
   }

   if ( bSelectItem )
   {
      if ( IsDesignTime( ) )
      {
         OnLButtonDown( nFlags, pt );
      }
      else
      {
         SetItemSelState( hItem, TVIS_SELECTED, TVIS_SELECTED );
         SelectItem( hItem );
         if ( (uSelState & TVIS_SELECTED) == 0 )
         {
         // PumpMessages( m_pZSubtask->m_vDialog );
         // CTreeCtrl::OnRButtonDown( nFlags, pt );
         }
      }
   }
#else
// hItem = HitTest( pt, &uFlags );
   if ( CanMultiSelect( ) == FALSE )
   {
      ClearSelection( );
      if ( hItem )
         bSelectItem = TRUE;
   }
   else
   if ( hItem )
   {
      if ( (nFlags & MK_CONTROL) == 0 && (nFlags & MK_SHIFT) == 0 )
      {
         uSelState = GetItemState( hItem, TVIS_SELECTED );
         if ( (uSelState & TVIS_SELECTED) == 0 )
         {
            ClearSelection( );
            bSelectItem = TRUE;
         }
      }
   }

   if ( bSelectItem )
   {
      if ( IsDesignTime( ) )
      {
         OnLButtonDown( nFlags, pt );
      }
      else
      {
         SetItemSelState( hItem, TVIS_SELECTED, TVIS_SELECTED );
         SelectItem( hItem );
         CTreeCtrl::OnRButtonDown( nFlags, pt );
      }
   }

#endif
   // if Error by Edit Label
   if ( ((m_dwStyle & TVS_EDITLABELS) && m_bLabelEdit) == 0 )
   {
      CPoint ptScreen( pt );
      ClientToScreen( &ptScreen );
      zULONG ulPoint = zMAKELONG( ptScreen.x, ptScreen.y );
   // TracePoint( "RButtonDown calling event at point: ", pt );
      ProcessImmediateEvent( this, zTREE_EVENT_RBUTTON_ITEM,
                             (zPVOID) ulPoint );
   }
}

void
ZMSTree::OnRdblclk( NMHDR *pNMHDR, LRESULT *pResult )
{
   // TODO: Add your control notification handler code here

   *pResult = 0;
}

void
ZMSTree::OnReturn( NMHDR *pNMHDR, LRESULT *pResult )
{
   // TODO: Add your control notification handler code here

   *pResult = 0;
}

void
ZMSTree::OnBegindrag( NMHDR *pNMHDR, LRESULT *pResult )
{
   NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *) pNMHDR;
   // TODO: Add your control notification handler code here

   *pResult = 0;
}

void
ZMSTree::OnBeginrdrag( NMHDR *pNMHDR, LRESULT *pResult )
{
   NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *) pNMHDR;
   // TODO: Add your control notification handler code here

   *pResult = 0;
}

void
ZMSTree::OnDeleteItem( NMHDR *pNMHDR, LRESULT *pResult )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::OnDeleteItem: ", *m_pzsTag );
#endif
   NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *) pNMHDR;
   // TODO: Add your control notification handler code here

   *pResult = 0;
}

BOOL
ZMSTree::PreTranslateMessage( MSG *pMsg )
{
   if ( pMsg->message == WM_KEYDOWN )
   {
      // When an item is being edited make sure the edit control
      // receives certain important key strokes
      if ( GetEditControl( ) &&
           ( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE ||
             pMsg->wParam == VK_ESCAPE || GetKeyState( VK_CONTROL) ) )
      {
         if ( pMsg->wParam == VK_ESCAPE )
            m_bLabelEditESC = TRUE;
         else
            m_bLabelEditESC = FALSE;

         ::TranslateMessage( pMsg );
         ::DispatchMessage( pMsg );
         return( TRUE );              // DO NOT process further
      }
      else
      if ( pMsg->wParam == VK_ESCAPE &&
           ProcessAction( 0, 0, 0, 0, 0 ) > 0 ) // Action being processed
      {
         TraceLineS( "ZMSTree::PreTranslateMessage ignoring VK_ESCAPE", "" );
         return( TRUE );              // DO NOT process further
      }
   }

   return( CTreeCtrl::PreTranslateMessage( pMsg ) );
}

void
ZMSTree::LabelEditCleanUp( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::LabelEditCleanUp: ", *m_pzsTag );
#endif

   m_csLabelEditOldValue.Empty( );
   m_lLabelEditTextLth = 0;

   if ( m_bLabelEditRemoveFlag )
   {
      SetNewStyle( TVS_EDITLABELS, FALSE );
      m_bLabelEditRemoveFlag = FALSE;
   }

   m_bLabelEdit = FALSE;

}

void
ZMSTree::LabelEditError( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::LabelEditError: ", *m_pzsTag );
#endif
   SetFocus( );
   ClearSelection( );

   SetItemSelState( hItem, TVIS_SELECTED, TVIS_SELECTED );
   SelectItem( hItem );

   EnsureVisible( hItem );
   EditLabel( hItem );
}

void
ZMSTree::InitBeginLabelEdit( CEdit *pEdit, ZOL_Node *pNode, HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::InitBeginLabelEdit: ", *m_pzsTag );
#endif
   zULONG ulLth;

   // set Text Limit
   GetAttributeDisplayLength( &ulLth, m_vApp, pNode->m_csEntityName,
                              pNode->m_csAttributeName,
                              pNode->m_csContextName ?
                                     pNode->m_csContextName : "" );

   // if Flag SHOW ENTITY active, added Entity Length
   if ( (m_lStyle & zTREES_NOSHOW_ENTITY) == 0 )
      ulLth += pNode->m_csEntityName.GetLength( ) + 1;

   if ( m_lLabelEditTextLth > 0 && m_lLabelEditTextLth < ulLth )
      ulLth = m_lLabelEditTextLth;

   pEdit->SetLimitText( ulLth );

#ifdef DEBUG_ALL
   TraceLineI( "ZMSTree::OnBeginLabelEdit TextLimit: ", ulLth );
#endif

   // save Item Text to member variable, then clear Item Text so that
   // on EditLabel the Background would by empty and not show the old Item
   // Text (see OnPaint)
   if ( hItem )
   {
      if ( m_csLabelEditOldValue.IsEmpty( ) )
         m_csLabelEditOldValue = GetItemText( hItem );

      SetItemText( hItem, "" );
   }
   m_bLabelEditESC = FALSE;
   m_bLabelEdit = TRUE;
}

void
ZMSTree::OnBeginLabelEdit( NMHDR *pNMHDR, LRESULT *pResult )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnBeginLabelEdit: ", *m_pzsTag );
#endif
   TV_DISPINFO *pTVDispInfo = (TV_DISPINFO *) pNMHDR;
   // TODO: Add your control notification handler code here

   zLONG lRC = ProcessImmediateEvent( this, zTREE_EVENT_BEGIN_EDITLABEL );
// if ( lRC && lRC != zNO_APPLICATION_EVENT )
   if ( lRC != zNO_APPLICATION_EVENT && (zSHORT) zLOUSHORT( lRC ) < 0 )
   {
      *pResult = 1;
      LabelEditCleanUp( );
      return;
   }

   TV_ITEM    *pItem = &(pTVDispInfo->item);
   ZOL_Node   *pNode = 0;
   HTREEITEM  hItem  = pItem->hItem;

   if ( hItem )
      pNode = (ZOL_Node *) GetItemData( hItem );

   if ( GetViewByName( &m_vApp, m_csTreeViewName, m_vSubtask, zLEVEL_SUBTASK ) >= 0
        && pNode->m_csEntityName && pNode->m_csAttributeName )
   {
      CEdit *pEdit = GetEditControl( );
      if ( pEdit )
      {
         // if Attribute not updateable, do not allow Edit Labels
         if ( MiGetUpdateForViewEntityAttr( m_vApp,
                                            pNode->m_csEntityName,
                                            pNode->m_csAttributeName,
                                            0 ) <= 0 )
         {
            *pResult = -1;
            LabelEditCleanUp( );
            return;
         }

         InitBeginLabelEdit( pEdit, pNode, hItem );
      }
   }

   *pResult = 0;
}

zSHORT
ZMSTree::EndLabelEdit( ZOL_Node *pNode, HTREEITEM hItem,
                       LRESULT *pResult, zBOOL bError )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::EndLabelEdit: ", *m_pzsTag );
#endif
   zSHORT  nRC = 0;
   CString csItemText = "";
   CEdit   *pEdit = GetEditControl( );

   if ( pEdit )
   {
      pEdit->GetWindowText( csItemText );
      CString cs = csItemText;

      // If Flag SHOW ENTITY active, remove Entity Name from ItemText
      // for set ItemText to Attribute.
      if ( (m_lStyle & zTREES_NOSHOW_ENTITY) == 0 )
      {
         CString csEntityName = pNode->m_csEntityName + " ";
         int k = cs.Find( csEntityName );
         if ( k >= 0 )
         {
            cs.Replace( csEntityName, "" );
         }
         else
         {
            // set Entity Name
            zULONG ulLth;
            GetAttributeDisplayLength( &ulLth, m_vApp, pNode->m_csEntityName,
                                       pNode->m_csAttributeName,
                                       pNode->m_csContextName ?
                                          pNode->m_csContextName : "" );
            csItemText = pNode->m_csEntityName + " " + cs.Left( ulLth );

            // Set result to 0 to not accept the user changes.
            *pResult = 0;
         }
      }

      SetItemText( hItem, csItemText );

      if ( bError )
         return( -1 );

      zULONG ulKey = pNode->m_ulEntityKey;

      // promote changes to the view
      if ( ulKey &&
           OL_SetCursorByEntityNumber( m_vApp, pNode->m_csEntityName,
                                       ulKey ) >= zCURSOR_SET )
      {
         nRC = SetAttributeFromVariable( m_vApp,
                                         pNode->m_csEntityName,
                                         pNode->m_csAttributeName,
                                         cs, zTYPE_STRING, 0,
                                         pNode->m_csContextName,
                                         (zSHORT) ( pNode->m_csContextName ?
                                                   0 : zUSE_DEFAULT_CONTEXT ) );
      } // endif ( ulKey && OL_SetCursorByEntityNumber ... )
   } // endif ( pEdit )

   return( nRC );
}

void
ZMSTree::OnEndLabelEdit( NMHDR *pNMHDR, LRESULT *pResult )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnEndLabelEdit: ", *m_pzsTag );
#endif
   zSHORT     nRC    = 0;
   zBOOL      bError = FALSE;
   HTREEITEM  hItem  = 0;

   TV_DISPINFO *pTVDispInfo = (TV_DISPINFO *) pNMHDR;
   TV_ITEM     *pItem = &(pTVDispInfo->item);

   if ( pItem )
      hItem = pItem->hItem;

   if ( pItem == 0 || hItem == 0 )
      return;

   // Set result to TRUE to accept the changes.
   *pResult = TRUE;

#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnEndLabelEdit: ", pItem->pszText );
#endif

   // if cancel Edit Label, set old Item Text
   if ( m_bLabelEditESC && !m_csLabelEditOldValue.IsEmpty( ) )
   {
      SetItemText( hItem, m_csLabelEditOldValue );
      LabelEditCleanUp( );
      return;
   }

   GetViewByName( &m_vApp, m_csTreeViewName, m_vSubtask, zLEVEL_SUBTASK );

   ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );
   if ( m_vApp && pNode && pNode->m_csEntityName && pNode->m_csAttributeName )
   {
      zLONG lRC = ProcessImmediateEvent( this, zTREE_EVENT_END_EDITLABEL );
   // if ( lRC && lRC != zNO_APPLICATION_EVENT )
      if ( lRC != zNO_APPLICATION_EVENT && (zSHORT) zLOUSHORT( lRC ) < 0 )
      {
         bError = TRUE;
      }

      nRC = EndLabelEdit( pNode, hItem, pResult, bError );
   } // endif ( m_vApp && pNode && pNode->m_csEntityName && ....

   if ( nRC <  0 )
   {
      LabelEditError( hItem );
      *pResult = 0;
   }
   else
   {
      LabelEditCleanUp( );
   }
}

void
ZMSTree::GetLastExpandedEntityName( zPCHAR pchEntityName )
{
   strcpy_s( pchEntityName, zTAG_LTH, m_csLastExpandedEntity );
}

void
ZMSTree::GetLastCollapsedEntityName( zPCHAR pchEntityName )
{
   strcpy_s( pchEntityName, zTAG_LTH, m_csLastCollapsedEntity );
}

void
ZMSTree::GetExpandingEntityName( zPCHAR pchEntityName )
{
   strcpy_s( pchEntityName, zTAG_LTH, m_csExpandingEntity );
}

void
ZMSTree::GetCollapsingEntityName( zPCHAR pchEntityName )
{
   strcpy_s( pchEntityName, zTAG_LTH, m_csCollapsingEntity );
}

// ItemExpand with flag TVE_COLLAPSE set does not send an OnItemExpanding
// Event ... so you have to implement it on your own.
zBOOL
ZMSTree::ItemExpand( HTREEITEM hItem, UINT nCode )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::ItemExpand ", *m_pzsTag );
#endif
   zBOOL bRC = FALSE;

   if ( hItem == 0 )
      return( bRC );

   if ( nCode == TVE_EXPAND )
   {
      if ( (GetItemState( hItem, TVIS_EXPANDED ) & TVIS_EXPANDED) == 0 )
      {
         SetItemState( hItem, 0, TVIS_EXPANDEDONCE );
         bRC = Expand( hItem, nCode );
         SetItemState( hItem, 0, TVIS_EXPANDEDONCE );
      }
   }
   else
   if ( nCode == TVE_COLLAPSE )
   {
      if ( GetItemState( hItem, TVIS_EXPANDED ) & TVIS_EXPANDED )
      {
         if ( ItemExpanding( hItem, nCode ) )
            return( bRC );

         bRC = Expand( hItem, nCode );
         SetItemState( hItem, 0, TVIS_EXPANDEDONCE );

         ItemExpanded( hItem, nCode );
      }
   }

   return( bRC );
}

zLONG
ZMSTree::ItemExpanding( HTREEITEM hItem, UINT nCode )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::ItemExpanding: ", *m_pzsTag );
#endif
   zLONG lRC = 0;

   if ( m_bExpandInMapFromOI )
      return( lRC );

   if ( hItem )
   {
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );

      m_csExpandingEntity  = "";
      m_csCollapsingEntity = "";

      while ( pNode )   // purist's goto
      {
         zLONG lEvent;
         if ( nCode == TVE_COLLAPSE )
         {
            // On collapse, if a child of the parent being collapsed is
            // selected, we want to select the parent.  If that selection
            // is successful, then permit the collapse, otherwise prevent
            // the collapse.
            HTREEITEM hItemSelected = GetSelectedItem( );

            while ( hItemSelected )
            {
               if ( hItemSelected == hItem )
                  break;

               hItemSelected = GetParentItem( hItemSelected );
            }

            if ( hItemSelected == hItem )
            {
               if ( SelectItem( hItem ) == 0 )
               {
                  lRC = -1;  // don't let it collapse happen
                  break;  // out of purist's goto
               }
            }

            lEvent = zTREE_EVENT_COLLAPSING;
            m_csCollapsingEntity = pNode->m_csEntityName;
         }
         else
         if ( nCode == TVE_EXPAND )
         {
            lEvent = zTREE_EVENT_EXPANDING;
            m_csExpandingEntity = pNode->m_csEntityName;
         }
         else
            lEvent = 0;

         if ( lEvent )
            lRC = ProcessImmediateEvent( this, lEvent );

      // if ( lRC == zNO_APPLICATION_EVENT )
         if ( lRC == zNO_APPLICATION_EVENT || (zSHORT) zLOUSHORT( lRC ) >= 0 )
            lRC = 0;

         break;  // out of purist's goto

      } // end: while ( pNode )
   } // end: if ( hItem )

   // if child Entity selected, remove this selection and set selection
   // if collapsing Item
   if ( IsDesignTime( ) == FALSE && nCode == TVE_COLLAPSE && lRC == 0 )
      CheckChildSelection( hItem );

   return( lRC );
}

void
ZMSTree::OnItemExpanding( NMHDR *pNMHDR, LRESULT *pResult )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::OnItemExpanding ", *m_pzsTag );
#endif
   NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *) pNMHDR;
   // TODO: Add your control notification handler code here

   *pResult = ItemExpanding( pNMTreeView->itemNew.hItem, pNMTreeView->action );
}

void
ZMSTree::ItemExpanded( HTREEITEM hItem, UINT nCode )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::ItemExpanded: ", *m_pzsTag );
#endif
   if ( hItem )
   {
      ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );

      if ( pNode )
      {
         zLONG lEvent;

         if ( nCode == TVE_EXPAND )
         {
            lEvent = zTREE_EVENT_EXPANDED;
         // pNode->m_bOpen = TRUE;

            if ( m_bExpandInMapFromOI == FALSE )
               m_csLastExpandedEntity = pNode->m_csEntityName;
         }
         else
         if ( nCode == TVE_COLLAPSE )
         {
            lEvent = zTREE_EVENT_COLLAPSED;
         // pNode->m_bOpen = FALSE;

            if ( m_bExpandInMapFromOI == FALSE )
               m_csLastCollapsedEntity = pNode->m_csEntityName;
         }
         else
            lEvent = 0;

         m_csExpandingEntity  = "";
         m_csCollapsingEntity = "";

         if ( lEvent && m_bExpandInMapFromOI == FALSE )
            ProcessImmediateEvent( this, lEvent );
      } // endif ( pNode )
   } // endif ( hItem )
}

void
ZMSTree::OnItemExpanded( NMHDR *pNMHDR, LRESULT *pResult )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::OnItemExpanded ", *m_pzsTag );
#endif
   NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *) pNMHDR;
   // TODO: Add your control notification handler code here

   *pResult = 0;

   if ( pNMTreeView->itemNew.hItem )
   {
      ItemExpanded( pNMTreeView->itemNew.hItem, pNMTreeView->action );
   }
}

void
ZMSTree::RemoveChildSelection( HTREEITEM hItem, zPBOOL pbSetNewSelection )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::RemoveChildSelection: ", *m_pzsTag );
#endif

   if ( ItemHasChildren ( hItem ) )
   {
      HTREEITEM hChild = GetChildItem( hItem );
      while ( hChild )
      {
         if ( GetItemState( hChild, TVIS_SELECTED ) & TVIS_SELECTED )
         {
            SetItemSelState( hChild, 0, TVIS_SELECTED );
            *pbSetNewSelection = TRUE;
         }

         RemoveChildSelection( hChild, pbSetNewSelection );
         hChild = GetNextSiblingItem( hChild );
      }
   }
}

void
ZMSTree::CheckChildSelection( HTREEITEM hItem )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::CheckChildSelection: ", *m_pzsTag );
#endif
   zBOOL bSetNewSelection = FALSE;

   RemoveChildSelection( hItem, &bSetNewSelection );

   if ( bSetNewSelection )
      SelectItem( hItem );
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

ZOL_Node *
ZMSTree::GetNewNode( zCPCHAR cpcMsg, NM_TREEVIEW *pNMTreeView )
{
   ZOL_Node *pNodeNew;

   if ( pNMTreeView->itemNew.hItem )
      pNodeNew = (ZOL_Node *) GetItemData( pNMTreeView->itemNew.hItem );
   else
      pNodeNew = 0;

#ifdef DEBUG_ALL
   if ( pNodeNew && pNodeNew->m_ulEntityKey > 10000 )
      MessageBox( "Error in EntityKey", "GetNewNode" );

   ZOL_Node *pNodeOld;
   if ( pNMTreeView->itemOld.hItem )
      pNodeOld = (ZOL_Node *) GetItemData( pNMTreeView->itemOld.hItem );
   else
      pNodeOld = 0;

   TraceLine( "%s Tag: %s  OldItem: (0x%08x) %d  %s   NewItem: (0x%08x) %d  %s",
              cpcMsg, *m_pzsTag,
              pNMTreeView->itemOld.hItem, pNodeOld ? pNodeOld->m_ulEntityKey : 0,
              (zCPCHAR) (pNMTreeView->itemOld.hItem ? GetItemText( pNMTreeView->itemOld.hItem ) : ""),
              pNMTreeView->itemNew.hItem, pNodeNew ? pNodeNew->m_ulEntityKey : 0,
              (zCPCHAR) (pNMTreeView->itemNew.hItem ? GetItemText( pNMTreeView->itemNew.hItem ) : "") );
#endif

   return( pNodeNew );
}

void
ZMSTree::OnSelChanging( NMHDR *pNMHDR, LRESULT *pResult )
{
   zSHORT k = 0;

   while ( m_ulMapActFlags & zTREE_RECURSIVESELCHANGE && k < 100 )
   {
      k++;
      Sleep( 10 );
   }

   m_ulMapActFlags |= zTREE_RECURSIVESELCHANGE;
   NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *) pNMHDR;
   ZOL_Node *pNodeNew = GetNewNode( "ZMSTree::OnSelChanging1", pNMTreeView );
   zLONG  lRC;
// static zBOOL bPreRecurse = FALSE;

#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnSelChanging Tag: ", *m_pzsTag );
#endif

// *pResult = 1;  // prevent SelChanged message

// if ( bPreRecurse ||
   if ( (m_ulMapActFlag2 & zMAPACT_MAPPING_FROM_OI) ||
        (m_ulMapActFlags & zTREE_SETFOCUS) )
   {
     *pResult = 0;  // permit SelChanged message
     return;
   }

// bPreRecurse = TRUE;

   if ( m_bPreSelectChangeAlreadyDone == FALSE )
   {
      lRC = ProcessImmediateEvent( this, zTREE_EVENT_PRESELECT_CHANGE );
   }
   else
   {
      m_bPreSelectChangeAlreadyDone = FALSE;
      lRC = 0;
   }

// bPreRecurse = FALSE;

// GetNewNode( "ZMSTree::OnSelChanging2", pNMTreeView );
// if ( lRC == zNO_APPLICATION_EVENT )
   if ( lRC == zNO_APPLICATION_EVENT || (zSHORT) zLOUSHORT( lRC ) >= 0 )
      *pResult = 0;  // permit SelChanged message
   else
      *pResult = lRC;

   if ( pNodeNew )
      m_ulKeyLast = pNodeNew->m_ulEntityKey;

#ifdef DEBUG_ALL
   TraceLine( "ZMSTree::OnSelChanging Key: %d       Result: %d",
              m_ulKeyLast, *pResult );
#endif

   if ( *pResult )  // only if we are preventing the SelChange
      m_ulMapActFlags &= ~zTREE_RECURSIVESELCHANGE;
}

void
ZMSTree::OnSelChanged( NMHDR *pNMHDR, LRESULT *pResult )
{
   NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *) pNMHDR;
   ZOL_Node *pNodeNew = GetNewNode( "ZMSTree::OnSelChanged1", pNMTreeView );

#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnSelChanged Tag: ", *m_pzsTag );
#endif

// static zBOOL bSelRecurse = FALSE;
   *pResult = 0;

// if ( bSelRecurse ||
   if ( ((m_ulMapActFlag2 & zMAPACT_MAPPING_FROM_OI) ||
         (m_ulMapActFlags & zTREE_SETFOCUS)) ||
        m_bSetMultiSelection )
   {
      m_ulMapActFlags &= ~zTREE_RECURSIVESELCHANGE;
      return;
   }

// bSelRecurse = TRUE;

// GetNewNode( "ZMSTree::OnSelChanged2", pNMTreeView );
   HWND  hWnd = m_hWnd;
   zLONG lRC = 0;
   if ( pNodeNew )
   {
      m_ulKeyLast = pNodeNew->m_ulEntityKey;

#ifdef DEBUG_ALL
      TraceLineI( "ZMSTree::OnSelChanged Key: ", m_ulKeyLast );
#endif

      // Promote changes to the view.
      if ( m_ulKeyLast &&
           GetViewByName( &m_vApp, m_csTreeViewName,
                          m_vSubtask, zLEVEL_SUBTASK ) >= 0 )
      {
         zSHORT nRC = OL_SetCursorByEntityNumber( m_vApp,
                                                  pNodeNew->m_csEntityName,
                                                  m_ulKeyLast );
         if ( nRC < zCURSOR_SET )
         {
            zCHAR szEntityName[ zTAG_LTH ];

            strcpy_s( szEntityName, zsizeof( szEntityName ), pNodeNew->m_csEntityName );
            GetRealEntityName( m_vApp, szEntityName );
            if ( zstrcmp( szEntityName, pNodeNew->m_csEntityName.GetString() ) != 0 )
            {
               nRC = OL_SetCursorByEntityNumber( m_vApp,
                                                 szEntityName,
                                                 m_ulKeyLast );
            }
         }

         if ( nRC < zCURSOR_SET )
         {
            TraceLineS( "ZMSTree::OnSelChanged : cannot set cursor to Entity ",
                         pNodeNew->m_csEntityName );
         }
         else
         {
            if ( pNMTreeView->itemNew.hItem )
            {
               if ( CanMultiSelect( ) == FALSE ||
                    (((GetKeyState( VK_SHIFT ) & 0x8000) == 0 &&
                     (GetKeyState( VK_CONTROL ) & 0x8000)) == 0) )
               {
                  ResetViewForDefaultSelectSet( m_vApp ); // resetting select states here!
                  ClearSelection( );
               }

               if ( IsDesignTime( ) )
               {
                  SetItemState( pNMTreeView->itemNew.hItem,
                                TVIS_SELECTED, TVIS_SELECTED );
               }
               else
               {
                  SetItemSelState( pNMTreeView->itemNew.hItem,
                                   TVIS_SELECTED, TVIS_SELECTED );
               }
            }
         }
      }

      lRC = ProcessImmediateEvent( this, zTREE_EVENT_SELECT_CHANGE );
   }

   if ( mIs_hWnd( hWnd ) )
   {
      if ( lRC > 0 )
         *pResult = lRC;

//    bSelRecurse = FALSE;

#ifdef DEBUG_ALL
      TraceLine( "ZMSTree::OnSelChanged Key: %d       Result: %d",
                 m_ulKeyLast, *pResult );
#endif

      m_ulMapActFlags &= ~zTREE_RECURSIVESELCHANGE;
   }
}

// Return entity key of currently selected item.
zULONG
ZMSTree::GetSelectedNodeEntityKey( )
{
   zULONG ulKey = 0;
   if ( m_ulKeyLast )
   {
      ulKey = m_ulKeyLast;
   }
   else
   {
      HTREEITEM hItem = GetSelectedItem( );
      if ( hItem )
      {
         ZOL_Node *pNode = (ZOL_Node *) GetItemData( hItem );
         ulKey = pNode->m_ulEntityKey;
      }
   }

#ifdef DEBUG_ALL
   TraceLine( "ZMSTree::GetSelectedNodeEntityKey Tag: %s       EntityKey: %d", *m_pzsTag, ulKey );
#endif
   return( ulKey );
}

zBOOL
ZMSTree::CanMultiSelect( )
{
#ifdef DEBUG_ALL
// TraceLineS( "ZMSTree::CanMultiSelect: ", *m_pzsTag );
#endif
   return( (m_lStyle & zTREES_MULTISEL) == zTREES_MULTISEL );
}

void
ZMSTree::DeselectAllEntities( )
{
// return;  // must be implemented on your own
// TraceLineS( "ZMSTree::DeselectAllEntities ", *m_pzsTag );
   SelectItem( 0 );
   m_hItemFirstSel = 0;

#if 1
   HTREEITEM hItem;

   while ( (hItem = GetSelectedItem( )) != 0 )
      SetItemState( hItem, 0, TVIS_SELECTED );

#else
   for ( HTREEITEM hItem = GetRootItem( );
         hItem;
         hItem = GetNextItemPhysical( hItem ) )
   {
      SetItemState( hItem, 0, TVIS_SELECTED );
   }
#endif
}

// Determine the name of the root entity by retrieving the first
// child of Dummy m_pRootEntry and getting its entity name.
CString
ZMSTree::GetRootEntityName( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::GetRootEntityName: ", *m_pzsTag );
#endif
   ZOL_Node *pRoot = 0;
   CString  csEntity;

   POSITION pos = m_pRootEntry->GetFirstChildPosition( );
   if ( pos )
   {
      pRoot = m_pRootEntry->GetNextChild( pos );
      csEntity = pRoot->m_csEntityName;
   }
   else
   {
      csEntity.Empty( );
   }

   return( csEntity );
}

void
ZMSTree::OnHScroll( UINT uSBCode, UINT uThumbPos,
                    CScrollBar *pScrollBar )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnHScroll: ", *m_pzsTag );
#endif
   if ( uSBCode == SB_PAGEUP || uSBCode == SB_PAGEDOWN )
   {
      SetRedraw( FALSE );
      CTreeCtrl::OnHScroll( uSBCode, uThumbPos, pScrollBar );
      SetRedraw( TRUE );
      Invalidate( );
   }
   else
      CTreeCtrl::OnHScroll( uSBCode, uThumbPos, pScrollBar );
}

void
ZMSTree::OnVScroll( UINT uSBCode, UINT uThumbPos,
                    CScrollBar *pScrollBar )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::OnVScroll: ", *m_pzsTag );
#endif
   if ( uSBCode == SB_PAGEUP || uSBCode == SB_PAGEDOWN )
   {
      SetRedraw( FALSE );
      CTreeCtrl::OnVScroll( uSBCode, uThumbPos, pScrollBar );
      SetRedraw( TRUE );
      Invalidate( );
   }
   else
      CTreeCtrl::OnVScroll( uSBCode, uThumbPos, pScrollBar );
}

void
ZMSTree::ParentResize( ZMapAct *pParent,
                       CSize   *pSize )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::ParentResize: ", *m_pzsTag );
#endif
   mDeleteInit( m_pBitmap1 );
   mDeleteInit( m_pBitmap2 );
   ZMapAct::ParentResize( pParent, pSize ); // default processing
}

#ifdef zREMOTE_SERVER

void
ZMSTree::HandleRemoteState( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMSTree::HandleRemoteState: ", *m_pzsTag );
#endif
   zVIEW  vXRA = SetupRemoteObject( );
   zSHORT nRC = 0;
   if ( vXRA )
   {
      nRC = CheckExistenceOfEntity( vXRA, m_csTreeSelectionEntity );
      if ( nRC < zCURSOR_SET )
      {
         // no entries so current selection is still valid
         return;
      }
      else
      {
         DeselectAllEntities( );
         nRC = SetCursorFirstEntity( vXRA, m_csTreeSelectionEntity, m_csTree );
         while ( nRC >= zCURSOR_SET )
         {
            zULONG ulKey;
            GetIntegerFromAttribute( &ulKey, vXRA, m_csTreeSelectionEntity,
                                     m_csTreeSelectionTag );
            ZOL_Node *pNode = m_pRootEntry->FindNodeByEntityKey( ulKey );
            ToggleSelection( pNode );
            nRC = SetCursorNextEntity( vXRA, m_csTreeSelectionEntity, m_csTree );
         }
      }
   }
}

#endif   // zREMOTE_SERVER

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Offsets for first and other columns.
// #define OFFSET_FIRST   2
// #define OFFSET_OTHER   6
#define LEFT_MARGIN 4
#define RIGHT_MARGIN 4
#define TOP_MARGIN 4
#define BOTTOM_MARGIN 4

#if 0
void CPrtTViewView::OnPrepareDC( CDC *pDC, CPrintInfo *pInfo )
{
   CTreeView::OnPrepareDC( pDC, pInfo );

   // Map logical unit of screen to printer unit
   pDC->SetMapMode( MM_ANISOTROPIC );
   CClientDC dcScreen( 0 );
   pDC->SetWindowExt( dcScreen.GetDeviceCaps( LOGPIXELSX ), dcScreen.GetDeviceCaps( LOGPIXELSX ) );
   pDC->SetViewportExt( pDC->GetDeviceCaps( LOGPIXELSX ), pDC->GetDeviceCaps( LOGPIXELSX ) );
}
#endif

zBOOL
ZMSTree::PrintZCtrl( zBOOL bTest, zCPCHAR cpcTitle, zLONG lFlags,
                     zSHORT nFontSize, zCPCHAR cpcFontFace )
{
   if ( m_pZSubtask && bTest == FALSE )
   {
      zBOOL  bPrompt;

      m_csTitle = cpcTitle;
      m_lPrintFlags = lFlags;
   // m_nLinesPerPage = 0;
      m_nTextHeight = -1;
      m_bPrintPreview = FALSE;

      HTREEITEM hItem = GetRootItem( );
      CRect rect;

      GetItemRect( hItem, m_rectBounds, TRUE );
      m_nRowHeight = m_rectBounds.Height( );

      // Find the total number of visible items and the right most coordinate.
      m_lTreeItemCnt = 0;

      do
      {
         m_lTreeItemCnt++;
         GetItemRect( hItem, rect, TRUE );
         if ( rect.right > m_rectBounds.right )
            m_rectBounds.right = rect.right;

      // hItem = GetNextItem( hItem, TVGN_NEXTVISIBLE );
         hItem = GetNextTreeItem( hItem );

      } while ( hItem );
#if 0
      // Find the entire print boundary - another way!!!
      int nScrollMin;
      int nScrollMax;

      GetScrollRange( SB_HORZ, &nScrollMin, &nScrollMax );
      m_rectBounds.left = 0;
      if ( nScrollMax > m_rectBounds.right )
         m_rectBounds.right = nScrollMax + 1;

      m_rectBounds.top = 0;
      m_rectBounds.bottom = m_nRowHeight * m_lTreeItemCnt;
      // Find the entire print boundary - another way!!!
#endif
      lFlags = zREPORT_REVERSE_PARM;
      lFlags |= (m_lPrintFlags & 0x00000002) ? zREPORT_LANDSCAPE : 0;
      lFlags |= (m_lPrintFlags & 0x00000004) ? zREPORT_PRINTPREVIEW : 0;
      lFlags |= (m_lPrintFlags & 0x00000010) ? zREPORT_PRINT2CSV : 0;
      bPrompt = (m_lPrintFlags & 0x00000008) ? TRUE : FALSE;

      OpenReport( m_pZSubtask->m_vDialog, "ZDRAPP", "PrintCtrlPage",
                  lFlags, TRUE, TRUE, bPrompt,
                  cpcTitle, (zPCHAR)(zCPCHAR) *m_pzsTag );
   }

   return( TRUE );  // this ctrl can be printed!
}

#define pDC   pZSubtask->m_pZPrintout->m_pDC

zSHORT
ZMSTree::PrintZPage( zLONG      lPageNbr,
                     zLONG  lPageWidth,
                     zLONG  lPageHeight )
{
   ZSubtask *pZSubtask;
   HTREEITEM hItem;
   zCHAR   szText[ 512 ];
   zLONG   lRow;
   CString cs;
   CFont   *pFontOld = 0;
   int     nOldMapMode;
   zBOOL   bPrintCSV;

   if ( m_pZSubtask && m_pZSubtask->m_pZTask &&
        m_pZSubtask->m_pZTask->m_pZSubtaskPrint )
   {
      pZSubtask = m_pZSubtask->GetSplitterMainSubtask( );
      if ( pZSubtask == 0 )
         pZSubtask = m_pZSubtask;
   }
   else
      pZSubtask = m_pZSubtask;

   if ( pZSubtask == 0 ||
        pZSubtask->m_pZPrintout == 0 ||
        pZSubtask->m_pZPrintout->m_pDC == 0 ||
        pZSubtask->m_pZPrintout->m_pDC->m_hDC == 0 )
   {
      return( 0 );
   }

   ZPrintout *pZPrintout = pZSubtask->m_pZPrintout;
   if ( pZPrintout->m_bPrintToCSV &&  // printing CSV file
        pZPrintout->m_lFileCSV >= 0 )
   {
      bPrintCSV = TRUE;
   }
   else
   {
      bPrintCSV = FALSE;
   }

   // -1, -2 ==> BeginPrint ... -3, -4 ==> EndPrint ... -2, -4 ==> PrintPreview
   if ( lPageNbr < 0 || m_hDIB == 0 )
   {
      if ( lPageNbr == -2 || lPageNbr == -4 )
         m_bPrintPreview = TRUE;

      if ( lPageNbr == -1 || lPageNbr == -2  || m_hDIB == 0 )
      {
         // Get text width
         CDC *pCtlDC = GetDC( );
         if ( pCtlDC == 0 )
            return( 0 );

         TEXTMETRIC tm;
         pCtlDC->GetTextMetrics( &tm );
         m_nCharWidth = (zSHORT) tm.tmAveCharWidth;
         double d = (double) pDC->GetDeviceCaps( LOGPIXELSY ) /
                                (double) pCtlDC->GetDeviceCaps( LOGPIXELSY );
         ReleaseDC( pCtlDC );

         // Find rows per page.
      // int nPageHeight = pDC->GetDeviceCaps( VERTRES );
      // m_nLinesPerPage = (int) ((double) nPageHeight / d ) /
      //                           m_nRowHeight - TOP_MARGIN - BOTTOM_MARGIN;

         // Set maximum pages.
      // m_lMaxPage = ((m_lTreeItemCnt - 1) / m_nLinesPerPage) + 1;

         // Create a memory DC compatible with the paint DC.
         CPaintDC dc( this );
         CDC MemDC;
         MemDC.CreateCompatibleDC( &dc );

         // Select a compatible bitmap into the memory DC
         CBitmap bitmap;
         bitmap.CreateCompatibleBitmap( &dc, m_rectBounds.Width( ), m_rectBounds.Height( ) );
         MemDC.SelectObject( &bitmap );
#if 0
         // Enlarge window size to include the whole print area boundary
         GetWindowPlacement( &m_WndPlace );
         MoveWindow( 0, 0, ::GetSystemMetrics( SM_CXEDGE ) * 2 + m_rectBounds.Width( ),
                     ::GetSystemMetrics( SM_CYEDGE ) * 2 + m_rectBounds.Height( ), FALSE );
         ShowScrollBar( SB_BOTH, FALSE );

         // Call the default printing.
         EnsureVisible( GetRootItem( ) );
         CWnd::DefWindowProc( WM_PAINT, (WPARAM) MemDC.m_hDC, 0 );
#endif
         // Now create a mask.
         CDC MaskDC;
         MaskDC.CreateCompatibleDC( &dc );
         CBitmap maskBitmap;

         // Create monochrome bitmap for the mask.
         maskBitmap.CreateBitmap( m_rectBounds.Width( ), m_rectBounds.Height( ), 1, 1, 0 );
         MaskDC.SelectObject( &maskBitmap );
         MemDC.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );

         // Create the mask from the memory DC.
         MaskDC.BitBlt( 0, 0, m_rectBounds.Width( ), m_rectBounds.Height( ), &MemDC,
                        m_rectBounds.left, m_rectBounds.top, SRCCOPY );

         // Copy image to clipboard.
         CBitmap clipBitmap;
         clipBitmap.CreateCompatibleBitmap( &dc, m_rectBounds.Width( ), m_rectBounds.Height( ) );
         CDC clipDC;
         clipDC.CreateCompatibleDC( &dc );
         CBitmap *pOldBitmap = clipDC.SelectObject( &clipBitmap );
         clipDC.BitBlt( 0, 0, m_rectBounds.Width( ), m_rectBounds.Height( ), &MemDC,
                        m_rectBounds.left, m_rectBounds.top, SRCCOPY );
         OpenClipboard( );
         EmptyClipboard( );
         SetClipboardData( CF_BITMAP, clipBitmap.GetSafeHandle( ) );
         CloseClipboard( );
         clipDC.SelectObject( pOldBitmap );
         clipBitmap.Detach( );

         // Copy the image in MemDC transparently.
         MemDC.SetBkColor( RGB( 0, 0, 0 ) );
         MemDC.SetTextColor( RGB( 255, 255, 255 ) );
         MemDC.BitBlt( m_rectBounds.left, m_rectBounds.top,
                       m_rectBounds.Width( ), m_rectBounds.Height( ),
                       &MaskDC, m_rectBounds.left, m_rectBounds.top, MERGEPAINT );

         CPalette pal;
         m_hDIB = DDBToDIB( bitmap, BI_RGB, &pal );
      // TraceLineS( "ZMSTree::PrintZPage creating hDIB", "" );

         nOldMapMode = pDC->SetMapMode( MM_TEXT );

         m_pFontNormal = new CFont;
         m_pFontBold = new CFont;
         m_pFontItalic = new CFont;
         m_pFontUnderline = new CFont;
         m_pFontNormal->CreatePointFont( 90, "Arial", pDC );
         LOGFONT lf;
         m_pFontNormal->GetLogFont( &lf );
         lf.lfWeight = FW_BOLD;
         m_pFontBold->CreateFontIndirect( &lf );
         lf.lfWeight = 0;
         lf.lfItalic = TRUE;
         m_pFontItalic->CreateFontIndirect( &lf );
         lf.lfItalic = FALSE;
         lf.lfUnderline = TRUE;
         m_pFontUnderline->CreateFontIndirect( &lf );

         m_rectDraw.SetRect( 0, 0, pDC->GetDeviceCaps( HORZRES ),
                             pDC->GetDeviceCaps( VERTRES ) );
         pDC->DPtoLP( &m_rectDraw );

         CRect rectMarginMM( 1, 1, 1, 1 );  // hardwired
         CSize sizeUp( rectMarginMM.left * 100, rectMarginMM.top * 100 );
         CSize sizeDown( rectMarginMM.right * 100, rectMarginMM.bottom * 100 );
         pDC->HIMETRICtoDP( &sizeUp );
         pDC->HIMETRICtoDP( &sizeDown );
         m_rectDraw.top  += sizeUp.cy;
         m_rectDraw.left += sizeUp.cx;
         m_rectDraw.right -= sizeDown.cx;
         m_rectDraw.bottom -= sizeDown.cy;

         pFontOld = pDC->SelectObject( m_pFontNormal );
         CSize szNormal = pDC->GetTextExtent( "JjQqWwYy" );
         szNormal.cx /= 8;
         pDC->SelectObject( m_pFontBold );
         CSize szBold = pDC->GetTextExtent( "JjQqWwYy" );
         szBold.cx /= 8;
         m_nTextHeight = (zSHORT) szNormal.cy;
         m_nTextHeightBold = (zSHORT) szBold.cy;
         m_nLinesPerPage = (m_rectDraw.Height( ) - (m_nTextHeightBold * 16)) / m_nTextHeight;
      // TraceLineI( "Print Tree Lines Per Page: ", m_nLinesPerPage );
         m_lMaxPage = (m_lTreeItemCnt / m_nLinesPerPage) + 1;

         pDC->SetMapMode( nOldMapMode );
         pDC->SelectObject( pFontOld );
         pFontOld = 0;
      }
      else
      if ( lPageNbr == -3 || lPageNbr == -4 )
      {
      // TraceLineS( "ZMSTree::PrintZPage freeing hDIB", "" );
         if ( bPrintCSV )
            PrintTextToCSV( m_pZSubtask->m_vDialog, 0, 0 );

         GlobalFree( m_hDIB );
         m_hDIB = 0;
      // SetWindowPlacement( &m_WndPlace );
      // RedrawWindow( );

         mDeleteInit( m_pFontNormal );
         mDeleteInit( m_pFontBold );
         mDeleteInit( m_pFontItalic );
         mDeleteInit( m_pFontUnderline );
      }

      if ( lPageNbr < 0 || m_hDIB == 0 )
         return( 0 );
   }

   // It's a Multiset list page.
   CFont    font;
   LOGFONT  lf;
   int      nLineNbr = 1;

   pDC->SaveDC( );
   pDC->SetBkMode( TRANSPARENT );

   GetFont( )->GetLogFont( &lf );

   // This aims to get the same size font for the printer as in use by the control
   // on the screen printer resolution.
   lf.lfHeight = -MulDiv(abs( lf.lfHeight ), pDC->GetDeviceCaps( LOGPIXELSY ), 72 );
      VERIFY( font.CreateFontIndirect( &lf ) );

   pDC->SelectObject( &font );

   CString csText( "A" );
   m_sizeChar = pDC->GetTextExtent( csText );

   zSHORT  nRC = 0;
   nOldMapMode = pDC->SetMapMode( MM_TEXT );
   pFontOld = pDC->SelectObject( m_pFontNormal );

// CPen penShadow( PS_SOLID, 1, ::GetSysColor( COLOR_GRAYTEXT ) );
   CPen penShadow( PS_SOLID, 1, RGB( 128, 128, 128 ) );
   CPen *pOldPen = pDC->SelectObject( &penShadow );

   CRect rect( m_rectDraw );
   CRect rectMarginMM( 10, 10, 5, 10 );  // hardwired

   CSize sizeUp( rectMarginMM.left * 100, rectMarginMM.top * 100 );
   CSize sizeDown( rectMarginMM.right * 100, rectMarginMM.bottom * 100 );
   pDC->HIMETRICtoDP( &sizeUp );
   pDC->HIMETRICtoDP( &sizeDown );
   rect.top += sizeUp.cy;
   rect.left += sizeUp.cx;
   rect.right -= sizeDown.cx;
   rect.bottom -= sizeDown.cy;

   zSHORT nOldBkMode = pDC->SetBkMode( TRANSPARENT );
   pFontOld = pDC->SelectObject( m_pFontNormal );

   CSize szNormal = pDC->GetTextExtent( "JjQqWwYy" );
   szNormal.cx /= 8;
   pDC->SelectObject( m_pFontBold );
   CSize szBold = pDC->GetTextExtent( "JjQqWwYy" );
   szBold.cx /= 8;

   CRect rectItem( rect );

   rectItem.top += TOP_MARGIN;
   rectItem.top -= m_nTextHeightBold;
   rectItem.bottom = rectItem.top;
   rectItem.top -= m_nTextHeightBold;

   GetWindowText( cs );
   if ( cs.IsEmpty( ) )
      m_pZSubtask->m_pZFWnd->GetWindowText( cs );

   if ( cs.IsEmpty( ) )
   {
      cs = *(m_pZSubtask->m_pzsDlgTag);
      cs += ".";
      cs += *(m_pZSubtask->m_pzsWndTag);
      cs += ".";
      cs += *m_pzsTag;
   }

   pZPrintout->RptDrawText( pDC, cs, rectItem,
                            DT_SINGLELINE | DT_VCENTER | DT_LEFT );

   if ( pZPrintout->m_csReportInfo.IsEmpty( ) )
      cs = pZPrintout->m_csReportDefName;
   else
      cs = pZPrintout->m_csReportInfo;

   cs += "   ";
   SysGetDateTime( szText, zsizeof( szText ) );
   szText[ 14 ] = 0;
   fnFormatString( szText, "####.##.##  ##:##:##" );
   cs += szText;
   pZPrintout->RptDrawText( pDC, cs, rectItem, DT_SINGLELINE | DT_VCENTER | DT_RIGHT );

   rectItem = rect;
   rectItem.bottom = rectItem.top + szNormal.cy;

// pDC->SelectObject( m_pFontBold );
// zLONG x1 = rect.left, x2 = rect.left;

// pDC->SelectObject( &penShadow );
   pZPrintout->RptMoveTo( pDC, rectItem.right - 1, rectItem.top - 1 );
   pZPrintout->RptLineTo( pDC, rectItem.left - sizeUp.cx / 2, rectItem.top - 1 );
// pZPrintout->RptLineTo( pDC, rectItem.left, rectItem.bottom - 1 );
// pZPrintout->RptLineTo( pDC, rectItem.right - 1, rectItem.bottom - 1 );
// rectItem.OffsetRect( 0, szNormal.cy );

   pDC->SelectObject( m_pFontNormal );

   // Position to the first visible item for the current page.
   hItem = GetRootItem( );
   zLONG lFirst = 0;
   zLONG lLast = (lPageNbr - 1) * m_nLinesPerPage;

// TraceLine( "ZMSTree::PrintZPage PageNbr: %d       Root Item: 0x%08x",
//            lPageNbr, hItem );

   if ( lLast > m_lTreeItemCnt )
      lLast = m_lTreeItemCnt;

   while ( lFirst < lLast )  // skip thru first lPageNbr - 1 items
   {
      lFirst++;
   // hItem = GetNextItem( hItem, TVGN_NEXTVISIBLE );
      hItem = GetNextTreeItem( hItem );
   }

   lLast = lFirst + m_nLinesPerPage;
   if ( lLast > m_lTreeItemCnt || bPrintCSV )
      lLast = m_lTreeItemCnt;

   for ( lRow = lFirst; lRow < lLast; lRow++ )
   {
#if 0
      TV_ITEM tvi;
      tvi.mask = TVIF_TEXT | TVIF_STATE | TVIF_CHILDREN;
      tvi.hItem = hItem;
      tvi.stateMask = 0xFFFF;      // get all state flags
      GetItem( &tvi );
#endif

      if ( bPrintCSV )
         PrintTextToCSV( m_pZSubtask->m_vDialog, 0, 0 );

      // calculate the rectangle for this tree item
      CRect rect( m_rectDraw.left + (m_sizeChar.cx * 2),
                  m_rectDraw.top + TOP_MARGIN + (m_sizeChar.cy * (nLineNbr + 2)),
                  m_rectDraw.left + m_rectDraw.Width( ),
                  m_rectDraw.top + TOP_MARGIN + (m_sizeChar.cy * (nLineNbr + 3)));

      if ( bPrintCSV )
      {
         HTREEITEM hParentItem = hItem;
         zSHORT  nCol = 0;
         CString csText = GetItemText( hItem );

         while ( (hParentItem = GetParentItem( hParentItem )) != 0 )
            nCol++;

         PrintTextToCSV( m_pZSubtask->m_vDialog, csText, nCol + 1 );
      }

      DrawTreeItem( pZPrintout, hItem, pDC, rect, this );
      nLineNbr++;

   // rectItem.OffsetRect( 0, szNormal.cy );
   // hItem = GetNextItem( hItem, TVGN_NEXTVISIBLE );
      hItem = GetNextTreeItem( hItem );
   }

// if ( lPageNbr > 1 )
   {
      zCHAR  szPageNbr[ 32 ];
      zSHORT k;

      _ltoa_s( lPageNbr, szPageNbr, zsizeof( szPageNbr ), 10 );
      k = (zSHORT) zstrlen( szPageNbr );
      szPageNbr[ k ] = '/';
      _ltoa_s( m_lMaxPage, szPageNbr + k + 1, zsizeof( szPageNbr ) - k - 1, 10 );
      rectItem = m_rectDraw;
      rectItem.bottom -= BOTTOM_MARGIN;
      rectItem.top = rectItem.bottom - (3 * m_nTextHeightBold);
      pDC->SelectObject( m_pFontBold );
      pZPrintout->RptDrawText( pDC, szPageNbr, rectItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER );
   }

   // Restore the pen, font, map mode, and background mode.
   pDC->SelectObject( pOldPen );
   pDC->SelectObject( pFontOld );
   pDC->SetMapMode( nOldMapMode );
   pDC->SetBkMode( nOldBkMode );

   VERIFY( pDC->RestoreDC( -1 ) );
   VERIFY( font.DeleteObject( ) );

   if ( lLast >= m_lTreeItemCnt )
      nRC = 0;
   else
      nRC = 1;     // more pages

   return( nRC );
}


#undef pDC


void
ZMSTree::PrintHeadFoot( CDC *pDC, zLONG lPage )
{
   zCHAR     szText[ 512 ];
   CClientDC dcScreen( 0 );
   CRect     rectFooter;

   rectFooter.top = m_nRowHeight * (TOP_MARGIN - 2);
   rectFooter.bottom = (int) ((double) (pDC->GetDeviceCaps( VERTRES ) *
      dcScreen.GetDeviceCaps( LOGPIXELSY )) / (double) pDC->GetDeviceCaps( LOGPIXELSY ) );
   rectFooter.left = LEFT_MARGIN * m_nCharWidth;
   rectFooter.right = (int) ((double) ( pDC->GetDeviceCaps( HORZRES ) *
      dcScreen.GetDeviceCaps( LOGPIXELSX )) / (double) pDC->GetDeviceCaps( LOGPIXELSX )) -
      RIGHT_MARGIN * m_nCharWidth;

   // Print App title on top left corner.
   CString csTemp( m_csTitle );

   SysGetDateTime( szText, zsizeof( szText ) );
   szText[ 14 ] = 0;
   fnFormatString( szText, "####.##.##  ##:##:##" );
   csTemp += szText;

   CRect rectHeader( rectFooter );
   rectHeader.bottom = rectHeader.top + m_nRowHeight;
   pDC->DrawText( csTemp, rectHeader, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER );

   rectFooter.top = rectFooter.bottom - m_nRowHeight * (BOTTOM_MARGIN - 1);
   rectFooter.bottom = rectFooter.top + m_nRowHeight;

   // Print draw page number at bottom center.
   csTemp.Format( "Page %d/%d", lPage, m_lMaxPage );
   pDC->DrawText( csTemp, rectFooter, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

HTREEITEM
ZMSTree::GetNextTreeItem( HTREEITEM hItem )
{
   // we return the next HTEEITEM for a tree such as:
   // Root (1)
   //    Child1 (2)
   //       xxxx (3)
   //       yyyy (4)
   //    Chiled2 (5)
   // Item (6)

   // Does this item have any children?
   if ( ItemHasChildren( hItem ) )
   {
      return( GetNextItem( hItem, TVGN_CHILD ) );
   }
   else
   if ( GetNextItem( hItem, TVGN_NEXT ) != 0 )
   {
      // The next item at this level.
      return( GetNextItem( hItem, TVGN_NEXT ) );
   }
   else
   {
      HTREEITEM hItemOrig = hItem;

      // Return the next item after our parent.
      hItem = GetParentItem( hItem );
      if ( hItem == 0 )
      {
         // no parent
         return( 0 );
      }

      while ( GetNextItem( hItem, TVGN_NEXT ) == 0 )
      {
         hItem = GetParentItem( hItem );
         if ( hItem == 0 )
         {
            hItem = hItemOrig;
            break;
         }
      }

      // Next item that follows our parent.
      return( GetNextItem( hItem, TVGN_NEXT ) );
   }
}

zLONG
ZMSTree::GetIndentLevelStyle( HTREEITEM hPrintItem, HTREEITEM hIndentItem )
{
   eDRAW_TYPES eDrawType = eNone;
   zBOOL bHasButtons = ((::GetWindowLong( m_hWnd, GWL_STYLE ) & TVS_HASBUTTONS) != 0);
   zBOOL bHasLines = ((::GetWindowLong( m_hWnd, GWL_STYLE ) & TVS_HASLINES) != 0);
   zBOOL bHasChildren = (ItemHasChildren( hPrintItem ) != 0);
   zBOOL bIsSiblingItem = (GetNextItem( hPrintItem, TVGN_NEXT ) != 0);
   zBOOL bIsExpanded = (GetItemState( hPrintItem, TVIS_EXPANDED ) != 0);

   if ( bHasButtons )
   {
      if ( bHasLines )
      {
         if ( hPrintItem == hIndentItem )
         {
            // We're drawing this at the actual item level.
            if ( bHasChildren )
            {
               if ( bIsSiblingItem )
               {
                  if ( bIsExpanded )
                  {
                     eDrawType = eMinusDrop;
                  }
                  else
                  {
                     eDrawType = ePlusDrop;
                  }
               }
               else
               {
                  if ( bIsExpanded )
                  {
                     eDrawType = eMinus;
                  }
                  else
                  {
                     eDrawType = ePlus;
                  }
               }
            }
            else
            {
               if ( bIsSiblingItem )
               {
                  eDrawType = eLinkDrop;
               }
               else
               {
                  eDrawType = eLink;
               }
            }
         }
         else
         {
            // this is a level above the current one
            bool bIsSiblingItem = (GetNextItem( hIndentItem, TVGN_NEXT ) != 0);
            if ( bIsSiblingItem )
            {
               eDrawType = eDrop;
            }
         }
      }
      else
      {
         // buttons, but no lines
         if ( hPrintItem == hIndentItem )
         {
            // were drawing this at the actual item level
            if ( bHasChildren )
            {
               if ( bIsExpanded )
               {
                  eDrawType = eMinus;
               }
               else
               {
                  eDrawType = ePlus;
               }
            }
         }
      }
   }
   else
   {
      if ( bHasLines )
      {
         // we are not drawing any [+] or [-] buttons
         if ( hPrintItem == hIndentItem )
         {
            // were drawing this at the actual item level
            if ( bIsSiblingItem )
            {
               eDrawType = eLinkDrop;
            }
            else
            {
               eDrawType = eLink;
            }
         }
         else
         {
            // this is a level above the current one
            bool bIsSiblingItem = (GetNextItem( hIndentItem, TVGN_NEXT ) != 0);
            if ( bIsSiblingItem )
            {
               eDrawType = eDrop;
            }
         }
      }
   }

   return( eDrawType );
}

void
ZMSTree::DrawTreeStyle( ZPrintout *pZPrintout, CDC *pDC, CRect box, eDRAW_TYPES type )
{
   if ( (pZPrintout && (pZPrintout->m_bPrintToCSV ||
        pZPrintout->m_bPrintToHTML || pZPrintout->m_bPrintToPDF)) || pDC == 0 )
   {
      return;
   }

   CPen  penDark( PS_SOLID, 1, GetSysColor( COLOR_3DSHADOW ) );
   CPen  penBlack( PS_SOLID, 3, RGB( 0, 0, 0 ) );
   CPen  *pOldPen;
   int   quarterX = box.Width( ) / 4;
   int   quarterY = box.Height( ) / 4;
   zBOOL bHasLines = ((::GetWindowLong( m_hWnd, GWL_STYLE ) & TVS_HASLINES) != 0);

   switch ( type )
   {
      case eNone:
         break;   // draw nothing for this

      case ePlus:
         // [+]-
         // []
         pOldPen = pDC->SelectObject( &penDark );
         pDC->MoveTo( box.left + quarterX, box.top + quarterY );
         pDC->LineTo( box.right - quarterX, box.top + quarterY );
         pDC->LineTo( box.right - quarterX, box.bottom - quarterY );
         pDC->LineTo( box.left + quarterX, box.bottom - quarterY );
         pDC->LineTo( box.left + quarterX, box.top + quarterY );
         if ( bHasLines )
         {
            pDC->MoveTo( box.right - quarterX, box.top + box.Height( ) / 2 );
            pDC->LineTo( box.right, box.top + box.Height( ) / 2 );
         }

         pDC->SelectObject( &penBlack );
         pDC->MoveTo( box.left + box.Width( ) / 2, box.top + quarterY );
         pDC->LineTo( box.left + box.Width( ) / 2, box.bottom - quarterY );
         pDC->MoveTo( box.left + quarterX, box.top + box.Height( ) / 2 );
         pDC->LineTo( box.right - quarterX, box.top + box.Height( ) / 2 );
         pDC->SelectObject( pOldPen );
         break;

      case ePlusDrop:
         // [+]-
         //  |
         pOldPen = pDC->SelectObject( &penDark );
         pDC->MoveTo( box.left + quarterX, box.top + quarterY );
         pDC->LineTo( box.right - quarterX, box.top + quarterY );
         pDC->LineTo( box.right - quarterX, box.bottom - quarterY );
         pDC->LineTo( box.left + quarterX, box.bottom - quarterY );
         pDC->LineTo( box.left + quarterX, box.top + quarterY );
         if ( bHasLines )
         {
            pDC->MoveTo( box.right - quarterX, box.top + box.Height( ) / 2 );
            pDC->LineTo( box.right, box.top + box.Height( ) / 2 );
            pDC->MoveTo( box.left + box.Width( ) / 2, box.top + quarterY );
            pDC->LineTo( box.left + box.Width( ) / 2, box.top );
         }

         pDC->SelectObject( &penBlack );
         pDC->MoveTo( box.left + box.Width( ) / 2, box.top + quarterY );
         pDC->LineTo( box.left + box.Width( ) / 2, box.bottom - quarterY );
         pDC->MoveTo( box.left + quarterX, box.top + box.Height( ) / 2 );
         pDC->LineTo( box.right - quarterX, box.top + box.Height( ) / 2 );
         pDC->SelectObject( pOldPen );
         break;

      case eMinus:
         // [-]-
         // []
         pOldPen = pDC->SelectObject( &penDark );
         pDC->MoveTo( box.left + quarterX, box.top + quarterY );
         pDC->LineTo( box.right - quarterX, box.top + quarterY );
         pDC->LineTo( box.right - quarterX, box.bottom - quarterY );
         pDC->LineTo( box.left + quarterX, box.bottom - quarterY );
         pDC->LineTo( box.left + quarterX, box.top + quarterY );
         if ( bHasLines )
         {
            // -
            pDC->MoveTo( box.right - quarterX, box.top + box.Height( ) / 2 );
            pDC->LineTo( box.right, box.top + box.Height( ) / 2 );
            // | top
            pDC->MoveTo( box.left + box.Width( ) / 2, box.top + quarterY );
            pDC->LineTo( box.left + box.Width( ) / 2, box.top );
         }

         // - in box
         pDC->SelectObject( &penBlack );
         pDC->MoveTo( box.left + quarterX, box.top + box.Height( ) / 2 );
         pDC->LineTo( box.right - quarterX, box.top + box.Height( ) / 2 );
         pDC->SelectObject( pOldPen );
         break;

      case eMinusDrop:
         // [-]-
         //  |
         // []
         pOldPen = pDC->SelectObject( &penDark );
         pDC->MoveTo( box.left + quarterX, box.top + quarterY );
         pDC->LineTo( box.right - quarterX, box.top + quarterY );
         pDC->LineTo( box.right - quarterX, box.bottom - quarterY );
         pDC->LineTo( box.left + quarterX, box.bottom - quarterY );
         pDC->LineTo( box.left + quarterX, box.top + quarterY );
         if ( bHasLines )
         {
            // -
            pDC->MoveTo( box.right, box.top + box.Height( ) / 2 );
            pDC->LineTo( box.right - quarterX, box.top + box.Height( ) / 2 );
            // | top
            pDC->MoveTo( box.left + box.Width( ) / 2, box.top );
            pDC->LineTo( box.left + box.Width( ) / 2, box.top + quarterY );
            // | bottom
            pDC->MoveTo( box.left + box.Width( ) / 2, box.bottom );
            pDC->LineTo( box.left + box.Width( ) / 2, box.bottom - quarterY );
         }

         // - in box
         pDC->SelectObject( &penBlack );
         pDC->MoveTo( box.left + quarterX, box.top + box.Height( ) / 2 );
         pDC->LineTo( box.right - quarterX, box.top + box.Height( ) / 2 );
         pDC->SelectObject( pOldPen );
         break;

      case eLink:
         // |
         // +-
         pOldPen = pDC->SelectObject( &penDark );
         pDC->MoveTo( box.left + box.Width( ) / 2, box.top );
         pDC->LineTo( box.left + box.Width( ) / 2, box.top + box.Height( ) / 2 );
         pDC->LineTo( box.right, box.top + box.Height( ) / 2 );
         pDC->SelectObject( pOldPen );
         break;

      case eLinkDrop:
         // |
         // +-
         // |
         pOldPen = pDC->SelectObject( &penDark );
         pDC->MoveTo( box.left + box.Width( ) / 2, box.top );
         pDC->LineTo( box.left + box.Width( ) / 2, box.bottom );
         pDC->MoveTo( box.left + box.Width( ) / 2, box.top + box.Height( ) / 2 );
         pDC->LineTo( box.right, box.top + box.Height( ) / 2 );
         pDC->SelectObject( pOldPen );
         break;

      case eDrop:
         // |
         pOldPen = pDC->SelectObject( &penDark );
         pDC->MoveTo( box.left + box.Width( ) / 2, box.top );
         pDC->LineTo( box.left + box.Width( ) / 2, box.bottom );
         pDC->SelectObject( pOldPen );
         break;
   }
}

void
ZMSTree::DrawTreeItem( ZPrintout *pZPrintout, HTREEITEM hPrintItem,
                       CDC *pDC, CRect rect, CWnd *pWnd )
{
   // We may/will need to offset the text to get the correct position.
   HTREEITEM  hRootItem = GetRootItem( );
   HTREEITEM  hIndent = hPrintItem;
   zSHORT     nIndent = 0;                   // number of indent levels
   TVITEM     itemInfo;
   CImageList *pIL = GetImageList( TVSIL_NORMAL );
   zBOOL      bLinesAtRoot = ((::GetWindowLong( m_hWnd, GWL_STYLE ) & TVS_LINESATROOT) != 0);

   if ( (pZPrintout && (pZPrintout->m_bPrintToCSV ||
        pZPrintout->m_bPrintToHTML || pZPrintout->m_bPrintToPDF)) || pDC == 0 )
   {
      pIL = 0;
   }

   if ( bLinesAtRoot )
   {
      // There are lines at root, need to move everything over to make room for them.
      nIndent++;
   }

   // Count the indent levels for this item.
   HTREEITEM hParentItem = GetParentItem( hPrintItem );
   while ( hIndent != 0 && hParentItem != 0 )
   {
      hIndent = GetParentItem( hIndent );
      hParentItem = GetParentItem( hParentItem );
      nIndent++;
   }

   if ( pIL )
      nIndent++;  // make room for any icon next to the item

   // Work out the position of the text.
   rect.left += nIndent * rect.Height( );        // offset our rectangle to avoid lines/buttons
   rect.left += LEFT_MARGIN;

   if ( ::GetWindowLong( m_hWnd, GWL_STYLE ) & (TVS_HASBUTTONS | TVS_HASLINES) )
   {
      // The item needs to have lines or +/- buttons drawn for it.
      // Correct position immediately to left of icon.
      CRect box( rect.left - rect.Height( ) * 2, rect.top, rect.left - rect.Height( ) - 1, rect.bottom );
      hIndent = hPrintItem;

      // Draw items until we get to the null item.
      while ( hIndent != 0 )
      {
         hParentItem = GetParentItem( hIndent );
         if ( hParentItem == 0 && bLinesAtRoot == FALSE )
            break;  // done drawing this item

         eDRAW_TYPES eStyle = (eDRAW_TYPES) GetIndentLevelStyle( hPrintItem, hIndent );
         DrawTreeStyle( pZPrintout, pDC, box, eStyle );
         box -= CPoint( rect.Height( ), 0 );

         // Get the style for the item at this level.
         hIndent = GetParentItem( hIndent );
      }
   }

   CString csText = GetItemText( hPrintItem );
   CRect rectText( rect );

   rectText.left += m_sizeChar.cx;
   pZPrintout->RptDrawText( pDC, csText, rectText,
                            DT_END_ELLIPSIS | DT_EXPANDTABS | DT_SINGLELINE | DT_VCENTER );
   if ( pIL )
   {
      // Draw the image next to the item.
      itemInfo.mask = TVIF_IMAGE;
      itemInfo.hItem = hPrintItem;
      GetItem( &itemInfo );
      if ( itemInfo.iImage >= 0 )
      {
         HANDLE hDib;
         hDib = ImageToDIB( pIL, itemInfo.iImage, pWnd );
         BITMAPINFOHEADER  *pBMI;
         pBMI = (BITMAPINFOHEADER *) GlobalLock( hDib );
         int nColors = 0;
         if ( pBMI->biBitCount <= 8 )
         {
            nColors = (1 << pBMI->biBitCount);
         }

         // Print the correct image.
         ::StretchDIBits( pDC->m_hDC,
                          rect.left - rect.Height( ),
                          rect.top,
                          rect.Height( ),
                          rect.Height( ),
                          0,
                          0,
                          pBMI->biWidth,
                          pBMI->biHeight,
                          (LPBYTE) pBMI + (pBMI->biSize + (nColors * sizeof( RGBQUAD ))),
                          (BITMAPINFO *) pBMI,
                          DIB_RGB_COLORS, SRCCOPY );

         // Free resources.
         GlobalUnlock( hDib );
         GlobalFree( hDib );
      }
   }
}

HANDLE
ZMSTree::ImageToDIB( CImageList *pImageList, int iImageNumber, CWnd *pWnd )
{
   // Local Variables.
   CBitmap    bitmap;
   CWindowDC  dc( pWnd );

   CDC        memDC;
   CRect      rect;
   CPalette   pal;
   IMAGEINFO  imageInfo;

   if ( !pImageList->GetImageInfo( iImageNumber, &imageInfo ) )
   {
      // Get of the Image Info failed.
      return( 0 );
   }

   // Create compatible stuff and select Bitmap.
   if ( !memDC.CreateCompatibleDC( &dc ) )
   {
      // Create failed.
      return( 0 );
   }

   if ( !bitmap.CreateCompatibleBitmap( &dc,
                                        imageInfo.rcImage.bottom-imageInfo.rcImage.top,
                                        imageInfo.rcImage.right-imageInfo.rcImage.left ) )
   {
      // Create failed.
      memDC.DeleteDC( );
      return( 0 );
   }

   CBitmap *pOldBitmap = memDC.SelectObject( &bitmap );
   if ( pOldBitmap == 0 )
   {
      // Select failed.
      memDC.DeleteDC( );
      return( 0 );
   }

   // Local Variables for Draw.
   CPoint point( 0, 0 );
   UINT nStyle = ILD_NORMAL;

   // Draw Image to the compatible DC.
   if ( !pImageList->Draw( &memDC, iImageNumber, point, nStyle ) )
   {
      // Drawing of the Image failed.
      memDC.SelectObject( pOldBitmap );
      VERIFY( bitmap.DeleteObject( ) );
      memDC.DeleteDC( );
      return( 0 );
   }

   // Create logical palette if device support a palette.
   if ( dc.GetDeviceCaps( RASTERCAPS ) & RC_PALETTE )
   {
      UINT       nSize   = sizeof( LOGPALETTE ) + (sizeof( PALETTEENTRY ) * 256);
      LOGPALETTE *pLP    = (LOGPALETTE *) new BYTE[ nSize ];
      pLP->palVersion    = 0x300;
      pLP->palNumEntries = (unsigned short) GetSystemPaletteEntries( dc, 0, 255, pLP->palPalEntry );

      // Create the palette.
      pal.CreatePalette( pLP );

      // Free memory.
      delete [] pLP;
   }

   memDC.SelectObject( pOldBitmap );
   memDC.DeleteDC( );

   // Convert the bitmap to a DIB.
   HANDLE h = DDBToDIB( bitmap, BI_RGB, &pal );
   VERIFY( bitmap.DeleteObject( ) );
   return( h );
}

// DDBToDIB    - Creates a DIB from a DDB
// bitmap      - Device dependent bitmap
// dwCompression - Type of compression - see BITMAPINFOHEADER
// pPal        - Logical palette
HANDLE
ZMSTree::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette *pPal )
{
   BITMAP bmp;
   BITMAPINFOHEADER bi;
   LPBITMAPINFOHEADER lpbi;
   DWORD dwLth;
   HANDLE hDIB;
   HANDLE hReAlloc;
   HDC hDC;
   HPALETTE hPal;

   ASSERT( bitmap.GetSafeHandle( ) );

   // The function has no arg for bitfields.
   if ( dwCompression == BI_BITFIELDS )
      return( 0 );

   // If a palette has not been supplied use default palette.
   hPal = (HPALETTE) pPal->GetSafeHandle( );
   if ( hPal == 0 )
      hPal = (HPALETTE) GetStockObject( DEFAULT_PALETTE );

   // Get bitmap information.
   bitmap.GetObject( sizeof( bmp ), (LPSTR) &bmp );

   // Initialize the bitmapinfoheader.
   bi.biSize          = sizeof( BITMAPINFOHEADER );
   bi.biWidth         = bmp.bmWidth;
   bi.biHeight        = bmp.bmHeight;
   bi.biPlanes        = 1;
   bi.biBitCount      = (unsigned short) (bmp.bmPlanes * bmp.bmBitsPixel);
   bi.biCompression   = dwCompression;
   bi.biSizeImage     = 0;
   bi.biXPelsPerMeter = 0;
   bi.biYPelsPerMeter = 0;
   bi.biClrUsed       = 0;
   bi.biClrImportant  = 0;

// // Compute the size of the  infoheader and the color table.
// int nColors = (1 << bi.biBitCount);
// if ( nColors > 256 )
//    nColors = 0;

   // Compute the size of the  infoheader and the color table.
   int nColors = 0;
   if ( bi.biBitCount <= 8 )
      nColors = (1 << bi.biBitCount);
   else
      nColors = 0;

   dwLth = bi.biSize + nColors * sizeof( RGBQUAD );

   // We need a device context to get the DIB from.
   hDC = ::GetDC( 0 );
   hPal = SelectPalette( hDC, hPal, FALSE );  // hPal is now previous palette
   RealizePalette( hDC );

   // Allocate enough memory to hold bitmapinfoheader and color table.
   hDIB = GlobalAlloc( GMEM_FIXED, dwLth );

   if ( hDIB == 0 )
   {
      // Reselect the original palette.
      if ( hPal )
         SelectPalette( hDC, hPal, FALSE );

      ::ReleaseDC( 0, hDC );
      return( 0 );
   }

   lpbi = (LPBITMAPINFOHEADER) GlobalLock( hDIB );

   *lpbi = bi;

   // Call GetDIBits with a zero lpBits param, so the device driver will
   // calculate the biSizeImage field.
   GetDIBits( hDC, (HBITMAP) bitmap.GetSafeHandle( ), 0L, (DWORD) bi.biHeight,
              (LPBYTE) 0, (LPBITMAPINFO) lpbi, (DWORD) DIB_RGB_COLORS );

   bi = *lpbi;

   // If the driver did not fill in the biSizeImage field, then compute it.
   // Each scan line of the image is aligned on a DWORD (32-bit) boundary.
   if ( bi.biSizeImage == 0 )
   {
      bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * bi.biHeight;

      // If a compression scheme is used the result may in fact be larger.
      // Increase the size to account for this.
      if ( dwCompression != BI_RGB )
         bi.biSizeImage = (bi.biSizeImage * 3) / 2;
   }

   // Realloc the buffer so that it can hold all the bits.
   dwLth += bi.biSizeImage;
   if ( (hReAlloc = GlobalReAlloc( hDIB, dwLth, GMEM_MOVEABLE )) != 0 )
      hDIB = hReAlloc;
   else
   {
      GlobalFree( hDIB );

      // Reselect the original palette.
      if ( hPal )
         SelectPalette( hDC, hPal, FALSE );

      ::ReleaseDC( 0, hDC );
      return( 0 );
   }

   // Get the bitmap bits.
   lpbi = (LPBITMAPINFOHEADER) hDIB;

   // FINALLY get the DIB.
   BOOL bGotBits = GetDIBits( hDC, (HBITMAP) bitmap.GetSafeHandle( ),
                              0L,                        // start scan line
                              (DWORD) bi.biHeight,       // # of scan lines
                              (LPBYTE) lpbi +            // address for bitmap bits
                                (bi.biSize + nColors * sizeof( RGBQUAD )),
                              (LPBITMAPINFO) lpbi,       // address of bitmapinfo
                              (DWORD) DIB_RGB_COLORS );  // use RGB for color table

   if ( bGotBits == FALSE )
   {
      GlobalFree( hDIB );

      // Reselect the original palette.
      if ( hPal )
         SelectPalette( hDC, hPal, FALSE );

      ::ReleaseDC( 0, hDC );
      return( 0 );
   }

   // Reselect the original palette.
   if ( hPal )
      SelectPalette( hDC, hPal, FALSE );

   ::ReleaseDC( 0, hDC );
   return( hDIB );
}

void
ZMSTree::ExpandAll( )
{
   // Expand all items in a tree control.
   HTREEITEM hItem;

   for ( hItem = GetRootItem( );
         hItem;
         hItem = GetNextTreeItem( hItem ) )
   {
      if ( ItemHasChildren( hItem ) )
         Expand( hItem, TVE_EXPAND );
   }
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//./ ADD NAME=OL_ResetNodeList
// Source Module=zdctlmst.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION:  OL_ResetNodeList
//
//  PURPOSE:    This operation resets the outliner.
//
//  PARAMETERS: vSubtask    - The subtask view for the window containing
//                            the control for which to get the dispatch
//                            interface.
//
//  RETURNS:   >= 0  ok
//               -1  Error
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OL_ResetNodeList( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineS( "OL_ResetNodeList: ", cpcCtrlTag );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL ) //???
      {
         TraceLineS( "drvr - Invalid control type for OL_ResetNodeList ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         pOL->DeleteAllItems( );
         mDeleteInit( pOL->m_pRootEntry );
         pOL->m_ulMapActFlag2 &= ~zMAPACT_MAPPED_FROM_OI;
         pOL->m_ulKeyLast = 0;
         pOL->m_szLastAccEntity[ 0 ] = 0;
         return( 0 );
      }
#endif
   }

   return( -1 );
}

//./ ADD NAME = OL_GetSelectedBitmap
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetDefaultBitmap
//
//
//  PURPOSE:    This operation gets the Selected Bitmap for an Entity.
//
//  PARAMETERS: vSubtask          - The subtask view for the window containing
//                                  the tree control.
//              cpcCtrlTag        - The unique name of the control.
//              cpcEntityName     - mapping Entity Name (0 = current Entity)
//              pchBitmapFileName - Return Bitmap File Name (0 = Zeidon Default Bitmap)
//              ulMaxReturnBitmapNameLength - max. Return Bitmap File Name Length
//
//  RETURNS:   -1 - Error locating control
//              0 - Bitmap is get
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetSelectedBitmap( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zCPCHAR cpcEntityName,
                      zPCHAR  pchBitmapFileName,
                      zULONG  ulMaxReturnBitmapNameLength )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetSelectedBitmap", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetSelectedBitmap ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->GetSelectedBitmap( cpcEntityName, pchBitmapFileName,
                                             ulMaxReturnBitmapNameLength );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_GetSelectedBitmap

//./ ADD NAME = OL_GetDefaultBitmap
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetDefaultBitmap
//
//
//  PURPOSE:    This operation get the Default Bitmap for a Entity
//
//  PARAMETERS: vSubtask          - The subtask view for the window containing
//                                  the tree control.
//              cpcCtrlTag        - The unique name of the control.
//              cpcEntityName     - mapping Entity Name (0 = current Entity)
//              cpcBitmapFileName - Return Bitmap File Name (0 = Zeidon Default Bitmap)
//              ulMaxReturnBitmapNameLength - max. Return Bitmap File Name Length
//
//  RETURNS:   -1 - Error locating control
//              0 - Bitmap is get
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetDefaultBitmap( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zCPCHAR cpcEntityName,
                     zPCHAR  pchBitmapFileName,
                     zULONG  ulMaxReturnBitmapNameLength )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetDefaultBitmap", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetDefaultBitmap ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->GetDefaultBitmap( cpcEntityName, pchBitmapFileName,
                                            ulMaxReturnBitmapNameLength );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_GetDefaultBitmap

//./ ADD NAME = OL_SetDefaultBitmap
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetDefaultBitmap
//
//
//  PURPOSE:    This operation set the Default Bitmap for a Entity
//
//  PARAMETERS: vSubtask          - The subtask view for the window containing
//                                  the tree control.
//              cpcCtrlTag        - The unique name of the control.
//              cpcEntityName     - mapping Entity Name (0 = current Entity)
//              cpcBitmapFileName - Bitmap File Name (0 = Zeidon Default Bitmap)
//
//  RETURNS:   -1 - Error locating control
//              0 - Bitmap is set
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetDefaultBitmap( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zCPCHAR cpcEntityName,
                     zCPCHAR cpcBitmapFileName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLine( "OL_SetDefaultBitmap Subtask: 0x%08x   Ctrl: %s   Entity: %s   BitmapFile: %s",
              vSubtask, cpcCtrlTag, cpcEntityName, cpcBitmapFileName );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetDefaultBitmap ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
        // mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->SetDefaultBitmap( cpcEntityName, cpcBitmapFileName );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_SetDefaultBitmap

//./ ADD NAME = OL_SetSelectedBitmap
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetSelectedBitmap
//
//
//  PURPOSE:    This operation set the Selected Bitmap for a Entity
//
//  PARAMETERS: vSubtask          - The subtask view for the window containing
//                                  the tree control.
//              cpcCtrlTag        - The unique name of the control.
//              cpcEntityName     - mapping Entity Name (0 = current Entity)
//              cpcBitmapFileName - Bitmap File Name (0 = Zeidon Default Bitmap)
//
//  RETURNS:   -1 - Error locating control
//              0 - Bitmap is set
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetSelectedBitmap( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zCPCHAR cpcEntityName,
                      zCPCHAR cpcBitmapFileName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLine( "OL_SetSelectedBitmap Subtask: 0x%08x   Ctrl: %s   Entity: %s   BitmapFile: %s",
              vSubtask, cpcCtrlTag, cpcEntityName, cpcBitmapFileName );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetSelectedBitmap ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
        // mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->SetSelectedBitmap( cpcEntityName, cpcBitmapFileName );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_SetSelectedBitmap

//./ ADD NAME = OL_SelectItem
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SelectItem
//
//
//  PURPOSE:    This operation selects or deselects the specified tree item.
//              It may close the tree
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - mapping Entity Name
//              ulEntityKey    - Entity Key to select
//              ulFlag         - 0 deselect specified item
//                             - 1 select specified item
//                             - 2 close tree prior to select
//                             - 4 sort ascending within parent item
//                             - 8 sort descending within parent item
//
//  RETURNS:   0 - selection successful
//            -1 - Error locating control
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SelectItem( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zCPCHAR cpcEntityName,
               zULONG  ulEntityKey,
               zULONG  ulFlag )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SelectItem", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SelectItem ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->SelectEntityItem( cpcEntityName,
                                            ulEntityKey, ulFlag );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_SelectItem

//./ ADD NAME = OL_FindItemByAttribute
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_FindItemByAttribute
//
//
//  PURPOSE:    This operation selects any tree item with the specified
//              attribute(s) value matching the find string.
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - mapping Entity Name (default to map EName)
//              cpcAttribName  - mapping Attribute Name (may be a list)
//              cpcFindString  - string to find
//              ulEntityKey    - Entity Key from which to select
//              ulFlag         - 0 find first
//                             - 1 find next
//
//  RETURNS:   0 - nothing selected found
//            -1 - Error locating control
//           otw - Entity Key of located item
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_FindItemByAttribute( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zCPCHAR cpcEntityName,
                        zCPCHAR cpcAttribName,
                        zCPCHAR cpcFindString,
                        zULONG  ulEntityKey,
                        zULONG  ulFlag )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_FindItemByAttribute", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_FindItemByAttribute ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->SelectItemByAttribute( cpcEntityName, cpcAttribName,
                                                 cpcFindString, ulEntityKey, ulFlag );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_SelectItem

//./ ADD NAME = OL_GetExpandState
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetExpandState
//
//
//  PURPOSE:    This operation gets the expanded state of the current
//              tree item for the given entity.
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - mapping Entity Name
//
//  RETURNS:   -1 - Error locating control
//              0 - Collapsed
//              1 - Expanded
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetExpandState( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zCPCHAR cpcEntityName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetExpandState", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetExpandState ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->GetExpandState( cpcEntityName );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_GetExpandState

//./ ADD NAME = OL_ExpandEntity
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_ExpandEntity
//
//
//  PURPOSE:    This operation sets the expanded state of the current
//              tree item for the given entity.
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - mapping Entity Name
//              lValue         - zEXPAND        expand current Entity Instance
//                               zEXPANDALL     expand all Entity Instances
//                               zCOLLAPSE      collapse current Entity Instance
//                               zCOLLAPSEALL   collapse all Entity Instances
//
//  RETURNS:   -1 - Error locating control
//             Otherwise old expand state
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_ExpandEntity( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zCPCHAR cpcEntityName,
                 zULONG  ulValue )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_ExpandEntity", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_ExpandEntity ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->ExpandEntity( cpcEntityName, ulValue );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_ExpandEntity

//./ ADD NAME = OL_EditLabel
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_EditLabel
//
//
//  PURPOSE:    This operation allows edit of the current tree item
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              ulTextLength   - Text Length (0 ==> Attribute Length)
//
//  RETURNS:   -1 - Error locating control
//             Otherwise Text Length
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_EditLabel( zVIEW    vSubtask,
              zCPCHAR  cpcCtrlTag,
              zULONG   ulTextLength )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_EditLabel", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_EditLabel ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->EditItem( ulTextLength );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_EditLabel

//./ ADD NAME = OL_SetCtrlState
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetCtrlState
//
//
//  PURPOSE:    This operation set the Properties tree Control
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              lStatusType    - zCONTROL_STATUS_ENABLED            (1)
//                               zCONTROL_STATUS_VISIBLE            (3)
//                               zCONTROL_STATUS_BACKGROUND_COLOR   (4)
//                               zCONTROL_STATUS_DISABLE_READONLY   (15)
//                               zCONTROL_STATUS_HASBUTTONS         (22)
//                               zCONTROL_STATUS_HASLINES           (23)
//                               zCONTROL_STATUS_LINESATROOT        (24)
//                               zCONTROL_STATUS_DISABLEDRAGDROP    (25)
//                               zCONTROL_STATUS_NOSHOW_ENTITY      (26)
//                               zCONTROL_STATUS_MULTIPLEROOT       (27)
//                               zCONTROL_STATUS_MULTISELECT        (28)
//                               zCONTROL_STATUS_SINGLEEXPAND       (29)
//                               zCONTROL_STATUS_EXPAND             (30)
//                               zCONTROL_STATUS_EXPANDALL          (31)
//              lValue         - TRUE = set this Property  FALSE = remove it
//
//  RETURNS:   -1 - Error locating control
//             Otherwise old value for this Property
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetCtrlState( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lStatusType,
                 zLONG   lValue )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SetCtrlState", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetCtrlState ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->SetZCtrlState( lStatusType, lValue );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_SetCtrlState

//./ ADD NAME = OL_GetCtrlState
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetCtrlState
//
//
//  PURPOSE:    This operation get the Properties tree Control
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              lStatusType    - zCONTROL_STATUS_ENABLED            (1)
//                               zCONTROL_STATUS_VISIBLE            (3)
//                               zCONTROL_STATUS_BACKGROUND_COLOR   (4)
//                               zCONTROL_STATUS_DISABLE_READONLY   (15)
//                               zCONTROL_STATUS_HASBUTTONS         (22)
//                               zCONTROL_STATUS_HASLINES           (23)
//                               zCONTROL_STATUS_LINESATROOT        (24)
//                               zCONTROL_STATUS_DISABLEDRAGDROP    (25)
//                               zCONTROL_STATUS_NOSHOW_ENTITY      (26)
//                               zCONTROL_STATUS_MULTIPLEROOT       (27)
//                               zCONTROL_STATUS_MULTISELECT        (28)
//                               zCONTROL_STATUS_SINGLEEXPAND       (29)
//                               zCONTROL_STATUS_EXPAND             (30)
//                               zCONTROL_STATUS_EXPANDALL          (31)
//              lValue         - TRUE = set this Property  FALSE = remove it
//
//  RETURNS:   -1 - Error locating control
//             Otherwise get value for this Property
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetCtrlState( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lStatusType )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetCtrlState", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetCtrlState ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->GetZCtrlState( lStatusType );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_GetCtrlState

//./ ADD NAME = OL_SetTxtFontForEntity
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetTxtFontForEntity
//
//
//  PURPOSE:    This operation set the Text Font for a tree Entity
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - Entity Name
//                               if 0 set Font for current selected Entity
//              fntTextFont    - Text Font to be set.
//
//  RETURNS:   -1 - Error locating control
//             Otherwise old Color
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetTxtFontForEntity( zVIEW    vSubtask,
                        zCPCHAR  cpcCtrlTag,
                        zCPCHAR  cpcEntityName,
                        LOGFONT  fntTextFont )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SetTxtFontForEntity", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetTxtFontForEntity ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->SetTxtFontForEntity( cpcEntityName, fntTextFont );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_SetTxtFontForEntity

//./ ADD NAME = OL_GetTextFontForEntity
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetTextFontForEntity
//
//
//  PURPOSE:    This operation get the Text Font for a tree entity
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - Entity Name
//                               if 0 set Font for current selected Entity
//              plSize         - Return Font size
//              plBold         - Return Bold or not (TRUE = BOLD  FALSE = not bold)
//              plItalic       - Return Italic or not (TRUE = Italic  FALSE = not italic)
//              plUnderline    - Return Underline or not (TRUE = Underline  FALSE = not underline)
//              plStrikeout    - Return Strikeout or not (TRUE = Strikeout  FALSE = not strikeout)
//              plTextColor    - Return RGB Text Color (0 = default)
//              plEscapement   - Return Escapement (angle in tenths of a degree from the x-axis)
//              pchFaceName     - Return FaceName (font face name 0 = default)
//
//  RETURNS:   -1 - Error locating control
//             Otherwise 0
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetTextFontForEntity( zVIEW    vSubtask,
                         zCPCHAR  cpcCtrlTag,
                         zCPCHAR  cpcEntityName,
                         zPLONG   plSize,
                         zPLONG   plBold,
                         zPLONG   plItalic,
                         zPLONG   plUnderline,
                         zPLONG   plStrikeout,
                         zPLONG   plTextColor,
                         zPLONG   plEscapement,
                         zPCHAR   pchFaceName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetTextFontForEntity", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetTextFontForEntity ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->GetTextFontForEntity( cpcEntityName, plSize, plBold,
                                                plItalic, plUnderline, plStrikeout,
                                                plTextColor, plEscapement, pchFaceName );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_GetTextFontForEntity

//./ ADD NAME = OL_SetTextFontForEntity
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetTextFontForEntity
//
//  PURPOSE:    This operation set the Text Font for a tree entity
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - Entity Name
//                               if 0 set Font for current selected Entity
//              lSize          - Font size
//              lBold          - Bold or not (TRUE = BOLD  FALSE = not bold)
//              lItalic        - Italic or not (TRUE = Italic  FALSE = not italic)
//              lUnderline     - Underline or not (TRUE = Underline  FALSE = not underline)
//              lStrikeout     - Strikeout or not (TRUE = Strikeout  FALSE = not strikeout)
//              lTextColor     - RGB Text Color (0 = default)
//              lEscapement    - Escapement (angle in tenths of a degree from the x-axis)
//              pchFaceName    - FaceName (font face name 0 = default)
//
//  RETURNS:   -1 - Error locating control
//             Otherwise old Color
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetTextFontForEntity( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zCPCHAR cpcEntityName,
                         zLONG   lSize,
                         zLONG   lBold,
                         zLONG   lItalic,
                         zLONG   lUnderline,
                         zLONG   lStrikeout,
                         zLONG   lTextColor,
                         zLONG   lEscapement,
                         zPCHAR  pchFaceName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SetTextFontForEntity", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetTextFontForEntity ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG nRC = pOL->SetTextFontForEntity( cpcEntityName, lSize, lBold,
                                                lItalic, lUnderline, lStrikeout,
                                                lTextColor, lEscapement, pchFaceName );
         return( nRC );
      }
#endif
   }

   return( -1 );
} // OL_SetTextFontForEntity

//./ ADD NAME = OL_GetTextColorForEntity
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetTextColorForEntity
//
//
//  PURPOSE:    This operation get the Text Color for a tree Entity
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - Entity Name
//                               if 0 set Color for current selected Entity
//
//  RETURNS:   -1 - Error locating control
//             Otherwise Text Color
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetTextColorForEntity( zVIEW    vSubtask,
                          zCPCHAR  cpcCtrlTag,
                          zCPCHAR  cpcEntityName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetTextColorForEntity", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetTextColorForEntity ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG lRC = pOL->GetTextColorForEntity( cpcEntityName );
         return( lRC );
      }
#endif
   }

   return( -1 );
} // GetTextColorForEntity

//./ ADD NAME = OL_SelectItemAtPosForEntity
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SelectItemAtPosForEntity
//
//
//  PURPOSE:    This operation selects a tree item for a specified
//              entity at the current cursor position.
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - Entity for which to select item (applies to
//                               all entities if blank).
//              lFlags         - 0 - first remove all select states
//                               1 - do not remove all select states
//                               2 - do not map
//                               4 - reset hilite based on select states
//                               8 - turn off hilite for specified item
//                              16 - cause current item to be re-selected
//                              32 - refresh control and select item associated
//                                   with entity's current cursor pos.
//                              64 - close all nodes except the specified item
//
//  RETURNS:   -1 - Error locating control
//              0 - OK
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OL_SelectItemAtPosForEntity( zVIEW    vSubtask,
                             zCPCHAR  cpcCtrlTag,
                             zCPCHAR  cpcEntityName,
                             zLONG    lFlags )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SelectItemAtPosForEntity", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SelectItemAtPosForEntity ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zSHORT nRC;

         if ( pzma->m_ulMapActFlags & zTREE_RECURSIVESELECTPOS )
            return( -1 );

         pzma->m_ulMapActFlags |= zTREE_RECURSIVESELECTPOS;
         nRC = pOL->SelectItemAtPosForEntity( cpcEntityName, lFlags );
         pzma->m_ulMapActFlags &= ~zTREE_RECURSIVESELECTPOS;
         return( nRC );
      }
   }

   return( -1 );
} // OL_SelectItemAtPosForEntity

//./ ADD NAME = OL_SetTextForCurrentItem
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetTextForCurrentItem
//
//
//  PURPOSE:    This operation sets the Text for the current tree Item.
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcItemText    - Search Item Text
//
//  RETURNS:   -1 - Error locating control
//              0 - OK
//              1 - No current item
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetTextForCurrentItem( zVIEW    vSubtask,
                          zCPCHAR  cpcCtrlTag,
                          zCPCHAR  cpcItemText )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SetTextForItem", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetTextForCurrentItem ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
      // zCHAR szMsg[ 256 ];
      // sprintf_s( szMsg, zsizeof( szMsg ), "OL_SetTextForCurrentItem Tag: %s %s", cpcCtrlTag, cpcItemText );
      // pOL->ListAllItems( szMsg );
         zLONG lRC = pOL->SetTextForCurrentItem( cpcItemText );
         return( lRC );
      }
#endif
   }

   return( -1 );
} // OL_SetTextForCurrentItem

//./ ADD NAME = OL_ResetAllTextColorsForItemText
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_ResetAllTextColorsForItemText
//
//
//  PURPOSE:    This operation remove the Text Color for a all tree Items
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//
//  RETURNS:   -1 - Error locating control
//              0 - Otherwise
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_ResetAllTextColorsForItemText( zVIEW    vSubtask,
                                  zCPCHAR  cpcCtrlTag )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_ResetAllTextColorsForItemText", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_ResetAllTextColorsForItemText ", cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         pOL->RemoveAllTextColorsForItemText( );
         return( 0 );
      }
#endif
   }

   return( -1 );
} // OL_ResetAllTextColorsForItemText

//./ ADD NAME = OL_SetTextColorForItemText
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetTextColorForItemText
//
//
//  PURPOSE:    This operation set the Text Color for a tree Item
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcItemText    - Search Item Text
//              lColor         - Text Color to be set.
//
//  RETURNS:   -1 - Error locating control
//             Otherwise old Color
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetTextColorForItemText( zVIEW    vSubtask,
                            zCPCHAR  cpcCtrlTag,
                            zCPCHAR  cpcItemText,
                            COLORREF clrTextColor,
                            zBOOL    bEnsureVisible )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SetTextColorForItemText", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetTextColorForItemText ", cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG lRC = pOL->SetTextItemColorText( cpcItemText, clrTextColor, bEnsureVisible );
         return( lRC );
      }
#endif
   }

   return( -1 );
} // OL_SetTextColorForItemText

//./ ADD NAME = OL_SetTextColorForEntity
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetTextColorForEntity
//
//
//  PURPOSE:    This operation set the Text Color for a tree Entity
//
//  PARAMETERS: vSubtask       - The subtask view for the window containing
//                               the tree control.
//              cpcCtrlTag     - The unique name of the control.
//              cpcEntityName  - Entity Name
//                               if 0 set Color for current selected Entity
//              lColor         - Text Color to be set.
//
//  RETURNS:   -1 - Error locating control
//             Otherwise old Color
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetTextColorForEntity( zVIEW    vSubtask,
                          zCPCHAR  cpcCtrlTag,
                          zCPCHAR  cpcEntityName,
                          COLORREF clrTextColor )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SetTextColorForEntity", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetTextColorForEntity ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         zLONG lRC = pOL->SetTextColorForEntity( cpcEntityName, clrTextColor );
         return( lRC );
      }
#endif
   }

   return( -1 );
} // SetTextColorForEntity

//./ ADD NAME = OL_GetBackgroundColor
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetBackgroundColor
//
//
//  PURPOSE:    This operation get the Background Color for a tree
//
//  PARAMETERS: vSubtask    - The subtask view for the window containing
//                            the tree control.
//              cpcCtrlTag  - The unique name of the control.
//
//  RETURNS:   -1 - Error locating control
//             Otherwise Background Color
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetBackgroundColor( zVIEW    vSubtask,
                       zCPCHAR  cpcCtrlTag )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetBackgroundColor", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetBackgroundColor ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         return( pOL->GetBackgroundColor( ) );
      }
#endif
   }

   return( -1 );
} // OL_SetBackgroundColor

//./ ADD NAME = OL_SetBackgroundColor
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_SetBackgroundColor
//
//
//  PURPOSE:    This operation set the Background Color for a tree
//
//  PARAMETERS: vSubtask    - The subtask view for the window containing
//                            the tree control.
//              cpcCtrlTag  - The unique name of the control.
//              lColor      - Background Color to be set.
//
//  RETURNS:   -1 - Error locating control
//             Otherwise old Color
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_SetBackgroundColor( zVIEW    vSubtask,
                       zCPCHAR  cpcCtrlTag,
                       zLONG    lColor )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_SetBackgroundColor", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_SetBackgroundColor ", cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         return( pOL->SetBackgroundColor( lColor ) );
      }
#endif
   }

   return( -1 );
} // OL_SetBackgroundColor

//./ ADD NAME=OL_GetCollapsingEntityName
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetCollapsingEntityName
//
//  PURPOSE:    This operation gets the entity name corresponding to the
//              collapsing tree item
//
//  PARAMETERS: vSubtask           - The subtask view for the window containing
//                                   the tree control.
//              cpcCtrlTag         - The unique name of the control.
//              lpReturnEntityName - The entity name returned to the user
//
//  RETURNS:    0 - Entity name returned
//             -1 - Error locating control
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetCollapsingEntityName( zVIEW   vSubtask,
                            zCPCHAR cpcCtrlTag,
                            zPCHAR  lpReturnEntityName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetCollapsingEntityName", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetCollapsingEntityName ", cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;
      lpReturnEntityName[ 0 ] = 0;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         pOL->GetCollapsingEntityName( lpReturnEntityName );
         return( 0 );
      }
#endif
   }

   return( -1 );
} // OL_GetCollapsingEntityName

//./ ADD NAME=OL_GetLastExpandedEntityName
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetLastExpandedEntityName
//
//  PURPOSE:    This operation gets the entity name corresponding to the
//              last expanded tree item
//
//  PARAMETERS: vSubtask           - The subtask view for the window containing
//                                   the tree control.
//              cpcCtrlTag         - The unique name of the control.
//              lpReturnEntityName - The entity name returned to the user
//
//  RETURNS:    0 - Entity name returned
//             -1 - Error locating control
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetLastExpandedEntityName( zVIEW   vSubtask,
                              zCPCHAR cpcCtrlTag,
                              zPCHAR  lpReturnEntityName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetLastExpandedEntityName", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetLastExpandedEntityName ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;
      lpReturnEntityName[ 0 ] = 0;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         pOL->GetLastExpandedEntityName( lpReturnEntityName );
         return( 0 );
      }
#endif
   }

   return( -1 );
} // OL_GetLastExpandedEntityName

//./ ADD NAME=OL_GetLastCollapsedEntityName
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetLastCollapsedEntityName
//
//  PURPOSE:    This operation gets the entity name corresponding to the
//              last collapsed tree item
//
//  PARAMETERS: vSubtask           - The subtask view for the window containing
//                                   the tree control.
//              cpcCtrlTag         - The unique name of the control.
//              lpReturnEntityName - The entity name returned to the user
//
//  RETURNS:    0 - Entity name returned
//             -1 - Error locating control
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetLastCollapsedEntityName( zVIEW   vSubtask,
                               zCPCHAR cpcCtrlTag,
                               zPCHAR  lpReturnEntityName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetLastCollapsedEntityName", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetLastCollapsedEntityName ", cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;
      lpReturnEntityName[ 0 ] = 0;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         pOL->GetLastCollapsedEntityName( lpReturnEntityName );
         return( 0 );
      }
#endif
   }

   return( -1 );
} // OL_GetLastCollapsedEntityName

//./ ADD NAME=OL_GetExpandingEntityName
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetExpandingEntityName
//
//  PURPOSE:    This operation gets the entity name corresponding to the
//              expanding tree item
//
//  PARAMETERS: vSubtask           - The subtask view for the window containing
//                                   the tree control.
//              cpcCtrlTag         - The unique name of the control.
//              lpReturnEntityName - The entity name returned to the user
//
//  RETURNS:    0 - Entity name returned
//             -1 - Error locating control
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
OL_GetExpandingEntityName( zVIEW   vSubtask,
                           zCPCHAR cpcCtrlTag,
                           zPCHAR  lpReturnEntityName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

#ifdef DEBUG_ALL
   TraceLineI( "In OL_GetExpandingEntityName", (zLONG) vSubtask );
#endif

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL )
      {
         TraceLineS( "drvr - Invalid control type for OL_GetExpandingEntityName ", cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;
      lpReturnEntityName[ 0 ] = 0;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         pOL->GetExpandingEntityName( lpReturnEntityName );
         return( 0 );
      }
#endif
   }

   return( -1 );
} // OL_GetExpandingEntityName

//./ ADD NAME=OL_GetCurrentEntityName
// Source Module=ZdCtlMST.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION: OL_GetCurrentEntityName
//                                              05/27/93 Modified: 05/27/93
//
//  PURPOSE:    This operation gets the entity name corresponding to the
//              tree item with focus.
//
//  PARAMETERS: vSubtask    - The subtask view for the window containing
//                            the tree control.
//              cpcCtrlTag  - The unique name of the control.
//              lpReturnView       - The view to the tree mapping object.
//              lpReturnEntityName - The entity name returned to the user
//
//  RETURNS: >= 0 - Entity name returned (with count of selected items)
//             -1 - Error locating control
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zOPER_EXPORT zLONG OPERATION
OL_GetCurrentEntityName( zVIEW    vSubtask,
                         zCPCHAR  cpcCtrlTag,
                         zPVIEW   lpReturnView,
                         zPCHAR   lpReturnEntityName )
{
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;
   zBOOL      bContinue = FALSE;
   zVIEW      vApp = 0;
   zULONG     ulEntityKey = 0;

#ifdef DEBUG_ALL
   TraceLineS( "OL_GetCurrentEntityName: ", cpcCtrlTag );
#endif

   lpReturnEntityName[ 0 ] = 0;
   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
#ifdef ZDR_DEBUG
      if ( pzma->m_ulIdNbr != zTREE_CONTROL ) //???
      {
         TraceLineS( "drvr - Invalid control type for OL_GetCurrentEntityName ",
                     cpcCtrlTag );
         return( -1 );
      }
#endif

#ifdef zUSE_MS_TREE
      ZMSTree *pOL;

      if ( pzma && pzma->m_pCtrl && mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZMSTree, pzma->m_pCtrl )) != 0 )
      {
         bContinue = TRUE;
         vApp = pOL->GetApplicationView( );
         ulEntityKey = pOL->GetSelectedNodeEntityKey( );
      }

      if ( lpReturnView )
         *lpReturnView = vApp;

   // TraceLineI( "OL_GetCurrentEntityName EntityKey: ", ulEntityKey );
      if ( bContinue && ulEntityKey )
      {
         HTREEITEM hItem;
         ZOL_Node *pNode;

         if ( pOL->m_pRootEntry )
            pNode = pOL->m_pRootEntry->FindNodeByEntityKey( ulEntityKey );
         else
         if ( (hItem = pOL->GetSelectedItem( )) != 0 )
            pNode = (ZOL_Node *) pOL->GetItemData( hItem );
         else
            pNode = 0;

         if ( pNode )
         {
            OL_SetCursorByEntityNumber( vApp, pNode->m_csEntityName, ulEntityKey );
            strcpy_s( lpReturnEntityName, zTAG_LTH, pNode->m_csEntityName );
            GetRealEntityName( vApp, lpReturnEntityName );
         }

      // TraceLine( "OL_GetCurrentEntityName Tag: %s  Item: (%d) %s   Entity: %s",
      //            *(pOL->m_pzsTag),
      //            pNode ? pNode->m_ulEntityKey : 0,
      //            (zCPCHAR) (pNode && pNode->m_hItem ? pOL->GetItemText( pNode->m_hItem ) : ""),
      //            lpReturnEntityName );

         return( pOL->GetSelectedCount( ) );
      }
#else
      ZTree *pOL = 0;
      if ( pzma && pzma->m_pCtrl &&
           mIs_hWnd( pzma->m_pCtrl->m_hWnd ) &&
           (pOL = DYNAMIC_DOWNCAST( ZTree, pzma->m_pCtrl )) != 0 &&
           pOL->m_pTree && pOL->m_pTree->OL_EntryCurr )
      {
         bContinue = TRUE;
         vApp = pOL->m_pTree->vApp;
         ulEntityKey = pOL->m_pTree->OL_EntryCurr->m_ulEntityKey;
      }

      if ( bContinue && ulEntityKey )
      {
         // *HH*
         OL_SetCursorByEntityNumber( vApp, pOL->m_pTree->OL_EntryCurr->m_szEntityName, ulEntityKey );
         if ( lpReturnView )
            *lpReturnView = vApp;

         strcpy_s( lpReturnEntityName, zTAG_LTH, pOL->m_pTree->OL_EntryCurr->m_szEntityName );

         return( 0 );
      }
      else
      {
         if ( lpReturnView )
            *lpReturnView = vApp;

         lpReturnEntityName[ 0 ] = 0;
      }
#endif
   }

   return( -1 );
}

#ifdef zUSE_MS_TREE

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


// We cannot just compare entity names because of recursive entities.
// If we are on a subobject, the tree might gives us the actual entity name,
// example TZWDLGSO.Control, but:
// The current entity name might be (example TZWDLGSO) CtrlCtrl.
// Therefore, we compare against the current entity name or the name of the
// subobject root (example TZWDLGSO: Control OR CtrlCtrl).
zSHORT
CompareEntityName( LPENTITYINSTANCE lpSearchEntityInstance, zCPCHAR cpcEntityName )
{
   LPVIEWENTITY lpCurrentViewEntity;
   LPVIEWENTITY lpParentViewEntity;
   LPENTITYINSTANCE  lpParentEntityInstance;
   zLONG lCurrentEREntTok, lParentEREntTok;

   lpCurrentViewEntity =  (LPVIEWENTITY) zGETPTR( lpSearchEntityInstance->hViewEntity );
   lCurrentEREntTok = lpCurrentViewEntity->lEREntTok;
   lpParentViewEntity = lpCurrentViewEntity;
   lpParentEntityInstance = lpSearchEntityInstance;
   do
   {
      if ( zstrcmp( lpParentViewEntity->szName, cpcEntityName ) == 0 )
         return( 0 ); // match

      lpParentEntityInstance = (LPENTITYINSTANCE)
                                  zGETPTR( lpParentEntityInstance->hParent );
      if ( !lpParentEntityInstance )
         break;

      lpParentViewEntity = (LPVIEWENTITY)
                              zGETPTR( lpParentEntityInstance->hViewEntity );
      lParentEREntTok = lpParentViewEntity->lEREntTok;

   } while ( lParentEREntTok == lCurrentEREntTok );

   return( 1 );  // no match
}

//./ ADD NAME=OL_SetCursorByEntityNumber
// Source Module=zdctlmst.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION:  OL_SetCursorByEntityNumber
//                                              10/24/00 Modified: 10/24/00
//
//  PURPOSE:    This operation sets Cursor Position according to the
//              "Twin Count Number" ... the first twin's number is 1.
//
//  PARAMETERS: vSubtask    - The subtask view for the window containing
//                            the control for which to get the dispatch
//                            interface.
//
//  RETURNS:    >= 0 - length of parameter returned
//              -1 - Error locating window or control
//              -2 - Invalid control type
//              -3 - Event not located
//              -4 - Parameter not located
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zOPER_EXPORT zSHORT OPERATION
OL_SetCursorByEntityNumber( zVIEW   v,
                            zCPCHAR cpcEntityName,
                            zULONG  ulEntityNbr )
{
#if 1

   if ( ulEntityNbr )
   {
      zCHAR szEntityName[ zTAG_LTH ];

      // Make sure all entities are in view.
      ResetViewPositions( v );  // Because of a bug in OE when using
                                // zQUAL_ENTITYKEY, some entity
                                // positions are not reset properly
                                // when recursive, so we need to call
                                // ResetViewPositions instead of just
                                // ResetViewFromSubobject.

      strcpy_s( szEntityName, zsizeof( szEntityName ), cpcEntityName );
      GetRealEntityName( v, szEntityName );

      if ( SetEntityCursor( v, szEntityName, 0, zQUAL_ENTITYKEY | zPOS_FIRST | zRECURS,
                            (zCPVOID) &ulEntityNbr, 0, 0, 0, zSCOPE_OI, 0 ) >= zCURSOR_SET )
      {
      // TraceLine( "OL_SetCursorByEntityNumber: %s (%s) Key:0x%08x ===================",
      //            cpcEntityName, szEntityName, lEntityNbr );
      // DisplayEntityInstance( v, szEntityName );
         return( 0 );
      }
   }

   return( -1 );

#else

   zCHAR  szReturnEntity[ zTAG_LTH ];
   LPENTITYINSTANCE  lpSearchEntityInstance;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;

   zLONG             lTwinCount = 0;
   zLONG             lTotalCount = -1;
   zSHORT            k;

   // start with root entity instance
   lpViewCsr = (LPVIEWCSR) zGETPTR( v->hViewCsr );
   lpViewOI  = (LPVIEWOI)  zGETPTR( lpViewCsr->hViewOI );
   lpSearchEntityInstance = (LPENTITYINSTANCE)
                                    zGETPTR( lpViewOI->hRootEntityInstance );

   // We need to count entities matching the name of cpcEntityName.
   for ( ;
         lpSearchEntityInstance;
         lpSearchEntityInstance = (LPENTITYINSTANCE) zGETPTR( lpSearchEntityInstance->hNextHier ) )
   {
      if ( lpSearchEntityInstance->u.nInd.bHidden )
         continue;

      lTotalCount++;
      if ( CompareEntityName( lpSearchEntityInstance, cpcEntityName ) == 0 )
         lTwinCount++;

      if ( lTwinCount >= lEntityNbr )
         break; // we are at the right position, set cursor accordingly
   }

   if ( lpSearchEntityInstance == 0 )
      return( -1 );

   k = SetCursorAbsolutePosition( szReturnEntity, v, lTotalCount );
   return( k );

#endif
}

//./ ADD NAME=OL_GetCurrentEntityNumber
// Source Module=zdctlmst.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  DIALOG OPERATION:  OL_GetCurrentEntityNumber
//
//  PURPOSE:    This operation return the "Twin Count Number" ... the
//              first twin's number is 1.
//
//  PARAMETERS: vSubtask    - The subtask view for the window containing
//                            the control for which to get the dispatch
//                            interface.
//
//  RETURNS:   >= 0  ok
//               -1  Error
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OL_GetCurrentEntityNumber( zVIEW   v,
                           zCPCHAR cpcEntityName,
                           zPULONG pulEntityNbr )
{
#if 1

   zCHAR szEntityName[ zTAG_LTH ];

   strcpy_s( szEntityName, zsizeof( szEntityName ), cpcEntityName );
   *pulEntityNbr = GetEntityKey( v, szEntityName );
   GetRealEntityName( v, szEntityName );

// if ( zstrcmp( szEntityName, cpcEntityName ) != 0 )
//    TraceLineS( "", "" );
//
// TraceLine( "OL_GetCurrentEntityNumber: %s (%s) Key:0x%08x ================", cpcEntityName, szEntityName, *plEntityNbr );
// DisplayEntityInstance( v, cpcEntityName );

   if ( *pulEntityNbr == 0 )
   {
   // *pulEntityNbr = -1;
      return( -1 );
   }

   return( 0 );

#else

   LPVIEWOD          lpViewOD;
   LPVIEWCSR         lpViewCsr;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPENTITYINSTANCE  lpSearchEntityInstance;
   zLONG             lCount;

   *pulEntityNbr = -1;

   // Get the view csr for the view
   lpViewCsr = (LPVIEWCSR) zGETPTR( v->hViewCsr );

   // Get the view object definition for the view
   lpViewOD = (LPVIEWOD) zGETPTR( v->hViewOD );

   // Validate that the entity exists
   lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewOD->hFirstOD_Entity );
   lpViewEntityCsr = (LPVIEWENTITYCSR) zGETPTR( lpViewCsr->hRootViewEntityCsr );

   // If the root cursor is not the first cursor, skip ViewEntities
   // until we get to the entity matching the root cursor.
   // If the view is position on a subobject, then
   // hFirstOD_EntityCsr = root of object (example TZWDLGSO: Dialog)
   // hRootViewEntityCsr = root of subobject (example TZWDLGSO: Control)

   if ( lpViewEntityCsr != (LPVIEWENTITYCSR) zGETPTR( lpViewCsr->hFirstOD_EntityCsr ) )
   {
      LPVIEWENTITYCSR lpSearchViewEntityCsr;

      lpSearchViewEntityCsr = (LPVIEWENTITYCSR) zGETPTR( lpViewCsr->hFirstOD_EntityCsr );
      while ( lpSearchViewEntityCsr != lpViewEntityCsr )
      {
         lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewEntity->hNextHier );
         lpSearchViewEntityCsr++;
      }
   }

   while ( lpViewEntityCsr &&
           zstrcmp( lpViewEntity->szName, cpcEntityName ) != 0 )
   {
      lpViewEntity = (LPVIEWENTITY) zGETPTR( lpViewEntity->hNextHier );
      lpViewEntityCsr = (LPVIEWENTITYCSR) zGETPTR( lpViewEntityCsr->hNextHier );
   }

   // if entity not found return error
   if ( lpViewEntityCsr == 0 )
   {
      return( -1 );
   }

   lCount = 0;
   lpViewCsr = (LPVIEWCSR) zGETPTR( v->hViewCsr );
   lpSearchEntityInstance  = (LPENTITYINSTANCE) zGETPTR( lpViewEntityCsr->hEntityInstance );
   if ( !lpSearchEntityInstance )
   {
      return( -1 );
   }

   if ( lpSearchEntityInstance == UNSET_CSR || lpSearchEntityInstance->u.nInd.bHidden )
   {
      return( -1 );
   }

   // We need to count entities matching the name of cpcEntityName.
   lpSearchEntityInstance = (LPENTITYINSTANCE) zGETPTR( lpSearchEntityInstance->hPrevHier );
   for ( ;
         lpSearchEntityInstance;
         lpSearchEntityInstance = (LPENTITYINSTANCE) zGETPTR( lpSearchEntityInstance->hPrevHier ) )
   {
      if ( lpSearchEntityInstance->u.nInd.bHidden )
         continue;

      if ( CompareEntityName( lpSearchEntityInstance, cpcEntityName ) == 0 )
         lCount++;
   }

   *plEntityNbr = lCount + 1;
   return( 0 );
#endif
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

AFX_EXT_API
CWnd * OPERATION
Outliner( ZSubtask *pZSubtask,
          CWnd     *pWndParent,
          ZMapAct  *pzmaComposite,
          zVIEW    vDialog,
          zSHORT   nOffsetX,
          zSHORT   nOffsetY,
          zKZWDLGXO_Ctrl_DEF *pCtrlDef )
{
   return( new ZMSTree( pZSubtask, pWndParent,
                        pzmaComposite, vDialog,
                        nOffsetX, nOffsetY, pCtrlDef ) );
}
#endif

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// VividTree.cpp : Implementation of Class VividTree
///////////////////////////////////////////////////////////////////////////
//
// Copyright(C) 2005 Jim Alsup  All rights reserved
//              email: ja.alsup@gmail.com
//
// License: This code is provided "as is" with no expressed or implied
//          warranty. You may use, or derive works from this file without
//          any restrictions except those listed below.
//
//        - This original header must be kept in the derived work.
//
//        - If your derived work is distributed in any form, you must
//          notify the author via the email address above and provide a
//          short description of the product and intended audience.
//
//        - You may not sell this code or a derived version of it as part
//          of a commercial code library.
//
//        - Offering the author a free licensed copy of any end product
//          using this code is not required, but does endear you with a
//          bounty of good karma.
//
///////////////////////////////////////////////////////////////////////////

//
// This owner draw tree control allows for the creation of a tree control
// that loosely resembles the user interface used by Skype's main window.
//
// Beside demonstrating the basics of creating an ownerdrawn tree control,
// but more importantly, demonstrates gradient backgrounds fills, bitmap
// backgrounds, flicker free drawing, and how to deal with these in a
// scrollable and resizable dialog.
//
// The underlying gradient or bitmap image is sized according the natural
// size of the visible (on screen or not) tree data.  This can be more
// readily understood and seen by opening and collasping the tree leaf
// with a long text name.  Notice the bmp or gradient resizes to the
// actual screen content.
//
// Version History
//
// Sept 1, 2005  1.0.0  Initial Version

//#include "stdafx.h"
//#include "VividTree.h"
//#include ".\vividtree.h"

#define _TREE_OWNER_DRAW 1  // Set to 0 to use Windows draw code.

// Gradient Filling Helper Routine
void
GradientFillRect( CDC *pDC, CRect &rect, COLORREF clrFrom, COLORREF clrTo, zBOOL bVGrad )
{
   TRIVERTEX       vert[ 2 ];
   GRADIENT_RECT   mesh;

   vert[ 0 ].x     = rect.left;
   vert[ 0 ].y     = rect.top;
   vert[ 0 ].Alpha = 0x0000;
   vert[ 0 ].Blue  = GetBValue( clrFrom ) << 8;
   vert[ 0 ].Green = GetGValue( clrFrom ) << 8;
   vert[ 0 ].Red   = GetRValue( clrFrom ) << 8;

   vert[ 1 ].x     = rect.right;
   vert[ 1 ].y     = rect.bottom;
   vert[ 1 ].Alpha = 0x0000;
   vert[ 1 ].Blue  = GetBValue( clrTo ) << 8;
   vert[ 1 ].Green = GetGValue( clrTo ) << 8;
   vert[ 1 ].Red   = GetRValue( clrTo ) << 8;

   mesh.UpperLeft  = 0;
   mesh.LowerRight = 1;
#if _MSC_VER >= 1300  // only VS7 and above has GradientFill as a pDC member
   pDC->GradientFill( vert, 2, &mesh, 1, bVGrad ? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H );
#else
   GradientFill( pDC->m_hDC, vert, 2, &mesh, 1, bVGrad ? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H );
#endif
}

// CTreeCtrlEx

IMPLEMENT_DYNAMIC(VividTree, CTreeCtrl)

VividTree::VividTree()
{
   m_clrGradientBkgdSel = RGB( 0x80, 0xa0, 0xff );  // blueish
   m_clrGradientBkgdFrom = RGB( 0xff, 0xff, 0xff ); // white
   m_clrGradientBkgdTo = RGB( 0xd5, 0xd5, 0xe0 );   // light greyish blue
   m_BkgdMode = BK_MODE_GRADIENT;
   m_bBmpTiledMode = FALSE;
   m_bGradientHorz = TRUE;

   VERIFY( m_BmpTreeClosed.LoadBitmap( IDB_TREE_CLOSED ) ) ;
   m_BmpTreeClosed.GetSafeHandle();
   VERIFY( m_BmpTreeOpened.LoadBitmap( IDB_TREE_OPENED ) ) ;
   m_BmpTreeOpened.GetSafeHandle();
   m_icon = NULL;
}

VividTree::~VividTree( )
{
   if ( m_BmpBackGround.GetSafeHandle( ) )
      m_BmpBackGround.DeleteObject( );

   if ( m_BmpTreeClosed.GetSafeHandle( ) )
      m_BmpTreeClosed.DeleteObject( );

   if ( m_BmpTreeOpened.GetSafeHandle( ) )
      m_BmpTreeOpened.DeleteObject( );
}

BEGIN_MESSAGE_MAP( VividTree, CTreeCtrl )
   ON_WM_ERASEBKGND( )
#if _TREE_OWNER_DRAW
   ON_WM_PAINT( )
#endif
   ON_NOTIFY_REFLECT( TVN_ITEMEXPANDING, OnTvnItemExpanding )
// ON_WM_CREATE( )
END_MESSAGE_MAP( )

// CVividTree message handlers
BOOL
VividTree::OnEraseBkgnd( CDC *pDC )
{
   // Nothing to do here -- see OnPaint.
   return( TRUE );
}

#if _TREE_OWNER_DRAW

void
VividTree::OnPaint( )
{
   CPaintDC dc( this );   // device context for painting
   CDC dcFlickerFree;     // memory based device context for flicker free painting
   CBitmap bmFlickerFree; // the bitmap we paint into
   CBitmap *pBitmapOld;
   CFont   *pFont;
   CFont   *pFontOld;
   CFont   fontDC;
   int     nModeOld;

   GetClientRect( &m_rect );
   SCROLLINFO scroll_info;

   // Determine window portal into which to draw taking account of scrolling position.
   if ( GetScrollInfo( SB_HORZ, &scroll_info, SIF_POS | SIF_RANGE ) )
   {
      m_nOffsetX = -scroll_info.nPos;
      m_nSizeX = max( scroll_info.nMax+1, m_rect.Width( ) );
   }
   else
   {
      m_nOffsetX = m_rect.left;
      m_nSizeX = m_rect.Width( );
   }

   if ( GetScrollInfo( SB_VERT, &scroll_info, SIF_POS | SIF_RANGE ) )
   {
      if ( scroll_info.nMin == 0 && scroll_info.nMax == 100 )
         scroll_info.nMax = 0;

      m_nOffsetY = -scroll_info.nPos * GetItemHeight( );
      m_nSizeY = max( (scroll_info.nMax + 2) * ((int) GetItemHeight( ) + 1), m_rect.Height( ) );
   }
   else
   {
      m_nOffsetY = m_rect.top;
      m_nSizeY = m_rect.Height( );
   }

   // Create an offscreen dc to paint with (prevents flicker issues).
   dcFlickerFree.CreateCompatibleDC( &dc );
   bmFlickerFree.CreateCompatibleBitmap( &dc, m_rect.Width( ), m_rect.Height( ) );

   // Select the bitmap into the off-screen DC.
   pBitmapOld = (CBitmap *) dcFlickerFree.SelectObject( &bmFlickerFree );

   // Default font in the DC is not the font used by the tree control,
   // so grab it and select it in.
   pFont = GetFont( );
   pFontOld = dcFlickerFree.SelectObject( pFont );

   // We're going to draw text transparently.
   nModeOld = dcFlickerFree.SetBkMode( TRANSPARENT );

   DrawBackGround( &dcFlickerFree );
   DrawItems( &dcFlickerFree );

   // Now Blt the changes to the real device context - this prevents flicker.
   dc.BitBlt( m_rect.left, m_rect.top, m_rect.Width( ), m_rect.Height( ), &dcFlickerFree, 0, 0, SRCCOPY );

   dcFlickerFree.SelectObject( pFontOld );
   dcFlickerFree.SetBkMode( nModeOld );
   dcFlickerFree.SelectObject( pBitmapOld );
}
#endif

// Draw TreeCtrl Background.
void
VividTree::DrawBackGround( CDC *pDC )
{
   BkMode BkgdMode = m_BkgdMode;

   if ( BkgdMode == BK_MODE_BMP )
   {
      if ( m_BmpBackGround.GetSafeHandle( ) == 0 )
         BkgdMode = BK_MODE_GRADIENT;
   }

   if ( BkgdMode == BK_MODE_GRADIENT )
   {
      GradientFillRect( pDC,
                        CRect( m_nOffsetX, m_nOffsetY, m_nSizeX + m_nOffsetX, m_nSizeY + m_nOffsetY ),
                        m_clrGradientBkgdFrom, m_clrGradientBkgdTo, !m_bGradientHorz );
   }
   else
   if ( BkgdMode == BK_MODE_FILL )
      pDC->FillSolidRect( m_rect, pDC->GetBkColor( ) );
   else
   if ( BkgdMode == BK_MODE_BMP )
   {
      BITMAP bmp;
      CDC dcMem;

      VERIFY( m_BmpBackGround.GetObject( sizeof( bmp ), (LPVOID) &bmp ) );
      dcMem.CreateCompatibleDC( NULL );
      CBitmap *pBitmapOld = (CBitmap *) dcMem.SelectObject( &m_BmpBackGround );

      if ( m_bBmpTiledMode )    // Bitmap Tile Mode
      {
         for ( int y = 0; y <= (m_nSizeY / bmp.bmHeight); y++ )
         {
            for ( int x = 0; x <= (m_nSizeX / bmp.bmWidth); x++ )
            {
               pDC->BitBlt( (x * bmp.bmWidth) + m_nOffsetX, (y * bmp.bmHeight) + m_nOffsetY,
                            bmp.bmWidth, bmp.bmHeight, &dcMem, 0, 0, SRCCOPY );
            }
         }
      }
      else  // Bitmap Stretch Mode
      {
         pDC->StretchBlt( m_nOffsetX, m_nOffsetY, m_nSizeX, m_nSizeY,
                          &dcMem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY );
      }

      // Clean up.
      dcMem.SelectObject( pBitmapOld );
   }
   else
      ASSERT( 0 );  // Unknown BackGround Mode
}

// Draw TreeCtrl Items.
void
VividTree::DrawItems( CDC *pDC )
{
   HTREEITEM itemShow;
   HTREEITEM itemParent;
   CRect     rectItem;
   CString   csText;
   COLORREF  clrText;
   DWORD     dwTreeStyle;
   BITMAP    bmp;
   CDC       dcMem;
   CBitmap   *pButtonBmp;
   int       nCnt = 0;
   int       nState;
   zBOOL     bSelected;
   zBOOL     bHasChildren;

   itemShow = GetFirstVisibleItem( );
   if ( itemShow == NULL )
      return;

   dcMem.CreateCompatibleDC( NULL );
   clrText = pDC->GetTextColor( );
   dwTreeStyle = ::GetWindowLong( m_hWnd, GWL_STYLE );

   do
   {
      nState = GetItemState( itemShow, TVIF_STATE );
      itemParent = GetParentItem( itemShow );
      bHasChildren = ItemHasChildren( itemShow ) || itemParent == NULL;
      bSelected = (nState & TVIS_SELECTED) &&
                  ((this == GetFocus( )) || (dwTreeStyle & TVS_SHOWSELALWAYS));

      if ( GetItemRect( itemShow, rectItem, TRUE ) )
      {
         if ( bHasChildren || bSelected )
         {
            COLORREF clrFrom;
            CRect rect;

            // Show
            if ( bSelected )
               clrFrom = m_clrGradientBkgdSel;
            else
               clrFrom = m_clrGradientBkgdTo - (m_clrGradientBkgdFrom - m_clrGradientBkgdTo);

            rect.top = rectItem.top;
            rect.bottom = rectItem.bottom;
            rect.right = m_nSizeX + m_nOffsetX;
            if ( bHasChildren == FALSE )
               rect.left = rectItem.left + m_nOffsetX;
            else
               rect.left = m_nOffsetX;

            GradientFillRect( pDC, rect, clrFrom, m_clrGradientBkgdTo, FALSE );
            pDC->SetTextColor( RGB( 0, 0, 255 ) );

            if ( bHasChildren )
            {
               // Draw an Open/Close button.
               if ( nState & TVIS_EXPANDED )
                  pButtonBmp = &m_BmpTreeOpened;
               else
                  pButtonBmp = &m_BmpTreeClosed;

               VERIFY( pButtonBmp->GetObject( sizeof( bmp ), (LPVOID) &bmp ) );
               CBitmap *pBitmapOld = (CBitmap *) dcMem.SelectObject( pButtonBmp );
               pDC->BitBlt( rectItem.left - bmp.bmWidth - 2, rectItem.top, bmp.bmWidth, bmp.bmHeight,
                            &dcMem, 0, 0, SRCAND );

               // Clean up.
               dcMem.SelectObject( pBitmapOld );
            }
         }

         if ( bHasChildren == FALSE )
         {
            // Look up the ICON instance (if any) and draw it.
            HICON icon = GetItemIcon( itemShow );
            if ( icon )
               DrawIconEx( pDC->m_hDC, rectItem.left - 18, rectItem.top, icon, 16, 16,0,0, DI_NORMAL );
         }

         csText = GetItemText( itemShow );
         rectItem.DeflateRect( 0,1,0,1 );
         if ( bSelected )
         {
            if ( bHasChildren == FALSE  )
               pDC->SetTextColor( GetSysColor( COLOR_HIGHLIGHTTEXT ) );

            COLORREF col = pDC->GetBkColor( );
            pDC->SetBkColor( GetSysColor( COLOR_HIGHLIGHT ) );
            pDC->DrawText( csText, rectItem, DT_LEFT );
            pDC->SetTextColor( clrText );
            pDC->SetBkColor( col );
         }
         else
         {
            pDC->DrawText( csText, rectItem, DT_LEFT );
            pDC->SetTextColor( clrText );
         }

      // if ( nState & TVIS_BOLD )
      //    pDC->SelectObject( pFont );
      }

   } while ( (itemShow = GetNextVisibleItem( itemShow )) != 0 );
}

void
VividTree::SetBitmapID( UINT id )
{
   // Delete any existing bitmap.
   if ( m_BmpBackGround.GetSafeHandle( ) )
      m_BmpBackGround.DeleteObject( );

   // Add in the new bitmap.
   VERIFY( m_BmpBackGround.LoadBitmap( id ) ) ;
   m_BmpBackGround.GetSafeHandle( );
}

// Determine if a referenced item is visible within the control window.
zBOOL
VividTree::IsItemVisible( HTREEITEM item )
{
   HTREEITEM itemScan = GetFirstVisibleItem( );
   while ( itemScan )
   {
      if ( item == itemScan )
         return( TRUE );

      itemScan = GetNextVisibleItem( itemScan );
   }

   return( FALSE );
}

// For a given tree node return an ICON for display on the left side.
// This default implementation only returns one icon.
// This function is virtual and meant to be overriden by deriving a class
// from VividTree and supplying your own icon images.
HICON
VividTree::GetItemIcon( HTREEITEM item )
{
   return( m_icon );  // default implementation - overridable
}

// If the background is a bitmap, and a tree is expanded/collapsed we
// need to redraw the entire background because windows moves the bitmap
// up (on collapse) destroying the position of the background.
void
VividTree::OnTvnItemExpanding( NMHDR *pNMHDR, LRESULT *pResult )
{
   LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>( pNMHDR );
   if ( GetBkMode( ) == VividTree::BK_MODE_BMP && IsItemVisible( pNMTreeView->itemNew.hItem ) )
      Invalidate( );  // redraw everything

   *pResult = 0;
}
