#define KZSYSSVC_INCL
#include "KZOENGAA.H" 
#include "ZDRVROPR.H" 
#include "TZVMLIP.H" 
#include "TZ__OPRS.H" 
 
#ifdef __cplusplus
extern "C"
{
#endif
 
#include "ZEIDONOP.H"

static zLONG
oTZWDLGSO_GenJSP_DownloadFile( zVIEW     vDialog,
                               zPCHAR    szDownloadFileName );


static zSHORT
oTZWDLGSO_GenJSP_FindTAB( zVIEW     vWindow );


static zLONG
oTZWDLGSO_FlagUsedViewsGetFocusR( zVIEW     vDialog,
                                  zVIEW     vDialogRoot,
                                  zPCHAR    szFocusCtrlTag,
                                  zLONG     lTabIndex,
                                  zPCHAR    szWysiwygEditor );


//:TRANSFORMATION OPERATION
//:GenerateJSP( VIEW vDialog BASED ON LOD TZWDLGSO,
//:             VIEW vSubtask )

//:   VIEW vLPLR        BASED ON LOD TZCMLPLO
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_GenerateJSP( zVIEW     vDialog,
                       zVIEW     vSubtask )
{
   zVIEW     vLPLR = 0; 
   //:VIEW vDialogRoot  BASED ON LOD TZWDLGSO
   zVIEW     vDialogRoot = 0; 
   //:VIEW vDialogTemp  BASED ON LOD TZWDLGSO
   zVIEW     vDialogTemp = 0; 
   //:VIEW vDialogTemp2 BASED ON LOD TZWDLGSO
   zVIEW     vDialogTemp2 = 0; 
   //:VIEW vGroupParent BASED ON LOD TZWDLGSO
   zVIEW     vGroupParent = 0; 
   //:VIEW vDfltMenu    BASED ON LOD TZWDLGSO
   zVIEW     vDfltMenu = 0; 
   //:STRING ( 32 )    szLPLR_Name
   zCHAR     szLPLR_Name[ 33 ] = { 0 }; 
   //:STRING ( 1024 )  szJSP_FileName
   zCHAR     szJSP_FileName[ 1025 ] = { 0 }; 
   //:STRING ( 1024 )  szJS_FileName
   zCHAR     szJS_FileName[ 1025 ] = { 0 }; 
   //:STRING ( 1024 )  szDirectoryName
   zCHAR     szDirectoryName[ 1025 ] = { 0 }; 
   //:STRING ( 10000 ) szWriteBuffer
   zCHAR     szWriteBuffer[ 10001 ] = { 0 }; 
   //:STRING ( 10000 ) szJavaScript
   zCHAR     szJavaScript[ 10001 ] = { 0 }; 
   //:STRING ( 100 )   szIndent
   zCHAR     szIndent[ 101 ] = { 0 }; 
   //:STRING ( 100 )   szIndentNext
   zCHAR     szIndentNext[ 101 ] = { 0 }; 
   //:STRING ( 256 )   szMsg
   zCHAR     szMsg[ 257 ] = { 0 }; 
   //:STRING ( 32 )    szWebDebugView
   zCHAR     szWebDebugView[ 33 ] = { 0 }; 
   //:STRING ( 32 )    szViewName
   zCHAR     szViewName[ 33 ] = { 0 }; 
   //:STRING ( 32 )    szEntityName
   zCHAR     szEntityName[ 33 ] = { 0 }; 
   //:STRING ( 32 )    szCtrlTag
   zCHAR     szCtrlTag[ 33 ] = { 0 }; 
   //:STRING ( 32 )    szListCtrlTag
   zCHAR     szListCtrlTag[ 33 ] = { 0 }; 
   //:STRING ( 32 )    szFocusCtrlTag
   zCHAR     szFocusCtrlTag[ 33 ] = { 0 }; 
   //:STRING ( 34 )    szActionTag
   zCHAR     szActionTag[ 35 ] = { 0 }; 
   //:STRING ( 32 )    szDialogTag
   zCHAR     szDialogTag[ 33 ] = { 0 }; 
   //:STRING ( 32 )    szWindowTag
   zCHAR     szWindowTag[ 33 ] = { 0 }; 
   //:STRING ( 32 )    szAttributeName
   zCHAR     szAttributeName[ 33 ] = { 0 }; 
   //:STRING ( 256 )   szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 64 )    szFormName
   zCHAR     szFormName[ 65 ] = { 0 }; 
   //:STRING ( 34 )    szAction
   zCHAR     szAction[ 35 ] = { 0 }; 
   //:STRING ( 1 )     InitializationCode
   zCHAR     InitializationCode[ 2 ] = { 0 }; 
   //:STRING ( 1 )     InsertBlankFlag
   zCHAR     InsertBlankFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szInsertPrebuildJavascriptInline
   zCHAR     szInsertPrebuildJavascriptInline[ 2 ] = { 0 }; 
   //:STRING ( 1 )     WorkFlag
   zCHAR     WorkFlag[ 2 ] = { 0 }; 
   //:// STRING ( 1024 )  szSizeF
   //:STRING ( 1024 )  szStyle
   zCHAR     szStyle[ 1025 ] = { 0 }; 
   //:STRING ( 1024 )  szFileName
   zCHAR     szFileName[ 1025 ] = { 0 }; 
   //:STRING ( 1 )     szBorder
   zCHAR     szBorder[ 2 ] = { 0 }; 
   //:STRING ( 50 )    szCSS_Class
   zCHAR     szCSS_Class[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szDivContentClass
   zCHAR     szDivContentClass[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szControlType
   zCHAR     szControlType[ 51 ] = { 0 }; 
   //:STRING ( 256 )   szBannerName
   zCHAR     szBannerName[ 257 ] = { 0 }; 
   //:STRING ( 10 )    szHeight
   zCHAR     szHeight[ 11 ] = { 0 }; 
   //:STRING ( 10 )    szWidth
   zCHAR     szWidth[ 11 ] = { 0 }; 
   //:STRING ( 64 )    szSystemIniApplName
   zCHAR     szSystemIniApplName[ 65 ] = { 0 }; 
   //:STRING ( 1 )     szTransferFileFlag
   zCHAR     szTransferFileFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szListButtonFlag
   zCHAR     szListButtonFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szTrace
   zCHAR     szTrace[ 2 ] = { 0 }; 
   //:STRING ( 50 )    szreCAPTCHAImport
   zCHAR     szreCAPTCHAImport[ 51 ] = { 0 }; 
   //:STRING ( 15 )    szIOImport
   zCHAR     szIOImport[ 16 ] = { 0 }; 
   //:STRING ( 50 )    szTempStr
   zCHAR     szTempStr[ 51 ] = { 0 }; 
   //:STRING ( 1 )     szUploadFile
   zCHAR     szUploadFile[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szDownloadFile
   zCHAR     szDownloadFile[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szSideMenuExists
   zCHAR     szSideMenuExists[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szShowSideMenu
   zCHAR     szShowSideMenu[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szShowTopMenu
   zCHAR     szShowTopMenu[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szShowBanner
   zCHAR     szShowBanner[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szNoPositioning
   zCHAR     szNoPositioning[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szWindowIsPopup
   zCHAR     szWindowIsPopup[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szWindowIsForDashboard
   zCHAR     szWindowIsForDashboard[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szNoAutoLogout
   zCHAR     szNoAutoLogout[ 2 ] = { 0 }; 
   //:STRING ( 1 )     szKeyRole
   zCHAR     szKeyRole[ 2 ] = { 0 }; 
   //:STRING ( 10 )    szTimeout
   zCHAR     szTimeout[ 11 ] = { 0 }; 
   //:// INTEGER          lHeight
   //:// INTEGER          lWidth
   //:INTEGER          lFileJSP
   zLONG     lFileJSP = 0; 
   //:INTEGER          lControl
   zLONG     lControl = 0; 
   //:INTEGER          lHeaderFile
   zLONG     lHeaderFile = 0; 
   //:INTEGER          lLastPosY
   zLONG     lLastPosY = 0; 
   //:INTEGER          lSize
   zLONG     lSize = 0; 
   //:INTEGER          X_Size
   zLONG     X_Size = 0; 
   //:INTEGER          Y_Size
   zLONG     Y_Size = 0; 
   //:INTEGER          lExtentY
   zLONG     lExtentY = 0; 
   //:INTEGER          lMinExtentY
   zLONG     lMinExtentY = 0; 
   //:INTEGER          lTableRowCnt
   zLONG     lTableRowCnt = 0; 
   //:INTEGER          lTabIndex
   zLONG     lTabIndex = 0; 
   //:INTEGER          lSort
   zLONG     lSort = 0; 
   //:INTEGER          lTrace
   zLONG     lTrace = 0; 
   //:// INTEGER          lFloat
   //:STRING ( 32 )    szWysiwygEditor
   zCHAR     szWysiwygEditor[ 33 ] = { 0 }; 
   //:INTEGER          ReusableDialogZKey
   zLONG     ReusableDialogZKey = 0; 
   //:INTEGER          ReusableWindowZKey
   zLONG     ReusableWindowZKey = 0; 
   //:DECIMAL          DLUnits
   ZDecimal  DLUnits = 0.0; 
   //:INTEGER          lLth
   zLONG     lLth = 0; 
   //:SHORT            nRC
   zSHORT    nRC = 0; 
   zCHAR     szTempString_0[ 33 ]; 
   zSHORT    RESULT; 
   zCHAR     szTempString_1[ 255 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zSHORT    lTempInteger_0; 
   zSHORT    lTempInteger_1; 
   zSHORT    lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zLONG     lTempInteger_4; 
   zSHORT    lTempInteger_5; 
   zLONG     lTempInteger_6; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zLONG     lTempInteger_7; 
   zSHORT    lTempInteger_8; 
   zLONG     lTempInteger_9; 
   zCHAR     szTempString_6[ 33 ]; 
   zSHORT    lTempInteger_10; 
   zSHORT    lTempInteger_11; 
   zSHORT    lTempInteger_12; 
   zLONG     lTempInteger_13; 
   zCHAR     szTempString_7[ 33 ]; 
   zSHORT    lTempInteger_14; 
   zLONG     lTempInteger_15; 
   zCHAR     szTempString_8[ 33 ]; 
   zSHORT    lTempInteger_16; 
   zSHORT    lTempInteger_17; 
   zSHORT    lTempInteger_18; 
   zLONG     lTempInteger_19; 
   zCHAR     szTempString_9[ 33 ]; 
   zSHORT    lTempInteger_20; 
   zLONG     lTempInteger_21; 
   zCHAR     szTempString_10[ 33 ]; 
   zSHORT    lTempInteger_22; 
   zCHAR     szTempString_11[ 33 ]; 
   zCHAR     szTempString_12[ 33 ]; 
   zCHAR     szTempString_13[ 33 ]; 
   zCHAR     szTempString_14[ 33 ]; 
   zCHAR     szTempString_15[ 255 ]; 
   zCHAR     szTempString_16[ 255 ]; 
   zCHAR     szTempString_17[ 255 ]; 
   zCHAR     szTempString_18[ 33 ]; 
   zCHAR     szTempString_19[ 33 ]; 
   zSHORT    lTempInteger_23; 
   zCHAR     szTempString_20[ 33 ]; 
   zSHORT    lTempInteger_24; 
   zCHAR     szTempString_21[ 255 ]; 
   zCHAR     szTempString_22[ 255 ]; 
   zSHORT    lTempInteger_25; 
   zSHORT    lTempInteger_26; 
   zSHORT    lTempInteger_27; 
   zSHORT    lTempInteger_28; 
   zSHORT    lTempInteger_29; 
   zCHAR     szTempString_23[ 33 ]; 
   zLONG     lTempInteger_30; 
   zLONG     lTempInteger_31; 
   zLONG     lTempInteger_32; 
   zLONG     lTempInteger_33; 
   zCHAR     szTempString_24[ 33 ]; 
   zSHORT    lTempInteger_34; 
   zSHORT    lTempInteger_35; 
   zCHAR     szTempString_25[ 33 ]; 
   zLONG     lTempInteger_36; 
   zLONG     lTempInteger_37; 
   zLONG     lTempInteger_38; 
   zLONG     lTempInteger_39; 
   zCHAR     szTempString_26[ 33 ]; 
   zSHORT    lTempInteger_40; 
   zLONG     lTempInteger_41; 
   zCHAR     szTempString_27[ 33 ]; 
   zLONG     lTempInteger_42; 
   zSHORT    lTempInteger_43; 
   zSHORT    lTempInteger_44; 
   zSHORT    lTempInteger_45; 
   zSHORT    lTempInteger_46; 
   zCHAR     szTempString_28[ 255 ]; 
   zSHORT    lTempInteger_47; 
   zSHORT    lTempInteger_48; 
   zSHORT    lTempInteger_49; 
   zSHORT    lTempInteger_50; 
   zLONG     lTempInteger_51; 
   zCHAR     szTempString_29[ 33 ]; 
   zLONG     lTempInteger_52; 
   zSHORT    lTempInteger_53; 
   zSHORT    lTempInteger_54; 
   zLONG     lTempInteger_55; 
   zLONG     lTempInteger_56; 
   zCHAR     szTempString_30[ 33 ]; 
   zCHAR     szTempString_31[ 33 ]; 
   zCHAR     szTempString_32[ 33 ]; 
   zCHAR     szTempString_33[ 33 ]; 
   zCHAR     szTempString_34[ 33 ]; 
   zCHAR     szTempString_35[ 11 ]; 
   zCHAR     szTempString_36[ 11 ]; 
   zCHAR     szTempString_37[ 255 ]; 
   zCHAR     szTempString_38[ 33 ]; 
   zSHORT    lTempInteger_57; 
   zCHAR     szTempString_39[ 33 ]; 
   zCHAR     szTempString_40[ 33 ]; 
   zCHAR     szTempString_41[ 33 ]; 
   zCHAR     szTempString_42[ 33 ]; 
   zCHAR     szTempString_43[ 33 ]; 
   zCHAR     szTempString_44[ 33 ]; 
   zCHAR     szTempString_45[ 33 ]; 
   zCHAR     szTempString_46[ 33 ]; 
   zCHAR     szTempString_47[ 33 ]; 
   zLONG     lTempInteger_58; 
   zSHORT    lTempInteger_59; 
   zCHAR     szTempString_48[ 255 ]; 
   zCHAR     szTempString_49[ 255 ]; 
   zCHAR     szTempString_50[ 33 ]; 
   zCHAR     szTempString_51[ 255 ]; 


   //:// Generate a JSP file for formatting the Window that has current position.

   //:NAME VIEW vDialog "GenJSP_Dialog"
   SetNameForView( vDialog, "GenJSP_Dialog", 0, zLEVEL_TASK );
   //:szDialogTag = vDialog.Dialog.Tag
   GetVariableFromAttribute( szDialogTag, 0, 'S', 33, vDialog, "Dialog", "Tag", "", 0 );
   //:szWindowTag = vDialog.Window.Tag
   GetVariableFromAttribute( szWindowTag, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
   //:szFormName = szDialogTag + szWindowTag
   ZeidonStringCopy( szFormName, 1, 0, szDialogTag, 1, 0, 65 );
   ZeidonStringConcat( szFormName, 1, 0, szWindowTag, 1, 0, 65 );

   //:// Initialize Output JSP File.
   //:GetViewByName( vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK )
   GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   //:szLPLR_Name = vLPLR.LPLR.Name
   GetVariableFromAttribute( szLPLR_Name, 0, 'S', 33, vLPLR, "LPLR", "Name", "", 0 );
   //:szSystemIniApplName = "[App." + szLPLR_Name + "]"
   ZeidonStringCopy( szSystemIniApplName, 1, 0, "[App.", 1, 0, 65 );
   ZeidonStringConcat( szSystemIniApplName, 1, 0, szLPLR_Name, 1, 0, 65 );
   ZeidonStringConcat( szSystemIniApplName, 1, 0, "]", 1, 0, 65 );
   //:SysReadZeidonIni( -1, szSystemIniApplName, "WebMinExtentY", szTempStr )
   SysReadZeidonIni( -1, szSystemIniApplName, "WebMinExtentY", szTempStr, zsizeof( szTempStr ) );
   //:lMinExtentY = zatol( szTempStr )
   lMinExtentY = zatol( szTempStr );

   //:szDirectoryName = ""
   ZeidonStringCopy( szDirectoryName, 1, 0, "", 1, 0, 1025 );
   //:szSystemIniApplName = "[App." + vLPLR.LPLR.Name + "]"
   GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vLPLR, "LPLR", "Name", "", 0 );
   ZeidonStringCopy( szSystemIniApplName, 1, 0, "[App.", 1, 0, 65 );
   ZeidonStringConcat( szSystemIniApplName, 1, 0, szTempString_0, 1, 0, 65 );
   ZeidonStringConcat( szSystemIniApplName, 1, 0, "]", 1, 0, 65 );
   //:SysReadZeidonIni( -1, szSystemIniApplName, "WebDebugView", szWebDebugView )
   SysReadZeidonIni( -1, szSystemIniApplName, "WebDebugView", szWebDebugView, zsizeof( szWebDebugView ) );
   //:SysReadZeidonIni( -1, szSystemIniApplName, "WebKeyRole", szKeyRole )
   SysReadZeidonIni( -1, szSystemIniApplName, "WebKeyRole", szKeyRole, zsizeof( szKeyRole ) );
   //:SysReadZeidonIni( -1, szSystemIniApplName, "WebDirectory", szDirectoryName )
   SysReadZeidonIni( -1, szSystemIniApplName, "WebDirectory", szDirectoryName, zsizeof( szDirectoryName ) );
   //:IF szDirectoryName = ""
   if ( ZeidonStringCompare( szDirectoryName, 1, 0, "", 1, 0, 1025 ) == 0 )
   { 
      //:szWriteBuffer = "Zeidon.ini file does not have WebDirectory entry in Application: " + szSystemIniApplName
      ZeidonStringCopy( szWriteBuffer, 1, 0, "Zeidon.ini file does not have WebDirectory entry in Application: ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szSystemIniApplName, 1, 0, 10001 );
      //:MessageSend( vSubtask, "", "JSP Generation",
      //:             szWriteBuffer,
      //:             zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
      MessageSend( vSubtask, "", "JSP Generation", szWriteBuffer, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
      //:RETURN -1
      return( -1 );
   } 

   //:END

   //:SysReadZeidonIni( -1, szSystemIniApplName, "JSPTraceLevel", szTrace )
   SysReadZeidonIni( -1, szSystemIniApplName, "JSPTraceLevel", szTrace, zsizeof( szTrace ) );
   //:TraceLineS("** TraceLevel ** ", szTrace)
   TraceLineS( "** TraceLevel ** ", szTrace );
   //:IF  szTrace = "1"
   if ( ZeidonStringCompare( szTrace, 1, 0, "1", 1, 0, 2 ) == 0 )
   { 
      //:lTrace = 1
      lTrace = 1;
      //:ELSE
   } 
   else
   { 
      //:lTrace = 0
      lTrace = 0;
   } 

   //:END

   //:szFileName = szDirectoryName + szFormName + ".jsp"
   ZeidonStringCopy( szFileName, 1, 0, szDirectoryName, 1, 0, 1025 );
   ZeidonStringConcat( szFileName, 1, 0, szFormName, 1, 0, 1025 );
   ZeidonStringConcat( szFileName, 1, 0, ".jsp", 1, 0, 1025 );
   //:SysConvertEnvironmentString( szJSP_FileName, szFileName )
   SysConvertEnvironmentString( szJSP_FileName, zsizeof( szJSP_FileName ), szFileName );

   //:TraceLineS( "GenerateJSP writing to file: ", szJSP_FileName )
   TraceLineS( "GenerateJSP writing to file: ", szJSP_FileName );
   //:lFileJSP = SysOpenFile( vDialog, szJSP_FileName, COREFILE_WRITE )
   lFileJSP = SysOpenFile( vDialog, szJSP_FileName, COREFILE_WRITE );
   //:IF lFileJSP < 0
   if ( lFileJSP < 0 )
   { 
      //:MessageSend( vSubtask, "", "JSP Generation",
      //:             "Invalid JSP directory structure.",
      //:             zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
      MessageSend( vSubtask, "", "JSP Generation", "Invalid JSP directory structure.", zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
      //:RETURN -1
      return( -1 );
   } 

   //:END

   //:CreateViewFromViewForTask( vDialogRoot, vDialog, 0 )
   CreateViewFromViewForTask( &vDialogRoot, vDialog, 0 );
   //:NAME VIEW vDialogRoot "DialogRoot"
   SetNameForView( vDialogRoot, "DialogRoot", 0, zLEVEL_TASK );

   //:// KJS 07/23/08 - Check if this dialog window will be built with all relative positioning or with absolute positioning
   //:IF  vDialog.Dialog.WEB_RelativePositionFlag = "Y" OR vDialog.Window.WEB_RelativePositionFlag = "Y"
   if ( CompareAttributeToString( vDialog, "Dialog", "WEB_RelativePositionFlag", "Y" ) == 0 || CompareAttributeToString( vDialog, "Window", "WEB_RelativePositionFlag", "Y" ) == 0 )
   { 
      //:szNoPositioning = "Y"
      ZeidonStringCopy( szNoPositioning, 1, 0, "Y", 1, 0, 2 );
      //:ELSE
   } 
   else
   { 
      //:szNoPositioning = ""
      ZeidonStringCopy( szNoPositioning, 1, 0, "", 1, 0, 2 );
   } 

   //:END

   //:// KJS 02/19/09 - Added WEB_AbsolutePositionFlag because I would like to use absolute positioning on my popup pages but the rest
   //:// I want to use relative positioning.  Since I think from now on we will probably only want to use relative positioning for most
   //:// pages, I think it will be easier to have this flag.
   //:IF  vDialog.Window.WEB_AbsolutePositionFlag = "Y"
   if ( CompareAttributeToString( vDialog, "Window", "WEB_AbsolutePositionFlag", "Y" ) == 0 )
   { 
      //:szNoPositioning = ""
      ZeidonStringCopy( szNoPositioning, 1, 0, "", 1, 0, 2 );
   } 

   //:END

   //:// KJS 09/16/08 - Thinking that if WEB_NoBannerFlag = "Y" and WEB_NoTopMenuFlag = "Y" and
   //:// szNoPositioning = "Y" (using relative positioning) then we can assume that this window
   //:// is a popup window and so we can get rid of the div "wrapper" and "maincontents" so that
   //:// the only div will be the content div.  Currently you can still see the body background like all
   //:// other windows, and I'm not sure we want that.
   //:// KJS 10/30/08 - I added two styles to the "Window Style" (this is in zeidon.ppe) one for popup and
   //:// one for dashboard.
   //:IF vDialogRoot.WndStyle.Tag = "Popup Window"
   if ( CompareAttributeToString( vDialogRoot, "WndStyle", "Tag", "Popup Window" ) == 0 )
   { 
      //:szWindowIsPopup = "Y"
      ZeidonStringCopy( szWindowIsPopup, 1, 0, "Y", 1, 0, 2 );
      //:ELSE
   } 
   else
   { 
      //:IF vDialogRoot.Window.WEB_NoBannerFlag = "Y" AND vDialogRoot.Window.WEB_NoTopMenuFlag = "Y" AND szNoPositioning = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Window", "WEB_NoBannerFlag", "Y" ) == 0 && CompareAttributeToString( vDialogRoot, "Window", "WEB_NoTopMenuFlag", "Y" ) == 0 && ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 
         //:szWindowIsPopup = "Y"
         ZeidonStringCopy( szWindowIsPopup, 1, 0, "Y", 1, 0, 2 );
         //:ELSE
      } 
      else
      { 
         //:szWindowIsPopup = ""
         ZeidonStringCopy( szWindowIsPopup, 1, 0, "", 1, 0, 2 );
      } 

      //:END
   } 

   //:END


   //:// Check to see if Window has any tab stops set and indicate so in the Window entity.
   //:nRC = 0
   nRC = 0;
   //:FOR EACH vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:IF nRC = 0
      if ( nRC == 0 )
      { 
         //:nRC = GenJSP_FindTAB( vDialog )
         nRC = oTZWDLGSO_GenJSP_FindTAB( vDialog );
      } 

      RESULT = SetCursorNextEntity( vDialog, "Control", "" );
      //:END
   } 

   //:END
   //:IF nRC = 0
   if ( nRC == 0 )
   { 
      //:vDialogRoot.Window.wWindowHasTabsFlag = "N"
      SetAttributeFromString( vDialogRoot, "Window", "wWindowHasTabsFlag", "N" );
      //:ELSE
   } 
   else
   { 
      //:vDialogRoot.Window.wWindowHasTabsFlag = "Y"
      SetAttributeFromString( vDialogRoot, "Window", "wWindowHasTabsFlag", "Y" );
   } 

   //:END

   //:// JSP HEADER

   //:// KJS 05/29/08 - We need to add a DOCTYPE to the jsp page.  Not exactly sure
   //:// which one to add and how often this might need to change (wondering if this should
   //:// be kept in the .ini file or something but for now I'll put it here.
   //:// Here is a website with a little info http://www.alistapart.com/stories/doctype/
   //:// Also this one http://htmlhelp.com/tools/validator/doctype.html
   //://szWriteBuffer = "<!DOCTYPE HTML PUBLIC ^-//W3C//DTD HTML 4.01 Transitional//EN^ ^http://www.w3.org/TR/html4/loose.dtd^>"
   //:szWriteBuffer = "<!DOCTYPE HTML>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<!DOCTYPE HTML>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<%-- " + szFormName + " --%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%-- ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " --%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szIOImport = ""
   ZeidonStringCopy( szIOImport, 1, 0, "", 1, 0, 16 );
   //:szreCAPTCHAImport = ""
   ZeidonStringCopy( szreCAPTCHAImport, 1, 0, "", 1, 0, 51 );

   //:CreateViewFromView( vDialogTemp, vDialog )
   CreateViewFromView( &vDialogTemp, vDialog );
   //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
   lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
   //:szCtrlTag = "File Transfer to Server"
   ZeidonStringCopy( szCtrlTag, 1, 0, "File Transfer to Server", 1, 0, 33 );
   //:nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl,
   //:                       szCtrlTag, "", "", 0, "Window", "" )
   nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl, szCtrlTag, "", "", 0, "Window", "" );
   //:// If we are uploading a file, we need to include "java.oi.*" in the import statement.
   //:IF nRC >= zCURSOR_SET
   if ( nRC >= zCURSOR_SET )
   { 
      //:szIOImport = "java.io.*"
      ZeidonStringCopy( szIOImport, 1, 0, "java.io.*", 1, 0, 16 );
      //:szUploadFile = "Y"
      ZeidonStringCopy( szUploadFile, 1, 0, "Y", 1, 0, 2 );
      //:TraceLineS("*** DOWNLOAD FILE Y *** ", "")
      TraceLineS( "*** DOWNLOAD FILE Y *** ", "" );
   } 

   //:END

   //:FOR EACH vDialogTemp.Action
   RESULT = SetCursorFirstEntity( vDialogTemp, "Action", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:// If there is an action to download a file, we need to include "java.oi.*" in the import statement.
      //:IF vDialogTemp.Action.Type = zWAB_ProcessDownloadFile
      if ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", zWAB_ProcessDownloadFile ) == 0 )
      { 
         //:szIOImport = "java.io.*"
         ZeidonStringCopy( szIOImport, 1, 0, "java.io.*", 1, 0, 16 );
      } 

      //:END
      //:// If there is an action for the reCAPTCHA control, then we need
      //:// net.tanesha.recaptcha.* in the import statement
      //:IF vDialogTemp.Action.Type = 35 OR vDialogTemp.Action.Type = 55
      if ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", 35 ) == 0 || CompareAttributeToInteger( vDialogTemp, "Action", "Type", 55 ) == 0 )
      { 
         //:szreCAPTCHAImport = "net.tanesha.recaptcha.*"
         ZeidonStringCopy( szreCAPTCHAImport, 1, 0, "net.tanesha.recaptcha.*", 1, 0, 51 );
      } 

      RESULT = SetCursorNextEntity( vDialogTemp, "Action", "" );
      //:END
   } 

   //:END

   //:// If there is an groupbox for the reCAPTCHA control, then we need
   //:// net.tanesha.recaptcha.* in the import statement
   //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
   lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
   //:szCtrlTag = "reCAPTCHA"
   ZeidonStringCopy( szCtrlTag, 1, 0, "reCAPTCHA", 1, 0, 33 );
   //:nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl,
   //:                       szCtrlTag, "", "", 0, "Window", "" )
   nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl, szCtrlTag, "", "", 0, "Window", "" );

   //:// If we are uploading a file, we need to include "java.oi.*" in the import statement.
   //:IF nRC >= zCURSOR_SET
   if ( nRC >= zCURSOR_SET )
   { 
      //:szreCAPTCHAImport = "net.tanesha.recaptcha.*"
      ZeidonStringCopy( szreCAPTCHAImport, 1, 0, "net.tanesha.recaptcha.*", 1, 0, 51 );
   } 

   //:END

   //:// szWriteBuffer = "<%@ page import=^java.util.*,javax.servlet.*,javax.servlet.http.*,zeidon.zView" + szIOImport + szreCAPTCHAImport + "^ %>"
   //:szWriteBuffer = "<%@ page import=^java.util.*^ %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ page import=^java.util.*^ %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "<%@ page import=^javax.servlet.*^ %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ page import=^javax.servlet.*^ %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "<%@ page import=^javax.servlet.http.*^ %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ page import=^javax.servlet.http.*^ %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "<%@ page import=^zeidon.zView^ %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ page import=^zeidon.zView^ %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:IF szIOImport != ""
   if ( ZeidonStringCompare( szIOImport, 1, 0, "", 1, 0, 16 ) != 0 )
   { 
      //:szWriteBuffer = "<%@ page import=^" + szIOImport + "^ %>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ page import=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szIOImport, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ %>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:IF szreCAPTCHAImport != ""
   if ( ZeidonStringCompare( szreCAPTCHAImport, 1, 0, "", 1, 0, 51 ) != 0 )
   { 
      //:szWriteBuffer = "<%@ page import=^" + szreCAPTCHAImport + "^ %>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ page import=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szreCAPTCHAImport, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ %>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "<%@ page import=^com.quinsoft." + szLPLR_Name + ".*^ %>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ page import=^com.quinsoft.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szLPLR_Name, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".*^ %>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:// KJS 07/10/15 - Include for an import file for any extra imports.
   //:IF vDialog.Dialog.WEB_ImportInclude != ""
   if ( CompareAttributeToString( vDialog, "Dialog", "WEB_ImportInclude", "" ) != 0 )
   { 
      //:szWriteBuffer = "<%@ include file=^" + vDialog.Dialog.WEB_ImportInclude  + "^ %>"
      GetVariableFromAttribute( szTempString_1, 0, 'S', 255, vDialog, "Dialog", "WEB_ImportInclude", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ %>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:/*
   //:IF szUploadFile = "Y" OR szDownloadFile = "Y"
   //:   // Page Header when File Transfer exists on Window.
   //:   szWriteBuffer = "<%@ page import=^java.util.*,javax.servlet.*,javax.servlet.http.*,java.io.*,zeidon.zView^ %>"
   //:ELSE
   //:   // Page Header when File Transfer does not exist on Window.
   //:   //KJS 12/11/07 - I'm going to put the java.io here as well, because we need this if there is file download
   //:   //on the page.  This could be on a subcontrol (in a grid) so for now I'm just putting this in.
   //:   szWriteBuffer = "<%@ page import=^java.util.*,javax.servlet.*,javax.servlet.http.*,zeidon.zView^ %>"
   //:END
   //:*/
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:/*
   //:// KJS 08/30/12 - Putting this in for Aadit... Show in seconds the page load time.
   //:szWriteBuffer = "<%"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   // Show the time in seconds it takes to load the page."
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   Date tPageStart   = new Date();"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "%>"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //:*/

   //:szWriteBuffer = "<%! "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%! ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// FindOpenFile public function
   //:// KJS 10/31/08 - This function is now in kzoejava.c and we do not want it in the jsp code.
   //:/*
   //:szWriteBuffer = "public String FindOpenFile( String strSID, zeidon.zView vAS )"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "{"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   zeidon.zView vTemp = new zeidon.zView( strSID );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   String strFile = vAS.MakeWebFileName( strSID, 0 ) + ^.html^;"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   int   nRC = vTemp.GetView( strSID, strFile, vAS );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   if ( nRC > 0 )"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   {"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "      vTemp.DropName( strSID, strFile );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "      return strFile;"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   }"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //:szWriteBuffer = "   return ^^;"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "}"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //:*/

   //:// INPUT MAPPING

   //:// First loop through controls and null out each Named View that is used.
   //:FOR EACH vDialog.ViewObjRef
   RESULT = SetCursorFirstEntity( vDialog, "ViewObjRef", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:vDialog.ViewObjRef.wWindowUseFlag = ""
      SetAttributeFromString( vDialog, "ViewObjRef", "wWindowUseFlag", "" );
      RESULT = SetCursorNextEntity( vDialog, "ViewObjRef", "" );
   } 

   //:END

   //:// Execute FlagUsedViewsGetFocusR for multiple functions, such as determining which views are used in mapping.
   //:FOR EACH vDialogRoot.ComboBoxEntry
   RESULT = SetCursorFirstEntity( vDialogRoot, "ComboBoxEntry", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:DELETE ENTITY vDialogRoot.ComboBoxEntry NONE
      RESULT = DeleteEntity( vDialogRoot, "ComboBoxEntry", zREPOS_NONE );
      RESULT = SetCursorNextEntity( vDialogRoot, "ComboBoxEntry", "" );
   } 

   //:END

   //:szWysiwygEditor = ""  // do not include widgEditor.js file
   ZeidonStringCopy( szWysiwygEditor, 1, 0, "", 1, 0, 33 );
   //:szFocusCtrlTag = ""
   ZeidonStringCopy( szFocusCtrlTag, 1, 0, "", 1, 0, 33 );
   //:lTabIndex = 9999
   lTabIndex = 9999;
   //:lSort = FlagUsedViewsGetFocusR( vDialog, vDialogRoot, szFocusCtrlTag, lTabIndex, szWysiwygEditor )
   lSort = oTZWDLGSO_FlagUsedViewsGetFocusR( vDialog, vDialogRoot, szFocusCtrlTag, lTabIndex, szWysiwygEditor );
   //:TraceLineS( "Focus on Control: ", szFocusCtrlTag )
   TraceLineS( "Focus on Control: ", szFocusCtrlTag );

   //:/******************************  ReplaceXSSValues  ******************************/
   //:// To prevent cross-scripting attacks.
   //:szWriteBuffer = "public String ReplaceXSSValues( String szFieldValue )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "public String ReplaceXSSValues( String szFieldValue )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String szOutput;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String szOutput;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "   szOutput = szFieldValue.replace(^<^,^&lt;^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   szOutput = szFieldValue.replace(^<^,^&lt;^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   szOutput = szOutput.replace(^>^,^&gt;^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   szOutput = szOutput.replace(^>^,^&gt;^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   szOutput = szOutput.replace(^\^^,^&quot;^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   szOutput = szOutput.replace(^\\^^,^&quot;^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   szOutput = szOutput.replace(^\'^,^&apos;^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   szOutput = szOutput.replace(^\\'^,^&apos;^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "   return( szOutput );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   return( szOutput );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:/******************************  DoInputMapping  ******************************/

   //:// Create prototype and any definitions for views that are to be used.
   //:szWriteBuffer = "public int DoInputMapping( HttpServletRequest request,"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "public int DoInputMapping( HttpServletRequest request,", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                           HttpSession session,"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                           HttpSession session,", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                           ServletContext application )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                           ServletContext application )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strSID = session.getId( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strSID = session.getId( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   zeidon.zView vAS = (zeidon.zView) session.getAttribute( ^ZeidonSubtask^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   zeidon.zView vAS = (zeidon.zView) session.getAttribute( ^ZeidonSubtask^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:FOR EACH vDialog.ViewObjRef WHERE vDialog.ViewObjRef.wWindowUseFlag = "Y"
   RESULT = SetCursorFirstEntityByString( vDialog, "ViewObjRef", "wWindowUseFlag", "Y", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:szWriteBuffer = "   zeidon.zView " + vDialog.ViewObjRef.Name + " = new zeidon.zView( strSID );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   zeidon.zView ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = new zeidon.zView( strSID );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      RESULT = SetCursorNextEntityByString( vDialog, "ViewObjRef", "wWindowUseFlag", "Y", "" );
   } 

   //:END

   //:szWriteBuffer = "   zeidon.zView vGridTmp = new zeidon.zView( strSID ); // temp view to grid view"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   zeidon.zView vGridTmp = new zeidon.zView( strSID ); // temp view to grid view", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   zeidon.zView vMsgQ = new zeidon.zView( strSID ); // view to Message Queue"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   zeidon.zView vMsgQ = new zeidon.zView( strSID ); // view to Message Queue", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   zeidon.zView v = new zeidon.zView( strSID );     // view to Message Queue"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   zeidon.zView v = new zeidon.zView( strSID );     // view to Message Queue", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   String strError = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strError = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strDateFormat = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strDateFormat = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strMapValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strMapValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int    iView = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    iView = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int    lEntityKey = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    lEntityKey = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strEntityKey = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strEntityKey = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strTag = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strTag = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strTemp = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strTemp = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int    iTableRowCnt = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    iTableRowCnt = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strSuffix = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strSuffix = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int    nRelPos = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    nRelPos = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int    nRC = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    nRC = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int    nMapError = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    nMapError = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //://KJS Trace
   //:IF (lTrace = 1)
   if ( lTrace == 1 )
   { 
      //:szWriteBuffer = "   vAS.TraceLine( ^DoInputMapping for jsp =======>> ^, ^" + szFormName + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAS.TraceLine( ^DoInputMapping for jsp =======>> ^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   vAS.TraceLine( ^DoInputMapping Session ID: ^ + strSID, vAS );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAS.TraceLine( ^DoInputMapping Session ID: ^ + strSID, vAS );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:// Generate mapping statements for each view and control.
   //:FOR EACH vDialog.ViewObjRef WHERE vDialog.ViewObjRef.wWindowUseFlag = "Y"
   RESULT = SetCursorFirstEntityByString( vDialog, "ViewObjRef", "wWindowUseFlag", "Y", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 

      //:szViewName = vDialog.ViewObjRef.Name
      GetVariableFromAttribute( szViewName, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
      //:szWriteBuffer = "   nRC = " + szViewName + ".GetView( strSID, ^" + szViewName + "^, vAS );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSID, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAS );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "   if ( nRC > 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC > 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:OrderEntityForView( vDialog, "Control", "PSDLG_Y A PSDLG_X A" )
      OrderEntityForView( vDialog, "Control", "PSDLG_Y A PSDLG_X A" );
      //:GenJSP_InputMapRecurs( vDialog, szViewName, lFileJSP, szWriteBuffer, lTableRowCnt )
      GenJSP_InputMapRecurs( vDialog, szViewName, lFileJSP, szWriteBuffer, lTableRowCnt );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
      RESULT = SetCursorNextEntityByString( vDialog, "ViewObjRef", "wWindowUseFlag", "Y", "" );
   } 


   //:END

   //:szWriteBuffer = "   if ( nMapError < 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nMapError < 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      iView = vAS.GetIntegerFromView( strSID );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      iView = vAS.GetIntegerFromView( strSID );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      vAS.TraceLine( ^DoInputMapping ERROR =======>> ^, strError );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAS.TraceLine( ^DoInputMapping ERROR =======>> ^, strError );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      nRC = vMsgQ.GetView( strSID, ^__MSGQ^, vAS );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = vMsgQ.GetView( strSID, ^__MSGQ^, vAS );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( nRC > 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC > 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         v.CreateViewFromView( strSID, vMsgQ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         v.CreateViewFromView( strSID, vMsgQ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAS.TraceLine( ^DoInputMapping found __MSGQ^, ^^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAS.TraceLine( ^DoInputMapping found __MSGQ^, ^^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         v.DisplayObjectInstance( strSID );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         v.DisplayObjectInstance( strSID );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAS.TraceLine( ^DoInputMapping __MSGQ View: ^, iView );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAS.TraceLine( ^DoInputMapping __MSGQ View: ^, iView );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         nRC = v.SetCursorFirst( strSID, ^Task^, ^Id^, iView, ^^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = v.SetCursorFirst( strSID, ^Task^, ^Id^, iView, ^^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAS.TraceLine( ^DoInputMapping SetCursorFirst RC: ^, nRC );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAS.TraceLine( ^DoInputMapping SetCursorFirst RC: ^, nRC );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if ( nRC == 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( nRC == 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            nRC = v.SetCursorFirst( strSID, ^QMsg^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            nRC = v.SetCursorFirst( strSID, ^QMsg^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            if ( nRC == 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( nRC == 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               vAS.TraceLine( ^DoInputMapping found QMsg Entity^, ^^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               vAS.TraceLine( ^DoInputMapping found QMsg Entity^, ^^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               v.SetAttributeFromVariable( strSID, ^QMsg^, ^Title^, strError, 'S',"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               v.SetAttributeFromVariable( strSID, ^QMsg^, ^Title^, strError, 'S',", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                                           strError.length( ) + 1, ^^, 8 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                                           strError.length( ) + 1, ^^, 8 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "            while ( nRC == 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            while ( nRC == 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               v.DisplayEntityInstance( strSID, ^QMsg^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               v.DisplayEntityInstance( strSID, ^QMsg^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               nRC = v.SetCursorNext( strSID, ^QMsg^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               nRC = v.SetCursorNext( strSID, ^QMsg^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               vAS.TraceLine( ^DoInputMapping SetCursorNext RC: ^, nRC );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               vAS.TraceLine( ^DoInputMapping SetCursorNext RC: ^, nRC );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "            vAS.TraceLine( ^DoInputMapping after __MSGQ^, ^^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            vAS.TraceLine( ^DoInputMapping after __MSGQ^, ^^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            nRC = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            nRC = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "         v.DisplayObjectInstance( strSID );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         v.DisplayObjectInstance( strSID );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         v.DropView( strSID );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         v.DropView( strSID );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         nRC = -1;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = -1;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      return( nRC );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      return( nRC );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   return( 1 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   return( 1 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:/******************************  End of DoInputMapping  ******************************/

   //:// End of JSP functions.
   //:szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );


   //:/************************* MAIN SECTION INITIALIZATION  This is where action jsp code will be created. ***********************/

   //:szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "session = request.getSession( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "session = request.getSession( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strSessionId = session.getId( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strSessionId = session.getId( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "zeidon.zView vAppSubtask; // view to this subtask"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "zeidon.zView vAppSubtask; // view to this subtask", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //://szWriteBuffer = "zeidon.zView wWebXA = new zeidon.zView( strSessionId ); // view to web transfer area"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "zeidon.zView vMsgQ = new zeidon.zView( strSessionId ); // view to Message Queue"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "zeidon.zView vMsgQ = new zeidon.zView( strSessionId ); // view to Message Queue", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "zView vKZXMLPGO = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "zView vKZXMLPGO = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strLastPage;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strLastPage;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "short  nRepos = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "short  nRepos = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "int bDone = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "int bDone = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "int nPos = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "int nPos = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "int nOptRC = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "int nOptRC = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "int nRC = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "int nRC = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "int nRCk = 0;  // temp fix for SetCursorEntityKey"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "int nRCk = 0;  // temp fix for SetCursorEntityKey", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "int lEKey = 0; // temp fix for SetCursorEntityKey"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "int lEKey = 0; // temp fix for SetCursorEntityKey", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "String strKey = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strKey = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strActionToProcess = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strActionToProcess = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strURL = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strURL = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strError = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strError = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strErrorFlag = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strErrorFlag = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strErrorTitle = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strErrorTitle = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strErrorMsg = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strErrorMsg = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strFocusCtrl = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strFocusCtrl = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strBannerName = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strBannerName = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strOpenFile = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strOpenFile = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strOpenPopupWindow = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strOpenPopupWindow = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strPopupWindowSZX = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strPopupWindowSZX = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strPopupWindowSZY = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strPopupWindowSZY = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strDateFormat = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strDateFormat = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:IF szKeyRole = "Y"
   if ( ZeidonStringCompare( szKeyRole, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "String strLoginName = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "String strLoginName = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "String strKeyRole = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "String strKeyRole = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END
   //:IF szWebDebugView != ""
   if ( ZeidonStringCompare( szWebDebugView, 1, 0, "", 1, 0, 33 ) != 0 )
   { 
      //:szWriteBuffer = "String strFeedback = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "String strFeedback = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END
   //:szWriteBuffer = "String strDialogName = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strDialogName = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strWindowName = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strWindowName = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strLastWindow = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strLastWindow = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strLastAction = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strLastAction = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strFunctionCall = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strFunctionCall = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strNextJSP_Name = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strNextJSP_Name = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "String strInputFileName = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "String strInputFileName = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "int iFileLth = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "int iFileLth = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// If this time through, this happens to be a refresh, then go to the logout screen.
   //:szWriteBuffer = "   strActionToProcess = (String) request.getParameter( ^zAction^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strActionToProcess = (String) request.getParameter( ^zAction^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "strLastWindow = (String) session.getAttribute( ^ZeidonWindow^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "strLastWindow = (String) session.getAttribute( ^ZeidonWindow^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "if ( strLastWindow == null ) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "if ( strLastWindow == null ) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "strLastWindow = ^NoLastWindow^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "strLastWindow = ^NoLastWindow^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "strLastAction = (String) session.getAttribute( ^ZeidonAction^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "strLastAction = (String) session.getAttribute( ^ZeidonAction^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// If this is a log on page (like wStartupLogin) then we don't want to have the 'Unregister Zeidon' happen
   //:// if the user leaves the page or refreshes.  It causes problems.  So we won't go to the logout page here.
   //:IF ( vDialog.Window.WEB_RegisterZeidonWindow != "Y" )
   if ( CompareAttributeToString( vDialog, "Window", "WEB_RegisterZeidonWindow", "Y" ) != 0 )
   { 
      //:szWriteBuffer = "if ( strLastWindow.equals(^" + szFormName + "^) && strActionToProcess == null && strLastAction == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "if ( strLastWindow.equals(^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^) && strActionToProcess == null && strLastAction == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "{"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   strURL = response.encodeRedirectURL( ^logout.jsp^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   strURL = response.encodeRedirectURL( ^logout.jsp^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   response.sendRedirect( strURL );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   response.sendRedirect( strURL );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   return;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   return;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "}"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:// vAppSubtask
   //:szWriteBuffer = "// Check to see if the Zeidon subtask view already exists.  If not, create"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "// Check to see if the Zeidon subtask view already exists.  If not, create", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "// it and copy it into the application object."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "// it and copy it into the application object.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "vAppSubtask = (zeidon.zView) session.getAttribute( ^ZeidonSubtask^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "vAppSubtask = (zeidon.zView) session.getAttribute( ^ZeidonSubtask^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "if ( vAppSubtask == null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "if ( vAppSubtask == null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// KJS 09/25/09 - Previously we were looking for the word "Login" in a window name to determine
   //:// if this window should have the RegisterZeidonApplication in it.  I will keep this code for now
   //:// but I really think this should be a property for the window.  I have added a checkbox to WND_UPD
   //:// for this.
   //:nRC = zSearchSubString( szFormName, "Login", "f", 0 )
   nRC = zSearchSubString( szFormName, "Login", "f", 0 );
   //:IF nRC >= 0 OR vDialog.Window.WEB_RegisterZeidonWindow = "Y" // "wStartUpLogin"
   if ( nRC >= 0 || CompareAttributeToString( vDialog, "Window", "WEB_RegisterZeidonWindow", "Y" ) == 0 )
   { 

      //:szWriteBuffer = "   vAppSubtask = new zeidon.zView( strSessionId );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask = new zeidon.zView( strSessionId );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   vAppSubtask.RegisterZeidonApplication( strSessionId, ^//" + vLPLR.LPLR.Name + "^ );"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vLPLR, "LPLR", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.RegisterZeidonApplication( strSessionId, ^//", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   session.setAttribute( ^ZeidonSubtask^, vAppSubtask );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   session.setAttribute( ^ZeidonSubtask^, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "}"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

      //:szWriteBuffer = "if ( vAppSubtask == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "if ( vAppSubtask == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "{"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   return; // something really bad has happened!!!"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   return; // something really bad has happened!!!", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:ELSE
   } 
   else
   { 
      //:/*
      //:szWriteBuffer = "   strURL = response.encodeRedirectURL( ^wStartUpLogin.jsp^ );"
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      //:szWriteBuffer = "   strActionToProcess = ^?^;"
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      //:szWriteBuffer = "   bDone = 1;"
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      //:szWriteBuffer = "   nRC = 1;"
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      //:*/
      //:szWriteBuffer = "   strURL = response.encodeRedirectURL( ^logout.jsp^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   strURL = response.encodeRedirectURL( ^logout.jsp^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   response.sendRedirect( strURL );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   response.sendRedirect( strURL );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   return; // something really bad has happened!!!"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   return; // something really bad has happened!!!", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 


   //:END

   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //://KJS Trace
   //:IF (lTrace = 1)
   if ( lTrace == 1 )
   { 
      //:szWriteBuffer = "   vAppSubtask.TraceLine( ^Initialize ========>>> Session ID: ^ + strSessionId, vAppSubtask );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine( ^Initialize ========>>> Session ID: ^ + strSessionId, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:// KJS 02/29/2008 - We would like to delete report files when they are generated.  Here is code
   //:// that sort of does the trick but the problem is that I need to know the exact file where the
   //:// jsp code is kept.  How should we do this.  I can try and get the current directory and then
   //:// figure it from there (I believe when I tried, current directory was
   //:// c:\program file...\webapps\" but then I need to know whether we are \zencas or \noa etc and
   //:// would this work in all cases.  Can't do theory like timout.inc cause this is jsp.  Do I hard
   //:// code the directory in the .ini file and assume all noa users would have the same tomcat directory
   //:// structure.  Need to talk to Aadit and Jeff.
   //:// Also, do I only want to create this code if this page contains a report or should I just do it all the
   //:// time?  Action.Type = 41 seems to be the action for start Browser HTML...
   //:/*
   //:CreateViewFromView( vDialogTemp, vDialog )
   //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
   //:nRC = SetEntityCursor( vDialogTemp, "Action", "Type", lControl,
   //:                       "41", "", "", 0, "Window", "" )
   //:IF nRC >= zCURSOR_SET
   //:   strOpenFile = request.getParameter( "zOpenFile" );
   //:   if ( strOpenFile != null && strOpenFile != "" )
   //:   {
   //:      strOpenFile = "C:\\Program Files\\Apache Group\\Tomcat 5.5\\webapps\\ROOT\\zencas\\" + strOpenFile;
   //:      File f = new File(strOpenFile);
   //:      //USE szSystemIniApplName????!!!!
   //:      //strOpenFile = "/zencas/kellytext.txt";
   //:      //File f = new File(request.getRealPath(strOpenFile));
   //:      f.delete();
   //:   }
   //:END
   //:DropView( vDialogTemp )
   //:*/

   //://KJS Trace
   //:IF (lTrace = 1)
   if ( lTrace == 1 )
   { 
      //:szWriteBuffer = "   vAppSubtask.TraceLine( ^Page Name ========>>> ^ + ^" + szFormName + "^, vAppSubtask );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine( ^Page Name ========>>> ^ + ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
      //:szWriteBuffer = "   vAppSubtask.TraceLine( ^zAction ========>>> ^ + strActionToProcess, vAppSubtask );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine( ^zAction ========>>> ^ + strActionToProcess, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:// Generate Transfer File to Server logic if there is a GroupBox of type "File Transfer to Server".
   //:CreateViewFromView( vDialogTemp, vDialog )
   CreateViewFromView( &vDialogTemp, vDialog );
   //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
   lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
   //:szCtrlTag = "File Transfer to Server"
   ZeidonStringCopy( szCtrlTag, 1, 0, "File Transfer to Server", 1, 0, 33 );
   //:nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl,
   //:                       szCtrlTag, "", "", 0, "Window", "" )
   nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl, szCtrlTag, "", "", 0, "Window", "" );
   //:IF nRC >= zCURSOR_SET
   if ( nRC >= zCURSOR_SET )
   { 
      //:GenJSP_ProcessFileIn( vDialog, lFileJSP, szWriteBuffer )
      oTZWDLGSO_GenJSP_ProcessFileIn( vDialog, lFileJSP, szWriteBuffer );
   } 

   //:END
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );

   //:// vKZXMLPGO
   //:szWriteBuffer = "   if ( vKZXMLPGO == null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( vKZXMLPGO == null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      vKZXMLPGO = new zeidon.zView( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      vKZXMLPGO = new zeidon.zView( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   nRC = vKZXMLPGO.GetView( strSessionId, ^KZXMLPGO^, vAppSubtask );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = vKZXMLPGO.GetView( strSessionId, ^KZXMLPGO^, vAppSubtask );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( nRC <= 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC <= 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      vKZXMLPGO.InitWebSessionObject( strSessionId, vAppSubtask, ^TestUserID^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      vKZXMLPGO.InitWebSessionObject( strSessionId, vAppSubtask, ^TestUserID^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      vKZXMLPGO.SetName( strSessionId, ^KZXMLPGO^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      vKZXMLPGO.SetName( strSessionId, ^KZXMLPGO^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   nRC = vMsgQ.GetView( strSessionId, ^__MSGQ^, vAppSubtask );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = vMsgQ.GetView( strSessionId, ^__MSGQ^, vAppSubtask );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:/* DKS_TRACE_START
   //:// Temporary traces to understand how Error Object is used.
   //:szWriteBuffer = "   if ( nRC > 0 )"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "      vAppSubtask.TraceLine( ^***Message Object Check: FOUND __MSGQ^, ^^ );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   else"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "      vAppSubtask.TraceLine( ^***Message Object Check: NOT found __MSGQ^, ^^ );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //:DKS_TRACE_END */

   //:szWriteBuffer = "   vAppSubtask.SetDefaultViewForActiveTask( strSessionId, 2 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.SetDefaultViewForActiveTask( strSessionId, 2 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// MAIN SECTION ACTION PROCESSING

   //:szWriteBuffer = "   strURL = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strURL = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   bDone = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   bDone = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   nRC = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "vAppSubtask.TraceLine(^*** " + szFormName + " strActionToProcess *** ^, strActionToProcess );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "vAppSubtask.TraceLine(^*** ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " strActionToProcess *** ^, strActionToProcess );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "vAppSubtask.TraceLine(^*** " + szFormName + " LastWindow *** ^, strLastWindow );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "vAppSubtask.TraceLine(^*** ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " LastWindow *** ^, strLastWindow );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "strLastAction = (String) session.getAttribute( ^ZeidonAction^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "strLastAction = (String) session.getAttribute( ^ZeidonAction^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "vAppSubtask.TraceLine(^*** " + szFormName + " LastAction *** ^, strLastAction );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "vAppSubtask.TraceLine(^*** ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " LastAction *** ^, strLastAction );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "if ( strActionToProcess != null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "if ( strActionToProcess != null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "   if ( vAppSubtask != null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( vAppSubtask != null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //://KJS Trace
   //:IF (lTrace = 1)
   if ( lTrace == 1 )
   { 
      //:szWriteBuffer = "      vAppSubtask.TraceLine( ^Process Action: ^, strActionToProcess );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask.TraceLine( ^Process Action: ^, strActionToProcess );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END
   //:// Process Error Object.
   //:szWriteBuffer = "      // Delete the message object if error on last interation."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Delete the message object if error on last interation.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      nRC = vMsgQ.GetView( strSessionId, ^__MSGQ^, vAppSubtask );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = vMsgQ.GetView( strSessionId, ^__MSGQ^, vAppSubtask );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( nRC > 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC > 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vMsgQ.DropObjectInstance( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vMsgQ.DropObjectInstance( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:IF szWebDebugView != ""
   if ( ZeidonStringCompare( szWebDebugView, 1, 0, "", 1, 0, 33 ) != 0 )
   { 

      //:szWriteBuffer = "   if ( vAppSubtask != null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( vAppSubtask != null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      strFeedback = request.getParameter( ^zFeedback^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strFeedback = request.getParameter( ^zFeedback^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( strFeedback != ^^ )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strFeedback != ^^ )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         vAppSubtask.TraceLine( ^DoInputMapping Feedback: ^, strFeedback );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.TraceLine( ^DoInputMapping Feedback: ^, strFeedback );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         vAppSubtask.SaveFeedback( strSessionId, ^" + szWebDebugView + "^, ^" + szDialogTag
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.SaveFeedback( strSessionId, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szWebDebugView, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szDialogTag, 1, 0, 10001 );
      //:szWriteBuffer = szWriteBuffer + "^, ^" + szWindowTag + "^, strFeedback );"
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szWindowTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, strFeedback );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 


   //:END

   //:// Create Action code for each Action, except for Window Actions.
   //:FOR EACH vDialog.Action
   RESULT = SetCursorFirstEntity( vDialog, "Action", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:szActionTag = vDialog.Action.Tag  // moved here just to assist debugging
      GetVariableFromAttribute( szActionTag, 0, 'S', 35, vDialog, "Action", "Tag", "", 0 );
      //:IF vDialog.ActWndEvent DOES NOT EXIST
      lTempInteger_0 = CheckExistenceOfEntity( vDialog, "ActWndEvent" );
      if ( lTempInteger_0 != 0 )
      { 
         //:// OR vDialog.ActEvent EXISTS // DKS likes this line ... Don does not
         //:// OR vDialog.ActOpt EXISTS   // DKS likes this line ... Don does not

         //:nRC = zstrcmpi( szActionTag, "alt-f4" )
         nRC = zstrcmpi( szActionTag, "alt-f4" );
         //:IF nRC = 0
         if ( nRC == 0 )
         { 
            //:szActionTag = "AltF4"
            ZeidonStringCopy( szActionTag, 1, 0, "AltF4", 1, 0, 35 );
         } 

         //:END

         //:IF vDialog.Action.Type != zWAB_ExitDialogTask
         if ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_ExitDialogTask ) != 0 )
         { 
            //:// We don't format the Action on exit dialog, as the function in the java script calls OnUnload.
            //:GenJSP_Action( vDialog, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szActionTag, lTrace )
            GenJSP_Action( vDialog, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szActionTag, lTrace );
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:IF vDialog.ActEvent EXISTS OR vDialog.ActOpt EXISTS
         lTempInteger_1 = CheckExistenceOfEntity( vDialog, "ActEvent" );
         lTempInteger_2 = CheckExistenceOfEntity( vDialog, "ActOpt" );
         if ( lTempInteger_1 == 0 || lTempInteger_2 == 0 )
         { 
            //:TraceLineS( "Action has WndEvent that PREVENTS generation: ", szActionTag )
            TraceLineS( "Action has WndEvent that PREVENTS generation: ", szActionTag );
         } 

         //:END
      } 

      RESULT = SetCursorNextEntity( vDialog, "Action", "" );
      //:END
   } 

   //:END

   //://If there are comboboxes on this page that are "auto include" or "set foreign key" but
   //://doesn't have another action, then we need a generic action that gets called.  We need
   //://to submit the page and have the DoInputMapping called (this is where the
   //://autoinclude etc code gets called).

   //:szWriteBuffer = "   while ( bDone == 0 && strActionToProcess.equals( ^ZEIDON_ComboBoxSubmit^ ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   while ( bDone == 0 && strActionToProcess.equals( ^ZEIDON_ComboBoxSubmit^ ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      bDone = 1;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      bDone = 1;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      // Input Mapping"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Input Mapping", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      nRC = DoInputMapping( request, session, application );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = DoInputMapping( request, session, application );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( nRC < 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC < 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         break;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         break;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      // No redirection, we are staying on this page."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // No redirection, we are staying on this page.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      nRC = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      break;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      break;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// If the Window has a reusable side menu, add the actions from that menu.
   //:IF vDialog.ReusableSideWindow EXISTS
   lTempInteger_3 = CheckExistenceOfEntity( vDialog, "ReusableSideWindow" );
   if ( lTempInteger_3 == 0 )
   { 
      //:IF vDialog.ReusableSideDialog.ZKey = vDialog.Dialog.ZKey
      if ( CompareAttributeToAttribute( vDialog, "ReusableSideDialog", "ZKey", vDialog, "Dialog", "ZKey" ) == 0 )
      { 
         //:CreateViewFromView( vDialogTemp, vDialog )
         CreateViewFromView( &vDialogTemp, vDialog );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = vDialog.ReusableSideWindow.ZKey
         GetIntegerFromAttribute( &lTempInteger_4, vDialog, "ReusableSideWindow", "ZKey" );
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", lTempInteger_4, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:FOR EACH vDialogTemp.Option
            RESULT = SetCursorFirstEntity( vDialogTemp, "Option", "" );
            while ( RESULT > zCURSOR_UNCHANGED )
            { 
               //:IF vDialogTemp.OptAct EXISTS
               lTempInteger_5 = CheckExistenceOfEntity( vDialogTemp, "OptAct" );
               if ( lTempInteger_5 == 0 )
               { 
                  //:SET CURSOR FIRST vDialogTemp.Action WHERE vDialogTemp.Action.ZKey = vDialogTemp.OptAct.ZKey
                  GetIntegerFromAttribute( &lTempInteger_6, vDialogTemp, "OptAct", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Action", "ZKey", lTempInteger_6, "" );
                  //:IF RESULT >= zCURSOR_SET
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:IF vDialogTemp.Action.Type != zWAB_ExitDialogTask
                     if ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", zWAB_ExitDialogTask ) != 0 )
                     { 
                        //://Because the menu actions can be created on separate windows from the control
                        //://actions, we need to make sure these actions are unique.  We will prefix a
                        //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
                        //:szAction = "sm" + vDialogTemp.Action.Tag
                        GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialogTemp, "Action", "Tag", "", 0 );
                        ZeidonStringCopy( szAction, 1, 0, "sm", 1, 0, 35 );
                        ZeidonStringConcat( szAction, 1, 0, szTempString_4, 1, 0, 35 );
                        //:lLth = zstrlen( szAction )
                        lLth = zstrlen( szAction );
                        //://IF lLth > 32
                        //://   MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32",
                        //://                szAction,
                        //://                zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                        //://END

                        //:GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace )
                        GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace );
                     } 

                     //:END
                  } 

                  //:END
               } 

               RESULT = SetCursorNextEntity( vDialogTemp, "Option", "" );
               //:END
            } 

            //:END
         } 

         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI_ByName( vSubtask, vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, vDialog.ReusableSideDialog.Tag, 0 )
         GetStringFromAttribute( szTempString_5, zsizeof( szTempString_5 ), vDialog, "ReusableSideDialog", "Tag" );
         ActivateMetaOI_ByName( vSubtask, &vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, szTempString_5, 0 );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = vDialog.ReusableSideWindow.ZKey
         GetIntegerFromAttribute( &lTempInteger_7, vDialog, "ReusableSideWindow", "ZKey" );
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", lTempInteger_7, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:FOR EACH vDialogTemp.Option
            RESULT = SetCursorFirstEntity( vDialogTemp, "Option", "" );
            while ( RESULT > zCURSOR_UNCHANGED )
            { 
               //:IF vDialogTemp.OptAct EXISTS
               lTempInteger_8 = CheckExistenceOfEntity( vDialogTemp, "OptAct" );
               if ( lTempInteger_8 == 0 )
               { 
                  //:SET CURSOR FIRST vDialogTemp.Action WHERE vDialogTemp.Action.ZKey = vDialogTemp.OptAct.ZKey
                  GetIntegerFromAttribute( &lTempInteger_9, vDialogTemp, "OptAct", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Action", "ZKey", lTempInteger_9, "" );
                  //:IF RESULT >= zCURSOR_SET
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:IF vDialogTemp.Action.Type != zWAB_ExitDialogTask
                     if ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", zWAB_ExitDialogTask ) != 0 )
                     { 
                        //://Because the menu actions can be created on separate windows from the control
                        //://actions, we need to make sure these actions are unique.  We will prefix a
                        //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
                        //:szAction = "sm" + vDialogTemp.Action.Tag
                        GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialogTemp, "Action", "Tag", "", 0 );
                        ZeidonStringCopy( szAction, 1, 0, "sm", 1, 0, 35 );
                        ZeidonStringConcat( szAction, 1, 0, szTempString_6, 1, 0, 35 );
                        //:lLth = zstrlen( szAction )
                        lLth = zstrlen( szAction );
                        //://IF lLth > 32
                        //://   MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32",
                        //://                szAction,
                        //://                zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                        //://END

                        //:GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace )
                        GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace );
                     } 

                     //:END
                  } 

                  //:END
               } 

               RESULT = SetCursorNextEntity( vDialogTemp, "Option", "" );
               //:END
            } 

            //:END
         } 

         //:END
         //:DropObjectInstance( vDialogTemp )
         DropObjectInstance( vDialogTemp );
      } 

      //:END
   } 

   //:END

   //:// If the Window or Dialog has a reusable main menu, add the actions from that menu.
   //:ReusableDialogZKey = 0
   ReusableDialogZKey = 0;
   //:IF vDialog.ReusableMainWindow EXISTS
   lTempInteger_10 = CheckExistenceOfEntity( vDialog, "ReusableMainWindow" );
   if ( lTempInteger_10 == 0 )
   { 
      //:ReusableDialogZKey = vDialog.ReusableMainDialog.ZKey
      GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "ReusableMainDialog", "ZKey" );
      //:ReusableWindowZKey = vDialog.ReusableMainWindow.ZKey
      GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "ReusableMainWindow", "ZKey" );
      //:ELSE
   } 
   else
   { 
      //:IF vDialog.DefaultReusableMainWindow EXISTS
      lTempInteger_11 = CheckExistenceOfEntity( vDialog, "DefaultReusableMainWindow" );
      if ( lTempInteger_11 == 0 )
      { 
         //:ReusableDialogZKey = vDialog.DefaultReusableMainDialog.ZKey
         GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "DefaultReusableMainDialog", "ZKey" );
         //:ReusableWindowZKey = vDialog.DefaultReusableMainWindow.ZKey
         GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "DefaultReusableMainWindow", "ZKey" );
      } 

      //:END
   } 

   //:END
   //:IF ReusableDialogZKey != 0  // dks
   if ( ReusableDialogZKey != 0 )
   { 
      //:IF ReusableDialogZKey = vDialog.Dialog.ZKey
      if ( CompareAttributeToInteger( vDialog, "Dialog", "ZKey", ReusableDialogZKey ) == 0 )
      { 
         //:CreateViewFromView( vDialogTemp, vDialog )
         CreateViewFromView( &vDialogTemp, vDialog );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:FOR EACH vDialogTemp.Option
            RESULT = SetCursorFirstEntity( vDialogTemp, "Option", "" );
            while ( RESULT > zCURSOR_UNCHANGED )
            { 
               //:IF vDialogTemp.OptAct EXISTS
               lTempInteger_12 = CheckExistenceOfEntity( vDialogTemp, "OptAct" );
               if ( lTempInteger_12 == 0 )
               { 
                  //:SET CURSOR FIRST vDialogTemp.Action WHERE vDialogTemp.Action.ZKey = vDialogTemp.OptAct.ZKey
                  GetIntegerFromAttribute( &lTempInteger_13, vDialogTemp, "OptAct", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Action", "ZKey", lTempInteger_13, "" );
                  //:IF RESULT >= zCURSOR_SET
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:IF vDialogTemp.Action.Type != zWAB_ExitDialogTask
                     if ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", zWAB_ExitDialogTask ) != 0 )
                     { 
                        //://Because the menu actions can be created on separate windows from the control
                        //://actions, we need to make sure these actions are unique.  We will prefix a
                        //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
                        //:szAction = "m" + vDialogTemp.Action.Tag
                        GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialogTemp, "Action", "Tag", "", 0 );
                        ZeidonStringCopy( szAction, 1, 0, "m", 1, 0, 35 );
                        ZeidonStringConcat( szAction, 1, 0, szTempString_7, 1, 0, 35 );
                        //:lLth = zstrlen( szAction )
                        lLth = zstrlen( szAction );
                        //:IF lLth > 32
                        if ( lLth > 32 )
                        { 
                           //:MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32",
                           //:             szAction,
                           //:             zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                           MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32", szAction, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                        } 

                        //:END

                        //:GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace )
                        GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace );
                     } 

                     //:END
                  } 

                  //:END
               } 

               RESULT = SetCursorNextEntity( vDialogTemp, "Option", "" );
               //:END
            } 

            //:END
         } 

         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI_ByZKey( vSubtask, vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 )
         ActivateMetaOI_ByZKey( vSubtask, &vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:FOR EACH vDialogTemp.Option
            RESULT = SetCursorFirstEntity( vDialogTemp, "Option", "" );
            while ( RESULT > zCURSOR_UNCHANGED )
            { 
               //:IF vDialogTemp.OptAct EXISTS
               lTempInteger_14 = CheckExistenceOfEntity( vDialogTemp, "OptAct" );
               if ( lTempInteger_14 == 0 )
               { 
                  //:SET CURSOR FIRST vDialogTemp.Action WHERE vDialogTemp.Action.ZKey = vDialogTemp.OptAct.ZKey
                  GetIntegerFromAttribute( &lTempInteger_15, vDialogTemp, "OptAct", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Action", "ZKey", lTempInteger_15, "" );
                  //:IF RESULT >= zCURSOR_SET
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:IF vDialogTemp.Action.Type != zWAB_ExitDialogTask
                     if ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", zWAB_ExitDialogTask ) != 0 )
                     { 
                        //://Because the menu actions can be created on separate windows from the control
                        //://actions, we need to make sure these actions are unique.  We will prefix a
                        //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
                        //:szAction = "m" + vDialogTemp.Action.Tag
                        GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialogTemp, "Action", "Tag", "", 0 );
                        ZeidonStringCopy( szAction, 1, 0, "m", 1, 0, 35 );
                        ZeidonStringConcat( szAction, 1, 0, szTempString_8, 1, 0, 35 );
                        //:lLth = zstrlen( szAction )
                        lLth = zstrlen( szAction );
                        //:IF lLth > 32
                        if ( lLth > 32 )
                        { 
                           //:MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32",
                           //:             szAction,
                           //:             zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                           MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32", szAction, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                        } 

                        //:END

                        //:GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace )
                        GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace );
                     } 

                     //:END
                  } 

                  //:END
               } 

               RESULT = SetCursorNextEntity( vDialogTemp, "Option", "" );
               //:END
            } 

            //:END
         } 

         //:END
         //:DropObjectInstance( vDialogTemp )
         DropObjectInstance( vDialogTemp );
      } 

      //:END
   } 

   //:END

   //:// If the Window or Dialog has a reusable main menu for actions only, add the actions from that menu.
   //:ReusableDialogZKey = 0
   ReusableDialogZKey = 0;
   //:IF vDialog.ReusableActionWindow EXISTS
   lTempInteger_16 = CheckExistenceOfEntity( vDialog, "ReusableActionWindow" );
   if ( lTempInteger_16 == 0 )
   { 
      //:ReusableDialogZKey = vDialog.ReusableActionDialog.ZKey
      GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "ReusableActionDialog", "ZKey" );
      //:ReusableWindowZKey = vDialog.ReusableActionWindow.ZKey
      GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "ReusableActionWindow", "ZKey" );
      //:ELSE
   } 
   else
   { 
      //:IF vDialog.DefaultReusableActionWindow EXISTS
      lTempInteger_17 = CheckExistenceOfEntity( vDialog, "DefaultReusableActionWindow" );
      if ( lTempInteger_17 == 0 )
      { 
         //:ReusableDialogZKey = vDialog.DefaultReusableActionDialog.ZKey
         GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "DefaultReusableActionDialog", "ZKey" );
         //:ReusableWindowZKey = vDialog.DefaultReusableActionWindow.ZKey
         GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "DefaultReusableActionWindow", "ZKey" );
      } 

      //:END
   } 

   //:END
   //:IF ReusableDialogZKey != 0  // dks
   if ( ReusableDialogZKey != 0 )
   { 
      //:IF ReusableDialogZKey = vDialog.Dialog.ZKey
      if ( CompareAttributeToInteger( vDialog, "Dialog", "ZKey", ReusableDialogZKey ) == 0 )
      { 
         //:CreateViewFromView( vDialogTemp, vDialog )
         CreateViewFromView( &vDialogTemp, vDialog );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:FOR EACH vDialogTemp.Option
            RESULT = SetCursorFirstEntity( vDialogTemp, "Option", "" );
            while ( RESULT > zCURSOR_UNCHANGED )
            { 
               //:IF vDialogTemp.OptAct EXISTS
               lTempInteger_18 = CheckExistenceOfEntity( vDialogTemp, "OptAct" );
               if ( lTempInteger_18 == 0 )
               { 
                  //:SET CURSOR FIRST vDialogTemp.Action WHERE vDialogTemp.Action.ZKey = vDialogTemp.OptAct.ZKey
                  GetIntegerFromAttribute( &lTempInteger_19, vDialogTemp, "OptAct", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Action", "ZKey", lTempInteger_19, "" );
                  //:IF RESULT >= zCURSOR_SET
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:IF vDialogTemp.Action.Type != zWAB_ExitDialogTask
                     if ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", zWAB_ExitDialogTask ) != 0 )
                     { 
                        //://Because the menu actions can be created on separate windows from the control
                        //://actions, we need to make sure these actions are unique.  We will prefix a
                        //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
                        //:szAction = "ma" + vDialogTemp.Action.Tag
                        GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialogTemp, "Action", "Tag", "", 0 );
                        ZeidonStringCopy( szAction, 1, 0, "ma", 1, 0, 35 );
                        ZeidonStringConcat( szAction, 1, 0, szTempString_9, 1, 0, 35 );
                        //:lLth = zstrlen( szAction )
                        lLth = zstrlen( szAction );
                        //:IF lLth > 32
                        if ( lLth > 32 )
                        { 
                           //:MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32",
                           //:             szAction,
                           //:             zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                           MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32", szAction, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                        } 

                        //:END

                        //:GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace )
                        GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace );
                     } 

                     //:END
                  } 

                  //:END
               } 

               RESULT = SetCursorNextEntity( vDialogTemp, "Option", "" );
               //:END
            } 

            //:END
         } 

         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI_ByZKey( vSubtask, vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 )
         ActivateMetaOI_ByZKey( vSubtask, &vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:FOR EACH vDialogTemp.Option
            RESULT = SetCursorFirstEntity( vDialogTemp, "Option", "" );
            while ( RESULT > zCURSOR_UNCHANGED )
            { 
               //:IF vDialogTemp.OptAct EXISTS
               lTempInteger_20 = CheckExistenceOfEntity( vDialogTemp, "OptAct" );
               if ( lTempInteger_20 == 0 )
               { 
                  //:SET CURSOR FIRST vDialogTemp.Action WHERE vDialogTemp.Action.ZKey = vDialogTemp.OptAct.ZKey
                  GetIntegerFromAttribute( &lTempInteger_21, vDialogTemp, "OptAct", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Action", "ZKey", lTempInteger_21, "" );
                  //:IF RESULT >= zCURSOR_SET
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:IF vDialogTemp.Action.Type != zWAB_ExitDialogTask
                     if ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", zWAB_ExitDialogTask ) != 0 )
                     { 
                        //://Because the menu actions can be created on separate windows from the control
                        //://actions, we need to make sure these actions are unique.  We will prefix a
                        //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
                        //:szAction = "ma" + vDialogTemp.Action.Tag
                        GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialogTemp, "Action", "Tag", "", 0 );
                        ZeidonStringCopy( szAction, 1, 0, "ma", 1, 0, 35 );
                        ZeidonStringConcat( szAction, 1, 0, szTempString_10, 1, 0, 35 );
                        //:lLth = zstrlen( szAction )
                        lLth = zstrlen( szAction );
                        //:IF lLth > 32
                        if ( lLth > 32 )
                        { 
                           //:MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32",
                           //:             szAction,
                           //:             zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                           MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32", szAction, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                        } 

                        //:END

                        //:GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace )
                        GenJSP_Action( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, szAction, lTrace );
                     } 

                     //:END
                  } 

                  //:END
               } 

               RESULT = SetCursorNextEntity( vDialogTemp, "Option", "" );
               //:END
            } 

            //:END
         } 

         //:END
         //:DropObjectInstance( vDialogTemp )
         DropObjectInstance( vDialogTemp );
      } 

      //:END
   } 

   //:END

   //:// OnUnload
   //:szWriteBuffer = "   while ( bDone == 0 && strActionToProcess.equals( ^_OnUnload^ ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   while ( bDone == 0 && strActionToProcess.equals( ^_OnUnload^ ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      bDone = 1;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      bDone = 1;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //://szWriteBuffer = "      session.setAttribute( ^ZeidonAction^, ^_OnUnload^ );"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //:szWriteBuffer = "      if ( vAppSubtask != null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( vAppSubtask != null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         nOptRC = vAppSubtask.CallDialogOperation( strSessionId, ^zGLOBALW^, ^CleanupObjects^, 0 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         nOptRC = vAppSubtask.CallDialogOperation( strSessionId, ^zGLOBALW^, ^CleanupObjects^, 0 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAppSubtask.TraceLine( ^OnUnload UnregisterZeidonApplication: ----------------------------------->>> ^, ^" + szFormName + "^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.TraceLine( ^OnUnload UnregisterZeidonApplication: ----------------------------------->>> ^, ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAppSubtask.UnregisterZeidonApplication( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.UnregisterZeidonApplication( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAppSubtask = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         session.setAttribute( ^ZeidonSubtask^, vAppSubtask );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         session.setAttribute( ^ZeidonSubtask^, vAppSubtask );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      // Next Window is HTML termination"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Next Window is HTML termination", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      strURL = response.encodeRedirectURL( ^logout.jsp^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strURL = response.encodeRedirectURL( ^logout.jsp^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      response.sendRedirect( strURL );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      response.sendRedirect( strURL );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      return;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      return;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// OnTimeout
   //:szWriteBuffer = "   while ( bDone == 0 && strActionToProcess.equals( ^_OnTimeout^ ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   while ( bDone == 0 && strActionToProcess.equals( ^_OnTimeout^ ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      bDone = 1;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      bDone = 1;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //://szWriteBuffer = "      session.setAttribute( ^ZeidonAction^, ^_OnTimeout^ );"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //:szWriteBuffer = "      if ( vAppSubtask != null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( vAppSubtask != null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         nOptRC = vAppSubtask.CallDialogOperation( strSessionId, ^zGLOBALW^, ^CleanupObjects^, 0 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         nOptRC = vAppSubtask.CallDialogOperation( strSessionId, ^zGLOBALW^, ^CleanupObjects^, 0 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAppSubtask.TraceLine( ^OnUnload UnregisterZeidonApplication: ----------------------------------->>> ^, ^" + szFormName + "^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.TraceLine( ^OnUnload UnregisterZeidonApplication: ----------------------------------->>> ^, ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAppSubtask.UnregisterZeidonApplication( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.UnregisterZeidonApplication( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAppSubtask = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         session.setAttribute( ^ZeidonSubtask^, vAppSubtask );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         session.setAttribute( ^ZeidonSubtask^, vAppSubtask );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "      // Next Window is HTML termination"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Next Window is HTML termination", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      strURL = response.encodeRedirectURL( ^TimeOut.html^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strURL = response.encodeRedirectURL( ^TimeOut.html^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      response.sendRedirect( strURL );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      response.sendRedirect( strURL );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      return;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      return;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// OnResubmitPage
   //:szWriteBuffer = "   while ( bDone == 0 && strActionToProcess.equals( ^_OnResubmitPage^ ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   while ( bDone == 0 && strActionToProcess.equals( ^_OnResubmitPage^ ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      bDone = 1;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      bDone = 1;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      session.setAttribute( ^ZeidonAction^, ^_OnResubmitPage^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      session.setAttribute( ^ZeidonAction^, ^_OnResubmitPage^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "      // Input Mapping"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Input Mapping", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      nRC = DoInputMapping( request, session, application );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = DoInputMapping( request, session, application );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( nRC < 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC < 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         break;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         break;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      strURL = response.encodeRedirectURL( ^" + szFormName + ".jsp^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strURL = response.encodeRedirectURL( ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".jsp^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      nRC = 1;  //do the redirection"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = 1;  //do the redirection", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      break;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      break;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   if ( nRC != 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC != 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( nRC > 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC > 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if ( nRC > 1 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( nRC > 1 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            strURL = response.encodeRedirectURL( ^" + szFormName + ".jsp^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            strURL = response.encodeRedirectURL( ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".jsp^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            vAppSubtask.TraceLine( ^Action Error Redirect to: ^, strURL );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            vAppSubtask.TraceLine( ^Action Error Redirect to: ^, strURL );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "         strActionToProcess = " + zQUOTES + zQUOTES + ";"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         strActionToProcess = ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, zQUOTES, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, zQUOTES, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ";", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         response.sendRedirect( strURL );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         response.sendRedirect( strURL );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if ( nRC > -128 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( nRC > -128 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            strActionToProcess = " + zQUOTES + zQUOTES + ";"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            strActionToProcess = ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, zQUOTES, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, zQUOTES, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ";", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            strURL = response.encodeRedirectURL( ^" + szFormName + ".jsp^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            strURL = response.encodeRedirectURL( ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".jsp^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            vAppSubtask.TraceLine( ^Mapping Error Redirect to: %s^, strURL );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            vAppSubtask.TraceLine( ^Mapping Error Redirect to: %s^, strURL );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            response.sendRedirect( strURL );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            response.sendRedirect( strURL );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            vAppSubtask.TraceLine( ^InputMapping Reentry Prevented^, ^^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            vAppSubtask.TraceLine( ^InputMapping Reentry Prevented^, ^^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   if ( strActionToProcess.length( ) == 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( strActionToProcess.length( ) == 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // vAppSubtask.GarbageCollectViews( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // vAppSubtask.GarbageCollectViews( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      return;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      return;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "if ( strErrorFlag != ^Y^ && vAppSubtask != null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "if ( strErrorFlag != ^Y^ && vAppSubtask != null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// DKS 2015.06.19 - Get the InsertPrebuildJavascriptInlineFlag.
   //:SysReadZeidonIni( -1, szSystemIniApplName, "InsertPrebuildJavascriptInlineFlag", szInsertPrebuildJavascriptInline )
   SysReadZeidonIni( -1, szSystemIniApplName, "InsertPrebuildJavascriptInlineFlag", szInsertPrebuildJavascriptInline, zsizeof( szInsertPrebuildJavascriptInline ) );

   //:szJavaScript = ""
   ZeidonStringCopy( szJavaScript, 1, 0, "", 1, 0, 10001 );

   //:// Actions Section Trailer, including prebuild and postbuild code.
   //:InsertBlankFlag = "N"
   ZeidonStringCopy( InsertBlankFlag, 1, 0, "N", 1, 0, 2 );
   //:FOR EACH vDialog.Action
   RESULT = SetCursorFirstEntity( vDialog, "Action", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:FOR EACH vDialog.ActWndEvent
      RESULT = SetCursorFirstEntity( vDialog, "ActWndEvent", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:IF vDialog.ActWndEvent.Type = 1 OR vDialog.ActWndEvent.Type = 2
         if ( CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 1 ) == 0 || CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 2 ) == 0 )
         { 

            //:IF InsertBlankFlag = "Y"
            if ( ZeidonStringCompare( InsertBlankFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
            { 
               //:szWriteBuffer = ""
               ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            } 

            //:END

            //:// KJS 04/30/15 - Inserting javascript code for prebuild action.
            //:IF vDialog.ActWndEvent.Type = 1 AND vDialog.Action.WebJavaScript != ""
            if ( CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 1 ) == 0 && CompareAttributeToString( vDialog, "Action", "WebJavaScript", "" ) != 0 )
            { 
               //:szJavaScript = vDialog.Action.WebJavaScript
               GetVariableFromAttribute( szJavaScript, 0, 'S', 10001, vDialog, "Action", "WebJavaScript", "", 0 );
            } 

            //:END

            //:IF vDialog.ActOper EXISTS
            lTempInteger_22 = CheckExistenceOfEntity( vDialog, "ActOper" );
            if ( lTempInteger_22 == 0 )
            { 

               //:szWriteBuffer = "   nOptRC = vAppSubtask.CallDialogOperation( strSessionId, ^" +
               //:                vDialog.Dialog.Tag + "^, ^" +
               //:                vDialog.ActOper.Name + "^, 1 );"
               GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "Dialog", "Tag", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   nOptRC = vAppSubtask.CallDialogOperation( strSessionId, ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_12, 0, 'S', 33, vDialog, "ActOper", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 1 );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "   if ( nOptRC <= -128 )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nOptRC <= -128 )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "   {"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      vAppSubtask.TraceLine( ^Operation Reentry Prevented^, ^^ );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask.TraceLine( ^Operation Reentry Prevented^, ^^ );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      return;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      return;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "   }"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

               //:szWriteBuffer = "   if ( nOptRC == 2 )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nOptRC == 2 )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "   {"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      zeidon.zView vView;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      zeidon.zView vView;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      String strMessage;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      String strMessage;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      String strURLParameters;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      String strURLParameters;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

               //:szWriteBuffer = "      vView = new zeidon.zView( strSessionId );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      vView = new zeidon.zView( strSessionId );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      nRC = vView.GetView( strSessionId, ^wXferO^, vAppSubtask );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = vView.GetView( strSessionId, ^wXferO^, vAppSubtask );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      strMessage = vView.GetString( strSessionId, ^Root^, ^WebReturnMessage^ );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      strMessage = vView.GetString( strSessionId, ^Root^, ^WebReturnMessage^ );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      strURLParameters = ^?CallingPage=" + szFormName + ".jsp^ +"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      strURLParameters = ^?CallingPage=", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".jsp^ +", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "                         ^&Message=^ + strMessage +"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "                         ^&Message=^ + strMessage +", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "                         ^&DialogName=^ + ^" + vDialog.Dialog.Tag + "^ +"
               GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vDialog, "Dialog", "Tag", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "                         ^&DialogName=^ + ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ +", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "                         ^&OperationName=^ + ^" + vDialog.ActOper.Name + "^;"
               GetVariableFromAttribute( szTempString_14, 0, 'S', 33, vDialog, "ActOper", "Name", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "                         ^&OperationName=^ + ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      strURL = response.encodeRedirectURL( ^MessageDisplay.jsp^ + strURLParameters );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      strURL = response.encodeRedirectURL( ^MessageDisplay.jsp^ + strURLParameters );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      response.sendRedirect( strURL );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      response.sendRedirect( strURL );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      vAppSubtask.TraceLine( ^Pre/Post Redirect to: ^, strURL );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask.TraceLine( ^Pre/Post Redirect to: ^, strURL );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      return;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      return;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "   }"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            } 

            //:END
            //:InsertBlankFlag = "Y"
            ZeidonStringCopy( InsertBlankFlag, 1, 0, "Y", 1, 0, 2 );
         } 

         RESULT = SetCursorNextEntity( vDialog, "ActWndEvent", "" );
         //:END
      } 

      RESULT = SetCursorNextEntity( vDialog, "Action", "" );
      //:END
   } 

   //:END

   //:IF InsertBlankFlag = "Y"
   if ( ZeidonStringCompare( InsertBlankFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:// If there is a dynamic banner name specified in the vKZXMLPGO object for this Dialog, use it. Otherwise, try to use the one in the Dialog definition.
   //:szWriteBuffer = "   nRC = vKZXMLPGO.SetCursorFirst( strSessionId, ^DynamicBannerName^, ^DialogName^, ^" + szDialogTag + "^, ^^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = vKZXMLPGO.SetCursorFirst( strSessionId, ^DynamicBannerName^, ^DialogName^, ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szDialogTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( nRC >= 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC >= 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      strBannerName = vKZXMLPGO.GetString( strSessionId, ^DynamicBannerName^, ^BannerName^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strBannerName = vKZXMLPGO.GetString( strSessionId, ^DynamicBannerName^, ^BannerName^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   if ( strBannerName == null |||| strBannerName.isEmpty( ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( strBannerName == null || strBannerName.isEmpty( ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szBannerName = vDialog.Dialog.WEB_TopBannerName
   GetVariableFromAttribute( szBannerName, 0, 'S', 257, vDialog, "Dialog", "WEB_TopBannerName", "", 0 );

   //:// If a banner include file has been entered by the user, then use this, otherwise
   //:// hardcode "./include/banner.inc" as the banner name.
   //:IF szBannerName != ""
   if ( ZeidonStringCompare( szBannerName, 1, 0, "", 1, 0, 257 ) != 0 )
   { 
      //:szWriteBuffer = "      strBannerName = ^" + szBannerName + "^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strBannerName = ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szBannerName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "      strBannerName = ^./include/banner.inc^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strBannerName = ^./include/banner.inc^;", 1, 0, 10001 );
   } 

   //:END
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:/*
   //:szBannerName = vDialog.Dialog.WEB_TopBannerName
   //:IF szBannerName = ""
   //:   szWriteBuffer = "   strBannerName = vAppSubtask.GetBannerName( strSessionId, ^" + szDialogTag + "^ );"
   //:ELSE
   //:   szWriteBuffer = "   strBannerName = ^" + szBannerName + "^;"
   //:END
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   nRC = wWebXA.GetView( strSessionId, ^wWebXfer^, vAppSubtask );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   if ( nRC > 0 )"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   {"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "      wWebXA.SetAttributeFromVariable( strSessionId, ^Root^, ^CurrentDialog^,"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "                                       ^" + szDialogTag + "^, 'S', 33, ^^, 8 );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "      wWebXA.SetAttributeFromVariable( strSessionId, ^Root^, ^CurrentWindow^,"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "                                       ^" + szWindowTag + "^, 'S', 33, ^^, 8 );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   }"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:*/

   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:/************************* End of MAIN SECTION INITIALIZATION (JSP CODE)   ***********************/

   //:// Start HTML

   //:// HTML SECTION *****************************************************************

   //:// JSP HEADER

   //:szWriteBuffer = "<html>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<html>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<head>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<head>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:IF vDialog.Window.Caption != ""
   if ( CompareAttributeToString( vDialog, "Window", "Caption", "" ) != 0 )
   { 
      //:szWriteBuffer = "<title>" + vDialog.Window.Caption + "</title>"
      GetVariableFromAttribute( szTempString_15, 0, 'S', 255, vDialog, "Window", "Caption", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<title>", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_15, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "</title>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:// KJS 04/30/15 - I can't think why we have the myheader.inc, why we would have that for pages absolute pages.
   //:// We didn't have Window.WEB_PageHeadInclude in the painter, but now it is there.
   //://IF szNoPositioning = "Y" OR szNoPositioning = "S"
   //:   IF vDialog.Window.WEB_PageHeadInclude != ""
   if ( CompareAttributeToString( vDialog, "Window", "WEB_PageHeadInclude", "" ) != 0 )
   { 
      //:   szWriteBuffer = "<%@ include file=^" + vDialog.Window.WEB_PageHeadInclude + "^ %>"
      GetVariableFromAttribute( szTempString_16, 0, 'S', 255, vDialog, "Window", "WEB_PageHeadInclude", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_16, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ %>", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:ELSE
   } 
   else
   { 
      //:   IF vDialog.Dialog.WEB_PageHeadInclude != ""
      if ( CompareAttributeToString( vDialog, "Dialog", "WEB_PageHeadInclude", "" ) != 0 )
      { 
         //:   szWriteBuffer = "<%@ include file=^" + vDialog.Dialog.WEB_PageHeadInclude  + "^ %>"
         GetVariableFromAttribute( szTempString_17, 0, 'S', 255, vDialog, "Dialog", "WEB_PageHeadInclude", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_17, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ %>", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         //:ELSE
      } 
      else
      { 
         //:   szWriteBuffer = "<%@ include file=^./include/head.inc^ %>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^./include/head.inc^ %>", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      } 

      //:   END
   } 

   //:   END
   //://ELSE
   //://   szWriteBuffer = "<%@ include file=^./include/myheader.inc^ %>"
   //://   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //://END

   //:// KJS 2/19/08 - Trying to help Jeff with timeout.  Place a
   //:// timeout value in timeout.inc for when to timeout.
   //:szWriteBuffer = "<!-- Timeout.inc has a value for nTimeout which is used to determine when to -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- Timeout.inc has a value for nTimeout which is used to determine when to -->", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "<!-- log a user out.  Timeout.inc is not used if the dialog or window has a timeout value set. -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- log a user out.  Timeout.inc is not used if the dialog or window has a timeout value set. -->", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "<%@ include file=^./include/timeout.inc^ %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^./include/timeout.inc^ %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// KJS 08/06/08 - Instead of using the class="noprint" to not display
   //:// a div or control when print/previewing a page, I think we will use the
   //:// class print.css.  Cleaner and easier to change items that we want hidden/not hidden.
   //:szWriteBuffer = "<link rel=^stylesheet^ type=^text/css^ href=^./css/print.css^ media=^print^ />"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<link rel=^stylesheet^ type=^text/css^ href=^./css/print.css^ media=^print^ />", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:/*****************************  JavaScript Functions Section *****************************************************/

   //:// common.js is used by both the Grid and Calendar controls. Since it's small, we'll always send it.
   //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/common.js^></script>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/common.js^></script>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:IF lSort != 0
   if ( lSort != 0 )
   { 
      //:// css.js and sts.js are used only by the Grid control when sorting is requested. Thus, we'll only send
      //:// it down to the browser when sorting is requested.
      //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/css.js^></script>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/css.js^></script>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/sts.js^></script>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/sts.js^></script>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/validations.js^></script>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/validations.js^></script>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/scw.js^></script>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/scw.js^></script>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// KJS 04/27/11 - I am not sure that we want to always include this js file but if not, then I need
   //:// to loop through all controls (and subcontrols) looking for a div that has a web control property of
   //:// "Show/Hide Toggle". For now I am always including it.
   //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/animatedcollapse.js^></script>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/animatedcollapse.js^></script>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:// KJS 06/09/11 - I am not sure that we want to always include this js file because at the moment, I am putting
   //:// this in because we want to do a md5 hash conversion.
   //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/md5.js^></script>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/md5.js^></script>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:IF szWysiwygEditor != ""
   if ( ZeidonStringCompare( szWysiwygEditor, 1, 0, "", 1, 0, 33 ) != 0 )
   { 

      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "<!-- TinyMCE -->"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- TinyMCE -->", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:szJS_FileName = ""
      ZeidonStringCopy( szJS_FileName, 1, 0, "", 1, 0, 1025 );
      //:SysReadZeidonIni( -1, szSystemIniApplName, "TinyMCEJavaScript", szJS_FileName )
      SysReadZeidonIni( -1, szSystemIniApplName, "TinyMCEJavaScript", szJS_FileName, zsizeof( szJS_FileName ) );
      //:IF szJS_FileName = ""
      if ( ZeidonStringCompare( szJS_FileName, 1, 0, "", 1, 0, 1025 ) == 0 )
      { 
         //:szJS_FileName = "./tinymce/jscripts/tiny_mce/tiny_mce.js"
         ZeidonStringCopy( szJS_FileName, 1, 0, "./tinymce/jscripts/tiny_mce/tiny_mce.js", 1, 0, 1025 );
      } 

      //:END

      //:// Use TinyMCE rather than widgEditor.
      //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^" + szJS_FileName
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szJS_FileName, 1, 0, 10001 );
      //:szWriteBuffer = szWriteBuffer + "^></script>"
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^></script>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:nRC = zSearchSubString( szWysiwygEditor, ".js", "f", 0 )
      nRC = zSearchSubString( szWysiwygEditor, ".js", "f", 0 );
      //:IF nRC < 0
      if ( nRC < 0 )
      { 
         //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/TinyMCE.js^></script>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/TinyMCE.js^></script>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^", 1, 0, 10001 );
         //:szWriteBuffer = szWriteBuffer + szWysiwygEditor
         ZeidonStringConcat( szWriteBuffer, 1, 0, szWysiwygEditor, 1, 0, 10001 );
         //:szWriteBuffer = szWriteBuffer + "^></script>"
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^></script>", 1, 0, 10001 );
      } 

      //:END
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "<!-- /TinyMCE -->"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- /TinyMCE -->", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 


   //:END

   //:// KJS 01/16/07 - If we have tab controls on the screen, Jeff wants to have the declarations up
   //:// here in this section.
   //:CreateViewFromView( vDialogTemp, vDialogRoot )
   CreateViewFromView( &vDialogTemp, vDialogRoot );
   //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
   lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
   //:szEntityName = "Tab"
   ZeidonStringCopy( szEntityName, 1, 0, "Tab", 1, 0, 33 );

   //:// Look for a control with ControlDef of "Tab"
   //:// vDialog.ControlDef.Tag
   //:nRC = SetEntityCursor( vDialogTemp, "ControlDef", "Tag", lControl,
   //:                       szEntityName, "", "", 0, "Window", "" )
   nRC = SetEntityCursor( vDialogTemp, "ControlDef", "Tag", lControl, szEntityName, "", "", 0, "Window", "" );
   //:IF nRC >= zCURSOR_SET
   if ( nRC >= zCURSOR_SET )
   { 
      //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^./js/tabpane.js^></script>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ src=^./js/tabpane.js^></script>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:// KJS 04/30/15 - If we have any javascript code on a window prebuild action, we should add it here.
   //:IF szJavaScript != ""
   if ( ZeidonStringCompare( szJavaScript, 1, 0, "", 1, 0, 10001 ) != 0 )
   { 
      //:// DKS 2015.06.15 - If InsertPrebuildJavascriptInline = "Y" (has to do with KeyRole), then we should not
      //:// add the JavaScript here for prebuild action... will be added in _AfterPageLoaded function.
      //:IF szInsertPrebuildJavascriptInline != "Y"
      if ( ZeidonStringCompare( szInsertPrebuildJavascriptInline, 1, 0, "Y", 1, 0, 2 ) != 0 )
      { 
         //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ >"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^ >", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "      // Javascript code entered by user for Window action prebuild."
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Javascript code entered by user for Window action prebuild.", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         //:szWriteBuffer = szJavaScript
         ZeidonStringCopy( szWriteBuffer, 1, 0, szJavaScript, 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         //:szWriteBuffer = "      // END of Javascript code entered by user."
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      // END of Javascript code entered by user.", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         //:szWriteBuffer = "</script>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "</script>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      } 

      //:END
   } 

   //:END

   //://szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^ src=^tabpane.js^></script>"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "<script language=^JavaScript^ type=^text/javascript^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<script language=^JavaScript^ type=^text/javascript^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "var isWindowClosing = true;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "var isWindowClosing = true;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "var timerID = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "var timerID = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "onerror = handleErr;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "onerror = handleErr;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "window.history.forward( 1 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "window.history.forward( 1 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// Look for additional Tab controls.
   //:LOOP WHILE nRC >= zCURSOR_SET
   while ( nRC >= zCURSOR_SET )
   { 

      //:szWriteBuffer = "var " + vDialogTemp.Control.Tag + ";"
      GetVariableFromAttribute( szTempString_18, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "var ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_18, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ";", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:lControl = zQUAL_STRING + zPOS_NEXT + zRECURS
      lControl = zQUAL_STRING + zPOS_NEXT + zRECURS;

      //:// Look for a control with controldef of "Tab"
      //:// vDialog.ControlDef.Tag
      //:nRC = SetEntityCursor( vDialogTemp, "ControlDef", "Tag", lControl,
      //:                       szEntityName, "", "", 0, "Window", "" )
      nRC = SetEntityCursor( vDialogTemp, "ControlDef", "Tag", lControl, szEntityName, "", "", 0, "Window", "" );
   } 

   //:END

   //:DropView( vDialogTemp )
   DropView( vDialogTemp );

   //:// Place a blank line here for reading purposes.
   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "function handleErr( msg, url, l )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function handleErr( msg, url, l )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //://szWriteBuffer = "// Uncomment the following (invalid) line and put it in some function below to help find the error."
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //://szWriteBuffer = "// document.replace(^http://www.enc.edu/^);"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )

   //:szWriteBuffer = "   var txt = ^There was an error on this page.\n\n^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var txt = ^There was an error on this page.\\n\\n^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   txt += ^Error: ^ + msg + ^\n^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   txt += ^Error: ^ + msg + ^\\n^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   txt += ^URL: ^ + url + ^\n^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   txt += ^URL: ^ + url + ^\\n^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   txt += ^Line: ^ + l + ^\n\n^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   txt += ^Line: ^ + l + ^\\n\\n^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   txt += ^Click OK to continue.\n\n^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   txt += ^Click OK to continue.\\n\\n^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   alert( txt );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   alert( txt );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   return true;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   return true;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "// This function returns Internet Explorer's major version number,"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "// This function returns Internet Explorer's major version number,", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "// or 0 for others. It works by finding the ^MSIE ^ string and"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "// or 0 for others. It works by finding the ^MSIE ^ string and", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "// extracting the version number following the space, up to the decimal"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "// extracting the version number following the space, up to the decimal", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "// point, ignoring the minor version number."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "// point, ignoring the minor version number.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "function msieversion( )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function msieversion( )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var ua = window.navigator.userAgent;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var ua = window.navigator.userAgent;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var msie = ua.indexOf( ^MSIE ^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var msie = ua.indexOf( ^MSIE ^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   if ( msie > 0 )      // if Internet Explorer, return version number"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( msie > 0 )      // if Internet Explorer, return version number", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      return parseInt( ua.substring( msie + 5, ua.indexOf( ^.^, msie ) ) );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      return parseInt( ua.substring( msie + 5, ua.indexOf( ^.^, msie ) ) );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   else                 // if another browser, return 0"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   else                 // if another browser, return 0", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      return 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      return 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //://Function _OnAlmostTimeout
   //:szWriteBuffer = "function _OnAlmostTimeout()"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function _OnAlmostTimeout()", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( _IsDocDisabled( ) == false )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( _IsDocDisabled( ) == false )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      var tStart   = new Date();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var tStart   = new Date();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      alert(^Your session will timeout in one minute.  Please click 'OK' within that time to continue and save your work if necessary.^)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      alert(^Your session will timeout in one minute.  Please click 'OK' within that time to continue and save your work if necessary.^)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "      var tEnd   = new Date();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var tEnd   = new Date();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      var tDiff = tEnd.getTime() - tStart.getTime();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var tDiff = tEnd.getTime() - tStart.getTime();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "      // If the time is less than one minute, resubmit the page.  Otherwise, go to the timeout window."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // If the time is less than one minute, resubmit the page.  Otherwise, go to the timeout window.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( tDiff < 60000 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( tDiff < 60000 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         document." + szFormName + ".zAction.value = ^_OnResubmitPage^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^_OnResubmitPage^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         document." + szFormName + ".submit( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         _OnTimeout( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         _OnTimeout( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //://function _OnTimeout
   //:szWriteBuffer = "function _OnTimeout( )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function _OnTimeout( )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( _IsDocDisabled( ) == false )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( _IsDocDisabled( ) == false )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      _DisableFormElements( true );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      _DisableFormElements( true );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "      document." + szFormName + ".zAction.value = ^_OnTimeout^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^_OnTimeout^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      document." + szFormName + ".submit( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //://function _BeforePageUnload
   //:szWriteBuffer = "function _BeforePageUnload( )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function _BeforePageUnload( )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( _IsDocDisabled( ) == false )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( _IsDocDisabled( ) == false )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      // If the user clicked on the window close box, then"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // If the user clicked on the window close box, then", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      // isWindowClosing will be true.  Otherwise if the user"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // isWindowClosing will be true.  Otherwise if the user", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      // clicked on something else in the page, isWindowClosing will be false."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // clicked on something else in the page, isWindowClosing will be false.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      // If the user clicked the window close box, unregister zeidon."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // If the user clicked the window close box, unregister zeidon.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// If the user hits the close box in the upper right of the window or leave this page to another web site,
   //:// then we want to try a log them out of zeidon because otherwise, we feel we have memory still cached.
   //:// We want to try and eliminate this and determine if the user has left this application and thus do
   //:// necessary clean up.
   //:szWriteBuffer = "      if ( isWindowClosing )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( isWindowClosing )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szNoAutoLogout = vDialogRoot.Dialog.WEB_NoAutoLogOut
   GetVariableFromAttribute( szNoAutoLogout, 0, 'S', 2, vDialogRoot, "Dialog", "WEB_NoAutoLogOut", "", 0 );
   //:// If this is a log on page (like wStartupLogin) then we don't want to have the 'Unregister Zeidon' happen
   //:// if the user leaves the page or refreshes.  It causes problems.
   //:// KJS 01/19/11 - If the window is a popup window, then we are not going to try doing the unload if the user
   //:// hits the close box because most likely on popup windows, user's would close the window this way.
   //:// KJS 02/09/11 - I have added a new checkbox to the dialog properties window so that we can turn off
   //:// automatically logging a user out for the pages of a dialog (currently we don't want this for the budget
   //:// pages in Zencas).  Otherwise, I keep changing this code back and forth to comment out the submit lines.
   //:IF ( vDialog.Window.WEB_RegisterZeidonWindow != "Y" AND szWindowIsPopup = "" AND szNoAutoLogout != "Y" )
   if ( CompareAttributeToString( vDialog, "Window", "WEB_RegisterZeidonWindow", "Y" ) != 0 && ZeidonStringCompare( szWindowIsPopup, 1, 0, "", 1, 0, 2 ) == 0 && ZeidonStringCompare( szNoAutoLogout, 1, 0, "Y", 1, 0, 2 ) != 0 )
   { 
      //:szWriteBuffer = "         document." + szFormName + ".zAction.value = ^_OnUnload^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^_OnUnload^;", 1, 0, 10001 );
      //://szWriteBuffer = "         document." + szFormName + ".zAction.value = ^_OnUnload^;"
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         document." + szFormName + ".submit( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
      //://szWriteBuffer = "         document." + szFormName + ".submit( );"
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "         // These lines are commented out because either we are registering zeidon on this"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         // These lines are commented out because either we are registering zeidon on this", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         // window or this is a popup window so we don't want to do an unload if the user"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         // window or this is a popup window so we don't want to do an unload if the user", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         // closes the window using the red close button."
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         // closes the window using the red close button.", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         //document." + szFormName + ".zAction.value = ^_OnUnload^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         //document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^_OnUnload^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         //document." + szFormName + ".submit( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         //document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //://szWriteBuffer = "      // No action needs to be taken here. This is just a place holder for traces."
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //://szWriteBuffer = "      // alert( document.wFacultDAdviseeList.zAction.value );"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //://function _IsDocDisabled
   //:szWriteBuffer = "function _IsDocDisabled( )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function _IsDocDisabled( )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var theForm;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var theForm;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var j;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var j;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var k;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var k;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   for ( j = 0; j < document.forms.length; j++ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   for ( j = 0; j < document.forms.length; j++ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      theForm = document.forms[ j ];"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      theForm = document.forms[ j ];", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      for ( k = 0; k < theForm.length; k++ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      for ( k = 0; k < theForm.length; k++ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if ( theForm.elements[ k ].name == ^zDisable^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( theForm.elements[ k ].name == ^zDisable^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            return theForm.elements[ k ].disabled;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            return theForm.elements[ k ].disabled;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   return false;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   return false;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //://function _DisableFormElements
   //:szWriteBuffer = "function _DisableFormElements( bDisabled )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function _DisableFormElements( bDisabled )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var theForm;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var theForm;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var type;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var type;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var lis;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var lis;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var thisLi;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var thisLi;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var j;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var j;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var k;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var k;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var bRC = false;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var bRC = false;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   if ( bDisabled && timerID != null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( bDisabled && timerID != null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      clearTimeout( timerID );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      clearTimeout( timerID );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      timerID = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      timerID = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// Controls on the window may have been set as disabled through javascript but
   //:// when we try to get the values for these controls in jsp (response.getParameter)
   //:// they will always be null.  Set any disabled fields to enabled for this reason.
   //:szWriteBuffer = "   // Controls on the window may have been set as disabled through javascript but"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Controls on the window may have been set as disabled through javascript but", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // when we try to get the values for these controls in jsp (response.getParameter)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // when we try to get the values for these controls in jsp (response.getParameter)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // they will always be null.  Set any disabled fields to enabled for this reason."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // they will always be null.  Set any disabled fields to enabled for this reason.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   for ( j = 0; j < document.forms.length; j++ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   for ( j = 0; j < document.forms.length; j++ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      theForm = document.forms[ j ];"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      theForm = document.forms[ j ];", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      for ( k = 0; k < theForm.length; k++ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      for ( k = 0; k < theForm.length; k++ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if (theForm.elements[ k ].disabled == true)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if (theForm.elements[ k ].disabled == true)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "             theForm.elements[ k ].disabled = false;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "             theForm.elements[ k ].disabled = false;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// We want to set some fields as disabled (like buttons and comboboxes) so that
   //:// while the jsp code is processing, users can not select these controls.
   //:// We do not have the above problem with response.getParameter with comboboxes because
   //:// we have a hidden field for every combobox (h + controltag) and we use that for the
   //:// response.getParameter in DoInputMapping.
   //:szWriteBuffer = "   // We want to set some fields as disabled (like buttons and comboboxes) so that"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // We want to set some fields as disabled (like buttons and comboboxes) so that", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // while the jsp code is processing, users can not select these controls."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // while the jsp code is processing, users can not select these controls.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   for ( j = 0; j < document.forms.length; j++ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   for ( j = 0; j < document.forms.length; j++ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      theForm = document.forms[ j ];"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      theForm = document.forms[ j ];", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "      for ( k = 0; k < theForm.length; k++ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      for ( k = 0; k < theForm.length; k++ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         type = theForm.elements[ k ].type;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         type = theForm.elements[ k ].type;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// szWriteBuffer = "         if ( type == ^button^ |||| type == ^checkbox^ |||| type == ^radio^ |||| type == ^select^ )"
   //:// szWriteBuffer = "         if ( type == ^button^ |||| type == ^select-one^ )"
   //:// szWriteBuffer = "         if ( type == ^button^ |||| (type != null && type.indexOf( ^select^ ) == 0) )"
   //:szWriteBuffer = "         if ( type == ^button^ |||| type == ^submit^ |||| (type != null && type.indexOf( ^select^ ) == 0) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( type == ^button^ || type == ^submit^ || (type != null && type.indexOf( ^select^ ) == 0) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            theForm.elements[ k ].disabled = bDisabled;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            theForm.elements[ k ].disabled = bDisabled;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if ( theForm.elements[ k ].name == ^zDisable^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( theForm.elements[ k ].name == ^zDisable^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            theForm.elements[ k ].disabled = bDisabled;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            theForm.elements[ k ].disabled = bDisabled;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            bRC = true;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            bRC = true;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );


   //:szWriteBuffer = "   lis = document.getElementsByTagName( ^li^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   lis = document.getElementsByTagName( ^li^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   for ( k = 0; k < lis.length; k++ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   for ( k = 0; k < lis.length; k++ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      thisLi = lis[ k ];"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      thisLi = lis[ k ];", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      thisLi.disabled = bDisabled;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      thisLi.disabled = bDisabled;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   return bRC;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   return bRC;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// Default button function.
   //:IF vDialog.Window.DfltButton != ""
   if ( CompareAttributeToString( vDialog, "Window", "DfltButton", "" ) != 0 )
   { 
      //:CreateViewFromView( vDialogTemp, vDialog )
      CreateViewFromView( &vDialogTemp, vDialog );
      //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
      lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
      //:nRC = SetEntityCursor( vDialogTemp, "Control", "Tag", lControl,
      //:                       vDialog.Window.DfltButton, "", "", 0, "Window", "" )
      GetStringFromAttribute( szTempString_19, zsizeof( szTempString_19 ), vDialog, "Window", "DfltButton" );
      nRC = SetEntityCursor( vDialogTemp, "Control", "Tag", lControl, szTempString_19, "", "", 0, "Window", "" );
      //:IF nRC >= zCURSOR_SET
      if ( nRC >= zCURSOR_SET )
      { 
         //:IF vDialogTemp.EventAct EXISTS
         lTempInteger_23 = CheckExistenceOfEntity( vDialogTemp, "EventAct" );
         if ( lTempInteger_23 == 0 )
         { 
            //:szWriteBuffer = "function _OnEnter( e )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "function _OnEnter( e )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "{"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   var keycode;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   var keycode;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   if ( window.event )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( window.event )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      keycode = window.event.keyCode;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      keycode = window.event.keyCode;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( e )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( e )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         keycode = e.which;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         keycode = e.which;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         return true;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         return true;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

            //:szWriteBuffer = "   if ( keycode == 13 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( keycode == 13 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      " + vDialogTemp.EventAct.Tag + "( );"
            GetVariableFromAttribute( szTempString_20, 0, 'S', 33, vDialogTemp, "EventAct", "Tag", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_20, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "( );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      return false;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      return false;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      return true;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      return true;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         } 

         //:END
      } 

      //:END
      //:DropView( vDialogTemp )
      DropView( vDialogTemp );
   } 

   //:END

   //://function _AfterPageLoaded
   //:szWriteBuffer = "function _AfterPageLoaded( )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function _AfterPageLoaded( )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "// _DisableFormElements( false );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "// _DisableFormElements( false );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   var szFocusCtrl = document." + szFormName + ".zFocusCtrl.value;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var szFocusCtrl = document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".zFocusCtrl.value;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( szFocusCtrl != ^^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( szFocusCtrl != ^^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      eval( 'document." + szFormName + ".' + szFocusCtrl + '.focus( )' );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      eval( 'document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".' + szFocusCtrl + '.focus( )' );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// Need to know "first" tab index by the time we get here!
   //:IF szFocusCtrlTag != ""
   if ( ZeidonStringCompare( szFocusCtrlTag, 1, 0, "", 1, 0, 33 ) != 0 )
   { 
      //:szWriteBuffer = "   else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      document." + szFormName + "." + szFocusCtrlTag + ".focus( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFocusCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".focus( );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 ) // add a blank line
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // This is where we put out a message from the previous iteration on this window"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // This is where we put out a message from the previous iteration on this window", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var szMsg = document." + szFormName + ".zError.value;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var szMsg = document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".zError.value;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( szMsg != ^^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( szMsg != ^^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      alert( szMsg ); // ^Houston ... We have a problem^"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      alert( szMsg ); // ^Houston ... We have a problem^", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   szMsg = document." + szFormName + ".zOpenFile.value;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   szMsg = document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".zOpenFile.value;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( szMsg != ^^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( szMsg != ^^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      var NewWin = window.open( szMsg );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var NewWin = window.open( szMsg );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( NewWin )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( NewWin )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         NewWin.focus( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         NewWin.focus( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:// szWriteBuffer = "         alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from 'my.enc.edu' for this action.^ );"
   //:szWriteBuffer = "         alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from this site for this action to work.^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from this site for this action to work.^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:IF szKeyRole = "Y"
   if ( ZeidonStringCompare( szKeyRole, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "   var LoginName = document." + szFormName + ".zLoginName.value;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   var LoginName = document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zLoginName.value;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   var keyRole = document." + szFormName + ".zKeyRole.value;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   var keyRole = document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zKeyRole.value;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:CreateViewFromView( vDialogTemp, vDialog )
   CreateViewFromView( &vDialogTemp, vDialog );

   //:// KJS 08/20/15 - We commented out the below code in 08/27/13 in the GenJspJava code. I guess I didn't do that here. :(
   //:// KJS 08/27/13 - I am commenting this code out because we call the Postbuild javascript code below (comment KJS 09/21/2009), so
   //:// this code means we call the javascript code twice. Maybe we should have this instead but for now I am taking it out (the below code
   //:// only looks for Postbuild action (not prebuild) because this is after the page has been rendered.
   //:/* // ePamms needs the following code DKS 2015.09.22
   //:// Check of prebuild and postbuild action jsp code.
   //:FOR EACH vDialogTemp.Action
   //:   FOR EACH vDialogTemp.ActWndEvent
   //:      IF vDialogTemp.ActWndEvent.Type = 1 OR
   //:         vDialogTemp.ActWndEvent.Type = 2
   //:         // DKS 2008.09.10 - We want to insert any javascript code that the
   //:         // user has entered for this pre/post build action.
   //:         szJavaScript = vDialogTemp.Action.WebJavaScript
   //:         IF  szJavaScript != ""
   //:            szWriteBuffer = "   // Javascript code entered by user."
   //:            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:            szWriteBuffer = szJavaScript
   //:            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:            szWriteBuffer = "   // END of Javascript code entered by user."
   //:            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //:         END
   //:      END
   //:   END
   //:END
   //:*/ // ePamms needs the above code ... but not in the C world
   //:// If this Window/Page has a "Start Web Popup" Action with mapping, then we need the following code
   //:// to actually start up the Popup, since the script code for the Action had to do the submit to
   //:// do input mapping.
   //:SET CURSOR FIRST vDialogTemp.Action
   //:           //WHERE ( vDialogTemp.Action.Type = zWAB_StartModalWebPopup OR vDialogTemp.Action.Type = zWAB_StartModelessWebPopup )
   //:           WHERE ( vDialogTemp.Action.Type = 78 OR vDialogTemp.Action.Type = 79 )
   //:             AND vDialogTemp.Action.NoMap = ""
   RESULT = SetCursorFirstEntity( vDialogTemp, "Action", "" );
   if ( RESULT > zCURSOR_UNCHANGED )
   { 
      while ( RESULT > zCURSOR_UNCHANGED && ( ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", 78 ) != 0 && CompareAttributeToInteger( vDialogTemp, "Action", "Type", 79 ) != 0 ) ||
              CompareAttributeToString( vDialogTemp, "Action", "NoMap", "" ) != 0 ) )
      { 
         RESULT = SetCursorNextEntity( vDialogTemp, "Action", "" );
      } 

   } 

   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szWidth = ""
      ZeidonStringCopy( szWidth, 1, 0, "", 1, 0, 11 );
      //:szHeight = ""
      ZeidonStringCopy( szHeight, 1, 0, "", 1, 0, 11 );
      //:szWriteBuffer = "   szMsg = document." + szFormName + ".zOpenPopupWindow.value;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   szMsg = document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zOpenPopupWindow.value;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( szMsg != ^^ )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( szMsg != ^^ )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //://KELLY22
      //:/*  We don't need this now, we look for these errors and window sizes elsewhere
      //:// The Popup size (both X and Y values) will be WebSize / 34,000 to convert Window Size to Web Page Size.
      //:CreateViewFromView( vDialogTemp2, vDialogRoot )
      //:IF vDialogRoot.Dialog.Tag != vDialogTemp.Action.DialogName
      //:   szMsg = "Error in Window, " + vDialogRoot.Window.Tag + ": A 'Set Subwindow' for a Popup exists to another Dialog, which is invalid."
      //:   MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
      //:ELSE
      //:   SET CURSOR FIRST vDialogTemp2.Window WHERE vDialogTemp2.Window.Tag = vDialogTemp.Action.WindowName
      //:   IF RESULT < zCURSOR_SET
      //:      szMsg = "Error in Window, " + vDialogRoot.Window.Tag + ": A 'Set Subwindow' for a Popup exists to a window that doesn't exist."
      //:      MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
      //:   ELSE
      //:      zIntegerToString( szWidth, 10, vDialogTemp2.Window.SZDLG_X / 34000 )
      //:      zIntegerToString( szHeight, 10, vDialogTemp2.Window.SZDLG_Y / 34000 )
      //:   END
      //:END
      //:*/

      //:// KJS 01/25/08 - The popup window was getting the size of the calling window (above code).  Instead, we want the popup window to be
      //:// the size of the painted popup window.  Added some hidden variables to hold this value (gets set in the OnClick function).
      //:szWriteBuffer = "   var strWidth = document." + szFormName + ".zPopupWindowSZX.value;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   var strWidth = document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zPopupWindowSZX.value;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   var strHeight = document." + szFormName + ".zPopupWindowSZY.value;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   var strHeight = document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zPopupWindowSZY.value;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:// KJS 11/19/09 - Aadit doesn't want to have a height or width in wRunRpts because it doesn't allow the print to work correctly (cuts
      //:// the page off if it's long).  The only problem is that even though you can control the page width through css, the popup window
      //:// itself is the size of the browser (not what we always want).  I am keeping this for now because the only other place I use this
      //:// is in wGradeBk but we might want to have a checkbox to say whether the window should be the size of the dialog window or no
      //:// height width given.
      //:// Also adding scrollbars=yes.
      //:szWriteBuffer = "   var strWindowOptions = ^menubar=0,toolbar=0,resizable=1,modal=1,scrollbars=yes^"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   var strWindowOptions = ^menubar=0,toolbar=0,resizable=1,modal=1,scrollbars=yes^", 1, 0, 10001 );
      //://szWriteBuffer = "   var strWindowOptions = ^menubar=0,toolbar=0,resizable=1,width=^ + strWidth + ^,height=^ + strHeight + ^,modal=1^"
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //://szWriteBuffer = "      var NewWin = window.open( szMsg, ^^,^menubar=0,toolbar=0,resizable=1,width=" + szWidth + ",height=" + szHeight + ",modal=1^ );"
      //:szWriteBuffer = "      var NewWin = window.open( szMsg, ^^, strWindowOptions );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      var NewWin = window.open( szMsg, ^^, strWindowOptions );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( NewWin )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( NewWin )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         NewWin.focus( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         NewWin.focus( );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:// szWriteBuffer = "         alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from 'my.enc.edu' for this action.^ );"
      //:szWriteBuffer = "         alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from this site for this action to work.^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from this site for this action to work.^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );

   //:szWriteBuffer = "   document." + szFormName + ".zError.value = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".zError.value = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   document." + szFormName + ".zOpenFile.value = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".zOpenFile.value = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// If this Window/Page has a "Start Web Popup" Action, initialize the zOpenPopupWindow value.
   //:CreateViewFromView( vDialogTemp, vDialog )
   CreateViewFromView( &vDialogTemp, vDialog );
   //:SET CURSOR FIRST vDialogTemp.Action
   //:           //WHERE ( vDialogTemp.Action.Type = zWAB_StartModalWebPopup OR vDialogTemp.Action.Type = zWAB_StartModelessWebPopup )
   //:           WHERE ( vDialogTemp.Action.Type = 78 OR vDialogTemp.Action.Type = 79 )
   //:             AND vDialogTemp.Action.NoMap = ""
   RESULT = SetCursorFirstEntity( vDialogTemp, "Action", "" );
   if ( RESULT > zCURSOR_UNCHANGED )
   { 
      while ( RESULT > zCURSOR_UNCHANGED && ( ( CompareAttributeToInteger( vDialogTemp, "Action", "Type", 78 ) != 0 && CompareAttributeToInteger( vDialogTemp, "Action", "Type", 79 ) != 0 ) ||
              CompareAttributeToString( vDialogTemp, "Action", "NoMap", "" ) != 0 ) )
      { 
         RESULT = SetCursorNextEntity( vDialogTemp, "Action", "" );
      } 

   } 

   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szWriteBuffer = "   document." + szFormName + ".zOpenPopupWindow.value = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zOpenPopupWindow.value = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );

   //:szWriteBuffer = "   if ( timerID != null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( timerID != null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      clearTimeout( timerID );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      clearTimeout( timerID );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      timerID = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      timerID = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// Generate a document entry for each ComboBox on the Page.
   //:IF vDialogRoot.ComboBoxEntry EXISTS
   lTempInteger_24 = CheckExistenceOfEntity( vDialogRoot, "ComboBoxEntry" );
   if ( lTempInteger_24 == 0 )
   { 
      //:FOR EACH vDialogRoot.ComboBoxEntry
      RESULT = SetCursorFirstEntity( vDialogRoot, "ComboBoxEntry", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:szWriteBuffer = "   document." + szFormName + ".h" + vDialogRoot.ComboBoxEntry.Name + ".value = " +
         //:                "document." + szFormName + "." + vDialogRoot.ComboBoxEntry.Name + ".value"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   document.", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".h", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_21, 0, 'S', 255, vDialogRoot, "ComboBoxEntry", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_21, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".value = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "document.", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_22, 0, 'S', 255, vDialogRoot, "ComboBoxEntry", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_22, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".value", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         RESULT = SetCursorNextEntity( vDialogRoot, "ComboBoxEntry", "" );
      } 

      //:END
      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //://KJS 12/17/07 - It was decided to change the time-out feature to 60 minutes instead of 15 because many
   //://faculty complained about it being too short.  We would really like to control this
   //://using userid so that different users can have different timeout times.
   //://KJS 2/14/08 - Now we have added LogoutTime to the zeidon.ini file as a quick fix.
   //://If the timeout is zero or null then do not have a timeout option for the generated
   //://jsp pages.  If there is a value, then create the timeout according to the value.
   //:/*
   //:SysReadZeidonIni( -1, szSystemIniApplName, "LogoutTime", szTimeout )
   //:IF  szTimeout = "" OR szTimeout = "0"
   //:   szWriteBuffer = "   // No timeout value specified."
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "   timerID = null;"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:ELSE
   //:   szWriteBuffer = "   var delay = 60000 * " + szTimeout + ";  // Timeout in " + szTimeout + " minutes"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "   timerID = setTimeout( ^_OnAlmostTimeout( )^, delay );"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:END
   //:*/

   //:// KJS 2/19/08 - Now trying with a variable in the file timeout.inc.
   //:// szWriteBuffer = "   var delay = 60000 * 15;  // 15 minutes"
   //:szWriteBuffer = "   var varTimeout = document." + szFormName + ".zTimeout.value;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var varTimeout = document.", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".zTimeout.value;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if (varTimeout > 0)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if (varTimeout > 0)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      var delay = 60000 * varTimeout;  // Timeout value in timeout.inc"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var delay = 60000 * varTimeout;  // Timeout value in timeout.inc", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      timerID = setTimeout( ^_OnAlmostTimeout( )^, delay );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      timerID = setTimeout( ^_OnAlmostTimeout( )^, delay );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      timerID = null; // No timeout specified"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      timerID = null; // No timeout specified", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// KJS 09/21/2009
   //:// If there are postbuild actions for this window, and those actions have javascript code on them, we
   //:// need to call the java functions that has the javascript code in them (previously only an operation
   //:// tied to this action was called up in the jsp code).  We are going to put a call to these functions
   //:// in the _AfterPageLoaded function.
   //:// Loop through the actions looking for one that has javascript code and place the calls here.
   //:CreateViewFromView( vDialogTemp, vDialog )
   CreateViewFromView( &vDialogTemp, vDialog );
   //:FOR EACH vDialogTemp.Action
   RESULT = SetCursorFirstEntity( vDialogTemp, "Action", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 

      //:FOR EACH vDialogTemp.ActWndEvent
      RESULT = SetCursorFirstEntity( vDialogTemp, "ActWndEvent", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 

         //:// DKS 2015.05.15 - for prebuild, need javascript code inserted directly into _AfterPageLoaded function,IF lActionType = zWAB_StayOnWindow AND
         //:// if szInsertPrebuildJavascriptInline = "Y", otherwise the prebuild javascript code is called in the
         //:// <head> section. InsertPrebuildJavascriptInline has to do with KeyRole code.
         //:// do not mess with szJavaScript here ... szJavaScript = vDialogTemp.Action.WebJavaScript
         //:IF vDialogTemp.ActWndEvent.Type = 1 AND szInsertPrebuildJavascriptInline = "Y"
         if ( CompareAttributeToInteger( vDialogTemp, "ActWndEvent", "Type", 1 ) == 0 && ZeidonStringCompare( szInsertPrebuildJavascriptInline, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:// Action is Prebuild.
            //:IF vDialogTemp.Action.WebJavaScript != ""
            if ( CompareAttributeToString( vDialogTemp, "Action", "WebJavaScript", "" ) != 0 )
            { 
               //:szWriteBuffer = "   // Prebuild action has javascript code entered by user."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Prebuild action has javascript code entered by user.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = vDialogTemp.Action.WebJavaScript
               GetVariableFromAttribute( szWriteBuffer, 0, 'S', 10001, vDialogTemp, "Action", "WebJavaScript", "", 0 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "   // END of Javascript code entered by user."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   // END of Javascript code entered by user.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
            } 

            //:END
         } 

         //:END
         //:IF vDialogTemp.ActWndEvent.Type = 2  // Action is postbuild.
         if ( CompareAttributeToInteger( vDialogTemp, "ActWndEvent", "Type", 2 ) == 0 )
         { 

            //:IF vDialogTemp.Action.WebJavaScript != ""
            if ( CompareAttributeToString( vDialogTemp, "Action", "WebJavaScript", "" ) != 0 )
            { 

               //:szWriteBuffer = "   // Postbuild actions that have javascript code."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Postbuild actions that have javascript code.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szActionTag = vDialogTemp.Action.Tag
               GetVariableFromAttribute( szActionTag, 0, 'S', 35, vDialogTemp, "Action", "Tag", "", 0 );
               //:szWriteBuffer = "   " + szActionTag + "( );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "( );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            } 


            //:END
         } 

         RESULT = SetCursorNextEntity( vDialogTemp, "ActWndEvent", "" );

         //:END
      } 

      RESULT = SetCursorNextEntity( vDialogTemp, "Action", "" );
      //:END
   } 

   //:END
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );

   //:// Because there is some postbuild code that could be called where isWindowClosing could be set to false, re-initialize it
   //:// again after the page has been loaded.
   //:szWriteBuffer = "   isWindowClosing = true;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   isWindowClosing = true;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   document.body.style.cursor = ^default^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   document.body.style.cursor = ^default^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// ******************************   End of _AfterPageLoaded ***********************

   //://KJS 10/19/07 - This is a generic function for any grids that have a
   //://checkbox on it.  If there is no "text" for this checkbox (so the header would be blank)
   //://we are going to create a checkbox in the grid header that calls this function.
   //://This will select all or unselect all the checkboxes in the grid.
   //:szWriteBuffer = "function CheckAllInGrid(id, CheckBoxName)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "function CheckAllInGrid(id, CheckBoxName)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "{"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var wcontrols = id.form.elements;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var wcontrols = id.form.elements;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var check = id.checked;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var check = id.checked;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   var wcontrol, i = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   var wcontrol, i = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "   while ( (wcontrol = wcontrols[ i++ ]) != null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   while ( (wcontrol = wcontrols[ i++ ]) != null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      //Check to see if the checkbox belongs to this table then check it."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      //Check to see if the checkbox belongs to this table then check it.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( wcontrol.name.indexOf( CheckBoxName ) != -1 && wcontrol.type == 'checkbox' )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( wcontrol.name.indexOf( CheckBoxName ) != -1 && wcontrol.type == 'checkbox' )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         wcontrol.checked = check;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         wcontrol.checked = check;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "}"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// ***********************    Generate JavaScript Function routine for each Action.   ***************
   //:FOR EACH vDialog.Action
   RESULT = SetCursorFirstEntity( vDialog, "Action", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 

      //:szActionTag = vDialog.Action.Tag
      GetVariableFromAttribute( szActionTag, 0, 'S', 35, vDialog, "Action", "Tag", "", 0 );
      //:nRC = zstrcmpi( szActionTag, "alt-f4" )
      nRC = zstrcmpi( szActionTag, "alt-f4" );
      //:IF nRC = 0
      if ( nRC == 0 )
      { 
         //:szActionTag = "AltF4"
         ZeidonStringCopy( szActionTag, 1, 0, "AltF4", 1, 0, 35 );
      } 

      //:END

      //:szListButtonFlag = ""
      ZeidonStringCopy( szListButtonFlag, 1, 0, "", 1, 0, 2 );
      //:IF vDialog.ActEvent EXISTS AND vDialog.ActCtrl EXISTS
      lTempInteger_25 = CheckExistenceOfEntity( vDialog, "ActEvent" );
      lTempInteger_26 = CheckExistenceOfEntity( vDialog, "ActCtrl" );
      if ( lTempInteger_25 == 0 && lTempInteger_26 == 0 )
      { 

         //:// Determine if Action for the ActCtrl is for a PushBtn within a Grid or HyperText (not hyperlink)
         //:// or an image (Bitmap or BitmapBtn) within a Grid..
         //:szCtrlTag = vDialog.ActCtrl.Tag
         GetVariableFromAttribute( szCtrlTag, 0, 'S', 33, vDialog, "ActCtrl", "Tag", "", 0 );
         //:CreateViewFromViewForTask( vDialogTemp, vDialogRoot, 0 )
         CreateViewFromViewForTask( &vDialogTemp, vDialogRoot, 0 );
         //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
         lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
         //://KJS 10/24/07 - Right now if there is an action that is called more than once on a window and
         //://one of the places the action is called is not from a PushBtn or GridEditCtl then
         //://this doesn't always work.  I just had a case where there was an action on RowSelect
         //://on the grid and the action was called from a hottext.  zListButtonFlag did not get set.
         //:nRC = SetEntityCursor( vDialogTemp, "Control", "Tag", lControl, szCtrlTag, "", "", 0, "Window", "" )
         nRC = SetEntityCursor( vDialogTemp, "Control", "Tag", lControl, szCtrlTag, "", "", 0, "Window", "" );
         //:IF nRC >= zCURSOR_SET
         if ( nRC >= zCURSOR_SET )
         { 
            //:szTempStr = vDialogTemp.ControlDef.Tag
            GetVariableFromAttribute( szTempStr, 0, 'S', 51, vDialogTemp, "ControlDef", "Tag", "", 0 );
            //:IF szTempStr = "PushBtn" OR szTempStr = "GridEditCtl" OR szTempStr = "Bitmap" OR szTempStr = "BitmapBtn" OR szTempStr = "GridCheckCtl" OR szTempStr = "CheckBox"
            if ( ZeidonStringCompare( szTempStr, 1, 0, "PushBtn", 1, 0, 51 ) == 0 || ZeidonStringCompare( szTempStr, 1, 0, "GridEditCtl", 1, 0, 51 ) == 0 || ZeidonStringCompare( szTempStr, 1, 0, "Bitmap", 1, 0, 51 ) == 0 ||
                 ZeidonStringCompare( szTempStr, 1, 0, "BitmapBtn", 1, 0, 51 ) == 0 || ZeidonStringCompare( szTempStr, 1, 0, "GridCheckCtl", 1, 0, 51 ) == 0 || ZeidonStringCompare( szTempStr, 1, 0, "CheckBox", 1, 0, 51 ) == 0 )
            { 

               //:// The Control for the Action was a Pushbutton or HyperText.
               //:// Identify if this Control is inside a Grid.
               //:nRC = 0
               nRC = 0;
               //:LOOP WHILE nRC = 0 AND szListButtonFlag = ""
               while ( nRC == 0 && ZeidonStringCompare( szListButtonFlag, 1, 0, "", 1, 0, 2 ) == 0 )
               { 
                  //:nRC = ResetViewFromSubobject( vDialogTemp )
                  nRC = ResetViewFromSubobject( vDialogTemp );
                  //:IF nRC = 0 AND vDialogTemp.ControlDef EXISTS
                  lTempInteger_27 = CheckExistenceOfEntity( vDialogTemp, "ControlDef" );
                  if ( nRC == 0 && lTempInteger_27 == 0 )
                  { 
                     //:IF vDialogTemp.ControlDef.Tag = "Grid"  // vDialogTemp.ControlDef.Key = 2010
                     if ( CompareAttributeToString( vDialogTemp, "ControlDef", "Tag", "Grid" ) == 0 )
                     { 
                        //:// The parent of the this control is a Grid, so indicate for later.
                        //:szListButtonFlag = "Y"
                        ZeidonStringCopy( szListButtonFlag, 1, 0, "Y", 1, 0, 2 );
                     } 

                     //:END
                  } 

                  //:END
               } 

               //:END
            } 

            //:END
         } 


         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
      } 


      //:END

      //:// Event is start email.
      //:IF vDialog.Action.Type = zWAB_StartEmailClient OR
      //:   vDialog.Action.Type = zWAB_StartEmailClientBCC OR
      //:   vDialog.Action.Type = zWAB_StartEmailClientCC
      if ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_StartEmailClient ) == 0 || CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_StartEmailClientBCC ) == 0 ||
           CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_StartEmailClientCC ) == 0 )
      { 

         //:szWriteBuffer = "function " + szActionTag + "( )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "function ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "{"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

         //:szWriteBuffer = "   // This is for indicating whether the user hit the window close box."
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   // This is for indicating whether the user hit the window close box.", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   isWindowClosing = false;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   isWindowClosing = false;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

         //:IF vDialog.ActWndEvent DOES NOT EXIST OR  // don't include pre/post build java code here
         lTempInteger_28 = CheckExistenceOfEntity( vDialog, "ActWndEvent" );
         //:   (vDialog.ActWndEvent.Type != 1 AND vDialog.ActWndEvent.Type != 2)
         if ( lTempInteger_28 != 0 || ( CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 1 ) != 0 && CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 2 ) != 0 ) )
         { 

            //://KJS 11/16/2007 - We want to insert any javascript code that the
            //://user has entered for this action.  This will be put before the action
            //://generated code for submitting.  If the user wants to skip the
            //://generated code, the inserted code should end with a return.
            //:szJavaScript = vDialog.Action.WebJavaScript
            GetVariableFromAttribute( szJavaScript, 0, 'S', 10001, vDialog, "Action", "WebJavaScript", "", 0 );
            //:IF szJavaScript != "" AND vDialog.Action.WebJavaScriptLocation = ""
            if ( ZeidonStringCompare( szJavaScript, 1, 0, "", 1, 0, 10001 ) != 0 && CompareAttributeToString( vDialog, "Action", "WebJavaScriptLocation", "" ) == 0 )
            { 
               //:szWriteBuffer = "      // Javascript code entered by user."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Javascript code entered by user.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
               //:szWriteBuffer = szJavaScript
               ZeidonStringCopy( szWriteBuffer, 1, 0, szJavaScript, 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
               //:szWriteBuffer = "      // END of Javascript code entered by user."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      // END of Javascript code entered by user.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
            } 

            //:END
         } 

         //:END

         //:// Go to generate special code for setting up email entries and starting email client.
         //:GenJSP_EmailEntries( vDialog, vDialogRoot, lFileJSP, szWriteBuffer, szFormName )
         GenJSP_EmailEntries( vDialog, vDialogRoot, lFileJSP, szWriteBuffer, szFormName );

         //:szWriteBuffer = "}"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         //:ELSE
      } 
      else
      { 
         //:IF szListButtonFlag = "Y"
         if ( ZeidonStringCompare( szListButtonFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:szWriteBuffer = "function " + szActionTag + "( strTagEntityKey )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "function ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "( strTagEntityKey )", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "function " + szActionTag + "( )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "function ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "( )", 1, 0, 10001 );
         } 

         //:END
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "{"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

         //:szWriteBuffer = "   // This is for indicating whether the user hit the window close box."
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   // This is for indicating whether the user hit the window close box.", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   isWindowClosing = false;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   isWindowClosing = false;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

         //:// This Action is Startup Web Popup WITHOUT mapping, so generate unique statements for that case.
         //:IF ( vDialog.Action.Type = zWAB_StartModalWebPopup OR vDialog.Action.Type = zWAB_StartModelessWebPopup ) AND vDialog.Action.NoMap = "Y"
         if ( ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_StartModalWebPopup ) == 0 || CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_StartModelessWebPopup ) == 0 ) &&
              CompareAttributeToString( vDialog, "Action", "NoMap", "Y" ) == 0 )
         { 

            //:IF vDialog.ActWndEvent DOES NOT EXIST OR  // don't include pre/post build java code here
            lTempInteger_29 = CheckExistenceOfEntity( vDialog, "ActWndEvent" );
            //:   (vDialog.ActWndEvent.Type != 1 AND vDialog.ActWndEvent.Type != 2)
            if ( lTempInteger_29 != 0 || ( CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 1 ) != 0 && CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 2 ) != 0 ) )
            { 

               //://KJS 11/16/2007 - We want to insert any javascript code that the
               //://user has entered for this action.  This will be put before the action
               //://generated code for submitting.
               //:szJavaScript = vDialog.Action.WebJavaScript
               GetVariableFromAttribute( szJavaScript, 0, 'S', 10001, vDialog, "Action", "WebJavaScript", "", 0 );
               //:IF szJavaScript != "" AND vDialog.Action.WebJavaScriptLocation = ""
               if ( ZeidonStringCompare( szJavaScript, 1, 0, "", 1, 0, 10001 ) != 0 && CompareAttributeToString( vDialog, "Action", "WebJavaScriptLocation", "" ) == 0 )
               { 
                  //:szWriteBuffer = "      // Javascript code entered by user."
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Javascript code entered by user.", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                  //:szWriteBuffer = szJavaScript
                  ZeidonStringCopy( szWriteBuffer, 1, 0, szJavaScript, 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                  //:szWriteBuffer = "      // END of Javascript code entered by user."
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "      // END of Javascript code entered by user.", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
               } 

               //:END
            } 

            //:END

            //://szWriteBuffer = "   isWindowClosing = false;"
            //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )

            //:szDialogTag = vDialog.Action.DialogName
            GetVariableFromAttribute( szDialogTag, 0, 'S', 33, vDialog, "Action", "DialogName", "", 0 );
            //:szWindowTag = vDialog.Action.WindowName
            GetVariableFromAttribute( szWindowTag, 0, 'S', 33, vDialog, "Action", "WindowName", "", 0 );

            //:// We are opening a popup window within this dialog
            //:IF szDialogTag = vDialogRoot.Dialog.Tag
            if ( CompareAttributeToString( vDialogRoot, "Dialog", "Tag", szDialogTag ) == 0 )
            { 
               //:// KJS 01/25/08 - The popup window was getting the size of the calling window (aboe code).  Instead, we want the popup window to be
               //:// the size of the painted popup window.  Added some hidden variables to hold this value.
               //:CreateViewFromView( vDialogTemp2, vDialogRoot )
               CreateViewFromView( &vDialogTemp2, vDialogRoot );
               //:SET CURSOR FIRST vDialogTemp2.Window WHERE vDialogTemp2.Window.Tag = szWindowTag
               RESULT = SetCursorFirstEntityByString( vDialogTemp2, "Window", "Tag", szWindowTag, "" );
               //:IF RESULT < zCURSOR_SET
               if ( RESULT < zCURSOR_SET )
               { 
                  //:szMsg = "Error in Window, " + vDialog.Window.Tag + ": A 'Set Subwindow' for a Popup exists to a window that doesn't exist: " + szWindowTag
                  GetVariableFromAttribute( szTempString_23, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
                  ZeidonStringCopy( szMsg, 1, 0, "Error in Window, ", 1, 0, 257 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_23, 1, 0, 257 );
                  ZeidonStringConcat( szMsg, 1, 0, ": A 'Set Subwindow' for a Popup exists to a window that doesn't exist: ", 1, 0, 257 );
                  ZeidonStringConcat( szMsg, 1, 0, szWindowTag, 1, 0, 257 );
                  //:MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                  MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                  //:ELSE
               } 
               else
               { 
                  //:// KJS 01/30/08 - Want the popup window to be opened with the correct size of the painted popup window
                  //:// not just a generic number (had been 600,300).
                  //:zIntegerToString( szWidth, 10, vDialogTemp2.Window.SZDLG_X / 34000 )
                  GetIntegerFromAttribute( &lTempInteger_30, vDialogTemp2, "Window", "SZDLG_X" );
                  zIntegerToString( szWidth, 10, lTempInteger_30 / 34000 );
                  //:zIntegerToString( szHeight, 10, vDialogTemp2.Window.SZDLG_Y / 34000 )
                  GetIntegerFromAttribute( &lTempInteger_31, vDialogTemp2, "Window", "SZDLG_Y" );
                  zIntegerToString( szHeight, 10, lTempInteger_31 / 34000 );
               } 

               //:END
               //:DropView( vDialogTemp2 )
               DropView( vDialogTemp2 );
               //:ELSE
            } 
            else
            { 
               //:// We are opening a popup window in a different dialog.  We want the size of the
               //:// popup window.  Need to open the other dialog.
               //:ActivateMetaOI_ByName( vSubtask, vDialogTemp2, 0, zREFER_DIALOG_META, zSINGLE, szDialogTag, 0 )
               ActivateMetaOI_ByName( vSubtask, &vDialogTemp2, 0, zREFER_DIALOG_META, zSINGLE, szDialogTag, 0 );
               //:SET CURSOR FIRST vDialogTemp2.Window WHERE vDialogTemp2.Window.Tag = szWindowTag
               RESULT = SetCursorFirstEntityByString( vDialogTemp2, "Window", "Tag", szWindowTag, "" );
               //:IF RESULT >= zCURSOR_SET
               if ( RESULT >= zCURSOR_SET )
               { 
                  //:zIntegerToString( szWidth, 10, vDialogTemp2.Window.SZDLG_X / 34000 )
                  GetIntegerFromAttribute( &lTempInteger_32, vDialogTemp2, "Window", "SZDLG_X" );
                  zIntegerToString( szWidth, 10, lTempInteger_32 / 34000 );
                  //:zIntegerToString( szHeight, 10, vDialogTemp2.Window.SZDLG_Y / 34000 )
                  GetIntegerFromAttribute( &lTempInteger_33, vDialogTemp2, "Window", "SZDLG_Y" );
                  zIntegerToString( szHeight, 10, lTempInteger_33 / 34000 );
                  //:ELSE
               } 
               else
               { 

                  //:szMsg = "Error in Window, " + vDialogRoot.Window.Tag + ": A 'Set Subwindow' for a Popup exists to a dialog.window that doesn't exist: " +
                  //:        szDialogTag + "." + szWindowTag
                  GetVariableFromAttribute( szTempString_24, 0, 'S', 33, vDialogRoot, "Window", "Tag", "", 0 );
                  ZeidonStringCopy( szMsg, 1, 0, "Error in Window, ", 1, 0, 257 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_24, 1, 0, 257 );
                  ZeidonStringConcat( szMsg, 1, 0, ": A 'Set Subwindow' for a Popup exists to a dialog.window that doesn't exist: ", 1, 0, 257 );
                  ZeidonStringConcat( szMsg, 1, 0, szDialogTag, 1, 0, 257 );
                  ZeidonStringConcat( szMsg, 1, 0, ".", 1, 0, 257 );
                  ZeidonStringConcat( szMsg, 1, 0, szWindowTag, 1, 0, 257 );
                  //:MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                  MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
               } 


               //:END
               //:DropObjectInstance( vDialogTemp2 )
               DropObjectInstance( vDialogTemp2 );
            } 


            //:END

            //:szWriteBuffer = "   var NewWin = window.open( ^" + szDialogTag + szWindowTag + ".jsp^, ^^,^menubar=0,toolbar=0,resizable=1,width=" + szWidth +
            //:                ",height=" + szHeight + ",modal=1^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   var NewWin = window.open( ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szDialogTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szWindowTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".jsp^, ^^,^menubar=0,toolbar=0,resizable=1,width=", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ",height=", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHeight, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ",modal=1^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

            //:szWriteBuffer = "   if ( NewWin )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( NewWin )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      NewWin.focus( );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      NewWin.focus( );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:// szWriteBuffer = "      alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from 'my.enc.edu' for this action.^ );"
            //:szWriteBuffer = "      alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from this site for this action to work.^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      alert( ^Pop-up windows are being blocked.  You need to set your browser to allow pop-ups from this site for this action to work.^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:ELSE
         } 
         else
         { 
            //:// Print Window
            //:IF vDialog.Action.Type = 60
            if ( CompareAttributeToInteger( vDialog, "Action", "Type", 60 ) == 0 )
            { 
               //:szWriteBuffer = "   window.print();"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   window.print();", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:ELSE
            } 
            else
            { 
               //:IF vDialog.Action.Type = zWAB_StayOnWindow AND vDialog.Action.WebJavaScript != ""
               if ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_StayOnWindow ) == 0 && CompareAttributeToString( vDialog, "Action", "WebJavaScript", "" ) != 0 )
               { 

                  //:// KJS 08/14/2009 - If the window type is zWAB_StayOnWindow (no refresh) and we have Javascript code on this action
                  //:// then we don't want to do the .submit (which we really don't want to do if the action is zWAB_StayOnWindow but I'm
                  //:// afraid there might be places where we kept the action zWAB_StayOnWindow because we knew it would always put
                  //:// the submit in).
                  //:szWriteBuffer = "   if ( _IsDocDisabled( ) == false )"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( _IsDocDisabled( ) == false )", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                  //:szWriteBuffer = "   {"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

                  //:szJavaScript = vDialog.Action.WebJavaScript
                  GetVariableFromAttribute( szJavaScript, 0, 'S', 10001, vDialog, "Action", "WebJavaScript", "", 0 );
                  //:// dks Note to Kelly 2016.04.26 - Since ePamms is not using C generation, make this do what you want
                  //:// dks 2015.06.20 - remove prebuild javascript if it is being inserted in _AfterPageLoaded
                  //:IF szInsertPrebuildJavascriptInline = "Y"
                  if ( ZeidonStringCompare( szInsertPrebuildJavascriptInline, 1, 0, "Y", 1, 0, 2 ) == 0 )
                  { 
                     //:IF vDialog.ActWndEvent EXISTS AND vDialog.ActWndEvent.Type = 1
                     lTempInteger_34 = CheckExistenceOfEntity( vDialog, "ActWndEvent" );
                     if ( lTempInteger_34 == 0 && CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 1 ) == 0 )
                     { 
                        //:// prebuild javascript being inserted inline in _AfterPageLoaded
                        //:ELSE
                     } 
                     else
                     { 
                        //:// otherwise, we need the javascript code
                        //:IF  szJavaScript != ""
                        if ( ZeidonStringCompare( szJavaScript, 1, 0, "", 1, 0, 10001 ) != 0 )
                        { 
                           //:szWriteBuffer = "      // Javascript code entered by user."
                           ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Javascript code entered by user.", 1, 0, 10001 );
                           //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                           WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                           //:szWriteBuffer = szJavaScript
                           ZeidonStringCopy( szWriteBuffer, 1, 0, szJavaScript, 1, 0, 10001 );
                           //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                           WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                           //:szWriteBuffer = "      // END of Javascript code entered by user."
                           ZeidonStringCopy( szWriteBuffer, 1, 0, "      // END of Javascript code entered by user.", 1, 0, 10001 );
                           //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                           WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                        } 

                        //:END
                     } 

                     //:END
                     //:// DKS 2015.07.07 - and we always want the submit
                     //:szWriteBuffer = "      document." + szFormName + ".zAction.value = ^" + szActionTag + "^;"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     //:szWriteBuffer = "      document." + szFormName + ".submit( );"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     //:ELSE
                  } 
                  else
                  { 
                     //:IF  szJavaScript != ""
                     if ( ZeidonStringCompare( szJavaScript, 1, 0, "", 1, 0, 10001 ) != 0 )
                     { 
                        //:szWriteBuffer = "      // Javascript code entered by user."
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Javascript code entered by user.", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                        //:szWriteBuffer = szJavaScript
                        ZeidonStringCopy( szWriteBuffer, 1, 0, szJavaScript, 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                        //:szWriteBuffer = "      // END of Javascript code entered by user."
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      // END of Javascript code entered by user.", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                     } 

                     //:END
                  } 

                  //:END
                  //:szWriteBuffer = "   }"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

                  //:ELSE
               } 
               else
               { 

                  //:// Normal Action.

                  //:szWriteBuffer = "   if ( _IsDocDisabled( ) == false )"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( _IsDocDisabled( ) == false )", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                  //:szWriteBuffer = "   {"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

                  //:// KJS 08/13/13 - I am assuming that Doug put this in. I pass in strEntityKey so I'm not sure why
                  //:// it's here...
                  //:IF szListButtonFlag = "Y"
                  if ( ZeidonStringCompare( szListButtonFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
                  { 
                     //:szWriteBuffer = "      var nIdx = strTagEntityKey.lastIndexOf( '::' );"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "      var nIdx = strTagEntityKey.lastIndexOf( '::' );", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     //:szWriteBuffer = "      var strEntityKey = strTagEntityKey.substring( nIdx + 2 );"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "      var strEntityKey = strTagEntityKey.substring( nIdx + 2 );", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                  } 

                  //:END

                  //:IF vDialog.ActWndEvent DOES NOT EXIST OR  // don't include pre/post build java code here
                  lTempInteger_35 = CheckExistenceOfEntity( vDialog, "ActWndEvent" );
                  //:(vDialog.ActWndEvent.Type != 1 AND vDialog.ActWndEvent.Type != 2)
                  if ( lTempInteger_35 != 0 || ( CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 1 ) != 0 && CompareAttributeToInteger( vDialog, "ActWndEvent", "Type", 2 ) != 0 ) )
                  { 

                     //://KJS 11/16/2007 - We want to insert any javascript code that the
                     //://user has entered for this action.  This will be put before the action
                     //://generated code for submitting.
                     //:szJavaScript = vDialog.Action.WebJavaScript
                     GetVariableFromAttribute( szJavaScript, 0, 'S', 10001, vDialog, "Action", "WebJavaScript", "", 0 );
                     //:IF szJavaScript != "" AND vDialog.Action.WebJavaScriptLocation = ""
                     if ( ZeidonStringCompare( szJavaScript, 1, 0, "", 1, 0, 10001 ) != 0 && CompareAttributeToString( vDialog, "Action", "WebJavaScriptLocation", "" ) == 0 )
                     { 
                        //:szWriteBuffer = "      // Javascript code entered by user."
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Javascript code entered by user.", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                        //:szWriteBuffer = szJavaScript
                        ZeidonStringCopy( szWriteBuffer, 1, 0, szJavaScript, 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                        //:szWriteBuffer = "      // END of Javascript code entered by user."
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      // END of Javascript code entered by user.", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                     } 

                     //:END
                  } 

                  //:END

                  //:// KJS 10/28/10 - Testing this to see how using an hourglass would work while
                  //:// the user is waiting for something to happen.
                  //:szWriteBuffer = "      document.body.style.cursor = ^wait^;"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.body.style.cursor = ^wait^;", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

                  //:// If this function is for Download File, we want to eliminate the _DisableFormElements statement.
                  //:IF vDialog.Action.Type != zWAB_ProcessDownloadFile
                  if ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_ProcessDownloadFile ) != 0 )
                  { 
                     //:szWriteBuffer = "      _DisableFormElements( true );"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "      _DisableFormElements( true );", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
                  } 

                  //:END

                  //:// We need to determine if this Action is on a Group for File Transfer to Server, because we need to
                  //:// use the Form Name from the Group in that case. We will locate the corresponding Action entry under
                  //:// the Control subobject and move up one level to find the Group.
                  //:szTransferFileFlag = ""
                  ZeidonStringCopy( szTransferFileFlag, 1, 0, "", 1, 0, 2 );
                  //:CreateViewFromView( vDialogTemp, vDialog )
                  CreateViewFromView( &vDialogTemp, vDialog );
                  //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
                  lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
                  //:szActionTag = vDialog.Action.Tag
                  GetVariableFromAttribute( szActionTag, 0, 'S', 35, vDialog, "Action", "Tag", "", 0 );
                  //:nRC = SetEntityCursor( vDialogTemp, "EventAct", "Tag", lControl,
                  //:                 szActionTag, "", "", 0, "Window", "" )
                  nRC = SetEntityCursor( vDialogTemp, "EventAct", "Tag", lControl, szActionTag, "", "", 0, "Window", "" );
                  //:IF nRC >= zCURSOR_SET
                  if ( nRC >= zCURSOR_SET )
                  { 
                     //:ResetViewFromSubobject( vDialogTemp )
                     ResetViewFromSubobject( vDialogTemp );
                     //:SET CURSOR FIRST vDialogTemp.WebControlProperty WHERE vDialogTemp.WebControlProperty.Name = "File Transfer to Server"
                     RESULT = SetCursorFirstEntityByString( vDialogTemp, "WebControlProperty", "Name", "File Transfer to Server", "" );
                     //:IF RESULT >= zCURSOR_SET
                     if ( RESULT >= zCURSOR_SET )
                     { 
                        //:szTransferFileFlag = "Y"
                        ZeidonStringCopy( szTransferFileFlag, 1, 0, "Y", 1, 0, 2 );
                     } 

                     //:END
                  } 

                  //:END
                  //:IF szTransferFileFlag = "Y"
                  if ( ZeidonStringCompare( szTransferFileFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
                  { 
                     //:szCtrlTag = vDialogTemp.Control.Tag
                     GetVariableFromAttribute( szCtrlTag, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
                     //:szWriteBuffer = "      document." + szCtrlTag + ".zAction.value = ^" + szActionTag + "^;"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     //:szWriteBuffer = "      document." + szCtrlTag + ".submit( );"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     //:ELSE
                  } 
                  else
                  { 
                     //:IF szListButtonFlag = "Y"
                     if ( ZeidonStringCompare( szListButtonFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
                     { 
                        //:// The Action was on a Button on a Grid, so identify the entry selected.
                        //:szWriteBuffer = "      document." + szFormName + ".zTableRowSelect.value = strEntityKey;"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ".zTableRowSelect.value = strEntityKey;", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     } 

                     //:END

                     //://KELLY
                     //:IF ( vDialog.Action.Type = zWAB_StartModalWebPopup OR vDialog.Action.Type = zWAB_StartModelessWebPopup ) AND vDialog.Action.NoMap = ""
                     if ( ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_StartModalWebPopup ) == 0 || CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_StartModelessWebPopup ) == 0 ) &&
                        CompareAttributeToString( vDialog, "Action", "NoMap", "" ) == 0 )
                     { 
                        //:// This Action is Startup Web Popup WITH mapping, so set zOpenPopupWindow to the next page jsp.
                        //:szDialogTag = vDialog.Action.DialogName
                        GetVariableFromAttribute( szDialogTag, 0, 'S', 33, vDialog, "Action", "DialogName", "", 0 );
                        //:szWindowTag = vDialog.Action.WindowName
                        GetVariableFromAttribute( szWindowTag, 0, 'S', 33, vDialog, "Action", "WindowName", "", 0 );

                        //:szWriteBuffer = "      document." + szFormName + ".zOpenPopupWindow.value = ^" + szDialogTag + szWindowTag + ".jsp^;"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ".zOpenPopupWindow.value = ^", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szDialogTag, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szWindowTag, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ".jsp^;", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

                        //:// We are opening a popup window within this dialog
                        //:IF szDialogTag = vDialogRoot.Dialog.Tag
                        if ( CompareAttributeToString( vDialogRoot, "Dialog", "Tag", szDialogTag ) == 0 )
                        { 
                           //:// KJS 01/25/08 - The popup window was getting the size of the calling window (above code).  Instead, we want the
                           //:// popup window to be the size of the painted popup window.  Added some hidden variables to hold this value.
                           //:CreateViewFromView( vDialogTemp2, vDialogRoot )
                           CreateViewFromView( &vDialogTemp2, vDialogRoot );
                           //:SET CURSOR FIRST vDialogTemp2.Window WHERE vDialogTemp2.Window.Tag = vDialog.Action.WindowName
                           GetStringFromAttribute( szTempString_25, zsizeof( szTempString_25 ), vDialog, "Action", "WindowName" );
                           RESULT = SetCursorFirstEntityByString( vDialogTemp2, "Window", "Tag", szTempString_25, "" );

                           //:IF RESULT >= zCURSOR_SET
                           if ( RESULT >= zCURSOR_SET )
                           { 
                              //:zIntegerToString( szWidth, 10, vDialogTemp2.Window.SZDLG_X / 34000 )
                              GetIntegerFromAttribute( &lTempInteger_36, vDialogTemp2, "Window", "SZDLG_X" );
                              zIntegerToString( szWidth, 10, lTempInteger_36 / 34000 );
                              //:zIntegerToString( szHeight, 10, vDialogTemp2.Window.SZDLG_Y / 34000 )
                              GetIntegerFromAttribute( &lTempInteger_37, vDialogTemp2, "Window", "SZDLG_Y" );
                              zIntegerToString( szHeight, 10, lTempInteger_37 / 34000 );
                              //:ELSE
                           } 
                           else
                           { 
                              //:szMsg = "Error in Window, " + vDialog.Window.Tag + ": A 'Set Subwindow' for a Popup exists to a window that doesn't exist: " + szWindowTag
                              GetVariableFromAttribute( szTempString_25, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
                              ZeidonStringCopy( szMsg, 1, 0, "Error in Window, ", 1, 0, 257 );
                              ZeidonStringConcat( szMsg, 1, 0, szTempString_25, 1, 0, 257 );
                              ZeidonStringConcat( szMsg, 1, 0, ": A 'Set Subwindow' for a Popup exists to a window that doesn't exist: ", 1, 0, 257 );
                              ZeidonStringConcat( szMsg, 1, 0, szWindowTag, 1, 0, 257 );
                              //:MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                              MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                           } 

                           //:END
                           //:DropView( vDialogTemp2 )
                           DropView( vDialogTemp2 );
                           //:ELSE
                        } 
                        else
                        { 
                           //:// We are opening a popup window in a different dialog.  We want the size of the
                           //:// popup window.  Need to open the other dialog.
                           //:ActivateMetaOI_ByName( vSubtask, vDialogTemp2, 0, zREFER_DIALOG_META, zSINGLE, szDialogTag, 0 )
                           ActivateMetaOI_ByName( vSubtask, &vDialogTemp2, 0, zREFER_DIALOG_META, zSINGLE, szDialogTag, 0 );
                           //:SET CURSOR FIRST vDialogTemp2.Window WHERE vDialogTemp2.Window.Tag = szWindowTag
                           RESULT = SetCursorFirstEntityByString( vDialogTemp2, "Window", "Tag", szWindowTag, "" );
                           //:IF RESULT >= zCURSOR_SET
                           if ( RESULT >= zCURSOR_SET )
                           { 
                              //:zIntegerToString( szWidth, 10, vDialogTemp2.Window.SZDLG_X / 34000 )
                              GetIntegerFromAttribute( &lTempInteger_38, vDialogTemp2, "Window", "SZDLG_X" );
                              zIntegerToString( szWidth, 10, lTempInteger_38 / 34000 );
                              //:zIntegerToString( szHeight, 10, vDialogTemp2.Window.SZDLG_Y / 34000 )
                              GetIntegerFromAttribute( &lTempInteger_39, vDialogTemp2, "Window", "SZDLG_Y" );
                              zIntegerToString( szHeight, 10, lTempInteger_39 / 34000 );
                              //:ELSE
                           } 
                           else
                           { 

                              //:szMsg = "Error in Window, " + vDialogRoot.Window.Tag + ": A 'Set Subwindow' for a Popup exists to a window that doesn't exist." +
                              //:  szDialogTag + "." + szWindowTag
                              GetVariableFromAttribute( szTempString_26, 0, 'S', 33, vDialogRoot, "Window", "Tag", "", 0 );
                              ZeidonStringCopy( szMsg, 1, 0, "Error in Window, ", 1, 0, 257 );
                              ZeidonStringConcat( szMsg, 1, 0, szTempString_26, 1, 0, 257 );
                              ZeidonStringConcat( szMsg, 1, 0, ": A 'Set Subwindow' for a Popup exists to a window that doesn't exist.", 1, 0, 257 );
                              ZeidonStringConcat( szMsg, 1, 0, szDialogTag, 1, 0, 257 );
                              ZeidonStringConcat( szMsg, 1, 0, ".", 1, 0, 257 );
                              ZeidonStringConcat( szMsg, 1, 0, szWindowTag, 1, 0, 257 );
                              //:MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                              MessageSend( vSubtask, "", "JSP Generation", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                           } 


                           //:END
                           //:DropObjectInstance( vDialogTemp2 )
                           DropObjectInstance( vDialogTemp2 );
                        } 


                        //:END

                        //:szWriteBuffer = "      document." + szFormName + ".zPopupWindowSZX.value = ^" + szWidth + "^;"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ".zPopupWindowSZX.value = ^", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                        //:szWriteBuffer = "      document." + szFormName + ".zPopupWindowSZY.value = ^" + szHeight + "^;"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ".zPopupWindowSZY.value = ^", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szHeight, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     } 


                     //:END

                     //:IF vDialog.Action.Type = zWAB_ExitDialogTask
                     if ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_ExitDialogTask ) == 0 )
                     { 
                        //:// For exiting the Dialog (ie., Session), the Action is OnUnload.
                        //:szWriteBuffer = "      document." + szFormName + ".zAction.value = ^_OnUnload^;"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^_OnUnload^;", 1, 0, 10001 );
                        //:ELSE
                     } 
                     else
                     { 
                        //:szWriteBuffer = "      document." + szFormName + ".zAction.value = ^" + szActionTag + "^;"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
                     } 

                     //:END
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     //:szWriteBuffer = "      document." + szFormName + ".submit( );"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

                     //://Type 84 is "Return from Web Popup/No Refresh
                     //://Type 85 is "Return from Web Popup/Refresh
                     //://We need to put in lines to close the popup window.
                     //:IF ( vDialog.Action.Type = zWAB_ReturnFromWebPopupWithRefresh )
                     if ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_ReturnFromWebPopupWithRefresh ) == 0 )
                     { 
                        //:szWriteBuffer = "      window.opener.location.href=window.opener.location.href;"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      window.opener.location.href=window.opener.location.href;", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                        //:szWriteBuffer = "      window.opener.focus();"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      window.opener.focus();", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     } 

                     //:END
                     //:IF ( vDialog.Action.Type = zWAB_ReturnFromWebPopupNoRefresh OR vDialog.Action.Type = zWAB_ReturnFromWebPopupWithRefresh )
                     if ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_ReturnFromWebPopupNoRefresh ) == 0 || CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_ReturnFromWebPopupWithRefresh ) == 0 )
                     { 
                        //:szWriteBuffer = "      window.close();"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "      window.close();", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                        WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                     } 

                     //:END
                  } 


                  //:END
                  //:DropView( vDialogTemp )
                  DropView( vDialogTemp );
                  //:szWriteBuffer = "   }"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               } 

               //:END
            } 

            //:END
         } 

         //:END
         //:szWriteBuffer = "}"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
      } 

      RESULT = SetCursorNextEntity( vDialog, "Action", "" );
      //:END
   } 

   //:END

   //:// If the Window has a reusable side menu, add functions for each action from that menu.
   //:IF vDialog.ReusableSideWindow EXISTS
   lTempInteger_40 = CheckExistenceOfEntity( vDialog, "ReusableSideWindow" );
   if ( lTempInteger_40 == 0 )
   { 
      //:IF vDialog.ReusableSideDialog.ZKey = vDialog.Dialog.ZKey
      if ( CompareAttributeToAttribute( vDialog, "ReusableSideDialog", "ZKey", vDialog, "Dialog", "ZKey" ) == 0 )
      { 
         //:CreateViewFromView( vDialogTemp, vDialog )
         CreateViewFromView( &vDialogTemp, vDialog );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = vDialog.ReusableSideWindow.ZKey
         GetIntegerFromAttribute( &lTempInteger_41, vDialog, "ReusableSideWindow", "ZKey" );
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", lTempInteger_41, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //://Because the menu actions can be created on separate windows from the control
            //://actions, we need to make sure these actions are unique.  We will prefix a
            //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
            //:GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "sm" )
            GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "sm" );
         } 

         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI_ByName( vSubtask, vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, vDialog.ReusableSideDialog.Tag, 0 )
         GetStringFromAttribute( szTempString_27, zsizeof( szTempString_27 ), vDialog, "ReusableSideDialog", "Tag" );
         ActivateMetaOI_ByName( vSubtask, &vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, szTempString_27, 0 );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = vDialog.ReusableSideWindow.ZKey
         GetIntegerFromAttribute( &lTempInteger_42, vDialog, "ReusableSideWindow", "ZKey" );
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", lTempInteger_42, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //://Because the menu actions can be created on separate windows from the control
            //://actions, we need to make sure these actions are unique.  We will prefix a
            //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
            //:GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "sm" )
            GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "sm" );
         } 

         //:END
         //:DropObjectInstance( vDialogTemp )
         DropObjectInstance( vDialogTemp );
      } 

      //:END
   } 

   //:END

   //:// If the Window has a reusable main menu, add functions for each action from that menu.
   //:ReusableDialogZKey = 0
   ReusableDialogZKey = 0;
   //:IF vDialog.ReusableMainWindow EXISTS
   lTempInteger_43 = CheckExistenceOfEntity( vDialog, "ReusableMainWindow" );
   if ( lTempInteger_43 == 0 )
   { 
      //:ReusableDialogZKey = vDialog.ReusableMainDialog.ZKey
      GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "ReusableMainDialog", "ZKey" );
      //:ReusableWindowZKey = vDialog.ReusableMainWindow.ZKey
      GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "ReusableMainWindow", "ZKey" );
      //:ELSE
   } 
   else
   { 
      //:IF vDialog.DefaultReusableMainWindow EXISTS
      lTempInteger_44 = CheckExistenceOfEntity( vDialog, "DefaultReusableMainWindow" );
      if ( lTempInteger_44 == 0 )
      { 
         //:ReusableDialogZKey = vDialog.DefaultReusableMainDialog.ZKey
         GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "DefaultReusableMainDialog", "ZKey" );
         //:ReusableWindowZKey = vDialog.DefaultReusableMainWindow.ZKey
         GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "DefaultReusableMainWindow", "ZKey" );
      } 

      //:END
   } 

   //:END
   //:IF ReusableDialogZKey != 0  // dks
   if ( ReusableDialogZKey != 0 )
   { 
      //:IF ReusableDialogZKey = vDialog.Dialog.ZKey
      if ( CompareAttributeToInteger( vDialog, "Dialog", "ZKey", ReusableDialogZKey ) == 0 )
      { 
         //:CreateViewFromView( vDialogTemp, vDialog )
         CreateViewFromView( &vDialogTemp, vDialog );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //://Because the menu actions can be created on separate windows from the control
            //://actions, we need to make sure these actions are unique.  We will prefix a
            //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
            //:GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "m" )
            GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "m" );
         } 

         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI_ByZKey( vSubtask, vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 )
         ActivateMetaOI_ByZKey( vSubtask, &vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //://Because the menu actions can be created on separate windows from the control
            //://actions, we need to make sure these actions are unique.  We will prefix a
            //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
            //:GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "m" )
            GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "m" );
         } 

         //:END
         //:DropObjectInstance( vDialogTemp )
         DropObjectInstance( vDialogTemp );
      } 

      //:END
   } 

   //:END

   //:// If the Window has a reusable menu for the actions only, add functions for each action from that menu.
   //:ReusableDialogZKey = 0
   ReusableDialogZKey = 0;
   //:IF vDialog.ReusableActionWindow EXISTS
   lTempInteger_45 = CheckExistenceOfEntity( vDialog, "ReusableActionWindow" );
   if ( lTempInteger_45 == 0 )
   { 
      //:ReusableDialogZKey = vDialog.ReusableActionDialog.ZKey
      GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "ReusableActionDialog", "ZKey" );
      //:ReusableWindowZKey = vDialog.ReusableActionWindow.ZKey
      GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "ReusableActionWindow", "ZKey" );
      //:ELSE
   } 
   else
   { 
      //:IF vDialog.DefaultReusableActionWindow EXISTS
      lTempInteger_46 = CheckExistenceOfEntity( vDialog, "DefaultReusableActionWindow" );
      if ( lTempInteger_46 == 0 )
      { 
         //:ReusableDialogZKey = vDialog.DefaultReusableActionDialog.ZKey
         GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "DefaultReusableActionDialog", "ZKey" );
         //:ReusableWindowZKey = vDialog.DefaultReusableActionWindow.ZKey
         GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "DefaultReusableActionWindow", "ZKey" );
      } 

      //:END
   } 

   //:END
   //:IF ReusableDialogZKey != 0  // dks
   if ( ReusableDialogZKey != 0 )
   { 
      //:IF ReusableDialogZKey = vDialog.Dialog.ZKey
      if ( CompareAttributeToInteger( vDialog, "Dialog", "ZKey", ReusableDialogZKey ) == 0 )
      { 
         //:CreateViewFromView( vDialogTemp, vDialog )
         CreateViewFromView( &vDialogTemp, vDialog );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:// Because the menu actions can be created on separate windows from the control
            //:// actions, we need to make sure these actions are unique.  We will prefix a
            //://"m" to the main menu actions and prefix a "sm" to the side menu actions and a
            //:// prefix of "ma" for menu actions where the menu will not be either the main menu
            //:// or a side menu.
            //:GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "ma" )
            GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "ma" );
         } 

         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI_ByZKey( vSubtask, vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 )
         ActivateMetaOI_ByZKey( vSubtask, &vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:// Because the menu actions can be created on separate windows from the control
            //:// actions, we need to make sure these actions are unique.  We will prefix a
            //://"m" to the main menu actions and prefix a "sm" to the side menu actions and a
            //:// prefix of "ma" for menu actions where the menu will not be either the main menu
            //:// or a side menu.
            //:GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "ma" )
            GenJSP_MenuFunctions( vDialogTemp, vDialogRoot, lFileJSP, szWriteBuffer, szFormName, "ma" );
         } 

         //:END
         //:DropObjectInstance( vDialogTemp )
         DropObjectInstance( vDialogTemp );
      } 

      //:END
   } 

   //:END

   //:// Generate Function routines for each button inside a Table (grid, etc.)
   //:// This function should not be JSP because this creates javascript not jsp
   //:GenJSP_ChildFunctions( vDialog, lFileJSP, szWriteBuffer, szFormName )
   GenJSP_ChildFunctions( vDialog, lFileJSP, szWriteBuffer, szFormName );

   //:// Comboboxes and listboxes need to do some mapping before the action
   //:// is called, so create separate javascript functions for actions that
   //:// are called from comboboxes or listboxes.
   //:// This function should not be JSP because this creates javascript not jsp
   //:GenJSP_OutputMapRecurs( vDialog, lFileJSP, szWriteBuffer, szFormName )
   GenJSP_OutputMapRecurs( vDialog, lFileJSP, szWriteBuffer, szFormName );

   //:// Do we want to put code here for grids that we are creating an output for
   //:// importing into excel.
   //:GenJSP_TableExport( vDialog, lFileJSP, szWriteBuffer, szNoPositioning )
   GenJSP_TableExport( vDialog, lFileJSP, szWriteBuffer, szNoPositioning );

   //:szWriteBuffer = "</script>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</script>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "</head>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</head>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:/*****************************  End of JavaScript Functions Section *****************************************************/


   //:/*****************************  Beginning of <body> Section  *****************************************************/

   //:// The following five line of codes were removed by DonC on 7/5/2007 after discussion with Doug that _AfterPageLoaded should
   //:// be executed even if lSort != 0.
   //://KJS 11/1/2007 - If there is an onLoad event on the body and we have table sorting on this page, the table
   //://sorting does not work in Firefox (seems to work in IE and Opera).  The solution is to not call _AfterPageLoaded on
   //://the body onLoad event but to create a call to addEvent(window 'load','_AfterPageLoaded)
   //://which does not interfere with the Standardista code (for table sorting) but still calls _AfterPageLoaded.
   //://In the Standardista code (sts.js) there is an addEvent that will call _AfterPageLoaded.
   //://Because of this, I think we do need the below code.  It uses the onLoad event if the web screen does not use table sorting
   //://but does not call onLoad if we are using table sorting and the _AfterPageLoaded gets called from addEvent in sts.js.
   //://I did see some documentation on the web that said the addEvent function doesn't work on IE5/Mac.  Might want to see if that's
   //://true. http://simonwillison.net/2004/May/26/addLoadEvent/
   //:IF lSort = 0
   if ( lSort == 0 )
   { 
      //:szWriteBuffer = "<body onLoad=^_AfterPageLoaded( )^ onSubmit=^_DisableFormElements( true )^ onBeforeUnload=^_BeforePageUnload( )^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<body onLoad=^_AfterPageLoaded( )^ onSubmit=^_DisableFormElements( true )^ onBeforeUnload=^_BeforePageUnload( )^>", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "<body onSubmit=^_DisableFormElements( true )^ onBeforeUnload=^_BeforePageUnload( )^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<body onSubmit=^_DisableFormElements( true )^ onBeforeUnload=^_BeforePageUnload( )^>", 1, 0, 10001 );
   } 

   //:END
   //://szWriteBuffer = "<body onLoad=^_AfterPageLoaded( )^ onSubmit=^_DisableFormElements( true )^ onBeforeUnload=^_BeforePageUnload( )^>"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// The user might want to have an include after the <body> so that they can create some divs that will be
   //:// displayed on the background of each page (ENC shows a skyline scene).  If so, create it here.
   //:// Do not create if the window is a popup or if there is no banner.
   //:IF vDialog.Dialog.WEB_PageBackgroundInclude != "" AND szWindowIsPopup = "" AND vDialogRoot.Window.WEB_NoBannerFlag = ""
   if ( CompareAttributeToString( vDialog, "Dialog", "WEB_PageBackgroundInclude", "" ) != 0 && ZeidonStringCompare( szWindowIsPopup, 1, 0, "", 1, 0, 2 ) == 0 && CompareAttributeToString( vDialogRoot, "Window", "WEB_NoBannerFlag", "" ) == 0 )
   { 
      //:szWriteBuffer = "<%@ include file=^" + vDialog.Dialog.WEB_PageBackgroundInclude + "^ %>"
      GetVariableFromAttribute( szTempString_28, 0, 'S', 255, vDialog, "Dialog", "WEB_PageBackgroundInclude", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_28, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ %>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:// KJS 10/30/08 - If a window has been created to be displayed on the user's dashboard, then this window needs to be specified
   //:// as a dashboard window because we have to do some special processing for this window (getting the blob from the dashboard entities).
   //:IF vDialogRoot.WndStyle.Tag = "Dashboard Window"
   if ( CompareAttributeToString( vDialogRoot, "WndStyle", "Tag", "Dashboard Window" ) == 0 )
   { 
      //:szWindowIsForDashboard = "Y"
      ZeidonStringCopy( szWindowIsForDashboard, 1, 0, "Y", 1, 0, 2 );
      //:ELSE
   } 
   else
   { 
      //:szWindowIsForDashboard = ""
      ZeidonStringCopy( szWindowIsForDashboard, 1, 0, "", 1, 0, 2 );
   } 

   //:END

   //:szShowBanner = "Y"
   ZeidonStringCopy( szShowBanner, 1, 0, "Y", 1, 0, 2 );
   //:szShowTopMenu = "Y"
   ZeidonStringCopy( szShowTopMenu, 1, 0, "Y", 1, 0, 2 );
   //:szShowSideMenu = "Y"
   ZeidonStringCopy( szShowSideMenu, 1, 0, "Y", 1, 0, 2 );

   //:IF szWindowIsPopup = "Y" AND szWindowIsForDashboard = "Y"
   if ( ZeidonStringCompare( szWindowIsPopup, 1, 0, "Y", 1, 0, 2 ) == 0 && ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szShowBanner = ""
      ZeidonStringCopy( szShowBanner, 1, 0, "", 1, 0, 2 );
      //:szShowTopMenu = ""
      ZeidonStringCopy( szShowTopMenu, 1, 0, "", 1, 0, 2 );
      //:szShowSideMenu = ""
      ZeidonStringCopy( szShowSideMenu, 1, 0, "", 1, 0, 2 );
      //:ELSE
   } 
   else
   { 
      //:IF vDialogRoot.Window.WEB_NoBannerFlag = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Window", "WEB_NoBannerFlag", "Y" ) == 0 )
      { 
         //:szShowBanner = ""
         ZeidonStringCopy( szShowBanner, 1, 0, "", 1, 0, 2 );
      } 

      //:END
      //:IF vDialog.Window.WEB_NoTopMenuFlag = "Y"
      if ( CompareAttributeToString( vDialog, "Window", "WEB_NoTopMenuFlag", "Y" ) == 0 )
      { 
         //:szShowTopMenu = ""
         ZeidonStringCopy( szShowTopMenu, 1, 0, "", 1, 0, 2 );
      } 

      //:END
   } 

   //:END

   //:// KJS 07/31/08 - I am adding a wrapper around the whole page, so that we can create styling in the
   //:// css.  Do not add this wrapper if the window is going to be a popup window or a window that will be part
   //:// of a dashboard.
   //://<!--This text is a comment-->
   //:IF szWindowIsPopup = "" AND szWindowIsForDashboard = ""
   if ( ZeidonStringCompare( szWindowIsPopup, 1, 0, "", 1, 0, 2 ) == 0 && ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "<div id=^wrapper^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^wrapper^>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:// Build the Banner before getting into Menu Options.
   //:// IF vDialogRoot.Window.WEB_NoBannerFlag = ""
   //:IF szShowBanner = "Y"
   if ( ZeidonStringCompare( szShowBanner, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:// strBannerName will always have a value, it might be a dynamic banner name set in vml code
      //:// or it might be an include file specified in the dialog or if neither of those, then
      //:// strBannerName has been set to "./include/banner.inc".
      //://szWriteBuffer = "<a href=^#^><img src=^images/<%=strBannerName%>^ width=^800^ height=^93^></a>"
      //:szWriteBuffer = "<jsp:include page='<%=strBannerName %>' />"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<jsp:include page='<%=strBannerName %>' />", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:szSideMenuExists = "N"
   ZeidonStringCopy( szSideMenuExists, 1, 0, "N", 1, 0, 2 );

   //:// Generate Main Navigation Bar
   //:ReusableDialogZKey = 0
   ReusableDialogZKey = 0;
   //:IF vDialog.ReusableMainWindow EXISTS
   lTempInteger_47 = CheckExistenceOfEntity( vDialog, "ReusableMainWindow" );
   if ( lTempInteger_47 == 0 )
   { 
      //:ReusableDialogZKey = vDialog.ReusableMainDialog.ZKey
      GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "ReusableMainDialog", "ZKey" );
      //:ReusableWindowZKey = vDialog.ReusableMainWindow.ZKey
      GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "ReusableMainWindow", "ZKey" );
      //:ELSE
   } 
   else
   { 
      //:IF vDialog.DefaultReusableMainWindow EXISTS
      lTempInteger_48 = CheckExistenceOfEntity( vDialog, "DefaultReusableMainWindow" );
      if ( lTempInteger_48 == 0 )
      { 
         //:ReusableDialogZKey = vDialog.DefaultReusableMainDialog.ZKey
         GetIntegerFromAttribute( &ReusableDialogZKey, vDialog, "DefaultReusableMainDialog", "ZKey" );
         //:ReusableWindowZKey = vDialog.DefaultReusableMainWindow.ZKey
         GetIntegerFromAttribute( &ReusableWindowZKey, vDialog, "DefaultReusableMainWindow", "ZKey" );
      } 

      //:END
   } 

   //:END

   //:// IF ( ReusableDialogZKey != 0 AND vDialog.Window.WEB_NoTopMenuFlag != "Y" )  // dks
   //:IF ( ReusableDialogZKey != 0 AND szShowTopMenu = "Y" )  // dks
   if ( ReusableDialogZKey != 0 && ZeidonStringCompare( szShowTopMenu, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:IF ReusableDialogZKey = vDialog.Dialog.ZKey
      if ( CompareAttributeToInteger( vDialog, "Dialog", "ZKey", ReusableDialogZKey ) == 0 )
      { 
         //:CreateViewFromView( vDialogTemp, vDialog )
         CreateViewFromView( &vDialogTemp, vDialog );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:BuildMainNavSection( vDialog, vDialogTemp, lFileJSP )
            BuildMainNavSection( vDialog, vDialogTemp, lFileJSP );
         } 

         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI_ByZKey( vSubtask, vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 )
         ActivateMetaOI_ByZKey( vSubtask, &vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, ReusableDialogZKey, 0 );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = ReusableWindowZKey
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", ReusableWindowZKey, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:BuildMainNavSection( vDialog, vDialogTemp, lFileJSP )
            BuildMainNavSection( vDialog, vDialogTemp, lFileJSP );
         } 

         //:END
         //:DropObjectInstance( vDialogTemp )
         DropObjectInstance( vDialogTemp );
      } 

      //:END
   } 

   //:END

   //:// KJS 07/31/08 - Before we build the main content items (side navigation if it exists and the page contents) we
   //:// are going to create another div.  Not sure this is necessary but I'm thinking it might be helpful (then the
   //:// footer can be after this).
   //:IF szWindowIsPopup = "" AND szWindowIsForDashboard = ""
   if ( ZeidonStringCompare( szWindowIsPopup, 1, 0, "", 1, 0, 2 ) == 0 && ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "<div id=^maincontent^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^maincontent^>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:// Left navigation bar from Menu.
   //:// If the Window has a Reusable menu, use it. Otherwise try to use the Main Menu for the Window.
   //:// If neither exists, there will be no left navigation bar.
   //:// IF vDialog.ReusableSideWindow EXISTS
   //:IF vDialog.ReusableSideWindow EXISTS AND szShowSideMenu = "Y"
   lTempInteger_49 = CheckExistenceOfEntity( vDialog, "ReusableSideWindow" );
   if ( lTempInteger_49 == 0 && ZeidonStringCompare( szShowSideMenu, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 

      //:IF vDialog.DfltMenu EXISTS AND vDialog.ReusableSideWindow.ZKey != vDialog.Window.ZKey
      lTempInteger_50 = CheckExistenceOfEntity( vDialog, "DfltMenu" );
      if ( lTempInteger_50 == 0 && CompareAttributeToAttribute( vDialog, "ReusableSideWindow", "ZKey", vDialog, "Window", "ZKey" ) != 0 )
      { 
         //:vDfltMenu = vDialog
         vDfltMenu = vDialog;
         //:ELSE
      } 
      else
      { 
         //:vDfltMenu = 0
         vDfltMenu = 0;
      } 

      //:END

      //:IF vDialog.ReusableSideDialog.ZKey = vDialog.Dialog.ZKey
      if ( CompareAttributeToAttribute( vDialog, "ReusableSideDialog", "ZKey", vDialog, "Dialog", "ZKey" ) == 0 )
      { 
         //:CreateViewFromView( vDialogTemp, vDialog )
         CreateViewFromView( &vDialogTemp, vDialog );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = vDialog.ReusableSideWindow.ZKey
         GetIntegerFromAttribute( &lTempInteger_51, vDialog, "ReusableSideWindow", "ZKey" );
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", lTempInteger_51, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:BuildSideNavSection( vDialog, vDialogTemp, lFileJSP, "Y", vDfltMenu )  // dks ... want Reusable + Default
            BuildSideNavSection( vDialog, vDialogTemp, lFileJSP, "Y", vDfltMenu );
            //:szSideMenuExists = "Y"
            ZeidonStringCopy( szSideMenuExists, 1, 0, "Y", 1, 0, 2 );
         } 

         //:END
         //:DropView( vDialogTemp )
         DropView( vDialogTemp );
         //:ELSE
      } 
      else
      { 
         //:ActivateMetaOI_ByName( vSubtask, vDialogTemp, 0, zREFER_DIALOG_META,  zSINGLE, vDialog.ReusableSideDialog.Tag, 0 )
         GetStringFromAttribute( szTempString_29, zsizeof( szTempString_29 ), vDialog, "ReusableSideDialog", "Tag" );
         ActivateMetaOI_ByName( vSubtask, &vDialogTemp, 0, zREFER_DIALOG_META, zSINGLE, szTempString_29, 0 );
         //:SET CURSOR FIRST vDialogTemp.Window WHERE vDialogTemp.Window.ZKey = vDialog.ReusableSideWindow.ZKey
         GetIntegerFromAttribute( &lTempInteger_52, vDialog, "ReusableSideWindow", "ZKey" );
         RESULT = SetCursorFirstEntityByInteger( vDialogTemp, "Window", "ZKey", lTempInteger_52, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:BuildSideNavSection( vDialog, vDialogTemp, lFileJSP, "Y", vDfltMenu )  // dks ... want Reusable + Default
            BuildSideNavSection( vDialog, vDialogTemp, lFileJSP, "Y", vDfltMenu );
            //:szSideMenuExists = "Y"
            ZeidonStringCopy( szSideMenuExists, 1, 0, "Y", 1, 0, 2 );
         } 

         //:END
         //:DropObjectInstance( vDialogTemp )
         DropObjectInstance( vDialogTemp );
      } 

      //:END

      //:ELSE
   } 
   else
   { 
      //:// IF vDialogRoot.DfltMenu EXISTS AND
      //:IF vDialogRoot.DfltMenu EXISTS AND szShowSideMenu = "Y" AND
      lTempInteger_53 = CheckExistenceOfEntity( vDialogRoot, "DfltMenu" );
      //:   (vDialog.ReusableMainDialog DOES NOT EXIST OR  // don't put out side menu if side == top
      lTempInteger_54 = CheckExistenceOfEntity( vDialog, "ReusableMainDialog" );
      //:    ReusableDialogZKey != vDialog.ReusableMainDialog.ZKey OR
      //:    ReusableWindowZKey != vDialog.ReusableMainWindow.ZKey)
      if ( lTempInteger_53 == 0 && ZeidonStringCompare( szShowSideMenu, 1, 0, "Y", 1, 0, 2 ) == 0 && ( lTempInteger_54 != 0 || CompareAttributeToInteger( vDialog, "ReusableMainDialog", "ZKey", ReusableDialogZKey ) != 0 ||
           CompareAttributeToInteger( vDialog, "ReusableMainWindow", "ZKey", ReusableWindowZKey ) != 0 ) )
      { 

         //:BuildSideNavSection( vDialog, vDialogRoot, lFileJSP, "N", 0 )
         BuildSideNavSection( vDialog, vDialogRoot, lFileJSP, "N", 0 );
         //:szSideMenuExists = "Y"
         ZeidonStringCopy( szSideMenuExists, 1, 0, "Y", 1, 0, 2 );
      } 

      //:END
   } 

   //:END

   //:szCSS_Class = vDialog.Window.CSS_Class
   GetVariableFromAttribute( szCSS_Class, 0, 'S', 51, vDialog, "Window", "CSS_Class", "", 0 );
   //:IF szCSS_Class = ""
   if ( ZeidonStringCompare( szCSS_Class, 1, 0, "", 1, 0, 51 ) == 0 )
   { 
      //:szCSS_Class = vDialog.Dialog.CSS_Class
      GetVariableFromAttribute( szCSS_Class, 0, 'S', 51, vDialog, "Dialog", "CSS_Class", "", 0 );
   } 

   //:END

   //:IF szCSS_Class != ""
   if ( ZeidonStringCompare( szCSS_Class, 1, 0, "", 1, 0, 51 ) != 0 )
   { 
      //:szDivContentClass = szCSS_Class
      ZeidonStringCopy( szDivContentClass, 1, 0, szCSS_Class, 1, 0, 51 );
      //://szWriteBuffer = "<div class=^" + szCSS_Class + "^>"
      //:szWriteBuffer = "<div id=^" + szCSS_Class + "^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCSS_Class, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:ELSE
   } 
   else
   { 
      //:// KJS 10/30/08 - Do I want to put a div with id for dashboard window and
      //:// for popup window???
      //:IF  szWindowIsPopup = "Y"
      if ( ZeidonStringCompare( szWindowIsPopup, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 
         //:// If no class was given, create a default div with the id of content.
         //:szWriteBuffer = "<div id=^contentpopup^>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^contentpopup^>", 1, 0, 10001 );
         //:WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 );
         //:szDivContentClass = "contentpopup"
         ZeidonStringCopy( szDivContentClass, 1, 0, "contentpopup", 1, 0, 51 );
         //:ELSE
      } 
      else
      { 
         //:IF  szWindowIsForDashboard = "Y"
         if ( ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:// If no class was given, create a default div with the id of content.
            //:szWriteBuffer = "<div id=^contentdashboard^>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^contentdashboard^>", 1, 0, 10001 );
            //:WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 )
            WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 );
            //:szDivContentClass = "contentdashboard"
            ZeidonStringCopy( szDivContentClass, 1, 0, "contentdashboard", 1, 0, 51 );
            //:ELSE
         } 
         else
         { 
            //:IF szSideMenuExists = "Y"
            if ( ZeidonStringCompare( szSideMenuExists, 1, 0, "Y", 1, 0, 2 ) == 0 )
            { 
               //:// If no class was given, create a default div with the id of content.
               //:szWriteBuffer = "<div id=^content^>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^content^>", 1, 0, 10001 );
               //:WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 );
               //:szDivContentClass = "content"
               ZeidonStringCopy( szDivContentClass, 1, 0, "content", 1, 0, 51 );
               //:ELSE
            } 
            else
            { 
               //:// If no class was given, and there is no side menu,
               //:// create a default div with the id of contentnosidemenu.
               //:szWriteBuffer = "<div id=^contentnosidemenu^>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^contentnosidemenu^>", 1, 0, 10001 );
               //:WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 );
               //:szDivContentClass = "contentnosidemenu"
               ZeidonStringCopy( szDivContentClass, 1, 0, "contentnosidemenu", 1, 0, 51 );
            } 

            //:END
         } 

         //:END
      } 

      //:END
   } 

   //:END

   //:// KJS 03/04/10 - We are going to try adding an include file for system maintenance.  That way if we
   //:// want to kick people out of MyENC, we will put code in systemmaintenance.inc that will have a flashing
   //:// message that will show on each page.
   //://<!--System Maintenance-->

   //://<div> <%@include file="./include/systemmaintenance.inc" %> </div>

   //://<!--System Maintenance-->

   //:szWriteBuffer = "<!--System Maintenance-->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<!--System Maintenance-->", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<%@ include file=^./include/systemmaintenance.inc^ %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^./include/systemmaintenance.inc^ %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<!-- END System Maintenance-->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- END System Maintenance-->", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialogRoot, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// Generate FORM
   //://CreateSizeString( vDialog, szSizeF )
   //:PIX_PER_DU( vDialog, DLUnits )
   PIX_PER_DU( vDialog, &DLUnits );

   //:// For Popups, we will use the Width from the Window. Otherwise we won't.
   //:// The way we will determine if this Window is for a Popup is to see if any Action is Return from Popup.
   //:// SET CURSOR FIRST vDialog.Action WHERE ( vDialog.Action.Type = zWAB_StartModalWebPopup OR vDialog.Action.Type = zWAB_StartModelessWebPopup )
   //:SET CURSOR FIRST vDialog.Action WHERE ( vDialog.Action.Type = 78 OR vDialog.Action.Type = 79 )
   RESULT = SetCursorFirstEntity( vDialog, "Action", "" );
   if ( RESULT > zCURSOR_UNCHANGED )
   { 
      while ( RESULT > zCURSOR_UNCHANGED && ( ( CompareAttributeToInteger( vDialog, "Action", "Type", 78 ) != 0 && CompareAttributeToInteger( vDialog, "Action", "Type", 79 ) != 0 ) ) )
      { 
         RESULT = SetCursorNextEntity( vDialog, "Action", "" );
      } 

   } 

   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:lSize = zLOUSHORT( vDialog.Window.SZDLG_X )
      GetIntegerFromAttribute( &lTempInteger_55, vDialog, "Window", "SZDLG_X" );
      lSize = zLOUSHORT( lTempInteger_55 );
      //:lSize = lSize * DLUnits
      lSize = lSize * DLUnits;
      //:szWidth = lSize
      ZeidonStringConvertFromNumber( szWidth, 1, 0, 10, lSize, (ZDecimal) 0.0, "I" );
      //:ELSE
   } 
   else
   { 
      //:szWidth = "750"
      ZeidonStringCopy( szWidth, 1, 0, "750", 1, 0, 11 );
   } 

   //:END
   //:lSize = zLOUSHORT( vDialog.Window.SZDLG_Y )
   GetIntegerFromAttribute( &lTempInteger_56, vDialog, "Window", "SZDLG_Y" );
   lSize = zLOUSHORT( lTempInteger_56 );
   //:lSize = lSize * DLUnits
   lSize = lSize * DLUnits;
   //:szHeight = lSize
   ZeidonStringConvertFromNumber( szHeight, 1, 0, 10, lSize, (ZDecimal) 0.0, "I" );
   //:szStyle = "width:" + szWidth + "px;height:" + szHeight + "px;"
   ZeidonStringCopy( szStyle, 1, 0, "width:", 1, 0, 1025 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 1025 );
   ZeidonStringConcat( szStyle, 1, 0, "px;height:", 1, 0, 1025 );
   ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 1025 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 1025 );

   //:szWriteBuffer = "<form name=^" + szFormName + "^ id=^" + szFormName + "^ method=^post^>"  // no height on form
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<form name=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ method=^post^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:// Eliminating <input termination.
   //:szWriteBuffer = "   <input name=^zAction^ id=^zAction^ type=^hidden^ value=^NOVALUE^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zAction^ id=^zAction^ type=^hidden^ value=^NOVALUE^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zTableRowSelect^ id=^zTableRowSelect^ type=^hidden^ value=^NOVALUE^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zTableRowSelect^ id=^zTableRowSelect^ type=^hidden^ value=^NOVALUE^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zDisable^ id=^zDisable^ type=^hidden^ value=^NOVALUE^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zDisable^ id=^zDisable^ type=^hidden^ value=^NOVALUE^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   strSessionId = session.getId( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strSessionId = session.getId( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// Add each view definition.
   //:FOR EACH vDialog.ViewObjRef //WHERE vDialog.ViewObjRef.wWindowUseFlag = "Y"
   RESULT = SetCursorFirstEntity( vDialog, "ViewObjRef", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:szWriteBuffer = "   zeidon.zView " + vDialog.ViewObjRef.Name + " = new zeidon.zView( strSessionId );"
      GetVariableFromAttribute( szTempString_30, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   zeidon.zView ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_30, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = new zeidon.zView( strSessionId );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      RESULT = SetCursorNextEntity( vDialog, "ViewObjRef", "" );
   } 

   //:END

   //://szWriteBuffer = "   zeidon.zView vKZXMLPGO = new zeidon.zView( strSessionId );"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   String strRadioGroupValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strRadioGroupValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strComboCurrentValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strComboCurrentValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strAutoComboBoxExternalValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strAutoComboBoxExternalValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strComboSelectedValue = ^0^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strComboSelectedValue = ^0^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strErrorColor = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strErrorColor = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strErrorMapValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strErrorMapValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strTextDisplayValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strTextDisplayValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strTextURL_Value = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strTextURL_Value = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strSolicitSave = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strSolicitSave = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strTblOutput = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strTblOutput = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int    ComboCount = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    ComboCount = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int    iTableRowCnt = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    iTableRowCnt = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:IF  szWindowIsForDashboard = "Y"
   if ( ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "   strViewName = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   strViewName = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   iFrameCount = 0;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   iFrameCount = 0;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END
   //:szWriteBuffer = "   int    nRC2 = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int    nRC2 = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   nRC = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   nRC2 = vKZXMLPGO.GetView( strSessionId, ^KZXMLPGO^, vAppSubtask );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC2 = vKZXMLPGO.GetView( strSessionId, ^KZXMLPGO^, vAppSubtask );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( nRC2 <= 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC2 <= 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      vKZXMLPGO.InitWebSessionObject( strSessionId, vAppSubtask, ^TestUserID^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      vKZXMLPGO.InitWebSessionObject( strSessionId, vAppSubtask, ^TestUserID^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      vKZXMLPGO.SetName( strSessionId, ^KZXMLPGO^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      vKZXMLPGO.SetName( strSessionId, ^KZXMLPGO^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //://KJS Trace
   //:IF (lTrace = 1)
   if ( lTrace == 1 )
   { 
      //:szWriteBuffer = "   vAppSubtask.TraceLine( ^InitWebPage: ^, ^" + vDialog.Dialog.Tag + vDialog.Window.Tag + "^ );"
      GetVariableFromAttribute( szTempString_31, 0, 'S', 33, vDialog, "Dialog", "Tag", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine( ^InitWebPage: ^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_31, 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_32, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_32, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:szWriteBuffer = "   nRC2 = vKZXMLPGO.InitWebPage( strSessionId, ^" + vDialog.Dialog.Tag + "^, ^" +
   //:                                                  vDialog.Window.Tag + "^ );"
   GetVariableFromAttribute( szTempString_33, 0, 'S', 33, vDialog, "Dialog", "Tag", "", 0 );
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC2 = vKZXMLPGO.InitWebPage( strSessionId, ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_33, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
   GetVariableFromAttribute( szTempString_34, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_34, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:IF  szWindowIsForDashboard = "Y"
   if ( ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:// HOW AM I GOING TO KNOW TO USE mUser????!!! Right now this is vDialog.CtrlMapView.Name but that is not correct.
      //://szViewName = vDialog.CtrlMapView.Name
      //:szViewName = "mUser"
      ZeidonStringCopy( szViewName, 1, 0, "mUser", 1, 0, 33 );
      //:szWriteBuffer = "   // Position on the correct Frame by looping through the dashboard object "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Position on the correct Frame by looping through the dashboard object ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   iFrameCount = vKZXMLPGO.GetInteger( strSessionId, ^Session^, ^DashboardFrameCount^ ); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   iFrameCount = vKZXMLPGO.GetInteger( strSessionId, ^Session^, ^DashboardFrameCount^ ); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( iFrameCount == 0 ) "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( iFrameCount == 0 ) ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      iFrameCount = 1; "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      iFrameCount = 1; ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   vAppSubtask.TraceLine(^**** FrameCount *** ^, iFrameCount); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine(^**** FrameCount *** ^, iFrameCount); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   nRC2 = " + szViewName + ".GetView( strSessionId, ^" + szViewName + "^, vAppSubtask ); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC2 = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask ); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   nRC = " + szViewName + ".SetCursorFirst( strSessionId, ^DashboardFrameUser^, ^wFrameNbr^, iFrameCount, ^^ ); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorFirst( strSessionId, ^DashboardFrameUser^, ^wFrameNbr^, iFrameCount, ^^ ); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   vAppSubtask.TraceLine(^**** nRC after SetCursorFirstByInteger *** ^, nRC); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine(^**** nRC after SetCursorFirstByInteger *** ^, nRC); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   strViewName = " + szViewName + ".GetStringFromAttributeByContext( strSessionId, ^DashboardFrame^, ^Name^, ^^, 254 ); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   strViewName = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^DashboardFrame^, ^Name^, ^^, 254 ); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   vAppSubtask.TraceLine(^**** ReportName *** ^, strViewName); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine(^**** ReportName *** ^, strViewName); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   nRC = " + szViewName + ".CheckExistenceOfEntity( strSessionId, ^PresentationObjectInstance^ ); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^PresentationObjectInstance^ ); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( nRC >= 0 ) "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC >= 0 ) ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      nRC = mDashboard.SetOIFromBlob(strSessionId, ^^, vAppSubtask, " + szViewName + ", ^PresentationObjectInstance^, ^ObjectInstanceBlob^,0); //zIGNORE_ERRORS "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = mDashboard.SetOIFromBlob(strSessionId, ^^, vAppSubtask, ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ", ^PresentationObjectInstance^, ^ObjectInstanceBlob^,0); //zIGNORE_ERRORS ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      strViewName = " + szViewName + ".GetStringFromAttributeByContext( strSessionId, ^DashboardFrame^, ^ObjectInstanceName^, ^^, 254 ); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strViewName = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szViewName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^DashboardFrame^, ^ObjectInstanceName^, ^^, 254 ); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      mDashboard.SetName( strSessionId, strViewName ); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      mDashboard.SetName( strSessionId, strViewName ); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   iFrameCount = iFrameCount + 1; "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   iFrameCount = iFrameCount + 1; ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   vKZXMLPGO.SetAttribute( strSessionId, ^Session^, ^DashboardFrameCount^, iFrameCount ); "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vKZXMLPGO.SetAttribute( strSessionId, ^Session^, ^DashboardFrameCount^, iFrameCount ); ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 


   //:END

   //:// Build call to FindErrorFields and process any errors.
   //:szWriteBuffer = "   // FindErrorFields Processing"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // FindErrorFields Processing", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   strError = vAppSubtask.FindErrorFields( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strError = vAppSubtask.FindErrorFields( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// If the download file is too large, we have an error for that (that can't easily be put in the MSGQ so I am
   //:// creating another option for that.
   //:IF szUploadFile = "Y"
   if ( ZeidonStringCompare( szUploadFile, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "   // If the download file is too large, we have an error."
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   // If the download file is too large, we have an error.", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( strError == null || strError.length() == 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( strError == null | strError.length() == 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      strError = (String) session.getAttribute( ^FileUploadError^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strError = (String) session.getAttribute( ^FileUploadError^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      session.setAttribute( ^FileUploadError^, ^^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      session.setAttribute( ^FileUploadError^, ^^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( strError == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strError == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         strError = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strError = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END
   //://KJS Trace
   //://szWriteBuffer = "   vAppSubtask.TraceLine( ^Post FindErrorFields Error1: ^, strError );"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )

   //:szWriteBuffer = "   nPos = strError.indexOf( ^\t^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   nPos = strError.indexOf( ^\\t^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //://KJS Trace
   //://szWriteBuffer = "   vAppSubtask.TraceLine( ^Post FindErrorFields Pos1: ^, nPos );"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )

   //:szWriteBuffer = "   if ( nPos > 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nPos > 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      strErrorFlag = strError.substring( 0, 1 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strErrorFlag = strError.substring( 0, 1 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      strError = strError.substring( nPos + 1 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strError = strError.substring( nPos + 1 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //://szWriteBuffer = "   vAppSubtask.TraceLine( ^Post FindErrorFields ErrorFlag: ^, strErrorFlag );"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   if ( nPos >= 0 && strErrorFlag.equals( ^Y^ ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nPos >= 0 && strErrorFlag.equals( ^Y^ ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      nPos = strError.indexOf( ^\t\t^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nPos = strError.indexOf( ^\\t\\t^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( nPos >= 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nPos >= 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         strErrorTitle = strError.substring( 0, nPos );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorTitle = strError.substring( 0, nPos );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         strErrorMsg = strError.substring( nPos + 2 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMsg = strError.substring( nPos + 2 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //://KJS Trace
   //:IF (lTrace = 1)
   if ( lTrace == 1 )
   { 
      //:szWriteBuffer = "         vAppSubtask.TraceLine( ^After FindErrorFields ErrorFlag: ^, strErrorFlag );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.TraceLine( ^After FindErrorFields ErrorFlag: ^, strErrorFlag );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         vAppSubtask.TraceLine( ^After FindErrorFields ErrorTitle: ^, strErrorTitle );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.TraceLine( ^After FindErrorFields ErrorTitle: ^, strErrorTitle );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         vAppSubtask.TraceLine( ^After FindErrorFields ErrorMsg: ^, strErrorMsg );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.TraceLine( ^After FindErrorFields ErrorMsg: ^, strErrorMsg );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   strSolicitSave = vKZXMLPGO.GetString( strSessionId, ^Session^, ^SolicitSaveFlag^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strSolicitSave = vKZXMLPGO.GetString( strSessionId, ^Session^, ^SolicitSaveFlag^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// FindOpenFile processing.
   //:szWindowTag = vDialog.Window.Tag
   GetVariableFromAttribute( szWindowTag, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
   //:szWriteBuffer = "   strFocusCtrl = vAppSubtask.GetFocusCtrl( strSessionId, ^" +
   //:                szDialogTag + "^, ^" + szWindowTag + "^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strFocusCtrl = vAppSubtask.GetFocusCtrl( strSessionId, ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szDialogTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szWindowTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   strOpenFile = vAppSubtask.FindOpenFile( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strOpenFile = vAppSubtask.FindOpenFile( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //://KJS Trace
   //:IF (lTrace = 1)
   if ( lTrace == 1 )
   { 
      //:szWriteBuffer = "   vAppSubtask.TraceLine( ^After Get OpenFile: ^, strOpenFile );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine( ^After Get OpenFile: ^, strOpenFile );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:szWriteBuffer = "   strDateFormat = vAppSubtask.GetDateDefaultContextFormat( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strDateFormat = vAppSubtask.GetDateDefaultContextFormat( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:/*
   //:IF szKeyRole = "Y"
   //:   szWriteBuffer = "   nRC2 = wWebXA.GetView( strSessionId, ^wWebXfer^, vAppSubtask );"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "   if ( nRC2 > 0 )"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "   {"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "      nRC2 = wWebXA.CheckExistenceOfEntity( strSessionId, ^Root^ );"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "      if ( nRC2 >= 0 )"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "      {"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "         strKeyRole = wWebXA.GetStringFromAttributeByContext( strSessionId, ^Root^, ^KeyRole^, ^KeyRole^, 254 );"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "         task.log().debug( ^Root.KeyRole: ^ + strKeyRole );"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "      }"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:   szWriteBuffer = "   }"
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:END
   //:*/

   //://KJS Trace
   //://szWriteBuffer = "   vAppSubtask.TraceLine( ^After Get DateFormat: ^, strDateFormat );"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )

   //:szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// Eliminating <input termination.
   //:szWriteBuffer = "   <input name=^zFocusCtrl^ id=^zFocusCtrl^ type=^hidden^ value=^<%=strFocusCtrl%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zFocusCtrl^ id=^zFocusCtrl^ type=^hidden^ value=^<%=strFocusCtrl%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zOpenFile^ id=^zOpenFile^ type=^hidden^ value=^<%=strOpenFile%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zOpenFile^ id=^zOpenFile^ type=^hidden^ value=^<%=strOpenFile%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zDateFormat^ id=^zDateFormat^ type=^hidden^ value=^<%=strDateFormat%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zDateFormat^ id=^zDateFormat^ type=^hidden^ value=^<%=strDateFormat%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:IF szKeyRole = "Y"
   if ( ZeidonStringCompare( szKeyRole, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "   <input name=^zLoginName^ id=^zLoginName^ type=^hidden^ value=^<%=strLoginName%>^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zLoginName^ id=^zLoginName^ type=^hidden^ value=^<%=strLoginName%>^>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   <input name=^zKeyRole^ id=^zKeyRole^ type=^hidden^ value=^<%=strKeyRole%>^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zKeyRole^ id=^zKeyRole^ type=^hidden^ value=^<%=strKeyRole%>^>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END
   //:szWriteBuffer = "   <input name=^zOpenPopupWindow^ id=^zOpenPopupWindow^ type=^hidden^ value=^<%=strOpenPopupWindow%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zOpenPopupWindow^ id=^zOpenPopupWindow^ type=^hidden^ value=^<%=strOpenPopupWindow%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zPopupWindowSZX^ id=^zPopupWindowSZX^ type=^hidden^ value=^<%=strPopupWindowSZX%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zPopupWindowSZX^ id=^zPopupWindowSZX^ type=^hidden^ value=^<%=strPopupWindowSZX%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zPopupWindowSZY^ id=^zPopupWindowSZY^ type=^hidden^ value=^<%=strPopupWindowSZY%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zPopupWindowSZY^ id=^zPopupWindowSZY^ type=^hidden^ value=^<%=strPopupWindowSZY%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zErrorFlag^ id=^zErrorFlag^ type=^hidden^ value=^<%=strErrorFlag%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zErrorFlag^ id=^zErrorFlag^ type=^hidden^ value=^<%=strErrorFlag%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// KJS 09/09/2009 - We are using Timeout.inc (which says this is for Jeff) but if there is a value in
   //:// WEB_Timeout for the dialog or window, we want to use that.
   //:IF vDialog.Window.WEB_Timeout != ""
   if ( CompareAttributeToString( vDialog, "Window", "WEB_Timeout", "" ) != 0 )
   { 
      //:szWriteBuffer = "   <input name=^zTimeout^ id=^zTimeout^ type=^hidden^ value=^"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zTimeout^ id=^zTimeout^ type=^hidden^ value=^", 1, 0, 10001 );
      //:szWriteBuffer = szWriteBuffer + vDialog.Window.WEB_Timeout
      GetVariableFromAttribute( &szTempString_35, 0, 'S', 11, vDialog, "Window", "WEB_Timeout", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_35, 1, 0, 10001 );
      //:szWriteBuffer = szWriteBuffer + "^>"
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^>", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:IF vDialog.Dialog.WEB_Timeout != ""
      if ( CompareAttributeToString( vDialog, "Dialog", "WEB_Timeout", "" ) != 0 )
      { 
         //:szWriteBuffer = "   <input name=^zTimeout^ id=^zTimeout^ type=^hidden^ value=^"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zTimeout^ id=^zTimeout^ type=^hidden^ value=^", 1, 0, 10001 );
         //:szWriteBuffer = szWriteBuffer + vDialog.Dialog.WEB_Timeout
         GetVariableFromAttribute( &szTempString_36, 0, 'S', 11, vDialog, "Dialog", "WEB_Timeout", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_36, 1, 0, 10001 );
         //:szWriteBuffer = szWriteBuffer + "^>"
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "   <input name=^zTimeout^ id=^zTimeout^ type=^hidden^ value=^<%=nTimeout%>^>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zTimeout^ id=^zTimeout^ type=^hidden^ value=^<%=nTimeout%>^>", 1, 0, 10001 );
      } 

      //:END
   } 

   //:END
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zSolicitSave^ id=^zSolicitSave^ type=^hidden^ value=^<%=strSolicitSave%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zSolicitSave^ id=^zSolicitSave^ type=^hidden^ value=^<%=strSolicitSave%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// Generate HTML Control output.
   //:OrderEntityForView( vDialog, "Control", "PSDLG_Y A PSDLG_X A" )
   OrderEntityForView( vDialog, "Control", "PSDLG_Y A PSDLG_X A" );
   //:vGroupParent = 0
   vGroupParent = 0;

   //:// KJS 07/23/08 - Check if this dialog window will be built with all relative positioning or with absolute positioning
   //:IF  vDialog.Dialog.WEB_RelativePositionFlag = "Y" OR vDialog.Window.WEB_RelativePositionFlag = "Y"
   if ( CompareAttributeToString( vDialog, "Dialog", "WEB_RelativePositionFlag", "Y" ) == 0 || CompareAttributeToString( vDialog, "Window", "WEB_RelativePositionFlag", "Y" ) == 0 )
   { 
      //:szNoPositioning = "Y"
      ZeidonStringCopy( szNoPositioning, 1, 0, "Y", 1, 0, 2 );
      //:ELSE
   } 
   else
   { 
      //:szNoPositioning = ""
      ZeidonStringCopy( szNoPositioning, 1, 0, "", 1, 0, 2 );
   } 

   //:END

   //:// KJS 02/19/09 - Added WEB_AbsolutePositionFlag because I would like to use absolute positioning on my popup pages but the rest
   //:// I want to use relative positioning.  Since I think from now on we will probably only want to use relative positioning for most
   //:// pages, I think it will be easier to have this flag.
   //:IF  vDialog.Window.WEB_AbsolutePositionFlag = "Y"
   if ( CompareAttributeToString( vDialog, "Window", "WEB_AbsolutePositionFlag", "Y" ) == 0 )
   { 
      //:szNoPositioning = ""
      ZeidonStringCopy( szNoPositioning, 1, 0, "", 1, 0, 2 );
   } 

   //:END

   //:GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFileJSP, szWriteBuffer, szIndentNext, lTableRowCnt, szNoPositioning, 0, 0 )
   GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFileJSP, szWriteBuffer, szIndentNext, lTableRowCnt, szNoPositioning, 0, 0 );

   //:// Complete the JSP file.
   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( strErrorFlag.equals( ^D^ ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( strErrorFlag.equals( ^D^ ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:IF (lTrace = 1)
   if ( lTrace == 1 )
   { 
      //:szWriteBuffer = "      vAppSubtask.TraceLine( ^Post FindErrorFields Error: ^, strError );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask.TraceLine( ^Post FindErrorFields Error: ^, strError );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:szWriteBuffer = "      nPos = strError.indexOf( ^\t^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nPos = strError.indexOf( ^\\t^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( nPos >= 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nPos >= 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         strErrorTitle = strError.substring( 0, nPos );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorTitle = strError.substring( 0, nPos );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         nPos = strError.indexOf( ^\t\t^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         nPos = strError.indexOf( ^\\t\\t^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         strErrorMsg = strError.substring( nPos + 2 );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMsg = strError.substring( nPos + 2 );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   <input name=^zError^ id=^zError^ type=^hidden^ value=^<%=strErrorMsg%>^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zError^ id=^zError^ type=^hidden^ value=^<%=strErrorMsg%>^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:IF szWebDebugView != ""
   if ( ZeidonStringCompare( szWebDebugView, 1, 0, "", 1, 0, 33 ) != 0 )
   { 
      //:szWriteBuffer = "   <div align=^clear:both;center;^><table style=^width:750px;background-color:black;color:white;border:none;font-size:8px;^><tr style=^background-color:blue;color:white;border:none;^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <div align=^clear:both;center;^><table style=^width:750px;background-color:black;color:white;border:none;font-size:8px;^><tr style=^background-color:blue;color:white;border:none;^>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   <td nowrap style=^background-color:blue;color:white;border:none;padding-top:6px;padding-bottom:6px;font-size:11px;^>Feedback: </td>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <td nowrap style=^background-color:blue;color:white;border:none;padding-top:6px;padding-bottom:6px;font-size:11px;^>Feedback: </td>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   <td nowrap style=^background-color:blue;color:white;border:none;padding-top:6px;padding-bottom:6px;font-size:11px;^><input name=^zFeedback^ id=^zFeedback^ style=^left:4px;width:700px;^></td>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <td nowrap style=^background-color:blue;color:white;border:none;padding-top:6px;padding-bottom:6px;font-size:11px;^><input name=^zFeedback^ id=^zFeedback^ style=^left:4px;width:700px;^></td>", 1, 0,
                        10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   </tr></table></div>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   </tr></table></div>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:szWriteBuffer = "</form>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</form>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:// FORM GENERATION FOR FILE TRANSFER GROUPS
   //:// Create Form statements for each Group of type "File Transfer to Server".
   //:// Note that each Group requires a subcontrol of type EditBox and another of type PushBtn.
   //:CreateViewFromView( vDialogTemp, vDialog )
   CreateViewFromView( &vDialogTemp, vDialog );
   //:NAME VIEW vDialogTemp "vDialogTemp"
   SetNameForView( vDialogTemp, "vDialogTemp", 0, zLEVEL_TASK );
   //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
   lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
   //:szCtrlTag = "File Transfer to Server"
   ZeidonStringCopy( szCtrlTag, 1, 0, "File Transfer to Server", 1, 0, 33 );
   //:nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl,
   //:                       szCtrlTag, "", "", 0, "Window", "" )
   nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl, szCtrlTag, "", "", 0, "Window", "" );
   //:LOOP WHILE nRC >= zCURSOR_SET
   while ( nRC >= zCURSOR_SET )
   { 
      //:// Generate Form Statement for Group, with hidden field zAction.
      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szFormName = vDialogTemp.Control.Tag
      GetVariableFromAttribute( szFormName, 0, 'S', 65, vDialogTemp, "Control", "Tag", "", 0 );
      //:szWriteBuffer = "<form name=^" + szFormName + "^  id=^" + szFormName + "^ method=^post^ enctype=^multipart/form-data^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<form name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^  id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ method=^post^ enctype=^multipart/form-data^>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   <input name=^zAction^ id=^zAction^ type=^hidden^ value=^HELP^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zAction^ id=^zAction^ type=^hidden^ value=^HELP^>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

      //:CreateAbsolStyleString( vDialogTemp, szStyle, X_Size, Y_Size, "" )
      CreateAbsolStyleString( vDialogTemp, szStyle, X_Size, Y_Size, "" );

      //:szClass = ""
      ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
      //:IF vDialogTemp.Control.CSS_Class != ""
      if ( CompareAttributeToString( vDialogTemp, "Control", "CSS_Class", "" ) != 0 )
      { 
         //:szClass = " class=^" + vDialogTemp.Control.CSS_Class + "^"
         GetVariableFromAttribute( szTempString_37, 0, 'S', 255, vDialogTemp, "Control", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_37, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
      } 

      //:END
      //:szWriteBuffer = "<div " + szStyle + szClass + ">  <!-- " + vDialogTemp.Control.Tag + " --> "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">  <!-- ", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_38, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_38, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " --> ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:// Get Group positions for adding to subcontrols.
      //://X_Size = vDialogTemp.Control.PSDLG_X * DLUnits
      //://Y_Size = vDialogTemp.Control.PSDLG_Y * DLUnits

      //:// Generate hidden field zTargetFileName, with JSP to retrieve name.
      //:// We are currently positioned on the GroupBox and need to reposition on the subcontrol Button
      //:// to generate the FileName mapping..
      //:szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   strErrorMapValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:SetViewToSubobject( vDialogTemp, "CtrlCtrl" )
      SetViewToSubobject( vDialogTemp, "CtrlCtrl" );
      //:FOR EACH vDialogTemp.Control
      RESULT = SetCursorFirstEntity( vDialogTemp, "Control", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:IF vDialogTemp.ControlDef.Tag = "PushBtn"
         if ( CompareAttributeToString( vDialogTemp, "ControlDef", "Tag", "PushBtn" ) == 0 )
         { 
            //:IF vDialogTemp.CtrlMapER_Attribute EXISTS
            lTempInteger_57 = CheckExistenceOfEntity( vDialogTemp, "CtrlMapER_Attribute" );
            if ( lTempInteger_57 == 0 )
            { 
               //:// The mapping for the Push Button specifies the attribute that contains the Target File Name (without suffix).

               //:szWriteBuffer = "   strSessionId = session.getId( );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   strSessionId = session.getId( );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

               //:szWriteBuffer = "   nRC = " + vDialogTemp.CtrlMapView.Name +
               //:                ".GetView( strSessionId, ^" + vDialogTemp.CtrlMapView.Name + "^, vAppSubtask );"
               GetVariableFromAttribute( szTempString_39, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_39, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_40, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_40, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "   if ( nRC > 0 )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC > 0 )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

               //:szWriteBuffer = "   {"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      nRC = " + vDialogTemp.CtrlMapView.Name +
               //:                ".CheckExistenceOfEntity( strSessionId, ^" +
               //:                vDialogTemp.CtrlMapRelatedEntity.Name + "^ );"
               GetVariableFromAttribute( szTempString_41, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_41, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_42, 0, 'S', 33, vDialogTemp, "CtrlMapRelatedEntity", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_42, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      if ( nRC >= 0 )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "         strErrorMapValue = " +
               //:                vDialogTemp.CtrlMapView.Name + ".GetString( strSessionId, ^" +
               //:                vDialogTemp.CtrlMapRelatedEntity.Name + "^, ^" +
               //:                vDialogTemp.CtrlMapER_Attribute.Name + "^ );"
               GetVariableFromAttribute( szTempString_43, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_43, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetString( strSessionId, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_44, 0, 'S', 33, vDialogTemp, "CtrlMapRelatedEntity", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_44, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_45, 0, 'S', 33, vDialogTemp, "CtrlMapER_Attribute", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_45, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "   }"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

               //:IF (lTrace = 1)
               if ( lTrace == 1 )
               { 
                  //:szWriteBuffer = "   else"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
                  //:szWriteBuffer = "      " + vDialogTemp.CtrlMapView.Name +
                  //:                ".TraceLine( ^Invalid View: ^, ^" + vDialogTemp.Control.Tag + "^ );"
                  GetVariableFromAttribute( szTempString_46, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_46, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
                  GetVariableFromAttribute( szTempString_47, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_47, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               } 

               //:END
            } 


            //:END
         } 

         RESULT = SetCursorNextEntity( vDialogTemp, "Control", "" );
         //:END
      } 

      //:END
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   <input name=^zTargetFileName^ id=^zTargetFileName^ type=^hidden^ value=^<%=strErrorMapValue%>^ >"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zTargetFileName^ id=^zTargetFileName^ type=^hidden^ value=^<%=strErrorMapValue%>^ >", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

      //:// Process EditBox and PushBtn as subcontrols.
      //:FOR EACH vDialogTemp.Control
      RESULT = SetCursorFirstEntity( vDialogTemp, "Control", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:IF vDialogTemp.ControlDef.Tag = "EditBox"
         if ( CompareAttributeToString( vDialogTemp, "ControlDef", "Tag", "EditBox" ) == 0 )
         { 
            //:szCtrlTag     = vDialogTemp.Control.Tag
            GetVariableFromAttribute( szCtrlTag, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
            //:szControlType = vDialogTemp.ControlDef.Tag
            GetVariableFromAttribute( szControlType, 0, 'S', 51, vDialogTemp, "ControlDef", "Tag", "", 0 );
            //:szWriteBuffer = "   <% /* " + szCtrlTag + ":" + szControlType + " */ %>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   <% /* ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ":", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szControlType, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " */ %>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

            //:CreateAbsolStyleString( vDialogTemp, szStyle, X_Size, Y_Size, "" )
            CreateAbsolStyleString( vDialogTemp, szStyle, X_Size, Y_Size, "" );

            //:// For some reason with the <input type="file" control, the width property doesn't
            //:// seem to size the width correctly.  Use the "size" attribute instead.  The weird thing
            //:// is that if I don't include the width in style, then the "Browse" button that gets
            //:// created is not inline with the field that displays the upload file. ???!!!
            //:zIntegerToString( szWidth, 10, vDialogTemp.Control.SZDLG_X / 3.5 )
            GetIntegerFromAttribute( &lTempInteger_58, vDialogTemp, "Control", "SZDLG_X" );
            zIntegerToString( szWidth, 10, lTempInteger_58 / (ZDecimal) 3.5 );

            //:szClass = vDialogTemp.Control.CSS_Class
            GetVariableFromAttribute( szClass, 0, 'S', 257, vDialogTemp, "Control", "CSS_Class", "", 0 );
            //:IF szClass = ""
            if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
            { 
               //:szWriteBuffer = "   <input name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^" + szWidth + "^ " + szStyle + " type=^file^  >"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " type=^file^  >", 1, 0, 10001 );
               //:ELSE
            } 
            else
            { 
               //:szWriteBuffer = "   <input class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^" + szWidth + "^ " + szStyle + " type=^file^  >"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input class=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " type=^file^  >", 1, 0, 10001 );
            } 

            //:END
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         } 

         //:END
         //:IF vDialogTemp.ControlDef.Tag = "PushBtn"
         if ( CompareAttributeToString( vDialogTemp, "ControlDef", "Tag", "PushBtn" ) == 0 )
         { 
            //:szCtrlTag     = vDialogTemp.Control.Tag
            GetVariableFromAttribute( szCtrlTag, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
            //:szControlType = vDialogTemp.ControlDef.Tag
            GetVariableFromAttribute( szControlType, 0, 'S', 51, vDialogTemp, "ControlDef", "Tag", "", 0 );
            //:szWriteBuffer = "   <% /* " + szCtrlTag + ":" + szControlType + " */ %>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   <% /* ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ":", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szControlType, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " */ %>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

            //:CreateAbsolStyleString( vDialogTemp, szStyle, X_Size, Y_Size, "" )
            CreateAbsolStyleString( vDialogTemp, szStyle, X_Size, Y_Size, "" );
            //:szActionTag = ""
            ZeidonStringCopy( szActionTag, 1, 0, "", 1, 0, 35 );
            //:IF vDialogTemp.EventAct EXISTS
            lTempInteger_59 = CheckExistenceOfEntity( vDialogTemp, "EventAct" );
            if ( lTempInteger_59 == 0 )
            { 
               //:szActionTag = vDialogTemp.EventAct.Tag
               GetVariableFromAttribute( szActionTag, 0, 'S', 35, vDialogTemp, "EventAct", "Tag", "", 0 );
            } 

            //:END
            //:szClass       = vDialogTemp.Control.CSS_Class
            GetVariableFromAttribute( szClass, 0, 'S', 257, vDialogTemp, "Control", "CSS_Class", "", 0 );
            //:IF szClass = ""
            if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
            { 
               //://szWriteBuffer = "   <input type=^submit^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " + " value=^" + vDialogTemp.Control.Text + "^" +
               //://                " onclick=^" + szActionTag + "()^ " + szStyle + " >"
               //:szWriteBuffer = "   <button type=^button^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " +
               //:                " onclick=^" + szActionTag + "()^ " + szStyle + " >" + vDialogTemp.Control.Text + "</button>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   <button type=^button^ name=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "()^ ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " >", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_48, 0, 'S', 255, vDialogTemp, "Control", "Text", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_48, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "</button>", 1, 0, 10001 );
               //:ELSE
            } 
            else
            { 
               //://szWriteBuffer = "   <input class=^" + szClass + "^ type=^submit^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " + " value=^" + vDialogTemp.Control.Text + "^" +
               //://                " onclick=^" + szActionTag + "()^ " + szStyle + " >"
               //:szWriteBuffer = "   <button type=^button^ class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " +
               //:                " onclick=^" + szActionTag + "()^ " + szStyle + " >" + vDialogTemp.Control.Text + "</button>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   <button type=^button^ class=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "()^ ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " >", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_49, 0, 'S', 255, vDialogTemp, "Control", "Text", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_49, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "</button>", 1, 0, 10001 );
            } 

            //:END
            //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         } 

         RESULT = SetCursorNextEntity( vDialogTemp, "Control", "" );
         //:END
      } 

      //:END
      //:ResetViewFromSubobject( vDialogTemp )
      ResetViewFromSubobject( vDialogTemp );

      //:szWriteBuffer = "</div>  <!-- " + vDialogTemp.Control.Tag + " --> "
      GetVariableFromAttribute( szTempString_50, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_50, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " --> ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "</form>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "</form>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

      //:lControl = zQUAL_STRING + zPOS_NEXT + zRECURS
      lControl = zQUAL_STRING + zPOS_NEXT + zRECURS;
      //:szCtrlTag = "File Transfer to Server"
      ZeidonStringCopy( szCtrlTag, 1, 0, "File Transfer to Server", 1, 0, 33 );
      //:nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl,
      //:                       szCtrlTag, "", "", 0, "Window", "" )
      nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl, szCtrlTag, "", "", 0, "Window", "" );
   } 

   //:END
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );

   //:szWriteBuffer = "</div>   <!-- This is the end tag for the div '" + szDivContentClass + "' -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>   <!-- This is the end tag for the div '", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szDivContentClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "' -->", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:IF  szWindowIsPopup = "" AND szWindowIsForDashboard = ""
   if ( ZeidonStringCompare( szWindowIsPopup, 1, 0, "", 1, 0, 2 ) == 0 && ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "</div>   <!-- This is the end tag for the div 'maincontent' -->"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>   <!-- This is the end tag for the div 'maincontent' -->", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:// KJS 07/31/08 I don't think we need the following lines.  We are always going to have a div with either
   //:// content or a name designated by the user.
   //:// If there is a side menu, a div is created with an id of content.  We
   //:// need to create the ending div tag.
   //://IF szSideMenuExists = "Y"
   //://   szWriteBuffer = "</div>  <!-- This is the end tag for the div 'content'  or the class given by the user -->"
   //://   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //://END

   //:// KJS 07/31/08
   //:// Include a footer at the bottom before the end wrapper div.
   //:// Only put in a footer if we are generating with relative position.
   //:IF szNoPositioning = "Y" AND szWindowIsPopup = "" AND szWindowIsForDashboard = ""
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 && ZeidonStringCompare( szWindowIsPopup, 1, 0, "", 1, 0, 2 ) == 0 && ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:IF vDialogRoot.Dialog.WEB_FooterInclude = ""
      if ( CompareAttributeToString( vDialogRoot, "Dialog", "WEB_FooterInclude", "" ) == 0 )
      { 
         //:// If the user did not specify a footer, hardcode footer.inc
         //:szWriteBuffer = "<%@ include file=^./include/footer.inc^ %>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^./include/footer.inc^ %>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "<%@ include file=^" + vDialogRoot.Dialog.WEB_FooterInclude + "^ %>"
         GetVariableFromAttribute( szTempString_51, 0, 'S', 255, vDialogRoot, "Dialog", "WEB_FooterInclude", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_51, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ %>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
      } 

      //:END
   } 

   //:END

   //://<!--This text is a comment-->
   //:IF  szWindowIsPopup = "" AND szWindowIsForDashboard = ""
   if ( ZeidonStringCompare( szWindowIsPopup, 1, 0, "", 1, 0, 2 ) == 0 && ZeidonStringCompare( szWindowIsForDashboard, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "</div>  <!-- This is the end tag for wrapper -->"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- This is the end tag for wrapper -->", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:// DO WE PUT IN THE CODE FOR DASHBOARD HERE???? 1111

   //:szWriteBuffer = "</body>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</body>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "</html>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</html>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:// szWriteBuffer = "<%@ include file=^menubottom.inc^ %>"
   //:// WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )

   //:// If the Window HAS a menu, then this JSP has the navigation structure within it and contained
   //:// a div statement. So end the div.
   //:// IF vDialogRoot.DfltMenu EXISTS  we never need it???  dks  2006.02.25
   //://    szWriteBuffer = "</div>"
   //://    WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:// END

   //:szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   session.setAttribute( ^ZeidonWindow^, ^" + szFormName + "^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   session.setAttribute( ^ZeidonWindow^, ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   session.setAttribute( ^ZeidonAction^, null );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   session.setAttribute( ^ZeidonAction^, null );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:// KJS 11/05/09 - For login screens, we want to unregisterzeidon at the end of building a page.  That way
   //:// when people come to this page but don't do anything, we don't have a session open.
   //:IF vDialog.Window.WEB_UnregisterZeidonWindow = "Y"
   if ( CompareAttributeToString( vDialog, "Window", "WEB_UnregisterZeidonWindow", "Y" ) == 0 )
   { 
      //://szWriteBuffer = "<%"
      //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      //:szWriteBuffer = "   if ( vAppSubtask != null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( vAppSubtask != null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      vAppSubtask.TraceLine( ^After building the page UnregisterZeidonApplication: ----------------------------------->>> ^, ^" + szFormName + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask.TraceLine( ^After building the page UnregisterZeidonApplication: ----------------------------------->>> ^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      vAppSubtask.UnregisterZeidonApplication( strSessionId );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask.UnregisterZeidonApplication( strSessionId );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      vAppSubtask = null;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask = null;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      session.setAttribute( ^ZeidonSubtask^, vAppSubtask );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      session.setAttribute( ^ZeidonSubtask^, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "  }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "  }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   } 

   //:   //szWriteBuffer = "%>"
   //:   //WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:END

   //:szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:DropView( vDialogRoot )
   DropView( vDialogRoot );

   //:/*
   //:// KJS 08/30/12 - Putting this in for Aadit... Show in seconds the page load time.
   //:szWriteBuffer = "<%"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   // Show the time in seconds it takes to load the page."
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   Date tPageEnd = new Date();"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   double tMilli = tPageEnd.getTime() - tPageStart.getTime();"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   double tSeconds = tMilli / 1000;"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //://szWriteBuffer = "   //String strDiff =String.valueOf(tSeconds);"
   //:szWriteBuffer = "   String strSeconds =Double.toString(tSeconds); "
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   String strMilli = Double.toString(tMilli);     "
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //://szWriteBuffer = "   //vAppSubtask.TraceLine( "Page Load Time (milli): --------->>> ", strMilli );"
   //:szWriteBuffer = "   vAppSubtask.TraceLine( ^Page Load Time (seconds): ------->>> ^, strSeconds );"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "%>"
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   //:*/

   //:SysCloseFile( vDialog, lFileJSP, 0 )
   SysCloseFile( vDialog, lFileJSP, 0 );
   return( 0 );
// END
} 


//:TRANSFORMATION OPERATION
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_GenJSP_ProcessFileIn( zVIEW     vDialog,
                                zLONG     lFileJSP,
                                zPCHAR    szWriteBuffer )
{

   //:GenJSP_ProcessFileIn( VIEW             vDialog BASED ON LOD TZWDLGSO,
   //:                   INTEGER          lFileJSP,
   //:                   STRING ( 10000 ) szWriteBuffer )

   //:// Build the JSP function code to process a file being transferred from the Client to the Server.

   //:szWriteBuffer = "   ServletInputStream in = request.getInputStream();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   ServletInputStream in = request.getInputStream();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   byte[] line = new byte[256];"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   byte[] line = new byte[256];", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   byte[] crlf = {(byte) 0x0D, (byte) 0x0A}; // \r\n"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   byte[] crlf = {(byte) 0x0D, (byte) 0x0A}; // \\r\\n", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sLine = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sLine = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String enctype = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String enctype = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String boundary = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String boundary = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String status = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String status = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sName = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sName = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sSourceFile = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sSourceFile = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sTargetFile = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sTargetFile = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sExtension = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sExtension = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sSourceFileNameOnly = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sSourceFileNameOnly = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sTargetDirectory = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sTargetDirectory = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String zAction = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String zAction = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String zTargetFileName = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String zTargetFileName = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   FileOutputStream file = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   FileOutputStream file = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int i = in.readLine(line, 0, 256);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int i = in.readLine(line, 0, 256);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //://szWriteBuffer = "   int iFileLth = 0;"
   //://WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   //:szWriteBuffer = "   boolean holdNewLine = false;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   boolean holdNewLine = false;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   if (i != -1 && strActionToProcess == null)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if (i != -1 && strActionToProcess == null)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   while (i != -1) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   while (i != -1) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //://**********************************
   //:szWriteBuffer = "      iFileLth = iFileLth + i;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      iFileLth = iFileLth + i;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( iFileLth > 10485760 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( iFileLth > 10485760 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         file.close();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         file.close();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         file = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         file = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         break;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         break;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //://************************************
   //:szWriteBuffer = "      boolean hasNewLine = i>=2 && line[i-1]==crlf[1] "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      boolean hasNewLine = i>=2 && line[i-1]==crlf[1] ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         && line[i-2]== crlf[0];"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         && line[i-2]== crlf[0];", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      if (hasNewLine) i = i-2;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if (hasNewLine) i = i-2;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      sLine = new String(line, 0, i);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      sLine = new String(line, 0, i);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      if (enctype==null) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if (enctype==null) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         // try to determine the encryption type"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // try to determine the encryption type", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if (i>3 && sLine.startsWith(^--^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if (i>3 && sLine.startsWith(^--^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            enctype = ^form-data^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            enctype = ^form-data^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            boundary = sLine;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            boundary = sLine;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            status = ^boundary^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            status = ^boundary^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            enctype = ^x-www-form-urlencoded^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            enctype = ^x-www-form-urlencoded^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      else if (enctype.equals(^x-www-form-urlencoded^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      else if (enctype.equals(^x-www-form-urlencoded^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         //out.println(^****************^+sLine);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         //out.println(^****************^+sLine);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      else if (enctype.equals(^form-data^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      else if (enctype.equals(^form-data^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         // Calculating the status of the current line"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Calculating the status of the current line", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if (status.equals(^boundary^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if (status.equals(^boundary^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            // Expecting the ^Content-Disposition:^ line"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            // Expecting the ^Content-Disposition:^ line", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            status = ^disposition^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            status = ^disposition^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else if (status.equals(^disposition^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else if (status.equals(^disposition^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            // Expecting the ^Content-Type:^ line or a blank line"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            // Expecting the ^Content-Type:^ line or a blank line", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            if (sLine.startsWith(^Content-Type:^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            if (sLine.startsWith(^Content-Type:^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               status = ^type^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               status = ^type^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            else "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            else ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               status = ^blank^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               status = ^blank^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else if (status.equals(^type^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else if (status.equals(^type^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            // Expecting a blank line"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            // Expecting a blank line", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            status = ^blank^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            status = ^blank^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else if (status.equals(^blank^) |||| status.equals(^data^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else if (status.equals(^blank^) || status.equals(^data^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            // Expecting the data or boundary"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            // Expecting the data or boundary", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            if (sLine.startsWith(boundary)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            if (sLine.startsWith(boundary)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               status = ^boundary^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               status = ^boundary^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            else "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            else ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               status = ^data^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               status = ^data^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         // Now ^status^ is updated. Let's do the saving and echoing"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Now ^status^ is updated. Let's do the saving and echoing", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if (status.equals(^disposition^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if (status.equals(^disposition^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            // Getting the file name and open a file for saving"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            // Getting the file name and open a file for saving", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            int l = sLine.indexOf(^filename=^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            int l = sLine.indexOf(^filename=^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            int x;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            int x;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "            if (l>=0) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            if (l>=0) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               sTargetFile = sTargetFile.replaceAll(^\^^,^^); "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               sTargetFile = sTargetFile.replaceAll(^\\^^,^^); ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "               //We need to save the file extension and use"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //We need to save the file extension and use", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               //this as the output file extension no matter what "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //this as the output file extension no matter what ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               //extension the output file has."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //extension the output file has.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               sSourceFile = sLine.substring(l+9);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               sSourceFile = sLine.substring(l+9);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               sSourceFile = sSourceFile.replaceAll(^\^^,^^); "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               sSourceFile = sSourceFile.replaceAll(^\\^^,^^); ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               l = sSourceFile.lastIndexOf(^.^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               l = sSourceFile.lastIndexOf(^.^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "               x = sSourceFile.lastIndexOf(^\\^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               x = sSourceFile.lastIndexOf(^\\\\^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "               //If x > l then the filename has no extension and"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //If x > l then the filename has no extension and", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               //there must be a period in the directory name."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //there must be a period in the directory name.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               if (x > l)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               if (x > l)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  sExtension = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  sExtension = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  sExtension = sSourceFile.substring(l+1);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  sExtension = sSourceFile.substring(l+1);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               sSourceFileNameOnly = sSourceFile.substring(x + 1);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               sSourceFileNameOnly = sSourceFile.substring(x + 1);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               strInputFileName = sSourceFileNameOnly;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               strInputFileName = sSourceFileNameOnly;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               sTargetFile = sTargetFile.replaceAll(^\^^,^^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               sTargetFile = sTargetFile.replaceAll(^\\^^,^^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               l = sTargetFile.lastIndexOf(^.^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               l = sTargetFile.lastIndexOf(^.^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               x = sTargetFile.lastIndexOf(^\\^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               x = sTargetFile.lastIndexOf(^\\\\^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );


   //:szWriteBuffer = "               //If the target files is just a directory (no file name is specified)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //If the target files is just a directory (no file name is specified)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               //then use the name of the input file."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //then use the name of the input file.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               if (x+1 == sTargetFile.length())"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               if (x+1 == sTargetFile.length())", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  sTargetDirectory = sTargetFile;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  sTargetDirectory = sTargetFile;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  sTargetFile = sTargetFile + sSourceFileNameOnly;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  sTargetFile = sTargetFile + sSourceFileNameOnly;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  sTargetDirectory = sTargetFile.substring(0, x + 1);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  sTargetDirectory = sTargetFile.substring(0, x + 1);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  //Target file name has no extension, so use the extension on the"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  //Target file name has no extension, so use the extension on the", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  //source file.  Otherwise, keep the name of target source entirely."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  //source file.  Otherwise, keep the name of target source entirely.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  if (x > l)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  if (x > l)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                     //No extension"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                     //No extension", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                     if (sExtension.equals(^^))"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                     if (sExtension.equals(^^))", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                        sTargetFile = sTargetFile + sExtension;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                        sTargetFile = sTargetFile + sExtension;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                     else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                     else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                        sTargetFile = sTargetFile + ^.^ + sExtension;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                        sTargetFile = sTargetFile + ^.^ + sExtension;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               if (sTargetFile.length()>0)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               if (sTargetFile.length()>0)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                   //If the directory doesn't exist, Create one. "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                   //If the directory doesn't exist, Create one. ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  File f = new File(sTargetDirectory);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  File f = new File(sTargetDirectory);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  boolean ok = f.mkdirs();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  boolean ok = f.mkdirs();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  file = new FileOutputStream(sTargetFile);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  file = new FileOutputStream(sTargetFile);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               l = sLine.indexOf(^ name=^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               l = sLine.indexOf(^ name=^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               if (l>=0) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               if (l>=0) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  sName = sLine.substring(l+6);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  sName = sLine.substring(l+6);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  sName = sName.replaceAll(^\^^,^^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  sName = sName.replaceAll(^\\^^,^^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  l = sName.lastIndexOf(^\\^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  l = sName.lastIndexOf(^\\\\^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  if (l>=0) sName = sName.substring(l+1);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  if (l>=0) sName = sName.substring(l+1);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  if (sName.length()>0) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  if (sName.length()>0) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                     if (sName.equals(^zAction^))"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                     if (sName.equals(^zAction^))", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                        zAction = ^Action^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                        zAction = ^Action^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                     else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                     else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                        zAction = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                        zAction = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                     if (sName.equals(^zTargetFileName^))"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                     if (sName.equals(^zTargetFileName^))", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                        zTargetFileName = ^TargetFileName^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                        zTargetFileName = ^TargetFileName^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                     else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                     else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                        zTargetFileName = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                        zTargetFileName = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else if (status.equals(^boundary^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else if (status.equals(^boundary^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            if (file!=null) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            if (file!=null) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               file.close();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               file.close();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               file = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               file = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if (status.equals(^data^)) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if (status.equals(^data^)) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            //We are writing out to the filename"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            //We are writing out to the filename", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            if (file!=null) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            if (file!=null) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               if (holdNewLine) file.write(crlf);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               if (holdNewLine) file.write(crlf);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               file.write(line,0,i);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               file.write(line,0,i);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               holdNewLine = hasNewLine;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               holdNewLine = hasNewLine;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            else "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            else ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               //Check if we have come across zAction or zTargetFileName"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //Check if we have come across zAction or zTargetFileName", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               //If so, then get the data and save them to a global filename."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               //If so, then get the data and save them to a global filename.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               if (zAction.equals(^Action^))"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               if (zAction.equals(^Action^))", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  strActionToProcess = sLine;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  strActionToProcess = sLine;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  zAction = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  zAction = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               if (zTargetFileName.equals(^TargetFileName^))"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               if (zTargetFileName.equals(^TargetFileName^))", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  sTargetFile = sLine;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  sTargetFile = sLine;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "                  zTargetFileName = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "                  zTargetFileName = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               holdNewLine = false;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               holdNewLine = false;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            holdNewLine = false;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            holdNewLine = false;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      i = in.readLine(line, 0, 256);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      i = in.readLine(line, 0, 256);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
   return( 0 );
// END
} 


//:LOCAL OPERATION
//:GenJSP_DownloadFile( VIEW vDialog,
//:                     STRING ( 32 ) szDownloadFileName )

//:   STRING ( 10000 ) szWriteBuffer
static zLONG
oTZWDLGSO_GenJSP_DownloadFile( zVIEW     vDialog,
                               zPCHAR    szDownloadFileName )
{
   zCHAR     szWriteBuffer[ 10001 ] = { 0 }; 
   //:INTEGER          lFileJSP
   zLONG     lFileJSP = 0; 


   //:lFileJSP = SysOpenFile( vDialog, szDownloadFileName, COREFILE_WRITE )
   lFileJSP = SysOpenFile( vDialog, szDownloadFileName, COREFILE_WRITE );
   //:IF lFileJSP < 0
   if ( lFileJSP < 0 )
   { 
      //:RETURN -1
      return( -1 );
   } 

   //:END

   //:szWriteBuffer = "<%-- wDownload_File --%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%-- wDownload_File --%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<%@ page import=^java.util.*,javax.servlet.*,javax.servlet.http.*,java.io.*,zeidon.zView^ %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ page import=^java.util.*,javax.servlet.*,javax.servlet.http.*,java.io.*,zeidon.zView^ %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<% "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<% ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   session = request.getSession( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   session = request.getSession( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strSessionId = session.getId( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strSessionId = session.getId( );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "  zeidon.zView vAppSubtask; // view to this subtask"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "  zeidon.zView vAppSubtask; // view to this subtask", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   zView vKZXMLPGO = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   zView vKZXMLPGO = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int nRC;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int nRC;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   String strURL;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strURL;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strError = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strError = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strErrorFlag = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strErrorFlag = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strErrorTitle = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strErrorTitle = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String strErrorMsg = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String strErrorMsg = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   // Check to see if the Zeidon subtask view already exists.  If not, create"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Check to see if the Zeidon subtask view already exists.  If not, create", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "  // it and copy it into the application object."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "  // it and copy it into the application object.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   vAppSubtask = (zeidon.zView) session.getAttribute( ^ZeidonSubtask^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask = (zeidon.zView) session.getAttribute( ^ZeidonSubtask^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( vAppSubtask == null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( vAppSubtask == null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      strURL = response.encodeRedirectURL( ^logout.jsp^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strURL = response.encodeRedirectURL( ^logout.jsp^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      response.sendRedirect( strURL );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      response.sendRedirect( strURL );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      return;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      return;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      vAppSubtask.TraceLine( ^*** In wDownload_file: ^, ^^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask.TraceLine( ^*** In wDownload_file: ^, ^^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      if ( vKZXMLPGO == null )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( vKZXMLPGO == null )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "        vKZXMLPGO = new zeidon.zView( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "        vKZXMLPGO = new zeidon.zView( strSessionId );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      nRC = vKZXMLPGO.GetView( strSessionId, ^KZXMLPGO^, vAppSubtask );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = vKZXMLPGO.GetView( strSessionId, ^KZXMLPGO^, vAppSubtask );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( nRC <= 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC <= 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vKZXMLPGO.InitWebSessionObject( strSessionId, vAppSubtask, ^TestUserID^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vKZXMLPGO.InitWebSessionObject( strSessionId, vAppSubtask, ^TestUserID^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vKZXMLPGO.SetName( strSessionId, ^KZXMLPGO^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vKZXMLPGO.SetName( strSessionId, ^KZXMLPGO^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      strURL = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strURL = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      nRC = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   String sDownloadFile = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sDownloadFile = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sSourceFileNameOnly = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sSourceFileNameOnly = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   String sExtension = null;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   String sExtension = null;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int l;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int l;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   int x;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   int x;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   // Download File Processing"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Download File Processing", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   sDownloadFile = (String) session.getAttribute( ^DownloadFile^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   sDownloadFile = (String) session.getAttribute( ^DownloadFile^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   vAppSubtask.TraceLine( ^*** Download File: ^, sDownloadFile );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine( ^*** Download File: ^, sDownloadFile );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   // Replace any quotes."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Replace any quotes.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   sDownloadFile = sDownloadFile.replaceAll(^\^^,^^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   sDownloadFile = sDownloadFile.replaceAll(^\\^^,^^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   l = sDownloadFile.lastIndexOf(^.^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   l = sDownloadFile.lastIndexOf(^.^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   x = sDownloadFile.lastIndexOf(^\\^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   x = sDownloadFile.lastIndexOf(^\\\\^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   vAppSubtask.TraceLine( ^*** sDownloadFile: ^, sDownloadFile );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine( ^*** sDownloadFile: ^, sDownloadFile );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   // If x > l then the filename has no extension and"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // If x > l then the filename has no extension and", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // there must be a period in the directory name."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // there must be a period in the directory name.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // Right now we are not using sExtension but just"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Right now we are not using sExtension but just", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // in case we want to change the encType I want"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // in case we want to change the encType I want", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   // to capture this."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // to capture this.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if (x > l)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if (x > l)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      sExtension = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      sExtension = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      sExtension = sDownloadFile.substring(l+1);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      sExtension = sDownloadFile.substring(l+1);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   // Get the filename only without directories."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // Get the filename only without directories.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   sSourceFileNameOnly = sDownloadFile.substring(x + 1);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   sSourceFileNameOnly = sDownloadFile.substring(x + 1);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   File InputFile = new File(sDownloadFile);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   File InputFile = new File(sDownloadFile);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   FileInputStream fis = new FileInputStream(InputFile); "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   FileInputStream fis = new FileInputStream(InputFile); ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   try"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   try", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      String contenttype = ^application/octet-stream^;  "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      String contenttype = ^application/octet-stream^;  ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      response.setContentType(contenttype);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      response.setContentType(contenttype);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      response.addHeader(^Content-Disposition^, ^attachment; filename=^ + sSourceFileNameOnly + ^;^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      response.addHeader(^Content-Disposition^, ^attachment; filename=^ + sSourceFileNameOnly + ^;^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      vAppSubtask.TraceLine( ^*** In sSourceFileNameOnly: ^, sSourceFileNameOnly);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      vAppSubtask.TraceLine( ^*** In sSourceFileNameOnly: ^, sSourceFileNameOnly);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      //response.setHeader(^Cache-Control^, ^cache,must-revalidate^); "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      //response.setHeader(^Cache-Control^, ^cache,must-revalidate^); ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      //response.addHeader(^Pragma^, ^public^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      //response.addHeader(^Pragma^, ^public^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      ServletOutputStream outStream = response.getOutputStream();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      ServletOutputStream outStream = response.getOutputStream();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      int c = 0;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      int c = 0;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      while ((c=fis.read())!=-1)"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      while ((c=fis.read())!=-1)", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         outStream.write(c); "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         outStream.write(c); ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      outStream.flush(); "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      outStream.flush(); ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      outStream.close();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      outStream.close();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      fis.close();"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      fis.close();", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   catch (Exception e) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   catch (Exception e) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if (InputFile!=null && InputFile.exists()) "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if (InputFile!=null && InputFile.exists()) ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         //TraceLine"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         //TraceLine", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         vAppSubtask.TraceLine( ^Error downloading file: ^, sDownloadFile );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         vAppSubtask.TraceLine( ^Error downloading file: ^, sDownloadFile );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   vAppSubtask.TraceLine( ^*** In wDownload_file 2: ^, ^^);"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   vAppSubtask.TraceLine( ^*** In wDownload_file 2: ^, ^^);", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<html><body></body></html>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<html><body></body></html>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );


   //:SysCloseFile( vDialog, lFileJSP, 0 )
   SysCloseFile( vDialog, lFileJSP, 0 );

   //:RETURN 0
   return( 0 );
// END
} 


//:LOCAL OPERATION
//:GenJSP_FindTAB( VIEW vWindow BASED ON LOD TZWDLGSO )

//:   SHORT nRC
static zSHORT
oTZWDLGSO_GenJSP_FindTAB( zVIEW     vWindow )
{
   zSHORT    nRC = 0; 
   zSHORT    RESULT; 


   //:// Determine if a Control with a TAB exists for a Control on the Window.
   //:// If so, return a 1.
   //:IF vWindow.Control.SyncKey < 9999
   if ( CompareAttributeToInteger( vWindow, "Control", "SyncKey", 9999 ) < 0 )
   { 
      //:RETURN 1
      return( 1 );
   } 

   //:END
   //:FOR EACH vWindow.CtrlCtrl
   RESULT = SetCursorFirstEntity( vWindow, "CtrlCtrl", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:SetViewToSubobject( vWindow, "CtrlCtrl" )
      SetViewToSubobject( vWindow, "CtrlCtrl" );
      //:nRC = GenJSP_FindTAB( vWindow )
      nRC = oTZWDLGSO_GenJSP_FindTAB( vWindow );
      //:ResetViewFromSubobject( vWindow )
      ResetViewFromSubobject( vWindow );
      //:IF nRC > 0
      if ( nRC > 0 )
      { 
         //:RETURN nRC
         return( nRC );
      } 

      RESULT = SetCursorNextEntity( vWindow, "CtrlCtrl", "" );
      //:END
   } 

   //:END
   //:RETURN 0
   return( 0 );
// END
} 


//:LOCAL OPERATION
//:FlagUsedViewsGetFocusR( VIEW vDialog     BASED ON LOD TZWDLGSO,
//:                        VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                        STRING ( 32 )    szFocusCtrlTag,
//:                        INTEGER          lTabIndex,
//:                        STRING ( 32 )    szWysiwygEditor )

//:   STRING ( 50 ) szControlType
static zLONG
oTZWDLGSO_FlagUsedViewsGetFocusR( zVIEW     vDialog,
                                  zVIEW     vDialogRoot,
                                  zPCHAR    szFocusCtrlTag,
                                  zLONG     lTabIndex,
                                  zPCHAR    szWysiwygEditor )
{
   zCHAR     szControlType[ 51 ] = { 0 }; 
   //:STRING ( 1 )  szProcessControlFlag
   zCHAR     szProcessControlFlag[ 2 ] = { 0 }; 
   //:INTEGER       lTempIndex
   zLONG     lTempIndex = 0; 
   //:INTEGER       lSubtype
   zLONG     lSubtype = 0; 
   //:INTEGER       lSubtypeX
   zLONG     lSubtypeX = 0; 
   //:INTEGER       lSort
   zLONG     lSort = 0; 
   //:INTEGER       nRC
   zLONG     nRC = 0; 
   zSHORT    RESULT; 
   zLONG     lTempInteger_0; 
   zSHORT    lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zSHORT    lTempInteger_3; 


   //:lSort = 0
   lSort = 0;

   //:// This operation performs the following functions:
   //:// 1. It is used to identify any Named Views that have mapping on this window (sets flag wWindowUseFlag).
   //:// 2. It identifies if a Grid exists that uses sorting. (That is needed to pull in the proper .js files.)
   //:// 3. It identifies the Control that should be given focus by setting the szFocusCtrlTag value.
   //:// 4. It identifies each ComboBox on the Page. This is used to generate on OnChange event capture by the calling routine.
   //:// 5. It identifies if there is an MLE request for the wysiwygEditor files.

   //:FOR EACH vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 

      //:szControlType = vDialog.ControlDef.Tag
      GetVariableFromAttribute( szControlType, 0, 'S', 51, vDialog, "ControlDef", "Tag", "", 0 );

      //:szProcessControlFlag = ""
      ZeidonStringCopy( szProcessControlFlag, 1, 0, "", 1, 0, 2 );
      //:IF szControlType = "GridEditCtl"
      if ( ZeidonStringCompare( szControlType, 1, 0, "GridEditCtl", 1, 0, 51 ) == 0 )
      { 
         //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Edit"
         RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Edit", "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:// For a GridEditCtl control, we have input mapping only if "Edit" property is requested.
            //:szProcessControlFlag = "Y"
            ZeidonStringCopy( szProcessControlFlag, 1, 0, "Y", 1, 0, 2 );
         } 

         //:END
      } 

      //:END
      //:IF szControlType = "GroupBox"
      if ( ZeidonStringCompare( szControlType, 1, 0, "GroupBox", 1, 0, 51 ) == 0 )
      { 
         //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Survey Group"
         RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Survey Group", "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:// If we have a group box that has a web property of "Survey Group" then this is a survey and
            //:// we will need mapping for each survey question.
            //:szProcessControlFlag = "Y"
            ZeidonStringCopy( szProcessControlFlag, 1, 0, "Y", 1, 0, 2 );
         } 

         //:END
      } 

      //:END
      //:IF szControlType = "EditBox" OR
      //:   szControlType = "ComboBox" OR
      //:   szControlType = "Text" OR
      //:   szControlType = "CheckBox" OR
      //:   szControlType = "ListBox" OR
      //:   szControlType = "MLEdit" OR
      //:   szControlType = "Outliner" OR
      //:   szControlType = "RadioGrp" OR
      //:   szControlType = "GridCheckCtl" OR
      //:   szControlType = "Grid" OR
      //:   szControlType = "Calendar" OR
      //:   szProcessControlFlag = "Y"
      if ( ZeidonStringCompare( szControlType, 1, 0, "EditBox", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "ComboBox", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "Text", 1, 0, 51 ) == 0 ||
           ZeidonStringCompare( szControlType, 1, 0, "CheckBox", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "ListBox", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "MLEdit", 1, 0, 51 ) == 0 ||
           ZeidonStringCompare( szControlType, 1, 0, "Outliner", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "RadioGrp", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "GridCheckCtl", 1, 0, 51 ) == 0 ||
           ZeidonStringCompare( szControlType, 1, 0, "Grid", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "Calendar", 1, 0, 51 ) == 0 || ZeidonStringCompare( szProcessControlFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 

         //:// 1.(above) Identify any Named Views that have mapping on this window.
         //:SET CURSOR FIRST vDialog.CtrlMapView WITHIN vDialog.Control
         RESULT = SetCursorFirstEntity( vDialog, "CtrlMapView", "Control" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:SET CURSOR FIRST vDialogRoot.ViewObjRef
            //:           WHERE vDialogRoot.ViewObjRef.ZKey = vDialog.CtrlMapView.ZKey
            GetIntegerFromAttribute( &lTempInteger_0, vDialog, "CtrlMapView", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( vDialogRoot, "ViewObjRef", "ZKey", lTempInteger_0, "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:vDialogRoot.ViewObjRef.wWindowUseFlag = "Y"
               SetAttributeFromString( vDialogRoot, "ViewObjRef", "wWindowUseFlag", "Y" );
            } 

            //:END

            //:IF szControlType = "ComboBox"
            if ( ZeidonStringCompare( szControlType, 1, 0, "ComboBox", 1, 0, 51 ) == 0 )
            { 
               //:SET CURSOR NEXT vDialog.CtrlMap
               RESULT = SetCursorNextEntity( vDialog, "CtrlMap", "" );
               //:IF vDialog.CtrlMapView EXISTS
               lTempInteger_1 = CheckExistenceOfEntity( vDialog, "CtrlMapView" );
               if ( lTempInteger_1 == 0 )
               { 
                  //:SET CURSOR FIRST vDialogRoot.ViewObjRef
                  //:           WHERE vDialogRoot.ViewObjRef.ZKey = vDialog.CtrlMapView.ZKey
                  GetIntegerFromAttribute( &lTempInteger_2, vDialog, "CtrlMapView", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vDialogRoot, "ViewObjRef", "ZKey", lTempInteger_2, "" );
                  //:IF RESULT >= zCURSOR_SET
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:vDialogRoot.ViewObjRef.wWindowUseFlag = "Y"
                     SetAttributeFromString( vDialogRoot, "ViewObjRef", "wWindowUseFlag", "Y" );
                  } 

                  //:END
               } 

               //:END
            } 

            //:END
         } 

         //:END

         //:// 2.(above) For Grid, identify is Sort is requested.
         //:IF lSort = 0 AND szControlType = "Grid"
         if ( lSort == 0 && ZeidonStringCompare( szControlType, 1, 0, "Grid", 1, 0, 51 ) == 0 )
         { 

            //:lSubtypeX = vDialog.Control.ExtendedStyle
            GetIntegerFromAttribute( &lSubtypeX, vDialog, "Control", "ExtendedStyle" );

            //:// #define zSS_SORTEDHEADERS 0x00040000 = 262144
            //:// #define zSS_REMEMBERSORT  0x00020000 = 131072

            //:lSort = IsFlagSequenceSet( lSubtypeX, 262144 )
            lSort = IsFlagSequenceSet( lSubtypeX, 262144 );
            //:IF lSort = 0
            if ( lSort == 0 )
            { 
               //:lSort = IsFlagSequenceSet( lSubtypeX, 131072 )
               lSort = IsFlagSequenceSet( lSubtypeX, 131072 );
            } 

            //:END
         } 


         //:END

         //:// 3.(above) Except for Grid, ListBox and Text, process for setting Focus.
         //:IF szControlType != "Grid" AND
         //:   szControlType != "Text" AND
         //:   szControlType != "ListBox"
         if ( ZeidonStringCompare( szControlType, 1, 0, "Grid", 1, 0, 51 ) != 0 && ZeidonStringCompare( szControlType, 1, 0, "Text", 1, 0, 51 ) != 0 && ZeidonStringCompare( szControlType, 1, 0, "ListBox", 1, 0, 51 ) != 0 )
         { 

            //:lTempIndex = vDialog.Control.SyncKey
            GetIntegerFromAttribute( &lTempIndex, vDialog, "Control", "SyncKey" );
            //:IF lTempIndex != 0 AND lTempIndex < lTabIndex
            if ( lTempIndex != 0 && lTempIndex < lTabIndex )
            { 

               //:szFocusCtrlTag = vDialog.Control.Tag
               GetVariableFromAttribute( szFocusCtrlTag, 0, 'S', 33, vDialog, "Control", "Tag", "", 0 );
               //:lTabIndex = lTempIndex
               lTabIndex = lTempIndex;
            } 


            //:END
         } 

         //:END

         //:// 4.(above) Create entry for ComboBox.
         //:IF szControlType = "ComboBox"
         if ( ZeidonStringCompare( szControlType, 1, 0, "ComboBox", 1, 0, 51 ) == 0 )
         { 
            //:lSubtype = vDialog.Control.Subtype
            GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "Subtype" );
            //:nRC = AreBitsSetInFlag( lSubtype, 61440 ) // 0x0000F000
            nRC = AreBitsSetInFlag( lSubtype, 61440 );
            //:IF nRC = 0   // IF vDialog.Control.Subtype < 12000  ==> Domain Combobox
            if ( nRC == 0 )
            { 
               //:CREATE ENTITY vDialogRoot.ComboBoxEntry
               RESULT = CreateEntity( vDialogRoot, "ComboBoxEntry", zPOS_AFTER );
               //:vDialogRoot.ComboBoxEntry.Name = vDialog.Control.Tag
               SetAttributeFromAttribute( vDialogRoot, "ComboBoxEntry", "Name", vDialog, "Control", "Tag" );
            } 

            //:END
         } 

         //:END

         //:// 5.(above) Check for wysiwygEditor.
         //:IF szControlType = "MLEdit" AND vDialog.Control.WebCtrlType = "wysiwygEditor"
         if ( ZeidonStringCompare( szControlType, 1, 0, "MLEdit", 1, 0, 51 ) == 0 && CompareAttributeToString( vDialog, "Control", "WebCtrlType", "wysiwygEditor" ) == 0 )
         { 
            //:szWysiwygEditor = vDialog.Control.JavaScript
            GetVariableFromAttribute( szWysiwygEditor, 0, 'S', 33, vDialog, "Control", "JavaScript", "", 0 );
            //:IF szWysiwygEditor = ""
            if ( ZeidonStringCompare( szWysiwygEditor, 1, 0, "", 1, 0, 33 ) == 0 )
            { 
               //:szWysiwygEditor = vDialog.Control.Tag
               GetVariableFromAttribute( szWysiwygEditor, 0, 'S', 33, vDialog, "Control", "Tag", "", 0 );
            } 

            //:END
         } 

         //:END

         //:ELSE
      } 
      else
      { 
         //:// Continue processing subobjects.
         //:IF vDialog.CtrlCtrl EXISTS
         lTempInteger_3 = CheckExistenceOfEntity( vDialog, "CtrlCtrl" );
         if ( lTempInteger_3 == 0 )
         { 
            //:SetViewToSubobject( vDialog, "CtrlCtrl" )
            SetViewToSubobject( vDialog, "CtrlCtrl" );
            //:lTempIndex = FlagUsedViewsGetFocusR( vDialog, vDialogRoot, szFocusCtrlTag, lTabIndex, szWysiwygEditor )
            lTempIndex = oTZWDLGSO_FlagUsedViewsGetFocusR( vDialog, vDialogRoot, szFocusCtrlTag, lTabIndex, szWysiwygEditor );
            //:IF lTempIndex != 0
            if ( lTempIndex != 0 )
            { 
               //:lSort = 1
               lSort = 1;
            } 

            //:END

            //:ResetViewFromSubobject( vDialog )
            ResetViewFromSubobject( vDialog );
         } 


         //:END
      } 

      RESULT = SetCursorNextEntity( vDialog, "Control", "" );
      //:END
   } 

   //:END

   //:RETURN lSort
   return( lSort );
// END
} 


 
#ifdef __cplusplus
}
#endif
