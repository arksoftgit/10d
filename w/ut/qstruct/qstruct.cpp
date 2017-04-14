/////////////////////////////////////////////////////////////////////////////
// QSTRUCT.CPP     - written by Doug Sorensen       - create date 06/05/1991
//                   (C)  Arksoft Inc., 1989-2015   - last update 11/11/2015
//
// This program generates a C structure (aligned on 4-byte boundaries) for
// a given (or ALL) entity within an object definition.
//
// Input Parms:
//    1. OBJECT definition file name
//    2. /An - Align attributes on an n-byte boundary
//    3. /B - Base (abstract) entity list
//    4. /D - Derived (subtype) entity list
//    5. /E - Entity name for which to build struct (defaults to ALL)
//    6. /J - Generate java class + setters/getters
//    7. /M - List attribute names which match an entity name
//    8. /O - output generated struct file (defaults to Entity.FIL)
//    9. /P - generate typedef for pointer to the structure
//   10. /Rsss - remove line with specified string (sss)
//   11. /S - generate struct size int
//
// Outputs:
//    1. File with structure for specified entity
//
/////////////////////////////////////////////////////////////////////////////

#define PGM_VERSION " v4.54 "
#include "..\arkutil.h"

//#define  READFILE      "r"    // read only
//#define  WRITEFILE     "w"    // write only (overwrite existing file)

//typedef const char *   zCPCHAR;
//typedef char *         zPCHAR;

#define mDeleteInit( p ) { if ( p ) { delete( p ); p = 0; } }
#define mDeleteInitA( p ) { if ( p ) { delete [] p; p = 0; } }

FILE *
fnOpenFile( char *pchBuff,
            char *pchMode );
short
qftoken( char  *szInputBuffer,      // input buffer
         char  *szTokenBuffer,      // token buffer
         short nMaxTokenLth,        // maximum length of a token
         short nMaxTokens );        // maximum number of tokens

void
fnWriteEntity( char *szObjectEntityDef );

void
fnWriteAttribute( char  chType,
                  char  *pchEntityName,
                  char  *pchAttributeName,
                  short nLth,
                  zBOOL bMatch );

void
fnWriteStructRec( char *szBuffer );

void
fnWriteAbstract( FILE *pXOD, short nBaseSubtype );

void
fnFinishUpJavaEntity( );

/////////////////////////////////////////////////////////////////////////////
// Class definition for CSListAttributeType (simple single-linked list).
//
// a simpleton single-link list
class CLinkAttributeType
{
public:
   CLinkAttributeType( zCPCHAR cpcAttribute, zCPCHAR cpcType );
   ~CLinkAttributeType( );

   zPCHAR m_pchAttribute;
   zPCHAR m_pchType;
   zLONG  m_lAttributeLth;
   zLONG  m_lTypeLth;
   CLinkAttributeType *m_pNext;
};

// manage a simpleton single-link list
class CSListAttributeType
{
public:
   CSListAttributeType( zCPCHAR cpcEntityName );
   ~CSListAttributeType( );

   CLinkAttributeType * Add( zCPCHAR cpcAttribute, zCPCHAR cpcType );    // return ptr if added ... 0 otw
   zLONG GetCount( ) { return( m_lCnt ); }
   CLinkAttributeType * GetFirstLink( ) { return( m_pHead ); }
   zCPCHAR GetEntityName( ) { return m_szEntityName; }

private:
   char m_szEntityName[ 33 ];
   CLinkAttributeType *m_pHead;
   CLinkAttributeType *m_pTail;
   zLONG  m_lCnt;
};

// this next set of defines is a copy of what is in the "struct.tok" file
#define eENTITY         0
#define eCHILDENTITY    1
#define eATTRIB         2
#define aNAME           3
#define aLTH            4
#define aTYPE           5

#define  TOKEN_DELIMITERS  " \t\n\r"

#define MAXTOKENLTH    20

#define ENTITY_NOTFOUND 0
#define ENTITY_PROCESS  1
#define ENTITY_FOUND    2
#define ENTITY_WRITTEN  3
#define ATTRIB_NOTFOUND 0
#define ATTRIB_FOUND    1

#define TYPE_STRING    'S'
#define TYPE_LONG      'L'
#define TYPE_BLOB      'B'
#define TYPE_INTEGER   'I'
#define TYPE_CHAR      'C'
#define TYPE_DECIMAL   'M'

FILE  *pStructFile;         // generated source file pointer
FILE  *pXOD;                // revised LOD file pointer
char  szStructFile[ 128 ] = "STRUCT.FIL";
char  szXOD_File[ 128 ] = "XOD.FIL";
short nNumberRecordsWritten;
char  szTokenBuffer[ 256 ];
CSList *g_pEntityList = 0;
CSList *g_pBaseEntityList = 0;
CSList *g_pSubtypeEntityList = 0;
zBOOL   g_bJava = FALSE;
CSListAttributeType *g_pListAttributeType = 0;

zBOOL  bTypedef = FALSE;
zBOOL  bAllEntities = FALSE;
zSHORT nAlign = 0;

int
main( int  argc,
      char *argv[ ] )
{
   FILE  *pObjectDefFile;         // object definition source file pointer
   char  szObjectDefFile[ 256 ];
   char  szObjectDefBase[ 256 ];
   char  szBuffer[ 256 ];
   char  szOrigBuffer[ 256 ];
   char  szEntityName[ 33 ];
   char  szAttributeName[ 33 ];
   char  chType;
   short nLth;
   char  *pchToken;
   short nTotalRecordCount;
   short nTokenNumber;
   short nTokenCnt;
   char  szTempString[ 256 ];
   char  szObjectEntityDef[ 256 ];
   short nObjectDef = 0;
   short nAttribute = 0;
   short nEntity = 0;
   zBOOL bMatch = FALSE;
   short nOutput = 0;
   short nBaseSubtype;     // 0 - no;  1 - Base;  2 - Subtype
   short nRemove = 0;
   zBOOL bChange = TRUE;
   zBOOL bStructSize = FALSE;
#ifdef DEBUG2
   BOOL  bDebug = FALSE;
#endif

   char  *pch;
   short k;

   for ( k = 1; k < argc; k++ )
   {
      if ( argv[ k ][ 0 ] == '/' || argv[ k ][ 0 ] == '-' )
      {
         if ( argv[ k ][ 1 ] == 'A' || argv[ k ][ 1 ] == 'a' )
         {
            nAlign = atoi( argv[ k ] + 2 );
         }
         else
         if ( argv[ k ][ 1 ] == 'B' || argv[ k ][ 1 ] == 'b' )
         {
            if ( g_pBaseEntityList == 0 )
               g_pBaseEntityList = new CSList;

            g_pBaseEntityList->AddToList( argv[ k ] + 2 );
         }
         else
         if ( argv[ k ][ 1 ] == 'D' || argv[ k ][ 1 ] == 'd' )
         {
            if ( g_pSubtypeEntityList == 0 )
               g_pSubtypeEntityList = new CSList;

            g_pSubtypeEntityList->AddToList( argv[ k ] + 2 );
         }
         else
         if ( argv[ k ][ 1 ] == 'E' || argv[ k ][ 1 ] == 'e' )
         {
            if ( argv[ k ][ 2 ] )   // a name is required
               nEntity = k;
            else
            {
               cerr << "Entity name is required for switch: " << argv[ k ] << endl;
               nObjectDef = 0;
               break;
            }
         }
         else
         if ( argv[ k ][ 1 ] == 'J' || argv[ k ][ 1 ] == 'j' )
         {
            g_bJava = TRUE;
         }
         else
         if ( argv[ k ][ 1 ] == 'M' || argv[ k ][ 1 ] == 'm' )
         {
            bMatch = TRUE;
            g_pEntityList = new CSList;
         }
         else
         if ( argv[ k ][ 1 ] == 'O' || argv[ k ][ 1 ] == 'o' )
         {
            if ( argv[ k ][ 2 ] )   // a name is required
               nOutput = k;
            else
            {
               cerr << "Output file name is required for switch: " << argv[ k ] << endl;
               nObjectDef = 0;
               break;
            }
         }
         else
         if ( argv[ k ][ 1 ] == 'P' || argv[ k ][ 1 ] == 'p' )
         {
            bTypedef = TRUE;
         }
         else
         if (argv[k][1] == 'R' || argv[k][1] == 'r')
         {
            if (argv[k][2])
            {
               nRemove = k;
               bChange = FALSE;
            }
         }
         else
         if (argv[k][1] == 'S' || argv[k][1] == 's')
         {
            bStructSize = TRUE;
         }
         else
         {
            if ( argv[ k ][ 1 ] != '?' )
               cerr << "Invalid switch - " << argv[ k ] << endl;

            nObjectDef = 0;
            break;
         }
      }
      else
      if ( nObjectDef == 0 )
      {
         nObjectDef = k;
      }
      else
      {
         cerr << "Too many arguments - " << argv[ k ] << endl;
         nObjectDef = 0;
         break;
      }
   }

   if ( (g_pBaseEntityList && g_pSubtypeEntityList == 0) ||
        (g_pBaseEntityList == 0 && g_pSubtypeEntityList) )
   {
      cerr << "Base and subtype lists must both be specified" << endl;
      nObjectDef = 0;
   }

   // If there was an error in the command line arguments.
   if ( nObjectDef == 0 )
   {
      cerr << argv[ 0 ] << "  v" << PGM_VERSION << "\n";
      cerr << "syntax:  " << argv[ 0 ]
      << " object_def_file [/A /B /D /E /M /O /P /?]\n"
      << "\n"
      << "Used to create a C struct for a given entity within an object definition\n"
      << "One positional argument is required\n"
      << "  object_def_file\n"
      << "Optional switches\n"
      << " /An - Align attribute fields on an n-byte boundary\n"
      << " /B - Base (abstract) entity list ... will rebuild XOD\n"
      << " /D - Derived (subtype) entity list ... will rebuild XOD\n"
      << " /E - Entity name for which to build structure (defaults to 'ALL')\n"
      << " /J - Generate java class + setters/getters\n"
      << " /M - check for attribute names that match an entity name\n"
      << " /O - output file for generated structure (defaults to 'Entity.FIL')\n"
      << " /P - generate typedef for pointer to the structure\n"
      << " /Rs - remove lines containing specified string\n"
      << "\n****** Processing Terminated ******\n"
      << endl;

      return( 1 );
   }

   _fullpath( szObjectDefFile, argv[ nObjectDef ], sizeof( szObjectDefFile ) );

   // Get just the base name of the object definition file.
   szObjectDefBase[ 0 ] = 'z';
   strcpy_s( szObjectDefBase + 1, sizeof( szObjectDefBase ) - 1, argv[ nObjectDef ] );
   pch = strrchr( szObjectDefBase, '\\' );
   if ( pch )
      strcpy_s( szObjectDefBase + 1, sizeof( szObjectDefBase ) - 1, pch + 1 );

   pch = strchr( szObjectDefBase, '.' );
   if ( pch )
      *pch = 0;

   _strupr_s( szObjectDefBase + 1, sizeof( szObjectDefBase ) - 1 );

   if ( nEntity )  // entity name switch
   {
      strcpy_s( szEntityName, sizeof( szEntityName ), argv[ nEntity ] + 2 );
      _strupr_s( szEntityName, sizeof( szEntityName ) );
      if ( strcmp( szEntityName, "ALL" ) == 0 )
         bAllEntities = TRUE;
      else
         bAllEntities = FALSE;
   }
   else
   {
      strcpy_s( szEntityName, sizeof( szEntityName ), "ALL" );
      bAllEntities = TRUE;
   }

   if ( nOutput )  // output file for generated struct
      strcpy_s( szStructFile, sizeof( szStructFile ), argv[ nOutput ] + 2 );
   else
   {
      strcpy_s( szStructFile, sizeof( szStructFile ), szEntityName );
      strcat_s( szStructFile, sizeof( szStructFile ), ".FIL" );
   }

   strcpy_s( szTokenBuffer, sizeof( szTokenBuffer ), "eENTITY" );
   strcpy_s( szTokenBuffer + 20, sizeof( szTokenBuffer ) - 20, "eCHILDENTITY" );
   strcpy_s( szTokenBuffer + 40, sizeof( szTokenBuffer ) - 40, "eATTRIB" );
   strcpy_s( szTokenBuffer + 60, sizeof( szTokenBuffer ) - 60, "aNAME" );
   strcpy_s( szTokenBuffer + 80, sizeof( szTokenBuffer ) - 80, "aLTH" );
   strcpy_s( szTokenBuffer + 100, sizeof( szTokenBuffer ) - 100, "aTYPE" );
   strcpy_s( szTokenBuffer + 120, sizeof( szTokenBuffer ) - 120, "" );

   nTokenCnt = 6;

#ifdef DEBUG2
{
   char szTempToken[ 256 ];
   short idx, j, k;                          // local indexes

   cerr << "TokenCount = " << nTokenCnt << endl;
   for ( idx = 0; idx < nTokenCnt; idx++ )
   {
      j = idx * MAXTOKENLTH;
      for ( k = 0; k < MAXTOKENLTH; k++, j++ )
        szTempToken[ k ] = szTokenBuffer[ j ];

      szTempToken[ MAXTOKENLTH ] = '\0';
      cerr << "Token " << idx << " = " << szTempToken << endl;
   }
}
#endif

   pObjectDefFile = fnOpenFile( szObjectDefFile, READFILE );
   pStructFile = fnOpenFile( szStructFile, WRITEFILE );
   if ( g_pBaseEntityList || nRemove )
      pXOD = fnOpenFile( szXOD_File, WRITEFILE );


   strcpy_s( szBuffer, sizeof( szBuffer ), "// " );
   strcat_s( szBuffer, sizeof( szBuffer ), argv[ 0 ] );
   strcat_s( szBuffer, sizeof( szBuffer ), "  build " );
   strcat_s( szBuffer, sizeof( szBuffer ), PGM_VERSION );
   strcat_s( szBuffer, sizeof( szBuffer ), "\n\n" );
   _strlwr_s( szBuffer, sizeof( szBuffer ) );
   fputs( szBuffer, pStructFile );
   if ( g_bJava )
   {
   }
   else
   {
      strcpy_s( szBuffer, sizeof( szBuffer ), "#ifndef __" );
      strcat_s( szBuffer, sizeof( szBuffer ), szObjectDefBase + 1 );
      strcat_s( szBuffer, sizeof( szBuffer ), "_hst__   // Sentry, use file only if it's not already included\n" );
      _strlwr_s( szBuffer, sizeof( szBuffer ) );
      fputs( szBuffer, pStructFile );

      strcpy_s( szBuffer, sizeof( szBuffer ), "#define __" );
      strcat_s( szBuffer, sizeof( szBuffer ), szObjectDefBase + 1 );
      strcat_s( szBuffer, sizeof( szBuffer ), "_hst__\n\n" );
      _strlwr_s( szBuffer, sizeof( szBuffer ) );
      fputs( szBuffer, pStructFile );

   // fputs( "// #define DEBUG_LODSTRUCT\n", pStructFile );  always use check byte!
   }

   nTotalRecordCount = 0;
   nNumberRecordsWritten= 0;
   nEntity = ENTITY_NOTFOUND;     // entity in process indicator
   nAttribute = ATTRIB_NOTFOUND;  // attribute in process indicator
   nBaseSubtype = 0;     // 0 - no;  1 - Base;  2 - Subtype
   szOrigBuffer[ 0 ] = 0;

   fgets( szBuffer, BUFSIZE, pObjectDefFile );
   while ( feof( pObjectDefFile ) == 0 )
   {
      nTotalRecordCount++;
      if ( nRemove && strstr( szBuffer, argv[ nRemove ] + 2 ) )
      {
         szBuffer[ 0 ] = 0;  // knock out this line
         bChange = TRUE;
      }

      if ( pXOD )
      {
         strcpy_s( szOrigBuffer, sizeof( szOrigBuffer ), szBuffer );
      // cout << szOrigBuffer << endl;
      }

#ifdef DEBUG2
      if ( bDebug )
         cerr << szBuffer << endl;
#endif

      nTokenNumber = qftoken( szBuffer, szTokenBuffer, MAXTOKENLTH, nTokenCnt );

      switch( nTokenNumber )
      {
         case eENTITY:
         case eCHILDENTITY:
            if ( pXOD && nBaseSubtype )
            {
               fnWriteAbstract( pXOD, nBaseSubtype );
               nBaseSubtype = 0;
            }

            if ( nEntity == ENTITY_WRITTEN )
            {
               if ( bAllEntities == FALSE )
                  goto END_ENTITY_label;
            }

            if ( nAttribute )
            {
               fnWriteAttribute( chType, szEntityName, szAttributeName, nLth, bMatch );
               nAttribute = ATTRIB_NOTFOUND;
            }

            if ( nEntity == ENTITY_WRITTEN )
               fnWriteEntity( szObjectEntityDef );

            nEntity = ENTITY_PROCESS;
            break;

         case eATTRIB:
            if ( pXOD && nBaseSubtype )
            {
               fnWriteAbstract( pXOD, nBaseSubtype );
               nBaseSubtype = 0;
            }

            if ( nEntity == ENTITY_FOUND || nEntity == ENTITY_WRITTEN )
            {
               if ( nEntity == ENTITY_FOUND )
               {
                  if ( g_bJava )
                  {
                     if ( g_pListAttributeType )
                        fnFinishUpJavaEntity( );

                     mDeleteInit( g_pListAttributeType );
                     g_pListAttributeType = new CSListAttributeType( szEntityName );
 
                     fnWriteStructRec( "/**" );
                     fnWriteStructRec( "This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr)." );
                     fnWriteStructRec( "" );
                     fnWriteStructRec( "Zeidon Dr is free software: you can redistribute it and/or modify" );
                     fnWriteStructRec( "it under the terms of the GNU Lesser General Public License as published by" );
                     fnWriteStructRec( "the Free Software Foundation, either version 3 of the License, or" );
                     fnWriteStructRec( "(at your option) any later version." );
                     fnWriteStructRec( "" );
                     fnWriteStructRec( "Zeidon Dr is distributed in the hope that it will be useful," );
                     fnWriteStructRec( "but WITHOUT ANY WARRANTY; without even the implied warranty of" );
                     fnWriteStructRec( "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" );
                     fnWriteStructRec( "GNU Lesser General Public License for more details." );
                     fnWriteStructRec( "" );
                     fnWriteStructRec( "You should have received a copy of the GNU Lesser General Public License" );
                     fnWriteStructRec( "along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>." );
                     fnWriteStructRec( "" );
                     fnWriteStructRec( "Copyright © 2011 - 2016 Arksoft, Inc." );
                     fnWriteStructRec( "*/" );
                     fnWriteStructRec( "" );
                     fnWriteStructRec( "package com.quinsoft.zeidon.gui;" );
                     fnWriteStructRec( "" );
                     fnWriteStructRec( "import com.quinsoft.zeidon.View;" );
                     fnWriteStructRec( "import com.quinsoft.zeidon.EntityCursor;" );
                     fnWriteStructRec( "import com.quinsoft.zeidon.Blob;" );
                     fnWriteStructRec( "" );
                     strcpy_s( szTempString, sizeof( szTempString ), "public class " );
                     strcat_s( szTempString, sizeof( szTempString ), szEntityName );
                     strcat_s( szTempString, sizeof( szTempString ), "Impl implements " );
                     strcat_s( szTempString, sizeof( szTempString ), szEntityName );
                     strcat_s( szTempString, sizeof( szTempString ), "" );
                     fnWriteStructRec( szTempString );
                     fnWriteStructRec( "{" );
                  // fnWriteStructRec( "   protected static final int zCALL_ERROR = -16;" );
                  // fnWriteStructRec( "" );
                  }
                  else
                  {
                     strcpy_s( szTempString, sizeof( szTempString ), "typedef struct tag" );
                     strcpy_s( szObjectEntityDef, sizeof( szObjectEntityDef ), szObjectDefBase );
                     strcat_s( szObjectEntityDef, sizeof( szObjectEntityDef ), "_" );
                     strcat_s( szObjectEntityDef, sizeof( szObjectEntityDef ), szEntityName );
                     strcat_s( szObjectEntityDef, sizeof( szObjectEntityDef ), "_DEF" );
                     strcat_s( szTempString, sizeof( szTempString ), szObjectEntityDef );
                     fnWriteStructRec( szTempString );
                     strcpy_s( szTempString, sizeof( szTempString ), "{" );
                     fnWriteStructRec( szTempString );
                  }
                  if ( bStructSize )
                  {
                     strcpy_s( szTempString, sizeof( szTempString ), "zLONG  lStructSize;\n" );
                     fnWriteStructRec( szTempString );
                  }

                  if ( bMatch && g_pEntityList )
                     g_pEntityList->Add( szEntityName );

                  nEntity = ENTITY_WRITTEN;
               }

               if ( nAttribute )
               {
                  fnWriteAttribute( chType, szEntityName, szAttributeName, nLth, bMatch );
                  chType = 0;
                  szAttributeName[ 0 ] = 0;
                  nLth = 0;
               }

               nAttribute = ATTRIB_FOUND;
            }

            break;

         case aNAME:
            if ( nEntity == ENTITY_PROCESS )
            {
               zPCHAR pchNextToken = NULL;

               pchToken = strtok_s( szBuffer + 6, TOKEN_DELIMITERS, &pchNextToken );
               if ( bAllEntities )
               {
                  strcpy_s( szEntityName, sizeof( szEntityName ), pchToken );
                  nEntity = ENTITY_FOUND;
                  if ( pXOD )
                  {
                     if ( g_pBaseEntityList->Find( szEntityName ) )
                        nBaseSubtype = 1;
                     else
                     if ( g_pSubtypeEntityList->Find( szEntityName ) )
                        nBaseSubtype = 2;
                     else
                        nBaseSubtype = 0;
                  }
               }
               else
               if ( strcmp( szEntityName, pchToken ) == 0 )
                  nEntity = ENTITY_FOUND;
               else
                  nEntity = ENTITY_NOTFOUND;
            }
            else
            if ( nEntity == ENTITY_WRITTEN && nAttribute )
            {
               zPCHAR pchNextToken = NULL;

               pchToken = strtok_s( szBuffer + 6, TOKEN_DELIMITERS, &pchNextToken );
               strcpy_s( szAttributeName, sizeof( szAttributeName ), pchToken );
#ifdef DEBUG2
               if ( strcmp( szAttributeName, "SB_ActionDisabling" ) == 0 )
                  bDebug = TRUE;
               else
                  bDebug = FALSE;
#endif
            }

            break;

         case aTYPE:
            if ( nAttribute )
            {
               zPCHAR pchNextToken = NULL;

               pchToken = strtok_s( szBuffer + 6, TOKEN_DELIMITERS, &pchNextToken );
               chType = *pchToken;
            }

            break;

         case aLTH:
            if ( nAttribute )
            {
               zPCHAR pchNextToken = NULL;

               pchToken = strtok_s( szBuffer + 5, TOKEN_DELIMITERS, &pchNextToken );
               nLth = atoi( pchToken ) + 1;

               if ( nAlign && (nLth % sizeof( void * )) )
                  nLth += sizeof( void * ) - (nLth % sizeof( void * ));
            }

            break;

         default:
         {
            if ( szBuffer[ 0 ] == 'e' )
            {
               if ( nAttribute == ATTRIB_FOUND )
               {
                  fnWriteAttribute( chType, szEntityName, szAttributeName, nLth, bMatch );
                  nAttribute = ATTRIB_NOTFOUND;
               }

               if ( nEntity == ENTITY_WRITTEN )
               {
                  fnWriteEntity( szObjectEntityDef );
                  nEntity = ENTITY_PROCESS;
               }
            }
         }
      }

      if ( pXOD )
      {
         fputs( szOrigBuffer, pXOD );
         szOrigBuffer[ 0 ] = 0;
      }

      fgets( szBuffer, BUFSIZE, pObjectDefFile );
      if ( pXOD && nBaseSubtype && (szBuffer[ 0 ] == '\n' || szBuffer[ 0 ] == '\r') )
      {
         fnWriteAbstract( pXOD, nBaseSubtype );
         nBaseSubtype = 0;
      }

   }   // end of:   while ( feof( pObjectDefFile ) == 0 )

   END_ENTITY_label:

   if ( pXOD )
   {
      if ( szOrigBuffer[ 0 ] )
         fputs( szOrigBuffer, pXOD );

      if ( nBaseSubtype )
      {
         fnWriteAbstract( pXOD, nBaseSubtype );
         nBaseSubtype = 0;
      }

      fclose( pXOD );
      if ( bChange )
         cout << "\nNew XOD file written: " << szXOD_File << endl;
      else
         _unlink( szXOD_File );
   }

   if ( nAttribute == ATTRIB_FOUND )
      fnWriteAttribute( chType, szEntityName, szAttributeName, nLth, bMatch );

   if ( nEntity == ENTITY_WRITTEN )
      fnWriteEntity( szObjectEntityDef );

   fclose( pObjectDefFile );

   cout << "\nNumber records read = " << nTotalRecordCount
        << "\nOutput file: " << szStructFile
        << "\nNumber records written = " << nNumberRecordsWritten << endl;

   mDeleteInit( g_pEntityList );
   if ( pStructFile )
   {
      if ( g_bJava )
      {
         if ( g_pListAttributeType )
            fnFinishUpJavaEntity( );

         mDeleteInit( g_pListAttributeType );
      }
      else
      {
         strcpy_s( szBuffer, sizeof( szBuffer ), "#endif   // #define __" );
         strcat_s( szBuffer, sizeof( szBuffer ), szObjectDefBase + 1 );
         strcat_s( szBuffer, sizeof( szBuffer ), "_hst__\n" );
         _strlwr_s( szBuffer, sizeof( szBuffer ) );
         fputs( szBuffer, pStructFile );
         fclose( pStructFile );
      }
   }

   return( 0 );
}

void
fnWriteEntity( char *szObjectEntityDef )
{
   char szTempString[ 256 ];

   szTempString[ 0 ] = 0;
   fnWriteStructRec( szTempString );

   if ( g_bJava )
   {
   // if ( g_pListAttributeType )
   //    fnFinishUpJavaEntity( );

   // mDeleteInit( g_pListAttributeType );
   // g_pListAttributeType = new CSListAttributeType( szObjectEntityDef );
   }
   else
   {
   // strcpy_s( szTempString, sizeof( szTempString ), "#ifdef DEBUG_LODSTRUCT" ); always use check byte!
   // fnWriteStructRec( szTempString );
      strcpy_s( szTempString, sizeof( szTempString ), "unsigned char CheckByte;" );
      fnWriteStructRec( szTempString );
   // strcpy_s( szTempString, sizeof( szTempString ), "#endif" );
   // fnWriteStructRec( szTempString );
      szTempString[ 0 ] = 0;
      fnWriteStructRec( szTempString );

      strcpy_s( szTempString, sizeof( szTempString ), "} " );
      strcat_s( szTempString, sizeof( szTempString ), szObjectEntityDef );
      strcat_s( szTempString, sizeof( szTempString ), ";" );
      fnWriteStructRec( szTempString );

      if ( bTypedef )
      {
         szTempString[ 0 ] = 0;
         fnWriteStructRec( szTempString );
         strcpy_s( szTempString, sizeof( szTempString ), "typedef " );
         strcat_s( szTempString, sizeof( szTempString ), szObjectEntityDef );
         strcat_s( szTempString, sizeof( szTempString ), "  *p" );
         strcat_s( szTempString, sizeof( szTempString ), szObjectEntityDef );
         strcat_s( szTempString, sizeof( szTempString ), ";" );
         fnWriteStructRec( szTempString );
      }
   }

   szTempString[ 0 ] = 0;
   fnWriteStructRec( szTempString );
}

void
fnWriteAttribute( char  chType,
                  char  *pchEntityName,
                  char  *pchAttributeName,
                  short nLth,
                  zBOOL bMatch )
{
   char szTempString[ 256 ];
// if ( strcmp( pchAttributeName, "IsDrivingViewForReportFlag" ) == 0 )
//    cout << "IsDrivingViewForReportFlag found" << endl;

   if ( bMatch && g_pEntityList && g_pEntityList->Find( pchAttributeName ) )
   {
      cout << "Attribute: " << pchAttributeName << " within Entity: "
           << pchEntityName << " matches entity name" << endl;
   }

   if ( g_bJava )
   {
      strcpy_s( szTempString, sizeof( szTempString ), "   protected " );
      switch( chType )
      {
         case TYPE_LONG:
              strcat_s( szTempString, sizeof( szTempString ), "Integer " );
              break;

         case TYPE_INTEGER:
              strcat_s( szTempString, sizeof( szTempString ), "Integer " );
              break;

         case TYPE_CHAR:
              strcat_s( szTempString, sizeof( szTempString ), "String  " );
              break;

         case TYPE_DECIMAL:
              strcat_s( szTempString, sizeof( szTempString ), "double  " );
              break;

         case TYPE_BLOB:
              strcat_s( szTempString, sizeof( szTempString ), "Blob    " );
              break;

         case TYPE_STRING:
         default:
              strcat_s( szTempString, sizeof( szTempString ), "String  " );
              break;
      }

      g_pListAttributeType->Add( pchAttributeName, szTempString + 13 );
      strcat_s( szTempString, sizeof( szTempString ), pchAttributeName );
      strcat_s( szTempString, sizeof( szTempString ), ";" );
   }
   else
   {
      switch( chType )
      {
         case TYPE_BLOB:
         case TYPE_LONG:
              strcpy_s( szTempString, sizeof( szTempString ), "   zLONG " );
              strcat_s( szTempString, sizeof( szTempString ), pchAttributeName );
              strcat_s( szTempString, sizeof( szTempString ), ";" );

              break;

         case TYPE_INTEGER:
              strcpy_s( szTempString, sizeof( szTempString ), "   zINT  " );
              strcat_s( szTempString, sizeof( szTempString ), pchAttributeName );
              strcat_s( szTempString, sizeof( szTempString ), ";" );

              break;

         case TYPE_CHAR:
              strcpy_s( szTempString, sizeof( szTempString ), "   zCHAR " );
              strcat_s( szTempString, sizeof( szTempString ), pchAttributeName );
              strcat_s( szTempString, sizeof( szTempString ), ";" );

              break;

         case TYPE_DECIMAL:
              strcpy_s( szTempString, sizeof( szTempString ), "   zDOUBLE " );
              strcat_s( szTempString, sizeof( szTempString ), pchAttributeName );
              strcat_s( szTempString, sizeof( szTempString ), ";" );

              break;

         case TYPE_STRING:
         default:
              strcpy_s( szTempString, sizeof( szTempString ), "   zCHAR " );
              strcat_s( szTempString, sizeof( szTempString ), pchAttributeName );
              strcat_s( szTempString, sizeof( szTempString ), "[ " );
              int k = strlen( szTempString );
              _itoa_s( nLth, szTempString + k, sizeof( szTempString ) - k, 10 );
              strcat_s( szTempString, sizeof( szTempString ), " ];" );
              break;
      }
   }

   fnWriteStructRec( szTempString );
}

void
fnWriteStructRec( char *szBuffer )
{
   if ( fputs( szBuffer, pStructFile ) == -1 || fputs( "\n", pStructFile ) == -1 )
   {
      cerr << "\n" << szStructFile << " - file can not be written"
           << "\n****** Processing Aborted ******\n";
      exit( 1 );
   }
   else
   {
      nNumberRecordsWritten++;
   }
}

/////////////////////////////////////////////////////////////////////////////
//
// fnOpenFile - open a file and check for valid open
//
/////////////////////////////////////////////////////////////////////////////
FILE *
fnOpenFile( char *pchFileSpec,
            char *pchMode )
{
   FILE *pFile;

   if ( fopen_s( &pFile, pchFileSpec, pchMode ) != 0 )
   {
      cerr << "Error opening file " << pchFileSpec << endl;
      exit( 1 );
   }
#ifdef DEBUG2
   else
      cerr << "File opened " << pchFileSpec << endl;
#endif

   return( pFile );
}

/////////////////////////////////////////////////////////////////////////////
//  This program checks an input buffer for a token in the token
//  buffer.  If found, the token number is returned, otherwise -1
//  is returned.
//
//  Input Parms:
//     1. Input buffer
//     2. Token buffer
//     3. Maximum length of a token
//     4. Maximum number of tokens
//
//  Returns:
//     1. Token number (-1 if not found )
//
/////////////////////////////////////////////////////////////////////////////
short
qftoken( char  *szInputBuffer,      // input buffer
         char  *szTokenBuffer,      // token buffer
         short nMaxTokenLth,        // maximum length of a token
         short nMaxTokens )         // maximum number of tokens
{
   char  szTempBuffer[ 256 ];
   char  *pToken;
   short k;

#if 0
   cerr << "searching buffer > '" << szInputBuffer << "'\n";
#endif
   // do not modify original input buffer (strtok does modify buffer)
   zPCHAR pchNextToken = NULL;

   strcpy_s( szTempBuffer, szInputBuffer );
   pToken = strtok_s( szTempBuffer, TOKEN_DELIMITERS, &pchNextToken );
   if ( pToken )
   {
      for ( k = 0; k < nMaxTokens; k++ )
      {
         if ( strcmp( szTokenBuffer + k * nMaxTokenLth, pToken ) == 0 )
            return( k );

      }   // end of:  for ( k = 0; k < nMaxTokens; k++ )
   }

   return( -1 );

}  // end of:  qftoken

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CSListAttributeType : simple single-linked list of attribute names/types
//
CLinkAttributeType::CLinkAttributeType( zCPCHAR cpcAttribute, zCPCHAR cpcType )
{
   m_lAttributeLth = strlen( cpcAttribute ) + 1;
   m_pchAttribute = new char[ m_lAttributeLth ];
   strcpy_s( m_pchAttribute, m_lAttributeLth, cpcAttribute );
   m_lTypeLth = strlen( cpcType ) + 1;
   m_pchType = new char[ m_lTypeLth ];
   strcpy_s( m_pchType, m_lTypeLth, cpcType );
   while ( m_lTypeLth > 1 && m_pchType[ m_lTypeLth - 2 ] == ' ' )
   {
      m_lTypeLth--;
      m_pchType[ m_lTypeLth - 1 ] = 0;
   }

   m_pNext = 0;
}

CLinkAttributeType::~CLinkAttributeType( )
{
   mDeleteInitA( m_pchAttribute );
   mDeleteInitA( m_pchType );
}

CSListAttributeType::CSListAttributeType( zCPCHAR cpcEntityName )
{
   strcpy_s( m_szEntityName, sizeof( m_szEntityName ), cpcEntityName );
   m_pHead = 0;
   m_pTail = 0;
   m_lCnt = 0;
}

CSListAttributeType::~CSListAttributeType( )
{
   CLinkAttributeType *pItem;
   while ( m_pHead )
   {
      pItem = m_pHead->m_pNext;
      delete( m_pHead );
      m_pHead = pItem;
   }
}

CLinkAttributeType *
CSListAttributeType::Add( zCPCHAR cpcAttribute, zCPCHAR cpcType )
{
   CLinkAttributeType *pItem = m_pTail;
   m_pTail = new CLinkAttributeType( cpcAttribute, cpcType );
   if ( pItem )
      pItem->m_pNext = m_pTail;
   else
      m_pHead = m_pTail;

   return( m_pTail );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void
fnWriteAbstract( FILE *pXOD, short nBaseSubtype )
{
   if ( pXOD && nBaseSubtype )
   {
      if ( nBaseSubtype == 1 )
      {
         fputs( "aABSTRACT  Y\n", pXOD );
      }
      else
      if ( nBaseSubtype == 2 )
      {
         fputs( "aABSTRACTCHILD Y\n", pXOD );
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void
fnFinishUpJavaEntity( )
{
   char szTempString[ 256 ];
   CLinkAttributeType *pItem = g_pListAttributeType->GetFirstLink( );

   fnWriteStructRec( "   // ctor" );
   strcpy_s( szTempString, sizeof( szTempString ), "   protected " );
   strcat_s( szTempString, sizeof( szTempString ), g_pListAttributeType->GetEntityName( ) );
   strcat_s( szTempString, sizeof( szTempString ), "Impl( EntityCursor cursor )" );
   fnWriteStructRec( szTempString );
   fnWriteStructRec( "   {" );
   strcpy_s( szTempString, sizeof( szTempString ), "      load" );
   strcat_s( szTempString, sizeof( szTempString ), g_pListAttributeType->GetEntityName( ) );
   strcat_s( szTempString, sizeof( szTempString ), "EntityStructure( cursor );" );
   fnWriteStructRec( szTempString );
   fnWriteStructRec( "   }" );

   fnWriteStructRec( "" );  // write blank line
   while ( pItem )
   {
      fnWriteStructRec( "   /**" );     
      strcpy_s( szTempString, sizeof( szTempString ), "    * @return the " );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      fnWriteStructRec( szTempString );
      fnWriteStructRec( "    */" );
      strcpy_s( szTempString, sizeof( szTempString ), "   public " );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchType );
      strcat_s( szTempString, sizeof( szTempString ), " get" );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      strcat_s( szTempString, sizeof( szTempString ), "( )\n   {" );
      fnWriteStructRec( szTempString );

      strcpy_s( szTempString, sizeof( szTempString ), "      return " );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      strcat_s( szTempString, sizeof( szTempString ), ";" );
      fnWriteStructRec( szTempString );

      fnWriteStructRec( "   }" );
      fnWriteStructRec( "" );
      fnWriteStructRec( "   /**" );
      strcpy_s( szTempString, sizeof( szTempString ), "    * @param " );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
//    strcat_s( szTempString, sizeof( szTempString ), " the " );
//    strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      strcat_s( szTempString, sizeof( szTempString ), " to set " );
      fnWriteStructRec( szTempString );
      fnWriteStructRec( "    */" );

      strcpy_s( szTempString, sizeof( szTempString ), "   public void set" );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      strcat_s( szTempString, sizeof( szTempString ), "( " );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchType );
      strcat_s( szTempString, sizeof( szTempString ), " " );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      strcat_s( szTempString, sizeof( szTempString ), " )\n   {" );
      fnWriteStructRec( szTempString );

      strcpy_s( szTempString, sizeof( szTempString ), "      this." );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      strcat_s( szTempString, sizeof( szTempString ), " = " );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      strcat_s( szTempString, sizeof( szTempString ), ";" );
      fnWriteStructRec( szTempString );
      fnWriteStructRec( "   }" );
      fnWriteStructRec( "" );

      pItem = pItem->m_pNext;
   }

   strcpy_s( szTempString, sizeof( szTempString ), "   public int load" );
   strcat_s( szTempString, g_pListAttributeType->GetEntityName( ) );
   strcat_s( szTempString, "EntityStructure( EntityCursor cursor )" );
   fnWriteStructRec( szTempString );
   fnWriteStructRec( "   {" );
   pItem = g_pListAttributeType->GetFirstLink( );
   while ( pItem )
   {
      // Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      // Tag = cursor.getStringFromAttribute( "Tag.cursor( " );  if ( Tag == null ) Tag = "";
      strcpy_s( szTempString, sizeof( szTempString ), "      " );
      strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
      strcat_s( szTempString, sizeof( szTempString ), " = cursor.get" );
      if ( pItem->m_pchType[ 0 ] == 'S' || pItem->m_pchType[ 0 ] == 'I' )
      {
         strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchType );
         strcat_s( szTempString, sizeof( szTempString ), "FromAttribute( \"" );
         strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
         strcat_s( szTempString, sizeof( szTempString ), "\" );  if ( " );
         strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
         strcat_s( szTempString, sizeof( szTempString ), " == null ) " );
         strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
         if ( pItem->m_pchType[ 0 ] == 'S' )
            strcat_s( szTempString, sizeof( szTempString ), " = \"\";" );
         else
            strcat_s( szTempString, sizeof( szTempString ), " = 0;" );
      }
      else
      {
         strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchType[ 0 ] == 'B' ? "Blob" :
                                                         pItem->m_pchType[ 0 ] == 'd' ? "Decimal" : "Unknown" ); 
         strcat_s( szTempString, sizeof( szTempString ), "FromAttribute( \"" );
         strcat_s( szTempString, sizeof( szTempString ), pItem->m_pchAttribute );
         strcat_s( szTempString, sizeof( szTempString ), "\" );" );
      }

      fnWriteStructRec( szTempString );

      pItem = pItem->m_pNext;
   }

   fnWriteStructRec( "" );
   fnWriteStructRec( "      return 0;" );
   fnWriteStructRec( "   }" );
   fnWriteStructRec( "" );
   fnWriteStructRec( "}" );
   fnWriteStructRec( "" );
   fnWriteStructRec( "" );
}