////////////////////////////////////////////////////////////////////////////
//  ARKUTIL.CPP   -  written by Doug Sorensen         - create date 04/09/99
//                   (C)  Arksoft Inc., 1989-2000     - last update 02/29/00
//
//  This file contains source for several utility classes:
//
//    CFileName
//    CSList
//    CSLink
//    CFileData
//    CDirData
//
/////////////////////////////////////////////////////////////////////////////

#include "arkutil.h"

zLONG g_lNbrBytesRead;
zLONG g_lNbrBytesWrite;
zLONG g_lCurrBufferOffset;
char  g_chEofChar;
zLONG g_lLoadDirCnt;
zLONG g_lLoadFileCnt;
zLONG g_lTotalFileCnt;
zLONG g_lFilesFound;
zLONG g_lFilesExcluded;
CDirData *g_pDirRoot;     // Root of directory tree from disk
CSList *g_pListInclude;
CSList *g_pListExclude;
fnDirBegin g_fnDirBegin;
fnDirTroll g_fnDirTroll;
fnDirEnd g_fnDirEnd;
zPCHAR g_pchSpecialIgnore;

//#define DEBUG
#ifdef DEBUG
char *rgpDebugErrMsg[ ] =
{
   "No memory",
   "Drive letter out of range",
   "Drive specifier incorrect",
   "Path > 64 characters",
   "Directory names 8 chars only",
   "File name too long",
   "Extension too long",
   "Invalid character",
   "Invalid path",
   ""
};
#endif

// ctor
CFileName::CFileName( zCPCHAR cpcPathSpec,
                      zBOOL   bExpectFileName,
                      zBOOL   bAcceptSpecial,
                      zCPCHAR cpcInvalidCharSet )
{
   m_cDrive = m_cErr = 0;
   m_pchPath = m_pchFullName = m_pchName = m_pchExt = 0;
   m_nFullNameLth = m_nPathLth = 0;
   m_lInvalidNameSetLth = strlen( cpcInvalidCharSet ) + 1;
   m_pchInvalidNameSet = new char[ m_lInvalidNameSetLth ];
   strcpy_s( m_pchInvalidNameSet, m_lInvalidNameSetLth, cpcInvalidCharSet );
   m_bSpecial = bAcceptSpecial;
   if ( cpcPathSpec[ 0 ] == 0 )
      return;

#ifdef DEBUG  // check #if at top
   cerr << cpcPathSpec << '\n';
   zSHORT nRC = Parse( cpcPathSpec, bExpectFileName );

   if ( m_cDrive )
      cerr << "drive = " << m_cDrive << endl;
   else
      cerr << "drive null\n";

   if ( m_pchPath )
      cerr << "path = " << m_pchPath << endl;
   else
      cerr << "path null\n";

   if ( m_pchName )
      cerr << "name = " << m_pchName << endl;
   else
      cerr << "name null\n";

   if ( m_pchExt )
      cerr << "ext = " << m_pchExt << endl;
   else
      cerr << "ext null\n";

   zSHORT  k = nRC > ENOMEM ? nRC + 1 - FN_BADDRIVE : 0;

   if ( nRC == FN_NULL )
      cerr << "File name null\n";
   else
   if ( nRC )
      cerr << rgpDebugErrMsg[ k ] << " RC = " << nRC << endl;
   else
      cerr << "File name OK\n";
#else
   Parse( cpcPathSpec, bExpectFileName, bAcceptSpecial );
#endif
}

// ctor
CFileName::CFileName( )
{
   m_cDrive = m_cErr = 0;
   m_pchPath = m_pchFullName = m_pchName = m_pchExt = 0;
   m_nFullNameLth = m_nPathLth = 0;
// m_pchPath = new char[ 1 ];
// m_pchFullName = new char[ 1 ];
   m_lInvalidNameSetLth = 15;
   m_pchInvalidNameSet = new char[ m_lInvalidNameSetLth ];
// strcpy_s( m_pchInvalidNameSet, m_lInvalidNameSetLth, "*+=[]:;\",.?/" );
// strcpy_s( m_pchInvalidNameSet, m_lInvalidNameSetLth, "*+=[]:;\",?/" );
   strcpy_s( m_pchInvalidNameSet, m_lInvalidNameSetLth, "*=[]:;\",?/" );
   m_bSpecial = FALSE;
}

// copy ctor
CFileName::CFileName( const CFileName& CFN_Copy )
{
   m_cDrive = m_cErr = 0;
   m_pchPath = m_pchFullName = m_pchName = m_pchExt = 0;
   m_nFullNameLth = m_nPathLth = 0;

   if ( CFN_Copy.m_pchFullName )
   {
      m_nFullNameLth = CFN_Copy.m_nFullNameLth;
      m_pchFullName = new char[ m_nFullNameLth + 1 ];
      if ( m_pchFullName == 0 )
         goto allocerr;

      memmove( m_pchFullName, CFN_Copy.m_pchFullName, m_nFullNameLth + 1 );
   }
   else
   {
      m_pchFullName = 0;
      m_nFullNameLth = 0;
   }

   if ( CFN_Copy.m_pchPath )
   {
      zLONG k;

      k = strlen( CFN_Copy.m_pchPath ) + 1;
      m_pchPath = new char[ k ];
      if ( !m_pchPath )
         goto allocerr;

      memmove( m_pchPath, CFN_Copy.m_pchPath, k );
   }
   else
      m_pchPath = 0;

   m_pchInvalidNameSet = CFN_Copy.m_pchInvalidNameSet;
   m_cDrive = CFN_Copy.m_cDrive;
   strcpy_s( m_pchName, CFN_Copy.m_nNameLth, CFN_Copy.m_pchName );
   m_nPathLth = CFN_Copy.m_nPathLth;
   strcpy_s( m_pchExt, CFN_Copy.m_nExtLth, CFN_Copy.m_pchExt );
   m_bSpecial = CFN_Copy.m_bSpecial;
   m_cErr = 0;
   return;

allocerr:
   m_cErr = ENOMEM;
}

CFileName& CFileName::operator=( const CFileName& CFN_Copy )
{
   if ( this == (CFileName *) &CFN_Copy )
      return( *this );

   mDeleteInitA( m_pchFullName );
   mDeleteInitA( m_pchPath );
   mDeleteInitA( m_pchExt );

   if ( CFN_Copy.m_pchFullName )
   {
      m_nFullNameLth = CFN_Copy.m_nFullNameLth;
      m_pchFullName = new char[ m_nFullNameLth + 1 ];
      if ( !m_pchFullName )
         goto allocerr1;

      memmove( m_pchFullName, CFN_Copy.m_pchFullName, m_nFullNameLth + 1 );
   }
   else
      m_pchFullName = 0;

   if ( CFN_Copy.m_pchPath )
   {
      zLONG k;

      k = strlen( CFN_Copy.m_pchPath ) + 1;
      m_pchPath = new char[ k ];
      if ( !m_pchPath )
      {
allocerr1:
         m_cErr = ENOMEM;
         return( *this );
      }
      else
         memmove( m_pchPath, CFN_Copy.m_pchPath, k );
   }
   else
      m_pchPath = 0;

   m_pchInvalidNameSet = CFN_Copy.m_pchInvalidNameSet;
   m_cDrive = CFN_Copy.m_cDrive;
   strcpy_s( m_pchName, CFN_Copy.m_nNameLth, CFN_Copy.m_pchName );
   m_nPathLth = CFN_Copy.m_nPathLth;
   m_nExtLth = CFN_Copy.m_nExtLth;
   strcpy_s( m_pchExt, m_nExtLth, CFN_Copy.m_pchExt );
   return( *this );
}

char *
CFileName::operator( )( )
{
   m_nFullNameLth = 1;
   if ( m_pchName )
      m_nFullNameLth = (zSHORT) strlen( m_pchName );

   if ( m_pchExt )
      m_nFullNameLth += (zSHORT) strlen( m_pchExt );

   if ( m_pchPath )
      m_nFullNameLth += (zSHORT) strlen( m_pchPath ) + 1;

   if ( m_cDrive )
      m_nFullNameLth += 2;

   mDeleteInitA( m_pchFullName );

   // Need an extra for a possible extra '\\'
   m_pchFullName = new char[ m_nFullNameLth + 2 ];
   if ( m_pchFullName == 0 )
   {
      m_cErr = ENOMEM;
      return( 0 );
   }

   if ( m_cDrive )
   {
      m_pchFullName[ 0 ] = m_cDrive;
      m_pchFullName[ 1 ] = ':';
      m_pchFullName[ 2 ] = 0;
   }
   else
      m_pchFullName[ 0 ] = 0;

   if ( m_pchPath )
   {
      strcat_s( m_pchFullName, m_nFullNameLth + 2, m_pchPath );
      m_nPathLth = (zSHORT) strlen( m_pchFullName );
      if ( m_pchFullName[ m_nPathLth - 1 ] != '\\' )
      {
         m_pchFullName[ m_nPathLth++ ] = '\\';
         m_pchFullName[ m_nPathLth ] = 0;
      }
   }
   else
      m_nPathLth = (zSHORT) strlen( m_pchFullName );

   strcat_s( m_pchFullName, m_nFullNameLth + 2, m_pchName );
   if ( *m_pchExt )
   {
      strcat_s( m_pchFullName, m_nFullNameLth + 2, "." );
      strcat_s( m_pchFullName, m_nFullNameLth + 2, m_pchExt );
   }

   m_nFullNameLth = (zSHORT) strlen( m_pchFullName );
   return( m_pchFullName );
}

zSHORT
CFileName::Update( char    cDriveLetter,
                   zCPCHAR cpcPath,
                   zCPCHAR cpcName,
                   zCPCHAR cpcExt,
                   zBOOL   bOverride )
{
#ifdef DEBUG
   cerr << "CFileName::Update\n";
   cerr << "cDrive = " << cDriveLetter << '\n';
   cerr << "cpcPath = " << cpcPath << '\n';
   cerr << "cpcName  = " << cpcName << '\n';
   cerr << "cpcExt   = " << cpcExt << endl;
   cerr << "bOverride = " << bOverride << endl;
#endif

   if ( cDriveLetter )
   {
      cDriveLetter = toupper( cDriveLetter );
      if ( cDriveLetter < 'A' || cDriveLetter > 'Z' )
         return( FN_BADDRIVE );

      m_cDrive = cDriveLetter;
   }
   else
   if ( bOverride )
      m_cDrive = 0;

   if ( cpcName )
   {
      zCPCHAR q = strpbrk( cpcName, m_pchInvalidNameSet );
      if ( q && (m_bSpecial == FALSE || (m_bSpecial && *q != '*' && *q != '?')) )
      {
         cerr << "m_bSpecial: " << m_bSpecial << "   q = " << q << endl;
         cerr << "Invalid character in file name - " << cpcName << endl;
         return( FN_BADCHAR );
      }

      m_nNameLth = (zSHORT) strlen( cpcName ) + 1;
      m_pchName = new char[ m_nNameLth ];
      if ( m_pchName == 0 )
         return( ENOMEM );

      strcpy_s( m_pchName, m_nNameLth, cpcName );
   // _strupr_s( m_pchName, m_nNameLth );
   }
   else
   if ( bOverride )
   {
      m_pchName = new char[ 1 ];
      if ( m_pchName == 0 )
         return( ENOMEM );

      m_nNameLth = 1;
      m_pchName[ 0 ] = 0;
   }

   if ( cpcExt )
   {
      zCPCHAR q = strpbrk( cpcExt, m_pchInvalidNameSet );
      if ( q && (!m_bSpecial || (m_bSpecial && *q != '*' && *q != '?')) )
      {
         cerr << "m_bSpecial: " << m_bSpecial << "   q = " << q << endl;
         cerr << "Invalid character in extension - " << cpcExt << endl;
         return( FN_BADCHAR );
      }

      m_nExtLth = (zSHORT) strlen( cpcExt ) + 1;
      m_pchExt = new char[ m_nExtLth ];
      if ( m_pchExt == 0 )
         return( ENOMEM );

      strcpy_s( m_pchExt, m_nExtLth, cpcExt );
   // _strupr_s( m_pchExt, m_nExtLth );
   }
   else
   if ( bOverride )
   {
      m_pchExt = new char[ 1 ];
      if ( m_pchExt == 0 )
         return( ENOMEM );

      m_nNameLth = 1;
      m_pchExt[ 0 ] = 0;
   }

   if ( cpcPath )
   {
      zSHORT nLth = (zSHORT) strlen( cpcPath );
      zCPCHAR r, q;

      if ( m_pchPath )
         mDeleteInitA( m_pchPath );

      q = strpbrk( cpcPath, m_pchInvalidNameSet );
      if ( q && *q != '\\' )
      {
         cerr << "m_bSpecial: " << m_bSpecial << "   q = " << q << endl;
         cerr << "Invalid character in path - " << cpcPath << endl;
         return( FN_BADCHAR );
      }

      for ( r = q = cpcPath; ; )
      {
         q = strchr( q, '\\' );
         if ( q == 0 )           // no more backslashes
            break;

         if ( *(q + 1) == 0 )
            break;
         else
            r = ++q;

         if ( *r == '\\' )
            return( FN_BADCHAR );
      }

//    if ( nLth > 64 )
//       return( FN_PTOOLONG );

      if ( strcmp( cpcPath, "\\" ) != 0 )
      {
         m_nPathLth = nLth + 1;
         m_pchPath = new char[ m_nPathLth ];
         if ( m_pchPath == 0 )
            return( ENOMEM );

         strcpy_s( m_pchPath, m_nPathLth, cpcPath );
      // _strupr_s( m_pchPath, m_nPathLth );
      }
      else
      {
         m_nPathLth = 1;
         m_pchPath = new char[ 1 ];
         if ( m_pchPath == 0 )
            return( ENOMEM );

         m_pchPath[ 0 ] = 0;
      }
   }
   else
   if ( bOverride )
   {
      if ( m_pchPath )
      {
         mDeleteInitA( m_pchPath );
         m_nPathLth = 0;
      }
   }

   (*this)( );  // to force reset of lengths
   return( 0 );
}

zSHORT
CFileName::Parse( zCPCHAR cpcPathSpec,
                  zBOOL   bExpectFileName,
                  zBOOL   bAcceptSpecial )
{
   char szLocal[ _MAX_PATH ];
   char szPath[ _MAX_PATH ];
   char szLocalName[ _MAX_PATH ];
   char szExtension[ _MAX_EXT ];
   char *pch;
   char *pchName;
   char cDriveLetter = 0;
   int  nDrive;
   zLONG k;

   if ( cpcPathSpec[ 0 ] && cpcPathSpec[ 0 ] != '.' )
      strncpy_s( szLocal, _MAX_PATH, cpcPathSpec, _MAX_PATH - 1 );
   else
   {
      _getcwd( szLocal, _MAX_PATH );
      if ( cpcPathSpec[ 0 ] == '.' && cpcPathSpec[ 1 ] == '.' )
      {
         pch = strrchr( szLocal, '\\' );
         if ( pch )
            *pch = 0;

         strcat_s( szLocal, _MAX_PATH, cpcPathSpec + 2 );
      }
      else
      if ( cpcPathSpec[ 0 ] == '.' )
      {
         strcat_s( szLocal, _MAX_PATH, cpcPathSpec + 1 );
      }
   }

   szLocal[ _MAX_PATH - 1 ] = 0;
   k = strlen( szLocal );
   if ( bExpectFileName == FALSE )
   {
      if ( k && szLocal[ k - 1 ] != '\\' )
      {
         if ( szLocal[ k - 1 ] == '.' )
            k--;
         else
            szLocal[ k++ ] = '\\';

         szLocal[ k ] = 0;
      }
   }
   else
   if ( k && szLocal[ k - 1 ] == ':' )
   {
      szLocal[ k++ ] = '.';
      szLocal[ k ] = 0;
   }

   m_bSpecial = bAcceptSpecial;

   nDrive = _getdrive( );
   pch = strchr( szLocal, ':' );
   if ( pch )
   {
      if ( pch != szLocal + 1 || strchr( pch + 1, ':' ) )
         return( FN_BADCOLON );

      cDriveLetter = toupper( szLocal[ 0 ] );
      pch++;
   }
   else
   {
      cDriveLetter = nDrive + 'A' - 1;
      pch = szLocal;
   }

   if ( *pch != '\\' )
   {
      _chdrive( cDriveLetter - 'A' + 1 );
      _getcwd( szPath, _MAX_PATH );
      _chdrive( nDrive );
      k = strlen( szPath );
      if ( k > 1 && szPath[ 1 ] == ':' )
      {
         strcpy_s( szPath, szPath + 2 );
         k -= 2;
      }

      if ( k && szPath[ k - 1 ] != '\\' )
      {
         szPath[ k++ ] = '\\';
         szPath[ k ] = 0;
      }

      strcat_s( szPath, _MAX_PATH, pch );
      strcpy_s( szLocal, _MAX_PATH, szPath );
      pch = szLocal;
   }

#ifdef DEBUG
   cerr << "parsing '" << szLocal << "' bExpectFN " << bExpectFileName << endl;
#endif

   pchName = strrchr( pch, '\\' );
   if ( pchName )
   {
      if ( pchName > pch )
      {
         if ( *(pchName - 1) == '\\' )
            return( FN_BADCHAR );

         if ( strcmp( pchName + 1, ".." ) == 0 )
         {
            pchName += 3;
            strcpy_s( pchName, _MAX_PATH, "\\*.*" );
         }
         else
         if ( strcmp( pchName + 1, "." ) == 0 )
            strcpy_s( pchName + 1, _MAX_PATH, "*.*" );
         else
         {
            struct _stat statBuffer;
            if ( _stat( szLocal, &statBuffer ) == 0 &&
                 (statBuffer.st_mode & _S_IFDIR) )
            {
            // strcat_s( pchName, _MAX_PATH - (pchName - szLocal), "*.*" );
               if ( bAcceptSpecial || m_bSpecial )
                  strcat_s( pchName, _MAX_PATH - (pchName - szLocal), "\\*.*" );
               else
                  strcat_s( pchName, _MAX_PATH - (pchName - szLocal), "\\" );

               pchName = strrchr( pchName, '\\' );
            }
         }
      }

      if ( pchName > pch )
      {
         *pchName++ = 0;
         strcpy_s( szPath, _MAX_PATH, pch );
      }
      else
      {
         pchName++;
         strcpy_s( szPath, _MAX_PATH, "\\" );
      }
   }
   else
   {
      pchName = pch;
      szPath[ 0 ] = 0;
   }

#ifdef DEBUG
   cerr << "cDrive = " << cDriveLetter << '\n';
   cerr << "szPath  = " << szPath << '\n';
   cerr << "m_pchName = " << pchName << '\n';
#endif

   pch = strrchr( pchName, '.' );
   if ( pch && strchr( pch, '\\' ) == 0 )
   {
      *pch++ = 0;
      strncpy_s( szExtension, _MAX_EXT, pch, _MAX_EXT - 1 );
      szExtension[ _MAX_EXT - 1 ] = 0;
   }
   else
   {
      szExtension[ 0 ] = 0;
   }

   strncpy_s( szLocalName, _MAX_PATH, pchName, _MAX_PATH - 1 );
   szLocalName[ _MAX_PATH - 1 ] = 0;

#ifdef DEBUG
   cerr << "path = " << szPath << " name = " << szLocalName << " ext = " << szExtension << endl;
#endif

   if ( szPath[ 0 ] == 0 )
   {
      _chdrive( cDriveLetter - 'A' + 1 );
      _getcwd( szPath, _MAX_PATH - 1 );
      _chdrive( nDrive );
      if ( strlen( szPath ) > 1 && szPath[ 1 ] == ':' )
         strcpy_s( szPath, szPath + 2 );
   }
   else
   {
      while ( (pch = strchr( szPath, '.' )) != 0 )
      {
         if ( *(pch + 1) == '.' || *(pch + 1) == '\\' ||
              (*(pch + 1) == 0 && pch > szPath && *(pch - 1) == '\\') )
         {
            _chdrive( cDriveLetter - 'A' + 1 );
            _getcwd( szLocal, _MAX_PATH - 1 );
            _chdrive( nDrive );
            k = strlen( szLocal );
            if ( k > 1 && szLocal[ 1 ] == ':' )
            {
               strcpy_s( szLocal, szLocal + 2 );
               k -= 2;
            }

            if ( k == 0 || (k && szLocal[ k - 1 ] != '//') )
            {
               szLocal[ k++ ] = '\\';
               szLocal[ k ] = 0;
            }

            k = 0;
            while ( szLocal[ k ] == szPath[ k ] )
               k++;

            if ( szPath[ k - 1 ] == '\\' )
            {
               while ( szPath[ k ] != '.' )
               {
                  szLocal[ k ] = szPath[ k ];
                  k++;
               }
            }

            szLocal[ k ] = 0;
            if ( szPath[ k ] == '.' )
            {
               if ( szPath[ k + 1 ] == '.' )
               {
                  szLocal[ k - 1 ] = 0;
                  pch = strrchr( szLocal, '\\' );
                  strcpy_s( pch, _MAX_PATH, szPath + k + 2 );
                  strcpy_s( szPath, _MAX_PATH, szLocal );
               }
               else
               {
                  if ( k && szPath[ k - 1 ] != '\\' )
                     return( FN_INVALIDPATH );
                  else
                  {
                     strcat_s( szLocal, _MAX_PATH, szPath + k + 2 );
                     strcpy_s( szPath, _MAX_PATH, szLocal );
                  }
               }
            }
            else
               return( FN_INVALIDPATH );
         }
         else
         {
#ifdef DEBUG
            cerr << "check point for directory with '.' " << szLocal << '\n';
#endif
            break;
         }

      } // end of:  while ( (m_pch = strchr( szPath, '.' )) )

   } // end of:  else of:  if ( szPath[ 0 ] == 0 )

   if ( bExpectFileName && szLocalName[ 0 ] == 0 && szExtension[ 0 ] == 0 )
   {
      szLocalName[ 0 ] = '*';
      szLocalName[ 1 ] = 0;
      szExtension[ 0 ] = '*';
      szExtension[ 1 ] = 0;
   }

   zSHORT nRC = Update( cDriveLetter, szPath, szLocalName, szExtension, TRUE );
   return( nRC );
}

zLONG
CFileName::GetFullNameLth( )
{
   return( m_nFullNameLth );
}

zSHORT
CFileName::GetDriveDirLth( )
{
   return( m_nPathLth );
}

zSHORT
CFileName::GetError( )
{
   zSHORT e = m_cErr;
   m_cErr = 0;
   return( e );
}

// This function returns the requested concatenation in the location
// specified.  The concatenated length is the return code.
zSHORT
CFileName::GetDrivePathFilenameExt( zPCHAR pchConcatName,
                                    zBOOL  bDrive,
                                    zBOOL  bPath,
                                    zBOOL  bFilename,
                                    zBOOL  bExt )
{
#ifdef DEBUG2
   cerr << "GetDrivePathFilenameExt\n";
   cerr << "cDrive = " << cDrive << '\n';
   cerr << "m_pchPath = " << m_pchPath << '\n';
   cerr << "m_pchName  = " << m_pchName << '\n';
   cerr << "m_pchExt   = " << m_pchExt << endl;
#endif

   zSHORT nLth = 0;

   *pchConcatName = 0;
   if ( bDrive && m_cDrive )
   {
      pchConcatName[ nLth++ ] = m_cDrive;
      pchConcatName[ nLth++ ] = ':';
   }

   if ( bPath && m_pchPath )
   {
      strcpy_s( pchConcatName + nLth, _MAX_PATH, m_pchPath );
      nLth += (zSHORT) strlen( m_pchPath );
      if ( m_pchName[ 0 ] )
      {
         pchConcatName[ nLth++ ] = '\\';
         pchConcatName[ nLth ] = 0;
      }
   }

   if ( bFilename && m_pchName[ 0 ] )
   {
      strcpy_s( pchConcatName + nLth, _MAX_PATH, m_pchName );
      nLth += (zSHORT) strlen( m_pchName );
   }

   if ( bExt && m_pchExt && m_pchExt[ 0 ] )
   {
      pchConcatName[ nLth++ ] = '.';
      strcpy_s( pchConcatName + nLth, _MAX_PATH, m_pchExt );
      nLth += (zSHORT) strlen( m_pchExt );
   }

   return( nLth );
}

// dtor
CFileName::~CFileName( )
{
   mDeleteInitA( m_pchInvalidNameSet );
   mDeleteInitA( m_pchPath );
   mDeleteInitA( m_pchFullName );
   mDeleteInitA( m_pchName );
   mDeleteInitA( m_pchExt );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CSLink : simple single-linked list of names
//
CSLink::CSLink( zCPCHAR cpcName )
{
   m_nNameLth = (zSHORT) strlen( cpcName ) + 1;
   m_pchName = new char[ m_nNameLth ];
   strcpy_s( m_pchName, m_nNameLth, cpcName );
   m_pNext = 0;
}

CSLink::~CSLink( )
{
   mDeleteInitA( m_pchName );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CSList : simple container for single-linked list of names
//
CSList::CSList( )
{
   m_pHead = 0;
   m_lCnt = 0;
}

CSList::~CSList( )
{
   CSLink *pItem;
   while ( m_pHead )
   {
      pItem = m_pHead->m_pNext;
      delete( m_pHead );
      m_pHead = pItem;
      m_lCnt--;
   }
}

CSLink *
CSList::GetFirstLink( )
{
   return( m_pHead );
}

// return ptr if added ... 0 if already in the list
CSLink *
CSList::Add( zCPCHAR cpcName )
{
   if ( cpcName == 0 || *cpcName == 0 || Find( cpcName ) )
      return( 0 );

   m_lCnt++;
   if ( m_pHead == 0 )
   {
      m_pHead = new CSLink( cpcName );
      return( m_pHead );
   }
   else
   {
      CSLink *pItem = m_pHead;
      while ( pItem->m_pNext )
         pItem = pItem->m_pNext;

      pItem->m_pNext = new CSLink( cpcName );
      return( pItem->m_pNext );
   }
}

// return ptr if added ... 0 otw
CSLink *
CSList::AddIgnoreDup( zCPCHAR cpcName )
{
   if ( cpcName == 0 )
      return( 0 );

   m_lCnt++;
   if ( m_pHead == 0 )
   {
      m_pHead = new CSLink( cpcName );
      return( m_pHead );
   }
   else
   {
      CSLink *pItem = m_pHead;
      while ( pItem->m_pNext )
         pItem = pItem->m_pNext;

      pItem->m_pNext = new CSLink( cpcName );
      return( pItem->m_pNext );
   }
}

// return ptr if found ... 0 if not found in the list
CSLink *
CSList::Find( zCPCHAR cpcName )
{
   CSLink *pItem = m_pHead;
   while ( pItem )
   {
      if ( strcmp( cpcName, pItem->m_pchName ) == 0 )
         return( pItem );

      pItem = pItem->m_pNext;
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// Parameters:  File name to check for being in the list
//
/////////////////////////////////////////////////////////////////////////////
zBOOL
CSList::FindFile( zCPCHAR cpcName )
{
   CSLink *pItem = m_pHead;
   while ( pItem )
   {
      if ( MatchFilenameToWildcard( pItem->m_pchName, cpcName ) )
         return( TRUE );

      pItem = pItem->m_pNext;
   }

   return( FALSE );
}

// return ptr if found ... 0 if not found in the list
CSLink *
CSList::Remove( zCPCHAR cpcName )
{
   CSLink *pItem = m_pHead;
   CSLink *pItemPrev = 0;
   while ( pItem )
   {
      if ( strcmp( cpcName, pItem->m_pchName ) == 0 )
      {
         if ( pItemPrev )
            pItemPrev->m_pNext = pItem->m_pNext;
         else
            m_pHead = pItem->m_pNext;

         m_lCnt--;
         return( pItem );
      }

      pItemPrev = pItem;
      pItem = pItem->m_pNext;
   }

   return( 0 );
}

zLONG
CSList::GetCount( )
{
   return( m_lCnt );
}

zBOOL
CSList::IsEmpty( )
{
   return( m_pHead ? FALSE : TRUE );
}

void
CSList::ExpandResponseFile( zCPCHAR cpcFileName )
{
   FILE  *pResponseFile;          // response file pointer
   char  szBuffer[ BUFSIZE ];
   zLONG k;

   if ( fopen_s( &pResponseFile, cpcFileName, READFILE ) == 0 )
   {
//    cerr << "\nResponse File........:  " << cpcFileName << endl;
   }
   else
   {
      cerr << "\nResponse file cannot be opened:  " << cpcFileName << endl;
      cerr << "****** Processing Aborted ******\n";
      exit( 1 );
   }

   while ( fgets( szBuffer, MAXLINE, pResponseFile ) )
   {
      k = strlen( szBuffer );
      while ( k && isspace( szBuffer[ k - 1 ] ) )
         szBuffer[ --k ] = 0;

      if ( szBuffer[ 0 ] == '@' )
      {
         if ( _stricmp( szBuffer + 1, cpcFileName ) == 0 )
         {
            cerr << "recursive response file " << cpcFileName << endl;
            cerr << "****** Processing Aborted ******\n";
            exit( 1 );
         }
         else
            ExpandResponseFile( szBuffer + 1 );
      }
      else
      {
         AddToList( szBuffer );
      }
   }
}

void
CSList::AddToList( zCPCHAR cpcList )
{
   zPCHAR  pchParm;
   zPCHAR  pch;
   zLONG   lBufferLth = strlen( cpcList ) + 1;
   zPCHAR  pchBuffer = new char[ lBufferLth ];

   strcpy_s( pchBuffer, lBufferLth, cpcList );
   pchParm = pchBuffer;
   while ( pchParm && *pchParm )
   {
      pch = strchr( pchParm, ';' );
      if ( pch )
         *pch = 0;

      if ( pchParm[ 0 ] == '!' && pchParm[ 1 ] == 0 )
      {
         AddToList( g_pchSpecialIgnore );
      }
      else
      if ( pchParm[ 0 ] == '@' )
      {
         ExpandResponseFile( pchParm + 1 );
      }
      else
      {
         // cerr << "Adding to List: " << pchParm << endl;
         Add( pchParm );
      }

      if ( pch )
      {
         *pch = ';';
         pch++;
      }

      pchParm = pch;
   }

   mDeleteInitA( pchBuffer );
}

void
CSList::AddToListIgnoreDup( zCPCHAR cpcList )
{
   zPCHAR  pchParm;
   zPCHAR  pch;
   zLONG   lBufferLth = strlen( cpcList ) + 1;
   zPCHAR  pchBuffer = new char[ lBufferLth ];

   strcpy_s( pchBuffer, lBufferLth, cpcList );
   pchParm = pchBuffer;
   while ( pchParm )
   {
      pch = strchr( pchParm, ';' );
      if ( pch )
         *pch = 0;

      AddIgnoreDup( pchParm );
      if ( pch )
      {
         *pch = ';';
         pch++;
      }

      pchParm = pch;
   }

   mDeleteInitA( pchBuffer );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CFileData::CFileData( zCPCHAR cpcName,
                      zCPCHAR cpcTimestamp )
{
   m_nNameLth = (zSHORT) strlen( cpcName ) + 1;
   m_pchName = new char[ m_nNameLth ];
   strcpy_s( m_pchName, m_nNameLth, cpcName );

   m_pchTimestamp = 0;
   if ( cpcTimestamp )
   {
      m_lTimestampLth = strlen( cpcTimestamp ) + 1;
      m_pchTimestamp = new char[ m_lTimestampLth ];
      strcpy_s( m_pchTimestamp, m_lTimestampLth, cpcTimestamp );
   }

   m_DateTime = 0;
   m_nState = 0;
   m_lSize = 0;
   m_pFileNext = 0;
}

CFileData::CFileData( zCPCHAR cpcName,
                      time_t  DateTime,
                      zLONG   lSize )
{
   m_nNameLth = (zSHORT) strlen( cpcName ) + 1;
   m_pchName = new char[ m_nNameLth ];
   strcpy_s( m_pchName, m_nNameLth, cpcName );

   m_pchTimestamp = 0;
   m_lTimestampLth = 0;
   m_pchTimestamp = 0;
// m_DateTime = fnSTimeToDirtime( DateTime, 0, 0 );

   m_DateTime = DateTime;
   m_nState = 0;
   m_lSize = lSize;
   m_pFileNext = 0;
}

CFileData::~CFileData( )
{
   mDeleteInitA( m_pchName );
   mDeleteInitA( m_pchTimestamp );
   mDeleteInit( m_pFileNext );
}

void
CFileData::SetDate( zCPCHAR cpcTimestamp )
{
   mDeleteInitA( m_pchTimestamp );
   m_lTimestampLth = strlen( cpcTimestamp ) + 1;
   m_pchTimestamp = new char[ m_lTimestampLth ];
   strcpy_s( m_pchTimestamp, m_lTimestampLth, cpcTimestamp );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CDirData::CDirData( zCPCHAR  cpcName,
                    CDirData *pDirParent )
{
   // Name is the simple directory name ... without a trailing backslash
   m_pDirParent = pDirParent;
   m_nNameLth = (zSHORT) strlen( cpcName );  // it's ok to say we're shorter than we really are

   m_pchName = new char[ m_nNameLth + 1 ];
   strcpy_s( m_pchName, m_nNameLth + 1, cpcName );
   if ( m_nNameLth && cpcName[ m_nNameLth - 1 ] == '\\' )
   {
      m_nNameLth--;
      m_pchName[ m_nNameLth ] = 0;
   }

   m_pDirNext = 0;
   m_pSubDir = 0;
   m_pFileHead = 0;
}

CDirData::~CDirData( )
{
   mDeleteInitA( m_pchName );
   mDeleteInit( m_pDirNext );
   mDeleteInit( m_pSubDir );
   mDeleteInit( m_pFileHead );
}

CDirData *
CDirData::AddDir( zPCHAR pchDir )
{
   CDirData *pDir = this;  // we start with the "root" ... which must exist!
   zPCHAR pchSlash;
   zPCHAR pch = pchDir;

   if ( strchr( pchDir, ':' ) || pchDir[ 0 ] == 0 )
   {
      cerr << "WhyDir: " << pchDir << endl;
      return( this );
   }

   while ( pchDir )
   {
      pchSlash = strchr( pchDir, '\\' );
      if ( pchSlash )
         *pchSlash = 0;

      pDir = pDir->AddSubDir( pchDir );
      if ( pchSlash )
      {
         *pchSlash = '\\'; // go to the next sub-directory level
         pchDir = pchSlash + 1;
      }
      else
         break;
   }

   return( pDir );
}

CDirData *
CDirData::AddSubDir( zPCHAR pchDir )
{
// if ( strchr( pchDir, ':' ) || pchDir[ 0 ] == 0 )
//    cerr << "WhySubDir: " << pchDir << endl;

// if ( strchr( pchDir, '\\' ) )
//    cerr << "WhyMultiSubDir: " << pchDir << endl;

   zSHORT nDirLth = (zSHORT) strlen( pchDir );
   if ( nDirLth && pchDir[ nDirLth - 1 ] == '\\' )
   {
      nDirLth--;
      pchDir[ nDirLth ] = 0;
   }

   if ( m_pSubDir == 0 )
   {
      m_pSubDir = new CDirData( pchDir, this );
      return( m_pSubDir );
   }

   CDirData *pDir = m_pSubDir;  // we are positioned at the parent directory
   CDirData *pDirPrev = 0;
   zSHORT nRC;

   while ( pDir )
   {
      nRC = _stricmp( pDir->m_pchName, pchDir );
      if ( nRC == 0 )
      {
//       cerr << "AddSubDir duplicate: " << pchDir << endl;
         break; // already in list
      }
      else
      if ( nRC > 0 )
      {
         // We are beyond the directory in alpha order.  Put a new entry
         // in the list at this point.
         pDir = new CDirData( pchDir, pDir->m_pDirParent );
         if ( pDirPrev )
         {
            pDir->m_pDirNext = pDirPrev->m_pDirNext;
            pDirPrev->m_pDirNext = pDir;
         }
         else
         {
            pDir->m_pDirNext = m_pSubDir;
            m_pSubDir = pDir;
         }

         break;
      }
      else
//    if ( nRC < 0 )
      {
         pDirPrev = pDir;
         if ( pDir->m_pDirNext == 0 )
         {
            pDir->m_pDirNext = new CDirData( pchDir, pDir->m_pDirParent );
            pDir = pDir->m_pDirNext;
            break;
         }

         pDir = pDir->m_pDirNext;
      }
   }

   return( pDir );
}

CDirData *
CDirData::SeekDir( zPCHAR pchDir,
                   zSHORT nDirLth,
                   zSHORT nOrigDirLth )
{
   if ( nDirLth == nOrigDirLth )
      return( this );

   CDirData *pDir = this;  // we start with the "root" ... which must exist!
   zPCHAR pchSlash = 0;
   zPCHAR pch;
   zSHORT nRC;

   pchDir += nOrigDirLth;
   nDirLth -= (nOrigDirLth + 1);
   pchDir[ nDirLth ] = 0;
   pch = pchDir;
   pDir = pDir->m_pSubDir;
   while ( pDir && pch )
   {
      pchSlash = strchr( pch, '\\' );
      if ( pchSlash )
         *pchSlash = 0;

      nRC = _stricmp( pDir->m_pchName, pch );
      if ( nRC == 0 )
      {
         // We matched so far.
         if ( pchSlash == 0 )
            break;            // there are no more backslashes ... found it!
         else
         {
            *pchSlash = '\\'; // go to the next sub-directory level
            pchSlash++;
            pch = pchSlash;
            pchSlash = 0;
            pDir = pDir->m_pSubDir;
         }
      }
      else
      if ( nRC > 0 )
      {
         pDir = 0;            // we are beyond the directory in alpha order
         if ( pchSlash )
         {
            *pchSlash = '\\';
            pchSlash = 0;
         }
      }
      else
//    if ( nRC < 0 )
      {
         pDir = pDir->m_pDirNext;
         if ( pchSlash )
         {
            *pchSlash = '\\'; // we need to find the same slash again
            pchSlash = 0;
         }
      }
   }

   if ( pchSlash )
      *pchSlash = '\\'; // we got out without cleaning up (not found)

   pchDir[ nDirLth ] = '\\';
   return( pDir );
}

CFileData *
CDirData::AddFile( CFileData *pFileData )
{
   if ( strchr( pFileData->m_pchName, ':' ) )
      cerr << "WhyFile: " << pFileData->m_pchName << endl;

   if ( pFileData->m_pchName[ 0 ] == 0 )
   {
      delete( pFileData );
      return( 0 );
   }

// if ( strstr( pFileData->m_pchName, "BCOPY" ) )
//    cerr << "Adding BCOPY to dir: " << m_pchName << endl;

   if ( m_pFileHead )
   {
      zSHORT nRC;

      // Order file linked list alphabetically.
      CFileData *pFilePrev = 0;
      CFileData *pFileCurr = m_pFileHead;
      while ( pFileCurr )
      {
         nRC = _stricmp( pFileCurr->m_pchName, pFileData->m_pchName );
         if ( nRC == 0 )
         {
            cerr << "AddFile duplicate: " << pFileCurr->m_pchName << endl;
            mDeleteInit( pFileData );
            return( pFileCurr );
         }

         if ( nRC > 0 )
            break;

         pFilePrev = pFileCurr;
         pFileCurr = pFileCurr->m_pFileNext;
      }

      if ( pFilePrev )
      {
         pFileData->m_pFileNext = pFilePrev->m_pFileNext;
         pFilePrev->m_pFileNext = pFileData;
      }
      else
      {
         pFileData->m_pFileNext = m_pFileHead;
         m_pFileHead = pFileData;
      }
   }
   else
   {
      m_pFileHead = pFileData;
   }

   return( pFileData );
}

CFileData *
CDirData::SeekFile( zCPCHAR cpcFileName )
{
   zSHORT nRC;
   CFileData *pFileCurr = m_pFileHead;
   while ( pFileCurr )
   {
      nRC = _stricmp( pFileCurr->m_pchName, cpcFileName );
      if ( nRC == 0 )
         break;        // we found it!
      else
      if ( nRC > 0 )
         return( 0 );  // not in this ordered list
      else
         pFileCurr = pFileCurr->m_pFileNext;
   }

   return( pFileCurr );
}

CFileData *
CDirData::RemoveFile( zCPCHAR cpcFileName )
{
   zSHORT nRC;
   CFileData *pFilePrev = 0;
   CFileData *pFileCurr = m_pFileHead;
   while ( pFileCurr )
   {
      nRC = _stricmp( pFileCurr->m_pchName, cpcFileName );
      if ( nRC == 0 )
      {
         // We found it ... remove it from the linked list.
//         if ( pFilePrev )
//            pFilePrev->m_pFileNext = pFileCurr->m_pFileNext;
//         else
//            m_pFileHead = pFileCurr->m_pFileNext;

         break;
      }
      else
      if ( nRC > 0 )
         return( 0 );  // not in this ordered list
      else
      {
         pFilePrev = pFileCurr;
         pFileCurr = pFileCurr->m_pFileNext;
      }
   }

   return( pFileCurr );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

char g_Buffer[ BUFSIZE ];
char g_OutputBuffer[ BUFSIZE ];

/////////////////////////////////////////////////////////////////////////////
//
//  This routine reads a file into a large buffer and manages the
//  return of newline/null ("\n\0") terminated strings.
//
//  Input Parms:
//     1. Return Buffer.
//     2. Maximum size of Return Buffer.
//     3. FILE pointer (handle).
//
//  Outputs:
//     1. Return Buffer.
//     2. Length of Return Buffer (zero if end of file).
//        (Negative 1 is returned if the return string would be
//         longer than the Maximum size of the Return Buffer).
//
/////////////////////////////////////////////////////////////////////////////
zLONG
qreads( zPCHAR szReturnBuffer,
        zLONG  lMaxReturnBufferSize,
        FILE   *pSrcFile )
{
   zLONG lReturnByteCount;

   lReturnByteCount = 0;

   while ( lReturnByteCount < lMaxReturnBufferSize )
   {
      if ( g_lCurrBufferOffset < g_lNbrBytesRead )
      {
         szReturnBuffer[ lReturnByteCount ] = g_Buffer[ g_lCurrBufferOffset++ ];
         if ( szReturnBuffer[ lReturnByteCount ] == '\n' )
         {
            lReturnByteCount++;
            szReturnBuffer[ lReturnByteCount ] = '\0';
            break;
         }
         else
         if ( szReturnBuffer[ lReturnByteCount ] == EOF_CHAR )
         {
            szReturnBuffer[ lReturnByteCount ] = '\0';
            g_lNbrBytesRead = g_lCurrBufferOffset;
            break;
         }
         else
            lReturnByteCount++;
      }
      else
      {
         if ( g_chEofChar != ' ' )
         {
            g_lNbrBytesRead = 0;
            break;
         }
         else
         {
            g_lNbrBytesRead = fread( g_Buffer, sizeof( char ), MAXLINE, pSrcFile );
            g_lCurrBufferOffset = 0;
            if ( g_lNbrBytesRead < MAXLINE )
            {
               if ( feof( pSrcFile ) )
               {
                  g_chEofChar = g_Buffer[ g_lNbrBytesRead ];
                  if ( g_chEofChar == EOF_CHAR )
                     g_lNbrBytesRead--;
                  else
                  if ( g_chEofChar == ' ' )
                     g_chEofChar = '~';
               }
               else
               {
                  printf( "Error reading Source File - %d\n", ferror( pSrcFile ) );
                  exit( 1 );
               }
            }
         }
      }
   }

   if ( lReturnByteCount < lMaxReturnBufferSize )
      return( lReturnByteCount );
   else
      return( -1 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  This routine writes a file into a large buffer and manages the
//  return of newline/null ("\n\0") terminated strings.
//
//  Input Parms:
//     1. Return Buffer.
//     2. Maximum size of Return Buffer.
//     3. FILE pointer (handle).
//
//  Outputs:
//     1. Return Buffer.
//     2. Length of Return Buffer (zero if end of file).
//
/////////////////////////////////////////////////////////////////////////////
void
qwrites( zPCHAR szLineBuffer,
         zLONG  lLineBufferSize,
         FILE   *pTgtFile )
{
   zLONG k;

   if ( g_lNbrBytesWrite + lLineBufferSize < MAXLINE &&
        lLineBufferSize >= 0 )
   {
      for ( k = 0; k < lLineBufferSize; k++ )
         g_OutputBuffer[ g_lNbrBytesWrite++ ] = szLineBuffer[ k ];
   }
   else
   {
      k = fwrite( g_OutputBuffer, sizeof( char ),
                  g_lNbrBytesWrite, pTgtFile );
      if ( k != g_lNbrBytesWrite )
      {
         printf( "\nOutput file cannot be written\n" );
         printf( "****** Processing Aborted ******\n" );
         exit( 1 );
      }
      else
      {
         g_lNbrBytesWrite = 0;
         if ( lLineBufferSize > 0 )
            for ( k = 0; k < lLineBufferSize; k++ )
               g_OutputBuffer[ g_lNbrBytesWrite++ ] = szLineBuffer[ k ];
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
//
//  This routine searches a buffer for a string using the Boyer-Moore
//  algorithm.
//
//  Input Parms:
//     1. Pattern to locate
//     2. Pattern length
//     3. Buffer to be searched for pattern
//        - expanded (uncompressed) as necessary
//        - fixed length records
//     4. Length of Buffer to be searched
//     5. Boyer-Moore Delta1 table
//     6. Boyer-Moore Delta2 table
//
//  Returns:
//     1. Location of pattern within buffer (-1 if not found)
//
/////////////////////////////////////////////////////////////////////////////
zLONG
qfind( zSHORT  nPatternLth,          // pattern length
       zCPCHAR cpcPattern,           // pattern to locate
       zLONG   lBufferLth,           // length of buffer to be searched
       zPCHAR  pchBuffer,            // buffer to be searched for pattern
       zLONG   *plDelta1Table,       // Boyer-Moore Delta1 Table
       zLONG   *plDelta2Table )      // Boyer-Moore Delta2 Table
{
   zLONG  lPatternLoc;
   zSHORT nPatternLthMinus1;
   zLONG  j, k;

   if ( nPatternLth <= 0 )
      return( -1  );       // signal "not found in buffer"

   lPatternLoc = -1;

   if ( nPatternLth == 1 )
   {
      k = 0;
      while ( k < lBufferLth )
      {
         if ( cpcPattern[ 0 ] == pchBuffer[ k ] )
         {
            lPatternLoc = k;
            break;
         }
         else
            k++;
      }

      return( lPatternLoc );
   }

   nPatternLthMinus1 = nPatternLth - 1;
   k = nPatternLthMinus1;

   while ( k < lBufferLth )
   {
      while ( k < lBufferLth )     //  FAST Loop  */
      {
 //      printf( "%c - k before = %d  ", pchBuffer[ k ], k );
 //      j = (unsigned char) pchBuffer[ k ];
 //      j = plDelta1Table[ j ];
 //      k += j;
         k += plDelta1Table[ (unsigned char) pchBuffer[ k ] ];
 //      printf( " --  k after = %d\n", k );
      }

      if ( k < LARGE )      //  really past true end of string???
         break;             //    yes... terminate search
//
//  Undo the large skip caused by the match found in the FAST loop.
//  Check for complete match in SLOW loop.
//
      k -= LARGE;
      k--;
  //  printf( "k after FAST loop match = %d\n", k );
      j = nPatternLthMinus1 - 1;
      while ( pchBuffer[ k ] == cpcPattern[ j ] )     // SLOW Loop
      {
         if ( j > 0 )
         {
            k--;
            j--;
         }
         else
         {
            lPatternLoc = k;  // pattern found ... terminate search
            k = LARGE;        //  permit outer while exit
            break;            //  exit inner while
         }
      }   //  end of:   while ( pchBuffer[ k ] == cpcPattern[ j ] )

      if ( lPatternLoc == -1 )   //  pattern not yet found
      {
         j = k + plDelta2Table[ j + 1 ];
         k += plDelta1Table[ pchBuffer[ k ] ];
         if ( k < j || k >= LARGE )  // take largest possible jump
            k = j;
      }

   }   //  end of outer:  while ( k <= lBufferLth )

   return( lPatternLoc );

} // end of:  qfind

/////////////////////////////////////////////////////////////////////////////
//
//  This routine makes the requested change at the current location
//  and attempts to locate the next occurrence of the string to be
//  changed in the current buffer.
//
//  Input Parms:
//     1. Position at which to replace
//     2. Search Pattern Length
//     3. Search Pattern
//     4. Replace Pattern Length
//     5. Replace Pattern
//     6. Length of buffer to be searched
//     7. Buffer to be searched for pattern
//     8. Boyer-Moore Delta1 Table
//     9. Boyer-Moore Delta2 Table
//    10. Maximum length of resultant string
//
//  Outputs:
//     1. File with line #, line, and file name where string found
//        for each string (named CHANGE.RPT)
//
/////////////////////////////////////////////////////////////////////////////
zLONG
qchange( zLONG   lCurrentPos,       //  current position at which to repl
         zSHORT  nPatternLth,       //  pattern length
         zCPCHAR cpcPattern,        //  pattern to locate
         zSHORT  nReplaceLth,       //  replace string length
         zPCHAR  pchReplace,        //  replace string
         zLONG   *lBufferLth,       //  length of buffer to be searched
         zPCHAR  pchBuffer,         //  buffer to be searched for pattern
         zLONG   *plDelta1Table,    //  Boyer-Moore Delta1 Table
         zLONG   *plDelta2Table,    //  Boyer-Moore Delta2 Table
         zLONG   lMaxLth )          //  Maximum lth of resultant string
{
   zLONG  lRemainingLth;
   zLONG  lReturnPos;
   zSHORT nTrueDeltaLth;
   zLONG  k;

 //
 //  If the original and replacement patterns are the same length,
 //  the substitution is trivial.
 //  Otherwise, preserve original placement of characters within the
 //  original buffer as much as possible by checking spacing.
 //
 //  e.g.  changing Doug to Jim
 //  QCHANGE.C   -  written by Doug Sorensen   - create date 02/14/89
 //  QCHANGE.C   -  written by Jim Sorensen    - create date 02/14/89
 //
   if ( nReplaceLth == 0 )
   {
      strcpy_s( pchBuffer + lCurrentPos, _MAX_PATH, pchBuffer + lCurrentPos + nPatternLth );
      *lBufferLth -= nPatternLth;
      return( lCurrentPos );
   }

   nTrueDeltaLth = nReplaceLth - nPatternLth;
   if ( nTrueDeltaLth == 0 )
   {
      for ( k = 0; k < nReplaceLth; )
         pchBuffer[ lCurrentPos++ ] = pchReplace[ k++ ];

      lReturnPos = lCurrentPos;
   }
   else   // changing the resultant length of the buffer
   {
      char szTempBuffer[ BUFSIZE ];

      if ( *lBufferLth + nTrueDeltaLth > lMaxLth )
         return( *lBufferLth + nTrueDeltaLth );     // signal error

      lRemainingLth = *lBufferLth - lCurrentPos - nPatternLth + 1;

      for ( k = 0; k < lRemainingLth; k++ )
         szTempBuffer[ k ] = pchBuffer[ lCurrentPos + nPatternLth + k ];

      for ( k = 0; k < nReplaceLth; )
         pchBuffer[ lCurrentPos++ ] = pchReplace[ k++ ];

      lReturnPos = lCurrentPos;

      k = 0;
      while ( lRemainingLth > 0 )
      {
         if ( szTempBuffer[ k ] == '\n' )
         {
            while ( lRemainingLth-- )
               pchBuffer[ lCurrentPos++ ] = szTempBuffer[ k++ ];
         }
         else
         if ( szTempBuffer[ k ] == ' ' &&  szTempBuffer[ k + 1 ] == ' ' )
         {
            if ( nTrueDeltaLth < 0 )
            {
               while ( nTrueDeltaLth )
               {
                  pchBuffer[ lCurrentPos++ ] = ' ';
                  nTrueDeltaLth++;
               }

               while ( lRemainingLth-- )
                  pchBuffer[ lCurrentPos++ ] = szTempBuffer[ k++ ];
            }
            else
            if ( nTrueDeltaLth > 0 )
            {
               k++;
               nTrueDeltaLth--;
               lRemainingLth--;
            }
            else
            {
               while ( lRemainingLth-- )
                  pchBuffer[ lCurrentPos++ ] = szTempBuffer[ k++ ];
            }
         }   // end of:  if ( szTempBuffer[ k ] == ' ' &&  s...
         else
         {
            pchBuffer[ lCurrentPos++ ] = szTempBuffer[ k++ ];
            lRemainingLth--;
         }

      }   // end of:  while ( lRemainingLth > 0 )

      *lBufferLth += nTrueDeltaLth;

   }   // end of:  else of:  if ( !nTrueDeltaLth )

   return( lReturnPos );
}

/////////////////////////////////////////////////////////////////////////////
//
//  These routines create the Boyer-Moore Delta 1 and 2 tables to be
//  used for the Boyer-Moore search algorithm.
//
//  Input Parms:
//     1. Pattern for which to search
//
//  Output Parms:
//     1. Boyer-Moore Delta1 table
//     2. Boyer-Moore Delta2 table
//
/////////////////////////////////////////////////////////////////////////////

// local prototypes
void
fnLoadDeltaOne( zSHORT  nPatternLth,
                zCPCHAR cpcPattern,
                zLONG   *plDelta1Table );
void
fnLoadDeltaTwo( zSHORT  nPatternLth,
                zCPCHAR cpcPattern,
                zLONG   *plDelta2Table );


void
qbldelta( zSHORT  nPatternLth,       // pattern length
          zCPCHAR cpcPattern,        // pattern to locate
          zLONG   *plDelta1Table,    // Boyer-Moore Delta1 Table
          zLONG   *plDelta2Table )   // Boyer-Moore Delta2 Table
{
   fnLoadDeltaOne( nPatternLth, cpcPattern, plDelta1Table );
   fnLoadDeltaTwo( nPatternLth, cpcPattern, plDelta2Table );
}

void
fnLoadDeltaOne( zSHORT  nPatternLth,
                zCPCHAR cpcPattern,
                zLONG   *plDelta1Table )
{
   zSHORT  nPatternLthMinus1;
   zSHORT  k;

   nPatternLthMinus1 = nPatternLth - 1;

   // Init Delta1 to pattern length for all characters.
   for ( k = 0; k < ASCIISIZE; k++ )
      plDelta1Table[ k ] = nPatternLth;

   // Set Delta1 for characters in pattern.
   for ( k = 0; k < nPatternLth; k++ )
      plDelta1Table[ cpcPattern[ k ] ] = nPatternLthMinus1 - k;

   // Set Delta1 to large value for last char in pattern.
   plDelta1Table[ cpcPattern[ nPatternLthMinus1 ] ] = LARGE;

} // end of:  fnLoadDeltaOne

void
fnLoadDeltaTwo( zSHORT  nPatternLth,      // using Rytter's correction
                zCPCHAR cpcPattern,       // to Knuth's scheme
                zLONG   *plDelta2Table )
{
   zSHORT k,
          q,  j,  t,
          qi, ji, ti,
          nTwicePatternLth;
   zSHORT f[ MAXPATTERN ],
          fi[ MAXPATTERN ];

   nTwicePatternLth = nPatternLth * 2;

   for ( k = 1;  k <= nPatternLth;  k++ )
      plDelta2Table[ k ] = nTwicePatternLth - k;

   j = nPatternLth;
   t = nPatternLth + 1;

   while ( j > 0 )
   {
      f[ j ] = t;
      while ( t <= nPatternLth &&
              cpcPattern[ j - 1 ] != cpcPattern[ t - 1 ] )
      {
         if ( (zLONG) nPatternLth - j < plDelta2Table[ t ] )
            plDelta2Table[ t ] = nPatternLth - j;

         t = f[ t ];

      }   // end of:  while ( t <= ... )

      t--;
      j--;

   } // end of:  while ( j > 0 )

   q = t;
   t = nPatternLth + 1 - q;
   qi = 1;
   ji = 1;
   ti = 0;

   while ( ji <= t )
   {
      fi[ ji ] = ti;
      while ( ti >= 1 && cpcPattern[ ji - 1 ] != cpcPattern[ ti - 1 ] )
         ti = fi[ ti ];

      ti++;
      ji++;

   } // end of:  while ( ji <= t )

   while ( q < nPatternLth )
   {
      for ( k = qi; k <= q; k++ )
      {
         if ( (zLONG) nPatternLth + q - k < plDelta2Table[ k ] )
            plDelta2Table[ k ] = nPatternLth + q - k;
      }

      qi = q + 1;
      q += t - fi[ t ];
      t = fi[ t ];

   } // end of:  while ( q < nPatternLth )

} // end of:  fnLoadDeltaTwo

void
fnTraverseDirList( CDirData *pDir,
                   zPCHAR   pchDrivePath,
                   zSHORT   nDrivePathLth,
                   zCPCHAR  cpcFileMask,
                   zSHORT   nAttrib,
                   zBOOL    bLoadFiles,
                   zSHORT   nRootLth )
{
   zCHAR  szDriveDirSpec[ _MAX_PATH ];
   zSHORT nDriveDirSpecLth;
   zSHORT nLth = (zSHORT) strlen( pDir->m_pchName );
   zSHORT nRC;

   strcpy_s( szDriveDirSpec, _MAX_PATH, pchDrivePath );
   nDriveDirSpecLth = nDrivePathLth;
   strcpy_s( szDriveDirSpec + nDriveDirSpecLth, _MAX_PATH - nDriveDirSpecLth, pDir->m_pchName );
   nDriveDirSpecLth += nLth;
   szDriveDirSpec[ nDriveDirSpecLth++ ] = '\\';
   szDriveDirSpec[ nDriveDirSpecLth ] = 0;
   nLth++;

   if ( (nRC = g_fnDirBegin( pDir, szDriveDirSpec, nRootLth )) > 0 )
   {
      if ( bLoadFiles )
         fnLoadFileList( pDir, szDriveDirSpec, cpcFileMask, nAttrib );

      CFileData *pFile = pDir->m_pFileHead;
      while ( pFile )
      {
         g_lTotalFileCnt++;
         szDriveDirSpec[ nDriveDirSpecLth ] = 0;
         nRC = g_fnDirTroll( pFile, pDir, szDriveDirSpec );
         if ( nRC > 0 )
            g_lFilesFound++;
         else
         if ( nRC == 0 )
            g_lFilesExcluded++;

         pFile = pFile->m_pFileNext;
      }

      g_fnDirEnd( pDir, szDriveDirSpec );
      if ( bLoadFiles )
         mDeleteInit( pDir->m_pFileHead );

      nRC = 0;
   }

   if ( nRC >= 0 )
   {
      pDir = pDir->m_pSubDir;
      while ( pDir )
      {
         fnTraverseDirList( pDir, szDriveDirSpec, nDriveDirSpecLth,
                            cpcFileMask, nAttrib, bLoadFiles, nRootLth );
         pDir = pDir->m_pDirNext;
      }
   }

// nDriveDirSpecLth -= nLth;
// szDriveDirSpec[ nDriveDirSpecLth ] = 0;
}

/////////////////////////////////////////////////////////////////////////////
//
// Function:  fnDirExcluded
//
// Parameters:  Directory name to be checked for exclusion
//
/////////////////////////////////////////////////////////////////////////////
zBOOL
fnDirExcluded( zPCHAR pchDirName, zSHORT nRootLth )
{
   short  nDirNameLth = (zSHORT) strlen( pchDirName );
   short  nExcNameLth;
   CSLink *pLink = 0;
   zCHAR  szDirName[ _MAX_PATH ];


   if ( g_pListExclude )
      pLink = g_pListExclude->GetFirstLink( );

   while ( pLink )
   {
      nExcNameLth = (zSHORT) strlen( pLink->m_pchName );
      if ( nExcNameLth && nExcNameLth <= nDirNameLth &&
           pLink->m_pchName[ nExcNameLth - 1 ] == '\\' )
      {
         strcpy_s( szDirName, _MAX_PATH, pchDirName );
         short nLth = nDirNameLth;

         while ( nLth - nExcNameLth >= nRootLth )
         {
            if ( ((nLth - nExcNameLth > nRootLth &&
                   *(szDirName + nLth - nExcNameLth - 1) == '\\') ||
                   (nLth - nExcNameLth == nRootLth)) &&
                 _stricmp( pLink->m_pchName,
                           szDirName + nLth - nExcNameLth ) == 0 )
            {
               return( TRUE );
            }

            while ( nLth-- > nRootLth )
            {
               if ( szDirName[ nLth - 1 ] == '\\' )
               {
                  szDirName[ nLth ] = 0;
                  break;
               }
            }
         }
      }

      pLink = pLink->m_pNext;
   }

   return( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
zLONG
fnLoadDirList( CDirData *pParentDir,
               zPCHAR   pchParentPath,
               zBOOL    bSubdir,
               zBOOL    bLoadFiles,
               zCPCHAR  cpcFileMask,
               zSHORT   nAttrib )
{
// ASSERT( pParentDir );
   struct _finddata_t findDir;
   zSHORT nParentPathLth;
   zSHORT nCurrPathLth;
   zLONG  hFile;
   zLONG  lDirCnt = 1;

   nParentPathLth = (zSHORT) strlen( pchParentPath );
   if ( pParentDir->m_pchName[ 0 ] )
   {
      if ( nParentPathLth > 0 && pchParentPath[ nParentPathLth - 1 ] != '\\' )
         pchParentPath[ nParentPathLth++ ] = '\\';

      strcpy_s( pchParentPath + nParentPathLth, _MAX_PATH - nParentPathLth, pParentDir->m_pchName );
   }

   // cerr << "Load dir parent path = " << pchParentPath << endl;
   nCurrPathLth = (zSHORT) strlen( pchParentPath );
   if ( nCurrPathLth > 0 && pchParentPath[ nCurrPathLth - 1 ] != '\\' )
   {
      pchParentPath[ nCurrPathLth++ ] = '\\';
      pchParentPath[ nCurrPathLth ] = 0;
   }

   if ( bSubdir )
   {
      strcpy_s( pchParentPath + nCurrPathLth, _MAX_PATH - nCurrPathLth, "*.*" );
      hFile = _findfirst( pchParentPath, &findDir );
      while ( hFile != -1 )
      {
         if ( (findDir.attrib & _A_SUBDIR) && findDir.name[ 0 ] != '.' )
         {
            pParentDir->AddSubDir( findDir.name );
            lDirCnt++;
         }

         if ( _findnext( hFile, &findDir ) )
         {
            _findclose( hFile );
            hFile = -1;
         }
      }  // end of:  while ( hFile != -1 )

      if ( bLoadFiles )
      {
         pchParentPath[ nCurrPathLth ] = 0;
         g_lLoadFileCnt += fnLoadFileList( pParentDir, pchParentPath, cpcFileMask, nAttrib );
      }

      CDirData *pDir = pParentDir->m_pSubDir;
      while ( pDir )
      {
         pchParentPath[ nCurrPathLth ] = 0;
         lDirCnt += fnLoadDirList( pDir, pchParentPath, bSubdir, bLoadFiles, cpcFileMask, nAttrib );
         pDir = pDir->m_pDirNext;
      }
   }

// pchParentPath[ nCurrPathLth ] = 0;     // remove anything after curr dir
// fnLoadFileList( pParentDir, pchParentPath, cpcFileMask, nFileAttrib );
// pchParentPath[ nParentPathLth ] = 0;   // remove current subdirectory name
   return( lDirCnt );
}

zLONG
fnLoadFileList( CDirData *pDir,
                zPCHAR   pchParentPath,
                zCPCHAR  cpcFileMask,
                zSHORT   nAttrib )
{
   struct _finddata_t findFile;
// zSHORT nLth = strlen( pchParentPath );
// char   *pchOrigPath = new char[ nLth + 512 ];
   zLONG  hFile;
   zLONG  lFileCnt = 0;

// strcpy_s( pchOrigPath, pchParentPath );
// cerr << "Load file list mask = " << cpcFileMask << endl;
// cerr << "Trying to load files: " << pchParentPath << endl;
   strcat_s( pchParentPath, _MAX_PATH, cpcFileMask );
   hFile = _findfirst( pchParentPath, &findFile );
   while ( hFile != -1 )
   {
      if ( (findFile.attrib & _A_SUBDIR) == 0 )
      {
      // if ( _stricmp( findFile.name, "Granny.bmp" ) == 0 )
      //    cerr << "Processing: " << pchParentPath << "  ==> " << findFile.name << endl;

//       strcpy_s( pchOrigPath + nLth, findFile.name );
//       if ( _stat( pchOrigPath, &g_statBufferS ) == 0 )

         if ( g_pListInclude == 0 ||
              g_pListInclude->FindFile( findFile.name ) )
         {
            lFileCnt++;
            pDir->AddFile( new CFileData( findFile.name,
                                          findFile.time_write,
                                       // g_statBufferS.st_mtime,
                                          findFile.size ) );
         }
//       else
//          cerr << "Cannot relocate " << pchParentPath
//               << " skipping file" << endl;
      }

      if ( _findnext( hFile, &findFile ) )
      {
         _findclose( hFile );
         hFile = -1;
      }

   }  // end of:  while ( nRC == 0 )

// mDeleteInitA( pchOrigPath );
   return( lFileCnt );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
void
fnDisplayLinkList( CSLink *pLink )
{
   while ( pLink )
   {
      cout << "Item: " << pLink->m_pchName << endl;
      pLink = pLink->m_pNext;
   }
}
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Function:  fnGetY_N
//
// Parameters: char *pchValidResponse - string of valid responses (must
//                                      be upper case!!!
//             char *pchPrompt - Prompt to elicit response
//
/////////////////////////////////////////////////////////////////////////////
char
fnGetY_N( zPCHAR pchValidResponse,
          zPCHAR pchPrompt )
{
   zUSHORT uCurrChar;
   char    ch;
   zSHORT  nCharOK = 0;

   cerr << pchPrompt;
   cerr.flush( );
   while ( nCharOK < 2 )
   {
      uCurrChar = cin.get( );
      if ( uCurrChar == 0 )      // extended ASCII character
      {
         uCurrChar = cin.get( );
         if ( uCurrChar == 75 )  // cursor left
         {
            if ( nCharOK > 0 )
            {
               nCharOK = 0;
               cerr.put( '\b' );
               cerr.put( '\0' );
               cerr.put( '\b' );
               cerr.flush( );
            }
         }
      }
      else
      if ( uCurrChar == '\n'  ||  uCurrChar == '\r' )
      {
//       cerr.put( '\n' );
         cerr.flush( );
         if ( nCharOK == 1 )
         {
            nCharOK = 2;
         }
         else
         {
            cerr << pchPrompt;
            cerr.flush( );
         }
      }
      else
      if ( uCurrChar == '\b' )
      {
         if ( nCharOK > 0 )
         {
            nCharOK = 0;
            cerr.put( '\b' );
            cerr.put( '\0' );
            cerr.put( '\b' );
            cerr.flush( );
         }
      }
      else
      if ( uCurrChar == '?' )
      {
         char *pch;

         pch = pchValidResponse;
         cerr << "Valid responses are:" << endl;
         while ( *pch )
         {
            cerr << "   " << *pch << endl;
            pch++;
         }
      }
      else
      {
         ch = toupper( uCurrChar );
         if ( strchr( pchValidResponse, ch ) )
         {
            if ( nCharOK == 0 )
               nCharOK = 1;
         }
      }
   }

   return( ch );
}

/////////////////////////////////////////////////////////////////////////////
//
// zBOOL
// MatchFilenameToWildcard( zCPCHAR cpcWildcardSpec,
//                          zCPCHAR cpcFileName )
//
// returns:
//
//   TRUE  - if cpcFileName could have been found using the
//           specified cpcWildcardSpec mask.
//
//   FALSE - if szFileName could not have been found using the mask
//
// Notes:
//    If no period (i.e. no file extension) is specified, following
//    defaults are taken:
//
//    For szWildcardSpec ".*" is used.
//
//    For szFileName "." is used.
//
/////////////////////////////////////////////////////////////////////////////
zBOOL
MatchFilenameToWildcard( zCPCHAR cpcWildcardSpec,
                         zCPCHAR cpcFileName )
{
// cerr << "MatchFilenameToWildcard " << cpcFileName << endl;
// cerr << "               Wildcard " << cpcWildcardSpec << endl;
   enum f_string
   {
      asterisk = '*',
      question_mark = '?',
      period = '.'
   };

   char   szStr1[ _MAX_PATH ],
          szStr2[ _MAX_PATH ];
   zPCHAR pchStr1;
   zPCHAR pchStr2;
   zBOOL  bFirstNameDone = FALSE;

   strcpy_s( szStr1, cpcWildcardSpec );
   strcpy_s( szStr2, cpcFileName );

   _strupr_s( szStr1, _MAX_PATH );
   _strupr_s( szStr2, _MAX_PATH );

   if ( strchr( szStr1, '.' ) == 0 )
      strcat_s( szStr1, _MAX_PATH, ".*" );

   if ( strchr( szStr2, '.' ) == 0 )
      strcat_s( szStr2, _MAX_PATH, "." );

   for ( pchStr1 = szStr1, pchStr2 = szStr2; *pchStr1 ; pchStr1++ )
   {
      switch ( pchStr1[ 0 ] )
      {
         case asterisk:
            if ( bFirstNameDone )
               return( TRUE );         // indicate match

            bFirstNameDone = TRUE;     // indicate filename done

            // position szStr1 pointer to period less one
            pchStr1 = strchr( pchStr1, '.' ) - 1;

            // position szStr2 pointer to period
            pchStr2 = strrchr( pchStr2, '.' );

            break;

         case question_mark:
            if ( bFirstNameDone )
            {
               if ( *pchStr2 )
                  pchStr2++;
            }
            else
            {
               if ( *pchStr2 != '.' )
                  pchStr2++;
            }
            break;

         case period:
            bFirstNameDone = TRUE;
            if ( *pchStr2 != '.' )
               return( FALSE );        // not a match

            pchStr2++;
            break;

         default:
            if ( *pchStr1 != *pchStr2 )
               return( FALSE );        // indicate no match

            pchStr2++;
            break;
      }
   }

   // If we are at the end of string two we have a match!  Otherwise not!
   if ( *pchStr2 == 0 )
      return( TRUE );
   else
      return( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
//
// Function:  fnRotateAction
//
// Parameters:  char *szPrompt - Prompt to elicit response
//
/////////////////////////////////////////////////////////////////////////////
void
fnRotateAction( zBOOL bRestart )
{
   static zSHORT nChar = -1;
   static char   szRotate[ ] = "|/-\\";

   if ( bRestart || nChar >= 3 )
      nChar = 0;
   else
      nChar++;

   cerr.put( szRotate[ nChar ] );
   cerr.put( '\b' );
   cerr.flush( );
}

/////////////////////////////////////////////////////////////////////////////
//
// Function:  fnCompareFiles
//
// Parameters:
//
// Returns:  TRUE - files compare (identical)
//           FALSE - files differ
//
/////////////////////////////////////////////////////////////////////////////
zBOOL
fnCompareFiles( zPCHAR pchSrcDir,
                zPCHAR pchTgtDir,
                FILE   *pRptFile )
{
   FILE *pSrcFile;
   FILE *pTgtFile;
   char szSrcBuffer[ BUFSIZE ];
   char szTgtBuffer[ BUFSIZE ];
   size_t nSrcBytesRead;
   size_t nTgtBytesRead;
   size_t nTotalSrcBytesRead = 0;
   size_t nTotalTgtBytesRead = 0;

   if ( fopen_s( &pSrcFile, pchSrcDir, READFILE ) != 0 )
      return( FALSE );

   if ( fopen_s( &pTgtFile, pchTgtDir, READFILE ) != 0 )
   {
      fclose( pSrcFile );
      return( FALSE );
   }

// cerr << "Comparing files: " << pchSrcDir << "  " << pchTgtDir << "\n";
   while ( feof( pSrcFile ) == 0 && feof( pTgtFile ) == 0 )
   {
      nSrcBytesRead = fread( szSrcBuffer, sizeof( char ),
                             MAXLINE, pSrcFile );
      nTgtBytesRead = fread( szTgtBuffer, sizeof( char ),
                             MAXLINE, pTgtFile );
      nTotalSrcBytesRead += nSrcBytesRead;
      nTotalTgtBytesRead += nTgtBytesRead;
      if ( nSrcBytesRead == nTgtBytesRead &&
           (nSrcBytesRead > 0 &&
            memcmp( szSrcBuffer, szTgtBuffer, nSrcBytesRead )) )
      {
      // cout << "** Same size/different content: " << szTgtDir << endl;
      // if ( pRptFile )
      //    fprintf( pRptFile, "(Same size/Differs.....) %s \n", szTgtDir );

         if ( nTotalSrcBytesRead == nTotalTgtBytesRead )
            nTotalTgtBytesRead = nTotalSrcBytesRead - 1;

         break;

      // fclose( pSrcFile );
      // fclose( pTgtFile );
      // return( FALSE );
      }
   }

   fclose( pSrcFile );
   fclose( pTgtFile );
   if ( nTotalSrcBytesRead == nTotalTgtBytesRead )
      return( TRUE );
   else
      return( FALSE );
}

// Check the line to see if it's binary or if it has text characteristics.  Returns
// TRUE if it finds binary characteristics.
// If a file consists of nothing but printable ASCII characters, then it is by definition an ASCII file.
zBOOL
fnCheckBinary( zPCHAR pchText )
{
   zLONG k = 0;

   if ( strchr( pchText, '\n' ) == 0 )
   {
      while ( pchText[ k ] )
      {
         if ( pchText[ k ] == 9 || pchText[ k ] == 10 || (pchText[ k ] >= 32 && pchText[ k ] <= 126) )
            k++;
         else
            return( TRUE );
      }
   }

   return( FALSE );
}

zBOOL
fnCheckLineForSpecifiedText( zCPCHAR cpcText1, zCPCHAR cpcText2, CSList *pListIgnore )
{
   CSLink *pLink = 0;

   if ( pListIgnore )
      pLink = pListIgnore->GetFirstLink( );

   while ( pLink )
   {
      if ( strstr( cpcText1, pLink->m_pchName ) && strstr( cpcText2, pLink->m_pchName ) )
         return( TRUE );

      pLink = pLink->m_pNext;
   }

   return( FALSE );
}

zSHORT
CompareBinaryFiles( zPCHAR pchFirstFile, zPCHAR pchSecondFile )
{
   char szBuffer1[ BUFSIZE ];
   char szBuffer2[ BUFSIZE ];
   FILE *f1;
   FILE *f2;
   zLONG lth1;
   zLONG lth2;
   zSHORT nRC = FILE_COMPARE_EQUAL;

   if ( fopen_s( &f1, pchFirstFile, READBINARY ) != 0 )
      f1 = 0;

   if ( fopen_s( &f2, pchSecondFile, READBINARY ) != 0 )
      f2 = 0;

   if ( f1 && f2 )
   {
      while ( !feof( f1 ) && !feof( f2 ) ) {
         lth1 = fread( szBuffer1, 1, BUFSIZE, f1 );
         lth2 = fread( szBuffer2, 1, BUFSIZE, f2 );
         if ( lth1 != lth2 || memcmp( szBuffer1, szBuffer2, lth1 ) != 0 )
         {
            nRC = FILE_COMPARE_DIFFERENT;
            break;
         }
      }
   }
   else
   {
      nRC = FILE_COMPARE_ERROR;
   }

   if ( f1 )
      fclose( f1 );

   if ( f2 )
      fclose( f2 );

   return( nRC );
}

zSHORT
CompareTextFiles( zPCHAR pchFirstFile,
                  zPCHAR pchSecondFile,
                  zLONG  lFirstFileLth,
                  zSHORT nOutputType,
                  FILE   *pRptFile,
                  zBOOL  bIgnoreWhiteSpace,
                  CSList *pListIgnore )
{
   zPCHAR pchT1 = 0;
   zPCHAR pchT2 = 0;
   zPCHAR pchT1_Temp = 0;
   zPCHAR pchT2_Temp = 0;
   zCHAR  szText1[ MAX_LINE_LENGTH + 1 ];  // add one for binary file check
   zCHAR  szText2[ MAX_LINE_LENGTH + 1 ];  // add one for binary file check
   zCHAR  szText3[ MAX_LINE_LENGTH * 2 ];  // extra for message
   zCHAR  szText1_Temp[ MAX_LINE_LENGTH ];
   zCHAR  szText2_Temp[ MAX_LINE_LENGTH ];
   zLONG  lCurrentLine1 = 0;
   zLONG  lCurrentLine2 = 0;
   zLONG  lTotalLines1 = 0;
   zLONG  lTotalLines2 = 0;
   zLONG  lOffset1 = -1;
   zLONG  lOffset2 = -1;
   zLONG  lFileLth = 0;
   zLONG  k;
   zLONG  j;
   zBOOL  bText1AllBlank;
   zBOOL  bText2AllBlank;
   zBOOL  bCompareNextLine;
   zSHORT nRC = FILE_COMPARE_DIFFERENT;

   // Check for valid file names.
   if ( pchFirstFile && pchSecondFile )
   {
      // Initialize a null byte for binary check below.
      szText1[ MAX_LINE_LENGTH ] = 0;
      szText2[ MAX_LINE_LENGTH ] = 0;

      // Try to open files.
      FILE *f1;
      FILE *f2;
      if ( fopen_s( &f1, pchFirstFile, "r" ) != 0 )
         f1 = 0;

      if ( fopen_s( &f2, pchSecondFile, "r" ) != 0 )
         f2 = 0;

      // Open log file.
   // FILE *pRptFile = 0;  log file is passed into this routine
      sprintf_s( szText3, MAX_LINE_LENGTH, "Comparing files: %s ... %s\n", pchFirstFile, pchSecondFile );
      if ( nOutputType == OUTPUT_TYPE_SCREEN )
      {
         printf( szText3 );
      }
      else
      if ( nOutputType == OUTPUT_TYPE_FILE )
      {
         if ( pRptFile )
         {
         // fopen_s( &pRptFile, "Log.txt", "w" );
            fputs( szText3, pRptFile );
         }
         else
            nOutputType = OUTPUT_TYPE_NONE;
      }

      // Check for valid files.
      if ( f1 && f2 )
      {
         nRC = FILE_COMPARE_EQUAL;
         do
         {
            // Increment line counters.
            lCurrentLine1++;
            lCurrentLine2++;

            // Read single line of text from files.  NULL return indicates error or EOF
            pchT1 = fgets( szText1, MAX_LINE_LENGTH, f1 );
            lFileLth += strlen( szText1 );
            pchT2 = fgets( szText2, MAX_LINE_LENGTH, f2 );

            if ( lCurrentLine1 == 1 &&
                 ((fnCheckBinary( szText1 ) || fnCheckBinary( szText2 )) || (feof( f1 ) && lFileLth < lFirstFileLth)) )
            {
               // It's either binary or has very long lines.
#if 1
               fclose( f1 );
               f1 = NULL;
               fclose( f2 );
               f2 = NULL;
               return( CompareBinaryFiles( pchFirstFile, pchSecondFile ) );
#else
               sprintf_s( szText3, MAX_LINE_LENGTH, "\nIgnoring binary file: [File1, %s] [File2, %s]\n",
                        pchFirstFile, pchSecondFile );
               if ( nOutputType == OUTPUT_TYPE_SCREEN )
                  printf( szText3 );
               else
               if ( nOutputType == OUTPUT_TYPE_FILE )
                  fputs( szText3, pRptFile );
               else
                  cerr << szText3 << endl;

               fclose( f1 );
               fclose( f2 );
               return( FILE_COMPARE_BINARY );
#endif
            }

         // if ( strstr( szText1, "Sum = 0.0;" ) )
         //    nRC /= k - k;

            // Compare lines of text.
            if ( strcmp( szText1, szText2 ) == 0 )
            {
            }
            else
            if ( fnCheckLineForSpecifiedText( szText1, szText2, pListIgnore ) == TRUE )
            {
               if ( nRC > FILE_COMPARE_DIFFERENT )
                  nRC = FILE_COMPARE_IGNORE;
            }
            else
            {
               bCompareNextLine = FALSE;
               while ( bIgnoreWhiteSpace )  // purist's goto
               {
                  // First check to see if only difference is whitespace.
                  if ( szText1[ 0 ] && szText2[ 0 ] )
                  {
                     bText1AllBlank = TRUE;
                     bText2AllBlank = TRUE;
                  }
                  else
                  {
                     if ( szText1[ 0 ] )
                        bText1AllBlank = FALSE;

                     if ( szText2[ 0 ] )
                        bText2AllBlank = FALSE;
                  }

                  for ( j = k = 0; szText1[ j ] && szText2[ k ]; )
                  {
                     if ( szText1[ j ] == szText2[ k ] )
                     {
                        if ( bText1AllBlank && isspace( szText1[ j ] ) == 0 )
                           bText1AllBlank = FALSE;

                        if ( bText2AllBlank && isspace( szText2[ k ] ) == 0 )
                           bText2AllBlank = FALSE;

                        j++;
                        k++;
                     }
                     else
                     if ( (szText1[ j ] == 0 || isspace( szText1[ j ] )) || (szText2[ k ] == 0 || isspace( szText2[ k ] )) )
                     {
                        while ( isspace( szText1[ j ] ) )
                           j++;

                        while ( isspace( szText2[ k ] ) )
                           k++;
                     }
                     else
                     {
                        bText1AllBlank = FALSE;
                        bText2AllBlank = FALSE;
                        break;  // out of for
                     }
                  }

                  if ( szText1[ j ] == szText2[ k ] )
                  {
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\nWhitespace Differences Line: [File1, %d] [File2, %d]\n%s",
                              lCurrentLine1, lCurrentLine2, szText1 );
                     if ( nOutputType == OUTPUT_TYPE_SCREEN )
                        printf( szText3 );
                     else
                     if ( nOutputType == OUTPUT_TYPE_FILE )
                        fputs( szText3, pRptFile );

                     if ( nRC > FILE_COMPARE_DIFFERENT && nRC < FILE_COMPARE_IGNORE )
                        nRC = FILE_COMPARE_WHITESPACE;

                     bCompareNextLine = TRUE;  // cause us to continue outer loop
                  }
                  else
                  {
                     if ( bText1AllBlank || bText2AllBlank )
                     {
                        if ( bText1AllBlank )
                        {
                           bText1AllBlank = FALSE;
                           if ( szText1[ j ] == 0 || isspace( szText1[ j ] ) )
                           {
                              lCurrentLine1++;
                              pchT1 = fgets( szText1, MAX_LINE_LENGTH, f1 );
                              if ( pchT1 == 0 )
                                 szText1[ 0 ] = 0;

                              lFileLth += strlen( szText1 );
                           }
                        }

                        if ( bText2AllBlank )
                        {
                           bText2AllBlank = FALSE;
                           if ( szText2[ k ] == 0 || isspace( szText2[ k ] ) )
                           {
                              lCurrentLine2++;
                              pchT2 = fgets( szText2, MAX_LINE_LENGTH, f2 );
                              if ( pchT2 == 0 )
                                 szText2[ 0 ] = 0;
                           }
                        }

                        continue;  // retry compare after skipping an "all blank line"
                     }
                  }

                  break;  // out of inner loop

               }  // end of:  purist's goto

               if ( bCompareNextLine )
                  continue;  // compare next line

               nRC = FILE_COMPARE_DIFFERENT;
               if ( nOutputType == OUTPUT_TYPE_NONE )
                  break;  // no need to go further since we are not reporting differences

               // Scan through second file looking for equal lines.
               lTotalLines2 = 0;
               lOffset2 = ftell( f2 );
               FILE *f2t;
               fopen_s( &f2t, pchSecondFile, "r" );
               fseek( f2t, lOffset2, SEEK_SET );
               do
               {
                  // Skip different lines
                  lTotalLines2++;
                  pchT2_Temp = fgets( szText2_Temp, MAX_LINE_LENGTH, f2t );

               } while ( pchT2_Temp && (strcmp( szText1, szText2_Temp ) != 0) );

               fclose( f2t );

               // Scan through first file looking for equal lines.
               lTotalLines1 = 0;
               lOffset1 = ftell( f1 );
               FILE *f1t;
               fopen_s( &f1t, pchFirstFile, "r" );
               fseek( f1t, lOffset1, SEEK_SET );
               do
               {
                  // Skip different lines.
                  lTotalLines1++;
                  pchT1_Temp = fgets( szText1_Temp, MAX_LINE_LENGTH, f1t );

               } while ( pchT1_Temp && (strcmp( szText2, szText1_Temp ) != 0) );

               fclose( f1t );

               // Compare lines passed (find minimum).
               if ( pchT1_Temp || pchT2_Temp )
               {
                  if ( lTotalLines2 < lTotalLines1 )
                  {
                     // Scan through second file looking for equal lines.
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\n******************************* Start Differences Section *******************************\n" );
                  // nRC /= k - k;
                     if ( nOutputType == OUTPUT_TYPE_SCREEN )
                     {
                        printf( szText3 );
                        printf( "\t\t[File2, %d]: %s", lCurrentLine2, szText2 );
                     }
                     else
                     if ( nOutputType == OUTPUT_TYPE_FILE )
                     {
                        fputs( szText3, pRptFile );
                        sprintf_s( szText3, MAX_LINE_LENGTH, "\t\t[File2, %d]: %s", lCurrentLine2, szText2 );
                        fputs( szText3, pRptFile );
                     }

                     lOffset2 = ftell( f2 );
                     FILE *f2t;
                     fopen_s( &f2t, pchSecondFile, "r" );
                     fseek( f2t, lOffset2, SEEK_SET );
                     for ( k = 0; k < lTotalLines2 - 1; k++ )
                     {
                        fgets( szText2_Temp, MAX_LINE_LENGTH, f2t );
                        if ( nOutputType == OUTPUT_TYPE_SCREEN )
                        {
                           printf( "\t\t[File2, %d]: %s", lCurrentLine2 + k + 1, szText2_Temp );
                        }
                        else
                        if ( nOutputType == OUTPUT_TYPE_FILE )
                        {
                           sprintf_s( szText3, "\t\t[File2, %d]: %s", lCurrentLine2 + k + 1, szText2_Temp );
                           fputs( szText3, pRptFile );
                        }
                     }

                     fgets( szText2_Temp, MAX_LINE_LENGTH, f2t );
                     lOffset2 = ftell( f2t );
                     fseek( f2, lOffset2, SEEK_SET );
                     fclose( f2t );
                     lCurrentLine2 += lTotalLines2;
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\n******************************* End Differences Section   *******************************\n" );
                     if ( nOutputType == OUTPUT_TYPE_SCREEN )
                        printf( szText3 );
                     else
                     if ( nOutputType == OUTPUT_TYPE_FILE )
                        fputs( szText3, pRptFile );
                  }
                  else
                  {
                     // Scan through first file looking for equal lines.
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\n******************************* Start Differences Section *******************************\n" );
                  // nRC /= k - k;
                     if ( nOutputType == OUTPUT_TYPE_SCREEN )
                     {
                        printf( szText3 );
                        printf( "\t\t[File1, %d]: %s", lCurrentLine1, szText1 );
                     }
                     else
                     if ( nOutputType == OUTPUT_TYPE_FILE )
                     {
                        fputs( szText3, pRptFile );
                        sprintf_s( szText3, MAX_LINE_LENGTH, "\t\t[File1, %d]: %s", lCurrentLine1, szText1 );
                        fputs( szText3, pRptFile );
                     }

                     lOffset1 = ftell( f1 );
                     FILE *f1t;
                     fopen_s( &f1t, pchFirstFile, "r" );
                     fseek( f1t, lOffset1, SEEK_SET );
                     for ( k = 0; k < lTotalLines1 - 1; k++ )
                     {
                        fgets( szText1_Temp, MAX_LINE_LENGTH, f1t );
                        if ( nOutputType == OUTPUT_TYPE_SCREEN )
                        {
                           printf( "\t\t[File1, %d]: %s", lCurrentLine1+k+1, szText1_Temp );
                        }
                        else
                        if ( nOutputType == OUTPUT_TYPE_FILE )
                        {
                           sprintf_s( szText3, MAX_LINE_LENGTH, "\t\t[File1, %d]: %s", lCurrentLine1+k+1, szText1_Temp );
                           fputs( szText3, pRptFile );
                        }
                     }

                     fgets( szText1_Temp, MAX_LINE_LENGTH, f1t );
                     lOffset1 = ftell( f1t );
                     fseek( f1, lOffset1, SEEK_SET );
                     fclose( f1t );
                     lCurrentLine1 += lTotalLines1;
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\n******************************* End Differences Section   *******************************\n" );
                     if ( nOutputType == OUTPUT_TYPE_SCREEN )
                        printf( szText3 );
                     else
                     if ( nOutputType == OUTPUT_TYPE_FILE )
                        fputs( szText3, pRptFile );
                  }
               }
               else
               {
                  sprintf_s( szText3, MAX_LINE_LENGTH, "\n******************************* Start Differences Section *******************************\n" );
               // nRC /= k - k;
                  if ( nOutputType == OUTPUT_TYPE_SCREEN )
                  {
                     printf( szText3 );
                     printf( "\t\t[File1, %d]: %s", lCurrentLine1, szText1 );
                     printf( "\t\t[File2, %d]: %s", lCurrentLine2, szText2 );
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\n******************************* End Differences Section   *******************************\n" );
                     printf( szText3 );
                  }
                  else
                  if ( nOutputType == OUTPUT_TYPE_FILE )
                  {
                     fputs( szText3, pRptFile );
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\t\t[File1, %d]: %s", lCurrentLine1, szText1 );
                     fputs( szText3, pRptFile );
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\t\t[File2, %d]: %s", lCurrentLine2, szText2 );
                     fputs( szText3, pRptFile );
                     sprintf_s( szText3, MAX_LINE_LENGTH, "\n******************************* End Differences Section   *******************************\n" );
                     fputs( szText3, pRptFile );
                  }
               }
            }

         } while ( pchT1 && pchT2 );

         // Show success.
         sprintf_s( szText3, MAX_LINE_LENGTH, "Success: %s %s %s compared!\n\n",
                  pchFirstFile, nRC >= FILE_COMPARE_EQUAL ? "==" : "!=", pchSecondFile );

         if ( nOutputType == OUTPUT_TYPE_SCREEN )
            printf( szText3 );
         else
         if ( nOutputType == OUTPUT_TYPE_FILE )
            fputs( szText3, pRptFile );
      // else
      //    cerr << szText3 << endl;
      }
      else
      {
         nRC = FILE_COMPARE_ERROR;
         sprintf_s( szText3, MAX_LINE_LENGTH,  "Error: %s file %s cannot be found!\n\n",
                  f1 ? "Second" : "First", f1 ? pchSecondFile: pchFirstFile );

         // Show error
         if ( nOutputType == OUTPUT_TYPE_SCREEN )
            printf( szText3 );
         else
         if ( nOutputType == OUTPUT_TYPE_FILE )
            fputs( szText3, pRptFile );
      // else
      //    cerr << szText3 << endl;
      }

      // Close files.
      if ( f1 )
         fclose( f1 );

      if ( f2 )
         fclose( f2 );

   // if ( nOutputType == OUTPUT_TYPE_FILE )
   // {
   //    // Close log file.
   //    fclose( pRptFile );
   // }
   }

// if ( nRC == FILE_COMPARE_WHITESPACE )
//    nRC /= nRC - nRC;

   return( nRC );
}

/////////////////////////////////////////////////////////////////////////////
//
// regex - Regular expression pattern matching and replacement.
//
//
// By:  Ozan S. Yigit (oz)
//      Dept. of Computer Science
//      York University
//
// This source has been altered to match the following documentation:
//
//  Meaning                                               Regular Expression
//  ----------------------------------------------------  ------------------
//  Cursor positioning                                        \c
//  Group expressions for searches                            { }
//  Match beginning of line                                   % <
//  Match end of line                                         $ >
//  Match either preceding or following character             |
//  Match tab character                                       \t
//  Match newline character                                   \n
//  Match one or more occurrences of previous character       +
//  Match zero or more occurrences of previous character      @
//  Match one character or range                              [ ]
//     Specify range to search for                            [ - ]
//     Specify characters not to match                        [~ ]
//  Numbers group in search expressions                       \num
//  Override regular expressions                              \
//  Specify numeric ASCII value                               \xhex number
//  Wildcard matching - exactly one character                 ?
//  match the beginning and/or ending of a word               ( )
//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
//
// These routines are the PUBLIC DOMAIN equivalents
// of regex routines as found in 4.nBSD UN*X, with minor
// extensions.
//
// These routines are derived from various implementations
// found in software tools books, and Conroy's grep. They
// are NOT derived from licensed/restricted software.
// For more interesting/academic/complicated implementations,
// see Henry Spencer's regexp routines, or GNU Emacs pattern
// matching module.
//
// Routines:
//   RE_Compile:     compile a regular expression into a DFA.
//
//      zPCHAR
//      RE_Compile( zPCHAR s );
//
//   RE_Match:       execute the DFA to match a pattern.
//
//      zSHORT
//      RE_Match( zPCHAR s );
//
//   RE_ModWord:     change RE_Match's understanding of what a "word"
//                   looks like (for \< and \>) by adding into the
//                   hidden word-character table.
//
//      void
//      RE_ModWord( zPCHAR s );
//
//   RE_Substitute:  substitute the matched portions in a new string.
//
//      zSHORT
//      RE_Substitute( zPCHAR src,
//                     zPCHAR dst );
//
//   RE_Fail:        failure routine for RE_Match.
//
//      void
//      RE_Fail( zPCHAR msg,
//               zCHAR op );
//
// Regular Expressions:
//
//      [1]    char     matches itself, unless it is a special character
//                      (metachar):  \ [ ] ? * + ~ $ % < > { } ( )
//
//      [2]    * ?      matches any (? ==> exactly one) character
//
//      [3]     \       matches the character following it, except when
//                      followed by a digit 1 to 9 (see [7], [8] and [9]).
//                      It is used as an escape character for all other
//                      meta-characters, and itself.  When used in a set
//                      (e.g. [4]), it is treated as an ordinary character.
//
//      [4]   [set]     matches one of the characters in the set.  If the
//                      first character in the set is "~", it matches a
//                      character NOT in the set.  A shorthand S-E is used
//                      to specify a set of characters S upto E, inclusive.
//                      The special characters "]" and "-" have no special
//                      meaning if they appear as the first chars in the set.
//
//                      examples:        match:
//
//                         [a-z]         any lowercase alpha
//
//                         [~]-]         any char except ] and -
//
//                         [~A-Z]        any char except uppercase alpha
//
//                         [a-zA-Z]      any alpha
//
//      [5]     @       any regular expression form [1] to [4], followed by
//                      closure char @ matches zero or more matches of that
//                      form.
//
//      [6]     +       same as [5], except it matches one or more.
//
//      [7]    { }      a regular expression in the form [1] to [10], enclosed
//                      as {form} matches what form matches.  The enclosure
//                      creates a set of tags, used for [8] and for pattern
//                      substitution.  The tagged forms are numbered starting
//                      from 1.
//
//      [8]   \digit    a \ followed by a digit 1 to 9 matches whatever a
//                      previously tagged regular expression ([7]) matched.
//
//      [9]    ( )      a regular expression starting with a (construct
//                      and/or ending with a) construct, restricts the
//                      pattern matching to the beginning of a word, and/or
//                      the end of a word.  A word is defined to be a character
//                      string beginning and/or ending with the characters
//                      A-Z a-z 0-9 and _.  It must also be preceded and/or
//                      followed by any character excluding those mentioned.
//
//      [10]            a composite regular expression xy where x and y are
//                      in the form [1] to [10] matches the longest match of
//                      x followed by a match for y.
//
//      [11]   < >      a regular expression starting with a < or % character
//             % $      and/or ending with a > or $ character, restricts the
//                      pattern matching to the beginning of the line, or
//                      the end of line. [a'; ors] Elsewhere in the pattern,
//                      <, %, > and $ are treated as ordinary characters.
//
//
// Acknowledgements:
//
//    HCR's Hugh Redelmeier has been most helpful in various stages of
//    development.  He convinced me to include BOW and EOW constructs,
//    originally invented by Rob Pike at the University of Toronto.
//
// References:
//    Software tools             Kernighan & Plauger
//    Software tools in Pascal   Kernighan & Plauger
//    Grep [rsx-11 C dist]       David Conroy
//    ed - text editor           Un*x Programmer's Manual
//    Advanced editing on Un*x   B. W. Kernighan
//    RegExp routines            Henry Spencer
//
// Notes:
//
//    This implementation uses a bit-set representation for character
//    classes for speed and compactness. Each character is represented
//    by one bit in a 128-bit block. Thus, CCL or NCL always takes a
//    constant 16 bytes in the internal dfa, and RE_Match does a single
//    bit comparison to locate the character in the set.
//
// Examples:
//
//    pattern:   foo*.*
//    compile:   CHR f CHR o CLO CHR o END CLO ANY END END
//    matches:   fo foo fooo foobar fobar foxx ...
//
//    pattern:   fo[ob]a[rz]
//    compile:   CHR f CHR o CCL 2 o b CHR a CCL bitset END
//    matches:   fobar fooar fobaz fooaz
//
//    pattern:   foo\\+
//    compile:   CHR f CHR o CHR o CHR \ CLO CHR \ END END
//    matches:   foo\ foo\\ foo\\\  ...
//
//    pattern:   \{foo\}[1-3]\1   (same as foo[1-3]foo)
//    compile:   BOT 1 CHR f CHR o CHR o EOT 1 CCL bitset REF 1 END
//    matches:   foo1foo foo2foo foo3foo
//
//    pattern:   \{fo.*\}-\1
//    compile:   BOT 1 CHR f CHR o CLO ANY END EOT 1 CHR - REF 1 END
//    matches:   foo-foo fo-fo fob-fob foobar-foobar ...
//
//////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
void
symbolic( zPCHAR sz );
void
dfadump( zDFA *ap );
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

zSHORT  g_naTagStack[ zMAXTAG ];    // subpat tag stack..
zDFA    g_dfa[ zMAXDFA ];           // automaton..
zSHORT  g_nStatus = zNOP;           // status of lastpat
zCHAR   g_bitCCL_Table[ zBITBLK ];  // bit table for CCL

zPCHAR g_pchBOL;
zPCHAR g_pchBeginMatch[ zMAXTAG ];
zPCHAR g_pchEndMatch[ zMAXTAG ];
zDFA   *g_pdfaJump[ zMAXTAG ];
zCHAR  g_szJumpB[ zMAXTAG ];
zCHAR  g_szJumpE[ zMAXTAG ];
zSHORT g_pnJumpBSub[ zMAXTAG ];
zSHORT g_nJumpRecurse = 0;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// i'd like to document this, but i can't since i don't know what it's
// doing ... yet.
void
RE_CharSet( zCHAR ch )
{
   g_bitCCL_Table[ (( ch ) & zBLKIND) >> 3 ] |= 1 << (( ch ) & zBITIND);
}

#define mInvalidPattern( x )   return( *g_dfa = zEND, x )
#define mStoreCh( x )    *pdfaCurr++ = x

//////////////////////////////////////////////////////////////////////////////
//
//   RE_Compile:  compile a regular expression into a DFA.
//
//////////////////////////////////////////////////////////////////////////////
zPCHAR
RE_Compile( zPCHAR pchPattern )
{
   zPCHAR pch;                     // pattern pointer
   zDFA   *pdfaCurr = g_dfa;       // dfa pointer
   zDFA   *pdfaSave;               // saved dfa pointer..
   zDFA   *pdfaHold = g_dfa;       // another one..
   zDFA   *pdfaTemp;               // a temporary dfa pointer..

   zSHORT nTagIdx = 0;             // tag stack index
   zSHORT nTagCnt = 1;             // actual tag count

   zSHORT ch1, ch2;
   zSHORT k;

   if ( !pchPattern || !*pchPattern )
   {
      if ( g_nStatus )
         return( 0 );
      else
         mInvalidPattern( "No previous regular expression" );
   }

   g_nStatus = zNOP;
   for ( pch = pchPattern; *pch; pch++ )
   {
      pdfaSave = pdfaCurr;
      switch( *pch )
      {
         case '|':               // match either preceding or following char..
            if ( pch == pchPattern || *(pch + 1) == 0 ||
                 pdfaCurr[ -1 ] == zBOL || pdfaCurr[ -1 ] == zBOT ||
                 pdfaCurr[ -1 ] == zBOW || pdfaCurr[ -1 ] == zCCL ||
                 pdfaCurr[ -1 ] == zNCL || *(pch + 1) == '}'     ||
                 *(pch + 1) == ']'     || *(pch + 1) == ')' )
            {
               mInvalidPattern( "| cannot start or end pattern" );
            }

            g_nJumpRecurse++;
            g_pnJumpBSub[ g_nJumpRecurse ] = 1;
            switch( *(pch + 1) )
            {
               case '{':
                  g_szJumpB[ g_nJumpRecurse ] = zBOT;
                  g_szJumpE[ g_nJumpRecurse ] = zEOT;
                  break;

               case '(':
                  g_szJumpB[ g_nJumpRecurse ] = zBOW;
                  g_szJumpE[ g_nJumpRecurse ] = zEOW;
                  break;

               case '[':
                  g_szJumpB[ g_nJumpRecurse ] = zCCL;
                  g_szJumpE[ g_nJumpRecurse ] = zCCL;
                  break;

               default:
                  g_szJumpB[ g_nJumpRecurse ] = zCHR;
                  g_szJumpE[ g_nJumpRecurse ] = zCHR;
            }

            // We are going to move previous "char group" two steps forward
            // to make room for OR and its corresponding offset.
            pdfaCurr += 2;

            mStoreCh( zJMP );
            g_pdfaJump[ g_nJumpRecurse ] = pdfaCurr;
            mStoreCh( 0 ); // this will be set properly as soon as possible

            pdfaTemp = pdfaCurr;  // hold on to current position
            pdfaCurr -= 3; // back up to position at which to start move

            // Move OR op and offset prior to the previous "char group".
            g_pnJumpBSub[ 0 ] = 0;     // for recursive groups
            g_szJumpE[ 0 ] = pdfaCurr[ -2 ];
            if ( g_szJumpE[ 0 ] == zEOL )
               g_szJumpB[ 0 ] = zBOL;
            else
            if ( g_szJumpE[ 0 ] == zEOT )
               g_szJumpB[ 0 ] = zBOT;
            else
            if ( g_szJumpE[ 0 ] == zEOW )
               g_szJumpB[ 0 ] = zBOW;
            else
            {
               // case zCHR
               if ( pdfaCurr - 3 >= g_dfa )
               {
                  *pdfaCurr = *(pdfaCurr - 2);
                  *(pdfaCurr - 1) = *(pdfaCurr - 3);
                  pdfaCurr -= 3;
                  mStoreCh( zOR );
                  mStoreCh( pdfaTemp - g_dfa );
                  pdfaCurr = pdfaTemp;
                  break;   // out of switch
               }
               else
                  mInvalidPattern( "| position to early" );
            }

            while ( pdfaCurr - 2 >= g_dfa )
            {
               *pdfaCurr = pdfaCurr[ -2 ];
               if ( *pdfaCurr == g_szJumpB[ 0 ] )
               {
                  if ( g_pnJumpBSub[ 0 ] == 1 )
                  {
                     pdfaCurr -= 2;
                     mStoreCh( zOR );
                     mStoreCh( pdfaTemp - g_dfa );
                     pdfaCurr = pdfaTemp;
                     break;  // out of while
                  }
                  else
                     g_pnJumpBSub[ 0 ]--;
               }
               else
               if ( *pdfaCurr == g_szJumpE[ 0 ] )
                  g_pnJumpBSub[ 0 ]++;

               pdfaCurr--;
            }

            if ( pdfaCurr != pdfaTemp )
               mInvalidPattern( "invalid | position" );

            break;

         case '*':               // match any (Zero-2-Many) char..
            mStoreCh( zZ2M );
            break;

         case '?':               // match any char..
            mStoreCh( zANY );
            break;

         case '<':               // match beginning-of-line..
         case '%':               // match beginning-of-line..
            if ( pch == pchPattern )
               mStoreCh( zBOL );
            else
            {
               mStoreCh( zCHR );
               mStoreCh( *pch );
            }

            break;

         case '>':               // match end-of-line..
         case '$':               // match end-of-line..
            if ( !*(pch + 1) )
               mStoreCh( zEOL );
            else
            {
               mStoreCh( zCHR );
               mStoreCh( *pch );
            }

            break;

         case '{':
            if ( nTagCnt < zMAXTAG )
            {
               if ( g_nJumpRecurse )
               {
                  if ( g_szJumpB[ g_nJumpRecurse ] == zBOT )
                     g_pnJumpBSub[ g_nJumpRecurse ]++;
               }

               g_naTagStack[ ++nTagIdx ] = nTagCnt;
               mStoreCh( zBOT );
               mStoreCh( (zCHAR) nTagCnt++ );
            }
            else
               mInvalidPattern( "Too many { } pairs" );

            break;

         case '}':
            if ( *pdfaHold == zBOT )
               mInvalidPattern( "Null pattern inside { }" );

            if ( nTagIdx > 0 )
            {
               mStoreCh( zEOT );
               mStoreCh( (zCHAR) g_naTagStack[ nTagIdx-- ] );

               if ( g_nJumpRecurse )
               {
                  if ( g_szJumpE[ g_nJumpRecurse ] == zEOT )
                     g_pnJumpBSub[ g_nJumpRecurse ]--;

                  if ( g_pnJumpBSub[ g_nJumpRecurse ] == 1 )
                  {
                     pdfaTemp = pdfaCurr;   // hold it for a second
                     pdfaCurr = g_pdfaJump[ g_nJumpRecurse ];
                     mStoreCh( pdfaTemp - g_dfa );
                     pdfaCurr = pdfaTemp;   // get it back

                     g_nJumpRecurse--;
                  }
               }
            }
            else
               mInvalidPattern( "Unmatched }" );

            break;

         case '(':
            mStoreCh( zBOW );
            break;

         case ')':
            if ( *pdfaHold == zBOW )
               mInvalidPattern( "Null pattern inside ( )" );

            mStoreCh( zEOW );
            if ( g_nJumpRecurse )
            {
               if ( g_szJumpE[ g_nJumpRecurse ] == zEOW )
               {
                  pdfaTemp = pdfaCurr;   // hold it for a second
                  pdfaCurr = g_pdfaJump[ g_nJumpRecurse ];
                  mStoreCh( pdfaTemp - g_dfa );
                  pdfaCurr = pdfaTemp;   // get it back

                  g_nJumpRecurse--;
               }
            }

            break;

         case '[':               // match char class..
            if ( *++pch == '~' )
            {
               mStoreCh( zNCL );
               pch++;
            }
            else
               mStoreCh( zCCL );

            if ( *pch == '-' )      // real dash
               RE_CharSet( *pch++ );

            if ( *pch == ']' )      // real bracket
               RE_CharSet( *pch++ );

            while ( *pch && *pch != ']' )
            {
               if ( *pch == '-' && *(pch + 1) && *(pch + 1) != ']' )
               {
                  pch++;
                  ch1 = *(pch - 2) + 1;
                  ch2 = *pch++;
                  while ( ch1 <= ch2 )
                     RE_CharSet( (zCHAR) ch1++ );
               }
#ifdef EXTEND
               else
               if ( *pch == '\\' && *(pch + 1) )
               {
                  pch++;
                  RE_CharSet( *pch++ );
               }
#endif
               else
                  RE_CharSet( *pch++ );
            }

            if ( !*pch )
               mInvalidPattern( "Missing ]" );

            for ( k = 0; k < zBITBLK; g_bitCCL_Table[ k++ ] = 0 )
               mStoreCh( g_bitCCL_Table[ k ] );

            if ( g_nJumpRecurse )
            {
               if ( g_szJumpE[ g_nJumpRecurse ] == zCCL )
               {
                  pdfaTemp = pdfaCurr;   // hold it for a second
                  pdfaCurr = g_pdfaJump[ g_nJumpRecurse ];
                  mStoreCh( pdfaTemp - g_dfa );
                  pdfaCurr = pdfaTemp;   // get it back

                  g_nJumpRecurse--;
               }
            }

            break;

         case '@':        // match 0 or more occurrences of previous char..
         case '+':        // match 1 or more occurrences of previous char..
            if ( pch == pchPattern )
               mInvalidPattern( "Empty closure" );

            pdfaSave = pdfaHold;       // previous opcode
            if ( *pdfaSave == zCLO )    // equivalence..
               break;

            switch( *pdfaSave )
            {
               case zBOL:
               case zBOT:
               case zEOT:
               case zBOW:
               case zEOW:
               case zREF:
                  mInvalidPattern( "Illegal closure" );
               default:
                  break;
            }

            if ( *pch == '+' )
            {
               for ( pdfaHold = pdfaCurr; pdfaSave < pdfaHold; pdfaSave++ )
                  mStoreCh( *pdfaSave );
            }

            mStoreCh( zEND );
            mStoreCh( zEND );
            pdfaHold = pdfaCurr;
            while ( --pdfaCurr > pdfaSave )
               *pdfaCurr = pdfaCurr[ -1 ];

            mStoreCh( zCLO );
            pdfaCurr = pdfaHold;

            if ( g_nJumpRecurse )
            {
               if ( g_szJumpE[ g_nJumpRecurse ] == zCHR )
               {
                  pdfaTemp = pdfaCurr;   // hold it for a second
                  pdfaCurr = g_pdfaJump[ g_nJumpRecurse ];
                  mStoreCh( pdfaTemp - g_dfa );
                  pdfaCurr = pdfaTemp;   // get it back

                  g_nJumpRecurse--;
               }
            }

            break;

         case '\\':              // tags, backrefs..
            switch( *++pch )
            {
               case '1':
               case '2':
               case '3':
               case '4':
               case '5':
               case '6':
               case '7':
               case '8':
               case '9':
                  k = *pch - '0';
                  if ( nTagIdx > 0 && g_naTagStack[ nTagIdx ] == k )
                     mInvalidPattern( "Cyclical reference" );

                  if ( nTagCnt > k )
                  {
                     mStoreCh( zREF );
                     mStoreCh( (zCHAR) k );
                  }
                  else
                     mInvalidPattern( "Undetermined reference" );

                  break;
#ifdef EXTEND
               case 'b':
                  mStoreCh( zCHR );
                  mStoreCh( '\b' );
                  break;

               case 'n':
                  mStoreCh( zCHR );
                  mStoreCh( '\n' );
                  break;

               case 'f':
                  mStoreCh( zCHR );
                  mStoreCh( '\f' );
                  break;

               case 'r':
                  mStoreCh( zCHR );
                  mStoreCh( '\r' );
                  break;

               case 't':
                  mStoreCh( zCHR );
                  mStoreCh( '\t' );
                  break;
#endif
               default:
                  mStoreCh( zCHR );
                  mStoreCh( *pch );
            }

            if ( g_nJumpRecurse )
            {
               if ( g_szJumpE[ g_nJumpRecurse ] == zCHR )
               {
                  pdfaTemp = pdfaCurr;   // hold it for a second
                  pdfaCurr = g_pdfaJump[ g_nJumpRecurse ];
                  mStoreCh( pdfaTemp - g_dfa );
                  pdfaCurr = pdfaTemp;   // get it back

                  g_nJumpRecurse--;
               }
            }

            break;

         default :               // an ordinary char
            mStoreCh( zCHR );
            mStoreCh( *pch );
            if ( g_nJumpRecurse )
            {
               if ( g_szJumpE[ g_nJumpRecurse ] == zCHR )
               {
                  pdfaTemp = pdfaCurr;   // hold it for a second
                  pdfaCurr = g_pdfaJump[ g_nJumpRecurse ];
                  mStoreCh( pdfaTemp - g_dfa );
                  pdfaCurr = pdfaTemp;   // get it back

                  g_nJumpRecurse--;
               }
            }

            break;
      }

      pdfaHold = pdfaSave;
   }

   if ( nTagIdx > 0 )
      mInvalidPattern( "Unmatched {" );

   mStoreCh( zEND );
   g_nStatus = zOKP;
   return( 0 );
}

//////////////////////////////////////////////////////////////////////////////
//
// RE_Match:
//    execute dfa to find a match to the pattern
//
//   special cases: (g_dfa[ 0 ])
//      zBOL
//         Match only once, starting from the beginning.
//      zCHR
//         First locate the character without calling RE_PatternMatch, and
//         if found, call RE_PatternMatch for the remaining string.
//      zEND
//         RE_Compile failed, poor luser did not check for it.  Fail fast.
//
//   If a match is found, g_pchBeginMatch[ 0 ] and g_pchEndMatch[ 0 ] are set
//   to the beginning and the end of the matched fragment, respectively, and
//   return TRUE.  Otherwise return FALSE.
//
//////////////////////////////////////////////////////////////////////////////
zBOOL
RE_Match( zPCHAR pchString )
{
   zCHAR ch;
   zPCHAR pch = 0;
   zDFA *pdfaCurr = g_dfa;

   g_pchBOL = pchString;

   g_pchBeginMatch[ 0 ] = 0;
   g_pchBeginMatch[ 1 ] = 0;
   g_pchBeginMatch[ 2 ] = 0;
   g_pchBeginMatch[ 3 ] = 0;
   g_pchBeginMatch[ 4 ] = 0;
   g_pchBeginMatch[ 5 ] = 0;
   g_pchBeginMatch[ 6 ] = 0;
   g_pchBeginMatch[ 7 ] = 0;
   g_pchBeginMatch[ 8 ] = 0;
   g_pchBeginMatch[ 9 ] = 0;

   switch( *pdfaCurr )
   {
      case zBOL:           // anchored: match from zBOL only
         pch = RE_PatternMatch( pchString, pdfaCurr );
         break;

      case zCHR:           // ordinary char: locate it fast
         ch = *(pdfaCurr + 1);
         while ( *pchString && *pchString != ch )
            pchString++;

         if ( *pchString == 0 )      // if EOS, fail, else fall thru
            return( FALSE );

      default:            // regular matching all the way
         while ( *pchString )
         {
            if ( (pch = RE_PatternMatch( pchString, pdfaCurr )) != 0 )
               break;

            pchString++;
         }

         break;

      case zEND:           // munged automaton.  fail always
         return( FALSE );
   }

   if ( pch == 0 )
      return( FALSE );

   g_pchBeginMatch[ 0 ] = pchString;
   g_pchEndMatch[ 0 ] = pch;
   return( TRUE );
}

//////////////////////////////////////////////////////////////////////////////
//
// RE_PatternMatch:
//   internal routine for the hard part
//
//   This code is mostly snarfed from an early
//   grep written by David Conroy. The backref and
//   tag stuff, and various other mods are by oZ.
//
//   special cases: (g_dfa[ n ], g_dfa[ n + 1 ])
//      zCLO zANY
//         We KNOW "?@" will match ANYTHING
//         upto the end of line. Thus, go to
//         the end of line straight, without
//         calling RE_PatternMatch recursively. As in
//         the other closure cases, the remaining
//         pattern must be matched by moving
//         backwards on the string recursively,
//         to find a match for xy (x is "?@" and
//         y is the remaining pattern) where
//         the match satisfies the LONGEST match
//         for x followed by a match for y.
//      zCLO CHR
//         We can again scan the string forward
//         for the single char without recursion,
//         and at the point of failure, we execute
//         the remaining dfa recursively, as
//         described above.
//
//   At the end of a successful match, g_pchBeginMatch[ n ] and
//   g_pchEndMatch[ n ] are set to the beginning and end of subpatterns
//   matched by tagged expressions (n = 1..9).
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// character classification table for word boundary operators zBOW and zEOW.
// The reason for not using ctype macros is that we can let the user add
// into our own table.  See RE_ModWord.  This table is not in the bitset form,
// since we may wish to extend it in the future for other character
// classifications.
//
// Note that TRUE is set for:  0-9 A-Z a-z _
//
//////////////////////////////////////////////////////////////////////////////
static zCHAR chrtyp[ zMAXCHR ] =
{
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 0, 0, 0, 0, 1, 0, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 0, 0, 0, 0, 0
};

#define inascii( x )    (0177 & ( x ))
#define iswordc( x )    chrtyp[ inascii( x ) ]
#define isinset( x, y ) ((x)[ ((y) & zBLKIND) >> 3 ] & (1 << ((y) & zBITIND)))

// Skip values for zCLO XXX to skip past the closure.
#define zANYSKIP   2       // zCLO zANY zEND ...
#define zCHRSKIP   3       // zCLO CHR chr zEND ...
#define zCCLSKIP   18      // zCLO zCCL 16bytes zEND ...

zPCHAR
RE_PatternMatch( zPCHAR pchString,
                 zDFA *pdfaCurr )
{
   zPCHAR pchExtra;             // extra pointer for zCLO and OR
   zPCHAR pchBeginSubPattern;   // beginning of subpat..
   zPCHAR pchEndSubPattern;     // ending of subpat..
   zPCHAR pchLinePtr;           // to save the line ptr
   zSHORT chOp, ch, k;

   while ( (chOp = *pdfaCurr++) != zEND )
   {
      switch( chOp )
      {
         case zCHR:
            if ( *pchString++ != *pdfaCurr++ )
               return( 0 );

            break;

         case zANY:
            if ( !*pchString++ )
               return( 0 );

            break;

         case zZ2M:
            if ( *pdfaCurr == zCHR )
            {
               ch = *(pdfaCurr + 1);
               while ( *pchString && *pchString != '\n' && *pchString != ch )
                  pchString++;
            }
            else
            if ( *pdfaCurr == zEOW )
            {
               while ( iswordc( *pchString ) )
                  pchString++;
            }

            // there could be other end conditions that need to be taken
            // into account here ... will take care of them as they arise.

            break;

         case zOR:
            // At some point we must pass through 2 "char groups".
            pdfaCurr++;
            if ( RE_PatternMatch( pchString, pdfaCurr ) != 0 )
               break;

            pdfaCurr = g_dfa + pdfaCurr[ -1 ];
            if ( RE_PatternMatch( pchString, pdfaCurr ) != 0 )
               break;

            return( 0 );

         case zJMP:
            pdfaCurr = g_dfa + *pdfaCurr;
            break;

         case zCCL:
            ch = *pchString++;
            if ( !isinset( pdfaCurr, ch ) )
               return( 0 );

            pdfaCurr += zBITBLK;
            break;

         case zNCL:
            ch = *pchString++;
            if ( isinset( pdfaCurr, ch ) )
               return( 0 );

            pdfaCurr += zBITBLK;
            break;

         case zBOL:
            if ( pchString != g_pchBOL )
               return( 0 );

            break;

         case zEOL:
            if ( *pchString )
               return( 0 );

            break;

         case zBOT:
            g_pchBeginMatch[ *pdfaCurr++ ] = pchString;
            break;

         case zEOT:
            g_pchEndMatch[ *pdfaCurr++ ] = pchString;
            break;

          case zBOW:
            if ( !(pchString != g_pchBOL && iswordc( pchString[ -1 ] )) &&
                 iswordc( *pchString ) )
            {
               break;
            }

            return( 0 );

         case zEOW:
            if ( (pchString != g_pchBOL && iswordc( pchString[ -1 ] )) &&
                 !iswordc( *pchString ) )
            {
               break;
            }

            return( 0 );

         case zREF:
            k = *pdfaCurr++;
            pchBeginSubPattern = g_pchBeginMatch[ k ];
            pchEndSubPattern = g_pchEndMatch[ k ];
            while ( pchBeginSubPattern < pchEndSubPattern )
            {
               if ( *pchBeginSubPattern++ != *pchString++ )
                  return( 0 );
            }

            break;

         case zCLO:
            pchLinePtr = pchString;
            switch( *pdfaCurr )
            {
               case zANY:
                  while ( *pchString )
                     pchString++;

                  k = zANYSKIP;
                  break;

               case zCHR:
                  ch = *(pdfaCurr + 1);
                  while ( *pchString && ch == *pchString )
                     pchString++;

                  k = zCHRSKIP;
                  break;

               case zCCL:
               case zNCL:
                  while ( *pchString &&
                          (pchExtra = RE_PatternMatch( pchString, pdfaCurr )) != 0 )
                  {
                     pchString = pchExtra;
                  }

                  k = zCCLSKIP;
                  break;

               default:
                  RE_Fail( "closure: invalid dfa.", *pdfaCurr );
                  return( 0 );
            }

            pdfaCurr += k;
            while ( pchString >= pchLinePtr )
            {
               if ( (pchExtra = RE_PatternMatch( pchString, pdfaCurr )) != 0 )
                  return( pchExtra );

               pchString--;
            }

            return( 0 );

         default:
            RE_Fail( "RE_Match: invalid dfa.", (zCHAR) chOp );
            return( 0 );
      }
   }

   return( pchString );
}

//////////////////////////////////////////////////////////////////////////////
//
// RE_ModWord:
//
//    Add new characters into the word table to change the RE_Match's
//    understanding of what a word should look like for (and).
//    Note that we only accept additions into the word definition.
//
//    If the string parameter is 0 or a null string, the table is reset
//    back to the default, which contains A-Z a-z 0-9 _ (we use the
//    compact bitset representation for the default table)
//
//////////////////////////////////////////////////////////////////////////////
static zCHAR deftab[ 16 ] =
{
   (zCHAR) 0,   (zCHAR) 0,   (zCHAR) 0,   (zCHAR) 0,
   (zCHAR) 0,   (zCHAR) 0,   (zCHAR) 377, (zCHAR) 003,
   (zCHAR) 376, (zCHAR) 377, (zCHAR) 377, (zCHAR) 207,
   (zCHAR) 376, (zCHAR) 377, (zCHAR) 377, (zCHAR) 007
};

void
RE_ModWord( zPCHAR sz )
{
   zSHORT k;

   if ( !sz || !*sz )
   {
      for ( k = 0; k < zMAXCHR; k++ )
      {
         if ( !isinset( deftab, k ) )
            iswordc( k ) = 0;
      }
   }
   else
   {
      while ( *sz )
         iswordc( *sz++ ) = 1;
   }
}

//////////////////////////////////////////////////////////////////////////////
//
// RE_Substitute:
//
//    substitute the matched portions of the source in the destination.
//
//    &        substitute the entire matched pattern.
//
//    \digit   substitute a subpattern, with the given tag number. Tags are
//             numbered from 1 to 9. If the particular tagged subpattern
//             does not exist, null is substituted.
//
//////////////////////////////////////////////////////////////////////////////
zSHORT
RE_Substitute( zPCHAR pchSrc,
               zPCHAR pchTgt )
{
   zCHAR  ch;
   zSHORT nIdx;
   zPCHAR pchBeginSubPattern;
   zPCHAR pchEndSubPattern;

   if ( pchTgt )
      *pchTgt = 0;

   if ( *pchSrc == 0 || g_pchBeginMatch[ 0 ] == 0 || pchTgt == 0 )
      return( 0 );

   while ( (ch = *pchSrc++) != 0 )
   {
      switch ( ch )
      {
         case '&':
            nIdx = 0;
            break;

         case '\\':
            ch = *pchSrc++;
            if ( ch >= '0' && ch <= '9' )
            {
               nIdx = ch - '0';
               break;
            }

         default:
            *pchTgt++ = ch;
            continue;
      }

      if ( (pchBeginSubPattern = g_pchBeginMatch[ nIdx ]) != 0 &&
           (pchEndSubPattern = g_pchEndMatch[ nIdx ]) != 0 )
      {
         while ( *pchBeginSubPattern && pchBeginSubPattern < pchEndSubPattern )
            *pchTgt++ = *pchBeginSubPattern++;

         if ( pchBeginSubPattern < pchEndSubPattern )
            return( 0 );
      }
   }

   *pchTgt = 0;
   return( 1 );
}

void
RE_Fail( zPCHAR pchMessage,
         zCHAR chOp )
{
   printf( "(RE_Fail) %s %c\n", pchMessage, chOp );
   exit( 1 );
}


#ifdef DEBUG
//////////////////////////////////////////////////////////////////////////////
//
// symbolic - produce a symbolic dump of the dfa.
//
//////////////////////////////////////////////////////////////////////////////
void
symbolic( zPCHAR sz )
{
   printf( "pattern: %s\n", sz );
   printf( "dfacode:\n" );
   dfadump( g_dfa );
}

void
dfadump( zDFA *pdfaCurr )
{
   zSHORT k;

   while ( *pdfaCurr != zEND )
   {
      switch( *pdfaCurr++ )
      {
         case zCLO:
            printf( "CLOSURE" );
            dfadump( pdfaCurr );
            switch( *pdfaCurr )
            {
               case zCHR:
                  k = zCHRSKIP;
                  break;

               case zANY:
                  k = zANYSKIP;
                  break;

               case zCCL:
               case zNCL:
                  k = zCCLSKIP;
                  break;
            }

            pdfaCurr += k;
            break;

         case zCHR:
            printf( "\tCHR  %c\n", *pdfaCurr++ );
            break;

         case zANY:
            printf( "\tANY  ?\n" );
            break;

         case zZ2M:
            printf( "\tZ2M  *\n" );
            break;

         case zOR:
            printf( "\tOR   %d\n", *pdfaCurr++ );
            break;

         case zJMP:
            printf( "\tJMP  %d\n", *pdfaCurr++ );
            break;

         case zBOL:
            printf( "\tBOL  -\n" );
            break;

         case zEOL:
            printf( "\tEOL  -\n" );
            break;

         case zBOT:
            printf( "BOT: %d\n", *pdfaCurr++ );
            break;

         case zEOT:
            printf( "EOT: %d\n", *pdfaCurr++ );
            break;

         case zBOW:
            printf( "BOW\n" );
            break;

         case zEOW:
            printf( "EOW\n" );
            break;

         case zREF:
            printf( "REF: %d\n", *pdfaCurr++ );
            break;

         case zCCL:
            printf( "\tCCL [" );
            for ( k = 0; k < zMAXCHR; k++ )
            {
               if ( isinset( pdfaCurr, (zCHAR) k ) )
                  printf( "%c", k );
            }

            printf( "]\n" );
            pdfaCurr += zBITBLK;
            break;

         case zNCL:
            printf( "\tNCL [" );
            for ( k = 0; k < zMAXCHR; k++ )
            {
               if ( isinset( pdfaCurr, (zCHAR) k ) )
                  printf( "%c", k );
            }

            printf( "]\n" );
            pdfaCurr += zBITBLK;
            break;

         default:
            printf( "invalid dfa - opcode %o\n", pdfaCurr[ -1 ] );
            exit( 1 );
            break;
      }
   }
}
#endif

//
// 컴컴컴컴컴컴컴컴컴�
// regular expressions
// 컴컴컴컴컴컴컴컴컴�
// regular expressions can be used to find or replace text. If you have ever
// typed "dir *.exe" from a command prompt then you have used the regular
// expression * before.
//
//   *            skips zero or more characters
//   ?            skips one character
//   < or %       finds the beginning of a line
//   > or $ or \n finds the end of a line
//   @            finds zero or more of the previous expression
//   +            finds one or more of the previous expression
//   |            finds either the previous or the next expression
//   [a-g]        finds a character between a and g
//   [~x-z]       finds any character except x through z
//   {}           defines a group inside the braces
//   \c           positions the cursor at this location after matching
//   \t           finds tabs
//   \xHH         finds the ascii character defined by two hex digits
//   \0 \1 .. \9  inserts text matched by its {} group (use with replace)
//   \            treat next character literally
//
//   examples:
//
//   th[eo]se     finds the word these or those
//   {cat}|{hat}  finds the word cat or hat
//   <hello       finds lines that start with the word hello
//   a{b}c        finds abc and if replacing with \0 it becomes b
//   [0-9]+cart   finds any number of digits followed by the word cart
//   \\j\+        finds literally \j+
//
//   notes:
//
//   1. > and $ do not include end of line in the match, but \n does
//   2. | precedence is not intuitive. bar|set is interpreted as ba{r|s}et
//      and thus finds the word baret or baset. use {bar}|{set} to find bar or set
//

void
RegexHelp( )
{
   cout
   << "[1]    char     matches itself, unless it is a special character\n"
   << "                (metachar):  \\ [ ] ? * + ~ $ % < > { } ( )\n"
   << "[2]    * ?      matches any (? ==> exactly one) character\n"
   << "[3]     \\       matches the character following it, except when\n"
   << "                followed by a digit 1 to 9 (see [7], [8] and [9]).\n"
   << "                It is used as an escape character for all other\n"
   << "                meta-characters, and itself.  When used in a set\n"
   << "                (e.g. [4]), it is treated as an ordinary character.\n"
   << "[4]   [set]     matches one of the characters in the set.  If the\n"
   << "                first character in the set is \"~\", it matches a\n"
   << "                character NOT in the set.  A shorthand S-E is used\n"
   << "                to specify a set of characters S upto E, inclusive.\n"
   << "                The special characters \"]\" and \"-\" have no special\n"
   << "                meaning if they appear as the first chars in the set.\n"
   << "                examples:        match:\n"
   << "                   [a-z]         any lowercase alpha\n"
   << "                   [~]-]         any char except ] and -\n"
   << "                   [~A-Z]        any char except uppercase alpha\n"
   << "                   [a-zA-Z]      any alpha\n";

   cout.flush( );
   printf( "More..." );
   _getch( );
   printf( "\b\b\b\b\b\b\b\0\0\0\0\0\0\0\b\b\b\b\b\b\b" );

   cout
   << "[5]     @       any regular expression form [1] to [4], followed by\n"
   << "                closure char @ matches zero or more matches of that\n"
   << "                form.\n"
   << "[6]     +       same as [5], except it matches one or more.\n"
   << "[7]    { }      a regular expression in the form [1] to [10], enclosed\n"
   << "                as {form} matches what form matches.  The enclosure\n"
   << "                creates a set of tags, used for [8] and for pattern\n"
   << "                substitution.  The tagged forms are numbered starting\n"
   << "                from 1.\n"
   << "[8]   \\digit    a \\ followed by a digit 1 to 9 matches whatever a\n"
   << "                previously tagged regular expression ([7]) matched.\n"
   << "[9]    ( )      a regular expression starting with a (construct\n"
   << "                and/or ending with a) construct, restricts the\n"
   << "                pattern matching to the beginning of a word, and/or\n"
   << "                the end of a word.  A word is defined to be a character\n"
   << "                string beginning and/or ending with the characters\n"
   << "                A-Z a-z 0-9 and _.  It must also be preceded and/or\n"
   << "                followed by any character excluding those mentioned.\n"
   << "[10]            a composite regular expression xy where x and y are\n"
   << "                in the form [1] to [10] matches the longest match of\n"
   << "                x followed by a match for y.\n"
   << "[11]   < >      a regular expression starting with a < or % character\n"
   << "       % $      and/or ending with a > or $ character, restricts the\n"
   << "                pattern matching to the beginning of the line, or\n"
   << "                the end of line. [anchors] Elsewhere in the pattern,\n"
   << "                <, %, > and $ are treated as ordinary characters.\n"
   << endl;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Parse a string date into its integer component MM/DD/YY and directory
// date formats.
//
/////////////////////////////////////////////////////////////////////////////
zWORD
fnEstablishDate( zPCHAR szDate,
                 zSHORT nDate[ ] )
{
   time_t t;
   struct tm *ptm = new struct tm;
   char chCurr = 0;
   zSHORT nLth = (zSHORT) strlen( szDate );
   zSHORT n, nNextComponent, k;

   // Establish default date as today.
   time( &t );                     // get time as long
   localtime_s( ptm, &t );         // convert to local time info
   nDate[ 0 ] = ptm->tm_year + 1900;
   nDate[ 1 ] = ptm->tm_mon + 1;   // adjust for class internal format
   nDate[ 2 ] = ptm->tm_mday;

   if ( szDate[ 0 ] )
   {
      for ( n = nNextComponent = k = 0; n < nLth; n++ )
      {
         if ( szDate[ n ] == '-' || szDate[ n ] == '/' || szDate[ n ] == '.' )
         {
            chCurr = szDate[ n ];
            szDate[ n ] = 0;
            nDate[ k++ ] = atoi( szDate + nNextComponent );
            nNextComponent = n + 1;
         }
         else
            chCurr = 0;
      }

      if ( chCurr == 0 )
      {
         nDate[ k ] = atoi( szDate + nNextComponent );
      }
   }

   if ( nDate[ 0 ] > 1900 )
      nDate[ 0 ] -= 1900;

   // Convert to "Dir format" date
   return( ((nDate[ 0 ] - 80) << 9) | (nDate[ 1 ] << 5) | nDate[ 2 ] );
}

/////////////////////////////////////////////////////////////////////////////
//
// Parse a string time into its integer component HH:MM:SS and directory
// time formats.
//
/////////////////////////////////////////////////////////////////////////////
zWORD
fnEstablishTime( zPCHAR szTime,
                 zSHORT nTime[ ] )
{
   time_t t;
   struct tm *ptm = 0;
   char chCurr = 0;
   zSHORT nLth = (zSHORT) strlen( szTime );
   zSHORT nNextComponent, k, n;

   // Establish default time as now.
   time( &t );                      // get time as long
   localtime_s( ptm, &t );          // convert to local time info
   nTime[ 0 ] = ptm->tm_hour + 1;   // adjust for class internal format
   nTime[ 1 ] = ptm->tm_min;
   nTime[ 2 ] = ptm->tm_sec;

   if ( szTime[ 0 ] )
   {
      nTime[ 0 ] = nTime[ 1 ] = nTime[ 2 ] = 0;
      for ( n = nNextComponent = k = 0; n < nLth; n++ )
      {
         chCurr = szTime[ n ];
         if ( chCurr == ':'  ||
              chCurr == 'a'  ||  chCurr == 'p'  ||
              chCurr == 'A'  ||  chCurr == 'P' )
         {
            szTime[ n ] = 0;
            nTime[ k++ ] = atoi( szTime + nNextComponent );
            if ( chCurr == ':' )
            {
               nNextComponent = n + 1;
            }
            else
            {
               if ( chCurr == 'p' || chCurr == 'P' )
               {
                  if ( nTime[ 0 ] < 12 )
                     nTime[ 0 ] += 12;
               }

               if ( chCurr == 'a' || chCurr == 'A' )
               {
                  if ( nTime[ 0 ] == 12 )
                     nTime[ 0 ] = 0;
               }

               //  A or P is expected to be the last pertinent info
               break;
            }
         }
         else
            chCurr = 0;
      }

      if ( chCurr == 0 )
         nTime[ k++ ] = atoi( szTime + nNextComponent );
   }

   // Convert to Dir format time
   return( (nTime[ 0 ] << 11) | (nTime[ 1 ] << 5) | (nTime[ 2 ] >> 1) );
}

/////////////////////////////////////////////////////////////////////////////
//
//  Convert from GMT 1970/01/01 00:00:00 to directory format:
//
//                                      bits   directory format
//                                     ------ ---------------------
//  GMT time is the number of     date  9-15  year relative to 1980
//  seconds since 00:00:00 GMT          5-8   month 0-12
//  on 01/01/1970 defined as            0-4   day of month (0-31)
//  typedef long time_t;          time 11-15  hours (0-23)
//                                      5-10  minutes (0-59)
//                                      0-4   2-second increments (0-29)
//
//  It also breaks the time value into its date and time components if
//  the pointers to those components are specified.
//
/////////////////////////////////////////////////////////////////////////////
zDWORD
fnSTimeToDirtime( time_t atime,
                  zWORD  *pwDate,
                  zWORD  *pwTime )
{
   struct tm t;
   zDWORD dwDirDateTime;
   zWORD wD;
   zWORD wT;

   // Convert to Dir format time
   localtime_s( &t, &atime );
   wD = (zWORD)(((t.tm_year - 80) << 9) | ((t.tm_mon + 1) << 5) | t.tm_mday);
   wT = (zWORD)((t.tm_hour << 11) | (t.tm_min << 5) | (t.tm_sec / 2));

#if 0
   cout << "qtime wD " << wD;
   cout << "qtime wT " << wT;
   dwDirDateTime = (zDWORD)(*wDate) << 16;
   dwDirDateTime += (zDWORD) *wTime;
#else
   dwDirDateTime = mMakeLong( wT, wD );
#endif

   if ( pwDate )
      *pwDate = wD;

   if ( pwTime )
      *pwTime = wT;

   return( dwDirDateTime );
}

/////////////////////////////////////////////////////////////////////////////
//
// Decode time from its directory format to its timestamp format (e.g.
// fFILENAME.EXT 1992/03/18 16:31:50)
//
//        bits   directory format             hex      binary
//       ------ ---------------------        ------  -------------------
//  date  9-15  year relative to 1980        0xFE00  1111 1110 0000 0000
//        5-8   month 0-12                   0x01E0  0000 0001 1110 0000
//        0-4   day of month (0-31)          0x001F  0000 0000 0001 1111
//  time 11-15  hours (0-23)                 0xF800  1111 1000 0000 0000
//        5-10  minutes (0-59)               0x07E0  0000 0111 1110 0000
//        0-4   2-second increments (0-29)   0x001F  0000 0000 0001 1111
//
/////////////////////////////////////////////////////////////////////////////
void
fnDirtimeToTimestamp( zDWORD dwDirDateTime,
                      zPCHAR pchTimestamp,
                      zLONG  lTimestampLth )
{
   zWORD wYear, wMonth, wDay, wHour, wMinute, wSecond;

   wYear = (zWORD) (dwDirDateTime >> 16);
   wHour = (zWORD) dwDirDateTime;

#if 0
   cout << "Date " << wYear << endl;
   cout << "Time " << wHour << endl << endl;
#endif

   wDay = wYear & 0x001F;
   wMonth = (wYear & 0x01E0) >> 5;
   wYear = 1980 + ((wYear & 0xFE00) >> 9);
   wSecond = 2 * (wHour & 0x001F);
   wMinute = (wHour & 0x07E0) >> 5;
   wHour = (wHour & 0xF800) >> 11;

#if 0
   cout << "Year   " << wYear << endl;
   cout << "Month  " << wMonth << endl;
   cout << "Day    " << wDay << endl;
   cout << "Hour   " << wHour << endl;
   cout << "Minute " << wMinute << endl;
   cout << "Second " << wSecond << endl;
#endif

   sprintf_s( pchTimestamp, lTimestampLth, "%04d/%02d/%02d %02d:%02d:%02d",
            wYear, wMonth, wDay, wHour, wMinute, wSecond );
}

zBOOL
fnWithinInterval( time_t dwDirDateTime1, time_t dwDirDateTime2,
                  zLONG  lInterval, short nTimeZoneOffset,
                  FILE   *pRptFile, zPCHAR szSrcFile )
{
   double d = difftime( dwDirDateTime1, dwDirDateTime2 );
   if ( d <= (double) lInterval && d >= (double) -lInterval )
   {
   // cout << "** Same size, in interval: " << szSrcFile << endl;
   // if ( pRptFile )
   //    fprintf( pRptFile, "*Same size, in interval* %s \n", szSrcFile );

      return( TRUE );
   }

   if ( nTimeZoneOffset )
   {
      d = d + (double) nTimeZoneOffset;
      if ( d <= (double) lInterval && d >= (double) -lInterval )
      {
      // cout << "** Same size, TimeZoneChk: " << szSrcFile << endl;
      // if ( pRptFile )
      //    fprintf( pRptFile, "*Same size, TimeZoneChk* %s \n", szSrcFile );

         return( TRUE );
      }
   }

   return( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
//  See "Implementing Quicksort Programs", Comm. ACM, October 1978,
//  and Corrigendum, Comm. ACM, June 1979.
/////////////////////////////////////////////////////////////////////////////

// number of characters or integers to swap
static long lSwapCnt;

// Subfiles of nMaxSpan or fewer elements will be sorted by a simple
// insertion sort.  Adjust nMaxSpan according to relative cost of a
// swap and a compare.  Reduce nMaxSpan (not less than 1) if a swap is
// very expensive such as when you have an array of large structures to
// be sorted, rather than an array of pointers to structures.  The
// default value is optimized for a high cost for compares.

int g_nMaxSpan;

#define SWAP( pElem1, pElem2 ) (*lpfnSwap)( (char *) (pElem1), (char *) (pElem2) )
#define CMPR( pElem1, pElem2 ) (*lpfnCmpr)( (char *) (pElem1), (char *) (pElem2) )

void
qqsort( char *pchBaseArray,             // base address of array to sort
        long lElements,                 // number of elements to sort
        long lElementBytes,             // size of element to sort
        FARPROC_ELEMCOMPARE lpfnCmpr )  // compare function
{
   char *pchStack[ 40 ],     // stack
        **sp;                // stack pointer
   char *pchLr, *pchRl;      // scan pointers
   char *pchEndArray;        // limit pointer
   long lRowLth;             // # bytes in nMaxSpan elements
   FARPROC_ELEMSWAP lpfnSwap;

   if ( lElementBytes % sizeof( int ) != 0 )
   {
      lpfnSwap = (FARPROC_ELEMSWAP) fnSwapChar;
      lSwapCnt = lElementBytes;
   }
   else
   {
      lpfnSwap = (FARPROC_ELEMSWAP) fnSwapInt;
      lSwapCnt = lElementBytes / sizeof( int );
   }

   lRowLth = g_nMaxSpan * lElementBytes; // initialize threshold

   sp = pchStack;                      // initialize stack pointer

   // pointer past end of array
   pchEndArray = pchBaseArray + lElements * lElementBytes;

   while ( TRUE )                      // repeat until done then return
   {
      // if more than nMaxSpan elements
      while ( (pchEndArray - pchBaseArray) > lRowLth )
      {
         // swap middle, pchBaseArray
         SWAP( ((long) (pchEndArray - pchBaseArray) >> 1) -
                ((((long) (pchEndArray - pchBaseArray) >> 1)) % lElementBytes) + pchBaseArray,
               pchBaseArray );

         // pchLr scans from left to right
         pchLr = pchBaseArray + lElementBytes;
         // pchRl scans from right to left
         pchRl = pchEndArray - lElementBytes;

         // Sedgewick's three-element sort sets up:
         //    *pchLr <= *pchBaseArray <= *pchRl
         // where *pchBaseArray is the pivot element
//
// printf( "pchBaseArray %s\n", *pchBaseArray );
// printf( "pLR %s\n", *pchLr );
// printf( "pchRl %s\n", *pchLr );
//
         if ( CMPR( pchLr, pchRl ) > 0 )
            SWAP( pchLr, pchRl );

         if ( CMPR( pchBaseArray, pchRl ) > 0 )
            SWAP( pchBaseArray, pchRl );

         if ( CMPR( pchLr, pchBaseArray ) > 0 )
            SWAP( pchLr, pchBaseArray );

         while ( TRUE )
         {
            do                        // move pchLr right until *pchLr >= pivot
               pchLr += lElementBytes;
            while ( CMPR( pchLr, pchBaseArray ) < 0 );

            do                        // move pchRl left until *pchRl <= pivot
               pchRl -= lElementBytes;
            while ( CMPR( pchRl, pchBaseArray ) > 0 );

            if ( pchLr > pchRl )      // break loop if pointers crossed
               break;

            SWAP( pchLr, pchRl );     // else swap elements, keep scanning
         }

         SWAP( pchBaseArray, pchRl ); // move pivot into correct place
         if ( pchRl - pchBaseArray >
              pchEndArray - pchLr )   // if left subfile is larger...
         {
            sp[ 0 ] = pchBaseArray;   // stack left subfile pchBaseArray
            sp[ 1 ] = pchRl;          //    and limit
            pchBaseArray = pchLr;     // sort the right subfile
         }
         else                         // else right subfile is larger
         {
            sp[ 0 ] = pchLr;          // stack right subfile pchBaseArray
            sp[ 1 ] = pchEndArray;    //    and limit
            pchEndArray = pchRl;      // sort the left subfile
         }

         sp += 2;                     // increment stack pointer
      }

      // Insertion sort on remaining subfile.
      pchLr = pchBaseArray + lElementBytes;
      while ( pchLr < pchEndArray )
      {
         pchRl = pchLr;
         while ( pchRl > pchBaseArray  &&
                 CMPR( pchRl - lElementBytes, pchRl ) > 0 )
         {
            SWAP( pchRl - lElementBytes, pchRl );
            pchRl -= lElementBytes;
         }

         pchLr += lElementBytes;
      }

      if ( sp > pchStack )   // if any entries on stack...
      {
         sp -= 2;         // pop the pchBaseArray and limit
         pchBaseArray = sp[ 0 ];
         pchEndArray = sp[ 1 ];
      }
      else                // else stack empty, all done
         break;           // return.
   }
}

void
fnSwapChar( char *pch1,       // swap characters
            char *pch2 )
{
  char cTemp;
  int  k;

  for ( k = 0;  k < lSwapCnt;  k++, pch1++, pch2++ )
  {
    cTemp = *pch1;
    *pch1 = *pch2;
    *pch2 = cTemp;
  }
}

void
fnSwapInt( int *pInt1,          // swap integers
           int *pInt2 )
{
  int  nTemp;
  int  k;

  for ( k = 0;  k < lSwapCnt;  k++, pInt1++, pInt2++ )
  {
    nTemp = *pInt1;
    *pInt1 = *pInt2;
    *pInt2 = nTemp;
  }
}



#if 0
static
void
fnSwapInt( int *pInt1,         // swap integers
           int *pInt2 )
{
   int nTemp;
   unsigned int k;

   k = nSwapCnt;
   while ( k-- )
   {
      nTemp = *pInt1;
      *pInt1 = *pInt2;
      *pInt2 = nTemp;

      pInt1++;
      pInt2++;
   }
}

static
void
fnSwapch( char *pch1,        // swap characters
            char *pch2 )
{
   char cTemp;
   unsigned int k;

   k = nSwapCnt;
   while ( k-- )
   {
      cTemp = *pch1;
      *pch1 = *pch2;
      *pch2 = cTemp;

      pch1++;
      pch2++;
   }
}
#endif
