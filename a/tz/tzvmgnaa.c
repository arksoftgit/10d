/////////////////////////////////////////////////////////////////////////////
//
// MODULE NAME:   tzvmgnaa.c - VML SubSystem Generator Main Module
// DESCRIPTION:   This is the source file which contains the main functions
//                for the Generator.
//
// //////////////////////////////////////////////////////////////////////////
// * Copyright (c) 1995 - 2016 QuinSoft, Inc.   All rights reserved.        *
// * Confidential and Proprietary material subject to license - do not      *
// * reproduce or disclose.  This material is an unpublished work and       *
// * is considered a trade secret belonging to the copyright holder.        *
// //////////////////////////////////////////////////////////////////////////
//
// AUTHOR:        Jeffrey S. Beam
// DATE:          1992/09/30
// API:           MicroSoft foundation classes and Windows 3.1 SDK
// ENVIRONMENT:   Windows 3.1
// REVISION:      10B    1995/08/05
//
// LAST MESSAGE ID: VM02004
//
// HISTORY:
//
//    1995/08/05: Beginning of 10B branch
//
/////////////////////////////////////////////////////////////////////////////
//
#include "tzlodopr.h"
#include "tz__oprs.h"
#include "tzvsecaa.h"
#include "tzvmlopr.hg"
#include "ZeidonOp.H"

/*
CHANGE LOG

2000.10.30 RG  Z2000
   GetViewByName: for parameter zLEVEL_TASK changed View --> 0
2000.10.25  SR  Z2000  Size of path variables
   Modified size of szXGODirectory, zXPGFileName, szPgmSrcDir, szCFileSpec
   and szTempCFileSpec in function Generate3GL
   because size of attributes ExecDir, MetaSrcDir and PgmSrcDir has
   been changed to 254 in datamodel.

2000.09.27  BL
   Modified Generate3GL for ActivateOI_FromFile without error message

1998.03.02  DGC
   Made changes to generate C++-compatable files:
      o  Change generation of zDECIMAL to ZDecimal.
      o  Add '#ifdef __cplusplus' stuff at beginning and end of each file.
*/

// local prototypes
zOPER_EXPORT zSHORT OPERATION
PreGenerateWork( zVIEW lpSubtask,
                 zPCHAR pchXPGName );
zOPER_EXPORT zSHORT OPERATION
PostGenerateC( zVIEW lpSubtask,
               zPCHAR pchCFileSpec,
               zPCHAR pchTempHeaderSpec,
               zLONG  lfCFileHandle,
               zLONG  lfHFileHandle );
zOPER_EXPORT zSHORT OPERATION
PostGenerateJava( zVIEW lpSubtask,
                  zPCHAR pchCFileSpec,
                  zPCHAR pchTempHeaderSpec,
                  zLONG  lfCFileHandle,
                  zLONG  lfHFileHandle );

zPCHAR szMessageListGenerate[ ] =
{
   "Profile Object could not be accessed, GenerateTerminating",
   "XPG or XPJ file could not be located. GenerateTerminating",
   "Application's Global Operation List could not be accessed from Configuration Management, GenerateTerminating",
   "TaskLPLR could not be accessed, GenerateTerminating",
   "TZOPSIGK.XGO could not be accessed, GenerateTerminating",
   "Could not get a list of LODs, GenerateTerminating",
   "Could not Load Error Object, GenerateTerminating",
   "Source file Meta could not be loaded, GenerateTerminating"
};

//
// OPERATION: Generate3GL
//
// DESCRIPTION: Generate3GL is the main driving function for the Generator
//
zOPER_EXPORT zSHORT OPERATION
Generate3GL( zVIEW   lpVSSubtask,        // pointer to the vml task
             zVIEW   vSubtask,           // pointer to the appl task
             zVIEW   vInSourceMeta,      // must be passed!
             zPCHAR  pchFileName,        // name of the vml file to generate
             zCPCHAR cpcGenLang,
             zLONG   lType )
{
   zVIEW  vTaskLPLR;
   zCHAR  szMsg[ 300 ];
   zCHAR  szXGODirectory[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szXPGFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szXPGName[ 33 ];
   zCHAR  szSourceFileEntity[ 32 ];
   zCHAR  szPgmSrcDir[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szCFileSpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szLPLR_Name[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szSystemIniApplName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szTempCFileSpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szOpGenType[ 2 ];
   zLONG  lfCFileHandle;
   zLONG  lfTempCFileHandle;
   zSHORT nLth;
   zSHORT nRC; // a return code to test the returns of operation calls

   g_szGenLang[ 0 ] = cpcGenLang[ 0 ];
   g_szGenLang[ 1 ] = 0;

   //-------------------------------------- Step One --------------------------------------------//
   // Initialize a global subtask so that every module has access to the generator subtask.

   lpGlobalSubtask = lpVSSubtask;

   // Get a view to the TaskLPLR to get the executable dir off of the TaskLPLR Entity.
   // Never Never Drop this View!!!
   nRC = GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );

   // If no LPLR exists get out now!
   if ( nRC != zLEVEL_TASK )
   {
      MessageSend( vSubtask, "VM02002", "VML Generator",
                   szMessageListGenerate[ 3 ],
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   nRC = GetStringFromAttribute( szCFileSpec, zsizeof( szCFileSpec ), vTaskLPLR, "LPLR", "PgmSrcDir" );
   SysConvertEnvironmentString( szPgmSrcDir, zsizeof( szPgmSrcDir ), szCFileSpec );

   //-------------------------------------- Step Two --------------------------------------------//
   // Initialize all of the global data that the generator needs to run.  Activate the source meta
   // that we want to generate for.  Activate the source meta to get the other necessary information.

   // DonC comment, 08/24/95.  We are currently assuming that the view of the source meta (which
   // would be the LOD or the Dialog) is always passed in.  We need to re-evaluate later.

   // If it was not sent in, then it's an error.
   if ( vInSourceMeta == 0 )
   {
      MessageSend( vSubtask, "VM02001", "VML Generator",
                   "Source must be passed in as parameter",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
      return( -1 );
   }
   else
   {
      g_vSourceMeta = vInSourceMeta;  // else use the one passed
   }

   SetNameForView( g_vSourceMeta, "vGenerateMeta", vSubtask, zLEVEL_TASK );

   //------------------------------------- Step Three -------------------------------------------//
   // Get the Directory for the actual source file text.  FileSpec is the fully qualified name of
   // the File.
   strcpy_s( szCFileSpec, zsizeof( szCFileSpec ), szPgmSrcDir );
   nLth = SysAppendcDirSep( szCFileSpec );

   // Get the name of the SourceFile entity in the meta object. Reuse szTempCFileSpec as a work area.
   MiGetObjectNameForView( szTempCFileSpec, g_vSourceMeta );
   if ( zstrcmp( szTempCFileSpec, "TZDGSRCO" ) == 0 )
      strcpy_s( szSourceFileEntity, zsizeof( szSourceFileEntity ), "DomainGroup" );
   else
   {
      if ( zstrcmp( szTempCFileSpec, "TZOGSRCO" ) == 0 )
         strcpy_s( szSourceFileEntity, zsizeof( szSourceFileEntity ), "GlobalOperationGroup" );
      else
         strcpy_s( szSourceFileEntity, zsizeof( szSourceFileEntity ), "SourceFile" );
   }

   if ( g_szGenLang[ 0 ] == 'J' )
   {
      /*
      strcat_s( szCFileSpec, zsizeof( szCFileSpec ), "JavaProject\\src\\" );
      nLth += 16;
      GetStringFromAttribute( szCFileSpec, zsizeof( szCFileSpec ), vTaskLPLR, "LPLR", "JavaPackageName" );
      GetStringFromAttribute( szCFileSpec + nLth, zsizeof( szCFileSpec ) - nLth, vTaskLPLR, "LPLR", "JavaPackageName" );
      nLth = SysAppendcDirSep( szCFileSpec );
      */

      // KJS 08/30/12 - Now that we are using maven, the directory structure for the java files is different.
      // I first changed the JavaPackageName but that needs to stay the same for the line:
      // "Package com.quinsoft.zencas" in the generated java.  So I have added JavaGenDir to the .ini.
      // Initialize Output for java generation files.
      GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vTaskLPLR, "LPLR", "Name" );
      strcpy_s( szSystemIniApplName, zsizeof( szSystemIniApplName ), "[App." );
      strcat_s( szSystemIniApplName, zsizeof( szSystemIniApplName ), szLPLR_Name );
      strcat_s( szSystemIniApplName, zsizeof( szSystemIniApplName ), "]" );
      SysReadZeidonIni( -1, szSystemIniApplName, "JavaGenDir", szMsg, zsizeof( szMsg ) );
      if ( szMsg[ 0 ] == 0 )
      {
         MessageSend( vSubtask, "VM02001", "VML Generator",
                      "JavaGenDir is not defined in the ini file, the java cannot be built.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, 0);
         return( -1 );
       //strcpy_s( szCFileSpec, zsizeof( szCFileSpec ), szPgmSrcDir );
       //nLth = SysAppendcDirSep( szCFileSpec );
       //strcpy_s( szCFileSpec + nLth , zsizeof( szCFileSpec ) - nLth, "JavaProject\\src\\com\\quinsoft\\" );
       //nLth += 29;
       //strcpy_s( szCFileSpec + nLth , zsizeof( szCFileSpec ) - nLth, szLPLR_Name );
      }
      else
      {
         SysConvertEnvironmentString( szCFileSpec, zsizeof( szCFileSpec ), szMsg );
      }

      nLth = SysAppendcDirSep( szCFileSpec );
   }

   GetStringFromAttribute( szCFileSpec + nLth, zsizeof( szCFileSpec ) - nLth, g_vSourceMeta, szSourceFileEntity, "Name" );

   // Need a C/Java file and a tmp file.
   if ( g_szGenLang[ 0 ] == 'J' )
   {
      if ( lType == zREFER_LOD_META ) // 2007
         strcat_s( szCFileSpec, zsizeof( szCFileSpec ), "_Object" );
      else
      if ( lType == zREFER_DIALOG_META ) // 2011
         strcat_s( szCFileSpec, zsizeof( szCFileSpec ), "_Dialog" );
      else
      if ( lType == zREFER_GOPGRP_META ) // 2014
         strcat_s( szCFileSpec, zsizeof( szCFileSpec ), "_Operation" );
      else
      {
         TraceLineI( "Make Target Unexpected Meta Type: ", lType );
         MessageSend( vSubtask, "ED00102", "Zeidon Compiler", "Unexpected meta type",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }

      strcpy_s( szTempCFileSpec, zsizeof( szTempCFileSpec ), szCFileSpec );
      strcat_s( szCFileSpec, zsizeof( szCFileSpec ), ".java" );
   }
   else
   {
      strcpy_s( szTempCFileSpec, zsizeof( szTempCFileSpec ), szCFileSpec );
      strcat_s( szCFileSpec, zsizeof( szCFileSpec ), ".c" );
   }

   strcat_s( szTempCFileSpec, zsizeof( szTempCFileSpec ), ".tmp" );

   //-------------------------------------- Step Four -------------------------------------------//
   // Build the XPG name / Load the File.

   // Get the ExecDir off of the LPLR Entity.  This will be the directory where the xpg is now or will be saved to.
   nRC = GetStringFromAttribute( szMsg, zsizeof( szMsg ), vTaskLPLR, "LPLR", "ExecDir" );
   SysConvertEnvironmentString( szXPGFileName, zsizeof( szXPGFileName ), szMsg );

   // Be sure the dir name is terminated with the delimiter.
   nLth = SysAppendcDirSep( szXPGFileName );

   // Build the information needed to load the XPG File.  Append the xpg name onto the target.  This is the name of the ExecComposite.
   GetStringFromAttribute( szXPGFileName + nLth, zsizeof( szXPGFileName ) - nLth, g_vSourceMeta, szSourceFileEntity, "Name" );

   // Concat the Extension onto the directory.
   if ( g_szGenLang[ 0 ] == 'J' )
      strcat_s( szXPGFileName, zsizeof( szXPGFileName ), ".XPJ" );
   else
      strcat_s( szXPGFileName, zsizeof( szXPGFileName ), ".XPG" );

   //-------------------------------------- Step Five -------------------------------------------//
   // Activate the XPG object.  We'll first drop the current one if it is active.  It should be kept around for debugging purposes.
   if ( GetViewByName( &g_lpPIView, "_GenFromXPG", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( g_lpPIView );

   // Activate a view to the "Parsed Instance".
   nRC = ActivateOI_FromFile( &g_lpPIView, "TZVSPOOO", lpVSSubtask, szXPGFileName, zSINGLE | zNOI_OKAY );
   if ( nRC )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), szMessageListGenerate[ 1 ] );
      strcat_s( szMsg, zsizeof( szMsg ), " file: " );
      strcat_s( szMsg, zsizeof( szMsg ), szXPGFileName );
      MessageSend( vSubtask, "VM02003", "VML Generator",
                   szMsg, // szMessageListGenerate[ 1 ],
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Name it for debugging.
   SetNameForView( g_lpPIView, "_GenFromXPG", lpVSSubtask, zLEVEL_SUBTASK );

   // Get XPG name.
   GetStringFromAttribute( szXPGName, zsizeof( szXPGName ), g_lpPIView, "VML_XSource", "Name" );

   //-------------------------------------- Step Six --------------------------------------------//
   // Load and get access to the global operation list.
   nRC = RetrieveViewForMetaList( vSubtask, &g_lpGOListView, zREFER_GO_META );

   if ( nRC < 0 ) //  failed
      g_lpGOListView = 0;

   // Get the dir name of the Zeidon tools so that we get the XGO directory.
   zgGetZeidonToolsDir( vSubtask, szXGODirectory, zAPPL_DIR_OBJECT );

   // The name of the system core operation list.
   strcpy_s( szXGODirectory, zsizeof( szXGODirectory ), "TZOPSIGK.XGO" );

   // Now that we have the name, try to load the operation list.
   nRC = ActivateOI_FromFile( &g_lpZOListView, "TZOPGRPO", lpVSSubtask, szXGODirectory, zSINGLE | zNOI_OKAY );

   if ( nRC < 0 ) //  failed
   {
      // Drop all views already retrieved so they don't hang around.
      g_lpZOListView = 0;

      DropView( g_lpGOListView );
   // DropView( g_lpPIView );

      MessageSend( vSubtask, "VM02004", "VML Generator",
                   szMessageListGenerate[ 4 ],
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   SetNameForView( g_lpZOListView, "_GenTZOPGRPO", lpVSSubtask, zLEVEL_SUBTASK );

   // KJS 04/23/13 - I am testing whether it is feasible to have two different zeidon operations one for c generation and one for java.
   // Loop through operations and delete the ones that are not for the language we are currently generating.
   nRC = SetCursorFirstEntity( g_lpZOListView, "Operation", "" );
   while ( nRC >= zCURSOR_SET )
   {
      szOpGenType[ 0 ] = 0;
      GetStringFromAttribute( szOpGenType, zsizeof( szOpGenType ), g_lpZOListView, "Operation", "GenerationType" );
     if ( szOpGenType[0] == 'C' && g_szGenLang[ 0 ] == 'J' )
     {
        DropEntity( g_lpZOListView, "Operation", zREPOS_NONE );
     }
     else
     if ( szOpGenType[0] == 'J' && g_szGenLang[ 0 ] == 'C' )
     {
        DropEntity( g_lpZOListView, "Operation", zREPOS_NONE );
     }
      nRC = SetCursorNextEntity( g_lpZOListView, "Operation", "" );
   }

   // Open the files.
   lfCFileHandle = SysOpenFile( vSubtask, szCFileSpec, COREFILE_WRITE );
   lfTempCFileHandle = SysOpenFile( vSubtask, szTempCFileSpec, COREFILE_WRITE );

   nRC = PreGenerateWork( vSubtask, szXPGName ); // set Jeff's globals

   // If stuff in PreGenerateWork failed, pass the bad news back up line.
   if ( nRC < 0 )
   {
      // Drop views before bailing out.
      DropView( g_lpGOListView );
      DropView( g_lpZOListView );
   // DropView( g_lpPIView );
      return( -1 );
   }

   TraceLineS( "Generating file: ", szCFileSpec );
   if ( g_szGenLang[ 0 ] == 'J' )
   {
      GenerateJavaSource( vSubtask, pchFileName, szXPGName, lfCFileHandle, lfTempCFileHandle, lType );
      nRC = PostGenerateJava( vSubtask, szCFileSpec, szTempCFileSpec, lfCFileHandle, lfTempCFileHandle );
   }
   else
   {
      GenerateC_Source( vSubtask, pchFileName, szXPGName, lfCFileHandle, lfTempCFileHandle );
      nRC = PostGenerateC( vSubtask, szCFileSpec, szTempCFileSpec, lfCFileHandle, lfTempCFileHandle );
   }

   // If something in PostGeneratefailed, pass the bad news back up line.
   if ( nRC < 0 )
   {
      // Drop views before bailing out.
      DropView( g_lpGOListView );
      DropView( g_lpZOListView );
   // DropView( g_lpPIView );
      return( -1 );
   }

   DropView( g_lpGOListView );
   DropView( g_lpZOListView );
// DropView( g_lpPIView );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
PreGenerateWork( zVIEW vSubtask,
                 zPCHAR lpszXPGName )
{
   // set Jeff's globals
   g_nCheckParms = 0;
   g_nInParmList = 0;
   return( 0 );
}

// This will copy the generated source (currently held in the temporary C file) underneath the
// defines and protos (currently held in the C file). This routine will delete all temporary files.
zOPER_EXPORT zSHORT OPERATION
PostGenerateC( zVIEW vSubtask,
               zPCHAR szCFileSpec,
               zPCHAR szTempCFileSpec,
               zLONG  lfCFileHandle,
               zLONG  lfTempCFileHandle )
{
   zBOOL  bDone = FALSE;
   zPCHAR pchLine;
   zSHORT nRC;

   // Combine the C file with the temp C file.

   // Close temp C file and reopen it for reading.
   nRC = SysCloseFile( vSubtask, lfTempCFileHandle, 0 );
   lfTempCFileHandle = SysOpenFile( vSubtask, szTempCFileSpec, COREFILE_READ );

   // Concat temp C file to end of C file.
   bDone = FALSE;
   while ( bDone == FALSE )  // while not done
   {
      // Read a line from temp C file.  If eof, stop copying.
      if ( SysReadLine( vSubtask, (zCOREMEM) &pchLine, lfTempCFileHandle ) <= 0 )
      {
         bDone = TRUE;
      }
      else // not eof
      {
         // Copy line to temp header file.
         SysWriteLine( vSubtask, lfCFileHandle, pchLine );
      }
   } // end of while

   // Finish the file by adding the "#ifdef __cplusplus..." stuff.
   SysWriteLine( vSubtask, lfCFileHandle, " " );
   SysWriteLine( vSubtask, lfCFileHandle, "#ifdef __cplusplus" );
   SysWriteLine( vSubtask, lfCFileHandle, "}" );
   SysWriteLine( vSubtask, lfCFileHandle, "#endif" );

   // Delete the temp C file
   // DM - instead of using the dos 'remove' command to delete the old C file, we use
   // our own system open with the delete option. This avoids problems with the short
   // pointers that 'remove' expects arrives, we can get rid of the following 'strcpy_s'.
   nRC = SysCloseFile( vSubtask, lfTempCFileHandle, 0 );
   lfTempCFileHandle = SysOpenFile( vSubtask, szTempCFileSpec, COREFILE_DELETE );

   // Close the completed C file.
   nRC = SysCloseFile( vSubtask, lfCFileHandle, 0 );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
PostGenerateJava( zVIEW vSubtask,
                  zPCHAR szCFileSpec,
                  zPCHAR szTempJavaFileSpec,
                  zLONG  lfCFileHandle,
                  zLONG  lfTempCFileHandle )
{
   zBOOL  bDone = FALSE;
   zPCHAR pchLine;
   zSHORT nRC;

   // Combine the Java file with the temp Java file.

   // Close temp Java file and reopen it for reading.
   nRC = SysCloseFile( vSubtask, lfTempCFileHandle, 0 );
   lfTempCFileHandle = SysOpenFile( vSubtask, szTempJavaFileSpec, COREFILE_READ );

   // Concat temp Java file to end of C file.
   bDone = FALSE;
   while ( bDone == FALSE )  // while not done
   {
      // Read a line from temp Java file.  If eof, stop copying.
      if ( SysReadLine( vSubtask, (zCOREMEM) &pchLine, lfTempCFileHandle ) <= 0 )
      {
         bDone = TRUE;
      }
      else // not eof
      {
         // Copy line to temp header file.
         SysWriteLine( vSubtask, lfCFileHandle, pchLine );
      }
   } // end of while

   // Delete the temp Java file
   // DM - instead of using the dos 'remove' command to delete the old Java file, we use
   // our own system open with the delete option. This avoids problems with the short
   // pointers that 'remove' expects arrives, we can get rid of the following 'strcpy_s'.
   nRC = SysCloseFile( vSubtask, lfTempCFileHandle, 0 );
   lfTempCFileHandle = SysOpenFile( vSubtask, szTempJavaFileSpec, COREFILE_DELETE );

   // Close the completed Java file.
   nRC = SysCloseFile( vSubtask, lfCFileHandle, 0 );

   return( 0 );
}
