#define KZSYSSVC_INCL
#include "KZOENGAA.H" 
#include "TZ__OPRS.H" 
#include "tzlodopr.h" 
#include "ZDRVROPR.H" 
 
#ifdef __cplusplus
extern "C"
{
#endif
 
#include "ZEIDONOP.H"

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_NLS_ControlText( zVIEW     vDialog,
                           LPVIEWENTITY lpEntity,
                           LPVIEWATTRIB lpAttribute,
                           zSHORT    GetOrSetFlag );


zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_NLS_ControlDIL_Text( zVIEW     vDialog,
                               LPVIEWENTITY lpEntity,
                               LPVIEWATTRIB lpAttribute,
                               zSHORT    GetOrSetFlag );


zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_NLS_CaptionText( zVIEW     vDialog,
                           LPVIEWENTITY lpEntity,
                           LPVIEWATTRIB lpAttribute,
                           zSHORT    GetOrSetFlag );


static zSHORT
oTZWDLGSO_OptionRelinkDelete( zVIEW     vSubtask,
                              zVIEW     vLOD_LPLR,
                              zVIEW     vDialog,
                              zVIEW     vOption,
                              zPVIEW    vLastLOD,
                              zPLONG    LastViewZKey );


zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_NLS_OptionText( zVIEW     vDialog,
                          LPVIEWENTITY lpEntity,
                          LPVIEWATTRIB lpAttribute,
                          zSHORT    GetOrSetFlag );


//:TRANSFORMATION OPERATION
//:ControlRelinkDelete( VIEW    vDialog     BASED ON LOD TZWDLGSO,
//:                     VIEW    vControl    BASED ON LOD TZWDLGSO,
//:                     VIEW    vLastLOD    BASED ON LOD TZZOLODO,
//:                     INTEGER LastViewZKey,
//:                     VIEW    vLOD_LPLR   BASED ON LOD TZCMLPLO,
//:                     VIEW    vSubtask )

//:   VIEW vDomain BASED ON LOD  TZDGSRCO
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_ControlRelinkDelete( zVIEW     vDialog,
                               zVIEW     vControl,
                               zPVIEW    vLastLOD,
                               zPLONG    LastViewZKey,
                               zVIEW     vLOD_LPLR,
                               zVIEW     vSubtask )
{
   zVIEW     vDomain = 0; 
   //:VIEW vReport BASED ON LOD  TZRPSRCO
   zVIEW     vReport = 0; 
   //:VIEW vPE     BASED ON LOD  TZPESRCO
   zVIEW     vPE = 0; 
   //:VIEW PE_List BASED ON LOD  TZCMLPLO
   zVIEW     PE_List = 0; 
   //:STRING ( 255 ) szMsg
   zCHAR     szMsg[ 256 ] = { 0 }; 
   //:STRING ( 64 )  szWindowReportName
   zCHAR     szWindowReportName[ 65 ] = { 0 }; 
   //:STRING ( 1 )   szContinueParseGen
   zCHAR     szContinueParseGen[ 2 ] = { 0 }; 
   //:INTEGER        nRemapFlag
   zLONG     nRemapFlag = 0; 
   //:SHORT          nRC
   zSHORT    nRC = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    RESULT; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zLONG     lTempInteger_1; 
   zCHAR     szTempString_2[ 33 ]; 
   zLONG     lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zLONG     lTempInteger_4; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zLONG     lTempInteger_5; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zSHORT    lTempInteger_6; 
   zLONG     lTempInteger_7; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zSHORT    lTempInteger_8; 
   zCHAR     szTempString_10[ 33 ]; 
   zSHORT    lTempInteger_9; 
   zCHAR     szTempString_11[ 33 ]; 
   zSHORT    lTempInteger_10; 
   zSHORT    lTempInteger_11; 
   zSHORT    lTempInteger_12; 
   zSHORT    lTempInteger_13; 
   zSHORT    lTempInteger_14; 
   zLONG     lTempInteger_15; 
   zLONG     lTempInteger_16; 
   zCHAR     szTempString_12[ 33 ]; 
   zCHAR     szTempString_13[ 33 ]; 
   zCHAR     szTempString_14[ 33 ]; 
   zSHORT    lTempInteger_17; 
   zLONG     lTempInteger_18; 
   zCHAR     szTempString_15[ 33 ]; 
   zCHAR     szTempString_16[ 33 ]; 
   zCHAR     szTempString_17[ 33 ]; 


   //://  Get View to Presentation Environment.
   //:IF GetViewByName( vPE, "TZPESRCO", vSubtask, zLEVEL_TASK ) < 0
   lTempInteger_0 = GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );
   if ( lTempInteger_0 < 0 )
   { 
      //:RetrieveViewForMetaList( vSubtask, PE_List, zREFER_PENV_META )
      RetrieveViewForMetaList( vSubtask, &PE_List, zREFER_PENV_META );
      //:nRC = LoadZeidonPPE( vSubtask, vPE, zREFER_PENV_META, PE_List,
      //:                     "Configuration Management", "" )
      nRC = LoadZeidonPPE( vSubtask, &vPE, zREFER_PENV_META, PE_List, "Configuration Management", "" );
      //:DropView( PE_List )
      DropView( PE_List );
      //:IF nRC < 0
      if ( nRC < 0 )
      { 
         //:RETURN nRC
         return( nRC );
      } 

      //:END

      //:SetNameForView( vPE, "TZPESRCO", vSubtask, zLEVEL_TASK )
      SetNameForView( vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );
   } 

   //:END

   //:// Process each subcontrol.
   //:FOR EACH vControl.CtrlCtrl
   RESULT = SetCursorFirstEntity( vControl, "CtrlCtrl", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:SetViewToSubobject( vControl, "CtrlCtrl" )
      SetViewToSubobject( vControl, "CtrlCtrl" );
      //:ControlRelinkDelete( vDialog, vControl, vLastLOD,
      //:                     LastViewZKey, vLOD_LPLR, vSubtask )
      oTZWDLGSO_ControlRelinkDelete( vDialog, vControl, vLastLOD, LastViewZKey, vLOD_LPLR, vSubtask );
      //:ResetViewFromSubobject( vControl )
      ResetViewFromSubobject( vControl );
      RESULT = SetCursorNextEntity( vControl, "CtrlCtrl", "" );
   } 

   //:END

   //:// Set szWindowReportName depending on whether or not view "Report" exists.
   //:// GET VIEW vReport NAMED "vReport"
   //:GetViewByName( vReport, "vReport", vSubtask, zLEVEL_TASK )
   GetViewByName( &vReport, "vReport", vSubtask, zLEVEL_TASK );
   //:IF vReport != 0
   if ( vReport != 0 )
   { 
      //:szWindowReportName = "Group: " + vReport.Group.Tag
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vReport, "Group", "Tag", "", 0 );
      ZeidonStringCopy( szWindowReportName, 1, 0, "Group: ", 1, 0, 65 );
      ZeidonStringConcat( szWindowReportName, 1, 0, szTempString_0, 1, 0, 65 );
      //:ELSE
   } 
   else
   { 
      //:szWindowReportName = "Window: " + vDialog.Window.Tag
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
      ZeidonStringCopy( szWindowReportName, 1, 0, "Window: ", 1, 0, 65 );
      ZeidonStringConcat( szWindowReportName, 1, 0, szTempString_1, 1, 0, 65 );
   } 

   //:END

   //://BL, 2000.02.03 new search pfad
   //:SET CURSOR FIRST vPE.ControlDef WHERE
   //:           vPE.ControlDef.Key = vControl.ControlDef.Key
   GetIntegerFromAttribute( &lTempInteger_1, vControl, "ControlDef", "Key" );
   RESULT = SetCursorFirstEntityByInteger( vPE, "ControlDef", "Key", lTempInteger_1, "" );
   //:IF RESULT < zCURSOR_SET
   if ( RESULT < zCURSOR_SET )
   { 
      //:SET CURSOR FIRST vPE.ControlDef WHERE
      //:           vPE.ControlDef.Tag = vControl.ControlDef.Tag
      GetStringFromAttribute( szTempString_2, zsizeof( szTempString_2 ), vControl, "ControlDef", "Tag" );
      RESULT = SetCursorFirstEntityByString( vPE, "ControlDef", "Tag", szTempString_2, "" );
      //:IF RESULT < zCURSOR_SET
      if ( RESULT < zCURSOR_SET )
      { 
         //:SET CURSOR FIRST vPE.ControlDef WHERE
         //:                 vPE.ControlDef.ZKey = vControl.ControlDef.ZKey
         GetIntegerFromAttribute( &lTempInteger_2, vControl, "ControlDef", "ZKey" );
         RESULT = SetCursorFirstEntityByInteger( vPE, "ControlDef", "ZKey", lTempInteger_2, "" );
      } 

      //:END
   } 

   //:END

   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:EXCLUDE vControl.ControlDef
      RESULT = ExcludeEntity( vControl, "ControlDef", zREPOS_AFTER );
      //:INCLUDE vControl.ControlDef FROM vPE.ControlDef
      RESULT = IncludeSubobjectFromSubobject( vControl, "ControlDef", vPE, "ControlDef", zPOS_AFTER );
      //:ELSE
   } 
   else
   { 
      //:szMsg ="ControlDef doesn't exist: " + vControl.ControlDef.Tag
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vControl, "ControlDef", "Tag", "", 0 );
      ZeidonStringCopy( szMsg, 1, 0, "ControlDef doesn't exist: ", 1, 0, 256 );
      ZeidonStringConcat( szMsg, 1, 0, szTempString_2, 1, 0, 256 );
      //:MessageSend( vSubtask, "WD00204", "ControlRelinkDelete",
      //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
      MessageSend( vSubtask, "WD00204", "ControlRelinkDelete", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
   } 

   //:END

   //:/*  For each CtrlMap, check each attribute or entity against the corresponding
   //:    LOD to make sure that attribute or entity exists in the LOD.  If it doesn't,
   //:    delete the CtrlMap.  */
   //:FOR EACH vControl.CtrlMap
   RESULT = SetCursorFirstEntity( vControl, "CtrlMap", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:IF vControl.CtrlMapView EXISTS
      lTempInteger_3 = CheckExistenceOfEntity( vControl, "CtrlMapView" );
      if ( lTempInteger_3 == 0 )
      { 
         //:IF LastViewZKey != vControl.CtrlMapView.ZKey
         if ( CompareAttributeToInteger( vControl, "CtrlMapView", "ZKey", *LastViewZKey ) != 0 )
         { 
            //:SET CURSOR FIRST vDialog.ViewObjRef WHERE
            //:    vDialog.ViewObjRef.ZKey = vControl.CtrlMapView.ZKey
            GetIntegerFromAttribute( &lTempInteger_4, vControl, "CtrlMapView", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( vDialog, "ViewObjRef", "ZKey", lTempInteger_4, "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:nRemapFlag = 0
               nRemapFlag = 0;
               //:ELSE
            } 
            else
            { 
               //:SET CURSOR FIRST vDialog.ViewObjRef WHERE
               //:    vDialog.ViewObjRef.Name = vControl.CtrlMapView.Name
               GetStringFromAttribute( szTempString_3, zsizeof( szTempString_3 ), vControl, "CtrlMapView", "Name" );
               RESULT = SetCursorFirstEntityByString( vDialog, "ViewObjRef", "Name", szTempString_3, "" );
               //:IF RESULT >= zCURSOR_SET
               if ( RESULT >= zCURSOR_SET )
               { 
                  //:// If there was a match on Name but not on Zkey,
                  //:// reinclude the CtrlMapView.
                  //:EXCLUDE vControl.CtrlMapView
                  RESULT = ExcludeEntity( vControl, "CtrlMapView", zREPOS_AFTER );
                  //:INCLUDE vControl.CtrlMapView FROM vDialog.ViewObjRef
                  RESULT = IncludeSubobjectFromSubobject( vControl, "CtrlMapView", vDialog, "ViewObjRef", zPOS_AFTER );
                  //:nRemapFlag = 0
                  nRemapFlag = 0;
                  //:ELSE
               } 
               else
               { 
                  //:nRemapFlag = -1
                  nRemapFlag = -1;
                  //:szMsg = "Deleting Control Mapping for:|   " + szWindowReportName +
                  //:        "|   Control: " + vControl.Control.Tag +
                  //:        "| because of missing View: " + vControl.CtrlMapView.Name
                  ZeidonStringCopy( szMsg, 1, 0, "Deleting Control Mapping for:\n  ", 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, szWindowReportName, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\n  Control: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vControl, "Control", "Tag", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_3, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\nbecause of missing View: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vControl, "CtrlMapView", "Name", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_4, 1, 0, 256 );
                  //:SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen )
                  SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen, zsizeof( szContinueParseGen ) );
                  //:IF szContinueParseGen = "N"
                  if ( ZeidonStringCompare( szContinueParseGen, 1, 0, "N", 1, 0, 2 ) == 0 )
                  { 
                     //:TraceLineS( szMsg, "" )
                     TraceLineS( szMsg, "" );
                     //:ELSE
                  } 
                  else
                  { 
                     //:MessageSend( vSubtask, "WD00506", "Control Relink",
                     //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                     MessageSend( vSubtask, "WD00506", "Control Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                  } 

                  //:END
                  //:DELETE ENTITY vControl.CtrlMap NONE
                  RESULT = DeleteEntity( vControl, "CtrlMap", zREPOS_NONE );
               } 

               //:END
            } 

            //:END
            //:IF nRemapFlag = 0
            if ( nRemapFlag == 0 )
            { 
               //:// There was a match on CtrlMapView ZKey or Name.
               //:// Make sure the corresponding LOD is activated.
               //:IF LastViewZKey != 0
               if ( *LastViewZKey != 0 )
               { 
                  //:DropMetaOI( vSubtask, vLastLOD )
                  DropMetaOI( vSubtask, *vLastLOD );
                  //:LastViewZKey = 0
                  *LastViewZKey = 0;
               } 

               //:END

               //:nRC = ActivateMetaOI_ByZKey( vSubtask, vLastLOD, 0, zREFER_LOD_META,
               //:                             zSINGLE, vDialog.LOD.ZKey, 0 )
               GetIntegerFromAttribute( &lTempInteger_5, vDialog, "LOD", "ZKey" );
               nRC = ActivateMetaOI_ByZKey( vSubtask, vLastLOD, 0, zREFER_LOD_META, zSINGLE, lTempInteger_5, 0 );
               //:IF nRC < 0
               if ( nRC < 0 )
               { 
                  //:nRC = ActivateMetaOI_ByName( vSubtask, vLastLOD, 0, zREFER_LOD_META,
                  //:                             zSINGLE, vDialog.LOD.Name, 0 )
                  GetStringFromAttribute( szTempString_5, zsizeof( szTempString_5 ), vDialog, "LOD", "Name" );
                  nRC = ActivateMetaOI_ByName( vSubtask, vLastLOD, 0, zREFER_LOD_META, zSINGLE, szTempString_5, 0 );
               } 

               //:END

               //:IF nRC < 0
               if ( nRC < 0 )
               { 
                  //:// If we get here, we have a Zeidon error.
                  //:szMsg = "Deleting CtrlMap due to LOD load error.| Registered View Name: " +
                  //:        vDialog.ViewObjRef.Name
                  GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
                  ZeidonStringCopy( szMsg, 1, 0, "Deleting CtrlMap due to LOD load error.\nRegistered View Name: ", 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_6, 1, 0, 256 );
                  //:MessageSend( vSubtask, "WD00507", "Control Relink",
                  //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                  MessageSend( vSubtask, "WD00507", "Control Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                  //:DELETE ENTITY vControl.CtrlMap NONE
                  RESULT = DeleteEntity( vControl, "CtrlMap", zREPOS_NONE );
                  //:ELSE
               } 
               else
               { 
                  //:LastViewZKey = vDialog.ViewObjRef.ZKey
                  GetIntegerFromAttribute( LastViewZKey, vDialog, "ViewObjRef", "ZKey" );
                  //:NAME VIEW vLastLOD "vLastLOD"
                  SetNameForView( *vLastLOD, "vLastLOD", 0, zLEVEL_TASK );
               } 

               //:END
            } 

            //:END
         } 

         //:END

         //://      IF vControl.CtrlMapView EXISTS
         //://         RelinkInstanceToInstance( vControl, "CtrlMapView",
         //://                                   vDialog, "ViewObjRef" )

         //:IF vControl.CtrlMapLOD_Attribute EXISTS
         lTempInteger_6 = CheckExistenceOfEntity( vControl, "CtrlMapLOD_Attribute" );
         if ( lTempInteger_6 == 0 )
         { 
            //:SET CURSOR FIRST vLastLOD.LOD_Attribute WITHIN vLastLOD.LOD WHERE
            //:    vLastLOD.LOD_Attribute.ZKey = vControl.CtrlMapLOD_Attribute.ZKey
            GetIntegerFromAttribute( &lTempInteger_7, vControl, "CtrlMapLOD_Attribute", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( *vLastLOD, "LOD_Attribute", "ZKey", lTempInteger_7, "LOD" );
            //:IF RESULT < 0
            if ( RESULT < 0 )
            { 
               //:// Since there was no match on ZKey, try to find a match on LOD Entity
               //:// name and ER Attribute name, in case the Attribute had been deleted
               //:// and recreated.  In this case, re-include the Attribute.
               //:SET CURSOR FIRST vLastLOD.LOD_Entity WHERE
               //:                 vLastLOD.LOD_Entity.Name = vControl.CtrlMapRelatedEntity.Name
               GetStringFromAttribute( szTempString_7, zsizeof( szTempString_7 ), vControl, "CtrlMapRelatedEntity", "Name" );
               RESULT = SetCursorFirstEntityByString( *vLastLOD, "LOD_Entity", "Name", szTempString_7, "" );
               //:IF RESULT >= zCURSOR_SET
               if ( RESULT >= zCURSOR_SET )
               { 
                  //:SET CURSOR FIRST vLastLOD.ER_Attribute WITHIN vLastLOD.LOD_Entity WHERE
                  //:                 vLastLOD.ER_Attribute.Name = vControl.CtrlMapER_Attribute.Name
                  GetStringFromAttribute( szTempString_7, zsizeof( szTempString_7 ), vControl, "CtrlMapER_Attribute", "Name" );
                  RESULT = SetCursorFirstEntityByString( *vLastLOD, "ER_Attribute", "Name", szTempString_7, "LOD_Entity" );
                  //:IF RESULT >= zCURSOR_SET     //
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:nRemapFlag = 0
                     nRemapFlag = 0;
                     //:ELSE
                  } 
                  else
                  { 
                     //:nRemapFlag = -1
                     nRemapFlag = -1;
                  } 

                  //:END
                  //:ELSE
               } 
               else
               { 
                  //:nRemapFlag = -1
                  nRemapFlag = -1;
               } 

               //:END
               //:IF nRemapFlag = 0  // We were able to remap to an attribute by same name.
               if ( nRemapFlag == 0 )
               { 
                  //:EXCLUDE vControl.CtrlMapLOD_Attribute
                  RESULT = ExcludeEntity( vControl, "CtrlMapLOD_Attribute", zREPOS_AFTER );
                  //:INCLUDE vControl.CtrlMapLOD_Attribute FROM vLastLOD.LOD_Attribute
                  RESULT = IncludeSubobjectFromSubobject( vControl, "CtrlMapLOD_Attribute", *vLastLOD, "LOD_Attribute", zPOS_AFTER );
                  //:ELSE
               } 
               else
               { 
                  //:szMsg = "Deleting Control Mapping for:|   " + szWindowReportName +
                  //:        "|   Control: " + vControl.Control.Tag +
                  //:        "|   because of missing Attribute: " + vControl.CtrlMapER_Attribute.Name +
                  //:        "|   in LOD: " + vControl.CtrlMapView.Name
                  ZeidonStringCopy( szMsg, 1, 0, "Deleting Control Mapping for:\n  ", 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, szWindowReportName, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\n  Control: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vControl, "Control", "Tag", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_7, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\n  because of missing Attribute: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vControl, "CtrlMapER_Attribute", "Name", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_8, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\n  in LOD: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vControl, "CtrlMapView", "Name", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_9, 1, 0, 256 );
                  //:IF vControl.CtrlMapLOD_Entity EXISTS
                  lTempInteger_8 = CheckExistenceOfEntity( vControl, "CtrlMapLOD_Entity" );
                  if ( lTempInteger_8 == 0 )
                  { 
                     //:szMsg = szMsg + "|   in Entity: " + vControl.CtrlMapLOD_Entity.Name
                     ZeidonStringConcat( szMsg, 1, 0, "\n  in Entity: ", 1, 0, 256 );
                     GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vControl, "CtrlMapLOD_Entity", "Name", "", 0 );
                     ZeidonStringConcat( szMsg, 1, 0, szTempString_10, 1, 0, 256 );
                     //:ELSE
                  } 
                  else
                  { 
                     //:IF vControl.CtrlMapRelatedEntity EXISTS
                     lTempInteger_9 = CheckExistenceOfEntity( vControl, "CtrlMapRelatedEntity" );
                     if ( lTempInteger_9 == 0 )
                     { 
                        //:szMsg = szMsg + "|   in Entity: " + vControl.CtrlMapRelatedEntity.Name
                        ZeidonStringConcat( szMsg, 1, 0, "\n  in Entity: ", 1, 0, 256 );
                        GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vControl, "CtrlMapRelatedEntity", "Name", "", 0 );
                        ZeidonStringConcat( szMsg, 1, 0, szTempString_11, 1, 0, 256 );
                     } 

                     //:END
                  } 

                  //:END
                  //:SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen )
                  SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen, zsizeof( szContinueParseGen ) );
                  //:IF szContinueParseGen = "N"
                  if ( ZeidonStringCompare( szContinueParseGen, 1, 0, "N", 1, 0, 2 ) == 0 )
                  { 
                     //:TraceLineS( szMsg, "" )
                     TraceLineS( szMsg, "" );
                     //:ELSE
                  } 
                  else
                  { 
                     //:MessageSend( vSubtask, "WD00508", "Control Relink",
                     //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                     MessageSend( vSubtask, "WD00508", "Control Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                  } 

                  //:END
                  //:IF vControl.CtrlMapLOD_Attribute EXISTS
                  lTempInteger_10 = CheckExistenceOfEntity( vControl, "CtrlMapLOD_Attribute" );
                  if ( lTempInteger_10 == 0 )
                  { 
                     //:EXCLUDE vControl.CtrlMapLOD_Attribute
                     RESULT = ExcludeEntity( vControl, "CtrlMapLOD_Attribute", zREPOS_AFTER );
                  } 

                  //:END
                  //:IF vControl.CtrlMapLOD_Entity EXISTS
                  lTempInteger_11 = CheckExistenceOfEntity( vControl, "CtrlMapLOD_Entity" );
                  if ( lTempInteger_11 == 0 )
                  { 
                     //:EXCLUDE vControl.CtrlMapLOD_Entity
                     RESULT = ExcludeEntity( vControl, "CtrlMapLOD_Entity", zREPOS_AFTER );
                  } 

                  //:END
                  //:IF vControl.CtrlMapContext EXISTS
                  lTempInteger_12 = CheckExistenceOfEntity( vControl, "CtrlMapContext" );
                  if ( lTempInteger_12 == 0 )
                  { 
                     //:EXCLUDE vControl.CtrlMapContext
                     RESULT = ExcludeEntity( vControl, "CtrlMapContext", zREPOS_AFTER );
                  } 

                  //:END
                  //:IF vControl.CtrlMapView EXISTS
                  lTempInteger_13 = CheckExistenceOfEntity( vControl, "CtrlMapView" );
                  if ( lTempInteger_13 == 0 )
                  { 
                     //:EXCLUDE vControl.CtrlMapView
                     RESULT = ExcludeEntity( vControl, "CtrlMapView", zREPOS_AFTER );
                  } 

                  //:END
               } 

               //:END
               //:ELSE
            } 
            else
            { 
               //:// Relink or Re-Include CtrlMapLOD_Attribute, & subordinates & Context
               //://RelinkInstanceToInstance( vControl, "CtrlMapLOD_Attribute", vLastLOD, "LOD_Attribute" )
               //://RelinkInstanceToInstance( vControl, "CtrlMapRelatedEntity", vLastLOD, "LOD_Entity" )
               //://RelinkInstanceToInstance( vControl, "CtrlMapER_Attribute", vLastLOD, "ER_Attribute" )
               //://RelinkInstanceToInstance( vControl, "CtrlMapER_Domain", vLastLOD, "Domain" )

               //:// If ER_Attribute or ER_Domain don't match on ZKey,
               //:// reinclude the LOD_Attribute entity.
               //:IF vControl.CtrlMapER_Attribute.ZKey  != vLastLOD.ER_Attribute.ZKey OR
               //:   vControl.CtrlMapER_Domain.ZKey     != vLastLOD.Domain.ZKey
               if ( CompareAttributeToAttribute( vControl, "CtrlMapER_Attribute", "ZKey", *vLastLOD, "ER_Attribute", "ZKey" ) != 0 || CompareAttributeToAttribute( vControl, "CtrlMapER_Domain", "ZKey", *vLastLOD, "Domain", "ZKey" ) != 0 )
               { 

                  //:EXCLUDE vControl.CtrlMapLOD_Attribute
                  RESULT = ExcludeEntity( vControl, "CtrlMapLOD_Attribute", zREPOS_AFTER );
                  //:INCLUDE vControl.CtrlMapLOD_Attribute FROM vLastLOD.LOD_Attribute
                  RESULT = IncludeSubobjectFromSubobject( vControl, "CtrlMapLOD_Attribute", *vLastLOD, "LOD_Attribute", zPOS_AFTER );
               } 

               //:END

               //:IF vControl.CtrlMapContext EXISTS
               lTempInteger_14 = CheckExistenceOfEntity( vControl, "CtrlMapContext" );
               if ( lTempInteger_14 == 0 )
               { 
                  //:// Try to find the Domain first by ZKey and then by name.
                  //:// If found, also find the Context by ZKey and then by name.
                  //:// If no match was finally found, exclude the Context.
                  //:nRC = ActivateMetaOI_ByZKey( vSubtask, vDomain, 0, zREFER_DOMAIN_META,
                  //:                             zSINGLE, vControl.CtrlMapER_Domain.ZKey , 0 )
                  GetIntegerFromAttribute( &lTempInteger_15, vControl, "CtrlMapER_Domain", "ZKey" );
                  nRC = ActivateMetaOI_ByZKey( vSubtask, &vDomain, 0, zREFER_DOMAIN_META, zSINGLE, lTempInteger_15, 0 );
                  //:IF nRC >= 0
                  if ( nRC >= 0 )
                  { 
                     //:SET CURSOR FIRST vDomain.Context WHERE
                     //:    vDomain.Context.ZKey = vControl.CtrlMapContext.ZKey
                     GetIntegerFromAttribute( &lTempInteger_16, vControl, "CtrlMapContext", "ZKey" );
                     RESULT = SetCursorFirstEntityByInteger( vDomain, "Context", "ZKey", lTempInteger_16, "" );
                     //:IF RESULT >= zCURSOR_SET
                     if ( RESULT >= zCURSOR_SET )
                     { 
                        //:nRemapFlag = 0
                        nRemapFlag = 0;
                        //:ELSE
                     } 
                     else
                     { 
                        //:SET CURSOR FIRST vDomain.Context WHERE
                        //:    vDomain.Context.Name = vControl.CtrlMapContext.Name
                        GetStringFromAttribute( szTempString_12, zsizeof( szTempString_12 ), vControl, "CtrlMapContext", "Name" );
                        RESULT = SetCursorFirstEntityByString( vDomain, "Context", "Name", szTempString_12, "" );
                        //:IF RESULT >= zCURSOR_SET
                        if ( RESULT >= zCURSOR_SET )
                        { 
                           //:nRemapFlag = 1
                           nRemapFlag = 1;
                           //:EXCLUDE vControl.CtrlMapContext
                           RESULT = ExcludeEntity( vControl, "CtrlMapContext", zREPOS_AFTER );
                           //:INCLUDE vControl.CtrlMapContext FROM vDomain.Context
                           RESULT = IncludeSubobjectFromSubobject( vControl, "CtrlMapContext", vDomain, "Context", zPOS_AFTER );
                           //:ELSE
                        } 
                        else
                        { 
                           //:nRemapFlag = -1
                           nRemapFlag = -1;
                        } 

                        //:END
                     } 

                     //:END
                     //:ELSE
                  } 
                  else
                  { 
                     //:nRC = ActivateMetaOI_ByName( vSubtask, vDomain, 0, zREFER_DOMAIN_META,
                     //:                             zSINGLE, vControl.CtrlMapER_Domain.Name , 0 )
                     GetStringFromAttribute( szTempString_12, zsizeof( szTempString_12 ), vControl, "CtrlMapER_Domain", "Name" );
                     nRC = ActivateMetaOI_ByName( vSubtask, &vDomain, 0, zREFER_DOMAIN_META, zSINGLE, szTempString_12, 0 );
                     //:IF nRC >= 0
                     if ( nRC >= 0 )
                     { 
                        //:SET CURSOR FIRST vDomain.Context WHERE
                        //:    vDomain.Context.Name = vControl.CtrlMapContext.Name
                        GetStringFromAttribute( szTempString_13, zsizeof( szTempString_13 ), vControl, "CtrlMapContext", "Name" );
                        RESULT = SetCursorFirstEntityByString( vDomain, "Context", "Name", szTempString_13, "" );
                        //:IF RESULT >= zCURSOR_SET
                        if ( RESULT >= zCURSOR_SET )
                        { 
                           //:nRemapFlag = 1
                           nRemapFlag = 1;
                           //:EXCLUDE vControl.CtrlMapContext
                           RESULT = ExcludeEntity( vControl, "CtrlMapContext", zREPOS_AFTER );
                           //:INCLUDE vControl.CtrlMapContext FROM vDomain.Context
                           RESULT = IncludeSubobjectFromSubobject( vControl, "CtrlMapContext", vDomain, "Context", zPOS_AFTER );
                           //:ELSE
                        } 
                        else
                        { 
                           //:nRemapFlag = -1
                           nRemapFlag = -1;
                        } 

                        //:END
                        //:ELSE
                     } 
                     else
                     { 
                        //:nRemapFlag = -1
                        nRemapFlag = -1;
                     } 

                     //:END
                  } 

                  //:END
                  //:IF nRemapFlag = -1
                  if ( nRemapFlag == -1 )
                  { 
                     //:szMsg = "Excluding Context for:|   " + szWindowReportName +
                     //:        "|   Control: " + vControl.Control.Tag +
                     //:        "| because of missing Context: " + vControl.CtrlMapContext.Name
                     ZeidonStringCopy( szMsg, 1, 0, "Excluding Context for:\n  ", 1, 0, 256 );
                     ZeidonStringConcat( szMsg, 1, 0, szWindowReportName, 1, 0, 256 );
                     ZeidonStringConcat( szMsg, 1, 0, "\n  Control: ", 1, 0, 256 );
                     GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vControl, "Control", "Tag", "", 0 );
                     ZeidonStringConcat( szMsg, 1, 0, szTempString_13, 1, 0, 256 );
                     ZeidonStringConcat( szMsg, 1, 0, "\nbecause of missing Context: ", 1, 0, 256 );
                     GetVariableFromAttribute( szTempString_14, 0, 'S', 33, vControl, "CtrlMapContext", "Name", "", 0 );
                     ZeidonStringConcat( szMsg, 1, 0, szTempString_14, 1, 0, 256 );
                     //:MessageSend( vSubtask, "WD00509", "Control Relink",
                     //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                     MessageSend( vSubtask, "WD00509", "Control Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                     //:EXCLUDE vControl.CtrlMapContext NONE
                     RESULT = ExcludeEntity( vControl, "CtrlMapContext", zREPOS_NONE );
                     //:ELSE
                  } 
                  else
                  { 
                     //:IF nRemapFlag = 0
                     if ( nRemapFlag == 0 )
                     { 
                        //:RelinkInstanceToInstance( vControl, "CtrlMapContext",
                        //:                          vDomain, "Context" )
                        RelinkInstanceToInstance( vControl, "CtrlMapContext", vDomain, "Context" );
                     } 

                     //:END
                     //:DropMetaOI( vSubtask, vDomain )
                     DropMetaOI( vSubtask, vDomain );
                  } 

                  //:END
               } 

               //:END
            } 

            //:END
         } 

         //:END

         //:IF vControl.CtrlMapLOD_Entity EXISTS
         lTempInteger_17 = CheckExistenceOfEntity( vControl, "CtrlMapLOD_Entity" );
         if ( lTempInteger_17 == 0 )
         { 
            //:SET CURSOR FIRST vLastLOD.LOD_Entity WHERE
            //:    vLastLOD.LOD_Entity.ZKey = vControl.CtrlMapLOD_Entity.ZKey
            GetIntegerFromAttribute( &lTempInteger_18, vControl, "CtrlMapLOD_Entity", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( *vLastLOD, "LOD_Entity", "ZKey", lTempInteger_18, "" );
            //:IF RESULT < 0
            if ( RESULT < 0 )
            { 
               //:// Since there was no match on ZKey, try again on name in case the
               //:// LOD_Entity had been deleted and readded.
               //:SET CURSOR FIRST vLastLOD.LOD_Entity WHERE
               //:    vLastLOD.LOD_Entity.Name = vControl.CtrlMapLOD_Entity.Name
               GetStringFromAttribute( szTempString_15, zsizeof( szTempString_15 ), vControl, "CtrlMapLOD_Entity", "Name" );
               RESULT = SetCursorFirstEntityByString( *vLastLOD, "LOD_Entity", "Name", szTempString_15, "" );
               //:IF RESULT >= zCURSOR_SET
               if ( RESULT >= zCURSOR_SET )
               { 
                  //:EXCLUDE vControl.CtrlMapLOD_Entity
                  RESULT = ExcludeEntity( vControl, "CtrlMapLOD_Entity", zREPOS_AFTER );
                  //:INCLUDE vControl.CtrlMapLOD_Entity FROM vLastLOD.LOD_Entity
                  RESULT = IncludeSubobjectFromSubobject( vControl, "CtrlMapLOD_Entity", *vLastLOD, "LOD_Entity", zPOS_AFTER );
                  //:ELSE
               } 
               else
               { 
                  //:szMsg = "Deleting Control Mapping for:|   " + szWindowReportName +
                  //:        "|   Control: " + vControl.Control.Tag +
                  //:        "| because of missing Entity: " + vControl.CtrlMapLOD_Entity.Name +
                  //:        "|   in LOD: " + vControl.CtrlMapView.Name
                  ZeidonStringCopy( szMsg, 1, 0, "Deleting Control Mapping for:\n  ", 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, szWindowReportName, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\n  Control: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_15, 0, 'S', 33, vControl, "Control", "Tag", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_15, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\nbecause of missing Entity: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_16, 0, 'S', 33, vControl, "CtrlMapLOD_Entity", "Name", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_16, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\n  in LOD: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_17, 0, 'S', 33, vControl, "CtrlMapView", "Name", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_17, 1, 0, 256 );
                  //:SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen )
                  SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen, zsizeof( szContinueParseGen ) );
                  //:IF szContinueParseGen = "N"
                  if ( ZeidonStringCompare( szContinueParseGen, 1, 0, "N", 1, 0, 2 ) == 0 )
                  { 
                     //:TraceLineS( szMsg, "" )
                     TraceLineS( szMsg, "" );
                     //:ELSE
                  } 
                  else
                  { 
                     //:MessageSend( vSubtask, "WD00510", "Control Relink",
                     //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                     MessageSend( vSubtask, "WD00510", "Control Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                  } 

                  //:END
                  //:DELETE ENTITY vControl.CtrlMap NONE
                  RESULT = DeleteEntity( vControl, "CtrlMap", zREPOS_NONE );
               } 

               //:END
               //:ELSE
            } 
            else
            { 
               //:// Relink CtrlMapLOD_Entity
               //:RelinkInstanceToInstance( vControl, "CtrlMapLOD_Entity",
               //:                          vLastLOD, "LOD_Entity" )
               RelinkInstanceToInstance( vControl, "CtrlMapLOD_Entity", *vLastLOD, "LOD_Entity" );
            } 

            //:END
         } 

         //:END
      } 

      RESULT = SetCursorNextEntity( vControl, "CtrlMap", "" );

      //:END
   } 

   //:END
   return( 0 );
// END
} 


//:DERIVED ATTRIBUTE OPERATION
//:NLS_ControlText( VIEW        vDialog BASED ON LOD TZWDLGSO,
//:                 STRING (32) lpEntity,
//:                 STRING (32) lpAttribute,
//:                 SHORT       GetOrSetFlag )
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_NLS_ControlText( zVIEW     vDialog,
                           LPVIEWENTITY lpEntity,
                           LPVIEWATTRIB lpAttribute,
                           zSHORT    GetOrSetFlag )
{

   return( 0 );
//    /*SHORT        nLanguageCode
//    STRING (254) szControl
//    SysGetLanguageCode ( nLanguageCode )
//    CASE GetOrSetFlag
//    OF   zDERIVED_GET:
//       // Determine Control text to use by checking the NLS Language Code for a match on
//       // a ControlNLS_Text entity.  If there is a match, use it.  Otherwise, use the Control.Text
//       // attribute.
//       SET CURSOR FIRST vDialog.ControlNLS_Text WHERE
//                        vDialog.ControlNLS_Text.LanguageIndex = nLanguageCode
//       IF RESULT >= zCURSOR_SET
//          szControl = vDialog.ControlNLS_Text.Text
//       ELSE
//          szControl = vDialog.Control.Text
//       END
//       StoreStringInRecord ( vDialog, lpEntity, lpAttribute, szControl )
//         // end zDERIVED_GET
//    OF   zDERIVED_SET:
//       // As for zDERIVED_GET above, use the Language Code to store the data entered into
//       // the derived attribute into the correct attribute.
//       // If there is ControlNLS_Text entity that matches the Language Code, then set the data there.
//       // If not, set it into the Window.Control attribute.
//       GetStringFromRecord ( vDialog, lpEntity, lpAttribute, szControl, 254 )
//       SET CURSOR FIRST vDialog.ControlNLS_Text WHERE
//                        vDialog.ControlNLS_Text.LanguageIndex = nLanguageCode
//       IF RESULT >= zCURSOR_SET
//          vDialog.ControlNLS_Text.Text = szControl
//       ELSE
//          vDialog.Control.Text = szControl
//       END
//         // end zDERIVED_SET
//    END  // case */
// END
} 


//:DERIVED ATTRIBUTE OPERATION
//:NLS_ControlDIL_Text( VIEW        vDialog BASED ON LOD TZWDLGSO,
//:                     STRING (32) lpEntity,
//:                     STRING (32) lpAttribute,
//:                     SHORT       GetOrSetFlag )

//:   SHORT        nLanguageCode
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_NLS_ControlDIL_Text( zVIEW     vDialog,
                               LPVIEWENTITY lpEntity,
                               LPVIEWATTRIB lpAttribute,
                               zSHORT    GetOrSetFlag )
{
   zSHORT    nLanguageCode = 0; 
   //:STRING (254) szDIL
   zCHAR     szDIL[ 255 ] = { 0 }; 
   zSHORT    RESULT; 


   //:SysGetLanguageCode ( nLanguageCode )
   SysGetLanguageCode( &nLanguageCode );

   //:CASE GetOrSetFlag
   switch( GetOrSetFlag )
   { 
      //:OF   zDERIVED_GET:
      case zDERIVED_GET :
         //:// Determine Control.NLS_DIL_Text to use by checking the NLS Language Code for a match on
         //:// a ControlNLS_DIL_Text entity.  If there is a match, use it.  Otherwise, use the
         //:// Control.DIL_Text attribute.

         //:SET CURSOR FIRST vDialog.ControlNLS_DIL_Text WHERE
         //:              vDialog.ControlNLS_DIL_Text.LanguageIndex = nLanguageCode
         RESULT = SetCursorFirstEntityByInteger( vDialog, "ControlNLS_DIL_Text", "LanguageIndex", nLanguageCode, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szDIL = vDialog.ControlNLS_DIL_Text.Text
            GetVariableFromAttribute( szDIL, 0, 'S', 255, vDialog, "ControlNLS_DIL_Text", "Text", "", 0 );
            //:ELSE
         } 
         else
         { 
            //:szDIL = vDialog.Control.DIL_Text
            GetVariableFromAttribute( szDIL, 0, 'S', 255, vDialog, "Control", "DIL_Text", "", 0 );
         } 

         //:END

         //:StoreStringInRecord ( vDialog, lpEntity, lpAttribute, szDIL )
         StoreStringInRecord( vDialog, lpEntity, lpAttribute, szDIL );
         break ;

      //:  /* end zDERIVED_GET */
      //:OF   zDERIVED_SET:
      case zDERIVED_SET :

         //:// As for zDERIVED_GET above, use the Language Code to store the data entered into
         //:// the derived attribute into the correct attribute.
         //:// If there is ControlNLS_DIL_Text entity that matches the Language Code, then set the
         //:// data there.  If not, set it into the Window.Control attribute.

         //:GetStringFromRecord ( vDialog, lpEntity, lpAttribute, szDIL, 254 )
         GetStringFromRecord( vDialog, lpEntity, lpAttribute, szDIL, 254 );

         //:SET CURSOR FIRST vDialog.ControlNLS_DIL_Text WHERE
         //:              vDialog.ControlNLS_DIL_Text.LanguageIndex = nLanguageCode
         RESULT = SetCursorFirstEntityByInteger( vDialog, "ControlNLS_DIL_Text", "LanguageIndex", nLanguageCode, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:vDialog.ControlNLS_DIL_Text.Text = szDIL
            SetAttributeFromString( vDialog, "ControlNLS_DIL_Text", "Text", szDIL );
            //:ELSE
         } 
         else
         { 
            //:vDialog.Control.DIL_Text = szDIL
            SetAttributeFromString( vDialog, "Control", "DIL_Text", szDIL );
         } 

         //:END
         break ;
   } 


   //:     /* end zDERIVED_SET */
   //:END  /* case */
   return( 0 );
// END
} 


//:DERIVED ATTRIBUTE OPERATION
//:NLS_CaptionText( VIEW        vDialog BASED ON LOD TZWDLGSO,
//:                 STRING (32) lpEntity,
//:                 STRING (32) lpAttribute,
//:                 SHORT       GetOrSetFlag )

//:   SHORT        nLanguageCode
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_NLS_CaptionText( zVIEW     vDialog,
                           LPVIEWENTITY lpEntity,
                           LPVIEWATTRIB lpAttribute,
                           zSHORT    GetOrSetFlag )
{
   zSHORT    nLanguageCode = 0; 
   //:STRING (255) szCaption
   zCHAR     szCaption[ 256 ] = { 0 }; 
   zSHORT    RESULT; 


   //:SysGetLanguageCode ( nLanguageCode )
   SysGetLanguageCode( &nLanguageCode );

   //:CASE GetOrSetFlag
   switch( GetOrSetFlag )
   { 
      //:OF   zDERIVED_GET:
      case zDERIVED_GET :

         //:// Determine Caption text to use by checking the NLS Language Code for a match on
         //:// a CaptionNLS_Text entity.  If there is a match, use it.  Otherwise, use the Window.Caption
         //:// attribute.

         //:SET CURSOR FIRST vDialog.CaptionNLS_Text WHERE
         //:              vDialog.CaptionNLS_Text.LanguageIndex = nLanguageCode
         RESULT = SetCursorFirstEntityByInteger( vDialog, "CaptionNLS_Text", "LanguageIndex", nLanguageCode, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szCaption = vDialog.CaptionNLS_Text.Text
            GetVariableFromAttribute( szCaption, 0, 'S', 256, vDialog, "CaptionNLS_Text", "Text", "", 0 );
            //:ELSE
         } 
         else
         { 
            //:szCaption = vDialog.Window.Caption
            GetVariableFromAttribute( szCaption, 0, 'S', 256, vDialog, "Window", "Caption", "", 0 );
         } 

         //:END

         //:StoreStringInRecord ( vDialog, lpEntity, lpAttribute, szCaption )
         StoreStringInRecord( vDialog, lpEntity, lpAttribute, szCaption );
         break ;

      //:  /* end zDERIVED_GET */
      //:OF   zDERIVED_SET:
      case zDERIVED_SET :

         //:// As for zDERIVED_GET above, use the Language Code to store the data entered into
         //:// the derived attribute into the correct attribute.
         //:// If there is CaptionNLS_Text entity that matches the Language Code, then set the data there.
         //:// If not, set it into the Window.Caption attribute.

         //:GetStringFromRecord ( vDialog, lpEntity, lpAttribute, szCaption, 254 )
         GetStringFromRecord( vDialog, lpEntity, lpAttribute, szCaption, 254 );

         //:SET CURSOR FIRST vDialog.CaptionNLS_Text WHERE
         //:              vDialog.CaptionNLS_Text.LanguageIndex = nLanguageCode
         RESULT = SetCursorFirstEntityByInteger( vDialog, "CaptionNLS_Text", "LanguageIndex", nLanguageCode, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:vDialog.CaptionNLS_Text.Text = szCaption
            SetAttributeFromString( vDialog, "CaptionNLS_Text", "Text", szCaption );
            //:ELSE
         } 
         else
         { 
            //:vDialog.Window.Caption = szCaption
            SetAttributeFromString( vDialog, "Window", "Caption", szCaption );
         } 

         //:END
         break ;
   } 


   //:     /* end zDERIVED_SET */
   //:END  /* case */
   return( 0 );
// END
} 


//:TRANSFORMATION OPERATION
//:DialogRelinkDelete( VIEW vDialog BASED ON LOD TZWDLGSO, VIEW vSubtask )

//:   VIEW         vLastLOD     BASED ON LOD TZZOLODO
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_DialogRelinkDelete( zVIEW     vDialog,
                              zVIEW     vSubtask )
{
   zVIEW     vLastLOD = 0; 
   //:VIEW         vVOR         BASED ON LOD TZWDVORO
   zVIEW     vVOR = 0; 
   //:VIEW         vLOD_LPLR    BASED ON LOD TZCMLPLO
   zVIEW     vLOD_LPLR = 0; 
   //:VIEW         vRecursive   BASED ON LOD TZWDLGSO
   zVIEW     vRecursive = 0; 
   //:INTEGER      LastViewZKey
   zLONG     LastViewZKey = 0; 
   //:STRING (255) szMsg
   zCHAR     szMsg[ 256 ] = { 0 }; 
   //:STRING ( 1 ) szContinueParseGen
   zCHAR     szContinueParseGen[ 2 ] = { 0 }; 
   //:SHORT  nRC
   zSHORT    nRC = 0; 
   zSHORT    RESULT; 
   zLONG     lTempInteger_0; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zSHORT    lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zCHAR     szTempString_5[ 33 ]; 
   zLONG     lTempInteger_3; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zLONG     lTempInteger_4; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zSHORT    lTempInteger_5; 
   zLONG     lTempInteger_6; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 


   //:RetrieveViewForMetaList( vSubtask, vLOD_LPLR, zREFER_LOD_META )
   RetrieveViewForMetaList( vSubtask, &vLOD_LPLR, zREFER_LOD_META );
   //:LastViewZKey = 0
   LastViewZKey = 0;
   //:NAME VIEW vDialog "vDialog"
   SetNameForView( vDialog, "vDialog", 0, zLEVEL_TASK );

   //:FOR EACH vDialog.ViewObjRef
   RESULT = SetCursorFirstEntity( vDialog, "ViewObjRef", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:IF LastViewZKey != 0
      if ( LastViewZKey != 0 )
      { 
         //:DropMetaOI( vSubtask, vLastLOD )
         DropMetaOI( vSubtask, vLastLOD );
         //:LastViewZKey = 0
         LastViewZKey = 0;
      } 

      //:END

      //:nRC = ActivateMetaOI_ByZKey( vSubtask, vVOR, 0, zREFER_VOR_META,
      //:                             zSINGLE, vDialog.ViewObjRef.ZKey, 0 )
      GetIntegerFromAttribute( &lTempInteger_0, vDialog, "ViewObjRef", "ZKey" );
      nRC = ActivateMetaOI_ByZKey( vSubtask, &vVOR, 0, zREFER_VOR_META, zSINGLE, lTempInteger_0, 0 );
      //:IF nRC >= 0
      if ( nRC >= 0 )
      { 
         //:nRC = ActivateMetaOI_ByName( vSubtask, vLastLOD, 0, zREFER_LOD_META,
         //:                             zSINGLE, vVOR.LOD.Name, 0 )
         GetStringFromAttribute( szTempString_0, zsizeof( szTempString_0 ), vVOR, "LOD", "Name" );
         nRC = ActivateMetaOI_ByName( vSubtask, &vLastLOD, 0, zREFER_LOD_META, zSINGLE, szTempString_0, 0 );
         //:IF nRC >= 0
         if ( nRC >= 0 )
         { 
            //:LastViewZKey = vDialog.ViewObjRef.ZKey
            GetIntegerFromAttribute( &LastViewZKey, vDialog, "ViewObjRef", "ZKey" );
            //:NAME VIEW vLastLOD "vLastLOD"
            SetNameForView( vLastLOD, "vLastLOD", 0, zLEVEL_TASK );
            //:// Relink ViewObjRef & LOD
            //://RelinkInstanceToInstance( vDialog, "ViewObjRef", vVOR, "ViewObjRef" )
            //://RelinkInstanceToInstance( vDialog, "LOD", vLastLOD, "LOD" )

            //:// Since RelinkInstanceToInstance does not reset the include flags,
            //:// use RelinkAllSubobjectsForOI for relinking entities that need those include
            //:// flags reset.  When a version of RelinkInstanceToInstance is created
            //:// that resets those flags, the following code can be removed.
            //:RelinkAllSubobjectsForOI( vDialog, "ViewObjRef", vVOR, "ViewObjRef" )
            RelinkAllSubobjectsForOI( vDialog, "ViewObjRef", vVOR, "ViewObjRef" );
            //:RelinkAllSubobjectsForOI( vDialog, "CtrlMapLOD_Attribute", vLastLOD, "LOD_Attribute" )
            RelinkAllSubobjectsForOI( vDialog, "CtrlMapLOD_Attribute", vLastLOD, "LOD_Attribute" );
            //:RelinkAllSubobjectsForOI( vDialog, "OptMapLOD_Attribute", vLastLOD, "LOD_Attribute" )
            RelinkAllSubobjectsForOI( vDialog, "OptMapLOD_Attribute", vLastLOD, "LOD_Attribute" );
            //:RelinkAllSubobjectsForOI( vDialog, "ActMapLOD_Entity", vLastLOD, "LOD_Entity" )
            RelinkAllSubobjectsForOI( vDialog, "ActMapLOD_Entity", vLastLOD, "LOD_Entity" );
            //:ELSE
         } 
         else
         { 
            //:szMsg = "Deleting Dialog View: " + vDialog.ViewObjRef.Name +
            //:        "| Missing LOD: " + vDialog.LOD.Name
            GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
            ZeidonStringCopy( szMsg, 1, 0, "Deleting Dialog View: ", 1, 0, 256 );
            ZeidonStringConcat( szMsg, 1, 0, szTempString_1, 1, 0, 256 );
            ZeidonStringConcat( szMsg, 1, 0, "\nMissing LOD: ", 1, 0, 256 );
            GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "LOD", "Name", "", 0 );
            ZeidonStringConcat( szMsg, 1, 0, szTempString_2, 1, 0, 256 );
            //:SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen )
            SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen, zsizeof( szContinueParseGen ) );
            //:IF szContinueParseGen = "N"
            if ( ZeidonStringCompare( szContinueParseGen, 1, 0, "N", 1, 0, 2 ) == 0 )
            { 
               //:TraceLineS( szMsg, "" )
               TraceLineS( szMsg, "" );
               //:ELSE
            } 
            else
            { 
               //:MessageSend( vSubtask, "WD00501", "Dialog Relink",
               //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
               MessageSend( vSubtask, "WD00501", "Dialog Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
            } 

            //:END
            //:EXCLUDE vDialog.ViewObjRef NONE
            RESULT = ExcludeEntity( vDialog, "ViewObjRef", zREPOS_NONE );
         } 

         //:END
         //:DropMetaOI( vSubtask, vVOR )
         DropMetaOI( vSubtask, vVOR );
         //:ELSE
      } 
      else
      { 
         //:nRC = ActivateMetaOI_ByName( vSubtask, vVOR, 0, zREFER_VOR_META,
         //:                             zSINGLE, vDialog.ViewObjRef.Name , 0 )
         GetStringFromAttribute( szTempString_3, zsizeof( szTempString_3 ), vDialog, "ViewObjRef", "Name" );
         nRC = ActivateMetaOI_ByName( vSubtask, &vVOR, 0, zREFER_VOR_META, zSINGLE, szTempString_3, 0 );
         //:IF nRC >= 0
         if ( nRC >= 0 )
         { 
            //:EXCLUDE vDialog.ViewObjRef NONE
            RESULT = ExcludeEntity( vDialog, "ViewObjRef", zREPOS_NONE );
            //:INCLUDE vDialog.ViewObjRef FROM vVOR.ViewObjRef
            RESULT = IncludeSubobjectFromSubobject( vDialog, "ViewObjRef", vVOR, "ViewObjRef", zPOS_AFTER );
            //:DropMetaOI( vSubtask, vVOR )
            DropMetaOI( vSubtask, vVOR );
            //:ELSE
         } 
         else
         { 
            //:szMsg = "Deleting Dialog View: " + vDialog.ViewObjRef.Name +
            //:        "| Missing Registered View."
            GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
            ZeidonStringCopy( szMsg, 1, 0, "Deleting Dialog View: ", 1, 0, 256 );
            ZeidonStringConcat( szMsg, 1, 0, szTempString_4, 1, 0, 256 );
            ZeidonStringConcat( szMsg, 1, 0, "\nMissing Registered View.", 1, 0, 256 );
            //:SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen )
            SysReadZeidonIni( -1, "[Workstation]", "ContinueParseGen", szContinueParseGen, zsizeof( szContinueParseGen ) );
            //:IF szContinueParseGen = "N"
            if ( ZeidonStringCompare( szContinueParseGen, 1, 0, "N", 1, 0, 2 ) == 0 )
            { 
               //:TraceLineS( szMsg, "" )
               TraceLineS( szMsg, "" );
               //:ELSE
            } 
            else
            { 
               //:MessageSend( vSubtask, "WD00502", "Dialog Relink",
               //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
               MessageSend( vSubtask, "WD00502", "Dialog Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
            } 

            //:END
            //:EXCLUDE vDialog.ViewObjRef NONE
            RESULT = ExcludeEntity( vDialog, "ViewObjRef", zREPOS_NONE );
         } 

         //:END
      } 

      RESULT = SetCursorNextEntity( vDialog, "ViewObjRef", "" );
      //:END
   } 

   //:END

   //:FOR EACH vDialog.Window
   RESULT = SetCursorFirstEntity( vDialog, "Window", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:CreateViewFromViewForTask( vRecursive, vDialog, 0 )
      CreateViewFromViewForTask( &vRecursive, vDialog, 0 );
      //:NAME VIEW vRecursive "vRecursive"
      SetNameForView( vRecursive, "vRecursive", 0, zLEVEL_TASK );
      //:FOR EACH vRecursive.Control
      RESULT = SetCursorFirstEntity( vRecursive, "Control", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:ControlRelinkDelete( vDialog, vRecursive, vLastLOD,
         //:                     LastViewZKey, vLOD_LPLR, vSubtask )
         oTZWDLGSO_ControlRelinkDelete( vDialog, vRecursive, &vLastLOD, &LastViewZKey, vLOD_LPLR, vSubtask );
         RESULT = SetCursorNextEntity( vRecursive, "Control", "" );
      } 

      //:END

      //:FOR EACH vDialog.Action
      RESULT = SetCursorFirstEntity( vDialog, "Action", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:FOR EACH vDialog.ActMap
         RESULT = SetCursorFirstEntity( vDialog, "ActMap", "" );
         while ( RESULT > zCURSOR_UNCHANGED )
         { 
            //:IF vDialog.ActMapView  EXISTS
            lTempInteger_1 = CheckExistenceOfEntity( vDialog, "ActMapView" );
            if ( lTempInteger_1 == 0 )
            { 
               //:IF LastViewZKey != vDialog.ActMapView.ZKey
               if ( CompareAttributeToInteger( vDialog, "ActMapView", "ZKey", LastViewZKey ) != 0 )
               { 
                  //:SET CURSOR FIRST vDialog.ViewObjRef WHERE
                  //:    vDialog.ViewObjRef.ZKey = vDialog.ActMapView.ZKey
                  GetIntegerFromAttribute( &lTempInteger_2, vDialog, "ActMapView", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vDialog, "ViewObjRef", "ZKey", lTempInteger_2, "" );
                  //:IF RESULT < zCURSOR_SET
                  if ( RESULT < zCURSOR_SET )
                  { 
                     //:SET CURSOR FIRST vDialog.ViewObjRef WHERE
                     //:    vDialog.ViewObjRef.Name = vDialog.ActMapView.Name
                     GetStringFromAttribute( szTempString_5, zsizeof( szTempString_5 ), vDialog, "ActMapView", "Name" );
                     RESULT = SetCursorFirstEntityByString( vDialog, "ViewObjRef", "Name", szTempString_5, "" );
                     //:IF RESULT >= zCURSOR_SET
                     if ( RESULT >= zCURSOR_SET )
                     { 

                        //:// If there was a match on Name but not on Zkey,
                        //:// reinclude the ActMapView.
                        //:EXCLUDE vDialog.ActMapView
                        RESULT = ExcludeEntity( vDialog, "ActMapView", zREPOS_AFTER );
                        //:INCLUDE vDialog.ActMapView FROM vDialog.ViewObjRef
                        RESULT = IncludeSubobjectFromSubobject( vDialog, "ActMapView", vDialog, "ViewObjRef", zPOS_AFTER );

                        //:// Activate the correct LOD for later processing.
                        //:IF LastViewZKey != 0
                        if ( LastViewZKey != 0 )
                        { 
                           //:DropMetaOI( vSubtask, vLastLOD )
                           DropMetaOI( vSubtask, vLastLOD );
                           //:LastViewZKey = 0
                           LastViewZKey = 0;
                        } 

                        //:END

                        //:nRC = ActivateMetaOI_ByZKey( vSubtask, vLastLOD, 0, zREFER_LOD_META,
                        //:                             zSINGLE, vDialog.LOD.ZKey, 0 )
                        GetIntegerFromAttribute( &lTempInteger_3, vDialog, "LOD", "ZKey" );
                        nRC = ActivateMetaOI_ByZKey( vSubtask, &vLastLOD, 0, zREFER_LOD_META, zSINGLE, lTempInteger_3, 0 );
                        //:IF nRC < 0
                        if ( nRC < 0 )
                        { 
                           //:nRC = ActivateMetaOI_ByName( vSubtask, vLastLOD, 0, zREFER_LOD_META,
                           //:                             zSINGLE, vDialog.LOD.Name, 0 )
                           GetStringFromAttribute( szTempString_5, zsizeof( szTempString_5 ), vDialog, "LOD", "Name" );
                           nRC = ActivateMetaOI_ByName( vSubtask, &vLastLOD, 0, zREFER_LOD_META, zSINGLE, szTempString_5, 0 );
                        } 

                        //:END

                        //:IF nRC < 0
                        if ( nRC < 0 )
                        { 
                           //:// If we get here, we have a Zeidon error.
                           //:szMsg = "Deleting ActMap due to LOD load error.| Registered View Name: " +
                           //:        vDialog.ViewObjRef.Name
                           GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
                           ZeidonStringCopy( szMsg, 1, 0, "Deleting ActMap due to LOD load error.\nRegistered View Name: ", 1, 0, 256 );
                           ZeidonStringConcat( szMsg, 1, 0, szTempString_6, 1, 0, 256 );
                           //:MessageSend( vSubtask, "WD00504", "Dialog Relink",
                           //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                           MessageSend( vSubtask, "WD00504", "Dialog Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                           //:DELETE ENTITY vDialog.ActMap NONE
                           RESULT = DeleteEntity( vDialog, "ActMap", zREPOS_NONE );
                           //:ELSE
                        } 
                        else
                        { 
                           //:LastViewZKey = vDialog.ViewObjRef.ZKey
                           GetIntegerFromAttribute( &LastViewZKey, vDialog, "ViewObjRef", "ZKey" );
                           //:NAME VIEW vLastLOD "vLastLOD"
                           SetNameForView( vLastLOD, "vLastLOD", 0, zLEVEL_TASK );
                        } 

                        //:END

                        //:ELSE
                     } 
                     else
                     { 
                        //:// There was no match on either ZKey or Name.
                        //:szMsg = "Deleting Action Mapping due to missing View. | Registered View Name: " +
                        //:        vDialog.ActMapView.Name
                        GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "ActMapView", "Name", "", 0 );
                        ZeidonStringCopy( szMsg, 1, 0, "Deleting Action Mapping due to missing View. \nRegistered View Name: ", 1, 0, 256 );
                        ZeidonStringConcat( szMsg, 1, 0, szTempString_7, 1, 0, 256 );
                        //:MessageSend( vSubtask, "WD00503", "Dialog Relink",
                        //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                        MessageSend( vSubtask, "WD00503", "Dialog Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                        //:DELETE ENTITY vDialog.ActMap NONE
                        RESULT = DeleteEntity( vDialog, "ActMap", zREPOS_NONE );
                     } 

                     //:END
                     //:ELSE
                  } 
                  else
                  { 
                     //:// There was a match on ActMapView Zkey.  Make sure the corresponding
                     //:// LOD is activated.
                     //:IF LastViewZKey != 0
                     if ( LastViewZKey != 0 )
                     { 
                        //:DropMetaOI( vSubtask, vLastLOD )
                        DropMetaOI( vSubtask, vLastLOD );
                        //:LastViewZKey = 0
                        LastViewZKey = 0;
                     } 

                     //:END

                     //:nRC = ActivateMetaOI_ByZKey( vSubtask, vLastLOD, 0, zREFER_LOD_META,
                     //:                             zSINGLE, vDialog.LOD.ZKey, 0 )
                     GetIntegerFromAttribute( &lTempInteger_4, vDialog, "LOD", "ZKey" );
                     nRC = ActivateMetaOI_ByZKey( vSubtask, &vLastLOD, 0, zREFER_LOD_META, zSINGLE, lTempInteger_4, 0 );
                     //:IF nRC < 0
                     if ( nRC < 0 )
                     { 
                        //:nRC = ActivateMetaOI_ByName( vSubtask, vLastLOD, 0, zREFER_LOD_META,
                        //:                             zSINGLE, vDialog.LOD.Name, 0 )
                        GetStringFromAttribute( szTempString_8, zsizeof( szTempString_8 ), vDialog, "LOD", "Name" );
                        nRC = ActivateMetaOI_ByName( vSubtask, &vLastLOD, 0, zREFER_LOD_META, zSINGLE, szTempString_8, 0 );
                     } 

                     //:END

                     //:IF nRC < 0
                     if ( nRC < 0 )
                     { 
                        //:// If we get here, we have a Zeidon error.
                        //:szMsg = "Deleting ActMap due to LOD load error.| Registered View Name: " +
                        //:        vDialog.ViewObjRef.Name
                        GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
                        ZeidonStringCopy( szMsg, 1, 0, "Deleting ActMap due to LOD load error.\nRegistered View Name: ", 1, 0, 256 );
                        ZeidonStringConcat( szMsg, 1, 0, szTempString_9, 1, 0, 256 );
                        //:MessageSend( vSubtask, "WD00504", "Dialog Relink",
                        //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                        MessageSend( vSubtask, "WD00504", "Dialog Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                        //:DELETE ENTITY vDialog.ActMap NONE
                        RESULT = DeleteEntity( vDialog, "ActMap", zREPOS_NONE );
                        //:ELSE
                     } 
                     else
                     { 
                        //:LastViewZKey = vDialog.ViewObjRef.ZKey
                        GetIntegerFromAttribute( &LastViewZKey, vDialog, "ViewObjRef", "ZKey" );
                        //:NAME VIEW vLastLOD "vLastLOD"
                        SetNameForView( vLastLOD, "vLastLOD", 0, zLEVEL_TASK );
                     } 

                     //:END
                  } 

                  //:END
               } 

               //:END

               //:IF vDialog.ActMapLOD_Entity EXISTS
               lTempInteger_5 = CheckExistenceOfEntity( vDialog, "ActMapLOD_Entity" );
               if ( lTempInteger_5 == 0 )
               { 
                  //:SET CURSOR FIRST vLastLOD.LOD_Entity WHERE
                  //:    vLastLOD.LOD_Entity.ZKey = vDialog.ActMapLOD_Entity.ZKey
                  GetIntegerFromAttribute( &lTempInteger_6, vDialog, "ActMapLOD_Entity", "ZKey" );
                  RESULT = SetCursorFirstEntityByInteger( vLastLOD, "LOD_Entity", "ZKey", lTempInteger_6, "" );
                  //:IF RESULT < zCURSOR_SET
                  if ( RESULT < zCURSOR_SET )
                  { 
                     //:SET CURSOR FIRST vLastLOD.LOD_Entity WHERE
                     //:    vLastLOD.LOD_Entity.Name = vDialog.ActMapLOD_Entity.Name
                     GetStringFromAttribute( szTempString_10, zsizeof( szTempString_10 ), vDialog, "ActMapLOD_Entity", "Name" );
                     RESULT = SetCursorFirstEntityByString( vLastLOD, "LOD_Entity", "Name", szTempString_10, "" );
                     //:IF RESULT >= zCURSOR_SET
                     if ( RESULT >= zCURSOR_SET )
                     { 
                        //:// If there was a match on Name but not on Zkey,
                        //:// reinclude the LOD_Entity.
                        //:EXCLUDE vDialog.ActMapLOD_Entity
                        RESULT = ExcludeEntity( vDialog, "ActMapLOD_Entity", zREPOS_AFTER );
                        //:INCLUDE vDialog.ActMapLOD_Entity FROM vLastLOD.LOD_Entity
                        RESULT = IncludeSubobjectFromSubobject( vDialog, "ActMapLOD_Entity", vLastLOD, "LOD_Entity", zPOS_AFTER );
                        //:ELSE
                     } 
                     else
                     { 
                        //:// There was no match on either ZKey or Name.
                        //:szMsg = "Deleting Action Mapping due to missing LOD Entity.|   Registered View Name: " +
                        //:        vDialog.ViewObjRef.Name + "|   LOD Entity Name: " +
                        //:        vDialog.ActMapLOD_Entity.Name
                        GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
                        ZeidonStringCopy( szMsg, 1, 0, "Deleting Action Mapping due to missing LOD Entity.\n  Registered View Name: ", 1, 0, 256 );
                        ZeidonStringConcat( szMsg, 1, 0, szTempString_10, 1, 0, 256 );
                        ZeidonStringConcat( szMsg, 1, 0, "\n  LOD Entity Name: ", 1, 0, 256 );
                        GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "ActMapLOD_Entity", "Name", "", 0 );
                        ZeidonStringConcat( szMsg, 1, 0, szTempString_11, 1, 0, 256 );
                        //:MessageSend( vSubtask, "WD00505", "Dialog Relink",
                        //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                        MessageSend( vSubtask, "WD00505", "Dialog Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                        //:DELETE ENTITY vDialog.ActMap NONE
                        RESULT = DeleteEntity( vDialog, "ActMap", zREPOS_NONE );
                     } 

                     //:END
                  } 

                  //:END
               } 

               //:END
            } 

            RESULT = SetCursorNextEntity( vDialog, "ActMap", "" );
            //:END
         } 

         RESULT = SetCursorNextEntity( vDialog, "Action", "" );
         //:END
      } 

      //:END

      //:FOR EACH vRecursive.Menu
      RESULT = SetCursorFirstEntity( vRecursive, "Menu", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:FOR EACH vDialog.Option
         RESULT = SetCursorFirstEntity( vDialog, "Option", "" );
         while ( RESULT > zCURSOR_UNCHANGED )
         { 
            //:OptionRelinkDelete( vSubtask, vLOD_LPLR, vDialog, vRecursive,
            //:                    vLastLOD, LastViewZKey )
            oTZWDLGSO_OptionRelinkDelete( vSubtask, vLOD_LPLR, vDialog, vRecursive, &vLastLOD, &LastViewZKey );
            RESULT = SetCursorNextEntity( vDialog, "Option", "" );
         } 

         RESULT = SetCursorNextEntity( vRecursive, "Menu", "" );
         //:END
      } 

      //:END

      //:DropView( vRecursive )
      DropView( vRecursive );
      RESULT = SetCursorNextEntity( vDialog, "Window", "" );
   } 


   //:END
   return( 0 );
// END
} 


//:LOCAL OPERATION
//:OptionRelinkDelete( VIEW vSubtask,
//:                    VIEW vLOD_LPLR   BASED ON LOD TZCMLPLO,
//:                    VIEW vDialog     BASED ON LOD TZWDLGSO,
//:                    VIEW vOption     BASED ON LOD TZWDLGSO,
//:                    VIEW vLastLOD    BASED ON LOD TZZOLODO,
//:                    INTEGER LastViewZKey )

//:   VIEW         vDomain BASED ON LOD TZDGSRCO
static zSHORT
oTZWDLGSO_OptionRelinkDelete( zVIEW     vSubtask,
                              zVIEW     vLOD_LPLR,
                              zVIEW     vDialog,
                              zVIEW     vOption,
                              zPVIEW    vLastLOD,
                              zPLONG    LastViewZKey )
{
   zVIEW     vDomain = 0; 
   //:STRING (255) szMsg
   zCHAR     szMsg[ 256 ] = { 0 }; 
   //:INTEGER      nRemapFlag
   zLONG     nRemapFlag = 0; 
   //:SHORT  nRC
   zSHORT    nRC = 0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 
   zLONG     lTempInteger_1; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zLONG     lTempInteger_2; 
   zCHAR     szTempString_3[ 33 ]; 
   zSHORT    lTempInteger_3; 
   zLONG     lTempInteger_4; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zSHORT    lTempInteger_5; 
   zLONG     lTempInteger_6; 
   zLONG     lTempInteger_7; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 


   //:// Process each subcontrol.
   //:FOR EACH vOption.OptOpt
   RESULT = SetCursorFirstEntity( vOption, "OptOpt", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:SetViewToSubobject( vOption, "OptOpt" )
      SetViewToSubobject( vOption, "OptOpt" );
      //:OptionRelinkDelete( vSubtask, vLOD_LPLR, vDialog, vOption, vLastLOD, LastViewZKey )
      oTZWDLGSO_OptionRelinkDelete( vSubtask, vLOD_LPLR, vDialog, vOption, vLastLOD, LastViewZKey );
      //:ResetViewFromSubobject( vOption )
      ResetViewFromSubobject( vOption );
      RESULT = SetCursorNextEntity( vOption, "OptOpt", "" );
   } 

   //:END

   //:/*  For each OptMap, check each entity against the corresponding
   //:    LOD to make sure that entity exists in the LOD.  If it doesn't,
   //:    delete the OptMap.  */
   //:FOR EACH vOption.OptMap
   RESULT = SetCursorFirstEntity( vOption, "OptMap", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:IF vOption.OptMapView EXISTS
      lTempInteger_0 = CheckExistenceOfEntity( vOption, "OptMapView" );
      if ( lTempInteger_0 == 0 )
      { 
         //:// Get the correct LOD, if the last one used isn't the one in this OptMap.
         //:IF LastViewZKey != vOption.OptMapView.ZKey
         if ( CompareAttributeToInteger( vOption, "OptMapView", "ZKey", *LastViewZKey ) != 0 )
         { 
            //:SET CURSOR FIRST vDialog.ViewObjRef WHERE
            //:    vDialog.ViewObjRef.ZKey = vOption.OptMapView.ZKey
            GetIntegerFromAttribute( &lTempInteger_1, vOption, "OptMapView", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( vDialog, "ViewObjRef", "ZKey", lTempInteger_1, "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:nRemapFlag = 0
               nRemapFlag = 0;
               //:ELSE
            } 
            else
            { 
               //:SET CURSOR FIRST vDialog.ViewObjRef WHERE
               //:    vDialog.ViewObjRef.Name = vOption.OptMapView.Name
               GetStringFromAttribute( szTempString_0, zsizeof( szTempString_0 ), vOption, "OptMapView", "Name" );
               RESULT = SetCursorFirstEntityByString( vDialog, "ViewObjRef", "Name", szTempString_0, "" );
               //:IF RESULT >= zCURSOR_SET
               if ( RESULT >= zCURSOR_SET )
               { 
                  //:// If there was a match on Name but not on Zkey,
                  //:// reinclude the OptMapView.
                  //:EXCLUDE vOption.OptMapView
                  RESULT = ExcludeEntity( vOption, "OptMapView", zREPOS_AFTER );
                  //:INCLUDE vOption.OptMapView FROM vDialog.ViewObjRef
                  RESULT = IncludeSubobjectFromSubobject( vOption, "OptMapView", vDialog, "ViewObjRef", zPOS_AFTER );
                  //:nRemapFlag = 0
                  nRemapFlag = 0;
                  //:ELSE
               } 
               else
               { 
                  //:szMsg = "Deleting Option Mapping for:|   Window: " + vDialog.Window.Tag +
                  //:        "|   Option: " + vOption.Option.Tag +
                  //:        "| because of missing View: " + vOption.OptMapView.Name
                  GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
                  ZeidonStringCopy( szMsg, 1, 0, "Deleting Option Mapping for:\n  Window: ", 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_0, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\n  Option: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vOption, "Option", "Tag", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_1, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\nbecause of missing View: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vOption, "OptMapView", "Name", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_2, 1, 0, 256 );
                  //:MessageSend( vSubtask, "WD00511", "Dialog Relink",
                  //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                  MessageSend( vSubtask, "WD00511", "Dialog Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                  //:DELETE ENTITY vOption.OptMap NONE
                  RESULT = DeleteEntity( vOption, "OptMap", zREPOS_NONE );
                  //:nRemapFlag = -1
                  nRemapFlag = -1;
               } 

               //:END
            } 

            //:END
            //:IF nRemapFlag = 0
            if ( nRemapFlag == 0 )
            { 
               //:// There was a match on OptMapView Zkey or Name.
               //:// Make sure the corresponding LOD is activated.
               //:IF LastViewZKey != 0
               if ( *LastViewZKey != 0 )
               { 
                  //:DropMetaOI( vSubtask, vLastLOD )
                  DropMetaOI( vSubtask, *vLastLOD );
                  //:LastViewZKey = 0
                  *LastViewZKey = 0;
               } 

               //:END

               //:nRC = ActivateMetaOI_ByZKey( vSubtask, vLastLOD, 0, zREFER_LOD_META,
               //:                             zSINGLE, vDialog.LOD.ZKey, 0 )
               GetIntegerFromAttribute( &lTempInteger_2, vDialog, "LOD", "ZKey" );
               nRC = ActivateMetaOI_ByZKey( vSubtask, vLastLOD, 0, zREFER_LOD_META, zSINGLE, lTempInteger_2, 0 );
               //:IF nRC < 0
               if ( nRC < 0 )
               { 
                  //:// If we get here, we have a Zeidon error.
                  //:szMsg = "Deleting OptMap due to LOD load error.| Registered View Name: " +
                  //:        vDialog.ViewObjRef.Name
                  GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "ViewObjRef", "Name", "", 0 );
                  ZeidonStringCopy( szMsg, 1, 0, "Deleting OptMap due to LOD load error.\nRegistered View Name: ", 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_3, 1, 0, 256 );
                  //:MessageSend( vSubtask, "WD00512", "Dialog Relink",
                  //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                  MessageSend( vSubtask, "WD00512", "Dialog Relink", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                  //:DELETE ENTITY vOption.OptMap NONE
                  RESULT = DeleteEntity( vOption, "OptMap", zREPOS_NONE );
                  //:ELSE
               } 
               else
               { 
                  //:LastViewZKey = vDialog.ViewObjRef.ZKey
                  GetIntegerFromAttribute( LastViewZKey, vDialog, "ViewObjRef", "ZKey" );
                  //:NAME VIEW vLastLOD "vLastLOD"
                  SetNameForView( *vLastLOD, "vLastLOD", 0, zLEVEL_TASK );
               } 

               //:   // Relink OptMapView?? Is it necessary?
               //:END
            } 

            //:END
         } 

         //:END

         //://         IF vOption.OptMapView EXISTS
         //://            RelinkInstanceToInstance( vOption, "OptMapView",
         //://                                      vDialog, "ViewObjRef" )


         //:IF vOption.OptMapLOD_Attribute EXISTS
         lTempInteger_3 = CheckExistenceOfEntity( vOption, "OptMapLOD_Attribute" );
         if ( lTempInteger_3 == 0 )
         { 
            //:SET CURSOR FIRST vLastLOD.LOD_Attribute WITHIN vLastLOD.LOD WHERE
            //:    vLastLOD.LOD_Attribute.ZKey  = vOption.OptMapLOD_Attribute.ZKey
            GetIntegerFromAttribute( &lTempInteger_4, vOption, "OptMapLOD_Attribute", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( *vLastLOD, "LOD_Attribute", "ZKey", lTempInteger_4, "LOD" );
            //:IF RESULT < 0
            if ( RESULT < 0 )
            { 
               //:// Since there was no match on ZKey, try to find a match on LOD Entity
               //:// name and ER Attribute name, in case the Attribute had been deleted
               //:// and recreated.  In this case, re-include the Attribute.
               //:SET CURSOR FIRST vLastLOD.LOD_Entity WHERE
               //:                 vLastLOD.LOD_Entity.Name = vOption.OptMapRelatedEntity.Name
               GetStringFromAttribute( szTempString_4, zsizeof( szTempString_4 ), vOption, "OptMapRelatedEntity", "Name" );
               RESULT = SetCursorFirstEntityByString( *vLastLOD, "LOD_Entity", "Name", szTempString_4, "" );
               //:IF RESULT >= zCURSOR_SET
               if ( RESULT >= zCURSOR_SET )
               { 
                  //:SET CURSOR FIRST vLastLOD.ER_Attribute WITHIN vLastLOD.LOD_Entity WHERE
                  //:                 vLastLOD.ER_Attribute.Name = vOption.OptMapER_Attribute.Name
                  GetStringFromAttribute( szTempString_4, zsizeof( szTempString_4 ), vOption, "OptMapER_Attribute", "Name" );
                  RESULT = SetCursorFirstEntityByString( *vLastLOD, "ER_Attribute", "Name", szTempString_4, "LOD_Entity" );
                  //:IF RESULT >= zCURSOR_SET     //
                  if ( RESULT >= zCURSOR_SET )
                  { 
                     //:nRemapFlag = 0
                     nRemapFlag = 0;
                     //:ELSE
                  } 
                  else
                  { 
                     //:nRemapFlag = -1
                     nRemapFlag = -1;
                  } 

                  //:END
                  //:ELSE
               } 
               else
               { 
                  //:nRemapFlag = -1
                  nRemapFlag = -1;
               } 

               //:END
               //:IF nRemapFlag = 0  // We were able to remap to an attribute by same name.
               if ( nRemapFlag == 0 )
               { 
                  //:EXCLUDE vOption.OptMapLOD_Attribute
                  RESULT = ExcludeEntity( vOption, "OptMapLOD_Attribute", zREPOS_AFTER );
                  //:INCLUDE  vOption.OptMapLOD_Attribute FROM vLastLOD.LOD_Attribute
                  RESULT = IncludeSubobjectFromSubobject( vOption, "OptMapLOD_Attribute", *vLastLOD, "LOD_Attribute", zPOS_AFTER );
                  //:ELSE
               } 
               else
               { 
                  //:szMsg = "Deleting Option Mapping for:|   Window: " + vDialog.Window.Tag +
                  //:        "|   Option: " + vOption.Option.Tag +
                  //:        "| because of missing Attribute: " + vOption.OptMapER_Attribute.Name
                  GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
                  ZeidonStringCopy( szMsg, 1, 0, "Deleting Option Mapping for:\n  Window: ", 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_4, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\n  Option: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vOption, "Option", "Tag", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_5, 1, 0, 256 );
                  ZeidonStringConcat( szMsg, 1, 0, "\nbecause of missing Attribute: ", 1, 0, 256 );
                  GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vOption, "OptMapER_Attribute", "Name", "", 0 );
                  ZeidonStringConcat( szMsg, 1, 0, szTempString_6, 1, 0, 256 );
                  //:MessageSend( vSubtask, "WD00513", "Dialog Activate",
                  //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                  MessageSend( vSubtask, "WD00513", "Dialog Activate", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                  //:DELETE ENTITY vOption.OptMap NONE
                  RESULT = DeleteEntity( vOption, "OptMap", zREPOS_NONE );
               } 

               //:END
               //:ELSE
            } 
            else
            { 
               //:// Relink OptMapLOD_Attribute, & subordinates & OptMapContext
               //://RelinkInstanceToInstance( vOption,  "OptMapLOD_Attribute",
               //://                          vLastLOD, "LOD_Attribute" )
               //://RelinkInstanceToInstance( vOption,  "OptMapRelatedEntity",
               //://                          vLastLOD, "LOD_Entity" )
               //://RelinkInstanceToInstance( vOption,  "OptMapER_Attribute",
               //://                          vLastLOD, "ER_Attribute" )
               //://RelinkInstanceToInstance( vOption,  "OptMapER_Domain",
               //://                          vLastLOD, "Domain" )
               //:IF vOption.OptMapContext EXISTS
               lTempInteger_5 = CheckExistenceOfEntity( vOption, "OptMapContext" );
               if ( lTempInteger_5 == 0 )
               { 
                  //:// Try to find the Domain first by ZKey and then by name.
                  //:// If found, also find the Context by ZKey and then by name.
                  //:// If no match was finally found, exclude the Context.
                  //:nRC = ActivateMetaOI_ByZKey( vSubtask, vDomain, 0, zREFER_DOMAIN_META,
                  //:                             zSINGLE, vOption.OptMapER_Domain.ZKey , 0 )
                  GetIntegerFromAttribute( &lTempInteger_6, vOption, "OptMapER_Domain", "ZKey" );
                  nRC = ActivateMetaOI_ByZKey( vSubtask, &vDomain, 0, zREFER_DOMAIN_META, zSINGLE, lTempInteger_6, 0 );
                  //:IF nRC >= 0
                  if ( nRC >= 0 )
                  { 
                     //:SET CURSOR FIRST vDomain.Context WHERE
                     //:    vDomain.Context.ZKey = vOption.OptMapContext.ZKey
                     GetIntegerFromAttribute( &lTempInteger_7, vOption, "OptMapContext", "ZKey" );
                     RESULT = SetCursorFirstEntityByInteger( vDomain, "Context", "ZKey", lTempInteger_7, "" );
                     //:IF RESULT >= 0
                     if ( RESULT >= 0 )
                     { 
                        //:nRemapFlag = 0
                        nRemapFlag = 0;
                        //:ELSE
                     } 
                     else
                     { 
                        //:SET CURSOR FIRST vDomain.Context WHERE
                        //:    vDomain.Context.Name = vOption.OptMapContext.Name
                        GetStringFromAttribute( szTempString_7, zsizeof( szTempString_7 ), vOption, "OptMapContext", "Name" );
                        RESULT = SetCursorFirstEntityByString( vDomain, "Context", "Name", szTempString_7, "" );
                        //:IF RESULT >= zCURSOR_SET
                        if ( RESULT >= zCURSOR_SET )
                        { 
                           //:nRemapFlag = 1
                           nRemapFlag = 1;
                           //:EXCLUDE vOption.OptMapContext
                           RESULT = ExcludeEntity( vOption, "OptMapContext", zREPOS_AFTER );
                           //:INCLUDE vOption.OptMapContext FROM vDomain.Context
                           RESULT = IncludeSubobjectFromSubobject( vOption, "OptMapContext", vDomain, "Context", zPOS_AFTER );
                           //:ELSE
                        } 
                        else
                        { 
                           //:nRemapFlag = -1
                           nRemapFlag = -1;
                        } 

                        //:END
                     } 

                     //:END
                     //:ELSE
                  } 
                  else
                  { 
                     //:nRC = ActivateMetaOI_ByName( vSubtask, vDomain, 0, zREFER_DOMAIN_META,
                     //:                             zSINGLE, vOption.OptMapER_Domain.Name , 0 )
                     GetStringFromAttribute( szTempString_7, zsizeof( szTempString_7 ), vOption, "OptMapER_Domain", "Name" );
                     nRC = ActivateMetaOI_ByName( vSubtask, &vDomain, 0, zREFER_DOMAIN_META, zSINGLE, szTempString_7, 0 );
                     //:IF nRC >= 0
                     if ( nRC >= 0 )
                     { 
                        //:SET CURSOR FIRST vDomain.Context WHERE
                        //:    vDomain.Context.Name = vOption.OptMapContext.Name
                        GetStringFromAttribute( szTempString_8, zsizeof( szTempString_8 ), vOption, "OptMapContext", "Name" );
                        RESULT = SetCursorFirstEntityByString( vDomain, "Context", "Name", szTempString_8, "" );
                        //:IF RESULT >= zCURSOR_SET
                        if ( RESULT >= zCURSOR_SET )
                        { 
                           //:nRemapFlag = 1
                           nRemapFlag = 1;
                           //:EXCLUDE vOption.OptMapContext
                           RESULT = ExcludeEntity( vOption, "OptMapContext", zREPOS_AFTER );
                           //:INCLUDE vOption.OptMapContext FROM vDomain.Context
                           RESULT = IncludeSubobjectFromSubobject( vOption, "OptMapContext", vDomain, "Context", zPOS_AFTER );
                           //:ELSE
                        } 
                        else
                        { 
                           //:nRemapFlag = -1
                           nRemapFlag = -1;
                        } 

                        //:END
                        //:ELSE
                     } 
                     else
                     { 
                        //:nRemapFlag = -1
                        nRemapFlag = -1;
                     } 

                     //:END
                  } 

                  //:END
                  //:IF nRemapFlag = -1
                  if ( nRemapFlag == -1 )
                  { 
                     //:szMsg = "Excluding Context for:|   Window: " + vDialog.Window.Tag +
                     //:        "|   Option: " + vOption.Option.Tag +
                     //:        "| because of missing Context: " + vOption.OptMapContext.Name
                     GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "Window", "Tag", "", 0 );
                     ZeidonStringCopy( szMsg, 1, 0, "Excluding Context for:\n  Window: ", 1, 0, 256 );
                     ZeidonStringConcat( szMsg, 1, 0, szTempString_8, 1, 0, 256 );
                     ZeidonStringConcat( szMsg, 1, 0, "\n  Option: ", 1, 0, 256 );
                     GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vOption, "Option", "Tag", "", 0 );
                     ZeidonStringConcat( szMsg, 1, 0, szTempString_9, 1, 0, 256 );
                     ZeidonStringConcat( szMsg, 1, 0, "\nbecause of missing Context: ", 1, 0, 256 );
                     GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vOption, "OptMapContext", "Name", "", 0 );
                     ZeidonStringConcat( szMsg, 1, 0, szTempString_10, 1, 0, 256 );
                     //:MessageSend( vSubtask, "WD00514", "Dialog Activate",
                     //:             szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
                     MessageSend( vSubtask, "WD00514", "Dialog Activate", szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
                     //:EXCLUDE vOption.OptMapContext NONE
                     RESULT = ExcludeEntity( vOption, "OptMapContext", zREPOS_NONE );
                     //:ELSE
                  } 
                  else
                  { 
                     //:IF nRemapFlag = 0
                     if ( nRemapFlag == 0 )
                     { 
                        //:RelinkInstanceToInstance( vOption, "OptMapContext",
                        //:                       vDomain, "Context" )
                        RelinkInstanceToInstance( vOption, "OptMapContext", vDomain, "Context" );
                     } 

                     //:END
                     //:DropMetaOI( vSubtask, vDomain )
                     DropMetaOI( vSubtask, vDomain );
                  } 

                  //:END
               } 

               //:END
            } 

            //:END
         } 

         //:END
      } 

      RESULT = SetCursorNextEntity( vOption, "OptMap", "" );
      //:END
   } 

   //:END
   return( 0 );
// END
} 


//:DERIVED ATTRIBUTE OPERATION
//:NLS_OptionText( VIEW        vDialog BASED ON LOD TZWDLGSO,
//:                STRING (32) lpEntity,
//:                STRING (32) lpAttribute,
//:                SHORT       GetOrSetFlag )

//:   SHORT        nLanguageCode
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_NLS_OptionText( zVIEW     vDialog,
                          LPVIEWENTITY lpEntity,
                          LPVIEWATTRIB lpAttribute,
                          zSHORT    GetOrSetFlag )
{
   zSHORT    nLanguageCode = 0; 
   //:STRING (254) szOption
   zCHAR     szOption[ 255 ] = { 0 }; 
   zSHORT    RESULT; 


   //:SysGetLanguageCode ( nLanguageCode )
   SysGetLanguageCode( &nLanguageCode );

   //:CASE GetOrSetFlag
   switch( GetOrSetFlag )
   { 
      //:OF   zDERIVED_GET:
      case zDERIVED_GET :

         //:// Determine Option text to use by checking the NLS Language Code for a match on
         //:// a OptionNLS_Text entity.  If there is a match, use it.  Otherwise, use the Option.Text
         //:// attribute.

         //:SET CURSOR FIRST vDialog.OptionNLS_Text WHERE
         //:              vDialog.OptionNLS_Text.LanguageIndex = nLanguageCode
         RESULT = SetCursorFirstEntityByInteger( vDialog, "OptionNLS_Text", "LanguageIndex", nLanguageCode, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szOption = vDialog.OptionNLS_Text.Text
            GetVariableFromAttribute( szOption, 0, 'S', 255, vDialog, "OptionNLS_Text", "Text", "", 0 );
            //:ELSE
         } 
         else
         { 
            //:szOption = vDialog.Option.Text
            GetVariableFromAttribute( szOption, 0, 'S', 255, vDialog, "Option", "Text", "", 0 );
         } 

         //:END

         //:StoreStringInRecord ( vDialog, lpEntity, lpAttribute, szOption )
         StoreStringInRecord( vDialog, lpEntity, lpAttribute, szOption );
         break ;

      //:  /* end zDERIVED_GET */
      //:OF   zDERIVED_SET:
      case zDERIVED_SET :

         //:// As for zDERIVED_GET above, use the Language Code to store the data entered into
         //:// the derived attribute into the correct attribute.
         //:// If there is OptionNLS_Text entity that matches the Language Code, then set the data there.
         //:// If not, set it into the Window.Option attribute.

         //:GetStringFromRecord ( vDialog, lpEntity, lpAttribute, szOption, 254 )
         GetStringFromRecord( vDialog, lpEntity, lpAttribute, szOption, 254 );

         //:SET CURSOR FIRST vDialog.OptionNLS_Text WHERE
         //:              vDialog.OptionNLS_Text.LanguageIndex = nLanguageCode
         RESULT = SetCursorFirstEntityByInteger( vDialog, "OptionNLS_Text", "LanguageIndex", nLanguageCode, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:vDialog.OptionNLS_Text.Text = szOption
            SetAttributeFromString( vDialog, "OptionNLS_Text", "Text", szOption );
            //:ELSE
         } 
         else
         { 
            //:vDialog.Option.Text = szOption
            SetAttributeFromString( vDialog, "Option", "Text", szOption );
         } 

         //:END
         break ;
   } 


   //:     /* end zDERIVED_SET */
   //:END  /* case */
   return( 0 );
// END
} 


 
#ifdef __cplusplus
}
#endif
