#define KZSYSSVC_INCL
#include "KZOENGAA.H" 
#include "TZ__OPRS.H" 
#include "ZDRVROPR.H" 
#include "TZVMLIP.H" 
 
#ifdef __cplusplus
extern "C"
{
#endif
 
#include "ZEIDONOP.H"

zSHORT zwTZPNTRAD_DeleteMenu( void );
zSHORT zwTZPNTRAD_SaveAs( zVIEW*, zPCHAR );
zSHORT zwTZPNTRAD_EnableMenuItems( zVIEW, zPCHAR, zPCHAR, zPCHAR, zSHORT*, zSHORT* );
zSHORT zwTZPNTRAD_EnableMenuDeleteAll( zVIEW, zPCHAR );
zSHORT zwTZPNTRAD_CheckDialogName( zVIEW, zVIEW, zPCHAR );
zSHORT zwTZPNTRAD_CreateWindowList( zVIEW, zVIEW, zVIEW );
zSHORT WND_UPD_SetColors( zVIEW, zVIEW );
zSHORT zwTZPNTRAD_LoadWindowPopups( zVIEW, zPCHAR, zPCHAR, zPCHAR, zPCHAR, zPCHAR );
zSHORT zwTZPNTRAD_LoadEventPopups( zVIEW, zPCHAR, zPCHAR, zPCHAR, zPCHAR, zPCHAR, zPCHAR );
zSHORT CtrlListEnableCtrls( zVIEW, zSHORT );
zSHORT CtrlListSetCheckedState( zVIEW, zVIEW, zLONG );
zSHORT CtrlListEnableButtonsAndCheckbox( zVIEW, zLONG );
zSHORT CtrlListShowAllCtrls( zVIEW, zVIEW );
zSHORT CtrlListSaveStyleFlags( zVIEW, zVIEW );
zSHORT CtrlListDetailWindow( zVIEW, zSHORT );

zOPER_EXPORT zSHORT OPERATION
GOTO_SelectReusableSideMenu( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
REMOVE_DefaultMenuActions( zVIEW     ViewToWindow );


zOPER_EXPORT zSHORT OPERATION
COPY_WindowToClipboard( zVIEW     ViewToWindow );


zOPER_EXPORT zSHORT OPERATION
PASTE_WindowFromClipboard( zVIEW     ViewToWindow );


zOPER_EXPORT zSHORT OPERATION
GOTO_SelectDefaultMenuActions( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
GOTO_SelectReusableMenuActions( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
CONVERT_ClassNames( zVIEW     ViewToWindow );


zOPER_EXPORT zSHORT OPERATION
GOTO_SelectReusableMainMenu( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
GOTO_SelectDefaultMainMenu( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
LOAD_SelectedDialog( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
SELECT_ReusableMenuWindow( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
REMOVE_DefaultMainMenu( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
REMOVE_ReusableSideMenu( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
REMOVE_ReusableMainMenu( zVIEW     vSubtask );


zOPER_EXPORT zSHORT OPERATION
CONVERT_SubControlsForDialog( zVIEW     ViewToWindow );


static zSHORT
o_FixCtrlCtrlAttribsRecursive( zVIEW     vDialog );


zOPER_EXPORT zSHORT OPERATION
CONVERT_ControlClassForWindow( zVIEW     ViewToWindow );


zOPER_EXPORT zSHORT OPERATION
CONVERT_ControlClassForDialog( zVIEW     ViewToWindow );


static zSHORT
o_CONVERT_ClassNamesRecursive( zVIEW     vDialogRoot,
                               zVIEW     vControl );


zOPER_EXPORT zSHORT OPERATION
REMOVE_ReusableMenuActions( zVIEW     ViewToWindow );


//:DIALOG OPERATION
//:GOTO_SelectReusableSideMenu( VIEW vSubtask )

//:   VIEW TZWINDOWL  REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
GOTO_SelectReusableSideMenu( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW TZDLG_List REGISTERED AS TZDLG_List
   zVIEW     TZDLG_List = 0; 
   //:VIEW TZWND_List BASED ON LOD  TZWDLGSO
   zVIEW     TZWND_List = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    lTempInteger_1; 
   zSHORT    lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zLONG     lTempInteger_4; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   RESULT = GetViewByName( &TZDLG_List, "TZDLG_List", vSubtask, zLEVEL_TASK );

   //:TZWINDOWL.Dialog.wReusableSelectEntityName = "ReusableSideWindow"
   SetAttributeFromString( TZWINDOWL, "Dialog", "wReusableSelectEntityName", "ReusableSideWindow" );
   //:IF TZWINDOWL.ReusableWindowSelection EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableWindowSelection" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableWindowSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableWindowSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.ReusableDialogSelection EXISTS
   lTempInteger_1 = CheckExistenceOfEntity( TZWINDOWL, "ReusableDialogSelection" );
   if ( lTempInteger_1 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableDialogSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableDialogSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.ReusableSideWindow EXISTS
   lTempInteger_2 = CheckExistenceOfEntity( TZWINDOWL, "ReusableSideWindow" );
   if ( lTempInteger_2 == 0 )
   { 
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      //:           WHERE TZDLG_List.W_MetaDef.CPLR_ZKey = TZWINDOWL.ReusableSideDialog.ZKey
      GetIntegerFromAttribute( &lTempInteger_3, TZWINDOWL, "ReusableSideDialog", "ZKey" );
      RESULT = SetCursorFirstEntityByInteger( TZDLG_List, "W_MetaDef", "CPLR_ZKey", lTempInteger_3, "" );
      //:IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:INCLUDE TZWINDOWL.ReusableDialogSelection FROM TZDLG_List.W_MetaDef
         RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableDialogSelection", TZDLG_List, "W_MetaDef", zPOS_AFTER );
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:IF TZWND_List.Dialog.ZKey != TZWINDOWL.ReusableSideDialog.ZKey
            if ( CompareAttributeToAttribute( TZWND_List, "Dialog", "ZKey", TZWINDOWL, "ReusableSideDialog", "ZKey" ) != 0 )
            { 
               //:DropMetaOI( vSubtask, TZWND_List )
               DropMetaOI( vSubtask, TZWND_List );
               //:TZWND_List = 0
               TZWND_List = 0;
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:TZWND_List = 0
            TZWND_List = 0;
         } 

         //:END
         //:IF TZWND_List != 0
         if ( TZWND_List != 0 )
         { 
            //:SET CURSOR FIRST TZWND_List.Window
            //:           WHERE TZWND_List.Window.ZKey = TZWINDOWL.ReusableSideWindow.ZKey
            GetIntegerFromAttribute( &lTempInteger_4, TZWINDOWL, "ReusableSideWindow", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( TZWND_List, "Window", "ZKey", lTempInteger_4, "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:INCLUDE TZWINDOWL.ReusableWindowSelection FROM TZWND_List.Window
               RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableWindowSelection", TZWND_List, "Window", zPOS_AFTER );
               //:ELSE
            } 
            else
            { 
               //:SET CURSOR FIRST TZWND_List.Window
               RESULT = SetCursorFirstEntity( TZWND_List, "Window", "" );
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:IF TZDLG_List.W_MetaDef.CPLR_ZKey  = TZWINDOWL.Dialog.ZKey
            if ( CompareAttributeToAttribute( TZDLG_List, "W_MetaDef", "CPLR_ZKey", TZWINDOWL, "Dialog", "ZKey" ) == 0 )
            { 
               //:CreateViewFromView( TZWND_List, TZWINDOWL )
               CreateViewFromView( &TZWND_List, TZWINDOWL );
               //:NAME VIEW TZWND_List "TZWND_List"
               SetNameForView( TZWND_List, "TZWND_List", 0, zLEVEL_TASK );
               //:ELSE
            } 
            else
            { 
               //:ActivateMetaOI( vSubtask, TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE )
               ActivateMetaOI( vSubtask, &TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE );
               //:NAME VIEW TZWND_List "TZWND_List"
               SetNameForView( TZWND_List, "TZWND_List", 0, zLEVEL_TASK );
            } 

            //:END
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:IF TZWINDOWL.Dialog.ZKey = TZWND_List.Dialog.ZKey
            if ( CompareAttributeToAttribute( TZWINDOWL, "Dialog", "ZKey", TZWND_List, "Dialog", "ZKey" ) == 0 )
            { 
               //:DropView( TZWND_List )
               DropView( TZWND_List );
               //:ELSE
            } 
            else
            { 
               //:DropMetaOI( vSubtask, TZWND_List )
               DropMetaOI( vSubtask, TZWND_List );
            } 

            //:END
         } 

         //:END
         //:SET CURSOR FIRST TZDLG_List.W_MetaDef
         RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
      } 

      //:END

      //:ELSE
   } 
   else
   { 

      //:GET VIEW TZWND_List NAMED "TZWND_List"
      RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
      //:IF RESULT >= 0
      if ( RESULT >= 0 )
      { 
         //:IF TZWINDOWL.Dialog.ZKey = TZWND_List.Dialog.ZKey
         if ( CompareAttributeToAttribute( TZWINDOWL, "Dialog", "ZKey", TZWND_List, "Dialog", "ZKey" ) == 0 )
         { 
            //:DropView( TZWND_List )
            DropView( TZWND_List );
            //:ELSE
         } 
         else
         { 
            //:DropMetaOI( vSubtask, TZWND_List )
            DropMetaOI( vSubtask, TZWND_List );
         } 

         //:END
      } 

      //:END
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:REMOVE_DefaultMenuActions( VIEW ViewToWindow )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
REMOVE_DefaultMenuActions( zVIEW     ViewToWindow )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", ViewToWindow, zLEVEL_TASK );

   //:IF TZWINDOWL.DefaultReusableActionWindow EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "DefaultReusableActionWindow" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.DefaultReusableActionWindow
      RESULT = ExcludeEntity( TZWINDOWL, "DefaultReusableActionWindow", zREPOS_AFTER );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:COPY_WindowToClipboard( VIEW ViewToWindow )

//:   VIEW TaskLPLR  REGISTERED AS TaskLPLR
zOPER_EXPORT zSHORT OPERATION
COPY_WindowToClipboard( zVIEW     ViewToWindow )
{
   zVIEW     TaskLPLR = 0; 
   zSHORT    RESULT; 
   //:VIEW TZWINDOWL REGISTERED AS TZWINDOWL
   zVIEW     TZWINDOWL = 0; 

   RESULT = GetViewByName( &TaskLPLR, "TaskLPLR", ViewToWindow, zLEVEL_TASK );
   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", ViewToWindow, zLEVEL_TASK );

   //:// Simply set up the Directory Path and Window Name in TaskLPLR.
   //:// This only allowed for the time being for an external LPLR.
   //:// We determine it is an external LPLR if TaskLPLR.LPLR.wFullyQualifiedFileName is not null.
   //:IF TaskLPLR.LPLR.wFullyQualifiedFileName = ""
   if ( CompareAttributeToString( TaskLPLR, "LPLR", "wFullyQualifiedFileName", "" ) == 0 )
   { 
      //:MessageSend( ViewToWindow, "", "Copy Window to Clipboard",
      //:             "This function is only valid for an external Dialog.",
      //:             zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 )
      MessageSend( ViewToWindow, "", "Copy Window to Clipboard", "This function is only valid for an external Dialog.", zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
      //:SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 )
      SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 );
      //:RETURN -1
      return( -1 );
   } 

   //:END
   //:TaskLPLR.LPLR.wCopyPasteDirectoryFileName = TaskLPLR.LPLR.wFullyQualifiedFileName
   SetAttributeFromAttribute( TaskLPLR, "LPLR", "wCopyPasteDirectoryFileName", TaskLPLR, "LPLR", "wFullyQualifiedFileName" );
   //:TaskLPLR.LPLR.wCopyPasteWindowName        = TZWINDOWL.Window.Tag
   SetAttributeFromAttribute( TaskLPLR, "LPLR", "wCopyPasteWindowName", TZWINDOWL, "Window", "Tag" );
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:PASTE_WindowFromClipboard( VIEW ViewToWindow )

//:   VIEW TaskLPLR     REGISTERED AS TaskLPLR
zOPER_EXPORT zSHORT OPERATION
PASTE_WindowFromClipboard( zVIEW     ViewToWindow )
{
   zVIEW     TaskLPLR = 0; 
   zSHORT    RESULT; 
   //:VIEW TZWINDOWL    REGISTERED AS TZWINDOWL
   zVIEW     TZWINDOWL = 0; 
   //:VIEW SourceDialog BASED ON LOD  TZWDLGSO
   zVIEW     SourceDialog = 0; 
   //:VIEW TargetDialog BASED ON LOD  TZWDLGSO
   zVIEW     TargetDialog = 0; 
   //:STRING ( 200 ) szFileName
   zCHAR     szFileName[ 201 ] = { 0 }; 
   //:STRING ( 32 )  szTag
   zCHAR     szTag[ 33 ] = { 0 }; 
   //:SHORT  nRC
   zSHORT    nRC = 0; 
   zCHAR     szTempString_0[ 255 ]; 

   RESULT = GetViewByName( &TaskLPLR, "TaskLPLR", ViewToWindow, zLEVEL_TASK );
   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", ViewToWindow, zLEVEL_TASK );

   //:// Copy the Window defined in LPLR work attributes wCopyPasteDirectoryName and wCopyPasteWindowName
   //:// into this Dialog.

   //:// Make sure directory and Window have been specified.
   //:IF TaskLPLR.LPLR.wCopyPasteDirectoryFileName = "" OR TaskLPLR.LPLR.wCopyPasteWindowName = ""
   if ( CompareAttributeToString( TaskLPLR, "LPLR", "wCopyPasteDirectoryFileName", "" ) == 0 || CompareAttributeToString( TaskLPLR, "LPLR", "wCopyPasteWindowName", "" ) == 0 )
   { 
      //:MessageSend( ViewToWindow, "", "Paste Window from Clipboard",
      //:             "A window and directory have not been copied to the clipboard.",
      //:             zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 )
      MessageSend( ViewToWindow, "", "Paste Window from Clipboard", "A window and directory have not been copied to the clipboard.", zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
      //:SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 )
      SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 );
      //:RETURN -1
      return( -1 );
   } 

   //:END

   //:// Create view for new window.
   //:CreateViewFromView( TargetDialog, TZWINDOWL )
   CreateViewFromView( &TargetDialog, TZWINDOWL );
   //:NAME VIEW TargetDialog "TargetDialog"
   SetNameForView( TargetDialog, "TargetDialog", 0, zLEVEL_TASK );

   //:// Check for duplicate name of Source window for paste
   //:SET CURSOR FIRST TargetDialog.Window WHERE TargetDialog.Window.Tag = TaskLPLR.LPLR.wCopyPasteWindowName
   GetStringFromAttribute( szTempString_0, zsizeof( szTempString_0 ), TaskLPLR, "LPLR", "wCopyPasteWindowName" );
   RESULT = SetCursorFirstEntityByString( TargetDialog, "Window", "Tag", szTempString_0, "" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:MessageSend( ViewToWindow, "", "Paste Window from Clipboard",
      //:             "A window by the same name as the copied window already exists in the current Dialog.",
      //:             zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 )
      MessageSend( ViewToWindow, "", "Paste Window from Clipboard", "A window by the same name as the copied window already exists in the current Dialog.", zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
      //:SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 )
      SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 );
      //:RETURN -1
      return( -1 );
   } 

   //:END

   //:// Activate original Dialog and position on window.
   //:szFileName = TaskLPLR.LPLR.wCopyPasteDirectoryFileName
   GetVariableFromAttribute( szFileName, 0, 'S', 201, TaskLPLR, "LPLR", "wCopyPasteDirectoryFileName", "", 0 );
   //:nRC = ActivateOI_FromFile( SourceDialog, "TZWDLGSO", ViewToWindow, szFileName, zSINGLE )
   nRC = ActivateOI_FromFile( &SourceDialog, "TZWDLGSO", ViewToWindow, szFileName, zSINGLE );
   //:IF nRC < 0
   if ( nRC < 0 )
   { 
      //:MessageSend( ViewToWindow, "", "Paste Clipboard",
      //:             "The requested Dialog could not be activated.",
      //:             zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 )
      MessageSend( ViewToWindow, "", "Paste Clipboard", "The requested Dialog could not be activated.", zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
      //:SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 )
      SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 );
      //:RETURN -1
      return( -1 );
   } 

   //:END
   //:NAME VIEW SourceDialog "SourceDialog"
   SetNameForView( SourceDialog, "SourceDialog", 0, zLEVEL_TASK );
   //:SET CURSOR FIRST SourceDialog.Window WHERE SourceDialog.Window.Tag = TaskLPLR.LPLR.wCopyPasteWindowName
   GetStringFromAttribute( szTempString_0, zsizeof( szTempString_0 ), TaskLPLR, "LPLR", "wCopyPasteWindowName" );
   RESULT = SetCursorFirstEntityByString( SourceDialog, "Window", "Tag", szTempString_0, "" );

   //:// Go to copy window.
   //:nRC = CloneWindow( TargetDialog, SourceDialog, TaskLPLR, ViewToWindow )
   nRC = oTZWDLGSO_CloneWindow( TargetDialog, SourceDialog, TaskLPLR, ViewToWindow );
   //:IF nRC >= 0
   if ( nRC >= 0 )
   { 
      //:// Re-order window list and enable display of new window.
      //:szTag = TargetDialog.Window.Tag
      GetVariableFromAttribute( szTag, 0, 'S', 33, TargetDialog, "Window", "Tag", "", 0 );
      //:OrderEntityForView( TargetDialog, "Window", "Tag A" )
      OrderEntityForView( TargetDialog, "Window", "Tag A" );
      //:SET CURSOR FIRST TargetDialog.Window WHERE TargetDialog.Window.Tag = szTag
      RESULT = SetCursorFirstEntityByString( TargetDialog, "Window", "Tag", szTag, "" );
      //:fnPainterCall( 11, ViewToWindow, 0, szTag )
      fnPainterCall( 11, ViewToWindow, 0, szTag, zsizeof( szTag ) );
      //:ELSE
   } 
   else
   { 
      //:// An error occurred during copy. Give a message and delete the Window just created.
      //:DELETE ENTITY TargetDialog.Window Previous
      RESULT = DeleteEntity( TargetDialog, "Window", zREPOS_PREV );
      //:MessageSend( ViewToWindow, "", "Paste Clipboard",
      //:             "An Error occurred during the CloneWindow function. The Paste function is aborted.",
      //:             zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 )
      MessageSend( ViewToWindow, "", "Paste Clipboard", "An Error occurred during the CloneWindow function. The Paste function is aborted.", zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
      //:SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 )
      SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 );
      //:RETURN -1
      return( -1 );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:GOTO_SelectDefaultMenuActions( VIEW vSubtask )

//:   VIEW TZWINDOWL  REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
GOTO_SelectDefaultMenuActions( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW TZDLG_List REGISTERED AS TZDLG_List
   zVIEW     TZDLG_List = 0; 
   //:VIEW TZWND_List BASED ON LOD  TZWDLGSO
   zVIEW     TZWND_List = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    lTempInteger_1; 
   zSHORT    lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zLONG     lTempInteger_4; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   RESULT = GetViewByName( &TZDLG_List, "TZDLG_List", vSubtask, zLEVEL_TASK );

   //:TZWINDOWL.Dialog.wReusableSelectEntityName = "DefaultReusableActionWindow"
   SetAttributeFromString( TZWINDOWL, "Dialog", "wReusableSelectEntityName", "DefaultReusableActionWindow" );
   //:IF TZWINDOWL.ReusableWindowSelection EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableWindowSelection" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableWindowSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableWindowSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.ReusableDialogSelection EXISTS
   lTempInteger_1 = CheckExistenceOfEntity( TZWINDOWL, "ReusableDialogSelection" );
   if ( lTempInteger_1 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableDialogSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableDialogSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.DefaultReusableActionWindow EXISTS
   lTempInteger_2 = CheckExistenceOfEntity( TZWINDOWL, "DefaultReusableActionWindow" );
   if ( lTempInteger_2 == 0 )
   { 
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      //:           WHERE TZDLG_List.W_MetaDef.CPLR_ZKey = TZWINDOWL.DefaultReusableActionDialog.ZKey
      GetIntegerFromAttribute( &lTempInteger_3, TZWINDOWL, "DefaultReusableActionDialog", "ZKey" );
      RESULT = SetCursorFirstEntityByInteger( TZDLG_List, "W_MetaDef", "CPLR_ZKey", lTempInteger_3, "" );
      //:IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:INCLUDE TZWINDOWL.ReusableDialogSelection FROM TZDLG_List.W_MetaDef
         RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableDialogSelection", TZDLG_List, "W_MetaDef", zPOS_AFTER );
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:IF TZWND_List.Dialog.ZKey != TZWINDOWL.DefaultReusableActionDialog.ZKey
            if ( CompareAttributeToAttribute( TZWND_List, "Dialog", "ZKey", TZWINDOWL, "DefaultReusableActionDialog", "ZKey" ) != 0 )
            { 
               //:DropMetaOI( vSubtask, TZWND_List )
               DropMetaOI( vSubtask, TZWND_List );
               //:TZWND_List = 0
               TZWND_List = 0;
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:TZWND_List = 0
            TZWND_List = 0;
         } 

         //:END
         //:IF TZWND_List != 0
         if ( TZWND_List != 0 )
         { 
            //:SET CURSOR FIRST TZWND_List.Window
            //:           WHERE TZWND_List.Window.ZKey = TZWINDOWL.DefaultReusableActionWindow.ZKey
            GetIntegerFromAttribute( &lTempInteger_4, TZWINDOWL, "DefaultReusableActionWindow", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( TZWND_List, "Window", "ZKey", lTempInteger_4, "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:INCLUDE TZWINDOWL.ReusableWindowSelection FROM TZWND_List.Window
               RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableWindowSelection", TZWND_List, "Window", zPOS_AFTER );
               //:ELSE
            } 
            else
            { 
               //:SET CURSOR FIRST TZWND_List.Window
               RESULT = SetCursorFirstEntity( TZWND_List, "Window", "" );
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:ActivateMetaOI( vSubtask, TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE )
            ActivateMetaOI( vSubtask, &TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE );
            //:NAME VIEW TZWND_List "TZWND_List"
            SetNameForView( TZWND_List, "TZWND_List", 0, zLEVEL_TASK );
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:DropMetaOI( vSubtask, TZWND_List )
            DropMetaOI( vSubtask, TZWND_List );
         } 

         //:END
         //:SET CURSOR FIRST TZDLG_List.W_MetaDef
         RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
      } 

      //:END

      //:ELSE
   } 
   else
   { 

      //:GET VIEW TZWND_List NAMED "TZWND_List"
      RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
      //:IF RESULT >= 0
      if ( RESULT >= 0 )
      { 
         //:DropMetaOI( vSubtask, TZWND_List )
         DropMetaOI( vSubtask, TZWND_List );
      } 

      //:END
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:GOTO_SelectReusableMenuActions( VIEW vSubtask )


//:   VIEW TZWINDOWL  REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
GOTO_SelectReusableMenuActions( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW TZDLG_List REGISTERED AS TZDLG_List
   zVIEW     TZDLG_List = 0; 
   //:VIEW TZWND_List BASED ON LOD  TZWDLGSO
   zVIEW     TZWND_List = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    lTempInteger_1; 
   zSHORT    lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zLONG     lTempInteger_4; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   RESULT = GetViewByName( &TZDLG_List, "TZDLG_List", vSubtask, zLEVEL_TASK );

   //:TZWINDOWL.Dialog.wReusableSelectEntityName = "ReusableActionWindow"
   SetAttributeFromString( TZWINDOWL, "Dialog", "wReusableSelectEntityName", "ReusableActionWindow" );
   //:IF TZWINDOWL.ReusableWindowSelection EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableWindowSelection" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableWindowSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableWindowSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.ReusableDialogSelection EXISTS
   lTempInteger_1 = CheckExistenceOfEntity( TZWINDOWL, "ReusableDialogSelection" );
   if ( lTempInteger_1 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableDialogSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableDialogSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.ReusableActionWindow EXISTS
   lTempInteger_2 = CheckExistenceOfEntity( TZWINDOWL, "ReusableActionWindow" );
   if ( lTempInteger_2 == 0 )
   { 
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      //:           WHERE TZDLG_List.W_MetaDef.CPLR_ZKey = TZWINDOWL.ReusableActionDialog.ZKey
      GetIntegerFromAttribute( &lTempInteger_3, TZWINDOWL, "ReusableActionDialog", "ZKey" );
      RESULT = SetCursorFirstEntityByInteger( TZDLG_List, "W_MetaDef", "CPLR_ZKey", lTempInteger_3, "" );
      //:IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:INCLUDE TZWINDOWL.ReusableDialogSelection FROM TZDLG_List.W_MetaDef
         RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableDialogSelection", TZDLG_List, "W_MetaDef", zPOS_AFTER );
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:IF TZWND_List.Dialog.ZKey != TZWINDOWL.ReusableActionDialog.ZKey
            if ( CompareAttributeToAttribute( TZWND_List, "Dialog", "ZKey", TZWINDOWL, "ReusableActionDialog", "ZKey" ) != 0 )
            { 
               //:DropMetaOI( vSubtask, TZWND_List )
               DropMetaOI( vSubtask, TZWND_List );
               //:TZWND_List = 0
               TZWND_List = 0;
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:TZWND_List = 0
            TZWND_List = 0;
         } 

         //:END
         //:IF TZWND_List != 0
         if ( TZWND_List != 0 )
         { 
            //:SET CURSOR FIRST TZWND_List.Window
            //:           WHERE TZWND_List.Window.ZKey = TZWINDOWL.ReusableActionWindow.ZKey
            GetIntegerFromAttribute( &lTempInteger_4, TZWINDOWL, "ReusableActionWindow", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( TZWND_List, "Window", "ZKey", lTempInteger_4, "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:INCLUDE TZWINDOWL.ReusableWindowSelection FROM TZWND_List.Window
               RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableWindowSelection", TZWND_List, "Window", zPOS_AFTER );
               //:ELSE
            } 
            else
            { 
               //:SET CURSOR FIRST TZWND_List.Window
               RESULT = SetCursorFirstEntity( TZWND_List, "Window", "" );
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:ActivateMetaOI( vSubtask, TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE )
            ActivateMetaOI( vSubtask, &TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE );
            //:NAME VIEW TZWND_List "TZWND_List"
            SetNameForView( TZWND_List, "TZWND_List", 0, zLEVEL_TASK );
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:DropMetaOI( vSubtask, TZWND_List )
            DropMetaOI( vSubtask, TZWND_List );
         } 

         //:END
         //:SET CURSOR FIRST TZDLG_List.W_MetaDef
         RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
      } 

      //:END

      //:ELSE
   } 
   else
   { 

      //:GET VIEW TZWND_List NAMED "TZWND_List"
      RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
      //:IF RESULT >= 0
      if ( RESULT >= 0 )
      { 
         //:DropMetaOI( vSubtask, TZWND_List )
         DropMetaOI( vSubtask, TZWND_List );
      } 

      //:END
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:CONVERT_ClassNames( VIEW ViewToWindow )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
CONVERT_ClassNames( zVIEW     ViewToWindow )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW vDialog   BASED ON LOD  TZWDLGSO
   zVIEW     vDialog = 0; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", ViewToWindow, zLEVEL_TASK );

   //:// Based on the Convert Type, convert Class Names for either the Dialog of the Window.
   //:CreateViewFromView( vDialog, TZWINDOWL )
   CreateViewFromView( &vDialog, TZWINDOWL );
   //:IF TZWINDOWL.Dialog.wClassNameConvertType = "D"
   if ( CompareAttributeToString( TZWINDOWL, "Dialog", "wClassNameConvertType", "D" ) == 0 )
   { 
      //:FOR EACH vDialog.Window
      RESULT = SetCursorFirstEntity( vDialog, "Window", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:CONVERT_ClassNamesRecursive( TZWINDOWL, vDialog )
         o_CONVERT_ClassNamesRecursive( TZWINDOWL, vDialog );
         RESULT = SetCursorNextEntity( vDialog, "Window", "" );
      } 

      //:END
      //:ELSE
   } 
   else
   { 
      //:CONVERT_ClassNamesRecursive( TZWINDOWL, vDialog )
      o_CONVERT_ClassNamesRecursive( TZWINDOWL, vDialog );
   } 

   //:END
   //:DropView( vDialog )
   DropView( vDialog );
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:GOTO_SelectReusableMainMenu( VIEW vSubtask )

//:   VIEW TZWINDOWL  REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
GOTO_SelectReusableMainMenu( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW TZDLG_List REGISTERED AS TZDLG_List
   zVIEW     TZDLG_List = 0; 
   //:VIEW TZWND_List BASED ON LOD  TZWDLGSO
   zVIEW     TZWND_List = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    lTempInteger_1; 
   zSHORT    lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zLONG     lTempInteger_4; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   RESULT = GetViewByName( &TZDLG_List, "TZDLG_List", vSubtask, zLEVEL_TASK );

   //:TZWINDOWL.Dialog.wReusableSelectEntityName = "ReusableMainWindow"
   SetAttributeFromString( TZWINDOWL, "Dialog", "wReusableSelectEntityName", "ReusableMainWindow" );
   //:IF TZWINDOWL.ReusableWindowSelection EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableWindowSelection" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableWindowSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableWindowSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.ReusableDialogSelection EXISTS
   lTempInteger_1 = CheckExistenceOfEntity( TZWINDOWL, "ReusableDialogSelection" );
   if ( lTempInteger_1 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableDialogSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableDialogSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.ReusableMainWindow EXISTS
   lTempInteger_2 = CheckExistenceOfEntity( TZWINDOWL, "ReusableMainWindow" );
   if ( lTempInteger_2 == 0 )
   { 
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      //:           WHERE TZDLG_List.W_MetaDef.CPLR_ZKey = TZWINDOWL.ReusableMainDialog.ZKey
      GetIntegerFromAttribute( &lTempInteger_3, TZWINDOWL, "ReusableMainDialog", "ZKey" );
      RESULT = SetCursorFirstEntityByInteger( TZDLG_List, "W_MetaDef", "CPLR_ZKey", lTempInteger_3, "" );
      //:IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:INCLUDE TZWINDOWL.ReusableDialogSelection FROM TZDLG_List.W_MetaDef
         RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableDialogSelection", TZDLG_List, "W_MetaDef", zPOS_AFTER );
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:IF TZWND_List.Dialog.ZKey != TZWINDOWL.ReusableMainDialog.ZKey
            if ( CompareAttributeToAttribute( TZWND_List, "Dialog", "ZKey", TZWINDOWL, "ReusableMainDialog", "ZKey" ) != 0 )
            { 
               //:DropMetaOI( vSubtask, TZWND_List )
               DropMetaOI( vSubtask, TZWND_List );
               //:TZWND_List = 0
               TZWND_List = 0;
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:TZWND_List = 0
            TZWND_List = 0;
         } 

         //:END
         //:IF TZWND_List != 0
         if ( TZWND_List != 0 )
         { 
            //:SET CURSOR FIRST TZWND_List.Window
            //:           WHERE TZWND_List.Window.ZKey = TZWINDOWL.ReusableMainWindow.ZKey
            GetIntegerFromAttribute( &lTempInteger_4, TZWINDOWL, "ReusableMainWindow", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( TZWND_List, "Window", "ZKey", lTempInteger_4, "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:INCLUDE TZWINDOWL.ReusableWindowSelection FROM TZWND_List.Window
               RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableWindowSelection", TZWND_List, "Window", zPOS_AFTER );
               //:ELSE
            } 
            else
            { 
               //:SET CURSOR FIRST TZWND_List.Window
               RESULT = SetCursorFirstEntity( TZWND_List, "Window", "" );
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:ActivateMetaOI( vSubtask, TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE )
            ActivateMetaOI( vSubtask, &TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE );
            //:NAME VIEW TZWND_List "TZWND_List"
            SetNameForView( TZWND_List, "TZWND_List", 0, zLEVEL_TASK );
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:DropMetaOI( vSubtask, TZWND_List )
            DropMetaOI( vSubtask, TZWND_List );
         } 

         //:END
         //:SET CURSOR FIRST TZDLG_List.W_MetaDef
         RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
      } 

      //:END

      //:ELSE
   } 
   else
   { 

      //:GET VIEW TZWND_List NAMED "TZWND_List"
      RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
      //:IF RESULT >= 0
      if ( RESULT >= 0 )
      { 
         //:DropMetaOI( vSubtask, TZWND_List )
         DropMetaOI( vSubtask, TZWND_List );
      } 

      //:END
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:GOTO_SelectDefaultMainMenu( VIEW vSubtask )

//:   VIEW TZWINDOWL  REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
GOTO_SelectDefaultMainMenu( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW TZDLG_List REGISTERED AS TZDLG_List
   zVIEW     TZDLG_List = 0; 
   //:VIEW TZWND_List BASED ON LOD  TZWDLGSO
   zVIEW     TZWND_List = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    lTempInteger_1; 
   zSHORT    lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zLONG     lTempInteger_4; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   RESULT = GetViewByName( &TZDLG_List, "TZDLG_List", vSubtask, zLEVEL_TASK );

   //:TZWINDOWL.Dialog.wReusableSelectEntityName = "DefaultReusableMainWindow"
   SetAttributeFromString( TZWINDOWL, "Dialog", "wReusableSelectEntityName", "DefaultReusableMainWindow" );
   //:IF TZWINDOWL.ReusableWindowSelection EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableWindowSelection" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableWindowSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableWindowSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.ReusableDialogSelection EXISTS
   lTempInteger_1 = CheckExistenceOfEntity( TZWINDOWL, "ReusableDialogSelection" );
   if ( lTempInteger_1 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableDialogSelection
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableDialogSelection", zREPOS_AFTER );
   } 

   //:END
   //:IF TZWINDOWL.DefaultReusableMainWindow EXISTS
   lTempInteger_2 = CheckExistenceOfEntity( TZWINDOWL, "DefaultReusableMainWindow" );
   if ( lTempInteger_2 == 0 )
   { 
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      //:           WHERE TZDLG_List.W_MetaDef.CPLR_ZKey = TZWINDOWL.ReusableMainDialog.ZKey
      GetIntegerFromAttribute( &lTempInteger_3, TZWINDOWL, "ReusableMainDialog", "ZKey" );
      RESULT = SetCursorFirstEntityByInteger( TZDLG_List, "W_MetaDef", "CPLR_ZKey", lTempInteger_3, "" );
      //:IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:INCLUDE TZWINDOWL.ReusableDialogSelection FROM TZDLG_List.W_MetaDef
         RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableDialogSelection", TZDLG_List, "W_MetaDef", zPOS_AFTER );
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:IF TZWND_List.Dialog.ZKey != TZWINDOWL.ReusableMainDialog.ZKey
            if ( CompareAttributeToAttribute( TZWND_List, "Dialog", "ZKey", TZWINDOWL, "ReusableMainDialog", "ZKey" ) != 0 )
            { 
               //:DropMetaOI( vSubtask, TZWND_List )
               DropMetaOI( vSubtask, TZWND_List );
               //:TZWND_List = 0
               TZWND_List = 0;
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:TZWND_List = 0
            TZWND_List = 0;
         } 

         //:END
         //:IF TZWND_List != 0
         if ( TZWND_List != 0 )
         { 
            //:SET CURSOR FIRST TZWND_List.Window
            //:           WHERE TZWND_List.Window.ZKey = TZWINDOWL.DefaultReusableMainWindow.ZKey
            GetIntegerFromAttribute( &lTempInteger_4, TZWINDOWL, "DefaultReusableMainWindow", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( TZWND_List, "Window", "ZKey", lTempInteger_4, "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:INCLUDE TZWINDOWL.ReusableWindowSelection FROM TZWND_List.Window
               RESULT = IncludeSubobjectFromSubobject( TZWINDOWL, "ReusableWindowSelection", TZWND_List, "Window", zPOS_AFTER );
               //:ELSE
            } 
            else
            { 
               //:SET CURSOR FIRST TZWND_List.Window
               RESULT = SetCursorFirstEntity( TZWND_List, "Window", "" );
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:ActivateMetaOI( vSubtask, TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE )
            ActivateMetaOI( vSubtask, &TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE );
            //:NAME VIEW TZWND_List "TZWND_List"
            SetNameForView( TZWND_List, "TZWND_List", 0, zLEVEL_TASK );
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:GET VIEW TZWND_List NAMED "TZWND_List"
         RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
         //:IF RESULT >= 0
         if ( RESULT >= 0 )
         { 
            //:DropMetaOI( vSubtask, TZWND_List )
            DropMetaOI( vSubtask, TZWND_List );
         } 

         //:END
         //:SET CURSOR FIRST TZDLG_List.W_MetaDef
         RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
      } 

      //:END

      //:ELSE
   } 
   else
   { 

      //:GET VIEW TZWND_List NAMED "TZWND_List"
      RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
      //:IF RESULT >= 0
      if ( RESULT >= 0 )
      { 
         //:DropMetaOI( vSubtask, TZWND_List )
         DropMetaOI( vSubtask, TZWND_List );
      } 

      //:END
      //:SET CURSOR FIRST TZDLG_List.W_MetaDef
      RESULT = SetCursorFirstEntity( TZDLG_List, "W_MetaDef", "" );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:LOAD_SelectedDialog( VIEW vSubtask )

//:   VIEW TZWINDOWL  REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
LOAD_SelectedDialog( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW TZDLG_List REGISTERED AS TZDLG_List
   zVIEW     TZDLG_List = 0; 
   //:VIEW TZWND_List BASED ON LOD  TZWDLGSO
   zVIEW     TZWND_List = 0; 
   zSHORT    lTempInteger_0; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   RESULT = GetViewByName( &TZDLG_List, "TZDLG_List", vSubtask, zLEVEL_TASK );

   //:// Make sure that TZWND_List is set up for the Dialog.
   //:GET VIEW TZWND_List NAMED "TZWND_List"
   RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );
   //:IF RESULT >= 0
   if ( RESULT >= 0 )
   { 
      //:IF TZWND_List.Dialog.ZKey != TZDLG_List.W_MetaDef.CPLR_ZKey
      if ( CompareAttributeToAttribute( TZWND_List, "Dialog", "ZKey", TZDLG_List, "W_MetaDef", "CPLR_ZKey" ) != 0 )
      { 
         //:IF TZWINDOWL.Dialog.ZKey = TZWND_List.Dialog.ZKey
         if ( CompareAttributeToAttribute( TZWINDOWL, "Dialog", "ZKey", TZWND_List, "Dialog", "ZKey" ) == 0 )
         { 
            //:DropView( TZWND_List )
            DropView( TZWND_List );
            //:ELSE
         } 
         else
         { 
            //:DropMetaOI( vSubtask, TZWND_List )
            DropMetaOI( vSubtask, TZWND_List );
         } 

         //:END
         //:TZWND_List = 0
         TZWND_List = 0;
      } 

      //:END
      //:ELSE
   } 
   else
   { 
      //:TZWND_List = 0
      TZWND_List = 0;
   } 

   //:END
   //:IF TZWND_List = 0
   if ( TZWND_List == 0 )
   { 
      //:IF TZDLG_List.W_MetaDef.CPLR_ZKey = TZWINDOWL.Dialog.ZKey
      if ( CompareAttributeToAttribute( TZDLG_List, "W_MetaDef", "CPLR_ZKey", TZWINDOWL, "Dialog", "ZKey" ) == 0 )
      { 
         //:CreateViewFromView( TZWND_List, TZWINDOWL )
         CreateViewFromView( &TZWND_List, TZWINDOWL );
         //:NAME VIEW TZWND_List "TZWND_List"
         SetNameForView( TZWND_List, "TZWND_List", 0, zLEVEL_TASK );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI( vSubtask, TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE )
         ActivateMetaOI( vSubtask, &TZWND_List, TZDLG_List, zREFER_DIALOG_META, zSINGLE );
         //:NAME VIEW TZWND_List "TZWND_List"
         SetNameForView( TZWND_List, "TZWND_List", 0, zLEVEL_TASK );
      } 

      //:END
   } 

   //:END
   //:SET CURSOR FIRST TZWND_List.Window
   RESULT = SetCursorFirstEntity( TZWND_List, "Window", "" );

   //:// Make sure that the ReusableWindowSelection isn't included.
   //:IF TZWINDOWL.ReusableWindowSelection EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableWindowSelection" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableWindowSelection NONE
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableWindowSelection", zREPOS_NONE );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:SELECT_ReusableMenuWindow( VIEW vSubtask )

//:   VIEW TZWINDOWL  REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
SELECT_ReusableMenuWindow( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW TZDLG_List REGISTERED AS TZDLG_List
   zVIEW     TZDLG_List = 0; 
   //:VIEW TZWND_List REGISTERED AS TZWND_List
   zVIEW     TZWND_List = 0; 
   //:STRING ( 32 ) IncludeEntityName
   zCHAR     IncludeEntityName[ 33 ] = { 0 }; 
   //:SHORT         nRC
   zSHORT    nRC = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    lTempInteger_1; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );
   RESULT = GetViewByName( &TZDLG_List, "TZDLG_List", vSubtask, zLEVEL_TASK );
   RESULT = GetViewByName( &TZWND_List, "TZWND_List", vSubtask, zLEVEL_TASK );

   //:IF TZWINDOWL.ReusableWindowSelection DOES NOT EXIST OR
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableWindowSelection" );
   //:   TZWINDOWL.ReusableDialogSelection DOES NOT EXIST
   lTempInteger_1 = CheckExistenceOfEntity( TZWINDOWL, "ReusableDialogSelection" );
   if ( lTempInteger_0 != 0 || lTempInteger_1 != 0 )
   { 

      //:MessageSend( vSubtask, "", "Select Reusable Menu",
      //:             "A Dialog or Window has not been selected.",
      //:             zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 )
      MessageSend( vSubtask, "", "Select Reusable Menu", "A Dialog or Window has not been selected.", zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
      //:SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 )
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      //:RETURN -1
      return( -1 );
   } 

   //:END
   //:IncludeEntityName = TZWINDOWL.Dialog.wReusableSelectEntityName
   GetVariableFromAttribute( IncludeEntityName, 0, 'S', 33, TZWINDOWL, "Dialog", "wReusableSelectEntityName", "", 0 );
   //:nRC = CheckExistenceOfEntity( TZWINDOWL, IncludeEntityName )
   nRC = CheckExistenceOfEntity( TZWINDOWL, IncludeEntityName );
   //:IF nRC >= 0
   if ( nRC >= 0 )
   { 
      //:ExcludeEntity( TZWINDOWL, IncludeEntityName, zREPOS_NONE )
      ExcludeEntity( TZWINDOWL, IncludeEntityName, zREPOS_NONE );
   } 

   //:END
   //:IncludeSubobjectFromSubobject( TZWINDOWL, IncludeEntityName, TZWND_List, "Window", zPOS_AFTER )
   IncludeSubobjectFromSubobject( TZWINDOWL, IncludeEntityName, TZWND_List, "Window", zPOS_AFTER );
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:REMOVE_DefaultMainMenu( VIEW vSubtask )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
REMOVE_DefaultMainMenu( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   //:IF TZWINDOWL.DefaultReusableMainWindow EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "DefaultReusableMainWindow" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.DefaultReusableMainWindow
      RESULT = ExcludeEntity( TZWINDOWL, "DefaultReusableMainWindow", zREPOS_AFTER );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:REMOVE_ReusableSideMenu( VIEW vSubtask )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
REMOVE_ReusableSideMenu( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   //:IF TZWINDOWL.ReusableSideWindow EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableSideWindow" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableSideWindow
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableSideWindow", zREPOS_AFTER );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:REMOVE_ReusableMainMenu( VIEW vSubtask )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
REMOVE_ReusableMainMenu( zVIEW     vSubtask )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", vSubtask, zLEVEL_TASK );

   //:IF TZWINDOWL.ReusableMainWindow EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableMainWindow" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableMainWindow
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableMainWindow", zREPOS_AFTER );
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:CONVERT_SubControlsForDialog( VIEW ViewToWindow )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
CONVERT_SubControlsForDialog( zVIEW     ViewToWindow )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   //:VIEW vDialog   BASED ON LOD  TZWDLGSO
   zVIEW     vDialog = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    lTempInteger_1; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", ViewToWindow, zLEVEL_TASK );

   //:IF OperatorPrompt( ViewToWindow, "Generate JSP",
   //:                     "Are you sure you want to continue??. Do not if you don't know what this is!!", 1, zBUTTONS_YESNO,
   //:                     zRESPONSE_YES, zICON_QUESTION ) = zRESPONSE_NO
   lTempInteger_0 = OperatorPrompt( ViewToWindow, "Generate JSP", "Are you sure you want to continue??. Do not if you don't know what this is!!", 1, zBUTTONS_YESNO, zRESPONSE_YES, zICON_QUESTION );
   if ( lTempInteger_0 == zRESPONSE_NO )
   { 
      //: RETURN -1
      return( -1 );
   } 

   //:END


   //:// Based on the Convert Type, convert Class Names for either the Dialog of the Window.
   //:CreateViewFromView( vDialog, TZWINDOWL )
   CreateViewFromView( &vDialog, TZWINDOWL );

   //:IF vDialog.Dialog.Converted = ""
   if ( CompareAttributeToString( vDialog, "Dialog", "Converted", "" ) == 0 )
   { 

      //:// Indicate that the Class Conversion is for all Windows in the Dialog.
      //:FOR EACH vDialog.Window
      RESULT = SetCursorFirstEntity( vDialog, "Window", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 

         //:// Process each Control
         //:FOR EACH vDialog.Control
         RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
         while ( RESULT > zCURSOR_UNCHANGED )
         { 

            //:IF vDialog.CtrlCtrl EXISTS
            lTempInteger_1 = CheckExistenceOfEntity( vDialog, "CtrlCtrl" );
            if ( lTempInteger_1 == 0 )
            { 
               //:// Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
               //:SetViewToSubobject( vDialog, "CtrlCtrl" )
               SetViewToSubobject( vDialog, "CtrlCtrl" );
               //:FixCtrlCtrlAttribsRecursive( vDialog )
               o_FixCtrlCtrlAttribsRecursive( vDialog );
               //:ResetViewFromSubobject( vDialog )
               ResetViewFromSubobject( vDialog );
            } 

            RESULT = SetCursorNextEntity( vDialog, "Control", "" );
            //:END
         } 

         RESULT = SetCursorNextEntity( vDialog, "Window", "" );

         //:END
      } 

      //:END
      //:vDialog.Dialog.Converted = "Y"
      SetAttributeFromString( vDialog, "Dialog", "Converted", "Y" );
   } 

   //:END
   //:DropView( vDialog )
   DropView( vDialog );
   return( 0 );
// END
} 


//:LOCAL OPERATION
static zSHORT
o_FixCtrlCtrlAttribsRecursive( zVIEW     vDialog )
{
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 

   //:FixCtrlCtrlAttribsRecursive( VIEW vDialog BASED ON LOD  TZWDLGSO )

   //:// Process each Control
   //:// Converting the fields to the correct field.
   //:// I realize this is only for applications that have been built since I made
   //:// changes to tzwdlgso adding WebHTML5 attriutes etc. Like ZENCAS files that
   //:// are older would not have this issue!
   //:FOR EACH vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 

      //:IF vDialog.Control.WebCtrlLabelLink != ""
      if ( CompareAttributeToString( vDialog, "Control", "WebCtrlLabelLink", "" ) != 0 )
      { 
         //:vDialog.Control.WebPlaceholder = vDialog.Control.WebCtrlLabelLink
         SetAttributeFromAttribute( vDialog, "Control", "WebPlaceholder", vDialog, "Control", "WebCtrlLabelLink" );
         //:vDialog.Control.WebCtrlLabelLink = ""
         SetAttributeFromString( vDialog, "Control", "WebCtrlLabelLink", "" );
      } 

      //:END
      //:IF vDialog.Control.WebNoGridDataMessage != ""
      if ( CompareAttributeToString( vDialog, "Control", "WebNoGridDataMessage", "" ) != 0 )
      { 
         //:vDialog.Control.WebCtrlLabelLink = vDialog.Control.WebNoGridDataMessage
         SetAttributeFromAttribute( vDialog, "Control", "WebCtrlLabelLink", vDialog, "Control", "WebNoGridDataMessage" );
         //:vDialog.Control.WebNoGridDataMessage = ""
         SetAttributeFromString( vDialog, "Control", "WebNoGridDataMessage", "" );
      } 

      //:END
      //:IF vDialog.Control.WebNoGridDataMsgClass != ""
      if ( CompareAttributeToString( vDialog, "Control", "WebNoGridDataMsgClass", "" ) != 0 )
      { 
         //:vDialog.Control.WebSelectSetName = vDialog.Control.WebNoGridDataMsgClass
         SetAttributeFromAttribute( vDialog, "Control", "WebSelectSetName", vDialog, "Control", "WebNoGridDataMsgClass" );
         //:vDialog.Control.WebNoGridDataMsgClass = ""
         SetAttributeFromString( vDialog, "Control", "WebNoGridDataMsgClass", "" );
      } 

      //:END
      //:IF vDialog.Control.WebreCAPTCHAPublicKey != ""
      if ( CompareAttributeToString( vDialog, "Control", "WebreCAPTCHAPublicKey", "" ) != 0 )
      { 
         //:vDialog.Control.WebNoGridDataMessage = vDialog.Control.WebreCAPTCHAPublicKey
         SetAttributeFromAttribute( vDialog, "Control", "WebNoGridDataMessage", vDialog, "Control", "WebreCAPTCHAPublicKey" );
         //:vDialog.Control.WebreCAPTCHAPublicKey = ""
         SetAttributeFromString( vDialog, "Control", "WebreCAPTCHAPublicKey", "" );
      } 

      //:END
      //:IF vDialog.Control.WebreCAPTCHAPrivateKey  != ""
      if ( CompareAttributeToString( vDialog, "Control", "WebreCAPTCHAPrivateKey", "" ) != 0 )
      { 
         //:vDialog.Control.WebNoGridDataMsgClass = vDialog.Control.WebreCAPTCHAPrivateKey
         SetAttributeFromAttribute( vDialog, "Control", "WebNoGridDataMsgClass", vDialog, "Control", "WebreCAPTCHAPrivateKey" );
         //:vDialog.Control.WebreCAPTCHAPrivateKey = ""
         SetAttributeFromString( vDialog, "Control", "WebreCAPTCHAPrivateKey", "" );
      } 

      //:END
      //:IF vDialog.Control.NLS_DIL_Text != ""
      if ( CompareAttributeToString( vDialog, "Control", "NLS_DIL_Text", "" ) != 0 )
      { 
         //:vDialog.Control.WebHTML5Attribute = vDialog.Control.NLS_DIL_Text
         SetAttributeFromAttribute( vDialog, "Control", "WebHTML5Attribute", vDialog, "Control", "NLS_DIL_Text" );
         //:vDialog.Control.NLS_DIL_Text = ""
         SetAttributeFromString( vDialog, "Control", "NLS_DIL_Text", "" );
      } 

      //:END

      //:IF vDialog.CtrlCtrl EXISTS
      lTempInteger_0 = CheckExistenceOfEntity( vDialog, "CtrlCtrl" );
      if ( lTempInteger_0 == 0 )
      { 
         //:// Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
         //:SetViewToSubobject( vDialog, "CtrlCtrl" )
         SetViewToSubobject( vDialog, "CtrlCtrl" );
         //:FixCtrlCtrlAttribsRecursive( vDialog )
         o_FixCtrlCtrlAttribsRecursive( vDialog );
         //:ResetViewFromSubobject( vDialog )
         ResetViewFromSubobject( vDialog );
      } 

      RESULT = SetCursorNextEntity( vDialog, "Control", "" );
      //:END
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:CONVERT_ControlClassForWindow( VIEW ViewToWindow )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
CONVERT_ControlClassForWindow( zVIEW     ViewToWindow )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", ViewToWindow, zLEVEL_TASK );

   //:// Indicate that the Class Conversion is for all Windows in the Dialog.
   //:TZWINDOWL.Dialog.wClassNameConvertType = "W"
   SetAttributeFromString( TZWINDOWL, "Dialog", "wClassNameConvertType", "W" );
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:CONVERT_ControlClassForDialog( VIEW ViewToWindow )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
CONVERT_ControlClassForDialog( zVIEW     ViewToWindow )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", ViewToWindow, zLEVEL_TASK );

   //:// Indicate that the Class Conversion is for all Windows in the Dialog.
   //:TZWINDOWL.Dialog.wClassNameConvertType = "D"
   SetAttributeFromString( TZWINDOWL, "Dialog", "wClassNameConvertType", "D" );
   return( 0 );
// END
} 


//:LOCAL OPERATION
//:CONVERT_ClassNamesRecursive( VIEW vDialogRoot BASED ON LOD  TZWDLGSO,
//:                             VIEW vControl    BASED ON LOD  TZWDLGSO )

//:   STRING ( 32 ) OriginalClassName
static zSHORT
o_CONVERT_ClassNamesRecursive( zVIEW     vDialogRoot,
                               zVIEW     vControl )
{
   zCHAR     OriginalClassName[ 33 ] = { 0 }; 
   //:STRING ( 32 ) NewClassName
   zCHAR     NewClassName[ 33 ] = { 0 }; 
   //:STRING ( 256 ) CSS_Class
   zCHAR     CSS_Class[ 257 ] = { 0 }; 
   //:SHORT  nReplaceCnt
   zSHORT    nReplaceCnt = 0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 


   //:// Convert the Control Class Names.
   //:OriginalClassName = vDialogRoot.Dialog.wOriginalClassName
   GetVariableFromAttribute( OriginalClassName, 0, 'S', 33, vDialogRoot, "Dialog", "wOriginalClassName", "", 0 );
   //:NewClassName      = vDialogRoot.Dialog.wNewClassName
   GetVariableFromAttribute( NewClassName, 0, 'S', 33, vDialogRoot, "Dialog", "wNewClassName", "", 0 );
   //:FOR EACH vControl.Control
   RESULT = SetCursorFirstEntity( vControl, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:CSS_Class = vControl.Control.CSS_Class
      GetVariableFromAttribute( CSS_Class, 0, 'S', 257, vControl, "Control", "CSS_Class", "", 0 );
      //:nReplaceCnt = zSearchAndReplaceWord( CSS_Class, 256,
      //:                                     OriginalClassName, NewClassName,
      //:                                     "" ) // " \t\r\n" alway in delimiter list
      nReplaceCnt = zSearchAndReplaceWord( CSS_Class, 256, OriginalClassName, NewClassName, "" );
      //:IF nReplaceCnt > 0
      if ( nReplaceCnt > 0 )
      { 
         //:vControl.Control.CSS_Class = CSS_Class
         SetAttributeFromString( vControl, "Control", "CSS_Class", CSS_Class );
      } 

      //:END
      //:IF vControl.CtrlCtrl EXISTS
      lTempInteger_0 = CheckExistenceOfEntity( vControl, "CtrlCtrl" );
      if ( lTempInteger_0 == 0 )
      { 
         //:SetViewToSubobject( vControl, "CtrlCtrl" )
         SetViewToSubobject( vControl, "CtrlCtrl" );
         //:CONVERT_ClassNamesRecursive( vDialogRoot, vControl )
         o_CONVERT_ClassNamesRecursive( vDialogRoot, vControl );
         //:ResetViewFromSubobject( vControl )
         ResetViewFromSubobject( vControl );
      } 

      RESULT = SetCursorNextEntity( vControl, "Control", "" );
      //:END
   } 

   //:END
   return( 0 );
// END
} 


//:DIALOG OPERATION
//:REMOVE_ReusableMenuActions( VIEW ViewToWindow )

//:   VIEW TZWINDOWL REGISTERED AS TZWINDOWL
zOPER_EXPORT zSHORT OPERATION
REMOVE_ReusableMenuActions( zVIEW     ViewToWindow )
{
   zVIEW     TZWINDOWL = 0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 

   RESULT = GetViewByName( &TZWINDOWL, "TZWINDOWL", ViewToWindow, zLEVEL_TASK );

   //:IF TZWINDOWL.ReusableActionWindow EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( TZWINDOWL, "ReusableActionWindow" );
   if ( lTempInteger_0 == 0 )
   { 
      //:EXCLUDE TZWINDOWL.ReusableActionWindow
      RESULT = ExcludeEntity( TZWINDOWL, "ReusableActionWindow", zREPOS_AFTER );
   } 

   //:END
   return( 0 );
// END
} 


 
#ifdef __cplusplus
}
#endif
