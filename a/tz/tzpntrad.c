//
// MODULE NAME:  TZPNTRAD  -  Painter dialog operations
// DESCRIPTION:  This is the c++ file which contains the painter
//               dialog operations
/////////////////////////////////////////////////////////////////////////////
// *  Copyright (c) 1998 - 2016 QuinSoft, Inc. All rights reserved. Confidential *
// * and Proprietary material subject to license - do not reproduce or      *
// * disclose.  This material is an unpublished work and is considered a    *
// * trade secret belonging to the copyright holder.                        *
/////////////////////////////////////////////////////////////////////////////
//  AUTHOR:  Gig Kirk
//  DATE:    9/30/92
//  API:     MicroSoft foundation classes and Windows 3.1 SDK
//  ENVIRONMENT: Windows 3.1
//
//  LAST MESSAGE ID: PN00223
//

/*
CHANGE LOG
2010.03.12 KJS
   Added operation GenerateJSPJava
   Added operation GenerateAllJSPJava
2003.06.19 DonC
   Added operation GenerateJSP
2003.01.23 DKS
   Added check in MigrateDialogs for a couple of control events ...
   EditChange, ComboEditChange and ComboSelect events.
2002.08.15 RR
   Replace Name of Zeidon Online Manuals by DEFINES
2002.08.09 BL
   avoid "ViewIsReadOnly" if a meta is not checked out.
2002.07.25
   make sure that dialog is checked out when migrating (<strg> + <alt> + 'M'). Correct bug on negative values.
2002.06.24 BL
   Bugfix for remapping after remove Registered View
2002.06.10    BL    R55735
   Target Specification: if TargetExecutable not selected, set selection
   for current Meta
2002.04.29    FH
   unset the readonly state, because to get rid of errors on window close for a non-checked-out dialog.
2001.09.04    DKS   Z10
   Removed compiler warning.
2001.06.25    DKS   Z10
   Changed MigrateDialogs to reposition ctrls in X and Y direction.
2001.06.11    BL
   If switch Project (LPLR) load PPE from the new LPLR
2001.05.08    DKS   Z10
   Added capability to Migrate and to Painter to proportionally resize
   all controls in X or Y direction in a Window/Dialog.
2001.05.01  DKS
   MigrateDialogs enhanced to permit save of all PWDs.
2001.04.19    DKS   Z10
   Added capability to Migrate and to Painter to proportionally resize
   all controls in a Window/Dialog.
2001.02.28    BL    WEB
   Bugfix Generate XRA
2001.02.28    BL    TREE and Repository
   Tree Control in Control List: if double click on tree Item, do not expand or
   collapse this Item
   If Dialog not checked out, disable Controls for update
2001.02.21    BL    WEB
   Generate XRA's from all Dialogs
2001.02.12    BL    R54697
   improve handling of return code from InitializeLPLR
2001.01.05    DKS   Z10
   Changed MigrateDialogs to permit change to new Tab event.
2001.01.05    DKS   Z10
   Changed Show/Hide Tabstops menu.
2001.01.04    DKS   Z10
   Add a flag to the Window update dialog to permit the specification
   of whether or not to select the first (edit or MLE) control on a window
   on initial entry to the window.
2000.12.29    BL    Z10   DKS
   Bugfix Control List for use key down and key up in Tree Control
   ( do not use operation SetFocusToCtrl )
2000.12.27    BL    Z10   F50709
   Modified SetHotkey: do not accept a Shortcut without assigning a key
2000.12.06    BL    Z10   R54308
   Modified CleanupActions: do not delete a Shortcut Action
2000.10.30    RG  Z2000
   GetViewByName: for parameter zLEVEL_TASK changed View --> 0
2000.10.25    SR  Z2000 Size of path variables
   - Modified size of szFileSpec1 and szFileSpec2 in function MigrateDialog
     and szSourceFileName and szNewFileName in function
    zwfnTZPNTRAD_SaveAsCopyFiles because size of attributes ExecDir, MetaSrcDir
    and PgmSrcDir has been changed to 254 in datamodel.
   - Adjust the size of messagetext variables.
   - Replace fix size of extension arrays (4) with zMAX_EXTENSION_LTH in function
     zwfnTZPNTRAD_SaveAsGetFilename .
2000.10.08    BL     Z10
   Bugfix Control List
2000.09.23    BL     Z10
   Bugfix Control List
2000.09.21    BL     Z10  RAD 53746
   Added Functions for Menu Format in Dialog Painter (=Format Controls)
2000.09.18  Bl    Z10
   Modified zwfnTZPNTRAD_SaveAsCheckFileName for check duplicate
   Source File Names
   Modified zwfnTZPNTRAD_SaveAsSetSourceName, zwTZPNTRAD_SaveAsSetDefaults
   for bugfix generate Source File Name
2000.09.03  BL    Z10   TB 50416, R53234
   Modified MergeCtrls for copy many Control
2000.09.01  BL    Z10   TB 5100
   Bugfix Toolbar: Completely maintained
   Modified zwTZPNTRAD_SaveAs for set new Dialog Name in Action
2000.08.15  BL    Z10  Repository and Tools
   Completely maintained Dialog Tool.
   If Dialog not checked out, disable all functions for update.
2000.07.10  BL    Z10   Save as with Source Files (TB 53236, 51337, 51037)
   Added zwTZPNTRAD_SaveAsKeepCurrentDesc, zwfnTZPNTRAD_SaveAsSourceFiles,
   zwfnTZPNTRAD_SaveAsGetFileName, zwfnTZPNTRAD_SaveAsCheckStatus,
   zwfnTZPNTRAD_SaveAsCheckName, zwfnTZPNTRAD_SaveAsCheckFileName,
   zwfnTZPNTRAD_SaveAsCopyFiles, zwfnTZPNTRAD_SaveAsSetSourceName and
   modified all save as Functions for copy source files
   Insert define for Action after SaveAS
2000.07.07  DKS   Z10
   CtrlList permits update of more attributes.  MergeCtrls verifies that a
   target "Control" entity exists prior to performing the SetViewToSubobject.
2000.06.26  DKS   Z10
   Force PASTED/CLONED controls to have unique tag.
2000.06.05  DKS   Z10
   Permit global change from Calendar ctrl back to edit.
   Send in flag to force reload of task view for LPLR.
2000.06.05  BL    Z10
   Modified zwTZPNTRAD_PostBuild: Using Ctrl+E to edit a dialog, the Painter
   does not get the appropriate title
2000.05.24  BL    Z10
   remove warning
2000.05.12  BL    Z10
   Replace SysGetPointerFromHandle througt SysGetPointerFromHandle
2000.05.09  BL
   Remove warnings
2000.05.08  BL    Z10
   Modified OpenDialogFile: does not ask for save after open dialog (TZWDLGSO
   is updated after activate througt attribute derived operations in LOD)
2000.05.04  BL    Z10   Repository and Tools
   Modified zwTZPNTRAD_PreBuild, zwTZPNTRAD_ResetProfileXFER, ExitDialog,
   SwitchLPLR and added zwfnTZPNTRAD_CheckActionAfterSaveAs, zwTZPNTRAD_NewDialog,
   zwTZPNTRAD_OpenDialog, AskForSave:
   if Dialog not checked out and user change this Dialog, then zeidon
   call the window "Save Dialog as". We save the action after Save as in
   the View TZSAVEAS (for example: Create new Dialog or Open an other Dialog
   or Switch Project or Exit Dialog Tool)
2000.05.03  BL    Z10   Repository and Tools
   Added zwTZPNTRAD_CheckNameForCheckOut and modified zwTZPNTRAD_SaveAsDialog
   for set check out state in window "Save as"
   Modified zwTZPNTRAD_PostBuild and EnablePainterWindows for set check
   out state in main window
   Modified RetrieveMetaList for set cursor on current dialog
   Modified zwTZPNTRAD_InitMenuItems: if dialog not checked out, disable
   menu item "Save"
   Added zwTZPNTRAD_Check_CheckoutStatus for set check out state in window
   "Open Dialog" and enable/disable Button "Delete"
2000.04.12  DKS   Z10   Migration
   Permit save of XWD based on internal PWD/XWD Timestamp comparison.
   Permit change from EditBox to Calendar based on Date and DateTime Domains.
2000.01.26  BL    Z10   Bug TB916
   Modified SwitchLPLR: drop View for Dialog list in Window ACTION DETAIL
2000.01.14  BL    Z10
   Modified LIST_MENU_OK for bug by SystemClose
2000.01.13  BL    Z10   PPE
   Modified zwTZPNTRAD_PreBuild, EnablePainterWindows for new PPE Handling:
   if PPE does not exists in Project Directotry, then load PPE from Zeidon
   Bin/Sys - Directory
*/

#define _MT 1

#define _NOANCHOR
#include <zstdafx.h>
#define zGLOBAL_DATA
#define KZOESYS_INCL
#define zNO_KZOEINCO    // to get the correct operation thru zGET_PTR
#define ZDRAPP_CLASS AFX_EXT_CLASS
#include "..\zdr\Zdr.h"
#include "..\zdr\TzCtl.h"

#include "KZOENGAA.H"
#include "stdlib.h"
#include <ctype.h>
#include <string.h>

#include "tz__oprs.h"
#include "tzlodopr.h"

#ifdef __cplusplus
extern "C"
{
#endif

// We need to define MutexInfo as a dummy typedef.  DO NOT TRY TO USE THIS!
typedef long MutexInfo;

#include "tzctlopr.h"
#include "ZeidonOp.H"

#pragma pack( 1 )
#include <tzwdlgso.hst>
#pragma pack( )

typedef zSHORT (POPERATION zPAINTERCALL)( zSHORT, zVIEW, zPVOID,
                                          zVIEW, zPCHAR, zLONG );

typedef zSHORT (POPERATION zFARPROC_DUP_CHECK)( zVIEW vSubtask,
                                                zVIEW vSrcDialog,
                                                zLONG lFlags );

zOPER_EXPORT zLONG  OPERATION
fnPainterCall( zSHORT nMsg,    zVIEW vSubtask,
               zVIEW  vDialog, zPCHAR szParm, zLONG lMaxLth );

zOPER_EXPORT zSHORT OPERATION
AskForSave( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
oTZPNTRAD_CloneOption( zVIEW  NewWO,
                       zVIEW  NewW,
                       zVIEW  OrigWO,
                       zVIEW  OrigW,
                       zLONG  lPosition,
                       zVIEW  vSubtask );

zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
zwTZPNTRAD_CreateWindowList( zVIEW vSubtask,
                             zVIEW vNewDialog,
                             zVIEW vNewDialogL );
zOPER_EXPORT zSHORT OPERATION
CleanupActions( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
CleanupOperations( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
PrebuildWindowList( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
DisplayWindowList( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SetDefaultWindow( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
ExitDialog( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
OpenDialogFile( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SaveDialogFile( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
UpdateWindowFromList( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_InitModalSubwindow( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
NewDialogFile( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
NewWindow( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
DlgCloneWindow( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_VerifyParmsOnType( zVIEW vSubtask );

//  *** Temp only ***
zOPER_EXPORT zSHORT OPERATION
DeleteWindow( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
DeleteWindowFromList( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
EnablePainterWindows( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
DisablePainterWindows( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
NextAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
PrevAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
NewAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
DeleteAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
ActionAdd( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
ActionUpdate( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
ActionDeleteFromList( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SortActionsForWindow( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
WndSelectAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
WndRemoveAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
OptSelectAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
DeleteDialog( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SortByName( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SortByDate( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
RetrieveMetaList( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SwitchLPLR( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MoveOptions( zVIEW vSubtask, zVIEW NewWO,
                      zVIEW OrigWO, zSHORT nPosition );

zOPER_EXPORT zSHORT OPERATION
ChangeSelectedControls( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SystemMinimize( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SystemRestore( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
NewHotkey( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
ShowHotkey( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SetHotkey( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
ShowTabbing( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
RemoveTabbing( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
ClearTabbingDisplay( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_TransferToEditor( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
LIST_ACT_AddAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
LIST_ACT_SelectAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
wTZOPRUSD_SetUpTZOPRUSO_View( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_RefreshAllSubwindows( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_RefreshAllWindowLists( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
ActionListTransfer( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
LIST_ACT_PostBuildInit( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
wTZOPRUSD_AddSourceFile( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
LIST_ACT_UpdateAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
wTZOPRUSD_GoToUpdateOperation( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
LIST_ACT_DeleteAction( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
wTZOPRUSD_DeleteSelectedOperat( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
wTZOPRUSD_DeleteSourceFile( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_SaveAs( zVIEW   vSubtask,
                   zPCHAR  szDialogName);

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_InitMenuItems( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_EnableMenuItems( zVIEW    vSubtask,
                            zPCHAR   szListname,
                            zPCHAR   szEntityName,
                            zPCHAR   szMenuItem,
                            zPSHORT  pnEnableUpdate,
                            zPSHORT  pnEnableDelete );

zOPER_EXPORT zSHORT OPERATION
zwTZPNCTAD_DeleteAllActions( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_EnableMenuDeleteAll( zVIEW   vSubtask,
                                zPCHAR  szEntityName );

zOPER_EXPORT zSHORT OPERATION
wTZOPRUSD_CheckExistsSourceFile( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
SetTitleWithCheckOutState( zVIEW   vSubtask,
                           zPCHAR  szToolname,
                           zPCHAR  szDialogname,
                           zVIEW   vToolView,
                           zPCHAR  szEntityname,
                           zLONG   lType );

zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
zwTZPNTRAD_LoadEventPopups( zVIEW vSubtask,
                            zPCHAR szActionNameForUpdate,
                            zPCHAR szActionNameForNew,
                            zPCHAR szActionNameForSelect,
                            zPCHAR szActionNameForRemove,
                            zPCHAR szActionNameForEdit,
                            zPCHAR szPopupName );

zOPER_EXPORT zSHORT OPERATION
OPT_UPD_OK( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
OPT_UPD_Init( zVIEW vSubtask );

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
OPT_UPD_DisableActionButton( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_SetSaveAsName( zVIEW vSubtask );

zSHORT
zwfnTZPNTRAD_CheckActionAfterSaveAs( zVIEW  vSubtask );


zSHORT
zwfnTZPNTRAD_SaveAsSetSourceName( zVIEW  vSubtask,
                                  zVIEW  vSaveAs,
                                  zVIEW  vDialogData,
                                  zSHORT nIndex );

zSHORT
zwfnTZPNTRAD_SaveAsCopyFiles( zVIEW    vSubtask,
                              zVIEW    vTZWINDOWL,
                              zVIEW    vSaveAs );

zSHORT
zwfnTZPNTRAD_SaveAsCheckFileName( zVIEW    vSubtask,
                                  zVIEW    vSaveAs );

zSHORT
zwfnTZPNTRAD_SaveAsCheckName( zVIEW    vSubtask,
                              zVIEW    vSaveAs,
                              zPCHAR   szOutName );

zSHORT
zwfnTZPNTRAD_SaveAsCheckStatus( zVIEW    vSubtask,
                                zVIEW    vTZDIALOGS,
                                zPCHAR   pchOutName );

zSHORT
zwfnTZPNTRAD_SaveAsGetFileName( zVIEW  vTaskLPLR,
                                zVIEW  vView,
                                zPCHAR pchAttribute,
                                zPCHAR pchSourceFileName );

zSHORT
zwfnTZPNTRAD_SaveAsSourceFiles( zVIEW   vSubtask,
                                zVIEW   vNewDialog,
                                zVIEW   vOldDialog );

zSHORT
zwfnTZPNTRAD_Load_PPE( zVIEW vSubtask );

void
CtrlList_LoadDetailWindow( zVIEW vSubtask,
                           zVIEW vPE,
                           zSHORT IsDoubleClick );

zSHORT
zwfnTZPNTRAD_DisableMenuForError( zVIEW vSubtask,
                                  zBOOL bEnable );

//#include <afxcoll.h>
//#include <afxwin.h>

zSHORT
zwfnTZPNTRAD_Load_PPE( zVIEW vSubtask )
{
   zVIEW   vMetaList;
   zVIEW   vTZPESRCO;
   zSHORT  nRC;

   if ( GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK ) > 0 )
      return( 0 );

   RetrieveViewForMetaList( vSubtask, &vMetaList, zREFER_PENV_META );
   nRC = LoadZeidonPPE( vSubtask, &vTZPESRCO, zREFER_PENV_META, vMetaList,
                        "Dialog Maintenance",
                        "Painter cannot be started.");

   if ( nRC < 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, 0, 0 );
      return( -16 );
   }

   if ( SetCursorFirstEntityByInteger( vTZPESRCO, "ControlDef",
                                       "Key", 1000, 0 ) >= 0 )
   {
      SetNameForView( vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK );
      DropView( vMetaList );
   }
   else
   {
      MessageSend( vSubtask, "PN00201", "Dialog Maintenance",
                   "Invalid Presentation Environment!\n"
                   "New PPE required.  Painter exiting.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, 0, 0 );
      return( -16 );
   }

   return( 0 );
}

void
fnCreateMappingEntities( zVIEW vSubtask, zVIEW vDialog )
{
// zPCHAR   pchLOD_Name;
// zPCHAR   pchEntityName;
// zPCHAR   pchAttributeName;
   zVIEW    vLOD;
   zVIEW    vPainter;
   zVIEW    vTZZOVEAO;
   zVIEW    vCM_List;
   zLONG    lZKey;
   zSHORT   nRC;

   GetViewByName( &vPainter, "TZPNMWIN", vSubtask, zLEVEL_TASK );
   if ( GetCtrlState( vPainter, "ControlBar", zCONTROL_STATUS_VISIBLE ) <= 0 ||
        GetViewByName( &vTZZOVEAO, "TZZOVEAO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      return;
   }

   TraceLineS( "In fnCreateMappingEntities",
               " ============== DOING WORK ==============" );

   // Drop the previous instance if it exists.
// DropObjectInstance( vTZZOVEAO );  // no ... drop it when View list changes

   ActivateEmptyObjectInstance( &vTZZOVEAO, "TZZOVEAO", vSubtask, zMULTIPLE );
   SetNameForView( vTZZOVEAO, "TZZOVEAO", vSubtask, zLEVEL_TASK );

   // Activate the LOD for the current ViewObjRef subobject.
   RetrieveViewForMetaList( vSubtask, &vCM_List, zREFER_LOD_META );

   if ( vDialog )
   {
      nRC = SetCursorFirstEntity( vDialog, "ViewObjRef", 0 );
      while ( nRC >= zCURSOR_SET )
      {
         CreateEntity( vTZZOVEAO, "ViewObjRef", zPOS_NEXT );
         SetMatchingAttributesByName( vTZZOVEAO, "ViewObjRef",
                                      vDialog, "ViewObjRef", zSET_ALL );
         CreateEntity( vTZZOVEAO, "LOD", zPOS_NEXT );
         SetMatchingAttributesByName( vTZZOVEAO, "LOD",
                                      vDialog, "LOD", zSET_ALL );
      // GetAddrForAttribute( &pchLOD_Name, vDialog, "ViewObjRef", "Name" );
         GetIntegerFromAttribute( &lZKey, vDialog, "LOD", "ZKey" );
         SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef",
                                        "CPLR_ZKey", lZKey, "" );
         ActivateMetaOI( vSubtask, &vLOD, vCM_List, zREFER_LOD_META, 0 );
         nRC = SetCursorFirstEntity( vLOD, "LOD_Entity", 0 );
         while ( nRC >= zCURSOR_SET )
         {
         // GetAddrForAttribute( &pchEntityName, vLOD, "LOD_Entity", "Name" );
         // TraceLine( "CreateMappingEntities LOD: %s   Entity Name: %s",
         //            pchLOD_Name, pchEntityName );
            CreateEntity( vTZZOVEAO, "LOD_Entity", zPOS_NEXT );
            SetMatchingAttributesByName( vTZZOVEAO, "LOD_Entity",
                                         vLOD, "LOD_Entity", zSET_ALL );
            nRC = SetCursorFirstEntity( vLOD, "LOD_Attribute", 0 );
            while ( nRC >= zCURSOR_SET )
            {
            // GetAddrForAttribute( &pchAttributeName, vLOD, "LOD_Entity", "Name" );
            // TraceLine( "CreateMappingEntities LOD: %s   Entity: %s   Attribute: %s",
            //            pchLOD_Name, pchEntityName, pchAttributeName );
               CreateEntity( vTZZOVEAO, "LOD_Attribute", zPOS_NEXT );
               SetMatchingAttributesByName( vTZZOVEAO, "LOD_Attribute",
                                            vLOD, "LOD_Attribute", zSET_ALL );

               CreateEntity( vTZZOVEAO, "ER_Attribute", zPOS_NEXT );
               SetMatchingAttributesByName( vTZZOVEAO, "ER_Attribute",
                                            vLOD, "ER_Attribute", zSET_ALL );

               nRC = SetCursorNextEntity( vLOD, "LOD_Attribute", 0 );
            }

            nRC = SetCursorNextEntity( vLOD, "LOD_Entity", 0 );
         }

         DropObjectInstance( vLOD );
         nRC = SetCursorNextEntity( vDialog, "ViewObjRef", 0 );
      }

      SetCursorFirstEntity( vDialog, "ViewObjRef", 0 );
   }

   RefreshCtrl( vPainter, "View" );
// MiSetInstanceUpdateFlag( vDialog, 0 );

// DisplayObjectInstance( vTZZOVEAO, 0, "LOD_Entity" );
}

//./ ADD NAME=OpenDialogFile
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      OpenDialogFile
//
//  PURPOSE:    To open a dialog file and paint the first window into
//              the painter
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
OpenDialogFile( zVIEW vSubtask )
{
   zVIEW       vNewDialog;
   zVIEW       vNewDialogL;
   zVIEW       vNewOptions;
   zVIEW       vMetaList;
   zVIEW       vPrevDialog;
   zVIEW       vIdleView;
   zVIEW       vTZPNTROO;
   zVIEW       vTZZOVEAO;
   LPVIEWCSR   lpViewCsr;
   LPVIEWOI    lpViewOI;
   zSHORT      nRC;

// TraceLineS( "In OpenDialogFile", "============== " );

   // Clear the painter windows.
   fnPainterCall( zMSG_DELETEALLPAINTERWINDOWS, vSubtask, 0, 0, 0 );

   // Drop the previous instance being worked on.
   if ( GetViewByName( &vPrevDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) > 0 )
      DropMetaOI( vSubtask, vPrevDialog );

   // Call configuration management to open the selected file.
   GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK );

   // If there are no W_MetaDefs, then one can't be opened.
   if ( CheckExistenceOfEntity( vMetaList, "W_MetaDef" ) != 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( 1 );
   }

   nRC = ActivateMetaOI( vSubtask, &vNewDialog, vMetaList,
                         zSOURCE_DIALOG_META, zSINGLE | zLEVEL_TASK );
   if ( nRC < 0 )
      return( nRC );

   if ( GetViewByName( &vIdleView, "__SysIdlePainter", vSubtask, zLEVEL_SYSTEM ) > 0 &&
        vIdleView == vSubtask )
   {
      DropNameForView( vIdleView, "__SysIdlePainter", vSubtask, zLEVEL_SYSTEM );
   }

   // Set the current opened file name.
   if ( GetViewByName( &vTZPNTROO, "TZPNTROO", vSubtask, zLEVEL_TASK ) >= 0 )
      SetAttributeFromAttribute( vTZPNTROO, "Palette", "OpenedFile",
                                 vMetaList, "W_MetaDef", "Name" );

   // Drop the previous instance if it exists.
   GetViewByName( &vTZZOVEAO, "TZZOVEAO", vSubtask, zLEVEL_TASK );
   if ( vTZZOVEAO )
      DropObjectInstance( vTZZOVEAO );

   // Name the view for mapping.
   SetNameForView( vNewDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );
   fnCreateMappingEntities( vSubtask, vNewDialog );

   // BL, remove update flag
   // View vNewDialog (TZWDLGSO) is updated after activate through
   // attribute derived operations in LOD)
   lpViewCsr = (LPVIEWCSR) SysGetPointerFromHandle( vNewDialog->hViewCsr );
   lpViewOI  = (LPVIEWOI) SysGetPointerFromHandle( lpViewCsr->hViewOI );
   lpViewOI->bUpdatedFile = FALSE;

   // If Dialog not checked out, set View read only ->
   // the user cannot update the values in Detail Windows.
   if ( !ComponentIsCheckedOut( vSubtask, vNewDialog, zSOURCE_DIALOG_META ) )
      SetViewReadOnly( vNewDialog );

   CreateViewFromViewForTask( &vNewDialogL, vNewDialog, 0 );
   SetNameForView( vNewDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vNewOptions, vNewDialog, 0 );
   SetNameForView( vNewOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   // If the window list modeless window is up, simply fill in the windows
   // for the list, otherwise display the first window in the dialog
   zwTZPNTRAD_CreateWindowList( vSubtask, vNewDialog, vNewDialogL );

   //BL, 1999.11.16 refresh all modeless subwindows
   zwTZPNTRAD_RefreshAllSubwindows( vSubtask );

   if ( MiGetUpdateForView( vNewDialog ) && ObjectInstanceUpdatedFromFile( vNewDialog ) )
   {
   // SysMessageBox( vNewDialog, "Open Dialog File", "Updated", -1 );
      MiSetInstanceUpdateFlag( vNewDialog, FALSE );  // it should not be updated on open
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_PreBuild( zVIEW vSubtask )
{
   zVIEW   vProfileXFER;
   zVIEW   vMetaList;
   zVIEW   vKZWDLGXO;
   zVIEW   vTaskLPLR;
   zVIEW   vSaveAs;
   zCHAR   szApplName[ 34 ];
   zCHAR   szLPLR_Name[ 33 ];
   zBOOL   bInvokedByHotkey = FALSE;

   // Get the Profile information and
   // Call configuration management to set up the default LPL.
   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   oTZ__PRFO_GetViewToProfile( &vProfileXFER, "WD", vSubtask, zCURRENT_OI );
   if ( vProfileXFER )
      SetNameForView( vProfileXFER, "ProfileXFER", vSubtask, zLEVEL_TASK );

   // Now see if the painter is being invoked by a hotkey.
   if ( GetViewByName( &vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_SYSTEM ) > 0 )
   {
//    TraceLineX( "TZPNTRAD Prebuild SysPainterHotkey: ", vKZWDLGXO );
      DropNameForView( vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_SYSTEM );
      SetNameForView( vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_TASK );
      bInvokedByHotkey = TRUE;
   }

   szLPLR_Name[ 0 ] = 0;
   if ( vKZWDLGXO )
   {
      if ( vTaskLPLR == 0 )
      {
         GetApplDirectoryFromView( szApplName, vKZWDLGXO, zAPPL_NAME, 33 );
         if ( InitializeLPLR( vSubtask, szApplName ) < 0 )
         {
            if ( bInvokedByHotkey )
            {
            // TraceLineS( "Hotkey Painter Invokation Failed ", "1" );
               ResumeFromPainter( vSubtask, 0, vKZWDLGXO );
            // SetNameForView( vKZWDLGXO, "__SysPainterHotkey", 0, zLEVEL_SYSTEM );
               DropNameForView( vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_TASK );
            }

            return( -1 );
         }
      }
   }
   else
   if ( CompareAttributeToString( vProfileXFER, "WD", "StartupLPLR_Option",
                                  "D" ) == 0 )   //default LPLR
   {
      if ( InitializeLPLR( vSubtask, "" ) < 0 )
      {
         if ( bInvokedByHotkey )
         {
         // TraceLineS( "Hotkey Painter Invokation Failed ", "2" );
            ResumeFromPainter( vSubtask, 0, vKZWDLGXO );
         // SetNameForView( vKZWDLGXO, "__SysPainterHotkey", 0, zLEVEL_SYSTEM );
            DropNameForView( vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_TASK );
         }

         return( -1 );
      }
   }
   else
   {
      GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vProfileXFER, "WD", "StartupLPLR_Name" );
      if ( InitializeLPLR( vSubtask, szLPLR_Name ) < 0 )
      {
         if ( bInvokedByHotkey )
         {
         // TraceLineS( "Hotkey Painter Invokation Failed ", "3" );
            ResumeFromPainter( vSubtask, 0, vKZWDLGXO );
         // SetNameForView( vKZWDLGXO, "__SysPainterHotkey", 0, zLEVEL_SYSTEM );
            DropNameForView( vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_TASK );
         }

         return( -1 );
      }
   }

   // Get a list of dialogs.
   if ( GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK ) < 1 )
      RetrieveViewForMetaList( vSubtask, &vMetaList, zREFER_DIALOG_META );

   SetNameForView( vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK );

   // Activate the presentation environment.
   if ( zwfnTZPNTRAD_Load_PPE( vSubtask ) < 0 )
      return( -1 );

   // If the Dialog is not checked out and user change this Dialog, then
   // Zeidon should call the window "Save Dialog as".
   // We save the action after Save as in the View TZSAVEAS (for example:
   // Create new Dialog or Open an other Dialog or Switch Project or
   // Exit Dialog Tool)
   if ( GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK ) < 0 )
   {
      ActivateEmptyObjectInstance( &vSaveAs, "TZSAVEAS", vSubtask, zSINGLE );
      SetNameForView( vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK );
      CreateEntity( vSaveAs, "ActionAfterSaveAS", zPOS_AFTER );
   }

   SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                            zNoActionAfterSaveAs );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_PostBuild( zVIEW vSubtask )
{
   zVIEW  vMetaList;
   zVIEW  vTZPNCTWO;
   zVIEW  vNewDialogL;
   zVIEW  vWindowList;
   zCHAR  szDialogName[ 33 ];
   zCHAR  szWindowName[ 33 ];
   zVIEW  vKZWDLGXO;
   zVIEW  vProfileXFER;

   // Set up the List of Dialogs
   if ( GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK ) >= 0 )
      SortByDate( vSubtask );

   // Name the subtask associated with the main window so we can
   // set its title later.
   SetNameForView( vSubtask, "TZPNMWIN", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_TASK ) > 0 )
   {
      GetStringFromAttribute( szDialogName, zsizeof( szDialogName ), vKZWDLGXO, "Dlg", "Tag" );
      GetStringFromAttribute( szWindowName, zsizeof( szWindowName ), vKZWDLGXO, "Wnd", "Tag" );
      if ( SetCursorFirstEntityByString( vMetaList, "W_MetaDef", "Name",
                                         szDialogName, "" ) == zCURSOR_SET )
      {
         if ( OpenDialogFile( vSubtask ) == -1 )
         {
            ResumeFromPainter( vSubtask, 0, vKZWDLGXO );
            DropNameForView( vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_TASK );
            return( -1 );
         }

         GetViewByName( &vNewDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
         if ( SetCursorFirstEntityByString( vNewDialogL, "Window", "Tag",
                                            szWindowName, 0 ) >= zCURSOR_SET )
         {
            fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, szWindowName, zsizeof( szWindowName ) );
            // UpdateWindowFromList( vSubtask );
         }

         if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) > 0 )
         {
            SetWindowActionBehavior( vWindowList, zWAB_ReturnToParent |
                                     zWAB_ProcessImmediateReturn, 0, 0 );
         }
      }
      else
      {
         // Transfer to the open dialog window
         if ( vMetaList )
            SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow |
                                     zWAB_ProcessImmediateAction,
                                     "TZPNTRAD", "DLG_OPEN" );
      }

      // Set window Title with check out state
      GetViewByName( &vNewDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
      SetTitleWithCheckOutState( vSubtask, "Dialog Maintenance", "TZWINDOWL",
                                  vNewDialogL, "Dialog", zSOURCE_DIALOG_META );
   }
   else
   {
      GetViewByName( &vNewDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

      // Set window Title with check out state
      SetTitleWithCheckOutState( vSubtask, "Dialog Maintenance", "TZWINDOWL",
                                  vNewDialogL, "Dialog", zSOURCE_DIALOG_META );

#ifdef __WIN32__
   // SetOptionState( vSubtask, "WindowList", zOPTION_STATUS_ENABLED, 0 );
#else
      if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) < 1 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StartModelessSubwindow |
                                  zWAB_ProcessImmediateAction,
                                  "TZPNTRAD", "WND_LIST" );
      }
#endif

      // Transfer to the open dialog window.
      if ( vMetaList )
         SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow |
                                  zWAB_ProcessImmediateAction,
                                  "TZPNTRAD", "DLG_OPEN" );
   }

   // Initialize the TZPNCTWO work object.
   ActivateEmptyObjectInstance( &vTZPNCTWO, "TZPNCTWO", vSubtask, zSINGLE );
   CreateEntity( vTZPNCTWO, "TZPNCTWO", zPOS_AFTER );
   SetAttributeFromString( vTZPNCTWO, "TZPNCTWO", "PainterType", "D" );
   SetNameForView( vTZPNCTWO, "TZPNCTWO", vSubtask, zLEVEL_TASK );

   // Set the top entities to "Dialog" and "Window" (rather than the report
   // values of "Report" and "Page").
   fnPainterCall( zMSG_INITPAINTER, vSubtask, 0, (zPCHAR) 0, 0 );

   if ( GetViewByName( &vProfileXFER, "ProfileXFER", vSubtask, zLEVEL_TASK ) > 0 )
   {
      zLONG lFlags;
      zSHORT nState;

      lFlags = RestoreWindowPlacement( vSubtask, vProfileXFER );
      nState = (lFlags & 0x00000001) ? 1 : 0;
      SetOptionState( vSubtask, "ScrollBars", zOPTION_STATUS_CHECKED, nState );
      fnPainterCall( zMSG_SETSCROLLBARS, vSubtask, 0, (zPCHAR) nState, 0 );
      nState = (lFlags & 0x00000002) ? 1 : 0;
      SetOptionState( vSubtask, "Grid", zOPTION_STATUS_CHECKED, nState );
      fnPainterCall( zMSG_SETGRID, vSubtask, 0, (zPCHAR) nState, 0 );
      nState = (zSHORT) fnPainterCall( zMSG_RESTORE_PLACEMENT, vSubtask, 0, (zPCHAR) vProfileXFER, 0 );
//    nState = (nState == 2) ? 0 : 1;
//    SetOptionState( vSubtask, "ToolBox", zOPTION_STATUS_CHECKED, nState );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ExitDialog( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vProfileXFER;
   zVIEW  vLPLR;
   zVIEW  vKZWDLGXO;
   zVIEW  vIdlePainter;
   zVIEW  vSaveAs;
   zSHORT bSaved;
   zLONG  lFlags;
   zSHORT nRC;

   GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );

   // We are terminating.
   fnPainterCall( zMSG_TERMPAINTER, vSubtask, 0, (zPCHAR) 1, 0 );

   if ( GetViewByName( &vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_TASK ) < 1 )
      vKZWDLGXO = 0;
// else
//    TraceLineX( "TZPNTRAD ExitDialog SysPainterHotkey: ", vKZWDLGXO );

   if ( GetViewByName( &vIdlePainter, "__SysIdlePainter", vSubtask, zLEVEL_SYSTEM ) < 1 )
      vIdlePainter = 0;

   bSaved = 1;

   nRC = AskForSave( vSubtask );
   if ( nRC )
   {
      if ( nRC == 99 )
      {
         // if Dialog not checked out and user change this Dialog, then zeidon
         // call the window "Save Dialog as"
         // We save the action after Save as in the View TZSAVEAS (for example:
         // Create new Dialog or Open an other Dialog or Switch Project or
         // Exit Dialog Tool)
         if ( vSaveAs )
            SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                                     zExitToolAfterSaveAs );

         return( 0 );
      }
      else
      {
         if ( vSaveAs )
            SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                                     zNoActionAfterSaveAs );

         if ( nRC < 0 || nRC == zRESPONSE_CANCEL )
         {
            // Cancel termination.
            fnPainterCall( zMSG_TERMPAINTER, vSubtask, 0, 0, 0 );
            return( 0 );
         }

         if ( nRC == zRESPONSE_NO )
            bSaved = 0;
      }
   }

   if ( vSaveAs )
      DropMetaOI( vSubtask, vSaveAs );

   // Now save the Profile Info ...
   oTZ__PRFO_GetViewToProfile( &vProfileXFER, "WD", vSubtask, zCURRENT_OI );

   if ( GetOptionState( vSubtask, "ScrollBars", zOPTION_STATUS_CHECKED ) )
      lFlags = 0x00000001;
   else
      lFlags = 0x00000000;

   if ( GetOptionState( vSubtask, "Grid", zOPTION_STATUS_CHECKED ) )
      lFlags |= 0x00000002;

   fnPainterCall( zMSG_SAVE_PLACEMENT, vSubtask, 0, (zPCHAR) vProfileXFER, 0 );
   SaveWindowPlacement( vSubtask, vProfileXFER, lFlags );

   if ( CompareAttributeToString( vProfileXFER, "WD", "StartupLPLR_Option",
                                  "L" ) == 0 )   //set Last LPLR
   {
      GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
      if ( vLPLR )
      {
         SetAttributeFromAttribute( vProfileXFER, "WD", "StartupLPLR_Name",
                                    vLPLR, "LPLR", "Name" );
      }
   }

   oTZ__PRFO_CommitProfile( vProfileXFER );

   // Delete all the painter windows explicitly before the default CWnd
   // destructor does it and causes problems
   fnPainterCall( zMSG_DELETEALLPAINTERWINDOWS, vSubtask, 0, 0, 0 );
   if ( vKZWDLGXO == 0 || vIdlePainter )
     fnPainterCall( zMSG_DELETETOOLBAR, vSubtask, 0, 0, 0 );
   else
   if ( vDialog && bSaved == FALSE )
      DropMetaOI( vSubtask, vDialog );

   if ( vKZWDLGXO )
   {
      zVIEW vWindowList;

      if ( vDialog == 0 || bSaved == FALSE )
         SetWindowCaptionTitle( vSubtask, "Painter", "[Idle]" );

      if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) > 0 )
         RefreshWindow( vWindowList );

      if ( vIdlePainter == 0 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         SetWindowState( vSubtask, zWINDOW_STATUS_MINIMIZE, 0 );
         SetNameForView( vSubtask, "__SysIdlePainter", 0, zLEVEL_SYSTEM );
      }
      else
      {
         TerminateLPLR( vSubtask );
      }

      ResumeFromPainter( vSubtask, 0, vKZWDLGXO );
      DropNameForView( vKZWDLGXO, "__SysPainterHotkey", vSubtask, zLEVEL_TASK );
   }
   else
      TerminateLPLR( vSubtask );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AskForSave( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zBOOL  bSaveAs = FALSE;
   zCHAR  szDialogName[ 33 ];
   zCHAR  szMessageText[ 254 ];
   zSHORT nRC;

   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) <= 0 )
      return( 0 );

   fnPainterCall( zMSG_UPDATEALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
   if ( MiGetUpdateForView( vDialog ) && ObjectInstanceUpdatedFromFile( vDialog ) )
   {
      // if Dialog not checked out, then ask for save as
      if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
      {
         bSaveAs = TRUE;
         GetStringFromAttribute( szDialogName, zsizeof( szDialogName ), vDialog, "Dialog", "Tag" );
         strcpy_s( szMessageText, zsizeof( szMessageText ), "Dialog is not checked out, but Dialog '" );
         strcat_s( szMessageText, zsizeof( szMessageText ), szDialogName );
         strcat_s( szMessageText, zsizeof( szMessageText ), "' has been modified. \n\nWould you like to " );
         strcat_s( szMessageText, zsizeof( szMessageText ), "save it with differend name?" );
         nRC = MessagePrompt( vSubtask, "DM00115", "Dialog Maintenance",
                              szMessageText, zBEEP, zBUTTONS_YESNOCANCEL,
                              zRESPONSE_YES, zICON_QUESTION );
      }
      else
      {
         nRC = IssueToolMsg( vSubtask, zTOOLMSG_SAVE, zTOOL_DIALOG,
                             zREFER_DIALOG_META,
                             vDialog, "Dialog", "Tag", 0 );
      }

      if ( nRC == zRESPONSE_CANCEL )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( nRC );
      }
      else
      {
         if ( nRC == zRESPONSE_YES )
         {
            // If Dialog not checked out and user would save it, then call
            // window save Dialog as.
            if ( bSaveAs )
            {
               SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow,
                                        "TZPNTRAD", "Dialog_SaveAs" );
               return( 99 );
            }

            nRC = SaveDialogFile( vSubtask );
            if ( nRC )
            {
               SetWindowActionBehavior( vSubtask,
                                        zWAB_TerminateActionForError,
                                        0, 0 );
               return( nRC );
            }
         }
         else
            return( zRESPONSE_NO );
      }
   } // endif ( MiGetUpdateForView( vDialog ) && ...

   return( 0 );
}

//./ ADD NAME=DeleteCurrentPainterWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DeleteCurrentPainterWindow
//
//  PURPOSE:    To hide the currently selected window
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DeleteCurrentPainterWindow( zVIEW vSubtask )
{
   fnPainterCall( zMSG_DELETECURRENTPAINTERWINDOW, vSubtask, 0, 0, 0 );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zSHORT
fnGetTagPrefix( zPCHAR pchTag )
{
   char   ch = 0;
   zSHORT nCnt = 0;
   zSHORT nPos = 0;
   zSHORT k = 0;

   while ( pchTag[ nPos ] && nCnt < 2 )
   {
      if ( isupper( pchTag[ nPos ] ) )
      {
         if ( nCnt )
            pchTag[ nCnt ] = pchTag[ nPos ];

         nCnt++;
      }
      else
      if ( ch == 0 &&
           pchTag[ nPos ] != 'a' &&
           pchTag[ nPos ] != 'e' &&
           pchTag[ nPos ] != 'i' &&
           pchTag[ nPos ] != 'o' &&
           pchTag[ nPos ] != 'u' )
      {
         // May need first non-vowel lower-case character.
         ch = toupper( pchTag[ nPos ] );
      }

      nPos++;
   }

   if ( ch && nCnt < 2 )
      pchTag[ nCnt++ ] = ch;

   pchTag[ nCnt ] = 0;

   return( nCnt );
}

void
fnRecurseChangeDlgTags( zVIEW vDialog )
{
   zCHAR  szTag[ 33 ];
   zCHAR  szText[ 256 ];
   zPCHAR pch;
   zSHORT nCnt;
   zSHORT nRC;

   nRC = SetCursorFirstEntity( vDialog, "Control", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      GetStringFromAttribute( szTag, zsizeof( szTag ), vDialog, "Control", "Tag" );
      if ( szTag[ 0 ] == 0   ||
          (szTag[ 0 ] == 'T' &&
           szTag[ 1 ] == 'e' &&
           szTag[ 2 ] == 'x' &&
           szTag[ 3 ] == 't') )
      {
         GetStringFromAttribute( szText, zsizeof( szText ), vDialog, "Control", "Text" );
         if ( szText[ 0 ] )
         {
            szText[ 32 ] = 0;
            strcpy_s( szTag, zsizeof( szTag ), szText );
         }
         else
         {
            szText[ 0 ] = 0;
            if ( CheckExistenceOfEntity( vDialog, "CtrlMap" ) == 0 &&
                 CheckExistenceOfEntity( vDialog, "CtrlMapLOD_Attribute" ) == 0 &&
                 CheckExistenceOfEntity( vDialog, "CtrlMapER_Attribute" ) == 0 )
            {
               GetStringFromAttribute( szText, zsizeof( szText ), vDialog,
                                       "CtrlMapER_Attribute", "Name" );
            }
         }

         // Remove embedded spaces.
         while ( (pch = zstrchr( szText, ' ' )) != 0 )
            strcpy( pch, pch + 1 );

         if ( szText[ 0 ] )
         {
            // Give the tag a prefix.
            GetStringFromAttribute( szTag, zsizeof( szTag ), vDialog, "ControlDef", "Tag" );
            nCnt = fnGetTagPrefix( szTag );
            if ( nCnt )
               szText[ 32 - nCnt ] = 0;

            strcpy_s( szTag + nCnt, zsizeof( szTag ) - nCnt, szText );
            SetAttributeFromString( vDialog, "Control", "Tag", szTag );
         }
      }

      SetViewToSubobject( vDialog, "CtrlCtrl" );
      fnRecurseChangeDlgTags( vDialog );
      ResetViewFromSubobject( vDialog );

      nRC = SetCursorNextEntity( vDialog, "Control", 0 );
   }
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    ChangeDlgTags
//
// PURPOSE:  This function changes the (Text) tags if there is a text
//           or an attribute set for the control.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ChangeDlgTags( zVIEW vSubtask )
{
   zVIEW  vControl;
   zVIEW  vDialog;

   // Get the view.
   GetViewByName( &vControl, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( MiGetUpdateForView( vControl ) == 0 )
      return( 0 );

   CreateViewFromView( &vDialog, vControl );
   while ( ResetViewFromSubobject( vDialog ) == 0 )
   {
      // nothing to do
   }

   // Loop through all Controls.
   fnRecurseChangeDlgTags( vDialog );

   DropView( vDialog );

   // This has to be done because the control is mapped after this operation.
   while ( ResetViewFromSubobject( vControl ) == 0 )
   {
      // nothing to do
   }


   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: zwTZPNTRAD_ProfileSave
//
// PURPOSE:   Save updated Profile.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_ProfileSave( zVIEW vSubtask )
{
   zVIEW  vProfileXFER;

   oTZ__PRFO_GetViewToProfile( &vProfileXFER, "EMD", vSubtask, zCURRENT_OI );
   oTZ__PRFO_CommitProfile( vProfileXFER );

   return( 0 );
}

//./ ADD NAME=DeleteDialog
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DeleteDialog
//
//  PURPOSE:    To delete a dialog file using the config. mgmt. function
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DeleteDialog( zVIEW vSubtask )
{
   zVIEW  vMetaList;
   zSHORT nRC;

   GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK );

   /* If there are no W_MetaDefs then one can't be opened. */
   if ( CheckExistenceOfEntity( vMetaList, "W_MetaDef" ) != 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( 1 );
   }

   if ( IssueToolMsg( vSubtask, zTOOLMSG_DELETE, zTOOL_DIALOG,
                      zREFER_DIALOG_META, vMetaList, "W_MetaDef",
                      "Name", 0 ) == zRESPONSE_YES )
   {
      nRC = DeleteMetaOI( vSubtask, vMetaList, zREFER_DIALOG_META );
      SetCursorPrevEntity( vMetaList, "W_MetaDef", "" );
   }

   return( 0 );
}

//./ ADD NAME=SortByName
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SortByName
//
//  PURPOSE:    To sort the dialog list by Name.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SortByName( zVIEW vSubtask )
{
   zVIEW  vMetaList;
   zSHORT nRC;

   nRC = GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   nRC = zgSortEntityWithinParent( zASCENDING, vMetaList,
                                   "W_MetaDef", "Name", "" );

   return( 0 );
}

//./ ADD NAME=SortByDate
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SortByDate
//
//  PURPOSE:    To delete a dialog file using the config. mgmt. function
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SortByDate( zVIEW vSubtask )
{
   zVIEW  vMetaList;
   zSHORT nRC;

   nRC = GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   nRC = zgSortEntityWithinParent( zDESCENDING, vMetaList,
                                   "W_MetaDef", "LastUpdateDate", "" );

   return( 0 );
}

//./ ADD NAME=SortByDesc
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SortByDesc
//
//  PURPOSE:    To delete a dialog file using the config. mgmt. function
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SortByDesc( zVIEW vSubtask )
{
   zVIEW  vMetaList;
   zSHORT nRC;

   nRC = GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   nRC = zgSortEntityWithinParent( zASCENDING, vMetaList,
                                   "W_MetaDef", "Desc", "" );

   return( 0 );
}


/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: WND_LIST_Popup
//
// PURPOSE:   Show Popup Menu for Window List
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT int OPERATION
WND_LIST_Popup( zVIEW vSubtask )
{
   CreateTrackingPopupMenu( vSubtask, "WND_LIST_Popup", -1, 0, FALSE, FALSE );
   return( 0 );
}

//./ ADD NAME=PrebuildWindowList
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
PrebuildWindowList( zVIEW vSubtask )
{
   zVIEW vProfileXFER;

   SetNameForView( vSubtask, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vProfileXFER, "ProfileXFER", vSubtask, zLEVEL_TASK ) > 0 )
      RestoreWindowPlacement( vSubtask, vProfileXFER );

   return( 0 );
}

//./ ADD NAME=DisplayWindowList
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SetWindowList( zVIEW vSubtask )
{
   zVIEW vWindowList;

   // is the window already created ?
   if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) < 1 )
   {
      // set Check-Status for WindowList
   // SetOptionState( vSubtask, "WindowList", zOPTION_STATUS_CHECKED, 1 );

      // Start the window list modeless window
      SetWindowActionBehavior( vSubtask, zWAB_StartModelessSubwindow,
                               "TZPNTRAD", "WND_LIST" );
   }
   else
   {
      // is the window at this time hidden ?
      if ( GetWindowState( vWindowList, zWINDOW_STATUS_VISIBLE ) > 0 )
      {
         // reset Check-Status for WindowList
      // SetOptionState( vSubtask, "WindowList", zOPTION_STATUS_CHECKED, 0 );

         // Hide the Window
         SetWindowState( vWindowList, zWINDOW_STATUS_VISIBLE, 0 );
      }
      else
      {
         // reset Check-Status for WindowList
      // SetOptionState( vSubtask, "WindowList", zOPTION_STATUS_CHECKED, 1 );

         // show the Window
         SetWindowState( vWindowList, zWINDOW_STATUS_VISIBLE, 1 );
      }
   }

   return( 0 );
}

//./ ADD NAME=SetDefaultWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SetDefaultWindow( zVIEW vSubtask )
{
   zVIEW vDialog;

   if ( GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if ( CheckExistenceOfEntity( vDialog, "Window" ) == zCURSOR_SET )
      {
         if ( SetCursorFirstEntity( vDialog, "DfltWnd", 0 ) == zCURSOR_SET )
            ExcludeEntity( vDialog, "DfltWnd", zREPOS_NONE );

         IncludeSubobjectFromSubobject( vDialog, "DfltWnd",
                                        vDialog, "Window", zPOS_AFTER );
      }
   }
   return( 0 );
}

//./ ADD NAME=ClearDefaultWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
ClearDefaultWindow( zVIEW vSubtask )
{
   zVIEW vDialog;

   if ( GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if ( SetCursorFirstEntity( vDialog, "DfltWnd", 0 ) == zCURSOR_SET )
         ExcludeEntity( vDialog, "DfltWnd", zREPOS_NONE );
   }
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_CreateWindowList
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
zwTZPNTRAD_CreateWindowList( zVIEW vSubtask,
                             zVIEW vNewDialog,
                             zVIEW vNewDialogL )
{

#ifndef __WIN32__
   zVIEW       vWindowList;
#endif

   // If the window list modeless window is up, simply fill in the windows
   // for the list, otherwise display the first window in the dialog
#ifndef __WIN32__
   if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) > 0 )
   {
      RefreshCtrl( vWindowList, "ListBox1" );
      ActivateWindow( vWindowList );

      // If only one window exists in the dialog file, paint it
      if ( SetCursorFirstEntity( vNewDialogL, "Window", 0 ) == zCURSOR_SET &&
           SetCursorNextEntity( vNewDialogL, "Window", 0 ) != zCURSOR_SET )
      {
         // Paint the first window in the dialog
         SetNameForView( vNewDialogL, "TZWINDOW", vSubtask, zLEVEL_TASK );
         fnPainterCall( zMSG_CREATEZEIDONWINDOW, vSubtask, 0, 0, 0 );
      }
      else
      {
         SetWindowState( vWindowList, zWINDOW_STATUS_VISIBLE, TRUE );
      }
   }
   else
   {
      // Paint the first window in the dialog
      fnPainterCall( zMSG_CREATEZEIDONWINDOW, vSubtask, 0, 0, 0 );
   }
#else
   // If only one window exists in the dialog file, paint it
   if ( SetCursorFirstEntity( vNewDialogL, "Window", 0 ) == zCURSOR_SET &&
        SetCursorNextEntity( vNewDialogL, "Window", 0 ) != zCURSOR_SET )
   {
      // Paint the first window in the dialog
      SetNameForView( vNewDialogL, "TZWINDOW", vSubtask, zLEVEL_TASK );
      fnPainterCall( zMSG_CREATEZEIDONWINDOW, vSubtask, 0, 0, 0 );
   }
   else
   {
      zCHAR  szDlgTag[ 33 ];
      zCHAR  szWndTag[ 33 ];

      GetStringFromAttribute( szDlgTag, zsizeof( szDlgTag ), vNewDialog, "Dialog", "Tag" );
      GetProfileStr( vSubtask, "Design", szDlgTag, "..Start",
                     "Window", szWndTag, zsizeof( szWndTag ) );
      if ( szWndTag[ 0 ] &&
           SetCursorFirstEntityByString( vNewDialogL, "Window", "Tag",
                                         szWndTag, "" ) == zCURSOR_SET )
      {
         // Paint the first window in the dialog
         SetNameForView( vNewDialogL, "TZWINDOW", vSubtask, zLEVEL_TASK );
         fnPainterCall( zMSG_CREATEZEIDONWINDOW, vSubtask, 0, 0, 0 );
      }
   }

   fnPainterCall( zMSG_REFRESHWINDOWLIST, vSubtask, 0, 0, 0 );
#endif

   return( 0 );
} // zwTZPNTRAD_CreateWindowList

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_GenerateXRA
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_GenerateXRA( zVIEW vSubtask )
{
   zVIEW   vMetaList = 0;
   zVIEW   vTaskLPLR = 0;
   zVIEW   vDialog   = 0;
   zVIEW   vXRA;
   zCHAR   szDialogName[ 33 ];
   zCHAR   szMsg[ zMAX_FILESPEC_LTH + 100 ];
   zCHAR   szRemotePath[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR   szFileSpec[ zMAX_FILESPEC_LTH + 1 ];
   zSHORT  nRC;

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   SysReadZeidonIni( -1, "[Workstation]", "ExecutableRemotePath", szRemotePath, zsizeof( szRemotePath ) );
   if ( szRemotePath[ 0 ] == 0 )
      GetStringFromAttribute( szRemotePath, zsizeof( szRemotePath ), vTaskLPLR, "LPLR", "ExecDir" );

   ofnTZCMWKSO_AppendSlash( szRemotePath );

   CreateViewFromViewForTask( &vMetaList, vTaskLPLR, 0 );
   RetrieveViewForMetaList( vSubtask, &vMetaList, zREFER_DIALOG_META );

   for ( nRC = SetCursorFirstEntity( vMetaList, "W_MetaDef", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vMetaList, "W_MetaDef", "" ) )
   {
      GetStringFromAttribute( szDialogName, zsizeof( szDialogName ), vMetaList, "W_MetaDef", "Name" );
      strcpy_s( szMsg, zsizeof( szMsg ), "Generate XRA for Dialog: '" );
      strcat_s( szMsg, zsizeof( szMsg ), szDialogName );
      strcat_s( szMsg, zsizeof( szMsg ), "'." );
      MB_SetMessage( vSubtask, 1, szMsg );

      if ( ActivateMetaOI( vSubtask, &vDialog, vMetaList,
                           zREFER_DIALOG_META, zSINGLE | zLEVEL_TASK ) != 1 )

      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Could not load Dialog '" );
         strcat_s( szMsg, zsizeof( szMsg ), szDialogName );
         strcat_s( szMsg, zsizeof( szMsg ), "'." );
         MessageSend( vSubtask, "PN00219", "Dialog Maintenance", szMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }
      else
      {
         strcpy_s( szFileSpec, zsizeof( szFileSpec ), szRemotePath );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), szDialogName );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XRA" );

         ConvertDialog( vMetaList, vDialog, "", &vXRA );

         if ( vXRA )
         {
            if ( CommitOI_ToFile( vXRA, szFileSpec, zSINGLE ) != 0 )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to save XRA '" );
               strcat_s( szMsg, zsizeof( szMsg ), szRemotePath );
               strcat_s( szMsg, zsizeof( szMsg ), "'." );
               MessageSend( vSubtask, "CM00428", "Dialog Maintenance",
                            szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            }
            DropObjectInstance( vXRA );
         }

         DropMetaOI( vSubtask, vDialog );
      }
   } // endfor

   DropView( vMetaList );
   MB_SetMessage( vSubtask, 1, "" );

    return( 0 );
} // zwTZPNTRAD_GenerateXRA

//./ ADD NAME=SaveDialogFile
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SaveDialogFile
//
//  PURPOSE:    To save a dialog file and call the conversion function
//              to create an executable dialog the driver can process
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SaveDialogFile( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vDialogConvert;

   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) < 1 )
      return( -1 );

   fnPainterCall( zMSG_UPDATEALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
   CreateViewFromViewForTask( &vDialogConvert, vDialog, 0 );
   AssignZKeyToMetaOI( vSubtask, vDialogConvert, zSOURCE_DIALOG_META, 0 );

   ResetView( vDialogConvert );

   SetNameForView( vSubtask, "TZCM_DialogSubtask", vSubtask, zLEVEL_TASK );

   if ( CommitMetaOI( vSubtask, vDialogConvert, zSOURCE_DIALOG_META ) < 0 )
   {
      MessageSend( vSubtask, "PN00219", "Dialog Maintenance",
                   "Unable to save Dialog",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -2 );
   }

   DropView( vDialogConvert );

   return( 0 );
}

//./ ADD NAME=SaveAllDialogs
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SaveAllDialogs
//
//  PURPOSE:    To save a dialog file and call the conversion function
//              to create an executable dialog the driver can process
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SaveAllDialogs( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vLPLR;
   zSHORT nRC;

   RetrieveViewForMetaList( vSubtask, &vLPLR, zSOURCE_DIALOG_META );
   nRC = SetCursorFirstEntity( vLPLR, "W_MetaDef", "" );
   while ( nRC >= zCURSOR_SET )
   {
      ActivateMetaOI( vSubtask, &vDialog, vLPLR, zSOURCE_DIALOG_META, zSINGLE );
      SetCursorFirstEntity( vDialog, "Window", "" );
      CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
      DropView( vDialog );
      nRC = SetCursorNextEntity( vLPLR, "W_MetaDef", "" );
   }

   return( 0 );
}

//./ ADD NAME=UpdateWindowFromList
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UpdateWindowFromList
//
//  PURPOSE:    To update a window from the list of windows
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UpdateWindowFromList( zVIEW vSubtask )
{
   zVIEW  vDialogList;
   zCHAR  szTag[ 33 ];
   zSHORT nRC;

   // Get the view to the window list
   if ( GetViewByName( &vDialogList, "TZWINDOWL", vSubtask, zLEVEL_TASK ) < 1 )
      return( -1 );
   if ( CheckExistenceOfEntity( vDialogList, "Window" ) != zCURSOR_SET )
      return( -1 );

   SetNameForView( vDialogList, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // Get Address of window tag and see if there is an active painter
   // for the window
   fnPainterCall( zMSG_GETACTIVEWINDOWNAME, vSubtask, 0, szTag, zsizeof( szTag ) );
   if ( szTag[ 0 ] == 0 )
      return( -1 );

   nRC = (zSHORT) fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, szTag, zsizeof( szTag ) );
   return( 0 );
}

//./ ADD NAME=SelectWindowFromList
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SelectWindowFromList
//
//  PURPOSE:    To Select a window from the list of windows
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SelectWindowFromList( zVIEW vSubtask )
{
   zVIEW  vDialogList;

   // Get the view to the window list
   if ( GetViewByName( &vDialogList, "TZWINDOWL", vSubtask, zLEVEL_TASK ) < 1 )
      return( -1 );
   if ( CheckExistenceOfEntity( vDialogList, "Window" ) != zCURSOR_SET ||
        !GetSelectStateOfEntityForSet( vDialogList, "Window", 1 ) )
   {
      SetCursorFirstEntity( vDialogList, "Window", 0 );
   }

   SetNameForView( vDialogList, "TZWINDOW", vSubtask, zLEVEL_TASK );
   return( 0 );
}


//./ ADD NAME=NewWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      NewWindow
//
//  PURPOSE:    To create a new window in the painter
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
NewWindow( zVIEW vSubtask )
{
   zVIEW  vDialog;
#ifndef __WIN32__
   zVIEW  vWindowList;
#endif
   zVIEW  vPE;
   zSHORT nIdx, nCursor;
   zCHAR  szTag[ 34 ];
   zPCHAR pchAttr;

   // Get the current open dialog.
   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) < 1 )
      return( -1 );

   GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );

   // Generate a name for the new window.
   if ( (nCursor = CheckExistenceOfEntity( vDialog, "Window" )) !=
                                                            zCURSOR_NULL )
   {
      strcpy_s( szTag, zsizeof( szTag ), "Window" );
      for ( nIdx = 1; nIdx < 1000; nIdx++ )
      {
         zltoa( (zLONG) nIdx, szTag + 6, zsizeof( szTag ) - 6 );
         if ( SetCursorFirstEntityByString( vDialog, "Window", "Tag",
                                            szTag, 0 ) < zCURSOR_SET )
         {
            break;
         }
      }
   }
   else
   {
      GetStringFromAttribute( szTag, zsizeof( szTag ), vDialog, "Dialog", "Tag" );
   }

   // If a dialog is currently being processed by the painter, update
   // the current window from the C++ controls to the Zeidon controls
   // and then clean out the painter, create a new window and
   // paint the new window into the painter
   SetCursorLastEntity( vDialog, "Window", 0 );
   CreateMetaEntity( vSubtask, vDialog, "Window", zPOS_AFTER );
   SetAttributeFromString( vDialog, "Window", "Tag", szTag );
   if ( nCursor == zCURSOR_NULL )
   {
      GetAddrForAttribute( &pchAttr, vDialog, "Dialog", "Desc" );
      if ( pchAttr[ 0 ] )
         SetAttributeFromString( vDialog, "Window", "Caption", pchAttr );
      else
         SetAttributeFromString( vDialog, "Window", "Caption", szTag );
   }
   else
   {
      SetAttributeFromString( vDialog, "Window", "Caption", szTag );
   }

   SetAttributeFromInteger( vDialog, "Window", "PSDLG_X", 2L );
   SetAttributeFromInteger( vDialog, "Window", "PSDLG_Y", 2L );
   SetAttributeFromInteger( vDialog, "Window", "SZDLG_X", 280L );
   SetAttributeFromInteger( vDialog, "Window", "SZDLG_Y", 128L );

   if ( nCursor == zCURSOR_NULL )
   {
      SetCursorFirstEntityByString( vPE, "WindowStyle", "Tag",
                                    "Primary Window", 0 );
   }
   else
   {
      SetCursorFirstEntityByString( vPE, "WindowStyle", "Tag",
                                    "Dialog Box", 0 );
   }

   if ( CheckExistenceOfEntity( vPE, "WindowStyle" ) > zCURSOR_NULL )
   {
      IncludeSubobjectFromSubobject( vDialog, "WndStyle",
                                     vPE, "WindowStyle",
                                     zPOS_BEFORE );
   }

   // Add default actions for OK and Cancel.
   if ( OperatorPrompt( vSubtask, "New Window",
                        "Do you want default buttons and actions created?",
                        1, zBUTTONS_YESNO,
                        zRESPONSE_YES, zICON_QUESTION ) == zRESPONSE_YES )
   {
      CreateMetaEntity( vSubtask, vDialog, "Action", zPOS_AFTER );
      SetAttributeFromString( vDialog, "Action", "Tag", "Alt-F4" );
      SetAttributeFromInteger( vDialog, "Action", "Type", 72 );
      CreateMetaEntity( vSubtask, vDialog, "Control", zPOS_AFTER );
      SetAttributeFromString( vDialog, "Control", "Tag", "OK" );
      SetAttributeFromString( vDialog, "Control", "Text", "OK" );
      SetAttributeFromInteger( vDialog, "Control", "PSDLG_X", 230 );
      SetAttributeFromInteger( vDialog, "Control", "PSDLG_Y", 12 );
      SetAttributeFromInteger( vDialog, "Control", "SZDLG_X", 40 );
      SetAttributeFromInteger( vDialog, "Control", "SZDLG_Y", 12 );
      SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key", 1020, "" );
      IncludeSubobjectFromSubobject( vDialog, "ControlDef",
                                     vPE,     "ControlDef", zPOS_AFTER );
      CreateMetaEntity( vSubtask, vDialog, "Event", zPOS_AFTER );
      SetAttributeFromInteger( vDialog, "Event", "Type", 1 );
      IncludeSubobjectFromSubobject( vDialog, "EventAct",
                                     vDialog, "Action", zPOS_AFTER );

      CreateMetaEntity( vSubtask, vDialog, "Action", zPOS_AFTER );
      SetAttributeFromString( vDialog, "Action", "Tag", "ESC" );
      SetAttributeFromInteger( vDialog, "Action", "Type", 71 );
      SetAttributeFromString( vDialog, "Action", "NoMap", "Y" );
      CreateMetaEntity( vSubtask, vDialog, "Control", zPOS_AFTER );
      SetAttributeFromString( vDialog, "Control", "Tag", "Cancel" );
      SetAttributeFromString( vDialog, "Control", "Text", "Cancel" );
      SetAttributeFromInteger( vDialog, "Control", "PSDLG_X", 230 );
      SetAttributeFromInteger( vDialog, "Control", "PSDLG_Y", 27 );
      SetAttributeFromInteger( vDialog, "Control", "SZDLG_X", 40 );
      SetAttributeFromInteger( vDialog, "Control", "SZDLG_Y", 12 );
      SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key", 1020, "" );
      IncludeSubobjectFromSubobject( vDialog, "ControlDef",
                                     vPE,     "ControlDef", zPOS_AFTER );
      CreateMetaEntity( vSubtask, vDialog, "Event", zPOS_AFTER );
      SetAttributeFromInteger( vDialog, "Event", "Type", 1 );
      IncludeSubobjectFromSubobject( vDialog, "EventAct",
                                     vDialog, "Action", zPOS_AFTER );
   }

   // Call the painter to create a new window
   SetNameForView( vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

#ifndef __WIN32__
   if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) > 0 )
      RefreshCtrl( vWindowList, "ListBox1" );
#endif

   fnPainterCall( zMSG_CREATEZEIDONWINDOW, vSubtask, 0, 0, 0 );

   GetViewByName( &vDialog, "TZPNMWIN", vSubtask, zLEVEL_TASK );
   RefreshWindow( vDialog );
   GetViewByName( &vDialog, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK );
   RefreshWindow( vDialog );
   return( 0 );
}

// Recursive function for copying controls
void
fnRecursProcessControls( zVIEW vSubtask, zVIEW vDialog, zVIEW vWindowList )
{
   // Create the control entity
   CreateMetaEntity( vSubtask, vDialog, "Control", zPOS_AFTER );
   SetMatchingAttributesByName( vDialog, "Control",
                                vWindowList, "Control",
                                zSET_NULL | zSET_NOTNULL );

   // Copy CtrlMap from source to target
   if ( SetCursorFirstEntity( vWindowList, "CtrlMap", 0 ) == zCURSOR_SET )
   do
   {
      CreateMetaEntity( vSubtask, vDialog, "CtrlMap", zPOS_AFTER );
      SetMatchingAttributesByName( vDialog, "CtrlMap",
                                   vWindowList, "CtrlMap",
                                   zSET_NULL | zSET_NOTNULL );
   }  while ( SetCursorNextEntity( vWindowList, "CtrlMap", 0 ) == zCURSOR_SET );

   // NOTE, Once we start including E/R information and domain information
   // under the mapping entity, we must do INCLUDES here for those
   // subordinate entities.

   // Copy Events under the Ctrl from source to target
   if ( SetCursorFirstEntity( vWindowList, "Event", 0 ) == zCURSOR_SET )
   do
   {
      CreateTemporalMetaEntity( vSubtask, vDialog, "Event", zPOS_AFTER );
      SetMatchingAttributesByName( vDialog, "Event",
                                   vWindowList, "Event",
                                   zSET_NULL | zSET_NOTNULL );
      if ( CheckExistenceOfEntity( vWindowList, "EventAct" ) == zCURSOR_SET )
      {
         CreateTemporalMetaEntity( vSubtask, vDialog, "EventAct", zPOS_AFTER );
         SetMatchingAttributesByName( vDialog, "EventAct",
                                      vWindowList, "EventAct",
                                      zSET_NULL | zSET_NOTNULL );
      }
   }  while ( SetCursorNextEntity( vWindowList, "Event", 0 ) == zCURSOR_SET );

   // Copy DIL_Msg from source to target
// Commented out by Don C 2/11/93
// if ( SetCursorFirstEntity( vWindowList, "CtrlDIL_Msg", 0 ) == zCURSOR_SET )
// do
// {
//    CreateMetaEntity( vSubtask, vDialog, "CtrlDIL_Msg", zPOS_AFTER );
//    SetMatchingAttributesByName( vDialog, "CtrlDIL_Msg",
//                                 vWindowList, "CtrlDIL_Msg",
//                                 zSET_NULL | zSET_NOTNULL );
// }  while ( SetCursorNextEntity( vWindowList, "CtrlDIL_Msg", 0 ) == zCURSOR_SET );

   // Recursively call ourself for all sub-controls
   if ( SetCursorFirstEntity( vWindowList, "CtrlCtrl", 0 ) == zCURSOR_SET )
   {
      SetViewToSubobject( vWindowList, "CtrlCtrl" );
      SetViewToSubobject( vDialog, "CtrlCtrl" );
      do
      {
         fnRecursProcessControls( vSubtask, vDialog, vWindowList );
      }  while ( SetCursorNextEntity( vWindowList, "Control", 0 ) == zCURSOR_SET );
      ResetViewFromSubobject( vWindowList );
      ResetViewFromSubobject( vDialog );
   }
}

// Recursive function for copying options
void
fnRecursProcessOptions( zVIEW vSubtask, zVIEW vDialog, zVIEW vWindowList )
{
   // Create the option entity
   CreateMetaEntity( vSubtask, vDialog, "Option", zPOS_AFTER );
   SetMatchingAttributesByName( vDialog, "Option",
                                vWindowList, "Option",
                                zSET_NULL | zSET_NOTNULL );

   // Copy OptAct from source to target
   if ( SetCursorFirstEntity( vWindowList, "OptAct", 0 ) == zCURSOR_SET )
   do
   {
      CreateMetaEntity( vSubtask, vDialog, "OptAct", zPOS_AFTER );
      SetMatchingAttributesByName( vDialog, "OptAct",
                                   vWindowList, "OptAct",
                                   zSET_NULL | zSET_NOTNULL );
   }  while ( SetCursorNextEntity( vWindowList, "OptAct", 0 ) ==
                                                               zCURSOR_SET );

   // Copy OptMap from source to target
   if ( SetCursorFirstEntity( vWindowList, "OptMap", 0 ) == zCURSOR_SET )
   do
   {
      CreateMetaEntity( vSubtask, vDialog, "OptMap", zPOS_AFTER );
      SetMatchingAttributesByName( vDialog, "OptMap",
                                   vWindowList, "OptMap",
                                   zSET_NULL | zSET_NOTNULL );
   }  while ( SetCursorNextEntity( vWindowList, "OptMap", 0 ) ==
                                                               zCURSOR_SET );

   // NOTE, Once we start including E/R information and domain information
   // under the mapping entity, we must do INCLUDES here for those
   // subordinate entities.

   // Recursively call ourself for all sub-options
   if ( SetCursorFirstEntity( vWindowList, "OptOpt", 0 ) == zCURSOR_SET )
   {
      SetViewToSubobject( vWindowList, "OptOpt" );
      SetViewToSubobject( vDialog, "OptOpt" );
      do
      {
         fnRecursProcessOptions( vSubtask, vDialog, vWindowList );
      }  while ( SetCursorNextEntity( vWindowList, "Option", 0 ) ==
                                                               zCURSOR_SET );
      ResetViewFromSubobject( vWindowList );
      ResetViewFromSubobject( vDialog );
   }
}

//./ ADD NAME=DlgCloneWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DlgCloneWindow
//
//  PURPOSE:    To clone an existing window in the painter
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DlgCloneWindow( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vWindowList;
   zSHORT nIdx;
   zCHAR  szTag[ 34 ];

   // Get the current open dialog.
   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) < 1 )
      return( -1 );

   // Get a cursor to the window to be cloned
   GetViewByName( &vWindowList, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vDialog, "Window" ) == zCURSOR_NULL )
      return( -1 );

   SetCursorLastEntity( vDialog, "Window", 0 );
   oTZWDLGSO_CloneWindow( vDialog, vWindowList, vSubtask, vSubtask );

   // Generate a name for the new window
   strcpy_s( szTag, zsizeof( szTag ), "Window" );
   for ( nIdx = 1; nIdx < 1000; nIdx++ )
   {
      zltoa((zLONG) nIdx, szTag + 6, zsizeof( szTag ) - 6 );
      if ( SetCursorFirstEntityByString( vWindowList, "Window", "Tag",
                                         szTag, 0 ) < zCURSOR_SET )
      {
         break;
      }
   }

   SetAttributeFromString( vDialog, "Window", "Tag", szTag );
#ifndef __WIN32__
   if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) > 0 )
      RefreshCtrl( vWindowList, "ListBox1" );
#endif

   return( (zSHORT) fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, szTag, zsizeof( szTag ) ) );
}

//./ ADD NAME=CleanupActions
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CleanupActions
//
//  PURPOSE:    This function lists all actions for the dialog and
//              offers the opportunity to delete the action if it
//              is unreferenced.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
CleanupActions( zVIEW vSubtask )
{
   zVIEW vDialog;
   zVIEW vWindow;

   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) > 0 )
   {
      zCHAR szTempString[ 256 ];
      zSHORT nLth1;
      zSHORT nLth2;
      zSHORT nRC;

      strcpy_s( szTempString, zsizeof( szTempString ), "Action unreferenced Dialog.Window.Action: " );
      nLth1 = (zSHORT) zstrlen( szTempString );
      GetStringFromAttribute( szTempString + nLth1, zsizeof( szTempString ) - nLth1, vDialog, "Dialog", "Tag" );
      nLth1 += (zSHORT) zstrlen( szTempString + nLth1 );
      szTempString[ nLth1++ ] = '.';

      CreateViewFromViewForTask( &vDialog, vDialog, 0 );
      nRC = SetCursorFirstEntity( vDialog, "Action", "Dialog" );
      while ( nRC >= zCURSOR_SET )
      {
         if ( CheckExistenceOfEntity( vDialog, "ActWndEvent" ) == 0 ||
              CheckExistenceOfEntity( vDialog, "ActEvent" ) == 0 ||
              CheckExistenceOfEntity( vDialog, "ActOpt" ) == 0   ||
              CheckExistenceOfEntity( vDialog, "ActHot" ) == 0 )
         {
            nRC = SetCursorNextEntity( vDialog, "Action", "Dialog" );
            continue;
         }

         GetStringFromAttribute( szTempString + nLth1, zsizeof( szTempString ) - nLth1,
                                 vDialog, "Window", "Tag" );
         nLth2 = (zSHORT) zstrlen( szTempString + nLth1 );
         szTempString[ nLth1 + nLth2++ ] = '.';
         GetStringFromAttribute( szTempString + nLth1 + nLth2, zsizeof( szTempString ) - nLth1 + nLth2,
                                 vDialog, "Action", "Tag" );
         strcat_s( szTempString + nLth1 + nLth2, zsizeof( szTempString ) - nLth1 - nLth2, "\n Delete this action?" );
         nRC = MessagePrompt( vSubtask, "PE002",
                              "Dialog Maintenance",
                              szTempString,
                              zBEEP, zBUTTONS_YESNOCANCEL,
                              zRESPONSE_NO,  0 );
         if ( nRC == zRESPONSE_CANCEL )
         {
            break;
         }
         else
         if ( nRC == zRESPONSE_YES )
         {
            DeleteEntity( vDialog, "Action", zREPOS_NONE );

            // Refresh Action List
            if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_ACT" ) >= 0 )
               RefreshWindow( vWindow );
         }

         nRC = SetCursorNextEntity( vDialog, "Action", "Dialog" );
      }
   }

   return( 0 );
}

//./ ADD NAME=CleanupOperations
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CleanupOperations
//
//  PURPOSE:    This function lists all operations for the dialog and
//              offers the opportunity to delete the operation if it
//              is unreferenced.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
CleanupOperations( zVIEW vSubtask )
{
   zVIEW vDialog;

   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) > 0 )
   {
      zCHAR szTempString[ 256 ];
      zSHORT nLth;
      zSHORT nLth2;
      zSHORT nRC;

      strcpy_s( szTempString, zsizeof( szTempString ), "Operation unreferenced in Dialog - " );
      nLth = (zSHORT) zstrlen( szTempString );
      CreateViewFromViewForTask( &vDialog, vDialog, 0 );
      nRC = SetCursorFirstEntity( vDialog, "Operation", "Dialog" );
      while ( nRC >= zCURSOR_SET )
      {
         if ( SetCursorFirstEntityByEntityCsr( vDialog, "ActOper", vDialog, "Operation", "Dialog" ) >= zCURSOR_SET )
         {
            nRC = SetCursorNextEntity( vDialog, "Operation", "Dialog" );
            continue;
         }

         GetStringFromAttribute( szTempString + nLth, zsizeof( szTempString ) - nLth, vDialog, "Window", "Tag" );
         nLth2 = (zSHORT) zstrlen( szTempString + nLth );
         strcpy_s( szTempString + nLth + nLth2, zsizeof( szTempString ) - nLth - nLth2, " - " );
         nLth2 += 3;
         GetStringFromAttribute( szTempString + nLth + nLth2, zsizeof( szTempString ) - nLth + nLth2, vDialog, "Operation", "Name" );
         strcat_s( szTempString + nLth + nLth2, zsizeof( szTempString ) - nLth - nLth2, "\n Delete this operation?" );
         if ( MessagePrompt( vSubtask, "PE002",
                             "Dialog Maintenance",
                             szTempString,
                             zBEEP, zBUTTONS_YESNO,
                             zRESPONSE_NO,  0 ) != zRESPONSE_NO )
         {
            DeleteEntity( vDialog, "Operation", zREPOS_NONE );
         }

         nRC = SetCursorNextEntity( vDialog, "Operation", "Dialog" );
      }
   }

   return( 0 );
}

//./ ADD NAME=ActionListTransfer
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ActionListTransfer
//
//  PURPOSE:    This function sets the ParentIsSelectAction attribute
//              to "N" to set up proper graying in the LIST_ACT window.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
ActionListTransfer( zVIEW vSubtask )
{
   zVIEW  vWork;
   zVIEW  vWindow;

   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_ACT" ) >= 0 )
   {
      SetWindowState( vWindow, zWINDOW_STATUS_DESTROY, 1 );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
   }

   zwTZPNTRAD_InitModalSubwindow( vSubtask );

   if ( GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      ActivateEmptyObjectInstance( &vWork, "TZPNCTWO", vSubtask, zSINGLE );
      CreateEntity( vWork, "TZPNCTWO", zPOS_AFTER );
      SetNameForView( vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );
   }

   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "N" );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_CheckDialogName
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
zwTZPNTRAD_CheckDialogName( zVIEW   vSubtask,
                            zVIEW   vPainter,
                            zPCHAR  pchDialogName )
{
   zSHORT  nIdx;
   zVIEW   vMetaList;
   zVIEW   vLOD_LPLR;

   GetStringFromAttribute( pchDialogName, 33, vPainter, "Palette", "NewFile" );
   if ( pchDialogName[ 0 ] == 0 )
   {
      MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                   "Must enter in a dialog name!",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "EDITTAG" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -2 );
   }

   // Truncate FileName to 8
   for ( nIdx = 0; nIdx < 8; nIdx++ )
   {
      if ( pchDialogName[ nIdx ] == ' ' )
         pchDialogName[ nIdx ] = '_';
   }
   pchDialogName[ 8 ] = 0;

   // There must be no other Dialog with same name.
   if ( GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK ) < 1 )
   {
      RetrieveViewForMetaList( vSubtask, &vMetaList, zREFER_DIALOG_META );
      SetNameForView( vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   }

   if ( SetCursorFirstEntityByString( vMetaList, "W_MetaDef", "Name",
                                      pchDialogName, 0 ) > zCURSOR_UNCHANGED )
   {
      MessageSend( vSubtask, "PN00220", "Dialog Maintenance",
                   "A Dialog by the same name already exists",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "EDITTAG" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -2 );
   }

   // There must be no LOD with same name.
   RetrieveViewForMetaList( vSubtask, &vLOD_LPLR, zREFER_LOD_META );
   if ( SetCursorFirstEntityByString( vLOD_LPLR,
                                      "W_MetaDef", "Name",
                                      pchDialogName, 0 ) > zCURSOR_UNCHANGED )
   {
      MessageSend( vSubtask, "PN00221", "Zeidon Object Maintenance",
                   "A LOD with the same name exists.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "EDITTAG" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -2 );
   }

   return( 0 );
} // zwTZPNTRAD_CheckDialogName



//./ ADD NAME=NewDialogFile
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      NewDialogFile
//
//  PURPOSE:    To start creating a new dialog
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
NewDialogFile( zVIEW vSubtask )
{
   zVIEW   vNewDialog;
   zVIEW   vNewDialogL;
   zVIEW   vNewOptions;
   zVIEW   vPrevDialog;
   zVIEW   vPainter;
   zCHAR   szDialogName[ 33 ];

   szDialogName[ 0 ] = 0;

   // get the C++ class pointer to the painter object from the
   // zeidon control object
   GetViewByName( &vPainter, "TZPNTROO", vSubtask, zLEVEL_TASK );

   if ( zwTZPNTRAD_CheckDialogName( vSubtask, vPainter, szDialogName ) < 0 )
      return( 0 );

   //Refresh all Lists from menu <View> (=Modeless Subwindows)
   RefreshAllSubwindows( vSubtask );

   // Declare a view to the appropriate source dialog object type
   ActivateEmptyMetaOI( vSubtask, &vNewDialog, zSOURCE_DIALOG_META,
                        zSINGLE | zLEVEL_TASK );
   CreateMetaEntity( vSubtask, vNewDialog, "Dialog", zPOS_AFTER );
   SetAttributeFromString( vNewDialog, "Dialog", "Tag", szDialogName );
   SetAttributeFromString( vNewDialog, "Dialog", "DLL_Name",
                           szDialogName );

   // Now create an empty SourceFile entity by the same name as the Dialog.
   CreateMetaEntity( vSubtask, vNewDialog, "SourceFile", zPOS_AFTER );
   SetAttributeFromString( vNewDialog, "SourceFile", "Name", szDialogName );
   SetAttributeFromString( vNewDialog, "SourceFile", "Extension", "VML" );
   SetAttributeFromString( vNewDialog, "SourceFile", "LanguageType", "V" );

   SetAttributeFromAttribute( vNewDialog, "Dialog", "Desc",
                              vPainter, "Palette", "Desc" );
   SetAttributeFromString( vPainter, "Palette", "OpenedFile", szDialogName );

   // Clear the painter windows
   fnPainterCall( zMSG_DELETEALLPAINTERWINDOWS, vSubtask, 0, 0, 0 );

   // Drop the previous instance being worked on.
   if ( GetViewByName( &vPrevDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) > 0 )
      DropMetaOI( vSubtask, vPrevDialog );

   // Name the view for mapping.
   SetNameForView( vNewDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );
   SetNameForView( vNewDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   CreateViewFromViewForTask( &vNewDialogL, vNewDialog, 0 );
   SetNameForView( vNewDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vNewOptions, vNewDialog, 0 );
   SetNameForView( vNewOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   // Call NewWindow to do the rest
   NewWindow( vSubtask );

   // Include the window just created as the default window.
   IncludeSubobjectFromSubobject( vNewDialog, "DfltWnd",
                                  vNewDialog, "Window", zPOS_AFTER );

   //BL, 1999.11.16 refresh all modeless subwindows
   zwTZPNTRAD_RefreshAllSubwindows( vSubtask );

   return( 0 );
}

//./ ADD NAME=DeleteWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DeleteWindow
//
//  PURPOSE:    To delete a window in the painter
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DeleteWindow( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vDialog2;
   zCHAR  szTag[ 33 ];
   zCHAR  szMessage[ 100 ];

   fnPainterCall( zMSG_GETACTIVEWINDOWNAME, vSubtask, 0, szTag, zsizeof( szTag ) );
   if ( szTag[ 0 ] == 0 )
      return( -1 );

   // Get the view to the window list
   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) < 1 )
      return( -1 );

   if ( SetCursorFirstEntityByString( vDialog, "Window",
                                      "Tag", szTag, 0 ) < zCURSOR_SET )
      return( -1 );

   // Create a view to the window in the event the painter drops
   // the current view we are using
   CreateViewFromViewForTask( &vDialog2, vDialog, 0 );

   // Make operator confirm the delete
   strcpy_s( szMessage, zsizeof( szMessage ), "OK to delete Window '" );
   strcat_s( szMessage, zsizeof( szMessage ), szTag );
   strcat_s( szMessage, zsizeof( szMessage ), "'?" );

   if ( MessagePrompt( vSubtask, "PE002",
                       "Dialog Maintenance",
                       szMessage,
                       zBEEP, zBUTTONS_YESNO,
                       zRESPONSE_NO,  0 ) == zRESPONSE_NO )
   {
      DropView( vDialog2 );
      return( -1 );
   }

   if ( fnPainterCall( zMSG_DELETECURRENTPAINTERWINDOW, vSubtask, 0, 0, 0 ) == 0 )
   {
      DeleteEntity( vDialog2, "Window", zREPOS_NEXT );

#ifndef __WIN32__
      SetNameForView( vDialog2, "TZWINDOW", vSubtask, zLEVEL_TASK );
      if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) > 0 )
         RefreshCtrl( vWindowList, "ListBox1" );
#endif
   }

   DropView( vDialog2 );
   return( 0 );
}

//./ ADD NAME=DeleteWindowFromList
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DeleteWindowFromList
//
//  PURPOSE:    To delete a window from the painter list. This operation
//              calls update window by name to display and 'make current'
//              the window to be deleted and then calls DeleteWindow to
//              delete the window.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DeleteWindowFromList( zVIEW vSubtask )
{
   zVIEW vDialog;
   zSHORT nRC;

   nRC = GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   /* If the dialog doesn't exist, or a window doesn't exist then
      it can't be deleted, so return. */
   if ( nRC < 1 || CheckExistenceOfEntity( vDialog, "Window" ) != 0 )
      return( 0 );

   GetViewByName( &vDialog, "TZPNMWIN", vSubtask, zLEVEL_TASK );

   if ( UpdateWindowFromList( vSubtask ) == 0 )
   {
      nRC = DeleteWindow( vSubtask );
      RefreshWindow( vDialog );
      fnPainterCall( zMSG_REFRESHWINDOWLIST, vSubtask, 0, 0, 0 );
      return( nRC );
   }

   return( -1 );
}

//./ ADD NAME=EnablePainterWindows
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      EnablePainterWindows
//
//  PURPOSE:    To enable painter windows when a control dialog returns
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
EnablePainterWindows( zVIEW vSubtask )
{
   zVIEW   vMetaList;
   zVIEW   vWindowList = 0;
   zVIEW   vTZPESRCO = 0;
   zVIEW   vTZWINDOWL;
   zSHORT  nRC;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // Activate the presentation environment, if the presentation
   // environment is no longer with us
   if ( GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      // Activate the presentation environment
      if ( zwfnTZPNTRAD_Load_PPE( vSubtask ) < 0 )
         return( -1 );

      fnPainterCall( zMSG_REPLACETOOLBARBUTTONS, vSubtask, 0, 0, 0 );
   } // endif ( GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )

   // Set window Title with check out state
   SetTitleWithCheckOutState( vSubtask, "Dialog Maintenance", "TZWINDOWL",
                              vTZWINDOWL, "Dialog", zSOURCE_DIALOG_META );

   //Refresh all Lists from menu <View> (=Modeless Subwindows)
   RefreshAllSubwindows( vSubtask );

   if ( GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK ) < 1 )
   {
      RetrieveViewForMetaList( vSubtask, &vMetaList, zREFER_DIALOG_META );
      if ( vMetaList )
         SetNameForView( vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   }

   if ( GetSubtaskForWindowName( vSubtask, &vWindowList, "WND_LIST" ) >= 0 )
   {
//    SetWindowState( vWindowList, zWINDOW_STATUS_VISIBLE, 1 );
//    SetWindowState( vWindowList, zWINDOW_STATUS_ENABLED, 1 );
#ifndef __WIN32__
      SetCtrlState( vWindowList, "ListBox1", zCONTROL_STATUS_ENABLED, 1 );
      RefreshCtrl( vWindowList, "ListBox1" );
#endif
   }

#ifndef __WIN32__
   if ( GetViewByName( &vMetaList, "TZDIALOGS", vSubtask, zLEVEL_TASK ) < 1 &&
        GetSubtaskForWindowName( vSubtask, &vWindowList, "WND_LIST" ) >= 0 )
   {
      ActivateWindow( vWindowList );
      return( 0 );
   }
#endif

   nRC = (zSHORT) fnPainterCall( zMSG_ENABLEPAINTERWINDOWS, vSubtask, 0, "Y", 0 );
   return( nRC );
}

//./ ADD NAME=DisablePainterWindows
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DisablePainterWindows
//
//  PURPOSE:    To disable painter windows when a control dialog returns
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DisablePainterWindows( zVIEW vSubtask )
{
   return( (zSHORT) fnPainterCall( zMSG_ENABLEPAINTERWINDOWS, vSubtask, 0, 0, 0 ) );
}

//./ ADD NAME=ShowTabbing
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ShowTabbing
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
ShowTabbing( zVIEW vSubtask )
{
   return( (zSHORT) fnPainterCall( zMSG_SHOWTABBING, vSubtask, 0, 0, 0 ) );
}

//./ ADD NAME=RemoveTabbing
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      RemoveTabbing
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
RemoveTabbing( zVIEW vSubtask )
{
   if ( MessagePrompt( vSubtask, "PE002",
                       "Dialog Maintenance",
                       "Remove All Tabstops?",
                       zBEEP, zBUTTONS_YESNO,
                       zRESPONSE_NO,  0 ) == zRESPONSE_YES )
   {
      return( (zSHORT) fnPainterCall( zMSG_REMOVETABBING, vSubtask, 0, 0, 0 ) );
   }

   return( 0 );
}

//./ ADD NAME=NextAction
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      NextAction
//
//  PURPOSE:    To Change the next Action definition for the current window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
NextAction( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   SetCursorNextEntity( vDialog, "Action", 0 );

   return( 0 );
}

//./ ADD NAME=PrevAction
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      PrevAction
//
//  PURPOSE:    To Change the previous Action definition for
//              the current window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
PrevAction( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   SetCursorPrevEntity( vDialog, "Action", 0 );

   return( 0 );
}

//./ ADD NAME=NewAction
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      NewAction
//
//  PURPOSE:    To Create a new Action in the current window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
NewAction( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   CreateMetaEntity( vSubtask, vDialog, "Action", zPOS_AFTER );

   return( 0 );
}

//./ ADD NAME=DeleteAction
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DeleteAction
//
//  PURPOSE:    To Delete an Action in the current window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DeleteAction( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( DeleteEntity( vDialog, "Action", zREPOS_NEXT ) == zCURSOR_NULL )
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParentWithRefresh, 0, 0 );

   return( 0 );
}

//./ ADD NAME=ActionAdd
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ActionAdd
//
//  PURPOSE:    To Add an action to the window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
ActionAdd( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   while ( ResetViewFromSubobject( vDialog ) == 0 )
   {
   }

   CreateMetaEntity( vSubtask, vDialog, "Action", zPOS_AFTER );
   SetAttributeFromString( vDialog, "Action", "Tag", "New" );
   return( 0 );
}

//./ ADD NAME=ActionUpdate
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    ActionUpdate
//
// PURPOSE:  To Update an action for the window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
ActionUpdate( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   while ( ResetViewFromSubobject( vDialog ) == 0 )
   {
   }

   if ( CheckExistenceOfEntity( vDialog, "Action" ) > zCURSOR_UNCHANGED )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow,
                               "TZPNTRAD", "ACT_UPD" );
   }

   return( 0 );
}

//./ ADD NAME=SortWindows
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SortWindows
//
//  PURPOSE:    To Sort windows in a Dialog
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SortWindows( zVIEW vSubtask )
{
   zVIEW vDialog;
   zCHAR szSelected[ 34 ];

   GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szSelected, zsizeof( szSelected ), vDialog, "Window", "Tag" );
   zgSortEntityWithinParent( zASCENDING, vDialog, "Window", "Tag", "" );
   SetCursorFirstEntityByString( vDialog, "Window", "Tag", szSelected, 0 );
   SetAllSelStatesForEntityForSet( vDialog, "Window", 0, 1, 0 );
   SetSelectStateOfEntityForSet( vDialog, "Window", 1, 1 );
   return( 0 );
}

//./ ADD NAME=SortActinsForWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SortActionsForWindow
//
//  PURPOSE:    To Sort actions for a window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SortActionsForWindow( zVIEW vSubtask )
{
   zVIEW vDialog;
   zCHAR szSelected[ 34 ];

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szSelected, zsizeof( szSelected ), vDialog, "Action", "Tag" );
   zgSortEntityWithinParent( zASCENDING, vDialog,
                             "Action", "Tag", "" );
   SetCursorFirstEntityByString( vDialog, "Action", "Tag", szSelected, 0 );
   SetAllSelStatesForEntityForSet( vDialog, "Action", 0, 1, 0 );
   SetSelectStateOfEntityForSet( vDialog, "Action", 1, 1 );
   return( 0 );
}

//./ ADD NAME=ActionDeleteFromList
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ActionDeleteFromList
//
//  PURPOSE:    To Delete an action for the window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
ActionDeleteFromList( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vDialog, "Action" ) > zCURSOR_UNCHANGED )
   {
      DeleteEntity( vDialog, "Action", zREPOS_NEXT );
   }

   return( 0 );
}

//./ ADD NAME=WndSelectAction
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WndSelectAction
//
//  PURPOSE:    To select an action for a window Event
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WndSelectAction( zVIEW vSubtask )
{
   zVIEW vDialog;
   zVIEW vEvents;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vDialog, "Action" ) > zCURSOR_UNCHANGED )
   {
      SetAttributeFromAttribute( vEvents, "EventAct", "Tag",
                                 vDialog, "Action", "Tag" );
   }

   return( 0 );
}

//./ ADD NAME=WndRemoveAction
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WndRemoveAction
//
//  PURPOSE:    To Remove an action for a window Event
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WndRemoveAction( zVIEW vSubtask )
{
   zVIEW vEvents;

   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   SetAttributeFromString( vEvents, "EventAct", "Tag", 0 );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// Recursive function for building TZPNOPWO Object
// NOTE: This CODE was borrowed/stolen from the painter control and
//       is duplicated in the painter control, the painter control
//       version should be eradicated and the build of the TZPNOPWO
//       object should be done in the prebuild of the menu window
//       ONLY and by this MODULE!!! 1/29/93 - Gig
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
fnBuildRecursSubOptions( zVIEW vSubtask, zVIEW vDialog, zVIEW vOptionList,
                         zSHORT nLevel, zSHORT nID )
{
   zSHORT nIdx;
   zCHAR  szText[ 34 ];
   zCHAR  szDisplayText[ 80 ];

   if ( SetCursorFirstEntity( vDialog, "Option", 0 ) == zCURSOR_SET )
   {
      do
      {
         szDisplayText[ 0 ] = 0;
         for ( nIdx = 0; nIdx <( 3 *(nLevel - 1) ); nIdx++ )
            szDisplayText[ nIdx ] = '.';
         szDisplayText[ nIdx ] = 0;
         GetStringFromAttribute( szText, zsizeof( szText ), vDialog, "Option", "Text" );
         strcat_s( szDisplayText, zsizeof( szDisplayText ), szText );
         CreateEntity( vOptionList, "Option", zPOS_AFTER );
         SetAttributeFromAttribute( vOptionList, "Option", "ZKey",
                                    vDialog, "Option", "ZKey" );
         SetAttributeFromInteger( vOptionList, "Option", "ID", nID++ );
      /* SetAttributeFromInteger( vOptionList, "Option",
                                  "StartLevel", nLevel ); */
         SetAttributeFromInteger( vOptionList, "Option",
                                  "Level", nLevel );
         SetAttributeFromString( vOptionList, "Option", "DisplayText",
                                 szDisplayText );
         SetViewToSubobject( vDialog, "OptOpt" );
         nID = fnBuildRecursSubOptions( vSubtask, vDialog, vOptionList,
                                        (zSHORT) (nLevel + 1), nID );
         ResetViewFromSubobject( vDialog );

      } while ( SetCursorNextEntity( vDialog, "Option", 0 ) == zCURSOR_SET );
   }

   return( nID );
}

/////////////////////////////////////////////////////////////////////////////
//
// Function to build the OptionList work object(TZPNOPWO)
//
/////////////////////////////////////////////////////////////////////////////
void
fnBuildOptionList( zVIEW vSubtask, zVIEW vDialog, zPVIEW vOptionList )
{
   zVIEW  vOption;

   GetViewByName( &vOption, "TZWINOPT", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      ActivateEmptyObjectInstance( vOptionList, "TZPNOPWO",
                                   vSubtask, zSINGLE );
      SetNameForView( *vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   }
   else
   {
   // nRC = DeleteEntity( *vOptionList, "Root", zREPOS_NONE );
      DropView( *vOptionList );
      ActivateEmptyObjectInstance( vOptionList, "TZPNOPWO",
                                   vSubtask, zSINGLE );
      SetNameForView( *vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   }

   CreateEntity( *vOptionList, "Root", zPOS_AFTER );

   if ( CheckExistenceOfEntity( vOption, "Option" ) == zCURSOR_SET )
   {
      fnBuildRecursSubOptions( vSubtask, vDialog, *vOptionList, 1, 1 );
   }
}

//./ ADD NAME=fnPositionOnZeidonOption
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnPositionOnZeidonOption
//
//  PURPOSE:    To Position on option corresponding to the
//              displayed/selected work object Option.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT
fnPositionOnZeidonOption( zVIEW vDialog, zVIEW vOptionList, zVIEW vSubtask )
{
   zUSHORT uLevel;
   zSHORT  nRC;
   zLONG   lZKey;
   zCHAR   szEntityName[ 256 ];

   if ( CheckExistenceOfEntity( vOptionList, "Option" ) != 0 )
      return( 0 );

   // Get ZKey of Option on which work object is positioned.
   GetIntegerFromAttribute( &lZKey, vOptionList, "Option", "ZKey" );

   // Position on first option in window
   while ( ResetViewFromSubobject( vDialog ) == 0 )
   {
   }

   nRC = SetCursorFirstEntity( vDialog, "Option", 0 );

   // Define a hierarchical cursor on the dialog view
   DefineHierarchicalCursor( vDialog, "Option" );

   // Search hierarchically until finding the corresponding Option
   for ( ; ; )
   {
      if ( nRC == zCURSOR_UNCHANGED )
      {
         MessageSend( vSubtask, "PN00204", "Dialog Maintenance",
                      "Program Error",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         break;
      }

      if ( nRC == zCURSOR_SET_RECURSIVECHILD )
         SetViewToSubobject( vDialog, szEntityName );

      if ( CompareAttributeToInteger( vDialog, "Option",
                                      "ZKey", lZKey ) == 0 )
      {
         break;
      }

      nRC = SetCursorNextEntityHierarchical( &uLevel, szEntityName, vDialog );
   }

   // Drop the hierarchical cursor
   DropHierarchicalCursor( vDialog );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: zwTZPNTRAD_DeleteMenu
//
// PURPOSE:   Delete a Menu
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_DeleteMenu( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vWindow;
   zSHORT nRC;

// Get Access to Window

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   nRC = MessagePrompt( vSubtask, "PE002",
                       "Dialog Maintenance",
                       "OK to delete selected Menus?",
                       zBEEP, zBUTTONS_YESNO,
                       zRESPONSE_NO,  0 );
// Delete Menu
   if ( nRC == zRESPONSE_YES )
   {
      for ( nRC = SetCursorFirstSelectedEntity( vDialog, "Menu", "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextSelectedEntity( vDialog, "Menu", "" ) )
      {
         nRC = DeleteEntity( vDialog, "Menu", zREPOS_NONE );
      }
      if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_MENU" ) >= 0 )
        RefreshWindow( vWindow );
   }
   else
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
   }

   return( 0 );
}

//./ ADD NAME=LIST_MENU_Prebuild
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:     LIST_MENU_Prebuild
//
//  PURPOSE:    Menu List Initialization.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
LIST_MENU_Prebuild( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zCHAR szTempString[ 255 ];

   // Set the caption for the window
   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      GetStringFromAttribute( szTempString, zsizeof( szTempString ), vDialog, "Window", "Tag");
      SetWindowCaptionTitle( vSubtask, 0, szTempString );
   }
   else
      SetWindowCaptionTitle( vSubtask, 0, "" );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
LIST_MENU_OK( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zSHORT nRC;
   zCHAR  szMsg[ 100 ];
   zCHAR  szMenuName[ 33 ];

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      // Make sure that all Menu entities have at least one Option.
      for ( nRC = SetCursorFirstEntity( vDialog, "Menu", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDialog, "Menu", 0 ) )
      {
         if ( CheckExistenceOfEntity( vDialog, "Option" ) < zCURSOR_SET )
         {
            strcpy_s( szMsg, zsizeof( szMsg ), "Menu item, " );
            GetStringFromAttribute( szMenuName, zsizeof( szMenuName ), vDialog, "Menu", "Tag" );
            strcat_s( szMsg, zsizeof( szMsg ), szMenuName );
            strcat_s( szMsg, zsizeof( szMsg ), ", must have at least one Option" );
            MessageSend( vSubtask, "PN00222", "Dialog Maintenance",
                         szMsg,
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
            SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
            return( -1 );
         }
      }
   }

   return( 0 );
}

//./ ADD NAME=UPD_MENU_Prebuild
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_Prebuild
//
//  PURPOSE:    Build the Option work object and initialize TZWINOPT.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_Prebuild( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vOptionList;
   zVIEW  vOptions;
   zCHAR  szTempString[ 255 ];

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vOptions, vDialog, 0 );
   SetNameForView( vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   fnBuildOptionList( vSubtask, vDialog, &vOptionList );

   // Highlight the first Option
   if ( CheckExistenceOfEntity( vOptionList, "Option" ) >= 0 )
   {
      SetCursorFirstEntity( vOptionList, "Option", "" );
      SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );
   }
   // Position on the first zeidon option.
   fnPositionOnZeidonOption( vOptions, vOptionList, vSubtask );

   // Set the caption for the window
   GetStringFromAttribute( szTempString, zsizeof( szTempString ), vDialog, "Window", "Tag");
   SetWindowCaptionTitle( vSubtask, 0, szTempString );

   return( 0 );
}

//./ ADD NAME=UPD_MENU_Postbuild
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_Postbuild
//
//  PURPOSE:    Set state of checkBox control
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_Postbuild( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vDialogCopy;
   zVIEW  vWindow;
   zSHORT nRC;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( SetCursorFirstEntity( vDialog, "DfltMenu", 0 ) == zCURSOR_SET )
   {
      if ( CompareAttributeToAttribute( vDialog, "DfltMenu", "Tag",
                                        vDialog, "Menu", "Tag" ) == 0 )
         SetCtrlState( vSubtask, "DefaultCheckBox", zCONTROL_STATUS_CHECKED, TRUE );
   }

   // Menu List is a multi selection list, delesect all Menues
   CreateViewFromViewForTask( &vDialogCopy, vDialog, 0 );
   for ( nRC = SetCursorFirstSelectedEntity( vDialog, "Menu", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextSelectedEntity( vDialog, "Menu", "" ) )
   {
      SetSelectStateOfEntity( vDialog, "Menu", 0 );
   }
   SetCursorFirstEntityByAttr( vDialog, "Menu", "ZKey",
                               vDialogCopy, "Menu", "ZKey", "" );
   DropView( vDialogCopy );
   SetSelectStateOfEntity( vDialog, "Menu", 1 );

   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_MENU" ) >= 0 )
      RefreshWindow( vWindow );

   if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
   {
      SetCtrlState( vSubtask, "DefaultCheckBox", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "Add", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "Delete", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "DefaultCheckBox", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "Up", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "Down", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "Left", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "Right", zCONTROL_STATUS_ENABLED, FALSE );
   }

   return( 0 );
}

//./ ADD NAME=UPD_MENU_ReturnFromSubWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_ReturnFromSubWindow
//
//  PURPOSE:    Rebuild the Option work object and position the
//              cursor on the correct entry.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_ReturnFromSubWindow( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vOptionList;
   zVIEW  vOptions;
   zLONG  lZKey;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   fnBuildOptionList( vSubtask, vDialog, &vOptionList );

   // Position on correct member in list.
   // If no Option exists at that level, go up a level.
   if ( CheckExistenceOfEntity( vDialog, "Menu" ) >= 0 )
   {
      if ( CheckExistenceOfEntity( vOptions, "Option" ) < 0 )
         ResetViewFromSubobject( vOptions );

      if ( CheckExistenceOfEntity( vOptions, "Option" ) >= 0 )
      {
         GetIntegerFromAttribute( &lZKey, vOptions, "Option", "ZKey" );
         SetCursorFirstEntityByInteger( vOptionList, "Option",
                                        "ZKey", lZKey, "" );
         SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );
      }
   }

   return( 0 );
}

//./ ADD NAME=UPD_MENU_SetDefaultMenu
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_SetDefaultMenu
//
//  PURPOSE:    To go to the previous menu in the dialog
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_SetDefaultMenu( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( SetCursorFirstEntity( vDialog, "DfltMenu", 0 ) == zCURSOR_SET )
   {
      ExcludeEntity( vDialog, "DfltMenu", zREPOS_NONE );
   }
   if ( CheckExistenceOfEntity( vDialog, "Menu" ) == zCURSOR_SET )
      IncludeSubobjectFromSubobject( vDialog, "DfltMenu",
                                     vDialog, "Menu", zPOS_AFTER );

   return( 0 );
}

//./ ADD NAME=UPD_MENU_ClearDefaultMenu
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_ClearDefaultMenu
//
//  PURPOSE:    To go to the previous menu in the dialog
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_ClearDefaultMenu( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( SetCursorFirstEntity( vDialog, "DfltMenu", 0 ) == zCURSOR_SET )
   {
      ExcludeEntity( vDialog, "DfltMenu", zREPOS_NONE );
   }

   return( 0 );
}

//./ ADD NAME=UPD_MENU_SetClearDefaultMenu
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_SetClearDefaultMenu
//
//  PURPOSE:    To either Set or Unset Default Menu based on CheckBox
//              This operation is performed when the checkbox changes
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_SetClearDefaultMenu( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( GetCtrlState( vSubtask, "DefaultCheckBox",
                      zCONTROL_STATUS_CHECKED ) == TRUE )
   {
      UPD_MENU_SetDefaultMenu( vSubtask );
   }
   else
   {
      UPD_MENU_ClearDefaultMenu( vSubtask );
   }

   return( 0 );
}

//./ ADD NAME=UPD_MENU_MenuPrev
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_MenuPrev
//
//  PURPOSE:    To go to the previous menu in the dialog
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MenuPrev( zVIEW vSubtask )
{
   zVIEW  vOptions;
   zVIEW  vDialog;
   zVIEW  vOptionList;

   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   AcceptSubobject( vDialog, "Menu" );
   if ( SetCursorPrevEntity( vDialog, "Menu", 0 ) == zCURSOR_SET )
   {
      SetViewFromView( vOptions, vDialog );
      fnBuildOptionList( vSubtask, vDialog, &vOptionList );
   }

   CreateTemporalSubobjectVersion( vDialog, "Menu" );

   return( 0 );
}

//./ ADD NAME=UPD_MENU_MenuNext
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_MenuNext
//
//  PURPOSE:    To go to the next menu in the dialog
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MenuNext( zVIEW vSubtask )
{
   zVIEW  vOptions;
   zVIEW  vDialog;
   zVIEW  vOptionList;

   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );
   AcceptSubobject( vDialog, "Menu" );
   if ( SetCursorNextEntity( vDialog, "Menu", 0 ) == zCURSOR_SET )
   {
      SetViewFromView( vOptions, vDialog );
      fnBuildOptionList( vSubtask, vDialog, &vOptionList );
   }
   CreateTemporalSubobjectVersion( vDialog, "Menu" );
   return( 0 );
}

//./ ADD NAME=UPD_MENU_MenuAdd
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_MenuAdd
//
//  PURPOSE:    To add a menu to the dialog
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MenuAdd( zVIEW vSubtask )
{
   zVIEW  vOptions;
   zVIEW  vDialog;
   zVIEW  vOptionList;

   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vDialog, "Menu" ) == zCURSOR_SET )
      AcceptSubobject( vDialog, "Menu" );
   CreateTemporalMetaEntity( vSubtask, vDialog, "Menu", zPOS_AFTER );
   SetAttributeFromString( vDialog, "Menu", "Tag", "New Menu");
   SetViewFromView( vOptions, vDialog );
   CreateMetaEntity( vSubtask, vOptions, "Option", zPOS_AFTER );
   SetAttributeFromString( vOptions, "Option", "Tag", "File" );
   SetAttributeFromString( vOptions, "Option", "Text", "&File..." );
   fnBuildOptionList( vSubtask, vDialog, &vOptionList );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_MoveOptions
//
//  PURPOSE:    To Move an item up in the menu bar
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MoveOptions( zVIEW  vSubtask,
                      zVIEW  NewWO,
                      zVIEW  OrigWO,
                      zSHORT nPosition )
{
   zSHORT   nRC;
   zSHORT   RESULT;

   nRC = CreateMetaEntity( vSubtask, NewWO, "Option", nPosition );
   nRC = SetMatchingAttributesByName( NewWO, "Option", OrigWO,
                                      "Option", zSET_NULL );
   RESULT = SetCursorFirstEntity( OrigWO, "OptOpt", "" );
   if ( RESULT > zCURSOR_UNCHANGED )
   {
      SetViewToSubobject( OrigWO, "OptOpt" );
      SetViewToSubobject( NewWO, "OptOpt" );
      while ( RESULT > zCURSOR_UNCHANGED )
      {
         IncludeSubobjectFromSubobject( NewWO, "Option",
                                        OrigWO, "Option", zPOS_AFTER );
         /*
         IncludeSubobjectFromSubobject( NewWO, "OptOpt", OrigWO,
                                       "OptOpt", zPOS_AFTER );
         */
         if ( CheckExistenceOfEntity( OrigWO, "OptMap" ) == zCURSOR_SET )
            IncludeSubobjectFromSubobject( NewWO, "OptMap",
                                          OrigWO, "OptMap", zPOS_AFTER );
         if ( CheckExistenceOfEntity( OrigWO, "OptAct" ) == zCURSOR_SET )
            IncludeSubobjectFromSubobject( NewWO, "OptAct",
                                          OrigWO, "OptAct", zPOS_AFTER );

         RESULT = SetCursorNextEntity( OrigWO, "Option", "" );
      }

      ResetViewFromSubobject( OrigWO );
      ResetViewFromSubobject( NewWO );
   }
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
oTZPNTRAD_CloneOption( zVIEW    NewWO,
                       zVIEW    NewW,
                       zVIEW    OrigWO,
                       zVIEW    OrigW,
                       zLONG    lPosition,
                       zVIEW    vSubtask )
{
   zSHORT   nRC;
   zSHORT   RESULT;
   zLONG    lTempInteger_0;
   zLONG    lTempInteger_1;
   zCHAR    szTempString_0[ 33 ];

   nRC = CreateMetaEntity( vSubtask, NewWO, "Option", (zSHORT) lPosition );
   nRC = SetMatchingAttributesByName( NewWO, "Option",
                                            OrigWO, "Option", zSET_NULL );
   RESULT = SetCursorFirstEntity( OrigWO, "OptOpt", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   {
      SetViewToSubobject( OrigWO, "OptOpt" );
      SetViewToSubobject( NewWO, "OptOpt" );
      oTZPNTRAD_CloneOption( NewWO, NewW, OrigWO,
                             OrigW, zPOS_AFTER, vSubtask );
      ResetViewFromSubobject( OrigWO );
      ResetViewFromSubobject( NewWO );
      RESULT = SetCursorNextEntity( OrigWO, "OptOpt", "" );
   }

   lTempInteger_0 = CheckExistenceOfEntity( OrigWO, "OptMap" );
   if ( lTempInteger_0 == zCURSOR_SET )
      oTZWDLGSO_CloneOptMap( vSubtask, OrigW, OrigWO, NewW, NewWO, vSubtask );

   lTempInteger_1 = CheckExistenceOfEntity( OrigWO, "OptAct" );
   if ( lTempInteger_1 == zCURSOR_SET )
   {
      if ( CompareAttributeToString( OrigWO, "OptAct", "Tag", "" ) != 0 )
      {
         GetStringFromAttribute( szTempString_0, zsizeof( szTempString_0 ), OrigWO, "OptAct", "Tag" );
         RESULT = SetCursorFirstEntityByString( NewW, "Action", "Tag", szTempString_0, "" );
         if ( RESULT >= 0 )
         {
            IncludeSubobjectFromSubobject( NewWO, "OptAct",
                                           NewW, "Action", zPOS_AFTER );
         }
      }
   }

   return( 0 );
}

//./ ADD NAME=UPD_MENU_MoveUpSameLevel
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_MoveUpSameLevel
//
//  PURPOSE:    To Move an item up in the menu bar
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MoveUpSameLevel( zVIEW vSubtask )
{
   zVIEW  vOptionList;
   zVIEW  vOption;
   zVIEW  vOption2;
   zVIEW  vWindow;
   zLONG  lZKey;

   GetViewByName( &vOption, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWindow, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vOptionList, "Option" ) < zCURSOR_SET )
      return( 0 );

   CreateViewFromViewForTask( &vOption2, vOption, 0 );
   if ( SetCursorPrevEntity( vOption, "Option", 0 ) > zCURSOR_UNCHANGED )
   {
      oTZPNTRAD_CloneOption( vOption, vWindow, vOption2, vWindow,
                             zPOS_BEFORE, vSubtask );
      /*
      UPD_MENU_MoveOptions( vSubtask, vOption, vOption2, zPOS_BEFORE );
      */
      DeleteEntity( vOption2, "Option", zREPOS_PREV );
   }

   DropView( vOption2 );
   fnBuildOptionList( vSubtask, vWindow, &vOptionList );
   GetIntegerFromAttribute( &lZKey, vOption, "Option", "ZKey" );
   SetCursorFirstEntityByInteger( vOptionList, "Option",
                                  "ZKey", lZKey, "" );
   SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );

   return( 0 );
}

//./ ADD NAME=UPD_MENU_MoveDownSameLevel
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_MoveDownSameLevel
//
//  PURPOSE:    To Move an item down in the menu bar
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MoveDownSameLevel( zVIEW vSubtask )
{
   zVIEW  vOptionList;
   zVIEW  vOption;
   zVIEW  vOption2;
   zVIEW  vWindow;
   zLONG  lZKey;

   GetViewByName( &vOption, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWindow, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vOptionList, "Option" ) < zCURSOR_SET )
      return( 0 );

   CreateViewFromViewForTask( &vOption2, vOption, 0 );
   if ( SetCursorNextEntity( vOption, "Option", 0 ) > zCURSOR_UNCHANGED )
   {
      oTZPNTRAD_CloneOption( vOption, vWindow, vOption2, vWindow,
                             zPOS_AFTER, vSubtask );
      /*
      UPD_MENU_MoveOptions( vSubtask, vOption, vOption2, zPOS_AFTER );
      */
      DeleteEntity( vOption2, "Option", zREPOS_PREV );
   }

   DropView( vOption2 );
   fnBuildOptionList( vSubtask, vWindow, &vOptionList );
   GetIntegerFromAttribute( &lZKey, vOption, "Option", "ZKey" );
   SetCursorFirstEntityByInteger( vOptionList, "Option",
                                  "ZKey", lZKey, "" );
   SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );

   return( 0 );
}

//./ ADD NAME=UPD_MENU_MoveUpOneLevel
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_MoveUpOneLevel
//
//  PURPOSE:    To take a menu bar item and move it up one level
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MoveUpOneLevel( zVIEW vSubtask )
{
   zVIEW  vOptionList;
   zVIEW  vOption;
   zVIEW  vOption2;
   zVIEW  vWindow;
   zLONG  lZKey;

   GetViewByName( &vOption, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWindow, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vOptionList, "Option" ) < zCURSOR_SET )
      return( 0 );

   CreateViewFromViewForTask( &vOption2, vOption, 0 );
   if ( ResetViewFromSubobject( vOption ) == zCURSOR_SET )
   {
      oTZPNTRAD_CloneOption( vOption, vWindow, vOption2, vWindow,
                             zPOS_AFTER, vSubtask );
      /*
      UPD_MENU_MoveOptions( vSubtask, vOption, vOption2, zPOS_AFTER );
      */
      DeleteEntity( vOption2, "Option", zREPOS_PREV );
   }

   DropView( vOption2 );
   fnBuildOptionList( vSubtask, vWindow, &vOptionList );
   GetIntegerFromAttribute( &lZKey, vOption, "Option", "ZKey" );
   SetCursorFirstEntityByInteger( vOptionList, "Option",
                                  "ZKey", lZKey, "" );
   SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );

   // return that everything is AOK
   return( 0 );
}

//./ ADD NAME=UPD_MENU_MoveDownOneLevel
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_MoveDownOneLevel
//
//  PURPOSE:    To take a menu bar item and move it down one level
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_MoveDownOneLevel( zVIEW vSubtask )
{
   zVIEW  vOptionList;
   zVIEW  vOption;
   zVIEW  vOption2;
   zVIEW  vWindow;
   zLONG  lZKey;

   GetViewByName( &vOption, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWindow, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vOptionList, "Option" ) < zCURSOR_SET )
      return( 0 );

   CreateViewFromViewForTask( &vOption2, vOption, 0 );
   if ( SetCursorPrevEntity( vOption, "Option", 0 ) > zCURSOR_UNCHANGED )
   {
      SetViewToSubobject( vOption, "OptOpt" );
      oTZPNTRAD_CloneOption( vOption, vWindow, vOption2, vWindow,
                             zPOS_AFTER, vSubtask );
      /*
      UPD_MENU_MoveOptions( vSubtask, vOption, vOption2, zPOS_BEFORE );
      */
      DeleteEntity( vOption2, "Option", zREPOS_PREV );
   }

   DropView( vOption2 );
   fnBuildOptionList( vSubtask, vWindow, &vOptionList );
   GetIntegerFromAttribute( &lZKey, vOption, "Option", "ZKey" );
   SetCursorFirstEntityByInteger( vOptionList, "Option",
                                  "ZKey", lZKey, "" );
   SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );

   // return that everything is AOK
   return( 0 );
}

//./ ADD NAME=UPD_MENU_OptionAdd
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_OptionAdd
//
//  PURPOSE:    To add an Option entry into the menu bar
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_OptionAdd( zVIEW vSubtask )
{
   zVIEW   vOptions;
   zVIEW   vDialog;
   zVIEW   vOptionList;
   zVIEW   vTmpOptions;
   zVIEW   vRecursOptions;
   zSHORT  nWork;
   zUSHORT uLevel;
   zLONG   lZKey;
   zBOOL   bTagFound;
   zCHAR   szTag[ 10 ];
   zCHAR   szEntityName[ 33 ];
   static zCHAR  szWork[ 6 ];
   zSHORT  nRC;

   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // Go down a level, if an Option exists, and set cursor on last
   // entry.
   if ( CheckExistenceOfEntity( vOptions, "Option" ) >= 0 )
   {
      SetViewToSubobject( vOptions, "OptOpt" );
      SetCursorLastEntity( vOptions, "Option", "" );
   }

   CreateMetaEntity( vSubtask, vOptions, "Option", zPOS_AFTER );
   SetAttributeFromString( vOptions, "Option", "Text", "New" );

   // Get the tag
   CreateViewFromViewForTask( &vTmpOptions, vOptions, 0 );
   while ( ResetViewFromSubobject( vTmpOptions ) == 0 )
   {
   }

   CreateViewFromViewForTask( &vRecursOptions, vTmpOptions, 0 );

   for ( nWork = 1; nWork < 1000; nWork++ )
   {
      zltoa( nWork, szWork, zsizeof( szWork ) );

      strcpy_s( szTag, zsizeof( szTag ), "New" );
      strcat_s( szTag, zsizeof( szTag ), szWork );

      SetViewFromView( vRecursOptions, vTmpOptions );
      // Now make sure that the tag is unique
      bTagFound = 0;
      DefineHierarchicalCursor( vRecursOptions, "Menu" );
      nRC = SetCursorNextEntityHierarchical( &uLevel,
                                             szEntityName, vRecursOptions );
      while ( nRC >= zCURSOR_SET && uLevel > 3 )
      {
         if ( nRC == zCURSOR_SET_RECURSIVECHILD )
         {
            SetViewToSubobject( vRecursOptions, "OptOpt" );
         }
         if ( CompareAttributeToString( vRecursOptions, "Option",
                                        "Tag", szTag ) == 0 )
         {
            bTagFound = 1;
            break;
         }
         nRC = SetCursorNextEntityHierarchical( &uLevel,
                                                szEntityName, vRecursOptions );
      }

      DropHierarchicalCursor( vRecursOptions );
      if ( bTagFound == FALSE )
         break;
   }

   DropView( vTmpOptions );
   DropView( vRecursOptions );
   SetAttributeFromString( vOptions, "Option", "Tag", szTag );

   fnBuildOptionList( vSubtask, vDialog, &vOptionList );

   // Highlight correct line
   GetIntegerFromAttribute( &lZKey, vOptions, "Option", "ZKey" );
   SetCursorFirstEntityByInteger( vOptionList, "Option",
                                  "ZKey", lZKey, "" );
   SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );

   return( 0 );
}

//./ ADD NAME=UPD_MENU_OptionSelect
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_OptionSelect
//
//  PURPOSE:    To select a menu bar entry in the list by mouse
//              single-click
//              Position on the Window Option that corresponds to
//              the work Option selected.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_OptionSelect( zVIEW vSubtask )
{
   zVIEW  vOptionList;
   zVIEW  vOptions;
   zVIEW  vDialog;
   zLONG  lZKey;

   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vOptionList, "Option" ) != 0 )
      return( 0 );

   // Position on the current Option
   fnPositionOnZeidonOption( vOptions, vOptionList, vSubtask );

   // Because OptionList was rebuilt, position has to be reset to the
   // current option.
   GetIntegerFromAttribute( &lZKey, vOptions, "Option", "ZKey" );
   SetCursorFirstEntityByInteger( vOptionList, "Option",
                                  "ZKey", lZKey, "" );
   SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );
   return( 0 );
}

//./ ADD NAME=UPD_MENU_OptionUpdate
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_OptionUpdate
//
//  PURPOSE:    To select a menu bar entry in the list by mouse
//              double-click
//              Position on the Window Option that corresponds to
//              the work Option selected and transfer to the
//              Option Update window.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_OptionUpdate( zVIEW vSubtask )
{
   zVIEW  vOptions;
   zVIEW  vOptionList;

   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK ) == -1 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( 0 );
   }

//   UPD_MENU_OptionSelect( vSubtask );
   CreateTemporalSubobjectVersion( vOptions, "Option" );

   return( 0 );
}


/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: OPT_UPD_NextMenuItem
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
OPT_UPD_NextMenuItem( zVIEW vSubtask )
{
   zVIEW  vOptionList;
   zVIEW  vOptions;
   zVIEW  vParentWindow;

   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   if ( OPT_UPD_OK( vSubtask ) >= 0 )
   {
      UPD_MENU_ReturnFromSubWindow( vSubtask );
      GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
      SetSelectStateOfEntityForSet( vOptionList, "Option", 0, 1 );

      SetCursorNextEntity( vOptionList, "Option", "" );
      // Position on the current Option
      fnPositionOnZeidonOption( vOptions, vOptionList, vSubtask );
      SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );

      UPD_MENU_OptionUpdate( vSubtask );
      OPT_UPD_Init( vSubtask );
      OPT_UPD_DisableActionButton( vSubtask );
      GetParentWindow( &vParentWindow, vSubtask );
      RefreshWindow( vParentWindow );
      SetFocusToCtrl( vSubtask, "Tag" );
   }

   return( 0 );
} // OPT_UPD_NextMenuItem


/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: OPT_UPD_PrevMenuItem
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
OPT_UPD_PrevMenuItem( zVIEW vSubtask )
{
   zVIEW  vOptionList;
   zVIEW  vOptions;
   zVIEW  vParentWindow;

   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );

   if ( OPT_UPD_OK( vSubtask ) >= 0 )
   {
      UPD_MENU_ReturnFromSubWindow( vSubtask );
      GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
      SetSelectStateOfEntityForSet( vOptionList, "Option", 0, 1 );

      SetCursorPrevEntity( vOptionList, "Option", "" );
      // Position on the current Option
      fnPositionOnZeidonOption( vOptions, vOptionList, vSubtask );
      SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );

      UPD_MENU_OptionUpdate( vSubtask );
      OPT_UPD_Init( vSubtask );
      OPT_UPD_DisableActionButton( vSubtask );
      GetParentWindow( &vParentWindow, vSubtask );
      RefreshWindow( vParentWindow );
      SetFocusToCtrl( vSubtask, "Tag" );
   }

   return( 0 );
} // OPT_UPD_PrevMenuItem



//./ ADD NAME=UPD_MENU_OptionDelete
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_OptionDelete
//
//  PURPOSE:    To delete a menu bar Option entry.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_OptionDelete( zVIEW vSubtask )
{
   zVIEW  vOptions;
   zVIEW  vDialog;
   zVIEW  vOptionList;
   zLONG  lZKey;
   zCHAR  szMenuItem[ 33 ];
   zCHAR  szMsg[ 100 ];

   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szMenuItem, zsizeof( szMenuItem ), vOptions, "Option", "Text" );
   strcpy_s( szMsg, zsizeof( szMsg ), "OK to delete Menu Item '" );
   strcat_s( szMsg, zsizeof( szMsg ), szMenuItem );
   strcat_s( szMsg, zsizeof( szMsg ), "'" );
   // check SubItems
   if ( CheckExistenceOfEntity( vOptions, "OptOpt" ) >= zCURSOR_SET )
      strcat_s( szMsg, zsizeof( szMsg ), " with all Subitems?" );
   else
      strcat_s( szMsg, zsizeof( szMsg ), "?" );

   if ( MessagePrompt( vSubtask, "", "Dialog Maintenance",
                       szMsg, 0, zBUTTONS_YESNO, zRESPONSE_NO,
                       zICON_QUESTION ) == zRESPONSE_NO )
   {
      return( 0 );
   }

   DeleteEntity( vOptions, "Option", zPOS_PREV );

   // If there are no Options at this level, reset the view back a
   // level.
   if ( CheckExistenceOfEntity( vOptions, "Option" ) < 0 )
      ResetViewFromSubobject( vOptions );

   fnBuildOptionList( vSubtask, vDialog, &vOptionList );
   // If any option exists, position on that option in the OptionList.
   if ( CheckExistenceOfEntity( vOptions, "Option" ) == 0 )
   {
      GetIntegerFromAttribute( &lZKey, vOptions, "Option", "ZKey" );
      SetCursorFirstEntityByInteger( vOptionList, "Option",
                                     "ZKey", lZKey, "" );
      SetSelectStateOfEntityForSet( vOptionList, "Option", 1, 1 );
   }

   return( 0 );
}


//./ ADD NAME=UPD_MENU_OK
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_OK
//
//  PURPOSE:    To save the results of the menu bar editing
//              and delete the work object.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_OK( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vDialogCopy;
   zSHORT nRC;
   zCHAR  szTag[ 33 ];

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( CompareAttributeToString( vDialog, "Menu", "Tag", "" ) == 0 )
   {
      MessageSend( vSubtask, "PN00205", "Dialog Maintenance",
                   "Menu Name is required.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "MenuName" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      return( -1 );
   }

   CreateViewFromViewForTask( &vDialogCopy, vDialog, 0 );
   GetStringFromAttribute( szTag, zsizeof( szTag ), vDialog, "Menu", "Tag" );
   nRC = SetCursorFirstEntityByString( vDialogCopy, "Menu", "Tag", szTag, "" );
   nRC = SetCursorNextEntityByString( vDialogCopy, "Menu", "Tag", szTag, "" );
   DropView( vDialogCopy );
   if ( nRC >= zCURSOR_SET )
   {
      MessageSend( vSubtask, "PN00205", "Dialog Maintenance",
                   "The Menu Name is not unique within this window.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "MenuName" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      return( -1 );
   }

   if ( CheckExistenceOfEntity( vDialog, "Option" ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "PN00206", "Dialog Maintenance",
                   "Menu Item for Menu is required.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      return( -1 );
   }

   nRC = AcceptSubobject( vDialog, "Menu" );
   SetSelectStateOfEntity( vDialog, "Menu", 1 );

   fnPainterCall( zMSG_REPAINTACTIONBAR, vSubtask, 0, 0, 0 );
   SetWindowActionBehavior( vSubtask, zWAB_ReturnToParentWithRefresh |
                                      zWAB_ProcessImmediateReturn, 0, 0 );

   SetCursorFirstSelectedEntity( vDialog, "Menu", "" );
   return( 0 );
}

//./ ADD NAME=UPD_MENU_Delete
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_Delete
//
//  PURPOSE:    To delete a Menu entry from the Window
//              If the last Menu entry was just deleted, you'll
//              just stay on this window with everything grayed, except
//              the Add Menu button.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_Delete( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vOptionList;
   zVIEW  vOptions;

   GetViewByName( &vOptions, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOptionList, "TZPNOPWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vDialog, "Menu" ) >= 0 )
   {
      DeleteEntity( vDialog, "Menu", zPOS_AFTER );
      SetViewFromView( vOptions, vDialog );
      fnBuildOptionList( vSubtask, vDialog, &vOptionList );
   }

   return( 0 );
}

//./ ADD NAME=UPD_MENU_Cancel
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UPD_MENU_Cancel
//
//  PURPOSE:    To cancel the results of the menu bar editing
//              Also delete the work object.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UPD_MENU_Cancel( zVIEW vSubtask )
{
   zVIEW vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   CancelSubobject( vDialog, "Menu" );

   return( 0 );
}

//./ ADD NAME=LIST_HK_Prebuild
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      LIST_HK_Prebuild
//
//  PURPOSE:    Set Caption
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
LIST_HK_Prebuild( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zCHAR szTempString[ 255 ];

   // Set the caption for the window
   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      GetStringFromAttribute( szTempString, zsizeof( szTempString ), vDialog, "Window", "Tag" );
      SetWindowCaptionTitle( vSubtask, 0, szTempString );
   }
   else
      SetWindowCaptionTitle( vSubtask, 0, "" );

   return( 0 );
}

//./ ADD NAME=NewHotkey
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      NewHotkey
//
//  PURPOSE:    To create a new hotkey specification.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
NewHotkey( zVIEW vSubtask )
{
   zACCEL_DEF ac;
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   CreateTemporalMetaEntity( vSubtask, vDialog, "Hotkey", zPOS_AFTER );
   SetAttributeFromString( vDialog, "Hotkey", "Tag", "New" );
   ac.fCtrl = 0;
   ac.fAlt = 0;
   ac.fShift = 0;
   ac.uVK = 112;
   SetAttributeFromInteger( vDialog, "Hotkey", "VKey", ac.uVK );
   SetAttributeFromBlob( vDialog, "Hotkey", "KeyCombo", &ac, sizeof( zACCEL_DEF ) );
   return( 0 );
}

//./ ADD NAME=DeleteHotkey
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DeleteHotkey
//
//  PURPOSE:    To delete a hotkey specification.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DeleteHotkey( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vWindow;
   zSHORT nRC;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( MessagePrompt( vSubtask, "PE002",
                       "Dialog Maintenance",
                       "OK to delete selected Shortcut Keys?",
                       zBEEP, zBUTTONS_YESNO,
                       zRESPONSE_NO,  0 ) == zRESPONSE_YES )
   {
      for ( nRC = SetCursorFirstSelectedEntity( vDialog, "Hotkey", "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextSelectedEntity( vDialog, "Hotkey", "" ) )
      {
         DeleteEntity( vDialog, "Hotkey", zREPOS_NONE );
      }
      if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_HK" ) >= 0 )
         RefreshWindow( vWindow );
   }
   return( 0 );
}


//./ ADD NAME=ShowHotkey
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ShowHotkey
//
//  PURPOSE:    To show the breakdown of the key combo components
//              for a hotkey.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
ShowHotkey( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zACCEL_DEF ac;
   zULONG  ulLth = sizeof( zACCEL_DEF );

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   GetBlobFromAttribute( &ac, &ulLth, vDialog, "Hotkey", "KeyCombo" );
   SetCtrlState( vSubtask, "Ctrl", zCONTROL_STATUS_CHECKED, ac.fCtrl );
   SetCtrlState( vSubtask, "Alt", zCONTROL_STATUS_CHECKED, ac.fAlt );
   SetCtrlState( vSubtask, "Shift", zCONTROL_STATUS_CHECKED, ac.fShift );

   if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
   {
      SetCtrlState( vSubtask, "Ctrl", zCONTROL_STATUS_ENABLED, 0 );
      SetCtrlState( vSubtask, "Alt", zCONTROL_STATUS_ENABLED, 0 );
      SetCtrlState( vSubtask, "Shift", zCONTROL_STATUS_ENABLED, 0 );
   }

   return( 0 );
}

//./ ADD NAME=InitVkey
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      InitVkey
//
//  PURPOSE:    To set the VKey attribute from the KeyCombo blob
//              for a hotkey.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
InitVkey( zVIEW vSubtask )
{
   zVIEW      vDialog;
   zVIEW      vDialogCopy;
   zVIEW      vWindow;
   zACCEL_DEF ac;
   zCHAR      szTempString[ 256 ];
   zSHORT     nRC;
   zULONG     ulLth = sizeof( zACCEL_DEF );

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // Shortcut List is a multi selection list, delesect all Shortcuts
   CreateViewFromViewForTask( &vDialogCopy, vDialog, 0 );
   for ( nRC = SetCursorFirstSelectedEntity( vDialog, "Hotkey", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextSelectedEntity( vDialog, "Hotkey", "" ) )
   {
      SetSelectStateOfEntity( vDialog, "Hotkey", 0 );
   }
   SetCursorFirstEntityByAttr( vDialog, "Hotkey", "ZKey",
                               vDialogCopy, "Hotkey", "ZKey", "" );
   DropView( vDialogCopy );
   SetSelectStateOfEntity( vDialog, "Hotkey", 1 );

   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_HK" ) >= 0 )
      RefreshCtrl( vWindow, "lbHotkey" );

   GetBlobFromAttribute( &ac, &ulLth, vDialog, "Hotkey", "KeyCombo" );
   SetAttributeFromInteger( vDialog, "Hotkey", "VKey", ac.uVK );

   // Put the window name in the caption.
   GetStringFromAttribute( szTempString, zsizeof( szTempString ), vDialog, "Window", "Tag");
   SetWindowCaptionTitle( vSubtask, 0, szTempString );

   return( 0 );
}

//./ ADD NAME=SetHotkey
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SetHotkey
//
//  PURPOSE:    To set the key combo from its components.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SetHotkey( zVIEW vSubtask )
{
   zACCEL_DEF ac;
   zVIEW  vDialog;
   zLONG  lVKey;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // check for null value
   if ( CompareAttributeToString( vDialog, "Hotkey", "VKey", "" ) == 0 )
   {
      MessageSend( vSubtask, "PN00207", "Dialog Maintenance",
                   "No Key selected.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "VKey" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( 0 );
   }

   AcceptSubobject( vDialog, "Hotkey" );
   ac.fCtrl = (zUSHORT) GetCtrlState( vSubtask, "Ctrl",
                                      zCONTROL_STATUS_CHECKED );
   ac.fAlt = (zUSHORT) GetCtrlState( vSubtask, "Alt",
                                     zCONTROL_STATUS_CHECKED );
   ac.fShift = (zUSHORT) GetCtrlState( vSubtask, "Shift",
                                       zCONTROL_STATUS_CHECKED );
   GetIntegerFromAttribute((zPLONG) &lVKey, vDialog, "Hotkey", "VKey" );
   ac.uVK = (zUSHORT) lVKey;
   SetAttributeFromBlob( vDialog, "Hotkey", "KeyCombo",
                         &ac, sizeof( zACCEL_DEF ) );
   return( 0 );
}

//./ ADD NAME=RetrieveMetaList
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      RetrieveMetaList
//
//  PURPOSE:    To insure a view to the meta list is available for
//              file open.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
RetrieveMetaList( zVIEW vSubtask )
{
   zVIEW vTZDIALOGS;
   zVIEW vTZWINDOWL;

   // Obtain list of Dialog's and position on the current Dialog if there is
   // one active.
   if ( GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK ) < 1 )
   {
      RetrieveViewForMetaList( vSubtask, &vTZDIALOGS, zREFER_DIALOG_META );
      SetNameForView( vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   }

   if ( GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) >= 0 &&
        CheckExistenceOfEntity( vTZWINDOWL, "Dialog" ) >= zCURSOR_SET )
   {
      // If Dialog open, then set cursor to it.
      SetCursorFirstEntityByAttr( vTZDIALOGS, "W_MetaDef", "Name",
                                  vTZWINDOWL, "Dialog", "Tag", "" );
   }
   else
   {
      OrderEntityForView( vTZDIALOGS, "W_MetaDef", "LastUpdateDate D" );
      SetCursorFirstEntity( vTZDIALOGS, "W_MetaDef", "" );
   }

// MessageBox( 0, "Check cursor position of TZDIALOGS", "TZPNTRAD.C", MB_OK );
   return( 0 );
}

//./ ADD NAME=CHG_CTRL_Prebuild
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CHG_CTRL_Prebuild
//
//  PURPOSE:    Setup for switching the type of a control in the painter
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
CHG_CTRL_Prebuild( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vPE;
   zSHORT nRC;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) <= 0 ||
        GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      TraceLineS( "CHG_CTRL_Prebuild unable to get required views", "" );
      return( -1 );
   }

   /* If there were no controls on the window and the user just created some
      and then immediately selected one and hit the toolbar change button,
      for whatever reason vDialog shows no controls under it yet and so
      we must call ACTIVATEPAINTERWINDOW which creates the Zeidon info. */
// if ( CheckExistenceOfEntity( vDialog, "Control" ) != 0 )
      fnPainterCall( zMSG_ACTIVATEPAINTERWINDOW, vSubtask, 0, 0, 0 );
// fnPainterCall( zMSG_ENABLEPAINTERWINDOWS, vSubtask, 0, 0, 0 );

   nRC = SetCursorFirstEntityByEntityCsr( vPE, "ControlDef",
                                          vDialog, "ControlDef", "" );
   return( 0 );
}

//./ ADD NAME=LIST_CTRL_EventsActs
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
// ENTRY:   LIST_CTRL_EventsActs
//
// PURPOSE: Setup for resetting Event/Action combinations in the painter:
//
//          1. Sets up the Outliner work attributes from CtrlBOI.
//          2. Initializes the TZPNEVWO Event work object as
//             necessary. (*** This shouldn't be necessary if the
//             Painter was always functioning correctly.  Remove and
//             test at some point.)
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT
fnIncludeCtrlMapViews( zVIEW vTopCtrl, zVIEW vControl )
{
   zSHORT nRC;

   nRC = SetCursorFirstEntity( vControl, "Control", 0 );
   while ( nRC == zCURSOR_SET )
   {
      IncludeSubobjectFromSubobject( vControl, "CtrlMapView",
                                     vTopCtrl, "CtrlMapView", zPOS_AFTER );

      SetViewToSubobject( vControl, "CtrlCtrl" );
      fnIncludeCtrlMapViews( vTopCtrl, vControl );
      ResetViewFromSubobject( vControl );

      nRC = SetCursorNextEntity( vControl, "Control", 0 );
   }

   return( 0 );
}

zSHORT
fnSetOutliner( zVIEW vSubtask )
{
   zVIEW    vTopCtrl;
   zVIEW    vControl;

   GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );

   /* recursive function to fix the CtrlCtrl's */
   CreateViewFromViewForTask( &vTopCtrl, vControl, 0 );
   SetViewToSubobject( vControl, "CtrlCtrl" );
   fnIncludeCtrlMapViews( vTopCtrl, vControl );

   DropView( vTopCtrl );
   ResetViewFromSubobject( vControl );
   ResetView( vControl );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
UPD_CTRL_TreeList( zVIEW vSubtask )
{
   zVIEW  vCtrlCtrl;     // the dialog control view

   GetViewByName( &vCtrlCtrl, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vCtrlCtrl, vCtrlCtrl, 0 );
   SetNameForView( vCtrlCtrl, "TZCONTROLL", vSubtask, zLEVEL_TASK );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
UPD_CTRL_PreSelectChange( zVIEW vSubtask )
{
// zVIEW  vCtrlCtrl;     // the dialog control view
//
// GetViewByName( &vCtrlCtrl, "TZCONTROLL", vSubtask, zLEVEL_TASK );
// DisplayEntityInstance( vCtrlCtrl, "Control" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
UPD_CTRL_SelectChange( zVIEW vSubtask )
{
// zVIEW  vCtrlCtrl;     // the dialog control view
//
// GetViewByName( &vCtrlCtrl, "TZCONTROLL", vSubtask, zLEVEL_TASK );
// DisplayEntityInstance( vCtrlCtrl, "Control" );
   RefreshCtrl( vSubtask, "Text" );
   RefreshCtrl( vSubtask, "Tag" );
   RefreshCtrl( vSubtask, "PosX" );
   RefreshCtrl( vSubtask, "PosY" );
   RefreshCtrl( vSubtask, "SizeX" );
   RefreshCtrl( vSubtask, "SizeY" );
   RefreshCtrl( vSubtask, "View" );
   RefreshCtrl( vSubtask, "Entity" );
   RefreshCtrl( vSubtask, "Attr" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
LIST_CTRL_EventsActs( zVIEW vSubtask )
{
   return( fnSetOutliner( vSubtask ) );

#if 0
   zVIEW    vDialogA;
   zVIEW    vDialogC;
   zVIEW    vDialogW;
   zVIEW    vWork;

   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogC, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );

   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "C" );

   fnPainterCall( zMSG_ACTIVATEPAINTERWINDOW, vSubtask, 0, 0, 0 );

   if ( GetViewByName( &vDialogA, "TZACTION", vSubtask, zLEVEL_TASK ) >= 0 )
      DropView( vDialogA );

   // If an Action for the Event exists, position on the linked Action
   // instance and set TZACTION to TZWINDOW.
   if ( CheckExistenceOfEntity( vDialogC, "EventAct" ) == zCURSOR_SET )
   {
      CreateViewFromViewForTask( &vDialogA, vDialogW, 0 );
      SetCursorFirstEntityByAttr( vDialogA, "Action", "Tag",
                                  vDialogC, "EventAct", "Tag", "" );
      SetNameForView( vDialogA, "TZACTION", vSubtask, zLEVEL_TASK );
   }
   else
   {
      // If not, set TZACTION to empty instance for auto graying.
      fnCreateEmptyActionView( vSubtask, vDialogW );
      /*
      ActivateEmptyObjectInstance( &vDialogA, 0, vDialogW, zSINGLE );
      SetNameForView( vDialogA, "TZACTION", vSubtask, zLEVEL_TASK );
      */
   }

   if ( CheckExistenceOfEntity( vDialogC, "Event" ) != zCURSOR_SET )
   {
//    GetViewByName( &vWork, "TZPACTLO", vSubtask, zLEVEL_TASK );
//    SetCursorFirstEntityByString( vWork, "Control", "Tag", "Outliner", "" );
//    do
      {
         CreateEntity( vDialogC, "Event", zPOS_AFTER );
         SetAttributeFromInteger( vDialogC, "Event", "ZKey", 5044371 );
         SetAttributeFromInteger( vDialogC, "Event", "Type", 1 );
//       SetAttributeFromAttribute( vDialogC, "Event", "Tag",
//                                  vWork, "Event", "Tag" );
//       SetAttributeFromAttribute( vDialogC, "Event", "Type",
//                                  vWork, "Event", "Type" );
      }
//    while ( SetCursorNextEntity( vWork, "Event", "" ) == zCURSOR_SET );
   }

   return( 0 );
#endif
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    LIST_CTRL_SelectAction
//
// PURPOSE:  This function creates the Event entity for the Push
//           Button, if it doesn't already exist.
//           **** Note that we should use Create Temporal entity. ***
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
LIST_CTRL_SelectAction( zVIEW vSubtask )
{
   zVIEW    vDialogC;
   zVIEW    vDialogW;
   zVIEW    vWork;

   GetViewByName( &vDialogC, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vDialogC, "Event" ) != zCURSOR_SET )
   {
      CreateTemporalMetaEntity( vSubtask, vDialogC, "Event", zPOS_AFTER );
      SetAttributeFromInteger( vDialogC, "Event", "Type", 1 );
   }
   if ( CheckExistenceOfEntity( vDialogC, "EventAct" ) == zCURSOR_SET )
   {
      SetCursorFirstEntityByAttr( vDialogW, "Action", "Tag",
                                  vDialogC, "EventAct", "Tag", "" );
   }

   // Set flag for LIST_ACT window graying and Action include for Control.
   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "C" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:      LIST_CTRL_ReturnFromSub
//
// PURPOSE:    Make sure TZACTION is the View for the Action just
//             selected.  TZACTION to be a null View, if no EventAct
//             existed prior to the Select.
//             Also drop the TZACTION View if it is null.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
LIST_CTRL_ReturnFromSub( zVIEW vSubtask )
{
   zVIEW    vDialogC;
   zVIEW    vDialogW;
   zVIEW    vDialogA;
   zVIEW    vEvent;

   GetViewByName( &vDialogC, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogA, "TZACTION", vSubtask, zLEVEL_TASK );

   // If an Action for the Event exists, position on the linked Action
   // instance and set TZACTION to TZWINDOW.
   if ( CheckExistenceOfEntity( vDialogC, "EventAct" ) == zCURSOR_SET )
   {
      // Drop TZACTION work OI, if it is empty.
      if ( CheckExistenceOfEntity( vDialogA, "Window" ) != zCURSOR_SET )
         DropObjectInstance( vDialogA );

      CreateViewFromViewForTask( &vDialogA, vDialogW, 0 );
      SetCursorFirstEntityByAttr( vDialogA, "Action", "Tag",
                                  vDialogC, "EventAct", "Tag", "" );
      SetNameForView( vDialogA, "TZACTION", vSubtask, zLEVEL_TASK );

      // Update Event/Action list.
      GetViewByName( &vEvent, "TZPNEVWO", vSubtask, zLEVEL_TASK );
      SetAttributeFromAttribute( vEvent, "EventAct", "Tag",
                                 vDialogC, "EventAct", "Tag" );
   }

   return( 0 );
}

//./ ADD NAME=SwitchLPLR
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:     SwitchLPLR
//
//  PURPOSE:   To switch to a new project library, simply drop
//             our local view for the dialog object TZDIALOGS
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SwitchLPLR( zVIEW vSubtask )
{
   zVIEW vTZDIALOGS;
   zVIEW vTZPESRCO;
   zVIEW vSaveAs;
   zSHORT nRC;

   // Ask and do save
   nRC = AskForSave( vSubtask);

   if ( nRC )
   {
      if ( GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK ) > 0 )
      {
         if ( nRC == 99 )
         {
            // if Dialog not checked out and user change this Dialog, then zeidon
            // call the window "Save Dialog as"
            // We save the action after Save as in the View TZSAVEAS (for example:
            // Create new Dialog or Open an other Dialog or Switch Project or
            // Exit Dialog Tool)
            SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                                     zSwitchLPLRAfterSaveAs );
         }
         else
         {
            SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                                     zNoActionAfterSaveAs );
            if ( nRC < 0 || nRC == zRESPONSE_CANCEL )
               return( 0 );
         }
      }
   }

   // Send in flag to force reload of task view for LPLR.
   fnPainterCall( zMSG_DELETEALLPAINTERWINDOWS, vSubtask, 0, (zPCHAR) 1, 0 );
   if ( GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK ) > 0 )
      DropView( vTZDIALOGS );

   //BL, 2000.01.26 drop View for Dialog list in Window ACTION DETAIL.
   if ( GetViewByName( &vTZDIALOGS, "TZDLG_List", vSubtask, zLEVEL_TASK ) > 0 )
      DropView( vTZDIALOGS );

   if ( GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK ) > 0 )
      DropView( vTZPESRCO );

   // This SetName causes the list of dialogs to be presented after the
   // switch LPLR completes.
   SetNameForView( vSubtask, "__SysIdlePainter", 0, zLEVEL_SYSTEM );

   return( 0 );
}

//./ ADD NAME=SystemMinimize
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SystemMinimize
//
//  PURPOSE:    Called when painter is minimized, tell painter to
//              minimize all windows being painter
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SystemMinimize( zVIEW vSubtask )
{
   zVIEW vDialog;
   zVIEW vIdleView;

   TraceLineS("(tzpntrad) - SystemMinimize","");

   fnPainterCall( zMSG_SYSTEMMINIMIZE, vSubtask, 0, 0, 0 );
   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) < 1 )
   {
      if ( GetViewByName( &vIdleView, "__SysIdlePainter", vSubtask, zLEVEL_SYSTEM ) < 1 )
      {
         SetWindowCaptionTitle( vSubtask, "Painter", "[Idle]" );
         SetNameForView( vSubtask, "__SysIdlePainter", 0, zLEVEL_SYSTEM );
      }
   }

   return( 0 );
}

//./ ADD NAME=SystemActivate
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SystemActivate
//
//  PURPOSE:    Called when painter is restored or maximized, restore
//              all painter windows
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SystemActivate( zVIEW vSubtask )
{
   zVIEW    vDialog;
   zVIEW    vKZWDLGXO;
   zVIEW    vIdleView;
   zVIEW    vTaskLPLR;
   zVIEW    vWindowList = 0;
   zCHAR    szWorkString[ 256 ];

// TraceLineS( "(tzpntrad) - SystemActivate", "" );

   if ( GetViewByName( &vKZWDLGXO,
                       "__SysPainterHotkey", vSubtask, zLEVEL_SYSTEM ) > 0 &&
        GetViewByName( &vIdleView,
                       "__SysIdlePainter", vSubtask, zLEVEL_SYSTEM ) > 0 &&
        vIdleView == vSubtask )
   {
      // The driver is trying to hotkey to us, see if we have an LPLR and
      // an open dialog already up.
      if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) > 0 )
      {
         GetApplDirectoryFromView( szWorkString, vKZWDLGXO, zAPPL_NAME,
                                   zsizeof( szWorkString ) - 1 );
         if ( CompareAttributeToString( vTaskLPLR, "LPLR", "Name",
                                        szWorkString ) == 0 )
         {
            if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) > 0 )
            {
               if ( CompareAttributeToAttribute( vDialog, "Dialog", "Tag",
                                vKZWDLGXO, "Dlg", "Tag" ) == 0 )
               {
                  DropNameForView( vKZWDLGXO, "__SysPainterHotkey",
                                   0, zLEVEL_SYSTEM );
                  SetNameForView( vKZWDLGXO, "__SysPainterHotkey",
                                  vSubtask, zLEVEL_TASK );
                  DropNameForView( vSubtask, "__SysIdlePainter",
                                   0, zLEVEL_SYSTEM );
                  GetStringFromAttribute( szWorkString, zsizeof( szWorkString ),
                                          vKZWDLGXO, "Wnd", "Tag" );
                  GetViewByName( &vWindowList, "TZWINDOWL", vSubtask, zLEVEL_TASK );
                  if ( SetCursorFirstEntityByString( vWindowList,
                       "Window", "Tag", szWorkString, 0 ) >= zCURSOR_SET )
                  {
                     fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, szWorkString, zsizeof( szWorkString ) );
//                   UpdateWindowFromList( vSubtask );
                  }

                  return( 0 );
               }
               else
                  DropMetaOI( vSubtask, vDialog );
            }
         }
         else
         {
            if ( GetViewByName( &vDialog, "TZDIALOGS", vSubtask, zLEVEL_TASK ) > 0 )
               DropView( vDialog );

            if ( GetViewByName( &vDialog, "TZPESRCO", vSubtask, zLEVEL_TASK ) > 0 )
               DropView( vDialog );

            TerminateLPLR( vSubtask );
            if ( GetViewByName( &vDialog, "TaskLPLR", vSubtask, zLEVEL_TASK ) > 0 )
               DropNameForView( vDialog, "TaskLPLR", vSubtask, zLEVEL_TASK );
         }
      }

      zwTZPNTRAD_PreBuild( vSubtask );
      zwTZPNTRAD_PostBuild( vSubtask );
   }
   else
   if ( GetViewByName( &vIdleView,
                       "__SysIdlePainter", vSubtask, zLEVEL_SYSTEM ) > 0 &&
        vIdleView == vSubtask )
   {
      DropNameForView( vIdleView, "__SysIdlePainter", vSubtask, zLEVEL_SYSTEM );

#ifdef __WIN32__
   // SetOptionState( vSubtask, "WindowList", zOPTION_STATUS_ENABLED, 0 );
#else
      if ( GetViewByName( &vDialog, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) < 1 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StartModelessSubwindow |
                                  zWAB_ProcessImmediateAction,
                                  "TZPNTRAD", "WND_LIST" );
      }
#endif
      if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) < 1 )
      {
         // Transfer to the open dialog window
         if ( GetViewByName( &vDialog, "TZDIALOGS", vSubtask, zLEVEL_TASK ) >= 0 )
            DropView( vDialog );

         SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow |
                                            zWAB_ProcessImmediateAction,
                                  "TZPNTRAD", "DLG_OPEN" );
      }
   }

   if ( fnPainterCall( zMSG_PAINTERINITIALIZED, vSubtask, 0, 0, 0 ) == 0 )
   {
//    TraceLineS( "(tzpntrad) - SystemActivate - ", "Early return" );
      return( 0 );
   }

#ifndef __WIN32__
   GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK );
   if ( vWindowList )
      PutWindowOnTop( vWindowList );

   fnPainterCall( zMSG_PUTTOOLBOXONTOP, vSubtask, 0, 0, 0 );
#endif

   GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );

   fnCreateMappingEntities( vSubtask, vDialog );

   // BL refresh all modeless Subwindows
   zwTZPNTRAD_RefreshAllWindowLists( vSubtask );

   return( 0 );
}

//./ ADD NAME=SystemRestore
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SystemRestore
//
//  PURPOSE:    Called when painter is restored or maximized, restore
//              all painter windows
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
SystemRestore( zVIEW vSubtask )
{
   TraceLineS("(tzpntrad) - SystemRestore","");

   fnPainterCall( zMSG_SYSTEMRESTORE, vSubtask, 0, 0, 0 );
   return( 0 );
}

//./ ADD NAME=CloneDialogWindow
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CloneDialogWindow
//
//  PURPOSE:    This function simply sets a flag to identify the
//              as clone instead of merge for the TZPNCWDD SEL_CLONE
//              dialog.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
CloneDialogWindow( zVIEW vSubtask )
{
   zVIEW vWork;
   zVIEW vDialog;

   GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );

   // If the dialog is not updatable, then don't do the merge.
   if ( MiGetUpdateForView( vDialog ) == 0 )
   {
      MessageSend( vSubtask, "PN00207", "Dialog Maintenance",
                   "This dialog is not updatable.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( 0 );
   }

   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );
   SetAttributeFromString( vWork, "TZPNCTWO", "CloneFunction", "C" );

   return( 0 );
}

//./ ADD NAME=MergeDialogWindow
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      MergeDialogWindow
//
//  PURPOSE:    This function simply sets a flag to identify the
//              as merge instead of clone for the TZPNCWDD SEL_CLONE
//              dialog.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
MergeDialogWindow( zVIEW vSubtask )
{
   zVIEW vWork;
   zVIEW vDialog;

   GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );

   // If the dialog is not updatable, then don't do the merge.
   if ( MiGetUpdateForView( vDialog ) == 0 )
   {
      MessageSend( vSubtask, "PN00208", "Dialog Maintenance",
                   "This dialog is not updatable.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( 0 );
   }

   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );
   SetAttributeFromString( vWork, "TZPNCTWO", "CloneFunction", "M" );

   return( 0 );
}

//./ ADD NAME=WND_UPD_SelectAction
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_SelectAction
//
//  PURPOSE:    To select an action for a window Event
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_SelectAction( zVIEW vSubtask )
{
   zVIEW vDialog;
   zVIEW vEvents;
   zVIEW vWork;
   zLONG lType;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );

   // Error if no Event was selected.
   if ( SetCursorFirstSelectedEntity( vEvents, "Event", "" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "PN00209", "Dialog Maintenance",
                   "No Event Selected",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      return( 0 );
   }

   GetIntegerFromAttribute( &lType, vEvents, "Event", "Type" );
   if ( SetCursorFirstEntityByInteger( vDialog, "WndEvent",
                                       "Type", lType, 0 ) != zCURSOR_SET )
   {
      CreateTemporalMetaEntity( vSubtask, vDialog, "WndEvent", zPOS_AFTER );
      SetAttributeFromInteger( vDialog, "WndEvent", "Type", lType );
   }

   // Set flag for LIST_ACT window graying and select behavior.
   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "W" );

   return( 0 );
}

//./ ADD NAME=WND_UPD_RemoveAction
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_RemoveAction
//
//  PURPOSE:    To Remove an action for a window Event
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_RemoveAction( zVIEW vSubtask )
{
zVIEW vEvents;
zVIEW vDialog;
zLONG lType;

   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   SetAttributeFromString( vEvents, "EventAct", "Tag", 0 );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetIntegerFromAttribute( &lType, vEvents, "Event", "Type" );
   if ( SetCursorFirstEntityByInteger( vDialog, "WndEvent", "Type",
                                       lType, "" ) == zCURSOR_SET )
   {
      DeleteEntity( vDialog, "WndEvent", zREPOS_PREV );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    WND_UPD_AddAction
//
// PURPOSE:  This function creates an Action entity and includes it to.
//           the selected Window.  It is used from Action_Popup
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
WND_UPD_AddAction( zVIEW vSubtask )
{
   zVIEW  vWork;

   WND_UPD_SelectAction( vSubtask );
   LIST_ACT_AddAction( vSubtask );

   // Set flag for select behavior.
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );
   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "W" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_Init
//
//  PURPOSE:
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_Init( zVIEW vSubtask )
{
   zVIEW vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // KJS 04/15/15 - Adding a new field (with domain table) for the jsp generation positioning. So if an old setting
   // was set, then change this new field.
   // Check that WEB_JSPGenerationPositioning doesn't have a value.
   if ( CompareAttributeToString( vDialog, "Window", "WEB_JSPGenerationPositioning", "" ) == 0 )
   {
      if ( CompareAttributeToString( vDialog, "Window", "WEB_RelativePositionFlag", "Y" ) == 0 )
      {
         SetAttributeFromString( vDialog, "Window", "WEB_JSPGenerationPositioning", "R" );
      }
      else if ( CompareAttributeToString( vDialog, "Window", "WEB_AbsolutePositionFlag", "Y" ) == 0 )
      {
         SetAttributeFromString( vDialog, "Window", "WEB_JSPGenerationPositioning", "A" );
      }
   }

// CreateTemporalSubobjectVersion( vDialog, "Window" );
   /* NO MORE WndPhysOverride
   if ( MiGetUpdateForView( vDialog ) &&
        CheckExistenceOfEntity( vDialog, "WndPhysOverride" ) != 0 )
   {
      CreateMetaEntity( vSubtask, vDialog, "WndPhysOverride", zPOS_AFTER );
   }
   */
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_Postbuild
//
//  PURPOSE:
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_Postbuild( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vTZDIALOGS;
   zVIEW  vDialogList;
   zULONG ulFlag;
   zSHORT nRC;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   GetIntegerFromAttribute( (zPLONG) &ulFlag, vDialog,
                            "Window", "GeneralFlag" );
   if ( ulFlag & 0x00000001 )
      SetCtrlState( vSubtask, "ScrollBars", zCONTROL_STATUS_CHECKED, TRUE );

   if ( ulFlag & 0x00000002 )
      SetCtrlState( vSubtask, "SelectFirstEdit", zCONTROL_STATUS_CHECKED, TRUE );

   if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
   {
      SetCtrlState( vSubtask, "ScrollBars", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "SelectFirstEdit", zCONTROL_STATUS_ENABLED, FALSE );
   }

   nRC = GetViewByName( &vDialogList, "TZDLG_List", vSubtask, zLEVEL_TASK );
   if ( nRC <= 0 )
   {
       GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_ANY );
       CreateViewFromViewForTask( &vDialogList, vTZDIALOGS, 0 );
       SetNameForView( vDialogList, "TZDLG_List", vSubtask, zLEVEL_TASK );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DLG_MAINT_Postbuild
//
//  PURPOSE:
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DLG_MAINT_Postbuild( zVIEW vSubtask )
{
   zVIEW  vTZDIALOGS;
   zVIEW  vDialogList;
   zVIEW  vDialog;
   zSHORT nRC;

   nRC = GetViewByName( &vDialogList, "TZDLG_List", vSubtask, zLEVEL_TASK );
   if ( nRC <= 0 )
   {
       GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_ANY );
       CreateViewFromViewForTask( &vDialogList, vTZDIALOGS, 0 );
       SetNameForView( vDialogList, "TZDLG_List", vSubtask, zLEVEL_TASK );
   }

   // KJS 04/15/15 - Adding a new field (with domain table) for the jsp generation positioning. So if an old setting
   // was set, then change this new field.
   // Check that WEB_JSPGenerationPositioning doesn't have a value.
   nRC = GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   if ( CompareAttributeToString( vDialog, "Dialog", "WEB_JSPGenerationPositioning", "" ) == 0 )
   {
      if ( CompareAttributeToString( vDialog, "Dialog", "WEB_RelativePositionFlag", "Y" ) == 0 )
      {
         SetAttributeFromString( vDialog, "Dialog", "WEB_JSPGenerationPositioning", "R" );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: WND_UPD_SetColors
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
WND_UPD_SetColors( zVIEW vSubtask,
                   zVIEW vDialog,
                   zVIEW vPE )
{
// zLONG  lZKey;
// zSHORT nRC;

#if 0
   // If any WndColorDefs have been added or deleted from the PE, then
   // make sure we add or delete them from the Dialog.
   nRC = SetCursorFirstEntity( vDialog, "WndClrOverride", "" );
   while ( nRC >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lZKey, vDialog, "WndColorDef", "ZKey" );
      nRC = SetCursorFirstEntityByInteger( vPE, "WndColorDef",
                                           "ZKey", lZKey, "" );
      if ( nRC < zCURSOR_SET )
         DeleteEntity( vDialog, "WndClrOverride", zREPOS_NONE );

      nRC = SetCursorNextEntity( vDialog, "WndClrOverride", "" );
   }

   nRC = SetCursorFirstEntity( vPE, "WndColorDef", "" );
   while ( nRC >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lZKey, vPE, "WndColorDef", "ZKey" );
      nRC = SetCursorFirstEntityByInteger( vDialog, "WndColorDef",
                                           "ZKey", lZKey, "Window" );
      if ( nRC < zCURSOR_SET )
      {
         // Get the position of the PE WndColorDef and create the
         // Dialogs WndColorDef in the same relative position.
         nRC = (zSHORT) GetRelativeEntityNumber( vPE, "WndColorDef",
                                                 0, 0L );

         // If nRC is 0 then the PE WndColorDef is the first entity
         // so the Dialog's WndClrOverride needs to be created before
         // its first WndClrOverride.
         if ( nRC == 0 )
         {
            SetCursorFirstEntity( vDialog, "WndClrOverride", 0 );
            CreateMetaEntity( vSubtask, vDialog, "WndClrOverride", zPOS_BEFORE );
         }
         else
         {
            // Position the Dialog on the WndClrOverride at relative
            // position nRC - 1.  Because relative positions start at
            // 0, you don't think you need to do the minus 1 but you do.
            SetEntityCursor( vDialog, "WndClrOverride", 0,
                             zPOS_FIRST | zPOS_RELATIVE, 0, 0, 0,
                             (zSHORT) (nRC - 1), 0, 0 );
            CreateMetaEntity( vSubtask, vDialog, "WndClrOverride", zPOS_AFTER );
         }

         IncludeSubobjectFromSubobject( vDialog, "WndColorDef",
                                        vPE, "WndColorDef", zPOS_AFTER );
         IncludeSubobjectFromSubobject( vDialog, "WndColor",
                                        vPE, "Color", zPOS_AFTER );
      }

      nRC = SetCursorNextEntity( vPE, "WndColorDef", "" );
   }
#endif

   return( 0 );
} // WND_UPD_SetColors

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_UpdateColors
//
//  PURPOSE:
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_UpdateColors( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vPE;
   zSHORT nRC;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );

   nRC = SetCursorFirstEntityByEntityCsr( vPE, "WindowStyle",
                                          vDialog, "WndStyle", "" );
   if ( nRC < zCURSOR_SET )
   {
      if ( SetCursorFirstEntityByAttr( vPE, "WindowStyle", "Tag",
                                       vDialog, "WndStyle", "Tag",
                                       "" ) < zCURSOR_SET )
      {
         return( 0 );
      }
   }

   // If Dialog not checked out, View is read only. To set a attribute
   // View has to be updateble. After change attribute set View read only again
   if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
      SetViewUpdate( vDialog );

   nRC = SetCursorFirstEntityByString( vPE, "Color", "Tag",
                                       "Windows Default", "" );

#if 0
   if ( CheckExistenceOfEntity( vDialog, "WndClrOverride" ) == zCURSOR_SET )
   {
      // If any WndColorDefs have been added or deleted from the PE, then
      // make sure we add or delete them from the Dialog.
      WND_UPD_SetColors( vSubtask, vDialog, vPE );
   }
   else
   {
      // Create CtrlColorDefs, all with the COLOR_WINDOW_DFLT CtrlColor.
      nRC = SetCursorFirstEntity( vPE, "WndColorDef", "" );
      while ( nRC >= zCURSOR_SET )
      {
         CreateMetaEntity( vSubtask, vDialog, "WndClrOverride", zPOS_AFTER );
         IncludeSubobjectFromSubobject( vDialog, "WndColorDef",
                                        vPE, "WndColorDef", zPOS_AFTER );
         IncludeSubobjectFromSubobject( vDialog, "WndColor",
                                        vPE, "Color", zPOS_AFTER );
         nRC = SetCursorNextEntity( vPE, "WndColorDef", "" );
      }
   }
#endif

   // If Dialog not checked out, View is read only. To set a attribute
   // View has to be updateble. After change attribute set View read only again
   if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
      SetViewReadOnly( vDialog );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_ColorsOK
//
//  PURPOSE:
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_ColorsOK( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zBOOL  bAllSet;
// zSHORT nRC;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // Loop through all the WndColorDefs.  If they all have WndColors set
   // to COLOR_WINDOW_DFLT, then delete all the WndColorDefs.
   bAllSet = TRUE;

#if 0
   nRC = SetCursorFirstEntity( vDialog, "WndClrOverride", "" );
   while ( nRC >= zCURSOR_SET && bAllSet )
   {
      if ( CompareAttributeToInteger( vDialog, "WndColor",
                                      "RGB_Color", zCOLOR_WINDOW_DFLT ) != 0 )
      {
         bAllSet = FALSE;
      }

      nRC = SetCursorNextEntity( vDialog, "WndClrOverride", "" );
   }
#endif

   if ( bAllSet == TRUE )
   {
      // If Dialog not checked out, View is read only. To set a attribute
      // View has to be updateble. After change attribute set View read only again
      if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
         SetViewUpdate( vDialog );

#if 0
      nRC = SetCursorFirstEntity( vDialog, "WndClrOverride", "" );
      while ( nRC >= zCURSOR_SET )
         nRC = DeleteEntity( vDialog, "WndClrOverride", zREPOS_NEXT );
#endif

      if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
         SetViewReadOnly( vDialog );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_UpdateFonts
//
//  PURPOSE:
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_UpdateFonts( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vPE;
   zSHORT nRC;
   zLONG  lZKey;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );

   nRC = SetCursorFirstEntityByEntityCsr( vPE, "WindowStyle",
                                          vDialog, "WndStyle", "" );
   if ( nRC < zCURSOR_SET )
      return( 0 );

   nRC = SetCursorFirstEntityByString( vPE, "Font", "Tag",
                                       "Windows Default", "" );

   if ( CheckExistenceOfEntity( vDialog, "WndFontOverride" ) == zCURSOR_SET )
   {
      /* If any WndFontDefs have been added or deleted from the PE, then
         make sure we add or delete them from the Dialog. */
      nRC = SetCursorFirstEntity( vDialog, "WndFontOverride", "" );
      while ( nRC >= zCURSOR_SET )
      {
         GetIntegerFromAttribute( &lZKey, vDialog, "WndFontDef", "ZKey" );
         nRC = SetCursorFirstEntityByInteger( vPE, "WndFontDef",
                                              "ZKey", lZKey, "" );
         /*
         nRC = SetCursorFirstEntityByEntityCsr( vPE, "WndFontDef",
                                                vDialog, "WndFontDef",
                                                "" );
         */
         if ( nRC < zCURSOR_SET )
         {
            DeleteEntity( vDialog, "WndFontOverride", zREPOS_NONE );
         }
         nRC = SetCursorNextEntity( vDialog, "WndFontOverride", "" );
      }

      nRC = SetCursorFirstEntity( vPE, "WndFontDef", "" );
      while ( nRC >= zCURSOR_SET )
      {
         GetIntegerFromAttribute( &lZKey, vPE, "WndFontDef", "ZKey" );
         nRC = SetCursorFirstEntityByInteger( vDialog, "WndFontDef",
                                              "ZKey", lZKey, "Window" );
         /*
         nRC = SetCursorFirstEntityByEntityCsr( vDialog, "WndFontDef",
                                                vPE, "WndFontDef", "Window" );
         */
         if ( nRC < zCURSOR_SET )
         {
            /* Get the position of the PE WndFontDef and create the
               Dialogs WndFontDef in the same relative position. */
            nRC = (zSHORT) GetRelativeEntityNumber( vPE, "WndFontDef", 0, 0L );

            /* If nRC is 0 then the PE WndFontDef is the first entity
               so the Dialog's WndFontOverride needs to be created before
               its first WndFontOverride. */
            if ( nRC == 0 )
            {
               SetCursorFirstEntity( vDialog, "WndFontOverride", 0 );
               CreateMetaEntity( vSubtask, vDialog, "WndFontOverride", zPOS_BEFORE );
            }
            else
            {
               /* Position the Dialog on the WndFontOverride at relative
                  position nRC - 1.  Because relative positions start at
                  0, you don't think you need to do the minus 1 but you
                  do. */
               SetEntityCursor( vDialog, "WndFontOverride", 0,
                                zPOS_FIRST | zPOS_RELATIVE, 0, 0, 0,
                                (zSHORT) (nRC - 1), 0, 0 );
               CreateMetaEntity( vSubtask, vDialog, "WndFontOverride", zPOS_AFTER );
            }

            IncludeSubobjectFromSubobject( vDialog, "WndFontDef",
                                           vPE, "WndFontDef", zPOS_AFTER );
            IncludeSubobjectFromSubobject( vDialog, "WndFont",
                                           vPE, "Font", zPOS_AFTER );
         }
         nRC = SetCursorNextEntity( vPE, "WndFontDef", "" );
      }
   }
   else
   {
#if 0
      // Create CtrlColorDefs, all with the COLOR_WINDOW_DFLT CtrlColor.
      nRC = SetCursorFirstEntity( vPE, "WndFontDef", "" );
      while ( nRC >= zCURSOR_SET )
      {
         CreateMetaEntity( vSubtask, vDialog, "WndFontOverride", zPOS_AFTER );
         IncludeSubobjectFromSubobject( vDialog, "WndFontDef",
                                        vPE, "WndFontDef", zPOS_AFTER );
         IncludeSubobjectFromSubobject( vDialog, "WndFont",
                                        vPE, "Font", zPOS_AFTER );
         nRC = SetCursorNextEntity( vPE, "WndFontDef", "" );
      }
#endif
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_FontsOK
//
//  PURPOSE:
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_FontsOK( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zSHORT nRC;
   zBOOL  bAllSet;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   /* Loop through all the WndFontDefs.   If they all have WndFonts set
      to COLOR_WINDOW_DFLT, then delete all the WndFontDefs. */
   bAllSet = TRUE;
   nRC = SetCursorFirstEntity( vDialog, "WndFontOverride", "" );
   while ( nRC >= zCURSOR_SET && bAllSet )
   {
      if ( CompareAttributeToString( vDialog, "WndFont",
                                     "Tag", "Windows Default" ) != 0 )
         bAllSet = FALSE;
      nRC = SetCursorNextEntity( vDialog, "WndFontOverride", "" );
   }
   if ( bAllSet == TRUE )
   {
      nRC = SetCursorFirstEntity( vDialog, "WndFontOverride", "" );
      while ( nRC >= zCURSOR_SET )
         nRC = DeleteEntity( vDialog, "WndFontOverride", zREPOS_NEXT );
   }

   return( 0 );
}

zSHORT
fnWndUpdate( zVIEW vSubtask, zBOOL bStayOnWindow )
{
   zVIEW    vTZPNTROO;
   zVIEW    vDialog;
   zVIEW    vDialogL;
   zCHAR    szNewTag[ 34 ];
   zULONG   ulFlag;

   // First, if a window name changed, make sure it is unique and
   // make the appropriate change in the painter active object
   GetViewByName( &vTZPNTROO, "TZPNTROO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // If the window name was changed, set the appropriate new name in
   // the painter's active list UNLESS a duplicate name was created, if
   // a duplicate name is created, issue an ERROR.
   GetStringFromAttribute( szNewTag, zsizeof( szNewTag ), vDialog, "Window", "Tag" );
   if ( szNewTag[ 0 ] == 0 ||
        (SetCursorFirstEntityByString( vDialogL, "Window", "Tag",
                                       szNewTag, 0 ) == zCURSOR_SET &&
         SetCursorNextEntityByString( vDialogL, "Window", "Tag",
                                      szNewTag, 0 ) == zCURSOR_SET ) )
   {
      MessageSend( vSubtask, "PN00210", "Dialog Maintenance",
                   "Window tag is null or not unique",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      SetFocusToCtrl( vSubtask, "WindowName" );
      return( 1 );
   }

   GetIntegerFromAttribute( (zPLONG) &ulFlag, vDialog,
                            "Window", "GeneralFlag" );
   if ( GetCtrlState( vSubtask, "ScrollBars",
                      zCONTROL_STATUS_CHECKED ) == TRUE )
   {
      ulFlag |= 0x00000001;
   }
   else
   {
      ulFlag &= ~0x00000001;
   }

   if ( GetCtrlState( vSubtask, "SelectFirstEdit",
                      zCONTROL_STATUS_CHECKED ) == TRUE )
   {
      ulFlag |= 0x00000002;
   }
   else
   {
      ulFlag &= ~0x00000002;
   }

   if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
      SetViewUpdate( vDialog );

   SetAttributeFromInteger( vDialog, "Window", "GeneralFlag", ulFlag );

   if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
      SetViewReadOnly( vDialog );

   // Tell the painter to update the window name if appropriate
   fnPainterCall( zMSG_UPDATEACTIVEWINDOWNAME, vSubtask, 0, szNewTag, zsizeof( szNewTag ) );

#ifndef __WIN32__
   // Refresh the window list in the event the window name has changed
   if ( GetViewByName( &vWindowList, "TZWND_LIST_Subtask", vSubtask, zLEVEL_TASK ) > 0 )
      RefreshCtrl( vWindowList, "ListBox1" );
#endif

   if ( bStayOnWindow == FALSE )
      fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );

   AcceptSubobject( vDialog, "Window" );

   if ( bStayOnWindow == FALSE )
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParentWithRefresh |
                                         zWAB_ProcessImmediateReturn, 0, 0 );
   return( 0 );
}

//./ ADD NAME=WND_UPD_OK
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      WND_UPD_OK
//
//  PURPOSE:    To Update the Window Detail
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
WND_UPD_OK( zVIEW vSubtask )
{
   return( fnWndUpdate( vSubtask, FALSE ) );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    WND_UPD_ReturnFromSubwindow
//
// PURPOSE:  This function sets up the Event entity in TZPNEVWO from
//           the selected Event entity in TZWINDOWL.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
WND_UPD_ReturnFromSubwindow( zVIEW vSubtask )
{
   zVIEW    vDialogW;
   zVIEW    vEvents;

   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );

   // Delete WndEvent entity if there is not a relationship to Action
   if ( CheckExistenceOfEntity( vDialogW, "WndEvent" ) == zCURSOR_SET )
      if ( CheckExistenceOfEntity( vDialogW, "WndAct" ) != zCURSOR_SET )
         DeleteEntity( vDialogW, "WndEvent", zREPOS_PREV );

   // Set up the TZPNEVWO object instance from TZWINDOW and refresh
   // the List Box.
   fnSetupWndEventList( vDialogW );
   RefreshCtrl( vSubtask, "EventListBox" );

   return( 0 );
}

//./ ADD NAME=UpdateNextWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UpdateNextWindow
//
//  PURPOSE:    To Update the next Window Detail
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UpdateNextWindow( zVIEW vSubtask )
{
   zVIEW    vDialog;
   zVIEW    vDialogL;

   // First, update the current window.
   if ( fnWndUpdate( vSubtask, TRUE ) == 0 )
   {
      GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
      if ( SetCursorNextEntity( vDialog, "Window", "" ) != 0 )
         SetCursorFirstEntity( vDialog, "Window", "" );

      if ( GetViewByName( &vDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) > 0 )
         SetViewFromView( vDialogL, vDialog );

      WND_UPD_ReturnFromSubwindow( vSubtask );

      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      SetFocusToCtrl( vSubtask, "WindowName" );
   }

   return( 0 );
}

//./ ADD NAME=UpdatePreviousWindow
// Source Module=tzpntrad.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UpdatePreviousWindow
//
//  PURPOSE:    To Update the previous Window Detail
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
UpdatePreviousWindow( zVIEW vSubtask )
{
   zVIEW    vDialog;
   zVIEW    vDialogL;

   // First, update the current window.
   if ( fnWndUpdate( vSubtask, TRUE ) == 0 )
   {
      GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
      if ( SetCursorPrevEntity( vDialog, "Window", "" ) != 0 )
         SetCursorLastEntity( vDialog, "Window", "" );

      if ( GetViewByName( &vDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) > 0 )
         SetViewFromView( vDialogL, vDialog );

      WND_UPD_ReturnFromSubwindow( vSubtask );

      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      SetFocusToCtrl( vSubtask, "WindowName" );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    WND_UPD_OperationEdit
//
// PURPOSE:  This function sets up the TZWINDOW view to the Action Operation
//           entity corresponding to EventAct for the current Event.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
WND_UPD_OperationEdit( zVIEW vSubtask )
{
   zVIEW    vWork;
   zVIEW    vDialogW;
   zCHAR    sTag[ 34 ];

   GetViewByName( &vWork, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // If EventAct exists, set cursor for Update Action window.  Otherwise, return an error.

   if ( CheckExistenceOfEntity( vWork, "EventAct" ) == zCURSOR_SET &&
        CompareAttributeToString( vWork, "EventAct", "Tag", "" ) != 0 )
   {
      GetStringFromAttribute( sTag, zsizeof( sTag ), vWork, "EventAct", "Tag" );
      SetCursorFirstEntityByString( vDialogW, "Action", "Tag", sTag, "" );

      if ( CheckExistenceOfEntity( vDialogW, "ActOper" ) >= zCURSOR_SET )
      {
         GetStringFromAttribute( sTag, zsizeof( sTag ), vDialogW, "ActOper", "Name" );
         SetCursorFirstEntityByString( vDialogW, "Operation", "Name", sTag, "Dialog" );
         TransferToEditor( vSubtask, vDialogW, "PN", 0 );
      }
      else
      {
         MessageSend( vSubtask, "PN00211", "Dialog Maintenance",
                      "No Operation Exists For Action.",
                      zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      }
   }
   else
   {
      // Position on Action that corresponds to EventAct entity instance.
      MessageSend( vSubtask, "PN00212", "Dialog Maintenance",
                   "No Action exists for Event.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    WND_UPD_UpdateAction
//
// PURPOSE:  This function sets up the TZWINDOW view to the Action
//           entity corresponding to EventAct for the current Event.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
WND_UPD_UpdateAction( zVIEW vSubtask )
{
   zVIEW    vWork;
   zVIEW    vDialogW;
   zCHAR    sTag[ 34 ];

   GetViewByName( &vWork, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // If EventAct exists, set cursor for Update Action window.
   // Otherwise, return an error.
   if (( CheckExistenceOfEntity( vWork, "EventAct" ) == zCURSOR_SET ) &&
     ( CompareAttributeToString( vWork, "EventAct", "Tag", "" ) != 0 ))
   {
      GetStringFromAttribute( sTag, zsizeof( sTag ), vWork, "EventAct", "Tag" );
      SetCursorFirstEntityByString( vDialogW, "Action", "Tag", sTag, "" );
      CreateTemporalSubobjectVersion( vDialogW, "Action" );
   }
   else
   {
      // Issue an error
      MessageSend( vSubtask, "PN00213", "Dialog Maintenance",
                   "No Action exists for Event.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
   }

   // Set flag for LIST_ACT window graying and select behavior.
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );
   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "W" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    OPT_UPD_Init
//
// PURPOSE:  This function sets up the TZACTION view for the
//           OPT_UPD window.   It is the same as TZWINDOW if a current
//           OptAct exits.  It is null otherwise.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OPT_UPD_Init( zVIEW vSubtask )
{
   zVIEW    vDialogA;
   zVIEW    vDialogO;
   zVIEW    vDialogW;
   zVIEW    vDialogL;
   zVIEW    vEvents;
   zSHORT   nRC;

   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogO, "TZWINOPT", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vDialogA, "TZACTION", vSubtask, zLEVEL_TASK ) >= 0 )
      DropView( vDialogA );

   // If an Action for the Option exists, position on the linked Action
   // instance and set TZACTION to TZWINDOW.
   if ( CheckExistenceOfEntity( vDialogO, "OptAct" ) == zCURSOR_SET )
   {
      CreateViewFromViewForTask( &vDialogA, vDialogW, 0 );
      SetCursorFirstEntityByAttr( vDialogA, "Action", "ZKey",
                                  vDialogO, "OptAct", "ZKey", "" );
      SetNameForView( vDialogA, "TZACTION", vSubtask, zLEVEL_TASK );
   }
   else
   {
      // If not, set TZACTION to empty instance for auto graying.
      fnCreateEmptyActionView( vSubtask, vDialogW );
    }

   // Make sure TZWINDOWL view exits.
   if ( GetViewByName( &vDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      CreateViewFromViewForTask( &vDialogL, vDialogW, 0 );
      SetNameForView( vDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   }

   // Initialize the TZPNEVWO work object if it's empty.
   nRC = GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   if ( nRC )
   {
      ActivateEmptyObjectInstance( &vEvents, "TZPNEVWO",
                                   vSubtask, zMULTIPLE );
      SetNameForView( vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   }

   if ( CheckExistenceOfEntity( vEvents, "Event" ) != zCURSOR_SET )
   {
      CreateEntity( vEvents, "Event", zPOS_AFTER );
      SetAttributeFromString( vEvents, "Event", "Tag",
                              "Menu Item Selected");
      CreateEntity( vEvents, "EventAct", zPOS_AFTER );
   }

   if ( CheckExistenceOfEntity( vDialogO, "OptAct" ) == zCURSOR_SET )
        SetAttributeFromAttribute( vEvents,"EventAct", "Tag",
                                   vDialogO, "OptAct", "Tag" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    OPT_UPD_OK
//
// PURPOSE:  This function tells the Painter to refresh the control.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OPT_UPD_OK( zVIEW vSubtask )
{
   zVIEW   vDialogO;
   zVIEW   vTmpOptions;
   zVIEW   vTemp;
   zSHORT  nRC;
   zUSHORT uLevel;
   zBOOL   bTagFound;
   zCHAR   szTag[ 256 ];
   zCHAR   szEntityName[ 33 ];

   GetViewByName( &vDialogO, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szTag, zsizeof( szTag ), vDialogO, "Option", "NLS_Text" );

   // Make sure that the option tag is unique
   GetStringFromAttribute( szTag, zsizeof( szTag ), vDialogO, "Option", "Tag" );
   CreateViewFromViewForTask( &vTmpOptions, vDialogO, 0 );
   while ( ResetViewFromSubobject( vTmpOptions ) == 0 )
   {
   }

   CreateViewFromViewForTask( &vTemp, vTmpOptions, 0 );
   bTagFound = 0;
   DefineHierarchicalCursor( vTmpOptions, "Menu" );
   nRC = SetCursorNextEntityHierarchical( &uLevel, szEntityName, vTmpOptions );

   // Loop through all the Options and OptOpts for this Menu and check the
   // tags.
   while ( nRC >= zCURSOR_SET && uLevel > 3 )
   {
      if ( nRC == zCURSOR_SET_RECURSIVECHILD )
      {
         SetViewToSubobject( vTmpOptions, "OptOpt" );
      }

      if ( CompareAttributeToString( vTmpOptions, "Option",
                                     "Tag", szTag ) == 0 )
      {
         SetViewFromView( vTemp, vTmpOptions );
         DropHierarchicalCursor( vTemp );
         if ( CompareEntityToEntity( vTemp, "Option",
                                     vDialogO, "Option" ) != 0 )
         {
            bTagFound = 1;
            break;
         }
      }

      nRC = SetCursorNextEntityHierarchical( &uLevel,
                                             szEntityName, vTmpOptions );
   }

   DropHierarchicalCursor( vTmpOptions );
   DropView( vTmpOptions );
   DropView( vTemp );
   if ( bTagFound )
   {
      MessageSend( vSubtask, "PN00214", "Dialog Maintenance",
                   "Tag is not unique!",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "Tag" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      return( -1 );
   }

   AcceptSubobject( vDialogO, "Option" );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: OPT_UPD_DisableActionButton
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
OPT_UPD_DisableActionButton( zVIEW vSubtask )
{
   zVIEW vEvents;
   zVIEW vAction;
   zBOOL bEnable = FALSE;

   if ( GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if ( CheckExistenceOfEntity( vEvents, "Event" ) >= zCURSOR_SET &&
           CheckExistenceOfEntity( vEvents, "EventAct" ) >= zCURSOR_SET )
      {
         if ( CompareAttributeToString( vEvents, "EventAct", "Tag", "" ) != 0 )
            bEnable = TRUE;
      }

      SetCtrlState( vSubtask, "UpdateAction", zCONTROL_STATUS_ENABLED, bEnable );
   }

   bEnable = FALSE;

   if ( GetViewByName( &vAction, "TZACTION", vSubtask, zLEVEL_TASK ) > 0 &&
        CheckExistenceOfEntity( vAction, "ActOper" ) >= zCURSOR_SET)
   {
      bEnable = TRUE;
   }

   EnableAction( vSubtask, "OPT_UPD_OperationEdit", bEnable );

   return( 0 );
} // OPT_UPD_DisableActionButton

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      OPT_UPD_RemoveAction
//
//  PURPOSE:    To Remove an action from a menu option
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
OPT_UPD_RemoveAction( zVIEW vSubtask )
{
   zVIEW vDialogO;
   zVIEW vEvents;

   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogO, "TZWINOPT", vSubtask, zLEVEL_TASK );

   SetAttributeFromString( vEvents, "EventAct", "Tag", 0 );
   ExcludeEntity( vDialogO, "OptAct", zREPOS_PREV );
   fnCreateEmptyActionView( vSubtask, vDialogO );

   OPT_UPD_DisableActionButton( vSubtask );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    OPT_UPD_SelectAction
//
// PURPOSE:  This function positions on the correct Action entity if
//           an OptAct entity exists and sets an indicator to note
//           that this is an Include OptAct for the SEL_ATTR window.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OPT_UPD_SelectAction( zVIEW vSubtask )
{
   zVIEW    vDialogO;
   zVIEW    vDialogW;
   zVIEW    vWork;

   GetViewByName( &vDialogO, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vDialogO, "OptAct" ) == zCURSOR_SET )
   {
      SetCursorFirstEntityByAttr( vDialogW, "Action", "Tag",
                                  vDialogO, "OptAct", "Tag", "" );
   }

   // Set flag for Action include for Option.
   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "O" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    OPT_UPD_UpdateAction
//
// PURPOSE:  This function sets the TZWINDOW cursor to the correct
//           Action.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OPT_UPD_UpdateAction( zVIEW vSubtask )
{
   zVIEW    vDialogO;
   zVIEW    vDialogW;
   zVIEW    vWork;

   GetViewByName( &vDialogO, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vDialogO, "OptAct" ) == zCURSOR_SET )
   {
      SetCursorFirstEntityByAttr( vDialogW, "Action", "Tag",
                                  vDialogO, "OptAct", "Tag", "" );
      CreateTemporalSubobjectVersion( vDialogW, "Action" );
   }
   else
   {
      MessageSend( vSubtask, "PN00215", "Dialog Maintenance",
                   "No Action exists for Item.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
   }

   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "W" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    OPT_UPD_AddAction
//
// PURPOSE:  This function creates an Action entity and includes it to.
//           the selected Option.  It is used from Action_Popup
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OPT_UPD_AddAction( zVIEW vSubtask )
{
   zVIEW    vWork;

   OPT_UPD_SelectAction( vSubtask );
   LIST_ACT_AddAction( vSubtask );
   LIST_ACT_SelectAction( vSubtask );

   // Set flag for Action include for Option.
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );
   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "O" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    OPT_UPD_OperationEdit
//
// PURPOSE:  This function calls editor after positioning on operation
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OPT_UPD_OperationEdit( zVIEW vSubtask )
{
   zVIEW    vDialogC;
   zVIEW    vDialogW;
   zCHAR    sTag[ 34 ];

   GetViewByName( &vDialogC, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vDialogC, "EventAct" ) == zCURSOR_SET &&
        CompareAttributeToString( vDialogC, "EventAct", "Tag", "" ) != 0 )
   {
      GetStringFromAttribute( sTag, zsizeof( sTag ), vDialogC, "EventAct", "Tag" );
      SetCursorFirstEntityByString( vDialogW, "Action", "Tag", sTag, "" );

      if ( CheckExistenceOfEntity( vDialogW, "ActOper" ) == zCURSOR_SET )
      {
         SetCursorFirstEntityByEntityCsr( vDialogW, "Operation",
                                          vDialogW, "ActOper", "Dialog" );
         TransferToEditor( vSubtask, vDialogW, "PN", 0 );
      }
      else
      {
         MessageSend( vSubtask, "PN00216", "Dialog Maintenance",
                      "No Operation Exists For Action.",
                      zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      }
   }
   else
   {
      MessageSend( vSubtask, "PN00217", "Dialog Maintenance",
                   "No Action exists for Menu Item.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
   }

   return( 0 );
}


/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    OPT_UPD_ReturnFromSub
//
// PURPOSE:  Make sure TZACTION is the View for the Action just
//           selected.  TZACTION to be a null View, if no OptAct
//           existed prior to the Select.
//           Also drop the TZACTION View if it is null.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OPT_UPD_ReturnFromSub( zVIEW vSubtask )
{
   zVIEW    vDialogO;
   zVIEW    vDialogW;
   zVIEW    vDialogA;
   zVIEW    vEvents;

   GetViewByName( &vDialogO, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogA, "TZACTION", vSubtask, zLEVEL_TASK );
   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );

   // If an Action for the Option exists, position on the linked Action
   // instance and set TZACTION to TZWINDOW.
   if ( CheckExistenceOfEntity( vDialogO, "OptAct" ) == zCURSOR_SET )
   {
      // Drop TZACTION work OI, if it is empty.
      if ( CheckExistenceOfEntity( vDialogA, "Window" ) != zCURSOR_SET )
         DropObjectInstance( vDialogA );

      CreateViewFromViewForTask( &vDialogA, vDialogW, 0 );
      SetCursorFirstEntityByAttr( vDialogA, "Action", "Tag",
                                  vDialogO, "OptAct", "Tag", "" );
      SetNameForView( vDialogA, "TZACTION", vSubtask, zLEVEL_TASK );
      SetAttributeFromAttribute( vEvents,"EventAct", "Tag",
                                 vDialogO, "OptAct", "Tag" );
   }
   else
      SetAttributeFromString( vEvents, "EventAct", "Tag", "" );

   OPT_UPD_DisableActionButton( vSubtask );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    OptContextMappingInit
//
// PURPOSE:  This function builds the MapDomain View for the Context
//           Combo Box, if there is current mapping.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OptContextMappingInit( zVIEW vSubtask )
{
   zVIEW    vDialog;
   zVIEW    vCM_List;
   zVIEW    vDomain;
   zLONG    lZKey;

   GetViewByName( &vDialog, "TZWINOPT", vSubtask, zLEVEL_TASK );
   RetrieveViewForMetaList( vSubtask, &vCM_List, zREFER_DOMAIN_META );

   if ( CheckExistenceOfEntity( vDialog,
                                "OptMapER_Attribute" ) == zCURSOR_SET )
   {
      // Activate the Domain for the current OptMapER_Domain.
      GetIntegerFromAttribute( &lZKey, vDialog, "OptMapER_Domain", "ZKey");
      SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef",
                                     "CPLR_ZKey", lZKey, "" );
      ActivateMetaOI( vSubtask, &vDomain, vCM_List, zREFER_DOMAIN_META, 0 );
   }
   else
      ActivateEmptyObjectInstance( &vDomain, "TZDGSRCO", vSubtask, 0 );

   SetNameForView( vDomain, "MapDomain", vSubtask, zLEVEL_TASK );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    SEL_OPT_SelectMapping
//
// PURPOSE:  This function does the necessary exclude/includes
//           to set up attribute mapping.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
SEL_OPT_SelectMapping( zVIEW vSubtask )
{
   zVIEW    vDialog;
   zVIEW    vLOD;
   zVIEW    vTZPNTROO;
   zVIEW    vTZWINDOWL;
   zSHORT   nRC;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZPNTROO, "TZPNTROO", vSubtask, zLEVEL_ANY );
   GetViewByName( &vDialog, "TZWINOPT", vSubtask, zLEVEL_TASK );
   nRC = GetViewByName( &vLOD, "SEL_LOD", vSubtask, zLEVEL_TASK );

   if ( !ComponentIsCheckedOut( vSubtask, vTZWINDOWL, zSOURCE_DIALOG_META ) )
   {
      DropMetaOI( vSubtask, vLOD );
      return( 0 );
   }

   if ( nRC <= 0 )
   {
      // If current OptMapContext exists, exclude it.
      if ( CheckExistenceOfEntity( vDialog, "OptMapContext" ) == zCURSOR_SET )
         ExcludeEntity( vDialog, "OptMapContext", zREPOS_PREV );

      // If current OptMapLOD_Attribute exists, exclude it.
      if ( CheckExistenceOfEntity( vDialog,
                                   "OptMapLOD_Attribute" ) == zCURSOR_SET )
      {
         ExcludeEntity( vDialog, "OptMapLOD_Attribute", zREPOS_PREV );
      }

      return( 0 );
   }

   // Alter mapping only if it changed from existing.
   if ( CheckExistenceOfEntity( vDialog,
                                "OptMapLOD_Attribute" ) != zCURSOR_SET ||
        CompareAttributeToAttribute( vDialog, "OptMapLOD_Attribute", "ZKey",
                                     vLOD, "LOD_Attribute", "ZKey" ) != 0 )
   {
      // If current OptMapContext exists, exclude it.
      if ( CheckExistenceOfEntity( vDialog, "OptMapContext" ) == zCURSOR_SET )
         ExcludeEntity( vDialog, "OptMapContext", zREPOS_PREV );

      // If current OptMapLOD_Attribute exists, exclude it.
      if ( CheckExistenceOfEntity( vDialog,
                                   "OptMapLOD_Attribute" ) == zCURSOR_SET )
      {
         ExcludeEntity( vDialog, "OptMapLOD_Attribute", zREPOS_PREV );
      }

      IncludeSubobjectFromSubobject( vDialog, "OptMapLOD_Attribute",
                                     vLOD, "LOD_Attribute", zPOS_AFTER );
   }

   // Set up default View Obj Ref and Entity for next mapping.
   if ( CheckExistenceOfEntity( vTZPNTROO, "CtrlWork" ) != zCURSOR_SET )
      CreateEntity( vTZPNTROO, "CtrlWork", zPOS_AFTER );

   SetAttributeFromAttribute( vTZPNTROO, "CtrlWork", "LastMapViewZKey",
                              vDialog, "OptMapView", "ZKey" );
   SetAttributeFromAttribute( vTZPNTROO, "CtrlWork", "LastMapEntityZKey",
                              vDialog, "OptMapRelatedEntity", "ZKey" );
   DropMetaOI( vSubtask, vLOD );

   // Set up Domain Context mapping.
   OptContextMappingInit( vSubtask );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    SEL_OPT_Init
//
// PURPOSE:  This function activates the LOD associated with the
//           current view.  If no view is currently defined, it
//           temporarily sets up a dummy view.  I'm not sure what
//           it should eventually do.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
SEL_OPT_Init( zVIEW vSubtask )
{
   zVIEW    vDialogO;
   zVIEW    vDialogW;
   zVIEW    vLOD;
   zVIEW    vCM_List;
   zVIEW    vTZPNTROO;
   zLONG    lZKey;

   GetViewByName( &vDialogW, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogO, "TZWINOPT", vSubtask, zLEVEL_TASK );
   RetrieveViewForMetaList( vSubtask, &vCM_List, zREFER_LOD_META );

   // If Dialog not checked out, View is read only. To set a attribute
   // View has to be updateble. After change attribute set View read only again
   if ( !ComponentIsCheckedOut( vSubtask, vDialogW, zSOURCE_DIALOG_META ) )
      SetViewUpdate( vDialogO );

   // Create work entity, if it doesn't exist.
   GetViewByName( &vTZPNTROO, "TZPNTROO", vSubtask, zLEVEL_ANY );
   if ( CheckExistenceOfEntity( vTZPNTROO, "CtrlWork" ) != zCURSOR_SET )
      CreateEntity( vTZPNTROO, "CtrlWork", zPOS_AFTER );

   // If OptMap doesn't exist, create it.
   if ( CheckExistenceOfEntity( vDialogO, "OptMap" ) != zCURSOR_SET )
   {
      CreateMetaEntity( vSubtask, vDialogO, "OptMap", zPOS_AFTER );
   }

   // If OptMapView exists, use the corresponding LOD for mapping.
   // Use OptMapView ZKey to locate ViewObjRef and then
   // LOD ZKey to locate LPLR LOD meta.
   if ( CheckExistenceOfEntity( vDialogO, "OptMapView" ) == zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lZKey, vDialogO, "OptMapView", "ZKey");
      SetCursorFirstEntityByInteger( vDialogW, "ViewObjRef",
                                     "ZKey", lZKey, "" );
      GetIntegerFromAttribute( &lZKey, vDialogW, "LOD", "ZKey" );
      SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef",
                                     "CPLR_ZKey", lZKey, "" );
      ActivateMetaOI( vSubtask, &vLOD, vCM_List, zREFER_LOD_META, 0 );
      SetNameForView( vLOD, "SEL_LOD", vSubtask, zLEVEL_TASK );
      // Select current mapping in LOD
      if ( CheckExistenceOfEntity( vDialogO,
                                   "OptMapLOD_Attribute" ) == zCURSOR_SET )
      {
         GetIntegerFromAttribute( &lZKey, vDialogO,
                                  "OptMapRelatedEntity", "ZKey" );
         SetCursorFirstEntityByInteger( vLOD, "LOD_Entity",
                                        "ZKey", lZKey, "" );
         SetSelectStateOfEntityForSet( vLOD, "LOD_Entity", 1, 1 );
         GetIntegerFromAttribute( &lZKey, vDialogO,
                                  "OptMapLOD_Attribute", "ZKey" );
         SetCursorFirstEntityByInteger( vLOD, "LOD_Attribute",
                                        "ZKey", lZKey, "" );
         SetSelectStateOfEntityForSet( vLOD, "LOD_Attribute", 1, 1 );
      }
   }
   else
   {
      // If no current mapping exists, try to use the last mapping
      // specified for the Entity and Attribute list boxes.  Also
      // set view to last view used.
      GetIntegerFromAttribute( &lZKey, vTZPNTROO,
                               "CtrlWork", "LastMapViewZKey");
      if ( SetCursorFirstEntityByInteger( vDialogW, "ViewObjRef",
                                          "ZKey", lZKey, "" ) == zCURSOR_SET )
      {
         if ( CheckExistenceOfEntity( vDialogO, "OptMapView" ) == zCURSOR_SET )
            ExcludeEntity( vDialogO, "OptMapView", zREPOS_PREV );

         IncludeSubobjectFromSubobject( vDialogO, "OptMapView",
                                        vDialogW, "ViewObjRef", zPOS_AFTER );
         GetIntegerFromAttribute( &lZKey, vDialogW, "LOD", "ZKey" );
         SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef",
                                        "CPLR_ZKey", lZKey, "" );
         ActivateMetaOI( vSubtask, &vLOD, vCM_List, zREFER_LOD_META, 0 );
         SetNameForView( vLOD, "SEL_LOD", vSubtask, zLEVEL_TASK );

         // Position on correct LOD_Entity
         GetIntegerFromAttribute( &lZKey, vTZPNTROO,
                                  "CtrlWork", "LastMapEntityZKey");
         SetCursorFirstEntityByInteger( vLOD, "LOD_Entity",
                                        "ZKey", lZKey, "" );
         SetSelectStateOfEntityForSet( vLOD, "LOD_Entity", 1, 1 );
      }
   }

   // if Dialog not checked out, set  View read only ->
   // the user cannot update the values in Detail Windows
   if ( !ComponentIsCheckedOut( vSubtask, vDialogW, zSOURCE_DIALOG_META ) )
      SetViewReadOnly( vDialogO );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    SEL_OPT_SelectView
//
// PURPOSE:  This function
//           1. Does the necessary exclude/include of OptMapView.
//           2. Activates the LOD for the View just selected.
//           3. Refreshes the Entity and Attribute List Boxes and sets
//              the LOD Entity and Attribute select states.
//
//           Note that steps 2 and 3 are not done if the include is
//           to the same LOD type as for the previous OptMapView.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
SEL_OPT_SelectView( zVIEW vSubtask )
{
   zVIEW    vLOD;
   zVIEW    vCM_List;
   zVIEW    vDialogO;
   zVIEW    vDialogW;
   zLONG    lZKey;
   zSHORT   nRC;

   GetViewByName( &vDialogO, "TZWINOPT", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   nRC = GetViewByName( &vLOD, "SEL_LOD", vSubtask, zLEVEL_TASK );
   // Drop the SEL_LOD meta OI, if it exists.
   if ( nRC >= 0 )
      DropMetaOI( vSubtask, vLOD );

   if ( CheckExistenceOfEntity( vDialogO, "OptMapView" ) == zCURSOR_SET )
   {
      // Activate the LOD for the current ViewObjRef subobject.
      RetrieveViewForMetaList( vSubtask, &vCM_List, zREFER_LOD_META );
      GetIntegerFromAttribute( &lZKey, vDialogW, "LOD", "ZKey" );
      SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef",
                                     "CPLR_ZKey", lZKey, "" );
      ActivateMetaOI( vSubtask, &vLOD, vCM_List, zREFER_LOD_META, 0 );
      SetNameForView( vLOD, "SEL_LOD", vSubtask, zLEVEL_TASK );

      SetSelectStateOfEntityForSet( vLOD, "LOD_Entity", 1, 1 );
      SetSelectStateOfEntityForSet( vLOD, "LOD_Attribute", 1, 1 );
      RefreshCtrl( vSubtask, "EntityList" );
      RefreshCtrl( vSubtask, "AttributeList" );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    SEL_OPT_SelectEntity
//
// PURPOSE:  This function refreshes the Entity and Attribute List Boxes.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
SEL_OPT_SelectEntity( zVIEW vSubtask )
{
   zVIEW  vLOD;

   GetViewByName( &vLOD, "SEL_LOD", vSubtask, zLEVEL_TASK );
   SetSelectStateOfEntityForSet( vLOD, "LOD_Attribute", 1, 1 );
   RefreshCtrl( vSubtask, "AttributeList" );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZPNTRAD_TransferToEditor
//
// PURPOSE:
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_TransferToEditor( zVIEW vSubtask )
{
   zVIEW  vMETAOBJECT;

   // Get Access to dialog Object
   GetViewByName( &vMETAOBJECT, "TZWINDOW", vSubtask, zLEVEL_TASK );

   // Disable focus to this window
   SetWindowState( vSubtask, zWINDOW_STATUS_ENABLED, FALSE );

   TransferToEditor( vSubtask, vMETAOBJECT, "WD", 0 );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_ControlPostBuild( zVIEW vSubtask )
{
   zVIEW   vTZPESRCO;
   zVIEW   vTZ__PRFO;
   zVIEW   vTZPNTBAR;
   zSHORT  nRC;

   // Get Views
   GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK );
   oTZ__PRFO_GetViewToProfile( &vTZ__PRFO, "WD", vSubtask, zCURRENT_OI );

   if ( GetViewByName( &vTZPNTBAR, "TZPNTBAR", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( vTZPNTBAR );

   ActivateEmptyObjectInstance( &vTZPNTBAR, "TZPNTBAR", vSubtask, zMULTIPLE );
   SetNameForView( vTZPNTBAR, "TZPNTBAR", vSubtask, zLEVEL_TASK );

   OrderEntityForView( vTZPESRCO, "ControlDef", "Tag A" );

   for ( nRC = SetCursorFirstEntity( vTZPESRCO, "ControlDef", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vTZPESRCO, "ControlDef", "" ) )
   {
      // Added all not deleted controls with painter icons
      if ( CompareAttributeToString( vTZPESRCO, "ControlDef",
                                     "PainterBitmap", "" ) != 0 &&
           CompareAttributeToInteger( vTZPESRCO, "ControlDef",
                                      "Invisible", 1 ) != 0  && // no deleted Controls
           CompareAttributeToInteger( vTZPESRCO, "ControlDef",
                                      "Invisible", -2 ) != 0 )  // no Report Control
      {
         CreateEntity( vTZPNTBAR, "ToolBarIcons", zPOS_AFTER );
         SetAttributeFromAttribute( vTZPNTBAR, "ToolBarIcons", "Tag",
                                    vTZPESRCO, "ControlDef", "Tag" );
         if ( SetEntityCursor( (zVIEW) vTZ__PRFO, "ControlDef", "Tag",
                               zPOS_FIRST | zQUAL_ENTITYATTR,
                               vTZPESRCO, "ControlDef", "Tag",
                               0, 0, 0 ) >= zCURSOR_SET )
         {
            SetAttributeFromInteger( vTZPNTBAR, "ToolBarIcons", "OnPalette", 1 );
         }
         else
         {
            SetAttributeFromInteger( vTZPNTBAR, "ToolBarIcons", "OnPalette", 0 );
         }
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_Control_Cancel
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_Control_Cancel( zVIEW vSubtask )
{
   zVIEW  vTZPNTBAR;

   if ( GetViewByName( &vTZPNTBAR, "TZPNTBAR", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( vTZPNTBAR );

   return( 0 );
} // zwTZPNTRAD_Control_Cancel

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_Control_OK( zVIEW vSubtask )
{
   zVIEW  vTZ__PRFO;
   zVIEW  vTZPNMWIN;
   zVIEW  vTZPNTBAR;
   zSHORT nRC;

   GetViewByName( &vTZPNTBAR, "TZPNTBAR", vSubtask, zLEVEL_TASK );

   nRC = SetCursorFirstEntityByInteger( vTZPNTBAR, "ToolBarIcons",
                                        "OnPalette", 1, "" );

   if ( nRC < zCURSOR_SET )
   {
      MessageSend( vSubtask, "PN???OK", "Dialog Maintenance",
                   "At least one control must\nbe selected on the Palette",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_TerminateActionForError, 0, 0 );
      return( 1 );
   }

   oTZ__PRFO_GetViewToProfile( &vTZ__PRFO, "WD", vSubtask, zCURRENT_OI );

   nRC = SetCursorFirstEntity( vTZ__PRFO, "ControlDef", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      nRC = DeleteEntity( vTZ__PRFO, "ControlDef", zREPOS_NEXT );
   }

   // This stuff has already been set and checked above.
   nRC = zCURSOR_SET;

   while ( nRC >= zCURSOR_SET )
   {
      CreateEntity( vTZ__PRFO, "ControlDef", zPOS_AFTER );
      SetAttributeFromAttribute( vTZ__PRFO, "ControlDef", "Tag",
                                 vTZPNTBAR, "ToolBarIcons", "Tag" );
      nRC = SetCursorNextEntityByInteger( vTZPNTBAR, "ToolBarIcons",
                                          "OnPalette", 1, "" );
   }

   oTZ__PRFO_CommitProfile( vTZ__PRFO );

   GetViewByName( &vTZPNMWIN, "TZPNMWIN", vSubtask, zLEVEL_TASK );
   fnPainterCall( zMSG_REPLACETOOLBARBUTTONS, vTZPNMWIN, 0, 0, 0 );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_InitVOR_Transfer( zVIEW vSubtask )
{
   zVIEW    vTZZOVEAO;

   // Drop the previous instance if it exists.
   if ( GetViewByName( &vTZZOVEAO, "TZZOVEAO", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vTZZOVEAO );

   zwTZPNTRAD_InitModalSubwindow( vSubtask );
   return( 0 );
}

// All actions which go to a modal sub-window from the painter main window
// should use this operation to cause the window to be updated prior to
// going to the sub-window.
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_InitModalSubwindow( zVIEW vSubtask )
{
   zVIEW  vWindow;

   GetViewByName( &vWindow, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( vWindow )
   {
      zVIEW vEvents;
      zVIEW vTZPESRCO;

      // Update the zeidon window before anything else
      fnPainterCall( zMSG_UPDATEZEIDONWINDOW, vSubtask, 0, 0, 0 );

      // Create an Events Object for window events
      if ( GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK ) > 0 )
      {
         DropObjectInstance( vEvents );
      }

      ActivateEmptyObjectInstance( &vEvents, "TZPNEVWO",
                                   vSubtask, zMULTIPLE );
      SetNameForView( vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
      GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK );
      SetCursorFirstEntity( vTZPESRCO, "WindowStyle", 0 );

      if ( SetCursorFirstEntity( vTZPESRCO, "EventDef", 0 ) == zCURSOR_SET )
      {
         do
         {
            CreateEntity( vEvents, "Event", zPOS_AFTER );
            SetMatchingAttributesByName( vEvents, "Event",
                                         vTZPESRCO, "EventDef", zSET_ALL );
            CreateEntity( vEvents, "EventAct", zPOS_AFTER );

         }  while ( SetCursorNextEntity( vTZPESRCO,
                                         "EventDef", 0 ) == zCURSOR_SET );
      }

      // Now set the actions defined for the window
      if ( SetCursorFirstEntity( vWindow, "WndEvent", 0 ) > zCURSOR_UNCHANGED )
      {
         zLONG lType;
         do
         {
            GetIntegerFromAttribute( &lType, vWindow,
                                    "WndEvent", "Type" );
            if ( SetCursorFirstEntityByInteger( vEvents, "Event", "Type",
                                                lType, 0 ) > zCURSOR_UNCHANGED )
            {
               SetMatchingAttributesByName( vEvents, "EventAct",
                                            vWindow, "WndAct",
                                            zSET_ALL );
            }
         } while ( SetCursorNextEntity( vWindow,
                                        "WndEvent", 0 ) > zCURSOR_UNCHANGED );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZPNTRAD_HelpAbout
//
// PURPOSE:    This Entry does the About
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_HelpAbout( zVIEW vSubtask )
{
   IssueToolAbout( vSubtask, zTOOL_DIALOG, __FILE__, __DATE__, __TIME__ );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZPNTRAD_HelpBasics
//
// PURPOSE:    This Entry transfers to basic help
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_HelpBasics( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, BASICS_MANUAL );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZPNTRAD_HelpOnHelp
//
// PURPOSE:    This Entry transfers to HelpOnHelp
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_HelpOnHelp( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, SYSTEM_HELP );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZPNTRAD_HelpContents
//
// PURPOSE:    This Entry transfers to help Contents
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_HelpContents( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, USERS_GUIDE );
   return( 0 );
}
// END OF PAINTER DIALOG OPERATIONS

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_PreBuildSelControls( zVIEW vSubtask )
{
   zVIEW  vTZPESRCO;
   zVIEW  vTZ__PRFO;

   GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK );
   oTZ__PRFO_GetViewToProfile( &vTZ__PRFO, "WD", vSubtask, zCURRENT_OI );
   if ( SetCursorFirstEntity( (zVIEW) vTZ__PRFO, "ControlDef", 0 ) < zCURSOR_SET )
   {
      SetAllSelStatesForEntityForSet( vTZPESRCO, "ControlDef", 1, 1, 0 );
   }
   else
   {
      SetAllSelStatesForEntityForSet( vTZPESRCO, "ControlDef", 0, 1, 0 );
      do
      {
         if ( SetEntityCursor( vTZPESRCO, "ControlDef", "Tag",
                               zPOS_FIRST | zQUAL_ENTITYATTR,
                               (zVIEW) vTZ__PRFO, "ControlDef", "Tag",
                               0, 0, 0 ) >= zCURSOR_SET )
         {
            SetSelectStateOfEntityForSet( vTZPESRCO, "ControlDef", 1, 1 );
         }

      } while ( SetCursorNextEntity( (zVIEW) vTZ__PRFO, "ControlDef", 0 )
                                                          >= zCURSOR_SET );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_UpdateToolbarControls( zVIEW vSubtask )
{
   zVIEW  vTZPESRCO;
   zVIEW  vTZ__PRFO;
   zVIEW  vTZPNMWIN;

   GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK );
   oTZ__PRFO_GetViewToProfile( &vTZ__PRFO, "WD", vSubtask, zCURRENT_OI );
   if ( SetCursorFirstEntity( vTZ__PRFO, "ControlDef", 0 ) >= zCURSOR_SET )
   {
      while ( DeleteEntity( vTZ__PRFO, "ControlDef",
                            zREPOS_NEXT ) == zCURSOR_SET );
   }

   if ( SetCursorFirstSelectedEntity( vTZPESRCO, "ControlDef", 0 )
                                                      >= zCURSOR_SET )
   {
      do
      {
         CreateEntity( vTZ__PRFO, "ControlDef", zPOS_AFTER );
         SetAttributeFromAttribute( vTZ__PRFO, "ControlDef", "Tag",
                                    vTZPESRCO, "ControlDef", "Tag" );
      } while ( SetCursorNextSelectedEntity( vTZPESRCO, "ControlDef", 0 )
                                                           >= zCURSOR_SET );
   }

   oTZ__PRFO_CommitProfile( vTZ__PRFO );
   SetAllSelStatesForEntityForSet( vTZPESRCO, "ControlDef", 0, 1, 0 );
   GetViewByName( &vTZPNMWIN, "TZPNMWIN", vSubtask, zLEVEL_TASK );
   fnPainterCall( zMSG_REPLACETOOLBARBUTTONS, vTZPNMWIN, 0, 0, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_CancelToolbarControls( zVIEW vSubtask )
{
   zVIEW  vTZPESRCO;

   GetViewByName( &vTZPESRCO, "TZPESRCO", vSubtask, zLEVEL_TASK );
   SetAllSelStatesForEntityForSet( vTZPESRCO, "ControlDef", 0, 1, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
WND_UPD_Popup( zVIEW vSubtask )
{
   zwTZPNTRAD_LoadEventPopups( vSubtask,
                               "UpdateAction",
                               "NewAction",
                               "SelectAction",
                               "RemoveAction",
                               "WND_UPD_OperationEdit",
                               "WND_UPD_Popup" );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
OPT_UPD_Popup( zVIEW vSubtask )
{
   zwTZPNTRAD_LoadEventPopups( vSubtask,
                               "UpdateAction",
                               "NewAction",
                               "SelectAction",
                               "RemoveAction",
                               "",
                               "OPT_UPD_Popup" );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    ControlActionDetail
//
// PURPOSE:  This function sets the TZWINDOW cursor to the correct
//           Action.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ControlActionDetail( zVIEW vSubtask )
{
   zVIEW    vDialogC;
   zVIEW    vDialogW;

   GetViewByName( &vDialogC, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vDialogC, "EventAct" ) == zCURSOR_SET )
   {
      SetCursorFirstEntityByAttr( vDialogW, "Action", "Tag",
                                  vDialogC, "EventAct", "Tag", "" );
      CreateTemporalSubobjectVersion( vDialogW, "Action" );
   }
   else
   {
      MessageSend( vSubtask, "PN00218", "Dialog Maintenance",
                   "No Action exists for Button.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
SetScrollbars( zVIEW vSubtask )
{
   zLONG lState = GetOptionState( vSubtask, "ScrollBars",
                                  zOPTION_STATUS_CHECKED );
   lState = !lState;
   SetOptionState( vSubtask, "ScrollBars", zOPTION_STATUS_CHECKED, lState );
   fnPainterCall( zMSG_SETSCROLLBARS, vSubtask, 0, (zPCHAR) lState, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
SetGrid( zVIEW vSubtask )
{
   zLONG lState = GetOptionState( vSubtask, "Grid",
                                  zOPTION_STATUS_CHECKED );
   lState = !lState;
   SetOptionState( vSubtask, "Grid", zOPTION_STATUS_CHECKED, lState );
   fnPainterCall( zMSG_SETGRID, vSubtask, 0, (zPCHAR) lState, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
InitMenu( zVIEW vSubtask )
{
   zCHAR   szLabel[ 64 ];
   zBOOL   bVisible;

   SetDrawMenuBar( vSubtask, FALSE );

   bVisible = (zBOOL) GetCtrlState( vSubtask, "ControlBar",
                                    zCONTROL_STATUS_VISIBLE );
   SetOptionState( vSubtask, "ShowHideControlBar", zOPTION_STATUS_TEXT,
                   (zULONG) (bVisible ? "Hide Control Bar" : "Show Control Bar") );

   if ( zwTZPNTRAD_InitMenuItems( vSubtask ) < 0 )
   {
      SetDrawMenuBar( vSubtask, TRUE );
      return( -1 );
   }

   if ( fnPainterCall( zMSG_UNDO, vSubtask, 0, szLabel, zsizeof( szLabel ) ) == 0 )
   {
      SetOptionState( vSubtask, "Undo", zOPTION_STATUS_TEXT, (zULONG) szLabel );
      SetOptionState( vSubtask, "Undo", zOPTION_STATUS_ENABLED, 1 );
   }
   else
   {
      SetOptionState( vSubtask, "Undo", zOPTION_STATUS_TEXT,
                      (zULONG) "&Undo\tCtrl+Z" );
      SetOptionState( vSubtask, "Undo", zOPTION_STATUS_ENABLED, 0 );
   }

   if ( fnPainterCall( zMSG_REDO, vSubtask, 0, szLabel, zsizeof( szLabel ) ) == 0 )
   {
      SetOptionState( vSubtask, "Redo", zOPTION_STATUS_TEXT, (zULONG) szLabel );
      SetOptionState( vSubtask, "Redo", zOPTION_STATUS_ENABLED, 1 );
   }
   else
   {
      SetOptionState( vSubtask, "Redo", zOPTION_STATUS_TEXT, (zULONG) "&Redo\tCtrl+Y" );
      SetOptionState( vSubtask, "Redo", zOPTION_STATUS_ENABLED, 0 );
   }

   if ( fnPainterCall( zMSG_GETTABBING, vSubtask, 0, 0, 0 ) == 0 )
   {
      SetOptionState( vSubtask, "ShowHide", zOPTION_STATUS_TEXT,
                      (zULONG) "Show &Tabstops" );
   }
   else
   {
      SetOptionState( vSubtask, "ShowHide", zOPTION_STATUS_TEXT,
                      (zULONG) "Hide &Tabstops" );
   }

   SetOptionState( vSubtask, "DeleteControls", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "AlignLeft", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "AlignRight", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "AlignTop", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "AlignBottom", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "EqualHeight", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "EqualWidth", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "EqualWidthHeight", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "EquiSpaceVertical", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "EquiSpaceHorizontal", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "AbutVertical", zOPTION_STATUS_ENABLED, 1 );
   SetOptionState( vSubtask, "AbutHorizontal", zOPTION_STATUS_ENABLED, 1 );

   if ( fnPainterCall( zMSG_CLIPBOARD_COPY, vSubtask, 0, szLabel, zsizeof( szLabel ) ) == 0 )
      SetOptionState( vSubtask, "Copy", zOPTION_STATUS_ENABLED, 1 );
   else
      SetOptionState( vSubtask, "Copy", zOPTION_STATUS_ENABLED, 0 );

   if ( fnPainterCall( zMSG_CLIPBOARD_PASTE, vSubtask, 0, szLabel, zsizeof( szLabel ) ) == 0 )
      SetOptionState( vSubtask, "Paste", zOPTION_STATUS_ENABLED, 1 );
   else
      SetOptionState( vSubtask, "Paste", zOPTION_STATUS_ENABLED, 0 );

   if ( fnPainterCall( zMSG_CLIPBOARD_PASTE_MENU, vSubtask, 0, szLabel, zsizeof( szLabel ) ) == 0 )
      SetOptionState( vSubtask, "PasteMenu", zOPTION_STATUS_ENABLED, 1 );
   else
      SetOptionState( vSubtask, "PasteMenu", zOPTION_STATUS_ENABLED, 0 );

   SetDrawMenuBar( vSubtask, TRUE );
   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
WindowListClose( zVIEW vSubtask )
{
   zVIEW vMainWindow;

   if ( GetViewByName( &vMainWindow, "TZPNMWIN", vSubtask, zLEVEL_TASK ) >= zCURSOR_SET )
   {
      // set Check-Status for WindowList
   // SetOptionState( vMainWindow, "WindowList", zOPTION_STATUS_CHECKED, 0 );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    CtrlContextMappingInit
//
// PURPOSE:  This function builds the MapDomain View for the Context
//           Combo Box, if there is current mapping.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
CtrlContextMappingInit( zVIEW vSubtask )
{
   zVIEW    vDialog;
   zVIEW    vCM_List;
   zVIEW    vDomain;
   zLONG    lZKey;

   if ( GetViewByName( &vDialog, "MapDomain", vSubtask, zLEVEL_TASK ) > 0 )
      DropView( vDialog );

   GetViewByName( &vDialog, "TZCONTROL", vSubtask, zLEVEL_TASK );
   RetrieveViewForMetaList( vSubtask, &vCM_List, zREFER_DOMAIN_META );

   if ( CheckExistenceOfEntity( vDialog,
                                "CtrlMapER_Attribute" ) == zCURSOR_SET )
   {
      // Activate the Domain for the current CtrlMapER_Domain.
      GetIntegerFromAttribute( &lZKey, vDialog, "CtrlMapER_Domain", "ZKey" );
      SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef",
                                     "CPLR_ZKey", lZKey, "" );
      ActivateMetaOI( vSubtask, &vDomain, vCM_List, zREFER_DOMAIN_META, 0 );
   }
   else
      ActivateEmptyObjectInstance( &vDomain, "TZDGSRCO", vSubtask, 0 );

   SetNameForView( vDomain, "MapDomain", vSubtask, zLEVEL_TASK );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListBuildContextList( zVIEW vSubtask )
{
   CtrlContextMappingInit( vSubtask );
   RefreshCtrl( vSubtask, "MapType" );
   RefreshCtrl( vSubtask, "Context" );
// RefreshCtrl( vSubtask, "Mapping" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListContextSelect( zVIEW vSubtask )
{
   MapCtrl( vSubtask, "MapType" );
   MapCtrl( vSubtask, "Context" );
   RefreshCtrl( vSubtask, "CtrlList" );
   RefreshCtrl( vSubtask, "Mapping" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListDisplayActionDetail( zVIEW vSubtask )
{
   zVIEW vControl;
   zVIEW vDialog;
   zVIEW vAction;

   GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vAction, "TZACTION", vSubtask, zLEVEL_TASK );
   if ( vAction == 0 )
   {
      // If an Action for the Event exists, position on the linked Action
      // instance and set TZACTION to TZWINDOW.  Otherwise, set TZACTION
      // to an empty instance for auto graying.
      if ( CheckExistenceOfEntity( vControl, "EventAct" ) == zCURSOR_SET )
      {
         CreateViewFromViewForTask( &vAction, vDialog, 0 );
         SetCursorFirstEntityByAttr( vAction, "Action", "Tag",
                                     vControl, "EventAct", "Tag", "" );

         SetNameForView( vAction, "TZACTION", vSubtask, zLEVEL_TASK );
      }
      else
      {
         fnCreateEmptyActionView( vSubtask, vDialog );
      }
   }

#if 0
   RefreshCtrl( vSubtask, "Operation" );
   RefreshCtrl( vSubtask, "Termination" );
   RefreshCtrl( vSubtask, "Dialog" );
   RefreshCtrl( vSubtask, "Window" );
   RefreshCtrl( vSubtask, "Function" );
#endif

   return( 0 );
}

#define zEDIT_CONTROL                       1010L
#define zMLE_CONTROL                        1015L
#define zPUSHBUTTON_CONTROL                 1020L
#define zCOMBOBOX_CONTROL                   1050L
#define zCALENDAR_CONTROL                   1060L
#define zLISTBOX_CONTROL                    1080L
#define zGROUPBOX_CONTROL                   1090L
#define zTAB_CONTROL                        2090L
#define zTABCTL_CONTROL                     2091L

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// Recursive function for moving ctrls covered by a group to be sub-ctrls
// of the group.
//
void
fnRecurseGroupCtrls( zVIEW vDialog )
{
   zVIEW  vCtrlDialog;
   zTZWDLGSO_Control_DEF ControlDef;
   zTZWDLGSO_Control_DEF GroupBoxDef;
   zLONG  lKey;
   zSHORT nRC;

   ControlDef.lStructSize = sizeof( zTZWDLGSO_Control_DEF );
   ControlDef.CheckByte = 0xFE;
   GroupBoxDef.lStructSize = sizeof( zTZWDLGSO_Control_DEF );
   GroupBoxDef.CheckByte = 0xFE;
   nRC = SetCursorFirstEntity( vDialog, "Control", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lKey, vDialog, "ControlDef", "Key" );
      if ( lKey == zGROUPBOX_CONTROL )
      {
         CreateViewFromViewForTask( &vCtrlDialog, vDialog, 0 );

         // Get the structure of attributes for this group box.
         GetStructFromEntityAttrs( (zPCHAR) &GroupBoxDef, vDialog, "Control" );
         if ( GroupBoxDef.CheckByte != 0xFE )
            MessageBox( 0, "GroupBoxDef Structure Length Error", "GetStructFromEntityAttrs", MB_OK );

         nRC = SetCursorFirstEntity( vCtrlDialog, "Control", 0 );
         while ( nRC >= zCURSOR_SET )
         {
            // get the structure of attributes for this control
            GetStructFromEntityAttrs( (zPCHAR) &ControlDef, vCtrlDialog, "Control" );
            if ( ControlDef.CheckByte != 0xFE )
               MessageBox( 0, "ControlDef Structure Length Error", "GetStructFromEntityAttrs", MB_OK );

            if ( GroupBoxDef.PSDLG_X < ControlDef.PSDLG_X && GroupBoxDef.PSDLG_Y < ControlDef.PSDLG_Y &&
                 GroupBoxDef.PSDLG_X + GroupBoxDef.SZDLG_X > ControlDef.PSDLG_X + ControlDef.SZDLG_X &&
                 GroupBoxDef.PSDLG_Y + GroupBoxDef.SZDLG_Y > ControlDef.PSDLG_Y + ControlDef.SZDLG_Y )
            {
               ControlDef.PSDLG_X -= GroupBoxDef.PSDLG_X;
               ControlDef.PSDLG_Y -= GroupBoxDef.PSDLG_Y;
               SetAttributeFromInteger( vCtrlDialog, "Control", "PSDLG_X", ControlDef.PSDLG_X );
               SetAttributeFromInteger( vCtrlDialog, "Control", "PSDLG_Y", ControlDef.PSDLG_Y );
               nRC = MoveSubobject( vDialog, "CtrlCtrl", vCtrlDialog, "Control", zPOS_LAST, zREPOS_NEXT );
            }
            else
               nRC = SetCursorNextEntity( vCtrlDialog, "Control", 0 );
         }

         DropView( vCtrlDialog );
      }

      SetViewToSubobject( vDialog, "CtrlCtrl" );
      fnRecurseGroupCtrls( vDialog );
      ResetViewFromSubobject( vDialog );

      nRC = SetCursorNextEntity( vDialog, "Control", 0 );
   }
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListEnableButtonCheckbox
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
CtrlListEnableButtonCheckbox( zVIEW  vSubtask,
                              zSHORT nEnable )
{
   SetCtrlState( vSubtask, "ChangeType", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Delete", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "AddMapEntity", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "DeleteMapEntity", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "MapType", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Context", zCONTROL_STATUS_ENABLED, nEnable );

   SetCtrlState( vSubtask, "SizeableBorder", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Invisible", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Disabled", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "NoTab", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Border", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "RightJustify", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "CenterJustify", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "FullClient", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "ReadOnly", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "AbsolutePixelSize", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "AbsolutePixelPos", zCONTROL_STATUS_ENABLED, nEnable );

   SetCtrlState( vSubtask, "AutoReposX", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "AutoReposY", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "AutoResizeX", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "AutoResizeY", zCONTROL_STATUS_ENABLED, nEnable );

   return( 0 );
} // CtrlListEnableButtonCheckbox


/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListRefreshCtrls
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
CtrlListRefreshCtrls( zVIEW  vSubtask )
{
   RefreshCtrl( vSubtask, "Type" );
   RefreshCtrl( vSubtask, "Tag" );
   RefreshCtrl( vSubtask, "Text" );
   RefreshCtrl( vSubtask, "Top" );
   RefreshCtrl( vSubtask, "Left" );
   RefreshCtrl( vSubtask, "Height" );
   RefreshCtrl( vSubtask, "Width" );
   RefreshCtrl( vSubtask, "Mapping" );
   RefreshCtrl( vSubtask, "MapType" );
   RefreshCtrl( vSubtask, "Context" );
   RefreshCtrl( vSubtask, "EventAction" );
   RefreshCtrl( vSubtask, "AutoReposX" );
   RefreshCtrl( vSubtask, "AutoResizeX" );
   RefreshCtrl( vSubtask, "AutoReposY" );
   RefreshCtrl( vSubtask, "AutoResizeY" );
   RefreshCtrl( vSubtask, "DD_Src" );
   RefreshCtrl( vSubtask, "DD_Tgt" );
   RefreshCtrl( vSubtask, "DIL_Inherited" );
   RefreshCtrl( vSubtask, "DIL_Text" );
   RefreshCtrl( vSubtask, "CSS_Id" );
   RefreshCtrl( vSubtask, "CSS_Class" );
   RefreshCtrl( vSubtask, "CSS_Class1" );
   RefreshCtrl( vSubtask, "CSS_Font" );
   RefreshCtrl( vSubtask, "CSS_Position" );
   RefreshCtrl( vSubtask, "CSS_Size" );
   RefreshCtrl( vSubtask, "TabOrder" );
   RefreshCtrl( vSubtask, "WebCtrlType" );

   return( 0 );
} // CtrlListRefreshCtrls

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListEnableCtrls
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
CtrlListEnableCtrls( zVIEW  vSubtask,
                     zSHORT nEnable )
{
   CtrlListEnableButtonCheckbox( vSubtask, nEnable );

   SetCtrlState( vSubtask, "Type", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Tag", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Text", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Top", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Left", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Height", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Width", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Detail", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Common", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "Mapping", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "EventAction", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "DD_Src", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "DD_Tgt", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "DIL_Inherited", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "DIL_Text", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "CSS_Id", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "CSS_Class", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "CSS_Class1", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "CSS_Font", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "CSS_Position", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "CSS_Size", zCONTROL_STATUS_ENABLED, nEnable );
   SetCtrlState( vSubtask, "TabOrder", zCONTROL_STATUS_ENABLED, nEnable );

   CtrlListRefreshCtrls( vSubtask );

   return( 0 );
} // CtrlListEnableCtrls

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListSetCheckedState
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
CtrlListSetCheckedState( zVIEW  vSubtask,
                         zVIEW  vControl,
                         zLONG  lSubtype )
{
   if ( lSubtype & zCONTROL_SIZEABLEBORDER )
      SetCtrlState( vSubtask, "SizeableBorder", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "SizeableBorder", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_INVISIBLE )
      SetCtrlState( vSubtask, "Invisible", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "Invisible", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_DISABLED )
      SetCtrlState( vSubtask, "Disabled", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "Disabled", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_RELATIVE_POS_X )
      SetCtrlState( vSubtask, "AutoReposX", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "AutoReposX", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_RELATIVE_POS_Y )
      SetCtrlState( vSubtask, "AutoReposY", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "AutoReposY", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_RELATIVE_SIZE_X )
      SetCtrlState( vSubtask, "AutoResizeX", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "AutoResizeX", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_RELATIVE_SIZE_Y )
      SetCtrlState( vSubtask, "AutoResizeY", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "AutoResizeY", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_NOTABSTOP )
      SetCtrlState( vSubtask, "NoTab", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "NoTab", zCONTROL_STATUS_CHECKED, 0 );

   if ( (lSubtype & zCONTROL_BORDEROFF ) == 0 )
      SetCtrlState( vSubtask, "Border", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "Border", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_RIGHTJUSTIFY )
      SetCtrlState( vSubtask, "RightJustify", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "RightJustify", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_CENTERJUSTIFY )
      SetCtrlState( vSubtask, "CenterJustify", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "CenterJustify", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROL_FULL_CLIENT )
      SetCtrlState( vSubtask, "FullClient", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "FullClient", zCONTROL_STATUS_CHECKED, 0 );

   GetIntegerFromAttribute( &lSubtype, vControl, "Control", "ExtendedStyle" );
   if ( fnPainterCall( zMSG_ISREPORT, vSubtask, 0, 0, 0 ) == 0 )
   {
      if ( lSubtype & zCONTROLX_DISABLE_READONLY )
         SetCtrlState( vSubtask, "ReadOnly", zCONTROL_STATUS_CHECKED, 1 );
      else
         SetCtrlState( vSubtask, "ReadOnly", zCONTROL_STATUS_CHECKED, 0 );
   }
   else
      SetCtrlState( vSubtask, "ReadOnly", zCONTROL_STATUS_ENABLED, 0 );

   if ( lSubtype & zCONTROLX_ABSOLUTE_PIXEL_SIZE )
      SetCtrlState( vSubtask, "AbsolutePixelSize", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "AbsolutePixelSize", zCONTROL_STATUS_CHECKED, 0 );

   if ( lSubtype & zCONTROLX_ABSOLUTE_PIXEL_POS )
      SetCtrlState( vSubtask, "AbsolutePixelPos", zCONTROL_STATUS_CHECKED, 1 );
   else
      SetCtrlState( vSubtask, "AbsolutePixelPos", zCONTROL_STATUS_CHECKED, 0 );

   return( 0 );
} // CtrlListSetCheckedState

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListShowAllCtrls
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
CtrlListShowAllCtrls( zVIEW vSubtask,
                      zVIEW vControl )
{
   zVIEW  vPE;
   zVIEW  vTZWINDOWL;
   zLONG  lParentCnt;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) > 0 &&
        SetEntityCursor( vPE, "ControlDef", "Key",
                         zPOS_FIRST | zQUAL_ENTITYATTR,
                         vControl, "ControlDef", "Key",
                         0, 0, 0 ) >= zCURSOR_SET )
   {
      if ( SetCursorFirstEntity( vPE, "ValidParent", 0 ) == zCURSOR_SET )
         lParentCnt = 1;
      else
         lParentCnt = 0;
   }
   else
   {
      lParentCnt = 1;
   }

   if ( !ComponentIsCheckedOut( vSubtask, vTZWINDOWL, zSOURCE_DIALOG_META ) )
   {
      CtrlListEnableButtonCheckbox( vSubtask, FALSE );
      SetCtrlState( vSubtask, "Detail", zCONTROL_STATUS_ENABLED, TRUE );
      SetCtrlState( vSubtask, "Common", zCONTROL_STATUS_ENABLED, TRUE );
      CtrlListRefreshCtrls( vSubtask );
   }
   else
   {
      CtrlListEnableCtrls( vSubtask, TRUE );
      if ( lParentCnt )
         SetCtrlState( vSubtask, "ChangeType", zCONTROL_STATUS_ENABLED, FALSE );
   }

   return( 0 );
} // CtrlListShowAllCtrls

zSHORT
fnShowCtrlList( zVIEW vSubtask )
{
   zVIEW vDialog;
   zVIEW vControl;
   zCHAR  szEntityName[ 33 ];
   zLONG lSubtype;

   if ( GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK ) >= 0 )
      DropView( vControl );

   if ( GetViewByName( &vControl, "TZACTION", vSubtask, zLEVEL_TASK ) >= 0 )
      DropView( vControl );

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) >= 0 )
      SetNameForView( vDialog, "NoRefresh", vSubtask, zLEVEL_TASK );

   if ( OL_GetCurrentEntityName( vSubtask, "CtrlList",
                                 &vDialog, szEntityName ) >= 0 &&
        zstrcmp( szEntityName, "Control" ) == 0 )
   {
      TraceLineS( "ShowCtrlList EntityName is Control: ", szEntityName );
      CreateViewFromViewForTask( &vControl, vDialog, 0 );
      SetViewFromView( vControl, vDialog );
      SetNameForView( vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );
      SetNameForView( vControl, "TZCTLMAP2", vSubtask, zLEVEL_TASK );

      // Build the TZPNEVWO object for the control events.
      fnPainterCall( zMSG_BUILDTZPNEVWO, vSubtask, 0, 0, 0 );

      // if Dialog check out, enable all Controls
      CtrlListShowAllCtrls( vSubtask, vControl );

      GetIntegerFromAttribute( &lSubtype, vControl, "Control", "Subtype" );
      CtrlListSetCheckedState( vSubtask, vControl, lSubtype );

      // Set up the Context
      CtrlContextMappingInit( vSubtask );
      CtrlListDisplayActionDetail( vSubtask );
   }
   else
   {
      TraceLineS( "ShowCtrlList EntityName: ", szEntityName );
      if ( GetViewByName( &vControl, "TZPNEVWO", vSubtask, zLEVEL_TASK ) >= 0 )
         DropView( vControl );

      RefreshCtrl( vSubtask, "Mapping" );
      RefreshCtrl( vSubtask, "EventAction" );
      RefreshCtrl( vSubtask, "MapType" );
      RefreshCtrl( vSubtask, "Context" );

      // Disable all Controls
      CtrlListEnableCtrls( vSubtask, FALSE );

      if ( GetViewByName( &vControl, "MapDomain", vSubtask, zLEVEL_TASK ) > 0 )
         DropView( vControl );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ShowCtrlList( zVIEW vSubtask )
{
   ED_LimitTextLength( vSubtask, "DIL_Text", 126 );
   ED_LimitTextLength( vSubtask, "FindText", 255 );
   SetCtrlState( vSubtask, "FindByTag", zCONTROL_STATUS_CHECKED, 1 );
   SetCtrlState( vSubtask, "FindByText", zCONTROL_STATUS_CHECKED, 1 );
   SetCtrlText( vSubtask, "InvisibleForFind", "" );

   return( fnShowCtrlList( vSubtask ) );
}

zSHORT
fnResetTagsR( zVIEW vDialog )
{
   zCHAR  szTag[ 33 ];
   zSHORT nLth;
   zSHORT nRC;

   // Loop through all Controls at this level.
   nRC = SetCursorFirstEntity( vDialog, "Control", "" );
   while ( nRC >= zCURSOR_SET )
   {
      GetStringFromAttribute( szTag, zsizeof( szTag ), vDialog, "Control", "Tag" );
      nLth = (zSHORT) zstrlen( szTag );
      if ( nLth > 0 && szTag[ nLth - 1 ] >= '0' && szTag[ nLth - 1 ] <= '9' )
         nLth--;

      if ( nLth > 0 )
      {
         szTag[ nLth ] = 0;
         SetAttributeFromString( vDialog, "Control", "Tag", szTag );
      }

      // Process any sub-controls.
      if ( CheckExistenceOfEntity( vDialog, "CtrlCtrl" ) == 0 )
      {
         SetViewToSubobject( vDialog, "CtrlCtrl" );
         fnResetTagsR( vDialog );
         ResetViewFromSubobject( vDialog );
      }

      nRC = SetCursorNextEntity( vDialog, "Control", "" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListResetTags( zVIEW vSubtask )
{
   zVIEW  vDialog;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      while ( ResetViewFromSubobject( vDialog ) == 0 )
      {
      }

      fnResetTagsR( vDialog );
   }

   RefreshCtrl( vSubtask, "CtrlList" );
   RefreshCtrl( vSubtask, "Tag" );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListSaveStyleFlags
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
CtrlListSaveStyleFlags( zVIEW vSubtask,
                        zVIEW vControl )
{
   zLONG lSubtype;

   GetIntegerFromAttribute( &lSubtype, vControl, "Control", "Subtype" );

    // Is Tab Presentation active?
   if ( TAB_GetActiveTab( vSubtask, "CtrlListTab" ) == 3 )
   {
      if ( GetCtrlState( vSubtask, "SizeableBorder", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_SIZEABLEBORDER;
      else
         lSubtype &= ~zCONTROL_SIZEABLEBORDER;

      if ( GetCtrlState( vSubtask, "Invisible", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_INVISIBLE;
      else
         lSubtype &= ~zCONTROL_INVISIBLE;

      if ( GetCtrlState( vSubtask, "Disabled", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_DISABLED;
      else
         lSubtype &= ~zCONTROL_DISABLED;

      if ( GetCtrlState( vSubtask, "NoTab", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_NOTABSTOP;
      else
         lSubtype &= ~zCONTROL_NOTABSTOP;

      if ( GetCtrlState( vSubtask, "Border", zCONTROL_STATUS_CHECKED ) == 0 )
         lSubtype |= zCONTROL_BORDEROFF;
      else
         lSubtype &= ~zCONTROL_BORDEROFF;

      if ( GetCtrlState( vSubtask, "RightJustify", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_RIGHTJUSTIFY;
      else
         lSubtype &= ~zCONTROL_RIGHTJUSTIFY;

      if ( GetCtrlState( vSubtask, "CenterJustify", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_CENTERJUSTIFY;
      else
         lSubtype &= ~zCONTROL_CENTERJUSTIFY;

      if ( GetCtrlState( vSubtask, "FullClient", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_FULL_CLIENT;
      else
         lSubtype &= ~zCONTROL_FULL_CLIENT;
   }

   // Is Tab Misc active?
   if ( TAB_GetActiveTab( vSubtask, "CtrlListTab" ) == 4 )
   {
      if ( GetCtrlState( vSubtask, "AutoReposX", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_RELATIVE_POS_X;
      else
         lSubtype &= ~zCONTROL_RELATIVE_POS_X;

      if ( GetCtrlState( vSubtask, "AutoReposY", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_RELATIVE_POS_Y;
      else
         lSubtype &= ~zCONTROL_RELATIVE_POS_Y;

      if ( GetCtrlState( vSubtask, "AutoResizeX", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_RELATIVE_SIZE_X;
      else
         lSubtype &= ~zCONTROL_RELATIVE_SIZE_X;

      if ( GetCtrlState( vSubtask, "AutoResizeY", zCONTROL_STATUS_CHECKED ) )
         lSubtype |= zCONTROL_RELATIVE_SIZE_Y;
      else
         lSubtype &= ~zCONTROL_RELATIVE_SIZE_Y;
   }

   SetAttributeFromInteger( vControl, "Control", "Subtype", lSubtype );

   return( 0 );
} // CtrlListSaveStyleFlags


zOPER_EXPORT zSHORT OPERATION
SaveCtrlList( zVIEW vSubtask )
{
   zVIEW vControl;
   zLONG lSubtype = 0;

   if ( GetViewByName( &vControl, "TZPNEVWO", vSubtask, zLEVEL_TASK ) > 0 )
      TraceLineS( "SaveCtrlList ", "Found TZPNEVWO" );
   else
      TraceLineS( "SaveCtrlList ", "NOT Found TZPNEVWO" );

   GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );
   if ( vControl )
   {
//    MessageBox( 0, "SaveCtrlList", "Control", MB_OK | MB_SYSTEMMODAL );
      if ( MapCtrl( vSubtask, "Tag" ) == 0 &&
           MapCtrl( vSubtask, "Text" ) == 0 &&
           MapCtrl( vSubtask, "Top" ) == 0 &&
           MapCtrl( vSubtask, "Left" ) == 0 &&
           MapCtrl( vSubtask, "Height" ) == 0 &&
           MapCtrl( vSubtask, "Width" ) == 0 &&
           MapCtrl( vSubtask, "AutoReposX" ) == 0 &&
           MapCtrl( vSubtask, "AutoResizeX" ) == 0 &&
           MapCtrl( vSubtask, "AutoReposY" ) == 0 &&
           MapCtrl( vSubtask, "AutoResizeY" ) == 0 &&
           MapCtrl( vSubtask, "DD_Src" ) == 0 &&
           MapCtrl( vSubtask, "DD_Tgt" ) == 0 &&
           MapCtrl( vSubtask, "DIL_Inherited" ) == 0 &&
           MapCtrl( vSubtask, "DIL_Text" ) == 0 &&
           MapCtrl( vSubtask, "CSS_Id" ) == 0 &&
           MapCtrl( vSubtask, "CSS_Class" ) == 0 &&
           MapCtrl( vSubtask, "CSS_Class1" ) == 0 &&
           MapCtrl( vSubtask, "CSS_Font" ) == 0 &&
           MapCtrl( vSubtask, "CSS_Position" ) == 0 &&
           MapCtrl( vSubtask, "CSS_Size" ) == 0 &&
           MapCtrl( vSubtask, "TabOrder" ) == 0 &&
           MapCtrl( vSubtask, "WebCtrlType" ) == 0 )
      {
         zCHAR szTag[ 33 ];

         if ( GetCtrlText( vSubtask, "Tag", szTag, zsizeof( szTag ) ) == 0 )
            OL_SetTextForCurrentItem( vSubtask, "CtrlList", szTag );

         CtrlListSaveStyleFlags( vSubtask, vControl );

         if ( fnPainterCall( zMSG_ISREPORT, vSubtask, 0, 0, 0 ) == 0 )
         {
            GetIntegerFromAttribute( &lSubtype, vControl, "Control", "ExtendedStyle" );
            // Is Tab Presentation active?
            if ( TAB_GetActiveTab( vSubtask, "CtrlListTab" ) == 3 )
            {
               if ( GetCtrlState( vSubtask, "ReadOnly", zCONTROL_STATUS_CHECKED ) )
                  lSubtype |= zCONTROLX_DISABLE_READONLY;
               else
                  lSubtype &= ~zCONTROLX_DISABLE_READONLY;
            }
         }

         // Is Tab Presentation active?
         if ( TAB_GetActiveTab( vSubtask, "CtrlListTab" ) == 3 )
         {
            if ( GetCtrlState( vSubtask, "AbsolutePixelSize", zCONTROL_STATUS_CHECKED ) )
               lSubtype |= zCONTROLX_ABSOLUTE_PIXEL_SIZE;
            else
               lSubtype &= ~zCONTROLX_ABSOLUTE_PIXEL_SIZE;

            if ( GetCtrlState( vSubtask, "AbsolutePixelPos", zCONTROL_STATUS_CHECKED ) )
               lSubtype |= zCONTROLX_ABSOLUTE_PIXEL_POS;
            else
               lSubtype &= ~zCONTROLX_ABSOLUTE_PIXEL_POS;
         }

         if ( fnPainterCall( zMSG_ISREPORT, vSubtask, 0, 0, 0 ) == 0 )
            SetAttributeFromInteger( vControl, "Control", "ExtendedStyle", lSubtype );
      }
      else
      {
         TraceLineS( "SaveCtrlList Mapping Error", "" );
         SetWindowActionBehavior( vSubtask, zWAB_TerminateActionForError,
                                  0, 0 );
         return( -1 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListMapping( zVIEW vSubtask )
{
   zVIEW vDialog;
   zCHAR  szEntityName[ 33 ];

// TraceLineS( "CtrlListMapping", "" );
   if ( OL_GetCurrentEntityName( vSubtask, "CtrlList",
                                 &vDialog, szEntityName ) >= 0 &&
        zstrcmp( szEntityName, "Control" ) == 0 )
   {
      while ( ResetViewFromSubobject( vDialog ) == 0 )
      {
      }

      GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
      if ( vDialog )
         SetNameForView( vDialog, "NoRefresh", vSubtask, zLEVEL_TASK );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListRefreshMapping( zVIEW vSubtask )
{
   RefreshCtrl( vSubtask, "Mapping" );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListCancel
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
CtrlListCancel( zVIEW vSubtask )
{
   zVIEW  vDialog;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      DropNameForView( vDialog, "NoRefresh", vSubtask, zLEVEL_TASK );
      while ( ResetViewFromSubobject( vDialog ) == 0 )
      {
      }
   }

   if ( GetViewByName( &vDialog, "MapDomain", vSubtask, zLEVEL_TASK ) > 0 )
      DropView( vDialog );

   return( 0 );
} // CtrlListCancel

zOPER_EXPORT zSHORT OPERATION
ReturnFromCtrlList( zVIEW vSubtask )
{
   zVIEW  vDialog;

   if ( SaveCtrlList( vSubtask ) < 0 )
      return( -1 );

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
   // TraceLineS( "ReturnFromCtrlList ResetViewFromSubobject", "" );
      DropNameForView( vDialog, "NoRefresh", vSubtask, zLEVEL_TASK );
      while ( ResetViewFromSubobject( vDialog ) == 0 )
      {
      }
   }

   if ( GetViewByName( &vDialog, "MapDomain", vSubtask, zLEVEL_TASK ) > 0 )
      DropView( vDialog );

   fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );
   SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent |
                                      zWAB_ProcessImmediateReturn, 0, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ReturnToCtrlList( zVIEW vSubtask )
{
   zVIEW  vDialog;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      while ( ResetViewFromSubobject( vDialog ) == 0 )
      {
      }
   }

   ShowCtrlList( vSubtask );
   return( 1 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      PreviousWindowCtrlList
//
//  PURPOSE:    To Update the previous Window Ctrl List
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
PreviousWindowCtrlList( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vDialogL;
   zVIEW  vMapDomain;

   if ( SaveCtrlList( vSubtask ) < 0 )
      return( -1 );

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
   // TraceLineS( "ReturnFromCtrlList ResetViewFromSubobject", "" );
      DropNameForView( vDialog, "NoRefresh", vSubtask, zLEVEL_TASK );
      while ( ResetViewFromSubobject( vDialog ) == 0 )
      {
      }

      if ( SetCursorPrevEntity( vDialog, "Window", "" ) != 0 )
         SetCursorLastEntity( vDialog, "Window", "" );

      if ( GetViewByName( &vDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) > 0 )
         SetViewFromView( vDialogL, vDialog );
   }

   if ( GetViewByName( &vMapDomain, "MapDomain", vSubtask, zLEVEL_TASK ) > 0 )
      DropView( vMapDomain );

// zwTZPNTRAD_InitModalSubwindow( vSubtask );
   OL_ResetNodeList( vSubtask, "CtrlList" );
   ShowCtrlList( vSubtask );
   RefreshCtrl( vSubtask, "Name" );
   RefreshCtrl( vSubtask, "Caption" );
   RefreshCtrl( vSubtask, "CtrlList" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      NextWindowCtrlList
//
//  PURPOSE:    To Update the next Window Ctrl List
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
NextWindowCtrlList( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vDialogL;
   zVIEW  vMapDomain;

   if ( SaveCtrlList( vSubtask ) < 0 )
      return( -1 );

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
   // TraceLineS( "ReturnFromCtrlList ResetViewFromSubobject", "" );
      DropNameForView( vDialog, "NoRefresh", vSubtask, zLEVEL_TASK );
      while ( ResetViewFromSubobject( vDialog ) == 0 )
      {
      }

      if ( SetCursorNextEntity( vDialog, "Window", "" ) != 0 )
         SetCursorFirstEntity( vDialog, "Window", "" );

      if ( GetViewByName( &vDialogL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) > 0 )
         SetViewFromView( vDialogL, vDialog );
   }

   if ( GetViewByName( &vMapDomain, "MapDomain", vSubtask, zLEVEL_TASK ) > 0 )
      DropView( vMapDomain );

// zwTZPNTRAD_InitModalSubwindow( vSubtask );
   OL_ResetNodeList( vSubtask, "CtrlList" );
   ShowCtrlList( vSubtask );
   RefreshCtrl( vSubtask, "Name" );
   RefreshCtrl( vSubtask, "Caption" );
   RefreshCtrl( vSubtask, "CtrlList" );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListPopup( zVIEW vSubtask )
{
   CreateTrackingPopupMenu( vSubtask, "CtrlListPopup", -1, 0, FALSE, FALSE );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:      CtrlListRemoveAction
//
// PURPOSE:    To Remove an action from a ctrl.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
CtrlListRemoveAction( zVIEW vSubtask )
{
   zVIEW    vDialog;
   zVIEW    vEvents;
   zLONG    lType;

   GetViewByName( &vDialog, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );

   GetIntegerFromAttribute( &lType, vEvents, "Event", "Type" );
   if ( SetCursorFirstEntityByInteger( vDialog, "Event", "Type",
                                       lType, 0 ) == zCURSOR_SET )
   {
      if ( CheckExistenceOfEntity( vDialog, "EventAct" ) == zCURSOR_SET )
         ExcludeEntity( vDialog, "EventAct", zREPOS_PREV );

      DeleteEntity( vDialog, "Event", zREPOS_PREV );
   }

   fnSetupEventList( vSubtask, vDialog );
   RefreshCtrl( vSubtask, "EventAction" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    CtrlListSelectAction
//
// PURPOSE:  This function creates the Event entity for the ctrl.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
CtrlListSelectAction( zVIEW vSubtask )
{
   zVIEW    vDialogC;
   zVIEW    vDialogW;
   zVIEW    vEvents;
   zVIEW    vWork;
   zLONG    lType;

   GetViewByName( &vDialogC, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   while ( ResetViewFromSubobject( vDialogW ) == 0 )
   {
   }

   GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vWork, "TZPNCTWO", vSubtask, zLEVEL_TASK );

   // Error if no Event was selected.
   if ( SetCursorFirstSelectedEntity( vEvents, "Event", "" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "PN00108", "Dialog Maintenance",
                   "No Event selected.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      return( -1 );
   }

   // Error if Event already exists.  Otherwise add it.
   GetIntegerFromAttribute( &lType, vEvents, "Event", "Type" );
   if ( SetCursorFirstEntityByInteger( vDialogC, "Event", "Type",
                                       lType, 0 ) >= zCURSOR_SET )
   {
      MessageSend( vSubtask, "PN00117", "Dialog Maintenance",
                   "Event already has an Action!\n"
                   "First remove the Action and then select a new one.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
      return( -1 );
   }
   else
   {
      CreateTemporalMetaEntity( vSubtask, vDialogC, "Event", zPOS_AFTER );
      SetAttributeFromInteger( vDialogC, "Event", "Type", lType );
   }

   // Set flag for LIST_ACT window graying and Action include for Control.
   SetAttributeFromString( vWork, "TZPNCTWO", "ParentIsSelectAction", "C" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    CtrlListUpdateAction
//
// PURPOSE:  This function sets the TZWINDOW cursor to the correct
//           Action.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
CtrlListUpdateAction( zVIEW vSubtask )
{
   zVIEW    vWork;
   zVIEW    vDialogW;
   zCHAR    szTag[ 34 ];

   GetViewByName( &vWork, "TZPNEVWO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogW, "TZWINDOW", vSubtask, zLEVEL_TASK );
   while ( ResetViewFromSubobject( vDialogW ) == 0 )
   {
   }

   // If EventAct exists, set cursor for Update Action window.
   // Otherwise, return an error.
   if ( (CheckExistenceOfEntity( vWork, "EventAct" ) == zCURSOR_SET) &&
        (CompareAttributeToString( vWork, "EventAct", "Tag", "" ) != 0) )
   {
      GetStringFromAttribute( szTag, zsizeof( szTag ), vWork, "EventAct", "Tag" );
      SetCursorFirstEntityByString( vDialogW, "Action", "Tag", szTag, "" );
      CreateTemporalSubobjectVersion( vDialogW, "Action" );
   }
   else
   // Position on Action that corresponds to EventAct entity instance.
   {
      MessageSend( vSubtask, "PN00107", "Dialog Maintenance",
                   "No Action exists for Event.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    CtrlListSelectOrUpdate
//
// PURPOSE:  This function calls Select or Update Action processing.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
CtrlListSelectOrUpdate( zVIEW vSubtask )
{
   zVIEW    vWork;
   zVIEW    vTZWINDOWL;

   GetViewByName( &vWork, "TZPNEVWO", vSubtask, zLEVEL_TASK );

   if ( (CheckExistenceOfEntity( vWork, "EventAct" ) == zCURSOR_SET) &&
        (CompareAttributeToString( vWork, "EventAct", "Tag", "" ) != 0) )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow,
                               "TZPNCTAD", "UPD_ACT" );
      return( CtrlListUpdateAction( vSubtask ) );
   }
   else
   {
      GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

      if ( ComponentIsCheckedOut( vSubtask, vTZWINDOWL, zSOURCE_DIALOG_META ) )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow,
                                  "TZPNCTAD", "SEL_ACT" );
         return( CtrlListSelectAction( vSubtask ) );
      }
   }

   return( 0 );
}

//./ ADD NAME=PopupMaintenance
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:     PopupMaintenance
//
//  PURPOSE:   To popup the correct menu based on the current selection
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
PopupMaintenance( zVIEW vSubtask )
{
   zVIEW  vControl;
   zCHAR  szEntityName[ 33 ];

   if ( OL_GetCurrentEntityName( vSubtask, "CtrlList",
                                 &vControl, szEntityName ) >= 0 &&
        zstrcmp( szEntityName, "Control" ) == 0 )
   {
      zVIEW  vPE;

      if ( GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) > 0 &&
           SetEntityCursor( vPE, "ControlDef", "Key",
                            zPOS_FIRST | zQUAL_ENTITYATTR,
                            vControl, "ControlDef", "Key",
                            0, 0, 0 ) >= zCURSOR_SET )
      {
         zLONG lParentCnt = CountEntitiesForView( vPE, "ValidParent" );
         zBOOL bDelete  = FALSE;
         zVIEW vDialog;

         GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );
         if ( ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
            bDelete = TRUE;

         if ( lParentCnt )
         {
            EnableAction( vSubtask, "DeleteCtrl", bDelete );
            CreateTrackingPopupMenu( vSubtask, "CtrlDetail",
                                     -1, 0, FALSE, FALSE );
         }
         else
         {
            EnableAction( vSubtask, "DeleteCtrl", bDelete );
            EnableAction( vSubtask, "ChangeCtrlType", bDelete );
            CreateTrackingPopupMenu( vSubtask, "CtrlMaintenance",
                                     -1, 0, FALSE, FALSE );
         }
         return( 0 );
      }
   }

   CreateTrackingPopupMenu( vSubtask, "Unknown", -1, 0, FALSE, FALSE );
   return( 0 );
}

//./ ADD NAME=ChangeCtrlType
// Source Module=tzpntrad.c
//////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:     ChangeCtrlType
//
//  PURPOSE:   To switch the type of a control in the painter
//
//  DESCRIPTION: This method attempts to change the selected controls
//               to the control type positioned on in the control object.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
ChangeCtrlType( zVIEW vSubtask )
{
#if 0
   zVIEW  vDialog;
   zVIEW  vControl;
   zVIEW  vPE;
   zCHAR  szEntityName[ 33 ];
   zSHORT nRC;

   if ( GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      TraceLineS( "ChangeCtrlType unable to get PE view", "" );
      return( -1 );
   }

   GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   if ( vDialog )
      SetNameForView( vDialog, "NoRefresh", vSubtask, zLEVEL_TASK );

   if ( OL_GetCurrentEntityName( vSubtask, "CtrlList", &vDialog, szEntityName ) >= 0 )
   {
      TraceLineS( "ChangeCtrlType: ", szEntityName );
      if ( zstrcmp( szEntityName, "Control" ) == 0 )
      {

#if 0
   zVIEW  vCtrlDef;
   zVIEW  vParentDef;
   zLONG  lNewType;
   zLONG  lParentType;
   zLONG  lType, lNewID;
   zSHORT nPos;
   zSHORT nRC;
   TZPainterCtrl *pCtrl;

      // Get the new type of control
      GetIntegerFromAttribute( &lNewType, vPE, "ControlDef", "Key" );
      SetNameForView( m_vDialog, szlTZCONTROL, vSubtask, zLEVEL_TASK );
      for ( nPos = 0; nPos < m_nCtrlCnt; nPos++ )
      {
         pCtrl = m_CtrlList[ nPos ];
         lParentType = 0;
         if ( pCtrl->m_pParentCtrl )
         {
            lParentType = pCtrl->m_pParentCtrl->m_lType;
         }

         lType = pCtrl->m_lType;
         if ( pCtrl->IsSelected( ) && lNewType != lType )
         {
            vParentDef = 0;
            if ( lParentType )
            {
               CreateViewFromViewForTask( &vParentDef, vPE, 0 );
               SetCursorFirstEntityByInteger( vParentDef, "ControlDef", "Key", lParentType, 0 );
            }

            pCtrl->PositionOnZeidonCtrl( );
            CreateViewFromViewForTask( &vCtrlDef, vPE, 0 );
            SetCursorFirstEntityByInteger( vCtrlDef, "ControlDef", "Key", pCtrl->m_lType, 0 );

            // PositionOnZeidonControl above may have moved the cursor in TZPESRCO to create
            // the previous control, now ensure that it is moved back to the new control
            SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key", lNewType, 0 );
            nRC = CtrlValidate( vCtrlDef, vParentDef, vPE, zCTRL_VALID_CHANGE );
            if ( nRC < 0 )
               lNewID = 0;
            else
            {
               // Get the ID of the control to be painted
               GetIntegerFromAttribute( &lNewID, vCtrlDef, "ControlDef", "Key" );
            }

            // Drop the view to the parent control if one was created
            if ( vParentDef )
               DropView( vParentDef );

            DropView( vCtrlDef );

            if ( nRC == 0 &&           // Old parent is still valid
                 lNewID == lNewType )  // Ctrl is being changed to type requested.
            {
               if ( SetCursorFirstEntity( m_vDialog, "ControlDef", 0 )
                                                          == zCURSOR_SET )
               {
                  ExcludeEntity( m_vDialog, "ControlDef", zREPOS_NONE );
               }

               SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key", lNewType, 0 );
               IncludeSubobjectFromSubobject( m_vDialog, "ControlDef", vPE, "ControlDef", zPOS_BEFORE );
               SendCtrlMsg( zCTRLMSG_CHANGE_TYPE, 0, lNewType, lType, 0, 0, pCtrl );
               RepaintZeidonCtrl( );
            }
         }

      }  while ( ResetViewFromSubobject( m_vDialog ) == 0 );
#endif
      }
   }
   else
      TraceLineS( "ChangeCtrlType: ", "Cannot locate Entity name" );

#endif

   TraceLineS( "ChangeCtrlType!!!!!!", "" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ChgCtrlPostbuild( zVIEW vSubtask )
{
   zVIEW  vControl;
   zVIEW  vPE;

   SetCtrlState( vSubtask, "OK", zCONTROL_STATUS_ENABLED, 0 );
   LB_SetDisplaySelectSet( vSubtask, "ChangeTypeList", 3 );
   LB_SetSelectSelectSet( vSubtask, "ChangeTypeList", 4 );

   GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );
   if ( vPE && SetEntityCursor( vPE, "ControlDef", "Key", zPOS_FIRST | zQUAL_ENTITYATTR,
                                vControl, "ControlDef", "Key", 0, 0, 0 ) >= zCURSOR_SET )
   {
      zCHAR  szTag[ 33 ],               szCurrTag[ 33 ];
      zCHAR  szAcceptsAllParents[ 2 ],  szCurrAcceptsAllParents[ 2 ];
      zCHAR  szAcceptsAllChildren[ 2 ], szCurrAcceptsAllChildren[ 2 ];
      zCHAR  szRequiresParent[ 2 ],     szCurrRequiresParent[ 2 ];
      zLONG  lKey,                      lCurrKey;
      zLONG  lInvisible,                lCurrInvisible;
      zLONG  lValidParentCnt,           lCurrValidParentCnt;
      zLONG  lValidChildCnt,            lCurrValidChildCnt;
      zSHORT nPrevSelSet;
      zSHORT nRC;

      GetStringFromAttribute( szTag, zsizeof( szTag ), vPE, "ControlDef", "Tag" );
      GetStringFromAttribute( szAcceptsAllParents, zsizeof( szAcceptsAllParents ), vPE,
                              "ControlDef", "AcceptsAllParents" );
      GetStringFromAttribute( szAcceptsAllChildren, zsizeof( szAcceptsAllChildren ), vPE,
                              "ControlDef", "AcceptsAllChildren" );
      GetStringFromAttribute( szRequiresParent, zsizeof( szRequiresParent ), vPE,
                              "ControlDef", "RequiresParent" );
      GetIntegerFromAttribute( &lKey, vPE, "ControlDef", "Key" );
      GetIntegerFromAttribute( &lInvisible, vPE, "ControlDef", "Invisible" );
      lValidParentCnt = CountEntitiesForView( vPE, "ValidParent" );
      lValidChildCnt = CountEntitiesForView( vPE, "ValidChild" );

      nPrevSelSet = SetSelectSetForView( vPE, 4 );
      SetAllSelectStatesForEntity( vPE, "ControlDef", FALSE, 0 );
      SetSelectSetForView( vPE, 3 );
      SetAllSelectStatesForEntity( vPE, "ControlDef", FALSE, 0 );
      SetSelectSetForView( vPE, 2 );
      SetAllSelectStatesForEntity( vPE, "ControlDef", FALSE, 0 );
      SetSelectSetForView( vPE, 1 );
      SetAllSelectStatesForEntity( vPE, "ControlDef", FALSE, 0 );

      SetSelectSetForView( vPE, 3 );
      nRC = SetCursorFirstEntity( vPE, "ControlDef", 0 );
      while ( nRC == zCURSOR_SET )
      {
         GetIntegerFromAttribute( &lCurrKey, vPE, "ControlDef", "Key" );
         if ( lCurrKey != lKey )
         {
            GetStringFromAttribute( szCurrTag, zsizeof( szCurrTag ), vPE, "ControlDef", "Tag" );
            GetStringFromAttribute( szCurrAcceptsAllParents, zsizeof( szCurrAcceptsAllParents ), vPE,
                                    "ControlDef", "AcceptsAllParents" );
            GetStringFromAttribute( szCurrAcceptsAllChildren, zsizeof( szCurrAcceptsAllChildren ), vPE,
                                    "ControlDef", "AcceptsAllChildren" );
            GetStringFromAttribute( szCurrRequiresParent, zsizeof( szCurrRequiresParent ), vPE,
                                    "ControlDef", "RequiresParent" );
            GetIntegerFromAttribute( &lCurrInvisible, vPE, "ControlDef", "Invisible" );
            lCurrValidParentCnt = CountEntitiesForView( vPE, "ValidParent" );
            lCurrValidChildCnt = CountEntitiesForView( vPE, "ValidChild" );

            if ( szAcceptsAllParents[ 0 ] == szCurrAcceptsAllParents[ 0 ] &&
                 szAcceptsAllChildren[ 0 ] == szCurrAcceptsAllChildren[ 0 ] &&
                 szRequiresParent[ 0 ] == szCurrRequiresParent[ 0 ] &&
                 lInvisible == lCurrInvisible &&
                 (lValidParentCnt == lCurrValidParentCnt || (lValidParentCnt && lCurrValidParentCnt)) &&
                 (lValidChildCnt == lCurrValidChildCnt || (lValidChildCnt && lCurrValidChildCnt)) )
            {
               SetSelectStateOfEntity( vPE, "ControlDef", TRUE );
            }
         }

         nRC = SetCursorNextEntity( vPE, "ControlDef", 0 );
      }

      SetSelectSetForView( vPE, nPrevSelSet );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ChgCtrlPickNewType( zVIEW vSubtask )
{
   zVIEW  vPE;

   GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );
   if ( GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      SetCtrlState( vSubtask, "OK", zCONTROL_STATUS_ENABLED, 0 );
      TraceLineS( "ChangeCtrlType unable to get PE view", "" );
      return( -1 );
   }

   SetCtrlState( vSubtask, "OK", zCONTROL_STATUS_ENABLED, 1 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ChgCtrlToggleCheck( zVIEW vSubtask )
{
   zVIEW  vPE;
   zSHORT nPrevSelSet;

   GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );
   if ( GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      TraceLineS( "ChangeCtrlType unable to get PE view", "" );
      return( -1 );
   }

   nPrevSelSet = SetSelectSetForView( vPE, 3 );
   SetAllSelectStatesForEntity( vPE, "ControlDef", FALSE, 0 );
   SetSelectSetForView( vPE, nPrevSelSet );

   ChgCtrlPostbuild( vSubtask );
   if ( GetCtrlState( vSubtask, "ChangeChildType", zCONTROL_STATUS_CHECKED ) == TRUE )
   {
//    SetCtrlState( vSubtask, "ChangeChildType", zCONTROL_STATUS_CHECKED, 1 );
   }
   else
   {
   }

   RefreshCtrl( vSubtask, "ChangeChild" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ChgCtrlChangeType( zVIEW vSubtask )
{
   zCHAR  szTag[ 33 ];
   zCHAR  szNewTag[ 33 ];
   zVIEW  vControl;
   zVIEW  vPE;
   zLONG  lKey;
   zSHORT nRC;

   GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );
   if ( GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      TraceLineS( "ChgCtrlChangeType unable to get PE view", "" );
      return( -1 );
   }

   if ( SetEntityCursor( vPE, "ControlDef", "Key",
                         zPOS_FIRST | zQUAL_ENTITYATTR,
                         vControl, "ControlDef", "Key",
                         0, 0, 0 ) >= zCURSOR_SET )
   {
      zCHAR  szMsg[ 512 ];
      zSHORT nPrevSelSet;

      GetStringFromAttribute( szTag, zsizeof( szTag ), vPE, "ControlDef", "Tag" );

      nPrevSelSet = SetSelectSetForView( vPE, 4 );
      SetCursorFirstSelectedEntity( vPE, "ControlDef", 0 );
      GetStringFromAttribute( szNewTag, zsizeof( szNewTag ), vPE, "ControlDef", "Tag" );
      SetSelectSetForView( vPE, nPrevSelSet );

      sprintf_s( szMsg, zsizeof( szMsg ),
                "OK to change control type from: \"%s\" to \"%s\"?\n"
                "N.B.  This is a provisional implementation and the\n"
                "integrity of the changed control cannot be guaranteed\n"
                "Please visit the detail for the control (and any\n"
                "sub-controls) to ensure integrity!\n"
                "Events and control specific information are deleted.\n"
                "Mapping is retained and may therefore be erroneous!",
                szTag, szNewTag );

      if ( MessagePrompt( vSubtask, "PExxx",
                          "Change Control Type",
                          szMsg,
                          zBEEP, zBUTTONS_YESNO,
                          zRESPONSE_NO,  0 ) != zRESPONSE_NO )
      {
         ExcludeEntity( vControl, "ControlDef", zREPOS_NONE );
         IncludeSubobjectFromSubobject( vControl, "ControlDef",
                                        vPE, "ControlDef", zPOS_BEFORE );
         SetAttributeFromBlob( vControl, "Control", "CtrlBOI", "", 0 );

         nRC = SetCursorFirstEntity( vControl, "Event", 0 );
         while ( nRC == zCURSOR_SET )
         {
            nRC = DeleteEntity( vControl, "Event", zREPOS_FIRST );
         }

         GetIntegerFromAttribute( &lKey, vPE, "ControlDef", "Key" );

         if ( SetCursorFirstEntity( vPE, "ValidChild", 0 ) == zCURSOR_SET &&
              SetEntityCursor( vPE, "ControlDef", "Key",
                               zPOS_FIRST | zQUAL_ENTITYATTR,
                               vPE, "ValidChild", "Key",
                               0, 0, 0 ) >= zCURSOR_SET )
         {
            if ( SetCursorFirstEntity( vPE, "ValidParent", 0 ) == zCURSOR_SET )
            {
               zLONG lKeyParent;

               GetIntegerFromAttribute( &lKeyParent, vPE,
                                        "ValidParent", "Key" );
               if ( lKey == lKeyParent )
               {
                  nRC = SetCursorFirstEntity( vControl, "CtrlCtrl", 0 );
                  if ( nRC == zCURSOR_SET )
                  {
                     SetViewToSubobject( vControl, "CtrlCtrl" );
                     while ( nRC == zCURSOR_SET )
                     {
                        ExcludeEntity( vControl, "ControlDef", zREPOS_NONE );
                        IncludeSubobjectFromSubobject( vControl,
                                                       "ControlDef", vPE,
                                                       "ControlDef",
                                                       zPOS_BEFORE );
                        SetAttributeFromBlob( vControl, "Control",
                                              "CtrlBOI", "", 0 );

                        nRC = SetCursorFirstEntity( vControl, "Event", 0 );
                        while ( nRC == zCURSOR_SET )
                        {
                           nRC = DeleteEntity( vControl, "Event",
                                               zREPOS_FIRST );
                        }

                        nRC = SetCursorNextEntity( vControl, "Control", 0 );
                     }

                     ResetViewFromSubobject( vControl );
                  }
               }
            }
         }
      }
   }
   else
      TraceLineS( "ChangeCtrlType: ", "Cannot locate Entity name" );

   GetViewByName( &vControl, "TZWINDOW", vSubtask, zLEVEL_TASK );
   while ( ResetViewFromSubobject( vControl ) == 0 )
   {
   }

   return( 0 );
}

void
CtrlList_LoadDetailWindow( zVIEW  vSubtask,
                           zVIEW  vPE,
                           zSHORT IsDoubleClick )
{
   zPCHAR pchDialog;
   zPCHAR pchWindow;

   // reset Expand State
   if ( IsDoubleClick )
   {
      zLONG lExpand = OL_GetCtrlState( vSubtask, "CtrlList", zCONTROL_STATUS_EXPAND );
      OL_SetCtrlState( vSubtask, "CtrlList", zCONTROL_STATUS_EXPAND, !lExpand );
   }

   GetAddrForAttribute( &pchDialog, vPE,
                        "ControlDef", "MaintenanceDialog" );
   GetAddrForAttribute( &pchWindow, vPE,
                        "ControlDef", "MaintenanceWindow" );
   SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow,
                            pchDialog, pchWindow );

}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListDetailWindow
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
CtrlListDetailWindow( zVIEW  vSubtask,
                      zSHORT nIsDoubleClick )
{
   zCHAR  szEntityName[ 33 ];
   zCHAR  *pchTag;
   zVIEW vControl;
   zVIEW vPE;

// TraceLineS( "CtrlListDetail", "" );
   if ( OL_GetCurrentEntityName( vSubtask, "CtrlList",
                                 &vControl, szEntityName ) < 0 ||
        zstrcmp( szEntityName, "Control" ) != 0 )
   {
      return( 0 );
   }

   if ( SaveCtrlList( vSubtask ) < 0 )
      return( -1 );

   GetViewByName( &vControl, "TZWINDOW", vSubtask, zLEVEL_TASK );
   while ( ResetViewFromSubobject( vControl ) == 0 )
   {
   }

   GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );
   GetAddrForAttribute( &pchTag, vControl, "Control", "Tag" );
   fnPainterCall( zMSG_SETCURRCTRL, vSubtask, 0, pchTag, 33 );
   if ( GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      TraceLineS( "CtrlListDetail unable to get PE view", "" );
      return( -1 );
   }

   if ( SetEntityCursor( vPE, "ControlDef", "Key",
                         zPOS_FIRST | zQUAL_ENTITYATTR,
                         vControl, "ControlDef", "Key",
                         0, 0, 0 ) >= zCURSOR_SET )
   {
      CtrlList_LoadDetailWindow( vSubtask, vPE, nIsDoubleClick );
   }

   return( 0 );
} // CtrlListDetailWindow

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListDetail_ByDoubleClick
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
CtrlListDetail_ByDoubleClick( zVIEW vSubtask )
{
   return( CtrlListDetailWindow( vSubtask, 1 ) );

} // CtrlListDetail_ByDoubleClick

zOPER_EXPORT zSHORT OPERATION
CtrlListDetail( zVIEW vSubtask )
{
   return( CtrlListDetailWindow( vSubtask, 0 ) );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListAddMapEntity( zVIEW vSubtask )
{
   zCHAR  szEntityName[ 33 ];
   zVIEW vControl;

// TraceLineS( "CtrlListAddMapEntity", "" );
   if ( OL_GetCurrentEntityName( vSubtask, "CtrlList",
                                 &vControl, szEntityName ) < 0 ||
        zstrcmp( szEntityName, "Control" ) != 0 )
   {
      return( 0 );
   }

   GetViewByName( &vControl, "TZCTLMAP2", vSubtask, zLEVEL_TASK );
   CreateMetaEntity( vSubtask, vControl, "CtrlMap", zPOS_AFTER );
   SetAttributeFromString( vControl, "CtrlMap", "Tag", "" );
   RefreshCtrl( vSubtask, "Mapping" );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListDeleteMapEntity( zVIEW vSubtask )
{
   zCHAR  szEntityName[ 33 ];
   zVIEW vControl;

// TraceLineS( "CtrlListDeleteMapEntity", "" );
   if ( OL_GetCurrentEntityName( vSubtask, "CtrlList",
                                 &vControl, szEntityName ) < 0 ||
        zstrcmp( szEntityName, "Control" ) != 0 )
   {
      return( 0 );
   }

   GetViewByName( &vControl, "TZCTLMAP2", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vControl, "CtrlMap" ) == zCURSOR_SET )
   {
      DeleteEntity( vControl, "CtrlMap", zREPOS_PREV );
      RefreshCtrl( vSubtask, "Mapping" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListDeleteMapAttribute( zVIEW vSubtask )
{
   zCHAR  szEntityName[ 33 ];
   zVIEW vControl;

// TraceLineS( "CtrlListDeleteMapAttribute", "" );
   if ( OL_GetCurrentEntityName( vSubtask, "CtrlList",
                                 &vControl, szEntityName ) < 0 ||
        zstrcmp( szEntityName, "Control" ) != 0 )
   {
      return( 0 );
   }

   GetViewByName( &vControl, "TZCTLMAP2", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vControl, "CtrlMap" ) == zCURSOR_SET )
   {
      ExcludeEntity( vControl, "CtrlMapER_Attribute", zREPOS_NONE );
      RefreshCtrl( vSubtask, "Mapping" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CtrlListDeleteCtrl( zVIEW vSubtask )
{
   zVIEW  vControl;
   zCHAR  szCtrlTag[ 34 ];
   zCHAR  szMsg[ 100 ];

   GetViewByName( &vControl, "TZCONTROL", vSubtask, zLEVEL_TASK );
   if ( vControl )
   {
      GetStringFromAttribute( szCtrlTag, zsizeof( szCtrlTag ), vControl, "Control", "Tag" );
      strcpy_s( szMsg, zsizeof( szMsg ), "OK to delete Control '" );
      strcat_s( szMsg, zsizeof( szMsg ), szCtrlTag );
      strcat_s( szMsg, zsizeof( szMsg ), "'?" );
      if ( MessagePrompt( vSubtask, "PE002",
                          "Dialog Maintenance",
                          szMsg, zBEEP, zBUTTONS_YESNO,
                          zRESPONSE_NO,  0 ) == zRESPONSE_YES )
      {
         DeleteEntity( vControl, "Control", zREPOS_AFTER );
         GetViewByName( &vControl, "TZWINDOW", vSubtask, zLEVEL_TASK );
         while ( ResetViewFromSubobject( vControl ) == 0 )
         {
         }
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT OPERATION
Undo( zVIEW vSubtask )
{
   fnPainterCall( zMSG_UNDO, vSubtask, 0, 0, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
Redo( zVIEW vSubtask )
{
   fnPainterCall( zMSG_REDO, vSubtask, 0, 0, 0 );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT OPERATION
CopySelectedCtrlsToClipboard( zVIEW vSubtask )
{
   fnPainterCall( zMSG_CLIPBOARD_COPY, vSubtask, 0, 0, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CopyClipboardToSelectedCtrl( zVIEW vSubtask )
{
   fnPainterCall( zMSG_CLIPBOARD_PASTE, vSubtask, 0, 0, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CopyMenuToClipboard( zVIEW vSubtask )
{
   fnPainterCall( zMSG_CLIPBOARD_COPY_MENU, vSubtask, 0, 0, 0 );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
CopyClipboardMenuToWindow( zVIEW vSubtask )
{
   fnPainterCall( zMSG_CLIPBOARD_PASTE_MENU, vSubtask, 0, 0, 0 );
   return( 0 );
}

zSHORT
fnPositionOnVOR( zVIEW     vTgt,
                 zVIEW     vSrc,
                 zVIEW     vSrcLPLR,
                 zPCHAR    pchViewName,
                 zVIEW     vSubtask )
{
   zVIEW     vVOR;
   zVIEW     vVOR_List;
   zVIEW     vLOD;
   zVIEW     vLOD_List;
   zCHAR     szMsg[ 65 ];
   zCHAR     szName[ 33 ];
   zSHORT    nRC;

   if ( SetCursorFirstEntityByString( vTgt, "ViewObjRef", "Name",
                                      pchViewName, 0 ) < 0 )
   {
      RetrieveViewForMetaList( vSubtask, &vVOR_List, zREFER_VOR_META );
      nRC = SetCursorFirstEntityByString( vVOR_List, "W_MetaDef",
                                          "Name", pchViewName, 0 );
      if ( nRC >= 0 )
      {
         ActivateMetaOI( vSubtask, &vVOR, vVOR_List, zREFER_VOR_META, zSINGLE );
         IncludeSubobjectFromSubobject( vTgt, "ViewObjRef", vVOR,
                                        "ViewObjRef", zPOS_AFTER );
      }
      else
      {
         RetrieveViewForMetaList( vSubtask, &vLOD_List, zREFER_LOD_META );
         nRC = SetCursorFirstEntityByString( vSrc, "ViewObjRef",
                                             "Name", pchViewName, 0 );
         if ( nRC < 0 )
         {
            strcpy_s( szMsg, zsizeof( szMsg ), "Window has mapping with no VOR: " );
            strcat_s( szMsg, zsizeof( szMsg ), pchViewName );
            MessageSend( vSubtask, "WD00207", "Named View Clone", szMsg,
                         zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
            DropView( vVOR_List );
            DropView( vLOD_List );
            return( -1 );
         }

         GetStringFromAttribute( szName, zsizeof( szName ), vSrc, "LOD", "Name" );
         nRC = SetCursorFirstEntityByString( vLOD_List, "W_MetaDef",
                                             "Name", szName, 0 );
         if ( nRC >= 0 )
         {
            ActivateEmptyMetaOI( vSubtask, &vVOR, zSOURCE_VOR_META, zSINGLE );
            CreateMetaEntity( vSubtask, vVOR, "ViewObjRef", zPOS_AFTER );
            SetMatchingAttributesByName( vVOR, "ViewObjRef", vSrc,
                                         "ViewObjRef", zSET_NULL );
            ActivateMetaOI( vSubtask, &vLOD, vLOD_List, zREFER_LOD_META, zSINGLE );
            IncludeSubobjectFromSubobject( vVOR, "LOD", vLOD,
                                           "LOD", zPOS_AFTER );
            CommitMetaOI( vSubtask, vVOR, zSOURCE_VOR_META );
            IncludeSubobjectFromSubobject( vTgt, "ViewObjRef", vVOR,
                                           "ViewObjRef", zPOS_AFTER );
            DropMetaOI( vSubtask, vLOD );
         }
         else
         {
            GetVariableFromAttribute( szName, 0, 'S', 33,
                                      vSrc, "LOD", "Name", "", 0 );
            strcpy_s( szMsg, zsizeof( szMsg ), "Non-existent LOD: " );
            strcat_s( szMsg, zsizeof( szMsg ), szName );
            MessageSend( vSubtask, "WD00208", "Named View Clone",
                         szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
            DropView( vVOR_List );
            DropView( vLOD_List );
            return( -1 );
         }

         DropView( vLOD_List );
      }

      DropMetaOI( vSubtask, vVOR );
      DropView( vVOR_List );
   }

   return( 0 );
}

zSHORT
fnCloneActMap( zVIEW     vSrcLPLR,
               zVIEW     vSrc,
               zVIEW     vTgt,
               zVIEW     vSubtask )
{
   zVIEW     vLOD;
   zVIEW     vLOD_List;
   zCHAR     szMsg[ 65 ];
   zCHAR     szTag[ 33 ];
   zSHORT    nRC;

   CreateMetaEntity( vSubtask, vTgt, "ActMap", zPOS_AFTER );
   SetMatchingAttributesByName( vTgt, "ActMap", vSrc, "ActMap", zSET_NULL );
   if ( CheckExistenceOfEntity( vSrc, "ActMapView" ) >= 0 )
   {
      GetStringFromAttribute( szTag, zsizeof( szTag ), vSrc, "ActMapView", "Name" );
      if ( fnPositionOnVOR( vTgt, vSrc, vSrcLPLR, szTag, vSubtask ) >= 0 )
      {
         IncludeSubobjectFromSubobject( vTgt, "ActMapView",
                                        vTgt, "ViewObjRef", zPOS_AFTER );
      }
      else
      {
         return( -1 );
      }

      RetrieveViewForMetaList( vSubtask, &vLOD_List, zREFER_LOD_META );
      GetStringFromAttribute( szTag, zsizeof( szTag ), vTgt, "LOD", "Name" );
      nRC = SetCursorFirstEntityByString( vLOD_List, "W_MetaDef",
                                          "Name", szTag, 0 );
      if ( GetViewByName( &vLOD, "TZTMPLOD", vSubtask, zLEVEL_TASK ) > 0 )
         DropMetaOI( vSubtask, vLOD );

      ActivateMetaOI( vSubtask, &vLOD, vLOD_List, zREFER_LOD_META, zSINGLE );
      SetNameForView( vLOD, "TZTMPLOD", vSubtask, zLEVEL_TASK );
      DropView( vLOD_List );
      if ( CheckExistenceOfEntity( vSrc, "ActMapLOD_Entity" ) >= 0 )
      {
         GetStringFromAttribute( szTag, zsizeof( szTag ), vSrc, "ActMapLOD_Entity", "Name" );
         nRC = SetCursorFirstEntityByString( vLOD, "LOD_Entity",
                                             "Name", szTag, 0 );
         if ( nRC >= 0 )
         {
            IncludeSubobjectFromSubobject( vTgt, "ActMapLOD_Entity",
                                           vLOD, "LOD_Entity", zPOS_AFTER );
         }
         else
         {
            GetVariableFromAttribute( szTag, 0, 'S', 33, vSrc,
                                      "ActMapLOD_Entity", "Name", "", 0 );
            strcpy_s( szMsg, zsizeof( szMsg ), "LOD_Entity doesn't exist: " );
            strcat_s( szMsg, zsizeof( szMsg ), szTag );
            MessageSend( vSubtask, "WD00214", "Dialog Clone", szMsg,
                         zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
         }
      }
   }
   else
   {
      GetViewByName( &vLOD, "TZTMPLOD", vSubtask, zLEVEL_TASK );
   }

   return( 0 );
}

zSHORT
fnCloneAction( zVIEW     vSrcLPLR,
               zVIEW     vSrc,
               zVIEW     vTgt,
               zVIEW     vSubtask )
{
   zLONG     lLth;
   zCHAR     szLanguageType[ 2 ];
   zCHAR     szSourceName[ 33 ];
   zCHAR     szTag[ 33 ];
   zSHORT    nRC;

   GetStringFromAttribute( szTag, zsizeof( szTag ), vSrc, "Action", "Tag" );
   nRC = SetCursorFirstEntityByString( vTgt, "Action", "Tag", szTag, 0 );
   if ( nRC >= zCURSOR_SET )
   {
      return( 0 );
   }

   if ( CompareAttributeToString( vSrc, "Action", "Tag", "" ) != 0 )
   {
      CreateMetaEntity( vSubtask, vTgt, "Action", zPOS_AFTER );
      SetMatchingAttributesByName( vTgt, "Action", vSrc, "Action", zSET_NULL );
   }

   nRC = SetCursorFirstEntity( vSrc, "ActMap", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      if ( fnCloneActMap( vSrcLPLR, vSrc, vTgt, vSubtask ) == -1 )
         return( -1 );

      nRC = SetCursorNextEntity( vSrc, "ActMap", 0 );
   }

   if ( CheckExistenceOfEntity( vSrc, "ActOper" ) == 0 )
   {
      GetStringFromAttribute( szTag, zsizeof( szTag ), vSrc, "ActOper", "Name" );
      nRC = SetCursorFirstEntityByString( vTgt, "Operation", "Name",
                                          szTag, "Dialog" );
      if ( nRC < zCURSOR_SET )
      {
         GetVariableFromAttribute( szLanguageType, 0, 'S', 2, vSrc,
                                   "SourceFile", "LanguageType", "", 0 );
         nRC = SetCursorFirstEntityByString( vTgt, "SourceFile",
                                             "LanguageType", szLanguageType,
                                             0 );
         if ( nRC < zCURSOR_SET )
         {
            GetVariableFromAttribute( szSourceName, 0, 'S', 33, vTgt,
                                      "Dialog", "Tag", "", 0 );
            nRC = SetCursorFirstEntityByString( vTgt, "SourceFile", "Name",
                                                szSourceName, 0 );
            if ( nRC >= zCURSOR_SET )
            {
               lLth = zstrlen( szSourceName );
               if ( lLth >= 8 )
               {
                  strcpy_s( szSourceName, zsizeof( szSourceName ), szSourceName );
               }

               strcat_s( szSourceName, zsizeof( szSourceName ), szLanguageType );
            }

            CreateMetaEntity( vSubtask, vTgt, "SourceFile", zPOS_AFTER );
            SetAttributeFromString( vTgt, "SourceFile", "Name",
                                    szSourceName );
            SetAttributeFromString( vTgt, "SourceFile",
                                    "LanguageType", szLanguageType );
            if ( szLanguageType[ 0 ] == 'V' )
            {
               SetAttributeFromString( vTgt, "SourceFile",
                                       "Extension", "VML" );
            }
            else
            {
               SetAttributeFromString( vTgt, "SourceFile",
                                       "Extension", "C" );
            }
         }

         GetStringFromAttribute( szTag, zsizeof( szTag ), vSrc, "ActOper", "Name" );
         nRC = SetCursorFirstEntityByString( vSrc, "Operation",
                                             "Name", szTag, "Dialog" );
         CreateMetaEntity( vSubtask, vTgt, "Operation", zPOS_AFTER );
         SetMatchingAttributesByName( vTgt, "Operation",
                                      vSrc, "Operation", zSET_NULL );
         nRC = SetCursorFirstEntity( vSrc, "Parameter", 0 );
         while ( nRC > zCURSOR_UNCHANGED )
         {
            CreateMetaEntity( vSubtask, vTgt, "Parameter", zPOS_AFTER );
            SetMatchingAttributesByName( vTgt, "Parameter",
                                         vSrc, "Parameter", zSET_NULL );
            nRC = SetCursorNextEntity( vSrc, "Parameter", 0 );
         }
      }

      nRC = IncludeSubobjectFromSubobject( vTgt, "ActOper",
                                           vTgt, "Operation", zPOS_AFTER );
   }

   return( 0 );
}

zSHORT
fnCtrlAttributeMapping( zVIEW  vSubtask,
                        zVIEW  vSrcLPLR,
                        zVIEW  vSrcC,
                        zVIEW  vTgtC,
                        zVIEW  vLOD )
{
   zVIEW     vDomain;
   zVIEW     vDomainList;
   zCHAR     szMsg[ 65 ];
   zCHAR     szTag[ 33 ];
   zLONG     lZKey;
   zSHORT    nRC;

   GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "CtrlMapER_Attribute", "Name" );
   nRC = SetCursorFirstEntityByString( vLOD, "ER_Attribute", "Name",
                                       szTag, "LOD_Entity" );
   if ( nRC >= 0 )
   {
      IncludeSubobjectFromSubobject( vTgtC, "CtrlMapLOD_Attribute",
                                     vLOD, "LOD_Attribute", zPOS_AFTER );
      if ( CheckExistenceOfEntity( vSrcC, "CtrlMapContext" ) >= 0 )
      {
         nRC = SetCursorFirstEntityByInteger( vSrcLPLR, "W_MetaType",
                                              "Type", 2003, 0 );
         GetIntegerFromAttribute( &lZKey, vSrcC, "CtrlMapER_Domain", "ZKey" );
         nRC = SetCursorFirstEntityByInteger( vSrcLPLR, "W_MetaDef",
                                              "CPLR_ZKey", lZKey, 0 );
         RetrieveViewForMetaList( vSubtask, &vDomainList, zREFER_DOMAIN_META );
         GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcLPLR, "W_MetaDef", "Name" );
         nRC = SetCursorFirstEntityByString( vDomainList, "W_MetaDef",
                                             "Name", szTag, 0 );
         if ( nRC >= 0 )
         {
            ActivateMetaOI( vSubtask, &vDomain, vDomainList,
                            zREFER_DOMAIN_META, zSINGLE );
            GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "CtrlMapContext", "Name" );
            nRC = SetCursorFirstEntityByString( vDomain, "Context", "Name",
                                                szTag, 0 );
            if ( nRC >= 0 )
            {
               IncludeSubobjectFromSubobject( vTgtC, "CtrlMapContext",
                                              vDomain, "Context", zPOS_AFTER );
            }
            else
            {
               GetVariableFromAttribute( szTag, 0, 'S', 33, vSrcC,
                                         "CtrlMapContext", "Name", "", 0 );
               strcpy_s( szMsg, zsizeof( szMsg ), "Context doesn't exist within Domain: " );
               strcat_s( szMsg, zsizeof( szMsg ), szTag );
               strcat_s( szMsg, zsizeof( szMsg ), ", " );
               GetVariableFromAttribute( szTag, 0, 'S', 33,
                                         vSrcLPLR, "W_MetaDef",
                                         "Name", "", 0 );
               strcat_s( szMsg, zsizeof( szMsg ), szTag );
               MessageSend( vSubtask, "WD00211", "Dialog Clone",
                            szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
            }

            DropMetaOI( vSubtask, vDomain );
         }
         else
         {
            GetVariableFromAttribute( szTag, 0, 'S', 33, vSrcLPLR,
                                      "W_MetaDef", "Name", "", 0 );
            strcpy_s( szMsg, zsizeof( szMsg ), "Domain doesn't exist: " );
            strcat_s( szMsg, zsizeof( szMsg ), szTag );
            MessageSend( vSubtask, "WD00212", "Dialog Clone",
                         szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
         }

         DropView( vDomainList );
      }
   }
   else
   {
      GetVariableFromAttribute( szTag, 0, 'S', 33, vSrcC,
                                "CtrlMapER_Attribute", "Name", "", 0 );
      strcpy_s( szMsg, zsizeof( szMsg ), "ER_Attribute doesn't exist: " );
      strcat_s( szMsg, zsizeof( szMsg ), szTag );
      MessageSend( vSubtask, "WD00213", "Dialog Clone", szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
   }

   return( 0 );
}

zSHORT
fnCloneCtrlMap( zVIEW     vTgt,
                zVIEW     vTgtC,
                zVIEW     vSrc,
                zVIEW     vSrcC,
                zVIEW     vSrcLPLR,
                zVIEW     vSubtask )
{
   zVIEW     vLOD;
   zVIEW     vLOD_List;
   zCHAR     szMsg[ 65 ];
   zCHAR     szTag[ 33 ];
   zSHORT    nRC;

   CreateMetaEntity( vSubtask, vTgtC, "CtrlMap", zPOS_AFTER );
   SetMatchingAttributesByName( vTgtC, "CtrlMap",
                                vSrcC, "CtrlMap", zSET_NULL );
   if ( CheckExistenceOfEntity( vSrcC, "CtrlMapView" ) >= 0 )
   {
      GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "CtrlMapView", "Name" );
      if ( fnPositionOnVOR( vTgt, vSrc, vSrcLPLR, szTag, vSubtask ) >= 0 )
      {
         IncludeSubobjectFromSubobject( vTgtC, "CtrlMapView",
                                        vTgt, "ViewObjRef", zPOS_AFTER );
      }
      else
      {
         return( -1 );
      }

      RetrieveViewForMetaList( vSubtask, &vLOD_List, zREFER_LOD_META );
      GetStringFromAttribute( szTag, zsizeof( szTag ), vTgt, "LOD", "Name" );
      nRC = SetCursorFirstEntityByString( vLOD_List, "W_MetaDef",
                                          "Name", szTag, 0 );
      if ( GetViewByName( &vLOD, "TZTMPLOD", vSubtask, zLEVEL_TASK ) > 0 )
         DropMetaOI( vSubtask, vLOD );

      ActivateMetaOI( vSubtask, &vLOD, vLOD_List, zREFER_LOD_META, zSINGLE );
      SetNameForView( vLOD, "TZTMPLOD", vSubtask, zLEVEL_TASK );
      DropView( vLOD_List );
   }

   if ( CheckExistenceOfEntity( vSrcC, "CtrlMapLOD_Entity" ) >= 0 )
   {
      GetViewByName( &vLOD, "TZTMPLOD", vSubtask, zLEVEL_TASK );
      GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "CtrlMapLOD_Entity", "Name" );
      nRC = SetCursorFirstEntityByString( vLOD, "LOD_Entity", "Name", szTag, 0 );
      if ( nRC >= 0 )
      {
         IncludeSubobjectFromSubobject( vTgtC, "CtrlMapLOD_Entity",
                                        vLOD, "LOD_Entity", zPOS_AFTER );
      }
      else
      {
         GetVariableFromAttribute( szTag, 0, 'S', 33, vSrcC,
                                   "CtrlMapLOD_Entity", "Name", "", 0 );
         strcpy_s( szMsg, zsizeof( szMsg ), "LOD_Entity doesn't exist: " );
         strcat_s( szMsg, zsizeof( szMsg ), szTag );
         MessageSend( vSubtask, "WD00209", "Control Clone",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
      }
   }

   if ( CheckExistenceOfEntity( vSrcC, "CtrlMapLOD_Attribute" ) >= 0 )
   {
      GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "CtrlMapRelatedEntity", "Name" );
      nRC = SetCursorFirstEntityByString( vLOD, "LOD_Entity", "Name", szTag, 0 );
      if ( nRC >= 0 )
      {
         fnCtrlAttributeMapping( vSubtask, vSrcLPLR, vSrcC, vTgtC, vLOD );
      }
      else
      {
         GetVariableFromAttribute( szTag, 0, 'S', 33, vSrcC,
                                   "CtrlMapRelatedEntity", "Name", "", 0 );
         strcpy_s( szMsg, zsizeof( szMsg ), "LOD_Entity doesn't exist: " );
         strcat_s( szMsg, zsizeof( szMsg ), szTag );
         MessageSend( vSubtask, "WD00210", "Control Clone",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
      }
   }

   return( 0 );
}

// Return TRUE if a duplicate tag is found.
zBOOL
fnEnsureUniqueCtrlTag( zVIEW vSubtask, zCPCHAR cpcCtrlTag )
{
   zPCHAR pchTag;
   zBOOL  bDuplicate = FALSE;
   zSHORT nRC = SetCursorFirstEntity( vSubtask, "Control", 0 );

   while ( bDuplicate == FALSE && nRC >= zCURSOR_SET )
   {
      GetAddrForAttribute( &pchTag, vSubtask, "Control", "Tag" );
      if ( zstrcmp( cpcCtrlTag, pchTag ) == 0 )
      {
         bDuplicate = TRUE;
      }
      else
      if ( SetViewToSubobject( vSubtask, "CtrlCtrl" ) >= 0 )
      {
         bDuplicate = fnEnsureUniqueCtrlTag( vSubtask, cpcCtrlTag );
         ResetViewFromSubobject( vSubtask );
      }

      nRC = SetCursorNextEntity( vSubtask, "Control", 0 );
   }

   return( bDuplicate );
}

zSHORT
fnCloneControl( zVIEW     vSrcLPLR,
                zVIEW     vSrc,
                zVIEW     vSrcC,
                zVIEW     vTgt,
                zVIEW     vTgtC,
                zVIEW     vPE,
                zBOOL     bReport,
                zVIEW     vSubtask )
{
   zVIEW     vDialog;
   zCHAR     szMsg[ 65 ];
   zCHAR     szTag[ 33 ];
   zLONG     lKey;
   zLONG     lUniqueId;
   zSHORT    nLth;
   zSHORT    nRC;

   CreateMetaEntity( vSubtask, vTgtC, "Control", zPOS_AFTER );
   SetMatchingAttributesByName( vTgtC, "Control",
                                vSrcC, "Control", zSET_NULL );
   if ( bReport == FALSE )
   {
      if ( CheckExistenceOfEntity( vSrcC, "Font" ) == 0 )
      {
         CreateMetaEntity( vSubtask, vTgtC, "Font", zPOS_AFTER );
         SetMatchingAttributesByName( vTgtC, "Font", vSrcC, "Font", zSET_NULL );
      }

      nRC = SetCursorFirstEntity( vSrcC, "WebControlProperty", 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         CreateMetaEntity( vSubtask, vTgtC, "WebControlProperty", zPOS_AFTER );
         SetMatchingAttributesByName( vTgtC, "WebControlProperty",
                                      vSrcC, "WebControlProperty", zSET_NULL );

         nRC = SetCursorNextEntity( vSrcC, "WebControlProperty", 0 );
      }
   }

   /*if ( CheckExistenceOfEntity( vSrcC, "ControlNLS_Text" ) == 0 )
   {
      CreateMetaEntity( vSubtask, vTgtC, "ControlNLS_Text", zPOS_AFTER );
      SetMatchingAttributesByName( vTgtC, "ControlNLS_Text",
                                   vSrcC, "ControlNLS_Text", zSET_NULL );
   }

   if ( CheckExistenceOfEntity( vSrcC, "ControlNLS_DIL_Text" ) == 0 )
   {
      CreateMetaEntity( vSubtask, vTgtC, "ControlNLS_DIL_Text", zPOS_AFTER );
      SetMatchingAttributesByName( vTgtC, "ControlNLS_DIL_Text",
                                   vSrcC, "ControlNLS_DIL_Text", zSET_NULL );
   }*/

   // Reset the current control's tag so we won't find it by Tag while we
   // ensure that the tag is unique.
   GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "Control", "Tag" );
   strcpy_s( szMsg, zsizeof( szMsg ), szTag ); // hold onto original tag
   SetAttributeFromString( vSrcC, "Control", "Tag",
                           "__&&&__^^^__Clone__@@@__%%%__" );

   CreateViewFromViewForTask( &vDialog, vTgtC, 0 );
   while ( ResetViewFromSubobject( vDialog ) == 0 )
   {
   }

   if ( fnEnsureUniqueCtrlTag( vDialog, szTag ) )
   {
      // Force unique CtrlTag here.
      nLth = (zSHORT) zstrlen( szTag );
      while ( nLth && szTag[ nLth - 1 ] >= '0' && szTag[ nLth - 1 ] <= '9' )
         nLth--;

      lUniqueId = zatol( szTag + nLth );
      if ( nLth == 0 )
      {
         strcpy_s( szTag, zsizeof( szTag ), "Tag" );
         nLth = 3;
      }

      while ( fnEnsureUniqueCtrlTag( vDialog, szTag ) )
      {
         lUniqueId++;
         zltoa( lUniqueId, szTag + nLth, zsizeof( szTag ) - nLth );
      }
   }

   SetAttributeFromString( vSrcC, "Control", "Tag", szMsg );
   SetAttributeFromString( vTgtC, "Control", "Tag", szTag );
   DropView( vDialog );

   GetIntegerFromAttribute( &lKey, vSrcC, "ControlDef", "Key" );
   nRC = SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key", lKey, 0 );
   if ( nRC >= 0 )
   {
      IncludeSubobjectFromSubobject( vTgtC, "ControlDef",
                                     vPE, "ControlDef", zPOS_AFTER );
   }
   else
   {
      if ( CompareAttributeToString( vSrcC, "ControlDef",
                                     "Tag", "Bitmap" ) == 0 )
      {
         nRC = SetCursorFirstEntityByString( vPE, "ControlDef", "Tag",
                                             "BitmapBtn", 0 );
         IncludeSubobjectFromSubobject( vTgtC, "ControlDef",
                                        vPE, "ControlDef", zPOS_AFTER );
      }
      else
      {
         GetVariableFromAttribute( szTag, 0, 'S', 33,
                                   vSrcC, "ControlDef", "Tag", "", 0 );
         strcpy_s( szMsg, zsizeof( szMsg ), "ControlDef doesn't exist: " );
         strcat_s( szMsg, zsizeof( szMsg ), szTag );
         MessageSend( vSubtask, "WD00204", "Dialog Clone",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
      }
   }

   if ( bReport == FALSE )
   {
#if 0
      nRC = SetCursorFirstEntity( vSrcC, "CtrlClrOverride", 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC,
            "CtrlColorDef", "Tag" );
         nRC = SetCursorFirstEntityByString( vPE, "CtrlColorDef", "Tag",
                                             szTag, 0 );
         if ( nRC >= 0 )
         {
            CreateMetaEntity( vSubtask, vTgtC, "CtrlClrOverride", zPOS_AFTER );
            IncludeSubobjectFromSubobject( vTgtC, "CtrlColorDef",
                                           vPE, "CtrlColorDef", zPOS_AFTER );
            GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "CtrlColor", "Tag" );
            nRC = SetCursorFirstEntityByString( vPE, "Color", "Tag", szTag, 0 );
            if ( nRC >= 0 )
            {
               IncludeSubobjectFromSubobject( vTgtC, "CtrlColor",
                                              vPE, "Color", zPOS_AFTER );
            }
            else
            {
               IncludeSubobjectFromSubobject( vTgtC, "CtrlColor",
                                              vPE, "CtrlColor", zPOS_AFTER );
            }
         }
         else
         {
            GetVariableFromAttribute( szTag, 0, 'S', 33, vSrcC,
                                      "CtrlColorDef", "Tag", "", 0 );
            strcpy_s( szMsg, zsizeof( szMsg ), "Color Definition doesn't exist: " );
            strcat_s( szMsg, zsizeof( szMsg ), szTag );
            MessageSend( vSubtask, "WD00205", "Dialog Clone",
                         szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
         }

         nRC = SetCursorNextEntity( vSrcC, "CtrlClrOverride", 0 );
      }

      nRC = SetCursorFirstEntity( vSrcC, "CtrlFontOverride", 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "CtrlFontDef", "Tag" );
         nRC = SetCursorFirstEntityByString( vPE, "CtrlFontDef", "Tag",
                                             szTag, 0 );
         if ( nRC >= 0 )
         {
            CreateMetaEntity( vSubtask, vTgtC, "CtrlFontOverride", zPOS_AFTER );
            IncludeSubobjectFromSubobject( vTgtC, "CtrlFontDef", vPE,
                                           "CtrlFontDef", zPOS_AFTER );
            GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "CtrlFont", "Tag" );
            nRC = SetCursorFirstEntityByString( vPE, "Font", "Tag", szTag, 0 );
            if ( nRC >= 0 )
            {
               IncludeSubobjectFromSubobject( vTgtC, "CtrlFont",
                                              vPE, "Font", zPOS_AFTER );
            }
            else
            {
               IncludeSubobjectFromSubobject( vTgtC, "CtrlFont",
                                              vPE, "CtrlFont", zPOS_AFTER );
            }
         }
         else
         {
            GetVariableFromAttribute( szTag, 0, 'S', 33,
               vSrcC, "CtrlFontDef", "Tag", "", 0 );
            strcpy_s( szMsg, zsizeof( szMsg ), "Font Definition doesn't exist: " );
            strcat_s( szMsg, zsizeof( szMsg ), szTag );
            MessageSend( vSubtask, "WD00206", "Dialog Clone",
                         szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
         }

         nRC = SetCursorNextEntity( vSrcC, "CtrlFontOverride", 0 );
      }
#endif
   }

   nRC = SetCursorFirstEntity( vSrcC, "CtrlCtrl", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      SetViewToSubobject( vSrcC, "CtrlCtrl" );
      SetViewToSubobject( vTgtC, "CtrlCtrl" );
      nRC = fnCloneControl( vSrcLPLR, vSrc, vSrcC, vTgt, vTgtC,
                            vPE, bReport, vSubtask );
      ResetViewFromSubobject( vSrcC );
      ResetViewFromSubobject( vTgtC );
      if ( nRC == -1 )
         return( -1 );

      nRC = SetCursorNextEntity( vSrcC, "CtrlCtrl", 0 );
   }

   nRC = SetCursorFirstEntity( vSrcC, "CtrlMap", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      if ( fnCloneCtrlMap( vTgt, vTgtC, vSrc, vSrcC, vSrcLPLR, vSubtask ) == -1 )
         return( -1 );

      nRC = SetCursorNextEntity( vSrcC, "CtrlMap", 0 );
   }

   if ( bReport == FALSE )
   {
      nRC = SetCursorFirstEntity( vSrcC, "Event", 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         if ( CompareAttributeToString( vSrcC, "EventAct", "Tag", "" ) != 0 )
         {
            CreateMetaEntity( vSubtask, vTgtC, "Event", zPOS_AFTER );
            SetMatchingAttributesByName( vTgtC, "Event",
                                         vSrcC, "Event", zSET_NULL );
            GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "EventAct", "Tag" );
            nRC = SetCursorFirstEntityByString( vTgt, "Action", "Tag", szTag, 0 );
            if ( nRC >= 0 )
            {
               IncludeSubobjectFromSubobject( vTgtC, "EventAct",
                                              vTgt, "Action", zPOS_AFTER );
            }
         }

         nRC = SetCursorNextEntity( vSrcC, "Event", 0 );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
zSHORT
zwfnTZPNTRAD_DisableMenuForError( zVIEW vSubtask, zBOOL bEnable )
{
   SetOptionState( vSubtask, "NewFile",     zOPTION_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "Open",        zOPTION_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "Dialog Spec", zOPTION_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "ScrollBars",  zOPTION_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "Grid",        zOPTION_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "TargetSpecification",
                                            zOPTION_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "CompilerSpecification",
                                            zOPTION_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "ToolbarControls",
                                            zOPTION_STATUS_ENABLED, bEnable );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_DisableAllMenuItems
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_DisableAllMenuItems( zVIEW vSubtask )
{
   zVIEW vTaskLPLR;

   // If there is an error situation disable all menu item without
   // "Switch Project".
   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) < 0 )
      zwfnTZPNTRAD_DisableMenuForError( vSubtask, FALSE );
   else
      zwfnTZPNTRAD_DisableMenuForError( vSubtask, TRUE );

   SetOptionState( vSubtask, "Save", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "GenerateXRA", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "Undo", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "Redo", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "Copy", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "Paste", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AddWindow", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AddMenu", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AddAction", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AddShortcut", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AddSourceFile", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AddOperation", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "UpdateMenu", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "UpdateAction", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "UpdateShortcut", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "UpdateSourceFile", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "UpdateOperation", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteWindow", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteControls", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteMenus", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteActions", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteShortcuts", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteSourceFiles", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteOperations", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteAllMenus", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteAllAction", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteAllShortcuts", zOPTION_STATUS_ENABLED, 0 );

   SetOptionState( vSubtask, "AlignLeft", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AlignRight", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AlignTop", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AlignBottom", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "EqualHeight", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "EqualWidth", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "EqualWidthHeight", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "EquiSpaceVertical", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "EquiSpaceHorizontal", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AbutVertical", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AbutHorizontal", zOPTION_STATUS_ENABLED, 0 );

   SetOptionState( vSubtask, "SetTabstops", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "RemoveTabbing", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AutodesignDialog", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "AutodesignWindow", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "CopyDialogWindow", zOPTION_STATUS_ENABLED, 0 );

   SetOptionState( vSubtask, "IncrementBothW", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "IncrementXW", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "IncrementYW", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DecrementBothW", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DecrementXW", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DecrementYW", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "IncrementBothD", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "IncrementXD", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "IncrementYD", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DecrementBothD", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DecrementXD", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DecrementYD", zOPTION_STATUS_ENABLED, 0 );

   SetOptionState( vSubtask, "MergeDialog Window", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "DeleteAct", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "Caption", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "ControlText", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "OptionText", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "ControlDILText", zOPTION_STATUS_ENABLED, 0 );
   SetOptionState( vSubtask, "SystemConversion", zOPTION_STATUS_ENABLED, 0 );

   return( 0 );
} // zwTZPNTRAD_DisableAllMenuItems

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_InitEditMenuItems
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_InitEditMenuItems( zVIEW vSubtask )
{
   zSHORT   nUpdate = 0;
   zSHORT   nDelete = 0;
   zSHORT   nEnable = 0;

   //Menus
   zwTZPNTRAD_EnableMenuItems( vSubtask, "LIST_MENU", "Menu", "MenuList",
                               &nUpdate, &nDelete );
   SetOptionState( vSubtask, "UpdateMenu", zOPTION_STATUS_ENABLED, nUpdate );
   SetOptionState( vSubtask, "DeleteMenus", zOPTION_STATUS_ENABLED, nDelete );
   nEnable = zwTZPNTRAD_EnableMenuDeleteAll( vSubtask, "Menu" );
   SetOptionState( vSubtask, "DeleteAllMenus", zOPTION_STATUS_ENABLED, nEnable );

   //Actions
   zwTZPNTRAD_EnableMenuItems( vSubtask, "LIST_ACT", "Action", "ActionList",
                               &nUpdate, &nDelete );
   SetOptionState( vSubtask, "UpdateAction", zOPTION_STATUS_ENABLED, nUpdate );
   SetOptionState( vSubtask, "DeleteActions", zOPTION_STATUS_ENABLED, nDelete );
   nEnable = zwTZPNTRAD_EnableMenuDeleteAll( vSubtask, "Action" );
   SetOptionState( vSubtask, "DeleteAllAction", zOPTION_STATUS_ENABLED, nEnable );

   //ShortCuts
   zwTZPNTRAD_EnableMenuItems( vSubtask, "LIST_HK", "Hotkey", "Hotkeys",
                               &nUpdate, &nDelete );
   SetOptionState( vSubtask, "UpdateShortcut", zOPTION_STATUS_ENABLED, nUpdate );
   SetOptionState( vSubtask, "DeleteShortcuts", zOPTION_STATUS_ENABLED, nDelete );
   nEnable = zwTZPNTRAD_EnableMenuDeleteAll( vSubtask, "Hotkey" );
   SetOptionState( vSubtask, "DeleteAllShortcuts", zOPTION_STATUS_ENABLED, nEnable );

   return( 0 );

} // zwTZPNTRAD_InitEditMenuItems

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_InitMenuItems
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_InitMenuItems( zVIEW vSubtask )
{
   zVIEW    vWindow;
   zVIEW    vTZWINDOWL;
   zVIEW    vTZWINDOW;
   zVIEW    vTZOPRUSO;
   zCHAR    szExecutableRemote[ zMAX_FILESPEC_LTH ];
   zSHORT   nIsCheckedOut = 0;

   zwTZPNTRAD_DisableAllMenuItems( vSubtask );

   // Generate XRA's
   SysReadZeidonIni( -1, "[Workstation]", "ExecutableRemote", szExecutableRemote, zsizeof( szExecutableRemote ) );
   if ( szExecutableRemote[ 0 ] )
      SetOptionState( vSubtask, "GenerateXRA", zOPTION_STATUS_ENABLED, 1 );

   if ( GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   nIsCheckedOut = ComponentIsCheckedOut( vSubtask, vTZWINDOWL, zSOURCE_DIALOG_META );

   if ( nIsCheckedOut == 1 )
   {
      SetOptionState( vSubtask, "Save", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "AddWindow", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "AddSourceFile", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "AddOperation", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "AutodesignDialog", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "AutodesignWindow", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "CopyDialogWindow", zOPTION_STATUS_ENABLED, 1 );

      SetOptionState( vSubtask, "IncrementBothW", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "IncrementXW", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "IncrementYW", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "DecrementBothW", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "DecrementXW", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "DecrementYW", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "IncrementBothD", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "IncrementXD", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "IncrementYD", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "DecrementBothD", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "DecrementXD", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "DecrementYD", zOPTION_STATUS_ENABLED, 1 );

      SetOptionState( vSubtask, "MergeDialog Window", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "DeleteAct", zOPTION_STATUS_ENABLED, 1 );
      SetOptionState( vSubtask, "SystemConversion", zOPTION_STATUS_ENABLED, 1 );

      if ( GetViewByName( &vTZWINDOW, "TZWINDOW", vSubtask, zLEVEL_TASK ) >= 0 )
      {
         SetOptionState( vSubtask, "AddMenu", zOPTION_STATUS_ENABLED, 1 );
         SetOptionState( vSubtask, "AddAction", zOPTION_STATUS_ENABLED, 1 );
         SetOptionState( vSubtask, "AddShortcut", zOPTION_STATUS_ENABLED, 1 );
         SetOptionState( vSubtask, "DeleteWindow", zOPTION_STATUS_ENABLED, 1 );
         SetOptionState( vSubtask, "RemoveTabbing", zOPTION_STATUS_ENABLED, 1 );
         SetOptionState( vSubtask, "Caption", zOPTION_STATUS_ENABLED, 1 );
         SetOptionState( vSubtask, "ControlText", zOPTION_STATUS_ENABLED, 1 );
         SetOptionState( vSubtask, "OptionText", zOPTION_STATUS_ENABLED, 1 );
         SetOptionState( vSubtask, "ControlDILText", zOPTION_STATUS_ENABLED, 1 );
      }
   }

   //Source File
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "SRCLIST" ) < 0 )
      SetOptionState( vSubtask, "SourceFiles", zCONTROL_STATUS_CHECKED, 0 );
   else
   {
      SetOptionState( vSubtask, "SourceFiles", zCONTROL_STATUS_CHECKED, 1 );
      if ( GetViewByName( &vTZOPRUSO, "TZOPRUSO", vSubtask, zLEVEL_TASK ) > 0 &&
           GetSelectStateOfEntity( vTZOPRUSO, "SourceFile" ) == 1 )
      {
         SetOptionState( vSubtask, "UpdateSourceFile", zOPTION_STATUS_ENABLED, 1 );
         if ( nIsCheckedOut == 1 )
            SetOptionState( vSubtask, "DeleteSourceFiles", zOPTION_STATUS_ENABLED, 1 );
      }
   }

   //Operations
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "OPERLIST" ) < 0 )
      SetOptionState( vSubtask, "Opers", zCONTROL_STATUS_CHECKED, 0 );
   else
   {
      SetOptionState( vSubtask, "Opers", zCONTROL_STATUS_CHECKED, 1 );
      if ( GetViewByName( &vTZOPRUSO, "TZOPRUSO", vSubtask, zLEVEL_TASK ) > 0 &&
           GetSelectStateOfEntity( vTZOPRUSO, "OperationList" ) == 1 )
      {
         SetOptionState( vSubtask, "UpdateOperation", zOPTION_STATUS_ENABLED, 1 );
         if ( nIsCheckedOut == 1 )
            SetOptionState( vSubtask, "DeleteOperations", zOPTION_STATUS_ENABLED, 1 );
      }
   }

   zwTZPNTRAD_InitEditMenuItems( vSubtask );

   return( 0 );
} // zwTZPNTRAD_InitMenuItems

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_EnableMenuDeleteAll
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_EnableMenuDeleteAll( zVIEW   vSubtask,
                                zPCHAR  szEntityName )
{
   zVIEW  vTZWINDOWL;
   zSHORT nEnable = 0;

   if ( GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) >= 0 &&
        CheckExistenceOfEntity( vTZWINDOWL, szEntityName ) >= zCURSOR_SET  &&
        ComponentIsCheckedOut( vSubtask, vTZWINDOWL, zSOURCE_DIALOG_META ) == 1 )
   {
      nEnable = 1;
   }

   return( nEnable );
} // zwTZPNTRAD_EnableMenuDeleteAll

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_EnableMenuItems
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_EnableMenuItems( zVIEW    vSubtask,
                            zPCHAR   szListname,
                            zPCHAR   szEntityName,
                            zPCHAR   szMenuItem,
                            zPSHORT  nEnableUpdate,
                            zPSHORT  nEnableDelete )
{
   zVIEW  vWindow;
   zVIEW  vTZWINDOWL;

   *nEnableUpdate = 0;
   *nEnableDelete = 0;

   if ( GetSubtaskForWindowName( vSubtask, &vWindow, szListname ) < 0 )
      SetOptionState( vSubtask, szMenuItem, zCONTROL_STATUS_CHECKED, 0 );
   else
   {
      SetOptionState( vSubtask, szMenuItem, zCONTROL_STATUS_CHECKED, 1 );
      if ( GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) >= 0 &&
           GetSelectStateOfEntity( vTZWINDOWL, szEntityName ) == 1 )
      {
         *nEnableUpdate = 1;
         if ( ComponentIsCheckedOut( vSubtask, vTZWINDOWL, zSOURCE_DIALOG_META ) == 1 )
            *nEnableDelete = 1;
      }
   }

   return( 0 );
} // zwTZPNTRAD_EnableMenuItems

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_DeleteAllMenus
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_DeleteAllMenus( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vWindow;
   zSHORT nRC;
   zCHAR  szTag[ 33 ];
   zCHAR  szMsg[ 200 ];

   GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szTag, zsizeof( szTag ), vDialog, "Window", "Tag" );

   strcpy_s( szMsg, zsizeof( szMsg ), "OK to delete all Menus from Window '" );
   strcat_s( szMsg, zsizeof( szMsg ), szTag );
   strcat_s( szMsg, zsizeof( szMsg ), "'?" );
   nRC = MessagePrompt( vSubtask, "PE002",
                        "Dialog Maintenance",
                        szMsg,
                        zBEEP, zBUTTONS_YESNO,
                        zRESPONSE_NO,  0 );

   if ( nRC == zRESPONSE_YES )
   {
      for ( nRC = SetCursorFirstEntity( vDialog, "Menu", "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDialog, "Menu", "" ) )
      {
         nRC = DeleteEntity( vDialog, "Menu", zREPOS_NONE );
      }
      if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_MENU" ) >= 0 )
        RefreshWindow( vWindow );
   }
   else
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
   }

   return( 0 );
} // zwTZPNTRAD_DeleteAllMenus

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_DeleteAllHotkeys
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_DeleteAllHotkeys( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zVIEW  vWindow;
   zSHORT nRC;
   zCHAR  szTag[ 33 ];
   zCHAR  szMsg[ 200 ];

   GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szTag, zsizeof( szTag ), vDialog, "Window", "Tag" );

   strcpy( szMsg, "OK to delete all Shortcut Keys from Window '" );
   strcat( szMsg, szTag);
   strcat(szMsg, "'?" );

   if ( MessagePrompt( vSubtask, "PE002",
                       "Dialog Maintenance",
                       szMsg,
                       zBEEP, zBUTTONS_YESNO,
                       zRESPONSE_NO,  0 ) == zRESPONSE_YES )
   {
      for ( nRC = SetCursorFirstEntity( vDialog, "Hotkey", "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDialog, "Hotkey", "" ) )
      {
         DeleteEntity( vDialog, "Hotkey", zREPOS_NONE );
      }
      if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_HK" ) >= 0 )
         RefreshWindow( vWindow );
   }
   return( 0 );
} // zwTZPNTRAD_DeleteAllHotkeys

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_DeleteAllActions
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_DeleteAllActions( zVIEW vSubtask )
{
   zVIEW  vWindow;

   zwTZPNCTAD_DeleteAllActions( vSubtask );

   // Refresh Action List
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_ACT" ) >= 0 )
      RefreshWindow( vWindow );

   return( 0 );
} //zwTZPNTRAD_DeleteAllActions

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_Check_CheckoutStatus
//
//    set check out state in window title
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_Check_CheckoutStatus( zVIEW vSubtask )
{
   zVIEW   vTZDIALOGS;
   zSHORT  nEnable = 0;
   zBOOL   bEnable = FALSE;

   if ( GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK ) >= 0 &&
        CheckExistenceOfEntity( vTZDIALOGS, "W_MetaDef" ) >= zCURSOR_SET )
   {
         nEnable = CheckOutStateForCurrentWindow( vSubtask, vTZDIALOGS );
         if ( nEnable )
            bEnable = TRUE;
   }

   SetCtrlState( vSubtask, "Delete", zOPTION_STATUS_ENABLED, nEnable );
   EnableAction( vSubtask, "DeleteDialog", bEnable );

   return( 0 );
} // zwTZPNTRAD_Check_CheckoutStatus

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_CheckNameForCheckOut
//
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_CheckNameForCheckOut( zVIEW vSubtask )
{
   zSHORT  nEnable = 1;
   zVIEW   vTZDIALOGS;
   zVIEW   vTZDIALOGS_Copy;
   zCHAR   szNewName[ 33 ];
   zCHAR   szOutName[ 33 ];

   GetCtrlText( vSubtask, "edDialogName", szNewName, 33 );
   UfCompressName( szNewName, szOutName, 8, "", "", "", "", 0 );

   if ( GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   CreateViewFromViewForTask( &vTZDIALOGS_Copy, vTZDIALOGS, 0 );

   if ( SetCursorFirstEntityByString( vTZDIALOGS_Copy, "W_MetaDef", "Name",
                                      szOutName, 0 ) > zCURSOR_UNCHANGED )
   {
      // set check out state in Title
      nEnable = CheckOutStateForCurrentWindow( vSubtask, vTZDIALOGS_Copy );
   }
   else
   {
      SetWindowCaptionTitle( vSubtask, "Save Dialog as", "" );
   }

   SetCtrlState( vSubtask, "OK", zCONTROL_STATUS_ENABLED, nEnable );

   DropView( vTZDIALOGS_Copy );

   return( 0 );
} // zwTZPNTRAD_CheckNameForCheckOut

zSHORT
zwfnTZPNTRAD_CheckActionAfterSaveAs( zVIEW  vSubtask )
{
   zVIEW   vSaveAs;
   zVIEW   vDialogs;
   zVIEW   vParentWindow;
   zLONG   lActionAfterSaveAs;

   GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialogs, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // Set window Title with check out state
   GetParentWindow( &vParentWindow, vSubtask );
   SetTitleWithCheckOutState( vParentWindow, "LDialog Maintenance",
                               "TZWINDOWL", vDialogs, "Dialog", zSOURCE_DIALOG_META );

   // if Dialog not checked out and user change this Dialog, then zeidon
   // call the window "Save Dialog as"
   // We save the action after Save as in the View TZSAVEAS (for example:
   // Create new Dialog or Open an other Dialog or Switch Project or Exit
   // Dialog0 Tool)

   GetIntegerFromAttribute( &lActionAfterSaveAs, vSaveAs,
                            "ActionAfterSaveAS", "Typ" );
   SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                            zNoActionAfterSaveAs );

   switch ( lActionAfterSaveAs )
   {
      case zNewComponentAfterSaveAs:   // Create new Dialog
         SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow,
                                  "TZPNTRAD", "DLG_NEW" );
         break;

      case zOpenComponentAfterSaveAs:   // Open Dialog
         SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow,
                                  "TZPNTRAD", "DLG_OPEN" );
         break;

      case zSwitchLPLRAfterSaveAs:   // Switch Project
         SwitchLPLR( vSubtask );
         SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow,
                                  "TZCMSLPD", "SwitchLPLR" );
         break;

      case zExitToolAfterSaveAs:   // Exit Dialog Tool
         ExitDialog( vSubtask );
         SetWindowActionBehavior( vSubtask, zWAB_ExitDialogTask, "", "" );
         break;
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_NewDialog
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_NewDialog( zVIEW vSubtask )
{
   zVIEW  vSaveAs;
   zSHORT nRC;

   // Ask and do save
   nRC = AskForSave( vSubtask );
   if ( nRC )
   {
      if ( GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK ) > 0 )
      {
         if ( nRC == 99 )
         {
            // If Dialog not checked out and user change this Dialog, then
            // zeidon call the window "Save Dialog as".
            // We save the action after Save as in the View TZSAVEAS (e.g.
            // Create new Dialog or Open an other Dialog or Switch Project or
            // Exit Dialog Tool).
            SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                                     zNewComponentAfterSaveAs );
         }
         else
            SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                                     zNoActionAfterSaveAs );
      }
   }

   return( 0 );
} // zwTZPNTRAD_NewDialog

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_OpenDialog
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_OpenDialog( zVIEW vSubtask )
{
   zVIEW  vSaveAs;
   zSHORT nRC;

   // Ask and do save
   nRC = AskForSave( vSubtask );
   if ( nRC )
   {
      if ( GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK ) > 0 )
      {
         if ( nRC == 99 )
         {
            // if Dialog not checked out and user change this Dialog, then zeidon
            // call the window "Save Dialog as"
            // We save the action after Save as in the View TZSAVEAS (for example:
            // Create new Dialog or Open an other Dialog or Switch Project or
            // Exit Dialog Tool)
            SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                                     zOpenComponentAfterSaveAs );
         }
         else
            SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ",
                                     zNoActionAfterSaveAs );
      }
   }

   return( 0 );

} // zwTZPNTRAD_OpenDialog

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_UpdateZeidonWindows
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_UpdateZeidonWindows( zVIEW vSubtask )
{
   fnPainterCall( zMSG_UPDATEALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );

   return( 0 );
} // zwTZPNTRAD_UpdateZeidonWindows

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_LoadOperationList
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_LoadOperationList( zVIEW vSubtask )
{
   zVIEW  vWindow;

   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "OPERLIST" ) >= 0 )
   {
      SetWindowState( vWindow, zWINDOW_STATUS_DESTROY, 1 );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
   }

   return( 0 );
} // zwTZPNTRAD_LoadOperationList

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_LoadSourceFileList
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_LoadSourceFileList( zVIEW vSubtask )
{
   zVIEW  vWindow;

   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "SRCLIST" ) >= 0 )
   {
      SetWindowState( vWindow, zWINDOW_STATUS_DESTROY, 1 );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
   }

   return( 0 );
} // zwTZPNTRAD_LoadSourceFileList

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_LoadShortcutList
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_LoadShortcutList( zVIEW vSubtask )
{
   zVIEW  vWindow;

   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_HK" ) >= 0 )
   {
      SetWindowState( vWindow, zWINDOW_STATUS_DESTROY, 1 );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
   }

   return( 0 );
} // zwTZPNTRAD_LoadShortcutList

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_LoadMenuList
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_LoadMenuList( zVIEW vSubtask )
{
   zVIEW  vWindow;

   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_MENU" ) >= 0 )
   {
      SetWindowState( vWindow, zWINDOW_STATUS_DESTROY, 1 );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
   }

   return( 0 );
} // zwTZPNTRAD_LoadMenuList

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_LoadWindowPopups
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
zwTZPNTRAD_LoadWindowPopups( zVIEW vSubtask,
                             zPCHAR szEntityName,
                             zPCHAR szActionNameForNew,
                             zPCHAR szActionNameForDelete,
                             zPCHAR szActionNameForDeleteAll,
                             zPCHAR szPopupName )
{
   POINT  pt;
// CPoint pt( GetMessagePos( ) );
   pt.x = pt.y = -1;
   zVIEW  vDialog;
   zBOOL  bNew          = FALSE;
   zBOOL  bDelete       = FALSE;
   zSHORT nIsCheckedOut = 0;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      nIsCheckedOut = ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META );

      if ( CheckExistenceOfEntity( vDialog, szEntityName ) >= zCURSOR_SET )
      {
         if ( nIsCheckedOut == 1 )
            bDelete = TRUE;
      }

      if ( nIsCheckedOut == 1 )
         bNew = TRUE;

      EnableAction( vSubtask, szActionNameForNew, bNew );
      EnableAction( vSubtask, szActionNameForDelete, bDelete );
      EnableAction( vSubtask, szActionNameForDeleteAll, bDelete );

      CreateTrackingPopupMenu( vSubtask, szPopupName, pt.x, pt.y, FALSE, FALSE );
   }

   return( 0 );
} // zwTZPNTRAD_LoadWindowPopups

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: UPD_MENU_LoadPopup
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
UPD_MENU_LoadPopup( zVIEW vSubtask )
{
   zwTZPNTRAD_LoadWindowPopups( vSubtask,
                                "Menu",
                                "NewMenu",
                                "DeleteMenu",
                                "DeleteAllMenus",
                                "MenuPopup" );

   return( 0 );
} // UPD_MENU_LoadPopup

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: SEL_OPT_Postbuild
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
SEL_OPT_Postbuild( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );

   if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
   {
      SetCtrlState( vSubtask, "ViewName", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "EntityList", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "AttributeList", zCONTROL_STATUS_ENABLED, FALSE );
   }

   return( 0 );
} // SEL_OPT_Postbuild

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_LoadEventPopups
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
zwTZPNTRAD_LoadEventPopups( zVIEW  vSubtask,
                            zPCHAR szActionNameForUpdate,
                            zPCHAR szActionNameForNew,
                            zPCHAR szActionNameForSelect,
                            zPCHAR szActionNameForRemove,
                            zPCHAR szActionNameForEdit,
                            zPCHAR szPopupName )
{
   zVIEW  vEvents;
   zVIEW  vDialog;
   zVIEW  vDialogCopy;
   zVIEW  vTZWINDOWL;
   zBOOL  bNew          = FALSE;
   zBOOL  bEdit         = FALSE;
   zBOOL  bUpdate       = FALSE;
   zBOOL  bDelete       = FALSE;
   zSHORT nIsCheckedOut = 0;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vEvents, "TZPNEVWO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      nIsCheckedOut = ComponentIsCheckedOut( vSubtask, vTZWINDOWL, zSOURCE_DIALOG_META );

      if ( CheckExistenceOfEntity( vEvents, "Event" ) >= zCURSOR_SET &&
           CheckExistenceOfEntity( vEvents, "EventAct" ) >= zCURSOR_SET )
      {
         if ( CompareAttributeToString( vEvents, "EventAct", "Tag", "" ) != 0 )
         {
            bUpdate = TRUE;
            if ( nIsCheckedOut == 1 )
               bDelete = TRUE;

            // Check Action Operation
            if ( zstrcmp( szPopupName, "CtrlListPopup" ) == 0 )
               CreateViewFromViewForTask( &vDialogCopy, vTZWINDOWL, 0 );
            else
               CreateViewFromViewForTask( &vDialogCopy, vDialog, 0 );

            SetCursorFirstEntityByAttr( vDialogCopy, "Action", "ZKey",
                                        vEvents, "EventAct", "ZKey", "" );
            if ( CheckExistenceOfEntity( vDialogCopy, "ActOper" ) >= zCURSOR_SET )
               bEdit = TRUE;
            DropView( vDialogCopy );
         }
      }

      if ( CheckExistenceOfEntity( vEvents, "Event" ) >= zCURSOR_SET &&
           nIsCheckedOut == 1 )
      {
         bNew = TRUE;
      }

      EnableAction( vSubtask, szActionNameForUpdate, bUpdate );
      EnableAction( vSubtask, szActionNameForNew, bNew );
      EnableAction( vSubtask, szActionNameForSelect, bNew );
      EnableAction( vSubtask, szActionNameForRemove, bDelete );
      EnableAction( vSubtask, szActionNameForEdit, bEdit );

      CreateTrackingPopupMenu( vSubtask, szPopupName, -1, 0, FALSE, FALSE );
   }

   return( 0 );
} // zwTZPNTRAD_LoadEventPopups

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: LIST_HK_LoadPopup
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
LIST_HK_LoadPopup( zVIEW vSubtask )
{
   zwTZPNTRAD_LoadWindowPopups( vSubtask,
                                "Hotkey",
                                "NewHotkey",
                                "DeleteHotkey",
                                "DeleteAllShortcuts",
                                "ShortcutPopup" );

   return( 0 );
} // LIST_HK_LoadPopup

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListLoadMappingPopup
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
CtrlListLoadMappingPopup( zVIEW vSubtask )
{
   POINT  pt;
// CPoint pt( GetMessagePos( ) );
   pt.x = pt.y = -1;
   zVIEW  vDialog;
   zVIEW  vMapping;
   zBOOL  bNew          = FALSE;
   zBOOL  bDelete       = FALSE;
   zSHORT nIsCheckedOut = 0;

   GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vMapping, "TZCTLMAP2", vSubtask, zLEVEL_TASK ) > 0 )
   {
      nIsCheckedOut = ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META );

      if ( CheckExistenceOfEntity( vMapping, "CtrlMap" ) >= zCURSOR_SET )
      {
         if ( nIsCheckedOut == 1 )
            bDelete = TRUE;
      }

      if ( nIsCheckedOut == 1 )
         bNew = TRUE;

      EnableAction( vSubtask, "CtrlListAddMapEntity", bNew );
      EnableAction( vSubtask, "CtrlListDeleteMapEntity", bDelete );

      CreateTrackingPopupMenu( vSubtask, "MappingPopup", pt.x, pt.y, FALSE, FALSE );
   }

   return( 0 );
} // CtrlListLoadMappingPopup

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListLoadEventPopup
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
CtrlListLoadEventPopup( zVIEW vSubtask )
{
   zwTZPNTRAD_LoadEventPopups( vSubtask,
                               "CtrlListUpdateAction",
                               "ActionAdd",
                               "CtrlListSelectAction",
                               "CtrlListRemoveAction",
                               "WND_UPD_OperationEdit",
                               "CtrlListPopup" );

   return( 0 );
} // CtrlListLoadEventPopup

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: CtrlListSetCtrlFlags
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
CtrlListSetCtrlFlags( zVIEW vSubtask )
{
   zVIEW vControl;
   zLONG lSubtype;

   if ( GetViewByName( &vControl, "NoRefresh", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      GetIntegerFromAttribute( &lSubtype, vControl, "Control", "Subtype" );
      CtrlListSetCheckedState( vSubtask, vControl, lSubtype );
   }

   return( 0 );
} // CtrlListSetCtrlFlags

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: UPD_MENU_LoadMenuPopup
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
UPD_MENU_LoadMenuPopup( zVIEW vSubtask )
{
   zVIEW  vTZPNOPWO;
   zVIEW  vDialog;
   zBOOL  bNew         = FALSE;
   zBOOL  bDelete       = FALSE;
   zSHORT nIsCheckedOut = 0;

   GetViewByName( &vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vTZPNOPWO, "TZPNOPWO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      nIsCheckedOut = ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META );

      if ( CheckExistenceOfEntity( vTZPNOPWO, "Option" ) >= zCURSOR_SET )
      {
         if ( nIsCheckedOut == 1 )
            bDelete = TRUE;
      }

      if ( nIsCheckedOut == 1 )
      {
         bNew = TRUE;
      }

      EnableAction( vSubtask, "OptionAdd", bNew );
      EnableAction( vSubtask, "OptionDelete", bDelete );

      CreateTrackingPopupMenu( vSubtask, "MenuPopup", -1, 0, FALSE, FALSE );
   }

   return( 0 );
} // UPD_MENU_LoadMenuPopup

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_AlignLeft
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_AlignLeft( zVIEW vSubtask )
{
   fnPainterCall( zMSG_ALIGN_LEFT, vSubtask, 0, 0, 0 );

   return( 0 );
} // zwTZPNTRAD_AlignLeft

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_AlignRight
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_AlignRight( zVIEW vSubtask )
{
   fnPainterCall( zMSG_ALIGN_RIGHT, vSubtask, 0, 0, 0 );

   return( 0 );
} // zwTZPNTRAD_AlignRight

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_AlignTop
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_AlignTop( zVIEW vSubtask )
{
   fnPainterCall( zMSG_ALIGN_TOP, vSubtask, 0, 0, 0 );

   return( 0 );
} // zwTZPNTRAD_AlignTop

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_AlignBottom
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_AlignBottom( zVIEW vSubtask )
{
   fnPainterCall( zMSG_ALIGN_BOTTOM, vSubtask, 0, 0, 0 );

   return( 0 );
} // zwTZPNTRAD_AlignBottom

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_EqualHeight
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_EqualHeight( zVIEW vSubtask )
{
   fnPainterCall( zMSG_SIZE_HEIGHT, vSubtask, 0, 0, 0 );

   return( 0 );
} // zwTZPNTRAD_EqualHeight

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_EqualWidth
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_EqualWidth( zVIEW vSubtask )
{
   fnPainterCall( zMSG_SIZE_WIDTH, vSubtask, 0, 0, 0 );
   return( 0 );
} // zwTZPNTRAD_EqualWidth

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_EqualWidthHeight
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_EqualWidthHeight( zVIEW vSubtask )
{
   fnPainterCall( zMSG_SIZE_WIDTH_HEIGHT, vSubtask, 0, 0, 0 );
   return( 0 );
} // zwTZPNTRAD_EqualWidthHeight

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_EquiSpaceVertical
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_EquiSpaceVertical( zVIEW vSubtask )
{
   fnPainterCall( zMSG_EQUAL_SPACE_VERTICAL, vSubtask, 0, 0, 0 );
   return( 0 );
} // zwTZPNTRAD_EquiSpaceVertical

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_EquiSpaceHorizontal
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_EquiSpaceHorizontal( zVIEW vSubtask )
{
   fnPainterCall( zMSG_EQUAL_SPACE_HORIZONTAL, vSubtask, 0, 0, 0 );
   return( 0 );
} // zwTZPNTRAD_EquiSpaceHorizontal

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_AbutVertical
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_AbutVertical( zVIEW vSubtask )
{
   fnPainterCall( zMSG_ABUT_VERTICAL, vSubtask, 0, 0, 0 );
   return( 0 );
} // zwTZPNTRAD_AbutVertical

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_AbutHorizontal
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_AbutHorizontal( zVIEW vSubtask )
{
   fnPainterCall( zMSG_ABUT_HORIZONTAL, vSubtask, 0, 0, 0 );
   return( 0 );
} // zwTZPNTRAD_AbutHorizontal

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_DeleteControls
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_DeleteControls( zVIEW vSubtask )
{
   fnPainterCall( zMSG_DELETE_SELECTED, vSubtask, 0, 0, 0 );
   return( 0 );
} // zwTZPNTRAD_DeleteControls

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_RefreshAllSubwindows
//
//    refresh all modeless subwindows
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_RefreshAllSubwindows( zVIEW vSubtask )
{
   zVIEW   vWindow;
   zVIEW   vView;

   // Refresh Operation List
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "OPERLIST" ) >= 0 )
      wTZOPRUSD_SetUpTZOPRUSO_View( vSubtask );

   // Refresh Source File List
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "SRCLIST" ) >= 0 )
   {
      GetViewByName( &vView, "TZWINDOWL", vSubtask, zLEVEL_TASK );
      SetNameForView( vView, "TZOPRUSO", vSubtask, zLEVEL_TASK );
   }

   RefreshAllSubwindows( vSubtask );

   return( 0 );
} //zwTZPNTRAD_RefreshAllSubwindows

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_RefreshAllWindowLists
//
//    refresh Action, Menu, Control and Shortcut List
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_RefreshAllWindowLists( zVIEW vSubtask )
{
   zVIEW   vWindow;

   // Refresh Action List.
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_ACT" ) >= 0 )
      RefreshWindow( vWindow );

   // Refresh Shortcut List.
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_HK" ) >= 0 )
      RefreshWindow( vWindow );

   // Refresh Menu List.
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_MENU" ) >= 0 )
      RefreshWindow( vWindow );

   return( 0 );
} // zwTZPNTRAD_RefreshAllWindowLists

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_ACT_AddAction
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_ACT_AddAction( zVIEW vSubtask )
{
   LIST_ACT_AddAction( vSubtask );

   return( 0 );
} //zwTZPNTRAD_ACT_AddAction

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_AddOperation
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_AddOperation( zVIEW vSubtask )
{
   wTZOPRUSD_CheckExistsSourceFile( vSubtask );

   return( 0 );
} //zwTZPNTRAD_AddOperation

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_AddSourceFile
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_AddSourceFile( zVIEW vSubtask )
{
   wTZOPRUSD_AddSourceFile( vSubtask );

   return( 0 );
} //zwTZPNTRAD_AddSourceFile

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_ACT_UpdateAction
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_ACT_UpdateAction( zVIEW vSubtask )
{
   LIST_ACT_UpdateAction( vSubtask );

   return( 0 );
} //zwTZPNTRAD_ACT_UpdateAction

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_UpdateOperation
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_UpdateOperation( zVIEW vSubtask )
{
   wTZOPRUSD_GoToUpdateOperation( vSubtask );

   return( 0 );
} //zwTZPNTRAD_UpdateOperation

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_UpdateSourceFile
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_UpdateSourceFile( zVIEW vSubtask )
{
   zVIEW  vSOURCE;

   GetViewByName( &vSOURCE, "TZOPRUSO", vSubtask, zLEVEL_TASK );

   CreateTemporalSubobjectVersion( vSOURCE, "SourceFile" );

   return( 0 );
} //zwTZPNTRAD_UpdateSourceFile

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_DeleteAction
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_DeleteAction( zVIEW vSubtask )
{
   zVIEW  vWindow;

   LIST_ACT_DeleteAction( vSubtask );

   // Refresh Action List
   if ( GetSubtaskForWindowName( vSubtask, &vWindow, "LIST_ACT" ) >= 0 )
      RefreshWindow( vWindow );

   return( 0 );
} //zwTZPNTRAD_DeleteAction

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_DeleteOperation
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_DeleteOperation( zVIEW vSubtask )
{
   wTZOPRUSD_DeleteSelectedOperat( vSubtask );

   return( 0 );
} //zwTZPNTRAD_DeleteOperation

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_DeleteSourceFile
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_DeleteSourceFile( zVIEW vSubtask )
{
   wTZOPRUSD_DeleteSourceFile( vSubtask );

   return( 0 );
} //zwTZPNTRAD_DeleteSourceFile

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_SaveAsPostBuild
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_SaveAsPostBuild( zVIEW vSubtask )
{
   zVIEW    vTZWINDOWL;
   zVIEW    vSourceFile;
   zVIEW    vTZDIALOGS;
   zVIEW    vSaveAs;
   zSHORT   nRC;

   RetrieveMetaList( vSubtask );

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vTZDIALOGS, "W_MetaDef" ) >= zCURSOR_SET )
      SetSelectStateOfEntity( vTZDIALOGS, "W_MetaDef", 0 );

   SetAttributeFromString( vSaveAs, "ActionAfterSaveAS", "SaveAsName8", "" );
   SetAttributeFromString( vSaveAs, "ActionAfterSaveAS", "DLL_Name", "" );

   //set current Description
   SetCtrlState( vSubtask, "cbKeepCurrentDesc", zCONTROL_STATUS_CHECKED, 1 );
   SetAttributeFromAttribute( vSaveAs, "ActionAfterSaveAS", "Desc",
                              vTZWINDOWL, "Dialog", "Desc" );

   // delete old Source Files
   for ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vSaveAs, "SourceFile", "" ) )
   {
      nRC = DeleteEntity( vSaveAs, "SourceFile", zREPOS_NONE );
   }

   // create new source Files
   CreateViewFromViewForTask( &vSourceFile, vTZWINDOWL, 0 );
   for ( nRC = SetCursorFirstEntity( vSourceFile, "SourceFile", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vSourceFile, "SourceFile", "" ) )
   {
      CreateEntity( vSaveAs, "SourceFile", zPOS_AFTER );
      SetAttributeFromAttribute(   vSaveAs, "SourceFile", "SourceName",
                                 vSourceFile, "SourceFile", "Name" );
      SetAttributeFromAttribute(   vSaveAs, "SourceFile", "LanguageType",
                                 vSourceFile, "SourceFile", "LanguageType" );
   }
   DropView( vSourceFile );

   if ( CheckExistenceOfEntity( vSaveAs, "SourceFile" ) >= zCURSOR_SET )
      OrderEntityForView( vSaveAs, "SourceFile", "LanguageType D SourceName A" );

   return( 0 );
} // zwTZPNTRAD_SaveAsPostBuild

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_SaveAsSetDefaults
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_SaveAsSetDefaults( zVIEW vSubtask )
{
   zVIEW  vSaveAs;
   zVIEW  vTZDIALOGS;
   zVIEW  vTZDialogCopy;
   zCHAR  szNewName[ 33 ];
   zCHAR  szOutName[ 33 ];
   zSHORT nRC;
   zSHORT nIndex = -1;

   GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK );

   CreateViewFromViewForTask( &vTZDialogCopy, vTZDIALOGS, 0 );

   // if Dialog Name not required, set default value
   GetStringFromAttribute( szNewName, zsizeof( szNewName ), vSaveAs, "ActionAfterSaveAS", "SaveAsName8" );
   UfCompressName( szNewName, szOutName, 8, "", "", "", "", 0 );

   //Name is not required, create Source File Names
   if ( zstrcmp( szOutName, "" ) != 0 )
   {
      SetAttributeFromString(   vSaveAs, "ActionAfterSaveAS", "DLL_Name", szOutName );

      for ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vSaveAs, "SourceFile", "" ) )
      {
         // if Dialog in DialogList, call zwTZPNTRAD_SetSaveAsName
         if ( SetCursorFirstEntityByString( vTZDialogCopy, "W_MetaDef", "Name",
                                            szOutName, "" ) >= zCURSOR_SET )
         {
            zwTZPNTRAD_SetSaveAsName( vSubtask );
         }
         else
         {
            // if Dialog not in DialogList, create all new Source
            // File Names
            nIndex = zwfnTZPNTRAD_SaveAsSetSourceName( vSubtask, vSaveAs,
                                                       0, nIndex );
         }
      }
   } //endif ( zstrcmp( szOutName, "" ) != 0 )

   DropView( vTZDialogCopy );

   return( 0 );
} // zwTZPNTRAD_SaveAsSetDefaults

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwfnTZPNTRAD_SaveAsSetSourceName
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
zwfnTZPNTRAD_SaveAsSetSourceName( zVIEW   vSubtask,
                                  zVIEW   vSaveAs,
                                  zVIEW   vDialogData,
                                  zSHORT  nIndex )
{
   zCHAR  szNewName[33];
   zCHAR  szIndex[ 4 ];
   zSHORT nPosition = 0;
   zSHORT nRC;

   szNewName[ 0 ] = 0;

   do
   {
      nIndex++;
      GetStringFromAttribute( szNewName, zsizeof( szNewName ), vSaveAs, "ActionAfterSaveAS",
                              "SaveAsName8" );
      if ( nIndex > 0 )
      {
         nPosition = (zSHORT) zstrlen( szNewName );
         if ( nPosition > 6 )
            nPosition = 6;

         zltoa( nIndex, szIndex, zsizeof( szIndex ) );
         if ( nIndex < 10 )
         {
            strncpy_s( szNewName + nPosition, zsizeof( szNewName ) - nPosition, "_", 1 );
            strncpy_s( szNewName + 1 + nPosition, zsizeof( szNewName ) - 1 - nPosition, szIndex, 2 );
         }
         else
         {
            if ( nPosition == 6 )
               nPosition--;
            strncpy_s( szNewName + nPosition, zsizeof( szNewName ) - nPosition, "_", 1 );
            strncpy_s( szNewName + 1 + nPosition, zsizeof( szNewName ) - 1 - nPosition, szIndex, 3 );
         }
      }
      nRC = -1;
      if ( vDialogData )
         nRC = SetCursorFirstEntityByString( vDialogData, "SourceFile", "Name", szNewName, "" );

   } while ( nRC >= zCURSOR_SET );

   SetAttributeFromString( vSaveAs, "SourceFile", "SaveAsName", szNewName );

   return( nIndex );
} // zwfnTZPNTRAD_SaveAsSetSourceName

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_SetSaveAsName
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_SetSaveAsName( zVIEW vSubtask )
{
   zVIEW  vTZDIALOGS;
   zVIEW  vTZWINDOWL;
   zVIEW  vSaveAs;
   zVIEW  vDialogData;
   zSHORT nRC;
   zSHORT nRC1 = -1;
   zSHORT nIndex = 0;

   GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK );

   SetAttributeFromAttribute( vSaveAs, "ActionAfterSaveAS", "SaveAsName8",
                              vTZDIALOGS, "W_MetaDef", "Name" );

   // set Description
   if ( GetCtrlState( vSubtask, "cbKeepCurrentDesc", zCONTROL_STATUS_CHECKED ) != 1 )
   {
      SetAttributeFromAttribute( vSaveAs, "ActionAfterSaveAS", "Desc",
                                 vTZDIALOGS, "W_MetaDef", "Desc" );
   }

   // set DLL Name and Source File Name
   if ( CompareAttributeToAttribute( vTZDIALOGS, "W_MetaDef", "Name",
                                     vTZWINDOWL, "Dialog", "Tag" ) == 0 )
   {
      CreateViewFromViewForTask( &vDialogData, vTZWINDOWL, 0 );
   }
   else
   {
      if ( ActivateMetaOI( vSubtask, &vDialogData, vTZDIALOGS, zSOURCE_DIALOG_META,
                           zSINGLE | zLEVEL_TASK ) != 1 )
      {
         return( -1 );
      }
   }

   SetAttributeFromAttribute( vSaveAs, "ActionAfterSaveAS", "DLL_Name",
                              vDialogData, "Dialog", "DLL_Name" );

   if ( CheckExistenceOfEntity( vDialogData, "SourceFile" ) >= zCURSOR_SET )
      OrderEntityForView( vDialogData, "SourceFile", "LanguageType D Name A" );
   else
      nIndex = -1;

   // set new source Files name
   nRC1 = SetCursorFirstEntity( vDialogData, "SourceFile", "" );
   for ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vSaveAs, "SourceFile", "" ) )
   {
      if ( nRC1 == zCURSOR_SET &&
           CompareAttributeToAttribute( vSaveAs, "SourceFile", "LanguageType",
                                        vDialogData, "SourceFile", "LanguageType" ) == 0 )
      {
         SetAttributeFromAttribute( vSaveAs, "SourceFile", "SaveAsName",
                                    vDialogData, "SourceFile", "Name" );
         nRC1 = SetCursorNextEntity( vDialogData, "SourceFile", "" );
      }
      else
      {
         nIndex = zwfnTZPNTRAD_SaveAsSetSourceName( vSubtask, vSaveAs, vDialogData, nIndex );
      }
   } // endfor ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );

   DropMetaOI( vSubtask, vDialogData );
   SetFocusToCtrl( vSubtask, "edDialogName" );

   return( 0 );
} // zwTZPNTRAD_SetSaveAsName

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_SaveAsKeepCurrentDesc
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_SaveAsKeepCurrentDesc( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vSaveAs;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK );

   if ( GetCtrlState( vSubtask, "cbKeepCurrentDesc", zCONTROL_STATUS_CHECKED ) == 1 )
   {
      SetAttributeFromAttribute( vSaveAs, "ActionAfterSaveAS", "Desc", vTZWINDOWL, "Dialog", "Desc" );
      RefreshCtrl( vSubtask, "edDesc" );
   }

   return( 0 );
} // zwTZPNTRAD_SaveAsKeepCurrentDesc

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_ResetView
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_ResetView( zVIEW vSubtask )
{
   zVIEW   vSaveAs;

   if ( GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      SetAttributeFromInteger( vSaveAs, "ActionAfterSaveAS", "Typ", zNoActionAfterSaveAs );
      SetAttributeFromString( vSaveAs, "ActionAfterSaveAS", "SaveAsName8", "" );
   }

   return( 0 );
} // zwTZPNTRAD_ResetView

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwfnTZPNTRAD_SaveAsCheckFileName
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
zwfnTZPNTRAD_SaveAsCheckFileName( zVIEW    vSubtask,
                                  zVIEW    vSaveAs )
{
   zVIEW    vSaveAsCopy;
   zSHORT   nRC;
   zCHAR    szNewName[33];
   zCHAR    szFileName[33];
   zCHAR    szMsg[ 100 ];

   CreateViewFromViewForTask( &vSaveAsCopy, vSaveAs, 0 );

   for ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vSaveAs, "SourceFile", "" ) )
   {
      // Source File Name is required
      GetStringFromAttribute( szNewName, zsizeof( szNewName ), vSaveAs, "SourceFile", "SaveAsName" );
      UfCompressName( szNewName, szFileName, 8, "", "", "", "", 0 );
      if ( zstrcmp( szFileName, "" ) == 0 )
      {
         MessageSend( vSubtask, "ZO00137", "Dialog Maintenance",
                      "Source File Name is required.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         SetFocusToCtrl( vSubtask, "ssSourceFile" );
         DropView( vSaveAsCopy );
         return( -2 );
      }

      // check duplicate Source File Names
      SetCursorFirstEntityByString( vSaveAsCopy, "SourceFile", "SaveAsName", szNewName, "" );
      if ( SetCursorNextEntityByString( vSaveAsCopy, "SourceFile", "SaveAsName",
                                        szNewName, "" ) >= zCURSOR_SET )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Source File Name '" );
         strcat_s( szMsg, zsizeof( szMsg ), szNewName );
         strcat_s( szMsg, zsizeof( szMsg ), "' is not unique." );
         MessageSend( vSubtask, "ZO00137", "Dialog Maintenance",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         SetFocusToCtrl( vSubtask, "ssSourceFile" );
         DropView( vSaveAsCopy );
         return( -2 );
      }

   } // endfor ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );

   DropView( vSaveAsCopy );

   return( 0 );
} //zwfnTZPNTRAD_SaveAsCheckFileName

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwfnTZPNTRAD_SaveAsCheckName
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
zwfnTZPNTRAD_SaveAsCheckName( zVIEW    vSubtask,
                              zVIEW    vSaveAs,
                              zPCHAR   szOutName )
{
   zVIEW  vLOD_LPLR;
   zCHAR  szMsg[155];
   zCHAR  szDLLName[33];
   zCHAR  szNewName[33];

   // Dialog Name is required
   if ( zstrcmp( szOutName, "" ) == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Dialog Name is required." );
      MessageSend( vSubtask, "ZO00137", "Dialog Maintenance",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      SetFocusToCtrl( vSubtask, "edDialogName" );
      return( -2 );
   }

   // DLL Name is required
   GetStringFromAttribute( szNewName, zsizeof( szNewName ), vSaveAs, "ActionAfterSaveAS", "DLL_Name" );
   UfCompressName( szNewName, szDLLName, 8, "", "", "", "", 0 );
   if ( zstrcmp( szDLLName, "" ) == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "DLL Name is required." );
      MessageSend( vSubtask, "ZO00137", "Dialog Maintenance",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      SetFocusToCtrl( vSubtask, "edDLLName" );
      return( -2 );
   }

   // There must be no LOD with same name.
   RetrieveViewForMetaList( vSubtask, &vLOD_LPLR, zREFER_LOD_META );
   if ( SetCursorFirstEntityByString( vLOD_LPLR, "W_MetaDef", "Name",
                                      szOutName, 0 ) > zCURSOR_UNCHANGED )
   {
      MessageSend( vSubtask, "PN00221", "Zeidon Object Maintenance",
                   "A LOD with the same name exists.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      SetFocusToCtrl( vSubtask, "edDialogName" );
      return( -2 );
   }
   DropView( vLOD_LPLR );

   if ( zwfnTZPNTRAD_SaveAsCheckFileName( vSubtask, vSaveAs ) < 0 )
   {
      return( -2 );
   }

   return( 0 );
} // zwfnTZPNTRAD_SaveAsCheckName

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwfnTZPNTRAD_SaveAsCheckStatus
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
zwfnTZPNTRAD_SaveAsCheckStatus( zVIEW    vSubtask,
                                zVIEW    vTZDIALOGS,
                                zPCHAR   szOutName )
{
   zCHAR  szMsg[155];

   //check the check out state
   if ( CompareAttributeToInteger( vTZDIALOGS, "W_MetaDef",
                                   "Status", 1 ) != 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Dialog '" );
      strcat_s( szMsg, zsizeof( szMsg ), szOutName );
      strcat_s( szMsg, zsizeof( szMsg ), "' is not checked out." );
      MessageSend( vSubtask, "ZO00137", "Dialog Maintenance",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      SetFocusToCtrl( vSubtask, "edDialogName" );
      return( -1 );
   }

   return( 0 );
} // zwfnTZPNTRAD_SaveAsCheckStatus

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwfnTZPNTRAD_SaveAsGetFileName
//
//    PARAMETER:
//    pchSourceFileName : Size fo pchSourceFileName has to be at least  zMAX_FILESPEC_LTH + 1
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
zwfnTZPNTRAD_SaveAsGetFileName( zVIEW  vTaskLPLR,
                                zVIEW  vView,
                                zPCHAR pchAttribute,
                                zPCHAR pchSourceFileName )
{
   zCHAR    szExtension[ zMAX_EXTENSION_LTH + 1 ];
   zCHAR    szNewName[ 33 ];
   zCHAR    szFileName[ 33 ];

   GetStringFromAttribute( szNewName, zsizeof( szNewName ), vView, "SourceFile", pchAttribute );
   UfCompressName( szNewName, szFileName, 8, "", "", "", "", 0 );

   GetStringFromAttribute( pchSourceFileName, zMAX_FILESPEC_LTH + 1, vTaskLPLR, "LPLR", "PgmSrcDir" );
   GetStringFromAttributeByContext( szExtension, vView, "SourceFile",
                                    "LanguageType", "LanguageType", zMAX_EXTENSION_LTH );

   ofnTZCMWKSO_AppendSlash( pchSourceFileName );
   strcat_s( pchSourceFileName, zMAX_FILESPEC_LTH + 1, szFileName );
   strcat_s( pchSourceFileName, zMAX_FILESPEC_LTH + 1, "." );
   strcat_s( pchSourceFileName, zMAX_FILESPEC_LTH + 1, szExtension );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwfnTZPNTRAD_SaveAsCopyFiles
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
zwfnTZPNTRAD_SaveAsCopyFiles( zVIEW    vSubtask,
                              zVIEW    vTZWINDOWL,
                              zVIEW    vSaveAs )
{
   zVIEW    vTaskLPLR;
   zVIEW    vSourceFile;
   zLONG    hFile;
   zSHORT   nRC;
   zBOOL    bReadOnly = FALSE;
   zCHAR    szMsg[ zMAX_FILESPEC_LTH + zSHORT_MESSAGE_LTH + 1 ];
   zCHAR    szSourceFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szNewFileName[ zMAX_FILESPEC_LTH + 1 ];

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   strcpy_s( szSourceFileName, zsizeof( szSourceFileName ), "" );

   // Source File Name already exists
   for ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vSaveAs, "SourceFile", "" ) )
   {
      zwfnTZPNTRAD_SaveAsGetFileName( vTaskLPLR, vSaveAs, "SaveAsName", szNewFileName );
      SetAttributeFromInteger( vSaveAs, "SourceFile", "ReplaceFile", 1 );

      hFile = SysOpenFile( vSubtask, szNewFileName, COREFILE_EXIST );
      if ( hFile == 1 )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Source File '" );
         strcat_s( szMsg, zsizeof( szMsg ), szNewFileName );
         strcat_s( szMsg, zsizeof( szMsg ), "' already exists. Replace existing File?" );
         nRC = MessagePrompt( vSubtask, "ZO00138", "Dialog Maintenance",
                              szMsg, zBEEP, zBUTTONS_YESNOCANCEL,
                              zRESPONSE_YES, zICON_QUESTION );

         if ( nRC == zRESPONSE_CANCEL )
         {
            SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
            SetFocusToCtrl( vSubtask, "ssSourceFile" );
            return( -1 );
         }
         else
         {
            if ( nRC == zRESPONSE_NO )
               SetAttributeFromInteger( vSaveAs, "SourceFile", "ReplaceFile", 0 );
         }
      }
   } // endfor ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );

   if ( MiGetUpdateForView( vTZWINDOWL ) == 0 )
   {
      bReadOnly = TRUE;
      SetViewUpdate( vTZWINDOWL );
   }

   // Set new Description and DLL Name
   SetAttributeFromAttribute( vTZWINDOWL, "Dialog", "Desc",
                              vSaveAs, "ActionAfterSaveAS", "Desc" );
   SetAttributeFromAttribute( vTZWINDOWL, "Dialog", "DLL_Name",
                              vSaveAs, "ActionAfterSaveAS", "DLL_Name" );

   // copy Source Files and set new Source File Name
   CreateViewFromViewForTask( &vSourceFile, vTZWINDOWL, 0 );
   for ( nRC = SetCursorFirstEntity( vSaveAs, "SourceFile", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vSaveAs, "SourceFile", "" ) )
   {
      if ( CompareAttributeToInteger( vSaveAs, "SourceFile", "ReplaceFile", 1 ) == 0 )
      {
         zwfnTZPNTRAD_SaveAsGetFileName( vTaskLPLR, vSaveAs, "SourceName", szSourceFileName );
         zwfnTZPNTRAD_SaveAsGetFileName( vTaskLPLR, vSaveAs, "SaveAsName", szNewFileName );
         SysCopyFile( vSubtask, szSourceFileName, szNewFileName, TRUE );
      }

      // set new Source FIle Name
      if ( SetCursorFirstEntityByAttr( vSourceFile, "SourceFile", "Name",
                                       vSaveAs, "SourceFile", "SourceName",
                                       "" ) == zCURSOR_SET )
      {
         SetAttributeFromAttribute( vSourceFile, "SourceFile", "Name",
                                    vSaveAs, "SourceFile", "SaveAsName" );
      }
   }

   DropView( vSourceFile );

   if ( bReadOnly == TRUE )
      SetViewReadOnly( vTZWINDOWL );

   return( 0 );
} // zwfnTZPNTRAD_SaveAsCopyFiles

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_SaveAsDialog
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_SaveAsDialog( zVIEW vSubtask )
{
   zSHORT nRC;
   zVIEW  vTZDIALOGS;
   zVIEW  vTZWINDOWL;
   zVIEW  vSaveAs;
   zCHAR  szNewName[ 33 ];
   zCHAR  szOutName[ 33 ];
   zCHAR  szMsg[ 255 ];

   GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   GetViewByName( &vSaveAs, "TZSAVEAS", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // Validate Dialog Name is OK
   GetStringFromAttribute( szNewName, zsizeof( szNewName ), vSaveAs, "ActionAfterSaveAS", "SaveAsName8" );
   UfCompressName( szNewName, szOutName, 8, "", "", "", "", 0 );

   //Name is required
   if ( zwfnTZPNTRAD_SaveAsCheckName( vSubtask, vSaveAs, szOutName ) < 0 )
      return( -1 );

   // Name already exists
   if ( SetCursorFirstEntityByString( vTZDIALOGS, "W_MetaDef", "Name",
                                      szOutName, 0 ) > zCURSOR_UNCHANGED )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Dialog already exists. Replace existing Dialog?" );
      nRC = MessagePrompt( vSubtask, "ZO00138", "Dialog Maintenance",
                           szMsg, zBEEP, zBUTTONS_YESNO,
                           zRESPONSE_NO, zICON_QUESTION );

      if ( nRC == zRESPONSE_NO )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         SetFocusToCtrl( vSubtask, "edDialogName" );
         return( -1 );
      }

      // check the check out state
      if ( zwfnTZPNTRAD_SaveAsCheckStatus( vSubtask, vTZDIALOGS, szOutName ) < 0 )
         return( -1 );

      // if this Dialog open, then save Dialog, not save as
      if ( CompareAttributeToString( vTZWINDOWL, "Dialog", "Tag", szOutName ) == 0 )
      {
         if ( zwfnTZPNTRAD_SaveAsCopyFiles( vSubtask, vTZWINDOWL, vSaveAs ) < 0 )
            return( -1 );

         SetAttributeFromString( vTZWINDOWL, "Dialog", "Tag", szOutName );
         SaveDialogFile( vSubtask );
         return( 0 );
      }
      else
      {
         // if another Dialog open, then replace existing Dialog
         nRC = DeleteMetaOI( vSubtask, vTZDIALOGS, zSOURCE_DIALOG_META );
      }
   }

   if ( zwfnTZPNTRAD_SaveAsCopyFiles( vSubtask, vTZWINDOWL, vSaveAs ) < 0 )
      return( -1 );

   SetAttributeFromString( vSaveAs, "ActionAfterSaveAS", "SaveAsName8", szOutName );
   zwTZPNTRAD_SaveAs( vSubtask, szOutName );

   zwfnTZPNTRAD_CheckActionAfterSaveAs( vSubtask );

   return( 0 );

} // zwTZPNTRAD_SaveAsDialog

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwfnTZPNTRAD_SaveAsSourceFiles
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
zwfnTZPNTRAD_SaveAsSourceFiles( zVIEW   vSubtask,
                                zVIEW   vNewDialog,
                                zVIEW   vOldDialog )
{
   zSHORT  nRC;

   // Copy each SourceFile subobject, with Operation information.
   nRC = SetCursorFirstEntity( vOldDialog, "SourceFile", "" );

   while ( nRC > zCURSOR_UNCHANGED )
   {
      CreateMetaEntity( vSubtask, vNewDialog, "SourceFile", zPOS_AFTER );
      SetMatchingAttributesByName( vNewDialog, "SourceFile",
                                   vOldDialog, "SourceFile", zSET_NULL );
      nRC = SetCursorFirstEntity( vOldDialog, "Operation", "" );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         CreateMetaEntity( vSubtask, vNewDialog, "Operation", zPOS_AFTER );
         SetMatchingAttributesByName( vNewDialog, "Operation",
                                      vOldDialog, "Operation", zSET_NULL );
         nRC = SetCursorFirstEntity( vOldDialog, "Parameter", "" );
         while ( nRC > zCURSOR_UNCHANGED )
         {
            // Abort with error message if the Parameter.ShortDesc attribute is
            // null, since ShortDesc is a required attribute and we don't want
            // to continue to migrate a Dialog with an error.
            if ( CompareAttributeToString( vOldDialog, "Parameter", "ShortDesc",
                 "" ) == 0 )
            {
               SetAttributeFromString( vOldDialog, "Parameter", "ShortDesc", "Subtask" );
            }

            CreateMetaEntity( vSubtask, vNewDialog, "Parameter", zPOS_AFTER );
            SetMatchingAttributesByName( vNewDialog, "Parameter",
                                         vOldDialog, "Parameter", zSET_NULL );

            nRC = SetCursorNextEntity( vOldDialog, "Parameter", "" );
         }
         nRC = SetCursorNextEntity( vOldDialog, "Operation", "" );
      }
      nRC = SetCursorNextEntity( vOldDialog, "SourceFile", "" );
   }

   return( 0 );
} // zwfnTZPNTRAD_SaveAsSourceFiles

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_SaveAs
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_SaveAs( zVIEW   vSubtask,
                   zPCHAR  szDialogName)
{
   zVIEW     vLPLR;
   zVIEW     vLPLR2;
   zVIEW     vOldDialog;
   zVIEW     vNewDialog;
   zVIEW     vTZDIALOGS;
   zSHORT    nRC;
   zCHAR     szViewObjRefName[ 33 ];
   zCHAR     szDfltWnd[ 33 ];
   zCHAR     szOldDialogName[ 33 ];

   GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   GetViewByName( &vOldDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   SetNameForView( vOldDialog, "vOldDialog", vSubtask, zLEVEL_TASK );

   ActivateEmptyMetaOI( vSubtask, &vNewDialog, zSOURCE_DIALOG_META, zSINGLE );
   SetNameForView( vNewDialog, "vNewDialog", vSubtask, zLEVEL_TASK );

   //Create Root-Entity
   CreateMetaEntity( vSubtask, vNewDialog, "Dialog", zPOS_AFTER );
   SetAttributeFromString( vNewDialog, "Dialog", "Tag", szDialogName );
   SetAttributeFromAttribute( vNewDialog, "Dialog", "LastSyncDate",
                              vOldDialog, "Dialog", "LastSyncDate" );
   SetAttributeFromAttribute( vNewDialog, "Dialog", "Desc",
                              vOldDialog, "Dialog", "Desc" );
   SetAttributeFromAttribute( vNewDialog, "Dialog", "DLL_Name",
                              vOldDialog, "Dialog", "DLL_Name" );

   // Copy each Registered View Name that is used by the Dialog.
   CreateViewFromViewForTask( &vLPLR2, vLPLR, 0 );
   nRC = SetCursorFirstEntity( vOldDialog, "ViewObjRef", "" );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      GetStringFromAttribute( szViewObjRefName, zsizeof( szViewObjRefName ), vOldDialog, "ViewObjRef", "Name" );
      oTZWDLGSO_PositionOnVOR( vNewDialog, vOldDialog, vLPLR2,
                               szViewObjRefName, vSubtask );
      nRC = SetCursorNextEntity( vOldDialog, "ViewObjRef", "" );
   }

   // Copy each SourceFile subobject, with Operation information.
   zwfnTZPNTRAD_SaveAsSourceFiles( vSubtask, vNewDialog, vOldDialog );

   // Copy Windows
   GetStringFromAttribute( szOldDialogName, zsizeof( szOldDialogName ), vOldDialog, "Dialog", "Tag" );
   nRC = SetCursorFirstEntity( vOldDialog, "Window", "" );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      if ( oTZWDLGSO_CloneWindow( vNewDialog, vOldDialog, vLPLR, vSubtask ) == -1 )
         return( -1 );

      // Set new Dialog Name in Action
      for ( nRC = SetCursorFirstEntityByString( vNewDialog, "Action", "DialogName",
                                                szOldDialogName, "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntityByString( vNewDialog, "Action", "DialogName",
                                               szOldDialogName, "" ) )
      {
         SetAttributeFromString( vNewDialog, "Action", "DialogName", szDialogName );
      }


      nRC = SetCursorNextEntity( vOldDialog, "Window", "" );
   }

   // Now include the Primary Window.
   if ( SetCursorFirstEntity( vOldDialog, "DfltWnd", 0 ) == zCURSOR_SET )
   {
      GetStringFromAttribute( szDfltWnd, zsizeof( szDfltWnd ), vOldDialog, "DfltWnd", "Tag" );
      SetCursorFirstEntityByString( vNewDialog, "Window", "Tag", szDfltWnd, "" );
      IncludeSubobjectFromSubobject( vNewDialog, "DfltWnd",
                                     vNewDialog, "Window", zPOS_AFTER );
   }

   SetCursorFirstEntity( vNewDialog, "Dialog", "" );
   SetNameForView( vNewDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   SetNameForView( vNewDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );

   SaveDialogFile( vSubtask );

   GetViewByName( &vTZDIALOGS, "TZDIALOGS", vSubtask, zLEVEL_TASK );
   SetCursorFirstEntityByAttr( vTZDIALOGS, "W_MetaDef", "CPLR_ZKey",
                               vNewDialog, "Dialog", "ZKey", "" );

   OpenDialogFile( vSubtask );
   DropObjectInstance( vOldDialog );

   return( 0 );
} // zwTZPNTRAD_SaveAs

/////////////////////////////////////////////////////////////////////////////
//
// One of vTgt and vTgtCtrl must be non-null (both may be non-null).
// If vTgt is null, use vTgtCtrl as the Top level view.  Otherwise if
// vTgtCtrl is not null, use vTgt as the Top level view and copy all
// of the source controls as children of the control pointed to by vTgtCtrl.
//
// In source ctrls, the first bit of the OptionFlags attribute to specify:
//    0 - parent control is required
//    1 - parent control is NOT required.
//
// N.B.  This operation is called dynamically from tzctlptx.cpp fnMergeCtrls!
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
MergeCtrls( zVIEW  vSubtask,
            zVIEW  vTgt,
            zVIEW  vSrc,
            zVIEW  vTgtCtrl,
            zVIEW  vSrcLPLR,
            zVIEW  vPE,
            zBOOL  bReport )
{
   zVIEW  vTgtC;
   zVIEW  vSrcC;
   zLONG  lTypeTgt;
   zLONG  lTypeSrc;
   zLONG  lZKey = 0;
   zSHORT nRC;

   CreateViewFromViewForTask( &vSrcC, vSrc, 0 );
   if ( vTgt == 0 )
      vTgt = vTgtCtrl;

   if ( vTgtCtrl )
   {
      zLONG  lCtrlCnt;
      zBOOL  bMatch = FALSE;

      CreateViewFromViewForTask( &vTgtC, vTgtCtrl, 0 );

      // First try to match on type of ctrl where the ctrl count is 1 in
      // in both the source and target ctrls.
      lCtrlCnt = CountEntitiesForView( vSrcC, "Control" );
      GetIntegerFromAttribute( &lTypeTgt, vTgtC, "ControlDef", "Key" );
      while ( bMatch == FALSE && lCtrlCnt == 1 )
      {
         GetIntegerFromAttribute( &lTypeSrc, vSrcC, "ControlDef", "Key" );
         if ( lTypeSrc == lTypeTgt )
            bMatch = TRUE;
         else
         {
            SetViewToSubobject( vSrcC, "CtrlCtrl" );
            lCtrlCnt = CountEntitiesForView( vSrcC, "Control" );
         }
      }

      if ( bMatch == FALSE )
      {
         while ( ResetViewFromSubobject( vSrcC ) == 0 )
         {
         }
      }

      // Now go as deep as possible in the subobjects matching on type of ctrl
      // where the ctrl count is 1 in in both the source and target ctrls.
      while ( CountEntitiesForView( vTgtC, "CtrlCtrl" ) == 1 &&
              CountEntitiesForView( vSrcC, "CtrlCtrl" ) == 1 )
      {
         SetViewToSubobject( vTgtC, "CtrlCtrl" );
         SetViewToSubobject( vSrcC, "CtrlCtrl" );
         GetIntegerFromAttribute( &lTypeTgt, vTgtC, "ControlDef", "Key" );
         GetIntegerFromAttribute( &lTypeSrc, vSrcC, "ControlDef", "Key" );
         if ( lTypeSrc != lTypeTgt )
         {
            ResetViewFromSubobject( vTgtC );
            ResetViewFromSubobject( vSrcC );
            break;
         }
      }

      GetIntegerFromAttribute( &lTypeTgt, vTgtC, "ControlDef", "Key" );
      GetIntegerFromAttribute( &lTypeSrc, vSrcC, "ControlDef", "Key" );
      if ( lTypeSrc == lTypeTgt )
      {
         zLONG lFlags;

         GetIntegerFromAttribute( &lFlags, vSrcC, "Control", "OptionFlags" );
         if ( (lFlags & 0x00000001) == 0x00000001 ) // parent not required
            SetViewToSubobject( vTgtC, "CtrlCtrl" );
      }
      else
      if ( CheckExistenceOfEntity( vTgtC, "Control" ) == 0 )
         SetViewToSubobject( vTgtC, "CtrlCtrl" );
   }
   else
   {
      CreateViewFromViewForTask( &vTgtC, vTgt, 0 );
   }

   GetIntegerFromAttribute( &lTypeTgt, vTgtC, "ControlDef", "Key" );
   GetIntegerFromAttribute( &lTypeSrc, vSrcC, "ControlDef", "Key" );
   while ( CountEntitiesForView( vSrcC, "Control" ) == 1 )
   {
      zLONG lFlags;

      GetIntegerFromAttribute( &lFlags, vSrcC, "Control", "OptionFlags" );
      if ( (lFlags & 0x00000001) == 0x00000001 ) // parent not required
         SetViewToSubobject( vSrcC, "CtrlCtrl" );
      else
         break;
   }

   GetIntegerFromAttribute( &lTypeTgt, vTgtC, "ControlDef", "Key" );
   GetIntegerFromAttribute( &lTypeSrc, vSrcC, "ControlDef", "Key" );
   if ( bReport == FALSE )
   {
      nRC = SetCursorFirstEntity( vSrc, "Action", 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         if ( fnCloneAction( vSrcLPLR, vSrc, vTgt, vSubtask ) == -1 )
         {
            DropView( vTgtC );
            DropView( vSrcC );
            return( -1 );
         }

         nRC = SetCursorNextEntity( vSrc, "Action", 0 );
      }
   }

// SetNameForView( vSrcC, "CloneViewSrcC", vSubtask, zLEVEL_TASK );
   nRC = SetCursorFirstEntity( vSrcC, "Control", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      // We will try to prevent recursive copies by holding onto the
      // ZKey of the current source control.  If we are going to copy
      // that control again, we will break.
      GetIntegerFromAttribute( &lZKey, vSrcC, "Control", "ZKey" );
      if ( fnCloneControl( vSrcLPLR, vSrc, vSrcC, vTgt, vTgtC, vPE,
                           bReport, vSubtask ) == -1 )
      {
         DropView( vTgtC );
         DropView( vSrcC );
         return( -1 );
      }

   // MessageBox( 0, "BeforeNextEntity", "MergeCtrls", MB_OK );
/*
BL 2000.09.04:
This code was commented out, because cut and paste with more than one
control did not work. The Compare is always TRUE, since vSrcC does
not change position and thus lZKey is compared to itself.
DKS: this code was introduced to avoid a loop. As there were changes in
fnCloneControl, this check is not necessary any more.
      if ( bReport == FALSE &&
           CompareAttributeToInteger( vSrcC, "Control", "ZKey", lZKey ) == 0 )
      {
         break;
      }
*/
      nRC = SetCursorNextEntity( vSrcC, "Control", 0 );
   // MessageBox( 0, "AfterNextEntity", "MergeCtrls", MB_OK );
      if ( CompareAttributeToInteger( vSrcC, "Control", "ZKey", lZKey ) == 0 )
      {
         break;
      }
   }

   DropView( vTgtC );
   DropView( vSrcC );
   return( 0 );
}

#if 0
// Recursive routine to clone options within a Menu.
zSHORT
fnCloneOptions( zVIEW  vTgt,
                zVIEW  vSrc,
                zVIEW  vTgtO,
                zVIEW  vSrcO,
                zVIEW  vSrcLPLR,
                zVIEW  vPE,
                zVIEW  vSubtask )
{
   zSHORT nRC;


   nRC = SetCursorFirstEntity( vSrcO, "Option", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      CreateMetaEntity( vSubtask, vTgtO, "Option", zPOS_AFTER );
      SetMatchingAttributesByName( vTgtO, "Option",
                                   vSrcO, "Option", zSET_NULL );

      if ( CheckExistenceOfEntity( vSrcO, "OptAct" ) > zCURSOR_UNCHANGED )
      {
         GetAddrForAttribute( &pch, vSrcO, "OptAct", "Tag" );
         if ( pch[ 0 ] )
         {
            if ( SetCursorFirstEntityByString( vTgt, "Act", "Tag",
                                               pch, 0 ) == zCURSOR_SET )
            {
               IncludeSubobjectFromSubobject( vTgtO, "OptAct",
                                              vTgt, "Act",
                                              zPOS_AFTER );
            }
            else
            {
               MessageSend( vSubtask, "CM00807", "Configuration Management",
                            "Opt cannot locate action for include",
                            zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               TraceLineS( "(tzpntrad) Option cannot locate action "
                              "for include ", pch );
            }
         }
      }

      if ( CheckExistenceOfEntity( vSrcO, "OptMap" ) > zCURSOR_UNCHANGED )
      {
         GetAddrForAttribute( &pch, vSrcO, "OptMap", "Tag" );
         CreateEntity( vTgtO, "OptMap", zPOS_AFTER );

         // Now reset the target values from the relationship values.
         if ( CheckExistenceOfEntity( vSrcO, "OptMapView" ) == 0 )
            SetAttributeFromAttribute( vTgtO, "OptMap", "VN",
                                       vSrcO, "OptMapView",
                                       "Name" );

         if ( CheckExistenceOfEntity( vSrcO, "OptMapLOD_Attribute" ) == 0 )
         {
            SetAttributeFromAttribute( vTgtO, "OptMap", "EN",
                                       vSrcO, "OptMapRelatedEntity",
                                       "Name" );
            SetAttributeFromAttribute( vTgtO, "OptMap", "AN",
                                       vSrcO, "OptMapER_Attribute",
                                       "Name" );
         }

         if ( CheckExistenceOfEntity( vSrcO, "OptMapContext" ) == 0 )
         {
            SetAttributeFromAttribute( vTgtO, "OptMap", "Context",
                                       vSrcO, "OptMapContext", "Name" );
         }

         SetAttributeFromAttribute( vTgtO, "Opt", "ChkOn",
                                    vSrcO, "Option",
                                    "CheckMarkValueOn" );
         SetAttributeFromAttribute( vTgtO, "Opt", "ChkOff",
                                    vSrcO, "Option",
                                    "CheckMarkValueOff" );
      }

      nRC = SetCursorFirstEntity( vSrcO, "OptOpt", 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         SetViewToSubobject( vSrcO, "OptOpt" );
         SetViewToSubobject( vTgtO, "OptOpt" );
         nRC = fnCloneOptions( vTgt, vSrc, vTgtO, vSrcO, vSrcLPLR, vPE, vSubtask );
         ResetViewFromSubobject( vSrcO );
         ResetViewFromSubobject( vTgtO );
         if ( nRC == -1 )
            return( -1 );

         nRC = SetCursorNextEntity( vSrcO, "OptOpt", 0 );
      }


      if ( CheckExistenceOfEntity(
         if ( CompareAttributeToString( vSrcC, "EventAct", "Tag", "" ) != 0 )
         {
            CreateMetaEntity( vSubtask, vTgtC, "Event", zPOS_AFTER );
            SetMatchingAttributesByName( vTgtC, "Event",
                                         vSrcC, "Event", zSET_NULL );
            GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcC, "EventAct", "Tag" );
            nRC = SetCursorFirstEntityByString( vTgt, "Action", "Tag", szTag, 0 );
            if ( nRC >= 0 )
            {
               IncludeSubobjectFromSubobject( vTgtC, "EventAct",
                                              vTgt, "Action", zPOS_AFTER );
            }
         }

      nRC = SetCursorNextEntity( vSrcO, "Option", 0 );
   }


   nRC = SetCursorFirstEntity( vSrcO, "CtrlMap", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      if ( fnCloneCtrlMap( vTgt, vTgtO, vSrc, vSrcO, vSrcLPLR, vSubtask ) == -1 )
         return( -1 );

      nRC = SetCursorNextEntity( vSrcO, "CtrlMap", 0 );
   }

   if ( bReport == FALSE )
   {
      nRC = SetCursorFirstEntity( vSrcO, "Event", 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         if ( CompareAttributeToString( vSrcO, "EventAct", "Tag", "" ) != 0 )
         {
            CreateMetaEntity( vSubtask, vTgtO, "Event", zPOS_AFTER );
            SetMatchingAttributesByName( vTgtO, "Event",
                                         vSrcO, "Event", zSET_NULL );
            GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcO, "EventAct", "Tag" );
            nRC = SetCursorFirstEntityByString( vTgt, "Action", "Tag", szTag, 0 );
            if ( nRC >= 0 )
            {
               IncludeSubobjectFromSubobject( vTgtO, "EventAct",
                                              vTgt, "Action", zPOS_AFTER );
            }
         }

         nRC = SetCursorNextEntity( vSrcO, "Event", 0 );
      }
   }


   nRC = SetCursorFirstEntity( vSrcO, "CtrlMap", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      if ( fnCloneCtrlMap( vTgt, vTgtO, vSrc, vSrcO, vSrcLPLR, vSubtask ) == -1 )
         return( -1 );

      nRC = SetCursorNextEntity( vSrcO, "CtrlMap", 0 );
   }

   if ( bReport == FALSE )
   {
      nRC = SetCursorFirstEntity( vSrcO, "Event", 0 );
      while ( nRC > zCURSOR_UNCHANGED )
      {
         if ( CompareAttributeToString( vSrcO, "EventAct", "Tag", "" ) != 0 )
         {
            CreateMetaEntity( vSubtask, vTgtO, "Event", zPOS_AFTER );
            SetMatchingAttributesByName( vTgtO, "Event",
                                         vSrcO, "Event", zSET_NULL );
            GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcO, "EventAct", "Tag" );
            nRC = SetCursorFirstEntityByString( vTgt, "Action", "Tag", szTag, 0 );
            if ( nRC >= 0 )
            {
               IncludeSubobjectFromSubobject( vTgtO, "EventAct",
                                              vTgt, "Action", zPOS_AFTER );
            }
         }

         nRC = SetCursorNextEntity( vSrcO, "Event", 0 );
      }
   }

   return( 0 );

   nRC = SetCursorFirstEntity( vSrcO, "Menu", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      if ( fnCloneMenu( vSrcLPLR, vSrcO, vTgtO, vPE,
                        bReport, vSubtask ) == -1 )
      {
         DropView( vTgt< );
         DropView( vSrcO );
         return( -1 );
      }

      nRC = SetCursorNextEntity( vSrcO, "Menu", 0 );
   }

   DropView( vTgtO );
   DropView( vSrcO );
   return( 0 );
}
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Use vTgt as the Top level view and copy the menu, options and related
// actions from the source window.
//
// N.B.  This operation is called dynamically from tzctlptx.cpp fnMergeMenu!
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
MergeMenu( zVIEW  vSubtask,
           zVIEW  vTgt,
           zVIEW  vSrc,
           zVIEW  vSrcLPLR,
           zVIEW  vPE )
{
   zVIEW  vTgtO;
   zVIEW  vSrcO;
   zCHAR  szMsg[ 65 ];
   zCHAR  szTag[ 33 ];
   zLONG  lUniqueId;
   zSHORT nLth;
   zSHORT nRC;

   CreateViewFromViewForTask( &vSrcO, vSrc, 0 );
   CreateViewFromViewForTask( &vTgtO, vTgt, 0 );

   while ( ResetViewFromSubobject( vSrcO ) == 0 )
   {
   }

   while ( ResetViewFromSubobject( vTgtO ) == 0 )
   {
   }

   nRC = SetCursorFirstEntity( vSrcO, "Action", 0 );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      if ( fnCloneAction( vSrcLPLR, vSrcO, vTgtO, vSubtask ) == -1 )
      {
         DropView( vTgtO );
         DropView( vSrcO );
         return( -1 );
      }

      nRC = SetCursorNextEntity( vSrcO, "Action", 0 );
   }

   CreateMetaEntity( vSubtask, vTgtO, "Menu", zPOS_AFTER );
   SetMatchingAttributesByName( vTgtO, "Menu",
                                vSrcO, "Menu", zSET_NULL );

   // Force unique MenuTag here.
   // Reset the current menu's tag so we won't find it by Tag while we
   // ensure that the tag is unique.
   GetStringFromAttribute( szTag, zsizeof( szTag ), vSrcO, "Menu", "Tag" );
   strcpy_s( szMsg, zsizeof( szMsg ), szTag ); // hold onto original tag
   SetAttributeFromString( vTgtO, "Menu", "Tag",
                           "__&&&__^^^__Clone__@@@__%%%__" );

   SetNameForView( vTgt, "CloneViewTgtO", vSubtask, zLEVEL_TASK );

   nLth = (zSHORT) zstrlen( szTag );
   while ( nLth && szTag[ nLth - 1 ] >= '0' && szTag[ nLth - 1 ] <= '9' )
      nLth--;

   lUniqueId = zatol( szTag + nLth );
   if ( nLth == 0 )
   {
      strcpy_s( szTag, zsizeof( szTag ), "Tag" );
      nLth = 3;
   }

   while ( SetCursorFirstEntityByString( vTgt, "Menu", "Tag", szTag, 0 ) == 0 )
   {
      lUniqueId++;
      zltoa( lUniqueId, szTag + nLth, zsizeof( szTag ) - nLth );
   }

// MessageBox( 0, "Text", "Title", MB_OK );
   SetAttributeFromString( vTgtO, "Menu", "Tag", szTag );

// fnCloneOptions( vTgt, vSrc, vTgtO, vSrcO, vSrcLPLR, vPE, vSubtask );
   nRC = SetCursorFirstEntity( vSrcO, "Option", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      oTZPNTRAD_CloneOption( vTgtO, vTgt, vSrcO, vSrc, zPOS_AFTER, vSubtask );
      nRC = SetCursorNextEntity( vSrcO, "Option", 0 );
   }

   DropView( vTgtO );
   DropView( vSrcO );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT OPERATION
GroupCtrlsMigration9J( zVIEW vSubtask )
{
   zVIEW  vDialog;
   zSHORT nRC;

   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) < 1 )
      return( -1 );

   fnPainterCall( zMSG_UPDATEZEIDONWINDOW, vSubtask, 0, 0, 0 );
   nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      fnRecurseGroupCtrls( vDialog );
      nRC = SetCursorNextEntity( vDialog, "Window", 0 );
   }

   fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zSHORT
fnChangeMappingViewR( zVIEW vDialog,
                      zVIEW vOldViewName,
                      zVIEW vNewViewName,
                      zBOOL bAllCtrlsAtLevel,
                      zBOOL bRecurse );

zBOOL g_bSkipPrompt = FALSE;
zLONG g_lFromWAB;
zLONG g_lToWAB;
zLONG g_lFromHeight;
zLONG g_lToHeight;
zCHAR g_szDlgTag[ 33 ];
zCHAR g_szGroupBox[ 33 ];
zCHAR g_szChangeFrom[ 4096 ];
zCHAR g_szChangeTo[ 4096 ];

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateAllJSP( zVIEW vSubtask );
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateAllJSPJava( zVIEW vSubtask );

#define zLISTBOX_COLUMNHEADERS         zCONTROL_SPECIFIC_3
#define zLISTBOX_SORTEDHEADERS         zCONTROL_SPECIFIC_2

#define zCOMBOBOX_NO_NULL             0x00000200L

#define zCHECK_OK                      0x00000001
#define zCHECK_EVENTS                  0x00000002
#define zCHECK_EVENTS_WEBJAVASCRIPT    0x00000004
//#define zCHECK_READONLY_LISTBOX        0x00000004
#define zCHECK_READONLY_EDITBOX        0x00000008
#define zCHECK_READONLY_ALL_CTRLS      0x00000020
#define zCHECK_CTRL_TYPE               0x00000010
#define zCHECK_DATETIMEDOMAIN_EDITBOX  0x00000040
#define zCHECK_DATEDOMAIN_EDITBOX      0x00000080
#define zCHECK_CALENDAR_TO_EDITBOX     0x00000100
#define zCHECK_ACTIVEX_PROPERTIES      0x00000200
//#define zCHECK_CHANGETAB_EVENT         0x00000400
//#define zCHECK_CHANGE_BREADCRUMB       0x00000400
//#define zCHECK_CHANGE_MOVEINCREMENT    0x00000400
//#define zCHECK_CHANGE_NOTETOREVIEWER   0x00000400
#define zCHECK_CHANGE_GROUPBOX_NEW     0x00000400
#define zCHECK_POSTBUILD_SETUP         0x00000800
#define zCHECK_INCREMENT_POS_SIZE      0x00010000
#define zCHECK_INCREMENT_POS_SIZEX     0x00011000
#define zCHECK_INCREMENT_POS_SIZEY     0x00012000
#define zCHECK_INCREMENT_POS_SIZEXY    0x00013000
#define zCHECK_DECREMENT_POS_SIZE      0x00020000
#define zCHECK_DECREMENT_POS_SIZEX     0x00021000
#define zCHECK_DECREMENT_POS_SIZEY     0x00022000
#define zCHECK_DECREMENT_POS_SIZEXY    0x00023000
#define zCHECK_CHANGE_EVENTS           0x00100000
#define zCHECK_COMBOBOX_NO_NULL        0x00200000
#define zCHECK_REPORT_EVENTS           0x00400000
#define zCHECK_REPORT_TAB_PAGES        0x00800000
#define zCHECK_REPORT_WEBMENUS         0x01000000
#define zCHECK_ADD_GROUPBOX            0x02000000
#define zCHECK_CHANGE_MAPPING          0x04000000
#define zCHECK_CHANGE_WAB              0x08000000
#define zCHECK_TIMESTAMP_ONLY          0x10000000
#define zCHECK_RESIZE_EDIT_CTRLS       0x20000000
#define zCHECK_SAVE_ALL_JSP            0x40000000
#define zCHECK_SAVE_ALL                0x80000000

zBOOL
CheckMigrateCtrls( zVIEW vDialog,
                   zVIEW vPE,
                   zLONG lCheckFlags,
                   zCPCHAR cpcDlgTag,
                   zCPCHAR cpcWndTag,
                   zLONG lData )
{
   zCHAR  szMsg[ 256 ];
   zCHAR  szDlgTag[ 34 ];
   zCHAR  szWndTag[ 34 ];
   zCHAR  szCtrlTag[ 34 ];
   zPCHAR pch;
   zBOOL  bChange = FALSE;
   zLONG  lSubtype;
   zLONG  lKey;
   zLONG  lPosX;
   zLONG  lPosY;
   zLONG  lSizeX;
   zLONG  lSizeY;
   zLONG  lIncrX;
   zLONG  lIncrY;
   zULONG ulLth;
   zSHORT nRC;

   nRC = SetCursorFirstEntity( vDialog, "Control", 0 );
   while ( nRC == zCURSOR_SET )
   {
      GetStringFromAttribute( szCtrlTag, zsizeof( szCtrlTag ), vDialog, "Control", "Tag" );

      if ( lCheckFlags & zCHECK_READONLY_ALL_CTRLS )
      {
         GetIntegerFromAttribute( &lSubtype, vDialog,
                                  "Control", "ExtendedStyle" );

         if ( (lSubtype & zCONTROLX_DISABLE_READONLY) == 0 )
         {
            bChange = TRUE;
            lSubtype |= zCONTROLX_DISABLE_READONLY;
            SetAttributeFromInteger( vDialog, "Control",
                                     "ExtendedStyle", lSubtype );
         }
      }
      else
      if ( lCheckFlags & (zCHECK_REPORT_EVENTS | zCHECK_CHANGE_WAB) )
      {
         zVIEW  vAct;
         zPCHAR pchAction;
         zPCHAR pchOperation;
         zLONG  lType;
         zLONG  lActType;

         CreateViewFromViewForTask( &vAct, vDialog, 0 );
         while ( ResetViewFromSubobject( vAct ) == 0 )
         {
         }

         zSHORT nRC = SetCursorFirstEntity( vDialog, "Event", 0 );
         while ( nRC >= zCURSOR_SET )
         {
            szDlgTag[ 0 ] = 0;
            szWndTag[ 0 ] = 0;
            pchOperation = "";
            if ( SetEntityCursor( vAct, "Action", 0,
                                  zPOS_FIRST | zQUAL_ENTITYCSR,
                                  vDialog, "EventAct",
                                  0, 0, 0, 0 ) >= zCURSOR_SET )
            {
               GetAddrForAttribute( &pchAction, vAct, "Action", "Tag" );
               GetIntegerFromAttribute( &lActType, vAct, "Action", "Type" );
               GetStringFromAttribute( szDlgTag, zsizeof( szDlgTag ), vAct, "Action", "DialogName" );
               GetStringFromAttribute( szWndTag, zsizeof( szWndTag ), vAct, "Action", "WindowName" );
               if ( CheckExistenceOfEntity( vAct, "ActOper" ) == 0 )
                  GetAddrForAttribute( &pchOperation, vAct, "ActOper", "Name" );
            }
            else
            {
               lActType = 0;
               pchAction = "";
            }

            GetIntegerFromAttribute( &lType, vDialog, "Event", "Type" );
            TraceLine( "Event Type: 0x%08x  Dlg.Wnd.Ctrl: %s.%s.%s", lType, cpcDlgTag, cpcWndTag, szCtrlTag );
            TraceLine( "                          Action: %s", pchAction );
            TraceLine( "                             WAB: %s", GetActionString( lActType ) );
            TraceLine( "                             Oper: %s", pchOperation );
            TraceLine( "                             ====> %s.%s", szDlgTag, szWndTag );
         // sprintf_s( szMsg, zsizeof( szMsg ), "Dlg.Wnd.Ctrl: %s.%s.%s Action: %s WAB: %s (%s.%s) Operation: %s",
         //           cpcDlgTag, cpcWndTag, szCtrlTag, pchAction,
         //           GetActionString( lActType ), szDlgTag, szWndTag, pchOperation );
         // TraceLine( "Event Type: 0x%08x  %s", lType, szMsg );
            if ( (lCheckFlags & zCHECK_CHANGE_WAB) && lActType == g_lFromWAB )
            {
               if ( OperatorPrompt( vDialog, "Convert selected WAB", szMsg, 0,
                                    zBUTTONS_YESNO, 0, 0 ) == zRESPONSE_YES )
               {
                  bChange = TRUE;
                  SetAttributeFromInteger( vAct, "Action", "Type", g_lToWAB );
               }
            }

            nRC = SetCursorNextEntity( vDialog, "Event", 0 );
         }
      }
      else
      if ( lCheckFlags &
           (zCHECK_INCREMENT_POS_SIZE | zCHECK_DECREMENT_POS_SIZE) )
      {
         bChange = TRUE;
         lIncrX = LOWORD( lData );
         if ( lIncrX < 0 )
            lIncrX = -lIncrX;

         lIncrY = HIWORD( lData );
         if ( lIncrY < 0 )
            lIncrY = -lIncrY;

         if ( ((lCheckFlags & zCHECK_INCREMENT_POS_SIZEX) ==
                                                zCHECK_INCREMENT_POS_SIZEX) ||
              ((lCheckFlags & zCHECK_DECREMENT_POS_SIZEX) ==
                                                zCHECK_DECREMENT_POS_SIZEX) )
         {
            GetIntegerFromAttribute( &lPosX, vDialog, "Control", "PSDLG_X" );
            GetIntegerFromAttribute( &lSizeX, vDialog, "Control", "SZDLG_X" );
            if ( (lCheckFlags & zCHECK_INCREMENT_POS_SIZEX) ==
                                                 zCHECK_INCREMENT_POS_SIZEX )
            {
               lPosX += lIncrX * lPosX / 100;
               lSizeX += lIncrX * lSizeX / 100;
               if ( lSizeX <= 0 )
               {
                  TraceLineS( "(trpntrad) Warning: Control size x became equal to zero; Control: ",
                              szCtrlTag );
               }
            }
            else
            {
               lPosX -= lIncrX * lPosX / 100;
               lSizeX -= lIncrX * lSizeX / 100;
               if ( lSizeX <= 0 )
               {
                  TraceLineS( "(trpntrad) Warning: Control size y became equal to zero; Control: ",
                              szCtrlTag );
               }
            }

            SetAttributeFromInteger( vDialog, "Control", "PSDLG_X", lPosX );
            SetAttributeFromInteger( vDialog, "Control", "SZDLG_X", lSizeX );
         }

         if ( ((lCheckFlags & zCHECK_INCREMENT_POS_SIZEY) ==
                                                zCHECK_INCREMENT_POS_SIZEY) ||
              ((lCheckFlags & zCHECK_DECREMENT_POS_SIZEY) ==
                                                zCHECK_DECREMENT_POS_SIZEY) )
         {
            GetIntegerFromAttribute( &lPosY, vDialog, "Control", "PSDLG_Y" );
            GetIntegerFromAttribute( &lSizeY, vDialog, "Control", "SZDLG_Y" );
            if ( (lCheckFlags & zCHECK_INCREMENT_POS_SIZEY) ==
                                                 zCHECK_INCREMENT_POS_SIZEY )
            {
               lPosY += lIncrY * lPosY / 100;
               lSizeY += lIncrY * lSizeY / 100;
            }
            else
            {
               lPosY -= lIncrY * lPosY / 100;
               lSizeY -= lIncrY * lSizeY / 100;
            }

            SetAttributeFromInteger( vDialog, "Control", "PSDLG_Y", lPosY );
            SetAttributeFromInteger( vDialog, "Control", "SZDLG_Y", lSizeY );
         }
      }
      else
      {
         GetIntegerFromAttribute( &lKey, vDialog, "ControlDef", "Key" );
         if ( CompareAttributeToInteger( vDialog, "ControlDef",
                                         "Key", lKey ) != 0 )
         {
            if ( lCheckFlags & zCHECK_SAVE_ALL )
            {
               if ( SetCursorFirstEntityByInteger( vPE, "ControlDef",
                                                   "Key", lKey, 0 ) == 0 )
               {
                  bChange = TRUE;
                  ExcludeEntity( vDialog, "ControlDef", zREPOS_NONE );
                  IncludeSubobjectFromSubobject( vDialog, "ControlDef",
                                                 vPE, "ControlDef", zPOS_BEFORE );
               }
               else
               {
                  TraceLine( "MigrateControls could NOT match PE for ControlDef "
                               "Key (%d) for Control: %s in Dlg.Wnd: %s.%s",
                             lKey, szCtrlTag, cpcDlgTag, cpcWndTag );
               }
            }
            else
            {
               TraceLine( "MigrateControls found unmatched ControlDef "
                            "Key (%d) for Control: %s in Dlg.Wnd: %s.%s",
                          lKey, szCtrlTag, cpcDlgTag, cpcWndTag );
            }
         }

         GetIntegerFromAttribute( &lKey, vDialog, "ControlDef", "Key" );

         if ( (lCheckFlags & zCHECK_ACTIVEX_PROPERTIES) &&
              lKey > 4000 && lKey < 32000 ) // ActiveX
         {
            GetAttributeLength( &ulLth, vDialog, "Control", "Properties" );
            if ( ulLth == 0 )
            {
               GetAttributeLength( &ulLth, vDialog, "Control", "CtrlBOI" );
               if ( ulLth )
               {
                  SetAttributeFromAttribute( vDialog, "Control", "Properties",
                                             vDialog, "Control", "CtrlBOI" );
                  SetAttributeFromBlob( vDialog, "Control", "CtrlBOI", "", 0 );
               }
            }
         }

         if ( (lCheckFlags & zCHECK_REPORT_TAB_PAGES) &&
              (lKey == zTAB_CONTROL) )
         {
            TraceLineS( "CreateSubSections -->", "" );
            TraceLineS( "CreateSubSections -->", "" );
            GetStringFromAttribute( szCtrlTag, zsizeof( szCtrlTag ), vDialog, "Control", "Tag" );
            TraceLine( "CreateSubSections -->   // %s.%s.%s",
                       cpcDlgTag, cpcWndTag, szCtrlTag );
            TraceLine( "CreateSubSections -->   IF mSecTmpl.SecuritySection.SectionName = \"%s\"",
                       cpcWndTag );
            zSHORT nRC = SetCursorFirstEntity( vDialog, "CtrlCtrl", 0 );
            while ( nRC >= zCURSOR_SET )
            {
               TraceLineS( "CreateSubSections -->",
                           "      CREATE ENTITY  mSecTmpl.SecuritySubSection" );

               GetStringFromAttribute( szCtrlTag, zsizeof( szCtrlTag ), vDialog, "CtrlCtrl", "Tag" );
               TraceLine( "CreateSubSections -->      mSecTmpl.SecuritySubSection.SubSectionName = \"%s\"",
                          szCtrlTag );
               TraceLineS( "CreateSubSections -->",
                           "      mSecTmpl.SecuritySubSection.AllowAccess =\"N\"" );

               nRC = SetCursorNextEntity( vDialog, "CtrlCtrl", 0 );
            }
         }

         if ( (lCheckFlags & zCHECK_CHANGE_EVENTS) &&
              (lKey == zEDIT_CONTROL || lKey == zCOMBOBOX_CONTROL) )
         {
            zVIEW vAct;
            zCHAR szTag[ 34 ];

            CreateViewFromViewForTask( &vAct, vDialog, 0 );
            while ( ResetViewFromSubobject( vAct ) == 0 )
            {
            }

            if ( lKey == zEDIT_CONTROL )
            {
               nRC = SetCursorFirstEntityByInteger( vDialog, "Event",
                                                    "Type", 18, "" );
               while ( nRC >= zCURSOR_SET )
               {
                  if ( SetEntityCursor( vAct, "Action", 0,
                                        zPOS_FIRST | zQUAL_ENTITYCSR,
                                        vDialog, "EventAct",
                                        0, 0, 0, 0 ) >= zCURSOR_SET )
                  {
                     if ( CompareAttributeToString( vAct, "Action",
                                                    "NoMap", "Y" ) != 0 )
                     {
                        GetStringFromAttribute( szTag, zsizeof( szTag ), vAct, "Action", "Tag" );
                        TraceLineS( "Edit Change Event found for Action: ",
                                    szTag );
                        TraceLineS( "   with Mapping not forced off in Window: ",
                                    cpcWndTag );
                     }
                  }

                  nRC = SetCursorNextEntityByInteger( vDialog, "Event",
                                                      "Type", 18, "" );
               }
            }

            if ( lKey == zCOMBOBOX_CONTROL )
            {
               nRC = SetCursorFirstEntityByInteger( vDialog, "Event",
                                                    "Type", 1, "" );
               while ( nRC >= zCURSOR_SET )
               {
                  if ( SetEntityCursor( vAct, "Action", 0,
                                        zPOS_FIRST | zQUAL_ENTITYCSR,
                                        vDialog, "EventAct",
                                        0, 0, 0, 0 ) >= zCURSOR_SET )
                  {
                     if ( CompareAttributeToString( vAct, "Action",
                                                    "NoMap", "Y" ) != 0 )
                     {
                        GetStringFromAttribute( szTag, zsizeof( szTag ), vAct, "Action", "Tag" );
                        TraceLineS( "Combo Change Event 1 found for Action: ",
                                    szTag );
                        TraceLineS( "   with Mapping not forced off in Window: ",
                                    cpcWndTag );
                     }
                  }

                  nRC = SetCursorNextEntityByInteger( vDialog, "Event",
                                                      "Type", 1, "" );
               }

               nRC = SetCursorFirstEntityByInteger( vDialog, "Event",
                                                    "Type", 5, "" );
               while ( nRC >= zCURSOR_SET )
               {
                  if ( SetEntityCursor( vAct, "Action", 0,
                                        zPOS_FIRST | zQUAL_ENTITYCSR,
                                        vDialog, "EventAct",
                                        0, 0, 0, 0 ) >= zCURSOR_SET )
                  {
                     if ( CompareAttributeToString( vAct, "Action",
                                                    "NoMap", "Y" ) != 0 )
                     {
                        GetStringFromAttribute( szTag, zsizeof( szTag ), vAct, "Action", "Tag" );
                        TraceLineS( "Combo Change Event 5 found for Action: ",
                                    szTag );
                        TraceLineS( "   with Mapping not forced off in Window: ",
                                    cpcWndTag );
                     }
                  }

                  nRC = SetCursorNextEntityByInteger( vDialog, "Event",
                                                      "Type", 5, "" );
               }
            }

            if ( lKey == zCALENDAR_CONTROL )
            {
               nRC = SetCursorFirstEntityByInteger( vDialog, "Event",
                                                    "Type", 1, "" );
               while ( nRC >= zCURSOR_SET )
               {
                  if ( SetEntityCursor( vAct, "Action", 0,
                                        zPOS_FIRST | zQUAL_ENTITYCSR,
                                        vDialog, "EventAct",
                                        0, 0, 0, 0 ) >= zCURSOR_SET )
                  {
                     if ( CompareAttributeToString( vAct, "Action",
                                                    "NoMap", "Y" ) != 0 )
                     {
                        GetStringFromAttribute( szTag, zsizeof( szTag ), vAct, "Action", "Tag" );
                        TraceLineS( "Calendar Change Event found for Action: ",
                                    szTag );
                        TraceLineS( "   with Mapping not forced off in Window: ",
                                    cpcWndTag );
                     }
                  }

                  nRC = SetCursorNextEntityByInteger( vDialog, "Event",
                                                      "Type", 1, "" );
               }
            }

            DropView( vAct );
         }

         if ( (lCheckFlags & zCHECK_OK) && lKey == zPUSHBUTTON_CONTROL )
         {
            GetAddrForAttribute( &pch, vDialog, "Control", "Text" );
            if ( zstrcmp( pch, "&OK" ) == 0 )
            {
               bChange = TRUE;
               SetAttributeFromString( vDialog, "Control", "Text", "OK" );
            }
            else
            if ( zstrcmp( pch, "&Cancel" ) == 0 )
            {
               bChange = TRUE;
               SetAttributeFromString( vDialog, "Control", "Text", "Cancel" );
            }
         }

      // if ( (lCheckFlags & zCHECK_CHANGETAB_EVENT) &&
      //      lKey == zTABCTL_CONTROL )
      // {
      //    if ( SetCursorFirstEntityByInteger( vDialog, "Event", "Type",
      //                                        1, "" ) >= zCURSOR_SET )
      //    {
      //       bChange = TRUE;
      //       SetAttributeFromInteger( vDialog, "Event", "Type", 3 );
      //    }
      // }

      // if ( (lCheckFlags & zCHECK_CHANGE_BREADCRUMB) &&
      //      lKey == zTEXT_CONTROL )
      // {
      //    GetAddrForAttribute( &pch, vDialog, "Control", "Tag" );
      //    GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "Subtype" );
      //
      //    if ( zstrcmp( pch, "BreadCrumb" ) == 0 )
      //    {
      //       if ( (lSubtype & zCONTROL_INVISIBLE) == 0 )
      //       {
      //          bChange = TRUE;
      //          lSubtype |= zCONTROL_INVISIBLE;
      //          SetAttributeFromInteger( vDialog, "Control", "Subtype", lSubtype );
      //       }
      //    }
      // }

      // if ( (lCheckFlags & zCHECK_CHANGE_MOVEINCREMENT) &&
      //      lKey == zEDIT_CONTROL )
      // {
      //    GetAddrForAttribute( &pch, vDialog, "Control", "Tag" );
      //    if ( zstrcmp( pch, "MoveIncrement" ) == 0 )
      //    {
      //       bChange = TRUE;
      //       SetAttributeFromInteger( vDialog, "Control", "SZDLG_X", 16 );
      //    }
      // }

      // if ( (lCheckFlags & zCHECK_CHANGE_NOTETOREVIEWER) &&
      //      lKey == zEDIT_CONTROL )
      // {
      //    GetAddrForAttribute( &pch, vDialog, "Control", "Tag" );
      //    if ( zstrcmp( pch, "NoteToReviewer" ) == 0 )
      //    {
      //       bChange = TRUE;
      //       SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key", zMLE_CONTROL, "" );
      //       ExcludeEntity( vDialog, "ControlDef", zREPOS_NONE );
      //       IncludeSubobjectFromSubobject( vDialog, "ControlDef",
      //                                      vPE, "ControlDef", zPOS_BEFORE );
      //       SetAttributeFromBlob( vDialog, "Control", "CtrlBOI", "", 0 );
      //
      //       nRC = SetCursorFirstEntity( vDialog, "Event", 0 );
      //       while ( nRC == zCURSOR_SET )
      //       {
      //          nRC = DeleteEntity( vDialog, "Event", zREPOS_FIRST );
      //       }
      //    }
      // }

         if ( (lCheckFlags & zCHECK_CHANGE_GROUPBOX_NEW) &&
              lKey == zGROUPBOX_CONTROL )
         {
            zBOOL  bFound = FALSE;
            zSHORT nCnt = 0;

            nRC = SetCursorFirstEntity( vDialog, "CtrlCtrl", 0 );
            while ( nRC == zCURSOR_SET )
            {
               nCnt++;
               GetAddrForAttribute( &pch, vDialog, "CtrlCtrl", "Text" );
               if ( zstrcmp( pch, "New" ) == 0 )
               {
                  bFound = TRUE;
               }

               nRC = SetCursorNextEntity( vDialog, "CtrlCtrl", 0 );
            }

            if ( bFound && nCnt == 2 )
            {
               bChange = TRUE;
               SetAttributeFromString( vDialog, "Control", "CSS_Class", "listgroup" );
               SetAttributeFromInteger( vDialog, "Control", "SZDLG_X", 243 );
               SetAttributeFromInteger( vDialog, "Control", "SZDLG_Y", 20 );
               nRC = SetCursorFirstEntity( vDialog, "CtrlCtrl", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  GetAddrForAttribute( &pch, vDialog, "CtrlCtrl", "Text" );
                  if ( zstrcmp( pch, "New" ) == 0 )
                  {
                     SetAttributeFromString( vDialog, "CtrlCtrl", "CSS_Class", "newbutton" );
                     SetAttributeFromInteger( vDialog, "CtrlCtrl", "PSDLG_X", 171 );
                     SetAttributeFromInteger( vDialog, "CtrlCtrl", "PSDLG_Y", 6 );
                     SetAttributeFromInteger( vDialog, "CtrlCtrl", "SZDLG_X", 39 );
                     SetAttributeFromInteger( vDialog, "CtrlCtrl", "SZDLG_Y", 13 );
                  }
                  else
                  {
                     SetAttributeFromString( vDialog, "CtrlCtrl", "CSS_Class", "listheader" );
                     SetAttributeFromInteger( vDialog, "CtrlCtrl", "PSDLG_X", 5 );
                     SetAttributeFromInteger( vDialog, "CtrlCtrl", "PSDLG_Y", 6 );
                     SetAttributeFromInteger( vDialog, "CtrlCtrl", "SZDLG_X", 77 );
                     SetAttributeFromInteger( vDialog, "CtrlCtrl", "SZDLG_Y", 8 );
                  }

                  nRC = SetCursorNextEntity( vDialog, "CtrlCtrl", 0 );
               }
            }
         }


         if ( lKey == zLISTBOX_CONTROL )
         {
            GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "Subtype" );
            if ( lSubtype & (zLISTBOX_COLUMNHEADERS | zLISTBOX_SORTEDHEADERS) )
            {
               if ( (lCheckFlags & zCHECK_EVENTS) &&
                    SetCursorFirstEntityByInteger( vDialog, "Event", "Type", 12, "" ) < zCURSOR_SET )
               {
                  if ( SetCursorFirstEntityByInteger( vDialog, "Event", "Type", 13, "" ) >= zCURSOR_SET ||
                       SetCursorFirstEntityByInteger( vDialog, "Event", "Type", 14, "" ) >= zCURSOR_SET )
                  {
                     bChange = TRUE;
                     SetAttributeFromInteger( vDialog, "Event", "Type", 12 );
                  }
               }

               /*
               if ( lCheckFlags & zCHECK_READONLY_LISTBOX )
               {
                  GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "ExtendedStyle" );

                  if ( (lSubtype & zCONTROLX_DISABLE_READONLY) == 0 )
                  {
                     bChange = TRUE;
                     lSubtype |= zCONTROLX_DISABLE_READONLY;
                     SetAttributeFromInteger( vDialog, "Control", "ExtendedStyle", lSubtype );
                  }
               }
               */
            }
         }

         if ( ((lCheckFlags & zCHECK_DATETIMEDOMAIN_EDITBOX) ||
               (lCheckFlags & zCHECK_DATEDOMAIN_EDITBOX) ||
               (lCheckFlags & zCHECK_READONLY_EDITBOX)) &&
              lKey == zEDIT_CONTROL )
         {
            if ( lCheckFlags & zCHECK_READONLY_EDITBOX )
            {
               GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "ExtendedStyle" );

               if ( (lSubtype & zCONTROLX_DISABLE_READONLY) == 0 )
               {
                  bChange = TRUE;
                  lSubtype |= zCONTROLX_DISABLE_READONLY;
                  SetAttributeFromInteger( vDialog, "Control",
                                           "ExtendedStyle", lSubtype );
               }
            }

            if ( ((lCheckFlags & zCHECK_DATETIMEDOMAIN_EDITBOX) ||
                  (lCheckFlags & zCHECK_DATEDOMAIN_EDITBOX)) )
            {
               if ( CheckExistenceOfEntity( vDialog, "CtrlMapER_Domain" ) == 0 )
               {
                  GetAddrForAttribute( &pch, vDialog,
                                       "CtrlMapER_Domain", "Name" );
                  if ( ((lCheckFlags & zCHECK_DATEDOMAIN_EDITBOX) &&
                        zstrcmp( "Date", pch ) == 0) ||
                       ((lCheckFlags & zCHECK_DATETIMEDOMAIN_EDITBOX) &&
                        zstrcmp( "DateTime", pch ) == 0) )
                  {
                     if ( SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key",
                                                         zCALENDAR_CONTROL,
                                                         0 ) == 0 )
                     {
                        bChange = TRUE;
                        ExcludeEntity( vDialog, "ControlDef", zREPOS_NONE );
                        IncludeSubobjectFromSubobject( vDialog, "ControlDef",
                                                       vPE, "ControlDef",
                                                       zPOS_BEFORE );
                     }
                  }
               }
            }
         }

         if ( (lCheckFlags & zCHECK_CALENDAR_TO_EDITBOX) &&
              lKey == zCALENDAR_CONTROL )
         {
            if ( SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key",
                                                zEDIT_CONTROL, 0 ) == 0 )
            {
               bChange = TRUE;
               ExcludeEntity( vDialog, "ControlDef", zREPOS_NONE );
               IncludeSubobjectFromSubobject( vDialog, "ControlDef",
                                              vPE, "ControlDef",
                                              zPOS_BEFORE );
            }
         }

#if 1
         if ( (lCheckFlags & zCHECK_CTRL_TYPE) && lKey == zPUSHBUTTON_CONTROL )
         {
            bChange = TRUE;
            SetAttributeFromString( vDialog, "Control", "CSS_Class", "formStylebutton" );
         }
#else
         if ( lCheckFlags & zCHECK_CTRL_TYPE )
         {
            GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "Type" );
            if ( lSubtype )
            {
               zCHAR szMsg[ 256 ];

               GetAddrForAttribute( &pch, vDialog, "Control", "Tag" );
               sprintf_s( szMsg, zsizeof( szMsg ), "(%s) Type for ctrl: \"%s\" is: ",
                         cpcWndTag, pch );
               TraceLineX( szMsg, lSubtype );
            }
         }
#endif
         if ( (lCheckFlags & zCHECK_COMBOBOX_NO_NULL) &&
              (lKey == zCOMBOBOX_CONTROL) )
         {
            GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "Subtype" );
            if ( lSubtype & zCOMBOBOX_NO_NULL )
            {
               zCHAR szMsg[ 256 ];

               GetAddrForAttribute( &pch, vDialog, "Control", "Tag" );
               sprintf_s( szMsg, zsizeof( szMsg ), "(%s) ComboBox No Null for ctrl: \"%s\"",
                         cpcWndTag, pch );
               TraceLineS( szMsg, "" );
            }
         }

         if ( (lCheckFlags & zCHECK_RESIZE_EDIT_CTRLS) &&
              (lKey == zEDIT_CONTROL || lKey == zTEXT_CONTROL) )
         {
            GetIntegerFromAttribute( &lSizeY, vDialog, "Control", "SZDLG_Y" );
            if ( lSizeY == g_lFromHeight || g_lFromHeight == 0 )
            {
               bChange = TRUE;
               SetAttributeFromInteger( vDialog, "Control", "SZDLG_Y", g_lToHeight );
            }
         }
      }

      SetViewToSubobject( vDialog, "CtrlCtrl" );
      if ( CheckMigrateCtrls( vDialog, vPE, lCheckFlags,
                              cpcDlgTag, cpcWndTag, lData ) )
      {
         bChange = TRUE;
      }

      ResetViewFromSubobject( vDialog );
      nRC = SetCursorNextEntity( vDialog, "Control", 0 );
   }

   return( bChange );
}

// z11001Zeidon    TEMP     TZWDLGSO 04/05/00   13:27:08 1.0a
// z10000Zeidon    ACCOUNT  KZWDLGXO 04/05/00   13:27:07 1.0a
zSHORT
fnLocateDialogDate( zPCHAR pchBuffer )
{
   zPCHAR pchColon2;
   zPCHAR pchColon1;
   zPCHAR pchSlash2;
   zPCHAR pchSlash1;
   zLONG  lLth = zstrlen( pchBuffer );
   zLONG  k;

   pchColon2 = zstrchr( pchBuffer, '\n' );
   if ( pchColon2 )
      *pchColon2 = 0;

   pchColon2 = zstrchr( pchBuffer, '\r' );
   if ( pchColon2 )
      *pchColon2 = 0;

   pchColon2 = zstrrchr( pchBuffer, ':' );
   if ( pchColon2 )
   {
      *pchColon2 = 0;
      pchColon1 = zstrrchr( pchBuffer, ':' );
      if ( pchColon1 )
      {
         pchSlash2 = zstrrchr( pchBuffer, '/' );
         if ( pchSlash2 )
         {
            *pchSlash2 = 0;
            pchSlash1 = zstrrchr( pchBuffer, '/' );
            if ( pchSlash1 && pchSlash1 + 3 == pchSlash2 &&
                 pchColon1 + 3 == pchColon2 )
            {
               *pchColon2 = ':';
               *(pchColon2 + 3) = 0;
               k = zatol( pchSlash2 + 1 );
               if ( k > 80 )
               {
                  pchBuffer[ 0 ] = '1';
                  pchBuffer[ 1 ] = '9';
               }
               else
               {
                  pchBuffer[ 0 ] = '2';
                  pchBuffer[ 1 ] = '0';
               }

               strcpy_s( pchBuffer + 2, lLth - 2, pchSlash2 + 1 );
               pchBuffer[ 4 ] = '/';
               strcpy_s( pchBuffer + 5, lLth - 5, pchSlash1 - 2 );
               pchBuffer[ 10 ] = ' ';
               strcpy_s( pchBuffer + 11, lLth - 11, pchColon1 - 2 );
               return( 0 );   // we think we did this correctly
            }
         }
      }
   }

   return( -1 );   // there was some sort of problem
}

zBOOL
ProportionallyResizeWindow( zVIEW vDialog, zLONG lCheckFlags, zLONG lIncr,
                            zCPCHAR cpcDlgTag, zCPCHAR cpcWndTag )
{
   zLONG  lIncrX;
   zLONG  lIncrY;
   zLONG  lPosX;
   zLONG  lPosY;
   zLONG  lSizeX;
   zLONG  lSizeY;
   zSHORT nClientWidth;
   zSHORT nClientHeight;
   zSHORT nClientSizeX;
   zSHORT nClientSizeY;
   zBOOL  bStop = FALSE;

   lIncrX = LOWORD( lIncr );
   if ( lIncrX < 0 )
       lIncrX = -lIncrX;

   lIncrY = HIWORD( lIncr );
   if ( lIncrY < 0 )
       lIncrY = -lIncrY;

   GetIntegerFromAttribute( &lPosX, vDialog, "Window", "PSDLG_X" );
   GetIntegerFromAttribute( &lPosY, vDialog, "Window", "PSDLG_Y" );
   GetIntegerFromAttribute( &lSizeX, vDialog, "Window", "SZDLG_X" );
   GetIntegerFromAttribute( &lSizeY, vDialog, "Window", "SZDLG_Y" );

   nClientWidth = LOWORD( lSizeX );
   nClientHeight = LOWORD( lSizeY );
   nClientSizeX = HIWORD( lSizeX );
   nClientSizeY = HIWORD( lSizeY );
   if ( ((lCheckFlags & zCHECK_INCREMENT_POS_SIZEX) ==
                                                zCHECK_INCREMENT_POS_SIZEX) ||
        ((lCheckFlags & zCHECK_INCREMENT_POS_SIZEY) ==
                                                zCHECK_INCREMENT_POS_SIZEY) )
   {
      if ( (lCheckFlags & zCHECK_INCREMENT_POS_SIZEX) ==
                                                zCHECK_INCREMENT_POS_SIZEX )
      {
         lPosX += lIncrX * lPosX / 100;
         nClientWidth += (zSHORT) (lIncrX * nClientWidth / 100);
         nClientSizeX += (zSHORT) (lIncrX * nClientSizeX / 100);
      }

      if ( (lCheckFlags & zCHECK_INCREMENT_POS_SIZEY) == zCHECK_INCREMENT_POS_SIZEY )
      {
         lPosY += lIncrY * lPosY / 100;
         nClientHeight += (zSHORT) (lIncrY * nClientHeight / 100);
         nClientSizeY += (zSHORT) (lIncrY * nClientSizeY / 100);
      }
   }
   else
   {
      if ( (lCheckFlags & zCHECK_DECREMENT_POS_SIZEX) == zCHECK_DECREMENT_POS_SIZEX )
      {
         lPosX -= lIncrX * lPosX / 100;
         nClientWidth -= (zSHORT) (lIncrX * nClientWidth / 100);
         nClientSizeX -= (zSHORT) (lIncrX * nClientSizeX / 100);
      }

      if ( (lCheckFlags & zCHECK_DECREMENT_POS_SIZEY) == zCHECK_DECREMENT_POS_SIZEY )
      {
         lPosY -= lIncrY * lPosY / 100;
         nClientHeight -= (zSHORT) (lIncrY * nClientHeight / 100);
         nClientSizeY -= (zSHORT) (lIncrY * nClientSizeY / 100);
      }
   }

   lSizeX = MAKELONG( nClientWidth, nClientSizeX );
   lSizeY = MAKELONG( nClientHeight, nClientSizeY );

   if ( nClientWidth <= 0 || nClientHeight <= 0 )
   {
      zCHAR   szWindowTag[ 34 ];
      zCHAR   szMsg[ 512 ];

      GetStringFromAttribute( szWindowTag, zsizeof( szWindowTag ), vDialog, "Window", "Tag" );
      strcpy_s( szMsg, zsizeof( szMsg ), "Window size became equal to zero; Window: " );
      strcat_s( szMsg, zsizeof( szMsg ), szWindowTag );
      strcat_s( szMsg, zsizeof( szMsg ), "\nDo you wish to abort the resize?" );

      if ( MessagePrompt( vDialog, "PE002", "Dialog Maintenance",
                          szMsg, zBEEP, zBUTTONS_YESNO, zRESPONSE_NO,  0 ) != zRESPONSE_YES )
      {
         bStop = TRUE;
      }
   }

   if ( bStop == FALSE )
   {
      SetAttributeFromInteger( vDialog, "Window", "PSDLG_X", lPosX );
      SetAttributeFromInteger( vDialog, "Window", "PSDLG_Y", lPosY );
      SetAttributeFromInteger( vDialog, "Window", "SZDLG_X", lSizeX );
      SetAttributeFromInteger( vDialog, "Window", "SZDLG_Y", lSizeY );

      CheckMigrateCtrls( vDialog, 0, lCheckFlags, cpcDlgTag, cpcWndTag, lIncr );
   }

   return( TRUE ); // change had to occur
}

zOPER_EXPORT zSHORT OPERATION
MigrateDialogs( zVIEW vSubtask )
{
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zPCHAR pchMenuTag;
   zPCHAR pchOptionTag;
   zPCHAR pchActionTag;
   zPCHAR pchTag;
   zPCHAR pch;
   zVIEW  vDialogList;
   zVIEW  vDialog;
   zVIEW  vPE;
   zBOOL  bChange;
   zSHORT nRC;
   zLONG  lCheckFlags = 0;
   zBOOL  bSaveAll = FALSE;
   zBOOL  bSaveAllJSP = FALSE;
   zLONG  lIncr;
   zLONG  k = 0;
   zVIEW  vTaskLPLR = 0;

   if ( GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      MessageSend( vSubtask, "PN00201", "Dialog Maintenance",
                   "Presentation Environment does not exist!\n"
                   "Cannot migrate Dialogs.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( 0 );
   }

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                   "Unable to open Task LPLR!\n"
                   "Cannot migrate Dialogs.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( 0 );
   }

   do // purist's goto
   {

   if ( MessageBox( 0, "Do you want to build JSP for\n"
                       "all Dialogs with name starting with 'w'?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_SAVE_ALL_JSP;
      bSaveAllJSP = TRUE;
      if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
      {
         MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                      "Unable to open Task LPLR!\n"
                      "Cannot migrate Dialogs.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( 0 );
      }

      break; // do only this option
   }
   else
   if ( MessageBox( 0, "Do you want to save all Dialogs?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      bSaveAll = TRUE;
      break; // do only this option
   }
// else
// if ( MessageBox( 0, "Do you want to reset the ChangeTab event\n"
//                     "to the new ChangeTab (Pre MapFromOI) event?",
//                  "Dialog Migration", MB_YESNO ) == IDYES )
// {
//    lCheckFlags |= zCHECK_CHANGETAB_EVENT;
//    break; // do only this option
// }
// else
// if ( MessageBox( 0, "Do you want to reset the BreadCrumb visible flag",
//                  "Dialog Migration", MB_YESNO ) == IDYES )
// {
//    lCheckFlags |= zCHECK_CHANGE_BREADCRUMB;
//    break; // do only this option
// }
   else
   if ( MessageBox( 0, "Do you want to change WebJavaScript?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
   // if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
   //                              "Specify the Change From JavaScript",
   //                              FALSE, g_szChangeFrom,
   //                              zsizeof( g_szChangeFrom ) ) == IDOK )

      OperatorPromptForFile( vSubtask, g_szChangeFrom, 256,
                             "POR Files (*.POR)|*.por|",
                             "POR",
                             zOFN_HIDEREADONLY | zOFN_NOCHANGEDIR |
                             zOFN_FILEMUSTEXIST );
      OperatorPromptForFile( vSubtask, g_szChangeTo, 256,
                             "POR Files (*.POR)|*.por|",
                             "POR",
                             zOFN_HIDEREADONLY | zOFN_NOCHANGEDIR |
                             zOFN_FILEMUSTEXIST );
      if ( g_szChangeFrom[ 0 ] && g_szChangeTo[ 0 ] )
      {
         zLONG lFile;

         lFile = SysOpenFile( vSubtask, g_szChangeFrom, COREFILE_READ );
         SysReadFile( vSubtask, lFile, g_szChangeFrom, 4096 );
         SysCloseFile( vSubtask, lFile, 0 );
         lFile = SysOpenFile( vSubtask, g_szChangeTo, COREFILE_READ );
         SysReadFile( vSubtask, lFile, g_szChangeTo, 4096 );
         SysCloseFile( vSubtask, lFile, 0 );
         if ( g_szChangeFrom[ 0 ] && g_szChangeTo[ 0 ] )
         {
            zCHAR szBuffer[ 16000 ];

            zsprintf( szBuffer, "Do you want to change WebJavaScript from: %s\n\n\n\n     to: %s",
                      g_szChangeFrom, g_szChangeTo );
            if ( MessageBox( 0, szBuffer,  "Dialog Migration", MB_YESNO ) == IDYES )
            {
               lCheckFlags |= zCHECK_EVENTS_WEBJAVASCRIPT;
               bSaveAll = TRUE;
            }
         }
      }

      break; // do only this option
   }
// else
// if ( MessageBox( 0, "Do you want to reset the MoveIncrement width to 16",
//                  "Dialog Migration", MB_YESNO ) == IDYES )
// {
//    lCheckFlags |= zCHECK_CHANGE_MOVEINCREMENT;
//    break; // do only this option
// }
// else
// if ( MessageBox( 0, "Do you want to reset the NoteToReviewer to MLEdit",
//                  "Dialog Migration", MB_YESNO ) == IDYES )
// {
//    lCheckFlags |= zCHECK_CHANGE_NOTETOREVIEWER;
//    break; // do only this option
// }
   else
   if ( MessageBox( 0, "Do you want to reset the New Button in the Groupbox",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_CHANGE_GROUPBOX_NEW;
      break; // do only this option
   }
   else
   if ( MessageBox( 0, "Do you want to report all Menus for\n"
                       "all Dialogs with name starting with 'w'?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_REPORT_WEBMENUS;
      break; // do only this option
   }
   else
   if ( MessageBox( 0, "Do you want to report all Notepages for\n"
                       "all Notebooks in all Dialogs?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_REPORT_TAB_PAGES;
   }
   else
   if ( MessageBox( 0, "Do you want to change mapping for a Dialog?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      zCHAR szMsg[ 256 ];

      lCheckFlags |= zCHECK_CHANGE_MAPPING;
      g_szDlgTag[ 0 ] = 0;
      while ( g_szDlgTag[ 0 ] == 0 )
      {
         OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter Dialog", 0,
                                 g_szDlgTag, zsizeof( g_szDlgTag ) - 1 );
      }

      sprintf_s( szMsg, zsizeof( szMsg ), "Are you sure you want to change mapping for Dialog: %s", g_szDlgTag );
      if ( OperatorPrompt( vSubtask, "Dialog Migration", szMsg, 0,
                           zBUTTONS_OKCANCEL, 0, 0 ) != zRESPONSE_OK )
      {
         return( 0 );
      }

      break; // do only this option
   }
   else
   if ( MessageBox( 0, "Do you want to add a GroupBox for a Dialog for\n"
                       "controls at the root level after a specified GroupBox?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      zCHAR szMsg[ 256 ];

      lCheckFlags |= zCHECK_ADD_GROUPBOX;
      g_szDlgTag[ 0 ] = 0;
      g_szGroupBox[ 0 ] = 0;
      while ( g_szGroupBox[ 0 ] == 0 || g_szDlgTag[ 0 ] == 0 )
      {
         OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter Dialog", 0,
                                 g_szDlgTag, zsizeof( g_szDlgTag ) - 1 );
         OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter GroupBox", 0,
                                 g_szGroupBox, zsizeof( g_szGroupBox ) - 1 );
      }

      sprintf_s( szMsg, zsizeof( szMsg ), "Are you sure you want to add a GroupBox after specified GroupBox: %s\n"
                       "  to Dialog: %s?", g_szGroupBox, g_szDlgTag );
      if ( OperatorPrompt( vSubtask, "Dialog Migration", szMsg, 0,
                           zBUTTONS_OKCANCEL, 0, 0 ) != zRESPONSE_OK )
      {
         return( 0 );
      }

      break; // do only this option
   }
   else
   if ( MessageBox( 0, "Do you want to report\n"
                       "all Events for Dialogs?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_REPORT_EVENTS;
   }
   else
   if ( MessageBox( 0, "Do you want to change WABs\n"
                       "for all Actions for Dialogs?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      zCHAR szWAB[ 256 ];

      lCheckFlags |= zCHECK_CHANGE_WAB;
      g_lFromWAB = g_lToWAB = -1;
      szWAB[ 0 ] = 0;
      while ( g_lFromWAB < 0 || g_lFromWAB > 99 || g_lToWAB < 0 || g_lToWAB > 99 )
      {
         OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter 'From' WAB", 0,
                                 szWAB, zsizeof( szWAB ) - 1 );
         g_lFromWAB = zatol( szWAB );
         OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter 'To' WAB", 0,
                                 szWAB, zsizeof( szWAB ) - 1 );
         g_lToWAB = zatol( szWAB );
      }

      zsprintf( szWAB, "Are you sure you want to convert selected WABs\n"
                       "  from: %s\n  to:   %s?",
                       GetActionString( g_lFromWAB ), GetActionString( g_lToWAB ) );
      if ( OperatorPrompt( vSubtask, "Dialog Migration", szWAB, 0,
                           zBUTTONS_OKCANCEL, 0, 0 ) != zRESPONSE_OK )
      {
         return( 0 );
      }
   }
   else
   if ( MessageBox( 0, "Do you want to save\n"
                       "dialogs based on Date only?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_TIMESTAMP_ONLY;
   }
   else
   if ( MessageBox( 0, "Do you want to report all Notepages for\n"
                       "all Notebooks in all Dialogs?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_REPORT_TAB_PAGES;
   }
   else
   if ( MessageBox( 0, "Do you want to check for the ComboBox No Null\n"
                       "specification for all dialogs?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_COMBOBOX_NO_NULL;
   }
   else
   if ( MessageBox( 0, "Do you want to migrate the PostBuild event\n"
                       "to the SetupWindow event for all dialogs?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      lCheckFlags |= zCHECK_POSTBUILD_SETUP;
      bSaveAll = TRUE;
   }
   else
   if ( MessageBox( 0, "Do you want to resize all dialogs?",
                    "Dialog Migration", MB_YESNO ) == IDYES )
   {
      zCHAR  szBuffer[ 32 ];
      zLONG  lIncrX;
      zLONG  lIncrY;

      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      bSaveAll = TRUE;
      lIncr = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the percentage X increment(+)"
                                     "/decrement(-) ... 0 for no X resize",
                                   FALSE, szBuffer,
                                   zsizeof( szBuffer ) ) == IDOK )
      {
         lIncrX = atol( szBuffer );
      }
      else
         lIncrX = 0;

      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the percentage Y increment(+)"
                                     "/decrement(-) ... 0 for no Y resize",
                                   FALSE, szBuffer,
                                   zsizeof( szBuffer ) ) == IDOK )
      {
         lIncrY = atol( szBuffer );
      }
      else
         lIncrY = 0;

      lIncr = MAKELONG( abs( lIncrX ), abs( lIncrY ) );
      if ( lIncr )
      {
         if ( lIncrX )
         {
            if ( lIncrX > 0 )
               lCheckFlags |= zCHECK_INCREMENT_POS_SIZEX;
            else
               lCheckFlags |= zCHECK_DECREMENT_POS_SIZEX;
         }

         if ( lIncrY )
         {
            if ( lIncrY > 0 )
               lCheckFlags |= zCHECK_INCREMENT_POS_SIZEY;
            else
               lCheckFlags |= zCHECK_DECREMENT_POS_SIZEY;
         }
      }
      else
         return( 0 );
   }
   else
   {
      if ( MessageBox( 0, "Do you want to set ActiveX Properties?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_ACTIVEX_PROPERTIES;
      }

      if ( MessageBox( 0, "Do you want to change EditBoxes\n"
                          "based on the Date Domain?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_DATEDOMAIN_EDITBOX;
      }

      if ( MessageBox( 0, "Do you want to change EditBoxes\n"
                          "files based on the DateTime Domain?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_DATETIMEDOMAIN_EDITBOX;
      }

      if ( MessageBox( 0, "Do you want to change\n"
                          "&OK to OK and &Cancel to Cancel?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_OK;
      }

      if ( MessageBox( 0, "Do you want to check for 'change' events\n"
                          "that do not have mapping forced off\n"
                          "(see Trace Log for listing)?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_CHANGE_EVENTS;
      }

      if ( MessageBox( 0, "Do you want to change\n"
                          "the Right Mouse Button Events for Header Listboxes?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_EVENTS;
      }

      /*
      if ( MessageBox( 0, "Do you want to change\n"
                          "Header Listboxes to Disable as Readonly?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_READONLY_LISTBOX;
      }
      */

      if ( MessageBox( 0, "Do you want to change\n"
                          "Editboxes to Disable as Readonly?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_READONLY_EDITBOX;
      }

      if ( MessageBox( 0, "Do you want to change\n"
                          "All controls to Disable as Readonly?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_READONLY_ALL_CTRLS;
      }

      if ( MessageBox( 0, "Do you want to change all text/edit controls to specified height?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         zCHAR szHeight[ 256 ];

         lCheckFlags |= zCHECK_RESIZE_EDIT_CTRLS;
         szHeight[ 0 ] = 0;
         OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter 'From' height (0 for all)", 0,
                                 szHeight, zsizeof( szHeight ) - 1 );
         g_lFromHeight = zatol( szHeight );
         szHeight[ 0 ] = 0;
         OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter 'To' height", 0,
                                 szHeight, zsizeof( szHeight ) - 1 );
         g_lToHeight = zatol( szHeight );
      }

      if ( MessageBox( 0, "Do you want to change Calendar\n"
                          "controls to EditBox controls?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_CALENDAR_TO_EDITBOX;
      }

#if 1
      if ( MessageBox( 0, "Do you want to set all 'New' buttons class to formStylebutton?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_CTRL_TYPE;
      }
#else
      if ( MessageBox( 0, "Do you want to check\n"
                          "Type of ctrls?",
                       "Dialog Migration", MB_YESNO ) == IDYES )
      {
         lCheckFlags |= zCHECK_CTRL_TYPE;
      }
#endif

   }
   } while( FALSE );  // end of: purist's goto

   if ( bSaveAll )
      lCheckFlags |= zCHECK_SAVE_ALL;

   if ( lCheckFlags == 0 && bSaveAll == FALSE )
      return( 0 );

// RetrieveViewForMetaList( vSubtask, &vDialogList, zSOURCE_DIALOG_META );
   RetrieveViewForMetaList( vSubtask, &vDialogList, zREFER_DIALOG_META );
   nRC = SetCursorFirstEntity( vDialogList, "W_MetaDef", 0 );
   while ( nRC == zCURSOR_SET )
   {
      k++;
      if ( ActivateMetaOI( vSubtask, &vDialog, vDialogList,
                           zSOURCE_DIALOG_META,
                           zSINGLE | zLEVEL_TASK ) == 1 )
      {
         zCHAR szMsg[ 256 ];

         SetNameForView( vDialog, "__CheckDialog", vSubtask, zLEVEL_TASK );
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         bChange = bSaveAll;

         if ( lCheckFlags & zCHECK_SAVE_ALL_JSP )
         {
            if ( pchDlgTag[ 0 ] == 'w' )
            {
               g_bSkipPrompt = TRUE;
               SetNameForView( vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );
               GenerateAllJSPJava( vSubtask );
               g_bSkipPrompt = FALSE;
            }
         }
         else
         if ( lCheckFlags & zCHECK_EVENTS_WEBJAVASCRIPT )
         {
            if ( pchDlgTag[ 0 ] == 'w' )
            {
               zBOOL bWindowChange;

               TraceLineS( "WebJavaScript checking dialog: ", pchDlgTag );

               bChange = FALSE;
               nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  bWindowChange = FALSE;
                  GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
                  nRC = SetCursorFirstEntity( vDialog, "Action", 0 );
                  while ( nRC == zCURSOR_SET )
                  {
                     GetAddrForAttribute( &pchActionTag, vDialog, "Action", "Tag" );
                     GetAddrForAttribute( &pch, vDialog, "Action", "WebJavaScript" );
                     if ( zstrcmp( pch, g_szChangeFrom ) == 0 )
                     {
                        TraceLine( "Changing WebJavaScript for Dialog.Window.Action: %s.%s.%s",
                                   pchDlgTag, pchWndTag, pchActionTag );
                        SetAttributeFromString( vDialog, "Action", "WebJavaScript", g_szChangeTo );
                        bChange = TRUE;
                        bWindowChange = TRUE;
                     }

                     nRC = SetCursorNextEntity( vDialog, "Action", 0 );
                  }

                  if ( bWindowChange )
                  {
                     TraceLine( "WebJavaScript modified for dialog.window: %s.%s", pchDlgTag, pchWndTag );
                  }
                  else
                  {
                     TraceLine( "WebJavaScript NOT modified for dialog.window: %s.%s", pchDlgTag, pchWndTag );
                  }

                  nRC = SetCursorNextEntity( vDialog, "Window", 0 );
                  TraceLineS( "", "" );
               }

               if ( bChange )
               {
                  TraceLineS( "WebJavaScript modified for dialog: ", pchDlgTag );
                  CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
               }
               else
               {
                  TraceLineS( "WebJavaScript NOT modified for dialog: ", pchDlgTag );
               }
            }
         }
         else
         if ( lCheckFlags & zCHECK_REPORT_WEBMENUS )
         {
            if ( pchDlgTag[ 0 ] == 'w' )
            {
               SetNameForView( vDialog, "TZWINDOWL", vSubtask, zLEVEL_TASK );
               nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
                  if ( CheckExistenceOfEntity( vDialog, "DfltMenu" ) == 0 )
                  {
                     GetAddrForAttribute( &pchTag, vDialog, "DfltMenu", "Tag" );
                     TraceLine( "Reporting Menus for Dialog.Window: %s.%s   DfltMenu: %s",
                                pchDlgTag, pchWndTag, pchTag );
                  }
                  else
                  {
                     TraceLine( "Reporting Menus for Dialog.Window: %s.%s",
                                pchDlgTag, pchWndTag );
                  }

                  if ( CheckExistenceOfEntity( vDialog, "ReusableMainWindow" ) == 0 )
                  {
                     GetAddrForAttribute( &pchTag, vDialog, "ReusableMainDialog", "Tag" );
                     GetAddrForAttribute( &pchWndTag, vDialog, "ReusableMainWindow", "Tag" );
                     TraceLine( "   Reusable Main Menu Dialog.Window: %s.%s", pchTag, pchWndTag );
                  }

                  if ( CheckExistenceOfEntity( vDialog, "ReusableSideWindow" ) == 0 )
                  {
                     GetAddrForAttribute( &pchTag, vDialog, "ReusableSideDialog", "Tag" );
                     GetAddrForAttribute( &pchWndTag, vDialog, "ReusableSideWindow", "Tag" );
                     TraceLine( "   Reusable Side Menu Dialog.Window: %s.%s", pchTag, pchWndTag );
                  }

                  nRC = SetCursorFirstEntity( vDialog, "Menu", 0 );
                  while ( nRC == zCURSOR_SET )
                  {
                     GetAddrForAttribute( &pchMenuTag, vDialog, "Menu", "Tag" );
                     nRC = SetCursorFirstEntity( vDialog, "Option", 0 );
                     while ( nRC == zCURSOR_SET )
                     {
                        GetAddrForAttribute( &pchOptionTag, vDialog, "Option", "Tag" );
                        if ( CheckExistenceOfEntity( vDialog, "OptAct" ) == 0 )
                        {
                           GetAddrForAttribute( &pchTag, vDialog, "OptAct", "Tag" );
                           TraceLine( "   Menu.Option.Action: %s.%s.%s", pchMenuTag, pchOptionTag, pchTag );
                        }
                        else
                        {
                           TraceLine( "   Menu.Option.Action: %s.%s", pchMenuTag, pchOptionTag, "<no action>" );
                        }

                        nRC = SetCursorNextEntity( vDialog, "Option", 0 );
                     }

                     nRC = SetCursorNextEntity( vDialog, "Menu", 0 );
                  }

                  nRC = SetCursorNextEntity( vDialog, "Window", 0 );
                  TraceLineS( "", "" );
               }
            }
         }
         else
         if ( lCheckFlags & zCHECK_POSTBUILD_SETUP )
         {
            bChange = FALSE;
            nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
            while ( nRC == zCURSOR_SET )
            {
               if ( SetCursorFirstEntityByInteger( vDialog, "WndEvent",
                                                   "Type", 0x00200000,
                                                   0 ) != zCURSOR_SET &&
                    SetCursorFirstEntityByInteger( vDialog, "WndEvent",
                                                   "Type", 2,
                                                   0 ) == zCURSOR_SET )
               {
                  bChange = TRUE;
                  SetAttributeFromInteger( vDialog, "WndEvent",
                                           "Type", 0x00200000 );
               }

               nRC = SetCursorNextEntity( vDialog, "Window", 0 );
            }

            if ( bChange )
            {
               TraceLineS( "MigrateDialogs modified dialog: ", pchDlgTag );
               CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
            }
         }
         else
         if ( lCheckFlags &
              (zCHECK_INCREMENT_POS_SIZE | zCHECK_DECREMENT_POS_SIZE) )
         {
            if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to save Dialog '" );
               strcat_s( szMsg, zsizeof( szMsg ), pchDlgTag );
               strcat_s( szMsg, zsizeof( szMsg ), "' because it is not checked out" );
               MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                            szMsg,
                          zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
            }
            else
            {
               nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
                  ProportionallyResizeWindow( vDialog, lCheckFlags,
                                              lIncr, pchDlgTag, pchWndTag );
                  nRC = SetCursorNextEntity( vDialog, "Window", 0 );
               }

               TraceLineS( "MigrateDialogs modified dialog: ", pchDlgTag );
               CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
            }
         }
         else
         if ( (lCheckFlags & zCHECK_CHANGE_MAPPING) && zstrcmp( g_szDlgTag, pchDlgTag ) == 0 )
         {
            if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to save Dialog '" );
               strcat_s( szMsg, zsizeof( szMsg ), pchDlgTag );
               strcat_s( szMsg, zsizeof( szMsg ), "' because it is not checked out" );
               MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                            szMsg,
                            zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
            }
            else
            {
               sprintf_s( szMsg, zsizeof( szMsg ), "Checking Dialog: %s for Migration", pchDlgTag );
               nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
               while ( nRC == 0 )
               {
                  zVIEW  vOldViewName;
                  zVIEW  vNewViewName;
                  zCHAR  szOldViewName[ 33 ];
                  zCHAR  szNewViewName[ 33 ];

                  GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );

                  CreateViewFromViewForTask( &vOldViewName, vDialog, 0 );
                  CreateViewFromViewForTask( &vNewViewName, vDialog, 0 );
                  strcpy_s( szOldViewName, zsizeof( szOldViewName ), "mSubLC" );
                  strcpy_s( szNewViewName, zsizeof( szNewViewName ), "mSPLDef" );
                  if ( SetCursorFirstEntityByString( vOldViewName, "ViewObjRef", "Name",
                                                     szOldViewName, 0 ) < zCURSOR_SET )
                  {
                     MessageSend( vSubtask, "", "Change View Mapping",
                                  "Old View Name is not a Registered View in this Dialog.",
                                  zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
                     SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
                     DropView( vOldViewName );
                     DropView( vNewViewName );
                     bChange = FALSE;
                     break;
                  }

                  if ( SetCursorFirstEntityByString( vNewViewName, "ViewObjRef", "Name",
                                                     szNewViewName, 0 ) < zCURSOR_SET )
                  {
                     MessageSend( vSubtask, "", "Change View Mapping",
                                  "New View Name is not a Registered View in this Dialog.",
                                  zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
                     SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
                     DropView( vOldViewName );
                     DropView( vNewViewName );
                     bChange = FALSE;
                     break;
                  }

                  // Go to execute change view mapping for this control and its children.
                  fnChangeMappingViewR( vDialog, vOldViewName, vNewViewName, TRUE, TRUE );
                  bChange = TRUE;

                  DropView( vNewViewName );
                  DropView( vOldViewName );


                  nRC = SetCursorNextEntity( vDialog, "Window", 0 );
               }

               if ( bChange )
               {
                  TraceLineS( "MigrateDialogs modified dialog: ", pchDlgTag );
                  CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
                  SetNameForView( vDialog, "Migrated", vSubtask, zLEVEL_TASK );
                  MessageSend( vSubtask, "PN00202", "Dialog Migration",
                               "Check mapping for view named Migrated",
                               zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
               }
               else
                  TraceLineS( "MigrateDialogs unmodified dialog: ", pchDlgTag );
            }

            return( 0 );
         }
         else
         if ( (lCheckFlags & zCHECK_ADD_GROUPBOX) && zstrcmp( g_szDlgTag, pchDlgTag ) == 0 )
         {
            if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to save Dialog '" );
               strcat_s( szMsg, zsizeof( szMsg ), pchDlgTag );
               strcat_s( szMsg, zsizeof( szMsg ), "' because it is not checked out" );
               MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                            szMsg,
                            zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
            }
            else
            {
               zPCHAR pchCtrlTag;

               sprintf_s( szMsg, zsizeof( szMsg ), "Checking Dialog: %s for Migration", pchDlgTag );
               nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
               while ( nRC == 0 )
               {
                  GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
                  nRC = SetCursorFirstEntity( vDialog, "Control", 0 );
                  while ( nRC == 0 )
                  {
                     GetAddrForAttribute( &pchCtrlTag, vDialog, "Control", "Tag" );
                     if ( zstrcmp( g_szGroupBox, pchCtrlTag ) == 0 )
                     {
                        zCHAR szCtrlTag[ 64 ];
                        zVIEW vGroupBox;
                        zVIEW vNextControl;
                        zLONG lPosX;
                        zLONG lPosY;
                        zLONG lSizeY;
                        zLONG lKey;
                        zLONG lReposX = 0;
                        zLONG lReposY = 0;

                        CreateViewFromView( &vGroupBox, vDialog );
                        CreateViewFromView( &vNextControl, vDialog );

                        CreateMetaEntity( vSubtask, vGroupBox, "Control", zPOS_AFTER );
                        strcpy_s( szCtrlTag, zsizeof( szCtrlTag ), pchWndTag );
                        strcat_s( szCtrlTag, zsizeof( szCtrlTag ), "Section" );
                        SetAttributeFromString( vGroupBox, "Control", "Tag", szCtrlTag );
                        strcpy_s( szCtrlTag, zsizeof( szCtrlTag ), pchWndTag );
                        strcat_s( szCtrlTag, zsizeof( szCtrlTag ), " Section" );
                        SetAttributeFromString( vGroupBox, "Control", "Text", szCtrlTag );
                        SetMatchingAttributesByName( vGroupBox, "Control",
                                                     vDialog, "Control", zSET_NULL );

                        SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key", zGROUPBOX_CONTROL, "" );
                        IncludeSubobjectFromSubobject( vGroupBox, "ControlDef",
                                                       vPE,       "ControlDef", zPOS_AFTER );
                        GetIntegerFromAttribute( &lPosY, vDialog, "Control", "PSDLG_Y" );
                        GetIntegerFromAttribute( &lSizeY, vDialog, "Control", "SZDLG_Y" );
                        lPosY += lSizeY + 5;
                        SetAttributeFromInteger( vGroupBox, "Control", "PSDLG_Y", lPosY );
                        SetViewToSubobject( vGroupBox, "CtrlCtrl" );
                        nRC = SetCursorNextEntity( vDialog, "Control", 0 );
                        nRC = SetCursorNextEntity( vDialog, "Control", 0 );  // both set cursors next intended
                        while ( nRC == 0 )
                        {
                           GetIntegerFromAttribute( &lKey, vDialog, "ControlDef", "Key" );
                           if ( lKey == zGROUPBOX_CONTROL )
                           {
                              break;  // done with this window
                           }

                           GetIntegerFromAttribute( &lPosX, vDialog, "Control", "PSDLG_X" );
                           GetIntegerFromAttribute( &lPosY, vDialog, "Control", "PSDLG_Y" );
                           if ( lReposX == 0 )
                              lReposX = lPosX - 6;

                           if ( lReposY == 0 )
                              lReposY = lPosY - 14;

                           lPosX -= lReposX;
                           lPosY -= lReposY;
                           SetAttributeFromInteger( vDialog, "Control", "PSDLG_X", lPosX );
                           SetAttributeFromInteger( vDialog, "Control", "PSDLG_Y", lPosY );
                           SetViewFromView( vNextControl, vDialog );
                           nRC = SetCursorNextEntity( vNextControl, "Control", 0 );

                           MoveSubobject( vGroupBox, "Control",
                                          vDialog, "Control",
                                          zPOS_AFTER, zREPOS_NEXT );
                           SetViewFromView( vDialog, vNextControl );
                           bChange = TRUE;
                        }

                        break;
                     }

                     nRC = SetCursorNextEntity( vDialog, "Control", 0 );
                  }

                  nRC = SetCursorNextEntity( vDialog, "Window", 0 );
               }

               if ( bChange )
               {
                  TraceLineS( "MigrateDialogs modified dialog: ", pchDlgTag );
                  CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
               }
               else
                  TraceLineS( "MigrateDialogs unmodified dialog: ", pchDlgTag );
            }

            return( 0 );
         }
         else
         if ( lCheckFlags && (lCheckFlags & zCHECK_TIMESTAMP_ONLY) == 0 )
         {
            if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to save Dialog '" );
               strcat_s( szMsg, zsizeof( szMsg ), pchDlgTag );
               strcat_s( szMsg, zsizeof( szMsg ), "' because it is not checked out" );
               MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                            szMsg,
                            zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
            }
            else
            {
               sprintf_s( szMsg, zsizeof( szMsg ), "Checking Dialog: %s for Migration", pchDlgTag );
               TraceLineS( szMsg, "" );
               MB_SetMessage( vSubtask, 1, szMsg );
               OrderEntityForView( vDialog, "Window", "Tag A" );
               nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
                  if ( lCheckFlags & (zCHECK_REPORT_EVENTS | zCHECK_CHANGE_WAB) )
                  {
                     zLONG  lType;

                     nRC = SetCursorFirstEntity( vDialog, "WndEvent", 0 );
                     while ( nRC >= zCURSOR_SET )
                     {
                        GetIntegerFromAttribute( &lType, vDialog, "WndEvent", "Type" );
                        TraceLine( "Event Type: 0x%08x   for Dlg.Wnd: %s.%s",
                                   lType, pchDlgTag, pchWndTag );

                        nRC = SetCursorNextEntity( vDialog, "WndEvent", 0 );
                     }
                  }

                  if ( CheckMigrateCtrls( vDialog, vPE, lCheckFlags,
                                          pchDlgTag, pchWndTag, lIncr ) )
                  {
                     bChange = TRUE;
                  }

                  nRC = SetCursorNextEntity( vDialog, "Window", 0 );
               }

               if ( bChange )
               {
                  TraceLineS( "MigrateDialogs modified dialog: ", pchDlgTag );
                  CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
               }
               else
                  TraceLineS( "MigrateDialogs unmodified dialog: ", pchDlgTag );
            }
         }
         else
         if ( bSaveAll )
         {
            if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to save Dialog '" );
               strcat_s( szMsg, zsizeof( szMsg ), pchDlgTag );
               strcat_s( szMsg, zsizeof( szMsg ), "' because it is not checked out" );
               MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                            szMsg,
                            zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
            }
            else
            {
               sprintf_s( szMsg, zsizeof( szMsg ), "Saving Dialog: %s", pchDlgTag );
               MB_SetMessage( vSubtask, 1, szMsg );
               TraceLineS( "MigrateDialogs (all) dialog: ", pchDlgTag );
               CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
            }
         }
         else
         {
            if ( !ComponentIsCheckedOut( vSubtask, vDialog, zSOURCE_DIALOG_META ) )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to save Dialog '" );
               strcat_s( szMsg, zsizeof( szMsg ), pchDlgTag );
               strcat_s( szMsg, zsizeof( szMsg ), "' because it is not checked out" );
               MessageSend( vSubtask, "PN00202", "Dialog Maintenance",
                            szMsg,
                            zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
            }
            else
            {
               zCHAR  szFileSpec1[ zMAX_FILESPEC_LTH + 1 ];
               zCHAR  szFileSpec2[ zMAX_FILESPEC_LTH + 1 ];
               zPCHAR pch1;
               zPCHAR pch2;
               zLONG  lFilePWD = -1;
               zLONG  lFileXWD = -1;
               zSHORT nLth;

               sprintf_s( szMsg, zsizeof( szMsg ), "Checking Dialog: %s for synchronization", pchDlgTag );
               TraceLineS( szMsg, "" );
               MB_SetMessage( vSubtask, 1, szMsg );
               GetStringFromAttribute( szFileSpec2, zsizeof( szFileSpec2 ), vTaskLPLR, "LPLR", "ExecDir" );
               nLth = (zSHORT) zstrlen( szFileSpec2 );
               if ( nLth && szFileSpec2[ nLth - 1 ] != '\\' )
                  szFileSpec2[ nLth++ ] = '\\';

               strcpy_s( szFileSpec2 + nLth, zsizeof( szFileSpec2 ) - nLth, pchDlgTag );
               strcat_s( szFileSpec2 + nLth, zsizeof( szFileSpec2 ) - nLth, ".xwd" );

               GetStringFromAttribute( szFileSpec1, zsizeof( szFileSpec1 ), vTaskLPLR, "LPLR", "MetaSrcDir" );
               nLth = (zSHORT) zstrlen( szFileSpec1 );
               if ( nLth && szFileSpec1[ nLth - 1 ] != '\\' )
                  szFileSpec1[ nLth++ ] = '\\';

               strcpy_s( szFileSpec1 + nLth, zsizeof( szFileSpec1 ) - nLth, pchDlgTag );
               nLth += (zSHORT) zstrlen( pchDlgTag );
               strcpy_s( szFileSpec1 + nLth, zsizeof( szFileSpec1 ) - nLth, ".pwd" );
               lFilePWD = SysOpenFile( vSubtask, szFileSpec1, COREFILE_READ );
               lFileXWD = SysOpenFile( vSubtask, szFileSpec2, COREFILE_READ );
               strcpy_s( szFileSpec2, zsizeof( szFileSpec2 ), szFileSpec1 );
               strcpy_s( szFileSpec2 + nLth, zsizeof( szFileSpec2 ) - nLth, ".tmp" );
               if ( lFilePWD >= 0 &&
                    (lFileXWD < 0 ||
                     (lFileXWD >= 0 &&
                      SysReadLine( vSubtask, &pch1, lFilePWD ) >= 0 &&
                      SysReadLine( vSubtask, &pch2, lFileXWD ) >= 0 &&
                      fnLocateDialogDate( pch1 ) == 0 &&
                      fnLocateDialogDate( pch2 ) == 0 &&
                      (zstrcmp( pch1, pch2 ) > 0 || bSaveAll))) && // ==> out of sync
                    SysCopyFile( vSubtask, szFileSpec1, szFileSpec2, TRUE ) > 0 )
               {
                  SysCloseFile( vSubtask, lFilePWD, 0 );
                  lFilePWD = -1;
                  if ( lFileXWD >= 0 )
                     SysCloseFile( vSubtask, lFileXWD, 0 );

                  lFileXWD = -1;

                  strcpy_s( szFileSpec2 + nLth, zsizeof( szFileSpec2 ) - nLth, ".pw~" );
                  SysRenameFile( vSubtask, szFileSpec1, szFileSpec2, TRUE );
                  strcpy_s( szFileSpec2 + nLth, zsizeof( szFileSpec2 ) - nLth, ".tmp" );
                  SysRenameFile( vSubtask, szFileSpec2, szFileSpec1, TRUE );

                  TraceLineS( "MigrateDialogs synchronize dialog: ", pchDlgTag );
                  CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
                  strcpy_s( szFileSpec2 + nLth, zsizeof( szFileSpec2 ) - nLth, ".pw~" );
                  SysRenameFile( vSubtask, szFileSpec2, szFileSpec1, TRUE );
               }
               else
               {
                  TraceLineS( "MigrateDialogs unmodified dialog: ", pchDlgTag );
               }

               if ( lFilePWD >= 0 )
                  SysCloseFile( vSubtask, lFilePWD, 0 );

               if ( lFileXWD >= 0 )
                  SysCloseFile( vSubtask, lFileXWD, 0 );
            }
         }

         DropObjectInstance( vDialog );
      }
      else
      {
         TraceLineI( "MigrateDialogs unexpected failure to open dialog in list ",
                     k );
      }

      nRC = SetCursorNextEntity( vDialogList, "W_MetaDef", 0 );
   }

   DropView( vDialogList );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeWndIncrement( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncrX;
   zLONG  lIncrY;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the percentage increment "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lIncrX = atol( szBuffer );
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the percentage increment "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lIncrY = atol( szBuffer );
      lIncr = MAKELONG( abs( lIncrX ), abs( lIncrY ) );
      if ( lIncr )
      {
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
         fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, pchWndTag, 33 );
         lCheckFlags = zCHECK_INCREMENT_POS_SIZEXY;
         ProportionallyResizeWindow( vDialog, lCheckFlags, lIncr, pchDlgTag, pchWndTag );
         fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeWndIncrX( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the X percentage increment "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lCheckFlags = atol( szBuffer );
      if ( lCheckFlags > 0 )
      {
         lIncr = MAKELONG( lCheckFlags, 0 );
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
         fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, pchWndTag, 33 );
         lCheckFlags = zCHECK_INCREMENT_POS_SIZEX;
         ProportionallyResizeWindow( vDialog, lCheckFlags,
                                     lIncr, pchDlgTag, pchWndTag );
         fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh,
                                  0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeWndIncrY( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the Y percentage increment "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lCheckFlags = atol( szBuffer );
      if ( lCheckFlags > 0 )
      {
         lIncr = MAKELONG( 0, lCheckFlags );
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
         fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, pchWndTag, 33 );
         lCheckFlags = zCHECK_INCREMENT_POS_SIZEY;
         ProportionallyResizeWindow( vDialog, lCheckFlags,
                                     lIncr, pchDlgTag, pchWndTag );
         fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeWndDecrement( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncrX;
   zLONG  lIncrY;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the percentage decrement "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lIncrX = atol( szBuffer );
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the percentage decrement "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lIncrY = atol( szBuffer );
      lIncr = MAKELONG( abs( lIncrX ), abs( lIncrY ) );
      if ( lIncr )
      {
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
         fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, pchWndTag, 33 );
         lCheckFlags = zCHECK_DECREMENT_POS_SIZEXY;
         ProportionallyResizeWindow( vDialog, lCheckFlags, lIncr, pchDlgTag, pchWndTag );
         fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeWndDecrX( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the X percentage decrement "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lCheckFlags = atol( szBuffer );
      if ( lCheckFlags > 0 )
      {
         lIncr = MAKELONG( lCheckFlags, 0 );
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
         fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, pchWndTag, 33 );
         lCheckFlags = zCHECK_DECREMENT_POS_SIZEX;
         ProportionallyResizeWindow( vDialog, lCheckFlags,
                                     lIncr, pchDlgTag, pchWndTag );
         fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh,
                                  0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeWndDecrY( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the Y percentage decrement "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lCheckFlags = atol( szBuffer );
      if ( lCheckFlags > 0 )
      {
         lIncr = MAKELONG( 0, lCheckFlags );
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
         fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, pchWndTag, 33 );
         lCheckFlags = zCHECK_DECREMENT_POS_SIZEY;
         ProportionallyResizeWindow( vDialog, lCheckFlags, lIncr, pchDlgTag, pchWndTag );
         fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeDlgIncrement( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncrX;
   zLONG  lIncrY;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the percentage increment "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lIncrX = atol( szBuffer );
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the percentage increment "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lIncrY = atol( szBuffer );
      lIncr = MAKELONG( abs( lIncrX ), abs( lIncrY ) );
      if ( lIncr )
      {
         zSHORT nRC;

         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         CreateViewFromViewForTask( &vDialog, vDialog, 0 );

         lCheckFlags = zCHECK_INCREMENT_POS_SIZEXY;
         nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
            GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
            ProportionallyResizeWindow( vDialog, lCheckFlags,
                                        lIncr, pchDlgTag, pchWndTag );
            nRC = SetCursorNextEntity( vDialog, "Window", 0 );
         }

         fnPainterCall( zMSG_REPAINTALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeDlgIncrX( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the X percentage increment "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lCheckFlags = atol( szBuffer );
      if ( lCheckFlags > 0 )
      {
         zSHORT nRC;

         lIncr = MAKELONG( lCheckFlags, 0 );
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         CreateViewFromViewForTask( &vDialog, vDialog, 0 );

         lCheckFlags = zCHECK_INCREMENT_POS_SIZEX;
         nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
            GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
            ProportionallyResizeWindow( vDialog, lCheckFlags,
                                        lIncr, pchDlgTag, pchWndTag );
            nRC = SetCursorNextEntity( vDialog, "Window", 0 );
         }

         fnPainterCall( zMSG_REPAINTALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeDlgIncrY( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the Y percentage increment "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lCheckFlags = atol( szBuffer );
      if ( lCheckFlags > 0 )
      {
         zSHORT nRC;

         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         lIncr = MAKELONG( 0, lCheckFlags );
         CreateViewFromViewForTask( &vDialog, vDialog, 0 );

         lCheckFlags = zCHECK_INCREMENT_POS_SIZEY;
         nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
            GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
            ProportionallyResizeWindow( vDialog, lCheckFlags,
                                        lIncr, pchDlgTag, pchWndTag );
            nRC = SetCursorNextEntity( vDialog, "Window", 0 );
         }

         fnPainterCall( zMSG_REPAINTALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeDlgDecrement( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncrX;
   zLONG  lIncrY;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the X percentage decrement "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lIncrX = atol( szBuffer );
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the Y percentage decrement "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lIncrY = atol( szBuffer );
      lIncr = MAKELONG( abs( lIncrX ), abs( lIncrY ) );
      if ( lIncr )
      {
         zSHORT nRC;

         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         CreateViewFromViewForTask( &vDialog, vDialog, 0 );
         lCheckFlags = zCHECK_DECREMENT_POS_SIZEXY;
         nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
            GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
            ProportionallyResizeWindow( vDialog, lCheckFlags,
                                        lIncr, pchDlgTag, pchWndTag );
            nRC = SetCursorNextEntity( vDialog, "Window", 0 );
         }

         fnPainterCall( zMSG_REPAINTALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeDlgDecrX( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the X percentage decrement "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lCheckFlags = atol( szBuffer );
      if ( lCheckFlags > 0 )
      {
         zSHORT nRC;

         lIncr = MAKELONG( lCheckFlags, 0 );
         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         CreateViewFromViewForTask( &vDialog, vDialog, 0 );

         lCheckFlags = zCHECK_DECREMENT_POS_SIZEX;
         nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
            GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
            ProportionallyResizeWindow( vDialog, lCheckFlags,
                                        lIncr, pchDlgTag, pchWndTag );
            nRC = SetCursorNextEntity( vDialog, "Window", 0 );
         }

         fnPainterCall( zMSG_REPAINTALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ProportionallyResizeDlgDecrY( zVIEW vSubtask )
{
   zCHAR  szBuffer[ 32 ];
   zVIEW  vDialog;
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zLONG  lCheckFlags;
   zLONG  lIncr;

   if ( GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK ) > 0 )
   {
      szBuffer[ 0 ] = '2';
      szBuffer[ 1 ] = '4';
      szBuffer[ 2 ] = 0;
      if ( OperatorPromptForInput( vSubtask, "Dialog Migration",
                                   "Specify the Y percentage decrement "
                                      "... 0 to stop resize", FALSE,
                                   szBuffer, zsizeof( szBuffer ) ) != IDOK )
      {
         return( 0 );
      }

      lCheckFlags = atol( szBuffer );
      if ( lCheckFlags > 0 )
      {
         zSHORT nRC;

         GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );
         lIncr = MAKELONG( 0, lCheckFlags );
         CreateViewFromViewForTask( &vDialog, vDialog, 0 );

         lCheckFlags = zCHECK_DECREMENT_POS_SIZEY;
         nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
            GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
            ProportionallyResizeWindow( vDialog, lCheckFlags,
                                        lIncr, pchDlgTag, pchWndTag );
            nRC = SetCursorNextEntity( vDialog, "Window", 0 );
         }

         fnPainterCall( zMSG_REPAINTALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindowWithRefresh, 0, 0 );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void
fnChangeCtrlMapView( zVIEW vControl,
                     zVIEW vNewViewName,
                     zLONG lOriginalViewZKey )
{
// zCHAR  szEntity[ 33 ];
// zCHAR  szAttribute[ 33 ];
// zLONG  lZKeyEntity;
// zLONG  lZKeyAttribute;
   zSHORT nRC;

   for ( nRC = SetCursorFirstEntity( vControl, "CtrlMap", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vControl, "CtrlMap", "" ) )
   {
      if ( CheckExistenceOfEntity( vControl, "CtrlMapView" ) == 0 )
      {
         // Check if the CtrlMapView we are on is the same as the view for which
         // we're to make the change. If not skip.
         if ( CompareAttributeToInteger( vControl, "CtrlMapView", "ZKey",
                                         lOriginalViewZKey ) == 0 )
         {

            if ( CompareAttributeToInteger( vNewViewName, "ViewObjRef", "ZKey",
                                            lOriginalViewZKey ) != 0 )
            {
#if 0
               // Set up to reset the Entity and Attribute since the ZKeys differ
               // from one ViewObjRef to another.
               if ( CheckExistenceOfEntity( vControl, "CtrlMapLOD_Attribute" ) == 0 )
               {
                  GetIntegerFromAttribute( &lZKeyEntity, vControl, "CtrlMapRelatedEntity", "ZKey" );
                  GetStringForAttribute( szEntity, vControl, "CtrlMapRelatedEntity", "Name" );
                  GetIntegerFromAttribute( &lZKeyAttribute, vControl, "CtrlMapLOD_Attribute", "ZKey" );
                  GetStringForAttribute( szAttribute, vControl, "CtrlMapLOD_Attribute", "Name" );
               }
               else
               {
                  szEntity[ 0 ] = 0;
                  szAttribute[ 0 ] = 0;
                  lZKeyEntity = 0;
                  lZKeyAttribute = 0;
               }

#endif

               ExcludeEntity( vControl, "CtrlMapView", zREPOS_NONE );
               IncludeSubobjectFromSubobject( vControl,  "CtrlMapView",
                                              vNewViewName, "ViewObjRef", zPOS_AFTER );

#if 0
               // When we do this, we need to reset the Entity and Attribute since the
               // ZKeys differ from one ViewObjRef to another.

               IncludeSubobjectFromSubobject( vTgtC, "CtrlMapLOD_Attribute",
                                              vLOD, "LOD_Attribute", zPOS_AFTER );

               // Select current mapping in LOD.
               if ( CheckExistenceOfEntity( vDialogC, "CtrlMapLOD_Attribute" ) == zCURSOR_SET )
               {
                  GetIntegerFromAttribute( &lZKey, vDialogC,
                                           "CtrlMapRelatedEntity", "ZKey" );
                  if ( SetCursorFirstEntityByInteger( vLOD, "LOD_Entity",
                                                      "ZKey", lZKey, "" ) != zCURSOR_SET )
                  {

                     GetAddrForAttribute( &pchEntity, vDialogC, "CtrlMapRelatedEntity", "Name" );
                     SetCursorFirstEntityByString( vLOD, "LOD_Entity",
                                                   "Name", pchEntity, "" );
                     TraceLineS( "LOD Entity not located by ZKey: ", pchEntity );
                  }

                  SetSelectStateOfEntityForSet( vLOD, "LOD_Entity", 1, 1 );
                  GetIntegerFromAttribute( &lZKey, vDialogC,
                                           "CtrlMapLOD_Attribute", "ZKey" );
                  if ( SetCursorFirstEntityByInteger( vLOD, "LOD_Attribute",
                                                      "ZKey", lZKey, "" ) != zCURSOR_SET )
                  {

                     GetAddrForAttribute( &pchAttribute, vDialogC, "CtrlMapER_Attribute", "Name" );
                     SetCursorFirstEntityByString( vLOD, "ER_Attribute",
                                                   "Name", pchAttribute, "LOD_Entity" );
                     TraceLineS( "LOD Attribute not located by ZKey: ", pchAttribute );
                  }

                  SetSelectStateOfEntityForSet( vLOD, "LOD_Attribute", 1, 1 );
               }
#endif

            }
         }
      }
   }
}

zSHORT
fnChangeMappingViewR( zVIEW vDialog,
                      zVIEW vOldViewName,
                      zVIEW vNewViewName,
                      zBOOL bAllCtrlsAtLevel,
                      zBOOL bRecurse )
{
   zLONG  lOriginalViewZKey;
   zSHORT nRC;

   // Get Original View ID.
   GetIntegerFromAttribute( &lOriginalViewZKey, vOldViewName, "ViewObjRef", "ZKey" );

   // Loop through all Controls at this level.
   if ( bAllCtrlsAtLevel )
      nRC = SetCursorFirstEntity( vDialog, "Control", "" );
   else
      nRC = CheckExistenceOfEntity( vDialog, "Control" );

   while ( nRC >= zCURSOR_SET )
   {
      // Change mapping view of each view that is identified by original view ID.
      fnChangeCtrlMapView( vDialog, vNewViewName, lOriginalViewZKey );

      // Process any recursive sub controls.
      if ( bRecurse && CheckExistenceOfEntity( vDialog, "CtrlCtrl" ) == 0 )
      {
         SetViewToSubobject( vDialog, "CtrlCtrl" );
         fnChangeMappingViewR( vDialog, vOldViewName, vNewViewName, TRUE, TRUE );
         ResetViewFromSubobject( vDialog );
      }

      if ( bAllCtrlsAtLevel )
         nRC = SetCursorNextEntity( vDialog, "Control", "" );
      else
         nRC = -1;
   }

   return( 0 );
}

// Recursive function to go through child controls.  vControl is positioned
// on the original Ctrl, vWnd is positioned on the Ctrl in a different window.
void
fnSetPsSzClassR( zVIEW vWnd, zVIEW vControl, zCPCHAR cpcDlg, zCPCHAR cpcWnd,
                 zBOOL bRecurse, zBOOL bSiblings )
{
   zPCHAR pchCtrlTag;
   zPCHAR pchCtrlCtrlTag;
   zPCHAR pchClass;
   zLONG  lPosX;
   zLONG  lPosY;
   zLONG  lSizeX;
   zLONG  lSizeY;
   zSHORT nRC;

   // Get the Tag of currently selected control.
   GetAddrForAttribute( &pchCtrlTag, vControl, "Control", "Tag" );

   GetIntegerFromAttribute( &lPosX, vControl, "Control", "PSDLG_X" );
   GetIntegerFromAttribute( &lPosY, vControl, "Control", "PSDLG_Y" );
   GetIntegerFromAttribute( &lSizeX, vControl, "Control", "SZDLG_X" );
   GetIntegerFromAttribute( &lSizeY, vControl, "Control", "SZDLG_Y" );
   GetAddrForAttribute( &pchClass, vControl, "Control", "CSS_Class" );
   SetAttributeFromInteger( vWnd, "Control", "PSDLG_X", lPosX );
   SetAttributeFromInteger( vWnd, "Control", "PSDLG_Y", lPosY );
   SetAttributeFromInteger( vWnd, "Control", "SZDLG_X", lSizeX );
   SetAttributeFromInteger( vWnd, "Control", "SZDLG_Y", lSizeY );
   SetAttributeFromString( vWnd, "Control", "CSS_Class", pchClass );

// TraceLine( "Setting Dlg.Wnd.Ctrl: %s.%s.%s  Pos/Size: %d,%d/%d,%d  Class: %s",
//            cpcDlg, cpcWnd, pchCtrlTag,
//            lPosX, lPosY, lSizeX, lSizeY, pchClass );

   if ( bRecurse && CheckExistenceOfEntity( vControl, "CtrlCtrl" ) == 0 )
   {
      SetViewToSubobject( vControl, "CtrlCtrl" );
      SetViewToSubobject( vWnd, "CtrlCtrl" );

      GetAddrForAttribute( &pchCtrlCtrlTag, vControl, "Control", "Tag" );
      if ( SetCursorFirstEntityByString( vWnd, "Control",
                                         "Tag", pchCtrlCtrlTag, 0 ) >= zCURSOR_SET )
      {
         // Recurse through child controls and siblings.
         fnSetPsSzClassR( vWnd, vControl, cpcDlg, cpcWnd, TRUE, TRUE );
      }

      ResetViewFromSubobject( vWnd );
      ResetViewFromSubobject( vControl );
   }

   if ( bSiblings )
   {
      nRC = SetCursorFirstEntity( vControl, "Control", 0 );
      while ( nRC == 0 )
      {
         // Don't process the original Ctrl.
         GetAddrForAttribute( &pchCtrlCtrlTag, vControl, "Control", "Tag" );
         if ( zstrcmp( pchCtrlTag, pchCtrlCtrlTag ) != 0 )
         {
            // We've got to make sure the vWnd has a Ctrl with the same Tag
            // as the Ctrl currently with cursor position in vControl.
            if ( SetCursorFirstEntityByString( vWnd, "Control",
                                               "Tag", pchCtrlCtrlTag, 0 ) >= zCURSOR_SET )
            {            // Recurse through child controls but not siblings.
               fnSetPsSzClassR( vWnd, vControl, cpcDlg, cpcWnd, TRUE, FALSE );
            }
         }

         nRC = SetCursorNextEntity( vControl, "Control", 0 );
      }

      SetCursorFirstEntityByString( vControl, "Control",
                                    "Tag", pchCtrlTag, 0 );
   }
}

void
fnDisplayControlsR( zVIEW vDialog, zCPCHAR cpcDlg, zCPCHAR cpcWnd )
{
   zPCHAR pchCtrlTag;
   zPCHAR pchClass;
   zLONG  lPosX;
   zLONG  lPosY;
   zLONG  lSizeX;
   zLONG  lSizeY;
   zSHORT nRC;

   // Get the Tag of currently selected control.
   GetAddrForAttribute( &pchCtrlTag, vDialog, "Control", "Tag" );

   GetIntegerFromAttribute( &lPosX, vDialog, "Control", "PSDLG_X" );
   GetIntegerFromAttribute( &lPosY, vDialog, "Control", "PSDLG_Y" );
   GetIntegerFromAttribute( &lSizeX, vDialog, "Control", "SZDLG_X" );
   GetIntegerFromAttribute( &lSizeY, vDialog, "Control", "SZDLG_Y" );
   GetAddrForAttribute( &pchClass, vDialog, "Control", "CSS_Class" );
   TraceLine( "Dlg.Wnd.Ctrl: %s.%s.%s  Pos/Size: %d,%d/%d,%d  Class: %s",
              cpcDlg, cpcWnd, pchCtrlTag, lPosX, lPosY, lSizeX, lSizeY, pchClass );

   if ( CheckExistenceOfEntity( vDialog, "CtrlCtrl" ) == 0 )
   {
      SetViewToSubobject( vDialog, "CtrlCtrl" );

      nRC = SetCursorFirstEntity( vDialog, "Control", 0 );
      while ( nRC == 0 )
      {
         fnDisplayControlsR( vDialog, cpcDlg, cpcWnd );
         nRC = SetCursorNextEntity( vDialog, "Control", 0 );
      }

      ResetViewFromSubobject( vDialog );
   }
}

void
DisplayControls( zVIEW vDialog, zCPCHAR cpcText1, zCPCHAR cpcText2 )
{
   zPCHAR pchDlgTag;
   zPCHAR pchWndTag;
   zSHORT nRC;

   TraceLineS( "", "" );
   TraceLineS( cpcText1, cpcText2 );

   CreateViewFromView( &vDialog, vDialog );
   while ( ResetViewFromSubobject( vDialog ) == 0 )
   {
   }

   // Get the Tag of current dialog.
   GetAddrForAttribute( &pchDlgTag, vDialog, "Dialog", "Tag" );

   nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
   while ( nRC == 0 )
   {
      // Get the Tag of current window.
      GetAddrForAttribute( &pchWndTag, vDialog, "Window", "Tag" );
      nRC = SetCursorFirstEntity( vDialog, "Control", 0 );
      while ( nRC == 0 )
      {
         fnDisplayControlsR( vDialog, pchDlgTag, pchWndTag );
         nRC = SetCursorNextEntity( vDialog, "Control", 0 );
      }
      nRC = SetCursorNextEntity( vDialog, "Window", 0 );
   }

   DropView( vDialog );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    PainterSelectedCallback
//
// PURPOSE:  This function is the function called by the painter for each
//           selected control.
//
//           lType - Reason for callback:
//                    0x00000001 - change View
//                    0x00000002 - change Entity
//                    0x00000004 - change Attribute
//                    0x00000010 - change Tag (in place)
//                    0x00000020 - change Text (in place)
//                    0x00000040 - change Font Face Name (in place)
//                    0x00000080 - change Font Size (in place)
//                    0x00000100 - change Pos of Control with same ...
//                    0x00000200 - change Size of Control with same ...
//                    0x00000400 - change Class of Control with same ...
//                    0x00000700 - change Pos/Size/Class of Control with same
//                                 Tag for all Windows for Dialog
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
PainterSelectedCallback( zVIEW   vSubtask, // view to painter window
                         zVIEW   vDialog,
                         zVIEW   vLOD,
                         zVIEW   vControl, // do not reposition this view
                         zPVOID  pCtrl,    // painter C++ pointer to ctrl
                         zLONG   lType,    // type of call
                         zPVOID  pvData,   // this data can get changed
                         zLONG   lFlags )
{
   zVIEW  vOldName;
   zVIEW  vNewName;
// zLONG  lRC;

   if ( MiGetUpdateForView( vDialog ) == 0 )
      return( 0 );

   if ( lType & 0x00000007 ) // change View and/or Entity and/or Attribute
   {
      zPCHAR pchDotEntity = 0;
      zPCHAR pchDotAttribute = 0;
      zPCHAR pchDot;
      zPCHAR pchNewViewName = (zPCHAR) pvData;
      zPCHAR pchEntityName = 0;
      zPCHAR pchAttribName = 0;
      zLONG  lZKey;

      pchDot = zstrchr( pchNewViewName, '.' );
      if ( pchDot )
      {
         pchDotEntity = pchDot;
         *pchDot++ = 0;
         pchEntityName = pchDot;
         pchDot = zstrchr( pchEntityName, '.' );
         if ( pchDot )
         {
            pchDotAttribute = pchDot;
            *pchDot++ = 0;
            pchAttribName = pchDot;
         }
      }

      if ( pchNewViewName && *pchNewViewName && (lType & 0x00000001) ) // change View
      {
         CreateViewFromView( &vOldName, vDialog );
         if ( CheckExistenceOfEntity( vControl, "CtrlMapView" ) == 0 )
            GetIntegerFromAttribute( &lZKey, vControl, "CtrlMapView", "ZKey" );
         else
            lZKey = 0;

         CreateViewFromView( &vNewName, vDialog );
         if ( (lZKey == 0 ||
               SetCursorFirstEntityByInteger( vOldName, "ViewObjRef", "ZKey",
                                              lZKey, 0 ) >= zCURSOR_SET) &&
              SetCursorFirstEntityByString( vNewName, "ViewObjRef", "Name",
                                            pchNewViewName, 0 ) >= zCURSOR_SET )
         {
            // Go to execute change view mapping at each Control level.
            fnChangeMappingViewR( vControl, vOldName, vNewName, FALSE, TRUE );
         }

         DropView( vOldName );
         DropView( vNewName );
      }

      if ( pchAttribName && *pchAttribName && (lType & 0x00000004) ) // change Attribute
      {
         zBOOL bInclude = TRUE;

         // We assume position has already been established on correct LOD_Entity.
         if ( CheckExistenceOfEntity( vControl, "CtrlMapLOD_Attribute" ) == 0 )
         {
            if ( CompareAttributeToAttribute( vControl, "CtrlMapLOD_Attribute", "ZKey",
                                              vLOD, "LOD_Attribute", "ZKey" ) == 0 )
            {
               bInclude = FALSE;
            }
            else
            {
               ExcludeEntity( vControl, "CtrlMapLOD_Attribute", zREPOS_NONE );
            }
         }

         if ( bInclude )
         {
            IncludeSubobjectFromSubobject( vControl, "CtrlMapLOD_Attribute",
                                           vLOD, "LOD_Attribute", zPOS_AFTER );
         // IncludeSubobjectFromSubobject( vControl, "CtrlMapRelatedEntity",
         //                                vLOD, "LOD_Entity", zPOS_AFTER );
         }
      }
      else
      if ( pchEntityName && *pchEntityName && (lType & 0x00000002) ) // change Entity
      {
         zBOOL bInclude = TRUE;

         // We assume position has already been established on correct LOD_Entity.
         if ( CheckExistenceOfEntity( vControl, "CtrlMapLOD_Entity" ) == 0 )
         {
            if ( CompareAttributeToAttribute( vControl, "CtrlMapLOD_Entity", "ZKey",
                                              vLOD, "LOD_Entity", "ZKey" ) == 0 )
            {
               bInclude = FALSE;
            }
            else
            {
               ExcludeEntity( vControl, "CtrlMapLOD_Entity", zREPOS_NONE );
            }
         }

         if ( bInclude )
         {
            IncludeSubobjectFromSubobject( vControl, "CtrlMapLOD_Entity",
                                           vLOD, "LOD_Entity", zPOS_AFTER );
         }
      }

      if ( pchDotEntity )
         *pchDotEntity = '.';

      if ( pchDotAttribute )
         *pchDotAttribute = '.';
   }
   else
   if ( lType & 0x00000070 ) // change Tag, Text, Font
   {
      if ( lType & 0x00000010 )
         ShowInplaceControlOverCtrl( vSubtask, vControl, pCtrl, "InplaceTag" );
      else
      if ( lType & 0x00000020 )
         ShowInplaceControlOverCtrl( vSubtask, vControl, pCtrl, "InplaceText" );
      else
      if ( lType & 0x00000040 )
         ShowInplaceControlOverCtrl( vSubtask, vControl, pCtrl, "InplaceFontFace" );
      else
      if ( lType & 0x00000080 )
         ShowInplaceControlOverCtrl( vSubtask, vControl, pCtrl, "InplaceFontSize" );
   }
   else
   if ( lType & 0x00000700 ) // change Position, Size, Class for all Controls
   {                         // with the same Tag for all Windows in Dialog
      zVIEW  vWnd;
      zPCHAR pchDlg;
      zPCHAR pchWnd;
      zPCHAR pchCtrlTag;
      zPCHAR pchWndCurr;
      zSHORT nRC;

      // Get the Tag of currently selected control.
      GetAddrForAttribute( &pchCtrlTag, vControl, "Control", "Tag" );

      // So we can modify the Dialog and not worry about the consequences.
      CreateViewFromViewForTask( &vWnd, vControl, 0 );
      while ( ResetViewFromSubobject( vWnd ) == 0 )
      {
      }

      CreateViewFromViewForTask( &vControl, vControl, 0 );  // protect original vControl
      GetAddrForAttribute( &pchDlg, vWnd, "Dialog", "Tag" );
      GetAddrForAttribute( &pchWnd, vWnd, "Window", "Tag" );

      nRC = SetCursorFirstEntity( vWnd, "Window", 0 );
      while ( nRC == zCURSOR_SET )
      {
         GetAddrForAttribute( &pchWndCurr, vWnd, "Window", "Tag" );
         if ( zstrcmp( pchWnd, pchWndCurr ) != 0 )
         {
            nRC = SetEntityCursor( vWnd, "Control", "Tag",
                                   zPOS_FIRST | zQUAL_STRING | zRECURS,
                                   pchCtrlTag, 0, 0, 0, "Window", 0 );
            if ( nRC > zCURSOR_UNCHANGED )
            {
               // Recurse through child controls but not siblings.
               fnSetPsSzClassR( vWnd, vControl, pchDlg, pchWndCurr, TRUE, FALSE );
            }
         }

         // The above SetEntityCursor could have put us down in a subobject.
         while ( ResetViewFromSubobject( vWnd ) == 0 )
         {
         }

         nRC = SetCursorNextEntity( vWnd, "Window", 0 );
      }

      DropView( vWnd );
      DropView( vControl );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
SetCtrlSizPosClasToSelectThruDlg( zVIEW vSubtask )
{
   zCHAR  szMsg[ 256 ];
   zPCHAR pchDlg;
   zVIEW  vDialog;
   zLONG  lRC = -1;

// GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vDialog, "vDialog", vSubtask, zLEVEL_TASK );
   if ( vDialog )
   {
      // Prompt operator to ensure ALL windows are to be generated.
      GetAddrForAttribute( &pchDlg, vDialog, "Dialog", "Tag" );
      sprintf_s( szMsg, zsizeof( szMsg ), "Reset Control Pos/Size/Class for ALL Windows in Dialog: %s?", pchDlg );
      if ( OperatorPrompt( vSubtask, "Reset Pos/Size/Class",
                           szMsg, 1, zBUTTONS_YESNO,
                           zRESPONSE_YES, zICON_QUESTION ) == zRESPONSE_NO )
      {
         return( -1 );
      }

   // DisplayControls( vDialog, "Changing Dialog BEFORE UPDATE ALL:", pchDlg );
      fnPainterCall( zMSG_UPDATEALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );

   // DisplayControls( vDialog, "Changing Dialog: ", pchDlg );
      lRC = CallPainterForSelectedControls( vSubtask, "tzpntrad",
                                            "PainterSelectedCallback",
                                            vDialog, 0, 0x00000700, 0, 0 );

   // DisplayControls( vDialog, "Changed Dialog: ", pchDlg );
      fnPainterCall( zMSG_REPAINTALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
   // DisplayControls( vDialog, "Changed Dialog after REPAINT ALL: ", pchDlg );
   }

   return( (zSHORT) lRC );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
UpdateTagInPlace( zVIEW vSubtask )
{
   zVIEW vDialog;
   zLONG lRC = -1;

   GetViewByName( &vDialog, "vDialog", vSubtask, zLEVEL_TASK );
   if ( vDialog )
   {
      zCHAR szOptionTag[ 65 ];
      zPCHAR pch;

      GetLastCommandTag( vSubtask, szOptionTag );
      TraceLineS( "UpdateTagInPlace Command: ", szOptionTag );
      pch = zstrrchr( szOptionTag, '.' );
      if ( pch )
         *pch = 0;

      lRC = CallPainterForSelectedControls( vSubtask, "tzpntrad",
                                            "PainterSelectedCallback",
                                            vDialog, 0, 0x00000010,
                                            szOptionTag, 0 );
   }

   return( (zSHORT) lRC );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
UpdateTextInPlace( zVIEW vSubtask )
{
   zVIEW vDialog;
   zLONG lRC = -1;

   GetViewByName( &vDialog, "vDialog", vSubtask, zLEVEL_TASK );
   if ( vDialog )
   {
      zCHAR szOptionTag[ 65 ];
      zPCHAR pch;

      GetLastCommandTag( vSubtask, szOptionTag );
      TraceLineS( "UpdateTextInPlace Command: ", szOptionTag );
      pch = zstrrchr( szOptionTag, '.' );
      if ( pch )
         *pch = 0;

      lRC = CallPainterForSelectedControls( vSubtask, "tzpntrad",
                                            "PainterSelectedCallback",
                                            vDialog, 0, 0x00000020, 0, 0 );
   }

   return( (zSHORT) lRC );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
UpdateFontFaceNameInPlace( zVIEW vSubtask )
{
   zVIEW vDialog;
   zLONG lRC = -1;

   GetViewByName( &vDialog, "vDialog", vSubtask, zLEVEL_TASK );
   if ( vDialog )
   {
      zCHAR szOptionTag[ 65 ];
      zPCHAR pch;

      GetLastCommandTag( vSubtask, szOptionTag );
      TraceLineS( "UpdatFontFaceNameInPlace Command: ", szOptionTag );
      pch = zstrrchr( szOptionTag, '.' );
      if ( pch )
         *pch = 0;

      lRC = CallPainterForSelectedControls( vSubtask, "tzpntrad",
                                            "PainterSelectedCallback",
                                            vDialog, 0, 0x00000040, 0, 0 );
   }

   return( (zSHORT) lRC );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
UpdateFontSizeInPlace( zVIEW vSubtask )
{
   zVIEW vDialog;
   zLONG lRC = -1;

   GetViewByName( &vDialog, "vDialog", vSubtask, zLEVEL_TASK );
   if ( vDialog )
   {
      zCHAR szOptionTag[ 65 ];
      zPCHAR pch;

      GetLastCommandTag( vSubtask, szOptionTag );
      TraceLineS( "UpdateFontSizeInPlace Command: ", szOptionTag );
      pch = zstrrchr( szOptionTag, '.' );
      if ( pch )
         *pch = 0;

      lRC = CallPainterForSelectedControls( vSubtask, "tzpntrad",
                                            "PainterSelectedCallback",
                                            vDialog, 0, 0x00000080, 0, 0 );
   }

   return( (zSHORT) lRC );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZPNTRAD_TargetSpecification
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZPNTRAD_TargetSpecification( zVIEW vSubtask )
{
   zVIEW vMeta;
   zVIEW vTaskLPLR;
   zVIEW vTZWINDOWL;
   zLONG lMetaZKey;

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) < 0 ||
        GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK ) < 0 )
   {
      return( -1 );
   }

   // if no selection found, select current meta
   if ( CheckExistenceOfEntity( vTaskLPLR, "TargetExecutable" ) != zCURSOR_SET ||
        SetCursorFirstSelectedEntity( vTaskLPLR, "TargetExecutable",
                                      "" ) >= zCURSOR_SET )
   {
      return( -1 );
   }

   CreateViewFromViewForTask( &vMeta, vTZWINDOWL, 0 );
   ResetView( vMeta );

   GetIntegerFromAttribute( &lMetaZKey, vMeta, "Dialog", "ZKey" );

   if ( SetCursorFirstEntityByInteger( vTaskLPLR, "Meta", "ZKey",
                                       lMetaZKey, "LPLR" ) >= zCURSOR_SET )
   {
      SetSelectStateOfEntity( vTaskLPLR, "TargetExecutable", TRUE );
   }

   DropView( vMeta );
   return( 0 );

} // zwTZPNTRAD_TargetSpecification

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
ChangeSelectedViewMapping( zVIEW vSubtask )
{
   zVIEW vDialog;
   zVIEW vTZZOVEAO;
   zLONG lRC = -1;

   GetViewByName( &vDialog, "vDialog", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZZOVEAO, "TZZOVEAO", vSubtask, zLEVEL_TASK );
   if ( vDialog && vTZZOVEAO )
   {
      zCHAR szVEA[ 3 * 33 ];

      GetStringFromAttribute( szVEA, zsizeof( szVEA ), vTZZOVEAO, "ViewObjRef", "Name" );

      lRC = CallPainterForSelectedControls( vSubtask, "tzpntrad",
                                            "PainterSelectedCallback",
                                            vDialog, 0, 1, szVEA, 0 );
   }

   return( (zSHORT) lRC );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
SetSelectedEntityMapping( zVIEW vSubtask )
{
   zVIEW vDialog;
   zVIEW vTZZOVEAO;
   zLONG lRC = -1;

   GetViewByName( &vDialog, "vDialog", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZZOVEAO, "TZZOVEAO", vSubtask, zLEVEL_TASK );
   if ( vDialog && vTZZOVEAO )
   {
      zVIEW vCM_List;
      zVIEW vLOD;
      zLONG lZKey;
      zCHAR szVEA[ 3 * 33 ];
      zSHORT nLth;

      GetStringFromAttribute( szVEA, zsizeof( szVEA ), vTZZOVEAO, "ViewObjRef", "Name" );
      nLth = (zSHORT) zstrlen( szVEA );
      szVEA[ nLth++ ] = '.';
      GetStringFromAttribute( szVEA + nLth, zsizeof( szVEA ) - nLth, vTZZOVEAO, "LOD_Entity", "Name" );
      GetIntegerFromAttribute( &lZKey, vTZZOVEAO, "LOD", "ZKey" );
      RetrieveViewForMetaList( vSubtask,
                               &vCM_List, zREFER_LOD_META );
      SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef",
                                     "CPLR_ZKey", lZKey, "" );
      ActivateMetaOI( vSubtask, &vLOD,
                      vCM_List, zREFER_LOD_META, 0 );

      GetIntegerFromAttribute( &lZKey, vTZZOVEAO, "LOD_Entity", "ZKey" );
      if ( SetCursorFirstEntityByInteger( vLOD, "LOD_Entity",
                                          "ZKey", lZKey, "" ) == zCURSOR_SET )
      {
         lRC = CallPainterForSelectedControls( vSubtask, "tzrpupdd",
                                               "PainterSelectedCallback",
                                               vDialog, vLOD, 3, szVEA, 0 );
      }

      DropMetaOI( vSubtask, vLOD );
   }

   return( (zSHORT) lRC );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
SetSelectedAttributeMapping( zVIEW vSubtask )
{
   zVIEW vDialog;
   zVIEW vTZZOVEAO;
   zLONG lRC = -1;

   GetViewByName( &vDialog, "vDialog", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZZOVEAO, "TZZOVEAO", vSubtask, zLEVEL_TASK );
   if ( vDialog && vTZZOVEAO )
   {
      zVIEW vCM_List;
      zVIEW vLOD;
      zLONG lZKey;
      zLONG lZKeyA;
      zCHAR szVEA[ 3 * 33 ];
      zSHORT nLth;

      GetStringFromAttribute( szVEA, zsizeof( szVEA ), vTZZOVEAO, "ViewObjRef", "Name" );
      nLth = (zSHORT) zstrlen( szVEA );
      szVEA[ nLth++ ] = '.';
      GetStringFromAttribute( szVEA + nLth, zsizeof( szVEA ) - nLth, vTZZOVEAO, "LOD_Entity", "Name" );
      nLth = (zSHORT) zstrlen( szVEA );
      szVEA[ nLth++ ] = '.';
      GetStringFromAttribute( szVEA + nLth, zsizeof( szVEA ) - nLth, vTZZOVEAO, "ER_Attribute", "Name" );
      GetIntegerFromAttribute( &lZKey, vTZZOVEAO, "LOD", "ZKey" );
      RetrieveViewForMetaList( vSubtask, &vCM_List, zREFER_LOD_META );
      SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef", "CPLR_ZKey", lZKey, "" );
      ActivateMetaOI( vSubtask, &vLOD, vCM_List, zREFER_LOD_META, 0 );

      GetIntegerFromAttribute( &lZKey, vTZZOVEAO, "LOD_Entity", "ZKey" );
      GetIntegerFromAttribute( &lZKeyA, vTZZOVEAO, "LOD_Attribute", "ZKey" );
      if ( SetCursorFirstEntityByInteger( vLOD, "LOD_Entity",
                                          "ZKey", lZKey, "" ) == zCURSOR_SET &&
           SetCursorFirstEntityByInteger( vLOD, "LOD_Attribute",
                                          "ZKey", lZKeyA, "" ) == zCURSOR_SET )
      {
         lRC = CallPainterForSelectedControls( vSubtask, "tzrpupdd",
                                               "PainterSelectedCallback",
                                               vDialog, vLOD, 7, szVEA, 0 );
      }

      DropMetaOI( vSubtask, vLOD );
   }

   return( (zSHORT) lRC );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zSHORT
fnChangeMappingView( zVIEW vSubtask )
{
   zVIEW  vOldViewName;
   zVIEW  vNewViewName;
   zVIEW  vTZWINDOWL;
   zVIEW  vDialog;
   zCHAR  szOriginalViewName[ 33 ];
   zCHAR  szNewViewName[ 33 ];

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vOldViewName, vTZWINDOWL, 0 );
   GetVariableFromAttribute( szOriginalViewName, 0, 'S', 32,
                             vOldViewName, "Dialog", "wOriginalViewName", "", 0 );
   if ( SetCursorFirstEntityByString( vOldViewName, "ViewObjRef", "Name",
                                      szOriginalViewName, 0 ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "", "Change View Mapping",
                   "Original View Name is not a Registered View in this Dialog.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      DropView( vOldViewName );
      return( -1 );
   }

   CreateViewFromViewForTask( &vNewViewName, vTZWINDOWL, 0 );
   GetVariableFromAttribute( szNewViewName, 0, 'S', 32,
                             vNewViewName, "Dialog", "wNewViewName", "", 0 );
   if ( SetCursorFirstEntityByString( vNewViewName, "ViewObjRef", "Name",
                                      szNewViewName, 0 ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "", "Change View Mapping",
                   "New View Name is not a Registered View in this Dialog.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      DropView( vOldViewName );
      DropView( vNewViewName );
      return( -1 );
   }

   // Go to execute change view mapping at each Control level.
   fnChangeMappingViewR( vDialog, vOldViewName, vNewViewName, TRUE, TRUE );

   DropView( vNewViewName );
   DropView( vOldViewName );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: ChangeMappingViewChildren
//
/////////////////////////////////////////////////////////////////////////////
zSHORT
fnChangeMappingViewChildren( zVIEW vSubtask, zBOOL bAtLevel )
{
   zVIEW  vOldViewName;
   zVIEW  vNewViewName;
   zVIEW  vDialog;
   zVIEW  vTZWINDOWL;
   zCHAR  szCtrlTag[ 33 ];
   zCHAR  szNewViewName[ 33 ];

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szCtrlTag, zsizeof( szCtrlTag ), vTZWINDOWL, "Control", "Tag" );

   CreateViewFromViewForTask( &vOldViewName, vTZWINDOWL, 0 );
   CreateViewFromViewForTask( &vNewViewName, vTZWINDOWL, 0 );
   SetNameForView( vOldViewName, "vOldViewName", vSubtask, zLEVEL_TASK );
   SetNameForView( vNewViewName, "vNewViewName", vSubtask, zLEVEL_TASK );
   GetCtrlText( vSubtask, "NewViewName", szNewViewName, 32 );
   if ( SetCursorFirstEntityByString( vNewViewName, "ViewObjRef", "Name",
                                      szNewViewName, 0 ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "", "Change View Mapping",
                   "New View Name is not a Registered View in this Dialog.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      DropView( vOldViewName );
      DropView( vNewViewName );
      return( -1 );
   }

   // Go to execute change view mapping for this control and its children.
   fnChangeMappingViewR( vDialog, vOldViewName, vNewViewName, bAtLevel, TRUE );

   DropView( vNewViewName );
   DropView( vOldViewName );

   return( 0 );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
ChangeMappingViewChildren( zVIEW vSubtask )
{
   return( fnChangeMappingViewChildren( vSubtask, FALSE ) );
}

#if 1

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_ChangeMappingView( zVIEW vSubtask )
{
   zVIEW  vDialog;

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   while ( ResetViewFromSubobject( vDialog ) == 0 )
   {
   }

   return( fnChangeMappingViewChildren( vSubtask, TRUE ) );
}

#else

zOPER_EXPORT zSHORT OPERATION
zwTZPNTRAD_ChangeMappingView( zVIEW vSubtask )
{
   zVIEW  vOldViewName;
   zVIEW  vNewViewName;
   zVIEW  vDialog;
   zVIEW  vTZWINDOWL;
   zCHAR  szOriginalViewName[ 33 ];
   zCHAR  szNewViewName[ 33 ];

   GetViewByName( &vDialog, "TZWINDOW", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vOldViewName, vTZWINDOWL, 0 );
   GetVariableFromAttribute( szOriginalViewName, 0, 'S', 32,
                             vOldViewName, "Dialog", "wOriginalViewName", "", 0 );
   if ( SetCursorFirstEntityByString( vOldViewName, "ViewObjRef", "Name",
                                       szOriginalViewName, 0 ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "", "Change View Mapping",
                   "Original View Name is not a Registered View in this Dialog.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      DropView( vOldViewName );
      return( -1 );
   }

   CreateViewFromViewForTask( &vNewViewName, vTZWINDOWL, 0 );
   GetVariableFromAttribute( szNewViewName, 0, 'S', 32,
                             vNewViewName, "Dialog", "wNewViewName", "", 0 );
   if ( SetCursorFirstEntityByString( vNewViewName, "ViewObjRef", "Name",
                                       szNewViewName, 0 ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "", "Change View Mapping",
                   "New View Name is not a Registered View in this Dialog.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      DropView( vOldViewName );
      DropView( vNewViewName );
      return( -1 );
   }

   // Go to execute change view mapping at each Control level.
   // If the Control entity on which we currently have position is selected, then we are only to
   // process that entity and its children.
   // If it is not selected, we will process all the entities in a loop.
   if ( GetSelectStateOfEntity( vDialog, "Control" ) == 1 )
   {
      zwTZPNTRAD_ChangeMappingViewR( vDialog, vOldViewName, vNewViewName );
   }
   else
   {
      zSHORT nRC;

      // Loop through all Controls at this level.
      for ( nRC = SetCursorFirstEntity( vDialog, "Control", "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDialog, "Control", "" ) )
      {
         zwTZPNTRAD_ChangeMappingViewR( vDialog, vOldViewName, vNewViewName );
      }
   }

   DropView( vNewViewName );
   DropView( vOldViewName );

   return( 0 );
}
#endif

zOPER_EXPORT zSHORT OPERATION
ShowControlBar( zVIEW   vSubtask )
{
   zVIEW vDialog;

   GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );
   fnCreateMappingEntities( vSubtask, vDialog );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
HideControlBar( zVIEW   vSubtask )
{
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ShowHideControlBar( zVIEW   vSubtask )
{
   zVIEW vDialog;
   zBOOL bVisible;

   GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK );
   bVisible = (zBOOL) GetCtrlState( vSubtask, "ControlBar",
                                    zCONTROL_STATUS_VISIBLE );
   SetCtrlState( vSubtask, "ControlBar", zCONTROL_STATUS_VISIBLE, !bVisible );
   SetOptionState( vSubtask, "ShowHideControlBar", zOPTION_STATUS_TEXT,
                   (zULONG) (bVisible ? "Show Control Bar" : "Hide Control Bar") );
   fnCreateMappingEntities( vSubtask, vDialog );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ShowMappingPopup( zVIEW   vSubtask )
{
   zCHAR szEntityName[ 33 ];

   OL_GetCurrentEntityName( vSubtask, "View", 0, szEntityName );
   TraceLineS( "EntityName: ", szEntityName );
   if ( zstrcmp( szEntityName, "ViewObjRef" ) == 0 )
      CreateTrackingPopupMenu( vSubtask, "ViewObjRef", -1, 0, FALSE, FALSE );

   if ( zstrcmp( szEntityName, "LOD" ) == 0 )
      CreateTrackingPopupMenu( vSubtask, "LOD", -1, 0, FALSE, FALSE );

   if ( zstrcmp( szEntityName, "LOD_Entity" ) == 0 )
      CreateTrackingPopupMenu( vSubtask, "LOD_Entity", -1, 0, FALSE, FALSE );

   if ( zstrcmp( szEntityName, "ER_Attribute" ) == 0 )
      CreateTrackingPopupMenu( vSubtask, "ER_Attribute", -1, 0, FALSE, FALSE );

   return( 0 );
}

zBOOL
ValidateCtrlAndActionTags( zVIEW vSubtask, zVIEW vDialog )
{
   zFARPROC_DUP_CHECK lpfnDuplicateCheck;
   zCHAR  szTempString[ 256 ];
   zLONG  hLibrary;
   zPCHAR pchDlg;
   zPCHAR pchWnd;
   zSHORT nRC;

   // If there are duplicate tags in Ctrl or across Ctrl/Action, it can
   // cause problems at run time for the generated JSP.  So let's warn
   // the developer if the condition exists.

   hLibrary = (zLONG) SysLoadLibrary( vSubtask, "tzctl" );
   if ( hLibrary )
   {
      if ( (lpfnDuplicateCheck =
            (zFARPROC_DUP_CHECK) SysGetProc( (LPLIBRARY) hLibrary,
                                             "CheckDuplicateTags" )) )
      {
      // TraceLine( "(tzcmcvto) Checking for duplicate control/action tags Dialog.Window: %s.%s",
      //            pchDlg, pchWnd );
         nRC = (*lpfnDuplicateCheck)( vSubtask, vDialog, 1 );
         if ( nRC > 0 )
         {
            GetAddrForAttribute( &pchDlg, vDialog, "Dialog", "Tag" );
            GetAddrForAttribute( &pchWnd, vDialog, "Window", "Tag" );
            zsprintf( szTempString,
                      "(tzcmcvto) Duplicate control/action tags found in Dialog.Window: %s.%s",
                      pchDlg, pchWnd );
            TraceLineS( szTempString, "" );
            strcat_s( szTempString, zsizeof( szTempString ), "\n(see Zeidon trace for details)" );
            MessageSend( vSubtask, "CM00815", "JSP Generation",
                         szTempString, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( TRUE );  // duplicates found
         }
      }
   }

   return( FALSE );  // no duplicates found
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: GenerateJSP
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateJSP( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zVIEW  vValidate;
   zLONG  lZKey;
   zLONG  lListHandle;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // So we can modify the Dialog and not worry about the consequences.
   GetIntegerFromAttribute( &lZKey, vTZWINDOWL, "Window", "ZKey" );
   ActivateOI_FromOI_ForTask( &vTZWINDOW, vTZWINDOWL, vSubtask, 0 );
   SetCursorFirstEntityByInteger( vTZWINDOW, "Window", "ZKey", lZKey, "" );
   CreateViewFromViewForTask( &vValidate, vTZWINDOW, 0 );
   SetViewFromView( vValidate, vTZWINDOW );

   lListHandle = 0;
   ValidateCtrlAndActionTags( vSubtask, vValidate );
   oTZWDLGSO_GenerateJSP( vTZWINDOW, vSubtask );
// oTZWDLGSO_GenerateXSL( vTZWINDOW );

   DropMetaOI_FromList( lListHandle );
   DropObjectInstance( vTZWINDOW );
   return( 0 );

} // GenerateJSP

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: GenerateJavaJSP
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateJSPJava( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zVIEW  vValidate;
   zLONG  lZKey;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // So we can modify the Dialog and not worry about the consequences.
   GetIntegerFromAttribute( &lZKey, vTZWINDOWL, "Window", "ZKey" );
   ActivateOI_FromOI_ForTask( &vTZWINDOW, vTZWINDOWL, vSubtask, 0 );
   SetCursorFirstEntityByInteger( vTZWINDOW, "Window", "ZKey", lZKey, "" );
   CreateViewFromViewForTask( &vValidate, vTZWINDOW, 0 );
   SetViewFromView( vValidate, vTZWINDOW );

   ValidateCtrlAndActionTags( vSubtask, vValidate );
   oTZWDLGSO_GenerateJSPJava( vTZWINDOW, vSubtask );
// oTZWDLGSO_GenerateXSL( vTZWINDOW );

   DropObjectInstance( vTZWINDOW );
   return( 0 );

} // GenerateJSPJava

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: GenerateAllJSP
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateAllJSP( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zVIEW  vValidate;
   zPCHAR pchDlg;
   zPCHAR pchWnd;
   zCHAR  szMsg[ 256 ];
   zLONG  lListHandle;
   zSHORT nRC;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // So we can modify the Dialog and not worry about the consequences.
   ActivateOI_FromOI_ForTask( &vTZWINDOWL, vTZWINDOWL, vSubtask, 0 );
   CreateViewFromViewForTask( &vTZWINDOW, vTZWINDOWL, 0 );
   CreateViewFromViewForTask( &vValidate, vTZWINDOWL, 0 );

   // Prompt operator to ensure ALL windows are to be generated.
   GetAddrForAttribute( &pchDlg, vTZWINDOWL, "Dialog", "Tag" );
   sprintf_s( szMsg, zsizeof( szMsg ), "Generate JSP for ALL Windows in Dialog: %s?", pchDlg );
   if ( g_bSkipPrompt == FALSE )
   {
      if ( OperatorPrompt( vSubtask, "Generate JSP",
                           szMsg, 1, zBUTTONS_YESNO,
                           zRESPONSE_YES, zICON_QUESTION ) == zRESPONSE_NO )
      {
         DropObjectInstance( vTZWINDOWL );
         return( -1 );
      }
   }

   lListHandle = 0;
   nRC = SetCursorFirstEntity( vTZWINDOW, "Window", 0 );
   while ( nRC == zCURSOR_SET )
   {
      GetAddrForAttribute( &pchWnd, vTZWINDOWL, "Window", "Tag" );
      sprintf_s( szMsg, zsizeof( szMsg ), "Generating JSP: %s.%s", pchDlg, pchWnd );
      MB_SetMessage( vSubtask, 1, szMsg );
      SetViewFromView( vValidate, vTZWINDOW );
      ValidateCtrlAndActionTags( vSubtask, vValidate );
      oTZWDLGSO_GenerateJSP( vTZWINDOW, vSubtask );
   // oTZWDLGSO_GenerateXSL( vTZWINDOW );
      nRC = SetCursorNextEntity( vTZWINDOW, "Window", 0 );
   }

   DropMetaOI_FromList( lListHandle );
   DropObjectInstance( vTZWINDOWL );
   return( 0 );

} // GenerateAllJSP

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: GenerateAllJavaJSP
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateAllJSPJava( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zVIEW  vValidate;
   zPCHAR pchDlg;
   zPCHAR pchWnd;
   zCHAR  szMsg[ 256 ];
   zSHORT nRC;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // So we can modify the Dialog and not worry about the consequences.
   ActivateOI_FromOI_ForTask( &vTZWINDOWL, vTZWINDOWL, vSubtask, 0 );
   CreateViewFromViewForTask( &vTZWINDOW, vTZWINDOWL, 0 );
   CreateViewFromViewForTask( &vValidate, vTZWINDOWL, 0 );

   // Prompt operator to ensure ALL windows are to be generated.
   GetAddrForAttribute( &pchDlg, vTZWINDOWL, "Dialog", "Tag" );
   sprintf_s( szMsg, zsizeof( szMsg ), "Generate Java JSP for ALL Windows in Dialog: %s?", pchDlg );
   if ( g_bSkipPrompt == FALSE )
   {
      if ( OperatorPrompt( vSubtask, "Generate Java JSP",
                           szMsg, 1, zBUTTONS_YESNO,
                           zRESPONSE_YES, zICON_QUESTION ) == zRESPONSE_NO )
      {
         DropObjectInstance( vTZWINDOWL );
         return( -1 );
      }
   }

   nRC = SetCursorFirstEntity( vTZWINDOW, "Window", 0 );
   while ( nRC == zCURSOR_SET )
   {
      GetAddrForAttribute( &pchWnd, vTZWINDOWL, "Window", "Tag" );
      sprintf_s( szMsg, zsizeof( szMsg ), "Generating JSP Java: %s.%s", pchDlg, pchWnd );
      MB_SetMessage( vSubtask, 1, szMsg );
      SetViewFromView( vValidate, vTZWINDOW );
      ValidateCtrlAndActionTags( vSubtask, vValidate );
      oTZWDLGSO_GenerateJSPJava( vTZWINDOW, vSubtask );
   // oTZWDLGSO_GenerateXSL( vTZWINDOW );
      nRC = SetCursorNextEntity( vTZWINDOW, "Window", 0 );
   }

   DropObjectInstance( vTZWINDOWL );
   return( 0 );

} // GenerateAllJSPJava

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: GenerateAllJavaJSP
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateAllJSPJavaAllDialogs( zVIEW vSubtask )
{
   zVIEW  vValidate;
   zVIEW  vTZWINDOW;
   zVIEW  vTaskLPLR;
   zPCHAR pchDlg;
   zPCHAR pchWnd;
   zCHAR  szMsg[ 256 ];
   zCHAR  SourceFileName[ 514 ] = { 0 };
   zCHAR  DialogName[ 256 ];
   zSHORT nRC;

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );

   // Prompt operator to ensure ALL windows are to be generated.
   GetAddrForAttribute( &pchDlg, vTaskLPLR, "LPLR", "Name" );
   zsprintf( szMsg, "Generate JSP FOR ALL DIALOGS in LPLR %s?!", pchDlg );
   if ( g_bSkipPrompt == FALSE )
   {
      if ( OperatorPrompt( vSubtask, "Generate Java JSP",
                           szMsg, 1, zBUTTONS_YESNO,
                           zRESPONSE_YES, zICON_QUESTION ) == zRESPONSE_NO )
      {
         return( -1 );
      }
   }

   if ( SetCursorFirstEntityByInteger( vTaskLPLR, "W_MetaType", "Type",
                                       11, 0 ) >= zCURSOR_SET )
   {
      nRC = SetCursorFirstEntity( vTaskLPLR, "W_MetaDef", 0 );
      while ( nRC == zCURSOR_SET )
      {
      //:SourceFileName = SourceLPLR.LPLR.MetaSrcDir + "\" + DialogName + ".PWD"
      GetStringFromAttribute( SourceFileName, zsizeof( SourceFileName ), vTaskLPLR, "LPLR", "MetaSrcDir" );
      GetStringFromAttribute( DialogName, zsizeof( DialogName ), vTaskLPLR, "W_MetaDef", "Name" );
                if ( zstrcmp( DialogName, "AD_Base" ) != 0 && zstrcmp( DialogName, "AD_BASE" ) != 0 )
                {
         ZeidonStringConcat( SourceFileName, 1, 0, "\\", 1, 0, 514 );
         ZeidonStringConcat( SourceFileName, 1, 0, DialogName, 1, 0, 514 );
         ZeidonStringConcat( SourceFileName, 1, 0, ".PWD", 1, 0, 514 );

         ActivateOI_FromFile( &vTZWINDOW, "TZWDLGSO", vTaskLPLR, SourceFileName, 8192 );
         CreateViewFromViewForTask( &vValidate, vTZWINDOW, 0 );


         nRC = SetCursorFirstEntity( vTZWINDOW, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
           GetAddrForAttribute( &pchWnd, vTZWINDOW, "Window", "Tag" );
           zsprintf( szMsg, "Generating JSP Java: %s.%s", pchDlg, pchWnd );
           MB_SetMessage( vSubtask, 1, szMsg );
           SetViewFromView( vValidate, vTZWINDOW );
           ValidateCtrlAndActionTags( vSubtask, vValidate );
           oTZWDLGSO_GenerateJSPJava( vTZWINDOW, vSubtask );
           nRC = SetCursorNextEntity( vTZWINDOW, "Window", 0 );
         }
         DropObjectInstance( vTZWINDOW );
                 }
       nRC = SetCursorNextEntity( vTaskLPLR, "W_MetaDef", 0 );
      }
   }
   return( 0 );

} // GenerateAllJSPJavaAllDialogs

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: FixPWDAllDialogs
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
FixPWDAllDialogs( zVIEW vSubtask )
{
   zVIEW  vValidate;
   zVIEW  vTZWINDOW;
   zVIEW  vTaskLPLR;
   zPCHAR pchDlg;
   zPCHAR pchWnd;
   zCHAR  szMsg[ 256 ];
   zCHAR  SourceFileName[ 514 ] = { 0 };
   zCHAR  DialogName[ 256 ];
   zSHORT nRC;

// The CtrlCtrl control was out of sync with Control (didn't contain all of the attributes). Because of this
// there are some attributes that get written to the pwd under the wrong attribute name. I have fixed TZWDLGSO.LOD but
// need to look through the controls and fix the attributes.

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );

   // Prompt operator to ensure ALL windows are to be generated.
   GetAddrForAttribute( &pchDlg, vTaskLPLR, "LPLR", "Name" );
   zsprintf( szMsg, "Generate JSP FOR ALL DIALOGS in LPLR %s?!", pchDlg );
   if ( g_bSkipPrompt == FALSE )
   {
      if ( OperatorPrompt( vSubtask, "Generate Java JSP",
                           szMsg, 1, zBUTTONS_YESNO,
                           zRESPONSE_YES, zICON_QUESTION ) == zRESPONSE_NO )
      {
         return( -1 );
      }
   }

   if ( SetCursorFirstEntityByInteger( vTaskLPLR, "W_MetaType", "Type",
                                       11, 0 ) >= zCURSOR_SET )
   {
      nRC = SetCursorFirstEntity( vTaskLPLR, "W_MetaDef", 0 );
      while ( nRC == zCURSOR_SET )
      {
      //:SourceFileName = SourceLPLR.LPLR.MetaSrcDir + "\" + DialogName + ".PWD"
      GetStringFromAttribute( SourceFileName, zsizeof( SourceFileName ), vTaskLPLR, "LPLR", "MetaSrcDir" );
      GetStringFromAttribute( DialogName, zsizeof( DialogName ), vTaskLPLR, "W_MetaDef", "Name" );
                if ( zstrcmp( DialogName, "AD_Base" ) != 0 && zstrcmp( DialogName, "AD_BASE" ) != 0 )
                {
         ZeidonStringConcat( SourceFileName, 1, 0, "\\", 1, 0, 514 );
         ZeidonStringConcat( SourceFileName, 1, 0, DialogName, 1, 0, 514 );
         ZeidonStringConcat( SourceFileName, 1, 0, ".PWD", 1, 0, 514 );

         ActivateOI_FromFile( &vTZWINDOW, "TZWDLGSO", vTaskLPLR, SourceFileName, 8192 );
         CreateViewFromViewForTask( &vValidate, vTZWINDOW, 0 );


         nRC = SetCursorFirstEntity( vTZWINDOW, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
           GetAddrForAttribute( &pchWnd, vTZWINDOW, "Window", "Tag" );
           zsprintf( szMsg, "Generating JSP Java: %s.%s", pchDlg, pchWnd );
           MB_SetMessage( vSubtask, 1, szMsg );
           SetViewFromView( vValidate, vTZWINDOW );
           ValidateCtrlAndActionTags( vSubtask, vValidate );
           oTZWDLGSO_GenerateJSPJava( vTZWINDOW, vSubtask );
           nRC = SetCursorNextEntity( vTZWINDOW, "Window", 0 );
         }
         DropObjectInstance( vTZWINDOW );
                 }
       nRC = SetCursorNextEntity( vTaskLPLR, "W_MetaDef", 0 );
      }
   }
   return( 0 );

} // FixPWDAllDialogs


/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: GenerateXRP
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateXRP( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zVIEW  vTZRPSRCO;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vTZWINDOW, vTZWINDOWL, 0 );

   oTZRPSRCO_GenerateXRP( &vTZRPSRCO, vTZWINDOW );
   DropView( vTZWINDOW );

   return( 0 );

} // GenerateXRP

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: GenerateAllXRP
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateAllXRP( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zVIEW  vTZRPSRCO;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vTZWINDOW, vTZWINDOWL, 0 );

   oTZRPSRCO_GenerateXRP( &vTZRPSRCO, vTZWINDOW );
   DropView( vTZWINDOW );

   return( 0 );

} // GenerateAllXRP

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
SetReadOnlyCurrentWindow( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vTZWINDOW, vTZWINDOWL, 0 );

   CheckMigrateCtrls( vTZWINDOW, 0, zCHECK_READONLY_ALL_CTRLS, 0, 0, 0 );

   DropView( vTZWINDOW );

   return( 0 );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
SetReadOnlyEntireDialog( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zSHORT nRC;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vTZWINDOW, vTZWINDOWL, 0 );

   nRC = SetCursorFirstEntity( vTZWINDOW, "Window", 0 );
   while ( nRC == zCURSOR_SET )
   {
      CheckMigrateCtrls( vTZWINDOW, 0, zCHECK_READONLY_ALL_CTRLS, 0, 0, 0 );
      nRC = SetCursorNextEntity( vTZWINDOW, "Window", 0 );
   }

   DropView( vTZWINDOW );

   return( 0 );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
SetResizeCurrentWindow( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zCHAR  szHeight[ 256 ];
   zSHORT nRC;

   szHeight[ 0 ] = 0;
   nRC = OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter 'From' height (0 for all)", 0,
                                 szHeight, zsizeof( szHeight ) - 1 );
   g_lFromHeight = zatol( szHeight );
   if ( nRC == zRESPONSE_OK && g_lFromHeight >= 0 )
   {
      szHeight[ 0 ] = 0;
      nRC = OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter 'To' height", 0,
                                    szHeight, zsizeof( szHeight ) - 1 );
      g_lToHeight = zatol( szHeight );

      if ( nRC == zRESPONSE_OK && g_lToHeight > 0 )
      {
         zPCHAR pchWndTag;

         GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
         CreateViewFromViewForTask( &vTZWINDOW, vTZWINDOWL, 0 );

         GetAddrForAttribute( &pchWndTag, vTZWINDOW, "Window", "Tag" );
         fnPainterCall( zMSG_UPDATEWINDOWBYNAME, vSubtask, 0, pchWndTag, 33 );

         CheckMigrateCtrls( vTZWINDOW, 0, zCHECK_RESIZE_EDIT_CTRLS, 0, 0, 0 );
         fnPainterCall( zMSG_REPAINTZEIDONWINDOW, vSubtask, 0, 0, 0 );

         DropView( vTZWINDOW );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
SetResizeEntireDialog( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zCHAR  szHeight[ 256 ];
   zSHORT nRC;

   szHeight[ 0 ] = 0;
   nRC = OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter 'From' height (0 for all)", 0,
                                 szHeight, zsizeof( szHeight ) - 1 );
   g_lFromHeight = zatol( szHeight );
   if ( nRC == zRESPONSE_OK && g_lFromHeight >= 0 )
   {
      szHeight[ 0 ] = 0;
      nRC = OperatorPromptForInput( vSubtask, "Dialog Migration", "Enter 'To' height", 0,
                                    szHeight, zsizeof( szHeight ) - 1 );
      g_lToHeight = zatol( szHeight );

      if ( nRC == zRESPONSE_OK && g_lFromHeight >= 0 )
      {
         fnPainterCall( zMSG_UPDATEALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
         GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
         CreateViewFromViewForTask( &vTZWINDOW, vTZWINDOWL, 0 );

         nRC = SetCursorFirstEntity( vTZWINDOW, "Window", 0 );
         while ( nRC == zCURSOR_SET )
         {
            CheckMigrateCtrls( vTZWINDOW, 0, zCHECK_RESIZE_EDIT_CTRLS, 0, 0, 0 );
            nRC = SetCursorNextEntity( vTZWINDOW, "Window", 0 );
         }

         fnPainterCall( zMSG_REPAINTALLZEIDONWINDOWS, vSubtask, 0, 0, 0 );
         DropView( vTZWINDOW );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: FindCtrl
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
FindCtrl( zVIEW vSubtask )
{
   zVIEW  vTZWINDOW;
   zCHAR  szText[ 256 ];

   if ( GetViewByName( &vTZWINDOW, "TZWINDOW", vSubtask, zLEVEL_TASK ) < 0 )
   {
      return( -1 );
   }

   GetCtrlText( vSubtask, "FindText", szText, zsizeof( szText ) );
   if ( szText[ 0 ] )
   {
      zCHAR  szAttrib[ 256 ];
      zSHORT nLth;
      zLONG  lRC = 0;

      SaveCtrlList( vSubtask );
      GetCtrlText( vSubtask, "InvisibleForFind", szAttrib, zsizeof( szAttrib ) );
      if ( szAttrib[ 0 ] )
         lRC = zatol( szAttrib );

      szAttrib[ 0 ] = 0;

      if ( GetCtrlState( vSubtask, "FindByTag", zCONTROL_STATUS_CHECKED ) )
         strcpy_s( szAttrib, zsizeof( szAttrib ), "Tag" );

      if ( GetCtrlState( vSubtask, "FindByText", zCONTROL_STATUS_CHECKED ) )
      {
         nLth = (zSHORT) zstrlen( szAttrib );
         if ( nLth > 0 )
            szAttrib[ nLth++ ] = ',';

         strcpy_s( szAttrib + nLth, zsizeof( szAttrib ) - nLth, "Text" );
      }

      lRC = OL_FindItemByAttribute( vSubtask, "CtrlList", "Control",
                                    szAttrib, szText, lRC, lRC != 0 ? 1 : 0 );
      if ( lRC && lRC != -1 )
      {
         TraceLineI( "FindCtrl RC: ", lRC );
         zltoa( lRC, szAttrib, zsizeof( szAttrib ) );
         SetCtrlText( vSubtask, "InvisibleForFind", szAttrib );
      // RefreshCtrl( vSubtask, "Mapping" );
      // RefreshCtrl( vSubtask, "EventAction" );
      // RefreshCtrl( vSubtask, "MapType" );
      // RefreshCtrl( vSubtask, "Context" );
      // RefreshWindowExceptForCtrl( vSubtask, "CtrlList" );
      // fnShowCtrlList( vSubtask );

      // if ( OL_SetCursorByEntityNumber( vTZWINDOW, "Control", lRC ) == 0 )
         {
            OL_SelectItemAtPosForEntity( vSubtask, "CtrlList", "Control", 2 + 4 + 16 );
         }

         GetStringFromAttribute( szText, zsizeof( szText ), vTZWINDOW, "Control", "Tag" );
         strcat_s( szText, zsizeof( szText ), " - Control found" );
         SysMessageBox( 0, szText,
                        "Please click on Ctrl to Show Information Properly", -1 );
      }
      else
         SetCtrlText( vSubtask, "InvisibleForFind", "" );
   }

   return( 0 );

} // FindCtrl

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
ReturnFromBuildDialogFlow( zVIEW vSubtask )
{
   zVIEW  vFlow;

   if ( GetViewByName( &vFlow, "TZFLOW", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vFlow );

   return( 0 );
}

void
fnSetTagType( zVIEW vFlow )
{
   zCHAR  szText[ 256 ];
   zCHAR  szType[ 32 ];

   // Get Tag and Type of widget (Control/MenuOptio/Hotkey) that invokes the event
   GetStringFromAttribute( szText, zsizeof( szText ), vFlow, "Widget", "Tag" );
   GetStringFromAttribute( szType, zsizeof( szType ), vFlow, "Widget", "Type" );
   if ( szType[ 0 ] )
   {
      strcat_s( szText, zsizeof( szText ), " - " );
      strcat_s( szText, zsizeof( szText ), szType );
   }

   SetAttributeFromString( vFlow, "Widget", "TagType", szText );

}

zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
BuildDialogFlow( zVIEW vSubtask )
{
   zCHAR  szWork[ 256 ];
   zCHAR  szText[ 256 ];
   zCHAR  szTag[ 32 ];
   zCHAR  szOper[ 32 ];
   zCHAR  szDlgTag[ 32 ];
   zCHAR  szWndTag[ 32 ];
   zVIEW  vDialog;
   zVIEW  vFlow;
   zLONG  lActType;
   zSHORT nLth;
   zSHORT nRC;

   ActivateEmptyObjectInstance( &vFlow, "TZFLOW", vSubtask, zSINGLE );
   CreateEntity( vFlow, "TZFLOW", zPOS_NEXT );
   SetNameForView( vFlow, "TZFLOW", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vDialog, "TZOPENDLG", vSubtask, zLEVEL_TASK ) > 0 )
   {
      CreateViewFromView( &vDialog, vDialog );
      while ( ResetViewFromSubobject( vDialog ) == 0 )
      {
         // nothing to do
      }

      SetAttributeFromAttribute( vFlow, "TZFLOW", "Tag", vDialog, "Dialog", "Tag" );
      SetAttributeFromAttribute( vFlow, "TZFLOW", "Name", vDialog, "Dialog", "Desc" );
      GetStringFromAttribute( szText, zsizeof( szText ), vFlow, "TZFLOW", "Tag" );
      GetStringFromAttribute( szWork, zsizeof( szWork ), vFlow, "TZFLOW", "Name" );
      if ( szWork[ 0 ] )
      {
         nLth = (zSHORT) zstrlen( szText );
         szText[ nLth++ ] = ' ';
         szText[ nLth++ ] = '-';
         szText[ nLth++ ] = ' ';
         strcpy_s( szText + nLth, zsizeof( szText ) - nLth, szWork );
      }

      SetAttributeFromString( vFlow, "TZFLOW", "Name", szText );
      nRC = SetCursorFirstEntity( vDialog, "Window", 0 );
      while ( nRC == zCURSOR_SET )
      {
         CreateEntity( vFlow, "Window", zPOS_NEXT );
         SetAttributeFromAttribute( vFlow, "Window", "Tag", vDialog, "Window", "Tag" );
         SetAttributeFromAttribute( vFlow, "Window", "Caption", vDialog, "Window", "Caption" );
         GetStringFromAttribute( szText, zsizeof( szText ), vFlow, "Window", "Tag" );
         nLth = (zSHORT) zstrlen( szText );
         szText[ nLth++ ] = ' ';
         szText[ nLth++ ] = '-';
         szText[ nLth++ ] = ' ';
         GetStringFromAttribute( szText + nLth, zsizeof( szText ) - nLth, vFlow, "Window", "Caption" );
         SetAttributeFromString( vFlow, "Window", "TagCaption", szText );
         nRC = SetCursorFirstEntity( vDialog, "Action", 0 );
         while ( nRC == zCURSOR_SET )
         {
            CreateEntity( vFlow, "Action", zPOS_NEXT );
            SetAttributeFromAttribute( vFlow, "Action", "Tag", vDialog, "Action", "Tag" );
            SetAttributeFromAttribute( vFlow, "Action", "Operation", vDialog, "Action", "Tag" );
            if ( CheckExistenceOfEntity( vDialog, "ActOper" ) == 0 )
               SetAttributeFromAttribute( vFlow, "Action", "Operation", vDialog, "ActOper", "Name" );
            else
               SetAttributeFromString( vFlow, "Action", "Operation", "n/a" );

            GetIntegerFromAttribute( &lActType, vDialog, "Action", "Type" );
            GetStringFromAttribute( szTag, zsizeof( szTag ), vFlow, "Action", "Tag" );
            GetStringFromAttribute( szOper, zsizeof( szOper ), vFlow, "Action", "Operation" );
            GetStringFromAttribute( szDlgTag, zsizeof( szDlgTag ), vDialog, "Action", "DialogName" );
            GetStringFromAttribute( szWndTag, zsizeof( szWndTag ), vDialog, "Action", "WindowName" );
            if ( szWndTag[ 0 ] )
            {
               sprintf_s( szText, zsizeof( szText ), "Tag: %s  Oper: %s   WAB: %s   ====> %s.%s",
                          szTag, szOper, GetActionString( lActType ), szDlgTag, szWndTag );
            }
            else
            {
               sprintf_s( szText, zsizeof( szText ), "Tag: %s  Oper: %s   WAB: %s",
                          szTag, szOper, GetActionString( lActType ) );
            }

            SetAttributeFromString( vFlow, "Action", "TagOperWAB_DlgWnd", szText );

            if ( CheckExistenceOfEntity( vDialog, "ActWndEvent" ) == 0 )
            {
               nRC = SetCursorFirstEntity( vDialog, "ActWndEvent", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  CreateEntity( vFlow, "Widget", zPOS_NEXT );
                  SetAttributeFromAttribute( vFlow, "Widget", "Tag", vDialog, "ActWndEvent", "EventName" );
                  SetAttributeFromString( vFlow, "Widget", "Type", "WindowEvent" );
                  fnSetTagType( vFlow );
                  nRC = SetCursorNextEntity( vDialog, "ActWndEvent", 0 );
               }
            }

            if ( CheckExistenceOfEntity( vDialog, "ActEvent" ) == 0 )
            {
               nRC = SetCursorFirstEntity( vDialog, "ActEvent", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  if ( CheckExistenceOfEntity( vDialog, "ActCtrl" ) == 0 )
                  {
                     CreateEntity( vFlow, "Widget", zPOS_NEXT );

                     GetStringFromAttribute( szText, zsizeof( szText ), vDialog, "ActCtrl", "Tag" );
                     nLth = (zSHORT) zstrlen( szText );
                     szText[ nLth++ ] = ' ';
                     szText[ nLth++ ] = '-';
                     szText[ nLth++ ] = ' ';
                     GetStringFromAttribute( szText + nLth, zsizeof( szText ) - nLth, vDialog, "ActCtrl", "Text" );

                     SetAttributeFromString( vFlow, "Widget", "Tag", szText );
                     SetAttributeFromString( vFlow, "Widget", "Type", "Control" );
                     fnSetTagType( vFlow );
                  }

                  nRC = SetCursorNextEntity( vDialog, "ActEvent", 0 );
               }
            }

            if ( CheckExistenceOfEntity( vDialog, "ActOpt" ) == 0 )
            {
               nRC = SetCursorFirstEntity( vDialog, "ActOpt", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  CreateEntity( vFlow, "Widget", zPOS_NEXT );
                  SetAttributeFromAttribute( vFlow, "Widget", "Tag", vDialog, "ActOpt", "Text" );
                  SetAttributeFromString( vFlow, "Widget", "Type", "Menu Option" );
                  fnSetTagType( vFlow );
                  nRC = SetCursorNextEntity( vDialog, "ActOpt", 0 );
               }
            }

            if ( CheckExistenceOfEntity( vDialog, "ActHot" ) == 0 )
            {
               nRC = SetCursorFirstEntity( vDialog, "ActHot", 0 );
               while ( nRC == zCURSOR_SET )
               {
                  CreateEntity( vFlow, "Widget", zPOS_NEXT );
                  SetAttributeFromAttribute( vFlow, "Widget", "Tag", vDialog, "ActHot", "Title" );
                  SetAttributeFromString( vFlow, "Widget", "Type", "Hotkey" );
                  fnSetTagType( vFlow );
                  nRC = SetCursorNextEntity( vDialog, "ActHot", 0 );
               }
            }

            nRC = SetCursorNextEntity( vDialog, "Action", 0 );
         }

         nRC = SetCursorNextEntity( vDialog, "Window", 0 );
      }

      DropView( vDialog );
      return( 0 );
   }

   return( -1 );
}


/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: GenerateJavaJSP
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
GenerateJSPJavaInc( zVIEW vSubtask )
{
   zVIEW  vTZWINDOWL;
   zVIEW  vTZWINDOW;
   zVIEW  vValidate;
   zLONG  lZKey;

   GetViewByName( &vTZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   // So we can modify the Dialog and not worry about the consequences.
   GetIntegerFromAttribute( &lZKey, vTZWINDOWL, "Window", "ZKey" );
   ActivateOI_FromOI_ForTask( &vTZWINDOW, vTZWINDOWL, vSubtask, 0 );
   SetCursorFirstEntityByInteger( vTZWINDOW, "Window", "ZKey", lZKey, "" );
   CreateViewFromViewForTask( &vValidate, vTZWINDOW, 0 );
   SetViewFromView( vValidate, vTZWINDOW );

   ValidateCtrlAndActionTags( vSubtask, vValidate );
   oTZWDLGSO_GenerateJSPJavaInc( vTZWINDOW, vSubtask );

   DropObjectInstance( vTZWINDOW );
   return( 0 );

} // GenerateJSPJava


#ifdef __cplusplus
}
#endif
