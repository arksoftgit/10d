/////////////////////////////////////////////////////////////////////////////
//
// File:            zdctlvwg.cpp
// *******************************************************************
// *  Copyright © 2001 - 2016 QuinSoft, Inc. and TONBELLER AG.       *
// * All rights reserved.                                            *
// * Confidential and Proprietary material subject to license -      *
// * do not reproduce or disclose. This material is an unpublished   *
// * work and is considered a trade secret belonging to the          *
// * copyright holder.                                               *
// *******************************************************************
// Autor:           TMV
// Datum:           19. April 2001
// description:     Implementation of the Virtual Grid control for the web
//
//
// Change log most recent first order:

// 2002.11.14    HH
//    did not compile with DEBUG_ALL.
//
// 2001.09.24    DKS   Bianca
//    Altered timing of NoteBook Ctrl Mapping.
//
// 2001.04.19    TMV   WEB
//    created
//
/////////////////////////////////////////////////////////////////////////////

#include "zstdafx.h"

#define ZDCTL_CLASS AFX_EXT_CLASS
#include "ZDr.h"

#include "ZdCtl.h"
#include "zdctlvwg.h"
#include "ZdCtlGbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Alignment constants
const static zCPCHAR GRID_ALIGN_LEFT    = "L"; // Left   dbgLeft
const static zCPCHAR GRID_ALIGN_RIGTH   = "R"; // Right    dbgRight
const static zCPCHAR GRID_ALIGN_CENTER  = "C"; // Center   dbgCenter
const static zCPCHAR GRID_ALIGN_DEFAULT = "L"; // General (default left)

// ppe control type identification constants
const static zLONG CONTROL_TYPE_COMBOBOX = 32001;
const static zLONG CONTROL_TYPE_CHECKBOX = 32002;
const static zLONG CONTROL_TYPE_EDIT     = 32003;
const static zLONG CONTROL_TYPE_RADIO    = 32004;
const static zLONG CONTROL_TYPE_RADIOGRP = 32005;

const static zLONG CMB_EMPTY_ENTRY       = 0;
const static zLONG zENTITYSTATE_SELECTED = 1;
// KZXRA Entity & Attribute identification constanst
// the grid itself
const static zCPCHAR pszGrid = "Grid";
// Row-Entity of a grid
const static zCPCHAR pszGridRow = "GridRow";
// column Entity one per subcontrol
const static zCPCHAR pszGridColumn      = "GridColumn";
// the entities describing the subcontrol
const static zCPCHAR pszGridEditBox     = "GridEditBox";
const static zCPCHAR pszGridComboBox    = "GridComboBox";
const static zCPCHAR pszGridCheckBox    = "GridCheckBox";
const static zCPCHAR pszGridRadioGroup  = "GridRadioGroup";
const static zCPCHAR pszGridRadioButton = "GridRadioButton";

const static zCPCHAR pszCtrl            = "Ctrl";
const static zCPCHAR pszCtrlCtrl        = "CtrlCtrl";
const static zCPCHAR pszCtrlMap         = "CtrlMap";

// Cell-Entity of a grid "one Cell one Entity"
const static zCPCHAR pszGridCell = "GridRowCell";
// Combobox Items one entity for each acceptable value
const static zCPCHAR pszGridCmbRowData = "GridCmbRowData";
// GridRow/GridCell-Entity-Attributes
// Tag is the unique identifier for a row or a cell within a row
const static zCPCHAR pszTag            = "Tag";
// NodeIndex is the order of a row or cell within a row
const static zCPCHAR pszNodeIndex      = "NodeIndex";
// Text is the value of cell within a row if it is an edit ctrl
const static zCPCHAR pszText           = "Text";
// Checked is the value of cell within a row if it is a Checkbox ctrl
const static zCPCHAR pszChecked        = "Checked";
// SelectedIndex is the value of cell within a row if it is a ComboBox or RadioGroup ctrl
const static zCPCHAR pszSelectedIndex  = "SelectedIndex";
const static zCPCHAR pszGridSelectedItem = "GridSelectedItem";
// modification attributes
const static zCPCHAR pszDeleteNode     = "DeleteNode";
const static zCPCHAR pszChangeNode     = "ChangeNode";
const static zCPCHAR pszInsertNode     = "InsertNode";
const static zCPCHAR pszEditable       = "Editable";
const static zCPCHAR pszIdNbr          = "IdNbr";

// Column Attributes
const static zCPCHAR pszColumnWidth     = "ColumnWidth";
const static zCPCHAR pszAllowSetFocus   = "AllowSetFocus";
const static zCPCHAR pszForegroundColor = "ForegroundColor";
const static zCPCHAR pszBackgroundColor = "BackgroundColor";
const static zCPCHAR pszTextColor       = "TextColor";
const static zCPCHAR pszFontName        = "FontName";
const static zCPCHAR pszFontSize        = "FontSize";
const static zCPCHAR pszBold            = "Bold";
const static zCPCHAR pszItalic          = "Italic";
const static zCPCHAR pszUnderline       = "UnderLine";
const static zCPCHAR pszStrikeThrough   = "StrikeThrough";
const static zCPCHAR pszAlignment       = "Alignment";
const static zCPCHAR pszPassword        = "Password";
const static zCPCHAR pszCase            = "Case";
const static zCPCHAR pszTextLth         = "TextLth";
const static zCPCHAR pszComboStyle      = "ComboStyle";

IMPLEMENT_DYNAMIC( ZWebGridCell, CObject )
IMPLEMENT_DYNAMIC( ZWebGridRow, CObject )
IMPLEMENT_DYNAMIC( ZWebGridCol, CObject )
IMPLEMENT_DYNAMIC( ZWebGridColEdit, ZWebGridCol )
IMPLEMENT_DYNAMIC( ZWebGridColCheckBox, ZWebGridCol )
IMPLEMENT_DYNAMIC( ZWebGridColComboBox, ZWebGridCol )
IMPLEMENT_DYNAMIC( ZWebGridColRadioGroup, ZWebGridCol )
IMPLEMENT_DYNAMIC( ZWebGridColRadioButton, CObject )
IMPLEMENT_DYNAMIC( ZWebGrid, CWnd )
IMPLEMENT_DYNAMIC( ZWebGridColMapping, CObject )
IMPLEMENT_DYNAMIC( ZWebGridEvent, CObject )
IMPLEMENT_DYNAMIC( ZWebGridEventChain, CObject )
IMPLEMENT_DYNAMIC( ZValueItem, CObject )

//./ ADD NAME=tgGetDomainType
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       tgGetDomainType
//                                            5/9/2001 Modified
//  PURPOSE:     gets the domaintype of an attribute
//
//  PARAMETERS:  zVIEW v -
//               zCPCHAR szEntity -
//               zCPCHAR szAttribute -
/**************************************************************************/
//./END + 2
static zSHORT
tgGetDomainType( zVIEW v, zCPCHAR szEntity, zCPCHAR szAttribute )
{
   LPVIEWENTITY lpViewEntity;
   LPVIEWATTRIB lpViewAttrib;
   LPDOMAIN     lpDomain;

   lpViewEntity = MiGetViewEntityForView( v, szEntity );
   if ( lpViewEntity == 0 )
      return( 0 );

   // find the attribute
   lpViewAttrib = (LPVIEWATTRIB) zGETPTR( lpViewEntity->hFirstOD_Attrib );
   while ( lpViewAttrib )
   {
      if ( zstrcmpi( lpViewAttrib->szName, szAttribute ) == 0 )
         break;

      lpViewAttrib = (LPVIEWATTRIB) zGETPTR( lpViewAttrib->hNextOD_Attrib );
   }

   if ( lpViewAttrib == 0 )
      return( 0 );

   lpDomain = (LPDOMAIN) zGETPTR( lpViewAttrib->hDomain );
   return( (zSHORT) lpDomain->cDomainType );
}

/**************************************************************************
**                                                                       **
** Implementation of ZWebGridCell (a single cell within a grid)          **
**                                                                       **
***************************************************************************/
ZWebGridCell::ZWebGridCell( )
{
   m_bChangedNode  = TRUE;
   m_bEnabled  = TRUE;
   m_bChecked  = FALSE;
   m_lSelected = -1;
   m_csValue.Empty( );
   m_pCol = 0;
   m_pParentGrid = 0;
   m_pRow = 0;
   m_lIndex = -1;
}

ZWebGridCell::~ZWebGridCell( )
{
}

// set the value of the current cell via get view.entity.attribute
zBOOL
ZWebGridCell::SetValueFromOI( zVIEW vApp )
{
   zBOOL bReturn = FALSE;
   COleVariant v;

   if ( vApp == 0 || m_pCol == 0 )
      return( bReturn );

   m_pCol->GetVariantFromAttribute( v, vApp );
   CString csValue = v.bstrVal;
   if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColEdit ) ) )
   {
      SetValue( csValue );
   }
   else
   if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColCheckBox ) ) )
   {
      SetChecked( csValue );
   }
   else
   if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColComboBox ) ) ||
        m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColRadioGroup ) ) )
   {
      SetSelected( csValue );
   }

   return( bReturn );
}

// store the value of the current cell in the underlying view.entity.attribute
zBOOL
ZWebGridCell::SaveValueToOI( zVIEW vApp )
{
   zBOOL bReturn = FALSE;
   if ( vApp && m_pCol )
      bReturn = (zBOOL) m_pCol->MapValueToOI( vApp, this );

   return( bReturn );
}

//./ ADD NAME=ZWebGridCell::SetValueFromXRA
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::SetValueFromXRA
//                                            1/31/2002 Modified
//  PURPOSE:    set the value of the current cell via RemoteObject KZXRA
//              1. set the cells value depending on column type
//              2. fire BeforeRowColChange event
//              3. synchronize cell and row cursor
//              4. fire BeforeColUpdate event
//              5. update the cells value aganist the OI
//              6. fire AfterColUpdate event
//              7. fire RowColChange event
//
//  PARAMETERS: zVIEW vXRA - view to the remote objekt
//
//  RETURN    : TRUE if Update is ok otherwise false
/**************************************************************************/
//./END + 2
zBOOL
ZWebGridCell::SetValueFromXRA( zVIEW vXRA )
{
   zBOOL  bReturn = FALSE;
   zCHAR  szCellChanged[ 32 ];
   zCHAR  szCellInserted[ 32 ];
   zCHAR  szCellDeleted[ 32 ];
   zPCHAR pszValue = 0;

   if ( vXRA == 0 )
      return( bReturn );

   GetStringFromAttribute( szCellChanged, zsizeof( szCellChanged ), vXRA, pszGridCell, pszChangeNode );
   GetStringFromAttribute( szCellInserted, zsizeof( szCellInserted ), vXRA, pszGridCell, pszInsertNode );
   GetStringFromAttribute( szCellDeleted, zsizeof( szCellDeleted ), vXRA, pszGridCell, pszDeleteNode );

   // check additional cell attributes and do something
   // to get this is almost impossible because there is no way to
   // add or delete columns using the lightdriver
   // this is just to complete the XML interface
   if ( szCellInserted[ 0 ] == 'Y' || szCellInserted[ 0 ] == 'y' )
   {
   }

   if ( szCellDeleted[ 0 ] == 'Y' || szCellDeleted[ 0 ] == 'y' )
   {
   }

   // this is the real worlds processing
   if ( szCellChanged[ 0 ] == 'Y' || szCellChanged[ 0 ] == 'y' )
   {
      CString csHelp;
      if ( m_pCol == 0 )
         return( bReturn );

      if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColComboBox ) ) ||
           m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColRadioGroup ) ) )
      {
         zLONG lSelected = -1;
         GetIntegerFromAttribute( &lSelected, vXRA, pszGridCell, pszSelectedIndex );
         SetValue( m_pCol->GetSelection( lSelected ) );
         SetSelected( lSelected );
      }
      else
      // set checked. This will synchronize the value against the checked flag
      // of a checkbox
      if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColCheckBox ) ) )
      {
         zCHAR szChecked[ 32 ];
         GetStringFromAttribute( szChecked, zsizeof( szChecked ), vXRA, pszGridCell, pszChecked );
         zBOOL bChecked = ( ::zstrcmpi( szChecked, "y" ) == 0 );
         SetValue( m_pCol->GetChecked( bChecked ) );
      }
      else
      if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColEdit ) ) )
      {
         GetAddrForAttribute( &pszValue, vXRA, pszGridCell, pszText );
         SetValue( pszValue );
      }
      else // default handler
      {
         GetAddrForAttribute( &pszValue, vXRA, pszGridCell, pszText );
         SetValue( pszValue );
      }
   }

   if ( IsChanged() )
   {
      zLONG lRC =  m_pParentGrid->FireVirtualEvent( DISPID_BeforeRowColChange);

   // if ( lRC != 0 && lRC != zNO_APPLICATION_EVENT)
      if ( lRC != zNO_APPLICATION_EVENT && (zSHORT) zLOUSHORT( lRC ) < 0 )
      {
         LPGRIDROW pRow = GetRow();
         m_pParentGrid->SetCurrentCell( pRow->GetIndex(), GetIndex() );

         zVIEW vApp = 0;
         if ( GetViewByName( &vApp, m_pParentGrid->GetListViewName( ),
                             m_pParentGrid->GetDialogView( ), zLEVEL_ANY ) > 0 )
         {
            m_pParentGrid->FireVirtualEvent( DISPID_BeforeColUpdate );
            if ( SaveValueToOI( vApp ) )
            {
               m_pParentGrid->FireVirtualEvent( DISPID_AfterColUpdate );
            }
         }

         m_pParentGrid->FireVirtualEvent( DISPID_RowColChange );
      }
   }

   return( bReturn );
}

//./ ADD NAME=ZWebGridCell::SaveValueToXRA
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::SaveValueToXRA
//                                            1/31/2002 Modified
//  PURPOSE:     stores a cells value in the remote object
//
//  PARAMETERS:  zVIEW vXRA       - view to the remote objekt
//
//  RETURN    :
/**************************************************************************/
//./END + 2
zBOOL
ZWebGridCell::SaveValueToXRA( zVIEW vXRA )
{
   if ( vXRA == 0 )
      return( FALSE );

   if ( m_bChangedNode == FALSE )
      return( TRUE ); //doing nothing if nothing is changed is ok

   // create a new Cell and supply all values
   CreateEntity( vXRA, pszGridCell, zPOS_LAST );
   // set unique identifier
   // dwKey us unique for a cell in a row
   SetAttributeFromInteger( vXRA, pszGridCell, pszTag, GetIndex() );
   // set index information
   SetAttributeFromInteger( vXRA, pszGridCell, pszNodeIndex, GetIndex() );
   // set change flags
   SetAttributeFromString( vXRA, pszGridCell, pszChangeNode,
                           m_bChangedNode ? "Y" : "N" );
   //SetAttributeFromString( vXRA, pszGridCell, pszInsertNode,
   //                        pCell->IsChanged( ) ? "Y" : "N" );

   // set selected index. this will synchronize the value against the index
   // of a selected combobox- or radiogroup- entry
   if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColComboBox ) ) ||
       m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColRadioGroup ) ) )
   {
//      SetSelected( m_csValue );
      SetAttributeFromInteger( vXRA, pszGridCell, pszSelectedIndex,
                              m_lSelected );
   }
   else
   // set checked. This will synchronize the value against the checked flag
   // of a checkbox
   if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColCheckBox ) ) )
   {
//      SetChecked( m_csValue );
      SetAttributeFromString( vXRA, pszGridCell, pszChecked,
                              m_bChecked ? "Y" : "N" );
   }
   else
   if ( m_pCol->IsKindOf( RUNTIME_CLASS( ZWebGridColEdit ) ) )
   {
      // last but not least the value
      SetAttributeFromString( vXRA, pszGridCell, pszText, m_csValue );
   }
   else // default handler
      SetAttributeFromString( vXRA, pszGridCell, pszText, m_csValue );

   m_bChangedNode = FALSE; // reset change flag
   return( TRUE );
}

//./ ADD NAME=ZWebGridCell::SetChecked
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::SetChecked
//                                            1/31/2002 Modified
//  PURPOSE:
//
//  PARAMETERS: CString csValue -
//
//  RETURN    :
/**************************************************************************/
//./END + 2
void
ZWebGridCell::SetChecked( CString csValue )
{
   zBOOL bChecked = FALSE;
   if ( m_pCol )
   {
      bChecked = m_pCol->IsChecked( csValue );
      if ( bChecked != m_bChecked )
      {
         m_bChecked = bChecked;
         m_bChangedNode = TRUE;
      }
   }
}

void
ZWebGridCell::SetSelected( CString csValue )
{
   if ( m_pCol )
   {
      m_lSelected = m_pCol->GetSelection( csValue );
   }
}

//./ ADD NAME=ZWebGridCell::GetValue
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::GetValue
//                                            4/24/2001 Modified
//  PURPOSE:     returns the value of the current cell
//
//  PARAMETERS: void -
/**************************************************************************/
//./END + 5
zCPCHAR
ZWebGridCell::GetValue( void )
{
   return( m_csValue );
}

zLONG
ZWebGridCell::GetSelection( void )
{
   return( m_lSelected );
}

//./ ADD NAME=ZWebGridCell::SetValue
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::SetValue
//                                            4/24/2001 Modified
//  PURPOSE:     sets the value of the current cell after a check against
//               the old value. Only if old and new value are different
//               the value is changed and the cell gets the changed flag
//
//  PARAMETERS:  zCPCHAR lpszValue - the value to be set
/**************************************************************************/
//./END + 2
void
ZWebGridCell::SetValue( zCPCHAR lpszValue )
{
   if ( m_csValue != lpszValue )
   {
      m_csValue = lpszValue;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCell::SetEnabled( zBOOL bEnable )
{
   if ( m_bEnabled != bEnable )
   {
      m_bEnabled = bEnable;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCell::SetEnabled( zVIEW vApp )
{
   zBOOL bEnabled = FALSE;
   if ( m_pCol )
   {
      // CanUpdateAttribute keeps track about a 0 view
      bEnabled = m_pCol->CanUpdateAttribute( vApp );
   }
}

void
ZWebGridCell::SetSelected( zLONG lSelected )
{
   if ( lSelected != m_lSelected )
   {
      m_lSelected = lSelected;
      m_bChangedNode = TRUE;
   }
}

zBOOL
ZWebGridCell::IsEnabled( void )
{
   return( m_bEnabled );
}

//./ ADD NAME=ZWebGridCell::IsChanged
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::IsChanged
//                                            4/24/2001 Modified
//  PURPOSE:     returns if a cell has ben changed by checking the changed flag
//
//  PARAMETERS:  void -
/**************************************************************************/
//./END + 2
zBOOL
ZWebGridCell::IsChanged( void )
{
   return( m_bChangedNode );
}

//./ ADD NAME=ZWebGridCell::SetGridColumn
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::SetGridColumn
//                                            5/8/2001 Modified
//  PURPOSE:    - attaches a Column object to a cell so a cell always
//                knows about its type and how to translate its value
//
//  PARAMETERS: LPGRIDCOL pCol - pointer to the attached grid column
/**************************************************************************/
//./END + 2
void
ZWebGridCell::SetGridColumn( LPGRIDCOL pCol )
{
   m_pCol = pCol;
   m_pParentGrid = m_pCol->GetGrid( );
}

//./ ADD NAME=ZWebGridCell::GetRow
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::GetRow
//                                            1/31/2002 Modified
//  PURPOSE:     return( the row to which the cell belongs to
//
//  PARAMETERS:
//
//  RETURN    :  LPGRIDROW the parent
/**************************************************************************/
//./END + 5
LPGRIDROW
ZWebGridCell::GetRow( )
{
   return( m_pRow );
}

//./ ADD NAME=ZWebGridCell::SetRow
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridCell::SetRow
//                                            1/31/2002 Modified
//  PURPOSE:    sets the row ( parent ) to which the cell belongs to
//
//  PARAMETERS: LPGRIDROW pRow -
//
//  RETURN    :
/**************************************************************************/
//./END + 2
void
ZWebGridCell::SetRow( LPGRIDROW pRow )
{
   ASSERT( pRow );
   m_pRow = pRow;
}

void
ZWebGridCell::SetIndex( zLONG lIndex )
{
   ASSERT( lIndex >= 0 );
   m_lIndex = lIndex;
}

zLONG
ZWebGridCell::GetIndex( )
{
   return( m_lIndex );
}

/**************************************************************************
**                                                                       **
** Implementation of ZWebGridCol ( a single column within a grid )       **
** a single column can be represented by various controltypes such as    **
** Edit, checkbox, combobox or radiogroup                                **
**                                                                       **
***************************************************************************/

ZWebGridCol::ZWebGridCol( zKZWDLGXO_Ctrl_DEF *pCtrlDef )
{
   m_pMapping = 0;
   m_pParentGrid = 0;
   m_bInitiallyLocked = FALSE;
   m_pCtrlDef = new zKZWDLGXO_Ctrl_DEF;
   zmemcpy( m_pCtrlDef, pCtrlDef, sizeof( zKZWDLGXO_Ctrl_DEF ) );

   m_bShow = TRUE;
   m_bButtonAlways = FALSE;
   m_bInsertNode = TRUE;
   m_bChangedNode = FALSE;
   m_bDeleteNode = FALSE;
   m_bAllowSetFocus = TRUE;

   m_lColumnWidth   = 50;
   m_lDisplayLength = -1;

   // Color members.
   m_lForeColor = 16777215;
   m_lBackColor = 0;
   m_lTextColor = 0;

   // Font members.
   m_csFontName.Empty( );
   m_lFontSize      = 0;
   m_bBold          = FALSE;
   m_bItalic        = FALSE;
   m_bUnderline     = FALSE;
   m_bStrikeThrough = FALSE;

   m_csAlignment    = GRID_ALIGN_DEFAULT;
}

ZWebGridCol::~ZWebGridCol( )
{
   if ( m_pCtrlDef )
      delete( m_pCtrlDef );
}

void
ZWebGridCol::SetMapping( ZWebGridColMapping *pMapping )
{
   if ( m_pMapping )
      delete( m_pMapping );

   m_pMapping = pMapping;
}

void
ZWebGridCol::SetParentGrid( LPGRID pParent )
{
   ASSERT( pParent );
   m_pParentGrid = pParent;
}

LPGRID
ZWebGridCol::GetGrid()
{
   ASSERT( m_pParentGrid );
   return( m_pParentGrid );
}

zVIEW ZWebGridCol::MapToRemoteDataSet( zVIEW vXRA )
{
   zVIEW vReturn = 0;
   if ( vXRA )
   {
      zSHORT nRC = SetCursorFirstEntityByString( vXRA,
                                                 pszGridColumn,
                                                 pszTag,
                                                 m_pCtrlDef->Tag,
                                                 pszGrid );
      if ( nRC <= zCURSOR_UNCHANGED )
      {
         CreateEntity( vXRA, pszGridColumn, zPOS_LAST );
         // supply common attributes
         SetAttributeFromInteger( vXRA, pszGridColumn, pszTag, m_pCtrlDef->IdNbr );
         SetAttributeFromString ( vXRA, pszGridColumn, pszText, m_pCtrlDef->Text );
         SetAttributeFromInteger( vXRA, pszGridColumn, pszIdNbr, m_pCtrlDef->IdNbr );
         SetAttributeFromInteger( vXRA, pszGridColumn, pszNodeIndex, m_pCtrlDef->IdNbr );

         SetAttributeFromString( vXRA, pszGridColumn, pszInsertNode,
                                 m_bInsertNode ? "Y" : "N" );
         m_bInsertNode = FALSE;

         SetAttributeFromString( vXRA, pszGridColumn, pszEditable,
                                 m_bInitiallyLocked ? "Y" : "N" );

         SetAttributeFromString( vXRA, pszGridColumn, pszDeleteNode,
                                 m_bDeleteNode ? "Y" : "N" );
         m_bDeleteNode = FALSE;

         SetAttributeFromString( vXRA, pszGridColumn, pszChangeNode,
                                 m_bChangedNode ? "Y" : "N" );
         m_bChangedNode = FALSE;

         vReturn = vXRA;
      }
   }

   return( vReturn );
}

zSHORT
ZWebGridCol::MapValueToOI( zVIEW vApp, LPGRIDCELL pCell )
{
   zSHORT nRC = zCALL_ERROR;

   if ( vApp == 0 || pCell == 0 || m_pMapping == 0 )
      return( nRC );

   if ( pCell->IsChanged( ) )
   {
      long lCallFlags = zACCEPT_NULL_ENTITY;

      CString csContext = m_pMapping->GetMapContextName( );
      if ( csContext.IsEmpty( ) )
         lCallFlags |= zUSE_DEFAULT_CONTEXT;

      CString csHelp = pCell->GetValue( );
      nRC = SetAttributeFromVariable( vApp,
                                      m_pMapping->GetMapEntityName( ),
                                      m_pMapping->GetMapAttributeName( ),
                                      csHelp,
                                      zTYPE_STRING,
                                      (zSHORT) csHelp.GetLength( ),
                                      csContext,
                                      (zSHORT) lCallFlags );
   }

   return( nRC );
}

zSHORT
ZWebGridCol::GetVariantFromAttribute( COleVariant &v, zVIEW vApp )
{
   zSHORT nRC = zCURSOR_NULL;

   CString cs;
   CString csEntity;
   CString csAttr;
   CString csContext;
   zULONG  ulDisplayLth = 256;
   zBOOL bCheckBox = FALSE;

   cs.Empty( );

   if ( m_pMapping )
   {
      csEntity    = m_pMapping->GetMapEntityName( );
      csAttr      = m_pMapping->GetMapAttributeName( );
      csContext   = m_pMapping->GetMapContextName( );
      ulDisplayLth = m_pMapping->GetAttributeDisplayLength( );
      //****************
      if ( ulDisplayLth == 0 )
      {
         m_pMapping->InitMappingAttributeLength( vApp );
         ulDisplayLth = m_pMapping->GetAttributeDisplayLength( );
         //stil 0 ? set default
         if ( ulDisplayLth == 0 )
            ulDisplayLth = 256;
      }

      //****************
      bCheckBox    = m_pMapping->IsKindOf( RUNTIME_CLASS( ZWebGridColCheckBox ) );
   }

   if ( csEntity.IsEmpty( ) || csAttr.IsEmpty( ) )
      return( nRC );

   zSHORT nFlag = zACCEPT_NULL_ENTITY;
   if ( csContext.IsEmpty( ) )
       nFlag = zACCEPT_NULL_ENTITY | zUSE_DEFAULT_CONTEXT;

   LPSTR szValue = cs.GetBufferSetLength( ulDisplayLth + 1 );
   nRC = GetVariableFromAttribute( szValue, 0, zTYPE_STRING,
                                   ulDisplayLth,
                                   vApp,
                                   csEntity,
                                   csAttr,
                                   csContext,
                                   nFlag );

   if ( nRC == zVAR_NULL )
      szValue[ 0 ] = 0;

   cs.ReleaseBuffer( );

   v = cs;

   return( nRC );
}

zBOOL
ZWebGridCol::IsChecked( CString csValue )
{
   zBOOL bReturn = FALSE;
   LPGRIDCOLCHECKBOX pCheckBox = 0;

   pCheckBox = DYNAMIC_DOWNCAST( ZWebGridColCheckBox, this );
   if ( pCheckBox )
      bReturn = pCheckBox->IsChecked( csValue );

   return( bReturn );
}


CString
ZWebGridCol::GetChecked( zBOOL bChecked )
{
   CString csHelp;
   LPGRIDCOLCHECKBOX pCheckBox = 0;

   csHelp.Empty( );
   pCheckBox = DYNAMIC_DOWNCAST( ZWebGridColCheckBox, this );
   if ( pCheckBox )
      csHelp = pCheckBox->GetChecked( bChecked );

   return( csHelp );
}

zLONG
ZWebGridCol::GetSelection( CString csValue )
{
   zLONG lSelection = -1;
   LPGRIDCOLCOMBOBOX   pComboBox = 0;
   LPGRIDCOlRADIOGROUP pRadioGrp = 0;

   pComboBox = DYNAMIC_DOWNCAST( ZWebGridColComboBox, this );
   if ( pComboBox )
      lSelection = pComboBox->GetSelection( csValue );
   else
   {
      pRadioGrp = DYNAMIC_DOWNCAST( ZWebGridColRadioGroup, this );
      lSelection = pRadioGrp->GetSelection( csValue );
   }

   return( lSelection );
}


CString
ZWebGridCol::GetSelection( zLONG lSelection )
{
   CString csHelp;

   csHelp.Empty( );
   if ( lSelection <= -1 )
      return( csHelp );

   LPGRIDCOLCOMBOBOX   pComboBox = 0;
   LPGRIDCOlRADIOGROUP pRadioGrp = 0;

   pComboBox = DYNAMIC_DOWNCAST( ZWebGridColComboBox, this );
   if ( pComboBox )
      csHelp = pComboBox->GetSelection( lSelection );
   else
   {
      pRadioGrp = DYNAMIC_DOWNCAST( ZWebGridColRadioGroup, this );
      csHelp = pRadioGrp->GetSelection( lSelection );;
   }

   return( csHelp );
}


zBOOL
ZWebGridCol::IsChanged( )
{
   return( m_bChangedNode );
}

zBOOL
ZWebGridCol::IsInitiallyLocked( )
{
   return( m_bInitiallyLocked );
}

void ZWebGridCol::SetInitiallyLocked( zBOOL bLockIt )
{
   zBOOL bColumnEditable = FALSE;

   if ( bLockIt == IsInitiallyLocked( ) ) // there is nothing to do
      return;

   if ( !bLockIt ) // if it's going to get unlocked check if Zeidon allows update
   {
      bColumnEditable = CanUpdateAttribute( 0 );
   }

   if ( bColumnEditable )
      m_bInitiallyLocked = bLockIt;
   else
      m_bInitiallyLocked = FALSE;

   m_bChangedNode = TRUE;
}

zBOOL
ZWebGridCol::CanUpdateAttribute( zVIEW vApp )
{
   zBOOL bColumnEditable = FALSE;
   zVIEW v = vApp;

   if ( m_pMapping )
   {
      if ( vApp == 0 )
         GetViewByName( &v, m_pMapping->GetMapViewName( ),
                        m_pParentGrid->GetDialogView( ), zLEVEL_ANY );
      if ( vApp )
      {
         bColumnEditable = (MiGetUpdateForViewEntityAttr( v,
                                       m_pMapping->GetMapEntityName( ),
                                       m_pMapping->GetMapAttributeName( ),
                                       0 ) > 0) ? TRUE : FALSE;
      }
   }

   return( bColumnEditable );
}

void
ZWebGridCol::SetAlignment( zLONG lAlignment )
{
   CString csHelp;

   switch ( lAlignment )
   {
      case 0:
         csHelp = GRID_ALIGN_LEFT;
         break;
      case 1:
         csHelp = GRID_ALIGN_RIGTH; // Right    dbgRight
         break;
      case 2:
         csHelp = GRID_ALIGN_CENTER; // Center   dbgCenter
         break;
      default:
         csHelp = GRID_ALIGN_DEFAULT; // General (default left)
         break;
   }

   SetAlignment( csHelp );
}

void
ZWebGridCol::SetAlignment( CString csAlignment )
{
   if ( csAlignment != m_csAlignment )
   {
      m_csAlignment  = csAlignment;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetAllowSetFocus( zBOOL bSet )
{
   if ( bSet != m_bAllowSetFocus )
   {
      m_bAllowSetFocus = bSet;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetColumnWidth( zLONG lWidth )
{
   if ( lWidth != m_lColumnWidth )
   {
      m_lColumnWidth = lWidth;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetForeColor( zLONG lForeColor )
{
   if ( lForeColor != m_lForeColor )
   {
      m_lForeColor = lForeColor;
      m_bChangedNode = TRUE;
   }
}


void
ZWebGridCol::SetBackColor( zLONG lBackColor )
{
   if ( lBackColor != m_lBackColor )
   {
      m_lBackColor = lBackColor;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetButtonAlways( zBOOL bButtonAlways )
{
   if ( bButtonAlways != m_bButtonAlways )
   {
      m_bButtonAlways = bButtonAlways;
      m_bChangedNode = TRUE;
   }
}


void
ZWebGridCol::SetTextColor( zLONG lTextColor )
{
   if ( lTextColor != m_lTextColor )
   {
      m_lTextColor  = lTextColor;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetFont( zCPCHAR pFontName,
                      zLONG   lFontSize,
                      zBOOL   bBold,
                      zBOOL   bUnderLine,
                      zBOOL   bItalic,
                      zBOOL   bStrikeThrough )
{
   SetFontName( pFontName );
   SetFontSize( lFontSize );
   SetBold( bBold );
   SetUnderline( bUnderLine );
   SetItalic( bItalic );
   SetStrikeThrough( bStrikeThrough );
}

void
ZWebGridCol::SetFontName( zCPCHAR pFontName )
{
   if ( m_csFontName.Compare( pFontName ) != 0 )
   {
      m_csFontName = pFontName;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetFontSize( zLONG lFontSize )
{
   if ( lFontSize != m_lFontSize )
   {
      m_lFontSize = lFontSize;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetBold( zBOOL bBold )
{
   if ( bBold != m_bBold )
   {
      m_bBold = bBold;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetUnderline( zBOOL bUnderline )
{
   if ( bUnderline != m_bUnderline )
   {
      m_bUnderline = bUnderline;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetItalic( zBOOL bItalic )
{
   if ( bItalic != m_bItalic )
   {
      m_bItalic = bItalic;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetStrikeThrough( zBOOL bStrikeThrough )
{
   if ( bStrikeThrough != m_bStrikeThrough )
   {
      m_bStrikeThrough = bStrikeThrough;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetShowColumn( zBOOL bShow )
{
   if ( m_bShow != bShow )
   {
      m_bShow = bShow;
      // toggle insert & delete state
      m_bDeleteNode = !m_bDeleteNode;
      m_bInsertNode = !m_bDeleteNode;
      m_bChangedNode = TRUE;
   }
}

void
ZWebGridCol::SetTextLength( zLONG lDisplayLength )
{
   if ( m_lDisplayLength != lDisplayLength && lDisplayLength > 0 )
   {
      m_lDisplayLength = lDisplayLength;
      m_bChangedNode = TRUE;
   }
}

zLONG
ZWebGridCol::GetMappingDisplayLength( )
{
   if ( m_lDisplayLength > 0 )
      return( m_lDisplayLength );
   else
      return( (zLONG)m_pMapping->GetAttributeDisplayLength( ) );
}

/**************************************************************************
**                                                                       **
** Implementation of ZWebGridColRadioGroup (a column within              **
** a grid that has the same properties and behavior like a RadionGroup)  **
**                                                                       **
***************************************************************************/
zLONG
ZWebGridColRadioGroup::GetSelection( CString csValue )
{
   zLONG lSelection = -1;
   zBOOL bFound = FALSE;

   POSITION pos = GetFirstButtonPosition( );
   for ( int k = 0; k < m_lRadioButtons.GetCount( ) && bFound == FALSE; k++ )
   {
      LPGRIDCOLRADIOBUTTON pButton = GetNextButton( pos );
      if ( pButton->GetCheckedValue( ) == csValue )
      {
         bFound = TRUE;
         lSelection = k;
      }
   }

   return( lSelection );
}

CString
ZWebGridColRadioGroup::GetSelection( zLONG lSelection )
{
   CString csHelp;

   csHelp.Empty( );
   if ( lSelection <= -1 )
      return( csHelp );

   if ( lSelection < m_lRadioButtons.GetCount( ) )
   {
      POSITION pos = m_lRadioButtons.FindIndex( lSelection );
      if ( pos )
      {
         LPGRIDCOLRADIOBUTTON pButton = (LPGRIDCOLRADIOBUTTON)m_lRadioButtons.GetAt( pos );
         if ( pButton )
            csHelp = pButton->GetCheckedValue( );
      }
   }

   return( csHelp );
}

#ifdef _DEBUG
void ZWebGridColRadioGroup::Dump( CDumpContext& dc ) const
{
   CRuntimeClass *pRc = GetRuntimeClass( );
   CObject::Dump( dc );
   dc << pRc->m_lpszClassName << "\n";
}
#endif


void
ZWebGridColRadioGroup::AddButton( LPGRIDCOLRADIOBUTTON pButton )
{
   m_lRadioButtons.AddTail( pButton );
}

/**************************************************************************
**                                                                       **
** Implementation of ZWebGridColEdit (a column within a grid             **
** that has the same properties and behavior like an editbox)            **
**                                                                       **
***************************************************************************/

ZWebGridColEdit::ZWebGridColEdit( zKZWDLGXO_Ctrl_DEF *CtrlDef ) :
                 ZWebGridCol( CtrlDef )
{
   if ( CtrlDef->Subtype & zEDITBOX_LOWERCASE )
      m_csCase = "L";
   else
   if ( CtrlDef->Subtype & zEDITBOX_UPPERCASE )
      m_csCase = "U";
   else
      m_csCase = "N";

   m_bPassword = zBOOL( CtrlDef->Subtype & zEDITBOX_PASSWORD );
}

ZWebGridColEdit::~ZWebGridColEdit( )
{
}

zVIEW
ZWebGridColEdit::MapToRemoteDataSet( zVIEW vXRA )
{
   zVIEW vReturn = 0;

   if ( vXRA )
   {
      vReturn = ZWebGridCol::MapToRemoteDataSet( vXRA );
      if ( vReturn )
      {
         CreateEntity( vXRA, pszGridEditBox, zPOS_LAST );
         SetAttributeFromInteger( vXRA, pszGridEditBox, pszTag, m_pCtrlDef->IdNbr );
         SetAttributeFromInteger( vXRA, pszGridEditBox,
                                  pszForegroundColor, m_lForeColor);
         SetAttributeFromInteger( vXRA, pszGridEditBox,
                                  pszBackgroundColor, m_lBackColor);
         SetAttributeFromInteger( vXRA, pszGridEditBox,
                                  pszTextColor, m_lTextColor);
         SetAttributeFromString( vXRA, pszGridEditBox,
                                  pszFontName, m_csFontName );
         SetAttributeFromInteger( vXRA, pszGridEditBox,
                                  pszFontSize, m_lFontSize);
         SetAttributeFromString( vXRA, pszGridEditBox,
                                 pszBold, m_bBold ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridEditBox,
                                 pszItalic, m_bItalic ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridEditBox,
                                 pszUnderline, m_bUnderline ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridEditBox,
                                 pszStrikeThrough, m_bStrikeThrough ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridEditBox,
                                 pszAlignment, m_csAlignment );
         SetAttributeFromInteger( vXRA, pszGridEditBox, pszTextLth,
                                  GetMappingDisplayLength( ) );
         SetAttributeFromString( vXRA, pszGridEditBox, pszPassword,
                                 m_bPassword ? "Y" : "N" );
         SetAttributeFromString( vXRA, pszGridEditBox, pszPassword, m_csCase );
      }
   }

   return( vReturn );
}

ZWebGridColCheckBox::ZWebGridColCheckBox( zKZWDLGXO_Ctrl_DEF *CtrlDef ) :
                     ZWebGridCol( CtrlDef )
{
   m_csCheckedValue.Empty( );
   m_csUncheckedValue.Empty( );
}

ZWebGridColCheckBox::~ZWebGridColCheckBox( )
{
}

zVIEW
ZWebGridColCheckBox::MapToRemoteDataSet(  zVIEW vXRA )
{
   zVIEW vReturn = 0;
   if ( vXRA )
   {
      vReturn = ZWebGridCol::MapToRemoteDataSet( vXRA );
      if ( vReturn )
      {
         CreateEntity( vXRA, pszGridCheckBox, zPOS_LAST );
         SetAttributeFromInteger( vXRA, pszGridCheckBox,
                                  pszTag, m_pCtrlDef->IdNbr );
         SetAttributeFromInteger( vXRA, pszGridCheckBox,
                                  pszForegroundColor, m_lForeColor);
         SetAttributeFromInteger( vXRA, pszGridCheckBox,
                                  pszBackgroundColor, m_lBackColor);
         SetAttributeFromInteger( vXRA, pszGridCheckBox,
                                  pszTextColor, m_lTextColor);
         SetAttributeFromString( vXRA, pszGridCheckBox,
                                 pszFontName, m_csFontName );
         SetAttributeFromInteger( vXRA, pszGridCheckBox,
                                  pszFontSize, m_lFontSize);
         SetAttributeFromString( vXRA, pszGridCheckBox,
                                 pszBold, m_bBold ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridCheckBox,
                                 pszItalic, m_bItalic ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridCheckBox,
                                 pszUnderline, m_bUnderline ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridCheckBox,
                                 pszStrikeThrough, m_bStrikeThrough ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridCheckBox,
                                  pszAlignment, m_csAlignment );
      }
   }

   return( vReturn );
}


zBOOL ZWebGridColCheckBox::IsChecked( CString csChecked )
{
   return( m_csCheckedValue == csChecked );
}

CString
ZWebGridColCheckBox::GetChecked( zBOOL bChecked )
{
   if ( bChecked )
      return( m_csCheckedValue );
   else
      return( m_csUncheckedValue );
}

void
ZWebGridColCheckBox::SetCheckboxTranslationValues( zCPCHAR cpcCheckedValue,
                                                   zCPCHAR cpcUncheckedValue )
{
   m_csCheckedValue   = cpcCheckedValue;
   m_csUncheckedValue = cpcUncheckedValue;
}

ZWebGridColComboBox::ZWebGridColComboBox( zKZWDLGXO_Ctrl_DEF *CtrlDef ) :
     ZWebGridCol( CtrlDef )
{
   m_pListMapping = 0;
   m_pBrowseMapping = 0;
   m_bPopulated = FALSE;
}


ZWebGridColComboBox::~ZWebGridColComboBox( )
{
   if ( m_pListMapping ) delete m_pListMapping;
   if ( m_pBrowseMapping ) delete m_pBrowseMapping;

   POSITION pos = m_mapValueItemSet.GetStartPosition( );
   while ( pos )
   {
      zLONG dwKey;
      LPVALUEITEM pItem;
      m_mapValueItemSet.GetNextAssoc( pos, dwKey, pItem );
      delete( pItem );
   }
   m_mapValueItemSet.RemoveAll( );

}

void
ZWebGridColComboBox::SetMapping( ZWebGridColMapping *pMapping )
{
   if ( !m_pMapping )
      ZWebGridCol::SetMapping( pMapping );
   else
   if ( !m_pListMapping )
      m_pListMapping = pMapping;
   else
   if ( !m_pBrowseMapping )
      m_pBrowseMapping = pMapping;
   else
   {
      TraceLineS( "ZWebGridColComboBox::SetMapping","Too much mappings?" );
      delete pMapping;
      pMapping = 0;
   }
}

zLONG
ZWebGridColComboBox::GetSubtype( )
{
   if ( m_pCtrlDef )
      return( m_pCtrlDef->Subtype );
   else
      return( 0 );
}

zLONG
ZWebGridColComboBox::GetSelection( CString csValue )
{
   zLONG lSelection = -1;

   if ( m_bPopulated == FALSE )
      Populate( );

   lSelection = GetEntryIndex( csValue );

   return( lSelection );
}

CString
ZWebGridColComboBox::GetSelection( zLONG lSelection )
{
   LPVALUEITEM pItem = 0;

   CString csHelp;

   csHelp.Empty( );

   if ( m_bPopulated == FALSE )
      Populate( );

   if ( m_mapValueItemSet.Lookup( lSelection, pItem ) )
   {
      csHelp = pItem->GetValue( );
   }

   return( csHelp );
}

POSITION
ZWebGridColComboBox::GetFirstValueItemPosition( )
{
   return( m_mapValueItemSet.GetStartPosition( ) );
}

void
ZWebGridColComboBox::GetNextValueItem( POSITION& rPos, zLONG& rdwKey,
                                       LPVALUEITEM& rItem )
{
   m_mapValueItemSet.GetNextAssoc( rPos, rdwKey, rItem );
}

zLONG
ZWebGridColComboBox::GetEntryIndex( CString csValue )
{
   zLONG lSelection = -1;
   LPVALUEITEM pItem = 0;
   zBOOL bFound = FALSE;
   zLONG dwKey = 0;

   POSITION pos = GetFirstValueItemPosition( );
   while ( pos && !bFound )
   {
      GetNextValueItem( pos, dwKey, pItem );
      if ( pItem )
      {
         if ( pItem->GetValue( ) == csValue )
         {
            bFound = TRUE;
            lSelection = pItem->GetID( );
         }
      }
   }

   return( lSelection );
}

void
ZWebGridColComboBox::Populate( )
{
   zBOOL bListDomainOnly = FALSE;
   zBOOL bIsComboBox = FALSE;
   CString csView;
   CString csEntity;
   CString csAttr;
   CString csContext;
   CString csHelp;
   CStringList csList;
   zULONG  ulDisplayLth;
   zVIEW vApp = 0;

   if ( m_bPopulated )
      return;

   if ( m_pMapping == 0 )
      return;

   csView = m_pMapping->GetMapViewName( );
   csEntity = m_pMapping->GetMapEntityName( );
   csAttr = m_pMapping->GetMapAttributeName( );
   csContext = m_pMapping->GetMapContextName( );
   ulDisplayLth = m_pMapping->GetAttributeDisplayLength( );

   if ( csEntity.IsEmpty( ) || csAttr.IsEmpty( ) )
      return;

   if ( (GetSubtype( ) & zCOMBOBOX_POSITION_ONLY) == 0 )
   {
      bListDomainOnly = TRUE;
   }

   if ( bListDomainOnly )
   {
      zVIEW vApplication;
      if ( GetViewByName( &vApplication, csView,
                          m_pParentGrid->GetDialogView( ), zLEVEL_ANY ) <= 0 )
      {
         TraceLineS( "Unable to load view for ZWebGridColComboBox - ", csView );
         return;
      }
      else
      {
         CreateViewFromViewForTask( &vApp, vApplication, 0 );
      }

      if ( vApp == 0 )
      {
         TraceLineS( "Unable to load view for ZWebGridColComboBox - ", csView );
         return;
      }

      zLONG pCursor = 0;
      PCHAR pchBuffer = csHelp.GetBufferSetLength( ulDisplayLth );

      zSHORT sDomainType = tgGetDomainType( vApp, csEntity, csAttr );
      if ( sDomainType == 'T' )
         RestListOfValues( );
      else
      {
         DropView( vApp );
         return;
      }

      zSHORT nRC = GetFirstTableEntryForAttribute( pchBuffer, ulDisplayLth, vApp, csEntity, csAttr, csContext, &pCursor );
      while ( nRC == 0 )
      {
         csHelp.ReleaseBuffer( );
         if ( ( GetSubtype( ) & zCOMBOBOX_SORT ) == 0 )
         {
            // create a sorted csinglist if neccessary
            POSITION pos = csList.GetHeadPosition( );
            zBOOL bFinished = FALSE;
            while ( pos && !bFinished )
            {
               CString csCompare = csList.GetAt( pos );
               if ( csCompare.Compare( csHelp ) > 0 ) //list should be ascendent
                  bFinished = TRUE;
               else
                  csList.GetNext( pos );
            }
            if ( pos && bFinished )
               csList.InsertBefore( pos, csHelp );
            else
               csList.AddTail( csHelp );
         }
         else
            csList.AddTail( csHelp );

         pchBuffer = csHelp.GetBufferSetLength( ulDisplayLth );
         nRC = GetNextTableEntryForAttribute( pchBuffer, ulDisplayLth, vApp, csEntity, csAttr, csContext, &pCursor );
      }

      csHelp.ReleaseBuffer( );
      POSITION pos = csList.GetHeadPosition( );
      int k = CMB_EMPTY_ENTRY;
      while ( pos )
      {
         csHelp = csList.GetNext( pos );
         LPVALUEITEM pItem = AddValueItem( k );
         pItem->SetId( k );
         pItem->SetValue( csHelp );
         k++;
      }
   }
   else
   {
      if ( GetSubtype( ) & zCOMBOBOX_POSITION_ONLY ||
          GetSubtype( ) & zCOMBOBOX_SELECT        ||
          GetSubtype( ) & zCOMBOBOX_INCLUDE       ||
          GetSubtype( ) & zCOMBOBOX_FOREIGN_KEY )
      {
         RestListOfValues( );
         BuildListOfValuesFromOI( );
      }
   }


   if ( vApp )
      DropView( vApp );

   m_bPopulated = TRUE;

}

void
ZWebGridColComboBox::RestListOfValues( )
{
   POSITION pos = m_mapValueItemSet.GetStartPosition( );
   while ( pos )
   {
      zLONG dwKey;
      LPVALUEITEM pItem;
      m_mapValueItemSet.GetNextAssoc( pos, dwKey, pItem );
      delete( pItem );
   }
   m_mapValueItemSet.RemoveAll( );
}

LPVALUEITEM
ZWebGridColComboBox::AddValueItem( DWORD dwKey )
{
   LPVALUEITEM pItem = new ZValueItem( );
   m_mapValueItemSet[ dwKey ] = pItem;

   return( pItem );
}

LPVALUEITEM
ZWebGridColComboBox::AddValueItem( DWORD dwKey, ZValueItem v )
{
   LPVALUEITEM pItem = new ZValueItem( v );
   m_mapValueItemSet[ dwKey ] = pItem;

   return( pItem );
}


void
ZWebGridColComboBox::BuildListOfValuesFromOI( )
{
   zSHORT   nRC;
   CString csListView;
   CString csListEntity;
   CString csListAttr;
   CString csListContext;
   CString csHelp;
   zULONG  ulDisplayLth;
   zULONG  ulFormatType = 0;
   zVIEW vApp = 0;
   zSHORT  nMinCardinality;
   zSHORT  nMaxCardinality;

   if ( !m_pListMapping || !m_pMapping )
   {
      return;
   }

   csListView      = m_pListMapping->GetMapViewName( );
   csListEntity    = m_pListMapping->GetMapEntityName( );
   csListAttr      = m_pListMapping->GetMapAttributeName( );
   csListContext   = m_pListMapping->GetMapContextName( );
   ulDisplayLth     = m_pListMapping->GetAttributeDisplayLength( );

   if ( csListView.IsEmpty( ) ||
        GetViewByName( &vApp, csListView,
                       m_pParentGrid->GetDialogView( ), zLEVEL_ANY ) < 0 )
   {
      TraceLineS( "Unable to load view for ZWebGridColComboBox - ", csListView );
      return;
   }

   if ( (ulFormatType & zCOMBOBOX_NO_NULL) == 0 )
   {
      // Insert a blank line at the beginning if the cardinality
      // permits it.
      MiGetCardinalityForEntity( (zPUSHORT) &nMinCardinality,
                                 (zPUSHORT) &nMaxCardinality,
                                 vApp, m_pMapping->GetMapEntityName( ) );
   }

   if ( ulFormatType & zCOMBOBOX_POSITION_ONLY )
   {
      zVIEW   vAppList;
      CString csEntity;
      CString csBrowseScope  = m_pBrowseMapping ? m_pBrowseMapping->GetMapEntityName( ) : "";
      CString csBrowseEntity = m_pBrowseMapping ? m_pBrowseMapping->GetMapEntityName( ) : "";
      CString csMapContext;
      zSHORT  nFlag = 0;

      // if no browse entity is specified, defaulting to list entity
      if ( !csBrowseEntity.IsEmpty( ) )
         csEntity = csBrowseEntity;
      else
         csEntity = csListEntity;

      // if no context is specified retrieve the "list attributes" default context
      if ( csListContext.IsEmpty( ) )
      {
         LPVIEWENTITY lpViewEntity;
         LPVIEWATTRIB lpViewAttrib;
         zLPCONTEXT   lpContext;

         lpViewEntity = MiGetViewEntityForView( vApp, csEntity );
         if ( lpViewEntity )
         {
            for ( lpViewAttrib = (LPVIEWATTRIB) zGETPTR( lpViewEntity->hFirstOD_Attrib );
                  lpViewAttrib;
                  lpViewAttrib = (LPVIEWATTRIB) zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
            {
               if ( zstrcmp( lpViewAttrib->szName, csListAttr.GetString() ) == 0 )
               {
                  LPDOMAIN lpDomain = (LPDOMAIN) zGETPTR( lpViewAttrib->hDomain );
                  if ( GetDefaultContext( &lpContext, lpDomain ) &&
                       *(lpContext->szName) )
                  {
                     csListContext = lpContext->szName;
                  }
                  break;
               }
            }
         }
      }

      if ( !csListContext.IsEmpty( ) )
         csMapContext = csListContext;
      else
      {
         // if there is still no context trace an error
         CString csError;
         csError.Format( "ZWebGridColComboBox::BuildListOfValuesFromOI unable to locate attribute %s for entity ", csListAttr );
         TraceLineS( csError, csEntity );
      }

      zLONG lRowCount = CountEntitiesForView( vApp, csEntity );
      if ( nMinCardinality == 0 )
         lRowCount++;

      ZValueItem *ItemArray = new ZValueItem[ lRowCount ];
      zLONG k = 0;
      if ( nMinCardinality == 0 )
      {
         ItemArray[ k ].SetId(-1);
         ItemArray[ k ].SetValue( "" );
         k++;
      }

      CreateViewFromViewForTask( &vAppList, vApp, 0 );
      nRC = SetEntityCursor( vAppList, csEntity, 0,
                             zPOS_FIRST, 0, 0, 0, 0,
                             csBrowseScope, 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         CString csValue;
         zPCHAR szMap = csValue.GetBufferSetLength( ulDisplayLth );
         nRC = GetVariableFromAttribute( szMap, 0, zTYPE_STRING,
                                         ulDisplayLth,
                                         vAppList, csEntity,
                                         csListAttr,
                                         csListContext, nFlag );
         if ( nRC == zVAR_NULL )
            szMap[ 0 ] = 0;

         zLONG ulKey = GetEntityKey( vAppList, csEntity );
         csValue.ReleaseBuffer( );

         ItemArray[ k ].SetId( ulKey );
         ItemArray[ k ].SetValue( csValue );
         k++;

         nRC = SetEntityCursor( vAppList, csEntity, 0,
                                zPOS_NEXT, 0, 0, 0, 0,
                                csBrowseScope, 0 );

      }  // end of:  while ( nRC > zCURSOR_UNCHANGED ) ... looping thru entities

      if ( (GetSubtype( ) & zCOMBOBOX_SORT) == 0 )
      {
         QuickSort( ItemArray, lRowCount, TRUE );
      }

      m_mapValueItemSet.InitHashTable( lRowCount );
      for ( k = 0; k < lRowCount; k++ )
      {
         LPVALUEITEM pItem = AddValueItem( k, ItemArray[ k ] );
      }

      DropView( vAppList );
      delete [] ItemArray;
   }

   m_bPopulated = TRUE;
}

zVIEW
ZWebGridColComboBox::MapToRemoteDataSet( zVIEW vXRA )
{
   zVIEW vReturn = 0;

   if ( vXRA )
   {
      vReturn = ZWebGridCol::MapToRemoteDataSet( vXRA );
      if ( vReturn )
      {
         CreateEntity( vXRA, pszGridComboBox, zPOS_LAST );
         SetAttributeFromInteger( vXRA, pszGridComboBox, pszTag, m_pCtrlDef->IdNbr );
         SetAttributeFromInteger( vXRA, pszGridComboBox,
                                  pszForegroundColor, m_lForeColor);
         SetAttributeFromInteger( vXRA, pszGridComboBox,
                                  pszBackgroundColor, m_lBackColor);
         SetAttributeFromInteger( vXRA, pszGridComboBox,
                                  pszTextColor, m_lTextColor);
         SetAttributeFromString( vXRA, pszGridComboBox,
                                 pszFontName, m_csFontName );
         SetAttributeFromInteger( vXRA, pszGridComboBox,
                                  pszFontSize, m_lFontSize);
         SetAttributeFromString( vXRA, pszGridComboBox,
                                 pszBold, m_bBold ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridComboBox,
                                 pszItalic, m_bItalic ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridComboBox,
                                 pszUnderline, m_bUnderline ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridComboBox,
                                 pszStrikeThrough, m_bStrikeThrough ? "Y":"N" );
         SetAttributeFromString( vXRA, pszGridComboBox,
                                 pszAlignment, m_csAlignment );
         SetAttributeFromString( vXRA, pszGridComboBox,
                                 pszStrikeThrough, m_bButtonAlways ? "Y":"N" );
         POSITION pos = GetFirstValueItemPosition( );
         while ( pos )
         {
            LPVALUEITEM pItem = 0;
            zLONG lKey = 0;
            GetNextValueItem( pos, lKey, pItem );
            CreateEntity( vXRA, pszGridCmbRowData, zPOS_LAST );
            SetAttributeFromInteger ( vXRA, pszGridCmbRowData, pszTag, pItem->GetID( ) );
            // dirty work arround. OE checks the changed flag of each attribute
            // prior to create the xml
#ifdef _DEBUG
            SetAttributeFromString( vXRA, pszGridCmbRowData, pszText, "You Shmock" );
#endif
            SetAttributeFromString( vXRA, pszGridCmbRowData, pszText, pItem->GetValue( ) );
         }
      }
   }

   return( vReturn );
}

zSHORT
ZWebGridColComboBox::MapValueToOI( zVIEW vApp, LPGRIDCELL pCell )
{
   zSHORT nRC = zCALL_ERROR;

   CString csListView;
   CString csListEntity;
   CString csListAttr;
   CString csListContext;
   CString csBrowseScope;
   zULONG  ulFormatType = 0;
   zULONG  ulDisplayLth = 0;
   zVIEW vAppList = 0;

   if ( vApp == 0 || pCell == 0 )
      return( nRC );

   if ( (ulFormatType & zCOMBOBOX_POSITION_ONLY) == 0 )
   {  // simple combobox domain mapping
      // we can use base class implementation
      return( ZWebGridCol::MapValueToOI( vApp, pCell ) );
   }

   if ( m_pListMapping ) // this should only be the case when
   {                     // when this guy is not a domain
      csListView      = m_pListMapping->GetMapViewName( );
      csListEntity    = m_pListMapping->GetMapEntityName( );
      csListAttr      = m_pListMapping->GetMapAttributeName( );
      csListContext   = m_pListMapping->GetMapContextName( );
   }

   ulDisplayLth = m_pMapping->GetAttributeDisplayLength( );
   ulFormatType = GetSubtype( );

   if ( ulFormatType & zCOMBOBOX_POSITION_ONLY )
   {
      if ( GetViewByName( &vAppList, csListView,
                          m_pParentGrid->GetDialogView( ), zLEVEL_ANY ) > 0 )
      {
         // Use the Browse entity name if specified, otherwise use the
         // Mapping entity name as the default to traverse.
         CString csEntity;
         CString csBrowseScope  = m_pBrowseMapping->GetMapEntityName( );
         CString csBrowseEntity = m_pBrowseMapping->GetMapEntityName( );
         zSHORT  nFlag = 0;

         // if no browse entity is specified, defaulting to list entity
         if ( !csBrowseEntity.IsEmpty( ) )
            csEntity = csBrowseEntity;
         else
            csEntity = csListEntity;

         // is there really an entity or is an empty entry selected?
         zLONG lSelected   = pCell->GetSelection( );
         zLONG lEntityKey  = 0;
         LPVALUEITEM pItem = 0;

         if ( m_mapValueItemSet.Lookup( lSelected, pItem ) )
         {
            lEntityKey = pItem->GetID( );
         }

         if ( lEntityKey == CMB_EMPTY_ENTRY ||
              SetEntityCursor( vAppList, csEntity, 0,
                               zQUAL_ENTITYKEY | zPOS_FIRST,
                               (zCPVOID) &lEntityKey,
                               0, 0, 0, 0, 0 ) >= 0)
         {
            if ( ulFormatType & zCOMBOBOX_SELECT )
            {
               SetAllSelectStatesForEntity( vAppList, csListEntity,
                                            FALSE, csBrowseScope );
               if ( lEntityKey == CMB_EMPTY_ENTRY )
                  nRC = SetSelectStateOfEntity( vAppList, csListEntity, TRUE );
            }
            else
            if ( ulFormatType & zCOMBOBOX_INCLUDE )
            {
               if ( CheckExistenceOfEntity( vApp, m_pMapping->GetMapEntityName( ) ) == zCURSOR_SET )
                  ExcludeEntity( vApp, m_pMapping->GetMapEntityName( ), zREPOS_BEFORE );

               if ( lEntityKey == CMB_EMPTY_ENTRY )
               {
                  nRC = IncludeSubobjectFromSubobject( vApp, m_pMapping->GetMapEntityName( ),
                                                       vAppList, csListEntity, zPOS_AFTER );
               }
            }
            else
            if ( ulFormatType & zCOMBOBOX_FOREIGN_KEY )
            {
               nRC = SetAttributeFromVariable( vApp, m_pMapping->GetMapEntityName( ),
                                         m_pMapping->GetMapAttributeName( ), pCell->GetValue( ),
                                         zTYPE_STRING, 0,
                                         m_pMapping->GetMapContextName( ),
                                         m_pMapping->GetMapContextName( ).IsEmpty( ) ?
                                          nFlag | zUSE_DEFAULT_CONTEXT :
                                          (zSHORT) nFlag );
            }
         }
      }
   }

   return( nRC );
}

void
ZWebGridColComboBox::SetInitiallyLocked( zBOOL bLockIt )
{
   zSHORT nColumnEditable = 0;

   if ( bLockIt == IsInitiallyLocked( ) ) // there is nothing to do
      return;

   if ( !bLockIt ) // if it's going to get unlocked check if Zeidon allows update
   {
      if ( m_pMapping )
      {
         zSHORT nOption = 0;
         if (  GetSubtype( ) & zCOMBOBOX_INCLUDE )
            nOption = zUPD_INCLUDE;

         zVIEW vApp = 0;
         GetViewByName( &vApp, m_pMapping->GetMapViewName( ),
                        m_pParentGrid->GetDialogView( ), zLEVEL_ANY );
         if ( vApp )
         {
            nColumnEditable = (MiGetUpdateForViewEntityAttr( vApp,
                                          m_pMapping->GetMapEntityName( ),
                                          m_pMapping->GetMapAttributeName( ),
                                          nOption ) > 0) ? TRUE : FALSE;
         }
      }
   }

   m_bInitiallyLocked = bLockIt;
   m_bChangedNode = TRUE;
}

ZWebGridColRadioGroup::ZWebGridColRadioGroup( zKZWDLGXO_Ctrl_DEF *CtrlDef ) :
                       ZWebGridCol( CtrlDef )
{
}

ZWebGridColRadioGroup::~ZWebGridColRadioGroup( )
{
   while ( m_lRadioButtons.GetCount( ) > 0 )
   {
      CObject *p = m_lRadioButtons.RemoveHead( );
      delete p;
   }
}

zVIEW ZWebGridColRadioGroup::MapToRemoteDataSet(  zVIEW vXRA )
{
   //browse all buttons and transfer button information
   zVIEW vReturn = 0;

   if ( vXRA )
   {
      vReturn = ZWebGridCol::MapToRemoteDataSet( vXRA );
      if ( vReturn )
      {
         CreateEntity( vXRA, pszGridRadioGroup, zPOS_LAST );
         SetAttributeFromInteger ( vXRA, pszGridRadioGroup, pszTag, m_pCtrlDef->IdNbr );
         SetAttributeFromInteger ( vXRA, pszGridRadioGroup,
                                   pszForegroundColor, m_lForeColor);
         SetAttributeFromInteger ( vXRA, pszGridRadioGroup,
                                   pszBackgroundColor, m_lBackColor);
         SetAttributeFromInteger ( vXRA, pszGridRadioGroup,
                                   pszTextColor, m_lTextColor);
         SetAttributeFromString  ( vXRA, pszGridRadioGroup,
                                   pszFontName, m_csFontName );
         SetAttributeFromInteger ( vXRA, pszGridRadioGroup,
                                   pszFontSize, m_lFontSize);
         SetAttributeFromString  ( vXRA, pszGridRadioGroup,
                                   pszBold, m_bBold ? "Y":"N" );
         SetAttributeFromString  ( vXRA, pszGridRadioGroup,
                                   pszItalic, m_bItalic ? "Y":"N" );
         SetAttributeFromString  ( vXRA, pszGridRadioGroup,
                                   pszUnderline, m_bUnderline ? "Y":"N" );
         SetAttributeFromString  ( vXRA, pszGridRadioGroup,
                                   pszStrikeThrough, m_bStrikeThrough ? "Y":"N" );
         SetAttributeFromString  ( vXRA, pszGridRadioGroup,
                                   pszAlignment, m_csAlignment );
         POSITION pos = GetFirstButtonPosition( );
         int k = 0;
         while ( pos )
         {
            LPGRIDCOLRADIOBUTTON pButton = GetNextButton( pos );
            CreateEntity( vXRA, pszGridRadioButton, zPOS_LAST );
            SetAttributeFromInteger ( vXRA, pszGridRadioButton, pszTag, k );
            SetAttributeFromInteger ( vXRA, pszGridRadioButton, pszIdNbr, k );
            SetAttributeFromString  ( vXRA, pszGridRadioButton, pszText, pButton->m_csDisplayValue );
            k++;
         }
      }
   }

   return( vReturn );
}

POSITION
ZWebGridColRadioGroup::GetFirstButtonPosition( )
{
   return( m_lRadioButtons.GetHeadPosition( ) );
}

LPGRIDCOLRADIOBUTTON
ZWebGridColRadioGroup::GetNextButton( POSITION &pos )
{
   return( (LPGRIDCOLRADIOBUTTON) m_lRadioButtons.GetNext( pos ) );
}

ZWebGridColRadioButton::ZWebGridColRadioButton( )
{
   m_csDisplayValue.Empty( );
   m_csValue.Empty( );
   m_bDefault = FALSE;
}

ZWebGridColRadioButton::ZWebGridColRadioButton( zKZWDLGXO_Ctrl_DEF &CtrlDefRB )
{

   zPCHAR pch = (zPCHAR) CtrlDefRB.CtrlBOI;
   if ( pch == 0 )      // there is no CtrlBOI
      return;

   if ( *pch )    // default radio button
   {
      //this is the default button
      m_bDefault = TRUE;
   }

   pch++;
   m_csValue = pch;
   m_csDisplayValue = CtrlDefRB.Text;
}

ZWebGridColRadioButton::~ZWebGridColRadioButton( )
{
}

/////////////////////////////////////////////////////////////////////////////////////
//
//    ZWebGridRow implementation
//
/////////////////////////////////////////////////////////////////////////////////////

ZWebGridRow::ZWebGridRow( LPGRID pGrid, zLONG lIndex, zLONG lCells, zVIEW vTemp )
{
   m_pCellSetArray = 0;
   m_lCells = 0;
   m_ulEntityKey = 0;
   m_lIndex = lIndex;
   m_bSelected = FALSE;
   m_pParentGrid = pGrid;
   m_bChangedNode = FALSE;
   m_bInsertNode = TRUE;
   m_bDeleteNode = FALSE;
   SetNumberOfCells( lCells );

   MapFromOI( vTemp );

}

zSHORT ZWebGridRow::MapFromOI( zVIEW vTemp )
{
   zSHORT nRC = 0;
   COleVariant v;

   for ( zSHORT lCol = 0; lCol < m_lCells && vTemp; lCol++ )
   {
      LPGRIDCOL pGC = m_pParentGrid->GetGridColumn( lCol );

      if ( pGC )
      {
         LPGRIDCELL pCell = GetCell( (DWORD) lCol );
         if ( pCell )
         {
            pCell->SetGridColumn( pGC );
            pCell->SetValueFromOI( vTemp );
         }
      }
   }
   return( nRC );
}

ZWebGridRow::~ZWebGridRow( )
{
   ResetContent( );
}

//./ ADD NAME=ZWebGridRow::SetSelect
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridRow::SetSelect
//                                            4/24/2001 Modified
//  PURPOSE:    set the select state of the current row
//
//  PARAMETERS: zBOOL bSet - TRUE if current row is marked as selected
//                           otherwise false
/**************************************************************************/
//./END + 2
void
ZWebGridRow::SetSelect( zBOOL bSet )
{
   if ( m_bSelected != bSet )
   {
      m_bSelected = bSet;
      m_bChangedNode  = TRUE;
      if ( m_pParentGrid->m_ulMapActFlag2 & zMAPACT_MAPPING_FROM_OI )
         m_pParentGrid->FireVirtualEvent( DISPID_SelChange );
   }
}

//./ ADD NAME=ZWebGridRow::SetEntityKey
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridRow::SetEntityKey
//                                            5/21/2001 Modified
//  PURPOSE:     Set the Zeidon internal unique key for an entity
//
//  PARAMETERS:  zLONG ulKey - the Entity key retrieved by OE call
//                             GetEntityKey
/**************************************************************************/
//./END + 2
void
ZWebGridRow::SetEntityKey( zULONG ulKey )
{
   if ( m_ulEntityKey != ulKey )
   {
      m_ulEntityKey = ulKey;
      m_bChangedNode = TRUE;
   }
}

zULONG
ZWebGridRow::GetEntityKey( )
{
   return( m_ulEntityKey );
}

zLONG
ZWebGridRow::GetIndex( )
{
   return( m_lIndex );
}

//./ ADD NAME=ZWebGridRow::IsChanged
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridRow::IsChanged
//                                            4/24/2001 Modified
//  PURPOSE:     to identify if a row has changed. A row is changed if
//               - the selection flag of the row has been changed or
//               - at least one of the cells has been changed
//
//  PARAMETERS:
/**************************************************************************/
//./END + 2
zBOOL
ZWebGridRow::IsChanged( )
{
   zBOOL bChanged = FALSE;
   LPGRIDCELL pCell = 0;


   if ( m_bChangedNode )              // check if the row is changed
      bChanged = m_bChangedNode;
   else
   {
      for ( zLONG k = 0; k < m_lCells && bChanged == FALSE; k++ )
      {
         pCell = GetCell( k );
         if ( pCell )
            bChanged = pCell->IsChanged( );
     }
   }

   return( bChanged );
}

zBOOL
ZWebGridRow::IsSelected( )
{
   return( m_bSelected );
}

zBOOL
ZWebGridRow::IsDeleted( )
{
   return( m_bDeleteNode );
}

zBOOL
ZWebGridRow::IsInserted( )
{
   return( m_bInsertNode );
}

void
ZWebGridRow::SetDeleted( zBOOL bDeleteNode )
{
   m_bDeleteNode = bDeleteNode;
}

//./ ADD NAME=ZWebGridRow::AddCell
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGridRow::AddCell
//                                            4/24/2001 Modified
//  PURPOSE:     add a cell and return( a pointer to it
//
//  PARAMETERS:  zLONG - Key to adress a cell later on (e.g. index?)
/**************************************************************************/
//./END + 4
LPGRIDCELL
ZWebGridRow::AddCell( zLONG lKey )
{
   LPGRIDCELL pCell = 0;
   /*
   if ( m_mapCellSet.Lookup( dwKey, pCell ) )
   {
      delete pCell;
   }
   pCell = new ZWebGridCell( );
   m_mapCellSet[ dwKey ] = pCell;
   */

   if ( lKey < m_lCells && lKey >= 0 )
      pCell = &(m_pCellSetArray[ lKey ]);

   return( pCell );
}

// retrieve the cell with a given Index
LPGRIDCELL
ZWebGridRow::GetCell( zLONG lCell )
{
   LPGRIDCELL pCell = 0;

   if ( lCell < m_lCells && lCell >= 0 )
      pCell =  &(m_pCellSetArray[ lCell ]);

   return( pCell );
}

// set the number of columns in this row to init the hashtable for
// the m_mapCellSet of this row
void
ZWebGridRow::SetNumberOfCells( zLONG dwCells )
{
   if ( m_pCellSetArray )
      delete [] m_pCellSetArray;

   m_lCells = dwCells;
   m_pCellSetArray = new ZWebGridCell[ m_lCells ];

   for ( zSHORT lCol = 0; lCol < m_lCells; lCol++ )
   {
      LPGRIDCELL pCell = GetCell( (DWORD) lCol );
      if ( pCell && pCell->IsChanged() )
      {
         pCell->SetRow( this );
         pCell->SetIndex( lCol );
      }
   }
}

void
ZWebGridRow::ResetContent( )
{
   /*
   POSITION pos = m_mapCellSet.GetStartPosition( );
   while ( pos )
   {
      DWORD dwKey;
      LPGRIDCELL pCell;
      m_mapCellSet.GetNextAssoc( pos, dwKey, pCell );
      delete pCell;
   }
   m_mapCellSet.RemoveAll( );
   */
   if ( m_pCellSetArray )
      delete [] m_pCellSetArray;
}

/*
POSITION
ZWebGridRow::GetFirstCellPosition( )
{
   return( m_mapCellSet.GetStartPosition( );
}

void
ZWebGridRow::GetNextCell(POSITION &rPos, DWORD &rdwKey, LPGRIDCELL &rCell)
{
   m_mapCellSet.GetNextAssoc( rPos, rdwKey, rCell);
}

*/

zBOOL
ZWebGridRow::LookupCell( zLONG lKey, LPGRIDCELL &rCell)
{
//   return( m_mapCellSet.Lookup( dwKey, rCell );
   zBOOL bReturn = FALSE;
   LPGRIDCELL pCell = 0;

   pCell = GetCell( lKey );
   if ( pCell )
   {
      rCell = pCell;
      bReturn = TRUE;
   }

   return( bReturn );
}

DWORD
ZWebGridRow::GetCellCount( )
{
   return( m_lCells );
}

zSHORT
ZWebGridRow::MapToOI( zVIEW vTemp )
{
   zSHORT nRC = zCALL_ERROR;

   if ( vTemp == 0 )
      return( nRC );

   if ( IsChanged( ) )
   {
      nRC = SetEntityCursor( vTemp,
                               m_pParentGrid->GetListEntity( ),
                               0,
                               zQUAL_ENTITYKEY | zPOS_FIRST,
                               (zCPVOID) &m_ulEntityKey,
                               0, 0, 0, 0, 0 );
      for ( zSHORT lCol = 0; lCol < m_lCells && nRC >= zCURSOR_UNCHANGED; lCol++ )
      {
         LPGRIDCELL pCell = GetCell( (DWORD) lCol );
         if ( pCell && pCell->IsChanged( ) )
            pCell->SaveValueToOI( vTemp );
      }

      nRC = zCURSOR_SET;
      m_bChangedNode = FALSE;
   }
   else
      nRC = zCURSOR_SET;

   return( nRC );
}

zSHORT
ZWebGridRow::MapToRemoteDataset( zVIEW vXRA )
{
   zSHORT nRC = zCALL_ERROR;

   if ( vXRA == 0 )
      return( nRC );

   if ( IsChanged( ) || IsInserted() || IsDeleted() )
   {
      // create a new Row and supply all values
      CreateEntity( vXRA, pszGridRow, zPOS_LAST );
      // set unique identifier
      SetAttributeFromInteger( vXRA, pszGridRow, pszTag, GetEntityKey( ) );
      // set index information
      SetAttributeFromInteger( vXRA, pszGridRow, pszNodeIndex, GetIndex( ) );
      // set change flags in the xra and reset them in the current grid
      // Insert Flag
      SetAttributeFromString( vXRA, pszGridRow, pszChangeNode,
                              IsChanged( ) ? "Y" : "N" );
      if ( m_bChangedNode )
         m_bChangedNode = FALSE;

      // Update Flag
      SetAttributeFromString( vXRA, pszGridRow, pszInsertNode,
                              IsInserted( ) ? "Y" : "N" );
      if ( m_bInsertNode )
         m_bInsertNode = FALSE;

      // Delete Flag
      SetAttributeFromString( vXRA, pszGridRow, pszDeleteNode,
                              IsDeleted( ) ? "Y" : "N" );
      // Select Flag
      if ( IsSelected( ) )
      {
         CreateEntity( vXRA, pszGridSelectedItem, zPOS_LAST );
         SetAttributeFromInteger( vXRA, pszGridSelectedItem, pszTag, GetIndex( ) );
         m_bSelected = FALSE;
      }
      DWORD dwCellCount = GetCellCount( );
      // save each cell value
      for ( DWORD lCellIndex = 0;
            lCellIndex < dwCellCount && lCellIndex >= 0;
            lCellIndex++ )
      {
         LPGRIDCELL pCell = GetCell( lCellIndex );
         if ( pCell )
         {
            pCell->SaveValueToXRA( vXRA );
         }
      }
      nRC = zCURSOR_SET;
      m_bChangedNode = FALSE;
   }
   else
      nRC = zCURSOR_SET;

   return( nRC );
}

/////////////////////////////////////////////////////////////////////////////////////
//
//    ZWebGrid implementation
//
/////////////////////////////////////////////////////////////////////////////////////
ZWebGrid::ZWebGrid( ZSubtask *pZSubtask,
             CWnd     *pWndParent,
             ZMapAct  *pzmaComposite,
             zVIEW    vDialog,
             zSHORT   nOffsetX,
             zSHORT   nOffsetY,
             zKZWDLGXO_Ctrl_DEF *pCtrlDef ) :
          CWnd( ),
          ZMapAct( pZSubtask,          // base class ctor
                   pzmaComposite,
                   pWndParent,
                   this,
                   vDialog,
                   nOffsetX,
                   nOffsetY,
                   pCtrlDef,
                   "Grid" )
{
   m_ulFlag = 0;
   m_bInsertMode = FALSE;

   m_lCurrentRow =  m_lCurrentCell = -1;
   m_lInactiveForeColor = 16777215; //white
   m_lInactiveBackColor = 0;        //black
   m_bAllowAddNew    = FALSE;
   m_bAllowDelete    = FALSE;
   m_bAllowRowSelect = FALSE;
   m_bAllowColSelect = FALSE;
   m_lMultiSelect    = 0;

   m_csListView.Empty( );
   m_csListEntityName.Empty( );
   m_csScopeEntityName.Empty( );
   m_bProcessSubControls = TRUE;

   LoadMapping( vDialog );

   m_bChangedNode = TRUE;
}

ZWebGrid::~ZWebGrid( )
{
   ResetContent( );
}

void
ZWebGrid::CreateZ( )
{
   //just because it's a virtual function of ZMapAct
   //do nothing if zREMOTE_SERVER is defined
}

zVIEW
ZWebGrid::GetDialogView( )
{
   if ( m_pZSubtask == 0 )
   {
      TraceLineS( "Invalid Zeidon Subtask for control ", *m_pzsTag );
      return( 0 );
   }

   return( m_pZSubtask->m_vDialog );

}

zSHORT
ZWebGrid::LoadMapping( zVIEW vDialog )
{
   zSHORT nMapCount = 0;
   zSHORT nRC = 0;

   // check main Control mapping like List & Scope.
   // these mapping are named "List" & "Scope" so they are easily to detect
   // if there is no "named list mapping" we pickup the first column mapping
   // as the list mapping.
   if ( CheckExistenceOfEntity( vDialog, pszCtrlMap ) > zCURSOR_UNCHANGED )
   {
      zKZWDLGXO_CtrlMap_DEF CtrlMapDef;

      nRC = SetCursorFirstEntity( vDialog, pszCtrlMap, 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         nMapCount++;
         CtrlMapDef.lStructSize = sizeof( zKZWDLGXO_CtrlMap_DEF );
         GetStructFromEntityAttrs( (zPCHAR) &CtrlMapDef, vDialog, pszCtrlMap );
         if ( zstrcmp( CtrlMapDef.Tag, "List" ) == 0 )
         {
            m_csListView       = CtrlMapDef.VN;
            m_csListEntityName = CtrlMapDef.EN;
         }
         else
         if ( zstrcmp ( CtrlMapDef.Tag, "Scope" ) == 0 )
         {
            m_csScopeEntityName = CtrlMapDef.EN;
         }
         // ignore other mappings

         nRC = SetCursorNextEntity( vDialog, pszCtrlMap, 0 );
      }

      SetCursorFirstEntity( vDialog, pszCtrlMap, 0 );
   }

   // process all CtrlCtrls
   if ( CheckExistenceOfEntity( vDialog, pszCtrlCtrl ) > zCURSOR_UNCHANGED )
   {
      zBOOL bFirstMapping = TRUE;
      SetViewToSubobject( vDialog, pszCtrlCtrl );
      ZWebGridCol *pCol = 0;
      zKZWDLGXO_Ctrl_DEF CtrlDef;
      int k = 0;

      nRC = SetCursorFirstEntity( vDialog, pszCtrl,"" );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         //check column type and create the it
         CtrlDef.lStructSize = sizeof( zKZWDLGXO_Ctrl_DEF );
         GetStructFromEntityAttrs( (zPCHAR) &CtrlDef, vDialog, pszCtrl );
         CtrlDef.IdNbr = k;
         k++;

         switch ( CtrlDef.Type )
         {
            case CONTROL_TYPE_COMBOBOX :
               pCol = new ZWebGridColComboBox( &CtrlDef );
               if ( pCol )
               {
                  // handle column type specific stuff such as type e.g. Domain / auto include
                  LPGRIDCOLCOMBOBOX pComboBox = (LPGRIDCOLCOMBOBOX) pCol;
               }

               break;

            case CONTROL_TYPE_CHECKBOX :
               pCol = new ZWebGridColCheckBox( &CtrlDef );
               if ( pCol )
               {
                  // handle column type specific stuff such a checked & unchecked values
                  LPGRIDCOLCHECKBOX pCheckBox = (LPGRIDCOLCHECKBOX) pCol;
                  zCPCHAR pszCheckedValue, pszUncheckedValue;

                  pszCheckedValue = (zPCHAR) CtrlDef.CtrlBOI;
                  pszUncheckedValue = pszCheckedValue + zstrlen( pszCheckedValue ) + 1;

                  pCheckBox->SetCheckboxTranslationValues( pszCheckedValue, pszUncheckedValue );
               }

               break;

            case CONTROL_TYPE_EDIT     :
               pCol = new ZWebGridColEdit( &CtrlDef );
               break;

            case CONTROL_TYPE_RADIOGRP :
               pCol = new ZWebGridColRadioGroup( &CtrlDef );
               if ( pCol )
               {
                  // handle column type specific stuff such a checked & unchecked values
                  LPGRIDCOlRADIOGROUP pGroup = (LPGRIDCOlRADIOGROUP) pCol;
                  if ( CheckExistenceOfEntity( vDialog, pszCtrlCtrl ) > zCURSOR_UNCHANGED )
                  {
                     SetViewToSubobject( vDialog, pszCtrlCtrl );
                     LPGRIDCOLRADIOBUTTON pRB = 0;
                     zKZWDLGXO_Ctrl_DEF CtrlDefRB;

                     nRC = SetCursorFirstEntity( vDialog, pszCtrl,"" );
                     while ( nRC > zCURSOR_UNCHANGED )
                     {
                        CtrlDefRB.lStructSize = sizeof( zKZWDLGXO_Ctrl_DEF );
                        GetStructFromEntityAttrs( (zPCHAR) &CtrlDefRB, vDialog, pszCtrl );
                        LPGRIDCOLRADIOBUTTON pButton = new ZWebGridColRadioButton( CtrlDefRB );
                        nRC = SetCursorNextEntity( vDialog, pszCtrl,"" );
                     }
                     ResetViewFromSubobject( vDialog );
                  }
               }

               break;

            default:
               pCol = 0;
               break;
         }

         if ( pCol )
         {
            AddColumn( pCol );
         }

         if ( CheckExistenceOfEntity( vDialog, pszCtrlMap ) > zCURSOR_UNCHANGED )
         {
            zKZWDLGXO_CtrlMap_DEF CtrlMapDef;

            zSHORT nRC = SetCursorFirstEntity( vDialog, pszCtrlMap, 0 );
            while ( nRC > zCURSOR_UNCHANGED )
            {
               CtrlMapDef.lStructSize = sizeof( zKZWDLGXO_CtrlMap_DEF );
               GetStructFromEntityAttrs( (zPCHAR) &CtrlMapDef, vDialog, pszCtrlMap );

               if ( pCol )
               {
                  pCol->SetMapping( new ZWebGridColMapping( CtrlMapDef ) );
               }
               // if the grid as a whole currently has no list mapping
               // pickup the first mapping and use it for list mapping
               if ( bFirstMapping && m_csListView.IsEmpty( ) )
               {
                  m_csListView       = CtrlMapDef.VN;
                  m_csListEntityName = CtrlMapDef.EN;
               }

               nRC = SetCursorNextEntity( vDialog, pszCtrlMap, 0 );
               bFirstMapping = FALSE;
            }


         }

         nRC = SetCursorNextEntity( vDialog, pszCtrl, "" );
      }
      ResetViewFromSubobject( vDialog );
   }

   return( m_listColumns.GetCount( ) );
}

void
ZWebGrid::AddColumn( LPGRIDCOL pCol )
{
   pCol->SetParentGrid( this );
   m_listColumns.AddTail( pCol );
}

//./ ADD NAME=ZWebGrid::ResetContent
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGrid::ResetContent
//                                            4/20/2001 Modified
//  PURPOSE:     used to delete all Rows
//
//  PARAMETERS:
/**************************************************************************/
//./END + 2
void
ZWebGrid::ResetContent( )
{
   POSITION pos = m_mapRowSet.GetStartPosition( );
   while ( pos )
   {
      DWORD dwKey;
      LPGRIDROW pRow;
      m_mapRowSet.GetNextAssoc( pos, dwKey, pRow );
      delete pRow;
   }
   m_mapRowSet.RemoveAll( );
}

//./ ADD NAME=ZWebGrid::ResetSelectionSet
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGrid::ResetSelectionSet
//                                            4/20/2001 Modified
//  PURPOSE:     traverse all the entries and reset the selection flag
//
//  PARAMETERS:  zBOOL bSet - TRUE if rows are selected otherwise FALSE
/**************************************************************************/
//./END + 2
void
ZWebGrid::ResetSelectionSet( zBOOL bSet )
{
   POSITION pos = m_mapRowSet.GetStartPosition( );
   while ( pos )
   {
      DWORD dwKey;
      LPGRIDROW pRow;
      m_mapRowSet.GetNextAssoc( pos, dwKey, pRow );
      pRow->SetSelect( bSet );
   }
}

zBOOL
ZWebGrid::SetValue( DWORD nRow, DWORD nColumn, zCPCHAR pszValue )
{
   zBOOL bOk = FALSE;
   LPGRIDROW pRow = 0;
   // if something has changed in the current row
   // an update has to occur against the mapped view
   if ( m_mapRowSet.Lookup( nRow, pRow ) )
   {
      LPGRIDCELL pCell = 0;
      if ( pRow->LookupCell( nColumn, pCell ) )
      {
         pCell->SetValue( pszValue );
         bOk = TRUE;
      }
   }

   return( bOk );
}


CString
ZWebGrid::GetValue( DWORD nRow, DWORD nColumn )
{
   CString csHelp;
   zBOOL bOk = FALSE;
   LPGRIDROW pRow = 0;

   csHelp.Empty( );
   if ( m_mapRowSet.Lookup( nRow, pRow ) )
   {
      LPGRIDCELL pCell = 0;
      if ( pRow->LookupCell( nColumn, pCell ) )
      {
         csHelp = pCell->GetValue( );
         bOk = TRUE;
      }
   }

   return( csHelp );
}


void
ZWebGrid::SetArrayDimensions( DWORD nRows, DWORD nColumns )
{
   // **** extract of mfc documentation ****
   // Initializes the hash table. For best performance, the hash table size should be a prime number.
   // To minimize collisions the size should be roughly 20 percent larger than the largest
   // anticipated data set.

   if ( m_mapRowSet.GetCount( ) )
   {
      ResetContent( );
      m_nRows = 0;
      m_nColumns = 0;
   }

   if ( nRows <= 0 || nColumns <= 0 )
      return;

   m_nRows = DWORD( nRows * 1.2 );
   m_mapRowSet.InitHashTable( m_nRows );
   m_nColumns = nColumns;
}

LPGRIDROW
ZWebGrid::AddRow( zLONG lEntityKey, zVIEW vTemp )
{
   zLONG lIndex = m_mapRowSet.GetCount( );
   LPGRIDROW pRow = new ZWebGridRow( this, lIndex, m_nColumns, vTemp );

   // set the external key
   pRow->SetEntityKey( lEntityKey );

   // internal key for the hashtable is the index
   m_mapRowSet[ lIndex ] = pRow;

   return( pRow );
}

zSHORT
ZWebGrid::MapFromOI( WPARAM wFlag )
{
   zSHORT nRC = 0;
   DWORD dwHelp = 0;
   LPGRIDROW pRow = 0;

   // under some circumstances such as insert mode
   // we must prevent the control from beeing refreshed to garantee
   // the data is propper shape
   if ( m_bInsertMode )
      return( nRC );

   if ( !m_csListEntityName.IsEmpty( ) && !m_csListView.IsEmpty( ) )
   {
      zLONG lRowCount = 0;
      zVIEW vApp = 0;
      if ( GetViewByName( &vApp, m_csListView,
                          GetDialogView( ), zLEVEL_ANY ) > 0 )
      {
         lRowCount = CountEntitiesForView( vApp, m_csListEntityName );
         // set dimensions / ArrayBounds
         // number of grid columns = number of mappings
         // number of grid Rows = number of entities in the "List" - View
         SetArrayDimensions( lRowCount, m_listColumns.GetCount( ) );
         zVIEW vTemp = 0;
         CreateViewFromViewForTask( &vTemp, vApp, m_pZSubtask->m_vDialog );

         // cache column properties
         nRC = SetEntityCursor( vTemp, m_csListEntityName, 0,
                                m_ulFlag | zPOS_FIRST, 0, 0, 0, 0,
                                m_csScopeEntityName, 0 );

         zULONG ulKey = 0;
         zLONG  lIndex = 0;

         POSITION pos = GetFirstRowPosition();
         while ( nRC > zCURSOR_UNCHANGED )
         {
            ulKey = GetEntityKey( vTemp, m_csListEntityName );
            if ( ulKey == 0 )
            {
               // the error will be reported by oe using SysMessageBox
               ResetContent( );
               nRC = zCURSOR_NULL; // to break the loop
            }
            else
            {  // adding a row means creating an array of cells see SetArrayDimensions
               // by passing the view the row is able to retrieve its cell values
               // at this point there is nothing to do but browsing the view
               if ( pos )
               {
                  GetNextRow( pos, dwHelp, pRow );
                  if ( !pRow )
                  {
                     // AddRow creates a new row and appends it to the list
                     pRow = AddRow( ulKey, vTemp );
                  }
                  else
                  {
                     pRow->MapFromOI( vTemp );
                     pRow->SetEntityKey( ulKey );
                  }
               }
               else
                  pRow = AddRow( ulKey, vTemp );

               if ( pRow )
               {
                  if ( GetSelectStateOfEntity( vTemp, m_csListEntityName ) == zENTITYSTATE_SELECTED )
                     pRow->SetSelect( TRUE );
               }
               nRC = SetEntityCursor( vTemp, m_csListEntityName, 0,
                                      m_ulFlag | zPOS_NEXT, 0, 0, 0, 0,
                                      m_csScopeEntityName, 0 );
            }
         } // end of:  while ( nRC > zCURSOR_UNCHANGED ) ... looping thru entities

         // if there are more rows in the grid than in the oi
         // those rows are obsolete
         while ( pos )
         {
            GetNextRow( pos, dwHelp, pRow );
            if ( pRow )
               pRow->SetDeleted( TRUE );
         }
         DropView( vTemp );
      }
   }

   // transfer the whole grid to the KZXRA
   MapToRemoteDataSet( );

   return( nRC );
}

zSHORT
ZWebGrid::MapToRemoteDataSet( )
{
#ifdef zREMOTE_SERVER
   zVIEW vXRA;

   if ( (vXRA = SetupRemoteObject( ) ) != 0 )
   {
      LPGRIDROW  pRow  = 0;
      LPGRIDCELL pCell = 0;
      DWORD dwKey;
      zLONG lRelNbr = 0;
      // Process subcontrols
      // e.g. combobox entries
      for ( zSHORT sCol = 0; sCol < (zSHORT)m_nColumns && m_bProcessSubControls; sCol++ )
      {
         LPGRIDCOL pGC = GetGridColumn( sCol );
         if ( pGC )
         {
            pGC->MapToRemoteDataSet( vXRA );
         }
      }
      m_bProcessSubControls = FALSE;// do it only once

      if ( CheckExistenceOfEntity( vXRA, pszGridRow ) == 0 )
      {
         zSHORT nRC = SetCursorFirstEntity( vXRA, pszGridRow, 0 );
         while ( nRC >= zCURSOR_SET )
            nRC = DeleteEntity( vXRA, pszGridRow, zREPOS_FIRST );
      }

      POSITION pos = GetFirstRowPosition( );
      while ( pos )
      {
         GetNextRow( pos, dwKey, pRow );
         if ( pRow )
            pRow->MapToRemoteDataset( vXRA );
      }
#ifdef _DEBUG
         DisplayObjectInstance( vXRA, "Grid", 0 );
#endif

      DropView( vXRA );
   }

#endif // zREMOTE_SERVER
   return( 0 );
}

zSHORT
ZWebGrid::MapFromRemoteDataset( )
{

#ifdef zREMOTE_SERVER

   zVIEW  vXRA;
   zLONG  lSelCount = 0;
      ZXRA_Item *pXRA;


   if ( m_pZSubtask->m_pZSocketTask &&
        (pXRA = m_pZSubtask->m_pZSocketTask->
            m_pCacheWndList->Find( *(m_pZSubtask->m_pzsRemoteWndTag),
                                   m_pZSubtask,
                                   "ZWebGrid::MapFromRemoteDataset" )) != 0 &&
        (pXRA->m_vXRA || pXRA->m_vXRA_Delta) )
   {
      zSHORT nPass;

//#ifdef DEBUG_ALL
//      TraceLineS( "ZWebGrid::MapFromRemoteDataset tag: ", *(pzma->m_pzsTag) );
//#endif
      if ( pXRA->m_vXRA_Delta == 0 )
         nPass = 1;
      else
         nPass = 0;

      while ( TRUE )
      {
         if ( nPass == 0 )
            CreateViewFromViewForTask( &vXRA, pXRA->m_vXRA_Delta, m_pZSubtask->m_vDialog );
         else
            CreateViewFromViewForTask( &vXRA, pXRA->m_vXRA, m_pZSubtask->m_vDialog );

         while ( ResetViewFromSubobject( vXRA ) == 0 )
         {
         }
         if ( CheckExistenceOfEntity( vXRA, "Wnd" ) < zCURSOR_SET ||
            SetCursorFirstEntityByString( vXRA, "Wnd", "Tag",
                                   *(m_pZSubtask->m_pzsRemoteWndTag),
                                   0 ) < zCURSOR_SET )
         {
            DropView( vXRA );
            if ( nPass == 0 )
            {
               nPass = 1;
               continue;
            }
            else
            {
               return( -1 );
            }
         }

         if ( PositionOnRemoteCtrl( this, vXRA, FALSE ) )
         {
            if ( CheckExistenceOfEntity( vXRA, pszGrid ) >= zCURSOR_SET )
            {
#ifdef DEBUG_ALL
               DisplayObjectInstance( vXRA, "Grid", 0 );
#endif

               zCHAR   szEntityName[ zTAG_LTH ];
               zBOOL   bFinished = FALSE;
               zUSHORT nLevel;
               zSHORT  nRC;
               zLONG   lRowIndex = -1;
               zLONG   lColIndex = -1;
               LPGRIDROW  pRow = 0;
               LPGRIDROW  pSelectedRow = 0;
               LPGRIDCELL pCell = 0;

               strcpy_s( szEntityName, zsizeof( szEntityName ), pszGrid );

               // XRA has a Hierarchical Cursor, so you can't use SetCursorFirst
               nRC = DefineHierarchicalCursor( vXRA, pszGrid );

               while ( nRC >= zCURSOR_SET && !bFinished )
               {
                  // If current entity is a "Row" entity check if it's changed.
                  // If so retrieve the Tag Attribute which is the unique Key
                  // for a row within the grid. Using this key, we can use the
                  // Lookup method of the hash table to retrieve a row pointer
                  // that we need for subsequent cell manipulations.
                  if ( zstrcmp( szEntityName, pszGridRow ) == 0 )
                  {
                     zCHAR szChanged[ 32 ];
                     zCHAR szInserted[ 32 ];
                     zCHAR szDeleteded[ 32 ];

                     GetStringFromAttribute( szChanged, zsizeof( szChanged ), vXRA,
                                             pszGridRow, pszChangeNode );
                     GetStringFromAttribute( szInserted, zsizeof( szInserted ), vXRA,
                                             pszGridRow, pszInsertNode );
                     GetStringFromAttribute( szDeleteded, zsizeof( szDeleteded ), vXRA,
                                             pszGridRow, pszDeleteNode );

                     if ( szChanged[ 0 ] == 'Y' || szChanged[ 0 ] == 'y' )
                     {
                        // Get unique identifier
                        GetIntegerFromAttribute( &lRowIndex, vXRA, pszGridRow, pszTag );
                        if ( m_mapRowSet.Lookup( lRowIndex, pRow ) )
                           SetCurrentRow( lRowIndex );//will possibly fire BeforeRowColChange and RowColChange

                     }
                     else
                     if ( szInserted[ 0 ] == 'Y' || szInserted[ 0 ] == 'y' )
                     {
                        //Fire a couple of events, retrieve entity number
                        //create a new row and make it the current
                        CreateRowFromXRA();
                     }
                     else
                     if ( szDeleteded[ 0 ] == 'Y' || szDeleteded[ 0 ] == 'y' )
                     {
                        // Get unique identifier
                        GetIntegerFromAttribute( &lRowIndex, vXRA, pszGridRow, pszTag );
                        if ( m_mapRowSet.Lookup( lRowIndex, pRow ) )
                           DeleteRowFromXRA( pRow );
                     }
                     else
                     {
                        pRow = 0;
                     }
                  }
                  else
                  // if current entity is a "Selected Row" entity retrieve the Tag Attribute
                  // which is the unique Key for a row within the grid. We use key to retrieve
                  // a row pointer for a SetSelect( TRUE ) call that will mark the row as selected
                  if ( zstrcmp( szEntityName, pszGridSelectedItem ) == 0 )
                  {
                     lSelCount++;
                     GetIntegerFromAttribute( &lRowIndex, vXRA, pszGridSelectedItem, pszTag );
                     m_mapRowSet.Lookup( lRowIndex, pSelectedRow );
                     if ( pSelectedRow )
                     {
                        pSelectedRow->SetSelect( TRUE );
                     }
                     pSelectedRow = 0;
                  }
                  else
                  // if current entity is a "Cell" check if we have a valid row.
                  // retrieve the Tag Attribute which is the unique Key for a cell within a row.
                  // We use key to retrieve a cell pointer and call the method for setting up
                  // with new data
                  if ( zstrcmp( szEntityName, pszGridCell ) == 0 )
                  {
                     ASSERT( pRow != 0 );
                     if ( pRow )
                     {
                        GetIntegerFromAttribute( &lColIndex, vXRA, pszGridCell, pszTag );
                        if ( pRow->LookupCell( lColIndex, pCell ) )
                        {
                           pCell->SetValueFromXRA( vXRA );
                        }
                     }
                  }
                  else
                  if ( ( zstrcmp( szEntityName, pszGrid ) == 0 )
                         || (zstrcmp( szEntityName, pszGridColumn ) == 0 )
                         || (zstrcmp( szEntityName, pszGridEditBox ) == 0 )
                         || (zstrcmp( szEntityName, pszGridComboBox ) == 0 )
                         || (zstrcmp( szEntityName, pszGridCheckBox ) == 0 )
                         || (zstrcmp( szEntityName, pszGridRadioGroup ) == 0 )
                         || (zstrcmp( szEntityName, pszGridRadioButton ) == 0 ) )
                     ;//nothing to do because layout such as columntype can not be changed
                      // by Lightdriver
                  else
                  {
                     // If we get here we are out of grid scope.
                     bFinished = TRUE;
                  }

                  nRC = SetCursorNextEntityHierarchical( &nLevel,
                                                         szEntityName, vXRA );
               }
            }

            DropHierarchicalCursor( vXRA );
         }
         else
         if ( nPass == 0 )
         {
            nPass = 1;
            DropView( vXRA );
            continue;
         }

         DropView( vXRA );
         break;


      }
   }

#endif // zREMOTE_SERVER

   return( 0 );
}


zSHORT
ZWebGrid::MapToOI( zLONG lFlag )
{
   zSHORT nRC = 0;
   DWORD dwKey = 0, dwCellKey = 0;
   LPGRIDROW  pRow  = 0;
   LPGRIDCELL pCell = 0;
   zVIEW vApp = 0;

   // get the new content from the KZXRA and tranfser it to virtual grid
   if ( MapFromRemoteDataset( ) == 0 )
   {
      //Update the underlying Object instance
      POSITION pos = GetFirstRowPosition( );
      while ( pos )
      {
         GetNextRow( pos, dwKey, pRow );
         if ( pRow )
         {
            DWORD dwCellCount = pRow->GetCellCount( );
            // for each cell
            for ( DWORD lCellIndex = 0;
                  lCellIndex < dwCellCount && lCellIndex >= 0;
                  lCellIndex++ )
            {
               pCell = pRow->GetCell( lCellIndex );
               if ( pCell )
               {
                  pCell->SaveValueToOI( vApp );
               }
            }
         }
      }
   }

   return( nRC );
}

LPGRIDCOL
ZWebGrid::GetGridColumn( short lIndex )
{
   LPGRIDCOL pGC = 0;

   if ( lIndex < m_listColumns.GetCount( ) && lIndex >= 0 )
   {
      POSITION pos = m_listColumns.FindIndex( lIndex );
      if ( pos )
         pGC = (LPGRIDCOL)m_listColumns.GetAt( pos );
   }

   return( pGC );
}

POSITION ZWebGrid::GetFirstRowPosition( )
{
   return( m_mapRowSet.GetStartPosition( ) );
}

void
ZWebGrid::GetNextRow( POSITION& rPos, DWORD& rdwKey, LPGRIDROW& rRow )
{
   m_mapRowSet.GetNextAssoc( rPos, rdwKey, rRow);
}

zCPCHAR
ZWebGrid::GetListViewName( )
{
   return( m_csListView );
}

zCPCHAR
ZWebGrid::GetListEntity( )
{
   return( m_csListEntityName );
}

zCPCHAR
ZWebGrid::GetScope( )
{
   return( m_csScopeEntityName );
}

//////////////////////////////////////////////////////////////////////////////
//
// wrapper for exported functions TG_???????????????
// the grid implementation needs to check for the web environment by using
// DYNAMIC_DOWNCAST or IsKindOf( RUNTIME_CLASS ( ZWebGrid )
// after that the following functions can be called
//
zSHORT
ZWebGrid::LockColumn(zSHORT nIndex, zBOOL bLock)
{
   zSHORT nRC = 0;

   if ( nIndex < 0 || nIndex > m_listColumns.GetCount( ) )
      nRC = -3;
   else
   {
      LPGRIDCOL pGC = GetGridColumn( nIndex );
      pGC->SetInitiallyLocked( bLock );

   }

   return( nRC );
}

zSHORT
ZWebGrid::EnableAutosort( zBOOL bEnable )
{
   zSHORT nRC = 0;

   return( nRC );
}

zSHORT
ZWebGrid::SetCheckBoxTranslation( zSHORT  nColumn,
                                  zCPCHAR cpcTRUE,
                                  zCPCHAR cpcFALSE )
{
   zSHORT nRC = 0;
   return( nRC );
}

zSHORT
ZWebGrid::SetCellData( zCPCHAR pchReturnData, zLONG lRowNbr, zLONG lColNbr )
{
   zSHORT nRC = 0;
   zVIEW vApp;
   CString csText = pchReturnData;

   nRC = SetCurrentCell( lRowNbr, lColNbr );
   if ( nRC != 1 )
   {
      nRC = 0;
      return( nRC );
   }

   // after calling SetCurrentCell the members m_lCurrentRow and m_lCurrentCell
   // should be in good shape so we can call SetValue using those menbers
   if ( SetValue( m_lCurrentRow, m_lCurrentCell, pchReturnData ) )
   {
      if ( GetViewByName( &vApp, m_csListView,
                          GetDialogView( ), zLEVEL_ANY ) <= 0 )
      {
         TraceLineS( "Unable to load view for ZWebGrid - ", m_csListView );
         return( nRC );
      }
      LPGRIDROW pRow = 0;
      if ( m_mapRowSet.Lookup( m_lCurrentRow, pRow ) )
      {
         pRow->MapToOI( vApp );
         nRC = 1;
      }
   }

   return( nRC );
}

zSHORT
ZWebGrid::GetCellData( zPCHAR pchReturnData, zLONG lMaxLth, zLONG lRowNbr, zLONG lColNbr )
{
   zSHORT nRC = 0;

   nRC = SetCurrentCell( lRowNbr, lColNbr );
   if ( nRC != 1 )
   {
      nRC = 0;
      return( nRC );
   }

   *pchReturnData = '\0';
   // after calling SetCurrentCell the members m_lCurrentRow and m_lCurrentCell
   // should be in good shape so we can call GetValue using those members
   CString csValue = GetValue( m_lCurrentRow, m_lCurrentCell );
   strcpy_s( pchReturnData, lMaxLth, csValue );

   return( nRC );
}

zSHORT
ZWebGrid::GetActiveCell( zPLONG plRowNbr, zPLONG plColNbr )
{
   zSHORT nRC = 0;

   *plRowNbr = -1;
   *plColNbr = -1;

   if ( m_lCurrentRow < 0 )
      m_lCurrentRow = 0;

   if ( m_lCurrentCell < 0 )
      m_lCurrentCell = 0;

   LPGRIDROW pRow = 0;
   // whatever happens validate row and column index against row and cell set
   if ( m_mapRowSet.Lookup( m_lCurrentRow, pRow ) )
   {
      LPGRIDCELL pCell = 0;
      if ( !pRow->LookupCell( m_lCurrentCell, pCell ) )
         m_lCurrentCell = -1;
      else
      {
         *plRowNbr = m_lCurrentRow;
         *plColNbr = m_lCurrentCell;
      }
   }
   else
   {
      m_lCurrentRow = -1;
   }

   if ( *plColNbr >= 0 && *plRowNbr >= 0 )
      nRC = 1;

   return( nRC );
}

zSHORT
ZWebGrid::SetCurrentCell( zLONG lRowNbr, zLONG lColNbr )
{
   zSHORT nRC = 0;

   zLONG lHelpRow  = lRowNbr;
   zLONG lHelpCell = lColNbr;

   if ( lRowNbr < 0 )
      lHelpRow = m_lCurrentRow;

   if ( lColNbr < 0 )
      lHelpCell = m_lCurrentCell;

   LPGRIDROW pRow = 0;

   // If something has changed in the current row
   // an update has to occur against the mapped view.
   if ( m_mapRowSet.Lookup( m_lCurrentRow, pRow ) )
   {
      if ( pRow->IsChanged( ) )
      {
         zVIEW vApp;
         if ( GetViewByName( &vApp, m_csListView,
                             GetDialogView( ), zLEVEL_ANY ) <= 0 )
         {
            TraceLineS( "Unable to load view for ZWebGrid - ", m_csListView );
            return( nRC );
         }

         pRow->MapToOI( vApp );
      }
   }

   // Now we can navigate to the new position
   // whatever happens validate row and column index against
   // row and cell set.
   if ( m_mapRowSet.Lookup( lHelpRow, pRow ) )
   {
      LPGRIDCELL pCell = 0;
      if ( !pRow->LookupCell( lHelpCell, pCell ) )
         nRC = 1; // no valid index
      else
      {
         zVIEW vApp;
         if ( GetViewByName( &vApp, m_csListView,
                             GetDialogView( ), zLEVEL_ANY ) <= 0 )
         {
            TraceLineS( "Unable to load view for ZWebGrid - ", m_csListView );
            return( nRC );
         }
         // if function is called from VML code there is a chance that
         // view and grid cursors get out of sync if it is followed
         // by a "Return Refresh" termination so the view cursor has to be set now
         zLONG lEntityKey = 0;
         nRC = SetEntityCursor( vApp,
                                m_csListEntityName,
                                0,
                                zQUAL_ENTITYKEY | zPOS_FIRST,
                                (zCPVOID) &lEntityKey,
                                0, 0, 0, 0, 0 );
         nRC = 1;
         m_lCurrentRow  = lHelpRow;
         m_lCurrentCell = lHelpCell;
      }
   }
   else
   {
      nRC = 1;
   }

   return( nRC );
}


zSHORT
ZWebGrid::SetCurrentRow( zLONG lRowNbr )
{
   zSHORT nRC = 0;

   zLONG lHelpRow  = lRowNbr;

   if ( lRowNbr < 0 )
      lHelpRow = m_lCurrentRow;

   LPGRIDROW pRow = 0;

   if ( lRowNbr == m_lCurrentRow )
      return( 1 );
   else
      FireVirtualEvent( DISPID_BeforeRowColChange );


   // If something has changed in the current row
   // an update has to occur against the mapped view.
   if ( m_mapRowSet.Lookup( m_lCurrentRow, pRow ) )
   {
      zVIEW vApp;
      if ( GetViewByName( &vApp, m_csListView,
                          GetDialogView( ), zLEVEL_ANY ) <= 0 )
      {
         TraceLineS( "Unable to load view for ZWebGrid - ", m_csListView );
         return( nRC );
      }

      pRow->MapToOI( vApp );
   }

   // Now we can navigate to the new position
   // whatever happens validate row and column index against
   // row and cell set.
   if ( m_mapRowSet.Lookup( lHelpRow, pRow ) )
   {
      zVIEW vApp;
      if ( GetViewByName( &vApp, m_csListView,
                          GetDialogView( ), zLEVEL_ANY ) <= 0 )
      {
         TraceLineS( "Unable to load view for ZWebGrid - ", m_csListView );
         return( nRC );
      }
      // if function is called from VML code there is a chance that
      // view and grid cursors get out of sync if it is followed
      // by a "Return Refresh" termination so the view cursor has to be set now
      zLONG lEntityKey = 0;
      nRC = SetEntityCursor( vApp,
                             m_csListEntityName,
                             0,
                             zQUAL_ENTITYKEY | zPOS_FIRST,
                             (zCPVOID) &lEntityKey,
                             0, 0, 0, 0, 0 );
      nRC = 1;
      m_lCurrentRow  = lHelpRow;
      FireVirtualEvent( DISPID_RowColChange );
   }
   else
   {
      nRC = 1;
   }

   return( nRC );
}


zSHORT
ZWebGrid::SetAllowAddNew( zBOOL bAllowAddNew )
{
   zSHORT nRC = 0;

   if ( bAllowAddNew != m_bAllowAddNew )
   {
      m_bAllowAddNew = bAllowAddNew;
      m_bChangedNode = TRUE;
   }

   return( nRC );
}


zSHORT
ZWebGrid::SetAllowDelete( zBOOL bAllowDelete )
{
   zSHORT nRC = 0;

   if ( bAllowDelete != m_bAllowDelete )
   {
      m_bAllowDelete = bAllowDelete;
      m_bChangedNode = TRUE;
   }

   return( nRC );
}


zSHORT
ZWebGrid::SetAllowRowSelect( zBOOL bAllowRowSelect )
{
   zSHORT nRC = 0;

   if ( bAllowRowSelect != m_bAllowRowSelect )
   {
      m_bAllowRowSelect = bAllowRowSelect;
      m_bChangedNode = TRUE;
   }

   return( nRC );
}


zSHORT
ZWebGrid::SetAllowColSelect( zBOOL bAllowColSelect )
{
   zSHORT nRC = 0;

   if ( bAllowColSelect != m_bAllowColSelect )
   {
      m_bAllowColSelect = bAllowColSelect;
      m_bChangedNode = TRUE;
   }

   return( nRC );
}


zSHORT
ZWebGrid::SetMultiSelect( zLONG lMultiSelect )
{
   zSHORT nRC = 0;

   if ( lMultiSelect != m_lMultiSelect )
   {
      m_lMultiSelect = lMultiSelect;
      m_bChangedNode = TRUE;
   }

   return( nRC );
}




//
// end of wrapper for exported functions TG_???????????????
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************
** class name      : ZWebGridColMapping                             **
** base class      : CObject                                               **
** derived classes : none                                                  **
**                                                                         **
** Description     : Hols basic Mapping information and provides           **
**                   serialization                                         **
**                                                                         **
**                                                                         **
****************************************************************************/
ZWebGridColMapping::ZWebGridColMapping( )
{
   m_ulDisplayLth = 0;
   m_csVName.Empty( );
   m_csEName.Empty( );
   m_csAName.Empty( );
   m_csContext.Empty( );
}

ZWebGridColMapping::ZWebGridColMapping(const ZWebGridColMapping& ColumnMapping)
{
   m_ulDisplayLth = 0;
   m_csVName   = ColumnMapping.GetMapViewName( );
   m_csEName   = ColumnMapping.GetMapEntityName( );
   m_csAName   = ColumnMapping.GetMapAttributeName( );
   m_csContext = ColumnMapping.GetMapContextName( );
}

ZWebGridColMapping::ZWebGridColMapping( zCPCHAR pszView, zCPCHAR pszEntity,
                                        zCPCHAR pszAttribute, zCPCHAR pszContext)
{
   m_ulDisplayLth = 0;
   SetMapping( pszView, pszEntity, pszAttribute, pszContext );
}

ZWebGridColMapping::~ZWebGridColMapping( )
{
}

ZWebGridColMapping::ZWebGridColMapping( zKZWDLGXO_CtrlMap_DEF CtrlMapDEF )
{
   m_ulDisplayLth = 0;
   SetMapping( CtrlMapDEF.VN, CtrlMapDEF.EN,
               CtrlMapDEF.AN, CtrlMapDEF.Context );
}

/**************************************************************************/
// Function name   : ZWebGridColMapping::SetMapping
// Description     :
// Return type     : void
// Argument        : zCPCHAR pszView         pointer to a views name
// Argument        : zCPCHAR pszEntity       pointer to an entityname name
//                                           within the view above
// Argument        : zCPCHAR pszAttribute    pointer to an attributename name
//                                           within the view entity above
// Argument        : zCPCHAR pszContext      pointer to a contextname of the
//                                           attribute above
/**************************************************************************/
void
ZWebGridColMapping::SetMapping( zCPCHAR pszView,
                                zCPCHAR pszEntity,
                                zCPCHAR pszAttribute,
                                zCPCHAR pszContext )
{
   m_csVName   = pszView;
   m_csEName   = pszEntity;
   m_csAName   = pszAttribute;
   m_csContext = pszContext;
}

/**************************************************************************/
// Function name   : ZWebGridColMapping::InitMappingAttributeLength
// Description     : Retrieves the max. input length of an attribute
// Return type     : void
// Argument        : zVIEW vApp hosting current entity and attribute
/**************************************************************************/
void
ZWebGridColMapping::InitMappingAttributeLength( zVIEW vApp )
{
   if ( m_csVName.IsEmpty( ) || m_csEName.IsEmpty( ) || m_csAName.IsEmpty( ) )
      return;

   ::GetAttributeDisplayLength( &m_ulDisplayLth, vApp,
                                m_csEName,
                                m_csAName,
                                m_csContext.IsEmpty( ) ?
                                   0 : (zCPCHAR) m_csContext );
}

/**************************************************************************/
// Function name   : ZWebGridColMapping::GetAttributeDisplayLength
// Description     : returns the max. input length of an attribute
//                   there must be a call to InitMappingAttributeLength
//                   prior to call this function
// Return type     : zULONG
/**************************************************************************/
zULONG ZWebGridColMapping::GetAttributeDisplayLength( )
{
   return( m_ulDisplayLth );
}

/****************************************************************************
** class name      : ZVirtualWebColumns                                    **
** base class      : CObList                                               **
** derived classes : none                                                  **
**                                                                         **
**                                                                         **
** Description     : just a container to hold all Zeidon specific column   **
**                   informations. All entries in this list shoud be       **
**                   derived from from ZWebGridCol                  **
****************************************************************************/

ZVirtualWebColumns::ZVirtualWebColumns( )
{
}

ZVirtualWebColumns::~ZVirtualWebColumns( )
{
   while ( GetCount( ) > 0 )
   {
      CObject *p = RemoveHead( );
      delete( p );
   }
}

#ifdef _DEBUG

void ZVirtualWebColumns::Dump( CDumpContext& dc ) const
{
   CObList::Dump( dc );
   POSITION pos = GetHeadPosition( );
   while ( pos )
   {
      CObject* p = (CObject *) GetNext( pos );
      if ( p )
         p->Dump( dc );
   }
}

#endif //_DEBUG

ZValueItem::ZValueItem( zLONG lIdentifier, zCPCHAR cpcValue )
{
   m_lIdentifier = lIdentifier;
   m_csValue = cpcValue;
}

ZValueItem::ZValueItem( ZValueItem& v )
{
   m_lIdentifier = v.GetID( );
   m_csValue = v.GetValue( );
}


ZValueItem::~ZValueItem( )
{
}

void
ZValueItem::SetValue( zCPCHAR cpcValue )
{
   m_csValue = cpcValue;
}

void
ZValueItem::SetId( zLONG lIdentifier )
{
   m_lIdentifier = lIdentifier;
}

zBOOL
ZValueItem::operator > ( ZValueItem& comp)
{
   return( zstrcmp( m_csValue.GetString(), comp.m_csValue.GetString() ) > 0 );
}

zBOOL
ZValueItem::operator < ( ZValueItem& comp )
{
   return( zstrcmp( m_csValue.GetString(), comp.m_csValue.GetString() ) < 0 );
}

zBOOL
ZValueItem::operator == ( ZValueItem& comp )
{
   return( (m_csValue == comp.GetValue( )) );
}

void
ZValueItem::operator = ( ZValueItem& comp )
{
   m_csValue = comp.GetValue( );
   m_lIdentifier = comp.GetID( );
}

CString
ZValueItem::GetValue( )
{
   return( m_csValue );
}

zLONG
ZValueItem::GetID( )
{
   return( m_lIdentifier );
}

ZWebGridEvent::ZWebGridEvent( zLONG lEvent )
{
}

ZWebGridEvent::~ZWebGridEvent()
{
}

////////////////////////////////////////////////////////////////////
//  Event chain implementation of webgrid ( reuseable )
//
ZWebGridEventChain::ZWebGridEventChain()
{
}

ZWebGridEventChain::~ZWebGridEventChain()
{
   RemoveAll();
}

void ZWebGridEventChain::Cancel()
{
   RemoveAll();
}

void ZWebGridEventChain::RemoveAll()
{
   POSITION pos = m_mapEventSet.GetStartPosition( );
   while ( pos )
   {
      zLONG lKey;
      LPGRIDEVENT pEvent;
      m_mapEventSet.GetNextAssoc( pos, lKey, pEvent );
      delete pEvent;
   }
   m_mapEventSet.RemoveAll( );
}

/////////////////////////////////////////////////////////////////////////////
//
// Special Functions for global grid operations
// The windows implementation of those functions can be found
// within the truegrid cpp files
//
/////////////////////////////////////////////////////////////////////////////

//./ ADD NAME=ZWEBGRID_LockColumn
// Source Module=zdctlo.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       ZWEBGRID_LockColumn
//                                           07/13/2001 Modified: 07/14/2001
//
//  PURPOSE:    to disable a column for editing and setting focus
//
//  PARAMETERS: zVIEW vSubtask      - View to the Dialog window
//              zCPCHAR  cpcCtrlTag - the controls tag
//              zSHORT nIndex       - index of the column to be locked
//                                    if -1 the current col
//              zBOOL bLock         - TRUE to lock, FALSE to unlock a column
//
/////////////////////////////////////////////////////////////////////////////
//./END + 5
zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_LockColumn( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zSHORT  nIndex,
                     zBOOL   bLock )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   zSHORT nRC = 0;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
      LPGRID pGrid = DYNAMIC_DOWNCAST( ZWebGrid, pzma->m_pCtrl );
      if ( pGrid )
      {
         nRC = pGrid->LockColumn( nIndex, bLock );
      }
      else
      {
         TraceLineS( "drvr - Invalid control type for ZWEBGRID_LockColumn ", cpcCtrlTag );
         nRC = -1;
      }
   }
   else
      nRC = -1;

   return( nRC );
}

//./ ADD NAME=ZWEBGRID_SetCellData
// Source Module=zdctlo.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       ZWEBGRID_SetCellData
//                                           07/13/2001 Modified: 07/14/2001
//  PURPOSE:    set data to a cell specified by row and column index
//
//  PARAMETERS: zVIEW vSubtask      - View to the Dialog window
//              zCPCHAR  cpcCtrlTag - the controls tag
//              zCPCHAR  pchData    - pointer to a buffer containing the new value
//              zLONG lRowNbr       - the row index of the cell
//                                    if -1 the current row
//              zLONG lColNbr       - the column index of the cell
//                                    if -1 the current col
//
/////////////////////////////////////////////////////////////////////////////
//./END + 6
zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetCellData( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zCPCHAR pchData,
                      zLONG   lRowNbr,
                      zLONG   lColNbr )
{
   CString strErrorMessage;
   zSHORT nRC = 0;
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
      LPGRID pGrid = DYNAMIC_DOWNCAST( ZWebGrid, pzma->m_pCtrl );
      if ( pGrid )
      {
         nRC = pGrid->SetCellData( pchData, lRowNbr, lColNbr );
      }
      else
      {
         TraceLineS( "drvr - Invalid control type for TG_SetCellData ", cpcCtrlTag );
         nRC = -1;
      }
   }

   return( nRC );
}

//./ ADD NAME=ZWEBGRID_GetCellData
// Source Module=zdctlo.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ZWEBGRID_GetCellData
//                                           07/13/2001 Modified: 07/14/2001
//  PURPOSE:    retrieve data of a cell specified by row and column index
//
//  PARAMETERS: zVIEW vSubtask      - View to the Dialog window
//              zCPCHAR cpcCtrlTag  - the controls tag
//              zPCHAR pchData      - pointer to a buffer getting the current value
//              zLONG lMaxLth       - maximum length of return buffer
//              zLONG lRowNbr       - the row index of the cell
//                                    if -1 the current row
//              zLONG lColNbr       - the column index of the cell
//                                    if -1 the current col
//
/////////////////////////////////////////////////////////////////////////////
//./END + 6
zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_GetCellData( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zPCHAR  pchData,
                      zLONG   lMaxLth,
                      zLONG   lRowNbr,
                      zLONG   lColNbr )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   zSHORT nRC = 0;

   if ( pchData && GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
      *pchData = 0;

      // check for Web Environment
      // If we are running in the web pzma->m_pCtrl is a ZWebGrid Instance
      LPGRID pGrid = DYNAMIC_DOWNCAST( ZWebGrid, pzma->m_pCtrl );
      if ( pGrid )
      {
         nRC = pGrid->GetCellData( pchData, lMaxLth, lRowNbr, lColNbr );
      }
      else
      {
         TraceLineS( "drvr - Invalid control type for GetCellData ", cpcCtrlTag );
         nRC = -1;
      }
   }

   return( nRC );
}

//./ ADD NAME=ZWEBGRID_GetActiveCell
// Source Module=zdctlo.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       ZWEBGRID_GetActiveCell
//                                           07/13/2001 Modified: 07/14/2001
//  PURPOSE:
//
//  PARAMETERS: zVIEW vSubtask      - View to the Dialog window
//              zCPCHAR  cpcCtrlTag - the controls tag
//              zPLONG lRowNbr      - pointer to a long for returning the current row
//              zPLONG lColNbr      - pointer to a long for returning the current column
//
/////////////////////////////////////////////////////////////////////////////
//./END + 5
zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_GetActiveCell( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zPLONG  lRowNbr,
                        zPLONG  lColNbr )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   zSHORT nRC = 0;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
      // check for Web Environment
      // If we are running in the web pzma is a ZWebGrid Instance
      LPGRID pGrid = DYNAMIC_DOWNCAST( ZWebGrid, pzma->m_pCtrl );
      if ( pGrid )
      {
         nRC = pGrid->GetActiveCell( lRowNbr, lColNbr );
      }
      else
      {
         TraceLineS( "drvr - Invalid control type for TG_GetActiveCell ", cpcCtrlTag );
         nRC = -1;
      }
   }

   return( nRC );
}

//./ ADD NAME=ZWEBGRID_SetActiveCell
// Source Module=zdctlo.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       ZWEBGRID_SetActiveCell
//                                           07/13/2001 Modified: 07/14/2001
//  PURPOSE:    Sets the input focus to a cell specified by row and column index
//
//  PARAMETERS: zVIEW vSubtask     - View to the Dialog window
//              zCPCHAR cpcCtrlTag - the controls tag
//              zLONG lRowNbr      - the Row of the cell where the input
//                                   focus has to be set ...
//                                   if -1 the current row stays active
//              zLONG lColNbr      - the Column of the cell where the input
//                                   focus has to be set ...
//                                   if -1 the current col stays active
//
/////////////////////////////////////////////////////////////////////////////
//./END + 5
zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetActiveCell( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zLONG   lRowNbr,
                        zLONG   lColNbr )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   zSHORT nRC = 0;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
      LPGRID pGrid = DYNAMIC_DOWNCAST( ZWebGrid, pzma->m_pCtrl );
      if ( pGrid )
      {
         nRC = pGrid->SetCurrentCell( lRowNbr, lColNbr );
      }
      else
      {
         TraceLineS( "drvr - Invalid control type for TG_SetActiveCell ", cpcCtrlTag );
         nRC = -1;
      }
   }

   return( nRC );
}

//./ ADD NAME=ZWEBGRID_EnableAutosort
// Source Module=zdctlo.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ZWEBGRID_EnableAutosort
//                                           07/13/2001 Modified: 07/14/2001
//  PURPOSE:    Enables or disables Autosort functionality
//
//  PARAMETERS: zVIEW vSubtask      - View to the Dialog window
//              zCPCHAR cpcCtrlTag  - the controls tag
//              zBOOL propVal       - TRUE to enable Autosort otherwise FALSE
//
/////////////////////////////////////////////////////////////////////////////
//./END + 4
zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_EnableAutosort( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         BOOL    propVal )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   zSHORT nRC = 0;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
      // check for Web Environment
      // If we are running in the web pzma->m_pCtrl is a ZWebGrid Instance
      LPGRID pGrid = DYNAMIC_DOWNCAST( ZWebGrid, pzma->m_pCtrl );
      if ( pGrid )
      {
         nRC = pGrid->EnableAutosort( propVal );
      }
      else
      {
         TraceLineS( "drvr - Invalid control type for TG_SetActiveCell ", cpcCtrlTag );
         nRC = -1;
      }
   }

   if ( nRC == 1 )
      SetFocusToCtrl( vSubtask, cpcCtrlTag );

   return( nRC );
}

//./ ADD NAME=ZWEBGRID_SetCheckBoxTranslation
// Source Module=zdctlo.cpp
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       ZWEBGRID_SetCheckBoxTranslation
//                                           07/13/2001 Modified: 07/14/2001
//  PURPOSE:     Defines Translation strings for a checked and unchecked
//               Checkbox in a grid it returns
//                 -1 if the control could not be located
//                 -2 if column index is out of range
//                 -3 if Checked/uncecked values are eqaul
//
//  PARAMETERS: zVIEW vSubtask     - View to the Dialog window
//              zCPCHAR cpcCtrlTag - the controls tag
//              zSHORT nColumn     - ColumnIndex of the column that
//                                   that displays a checkbox
//              zCPCHAR cpcTRUE    - String that is assigned to the entity/
//                                   attribute if the checkbox is checked
//              zCPCHAR cpcFALSE   - String that is assigned to the entity/
//                                   attribute if the checkbox is unchecked
//
/////////////////////////////////////////////////////////////////////////////
//./END + 6
zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetCheckBoxTranslation( zVIEW   vSubtask,
                                 zCPCHAR cpcCtrlTag,
                                 zSHORT  nColumn,
                                 zCPCHAR cpcTRUE,
                                 zCPCHAR cpcFALSE )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   zSHORT nRC = 0;

   if ( GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, cpcCtrlTag ) == 0 )
   {
      // check for Web Environment
      // If we are running in the web pzma->m_pCtrl is a ZWebGrid Instance
      LPGRID pGrid = DYNAMIC_DOWNCAST( ZWebGrid, pzma->m_pCtrl );
      if ( pGrid )
      {
         nRC = pGrid->SetCheckBoxTranslation( nColumn, cpcTRUE, cpcFALSE );
      }
      else
      {
         TraceLineS( "drvr - Invalid control type for TG_SetCheckBoxTranslation ", cpcCtrlTag );
         nRC = -1;
      }
   }

   return( nRC );
}

zSHORT
ZWebGrid::FireVirtualEvent(zLONG lEventId)
{

   return( ((zSHORT) ProcessImmediateEvent( this, lEventId, 0 )) );
}

//./ ADD NAME=ZWebGrid::CreateRowFromXRA
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGrid::CreateRowFromXRA
//                                            1/30/2002 Modified
//  PURPOSE:    Process the creation of a new row
//                1. Fire the before insert event
//                2. Position to the last entity which should be the new one
//                3. create a new row instance and append it to the list of rows
//                4. make new row the current row
//                5. Fire the after insert event
//
//  PARAMETERS:
//
//  RETURN    : pointer to the new row
/**************************************************************************/
//./END + 2
LPGRIDROW
ZWebGrid::CreateRowFromXRA( )
{
   zVIEW vApp = 0;
   LPGRIDROW lpRow = 0;
   zLONG lRC = 0;

   m_bInsertMode = TRUE;

   lRC = FireVirtualEvent( DISPID_BeforeInsert );

   // a return( code less than 0 will cancel tha whole process
// if ( nRC != 0 && nRC != zNO_APPLICATION_EVENT )
   if ( lRC != zNO_APPLICATION_EVENT && (zSHORT) zLOUSHORT( lRC ) < 0 )
   {
      m_bInsertMode = FALSE;
      return( lpRow );
   }

   if ( GetViewByName( &vApp, m_csListView,
                       GetDialogView( ), zLEVEL_ANY ) > 0 )
   {
      // Set Cursor to the entity created by usercode
      lRC = SetEntityCursor( vApp, m_csListEntityName, 0,
                             m_ulFlag | zPOS_LAST, 0, 0, 0, 0,
                             m_csScopeEntityName, 0 );
      if ( lRC >= zCURSOR_UNCHANGED )
      {
         zULONG ulEntityKey = GetEntityKey( vApp, m_csListEntityName );
         lpRow = AddRow( ulEntityKey, vApp );
         SetCurrentRow( ulEntityKey );
      }
   }

   lRC = FireVirtualEvent( DISPID_AfterInsert );

   m_bInsertMode = FALSE;
   return( lpRow );
}

//./ ADD NAME=ZWebGrid::DeleteRowFromXRA
// Source Module=zdctlvwg.cpp
//**************************************************************************/
//
//  ENTRY:       ZWebGrid::DeleteRowFromXRA
//                                            1/31/2002 Modified
//  PURPOSE:    delete a row from row set
//              1. Synchronize cursor settings grid vs oi
//              2. fire before delete event
//              3. remove row from row set
//              4. fire after delete event
//
//  PARAMETERS: LPGRIDROW lpRow - pointer to the row that is about to be deleted
//
//  RETURN    :
/**************************************************************************/
//./END + 2
void
ZWebGrid::DeleteRowFromXRA( LPGRIDROW lpRow )
{
   zVIEW vApp = 0;
   zLONG lRC = 0;

   if ( GetViewByName( &vApp, m_csListView,
                       GetDialogView( ), zLEVEL_ANY ) > 0 )
   {
      // position to the entity that is about to be deleted
      zULONG ulEntityKey = lpRow->GetEntityKey( );
      lRC = SetEntityCursor( vApp,
                             GetListEntity( ),
                             0,
                             zQUAL_ENTITYKEY | zPOS_FIRST,
                             (zCPVOID) &ulEntityKey,
                             0, 0, 0, 0, 0 );

      lRC = FireVirtualEvent( DISPID_BeforeDelete );

      // A return( code less than 0 will cancel tha whole process.
   // if ( nRC != 0 && nRC != zNO_APPLICATION_EVENT )
      if ( lRC != zNO_APPLICATION_EVENT && (zSHORT) zLOUSHORT( lRC ) < 0 )
      {
         return;
      }
      else
      {
         m_mapRowSet.RemoveKey( lpRow->GetIndex() );
         delete( lpRow );
      }

      lRC = FireVirtualEvent( DISPID_AfterDelete );
   }
}
