/////////////////////////////////////////////////////////////////////////////
//
// MODULE NAME:   tzcmoprs.c - Zeidon application operations
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
// LAST MESSAGE ID: CM00472
//
// HISTORY:
//
//    1995/08/05: Beginning of 10B branch
//
/////////////////////////////////////////////////////////////////////////////
//

/*
CHANGE LOG
2001.11.27    DKS    WEB
   Added operation SetUpMapLOD in support of setting the DataType for
   each Column of a ListBox in the XRA.
2001.07.20 RG
   Added Operation: SetCompSpecPaths
2001.07.06 RG
   Added Operation: IntGenFullQualPathFromRelPath
2001.06.11 BL
   Modified LoadZeidonPPE for set correct Return Value
2001.05.10 BL
   Modified ComponentIsCheckedOut for recurvice Entities
2001.04.09 PAS
   Changed usage of INI setting to force the writing of binary data and also
   use the "ReleaseVersion" in the file header to make sure that once a source
   meta is stored with the new format it will not accidently revert back to
   the previous format.
2001.03.12 PAS
   Changed calls to CommitOI_ToFile for all "source" metas to use zENCODE_BLOBS
   flag.  This encodes binary to characters between 0x20 and 0x7F.
2001.03.27 RG  R54738
   Delete of XRP, XSQ and REP file for Reports too
2001.03.01 BL
   Fix for Windows 98; change TaskID > 0 to TaskID (Win9x has negative IDs)
2001.02.12 BL  R54697
   Modified InitializeLPLR for do not show a rebuild message
2000.12.12 DKS Z2000
   Change CreateMetaEntity and CreateTemporalMetaEntity to ensure a valid
   ZKey is generated ... if a ZKey below 1 million is generated, it can
   cause the VML generator to generate an invalid XPG file since it assumes
   the nOffset member of the sQExprStruct structure to be an offset if its
   value is less than MAXSTRING, and a ZKey otherwise.
2000.11.02 DGC Z2000
   Change CommitMetaOI( vSubtask ) to NOT use a temp file name. Core now automatically
   creates a backup file when saving OIs.
2000.10.30 RG  Z2000
    GetViewByName: for parameter zLEVEL_TASK changed View --> 0
2000.10.23  SR  Z2000 Size of path variables
   Modified size of file specification variables in functions LoadZeidonPPE,
   BuildLPLR_MetaTypes, CreatePE_ExecVersion, DeleteMetaOI,
   CommitDependentOI, fnCommitMetaOI and fnActivateMetaOI
   because size of attributes ExecDir, MetaSrcDir and PgmSrcDir has
   been changed to 254 in datamodel.
   Adjust the size of messagetext variables.

2000.06.25   BL
   Modified SetTitleWithCheckOutState and ComponentIsCheckedOut
   for Reports

2000.06.20   BL  Bug R53235
   Modified fnCommitMetaOI: CommitOI_ToFile without zINCREMENTAL

2000.06.05   BL
   Rename BiancaFromBinSys in PPE_FromBinSys

2000.05.03   BL
   Modified ComponentIsCheckedOut for Dialogs

2000.04.27   BL
   Bugfix ComponentIsCheckedOut

2000.04.12   HH
   Activate WorkStation with zIGNORE_ATTRIB_ERRORS.

2000.03.28   BL
   Modified Title for check out state in SetTitleWithCheckOutState and
   CheckOutStateForCurrentWindow. This is necessary for Zeidon-Test

2000.02.28  BL
   Added SaveSortOrder for save sort order in window "Open Component"
   (for example "Open Domain")
   Added SortComponents for sort components in window "Open Component"
   (for example "Open Domain")

2000.02.25  BL
   Modified ComponentIsCheckedOut for Domains and Global Operations
   Added CheckOutStateForCurrentWindow: for windows within Tools (for
   example Open Domain): set check out state in title
   Added SetTitleWithCheckOutState: set Project name, Tool name, component name
   and check out state in title

2000.02.17  BL
   Added CheckAllDuplicateName, CheckDuplicateName, CheckDuplicateNameForRefresh:
   Check duplicate component names
   Added CheckDuplicateComponents: Check: duplicate component types between CPLR
   and LPLR (for ERD, TE, PPE )

2000.02.01  BL    Z10  PPE
   Modified CreatePE_ExecVersion for delete access to Attribute CtrlFontDel
   (is deleted in LOD TZPESRCO)

2000.01.30  BL    Z10  PPE
   Modified SfActivateSysOI_FromFile: XPE does not exists, then no error message

2000.01.28  BL    Z10  Repository
   Insert ComponentIsCheckedOut: if Component checked out

2000.01.19  HH    Z10  PPE
   PPE loaded from system directory must be in Zeidon Object thread.

2000.01.13  BL    Z10  PPE
   Modified fnActivateMetaOI: Load PPE from LPLR, not from system directory
   Insert LoadZeidonPPE: load PPE from LPLR directory, was not found then
   search in Zeidon Bin/Sys directory

1999.12.28, 1999.12.29  BL    Z10   Bugfix Repositiory
   Added Operation fnRemoveCreateFlag: is a Entity included and created,
   then remove the create-flag and modified Operation fnCommitMetaOI

1999.05.11  DKS   Z10   ActiveX
   Added ActiveX attributes.

14.04.1997  DonC
   Modified fnCommitMetaOI to eliminate LOD objects from the Active list
   during commit of ERD so that ERD changes would take immediate affect in
   other objects.

26.05.1997  DonC
   Corrected fnCommitMetaOI to eliminate error message on delete of Domain
   or Operation within Domain Group or Operation Group.

08.06.1997  DonC
   Removed nRC from two set cursor statements in InitializeLPLR because they
   were obscurring the nRC value returned from an earlier Activate.

09.07.1997  DonC
   Modified RetrieveViewForMetaList to add error message when return code
   for the get view for vTaskMetas is invalid.

05.09.1997  DonC
   Modified the CommitOI_ToFile logic for commiting metas so that the code
   first committed to a temporary file and then renamed the file to the
   correct name.

1997.11.13    DGC
   Changed CopyFile() to SysCopyFile().

05.12.1997  DonC
   Modified fnAcitvateMetaOI to make sure the LOD_Entity.IndentName value is
   actually indented.

14.01.1998  DonC
   Corrected processing of IndentName in fnActivateMetaOI.

17.01.1998  DonC
   Added relink of DomainGroup to ER on commit of DomainGrp in operation
   fnCommitMetaOI.

11.08.1998  DonC
   Modified fnActivateMetaOI to eliminate check for negative TaskID since it
   appears to be spurious code from the past that no longer is used (TaskID's
   didn't ever appear to be negative in 9I) and creates problems in 9J since
   a TaskID can now come back negative.

18.08.1998  DonC
   Modified InitializeLPLR to check that Workstation Administration is not
   running. (QS 190)

1998/09/08  DC
   Further eliminated code in fnActivateMetaOI that checked fror negative
   TaskID, as in above.

1998/09/18  DC
   Modified fnCommitMetaOI so that check for duplicate names for Operations
   and Domains worked properly. (TB 318)

1998/10/05  HH
   reversed Don's Change "1998/09/08  DC".
   It created a problem: open meta (repository), close Zeidon Tool,
   open meta again : Error message CM00416 .

1999.02.08  DKS
   Implemented save of .XRP which flattens the Control/CtrlCtrl structure.

1999.04.14  HH
   Improve error handling in fnCommitMetaOI (fail of SysRenameFile).
*/

#define _NOANCHOR
#include <zstdafx.h>
//#define zGLOBAL_DATA

#include "..\..\a\oe\kzoephdr.h"   // added to get "..\oe\kzoengaa.hg" to work
#include "tzlodopr.h"
#include "tz__oprs.h"
#include "tzcm_opr.hg"

#define ZDRAPP_CLASS AFX_EXT_CLASS
#include "..\zdr\Zdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "ZeidonOp.H"
#include "tzvmlip.h"

#define NAME_OF_CACHED_PPE "PPE_FromBinSys"

// following variable defined here because it was too hard for the linker to
// resolve the global variable defined in  "..\oe\kzoengaa.hg"
//*** NOTE: Go to "..\oe\kzoengaa.hg" to change the values.
zPCHAR szlReleaseCompatible = zRELEASE_COMPAT_LEVEL;
zPCHAR szlReleaseCurrent    = zRELEASE_CURRENT_LEVEL;

/*  local prototypes  */
zVIEW OPERATION
CreatePE_ExecVersion( zVIEW vSubtask, zVIEW vPresEnv );
zVIEW OPERATION
ConvertReport( zVIEW   vSubtask,
               zVIEW   vSrcReport,
               zCPCHAR szTgtRptName );
zVIEW OPERATION
ConvertXSLT( zVIEW   vSubtask,
             zVIEW   vSrcXSLT,
             zCPCHAR szTgtXSLT_Name );
zOPER_EXPORT zSHORT OPERATION
zGetFirstEntityNameForView( zVIEW   vViewToInstance,
                            zPCHAR  pchEntityName );
zOPER_EXPORT zSHORT OPERATION
zSearchAndReplace(zPCHAR  szTarget,
                  zCULONG ulTargetLen,
                  zCPCHAR szSearch,
                  zCPCHAR szReplace);

/////////////////////////////////////////////////////////////////////////////
// The following function checks the ZeidonRT.INI and Zeidon.INI for item
// AllowBinaryDataInSourceMetaFiles in the [ZeidonTools] section.  Return
// codes are as follows:
//    1 - INI item is 'Y' or not specified
//          (the meta file is written with the same manner as it existed)
//    2 - INI item is 'F' (force to old - with binary - format
//          regardless of it's current format)
//    3 - INI item is 'N' (write with the new format regardless of its
//          current format)
/////////////////////////////////////////////////////////////////////////////
zSHORT OPERATION
fnAllowBinaryDataInSourceMetaFiles( zVIEW lpTaskView )
{
   zCHAR szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR szBuffer[ 256 ];

   szBuffer[ 0 ] = 0;
   SysReadZeidonIni( -1, "[Workstation]", "LocalDir", szFileName, zsizeof( szFileName ) );
   if ( szFileName[ 0 ] )
   {
      SysAppendcDirSep( szFileName );
      strcat_s( szFileName, zsizeof( szFileName ), "ZeidonRT.ini" );
      GetPrivateProfileString( "ZeidonTools", "AllowBinaryDataInSourceMetaFiles", "", szBuffer, zsizeof( szBuffer ), szFileName );
   }

   if ( szBuffer[ 0 ] == 0 )
   {
      SysReadZeidonIni( -1, "[ZeidonTools]", "AllowBinaryDataInSourceMetaFiles", szBuffer, zsizeof( szBuffer ) );
   }

   if ( szBuffer[ 0 ] == 'N' || szBuffer[ 0 ] == 'n' )
      return( 3 );
   else
   if ( szBuffer[ 0 ] == 'F' || szBuffer[ 0 ] == 'f' )
      return( 2 );
   else
      return( 1 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
zSHORT
fnGetDirectorySpec( zVIEW vSubtask, zPCHAR pchDirectorySpec, zLONG lMaxLth, zLONG lType, zBOOL bConvertEnvironment )
{
   zVIEW vTaskLPLR;
   zCHAR szWork[ zMAX_FILESPEC_LTH + 1 ];

   pchDirectorySpec[ 0 ] = 0;
// MessageBox( 0, "TaskLPLR", "fnGetDirectorySpec", MB_OK );
   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
      return( -1 );

   if ( (lType < 0) || ((lType > zSOURCE_MAX_META) && (lType < 1000)) || ((lType > 1000) && (lType < 2000)) || (lType > zREFER_MAX_META) )
   {
      MessageSend( vSubtask, "CM00401", "Configuration Management",
                   "Invalid Zeidon Type passed to CM Operation",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   GetStringFromAttribute( szWork, zsizeof( szWork ), vTaskLPLR, "LPLR", "MetaSrcDir" );
   if ( bConvertEnvironment )
      SysConvertEnvironmentString( pchDirectorySpec, lMaxLth, szWork );
   else
      strcpy_s( pchDirectorySpec, lMaxLth, szWork );

   ofnTZCMWKSO_AppendSlash( pchDirectorySpec );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
zSHORT
fnBreakDownZKey( zULONG  ulZKey,
                 zPLONG  plWKS_Id,
                 zPLONG  plMaxZKey )
{
   *plWKS_Id = ulZKey / 1000000;
   while ( ulZKey > 999999999 )
      ulZKey -= 1000000000;

   while ( ulZKey > 99999999 )
      ulZKey -= 100000000;

   while ( ulZKey > 9999999 )
      ulZKey -= 10000000;

   while ( ulZKey > 999999 )
      ulZKey -= 1000000;

   *plMaxZKey = ulZKey;
   return( 0 );
}

//./ ADD NAME=InitializeLPLR
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: InitializeLPLR
//
//  PURPOSE:    Called at the start of all Zeidon Tools. This will load
//              the WorkStation and LPLR objects.  The WorkStation object
//              must exist.
//              If the LPLR Name is NULL, then the current Default LPLR is
//              used.
//              Temporarily, the LPLR will be rebuilt from the \BIN\SYS
//              directories, if not found. The LPLR file is TZCMLPLR.XLP.
//
//  PARAMETERS: vSubtask - A valid Subtask view
//              LPLR_Name - The LPLR Name or NULL for Default
//
//  RETURNS:    1 - LPL initialized successfully
//             -1 - Error encountered during LPL initialization
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zOPER_EXPORT zSHORT OPERATION
InitializeLPLR( zVIEW  vSubtask,
                zPCHAR pchLPLR_NameIn )
{
   zLONG  lTaskUseCnt;
   zVIEW  vZeidonCM;
   zVIEW  vActiveMetas;
   zVIEW  vLPLR;
   zVIEW  WKS_View;
   zVIEW  vTaskMetas;
   zULONG ulZKey;
   HFILE  hFile;
   zCHAR  szLPLR_Name[ 80 ];
   zCHAR  szLPLR_FileName[ 33 ];
   zCHAR  szLPLR_Spec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szErrMsg[ zLONG_MESSAGE_LTH + 1 ]; // includes szLPLR_Spec
   LPTASK lpTask;
   zSHORT nRC;

   //TraceLineS("*** InitializeLPLR *** ", "");

   // Check to make sure that the Workstation Administration tool is not up.
   lpTask = 0;
   while ( (lpTask = SfGetNextTask( lpTask )) != 0 )
   {
      zCHAR szDialogName[ 200 ];

      // Retrieve name of the task.
      SfGetTaskInfo( szDialogName, zsizeof( szDialogName ), zTASK_DIALOG, lpTask );

      // We don't allow the Workstation Admin tool, TZCMLPLD, to be running,
      // unless it is the current task.
      if ( zstrcmpi( szDialogName, "TZCMLPLD" ) == 0 && lpTask != SfGetCurrentTask( vSubtask ) )
      {
         MessageSend( vSubtask, "CM00299", "Configuration Management",
                      "Regular tools are not allowed to run while "
                        "Workstation Administration is running.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_ExitDialogTask, 0, 0 );
         return( -1 );
      }
   }

   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
   if ( vZeidonCM == 0 )
   {
      if ( SfCreateSystemSubtask( &vZeidonCM, vSubtask, "Zeidon_Tools" ) == 0 )
      {
         SetNameForView( vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
      }

      SetViewFlags( vZeidonCM, zVF_MESSAGEONDROP );
   }

   // Create a work LPLR entity to keep track of ActiveMetas.
   GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK );
   if ( vActiveMetas == 0 )
   {
      ActivateEmptyObjectInstance( &vActiveMetas, "TZCMLPLO", vZeidonCM,
                                   zMULTIPLE | zLEVEL_APPLICATION );
      SetNameForView( vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK );
   }

   fnGetTaskOI_ListName( vSubtask, szLPLR_Name, zsizeof( szLPLR_Name ) );
   GetViewByName( &vTaskMetas, szLPLR_Name, vZeidonCM, zLEVEL_SUBTASK );
   if ( vTaskMetas == 0 )
   {
      if ( SfCreateSystemSubtask( &vTaskMetas, vZeidonCM, 0 ) == 0 )
         SetNameForView( vTaskMetas, szLPLR_Name, vZeidonCM, zLEVEL_SUBTASK );
   }

   GetViewByName( &WKS_View, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );
   if ( WKS_View == 0 )  // view isn't there
   {
      if ( oTZCMWKSO_ActivateWorkStation( &WKS_View, vZeidonCM, zSINGLE | zLEVEL_APPLICATION | zIGNORE_ATTRIB_ERRORS ) != 0 )
      {
         strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Unable to open the RepositoryClient File - " );
         GetStringFromAttribute( szErrMsg + zstrlen( szErrMsg ), zsizeof( szErrMsg ) - zstrlen( szErrMsg ), WKS_View, "LPLR", "Name" );
         MessageSend( vSubtask, "CM00402", "Configuration Management",
                      szErrMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         strcpy_s( szErrMsg, zsizeof( szErrMsg ), "If you are a new user use the LPLR Dialog" );
         strcat_s( szErrMsg, zsizeof( szErrMsg ),
                  "\nto initialize the Repository Client. Otherwise," );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\npossible reasons for your being unable to open" );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\nthe Repository Client are:\n" );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\n1: The Repository Client File exists but" );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\n  cannot be activated." );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\n2: The Repository Client File exists but" );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\n  is not in the directory identified by the" );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\n     ZEIDON environment variable." );
         MessageSend( vSubtask, "CM00403", "Configuration Management",
                      szErrMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }

      SetNameForView( WKS_View, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );
   }

   if ( pchLPLR_NameIn &&
        zstrcmp( pchLPLR_NameIn, "CM New User" ) == 0 )
   {
      return( 0 );
   }
   if ( pchLPLR_NameIn &&
        SetCursorFirstEntityByString( WKS_View, "LPLR", "Name", pchLPLR_NameIn, "" ) == zCURSOR_SET )
   {
      ;  // nothing to do here
   }
   else
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKey, WKS_View, "RepositoryClient", "DefaultLPLR_ZKey" );
      if ( SetCursorFirstEntityByInteger( WKS_View, "LPLR", "ZKey", (zLONG) ulZKey, "" ) != zCURSOR_SET )
      {
         if ( SetCursorFirstEntity( WKS_View, "LPLR", "" ) == zCURSOR_SET )
         {
            SetAttributeFromAttribute( WKS_View, "RepositoryClient", "DefaultLPLR_ZKey", WKS_View, "LPLR", "ZKey" );
            oTZCMWKSO_CommitWorkstation( WKS_View );
         }
         else
         {
            //strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Unable to ActivateDefaultLPL because" );
            //strcat_s( szErrMsg, zsizeof( szErrMsg ), " no LPL Releases defined for Client." );
            //strcat_s( szErrMsg, zsizeof( szErrMsg ), "\nUse LPLR Dialog to define LPLR's" );
            // KJS 03/27/13 - I don't feel that the above message makes much sense to a new
            // zeidon user so I am changing it.
            strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Unable to activate a default project because no projects exist.\n" );
            strcat_s( szErrMsg, zsizeof( szErrMsg ), "Please create a new project." );
            MessageSend( vSubtask, "CM00406", "Configuration Management",
                         szErrMsg,
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }
      }
   }

   GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), WKS_View, "LPLR", "Name" );
   GetStringFromAttribute( szErrMsg, zsizeof( szErrMsg ), WKS_View, "LPLR", "ExecDir" ); // borrow szErrMsg for a sec...
   SysConvertEnvironmentString( szLPLR_Spec, zsizeof( szLPLR_Spec ), szErrMsg );
   ofnTZCMWKSO_AppendSlash( szLPLR_Spec );
   strncpy_s( szLPLR_FileName, zsizeof( szLPLR_FileName ), szLPLR_Name, zsizeof( szLPLR_FileName ) - 1 );
   //TruncateName8( szLPLR_FileName );
   strcat_s( szLPLR_Spec, zsizeof( szLPLR_Spec ), szLPLR_FileName );
   strcat_s( szLPLR_Spec, zsizeof( szLPLR_Spec ), ".XLP" );
   nRC = GetViewByName( &vLPLR, szLPLR_Name, vZeidonCM, zLEVEL_SUBTASK );
   if ( vLPLR == 0 )  // view isn't there
   {
      hFile = (HFILE) SysOpenFile( vSubtask, szLPLR_Spec, COREFILE_READ );
      if ( hFile < 0 )
         nRC = -1;
      else
      {
         SysCloseFile( vSubtask, hFile, 0 );
         nRC = ActivateOI_FromFile( &vLPLR, "TZCMLPLO", vZeidonCM, szLPLR_Spec, zSINGLE | zLEVEL_APPLICATION | zIGNORE_ERRORS );

         // Make sure Operation lists are alphabetized.
         SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", 2002, "" );
         OrderEntityForView( vLPLR, "W_MetaDef", "Name A" );
         SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", 2, "" );
         OrderEntityForView( vLPLR, "W_MetaDef", "Name A" );

         // *** TEMPORARY CODE ***
         // The following code is temporary and makes sure there is a Report
         // W_MetaType in the LPLR.  It was created 9/3/96 and only needs to
         // exist until Report is added as an official meta.
         if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", zSOURCE_REPORT_META, 0 ) < zCURSOR_SET )
         {
            SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", 14, 0 );
            CreateEntity( vLPLR, "W_MetaType", zPOS_AFTER );
            SetAttributeFromInteger( vLPLR, "W_MetaType", "Type", zSOURCE_REPORT_META );
         }

         if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", zREFER_REPORT_META, 0 ) < zCURSOR_SET )
         {
            SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", 2014, 0 );
            CreateEntity( vLPLR, "W_MetaType", zPOS_AFTER );
            SetAttributeFromInteger( vLPLR, "W_MetaType", "Type", zREFER_REPORT_META );
         }

         // *** TEMPORARY CODE ***
         // The following code is temporary and makes sure there is an XSLT
         // W_MetaType in the LPLR.  It was created 2012.06.14 and only needs to
         // exist until XSLT is added as an official meta.
         if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", zSOURCE_XSLT_META, 0 ) < zCURSOR_SET )
         {
            SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", 14, 0 );
            CreateEntity( vLPLR, "W_MetaType", zPOS_AFTER );
            SetAttributeFromInteger( vLPLR, "W_MetaType", "Type", zSOURCE_XSLT_META );
         }

         if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", zREFER_XSLT_META, 0 ) < zCURSOR_SET )
         {
            SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", 2014, 0 );
            CreateEntity( vLPLR, "W_MetaType", zPOS_AFTER );
            SetAttributeFromInteger( vLPLR, "W_MetaType", "Type", zREFER_XSLT_META );
         }
      }

      if ( nRC == 0 )
         SetNameForView( vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
      else
      {
         strcpy_s( szErrMsg, zsizeof( szErrMsg ), "The default Project File " );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), szLPLR_Spec );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\nwas not found! Please check the Project Information." );
         MessageSend( vSubtask, "CM00406", "Configuration Management",
                      szErrMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }

      SetAttributeFromInteger( vLPLR, "LPLR", "TaskUseCount", 0 );
      SetNameForView( vLPLR, szLPLR_Name, vZeidonCM, zLEVEL_SUBTASK );

      // Create a work LPLR entity to keep track of ActiveMetas.
      if ( CheckExistenceOfEntity( vActiveMetas, "LPLR" ) != zCURSOR_SET )
      {
         CreateEntity( vActiveMetas, "LPLR", zPOS_AFTER );
         SetAttributeFromAttribute( vActiveMetas, "LPLR", "Name", WKS_View, "LPLR", "Name" );
      }
      else
      {
         if ( SetCursorFirstEntityByString( vActiveMetas, "LPLR", "Name", szLPLR_Name, 0 ) != zCURSOR_SET )
         {
            CreateEntity( vActiveMetas, "LPLR", zPOS_AFTER );
            SetAttributeFromAttribute( vActiveMetas, "LPLR", "Name", WKS_View, "LPLR", "Name" );
         }
         else
         {
            fnCleanupActiveMetas( vActiveMetas, vZeidonCM );
         }
      }
   }
   else
   {
      if ( SetCursorFirstEntityByString( vActiveMetas, "LPLR", "Name", szLPLR_Name, 0 ) >= zCURSOR_SET )
      {
         nRC = fnCleanupActiveMetas( vActiveMetas, vZeidonCM );
      }

      SetNameForView( vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   }

   GetIntegerFromAttribute( &lTaskUseCnt, vLPLR, "LPLR", "TaskUseCount" );
   lTaskUseCnt++;
   SetAttributeFromInteger( vLPLR, "LPLR", "TaskUseCount", lTaskUseCnt );

   return( 1 );
}

//./ ADD NAME=InitializeDefaultLPL
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: InitializeDefaultLPL
//
//  PURPOSE:    Calls InitializeLPLR with NULL LPLR Name.  This just for
//              compatibility with old Code!!!!!!!!!!!!!!!!!!!!
//
//  PARAMETERS: vSubtask - A valid  Subtask view
//
//  RETURNS:    1 - LPL initialized successfully
//             -1 - Error encountered during LPL initialization
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
InitializeDefaultLPL( zVIEW vSubtask )
{
   return( InitializeLPLR( vSubtask, "" ) );
}

//./ ADD NAME=TerminateLPLR
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: TerminateLPLR
//
//  PURPOSE:    Called at the end of all Zeidon Tools. This will drop
//              the TaskLPLR view and if it the only remaining one it
//              drop the LPLR Object Instance.
//
//  PARAMETERS: vSubtask - A valid  Subtask view
//
//  RETURNS:    1 - LPLR terminated successfully
//             -1 - Error encountered during LPLR termination
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
TerminateLPLR( zVIEW vSubtask )
{
   zVIEW  WorkView;
   zVIEW  vLPLR;
   zVIEW  vZeidonCM;
   zVIEW  vTaskOI;
   zVIEW  vTaskMetas;
   zVIEW  vActiveMetas;
   zCHAR  szViewName[ 80 ];
   zLONG  lTaskID;
   zLONG  lTaskUseCnt;
   zSHORT nRC;

   nRC = GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   if ( vLPLR == 0 )  // View isn't there
   {
      TraceLineS( "(tzcmoprs) TerminateLPLR: ", "Unable to drop the Project!" );
      return( -1 );
   }

   // Clean up the CM views for the Task activated Metas.
   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
   if ( vZeidonCM == 0 )
   {
      MessageSend( vSubtask, "CM00410", "Configuration Management",
                   "Unable to locate ZeidonCM view!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK );
   GetStringFromAttribute( szViewName, zsizeof( szViewName ), vLPLR, "LPLR", "Name" );
   if ( SetCursorFirstEntityByString( vActiveMetas, "LPLR", "Name", szViewName, "" ) < zCURSOR_SET )
   {
      zCHAR  szMsg[ 512 ];

      // It is possible that this problem occurs because the ZKey in TZCMWKS8.POR for the specified LPLR does not match
      // the ZKey in the .XLP for the LPLR.  If that's the case, fix the ZKey in TZCMWKS8.POR!
      strcpy_s( szMsg, zsizeof( szMsg ), "Unable to locate Project in CM ACTIVE view: " );
      strcat_s( szMsg, zsizeof( szMsg ), szViewName );
      MessageSend( vSubtask, "CM00411", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   lTaskID = SysGetTaskFromView( vSubtask );
   nRC = SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaDef", "TaskID", lTaskID, "LPLR" );
   while ( (nRC == zCURSOR_SET) || (nRC == zCURSOR_SET_NEWPARENT) )
   {
      GetStringFromAttribute( szViewName, zsizeof( szViewName ), vActiveMetas,
                              "W_MetaDef", "CM_ViewName" );
      strcat_s( szViewName, zsizeof( szViewName ), ".u" );
      GetViewByName( &WorkView, szViewName, vZeidonCM, zLEVEL_SUBTASK );
      if ( WorkView )
         DropObjectInstance( WorkView );

      strcpy_s( szViewName + zstrlen( szViewName ) - 2, zsizeof( szViewName ) - zstrlen( szViewName ) + 2, ".r" );
      if ( GetViewByName( &WorkView, szViewName, vZeidonCM, zLEVEL_SUBTASK ) > 0 )
      {
         SetAttributeFromString( vActiveMetas, "W_MetaDef", "TaskID", "" );
      }
      else
      {
         ExcludeEntity( vActiveMetas, "W_MetaDef", zREPOS_NONE );
      }

      nRC = SetCursorNextEntityByInteger( vActiveMetas, "W_MetaDef", "TaskID", lTaskID, "LPLR" );
   }

   fnGetTaskOI_ListName( vSubtask, szViewName, zsizeof( szViewName ) );
   GetViewByName( &vTaskMetas, szViewName, vZeidonCM, zLEVEL_SUBTASK );
   if ( vTaskMetas )
   {
      nRC = SfGetFirstNamedView( &vTaskOI, szViewName, vTaskMetas, zLEVEL_SUBTASK );
      while( nRC > 0 )
      {
         DropView( vTaskOI );
         nRC = SfGetFirstNamedView( &vTaskOI, szViewName, vTaskMetas, zLEVEL_SUBTASK );
      }

      nRC = SfDropSubtask( vTaskMetas, 0 );
   }

   GetIntegerFromAttribute( &lTaskUseCnt, vLPLR, "LPLR", "TaskUseCount" );
   if ( lTaskUseCnt > 0 )
      lTaskUseCnt--;

   if ( lTaskUseCnt < 1 )
   {
   // DropObjectInstance( vLPLR );
      SetAttributeFromInteger( vLPLR, "LPLR", "TaskUseCount", lTaskUseCnt );
      nRC = SetCursorFirstEntity( vActiveMetas, "W_MetaDef", "LPLR" );
      while ( nRC == zCURSOR_SET )
      {
         GetStringFromAttribute( szViewName, zsizeof( szViewName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
         strcat_s( szViewName, zsizeof( szViewName ), ".u" );
         if ( GetViewByName( &WorkView, szViewName, vZeidonCM, zLEVEL_SUBTASK ) > 0 )
         {
            DropObjectInstance( WorkView );
            nRC = ExcludeEntity( vActiveMetas, "W_MetaDef", zREPOS_NEXT );
         }
         else
            nRC = SetCursorNextEntity( vActiveMetas, "W_MetaDef", "LPLR" );
      }

//    DeleteEntity( vActiveMetas, "LPLR", zREPOS_NONE );
/* PETTIT  Test bug of deleting a root of a multi-root OI
      nRC = SetCursorFirstEntity( vActiveMetas, "W_MetaType", "" );
      while ( nRC == zCURSOR_SET )
      {
         DeleteEntity( vActiveMetas, "W_MetaType", zREPOS_NONE );
         nRC = SetCursorNextEntity( vActiveMetas, "W_MetaType", "" );
      }
*/
   }
   else
   {
      nRC = SetAttributeFromInteger( vLPLR, "LPLR", "TaskUseCount", lTaskUseCnt );
   }

   if ( ObjectInstanceUpdatedFromFile( vLPLR ) == 1 )
       oTZCMLPLO_CommitLPLR( vLPLR );

   return( 1 );
}

//./ ADD NAME=RetrieveViewForMetaList
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: RetrieveViewForMetaList
//
//  PURPOSE:    Called to return the View of a subobject of the current LPL.
//              The View can then be used to list all metas of a particular
//              type (such as dialogs, LOD's, Model's, etc.)  When the View
//              is returned it is the developers responsibility to provide
//              a name for the view.
//
//  PARAMETERS: lpListView - a pointer to a View to be returned
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//
//  RETURNS:    1 - View retrieved successfully
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zOPER_EXPORT zSHORT OPERATION
RetrieveViewForMetaList( zVIEW  vSubtask,
                         zPVIEW lpListView,
                         zSHORT nType )
{
   zSHORT nEntityType;
   zVIEW  vLPLR;
   zVIEW  vZeidonCM;
   zVIEW  vTaskMetas;
   zCHAR  szName[ 80 ];
   zSHORT nRC = 0;

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   if ( vLPLR )  // View is there
   {
      if ( GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION ) < 0 )
      {
         MessageSend( vSubtask, "CM00412", "Configuration Management",
                      "Unable to locate ZeidonCM view!",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }

      fnGetTaskOI_ListName( vSubtask, szName, zsizeof( szName ) ); // __CM.800013b8
      GetViewByName( &vTaskMetas, szName, vZeidonCM, zLEVEL_SUBTASK );
      if ( vTaskMetas == 0 )
      {
         MessageSend( vZeidonCM, "CM00471", "TZCMOPRS ERROR",
                      "System Error: vTaskMetas view not found",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }

      if ( CreateViewFromViewForTask( lpListView, vLPLR, vSubtask ) == 0 )
      {
         if ( SetCursorFirstEntityByInteger( *lpListView, "W_MetaType", "Type", nType, "" ) != zCURSOR_SET )
         {
            nRC = CreateEntity( *lpListView, "W_MetaType", zPOS_AFTER );
            SetAttributeFromInteger( *lpListView, "W_MetaType", "Type", nType );
         }

         SetViewToSubobject( *lpListView, "W_MetaType" );
         szName[ 0 ] = 'l';
         zltoa( *((zPLONG) lpListView), szName + 1, zsizeof( szName ) - 1 );
         SetNameForView( *lpListView, szName, vTaskMetas, zLEVEL_SUBTASK | zNAME_AUTODROP );
         return( 1 );
      }
   }
   else
   if ( *lpListView )
   {
      MessageSend( *lpListView, "CM00413", "Configuration Management",
                   "Unable to locate TaskLPLR view!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
   }

   return( -1 );
}

//./ ADD NAME=fnActivateMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: fnActivateMetaOI
//
//  PURPOSE:    Activates an Object Instance from a MetaList retrieved
//              via RetrieveViewForMetaList, by declaring a view and then
//              loading the OI from a portable file.
//
//              When activating a meta that is part of a group (e.g. domains)
//              we activate the group and then position the cursor in the
//              group to point to the meta requested.
//
//  PARAMETERS: pvMOI - a pointer to a View to be returned
//              ListView - a valid LPL list view
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//              lControl - NOT USED.  zLEVEL_APPLICATION is always used
//                         for control so the memory is for the OI is
//                         kept at the application task.
//
//  RETURNS:    1 - Meta OI successfully activated
//             -1 - Error encountered
///
/////////////////////////////////////////////////////////////////////////////
//./ END + 6
zOPER_EXPORT zSHORT OPERATION
fnActivateMetaOI( zVIEW   vSubtask,
                  zPVIEW  pvMOI,
                  zVIEW   vListView,
                  zSHORT  nType,
                  zLONG   lControl )
{
   zVIEW  vZeidonCM;
   zVIEW  vActiveMetas;
   zVIEW  vTaskMetas;
// zVIEW  vApplication;
   zVIEW  vTaskLPLR;
   zVIEW  CM_View;
   zVIEW  vWkListView;
// zVIEW  vTZCMULWO;
// zVIEW  vTZCMWKSO;
   zBOOL  bCopyOI = FALSE;
   zSHORT nEntityType;
   zSHORT nOrigType;
   zSHORT nActiveType, nPhaseCtl;
   zBOOL  bReactivate;
   zLONG  lStatus, lTaskID, lCurrentTaskID;
   zLONG  lMetaOI_ZKey;
// zLONG  lPrefix;
// zLONG  lLastPrefix;
   zULONG ulOrigMetaOI_ZKey = 0;
   zCHAR  szMetaOI_Name[ 33 ];
   zCHAR  szMetaOI_Def[ 33 ];
   zCHAR  szTempSpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szFileSpec[ zMAX_FILESPEC_LTH + 1 ];
// zCHAR  szFileName[ 255 ];
   zCHAR  szCM_ViewName[ 80 ];
   zCHAR  szLPLR_Name[ 80 ];
// zCHAR  szUserName[ 80 ];
   zCHAR  szSyncDate[ 20 ];
   zCHAR  szGroupName[ 80 ];
   zSHORT nRC = 0;

   // Check to make sure that type is OK.
   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   if ( CheckExistenceOfEntity( vListView, "W_MetaDef" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00414", "Configuration Management",
                   "NULL Meta Def passed to ActivateMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -16 );
   }

   if ( CompareAttributeToInteger( vListView, "W_MetaDef", "UpdateInd", 3 ) == 0 )
   {
      MessageSend( vSubtask, "CM00415", "Configuration Management",
                   "Deleted Meta Def passed to ActivateMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -16 );
   }

   // I need the view to the TaskLPLR to get the name of the root LPLR in the ActiveMeta OI.
   // It is also needed to properly qualify the task for vWkListView.
   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vTaskLPLR, "LPLR", "Name" ); // e.g. Zeidon

   // The following code changes the Type for Domain and Global Operation
   // Activates into Domain Group and Global Operation Group Activates.
   // A new LPLR view, vWkListView, is used because the Domain and Global
   // Operation processing alters the position on the W_MetaType and we
   // want to leave the ListView position unaltered.
   CreateViewFromViewForTask( &vWkListView, vListView, vTaskLPLR );
   SetNameForView( vWkListView, "WkListView", vSubtask, zLEVEL_TASK );
   if ( 0 )
   {
      MessageSend( vSubtask, "CM00418", "Configuration Management",
                   "Check WkListView for Operations",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
   }

   nOrigType = nType;                 // keep track of the original type

   if ( nType == zSOURCE_DOMAIN_META || nType == zREFER_DOMAIN_META )
   {
      // Save Domain ZKey for later positioning.
      GetIntegerFromAttribute( (zPLONG) &ulOrigMetaOI_ZKey, vWkListView, "W_MetaDef", "CPLR_ZKey" );

      if ( nType == zSOURCE_DOMAIN_META )
         nType = zSOURCE_DOMAINGRP_META;
      else
         nType = zREFER_DOMAINGRP_META;

      // Reposition on the correct group type.
      SetCursorFirstEntityByInteger( vWkListView, "W_MetaType", "Type", zREFER_DOMAINGRP_META, "" );

      // Then position on the correct Domain within the group type.
   // SetCursorFirstEntityByAttr( vWkListView, "W_MetaDef", "Name", vListView, "W_MetaDef", "GroupName", "" );
      GetStringFromAttribute( szGroupName, zsizeof( szGroupName ), vListView, "W_MetaDef", "GroupName" );
      SetCursorFirstEntityByString( vWkListView, "W_MetaDef", "Name", szGroupName, "" );
   }

   if ( nType == zSOURCE_GO_META || nType == zREFER_GO_META )
   {
      // Save Global Operation ZKey for later positioning.
      GetIntegerFromAttribute( (zPLONG) &ulOrigMetaOI_ZKey, vWkListView, "W_MetaDef", "CPLR_ZKey" );

      if ( nType == zSOURCE_GO_META )
         nType = zSOURCE_GOPGRP_META;
      else
         nType = zREFER_GOPGRP_META;

      // Reposition on the correct group type.
      SetCursorFirstEntityByInteger( vWkListView, "W_MetaType", "Type", zREFER_GOPGRP_META, "" );

      // Then position on the correct Operation within the group type.
   // SetCursorFirstEntityByAttr( vWkListView, "W_MetaDef", "Name", vListView, "W_MetaDef", "GroupName", "" );
      GetStringFromAttribute( szGroupName, zsizeof( szGroupName ), vListView, "W_MetaDef", "GroupName" );
      SetCursorFirstEntityByString( vWkListView, "W_MetaDef", "Name", szGroupName, "" );
   }

   // PETTIT The following if else is necessary until CM handles the Open,
   // New, etc. Menu items.

#if 0
   DonC comment on 4/21/1996:  I am eliminating the following code for now
   because our current position is that a user can modify a meta that is
   not checked out but cannot save it.  However, I am leaving the following
   code in case we change our mind.

   // If the user requested a Source meta, check the status of the MetaDef.
   // If the status is not 1 (e.g. it is not active), then the user can only
   // reference the meta, so change the meta to a Refer meta.
   if ( nType <= zSOURCE_MAX_META )
   {
      if ( CompareAttributeToInteger( vWkListView, "W_MetaDef","Status", 1 ) != 0 )
      {
         nEntityType = CM_REFER_TYPE;
         nType = nType + 2000;  // Change SOURCE to REFER.
      }
   }
#endif

   if ( nEntityType == CM_ACTIVE_TYPE )
      nActiveType = nType;
   else
      nActiveType = nType - 2000;

   // Get the view to ZedionCM OI.
   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );

   // Get the view to the vTaskMetas subtask.
   fnGetTaskOI_ListName( vSubtask, szMetaOI_Name, zsizeof( szMetaOI_Name ) );
   GetViewByName( &vTaskMetas, szMetaOI_Name, vZeidonCM, zLEVEL_SUBTASK );

   // Get the view to the ActiveMeta OI.
   GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK );

   SetCursorFirstEntityByAttr( vActiveMetas, "LPLR", "Name", vTaskLPLR, "LPLR", "Name", "" );
   bReactivate = TRUE;

   // Check to see if a W_MetaType exists for Type = nActiveType.  If not, then create one.
   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaType", "Type", nActiveType, "" ) != zCURSOR_SET )
   {
      CreateEntity( vActiveMetas, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vActiveMetas, "W_MetaType", "Type", nActiveType );
   }

   // Check in the Active Meta List for a hit on the requested Meta.
   GetIntegerFromAttribute( &lMetaOI_ZKey, vWkListView, "W_MetaDef", "CPLR_ZKey" );
   nRC = SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaDef", "CPLR_ZKey", lMetaOI_ZKey, "" );
   if ( nRC == zCURSOR_SET )
   {
      // It is in the Active List, now check if it's really still active.
      GetStringFromAttribute( szCM_ViewName, zsizeof( szCM_ViewName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
      GetIntegerFromAttribute( &lTaskID, vActiveMetas, "W_MetaDef", "TaskID" );
      if ( nEntityType == CM_REFER_TYPE )
      {
         strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".r" );
         if ( GetViewByName( &CM_View, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK ) < 1 )
         {
            // It's in vActiveMetas but it's not loaded for REFER.
#if 0
      Removed by DonC on Aug 11, 1998.
            if ( TaskID <= 0 )
            {
               // If it's not loaded for update Exclude it
               ExcludeEntity( vActiveMetas, "W_MetaDef", zREPOS_NONE );
               nRC = zCURSOR_UNCHANGED;  // set nRC so meta gets reloaded
            }
#endif
         }
         else
         {
            // It's there so set the flag so it's not reactivated.
            bReactivate = FALSE;
         }
      } // if ( nEntityType == CM_REFER_TYPE )...
      else
      {
         // Requesting an Update View.
         strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".u" );
         if ( GetViewByName( &CM_View, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK ) < 1 )
         {
            // It's in vActiveMetas but it's not loaded for UPDATE.

            // Change last zCHAR in view name from "u" to "r" and try to get THAT view.
            szCM_ViewName[ zstrlen( szCM_ViewName ) - 1 ] = 'r';
            if ( GetViewByName( &CM_View, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK ) < 1 )
            {
               // It's in vActiveMetas but it's not loaded for REFER either.
               ExcludeEntity( vActiveMetas, "W_MetaDef", zREPOS_NONE );
               nRC = zCURSOR_UNCHANGED;  // set nRC so meta gets reloaded
            }
            else
            {
               // It's loaded for REFER.
               if ( lTaskID )  // any non-zero task id is valid (Win9x has negative IDs)
               {
                  // Update View might have gotten blown away.
                  SetAttributeFromInteger( vActiveMetas, "W_MetaDef", "TaskID", 0 );
               }

               bCopyOI = TRUE;
            }
         }
         else
         {
            // ERROR situation...
            // It's already loaded for update by somebody else.
            if ( lTaskID ) // added back 5.10.98 **HH**
            {
            // if ( lTaskID == SysGetTaskFromView( vListView ) )
               if ( lTaskID == SysGetTaskFromView( vSubtask ) )
               {
                  if ( ObjectInstanceUpdatedFromFile( CM_View ) == 0 )
                     bCopyOI = TRUE;
               }
               else
               {
                  MessageSend( vSubtask, "CM00416", "Configuration Management",
                               "The Meta requested for update is already\n"
                                 "opened for update by another task\n"
                                 "Unable to open!",
                               zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
                  {
                     return( -1 );
                  }
               }
            }
         }
      } // if ( nEntityType == CM_REFER_TYPE )...else...

   } // if ( nRC == zCURSOR_SET )...

   GetIntegerFromAttribute( &lStatus, vWkListView, "W_MetaDef", "Status" );
   if ( nRC != zCURSOR_SET ) // not in the Active List
   {
      IncludeSubobjectFromSubobject( vActiveMetas, "W_MetaDef", vWkListView, "W_MetaDef", zPOS_AFTER );
      if ( (nEntityType == CM_ACTIVE_TYPE) && (lStatus == 1) )
      {
      // lCurrentTaskID = SysGetTaskFromView( vListView );
         lCurrentTaskID = SysGetTaskFromView( vSubtask );
         SetAttributeFromInteger( vActiveMetas, "W_MetaDef", "TaskID", lCurrentTaskID );
      }

      if ( nEntityType == CM_REFER_TYPE )
      {
         // The view may still be hanging around if Zeidon was still open.
         GetStringFromAttribute( szCM_ViewName, zsizeof( szCM_ViewName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
         strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".r" );
         if ( GetViewByName( &CM_View, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK ) > 0 )
         {
            // It's loaded for REFER so set the flag so it's not reactivated.
            bReactivate = FALSE;
         }
      }
   }

   // If we don't have to reactivate the object, then create a view and return.
   if ( bReactivate == FALSE ) // REFER is already activated
   {
      CreateViewFromViewForTask( pvMOI, CM_View, vSubtask );
      ResetView( *pvMOI );

      szCM_ViewName[ 0 ] = 'r';
      zltoa( *((zPLONG) pvMOI), szCM_ViewName + 1, zsizeof( szCM_ViewName ) - 1 );
      SetNameForView( *pvMOI, szCM_ViewName, vTaskMetas, zLEVEL_SUBTASK | zNAME_AUTODROP );

#if 0
      // We no longer set refer views as read-only.  Instead, we check in
      // fnCommitObjectInstance and don't allow commits for REFER views.
      SetViewReadOnly( *pvMOI );
#endif

      // If we are activating a Domain, we must position on the correct Domain within the Domain Group.
      if ( nOrigType == zSOURCE_DOMAIN_META || nOrigType == zREFER_DOMAIN_META )
      {
         if ( SetCursorFirstEntityByInteger( *pvMOI, "Domain", "ZKey", ulOrigMetaOI_ZKey, "" ) != zCURSOR_SET )
         {
            SetNameForView( *pvMOI, "__MOI_Error", 0, zLEVEL_SUBTASK );
            TraceLine( "fnActivateMetaOI cannot find Domain (%d) in DomainGroup ... View: 0x%08x (%s or %s)",
                       ulOrigMetaOI_ZKey, *pvMOI, "__MOI_Error", szCM_ViewName );
            DisplayObjectInstance( *pvMOI, "", "" );
            MessageSend( vSubtask, "CM00417", "Configuration Management",
                         "Couldn't find Domain in DomainGroup",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

            return( -1 );
         }
      }

      // If we are activating a Global Operation, we must position on the correct Operation within the Global Operation Group.
      if ( nOrigType == zSOURCE_GO_META || nOrigType == zREFER_GO_META )
      {
         if ( SetCursorFirstEntityByInteger( *pvMOI, "Operation", "ZKey", ulOrigMetaOI_ZKey, "" ) != zCURSOR_SET )
         {
            SetNameForView( *pvMOI, "__MetaGroup_Error", vSubtask, zLEVEL_TASK );
            TraceLine( "Couldn't find \"Operation\" (__MetaGroup_Error view: %s) in Global Op Group by ZKey: %d",
                       szCM_ViewName, ulOrigMetaOI_ZKey );
            DisplayObjectInstance( *pvMOI, "", "" );
            MessageSend( vSubtask, "CM00418", "Configuration Management",
                         "Couldn't find Global Op in Global Op Group",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }
      }

      DropView( vWkListView );
      return( 1 );
   }

   if ( (nEntityType == CM_ACTIVE_TYPE) && (lStatus == 1) )
   {
   // lCurrentTaskID = SysGetTaskFromView( vListView );
      lCurrentTaskID = SysGetTaskFromView( vSubtask );
      SetAttributeFromInteger( vActiveMetas, "W_MetaDef", "TaskID", lCurrentTaskID );
   }

   // If bCopyOI is true, then the meta already exists for REFER, but we need to activate it for SOURCE (i.e. update).
   // All we need to do is create a new OI from the REFER OI.
   if ( bCopyOI )
   {
      if ( ActivateOI_FromOI_ForTask( pvMOI, CM_View, 0, zLEVEL_APPLICATION ) != 0 )
      {
         MessageSend( vSubtask, "CM00419", "Configuration Management",
                      "Error activating OI from OI",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }
   }
   else
   {
      ///////////////////////////////////////////////////////////////////////
      // The Meta needs to be loaded from a file.  We need to know the
      // following:
      //
      // o  The name of the LOD for the meta.
      // o  The name of the portable file that contains the OI.
      //
      // Knowing these, we can then activate the OI from the file.
      //
      ///////////////////////////////////////////////////////////////////////

      // Retrieve the name of the LOD for meta type we are activating.  Note
      // that the LOD name may be changed in the following 'switch' code.
      if ( nEntityType == CM_ACTIVE_TYPE )
         strcpy_s( szMetaOI_Def, zsizeof( szMetaOI_Def ), SRC_CMOD[ nType ].szOD );
      else
         strcpy_s( szMetaOI_Def, zsizeof( szMetaOI_Def ), REFER_CMOD[ nType - 2000 ].szOD );

      // Find the name of the portable file containing the OI.
      switch ( nActiveType )
      {
         case zSOURCE_VOR_META:
            GetIntegerFromAttribute( &lMetaOI_ZKey, vWkListView, "W_MetaDef", "CPLR_ZKey" );
            zltoxa( lMetaOI_ZKey, szMetaOI_Name );
            break;

         default:
            GetStringFromAttribute( szMetaOI_Name, zsizeof( szMetaOI_Name ), vWkListView, "W_MetaDef", "Name" );
            //TruncateName8( szMetaOI_Name );
            break;

      } // switch ( nActiveType )...

      //BL, 2000.01.13 Load PPE from LPLR, not from system directory
      //               if PPE does not exist in LPLR, then we call the
      //               Function ActivateOI_FromFile, not ActivateMetaOI
      fnGetDirectorySpec( vSubtask, szTempSpec, zsizeof( szTempSpec ), nType, FALSE ); // for CompilerSpec, needed to use vSubtask
#if 0
      // We will get PEs from the system directory and others from the LPLR.
      if ( nActiveType == zSOURCE_PENV_META )
         zgGetZeidonToolsDir( vSubtask, szTempSpec, zAPPL_DIR_OBJECT );
      else
         fnGetDirectorySpec( szTempSpec, zsizeof( szTempSpec ), nType, TRUE );
#endif
      SysConvertEnvironmentString( szFileSpec, zsizeof( szFileSpec ), szTempSpec );
      strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_Name );
      if ( nEntityType == CM_ACTIVE_TYPE )
         strcat_s( szFileSpec, zsizeof( szFileSpec ), SRC_CMOD[ nType ].szOD_EXT );
      else
         strcat_s( szFileSpec, zsizeof( szFileSpec ), REFER_CMOD[ nType - 2000 ].szOD_EXT );

      // DGC 10/4/95  Added zIGNORE_ERRORS to ignore activation errors (we
      // wanted to ignore a known error). This should be removed at some point.
      // Finally, activate the OI from the portable file.
   // SfCreateSubtask( &vApplication, vSubtask, szLPLR_Name );  // LPLR "Zeidon"
      nRC = ActivateOI_FromFile( pvMOI, szMetaOI_Def, vWkListView, // vApplication,
                                 szFileSpec, zIGNORE_ERRORS | zLEVEL_APPLICATION );
   // SfDropSubtask( vApplication, 0 );
      if ( nRC )
      {
         zCHAR szMsg[ zLONG_MESSAGE_LTH + 1 ];

         sprintf_s( szMsg, zsizeof( szMsg ), "Error activating OI from file: %s", szFileSpec );
         MessageSend( vSubtask, "CM00420", "Configuration Management",
                      szMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }
   }

   // Recreate the view name either for read-only or update.  nPhaseCtl is used
   // by the PostActivate code--it indicates whether we are activating the meta
   // for read-only or update.
   GetStringFromAttribute( szCM_ViewName, zsizeof( szCM_ViewName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
   if ( nEntityType == CM_REFER_TYPE )
   {
      nPhaseCtl = 1;
      strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".r" );
   }
   else
   {
      nPhaseCtl = 0;
      strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".u" );
   }

   // Name the new view.  The view is for the Zeidon system.
   SetNameForView( *pvMOI, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK );

   // The current view pvMOI will be used for internal CM use.  We need to
   // create a new view to be passed back to the application that requested
   // the meta.
   CreateViewFromViewForTask( pvMOI, *pvMOI, vSubtask );

   // **** Temporary Hack  05.12.1997
   // If this is a LOD, we are going to make sure that all IndentName values
   // are actually indented, since there has been a bug that removes the
   // indentation.  We will also make sure the Indented name is not blank.
   if ( nOrigType == zSOURCE_LOD_META || nOrigType == zREFER_LOD_META )
   {
      zVIEW  vTempLOD;
      zLONG  lLevel;
      zCHAR  szName[ 33 ];
      zCHAR  szIndentName[ 256 ];
      zSHORT k;

      CreateViewFromViewForTask( &vTempLOD, *pvMOI, 0 );
      for ( nRC = SetCursorFirstEntity( vTempLOD, "LOD_Entity", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vTempLOD, "LOD_Entity", 0 ) )
      {
         GetIntegerFromAttribute( &lLevel, vTempLOD, "LOD_Entity", "IndentLvl" );
         GetStringFromAttribute( szIndentName, zsizeof( szIndentName ), vTempLOD, "LOD_Entity", "IndentName" );
         if ( (lLevel > 0 && szIndentName[ 0 ] != ' ') || (szIndentName[ 0 ] == 0) )
         {
            // There is an indentation level but the IndentName is not
            // indented.  Thus we will indent it.
            // Put x blank chars at beginning of indent name, where x is IndentLvl.
            // Then concat the regular names after the blanks.
            // Don't put more than 21 blanks in name.
            for ( k = 0;
                  k < lLevel && k < 21;
                  k++ )
            {
               szIndentName[ k ] = ' ';
            }

            szIndentName[ k ] = 0;

            GetStringFromAttribute( szName, zsizeof( szName ), vTempLOD, "LOD_Entity", "Name" );
            strcat_s( szIndentName, zsizeof( szIndentName ), szName );
            SetAttributeFromString( vTempLOD, "LOD_Entity", "IndentName", szIndentName );
         }
      }

      DropView( vTempLOD );
   }

   // Now that the object instance has been activated, call the logical object operation for the object type to ensure all
   // appropriate object linking is done.  Use a different view to ensure that the cursors don't get moved in listview.
   szSyncDate[ 0 ] = 0;
   cfPostActivate( vSubtask, nType, szSyncDate, vZeidonCM, *pvMOI, vWkListView, nPhaseCtl, 0 );

   // DGC 8/17/95
   // I don't think the following command is necessary, so I'm going to take it out.
// ResetView( *pvMOI );

   // If we are activating a Domain, we must position on the correct Domain within the Domain Group.
   if ( nOrigType == zSOURCE_DOMAIN_META || nOrigType == zREFER_DOMAIN_META )
   {
      if ( SetCursorFirstEntityByInteger( *pvMOI, "Domain", "ZKey", ulOrigMetaOI_ZKey, "" ) != zCURSOR_SET )
      {
         SetNameForView( *pvMOI, "__MOI_Error", vSubtask, zLEVEL_SUBTASK );
         TraceLine( "fnActivateMetaOI2 cannot find Domain (%d) in DomainGroup ... View: 0x%08x (%s)",
                    ulOrigMetaOI_ZKey, *pvMOI, "__MOI_Error" );
         DisplayObjectInstance( *pvMOI, "", "" );
         MessageSend( vSubtask, "CM00417", "Configuration Management",
                      "Couldn't find Domain in DomainGroup",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }
   }

   // If we are activating a Global Operation, we must position on the correct Operation within the Global Operation Group.
   if ( nOrigType == zSOURCE_GO_META || nOrigType == zREFER_GO_META )
   {
      if ( SetCursorFirstEntityByInteger( *pvMOI, "Operation", "ZKey", ulOrigMetaOI_ZKey, "" ) != zCURSOR_SET )
      {
         SetNameForView( *pvMOI, "MetaGroup", vSubtask, zLEVEL_TASK );
         TraceLine( "Couldn't find \"Operation\" (MetaGroup view:%s) in Global Op Group by ZKey: %d", szCM_ViewName, ulOrigMetaOI_ZKey );
         DisplayObjectInstance( *pvMOI, "", "" );
         MessageSend( vSubtask, "CM00418", "Configuration Management",
                      "Couldn't find Global Op in Global Op Group",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }
   }

   // Name the view based upon the ZKey and update/refer type for identification by Task.
   if ( nEntityType == CM_ACTIVE_TYPE && lStatus == 1 )
      szCM_ViewName[ 0 ] = 'u';
   else
      szCM_ViewName[ 0 ] = 'r';

   zltoa( *((zPLONG) pvMOI), szCM_ViewName + 1, zsizeof( szCM_ViewName ) - 1 );
   SetNameForView( *pvMOI, szCM_ViewName, vTaskMetas, zLEVEL_SUBTASK | zNAME_AUTODROP );

   // We no longer set refer views as read-only.  Instead, we check in fnCommitObjectInstance and don't allow commits for REFER views.
#if 0
   if ( (nEntityType != CM_ACTIVE_TYPE) || (lStatus != 1) )
      SetViewReadOnly( *pvMOI );
#endif

   DropView( vWkListView );

   return( 1 );
} // fnActivateMetaOI

//./ ADD NAME=ActivateMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: ActivateMetaOI
//
//  PURPOSE:    Activates an Object Instance from a MetaList retrieved
//              via RetriveViewForMetaList, by declaring a view and then
//              loading the OI from a portable file.
//
//  PARAMETERS: pvMOI - a pointer to a View to be returned
//              ListView - a valid LPL list view
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//
//  RETURNS:    1 - Meta OI successfully activated
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zOPER_EXPORT zSHORT OPERATION
ActivateMetaOI( zVIEW   vSubtask,
                zPVIEW  pvMOI,
                zVIEW   vListView,
                zSHORT  nType,
                zLONG   lControl )
{
   zVIEW  vTaskLPLR;
   zSHORT nRC;

   *pvMOI = 0;
   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );

   SysMutexLock( vSubtask, "ActMeta", 0, 0 );
// TraceLineX( "ActivateMetaOI Locked Mutex: ActMeta  for Task: ", (zLONG) vSubtask->hTask );
   nRC = fnActivateMetaOI( vSubtask, pvMOI, vListView, nType, 0 );
// TraceLineX( "ActivateMetaOI Unlocking Mutex: ActMeta  for Task: ", (zLONG) vSubtask->hTask );
   SysMutexUnlock( vSubtask, "ActMeta", 0 );

   if ( nRC < 0 )
      return( nRC );

   if ( ObjectInstanceUpdatedFromFile( vTaskLPLR ) == 1 )
      oTZCMLPLO_CommitLPLR( vTaskLPLR );

   return( nRC );
}

//./ ADD NAME=ActivateMetaOI_ByName
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: ActivateMetaOI_ByName
//
//  PURPOSE:    Activates an Object Instance using the Name.  The routine
//              will get a MetaList if one is NOT specified in the call.
//              The Meta is "Activated" only if it is not currently loaded
//              or the call specifies to force a re-load.
//
//  PARAMETERS: pvMOI - pointer to a View to be returned
//              vListView  - valid LPL list view or ZERO
//              nType      - valid LPL meta type, i.e. zSOURCE_DIALOG_META
//              lControl   - usually  zSINGLE | zLEVEL_APPLICATION
//              pchName    - string containing 'name' of Meta
//              nCurrentOrReload - one of the following:
//                   zCURRENT_OI         0
//                   zFORCE_RELOAD       1
//
//  RETURNS:    0 - Meta OI View returned from loaded Meta
//              1 - Meta OI activated and View returned
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zOPER_EXPORT zSHORT OPERATION
ActivateMetaOI_ByName( zVIEW   vSubtask,
                       zPVIEW  pvMOI,
                       zVIEW   vListView,
                       zSHORT  nType,
                       zLONG   lControl,
                       zPCHAR  pchName,
                       zSHORT  nCurrentOrReload )
{
   zVIEW  vCM_List;
   zSHORT nEntityType;
   zSHORT nRC;

   if ( pchName == 0 || pchName[ 0 ] == 0 )
   {
      *pvMOI = 0;
      return( -1 );
   }

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   SysMutexLock( vSubtask, "ActMeta", 0, 0 );
// TraceLineX( "ActivateMetaOI_ByName Locked Mutex: ActMeta  for Task: ", (zLONG) vSubtask->hTask );

   // Get Access to CM List Object
   if ( vListView )
   {
      vCM_List = vListView;

      //*** Change Start  -  Don Christensen  -  2/17/94
      // This set cursor is necessary to position on the correct W_MetaType, when the vListView is not the default.
      if ( nType < 2000 )
      {
         nRC = SetCursorFirstEntityByInteger( vCM_List, "W_MetaType", "Type", nType + 2000, "" );
      }
      else
      {
         nRC = SetCursorFirstEntityByInteger( vCM_List, "W_MetaType", "Type", nType, "" );
      }
      //*** Change End
   }
   else
   {
      if ( nType < 2000 )
      {
         nRC = RetrieveViewForMetaList( vSubtask, &vCM_List, (zSHORT) (nType + 2000) );
      }
      else
      {
         nRC = RetrieveViewForMetaList( vSubtask, &vCM_List, nType );
      }
   }

   nRC = SetCursorFirstEntityByString( vCM_List, "W_MetaDef", "Name", pchName, "" );
   if ( nRC != zCURSOR_SET )
   {
      *pvMOI = 0;
     // The following was deleted by DonC on 9/28/07. Coming into this code is not an error condition.
     // It happens every time a new LOD is created and the return code of -1 tells the caller to create
     // the Named View (PVR).
      //SetNameForView( vCM_List, "_CM_List", vSubtask, zLEVEL_TASK );
      //TraceLine( "(tzcmoprs) ActivateMetaOI_ByName - missing Name: %s  in View: _CM_List  Entity: W_MetaDef", pchName );
      //SysMessageBox( 0, "Missing Name in View: _CM_List  Entity: W_MetaDef", pchName, -1 );
      if ( vListView == 0 )
      {
         DropView( vCM_List );
      }

   // TraceLineX( "ActivateMetaOI_ByName Unlocking Mutex: ActMeta  for Task: ", (zLONG) vSubtask->hTask );
      SysMutexUnlock( vSubtask, "ActMeta", 0 );
      return( -1 );
   }

   nRC = ActivateMetaOI( vSubtask, pvMOI, vCM_List, nType, lControl );
   if ( vListView == 0 )
   {
      DropView( vCM_List );
   }

// TraceLineX( "ActivateMetaOI_ByName Unlocking Mutex: ActMeta  for Task: ", (zLONG) vSubtask->hTask );
   SysMutexUnlock( vSubtask, "ActMeta", 0 );

   return( nRC );
}

//./ ADD NAME=ActivateMetaOI_ByZKey
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: ActivateMetaOI_ByZKey
//
//  PURPOSE:    Activates an Object Instance using a ZKey.  The routine
//              will get a MetaList if one is NOT specified in the call.
//              The Meta is "Activated" only if it is not currently loaded
//              or the call specifies to force a re-load.
//
//  PARAMETERS: pvMOI - pointer to a View to be returned
//              vListView  - valid LPL list view or ZERO
//              nType      - valid LPL meta type, i.e. zSOURCE_DIALOG_META
//              lControl   - usually  zSINGLE | zLEVEL_APPLICATION
//              lZKey      - long containing ZKey of Meta
//              nCurrentOrReload - one of the following:
//                   zCURRENT_OI         0
//                   zFORCE_RELOAD       1
//
//  RETURNS:    0 - Meta OI View returned from loaded Meta
//              1 - Meta OI activated and View returned
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zOPER_EXPORT zSHORT OPERATION
ActivateMetaOI_ByZKey( zVIEW   vSubtask,
                       zPVIEW  pvMOI,
                       zVIEW   vListView,
                       zSHORT  nType,
                       zLONG   lControl,
                       zLONG   lZKey,
                       zSHORT  nCurrentOrReload )
{
   zVIEW  vCM_List;
   zSHORT nEntityType;
   zSHORT nRC;

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   SysMutexLock( vSubtask, "ActMeta", 0, 0 );
// TraceLineX( "ActivateMetaOI_ByName Locked Mutex: ActMeta  for Task: ", (zLONG) vSubtask->hTask );

   // Get Access to CM List Object.
   if ( vListView )
   {
      vCM_List = vListView;
   }
   else
   {
      if ( nType < 2000 )
      {
         nRC = RetrieveViewForMetaList( vSubtask, &vCM_List, (zSHORT) (nType + 2000) );
      }
      else
      {
         nRC = RetrieveViewForMetaList( vSubtask, &vCM_List, nType );
      }
   }

   nRC = SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef", "CPLR_ZKey", lZKey, "" );
   if ( nRC != zCURSOR_SET )
   {
      *pvMOI = 0;
      TraceLineI( "(tzcmoprs) ActivteMetaOI_ByZKey - missing ZKey = ", lZKey );
   // TraceLineX( "ActivateMetaOI_ByZKey Unlocking Mutex: ActMeta  for Task: ", (zLONG) vSubtask->hTask );
      SysMutexUnlock( vSubtask, "ActMeta", 0 );
      return( -1 );
   }

   nRC = ActivateMetaOI( vSubtask, pvMOI, vCM_List, nType, lControl );
   if ( vListView == 0 )
      DropView( vCM_List );

// TraceLineX( "ActivateMetaOI_ByZKey Unlocking Mutex: ActMeta  for Task: ", (zLONG) vSubtask->hTask );
   SysMutexUnlock( vSubtask, "ActMeta", 0 );

   return( nRC );
}

//./ ADD NAME=ActivateMetaOI_KeepList
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: ActivateMetaOI_KeepList
//
//  PURPOSE:    Activates an Object Instance using the Name.  The routine
//              will get a MetaList if one is NOT specified in the call.
//              The Meta is "Activated" only if it is not currently loaded
//              or the call specifies to force a re-load.
//
//  PARAMETERS: pvMOI - pointer to a View to be returned
//              vListView  - valid LPL list view or ZERO
//              nType      - valid LPL meta type, i.e. zSOURCE_DIALOG_META
//              lControl   - usually  zSINGLE | zLEVEL_APPLICATION
//              pchName    - string containing 'name' of Meta
//              nCurrentOrReload - one of the following:
//                   zCURRENT_OI         0
//                   zFORCE_RELOAD       1
//              nNameOrZKey - 0 ==> Name; 1 ==> ZKey
//              lListHandle - returned/passed (initially zero)
//
//  RETURNS:    Handle to List of loaded Meta OI's
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 11
zOPER_EXPORT zLONG  OPERATION
ActivateMetaOI_KeepList( zVIEW   vSubtask,
                         zPVIEW  pvMOI,
                         zVIEW   vListView,
                         zSHORT  nType,
                         zLONG   lControl,
                         zPCHAR  pchName,
                         zLONG   lZKey,
                         zSHORT  nCurrentOrReload,
                         zSHORT  nNameOrZKey,
                         zLONG   lListHandle )
{
   ZDualCorrelatedList *pViewList;
   ZDualCorrelatedItem *pViewItem;

   if ( lListHandle )
   {
      pViewList = (ZDualCorrelatedList *) lListHandle;
   }
   else
   {
      pViewList = new ZDualCorrelatedList;
      lListHandle = (zLONG) pViewList;
   }

   if ( nNameOrZKey == 0 )
   {
      pViewItem = pViewList->FindKey( pchName );
      if ( pViewItem == 0 )
      {
         ActivateMetaOI_ByName( vSubtask, pvMOI, vListView, nType, lControl, pchName, nCurrentOrReload );
         pViewList->Add( 0, (zLONG) *pvMOI, pchName, 0 );
      }
      else
         *pvMOI = (zVIEW) pViewItem->m_lValue;
   }
   else
   {
      pViewItem = pViewList->FindKey( lZKey );
      if ( pViewItem == 0 || MiValidView( (zVIEW) pViewItem->m_lValue ) == FALSE )
      {
         ActivateMetaOI_ByZKey( vSubtask, pvMOI, vListView, nType, lControl, lZKey, nCurrentOrReload );
         pViewList->Add( lZKey, (zLONG) *pvMOI, 0, 0 );
      }
      else
         *pvMOI = (zVIEW) pViewItem->m_lValue;
   }

   return( lListHandle );
}

zOPER_EXPORT zLONG  OPERATION
DropMetaOI_FromList( zLONG   lListHandle )
{
   ZDualCorrelatedList *pViewList;
   ZDualCorrelatedItem *pViewItem;
   zVIEW vMOI;

   if ( lListHandle )
   {
      pViewList = (ZDualCorrelatedList *) lListHandle;
      while ( pViewList->m_pHeadItem )
      {
         pViewItem = pViewList->m_pHeadItem;
         pViewList->m_pHeadItem = pViewList->m_pHeadItem->m_pNextItem;
         vMOI = (zVIEW) pViewItem->m_lValue;
         if ( MiValidView( vMOI ) )
            DropObjectInstance( vMOI );
         else
            TraceLineX( "DropMetaOI_FromList unexpected invalid view: ", (zLONG) vMOI );
      }

      delete( pViewList );
   }

   return( 0 );
}

//BL, 2000.01.04 Bugfix for Repository
//If an Entity is included and created, then remove the create flag.
zOPER_EXPORT zSHORT OPERATION
fnRemoveCreateFlag( zVIEW  pvMOI )
{
   zCHAR     szEntityName[ 33 ];
   zUSHORT   uLevel;
   zVIEW     vMOI;
   zSHORT    nRC;

   CreateViewFromViewForTask( &vMOI, pvMOI, 0 );

   // Root-Entity.
   strcpy_s( szEntityName, zsizeof( szEntityName ), "" );
   zGetFirstEntityNameForView( vMOI, szEntityName );

   DefineHierarchicalCursor( vMOI, szEntityName );
   nRC = SetCursorNextEntityHierarchical( &uLevel, szEntityName, vMOI );

   while ( nRC >= zCURSOR_SET )
   {
      if ( GetIncrementalUpdateFlags( vMOI, szEntityName, zSET_INCR_CREATED ) == 1 )
      {
         if ( GetIncrementalUpdateFlags( vMOI, szEntityName, zSET_INCR_INCLUDED ) == 1 )
         {
            // zSET_INCR_PERSISTENT clears the "created" flag.
            SetIncrementalUpdateFlags( vMOI, szEntityName, zSET_INCR_PERSISTENT | zSET_INCR_CURSORPOS );
         }
      }

      nRC = SetCursorNextEntityHierarchical( &uLevel, szEntityName, vMOI );
   }

   DropHierarchicalCursor( vMOI );
   DropView( vMOI );
   return( 0 );
}

//=fnCommitMetaOI
zOPER_EXPORT zSHORT OPERATION
fnCommitMetaOI( zVIEW  vSubtask,
                zVIEW  vMOI,
                zSHORT nType,
                zVIEW  vActiveMetas,
                zVIEW  vZeidonCM,
                zVIEW  vLPLR )
{
   zSHORT nRC, nEntityType;
   zBOOL  bNewMeta;
   zSHORT ReferViewsActive, ReferOI_Active;
   zVIEW  vWork1;
   zVIEW  CM_View;
   zVIEW  MOI_ExecView;
   zVIEW  IncludeView;
   zVIEW  WKS_View;
   zVIEW  vTempLPLR;
   zCHAR  szMetaOI_Name[ 33 ];   /* protect from long name */
   zCHAR  szMetaOI_File[ 33 ];   /* protect from long name */
   zCHAR  szSubEntityName[ 33 ];
   zCHAR  szSubOI_Name[ 33 ];
   zCHAR  szObjectName[ 33 ];
   zSHORT SubType;
   zLONG  lMetaOI_ZKey;
   zLONG  lSubOI_ZKey;
   zCHAR  szFileSpec[ zMAX_FILESPEC_LTH + 1 ];
// zCHAR  szTempFileName[ 2 * zMAX_FILESPEC_LTH + 1 ];
// zCHAR  szTempFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR  szDesc[ 256 ];
   zCHAR  szMsg[ zLONG_MESSAGE_LTH + 1 ];
   zCHAR  szTimestamp[ 33 ];
   zLONG  lTaskID;
   zLONG  lMOI_InstanceID;
   zCHAR  szCM_ViewName[ 80 ];
   zCHAR  szTaskView[ 80 ];
   zCHAR  szNamedView[ 80 ];

   TraceLineS( "fnCommitMetaOI", "=======================================" );

   ReferOI_Active = 0;
   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   GetStringFromAttribute( szMetaOI_Name, zsizeof( szMetaOI_Name ), vMOI, SRC_CMOD[ nType ].szOD_ROOT, SRC_CMOD[ nType ].szOD_NAME );

   // If the view is read-only, then we can't commit it.
   nRC = MiGetUpdateForView( vMOI );
   if ( (nEntityType == CM_REFER_TYPE) || (nRC == 0) )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "The meta passed to CommitMetaOI, " );
      strcat_s( szMsg, zsizeof( szMsg ), szMetaOI_Name );
      strcat_s( szMsg, zsizeof( szMsg ), "is not an Active Meta. See Trace" );
      TraceLineS( "Zeidon Configuration Management", szMsg );
      TraceLineI( "   Type passed is: ", nType );
      MessageSend( vSubtask, "CM00422", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

      return( -1 );
   }

   // Get the ZKey for the OI we are about to commit.
   GetIntegerFromAttribute( &lMetaOI_ZKey, vMOI, SRC_CMOD[ nType ].szOD_ROOT, "ZKey" );

   // Position on the correct W_MetaType. If it doesn't exist, create one.
   if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", nType, "" ) != zCURSOR_SET )
   {
      // DGC? - Why are we creating an entity?  Shouldn't it already exist?
      // If we are commiting an OI, then it has been activated and therefore
      // the MetaType entity should have been created.

      // It does already exist for reports (so we don't get here ... DKS).
      CreateEntity( vLPLR, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vLPLR, "W_MetaType", "Type", nType );
   }

   // Position on the correct W_MetaType. If it doesn't exist, create one.
   if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", nType + 2000, "" ) != zCURSOR_SET )
   {
      // DGC? - Why are we creating an entity?  Shouldn't it already exist?
      // If we are commiting an OI, then it has been activated and therefore
      // the MetaType entity should have been created.

      // It does already exist for reports (so we don't get here ... DKS).
      CreateEntity( vLPLR, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vLPLR, "W_MetaType", "Type", nType + 2000 );
   }

   if ( SetCursorFirstEntityByAttr( vActiveMetas, "LPLR", "Name", vLPLR,
                                    "LPLR", "Name", "" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00423", "Configuration Management",
                   "Unable to locate LPLR Entity in ZeidonCM for CommitMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

      return( -1 );
   }

   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaType", "Type", nType, "" ) != zCURSOR_SET )
   {
      CreateEntity( vActiveMetas, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vActiveMetas, "W_MetaType", "Type", nType );
   }

   // Now check for Duplicately named Metas.
   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaDef", "CPLR_ZKey", lMetaOI_ZKey, "" ) < zCURSOR_SET )
   {
      nRC = fnCheckForDuplicateName( vMOI, vLPLR, szMetaOI_Name, lMetaOI_ZKey, 1 ); // Adding New Meta
   }
   else
   {
      if ( CompareAttributeToInteger( vActiveMetas, "W_MetaDef", "UpdateInd", 3 ) == 0 )
      {
         MessageSend( vSubtask, "CM00424", "Configuration Management",
                      "Deleted Meta Def passed to CommitMetaOI",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }

      nRC = fnCheckForDuplicateName( vMOI, vLPLR, szMetaOI_Name, lMetaOI_ZKey, 0 );  // Updating Meta
   }

   if ( nRC == -1 )
      return( -1 );

   if ( nRC == 1 ) // duplicate found and renamed
   {
      GetStringFromAttribute( szMetaOI_Name, zsizeof( szMetaOI_Name ), vMOI, SRC_CMOD[ nType ].szOD_ROOT, SRC_CMOD[ nType ].szOD_NAME );
   }

   if ( nType == zSOURCE_DOMAINGRP_META || nType == zSOURCE_GOPGRP_META )
   {
      // For Global Operation Groups and Domain Groups, check each Global Operation or
      // Domain within the Group to make sure there are no duplicates.
      if ( nType == zSOURCE_DOMAINGRP_META )
      {
         strcpy_s( szSubEntityName, zsizeof( szSubEntityName ), "Domain" );
         SubType = zSOURCE_DOMAIN_META;
      }
      else
      {
         strcpy_s( szSubEntityName, zsizeof( szSubEntityName ), "Operation" );
         SubType = zSOURCE_GO_META;
      }

      CreateViewFromViewForTask( &vTempLPLR, vLPLR, vSubtask );
      SetCursorFirstEntityByInteger( vTempLPLR, "W_MetaType", "Type", SubType + 2000, 0 );
      nRC = SetCursorFirstEntity( vMOI, szSubEntityName, 0 );
      while ( nRC >= zCURSOR_SET )
      {
         GetStringFromAttribute( szSubOI_Name, zsizeof( szSubOI_Name ), vMOI, szSubEntityName, "Name" );
         GetIntegerFromAttribute( &lSubOI_ZKey, vMOI, szSubEntityName, "ZKey" );
         nRC = fnCheckForDuplicateName( vMOI, vTempLPLR, szSubOI_Name, lSubOI_ZKey, 0 );
         if ( nRC == -1 )
            return( -1 );

         nRC = SetCursorNextEntity( vMOI, szSubEntityName, 0 );
      }

      // For Global Operation Groups and Domain Groups, loop through each operation or domain in the Group and update the
      // names, in case any of those names were changed. Do this first for zSOURCE type and then for zREFER type.
      for ( nRC = SetCursorFirstEntity( vMOI, szSubEntityName, 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vMOI, szSubEntityName, 0 ) )
      {
         GetStringFromAttribute( szSubOI_Name, zsizeof( szSubOI_Name ), vMOI, szSubEntityName, "Name" );
         GetIntegerFromAttribute( &lSubOI_ZKey, vMOI, szSubEntityName, "ZKey" );

         // zSOURCE type
         SetCursorFirstEntityByInteger( vTempLPLR, "W_MetaType", "Type", SubType, 0 );
         nRC = SetCursorFirstEntityByInteger( vTempLPLR, "W_MetaDef", "CPLR_ZKey", lSubOI_ZKey, 0 );
         if ( nRC >= zCURSOR_SET )
            SetAttributeFromString( vTempLPLR, "W_MetaDef", "Name", szSubOI_Name );

         // zREFER type
         SetCursorFirstEntityByInteger( vTempLPLR, "W_MetaType", "Type", SubType + 2000, 0 );
         nRC = SetCursorFirstEntityByInteger( vTempLPLR, "W_MetaDef", "CPLR_ZKey", lSubOI_ZKey, 0 );
         if ( nRC >= zCURSOR_SET )
            SetAttributeFromString( vTempLPLR, "W_MetaDef", "Name", szSubOI_Name );
      }

      DropView( vTempLPLR );
   }

// lTaskID = SysGetTaskFromView( vMOI );
   lTaskID = SysGetTaskFromView( vSubtask );

   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaDef", "CPLR_ZKey", lMetaOI_ZKey, "" ) != zCURSOR_SET )
   {
      // New Meta
      bNewMeta = TRUE;

#if 0
// PETTIT  I think the MetaDef should always exist after the change to ActivateEmptyMetaOIis made

      nRC = IncludeSubobjectFromSubobject( vActiveMetas, "W_MetaDef", vLPLR, "W_MetaDef", zPOS_AFTER );
      GetStringFromAttribute( szCM_ViewName, zsizeof( szCM_ViewName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
      strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".u" );
      CreateViewFromViewForTask( &CM_View, vMOI, vSubtask );
      SetNameForView( CM_View, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK );
      SetAttributeFromInteger( vActiveMetas, "W_MetaDef", "TaskID", lTaskID );
#endif
   }
   else
   {
      // a W_MetaDef exists for this OI in the CM Active list
      bNewMeta = FALSE;
      GetStringFromAttribute( szCM_ViewName, zsizeof( szCM_ViewName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
      strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".u" );
      if ( GetViewByName( &CM_View, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK ) < 0 )
      {
         // If such a named view was not found, then the meta was not opened for update.
         MessageSend( vSubtask, "CM00425", "Configuration Management",
                      "The Meta being committed was not Activated for update.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }

      lMOI_InstanceID = MiGetInstanceID_ForView( CM_View );
      if ( CompareAttributeToInteger( vActiveMetas, "W_MetaDef", "TaskID", lTaskID ) != 0 )
      {
         if ( CompareAttributeToInteger( vActiveMetas, "W_MetaDef", "TaskID", 0 ) == 0 )
         {
            MessageSend( vSubtask, "CM00426", "Configuration Management",
                         "The Meta passed to CommitMetaOI was not "
                         "opened for Update!",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }
         else
         {
            if ( MiGetInstanceID_ForView( vMOI ) != lMOI_InstanceID )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "The View to the Meta passed to CommitMetaOI\nis not to the the same Object Instance for\n"
                                                 "which the view was originally opened." );
               MessageSend( vSubtask, "CM00427", "Configuration Management",
                            szMsg,
                            zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               return( -1 );
            }
         }
      }

      // Replace the last zCHAR in szCM_ViewName with an 'r'.
      szCM_ViewName[ zstrlen( szCM_ViewName ) - 1 ] = 'r';
      if ( GetViewByName( &CM_View, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK ) > 0 )
      {
         // REFER OI of Meta exists - Check if there are Views to it
         ReferOI_Active = 1;
         ReferViewsActive = 0;
         lMOI_InstanceID = MiGetInstanceID_ForView( CM_View );
         nRC = SfGetFirstNamedView( &vWork1, szNamedView, vZeidonCM, zLEVEL_SUBTASK );
         while ( nRC > 0 )
         {
            if ( zstrncmp( szNamedView, "__CM.", 5 ) == 0 )
            {
               zVIEW  vWork2;

               nRC = SfGetFirstNamedView( &vWork2, szTaskView, vWork1, zLEVEL_SUBTASK );
               while ( nRC > 0 )
               {
                  if ( zstrncmp( szTaskView, "r", 1 ) == 0 )
                  {
                     if ( MiGetInstanceID_ForView( vWork2 ) == lMOI_InstanceID )
                     {
                        ReferViewsActive = 1;
                        break;
                     }
                  }

                  nRC = SfGetNextNamedView( &vWork2, szTaskView, vWork1, zLEVEL_SUBTASK );
               }
            }

            if ( ReferViewsActive == 1 )
               return( 0 );

            nRC = SfGetNextNamedView( &vWork1, szNamedView, vZeidonCM, zLEVEL_SUBTASK );
         }

         DropObjectInstance( CM_View );
      }
   }

   if ( GetViewByName( &WKS_View, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK ) <= 0 )
   {
      return( -1 );
   }

   nRC = fnGetDirectorySpec( vMOI, szFileSpec, zsizeof( szFileSpec ), nType, TRUE );

   switch ( nType )
   {
      case zSOURCE_VOR_META:
         zltoxa( lMetaOI_ZKey, szMetaOI_File );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_File );
         break;

      default:
         if ( bNewMeta == FALSE &&
              CompareAttributeToString( vActiveMetas, "W_MetaDef", "Name", szMetaOI_Name ) != 0 )
         {
            // FileName change
            nRC = (zSHORT) zstrlen( szFileSpec );
            GetStringFromAttribute( szFileSpec + nRC, zsizeof( szFileSpec ) - nRC, vActiveMetas, "W_MetaDef", "Name" );
            //TruncateName8( &szFileSpec[ nRC ] );
            strcat_s( szFileSpec, zsizeof( szFileSpec ), SRC_CMOD[ nType ].szOD_EXT );
            SysOpenFile( vLPLR, szFileSpec, COREFILE_DELETE );
            if ( nType == zSOURCE_DIALOG_META || nType == zSOURCE_LOD_META )
            {
               GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vLPLR, "LPLR", "ExecDir" );
               ofnTZCMWKSO_AppendSlash( szFileSpec );
               nRC = (zSHORT) zstrlen( szFileSpec );
               GetStringFromAttribute( szFileSpec + nRC, zsizeof( szFileSpec ) - nRC, vActiveMetas, "W_MetaDef", "Name" );
               //TruncateName8( &szFileSpec[ nRC ] );

               if ( nType == zSOURCE_LOD_META )
                  strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XOD" );
               else
                  strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XWD" );

               SysOpenFile( vLPLR, szFileSpec, COREFILE_DELETE );
            }

            nRC = fnGetDirectorySpec( vLPLR, szFileSpec, zsizeof( szFileSpec ), nType, TRUE );
         }

         strcpy_s( szMetaOI_File, zsizeof( szMetaOI_File ), szMetaOI_Name );
         //TruncateName8( szMetaOI_File );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_File );

         break; // default.

   } // switch ( nType )...

   strcat_s( szFileSpec, zsizeof( szFileSpec ), SRC_CMOD[ nType ].szOD_EXT );
   GetVariableFromAttribute( szDesc, 0, zTYPE_STRING, 255, vMOI, SRC_CMOD[ nType ].szOD_ROOT, "Desc", "", 0 );

   // Commit the XWD/XRA if a Dialog Meta.
   if ( nType == zSOURCE_DIALOG_META || nType == zSOURCE_REPORT_META || nType == zSOURCE_XSLT_META )
   {
      zVIEW vDialogSubtask;

      GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vLPLR, "LPLR", "ExecDir" );
      ofnTZCMWKSO_AppendSlash( szFileSpec );
      strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_File );

      GetViewByName( &vDialogSubtask, "TZCM_DialogSubtask", vSubtask, zLEVEL_TASK );
//    MOI_ExecView = ConvertDialog( vDialogSubtask, vMOI, "" );
      if ( nType == zSOURCE_DIALOG_META )
      {
         zCHAR szRemotePath[ zMAX_FILESPEC_LTH + 1 ];
         zVIEW  vXRA;
         zSHORT nLth;

         nLth = (zSHORT) zstrlen( szFileSpec );
         MOI_ExecView = ConvertDialog( vSubtask, vMOI, "", &vXRA );

         SysReadZeidonIni( -1, "[Workstation]", "ExecutableRemote", szRemotePath, zsizeof( szRemotePath ) );
         if ( szRemotePath[ 0 ] )
         {
            SysReadZeidonIni( -1, "[Workstation]", "ExecutableRemotePath", szRemotePath, zsizeof( szRemotePath ) );
            if ( szRemotePath[ 0 ] )
            {
               ofnTZCMWKSO_AppendSlash( szRemotePath );
               strcat_s( szRemotePath, zsizeof( szRemotePath ), szMetaOI_File );
               strcat_s( szRemotePath, zsizeof( szRemotePath ), ".XRA" );
            }
            else
            {
               strcpy_s( szRemotePath, zsizeof( szRemotePath ), szFileSpec );
               strcpy_s( szRemotePath + nLth, zsizeof( szRemotePath ) - nLth, ".XRA" );
            }

            nRC = CommitOI_ToFile( vXRA, szRemotePath, zSINGLE );
            if ( nRC )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "CommitMetaOI failed trying to save " );
               strcat_s( szMsg, zsizeof( szMsg ), szRemotePath );
               MessageSend( vSubtask, "CM00428", "Configuration Management",
                            szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            }

            DropObjectInstance( vXRA );
         }

         strcpy_s( szFileSpec + nLth, zsizeof( szFileSpec ) - nLth, ".XWD" );
      }
      else
      if ( nType == zSOURCE_REPORT_META )
      {
         // Create the Report executable file (.XRP) in the executable meta
         // directory, which is a flattened version of the Report source
         // (.PRP) in the source meta directory.  The executable is flattened
         // by putting all controls to the Control level (moving CtrlCtrl
         // entities directly under the appropriate Group entities as Control
         // entities ... no recursive relationships).
#if 0
         fnGetDirectorySpec( szFileSpec, zsizeof( szFileSpec ), nType, TRUE );
         strcpy_s( szMetaOI_File, zsizeof( szMetaOI_File ), szMetaOI_Name );
         //TruncateName8( szMetaOI_File );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_File );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), SRC_CMOD[ nType ].szOD_EXT );

         GetViewByName( &vTempLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
         GetStringFromAttribute( szFileSpecExec, zsizeof( szFileSpecExec ),
                                 vTempLPLR, "LPLR", "ExecDir" );
         ofnTZCMWKSO_AppendSlash( szFileSpecExec );
         strcat_s( szFileSpecExec, zsizeof( szFileSpecExec ), szMetaOI_File );
         strcat_s( szFileSpecExec, zsizeof( szFileSpecExec ), ".XRP" );
         SysCopyFile( szFileSpec, szFileSpecExec, TRUE );
         break;
#endif

         MOI_ExecView = ConvertReport( vLPLR, vMOI, "" );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XRP" );
      }
      else
      {
         // Create the XSLT executable file (.XSL) in the executable meta
         // directory, which is a flattened version of the Report source
         // (.PSL) in the source meta directory.  The executable is flattened
         // by putting all controls to the Control level (moving CtrlCtrl
         // entities directly under the appropriate Group entities as Control
         // entities ... no recursive relationships).

         MOI_ExecView = ConvertXSLT( vLPLR, vMOI, "" );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XSL" );
      }

      nRC = CommitOI_ToFile( MOI_ExecView, szFileSpec, zSINGLE );
      if ( nRC )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "CommitMetaOI failed trying to save " );
         strcat_s( szMsg, zsizeof( szMsg ), szFileSpec );
         MessageSend( vSubtask, "CM00428", "Configuration Management",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }

      DropObjectInstance( MOI_ExecView );
      fnGetDirectorySpec( vMOI, szFileSpec, zsizeof( szFileSpec ), nType, TRUE );
      strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_File );
      strcat_s( szFileSpec, zsizeof( szFileSpec ), SRC_CMOD[ nType ].szOD_EXT );
   }

   // Decide what control flags should be used based on the current file
   // version and the INI settings.
   nRC = fnAllowBinaryDataInSourceMetaFiles( vLPLR );
   if ( nRC == 1 )
   {
      // Keep it the same format.
      if ( MiCompareOI_ToRelease( vMOI, szlReleaseCompatible ) <= 0 )
      {
         MiSetOI_ReleaseForView( vMOI, szlReleaseCompatible );
         nRC = CommitOI_ToFile( vMOI, szFileSpec, zSINGLE );
      }
      else
      {
         MiSetOI_ReleaseForView( vMOI, szlReleaseCurrent );
         nRC = CommitOI_ToFile( vMOI, szFileSpec,
                                zSINGLE | zENCODE_BLOBS | zNO_NULL_STRING_TERM );
      }
   }
   else
   if ( nRC == 2 )
   {
      // Force it to compatibility format.
      MiSetOI_ReleaseForView( vMOI, szlReleaseCompatible );
      nRC = CommitOI_ToFile( vMOI, szFileSpec, zSINGLE );
   }
   else
   {
      // Use the current release version of the software.
      MiSetOI_ReleaseForView( vMOI, szlReleaseCurrent );
      nRC = CommitOI_ToFile( vMOI, szFileSpec,
                             zSINGLE | zENCODE_BLOBS | zNO_NULL_STRING_TERM );
   }

   if ( nRC )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "CommitMetaOI failed trying to save " );
      strcat_s( szMsg, zsizeof( szMsg ), szFileSpec );
      MessageSend( vSubtask, "CM00429", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( ReferOI_Active == 1 )
   {
      if ( nType != zSOURCE_DIALOG_META && nType != zSOURCE_REPORT_META &&
           nType != zSOURCE_XSLT_META && nType != zSOURCE_UIS_META )
      {
         nRC = ActivateMetaOI_ByZKey( vSubtask, &CM_View, vWork1,
                                      (zSHORT) (nType + 2000),
                                      zLEVEL_SUBTASK, lMetaOI_ZKey, 0 );

         // If we are committing a DomainGroup, relink it with any ERDs
         // that are currently in memory.
         if ( nType == zSOURCE_DOMAINGRP_META )
         {
            zVIEW vDomainGrp;

            nRC = SfGetFirstNamedView( &vWork1, szNamedView, vZeidonCM,
                                       zLEVEL_SUBTASK );
            while ( nRC > 0 )
            {
               if ( zstrncmp( szNamedView, "__CM.", 5 ) == 0 )
                  szObjectName[ 0 ] = 0;
               else
                  MiGetObjectNameForView( szObjectName, vWork1 );

               if ( zstrcmp( (LPCTSTR) szObjectName, "TZEREMDO" ) == 0 )
               {
                  // Loop through all Domains in ER and Relink any of those
                  // Domains to the current DomainGrp that are a part of that
                  // DomainGrp.
                  CreateViewFromViewForTask( &vDomainGrp, vMOI, vSubtask );
                  for ( nRC = SetCursorFirstEntity( vWork1, "Domain", "EntpER_Model" );
                        nRC >= zCURSOR_SET;
                        nRC = SetCursorNextEntity( vWork1, "Domain", "EntpER_Model" ) )
                  {
                     nRC = SetCursorFirstEntityByAttr( vDomainGrp, "Domain", "ZKey",
                                                       vWork1, "Domain", "ZKey", 0 );
                     if ( nRC >= 0 )
                     {
                        RelinkInstanceToInstance( vWork1,     "Domain",
                                                  vDomainGrp, "Domain" );
                     }
                  }

                  DropView( vDomainGrp );
               }

               nRC = SfGetNextNamedView( &vWork1, szNamedView, vZeidonCM,
                                         zLEVEL_SUBTASK );
            }
         }

         DropMetaOI( vSubtask, CM_View );
      }
   }

   // Reset to correct W_MetaType in case of PostActivate having changed
   // position.
   SetCursorFirstEntityByInteger( vLPLR, "W_MetaType",
                                  "Type", nType + 2000, "" );
   if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaDef", "CPLR_ZKey",
                                       lMetaOI_ZKey, "" ) != zCURSOR_SET )
   {
      // Corresponding W_MetaDef Not Found - New Meta.
      CreateEntity( vLPLR, "W_MetaDef", zPOS_AFTER );
      SetAttributeFromInteger( vLPLR, "W_MetaDef", "Status", 1 );
   }

   SetAttributeFromString( vLPLR, "W_MetaDef", "Name", szMetaOI_Name );
   SysGetDateTime( szTimestamp, zsizeof( szTimestamp ) );
   SetAttributeFromString( vLPLR, "W_MetaDef", "LastUpdateDate", szTimestamp );
   SetAttributeFromString( vLPLR, "W_MetaDef", "LastSyncDate", szTimestamp );
   SetAttributeFromInteger( vLPLR, "W_MetaDef", "UpdateInd", 2 );
   SetAttributeFromInteger( vLPLR, "W_MetaDef", "CPLR_ZKey", lMetaOI_ZKey );
   SetAttributeFromString( vLPLR, "W_MetaDef", "Desc", szDesc );

   // Include W_MetaDef to Active MetaDef if not already there.
   CreateViewFromViewForTask( &IncludeView, vLPLR, vSubtask );
   SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", nType, "" );
   if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaDef",
                                       "CPLR_ZKey", lMetaOI_ZKey,
                                       "" ) != zCURSOR_SET )
   {
      // New
      nRC = IncludeSubobjectFromSubobject( vLPLR, "W_MetaDef",
                                           IncludeView, "W_MetaDef",
                                           zPOS_AFTER );

      //BL, 1999.12.29  if check in, then this Meta does exists in
      //                View vActiveMetas
      if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaDef",
                                          "CPLR_ZKey", lMetaOI_ZKey,
                                          "" ) != zCURSOR_SET )
      {
         nRC = IncludeSubobjectFromSubobject( vActiveMetas, "W_MetaDef",
                                              vLPLR, "W_MetaDef",
                                              zPOS_AFTER );
      }

      GetStringFromAttribute( szCM_ViewName, zsizeof( szCM_ViewName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
      strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".u" );
      CreateViewFromViewForTask( &CM_View, vMOI, vSubtask );
      SetNameForView( CM_View, szCM_ViewName, vZeidonCM, zLEVEL_SUBTASK );
      SetAttributeFromInteger( vActiveMetas, "W_MetaDef", "TaskID", lTaskID );
   }

   DropView( IncludeView );
   zgSortEntityWithinParent( zASCENDING, vLPLR, "W_MetaDef", "Name", "" );

   switch ( nType )
   {
      case zSOURCE_ERD_META:
         // Make sure that all LODs are eliminated from the Active Metas list.
         if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaType", "Type",
                                             zSOURCE_LOD_META, 0 ) >= zCURSOR_SET )
         {
            for ( nRC =  SetCursorFirstEntity( vActiveMetas, "W_MetaDef", 0 );
                  nRC >= zCURSOR_SET;
                  nRC =  SetCursorNextEntity( vActiveMetas, "W_MetaDef", 0 ) )
            {
               GetStringFromAttribute( szNamedView, zsizeof( szNamedView ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
               strcat_s( szNamedView, zsizeof( szNamedView ), ".r" );
               if ( GetViewByName( &CM_View, szNamedView, vZeidonCM, zLEVEL_SUBTASK ) > 0 )
               {
                  DropObjectInstance( CM_View );
               }

               ExcludeEntity( vActiveMetas, "W_MetaDef", zREPOS_NONE );
            }
         }

         break;

      case zSOURCE_LOD_META:
         nRC = SetNameForView( vMOI, "TZZOLODO", vSubtask, zLEVEL_TASK );
         oTZZOXODO_SaveXOD( vSubtask, vMOI );

         // Get access to the newly built XOD.
         if ( GetViewByName( &MOI_ExecView, "TZZOXODO", vSubtask, zLEVEL_TASK ) < 1 )
         {
            strcpy_s( szMsg, zsizeof( szMsg ), "(fnCommitMetaOI) Unable to Access XOD. XOD must be opened." );
            MessageSend( vSubtask, "CM00430", "Configuration Management",
                         szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }

         // Save the XOD to a file.
         GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vLPLR, "LPLR", "ExecDir" );
         ofnTZCMWKSO_AppendSlash( szFileSpec );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_File );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XOD" );
         if ( CommitOI_ToFile( MOI_ExecView, szFileSpec, zSINGLE ) != 0 )
         {
            strcpy_s( szMsg, zsizeof( szMsg ), "Commit of XOD failed." );
            MessageSend( vSubtask, "CM00431", "Configuration Management",
                         szMsg,
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }

         break;

      case zSOURCE_PENV_META:
         MOI_ExecView = CreatePE_ExecVersion( vLPLR, vMOI );
         GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vLPLR, "LPLR", "ExecDir" );
         ofnTZCMWKSO_AppendSlash( szFileSpec );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), "ZEIDON.XPE" );
         if ( CommitOI_ToFile( MOI_ExecView, szFileSpec, zSINGLE ) != 0 )
         {
            strcpy_s( szMsg, zsizeof( szMsg ), "Commit of Executable Presentation Environment -\n" );
            strcpy_s( szMsg, zsizeof( szMsg ), szFileSpec );
            strcpy_s( szMsg, zsizeof( szMsg ), " failed." );
            MessageSend( vSubtask, "CM00432", "Configuration Management",
                         szMsg,
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }

         break;

      case zSOURCE_GOPGRP_META:
      case zSOURCE_DOMAINGRP_META:
      {
         zVIEW  vWorkRefer;
         zVIEW  vWorkSource;
         zLONG  lStatus;
         zLONG  lSourceItem;
         zLONG  lReferItem;
         zPCHAR lpchItemName;
         zPCHAR lpchGroupName;

         // We have just committed a group (e.g.  DomainGroup).  We need to
         // create a W_MetaDef entity for each item in the group (e.g.
         // domain) so that CM can then activate an item by name.

         // The logic is the same for both domain and GO groups, but some of
         // the values are different, so we set up some variables.
         if ( nType == zSOURCE_DOMAINGRP_META )
         {
            lReferItem    = zREFER_DOMAIN_META;
            lSourceItem   = zSOURCE_DOMAIN_META;
            lpchItemName  = "Domain";                 // Name of the item ent.
            lpchGroupName = "DomainGroup";            // Name of group entity.
         }
         else
         {
            lReferItem    = zREFER_GO_META;
            lSourceItem   = zSOURCE_GO_META;
            lpchItemName  = "Operation";              // Name of the item ent.
            lpchGroupName = "GlobalOperationGroup";   // Name of group entity.
         }

         CreateViewFromViewForTask( &vWorkRefer, vLPLR, vSubtask );
         CreateViewFromViewForTask( &vWorkSource, vLPLR, vSubtask );

#ifdef DEBUG
         SetNameForView( vWorkRefer, "WorkRefer", vSubtask, zLEVEL_TASK );
         SetNameForView( vWorkSource, "WorkSource", vSubtask, zLEVEL_TASK );
#endif

         // Get the value of W_MetaDef.Status from the group W_MetaDef. If the
         // attribute isn't set then set lStatus = -1. Otherwise lStatus will
         // be 0 or 1.  Later on when we're setting W_MetaDef.Status for the
         // domain, if lStatus = -1 then we'll leave W_MetaDef.Status as null.
         // NOTE:  We are assuming that the view vLPLR is pointing to the
         // correct group W_MetaDef.
         if ( GetIntegerFromAttribute( &lStatus, vLPLR, "W_MetaDef", "Status" ) < 0 )
         {
            lStatus = -1;
         }

         // Find the item Meta type (eg Domain). If it doesn't exist, create it.
         if ( SetCursorFirstEntityByInteger( vWorkSource, "W_MetaType",
                                             "Type", lSourceItem, "" ) != zCURSOR_SET )
         {
            CreateEntity( vWorkSource, "W_MetaType", zPOS_LAST );
            SetAttributeFromInteger( vWorkSource, "W_MetaType", "Type", lSourceItem );
         }

         // Same for REFER
         if ( SetCursorFirstEntityByInteger( vWorkRefer, "W_MetaType",
                                             "Type", lReferItem, "" ) != zCURSOR_SET )
         {
            CreateEntity( vWorkRefer, "W_MetaType", zPOS_LAST );
            SetAttributeFromInteger( vWorkRefer, "W_MetaType", "Type", lReferItem );
         }

         // Loop through each of the items in the MetaDef, looking for items
         // with GroupName that matches the name of the group.  If it doesn't
         // exist in the Meta OI, then it's been deleted from the Meta and it
         // needs to be deleted from the item list.
         for ( nRC = SetCursorFirstEntityByAttr( vWorkRefer, "W_MetaDef", "GroupName",
                                                 vMOI, lpchGroupName, "Name", 0 );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntityByAttr( vWorkRefer, "W_MetaDef", "GroupName",
                                                vMOI, lpchGroupName, "Name", 0 ) )
         {
            // Try to find the item in the Meta OI by ZKey.  If it doesn't exist,
            // then it no longer exists in the Meta OI and needs to be deleted
            // from the LPLR.
            if ( SetCursorFirstEntityByAttr( vMOI, lpchItemName, "ZKey",
                                             vWorkRefer, "W_MetaDef",
                                             "CPLR_ZKey", "" ) != zCURSOR_SET )
            {
               DeleteEntity( vWorkRefer, "W_MetaDef", zREPOS_NONE );
            }
         }

         // Loop through each of the items in the group.  If it doesn't
         // exist in the Refer LPLR, add it to both source and refer.
         for ( nRC = SetCursorFirstEntity( vMOI, lpchItemName, "" );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntity( vMOI, lpchItemName, "" ) )
         {
            // Try to find the W_MetaDef by ZKey.  If it doesn't exist, then it
            // needs to be created.
            if ( SetCursorFirstEntityByAttr( vWorkRefer, "W_MetaDef", "CPLR_ZKey",
                                             vMOI, lpchItemName, "ZKey", "" ) != zCURSOR_SET )
            {
               // Create entity in refer meta type
               CreateEntity( vWorkRefer, "W_MetaDef", zREPOS_LAST );
               SetAttributeFromAttribute( vWorkRefer, "W_MetaDef", "Name",
                                          vMOI, lpchItemName, "Name" );
               SetAttributeFromAttribute( vWorkRefer, "W_MetaDef", "CPLR_ZKey",
                                          vMOI, lpchItemName, "ZKey" );
               SetAttributeFromAttribute( vWorkRefer, "W_MetaDef", "GroupName",
                                          vMOI, lpchGroupName, "Name" );
               if ( lStatus >= 0 )
                  SetAttributeFromInteger( vWorkRefer, "W_MetaDef", "Status", lStatus );

               // Create entity in source meta type
               CreateEntity( vWorkSource, "W_MetaDef", zREPOS_LAST );
               SetAttributeFromAttribute( vWorkSource, "W_MetaDef", "Name", vMOI, lpchItemName, "Name" );
               SetAttributeFromAttribute( vWorkSource, "W_MetaDef", "CPLR_ZKey", vMOI, lpchItemName, "ZKey" );
               SetAttributeFromAttribute( vWorkSource, "W_MetaDef", "GroupName", vMOI, lpchGroupName, "Name" );

               // If lStatus is not -1, then we need to set status in W_MetaDef.
               if ( lStatus >= 0 )
               {
                  SetAttributeFromInteger( vWorkSource, "W_MetaDef", "Status", lStatus );
               }
            }

         } // for...

         DropView( vWorkRefer );
         DropView( vWorkSource );

         break;

      } // case zSOURCE_DOMAINGRP_META...

   } // switch ( nType )...

   if ( oTZCMLPLO_CommitLPLR( vLPLR ) == 0 )
   {
      if ( oTZCMWKSO_CommitWorkstation( WKS_View ) == 0 )
         return( 1 );
   }

   return( -1 );
} // fnCommitMetaOI

//./ ADD NAME=CommitMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: CommitMetaOI
//
//  PURPOSE:    Commits an Zeidon Meta Object Instance by storing it to
//              a portable file.
//
//  PARAMETERS: vMOI - the view of the OI to be stored
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//
//  RETURNS:    1 - Meta OI successfully committed
//              0 - Meta is being referenced by another Zeidon Tool and
//                  the Meta cannot be saved at this time
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zOPER_EXPORT zSHORT OPERATION
CommitMetaOI( zVIEW  vSubtask,
              zVIEW  vMOI,
              zSHORT nType )
{
   zSHORT nRC;
   zVIEW vOrigActiveMetas;
   zVIEW vActiveMetas;
   zVIEW vZeidonCM;
   zVIEW vLPLR;

   TraceLineS( "CommitMetaOI ", "========================================" );
   if ( GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
   {
      MessageSend( vSubtask, "CM00433", "Configuration Management",
                   "Unable to locate TaskLPLR in CommitMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION ) <= 0 )
   {
      MessageSend( vSubtask, "CM00434", "Configuration Management",
                   "Unable to locate ZeidonCM in CommitMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( GetViewByName( &vOrigActiveMetas, "OpenCM_Metas",
                       vZeidonCM, zLEVEL_SUBTASK ) <= 0 )
   {
      MessageSend( vSubtask, "CM00435", "Configuration Management",
                   "Unable to locate OpenCM_Metas in CommitMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Use a temporay view for vActiveMetas so that no subordinate processing
   // will alter vActiveMetas position (as ConvertDialog does in Domain
   // handling).
   CreateViewFromViewForTask( &vActiveMetas, vOrigActiveMetas, vSubtask );

   nRC = fnCommitMetaOI( vSubtask, vMOI, nType, vActiveMetas, vZeidonCM, vLPLR );
   if ( nRC )
   {
      DropView( vActiveMetas );
      TraceLineI( "CommitMetaOI RC = ", nRC );
      return( nRC );
   }
   else
   {
      zCHAR szMsg[ zMAX_MESSAGE_LTH + 1 ];

      GetVariableFromAttribute( szMsg, 0, zTYPE_STRING, 125, vActiveMetas,
                                "W_MetaType", "Type", "CM_Type", 0 );
      strcat_s( szMsg, zsizeof( szMsg ), " " );
      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ),
                              vActiveMetas, "W_MetaDef", "Name" );
      strcat_s( szMsg, zsizeof( szMsg ), " is in use by another tool.\n"
                      "To complete save, close the Zeidon Tool(s) and\n"
                      "retry the save.  If all else fails, check OpenCM_Metas" );
      if ( MessagePrompt( vMOI, "CM00436", "Configuration Management",
                           szMsg, zBEEP, zBUTTONS_YESNO, zRESPONSE_YES, 0 )  == zRESPONSE_NO )
      {
         DropView( vActiveMetas );
         return( nRC );
      }

      do
      {
         nRC = fnCommitMetaOI( vSubtask, vMOI, nType, vActiveMetas, vZeidonCM, vLPLR );
         if ( nRC == 0 )
         {
            nRC = MessagePrompt( vMOI, "CM00437", "Configuration Management",
                                  szMsg, zBEEP, zBUTTONS_YESNO, zRESPONSE_YES, 0 );
            if ( nRC == zRESPONSE_NO || nRC == zCALL_ERROR )
            {
               DropView( vActiveMetas );
               return( 0 );
            }
         }
      } while ( nRC == 0 );

      DropView( vActiveMetas );
      TraceLineI( "CommitMetaOI nRC = ", nRC );
      return( nRC );
   }
} // CommitMetaOI

zOPER_EXPORT zSHORT OPERATION
CommitDependentOI( zVIEW  vSubtask,
                   zVIEW  vMOI,
                   zSHORT nType )
{
   zSHORT nRC, nEntityType;
   zLONG lFlags;
   zVIEW MOI_ExecView;
   zVIEW vZeidonCM;
   zVIEW CM_View;
   zVIEW vActiveMetas;
   zVIEW vTaskLPLR;
   zVIEW WKS_View;
   zVIEW vProfileXFER;
   zCHAR szMetaOI_Name[ 80 ];   // protect from long name
   zCHAR szMetaOI_File[ 33 ];   // protect from long name
   zLONG lMetaOI_ZKey;
   zCHAR szFileSpec[ zMAX_FILESPEC_LTH + 1 ];
// zCHAR szTempFileName[ 2 * zMAX_FILESPEC_LTH + 1 ]; // includes szFileSpec
   zCHAR szMsg[ zMAX_MESSAGE_LTH + 1 ];
   zCHAR szTimestamp[ 33 ];

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   if ( nEntityType != CM_REFER_TYPE )
   {
      MessageSend( vSubtask, "CM00438", "Configuration Management",
                   "Meta passed to CommitDependentOI is not a REFER Meta, see Trace",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      TraceLineS( "Zeidon Configuration Management",
       "Meta passed to CommitDependentOI is not a REFER Meta, Type passed is:" );
      TraceLineI( "Zeidon Configuration Management", nType );
      return( -1 );
   }

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
      return( -1 );

   if ( GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION ) <= 0 )
   {
      return( -1 );
   }

   if ( GetViewByName( &WKS_View, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK ) <= 0 )
   {
      return( -1 );
   }

   if ( SetCursorFirstEntityByInteger( vTaskLPLR, "W_MetaType",
                                       "Type", nType, "" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00439", "Configuration Management",
                   "Meta type passed to CommitMetaOI is not in LPLR, see Trace",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      TraceLineS( "Zeidon Configuration Management",
       "Meta type passed to CommitMetaOI is not in LPLR, Type passed is:" );
      TraceLineI( "Zeidon Configuration Management", nType );
      return( -1 );
   }

   nRC = fnGetDirectorySpec( vMOI, szFileSpec, zsizeof( szFileSpec ), nType, TRUE );

   GetIntegerFromAttribute( &lMetaOI_ZKey, vMOI,
                            REFER_CMOD[ nType - 2000 ].szOD_ROOT, "ZKey" );
   GetStringFromAttribute( szMetaOI_Name, zsizeof( szMetaOI_Name ), vMOI,
                           REFER_CMOD[ nType - 2000 ].szOD_ROOT,
                           REFER_CMOD[ nType - 2000 ].szOD_NAME );
   if ( nType == zREFER_VOR_META )
   {
      zltoxa( lMetaOI_ZKey, szMetaOI_File );
   }
   else
   {
      strcpy_s( szMetaOI_File, zsizeof( szMetaOI_File ), szMetaOI_Name );
      //TruncateName8( szMetaOI_File );
   }

   strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_File );
   strcat_s( szFileSpec, zsizeof( szFileSpec ), REFER_CMOD[ nType - 2000 ].szOD_EXT );
   if ( SetCursorFirstEntityByInteger( vTaskLPLR, "W_MetaDef",
                                       "CPLR_ZKey", lMetaOI_ZKey,
                                       "" ) != zCURSOR_SET )   // Not Found
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Meta passed to CommitDependentOI - " );
      strcat_s( szMsg, zsizeof( szMsg ), szMetaOI_Name );
      strcat_s( szMsg, zsizeof( szMsg ), " Not found in LPLR!" );
      MessageSend( vSubtask, "CM00440", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( CompareAttributeToInteger( vTaskLPLR, "W_MetaDef", "UpdateInd", 3 ) == 0 )
   {
      MessageSend( vSubtask, "CM00441", "Configuration Management",
                   "Deleted Meta Def passed to CommitDependentOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   lFlags = zINCREMENTAL;
   oTZ__PRFO_GetViewToProfile( &vProfileXFER, "TZ", vSubtask, zCURRENT_OI );
   if ( vProfileXFER )
   {
      if ( CompareAttributeToString( vProfileXFER, "TZ",
                                     "CM_FileType", "B" ) != 0 )
//                                   "CM_FileType", "A" ) != 0 )
//            lFlags |= zBINARY;
         lFlags |= zASCII;
   }

///// All this just to get an updatable Meta  //////////////////////////
   /* Get the view to the vTaskMetas subtask - remove if not needed
   fnGetTaskOI_ListName( vSubtask, szMetaOI_Name, zsizeof( szMetaOI_Name ) );
   nRC = GetViewByName( &vTaskMetas, szMetaOI_Name, vZeidonCM, zLEVEL_SUBTASK );
   */
   // Get the view to the ActiveMeta OI
   nRC = GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK );
   // Need the name of the TaskLPLR to get to the root LPLR in the ActiveMeta OI
   nRC = GetStringFromAttribute( szMsg, zsizeof( szMsg ), vTaskLPLR, "LPLR", "Name" );
   nRC = SetCursorFirstEntityByString( vActiveMetas, "LPLR", "Name", szMsg, "" );

   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaType", "Type",
                                       nType - 2000, "" ) != zCURSOR_SET )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Meta Type not found in ActiveMeta List.\nType is " );
      zltoa( nType - 2000, szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ) );
      MessageSend( vSubtask, "CM00442", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }
   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaDef", "CPLR_ZKey", lMetaOI_ZKey, "" ) != zCURSOR_SET )   // Not in the Active List
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Meta not found in ActiveMeta List.\nType is " );
      strcat_s( szMsg, zsizeof( szMsg ), szMetaOI_Name );
      MessageSend( vSubtask, "CM00443", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   GetStringFromAttribute( szMsg, zsizeof( szMsg ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
   strcat_s( szMsg, zsizeof( szMsg ), ".r" );
   if ( GetViewByName( &CM_View, szMsg, vZeidonCM, zLEVEL_SUBTASK ) < 1 )
   {
      // vActiveMetas has him but it's not still active
      strcpy_s( szMsg, zsizeof( szMsg ), "Meta not found in ActiveMeta List.\nName is " );
      strcat_s( szMsg, zsizeof( szMsg ), szMetaOI_Name );
      MessageSend( vSubtask, "CM00444", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   ////////////////////////////////////////////////////////////////////////
   // Decide what control flags should be use based on the current file version
   // and the INI settings
   nRC = fnAllowBinaryDataInSourceMetaFiles( vMOI );
   if ( nRC == 1 )
   {
      // keep it the same format as the file
      if ( MiCompareOI_ToRelease( vMOI, szlReleaseCompatible ) <= 0 )
      {
         MiSetOI_ReleaseForView( vMOI, szlReleaseCompatible );
         nRC = CommitOI_ToFile( vMOI, szFileSpec, lFlags );
      }
      else
      {
         MiSetOI_ReleaseForView( vMOI, szlReleaseCurrent );
         nRC = CommitOI_ToFile( vMOI, szFileSpec, lFlags | zENCODE_BLOBS | zNO_NULL_STRING_TERM );
      }
   }
   else
   if ( nRC == 2 )
   {
      // Force it to compatibility format
      MiSetOI_ReleaseForView( vMOI, szlReleaseCompatible );
      nRC = CommitOI_ToFile( vMOI, szFileSpec, lFlags );
   }
   else
   {
      // Use the current format
      MiSetOI_ReleaseForView( vMOI, szlReleaseCurrent );
      nRC = CommitOI_ToFile( vMOI, szFileSpec, lFlags | zENCODE_BLOBS | zNO_NULL_STRING_TERM );
   }

   if ( nRC )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "CommitDependentOI failed trying to save " );
      strcat_s( szMsg, zsizeof( szMsg ), szFileSpec );
      MessageSend( vSubtask, "CM00445", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   SetAttributeFromString( vTaskLPLR, "W_MetaDef", "Name", szMetaOI_Name );
   SysGetDateTime( szTimestamp, zsizeof( szTimestamp ) );
   SetAttributeFromString( vTaskLPLR, "W_MetaDef", "LastSyncDate", szTimestamp );
   SetAttributeFromInteger( vTaskLPLR, "W_MetaDef", "UpdateInd", 1 );

   // zgSortEntityWithinParent( zASCENDING, vTaskLPLR, "W_MetaDef", "Name", "" );
   if ( nType == zREFER_LOD_META )
   {
      nRC = SetNameForView( vMOI, "TZZOLODO", vMOI, zLEVEL_TASK );
      oTZZOXODO_SaveXOD( vSubtask, vMOI );

      // Get access to the newly built XOD
      if ( GetViewByName( &MOI_ExecView, "TZZOXODO", vSubtask, zLEVEL_TASK ) < 1 )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "(CommitDependentOI) Unable to Access XOD. XOD must be opened." );
         MessageSend( vSubtask, "CM00446", "Configuration Management",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( 0 );
      }

      // Save the XOD to a file
      GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vTaskLPLR, "LPLR", "ExecDir" );
      ofnTZCMWKSO_AppendSlash( szFileSpec );
      strcpy_s( szMetaOI_File, zsizeof( szMetaOI_File ), szMetaOI_Name );
   // TruncateName8( szMetaOI_File );
      strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_File );
      strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XOD" );
      lFlags = zSINGLE;
      if ( CommitOI_ToFile( MOI_ExecView, szFileSpec, lFlags ) != 0 )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Commit of XOD failed." );
         MessageSend( vSubtask, "CM00447", "Configuration Management",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }
   }
   if ( oTZCMLPLO_CommitLPLR( vTaskLPLR ) == 0 )
   {

/* PETTIT Probably don't need to commit WKS because MaxZKey shouldn't have been updated.

      if ( oTZCMWKSO_CommitWorkstation( WKS_View ) == 0 )
*/
         return( 1 );
   }
   return( -1 );
}

//./ ADD NAME=ActivateEmptyMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: ActivateEmptyMetaOI
//
//  PURPOSE:    Activates an empty Zeidon Meta OI by declaring a view
//              and then activating an empty object instance
//
//  PARAMETERS: pvMOI - a pointer to a View to be returned
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//
//  RETURNS:    1 - Meta OI successfully activated
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zOPER_EXPORT zSHORT OPERATION
ActivateEmptyMetaOI( zVIEW  vSubtask,
                     zPVIEW pvMOI,
                     zSHORT nType,
                     zLONG  lControl )
{
   zVIEW  vTaskLPLR;
   zVIEW  vZeidonCM;
   zVIEW  vActiveMetas;
   zVIEW  vTaskMetas;
   zSHORT nEntityType;
   zCHAR  szWorkName[ 80 ];
   zCHAR  szOD_RootName[ 33 ];
   zSHORT nRC;

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
      return( -1 );

   if ( SetCursorFirstEntityByInteger( vTaskLPLR, "W_MetaType", "Type", nType, "" ) != zCURSOR_SET )
   {
      CreateEntity( vTaskLPLR, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vTaskLPLR, "W_MetaType", "Type", nType );
   }

   if ( nEntityType == CM_ACTIVE_TYPE )
   {
      strcpy_s( szWorkName, zsizeof( szWorkName ), SRC_CMOD[ nType ].szOD );
      strcpy_s( szOD_RootName, zsizeof( szOD_RootName ), SRC_CMOD[ nType ].szOD_ROOT );
      lControl = zLEVEL_APPLICATION;
//    lControl = zLEVEL_TASK;
   }
   else
   {
      strcpy_s( szWorkName, zsizeof( szWorkName ), REFER_CMOD[ nType - 2000 ].szOD );
      strcpy_s( szOD_RootName, zsizeof( szOD_RootName ), REFER_CMOD[ nType - 2000 ].szOD_ROOT );
      lControl = zLEVEL_APPLICATION;
   }
#if 0
   if ( nType == zSOURCE_DIALOG_META || nType == zREFER_DIALOG_META ||
     // nType == zSOURCE_DTE_META    || nType == zREFER_DTE_META ||
        nType == zSOURCE_UIS_META    || nType == zREFER_UIS_META )
#endif
   if ( ActivateEmptyObjectInstance( pvMOI, szWorkName,
                                     vTaskLPLR, lControl ) != 0 )
   {
      return( -1 );
   }

   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );

   // Get the view to the vTaskMetas subtask.
   fnGetTaskOI_ListName( vSubtask, szWorkName, zsizeof( szWorkName ) );
   GetViewByName( &vTaskMetas, szWorkName, vZeidonCM, zLEVEL_SUBTASK );

   // Get the view to the ActiveMeta OI.
   GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK );
   nRC = GetStringFromAttribute( szWorkName, zsizeof( szWorkName ), vTaskLPLR, "LPLR", "Name" );
   nRC = SetCursorFirstEntityByString( vActiveMetas, "LPLR", "Name",
                                                     szWorkName, "" );
   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaType", "Type",
                                       nType, "" ) != zCURSOR_SET )
   {
      CreateEntity( vActiveMetas, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vActiveMetas, "W_MetaType", "Type", nType );
   }

/* PETTIT Include the following code when ready
   nRC = CreateMetaEntity( vSubtask, *pvMOI, szOD_RootName, zPOS_AFTER );
   CreateEntity( vActiveMetas, "W_MetaDef", zPOS_AFTER );
   SetAttributeFromAttribute( vActiveMetas, "W_MetaDef", "CPLR_ZKey", *pvMOI, szOD_RootName, "ZKey" );
   GetStringFromAttribute( szWorkName, zsizeof( szWorkName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
   if ( nEntityType == CM_ACTIVE_TYPE )
   {
      SetAttributeFromInteger( vActiveMetas, "W_MetaDef", "TaskID", SysGetTaskFromView( vSubtask ) );
      sztrcat( szWorkName, ".u" );
   }
   else
      sztrcat( szWorkName, ".r" );

   nRC = SetNameForView( *pvMOI, szWorkName, vZeidonCM, zLEVEL_SUBTASK );
*/

   // Create a separate view for returning to the application
   CreateViewFromViewForTask( pvMOI, *pvMOI, vSubtask );
   ResetView( *pvMOI );
   if ( nEntityType == CM_ACTIVE_TYPE )
      szWorkName[ 0 ] = 'u';
   else
      szWorkName[ 0 ] = 'r';

   zltoa( *((zPLONG) pvMOI), szWorkName + 1, zsizeof( szWorkName ) - 1 );
   SetNameForView( *pvMOI, szWorkName, vTaskMetas, zLEVEL_SUBTASK | zNAME_AUTODROP );
   return( 1 );
}

//./ ADD NAME=DropMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: DropMetaOI
//
//  PURPOSE:    Drops the View to a Meta Object Instance
//
//  PARAMETERS: vMOI - the View to be dropped
//
//  RETURNS:    0 - View to Meta OI successfully dropped
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zOPER_EXPORT zSHORT OPERATION
DropMetaOI( zVIEW vSubtask, zVIEW vMOI )
{
   zVIEW  vZeidonCM;
   zVIEW  vActiveMetas;
   zVIEW  vTaskMetas;
   zVIEW  vTaskLPLR;
   zVIEW  RU_View;
   zLONG  lMOI_InstanceID;
   zCHAR  szLPLR_Name[ 33 ];
   zCHAR  szViewName[ 80 ];

   // Get the Instance Id of the meta to be dropped.
   lMOI_InstanceID = MiGetInstanceID_ForView( vMOI );

   // Get the view to ZedionCM OI.
   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );

   // Get the view to the vTaskMetas subtask.
   fnGetTaskOI_ListName( vSubtask, szViewName, zsizeof( szViewName ) );
   GetViewByName( &vTaskMetas, szViewName, vZeidonCM, zLEVEL_SUBTASK );
   zltoa( (zLONG) vMOI, szViewName + 1, zsizeof( szViewName ) - 1 );
   szViewName[ 0 ] = 'r';
   if ( GetViewByName( &RU_View, szViewName, vTaskMetas, zLEVEL_SUBTASK ) > 0 )
   {
      DropView( vMOI );
      return( 0 );
   }

   szViewName[ 0 ] = 'u';
   if ( GetViewByName( &RU_View, szViewName, vTaskMetas, zLEVEL_SUBTASK ) < 0 )  // not an Update View
   {
      return( -1 );
   }

   // OK, so the View is to an Update (SOURCE) Meta. I need to check the
   // OpenCM_Metas for a match on TaskID. If there is a match and the
   // CM_ViewName.u InstanceID matches our InstanceID, drop the Object
   // Instance, remove the TaskID, then check for a CM_ViewName.r and if
   // there isn't one exclude the W_MetaDef.

   // Get the view to the ActiveMeta OI.
   GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK );

   // I need the view to the TaskLPLR to get the name of the root LPLR
   // in the ActiveMeta OI.
   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vTaskLPLR, "LPLR", "Name" );
   SetCursorFirstEntityByString( vActiveMetas, "LPLR", "Name", szLPLR_Name, "" );
   if ( fnCheckCM_ForActiveMetaByTask( vSubtask, lMOI_InstanceID ) == 1 )
   {
      // Found!
      SetAttributeFromInteger( vActiveMetas, "W_MetaDef", "TaskID", 0 );
      DropObjectInstance( vMOI );
      GetStringFromAttribute( szViewName, zsizeof( szViewName ), vActiveMetas, "W_MetaDef", "CM_ViewName" );
      strcat_s( szViewName, zsizeof( szViewName ), ".r" );
      if ( GetViewByName( &RU_View, szViewName, vZeidonCM, zLEVEL_SUBTASK ) < 0 )
      {
         ExcludeEntity( vActiveMetas, "W_MetaDef", zREPOS_NONE );
      }

      return( 0 );
   }

   // The Meta wasn't found in CM so Drop the OI - Could be a new?
   DropObjectInstance( vMOI );
   return( 0 );
}

//./ ADD NAME=DeleteMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: DeleteMetaOI
//
//  PURPOSE:    Deletes a Meta Object Instance (portable file)
//
//  PARAMETERS: vListView - a valid LPL list view
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//
//  RETURNS:    0 - Meta OI successfully deleted
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zOPER_EXPORT zSHORT OPERATION
DeleteMetaOI( zVIEW  vSubtask,
              zVIEW  vListView,
              zSHORT nType )
{
   zSHORT nEntityType;
   zSHORT nWorkType;
   zSHORT nReferOI_Active = 0;
   zSHORT nReferViewsActive;
   zLONG  lTaskID;
   zLONG  lMOI_InstanceID;
   zLONG  lMetaOI_ZKey;
   zVIEW  vTaskLPLR;
   zVIEW  vMeta;
   zVIEW  vLPLR;
   zVIEW  vLPLR2;
   zVIEW  vZeidonCM;
   zVIEW  vActiveMetas;
   zVIEW  vActiveList;
   zVIEW  vWork1;
   zVIEW  vWork2;
   zVIEW  CM_View;
   zVIEW  vVOR;
   zVIEW  vVOR_LPLR;
   zCHAR  szMetaOI_Name[ 33 ];
   zCHAR  szEntityName[ 33 ];
   zCHAR  szCM_ViewName[ 80 ];
   zCHAR  szNamedView[ 80 ];
   zCHAR  szTaskView[ 80 ];
   zCHAR  szFileSpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szErrMsg[ zLONG_MESSAGE_LTH + 1 ];
   zSHORT nRC, nRC2;

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vLPLR, vTaskLPLR, vSubtask );

   if ( GetViewByName( &vZeidonCM, "ZeidonCM",
                       vSubtask, zLEVEL_APPLICATION ) <= 0 )
   {
      MessageSend( vSubtask, "CM00448", "Configuration Management",
                   "Unable to locate ZeidonCM in DeleteMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( GetViewByName( &vActiveMetas, "OpenCM_Metas",
                       vZeidonCM, zLEVEL_SUBTASK ) <= 0 )
   {
      MessageSend( vSubtask, "CM00449", "Configuration Management",
                   "Unable to locate OpenCM_Metas in DeleteMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   CreateViewFromViewForTask( &vActiveList, vActiveMetas, vSubtask );

   if ( nEntityType == CM_ACTIVE_TYPE )
      nWorkType = nType;
   else
      nWorkType = nType - 2000;

   GetIntegerFromAttribute( &lMetaOI_ZKey, vListView, "W_MetaDef", "CPLR_ZKey" );
   GetStringFromAttribute( szMetaOI_Name, zsizeof( szMetaOI_Name ), vListView, "W_MetaDef", "Name" );
   nRC = SetCursorFirstEntityByInteger( vLPLR, "W_MetaDef",
                                        "CPLR_ZKey", lMetaOI_ZKey, "LPLR" );
   if ( nRC < zCURSOR_SET )
   {
      strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Component to be Deleted not found in the LPLR." );
      MessageSend( vSubtask, "CM00450", "Configuration Management",
                   szErrMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( CompareAttributeToInteger( vLPLR, "W_MetaType", "Type", nWorkType ) != 0 )
   {
      strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Component to be Deleted not active in the LPLR." );
      MessageSend( vSubtask, "CM00451", "Configuration Management",
                   szErrMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( CompareAttributeToString( vLPLR, "W_MetaDef", "Name", szMetaOI_Name ) != 0 )
   {
      strcpy_s( szErrMsg, zsizeof( szErrMsg ),
               "Component to be Deleted found in the LPLR under a different name" );
      MessageSend( vSubtask, "CM00452", "Configuration Management",
                   szErrMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   nRC = SetCursorFirstEntityByEntityCsr( vActiveList, "W_MetaDef",
                                          vLPLR, "W_MetaDef", "LPLR" );
   if ( nRC >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lTaskID, vActiveList, "W_MetaDef", "TaskID" );
      if ( lTaskID )
      {
         GetStringFromAttribute( szCM_ViewName, zsizeof( szCM_ViewName ), vActiveList,
                                 "W_MetaDef", "CM_ViewName" );
         strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".u" );
         if ( GetViewByName( &CM_View, szCM_ViewName,
                             vZeidonCM, zLEVEL_SUBTASK ) > 0 )
         {
            strcpy_s( szErrMsg, zsizeof( szErrMsg ),
                     "Component to be Deleted is currently opened for update." );
            MessageSend( vSubtask, "CM00453", "Configuration Management",
                         szErrMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }
      }
   }

   if ( nRC >= zCURSOR_SET )
   {
      GetStringFromAttribute( szCM_ViewName, zsizeof( szCM_ViewName ), vActiveList,
                              "W_MetaDef", "CM_ViewName" );
      strcat_s( szCM_ViewName, zsizeof( szCM_ViewName ), ".r" );
      nReferOI_Active = 0;
      if ( GetViewByName( &CM_View, szCM_ViewName,
                          vZeidonCM, zLEVEL_SUBTASK ) > 0 )
      {
         // REFER OI of Meta exists - Check if there are Views to it
         nReferOI_Active = 1;
         nReferViewsActive = 0;
         lMOI_InstanceID = MiGetInstanceID_ForView( CM_View );
         nRC = SfGetFirstNamedView( &vWork1, szNamedView, vZeidonCM,
                                    zLEVEL_SUBTASK );
         while ( nRC > 0 )
         {
            if ( zstrncmp( szNamedView, "__CM.", 5 ) == 0 )
            {
               nRC = SfGetFirstNamedView( &vWork2, szTaskView,
                                          vWork1, zLEVEL_SUBTASK );
               while ( nRC > 0 )
               {
                  if ( zstrncmp( szTaskView, "r", 1 ) == 0 )
                  {
                     if ( MiGetInstanceID_ForView( vWork2 ) == lMOI_InstanceID )
                     {
                        nReferViewsActive = 1;
                        break;
                     }
                  }

                  nRC = SfGetNextNamedView( &vWork2, szTaskView,
                                            vWork1, zLEVEL_SUBTASK );
               }
            }

            if ( nReferViewsActive == 1 )
            {
               strcpy_s( szErrMsg, zsizeof( szErrMsg ),
                        "The Meta you are trying to delete,\n" );
               GetStringFromAttribute( szErrMsg + zstrlen( szErrMsg ), zsizeof( szErrMsg ) - zstrlen( szErrMsg ),
                                       vActiveMetas, "W_MetaDef", "Name" );
               strcat_s( szErrMsg, zsizeof( szErrMsg ), ", Type " );
               GetVariableFromAttribute( szErrMsg + zstrlen( szErrMsg ),
                                         0, zTYPE_STRING, 125, vActiveMetas,
                                         "W_MetaType", "Type", "CM_Type", 0 );
               strcat_s( szErrMsg, zsizeof( szErrMsg ),
                  ",\nis being referenced by a Zeidon Tool.\n"
                  "To delete this meta close the other Zeidon Tool.\n" );
               MessageSend( vSubtask, "CM00454", "Configuration Management",
                            szErrMsg,
                            zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               return( 0 );
            }

            nRC = SfGetNextNamedView( &vWork1, szNamedView,
                                      vZeidonCM, zLEVEL_SUBTASK );
         }
      }
   }

   if ( nReferOI_Active && nReferViewsActive == 0 )
      DropObjectInstance( CM_View );
   else
   if ( nReferOI_Active )
      DropView( CM_View );

   // Determine fully contatenated file name for delete.
   nRC = fnGetDirectorySpec( vListView, szFileSpec, zsizeof( szFileSpec ), nType, TRUE );
   if ( nWorkType == zSOURCE_VOR_META )
   {
      zltoxa( lMetaOI_ZKey, szMetaOI_Name );
   }
   strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_Name );
   strcat_s( szFileSpec, zsizeof( szFileSpec ), SRC_CMOD[ nWorkType ].szOD_EXT );

   nRC = ActivateMetaOI_ByZKey( vSubtask, &vMeta, vListView, nWorkType,
                                zSINGLE | zLEVEL_APPLICATION,
                                lMetaOI_ZKey, zCURRENT_OI );
   if ( nRC < 0 )
   {
      strcpy_s( szErrMsg, zsizeof( szErrMsg ),
               "Removing meta without deleting file." );
      MessageSend( vSubtask, "CM00455", "Configuration Management",
                   szErrMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      DeleteEntity( vLPLR, "W_MetaDef", zREPOS_NONE );
      return( -1 );
   }

   if ( CheckExistenceOfEntity( vMeta, "Z_MetaDef" ) >= zCURSOR_SET )
   {
      if ( CompareAttributeToInteger( vLPLR, "W_MetaDef",
                                      "UpdateInd", 3 ) == 0 )
      {
         strcpy_s( szErrMsg, zsizeof( szErrMsg ),
                  "Component to be Deleted has already been deleted." );
         MessageSend( vSubtask, "CM00456", "Configuration Management",
                      szErrMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( -1 );
      }
      nRC = SetCursorFirstEntityByInteger( vLPLR, "W_MetaType",
                                          "Type", nWorkType, "" );
      nRC = SetCursorFirstEntityByInteger( vLPLR, "W_MetaDef",
                                           "CPLR_ZKey", lMetaOI_ZKey, "" );
      SetAttributeFromInteger( vLPLR, "W_MetaDef", "UpdateInd", 3 );
      SetAttributeFromString( vLPLR, "W_MetaDef", "Desc", "*** Deleted ***" );
      nRC = SetCursorFirstEntityByInteger( vLPLR, "W_MetaType",
                                          "Type", nWorkType + 2000, "" );
      nRC = SetCursorFirstEntityByInteger( vLPLR, "W_MetaDef",
                                           "CPLR_ZKey", lMetaOI_ZKey, "" );
      nRC2 = SetCursorFirstEntityByEntityCsr( vActiveList, "W_MetaDef",
                                              vLPLR, "W_MetaDef",
                                              "LPLR" );
      if ( nRC2 >= zCURSOR_SET )
      {
         ExcludeEntity( vActiveList, "W_MetaDef", zREPOS_NONE );
      }

      if ( nRC >= zCURSOR_SET )
      {
         ExcludeEntity( vLPLR, "W_MetaDef", zREPOS_NONE );
      }
   }
   else
   {
      if ( SysOpenFile( vLPLR, szFileSpec, COREFILE_DELETE ) < 0 )
      {
         strcpy_s( szErrMsg, zsizeof( szErrMsg ), "File " );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), szFileSpec );
         strcat_s( szErrMsg, zsizeof( szErrMsg ), "\nNot found - deleting entry from CM List" );
         MessageSend( vSubtask, "CM00457", "Configuration Management",
                      szErrMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }

      nRC = SetCursorFirstEntityByEntityCsr( vActiveList, "W_MetaDef",
                                             vLPLR, "W_MetaDef", "LPLR" );
      if ( nRC >= zCURSOR_SET )
      {
         nRC = ExcludeEntity( vActiveList, "W_MetaDef", zREPOS_NONE );
      }

      nRC = DeleteEntity( vLPLR, "W_MetaDef", zREPOS_PREV );
      if ( nWorkType == zSOURCE_DIALOG_META || nWorkType == zSOURCE_LOD_META )
      {
         GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vLPLR, "LPLR", "ExecDir" );
         ofnTZCMWKSO_AppendSlash( szFileSpec );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_Name );
         if ( nWorkType == zSOURCE_DIALOG_META )
            strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XWD" );
         else
         {
            strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XOD" );
            // For LOD, also delete all the related VORs.  This has to be
            // done by activating every VOR to see if it is for the deleted LOD.
            RetrieveViewForMetaList( vSubtask, &vVOR_LPLR, zSOURCE_VOR_META );
            nRC = SetCursorFirstEntity( vVOR_LPLR, "W_MetaDef", 0 );
            while ( nRC >= zCURSOR_SET )
            {
               nRC = ActivateMetaOI( vSubtask, &vVOR, vVOR_LPLR, zSOURCE_VOR_META,
                                     zSINGLE | zLEVEL_APPLICATION );
               if ( nRC >= 0 )
               {
                  if ( CompareAttributeToString( vVOR, "LOD", "Name",
                                                 szMetaOI_Name ) == 0 )
                  {
                     DropMetaOI( vSubtask, vVOR );
                     nRC = DeleteMetaOI( vSubtask, vVOR_LPLR, zSOURCE_VOR_META );
                     if ( nRC >= 0 )
                        SetCursorPrevEntity( vVOR_LPLR, "W_MetaDef", 0 );
                     nRC = CheckExistenceOfEntity( vVOR_LPLR, "W_MetaDef" );
                  }
                  else
                  {
                     DropMetaOI( vSubtask, vVOR );
                     nRC = SetCursorNextEntity( vVOR_LPLR, "W_MetaDef", 0 );
                  }
               }
               else
                  nRC = SetCursorNextEntity( vVOR_LPLR, "W_MetaDef", 0 );
            }
         }

         if ( SysOpenFile( vVOR_LPLR, szFileSpec, COREFILE_DELETE ) < 0 )
         {
            strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Corresponding Executable File " );
            strcat_s( szErrMsg, zsizeof( szErrMsg ), szFileSpec );
            strcat_s( szErrMsg, zsizeof( szErrMsg ), " Not found." );
            MessageSend( vSubtask, "CM00458", "Configuration Management",
                         szErrMsg,
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         }
      }

      // if this is a Report we have to delete file XRP and for SironReports
      // files REP and XSQ too.
      if ( nWorkType == zSOURCE_REPORT_META || nWorkType == zREFER_REPORT_META ||
           nWorkType == zSOURCE_XSLT_META || nWorkType == zREFER_XSLT_META )
      {
         zCHAR szReportFile[ zMAX_FILESPEC_LTH + 1 ];
         GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vLPLR, "LPLR", "ExecDir" );
         ofnTZCMWKSO_AppendSlash( szFileSpec );
         strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_Name );
         strcpy_s( szReportFile, zsizeof( szReportFile ), szFileSpec ); // Save the name without extension
                                                  // because we have to delete XSQ too
                                                  // for  SironReports
         if ( nWorkType == zSOURCE_REPORT_META || nWorkType == zREFER_REPORT_META )
            strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XRP" );
         else
            strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XSL" );

         if ( SysOpenFile( vLPLR, szFileSpec, COREFILE_DELETE ) < 0 )
         {
            strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Corresponding Executable File " );
            strcat_s( szErrMsg, zsizeof( szErrMsg ), szFileSpec );
            strcat_s( szErrMsg, zsizeof( szErrMsg ), " Not found." );
            MessageSend( vSubtask, "CM00458", "Configuration Management",
                         szErrMsg,
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         }

         if ( nWorkType == zSOURCE_REPORT_META || nWorkType == zREFER_REPORT_META )
         {
             // Try to delete the XSQ file
             strcpy_s( szFileSpec, zsizeof( szFileSpec ), szReportFile );
             strcat_s( szFileSpec, zsizeof( szFileSpec ), ".XSQ" );
             SysOpenFile( vLPLR, szFileSpec,
                     COREFILE_DELETE ); // We don't test the Returncode of
                                             // SysOpenFile, because we get an error
                                             // if the report is a zeidon report.
             // Try to delete the REP file
             // We first get the directory where we'll find the REP file if it exists
             GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vLPLR, "LPLR", "PgmSrcDir" );
             ofnTZCMWKSO_AppendSlash( szFileSpec );
             strcat_s( szFileSpec, zsizeof( szFileSpec ), szMetaOI_Name );
             strcat_s( szFileSpec, zsizeof( szFileSpec ), ".REP" );
             SysOpenFile( vLPLR, szFileSpec,
                     COREFILE_DELETE ); // We don't test the Returncode of
                                             // SysOpenFile, because we get an error
                                             // if the report is a zeidon report.
         }
      }
   }

   // If this is a Domain Group, remove all the subordinate Domain entries
   // from the LPLR list.
   if ( nWorkType == zSOURCE_DOMAINGRP_META )
   {
      CreateViewFromViewForTask( &vLPLR2, vLPLR, vSubtask );
      SetCursorFirstEntityByInteger( vLPLR2, "W_MetaType", "Type",
                                     zSOURCE_DOMAIN_META, "" );
      nRC = SetCursorFirstEntity( vLPLR2, "W_MetaDef", "" );
      while ( nRC >= zCURSOR_SET )
      {
         if ( CompareAttributeToAttribute( vLPLR2, "W_MetaDef", "GroupName",
                                           vMeta, "DomainGroup", "Name" ) == 0 )
         {
            DeleteEntity( vLPLR2, "W_MetaDef", zREPOS_NONE );
         }

         nRC = SetCursorNextEntity( vLPLR2, "W_MetaDef", "" );
      }
      SetCursorFirstEntityByInteger( vLPLR2, "W_MetaType", "Type",
                                     zREFER_DOMAIN_META, "" );
      nRC = SetCursorFirstEntity( vLPLR2, "W_MetaDef", "" );
      while ( nRC >= zCURSOR_SET )
      {
         if ( CompareAttributeToAttribute( vLPLR2, "W_MetaDef", "GroupName",
                                           vMeta, "DomainGroup", "Name" ) == 0 )
         {
            DeleteEntity( vLPLR2, "W_MetaDef", zREPOS_NONE );
         }

         nRC = SetCursorNextEntity( vLPLR2, "W_MetaDef", "" );
      }

      DropView( vLPLR2 );
   }

   // If this is an Operation Group, remove all the subordinate Operation
   // entries from the LPLR list.
   if ( nWorkType == zSOURCE_GOPGRP_META )
   {
      CreateViewFromViewForTask( &vLPLR2, vLPLR, vSubtask );
      SetCursorFirstEntityByInteger( vLPLR2, "W_MetaType", "Type",
                                     zSOURCE_GO_META, "" );
      nRC = SetCursorFirstEntity( vLPLR2, "W_MetaDef", "" );
      while ( nRC >= zCURSOR_SET )
      {
         if ( CompareAttributeToAttribute( vLPLR2, "W_MetaDef", "GroupName",
                                           vMeta, "GlobalOperationGroup", "Name" ) == 0 )
         {
            DeleteEntity( vLPLR2, "W_MetaDef", zREPOS_NONE );
         }

         nRC = SetCursorNextEntity( vLPLR2, "W_MetaDef", "" );
      }

      SetCursorFirstEntityByInteger( vLPLR2, "W_MetaType", "Type",
                                     zREFER_GO_META, "" );
      nRC = SetCursorFirstEntity( vLPLR2, "W_MetaDef", "" );
      while ( nRC >= zCURSOR_SET )
      {
         if ( CompareAttributeToAttribute( vLPLR2, "W_MetaDef", "GroupName",
                                           vMeta, "GlobalOperationGroup", "Name" ) == 0 )
         {
            DeleteEntity( vLPLR2, "W_MetaDef", zREPOS_NONE );
         }

         nRC = SetCursorNextEntity( vLPLR2, "W_MetaDef", "" );
      }

      DropView( vLPLR2 );
   }

   if ( CheckExistenceOfEntity( vMeta, "Z_MetaDef" ) >= zCURSOR_SET )
   {
      strcpy_s( szEntityName, zsizeof( szEntityName ), SRC_CMOD[ nWorkType ].szOD_ROOT );
      DeleteEntity( vMeta, szEntityName, zREPOS_NONE );
      CommitOI_ToFile( vMeta, szFileSpec, zASCII | zINCREMENTAL );
   }

   DropObjectInstance( vMeta );

   if ( oTZCMLPLO_CommitLPLR( vLPLR ) == 0 )
   {
      DropView( vLPLR );
      return( 0 );
   }

   DropView( vLPLR );
   return( -1 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    CreatePE_ExecVersion
//
// PURPOSE:  Create the executable version of the Presentation
//           Environment instance (ZEIDON.XPE).
//
/////////////////////////////////////////////////////////////////////////////
zVIEW OPERATION
CreatePE_ExecVersion( zVIEW vSubtask, zVIEW vPresEnv )
{
   zVIEW  vPresEnvX;
   zVIEW  vTmpExe;
   zLONG  lRel;
 //zLONG  lLoop;
 //zLONG  lFontCount;
   zCHAR  szWorkString[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szGUID[ 80 ];
   zLONG  lIdNbr;
   zPCHAR pch;
   zSHORT nRC;

   TraceLineS( "CreatePE_ExecVersion", "================================" );

   GetStringFromAttribute( szWorkString, zsizeof( szWorkString ), vSubtask, "LPLR", "ExecDir" );
   ofnTZCMWKSO_AppendSlash( szWorkString );
   strcat_s( szWorkString, zsizeof( szWorkString ), "ZEIDON.XPE" );

   //BL, 2000.01.30 XPE does not exists, then no error message
   if ( SfActivateSysOI_FromFile( &vTmpExe,
                                  "KZPEXVOO", vSubtask,
                                  szWorkString, zSINGLE | zNOI_OKAY ) >= 0 )
   {
      GetIntegerFromAttribute( &lRel, vTmpExe, "PE", "Rel" );
   }

   ActivateEmptyObjectInstance( &vPresEnvX, "KZPEXVOO", vSubtask, zSINGLE );
   CreateEntity( vPresEnvX, "PE", zPOS_AFTER );
   SetAttributeFromInteger( vPresEnvX, "PE", "Rel", lRel );

   ResetView( vPresEnv );

   nRC = SetCursorFirstEntity( vPresEnv, "EventDef", "" );
   while ( nRC >= zCURSOR_SET )
   {
      GetAddrForAttribute( &pch, vPresEnv, "EventDef", "RegWEB" );
      if ( *pch == 'Y' || *pch == 'y' )
      {
         CreateEntity( vPresEnvX, "WndEvent", zPOS_AFTER );
         SetAttributeFromAttribute( vPresEnvX, "WndEvent", "Type",
                                    vPresEnv, "EventDef", "Type" );
      }

      nRC = SetCursorNextEntity( vPresEnv, "EventDef", "" );
   }

   nRC = SetCursorFirstEntity( vPresEnv, "ControlDef", "" );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      GetIntegerFromAttribute( &lIdNbr, vPresEnv, "ControlDef", "Id" );
      GetStringFromAttribute( szWorkString, zsizeof( szWorkString ), vPresEnv,
                              "ControlDef", "RT_OperationName" );
      GetStringFromAttribute( szGUID, zsizeof( szGUID ), vPresEnv,
                              "ControlDef", "GUID" );

      // Don't put any control in the XPE that doesn't have both an Id Number
      // and a Runtime Operation Name.
      if ( (lIdNbr == 0 && szGUID[ 0 ] == 0) || szWorkString[ 0 ] == 0 )
      {
         GetIntegerFromAttribute( &lIdNbr, vPresEnv, "ControlDef", "Key" );
         TraceLineI( "Skipping ControlDef Id = ", lIdNbr );
      }
      else
      {
         CreateEntity( vPresEnvX, "Ctrl", zPOS_AFTER );

         // This is the result of an early design mistake that would be
         // very hard to overturn at this point in time.  The Key of the
         // ControlDef entity is not really a ZKey.  It is a Key (must
         // be unique) and should NOT be migrated.
         SetAttributeFromAttribute( vPresEnvX, "Ctrl", "Key",
                                    vPresEnv, "ControlDef", "Key" );

//       SetAttributeFromAttribute( vPresEnvX, "Ctrl", "Tag",
//                                  vPresEnv, "ControlDef", "Tag" );
         SetAttributeFromAttribute( vPresEnvX, "Ctrl", "DLL",
                                    vPresEnv, "ControlDef", "RT_DLL_Name" );
         SetAttributeFromString( vPresEnvX, "Ctrl", "COP", szWorkString );

//       SetAttributeFromAttribute( vPresEnvX, "Ctrl", "TagPE",
//                                  vPresEnv, "ControlDef", "Tag" );
//       SetAttributeFromString( vPresEnvX, "Ctrl", "GUID", szGUID );
//       SetAttributeFromAttribute( vPresEnvX, "Ctrl", "Script",
//                                  vPresEnv, "ControlDef",
//                                  "ActiveX_Script" );
//       SetAttributeFromAttribute( vPresEnvX, "Ctrl", "ScriptDLL",
//                                  vPresEnv, "ControlDef",
//                                  "ActiveX_ScriptDLL" );
      }

      nRC = SetCursorFirstEntity( vPresEnv, "CtrlEventDef", "" );
      while ( nRC >= zCURSOR_SET )
      {
         GetAddrForAttribute( &pch, vPresEnv, "CtrlEventDef", "RegWEB" );
         if ( *pch == 'Y' || *pch == 'y' )
         {
            CreateEntity( vPresEnvX, "CtrlEvent", zPOS_AFTER );
            SetAttributeFromAttribute( vPresEnvX, "CtrlEvent", "Type",
                                       vPresEnv, "CtrlEventDef", "Type" );
         }

         nRC = SetCursorNextEntity( vPresEnv, "CtrlEventDef", "" );
      }

      nRC = SetCursorNextEntity( vPresEnv, "ControlDef", "" );
   }
#if 0
   lFontCount = 0;
   nRC = SetCursorFirstEntity( vPresEnv, "Font", "" );
   while ( nRC > zCURSOR_UNCHANGED )
   {
      lFontCount++;
      nRC = SetCursorNextEntity( vPresEnv, "Font", "" );
   }

   lLoop = 0;
   while ( lLoop < lFontCount )
   {
      SetCursorFirstEntityByInteger( vPresEnv, "Font", "Id", lLoop, "" );
      CreateEntity( vPresEnvX, "Font", zPOS_AFTER );
      /*
      SetAttributeFromAttribute( vPresEnvX, "Font", "Id",
                                 vPresEnv, "Font", "Id" );
      */
//      SetAttributeFromAttribute( vPresEnvX, "Font", "Struct",
      SetAttributeFromAttribute( vPresEnvX, "Font", "LFont",
                                 vPresEnv, "Font", "WindowsStructure" );
      SetAttributeFromAttribute( vPresEnvX, "Font", "RGB",
                                 vPresEnv, "Font", "RGB_Color" );
      SetAttributeFromAttribute( vPresEnvX, "Font", "Size",
                                 vPresEnv, "Font", "PointSize" );

      lLoop++;
   }
#endif
   ResetView( vPresEnv );
   return( vPresEnvX );
}

//./ ADD NAME=CheckExistenceOfMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: CheckExistenceOfMetaOI
//
//  PURPOSE:    Determines if a Zeidon Meta OI exists
//
//  PARAMETERS: szMetaName - the name of the OI to search for
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//
//  RETURNS:    1 - Meta OI exists
//              0 - Meta OI not found
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zOPER_EXPORT zSHORT OPERATION
CheckExistenceOfMetaOI( zVIEW  vSubtask,
                        zPCHAR szMetaName,
                        zSHORT nType )
{
   zSHORT nEntityType;
   zVIEW  vTaskLPLR;

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if ( SetCursorFirstEntityByInteger( vTaskLPLR, "W_MetaType",
                                          "Type", nType, "" ) == zCURSOR_SET )
      {
         if ( SetCursorFirstEntityByString( vTaskLPLR, "W_MetaDef",
                                             "Name", szMetaName,
                                             "" ) == zCURSOR_SET &&
              CompareAttributeToInteger( vTaskLPLR, "W_MetaDef",
                                         "UpdateInd", 3 ) != 0 )
         {
            return( 1 );
         }
         else
            return( 0 );
      }
      else
         return( 0 );
   }

   return( -1 );

} // CheckExistenceOfMetaOI

//./ ADD NAME=CheckExistenceOfMetaOI_ByZKey
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: CheckExistenceOfMetaOI_ByZKey
//
//  PURPOSE:    Searches the LPLR for a meta matching the ZKey and LPLR
//              type passed.
//
//  PARAMETERS: ZKey - ZKey to the Meta be searched for
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//
//  RETURNS:    1 - Matching meta found
//              0 - No matching meta found
//             -1 - Error encountered, type invalid or LPLR not initialized
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zOPER_EXPORT zSHORT OPERATION
CheckExistenceOfMetaOI_ByZKey( zVIEW  vSubtask,
                               zULONG ulZKey,
                               zSHORT nType )
{
   zVIEW  vTaskLPLR;
   zSHORT nEntityType;

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if ( SetCursorFirstEntityByInteger( vTaskLPLR, "W_MetaType",
                                          "Type", nType, "" ) == zCURSOR_SET )
      {
         if ( SetCursorFirstEntityByInteger( vTaskLPLR, "W_MetaDef",
                                             "CPLR_ZKey", ulZKey,
                                             "" ) == zCURSOR_SET &&
              CompareAttributeToInteger( vTaskLPLR, "W_MetaDef",
                                         "UpdateInd", 3 ) != 0 )
         {
            return( 1 );
         }
         else
         {
            return( 0 );
         }
      }
   }

   return( -1 );
}

//./ ADD NAME=CreateTE_MetaEntity
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: CreateTE_MetaEntity
//
//  PURPOSE:    Creates a Zeidon Meta Entity for a TE meta entity and sets the ZKey attribute
//              from the MaxZKey attribute found in the WorkStation
//              Object
//
//  PARAMETERS: lpView - the meta object view to create the entity for
//              szEntityName - the Zeidon meta entity name
//              nPosition - integer indicating BEFORE or AFTER
//
//  RETURNS:    0 - Meta entity created
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zOPER_EXPORT zSHORT OPERATION
CreateTE_MetaEntity( zVIEW  vSubtask,
                  zVIEW  lpView,
                  zPCHAR szEntityName,
                  zSHORT nPosition )
{
   zVIEW   WKS_View;
   zVIEW   vZeidonCM;
   zULONG  ulMaxZKey;

   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask,  zLEVEL_APPLICATION );
   GetViewByName( &WKS_View, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );
   if ( WKS_View == 0 )  // View isn't there
   {
      MessageSend( lpView, "CM00459", "Configuration Management",
                   "The RepositoryClient View ID was not found",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Retrieve the TE MaxZkey, which has the last ZKey value generated for a meta entity in the TE, and increment it.
   GetIntegerFromAttribute( (zPLONG) &ulMaxZKey, WKS_View,
                            "RepositoryClient", "TE_MaxZKey" );
   ulMaxZKey++;

   // Create the Meta Entity and set the ZKey just incremented.
   if ( CreateEntity( lpView, szEntityName, nPosition ) < 0 )
      return( -1 );
   if ( SetAttributeFromInteger( lpView, szEntityName,
                                 "ZKey", ulMaxZKey ) != 0 )
   {
      DeleteEntity( lpView, szEntityName, zREPOS_NONE );
      MessageSend( lpView, "CM00461", "Configuration Management",
                   "Unable to set MaxZKey in operation CreateTE_MetaEntity",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Store the Max ZKey value just generated.
   SetAttributeFromInteger( WKS_View, "RepositoryClient",
                            "TE_MaxZKey", ulMaxZKey );
   return( 0 );
}

// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: InitializeNextZKeyForObject
//
//  PURPOSE:    Searches the object for the maximum ZKey value and sets the NextZKeyToAssign attribute
//              to that value + 1.
//
//  PARAMETERS: lpView - the meta object view
//
//  RETURNS:    0, unless there is an error.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zOPER_EXPORT zSHORT OPERATION
InitializeNextZKeyForObject( zVIEW  vMetaRootView,
                             zPCHAR szRootEntityName,
                             zPCHAR szEntityName )
{

   zVIEW     vHierMetaOI = 0;
   zCHAR     szMsg[ 501 ] = { 0 };
   zCHAR     szDateTimeStamp[ 51 ] = { 0 };
   zCHAR     szGeneratedKey[ 21 ] = { 0 };
   zCHAR     szCurrentEntityName[ 33 ];
   zLONG     lZKey = 0;
   zLONG     lMaxZKey = 0;
   zSHORT    nHierRC = 0;
   zSHORT    nReturnLevel = 0;

   // Initialize the NextZKeyToAssign value in the object, which is done in two different ways.
   // 1. If the entity being created in CreateMetaEntity is the root entity, then we will use the
   //    date/time stamp as a random number generator.
   // 2. Otherwise, we will set NextZKeyToAssign to one more than the highest ZKey in the object.

   if ( ZeidonStringCompare( szRootEntityName, 1, 0, szEntityName, 1, 0, 33 ) != 0 )
   {
      // Option 1:
      // Initialize the Next ZKey to Assign value for the meta object to one more than the highest ZKey
      // Value in the object.
      // Process each entity hierarchically, looking for highest ZKey value.
      CreateViewFromView( &vHierMetaOI, vMetaRootView );
      DefineHierarchicalCursor( vHierMetaOI, szRootEntityName );
      ZeidonStringCopy( szCurrentEntityName, 1, 0, szRootEntityName, 1, 0, 33 );

      GetIntegerFromAttribute( &lMaxZKey, vHierMetaOI, szCurrentEntityName, "ZKey" );
      nHierRC = zCURSOR_SET;
      while ( nHierRC >= zCURSOR_SET )
      {
         nHierRC = SetCursorNextEntityHierarchical( (zPUSHORT) &nReturnLevel, szCurrentEntityName, vHierMetaOI );
         if ( nHierRC >= zCURSOR_SET )
         {

            // Check ZKey in current entity against current Max ZKey.
            // But first make sure attribute ZKey exists in the Entity.
            if ( zLodContainsAttribute( vHierMetaOI, szCurrentEntityName, "ZKey" ) >= 0 )
            {
               GetIntegerFromAttribute( &lZKey, vHierMetaOI, szCurrentEntityName, "ZKey" );
               if ( lZKey > lMaxZKey )
               {
                  lMaxZKey = lZKey;
               }
            }

            // For recursive subentity, step down a level.
            if ( nHierRC == zCURSOR_SET_RECURSIVECHILD )
            {
               SetViewToSubobject( vHierMetaOI, szCurrentEntityName );
            }
         }
      }

      lMaxZKey = lMaxZKey + 1;

      DropView( vHierMetaOI );
   }
   else
   {
      // Option 2:
      // This is the Root of the object, so we will use the date/time stamp as a random number generator
      // for generating the ZKey of the root entity and set the NextZKeyToAssign to 1000.
      // DateTimeStamp is of form YYYYMMDDHHMMSSTTT.
      // We will use 9 middle digits, DDHHMMSST, forming DDH,HMM,SST, which would generate a key up to 312,459,599.
      SysGetDateTime( szDateTimeStamp, zsizeof( szDateTimeStamp ) );
      ZeidonStringCopy( szGeneratedKey, 1, 0, szDateTimeStamp, 6, 9, 21 );
      lMaxZKey = zStringToInteger( szGeneratedKey );
   }

   // Set the NextZKeyToAssign attribute
   SetAttributeFromInteger( vMetaRootView, szRootEntityName, "NextZKeyToAssign", lMaxZKey );

   return( 0 );
}

//./ ADD NAME=CreateMetaEntity
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: CreateMetaEntity
//
//  PURPOSE:    Creates a Zeidon Meta Entity and sets the ZKey attribute
//              from the MaxZKey attribute found in the WorkStation
//              Object
//
//  PARAMETERS: lpView - the meta object view to create the entity for
//              szEntityName - the Zeidon meta entity name
//              nPosition - integer indicating BEFORE or AFTER
//
//  RETURNS:    0 - Meta entity created
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zOPER_EXPORT zSHORT OPERATION
fnCreateMetaEntity( zVIEW  vSubtask,
                    zVIEW  lpView,
                    zPCHAR szEntityName,
                    zSHORT nPosition,
                    zSHORT nType )
{
   zVIEW  lpRootView;
   zVIEW   WKS_View;
   zVIEW   vZeidonCM;
   zULONG  ulMaxZKey;
   zLONG   lGenKeyStart = 0;
   zSHORT  nRC;
   zCHAR   szMsg[ 300 ] = { 0 };
   zCHAR   szObjectName[ 33 ];
   zCHAR   szRootEntityName[ 33 ];

   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask,  zLEVEL_APPLICATION );
   GetViewByName( &WKS_View, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );

   if ( WKS_View == 0 )  // View isn't there
   {
      MessageSend( lpView, "CM00459", "Configuration Management",
                   "The RepositoryClient View ID was not found. We should no longer get this call Don C.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // ZKey generation was modified by DonC on 10/26/2015.

   // Determine Root Entity Name for meta object for use in processing the ZKey.
   MiGetObjectNameForView( szObjectName, lpView );
   if ( zstrcmpi( szObjectName, "TZWDLGSO" ) == 0 )
      strcpy_s( szRootEntityName, "Dialog" );
   else
   if ( zstrcmpi( szObjectName, "TZZOLODO" ) == 0 )
      strcpy_s( szRootEntityName, "LOD" );
   else
   if ( zstrcmpi( szObjectName, "TZTEVNRO" ) == 0 )
      strcpy_s( szRootEntityName, "TE_DB_Environ" );
   else
   if ( zstrcmpi( szObjectName, "TZEREMDO" ) == 0 )
      strcpy_s( szRootEntityName, "EntpER_Model" );
   else
   if ( zstrcmpi( szObjectName, "TZRPSRCO" ) == 0 )
      strcpy_s( szRootEntityName, "Report" );
   else
   if ( zstrcmpi( szObjectName, "TZCMLPLO" ) == 0 )
      strcpy_s( szRootEntityName, "LPLR" );
   else
   if ( zstrcmpi( szObjectName, "TZDGSRCO" ) == 0 )
      strcpy_s( szRootEntityName, "DomainGroup" );
   else
   if ( zstrcmpi( szObjectName, "TZDMXGPO" ) == 0 )
      strcpy_s( szRootEntityName, "DomainGroup" );
   else
   if ( zstrcmpi( szObjectName, "TZOGSRCO" ) == 0 )
      strcpy_s( szRootEntityName, "GlobalOperationGroup" );
   else
   if ( zstrcmpi( szObjectName, "TZBRLOVO" ) == 0 )
      strcpy_s( szRootEntityName, "Root" );
   else
   if ( zstrcmpi( szObjectName, "TZTENVRO" ) == 0 )
      strcpy_s( szRootEntityName, "TE_DB_Environ" );
   else
   if ( zstrcmpi( szObjectName, "TZOPHDRO" ) == 0 )
      strcpy_s( szRootEntityName, "HeaderFile" );
   else
   if ( zstrcmpi( szObjectName, "TZERSASO" ) == 0 )
      strcpy_s( szRootEntityName, "SubjectArea" );
   else
   if ( zstrcmpi( szObjectName, "TZWDVORO" ) == 0 )
      strcpy_s( szRootEntityName, "ViewObjRef" );
   else
   if ( zstrcmpi( szObjectName, "TZPESRCO" ) == 0 )
      strcpy_s( szRootEntityName, "PresEnvDef" );
   else
   if ( zstrcmpi( szObjectName, "TZADSCDO" ) == 0 )
      strcpy_s( szRootEntityName, "UI_Spec" );
   else
   if ( zstrcmpi( szObjectName, "TZCMWKSO" ) == 0 )
      strcpy_s( szRootEntityName, "RepositoryClient" );
   else
   if ( zstrcmpi( szObjectName, "TZXSLTSO" ) == 0 )
      strcpy_s( szRootEntityName, "XSLT" );
   else
// if ( zstrcmpi( szRootEntityName, "NULL" ) == 0 )
   {
   // strcpy_s( szRootEntityName, "NULL" );
      strcpy_s( szMsg, "There is no ZKey Handler for object, " );
      zstrcat( szMsg, szObjectName );
      MessageSend( lpView, "", "Create Meta Entity", szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Execute a CreateEntity or a CreateTemporalEntity based on the Type passed in.
   if ( nType == 0 )
   {
      nRC = CreateEntity( lpView, szEntityName, nPosition );
      if ( nRC < 0 )
         return( -1 );
   }
   else
   {
      nRC = CreateTemporalEntity( lpView, szEntityName, nPosition );
      if ( nRC < 0 )
         return( -1 );
   }

   // Get the NextZKeyToAssign for the correct Root Entity.
   CreateViewFromView( &lpRootView, lpView );
   SetNameForView( lpRootView, "lpRootView", lpView, zLEVEL_TASK );
   ResetView( lpRootView );

   GetIntegerFromAttribute( (zPLONG) &ulMaxZKey, lpRootView, szRootEntityName, "NextZKeyToAssign" );

   // If the NextZKeyToAssign just retrieved is zero, then we will execute InitializeNextZKeyForObject to properly initialize & increment it.
   if ( ulMaxZKey == 0 )
   {
      InitializeNextZKeyForObject( lpRootView, szRootEntityName, szEntityName );
      GetIntegerFromAttribute( (zPLONG) &ulMaxZKey, lpRootView, szRootEntityName, "NextZKeyToAssign" );
   }
   ulMaxZKey++;
   SetAttributeFromInteger( lpRootView, szRootEntityName, "NextZKeyToAssign", ulMaxZKey );

   DropView( lpRootView );

   if ( SetAttributeFromInteger( lpView, szEntityName, "ZKey", ulMaxZKey ) != 0 )
   {
      DeleteEntity( lpView, szEntityName, zREPOS_NONE );
      MessageSend( lpView, "CM00461", "Configuration Management",
                   "Unable to set MaxZKey in operation CreateMetaEntity",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   return( 0 );
}

//./ ADD NAME=CreateMetaEntity
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: CreateMetaEntity
//
//  PURPOSE:    Creates a Zeidon Meta Entity and sets the ZKey attribute
//              from the MaxZKey attribute found in the WorkStation
//              Object
//
//  PARAMETERS: lpView - the meta object view to create the entity for
//              szEntityName - the Zeidon meta entity name
//              nPosition - integer indicating BEFORE or AFTER
//
//  RETURNS:    0 - Meta entity created
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zOPER_EXPORT zSHORT OPERATION
CreateMetaEntity( zVIEW  vSubtask,
                  zVIEW  lpView,
                  zPCHAR szEntityName,
                  zSHORT nPosition )
{

   zSHORT  nRC;

   nRC = fnCreateMetaEntity( vSubtask, lpView, szEntityName, nPosition, 0 );
   return nRC;

}

//./ ADD NAME=CreateTemporalMetaEntity
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: CreateTemporalMetaEntity
//
//  PURPOSE:    Creates a Zeidon Meta Entity and sets the ZKey attribute
//              from the MaxZKey attribute found in the WorkStation
//              Object
//
//  PARAMETERS: lpView - the meta object view to create the entity for
//              szEntityName - the Zeidon meta entity name
//              nPosition - integer indicating BEFORE or AFTER
//
//  RETURNS:    0 - Meta entity created
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zOPER_EXPORT zSHORT OPERATION
CreateTemporalMetaEntity( zVIEW  vSubtask,
                          zVIEW  lpView,
                          zPCHAR szEntityName,
                          zSHORT nPosition )
{
   zSHORT  nRC;

   nRC = fnCreateMetaEntity( vSubtask, lpView, szEntityName, nPosition, 1 );
   return nRC;
}

//./ ADD NAME=CreateFileNameFromZKey
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: CreateFileNameFromZKey
//
//  PURPOSE:    Creates an eight character file name based upon the
//              WKS_Id and MaxZKey values extrapilated from the ZKey
//              attribute of the entity passed.
//
//  PARAMETERS: szFileName - the address of the file name to be created
//              lpView - the view for which the entity resides
//              pchEntityName - the Zeidon meta entity name
//
//  RETURNS:    0 - FileName created successfully
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zOPER_EXPORT zSHORT OPERATION
CreateFileNameFromZKey( zPCHAR pchFileName,
                        zLONG  lMaxLth,
                        zVIEW  lpView,
                        zPCHAR pchEntity )
{
   zULONG  ulZKey;
   zSHORT  nRC;

   nRC = GetIntegerFromAttribute( (zPLONG) &ulZKey, lpView, pchEntity, "ZKey" );
   zltoxa( ulZKey, pchFileName );
   return( 0 );

#if 0
   long lNumZKey;

   nRC = fnBreakDownZKey( lZKey, &lWKS_Id, &lNumZKey );
   if ( nRC == 0 )
   {
      lWKS_Id = lWKS_Id + 64;
      pchFileName[ 0 ] = ( zCHAR )lWKS_Id;
      if ( lNumZKey < 10 )
      {
         strcpy_s( pchFileName + 1, zsizeof( pchFileName ) - 1, "000000" );
         zltoa( lNumZKey, pchFileName + 7, lMaxLth - 7 );
      }
      else
      if ( lNumZKey < 100 )
      {
         strcpy_s( pchFileName + 1, zsizeof( pchFileName ) - 1, "00000" );
         zltoa( lNumZKey, pchFileName + 6, lMaxLth - 6 );
      }
      else
      if ( lNumZKey < 1000 )
      {
         strcpy_s( pchFileName + 1, zsizeof( pchFileName ) - 1, "0000" );
         zltoa( lNumZKey, pchFileName + 5, lMaxLth - 5 );
      }
      else
      if ( lNumZKey < 10000 )
      {
         strcpy_s( pchFileName + 1, zsizeof( pchFileName ) - 1, "000" );
         zltoa( lNumZKey, pchFileName + 4, lMaxLth - 4 );
      }
      else
      if ( lNumZKey < 100000 )
      {
         strcpy_s( pchFileName + 1, zsizeof( pchFileName ) - 1, "00" );
         zltoa( lNumZKey, pchFileName + 3, lMaxLth - 3 );
      }
      else
      if ( lNumZKey < 1000000 )
      {
         strcpy_s( pchFileName + 1, zsizeof( pchFileName ) - 1, "0" );
         zltoa( lNumZKey, pchFileName + 2, lMaxLth - 2 );
      }
      else
         zltoa( lNumZKey, pchFileName + 1, lMaxLth - 1 );
   return( 0 );
   }
   else
      return( -1 );
#endif
}

//./ ADD NAME=zltoxa
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: zltoxa
//
//  PURPOSE:    Converts a long to a hex string with the first character
//              set to 'Z' if it is a '0'.
//
//  PARAMETERS: lIn         - the long integer to be coverted
//              szHexString - the string returned (must be 8 chars + null)
//
//  RETURNS:    0 - allways
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zOPER_EXPORT zSHORT OPERATION
zltoxa( zLONG  lIn,
        zPCHAR szHexString )
{
   zLONG lWk;
   zPCHAR p;
   unsigned char c;
   int i;

   lWk = lIn;
   p = (zPCHAR) &lWk;
   p = p + 3;
   szHexString[ 8 ] = 0;
   for ( i = 0; i < 7; )
   {
      c = *p;
      c = c >> 4;      // shift c because p is a 'signed' char
      if ( c > 9 )
         c = c + 55;
      else
         c = c + 48;
      szHexString[ i++ ] = c;
      c = *p & 0x0f;
      if ( c > 9 )
         c = c + 55;
      else
         c = c + 48;
      szHexString[ i++ ] = c;
      p--;
   }

   if ( szHexString[ 0 ] == '0' )
      szHexString[ 0 ] = 'Z';

   return( 0 );
}

//./ ADD NAME=zxatol
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: zxatol
//
//  PURPOSE:    Converts a long to a hex string with the first character
//              set to 'Z' if it is a '0'.
//
//  PARAMETERS: szHexString - the string input (must be 8 chars + null)
//              plIn        - pointer to the long integer to be returned
//
//  RETURNS:    0 - allways
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zOPER_EXPORT zSHORT OPERATION
zxatol(  zPCHAR szHexString,
         zPLONG plIn )
{
   zLONG lWk;
   zPCHAR p;
   unsigned char c;
   int i;

   if ( szHexString[ 0 ] == 'Z' )
      szHexString[ 0 ] = '0';
   p = (zPCHAR) &lWk;
   p = p + 3;
   for ( i = 0; i < 7; )
   {
      c = szHexString[ i++ ];
      if ( c > 64 )
         c = c -55;
      else
         c = c -48;
      *p = c << 4;      // shift c because p is a 'signed' char
      c = szHexString[ i++ ];
      if ( c > 64 )
         c = c -55;
      else
         c = c -48;
      *p = c | *p;
      p--;
   }
   *plIn = lWk;
   return( 0 );
}

//./ ADD NAME=AssignZKeyToMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: AssignZKeyToMetaOI
//
//  PURPOSE:    Checks an Object Instance's Entities for valid ZKey
//              attributes and if they are not set or are invalid or
//              reassignment is requested, a new ZKey is set.
//
//  PARAMETERS: OI_View - the view of the Object Instance to be checked
//              nType - a valid LPL meta type, i.e. zSOURCE_DIALOG_META
//              Assign - indicator telling function to reassign all
//                       ZKeys (1) or only invalid ZKeys (0)
//
//  RETURNS:    0 - ZKeys successfully converted
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zOPER_EXPORT zSHORT OPERATION
AssignZKeyToMetaOI( zVIEW  vSubtask,
                    zVIEW  OI_View,
                    zSHORT nType,
                    zSHORT Assign )
{
   zCHAR   szErrMsg[ zSHORT_MESSAGE_LTH + 1 ];
   zCHAR   szEntityName[ 33 ];
   zULONG  ulZKey;
   zUSHORT uLevel;
   zSHORT  nRC, nEntityType;

   nEntityType = fnVerifyType( nType );
   if ( nEntityType < 0 )
      return( -1 );
   if ( nEntityType == CM_ACTIVE_TYPE )
   {
      strcpy_s( szEntityName, zsizeof( szEntityName ), SRC_CMOD[ nType ].szOD_ROOT );
      if ( DefineHierarchicalCursor( OI_View, SRC_CMOD[ nType ].szOD_ROOT ) != 0 )
      {
         return( -1 );
      }
   }
   else
   if ( nEntityType == CM_REFER_TYPE )
   {
      strcpy_s( szEntityName, zsizeof( szEntityName ), REFER_CMOD[ nType - 10000 ].szOD_ROOT );
      if ( DefineHierarchicalCursor( OI_View, REFER_CMOD[ nType - 2000 ].szOD_ROOT ) != 0 )
      {
         return( -1 );
      }
   }

   nRC = zCURSOR_SET;
   do
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKey, OI_View, szEntityName, "ZKey" );
      if ( (ulZKey > 999999999) || (ulZKey <= 0) || (Assign == 1) )
      {
         if ( SetZKeyToNextZKey( vSubtask, OI_View, szEntityName ) < 0 )
         {
            TraceLineS( "Configuration Management", "Assign of ZKey Failed!!!" );
            strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Entity is: " );
            strcpy_s( szErrMsg, zsizeof( szErrMsg ), szEntityName );
            TraceLineS( "Configuration Management", szErrMsg );
            DisplayEntityInstance( OI_View, szEntityName );
            strcpy_s( szErrMsg, zsizeof( szErrMsg ), "Root Entity is: " );
            strcpy_s( szErrMsg, zsizeof( szErrMsg ), SRC_CMOD[ nType ].szOD_ROOT );
            TraceLineS( "Configuration Management", szErrMsg );
            return( -1 );
         }
      }

      if ( nRC == zCURSOR_SET_RECURSIVECHILD )
         nRC = SetViewToSubobject( OI_View, szEntityName );

      nRC = SetCursorNextEntityHierarchical( &uLevel, szEntityName, OI_View );

   } while ( (nRC != zCURSOR_UNCHANGED) && (nRC != zCALL_ERROR) );

   nRC = DropHierarchicalCursor( OI_View );
   return( 0 );
}

//./ ADD NAME=SetZKeyToNextZKey
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: SetZKeyToNextZKey
//
//  PURPOSE:    Set the "ZKey" attribute of the input MetaEntity to the
//              next vailable ZKey for the workstation.
//
//  PARAMETERS: OI_View    - the view of the Object Instance
//              EntityName - of the currently positioned MetaEntity
//
//  RETURNS:    0 - ZKeys successfully set
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zOPER_EXPORT zSHORT OPERATION
SetZKeyToNextZKey( zVIEW  vSubtask,
                   zVIEW  lpView,
                   zPCHAR szEntityName )
{
   zVIEW   vZeidonCM;
   zVIEW   WKS_View;
   zVIEW   vTZCMREPO;
   zLONG   lWKS_Id;
   zLONG   lWkZKey;
   zULONG  ulMaxZKey;

   if ( GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION ) <= 0 )
   {
      return( -1 );
   }

   GetViewByName( &WKS_View, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );
   if ( WKS_View == 0 )  // View isn't there
   {
      MessageSend( lpView, "CM00465", "Configuration Management",
                   "The RepositoryClient View ID was not found",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   GetIntegerFromAttribute( (zPLONG) &ulMaxZKey, WKS_View, "RepositoryClient", "MaxZKey" );
   if ( ulMaxZKey == 0 )
   {
      GetIntegerFromAttribute( &lWKS_Id, WKS_View, "RepositoryClient", "WKS_Id" );
      ulMaxZKey = lWKS_Id * 1000000;
   }

/* PETTIT  Add this code when we have a CPL to work with!!!!!!  */
   fnBreakDownZKey( ulMaxZKey, &lWKS_Id, &lWkZKey );
   if ( lWkZKey > 999999 )
   {
      GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );
      if ( vTZCMREPO < 0 )
      {
         if ( ActivateObjectInstance( &vTZCMREPO, "TZCMREPO", lpView, 0, zSINGLE ) != 0 )
         {
            MessageSend( lpView, "CM00466", "Configuration Management",
                         "MaxZKey limit exceeded, unable to access "
                           "Installation object to assign new WKS_Id",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }
      }

      GetIntegerFromAttribute( &lWKS_Id, vTZCMREPO, "Installation", "NextWKS_Id" );
      SetAttributeFromInteger( WKS_View, "RepositoryClient", "WKS_Id", lWKS_Id );
      ulMaxZKey = lWKS_Id * 1000000;
      lWKS_Id++;
      SetAttributeFromInteger( vTZCMREPO, "Installation", "NextWKS_Id", lWKS_Id );
      CommitObjectInstance( vTZCMREPO );
      oTZCMWKSO_CommitWorkstation( WKS_View );
   }

   ulMaxZKey++;
   if ( SetAttributeFromInteger( lpView, szEntityName, "ZKey", ulMaxZKey ) != 0 )
   {
      MessageSend( lpView, "CM00467", "Configuration Management",
                   "Unable to set MaxZKey in operation AssignZKeyToMetaOI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   SetAttributeFromInteger( WKS_View, "RepositoryClient", "MaxZKey", ulMaxZKey );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
zSHORT
fnSetCPLR_ZKey( zVIEW vSubtask, zVIEW vTaskLPLR, zPCHAR szEntityName )
{
   zVIEW   vZeidonCM;
   zVIEW   WKS_View;
   zVIEW   vTZCMREPO;
   zLONG   lWKS_Id;
   zLONG   lWkZKey;
   zULONG  ulMaxZKey;

   if ( GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION ) <= 0 )
   {
      return( -1 );
   }

   if ( GetViewByName( &WKS_View, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK ) < 0 )
   {
      MessageSend( vTaskLPLR, "CM00468", "Configuration Management",
                   "The RepositoryClient View ID was not found",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   GetIntegerFromAttribute( (zPLONG) &ulMaxZKey, WKS_View, "RepositoryClient", "MaxZKey" );
   if ( ulMaxZKey == 0 )
   {
      GetIntegerFromAttribute( &lWKS_Id, WKS_View, "RepositoryClient", "WKS_Id" );
      ulMaxZKey = lWKS_Id * 1000000;
   }

/* PETTIT  Add this code when we have a CPL to work with!!!!!!  */
   fnBreakDownZKey( ulMaxZKey, &lWKS_Id, &lWkZKey );
   if ( lWkZKey > 999999 )
   {
      if ( GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK ) < 0 )
      {
         if ( ActivateObjectInstance( &vTZCMREPO, "TZCMREPO", vTaskLPLR, 0, zSINGLE ) != 0 )
         {
            MessageSend( vTaskLPLR, "CM00469", "Configuration Management",
                         "MaxZKey limit exceeded, unable to access "
                           "Installation object to assign new WKS_Id",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }
      }

      GetIntegerFromAttribute( &lWKS_Id, vTZCMREPO, "Installation", "NextWKS_Id" );
      SetAttributeFromInteger( WKS_View, "RepositoryClient", "WKS_Id", lWKS_Id );
      ulMaxZKey = lWKS_Id * 1000000;
      lWKS_Id++;
      SetAttributeFromInteger( vTZCMREPO, "Installation", "NextWKS_Id", lWKS_Id );
      CommitObjectInstance( vTZCMREPO );
      oTZCMWKSO_CommitWorkstation( WKS_View );
   }

   ulMaxZKey++;
   if ( SetAttributeFromInteger( vTaskLPLR, szEntityName, "CPLR_ZKey", ulMaxZKey ) != 0 )
   {
      MessageSend( vTaskLPLR, "CM00470", "Configuration Management",
                   "Unable to set MaxZKey in operation SetCPLR_ZKey",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   SetAttributeFromInteger( WKS_View, "RepositoryClient", "MaxZKey", ulMaxZKey );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
BuildLPLR_MetaTypes( zVIEW vSubtask, zVIEW vLPLR, zSHORT BuildMetas )
{
   zVIEW         IncludeView;
   zCHAR         szDirectorySpec[ zMAX_FILESPEC_LTH + 1 ];
   zLONG         nType;
   zULONG        ulZKey;
   zSHORT        nRC;

   for ( nType = 2000; nType <= zREFER_MAX_META; nType++ )
   {
      // If W_MetaType exists for the current Type, then delete it to make sure that we are starting from scratch.
      if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", nType, "" ) == zCURSOR_SET )
      {
         DeleteEntity( vLPLR, "W_MetaType", zPOS_AFTER );
      }

      CreateEntity( vLPLR, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vLPLR, "W_MetaType", "Type", nType );

      // DGC - DOMGRP
      // Skip domains and global ops because we will pick them up as part of domain groups and gop groups.
      // See fnGetAndSetZKey for more.
      if ( nType == zREFER_DOMAIN_META || nType == zREFER_GO_META )
         continue;

      if ( BuildMetas == 1 )
      {
         zCHAR  szTempSpec[ zMAX_FILESPEC_LTH + 1 ];

         GetStringFromAttribute( szTempSpec, zsizeof( szTempSpec ), vLPLR, "LPLR", "MetaSrcDir" );
         SysConvertEnvironmentString( szDirectorySpec, zsizeof( szDirectorySpec ), szTempSpec );
         ofnTZCMWKSO_AppendSlash( szDirectorySpec );
         strcat_s( szDirectorySpec, zsizeof( szDirectorySpec ), "*" );
         strcat_s( szDirectorySpec, zsizeof( szDirectorySpec ), SRC_CMOD[ nType - 2000 ].szOD_EXT );
         fnBuildMetas( vSubtask, vLPLR, szDirectorySpec, CM_REFER_TYPE );
      }
   }

   nRC = CreateViewFromViewForTask( &IncludeView, vLPLR, 0 );  // the include view needs to be in the same task
                                                               // as vLPLR, not in the same task as vSubtask
   for ( nType = 0; nType <= zSOURCE_MAX_META; nType++ )
   {
      // If W_MetaType exists for the current Type, then delete it to make sure that we are starting from scratch.
      if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", nType, "" ) == zCURSOR_SET )
      {
         DeleteEntity( vLPLR, "W_MetaType", zPOS_AFTER );
      }

      CreateEntity( vLPLR, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vLPLR, "W_MetaType", "Type", nType );

      if ( SetCursorFirstEntityByInteger( IncludeView, "W_MetaType", "Type", nType + 2000, "" ) == zCURSOR_SET )
      {
         nRC = SetCursorFirstEntity( IncludeView, "W_MetaDef", "" );
         while ( nRC == zCURSOR_SET )
         {
            GetIntegerFromAttribute( (zPLONG) &ulZKey, IncludeView, "W_MetaDef", "CPLR_ZKey" );
            if ( SetCursorFirstEntityByInteger( vLPLR, "W_MetaDef", "CPLR_ZKey", (zLONG) ulZKey, "" ) != zCURSOR_SET )
            {
              IncludeSubobjectFromSubobject( vLPLR, "W_MetaDef", IncludeView, "W_MetaDef", zPOS_AFTER );
            }

            nRC = SetCursorNextEntity( IncludeView, "W_MetaDef", "" );
         }
      }
   }

   nRC = DropView( IncludeView );
   zgSortEntityWithinParent( zASCENDING, vLPLR, "W_MetaType", "Type", "" );
   return( 0 );
}

//BL, 2000.01.13 if PPE does not exist in LPLR directory, then load PPE from
//               Zeidon Bin/Sys  directory
zOPER_EXPORT zSHORT OPERATION
LoadZeidonPPE( zVIEW  vSubtask,
               zPVIEW pvPPEView,
               zSHORT nType,
               zVIEW  vMetaView,
               zPCHAR pchMessageTitle,
               zPCHAR pchMessageText )
{
   zCHAR   szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR   szLPLR_Phat[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR   szSystem_Phat[ zMAX_FILESPEC_LTH + 1 ];
   // SR 2000.10.23:
   // allocate 2*zMAX_FILESPEC_LTH + zLONG_MESSAGE_LTH + 1  space because szMessage includes szLPLR_Phat and szSystem_Phat and
   // additional  zLONG_MESSAGE_LTH + 1  because size of pchMessageText is unknown
   zCHAR  szMessage[ 2 * zMAX_FILESPEC_LTH + zLONG_MESSAGE_LTH + 1 ];
   zVIEW  vTaskLPLR;
   zVIEW  vSystemPPE;
   zVIEW  vZeidonCM;
   zSHORT nRC = -1;

   RetrieveViewForMetaList( vSubtask, &vMetaView, nType );

   if ( SetCursorFirstEntity( vMetaView, "W_MetaDef", "" ) < zCURSOR_SET )
   {
      // No PPE in LPLR, use the one from Zeidon System.

      // First, if we already got it on system level, take the "one and only".
      GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
      nRC = GetViewByName( &vSystemPPE, NAME_OF_CACHED_PPE, vZeidonCM, zLEVEL_SUBTASK );

      if ( nRC >= 0 )
      {
         // ok, we found it ...
         // Create a new view, because it will be renamed.
         CreateViewFromViewForTask( pvPPEView, vSystemPPE, vSubtask );
         return( 0 );
      }

      zgGetZeidonToolsDir( vSubtask, szSystem_Phat, zAPPL_DIR_OBJECT );
      strcpy_s( szFileName, zsizeof( szFileName ), szSystem_Phat );
      strcat_s( szFileName, zsizeof( szFileName ), "ZEIDON.PPE" );

      // zLEVEL_APPLICATION is required, so that the view
      //  would belong to the main task. Strange ...
      nRC = ActivateOI_FromFile( &vSystemPPE, "TZPESRCO", vMetaView, szFileName, zIGNORE_ERRORS | zLEVEL_APPLICATION );
      if ( nRC < 0 )
      {
         if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) > 0 )
         {
            GetStringFromAttribute( szLPLR_Phat, zsizeof( szLPLR_Phat ), vTaskLPLR, "LPLR", "MetaSrcDir" );
         }
         else
            strcpy_s( szSystem_Phat, zsizeof( szSystem_Phat ), "" );

         strcpy_s( szMessage, zsizeof( szMessage ), "Presentation Environment was not found in directories\n" );
         strcat_s( szMessage, zsizeof( szMessage ), szLPLR_Phat );
         strcat_s( szMessage, zsizeof( szMessage ), " and " );
         strcat_s( szMessage, zsizeof( szMessage ), szSystem_Phat );
         strcat_s( szMessage, zsizeof( szMessage ), ".\n\n" );
         strcat_s( szMessage, zsizeof( szMessage ), pchMessageText );
         SysMessageBox( vTaskLPLR, pchMessageTitle, szMessage, zBEEP );
         return( -1 );
      }

      // Create a copy, PPE must be on on System Level,
      //  because it is linked to TZWDLGSO.
      CreateViewFromViewForTask( pvPPEView, vSystemPPE, vSubtask );
      SetNameForView( vSystemPPE, NAME_OF_CACHED_PPE, vZeidonCM, zLEVEL_SUBTASK );
   // SetViewFlags( vSystemPPE, 1 );
   }
   else
   {
      nRC = ActivateMetaOI( vSubtask, pvPPEView, vMetaView, nType, zSINGLE );
   }

   return( nRC );
}

//BL, 2000.01.28  if Component check out
//                RETURNS:    0   - Component (View) is NOT checked out
//                            1   - Component (View) is checked out
//                            zCALL_ERROR
zOPER_EXPORT zSHORT OPERATION
ComponentIsCheckedOut( zVIEW  vSubtask,
                       zVIEW  vComponentView,
                       zLONG  lType )
{
   zCHAR  szEntityName[ 33 ];
   zCHAR  szAttributeName[ 33 ];
   zVIEW  vActiveMetas;
   zVIEW  vZeidonCM;
   zVIEW  vLPLR;
   zVIEW  vComponent;
   zSHORT nRC = 1;

   if ( GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
      return( zCALL_ERROR );

   if ( GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION ) <= 0 )
   {
      return( zCALL_ERROR );
   }

   if ( GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK ) <= 0 )
   {
      return( zCALL_ERROR );
   }

   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaType", "Type", lType, "" ) != zCURSOR_SET )
   {
      if ( lType >= 2000 )
      {
         lType = lType - 2000;
         if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaType", "Type", lType, "" ) != zCURSOR_SET )
         {
            return( nRC );
         }
      }
   }

   if ( CheckExistenceOfEntity( vActiveMetas, "W_MetaDef" ) == zCURSOR_NULL )
      return( nRC );

   if ( !vComponentView )
      return( nRC );

   CreateViewFromViewForTask( &vComponent, vComponentView, vSubtask );
   ResetView( vComponent );

   szEntityName[ 0 ] = 0;  // strcpy_s( szEntityName, zsizeof( szEntityName ), "" );
   zGetFirstEntityNameForView( vComponent, szEntityName );

   if ( lType == zSOURCE_DIALOG_META || lType == zSOURCE_REPORT_META || lType == zSOURCE_XSLT_META )
      strcpy_s( szAttributeName, zsizeof( szAttributeName ), "Tag" );
   else
      strcpy_s( szAttributeName, zsizeof( szAttributeName ), "Name" );

   // Position on the correct Component within the type.
   if ( SetCursorFirstEntityByAttr( vActiveMetas, "W_MetaDef", "Name", vComponent, szEntityName, szAttributeName, "" ) == zCURSOR_SET &&
        CompareAttributeToInteger( vActiveMetas, "W_MetaDef", "Status", 1 ) != 0 )
   {
      nRC = 0;
   }

   DropView( vComponent );
   return( nRC );
}

//BL, 2000.02.17  Check: duplicate component types between CPLR and LPLR (for ERD, TE, PPE )
//
//                RETURNS:    < 0   - duplicate component
//                            = 0   - no duplicate component
zOPER_EXPORT zSHORT OPERATION
CheckDuplicateComponents( zVIEW   vTZCMLPLO,       // LPLR View
                          zVIEW   vTZCMCPRO,       // CPLR View
                          zLONG   lComponentType,  // Component type
                          zPCHAR  pchName )        // Name for duplicate Component
{
   zVIEW   vTZCMLPLO_Copy;
   zVIEW   vTZCMCPRO_Copy;
   zULONG  ulZKeyLPLR;
   zULONG  ulZKeyCPRO;
   zLONG   lTypeCPRO;
   zSHORT  nRC;

   CreateViewFromViewForTask( &vTZCMLPLO_Copy, vTZCMLPLO, 0 );
   CreateViewFromViewForTask( &vTZCMCPRO_Copy, vTZCMCPRO, 0 );

   nRC = 0;
   strcpy_s( pchName, 33, "" );

   if ( CheckExistenceOfEntity( vTZCMCPRO_Copy, "Z_MetaDef" ) >= zCURSOR_SET  &&
        SetCursorFirstEntityByInteger( vTZCMCPRO_Copy, "Z_MetaDef", "Type", lComponentType, "" ) == zCURSOR_SET    &&
        CheckExistenceOfEntity( vTZCMLPLO_Copy, "W_MetaType" ) >= zCURSOR_SET &&
        SetCursorFirstEntityByInteger( vTZCMLPLO_Copy, "W_MetaType", "Type", lComponentType, "" ) == zCURSOR_SET    &&
        CheckExistenceOfEntity( vTZCMLPLO_Copy, "W_MetaDef" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lTypeCPRO, vTZCMCPRO_Copy, "Z_MetaDef", "Type" );
      if ( lTypeCPRO == lComponentType )
      {
         //2 Components exist, check the Keys
         GetIntegerFromAttribute( (zPLONG) &ulZKeyLPLR, vTZCMLPLO_Copy, "W_MetaDef", "CPLR_ZKey" );
         GetIntegerFromAttribute( (zPLONG) &ulZKeyCPRO, vTZCMCPRO_Copy, "Z_MetaDef", "ZKey" );

         if ( ulZKeyLPLR != ulZKeyCPRO )
         {
            // duplicate component
            GetStringFromAttribute( pchName, 33, vTZCMCPRO_Copy, "Z_MetaDef", "Name" );
            nRC = 1;
            return( -1 );
         }
      }
   } //endif ( SetCursorFirstEntityByInteger( TZCMLPLO_Copy ....

   DropView( vTZCMLPLO_Copy );
   DropView( vTZCMCPRO_Copy );

   return( nRC );
}

//BL, 2000.02.17  Check all component for duplicate component names
//
//                RETURNS:    < 0   - duplicate component names
//                            = 0   - no duplicate component names
zOPER_EXPORT zSHORT OPERATION
CheckAllDuplicateName( zVIEW   vTZCMLPLO,   // LPLR View
                       zVIEW   vTZCMCPRO,   // CPLR View
                       zPCHAR  pchTypeCPLR,  // Return Type for duplicate Name
                       zPCHAR  pchTypeLPLR,  // Return Type for duplicate Name
                       zPCHAR  pchName )     // Return Name for duplicate Component
{
   zVIEW   vTZCMLPLO_Copy;
   zSHORT  nRC;

   CreateViewFromViewForTask( &vTZCMLPLO_Copy, vTZCMLPLO, 0 );

   if ( CheckExistenceOfEntity( vTZCMLPLO_Copy, "W_MetaType" ) < zCURSOR_SET )
      return( 0 );

   nRC = SetCursorFirstEntity( vTZCMLPLO_Copy, "W_MetaDef", "LPLR" );
   while ( nRC >= zCURSOR_SET )
   {
      nRC = CheckDuplicateName( vTZCMLPLO_Copy,  vTZCMCPRO, pchTypeCPLR, pchTypeLPLR, pchName );
      if ( nRC < 0 )
      {
         DropView( vTZCMLPLO_Copy );
         return( nRC );
      }

      nRC = SetCursorNextEntity( vTZCMLPLO_Copy, "W_MetaDef", "LPLR" );
   }

   DropView( vTZCMLPLO_Copy );
   return( 0 );
}

//BL, 2000.02.17  Check current component for duplicate component names
//
//          RETURNS:    - 1   - duplicate component names within component type
//                      - 2   - duplicate component names between LODs and Dialogs
//                      = 0   - no duplicate component names
zOPER_EXPORT zSHORT OPERATION
CheckDuplicateName( zVIEW   vTZCMLPLO,       // LPLR View
                    zVIEW   vTZCMCPRO,       // CPLR View
                    zPCHAR  pchTypeCPLR,      // Return Type for duplicate Name
                    zPCHAR  pchTypeLPLR,      // Return Type for duplicate Name
                    zPCHAR  pchName )         // Return Name for duplicate Component
{
   zVIEW   vTZCMCPRO_Copy;
   zULONG  ulZKeyLPLR;
   zULONG  ulZKeyCPRO;
   zLONG   lTypeCPRO;
   zLONG   lTypeLPLR;
   zSHORT  nRC;

   CreateViewFromViewForTask( &vTZCMCPRO_Copy, vTZCMCPRO, 0 );

   GetStringFromAttribute( pchName, 33, vTZCMLPLO, "W_MetaDef", "Name" );
   //exists a component with this name, then check the Key
   if ( SetCursorFirstEntityByString( vTZCMCPRO_Copy, "Z_MetaDef", "Name", pchName, "" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKeyLPLR, vTZCMLPLO, "W_MetaDef", "CPLR_ZKey" );
      do
      {
         GetIntegerFromAttribute( (zPLONG) &ulZKeyCPRO, vTZCMCPRO_Copy, "Z_MetaDef", "ZKey" );
         //is another component, check the type
         if ( ulZKeyLPLR != ulZKeyCPRO )
         {
            GetIntegerFromAttribute( &lTypeCPRO, vTZCMCPRO_Copy, "Z_MetaDef", "Type" );
            GetIntegerFromAttribute( &lTypeLPLR, vTZCMLPLO, "W_MetaType", "Type" );
            if ( lTypeLPLR >= 2000 )
               lTypeLPLR = lTypeLPLR - 2000;
            if ( lTypeCPRO >= 2000 )
               lTypeCPRO = lTypeCPRO - 2000;

            nRC = 0;
            if ( lTypeCPRO == lTypeLPLR )
               nRC = -1;

            //check duplicate Name between Dialogs and LODs
            if ( (lTypeCPRO == zSOURCE_DIALOG_META && lTypeLPLR == zSOURCE_LOD_META) ||
                 (lTypeCPRO == zSOURCE_LOD_META && lTypeLPLR == zSOURCE_DIALOG_META) )
            {
               nRC = -2;
            }

            if ( nRC < 0 )
            {
               GetVariableFromAttribute( pchTypeCPLR, 0, zTYPE_STRING, 125, vTZCMCPRO_Copy, "Z_MetaDef", "Type", "CM_Type", 0 );
               GetVariableFromAttribute( pchTypeLPLR, 0, zTYPE_STRING, 125, vTZCMLPLO, "W_MetaType", "Type", "CM_Type", 0 );
               DropView( vTZCMCPRO_Copy );
               return( nRC );
            }
         } //endif ( ulZKeyLPLR != ulZKeyCPRO )
      }
      while ( SetCursorNextEntityByString( vTZCMCPRO_Copy, "Z_MetaDef", "Name", pchName, "" ) >= zCURSOR_SET );
   } //endif ( SetCursorFirstEntityByString( vTZCMCPRO_Copy, "Z_MetaDef"...

   DropView( vTZCMCPRO_Copy );

   return( 0 );
}

//BL, 2000.02.17  Check current component for duplicate component names
//
//                RETURNS:    < 0   - duplicate component names
//                            = 0   - no duplicate component names
zOPER_EXPORT zSHORT OPERATION
CheckDuplicateNameForRefresh( zVIEW    vTZCMLPLO,   // LPLR View
                              zVIEW    vTZCMCPRO,   // CPLR View
                              zPCHAR   pchTypeCPLR,  // ReturnType for duplicate Name
                              zPCHAR   pchTypeLPLR,  // ReturnType for duplicate Name
                              zPCHAR   pchName,      // ReturnName for duplicate Comp
                              zPULONG  pulZKeyLPLR )// ReturnZKey for duplicate Comp
{
   zVIEW   vTZCMLPLO_Copy;
   zULONG  ulZKeyCPRO;
   zLONG   lTypeCPRO;
   zLONG   lTypeLPLR;
   zSHORT  nRC;

   *pulZKeyLPLR = 0;
   CreateViewFromViewForTask( &vTZCMLPLO_Copy, vTZCMLPLO, 0 );

   GetStringFromAttribute( pchName, 33, vTZCMCPRO, "Z_MetaDef", "Name" );

   // If a component exists with this name, then check the Key.
   if ( SetCursorFirstEntityByString( vTZCMLPLO_Copy, "W_MetaDef", "Name", pchName, "LPLR" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKeyCPRO, vTZCMCPRO, "Z_MetaDef", "ZKey" );
      do
      {
         GetIntegerFromAttribute( (zPLONG) pulZKeyLPLR, vTZCMLPLO_Copy, "W_MetaDef", "CPLR_ZKey" );

         // If it is another component ... check the type.
         if ( *pulZKeyLPLR != ulZKeyCPRO )
         {
            GetIntegerFromAttribute( &lTypeCPRO, vTZCMCPRO, "Z_MetaDef", "Type" );
            GetIntegerFromAttribute( &lTypeLPLR, vTZCMLPLO_Copy, "W_MetaType", "Type" );
            if ( lTypeLPLR >= 2000 )
               lTypeLPLR = lTypeLPLR - 2000;
            if ( lTypeCPRO >= 2000 )
               lTypeCPRO = lTypeCPRO - 2000;

            nRC = 0;
            if ( lTypeCPRO == lTypeLPLR )
               nRC = -1;

            // Check duplicate Name between Dialogs and LODs.
            if ( (lTypeCPRO == zSOURCE_DIALOG_META &&
                  lTypeLPLR == zSOURCE_LOD_META) ||
                 (lTypeCPRO == zSOURCE_LOD_META &&
                  lTypeLPLR == zSOURCE_DIALOG_META) )
            {
               nRC = -2;
            }

            if ( nRC < 0 )
            {
               GetVariableFromAttribute( pchTypeLPLR, 0, zTYPE_STRING, 125, vTZCMLPLO_Copy, "W_MetaType", "Type", "CM_Type", 0 );
               GetVariableFromAttribute( pchTypeCPLR, 0, zTYPE_STRING, 125, vTZCMCPRO, "Z_MetaDef", "Type", "CM_Type", 0 );
               DropView( vTZCMLPLO_Copy );
               return( nRC );
            }
         } //endif ( ulZKeyLPLR != ulZKeyCPRO )
      }
      while ( SetCursorNextEntityByString( vTZCMLPLO_Copy, "W_MetaDef", "Name", pchName, "LPLR" ) >= zCURSOR_SET );
   } //endif ( SetCursorFirstEntityByString( vTZCMLPLO_Copy, "W_MetaDef"...

   DropView( vTZCMLPLO_Copy );

   return( 0 );
}

//BL, 2000.02.25  set Project name, Tool name, component name and check out state in title
//
//                RETURNS:    < 0   - error
//                            = 0   - no error
zOPER_EXPORT zSHORT OPERATION
SetTitleWithCheckOutState( zVIEW    vSubtask,
                            zPCHAR  pchToolName,
                            zPCHAR  pchLodName,
                            zVIEW   vToolView,
                            zPCHAR  pchEntityName,
                            zLONG   lType )
{
   zVIEW  vTaskLPLR;
   zCHAR  szComponentname[ 33 ];
   zCHAR  szLPL_Name[ 33 ];
   zCHAR  szAttributename[ 33 ];
   zCHAR  szTitle[ 255 ];
   zCHAR  szCheckedOut[ 50 ];

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) < 0 )
   {
      SetWindowCaptionTitle( vSubtask, pchToolName, "" );
      return( -1 );
   }

   if ( lType == zSOURCE_DIALOG_META || lType == zSOURCE_REPORT_META || lType == zSOURCE_XSLT_META )
      strcpy_s( szAttributename, zsizeof( szAttributename ), "Tag" );
   else
      strcpy_s( szAttributename, zsizeof( szAttributename ), "Name" );

   GetStringFromAttribute( szLPL_Name, zsizeof( szLPL_Name ), vTaskLPLR, "LPLR", "Name" );

   if ( GetViewByName( &vToolView, pchLodName, vSubtask, zLEVEL_TASK ) >= 0 )
   {
      GetStringFromAttribute( szComponentname, zsizeof( szComponentname ), vToolView,
                              pchEntityName, szAttributename );
      // if component not checked out, then set new Title
      if ( ComponentIsCheckedOut( vSubtask, vToolView, lType ) )
         strcpy_s( szCheckedOut, zsizeof( szCheckedOut ), "" );
      else
         strcpy_s( szCheckedOut, zsizeof( szCheckedOut ), " < not checked out >" );
   }
   else
   {
      strcpy_s( szComponentname, zsizeof( szComponentname ), "[Untitled]" );
      strcpy_s( szCheckedOut, zsizeof( szCheckedOut ), "" );
   }

   strcpy_s( szTitle, zsizeof( szTitle ), pchToolName );
   strcat_s( szTitle, zsizeof( szTitle ), " - " );
   strcat_s( szTitle, zsizeof( szTitle ), szComponentname );

   strcat_s( szTitle, zsizeof( szTitle ), szCheckedOut );
   SetWindowCaptionTitle( vSubtask, szLPL_Name, szTitle );

   return( 0 );
}

//BL, 2000.02.25  for windows within Tools (for example Open Domain):
//                set check out state in title and returned checked out state
//                RETURNS:    0   - Component is NOT checked out
//                            1   - Component is checked out
//                            zCALL_ERROR
zOPER_EXPORT zSHORT OPERATION
CheckOutStateForCurrentWindow( zVIEW   vSubtask,
                               zVIEW   vToolView )
{
   zCHAR  szTitle[ 250 ];
   zCHAR  szNotCheckedOut[ 30 ];
   zSHORT nCheckOut = 0;
   HWND   hWnd;

   GetWindowHandle( (zPULONG) &hWnd, 0, vSubtask, 0 );
   GetWindowText( hWnd, szTitle, 249 );

   strcpy_s( szNotCheckedOut, zsizeof( szNotCheckedOut ), " < not checked out >" );
   zSearchAndReplace( szTitle, 249, szNotCheckedOut, "" );

   if ( CheckExistenceOfEntity( vToolView, "W_MetaDef" ) >= zCURSOR_UNDEFINED )
   {
      if ( CompareAttributeToInteger( vToolView, "W_MetaDef",
           "Status", 1 ) == 0 )
      {
         nCheckOut = 1;
      }

      // if component not checked out
      if ( nCheckOut )
         strcat_s( szTitle, zsizeof( szTitle ), "" );
      else
         strcat_s( szTitle, zsizeof( szTitle ), szNotCheckedOut );

      SetWindowCaptionTitle( vSubtask, szTitle, "" );
   }

   return( nCheckOut );
}

// Save sort order for window open components (for example "Open Domain").
zOPER_EXPORT zSHORT OPERATION
SaveSortOrder( zVIEW vSubtask,
               zVIEW vCM_List )
{
   zPCHAR pchListCtrl;
   zCHAR  szAttributeName[ 33 ];
   zLONG  lType;

   if ( CheckExistenceOfEntity( vCM_List, "W_MetaType" ) < zCURSOR_SET )
      return( -1 );

   // get ListCtrl Tag
   pchListCtrl = (zPCHAR) GetActionParameters( vSubtask );

   // get Component Type
   GetIntegerFromAttribute( &lType, vCM_List, "W_MetaType", "Type" );

   if ( zstrcmp( pchListCtrl, "Name" ) == 0 )
      SetAttributeFromInteger( vCM_List, "W_MetaType", "SortOrder", 1 );
   else
   if ( zstrcmp( pchListCtrl, "LastUpdated" ) == 0 )
      SetAttributeFromInteger( vCM_List, "W_MetaType", "SortOrder", 2 );
   else
   {
      if ( lType == zREFER_DOMAIN_META || lType == zREFER_GO_META )
         strcpy_s( szAttributeName, zsizeof( szAttributeName ), "GroupName" );
      else
         strcpy_s( szAttributeName, zsizeof( szAttributeName ), "Description" );

      if ( zstrcmp( pchListCtrl, szAttributeName ) == 0 )
         SetAttributeFromInteger( vCM_List, "W_MetaType", "SortOrder", 3 );
      else
         SetAttributeFromInteger( vCM_List, "W_MetaType", "SortOrder", 0 );
   }

   return( 0 );
}

// Sort components for window open components (for example "Open Domain").
zOPER_EXPORT zSHORT OPERATION
SortComponents( zPVIEW vCM_List )
{
   zLONG  lSortOrder;
   zCHAR  szOrderKeys[ 100 ];
   zLONG  lType;

   if ( CheckExistenceOfEntity( *vCM_List, "W_MetaType" ) < zCURSOR_SET ||
        CheckExistenceOfEntity( *vCM_List, "W_MetaDef" ) < zCURSOR_SET )
   {
      return( -1 );
   }

   // Get Component Type.
   GetIntegerFromAttribute( &lSortOrder, *vCM_List, "W_MetaType", "SortOrder" );
   GetIntegerFromAttribute( &lType, *vCM_List, "W_MetaType", "Type" );

   switch( lSortOrder )
   {
      case 0:        // no sort order
         strcpy_s( szOrderKeys, zsizeof( szOrderKeys ), "LastUpdateDate D Name A" );
         break;

      case 1:        // sort by name
         strcpy_s( szOrderKeys, zsizeof( szOrderKeys ), "Name A LastUpdateDate D" );
         break;

      case 2:        // sort by last update date
         strcpy_s( szOrderKeys, zsizeof( szOrderKeys ), "LastUpdateDate D Name A" );
         break;

      case 3:        // sort by Group or Description
         if ( lType == zSOURCE_DOMAIN_META || lType == zSOURCE_GO_META ||
              lType == zREFER_DOMAIN_META  || lType == zREFER_GO_META )
            strcpy_s( szOrderKeys, zsizeof( szOrderKeys ), "GroupName A Name A" );
         else
            strcpy_s( szOrderKeys, zsizeof( szOrderKeys ), "Desc A Name A" );
         break;
   }

   // Now order the domains by date and name.
   OrderEntityForView( *vCM_List, "W_MetaDef", szOrderKeys );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
IntGenFullQualPathFromRelPath( zVIEW  vSubtask,
                               zPCHAR pchFileName,
                               zPCHAR pchBaseDir,
                               zSHORT nMaxLth,
                               zPCHAR pchDirTxt )
{
   zCHAR szOutput[ 2 * zMAX_FILESPEC_LTH + 1 ];
   zCHAR szMsg[ zSHORT_MESSAGE_LTH + 1 ];
   zSHORT nRC;

   // Build a fully qualified path from a relative path for the Target Executable Directory
   if ( (nRC = GenFullQualPathFromRelPath( pchFileName, pchBaseDir, szOutput, nMaxLth )) == -1)
   {
      // Path exceeds max. length
      sprintf( szMsg, "Path for %s exceeds maximum size", pchDirTxt );
      MessageSend( vSubtask, "ED00105", "Zeidon Compiler", szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }
   else
   {
      strcpy_s( pchFileName, nMaxLth, szOutput );
      return( nRC );
   }
}

zOPER_EXPORT zSHORT OPERATION
SetCompSpecPaths( zVIEW  vTarget,
                  zPCHAR pchSourceCompSrcDir,
                  zPCHAR pchSourceLPLRName,
                  zPCHAR pchSourceAktDir,
                  zPCHAR pchEntityName,
                  zPCHAR pchAttributeName,
                  zPCHAR pchDirName,
                  zPCHAR pchMsgTitle,
                  zSHORT nMaxLth )
{

   zCHAR szNewPath[ 2 * zMAX_FILESPEC_LTH + 1 ];
   zCHAR szAktDirUpper[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR szBaseDir[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR szBaseDirUpper[zMAX_FILESPEC_LTH + 1];
   zCHAR szLPLRNameUpper[ zMAX_FILENAME_LTH + 1 ];
   zCHAR szAktLPLRName[zMAX_FILENAME_LTH + 1 ];
   zCHAR szMsg[ 513 ];

   zSHORT nZRetCode;
   zSHORT nAnfPos;
   zSHORT nAnzahl;
   zSHORT nAktLth;
   zSHORT nBaseLth;
   zSHORT nRC;

   // for comparing change the actual directory-name to uppercase
   nZRetCode = zToUpper( pchSourceAktDir, szAktDirUpper );

   // The pathnames in Compilerspecification should be changed.
   // See if the actual directory is relative or fully qualified
   nRC = GenFullQualPathFromRelPath( pchSourceAktDir, pchSourceCompSrcDir, szNewPath, nMaxLth );
   switch( nRC )
   {
      case 0 :
         // The pathname was relative. There is nothing to do
         nZRetCode = SetAttributeFromString( vTarget, pchEntityName, pchAttributeName, pchSourceAktDir );
         break;

      case 1 :
         // The path was fully qualified
         // See if ComponentSourceDirectory is part of the pathname
         nZRetCode = zToUpper( pchSourceCompSrcDir, szBaseDirUpper );
         nRC = zSearchSubString( szAktDirUpper, szBaseDirUpper, "f", 0 );
         if ( nRC != -1 )
         {
            // The Component Source Directory is part of the pathname
            // Take the new component Source directory and add the end of
            // the original pathname
            GetStringFromAttribute( szBaseDir, zsizeof( szBaseDir ), vTarget, "LPLR", "MetaSrcDir" );
            nAktLth = (zSHORT) zstrlen( szAktDirUpper );
            nBaseLth = (zSHORT) zstrlen( szBaseDirUpper );
            nAnzahl = nAktLth - nBaseLth;
            nAnfPos = nAktLth - nAnzahl + 1;
            ZeidonStringConcat( szBaseDir, 1, 0, pchSourceAktDir, nAnfPos, nAnzahl, 257 );
            nZRetCode = SetAttributeFromString( vTarget, pchEntityName, pchAttributeName, szBaseDir );
         }
         else
         {
            // The Component Source Directory isn't part of the pathname
            // See if the LPLR-Name is part of the pathname
            nZRetCode = zToUpper( pchSourceLPLRName, szLPLRNameUpper );
            nRC = zSearchSubString( szAktDirUpper, szLPLRNameUpper, "f", 0 );
            if (nRC == -1)
            {
               // LPLR-Name isn't part of the pathname. Take it like it is
               nZRetCode = SetAttributeFromString( vTarget, pchEntityName,
                                                   pchAttributeName, pchSourceAktDir );
            }
            else
            {
               // LPLR-Name is part of the pathname. Replace the old LPLR-Name with the new one.
               GetStringFromAttribute( szAktLPLRName, zsizeof( szAktLPLRName ), vTarget, "LPLR", "Name" );
               zSearchAndReplace(pchSourceAktDir, 255, pchSourceLPLRName, szAktLPLRName);
               nZRetCode = SetAttributeFromString( vTarget, pchEntityName, pchAttributeName, pchSourceAktDir );
            }
         }

         break;

      default  :
         ZeidonStringCopy( szMsg, 1, 0, "Path ", 1, 0, 513 );
         ZeidonStringConcat( szMsg, 1, 0, pchDirName, 1, 0, 513 );
         ZeidonStringConcat( szMsg, 1, 0, " exceeds maximum size !", 1, 0, 513 );
         TraceLineS( pchMsgTitle, szMsg );
         break;
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:    SetUpMapLOD
//
// PURPOSE:  This function sets up the SEL_LOD OI for Entity or
//           Attribute mapping.  If a current CtrlMapView entity
//           instance exists, it positions on the related ViewObjRef
//           entity and activates the corresponding LOD.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zLONG OPERATION
SetUpMapLOD( zVIEW   vSubtask,
             zVIEW   vDialogW,
             zVIEW   vDialogC,
             zPCHAR  cpcMapView )
{
   zVIEW    vLOD = 0;
   zVIEW    vCM_List;
   zLONG    lZKey;

   // Set up SEL_LOD, if current mapping exists, and any other mapping
   // data required.

   // pchMapView is CtrlMapView if this was called for Control mapping ... or
   // pchMapView is ActMapView if this was called for Action mapping.  If the
   // MapView exists, use the corresponding LOD for mapping.  Use pchMapView
   // ZKey to locate ViewObjRef and then LOD ZKey to locate LPLR LOD meta.
   if ( CheckExistenceOfEntity( vDialogC, cpcMapView ) == zCURSOR_SET )
   {
      RetrieveViewForMetaList( vSubtask, &vCM_List, zREFER_LOD_META );
      GetIntegerFromAttribute( &lZKey, vDialogC, cpcMapView, "ZKey" );
      SetCursorFirstEntityByInteger( vDialogW, "ViewObjRef", "ZKey", lZKey, "" );
      GetIntegerFromAttribute( &lZKey, vDialogW, "LOD", "ZKey" );
      SetCursorFirstEntityByInteger( vCM_List, "W_MetaDef", "CPLR_ZKey", lZKey, "" );
      ActivateMetaOI( vSubtask, &vLOD, vCM_List, zREFER_LOD_META, 0 );
   }

   return( (zLONG) vLOD );
}


//./ ADD NAME=ActivateMetaOI
// Source Module=tzcmoprs.c
/////////////////////////////////////////////////////////////////////////////
//
//  CM OPERATION: RebuildMetaLists
//
//  PURPOSE:    Rebuild the XLP and LLP. Moved from TZCMSLPD to a global operation.
//
//  PARAMETERS: vSubtask -
//
//  RETURNS:    1 - Meta OI successfully activated
//             -1 - Error encountered
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zOPER_EXPORT zSHORT OPERATION
RebuildMetaLists( zVIEW   vSubtask )
{
   zVIEW  vZeidonCM;
   zVIEW  vTZCMWKSO;
   zVIEW  LPLR_View;
   zVIEW  vTZCMSLPL;
   zVIEW  TZCMULWO = 0;
   zCHAR  szLPLR_FileSpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szDirectorySpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szLPLR_Name[ 33 ];
   zCHAR  szLPLR_FileName[ 33 ];
   zCHAR  szTimestamp[ 22 ];
   zLONG  lTaskUseCnt;
   zLONG  lCurrentZKey;
   zLONG  lZKey;
   zSHORT nRC, nLPLR_Activated;
   HFILE  hFile;
   zCHAR  szDetachSpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szMsg[ zMAX_FILESPEC_LTH + zSHORT_MESSAGE_LTH + 1 ];

   SetNameForView( vSubtask, "TZCM_RebuildLPLR", vSubtask, zLEVEL_TASK );
   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );
   if ( vTZCMWKSO == 0 )  // view isn't there
      return( -1 );

   // TZCMSLPL exists if we come here from SwitchLPLR but doesn't exist if we are calling this from
   // "Create New Project", we will assume for now that we are on the correct LPLR in TZCMWKSO if
   // TZCMSLPL doesn't exist.
   if ( GetViewByName( &vTZCMSLPL, "TZCMSLPL", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      GetIntegerFromAttribute( &lZKey, vTZCMSLPL, "LPLR", "ZKey" );
      GetIntegerFromAttribute( &lCurrentZKey, vTZCMWKSO, "LPLR", "ZKey" );
      nRC = SetCursorFirstEntityByInteger( vTZCMWKSO, "LPLR", "ZKey", lZKey, "" );
   }
   GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vTZCMWKSO, "LPLR", "Name" );
   nLPLR_Activated = GetViewByName( &LPLR_View, szLPLR_Name, vZeidonCM, zLEVEL_SUBTASK );
   GetStringFromAttribute( szDirectorySpec, zsizeof( szDirectorySpec ), vTZCMWKSO, "LPLR", "ExecDir" ); // borrow szDirectorySpec for a second
   SysConvertEnvironmentString( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), szDirectorySpec );
   ofnTZCMWKSO_AppendSlash( szLPLR_FileSpec );
   strncpy_s( szLPLR_FileName, zsizeof( szLPLR_FileName ), szLPLR_Name, zsizeof( szLPLR_FileName ) - 1 );
   for ( nRC = 0; nRC < 32; nRC++ )
   {
      if ( szLPLR_FileName[ nRC ] == 0 )
         break;

      if ( szLPLR_FileName[ nRC ] == ' ' )
         szLPLR_FileName[ nRC ] = '_';
   }

   szLPLR_FileName[ nRC ] = 0;
   strcat_s( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), szLPLR_FileName );
   strcat_s( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), ".XLP" );
   if ( nLPLR_Activated < 1 ) // LPLR currently not activated
   {
      hFile = (HFILE) SysOpenFile( vSubtask, szLPLR_FileSpec, COREFILE_READ );
      if ( hFile > 0 )
      {                     // Activate LPLR for rebuild only
         SysCloseFile( vSubtask, hFile, 0 );
         nRC = ActivateOI_FromFile( &LPLR_View, "TZCMLPLO", vSubtask, szLPLR_FileSpec, zSINGLE );
         nRC = BuildLPLR_MetaTypes( vSubtask, LPLR_View, 1 );
      }
      else
      {
         if ( ActivateEmptyObjectInstance( &LPLR_View, "TZCMLPLO", vSubtask, zSINGLE ) != 0 )
         {
            MessageSend( vSubtask, "CM00604", "Configuration Management",
                         "Error activating empty Project Instance",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
            return( -1 );
         }

         CreateMetaEntity( vSubtask, LPLR_View, "LPLR", zPOS_AFTER );
         SetAttributeFromAttribute( vTZCMWKSO, "LPLR", "ZKey", LPLR_View, "LPLR", "ZKey" );
         SetMatchingAttributesByName( LPLR_View, "LPLR", vTZCMWKSO, "LPLR", zSET_NOTNULL );
         if ( CheckExistenceOfEntity( vTZCMWKSO, "CorrespondingCPLR" ) >= zCURSOR_SET )
              IncludeSubobjectFromSubobject( LPLR_View, "CorrespondingCPLR", vTZCMWKSO, "CorrespondingCPLR", zPOS_AFTER );
         nRC = BuildLPLR_MetaTypes( vSubtask, LPLR_View, 1 );
      }
   }
   else  // LPLR is currently active
   {
      if ( lZKey != lCurrentZKey )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Project is currently active in another task.\n" );
         strcat_s( szMsg, zsizeof( szMsg ), "Rebuilding the Project may corrupt the meta list.\n" );
         strcat_s( szMsg, zsizeof( szMsg ), "Rebuilding of the Project is therefore cancelled!" );
         MessageSend( vSubtask, "CM00605", "Configuration Management",
                      szMsg,
                      zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
         return( -1 );
      }
      else
      {
         GetIntegerFromAttribute( &lTaskUseCnt, LPLR_View, "LPLR", "TaskUseCount" );
         if ( lTaskUseCnt > 1 )
         {
            strcpy_s( szMsg, zsizeof( szMsg ), "Project is currently active in more than one task.\n" );
            strcat_s( szMsg, zsizeof( szMsg ), "Rebuilding the Project may corrupt the meta list.\n" );
            strcat_s( szMsg, zsizeof( szMsg ), "Rebuilding of the Project is therefore cancelled!" );
            MessageSend( vSubtask, "CM00606", "Configuration Management",
                         szMsg,
                         zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
            return( -1 );
         }
      }

      nRC = BuildLPLR_MetaTypes( vSubtask, LPLR_View, 1 );
   }

   if ( nRC < 0 )
      return( -1 );

   // Test to see if we are indeed writing the correct O to file.
   GetStringFromAttribute( szDirectorySpec, zsizeof( szDirectorySpec ), LPLR_View, "LPLR", "Name" );
   if ( zstrcmpi( szDirectorySpec, szLPLR_Name ) != 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Project Name " );
      strcat_s( szMsg, zsizeof( szMsg ), szLPLR_Name );
      strcat_s( szMsg, zsizeof( szMsg ), " doesn't match name \nof OI file\n" );
      strcat_s( szMsg, zsizeof( szMsg ), szLPLR_FileSpec );
      strcat_s( szMsg, zsizeof( szMsg ), "\nCommit of Project aborted!\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Please notify Bill of error" );
      MessageSend( vSubtask, "CM00607", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   nRC = zgSortEntityWithinParent( zASCENDING, LPLR_View, "W_MetaType", "Type", "" );

   // KSJ 06/10/15 - I think that we want to make sure that the Base Directory in both XLP and LLP are not something that
   // was brought from someone else's project, should be based on the LPLR here on this machine.
   SetAttributeFromAttribute( LPLR_View, "LPLR", "MetaSrcDir", vTZCMWKSO, "LPLR", "MetaSrcDir" );
   SetAttributeFromAttribute( LPLR_View, "LPLR", "PgmSrcDir", vTZCMWKSO, "LPLR", "PgmSrcDir" );
   SetAttributeFromAttribute( LPLR_View, "LPLR", "ExecDir", vTZCMWKSO, "LPLR", "ExecDir" );

   // Added LastBuildDate so that we could then compare the LLP and XLP so see if they should be rebuild because they are out
   // of sync.
   SysGetDateTime( szTimestamp, zsizeof( szTimestamp ) );
   SetAttributeFromString( LPLR_View, "LPLR", "LastBuildDate", szTimestamp );

   if ( CommitOI_ToFile( LPLR_View, szLPLR_FileSpec, zSINGLE ) != 0 ) // zBINARY | zSINGLE ) == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Project " );
      strcat_s( szMsg, zsizeof( szMsg ), szLPLR_Name );
      strcat_s( szMsg, zsizeof( szMsg ), " XLP could not be committed in\n" );
      strcat_s( szMsg, zsizeof( szMsg ), szLPLR_FileSpec );
      MessageSend( vSubtask, "CM00608", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );
      return( -1 );
   }
   GetStringFromAttribute( szDirectorySpec, zsizeof( szDirectorySpec ), vTZCMWKSO, "LPLR", "MetaSrcDir" ); // borrow szDirectorySpec for a second
   SysConvertEnvironmentString( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), szDirectorySpec );
   ofnTZCMWKSO_AppendSlash( szLPLR_FileSpec );
   strncpy_s( szLPLR_FileName, zsizeof( szLPLR_FileName ), szLPLR_Name, zsizeof( szLPLR_FileName ) - 1 );
   strcat_s( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), szLPLR_FileName );
   strcat_s( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), ".LLP" );
   if ( CommitOI_ToFile( LPLR_View, szLPLR_FileSpec, zSINGLE ) != 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Project " );
      strcat_s( szMsg, zsizeof( szMsg ), szLPLR_Name );
      strcat_s( szMsg, zsizeof( szMsg ), " LLP could not be committed in\n" );
      strcat_s( szMsg, zsizeof( szMsg ), szLPLR_FileSpec );
      MessageSend( vSubtask, "CM00608", "Configuration Management",
                   szMsg,
                   zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );
      return( -1 );
   }

   if ( nLPLR_Activated < 1 )  // Application LPLR View not found
   {
      // Drop the OI because it wasn't activated before.
      DropObjectInstance( LPLR_View );
   // GetWKS_FileName( szDirectorySpec );
   // CommitOI_ToFile( vTZCMWKSO, szDirectorySpec, zSINGLE );
   }

   if ( SysGetEnvVar( szDetachSpec, "ZEIDON", zMAX_FILENAME_LTH + 1 ) == 0 )
   {
      ofnTZCMWKSO_AppendSlash( szDetachSpec );
      strcat_s( szDetachSpec, zsizeof( szDetachSpec ), "TZCM.DET" );
      hFile = (HFILE) SysOpenFile( vSubtask, szDetachSpec, COREFILE_DELETE );
   }

   nRC = SetCursorFirstEntityByInteger( vTZCMWKSO, "LPLR", "ZKey", lCurrentZKey, "" );
   return( 0 );
}

// Added this to Global Operations because I believe we will be wanting to call this from somewhere other than just
// the te Build XODs.
zOPER_EXPORT zSHORT OPERATION
RebuildXODs( zVIEW vSubtask )
{
   // This routine does not actually save LODs, but only builds the XODs
   // on the LPLR.

   zVIEW  vDTE;
   zVIEW  vLPLR;
   zVIEW  vLOD_List;
   zVIEW  vLOD;
   zVIEW  vXOD;
   zSHORT nRC;
   zCHAR  szMsg[ zSHORT_MESSAGE_LTH + 1 ];
   zCHAR  szLOD_Name[ 33 ];
   zCHAR  szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szTemp[ zMAX_FILESPEC_LTH + 1 ];

   GetViewByName( &vDTE, "TE_DB_Environ", vSubtask, zLEVEL_TASK );
   GetViewByName( &vLOD_List, "TZZOLFLO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );

   // Save Subtask for use by XOD build routine.
   SetNameForView( vSubtask, "TE_Window", vSubtask, zLEVEL_TASK );

   // For each selected LOD, build the XOD using the current DBMS and
   // commit as file to LPLR, unless the LOD does not have a POD.
   // Note that we are not looking to see if the DBMS identified
   // in the POD.TE_SourceZKey matches the current DBMS. We will save
   // selected LODs with the current DBMS no matter how they were saved
   // last time.

   for ( nRC = SetCursorFirstEntity( vLOD_List, "W_MetaDef", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vLOD_List, "W_MetaDef", "" ) )
   {
      GetStringFromAttribute( szLOD_Name, zsizeof( szLOD_Name ), vLOD_List, "W_MetaDef", "Name" );

      nRC = ActivateMetaOI( vSubtask, &vLOD, vLOD_List, zREFER_LOD_META, zCURRENT_OI );
      if ( nRC < 0 )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Could not Activate LOD: " );
         strcat_s( szMsg, zsizeof( szMsg ), szLOD_Name );
         strcat_s( szMsg, zsizeof( szMsg ), ".\nAborting Build" );
         MessageSend( vSubtask, "TE00426", "Physical Data Model",
                      szMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( 0 );
      }
      else
      {
         // Send message that we are building the LOD.
         strcpy_s( szMsg, zsizeof( szMsg ), "Building executable for LOD: " );
         strcat_s( szMsg, zsizeof( szMsg ), szLOD_Name );
         strcat_s( szMsg, zsizeof( szMsg ), "." );
         MB_SetMessage( vSubtask, 1, szMsg );

         // Make sure the TE_SourceZKey attribute is set because it determines
         // what DBMS_Source is used in building the XOD.
         if ( CheckExistenceOfEntity( vLOD, "POD" ) >= zCURSOR_SET )
            SetAttributeFromAttribute( vLOD, "POD", "TE_SourceZKey", vDTE, "TE_DBMS_Source", "ZKey" );

         // Build the XOD in memory.
         oTZZOXODO_SaveXOD( vSubtask, vLOD );
         SetNameForView( vLOD, "TZZOLODO", vSubtask, zLEVEL_TASK );
         GetViewByName( &vXOD, "TZZOXODO", vSubtask, zLEVEL_TASK );
         DropMetaOI( vSubtask, vLOD );

         // Commit the XOD to LPLR file.
         GetStringFromAttribute( szTemp, zsizeof( szTemp ), vLPLR, "LPLR", "ExecDir" );
         SysConvertEnvironmentString( szFileName, zsizeof( szFileName ), szTemp );
         ofnTZCMWKSO_AppendSlash( szFileName );
         strcat_s( szFileName, zsizeof( szFileName ), szLOD_Name );
         strcat_s( szFileName, zsizeof( szFileName ), ".XOD" );
         TraceLineS( "*** Committing workstation file: ", szFileName );
         CommitOI_ToFile( vXOD, szFileName, zSINGLE );
      }
   }

   MB_SetMessage( vSubtask, 1, "Build of XODs complete." );
   return( 0 );
}

////////////////////////////////////////////////////////////////////////
//   OPERATION:  RebuildXDM
//   PURPOSE:    This Entry selects an operation for the domain
////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
RebuildXDM( zVIEW vSubtask )
{
   zVIEW    vActiveDomain;
   zVIEW    vDomainGrp;
   zVIEW    vCM_List;
   zVIEW    vCM_List2;
   zVIEW    vXDM;
   zLONG    lDomainZKey;
   zSHORT   nRC;
   zSHORT   RESULT;
   zBOOL    bUpdated;

   bUpdated = 0;
   if ( GetViewByName( &vActiveDomain, "TZDGSRCO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if ( (bUpdated = (zBOOL) ObjectInstanceUpdatedFromFile( vActiveDomain )) != 0 )
      {
         if ( MessagePrompt( vSubtask, "DM00108",
                             "Domain Maintenance",
                             "The Domain currently active has been updated. "
                             "The active domain WILL NOT be included in "
                             "the rebuilt executable until a save is done.\n\n"
                             "Would you like to continue with the rebuild anyway?",
                             zBEEP, zBUTTONS_YESNO,
                             zRESPONSE_NO,      0 )  == zRESPONSE_YES )
         {
            return( 0 );
         }
      }
   }

   nRC = oTZDMXGPO_GetViewForXDM( vSubtask, &vXDM, zCURRENT_OI );
   if ( nRC >= 0 )
   {
      for ( nRC = SetCursorFirstEntity( vXDM, "Domain", "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vXDM, "Domain", "" ) )
      {
         DeleteEntity( vXDM, "Domain", zREPOS_PREV );
      }
   }

   nRC = RetrieveViewForMetaList( vSubtask, &vCM_List, zREFER_DOMAIN_META );
   RESULT = SetCursorFirstEntity( vCM_List, "W_MetaDef", "" );
   while ( RESULT >= zCURSOR_SET )
   {
      nRC = GetIntegerFromAttribute( &lDomainZKey, vCM_List, "W_MetaDef", "CPLR_ZKey" );

      // Use a second CM_List view for Activate since Activate will alter
      // its position.
      CreateViewFromViewForTask( &vCM_List2, vCM_List, 0 );
      nRC = ActivateMetaOI( vSubtask, &vDomainGrp, vCM_List2,
                            zREFER_DOMAIN_META,
                            zSINGLE | zLEVEL_APPLICATION );
      DropView( vCM_List2 );

      RESULT = SetCursorNextEntity( vCM_List, "W_MetaDef", "" );
      if ( nRC >= 0 )
      {
         if ( RESULT >= zCURSOR_SET )
            oTZDMSRCO_ReplaceOrAddDomToXDM( vSubtask, vDomainGrp, 0 );
         else
            oTZDMSRCO_ReplaceOrAddDomToXDM( vSubtask, vDomainGrp, 1 );
         DropMetaOI( vSubtask, vDomainGrp );
      }
   }

   return( nRC );
}



#ifdef __cplusplus
}
#endif
