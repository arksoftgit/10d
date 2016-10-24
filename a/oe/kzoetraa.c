//
// MODULE NAME:  KZOETRAA  -  Object services Tracing Operations
// DESCRIPTION:  This is the source file which contains Object services
//               trace operations.
// OPERATIONS:   All OPERATIONS which do debugging and tracing
// **********************************************************************
// * Copyright (c) 1993-2016 QuinSoft, Inc. All rights reserved. *
// * Confidential and Proprietary material subject to license -         *
// * do not reproduce or disclose. This material is an unpublished      *
// * work and is considered a trade secret belonging to the             *
// * copyright holder.                                                  *
// **********************************************************************
//  AUTHOR:  Gig Kirk
//  DATE:    3/31/92
//  API:     NONE
//  ENVIRONMENT: ANY
//

/*
CHANGE LOG most recent first order

2003.10.25  DKS
   DisplayObjectInstance now calls ResetViewPositions so it doesn't reset
   select states and then DisplayEntityInstance displays SelectSet info.

2001.11.27  DGC  10b
   Somebody removed some code in DisplayObjectInstance( ), probably erroneously.
   Since there was no change log, I'm putting the code back in.

2001.05.14  DGC  10b
   Fixed crash in DisplayObjectInstance( ) reported by Doug.

2001.04.18  DGC  10b
   Added code for DropViewObject( ) logic.

2001.04.06   DGC
   Added trace of entity key.

200102.12   BL   F51015
   Object Browser, if lpViewOD = NULL do not write Object Definition

2000.10.03  DGC
   Changed signature of fnCompareEIAttrs( ).

2000.09.29  DGC
   fnDisplayEntityInstance( ) now displays incremental flags.

1999.12.13  DKS
   Added CompareEntitiesIgnoringAttrs if that's OK with DG.

1999.11.29  DGC
   Added code to fnAllocDataspace( ) to help find leaks.

----------
1999.10.27  HH  ALL
   merged from 9J: to improve performance of sorting decimals,
   fnCompareEIAttrs is called with a new parameter, LPTASK.

1999.06.03  DGC  10a
   Added GetTracingFlags( ).

1999.04.07  DGC  10a
   Changed tracing.  Returned the use of lpTask in TraceLineS( ).

*/

#include "kzoephdr.h"
#include <stdio.h>
#include <stdarg.h>

#if defined( _WINDOWS ) && defined( DEBUG )
#pragma optimize( "", off )
#endif

// From kzoeoiaa.c
zSHORT LOCALOPER
fnCompareEIAttrs( LPTASK            lpCurrentTask,
                  zVIEW             lpView1,
                  LPENTITYINSTANCE  lpInstance1,
                  LPVIEWATTRIB      lpViewAttrib1,
                  zPCHAR            pchContext1,
                  zVIEW             lpView2,
                  LPENTITYINSTANCE  lpInstance2,
                  LPVIEWATTRIB      lpViewAttrib2,
                  zPCHAR            pchContext2 );

#define zMAX_MSG_LTH 255

//./ ADD NAME=OperationCount
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      OperationCount
//
//  PURPOSE:    To count operations calls for performance tuning
//
//  PARAMETERS:  0,  display current count
//               1,  Start counting,
//               11, Start counting and disable task tracing
//               2,  Stop  counting
//               3,  Clear counts
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void OPERATION
OperationCount( zVIEW vTaskView, zSHORT nOpt )
{
   LPTASK   lpTask;
   zCHAR    szMessage[ 256 ];
   zPLONG   lplCount1;
   zPLONG   lplCount2;
   zLONG    lExternal, lInternal, lTime;
   zSHORT   nIdx;

   lpTask = zGETPTR( vTaskView->hTask );
   if ( lpTask == 0 )
      return;

   switch ( nOpt )
   {
      case 0:   // Display existing counts
         lExternal = 0;
         lInternal = 0;
         lpTask->bTrace = TRUE;
         TraceLineS( "Operation Counts:", "" );
         if ( lpTask->hCountBuf )
         {
            lplCount1 = (zPLONG) zGETPTR( lpTask->hCountBuf );
            lplCount2 = lplCount1 + 1;
            SysGetDateTime( szMessage, zsizeof( szMessage ) );
            szMessage[ 16 ] = 0;
            *lplCount2 = zatol( szMessage + 8 ) + 100000000;
            lTime = *lplCount2 - *lplCount1;
            strcpy_s( szMessage, zsizeof( szMessage ), " " );
            for ( nIdx = 1 ; nIdx < 450 ; nIdx++ )
            {
               lplCount1 += 2;
               lplCount2 = lplCount1 + 1;
               if ( *lplCount1 || *lplCount2 )
               {
                  lExternal += *lplCount1;
                  lInternal += *lplCount2;
                  szMessage[ 3 ] = 0;
                  SysGetOperationMessage( szMessage + 3, nIdx, 40 );
                  if ( szMessage[ 3 ] == 0 )
                  {
                     szMessage[ 3 ] = '(';
                     zltoa( nIdx, szMessage + 4, zsizeof( szMessage ) - 4 );
                     strcat_s( szMessage, zsizeof( szMessage ), ")" );
                  }

                  strcat_s( szMessage, zsizeof( szMessage ), ", External calls (" );
                  zltoa( *lplCount1, szMessage + 200, zsizeof( szMessage ) - 200 );
                  strcat_s( szMessage, zsizeof( szMessage ), szMessage + 200 );
                  strcat_s( szMessage, zsizeof( szMessage ), "), Internal calls (" );
                  zltoa( *lplCount2, szMessage + 200, zsizeof( szMessage ) - 200 );
                  strcat_s( szMessage, zsizeof( szMessage ), szMessage + 200 );
                  strcat_s( szMessage, zsizeof( szMessage ), ")" );
                  TraceLineS( szMessage, "" );
               }
            }

            TraceLineI( "   Total external calls: ", lExternal );
            TraceLineI( "   Total internal calls: ", lInternal );
            lplCount1 = (zPLONG) zGETPTR( lpTask->hCountBuf );
            lplCount2 = lplCount1 + 1;
            zltoa( *lplCount1, szMessage + 199, zsizeof( szMessage ) - 199 );
            strncpy_s( szMessage, zsizeof( szMessage ), szMessage + 200, 2 );
            strcpy_s( szMessage + 2, zsizeof( szMessage ) - 2, ":" );
            strncpy_s( szMessage + 3, zsizeof( szMessage ) - 3, szMessage + 202, 2 );
            strcpy_s( szMessage + 5, zsizeof( szMessage ) - 5, ":" );
            strncpy_s( szMessage + 6, zsizeof( szMessage ) - 6, szMessage + 204, 2 );
            strcpy_s( szMessage + 8, zsizeof( szMessage ) - 9, "." );
            strcpy_s( szMessage + 9, zsizeof( szMessage ) - 9, szMessage + 206 );
            TraceLineS( "   Start time: ", szMessage );
            zltoa( *lplCount2, szMessage + 199, zsizeof( szMessage ) - 199 );
            strncpy_s( szMessage, zsizeof( szMessage ), szMessage + 200, 2 );
            strcpy_s( szMessage + 2, zsizeof( szMessage ) - 2, ":" );
            strncpy_s( szMessage + 3, zsizeof( szMessage ) - 3, szMessage + 202, 2 );
            strcpy_s( szMessage + 5, zsizeof( szMessage ) - 5, ":" );
            strncpy_s( szMessage + 6, zsizeof( szMessage ) - 6, szMessage + 204, 2 );
            strcpy_s( szMessage + 8, zsizeof( szMessage ) - 8, "." );
            strcpy_s( szMessage + 9, zsizeof( szMessage ) - 9, szMessage + 206 );
            TraceLineS( "   Stop  time: ", szMessage );
         }
         else
            TraceLineS( "   ERROR counting not active", "!!!" );

         break;

      case 1:    // Start counting
      case 11:   // Start counting, disable trace
         lpTask->bCount = TRUE;
         if ( nOpt == 11 )
            lpTask->bTrace = FALSE;

         if ( lpTask->hCountBuf == 0 )
         {
            lpTask->hCountBuf = (zPCHAR) fnAllocDataspace( lpTask->hFirstDataHeader,
                                                           4000, 1, 0, iCountBuf );
         }

         if ( lpTask->hCountBuf )
         {
            lplCount1 = (zPLONG) zGETPTR( lpTask->hCountBuf );
            SysGetDateTime( szMessage, zsizeof( szMessage ) );
            szMessage[ 16 ] = 0;
            *lplCount1 = zatol( szMessage + 8 ) + 100000000;
         }

         break;

      case 2:   // Stop  counting
         lpTask->bCount = FALSE;
         break;

      case 3:   // Clear count buffer
         if ( lpTask->hCountBuf )
         {
            lplCount1 = (zPLONG) zGETPTR( lpTask->hCountBuf );
            for ( nIdx = 0 ; nIdx < 450 ; nIdx++ )
            {
               *lplCount1 = 0;
               lplCount1++;
               *lplCount1 = 0;
               lplCount1++;
            }
         }

         break;
   }

   return;
}

//./ ADD NAME=TraceLineI
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      TraceLineI
//
//  PURPOSE:    To trace an integer (zLONG) to the trace window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void OPERATION
TraceLineI( zCPCHAR Title, zLONG lValue )
{
   zCHAR szLong[ 32 ];

   zltoa( lValue, szLong, zsizeof( szLong ) );
   TraceLineS( Title, szLong );
}

//./ ADD NAME=TraceLineX
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      TraceLineX
//
//  PURPOSE:    To trace a hex integer (zLONG) to the trace window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void OPERATION
TraceLineX( zCPCHAR Title, zULONG lValue )
{
   zCHAR szHex[ 16 ];

   szHex[ 0 ] = '0';
   szHex[ 1 ] = 'x';
   zltox( lValue, szHex + 2, zsizeof( szHex ) - 2 );
   TraceLineS( Title, szHex );
}

//./ ADD NAME=TraceLineS
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      TraceLineS
//
//  PURPOSE:    To trace a string to the trace window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void OPERATION
TraceLineS( zCPCHAR Title, zCPCHAR String )
{
   zCHAR szMessage[ zMAX_MSG_LTH + 1 ];

   if ( g_hAnchorBlock == 0 )
      return;

   if ( Title )
   {
      int  nTitleLth = zstrlen( Title );
      int  nStringLth;

      if ( String )
         nStringLth = zstrlen( String );
      else
         nStringLth = 6;   // for "(null)"

      // The common case is that everything fits nicely ... so take care of it right away.
      if ( nTitleLth + nStringLth < zMAX_MSG_LTH )
      {
         strcpy_s( szMessage, zsizeof( szMessage ), Title );
         if ( String )
            strcpy_s( szMessage + nTitleLth, zsizeof( szMessage ) - nTitleLth, String );
         else
            strcpy_s( szMessage + nTitleLth, zsizeof( szMessage ) - nTitleLth, "(null)" );
      }
      else
      {
         // If we get to this code, our message exceeds the amount of
         // memory allocated for szMessage ... so we try to nicely break
         // up the message.

         int    nLth = 0;           // amount sent so far
         int    nMsgOffset = 0;     // amount of szMessage currently loaded
         zPCHAR pch;
         int    nVacant;

         while ( nLth < nTitleLth )
         {
            nVacant = zMAX_MSG_LTH - nMsgOffset;
            if ( nVacant > nTitleLth - nLth )  // fit rest of title?
            {
               strcpy_s( szMessage + nMsgOffset, zsizeof( szMessage ) - nMsgOffset, Title + nLth );
               nVacant -= (nTitleLth - nLth);
               nMsgOffset += nTitleLth - nLth;
               nLth = nTitleLth;
            }
            else
            {
               // fit as much of title as possible into szMessage using
               // commas and spaces to break the message if possible
               strncpy_s( szMessage + nMsgOffset, zsizeof( szMessage ) - nMsgOffset, Title + nLth, nVacant );
               szMessage[ zMAX_MSG_LTH ] = 0;

               pch = zstrrchr( szMessage, ',' );
               if ( pch > szMessage + 5 )
               {
                  pch++;
                  *pch = 0;
                  nLth += (pch - (zPCHAR) szMessage) - nMsgOffset;
               }
               else
               {
                  pch = zstrrchr( szMessage, ' ' );
                  if ( pch > szMessage + 5 )
                  {
                     pch++;
                     *pch = 0;
                     nLth += (pch - (zPCHAR) szMessage) - nMsgOffset;
                  }
                  else
                     nLth += nVacant;
               }

               SysMessageList( szMessage );
               strcpy_s( szMessage, zsizeof( szMessage ), " + " );
               nMsgOffset = 5;
            }
         }

         nLth = 0;
         while ( nLth < nStringLth )
         {
            nVacant = zMAX_MSG_LTH - nMsgOffset;
            if ( nVacant > nStringLth - nLth )  // fit rest of string?
            {
               strcpy_s( szMessage + nMsgOffset, zsizeof( szMessage ) - nMsgOffset, String + nLth );
               nVacant -= (nStringLth - nLth);
               nMsgOffset += nStringLth - nLth;
               nLth = nStringLth;
            }
            else
            {
               // fit as much of title as possible into szMessage using
               // commas and spaces to break the message if possible
               strncpy_s( szMessage + nMsgOffset, zsizeof( szMessage ) - nMsgOffset, String + nLth, nVacant );
               szMessage[ zMAX_MSG_LTH ] = 0;

               pch = zstrrchr( szMessage, ',' );
               if ( pch > szMessage + 5 )
               {
                  pch++;
                  *pch = 0;
                  nLth += (pch - (zPCHAR) szMessage) - nMsgOffset;
               }
               else
               {
                  pch = zstrrchr( szMessage, ' ' );
                  if ( pch > szMessage + 5 )
                  {
                     pch++;
                     *pch = 0;
                     nLth += (pch - (zPCHAR) szMessage) - nMsgOffset;
                  }
                  else
                     nLth += nVacant;
               }

               SysMessageList( szMessage );
               strcpy_s( szMessage, zsizeof( szMessage ), " + " );
               nMsgOffset = 5;
            }
         }
      }
   }
   else
   {
      strcpy_s( szMessage, zsizeof( szMessage ), "(oetr) Invalid \"null\" TraceLine title" );
   }

   SysMessageList( szMessage );
}

#ifndef _countof
#define _countof(array) (zsizeof(array)/zsizeof(array[ 0 ]))
#endif

//./ ADD NAME=TraceLine
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      TraceLine
//
//  PURPOSE:    To trace variable trace information to the trace window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void VARYOPER
TraceLine( zCPCHAR cpcFormat, ... )
{
   short   nBufCnt;
   zCHAR   szBuffer[ 65534 ];
   va_list args;

   va_start( args, cpcFormat );

   nBufCnt = _vsnprintf_s( szBuffer, zsizeof( szBuffer ), _countof( szBuffer ), cpcFormat, args );

   // was there an error? was the expanded string too long?
   if ( nBufCnt >= 0 )
      TraceLineS( szBuffer, "" );
   else
      TraceLineS( "Error formatting message: ", cpcFormat );

   va_end( args );
}

//./ ADD NAME=TraceBuffer
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      TraceBuffer
//
//  PURPOSE:    To trace a buffer to the trace window
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void OPERATION
TraceBuffer( zCPCHAR cpcPrefix, zPVOID pvBuffer, zULONG ulLth )
{
   zCPCHAR cpcBuffer = (zCPCHAR) pvBuffer;
   zCHAR   szHex[ 256 ];
   zCHAR   szAscii[ 256 ];
   zCHAR   sz[ 256 ];
   zULONG  ulPos;
   zULONG  n;
   zULONG  ulBlankLines;
   zULONG  ulLongestStr = 0;

   // szHex is a buffer containing the prefix and the hex representation of
   // 16 bytes from the buffer.  szAscii is a buffer containing the ASCII
   // representation of those same 16 bytes.

   szHex[ 0 ]   = 0;
   szAscii[ 0 ] = 0;

   // Loop through each byte in the buffer and display a block of 16 bytes
   // on each line in the trace window.
   for ( ulPos = 0; ulPos < ulLth; ulPos++ )
   {
      // If the index is a multiple of 16, then trace the szHex and szAscii
      // buffers (if they aren't empty) and reset them.
      if ( ulPos % 16 == 0 )
      {
         if ( szHex[ 0 ] )
         {
            TraceLineS( szHex, szAscii );

            // Keep track of the longest hex string.
            if ( ulLongestStr < zstrlen( szHex ) )
               ulLongestStr = zstrlen( szHex );
         }

         // Check for long string of same characters.
         for ( n = ulPos; n < ulLth; n++ )
         {
            if ( n > 0 && cpcBuffer[ n ] != cpcBuffer[ n - 1 ] )
               break;
         }

         ulBlankLines = (n - ulPos) / 16;
         if ( ulBlankLines > 2 )
         {
            n = ulBlankLines * 16;
            sprintf_s( szHex, zsizeof( szHex ), "%s %d Repeat Lines (%4d thru %4d) ",
                       cpcPrefix, ulBlankLines, ulPos, ulPos + n - 1 );
            TraceLineS( szHex, "" );
            ulPos += n;
         }

         // Add the offset counter to cpcPrefix.
         sprintf_s( szHex, zsizeof( szHex ), "%s(%4d) ", cpcPrefix, ulPos );
         strcpy_s( szAscii, zsizeof( szAscii ), " " );
      }
      else
      if ( ulPos % 8 == 0 )
      {
         // The index is a multiple of 8, so add a few spaces to the buffers
         // to make the trace a little easier to read.
         strcat_s( szHex, zsizeof( szHex ), " " );
      // strcat_s( szAscii, zsizeof( szAscii ), " " );
      }

      // Convert the current byte to a 2-char hex number.
      zltox( (zLONG) cpcBuffer[ ulPos ], sz, zsizeof( sz ) );
      n = zstrlen( sz );
      if ( n < 2 )
      {
         strcat_s( szHex, zsizeof( szHex ), "0" );
         n = 0;
      }
      else
         n -= 2;

      // Add the hex number to szHex.
      strcat_s( szHex, zsizeof( szHex ), sz + n );
      strcat_s( szHex, zsizeof( szHex ), " " );

      // If the current byte is a printable char, then copy it to the ASCII
      // buffer.  Otherwise add a "." to the buffer.
      if ( cpcBuffer[ ulPos ] >= 32 && cpcBuffer[ ulPos ] <= 126 )
      {
         n = zstrlen( szAscii );
         szAscii[ n++ ] = cpcBuffer[ ulPos ];
         szAscii[ n ]   = 0;
      }
      else
         strcat_s( szAscii, zsizeof( szAscii ), "." );

   } // for...

   // If szHex is not empty, then the buffers contain information that needs
   // to be traced.
   if ( szHex[ 0 ] )
   {
      // Pad the current szHex string with spaces so that it matches (in lth)
      // the longest szHex string that was traced.
      ulPos = zstrlen( szHex );
      while ( ulPos < ulLongestStr )
         szHex[ ulPos++ ] = ' ';

      szHex[ ulPos ] = 0;

      TraceLineS( szHex, szAscii );
   }

} // TraceBuffer

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void
SetHexBuffer( zPCHAR        pchBuffer,
              zSHORT        nOffset,
              unsigned char ch )
{
   unsigned char chHex;

// pchBuffer[ nOffset + 49 ] = (isprint( ch ) || ch != 0xA1) ? '.' : ch;
   pchBuffer[ nOffset + 49 ] =
         (ch == 0xA1 || ch == '\n' || ch == 0xFF ||
          ch == '\r' || ch == 0) ? '.' : ch;
   chHex = ch % 16;
   pchBuffer[ nOffset * 3 + 1 ] = (chHex > 9) ? 'A' + chHex - 10 : '0' + chHex;
   chHex = ch / 16;
   pchBuffer[ nOffset * 3 ] = (chHex > 9) ? 'A' + chHex - 10 : '0' + chHex;
// pchBuffer[ nOffset * 3 + 2 ] = (nOffset == 7) ? '-' : ' ';
}

void
FormatInteger( zPCHAR        pchBuffer,
               zLONG         lValue,
               zSHORT        nDigits,
               unsigned char chFill )
{
   while ( nDigits )
   {
      nDigits--;
      if ( lValue )
      {
         pchBuffer[ nDigits ] = '0' + lValue % 10;
      }
      else
      {
         pchBuffer[ nDigits ] = chFill;
      }

      lValue /= 10;
   }
}

zCHAR szBlankLine[ 81 ] = "                                        "
                          "                                        ";

void OPERATION
TraceHex( zPVOID  pvBlob,
          zLONG   lBlobLth )
{
   zCHAR  szBuffer[ 256 ];
   zPCHAR pch = (zPCHAR) pvBlob;
   zPCHAR pchEnd = pch + lBlobLth;
   unsigned char ch;
   zSHORT k;
   zSHORT j;

   k = 1;
   strcpy_s( szBuffer, zsizeof( szBuffer ), szBlankLine );
   szBuffer[ 34 ] = '-';
   szBuffer[ 59 ] = szBuffer[ 76 ] = (zCHAR) 0xB3;
   szBuffer[ 77 ] = 0;
   while ( pch < pchEnd )
   {
      FormatInteger( szBuffer, (k - 1) * 16, 9, '0' );

      for ( j = 0; j < 16; j++, pch++ )
      {
         if ( pch < pchEnd )
            ch = *pch;
         else
            ch = 0;

         SetHexBuffer( szBuffer + 11, j, ch );
      }

      TraceLineS( szBuffer, "" );
      k++;
   }
}

void OPERATION
TraceBlob( zCPCHAR cpcMessage,
           zPVOID  pvBlob,
           zLONG   lBlobLth )
{

   TraceLineI( cpcMessage, lBlobLth );
   TraceHex( pvBlob, lBlobLth );
}

/////////////////////////////////////////////////////////////////////////////

//./ ADD NAME=DisplayEntityInstance
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DisplayEntityInstance
//
//  PURPOSE:    To display an entity instance
//
//  RETURNS:    0           - Entity Displayed
//              zCALL_ERROR - Error on call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT  OPERATION
DisplayEntityInstance( zVIEW lpView, zCPCHAR cpcEntityName )
{
   LPTASK            lpCurrentTask;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPENTITYINSTANCE  lpEntityInstance;
   zPCHAR            pchWorkEntityName;
   int               nRC;

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iDisplayEntityInstance, lpView,
                                          zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   pchWorkEntityName = (zPCHAR) cpcEntityName;

   if ( pchWorkEntityName == 0 || pchWorkEntityName[ 0 ] == 0 )
   {
      LPVIEWCSR       lpViewCsr = zGETPTR( lpView->hViewCsr );
      LPVIEWENTITYCSR lpRootViewEntityCsr =
                                  zGETPTR( lpViewCsr->hRootViewEntityCsr );
      LPVIEWENTITY    lpViewEntity =
                                  zGETPTR( lpRootViewEntityCsr->hViewEntity );

      pchWorkEntityName = lpViewEntity->szName;
   }

   // Validate that the entity exists
   if ( (lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, lpView,
                                           pchWorkEntityName, 0 )) == 0 )
   {
      fnOperationReturn( iDisplayEntityInstance, lpCurrentTask );
      return( zCALL_ERROR );
   }

   TraceLineS( "", "" );
   TraceLine( "Entity Instance Display: %s  for view: 0x%08x",
               cpcEntityName, lpView );
   if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR )
      fnEstablishCursorForView( lpViewEntityCsr );

   lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
   if ( lpEntityInstance == 0 || lpEntityInstance->u.nInd.bHidden )
   {
      TraceLineS( "    Cursor is NULL or Undefined for ",
                  lpViewEntity->szName );
      fnOperationReturn( iDisplayEntityInstance, lpCurrentTask );
      return( 0 );
   }

   nRC = fnDisplayEntityInstance( lpView, lpViewEntityCsr, 0, 0 );

   fnOperationReturn( iDisplayEntityInstance, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=DisplayEntityInstancePath
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DisplayEntityInstancePath
//
//  PURPOSE:    To display the path to an entity instance starting at
//              the root of the object instance.
//
//  RETURNS:    0           - Path Displayed
//              zCALL_ERROR - Error on call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT  OPERATION
DisplayEntityInstancePath( zVIEW  lpView, zCPCHAR cpcEntityName )
{
   LPTASK            lpCurrentTask;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPENTITYINSTANCE  lpEntityInstance;
   LPENTITYINSTANCE  lpCurrentInstance;
   zPCHAR            pchWorkEntityName;
   int               nRC, nLevel;

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iDisplayEntityInstancePath,
                                          lpView, zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   pchWorkEntityName = (zPCHAR) cpcEntityName;

   if ( pchWorkEntityName == 0 || pchWorkEntityName[ 0 ] == 0 )
   {
      LPVIEWCSR       lpViewCsr = zGETPTR( lpView->hViewCsr );
      LPVIEWENTITYCSR lpRootViewEntityCsr =
                                  zGETPTR( lpViewCsr->hRootViewEntityCsr );
      LPVIEWENTITY    lpViewEntity =
                                  zGETPTR( lpRootViewEntityCsr->hViewEntity );

      pchWorkEntityName = lpViewEntity->szName;
   }

   // Validate that the entity exists
   if ( (lpViewEntity = fnValidViewEntity( &lpViewEntityCsr,
                                           lpView, pchWorkEntityName, 0 )) == 0 )
   {
      fnOperationReturn( iDisplayEntityInstancePath, lpCurrentTask );
      return( zCALL_ERROR );
   }

   TraceLineS( "", "" );
   if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR )
      fnEstablishCursorForView( lpViewEntityCsr );

   lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
   if ( lpEntityInstance == 0 || lpEntityInstance->u.nInd.bHidden )
   {
      TraceLineS( "    Cursor is NULL or Undefined for ",
                  lpViewEntity->szName );
      fnOperationReturn( iDisplayEntityInstancePath, lpCurrentTask );
      return( 0 );
   }

   TraceLineS( "---- Begin Entity Instance Path Display ", "----" );
   lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
   nLevel = 1;
   CreateViewFromViewForTask( &lpView, lpView, 0 );
   do
   {
      lpCurrentInstance = lpEntityInstance;
      while ( lpCurrentInstance->hParent &&
              lpCurrentInstance->nLevel > nLevel )
      {
         lpCurrentInstance = zGETPTR( lpCurrentInstance->hParent );
      }

      nLevel = lpCurrentInstance->nLevel;
      lpViewEntityCsr = fnEstablishViewForInstance( lpView, 0,
                                                    lpCurrentInstance );
      nRC = fnDisplayEntityInstance( lpView, lpViewEntityCsr, 0, 0 );
      nLevel++;
   }  while ( nLevel <= lpEntityInstance->nLevel );

   TraceLineS( "---- End   Entity Instance Path Display ", "----" );
   DropView( lpView );

   fnOperationReturn( iDisplayEntityInstancePath, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=DisplayObjectInstance
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DisplayObjectInstance
//
//  PURPOSE:    To display an object instance
//
//  RETURNS:    0           - Object Displayed
//              zCALL_ERROR - Error on call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT  OPERATION
DisplayObjectInstance( zVIEW lpView, zCPCHAR cpcScopeEntity,
                       zCPCHAR cpcEntityName )
{
   LPTASK            lpCurrentTask;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPVIEWENTITYCSR   lpViewEntityCsrPosition;
   LPENTITYINSTANCE  lpStartInstance;
   LPENTITYINSTANCE  lpEntityInstance;
   zVIEW             lpNewView;
   LPVIEWOD          lpViewOD;
   zSHORT            nStartLevel;
   zSHORT            nRC;

   // If task not active or disabled, or view invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iDisplayObjectInstance,
                                          lpView, zVALID_VIEW )) == 0 )
   {
      return( zCALL_ERROR );
   }

   nRC = fnDeclareView( &lpNewView, lpCurrentTask, lpView, 0, 0 );
   if ( nRC < 0 )
   {
      fnOperationReturn( iDisplayObjectInstance, lpCurrentTask );
      return( nRC );
   }

   nRC = SetViewFromView( lpNewView, lpView );
   if ( nRC < 0 )
   {
      DropView( lpNewView );
      fnOperationReturn( iDisplayObjectInstance, lpCurrentTask );
      return( nRC );
   }

   // Validate that the (childmost) entity to be displayed exists.
   if ( cpcEntityName && cpcEntityName[ 0 ] )
   {
      if ( (lpViewEntity = fnValidViewEntity( &lpViewEntityCsr,
                                              lpNewView,
                                              cpcEntityName, 0 )) == 0 )
      {
         cpcEntityName = 0;  // invalid entity passed in ... ignore
      }
   }
   else
      cpcEntityName = 0;

   // Validate that the scope entity exists.
   if ( cpcScopeEntity && cpcScopeEntity[ 0 ] )
   {
      if ( (lpViewEntity = fnValidViewEntity( &lpViewEntityCsr,
                                              lpNewView,
                                              cpcScopeEntity, 0 )) == 0 )
      {
         DropView( lpNewView );
         fnOperationReturn( iDisplayObjectInstance, lpCurrentTask );
         return( zCALL_ERROR );
      }

      // If the cursor is not set, try resetting it.
      if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR ||
           lpViewEntityCsr->hEntityInstance == NULL_CSR )
      {
         fnResetCursorForViewChildren( lpViewEntityCsr );

         // If it's STILL not set then there are no child entities so get out.
         if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR ||
              lpViewEntityCsr->hEntityInstance == NULL_CSR )
         {
            TraceLineS( "", "" );
            TraceLineS( "Object Instance is NULL for entity ", cpcScopeEntity );
            DropView( lpNewView );
            fnOperationReturn( iDisplayObjectInstance, lpCurrentTask );
            return( 0 );
         }
      }

      lpStartInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
      nStartLevel = lpViewEntity->nLevel;
   }
   else
   {
      LPVIEWCSR lpViewCsr;
      LPVIEWOI  lpViewOI;

   // ResetView( lpNewView );
      ResetViewPositions( lpNewView );  // don't reset select states!
      lpViewCsr = zGETPTR( lpNewView->hViewCsr );
      lpViewEntityCsr = zGETPTR( lpViewCsr->hRootViewEntityCsr );
      nStartLevel = 0;
      lpViewOI = zGETPTR( lpViewCsr->hViewOI );
      lpStartInstance = zGETPTR( lpViewOI->hRootEntityInstance );
   }

   lpViewOD = zGETPTR( lpView->hViewOD );
   TraceLineS( "", "" );
   TraceLine( "Object Instance Display for View Id: 0x%08x  Def: %s",
              lpView, lpViewOD->szName );

   for ( lpEntityInstance = lpStartInstance;
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
   {
      lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
      if ( lpViewEntity->nLevel <= nStartLevel &&
           lpEntityInstance != lpStartInstance )
      {
         break;
      }

      if ( lpEntityInstance->u.nInd.bHidden ||
           (cpcEntityName && zstrcmp( cpcEntityName,
                                      lpViewEntity->szName ) != 0) )
      {
         continue;
      }

      lpViewEntityCsr = fnEstablishViewForInstance( lpNewView, 0,
                                                    lpEntityInstance );

      // Find entity at current position.
      if ( fnValidViewEntity( &lpViewEntityCsrPosition, lpView,
                              lpViewEntity->szName, 1 ) != 0 )
      {
         fnDisplayEntityInstance( lpNewView, lpViewEntityCsr,
                                  (zSHORT) (lpViewEntityCsr->nLevel - nStartLevel),
                                  lpViewEntityCsrPosition );
      }
   }

   DropView( lpNewView );

   fnOperationReturn( iDisplayObjectInstance, lpCurrentTask );
   return( 0 );
}

//./ ADD NAME=fnDisplayEntityInstance
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:  fnDisplayEntityInstance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT
fnDisplayEntityInstance( zVIEW            lpView,
                         LPVIEWENTITYCSR  lpViewEntityCsr,
                         zSHORT           nSpaces,
                         LPVIEWENTITYCSR  lpViewEntityCsrPosition )
{
   LPVIEWENTITY  lpViewEntity;
   LPVIEWATTRIB  lpViewAttrib;
   zCHAR         szSpaces[ 30 ];
   zCHAR         szTraceAll[ 2 ];
   zCHAR         szWorkString[ 32000 ];
   LPVIEWCSR          lpViewCsr;
   LPSELECTEDINSTANCE lpSelectedInstance;
   int           k;

   SysReadZeidonIni( -1, "[Debug]", "TraceAllAttributes", szTraceAll, zsizeof( szTraceAll ) );

   strcpy_s( szSpaces, zsizeof( szSpaces ), "                           " );
   if ( nSpaces > 20 )
      nSpaces = 20;

   szSpaces[ nSpaces ] = 0;

   lpViewEntity = zGETPTR( lpViewEntityCsr->hViewEntity );
   TraceLine( "%s|==>%s%s", szSpaces, lpViewEntity->szName,
              (lpViewEntityCsr && lpViewEntityCsrPosition &&
               lpViewEntityCsr->hEntityInstance ==
                  lpViewEntityCsrPosition->hEntityInstance) ? " *" : "" );

   lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
   strcpy_s( szWorkString, zsizeof( szWorkString ), "  " );
   if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR )
   {
      TraceLineS( "   Cursor for EntityInstance is ", "UNSET" );
   }
   else
   if ( lpViewEntityCsr->hEntityInstance == NULL_CSR )
   {
      TraceLineS( "   Cursor for EntityInstance is ", "NULL" );
   }
   else
   {
      zCHAR            szFlags[ 50 ] = "Incremental Update Flags: ";
      LPENTITYINSTANCE lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );

      if ( lpEntityInstance->u.nInd.bHidden      ||
           lpEntityInstance->u.nInd.bTemporal    ||
           lpEntityInstance->hPrevVsn            ||
           lpEntityInstance->u.nInd.bPrevVersion ||
           lpEntityInstance->u.nInd.bPrevVsnRoot )
      {
         TraceLineS( ">>>EntityInstance flags:", " Start" );
         if ( lpEntityInstance->u.nInd.bHidden )
            TraceLineS( ">>>EntityInstance is hidden", "" );
         if ( lpEntityInstance->u.nInd.bTemporal )
            TraceLineS( ">>>EntityInstance is temporal", "" );
         if ( lpEntityInstance->hPrevVsn )
            TraceLineS( ">>>EntityInstance has a previous version", "" );
         if ( lpEntityInstance->u.nInd.bPrevVersion )
            TraceLineS( ">>>EntityInstance is a previous version", "" );
         if ( lpEntityInstance->u.nInd.bPrevVsnRoot )
            TraceLineS( ">>>EntityInstance is a previous version root", "" );

         TraceLineS( ">>>EntityInstance flags:", " End" );
      }

      if ( lpEntityInstance->u.nInd.bCreated )
         strcat_s( szFlags, zsizeof( szFlags ), "C" );

      if ( lpEntityInstance->u.nInd.bIncluded )
         strcat_s( szFlags, zsizeof( szFlags ), "I" );

      if ( lpEntityInstance->u.nInd.bDeleted )
         strcat_s( szFlags, zsizeof( szFlags ), "D" );

      if ( lpEntityInstance->u.nInd.bExcluded )
         strcat_s( szFlags, zsizeof( szFlags ), "X" );

      if ( lpEntityInstance->u.nInd.bExcluded )
         strcat_s( szFlags, zsizeof( szFlags ), "U" );

      TraceLineS( szSpaces, szFlags );

      if ( lpEntityInstance->lTag )
         TraceLineX( ">>>EntityInstance Tag:", lpEntityInstance->lTag );

      lpViewCsr = zGETPTR( lpView->hViewCsr );
      lpSelectedInstance = zGETPTR( lpViewCsr->hFirstSelectedInstance );

      while ( lpSelectedInstance &&
                 ((LPENTITYINSTANCE)
                   zGETPTR( lpSelectedInstance->xEntityInstance ) !=
                                                         lpEntityInstance ||
                   lpSelectedInstance->hViewEntity !=
                                            lpEntityInstance->hViewEntity ) )
      {
         lpSelectedInstance = (LPSELECTEDINSTANCE)
                        zGETPTR( lpSelectedInstance->hNextSelectedInstance );
      }

      strcpy_s( szWorkString, zsizeof( szWorkString ), ">>>EntityInstance " );
      if ( lpSelectedInstance && lpSelectedInstance->nSelectSet )
      {
         zSHORT nWk1, nWk2, nWk3;

         nWk1 = 0;
         nWk2 = 0x0001;
         strcat_s( szWorkString, zsizeof( szWorkString ), "Selected(" );
         for ( nWk3 = 1; nWk3 < 17; nWk3++ )
         {
            if ( lpSelectedInstance->nSelectSet & nWk2 )
            {
               if ( nWk1 )
                  strcat_s( szWorkString, zsizeof( szWorkString ), "," );

               zltoa( nWk3, szWorkString + 250, zsizeof( szWorkString ) - 250 );
               strcat_s( szWorkString, zsizeof( szWorkString ), szWorkString + 250 );
               nWk1++;
            }

            nWk2 <<= 1;
         }

         strcat_s( szWorkString, zsizeof( szWorkString ), ") " );
      }

      TraceLine( "%s%s%d", szSpaces, "Entity Key: ", lpEntityInstance->ulKey );

      while ( lpViewAttrib )
      {
         strcpy_s( szWorkString + 3, zsizeof( szWorkString ) - 3, lpViewAttrib->szName );
         k = zstrlen( szWorkString );
         szWorkString[ k++ ] = ' ';
         while ( k < 14 )
            szWorkString[ k++ ] = ' ';

         szWorkString[ k ] = 0;
         if ( lpViewAttrib->cType == 'B' )
         {
            zULONG  ulLth;

            ulLth = 0;
            fnGetAttributeLength( &ulLth, lpView,
                                  zGETPTR( lpViewEntityCsr->hEntityInstance ),
                                  lpViewAttrib );
            if ( ulLth )
            {
               strcpy_s( szWorkString + k, zsizeof( szWorkString ) - k, "Blob Lth=" );
               zltoa( (zLONG) ulLth, szWorkString + k + 9, zsizeof( szWorkString ) - k - 9 );
               k = zstrlen( szWorkString );
               szWorkString[ k++ ] = ' ';
               szWorkString[ k ] = 0;
            }
         }
      // else  dks 2007.01.11
         {
            fnGetStringFromAttribute( &szWorkString[ k ],
                                      (zSHORT) ((zsizeof( szWorkString ) - 1000) - k),
                                      lpView,
                                      lpViewEntityCsr,
                                      lpViewAttrib, 0 );
         }

         if ( szWorkString[ k ] || szTraceAll[ 0 ] == 'Y' )
            TraceLineS( szSpaces, szWorkString );

         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib );
      }
   }

   return( 0 );
}

void
fnShowEntityInstanceInfo( LPENTITYINSTANCE lpEntityInstance )
{
   LPVIEWENTITY lpViewEntity;

   TraceLineS( "EntityInstance  ", "" );
   switch ( (zLONG) lpEntityInstance )
   {
      case (zLONG) UNSET_CSR:
         TraceLineS( "       is UNSET", "" );
         TraceLineS( "", "" );
         break;

      case (zLONG) NULL_CSR:
         TraceLineS( "       is NULL", "" );
         TraceLineS( "", "" );
         break;

      default:
         TraceLineI( "       level  ", lpEntityInstance->nLevel );
         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
         TraceLineS( "       name   ", lpViewEntity->szName );
   }
}

void
fnShowViewEntityCsrInfo( LPVIEWENTITYCSR lpViewEntityCsr )
{
   LPVIEWENTITY lpViewEntity;

   TraceLineS( "EntityCsr", "" );
   if ( lpViewEntityCsr )
   {
      TraceLineI( "       level  ", lpViewEntityCsr->nLevel );
      TraceLineI( "       hier   ", lpViewEntityCsr->nHierNbr );
      lpViewEntity = zGETPTR( lpViewEntityCsr->hViewEntity );
      TraceLineS( "       name   ", lpViewEntity->szName );
      fnShowEntityInstanceInfo( zGETPTR( lpViewEntityCsr->hEntityInstance ) );
   }
   else
   {
      TraceLineS( "       is NULL", "" );
      TraceLineS( "", "" );
      TraceLineS( "", "" );
   }
}

//./ ADD NAME=DisplayCursorInfo
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DisplayCursorInfo
//
//  PURPOSE:    To display an cursor information for a view
//
//  RETURNS:    0           - info Displayed
//              zCALL_ERROR - Error on call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT  OPERATION
DisplayCursorInfo( zVIEW  lpView )
{
   LPTASK            lpCurrentTask;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;
   LPVIEWOD          lpViewOD;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPENTITYINSTANCE  lpEntityInstance;
   LPVIEWSUBOBJECT   lpViewSubobject;
   zUSHORT           uIdx, uLimit;

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iDisplayCursorInfo, lpView,
                                          zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   lpViewOD  = zGETPTR( lpViewOI->hViewOD );
   lpViewEntityCsr = zGETPTR( lpViewCsr->hFirstOD_EntityCsr );

   TraceLineS( "View Cursor Info for Object ", lpViewOD->szName );
   TraceLineS( "  RootViewEntityCsr", "" );
   fnShowViewEntityCsrInfo( zGETPTR( lpViewCsr->hRootViewEntityCsr ) );
   TraceLineS( "", "" );

   lpEntityInstance = zGETPTR( lpViewCsr->hHierRootEntityInstance );
   TraceLineS( "ViewCsr HierRootInstance", "" );
   fnShowEntityInstanceInfo( zGETPTR( lpViewCsr->hHierRootEntityInstance ) );
   TraceLineS( "", "" );

   TraceLineS( "ViewCsr HierInstance", "" );
   fnShowEntityInstanceInfo( zGETPTR( lpViewCsr->hHierEntityInstance ) );
   TraceLineS( "", "" );

   TraceLineS( "ViewCsr ViewParentInstance", "" );
   fnShowEntityInstanceInfo( zGETPTR( lpViewCsr->hViewParentEntityInstance ) );
   TraceLineS( "", "" );

   uLimit = lpViewCsr->uEntities;
   TraceLineI( "The number of entities is ", uLimit );

   for ( uIdx = 1; uIdx <= uLimit; uIdx++, lpViewEntityCsr++ )
   {
      lpViewEntity = zGETPTR( lpViewEntityCsr->hViewEntity );

      TraceLineI( "Entity number ", uIdx );
      TraceLineI( "       level  ", lpViewEntity->nLevel );
      TraceLineI( "       hier   ", lpViewEntity->nHierNbr );
      TraceLineS( "       name   ", lpViewEntity->szName );
      fnShowViewEntityCsrInfo( lpViewEntityCsr );
      TraceLineS( "", "" );
   }

   lpViewSubobject = zGETPTR( lpViewCsr->hFirstViewSubobject );
   uIdx = 0;
   while ( lpViewSubobject )
   {
      TraceLineI( "Subobject Information ", ++uIdx );
      TraceLineS( "**ViewRootParentCsr", "" );
      fnShowViewEntityCsrInfo( zGETPTR( lpViewSubobject->hViewRootParentCsr ) );
      TraceLineS( "**SubobjectRootCsr", "" );
      fnShowViewEntityCsrInfo( zGETPTR( lpViewSubobject->hRootCsr ) );
      TraceLineI( "**Hierarchical number of root csr ",
                  lpViewSubobject->nRootHierNbr );
      TraceLineS( "**LastDescendentCsr", "" );
      fnShowViewEntityCsrInfo( zGETPTR( lpViewSubobject->hLastDescCsr ) );
      TraceLineI( "**LastDescHierNbr ", lpViewSubobject->nLastDescHierNbr );
      TraceLineS( "**ViewParentEntityInstance", "" );
      fnShowEntityInstanceInfo( zGETPTR( lpViewSubobject->
                                             hViewParentEntityInstance ) );
      TraceLineS( "**RootEntityInstance", "" );
      fnShowEntityInstanceInfo( zGETPTR( lpViewSubobject->
                                                   hRootEntityInstance ) );
      TraceLineS( "..Recursive subobject info..", "" );
      TraceLineI( "  Level adjustment ", lpViewSubobject->nLevelChg );
      if ( lpViewSubobject->hRecursViewEntity )
      {
         LPVIEWENTITY lpRecursViewEntity;

         lpRecursViewEntity = zGETPTR( lpViewSubobject->hRecursViewEntity );
         TraceLineS( "**Recursive View Entity: ",
                     lpRecursViewEntity->szName );
      }
      else
         TraceLineS( "**Recursive View Entity: ", "NULL" );

      TraceLineS( "            View Entity Csr", "" );
      fnShowViewEntityCsrInfo( zGETPTR( lpViewSubobject->
                                                   hRecursViewEntityCsr ) );
      TraceLineS( "        Parent EntityInstance", "" );
      fnShowEntityInstanceInfo( zGETPTR( lpViewSubobject->
                                             hRecursParentEntityInstance ) );
      TraceLineS( "..End Recursive subobject info..", "" );
      TraceLineS( "", "" );

      lpViewSubobject = zGETPTR( lpViewSubobject->hNextViewSubobject );
   }

   fnOperationReturn( iDisplayCursorInfo, lpCurrentTask );
   return( 0 );
}

void LOCALOPER
fnTraceViewEntity( LPVIEWENTITY lpViewEntity )
{
   TraceLineS( "", "" );
   TraceLineS( "      ENTITY Name = ", lpViewEntity->szName );
   TraceLineI( "      Level = ", (zLONG) lpViewEntity->nLevel );

   if ( lpViewEntity->szXML_Name[ 0 ] )
      TraceLineS( "      XML name = ", lpViewEntity->szXML_Name );

   if ( lpViewEntity->hParent )
   {
      LPVIEWENTITY lpParent = zGETPTR( lpViewEntity->hParent );
      TraceLineS( "      Parent name = ", lpParent->szName );
   }

   TraceLineI( "      Hier number = ", (zLONG) lpViewEntity->nHierNbr );
   TraceLineI( "      Card min = ", (zLONG) lpViewEntity->uCardMin );
   TraceLineI( "      Card max = ", (zLONG) lpViewEntity->uCardMax );
   TraceLineI( "      Record size = ", lpViewEntity->ulRecordSize );
   TraceLineI( "      NonPersist size = ",
               lpViewEntity->ulNonPersistSize );
   TraceLineI( "      Max Attr lth = ", (zLONG) lpViewEntity->ulMaxLth );
   TraceLineI( "      Lock Level      = ", (zLONG) lpViewEntity->nLock );

   if ( lpViewEntity->szDBName[ 0 ] )
      TraceLineS( "      Database name = ", lpViewEntity->szDBName );

   if ( lpViewEntity->szServer[ 0 ] )
      TraceLineS( "      Server name = ", lpViewEntity->szServer );

   if ( lpViewEntity->szECEOpername[ 0 ] )
      TraceLineS( "      ECEOper name = ", lpViewEntity->szECEOpername );

   TraceLineS( "      Flags:", "" );
   if ( lpViewEntity->bCreate )
      TraceLineS( "          bCreate", "" );
   if ( lpViewEntity->bDelete )
      TraceLineS( "          bDelete", "" );
   if ( lpViewEntity->bUpdate )
      TraceLineS( "          bUpdate", "" );
   if ( lpViewEntity->bInclude )
      TraceLineS( "          bInclude", "" );
   if ( lpViewEntity->bExclude )
      TraceLineS( "          bExclude", "" );
   if ( lpViewEntity->bInclSrc )
      TraceLineS( "          bInclSrc", "" );
   if ( lpViewEntity->bHidden )
      TraceLineS( "          bHidden", "" );
   if ( lpViewEntity->bPDelete )
      TraceLineS( "          bPDelete", "" );
   if ( lpViewEntity->bPRestrict )
      TraceLineS( "          bPRestrict", "" );
   if ( lpViewEntity->bCheckRestrict )
      TraceLineS( "          bCheckRestrict", "" );
   if ( lpViewEntity->bRecursiveSt )
      TraceLineS( "          bRecursiveSt", "" );
   if ( lpViewEntity->bAutoCreate )
      TraceLineS( "          bAutoCreate", "" );
   if ( lpViewEntity->bDerived )
      TraceLineS( "          bDerived", "" );
   if ( lpViewEntity->bDerivedPath )
      TraceLineS( "          bDerivedPath", "" );
   if ( lpViewEntity->bGenkey )
      TraceLineS( "          bGenkey", "" );
   if ( lpViewEntity->bAttrInit )
      TraceLineS( "          bAttrInit", "" );
   if ( lpViewEntity->bAttrOrder )
      TraceLineS( "          bAttrOrder", "" );
   if ( lpViewEntity->bAttrOrderChild )
      TraceLineS( "          bAttrOrderChild", "" );
   if ( lpViewEntity->bAutoSeq )
      TraceLineS( "          bAutoSeq", "" );
   if ( lpViewEntity->bIncrLoad )
      TraceLineS( "          bIncrLoad", "" );
   if ( lpViewEntity->bFullPersist )
      TraceLineS( "          bFullPersist", "" );
   if ( lpViewEntity->bSharesParRec )
      TraceLineS( "          bSharesParRec", "" );
   if ( lpViewEntity->bSharesChdRec )
      TraceLineS( "          bSharesChdRec", "" );
   if ( lpViewEntity->bDupInstance )
      TraceLineS( "          bDupInstance", "" );
   if ( lpViewEntity->bDupRel )
      TraceLineS( "          bDupRel", "" );
   if ( lpViewEntity->bDupRelPath )
      TraceLineS( "          bDupRelPath", "" );
   if ( lpViewEntity->bRelLink1 )
      TraceLineS( "          bRelLink1", "" );
   if ( lpViewEntity->bCreateConstraint )
      TraceLineS( "          bCreateConstraint", "" );
   if ( lpViewEntity->bDeleteConstraint )
      TraceLineS( "          bDeleteConstraint", "" );
   if ( lpViewEntity->bIncludeConstraint )
      TraceLineS( "          bIncludeConstraint", "" );
   if ( lpViewEntity->bExcludeConstraint )
      TraceLineS( "          bExcludeConstraint", "" );
   if ( lpViewEntity->bAcceptConstraint )
      TraceLineS( "          bAcceptConstraint", "" );
   if ( lpViewEntity->bCancelConstraint )
      TraceLineS( "          bCancelConstraint", "" );
   if ( lpViewEntity->bRequiredChild )
      TraceLineS( "          bRequiredChild", "" );
   if ( lpViewEntity->bAutoLoadFromParent )
      TraceLineS( "          bAutoLoadFromParent", "" );
   if ( lpViewEntity->bContainsBlob )
      TraceLineS( "          bContainsBlob", "" );
   if ( lpViewEntity->bHasDB_Oper )
      TraceLineS( "          bHasDB_Oper", "" );

} // fnTraceViewEntity

void LOCALOPER
fnTraceViewAttrib( LPVIEWATTRIB lpViewAttrib, zPCHAR s )
{
   TraceLineS( "", "" );
   TraceLineS( "              ATTRIBUTE Name = ",
               lpViewAttrib->szName );

   s[ 0 ] = lpViewAttrib->cType;
   TraceLineS( "              Type = ", s );
   TraceLineI( "              ERTok  = ", (zLONG) lpViewAttrib->lERAttTok );
   TraceLineI( "              Length = ", (zLONG) lpViewAttrib->ulLth );
   TraceLineI( "              Offset = ",
               (zLONG) lpViewAttrib->ulRecordOffset );
   if ( lpViewAttrib->cSequencing > 0 )
      TraceLineI( "              Sequencing # = ",
                  (zLONG) lpViewAttrib->cSequencing );

   if ( lpViewAttrib->szDerivedOper[ 0 ] )
      TraceLineS( "              DerivedOper = ",
                  lpViewAttrib->szDerivedOper );

   if ( lpViewAttrib->hDerivedXPG )
      TraceLineS( "              DerivedXPG = YES", "" );

   if ( lpViewAttrib->cDB_Oper )
   {
      s[ 0 ] = lpViewAttrib->cDB_Oper;
      TraceLineS( "              DB Oper = ", s );
   }

   TraceLineS( "              FLAGS:", "" );
   if ( lpViewAttrib->bPersist )
      TraceLineS( "                 bPersist", "" );

   if ( lpViewAttrib->bKey )
      TraceLineS( "                 bKey", "" );

   if ( lpViewAttrib->bForeignKey )
      TraceLineS( "                 bForeignKey", "" );

   if ( lpViewAttrib->bGenkey )
      TraceLineS( "                 bGenkey", "" );

   if ( lpViewAttrib->bRequired )
      TraceLineS( "                 bRequired", "" );

   if ( lpViewAttrib->bHidden )
      TraceLineS( "                 bHidden", "" );

   if ( lpViewAttrib->bCaseSens )
      TraceLineS( "                 bCaseSens", "" );

   if ( lpViewAttrib->bCrDate )
      TraceLineS( "                 bCrDate", "" );

   if ( lpViewAttrib->bUpDate )
      TraceLineS( "                 bUpDate", "" );

   if ( lpViewAttrib->bUserID )
      TraceLineS( "                 bUserID", "" );

   if ( lpViewAttrib->bAutoSeq )
      TraceLineS( "                 bAutoSeq", "" );

   if ( lpViewAttrib->bSequencingD )
      TraceLineS( "                 bSequencingD", "" );

   if ( lpViewAttrib->bNoUpdate )
      TraceLineS( "                 bNoUpdate", "" );

   if ( lpViewAttrib->bNoPersistUpd )
      TraceLineS( "                 bNoPersistUpd", "" );

} // fnTraceViewAttrib

//./ ADD NAME=DisplayObjectDef
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DisplayObjectDef
//
//  PURPOSE:    To print to the trace file the object definition.
//
//  PARAMETERS: lpPtr    - A view pointer OR Object definition pointer.
//              nControl - if = 0, then lpPtr is a view pointer
//                         if = 1, then lpPtr is an object def pointer.
//
//  RETURNS:    0           - Trace worked
//              zCALL_ERROR - Something wrong.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
DisplayObjectDef( zVIEW lpPtr, zSHORT nControl )
{
   LPVIEWOD     lpViewOD;
   LPVIEWENTITY lpViewEntity;
   LPVIEWATTRIB lpViewAttrib;
   LPDATARECORD lpDataRecord;
   LPDATAFIELD  lpDataField;
   LPRELRECORD  lpRelRecord;
   LPRELFIELD   lpRelField;
   zCHAR        sz[ 2 ];

   if ( nControl == 1 )
      lpViewOD = (LPVIEWOD) lpPtr;
   else
      lpViewOD = zGETPTR( lpPtr->hViewOD );

   sz[ 1 ] = 0;

   TraceLineS( "", "" );
   TraceLineS( "Tracing object definition", "" );
   TraceLineS( "", "" );

   if ( lpViewOD == 0 )
   {
      TraceLineS( "Cancel Tracing, lpViewOD is null", "" );
      return( -1 );
   }

   TraceLineS( "Object def name = ", lpViewOD->szName );
   TraceLineS( "Database name = ", lpViewOD->szDfltDBName );

   if ( lpViewOD->szOperLibname[ 0 ] )
      TraceLineS( "OperLib name = ", lpViewOD->szOperLibname );

   if ( lpViewOD->szOCEOpername[ 0 ] )
      TraceLineS( "OCEOper name = ", lpViewOD->szOCEOpername );

   if ( lpViewOD->hDBHandler )
   {
      LPDBHANDLER lpDBHandler = zGETPTR( lpViewOD->hDBHandler );

      TraceLineS( "DBHandler name = ", lpDBHandler->szName );
   }

   if ( lpViewOD->hGKHandler )
   {
      LPGKHANDLER lpGKHandler = zGETPTR( lpViewOD->hGKHandler );

      TraceLineS( "GKHandler name = ", lpGKHandler->szName );
   }

   TraceLineI( "Entity Count   = ", lpViewOD->uEntities );
   TraceLineI( "Cache Number   = ", lpViewOD->cCacheNbr );
   TraceLineI( "Lock Level     = ", lpViewOD->nLock );
   TraceLineI( "Ent Lock Level = ", lpViewOD->nEntityLock );

#if 0
   TraceLineX( "Locking Flags  = 0x", lpViewOD->lLockFlags );
   if ( lpViewOD->lLockFlags != 0 )
   {
      if ( lpViewOD->lLockFlags & zLOCK_OPTIMISTIC )
         TraceLineS( "          zLOCK_OPTIMISTIC", "" );

      if ( lpViewOD->lLockFlags & zLOCK_IGNOREINC )
         TraceLineS( "          zLOCK_IGNOREINC", "" );
   }
#endif

   TraceLineS( "Flags: ", "" );
   if ( lpViewOD->bHasDupInstance )
      TraceLineS( "     bHasDupInstance", "" );

   if ( lpViewOD->bHasDupRel )
      TraceLineS( "     bHasDupRel", "" );

   if ( lpViewOD->bHasDerivedPath )
      TraceLineS( "     bHasDerivedPath", "" );

   if ( lpViewOD->bActivateConstraint )
      TraceLineS( "     bActivateConstraint", "" );

   if ( lpViewOD->bActivateEmptyConstraint )
      TraceLineS( "     bActivateEmptyConstraint", "" );

   if ( lpViewOD->bCommitConstraint )
      TraceLineS( "     bCommitConstraint", "" );

   if ( lpViewOD->bDropOIConstraint )
      TraceLineS( "     bDropOIConstraint", "" );

   if ( lpViewOD->bDeprecated )
      TraceLineS( "     bDeprecated", "" );

   lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
   while ( lpViewEntity )
   {
      fnTraceViewEntity( lpViewEntity );

      lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
      while ( lpViewAttrib )
      {
         fnTraceViewAttrib( lpViewAttrib, sz );

         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib );
      } // while ( lpViewAttrib )...

      lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );
      while ( lpDataRecord )
      {
         TraceLineS( "", "" );
         TraceLineS( "              DATARECORD name = ",
                     lpDataRecord->szRecordName );

         sz[ 0 ] = lpDataRecord->cRecordType;
         TraceLineS( "              Record Type = ", sz );

         if ( lpDataRecord->lRecordID )
            TraceLineI( "              Record ID = ", lpDataRecord->lRecordID );

         lpDataField = zGETPTR( lpDataRecord->hFirstDataField );
         while ( lpDataField )
         {
            LPVIEWATTRIB lpTemp = zGETPTR( lpDataField->hViewAttrib );

            TraceLineS( "                DATAFIELD Attribute name = ",
                        lpTemp->szName );
            TraceLineS( "                Field name = ",
                        lpDataField->szFldName );

            sz[ 0 ] = lpDataField->cFldType;
            TraceLineS( "                Field type = ", sz );

            TraceLineI( "                Field length = ",
                        (zLONG) lpDataField->uFldLth );

            if ( lpDataField->uFldOffset )
               TraceLineI( "                Field length = ",
                           (zLONG) lpDataField->uFldOffset );
            if ( lpDataField->lFldID )
               TraceLineI( "                Field length = ",
                           lpDataField->lFldID );

            lpDataField = zGETPTR( lpDataField->hNextDataField );
         } // while ( lpDataField )...

         lpRelRecord = zGETPTR( lpDataRecord->hFirstRelRecord );
         while ( lpRelRecord )
         {
            TraceLineS( "", "" );
            TraceLineS( "                RELRECORD", "" );
            sz[ 0 ] = lpRelRecord->cOwnerMember;
            TraceLineS( "                cOwnerMember = ", sz );
            if ( lpRelRecord->szRecordName[ 0 ] )
               TraceLineS( "                Record name = ",
                           lpRelRecord->szRecordName );

            if ( lpRelRecord->lRecordID )
               TraceLineI( "                Record ID = ",
                           (zLONG) lpRelRecord->lRecordID );

            if ( lpRelRecord->szSetName1[ 0 ] )
               TraceLineS( "                Set name 1 = ",
                           lpRelRecord->szSetName1 );

            if ( lpRelRecord->lSetID1 )
               TraceLineI( "                Set 1 ID = ",
                           (zLONG) lpRelRecord->lSetID1 );

            if ( lpRelRecord->szSetName2[ 0 ] )
               TraceLineS( "                Set name 2 = ",
                           lpRelRecord->szSetName2 );

            if ( lpRelRecord->lSetID2 )
               TraceLineI( "                Set 2 ID = ",
                           (zLONG) lpRelRecord->lSetID2 );

            lpRelField = zGETPTR( lpRelRecord->hFirstRelField );
            while ( lpRelField )
            {
               LPDATAFIELD  lpTempDataField;
               LPVIEWATTRIB lpTempViewAttrib;
               LPVIEWENTITY lpTempViewEntity;

               TraceLineS( "", "" );
               TraceLineS( "                     RELFIELD:", "" );

               if ( lpRelField->hSrcDataField )
               {
                  lpTempDataField  = zGETPTR( lpRelField->hSrcDataField );
                  lpTempViewAttrib = zGETPTR( lpTempDataField->hViewAttrib );
                  lpTempViewEntity = zGETPTR( lpTempViewAttrib->hViewEntity );

                  TraceLineS( "                     Source entity = ",
                              lpTempViewEntity->szName );
                  TraceLineS( "                     Source attrib = ",
                              lpTempViewAttrib->szName );
               }

               if ( lpRelField->hRelDataField )
               {
                  lpTempDataField  = zGETPTR( lpRelField->hRelDataField );
                  lpTempViewAttrib = zGETPTR( lpTempDataField->hViewAttrib );
                  lpTempViewEntity = zGETPTR( lpTempViewAttrib->hViewEntity );

                  TraceLineS( "                     Rel entity = ",
                              lpTempViewEntity->szName );
                  TraceLineS( "                     Rel attrib = ",
                              lpTempViewAttrib->szName );
               }

               if ( lpRelField->szFldName[ 0 ] )
                  TraceLineS( "                     Field name = ",
                              lpRelField->szFldName );

               lpRelField = zGETPTR( lpRelField->hNextRelField );
            } // while ( lpRelField )...

            lpRelRecord = zGETPTR( lpRelRecord->hNextRelRecord );
         } // while ( lpRelRecord )...

         lpDataRecord = zGETPTR( lpDataRecord->hNextDataRecord );
      } // while ( lpDataRecord )...

      lpViewEntity = zGETPTR( lpViewEntity->hNextHier );
   } // while ( lpViewEntity )...

   return( 0 );

}  /* DisplayObjectDef */

//./ ADD NAME=fnCompareEntityToEntity
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnCompareEntityToEntity
//
//  PURPOSE:    To compare two entities.  Compares the entity and all of
//              its attributes.  If the entities are not the same type,
//              then the attributes are compared by name.
//
//  RETURNS:    0           - Entities are equal
//              1           - Entities are not equal
//              zCALL_ERROR - Error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 7
zSHORT
fnCompareEntityToEntity( LPVIEWENTITY     lpTgtViewEntity,
                         LPENTITYINSTANCE lpTgtEntityInstance,
                         LPVIEWENTITY     lpSrcViewEntity,
                         LPENTITYINSTANCE lpSrcEntityInstance,
                         zBOOL            bPersistOnly,
                         zBOOL            bKeysOnly )
{
   LPVIEWOI lpViewOI      = zGETPTR( lpSrcEntityInstance->hViewOI );
   LPTASK   lpCurrentTask = zGETPTR( lpViewOI->hTask );
   zSHORT   nRC;

   // Start by assuming that the entities are equal.
   nRC = 0;

   if ( lpTgtViewEntity != lpSrcViewEntity )
   {
      LPVIEWATTRIB lpFirstSrcViewAttrib;
      LPVIEWATTRIB lpTgtViewAttrib;
      LPVIEWATTRIB lpSrcViewAttrib;

      // The view entities are different, so compare attributes by name.
      lpFirstSrcViewAttrib = zGETPTR( lpSrcViewEntity->hFirstOD_Attrib );
      for ( lpTgtViewAttrib = zGETPTR( lpTgtViewEntity->hFirstOD_Attrib );
            lpTgtViewAttrib;
            lpTgtViewAttrib = zGETPTR( lpTgtViewAttrib->hNextOD_Attrib ) )
      {
         if ( bPersistOnly && lpTgtViewAttrib->bPersist == FALSE )
            continue;

         if ( bKeysOnly && lpTgtViewAttrib->bKey == FALSE )
            continue;

         if ( lpTgtViewAttrib->bHidden )
            continue;

         // Find the src view attrib that has the same name as lpTgtViewAttrib
         lpSrcViewAttrib = lpFirstSrcViewAttrib;
         while ( lpSrcViewAttrib &&
                 zstrcmp( lpSrcViewAttrib->szName,
                          lpTgtViewAttrib->szName ) != 0 )
         {
            lpSrcViewAttrib = zGETPTR( lpSrcViewAttrib->hNextOD_Attrib );
         }

         // If no matching attr was found skip it.
         if ( lpSrcViewAttrib == 0 )
            continue;

         if ( lpSrcViewAttrib->bHidden )
            continue;

         if ( fnCompareEIAttrs( lpCurrentTask,
                                0, lpTgtEntityInstance, lpTgtViewAttrib, 0,
                                0, lpSrcEntityInstance, lpSrcViewAttrib, 0 ) != 0 )
         {
            return( 1 ); // Indicate unequal.
         }

      }  // for ( lpTgtViewAttrib... )...

   } // if ( lpTgtViewEntity != lpSrcViewEntity )...
   else
   {
      LPVIEWATTRIB lpCompareViewAttrib;

      // Compare each attribute for the entities.
      for ( lpCompareViewAttrib = zGETPTR( lpTgtViewEntity->hFirstOD_Attrib );
            lpCompareViewAttrib;
            lpCompareViewAttrib = zGETPTR( lpCompareViewAttrib->hNextOD_Attrib ) )
      {
         if ( bPersistOnly && lpCompareViewAttrib->bPersist == FALSE )
            continue;

         if ( bKeysOnly && lpCompareViewAttrib->bKey == FALSE )
            continue;

         if ( lpCompareViewAttrib->bHidden )
            continue;

         // Compare the attributes.
         if ( fnCompareEIAttrs( lpCurrentTask,
                                0, lpTgtEntityInstance, lpCompareViewAttrib, 0,
                                0, lpSrcEntityInstance,
                                lpCompareViewAttrib, 0 ) != 0 )
         {
            return( 1 ); // Indicate unequal.
         }

      }  // while ( lpCompareViewAttrib )...

   }  // if (...) else...

   return( 0 );

}  /* fnCompareEntityToEntity */

//./ ADD NAME=CompareEntityToEntity
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CompareEntityToEntity
//
//  PURPOSE:    To compare two entities.  Compares the entity and all of
//              its attributes.  If the entities are not the same type,
//              then the attributes are compared by name.
//
//  PARAMETERS: lpTgtView          - View containing target entity
//              szTgtEntityName    - Entity to be compared
//              lpSrcView          - View containing source entity
//              szSrcEntityName    - Entity to be compared
//
//  RETURNS:    0           - Entities are equal
//              1           - Entities are not equal
//              zCALL_ERROR - Error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zSHORT OPERATION
CompareEntityToEntity( zVIEW lpTgtView, zCPCHAR cpcTgtEntityName,
                       zVIEW lpSrcView, zCPCHAR cpcSrcEntityName )
{
   LPTASK           lpCurrentTask;
   LPVIEWENTITY     lpTgtViewEntity;
   LPVIEWENTITYCSR  lpTgtViewEntityCsr;
   LPVIEWENTITY     lpSrcViewEntity;
   LPVIEWENTITYCSR  lpSrcViewEntityCsr;
   int              nRC;

   // Validate parameters
   if ( fnValidateInstanceParameters( &lpCurrentTask,
                                      &lpTgtViewEntity,
                                      &lpTgtViewEntityCsr,
                                      iCompareEntityToEntity,
                                      lpTgtView,
                                      cpcTgtEntityName, 0 ) )
   {
      return( zCALL_ERROR );
   }

   if ( fnValidateInstanceParameters( &lpCurrentTask,
                                      &lpSrcViewEntity,
                                      &lpSrcViewEntityCsr,
                                      iCompareEntityToEntity,
                                      lpSrcView,
                                      cpcSrcEntityName,
                                      2 ) ) // we've already sent the id
   {
   // fnOperationReturn( iCompareEntityToEntity, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // Start by assuming that the entities are equal.
   nRC = fnCompareEntityToEntity( lpTgtViewEntity,
                                  zGETPTR( lpTgtViewEntityCsr->hEntityInstance ),
                                  lpSrcViewEntity,
                                  zGETPTR( lpSrcViewEntityCsr->hEntityInstance ),
                                  FALSE, FALSE );  // Compare all attributes.

   fnOperationReturn( iCompareEntityToEntity, lpCurrentTask );
   return( nRC );

}  /* CompareEntityToEntity */

//./ ADD NAME=fnCompareEntitiesIgnoringAttrs
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnCompareEntitiesIgnoringAttrs
//
//  PURPOSE:    To compare two entities.  Compares the entity and all of
//              its attributes.  If the entities are not the same type,
//              then the attributes are compared by name.
//
//  RETURNS:    0           - Entities are equal
//              1           - Entities are not equal
//              zCALL_ERROR - Error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 6
zSHORT
fnCompareEntitiesIgnoringAttrs( LPVIEWENTITY     lpTgtViewEntity,
                                LPENTITYINSTANCE lpTgtEntityInstance,
                                LPVIEWENTITY     lpSrcViewEntity,
                                LPENTITYINSTANCE lpSrcEntityInstance,
                                zPCHAR           pchAttrList )
{
   zPCHAR   pch;
   zPCHAR   pchSemi;
   zSHORT   nRC;
   LPVIEWOI lpViewOI      = zGETPTR( lpSrcEntityInstance->hViewOI );
   LPTASK   lpCurrentTask = zGETPTR( lpViewOI->hTask );

   // Start by assuming that the entities are equal.
   nRC = 0;

   if ( lpTgtViewEntity != lpSrcViewEntity )
   {
      LPVIEWATTRIB lpFirstSrcViewAttrib;
      LPVIEWATTRIB lpTgtViewAttrib;
      LPVIEWATTRIB lpSrcViewAttrib;

      // The view entities are different, so compare attributes by name.
      lpFirstSrcViewAttrib = zGETPTR( lpSrcViewEntity->hFirstOD_Attrib );
      for ( lpTgtViewAttrib = zGETPTR( lpTgtViewEntity->hFirstOD_Attrib );
            lpTgtViewAttrib;
            lpTgtViewAttrib = zGETPTR( lpTgtViewAttrib->hNextOD_Attrib ) )
      {
         if ( lpTgtViewAttrib->bHidden )
            continue;

         pch = pchAttrList;
         while ( pch )
         {
            pchSemi = zstrchr( pch, ';' );
            if ( pchSemi )
               *pchSemi = 0;

            if ( zstrcmp( pch, lpTgtViewAttrib->szName ) == 0 )
            {
               if ( pchSemi )
                  *pchSemi = ';';

               break;
            }

            if ( pchSemi )
               *pchSemi = ';';

            pch = pchSemi;
         }

         if ( pch )
            continue;

         // Find the src view attrib that has the same name as lpTgtViewAttrib
         lpSrcViewAttrib = lpFirstSrcViewAttrib;
         while ( lpSrcViewAttrib &&
                 zstrcmp( lpSrcViewAttrib->szName,
                          lpTgtViewAttrib->szName ) != 0 )
         {
            lpSrcViewAttrib = zGETPTR( lpSrcViewAttrib->hNextOD_Attrib );
         }

         // If no matching attr was found skip it.
         if ( lpSrcViewAttrib == 0 )
            continue;

         if ( lpSrcViewAttrib->bHidden )
            continue;

         if ( fnCompareEIAttrs( lpCurrentTask,
                                0, lpTgtEntityInstance, lpTgtViewAttrib, 0,
                                0, lpSrcEntityInstance,
                                lpSrcViewAttrib, 0 ) != 0 )
         {
            return( 1 ); // Indicate unequal.
         }

      }  // for ( lpTgtViewAttrib... )...

   } // if ( lpTgtViewEntity != lpSrcViewEntity )...
   else
   {
      LPVIEWATTRIB lpCompareViewAttrib;

      // Compare each attribute for the entities.
      for ( lpCompareViewAttrib = zGETPTR( lpTgtViewEntity->hFirstOD_Attrib );
            lpCompareViewAttrib;
            lpCompareViewAttrib = zGETPTR( lpCompareViewAttrib->hNextOD_Attrib ) )
      {
         if ( lpCompareViewAttrib->bHidden )
            continue;

         pch = pchAttrList;
         while ( pch )
         {
            pchSemi = zstrchr( pch, ';' );
            if ( pchSemi )
               *pchSemi = 0;

            if ( zstrcmp( pch, lpCompareViewAttrib->szName ) == 0 )
            {
               if ( pchSemi )
                  *pchSemi = ';';

               break;
            }

            if ( pchSemi )
               *pchSemi = ';';

            pch = pchSemi;
         }

         if ( pch )
            continue;

         // Compare the attributes.
         if ( fnCompareEIAttrs( lpCurrentTask,
                                0, lpTgtEntityInstance, lpCompareViewAttrib, 0,
                                0, lpSrcEntityInstance,
                                lpCompareViewAttrib, 0 ) != 0 )
         {
            return( 1 ); // Indicate unequal.
         }

      }  // while ( lpCompareViewAttrib )...

   }  // if (...) else...

   return( 0 );

}  /* fnCompareEntitiesIgnoringAttrs */

//./ ADD NAME=CompareEntitiesIgnoringAttrs
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CompareEntitiesIgnoringAttrs
//
//  PURPOSE:    To compare two entities.  Compares the entity and all of
//              its attributes.  If the entities are not the same type,
//              then the attributes are compared by name.
//
//  PARAMETERS: lpTgtView          - View containing target entity
//              cpcTgtEntityName    - Entity to be compared
//              lpSrcView          - View containing source entity
//              cpcSrcEntityName    - Entity to be compared
//
//  RETURNS:    0           - Entities are equal
//              1           - Entities are not equal
//              zCALL_ERROR - Error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT OPERATION
CompareEntitiesIgnoringAttrs( zVIEW lpTgtView, zCPCHAR cpcTgtEntityName,
                              zVIEW lpSrcView, zCPCHAR cpcSrcEntityName,
                              zPCHAR pchAttrList )
{
   LPTASK           lpCurrentTask;
   LPVIEWENTITY     lpTgtViewEntity;
   LPVIEWENTITYCSR  lpTgtViewEntityCsr;
   LPVIEWENTITY     lpSrcViewEntity;
   LPVIEWENTITYCSR  lpSrcViewEntityCsr;
   int              nRC;

   // Validate parameters
   if ( fnValidateInstanceParameters( &lpCurrentTask,
                                      &lpTgtViewEntity,
                                      &lpTgtViewEntityCsr,
                                      iCompareEntityToEntity,
                                      lpTgtView,
                                      cpcTgtEntityName, 0 ) )
   {
      return( zCALL_ERROR );
   }

   if ( fnValidateInstanceParameters( &lpCurrentTask,
                                      &lpSrcViewEntity,
                                      &lpSrcViewEntityCsr,
                                      iCompareEntityToEntity,
                                      lpSrcView,
                                      cpcSrcEntityName,
                                      2 ) ) // we've already sent the id
   {
   // fnOperationReturn( iCompareEntityToEntity, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // Start by assuming that the entities are equal.
   nRC = fnCompareEntitiesIgnoringAttrs( lpTgtViewEntity,
                                         zGETPTR( lpTgtViewEntityCsr->hEntityInstance ),
                                         lpSrcViewEntity,
                                         zGETPTR( lpSrcViewEntityCsr->hEntityInstance ),
                                         pchAttrList ); // Ignore attrs in list

   fnOperationReturn( iCompareEntityToEntity, lpCurrentTask );
   return( nRC );

}  /* CompareEntitiesIgnoringAttrs */

/*
   Used by fnCompareOI_ToOI, this skips certain entity instances depending
   on the value of lControl.

   Returns: TRUE  - Entity instance skipped.
            FALSE - Entity instance OK.
*/
zBOOL
fnCompareSkipEntityInstance( LPENTITYINSTANCE *ppEntityInstance,
                             zLONG            lControl )
{
   LPENTITYINSTANCE lpOldEntityInstance = *ppEntityInstance;

   // Skip entity instances for the following reasons:
   //   (1) Entity instance is hidden
   //   (2) User has indicated that we should ignore included instances
   //       and the entity instance is included.
   // Note that if any of the above conditions are true for a particular
   // entity, then we can safely skip over ALL the child entities for that
   // entity.  If we add a condition that doesn't allow us to skip children
   // (e.g. skip derived entities) then we will need another 'while' loop.
   while ( (*ppEntityInstance) )
   {
      zBOOL bSkip;
      LPVIEWENTITY lpViewEntity = zGETPTR( (*ppEntityInstance)->hViewEntity );

      // If the user only wants to compare persistant data, see if the
      // current entity instance has a data record.  If it doesn't, then
      // the entity isn't persistent.
      if ( lControl & zCOMPAREOI_PERSISTONLY &&
           lpViewEntity->hFirstDataRecord == 0 )
      {
         (*ppEntityInstance) = zGETPTR( (*ppEntityInstance)->hNextHier );
         continue;
      }

      // We use bSkip for readability's sake.  We start off by assuming that
      // we will not skip the current *ppEntityInstance.  We then check each
      // of the reasons we would skip the entity instance.  If any of them
      // come up TRUE, then we set bSkip to indicate that we're going to
      // skip the entity instance.

      // Assume that we're not going to skip the entity instance.
      bSkip = FALSE;

      // Skip the entity instance if it's hidden.
      if ( (*ppEntityInstance)->u.nInd.bHidden )
         bSkip = TRUE;

      // If we're not skipping the current entity instance, then break the
      // loop.
      if ( bSkip == FALSE )
         break;

      // Skip the current entity and all its children.
      if ( (*ppEntityInstance)->hNextTwin )
      {
         // Current entity has a twin, so set the twin as 'current'.
         (*ppEntityInstance) = zGETPTR( (*ppEntityInstance)->hNextTwin );
      }
      else
      {
         zSHORT nLevel;

         // Current entity has no twin, so look for the next entity that has
         // a level that is less than or equal to the 'current' entity.  This
         // will set (*ppEntityInstance) to the next entity in hier order
         // that is not a child of the 'current' entity.
         nLevel = (*ppEntityInstance)->nLevel;
         do
         {
            (*ppEntityInstance) = zGETPTR( (*ppEntityInstance)->hNextHier );
         } while ( (*ppEntityInstance) &&
                   (*ppEntityInstance)->nLevel > nLevel );
      }

   } // while...

   return( *ppEntityInstance == lpOldEntityInstance );

} // fnCompareSkipEntityInstance

//./ ADD NAME=fnCompareOI_ToOI
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnCompareOI_ToOI
//
//  PURPOSE:    To compare two object instances.
//              its attributes.
//
//  PARAMETERS: lpTgtView          - View containing target instance
//              lpSrcView          - View containing source instance
//              lControl           - Controls what kind of compares are
//                                   to be used. Values are:
//                   0 - Default.
//                   zCOMPAREOI_IGNOREINC - Only compare the key values of
//                         entities that are include only and totally ignore
//                         entities that are display only.
//                   zCOMPAREOI_PERSISTONLY -
//                   zCOMPAREOI_RETURN - If the two OIs are only different
//                         in attr values, the compare continues unless
//                         this flag is set.
//
//              NOTE: Any changes dealing with lControl must take into
//              account that lControl = 0 is the default.  For example,
//              if the compare is changed so that included entities
//              can be ignored then lControl == 0 must compare included
//              entities.  In other words, how this operation works
//              must never change when lControl == 0.  This is because
//              the operation CompareOI_ToOI calls this operation with
//              lControl = 0.
//
//  RETURNS:    0           - Object instances are equal
//              1           - Mismatch in entity instances in OI
//              2           - Entity instance structure mismatch in OI
//              zCALL_ERROR - Error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT
fnCompareOI_ToOI( zVIEW lpTgtView, zVIEW lpSrcView, zLONG lControl )
{
   zSHORT            nRC = 0;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpSrcViewOI;
   LPVIEWOI          lpTgtViewOI;
   LPENTITYINSTANCE  lpSrcInstance;
   LPENTITYINSTANCE  lpTgtInstance;
   zBOOL             bComparePersistOnly;
   zBOOL             bCompareKeysOnly;

   bComparePersistOnly = (zBOOL) (lControl & zCOMPAREOI_PERSISTONLY);

   lpViewCsr   = zGETPTR( lpSrcView->hViewCsr );
   lpSrcViewOI = zGETPTR( lpViewCsr->hViewOI );
   lpViewCsr   = zGETPTR( lpTgtView->hViewCsr );
   lpTgtViewOI = zGETPTR( lpViewCsr->hViewOI );

   for ( lpSrcInstance = zGETPTR( lpSrcViewOI->hRootEntityInstance ),
         lpTgtInstance = zGETPTR( lpTgtViewOI->hRootEntityInstance );
         lpSrcInstance && lpTgtInstance;
         lpSrcInstance = zGETPTR( lpSrcInstance->hNextHier ),
         lpTgtInstance = zGETPTR( lpTgtInstance->hNextHier ) )
   {
      LPVIEWENTITY lpTgtEntity;
      LPVIEWENTITY lpSrcEntity;

      // Root out undesired entities (e.g. hidden entities).
      if ( fnCompareSkipEntityInstance( &lpSrcInstance, lControl ) )
         if ( lpSrcInstance == 0 )
            break;

      if ( fnCompareSkipEntityInstance( &lpTgtInstance, lControl ) )
         if ( lpTgtInstance == 0 )
            break;

      lpTgtEntity = zGETPTR( lpTgtInstance->hViewEntity );
      lpSrcEntity = zGETPTR( lpSrcInstance->hViewEntity );

      // If entity types are different or if the level of the instances don't
      // match (possible with recursive entities) then return with mismatch.
      if ( lpSrcEntity != lpTgtEntity ||
           lpSrcInstance->nLevel != lpTgtInstance->nLevel )
      {
         TraceLineS( "(tr) CompareOI_ToOI - Entity Structure mismatch", "" );
         return( 2 );
      }

      // Assume we're going to compare all attributes.
      bCompareKeysOnly = FALSE;

      // If the control flag indicates we are to ignore non-keys in
      // include-only entities, check for include/create.
      if ( lControl & zCOMPAREOI_IGNOREINC )
      {
         if ( lpTgtEntity->bCreate == FALSE && lpTgtEntity->bUpdate == FALSE )
         {
            if ( lpTgtEntity->bInclude == FALSE )
            {
               // User can't change entity at all so it's just displayable.
               // Ignore this entity instance.
               continue;
            }

            // Entity is only includable so only compare the keys.
            bCompareKeysOnly = TRUE;
         }
      }

      if ( fnCompareEntityToEntity( zGETPTR( lpTgtInstance->hViewEntity ),
                                    lpTgtInstance,
                                    zGETPTR( lpSrcInstance->hViewEntity ),
                                    lpSrcInstance, bComparePersistOnly,
                                    bCompareKeysOnly ) == 1 )
      {
         TraceLineS( "(tr) CompareOI_ToOI - Entity Instance mismatch", "" );
         if ( lControl & zCOMPAREOI_RETURN )
            return( 1 );

         nRC = 1;
      }

   } // for ( ... )...

   // If either of the two entity instances are not null, then the OIs don't
   // match because at least one of the entity instances is null.
   if ( lpSrcInstance || lpTgtInstance )
   {
      TraceLineS( "(tr) CompareOI_ToOI - Entity Structure mismatch", " Empty" );
      nRC = 2;
   }

   return( nRC );
}

//./ ADD NAME=CompareOI_ToOI
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CompareOI_ToOI
//
//  PURPOSE:    To compare two object instances.
//              its attributes.
//
//  PARAMETERS: lpTgtView          - View containing target instance
//              lpSrcView          - View containing source instance
//
//  RETURNS:    0           - Object instances are equal
//              1           - Mismatch in entity instances in OI
//              2           - Entity instance structure mismatch in OI
//              zCALL_ERROR - Error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
CompareOI_ToOI( zVIEW lpTgtView, zVIEW lpSrcView )
{
   LPTASK            lpCurrentTask;
   LPVIEWCSR         lpSrcViewCsr;
   LPVIEWCSR         lpTgtViewCsr;
   zSHORT            nRC;

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iCompareOI_ToOI, lpTgtView,
                                          zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( fnValidViewCsr( lpCurrentTask, lpSrcView ) == 0 )
   {
      fnOperationReturn( iCompareOI_ToOI, lpCurrentTask );
      return( zCALL_ERROR );
   }

   if ( lpSrcView->hViewOD != lpTgtView->hViewOD )
   {
      TraceLineS( "CompareOI_ToOI - Object type mismatch", "" );
      fnOperationReturn( iCompareOI_ToOI, lpCurrentTask );
      return( zCALL_ERROR );
   }

   lpSrcViewCsr = zGETPTR( lpSrcView->hViewCsr );
   lpTgtViewCsr = zGETPTR( lpTgtView->hViewCsr );

   if ( lpSrcViewCsr->hViewOI == lpTgtViewCsr->hViewOI )
   {
      TraceLineS( "(tr) CompareOI_ToOI - Src and Tgt are same instance", "" );
      fnOperationReturn( iCompareOI_ToOI, lpCurrentTask );
      return( 0 );
   }

   nRC = fnCompareOI_ToOI( lpTgtView, lpSrcView, 0 );

   fnOperationReturn( iCompareOI_ToOI, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=GetTracingFlags
// Source Module=kzoetraa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      GetTracingFlags
//
//  PURPOSE:    Returns a pointer to the tracing flags.
//              its attributes.
//
//  PARAMETERS:
//
//  RETURNS:    0 - Error
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
LPTRACINGFLAGS OPERATION
GetTracingFlags( void )
{
   if ( AnchorBlock )
      return( &AnchorBlock->TraceFlags );
   else
      return( 0 );
}
