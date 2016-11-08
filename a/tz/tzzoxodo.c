/////////////////////////////////////////////////////////////////////////////
//
// MODULE NAME:   tzzoxodo.c - Zeidon application operations
// DESCRIPTION:   This C file contains global and LOD operations for the
//                Zeidon application.
//
// //////////////////////////////////////////////////////////////////////////
// * Copyright (c) 1995 - 2016 QuinSoft, Inc.   All rights reserved.        *
// * Confidential and Proprietary material subject to license - do not      *
// * reproduce or disclose.  This material is an unpublished work and       *
// * is considered a trade secret belonging to the copyright holder.        *
// //////////////////////////////////////////////////////////////////////////
//
// AUTHOR:        Gig Kirk
// DATE:          1992/09/30
// API:           MicroSoft foundation classes and Windows 3.1 SDK
// ENVIRONMENT:   Windows 3.1
// REVISION:      10B    1995/08/05
//
// LAST MESSAGE ID: ZO00318
//
// HISTORY:
//
//    1995/08/05: Beginning of 10B branch
//
/////////////////////////////////////////////////////////////////////////////
//

/*
CHANGE LOG
2002.06.07 BL
   Modified ofnTZZOXODO_BldRelFieldFK for SavaAs Lod without Attributes

2001.08.14 DGC
   Fixed bug that kept keys from having a DATAFIELD record when the key attribute
   was hidden.

2001.08.03 DGC
   Fixed migrate bug reported by HH.

2001.04.25 HH
   forward SQL_JoinWithParent flag.

2000.11.17 HH
   Support the new "Switch Foreign Key" concept in TE generation (SAP).
   Handle Foreign keys beeing an ER attribute (SAP).

2000.10.25  SR  Z2000 Size of path variables
   Modified size of size of szXMD_FileSpec in function oTZZOXODO_SaveXOD
   because size of attributes ExecDir, MetaSrcDir and PgmSrcDir has
   been changed to 254 in datamodel.
   Adjust the size of messagetext variables.
2000.08.21 RG  Z2000
   While building the XOD's we have to check if the entityname includes
   the tableowner

2000.08.14 DC  Z10
   Fixed a bug reported by, oh everybody.  For recursive entites we make
   sure that the parent and child entities have the exact same work attrs.

2000.04.25 DC  Z10
   Modified positioning on ER Attributes for building physical data so that
   if a match was not found on ZKey, we would look for a match on Name.

2000.04.05 DC  Z10
   Added call to ofnTZZOXODO_ProcDupEntity to process LOD entities that have
   the DuplicateEntityInstance flag set to make sure that all LOD_Entities
   for the same ER_Entity have a common set of Attributes. That means that
   given LOD_Entity A, all attributes for other LOD_Entities for the same
   ER_Entity as A will be added to A if they don't already exist in A.

2000.01.13 BL  Z10
   remove unreferenced local variable

1999.10.09 DC  Z10
   Modified SaveXOD to set ER_DATE from EntpER_Model.LastSyncDate instead
   of from W_MetaDef.LastUpdateDate, since the latter date was not correct
   when a PMD was copied.

1999.08.11 RG  Z9J/Z2000  VSAM
   If there is no relationship in the TE then this is OK for all entities
   which have a relationship in the ERD and have no key attribute

1999.08.05 RG  Z9J/Z2000  VSAM
   We don't need the XSK-Files anymore. Therefore remove of call of
   TZSIXSKO_SaveXSK

1999.07.19 DC  9J/Z10
   Made modifications to several operations so that Network XODs would have
   the same substructure (DATARECORD, etc.) as database XODs.

1999.07.13 DGC 10a
   Added the addition of ER_DATE into the XOD.  This allows Core to check for
   LODs that are out of sync.

1999.06.30 DC  9J+Z10
   Further modified SEQUENCING processing for foreign keys so that it would
   not generate SEQUENCING entries for foreign keys that were for
   relationships that not a part of the subobject being processed.
   Also modified SEQUENCING processing for regular attributes so that
   entries would not be generated for attributes that are part of an
   entity with max cardinality of 1.

1999.06.10 DC  Z10
   Modified ofnTZZOXODO_BldXODChildEnt so that derived entity would not
   go through AutoLoad logic, which was sometimes generating an error.

1999.05.20 DC  9J+Z10  TS294, TS390, TS595
   Modified ofnTZZOXODO_BldAttribFK and created ofnTZZOXODO_SetSequencingForFK
   to correct the generation of SEQUENCING information in the XOD. Extra
   SEQUENCING entries were being generated under some circumstances.

1999.04.09 DC  Z10   Domains
   Added handling of DerivedExpression in building of XOD ATTRIB entity.

2010.01.29 DC  Z10
   Modified ofnTZZOXODO_BldXODChildEnt operation to correct order of attributes in XOD.
   See comments in code marked DonC.
*/

#include "tzlodopr.h"
#include "tz__oprs.h"
#include "tzlodopr.hg"
#include "ZeidonOp.H"

// #define CreateViewFromViewForTask( pvReturn, vSrc, vTask ) CreateViewTrace( __FILE__ " #" mSTR2( __LINE__ ), pvReturn, vSrc, vTask )
// #define DropView( v ) DropViewTrace( __FILE__ " #" mSTR2( __LINE__ ), v )

zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXOD( zVIEW vSubtask, zVIEW vTZZOXODO_Root,
                    zVIEW vTZZOXODO, zVIEW vTZZOLOD1,
                    zVIEW vTZEREMDO_REF, zVIEW vTZTENVRO_REF );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODChildEnt( zVIEW vSubtask, zVIEW vTZZOXODO_Root,
                            zVIEW vTZZOXODO, zVIEW vTZZOLOD1,
                            zVIEW vTZEREMDO_REF, zVIEW vTZTENVRO_REF,
                            zPCHAR pszParadigm, zPCHAR pszNetwork,
                            zPLONG pnAttrCount,
                            zSHORT nDerivedFlag,
                            zCPCHAR cpcDEBUGCHG );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODEntity( zVIEW vSubtask, zVIEW vTZZOXODO, zVIEW vTZZOLOD1 );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODAttrib( zVIEW vSubtask, zVIEW vTZZOXODO, zVIEW vTZZOLOD1,
                          zVIEW vTZEREMDO_REF, zCPCHAR cpcDEBUGCHG );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODAttribHidden( zVIEW vSubtask, zVIEW vTZZOXODO,
                                zVIEW vTZEREMDO_REF, zCPCHAR cpcDEBUGCHG );
static zSHORT
ofnTZZOXODO_BldXODDataRec( zVIEW vSubtask, zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF,
                           zVIEW vTZZOLODO );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODRelRec( zVIEW vSubtask, zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF,
                          zVIEW vTZZOLOD1, zVIEW vTZTENVRO_Parent,
                          zPCHAR szType, zPLONG pnAttrCount );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODDataField( zVIEW vSubtask, zVIEW vTZZOXODO,
                             zVIEW vTZTENVRO_REF );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldAttribGK( zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldDataFieldGK( zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldAttribFK( zVIEW vTZZOXODO,
                         zVIEW vTZTENVRO_REF,
                         zVIEW vTZZOLOD1 );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldDataFieldFK( zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldRelFieldFK( zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF,
                           zVIEW vTZZOXOD1, zVIEW vTZTENVR1_Alt );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldDB_DataFields( zVIEW vTZZOXODO, zVIEW vTZZOLOD1 );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldRelFieldsForMM( zVIEW vSubtask,
                               zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF,
                               zVIEW vTZZOXOD1, zVIEW vTZTENVR1_Alt,
                               zVIEW vTZZOLOD1, zPLONG pnAttrCount );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_PosOnBaseField( zVIEW vTZZOXODO,
                            zVIEW vTZTENVRO_REF, zVIEW vTZTENVR1,
                            zVIEW vTZTENVR1_Alt );

zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldAutoSeq( zVIEW vSubtask, zVIEW vTZZOXODO,
                        zVIEW vTZTENVRO_REF, zVIEW vTZZOLOD1 );
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_ProcDupEntity( zVIEW vSubtask, zVIEW vTZZOXODO,
                           zVIEW vTZEREMDO_REF,
                           zVIEW vTZTENVRO_REF,
                           zVIEW vTZZOLOD1,
                           zPLONG pnAttrCount );

static zLONG GetBaseKey( zVIEW vTZTENVRO );
static zSHORT LocateTE_Field_PK( zVIEW vTZTENVR1, zVIEW vTZTENVRO_REF );

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: oTZZOXODO_SaveXOD
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
oTZZOXODO_SaveXOD( zVIEW vSubtask, zVIEW vTZZOLODO )
{
   zVIEW  vTZZOLOD1;
   zVIEW  vTZZOXODO;
   zVIEW  vTZZOXODO_Root;
   zVIEW  vTZZOXOD1;
   zVIEW  vTZEREMDO_REF;
   zVIEW  vTZTENVRO_REF = 0;
   zVIEW  vTZTENVR1 = 0;
   zVIEW  vT;
   zVIEW  vTZTEDBLO = 0;
   zVIEW  vTaskLPLR;
   zCHAR  szXMD_FileSpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szXMD_DateTime[ 20 ];
   zCHAR  szEMD_DateTime[ 20 ];
   zCHAR  szDTE_DateTime[ 20 ];
   zCHAR  szLOD_Name[ zZEIDON_NAME_LTH + 1 ];
   zCHAR  szAppName[ zZEIDON_NAME_LTH + 1 ];
   zLONG  lTE_ZKey = 0;
   zLONG  hXMD_File;
   zSHORT nRC;

   nRC = ActivateEmptyObjectInstance( &vTZZOXODO, "TZZOXODO", vTZZOLODO, zMULTIPLE | zLEVEL_APPLICATION );
   if ( nRC < 0 )
   {
      MessageSend( vSubtask, "ZO00301", "Operations",
                   "Unable to Activate Empty XOD.\n\nSeek help.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( 0 );
   }

   SetNameForView( vTZZOXODO, "TZZOXODO", vSubtask, zLEVEL_TASK );

   // Get access to ER Object.
   if ( GetViewByName( &vTZEREMDO_REF, "TZEREMDO_REF", vSubtask, zLEVEL_TASK ) < 1 )
   {
      RetrieveViewForMetaList( vSubtask, &vT, zREFER_ERD_META );
      if ( CheckExistenceOfEntity( vT, "W_MetaDef" ) == zCURSOR_SET )
      {
         ActivateMetaOI( vSubtask, &vTZEREMDO_REF, vT, zREFER_ERD_META, zSINGLE | zLEVEL_APPLICATION );
         SetNameForView( vTZEREMDO_REF, "TZEREMDO_REF", vSubtask, zLEVEL_TASK );
      }
      else
         vTZEREMDO_REF = 0;

      DropView( vT );
   }

   CreateEntity( vTZZOXODO, "OBJECT", zPOS_AFTER );

   // If LOD contains a POD reference, then get access to the TE Object.
   if ( CheckExistenceOfEntity( vTZZOLODO, "POD" ) >= zCURSOR_SET )
   {
      zLONG lZKey;

      if ( CompareAttributeToInteger( vTZZOLODO, "POD", "MULTI_ROOT_LIMIT", 0 ) != 0 )
      {
         SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "MR_LIMIT", vTZZOLODO, "POD", "MULTI_ROOT_LIMIT" );
      }

      GetViewByName( &vTZTENVRO_REF, "TE_DB_Environ", vSubtask, zLEVEL_TASK );
      if ( vTZTENVRO_REF == 0 )
      {
         GetIntegerFromAttribute( &lTE_ZKey, vTZZOLODO, "TE_DB_Environ", "ZKey" );
         ActivateMetaOI_ByZKey( vSubtask, &vTZTENVRO_REF, 0, zREFER_DTE_META, zSINGLE | zLEVEL_APPLICATION, lTE_ZKey, zCURRENT_OI );
         if ( !vTZTENVRO_REF )
         {
            MessageSend( vSubtask, "ZO00302", "Operations",
                         "Unable to Load related TE.\n\nOpen or Create TE First.",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            DeleteEntity( vTZZOXODO, "OBJECT", zREPOS_NONE );
            return( 0 );
         }

         SetNameForView( vTZTENVRO_REF, "TE_DB_Environ", vSubtask, zLEVEL_TASK );
      }

      // DGC 12/9/96  Check to see if TE Source ZKey has been set in the LOD.  If it has, then set the entity in the TE view
      // to match.  This will cause us to save the current LOD with the same TE as the last time the LOD was saved.
      GetIntegerFromAttribute( &lZKey, vTZZOLODO, "POD", "TE_SourceZKey" );
      if ( lZKey )
      {
         if ( SetCursorFirstEntityByInteger( vTZTENVRO_REF, "TE_DBMS_Source", "ZKey", lZKey, 0 ) < zCURSOR_SET )
         {
            MessageSend( vSubtask, "ZO00302", "Operations",
                         "Unable to Load related TE.\n\nOpen or Create TE First.",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            DeleteEntity( vTZZOXODO, "OBJECT", zREPOS_NONE );
            return( 0 );
         }
      }
   }

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   if ( vTaskLPLR )
   {
      zCHAR  szXMD_FileTemp[ zMAX_FILESPEC_LTH + 1 ];

      GetStringFromAttribute( szXMD_FileTemp, zsizeof( szXMD_FileTemp ), vTaskLPLR, "LPLR", "ExecDir" );
      strcat_s( szXMD_FileTemp, zsizeof( szXMD_FileTemp ), "\\ZEIDON.XMD" );
      SysConvertEnvironmentString( szXMD_FileSpec, zsizeof( szXMD_FileSpec ), szXMD_FileTemp );
      hXMD_File = SysOpenFile( vTaskLPLR, szXMD_FileSpec, COREFILE_READ );
      if ( hXMD_File >= 0 )
      {
         SysGetFileDateTime( hXMD_File, szXMD_DateTime, zsizeof( szXMD_DateTime ) );
         SysCloseFile( vTaskLPLR, hXMD_File, 0 );
      }
      else
         szXMD_DateTime[ 0 ] = 0;

      if ( vTZEREMDO_REF )
      {
         GetStringFromAttribute( szEMD_DateTime, zsizeof( szEMD_DateTime ), vTZEREMDO_REF, "EntpER_Model", "LastSyncDate" );
         if ( szEMD_DateTime[ 0 ] == 0 )
         {
            RetrieveViewForMetaList( vSubtask, &vT, zREFER_ERD_META );
            GetStringFromAttribute( szEMD_DateTime, zsizeof( szEMD_DateTime ), vT, "W_MetaDef", "LastUpdateDate" );
            DropView( vT );
         }
      }
      else
         szEMD_DateTime[ 0 ] = 0;

      if ( lTE_ZKey > 0 )
      {
         RetrieveViewForMetaList( vSubtask, &vT, zREFER_DTE_META );
         SetCursorFirstEntityByInteger( vT, "W_MetaDef", "CPLR_ZKey", lTE_ZKey, "" );
         GetStringFromAttribute( szDTE_DateTime, zsizeof( szDTE_DateTime ), vT, "W_MetaDef", "LastUpdateDate" );
         DropView( vT );
      }

      if ( (zstrcmp( szXMD_DateTime, szEMD_DateTime ) < 0  || zstrcmp( szXMD_DateTime, szDTE_DateTime ) < 0) && vTZTENVRO_REF )
      {
         // Use a work view so as not to alter position of DBMS_Source.
         CreateViewFromViewForTask( &vTZTENVR1, vTZTENVRO_REF, 0 );
         oTZEREMXO_BuildExecutableModel( vSubtask, 0, vTZEREMDO_REF, vTZTENVR1 );
         DropView( vTZTENVR1 );
      }

      // DGC 1999.07.13
      // Add date of ER to XOD.
      SetAttributeFromString( vTZZOXODO, "OBJECT", "ER_DATE", szEMD_DateTime );
   }

   GetStringFromAttribute( szLOD_Name, zsizeof( szLOD_Name ), vTZZOLODO, "LOD", "Name" );

   SetAttributeFromString( vTZZOXODO, "OBJECT", "NAME", szLOD_Name );
   SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "ZKey", vTZZOLODO, "LOD", "ZKey" );
   if ( SetCursorFirstEntity( vTZZOLODO, "LOD_ConstraintOper", "" ) >= zCURSOR_SET )
   {
      zCHAR  szTempName[ 256 ] = "";
      zCHAR  szType[ 256 ];
      zLONG  lLth;

      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OCEOPER", vTZZOLODO, "LOD_ConstraintOper", "C_GeneratedOperationName" );

      // KJS 10/15/14 - Set the SourceFile Name, Extension.
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OCSRCTYPE", vTZZOLODO, "SourceFileForOCOper", "Extension" );

      GetStringFromAttribute( szType, zsizeof( szType ), vTZZOLODO, "SourceFileForOCOper", "Extension" );

      // If the source file is VML or Java, then we want to get the JavaPackageName.
      if ( vTaskLPLR && ( szType[ 0 ] == 'V' || szType[ 0 ] == 'J' ) )
      {
         zPCHAR pchSlash;

         GetStringFromAttribute( szTempName, zsizeof( szTempName ), vTaskLPLR, "LPLR", "JavaPackageName" );
         while ( (pchSlash = zstrchr( szTempName, '\\' )) != 0 )
            *pchSlash = '.';
      }

      lLth = zstrlen( szTempName );
      if ( lLth > 0 )
         szTempName[ lLth++ ] = '.';

      GetStringFromAttribute( szTempName + lLth, zsizeof( szTempName ) - lLth, vTZZOLODO, "SourceFileForOCOper", "Name" );

      // We only want the _Object extension, if this is VML that we are converting into java.
      if ( szType[ 0 ] == 'V' )
         strcat_s( szTempName, zsizeof( szTempName ), "_Object" );

      SetAttributeFromString( vTZZOXODO, "OBJECT", "OCSRCFILE", szTempName );
   //                         vTZZOLODO, "SourceFileForOCOper", "Name" );

      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OCACT", vTZZOLODO, "LOD", "ActivateConstraint" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OCACTE", vTZZOLODO, "LOD", "ActivateEmptyConstraint" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OCCOM", vTZZOLODO, "LOD", "CommitConstraint" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OCDROP", vTZZOLODO, "LOD", "DropOIConstraint" );
   }

   SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "NETCOMPRESS", vTZZOLODO, "LOD", "NetCompressedFlag" );
   nRC = CompareAttributeToString( vTZZOLODO, "LOD", "DLL_Name", "" );
   if ( nRC == 0 )
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OPER_LIBNM", vTZZOLODO, "LOD", "Name" );
   else
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OPER_LIBNM", vTZZOLODO, "LOD", "DLL_Name" );

   if ( vTZTENVRO_REF )
   {
      CreateViewFromViewForTask( &vTZZOLOD1, vTZZOLODO, 0 );
      CreateViewFromViewForTask( &vTZZOXOD1, vTZZOXODO, 0 );

      CreateEntity( vTZZOXODO, "OBJECT", zPOS_LAST );
      CreateViewFromViewForTask( &vTZTENVR1, vTZTENVRO_REF, 0 );
      CreateViewFromViewForTask( &vTZZOXODO_Root, vTZZOXODO, 0 );
      ofnTZZOXODO_BldXOD( vSubtask, vTZZOXODO_Root, vTZZOXODO, vTZZOLOD1, vTZEREMDO_REF, vTZTENVRO_REF );

      SetMatchingAttributesByName( vTZZOXODO, "OBJECT", vTZZOXOD1, "OBJECT", zSET_KEYS | zSET_NULL );
      SetViewFromView( vTZTENVRO_REF, vTZTENVR1 );

      DropView( vTZTENVR1 );
      DropView( vTZZOXODO_Root );
      SetViewFromView( vTZZOLOD1, vTZZOLODO );

      DeleteEntity( vTZZOXOD1, "OBJECT", zREPOS_FIRST );
      DropView( vTZZOLOD1 );
      DropView( vTZZOXOD1 );

      if ( CheckExistenceOfEntity( vTZZOXODO, "OBJECT" ) < zCURSOR_SET )
      {
         MessageSend( vSubtask, "ZO00304", "Operations",
                      "Root Entity is not in the TE Physical Model.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( zCALL_ERROR );
      }

      GetViewByName( &vTZTEDBLO, "TZTEDBLO", vSubtask, zLEVEL_TASK );
      if ( vTZTEDBLO == 0 )
      {
         ActivateOI_FromFile( &vTZTEDBLO, "tztedblo", vTZZOLODO, "tztedblo.xdl", zMULTIPLE );
         SetNameForView( vTZTEDBLO, "TZTEDBLO", vSubtask, zLEVEL_TASK );
      }

      SetCursorFirstEntityByAttr( vTZTEDBLO, "TE_DBMS_Source", "DBMS", vTZTENVRO_REF, "TE_DBMS_Source", "DBMS", 0 );

      if ( CompareAttributeToString( vTZTEDBLO, "TE_DBMS_Source", "DBS_PostXOD_BuildHook", "Y" ) == 0 )
      {
         zPCHAR    pszExecutable;
         LPLIBRARY hLibrary;
         zSHORT    (POPERATION pfnHook) ( zVIEW, zVIEW, zVIEW, zVIEW, zVIEW );

         GetAddrForAttribute( &pszExecutable, vTZTEDBLO, "TE_DBMS_Source", "GenerateExecutable" );
         hLibrary = SysLoadLibrary( vTZZOLODO, pszExecutable );
         pfnHook = (zSHORT (__stdcall *)(zVIEW, zVIEW, zVIEW, zVIEW, zVIEW)) SysGetProc( hLibrary, "PostXOD_BuildHook" );
         if ( pfnHook == 0 )
         {
            zCHAR  szMsg[ 256 ];

            strcpy_s( szMsg, zsizeof( szMsg ), "Couldn't find BuildHook operation - PostXOD_BuildHook in " );
            strcat_s( szMsg, zsizeof( szMsg ), pszExecutable );
            SysMessageBox( vTZZOLODO, "Build XOD Error", szMsg, 1 );
         }
         else
         {
            nRC = (*pfnHook)( vTZTEDBLO, vTZZOXODO, vTZZOLODO, vTZEREMDO_REF, vTZTENVRO_REF );
            if ( nRC == zCALL_ERROR )
            {
               SysFreeLibrary( vTZZOLODO, hLibrary );
               return( zCALL_ERROR );
            }
         }

         SysFreeLibrary( vTZZOLODO, hLibrary );
      }
   }
   else
   {
      CreateViewFromViewForTask( &vTZZOXODO_Root, vTZZOXODO, 0 );
      ofnTZZOXODO_BldXOD( vSubtask, vTZZOXODO_Root, vTZZOXODO, vTZZOLODO, vTZEREMDO_REF, vTZTENVRO_REF );
      DropView( vTZZOXODO_Root );
   }

   // Tell core to reload the XOD.  First get a subtask view to the application.  If SourceLPLR and TargetLPLR are defined,
   // then we are doing a migrate and we don't want to drop the view object because we get errors.
   if ( GetViewByName( &vT, "TargetLPLR", vSubtask, zLEVEL_TASK ) < 0 && GetViewByName( &vT, "SourceLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      GetStringFromAttribute( szAppName, zsizeof( szAppName ), vTaskLPLR, "LPLR", "Name" );
      SfCreateSubtask( &vSubtask, vSubtask, szAppName );
      DropViewObject( vSubtask, szLOD_Name, FALSE );
      SfDropSubtask( vSubtask, 0 );
   }

   return( 0 );
}

/*
   Sequence attributes are used to automatically sort entities.  We allow the
   user to sort entities using the values of child entities if the child entity has a 1-1 relationship.

   To make things quicker and easier for Core we will change the sequencing
   attributes for entity 'P' belong to child entity 'C' if:

   o  The attribute is a key of 'C'.
   o  The entity has a 1-1 relationship with 'P'.

   We will change the sequencing to be in 'P' using the Foreign Key.
*/
zVOID LOCALOPER
fnResetSequenceAttributes( zVIEW vXOD )
{
   zSHORT  nRC;
   zVIEW   vT;
   zVIEW   vXOD2 = 0;
   zCHAR   szEntityName[ zZEIDON_NAME_LTH + 1 ];
   zLONG   lPos;
   zBOOL   bFoundEntity;

   // First we will create a temporary OI to keep track of child entities that
   // have a 1-1 relationship with the parent.  In this temp OI the attribute
   // ENTITY.MAX_LTH will contain the absolute position of the child entity.
   ActivateEmptyObjectInstance( &vT, "TZZOXODO", vXOD, zSINGLE );
   CreateEntity( vT, "OBJECT", zPOS_FIRST );

   // Create a temp copy so we can muck with cursors.
   CreateViewFromViewForTask( &vXOD, vXOD, 0 );

   // Go through all the entities in vTZZOXODO and look for child entities.
   // To make it easier we will just go through hierarchially.
   // We'll start looking after the first "ENTITY" because we don't care about the root.
   lPos = 3;

   // We'll assume that there are no entities with a 1-1 relationship with its parent.
   bFoundEntity = FALSE;

   for ( nRC = SetCursorAbsolutePosition( szEntityName, vXOD, lPos );
         nRC > zCURSOR_NULL;
         nRC = SetCursorAbsolutePosition( szEntityName, vXOD, lPos++ ) )
   {
      // If we didn't find a child entity for this csr then skip it.
      if ( zstrcmp( szEntityName, "ENTITY" ) != 0 )
         continue;

      GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vXOD, "ENTITY", "NAME" );

      // Do a reset view from parent so we can access the CARDMAX attribute.
      ResetViewFromSubobject( vXOD );

      if ( CompareAttributeToString( vXOD, "CHILDENTITY", "NAME", szEntityName ) != 0 )
         SysMessageBox( vXOD, "DGC", "We have an error", 1 );

      // If the CardMax for the child entity is > 1 then we can't do anything with the sequence numbers so forget it.
      if ( CompareAttributeToInteger( vXOD, "CHILDENTITY", "CARDMAX", 1 ) > 0 )
         continue;

      bFoundEntity = TRUE;

      // Create an entity in our temp OI.
      CreateEntity( vT, "ENTITY", zPOS_LAST );
      SetAttributeFromAttribute( vT, "ENTITY", "NAME", vXOD, "CHILDENTITY", "NAME" );
      SetAttributeFromInteger( vT, "ENTITY", "MAX_LTH", lPos );
   }

   // If we didn't find an entity with a 1-1 relationship then let's get out.
   if ( bFoundEntity == FALSE )
      goto EndOfFunction;

   // Create another view of XOD.
   CreateViewFromViewForTask( &vXOD2, vXOD, 0 );

   // Now we'll back up through the entities and look for sequence fields that are also keys.
   for ( nRC = SetCursorLastEntity( vT, "ENTITY", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorPrevEntity( vT, "ENTITY", 0 ) )
   {
      zLONG lSeqNum;
      zLONG lTok;

      // Get the absolute position from vT and set vXOD accordingly.
      GetIntegerFromAttribute( &lPos, vT, "ENTITY", "MAX_LTH" );
      SetCursorAbsolutePosition( szEntityName, vXOD, lPos );

      // Look to see if there are any sequence numbers in the entity.
      for ( nRC = SetCursorFirstEntity( vXOD, "ATTRIB", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vXOD, "ATTRIB", 0 ) )
      {
         GetIntegerFromAttribute( &lSeqNum, vXOD, "ATTRIB", "SEQUENCING" );
         if ( lSeqNum == 0 )
            continue;

         // If the sequencing attribute is not a key then got to next attrib.
         if ( CompareAttributeToString( vXOD, "ATTRIB", "KEY", "Y" ) != 0 )
            continue;

         // Find the *target* attribute token for the key.  This should be the FK of the parent.
         // First find the source RelField.
         GetIntegerFromAttribute( &lTok, vXOD, "ATTRIB", "XVAATT_TOK" );
         if ( SetCursorFirstEntityByInteger( vXOD, "RELFIELD", "SRCXVAATT_TOK", lTok, "ENTITY" ) < zCURSOR_SET )
         {
            continue;  // No source rel field so forget it.
         }

         // Get the target rel field token.
         GetIntegerFromAttribute( &lTok, vXOD, "RELFIELD", "RELXVAATT_TOK" );

         // No try to find the attribute that matches lTok.  This should be the FK in the parent.
         // We'll do this by looking in each parent for a match.
         SetViewFromView( vXOD2, vXOD );
         do
         {
            ResetViewFromSubobject( vXOD2 );
         } while ( SetCursorFirstEntityByInteger( vXOD2, "ATTRIB", "XVAATT_TOK", lTok, 0 ) < zCURSOR_SET );

         // Set the sequencing number for the FK and turn off sequencing in the original attribute.
         SetAttributeFromInteger( vXOD2, "ATTRIB", "SEQUENCING", lSeqNum );
         SetAttributeFromAttribute( vXOD2, "ATTRIB", "SEQ_AD", vXOD,  "ATTRIB", "SEQ_AD" );
         SetAttributeFromString( vXOD, "ATTRIB", "SEQUENCING", "" );
         SetAttributeFromString( vXOD, "ATTRIB", "SEQ_AD", "" );

      } // for ( nRC = SetCursorFirstEntity( vXOD, "ATTRIB", 0 )...

   } // for ( nRC = SetCursorLastEntity( vT, "ENTITY", 0 )...

EndOfFunction:
   if ( vXOD2 )
      DropView( vXOD2 );

   DropView( vXOD );
   DropView( vT );

} // fnResetSequenceAttributes

/*
   Makes sure that a recursive entity and it's (recursive) parent both have the same work attributes.
*/
void
fnCopyRecursiveWorkAttributes( zVIEW vChild )
{
   zVIEW  vParent;
   zSHORT nRC;

   CreateViewFromViewForTask( &vParent, vChild, 0 );

   // Find the recursive parent.
   do
   {
      ResetViewFromSubobject( vParent );
   } while ( CompareAttributeToAttribute( vChild, "ENTITY", "ERENT_TOK", vParent, "ENTITY", "ERENT_TOK" ) != 0 );

   // Make sure all work attributes that exist in the parent are in the child.
   for ( nRC = SetCursorFirstEntity( vParent, "ATTRIB", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vParent, "ATTRIB", 0 ) )
   {
      // If attrib isn't a work attrib skip it.
      if ( CompareAttributeToString( vParent, "ATTRIB", "PERSIST", "Y" ) == 0 )
         continue;

      // See if we can find the attr by NAME in the child.
      if ( SetCursorFirstEntityByAttr( vChild, "ATTRIB", "NAME", vParent, "ATTRIB", "NAME", 0 ) < zCURSOR_SET )
      {
         // Attr doesn't exist so create it.
         CreateEntity( vChild, "ATTRIB", zPOS_LAST );
      }

      // Now copy all the attrib info from parent to child.  This might not be necessary because the info *should* be the
      // same anyway.  Doing this enforces it.
      SetMatchingAttributesByName( vChild, "ATTRIB", vParent, "ATTRIB", zSET_ALL );
   }

   // Now make sure all child attrs exist in the parent.
   for ( nRC = SetCursorFirstEntity( vChild, "ATTRIB", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vChild, "ATTRIB", 0 ) )
   {
      // If attrib isn't a work attrib skip it.
      if ( CompareAttributeToString( vChild, "ATTRIB", "PERSIST", "Y" ) == 0 )
         continue;

      // See if we can find the attr by NAME in the child.
      if ( SetCursorFirstEntityByAttr( vParent, "ATTRIB", "NAME", vChild, "ATTRIB", "NAME", 0 ) >= zCURSOR_SET )
      {
         // Attr exists so skip it.
         continue;
      }

      // Create attr in the parent and copy attributes.
      CreateEntity( vParent, "ATTRIB", zPOS_LAST );
      SetMatchingAttributesByName( vParent, "ATTRIB", vChild, "ATTRIB", zSET_ALL );
   }

   DropView( vParent );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldXOD
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXOD( zVIEW vSubtask, zVIEW vTZZOXODO_Root,
                    zVIEW vTZZOXODO, zVIEW vTZZOLODO,
                    zVIEW vTZEREMDO_REF, zVIEW vTZTENVRO_REF )
{
   zVIEW  vTZZOLOD1;
   zCHAR  szDEBUGCHG[ zZEIDON_NAME_LTH + 1 ];
   zPCHAR pszParadigm;
   zPCHAR pszNetwork;
   zPCHAR lpszXOD_Name;
   zLONG  lAttrCount = 0;
   zLONG  lEntityZKey;
   zLONG  lAttribZKey;
   zLONG  lEntityLth;
   zLONG  lAttribLth;
   zSHORT nRC;

   // nDerivedFlag tells me, whether the current Entity or any of its parents is derived.
   zSHORT nDerivedFlag;

   if ( vTZTENVRO_REF )
   {
      GetAddrForAttribute( &pszParadigm, vTZTENVRO_REF, "TE_DBMS_Source", "Paradigm" );
      GetAddrForAttribute( &pszNetwork, vTZTENVRO_REF,  "TE_DBMS_Source", "Network" );
   }
   else
   {
      pszNetwork = pszParadigm = "";
   }


   // If network is not null, then set network information.
   if ( *pszNetwork )
   {
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "DFT_DBNAME", vTZTENVRO_REF, "TE_DBMS_Source", "Name" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "NETWORK", vTZTENVRO_REF, "TE_DBMS_Source", "Network" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "LOCK", vTZZOLODO, "LOD", "DataLocking" );
   }
   else
   if ( *pszParadigm )
   {
      // Stuff that's common to all physical paradigms.  Note that for network stuff none of this stuff is set.
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "DFT_DBNAME", vTZTENVRO_REF, "TE_DBMS_Source", "Name" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "DATABASE", vTZTENVRO_REF, "TE_DBMS_Source", "Name" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "HANDLER", vTZTENVRO_REF, "TE_DBMS_Source", "Executable" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "GKHANDLER", vTZTENVRO_REF, "TE_DBMS_Source", "GenKeyExecutable" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "SironDB_Type", vTZTENVRO_REF, "TE_DBMS_Source", "SironDB_Type" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "CACHENUM", vTZZOLODO, "LOD", "CacheNumberPerEntity" );
      SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "LOCK", vTZZOLODO, "LOD", "DataLocking" );

      // Stuff specific to paradigms.
      switch ( *pszParadigm )
      {
         case 'N':
            SetAttributeFromInteger( vTZZOXODO, "OBJECT", "OFRECID", 10000 );
            SetAttributeFromAttribute( vTZZOXODO, "OBJECT", "OFBUFSZ", vTZTENVRO_REF, "TE_DBMS_Source", "OverflowAttrLth" );
            break;

         case 'R':
            break;
      }
   }

   SysReadZeidonIni( -1, "[Debug]", "DEBUGCHG", szDEBUGCHG, zsizeof( szDEBUGCHG ) ); // currently Java Debug only

   CreateViewFromViewForTask( &vTZZOLOD1, vTZZOLODO, 0 );

   SetCursorFirstEntity( vTZZOLOD1, "LOD_EntityParent", "" );
   CreateEntity( vTZZOXODO, "ENTITY", zPOS_AFTER );
   ofnTZZOXODO_BldXODEntity( vSubtask, vTZZOXODO, vTZZOLOD1 );

   // If the LOD was built with TE (vTZTENVRO_REF view exists) and the LOD_Entity is for entity in data model (ER_EntityRec exists),
   // then position on the corresponding table in TE using the ER_Entity.
   if ( vTZTENVRO_REF &&
        CheckExistenceOfEntity( vTZZOLOD1, "ER_EntityRec" ) >= zCURSOR_SET &&
        CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 )
   {
      GetIntegerFromAttribute( &lEntityZKey, vTZZOLOD1, "ER_EntityRec", "ZKey" );
      nRC = SetCursorFirstEntityByInteger( vTZTENVRO_REF, "ER_Entity", "ZKey", lEntityZKey, "TE_DBMS_Source" );
      if ( nRC < zCURSOR_SET )
      {
         zCHAR    szMsg[ 500 ];
         zPCHAR   pchMsgName;

         strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Entity in TE Data Source.\n\nEntity Name = " );
         GetAddrForAttribute( &pchMsgName, vTZZOLOD1, "ER_EntityRec", "Name" );
         strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
         strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );
         MessageSend( vSubtask, "ZO00305", "Operations", szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( 0 );
      }
   }

   if ( *pszParadigm &&
        CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Work", "Y" ) != 0 &&
        CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 )
   {
      // Build physical data record.
      CreateEntity( vTZZOXODO, "DATARECORD", zPOS_AFTER );
      ofnTZZOXODO_BldXODDataRec( vSubtask, vTZZOXODO, vTZTENVRO_REF, vTZZOLOD1 );
   }

   // On 3/08/2010, DonC made the following change so that attributes would be built in their proper order, which
   // is the order under LOD_Entity and not LOD_EntityParent. The order under LOD_Entity is the order you see from the
   // LOD maintenance dialog and the order in which you want them to appear in the Object Browser.
   // A similar change was made on 1/29/2010 for the XOD Child Entity, but the root was forgotten.
   SetCursorFirstEntityByEntityCsr( vTZZOLOD1, "LOD_Entity", vTZZOLOD1, "LOD_EntityParent", 0 );
   for ( nRC = SetCursorFirstEntity( vTZZOLOD1, "LOD_Attribute", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vTZZOLOD1, "LOD_Attribute", 0 ) )
   {
     SetCursorFirstEntityByEntityCsr( vTZZOLOD1, "LOD_AttributeRec", vTZZOLOD1, "LOD_Attribute", 0 );

   //for ( nRC = SetCursorFirstEntity( vTZZOLOD1, "LOD_AttributeRec", 0 );
   //      nRC >= zCURSOR_SET;
   //      nRC = SetCursorNextEntity( vTZZOLOD1, "LOD_AttributeRec", 0 ) )
   //{
   // End of DonC change
      CreateEntity( vTZZOXODO, "ATTRIB", zPOS_AFTER );
      lAttrCount++;
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", lAttrCount );
      ofnTZZOXODO_BldXODAttrib( vSubtask, vTZZOXODO, vTZZOLOD1, vTZEREMDO_REF, szDEBUGCHG );

      if ( *pszParadigm &&
           CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "Work", "Y" ) != 0 &&
           CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "Work", "Y" ) != 0 &&
           CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 )
      {
         if ( SetCursorFirstEntityByAttr( vTZTENVRO_REF, "ER_Attribute", "ZKey", vTZZOLOD1, "ER_AttributeRec", "ZKey", "TE_TablRec" ) < zCURSOR_SET )
         {
            if ( SetCursorFirstEntityByAttr( vTZTENVRO_REF, "ER_Attribute", "Name", vTZZOLOD1, "ER_AttributeRec", "Name", "TE_TablRec" ) < zCURSOR_SET )
            {
               zCHAR    szMsg[500];
               zPCHAR   pchMsgName;

               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Attribute in TE.\n\nAttr Name = " );
               GetAddrForAttribute( &pchMsgName, vTZZOLOD1, "ER_AttributeRec", "Name" );
               strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
               strcat_s( szMsg, zsizeof( szMsg ), "\nfor entity: " );
               GetAddrForAttribute( &pchMsgName, vTZZOLOD1, "ER_EntityRec", "Name" );
               strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
               strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );
               MessageSend( vSubtask, "ZO00306", "Operations",
                            szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               break;
            }
         }

         CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_AFTER );
         ofnTZZOXODO_BldXODDataField( vSubtask, vTZZOXODO, vTZTENVRO_REF );
      }
   }

   // Process any Duplicate Entities to make sure they have all necessary ER attributes.
   ofnTZZOXODO_ProcDupEntity( vSubtask, vTZZOXODO, vTZEREMDO_REF, vTZTENVRO_REF, vTZZOLOD1, &lAttrCount );

   // Complete any ATTRIB entries that have a DB_OPER specification.
   ofnTZZOXODO_BldDB_DataFields( vTZZOXODO, vTZZOLOD1 );

   // We'll assume that we have all the ER attributes in the entity.  If we don't we will turn off the flag later.
   SetAttributeFromString( vTZZOXODO, "ENTITY", "FULLPERSIST", "Y" );

   // Build hidden attributes.
   if ( CheckExistenceOfEntity( vTZZOLOD1, "ER_EntityRec" ) >= zCURSOR_SET &&
        SetCursorFirstEntityByEntityCsr( vTZEREMDO_REF, "ER_Entity", vTZZOLOD1, "ER_EntityRec", 0 ) >= zCURSOR_SET )
   {
      // Loop through all ER attributes.  If it's not part of the LOD, then it's a hidden attribute.
      for ( nRC = SetCursorFirstEntity( vTZEREMDO_REF, "ER_Attribute", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vTZEREMDO_REF, "ER_Attribute", 0 ) )
      {
         // Skip if it's part of LOD_Entitiy.
         if ( SetCursorFirstEntityByEntityCsr( vTZZOLOD1, "ER_AttributeRec", vTZEREMDO_REF, "ER_Attribute", "LOD_EntityParent" ) >= zCURSOR_SET )
         {
            continue;
         }

         // Skip if it's a work attribute.
         if ( CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "Work", "Y" ) == 0 )
         {
            continue;
         }

         // Entity does not contain all the persistent attributes.
         SetAttributeFromString( vTZZOXODO, "ENTITY", "FULLPERSIST", "" );

         CreateEntity( vTZZOXODO, "ATTRIB", zPOS_AFTER );
         lAttrCount++;
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", lAttrCount );
         ofnTZZOXODO_BldXODAttribHidden( vSubtask, vTZZOXODO, vTZEREMDO_REF, szDEBUGCHG );

      // if ( *pszParadigm == 0 || *pszNetwork )
      //    continue;

         if ( *pszParadigm &&
              (CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "ParticipatesInKey", "Y" ) == 0 ||
               (CheckExistenceOfEntity( vTZZOLOD1, "LOD_AttributeRec" ) >= zCURSOR_SET &&
                CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "Work", "Y" ) != 0  &&
                CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "Work", "Y" ) != 0  &&
                CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0)) )
         {
            GetIntegerFromAttribute( &lAttribZKey, vTZEREMDO_REF, "ER_Attribute", "ZKey" );
            nRC = SetCursorFirstEntityByInteger( vTZTENVRO_REF, "ER_Attribute", "ZKey", lAttribZKey, "TE_TablRec" );
            if ( nRC < zCURSOR_SET )
            {
               zCHAR    szMsg[ 500 ];
               zPCHAR   pchMsgName;

               strcpy_s( szMsg, zsizeof(szMsg), "Unable to Find Attribute in TE.\n\nAttr Name = " );
               GetAddrForAttribute( &pchMsgName, vTZTENVRO_REF, "ER_Attribute", "Name" );
               strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
               strcat_s( szMsg, zsizeof( szMsg ), "\nfor entity: " );
               GetAddrForAttribute( &pchMsgName, vTZZOLOD1, "ER_EntityRec", "Name" );
               strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
               strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );
               MessageSend( vSubtask, "ZO00307", "Operations",
                            szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               break;
            }

            CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_AFTER );
            ofnTZZOXODO_BldXODDataField( vSubtask, vTZZOXODO, vTZTENVRO_REF );
         }
      } // for...
   }

   SetCursorFirstEntity( vTZZOLOD1, "LOD_AttributeRec", 0 );

   if ( *pszParadigm )
   {
      // Loop for all data fields.  If there is no ER_Attribute record defined under the field, then it's either a GenKey
      // field or an AutoSeq field.  Add either accordingly.
      for ( nRC = SetCursorFirstEntityByString( vTZTENVRO_REF, "TE_FieldDataRel", "DataOrRelfieldOrSet", "D", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntityByString( vTZTENVRO_REF, "TE_FieldDataRel", "DataOrRelfieldOrSet", "D", 0 ) )
      {
         if ( CheckExistenceOfEntity( vTZTENVRO_REF, "ER_Attribute" ) >= zCURSOR_SET )
         {
            continue;
         }

         CreateEntity( vTZZOXODO, "ATTRIB", zPOS_LAST );
         lAttrCount++;
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", lAttrCount );

         if ( CheckExistenceOfEntity( vTZTENVRO_REF, "ER_RelLink" ) >= zCURSOR_SET )
         {
//          if ( CheckExistenceOfEntity( vTZZOXODO, "DATARECORD" ) >= zCURSOR_SET )
            {
               // Field is an AutoSeq field.
               ofnTZZOXODO_BldAutoSeq( vSubtask, vTZZOXODO, vTZTENVRO_REF, vTZZOLOD1 );
            }
         }
         else
         {
            // Field is a GenKey.
            ofnTZZOXODO_BldAttribGK( vTZZOXODO, vTZTENVRO_REF );
            CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_LAST );
            ofnTZZOXODO_BldDataFieldGK( vTZZOXODO, vTZTENVRO_REF );
         }
      }

      SetNameForView( vTZZOLOD1, "TZZOLOD1", vSubtask, zLEVEL_TASK );

      // Create the foreign keys for relational databases.
      if ( *pszParadigm == 'R' &&
           CheckExistenceOfEntity( vTZZOLOD1, "ER_EntityRec" ) >= zCURSOR_SET &&
           CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 )

      {
         for ( nRC = SetCursorFirstEntityByString( vTZTENVRO_REF, "TE_FieldDataRel", "DataOrRelfieldOrSet", "R", 0 );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntityByString( vTZTENVRO_REF, "TE_FieldDataRel", "DataOrRelfieldOrSet", "R", "" ) )
         {
            CreateEntity( vTZZOXODO, "ATTRIB", zPOS_LAST );
            lAttrCount++;
            SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", lAttrCount );
            SetAttributeFromString( vTZZOXODO, "ATTRIB", "FORKEY", "Y" );
            ofnTZZOXODO_BldAttribFK( vTZZOXODO, vTZTENVRO_REF, vTZZOLOD1 );

            if ( CheckExistenceOfEntity( vTZZOXODO, "DATARECORD" ) >= zCURSOR_SET )
            {
               CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_LAST );
               ofnTZZOXODO_BldDataFieldFK( vTZZOXODO, vTZTENVRO_REF );
            }
         }
      }
   }

   // Loop through the ATTRIB entities to compute the total length and put that length in the ENTITY.
   lEntityLth = 0;
   for ( nRC = SetCursorFirstEntity( vTZZOXODO, "ATTRIB", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vTZZOXODO, "ATTRIB", 0 ) )
   {
      zPCHAR psz;

      GetAddrForAttribute( &psz, vTZZOXODO, "ATTRIB", "TYPE" );
      switch ( *psz )
      {
         case zTYPE_DATETIME:
            lEntityLth = lEntityLth + 18;
            break;

         case zTYPE_DECIMAL:
            lEntityLth = lEntityLth + 22;
            break;

         case zTYPE_INTEGER:
            lEntityLth = lEntityLth + 11;
            break;

         case zTYPE_BLOB:
            lEntityLth = lEntityLth + 0;
            break;

         default:
            // Must be String or other type using LTH.
            GetIntegerFromAttribute( &lAttribLth, vTZZOXODO, "ATTRIB", "LTH" );
            lEntityLth = lEntityLth + lAttribLth + 1;
      }
   }

   SetAttributeFromInteger( vTZZOXODO, "ENTITY", "MAX_LTH", lEntityLth );

   // nDerivedFlag tells me whether the current Entity or any of its parents is derived.
   nRC = CheckExistenceOfEntity( vTZZOLOD1, "LOD_EntityChild" );
   if ( nRC >= zCURSOR_SET )
   {
      if ( CompareAttributeToString( vTZZOXODO, "ENTITY", "DERIVED", "Y" ) == 0 )
         nDerivedFlag = 1;
      else
         nDerivedFlag = 0;

      ofnTZZOXODO_BldXODChildEnt( vSubtask, vTZZOXODO_Root, vTZZOXODO, vTZZOLOD1,
                                  vTZEREMDO_REF, vTZTENVRO_REF, pszParadigm, pszNetwork, &lAttrCount,
                                  nDerivedFlag, szDEBUGCHG );

      // For relational DB's we need to change the sequencing attributes so that we sequence FK's instead of keys.
      if ( *pszParadigm == 'R' )
         fnResetSequenceAttributes( vTZZOXODO );
   }

   DropView( vTZZOLOD1 );

   // Create prototypes for all the operations that are global in scope and merge them into the external header file.
   GetAddrForAttribute( &lpszXOD_Name, vTZZOLODO, "LOD", "Name" );
   MergeGlobalPrototypes( vTZZOLODO, lpszXOD_Name, "LOD", 0 );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldXODChildEnt
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODChildEnt( zVIEW  vSubtask, zVIEW  vTZZOXODO_Root,
                            zVIEW  vTZZOXODO,
                            zVIEW  vTZZOLOD1,
                            zVIEW  vTZEREMDO_REF,
                            zVIEW  vTZTENVRO_REF,
                            zPCHAR pszParadigm,
                            zPCHAR pszNetwork,
                            zPLONG plAttrCount,
                            zSHORT nDerivedFlag,
                            zCPCHAR cpcDEBUGCHG )
{
   zVIEW  vTZTENVRO_Parent;
   zVIEW  vTZZOLODO_Parent;
   zVIEW  vTZZOLODR;   // Positioned on Root view
   zLONG  lEntityZKey;
   zLONG  lAttribZKey;
   zLONG  lEntityLth;
   zLONG  lAttribLth;
   zSHORT nAutoLoadFlag;
   zSHORT nRC;

   if ( vTZTENVRO_REF )
      CreateViewFromViewForTask( &vTZTENVRO_Parent, vTZTENVRO_REF, 0 );
   else
      vTZTENVRO_Parent = 0;

   for ( nRC = SetCursorFirstEntity( vTZZOLOD1, "LOD_EntityChild", 0 );
         nRC >= zCURSOR_SET;
         nRC  = SetCursorNextEntity( vTZZOLOD1, "LOD_EntityChild", 0 ) )
   {
      CreateViewFromViewForTask( &vTZZOLODO_Parent, vTZZOLOD1, 0 );

      SetViewToSubobject( vTZZOLOD1, "LOD_EntityChild" );
      SetViewToSubobject( vTZZOXODO, "CHILDENTITY" );

      // nDerivedFlag tells me, whether the current Entity or any of its parents is derived.
      if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Derived", "Y" ) == 0 )
         nDerivedFlag = 1;

      CreateEntity( vTZZOXODO, "ENTITY", zPOS_AFTER );
      ofnTZZOXODO_BldXODEntity( vSubtask, vTZZOXODO, vTZZOLOD1 );

      // If the entity is not a work entity then there should be a matching entity in the TE.  Set cursor to that entity.
      if ( *pszParadigm &&
           CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Work", "Y" ) != 0 &&
           CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 )
      {
         GetIntegerFromAttribute( &lEntityZKey, vTZZOLOD1, "ER_EntityRec", "ZKey" );
         nRC = SetCursorFirstEntityByInteger( vTZTENVRO_REF, "ER_Entity", "ZKey", lEntityZKey, "TE_DBMS_Source" );
         if ( nRC < zCURSOR_SET )
         {
            zCHAR    szMsg[500];
            zPCHAR   pchMsgName;

            strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Entity in TE Data Source with same DBMS.\n\nEntity Name = " );
            GetAddrForAttribute( &pchMsgName, vTZZOLOD1, "ER_EntityRec", "Name" );
            strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
            strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );
            MessageSend( vSubtask, "ZO00308", "Operations",
                         szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            DropView( vTZTENVRO_Parent );
            ResetViewFromSubobject( vTZZOLOD1 );
            ResetViewFromSubobject( vTZZOXODO );
            return( 0 );
         }

         CreateEntity( vTZZOXODO, "DATARECORD", zPOS_AFTER );
         ofnTZZOXODO_BldXODDataRec( vSubtask, vTZZOXODO, vTZTENVRO_REF, vTZZOLOD1 );
      }

      // Create the Attribute information.
     // On 1/29/2010, DonC made the following change so that attributes would be built in their proper order, which
     // is the order under LOD_Entity and not LOD_EntityParent. The order under LOD_Entity is the order you see from the
     // LOD maintenance dialog and the order in which you want them to appear in the Object Browser.
     CreateViewFromViewForTask( &vTZZOLODR, vTZZOLOD1, 0 );
     nRC = 0;
     ResetView( vTZZOLODR );   // Reset to top of subobjects.
     SetCursorFirstEntityByEntityCsr( vTZZOLODR, "LOD_Entity", vTZZOLOD1, "LOD_EntityParent", 0 );
      for ( nRC = SetCursorFirstEntity( vTZZOLODR, "LOD_Attribute", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vTZZOLODR, "LOD_Attribute", 0 ) )
      {
        SetCursorFirstEntityByEntityCsr( vTZZOLOD1, "LOD_AttributeRec", vTZZOLODR, "LOD_Attribute", 0 );
       // End of DonC change
         CreateEntity( vTZZOXODO, "ATTRIB", zPOS_AFTER );
         (*plAttrCount)++;
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", *plAttrCount );
         ofnTZZOXODO_BldXODAttrib( vSubtask, vTZZOXODO, vTZZOLOD1, vTZEREMDO_REF, cpcDEBUGCHG );

         if ( *pszParadigm &&
              CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "Work", "Y" ) != 0  &&
              CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "Work", "Y" ) != 0  &&
              CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 )
         {
            if ( SetCursorFirstEntityByAttr( vTZTENVRO_REF, "ER_Attribute", "ZKey", vTZZOLOD1, "ER_AttributeRec", "ZKey", "TE_TablRec" ) < zCURSOR_SET )
            {
               if ( SetCursorFirstEntityByAttr( vTZTENVRO_REF, "ER_Attribute", "Name", vTZZOLOD1, "ER_AttributeRec", "Name", "TE_TablRec" ) < zCURSOR_SET )
               {
                  zCHAR    szMsg[500];
                  zPCHAR   pchMsgName;

                  strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Attribute in TE.\n\nAttr Name = " );
                  GetAddrForAttribute( &pchMsgName, vTZZOLOD1, "ER_AttributeRec", "Name" );
                  strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
                  strcat_s( szMsg, zsizeof( szMsg ), "\nfor entity: " );
                  GetAddrForAttribute( &pchMsgName, vTZZOLOD1, "ER_EntityRec", "Name" );
                  strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
                  strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );
                  MessageSend( vSubtask, "ZO00309", "Operations",
                               szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               }
            }
            else
            {
               CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_AFTER );
               ofnTZZOXODO_BldXODDataField( vSubtask, vTZZOXODO, vTZTENVRO_REF );
            }
         }
      }
     DropView( vTZZOLODR );

      // Process any Duplicate Entities to make sure they have all necessary ER attributes.
      ofnTZZOXODO_ProcDupEntity( vSubtask, vTZZOXODO, vTZEREMDO_REF, vTZTENVRO_REF, vTZZOLOD1, plAttrCount );

      // Complete any ATTRIB entries that have a DB_OPER specification.
      ofnTZZOXODO_BldDB_DataFields( vTZZOXODO, vTZZOLOD1 );

      // We'll assume that we have all the ER attributes in the entity.  If we don't we will turn off the flag later.
      SetAttributeFromString( vTZZOXODO, "ENTITY", "FULLPERSIST", "Y" );

      if ( CheckExistenceOfEntity( vTZZOLOD1, "ER_EntityRec" ) >= zCURSOR_SET )
      {
         SetCursorFirstEntityByEntityCsr( vTZEREMDO_REF, "ER_Entity", vTZZOLOD1, "ER_EntityRec", 0 );
         for ( nRC = SetCursorFirstEntity( vTZEREMDO_REF, "ER_Attribute", 0 );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntity( vTZEREMDO_REF, "ER_Attribute", 0 ) )
         {
            nRC = SetCursorFirstEntityByEntityCsr( vTZZOLOD1, "ER_AttributeRec", vTZEREMDO_REF, "ER_Attribute", "LOD_EntityParent" );
            if ( nRC >= zCURSOR_SET )
               continue;

            // Skip if it's a work attribute.
            if ( CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "Work", "Y" ) == 0 )
            {
               continue;
            }

            // Entity does not contain all the persistent attributes.
            SetAttributeFromString( vTZZOXODO, "ENTITY", "FULLPERSIST", "" );

            CreateEntity( vTZZOXODO, "ATTRIB", zPOS_AFTER );
            (*plAttrCount)++;
            SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", *plAttrCount );
            ofnTZZOXODO_BldXODAttribHidden( vSubtask, vTZZOXODO, vTZEREMDO_REF, cpcDEBUGCHG );

            //if ( *pszParadigm == 0 || *pszNetwork != 0 )
            //   continue;

            if ( *pszParadigm &&
                 CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "Work", "Y" ) != 0  &&
                 CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 )
            {
               GetIntegerFromAttribute( &lAttribZKey, vTZEREMDO_REF, "ER_Attribute", "ZKey" );
               nRC = SetCursorFirstEntityByInteger( vTZTENVRO_REF, "ER_Attribute", "ZKey", lAttribZKey, "TE_TablRec" );
               if ( nRC < zCURSOR_SET )
               {
                  zCHAR    szMsg[ 500 ];
                  zPCHAR   pchMsgName;

                  strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Attribute in TE.\n\nAttr Name = " );
                  GetAddrForAttribute( &pchMsgName, vTZEREMDO_REF, "ER_Attribute", "Name" );
                  strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
                  strcat_s( szMsg, zsizeof( szMsg ), "\nfor entity: " );
                  GetAddrForAttribute( &pchMsgName, vTZZOLOD1, "ER_EntityRec", "Name" );
                  strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
                  strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );

                  MessageSend( vSubtask, "ZO00310", "Operations",
                               szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
                  break;
               }

               CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_AFTER );
               ofnTZZOXODO_BldXODDataField( vSubtask, vTZZOXODO, vTZTENVRO_REF );
            }
         } // for each ER_Attribute...

         if ( *pszParadigm &&
              CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 )
         {
            // Loop for all data fields.  If there is no ER_Attribute record defined under the field, then it's either
            // a GenKey field or an AutoSeq field. Add either accordingly.
            for ( nRC = SetCursorFirstEntityByString( vTZTENVRO_REF, "TE_FieldDataRel", "DataOrRelfieldOrSet", "D", 0 );
                  nRC >= zCURSOR_SET;
                  nRC = SetCursorNextEntityByString( vTZTENVRO_REF, "TE_FieldDataRel", "DataOrRelfieldOrSet", "D", 0 ) )
            {
               if ( CheckExistenceOfEntity( vTZTENVRO_REF, "ER_Attribute" ) >= zCURSOR_SET )
                  continue;

               CreateEntity( vTZZOXODO, "ATTRIB", zPOS_LAST );
               (*plAttrCount)++;
               SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", *plAttrCount );

               // If the entity is derived --> there is no datarecord--> don't build AutoSeq.
               if ( CheckExistenceOfEntity( vTZTENVRO_REF, "ER_RelLink" ) >= zCURSOR_SET )
               {
               // if ( CheckExistenceOfEntity( vTZZOXODO, "DATARECORD" ) >= zCURSOR_SET )
                  {
                     // Field is an AutoSeq field.
                     ofnTZZOXODO_BldAutoSeq( vSubtask, vTZZOXODO, vTZTENVRO_REF, vTZZOLOD1 );
                  }
               }
               else
               {
                  ofnTZZOXODO_BldAttribGK( vTZZOXODO, vTZTENVRO_REF );
                  CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_LAST );
                  ofnTZZOXODO_BldDataFieldGK( vTZZOXODO, vTZTENVRO_REF );
               }
            }

            // Build foreign keys for relational databases.
            if ( *pszParadigm == 'R' )
            {
               for ( nRC = SetCursorFirstEntityByString( vTZTENVRO_REF, "TE_FieldDataRel", "DataOrRelfieldOrSet", "R", 0 );
                     nRC >= zCURSOR_SET;
                     nRC = SetCursorNextEntityByString( vTZTENVRO_REF, "TE_FieldDataRel", "DataOrRelfieldOrSet", "R", 0 ) )
               {
                  CreateEntity( vTZZOXODO, "ATTRIB", zPOS_LAST );
                  (*plAttrCount)++;
                  SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", *plAttrCount );
                  SetAttributeFromString( vTZZOXODO, "ATTRIB", "FORKEY", "Y" );
                  ofnTZZOXODO_BldAttribFK( vTZZOXODO, vTZTENVRO_REF, vTZZOLOD1 );

                  // look for the DATARECORD:
                  if (  CheckExistenceOfEntity( vTZZOXODO, "DATARECORD") >= zCURSOR_SET )

                  {
                     CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_LAST );
                     ofnTZZOXODO_BldDataFieldFK( vTZZOXODO, vTZTENVRO_REF );
                  }
               }
            }

            if ( CompareAttributeToString( vTZZOLOD1, "ER_EntityRec", "Purpose", "W" ) != 0 &&
                 CompareAttributeToString( vTZZOLODO_Parent, "LOD_EntityParent", "Work", "Y" ) != 0 &&
                 CompareAttributeToString( vTZZOLODO_Parent, "ER_EntityRec", "Purpose", "W" ) != 0 )

            {
               CreateEntity( vTZZOXODO, "RELRECORD", zPOS_AFTER );
               ofnTZZOXODO_BldXODRelRec( vSubtask, vTZZOXODO, vTZTENVRO_REF, vTZZOLOD1, vTZTENVRO_Parent, pszParadigm, plAttrCount );
            }

         } // if ( *pszParadigm )...

         DropView( vTZZOLODO_Parent );

      } // if ( CheckExistenceOfEntity( vTZZOLOD1, "ER_EntityRec" ) >= zCURSOR_SET )...

      SetCursorFirstEntity( vTZZOLOD1, "LOD_AttributeRec", 0 );

      // Check to make sure that recursive entities have work attributes that match their recursive parents.
      // NOTE!
      // NOTE! This change does not keep XVAATT_TOKs in order.  This shouldn't be a problem because the tokens are only used
      // NOTE! for persistent attributes but someday we should probably change it so that the tokens are "correct".
      // NOTE!
      if ( CompareAttributeToString( vTZZOXODO, "ENTITY", "RECURSIVE", "Y" ) == 0 )
         fnCopyRecursiveWorkAttributes( vTZZOXODO );

      // Loop through the ATTRIB entities to compute the total length and put that length in the ENTITY.
      lEntityLth = 0;
      for ( nRC = SetCursorFirstEntity( vTZZOXODO, "ATTRIB", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vTZZOXODO, "ATTRIB", 0 ) )
      {
         zPCHAR psz;

         GetAddrForAttribute( &psz, vTZZOXODO, "ATTRIB", "TYPE" );
         switch ( *psz )
         {
            case zTYPE_DATETIME:
               lEntityLth = lEntityLth + 18;
               break;

            case zTYPE_DECIMAL:
               lEntityLth = lEntityLth + 22;
               break;

            case zTYPE_INTEGER:
               lEntityLth = lEntityLth + 11;
               break;

            case zTYPE_BLOB:
               lEntityLth = lEntityLth + 0;
               break;

            default:
               // Must be String or other type using LTH.
               GetIntegerFromAttribute( &lAttribLth, vTZZOXODO, "ATTRIB", "LTH" );
               lEntityLth = lEntityLth + lAttribLth + 1;
         }
      }

      // Go to process child entity.
      if ( CheckExistenceOfEntity( vTZZOLOD1, "LOD_EntityChild" ) >= zCURSOR_SET )
      {
         ofnTZZOXODO_BldXODChildEnt( vSubtask, vTZZOXODO_Root, vTZZOXODO, vTZZOLOD1, vTZEREMDO_REF, vTZTENVRO_REF, pszParadigm,
                                     pszNetwork, plAttrCount, nDerivedFlag, cpcDEBUGCHG );
      }

      SetAttributeFromInteger( vTZZOXODO, "ENTITY", "MAX_LTH", lEntityLth );
      // Set AUTOLOADFROMPARENT for SQL.
      // We will set AUTOLOADFROMPARENT if two conditions are true:

      // 1. If all of the "not hidden" attributes under the XOD Entity are keys.
      //    If this is true, then all of those key attributes should be in the parent as foreign keys.

      // 2. If the entity being processed is a leaf node (has no child)
      //    OR
      //    If the entity has only one child and that relationship to its child is in the Identifier for
      //    the entity being processed.

      // We will perform the 1st check by looping through the ATTRIB attributes
      // and aborting with the first "not hidden" attribute that is not a key.

      if ( *pszParadigm == 'R' && nDerivedFlag == 0 )
      {
         zVIEW vWorkERD;

         CreateViewFromViewForTask( &vWorkERD, vTZEREMDO_REF, 0 );
         SetNameForView( vWorkERD, "***WorkERD", vSubtask, zLEVEL_TASK );
         if ( CheckExistenceOfEntity( vTZZOLOD1, "ER_EntityRec" ) >= zCURSOR_SET )
         {
            SetCursorFirstEntityByAttr( vWorkERD, "ER_Entity", "ZKey", vTZZOLOD1, "ER_EntityRec", "ZKey", 0 );
         }

         nAutoLoadFlag = 1;
         for ( nRC = SetCursorFirstEntity( vTZZOXODO, "ATTRIB", 0 );
               nRC >= zCURSOR_SET && nAutoLoadFlag == 1;
               nRC = SetCursorNextEntity( vTZZOXODO, "ATTRIB", 0 ) )
         {
            if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "KEY", "Y" ) != 0 &&
                 CompareAttributeToString( vTZZOXODO, "ATTRIB", "HIDDEN", "Y" ) != 0 )
            {
               nAutoLoadFlag = 0;
            }
         }

         if ( nAutoLoadFlag == 1 )
         {
            // The first condition above was successful. We will now check the second.
            // We will actually make three separate tests.

            // 1. Is this entity a leaf node?
            nRC = SetCursorFirstEntity( vTZZOLOD1, "LOD_EntityChild", 0 );
            if ( nRC < zCURSOR_SET )
            {
               // Entity is leaf node. Set AUTOLOAD flag.
               nAutoLoadFlag = 1;
            }
            else
            {
               // 2. Is there more than one child entity?
               nRC = SetCursorNextEntity( vTZZOLOD1, "LOD_EntityChild", 0 );
               if ( nRC >= zCURSOR_SET )
               {
                  // The entity has multiple children. Don't set AUTOLOAD flag.
                  nAutoLoadFlag = 0;
               }
               else
               {
                  // There is a single child. We must now check to see if the relationship to the child is included
                  // in the Identifier for the entity being processed.

                  // First position on child relationship in the ERD.
                  SetViewToSubobject( vTZZOLOD1, "LOD_EntityChild" );
                  SetCursorFirstEntityByAttr( vWorkERD,  "ER_RelLink", "ZKey", vTZZOLOD1, "ER_RelLinkRec", "ZKey", 0 );
                  ResetViewFromSubobject( vTZZOLOD1 );

                  // 3. Try to locate relationship in Identifier.
                  nRC = SetCursorFirstEntityByAttr( vWorkERD, "ER_RelLinkIdentifier", "ZKey", vWorkERD, "ER_RelLink_Other", "ZKey", "ER_EntIdentifier" );
                  if ( nRC >= zCURSOR_SET )
                  {
                     // The relationship is part of the Identifer, set AUTOLOAD flag.
                     nAutoLoadFlag = 1;
                  }
                  else
                  {
                     // The relationship is NOT part of the Identifer, don't set the AUTOLOAD flag.
                     nAutoLoadFlag = 0;
                  }
               }
            }
         }

         DropView( vWorkERD );

         // Now set the AUTOLOADFROMPARENT flag based on results of the logic above.
         if ( nAutoLoadFlag == 1 )
         {
            SetAttributeFromString( vTZZOXODO, "ENTITY", "AUTOLOADFROMPARENT", "Y" );
         }
      }

      // nDerivedFlag tells me, whether the currend Entity or any of its parents is derived.
      //if ( nDerivedFlag &&
      //     CheckExistenceOfEntity( vTZZOXODO, "DATARECORD" ) >= zCURSOR_SET )
      //  DeleteEntity( vTZZOXODO, "DATARECORD", zREPOS_NONE );

      ResetViewFromSubobject( vTZZOLOD1 );
      ResetViewFromSubobject( vTZZOXODO );

   } // for ( nRC = SetCursorFirstEntity( vTZZOLOD1, "LOD_EntityChild", 0 )...

   if ( vTZTENVRO_Parent )
      DropView( vTZTENVRO_Parent );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldXODEntity
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODEntity( zVIEW vSubtask, zVIEW vTZZOXODO, zVIEW vTZZOLOD1 )
{
   zCHAR  szInd[ 2 ];
   zCHAR  szEntityName[ 33 ];
   zLONG  lIndentLvl;
   zSHORT nRC;

   GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vTZZOLOD1, "LOD_EntityParent", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "NAME", vTZZOLOD1, "LOD_EntityParent", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "LOCK", vTZZOLOD1, "LOD_EntityParent", "DataLocking" );
   SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ACT_LIMIT", vTZZOLOD1, "LOD_EntityParent", "MultipleChildLimit" );
   SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "XML_NAME", vTZZOLOD1, "LOD_EntityParent", "XML_Name" );
   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "AutoCreate", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "AUTOCREATE", vTZZOLOD1, "LOD_EntityParent", "AutoCreate" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Create", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "CREATE", vTZZOLOD1, "LOD_EntityParent", "Create" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Delete", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "DELETE", vTZZOLOD1, "LOD_EntityParent", "Delete" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Derived", "Y" ) == 0 ||
        CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Work", "Y" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ENTITY", "DERIVED", "Y" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Exclude", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "EXCLUDE", vTZZOLOD1, "LOD_EntityParent", "Exclude" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Include", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "INCLUDE", vTZZOLOD1, "LOD_EntityParent", "Include" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "InclSrc", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "INCLSRC", vTZZOLOD1, "LOD_EntityParent", "InclSrc" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Hidden", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "HIDDEN", vTZZOLOD1, "LOD_EntityParent", "Hidden" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Recursive", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "RECURSIVE", vTZZOLOD1, "LOD_EntityParent", "Recursive" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Abstract", "Y" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ENTITY", "ABSTRACT", "Y" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Abstract", "C" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ENTITY", "ABSTRACTCHILD", "Y" );
   }

   if ( (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "SeqType", "R" ) == 0) ||
        (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "SeqType", "A" ) == 0) )
   {
      GetStringFromAttribute( szInd, zsizeof( szInd ), vTZZOLOD1, "LOD_EntityParent", "SeqType" );
      SetAttributeFromString( vTZZOXODO, "ENTITY", "SEQTYPE", szInd );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "DupEntityInstance", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "DUPENTIN", vTZZOLOD1, "LOD_EntityParent", "DupEntityInstance" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "DupRelationshipInstance", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "DUPRELIN", vTZZOLOD1, "LOD_EntityParent", "DupRelationshipInstance" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "LazyLoadFlag", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "LAZYLOAD", vTZZOLOD1, "LOD_EntityParent", "LazyLoadFlag" );
   }

   if ( (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "ParentDeleteBehave", "D" ) == 0) ||
        (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "ParentDeleteBehave", "E" ) == 0) ||
        (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "ParentDeleteBehave", "R" ) == 0) )
   {
      GetStringFromAttribute( szInd, zsizeof( szInd ), vTZZOLOD1, "LOD_EntityParent", "ParentDeleteBehave" );
      SetAttributeFromString( vTZZOXODO, "ENTITY", "PDELETE", szInd );
   }

   if ( (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Update", "" ) == 0) ||
        (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Update", "Y" ) == 0) )
      nRC = SetAttributeFromString( vTZZOXODO, "ENTITY", "UPDATE", "Y" );

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Work", "Y" ) == 0 )
   {
      nRC = SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ERENT_TOK", vTZZOLOD1, "LOD_EntityParent", "ZKey" );
   }
   else
   {
      // Not a WORK entity.
      nRC = SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ERENT_TOK", vTZZOLOD1, "ER_EntityRec", "ZKey" );
   }

   if ( SetCursorFirstEntity( vTZZOLOD1, "LOD_EntityConstraintOperRec", "" ) >= zCURSOR_SET )
   {
      zVIEW  vTaskLPLR;
      zCHAR  szTempName[ 256 ] = "";
      zCHAR  szType[ 256 ];
      zLONG  lLth;

      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ECEOPER", vTZZOLOD1, "LOD_EntityConstraintOperRec", "C_GeneratedOperationName" );

      // KJS 10/15/14 - Add Name and Extension for Entity Constraint.
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ECESRCTYPE", vTZZOLOD1, "SourceFileForECOperRec", "Extension" );
      GetStringFromAttribute( szType, zsizeof( szType ), vTZZOLOD1, "SourceFileForECOperRec", "Extension" );

      GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );

      // If the source file is VML or Java, then we want to get the JavaPackageName.
      if ( vTaskLPLR && ( szType[ 0 ] == 'V' || szType[ 0 ] == 'J' ) )
      {
         zPCHAR pchSlash;

         GetStringFromAttribute( szTempName, zsizeof( szTempName ), vTaskLPLR, "LPLR", "JavaPackageName" );
         while ( (pchSlash = zstrchr( szTempName, '\\' )) != 0 )
            *pchSlash = '.';

      }

      lLth = zstrlen( szTempName );
      if ( lLth > 0 )
         szTempName[ lLth++ ] = '.';

      GetStringFromAttribute( szTempName + lLth, zsizeof( szTempName ) - lLth, vTZZOLOD1, "SourceFileForECOperRec", "Name" );

      // We only want the _Object extension, if this is VML that we are converting into java.
      if ( szType[ 0 ] == 'V' )
         strcat_s( szTempName, zsizeof( szTempName ), "_Object" );

      SetAttributeFromString( vTZZOXODO, "ENTITY", "ECESRCFILE", szTempName );
   //                         vTZZOLOD1, "SourceFileForECOperRec", "Name" );

      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ECCR", vTZZOLOD1, "LOD_EntityParent", "CreateConstraint" );
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ECDEL", vTZZOLOD1, "LOD_EntityParent", "DeleteConstraint" );
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ECINC", vTZZOLOD1, "LOD_EntityParent", "IncludeConstraint" );
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ECEXC", vTZZOLOD1, "LOD_EntityParent", "ExcludeConstraint" );
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ECACC", vTZZOLOD1, "LOD_EntityParent", "AcceptConstraint" );
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ECCAN", vTZZOLOD1, "LOD_EntityParent", "CancelConstraint" );
   }

   // Don't build rest on Root.
   nRC = GetIntegerFromAttribute( &lIndentLvl, vTZZOLOD1, "LOD_EntityParent", "IndentLvl" );
   if ( lIndentLvl == 0 )
      return( 0 );

   if ( (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Work", "Y" ) == 0) ||
        (CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "Derived", "Y" ) == 0) ||
        (CheckExistenceOfEntity( vTZZOLOD1, "ER_RelTypeRec" ) < zCURSOR_SET ) )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ERREL_TOK", vTZZOLOD1, "LOD_EntityParent", "ZKey" );
      SetAttributeFromString( vTZZOXODO, "ENTITY", "CARDMIN", "0" );
      SetAttributeFromInteger( vTZZOXODO, "ENTITY", "CARDMAX", 999999 );
   }
   else
   {
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "ERREL_TOK", vTZZOLOD1, "ER_RelTypeRec", "ZKey" );
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "CARDMIN", vTZZOLOD1, "ER_RelLinkRec", "CardMin" );
      SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "HANG_FK", vTZZOLOD1, "ER_RelLinkRec", "HangingForeignKeyEntity" );

      // CardMax is 999999 in XOD if it is "M" in LOD.
      if ( CompareAttributeToString( vTZZOLOD1, "ER_RelLinkRec", "CardMax", "M" ) == 0 )
         SetAttributeFromInteger( vTZZOXODO, "ENTITY", "CARDMAX", 999999 );
      else
         SetAttributeFromAttribute( vTZZOXODO, "ENTITY", "CARDMAX", vTZZOLOD1, "ER_RelLinkRec", "CardMax" );

      if ( CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "RelLinkIndicator", "L" ) == 0 )
      {
         SetAttributeFromInteger( vTZZOXODO, "ENTITY", "ERREL_LINK", 1 );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldXODAttrib
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODAttrib( zVIEW vSubtask, zVIEW vTZZOXODO,
                          zVIEW vTZZOLOD1,
                          zVIEW vTZEREMDO_REF,
                          zCPCHAR cpcDEBUGCHG )
{
   zCHAR  szEntityName[ 33 ];
   zCHAR  szAttribName[ 33 ];
   zCHAR  szDataType[ 2 ];
   zPCHAR pchType;
   zSHORT nRC;

   GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vTZZOXODO, "ENTITY", "NAME" );

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "NAME", vTZZOLOD1, "ER_AttributeRec", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "XML_SIMPLE_NAME", vTZZOLOD1, "ER_AttributeRec", "XML_SimpleName" );
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "XML_NAME_EXTERNAL", vTZZOLOD1, "ER_AttributeRec", "XML_NameExternal" );

   GetStringFromAttribute( szAttribName, zsizeof( szAttribName ), vTZZOXODO, "ATTRIB", "NAME" );
   if ( cpcDEBUGCHG && cpcDEBUGCHG[ 0 ] && zstrcmp( szAttribName, cpcDEBUGCHG ) == 0 )
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DEBUGCHG", "Y" );


   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "ERATT_TOK", vTZZOLOD1, "ER_AttributeRec", "ZKey" );

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "ParticipatesInKey", "Y" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "KEY", "Y" );
   }

   // Hashkey Specification
   if ( CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "HashkeyType", "G" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "HASHKEY", "GLOBAL" );
   }
   if ( CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "HashkeyType", "P" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "HASHKEY", "UNDER_PARENT" );
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "HASHKEY_PARENT",
                                 vTZZOLOD1, "LOD_AttributeRec", "HashkeyParentEntityName" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "NotNull", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "REQUIRED", vTZZOLOD1, "ER_AttributeRec", "NotNull" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "CaseSens", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "CASESENS", vTZZOLOD1, "ER_AttributeRec", "CaseSens" );
   }

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DB_OPER", vTZZOLOD1, "LOD_AttributeRec", "DB_DerivedValue" );
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DOMAIN", vTZZOLOD1, "DomainRec", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "APDM_TOK", vTZZOLOD1, "DomainRec", "ZKey" );

   // If Domain.DataType is "Date" or "Time", set ATTRIB.TYPE to "T".
   GetStringFromAttribute( szDataType, zsizeof( szDataType ), vTZZOLOD1, "DomainRec", "DataType" );
   if ( *szDataType == 'D' || *szDataType == 'I' )
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "TYPE", "T" );
   else
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "TYPE", vTZZOLOD1, "DomainRec", "DataType" );

   GetAddrForAttribute( &pchType, vTZZOXODO, "ATTRIB", "TYPE" );
   switch ( *pchType )
   {
      case zTYPE_STRING:
         if ( CompareAttributeToInteger( vTZZOLOD1, "ER_AttributeRec", "Lth", 0 ) == 0 ||
              CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "Lth", "" ) == 0 )
         {
            SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "LTH", vTZZOLOD1, "DomainRec", "MaxStringLth" );
         }
         else
         {
            SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "LTH", vTZZOLOD1, "ER_AttributeRec", "Lth" );
         }

         break;

      case zTYPE_INTEGER:
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );
         break;

      case zTYPE_DECIMAL:
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 8 );
         SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DECIMAL", vTZZOLOD1, "DomainRec", "DecimalFormat" );
         break;

      case zTYPE_BLOB:
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 7 );
         break;

      case zTYPE_DATETIME:
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 6 );
         break;
   }

   // We need to make sure the GENKEY attribute is set here in case the TE source is network.
   // The GENKEY attribute used to be set in BldXODDataField.
   // First use the ER_Entity position in the LOD to position on the correct entity in the ERD.
   // Then use the ER_Attribute position in the LOD to position on the correct ER_AttributeIdentifier in the ERD.
   // Then checkthe corresponding ER_EntIdentifier (the Identifier entity) to see if it is for a generated key.
   // but not for work LOD's (ER_EntityRec does not exist!)
   if (CheckExistenceOfEntity( vTZZOLOD1,"ER_EntityRec") >= zCURSOR_SET)
   {
     SetCursorFirstEntityByAttr( vTZEREMDO_REF, "ER_Entity", "ZKey", vTZZOLOD1, "ER_EntityRec", "ZKey", 0 );
     nRC = SetCursorFirstEntityByAttr( vTZEREMDO_REF, "ER_AttributeIdentifier", "ZKey", vTZZOLOD1, "ER_AttributeRec", "ZKey", "ER_Entity" );
     if ( nRC >= zCURSOR_SET &&
          CompareAttributeToString( vTZEREMDO_REF, "ER_EntIdentifier", "SystemMaintained", "Y" ) == 0 )
     {
        SetAttributeFromString( vTZZOXODO, "ATTRIB", "GENKEY", "Y" );
     }
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "Hidden", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "HIDDEN", vTZZOLOD1, "LOD_AttributeRec", "Hidden" );
   }

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "INIT", vTZZOLOD1, "LOD_AttributeRec", "Init" );

   // Set SEQUENCING information.
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "SEQUENCING", vTZZOLOD1, "LOD_AttributeRec", "SeqPriority" );
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "SEQ_AD", vTZZOLOD1, "LOD_AttributeRec", "SeqOrder" );

   if ( CheckExistenceOfEntity( vTZZOLOD1, "LOD_AttrDerivationOperRec" ) >= zCURSOR_SET )
   {
      zVIEW  vTaskLPLR;
   // zVIEW  vTemp;
      zCHAR  szTempName[ 256 ] = "";
      zCHAR  szType[ 256 ];
      zLONG  lLth;

   // MessageSend( vSubtask, "ZO00305", "Operations",
   //              "LOD_AttrDerive", zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DERIVEDF", vTZZOLOD1, "LOD_AttrDerivationOperRec", "C_GeneratedOperationName" );
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DRSRCTYPE", vTZZOLOD1, "SourceFileForDARec", "Extension" );

      // Kelly wanted aDERIVEDF  owWebXfer_dTotalRequestedAmount
      //          and aDERIVEDC  com.quinsoft.zencas.wWebXfer_Object
      GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );

      GetStringFromAttribute( szType, zsizeof( szType ), vTZZOLOD1, "SourceFileForDARec", "Extension" );

      // If the source file is VML or Java, then we want to get the JavaPackageName.
      if ( vTaskLPLR && ( szType[ 0 ] == 'V' || szType[ 0 ] == 'J' ) )
      {
         zPCHAR pchSlash;

         GetStringFromAttribute( szTempName, zsizeof( szTempName ), vTaskLPLR, "LPLR", "JavaPackageName" );
         while ( (pchSlash = zstrchr( szTempName, '\\' )) != 0 )
            *pchSlash = '.';

      }
         lLth = zstrlen( szTempName );
      if ( lLth > 0 )
            szTempName[ lLth++ ] = '.';

         GetStringFromAttribute( szTempName + lLth, zsizeof( szTempName ) - lLth, vTZZOLOD1, "SourceFileForDARec", "Name" );

      // We only want the _Object extension, if this is VML that we are converting into java.
      if ( szType[ 0 ] == 'V' )
         strcat_s( szTempName, zsizeof( szTempName ), "_Object" );

      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DERIVEDC", szTempName );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "Work", "Y" ) != 0 &&
        CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "Work", "Y" ) != 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "PERSIST", "Y" );
   }

   if ( CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "Update", "" ) == 0 ||
        CompareAttributeToString( vTZZOLOD1, "LOD_AttributeRec", "Update", "Y" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "UPDATE", "Y" );
   }

   // Set up derived expression.
   if ( CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "DerivedExpression", "" ) != 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DERIVEDZ", "Y" );

      // If the XPG is NULL then we don't need to use the XPG, just the original simple "interpreter".
      if ( CompareAttributeToString( vTZZOLOD1, "ER_AttributeRec", "DerivedExpressionXPG", "" ) == 0 )
      {
         SetAttributeFromString( vTZZOXODO, "ATTRIB", "DERIVEDF", "DfExprVML" );
         SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DERIVEDE", vTZZOLOD1, "ER_AttributeRec", "DerivedExpression" );
      }
      else
      {
         SetAttributeFromString( vTZZOXODO, "ATTRIB", "DERIVEDF", "*xpg*" );
         SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DERIVEDOPERXPG", vTZZOLOD1, "ER_AttributeRec", "DerivedExpressionXPG" );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldXODAttribHidden
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODAttribHidden( zVIEW vSubtask, zVIEW vTZZOXODO,
                                zVIEW vTZEREMDO_REF, zCPCHAR cpcDEBUGCHG )
{
   zCHAR  szEntityName[ 33 ];
   zCHAR  szAttribName[ 33 ];
   zCHAR  szDataType[ 2 ];
   zPCHAR pchType;

   GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vTZZOXODO, "ENTITY", "NAME" );

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "NAME", vTZEREMDO_REF, "ER_Attribute", "Name" );

   GetStringFromAttribute( szAttribName, zsizeof( szAttribName ), vTZZOXODO, "ATTRIB", "NAME" );

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "ERATT_TOK", vTZEREMDO_REF, "ER_Attribute", "ZKey" );
   if ( CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "ParticipatesInKey", "Y" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "KEY", "Y" );
   }

   if ( CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "NotNull", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "REQUIRED", vTZEREMDO_REF, "ER_Attribute", "NotNull" );
   }

   if ( CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "CaseSens", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "CASESENS", vTZEREMDO_REF, "ER_Attribute", "CaseSens" );
   }

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DOMAIN", vTZEREMDO_REF, "Domain", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "APDM_TOK", vTZEREMDO_REF, "Domain", "ZKey" );

   // If Domain.DataType is "Date" or "Time", set ATTRIB.TYPE to "T".
   GetStringFromAttribute( szDataType, zsizeof( szDataType ), vTZEREMDO_REF, "Domain", "DataType" );
   if ( *(zPCHAR)szDataType == 'D' || *(zPCHAR)szDataType == 'I' )
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "TYPE", "T" );
   else
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "TYPE", vTZEREMDO_REF, "Domain", "DataType" );

   GetAddrForAttribute( &pchType, vTZZOXODO, "ATTRIB", "TYPE" );
   switch ( *pchType )
   {
      case zTYPE_STRING:
         if ( CompareAttributeToInteger( vTZEREMDO_REF, "ER_Attribute", "Lth", 0 ) == 0 ||
              CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "Lth", "" ) == 0 )
         {
            SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "LTH", vTZEREMDO_REF, "Domain", "MaxStringLth" );
         }
         else
         {
            SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "LTH", vTZEREMDO_REF, "ER_Attribute", "Lth" );
         }

         break;

      case zTYPE_INTEGER:
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );
         break;

      case zTYPE_DECIMAL:
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 8 );
         SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DECIMAL", vTZEREMDO_REF, "Domain", "DecimalFormat" );
         break;

      case zTYPE_BLOB:
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 7 );
         break;

      case zTYPE_DATETIME:
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 6 );
         break;
   }

// DGC 12/11/96   Removed the following stuff because these types are invalid.
#if 0
   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "Y" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 1 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "N" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 2 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "F" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "R" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 8 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "W" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 10 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "D" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "H" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 2 );
#endif

   SetAttributeFromString( vTZZOXODO, "ATTRIB", "HIDDEN", "Y" );

   if ( CompareAttributeToString( vTZEREMDO_REF, "ER_Attribute", "Work", "Y" ) != 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "PERSIST", "Y" );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldXODDataRec
//
/////////////////////////////////////////////////////////////////////////////
static zSHORT
ofnTZZOXODO_BldXODDataRec( zVIEW vSubtask, zVIEW vTZZOXODO,
                           zVIEW vTZTENVRO_REF, zVIEW vTZZOLODO )
{
   zCHAR  szRecName[ 255 ];
   zCHAR  *pchDot;

   // RECNAME is the name of the record or SQL table.  If SQL_TableOwner is specified, then prefix RECNAME with the owner name followed by a '.'.
   // First we have to check if the Entityname includes the tableowner.
   GetStringFromAttribute( szRecName, zsizeof( szRecName ), vTZTENVRO_REF, "TE_TablRec", "Name" );

   // If we find a '.' the entityname includes the ownername and we may not check the SQL_TableOwner and the Defaultownwer
   pchDot = strchr( szRecName, '.' );
   if ( pchDot == 0 )
   {
      GetStringFromAttribute( szRecName, zsizeof( szRecName ), vTZTENVRO_REF, "TE_TablRec", "SQL_TableOwner" );
      if ( szRecName[ 0 ] == 0 )
      {
         GetStringFromAttribute( szRecName, zsizeof( szRecName ), vTZTENVRO_REF, "TE_DBMS_Source", "DefaultOwner" );
      }

      if ( szRecName[ 0 ] )
      {
         strcat_s( szRecName, zsizeof( szRecName ), "." );
         GetStringFromAttribute( szRecName + zstrlen( szRecName ), zsizeof( szRecName ) - zstrlen( szRecName ),
                                 vTZTENVRO_REF, "TE_TablRec", "Name" );
      }
      else
         GetStringFromAttribute( szRecName, zsizeof( szRecName ), vTZTENVRO_REF, "TE_TablRec", "Name" );
   }

   SetAttributeFromString( vTZZOXODO, "DATARECORD", "RECNAME", szRecName );

   SetAttributeFromAttribute( vTZZOXODO, "DATARECORD", "RECID", vTZTENVRO_REF, "TE_TablRec", "DBMS_ID" );

   // Set to Primary for Temporary Reasons.
   SetAttributeFromString( vTZZOXODO, "DATARECORD", "TYPE", "P" );

   // If there is a POD_Entity, we must forward the DBH specific information to the XOD.
   if ( CheckExistenceOfEntity( vTZZOLODO, "POD_Entity" ) >= zCURSOR_SET )
   {
      SetAttributeFromAttribute( vTZZOXODO, "DATARECORD", "JOIN", vTZZOLODO, "POD_Entity", "SQL_JoinWithParent" );
      SetAttributeFromAttribute( vTZZOXODO, "DATARECORD", "ACTIVATEONE", vTZZOLODO, "POD_Entity", "SQL_ActivateInOne" );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldXODDataField
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODDataField( zVIEW vSubtask, zVIEW vTZZOXODO,
                             zVIEW vTZTENVRO_REF )
{
   zSHORT nRC;

   zVIEW  vTZTENVR1;

   CreateViewFromViewForTask( &vTZTENVR1, vTZTENVRO_REF, 0 );

   SetCursorFirstEntity( vTZTENVR1, "TE_TablRecKey", "" );
   nRC = SetCursorFirstEntityByEntityCsr( vTZTENVR1, "TE_FieldDataRelKey", vTZTENVR1, "TE_FieldDataRel", 0 );
   if ( nRC >= zCURSOR_SET )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "KEY", "Y" );
#if 0
      if ( CompareAttributeToString( vTZTENVR1, "TE_TablRecKey", "Category", "1" ) == 0 ||
           CompareAttributeToString( vTZTENVR1, "TE_TablRecKey", "Category", "2" ) == 0 )
      {
         if ( CompareAttributeToString( vTZTENVR1, "ER_EntIdentifier", "SystemMaintained", "Y" ) == 0 )
            SetAttributeFromString( vTZZOXODO, "ATTRIB", "GENKEY", "Y" );
      }
#endif
   }

   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "XVAATT_TOK", vTZZOXODO, "ATTRIB", "XVAATT_TOK" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDID", vTZTENVRO_REF, "TE_FieldDataRel", "DBMS_ID" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDOFFSET", vTZTENVRO_REF, "TE_FieldDataRel", "Offset" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDTYPE", vTZTENVRO_REF, "TE_FieldDataRel", "DataType" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDLTH", vTZTENVRO_REF, "TE_FieldDataRel", "Length" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDNAME", vTZTENVRO_REF, "TE_FieldDataRel", "Name" );

   DropView( vTZTENVR1 );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldDB_DataFields
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldDB_DataFields( zVIEW vTZZOXODO, zVIEW vTZZOLOD1 )
{
   zVIEW  vTZZOLOD2;
   zVIEW  vTZZOXOD2;
   zLONG  lAttribZKey;
   zLONG  lXVAATT_TOK;
   zSHORT nRC;

   // We will now loop through the ATTRIB entities and complete any entries that have a DB_OPER specification.  For each of these
   // we must add a DATAFIELD entry and tie it back to the original ATTRIB entry with the DB_OPER specification.  We will do this
   // by locating the ATTRIB entry for the DB_LOD_AttributeRec entity and its corresponding DATAFIELD entry.  Then we will duplicate that
   // entry, and change its XVAATT_TOK value to point to the original ATTRIB entry.

   SetCursorLastEntity( vTZZOXODO, "DATAFIELD", "" );
   nRC = SetCursorFirstEntity( vTZZOXODO, "ATTRIB", "" );
   while ( nRC >= zCURSOR_SET )
   {
      if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "DB_OPER", "" ) != 0 )
      {
         // Set position on corresponding LOD and ER Attribute.
         CreateViewFromViewForTask( &vTZZOLOD2, vTZZOLOD1, 0 );
         CreateViewFromViewForTask( &vTZZOXOD2, vTZZOXODO, 0 );
         GetIntegerFromAttribute( &lAttribZKey, vTZZOXODO, "ATTRIB", "ERATT_TOK" );
         SetCursorFirstEntityByInteger( vTZZOLOD2, "ER_AttributeRec", "ZKey", lAttribZKey, "LOD_EntityParent" );

         // Then position on ATTRIB entity for corresponding DB_ER_AttributeRec.
         GetIntegerFromAttribute( &lAttribZKey, vTZZOLOD2, "DB_ER_AttributeRec", "ZKey" );
         SetCursorFirstEntityByInteger( vTZZOXOD2, "ATTRIB", "ERATT_TOK", lAttribZKey, "" );
         GetIntegerFromAttribute( &lXVAATT_TOK, vTZZOXOD2, "ATTRIB", "XVAATT_TOK" );
         SetCursorFirstEntityByInteger( vTZZOXOD2, "DATAFIELD", "XVAATT_TOK", lXVAATT_TOK, "" );

         // Don't build the DATAFIELD entity if the souce doesn't have one.
         if ( CheckExistenceOfEntity( vTZZOXOD2, "DATAFIELD" ) >= zCURSOR_SET )
         {
            CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_AFTER );
            SetMatchingAttributesByName( vTZZOXODO, "DATAFIELD", vTZZOXOD2, "DATAFIELD", zSET_NULL );
            SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "XVAATT_TOK", vTZZOXODO, "ATTRIB",    "XVAATT_TOK" );
         }

         DropView( vTZZOLOD2 );
         DropView( vTZZOXOD2 );
      }

      nRC = SetCursorNextEntity( vTZZOXODO, "ATTRIB", "" );
   }

   return( 0 );

} // ofnTZZOXODO_BldDB_DataFields

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldAttribFK
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldAttribFK( zVIEW vTZZOXODO,
                         zVIEW vTZTENVRO_REF,
                         zVIEW vTZZOLOD1 )
{
   zVIEW  vTZTENVR1;
   zVIEW  vTZTENVR2;
   zCHAR  szEntName[ 33 ];
   zCHAR  szAttName[ 33 ];
   zCHAR  szDataType[ 2 ];
   zSHORT nRC;

   GetStringFromAttribute( szEntName, zsizeof( szEntName ), vTZTENVRO_REF, "TE_TablRec", "Name" );
   GetStringFromAttribute( szAttName, zsizeof( szAttName ), vTZTENVRO_REF, "TE_FieldDataRel", "Name" );

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "NAME", vTZTENVRO_REF, "TE_FieldDataRel", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "ERATT_TOK", vTZTENVRO_REF, "TE_FieldDataRel", "ZKey" );
   if ( CompareAttributeToString( vTZTENVRO_REF, "TE_FieldDataRel", "SQL_NULLS", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "REQUIRED", vTZTENVRO_REF, "TE_FieldDataRel", "SQL_NULLS" );
   }

   // We must set the ATTRIB.TYPE value from the Domain of the attribute which is the original source of the foreign key.
   // Because this could be recursive up several levels in the LOD, we will follow the chain of TE_FieldDataRelPK entries
   // until we find a TE_FieldDataRel entity of type "data". We will then get the Domain.DataType value for that entry.
   CreateViewFromViewForTask( &vTZTENVR1, vTZTENVRO_REF, 0 );
   nRC = SetCursorFirstEntityByAttr( vTZTENVR1, "TE_FieldDataRel", "ZKey", vTZTENVRO_REF, "TE_FieldDataRel_PK", "ZKey", "TE_DBMS_Source" );
   while ( nRC >= zCURSOR_SET &&
           CompareAttributeToString( vTZTENVR1, "TE_FieldDataRel", "DataOrRelfieldOrSet", "D" ) != 0 )
   {
      CreateViewFromViewForTask( &vTZTENVR2, vTZTENVR1, 0 );
      nRC = SetCursorFirstEntityByAttr( vTZTENVR1, "TE_FieldDataRel", "ZKey", vTZTENVR2, "TE_FieldDataRel_PK", "ZKey", "TE_DBMS_Source" );
      DropView( vTZTENVR2 );
   }

   if ( CheckExistenceOfEntity( vTZTENVR1, "ER_Attribute" ) >= zCURSOR_SET )
   {
      // If Domain.DataType is "Date" or "Time", set ATTRIB.TYPE to "T".
      GetStringFromAttribute( szDataType, zsizeof( szDataType ),vTZTENVR1, "Domain", "DataType" );
      if ( szDataType[ 0 ] == 'D' || szDataType[ 0 ] == 'I' )
         SetAttributeFromString( vTZZOXODO, "ATTRIB", "TYPE", "T" );
      else
         SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "TYPE", vTZTENVR1, "Domain", "DataType" );

      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DOMAIN", vTZTENVR1, "Domain", "Name" );
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "APDM_TOK", vTZTENVR1, "Domain", "ZKey" );
      if ( CompareAttributeToString( vTZTENVR1, "ER_Attribute", "CaseSens", "Y" ) == 0 )
      {
         SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "CASESENS", vTZTENVR1, "ER_Attribute", "CaseSens" );
      }
   }
   else
   {
      // If there is no ER_Attribute entity, we will treat this entry as a System Maintained key.
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "TYPE", "L" );
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );
   }

   nRC = DropView( vTZTENVR1 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "S" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "LTH", vTZTENVRO_REF, "TE_FieldDataRel", "Length" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "L" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "M" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 8 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "B" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 7 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "Y" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 1 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "N" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 2 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "F" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "R" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 8 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "W" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 10 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "T" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 6 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "D" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "H" ) == 0 )
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 2 );

   SetAttributeFromString( vTZZOXODO, "ATTRIB", "HIDDEN",  "Y" );
   SetAttributeFromString( vTZZOXODO, "ATTRIB", "PERSIST", "Y" );
   SetAttributeFromString( vTZZOXODO, "ATTRIB", "UPDATE",  "Y" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldDataFieldFK
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldDataFieldFK( zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF )
{
   zVIEW  vTZTENVR1;
   zSHORT nRC;

   CreateViewFromViewForTask( &vTZTENVR1, vTZTENVRO_REF, 0 );

   SetCursorFirstEntity( vTZTENVR1, "TE_TablRecKey", "" );
   nRC = SetCursorFirstEntityByEntityCsr( vTZTENVR1, "TE_FieldDataRelKey", vTZTENVR1, "TE_FieldDataRel", "" );
   if ( nRC >= zCURSOR_SET )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "KEY", "Y" );
   }

   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "XVAATT_TOK", vTZZOXODO, "ATTRIB", "XVAATT_TOK" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDID", vTZTENVRO_REF, "TE_FieldDataRel", "DBMS_ID" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDOFFSET", vTZTENVRO_REF, "TE_FieldDataRel", "Offset" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDNAME", vTZTENVRO_REF, "TE_FieldDataRel", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDTYPE", vTZTENVRO_REF, "TE_FieldDataRel", "DataType" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDLTH", vTZTENVRO_REF, "TE_FieldDataRel", "Length" );

   DropView( vTZTENVR1 );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldAttribGK
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldAttribGK( zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF )
{
   zCHAR  szEntName[ 33 ];
   zCHAR  szAttName[ 33 ];

   GetStringFromAttribute( szEntName, zsizeof( szEntName ), vTZTENVRO_REF, "TE_TablRec", "Name" );
   GetStringFromAttribute( szAttName, zsizeof( szAttName ), vTZTENVRO_REF, "TE_FieldDataRel", "Name" );

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "NAME", vTZTENVRO_REF, "TE_FieldDataRel", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "ERATT_TOK", vTZTENVRO_REF, "TE_FieldDataRel", "ZKey" );
   if ( CompareAttributeToString( vTZTENVRO_REF, "TE_FieldDataRel", "SQL_NULLS", "Y" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "REQUIRED", vTZTENVRO_REF, "TE_FieldDataRel", "SQL_NULLS" );
   }

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "TYPE", vTZTENVRO_REF, "TE_FieldDataRel", "DataType" );
   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "S" ) == 0 )
   {
      SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "LTH", vTZTENVRO_REF, "TE_FieldDataRel", "Length" );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Text" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "L" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Integer" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "M" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 8 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Decimal" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "B" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 7 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Blob" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "Y" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 1 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Text" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "N" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 2 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "ShortInteger" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "F" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Integer" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "R" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 8 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Decimal" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "W" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 10 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Date" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "T" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 6 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Time" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "D" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 4 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "Date" );
   }

   if ( CompareAttributeToString( vTZZOXODO, "ATTRIB", "TYPE", "H" ) == 0 )
   {
      SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "LTH", 2 );
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "DOMAIN", "ShortInteger" );
   }

   SetAttributeFromString( vTZZOXODO, "ATTRIB", "HIDDEN",  "Y" );
   SetAttributeFromString( vTZZOXODO, "ATTRIB", "PERSIST", "Y" );
   SetAttributeFromString( vTZZOXODO, "ATTRIB", "UPDATE",  "Y" );
   SetAttributeFromString( vTZZOXODO, "ATTRIB", "GENKEY",  "Y" );
   SetAttributeFromString( vTZZOXODO, "ATTRIB", "KEY",     "Y" );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldDataFieldGK
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldDataFieldGK( zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF )
{
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "XVAATT_TOK", vTZZOXODO, "ATTRIB", "XVAATT_TOK" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDID", vTZTENVRO_REF, "TE_FieldDataRel", "DBMS_ID" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDOFFSET", vTZTENVRO_REF, "TE_FieldDataRel", "Offset" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDNAME", vTZTENVRO_REF, "TE_FieldDataRel", "Name" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDTYPE", vTZTENVRO_REF, "TE_FieldDataRel", "DataType" );
   SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDLTH", vTZTENVRO_REF, "TE_FieldDataRel", "Length" );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldXODRelRec
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldXODRelRec( zVIEW vSubtask, zVIEW  vTZZOXODO,
                          zVIEW  vTZTENVRO_REF,
                          zVIEW  vTZZOLOD1,
                          zVIEW  vTZTENVRO_Parent,
                          zPCHAR pszParadigm,
                          zPLONG plAttrCount )
{
   zVIEW  vTZTENVR1;
   zVIEW  vTZTENVR1_Alt;
   zVIEW  vTZZOXOD1;
   zVIEW  vERD;
   zVIEW  vERDWork;
   zLONG  lRelLinkZKey;
   zLONG  lRelTypeZKey;
   zCHAR  szRecName[ 255 ];
   zCHAR  szSironDB_Type[ 2 ];
   zCHAR  szEntityName[ 9 ];       /* Entityname == Siron Catalogname */
   zSHORT nRelError;               /* > 0 if no Relationship in TE */
   zSHORT nRC;

   if ( CheckExistenceOfEntity( vTZZOLOD1, "ER_RelLinkRec" ) < zCURSOR_SET )
      return( 0 );

   CreateViewFromViewForTask( &vTZTENVR1, vTZTENVRO_REF, 0 );
   SetNameForView( vTZTENVR1, "vTZTENVR1_RelRec", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vTZTENVR1_Alt, vTZTENVRO_Parent, 0 );
   SetNameForView( vTZTENVR1_Alt, "vTZTENVR1_AltRelRec", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vTZZOXOD1, vTZZOXODO, 0 );
   SetNameForView( vTZZOXOD1, "vTZZOXOD1_RelRec", vSubtask, zLEVEL_TASK );
   ResetViewFromSubobject( vTZZOXOD1 );

   GetIntegerFromAttribute( &lRelLinkZKey, vTZZOLOD1, "ER_RelLinkRec", "ZKey" );
   GetIntegerFromAttribute( &lRelTypeZKey, vTZZOLOD1, "ER_RelTypeRec", "ZKey" );

   // Position on the TE_FieldDataRel entity that is the first foreign key for the RelLink.
   // We must be careful not to stop at an AutoSeq field by mistake.
   for ( nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_RelLink", "ZKey", lRelLinkZKey, "TE_DBMS_Source" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntityByInteger( vTZTENVR1, "ER_RelLink", "ZKey", lRelLinkZKey, "TE_DBMS_Source" ) )
   {
      if ( CheckExistenceOfEntity ( vTZTENVR1, "TE_FieldDataRel_PK" ) >= zCURSOR_SET )
         break;
   }

   if ( nRC < zCURSOR_SET )
   {
      SetViewFromView( vTZTENVR1, vTZTENVRO_Parent );
      SetViewFromView( vTZTENVR1_Alt, vTZTENVRO_REF );

      // Position on the TE_FieldDataRel entity that is the first foreign key for the RelLink.
      // We must be careful not to stop at an AutoSeq field by mistake.
      for ( nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_RelLink", "ZKey", lRelLinkZKey, "TE_DBMS_Source" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntityByInteger( vTZTENVR1, "ER_RelLink", "ZKey", lRelLinkZKey, "TE_DBMS_Source" ) )
      {
         if ( CheckExistenceOfEntity ( vTZTENVR1, "TE_FieldDataRel_PK" ) >= zCURSOR_SET )
            break;
      }
   }

   if ( nRC >= zCURSOR_SET )
   {
      if ( CompareAttributeToString( vTZTENVR1, "TE_TablRec", "DataOrRel", "D" ) == 0 )
      {
         SetAttributeFromString( vTZZOXODO, "RELRECORD", "OWNER_MEMB", "O" );
         if ( *pszParadigm == 'R' )
         {
            ofnTZZOXODO_BldRelFieldFK( vTZZOXODO, vTZTENVR1, vTZZOXOD1, vTZTENVR1_Alt );
         }
         else
         {
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "SETID1", vTZTENVR1, "TE_FieldDataRel", "DBMS_ID" );
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "SETNAME1", vTZTENVR1, "TE_FieldDataRel", "Name" );
         }
      }
      else
      {
         SetAttributeFromString( vTZZOXODO, "RELRECORD", "OWNER_MEMB", "2" );

         // RECNAME is the name of the record or SQL table.  If SQL_TableOwner is specified, then prefix RECNAME with the owner name followed by a '.'.
         GetStringFromAttribute( szRecName, zsizeof( szRecName ), vTZTENVR1, "TE_TablRec", "SQL_TableOwner" );
         if ( *szRecName == 0 )
         {
            GetStringFromAttribute( szRecName, zsizeof( szRecName ), vTZTENVR1, "TE_DBMS_Source", "DefaultOwner" );
         }
         if ( *szRecName != 0 )
         {
            strcat_s( szRecName, zsizeof( szRecName ), "." );
            GetStringFromAttribute( szRecName + zstrlen( szRecName ), zsizeof( szRecName ) - zstrlen( szRecName ), vTZTENVR1, "TE_TablRec", "Name" );
         }
         else
            GetStringFromAttribute( szRecName, zsizeof( szRecName ), vTZTENVR1, "TE_TablRec", "Name" );

         SetAttributeFromString( vTZZOXODO, "RELRECORD", "RECNAME", szRecName );

         if ( *pszParadigm == 'R' )
         {
            ofnTZZOXODO_BldRelFieldsForMM( vSubtask, vTZZOXODO, vTZTENVR1, vTZZOXOD1, vTZTENVR1_Alt, vTZZOLOD1, plAttrCount );
         }
         else
         {
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "RECID", vTZTENVR1, "TE_TablRec", "DBMS_ID" );
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "SETID1", vTZTENVR1, "TE_FieldDataRel", "DBMS_ID" );
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "SETNAME1",  vTZTENVR1, "TE_FieldDataRel", "Name" );
         }

         if ( SetCursorNextEntity( vTZTENVR1, "TE_FieldDataRel", 0 ) <  zCURSOR_SET )
         {
            nRC = SetCursorPrevEntity( vTZTENVR1, "TE_FieldDataRel", 0 );
         }

         if ( *pszParadigm == 'N' )
         {
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "SETID2", vTZTENVR1, "TE_FieldDataRel", "DBMS_ID" );
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "SETNAME2", vTZTENVR1, "TE_FieldDataRel", "Name" );
         }
      }
   }
   else
   {
      SetViewFromView( vTZTENVR1, vTZTENVRO_REF );
      SetViewFromView( vTZTENVR1_Alt, vTZTENVRO_Parent );
      nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_RelType_O", "ZKey", lRelTypeZKey, "TE_DBMS_Source" );
      if ( nRC < zCURSOR_SET )
      {
         SetViewFromView( vTZTENVR1, vTZTENVRO_Parent );
         SetViewFromView( vTZTENVR1_Alt, vTZTENVRO_REF );
         nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_RelType_O", "ZKey", lRelTypeZKey, "TE_DBMS_Source" );
      }

      if ( nRC >= zCURSOR_SET )
      {
         SetAttributeFromString( vTZZOXODO, "RELRECORD", "OWNER_MEMB", "M" );
         if ( *pszParadigm == 'R' )
         {
            ofnTZZOXODO_BldRelFieldFK( vTZZOXODO, vTZTENVR1, vTZZOXOD1, vTZTENVR1_Alt );
         }
         else
         {
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "SETID1", vTZTENVR1, "TE_FieldDataRel", "DBMS_ID" );
            SetAttributeFromAttribute( vTZZOXODO, "RELRECORD", "SETNAME1", vTZTENVR1, "TE_FieldDataRel", "Name" );
         }
      }
      else
      {
         GetStringFromAttribute( szSironDB_Type, zsizeof( szSironDB_Type ), vTZTENVR1, "TE_DBMS_Source", "SironDB_Type");
         if ( szSironDB_Type[ 0 ] != 'F' )
         {
            // For databases we have an error, when we get here.
            nRelError = 1;
         }
         else
         {
            // If the target entity for the relationship is a SironGroup, without a Katalog (meaning it is a subordinate Siron Group),
            // then it is valid to get here.
            // We know that it is a subordinate Siron Group if there is a relationship in the ERD and the entity has no key.
            GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vTZZOLOD1, "ER_EntityRec", "Name" );

            //  Get access to ER Object
            nRC = GetViewByName( &vERD, "TZEREMDO_REF", vSubtask, zLEVEL_TASK );

            CreateViewFromViewForTask( &vERDWork, vERD, 0 );
            nRC = SetCursorFirstEntityByAttr( vERDWork, "ER_Entity", "Name", vTZZOLOD1, "ER_EntityRec", "Name", 0 );
            nRelError = 0;
            if ( nRC >= zCURSOR_SET )
            {
               // Is there a relationship in the datamodel ????
               nRC = CheckExistenceOfEntity (vERDWork, "ER_RelLink" );
               if ( nRC == zCURSOR_SET )
               {
                   // Does the entity have a key attribute ????
                   nRC = SetCursorFirstEntity( vERDWork, "ER_Attribute", 0 );
                   while ( nRC >= zCURSOR_SET )
                   {
                       nRC = CompareAttributeToString( vERDWork, "ER_Attribute", "ParticipatesInKey", "Y" );
                       if ( nRC == 0 )
                       {
                           nRelError = 4;    // Entity has key attribute
                           break;
                       }
                       nRC = SetCursorNextEntity( vERDWork, "ER_Attribute", 0 );
                   }
               }
               else
               {
                  nRelError = 2;  // No Releationship in the ERD
               }
            }
            else
            {
               nRelError = 3;   // Entity not found in ERD
            }
         }

         if ( nRelError > 0 )
         {
            zCHAR   szRelName[ 100 ];
            zCHAR   szSrcEntity[ 33 ];
            zCHAR   szTgtEntity[ 33 ];
            zCHAR   szSrcRelLink[ 33 ];
            zCHAR   szMsg[ 500 ];

            SetNameForView( vTZTENVR1, "vTZTENVR1", vSubtask, zLEVEL_TASK );
            SetNameForView( vTZZOLOD1, "vTZZOLOD1", vSubtask, zLEVEL_TASK );

         // TraceLineI( "Search failed in view TZTENVR1 for ER_RelLinkRec ZKey:", lRelLinkZKey );
         // TraceLineS( "Display TZTENVR1", "###############################################################" );
         //xDisplayObjectInstance( vTZTENVR1, "", "" );
         // TraceLineI( "Search failed in view TZZOLOD1 for ER_RelTypeRec ZKey:", lRelTypeZKey );
         // TraceLineS( "Display TZZOLOD1", "###############################################################" );
         //xDisplayObjectInstance( vTZZOLOD1, "", "" );

            //------------------------------------------------------------------------
            strcpy_s( szRelName, zsizeof( szRelName ), "Relationship: '" );
            GetStringFromAttribute( szSrcEntity, zsizeof( szSrcEntity ), vTZZOXOD1, "ENTITY", "NAME" );

            strcat_s( szRelName, zsizeof( szRelName ), szSrcEntity );
            strcat_s( szRelName, zsizeof( szRelName ), " (" );

            GetStringFromAttribute( szSrcRelLink, zsizeof( szSrcRelLink ), vTZZOLOD1, "ER_RelLinkRec", "Name" );

            strcat_s( szRelName, zsizeof( szRelName ), szSrcRelLink );
            strcat_s( szRelName, zsizeof( szRelName ), ") " );
            GetStringFromAttribute( szTgtEntity, zsizeof( szTgtEntity ), vTZZOLOD1, "LOD_EntityParent", "Name" );
            strcat_s( szRelName, zsizeof( szRelName ), szTgtEntity );
            strcat_s( szRelName, zsizeof( szRelName ), "'" );
            //------------------------------------------------------------------------

            strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Relationship in TE.\n\n" );
            strcat_s( szMsg, zsizeof( szMsg ), szRelName );
            strcat_s( szMsg, zsizeof( szMsg ), "\n\nA relationship may have been deleted and recreated with " );
            strcat_s( szMsg, zsizeof( szMsg ), "a new name or your ER may be out of sync with your TE. " );
            strcat_s( szMsg, zsizeof( szMsg ), "\nIf you recreated a relationship with a new name, you must delete" );
            strcat_s( szMsg, zsizeof( szMsg ), " and recreate the subobject in the LOD." );
            strcat_s( szMsg, zsizeof( szMsg ), "\nNote the possibility that the entity may not have an \"Identifier\" defined." );
            strcat_s( szMsg, zsizeof( szMsg ), "\nIf your ER is out of sync with the TE, you must delete and recreate your " );
            strcat_s( szMsg, zsizeof( szMsg ), "tables and relationships in the TE." );
            MessageSend( vSubtask, "ZO00305", "Operations", szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         }
      }
   }

   DropView( vTZTENVR1_Alt );
   DropView( vTZTENVR1 );
   DropView( vTZZOXOD1 );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldRelFieldFK
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldRelFieldFK( zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF,
                           zVIEW vTZZOXOD1, zVIEW vTZTENVR1_Alt )
{
   zVIEW  vTZTENVR1;
   zLONG  lRelLinkZKey;
   zLONG  lEntityZKey;
   zLONG  lAttrZKey;
   zLONG  lFK_ZKey;
   zSHORT nRC;

   CreateViewFromViewForTask( &vTZTENVR1, vTZTENVRO_REF, 0 );

   GetIntegerFromAttribute( &lRelLinkZKey, vTZTENVRO_REF, "ER_RelLink", "ZKey" );

   // Position on the TE_FieldDataRel entity that is the first foreign key for the RelLink.
   // We must be careful not to stop at an AutoSeq field by mistake.
   for ( nRC = SetCursorFirstEntityByInteger( vTZTENVRO_REF, "ER_RelLink", "ZKey", lRelLinkZKey, "TE_DBMS_Source" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntityByInteger( vTZTENVRO_REF, "ER_RelLink", "ZKey", lRelLinkZKey, "TE_DBMS_Source" ) )
   {
      if ( CheckExistenceOfEntity( vTZTENVRO_REF, "TE_FieldDataRel_PK" ) >= zCURSOR_SET )
      {
         break;
      }
   }

   // Loop for each foreign key used to implement the relationship.
   while ( nRC >= zCURSOR_SET )
   {
      nRC = CreateEntity( vTZZOXODO, "RELFIELD", zPOS_AFTER );

      // Determine if the Foreign keys for this relationship are on parent or self.
      // Note that the owner always has the Foreign keys.
      if ( CompareAttributeToString( vTZZOXODO, "RELRECORD", "OWNER_MEMB", "O" ) == 0 )
      {
         // The Foreign keys for this relationship are on self.
         GetIntegerFromAttribute( &lEntityZKey, vTZZOXOD1, "ENTITY", "ERENT_TOK" );

         // Position on parent Entity in TE
         nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_Entity", "ZKey", lEntityZKey, "TE_DBMS_Source" );
         if ( nRC < zCURSOR_SET )
         {
            SetViewFromView( vTZTENVR1, vTZTENVR1_Alt );
            nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_Entity", "ZKey", lEntityZKey, "TE_DBMS_Source" );
            if ( nRC < zCURSOR_SET )
            {
               zCHAR    szMsg[ 500 ];
               zPCHAR   pchMsgName;

               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Entity for Bld FK in TE.\n\nEntity Name = " );
               GetAddrForAttribute( &pchMsgName, vTZZOXOD1, "ENTITY", "NAME" );
               strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
               strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities and relationships with ER Model" );

               MessageSend( vTZZOXOD1, "ZO00312", "Operations",
                            szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               return( 0 );
            }
         }
         // Position on parent Entity primary key which matches self's foreign key *HH* take care:
         //  if it is a "switched" foreign key, then the TE_FieldDataRel_PK might be the Base Key, which ist NOT in the parent.
         nRC = LocateTE_Field_PK( vTZTENVR1, vTZTENVRO_REF );
         if ( nRC < zCURSOR_SET ||
              CompareAttributeToAttribute( vTZZOXOD1, "ENTITY", "ERENT_TOK", vTZTENVR1, "ER_Entity", "ZKey" ) != 0 )
         {
            // The foreign key on self matches a foreign key on parent and this is typically the case in relationship based identifiers where
            // the foreign key on parent is part of it's key.
            SetCursorFirstEntityByEntityCsr( vTZTENVR1, "TE_FieldDataRel_PK", vTZTENVRO_REF, "TE_FieldDataRel_PK", "TE_TablRec" );
            GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "TE_FieldDataRel", "ZKey" );

            // Position on parent Entity attribute which is a foreign key which participates in the key for parent.
            SetCursorFirstEntityByInteger( vTZZOXOD1, "ATTRIB", "ERATT_TOK", lAttrZKey, "" );
         }
         else
         {
            // The foreign key on self matches a primary key on parent we will now determine if the primary key on parent is visible or manufactured.
            if ( CheckExistenceOfEntity( vTZTENVR1, "ER_Attribute" ) >= zCURSOR_SET )
               GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "ER_Attribute", "ZKey" );
            else
               GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "TE_FieldDataRel", "ZKey" );

            // Position on parent Entity attribute which participates in the key for parent.
            SetCursorFirstEntityByInteger( vTZZOXOD1, "ATTRIB", "ERATT_TOK", lAttrZKey, "" );
         }

         // Position on the ATTRIB which implements this foreign key on self.  If the FK is an ER attribute, which is only possible in "wrong"
         // SAP data models, then we go by the ZKey of the ER attribute.
         if ( CheckExistenceOfEntity( vTZTENVRO_REF, "ER_Attribute" ) >= zCURSOR_SET )
            GetIntegerFromAttribute( &lFK_ZKey, vTZTENVRO_REF, "ER_Attribute", "ZKey" );
         else
            GetIntegerFromAttribute( &lFK_ZKey, vTZTENVRO_REF, "TE_FieldDataRel", "ZKey" );

         SetCursorFirstEntityByInteger( vTZZOXODO, "ATTRIB", "ERATT_TOK", lFK_ZKey, "" );

         // Set SRCXVATT_TOK from parent key and RELXVAATT_TOK from foreign key on self.
         if ( CheckExistenceOfEntity( vTZZOXOD1, "ATTRIB" ) >= zCURSOR_SET )
            SetAttributeFromAttribute( vTZZOXODO, "RELFIELD", "SRCXVAATT_TOK", vTZZOXOD1, "ATTRIB", "XVAATT_TOK" );

         if ( CheckExistenceOfEntity( vTZZOXODO, "ATTRIB" ) >= zCURSOR_SET )
            SetAttributeFromAttribute( vTZZOXODO, "RELFIELD", "RELXVAATT_TOK", vTZZOXODO, "ATTRIB", "XVAATT_TOK" );
      }
      else // The relationship being implemented is implemented on parent
      {
         GetIntegerFromAttribute( &lEntityZKey, vTZZOXODO, "ENTITY", "ERENT_TOK" );
         nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_Entity", "ZKey", lEntityZKey, "TE_DBMS_Source" );
         if ( nRC < zCURSOR_SET )
         {
            SetViewFromView( vTZTENVR1, vTZTENVR1_Alt );
            nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_Entity","ZKey", lEntityZKey, "TE_DBMS_Source" );
            if ( nRC < zCURSOR_SET )
            {
               zCHAR    szMsg[500];
               zPCHAR   pchMsgName;

               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Parent Entity for Bld FK in TE.\n\nEntity Name = " );
               GetAddrForAttribute( &pchMsgName, vTZZOXOD1, "ENTITY", "NAME" );
               strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
               strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities and relationships with ER Model" );
               MessageSend( vTZZOXOD1, "ZO00313", "Operations",
                            szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               return( 0 );
            }
         }

         // *HH*
         //  vTZTENVR1 is positioned on the LOD parent entity.
         //  vTZTENVRO_REF is on the current entity containing the foreign key.
         //  the corresponding key in vTZTENVR1 should be gotten via TE_FieldDataRel_PK.
         //  However, if the Foreign Key was "switched over to another one" as it
         //  might be done by TE - Foreign Key Maintenance or by SAP TE creation,
         //  then the TE_FieldDataRel_PK is the "Base Key", which is implemented as
         //  an ER Attribute and is not neccessarily in the LOD parent (see vTZTENVR1).
         //  We then have to find the key part in TZTENVR1, which is going to the same Base Key.
         nRC = LocateTE_Field_PK( vTZTENVR1, vTZTENVRO_REF );
         if ( nRC < zCURSOR_SET ||
              CompareAttributeToAttribute( vTZZOXODO, "ENTITY", "ERENT_TOK", vTZTENVR1, "ER_Entity", "ZKey" ) != 0 )
         {
            SetCursorFirstEntityByEntityCsr( vTZTENVR1, "TE_FieldDataRel_PK", vTZTENVRO_REF, "TE_FieldDataRel_PK", "TE_TablRec" );
            GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "TE_FieldDataRel", "ZKey" );
            SetCursorFirstEntityByInteger( vTZZOXODO, "ATTRIB", "ERATT_TOK", lAttrZKey, "" );
         }
         else
         {
            if ( CheckExistenceOfEntity( vTZTENVR1, "ER_Attribute" ) >= zCURSOR_SET )
            {
               GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "ER_Attribute", "ZKey" );
            }
            else
            {
               GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "TE_FieldDataRel", "ZKey" );
            }

            SetCursorFirstEntityByInteger( vTZZOXODO, "ATTRIB", "ERATT_TOK", lAttrZKey, "" );
         }

         GetIntegerFromAttribute( &lFK_ZKey,
                                  vTZTENVRO_REF, "TE_FieldDataRel", "ZKey" );
         SetCursorFirstEntityByInteger( vTZZOXOD1, "ATTRIB", "ERATT_TOK", lFK_ZKey, "" );
         SetAttributeFromAttribute( vTZZOXODO, "RELFIELD", "SRCXVAATT_TOK", vTZZOXODO, "ATTRIB", "XVAATT_TOK" );
         SetAttributeFromAttribute( vTZZOXODO, "RELFIELD", "RELXVAATT_TOK", vTZZOXOD1, "ATTRIB", "XVAATT_TOK" );
      }

      nRC = SetCursorNextEntityByInteger( vTZTENVRO_REF, "ER_RelLink", "ZKey", lRelLinkZKey, "TE_TablRec" );
   }

   DropView( vTZTENVR1 );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_BldRelFieldsForMM
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldRelFieldsForMM( zVIEW vSubtask, zVIEW vTZZOXODO, zVIEW vTZTENVRO_REF,
                               zVIEW vTZZOXOD1, zVIEW vTZTENVR1_Alt,
                               zVIEW vTZZOLOD1, zPLONG plAttrCount )
{
   zVIEW  vTZTENVR1;
   zLONG  lRelTypeZKey;
   zLONG  lAttrZKey;
   zSHORT nRC;

   CreateViewFromViewForTask( &vTZTENVR1, vTZTENVRO_REF, 0 );

   GetIntegerFromAttribute( &lRelTypeZKey, vTZTENVRO_REF, "ER_RelType_O", "ZKey" );
   nRC = SetCursorFirstEntityByInteger( vTZTENVRO_REF, "ER_RelType_O", "ZKey", lRelTypeZKey, "TE_TablRec" );
   while ( nRC >= zCURSOR_SET )
   {
      if ( CheckExistenceOfEntity( vTZTENVRO_REF, "TE_FieldDataRel_PK" ) < zCURSOR_SET )
      {
         // If there is no PK entity, process as an AUTOSEQ field.

         CreateEntity( vTZZOXODO, "ATTRIB", zPOS_LAST );
         (*plAttrCount)++;
         SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", *plAttrCount );
         ofnTZZOXODO_BldAutoSeq( vSubtask, vTZZOXODO, vTZTENVRO_REF, vTZZOLOD1 );
      }
      else
      {
         // Process as Rel Field.
         CreateEntity( vTZZOXODO, "RELFIELD", zPOS_LAST );

         // In general it's enough to compare the tokens of the rellink.
         // if they match then we got the right one (if it's not a RECURSIVE relationship).
         // to be shure whether it is not recursive we also look at the RelLink of the LOD.
         if ( CompareAttributeToAttribute( vTZTENVRO_REF, "ER_EntityRelLink", "ZKey", vTZZOXODO, "ENTITY", "ERENT_TOK" ) == 0 &&
              CompareAttributeToAttribute( vTZTENVRO_REF, "ER_RelLink", "ZKey", vTZZOLOD1, "ER_RelLinkRec", "ZKey" ) != 0 )
         {
            ofnTZZOXODO_PosOnBaseField( vTZZOXODO, vTZTENVRO_REF, vTZTENVR1, vTZTENVR1_Alt );

            if ( CompareAttributeToString( vTZTENVR1, "TE_TablRec", "DataOrRel", "D" ) == 0 )
            {
               if ( CheckExistenceOfEntity( vTZTENVR1, "ER_Attribute" ) >= zCURSOR_SET )
                  GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "ER_Attribute", "ZKey" );
               else
                  GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "TE_FieldDataRel", "ZKey" );
            }
            else
            {
               GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "TE_FieldDataRel_PK", "ZKey" );
            }

            nRC = SetCursorFirstEntityByInteger( vTZZOXODO, "ATTRIB", "ERATT_TOK", lAttrZKey, "" );
            if ( nRC >= zCURSOR_SET )
            {
               SetAttributeFromAttribute( vTZZOXODO, "RELFIELD", "SRCXVAATT_TOK", vTZZOXODO, "ATTRIB", "XVAATT_TOK" );
            }
         }
         else
         {
            if ( CompareAttributeToAttribute( vTZTENVRO_REF, "ER_EntityRelLink", "ZKey", vTZZOXOD1, "ENTITY", "ERENT_TOK" ) == 0 )
            {
               ofnTZZOXODO_PosOnBaseField( vTZZOXOD1, vTZTENVRO_REF, vTZTENVR1, vTZTENVR1_Alt );
               if ( CompareAttributeToString( vTZTENVR1, "TE_TablRec", "DataOrRel", "D" ) == 0 )
               {
                  if ( CheckExistenceOfEntity( vTZTENVR1, "ER_Attribute" ) >= zCURSOR_SET )
                  {
                     GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "ER_Attribute", "ZKey" );
                  }
                  else
                  {
                     GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "TE_FieldDataRel", "ZKey" );
                  }
               }
               else
               {
                  GetIntegerFromAttribute( &lAttrZKey, vTZTENVR1, "TE_FieldDataRel_PK", "ZKey" );
               }

               nRC = SetCursorFirstEntityByInteger( vTZZOXOD1, "ATTRIB", "ERATT_TOK", lAttrZKey, "" );
               if ( nRC >= zCURSOR_SET )
               {
                  nRC = SetAttributeFromAttribute( vTZZOXODO, "RELFIELD", "SRCXVAATT_TOK", vTZZOXOD1, "ATTRIB", "XVAATT_TOK" );
               }
            }
         }

         SetAttributeFromAttribute( vTZZOXODO, "RELFIELD", "FLDNAME", vTZTENVRO_REF, "TE_FieldDataRel", "Name" );
      }

      nRC = SetCursorNextEntityByInteger( vTZTENVRO_REF, "ER_RelType_O", "ZKey", lRelTypeZKey, "TE_TablRec" );
   }

   DropView( vTZTENVR1 );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: ofnTZZOXODO_PosOnBaseField
//
// TRIGGLODED BY:
//    WINDOW: TZZOLODD
//    ACTION: OPTION
//    NAME: File_Save
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_PosOnBaseField( zVIEW vTZZOXODO,
                            zVIEW vTZTENVRO_REF, zVIEW vTZTENVR1,
                            zVIEW vTZTENVR1_Alt )
{
   zLONG  lEntityZKey;
   zSHORT nRC;

   GetIntegerFromAttribute( &lEntityZKey, vTZZOXODO, "ENTITY", "ERENT_TOK" );
   nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_Entity", "ZKey", lEntityZKey, "TE_DBMS_Source" );
   if ( nRC < zCURSOR_SET )
   {
      SetViewFromView( vTZTENVR1, vTZTENVR1_Alt );
      nRC = SetCursorFirstEntityByInteger( vTZTENVR1, "ER_Entity", "ZKey", lEntityZKey, "TE_DBMS_Source" );
      if ( nRC < zCURSOR_SET )
      {
         zCHAR    szMsg[500];
         zPCHAR   pchMsgName;

         strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Entity for Base Field in TE.\n\nEntity Name = " );
         GetAddrForAttribute( &pchMsgName, vTZZOXODO, "ENTITY", "NAME" );
         strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
         strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );
         MessageSend( vTZZOXODO, "ZO00314", "Operations",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( 0 );
      }
   }

   nRC = SetCursorFirstEntityByEntityCsr( vTZTENVR1, "TE_FieldDataRel", vTZTENVRO_REF, "TE_FieldDataRel_PK", "TE_TablRec" );
   if ( nRC < zCURSOR_SET )
   {
      nRC = SetCursorFirstEntityByEntityCsr( vTZTENVR1, "TE_FieldDataRel_PK", vTZTENVRO_REF, "TE_FieldDataRel_PK", "TE_TablRec" );
   }

   if ( nRC < zCURSOR_SET )
   {
      zCHAR    szMsg[500];
      zPCHAR   pchMsgName;

      strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Base Field in TE.\n\nEntity Name = " );
      GetAddrForAttribute( &pchMsgName, vTZZOXODO, "ENTITY", "NAME" );
      strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
      strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );

      MessageSend( vTZZOXODO, "ZO00315", "Operations",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_BldAutoSeq( zVIEW vSubtask, zVIEW vTZZOXODO,
                        zVIEW vTZTENVRO_REF, zVIEW vTZZOLOD1 )
{
   zVIEW  vDomain;
   zSHORT nRC;

   // Build the ATTRIB data for an AutoSeq field.
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "NAME", vTZTENVRO_REF, "TE_FieldDataRel", "Name" );

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "LTH", vTZTENVRO_REF, "TE_FieldDataRel", "Length" );

   // Frank H. (07/04/16): fill the ERATT_TOK with the ZKey of the FieldData
   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "ERATT_TOK", vTZTENVRO_REF, "TE_FieldDataRel", "ZKey" );

   SetAttributeFromString( vTZZOXODO, "ATTRIB", "HIDDEN", "Y" );
   SetAttributeFromString( vTZZOXODO, "ATTRIB", "PERSIST", "Y" );

   if ( CheckExistenceOfEntity( vTZZOLOD1, "ER_RelLinkRec" ) == 0 &&
        CompareAttributeToAttribute( vTZTENVRO_REF, "ER_RelLink", "ZKey", vTZZOLOD1, "ER_RelLinkRec", "ZKey" ) == 0 )
   {
      SetAttributeFromString( vTZZOXODO, "ATTRIB", "AUTO_SEQ", "Y" );
   }

   // Retrieve the Integer domain and set up corresponding values in ATTRIB entity.
   nRC = ActivateMetaOI_ByName( vSubtask, &vDomain, 0, zREFER_DOMAIN_META, zSINGLE, "Integer", 0 );
   if ( nRC < zCURSOR_SET )
   {
      MessageSend( vSubtask, "ZO00316", "Operations",
                   "Missing Integer Domain required by AutoSeq field.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( 0 );
   }

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "DOMAIN", vDomain, "Domain", "Name" );

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "APDM_TOK", vDomain,   "Domain", "ZKey" );

   SetAttributeFromAttribute( vTZZOXODO, "ATTRIB", "TYPE", vDomain,   "Domain", "DataType" );
   DropMetaOI( vSubtask, vDomain );

   //
   // Create and build the DATAFIELD data for AutoSeq field if there is a DATARECORD entry.
   //
   if ( CheckExistenceOfEntity( vTZZOXODO, "DATARECORD" ) >= zCURSOR_SET )
   {
      CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_LAST );
      SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDLTH", vTZZOXODO, "ATTRIB", "LTH" );

      SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDNAME", vTZZOXODO, "ATTRIB", "NAME" );

      SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "FLDTYPE", vTZZOXODO, "ATTRIB", "TYPE" );

      SetAttributeFromAttribute( vTZZOXODO, "DATAFIELD", "XVAATT_TOK", vTZZOXODO, "ATTRIB", "XVAATT_TOK" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ofnTZZOXODO_ProcDupEntity( zVIEW vSubtask, zVIEW vTZZOXODO,
                           zVIEW vTZEREMDO_REF,
                           zVIEW vTZTENVRO_REF,
                           zVIEW vTZZOLOD1,
                           zPLONG plAttrCount )
{
   zVIEW  vLOD2;
   zSHORT nRC;

   // If the LOD_Entity specifies "DupEntityInstance", then make sure that all
   // Attributes for any other LOD_Entity for the same ER_Entity are in the XOD.
   // Without this change, some Attribute values for such entities will not
   // be read and will incorrectly appear as null.
   return( 0 );

   if (  CompareAttributeToString( vTZZOLOD1, "LOD_EntityParent", "DupEntityInstance", "Y" ) == 0 &&
         CheckExistenceOfEntity( vTZZOLOD1, "ER_EntityRec" ) >= zCURSOR_SET )
   {
      zCHAR szDEBUGCHG[ 33 ];

      szDEBUGCHG[ 0 ] = 0;  // can't get to here anyhow because of above return

      CreateViewFromViewForTask( &vLOD2, vTZZOLOD1, 0 );

      // Loop through all LOD_Entities for the same ER Entity that also specify DupEntityInstance and make sure all of their attributes
      // are included under this XOD ENTITY.
      for ( nRC = SetCursorFirstEntityByEntityCsr( vLOD2, "ER_Entity", vTZZOLOD1, "ER_EntityRec", "LOD" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntityByEntityCsr( vLOD2, "ER_Entity", vTZZOLOD1, "ER_EntityRec", "LOD" ) )
      {
         // Skip the original entity.
         if ( CompareAttributeToAttribute( vLOD2, "LOD_Entity", "ZKey", vTZZOLOD1, "LOD_EntityParent", "ZKey" ) == 0 )
            continue;

         // Skip if it is not a DupEntityInstance.
         if ( CompareAttributeToString( vLOD2, "LOD_Entity", "DupEntityInstance", "Y" ) == 0 )
         {
            continue;
         }

         // Loop through all the attributes under this LOD entity and make sure all ER attributes exist under the original LOD entity.
         for ( nRC = SetCursorFirstEntity( vLOD2, "LOD_Attribute", 0 );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntity( vLOD2, "LOD_Attribute", 0 ) )
         {
            // Skip if the ER_Attribute is already there.
            nRC = SetCursorFirstEntityByEntityCsr( vTZZOLOD1, "ER_AttributeRec", vLOD2, "ER_Attribute", "LOD_EntityParent" );
            if ( nRC >= zCURSOR_SET )
               continue;

            // Skip if it's a work attribute.
            if ( CompareAttributeToString( vLOD2, "ER_Attribute", "Work", "Y" ) != 0 &&
                 CompareAttributeToString( vLOD2, "LOD_Attribute", "Work", "Y" ) != 0 &&
                 CompareAttributeToString( vLOD2, "ER_Entity", "Purpose", "W" ) != 0 )
               continue;

            CreateEntity( vTZZOXODO, "ATTRIB", zPOS_AFTER );
            *plAttrCount++;
            SetAttributeFromInteger( vTZZOXODO, "ATTRIB", "XVAATT_TOK", *plAttrCount );
            ofnTZZOXODO_BldXODAttrib( vSubtask, vTZZOXODO, vLOD2, vTZEREMDO_REF, szDEBUGCHG );

            if ( SetCursorFirstEntityByAttr( vTZTENVRO_REF, "ER_Attribute", "ZKey", vLOD2, "ER_Attribute", "ZKey", "TE_TablRec" ) < zCURSOR_SET )
            {
               zCHAR    szMsg[500];
               zPCHAR   pchMsgName;

               strcpy_s( szMsg, zsizeof( szMsg ), "Unable to Find Attribute in TE.\n\nAttr Name = " );
               GetAddrForAttribute( &pchMsgName, vLOD2, "ER_Attribute", "Name" );
               strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
               strcat_s( szMsg, zsizeof( szMsg ), "\nfor entity: " );
               GetAddrForAttribute( &pchMsgName, vLOD2, "ER_Entity", "Name" );
               strcat_s( szMsg, zsizeof( szMsg ), pchMsgName );
               strcat_s( szMsg, zsizeof( szMsg ), "\n\n Please re-synchronize the TE entities with ER Model" );
               MessageSend( vSubtask, "ZO00306", "Operations",
                            szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               break;
            }

            CreateEntity( vTZZOXODO, "DATAFIELD", zPOS_AFTER );
            ofnTZZOXODO_BldXODDataField( vSubtask, vTZZOXODO, vTZTENVRO_REF );

         } // for each LOD_Attribute
      } // for each LOD_Entity with same ER_Entity

      DropView( vLOD2 );

   } // if ( CheckExistenceOfEntity( vTZZOLOD1, "ER_EntityRec" ) >= zCURSOR_SET )...

   return( 0 );
}

// For a TE_Field in the current entity (vTZTENVRO_REF), find the matching key field in the parent (vTZTENVR1).
// This code regards the special circumstances of "foreign key switching".
static zSHORT
LocateTE_Field_PK( zVIEW vTZTENVR1, zVIEW vTZTENVRO_REF )
{
   zVIEW vTZTENVR2;
   zLONG lZKeyBase = -1;
   zSHORT nRC;

   // First try to find  the PK inside the parent table.
   nRC = SetCursorFirstEntityByEntityCsr( vTZTENVR1, "TE_FieldDataRel", vTZTENVRO_REF, "TE_FieldDataRel_PK", "TE_TablRec" );
   if ( nRC >= zCURSOR_SET )
      return( nRC ); // fine, the PK is in the parent

   // We assume, that the _PK from vTZTENVRO_REF is pointing to the Base Key.  This can't be true, if the _PK is not a ER attribute.
   if ( CompareAttributeToString( vTZTENVRO_REF, "TE_FieldDataRel_PK", "DataOrRelfieldOrSet", "D" ) != 0 )
   {
      return( nRC ); // no it is NOT the Base Key
   }

   // Now, check for a key attribute going to the same Base Key.
   GetIntegerFromAttribute( &lZKeyBase, vTZTENVRO_REF, "TE_FieldDataRel_PK", "ZKey" );
   CreateViewFromViewForTask( &vTZTENVR2, vTZTENVR1, 0 );
   SetCursorFirstEntity( vTZTENVR2, "TE_TablRecKey", "" ); // not necessary

   // The candidate must be a foreign key, DataOrRelfieldOrSet = "R".
   for ( nRC = SetCursorFirstEntityByString( vTZTENVR2, "TE_FieldDataRelKey", "DataOrRelfieldOrSet", "R", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntityByString( vTZTENVR2, "TE_FieldDataRelKey", "DataOrRelfieldOrSet", "R", 0 ) )
   {
      SetCursorFirstEntityByEntityCsr( vTZTENVR2, "TE_FieldDataRel", vTZTENVR2, "TE_FieldDataRelKey", 0 );
      if ( GetBaseKey( vTZTENVR2 ) == lZKeyBase )
         break;
   }

   if ( nRC >= zCURSOR_SET )
   {
      // That is the one we need.
      SetCursorFirstEntityByEntityCsr( vTZTENVR1, "TE_FieldDataRel", vTZTENVR2, "TE_FieldDataRelKey", 0 );
   }

   return( nRC );
}

// Go down the TE_FieldDataRel_PK chain, until an ER attribute is found.
static zLONG
GetBaseKey( zVIEW vTZTENVRO )
{
   zVIEW vTZTENVR3, vTZTENVR4;
   zLONG lZKey = 0;
   zSHORT nRC;

   if ( CompareAttributeToString( vTZTENVRO, "TE_FieldDataRel_PK", "DataOrRelfieldOrSet", "D" ) == 0 )
   {
      GetIntegerFromAttribute( &lZKey, vTZTENVRO, "TE_FieldDataRel_PK", "ZKey" );
      return( lZKey );
   }

   CreateViewFromViewForTask( &vTZTENVR3, vTZTENVRO, 0 );
   nRC = SetCursorFirstEntityByAttr( vTZTENVR3, "TE_FieldDataRel", "ZKey", vTZTENVRO, "TE_FieldDataRel_PK", "ZKey", "TE_DBMS_Source" );
   while ( nRC >= zCURSOR_SET &&
          CompareAttributeToString( vTZTENVR3, "TE_FieldDataRel_PK", "DataOrRelfieldOrSet", "D" ) != 0 )
   {
      CreateViewFromViewForTask( &vTZTENVR4, vTZTENVR3, 0 );
      nRC = SetCursorFirstEntityByAttr( vTZTENVR3, "TE_FieldDataRel", "ZKey", vTZTENVR4, "TE_FieldDataRel_PK", "ZKey", "TE_DBMS_Source" );
      DropView( vTZTENVR4 );
   }

   GetIntegerFromAttribute( &lZKey, vTZTENVR3, "TE_FieldDataRel_PK", "ZKey" );
   DropView( vTZTENVR3 );
   return( lZKey );
}

///////////////////////////// end of file  //////////////////////////////////