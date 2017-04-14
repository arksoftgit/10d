//
// MODULE NAME:  KZOEOIAA  -  Object services Object Instance Activation
// DESCRIPTION:  This is the source file which contains Object services
//               operations for Activating and dropping object Instances
//               as well as creating and deleting views on object instances
// OPERATIONS:   All OPERATIONS which activate and drop object Instances
// **********************************************************************
// * Copyright (c) 1993-2016 QuinSoft, Inc. All rights reserved. *
// * Confidential and Proprietary material subject to license -         *
// * do not reproduce or disclose. This material is an unpublished      *
// * work and is considered a trade secret belonging to the             *
// * copyright holder.                                                  *
// **********************************************************************
//  AUTHOR:  Gig Kirk
//  DATE:    4/13/92
//  API:     NONE
//  ENVIRONMENT: ANY
//

/*
CHANGE LOG

2003.02.10  DGC
   Loading DBHandler function first tries a "default" name that doesn't include
   the dbhandler name.  Same with Genkey handler.

2003.01.27  DGC
   Made change to GenerateQualFromEntityList( ) per Don's request. Using
   "*root*" to qualify the target entity.

2002.10.20  DGC
   Added GenerateQualFromEntityList( ).

2002.07.24  DGC
   Fixed a bug reported by Don.  When loading compressed OIs, the code was not
   correctly retrieving the attrib flags from the compressed stream.

2002.05.15  DGC
   Fixed error reported by Jeff that occurred when writing an OI to a
   compressed text stream.  Null integer attributes were being sent as 0.

2002.03.28  HH
   R56268, improve error handling genkey creation failed.

2002.02.22  HH
   Reduced the stacksize used by view arrays by malloc from heap.
   This was done because VSE CICS crashed at Tonbeller site.

2002.01.10  HH
   fix for the attribute flags problem on BIG ENDIAN CPU's.

2001.12.06  DGC
   Fixed bug reported by Phil.  Commit of cluster with an unchanged OI caused
   problems.

2001.11.13  HH
   Handle database deadlock by redoing the ACTIVATE.

2001.08.30  DGC  10b
   Fixed a crash found by Matt.  When printing the View OD names for a
   warning message, we weren't printing the OD name correctly

2001.08.01  DGC  10b
   Added zOCE_STATE_MULTIPLE to activate contraints.

2001.05.18  DGC
   Made change to pessimistic locking semaphore--don't create/delete a
   semaphore if a ViewOD doesn't have locking specified for it.

2001.05.18  DGC
   Improved a diagnostic message.

2001.05.07  PAS
   Make sure that all committed OIs that use zENCODE_BLOBS and/or
   zNO_NULL_STRING_TERM have the ReleaseCUrrent value.

2001.05.06  BL   Repository
   Improve handling of view clusters.

2001.05.05  BL   Repository
   change increment zCLUSTER_VIEW_COUNT form 500 to 2000

2001.05.02  HH
   Improve handling of view clusters.

2001.04.25  DGC  Z10
   Fixed bug reported by Jeff.  We were creating an extra coorespondence
   table if an entity was flagged as created and included.

2001.04.20  DGC
   Added flag to fnValidViewAttrib( ) to allow hidden attributes.

2001.04.09  PAS
   Make sure that all committed OIs to files have at least the
   ReleaseCompat value.

2001.03.27  PAS
   Enhanced commit and activation of objects to/from files so that the files
   contain no binary characters.  The storage of string data with CRLF
   characters is changed to eliminate the trailing null terminator.  Blobs
   can now be stored encoded via the UUENCODE/UUDECODE 'standard'.

2001.04.06  DGC  10b
   Added code for entity instance tags.

2001.01.23  DGC  10b
   Fixed bug R53910 - During activate check to make sure the LOD has physical
   information.

2001.01.22  DGC  10b
   Fixed but R54414.  We now never sort dates using a context.  We always
   sort them using the internal value.

2001.01.16 US Z2000
   fnDropViewOI( ): removed the if clause that a drop is not done if it
   is a server or in the shutdown phase. Result of this if was a
   steadily increasing memory, that killed even a zeidon on a workstation
   the reason for this if clause was the very slow free of the zeidon
   memory mamagement, but this has been changed and is fast now
   So you can't see any measurable performance differences.

2000.12.05  DGC  10b
   Fixed bug R54297...sorting problem.  We should only sort dates using
   strcmp if we are retrieving the date with a context.

2000.12.01  DGC  10b
   Fix for important bug reported by Frank H.  When an entity was being
   excluded it was being flagged as updated.

2000.11.13  RG  Z2000
   Fixed again OrderEntityForView (no return without fnOperationReturn)

2000.11.09  RG/BL
   Fixed function OrderEntityForView

2000.11.01  DGC
   Fixed a bug in pessimistic locking reported by Don.  Creating the locking
   semaphore didn't check to make sure we were setting the lock twice when
   the cluster had two OI's with the same LOD.

2000.10.09  DGC
   Made change to use fnSetUpdateIndicator( ).

2000.10.09  DGC
   Added the ability to use contexts when sorting attributes.

2000.07.27  HH
   When an OI is loaded from file, compare attribute names case insensitive.

2000.07.24  DGC  Z10
   Made change to write attribs with derived functions IF they are
   persistent.

2000.07.24  DGC  Z10
   Sorting an OI with AutoSeq=Y was not setting the update flag for the OI.

2000.07.18  DGC  Z10
   Fixed bug reported by Phil/Jeff--if a root entity is included from another
   OI core should just ignore the Insert dbhandler call.

2000.07.12  DGC  Z10
   Added a new message passed to DBHandler...DBH_Object | DBH_NewObject.

2000.07.12  DGC  Z10
   Fixed problem with committing included relationships. Included relationships
   were not being committed if the entity was also created.

2000.06.30  DGC  Z10
   Removed validity checking when linking Duplicate Instances during an
   activate.  We used to make sure one of the EI's was flagged as Full Perist
   but now we don't have to because XOD build generates a cross-product of
   all the attributes for each of the entities flagged as Dup Instance.

2000.06.21  DGC  Z10
   Removed caching logic from activate.  It could be re-added so that the
   dbhandler can call it.

2000.06.19  DGC  Z10
   Fixed bug reported by HH.  fnWriteOI_ToTextStream was not correctly writing
   link cards if the linked EI was hidden.

2000.05.04  DGC  Z10
   Made changes to allow DBHandler to order an OI instead of Activate.

2000.05.04  DGC  Z10
   Change signature of LoadEntity( ).

2000.05.03  RG  Z2000
   Fixed OrderEntityForView( ): if several attributes have been separated
   by ',' we got an errormessage 'Invalid Attribute Name for LOD...'
   We have to check ',' in the attribute list

2000.04.24  DGC 10b
   Made change to commit logic.  If an entity was created in OI 'A' and
   included into OI 'B' and then B was committed, the create flag in A is
   turned off.  When A is committed the relationship between the created
   entity and it's parent is not created because the created entity has no
   incremental flag set.

   Now, when an entity is created on the DB, all linked entities that have
   the created flag on will have their included flag set on.

2000.03.03  DGC 10b
   Fixed bug TB1082.  OrderEntityForView( ) was ignoring the order attributes
   after the first one.

2000.03.03  DGC
   CreateViewCluster( ) creates a cluster that can hold 500 views.

2000.03.03  DGC
   Added code to fix bug that kept Duplicate Relationship entities from
   being spawned after an activate.

2000.02.25  DGC 10b
    Made fix to ActivateOI_FromOI_ForTask( ) that allows user to create OI from a
    system object.

2000.01.31  RG Z2000
    LOCALOPERATION --> LOCALOPER because of compiler error

2000.01.19  HH Z10
   In fnDropViewOI the link chain is cleared, even if the task is beeing
   shut down. This is done, because an object might have external links
   to another object in the main task.

2000.01.06  DGC  10a/10b
   First 2000 bugfix!  The code in CommitMultipleOIs( ) checks the OIs after
   the commit is done to see if there are any EI's that still have the created
   flag set and if it does it shows a message because there shouldn't be
   any EI's with the created flag set after a commit.  But it *is* ok if the
   entity is also flagged as deleted.  Added code to set if EI is deleted also.

2000.01.04  BL Z10 Repository
   Modified Operation fnInitializeGenKeys: No Error message when Entity has
   duplicate Instance

1999.11.29  DGC
   Added code to fnAllocDataspace( ) to help find leaks.

   Fixed bug in CommitObjectInstance( )...crashed when lpView == 0.

1999.11.27  DGC ALL
   Fixed bug in sorting--we were calling derived operations even if the
   entity was null.  We now check to make sure an entity exists before calling
    the derived oper.

1999.10.27  HH  ALL
   merged from 9J: to improve performance of sorting decimals,
   fnCompareEIAttrs is called with a new parameter, LPTASK.

1999.10.13  DGC  10a  TB772
   Fixed bug in ActivateOI_FromOI_ForTask( ). Activating with zSINGLE from an OI that
   had multiple roots activated multiple roots.  Core wasn't setting the
   hPrevTwin pointer correctly.

1999.10.08  DGC
   Modified fnCommitPreLoops to not turn off the hidden flag for dead
   attributes before call the db handler.

1999.09.24  DGC  10a
   Removed a check for the lpTask->bDebug flag when dropping an OI. This was
   causing us to perform unnecessary logic that took a long time.

1999.08.20  DGC  10a
   Fixed some bugs...implemented zWRITE_KEYS_ONLY so we could write only
   key attributes to a text stream.

1999.06.23  DGC  10a
   Fixed problem reported by FH.  fnOrderEntityForView( ) was passing the
   wrong lpViewEntity to the derived attribute functions.

   Started fixing commit problems with linked entity instances.  New logic
   uses bDBH... EI flags.

   Lot's of stuff with genkeys and FKs.  We generate genkeys and copy FK's
   at the very beginning of a cluster.

1999.06.01  DGC  10a
   Added ability to use bubble sort when sorting entities.
   Turn off attribute changed flags after commit.
   Fixed bug where integer FK were no correctly set to NULL.

1999.05.20  DGC  10a
   Changed sorting to use quicksort instead of a bubble sort.

   Added check for szER_Date for compressed OIs.  As part of this I removed
   the ability to write binary text streams.

1999.01.08  DGC
   Changed tracing of caching information to trace only when DBHandler trace
   level is at least 1.

1999.01.11  DGC
   Fixed problem reported by Frank where entities weren't being loaded when
   the activate limit was reached.

1999.01.20  DGC
   Attempted to fix Frank H's problem (TB390).

1999.02.12  DGC
   Started adding (and removing) stuff for attribute flags.

   Changed displaying of SysDiagnosticMessage( ) to show for entities that
   are *NOT* derived.

1999.03.04  DGC
   Moved some traces around.

1999.03.11  DGC
   Fixed pessimistic locking problems that occurred when using networking.
   Removed locking error message.

1999.03.15  DGC
   Don't execute commit constraints if we are only dropping pessimistic locks.

1999.03.16   DGC
   Changed logic to use lpViewEntity->lEREntTok as an ID instead of casting
   lpViewEntity (the pointer value) to a long.  I'm trying to stop using
   pointers as long integer values (for possible conversion to AS400).

1999.04.07   DGC  10a
   Fixed bug that I found--ActivateOI crashed if activate is with locking but
   activate fails for some reason.

1999.04.19   DGC  10a
   Fixed bug that I found--if an entity contains *only* an AUTOSEQ attribute
   a data stick (hRecord) doesn't get created for the entity.  The AUTOSEQ
   logic at commit-time didn't handle this.  Now it does.

*/

#include "kzoephdr.h"
#include <stdio.h>
#include <stdarg.h>
#define  Dbg 0

#if defined( _WINDOWS ) && defined( DEBUG )
#pragma optimize( "", off )
#endif

// Comment this out to keep from using attribute flags.
#define zATTRIBFLAGS       0x02000000L

// DGC 2-14-96
// Strings that contain special chars (chars with ASCII values < space [0x20] )
// need to be stored as blobs when being stored in an ASCII portable file.
// When this happens, the first byte in the portable file is the following
// byte followed by the length.  For example, the line storing the string
// "abc/nefg" would like like the following in the portable file:
//        aAttrName .7
//        abc
//        efg
// where the '.' represents the special byte.
#define zSTRING_STORED_AS_BLOB   0x1F

// PAS 03/09/2001
// We will now allow BLOBs to be stored encoded.  This is used primarily for
// Zeidon Metas stored as protable files.  A process similar to UUENCODE/UUDECODE
// is used.  Basically, every 6-bits of the blob is encoded to a character between
// 0x20 and 0x7F.  Details are in the routines:
//     UUENCODE_NextEncodedLine
//     UUDECODE_NextLineToBuffer
// The character below is used in the portable file (just like
// zSTRING_STORED_AS_BLOB) to determine if the blob needs to be decoded
// during activation.
#define zBLOB_STORED_ENCODED     'U'

zSHORT  OPERATION
UUENCODE_NextEncodedLine( zPCHAR  pchLineOut,
                          zPCHAR  pchBuffer,
                          zULONG  ulBufferLth,
                          zPULONG pulBufferPos );
zSHORT  OPERATION
UUDECODE_NextLineToBuffer( zPCHAR  pchEncodedLine,
                           zPCHAR  pchBuffer,
                           zULONG  ulBufferLth,
                           zPULONG pulBufferPos );

// Used by Write/Read stream for compressed OIs.
#define zENTITY_BUFFER_SIZE      10000

#ifndef CHAR_IS_SPECIAL
   #define CHAR_IS_SPECIAL( c ) ((c)=='\n' || (c)=='\r' || (c)=='\v' || (c)==zSTRING_STORED_AS_BLOB)
#endif

#define MAX_SEQ_ENTS 100   // Max entities with auto seq. attrs in 1 OD.
#define MAX_SEQ_ATTS  20   // Max attrs in 1 entity with auto sequencing.

#define zMAX_KEYS_FOR_LOCK   40     // Max # of keys for pess. locking.
#define zMAX_KEYLTH_FOR_LOCK 200    // Max lth of concat keys for pess. locking.

#define zCLUSTER_VIEW_COUNT  2000    // # of views a cluster can hold.

// Used to store info about OI in portable files.
#define zOI_ISLOCKED         0x00000001
#define zOI_READONLY         0x00000002

// Following structure for ActivateOI_FromFile.
typedef struct FileDataStruct FileDataRecord;
typedef FileDataRecord *LPFILEDATA;
struct FileDataStruct
{
   zPCHAR   pchFileName;
   zLONG    hFile;
   zLONG    lLine;
};

// Following structure for reading OI info from a buffer..
typedef struct BufferDataStruct
{
   zPCHAR   pchBuffer;
   zPCHAR   pchCurrentByte;
   zPCHAR   pchEnd;
} BufferDataRecord, * LPBUFFERDATA;

// Following structures for ActivateObjectInstance
typedef struct EntityCacheStruct EntityCache;
typedef EntityCache *LPENTITYCACHE;
struct EntityCacheStruct
{
   zCHAR              nIdx;
   LPENTITYINSTANCE   lpEntityInstance[ 1 ];
};

typedef struct CacheInfoStruct CacheInfo;
typedef CacheInfo *LPCACHEINFO;
struct CacheInfoStruct
{
   zCHAR   nCacheNum;
   zUSHORT usCacheSize;
   zULONG  ulCacheCount;
};

// we allocate the view array stuff on the heap rather than
//  using stack memory, because of supporting stupid CICS
typedef struct
{
   zLONG    lCount;
   zVIEW    *pvArray;
   LPVIEWOI *pViewOI_Array;
   LPVIEWOD *pViewOD_Array;
   zBOOL    *pbGenkeyNeededArray;
   zBOOL    *pbFK_NeededArray;
   zPVOID    pvDyn[ 10 ]; // used for only one view
} VIEWARRAYBLOCK;

LPATTRIBFLAGS LOCALOPER
fnGetAttribFlagsPtr( LPENTITYINSTANCE lpEntityInstance,
                     LPVIEWATTRIB     lpViewAttribute );

LPVIEWENTITYCSR LOCALOPER
fnCreateEntityCsrHandle( LPVIEWENTITYCSR lpViewEntityCsr,
                         LPVIEWCSR       lpViewCsr,
                         zSHORT          nIndex );

zSHORT LOCALOPER
fnCommitObjectInstance( LPVIEWCLUSTER lpViewCluster,
                        zVIEW         lpViewArray[],
                        zSHORT        nViewCount,
                        zPSHORT       pnViewErrorIdx,
                        LPTASK        lpCurrentTask,
                        zLONG         lControl,
                        VIEWARRAYBLOCK *pViewArrayBlock );

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

zSHORT LOCALOPER
fnCreateConcatKey( zPCHAR           pchKeyString,
                   LPENTITYINSTANCE lpEntityInstance,
                   LPVIEWATTRIB     lpKeyViewAttrib[],
                   zSHORT           nKeyCnt );

LPATTRIBFLAGS LOCALOPER
fnGetAttribFlagsPtr( LPENTITYINSTANCE lpEntityInstance,
                     LPVIEWATTRIB     lpViewAttribute );

LPENTITYINSTANCE LOCALOPER
fnFindLastEntityUnderParent( LPENTITYINSTANCE lpParent,
                             zBOOL            bUseTwin );
static zSHORT
fnInitViewArrayBlock( VIEWARRAYBLOCK *pViewArrayBlock,
                      zLONG nViewCount );
static void
fnFreeViewArrayBlock( VIEWARRAYBLOCK *pViewArrayBlock );

//  Do commit based on entity rules
#define  VIEWENT_RULES 1
#define __ACTIVATE_CONSTRAINTS__


//./ ADD NAME=ActivateEmptyObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ActivateEmptyObjectInstance
//
//  PURPOSE:    To activate an empty Object instance and return a
//              view to the object instance.
//
//  PARAMETERS: lpReturn View - View returned to instance activated
//              cpcViewOD_Name - Name of the view object.  If 0, the
//                              returned view is for the same object as
//                              the initial view(?).
//              lpAppQualView - Used to qualify the application in which
//                              to look for the object.  If the view
//                              passed is a subtask view, then the
//                              application that is used is the
//                              application tied to the subtask.
//                              Otherwise, the application for the view
//                              object associated with the passed view
//                              is used.  Note: View cannot be a subtask
//                              view when zLEVEL_SAME is specified.
//              lControl      - Controls certain aspects of the file
//                              loaded.
//                            zSINGLE   - (default) only one entity at the
//                                        root level.
//                            zMULTIPLE - multiple entities at the root
//                                        level
//
//                            zLEVEL_APPLICATION - created view is tied
//                                        to the application task,
//                                        rather than the active task.
//                            zLEVEL_SYSTEM   - created view is tied
//                                        with the system task,
//                                        rather than the active task.
//                            zLEVEL_SAME - created view is tied to the
//                                        same task as lpAppQualView.
//                                        Note: specifying this option
//                                        requires that lpAppQualView be
//                                        be specified and that it not be
//                                        a subtask view.
//                            zREADONLY - Marks the View and the Instance
//                                        as read only.  Any view created
//                                        from this view will also be
//                                        marked as read only.
//
//  RETURNS:  0           - Instance activated successfully
//            zCALL_ERROR - Error Activating object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT OPERATION
ActivateEmptyObjectInstance( zPVIEW  pvReturnView,
                             zCPCHAR cpcViewOD_Name,
                             zVIEW   lpAppQualView,
                             zLONG   lControl )
{
   LPTASK         lpCurrentTask;
   LPTASK         lpOwningTask;
   LPVIEWOD       lpViewOD;
   zVIEW          lpView;
   zLONG          l;
   zSHORT         nRC;

   // Init in case of early error
   *pvReturnView = 0;

   // If task not active or disabled, or view invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iActivateEmptyObjectInstance,
                                          lpAppQualView, zVALID_VIEW )) == 0 )
   {
      return( zCALL_ERROR );
   }

   // Verify only one zLEVEL_ option requested
   l = lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM | zLEVEL_SAME);
   if ( l && (-l & l) != l )
   {
      // error, More than one zLEVEL_ option requested
      // "KZOEE023 - Invalid parameter, "
      fnIssueCoreError( lpCurrentTask, lpAppQualView, 8, 23, 0,
                        "More than one zLEVEL_ option requested", 0 );
      fnOperationReturn( iActivateEmptyObjectInstance, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // If zLEVEL_SAME is requested
   if ( lControl & zLEVEL_SAME )
   {
      if ( lpAppQualView == 0 || lpAppQualView->hSubtask )
      {
         // "KZOEE100 - Invalid View, view is a Subtask View"
         fnIssueCoreError( lpCurrentTask, lpAppQualView, 8, 100, 0,
                           "lpAppQualView", "with zLEVEL_SAME" );
         fnOperationReturn( iActivateEmptyObjectInstance, lpCurrentTask );
         return( zCALL_ERROR );
      }
      else
      {
         LPVIEWCSR lpViewCsr;

         // Turn off the 'same' indicator
         lControl ^= zLEVEL_SAME;
         // To determine what the level is of the qualifying view
         //   1. Change lpAppQualView to point to the initial
         //      view created for the object instance
         //   2. Check for application level, if there use
         //      zLEVEL_APPLICATION.
         //   3. Check if the view task is the main task, if so use
         //      zLEVEL_SYSTEM.
         //   4. Use the task level...
         lpViewCsr = zGETPTR( lpAppQualView->hViewCsr );
         while ( lpViewCsr->hNextViewCsr )
            lpViewCsr = zGETPTR( lpViewCsr->hNextViewCsr );

         lpAppQualView = zGETPTR( lpViewCsr->hView );
         if ( lpAppQualView->bApplicationView )
            lControl |= zLEVEL_APPLICATION;
         else
         if ( lpAppQualView->hTask == AnchorBlock->hMainTask )
            lControl |= zLEVEL_SYSTEM;
      }
   }

   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
      lpOwningTask = zGETPTR( AnchorBlock->hMainTask );
   else
      lpOwningTask = lpCurrentTask;

   if ( (nRC = fnDeclareView( pvReturnView, lpOwningTask,
                              lpAppQualView, cpcViewOD_Name, 0 )) != 0 )
   {
      fnOperationReturn( iActivateEmptyObjectInstance, lpCurrentTask );
      return( nRC );
   }

#if 0
   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
   {
      zSHORT nScope = (lControl & zLEVEL_APPLICATION) ?
                                  zLEVEL_APPLICATION : zLEVEL_SYSTEM;
      if ( (nRC = SfTransferView( *pvReturnView, lpAppQualView,
                                  nScope )) != 0 )
      {
         fnOperationReturn( iActivateEmptyObjectInstance, lpCurrentTask );
         return( nRC );
      }
   }
#endif

   nRC = fnActivateEmptyObjectInstance( lpCurrentTask, *pvReturnView, lControl );
   lpView = *pvReturnView;
   lpViewOD = zGETPTR( lpView->hViewOD );
   if ( lControl & zREADONLY )
      lpView->bReadOnly = TRUE;

// TraceLine( "ActivateEmptyObjectInstance: 0x%08x   LOD: %s",
//            lpView, lpViewOD->szName );

#ifdef __ACTIVATE_CONSTRAINTS__
   if ( lpViewOD->bActivateEmptyConstraint && nRC == 0 )
   {
      zSHORT   nState;

      nState = (lControl & zLEVEL_SYSTEM) ? zOCE_STATE_SYSTEM : 0;
         if ( lControl & zMULTIPLE )
            nState |= zOCE_STATE_MULTIPLE;

      nRC = fnInvokeOCEOperation( lpView, lpCurrentTask,
                                  zOCE_ACTIVATE_EMPTY, nState );
      if ( nRC )
      {
         fnDropView( lpView );
         *pvReturnView = 0;
      }
   }
#endif

   fnOperationReturn( iActivateEmptyObjectInstance, lpCurrentTask );
   return( nRC );
}

// Remove ('resolve') all references to other views in the qualification OI.
// lpView must have object def of KZDBHQUA.
// This function is expected to be called twice, once with pchQualEntity =
// "QualAttrib" and once with pchQualEntity = "SubQualAttrib".
void
fnResolveQualOI( zVIEW vView, zPCHAR pchQualEntity )
{
   zSHORT nRC;

   for ( nRC = SetCursorFirstEntity( vView, "EntitySpec", 0 );
         nRC == zCURSOR_SET;
         nRC = SetCursorNextEntity( vView, "EntitySpec", 0 ) )
   {
      for ( nRC = SetCursorFirstEntity( vView, pchQualEntity, "EntitySpec" );
            nRC == zCURSOR_SET;
            nRC = SetCursorNextEntity( vView, pchQualEntity, "EntitySpec" ) )
      {
         zVIEW  vSourceView;
         zPCHAR pchSourceViewName;
         zPCHAR pchSourceEntityName;
         zPCHAR pchSourceAttributeName;
         zPCHAR pchOper;

         // See if QualAttrib references another view.
         GetAddrForAttribute( &pchSourceViewName, vView, pchQualEntity,
                              "SourceViewName" );
         if ( *pchSourceViewName )
            GetViewByName( &vSourceView, pchSourceViewName, vView, zLEVEL_TASK );
         else
            GetIntegerFromAttribute( (zPLONG) &vSourceView, vView,
                                     pchQualEntity, "SourceViewID" );

         // If vSourceView is 0, then the current QualAttrib doesn't reference
         // another view, so continue with the next QualAttrib.
         if ( vSourceView == 0 )
            continue;

         // Get the source entity and attribute names.
         GetAddrForAttribute( &pchSourceEntityName, vView, pchQualEntity,
                              "SourceEntityName" );
         GetAddrForAttribute( &pchSourceAttributeName, vView, pchQualEntity,
                              "SourceAttributeName" );

         // Check to see if the operation is "IS".  If it is, then we have to
         // save the key values.
         GetAddrForAttribute( &pchOper, vView, pchQualEntity, "Oper" );
         if ( zstrcmpi( pchOper, "IS" ) == 0 )
         {
            LPVIEWENTITY lpViewEntity;
            LPVIEWATTRIB lpViewAttrib;
            zVIEW        vTemp;
            zBOOL        bFirstKey = TRUE;

            // Save a copy of the current view so we can delete the QualAttrib
            // entity later.
            CreateViewFromViewForTask( &vTemp, vView, 0 );

            CreateEntity( vView, pchQualEntity, zPOS_NEXT );
            SetAttributeFromString( vView, pchQualEntity, "Oper", "(" );

            // The oper is "IS".  This means we need to replace the current
            // QualAttrib with QualAttribs to compare each key.
            lpViewEntity = MiGetViewEntityForView( vSourceView,
                                                   pchSourceEntityName );
            for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
                  lpViewAttrib;
                  lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
            {
               // We only care about keys...
               if ( lpViewAttrib->bKey == FALSE )
                  continue;

               if ( bFirstKey )
                  bFirstKey = FALSE;
               else
               {
                  CreateEntity( vView, pchQualEntity, zPOS_NEXT );
                  SetAttributeFromString( vView, pchQualEntity, "Oper", "AND" );
               }

               CreateEntity( vView, pchQualEntity, zPOS_NEXT );
               SetAttributeFromString( vView, pchQualEntity, "EntityName",
                                       pchSourceEntityName );
               SetAttributeFromString( vView, pchQualEntity, "AttributeName",
                                       lpViewAttrib->szName );
               SetAttributeFromString( vView, pchQualEntity, "Oper", "=" );
               SetAttributeFromAttribute( vView, pchQualEntity, "Value",
                                          vSourceView, pchSourceEntityName,
                                          lpViewAttrib->szName );
            } // for...

            CreateEntity( vView, pchQualEntity, zPOS_NEXT );
            SetAttributeFromString( vView, pchQualEntity, "Oper", ")" );

            DeleteEntity( vTemp, pchQualEntity, zREPOS_NONE );
            DropView( vTemp );

            // We've done all that needs to be done, so process the next
            // qual entity.
            continue;

         } // if ( zstrcmpi( pchOper, "IS" )...

         // Copy attribute value from the source view to the qual view.
         SetAttributeFromAttribute( vView, pchQualEntity, "Value",
                                    vSourceView, pchSourceEntityName,
                                    pchSourceAttributeName );

         // Set the qual attrib to be null.
         SetAttributeFromString( vView, pchQualEntity, "SourceViewName", "" );
         SetAttributeFromInteger( vView, pchQualEntity, "SourceViewID", 0 );
         SetAttributeFromString( vView, pchQualEntity, "SourceEntityName", "" );
         SetAttributeFromString( vView, pchQualEntity, "SourceAttributeName", "" );

      } // for each pchQualEntity...

   } // for each "EntitySpec"...

} // fnResolveQualOI

zSHORT LOCALOPER
fnSetLockingAttributes( LPTASK          lpCurrentTask,
                        zVIEW           vLock,
                        LPVIEWENTITY    lpLockEntity,
                        LPVIEWENTITYCSR lpLockEntityCsr,
                        zPCHAR          pchLOD_Name,
                        zPCHAR          pchKeyString,
                        zBOOL           bSetUserName,
                        zBOOL           bSetTimestamp,
                        zPCHAR          pchAllowRead )
{
   LPVIEWATTRIB lpViewAttrib;
   zSHORT       nCnt = 0;

   // Loop through each of the attributes in the lock OI.  When we find
   // one we want set it.  To keep us from looping unnecessarily we keep
   // track of the # of attributes we set.  When we get to 5 we're done.
   for ( lpViewAttrib = zGETPTR( lpLockEntity->hFirstOD_Attrib );
         lpViewAttrib && nCnt < 5;
         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
   {
      if ( zstrcmp( lpViewAttrib->szName, "LOD_Name" ) == 0 )
      {
         nCnt++;

         if ( pchLOD_Name &&
              fnSetAttributeFromVariable( vLock, lpLockEntityCsr,
                                          lpViewAttrib,
                                          (zPVOID) pchLOD_Name, 'S', 0, 0,
                                          lpCurrentTask, 0 ) != 0 )
         {
            return( zCALL_ERROR ); // error setting attribute
         }
      }
      else
      if ( zstrcmp( lpViewAttrib->szName, "KeyValue" ) == 0 )
      {
         nCnt++;

         if ( fnSetAttributeFromVariable( vLock, lpLockEntityCsr,
                                          lpViewAttrib,
                                          (zPVOID) pchKeyString, 'S',
                                          0, 0, lpCurrentTask, 0 ) != 0 )
         {
            return( zCALL_ERROR ); // error setting attribute
         }
      }
      else
      if ( zstrcmp( lpViewAttrib->szName, "UserName" ) == 0 )
      {
         nCnt++;

         if ( bSetUserName )
         {
            zCHAR szUserName[ zZEIDON_NAME_LTH + 1 ];
            zCHAR szPassword[ zZEIDON_NAME_LTH + 1 ];

            SysGetUserID( vLock, szUserName, zsizeof( szUserName ), szPassword, zsizeof( szPassword ) );
            if ( fnSetAttributeFromVariable( vLock, lpLockEntityCsr,
                                             lpViewAttrib,
                                             (zPVOID) szUserName, 'S',
                                             0, 0, lpCurrentTask, 0 ) != 0 )
            {
               return( zCALL_ERROR ); // error setting attribute
            }
         }
      }
      else
      if ( zstrcmp( lpViewAttrib->szName, "Timestamp" ) == 0 )
      {
         nCnt++;

         if ( bSetTimestamp )
         {
            zCHAR szDateTime[ 30 ];

            SysGetDateTime( szDateTime, zsizeof( szDateTime ) );
            if ( fnSetAttributeFromVariable( vLock, lpLockEntityCsr,
                                             lpViewAttrib,
                                             (zPVOID) szDateTime, 'S',
                                             0, 0, lpCurrentTask, 0 ) != 0 )
            {
               return( zCALL_ERROR ); // error setting attribute
            }
         }
      }
      else
      if ( zstrcmp( lpViewAttrib->szName, "AllowRead" ) == 0 )
      {
         nCnt++;

         if ( pchAllowRead &&
              fnSetAttributeFromVariable( vLock, lpLockEntityCsr,
                                          lpViewAttrib,
                                          (zPVOID) pchAllowRead, 'S',
                                          0, 0, lpCurrentTask, 0 ) != 0 )
         {
            return( zCALL_ERROR ); // error setting attribute
         }
      }

   } // for each lpViewAttrib...

   return( 0 );

} // fnSetLockingAttributes

/*
   Creates the locking semaphore for pessimistic locks.  lpArray[] is either
   an array of views (if vSubtask = 0) or an array of lpViewODs (if vSubtask
   != 0).

   Returns :  0 - Semaphore created OK.
              1 - Semaphore not needed.
              zCALL_ERROR.
*/
zSHORT LOCALOPER
fnCreatePessimisticSemaphore( LPTASK   lpCurrentTask,
                              zPVOID   lpArray[],
                              zSHORT   nViewCount,
                              zPSHORT  pnViewErrorIdx,
                              zVIEW    vSubtask )
{
   ViewClusterRecord vLock;
   LPVIEWENTITY      lpLockEntity;
   LPVIEWENTITYCSR   lpLockEntityCsr;
   LPENTITYINSTANCE  lpEntityInstance;
   LPVIEWCLUSTER     lpViewCluster;
   VIEWARRAYBLOCK    tViewArrayBlock = { 0 };
   zCHAR             szLockName[ 50 ];
   zBOOL             bGlobalLockCreated = FALSE;
   zBOOL             bArrayIsViewList;
   zBOOL             bMutexLocked = FALSE;
   zBOOL             bCreateSemaphore;
   zSHORT            nCommit;
   zSHORT            k;
   zSHORT            nRC = zCALL_ERROR;

   vLock.vOI = 0;
   vLock.lControl = 0;

   if ( vSubtask == 0 )
   {
      bArrayIsViewList = TRUE;
      lpViewCluster = (LPVIEWCLUSTER) lpArray;

      // vSubtask is just the first valid view in the list.
      for ( k = 0; k < nViewCount; k++ )
      {
         if ( lpViewCluster[ k ].vOI )
         {
            vSubtask = lpViewCluster[ k ].vOI;
            break;
         }
      }
   }
   else
      bArrayIsViewList = FALSE;

   // Create an empty lock OI.
   if ( fnDeclareView( &vLock.vOI, lpCurrentTask, vSubtask, "ZPLOCKO", 0 ) != 0 )
      return( zCALL_ERROR );

   if ( fnActivateEmptyObjectInstance( lpCurrentTask, vLock.vOI, zMULTIPLE ) != 0 )
      return( zCALL_ERROR );

   // It's possible that the user wants to keep the locks for all the views.
   // Following flag is TRUE if there is a least one lock.
   bCreateSemaphore = FALSE;

   // Loop through all the views and set a lock.
   for ( k = 0; k < nViewCount; k++ )
   {
      LPVIEWOD lpViewOD;

      if ( bArrayIsViewList )
      {
         if ( lpViewCluster[ k ].vOI == 0 )
            continue;

         // If we're keeping locks on this guy then skip him.
         if ( lpViewCluster[ k ].lControl & zCOMMIT_KEEPLOCKS )
            continue;

         // Get ViewOD from view.
         lpViewOD = zGETPTR( lpViewCluster[ k ].vOI->hViewOD );
      }
      else
      {
         if ( lpArray[ k ] == 0 )
            continue;

         lpViewOD = (LPVIEWOD) lpArray[ k ];
      }

      // If this ViewOD doesn't have any locking (which is possible if we're
      // committing a cluster) then we can skip it.
      if ( lpViewOD->nLock       < zLL_PESSIMISTIC &&
           lpViewOD->nEntityLock < zLL_PESSIMISTIC )
      {
         continue;
      }

      bCreateSemaphore = TRUE;

      // Set lock name.  If OD does not have pessimistic locking at the entity
      // level then it's safe to lock out other users trying to lock the same
      // OD.  This allows us to use the entity name for the locking semaphore.
      // If the OD has entity locking we need to use a "global" entity locking
      // semaphore so that no one can lock entities at the same time.
      if ( lpViewOD->nEntityLock )
      {
         // If we've already created the global lock entity just continue.
         if ( bGlobalLockCreated )
            continue;

         bGlobalLockCreated = TRUE;

         // We are using entity level locking.
         strcpy_s( szLockName, zsizeof( szLockName ), "#Global Entity Lock" );
      }
      else
         // We are not using entity level locking so we can just lock out other
         // users using the same LOD.  We prefix the name with a '#' to to
         // indicate that this is the locking semaphore.
         sprintf_s( szLockName, zsizeof( szLockName ), "#%s", lpViewOD->szName );

      // Check to make sure we're not already setting the lock for this type.
      if ( SetCursorFirstEntityByString( vLock.vOI, "ZeidonLock", "LOD_Name",
                                         szLockName, 0 ) >= zCURSOR_SET )
      {
         continue;
      }

      // Get the lpViewEntity and lpLockEntityCsr for the lock OI.
      lpLockEntity = fnValidViewEntity( &lpLockEntityCsr, vLock.vOI, "ZeidonLock", 0 );

      if ( fnCreateEntity( vLock.vOI, lpLockEntity, lpLockEntityCsr,
                           zPOS_LAST, FALSE ) != 0 )
      {
         goto EndOfFunction;
      }

      // fnCreateEntity DOES NOT set the bCreated flag so set it.
      lpEntityInstance = zGETPTR( lpLockEntityCsr->hEntityInstance );
      lpEntityInstance->u.nInd.bCreated = TRUE;

      // Set entity name and key string (which is just a description).
      if ( fnSetLockingAttributes( lpCurrentTask,
                                   vLock.vOI, lpLockEntity, lpLockEntityCsr,
                                   szLockName, "Locking semaphore",
                                   TRUE, TRUE, "N" ) != 0 )
         goto EndOfFunction;

   } // for ( k... )...

   // If we didn't find any views that needed to drop their locks then get out.
   if ( bCreateSemaphore == FALSE )
      return( 1 );

   // Now lock the pessimistic semaphore.  This will hopefully single-thread
   // creation of the semaphore.  It doesn't really do anything if we are
   // running as simple client-server.
   zLOCK_MUTEX( zMUTEX_PESSIMISTICLOCK );
   bMutexLocked = TRUE;

   // Now commit the lock OI.  This should set the semaphore lock.  We'll try
   // a few times before giving up.
   if ( fnInitViewArrayBlock( &tViewArrayBlock, 1 ) != 0 )
      goto EndOfFunction;

   for ( k = 0; k < 10; k++ )
   {
      // Try committing the semaphore.  If the return code indicates that
      // we have a duplicate root then somebody else is working with the
      // lock object so try again.
      nCommit = fnCommitObjectInstance( &vLock, &vLock.vOI, 1, 0,
                                        lpCurrentTask, 0, &tViewArrayBlock );
      if ( nCommit == 0 )
         break;               // Everything OK.

      if ( nCommit == zDUPLICATE_ROOT )
      {
         SysWait( 1000 );     // Wait a second.
         continue;            // Try again.
      }

      // Oops--there must be something wrong.  Get out.
      goto EndOfFunction;
   }

   // If nCommit isn't 0 then we had problems trying to write the semaphore
   // record.  Show error and get out.
   if ( nCommit )
   {
      fnSysMessageBox( lpCurrentTask, szlOE_SystemError,
                       "Waited too long to write pessimistic lock semaphore", 1 );
      goto EndOfFunction;
   }

   // Set flag indicating that current task has written locking semaphore.
   lpCurrentTask->bPessimisticLockingSet = TRUE;

   // If we get here everything's OK.
   nRC = 0;

EndOfFunction:
   // If something went wrong then unlock the mutex.
   if ( nRC && bMutexLocked )
      zUNLOCK_MUTEX( zMUTEX_PESSIMISTICLOCK );

   if ( vLock.vOI )
      fnDropView( vLock.vOI );

   fnFreeViewArrayBlock( &tViewArrayBlock );

   if ( nRC == zCALL_ERROR && pnViewErrorIdx )
      *pnViewErrorIdx = k;

   return( nRC );

} // fnCreatePessimisticSemaphore

zSHORT LOCALOPER
fnDeletePessimisticSemaphore( LPTASK   lpCurrentTask,
                              zPVOID   lpArray[],
                              zSHORT   nViewCount,
                              zPSHORT  pnViewErrorIdx,
                              zVIEW    vSubtask )
{
   ViewClusterRecord vLock;
   zCHAR             szLockName[ 50 ];
   LPVIEWENTITY      lpLockEntity;
   LPVIEWENTITYCSR   lpLockEntityCsr;
   LPENTITYINSTANCE  lpEntityInstance;
   LPVIEWCLUSTER     lpViewCluster;
   VIEWARRAYBLOCK    tViewArrayBlock = {0};
   zBOOL             bArrayIsViewList;
   zSHORT            k;
   zSHORT            nRC = zCALL_ERROR;

   vLock.vOI = 0;
   vLock.lControl = 0;

   if ( vSubtask == 0 )
   {
      bArrayIsViewList = TRUE;
      lpViewCluster = (LPVIEWCLUSTER) lpArray;

      // vSubtask is just the first valid view in the list.
      for ( k = 0; k < nViewCount; k++ )
      {
         if ( lpViewCluster[ k ].vOI )
         {
            vSubtask = lpViewCluster[ k ].vOI;
            break;
         }
      }
   }
   else
      bArrayIsViewList = FALSE;

   // Create an empty lock OI.
   if ( fnDeclareView( &vLock.vOI, lpCurrentTask, vSubtask, "ZPLOCKO", 0 ) != 0 )
      return( zCALL_ERROR );

   if ( fnActivateEmptyObjectInstance( lpCurrentTask, vLock.vOI, zMULTIPLE ) != 0 )
      return( zCALL_ERROR );

   for ( k = 0; k < nViewCount; k++ )
   {
      LPVIEWOD lpViewOD;

      if ( bArrayIsViewList )
      {
         if ( lpViewCluster[ k ].vOI == 0 )
            continue;

         // If we're keeping locks on this guy then skip him.
         if ( lpViewCluster[ k ].lControl & zCOMMIT_KEEPLOCKS )
            continue;

         // Get ViewOD from view.
         lpViewOD = zGETPTR( lpViewCluster[ k ].vOI->hViewOD );
      }
      else
      {
         if ( lpArray[ k ] == 0 )
            continue;

         lpViewOD = (LPVIEWOD) lpArray[ k ];
      }

      // If this ViewOD doesn't have any locking (which is possible if we're
      // committing a cluster) then we can skip it.
      if ( lpViewOD->nLock       < zLL_PESSIMISTIC &&
           lpViewOD->nEntityLock < zLL_PESSIMISTIC )
      {
         continue;
      }

      // Set lock name.  If OD does not have pessimistic locking at the entity
      // level then it's safe to lock out other users trying to lock the same
      // OD.  This allows us to use the entity name for the locking semaphore.
      // If the OD has entity locking we need to use a "global" entity locking
      // semaphore so that no one can lock entities at the same time.
      if ( lpViewOD->nEntityLock )
      {
         // We are using entity level locking.
         strcpy_s( szLockName, zsizeof( szLockName ), "#Global Entity Lock" );
      }
      else
      {
         // We are not using entity level locking so we can just lock out other
         // users using the same LOD.  We prefix the name with a '#' to to
         // indicate that this is the locking semaphore.
         sprintf_s( szLockName, zsizeof( szLockName ), "#%s", lpViewOD->szName );
      }

      // Get the lpViewEntity and lpLockEntityCsr for the lock OI.
      lpLockEntity = fnValidViewEntity( &lpLockEntityCsr, vLock.vOI,
                                        "ZeidonLock", 0 );

      if ( fnCreateEntity( vLock.vOI, lpLockEntity, lpLockEntityCsr,
                           zPOS_LAST, FALSE ) != 0 )
      {
         goto EndOfFunction;
      }

      // Set entity name and key string (which is just a description).
      if ( fnSetLockingAttributes( lpCurrentTask,
                                   vLock.vOI, lpLockEntity, lpLockEntityCsr,
                                   szLockName, "Locking semaphore",
                                   0, 0, 0 ) != 0 )
      {
         goto EndOfFunction;
      }

      // Here's where we cheat -- turn off Create flag and turn on the
      // Delete/Hidden flags so that when we commit the OI the locking
      // records will be deleted.
      lpEntityInstance = zGETPTR( lpLockEntityCsr->hEntityInstance );
      lpEntityInstance->u.nInd.bCreated = FALSE;
      lpEntityInstance->u.nInd.bDeleted = TRUE;
      lpEntityInstance->u.nInd.bHidden = TRUE;
   }

   // Set flag indicating that current task no longer has a locking semaphore.
   lpCurrentTask->bPessimisticLockingSet = FALSE;

   // Now commit the lock OI.  This should release the semaphore lock.
   if ( fnInitViewArrayBlock( &tViewArrayBlock, 1 ) != 0 )
      goto EndOfFunction;

   if ( fnCommitObjectInstance( &vLock, &vLock.vOI, 1, 0, lpCurrentTask,
                                0, &tViewArrayBlock ) != 0 )
   {
      goto EndOfFunction;
   }

   // If we get here everything's OK.
   nRC = 0;

EndOfFunction:
   zUNLOCK_MUTEX( zMUTEX_PESSIMISTICLOCK );

   if ( vLock.vOI )
      fnDropView( vLock.vOI );

   fnFreeViewArrayBlock( &tViewArrayBlock );

   if ( nRC == zCALL_ERROR && pnViewErrorIdx )
      *pnViewErrorIdx = k;

   return( nRC );

} // fnDeletePessimisticSemaphore

//./ ADD NAME=fnRelinkObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:   fnRelinkObjectInstance
//
//  PURPOSE: Attempt to relink instances for
//           all entity types marked as dup instance and then attempt to
//           reinclude any instances which have duplicate relationships
//
//  PARAMETERS: lpView - View to relink.
//
//  RETURNS:   0 - No relinking done.
//             1 - Relinking attempted but nothing done.
//             2 - At least one entity instance relinked.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT LOCALOPER
fnRelinkObjectInstance( zVIEW lpView )
{
   LPVIEWENTITY      lpViewEntity;
   LPVIEWOD          lpViewOD;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;
   LPENTITYINSTANCE  lpRootInstance;
   LPENTITYINSTANCE  lpEntityInstance;
   LPENTITYINSTANCE  lpSearchInstance;
   zSHORT            nRC = 0;

   lpViewOD       = zGETPTR( lpView->hViewOD );
   lpViewCsr      = zGETPTR( lpView->hViewCsr );
   lpViewOI       = zGETPTR( lpViewCsr->hViewOI );
   lpRootInstance = zGETPTR( lpViewOI->hRootEntityInstance );

   if ( lpRootInstance == 0 )
      return( 0 );

   // If the object definition has view entities marked as
   // has dup instance, go through and attempt to relink them
   // together now
   if ( lpViewOD->bHasDupInstance )
   {
      LPENTITYINSTANCE lpDupEntityInstance = 0;

      if ( nRC == 0 )
         nRC = 1;

      // Look for EI's that are flagged as duplicate instances and link
      // together the same instances.  We will start looping with the first
      // EI and see if it is the same as any PREVIOUS EI's.  If we find a
      // match then they will be linked.
      for ( lpEntityInstance = lpRootInstance;
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // If this EI isn't a duplicate entity then skip it.
         if ( lpViewEntity->bDupInstance == FALSE )
            continue;

         // To save some looping time we'll keep track of the first EI that
         // is flagged as a dup instance.
         if ( lpDupEntityInstance == 0 )
            lpDupEntityInstance = lpEntityInstance;

         // Now try to find the first EI that matches lpEntityInstance.  If
         // lpSearchInstance == lpEntityInstance then we've searched all the
         // previous EIs so we can stop looking.
         for ( lpSearchInstance = lpDupEntityInstance;
               lpSearchInstance != lpEntityInstance;
               lpSearchInstance = zGETPTR( lpSearchInstance->hNextHier ) )
         {
            LPVIEWENTITY lpSearchViewEntity;

            lpSearchViewEntity = zGETPTR( lpSearchInstance->hViewEntity );

            // If the entities are not the same ER entity then we can't link.
            if ( lpViewEntity->lEREntTok != lpSearchViewEntity->lEREntTok )
               continue;

            // The search view entity must be flagged as duplicate instance.
            if ( lpSearchViewEntity->bDupInstance == FALSE )
               continue;

            if ( !fnInstanceKeysMatch( lpEntityInstance, lpSearchInstance ) )
               continue;

            fnRelinkInstanceToInstance( lpEntityInstance, lpSearchInstance );

            // We found a match for the current lpEntityInstance so stop
            // looking for more matches.
            break;

         } // for ( lpSearchInstance...)

      } // for ( lpEntityInstance...)

   } // if ( lpViewOD->bHasDupInstance )...

   // if the view object has duplicate relationships, try and
   // spawn any necessary includes to instantiate the relationships
   if ( lpViewOD->bHasDupRel )
   {
      if ( nRC == 0 )
         nRC = 1;

      // Loop through the view entities and look for entities that are
      // flagged as dup relationships.
      for ( lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
            lpViewEntity;
            lpViewEntity = zGETPTR( lpViewEntity->hNextHier ) )
      {
         LPVIEWENTITY      hDupRelParent;
         LPENTITYINSTANCE  lpParentInstance;

         if ( lpViewEntity->bDupRel == FALSE )
            continue;

         // Get the parent entity of the dup rel entity.  Then we will loop
         // through all the the EI's looking for instances of the parent.
         hDupRelParent = lpViewEntity->hParent;
         for ( lpParentInstance = lpRootInstance;
               lpParentInstance;
               lpParentInstance = zGETPTR( lpParentInstance->hNextHier ) )
         {
            LPENTITYINSTANCE lpSearchInstance;
            LPENTITYINSTANCE lpSourceInstance;

            if ( lpParentInstance->hViewEntity != hDupRelParent )
               continue;

            // We have found an an entity instance that is the parent of the
            // dup rel entity.  Now we have to check to see if we should
            // include another entity instance under the parent.  Look to
            // see if there is another EI in the OI who's relationship
            // matches the dup rel entity.
            for ( lpSearchInstance = lpRootInstance;
                  lpSearchInstance;
                  lpSearchInstance = zGETPTR( lpSearchInstance->hNextHier ) )
            {
               LPVIEWENTITY    lpSourceEntity;
               LPVIEWENTITYCSR lpViewEntityCsr;

               lpSourceEntity = zGETPTR( lpSearchInstance->hViewEntity );

               // If the relationship token of the source instance does not
               // match the token of the dup rel entity then try the next one.
               if ( lpSourceEntity->lERRelTok != lpViewEntity->lERRelTok )
                  continue;

               // Make sure the source entity is not derived or dup rel itself.
               if ( lpSourceEntity->bDerivedPath || lpSourceEntity->bDupRelPath )
                  continue;

               // Check to see if the relationship of the search instance is
               // the same or the inverse of lpViewEntity.
               if ( lpSourceEntity->lEREntTok == lpViewEntity->lEREntTok )
               {
                  // If we get here then the following is an example of the
                  // situation:
                  //
                  //     (R)
                  //      |
                  //     (A)
                  //    /  \
                  //  (X)  (B)
                  //   |    |
                  //  (Y)  (X')
                  //        |
                  //       (Y')
                  //
                  // Y' is the dup rel entity (lpViewEntity) and X' is the
                  // parent (lpParent).  Y is the current lpSearchInstance and
                  // is the entity that we want to include under X'.  In this
                  // case we want to make sure that the values of the keys for
                  // X and X' are the same.
                  if ( !fnInstanceKeysMatch( lpParentInstance,
                                             zGETPTR( lpSearchInstance->hParent ) ) )
                  {
                     // Keys don't match so it's not a candidate.  Try again
                     // with the next instance.
                     continue;
                  }

                  // Source for the include is Y (lpSearchInstance).
                  lpSourceInstance = lpSearchInstance;
               }
               else
               {
                  // If we get here then the following is an example of the
                  // situation:
                  //
                  //                       (R)
                  //                        |
                  //                       (A)
                  //                      /  \
                  //  X and Y are  ==>  (Y)  (B)
                  //  inversed           |    |
                  //  from above   ==>  (X)  (X')
                  //                          |
                  //                         (Y')
                  //
                  // Y' is the dup rel entity (lpViewEntity) and X' is the
                  // parent (lpParent).  X is the current lpSearchInstance.
                  // The entity that we want to include under X' is the
                  // parent of X -- Y.  Make sure X and X' are the same.
                  if ( !fnInstanceKeysMatch( lpParentInstance,
                                             lpSearchInstance ) )
                  {
                     // Keys don't match so it's not a candidate.  Try again
                     // with the next instance.
                     continue;
                  }

                  // The source of the include is the parent of X.
                  lpSourceInstance = zGETPTR( lpSearchInstance->hParent );
                  lpSourceEntity   = zGETPTR( lpSourceInstance->hViewEntity );
               }

               // We have found a match!  First establish the cursor positions
               // to match our parent and source instances.
               lpViewEntityCsr = zGETPTR( lpViewCsr->hFirstOD_EntityCsr );
               lpViewEntityCsr += (lpViewEntity->nHierNbr - 1);
               lpViewEntityCsr = zGETPTR( lpViewEntityCsr->hParent );
               fnEstablishViewForInstance( lpView, lpViewEntityCsr,
                                           lpParentInstance );

               lpViewEntityCsr = zGETPTR( lpViewCsr->hFirstOD_EntityCsr );
               lpViewEntityCsr += (lpSourceEntity->nHierNbr - 1);
               fnEstablishViewForInstance( lpView, lpViewEntityCsr,
                                           lpSourceInstance );

               // Include the source instance to instantiate the dup rel entity.
               if ( fnIncludeSubobjectFromSubobject( lpView, lpViewEntity,
                                                     lpView, lpSourceEntity,
                                                     zPOS_FIRST, 0,
                                                     0 ) == zCALL_ERROR )
               {
                  return( zCALL_ERROR );
               }

               // We've found the source instance and included it so we're
               // done looking for a source instance to include so break.
               //break;

            } // for ( lpSearchInstance )...

         } // for ( lpParentInstance )...

      } // for ( lpViewEntity...)

   } // if ( lpViewOD->bHasDupRel )...

   return( nRC );

} // fnRelinkObjectInstance

//./ ADD NAME=ActivateObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:   ActivateObjectInstance
//
//  PURPOSE: To activate an Object instance and return a view to the
//           object instance.
//
//  PARAMETERS: pvReturnView  - View returned to instance activated
//              cpcViewOD_Name - Name of the view object.  If 0, the
//                              returned view is for the same object as
//                              the initial view(?).
//              lpAppQualView - Used to qualify the application in which
//                              to look for the object.  If the view
//                              passed is a subtask view, then the
//                              application that is used is the
//                              application tied to the subtask.
//                              Otherwise, the application for the view
//                              object associated with the passed view
//                              is used.
//              lpQualView    - View qualifying what object instance to load.
//              lControl      - Controls certain aspects of the file loaded.
//                            zSINGLE   - (default) only one entity at the
//                                        root level.
//                            zMULTIPLE - multiple entities at the root
//                                        level
//                            zLEVEL_APPLICATION - created view is tied
//                                        to the application task,
//                                        rather than the active task.
//                            zLEVEL_SYSTEM - created view is tied
//                                        with the system task,
//                                        rather than the active task.
//                            zLEVEL_SAME - created view is tied to the
//                                        same task as lpAppQualView.
//                                        Note: specifying this option
//                                        requires that lpAppQualView be
//                                        be specified and that it not be
//                                        a subtask view.
//                            zACTIVATE_ROOTONLY - Activate only the root
//                                        level entity(ies).
//                            zNOENQUEUE- Do not activate the enqueue
//                                        handler as part of activate. Note
//                                        that this is implied by readonly
//                                        as well!
//                            zREADONLY - Marks the View and the Instance
//                                        as read only.  Any view created
//                                        from this view will also be
//                                        marked as read only.
//                            zSINGLE_FOR_UPDATE - Used when activating OIs
//                                        with locking.  This flag specifies
//                                        that locking should be used.
//                            zACTIVATE_CONTINUE - Continue's an activate
//                                        from a previous activate call.
//                                        Assumes that root entity has seq.
//                                        attributes and that lpView is a
//                                        valid view pointing to the current
//                                        OI.  Cursor position is set to the
//                                        last of the original entities.
//
//  RETURNS:   -1 - No instance found matching lpQualView; pvReturnView
//                  is a view to an empty object instance.
//              0 - Object instance activated, single root found
//              1 - Object instance activated, multiple roots found.  If
//                  zSINGLE was specified, only the first was activated.
//              2 - Object was loaded OK but not all entities were loaded
//                  because of Activate Limit contstraints.
//    zDB_UNAVAIL - Database is in exclusive use by another user.
//    zCONSTRAINT_VIOLATION - Activate constraint violation
//    zCALL_ERROR - Error Activating object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 6
zSHORT OPERATION
ActivateObjectInstance( zPVIEW  pvReturnView,
                        zCPCHAR cpcViewOD_Name,
                        zVIEW   lpAppQualView,
                        zVIEW   lpQualView,
                        zLONG   lControl )
{
   LPTASK            lpCurrentTask;
   LPTASK            lpOwningTask;
   LPVIEWOD          lpViewOD;
   LPVIEWOI          lpViewOI = 0;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWCSR         lpViewCsr;
   LPENTITYINSTANCE  lpOrigInstance;
   LPVIEWENTITYCSR   lpOrigViewEntityCsr;
   zVIEW             lpView = 0;
   zVIEW             vTempQual = 0;
   zVIEW             vOrigView = *pvReturnView;
   zLONG             lTickCount;
   zLONG             l;
   zBOOL             bDropQual = FALSE;   // used when continuing an activate
   zBOOL             bLockingSemaphoreCreatedHere = FALSE;
   zSHORT            nRC = zCALL_ERROR;

   *pvReturnView = 0;
   if ( AnchorBlock->TraceFlags.bOI_Times )
      lTickCount = SysGetTickCount( );

   // If task not active or disabled, return zCALL_ERROR.
   if ( lpAppQualView )
      lpView = lpAppQualView;

   if ( (lpCurrentTask = fnOperationCall( iActivateObjectInstance,
                                          lpView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   lpCurrentTask->bLoadAllocLimit = FALSE;
   if ( lpQualView && fnValidViewObject( lpCurrentTask, lpQualView ) == 0 )
      goto EndOfFunction;

   if ( fnValidView( lpCurrentTask, lpAppQualView ) == 0 )
      goto EndOfFunction;

   lpViewOD = ActivateViewObject( lpAppQualView, cpcViewOD_Name, FALSE );
   if ( lpViewOD == 0 )
      goto EndOfFunction;

   // Verify only one zLEVEL_ option requested.
   l = lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM | zLEVEL_SAME);
   if ( l && (-l & l) != l )
   {
      // error, More than one zLEVEL_ option requested
      // "KZOEE023 - Invalid parameter, "
      fnIssueCoreError( lpCurrentTask, lpView, 8, 23, 0,
                        "More than one zLEVEL_ option requested", 0 );
      goto EndOfFunction;
   }

   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
      lpOwningTask = zGETPTR( AnchorBlock->hMainTask );
   else
      lpOwningTask = lpCurrentTask;

   // If zLEVEL_SAME is requested.
   if ( lControl & zLEVEL_SAME )
   {
      if ( lpAppQualView == 0 || lpAppQualView->hSubtask )
      {
         // "KZOEE100 - Invalid View, view is a Subtask View"
         fnIssueCoreError( lpCurrentTask, lpView, 8, 100, 0, "lpAppQualView",
                           "with zLEVEL_SAME" );
         goto EndOfFunction;
      }
      else
      {
         // LPVIEWCSR lpViewCsr;

         // Turn off the 'same' indicator
         lControl ^= zLEVEL_SAME;
         // To determine what the level is of the qualifying view
         //   1. Change lpAppQualView to point to the initial
         //      view created for the object instance
         //   2. Check for application level, if there use
         //      zLEVEL_APPLICATION.
         //   3. Check if the view task is the main task, if so use
         //      zLEVEL_SYSTEM.
         //   4. Use the task level...
         lpViewCsr = zGETPTR( lpAppQualView->hViewCsr );
         while ( lpViewCsr->hNextViewCsr )
            lpViewCsr = zGETPTR( lpViewCsr->hNextViewCsr );

         lpAppQualView = zGETPTR( lpViewCsr->hView );
         if ( lpAppQualView->bApplicationView )
            lControl |= zLEVEL_APPLICATION;
         else
         if ( lpAppQualView->hTask == AnchorBlock->hMainTask )
            lControl |= zLEVEL_SYSTEM;
      }
   }

   // Check to see if we are continuing a previous activate.  If we are, then
   // we need to activate the next group of entities from the database.  To
   // do this we need to add to the current qualification view information to
   // load only entities that come after the last entity in the current OI.
   // The new qualification will then logically look like:
   //       ACTIVATE view
   //       WHERE (original-qual) AND
   //             (view.ent.seq-attr1 > lastent.ent.seq-attr1 OR
   //              (view.ent.seq-attr1 = lastent.ent.seq-attr1 AND
   //               view.ent.seq-attr2 > lastent.ent.seq-attr2))
   if ( lControl & zACTIVATE_CONTINUE )
   {
      LPVIEWATTRIB     lpViewAttrib;
      LPVIEWATTRIB     lpSeqViewAttrib[ MAX_SEQ_ATTS + 1 ];
      LPVIEWCSR        lpOrigViewCsr;
      LPVIEWOI         lpOrigViewOI;
      zCHAR            chCurrentAttrNbr;
      zCHAR            chMaxAttrNbr;
      zCHAR            chFirstAttrNbr;

      // Since we are continuing a previous activate, they had better pass
      // us the old view.
      if ( fnValidView( lpCurrentTask, vOrigView ) == 0 )
         goto EndOfFunction;

      *pvReturnView = vOrigView;
      lpOrigViewCsr = zGETPTR( vOrigView->hViewCsr );
      lpOrigViewOI  = zGETPTR( lpOrigViewCsr->hViewOI );
      if ( lpOrigViewOI == 0 || lpOrigViewOI->hRootEntityInstance == 0  )
      {
         fnSysMessageBox( lpCurrentTask, szlOE_SystemError,
                          "Expecting valid OI for zACTIVATE_CONTINUE", 1 );
         goto EndOfFunction;
      }

      // Get the root view entity.
      lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );

      // Null out table for now.
      for ( chCurrentAttrNbr = 0;
            chCurrentAttrNbr <= MAX_SEQ_ATTS;
            chCurrentAttrNbr++ )
      {
         lpSeqViewAttrib[ chCurrentAttrNbr ] = 0;
      }

      // First find the max cSequencing numbers for persistent attributes.
      chMaxAttrNbr = 0;
      for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
            lpViewAttrib;
            lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
      {
         if ( lpViewAttrib->cSequencing == 0 )
            continue;

         lpSeqViewAttrib[ lpViewAttrib->cSequencing ] = lpViewAttrib;

         if ( lpViewAttrib->cSequencing > chMaxAttrNbr )
            chMaxAttrNbr = lpViewAttrib->cSequencing;
      }

      if ( chMaxAttrNbr == 0 )
      {
         fnSysMessageBox( lpCurrentTask, szlOE_SystemError,
                          "Root entity has no default sequencing attributes",
                          1 );
         goto EndOfFunction;
      }

      // We need to add information to the qualification object.  If they
      // didn't give us one, then we need to create one.  We also need to set
      // the flag that indcates we will need to drop the qualification object
      // later.
      bDropQual = TRUE;
      if ( lpQualView == 0 )
      {
         SfActivateSysEmptyOI( &lpQualView, "kzdbhqua",
                               lpAppQualView, zMULTIPLE );
      }
      else
         ActivateOI_FromOI_ForTask( &lpQualView, lpQualView, 0, zMULTIPLE );

      // We need to find the last root instance of the original OI.
      for ( lpOrigInstance = zGETPTR( lpOrigViewOI->hRootEntityInstance );
            lpOrigInstance->hNextTwin;
            lpOrigInstance = zGETPTR( lpOrigInstance->hNextTwin ) )
      {
         ;  // nothing needs to be done here
      }

      lpOrigViewEntityCsr = fnEstablishViewForInstance( vOrigView, 0,
                                                        lpOrigInstance );

      // Make sure that EntitySpec for the root entity exists.
      if ( SetCursorFirstEntityByString( lpQualView, szlEntitySpec,
                                         szlEntityName,
                                         lpViewEntity->szName,
                                         0 ) < zCURSOR_SET )
      {
         CreateEntity( lpQualView, szlEntitySpec, zPOS_LAST );
         SetAttributeFromString( lpQualView, szlEntitySpec, szlEntityName,
                                 lpViewEntity->szName );
      }
      else
      {
         // Qual view already has qualification on the root entity, so add
         // QualAttrib entities to surround qualification with parens.
         CreateEntity( lpQualView, szlQualAttrib, zPOS_FIRST );
         SetAttributeFromString( lpQualView, szlQualAttrib, szlOper, "(" );

         CreateEntity( lpQualView, szlQualAttrib, zPOS_LAST );
         SetAttributeFromString( lpQualView, szlQualAttrib, szlOper, ")" );

         CreateEntity( lpQualView, szlQualAttrib, zPOS_LAST );
         SetAttributeFromString( lpQualView, szlQualAttrib, szlOper, "AND" );

         CreateEntity( lpQualView, szlQualAttrib, zPOS_NEXT );
         SetAttributeFromString( lpQualView, szlQualAttrib, szlOper, "(" );

         CreateEntity( lpQualView, szlQualAttrib, zPOS_LAST );
         SetAttributeFromString( lpQualView, szlQualAttrib, szlOper, ")" );

         SetCursorPrevEntity( lpQualView, szlQualAttrib, 0 );
      }

      chFirstAttrNbr = 0;

      for ( chCurrentAttrNbr = 1;
            chCurrentAttrNbr <= chMaxAttrNbr;
            chCurrentAttrNbr++ )
      {
         zSHORT k;

         if ( lpSeqViewAttrib[ chCurrentAttrNbr ] == 0 )
            continue;

         if ( chFirstAttrNbr == 0 )
            chFirstAttrNbr = chCurrentAttrNbr;

         // If chCurrentAttrNbr > chFirstAttrNbr, then we have multiple seq
         // attrs in the entity and we need to stick in an "OR".
         if ( chCurrentAttrNbr > chFirstAttrNbr )
         {
            CreateEntity( lpQualView, szlQualAttrib, zPOS_NEXT );
            SetAttributeFromString( lpQualView, szlQualAttrib, szlOper, "OR" );

            CreateEntity( lpQualView, szlQualAttrib, zPOS_NEXT );
            SetAttributeFromString( lpQualView, szlQualAttrib, szlOper, "(" );
         }

         for ( k = chFirstAttrNbr; k <= chCurrentAttrNbr; k++ )
         {
            zCHAR sz[ 256 ];

            if ( lpSeqViewAttrib[ k ] == 0 )
               continue;

            if ( k > chFirstAttrNbr )
            {
               CreateEntity( lpQualView, szlQualAttrib, zPOS_NEXT );
               SetAttributeFromString( lpQualView, szlQualAttrib,
                                       szlOper, "AND" );
            }

            CreateEntity( lpQualView, szlQualAttrib, zPOS_NEXT );
            SetAttributeFromString( lpQualView, szlQualAttrib, szlEntityName,
                                    lpViewEntity->szName );
            SetAttributeFromString( lpQualView, szlQualAttrib, "AttributeName",
                                    lpSeqViewAttrib[ k ]->szName );

            if ( k == chCurrentAttrNbr )
            {
               if ( lpSeqViewAttrib[ k ]->bSequencingD )
                  SetAttributeFromString( lpQualView, szlQualAttrib,
                                          szlOper, "<" );
               else
                  SetAttributeFromString( lpQualView, szlQualAttrib,
                                          szlOper, ">" );
            }
            else
               SetAttributeFromString( lpQualView, szlQualAttrib,
                                       szlOper, "=" );

            GetStringFromRecord( vOrigView, lpViewEntity,
                                 lpSeqViewAttrib[ k ], sz, 256 );
            SetAttributeFromString( lpQualView, szlQualAttrib, "Value", sz );
         }

         if ( chCurrentAttrNbr > chFirstAttrNbr )
         {
            CreateEntity( lpQualView, szlQualAttrib, zPOS_NEXT );
            SetAttributeFromString( lpQualView, szlQualAttrib, szlOper, ")" );
         }

      } // for...

   } // if ( lControl & zACTIVATE_CONTINUE )...

   lpView = 0;
   if ( lpViewOD->szNetwork[ 0 ] == 0 || lControl & zACTIVATE_LOCAL )
   {
      zSHORT nActivateCount;

      // Make sure the LOD has data records.
      lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
      if ( lpViewEntity->hFirstDataRecord == 0 )
      {
         // "KZOEE083 - LOD does not have physical information"
         fnIssueCoreError( lpCurrentTask, lpAppQualView, 16, 83, 0, lpViewOD->szName, 0 );
         goto EndOfFunction;
      }

      // Check to see if we have pessimistic locking defined for the LOD.
      if ( lpViewOD->nLock       >= zLL_PESSIMISTIC ||
           lpViewOD->nEntityLock >= zLL_PESSIMISTIC )
      {
         // Check to make sure we can load objects needed for pessimistic
         // locking.
         if ( ActivateViewObject( lpAppQualView, "ZPLOCKO", FALSE ) == 0 )
            goto EndOfFunction;

         // Look for the qualification object.
         if ( ActivateViewObject( lpAppQualView, "KZDBHQUA", TRUE ) == 0 )
            goto EndOfFunction;

         // If user requests locking, then we need to create the locking
         // semaphore so that only one user changes locking at the same time.
         if ( lControl & zSINGLE_FOR_UPDATE )
         {
            if ( lpCurrentTask->bPessimisticLockingSet == FALSE )
            {
               if ( fnCreatePessimisticSemaphore( lpCurrentTask,
                                                  (zPVOID) &lpViewOD, 1, 0,
                                                  lpAppQualView ) < 0 )
               {
                  goto EndOfFunction;
               }

               bLockingSemaphoreCreatedHere = TRUE;
            }
         }
      }

      if ( (nRC = fnDeclareView( &lpView, lpOwningTask, lpAppQualView,
                                 cpcViewOD_Name, FALSE )) != 0 )
      {
         goto EndOfFunction;
      }

#if 0
      if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
      {
         zSHORT nScope = (lControl & zLEVEL_APPLICATION) ?
                                     zLEVEL_APPLICATION : zLEVEL_SYSTEM;

         // Must be done prior to activation.
         SfTransferView( lpView, lpAppQualView, nScope );
      }
#endif

      nRC = fnActivateEmptyObjectInstance( lpCurrentTask, lpView, lControl );
      if ( nRC )
      {
         // fnActivateEmptyObjectInstance didn't work for some reason.
         // Restore the view cursor to the way is was before the call.
         goto EndOfFunction;
      }

      nActivateCount = 1;

      SetNameForView( lpView, "__Load-in-progress", 0, zLEVEL_TASK );

      // Call fnActivateObjectInstance until activate was achieved. It is
      // possible that there are locks in place that keep the activate from
      // working.
      // Activate object instance.  If database is in use, wait two seconds
      // and try again.
      // Create a temp qualification so the original doesn't get changed.
      if ( lpQualView )
      {
         fnDeclareView( &vTempQual, lpOwningTask, lpQualView, 0, 0 );
         fnSetViewFromView( vTempQual, lpQualView );
      }
      else
         vTempQual = 0;

      while ( TRUE )
      {
         nRC = fnActivateObjectInstance( lpCurrentTask, lpView,
                                         vTempQual, lControl );

         // If fnActivateObjectInstance worked OK, drop old ViewCsr,
         // otherwise restore the view cursor.
         if ( nRC >= -1 )
         {
            // Try to relink entity instances.
            fnRelinkObjectInstance( lpView );
            break;
         }
         else
         if ( nRC == zDB_UNAVAIL )
         {
            // Database was unavailable (in use by another user).
            nActivateCount++;

            // If we've tried 8 times, exit anyway.
            if ( nActivateCount > 8 )
            {
               fnDropView( lpView );
               lpView = 0;   // Null out lpView so it won't be dropped again.
               goto EndOfFunction;
            }

            SysWait( 2000 );  // Wait for 2 seconds then try again.
            TraceLineS( "(oi) -------------------------------", "" );
            TraceLineS( "(oi) Database unavailable--try again", "" );
            TraceLineS( "(oi) -------------------------------", "" );
         }
         else
         if ( nRC == zDB_DEADLOCK )
         {
            // Transaction backed out because of deadlock.
            zCHAR  szMsg[ 256 ];

            strcpy_s( szMsg, zsizeof( szMsg ), "(oi) Database Deadlock - Object=" );
            strcat_s( szMsg, zsizeof( szMsg ), cpcViewOD_Name );
            strcat_s( szMsg, zsizeof( szMsg ), " Activate Retry Count=" );
            TraceLineI( szMsg, nActivateCount );

            nActivateCount++;

            // If we've tried 3 times, exit anyway.
            if ( nActivateCount > 3 )
            {
               fnDropView( lpView );
               lpView = 0;   // Null out lpView so it won't be dropped again.
               TraceLineS( "(oi) Deadlock Crash - Retry Count exceeded", "" );

               goto EndOfFunction;
            }

            DropObjectInstance( lpView );

            nRC = fnDeclareView( &lpView, lpOwningTask, lpAppQualView,
                                 cpcViewOD_Name, FALSE );
            if ( nRC )
               goto EndOfFunction;

#if 0
            if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
            {
               zSHORT nScope = (lControl & zLEVEL_APPLICATION) ?
                                           zLEVEL_APPLICATION : zLEVEL_SYSTEM;
               SfTransferView( lpView, lpAppQualView, nScope );
            }
#endif

            if ( fnActivateEmptyObjectInstance( lpCurrentTask, lpView,
                                                lControl ) != 0 )
            {
               goto EndOfFunction;
            }

            SetNameForView( lpView, "__Load-in-progress", 0, zLEVEL_TASK );
         }
         else
         {
            if ( nRC == zMEMORY_LIMIT )
            {
               // Transaction backed out because of memory error.
               TraceLine( "(oi) Database Memory Limit Reached (Task: 0x%08x) - Object: %s",
                          zGETHNDL( lpCurrentTask), cpcViewOD_Name );
            }

            // Some error occurred.  Bomb out.
            fnDropView( lpView );
            lpView = 0;   // Null out lpView so it won't be dropped again.
            goto EndOfFunction;
         }
      } // while ( TRUE )...

      if ( nRC >= 0 )
      {
         lpViewCsr = zGETPTR( lpView->hViewCsr );
         lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
      }

      // If nRC is 0 or greater, then we've retrieved a valid object.  If
      // the Object instance has any optmistic locking, then some
      // processing needs to be performed.
      if ( nRC >= 0 && (lControl & zSINGLE_FOR_UPDATE) &&
           (lpViewOD->nLock == zLL_OPTIMISTIC_NOINC ||
            lpViewOD->nLock == zLL_OPTIMISTIC_CMPRALL) )
      {
         zVIEW vOriginalOI;

         // The user wants optimistic locking.  All we need to do right
         // now is save the current OI and the qualification OI.  First
         // make sure we don't have any old ones lying around.
         if ( lpViewOI->vOriginalOI )
            fnDropView( zGETPTR( lpViewOI->vOriginalOI ) );

         if ( lpViewOI->vQualOI )
            fnDropView( zGETPTR( lpViewOI->vQualOI ) );

         // Copy the current OI to a safe place so that we can reference
         // it later.  We need to flag the original view so that if
         // vOriginalOI gets dropped before the main OI gets dropped we
         // will know about it.
         ActivateOI_FromOI_ForTask( &vOriginalOI, lpView, 0, zMULTIPLE );
         vOriginalOI->bOrigView   = TRUE;
         vOriginalOI->bViewLocked = TRUE;
         vOriginalOI->hMainOI     = zGETHNDL( lpViewOI );
         lpViewOI->vOriginalOI    = zGETHNDL( vOriginalOI );

         if ( lpQualView )
         {
            zVIEW vQualOI;

            ActivateOI_FromOI_ForTask( &vQualOI, lpQualView, 0, zMULTIPLE );
            vQualOI->bQualView   = TRUE;
            vQualOI->bViewLocked = TRUE;
            vQualOI->hMainOI     = vOriginalOI->hMainOI; // = zGETHNDL( lpViewOI );

            // It is possible that the qual OI contains references to
            // another view.  These views might not be around (or they
            // might change) when we use the qual OI again.  To avoid
            // these errors, resolve all references to other views.
            fnResolveQualOI( vQualOI, "QualAttrib" );
            fnResolveQualOI( vQualOI, "SubQualAttrib" );

            lpViewOI->vQualOI = zGETHNDL( vQualOI );
         }
         else
            lpViewOI->vQualOI = 0;

      } // if ( nRC >= 0 && OPTIMISTIC LOCKING )...

      if ( lpView )
         DropNameForView( lpView, "__Load-in-progress", lpView, zLEVEL_TASK );

   } // if ( lpViewOD->hszNetwork == 0 || lControl & zACTIVATE_LOCAL )...
   else
   {
      zLONG lNetControl;

      // We need to activate from the network, sooo ...

      // First make sure the network is active.
      nRC = NetStatus( lpAppQualView, lpViewOD->szNetwork );
      if ( nRC == 0 )
      {
         nRC = NetStartup( lpAppQualView, lpViewOD->szNetwork,
                           lpViewOD->szNetwork );
         if ( nRC )
         {
            MessageSend( lpAppQualView, "xx", "KZOEOIAA",
                        "Network cannot be started.",
                        zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
            nRC = zCALL_ERROR;
            goto EndOfFunction;
         }
      }

      // Since we are handling the CONTINUE logic on the client side, turn
      // off the CONTINUE flag (if it's on).
      lNetControl = lControl & ~zACTIVATE_CONTINUE;

      nRC = NetActivateOI( lpViewOD->szNetwork, 0, &lpView,
                           (zPCHAR) cpcViewOD_Name, lpAppQualView,
                           lpQualView, lNetControl );
   }

   if ( lpView )
   {
      lpViewOD  = zGETPTR( lpView->hViewOD );
      lpViewCsr = zGETPTR( lpView->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
      lpViewOI->lActivateControl = lControl;
   }

   if ( nRC >= 0 && lControl & zREADONLY )
      lpView->bReadOnly = TRUE;

   // If we are doing a CONTINUE activate then we need to add the entities
   // just loaded to the original instance.
   if ( lControl & zACTIVATE_CONTINUE )
   {
      LPENTITYINSTANCE lpEntityInstance;

      for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
      // LPDATARECORD     lpFirstDataRecord;
      // LPDATAFIELD      lpDataField;
         LPVIEWATTRIB     lpViewAttrib;
         LPVIEWENTITYCSR  lpViewEntityCsr;
         LPENTITYINSTANCE lpNewEI;
         zBOOL            bNewRoot;

         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
         fnEstablishViewForInstance( lpView, 0, lpEntityInstance );

         fnValidViewEntity( &lpViewEntityCsr, vOrigView,
                            lpViewEntity->szName, 0 );
         if ( lpViewEntity->hParent )
            bNewRoot = FALSE;
         else
            bNewRoot = FALSE; // TRUE;

         fnCreateEntity( vOrigView, lpViewEntity, lpViewEntityCsr, zPOS_LAST,
                         (zSHORT) bNewRoot );
         lpNewEI = zGETPTR( lpViewEntityCsr->hEntityInstance );

         // Loop through all persistent entities and store values in object.
         for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
               lpViewAttrib;
               lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
         {
            zPCHAR  lpPtr;
            zULONG  uLth;

            if ( lpViewAttrib->bPersist )
            {
               fnGetAttrAddrFromEntityInstance( &lpPtr, &uLth,
                                                lpEntityInstance,
                                                lpViewAttrib );
               fnStoreValueInEntityInstance( lpNewEI, lpViewEntity,
                                             lpViewAttrib, lpPtr, uLth );
            }

         } // for ( lpDataField... )...

      } // for ( lpEntityInstance... )...

      fnDropView( lpView );
      lpView = vOrigView;

   } // if ( lControl & zACTIVATE_CONTINUE )...

   if ( nRC >= 0 )
   {
      // Reset the view to its initial state.
      if ( lControl & zACTIVATE_CONTINUE )
         fnEstablishViewForInstance( lpView, 0, lpOrigInstance );
      else
         fnResetView( lpView, 0 );

   } // if ( nRC >= 0 )...

#ifdef __ACTIVATE_CONSTRAINTS__

   if ( (lControl & zACTIVATE_NOCONSTRAINTS) == 0 )
   {
      // If there is an Object Constraint for activate, see if it has
      // any objections about continuing.
      if ( nRC >= 0 && lpViewOD->bActivateConstraint )
      {
         zSHORT   nState;
         zSHORT   k;

         nState = (lControl & zLEVEL_SYSTEM) ? zOCE_STATE_SYSTEM : 0;
         if ( lControl & zMULTIPLE )
            nState |= zOCE_STATE_MULTIPLE;

         k = fnInvokeOCEOperation( lpView, lpCurrentTask,
                                   zOCE_ACTIVATE, nState );
         // If object constraint says no go, drop the view and exit
         if ( k )
         {
            nRC = k;
            goto EndOfFunction;
         }
      }
   }
#endif

   // If the view has pessimistic locking and if the zSINGLE_FOR_UPDATE flag
   // has not been set or if the locking level is zLL_PESSIMISTIC then the
   // view is read-only.
   if ( nRC >= -1 && lpView &&
        (((lControl & zSINGLE_FOR_UPDATE) == 0 &&
          (lpViewOD->nLock > 0 ||
           lpViewOD->nEntityLock > zLL_PESSIMISTIC)) ||
         lpViewOD->nLock == zLL_PESSIMISTIC) )
   {
      lpView->bReadOnly   = TRUE;
      lpViewOI->bReadOnly = TRUE;
   }

EndOfFunction:

   if ( bLockingSemaphoreCreatedHere )
      fnDeletePessimisticSemaphore( lpCurrentTask,
                                    (zPVOID) &lpViewOD, 1, 0, lpAppQualView );

   if ( AnchorBlock->TraceFlags.bOI_Times )
   {
      zCHAR sz[ 100 ];

      sprintf_s( sz, zsizeof( sz ), "%lf seconds for object %s ",
                 (double) (SysGetTickCount( ) - lTickCount) / zTICKS_PER_SECOND,
                 cpcViewOD_Name );
      TraceLineS( "(oi) Total time for ActivateObjectInstance = ", sz );
   }

   if ( nRC < -1 )
   {
      if ( lpView )
         fnDropView( lpView );

      if ( (lControl & zACTIVATE_CONTINUE) == 0 )
         *pvReturnView = 0;
   }
   else
      *pvReturnView = lpView;

   if ( vTempQual )
      fnDropView( vTempQual );

   if ( bDropQual )
      fnDropView( lpQualView );

   fnOperationReturn( iActivateObjectInstance, lpCurrentTask );
   return( nRC );

}  // ActivateObjectInstance

zSHORT OPERATION
fnReadDataFromFileStream( zVIEW   lpView,
                          zPVOID  pvData,
                          zPPCHAR ppchReturnBuffer,
                          zULONG  uLth,
                          zSHORT  nErrorNbr )
{
   LPFILEDATA lpFileData = (LPFILEDATA) pvData;

   // If nErrorNbr is not 0, then flash the error message and get out.
   if ( nErrorNbr )
   {
      zPCHAR pchExtraData = (zPCHAR) ppchReturnBuffer;
      LPTASK lpTask = zGETPTR( lpView->hTask );

      switch ( nErrorNbr )
      {
         case 74:
         {
            // "KZOEE074 - Invalid Entity name on line "
            fnIssueCoreError( lpTask, lpView, 16, 74, lpFileData->lLine,
                              pchExtraData, lpFileData->pchFileName );
            break;
         }

         case 75:
            // "KZOEE075 - Invalid Entity level on line "
            fnIssueCoreError( lpTask, lpView, 16, 75, lpFileData->lLine,
                              pchExtraData, lpFileData->pchFileName );
            break;

         case 90:
            // "KZOEE090 - Maximum number of entites in portable file exceeded"
            fnIssueCoreError( lpTask, lpView, 16, 90, lpFileData->lLine,
                              lpFileData->pchFileName, "" );
            break;

         case 104:
            // "KZOEE104 - Invalid Attribute name for Entity"
            fnIssueCoreError( lpTask, lpView, 16, 104, 0, pchExtraData, 0 );
            break;

      } // switch ( nErrorNbr )

      return( 0 );

   } // if ( nErrorNbr )...

   lpFileData->lLine++;

   if ( uLth )
      return( SysReadLineLth( lpView, ppchReturnBuffer, lpFileData->hFile, uLth ) );
   else
      return( SysReadLine( lpView, ppchReturnBuffer, lpFileData->hFile ) );

} // fnReadDataFromFileStream

//./ ADD NAME=ActivateOI_FromFile
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ActivateOI_FromFile
//
//  PURPOSE:    To activate an Object instance from a file and
//              return a view to the object instance
//
//  PARAMETERS: pvReturnView  - View returned to instance activated
//              cpcViewOD_Name - Name of the view object.  If 0, the
//                              returned view is for the same object as
//                              the initial view(?).
//              lpAppQualView - Used to qualify the application in which
//                              to look for the object.  If the view
//                              passed is a subtask view, then the
//                              application that is used is the
//                              application tied to the subtask.
//                              Otherwise, the application for the view
//                              object associated with the passed view
//                              is used.  This must be a valid view!
//              szFileName    - The fully-qualified file name from which
//                              to activate (including the drive, path,
//                              and file extension).
//              lControl      - Controls certain aspects of the file
//                              loaded.
//                            zSINGLE   - (default) only one entity at the
//                                        root level.
//                            zMULTIPLE - multiple entities at the root
//                                        level
//                            zLEVEL_APPLICATION - created view is tied
//                                        to the application task,
//                                        rather than the active task.
//                            zLEVEL_SYSTEM - created view is tied
//                                        with the system task,
//                                        rather than the active task.
//                            zLEVEL_SAME - created view is tied to the
//                                        same task as lpAppQualView.
//                                        Note: specifying this option
//                                        requires that lpAppQualView be
//                                        be specified and that it not be
//                                        a subtask view.
//                            zNOI_OKAY - when set, if the file could not
//                                        be found, no error message is
//                                        issued, just return code set.
//                            zREADONLY - Marks the View and the Instance
//                                        as read only.  Any view created
//                                        from this view will also be
//                                        marked as read only.
//                            zIGNORE_ERRORS - Loads what info it can if
//                                        the file is ASCII
//
//  RETURNS:   -1 - zNOI_OKAY was specified and the file could not be
//                  loaded into the Object Instance; pvReturnView points
//                  to an empty object instance.
//              0 - Object instance activated, single root found
//              1 - Object instance activated, multiple roots found.  If
//                  zSINGLE was specified, only the first was activated.
//    zCALL_ERROR - Error Activating object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 6
zSHORT OPERATION
ActivateOI_FromFile( zPVIEW    pvReturnView,
                     zCPCHAR   cpcViewOD_Name,
                     zVIEW     lpAppQualView,
                     zCPCHAR   cpcFileName,
                     zLONG     lControl )
{
   LPTASK          lpCurrentTask;
   LPTASK          lpTask;
   LPVIEWOD        lpViewOD;
   LPAPP           lpApp;
   FileDataRecord  ActFileData;
   zVIEW           vTask;
   zLONG           l;
   zLONG           hFile;
   zCHAR           szOpenFileName[ 2 * zMAX_FILESPEC_LTH + 1 ];
   zCHAR           szWork[ 2 * zMAX_FILESPEC_LTH + 1 ];
   zBOOL           bSystemObj;
   zSHORT          nRC;

   // Init in case of error.
   *pvReturnView = 0;
   bSystemObj = (lControl & zACTIVATE_SYSTEM) ? TRUE : FALSE;

   // If task not active or disabled, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iActivateOI_FromFile,
                                          lpAppQualView, 0 )) == 0 )
   {
      return( zCALL_ERROR );
   }

   // Unless we're activating a system object, ensure that the app qual
   // view is valid.
   if ( (lpAppQualView || !(lControl & zACTIVATE_SYSTEM)) &&
        fnValidView( lpCurrentTask, lpAppQualView ) == 0 )
   {
      fnOperationReturn( iActivateOI_FromFile, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // Verify only one zLEVEL_ option requested.
   l = lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM | zLEVEL_SAME);
   if ( l && (-l & l) != l )
   {
      // error, More than one zLEVEL_ option requested
      // "KZOEE023 - Invalid parameter, "
      fnIssueCoreError( lpCurrentTask, lpAppQualView, 8, 23, 0,
                        "More than one zLEVEL_ option requested", 0 );
      fnOperationReturn( iActivateOI_FromFile, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // If zLEVEL_SAME is requested.
   if ( lControl & zLEVEL_SAME )
   {
      if ( lpAppQualView == 0 || lpAppQualView->hSubtask )
      {
         // "KZOEE100 - Invalid View, view is a Subtask View"
         fnIssueCoreError( lpCurrentTask, lpAppQualView, 8, 100, 0,
                           "lpAppQualView", "with zLEVEL_SAME" );
         fnOperationReturn( iActivateOI_FromFile, lpCurrentTask );
         return( zCALL_ERROR );
      }
      else
      {
         LPVIEWCSR lpViewCsr;

         // Turn off the 'same' indicator
         lControl ^= zLEVEL_SAME;
         // To determine what the level is of the qualifying view
         //   1. Change lpAppQualView to point to the initial
         //      view created for the object instance
         //   2. Check for application level, if there use
         //      zLEVEL_APPLICATION.
         //   3. Check if the view task is the main task, if so use
         //      zLEVEL_SYSTEM.
         //   4. Use the task level...
         lpViewCsr = zGETPTR( lpAppQualView->hViewCsr );
         while ( lpViewCsr->hNextViewCsr )
            lpViewCsr = zGETPTR( lpViewCsr->hNextViewCsr );

         lpAppQualView = zGETPTR( lpViewCsr->hView );
         if ( lpAppQualView->bApplicationView )
            lControl |= zLEVEL_APPLICATION;
         else
         if ( lpAppQualView->hTask == AnchorBlock->hMainTask )
            lControl |= zLEVEL_SYSTEM;
      }
   }

   // Make sure request is for valid OD.
   lpViewOD = ActivateViewObject( lpAppQualView, cpcViewOD_Name, bSystemObj );
   if ( lpViewOD == 0 )
   {
      fnOperationReturn( iActivateOI_FromFile, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // First off, see if we can open the filename requested,
   // go through characters in name and see if they need either
   // a directory qualification prefix or an object file suffix.

// Change DGC 5/27/96 -- In an attempt to make all code retrieve the
// application in the same way from a view, I have changed the following code.
   fnGetApplicationForSubtask( &lpApp, lpAppQualView );

// DGC 9/23/96
// I changed the logic: if the file name is not qualfied, use the object dir
// for the application. I repeated this change in CommitOI_ToFile.
   if ( zstrchr( cpcFileName, cDirSep ) == 0 )
   {
      if ( lpApp )
         strcpy_s( szWork, zsizeof( szWork ), lpApp->szObjectDir );
      else
      {
         LPAPP lpSystemApp = zGETPTR( AnchorBlock->hSystemApp );

         strcpy_s( szWork, zsizeof( szWork ), lpSystemApp->szObjectDir );
      }

      SysAppendcDirSep( szWork );
   }
   else
      szWork[ 0 ] = 0;

   strcat_s( szWork, zsizeof( szWork ), cpcFileName ); // w\bin\sys\tzrpsrco.lod
   SysConvertEnvironmentString( szOpenFileName, zsizeof( szOpenFileName ), szWork );

   if ( AnchorBlock->TraceFlags.bOpenFile )
   {
      if ( zstrstr( cpcFileName, "TZCMULWO.POR" ) == 0 )
      {
         if ( zstrstr( cpcFileName, "KZTRANWO." ) != 0 )
            TraceLineS( "(oi) opening >>>>>>>>>> ", szOpenFileName );
         else
            TraceLineS( "(oi) opening ", szOpenFileName );
      }
   }

   // Open the file for the object instance data.
   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
   {
      lpTask = zGETPTR( AnchorBlock->hMainTask );
   // hFile = fnSysOpenFile( lpTask, szOpenFileName, COREFILE_READ );
   }
   else
   {
      lpTask = lpCurrentTask;
   // hFile = SysOpenFile( lpAppQualView, szOpenFileName, COREFILE_READ );
   }

   if ( lpAppQualView && zGETPTR( lpAppQualView->hTask ) == lpTask ) // added dks 2006.09.15 to prevent looking
      vTask = lpAppQualView;                                         // at incorrect app when we just pick vTask
   else                                                              // willy-nilly (as is done on the next line)
      vTask = zGETPTR( lpTask->hFirstView );

   hFile = SysOpenFile( vTask, szOpenFileName, COREFILE_READ );
   if ( hFile == -1 )
   {
      if ( lControl & zNOI_OKAY )
      {
         fnOperationReturn( iActivateOI_FromFile, lpCurrentTask );
         return( -1 );
      }
      else
      {
         //  "KZOEE071 - Error opening instance file "
         fnIssueCoreError( lpCurrentTask, lpAppQualView, 16, 71, 0,
                           szOpenFileName, 0 );
         fnOperationReturn( iActivateOI_FromFile, lpCurrentTask );
         return( zCALL_ERROR );
      }
   }

   ActFileData.pchFileName = szOpenFileName;
   ActFileData.hFile = hFile;
   ActFileData.lLine = 1;

   nRC = SfActivateOI_FromStream( pvReturnView, cpcViewOD_Name,
                               // lpAppQualView, lControl,
                                  vTask, lControl,
                                  fnReadDataFromFileStream,
                                  (zPVOID) &ActFileData );

// TraceLine( "ActivateOI_FromFile: 0x%08x", *pvReturnView );

   // Close the file
   fnSysCloseFile( lpTask, hFile, 0 );

   fnOperationReturn( iActivateOI_FromFile, lpCurrentTask );
   return( nRC );

} // ActivateOI_FromFile

//./ ADD NAME=ActivateOI_FromOI_ForTask
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ActivateOI_FromOI_ForTask
//
//  PURPOSE:    To create an object instance from an object instance
//              already in memory. This operation copies an object
//              instance in memory and isolates (delinks) it from
//              any other object instances in memory which the
//              source instance may be linked to. The incremental
//              information from the source instance in memory is
//              brought over to the new instance as is.
//
//  PARAMETERS: pvReturnView  - View returned to instance activated
//              lpSrcView     - The view which currently contains the
//                              instance to be activated (copied)
//              lControl      - Controls certain aspects of the OI
//                              loaded.
//                            zSINGLE   - (default) only one entity at the
//                                        root level.  Activates the root
//                                        entity that is selected.
//                            zMULTIPLE - multiple entities at the root
//                                        level
//                            zLEVEL_APPLICATION - created view is tied
//                                        to the application task,
//                                        rather than the active task.
//                            zLEVEL_SYSTEM   - created view is tied
//                                        with the system task,
//                                        rather than the active task.
//                            zLEVEL_SAME - created view is tied to the
//                                        same task as lpAppQualView.
//                                        Note: specifying this option
//                                        requires that lpAppQualView be
//                                        be specified and that it not be
//                                        a subtask view.
//                            zREADONLY - Marks the View and the Instance
//                                        as read only.  Any view created
//                                        from this view will also be
//                                        marked as read only.
//
//  RETURNS:    0 - Object instance activated, single root found
//              1 - Object instance activated, multiple roots found.  If
//                  zSINGLE was specified, only the first was activated.
//    zCALL_ERROR - Error Activating object instance
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT OPERATION
ActivateOI_FromOI( zPVIEW  pvReturnView,
                   zVIEW   lpSrcView,
                   zLONG   lControl )
{
   return( ActivateOI_FromOI_ForTask( pvReturnView, lpSrcView, 0, lControl ) );
}

zSHORT OPERATION
ActivateOI_FromOI_ForTask( zPVIEW  pvReturnView,
                           zVIEW   lpSrcView,
                           zVIEW   lpTaskView,
                           zLONG   lControl )
{
   LPTASK      lpCurrentTask;
   LPTASK      lpOwningTask;
   LPVIEWOI    lpSrcViewOI;
   LPVIEWOI    lpTgtViewOI;
   LPVIEWCSR   lpViewCsr;
   zVIEW       lpTgtView;
   zLONG       l;
   zBOOL       bMultiple;
   zSHORT      nRC;

   *pvReturnView = 0;  // init in case of error

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iActivateOI_FromOI, lpSrcView,
                                          zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   // Get the view oi and ensure that it has no outstanding temporal
   // entities or subobjects.
   lpViewCsr = zGETPTR( lpSrcView->hViewCsr );

   lpSrcViewOI = zGETPTR( lpViewCsr->hViewOI );
   if ( lpSrcViewOI->nVersionedInstances )
   {
      //  "KZOEE076 - Object instance contains versioned entity instances"
      fnIssueCoreError( lpCurrentTask, lpSrcView, 8, 76, 0, 0, 0 );
      fnOperationReturn( iActivateOI_FromOI, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // Verify only one zLEVEL_ option requested.
   l = lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM | zLEVEL_SAME);
   if ( l && (-l & l) != l )
   {
      // error, More than one zLEVEL_ option requested
      // "KZOEE023 - Invalid parameter, "
      fnIssueCoreError( lpCurrentTask, lpSrcView, 8, 23, 0,
                        "More than one zLEVEL_ option requested", 0 );
      fnOperationReturn( iActivateOI_FromOI, lpCurrentTask );
      return( zCALL_ERROR );
   }

   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
      lpOwningTask = zGETPTR( AnchorBlock->hMainTask );
   else
      lpOwningTask = lpCurrentTask;

   // Get multiple root indicator.
   bMultiple = 0;
   if ( lControl & zMULTIPLE )
      bMultiple = TRUE;

   // If zLEVEL_SAME is requested.
   if ( lControl & zLEVEL_SAME )
   {
      // Turn off the 'same' indicator.
      lControl ^= zLEVEL_SAME;
      // To determine what the level is of the qualifying view
      //   1. Change lpSrcView to point to the initial
      //      view created for the object instance
      //   2. Check for application level, if there use
      //      zLEVEL_APPLICATION.
      //   3. Check if the view task is the main task, if so use
      //      zLEVEL_SYSTEM.
      //   4. Use the task level...
      lpViewCsr = zGETPTR( lpSrcView->hViewCsr );
      while ( lpViewCsr->hNextViewCsr )
         lpViewCsr = zGETPTR( lpViewCsr->hNextViewCsr );

      lpSrcView = zGETPTR( lpViewCsr->hView );
      if ( lpSrcView->bApplicationView )
         lControl |= zLEVEL_APPLICATION;
      else
      if ( lpSrcView->hTask == AnchorBlock->hMainTask )
         lControl |= zLEVEL_SYSTEM;
   }

   if ( (nRC = fnDeclareView( &lpTgtView, lpOwningTask,
                              lpSrcView, 0, 0 )) != 0 )
   {
      fnOperationReturn( iActivateOI_FromOI, lpCurrentTask );
      return( nRC );
   }

#if 0
   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
   {
      zSHORT nScope = (lControl & zLEVEL_APPLICATION) ?
                                  zLEVEL_APPLICATION : zLEVEL_SYSTEM;
      if ( (nRC = SfTransferView( lpTgtView, lpSrcView,
                                  nScope )) != 0 )
      {
         fnOperationReturn( iActivateOI_FromOI, lpCurrentTask );
         return( nRC );
      }
   }
#endif

   // Create an empty object instance in which to copy the object instance.
   nRC = fnActivateEmptyObjectInstance( lpCurrentTask, lpTgtView, lControl );
   if ( nRC == 0 )
   {
      LPTASK           lpInstanceOwningTask;
      LPVIEWENTITY     lpViewEntity;
      LPENTITYINSTANCE lpSrcEntityInstance;
      LPENTITYINSTANCE lpTgtEntityInstance;
      LPENTITYINSTANCE lpLastTgtEntityInstance;
      LPENTITYINSTANCE lpTgtParent;
      LPENTITYINSTANCE lpWkInstance1;
      LPENTITYINSTANCE lpWkInstance2;
      LPVIEWOI         hTgtViewOI;
      zPVOID           hTgtEntityInstance;
      zSHORT           nLastLvl;

      // Here we copy the instance in memory.
      lpViewCsr   = zGETPTR( lpTgtView->hViewCsr );
      hTgtViewOI  = lpViewCsr->hViewOI;
      lpTgtViewOI = zGETPTR( hTgtViewOI );
      lpInstanceOwningTask = zGETPTR( lpTgtViewOI->hAllocTask );
      lpTgtEntityInstance = 0;
      lpLastTgtEntityInstance = 0;
      lpTgtParent = 0;

      // Set the first source entity instance.  If zSINGLE was set, then the
      // first entity instance should be the selected root for the view.
      lpSrcEntityInstance = 0;

      if ( bMultiple == FALSE )
      {
         LPVIEWENTITYCSR lpRootViewEntityCsr;

         lpViewCsr= zGETPTR( lpSrcView->hViewCsr );
         lpRootViewEntityCsr = zGETPTR( lpViewCsr->hRootViewEntityCsr );
         lpSrcEntityInstance = zGETPTR( lpRootViewEntityCsr->hEntityInstance );
      }

      if ( lpSrcEntityInstance == 0 || lpSrcEntityInstance == UNSET_CSR )
         lpSrcEntityInstance = zGETPTR( lpSrcViewOI->hRootEntityInstance );

      // For each instance in the source, copy the instance and
      // link the new instance to the source instance. This link will
      // be removed later on after the initial copy is complete.
      while ( lpSrcEntityInstance )
      {
         nLastLvl = lpSrcEntityInstance->nLevel;
         lpViewEntity = zGETPTR( lpSrcEntityInstance->hViewEntity );

         hTgtEntityInstance =
                     fnAllocDataspace( lpInstanceOwningTask->hFirstDataHeader,
                                       sizeof( EntityInstanceRecord ), 0, 0,
                                       iEntityInstance );
         lpTgtEntityInstance = zGETPTR( hTgtEntityInstance );
         if ( lpTgtEntityInstance )
         {
            zmemcpy( (zPVOID) lpTgtEntityInstance,
                     (zPVOID) lpSrcEntityInstance,
                     sizeof( EntityInstanceRecord ) );
            lpTgtEntityInstance->hViewOI   = hTgtViewOI;
            lpTgtEntityInstance->hPrevHier = zGETHNDL( lpLastTgtEntityInstance );
            lpTgtEntityInstance->hNextHier = 0;
            lpTgtEntityInstance->hNextTwin = 0;
            fnSetEntityKey( lpInstanceOwningTask, 0, lpTgtEntityInstance );
            if ( lpLastTgtEntityInstance )
            {
               lpLastTgtEntityInstance->hNextHier = hTgtEntityInstance;
               if ( lpSrcEntityInstance->hPrevTwin )
               {
                  LPENTITYINSTANCE hWkInstance1;

                  hWkInstance1  = lpSrcEntityInstance->hPrevHier;
                  lpWkInstance1 = zGETPTR( hWkInstance1 );
                  lpWkInstance2 = zGETPTR( lpTgtEntityInstance->hPrevHier );
                  while ( hWkInstance1 != lpSrcEntityInstance->hPrevTwin )
                  {
                     hWkInstance1  = lpWkInstance1->hPrevHier;
                     lpWkInstance1 = zGETPTR( hWkInstance1 );
                     lpWkInstance2 = zGETPTR( lpWkInstance2->hPrevHier );
                  }

                  lpTgtEntityInstance->hPrevTwin = zGETHNDL( lpWkInstance2 );
                  lpWkInstance2->hNextTwin = hTgtEntityInstance;
               }
            }
            else
            {
               lpTgtViewOI->hRootEntityInstance = hTgtEntityInstance;
               lpTgtEntityInstance->hPrevTwin = 0;
            }

            lpTgtEntityInstance->hParent = zGETHNDL( lpTgtParent );
         // if ( lpTgtEntityInstance->hParent == UNSET_CSR )
         //    SysMessageBox( 0, "ActivateOI_FromOI", "UNSET_CSR", -1 );

            if ( lpSrcEntityInstance->hNextLinked )
               lpSrcEntityInstance->hNextLinked = hTgtEntityInstance;

            fnAddEntityToDebugChange( lpTgtEntityInstance );
         }
         else
         if ( lpLastTgtEntityInstance )
         {
            lpLastTgtEntityInstance->hNextHier = 0;
            lpLastTgtEntityInstance->hNextTwin = 0;
            nRC = zCALL_ERROR;
            break;
         }

         // Get the next entity instance in memory to copy.
         lpSrcEntityInstance = zGETPTR( lpSrcEntityInstance->hNextHier );
         if ( lpSrcEntityInstance )
         {
            if ( lpSrcEntityInstance->nLevel == 1 && bMultiple == FALSE )
            {
               nRC = 1;
               lpSrcEntityInstance = 0;
            }
            else
            if ( lpSrcEntityInstance->nLevel > nLastLvl )
               lpTgtParent = lpTgtEntityInstance;
            else
            {
               while ( lpTgtParent &&
                       lpTgtParent->nLevel >= lpSrcEntityInstance->nLevel )
               {
                  lpTgtParent = zGETPTR( lpTgtParent->hParent );
               }
            }
         }
         else
            nRC = 0;

         lpLastTgtEntityInstance = lpTgtEntityInstance;
      }

      // We've copied the entity instance chain and linked all the
      // new instance information with the source being copied, now
      // isolate the copied instance by de-linking it from all
      // instances in other ViewOI's and copying the data-record
      // for each instance.
      hTgtEntityInstance  = lpTgtViewOI->hRootEntityInstance;
      lpTgtEntityInstance = zGETPTR( hTgtEntityInstance );
      while ( lpTgtEntityInstance )
      {
         // First, see if the attribute record information needs
         // to be copied, if so, copy it now.
         lpWkInstance1 = zGETPTR( lpTgtEntityInstance->hNextLinked );
         while ( lpWkInstance1 && lpWkInstance1 != lpTgtEntityInstance )
         {
            if ( lpWkInstance1->hViewOI != hTgtViewOI )
               break;

            lpWkInstance1 = zGETPTR( lpWkInstance1->hNextLinked );
         }

         // Copy the non-persistent record regardless
         lpTgtEntityInstance->hNonPersistRecord =
             fnCopyAttributeRecord( lpInstanceOwningTask,
                zGETPTR( lpTgtEntityInstance->hViewEntity ),
                (zPCHAR) zGETPTR( lpTgtEntityInstance->hNonPersistRecord ), 0 );

         // Copy the persistent record unless the instance is linked
         // only to instances in the same ViewOI (which means that
         // the persistent record has already been copied).
         if ( lpWkInstance1 != lpTgtEntityInstance )
         {
            lpTgtEntityInstance->hPersistRecord =
                     fnCopyAttributeRecord( lpInstanceOwningTask,
                         zGETPTR( lpTgtEntityInstance->hViewEntity ),
                         (zPCHAR) zGETPTR( lpTgtEntityInstance->hPersistRecord ), 1 );

            if ( lpWkInstance1 )
            {
               // The instance is linked to another instance in a different
               // ViewOI, create two chains out of the single chain to isolate
               // this object instance from the other one being copied.
               lpSrcEntityInstance = lpWkInstance1;
               lpWkInstance1 = zGETPTR( lpTgtEntityInstance->hNextLinked );
               while ( lpWkInstance1->hNextLinked != hTgtEntityInstance )
                  lpWkInstance1 = zGETPTR( lpWkInstance1->hNextLinked );

               lpWkInstance1->hNextLinked = lpTgtEntityInstance->hNextLinked;
               lpTgtEntityInstance->hNextLinked = 0;
               for ( ; ; )
               {
                  lpWkInstance1 = zGETPTR( lpSrcEntityInstance->hNextLinked );
                  while ( lpWkInstance1 != lpSrcEntityInstance &&
                          lpWkInstance1->hViewOI != lpTgtEntityInstance->hViewOI )
                  {
                     lpWkInstance1 = zGETPTR( lpWkInstance1->hNextLinked );
                  }

                  if ( lpWkInstance1 == lpSrcEntityInstance )
                     break;

                  // We've found another instance in the source chain which
                  // needs to be moved to the target chain, add the instance
                  // to the target chain and update its record pointer to
                  // be the same as the target instance.
                  lpWkInstance2 = lpSrcEntityInstance;
                  while ( lpWkInstance2->hNextLinked != zGETHNDL( lpWkInstance1 ) )
                     lpWkInstance2 = zGETPTR( lpWkInstance2->hNextLinked );

                  lpWkInstance2->hNextLinked = lpWkInstance1->hNextLinked;
                  lpWkInstance1->hPersistRecord = lpTgtEntityInstance->hPersistRecord;
                  if ( lpTgtEntityInstance->hNextLinked == 0 )
                     lpWkInstance1->hNextLinked = hTgtEntityInstance;
                  else
                     lpWkInstance1->hNextLinked = lpTgtEntityInstance->hNextLinked;

                  lpTgtEntityInstance->hNextLinked = zGETHNDL( lpWkInstance1 );
               }
            }
         }

         hTgtEntityInstance  = lpTgtEntityInstance->hNextHier;
         lpTgtEntityInstance = zGETPTR( hTgtEntityInstance );
      }
   }

   if ( nRC >= 0 )
      fnResetView( lpTgtView, 0 );

   // Based on the return code, see if we have to reset the view to the
   // prior instance or clean up the prior instance.
   // Note: rc = indicates multiple level1 roots are present.
   if ( nRC >= -1 )
   {
      if ( lControl & zREADONLY )
         lpTgtView->bReadOnly = TRUE;

      lpTgtViewOI->bUpdated     = lpSrcViewOI->bUpdated;
      lpTgtViewOI->bUpdatedFile = lpSrcViewOI->bUpdatedFile;

      *pvReturnView = lpTgtView;
   // TraceLine( "CreateViewFromView: 0x%08x", *pvReturnView );
   }
   else
   {
      fnDropView( lpTgtView );
      *pvReturnView = 0;
   }

   fnOperationReturn( iActivateOI_FromOI, lpCurrentTask );
   return( nRC );

} // ActivateOI_FromOI_ForTask

// Reads a "line" of OI data from a buffer.
//
// The buffer MUST have an extra byte at the end to designate the "EOF" of the
// buffer.  This char may be anything except /r or /n.
zSHORT OPERATION
fnReadDataFromBuffer( zVIEW   lpView,
                      zPVOID  pvData,
                      zPPCHAR ppchReturnBuffer,
                      zULONG  uLth,
                      zSHORT  nErrorNbr )
{
   LPBUFFERDATA lpBufferData = (LPBUFFERDATA) pvData;

   // If nErrorNbr is not 0, then flash the error message and get out.
   if ( nErrorNbr )
   {
      LPTASK lpTask = zGETPTR( lpView->hTask );
      zPCHAR pchExtraData = (zPCHAR) ppchReturnBuffer;

      switch ( nErrorNbr )
      {
         case 74:
            // "KZOEE074 - Invalid Entity name on line "
            fnIssueCoreError( lpTask, lpView, 16, 74, 0,
                              pchExtraData, 0 );
            break;

         case 75:
            // "KZOEE075 - Invalid Entity level on line "
            fnIssueCoreError( lpTask, lpView, 16, 75, 0,
                              pchExtraData, 0 );
            break;

         case 90:
            // "KZOEE090 - Maximum number of entites in portable file exceeded"
            fnIssueCoreError( lpTask, lpView, 16, 90, 0, 0, "" );
            break;

         case 104:
            // "KZOEE104 - Invalid Attribute name for Entity"
            fnIssueCoreError( lpTask, lpView, 16, 104, 0, pchExtraData, 0 );
            break;

      } // switch ( nErrorNbr )

      return( 0 );

   } // if ( nErrorNbr )...

   if ( lpBufferData->pchCurrentByte >= lpBufferData->pchEnd )
   {
      *ppchReturnBuffer = 0;
      return( 0 ); // EOF
   }

   if ( uLth )
   {
      if ( lpBufferData->pchCurrentByte + uLth >= lpBufferData->pchEnd )
      {
         SysMessageBox( lpView, "Internal Core Error", "Out of buffer space", 1 );
         return( 0 );
      }

      *ppchReturnBuffer = lpBufferData->pchCurrentByte;
      lpBufferData->pchCurrentByte += uLth;

      return( 1 );
   }
   else
   {
      *ppchReturnBuffer = lpBufferData->pchCurrentByte;

      // Look for the end of the line or the end of the buffer.  Note that
      // pchEnd points to the "EOF" char and is not part of the data.
      while ( lpBufferData->pchCurrentByte[ 0 ] != '\n' &&
              lpBufferData->pchCurrentByte[ 0 ] != '\r' &&
              lpBufferData->pchCurrentByte < lpBufferData->pchEnd )
      {
         lpBufferData->pchCurrentByte++;
      }

      if ( (lpBufferData->pchCurrentByte[ 0 ] == '\r' &&
            lpBufferData->pchCurrentByte[ 1 ] == '\n' ) ||
           (lpBufferData->pchCurrentByte[ 0 ] == '\n' &&
            lpBufferData->pchCurrentByte[ 1 ] == '\r') )
      {
         *(lpBufferData->pchCurrentByte++) = 0;  // Null end of line and skip \r or \n
      }

      *(lpBufferData->pchCurrentByte++) = 0;  // Null end of line and skip \r or \n

      return( 1 );
   }
}

//./ ADD NAME=fnActivateOI_FromBuffer
/*

   Activates an OI from a memory buffer.

*/
zSHORT OPERATION
fnActivateOI_FromBuffer( zPVIEW   pvReturnView,
                         zCPCHAR  cpcViewOD_Name,
                         zVIEW    lpAppQualView,
                         zPCHAR   pchBuffer,
                         zULONG   uLth,
                         zLONG    lControl )
{
   BufferDataRecord ActBuffData;
   zPCHAR pchData;
   zSHORT nRC;

   // SfActivate needs to be able to change the data in the buffer.  Because of
   // this we will copy the buffer into a temporary buffer.  SfActivate also
   // expects an extra character at the end of the buffer to indicate the EOF.
   // So we need to allocate an extra byte.
   pchData = malloc( uLth + 1 );
   zmemcpy( pchData, pchBuffer, uLth );
   pchData[ uLth ] = 0;  // set the last byte to NULL

   // Set up data to be passed through to fnReadDataFromBuffer( ).
   ActBuffData.pchBuffer      = pchData;
   ActBuffData.pchCurrentByte = pchData;
   ActBuffData.pchEnd         = pchData + uLth;

   nRC = SfActivateOI_FromStream( pvReturnView, cpcViewOD_Name,
                                  lpAppQualView, lControl,
                                  fnReadDataFromBuffer,
                                  (zPVOID) &ActBuffData );
   free( pchData );
   return( nRC );
}

#if 0
LPDBHANDLER LOCALOPER
fnGetDBHandler( LPTASK  hTask,
                zCPCHAR cpcDBHandlerName )
{
   LPDBHANDLER   lpDBHandler;
   LPTASK        lpTask;

   lpTask = zGETPTR( hTask );

   lpDBHandler = zGETPTR( lpTask->hFirstTaskDBHandler );
   while ( lpDBHandler )
   {
      if ( zstrcmp( lpDBHandler->szName, cpcDBHandlerName ) == 0 )
         break;

      lpDBHandler = zGETPTR( lpDBHandler->hNextDBHandler );
   }

   if ( lpDBHandler == 0 )
   {
      // Create DBHandlerTask object and attach to Task.
      LPDBHANDLER hDBHandler = fnAllocDataspace( lpTask->hFirstDataHeader,
                                                 sizeof( DBHandlerRecord ),
                                                 1, 0, iDBHandler );
      lpDBHandler = zGETPTR( hDBHandler );
      if ( lpDBHandler == 0 )
         return( 0 );  // could not allocate memory

   // if ( hTask == 0 )
   // {
   //    zSHORT nRC = 0;
   //    nRC /= nRC;
   // }

      lpDBHandler->hLibrary        = 0;
      lpDBHandler->pfDBHandlerOper = 0;
      strcpy_s( lpDBHandler->szName, cpcDBHandlerName );

      // Insert lpDBHandler into DBHandler chain.
      lpDBHandler->hNextDBHandler = lpTask->hFirstDBHandler;
      lpTask->hFirstDBHandler = hDBHandler;
   }

   // lpDBHandler is good at this point.  Now we need to ensure
   // that we have loaded the correct handler library.
   if ( lpDBHandler->hLibrary == 0 )
   {
      LPLIBRARY  hLibrary;
      zVIEW      vTask;
      zCHAR      szFuncName[ zZEIDON_NAME_LTH + 1 ];

      vTask = zGETPTR( lpTask->hFirstView );
      SysMutexLock( vTask, "Zeidon DBH", 0, 0 );

      // Load the DBHandler library.  If it can't be found, return with error.
      if ( zstrncmpi( lpDBHandler->szName, "KZ", 2 ) == 0 )
      {
         // If handler name starts with KZ, then load handler from Zeidon
         // bin directory.
         zCHAR szLibName[ zMAX_FILENAME_LTH + 1 ];

         strcpy_s( szLibName, zsizeof( szLibName ), AnchorBlock->szZeidonBin );
         strcat_s( szLibName, zsizeof( szLibName ), lpDBHandler->szName );
         hLibrary = SysLoadLibrary( vTask, szLibName );
      }
      else
      {
         hLibrary = SysLoadLibrary( vTask, lpDBHandler->szName );
      }

      if ( hLibrary )
      {
         lpDBHandler->hLibrary = hLibrary;

         // Define entry function name.  First try the default name.
         lpDBHandler->pfDBHandlerOper =
                           (zPDBHOPER) SysGetProc( hLibrary, "DBH_MsgProc" );
         if ( lpDBHandler->pfDBHandlerOper == 0 )
         {
            // Couldn't find the default name.  Try the old-style name.
            strcpy_s( szFuncName, zsizeof( szFuncName ), lpDBHandler->szName );
            strcat_s( szFuncName, zsizeof( szFuncName ), "_DBH_MsgProc" );

            // Find the address of entry func.
            lpDBHandler->pfDBHandlerOper =
                             (zPDBHOPER) SysGetProc( hLibrary, szFuncName );
         }
      }

      SysMutexUnlock( vTask, "Zeidon DBH", 0 );
   }

   return( lpDBHandler );
}
#endif

//./ ADD NAME=fnGetDBHandlerOper
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnGetDBHandlerOper
//
//  PURPOSE:    To retrieve the DBHandler Oper.
//
//              NOTE: Called only from ActivateObjectInstance and
//                    CommitObjectInstance.
//
//  PARAMETERS: lpTask - Current task.
//              lpView - View of the Object Instance to commit.
//              pOper  - Pointer to pOper struct that returns DBHandler oper.
//
//  RETURNS:    0           - Error finding oper.
//              otherwise   - OK--returns pointer to TaskDBHandler
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
LPTASKDBHANDLER LOCALOPER
fnGetDBHandlerOper( LPTASK      lpTask,
                    zVIEW       lpView,
                    zlpPDBHOPER pOperReturn )
{
   LPDBHANDLER      hDBHandler;
   LPDBHANDLER      lpDBHandler;
   LPTASKDBHANDLER  lpTaskDBHandler;
   LPVIEWOD         lpViewOD;
   LPLIBRARY        hLibrary;
   zPVOID           lpPtr;
   zPDBHOPER        pOper;
   zSHORT           nRC;
   zLONG            lProcessID = SysGetProcessID( 0 );

   *pOperReturn = 0;  // initialize

   lpViewOD = zGETPTR( lpView->hViewOD );
   hDBHandler = lpViewOD->hDBHandler;
   lpDBHandler = zGETPTR( hDBHandler );
// lpDBHandler = fnGetDBHandler( hTask, lpViewOD->szDBHandler );

   // Make sure DBHandler can be found.
   if ( lpDBHandler == 0 )
   {
      // "KZOEE080 - Object Definition does not have a Database handler
      // specified"
      fnIssueCoreError( lpTask, lpView, 8, 80, 0, 0, 0 );
      return( 0 );
   }

   // See if DBHandler has already been invoked for this task.
   for ( lpTaskDBHandler = zGETPTR( lpTask->hFirstTaskDBHandler );
         lpTaskDBHandler;
         lpTaskDBHandler = zGETPTR( lpTaskDBHandler->hNextTaskDBHandler ) )
   {
      if ( lpTaskDBHandler->hDBHandler != hDBHandler )
         continue;

      if ( lpTaskDBHandler->lProcessID != lProcessID )
         continue;

      // If we get here then we found the one we're looking for
      break;
   }

   // If TaskDBHandler wasn't found, then this is the first time the
   // DBHandler has been called for this task.
   if ( lpTaskDBHandler )
   {
      // The task DBHandler was found--return pointer to DBHandler routine.
      pOper = lpTaskDBHandler->pfDBHandlerOper;
   }
   else
   {
      zPVOID hTaskDBHandler;
      zCHAR  szFuncName[ 30 ];

      // Load the DBHandler library.  If it can't be found, return with error.
      if ( zstrncmpi( lpDBHandler->szName, "KZ", 2 ) == 0 )
      {
         // If handler name starts with KZ, then load handler from Zeidon
         // bin directory.
         zCHAR szLibName[ 100 ];

         strcpy_s( szLibName, zsizeof( szLibName ), AnchorBlock->szZeidonBin );
         strcat_s( szLibName, zsizeof( szLibName ), lpDBHandler->szName );
         hLibrary = SysLoadLibrary( lpView, szLibName );
      }
      else
         hLibrary = SysLoadLibrary( lpView, lpDBHandler->szName );

      if ( hLibrary == 0 )
         return( 0 );

      // Define entry function name.  First try the default name.
      pOper = (zPDBHOPER) SysGetProc( hLibrary, "DBH_MsgProc" );
      if ( pOper == 0 )
      {
         // Couldn't find the default name.  Try the old-style name.
         strcpy_s( szFuncName, zsizeof( szFuncName ), lpDBHandler->szName );
         strcat_s( szFuncName, zsizeof( szFuncName ), "_DBH_MsgProc" );

         // Find the address of entry func.  If it can't be found, return with
         // an error.
         pOper = (zPDBHOPER) SysGetProc( hLibrary, szFuncName );
         if ( pOper == 0 )
            return( 0 );
      }

      // Call DBHandler routine to issue start of transaction.  Bomb out if
      // it doesn't work.
      lpPtr = 0;
      nRC = (*pOper)( (zLONG) zGETHNDL( lpTask ), DBH_Init, 0,
                      lpViewOD, 0, lpView, 0, (zPVOID) &lpPtr );
      if ( nRC < 0 )
         return( 0 );

      // Create TaskDBHandler object and attach to Task.
      hTaskDBHandler = fnAllocDataspace( lpTask->hFirstDataHeader,
                                         sizeof( TaskDBHandlerRecord ), 1, 0,
                                         iTaskDBHandler );
      lpTaskDBHandler = zGETPTR( hTaskDBHandler );
      if ( lpTaskDBHandler == 0 )
         return( 0 );

      lpTaskDBHandler->hLibrary        = hLibrary;
      lpTaskDBHandler->pfDBHandlerOper = pOper;
      lpTaskDBHandler->hDBHandler      = hDBHandler;
      lpTaskDBHandler->lProcessID      = lProcessID;

      // Insert lpTaskDBHandler into lpTask chain.
      lpTaskDBHandler->hNextTaskDBHandler = lpTask->hFirstTaskDBHandler;
      lpTask->hFirstTaskDBHandler = hTaskDBHandler;
   }  // if ( lpTaskDBHandler )...else...

   *pOperReturn = pOper;

// TraceLine( "fnGetDBHandlerOper in Process: %d   looking for DBHandler: 0x%08x for Task: %d (0x%08x)   Name: %s",
//            lProcessID, zGETHNDL( lpDBHandler ), hTask, hTask, lpTaskDBHandler->szName );

   return( lpTaskDBHandler );

} // fnGetDBHandlerOper

//./ ADD NAME=fnGetGKHandlerOper
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnGetGKHandlerOper
//
//  PURPOSE:    To retrieve the GKHandler Oper.
//
//              NOTE: Called only from CommitObjectInstance ONLY!
//
//  PARAMETERS: lpTask  - Current task.
//              pGKOper - Pointer to pOper struct that returns GKhandler oper.
//
//  RETURNS:    0           - Instance committed successfully
//              zCALL_ERROR - Error committing object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT
fnGetGKHandlerOper( zVIEW       vSubtask,
                    LPTASK      lpTask,
                    LPGKHANDLER hGKHandler,
                    zlpPGKHOPER pOperReturn )
{
   LPGKHANDLER      lpGKHandler;
   LPTASKGKHANDLER  lpTaskGKHandler;
   LPLIBRARY        hLibrary;
   zPGKHOPER        pGKOper;
   zSHORT           nRC;
   zLONG            lProcessID = SysGetProcessID( 0 );

   lpGKHandler = zGETPTR( hGKHandler );

   // Make sure DBHandler can be found.
   if ( lpGKHandler == 0 )
   {
      // "KZOEE081 - Object Definition does not have a Genkey handler
      // specified"
      fnIssueCoreError( lpTask, vSubtask, 8, 81, 0, 0, 0 );
      return( zCALL_ERROR );
   }

   // See if GKHandler has already been invoked for this task.
   for ( lpTaskGKHandler = zGETPTR( lpTask->hFirstTaskGKHandler );
         lpTaskGKHandler;
         lpTaskGKHandler = zGETPTR( lpTaskGKHandler->hNextTaskGKHandler ) )
   {
      if ( lpTaskGKHandler->lProcessID != lProcessID )
         continue;

      if ( lpTaskGKHandler->hGKHandler != hGKHandler )
         continue;

      // If we get here we found the GKHandler that we want.
      break;
   }

   // If TaskGKHandler wasn't found, then this is the first time the
   // GKHandler has been called for this task.
   if ( lpTaskGKHandler )
   {
      // The task DBHandler was found--return pointer to DBHandler routine.
      pGKOper = lpTaskGKHandler->pfGKHandlerOper;
   }
   else
   {
      zCHAR  szFuncName[ 30 ];
      zPVOID hTaskGKHandler;

      // Load the DBHandler library.  If it can't be found, return with error.
      if ( zstrncmp( lpGKHandler->szName, "KZ", 2 ) == 0 )
      {
         // If handler name starts with KZ, then load handler from Zeidon
         // bin directory.
         zCHAR szLibName[ 100 ];

         strcpy_s( szLibName, zsizeof( szLibName ), AnchorBlock->szZeidonBin );
         strcat_s( szLibName, zsizeof( szLibName ), lpGKHandler->szName );

         TraceLineS( "(oi) Attempting to load GK-handler as ", szLibName );
         hLibrary = SysLoadLibrary( vSubtask, szLibName );
      }
      else
      {
         TraceLineS( "(oi) Attempting to load GK-handler as ",
                     lpGKHandler->szName );
         hLibrary = SysLoadLibrary( vSubtask, lpGKHandler->szName );
      }

      if ( hLibrary == 0 )
         return( zCALL_ERROR );

      pGKOper = (zPGKHOPER) SysGetProc( hLibrary, "GKH_MsgProc" );
      if ( pGKOper == 0 )
      {
         // Try the old style name.
         strcpy_s( szFuncName, zsizeof( szFuncName ), lpGKHandler->szName );
         strcat_s( szFuncName, zsizeof( szFuncName ), "_GKH_MsgProc" );

         // Find the address of entry func.  If it can't be found, return with
         // an error.
         pGKOper = (zPGKHOPER) SysGetProc( hLibrary, szFuncName );
         if ( pGKOper == 0 )
            return( zCALL_ERROR );
      }

      // Call gkhandler routine to issue start of transaction.  Bomb out if it doesn't work.
      nRC = (*pGKOper)( DBH_Init, vSubtask, 0, 0, 0 );
      if ( nRC < 0 )
         return( zCALL_ERROR );

      // Create TaskGKHandler object and attatch to Task.
      hTaskGKHandler = fnAllocDataspace( lpTask->hFirstDataHeader,
                                         sizeof( TaskGKHandlerRecord ), 1, 0,
                                         iTaskGKHandler );
      lpTaskGKHandler = zGETPTR( hTaskGKHandler );
      if ( lpTaskGKHandler == 0 )
         return( zCALL_ERROR );

      lpTaskGKHandler->hLibrary        = hLibrary;
      lpTaskGKHandler->pfGKHandlerOper = pGKOper;
      lpTaskGKHandler->hGKHandler      = hGKHandler;
      lpTaskGKHandler->lProcessID      = lProcessID;

      // Insert lpTaskGKHandler into lpTask chain.
      lpTaskGKHandler->hNextTaskGKHandler = lpTask->hFirstTaskGKHandler;
      lpTask->hFirstTaskGKHandler = hTaskGKHandler;

   }  // if ( lpTaskGKHandler )...else...

   *pOperReturn = pGKOper;

   return( 0 );

} // fnGetGKHandlerOper

#if 0
LPGKHANDLER LOCALOPER
fnGetGKHandler( LPTASK  hTask,
                zCPCHAR cpcGKHandlerName )
{
   LPGKHANDLER   lpGKHandler;
   LPTASK        lpTask = zGETPTR( hTask );

   lpGKHandler = zGETPTR( lpTask->hFirstGKHandler );
   while ( lpGKHandler )
   {
      if ( zstrcmp( lpGKHandler->szName, cpcGKHandlerName ) == 0 )
         break;

      lpGKHandler = zGETPTR( lpGKHandler->hNextGKHandler );
   }

   lpTask = zGETPTR( hTask );
   if ( lpGKHandler == 0 )
   {
      // Create GKHandlerTask object and attach to Task.
      LPGKHANDLER hGKHandler = fnAllocDataspace( lpTask->hFirstDataHeader,
                                                 sizeof( GKHandlerRecord ),
                                                 1, 0, iGKHandler );
      lpGKHandler = zGETPTR( hGKHandler );
      if ( lpGKHandler == 0 )
         return( 0 );  // could not allocate memory

      lpGKHandler->hTask           = hTask;
   // if ( hTask == 0 )
   // {
   //    zSHORT nRC = 0;
   //    nRC /= nRC;
   // }

      lpGKHandler->hLibrary        = 0;
      lpGKHandler->pfGKHandlerOper = 0;
      strcpy_s( lpGKHandler->szName, cpcGKHandlerName );

      // Insert lpGKHandler into GKHandler chain.
      lpGKHandler->hNextGKHandler = lpTask->hFirstGKHandler;
      lpTask->hFirstGKHandler = hGKHandler;
   }

   // lpGKHandler is good at this point.  Now we need to ensure that we
   // have loaded the correct handler library.
   if ( lpGKHandler->hLibrary == 0 )
   {
      LPLIBRARY  hLibrary;
      zVIEW      vTask;
      zCHAR      szFuncName[ zZEIDON_NAME_LTH + 1 ];

      vTask = zGETPTR( lpTask->hFirstView );
      SysMutexLock( vTask, "Zeidon GKH", 0, 0 );

      // Load the GKHandler library.  If it can't be found, return with error.
      if ( zstrncmpi( lpGKHandler->szName, "KZ", 2 ) == 0 )
      {
         // If handler name starts with KZ, then load handler from Zeidon
         // bin directory.
         zCHAR szLibName[ zMAX_FILENAME_LTH + 1 ];

         strcpy_s( szLibName, zsizeof( szLibName ), AnchorBlock->szZeidonBin );
         strcat_s( szLibName, zsizeof( szLibName ), lpGKHandler->szName );

         TraceLineS( "(oi) Attempting to load GK-handler as ", szLibName );
         hLibrary = SysLoadLibrary( vTask, szLibName );
      }
      else
      {
         TraceLineS( "(oi) Attempting to load GK-handler as ",
                     lpGKHandler->szName );
         hLibrary = SysLoadLibrary( vTask, lpGKHandler->szName );
      }

      if ( hLibrary )
      {
         lpGKHandler->hLibrary = hLibrary;

         // Define entry function name.  First try the default name.
         lpGKHandler->pfGKHandlerOper =
                           (zPGKHOPER) SysGetProc( hLibrary, "GKH_MsgProc" );
         if ( lpGKHandler->pfGKHandlerOper == 0 )
         {
            // Couldn't find the default name.  Try the old-style name.
            strcpy_s( szFuncName, zsizeof( szFuncName ), lpGKHandler->szName );
            strcat_s( szFuncName, zsizeof( szFuncName ), "_GKH_MsgProc" );

            // Find the address of entry func.
            lpGKHandler->pfGKHandlerOper =
                             (zPGKHOPER) SysGetProc( hLibrary, szFuncName );
         }
      }

      SysMutexUnlock( vTask, "Zeidon GKH", 0 );
   }

   return( lpGKHandler );
}

//./ ADD NAME=fnGetGKHandlerOper
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnGetGKHandlerOper
//
//  PURPOSE:    To retrieve the GKHandler Oper.
//
//              NOTE: Called only from CommitObjectInstance ONLY!
//
//  PARAMETERS: lpTask  - Current task.
//              pGKOper - Pointer to pOper struct that returns GKhandler oper.
//
//  RETURNS:    0           - Handler returned successfully
//              zCALL_ERROR - Error locating handler
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT
fnGetGKHandlerOper( zVIEW       lpView,
                    LPTASK      lpTask,
                    LPGKHANDLER lpGKHandler,
                    zlpPGKHOPER pOperReturn )
{
   LPTASK          hTask;
   zLONG           lProcessID;
   zSHORT          nRC = zCALL_ERROR;

// SysMessageBox( 0, "Get GKH", "fnGetGKHandlerOper", 0 );

   *pOperReturn = 0;  // initialize

   lProcessID = SysGetProcessID( 0 );
   hTask = zGETHNDL( lpTask );

#if 0
   if ( g_vDefaultTaskView && hTask != g_vDefaultTaskView->hTask )
   {
      TraceLine( "GetGKHandlerOper RESETTING task from: 0x%08x  to: 0x%08x",
                 hTask, g_vDefaultTaskView->hTask );
      hTask = g_vDefaultTaskView->hTask;
      lpTask = zGETPTR( hTask );
   }
#endif

   // Make sure GKHandler can be found.
   if ( lpGKHandler == 0 )
   {
      // "KZOEE081 - Object Definition does not have a Genkey handler
      // specified".
      fnIssueCoreError( lpTask, lpView, 8, 81, 0, 0, 0 );
      return( zCALL_ERROR );
   }

   // If it can't be found, return with an error.
   if ( lpGKHandler->pfGKHandlerOper )
   {
      // Call GKHandler routine to issue start of transaction.  Bomb out
      // if it doesn't work.
      nRC = (*(lpGKHandler->pfGKHandlerOper))( DBH_Init, lpView, 0, 0, 0 );
      if ( nRC < 0 )
         nRC = zCALL_ERROR;   // error!
      else
         *pOperReturn = lpGKHandler->pfGKHandlerOper;
   }

// TraceLine( "fnGetGKHandlerOper in Process: %d   looking for GKHandler: 0x%08x for Task: %d (0x%08x)   Name: %s",
//            lProcessID, zGETHNDL( lpGKHandler ), hTask, hTask, lpGKHandler->szName );

   return( nRC );

} // fnGetGKHandlerOper
#endif

//./ ADD NAME=CommitObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CommitObjectInstance
//
//  PURPOSE:    To commit an Object instance from memory
//
//  DESCRIPTION: See CommitMultipleOIs
//
//  PARAMETERS: lpView - View of the Object Instance to commit.
//
//  RETURNS:    0           - Instance committed successfully
//          zDUPLICATE_ROOT - An attempt was made to insert a root entity
//                            that already exists on the database.
//   zOPTIMISTIC_LOCK_ERROR - OI has changed on the database.
//        zCONSTRAINT_ERROR - Constraint violation
//              zCALL_ERROR - Error committing object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
CommitObjectInstance( zVIEW  lpView )
{
   ViewClusterRecord ViewCluster;
   LPTASK            lpCurrentTask;
   zSHORT            nRC;

   // If task not active or disabled, or view invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iCommitObjectInstance, lpView,
                                          zVALID_VIEW )) == 0 )
   {
      return( zCALL_ERROR );
   }

   ViewCluster.vOI      = lpView;
   ViewCluster.lControl = 0;

   // Call commit multiple.  We use "-1" to tell commit multiple that it is
   // being called from CommitObjectInstance.
   nRC = CommitMultipleOIs( &ViewCluster, 1, (zPSHORT) -1, 0 );
   fnOperationReturn( iCommitObjectInstance, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=CreateViewCluster
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       CreateViewCluster
//
//  PURPOSE:     Used by VML apps to create a view array to be used with
//               CommitMultipleOIs.
//
//  PARAMETERS: lpArray - Pointer to integer which will hold the pointer
//              to the view array.
//
//  RETURNS:    0 if OK.
//              zCALL_ERROR if error.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
CreateViewCluster( zVIEW vTaskView, zPLONG lpArray )
{
   LPVIEWCLUSTER pv;
   LPTASK        lpTask = zGETPTR( vTaskView->hTask );
   zPVOID        h;
   zLONG         lCnt;

   if ( lpTask == 0 )
      return( zCALL_ERROR );

   lCnt = zCLUSTER_VIEW_COUNT;

   // Allocate space and set it to all 0s.  Allocate enough space for all the
   // views + 1.  This will allow AddViewToViewArray( ) to know when it's
   // reached the end of the list.
   h = fnAllocDataspace( lpTask->hFirstDataHeader,
                         sizeof( ViewClusterRecord ) * (zULONG) (lCnt + 1),
                         TRUE, 0, iCluster );
   pv = (LPVIEWCLUSTER) zGETPTR( h );

   if ( pv )
   {
      // At the end of the array set the last view to -1.
      pv[ lCnt ].vOI = (zVIEW) -1;
   }

   *lpArray = (zLONG) pv;

   return( 0 );
}

//./ ADD NAME=AddToViewCluster
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       AddToViewCluster
//
//  PURPOSE:     Used by VML apps to manipulate a view array to be used with
//               CommitMultipleOIs.
//
//  PARAMETERS: lArray - Value returned from CreateViewCluster.
//              lpView - View to add to array.
//
//  RETURNS:    Index of view.
//              zCALL_ERROR if too many views added to the array.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
AddToViewCluster( zLONG lArray, zVIEW lpView, zLONG lControl )
{
   LPTASK        lpCurrentTask = zGETPTR( lpView->hTask );
   LPVIEWCLUSTER pv = (LPVIEWCLUSTER) lArray;
   LPVIEWCSR     lpViewCsr;
   LPVIEWOI      hViewOI;
   zSHORT        nIdx;

   // If task not active or disabled, or view invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iAddToViewCluster, lpView,
                                          zVALID_VIEW )) == 0 )
   {
      return( zCALL_ERROR );
   }

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   if ( lpViewCsr == 0 )
   {
      SysMessageBox( lpView, szlOE_SystemError, "View doesn't have an OI", 0 );
      fnOperationReturn( iAddToViewCluster, lpCurrentTask );
      return( -1 );
   }

   hViewOI = lpViewCsr->hViewOI;

   // Look for the first 0 (e.g. empty) cell in the array. If we find one
   // that is -1, then we've reached the end of the list so end with error.
   for ( nIdx = 0; pv[ nIdx ].vOI; nIdx++ )
   {
      if ( pv[ nIdx ].vOI == (zVIEW) -1 )
      {
         // "KZOEE087 - Too many views in View array"
         fnIssueCoreError( lpCurrentTask, lpView, 8, 87, 0, 0, 0 );
         fnOperationReturn( iAddToViewCluster, lpCurrentTask );
         return( zCALL_ERROR );
      }
   }

   pv[ nIdx ].vOI      = lpView;
   pv[ nIdx ].lControl = lControl;

   fnOperationReturn( iAddToViewCluster, lpCurrentTask );
   return( nIdx );
}

//./ ADD NAME=AppendViewCluster
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       AddToViewCluster
//
//  PURPOSE:     Append the contents of one view cluster to another.
//               Thereafter the source cluster is freed and must not be
//               used any more.
//
//  PARAMETERS: lTargetArray - Target Cluster
//              lSourceArray - Source Cluster
//
//  RETURNS:    original size of target cluster - can be added to
//              any index in source cluster to obtain the index in the
//              new target cluster;
//              zCALL_ERROR if too many views added to the array.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
AppendViewCluster( zLONG lTargetArray, zLONG lSourceArray )
{
   LPVIEWCLUSTER pvTarget = (LPVIEWCLUSTER) lTargetArray;
   LPVIEWCLUSTER pvSource = (LPVIEWCLUSTER) lSourceArray;
   zLONG  k;
   zSHORT n;
   zSHORT nRC = 0;

   for ( k = 0; pvSource[ k ].vOI; k++ )
   {
      if ( pvSource[ k ].vOI == (zVIEW) -1 )
         break; // this is the end of the array

      n = AddToViewCluster( lTargetArray,
                            pvSource[ k ].vOI, pvSource[ k ].lControl );
      if ( n < 0 )
         return( zCALL_ERROR );

      if ( k == 0 )
         nRC = n; // first index is the Offset of appended cluster
   }

   fnFreeDataspace( pvSource );
   return( nRC );
}

//./ ADD NAME=AddViewToViewCluster
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       AddViewToViewCluster
//
//  PURPOSE:     Used by VML apps to manipulate a view array to be used with
//               CommitMultipleOIs.
//
//  PARAMETERS: lArray - Value returned from CreateViewCluster.
//              lpView - View to add to array.
//
//  RETURNS:    Index of view.
//              zCALL_ERROR if too many views added to the array.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
AddViewToViewCluster( zLONG lArray, zVIEW lpView )
{
   return( AddToViewCluster( lArray, lpView, 0 ) );
}

//./ ADD NAME=DropViewCluster
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       DropViewCluster
//
//  PURPOSE:     Drop the view cluster.
//
//  PARAMETERS: lArray - Value returned from CreateViewCluster.
//
//  RETURNS:    Index of view.
//              zCALL_ERROR if too many views added to the array.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
DropViewCluster( zLONG lArray )
{
   LPTASK        lpCurrentTask = 0;
   LPVIEWCLUSTER lpViewCluster = (LPVIEWCLUSTER) lArray;
   zSHORT        idx;

   // Loop through each of the OI's in the cluster.  If the vOI value is
   // -1 then we've reached the end of the view cluster.
   for ( idx = 0; lpViewCluster[ idx ].vOI != (zVIEW) -1; idx++ )
   {
      if ( lpViewCluster[ idx ].vOI == 0 )
         continue;

      // Retrieve the task if we haven't done it already.
      if ( lpCurrentTask == 0 &&
           (lpCurrentTask = fnOperationCall( iDropViewCluster,
                                             lpViewCluster[ idx ].vOI, 0 )) == 0 )
      {
         return( zCALL_ERROR );
      }

      if ( lpViewCluster[ idx ].lControl & zCOMMIT_DROPOBJECTINSTANCE )
         DropObjectInstance( lpViewCluster[ idx ].vOI );
      else
      if ( lpViewCluster[ idx ].lControl & zCOMMIT_DROPVIEW )
         DropView( lpViewCluster[ idx ].vOI );
   }

   fnFreeDataspace( lpViewCluster );

   if ( lpCurrentTask )
      fnOperationReturn( iDropViewCluster, lpCurrentTask );

   return( 0 );
}

//./ ADD NAME=CommitMultipleOIs
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CommitMultipleOIs
//
//  PURPOSE:    To commit multiple OIs in one transaction with control flags.
//
//  DESCRIPTION: This operation applies all updates for an object
//               instance to the database by issuing Relationship Deletes,
//               Deletes, Inserts, Relationship Inserts, and
//               Updates to the database handler associated with the
//               object. After all messages are complete, a Commit or
//               Rollback message is sent to commit or rollback
//               the transaction. NOTE: All cursors in any view
//               for the object instance which were in an undefined
//               state (i.e. on a deleted instance) ARE RESET!!!.
//               Otherwise, all cursors are preserved in their
//               pre-commit state.
//
//               Note that if one commit fails then all commits are assumed
//               to have failed and commit processing stop immediately.
//
//  PARAMETERS: lpViewArray   - Pointer to an array of views.
//              nViewCount    - Number of views in array.  If it's 0 then
//                              assume that the array is null-terminated.
//              nViewErrorIdx - Pointer to index of view that returned with an
//                              error. Undefined if no error.  Optional.
//              lControl      - Control certain aspects of Commit.
//
//                zCOMMIT_NOCLEANUP     0x00000100
//                   Keeps Core from cleaning up deleted/excluded entities
//                   after the commit is finished.  Used only internally.
//
//  RETURNS:    0           - All Instances committed successfully
//          zDUPLICATE_ROOT - An attempt was made to insert a root entity
//                            that already exists on the database.
//   zOPTIMISTIC_LOCK_ERROR - OI has changed on the database.
//        zCONSTRAINT_ERROR - Constraint violation
//              zCALL_ERROR - Error committing object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
CommitMultipleOIs( LPVIEWCLUSTER lpOrigViewCluster,
                   zSHORT        nViewCount,
                   zPSHORT       pnViewErrorIdx,
                   zLONG         lControl )
{
   LPVIEWCLUSTER     lpViewCluster = 0;
   VIEWARRAYBLOCK    tViewArrayBlock = { 0 };
   LPTASK            lpCurrentTask;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;
   LPVIEWOD          lpViewOD;
   zPCHAR            pchNetworkName = 0;
   zVIEW             vReferenceView;
   zVIEW             *lpViewArray = 0;
   zLONG             lTickCount;
   zBOOL             bNetworkCommit = FALSE;
   zBOOL             bLockingSemaphoreCreatedHere = FALSE;
   zBOOL             bDropPessimisticLocks = FALSE;
   zSHORT            iOpID;
   zSHORT            k;
   zSHORT            nRC;
   zSHORT            nReturn = zCALL_ERROR;

   if ( AnchorBlock->TraceFlags.bOI_Times )
      lTickCount = SysGetTickCount( );

   // If nViewCount is 0 then determine number of views by counting non-zero
   // views.
   if ( nViewCount == 0 )
   {
      // The list can be terminated by either a 0 or -1.  The -1 might be
      // set by CreateEmptyViewCluster( ) above.
      while ( TRUE )
      {
         if ( lpOrigViewCluster[ nViewCount ].vOI == 0 )
            break;

         if ( lpOrigViewCluster[ nViewCount ].vOI == (zVIEW) -1 )
            break;

         nViewCount++;
      }

      // If nViewCount is *still* 0 then just get out.
      if ( nViewCount == 0 )
      {
         if ( pnViewErrorIdx )
            *pnViewErrorIdx = -1;

         return( 0 );
      }
   }

   if ( pnViewErrorIdx == (zPSHORT) -1 )
   {
      iOpID = iCommitObjectInstance;
      pnViewErrorIdx = 0;
      lpCurrentTask = zGETPTR( lpOrigViewCluster[ 0 ].vOI->hTask );
   }
   else
   {
      iOpID = iCommitMultipleOIs;

      // If task not active or disabled, or view invalid, return zCALL_ERROR.
      for ( k = 0; k < nViewCount; k++ )
      {
         if ( lpOrigViewCluster[ k ].vOI )
            break;
      }

      if ( (lpCurrentTask = fnOperationCall( iOpID,
                                             lpOrigViewCluster[ k ].vOI, 0 )) == 0 )
      {
         return( zCALL_ERROR );
      }
   }

// TraceLineI( "CommitMultipleOIs: ENTRY OperationID: ", iOpID );

   lpViewCluster = fnAllocDataspace( lpCurrentTask->hFirstDataHeader,
                                     sizeof( ViewClusterRecord ) * (zULONG) nViewCount,
                                     TRUE, 0, iCluster );
   lpViewCluster = zGETPTR( lpViewCluster );

   // Create temporary views so core can muck with the cursors.
   for ( k = 0; k < nViewCount; k++ )
   {
      LPVIEWCSR  lpViewCsr;
      LPVIEWOI   hViewOI;
      zLONG      j;

      if ( lpOrigViewCluster[ k ].vOI == 0 )
         continue;

      lpViewCsr = zGETPTR( lpOrigViewCluster[ k ].vOI->hViewCsr );
      if ( lpViewCsr == 0 )
         continue; // should never occur

      hViewOI = lpViewCsr->hViewOI;

      // Make sure the OI isn't already part of the cluster.
      for ( j = 0; j < k; j++ )
      {
         if ( lpOrigViewCluster[ j ].vOI == 0 )
            continue;

         lpViewCsr = zGETPTR( lpOrigViewCluster[ j ].vOI->hViewCsr );
         if ( lpViewCsr == 0 )
            continue; // should never occur

         if ( lpViewCsr->hViewOI == hViewOI )
         {
            // it is already in cluster, so skip it for commit
            hViewOI = 0; // just to indicate skipping
            break;
         }
      }

      if ( hViewOI == 0 )
         continue; // skip, because OI already found in cluster

      CreateViewFromViewForTask( &lpViewCluster[ k ].vOI,
                                 lpOrigViewCluster[ k ].vOI, 0 );
   }

   if ( fnInitViewArrayBlock( &tViewArrayBlock, nViewCount ) != 0 )
   {
      if ( iOpID == iCommitMultipleOIs )
         fnOperationReturn( iOpID, lpCurrentTask );

      return( zCALL_ERROR );
   }

   lpViewArray = tViewArrayBlock.pvArray;

   // Verify that all the views are OK.
   for ( k = 0; k < nViewCount; k++ )
   {
      // We allow NULL views.  This is mostly because fnNetProcessCommit might
      // send us an array containing null views.
      if ( lpViewCluster[ k ].vOI == 0 )
         continue;

      if ( fnValidViewCsr( lpCurrentTask, lpViewCluster[ k ].vOI ) == 0 )
      {
         if ( pnViewErrorIdx )
            *pnViewErrorIdx = k;

         goto EndOfFunction;
      }

      lpViewArray[ k ] = lpViewCluster[ k ].vOI;

      lpViewCsr = zGETPTR( lpViewArray[ k ]->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
      lpViewOD  = zGETPTR( lpViewArray[ k ]->hViewOD );

      // Check to see if this is a network commit.
      if ( lpViewOD->szNetwork &&
           (lpViewOI->lActivateControl & zACTIVATE_LOCAL) == 0 )
      {
         pchNetworkName = lpViewOD->szNetwork;
      }

      // If lControl for commit is zCOMMIT_DROPLOCKSONLY then turn on the flag
      // for each of the views.
      if ( lControl & zCOMMIT_DROPLOCKSONLY )
         lpViewCluster[ k ].lControl |= zCOMMIT_DROPLOCKSONLY;

      // If we're only committing the objects to drop the locks then we don't
      // want to commit this OI so set lpViewArray to 0.
      if ( lpViewCluster[ k ].lControl & zCOMMIT_DROPLOCKSONLY )
      {
         // If a network has been specified for this cluster then we *don't*
         // want to zero out the view because we want to send it the server.
         if ( pchNetworkName == 0 || *pchNetworkName == 0 )
            lpViewArray[ k ] = 0;
         else
            vReferenceView = lpViewArray[ k ];  // dks donc jb  2004.11.02

         continue;
      }

      // If OI is read-only then forget it.
      if ( lpViewOI->bReadOnly )
      {
         LPTASK lpTask = zGETPTR( lpViewArray[ k ]->hTask );
         if ( pnViewErrorIdx )
            *pnViewErrorIdx = k;

         // "KZOEE079 - Trying to commit a read-only view".
         fnIssueCoreError( lpTask, lpViewArray[ k ], 8, 79, 0,
                           "Object Name = ", lpViewOD->szName );
         goto EndOfFunction;
      }

      // Make sure OI does not contain versioned instances
      if ( lpViewOI->nVersionedInstances )
      {
         LPTASK lpTask = zGETPTR( lpViewArray[ k ]->hTask );
         if ( pnViewErrorIdx )
            *pnViewErrorIdx = k;

         //  "KZOEE076 - Object instance contains versioned entity instances"
         fnIssueCoreError( lpTask, lpViewArray[ k ], 8, 76, 0, 0, 0 );
         goto EndOfFunction;
      }

      // Make sure that the view has an object instance.
      if ( lpViewOI->hRootEntityInstance == 0 )
      {
         // Set array value to 0 to indicate that we don't need to commit
         // this view.
         lpViewArray[ k ] = 0;
         continue;
      }

      // If OI hasn't been updated then forget about it UNLESS...
      // there is pessimistic locking.  Then we need to continue so that any
      // pessimistic locks are dropped.
      if ( lpViewOI->bUpdated == FALSE &&
           (lpViewOI->lActivateControl & zACTIVATE_WITH_LOCKING) == 0 )
      {
         // Set array value to 0 to indicate that we don't need to commit
         // this view.
         lpViewArray[ k ] = 0;
         continue;
      }

      // Check to see if we need pessimistic locks on this view.
      if ( lpViewOI->bIsLocked && (lControl & zCOMMIT_KEEPLOCKS) == 0 )
         bDropPessimisticLocks = TRUE;

      vReferenceView = lpViewArray[ k ];
   }

   // Make sure that at least one view is being committed.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewArray[ k ] )
         break;

      if ( lpViewCluster[ k ].lControl & zCOMMIT_DROPLOCKSONLY )
         break;
   }

   if ( k == nViewCount )
   {
      // No non-zero views found so forget it.
      nReturn = 0;
      goto EndOfFunction;
   }

#ifdef __ACTIVATE_CONSTRAINTS__
   if ( (lControl & zCOMMIT_NOCONSTRAINTS) == 0 )
   {
      for ( k = 0; k < nViewCount; k++ )
      {
         zSHORT nState;

         // Don't worry about null views.
         if ( lpViewArray[ k ] == 0 )
            continue;

         // If this view is only dropping the pessimistic locks then don't
         // call the constraint.
         if ( lpViewCluster[ k ].lControl & zCOMMIT_DROPLOCKSONLY )
            continue;

         lpViewOD = zGETPTR( lpViewArray[ k ]->hViewOD );

         // If object has commit constraint active, check for objections.
         // If any exit...
         if ( lpViewOD->bCommitConstraint == FALSE )
            continue;

         nState = 0;
         if ( lpCurrentTask->bShutdown )
            nState += zOCE_STATE_SHUTDOWN;

         nRC = fnInvokeOCEOperation( lpViewArray[ k ], lpCurrentTask,
                                     zOCE_COMMIT, nState );
         if ( nRC )
         {
            if ( pnViewErrorIdx )
               *pnViewErrorIdx = k;

            nReturn = nRC;
            goto EndOfFunction;
         }
      }
   }
#endif

   if ( pchNetworkName && *pchNetworkName )
   {
      // Network Commit

      // First make sure the network is active.
      if ( NetStatus( vReferenceView, pchNetworkName ) == 0 )
      {
         if ( NetStartup( vReferenceView, pchNetworkName, pchNetworkName ) != 0 )
         {
            TraceLineS( "(oi) Can't start network = ", pchNetworkName );
            MessageSend( vReferenceView, "xx", "KZOEOIAA",
                        "Network cannot be started.",
                        zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );

            goto EndOfFunction;
         }
      }

      nRC = NetCommitOI( pchNetworkName, 0, lpViewCluster,
                         lpViewArray, nViewCount, pnViewErrorIdx, lControl );

#ifdef DEBUG
      if ( nRC == 0 )
      {
         for ( k = 0; k < nViewCount; k++ )
         {
            LPENTITYINSTANCE lpEntityInstance;
            LPVIEWENTITY     lpViewEntity;

            if ( lpViewArray[ k ] == 0 )
               continue;

            lpViewCsr = zGETPTR( lpViewArray[ k ]->hViewCsr );
            lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

            for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
                  lpEntityInstance;
                  lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
            {
               lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

               if ( lpViewEntity->bDerivedPath == FALSE &&
                    ((lpEntityInstance->u.nInd.bCreated  &&
                      lpEntityInstance->u.nInd.bDeleted == FALSE &&
                      lpViewEntity->bCreate)                  ||
                     (lpEntityInstance->u.nInd.bUpdated  &&
                      lpEntityInstance->u.nInd.bDeleted == FALSE &&
                      lpViewEntity->bUpdate)                  ||
                     (lpEntityInstance->u.nInd.bDeleted  &&
                      lpEntityInstance->u.nInd.bCreated == FALSE &&
                      lpViewEntity->bDelete))
/*
               ||   (lpEntityInstance->u.nInd.bIncluded &&
                     lpViewEntity->bInclude)                 ||
                    (lpEntityInstance->u.nInd.bExcluded &&
                     lpViewEntity->bExclude)
*/
                   )
               {
                  if ( (lControl & zCOMMIT_DROPLOCKSONLY) == 0 )
                  {
                     zCHAR szMsg[ 1024 ];

                     lpViewOD = zGETPTR( lpViewArray[ k ]->hViewOD );

                     TraceLineS( "(oi) Warning ============================", "" );
                     TraceLineS( "(oi) Object definition = ", lpViewOD->szName );
                     TraceLineS( "(oi) Entity name = ", lpViewEntity->szName );
                     TraceLineX( "(oi) EI Flags    = ", lpEntityInstance->u.nIndicators );
                     sprintf_s( szMsg, zsizeof( szMsg ), "%s %s Object Definition: %s "
                                 "EntityName: %s   EI Flags 0x%08x",
                               "OE Warning", "Return code indicates that "
                                 "Commit was successful but OI still has "
                                 "instances marked as changed.",
                               lpViewOD->szName,
                               lpViewEntity->szName,
                               lpEntityInstance->u.nIndicators );
                     SysDiagnosticMessage( lpViewArray[ k ], "OE Warning",
                                           szMsg, 1 );
                  }

                  if ( lpViewEntity->bCreate )
                     lpEntityInstance->u.nInd.bCreated = FALSE;

                  // break; Hi DG, was this the bug ??? **HH**
               }
            } // for...

         } // for k...
      }
#endif

      nReturn = nRC;
      goto EndOfFunction;
   }

   // Check to see if any OIs where activated using pessimistic locking.  If
   // so then we need to create the pessimistic lock semaphore record for the
   // current task (unless it's already been created).
   if ( bDropPessimisticLocks &&
        lpCurrentTask->bPessimisticLockingSet == FALSE )
   {
      // Returns: 0 - everything OK;  1 - Semaphore not needed.
      nRC = fnCreatePessimisticSemaphore( lpCurrentTask,
                                          (zPVOID) lpViewCluster,
                                          nViewCount, pnViewErrorIdx, 0 );
      if ( nRC < 0 )
         goto EndOfFunction;  // oops...error.

      if ( nRC == 0 )
         bLockingSemaphoreCreatedHere = TRUE;
   }

   // Commit all the object instances in the array.
   nReturn = fnCommitObjectInstance( lpViewCluster, lpViewArray, nViewCount,
                                     pnViewErrorIdx, lpCurrentTask,
                                     lControl, &tViewArrayBlock );

   if ( bLockingSemaphoreCreatedHere )
      fnDeletePessimisticSemaphore( lpCurrentTask, (zPVOID) lpViewCluster,
                                    nViewCount, pnViewErrorIdx, 0 );

EndOfFunction:
   if ( lpViewCluster )
   {
      // Drop the temporary views.
      for ( k = 0; k < nViewCount; k++ )
      {
         if ( lpViewCluster[ k ].vOI )
            fnDropView( lpViewCluster[ k ].vOI );
      }

      fnFreeDataspace( lpViewCluster );
   }

   // free the VIEWARRAYBLOCK areas
   fnFreeViewArrayBlock( &tViewArrayBlock );

   if ( AnchorBlock->TraceFlags.bOI_Times )
   {
      zCHAR sz[ 30 ];

      sprintf_s( sz, zsizeof( sz ), "%lf seconds",
                 (double) (SysGetTickCount( ) - lTickCount) / zTICKS_PER_SECOND );
      TraceLineS( "(oi) Total time for CommitMultipleOIs = ", sz );
   }

   if ( iOpID == iCommitMultipleOIs )
      fnOperationReturn( iOpID, lpCurrentTask );

// TraceLineI( "CommitMultipleOIs: EXIT OperationID: ", iOpID );
   return( nReturn );

} // CommitMultipleOIs

//./ ADD NAME=CommitMultipleObjectInstances
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:       CommitMultipleObjectInstances
//
//  PURPOSE:     Used as a simple VML interface to call CommitMultipleOIs.
//
//  PARAMETERS: lArray - Value returned from CreateViewCluster.
//              lpErrorIndex - Pointer to hold integer value identifying
//              the view that caused an error if the commit fails.
//
//  RETURNS:    Normal CommitObjectInstance return codes.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
CommitMultipleObjectInstances( zLONG lpArray, zPLONG lpErrorIndex )
{
   zSHORT nIndex;
   zSHORT nRC;

   nRC = CommitMultipleOIs( (LPVIEWCLUSTER) lpArray, 0, &nIndex, 0 );
   *lpErrorIndex = (zLONG) nIndex;

   return( nRC );
}

// Copies all foreign keys to/from lpEntityInstance.  This should only be
// called for SQL databases.
//
// If bCheckLinked is TRUE then don't try setting instances linked to
// lpEntityInstance.
//
// Returns 0 if everything OK.
//         1 if the FK couldn't be set because the source hasn't been set.
//
// Example:
//    Given the entity instance:    A        A-B,A-D is one-to-many.
//                                 / \       B & C are recursive.
//                                B   D      D-E is many-to-one.
//                                |   |
//                                C   E
//
//    maybe more later...
//
zSHORT LOCALOPER
fnSetForeignKeysForInstance( LPENTITYINSTANCE lpEntityInstance )
{
   LPVIEWENTITY   lpViewEntity;
   LPDATARECORD   lpDataRecord;
   LPRELRECORD    lpRelRecord;
   LPRELFIELD     lpRelField;
   LPVIEWOI       lpViewOI;
   LPTASK         lpTask;

   lpViewOI = zGETPTR( lpEntityInstance->hViewOI );

   // Get Task owning the view object instance
   lpTask = zGETPTR( lpViewOI->hAllocTask );

   lpEntityInstance->u.nInd.bForeignKeys = 0;

   lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
   if ( lpViewEntity->hParent == 0 )
      return( 0 );

   lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );
   lpRelRecord  = zGETPTR( lpDataRecord->hFirstRelRecord );
   if ( lpRelRecord == 0 )
      return( 0 );

   lpRelField   = zGETPTR( lpRelRecord->hFirstRelField );
   if ( lpRelField == 0 )
      return( 0 );

   // For each rel field, check to see if the current entity
   // instance has a foreign key.  If it does, then the value
   // needs to be copied
   for ( ;
         lpRelField;
         lpRelField = zGETPTR( lpRelField->hNextRelField ) )
   {
      LPVIEWATTRIB      lpSrcViewAttrib;
      LPVIEWATTRIB      lpRelViewAttrib;
      LPVIEWENTITY      lpRelViewEntity;
      LPVIEWENTITY      lpSrcViewEntity;
      LPENTITYINSTANCE  lpRelInstance;
      LPENTITYINSTANCE  lpSrcInstance;
      LPDATAFIELD       lpWkDataField;

      // If the rel field doesn't have a data field, then skip it.
      if ( lpRelField->hRelDataField == 0 )
         continue;

      lpWkDataField   = zGETPTR( lpRelField->hSrcDataField );
      lpSrcViewAttrib = zGETPTR( lpWkDataField->hViewAttrib );
      lpWkDataField   = zGETPTR( lpRelField->hRelDataField );
      lpRelViewAttrib = zGETPTR( lpWkDataField->hViewAttrib );
      lpSrcViewEntity = zGETPTR( lpSrcViewAttrib->hViewEntity );
      lpRelViewEntity = zGETPTR( lpRelViewAttrib->hViewEntity );

      // We now have the attributes--the source and relationship (i.e. target)
      // attributes.  One is part of the current entity (lpViewEntity) and
      // the other is a parent of the current entity.  Find the entity
      // instance of the parent entity.

      if ( lpRelViewEntity != lpViewEntity )
      {
         // The relationship entity is different from the current entity.
         // Find the relationship entity instance.
         lpSrcInstance = lpEntityInstance;
         lpRelInstance = zGETPTR( lpEntityInstance->hParent );
         while ( lpRelInstance->hViewEntity != lpRelViewAttrib->hViewEntity )
         {
            LPVIEWENTITY lpWkRelViewEntity =
                                    zGETPTR( lpRelInstance->hViewEntity );

            // DGC 4/8/97
            // If the parent entity we are looking for is a recursive parent,
            // then it's possible that the entity instance we are looking for
            // has an lpViewEntity that is the recursive child entity.
            if ( lpRelViewEntity->bRecursivePar &&
                 lpWkRelViewEntity->bRecursive &&
                 lpWkRelViewEntity->lEREntTok == lpRelViewEntity->lEREntTok )
            {
               break;
            }

            lpRelInstance = zGETPTR( lpRelInstance->hParent );
         }
      } // if ( lpRelViewEntity != lpViewEntity )...
      else
      {
         // The source entity is different from the current entity.
         // Find the source entity instance.
         lpRelInstance = lpEntityInstance;
         lpSrcInstance = zGETPTR( lpEntityInstance->hParent );
         while ( lpSrcInstance->hViewEntity != lpSrcViewAttrib->hViewEntity )
         {
            LPVIEWENTITY lpWkSrcViewEntity =
                                    zGETPTR( lpSrcInstance->hViewEntity );

            // DGC 4/8/97
            // If the parent entity we are looking for is a recursive parent,
            // then it's possible that the entity instance we are looking for
            // has an lpViewEntity that is the recursive child entity.
            if ( lpSrcViewEntity->bRecursivePar &&
                 lpWkSrcViewEntity->bRecursive &&
                 lpWkSrcViewEntity->lEREntTok == lpSrcViewEntity->lEREntTok )
            {
               break;
            }

            lpSrcInstance = zGETPTR( lpSrcInstance->hParent );
         }
      } // if ( lpRelViewEntity != lpViewEntity )...else...

      if ( lpEntityInstance->u.nInd.bCreated ||
           lpEntityInstance->u.nInd.bIncluded )
      {
         zULONG  uLth;
         zPVOID  lpValue;

         // If the source instance hasn't had *IT'S* FKs set then skip this
         // one and try again later.
         if ( lpSrcInstance->u.nInd.bForeignKeys )
         {
            // Turn the flag back on for this instance.
            lpEntityInstance->u.nInd.bForeignKeys = TRUE;
            return( 1 );
         }

         fnGetAttrAddrFromEntityInstance( (zCOREMEM) &lpValue,
                                          &uLth,
                                          lpSrcInstance,
                                          lpSrcViewAttrib );
         fnStoreValueInEntityInstance( lpRelInstance,
                                       lpRelViewEntity,
                                       lpRelViewAttrib,
                                       lpValue, uLth );
      }
      else
      {
         zDECIMAL d;
         zCHAR    s[ 3 ] = "";
         zPVOID   p;

         // Set foreign key to null.
         switch ( lpRelViewAttrib->cType )
         {
            case zTYPE_DECIMAL:
               SysAssignDecimalFromNull( &d );
               p = (zPVOID) &d;
               break;

            case zTYPE_INTEGER:
               p = (zPVOID) &lNullInteger;
               break;

            case zTYPE_STRING:
               p = (zPVOID) s;
               break;

            case zTYPE_DATE:
            case zTYPE_DATETIME:
               p = (zPVOID) &stNullDateTime;
               break;
         }

         // Gig, 10/4/93
         // If the foreign key is a key to the target entity, then
         // we cannot null the key because we would lose the
         // capability of updating the entity (in this case it
         // better be deleted!!!)
         if ( lpRelViewAttrib->bKey == FALSE )
         {
            // HH: p points to correct datatype (set in 'switch' above).
            fnStoreValueInEntityInstance( lpRelInstance,
                                          lpRelViewEntity,
                                          lpRelViewAttrib,
                                          (zPVOID) p, 0 );
         }
      }

      // Turn off the dbh flag to make sure that the DBHandler updates
      // the instance.
      lpRelInstance->u.nInd.bDBHUpdated = FALSE;

   } // for ( lpRelField )...

   return( 0 );

} // fnSetForeignKeysForInstance

// If the EI is flagged as created and the entity doesn't have
// create authority then make sure that there is a linked EI in
// the current cluster that does have create authority.
zVOID LOCALOPER
fnCheckCreateDeleteFlags( LPENTITYINSTANCE lpEntityInstance,
                          zVIEW            lpViewArray[],
                          LPVIEWOD         lpViewOD_Array[],
                          LPVIEWOI         lpViewOI_Array[],
                          zSHORT           nViewCount,
                          zBOOL            bCheckCreate )
{
   LPVIEWENTITY lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
   LPVIEWENTITY lpCandidateViewEntity = 0;
   LPVIEWOD     lpCandidateViewOD = 0;
   LPVIEWOI     lpCandidateViewOI = 0;
   LPVIEWOI     lpViewOI;
   zBOOL        bShowMsg = TRUE;  // We'll assume a problem.
   zSHORT       k;

   // Look for a linked entity instance that has create authority.
   if ( lpEntityInstance->hNextLinked )
   {
      LPENTITYINSTANCE lpLinked;

      for ( lpLinked = zGETPTR( lpEntityInstance->hNextLinked );
            lpLinked != lpEntityInstance;
            lpLinked = zGETPTR( lpLinked->hNextLinked ) )
      {
         LPVIEWENTITY lpLinkedViewEntity;

         // If the EI doesn't have create authority then skip it.
         lpLinkedViewEntity = zGETPTR( lpLinked->hViewEntity );
         if ( bCheckCreate )
         {
            if ( lpLinkedViewEntity->bCreate == FALSE )
               continue;
         }
         else
         {
            if ( lpLinkedViewEntity->bDelete == FALSE )
               continue;
         }

         lpViewOI = zGETPTR( lpLinked->hViewOI );

         // Check to see if the linked EI belongs to one of the
         // OIs in the current cluster.
         for ( k = 0; k < nViewCount; k++ )
         {
            if ( lpViewArray[ k ] == 0 )
               continue;

            if ( lpViewOI == lpViewOI_Array[ k ] )
            {
               // We found a linked EI in the current cluster with
               // create authority.  Everything's OK.
               bShowMsg = FALSE;
               break;
            }
         }

         if ( bShowMsg == FALSE )
            break;

         // If we get here then we've found an EI that has create/delete
         // authority but is not part of an OI in the cluster.
         // This is a candidate for adding to the cluster.
         lpCandidateViewEntity = zGETPTR( lpLinked->hViewEntity );
         lpCandidateViewOD     = zGETPTR( lpViewOI->hViewOD );
         lpCandidateViewOI     = lpViewOI;
      } // for ( lpLinked...)...
   }

   // If bShowMsg is TRUE then we didn't find an EI with create
   // authority in the current cluster.  Show diagnostic message.
   if ( bShowMsg )
   {
      zCHAR    szMsg[ 1000 ];
      zVIEW    lpView = 0;
      LPVIEWOI lpViewOI = zGETPTR( lpEntityInstance->hViewOI );
      LPVIEWOD lpViewOD = zGETPTR( lpViewOI->hViewOD );

      // Find the view that references lpViewOI.
      for ( k = 0; k < nViewCount; k++ )
      {
         LPVIEWCSR lpViewCsr;

         if ( lpViewArray[ k ] == 0 )
            continue;

         lpViewCsr = zGETPTR( lpViewArray[ k ]->hViewCsr );
         if ( lpViewCsr->hViewOI == lpEntityInstance->hViewOI )
         {
            // We found it.
            lpView = lpViewArray[ k ];
            break;
         }
      }

      TraceLineS( "----------------- Warning ----------------", "" );
      sprintf_s( szMsg, zsizeof( szMsg ), "Warning: Trying to commit an entity that "
                "has been %s but does not have %s "
                "authority in the current cluster.  OD.EntityName = %s.%s",
                bCheckCreate ? "created" : "deleted",
                bCheckCreate ? "create" : "delete",
                lpViewOD->szName, lpViewEntity->szName );
      TraceLineS( szMsg, "" );
      TraceLineS( "", "" );

      // List the views in the cluster.
      TraceLineI( "Number of views in the cluster: ", nViewCount );
      for ( k = 0; k < nViewCount; k++ )
      {
         if ( lpViewArray[ k ] == 0 )
         {
            TraceLineS( "   View ID = ", "(null) View not flagged as changed" );
            continue;
         }

         sprintf_s( szMsg, zsizeof( szMsg ), " View ID = %lx, Object name = %s",
                    (zULONG) lpViewArray[ k ], lpViewOD_Array[ k ]->szName );
         TraceLineS( szMsg, "" );
      }


      sprintf_s( szMsg, zsizeof( szMsg ), "%s.%s", lpViewOD->szName, lpViewEntity->szName );
      if ( bCheckCreate )
         TraceLineS( "OD.Entity with Create flag = ", szMsg );
      else
         TraceLineS( "OD.Entity with Delete flag = ", szMsg );
      TraceLineX( "OI ID = ", (zLONG) lpViewOI );

      if ( lpCandidateViewEntity )
      {
         sprintf_s( szMsg, zsizeof( szMsg ), "%s.%s", lpCandidateViewOD->szName,
                   lpCandidateViewEntity->szName );
         TraceLineS( "OD.Entity with create authority = ", szMsg );
         TraceLineX( "OI ID = ", (zLONG) lpCandidateViewOI );
      }

      TraceLineS( "", "" );
      CreateViewFromViewForTask( &lpView, lpView, 0 );
      fnEstablishViewForInstance( lpView, 0, lpEntityInstance );
      DisplayEntityInstancePath( lpView, lpViewEntity->szName );
      sprintf_s( szMsg, zsizeof( szMsg ), "Warning: Trying to commit an entity that "
                "has been %s but does not have %s "
                "authority in the current cluster.  OD.EntityName = %s.%s. "
                "See trace for more information.",
                bCheckCreate ? "created" : "deleted",
                bCheckCreate ? "create" : "delete",
                lpViewOD->szName, lpViewEntity->szName );
      SysDiagnosticMessage( lpView, szlOE_SystemError, szMsg, 1 );
      TraceLineS( "-------------------", "" );
      fnDropView( lpView );
   }
}

zSHORT LOCALOPER
fnInitializeGenKeys( zVIEW       lpViewArray[],
                     zSHORT      nViewCount,
                     zPSHORT     pnViewErrorIdx,
                     LPTASK      lpCurrentTask,
                     zPVIEW      lpKZGKHWOB,
                     zlpPGKHOPER ppGKOper,
                     VIEWARRAYBLOCK *pViewArrayBlock )
{
   LPGKHANDLER      hGKHandler = 0;
   LPVIEWOI         *lpViewOI_Array = pViewArrayBlock->pViewOI_Array;
   LPVIEWOD         *lpViewOD_Array = pViewArrayBlock->pViewOD_Array;
   LPVIEWENTITY     lpLastInsertedViewEntity = 0;
   LPENTITYINSTANCE lpEntityInstance;
   LPTASK           hTask;
   zVIEW            vSubtask;
   zBOOL            bHiddenOnly;
   zBOOL            bSettingFKs;
   zBOOL            *bGenkeyNeededArray = pViewArrayBlock->pbGenkeyNeededArray;
   zBOOL            *bFK_NeededArray = pViewArrayBlock->pbFK_NeededArray;
   zSHORT           nDebugCnt;
   zSHORT           k;
   zSHORT           nRC;

   // Set up support arrays.
   for ( k = 0; k < nViewCount; k++ )
   {
      LPVIEWCSR lpViewCsr;

      if ( lpViewArray[ k ] == 0 )
         continue;

      lpViewOD_Array[ k ] = zGETPTR( lpViewArray[ k ]->hViewOD );
      lpViewCsr = zGETPTR( lpViewArray[ k ]->hViewCsr );
      lpViewOI_Array[ k ] = zGETPTR( lpViewCsr->hViewOI );
   }

   // We'll use one of the views as a subtask view.
   // vSubtask is just the first valid view in the list.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewArray[ k ] )
      {
         vSubtask = lpViewArray[ k ];
         break;
      }
   }

   hTask = vSubtask->hTask;

   for ( k = 0; k < nViewCount; k++ )
   {
      bGenkeyNeededArray[ k ] = FALSE;
      bFK_NeededArray[ k ] = FALSE;

      if ( lpViewArray[ k ] == 0 )
         continue;

      // Check to see if the View has genkeys.  If it does then make sure the
      // genkey handler has been loaded.
      if ( lpViewOD_Array[ k ]->bGenkey )
      {
         if ( hGKHandler == 0 )
         {
            hGKHandler = lpViewOD_Array[ k ]->hGKHandler;

            // Make sure that the GKHandler has been set.
            if ( hGKHandler == 0 )
            {
               zCHAR    szMsg[ 256 ];

               sprintf_s( szMsg, zsizeof( szMsg ), "No GenKey handler set for LOD: %s",
                         lpViewOD_Array[ k ]->szName );
               SysMessageBox( vSubtask, szlOE_SystemError, szMsg, 1 );
               return( zCALL_ERROR );
            }
         }
         else
         {
            // Make sure that all the views have the same GKHandler.
            if ( lpViewOD_Array[ k ]->hGKHandler != hGKHandler )
            {
               SysMessageBox( vSubtask, szlOE_SystemError,
                              "OIs have different GenKey handlers", 1 );
               return( zCALL_ERROR );
            }
         }
      }

      // Go through entity instance looking for entities that need genkeys.
      // Also check to see if the EI needs to set a foreign key.
      for ( lpEntityInstance = zGETPTR( lpViewOI_Array[ k ]->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         LPVIEWENTITY lpViewEntity;
         LPVIEWATTRIB lpViewAttrib;
         zPVOID       pDummy;
         zULONG       uLth;

         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // Entities on a derived path don't get a genkey or a foreign key.
         if ( lpViewEntity->bDerivedPath )
         {
            // If an EI is down a derived path then all children are also a
            // derived path.  We can try to save a little time by ignoring
            // all the children.
            while ( lpEntityInstance->hNextTwin )
               lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );

            continue;
         }

         // Check to see if the EI needs to set some foreign keys.
         // NOTE!
         // NOTE! The logic here matches the logic that is in
         // NOTE! fnCommitPreLoops( ). Any changes here should be reflected
         // NOTE! there.
         // NOTE!
         if ( lpEntityInstance->u.nInd.bHidden == FALSE )
         {
            // DGC 99.07.02
            // If the EI is flagged as created and the entity doesn't have
            // create authority then make sure that there is a linked EI in
            // the current cluster that does have create authority.
            if ( lpEntityInstance->u.nInd.bCreated &&
                 lpViewEntity->bCreate == FALSE &&
                 lpViewEntity->bDupInstance == FALSE ) //BL, 2000.01.04 Bugfix Repository
            {
               fnCheckCreateDeleteFlags( lpEntityInstance, lpViewArray,
                                         lpViewOD_Array, lpViewOI_Array,
                                         nViewCount, TRUE );
            }

            if ( lpEntityInstance->u.nInd.bCreated
#if ( VIEWENT_RULES )
                  && lpViewEntity->bCreate
#endif
               )
            {
               // Foreign keys need to be set later.
               bFK_NeededArray[ k ] = TRUE;
               lpEntityInstance->u.nInd.bForeignKeys = TRUE;
            }
            else
            {
               if ( lpEntityInstance->u.nInd.bIncluded &&
                    lpEntityInstance->hParent          &&
#if ( VIEWENT_RULES )
                    lpViewEntity->bInclude &&
#endif
                    ( lpEntityInstance->u.nInd.bCreated == FALSE
#if ( VIEWENT_RULES )
                      || lpViewEntity->bCreate == FALSE
#endif
                  ) )
               {
                  // Foreign keys need to be set later.
                  bFK_NeededArray[ k ] = TRUE;
                  lpEntityInstance->u.nInd.bForeignKeys = TRUE;
               }
            }
         } // if ( lpEntityInstance->u.nInd.bHidden == FALSE )...
         else
         {
            if ( lpEntityInstance->u.nInd.bCreated == FALSE &&
                 lpEntityInstance->u.nInd.bIncluded == FALSE )
            {
               if ( lpEntityInstance->u.nInd.bExcluded
#if ( VIEWENT_RULES )
                    && lpViewEntity->bExclude
#endif
                  )
               {
                  bFK_NeededArray[ k ] = TRUE;
                  lpEntityInstance->u.nInd.bForeignKeys = TRUE;
               }
               else
               if ( lpEntityInstance->u.nInd.bDeleted
#if ( VIEWENT_RULES )
                    && lpViewEntity->bDelete
#endif
                  )
               {
                  bFK_NeededArray[ k ] = TRUE;
                  lpEntityInstance->u.nInd.bForeignKeys = TRUE;
               }
            }
         } // if ( lpEntityInstance->u.nInd.bHidden == FALSE )...else...

         // At this point we've determined whether an EI needs an FK.  From
         // this point on we're only worried about genkeys.

         // If NoGenKey flag is set then we already created a genkey for
         // another linked instance.
         if ( lpEntityInstance->u.nInd.bNoGenKey )
            continue;

         // We only create genkeys for EIs that were created.  If it's
         // created make sure it's not also deleted.
         if ( lpEntityInstance->u.nInd.bCreated == FALSE ||
              lpEntityInstance->u.nInd.bDeleted )
         {
            continue;
         }

#if ( VIEWENT_RULES )
         if ( lpViewEntity->bCreate == FALSE )
            continue;
#endif

         if ( lpViewEntity->bGenkey == FALSE )
            continue;

         // Check to see if the attribute is NULL.  If it is not then
         // we'll ignore it.
         for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
               lpViewAttrib->bGenkey == FALSE;
               lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
         {
            ; // nothing needs to be done here
         }

         if ( fnGetAttrAddrFromEntityInstance( (zCOREMEM) &pDummy,
                                               &uLth, lpEntityInstance,
                                               lpViewAttrib ) != -1 )
         {
            continue;   // Attrib is not null so ignore it.
         }

         // If genkey work object hasn't been activated, then activate it.
         if ( *lpKZGKHWOB == 0 )
         {
            SfActivateSysEmptyOI( lpKZGKHWOB, "KZGKHWOB", vSubtask, zSINGLE );
            CreateEntity( *lpKZGKHWOB, "KZGKHWOB", zPOS_FIRST );
            SetNameForView( *lpKZGKHWOB, "_KZGKHWOB", 0, zLEVEL_TASK );
         }

         // lpKZGKHWOB is a work object that contains an entity for each
         // entity instance in the OI being committed and the number of
         // entity instances that need genkeys.
         //
         // If the lpViewEntity of the current entity instance is the same
         // as the previous entity instance, then increment the count in
         // lpKZGKHWOB by 1.  If they are different, then we need to find
         // the entity instance in lpKZGKHWOB that corresponds with the
         // current lpEntityInstance.  If one is not found, then it needs
         // to be created.
         if ( lpViewEntity != lpLastInsertedViewEntity )
         {
            // lpViewEntity for current lpEntityInstance does not match
            // last lpEntityInstance.  Try to find the entity in lpKZGKHWOB
            // that corresponds with the lpViewEntity.
            nRC = SetCursorFirstEntityByInteger( *lpKZGKHWOB, "Genkey",
                                                 "EntityID",
                                                 lpViewEntity->lEREntTok, "" );
            if ( nRC == zCURSOR_SET )
            {
               // Entity was found--increment genkey count by 1.
               AddToAttributeFromInteger( *lpKZGKHWOB, "Genkey",
                                          "EntityCount", 1 );
            }
            else
            {
               LPDATARECORD lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );

               // Entity not found--create entity and initialize.
               CreateEntity( *lpKZGKHWOB, "Genkey", zPOS_FIRST );
               SetAttributeFromInteger( *lpKZGKHWOB, "Genkey",
                                        "EntityID", lpViewEntity->lEREntTok );
               SetAttributeFromInteger( *lpKZGKHWOB, "Genkey",
                                        "EntityCount", 1 );
               SetAttributeFromString( *lpKZGKHWOB, "Genkey",
                                       "TableName", lpDataRecord->szRecordName );
               SetAttributeFromString( *lpKZGKHWOB, "Genkey",
                                       "EntityName", lpViewEntity->szName );
            }

            lpLastInsertedViewEntity = lpViewEntity;
         } // if ( lpViewEntity != lpLastInsertedViewEntity )...
         else
            AddToAttributeFromInteger( *lpKZGKHWOB, "Genkey", "EntityCount", 1 );

         bGenkeyNeededArray[ k ] = TRUE;
         lpEntityInstance->u.nInd.bGenKeyNeeded = TRUE;

         // Set a flag for all linked instances to keep another genkey from
         // being created.
         if ( lpEntityInstance->hNextLinked )
         {
            LPENTITYINSTANCE lpLinked;

            for ( lpLinked = zGETPTR( lpEntityInstance->hNextLinked );
                  lpLinked != lpEntityInstance;
                  lpLinked = zGETPTR( lpLinked->hNextLinked ) )
            {
               lpLinked->u.nInd.bNoGenKey = TRUE;
            }
         }

      } // for ( lpEntityInstance )...
   } // for ( k = 0; k < nViewCount; k++ )

   // If the Genkey handler work object has been defined, then call the
   // genkey handler to start transactions.
   if ( *lpKZGKHWOB )
   {
      if ( fnGetGKHandlerOper( *lpKZGKHWOB, lpCurrentTask, hGKHandler,
                               (zlpPGKHOPER) ppGKOper ) == zCALL_ERROR )
      {
         LPTASK lpTask = zGETPTR( vSubtask->hTask );
         // "KZOEE082 - Error starting Genkey handler"
         fnIssueCoreError( lpTask, vSubtask, 16, 82, 0, 0, 0 );
         return( zCALL_ERROR );
      }

      // Call DBHandler routine to issue start of transaction.
      nRC = (**ppGKOper)( DBH_StartGenkey, vSubtask, 0, 0, *lpKZGKHWOB );
      if ( nRC < 0 )
         return( nRC );

      // Now set the gen keys.
      lpLastInsertedViewEntity = 0;
      for ( k = 0; k < nViewCount; k++ )
      {
         // If we didn't find any genkeys for this view then skip it.
         if ( bGenkeyNeededArray[ k ] == FALSE )
            continue;

         // Go through entity instance looking for entities that need genkeys.
         for ( lpEntityInstance = zGETPTR( lpViewOI_Array[ k ]->hRootEntityInstance );
               lpEntityInstance;
               lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
         {
            LPVIEWENTITY lpViewEntity;
            LPVIEWATTRIB lpViewAttrib;
            zPVOID       pDummy;
            zULONG       uLth;

            // Look for an EI that needs a genkey.
            if ( lpEntityInstance->u.nInd.bGenKeyNeeded == FALSE )
               continue;

            lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

            // Check to see if the attribute is NULL.  If it is not then
            // we'll ignore it.
            for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
                  lpViewAttrib->bGenkey == FALSE;
                  lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
            {
               ; // nothing needs to be done here
            }

            if ( fnGetAttrAddrFromEntityInstance( (zCOREMEM) &pDummy,
                                                  &uLth, lpEntityInstance,
                                                  lpViewAttrib ) != -1 )
            {
               continue;   // attrib is not null so ignore it
            }

            if ( lpViewEntity != lpLastInsertedViewEntity )
            {
               // lpViewEntity for current lpEntityInstance does not match
               // last lpEntityInstance.  Try to find the entity in lpKZGKHWOB
               // that corresponds with the lpViewEntity.
               nRC = SetCursorFirstEntityByInteger( *lpKZGKHWOB, "Genkey",
                                                    "EntityID",
                                                    lpViewEntity->lEREntTok, "" );

               lpLastInsertedViewEntity = lpViewEntity;
            }

            fnEstablishViewForInstance( lpViewArray[ k ], 0, lpEntityInstance );

            // Tell genkey handler to set attribute value.
            nRC = (**ppGKOper)( DBH_GetGenkey, lpViewArray[ k ],
                                lpViewOD_Array[ k ],
                                lpViewEntity, *lpKZGKHWOB );
            if ( nRC < 0 )
               return( zCALL_ERROR );

         } // for ( lpEntityInstance )...

      } // for ( k = 0; k < nViewCount; k++ )

   } // if ( *lpKZGKHWOB != 0 )...

   //
   // Now copy FKs.  We have to loop possibly many times to set the FKs.  It's
   // possible that the source for a FK is a FK from yet another EI.  We don't
   // want to copy a FK until we know that the source for a FK has been
   // properly set.  We also want to make sure we set the FK's for the EIs that
   // have been excluded/deleted before we copy FKs for the included/created.
   //
   bHiddenOnly = TRUE;  // We'll start by setting FKs for hidden EIs only.
   nDebugCnt   = 0;     // We'll keep a counter in case we get an infinite loop.
   bSettingFKs = TRUE;
   while ( bSettingFKs )
   {
      // We'll hope that we're done setting FKs after this iteration.  If we
      // find we need to set more FKs then we'll turn it back on.
      bSettingFKs = FALSE;

      if ( nDebugCnt++ > 100 )
      {
         SysMessageBox( vSubtask, szlOE_SystemError,
                        "Infinite loop trying to set FKs?", 1 );
         return( zCALL_ERROR );
      }

      for ( k = 0; k < nViewCount; k++ )
      {
         // If we didn't find any FKs for this view then skip it.
         if ( bFK_NeededArray[ k ] == FALSE )
            continue;

         // Let's hope that this view doesn't need FKs set after this
         // iteration.  If it does then we'll turn the flag back on.
         bFK_NeededArray[ k ] = FALSE;

         // Go through entity instance looking for entities that need genkeys.
         // Also check to see if the EI needs to set a foreign key.
         for ( lpEntityInstance = zGETPTR( lpViewOI_Array[ k ]->hRootEntityInstance );
               lpEntityInstance;
               lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
         {
            LPVIEWENTITY lpViewEntity;

            // If the EI isn't flagged as needing a FK then skip it.
            if ( lpEntityInstance->u.nInd.bForeignKeys == FALSE )
               continue;

            // Entities on a derived path don't get a FK set..
            lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
            if ( lpViewEntity->bDerivedPath )
            {
               // If an EI is down a derived path then all children are also a
               // derived path.  We can try to save a little time by ignoring
               // all the children.
               while ( lpEntityInstance->hNextTwin )
                  lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );

               continue;
            }

            // If the EI is not hidden and we're setting FKs for hidden EIs
            // only then set flags for another try.
            if ( lpEntityInstance->u.nInd.bHidden == FALSE && bHiddenOnly )
            {
               bFK_NeededArray[ k ] = TRUE;
               bSettingFKs = TRUE;
               continue;
            }

            // Call a function to set the FK.  If the return code is 1 then
            // we couldn't set the FK because a source value hasn't been set
            // yet and we'll have to try again later.
            if ( fnSetForeignKeysForInstance( lpEntityInstance ) == 1 )
            {
               bFK_NeededArray[ k ] = TRUE;
               bSettingFKs = TRUE;
            }

         } // for ( lpEntityInstance )...

      } // for ( k = 0; k < nViewCount; k++ )

      // After one iteration we can set non-hidden FKs.
      bHiddenOnly = FALSE;

   } // while ( bSettingFKs )...

   return( 0 );

} // fnInitializeGenKeys

// This function is called after an EI has been included into the DB.  This
// function sets the bDBHIncluded/bDBHExcluded flag for all linked EIs in the
// same OI that have the same relationship.
zSHORT LOCALOPER
fnMarkDuplicateRelationship( LPENTITYINSTANCE lpEntityInstance,
                             zBOOL            bIncludeFlag )
{
   LPVIEWOI         lpViewOI;
   LPVIEWENTITY     lpViewEntity;
   LPVIEWENTITY     lpLnkViewEntity;
   LPENTITYINSTANCE lpParent;
   LPENTITYINSTANCE lpLnkParent;
   LPENTITYINSTANCE lpLnkEntityInstance;

   // Return 0 if instance passed is not linked
   if ( lpEntityInstance->hNextLinked == 0 )
      return( 0 );

   // Get Object instance for entity instance
   lpViewOI     = zGETPTR( lpEntityInstance->hViewOI );
   lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
   lpParent     = zGETPTR( lpEntityInstance->hParent );

   // If the parent isn't linked then there are no duplicate relationships.
   if ( lpParent == 0 || lpParent->hNextLinked == 0 )
      return( 0 );

   // Duplicate relationship searching phase I, see if a linked instance to
   // the target instance in the same object instance represents the
   // same relationship type AND has the same parent
   for ( lpLnkEntityInstance = zGETPTR( lpEntityInstance->hNextLinked );
         lpLnkEntityInstance != lpEntityInstance;
         lpLnkEntityInstance = zGETPTR( lpLnkEntityInstance->hNextLinked ) )
   {
      LPENTITYINSTANCE lpWrkEntityInstance;

      // Check to make sure linked EI has a parent--it is possible for a root
      // to be flagged as included and we don't care about roots.
      if ( lpLnkEntityInstance->u.nInd.bDeleted  ||
           lpLnkEntityInstance->hParent == 0 )
      {
         continue;
      }

      // Check for appropriate include/exclude flag.
      if ( bIncludeFlag )
      {
         if ( lpLnkEntityInstance->u.nInd.bIncluded == FALSE ||
              lpLnkEntityInstance->u.nInd.bExcluded )
         {
            continue;
         }
      }
      else
      {
         if ( lpLnkEntityInstance->u.nInd.bIncluded ||
              lpLnkEntityInstance->u.nInd.bExcluded == FALSE )
         {
            continue;
         }
      }

      lpLnkViewEntity = zGETPTR( lpLnkEntityInstance->hViewEntity );

      // Linked EI must have the same relationship and it can't be derived.
      if ( lpLnkViewEntity->lERRelTok != lpViewEntity->lERRelTok ||
           lpLnkViewEntity->bDerivedPath )
      {
         continue;
      }

      // Now check to see if the parent of the linked EI is linked to the
      // parent of the original EI.  If it is then the linked EI and the
      // original EI have the same relationship.

      lpLnkParent = zGETPTR( lpLnkEntityInstance->hParent );

      for ( lpWrkEntityInstance = zGETPTR( lpLnkParent->hNextLinked );
            lpWrkEntityInstance && lpWrkEntityInstance != lpLnkParent;
            lpWrkEntityInstance = zGETPTR( lpWrkEntityInstance->hNextLinked ) )
      {
         if ( lpWrkEntityInstance == lpParent )
         {
            // The parents of the two linked EIs are also linked.  Set flag
            // and break loop.
            if ( bIncludeFlag )
               lpLnkEntityInstance->u.nInd.bDBHIncluded = TRUE;
            else
               lpLnkEntityInstance->u.nInd.bDBHExcluded = TRUE;

            break;
         }
      }
   }

   // Duplicate relationship searching, phase II, see if the parent of
   // the instance has a linked instance representing the same relationship
   // type which is also a child of one of the targets linked instances.
   // (i.e. the same relationship instance inverted).
   for ( lpLnkParent = zGETPTR( lpParent->hNextLinked );
         lpLnkParent != lpParent;
         lpLnkParent = zGETPTR( lpLnkParent->hNextLinked ) )
   {
      LPENTITYINSTANCE lpGrandParent;

      // Check for appropriate include/exclude flag.
      if ( bIncludeFlag )
      {
         if ( lpLnkParent->u.nInd.bIncluded == FALSE ||
              lpLnkParent->u.nInd.bExcluded )
         {
            continue;
         }
      }
      else
      {
         if ( lpLnkParent->u.nInd.bIncluded || lpLnkParent->u.nInd.bExcluded == FALSE )
            continue;
      }

      lpLnkViewEntity = zGETPTR( lpLnkParent->hViewEntity );

      // Check to see if the relationship for the EI linked to the parent is
      // the same as the relationship of the original EI.
      if ( lpLnkViewEntity->lERRelTok != lpViewEntity->lERRelTok )
         continue;  // Nope.

      // OK, we have an EI (lpLnkParent) that has the same relationship as
      // lpEntityInstance.  Check to see if the parent of lpLnkParent (lpGrandParent)
      // is linked with lpEntityInstance.  If they are linked then lpLnkParent
      // has the same physical relationship as lpEntityInstance.
      lpGrandParent = zGETPTR( lpLnkParent->hParent );
      for ( lpLnkEntityInstance = zGETPTR( lpEntityInstance->hNextLinked );
            lpLnkEntityInstance != lpEntityInstance;
            lpLnkEntityInstance = zGETPTR( lpLnkEntityInstance->hNextLinked ) )
      {
         if ( lpLnkEntityInstance == lpGrandParent )
         {
            // If we've found an inverted structure in the same
            // object instance which is the same relationship type, set flag.
            if ( bIncludeFlag )
               lpLnkParent->u.nInd.bDBHIncluded = TRUE;
            else
               lpLnkParent->u.nInd.bDBHExcluded = TRUE;

            break;
         }
      }
   }

   return( 0 );
}

//./ ADD NAME=fnCommitPreLoops
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:
//
//  PURPOSE:      Called by fnCommitObjectInstance, this function performs
//                some things before the Object Instance is committed.  The
//                main reason for this function is to break up fnCommit...
//                to a smaller size to allow the compiler to optimize.
//
//             o  Some validity checking.
//             o  Checks cardinality and required attributes.
//             o  Sets any auto-sequence attributes.
//             o  Turns off "hidden" flag so db-handler can access all data.
//             o  Sets lpFirst.../lpLast... EntityInstance pointers.
//
//  PARAMETERS:
//
//  RETURNS:    0           - Everthing OK
//              zCALL_ERROR - Oops!
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT
fnCommitPreLoops( LPTASK           lpCurrentTask,
                  zVIEW            lpView,
                  LPENTITYINSTANCE *plpLastEntityInstance,
                  zPLONG           plHiddenCnt )
{
   LPVIEWOD             lpViewOD;
   LPVIEWOI             lpViewOI;
   LPVIEWCSR            lpViewCsr;
   LPVIEWENTITY         lpViewEntity;
   LPVIEWENTITY         lpLastInsertedViewEntity;
   LPENTITYINSTANCE     lpEntityInstance;
   LPENTITYINSTANCE     lpRootEntityInstance;
   LPDATARECORD         lpDataRecord;
   LPVIEWATTRIB         lpViewAttrib;
   LPRELRECORD          lpRelRecord;
   zSHORT               nRC;

   lpLastInsertedViewEntity = 0;

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   lpViewOD  = zGETPTR( lpViewOI->hViewOD );
   lpRootEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );

   // Change the "hidden" indicator to false if the entity instance was
   // deleted.  This will allow the db-handler to access the entity instance.
   *plHiddenCnt = 0;
   nRC = 0;
   for ( lpEntityInstance = lpRootEntityInstance;
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
   {
      // Keep track of the last valid EI.
      *plpLastEntityInstance = lpEntityInstance;

      lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

      // If it is a derived path, skip it
      if ( lpViewEntity->bDerivedPath )
         continue;

      lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );

      // If it has no data record, skip it
      if ( lpDataRecord == 0 )
         continue;

      lpRelRecord  = zGETPTR( lpDataRecord->hFirstRelRecord );

      // If the entity for the current entity instance has an automatic
      // sequence attribute AND it is the first twin under its parent,
      // ensure that the sequence numbers for all the twins are correct.
      if ( lpViewEntity->bAutoSeq &&
           lpEntityInstance->hPrevTwin == 0 &&  // Must be first twin.
           lpEntityInstance->hNextTwin )   // Don't bother if only 1 twin.
      {
         zULONG           uLth;
         zLONG            lSeq;
         zPLONG           lpSeqPtr;
         LPENTITYINSTANCE lpTwin;

         // First, find the autoseq view attrib.
         lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
         while ( lpViewAttrib->bAutoSeq == FALSE )
            lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib );

         // For each of the twins, set the seq attribute.
         lSeq = 1;
         lpTwin = lpEntityInstance;
         while ( lpTwin )
         {
            // If the twin wasn't deleted, then set it's sequence number.
            if ( lpTwin->u.nInd.bHidden == FALSE )
            {
               // Make sure the entity instance has a data record.
               if ( lpTwin->hPersistRecord == 0 )
                  fnCreateAttributeRecord( zGETPTR( lpViewOI->hAllocTask ),
                                           lpViewEntity, lpTwin );

               fnGetAttrAddrFromEntityInstance( (zCOREMEM) &lpSeqPtr, &uLth,
                                                lpTwin, lpViewAttrib );

               // Only update sequence attribute if the value of the seqence
               // attribute in the entity is different from the local counter.
               if ( *lpSeqPtr != lSeq )
               {
                  LPATTRIBFLAGS lpAttribFlags;

                  *lpSeqPtr = lSeq;
                  lpTwin->u.nInd.bSequenceUpdt = TRUE;

                  // Since changing the attribute value via a pointer doesn't
                  // change the attrib flag do so now.
                  lpAttribFlags = fnGetAttribFlagsPtr( lpTwin, lpViewAttrib );
                  lpAttribFlags->u.bFlags.bUpdated = TRUE;

                  // Turn off the bDBHUpdated flag (if it's on) so that we
                  // make sure the entity is updated.  If the entity instance
                  // is linked with someone else it's possible that the
                  // entity was updated through the other link.
                  lpEntityInstance->u.nInd.bDBHUpdated = FALSE;
               }

               lSeq++;
            }

            lpTwin = zGETPTR( lpTwin->hNextTwin );
         }
      } // if ( lpViewEntity->bAutoSeq && lpEntityInstance->hPrevTwin == 0 )...

      if ( lpEntityInstance->u.nInd.bHidden )
      {
         // Increment Hidden counter
         (*plHiddenCnt)++;

         // Unhide the instance so the DBHandler can access it unless it is
         // "dead".  If it's "dead" the the DBHandler shouldn't care about it.
         if ( !fnEntityInstanceIsDead( lpEntityInstance ) )
            lpEntityInstance->u.nInd.bHidden = FALSE;
      }

   }  // for ( lpEntityInstance )...

   return( 0 );

} // fnCommitPreLoops

// fnCleanupInstance
//
// Cleans up an Object Instance. After an OI has been committed, there is a
// lot of junk in the OI that is no longer needed.  In addition, the entity
// instances that where created/included/updated must be flagged as unchanged
// so that the next commit doesn't try to create/include/update the entity
// again.  Performs the following:
//
// o  Cleans up all view cursors that point to the OI.
// o  Unmarks created, updated, and included entity instances.
// o  Unmarks updated attributes.
// o  Sets cr/del/hidden flags in linked instances.
// o  If lHiddenCnt is non-zero, then this function reclaims all deleted
//    and excluded entity instances from the OI i.e. drops them from the OI
//    and frees all memory used by those entities.
//
// This operation is called from fnCommitObjectInstance (kzoeoiaa.c) and
// fnProcessCommitOI (kzoeneta.c).
void
fnCleanupInstance( zVIEW lpView, zLONG lHiddenCnt )
{
   LPVIEWCSR         lpViewCsr = zGETPTR( lpView->hViewCsr );
   LPVIEWOI          lpViewOI = zGETPTR( lpViewCsr->hViewOI );
   LPVIEWENTITY      lpViewEntity;
   LPENTITYINSTANCE  lpRootEntityInstance;
   LPENTITYINSTANCE  lpEntityInstance;
   LPENTITYINSTANCE  lpNextLinked;
   LPVIEWCSR         lpWrkViewCsr;

   // Clean up any view cursors which point to a hidden entity
   // If the root was deleted, delete all view cursors except the one
   // used in this call - REMOVED 1/22/93...Causes reclamation problems and
   // also does not account for multiple roots in the instance, the
   // reclamation code below will clean up the instance except for
   // the deleted root, This is enough cleanup under the circumstances
   // 1/22/93 ... Gig
   lpRootEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
   lpWrkViewCsr = zGETPTR( lpViewOI->hFirstViewCsr );
   while ( lpWrkViewCsr )
   {
      LPVIEWCSR lpNextViewCsr;

      lpNextViewCsr = zGETPTR( lpWrkViewCsr->hNextViewCsr );

      // Get rid of any view cursors whose parent entity instance has been
      // deleted
      lpEntityInstance = zGETPTR( lpWrkViewCsr->hViewParentEntityInstance );
      if ( lpEntityInstance && lpEntityInstance->u.nInd.bHidden )
         fnDropViewCsr( lpWrkViewCsr );
      else
      {
         // Go through all view entity cursors (except the root) and set all
         // cursors pointing to a hidden instance to unset.
         LPVIEWENTITYCSR lpViewEntityCsr;
         zUSHORT         uIdx;

         // Turn Off Hierarchical stuff in ViewCsr
         lpViewCsr->hHierRootEntityInstance = 0;
         lpViewCsr->hHierEntityInstance = 0;

         lpViewEntityCsr = zGETPTR( lpViewCsr->hFirstOD_EntityCsr );
         lpViewEntityCsr++;  // Skip the root.
         for ( uIdx = 2; uIdx <= lpViewCsr->uEntities; uIdx++ )
         {
            lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
            if ( lpEntityInstance && lpEntityInstance != UNSET_CSR &&
                 lpEntityInstance->u.nInd.bHidden )
            {
               if ( lpEntityInstance != lpRootEntityInstance )
               {
                  lpViewEntityCsr->hEntityInstance = UNSET_CSR;
               // if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR )
               //    SysMessageBox( 0, "fnCleanupInstance", "UNSET_CSR", -1 );
               }

               fnResetCursorForViewChildren( lpViewEntityCsr );
            }

            lpViewEntityCsr++;
         }
      }

      lpWrkViewCsr = lpNextViewCsr;
   }

   // Now un-mark all created, updated and included instances and
   // remove any deleted instances
   for ( lpEntityInstance = lpRootEntityInstance;
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
   {
      LPVIEWATTRIB     lpViewAttrib;
      LPENTITYINSTANCE lpParent;

      lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

      // Skip the entity if the DBH didn't do anything
      if ( lpEntityInstance->u.nInd.bDBHCreated == FALSE &&
           lpEntityInstance->u.nInd.bDBHIncluded == FALSE &&
           lpEntityInstance->u.nInd.bDBHDeleted == FALSE &&
           lpEntityInstance->u.nInd.bDBHExcluded == FALSE &&
           lpEntityInstance->u.nInd.bDBHUpdated == FALSE )
      {
         continue;
      }

      lpEntityInstance->u.nInd.bCreated =
         lpEntityInstance->u.nInd.bUpdated =
         lpEntityInstance->u.nInd.bDeleted =
         lpEntityInstance->u.nInd.bIncluded =
         lpEntityInstance->u.nInd.bExcluded = FALSE;

      // If the EI was not updated, deleted, or created then we are done with
      // this entity.
      if ( lpEntityInstance->u.nInd.bDBHCreated == FALSE &&
           lpEntityInstance->u.nInd.bDBHDeleted == FALSE &&
           lpEntityInstance->u.nInd.bDBHUpdated == FALSE )
      {
         continue;
      }

      // Turn off the updated flag for each of the attributes.
      for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
            lpViewAttrib;
            lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
      {
         LPATTRIBFLAGS lpAttribFlags;

         // Skip non-persistent attributes.
         if ( lpViewAttrib->bPersist == FALSE )
            continue;

         lpAttribFlags = fnGetAttribFlagsPtr( lpEntityInstance, lpViewAttrib );
         lpAttribFlags->u.bFlags.bUpdated = FALSE;
      }

      // Set flags for other linked instances.  If this instance isn't linked
      // then go on to next one.
      if ( lpEntityInstance->hNextLinked == 0 )
         continue;

      for ( lpNextLinked = zGETPTR( lpEntityInstance->hNextLinked );
            lpNextLinked != lpEntityInstance;
            lpNextLinked = zGETPTR( lpNextLinked->hNextLinked ) )
      {
         LPVIEWENTITY lpLinkedViewEntity = zGETPTR( lpNextLinked->hViewEntity );

         // Turn off flags in linked entities depending on what the DBHandler
         // did to the current EI.
         if ( lpEntityInstance->u.nInd.bDBHCreated )
            lpNextLinked->u.nInd.bCreated = FALSE;

         if ( lpEntityInstance->u.nInd.bDBHUpdated )
            lpNextLinked->u.nInd.bUpdated = FALSE;

         if ( lpEntityInstance->u.nInd.bDBHDeleted )
            lpNextLinked->u.nInd.bDeleted = FALSE;

         // Do some more processing if the EI is included/excluded.  If not
         // inc/exc then skip it.
         if ( lpEntityInstance->u.nInd.bDBHIncluded == FALSE &&
              lpEntityInstance->u.nInd.bDBHExcluded == FALSE )
         {
            continue;
         }

         // If lpEntityInstance and lpNextLinked have the same relationship
         // with their respective parents then we don't want to inc/exc the
         // lpNextLinked because it's already been done.  If the two EIs are
         // in the same OI then they must have the same linked parents.
         if ( lpNextLinked->hViewOI == lpEntityInstance->hViewOI ||
              ( lpLinkedViewEntity->lERRelTok == lpViewEntity->lERRelTok &&
                fnInstanceLinkedToInstance( zGETPTR( lpNextLinked->hParent ),
                                            zGETPTR( lpEntityInstance->hParent ) ) ) )
         {
            if ( lpEntityInstance->u.nInd.bDBHIncluded )
               lpNextLinked->u.nInd.bIncluded = FALSE;

            if ( lpEntityInstance->u.nInd.bDBHExcluded )
               lpNextLinked->u.nInd.bExcluded = FALSE;
         }
      }

      // if the instance has a parent and the parent is linked, see
      // if one of the linked parents is an inverted representation
      // of the same relationship
      lpParent = zGETPTR( lpEntityInstance->hParent );
      if ( lpParent == 0 || lpParent->hNextLinked == 0 )
         continue;

      for ( lpNextLinked = zGETPTR( lpParent->hNextLinked );
            lpNextLinked != lpParent;
            lpNextLinked = zGETPTR( lpNextLinked->hNextLinked ) )
      {
         LPVIEWENTITY lpLinkedViewEntity = zGETPTR( lpNextLinked->hViewEntity );

         if ( lpNextLinked->hParent &&
              lpLinkedViewEntity->lERRelTok == lpViewEntity->lERRelTok &&
              fnInstanceLinkedToInstance( zGETPTR( lpNextLinked->hParent ),
                                          lpEntityInstance ) )
         {
            lpNextLinked->u.nInd.bIncluded = FALSE;
            lpNextLinked->u.nInd.bExcluded = FALSE;
         }
      }

   } // for each lpEntityInstance...

   // Call fnReclaim to clean up deleted instances
   if ( lHiddenCnt )
      fnReclaimHiddenInstances( lpViewOI );

} // fnCleanupInstance

// If bLOD_Lock is TRUE then the lock we are deleting is at the LOD level
// (and lpFirstEntityInstance had better be a root instance!).
zSHORT LOCALOPER
fnDeleteLocksOnTwins( LPTASK           lpCurrentTask,
                      zVIEW            vLock,
                      LPENTITYINSTANCE lpFirstEntityInstance,
                      zVIEW            lpView,
                      zBOOL            bLOD_Lock,
                      LPVIEWOI         lpViewOI )
{
   LPVIEWENTITY      lpLockEntity;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWATTRIB      lpViewAttrib;
   LPVIEWATTRIB      lpKeyViewAttrib[ zMAX_KEYS_FOR_LOCK ];
   LPENTITYINSTANCE  lpEntityInstance;
   LPVIEWENTITYCSR   lpLockEntityCsr;
   LPVIEWOD          lpViewOD = zGETPTR( lpView->hViewOD );
   zCHAR             szKeyString[ zMAX_KEYLTH_FOR_LOCK + 1 ];
   zCHAR             szLockName[ 35 ];
   zSHORT            nKeyCnt;
   zSHORT            nRC = zCALL_ERROR;       // Assume error.

   lpViewEntity = zGETPTR( lpFirstEntityInstance->hViewEntity );

   // To save time later find all the keys in the LOD and store them in a table.
   nKeyCnt = 0;
   for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
         lpViewAttrib;
         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
   {
      if ( lpViewAttrib->bKey )
         lpKeyViewAttrib[ nKeyCnt++ ] = lpViewAttrib;
   }

   // Get the lpViewEntity and lpLockEntityCsr for the lock OI.
   lpLockEntity = fnValidViewEntity( &lpLockEntityCsr, vLock, "ZeidonLock", 0 );

   if ( bLOD_Lock )
   {
      // We are checking a LOD level lock so we set LockName to the name of
      // the LOD.
      strcpy_s( szLockName, zsizeof( szLockName ), lpViewOD->szName );
   }
   else
   {
      // We are checking a lock at the entity level so use the name of the
      // entity for the LockName.  In addition, to handle the rare case where
      // a LOD and entity name are the same we prefix all entity names with
      // a '@' because it's an invalid character for entity names.  This
      // insures that the LockName for the entity does not match a LOD name.
      sprintf_s( szLockName, zsizeof( szLockName ), "@%s", lpViewEntity->szName );
   }

   // Loop through each of the twin entities and create a locking record.  We
   // are going to cheat by then turning off the Create flag and turning on
   // the Delete and Hidden flags.  This will allow us to delete the lock
   // records off the DB without activating them first.
   for ( lpEntityInstance = lpFirstEntityInstance;
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin ) )
   {
      LPENTITYINSTANCE lpLockEntityInstance;

      // We don't care about instances that have been created.  Created
      // entities won't have a locking record because they where just created.
      // Same for included entities.
      if ( lpEntityInstance->u.nInd.bCreated ||
           lpEntityInstance->u.nInd.bIncluded )
         continue;

      // Create the concat key string.
      fnCreateConcatKey( szKeyString, lpEntityInstance,
                         lpKeyViewAttrib, nKeyCnt );

      if ( fnCreateEntity( vLock, lpLockEntity, lpLockEntityCsr,
                           zPOS_LAST, FALSE ) != 0 )
         goto EndOfFunction;

      if ( fnSetLockingAttributes( lpCurrentTask,
                                   vLock, lpLockEntity, lpLockEntityCsr,
                                   szLockName, szKeyString, 0, 0, 0 ) != 0 )
         goto EndOfFunction;

      // Here's where we cheat -- turn off Create flag and turn on the
      // Delete/Hidden flags so that when we commit the OI the locking
      // records will be deleted.
      lpLockEntityInstance = zGETPTR( lpLockEntityCsr->hEntityInstance );
      lpLockEntityInstance->u.nInd.bCreated = FALSE;
      lpLockEntityInstance->u.nInd.bDeleted = lpLockEntityInstance->u.nInd.bHidden = TRUE;

   } // for ( lpEntityInstance...)

   // If we get here then everything is OK.
   nRC = 0;

EndOfFunction:

   return( nRC );

} // fnDeleteLocksOnTwins

// Delete all the pessimistic lock records for all the views in lpViewArray.
zSHORT LOCALOPER
fnRemoveLocksOnOIs( LPTASK        lpCurrentTask,
                    LPVIEWCLUSTER lpViewCluster,
                    zSHORT        nViewCount,
                    zPSHORT       pnViewErrorIdx )
{
   ViewClusterRecord vLock;
   VIEWARRAYBLOCK    tViewArrayBlock = {0};
   zVIEW             vSubtask = 0;
   zBOOL             bDropLocks;
   zSHORT            k;
   zSHORT            nRC = zCALL_ERROR;       // Assume error.

   vLock.vOI = 0;
   vLock.lControl = 0;

   // vSubtask is just the first valid view in the list.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewCluster[ k ].vOI )
      {
         vSubtask = lpViewCluster[ k ].vOI;
         break;
      }
   }

   bDropLocks = FALSE;

   for ( k = 0; k < nViewCount; k++ )
   {
      LPVIEWOD  lpViewOD;
      LPVIEWCSR lpViewCsr;
      LPVIEWOI  lpViewOI;

      if ( lpViewCluster[ k ].vOI == 0 )
         continue;

      if ( lpViewCluster[ k ].lControl & zCOMMIT_KEEPLOCKS )
         continue;

      lpViewOD  = zGETPTR( lpViewCluster[ k ].vOI->hViewOD );
      lpViewCsr = zGETPTR( lpViewCluster[ k ].vOI->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      // If view wasn't activated with locking forget about it.
      if ( lpViewOI->bIsLocked == FALSE )
         continue;

      // If bDropLocks is FALSE then we haven't created the vLock object yet.
      if ( bDropLocks == FALSE )
      {
         // Create an empty lock OI.
         if ( fnDeclareView( &vLock.vOI, lpCurrentTask, vSubtask,
                             "ZPLOCKO", FALSE ) != 0 )
         {
            return( zCALL_ERROR );
         }

         if ( fnActivateEmptyObjectInstance( lpCurrentTask,
                                             vLock.vOI, zMULTIPLE ) != 0 )
         {
            return( zCALL_ERROR );
         }

         // Set flag to indicate:
         //    o The lock OI has been created.
         //    o We need to commit the lock object so that locks are removed.
         bDropLocks = TRUE;
      }

      // If the view has LOD-level locking release the LOD-level lock.
      if ( lpViewOD->nLock > zLL_PESSIMISTIC )
      {
         if ( fnDeleteLocksOnTwins( lpCurrentTask, vLock.vOI,
                                    zGETPTR( lpViewOI->hRootEntityInstance ),
                                    lpViewCluster[ k ].vOI,
                                    TRUE, lpViewOI ) != 0 )
         {
            goto EndOfFunction;
         }
      }

      // If the view has entity-level locking release the entity-level lock.
      if ( lpViewOD->nEntityLock > zLL_PESSIMISTIC )
      {
         LPENTITYINSTANCE lpEntityInstance;

         for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
               lpEntityInstance;
               lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
         {
            LPVIEWENTITY lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

            // If entity has no locking skip it.
            if ( lpViewEntity->nLock == 0 )
               continue;

            // If the instance is not the first twin then skip it.
            if ( lpEntityInstance->hPrevTwin )
               continue;

            if ( fnDeleteLocksOnTwins( lpCurrentTask, vLock.vOI,
                                       lpEntityInstance,
                                       lpViewCluster[ k ].vOI, FALSE,
                                       lpViewOI ) != 0 )
            {
               nRC = zCALL_ERROR;
               break;
            }

         } // for ( lpEntityInstance )...
      }

   } // for ( k = 0... )...

   // If we didn't find any views that should be locked then get out.
   if ( bDropLocks == FALSE )
   {
      nRC = 0;
      goto EndOfFunction;
   }

   // Now commit the lock OI.  This should delete the locks.
   if ( fnInitViewArrayBlock( &tViewArrayBlock, 1 ) != 0 )
      goto EndOfFunction;

   if ( fnCommitObjectInstance( &vLock, &vLock.vOI, 1, 0, lpCurrentTask,
                                0, &tViewArrayBlock ) != 0 )
   {
      goto EndOfFunction;
   }

   // Flag all the OI's as no longer locked.
   for ( k = 0; k < nViewCount; k++ )
   {
      LPVIEWCSR lpViewCsr;
      LPVIEWOI  lpViewOI;

      if ( lpViewCluster[ k ].vOI == 0 )
         continue;

      if ( lpViewCluster[ k ].lControl & zCOMMIT_KEEPLOCKS )
         continue;

      lpViewCsr = zGETPTR( lpViewCluster[ k ].vOI->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      lpViewOI->bIsLocked = FALSE;

   } // for ( k = 0... )...

   // If we get here then everything's OK.
   nRC = 0;

EndOfFunction:
   if ( vLock.vOI )
      fnDropView( vLock.vOI );

   fnFreeViewArrayBlock( &tViewArrayBlock );
   return( nRC );

} // fnRemoveLocksOnOIs

//./ ADD NAME=fnCommitSingleOI
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:
//
//  PURPOSE:      To commit an single OI.  Called from fnCommitObjectInstance.
//                Performs the following:
//
//                Checks optimistic locking for the view.
//                Run fnCommitPreLoops (creates GenKeys among other things).
//                Call DBH to perform excludes, del's, creates, inc's, upd's.
//                Clear flags/reclaim instances depending on lControl.
//
//  PARAMETERS:   lpView   - View to commit.
//
//  RETURNS:    0           - Everthing OK
//              zCALL_ERROR - Oops!
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT LOCALOPER
fnCommitSingleOI( zVIEW           lpView,
                  zLONG           lControl,
                  LPTASK          lpCurrentTask,
                  LPTASKDBHANDLER lpTaskDBHandler )
{
   LPVIEWOD             lpViewOD;
   LPVIEWOI             lpViewOI;
   LPVIEWCSR            lpViewCsr;
   LPVIEWENTITY         lpViewEntity;
   LPENTITYINSTANCE     lpEntityInstance;
   LPENTITYINSTANCE     lpLastEntityInstance;
   LPENTITYINSTANCE     lpRootEntityInstance;
   LPENTITYINSTANCE     lpLinked;
   zPDBHOPER            pOper = lpTaskDBHandler->pfDBHandlerOper;
   zPVOID               lpPtr = lpTaskDBHandler->lpConnection;
   zLONG                lHiddenCnt;
   zSHORT               nRC;

   // DGC 1998/11/17
   // We have code that is special just for relational DBs.  At the moment we
   // only support relational DBs so I'm setting the following variable to
   // be always TRUE.  When we support other DB types we'll have to do
   // something different.
   zBOOL                bRelational = TRUE;

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   lpViewOD  = zGETPTR( lpViewOI->hViewOD );

   nRC = (*pOper)( (zLONG) lpView->hTask, DBH_Object | DBH_NewObject, 0,
                   lpViewOD, 0, lpView, 0, &lpPtr );

   // Make sure OI does not contain versioned instances.
   if ( lpViewOI->nVersionedInstances )
   {
      LPTASK lpTask = zGETPTR( lpView->hTask );
      //  "KZOEE076 - Object instance contains versioned entity instances"
      fnIssueCoreError( lpTask, lpView, 8, 76, 0, 0, 0 );
      return( zCALL_ERROR );
   }

   // Check to see if the OI was activated using optmistic locking.
   if ( lpViewOI->lActivateControl & zACTIVATE_WITH_LOCKING &&
        (lpViewOD->nLock == zLL_OPTIMISTIC_NOINC ||
         lpViewOD->nLock == zLL_OPTIMISTIC_CMPRALL) )
   {
      zVIEW vCheckView;
      zLONG lCmprCntrl;

      // Since we have optimistic locking, we should have a copy of the
      // original OI (the OI after it was loaded).  Make sure we got it.
      if ( lpViewOI->vOriginalOI == 0 )
      {
         // This should never happen (if it does it's a core error) so we'll
         // just use SysMessageBox.
         SysMessageBox( lpView, "Internal Core Error",
                        "Couldn't find original OI!", 1 );
         return( zCALL_ERROR );
      }

      // Now activate the OI again using the qualification object but
      // WITHOUT optimistic locking.
      TraceLineS( "(oi) Activating Optimistic Check view", "" );
      nRC = ActivateObjectInstance( &vCheckView, lpViewOD->szName,
                                    lpView, zGETPTR( lpViewOI->vQualOI ),
                                    (lpViewOI->lActivateControl &
                                               ~(zACTIVATE_WITH_LOCKING)) );
      if ( nRC < 0 )
      {
         LPTASK lpTask = zGETPTR( lpView->hTask );
         // We've got an error loading the optimistic check view, so get out.
         if ( vCheckView )
            DropView( vCheckView );

         TraceLineI( "(oi) Error loading Optimistic check view.  RC = ", nRC );

         // "KZOEE092 - Couldn't re-activate OI for optimistic lock check",
         fnIssueCoreError( lpTask, lpView, 8, 92, 0, 0, 0 );
         return( zCALL_ERROR );
      }

      // We're about to compare the OIs but first check to see if we should
      // ignore non-key values for include-only entities.
      lCmprCntrl = zCOMPAREOI_PERSISTONLY | zCOMPAREOI_RETURN;
      if ( lpViewOD->nLock == zLL_OPTIMISTIC_NOINC )
         lCmprCntrl |= zCOMPAREOI_IGNOREINC;

      // We now have a copy of the original OI and the current one.  Compare
      // the two and see if they are the same.  If they are not, then there
      // is an error.
      nRC = fnCompareOI_ToOI( zGETPTR( lpViewOI->vOriginalOI ), vCheckView,
                              lCmprCntrl );
      TraceLineI( "(oi) Optimistic locking compare RC = ", nRC );
      DropView( vCheckView );  // We no longer need this...
      if ( nRC )
      {
         LPTASK lpTask = zGETPTR( lpView->hTask );
         // "KZOEE093 - Optimistic locking error -- OI has changed since it was activated",
         fnIssueCoreError( lpTask, lpView, 8, 93, 0, 0, 0 );
         return( zOPTIMISTIC_LOCK_ERROR );
      }

   } // if ( OPTIMISTIC LOCKING )...

   // Perform some pre-commit stuff.  fnCommitPreLoops does:
   //    o  Sets any auto-sequence attributes.
   //    o  Turns off "hidden" flag so db-handler can access all data.
   nRC = fnCommitPreLoops( lpCurrentTask, lpView, &lpLastEntityInstance,
                           &lHiddenCnt );
   if ( nRC )
      return( nRC );

   lpRootEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );

   // Now we pass the chain once each to do relationship deletes, deletes,
   // relationship inserts, and updates. The delete passes are done in reverse
   // hierarchical order so deletes occur from the bottom up.

   //==============================================================
   // PASS Number 1, do excludes (relationship deletes).
   if ( nRC == 0 )
   {
      for ( lpEntityInstance = lpLastEntityInstance;
            lpEntityInstance && nRC == 0;
            lpEntityInstance = zGETPTR( lpEntityInstance->hPrevHier ) )
      {
         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // EIs down a derived path don't get committed to the database.
         // Since all children of a derived EI are also derived we can skip
         // the twins of the current EI.
         if ( lpViewEntity->bDerivedPath )
         {
            while ( lpEntityInstance->hPrevTwin )
               lpEntityInstance = zGETPTR( lpEntityInstance->hPrevTwin );

            continue;
         }

#if ( VIEWENT_RULES )
         // Skip the EI if we don't allow excluding this entity.
         if ( lpViewEntity->bExclude == FALSE )
            continue;
#endif

         // Exclude entity if the entity...
         if ( lpEntityInstance->u.nInd.bExcluded             && // was excluded...
              lpEntityInstance->u.nInd.bDBHExcluded == FALSE && // wasn't committed...
              lpEntityInstance->u.nInd.bIncluded == FALSE    && // wasn't inc'd and...
              lpEntityInstance->u.nInd.bCreated == FALSE )      // wasn't created
         {
            // Set entity cursor to point to lpEntityInstance.
            fnEstablishViewForInstance( lpView, 0, lpEntityInstance );

            // Call DBHandler routine.
            nRC = (*pOper)( (zLONG) lpView->hTask, DBH_Entity | DBH_DeleteRel, 0,
                            lpViewOD, lpViewEntity, lpView, 0, &lpPtr );

            lpEntityInstance->u.nInd.bDBHExcluded = TRUE;

            // Set the bDBHExcluded flag for all linked EIs that have the
            // exact same relationship.
            fnMarkDuplicateRelationship( lpEntityInstance, FALSE );
         }

      }  // for ( lpEntityInstance ...)...

   }  // if ( lpFirstDeleteRel )...

   //==============================================================
   // PASS Number 2, do deletes.
   if ( nRC == 0 )
   {
      for ( lpEntityInstance = lpLastEntityInstance;
            lpEntityInstance && nRC == 0;
            lpEntityInstance = zGETPTR( lpEntityInstance->hPrevHier ) )
      {
         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // EIs down a derived path don't get committed to the database.
         // Since all children of a derived EI are also derived we can skip
         // the twins of the current EI.
         if ( lpViewEntity->bDerivedPath )
         {
            while ( lpEntityInstance->hPrevTwin )
               lpEntityInstance = zGETPTR( lpEntityInstance->hPrevTwin );

            continue;
         }

#if ( VIEWENT_RULES )
         // If we don't allow deletes then skip it.
         if ( lpViewEntity->bDelete == FALSE )
            continue;
#endif

         // Delete entity if prev dbcall was OK and the entity...
         if ( lpEntityInstance->u.nInd.bDeleted             && // was deleted and...
              lpEntityInstance->u.nInd.bDBHDeleted == FALSE && // wasn't committed and...
              lpEntityInstance->u.nInd.bCreated == FALSE    && // wasn't created and...
              lpEntityInstance->u.nInd.bIncluded == FALSE )    // wasn't included
         {
            zBOOL bDelete = FALSE;  // process each entity normally

            // Set entity cursor to point to lpEntityInstance.
            fnEstablishViewForInstance( lpView, 0, lpEntityInstance );

            // Start dks ... 2006.01.25
            if ( lpEntityInstance->hParent )
            {
               LPVIEWENTITY      lpVE_Parent;
               LPVIEWENTITY      lpVE_NextHier;
               LPENTITYINSTANCE  lpEI_Parent;

               lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
               lpVE_NextHier = zGETPTR( lpViewEntity->hNextHier );
               lpVE_Parent = zGETPTR( lpViewEntity->hParent );
               lpEI_Parent = zGETPTR( lpEntityInstance->hParent );
               if ( lpEI_Parent->u.nInd.bDeleted &&    // parent was deleted and...
                    lpViewEntity->bPDelete &&          // entity has ParentDelete behavior and...
                    lpVE_Parent->bSingleKey &&         // parent entity is single key and...
                    lpEntityInstance->hPrevTwin &&     // more than one instance to delete and...
                    lpViewEntity->bDerivedPath == FALSE && // cannot be derived
                    (lpVE_NextHier == 0 ||
                     lpVE_NextHier->hParent != lpEntityInstance->hViewEntity) )  // cannot have child entities
               {
                  // This should be the condition we are looking for ... dks ... 2006.01.25
                  bDelete = TRUE;       // call DBHandler once in the loop below
               }
            }
            // End dks ... 2006.01.25

            // Call DBHandler routine.
            if ( bDelete )  // dks ... 2006.01.25
            {
               lpEntityInstance->u.nInd.bDBHDeleteAll = TRUE;  // call delete special case
               nRC = (*pOper)( (zLONG) lpView->hTask,
                               DBH_Entity | DBH_Delete | DBH_DeleteAll, 0,
                               lpViewOD, lpViewEntity, lpView, 0, &lpPtr );

               // Flag each twin that message has been sent to handler.
               while ( lpEntityInstance->hPrevTwin )
               {
                  lpEntityInstance->u.nInd.bDBHDeleted = TRUE;
                  lpEntityInstance = zGETPTR( lpEntityInstance->hPrevTwin );
               }
            }
            else
            {
               // This is the only original code prior to 2006.01.25
               nRC = (*pOper)( (zLONG) lpView->hTask, DBH_Entity | DBH_Delete, 0,
                               lpViewOD, lpViewEntity, lpView, 0, &lpPtr );
            }  // dks ... 2006.01.25

            // Flag that message has been sent to handler.
            lpEntityInstance->u.nInd.bDBHDeleted = TRUE;

            // Turn on the DBHDeleted flag for all linked instances.  This
            // will keep them from being deleted again.
            for ( lpLinked = zGETPTR( lpEntityInstance->hNextLinked );
                  lpLinked && lpLinked != lpEntityInstance;
                  lpLinked = zGETPTR( lpLinked->hNextLinked ) )
            {
               lpLinked->u.nInd.bDBHDeleted = TRUE;
            }
         }

      }  // while ( lpEntityInstance && nRC == 0 )...

   }  // if ( lpFirstDelete )...

   //==============================================================
   // PASS Number 3, do creates.
   if ( nRC == 0 )
   {
      for ( lpEntityInstance = lpRootEntityInstance;
            lpEntityInstance && nRC == 0;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // EIs down a derived path don't get committed to the database.
         // Since all children of a derived EI are also derived we can skip
         // the twins of the current EI.
         if ( lpViewEntity->bDerivedPath )
         {
            while ( lpEntityInstance->hNextTwin )
               lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );

            continue;
         }

#if ( VIEWENT_RULES )
         // If we don't allow creates then skip it.
         if ( lpViewEntity->bCreate == FALSE )
            continue;
#endif

         // Create the entity if the entity...
         if ( lpEntityInstance->u.nInd.bDBHCreated == FALSE && // not committed and...
              lpEntityInstance->u.nInd.bCreated             && // was created and...
              lpEntityInstance->u.nInd.bDeleted == FALSE    && // wasn't deleted and...
              lpEntityInstance->u.nInd.bHidden == FALSE )      // is not hidden
         {
            // Set entity cursor to point to lpEntityInstance.
            fnEstablishViewForInstance( lpView, 0, lpEntityInstance );

            // Call DBHandler routine.
            nRC = (*pOper)( (zLONG) lpView->hTask, DBH_Entity | DBH_Insert, 0,
                            lpViewOD, lpViewEntity, lpView, 0, &lpPtr );

            // Flag that message sent to handler
            lpEntityInstance->u.nInd.bDBHCreated = TRUE;

            // Turn on the dbh flag for all linked instances.  This will
            // keep them from being created again.
            for ( lpLinked = zGETPTR( lpEntityInstance->hNextLinked );
                  lpLinked && lpLinked != lpEntityInstance;
                  lpLinked = zGETPTR( lpLinked->hNextLinked ) )
            {
               lpLinked->u.nInd.bDBHCreated = TRUE;

               // If the linked instance is flagged as created then we need
               // to set it's included flag on so that the *relationship*
               // is still created.
               if ( lpLinked->u.nInd.bCreated )
                  lpLinked->u.nInd.bIncluded = TRUE;
            }
         }
      } // for ( lpEntityInstance && nRC == 0 )

   } // if ( nRC )...

   //==============================================================
   // PASS Number 4, do insert relationships
   if ( nRC == 0 )
   {
      for ( lpEntityInstance = lpRootEntityInstance;
            lpEntityInstance && nRC == 0;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // EIs down a derived path don't get committed to the database.
         // Since all children of a derived EI are also derived we can skip
         // the twins of the current EI.
         if ( lpViewEntity->bDerivedPath )
         {
            while ( lpEntityInstance->hNextTwin )
               lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );

            continue;
         }

#if ( VIEWENT_RULES )
         // If we don't allow includes then skip it.
         if ( lpViewEntity->bInclude == FALSE )
            continue;
#endif

         // If the entity doesn't have a parent (i.e. it's the root) then
         // we don't want to include it...there's nothing to include.  So
         // just flag it as already included.
         if ( lpEntityInstance->hParent == 0 )
         {
            lpEntityInstance->u.nInd.bDBHIncluded = TRUE;
            continue;
         }

         // Include relationship if prev dbcall was OK and the entity...
         if ( lpEntityInstance->u.nInd.bIncluded             && // was included and...
              lpEntityInstance->u.nInd.bExcluded == FALSE    && // wasn't committed and...
              lpEntityInstance->u.nInd.bDBHIncluded == FALSE && // wasn't committed and...
              lpEntityInstance->u.nInd.bHidden == FALSE )       // is not hidden.
         {
            // Set entity cursor to point to lpEntityInstance.
            fnEstablishViewForInstance( lpView, 0, lpEntityInstance );

            // Call DBHandler routine.
            nRC = (*pOper)( (zLONG) lpView->hTask, DBH_Entity | DBH_InsertRel, 0,
                            lpViewOD, lpViewEntity, lpView, 0, &lpPtr );

            lpEntityInstance->u.nInd.bDBHIncluded = TRUE;

            // Set the bDBHIncluded flag for all linked EIs that have the
            // exact same relationship as lpEntityInstance.
            fnMarkDuplicateRelationship( lpEntityInstance, TRUE );
         }
      } // for ( lpEntityInstance != lpStopInstance && nRC == 0 )
   } // if ( nRC >= 0 )...

   //==============================================================
   // PASS Number 5, do entity updates
   if ( nRC == 0 )
   {
      for ( lpEntityInstance = lpRootEntityInstance;
            lpEntityInstance && nRC == 0;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // EIs down a derived path don't get committed to the database.
         // Since all children of a derived EI are also derived we can skip
         // the twins of the current EI.
         if ( lpViewEntity->bDerivedPath )
         {
            while ( lpEntityInstance->hNextTwin )
               lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );

            continue;
         }

#if ( VIEWENT_RULES )
         if ( lpViewEntity->bUpdate == FALSE )
         {
            // the DB is relational and we need to update because of an
            // included or excluded entity.
            if ( bRelational == FALSE ||
                 (lpEntityInstance->u.nInd.bIncluded == FALSE &&
                  lpEntityInstance->u.nInd.bExcluded == FALSE) )
            {
               continue;
            }
         }
#endif

         // Update entity if the entity...
         if ( lpEntityInstance->u.nInd.bDBHUpdated == FALSE && // not already updated...
              lpEntityInstance->u.nInd.bUpdated == TRUE     && // was updated and...
              lpEntityInstance->u.nInd.bHidden == FALSE     && // isn't hidden and...
              lpEntityInstance->u.nInd.bCreated == FALSE    && // wasn't created and...
              lpEntityInstance->u.nInd.bDeleted == FALSE )     // wasn't deleted and...
         {
            // Set entity cursor to point to lpEntityInstance.
            fnEstablishViewForInstance( lpView, 0, lpEntityInstance );

            // Call DBHandler routine.
            nRC = (*pOper)( (zLONG) lpView->hTask, DBH_Entity | DBH_Update, 0,
                            lpViewOD, lpViewEntity, lpView, 0, &lpPtr );

            // Flag that message sent to handler
            lpEntityInstance->u.nInd.bDBHUpdated = TRUE;

            // If the EI is flagged as excluded then we have updated the EI
            // to blank out an empty key so now flag it as hidden.
            if ( lpEntityInstance->u.nInd.bExcluded )
               lpEntityInstance->u.nInd.bHidden = TRUE;

            // Turn on the dbh flag for all linked instances.  This will
            // keep them from being updated again.
            for ( lpLinked = zGETPTR( lpEntityInstance->hNextLinked );
                  lpLinked && lpLinked != lpEntityInstance;
                  lpLinked = zGETPTR( lpLinked->hNextLinked ) )
            {
               lpLinked->u.nInd.bDBHUpdated = TRUE;
            }
         }
         else
         if ( lpEntityInstance->u.nInd.bSequenceUpdt )
         {
            // Set entity cursor to point to lpEntityInstance.
            fnEstablishViewForInstance( lpView, 0, lpEntityInstance );

            // Call DBHandler routine.
            nRC = (*pOper)( (zLONG) lpView->hTask, DBH_Entity | DBH_UpdateSeq, 0,
                            lpViewOD, lpViewEntity, lpView, 0, &lpPtr );

            // Flag that message sent to handler
            lpEntityInstance->u.nInd.bDBHUpdated = TRUE;
         }
      }  // for ( lpEntityInstance && nRC == 0 )...
   }  // if ( nRC == 0 )...

   //==============================================================
   // All deletes, updates, and inserts have been performed.

   // Turn the hidden flag back on for deleted/excluded instances.
   for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
   {
      if ( lpEntityInstance->u.nInd.bDeleted ||
           lpEntityInstance->u.nInd.bExcluded )
      {
         lpEntityInstance->u.nInd.bHidden = TRUE;
      }
   }

   // If the view is left at a subobject after processing, reset it
   // back to the top level
   while ( fnResetViewFromSubobject( lpView ) == 0 );

   if ( nRC < 0 )
   {
      if ( nRC < zDUPLICATE_ROOT )
         return( zCALL_ERROR );
      else
         return( nRC );
   }

   return( 0 ); // Everything OK.

} // fnCommitSingleOI

//./ ADD NAME=fnCommitObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:
//
//  PURPOSE:      To commit a group of OIs.  Performs the following:
//
//                Starts the database transaction.
//                Commit each view using fnCommitSingleOI.
//                Closes the database transaction.
//                Drop pessimistic locks.
//                Restore optimistic locking OIs.
//                Cleanup views (drop deleted instances).
//
//  PARAMETERS:
//
//  RETURNS:    0           - Everthing OK
//              zCALL_ERROR - Oops!
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 8
zSHORT LOCALOPER
fnCommitObjectInstance( LPVIEWCLUSTER  lpViewCluster,
                        zVIEW          lpViewArray[],
                        zSHORT         nViewCount,
                        zPSHORT        pnViewErrorIdx,
                        LPTASK         lpCurrentTask,
                        zLONG          lControl,
                        VIEWARRAYBLOCK *pViewArrayBlock )
{
   LPVIEWOD             lpViewOD;
   LPVIEWOI             lpViewOI;
   LPVIEWCSR            lpViewCsr;
   LPTASKDBHANDLER      lpTaskDBHandler;
   LPENTITYINSTANCE     lpEntityInstance;
   zPGKHOPER            pGKOper = 0;
   zPDBHOPER            pOper;
   zPVOID               lpPtr;
   zVIEW                lpKZGKHWOB;
   zVIEW                vSubtask;
   zBOOL                bTransactionStartedHere;
   zSHORT               k;
   zSHORT               nRC;

   // Find the first non-zero view in the list.  We'll use this to pass into
   // the DBHandler so that the DBH knows what DB where dealing with.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewCluster[ k ].vOI )
      {
         vSubtask = lpViewCluster[ k ].vOI;
         break;
      }
   }

   // Turn off the DBH flags for all entity instances.  This allows
   // us to figure out if the entity instance was processed.
   for ( k = 0; k < nViewCount; k++ )
   {
      if ( lpViewArray[ k ] == 0 )
         continue;

      lpViewCsr = zGETPTR( lpViewArray[ k ]->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         lpEntityInstance->u.nInd.bDBHCreated =
            lpEntityInstance->u.nInd.bDBHIncluded  =
            lpEntityInstance->u.nInd.bDBHDeleted   =
            lpEntityInstance->u.nInd.bDBHExcluded  =
            lpEntityInstance->u.nInd.bDBHUpdated   =
            lpEntityInstance->u.nInd.bSequenceUpdt =
            lpEntityInstance->u.nInd.bGenKeyNeeded =
            lpEntityInstance->u.nInd.bNoGenKey     =
            lpEntityInstance->u.nInd.bForeignKeys  = 0;
      }
   }

   // Initialize the genkey handler and create the genkeys.  This will also
   // determine if any EI's need to have foreign keys set.
   lpKZGKHWOB = 0;
   nRC = fnInitializeGenKeys( lpViewArray, nViewCount, pnViewErrorIdx,
                              lpCurrentTask, &lpKZGKHWOB, &pGKOper,
                              pViewArrayBlock );
   if ( nRC == zCALL_ERROR )
      return( zCALL_ERROR );

   // Make sure that DBHandler is out there.
   lpTaskDBHandler = fnGetDBHandlerOper( lpCurrentTask, vSubtask, &pOper );
   if ( lpTaskDBHandler == 0 )
      return( zCALL_ERROR );

   if ( lpTaskDBHandler->bTranStarted )
   {
      bTransactionStartedHere = FALSE;
      lpPtr = lpTaskDBHandler->lpConnection;
   }
   else
   {
      // Call DBHandler routine to issue start of transaction.
      lpViewOD = zGETPTR( vSubtask->hViewOD );
      lpPtr = 0;
      nRC = (*pOper)( (zLONG) zGETHNDL( lpCurrentTask ),
                      DBH_Object | DBH_TranBegin, DBH_StoreOI, lpViewOD,
                      0, vSubtask, 0, &lpPtr );
      if ( nRC < 0 )
         return( zCALL_ERROR );

      bTransactionStartedHere = TRUE;
      lpTaskDBHandler->bTranStarted = TRUE;
      lpTaskDBHandler->lpConnection = lpPtr;
   }

   // Commit each view separately.
   for ( k = 0; k < nViewCount && nRC >= 0; k++ )
   {
      // If the view is 0 then we're not supposed to commit it (maybe it
      // wasn't changed?) so just skip it.
      if ( lpViewArray[ k ] == 0 )
         continue;

      nRC = fnCommitSingleOI( lpViewArray[ k ], lControl, lpCurrentTask,
                              lpTaskDBHandler );

      // If there was an error then stop committing.
      if ( nRC < 0 )
      {
         if ( pnViewErrorIdx )
            *pnViewErrorIdx = k;

         break;
      }
   }

   // If genkey work object defined, call genkey handler to commit genkeys.
   if ( lpKZGKHWOB )
   {
      if ( nRC == 0 )
         (*pGKOper)( DBH_Commit, vSubtask, 0, 0, lpKZGKHWOB );
      else
         (*pGKOper)( DBH_Rollback, vSubtask, 0, 0, lpKZGKHWOB );

      fnDropObjectInstance( lpKZGKHWOB );
   }

   // End the transaction if the transaction was started in this function call.
   if ( bTransactionStartedHere || lControl & zCOMMIT_FORCETRAN )
   {
      // We're about to close the transaction so set flag.
      lpTaskDBHandler->bTranStarted = FALSE;
      lpTaskDBHandler->lpConnection = 0;

      if ( nRC < 0 )
      {
         // Call DBHandler routine to issue rollback.
         (*pOper)( (zLONG) zGETHNDL( lpCurrentTask ),
                   DBH_Object | DBH_Rollback, 0, lpViewOD,
                   0, vSubtask, 0, &lpPtr );
      }
      else
      {
         // Incremental update succeeded; issue commit to DBhandler.
         nRC = (*pOper)( (zLONG) zGETHNDL( lpCurrentTask ),
                         DBH_Object | DBH_Commit, DBH_StoreOI, lpViewOD, 0,
                         vSubtask, 0, &lpPtr );
      }
   }

   // If view was activated with locking then delete the locks.
   if ( nRC >= 0 )
   {
      // A LOD has been committed using pessimistic locks.  Delete the locks
      // on the LODs.
      if ( fnRemoveLocksOnOIs( lpCurrentTask, lpViewCluster,
                               nViewCount, pnViewErrorIdx ) != 0 )
      {
         nRC = zCALL_ERROR;
      }
   }

   // If the transaction failed, return an error.
   if ( nRC < 0 )
      return( nRC );

   // If the commit is OK and we have optimistic locking, then drop the
   // "old" OI and replace it with a copy of the new OI.
   for ( k = 0; k < nViewCount; k++ )
   {
      zVIEW vTemp;

      if ( lpViewArray[ k ] == 0 )
         continue;

      lpViewCsr = zGETPTR( lpViewArray[ k ]->hViewCsr );
      lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      if ( lpViewOI->lActivateControl & zACTIVATE_WITH_LOCKING &&
           (lpViewOD->nLock == zLL_OPTIMISTIC_NOINC ||
            lpViewOD->nLock == zLL_OPTIMISTIC_CMPRALL) )
      {
         fnDropView( zGETPTR( lpViewOI->vOriginalOI ) );
         ActivateOI_FromOI_ForTask( &vTemp, lpViewArray[ k ], 0, zMULTIPLE );
         lpViewOI->vOriginalOI = zGETHNDL( vTemp );
         vTemp->bOrigView      = TRUE;
         vTemp->bViewLocked    = TRUE;
         vTemp->hMainOI        = lpViewCsr->hViewOI;
      }

      if ( (lControl & zCOMMIT_NOCLEANUP) == 0 )
      {
         // Clean-up and reclaim hidden (i.e. deleted) instances.
         fnCleanupInstance( lpViewArray[ k ], 1 );
      }

      // Mark the object instance as not updated.
      lpViewOI->bUpdated = lpViewOI->bUpdatedFile = 0;
   }

   return( 0 );
}

zSHORT OPERATION
fnPutDataToFile( zVIEW   lpTaskView,
                 zPVOID  lpvData,
                 zCPCHAR cpcBuffer,
                 zULONG  ulLth,
                 zCHAR   cDataType )
{
   LPFILEDATA lpFileData = (LPFILEDATA) lpvData;

   if ( ulLth )
      return( SysWriteLineLth( lpTaskView, lpFileData->hFile, cpcBuffer, ulLth, TRUE ) );
   else
      return( SysWriteLine( lpTaskView, lpFileData->hFile, cpcBuffer ) );
}

/*
=fnWriteOI_ToTextStream

   NOTE: This function uses the bWritten flag to indicate whether or not
   an entity instance has been written to the stream.

*/

zSHORT
fnWriteOI_ToTextStream( zVIEW          lpView,
                        LPFN_PUTSTREAM lpfnStreamFunc,
                        zPVOID         lpvData,
                        zBOOL          bIncremental,
                        zLONG          lControl )
{
   LPAPP                lpApp;
   LPVIEWOD             lpViewOD;
   LPVIEWOI             lpViewOI;
   LPVIEWENTITY         lpViewEntity;
   LPVIEWATTRIB         lpViewAttrib;
   LPVIEWCSR            lpViewCsr;
   LPENTITYINSTANCE     lpEntityInstance;
   ViewEntityCsrRecord  ViewEntityCsr;
   LPTASK               lpTask;
   LPATTRIBFLAGS        lpAttribFlags;
   zPCHAR               pchAttr;
   zPCHAR               pchBuffer = 0;
   zCHAR                szWorkString[ 300 ];
   zLONG                lLastLinkedInstance;
   zLONG                lHierCount;
   zULONG               ulLth;
   zULONG               uPos;
   zBOOL                bMsgBox = TRUE;
   zSHORT               nLevel;
   zLONG                k;
   zSHORT               nRC = zCALL_ERROR;

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   lpViewOD  = zGETPTR( lpViewOI->hViewOD );
   lpApp     = zGETPTR( lpViewOD->hApp );
   lpTask    = zGETPTR( lpView->hTask );

   // If user wants entity tags, write out the tag for the OI.
   if ( lControl & zENTITY_TAGS )
   {
      if ( lControl & zCOMPRESSED )
         sprintf_s( szWorkString, zsizeof( szWorkString ), "mOITAG %lx", (zLONG) lpViewOI );
      else
         sprintf_s( szWorkString, zsizeof( szWorkString ), "mOITAG %lx", (zLONG) lpViewOI );

      if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
         return( zCALL_ERROR );
   }
   else
   if ( lpViewOI->lTag )
   {
      // If the tag for the current OI is non-zero, then we'll write it.
      if ( lControl & zCOMPRESSED )
         sprintf_s( szWorkString, zsizeof( szWorkString ), "mOITAG %lx", lpViewOI->lTag );
      else
         sprintf_s( szWorkString, zsizeof( szWorkString ), "mOITAG %lx", lpViewOI->lTag );

      if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
         return( zCALL_ERROR );
   }

   // Set some flags.
   for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
   {
      lpEntityInstance->u.nInd.bWritten =
         lpEntityInstance->u.nInd.bRecordOwner = FALSE;

      lpEntityInstance->lHierCount = 0;
   }

   // We need to write some information about the OI.
   if ( lControl & zINCREMENTAL )
   {
      zULONG uFlags = 0;

      uFlags = 0;
      if ( lpViewOI->bIsLocked )
         uFlags |= zOI_ISLOCKED;

      if ( lpView->bReadOnly )
         uFlags |= zOI_READONLY;

      if ( uFlags )
      {
         if ( lControl & zCOMPRESSED )
            sprintf_s( szWorkString, zsizeof( szWorkString ), "mOIFLAGS %lx", uFlags );
         else
            sprintf_s( szWorkString, zsizeof( szWorkString ), "mOIFLAGS %lx", uFlags );

         if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
            return( zCALL_ERROR );
      }
   }

   // If we are writting the OI in a compressed format, we need a buffer.
   if ( lControl & zCOMPRESSED )
   {
      // Allocate a buffer to contain attribute data for an entity.
      pchBuffer = fnAllocDataspace( lpTask->hFirstDataHeader,
                                    zENTITY_BUFFER_SIZE, 0, 0, iBuffer );
      pchBuffer = zGETPTR( pchBuffer );
   }

   // write out the entity instances
   lpAttribFlags = 0;
   lHierCount = 0;
   lLastLinkedInstance = -1;      // last linked relative instance counter
   for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
   {
      zBOOL  bEntityIsCompressed;
      zPCHAR pchBufferEnd;
      zBOOL  bValuesStored;

      lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

      // This entity can be compressed if:
      // o  lControl specifies compression.
      // o  The max size of all the attributes for the entity is smaller
      //    then the buffer we set up to hold all the attribute values.
      bEntityIsCompressed = lControl & zCOMPRESSED &&
                            lpViewEntity->ulMaxLth < zENTITY_BUFFER_SIZE;

#if 0
      // DGC 02/25/98
      // Following code is called and may be (?) needed.
      if ( bIncremental &&
           lpEntityInstance->u.nInd.bExcluded &&
           lpEntityInstance->u.nInd.bDeleted &&
           lpEntityInstance->u.nInd.bCreated == FALSE &&
           lpEntityInstance->u.nInd.bIncluded == FALSE &&
           lpEntityInstance->u.nInd.bRelOwner &&
           lpViewEntity->bDelete == FALSE &&
           lpViewEntity->bExclude )
      {
         LPENTITYINSTANCE lpDupInstance;
         LPVIEWENTITY     lpDupViewEntity;

         lpDupInstance = lpEntityInstance;
         for ( ; ; )
         {
            lpDupInstance = fnFindDuplicateRelationship( lpDupInstance, 1, 0 );
            if ( lpDupInstance == 0 || lpDupInstance == lpEntityInstance )
               break;

            lpDupViewEntity = zGETPTR( lpDupInstance->hViewEntity );
            if ( lpDupInstance->u.nInd.bDeleted &&
                 lpDupViewEntity->bDerivedPath == FALSE &&
                 lpDupViewEntity->bDelete )
            {
               lpEntityInstance->u.nInd.bExcluded = FALSE;
               break;
            }
            else
            {
               lpDupInstance->u.nInd.bRelOwner = FALSE;
            }
         }
      }
#endif

      // Look to see if the current instance should be written out.  If
      // not we'll skip it and go on to the next one.  All non-hidden
      // instances get written so we'll look for that first.
      if ( lpEntityInstance->u.nInd.bHidden )
      {
         // The EI is hidden.  Don't write the current EI if we're not
         // writing incrementals or if the EI is dead.
         if ( bIncremental == FALSE ||
              fnEntityInstanceIsDead( lpEntityInstance ) )
         {
            nLevel = lpEntityInstance->nLevel;

            for ( lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier );
                  lpEntityInstance;
                  lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
            {
               if ( lpEntityInstance->nLevel <= nLevel )
                  break;
            }

            if ( lpEntityInstance == 0 )
               break;
            else
               lpEntityInstance = zGETPTR( lpEntityInstance->hPrevHier );

            // Continue with the next EI.
            continue;
         }
      }

      lpEntityInstance->lHierCount = lHierCount++;

      // Build the entity name line.
      szWorkString[ 0 ] = 'e';
      if ( lControl & zCOMPRESSED )
      {
         // Use the hierarchical number instead of the entity name.
         sprintf_s( szWorkString + 1, zsizeof( szWorkString ) - 1, "%x %x", lpViewEntity->nHierNbr, lpEntityInstance->nLevel );
         k = zstrlen( szWorkString );
      }
      else
      {
         strcpy_s( szWorkString + 1, zsizeof( szWorkString ) - 1, lpViewEntity->szName );
         k = zstrlen( szWorkString );

         szWorkString[ k++ ] = ' ';
         while ( k < 11 )
            szWorkString[ k++ ] = ' ';

         zltoa( lpEntityInstance->nLevel, szWorkString + k, zsizeof( szWorkString ) - k );
         k = zstrlen( szWorkString );
      }

      // if we are writing an incremental file, write out the indicators.
      if ( bIncremental )
      {
         szWorkString[ k++ ] = ',';
         zbtoa( lpEntityInstance->u.nIndicators, szWorkString + k, zsizeof( szWorkString ) - k );

         if ( lControl & zCOMPRESSED )
         {
            zLONG lTemp;

            // Convert number for decimal format to hexadecimal.
            lTemp = zatol( szWorkString + k );
            zltox( lTemp, szWorkString + k, zsizeof( szWorkString ) - k );
         }
      }

      // Write out the entity name.
      if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
         goto EndOfFunction;

      // If user wants entity tags, write it.
      if ( lControl & zENTITY_TAGS )
      {
         if ( lControl & zCOMPRESSED )
            sprintf_s( szWorkString, zsizeof( szWorkString ), "mETAG %lx", (zLONG) lpEntityInstance );
         else
            sprintf_s( szWorkString, zsizeof( szWorkString ), "mETAG %lx", (zLONG) lpEntityInstance );

         if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
            goto EndOfFunction;
      }
      else
      if ( lpEntityInstance->lTag )
      {
         // If the tag for the current entity instance is non-zero, then we'll
         // write it.
         if ( lControl & zCOMPRESSED )
            sprintf_s( szWorkString, zsizeof( szWorkString ), "mETAG %lx", lpEntityInstance->lTag );
         else
            sprintf_s( szWorkString, zsizeof( szWorkString ), "mETAG %lx", lpEntityInstance->lTag );

         if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
            goto EndOfFunction;
      }

      if ( lControl & zENTITY_KEYS )
      {
         if ( lControl & zCOMPRESSED )
            sprintf_s( szWorkString, zsizeof( szWorkString ), "mEKEY %lx", lpEntityInstance->ulKey );
         else
            sprintf_s( szWorkString, zsizeof( szWorkString ), "mEKEY %lx", lpEntityInstance->ulKey );

         if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
            goto EndOfFunction;
      }

      // If the EI has already been written (this means it's linked to another
      // EI that has already been written) and it has no non-persist record,
      // then we don't need to write it's attribute values.
      lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
      if ( lpEntityInstance->u.nInd.bWritten )
      {
         lLastLinkedInstance = lpEntityInstance->lHierCount;

         if ( lpEntityInstance->u.nInd.bHidden == FALSE &&
              lpEntityInstance->hNonPersistRecord == FALSE )
         {
            bEntityIsCompressed = FALSE; // Make sure we don't write anything
            lpViewAttrib = 0;
         }
      }

      // Set flag to indicate that entity instance has been written to
      // the stream.  Let's also mark all the linked instances.
      if ( lpEntityInstance->u.nInd.bWritten == FALSE &&
           lpEntityInstance->hNextLinked )
      {
         LPENTITYINSTANCE lpLinked;

         // Set the record owner.  This means that this EI will not have
         // link lines written (e.g. "i38,102") for it.
         lpEntityInstance->u.nInd.bRecordOwner = TRUE;

         for ( lpLinked = zGETPTR( lpEntityInstance->hNextLinked );
               lpLinked != lpEntityInstance;
               lpLinked = zGETPTR( lpLinked->hNextLinked ) )
         {
            // For a little insurance we'll only set the flags for EIs in
            // the same OI.
            if ( lpLinked->hViewOI == lpEntityInstance->hViewOI )
               lpLinked->u.nInd.bWritten = TRUE;
            }
         }

      lpEntityInstance->u.nInd.bWritten = TRUE;

      // Some stuff needs to be done if we're storing in compressed format...
      if ( bEntityIsCompressed )
      {
         // pchBufferEnd points to the first unused byte in the compression buffer.
         pchBufferEnd = pchBuffer;

         // In rare cases an entity will have all NULL attribute
         // values (this will usually occur when an instance is linked).
         // If that happens, don't bother writting the attribute values.
         bValuesStored = FALSE;
      }

      ViewEntityCsr.hEntityInstance = zGETHNDL( lpEntityInstance );

      // Write the attribute values.
      for ( ;              // assigned above
            lpViewAttrib;
            lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
      {
         static AttribFlagsRecord ZeroAttribFlags = { 0 };

         // If attribute is derived, don't bother.
         if ( lpViewAttrib->szDerivedOper[ 0 ] && lpViewAttrib->bPersist == FALSE )
         {
            continue;
         }

         // If we are only writing keys and this attr isn't a key then skip it.
         if ( lControl & zWRITE_KEYS_ONLY && lpViewAttrib->bKey == FALSE )
            continue;

         // Get a pointer to the attribute flags if we are writing incremental
         // flags.  If we're not writing incremental then we'll leave the ptr
         // as it is--WHICH HAD BETTER BE 0.
         if ( bIncremental )
         {
            lpAttribFlags = fnGetAttribFlagsPtr( lpEntityInstance,
                                                 lpViewAttrib );

            // If lpAttribFlags is 0 then this means that a data record
            // (i.e. data stick) has been created for this attrib.  Just set
            // lpAttribFlags to point to a 0 flag record.
            if ( lpAttribFlags == 0 )
               lpAttribFlags = &ZeroAttribFlags;
         }

         if ( bEntityIsCompressed && lpViewAttrib->cType != zTYPE_BLOB )
         {
            // If the entity is linked with another, then we don't need to store
            // the attribute value, but we do need to store a dummy value in the
            // attribute buffer.
            if ( lpViewAttrib->bPersist &&
                 lpEntityInstance->lHierCount == lLastLinkedInstance )
            {
               *pchBufferEnd++ = 0;
               continue;
            }

            if ( lpViewAttrib->cType == zTYPE_INTEGER )
            {
               zLONG l;

               if ( fnGetIntegerFromAttribute( &l, lpView, &ViewEntityCsr, lpViewAttrib ) != 0 )
               {
                  // Integer is null so set null value.
                  *pchBufferEnd = 0;
               }
               else
               if ( l >= 0 )
                  zltox( l, pchBufferEnd, zENTITY_BUFFER_SIZE - (pchBufferEnd - pchBuffer) );
               else
               {
                  *pchBufferEnd = '-';
                  zltox( l * -1, pchBufferEnd + 1, zENTITY_BUFFER_SIZE - (pchBufferEnd + 1 - pchBuffer) );
               }
            }
            else
               fnGetStringFromAttribute( pchBufferEnd, zENTITY_BUFFER_SIZE,
                                         lpView, &ViewEntityCsr,
                                         lpViewAttrib, 0 );

            // Check to see if we have a valid (i.e. non-null) attribute
            // value.  If we do, then we've stored a "real" value.
            if ( *pchBufferEnd )
               bValuesStored = TRUE;

            pchBufferEnd += zstrlen( pchBufferEnd ) + 1;

            // If the attrib flags is not 0 then we need to write them as well.
            if ( lpAttribFlags )
            {
               zltox( (zLONG) lpAttribFlags->u.uFlags, pchBufferEnd, zENTITY_BUFFER_SIZE - (pchBufferEnd - pchBuffer) );
               pchBufferEnd += zstrlen( pchBufferEnd ) + 1;
            }

         } // if ( bEntityIsCompressed && lpViewAttrib->cType != zTYPE_BLOB )...
         else
         {
            zBOOL bStringContainsSpecialChars;
            zCHAR szAttribFlags[ 12 ];

            // If the current entity instance is a linked instance then we
            // don't need to store the attribute values because they'll be
            // included from the linked instance.  This is only TRUE for
            // persistent attributes.  Non-persistent attrs need to be stored
            // with the current EI.
            if ( lpViewAttrib->bPersist &&
                 lpEntityInstance->lHierCount == lLastLinkedInstance )
            {
               continue;
            }

            // If lpAttribFlags is not 0 then we're supposed to send the
            // attrib flags for each attribute.  To save space we won't bother
            // sending the flags if they are all off.
            if ( lpAttribFlags && lpAttribFlags->u.uFlags == 0 )
               lpAttribFlags = 0;   // Indicates: don't bother sending flags.

            // If the attrib flags is not 0 then set up string.
            if ( lpAttribFlags )
               sprintf_s( szAttribFlags, zsizeof( szAttribFlags ), ",%lx", lpAttribFlags->u.uFlags );
            else
               szAttribFlags[ 0 ] = 0;

            // If we are here and zCOMPRESSED has been specified, then
            // the entity can't be compressed for some reason (the attribute
            // might be a blob, etc.) but we can still save a few bytes by
            // using XVATOK instead of the name.
            if ( lControl & zCOMPRESSED )
               sprintf_s( szWorkString, zsizeof( szWorkString ), "a%lx%s ", lpViewAttrib->lXVAAttTok, szAttribFlags );
            else
            {
               zCHAR szAttribName[ 50 ];

               sprintf_s( szAttribName, zsizeof( szAttribName ), "%s%s", lpViewAttrib->szName, szAttribFlags );
               sprintf_s( szWorkString, zsizeof( szWorkString ), "a%-9s ", szAttribName );
            }

            k = zstrlen( szWorkString );

            fnGetAddrForAttribute( &pchAttr, lpView, &ViewEntityCsr, 0, lpViewAttrib );

            // If we are dealing with a string, check to see if
            // it contains any special chars (e.g. '\n'). If it does, then
            // we have to store the string as a blob.
            bStringContainsSpecialChars = FALSE;
            if ( lpViewAttrib->cType == zTYPE_STRING )
            {
               zPCHAR pch = pchAttr;

               // We also store the string as a blob if it has more than
               // 254 chars.
               if ( zstrlen( pch ) > 254 )
                  bStringContainsSpecialChars = TRUE;
               else
                  while ( pch[ 0 ] )
                  {
                     if ( CHAR_IS_SPECIAL( pch[ 0 ] ) )
                     {
                        bStringContainsSpecialChars = TRUE;
                        break;
                     }

                     pch++;
                  }
            }

            if ( lpViewAttrib->cType == zTYPE_BLOB ||
                 bStringContainsSpecialChars )
            {
               zCHAR cStreamType;

               if ( lpViewAttrib->cType == zTYPE_BLOB )
               {
                  fnGetAttributeLength( &ulLth, lpView,
                                        zGETPTR( ViewEntityCsr.hEntityInstance ),
                                        lpViewAttrib );
                  cStreamType = zTYPE_BLOB;
               }
               else
               {
                  ulLth = zstrlen( pchAttr ) + 1;
                  if ( ulLth == 1 )
                     ulLth = 0;

                  cStreamType = zTYPE_STRING;
               }

               // If the attribute has a length, then write the length and
               // then the value.
               if ( ulLth )
               {
                  // If we're storing a string with "special" chars, then the
                  // first byte before the length is the "special" flag.
                  if ( bStringContainsSpecialChars )
                     szWorkString[ k++ ] = zSTRING_STORED_AS_BLOB;
                  else
                  if ( lControl & zENCODE_BLOBS )
                     szWorkString[ k++ ] = zBLOB_STORED_ENCODED;

                  zltoa( ulLth, szWorkString + k, zsizeof( szWorkString ) - k );

                  // write out the attribute name and length
                  if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0,
                                          zTYPE_STRING ) )
                     goto EndOfFunction;

                  // write out the data
                  if ( cStreamType == zTYPE_BLOB && (lControl & zENCODE_BLOBS) )
                  {
                     uPos = 0;
                     while ( UUENCODE_NextEncodedLine( szWorkString, pchAttr,
                                                       ulLth, &uPos ) == 1)
                     {
                        //TraceLineS( "Encoded Line: ", szWorkString);
                        if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, cStreamType ) )
                           goto EndOfFunction;
                     }

                     //TraceLineS( "Encoded Line: ", szWorkString);
                     if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, cStreamType ) )
                        goto EndOfFunction;
                  }
                  else
                  if ( cStreamType == zTYPE_STRING )
                  {
                     // PAS 03/09/2001 - to eliminate x00 in the portable
                     //                  files, we temporarily change the
                     //                  byte to the char 0.
                     if ( lControl & zNO_NULL_STRING_TERM )
                     {
                        pchAttr[ ulLth - 1 ] = '0';
                        if ( (*lpfnStreamFunc)( lpView, lpvData, pchAttr,
                                                ulLth, cStreamType ) )
                        {
                           pchAttr[ ulLth - 1 ] = 0;
                           goto EndOfFunction;
                        }
                        else
                           pchAttr[ ulLth - 1 ] = 0;

                     // PAS 03/09/2001 - and above, we change it back before
                     //                  returning
                     }
                     else
                     {
                        if ( (*lpfnStreamFunc)( lpView, lpvData, pchAttr,
                                                ulLth, cStreamType ) )
                        {
                           goto EndOfFunction;
                        }
                     }
                  }
                  else
                  if ( (*lpfnStreamFunc)( lpView, lpvData, pchAttr,
                                          ulLth, cStreamType ) )
                  {
                     goto EndOfFunction;
                  }
               }
               else
               if ( lpAttribFlags )
               {
                  // We need to write the attrib flags so write the attribute
                  // value as NULL.
                  if ( lpViewAttrib->cType == zTYPE_BLOB )
                  {
                     // Add "0" to the end of the string.
                     szWorkString[ k++ ] = '0';
                  }

                  // Null-terminate the string.
                  szWorkString[ k++ ] = 0;

                  // Write it.
                  if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0,
                                          zTYPE_STRING ) )
                  {
                     goto EndOfFunction;
                  }
               }
            } // if ( lpViewAttrib->cType == zTYPE_BLOB || )...
            else
            {
               zBOOL bAttribIsNull;

               // Check to see if we are writing compressed.  This might happen
               // if there are too many attributes to write in the compress
               // buffer.
               if ( lControl & zCOMPRESSED &&
                    lpViewAttrib->cType == zTYPE_INTEGER )
               {
                  zLONG l;

                  // We are writing a compressed file so convert the value to a hex number.
                  if ( fnGetIntegerFromAttribute( &l, lpView, &ViewEntityCsr, lpViewAttrib ) == -1 )
                  {
                     bAttribIsNull = TRUE;

                     // Write the attribute value as a '*' to indicate that the integer is null.
                     szWorkString[ k++ ] = '*';
                     szWorkString[ k++ ] = 0;
                  }
                  else
                  {
                     bAttribIsNull = FALSE;

                     if ( l < 0 )
                     {
                        szWorkString[ k++ ] = '-';
                        l = l * -1;
                     }

                     zltox( l, szWorkString + k, zsizeof( szWorkString ) - k );
                  }
               }
               else
               {
                  if ( fnGetStringFromAttribute( &szWorkString[ k ], 255,
                                                 lpView, &ViewEntityCsr,
                                                 lpViewAttrib, 0 ) == -1 )
                  {
                     bAttribIsNull = TRUE;
                  }
                  else
                     bAttribIsNull = FALSE;
               }

               // Write the value if it's not null OR if there are attribute
               // flags.  If there are attrib flags then we need to
               // keep track of null values.
               if ( bAttribIsNull == FALSE || lpAttribFlags )
               {
                  if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
                  {
                     goto EndOfFunction;
                  }
               }

            } // if ( lpViewAttrib->cType == zTYPE_BLOB || )...else...

         } // if ( lControl & zCOMPRESSED )...else...

      } // for ( lpViewAttrib... )...

      if ( bEntityIsCompressed && bValuesStored )
      {
         zCHAR szLth[ 20 ];

         ulLth = (zULONG) (pchBufferEnd - pchBuffer);

         // Set first char to 'a' to indicate that it's attribute data.
         // The next char is a space to differentiate it with a normal
         // attribute value line.
         sprintf_s( szLth, zsizeof( szLth ), "a %x", ulLth );
         if ( (*lpfnStreamFunc)( lpView, lpvData, szLth, zstrlen( szLth ), zTYPE_STRING ) )
         {
            goto EndOfFunction;
         }

         // Now send the buffer.
         if ( (*lpfnStreamFunc)( lpView, lpvData, pchBuffer, ulLth, zTYPE_STRING ) )
            goto EndOfFunction;
      }
      else
      {
         if ( (lControl & zCOMPRESSED) == 0 )
         {
            // Write a blank line just to make things look pretty.
            if ( (*lpfnStreamFunc)( lpView, lpvData, "", 0, zTYPE_STRING ) )
               goto EndOfFunction;
         }
      }

   } // for ( lpEntityInstance... )...

   // If any intra-object linked instances were found, create
   // link records now.
   if ( lLastLinkedInstance > -1 )
   {
      LPENTITYINSTANCE lpSourceEntityInstance;

      for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         // If we've gone past the last linked instance break.
         if ( lpEntityInstance->lHierCount > lLastLinkedInstance )
            break;

         // Look to see if the current instance should be written out.  If
         // not we'll skip it and go on to the next one.  All non-hidden
         // instances get written so we'll look for that first.
         if ( lpEntityInstance->u.nInd.bHidden )
         {
            // We'll skip hidden entities if:
            // o  We aren't writing incrementals
            //    -or-
            // o  The EI is "dead" e.g. created and deleted.
            if ( bIncremental == FALSE ||
                 fnEntityInstanceIsDead( lpEntityInstance ) )
            {
               // The current instance should not be written to the file.
               // This also means that it's children should not be written.
               // Skip the children.
               nLevel = lpEntityInstance->nLevel;
               for ( lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier );
                     lpEntityInstance;
                     lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
               {
                  if ( lpEntityInstance->nLevel <= nLevel )
                     break;
               }

               // If no more instance break loop.
               if ( lpEntityInstance == 0 )
                  break;

               // Do the following so that when the 'for' loop gets the next
               // entity instance it will be the one we want.
               lpEntityInstance = zGETPTR( lpEntityInstance->hPrevHier );

               // Skip the hidden instance.
               continue;
            }
         }

         // If the entity is not linked to another entity then there are no
         // link cards to write, so skip it.
         if ( lpEntityInstance->hNextLinked == 0 )
            continue;

         // If the entity is the record owner then we don't write link cards.
         // Link cards are written for the non-record owner.
         if ( lpEntityInstance->u.nInd.bRecordOwner )
            continue;

         // Look for the record owner in the same OI.
         lpSourceEntityInstance = zGETPTR( lpEntityInstance->hNextLinked );
         while ( lpSourceEntityInstance->hViewOI != lpEntityInstance->hViewOI ||
                 lpSourceEntityInstance->u.nInd.bRecordOwner == FALSE )
         {
            lpSourceEntityInstance =
                                 zGETPTR( lpSourceEntityInstance->hNextLinked );
            if ( lpSourceEntityInstance == lpEntityInstance )
               break;
         }

         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // If lpSourceEntityInstance == lpEntityInstance then no other
         // linked instances where found in the loop above.
         if ( lpSourceEntityInstance == lpEntityInstance )
         {
            LPTASK lpTask = zGETPTR( lpView->hTask );
            zVIEW           vWork;
            LPVIEWENTITYCSR lpWorkViewEntityCsr;

            CreateViewFromViewForTask( &vWork, lpView, 0 );
            lpWorkViewEntityCsr =
               fnEstablishViewForInstance( vWork, 0, lpSourceEntityInstance );

            while ( lpWorkViewEntityCsr )
            {
               fnDisplayEntityInstance( vWork, lpWorkViewEntityCsr, 0, 0 );
               lpWorkViewEntityCsr = zGETPTR( lpWorkViewEntityCsr->hParent );
            }

            DropView( vWork );

            // "KZOEE078 - Internal error, linked instance "
            // "           has no visible owner"
            fnIssueCoreError( lpTask, lpView, 16, 78, (zLONG) 0,
                              lpViewEntity->szName, 0 );
         }

#ifdef DEBUG
         // Check to make sure the linked EI's have the same ER token.
         {
            LPVIEWENTITY lpSrcViewEntity;

            lpViewEntity    = zGETPTR( lpEntityInstance->hViewEntity );
            lpSrcViewEntity = zGETPTR( lpSourceEntityInstance->hViewEntity );

            if ( lpSrcViewEntity->lEREntTok != lpViewEntity->lEREntTok )
            {
               TraceLine( "(oi) Error (OD: %s) - Src View Entity: %s Token: %d  View Entity: %s Token = %d",
                          lpViewOD->szName, lpSrcViewEntity->szName, lpSrcViewEntity->lEREntTok,
                          lpViewEntity->szName, lpViewEntity->lEREntTok );
               if ( bMsgBox )
               {
                  bMsgBox = FALSE;
                  SysMessageBox( lpView, szlOE_SystemError,
                                 "Error writing OI: ER Tokens don't match for linked entities!", 1 );
               }
            }
         }
#endif

         if ( lControl & zCOMPRESSED )
         {
            sprintf_s( szWorkString, zsizeof( szWorkString ), "i%lx %lx",
                       lpEntityInstance->lHierCount,
                       lpSourceEntityInstance->lHierCount );
         }
         else
         {
            szWorkString[ 0 ] = 'i';
            zltoa( lpEntityInstance->lHierCount, szWorkString + 1, zsizeof( szWorkString ) - 1 );
            k = zstrlen( szWorkString );
            do
            {
               szWorkString[ k++ ] = ' ';
            } while ( k < 11 );

            zltoa( lpSourceEntityInstance->lHierCount, szWorkString + k, zsizeof( szWorkString ) - k );
         }

         if ( lpEntityInstance->lHierCount != lpSourceEntityInstance->lHierCount )
         {
            if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
               goto EndOfFunction;
         }

      } // for ...

   } // if ( lLastLinkedInstance > -1 )...

   //
   // Check to see if we need to save the cursor positions.
   //
   // We save the cursor positions by storing each entity cursor as:
   //    cent-#, absolute-entity-instance-#
   // The numbers are stored as hex values.  For example, the root cursor
   // would be saved as:
   //    c1, 1
   // Absence of the cursor record means the cursor is null.
   //
   // Note: if lpEntityInstance->u.nInd.bWritten is 0, then the entity
   // instance wasn't written to the stream.
   //
   if ( lControl & zSAVE_CURSORS )
   {
      LPVIEWENTITYCSR  lpViewEntityCsr;
      LPENTITYINSTANCE lpCurrentEI;
      zLONG            lInstanceCount;

      lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
      lInstanceCount = 1;

      for ( lpViewEntityCsr = zGETPTR( lpViewCsr->hFirstOD_EntityCsr );
            lpViewEntityCsr;
            lpViewEntityCsr = zGETPTR( lpViewEntityCsr->hNextHier ) )
      {
         // If the entity cursor is NULL then ignore this cursor.
         if ( lpViewEntityCsr->hEntityInstance == 0 )
            continue;

         if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR )
         {
            sprintf_s( szWorkString, zsizeof( szWorkString ), "c%x 0", lpViewEntityCsr->nHierNbr );

            if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
               goto EndOfFunction;

            continue;
         }

         lpCurrentEI = zGETPTR( lpViewEntityCsr->hEntityInstance );

         if ( lpCurrentEI->u.nInd.bWritten == FALSE )
         {
            LPENTITYINSTANCE lpSrchInstance;
            zBOOL            bNoTwins = TRUE;

            // The current entity instance wasn't written to the stream.  If
            // none of its twins were written to the stream then the cursor
            // is considered NULL.

            // Search previous twins.
            for ( lpSrchInstance = zGETPTR( lpCurrentEI->hPrevTwin );
                  lpSrchInstance;
                  lpSrchInstance = zGETPTR( lpSrchInstance->hPrevTwin ) )
            {
               if ( lpSrchInstance->u.nInd.bWritten )
               {
                  bNoTwins = FALSE;
                  break;
               }
            }

            // Search next twins.
            if ( bNoTwins )
            {
               for ( lpSrchInstance = zGETPTR( lpCurrentEI->hNextTwin );
                     lpSrchInstance;
                     lpSrchInstance = zGETPTR( lpSrchInstance->hNextTwin ) )
               {
                  if ( lpSrchInstance->u.nInd.bWritten )
                  {
                     bNoTwins = FALSE;
                     break;
                  }
               }
            }

            // If we didn't find any twins then the cursor is considered
            // NULL so don't write the cursor record to the stream.
            if ( bNoTwins )
               continue;

            // Cursor points to invalid entity but the entity does have
            // valid twins, so send record indicating that the cursor is
            // currently not set.
            sprintf_s( szWorkString, zsizeof( szWorkString ), "c%x 0", lpViewEntityCsr->nHierNbr );
         }
         else
         {
            for ( ;
                  lpEntityInstance != lpCurrentEI;
                  lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
            {
               // If the entity instance wasn't written to the stream, then
               // don't bother counting it.
               if ( lpEntityInstance->u.nInd.bWritten == FALSE )
                  continue;

               lInstanceCount++;
            }

            sprintf_s( szWorkString, zsizeof( szWorkString ), "c%x %lx", lpViewEntityCsr->nHierNbr,
                      lInstanceCount );
         }

         if ( (*lpfnStreamFunc)( lpView, lpvData, szWorkString, 0, zTYPE_STRING ) )
            goto EndOfFunction;
      }
   }

   // If we get here then everything's OK.
   nRC = 0;

EndOfFunction:

   if ( pchBuffer )
      fnFreeDataspace( pchBuffer );

   return( nRC );

} // fnWriteOI_ToTextStream

// The FileHeader struct is loaded with data ... make a string by spacing out the values.
zLONG
fnFillHeaderFieldMember( zPCHAR pchFileHeader, zLONG lMaxLth, zLONG lLth, zPCHAR pchField, zLONG lFieldLth, zLONG lFillLth, zBOOL bForceSpace )
{
   zLONG k = 0;

   while ( k < lFieldLth )
   {
      if ( pchField[ k ] == 0 )
      {
         while ( k++ < lFillLth )
         {
            pchFileHeader[ lLth++ ] = ' ';
         }
         break;
      }
      else
      {
         pchFileHeader[ lLth++ ] = pchField[ k++ ];
      }
   }

   if ( bForceSpace &&  lLth > 0 && pchFileHeader[ lLth - 1 ] != ' ' )
      pchFileHeader[ lLth++ ] = ' ';

   pchFileHeader[ lLth ] = 0;
   return( lLth );
}

void
fnFillHeaderLine( zPCHAR pchFileHeader, zLONG lMaxLth, FileHeaderRecord FileHeader )
{
   zLONG lLth = 0;
   pchFileHeader[ 0 ] = 0;
   lLth = fnFillHeaderFieldMember( pchFileHeader, lMaxLth, lLth, FileHeader.chTypeIndicator, zsizeof( FileHeader.chTypeIndicator ), zsizeof( FileHeader.chTypeIndicator ), FALSE );
   lLth = fnFillHeaderFieldMember( pchFileHeader, lMaxLth, lLth, FileHeader.szZeidon, zsizeof( FileHeader.szZeidon ), zsizeof( FileHeader.szZeidon ), TRUE );
   lLth = fnFillHeaderFieldMember( pchFileHeader, lMaxLth, lLth, FileHeader.szFileName, zsizeof( FileHeader.szFileName ), 9, TRUE );
   lLth = fnFillHeaderFieldMember( pchFileHeader, lMaxLth, lLth, FileHeader.szObjectType, zsizeof( FileHeader.szObjectType ), zsizeof( FileHeader.szObjectType ), TRUE );
   lLth = fnFillHeaderFieldMember( pchFileHeader, lMaxLth, lLth, FileHeader.szDate, zsizeof( FileHeader.szDate ), zsizeof( FileHeader.szDate ), TRUE );
   lLth = fnFillHeaderFieldMember( pchFileHeader, lMaxLth, lLth, FileHeader.szTime, zsizeof( FileHeader.szTime ), zsizeof( FileHeader.szTime ), TRUE );
   lLth = fnFillHeaderFieldMember( pchFileHeader, lMaxLth, lLth, FileHeader.szRelease, zsizeof( FileHeader.szRelease ), 0, FALSE );
}
//=SfWriteOI_ToStream
zSHORT OPERATION
SfWriteOI_ToStream( zVIEW          lpView,
                    zCPCHAR        cpcHeaderName,
                    zLONG          lControl,
                    LPFN_PUTSTREAM lpfnStreamFunc,
                    zPVOID         lpvData )
{
   LPTASK               lpCurrentTask;
   LPVIEWOD             lpViewOD;
   LPVIEWOI             lpViewOI;
   LPVIEWCSR            lpViewCsr;
   FileHeaderRecord     FileHeader;
   zPCHAR               pchLine;
   zPCHAR               pchFileNmp;
   zCHAR                szFileHeader[ sizeof( FileHeaderRecord ) ];
   zCHAR                szDateTime[ 20 ];
   zCHAR                szTemp[ 50 ];
   zLONG                lTickCount;
   zBOOL                bOptimistic;
   zBOOL                bIncremental;
// zSHORT               k;
   zSHORT               nRC;

   if ( AnchorBlock->TraceFlags.bOI_Times )
      lTickCount = SysGetTickCount( );

   // If task not active or disabled, return zCALL_ERROR.
   lpCurrentTask = zGETPTR( lpView->hTask );

   // Validate that the view passed is valid
   if ( fnValidViewCsr( lpCurrentTask, lpView ) == 0 )
      return( zCALL_ERROR );

   lpViewOD  = zGETPTR( lpView->hViewOD );
   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

   // Make sure OI does not contain versioned instances
   if ( lpViewOI->nVersionedInstances )
#if 0  // DGC 1999.06.04  No longer an error?  It seems like we should be able
       // to pass OIs even if they have versions.  We will, however, only
       // perform Reclaim if there are no versions (we wouldn't want to get
       // rid of something we want).
   {
      //  "KZOEE076 - Object instance contains versioned entity instances"
      fnIssueCoreError( lpCurrentTask, lpView, 8, 76, 0, 0, 0 );
      return( zCALL_ERROR );
   }

   // Get rid of all deadwood instances (e.g. entities that have been created AND deleted).
   fnReclaimHiddenInstances( lpViewOI );

#else
      ;
   else
      // Get rid of all deadwood instances (e.g. entities that have been created AND deleted).
      fnReclaimHiddenInstances( lpViewOI );
#endif

   // build header record
   zmemset( &FileHeader.chTypeIndicator, ' ', sizeof( FileHeaderRecord ) );

   // Set bIncremental and bBinary
   if ( lControl & zINCREMENTAL )
      bIncremental = TRUE;
   else
      bIncremental = FALSE;

   // If the view has an "original OI" then the view was activated with
   // optimistic locking and we need to send the original OI as well.
   if ( lpViewOI->vOriginalOI )
      bOptimistic = TRUE;
   else
      bOptimistic = FALSE;

   // We store information now as bit-flags.
   FileHeader.chTypeIndicator[ 0 ] = szlNewPortableHeader[ 0 ];

   // DGC 1999.05.07
   // Used to be binary indicator.  Now it determines if the ER date is store
   // with with a compressed OI.  This flag can be re-used for something else
   // when all customers are using post-9j core.
   FileHeader.chTypeIndicator[ 1 ] = '1'; // This release always store date.

   if ( bIncremental )
      FileHeader.chTypeIndicator[ 2 ] = '1';
   else
      FileHeader.chTypeIndicator[ 2 ] = '0';

   if ( lControl & zCOMPRESSED )
      FileHeader.chTypeIndicator[ 3 ] = '1';
   else
      FileHeader.chTypeIndicator[ 3 ] = '0';

   if ( bOptimistic )
      FileHeader.chTypeIndicator[ 4 ] = '1';
   else
      FileHeader.chTypeIndicator[ 4 ] = '0';

#ifdef USE_ATTRIBFLAGS
   // Using attribute flags logic.
   if ( bIncremental )
      FileHeader.chTypeIndicator[ 5 ] = '1';
   else
      FileHeader.chTypeIndicator[ 5 ] = '0';
#else
   // Reserved for later use...
   FileHeader.chTypeIndicator[ 5 ] = '-';
#endif

   strcpy_s( FileHeader.szZeidon, zsizeof( FileHeader.szZeidon ), szlmZeidon );

   pchFileNmp = (zPCHAR) cpcHeaderName;
   pchLine    = (zPCHAR) cpcHeaderName;
   while ( (pchLine = zstrchr( pchLine, cDirSep )) != 0 )
   {
      pchLine++;
      pchFileNmp = pchLine;
   }

   // we are building the header record for this file and realize that the
   // file name we are copying to FileHeader.szFileName may be longer than
   // sizeof( FileHeader.szFileName ). This is OK since the FileHeader
   // structure is large enough to accomodate an overwrite.
   strcpy_s( FileHeader.szFileName, zsizeof( FileHeader.szFileName ), pchFileNmp ); // no longer permitting overwrite ... dks 2015.11.12
   pchLine = zstrchr( FileHeader.szFileName, '.' );
   if ( pchLine )
   {
      strcpy_s( pchLine, zsizeof( FileHeader.szFileName ) - (pchLine - FileHeader.szFileName), "       " );
      pchLine[ 0 ] = 0;
   }

   SysTranslateString( FileHeader.szFileName, 'U' );
   strcpy_s( FileHeader.szObjectType, zsizeof( FileHeader.szObjectType ), lpViewOD->szName );
   SysGetDateTime( szDateTime, zsizeof( szDateTime ) );
   fnDateTimeFormat( szDateTime, FileHeader.szDate, zsizeof( FileHeader.szDate ), FileHeader.szTime, zsizeof( FileHeader.szTime ) );

   // Even if this is not a MetaOI, we should force the release level for
   // all files to be at the minimal level of the software.
   if ( MiCompareOI_ToRelease( lpView, szlReleaseCompatible ) < 0 )
   {
      MiSetOI_ReleaseForView( lpView, szlReleaseCompatible );
   }

   // if we are using new features, force to current Release
   if ( (lControl & zENCODE_BLOBS) || (lControl & zNO_NULL_STRING_TERM) )
   {
      MiSetOI_ReleaseForView( lpView, szlReleaseCurrent );
   }

   strcpy_s( FileHeader.szRelease, zsizeof( FileHeader.szRelease ), lpViewOI->szRelease ); // dks 3/5/96

   /* this is what used to be done to get: "z1000-Zeidon    ACCOUNT  TZZOXODO 07/04/15   10:58:29 1.0a2"

   pchLine = FileHeader.chTypeIndicator;
   for ( k = 0; k < sizeof( FileHeaderRecord ); k++ )
   {
      if ( pchLine[ k ] == 0 )
         pchLine[ k ] = ' ';
   }

   FileHeader.nEntityInstanceRecordSize = 0;
   */

   fnFillHeaderLine( szFileHeader, zsizeof( szFileHeader ), FileHeader );

   if ( (*lpfnStreamFunc)( lpView, lpvData, szFileHeader, 0, zTYPE_STRING ) == zCALL_ERROR )
   {
      return( zCALL_ERROR );
   }

   // Write the ER date from the OD if we have incrementals.
   if ( bIncremental &&
        (*lpfnStreamFunc)( lpView, lpvData, lpViewOD->szER_Date, 0, zTYPE_STRING ) == zCALL_ERROR )
   {
      return( zCALL_ERROR );
   }

   // Write the flags used to activate the OI.
   if ( lpViewOI->lActivateControl )
   {
      sprintf_s( szTemp, zsizeof( szTemp ), "mCONTROL %lx", lpViewOI->lActivateControl );
      if ( (*lpfnStreamFunc)( lpView, lpvData, szTemp, 0, zTYPE_STRING ) == zCALL_ERROR )
      {
         return( zCALL_ERROR );
      }
   }

   nRC = fnWriteOI_ToTextStream( lpView, lpfnStreamFunc, lpvData,  bIncremental, lControl );

   // Write the original OI for optimistic locking.
   if ( nRC == 0 && bOptimistic )
   {
      if ( (*lpfnStreamFunc)( lpView, lpvData, "ZEND", 0, zTYPE_STRING ) == zCALL_ERROR )
      {
         return( zCALL_ERROR );
      }

      // Write the OI to the text stream but don't save the cursors.
      nRC = fnWriteOI_ToTextStream( zGETPTR( lpViewOI->vOriginalOI ),
                                    lpfnStreamFunc,
                                    lpvData, bIncremental,
                                    ( lControl & ~zSAVE_CURSORS ) );
   }

   // Write the qualification OI for optimistic locking.
   if ( nRC == 0 && bOptimistic )
   {
      if ( (*lpfnStreamFunc)( lpView, lpvData, "ZEND",
                              0, zTYPE_STRING ) == zCALL_ERROR )
      {
         return( zCALL_ERROR );
      }

      // Write the OI to the text stream but don't save the cursors.
      if ( lpViewOI->vQualOI )
         nRC = fnWriteOI_ToTextStream( zGETPTR( lpViewOI->vQualOI ),
                                       lpfnStreamFunc,
                                       lpvData, bIncremental,
                                       ( lControl & ~zSAVE_CURSORS ) );
   }

   if ( nRC == 0 )
      lpViewOI->bUpdatedFile = 0;

   if ( AnchorBlock->TraceFlags.bOI_Times )
   {
      zCHAR sz[ 100 ];

      sprintf_s( sz, zsizeof( sz ), "(%s) = %lf seconds", lpViewOD->szName,
                 (double) ( SysGetTickCount( ) - lTickCount ) / zTICKS_PER_SECOND );
      TraceLineS( "(oi) Total time for SfWriteOI_ToStream ", sz );
   }

   return( nRC );

} // SfWriteOI_ToStream

//./ ADD NAME=CommitOI_ToFile
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      CommitOI_ToFile
//
//  PURPOSE:    To commit an Object instance from memory to a file
//
//  PARAMETERS: lpView      - View containing object instance to write out.
//              cpcFileName - The fully-qualified file name to write
//                            to (including the drive, path, and
//                            file extension).
//              lControl    - Controls certain aspects of committing the
//                            file, values: zASCII, zINCREMENTAL,
//                            zCOMPRESSED, zSAVE_CURSORS.
//
//  RETURNS:    0            - Instance committed successfully
//              zCALL_ERROR  - Error committing object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
CommitOI_ToFile( zVIEW lpView, zCPCHAR cpcFileName, zLONG lControl )
{
   LPTASK         lpCurrentTask;
   FileDataRecord FileData;
   zCHAR          szOpenFileName[ 2 * zMAX_FILESPEC_LTH + 1 ];
   zCHAR          szWork[ 2 * zMAX_FILESPEC_LTH + 1 ];
   zLONG          hFile;
   zSHORT         nTrys;
   zSHORT         nRC;

   // If task not active or disabled, or view invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iCommitOI_ToFile, lpView,
                                          zVALID_VIEW )) == 0 )
   {
      return( zCALL_ERROR );
   }

// DGC 9/23/96
// I changed the logic: if the file name is not qualfied, use the object dir
// for the application. I repeated this change in CommitOI_ToFile.
   if ( zstrchr( cpcFileName, cDirSep ) == 0 )
   {
      LPAPP lpApp;

      fnGetApplicationForSubtask( &lpApp, lpView );
      if ( lpApp )
         strcpy_s( szWork, zsizeof( szWork ), lpApp->szObjectDir );
      else
      {
         lpApp = zGETPTR( AnchorBlock->hSystemApp );
         strcpy_s( szWork, zsizeof( szWork ), lpApp->szObjectDir );
      }

      SysAppendcDirSep( szWork );
   }
   else
      szWork[ 0 ] = 0;

   strcat_s( szWork, zsizeof( szWork ), cpcFileName );
   SysConvertEnvironmentString( szOpenFileName, zsizeof( szOpenFileName ), szWork );

   // Open the file for the object instance data ... this file really should
   // exist, but it may already be open.  So we will try more than once to
   // open it before giving up.
   hFile = -1;
   nTrys = 0;
   while ( hFile == -1 && nTrys++ < 10 )
   {
      hFile = SysOpenFile( lpView, szOpenFileName,
                COREFILE_CREATE | COREFILE_WRITELINE_BUFFERED | COREFILE_BACKUP );
      if ( hFile == -1 )
         SysWait( 500 );
   }

   if ( hFile == -1 )
   {
      //  "KZOEE071 - Error opening instance file "
      fnIssueCoreError( lpCurrentTask, lpView, 16, 71, 0, cpcFileName, 0 );
      fnOperationReturn( iCommitOI_ToFile, lpCurrentTask );
      return( zCALL_ERROR );
   }

   FileData.pchFileName = (zPCHAR) cpcFileName;
   FileData.hFile       = hFile;
   FileData.lLine       = 0;

   nRC = SfWriteOI_ToStream( lpView, cpcFileName, lControl,
                             fnPutDataToFile, (zPVOID) &FileData );

   if ( nRC == zCALL_ERROR )
      SysCloseFileWithControl( lpView, hFile, 0, CLOSEFILE_ABORT_BACKUP );
   else
      nRC = SysCloseFileWithControl( lpView, hFile, 0, 0 );

   fnOperationReturn( iCommitOI_ToFile, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=DropObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      DropObjectInstance
//
//  PURPOSE:    To drop an Object instance from memory
//
//  PARAMETERS: lpView - View to object instance to drop.
//
//  RETURNS:    0           - Instance dropped successfully
//              zCALL_ERROR - Error Dropping object instance
//
//
//  NOTE:  ALL Views to the object instance will become invalid
//         when this instance is dropped.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
DropObjectInstance( zVIEW  lpView )
{
   LPTASK            lpCurrentTask;
   zSHORT            nRC;

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iDropObjectInstance, lpView,
                                          zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   // Call fnDropObjectInstance with current view
   nRC = fnDropObjectInstance( lpView );

   fnOperationReturn( iDropObjectInstance, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=ObjectInstanceUpdated
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ObjectInstanceUpdated
//
//  PURPOSE:    To determine if an Object instance has been updated
//
//  PARAMETERS: lpView - View of object instance to check.
//
//  RETURNS:    0           - Instance has not been updated
//              1           - Instance has been updated
//              zCALL_ERROR - Error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
ObjectInstanceUpdated( zVIEW  lpView )
{
   LPTASK            lpCurrentTask;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;
   zSHORT            nRC;

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iObjectInstanceUpdated, lpView,
                                          zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   nRC = lpViewOI->bUpdated;

   fnOperationReturn( iObjectInstanceUpdated, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=ObjectInstanceUpdatedFromFile
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      ObjectInstanceUpdatedFile
//
//  PURPOSE:    To determine if an Object instance has been updated since
//              it was last activated/committed from/to a portable file.
//
//  PARAMETERS: lpView - View of object instance to check.
//
//  RETURNS:    0           - Instance has not been updated
//              1           - Instance has been updated
//              zCALL_ERROR - Error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
ObjectInstanceUpdatedFromFile( zVIEW  lpView )
{
   LPTASK            lpCurrentTask;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;
   zSHORT            nRC;

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iObjectInstanceUpdatedFromFile,
                                          lpView, zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   nRC       = lpViewOI->bUpdatedFile;

   fnOperationReturn( iObjectInstanceUpdatedFromFile, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=fnDropViewCsr
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   fnDropViewCsr
//
//  PURPOSE:    To drop a view cursor object and remove it from the
//              ViewOI chain. This function WILL NOT delete the View
//              Object pointed to by the view Csr object because the
//              view may be reassigned to another view csr. If the
//              ViewOI has no more View cursors after the View cursor
//              is dropped, then the ViewOI is dropped.
//
//  RETURNS:    0 - View cursor successfully dropped
//             -1 - error dropping view
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT
fnDropViewCsr( LPVIEWCSR lpViewCsr )
{
   LPVIEWOI           lpViewOI;
   LPVIEWCSR          hViewCsr = (LPVIEWCSR) zGETHNDL( lpViewCsr );
   LPVIEWSUBOBJECT    lpViewSubobject;
   LPSELECTEDINSTANCE lpSelectedInstance;
   zVIEW              lpView;
   zBOOL              bMutexLocked;
   zSHORT             nRC;

   if ( lpViewCsr == 0 )
      return( 0 );

   lpViewOI = zGETPTR( lpViewCsr->hViewOI );

#ifdef __ACTIVATE_CONSTRAINTS__
   // Check to see if we are dropping the last ViewCsr for the OI.  If we are
   // then we need to call the DropOI constraint.
   if ( lpViewOI->hFirstViewCsr == hViewCsr && lpViewCsr->hNextViewCsr == 0 )
   {
      LPVIEWOD lpViewOD;

      // We are dropping the last view csr which means we are dropping the
      // OI as well.
      lpView   = zGETPTR( lpViewCsr->hView );

      // If the OI has pessimistic locking then commit the OI to drop the
      // locks.
      if ( lpViewOI->bIsLocked )
      {
         ViewClusterRecord ViewCluster;

         ViewCluster.vOI      = lpView;
         ViewCluster.lControl = zCOMMIT_DROPLOCKSONLY;

         // We need to commit the object to release the pessimistic lock.
         nRC = CommitMultipleOIs( &ViewCluster, 1, 0, zCOMMIT_DROPLOCKSONLY );
      }

      // If object has drop oi constraint active, check for objections.
      lpViewOD = zGETPTR( lpView->hViewOD );
      if ( lpViewOD->bDropOIConstraint )
      {
         zSHORT nState = 0;
         LPTASK lpCurrentTask = zGETPTR( lpView->hTask );

         if ( lpCurrentTask->bShutdown )
            nState += zOCE_STATE_SHUTDOWN;

         fnInvokeOCEOperation( zGETPTR( lpViewCsr->hView ),
                               lpCurrentTask, zOCE_DROPOI, nState );
         lpViewOI->bDropConstraintInvoked = TRUE;
      }
   }
#endif

   if ( lpViewOI->hTask == AnchorBlock->hMainTask )  // added dks
   {
      bMutexLocked = TRUE;
      zLOCK_MUTEX( zMUTEX_ANCHORBLOCK );
   }
   else
      bMutexLocked = FALSE;

   // Unchain ViewCsr from View OI.
   if ( lpViewOI->hFirstViewCsr == hViewCsr )
      lpViewOI->hFirstViewCsr = lpViewCsr->hNextViewCsr;
   else
   {
      LPVIEWCSR lpWorkViewCsr;

      lpWorkViewCsr = zGETPTR( lpViewOI->hFirstViewCsr ); // blew on this line 2006.07.03 dks
      while ( lpWorkViewCsr->hNextViewCsr != hViewCsr )
         lpWorkViewCsr = zGETPTR( lpWorkViewCsr->hNextViewCsr );

      lpWorkViewCsr->hNextViewCsr = lpViewCsr->hNextViewCsr;
   }

   while ( lpViewCsr->hFirstViewSubobject )
   {
      lpViewSubobject = zGETPTR( lpViewCsr->hFirstViewSubobject );
      lpViewCsr->hFirstViewSubobject = lpViewSubobject->hNextViewSubobject;
      fnFreeDataspace( lpViewSubobject );
   }

   while ( lpViewCsr->hFirstSelectedInstance )
   {
      lpSelectedInstance = zGETPTR( lpViewCsr->hFirstSelectedInstance );
      lpViewCsr->hFirstSelectedInstance =
                              lpSelectedInstance->hNextSelectedInstance;
      fnFreeDataspace( lpSelectedInstance );
   }

   // If the view which used to point to us *still* points to us, then
   // zero out the pointer since we are going away.
   lpView = zGETPTR( lpViewCsr->hView );
   if ( lpView && lpView->hViewCsr == hViewCsr )
      lpView->hViewCsr = 0;

   fnFreeDataspace( lpViewCsr );  // should this line be moved to after the following if block?? dks 2006.07.19

   // If the ViewOI has no more cursors, drop it!
   if ( lpViewOI->hFirstViewCsr == 0 )
      fnDropViewOI( lpViewOI );  // dks 2006.09.18 error while cleaning up client OE

   if ( bMutexLocked )
      zUNLOCK_MUTEX( zMUTEX_ANCHORBLOCK );

   return( 0 );
}

//./ ADD NAME=fnDropObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   fnDropObjectInstance
//
//  PURPOSE:    To drop an Object instance from memory
//
//  PARAMETERS: lpView - View to object instance to drop.
//
//  RETURNS:    0 - Instance dropped successfully
//             -1 - Error Dropping object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT
fnDropObjectInstance( zVIEW  lpView )
{
   LPVIEWOI          lpViewOI;
   LPVIEWCSR         lpViewCsr;
   LPVIEWCSR         lpFirstViewCsr;
   zVIEW             lpCurrentView;
   zVIEW             lpLastView;

   // If no ViewCsr, go home ...
   if ( lpView->hViewCsr == 0 )
      return( 0 );

   // Get pointers to ViewOI and task owning the ViewOI.
   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

// {
//    LPVIEWOD lpViewOD = zGETPTR( lpView->hViewOD );
//    TraceLine( "DropObjectInstance: 0x%08x   LOD: %s",
//               lpView, lpViewOD->szName );
//    if ( zstrcmp( "KZMSGQOO", lpViewOD->szName ) == 0 )
//       SysMessageBox( lpView, "Dropping LOD", lpViewOD->szName, 0 );
// }

   // Find the last view cursor for the ViewOI.
   while ( lpViewCsr->hNextViewCsr )
      lpViewCsr = zGETPTR( lpViewCsr->hNextViewCsr );

   // Drop all the views.  When the last view is dropped, fnDropView will
   // drop the object instance.  The DropObjectInstance constraint will
   // be called then.
   lpLastView = zGETPTR( lpViewCsr->hView );
   lpCurrentView = 0;
   do
   {
      lpFirstViewCsr = zGETPTR( lpViewOI->hFirstViewCsr );
      lpCurrentView = zGETPTR( lpFirstViewCsr->hView );
      fnDropView( lpCurrentView );

   }  while ( lpCurrentView != lpLastView );

   return( 0 );
}

void LOCALOPER
fnClearLinks( LPENTITYINSTANCE lpEntityInstance )
{
   LPENTITYINSTANCE lpNextLinked;
   LPENTITYINSTANCE lpSearchLink;
   LPENTITYINSTANCE hEntityInstance = zGETHNDL( lpEntityInstance );

   lpNextLinked = zGETPTR( lpEntityInstance->hNextLinked );

   if ( lpNextLinked->hNextLinked == hEntityInstance )
      lpNextLinked->hNextLinked = 0;
   else
   {
      lpSearchLink = lpNextLinked;
      while ( lpSearchLink->hNextLinked != hEntityInstance )
         lpSearchLink = zGETPTR( lpSearchLink->hNextLinked );

      lpSearchLink->hNextLinked = lpEntityInstance->hNextLinked;
   }
}

//./ ADD NAME=fnDropViewOI
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    fnDropViewOI
//
//  PURPOSE:     To drop a ViewOI Object and all instance data
//
//  PARAMETERS:  lpViewOI - View of the object instance to drop.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void
fnDropViewOI( LPVIEWOI lpViewOI )
{
   LPENTITYINSTANCE  lpEntityInstance;
   LPENTITYINSTANCE  lpNextEntityInstance;
   LPENTITYINSTANCE  lpLastEntityInstance;
   LPENTITYINSTANCE  lpSearchLink;
   LPENTITYINSTANCE  lpSearchVsn;
   LPTASK            lpOwningTask;
   zBOOL             bPrevVersion;

   lpOwningTask = zGETPTR( lpViewOI->hTask );

   // If the ViewOI is in a task being shutdown and does not have any
   // instances shared with the system task, skip freeing up the instance
   // data, it will go away on completion of task cleanup.
   // If the task is running as a server task then we won't free memory
   // because it will be shut down shortly.
   // Things are unfortunately not working as suggested in the comment above.
   // So always do a drop, even when the task is a server task and is being
   // shutdown (US).
   // Check to see if we have any locking OI's.  If we do, drop them.
   if ( lpViewOI->vOriginalOI )
   {
      zVIEW vOriginalOI = zGETPTR( lpViewOI->vOriginalOI );

      // DGC 05/05/97
      // Following check shouldn't be needed once I fix a bug.
      if ( vOriginalOI->nTableID != iView )
      {
         fnSysMessageBox( zGETPTR( lpViewOI->hTask ), szlOE_SystemError,
                          "Trying to drop original OI but it's not there!", 1 );
      }
      else
         fnDropView( vOriginalOI );
   }

   if ( lpViewOI->vQualOI )
      fnDropView( zGETPTR( lpViewOI->vQualOI ) );

   // If there are any outstanding versioned instances, find the
   // last entity instance in the object instance and work backward
   // from there to clean up outstanding versioned chains until all
   // versions are gone. First, find the last instance in the chain.
   if ( lpViewOI->nVersionedInstances )
   {
      lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
      while ( lpEntityInstance->hNextHier )
      {
         if ( lpEntityInstance->hNextTwin )
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin );
         else
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier );
      }

      lpLastEntityInstance = lpEntityInstance;
   }

   // Delete the instance data associated with the ViewOI.
// AnchorBlock->nStatus = 101; // DGC debugging hack.
   if ( lpViewOI->hRootEntityInstance )
   for ( ; ; )
   {
      lpEntityInstance = 0;

      // If there are versioned instances out there, let's clean them
      // up!!!  Go to the end of the chain and find one.
      if ( lpViewOI->nVersionedInstances )
      {
         LPENTITYINSTANCE lpPrevVsn;

         lpEntityInstance = lpLastEntityInstance;
         lpPrevVsn = zGETPTR( lpEntityInstance->hPrevVsn );

         // Search for an entity instance which has an outstanding
         // previous version.
         while ( lpEntityInstance &&
                 (lpPrevVsn == 0 || lpPrevVsn->u.nInd.bPrevVsnRoot == FALSE) )
         {
            // Since temporal entitys have no previous version, simply
            // unmark them and subtract 1 from the version count.
            if ( lpEntityInstance->u.nInd.bTemporal )
            {
               lpEntityInstance->u.nInd.bTemporal = 0;
               lpViewOI->nVersionedInstances--;
               if ( lpViewOI->nVersionedInstances == 0 )
               {
                  lpEntityInstance = 0;
                  break;
               }
            }

            lpEntityInstance = zGETPTR( lpEntityInstance->hPrevHier );
            if ( lpEntityInstance )
               lpPrevVsn = zGETPTR( lpEntityInstance->hPrevVsn );
         }

         if ( lpEntityInstance )
            lpEntityInstance = zGETPTR( lpEntityInstance->hPrevVsn );
         else
            lpViewOI->nVersionedInstances = 0;
      }

      // If no entity instance found which is a previous version, go
      // for the main entity instance chain!!
      if ( lpEntityInstance == 0 )
      {
         lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
         lpViewOI->hRootEntityInstance = 0;
      }

      // Clean up the entity instances.
      while ( lpEntityInstance )
      {
         LPVIEWENTITY lpViewEntity;

         lpNextEntityInstance = zGETPTR( lpEntityInstance->hNextHier );
         lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

         // If there are versioned instances in this instance, zero
         // all records for newer versions linked to this instance
         // whose record matches the link instance record.
         if ( lpEntityInstance->hNextVsn )
         {
            LPENTITYINSTANCE lpNextVsn;

            // If there are linked instances to the old version of an
            // entity instance, see if the prev-version indicator needs
            // to be unset for all the linked instances because the
            // new version is being dropped by fnDropViewOI.
            if ( lpEntityInstance->hNextLinked )
            {
               bPrevVersion = FALSE;
               lpSearchLink = zGETPTR( lpEntityInstance->hNextLinked );
               while ( lpSearchLink && lpSearchLink != lpEntityInstance )
               {
                  if ( lpSearchLink->hNextVsn )
                  {
                     bPrevVersion = TRUE;
                     break;
                  }

                  lpSearchLink = zGETPTR( lpSearchLink->hNextLinked );
               }

               if ( bPrevVersion == 0 )
               {
                  lpSearchLink = zGETPTR( lpEntityInstance->hNextLinked );
                  while ( lpSearchLink &&
                          lpSearchLink != lpEntityInstance )
                  {
                     lpSearchLink->u.nInd.bPrevVersion = FALSE;
                     lpSearchLink = zGETPTR( lpSearchLink->hNextLinked );
                  }
               }
            }

            // If the newer version record matches the older version
            // record (because the entity is NOT UPDATEABLE), clear
            // all the record pointers in the newer versions so we do
            // not attempt to free the same record multiple times.
            lpNextVsn = zGETPTR( lpEntityInstance->hNextVsn );
            if ( lpNextVsn->hPersistRecord == lpEntityInstance->hPersistRecord )
            {
               lpSearchVsn = lpNextVsn;
               while ( lpSearchVsn )
               {
                  lpSearchVsn->hPersistRecord = 0;
                  lpSearchLink = zGETPTR( lpSearchVsn->hNextLinked );
                  while ( lpSearchLink && lpSearchLink != lpSearchVsn )
                  {
                     lpSearchLink->hPersistRecord = 0;
                     lpSearchLink = zGETPTR( lpSearchLink->hNextLinked );
                  }

                  lpSearchVsn = zGETPTR( lpSearchVsn->hNextVsn );
               }
            }
         }

         // Reset version pointers.
         if ( lpEntityInstance->hNextVsn )
         {
            LPENTITYINSTANCE lpNextVsn =
                                 zGETPTR( lpEntityInstance->hNextVsn );

            lpNextVsn->hPrevVsn = lpEntityInstance->hPrevVsn;
         }

         if ( lpEntityInstance->hPrevVsn )
         {
            LPENTITYINSTANCE lpPrevVsn = zGETPTR( lpEntityInstance->hPrevVsn );

            lpPrevVsn->hNextVsn = lpEntityInstance->hNextVsn;
         }

         // If the entity instance is linked, remove the entity instance
         // from the link chain.
         if ( lpEntityInstance->hNextLinked )
         {
            LPENTITYINSTANCE lpNextLinked =
                              zGETPTR( lpEntityInstance->hNextLinked );

            if ( lpNextLinked->hNextLinked == zGETHNDL( lpEntityInstance ) )
               lpNextLinked->hNextLinked = 0;
            else
            {
               lpSearchLink = lpNextLinked;
               while ( lpSearchLink->hNextLinked !=
                                             zGETHNDL( lpEntityInstance ) )
                  lpSearchLink = zGETPTR( lpSearchLink->hNextLinked );

               lpSearchLink->hNextLinked = lpEntityInstance->hNextLinked;
            }
         }
         else
            fnDeleteAttributeRecord( lpViewEntity, lpEntityInstance, TRUE );  // dks 2006.09.18 error while cleaning up client OE

         fnDeleteAttributeRecord( lpViewEntity, lpEntityInstance, FALSE );
         fnRemoveEntityFromDebugChange( lpEntityInstance );
         fnFreeDataspace( lpEntityInstance );
         lpEntityInstance = lpNextEntityInstance;
      }

      // Get out when no root instance exists any more.
      if ( lpViewOI->hRootEntityInstance == 0 )
         break;
   }

// AnchorBlock->nStatus = AnchorInitialized;

   // Free the ViewOI.
   if ( lpOwningTask->hFirstViewOI == zGETHNDL( lpViewOI ) )
      lpOwningTask->hFirstViewOI = lpViewOI->hNextViewOI;
   else
   {
      LPVIEWOI lpSearchViewOI;

      lpSearchViewOI = zGETPTR( lpOwningTask->hFirstViewOI );
      if ( lpSearchViewOI )
      {
         while ( lpSearchViewOI->hNextViewOI != zGETHNDL( lpViewOI ) )
            lpSearchViewOI = zGETPTR( lpSearchViewOI->hNextViewOI );

         lpSearchViewOI->hNextViewOI = lpViewOI->hNextViewOI;
      }
   }

   fnFreeDataspace( lpViewOI );
}

//./ ADD NAME=fnActivateEmptyObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   fnActivateEmptyObjectInstance
//
//  PURPOSE:    To activate an empty Object instance and return a
//              view to the object instance.
//
//  PARAMETERS: lpTask  - View identifying subtask under which the instance
//                        is to be activated. NOTE: The subtask also
//                        identifies the application which owns the
//                        View Object type being activated.
//              lpView  - The View Object Definition (type) to be
//                        activated.
//              lControl - Controls certain aspects of the file loaded.
//                         zSINGLE  - (default) only one entity at the
//                                    root level.
//                         zMULTIPLE - multiple entities at the root level
//
//  RETURNS:    0 - Instance activated successfully
//    zCALL_ERROR - Error Activating object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT
fnActivateEmptyObjectInstance( LPTASK    lpCurrentTask,
                               zVIEW     lpView,
                               zLONG     lControl )
{
   LPTASK            hInstanceOwningTask;
   LPTASK            lpInstanceOwningTask;
   LPVIEWOD          lpViewOD;
   LPVIEWOI          lpViewOI;
   LPVIEWCSR         lpViewCsr;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   zCHAR             szDateTime[ 20 ];
   zPVOID            hViewOI;
   zPVOID            hViewCsr;
   zUSHORT           uEntities;
   zSHORT            nHierNbr;

   lpViewOD = zGETPTR( lpView->hViewOD );

   // Determine the task which owns the instance, NOTE, this task
   // should be returned by fnValidView in the future since fnValidView
   // has already done the same search! Gig...9/1/92
   if ( lpView->bApplicationView )
      hInstanceOwningTask = AnchorBlock->hMainTask;
   else
      hInstanceOwningTask = lpView->hTask;

   lpInstanceOwningTask = zGETPTR( hInstanceOwningTask );

   // Create a ViewOI Record
   // NOTE: We create view oi records in the main dataspace so all
   // tasks can go through the ViewOI's on clean-up to determine if
   // an application is in use
   hViewOI = fnAllocDataspace( AnchorBlock->hMainFirstDataHeader,
                               sizeof( ViewOI_Record ), 1, 0, iViewOI );
   lpViewOI = zGETPTR( hViewOI );
   if ( lpViewOI == 0 )
   {
   // fnOperationReturn( iActivateEmptyObjectInstance, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // Get the count of entities.
   uEntities = lpViewOD->uEntities;

   // Allocate space for View
   // Create a ViewOI Record
   hViewCsr = fnAllocDataspace( AnchorBlock->hMainFirstDataHeader,
                                sizeof( ViewCsrRecord ) + (zULONG)
                                  (uEntities * sizeof( ViewEntityCsrRecord )),
                                1, 0, iViewCsr );
   lpViewCsr = zGETPTR( hViewCsr );
   if ( lpViewCsr == 0 )
   {
      fnFreeDataspace( lpViewOI );
   // fnOperationReturn( iActivateEmptyObjectInstance, lpCurrentTask );
      return( zCALL_ERROR );
   }

   // Set up View OI record
   lpViewOI->hViewOD            = zGETHNDL( lpViewOD );
   lpViewOI->hFirstViewCsr      = hViewCsr;
   lpViewOI->hTask              = hInstanceOwningTask;
   lpViewOI->hAllocTask         = hInstanceOwningTask;

   // Put date time stamp into View OI record.
   SysGetDateTime( szDateTime, zsizeof( szDateTime ) );
   UfStringToDateTime( szDateTime, (LPDATETIME) &(lpViewOI->DateTime) );
   strcpy_s( lpViewOI->szRelease, zsizeof( lpViewOI->szRelease ), szlReleaseCompatible ); // initialize release for compatiblity

   // Mark View OI as read only if requested, and the View also ...
   if ( lControl & zREADONLY )
   {
      lpViewOI->bReadOnly = TRUE;
   }

   if ( lControl & zMULTIPLE )
      lpViewOI->bMultipleRootLevels = TRUE;
   else
      lpViewOI->bMultipleRootLevels = FALSE;

   // Set up View Cursor Record
   lpViewCsr->hView             = zGETHNDL( lpView );
   lpViewCsr->hViewOI           = hViewOI;
   lpViewCsr->uEntities         = uEntities;
   lpViewCsr->nCurrentSelectSet = 0x0001;

   // Set the View Csr in the View
   lpView->hViewCsr             = hViewCsr;

   // Initialize ViewEntityCsr records
   lpViewEntity    = zGETPTR( lpViewOD->hFirstOD_Entity );
   lpViewEntityCsr = (LPVIEWENTITYCSR) (lpViewCsr + 1);

   // Double assignment ...
   lpViewCsr->hRootViewEntityCsr  =         // continued ...
   lpViewCsr->hFirstOD_EntityCsr =
                  fnCreateEntityCsrHandle( lpViewEntityCsr, lpViewCsr, 0 );
   nHierNbr = 1;
   for ( ; ; )
   {
      lpViewEntityCsr->nTableID    = iViewEntityCsr;
      lpViewEntityCsr->hViewCsr    = hViewCsr;
      lpViewEntityCsr->hNextHier   =
                  fnCreateEntityCsrHandle( lpViewEntityCsr, lpViewCsr, 1 );
      lpViewEntityCsr->hViewEntity = zGETHNDL( lpViewEntity );
      lpViewEntityCsr->nLevel      = lpViewEntity->nLevel;
      lpViewEntityCsr->nHierNbr    = nHierNbr;
      nHierNbr++;

      if ( lpViewEntity->hPrevHier )
      {
         LPVIEWENTITYCSR lpParentViewEntityCsr;

         lpViewEntityCsr->hPrevHier =
                  fnCreateEntityCsrHandle( lpViewEntityCsr, lpViewCsr, -1 );
         lpParentViewEntityCsr = zGETPTR( lpViewEntityCsr->hPrevHier );
         while ( lpParentViewEntityCsr->nLevel >= lpViewEntityCsr->nLevel )
         {
            lpParentViewEntityCsr = zGETPTR( lpParentViewEntityCsr->hPrevHier );
         }

         lpViewEntityCsr->hParent =
               fnCreateEntityCsrHandle( lpParentViewEntityCsr, lpViewCsr, 0 );
      // if ( lpViewEntityCsr->hParent == (LPVIEWENTITYCSR) 1 )
      //    SysMessageBox( 0, "fnActivateEmptyObjectInstance", "1", -1 );
      }

      lpViewEntity = zGETPTR( lpViewEntity->hNextHier );

      if ( lpViewEntity )
         lpViewEntityCsr++;
      else
      {
         lpViewEntityCsr->hNextHier = 0;  // end ViewEntityCsr chain
         break;
      }
   }

   // Chain ViewOI to the application task
   lpViewOI->hNextViewOI = lpInstanceOwningTask->hFirstViewOI;
   lpInstanceOwningTask->hFirstViewOI = hViewOI;

   return( 0 );
}

/*
   An attempt was made to load a child entity but none was found.  The entity
   was flagged as a "hanging" entity.  This means that the relationship with
   it's parent is many-to-one (e.g. the foreign key is in the parent) and it's
   possible that the parent's FK is *not* null.

   This is usually an error but for the current child entity it is ok.  What
   we do here is to check the parent entity instance and see if the value of
   the foreign key is null.  If it not then we create an empty child entity
   instance and set its key value to match the foreign key of the parent.

   Returns: just 0 for now.
*/
zSHORT LOCALOPER
fnAddHangingEntity( zVIEW        lpView,
                    LPVIEWENTITY lpChildEntity )
{
   LPDATARECORD lpChildDataRecord = zGETPTR( lpChildEntity->hFirstDataRecord );
   LPRELRECORD  lpChildRelRecord  = zGETPTR( lpChildDataRecord->hFirstRelRecord );
   LPRELFIELD   lpRelField;
   zBOOL        bEntityCreated = FALSE;

   for ( lpRelField = zGETPTR( lpChildRelRecord->hFirstRelField );
         lpRelField;
         lpRelField = zGETPTR( lpRelField->hNextRelField ) )
   {
      LPVIEWENTITY     lpParentEntity;
      LPVIEWATTRIB     lpTargetAttrib;
      LPVIEWATTRIB     lpSrcAttrib;
      LPDATAFIELD      lpTargetDataField;
      LPDATAFIELD      lpSrcDataField;
      LPVIEWENTITYCSR  lpViewEntityCsr;
      LPENTITYINSTANCE lpEntityInstance;
      zPCHAR           pchPtr;
      zCHAR            chType;
      zULONG           ulLth;

      // Check to see if the Rel field (the target field) is not-null.  Note
      // the the rel field had better be in a parent entity!
      lpTargetDataField = zGETPTR( lpRelField->hRelDataField );
      lpTargetAttrib    = zGETPTR( lpTargetDataField->hViewAttrib );
      lpParentEntity    = zGETPTR( lpTargetAttrib->hViewEntity );

      if ( lpParentEntity == lpChildEntity )
      {
         TraceLineS( "(oi) Hangin key error! ", "- ParentEntity == ChildEntity" );
         continue;
      }

      // Get the entity csr.
      fnValidViewEntity( &lpViewEntityCsr, lpView, lpParentEntity->szName, 0 );

      if ( fnAttributeValueNull( lpView,
                                 zGETPTR( lpViewEntityCsr->hEntityInstance ),
                                 lpTargetAttrib ) )
      {
         continue;
      }

      // If we get here then the target attrib is not null.  This means we
      // need to create an entity instance (if not already created) and
      // copy the attribute value.

      if ( bEntityCreated == FALSE )
      {
         // Get the entity csr.
         fnValidViewEntity( &lpViewEntityCsr, lpView, lpChildEntity->szName, 0 );

         fnCreateEntity( lpView, lpChildEntity, lpViewEntityCsr, zPOS_NEXT, 0 );
         lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
         lpEntityInstance->u.nInd.bHangingEntity = TRUE;

         bEntityCreated = TRUE;
      }

      GetValueFromRecord( lpView, lpParentEntity, lpTargetAttrib, &pchPtr,
                          &chType, &ulLth );

      lpSrcDataField = zGETPTR( lpRelField->hSrcDataField );
      lpSrcAttrib    = zGETPTR( lpSrcDataField->hViewAttrib );

      StoreValueInRecord( lpView, lpChildEntity, lpSrcAttrib, pchPtr, ulLth );
   }

   return( 0 );
}

// An attempt to make it easier to set up a qualification object in core.
zSHORT LOCALOPER
fnCreateQualification( LPTASK           lpCurrentTask,
                       zVIEW            lpView,
                       zPVIEW           pvQual,
                       LPVIEWENTITYCSR  *plpViewEntityCsr,
                       zPCHAR           pchEntitySpec,
                       zPCHAR           pchEntityName,
                       zPCHAR           pchAttributeName,
                       zPCHAR           pchOper,
                       zPCHAR           pchValue )
{
   LPVIEWENTITY      lpViewEntity;
   LPVIEWATTRIB      lpViewAttrib;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   zVIEW             vQual;
   zLONG             lCnt;

   if ( *pvQual == 0 )
   {
      if ( fnDeclareView( pvQual, lpCurrentTask, lpView,
                          "KZDBHQUA", TRUE ) != 0 )
      {
         *pvQual = 0;
         return( zCALL_ERROR );
      }

      if ( fnActivateEmptyObjectInstance( lpCurrentTask, *pvQual,
                                          zSINGLE ) != 0 )
      {
         return( zCALL_ERROR );
      }
   }

   vQual = *pvQual;

   // If pchEntitySpec was supplied, then create an entity spec.
   if ( pchEntitySpec )
   {
      // Get lpViewEntity, lpViewEntityCsr, and lpViewAttrib.
      lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, vQual, "EntitySpec", 0 );
      lpViewAttrib = fnValidViewAttrib( vQual, lpViewEntity, "EntityName", 0 );

      // Make sure entity spec doesn't already exist.
      if ( fnSetEntityCursor( vQual, lpViewEntity, lpViewEntityCsr,
                              lpViewAttrib, zPOS_FIRST | zQUAL_STRING,
                              (zPVOID) pchEntitySpec,
                              0, 0, 0, 0, 0, lpCurrentTask ) != zCURSOR_SET )
      {
         if ( fnCreateEntity( vQual, lpViewEntity, lpViewEntityCsr,
                              zPOS_NEXT, FALSE ) != 0 )
         {
            return( zCALL_ERROR );
         }

         if ( fnSetAttributeFromVariable( vQual, lpViewEntityCsr, lpViewAttrib,
                                          (zPVOID) pchEntitySpec, 'S', 0, 0,
                                          lpCurrentTask, 0 ) != 0 )
         {
            return( zCALL_ERROR );
         }
      }
   }

   // If no oper was supplied we're done.
   if ( pchOper == 0 )
      return( 0 );

   if ( plpViewEntityCsr )
   {
      if ( *plpViewEntityCsr )
      {
         // User supplied valid cursor so use it.
         lpViewEntityCsr = *plpViewEntityCsr;
         lpViewEntity    = zGETPTR( (*plpViewEntityCsr)->hViewEntity );
      }
      else
      {
         // Get lpViewEntity and plpViewEntityCsr.
         lpViewEntity    = fnValidViewEntity( plpViewEntityCsr, vQual, "QualAttrib", 0 );
         lpViewEntityCsr = *plpViewEntityCsr;
      }
   }
   else
   {
      lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, vQual, "QualAttrib", 0 );
   }

   // Create the new qual attrib.
   if ( fnCreateEntity( vQual, lpViewEntity, lpViewEntityCsr,
                        zPOS_LAST, FALSE ) != 0 )
   {
      return( zCALL_ERROR );
   }

   // Loop through each of the view attribs.  When we find one we want, set
   // the value.  We keep track of the # of attributes we set so we don't
   // have to keep searching even when we've set all the values.
   lCnt = 0;
   for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
         lpViewAttrib;
         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
   {
      zPCHAR pchAttribName = lpViewAttrib->szName;

      if ( zstrcmp( pchAttribName, "EntityName" ) == 0 )
      {
         if ( pchEntityName &&
              fnSetAttributeFromVariable( vQual, lpViewEntityCsr, lpViewAttrib,
                                          (zPVOID) pchEntityName, 'S', 0, 0,
                                          lpCurrentTask, 0 ) != 0 )
         {
            return( zCALL_ERROR );
         }

         if ( ++lCnt == 4 )
            break;               // We've set all values so break.
      }
      else
      if ( zstrcmp( pchAttribName, "AttributeName" ) == 0 )
      {
         if ( pchAttributeName &&
              fnSetAttributeFromVariable( vQual, lpViewEntityCsr, lpViewAttrib,
                                          (zPVOID) pchAttributeName, 'S', 0, 0,
                                          lpCurrentTask, 0 ) != 0 )
         {
            return( zCALL_ERROR );
         }

         if ( ++lCnt == 4 )
            break;               // We've set all values so break.
      }
      else
      if ( zstrcmp( pchAttribName, "Oper" ) == 0 )
      {
         if ( fnSetAttributeFromVariable( vQual, lpViewEntityCsr, lpViewAttrib,
                                          (zPVOID) pchOper, 'S', 0, 0,
                                          lpCurrentTask, 0 ) != 0 )
         {
            return( zCALL_ERROR );
         }

         if ( ++lCnt == 4 )
            break;               // We've set all values so break.
      }
      else
      if ( zstrcmp( pchAttribName, "Value" ) == 0 )
      {
         if ( pchValue &&
              fnSetAttributeFromVariable( vQual, lpViewEntityCsr, lpViewAttrib,
                                          (zPVOID) pchValue, 'S', 0, 0,
                                          lpCurrentTask, 0 ) != 0 )
         {
            return( zCALL_ERROR );
         }

         if ( ++lCnt == 4 )
            break;               // We've set all values so break.
      }

   } // for...

   return( 0 );

} // fnCreateQualification

zCHAR gszKeyDelimStr[] = "/|\\\t\n`~!@#$%^&*-_=+;<>?aAzZ10";

/*
   Keys are seperated by delimiters.  If this function is called then a new
   delimiter must be found because the current delimiter was found to exist
   in the latest key.  Find a new delimiter by finding the next char in the
   delimter string that does not exist in the current key values or the new
   key value.
*/
zCHAR LOCALOPER
fnFindKeyDelim( zCHAR  chCurrentDelim,
                zPCHAR pchStart,
                zPCHAR pchEnd,
                zPCHAR pchNewString )
{
   zPCHAR pchOldDelim;
   zPCHAR pchNewDelim;
   zPCHAR pch;

   if ( chCurrentDelim == 0 )
      return( gszKeyDelimStr[ 0 ] );

   // Look for current delim in string.
   pchOldDelim = zstrchr( gszKeyDelimStr, chCurrentDelim );

   // Point to next delim in string.
   pchNewDelim = pchOldDelim + 1;

   // Look for next delim in gszKeyDelimStr not in buffer or new string.
   while ( zstrchr( pchNewString, *pchNewDelim ) )
      pchNewDelim++;

   for ( pch = pchStart; pch < pchEnd; pch++ )
   {
      if ( *pch == *pchNewDelim )
      {
         pchNewDelim++;

         // Make sure new delim isn't in new string.
         while ( zstrchr( pchNewString, *pchNewDelim ) )
            pchNewDelim++;

         // Reset pch to start looking at the beginning of the string again.
         pch = pchStart;

         continue;
      }
   }

   // Convert all pchOldDelims to pchNewDelim.
   for ( pch = pchStart; pch < pchEnd; pch++ )
   {
      if ( *pch == *pchOldDelim )
         *pch = *pchNewDelim;
   }

   return( *pchNewDelim );

} // fnFindKeyDelim

/*

   Create a string of all the concatinated keys in lpEntityInstance.

*/
zSHORT LOCALOPER
fnCreateConcatKey( zPCHAR           pchKeyString,
                   LPENTITYINSTANCE lpEntityInstance,
                   LPVIEWATTRIB     lpKeyViewAttrib[],
                   zSHORT           nKeyCnt )
{
   LPVIEWOI lpViewOI = zGETPTR( lpEntityInstance->hViewOI );
   LPTASK   lpAllocTask = zGETPTR( lpViewOI->hAllocTask );
   zPCHAR   pch;
   zCHAR    chDelim;
   zSHORT   k;

   // Get the default key delimiter.
   chDelim = fnFindKeyDelim( 0, 0, 0, 0 );

   // Because the delimiter can change, the first char will be the delimiter for the string.
   pch = pchKeyString;

   // Go through each of the keys are retrieve the values.
   for ( k = 0; k < nKeyCnt; k++ )
   {
      zPVOID  lpPtr;
      zULONG  ulLth;

      *pch++ = chDelim;

      // Get pointer to key value.
      if ( fnGetAttrAddrFromEntityInstance( (zCOREMEM) &lpPtr,
                                            &ulLth, lpEntityInstance,
                                            lpKeyViewAttrib[ k ] ) == -1 )
      {
         // Key is null so just continue.
         continue;
      }

      // Convert internal key value to string.
      switch ( lpKeyViewAttrib[ k ]->cType )
      {
         case zTYPE_STRING:
            // Don't need to convert it--just copy it.
            strcpy_s( pch, zMAX_KEYLTH_FOR_LOCK + 1 - (pch - pchKeyString), (zPCHAR) lpPtr );
            break;

         case zTYPE_INTEGER:
            zltoa( *((zPLONG) lpPtr), pch, zMAX_KEYLTH_FOR_LOCK + 1 - (pch - pchKeyString) );
            break;

         case zTYPE_DECIMAL:
            ConvertDecimalToString( pch, lpKeyViewAttrib[ k ], *((zPDECIMAL) lpPtr), 0 );
            break;

         case zTYPE_BLOB:
            // No blobs should ever be keys.
            break;

         case zTYPE_DATETIME:
             UfDateTimeToString( (LPDATETIME) lpPtr, pch, 18 );
            break;

      } // switch ( lpKeyViewAttribute[ k ]->cType )...

      // Make sure that the delimiter is not in the new value.
      if ( zstrchr( pch, chDelim ) != 0 )
      {
         // The current delimiter exists in the key value so we must get a new one.
         // fnFindKeyDelim will change all the old delims to match the new delim.
         chDelim = fnFindKeyDelim( chDelim, pchKeyString, pch, pch );
      }

      // Set pch to point to the end of the string.
      pch = zstrchr( pch, 0 );

   } // for ( k... )

   return( 0 );

} // fnCreateConcatKey

/*

   This oper checks to make sure that all the twin entities of
   lpFirstEntityInstance are not locked.

   If bLOD_Lock is TRUE then the lock we are checking is at the LOD level
   (and lpFirstEntityInstance had better be a root instance!).

*/
zSHORT LOCALOPER
fnCheckLocksOnTwins( LPTASK           lpCurrentTask,
                     zBOOL            bLOD_Lock,
                     zBOOL            bAllowReadOnly,
                     zVIEW            lpView,
                     LPENTITYINSTANCE lpFirstEntityInstance,
                     LPVIEWOD         lpViewOD )
{
   LPVIEWENTITY      lpViewEntity;
   LPVIEWATTRIB      lpViewAttrib;
   LPVIEWATTRIB      lpKeyViewAttrib[ zMAX_KEYS_FOR_LOCK ];
   LPENTITYINSTANCE  lpEntityInstance;
   LPVIEWENTITYCSR   lpQualAttribEntityCsr = 0;
   LPVIEWATTRIB      lpValueViewAttrib;
   zVIEW             vQual = 0;
   zVIEW             vLock = 0;
   zCHAR             szKeyString[ zMAX_KEYLTH_FOR_LOCK + 1 ];
   zCHAR             szLockName[ 35 ];
   zSHORT            nKeyCnt;
   zSHORT            nRC = zCALL_ERROR;       // Assume everything error.

   lpViewEntity = zGETPTR( lpFirstEntityInstance->hViewEntity );

   // To save time later find all the keys in the LOD and store them in a table.
   nKeyCnt = 0;
   for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
         lpViewAttrib;
         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
   {
      if ( lpViewAttrib->bKey )
         lpKeyViewAttrib[ nKeyCnt++ ] = lpViewAttrib;
   }

   if ( bLOD_Lock )
   {
      // We are checking a LOD level lock so we set LockName to the name of
      // the LOD.
      strcpy_s( szLockName, zsizeof( szLockName ), lpViewOD->szName );
   }
   else
   {
      // We are checking a lock at the entity level so use the name of the
      // entity for the LockName.  In addition, to handle the rare case where
      // a LOD and entity name are the same we prefix all entity names with
      // a '@' because it's an invalid character for entity names.  This
      // insures that the LockName for the entity does not match a LOD name.
      sprintf_s( szLockName, zsizeof( szLockName ), "@%s", lpViewEntity->szName );
   }

   // Create EntitySpec and QualAttribs.  This creates a qual that
   // is analogous to:
   //    ACTIVATE view WHERE view.ZeidonLock.LOD_Name = lod-name AND
   //                        view.ZeidonLock.KeyValue = ?
   fnCreateQualification( lpCurrentTask, lpView, &vQual,
                          &lpQualAttribEntityCsr, "ZeidonLock", "ZeidonLock",
                          "LOD_Name", "=", szLockName );
   fnCreateQualification( lpCurrentTask, lpView, &vQual,
                          &lpQualAttribEntityCsr, 0, 0, 0, "AND", 0 );
   fnCreateQualification( lpCurrentTask, lpView, &vQual,
                          &lpQualAttribEntityCsr,
                          0, "ZeidonLock", "KeyValue", "=", "" );

   // Get the lpViewAttrib for the Value attribute for later use with
   // fnSetAttributeFromVariable.
   lpValueViewAttrib =
           fnValidViewAttrib( vQual,
                              zGETPTR( lpQualAttribEntityCsr->hViewEntity ),
                              "Value", 0 );

   // Loop through each of the root entities and make sure that none of the
   // key values already exist.
   for ( lpEntityInstance = lpFirstEntityInstance;
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin ) )
   {
      zSHORT k;

      // Create the concat key string and set the value in the qual object.
      fnCreateConcatKey( szKeyString, lpEntityInstance,
                         lpKeyViewAttrib, nKeyCnt );
      fnSetAttributeFromVariable( vQual, lpQualAttribEntityCsr,
                                  lpValueViewAttrib, (zPVOID) szKeyString,
                                  'S', 0, 0, lpCurrentTask, 0 );


      k = ActivateObjectInstance( &vLock, "ZPLOCKO", lpView, vQual, 0 );
      if ( k < -1 )
         goto EndOfFunction;

      if ( k >= 0 )
      {
         zPCHAR pch;

         // Uh-oh -- we found a lock record matching the keys.  Check to see
         // if we can at least keep the view as read-only.
         GetAddrForAttribute( &pch, vLock, "ZeidonLock", "AllowRead" );
         if ( *pch != 'Y' || bAllowReadOnly == FALSE )
         {
            zCHAR szWhat[ 100 ];
            zCHAR szMsg[ 200 ];
            zCHAR szDate[ 50 ];

            // User attempted to get some sort of lock but it's already locked
            // OR
            // someone has an exclusive lock that doesn't even allow
            // read-only views so don't allow activate.

            if ( bLOD_Lock )
               sprintf_s( szWhat, zsizeof( szWhat ), "LOD '%s' is locked", lpViewOD->szName );
            else
               sprintf_s( szWhat, zsizeof( szWhat ), "Entity '%s' is locked", lpViewEntity->szName );

            GetAddrForAttribute( &pch, vLock, "ZeidonLock", "UserName" );
            GetStringFromAttribute( szMsg, zsizeof( szMsg ), vLock, "ZeidonLock", "Timestamp" );
            UfFormatDateTime( szDate, zsizeof( szDate ), szMsg, "YYYY-M-D HH:MI:SS" );
            TraceLineS( "(oi) Object locked by ", pch );
            TraceLineS( "(oi) Object locked on ", szDate );
            TraceLineS( "(oi) Concatenated key = ", szKeyString );
         // sprintf_s( szMsg, zsizeof( szMsg ), "By '%s' on %s", pch, szDate );
         // fnIssueCoreError( lpTask, lpView, 16, 94, 0, szWhat, szMsg );

            nRC = zLOCK_ERROR;
            goto EndOfFunction;
         }
      }

      // We don't need it anymore so...
      fnDropView( vLock );
      vLock = 0;

   } // for ( lpEntityInstance...)

   // If we get here then everything is OK.
   nRC = 0;

EndOfFunction:
   if ( vQual )
      fnDropView( vQual );

   if ( vLock )
      fnDropView( vLock );

   return( nRC );

} // fnCheckLocksOnTwins

// DGC 2000.06.21
// Caching logic is being removed because it conflicts with DBHandlers that
// use JOINS to load objects.  I'm leaving the code in because it is
// possible that some day we will want to use caching from the DBHandler.
#if 0
//./ ADD NAME=fnFindCacheViewEntity
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   fnFindCacheViewEntity
//
//  PURPOSE:    To find the first entity in the OD that has the same ER
//              token as lpViewEntity.
//
//
//  PARAMETERS:  lpViewOD     - Obvious
//               lpViewEntity - Entity we are trying to find a cache for.
//
//  RETURNS:    Caching entity.
//
/////////////////////////////////////////////////////////////////////////////
//./ END
LPVIEWENTITY LOCALOPER
fnFindCacheViewEntity( LPVIEWOD     lpViewOD,
                       LPVIEWENTITY lpViewEntity )
{
   LPVIEWENTITY lpCacheViewEntity;

   if ( lpViewOD )
      lpCacheViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
   else
   {
      // Find the first view entity by backing up from lpViewEntity.
      for ( lpCacheViewEntity = lpViewEntity;
            lpCacheViewEntity->hPrevHier;
            lpCacheViewEntity = zGETPTR( lpCacheViewEntity->hPrevHier ) )
      {
         ; // nothing needs to be done here
      }
   }

   for ( ;
         lpCacheViewEntity;
         lpCacheViewEntity = zGETPTR( lpCacheViewEntity->hNextHier ) )
   {
      if ( lpCacheViewEntity->lEREntTok == lpViewEntity->lEREntTok )
         return( zGETHNDL( lpCacheViewEntity ) );
   }

   // We should never be here...
   return( 0 );
}

zVOID LOCALOPER
fnCacheEntity( LPENTITYINSTANCE lpEntityInstance,
               LPCACHEINFO      lpCacheInfo )
{
   LPENTITYCACHE lpEntityCache;
   LPRELRECORD   lpRelRecord;
   LPVIEWENTITY  lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
   LPVIEWENTITY  lpCacheViewEntity;
   LPDATARECORD  lpFirstDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );

   // Don't bother caching entities unless the relationship between the
   // entity and it's parent is the reverse of 1-to-m.
   lpRelRecord = zGETPTR( lpFirstDataRecord->hFirstRelRecord );
   if ( lpRelRecord->cOwnerMember != zDBH_MANY_TO_ONE )
      return;

   // Entity cache data is stored after entity cache info.
   lpEntityCache = (LPENTITYCACHE) (lpCacheInfo + 1);

   // Caches are stored under the first ViewEntity that matches
   // lpViewEntity->lERAttTok.
   if ( lpViewEntity->hCacheViewEntity == 0 )
      lpViewEntity->hCacheViewEntity = fnFindCacheViewEntity( 0, lpViewEntity );
   lpCacheViewEntity = zGETPTR( lpViewEntity->hCacheViewEntity );

   // Now point lpEntityCache to point to the correct entity.
   lpEntityCache = (LPENTITYCACHE)
      ((zPCHAR) lpEntityCache +
             (lpCacheInfo->usCacheSize * (lpCacheViewEntity->nHierNbr - 1)));

#if 0 // DGC 10/22/98  Is this needed?  We only get into this function if the
      //               entity was loaded, not cached.

   // Now loop through each of the cached entity instances to see if the
   // entity is already cached.
   for ( uIdx = 0;
         uIdx < lpCacheInfo->cCacheNbr &&
            lpEntityCache->lpEntityInstance[ uIdx ];  // Ignore empty EIs.
         uIdx++ )
   {
      if ( lpEntityCache->lpEntityInstance[ uIdx ] == lpEntityInstance )
         return;  // Entity is already cached.
   }
#endif

   // Entity isn't cached, so cache it.
   lpEntityCache->lpEntityInstance[ lpEntityCache->uIdx ] = lpEntityInstance;
   lpEntityCache->uIdx = (lpEntityCache->uIdx + 1 ) % lpCacheInfo->cCacheNbr;

} // fnCacheEntity

zBOOL LOCALOPER
fnLoadCachedEntity( LPTASK           lpTask,
                    zVIEW            lpView,
                    LPVIEWENTITY     lpViewEntity,
                    LPENTITYINSTANCE lpParentInstance,
                    LPCACHEINFO      lpCacheInfo )
{
   LPENTITYCACHE lpEntityCache;
   LPDATARECORD  lpDataRecord = zGETPTR( lpViewEntity->hFirstDataRecord );
   LPRELRECORD   lpRelRecord;
   LPVIEWENTITY  lpCacheViewEntity;
   LPVIEWENTITY  hViewEntity = zGETHNDL( lpViewEntity );
   zUSHORT       uIdx;

   // We can't load cached entities unless the relationship between the current
   // entity and it's parent is the reverse of 1-to-m.
   lpRelRecord = zGETPTR( lpDataRecord->hFirstRelRecord );
   if ( lpRelRecord->cOwnerMember != zDBH_MANY_TO_ONE )
      return( FALSE );

   // Entity cache data is stored after entity cache info.
   lpEntityCache = (LPENTITYCACHE) (lpCacheInfo + 1);

   // Caches are stored under the first ViewEntity that matches
   // lpViewEntity->lERAttTok.
   if ( lpViewEntity->hCacheViewEntity == 0 )
      lpViewEntity->hCacheViewEntity = fnFindCacheViewEntity( 0, lpViewEntity );
   lpCacheViewEntity = zGETPTR( lpViewEntity->hCacheViewEntity );

   // Now point lpEntityCache to point to the correct entity.
   lpEntityCache = (LPENTITYCACHE)
      ((zPCHAR) lpEntityCache +
             (lpCacheInfo->usCacheSize * (lpCacheViewEntity->nHierNbr - 1)));

   // Now loop through each of the cached entity instances to see if any keys
   // match the parent keys.
   for ( uIdx = 0;
         uIdx < lpCacheInfo->cCacheNbr &&
            lpEntityCache->lpEntityInstance[ uIdx ];  // Ignore empty EIs.
         uIdx++ )
   {
      zBOOL             bCompareOK;
      LPRELFIELD        lpRelField;
      LPENTITYINSTANCE  lpNewEI;
      zCHAR             szMsg[ 100 ];

      // Assume entities have the same key values until proven otherwise.
      bCompareOK = TRUE;

      // Get the view entity for the entity instance that was cached.
      lpCacheViewEntity =
            zGETPTR( lpEntityCache->lpEntityInstance[ uIdx ]->hViewEntity );

      // Compare each of the keys (rel fields).
      for ( lpRelField = zGETPTR( lpRelRecord->hFirstRelField );
            lpRelField;
            lpRelField = zGETPTR( lpRelField->hNextRelField ) )
      {
         LPENTITYINSTANCE lpParentEI;
         LPVIEWENTITY     lpSrchViewEntity;
         LPDATAFIELD      lpRelDataField;
         LPDATAFIELD      lpSrcDataField;
         LPVIEWATTRIB     lpViewAttrib;

         // Get the parent entity instance for each rel field so that we can
         // compare it's attribute value with the attribute value from the
         // cached EI.  Since the key value can come from any entity in the
         // parent chain, we must find the entity instance that has the
         // same lpViewEntity as the one referenced in the rel field.
         lpParentEI = lpParentInstance;  // Start with the immediate parent.
         lpSrcDataField   = zGETPTR( lpRelField->hSrcDataField );
         lpRelDataField   = zGETPTR( lpRelField->hRelDataField );
         lpViewAttrib     = zGETPTR( lpRelDataField->hViewAttrib );
         lpSrchViewEntity = zGETPTR( lpViewAttrib->hViewEntity );

         while ( lpParentEI &&
                 lpParentEI->hViewEntity != zGETHNDL( lpSrchViewEntity ) )
         {
            lpParentEI = zGETPTR( lpParentEI->hParent );
         }

         // If there is no parent entity instance then there is some error.
         // Return FALSE.
         if ( lpParentEI == 0 )
            return( FALSE );

         if ( fnCompareEIAttrs( lpTask, lpParentEI,
                                lpEntityCache->lpEntityInstance[ uIdx ],
                                lpViewAttrib, 0,
                                zGETPTR( lpSrcDataField->hViewAttrib ),
                                0 ) != 0 )
         {
            bCompareOK = FALSE;
            break;
         }

      } // for ( lpRelField... )...

      // Attribute values didn't compare so continue with the next cached EI.
      if ( bCompareOK == FALSE )
         continue;

      // Entity keys match!  It is possible that the cached EI has different
      // attributes then the EI we are loading.  Check to make sure that all
      // the non-hidden attributes in the target entity are not hidden in
      // the cached EI.
      if ( !fnEntityContainsEntity( lpCacheViewEntity, lpViewEntity ) )
      {
         // Target entity has an attribute that the cache entity does not so
         // we consider the compare to fail.  Go to the next cached entity.
         continue;
      }

      // Create new entity instance from cached EI.
      lpCacheInfo->ulCacheCount++;

      // First create the entity instance.
      LoadEntity( lpView, lpViewEntity->szName, zPOS_LAST, 0 );

      // Find the entity instance for the new child.
      for ( lpNewEI = zGETPTR( lpParentInstance->hNextHier );
            lpNewEI->hViewEntity != hViewEntity;
            lpNewEI = zGETPTR( lpNewEI->hNextHier ) )
      {
         // nothing needs to be done here
      }

      // Delete the persistent record from the new EI.
      fnDeleteAttributeRecord( lpViewEntity, lpNewEI, TRUE );

      // Copy a new persistent record from the cached EI.
      lpNewEI->hPersistRecord =
        fnCopyAttributeRecord( zGETPTR( lpViewOI->hAllocTask ), lpViewEntity, // VieOI is needed
                               zGETPTR( lpEntityCache->
                                 lpEntityInstance[ uIdx ]->hPersistRecord ),
                               TRUE );

      // Do the same for non-persistent records.
      fnDeleteAttributeRecord( lpViewEntity, lpNewEI, FALSE );
      lpNewEI->hNonPersistRecord =
        fnCopyAttributeRecord( zGETPTR( lpViewOI->hAllocTask ),  // ViewOI is needed
                               lpViewEntity,
                               zGETPTR( lpEntityCache->
                                 lpEntityInstance[ uIdx ]->hNonPersistRecord ),
                               FALSE );

      if ( lpTask->nDBHandlerTraceLevel > 0 )
      {
         TraceLineS( "", "" );
         sprintf_s( szMsg, zsizeof( szMsg ), "Entity %s loaded from cache.", lpViewEntity->szName );
         TraceLineS( szMsg, "" );
         TraceLineS( "", "" );
      }

      // We created the EI from a cached EI, so return TRUE.
      return( TRUE );

   } // for ( uIdx... )...

   // No cached records matched the one needed so return false.
   return( FALSE );

} // fnLoadCachedEntity

#endif // Remove cache logic.

/*

   Checks to make sure that lpEntityInstance does not have a parent with
   the same keys.

   Returns FALSE - No infinite loop.
           TRUE  - Oops...infinite loop.
*/
zSHORT LOCALOPER
fnCheckForRecursiveLoop( zVIEW            lpView,
                         LPENTITYINSTANCE lpEntityInstance )
{
   LPVIEWENTITY     lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
   LPENTITYINSTANCE lpParent;
   LPVIEWATTRIB     lpKeys[ 200 ];
   LPVIEWATTRIB     lpViewAttrib;
   LPTASK           lpCurrentTask = zGETPTR( lpView->hTask );
   zSHORT           nKeyCnt;

   // In an attempt to make things faster later let's get all the keys for
   // lpEntityInstance.
   nKeyCnt = 0;
   for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
         lpViewAttrib;
         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
   {
      if ( lpViewAttrib->bKey == FALSE )
        continue;

      lpKeys[ nKeyCnt++ ] = lpViewAttrib;
   }


   for ( lpParent = zGETPTR( lpEntityInstance->hParent );
         lpParent;
         lpParent = zGETPTR( lpParent->hParent ) )
   {
      LPVIEWENTITY lpParentViewEntity = zGETPTR( lpParent->hViewEntity );
      zBOOL        bKeysMatch;
      zSHORT       k;

      // We only care about the parent if it's also recursive.  If NONE of the
      // recursive flags are set then skip it.  It's possible--althought
      // highly unlikely--that the entity we are looking for also exists as
      // a non-recursive entity between the recursive parent & child.
      if ( lpParentViewEntity->bRecursiveSt  == 0 &&
           lpParentViewEntity->bRecursive    == 0 &&
           lpParentViewEntity->bRecursivePar == 0 )
      {
         continue;
      }

      // The parent must be the same ER entity as the child.
      if ( lpParentViewEntity->lEREntTok != lpViewEntity->lEREntTok )
         continue;

      // Make sure the keys are different.  We will start by assuming they
      // are the same until proven otherwise.
      bKeysMatch = TRUE;
      for ( k = 0; k < nKeyCnt; k++ )
      {
         LPVIEWATTRIB lpParentViewAttrib;

         // Now find the key value in the parent.
         if ( lpViewEntity == lpParentViewEntity )
            lpParentViewAttrib = lpKeys[ k ];
         else
         {
            // We have to hunt for it.
            for ( lpParentViewAttrib = zGETPTR( lpParentViewEntity->hFirstOD_Attrib );
                  lpParentViewAttrib->lERAttTok != lpKeys[ k ]->lERAttTok;
                  lpParentViewAttrib = zGETPTR( lpParentViewAttrib->hNextOD_Attrib ) )
            {
               ; // nothing needs to be done here
            }
         }

         if ( fnCompareEIAttrs( lpCurrentTask,
                                0, lpParent, lpParentViewAttrib, 0,
                                0, lpEntityInstance, lpKeys[ k ], 0 ) != 0 )
         {
            bKeysMatch = FALSE;
            break;
         }
      }

      // If bKeysMatch is still TRUE then lpParent and lpEntityInstance
      // reference the same data.  This is an error that will cause an
      // infinite loop in the recursive subobject.
      if ( bKeysMatch )
      {
         LPVIEWOD lpViewOD = zGETPTR( lpView->hViewOD );

         TraceLineS( "==== Activate error: Infinite recursive subobject ====", "" );
         TraceLineS( "Object Name   = ", lpViewOD->szName );
         TraceLineS( "Parent Entity = ", lpParentViewEntity->szName );
         TraceLineI( "Parent level  = ", lpParent->nLevel );
         TraceLineS( "Child Entity  = ", lpViewEntity->szName );
         TraceLineI( "Child level   = ", lpEntityInstance->nLevel );
         DisplayEntityInstance( lpView, lpViewEntity->szName );

         //  "KZOEE095 - Recursive error."
         fnIssueCoreError( lpCurrentTask, lpView, 16, 95, 0, lpViewOD->szName, 0 );

         return( TRUE );
      }

   } // for each lpParent...

   // If we get here then everything must be OK.
   return( FALSE );

} // fnCheckForRecursiveLoop.

//./ ADD NAME=fnLoadChildEntities
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   fnLoadChildEntities
//
//  PURPOSE:    To load all the child enties of lpEntityInstance.
//              Used only by fnActivateObjectInstance.
//
//  ASSUMES:    The object instance referenced by lpView is empty.
//
//
//  PARAMETERS:  lpView       - Target view.
//               lpEntityInst - Parent entity instance.
//               lpQualView   - View to qualification object
//               pOper        - Function pointer to DBHandler routine.
//               lpPtr        - Work pointer used by DBHandler.
//
//  RETURNS:    0 - Entities loaded.
//              2 - Entities loaded but Activate Limit constraint reached.
//   zDB_DEADLOCK - database deadlock occurred
//   zCALL_ERROR  - Error loading entities.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 6
zSHORT
fnLoadChildEntities( LPTASK           lpCurrentTask,
                     zVIEW            lpView,
                     LPENTITYINSTANCE lpEntityInstance,
                     zVIEW            lpQualView,
                     zPDBHOPER        pOper,
                     zPVOID           *lpPtr )
{
   LPVIEWOD         lpViewOD = zGETPTR( lpView->hViewOD );
   LPVIEWENTITY     hViewEntity;
   LPVIEWENTITY     lpViewEntity;
   LPVIEWENTITY     lpChildViewEntity;
   LPVIEWENTITY     hChildViewEntity;
   LPVIEWENTITYCSR  lpViewEntityCsr;
   LPENTITYINSTANCE lpChildEntityInstance;
   zSHORT           nEntityInstanceLevel;
   zSHORT           nReturnCode = 0;
   zSHORT           nRC;

   lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
   nEntityInstanceLevel = lpEntityInstance->nLevel;

   // If view entity is recursive, then reset lpViewEntity to point to the
   // parent view entity that has the same EREntTok as the current lpViewEntity.
   if ( lpViewEntity->bRecursive )
   {
      zLONG lCurrentEREntTok;

      lCurrentEREntTok = lpViewEntity->lEREntTok;
      lpViewEntity = zGETPTR( lpViewEntity->hParent );
      while ( lpViewEntity->lEREntTok != lCurrentEREntTok )
         lpViewEntity = zGETPTR( lpViewEntity->hParent );
   }

   hViewEntity = zGETHNDL( lpViewEntity );

   // The first child ViewEntity of the current lpViewEntity is the next
   // view entity in hierachical order.
   hChildViewEntity  = lpViewEntity->hNextHier;
   lpChildViewEntity = zGETPTR( hChildViewEntity );

   // Check to see if there are child entity definitions.  If not, there are
   // no children to load, so exit.  There is no child entity if:
   //    o lpChildViewEntity is null (there are no entities after
   //      lpViewEntity).
   //    o The level number of the next view entity is "equal to" (which means
   //      that the next view entity is a sibling) or "less than" (which means
   //      that the next view entity is the sibling of an ancestor).
   if ( lpChildViewEntity == 0 ||
        lpChildViewEntity->nLevel <= lpViewEntity->nLevel )
   {
      return( 0 );
   }

   // Load all the child entities of lpEntityInstance, starting with the first
   // child entity definition via hierarchical ordering.  After loading a type
   // of entity, find the next child entity type and (if there are more) load
   // those.  Keep going until there are no more child entity types for
   // lpEntityInstance.

   for ( ;
         lpChildViewEntity;
         lpChildViewEntity = zGETPTR( lpChildViewEntity->hNextSibling ) )
   {
      hChildViewEntity = zGETHNDL( lpChildViewEntity );

      // If the max cardinality of the child instance is 1 then it's possible
      // that the child was already activated by the DBHandler.  Check to see
      // if a child EI already exists.
      if ( lpChildViewEntity->uCardMax == 1 )
      {
         // Because the object might be recursive, we also
         // need to check to make sure that the level of the child entity
         // instance is exactly 1 more the the level of the parent entity.
         lpChildEntityInstance = zGETPTR( lpEntityInstance->hNextHier );
         while ( lpChildEntityInstance &&
                 (lpChildEntityInstance->hViewEntity != hChildViewEntity ||
                  lpChildEntityInstance->nLevel != nEntityInstanceLevel + 1) )
         {
            if ( lpChildEntityInstance->nLevel <= nEntityInstanceLevel )
            {
               lpChildEntityInstance = 0;
               break;
            }

            while ( lpChildEntityInstance->hNextTwin )
               lpChildEntityInstance = zGETPTR( lpChildEntityInstance->hNextTwin );

            lpChildEntityInstance = zGETPTR( lpChildEntityInstance->hNextHier );
         }

         nRC = 0;
      }
      else
         lpChildEntityInstance = 0;

      // If lpChildEntityInstance is still 0 then we need to load it.
      if ( lpChildEntityInstance == 0 )
      {
         // If the child entity not either a derived path or a duplicate
         // relationship path then attempt to load that entity.
         if ( lpChildViewEntity->bDerivedPath == FALSE &&
              lpChildViewEntity->bDupRelPath == FALSE )
         {
            // Child entities couldn't be loaded via cacheing, so call the
            // db-handler.
            nRC = (*pOper)( (zLONG) zGETHNDL( lpCurrentTask ),
                            DBH_Entity | DBH_Load, 0, lpViewOD,
                            lpChildViewEntity, lpView, lpQualView, lpPtr );
            if ( nRC == zDB_DEADLOCK )
               return( nRC );

            if ( lpCurrentTask->bLoadAllocLimit )
            {
               lpCurrentTask->bLoadAllocLimit = FALSE;
               return( zMEMORY_LIMIT );
            }

            if ( nRC < -1 )
               return( zCALL_ERROR );

            // Check to see if the activate limit was reached.
            if ( nRC == 2 )
               nReturnCode = 2;
         }

         // If we didn't load any child entities see if we need to create a
         // child entity because of the "hanging keys" problem.
         if ( nRC == -1 && lpChildViewEntity->bHangingFKey )
            fnAddHangingEntity( lpView, lpChildViewEntity );

         // If any children were loaded, call this proc recursively to load all
         // of THEIR children.

         // Find the first child entity of lpChildViewEntity.
         lpChildEntityInstance = zGETPTR( lpEntityInstance->hNextHier );

         // Now find the first child entity instance that matches
         // lpChildViewEntity.  Because the object might be recursive, we also
         // need to check to make sure that the level of the child entity
         // instance is exactly 1 more the the level of the parent entity.
         while ( lpChildEntityInstance &&
                 (lpChildEntityInstance->hViewEntity != hChildViewEntity ||
                  lpChildEntityInstance->nLevel != nEntityInstanceLevel + 1) )
         {
            if ( lpChildEntityInstance->nLevel <= nEntityInstanceLevel )
            {
               lpChildEntityInstance = 0;
               break;
            }

            while ( lpChildEntityInstance->hNextTwin )
               lpChildEntityInstance = zGETPTR( lpChildEntityInstance->hNextTwin );

            lpChildEntityInstance = zGETPTR( lpChildEntityInstance->hNextHier );
         }

      } // if ( lpChildEntityInstance == 0 )...

      // If nRC == -1, then no children were loaded.
      if ( nRC >= 0 && lpChildEntityInstance )
      {
         // Load the children of the just-loaded children.
         while ( lpChildEntityInstance )
         {
            //
            // Make lpChildEntityInstance the current instance.
            //
            lpViewEntityCsr =
                fnEstablishViewForInstance( lpView, 0, lpChildEntityInstance );

            // If the entity is flagged as recursive, then set the view to
            // have the current child entity as the parent of the recursive
            // relationship before calling fnLoadChildEntities.
            if ( lpChildViewEntity->bRecursive )
            {
               fnSetViewToSubobject( lpView, lpChildViewEntity,
                                     lpViewEntityCsr );

               // Check to make sure the recursive entity instance hasn't
               // already been loaded as a parent.  If it has then this is
               // an error because the OI has an infinite looping sub-object.
               // If the return value is TRUE then there was an error.
               if ( fnCheckForRecursiveLoop( lpView,
                                             lpChildEntityInstance ) == 0 )
               {
                  // Everything ok so load children.
                  nRC = fnLoadChildEntities( lpCurrentTask, lpView,
                                             lpChildEntityInstance, lpQualView,
                                             pOper, lpPtr );
                  if ( nRC == zDB_DEADLOCK || nRC == zMEMORY_LIMIT )
                     return( nRC );

                  if ( nRC < 0 )
                     return( zCALL_ERROR );

                  if ( nRC == 2 )
                     nReturnCode = 2;
               }

               fnResetViewFromSubobject( lpView );
            }
            else
            {
               nRC = fnLoadChildEntities( lpCurrentTask, lpView,
                                          lpChildEntityInstance, lpQualView,
                                          pOper, lpPtr );
               if ( nRC == zDB_DEADLOCK || nRC == zMEMORY_LIMIT )
                  return( nRC );

               if ( nRC < 0 )
                  return( zCALL_ERROR );

               if ( nRC == 2 )
                  nReturnCode = 2;
            }

            // Get next twin.
            lpChildEntityInstance = zGETPTR( lpChildEntityInstance->hNextTwin );

         }  // while ( lpChildEntityInstance )...

      }  // if ( nRC > 0 && lpChildEntityInstance &&... )...

   } // for ( lpChildViewEntity )

   return( nReturnCode );

}  // fnLoadChildEntities

/*
   This oper gets called after OIs have been loaded successfully and we need
   to set some locks.

   For each twin of lpFirstEntityInstance we will create a record that
   consists of the LOD/entity name and a string of concatenated keys.
*/
zSHORT LOCALOPER
fnSetLocksOnTwins( LPTASK           lpCurrentTask,
                   zBOOL            bLOD_Lock,
                   zVIEW            lpView,
                   LPENTITYINSTANCE lpFirstEntityInstance,
                   LPVIEWOI         lpViewOI,
                   zBOOL            bAllowRead )
{
   ViewClusterRecord vLock;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWATTRIB      lpViewAttrib;
   LPVIEWATTRIB      lpKeyViewAttrib[ zMAX_KEYS_FOR_LOCK ];
   LPENTITYINSTANCE  lpEntityInstance;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPVIEWOD          lpViewOD = zGETPTR( lpView->hViewOD );
   VIEWARRAYBLOCK    tViewArrayBlock = { 0 };
   zCHAR             szKeyString[ zMAX_KEYLTH_FOR_LOCK + 1 ];
   zCHAR             szLockName[ 35 ];
   zSHORT            nKeyCnt;
   zSHORT            nRC = zCALL_ERROR;       // Assume everything error.

   vLock.vOI = 0;
   vLock.lControl = 0;

   lpViewEntity = zGETPTR( lpFirstEntityInstance->hViewEntity );

   // To save time later find all the keys in the LOD and store them in a table.
   nKeyCnt = 0;
   for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
         lpViewAttrib;
         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
   {
      if ( lpViewAttrib->bKey )
         lpKeyViewAttrib[ nKeyCnt++ ] = lpViewAttrib;
   }

   // Create an empty lock OI.
   if ( fnDeclareView( &vLock.vOI, lpCurrentTask, lpView, "ZPLOCKO", FALSE ) != 0 )
      return( zCALL_ERROR );

   if ( fnActivateEmptyObjectInstance( lpCurrentTask, vLock.vOI, zMULTIPLE ) != 0 )
      return( zCALL_ERROR );

   // Get the lpViewEntity and lpViewEntityCsr for the lock OI.
   lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, vLock.vOI, "ZeidonLock", 0 );

   if ( bLOD_Lock )
   {
      // We are setting a LOD level lock so we set LockName to the name of
      // the LOD.
      strcpy_s( szLockName, zsizeof( szLockName ), lpViewOD->szName );
   }
   else
   {
      // We are setting a lock at the entity level so use the name of the
      // entity for the LockName.  In addition, to handle the rare case where
      // a LOD and entity name are the same we prefix all entity names with
      // a '@' because it's an invalid character for entity names.  This
      // insures that the LockName for the entity does not match a LOD name.
      lpViewEntity = zGETPTR( lpFirstEntityInstance->hViewEntity );
      sprintf_s( szLockName, zsizeof( szLockName ), "@%s", lpViewEntity->szName );
   }

   // Loop through each of the root entities and create a locking record.
   for ( lpEntityInstance = lpFirstEntityInstance;
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin ) )
   {
      LPENTITYINSTANCE lpLockInstance;

      // Create the concat key string.
      fnCreateConcatKey( szKeyString, lpEntityInstance,
                         lpKeyViewAttrib, nKeyCnt );

      if ( fnCreateEntity( vLock.vOI, lpViewEntity, lpViewEntityCsr,
                           zPOS_LAST, FALSE ) != 0 )
      {
         goto EndOfFunction;
      }

      // fnCreateEntity DOES NOT set the bCreated flag so set it.
      lpLockInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
      lpLockInstance->u.nInd.bCreated = TRUE;

      if ( fnSetLockingAttributes( lpCurrentTask,
                                   vLock.vOI, lpViewEntity, lpViewEntityCsr,
                                   szLockName, szKeyString,
                                   TRUE, TRUE, bAllowRead ? "Y" : "N" ) != 0 )
      {
         goto EndOfFunction;
      }
   } // for ( lpEntityInstance...)

   // Now commit the lock OI.
   if ( fnInitViewArrayBlock( &tViewArrayBlock, 1 ) != 0 )
      goto EndOfFunction;

   if ( fnCommitObjectInstance( &vLock, &vLock.vOI, 1, 0, lpCurrentTask,
                                0, &tViewArrayBlock ) != 0 )
   {
      goto EndOfFunction;
   }

   lpViewOI->bIsLocked = TRUE;

   // If we get here then everything is OK.
   nRC = 0;

EndOfFunction:
   if ( vLock.vOI )
      fnDropView( vLock.vOI );

   fnFreeViewArrayBlock( &tViewArrayBlock );

   return( nRC );

} // fnSetLocksOnTwins

//./ ADD NAME=fnActivateObjectInstance
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   fnActivateObjectInstance
//
//  PURPOSE:    To activate an Object instance and return a
//              view to the object instance.
//
//  ASSUMES:    The object instance referenced by lpView is empty.
//
//
//  PARAMETERS:  lpView     - View returned to instance activated
//               lpQualView - View qualifying what object instance to load
//               lControl   - Indicates the maximum # of root entities
//                            activated.
//
//  RETURNS:   -1 - No instance found matching lpQualView; pvReturnView
//                  unchanged.
//              0 - Object instance activated, single root found
//              1 - Object instance activated, multiple roots found.  If
//                  zSINGLE was specified, only the first was activated.
//   zDB_DEADLOCK - database deadlock occurred
//   zMEMORY_LIMIT - Activate reached memory limit for task
//   zCALL_ERROR  - Error loading entities.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT
fnActivateObjectInstance( LPTASK    lpCurrentTask,
                          zVIEW     lpView,
                          zVIEW     lpQualView,
                          zLONG     lControl )
{
   LPVIEWOD          lpViewOD;
   LPVIEWOI          lpViewOI;
   LPVIEWCSR         lpViewCsr;
   LPENTITYINSTANCE  lpEntityInstance;
   LPTASKDBHANDLER   lpTaskDBHandler;
   zPDBHOPER         pOper;
   zPVOID            lpPtr;
   zBOOL             bTransactionStartedHere;
   zSHORT            nReturnCode;
   zSHORT            nRC;

   lpPtr       = 0;
   nReturnCode = 0;

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   lpViewOD  = zGETPTR( lpViewOI->hViewOD );
   lpTaskDBHandler = fnGetDBHandlerOper( lpCurrentTask, lpView,
                                         (zlpPDBHOPER) &pOper );
   if ( lpTaskDBHandler == 0 )
      return( zCALL_ERROR );

   // Check to see if a transaction has already been started for the database.
   // If it has already been started we don't want to do it again but set a
   // flag to indicate we don't want to END the transaction later.
   //
   // We need to do this because fnActivateObjectInstance can be called
   // recursively.
   if ( lpTaskDBHandler->bTranStarted )
   {
      bTransactionStartedHere = FALSE;
      lpPtr = lpTaskDBHandler->lpConnection;
   }
   else
   {
      // Call DBHandler routine to issue start of transaction.
      nRC = (*pOper)( (zLONG) zGETHNDL( lpCurrentTask ),
                      DBH_Object | DBH_TranBegin, DBH_LoadOI,
                      lpViewOD, 0, lpView, lpQualView, &lpPtr );
      if ( nRC < 0 )
         return( nRC );

      // Set flag to indicate that we started the transaction here and will
      // need to end the transaction before we exit the operation.
      bTransactionStartedHere = TRUE;
      lpTaskDBHandler->bTranStarted = TRUE;
      lpTaskDBHandler->lpConnection = lpPtr;
   }

   // Retrieve the root entity(-ies).
   nRC = (*pOper)( (zLONG) zGETHNDL( lpCurrentTask ),
                   DBH_Entity | DBH_Load, (int) lControl, lpViewOD,
                   zGETPTR( lpViewOD->hFirstOD_Entity ),
                   lpView, lpQualView, &lpPtr );

   // If nRC > 0, then the root entity was loaded OK but multiple roots were
   // found and lControl = zSINGLE or the multi-root limit was reached.
   // This means that not all roots where loaded.
   // Set nRC back to 0 (indicate load was OK) and set nReturnCode = 1 (this
   // will be returned by the Activate if everything else goes OK).
   if ( nRC >= 1 )
   {
      nReturnCode = nRC;
      nRC = 0;
   }

   // If we activated some information check to see if we need to set up
   // some pessimistic locks.
   if ( nRC >= 0 && lpViewOD->nLock >= zLL_PESSIMISTIC )
   {
      zBOOL bReadOnly = (lControl & zSINGLE_FOR_UPDATE) == 0 ||
                        lpViewOD->nLock == zLL_PESSIMISTIC;

      nRC = fnCheckLocksOnTwins( lpCurrentTask, TRUE, bReadOnly, lpView,
                                 zGETPTR( lpViewOI->hRootEntityInstance ),
                                 lpViewOD );

      // If nRC >= 0 then we might need to set locks on the parent entities.
      if ( nRC >= 0 )
      {
         zBOOL bAllowRead = lpViewOD->nLock == zLL_PESSIMISTIC_WITHREAD;

         if ( bReadOnly == FALSE &&
              fnSetLocksOnTwins( lpCurrentTask, TRUE, lpView,
                                 zGETPTR( lpViewOI->hRootEntityInstance ),
                                 lpViewOI, bAllowRead ) != 0 )
         {
            nRC = zCALL_ERROR;
         }
      }
   }

   // For each of the root entities, call fnLoadChildEntities to load all of
   // their children if lower-level entities are to be loaded.
   if ( nRC >= 0 && (lControl & zACTIVATE_ROOTONLY) == 0 )
   {
      for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
            lpEntityInstance && nRC >= 0;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextTwin ) )
      {
         // Make lpEntityInstance the current instance.
         fnEstablishViewForInstance( lpView, 0, lpEntityInstance );

         nRC = fnLoadChildEntities( lpCurrentTask, lpView, lpEntityInstance,
                                    lpQualView, pOper, &lpPtr );
         if ( nRC == zDB_DEADLOCK || nRC == zMEMORY_LIMIT )
            nReturnCode = nRC;

         // If nRC is 2 then not all child entities where loaded because the
         // Activate Limit constraint was reached.
         if ( nRC == 2 )
            nReturnCode = 2;

      }  // for ( lpEntityInstance )...

   } // if ( nRC >= 0 && (lControl & zACTIVATE_ROOTONLY) == 0 )...
   else
   if ( lControl == (lControl | zACTIVATE_ROOTONLY) )
      lpViewOI->bRootOnly = TRUE;

   // If we activated some information check to see if we need to set up
   // some pessimistic locks.
   if ( nRC >= 0 && lpViewOD->nEntityLock >= zLL_PESSIMISTIC )
   {
      // Loop through all the instances and check to see if
      // the entity has locking.
      for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         LPVIEWENTITY lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
         zBOOL        bReadOnly;

         // If entity has no locking skip it.
         if ( lpViewEntity->nLock == 0 )
            continue;

         // If the instance is not the first twin then skip it.
         if ( lpEntityInstance->hPrevTwin )
            continue;

         // We're about to check the locks on the entity instances but if the
         // zSINGLE_FOR_UPDATE flag is not set or if the locking level is only
         // zLL_PESSIMISTIC then the entity instance is read-only.
         bReadOnly = (lControl & zSINGLE_FOR_UPDATE) == 0 ||
                     lpViewEntity->nLock == zLL_PESSIMISTIC;

         // Make sure the entities aren't locked.
         if ( fnCheckLocksOnTwins( lpCurrentTask, FALSE, bReadOnly, lpView,
                                   lpEntityInstance, lpViewOD ) != 0 )
         {
            nRC = zCALL_ERROR;
            break;
         }

         // If entity instances are not read-only then we need to set up locks
         // for the entities.
         if ( bReadOnly == FALSE )
         {
            zBOOL bAllowRead = lpViewEntity->nLock == zLL_PESSIMISTIC_WITHREAD;

            if ( fnSetLocksOnTwins( lpCurrentTask, FALSE, lpView,
                                    lpEntityInstance, lpViewOI,
                                    bAllowRead ) != 0 )
            {
               nRC = zCALL_ERROR;
               break;
            }
         }
      } // for...
   }

   // Check to see if we need to close the transaction.
   if ( bTransactionStartedHere )
   {
      // We're about to close the transaction so set flag.
      lpTaskDBHandler->bTranStarted = FALSE;
      lpTaskDBHandler->lpConnection = 0;

      if ( nRC >= -1 )
      {
         // Call DBHandler routine to commit transaction.
         if ( (*pOper)( (zLONG) zGETHNDL( lpCurrentTask ),
                        DBH_Object | DBH_Commit, DBH_LoadOI,
                        lpViewOD, 0, lpView, 0, &lpPtr ) != 0 )
         {
            return( zCALL_ERROR );
         }
      }
      else
      {
         // Call DBHandler routine to rollback transaction.
         (*pOper)( (zLONG) zGETHNDL( lpCurrentTask ),
                   DBH_Object | DBH_Rollback, DBH_LoadOI,
                   lpViewOD, 0, lpView, 0, &lpPtr );
         return( nRC );
      }
   }

   // At this point if:
   //    nRC = 0, nReturnCode = 1 -- 1 root loaded, mult found; children loaded
   //    nRC = 0, nReturnCode = 0 -- all roots (possibly only 1) loaded.
   //    nRC = -1                 -- No root found matching lpQual.
   //    nRC < -1                 -- Error loading entities.

   if ( nRC >= -1 )
   {
      // Before we exit, reset indicators in object instance to denote
      // that entities are not to be created/include at commit time.
      for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
            lpEntityInstance;
            lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
      {
         lpEntityInstance->u.nInd.bCreated        =
            lpEntityInstance->u.nInd.bIncluded    =
            lpEntityInstance->u.nInd.bUpdated     =
            lpEntityInstance->u.nInd.bDBHCreated  =
            lpEntityInstance->u.nInd.bDBHIncluded =
            lpEntityInstance->u.nInd.bDBHDeleted  =
            lpEntityInstance->u.nInd.bDBHExcluded =
            lpEntityInstance->u.nInd.bDBHUpdated  = 0;
      }

      lpViewOI->bUpdated = lpViewOI->bUpdatedFile = 0;

      if ( nRC == 0 )
         return( nReturnCode );
      else
         return( nRC );
   }

   return( nRC );

}  //  fnActivateObjectInstance

//=fnActivateOI_FromTextStream
zSHORT
fnActivateOI_FromTextStream( zVIEW          lpView,
                             LPFN_GETSTREAM lpfnStreamFunc,
                             zPVOID         lpvData,
                             zPLONG         plControl )
{
   LPVIEWOD          lpViewOD;
   LPVIEWOI          lpViewOI;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWATTRIB      lpViewAttrib;
   LPVIEWCSR         lpViewCsr;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPENTITYINSTANCE  lpEntityInstance;
   LPENTITYINSTANCE  lpSrcInstance;
   LPENTITYINSTANCE  lpTgtInstance;
   LPENTITYINSTANCE  lpCursorEI;    // Used to set cursors.
   LPTASK            lpTask;
   zPCHAR            pchAttr;
   zPCHAR            pchLine;
   zPLONG            pRelinkBufferTable[ 10 ] = { 0 };
   zPLONG            pRelinkBufferPtr;
   zPLONG            pRelinkBufferEnd;
   zULONG            ulLth;
   zULONG            ulLthDecoded;
   zULONG            uPos;
   zBOOL             bIgnoreEntityErrors;
   zBOOL             bIgnoreAttribErrors;
   zBOOL             bEntityIsCompressed;
   zBOOL             bOI_IsUpdated = FALSE;
   zBOOL             bSkipAttributes = FALSE;
   zBOOL             bMsgBox = TRUE;
   zCHAR             szWorkString[ 256 ];
   zLONG             lIndicators = 0, lPrevIndicators;
   zLONG             lEntityCnt = 0;
   zLONG             lLineCount = 0;
   zLONG             k;
   zSHORT            nErrorEntityLvl;
   zSHORT            nErrorEntityCnt;
   zSHORT            nErrorAttribCnt;
   zSHORT            nEOF;
   zSHORT            nLevel;
   zSHORT            nRC = 0;
#if 1  // debugging
   zSHORT            nFlag = -1;
#endif

   // The following should only be used for cursor processing.
   zLONG             lInstanceCount = 0;

   bIgnoreEntityErrors = (*plControl & zIGNORE_ENTITY_ERRORS) ? 1 : 0;
   bIgnoreAttribErrors = (*plControl & zIGNORE_ATTRIB_ERRORS) ? 1 : 0;

   nErrorEntityLvl = 0;
   nErrorEntityCnt = 0;
   nErrorAttribCnt = 0;

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );
   lpViewOD  = zGETPTR( lpViewOI->hViewOD );
   lpTask    = zGETPTR( lpView->hTask );

   // Initialize buffer pointers to indicate it hasn't been allocated yet.
   pRelinkBufferEnd = pRelinkBufferPtr = 0;

   // Process the stream
   lpViewEntityCsr = 0;
   lpEntityInstance = 0;
   while ( (nEOF = (*lpfnStreamFunc)( lpView, lpvData,
                                      &pchLine, 0, 0 )) == 1 )
   {
      lLineCount++;
         if ( pRelinkBufferPtr == pRelinkBufferEnd )
         {
            k = lEntityCnt / 160000;  // moved up from 16000 dks/don 2007.01.04

            // If we've loaded 160000 * 10 entities then bomb.
            if ( k >= 10 )
            {
               // if the relink entity pointer is at the end of the
               // space allocated, issue an error
               //  "KZOEE090 - Maximum number of entities in portable file exceeded "
               (*lpfnStreamFunc)( lpView, lpvData, 0, 0, 90 );
               nRC = zCALL_ERROR;
               break;
            }

            pRelinkBufferTable[ k ] = SysMalloc( 640000L );
            pRelinkBufferEnd = pRelinkBufferTable[ k ] + 640000 / 4;  // Space for 160000 entities ... moved up from 16000 dks/don 2007.01.04
            pRelinkBufferPtr = pRelinkBufferTable[ k ];

      }

      if ( nErrorEntityLvl )
      {
         if ( pchLine[ 0 ] == 'e' )
         {
            SysParseLine( szWorkString, zsizeof( szWorkString ), &pchLine, pchLine + 1 );
            if ( *plControl & zCOMPRESSED )
               nLevel = (zSHORT) zxtol( pchLine );
            else
               nLevel = (zSHORT) zatol( pchLine );

            if ( nLevel > nErrorEntityLvl )
               pchLine[ 0 ] = ' ';

               *pRelinkBufferPtr = 0;
               pRelinkBufferPtr++;
            lEntityCnt++;
         }
         else
         if ( pchLine[ 0 ] == 'a' )
            pchLine[ 0 ] = ' ';
      }

      if ( pchLine[ 0 ] == 'm' )  // Meta information
      {
         // Meta information is information about the OI (as opposed to the
         // info *in* the OI).
         SysParseLine( szWorkString, zsizeof( szWorkString ), &pchLine, pchLine + 1 );
         switch ( szWorkString[ 0 ] )
         {
            case 'C':
               if ( zstrcmp( szWorkString, "CONTROL" ) == 0 )
                  lpViewOI->lActivateControl = zxtol( pchLine );

               break;

            case 'E':
               if ( zstrcmp( szWorkString, "ETAG" ) == 0 )
                  lpEntityInstance->lTag = zxtol( pchLine );
               else
               if ( zstrcmp( szWorkString, "EKEY" ) == 0 )
                  lpEntityInstance->ulKey = (zULONG) zxtol( pchLine );

               break;

            case 'O':
               if ( zstrcmp( szWorkString, "OITAG" ) == 0 )
                  lpViewOI->lTag = zxtol( pchLine );
               else
               if ( zstrcmp( szWorkString, "OIFLAGS" ) == 0 )
               {
                  zULONG uFlags = zxtol( pchLine );

                  // If zOI_ISLOCKED flag is set then the OI has pessimistic
                  // locks set.
                  if ( uFlags & zOI_ISLOCKED )
                     lpViewOI->bIsLocked = TRUE;

                  if ( uFlags & zOI_READONLY )
                     lpView->bReadOnly = TRUE;
               }

               break;
         }
      }
      else
      if ( pchLine[ 0 ] == 'e' )  // Entity type
      {
         SysParseLine( szWorkString, zsizeof( szWorkString ), &pchLine, pchLine + 1 );
         if ( *plControl & zCOMPRESSED )
            nLevel = (zSHORT) zxtol( pchLine );
         else
            nLevel = (zSHORT) zatol( pchLine );

         if ( *plControl & zINCREMENTAL )
         {
            while ( pchLine[ 0 ] != ',' )
               pchLine++;

            pchLine++;
            lPrevIndicators = lIndicators;

            if ( *plControl & zCOMPRESSED )
               lIndicators = (zLONG) zxtob( pchLine );
            else
               lIndicators = (zLONG) zatob( pchLine ); /* HH, 14.10.96 */
         }

         for ( ; ; )  // Validate view entity received
         {
            zSHORT nHierNbr;

            lpViewEntity    = zGETPTR( lpViewOD->hFirstOD_Entity );
            lpViewEntityCsr = zGETPTR( lpViewCsr->hRootViewEntityCsr );

            // If the root cursor is not the first cursor, skip ViewEntities
            // until we get to the entity matching the root cursor
            if ( lpViewEntityCsr != zGETPTR( lpViewCsr->hFirstOD_EntityCsr ) )
            {
               LPVIEWENTITYCSR lpSearchViewEntityCsr;

               lpSearchViewEntityCsr =
                                    zGETPTR( lpViewCsr->hFirstOD_EntityCsr );

               while ( lpSearchViewEntityCsr != lpViewEntityCsr )
               {
                  lpViewEntity = zGETPTR( lpViewEntity->hNextHier );
                  lpSearchViewEntityCsr++;
               }
            }

            if ( *plControl & zCOMPRESSED )
               nHierNbr = (zSHORT) zxtol( szWorkString );

            while ( lpViewEntityCsr )
            {
               if ( *plControl & zCOMPRESSED )
               {
                  if ( lpViewEntity->nHierNbr == nHierNbr )
                     break;
               }
               else
               if ( zstrcmp( lpViewEntity->szName, szWorkString ) == 0 )
                  break;

               lpViewEntity    = zGETPTR( lpViewEntity->hNextHier );
               lpViewEntityCsr = zGETPTR( lpViewEntityCsr->hNextHier );
            }

            if ( lpViewEntityCsr == 0 )
            {
               // OK, No cursor was found in the current view, if there are
               // outstanding subobjects, do a reset and try again to find
               // the entity
               if ( lpViewCsr->hFirstViewSubobject )
                  fnResetViewFromSubobject( lpView );
               else
               {
                  lpViewEntity = 0;
                  break;  // Ouch, Entity does not exist, give up
               }
            }
            else
            {
               // We've found a cursor which matches the entity type
               // now check to see if a SetViewToSubobject or a reset is
               // needed to create the entity at the appropriate level
               if ( lpViewEntityCsr->nLevel == nLevel )
               {
                  break;
               }
               else
               if ( lpViewEntityCsr->nLevel > nLevel )
               {
                  if ( lpViewCsr->hFirstViewSubobject == 0 )
                     break;

                  while ( lpViewEntityCsr->nLevel > nLevel &&
                          lpViewCsr->hFirstViewSubobject )
                  {
                     fnResetViewFromSubobject( lpView );
                  }
               }
               else
               {
                  // The view entity csr level is < the entity level.
                  // In this case, the current (last) instance must be the
                  // parent of the instance we are about to create and
                  // it must have recursive behaviour. Otherwise we will
                  // drop out and issue a level error
                  if ( lpEntityInstance )
                  {
                     LPVIEWENTITY lpWkViewEntity =
                                 zGETPTR( lpEntityInstance->hViewEntity );

                     if ( lpWkViewEntity->bRecursive )
                        fnSetViewToSubobject( lpView, lpWkViewEntity, 0 );
                  }

                  break;
               }
            }  // if ( lpViewEntityCsr == 0 )...else...
         }  // for ( ; ; )...

         bSkipAttributes = FALSE;

         if ( lpViewEntity == 0 )
         {
            // Let's at least trace it out.
            TraceLineS( "(WARNING) Couldn't find entity ", szWorkString );
            TraceLineS( "(WARNING) in LOD ", lpViewOD->szName );

            if ( bIgnoreEntityErrors == FALSE || nLevel == 1 )
            {
               //  "KZOEE074 - Invalid Entity name on line "
               (*lpfnStreamFunc)( lpView, lpvData, (zPPCHAR) szWorkString, 0, 74 );
               nRC = zCALL_ERROR;
               break;
            }

            nErrorEntityLvl = nLevel;
            nErrorEntityCnt++;
         }
         else
         if ( *plControl & zACTIVATE_ROOTONLY && nLevel > 1 )
         {
            // Current entity is not a root and user indicated that she only
            // wants roots.  Set flag to indicate we want to skip setting
            // attribute values.
            bSkipAttributes = TRUE;
            continue;
         }
         else
         if ( lpViewEntityCsr->nLevel != nLevel )
         {
            // if the view cursor level does not equal the entity
            // level coming in, issue an error
            //  "KZOEE075 - Invalid Entity level on line "
            (*lpfnStreamFunc)( lpView, lpvData, (zPPCHAR) szWorkString, 0, 75 );
            nRC = zCALL_ERROR;
            break;
         }
         else
         {
            if ( nLevel == 1 && lpViewEntityCsr->hEntityInstance &&
                 lpViewOI->bMultipleRootLevels == FALSE )
            {
               // Doing this stuff means that there are multiple level 1
               // roots in the the file, but that the user has requested
               // activation of the the instance with zSINGLE rather than
               // zMULTIPLE.  We will act like the EOF condition has
               // occurred and set return code to indicate that we found
               // multiple roots.
               nRC = 1;
               bSkipAttributes = TRUE;
               continue;
            }
            else
            {
               nRC = fnCreateEntity( lpView, lpViewEntity,
                                     lpViewEntityCsr, zPOS_AFTER, 0 );
               if ( nRC )
                  break;

               nErrorEntityLvl = 0;
            }
         }

         // The current entity is compressed if:
         // o  The portable file is stored in compressed format.
         // o  The max size of all the attributes for the entity is smaller
         //    then the buffer we set up to hold all the attribute values.
         bEntityIsCompressed = (*plControl & zCOMPRESSED) &&
                               (lpViewEntity->ulMaxLth < zENTITY_BUFFER_SIZE);

         if ( nErrorEntityLvl == 0 )
         {
            // if this is not the first instance, set the indicators on
            // the previous instance. NOTE this is done after all updates
            // so the update flag can be reset!
            if ( lpEntityInstance )
            {
               if ( *plControl & zINCREMENTAL )
               {
                  lpEntityInstance->u.nIndicators = lPrevIndicators;
                  lpEntityInstance->u.nInd.bPrevVersion = FALSE;

                  // A hack to make sure that a delete/excluded entity is
                  // flagged as hidden.  This tries to fix a bug.
                  if ( lpEntityInstance->u.nInd.bDeleted  ||
                       lpEntityInstance->u.nInd.bExcluded )
                  {
                     lpEntityInstance->u.nInd.bHidden = TRUE;
                  }

                  if ( lpEntityInstance->u.nInd.bCreated  ||
                       lpEntityInstance->u.nInd.bDeleted  ||
                       lpEntityInstance->u.nInd.bIncluded ||
                       lpEntityInstance->u.nInd.bExcluded ||
                       lpEntityInstance->u.nInd.bUpdated )
                  {
                     bOI_IsUpdated = TRUE;
                  }
               }
               else
                  lpEntityInstance->u.nInd.bUpdated = FALSE;
            }

            // Set lpEntityInstance to instance just created.
            lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
               *pRelinkBufferPtr = (zLONG) lpEntityInstance;
            lEntityCnt++;

#if 0  // debugging
            if ( nFlag )
            {
               if ( nFlag < 0 )
               {
                  zCHAR szFile[ 256 ];

                  nFlag = 0;  // we only want to check this once
                  SysReadZeidonIni( -1, "[Workstation]", "DebugRelink", szFile, zsizeof( szFile ) );
                  if ( szFile[ 0 ] )
                  {
                     FileDataRecord  *pActFileData = (FileDataRecord *) lpvData;
                     if ( zstrstr( pActFileData->pchFileName, szFile ) )
                        nFlag = 1;
                  }
               }
               if ( nFlag > 0 )
               {
                  LPVIEWENTITY lpEntityTemp = zGETPTR( lpEntityInstance->hViewEntity );
                  TraceLine( "Setting Relink Ptr: %d   at Entity #: %d   for EI: %d   Entity: %s", (zLONG) pRelinkBufferPtr, lEntityCnt, (zLONG) lpEntityInstance, lpEntityTemp->szName );
               }
            }
#endif
            pRelinkBufferPtr++;
            lpEntityInstance->u.nInd.bCreated = TRUE;
            lpEntityInstance->u.nInd.bPrevVersion = FALSE;
         }
         else
         {
               *pRelinkBufferPtr = 0;
               pRelinkBufferPtr++;
            lEntityCnt++;

            // If we're ignoring errors then set the error code back to 0
            // so that we can keep processing entities.
            if ( bIgnoreEntityErrors )
               nErrorEntityLvl = 0;
         }
      }  // if ( pchLine[ 0 ] == 'e' )...
      else
      if ( pchLine[ 0 ] == 'a' && lpViewEntity )  // Attrib and entity exists
      {
         LPATTRIBFLAGS     lpAttribFlags;
         AttribFlagsRecord AttribFlags;

         if ( bEntityIsCompressed && pchLine[ 1 ] == ' ' )
         {
            zPCHAR pchStart;

            // The entity is stored in a compressed format.  The line we just
            // read contains an 'a' followed by the length of all the attribute
            // data in hex.
            ulLth = zxtol( pchLine + 2 );
            nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, ulLth, 0 );
            if ( nEOF != 1 )
            {
               nRC = zCALL_ERROR;
               break;
            }

            pchStart = pchLine;

            // If bSkipAttributes is TRUE, then we need to skip over these attributes.
            if ( bSkipAttributes )
               continue;

            // pchLine should now point to a buffer containing all the
            // attribute values.  Copy each value to the entity.
            for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
                  lpViewAttrib;
                  lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
            {
               if ( lpViewAttrib->szDerivedOper[ 0 ] &&
                    lpViewAttrib->bPersist == FALSE )
               {
                  continue;
               }

               if ( lpViewAttrib->cType == zTYPE_BLOB )
                  continue;

               if ( *pchLine == 0 )
               {
                  // Attribute value is null.  Skip over 0.
                  pchLine++;

                  // Make sure that a record (data stick exists).
                  if ( (lpViewAttrib->bPersist &&
                        lpEntityInstance->hPersistRecord == 0) ||
                       (lpViewAttrib->bPersist == FALSE &&
                        lpEntityInstance->hNonPersistRecord == 0) )
                  {
                     // Set a null value so that the record gets created.
                     if ( fnSetAttributeFromString( lpView, lpViewEntityCsr,
                                                    lpViewAttrib,
                                                    "", 0 ) != 0 )
                     {
                        nRC = zCALL_ERROR;
                        break;
                     }
                  }
               }
               else
               {
                  if ( lpViewAttrib->cType == zTYPE_INTEGER )
                  {
                     zLONG l;

                     l = zxtol( pchLine );
                     if ( fnSetAttributeFromInteger( lpView, lpViewEntityCsr,
                                                     lpViewAttrib, l ) != 0 )
                     {
                        nRC = zCALL_ERROR;
                        break;
                     }
                  }
                  else
                  {
                     if ( fnSetAttributeFromString( lpView, lpViewEntityCsr,
                                                    lpViewAttrib,
                                                    pchLine, 0 ) != 0 )
                     {
                        nRC = zCALL_ERROR;
                        break;
                     }
                  }

                  pchLine += zstrlen( pchLine ) + 1;
               }

               // Now set the attribute flags.
               if ( (*plControl & zINCREMENTAL) &&
                    (*plControl & zATTRIBFLAGS) )
               {
                  lpAttribFlags = fnGetAttribFlagsPtr( lpEntityInstance,
                                                       lpViewAttrib );
                  lpAttribFlags->u.uFlags = zxtob( pchLine );

                  pchLine += zstrlen( pchLine ) + 1;
               }
            }

            if ( nRC == zCALL_ERROR )
               break;

            // Continue with the next line in the file.
            continue;

         } // if ( bEntityIsCompressed )...

         // If we get here, then bEntityIsCompressed is FALSE.  But it's still
         // possible that the OI is stored in a compressed format--it's just
         // that the attributes couldn't be squeezed into one line.  If the OI
         // is compressed, then the attribute names are stored as the XVA
         // tokens instead of the names.

         // First get the attribute name/number into szWorkString.  The end of
         // the name/number is indicated when we find a space or comma.
         for ( k = 0, pchLine++;
               pchLine[ k ] && pchLine[ k ] != ' ' && pchLine[ k ] != ',';
               k++ )
         {
            szWorkString[ k ] = pchLine[ k ];
         }

         // Terminate szWorkString.
         szWorkString[ k ] = 0;
      // if ( zstrcmp( szWorkString, "ZKey" ) == 0 )
      //    TraceLineI( pchLine, lLineCount );

         // If the next char in the line is a comma then we also need to
         // retrieve the attribute flags.
         if ( pchLine[ k ] == ',' )
         {
            zCHAR  szAttribFlags[ 12 ];
            zSHORT j;

            k++;  // Skip over the ','.
            j = 0;
            while ( pchLine[ k ] && pchLine[ k ] != ' ' )
               szAttribFlags[ j++ ] = pchLine[ k++ ];

            szAttribFlags[ j ] = 0;

            AttribFlags.u.uFlags = zxtob( szAttribFlags );
         }
         else
         {
            // If flags aren't specified then they are assumed 0 *unless* this
            // OI wasn't stored with attrib flags (this means it was stored
            // with a pre-10a version).  In this case we have to assume that
            // every attribute has been changed.
            AttribFlags.u.uFlags = 0; // Turn off all flags.
            if ( (*plControl & zATTRIBFLAGS ) == 0 )
            {
               // No attrib flags--turn on 'changed' bit.
               AttribFlags.u.bFlags.bUpdated = TRUE;
            }
         }

         if ( *plControl & zCOMPRESSED )
         {
            zLONG lXVATok;

            // Point pchLine to first char of attribute value if there is
            // more info after the attribute name.
            if ( pchLine[ k ] )
               pchLine += k + 1;

            lXVATok = zxtol( szWorkString );

            // Look for the attribute that matches the XVA token.
            for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
                  lpViewAttrib && lpViewAttrib->lXVAAttTok != lXVATok;
                  lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
            {
               // nothing needs to be done here
            }
         }
         else
         {
            // Point pchLine to first char of attribute value if there is
            // more info after the attribute name.

            // Skip over any blanks that filled out the name.
            if ( pchLine[ k ] )
            {
               if ( k < 9 )
                  pchLine += 10;
               else
                  pchLine += k + 1;
            }

            // Look for the attribute that matches the attribute name.
            for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
                  lpViewAttrib;
                  lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
            {
               if ( zstrcmpi( lpViewAttrib->szName, szWorkString ) == 0 )
                  break;
            }
         }

         // If entity not found return error.
         if ( lpViewAttrib == 0 )
         {
            if ( bIgnoreAttribErrors == FALSE )
            {
               zCHAR sz[ 400 ];

               strcpy_s( sz, zsizeof( sz ), lpViewEntity->szName );
               strcat_s( sz, zsizeof( sz ), "." );
               strcat_s( sz, zsizeof( sz ), szWorkString );

               //  "KZOEE104 - Invalid Attribute name for Entity"
               (*lpfnStreamFunc)( lpView, lpvData, (zPPCHAR) sz, 0, 104 );

               // DGC 10-4-95
               // We no longer consider this an error worth bombing out.
               // nRC = zCALL_ERROR;
               // break;
            }

            nErrorAttribCnt++;
         }
         else
         if ( lpViewAttrib->cType == zTYPE_BLOB ||
              (lpViewAttrib->cType == zTYPE_STRING &&
               *pchLine == zSTRING_STORED_AS_BLOB) )
         {
            // If a string is stored with special characters (e.g. '\n') then
            // is is stored as a blob.  This is indicated if the first char
            // in pchLine is zSTRING_STORED_AS_BLOB.
            if ( lpViewAttrib->cType == zTYPE_STRING &&
                 *pchLine == zSTRING_STORED_AS_BLOB )
            {
               pchLine++;  // Point pchLine past zSTRING_STORED_AS_BLOB.
               ulLth = zatol( pchLine );
               if ( ulLth )
                  nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, ulLth, 0 );
            }
            else // must be blob, so need to check for encoding
            {
               ulLthDecoded = 0;
               if ( *pchLine == zBLOB_STORED_ENCODED )
               {
                  pchLine++;  // point pchLine past zBLOB_STORED_ENCODED
                  ulLth = zatol( pchLine );
                  if ( ulLth )
                  {
                     // If are ignoring attributes, just skip the encoded lines.
                     if ( bSkipAttributes )
                     {
                        nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, 0, 0 );
                        while ( TRUE )
                        {
                           if ( *pchLine == 0x60 )  // terminating "`" line
                              break;

                           nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, 0, 0 );
                        }
                     }
                     else
                     {
                        // Init the blob attribute to have a buffer for decoding.
                        if ( fnSetAttributeFromBlob( lpView, lpViewEntityCsr,
                                                     lpViewAttrib,
                                                     0, ulLth ) != 0 )
                        {
                           nRC = zCALL_ERROR;
                           break;
                        }

                        fnGetAddrForAttribute( &pchAttr, lpView, lpViewEntityCsr, 0,
                                               lpViewAttrib );

                        // Now decode the blob lines until the 'zero length' line is found.
                        uPos = 0;
                        nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, 0, 0 );
                        while ( TRUE )
                        {
                           nRC = UUDECODE_NextLineToBuffer( pchLine, pchAttr, ulLth, &uPos );
                           //TraceLineS( "Decoded Line: ", pchLine);
                           if ( nRC < 0 )
                           {
                              TraceLineI( "Error from UUDECODE_NextLineToBuffer: ", nRC );
                              nRC = zCALL_ERROR;
                              break;
                           }

                           if ( nRC == 0 )
                              break;

                           ulLthDecoded = ulLthDecoded + nRC;
                           nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, 0, 0 );
                        }

                        if ( ulLthDecoded != ulLth )
                        {
                           TraceLineI( "UUDECODE length invalid: ", ulLthDecoded );
                           nRC = zCALL_ERROR;
                           break;
                        }
                     }
                  }
               }
               else
               {
                  ulLth = zatol( pchLine );
                  if ( ulLth )
                     nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, ulLth, 0 );
               }
            }

         // ulLth = zatol( pchLine );
            if ( ulLth )
            {
            // nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, ulLth, 0 );
               if ( nEOF != 1 )
               {
                  nRC = zCALL_ERROR;
                  break;
               }

               lLineCount++;

               // If bSkipAttributes is TRUE, then we need to skip over these attributes.
               if ( bSkipAttributes )
                  continue;

               if ( lpViewAttrib->cType == zTYPE_BLOB )
               {
                  if ( ulLthDecoded > 0 )
                  {
                     // Do nothing since it has been stored during decode
                  }
                  else
                  {
                     if ( fnSetAttributeFromBlob( lpView, lpViewEntityCsr,
                                                  lpViewAttrib,
                                                  pchLine, ulLth ) != 0 )
                     {
                        nRC = zCALL_ERROR;
                        break;
                     }
                  }
               }
               else
               {
                  // PAS 03-09-2001 - x00 is no longer put at the end of
                  //                  a string that was stored as a BLOB
                  //                  (with length), so always terminate
                  pchLine[ ulLth - 1 ] = 0;
                  if ( fnSetAttributeFromString( lpView, lpViewEntityCsr,
                                                 lpViewAttrib,
                                                 pchLine, 0 ) != 0 )
                  {
                     nRC = zCALL_ERROR;
                     break;
                  }
               }
            }
            else
               // If bSkipAttributes is TRUE, then we need to skip over these attributes.
               if ( bSkipAttributes )
                  continue;

            // Now set the attribute flags.
            lpAttribFlags = fnGetAttribFlagsPtr( zGETPTR( lpViewEntityCsr->hEntityInstance ),
                                                 lpViewAttrib );
            lpAttribFlags->u.uFlags = AttribFlags.u.uFlags;
         }
         else
         {
            // If bSkipAttributes is TRUE, then we need to skip over these attributes.
            if ( bSkipAttributes )
               continue;

            if ( *plControl & zCOMPRESSED &&
                 lpViewAttrib->cType == zTYPE_INTEGER )
            {
               zLONG  l;

               if ( *pchLine == '*' )
               {
                  // Integer attribute is NULL.
                  fnSetAttributeFromString( lpView, lpViewEntityCsr,
                                            lpViewAttrib, "", 0 );
               }
               else
               {
                  if ( *pchLine == '-' )
                     l = zxtol( pchLine + 1 ) * -1;
                  else
                     l = zxtol( pchLine );

                  if ( fnSetAttributeFromInteger( lpView, lpViewEntityCsr,
                                                  lpViewAttrib, l ) != 0 )
                  {
                     nRC = zCALL_ERROR;
                     break;
                  }
               }
            }
            else
            {
               if ( fnSetAttributeFromString( lpView, lpViewEntityCsr,
                                              lpViewAttrib, pchLine, 0 ) != 0 )
               {
                  nRC = zCALL_ERROR;
                  break;
               }
            }

            // Now set the attribute flags.
            lpAttribFlags = fnGetAttribFlagsPtr( zGETPTR( lpViewEntityCsr->hEntityInstance ),
                                                 lpViewAttrib );
            lpAttribFlags->u.uFlags = AttribFlags.u.uFlags;
         }

         nRC = 0;  // Everything OK so far...

      }  // ...else...if ( pchLine[ 0 ] == 'a' && lpViewEntity )...
      else
      if ( pchLine[ 0 ] == 'i' )
      {
         zLONG  lLinkTgt;
         zLONG  lLinkSrc;

         // If we are reading root only then don't bother with the link cards.
         if ( *plControl & zACTIVATE_ROOTONLY )
            continue;

         SysParseLine( szWorkString, zsizeof( szWorkString ), &pchLine, pchLine + 1 );
         if ( *plControl & zCOMPRESSED )
         {
            lLinkTgt = zxtol( szWorkString );
            lLinkSrc = zxtol( pchLine );
         }
         else
         {
            lLinkTgt = zatol( szWorkString );
            lLinkSrc = zatol( pchLine );
         }

         // Change to attempt to fix relink errors - dks 2015.12.29
         k = lLinkSrc / 160000;  // moved up from 16000 dks/don 2007.01.04
         lpSrcInstance = (LPENTITYINSTANCE) *(pRelinkBufferTable[ k ] + lLinkSrc % 160000);  // moved up from 16000 dks/don 2007.01.04
         k = lLinkTgt / 160000;  // moved up from 16000 dks/don 2007.01.04
         lpTgtInstance = (LPENTITYINSTANCE) *(pRelinkBufferTable[ k ] + lLinkTgt % 160000);  // moved up from 16000 dks/don 2007.01.04
         if ( lpTgtInstance && lpSrcInstance )
         {
            LPVIEWENTITY lpTgtViewEntity;
            LPENTITYINSTANCE  lpSrcInstanceHld = lpSrcInstance;
            zLONG  lLinkSrcHld = lLinkSrc;

            lpTgtViewEntity = zGETPTR( lpTgtInstance->hViewEntity );
            while ( lLinkSrc >= 0 )
            {
               lpViewEntity = zGETPTR( lpSrcInstance->hViewEntity );
#if 0 // debugging
               if ( nFlag > 0 )
                  TraceLine( "Checking Relink (OD: %s) - TgtPtr: %d.%d   SrcPtr: %d.%d   at Index: %d   for Entity  Tgt: %s   Src: %s",
                             lpViewOD->szName, lLinkTgt, (zLONG) lpTgtInstance, lLinkSrc, (zLONG) lpSrcInstance, k, lpTgtViewEntity->szName, lpViewEntity->szName );
#endif
               if ( lpTgtViewEntity->lEREntTok == lpViewEntity->lEREntTok )
                  break;

               lLinkSrc--;
               if ( lLinkSrc < 0 )  // we couldn't fix the error
               {
                  lpSrcInstance = lpSrcInstanceHld;
                  lLinkSrc = lLinkSrcHld;
                  lpViewEntity = zGETPTR( lpSrcInstance->hViewEntity );
                  break;
               }
               else
               {
                  k = lLinkSrc / 160000;  // moved up from 16000 dks/don 2007.01.04
                  lpSrcInstance = (LPENTITYINSTANCE) *(pRelinkBufferTable[ k ] + lLinkSrc % 160000);  // moved up from 16000 dks/don 2007.01.04
               }
            }
            if ( lpTgtViewEntity->lEREntTok != lpViewEntity->lEREntTok )
            {
               FileDataRecord  *pActFileData = (FileDataRecord *) lpvData;

               TraceLine( "(oi) Relink Error (OD: %s) - Tgt View Entity: %s Token: %d  View Entity: %s Token = %d  TgtPtr: %d   SrcPtr: %d   at Index: %d   File: %s",
                          lpViewOD->szName, lpTgtViewEntity->szName, lpTgtViewEntity->lEREntTok,
                          lpViewEntity->szName, lpViewEntity->lEREntTok, lLinkTgt, lLinkSrc, k, pActFileData->pchFileName );
               if ( bMsgBox )
               {
                  bMsgBox = FALSE;
                  SysMessageBox( lpView, szlOE_SystemError, "ER Tokens don't match for linked entities!", 1 );
               }
            }
            else
            {
               lpTgtInstance->hPersistRecord = lpSrcInstance->hPersistRecord;
               if ( lpSrcInstance->hNextLinked )
                  lpTgtInstance->hNextLinked = lpSrcInstance->hNextLinked;
               else
                  lpTgtInstance->hNextLinked = zGETHNDL( lpSrcInstance );

               lpSrcInstance->hNextLinked = zGETHNDL( lpTgtInstance );
            }
         }
         else
         {
            TraceLineS( "(oi) Failed entity linking", "" );

            TraceLineI( "(oi) Link Src # = ", lLinkSrc );
            if ( lpSrcInstance )
            {
               lpViewEntity = zGETPTR( lpSrcInstance->hViewEntity );
               TraceLineS( "(oi) Source Entity = ", lpViewEntity->szName );
            }

            TraceLineI( "(oi) Link Tgt # = ", lLinkTgt );
            if ( lpTgtInstance )
            {
               lpViewEntity = zGETPTR( lpTgtInstance->hViewEntity );
               TraceLineS( "(oi) Target Entity = ", lpViewEntity->szName );
            }
         }

      }  // ...else...if ( pchLine[ 0 ] == 'i' )
      else
      if ( pchLine[ 0 ] == 'c' )
      {
         zSHORT nHierNbr;
         zLONG  l;

         // First make sure that the last created entity instance has its indicators set.
         if ( lpEntityInstance )
         {
            if ( *plControl & zINCREMENTAL )
            {
               lpEntityInstance->u.nIndicators = lIndicators;
               lpEntityInstance->u.nInd.bPrevVersion = FALSE;

               // A hack to make sure that a delete/excluded entity is
               // flagged as hidden.  This tries to fix a bug.
               if ( lpEntityInstance->u.nInd.bDeleted  ||
                    lpEntityInstance->u.nInd.bExcluded )
               {
                  lpEntityInstance->u.nInd.bHidden = TRUE;
               }

               if ( lpEntityInstance->u.nInd.bCreated  ||
                    lpEntityInstance->u.nInd.bDeleted  ||
                    lpEntityInstance->u.nInd.bIncluded ||
                    lpEntityInstance->u.nInd.bExcluded ||
                    lpEntityInstance->u.nInd.bUpdated )
               {
                  bOI_IsUpdated = TRUE;
               }
            }
            else
               lpEntityInstance->u.nInd.bUpdated = FALSE;

            // Set lpEntityInstance to 0 to indicate that the indicators for
            // the last entity instance has been set.
            lpEntityInstance = 0;
         }

         // Cursor positions are saved in cursor records.  A cursor record
         // looks like:
         //    cEnt-hier-nbr, absolute-instance-count
         // For example, the cursor record for the root might look like:
         //    c1, 1
         // Numbers are stored in hex format.

         // If lInstanceCount is 0, then we need to set up some stuff.
         if ( lInstanceCount == 0 )
         {
            LPVIEWCSR lpFirstViewCsr = zGETPTR( lpViewOI->hFirstViewCsr );

            // Indicate that cursor positions have been loaded.
            *plControl = *plControl | zSAVE_CURSORS;

            // Initialize all entity cursors to be NULL.
            for ( lpViewEntityCsr = zGETPTR( lpFirstViewCsr->hFirstOD_EntityCsr );
                  lpViewEntityCsr;
                  lpViewEntityCsr = zGETPTR( lpViewEntityCsr->hNextHier ) )
            {
               lpViewEntityCsr->hEntityInstance = 0;
            }

            lpViewEntityCsr = zGETPTR( lpFirstViewCsr->hFirstOD_EntityCsr );
            lpCursorEI      = zGETPTR( lpViewOI->hRootEntityInstance );
            lInstanceCount  = 1;
         }

         // Get entity hier number and absolute instance position from record.
         SysParseLine( szWorkString, zsizeof( szWorkString ), &pchLine, pchLine + 1 );
         nHierNbr = (zSHORT) zxtol( szWorkString );
         l = zxtol( pchLine );

         // Entity cursors that are NULL do not have a cursor record.  If the
         // hier nbr read from the record is greater than the "current"
         // entity cursor, then at least one cursor is NULL.
         while ( lpViewEntityCsr->nHierNbr < nHierNbr )
            lpViewEntityCsr = zGETPTR( lpViewEntityCsr->hNextHier );

         if ( l == 0 )
         {
            lpViewEntityCsr->hEntityInstance = UNSET_CSR;
         // if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR )
         //    SysMessageBox( 0, "fnActivateOI_FromStream", "UNSET_CSR", -1 );
         }
         else
         {
            // Look for the entity instance that has the absolute position l.
            while ( lInstanceCount < l )
            {
               lpCursorEI = zGETPTR( lpCursorEI->hNextHier );
               lInstanceCount++;
            }

            if ( lpViewEntityCsr->hViewEntity == lpCursorEI->hViewEntity )
            {
               lpViewEntityCsr->hEntityInstance = zGETHNDL( lpCursorEI );
            // if ( lpViewEntityCsr->hEntityInstance == UNSET_CSR )
            //    SysMessageBox( 0, "fnActivateOI_FromStream2", "UNSET_CSR", -1 );
            }
            else
            {
               LPVIEWENTITY lpWk = zGETPTR( lpViewEntityCsr->hViewEntity );

               TraceLineS( "(oi) Entity type mismatch during cursor restoration"
                           " for entity ", lpWk->szName );
            }
         }

         lpViewEntityCsr = zGETPTR( lpViewEntityCsr->hNextHier );

      }  // ...else...if ( pchLine[ 0 ] == 'c' )
      else
      if ( zstrncmp( pchLine, "ZEND", 4 ) == 0 )
      {
         // "ZEND" means we got to the end of the current OI so break out
         // of loop.
         nRC = 0;
         break;
      }

   } // while ( (nEOF = (*lpfnStreamFunc)( ... )) == 1 )

      for ( lEntityCnt = 0; pRelinkBufferTable[ lEntityCnt ]; lEntityCnt++ )
         SysFree( pRelinkBufferTable[ lEntityCnt ] );

   if ( nEOF == zCALL_ERROR )
      nRC = zCALL_ERROR;

   // Mark the final instance indicators after updating all of the attributes.
   if ( nRC >= 0 )
   {
      if ( lpEntityInstance )
      {
         if ( *plControl & zINCREMENTAL )
         {
            lpEntityInstance->u.nIndicators = lIndicators;
            lpEntityInstance->u.nInd.bPrevVersion = FALSE;

            if ( lpEntityInstance->u.nInd.bCreated  ||
                 lpEntityInstance->u.nInd.bDeleted  ||
                 lpEntityInstance->u.nInd.bIncluded ||
                 lpEntityInstance->u.nInd.bExcluded ||
                 lpEntityInstance->u.nInd.bUpdated )
            {
               bOI_IsUpdated = TRUE;
            }
         }
         else
            lpEntityInstance->u.nInd.bUpdated = FALSE;
      }

      // Check if OI is updated.
      lpViewOI->bUpdated     = bOI_IsUpdated;
      lpViewOI->bUpdatedFile = FALSE;
   }

   return( nRC );

} // fnActivateOI_FromTextStream

//./ ADD NAME=SfActivateOI_FromStream
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SfActivateOI_FromStream
//
//  PURPOSE:    To activate an Object instance from a ASCII stream and
//              return a view to the object instance
//
//  PARAMETERS: pvReturnView  - View returned to instance activated
//              cpcViewOD_Name - Name of the view object.  If 0, the
//                              returned view is for the same object as
//                              the initial view(?).
//              lpAppQualView - Used to qualify the application in which
//                              to look for the object.  If the view
//                              passed is a subtask view, then the
//                              application that is used is the
//                              application tied to the subtask.
//                              Otherwise, the application for the view
//                              object associated with the passed view
//                              is used.
//              lControl      - Controls certain aspects of the file
//                              loaded.
//                            zSINGLE   - (default) only one entity at the
//                                        root level.
//                            zMULTIPLE - multiple entities at the root
//                                        level
//                            zLEVEL_APPLICATION - created view is tied
//                                        to the application task,
//                                        rather than the active task.
//                            zLEVEL_SYSTEM   - created view is tied
//                                        with the system task,
//                                        rather than the active task.
//                            zLEVEL_SAME - created view is tied to the
//                                        same task as lpAppQualView.
//                                        Note: specifying this option
//                                        requires that lpAppQualView be
//                                        be specified and that it not be
//                                        a subtask view.
//                            zNOI_OKAY - when set, if the file could not
//                                        be found, no error message is
//                                        issued, just return code set.
//                            zREADONLY - Marks the View and the Instance
//                                        as read only.  Any view created
//                                        from this view will also be
//                                        marked as read only.
//                            zIGNORE_ERRORS - Loads what info it can if
//                                        the file is ASCII
//              lpfnStreamFunc - Stream reader function.  Called by Core to
//                               read data from the stream.
//              lpvData        - Data pointer that is passed throught to
//                               the stream reader function.
//
//  RETURNS:   -1 - zNOI_OKAY was specified and the file could not be
//                  loaded into the Object Instance; pvReturnView points
//                  to an empty object instance.
//              0 - Object instance activated, single root found
//              1 - Object instance activated, multiple roots found.  If
//                  zSINGLE was specified, only the first was activated.
//    zCALL_ERROR - Error Activating object instance
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 6
zSHORT OPERATION
SfActivateOI_FromStream( zPVIEW         pvReturnView,
                         zCPCHAR        cpcViewOD_Name,
                         zVIEW          lpAppQualView,
                         zLONG          lControl,
                         LPFN_GETSTREAM lpfnStreamFunc,
                         zPVOID         lpvData )
{
   LPTASK            lpCurrentTask;
   LPTASK            lpOwningTask;
   LPVIEWCSR         lpViewCsr;
   LPVIEWOI          lpViewOI;
   LPVIEWOD          lpViewOD;
   zVIEW             lpView;
   zVIEW             vOrigView = 0;
   zVIEW             vQualView = 0;
   zPCHAR            pchLine;
   zLONG             lTickCount;
   zBOOL             bContainsOptimisticOIs = FALSE;
   zSHORT            nEOF;
   zSHORT            nRC;

   if ( AnchorBlock->TraceFlags.bOI_Times )
      lTickCount = SysGetTickCount( );

   // Init in case of error.
   *pvReturnView = 0;

   // If task not active or disabled, return zCALL_ERROR.
   lpCurrentTask = zGETPTR( lpAppQualView->hTask );
   if ( lpCurrentTask == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
      lpOwningTask = zGETPTR( AnchorBlock->hMainTask );
   else
      lpOwningTask = lpCurrentTask;

   if ( lControl & zACTIVATE_SYSTEM )
   {
      if ( (nRC = fnDeclareView( pvReturnView, lpOwningTask,
                                 lpAppQualView, cpcViewOD_Name, 1 )) != 0 )
      {
      // fnOperationReturn( iSfActivateSysOI_FromFile, lpCurrentTask, 0 );
         return( nRC );
      }

#if 0
      if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
      {
         zSHORT nScope = (lControl & zLEVEL_APPLICATION) ?
                                     zLEVEL_APPLICATION : zLEVEL_SYSTEM;
         if ( (nRC = SfTransferView( *pvReturnView, lpAppQualView,
                                     nScope )) != 0 )
         {
            return( nRC );
         }
      }
#endif
   }
   else
   {
      if ( (nRC = fnDeclareView( pvReturnView, lpOwningTask,
                                 lpAppQualView, cpcViewOD_Name, 0 )) != 0 )
      {
         return( nRC );
      }

#if 0
      if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
      {
         zSHORT nScope = (lControl & zLEVEL_APPLICATION) ?
                                     zLEVEL_APPLICATION : zLEVEL_SYSTEM;
         if ( (nRC = SfTransferView( *pvReturnView, lpAppQualView, nScope )) != 0 )
            return( nRC );
      }
#endif
   }

   lpView   = *pvReturnView;
   lpViewOD = zGETPTR( lpView->hViewOD );

   nRC = fnActivateEmptyObjectInstance( lpCurrentTask, lpView, lControl );
   if ( nRC )
      goto EndOfFunction;

   //======================================================================
   // Retrieve the first line from the stream and determine if the stream
   // is a binary or ASCII stream.
   //======================================================================

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

   nEOF = (*lpfnStreamFunc)( lpView, lpvData, &pchLine, 0, 0 );
   if ( nEOF == 0 || nEOF == zCALL_ERROR )
   {
      //  "KZOEE072 - Error reading instance file "
   // fnIssueCoreError( lpCurrentTask, lpView, 16, 72, 0, szOpenFileName, 0 );
      return( zCALL_ERROR );
   }

#if 0    // sample header
rZeidon    SPARDA01 TZEREMDO 03/01/96   09:03:16 1.0a

      // sample new header
z0100-Zeidon    SPARDA01 TZEREMDO 03/01/96   09:03:16 1.0a
z1000-Zeidon    ACCOUNT  TZWDLGSO 04/18/07   09:18:42 1.0a2
#endif

   // DGC 10/23/96  New header style where binary, incremental, and compressed
   // information is stored as bit-flags.
   if ( *pchLine == 'z' )
   {
      // New header style.
      if ( zstrncmp( pchLine + 6, szlmZeidon, 6 ) != 0 )
      {
         //  "KZOEE073 - Invalid instance file header in "
      // fnIssueCoreError( lpCurrentTask, lpView, 16, 73, 0, szOpenFileName, 0 );
         return( zCALL_ERROR );
      }

      // Just got the header ... set the release value from the file
      // header into the view (object instance) release value. (dks 3/5/96)
      if ( zstrlen( pchLine ) > 55 )
      {
         strncpy_s( lpViewOI->szRelease, zsizeof( lpViewOI->szRelease ), pchLine + 54, 8 );
         lpViewOI->szRelease[ 8 ] = 0;
      }

      if ( pchLine[ 2 ] == '1' )
         lControl |= zINCREMENTAL;
      else
         lControl &= ~zINCREMENTAL;

      if ( pchLine[ 3 ] == '1' )
         lControl |= zCOMPRESSED;
      else
         lControl &= ~zCOMPRESSED;

      if ( pchLine[ 4 ] == '1' )
         bContainsOptimisticOIs = TRUE;

      // Attrib flags have been written if the 5th flag is set or if the OI is
      // written in incremental/compressed form.
      if ( pchLine[ 5 ] == '1' ||
           ((lControl & zCOMPRESSED) && (lControl & zINCREMENTAL)) )
      {
         lControl |= zATTRIBFLAGS;
      }

      // This used to be the binary flag.  For now it tells us whether the
      // ER_Date is stored with the LOD.
      if ( pchLine[ 1 ] == '1' && (lControl & zINCREMENTAL) != 0 )
      {
         // Get the ER date.
         (*lpfnStreamFunc)( lpView, lpvData, &pchLine, 0, 0 );

         // Check to see if the ER dates match.  We only worry about this if
         // the OI is compressed.  If it's not compressed then we can probably
         // handle any differences.
         if ( (lControl & zCOMPRESSED) &&
              pchLine[ 0 ] && lpViewOD->szER_Date[ 0 ] &&
              zstrcmp( lpViewOD->szER_Date, pchLine ) != 0 )
         {
            // "KZOEE088 - Compressed OI is out of sync with LOD/XOD"
            fnIssueCoreError( lpCurrentTask, lpView, 16, 88, 0, lpViewOD->szName, 0 );
            return( zCALL_ERROR );
         }
      }
   }
   else
   {
      // Old header style.
      if ( zstrncmp( pchLine + 1, szlmZeidon, 6 ) )
      {
         //  "KZOEE073 - Invalid instance file header in "
      // fnIssueCoreError( lpCurrentTask, lpView, 16, 73, 0, szOpenFileName, 0 );
         return( zCALL_ERROR );
      }

      // just got the header ... set the release value from the file
      // header into the view (object instance) release value. (dks 3/5/96)
      if ( zstrlen( pchLine ) > 50 )
      {
         strncpy_s( lpViewOI->szRelease, zsizeof( lpViewOI->szRelease ), pchLine + 49, 8 );
         lpViewOI->szRelease[ 8 ] = 0;
      }

      // Set Incremental.
      if ( pchLine[ 0 ] == 'r' )
         lControl |= zINCREMENTAL;
      else
         lControl &= ~zINCREMENTAL;
   }

   // Set Root only indicator.
   if ( lControl & zACTIVATE_ROOTONLY )
      lpViewOI->bRootOnly = TRUE;

   nRC = fnActivateOI_FromTextStream( lpView, lpfnStreamFunc, lpvData, &lControl );
   if ( nRC < -1 )
      goto EndOfFunction;

   // If the stream has optimistic locking information try to activate
   // the "original view" and the qualification view.  These should appear
   // in the stream after the main view.
   if ( bContainsOptimisticOIs )
   {
      zLONG  lTempControl;
      zSHORT nSaveRC = nRC;

      // lTempControl is what we use to activate the original OI and the
      // qualification OI.  Since no OI is OK, add it to the flag.
      lTempControl = lControl | zNOI_OKAY;

      if ( lControl & zACTIVATE_SYSTEM )
      {
         nRC = fnDeclareView( &vOrigView, lpOwningTask,
                              lpAppQualView, cpcViewOD_Name, 1 );
      }
      else
      {
         nRC = fnDeclareView( &vOrigView, lpOwningTask,
                              lpAppQualView, cpcViewOD_Name, 0 );
      }

      if ( nRC < 0 )
         goto EndOfFunction;

      nRC = fnActivateEmptyObjectInstance( lpCurrentTask, vOrigView, lControl );

      if ( nRC < 0 )
         goto EndOfFunction;

      nRC = fnActivateOI_FromTextStream( vOrigView, lpfnStreamFunc,
                                         lpvData, &lTempControl );

      if ( nRC < -1 )
         goto EndOfFunction;

      nRC = fnDeclareView( &vQualView, lpOwningTask,
                           lpAppQualView, "KZDBHQUA", 1 );

      if ( nRC < 0 )
         goto EndOfFunction;

      nRC = fnActivateEmptyObjectInstance( lpCurrentTask, vQualView, lControl );

      if ( nRC < 0 )
         goto EndOfFunction;

      nRC = fnActivateOI_FromTextStream( vQualView, lpfnStreamFunc,
                                         lpvData, &lTempControl );

      if ( nRC < -1 )
         goto EndOfFunction;
      else
      if ( nRC == -1 )
      {
         // Qual view is empty so we really don't need it.
         fnDropView( vQualView );
         vQualView = 0;
      }

      nRC = nSaveRC;

      vOrigView->bOrigView   = TRUE;
      vOrigView->bViewLocked = TRUE;
      vOrigView->hMainOI     = zGETHNDL( lpViewOI );
      lpViewOI->vOriginalOI  = zGETHNDL( vOrigView );

      vQualView->bQualView   = TRUE;
      vQualView->bViewLocked = TRUE;
      vQualView->hMainOI     = zGETHNDL( lpViewOI );
      lpViewOI->vQualOI      = zGETHNDL( vQualView );
   }

   // Reset the view if successful.
   if ( nRC >= 0 )
   {
      if ( (lControl & zSAVE_CURSORS) == 0 )
         fnResetView( lpView, 0 );

      if ( lControl & zREADONLY )
         lpView->bReadOnly = TRUE;
   }

   // Now that we are finished activating, check the root instance
   // to determine if multiple roots were loaded.
   if ( nRC == 0 )
   {
      LPENTITYINSTANCE lpRootEntityInstance =
                                 zGETPTR( lpViewOI->hRootEntityInstance );

      if ( lpRootEntityInstance && lpRootEntityInstance->hNextTwin )
      {
         nRC = 1;
      }
   }

#ifdef __ACTIVATE_CONSTRAINTS__
   if ( (lControl & zACTIVATE_NOCONSTRAINTS) == 0 )
   {
      if ( lpViewOD->bActivateConstraint && nRC >= -1 )
      {
         zSHORT   k;
         zSHORT   nState = zOCE_STATE_FILE;

         if ( lControl & zLEVEL_SYSTEM )
            nState += zOCE_STATE_SYSTEM;

         if ( nRC == -2 )
            nState += zOCE_STATE_NOI;

         k = fnInvokeOCEOperation( lpView, lpCurrentTask,
                                   zOCE_ACTIVATE, nState );
         if ( k )
         {
            fnDropView( lpView );
            *pvReturnView = 0;
         // fnOperationReturn( iActivateOI_FromFile, lpCurrentTask );
            return( k );
         }
      }
   }
#endif

EndOfFunction:

   // Based on the return code, see if we have to reset the view to the
   // prior instance or clean up the prior instance.
   // note: rc = indicates multiple level1 roots present
   if ( nRC >= -1 )
   {
      lpViewOI->bUpdatedFile = FALSE;
   }
   else
   {
      fnDropView( lpView );
      *pvReturnView = 0;

      if ( vOrigView )
         fnDropView( vOrigView );

      if ( vQualView )
         fnDropView( vQualView );
   }

   if ( AnchorBlock->TraceFlags.bOI_Times )
   {
      zCHAR sz[ 100 ];

      if ( zstrcmp( lpViewOD->szName, "TZCMULWO" ) != 0 )
      {
         sprintf_s( sz, zsizeof( sz ), "(%s) = %lf seconds", lpViewOD->szName,
                    (double) (SysGetTickCount( ) - lTickCount) / zTICKS_PER_SECOND );
         TraceLineS( "(oi) Total time for SfActivateOI_FromStream ", sz );
      }
   }

   return( nRC );

} // SfActivateOI_FromStream

//./ ADD NAME=SfActivateSysOI_FromFile
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SfActivateSysOI_FromFile
//
//  PURPOSE:    To activate an Object instance from a file and
//              return a view to the object instance
//
//  PARAMETERS: pvReturnView  - View returned to instance activated
//              cpcViewOD_Name - Name of the view object.  If 0, the
//                              returned view is for the same object as
//                              the initial view(?).
//              lpAppQualView - Used to qualify the application in which
//                              to look for the object.  If the view
//                              passed is a subtask view, then the
//                              application that is used is the
//                              application tied to the subtask.
//                              Otherwise, the application for the view
//                              object associated with the passed view
//                              is used.
//              cpcFileName   - The fully-qualified file name from which
//                              to activate ( including the drive, path,
//                              and file extension ).
//              lControl      - Controls certain aspects of the file
//                              loaded.
//                            zSINGLE   - (default) only one entity at the
//                                        root level.
//                            zMULTIPLE - multiple entities at the root
//                                        level
//                            zNOI_OKAY - when set, if the file could not
//                                        be opened, no error message is
//                                        issued, just return code set.
//                            zREADONLY - Marks the View and the Instance
//                                        as read only.  Any view created
//                                        from this view will also be
//                                        marked as read only.
//
//  RETURNS:   -1 - zNOI_OKAY was specified and the file could not be
//                  loaded into the Object Instance.
//              0 - Object instance activated, single root found
//              1 - Object instance activated, multiple roots found.  If
//                  zSINGLE was specified, only the first was activated.
//    zCALL_ERROR - Error Activating object instance
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 6
zSHORT OPERATION
SfActivateSysOI_FromFile( zPVIEW   pvReturnView,
                          zCPCHAR  cpcViewOD_Name,
                          zVIEW    lpAppQualView,
                          zCPCHAR  cpcFileName,
                          zLONG    lControl )
{
   LPTASK      lpCurrentTask;
   zSHORT      nRC;

   // init in case of error
   *pvReturnView = 0;

#ifdef DEBUG
   if ( lpAppQualView == 0 )
   {
      TraceLine( "SfActivateSysOI_FromFile now REQUIRES a non-zero "
                   "qualification view for Object Definition: %s", cpcViewOD_Name );
      SysMessageBox( 0, "Zeidon OE", "SfActivateSysOI_FromFile now REQUIRES a "
                     "non-zero qualification view.  System will now crash", 0 );
   }
#endif

   // If task not active or disabled, or view invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iSfActivateSysOI_FromFile,
                                          lpAppQualView, zVALID_VIEW )) == 0 )
   {
      return( zCALL_ERROR );
   }

   nRC = ActivateOI_FromFile( pvReturnView, cpcViewOD_Name, lpAppQualView,
                              cpcFileName, lControl | zACTIVATE_SYSTEM );

   fnOperationReturn( iSfActivateSysOI_FromFile, lpCurrentTask );
   return( nRC );

} // SfActivateSysOI_FromFile

//./ ADD NAME=SfActivateSysEmptyOI
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      SfActivateSysEmptyOI
//
//  PURPOSE:    To activate an empty Object instance and return a
//              view to the object instance.
//
//  PARAMETERS: lpReturn View - View returned to instance activated
//              cpcViewOD_Name - Name of the view object.  If 0, the
//                              returned view is for the same object as
//                              the initial view(?).
//              lpAppQualView - Used to qualify the application in which
//                              to look for the object.  If the view
//                              passed is a subtask view, then the
//                              application that is used is the
//                              application tied to the subtask.
//                              Otherwise, the application for the view
//                              object associated with the passed view
//                              is used.
//              lControl      - Controls certain aspects of the file
//                              loaded.
//                            zSINGLE   - (default) only one entity at the
//                                        root level.
//                            zMULTIPLE - multiple entities at the root
//                                        level
//                            zREADONLY - Marks the View and the Instance
//                                        as read only.  Any view created
//                                        from this view will also be
//                                        marked as read only.
//
//  RETURNS:  0           - Instance activated successfully
//            zCALL_ERROR - Error Activating object instance
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT OPERATION
SfActivateSysEmptyOI( zPVIEW  pvReturnView,
                      zCPCHAR cpcViewOD_Name,
                      zVIEW   lpAppQualView,
                      zLONG   lControl )
{
   LPTASK      lpCurrentTask;
   LPTASK      lpOwningTask;
   LPVIEWOD    lpViewOD;
   zVIEW       lpView;
   zSHORT      nRC;

   // init in case of error
   *pvReturnView = 0;

#ifdef DEBUG
   if ( lpAppQualView == 0 )
   {
      TraceLine( "SfActivateSysEmptyOI now REQUIRES a non-zero "
                   "qualification view for Object Definition: %s.", cpcViewOD_Name );
      SysMessageBox( 0, "Zeidon OE", "SfActivateSysEmptyOI now REQUIRES a "
                     "non-zero qualification view.  System will now crash", 0 );
   }
#endif

   // If task not active or disabled, or view invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iSfActivateSysEmptyOI,
                                          lpAppQualView, zVALID_VIEW )) == 0 )
   {
      return( zCALL_ERROR );
   }

   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
      lpOwningTask = zGETPTR( AnchorBlock->hMainTask );
   else
      lpOwningTask = lpCurrentTask;

   if ( (nRC = fnDeclareView( pvReturnView, lpOwningTask,
                              lpAppQualView, cpcViewOD_Name, 1 )) != 0 )
   {
      fnOperationReturn( iSfActivateSysEmptyOI, lpCurrentTask );
      return( nRC );
   }

#if 0
   if ( lControl & (zLEVEL_APPLICATION | zLEVEL_SYSTEM) )
   {
      zSHORT nScope = (lControl & zLEVEL_APPLICATION) ?
                                  zLEVEL_APPLICATION : zLEVEL_SYSTEM;
      if ( (nRC = SfTransferView( *pvReturnView, lpAppQualView,
                                  nScope )) != 0 )
      {
         fnOperationReturn( iSfActivateSysEmptyOI, lpCurrentTask );
         return( nRC );
      }
   }
#endif

   nRC = fnActivateEmptyObjectInstance( lpCurrentTask, *pvReturnView, lControl );
   lpView = *pvReturnView;
   if ( lControl & zREADONLY )
      lpView->bReadOnly = TRUE;

#ifdef __ACTIVATE_CONSTRAINTS__
   // If object has activate constraint active, check for objections.
   // If any drop view and exit...
   lpViewOD = zGETPTR( lpView->hViewOD );
   if ( lpViewOD->bActivateEmptyConstraint && nRC == 0 )
   {
      zSHORT nState = zOCE_STATE_SYSTEM;

      nRC = fnInvokeOCEOperation( lpView, lpCurrentTask,
                                  zOCE_ACTIVATE_EMPTY, nState );
      if ( nRC )
      {
         fnDropView( lpView );
         *pvReturnView = 0;
      }
   }
#endif

   fnOperationReturn( iSfActivateSysEmptyOI, lpCurrentTask );
   return( nRC );
}

//./ ADD NAME=fnDateTimeFormat
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnDateTimeFormat
//
//  PURPOSE:    To format DateTime field "yyyymmddhhmmsshh", to
//              a Date field "mm/dd/yy", and a Time field "hh:mm:ss"
//
//  PARAMETERS: szDateTime - input "yyyymmddhhmmsshh"
//              szDate     - output "mm/dd/yy"
//              szTime     - output "hh:mm:ss"
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
void
fnDateTimeFormat( zPCHAR pchDateTime, zPCHAR pchDate, zLONG lDateLth, zPCHAR pchTime, zLONG lTimeLth )
{
   strncpy_s( pchDate, lDateLth, pchDateTime + 4, 2 );          // copy month
   pchDate[ 2 ] = '/';                                          // separator
   strncpy_s( pchDate + 3, lDateLth - 3, pchDateTime + 6, 2 );  // copy day
   pchDate[ 5 ] = '/';                                          // separator
   strncpy_s( pchDate + 6, lDateLth - 6, pchDateTime + 2, 2 );  // copy year
   pchDate[ 8 ] = 0;                                            // null terminator

   strncpy_s( pchTime, lTimeLth, pchDateTime + 8, 2 );          // copy hours
   pchTime[ 2 ] = ':';                                          // separator
   strncpy_s( pchTime + 3, lDateLth - 3, pchDateTime + 10, 2 ); // copy minutes
   pchTime[ 5 ] = ':';                                          // separator
   strncpy_s( pchTime + 6, lDateLth - 6, pchDateTime + 12, 2 ); // copy seconds
   pchDate[ 8 ] = 0;                                            // null terminator
}

//./ ADD NAME=fnCompareEIAttrs
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:  fnCompareEIAttrs
//
//  ARGUMENTS:
//        lpCurrentTask
//        lpView1       - View for 1st attr.  Only needed if context is used.
//        lpInstance1,  - Instance ptr for 1st attr.
//        lpViewAttrib1 -
//        pchContext1   - Context for 1st attr.  If null then don't use it.
//                        If empty string then use default context.
//        lpView2       - View for 2nd attr.  Only needed if context is used.
//        lpInstance2   -
//        lpViewAttrib2 -
//        pchContext2   - Context for 2nd attr.  If null then don't use it.
//                        If empty string then use default context.
//
//  RETURNS:  -1 lpInstance1.lpEntityAttrib <  lpInstance2.lpEntityAttrib
//             0 lpInstance1.lpEntityAttrib == lpInstance2.lpEntityAttrib
//             1 lpInstance1.lpEntityAttrib >  lpInstance2.lpEntityAttrib
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT LOCALOPER
fnCompareEIAttrs( LPTASK            lpCurrentTask,
                  zVIEW             lpView1,
                  LPENTITYINSTANCE  lpInstance1,
                  LPVIEWATTRIB      lpViewAttrib1,
                  zPCHAR            pchContextName1,
                  zVIEW             lpView2,
                  LPENTITYINSTANCE  lpInstance2,
                  LPVIEWATTRIB      lpViewAttrib2,
                  zPCHAR            pchContextName2 )
{
   zPCHAR   pchValue1, pchValue2;
   zSHORT   bNull1, bNull2;
   zCHAR    chType1, chType2;
   zSHORT   nRC;

   typedef union _AttrValues
   {
      zLONG          l;
      zCHAR          sz[ 256 ];
      zDECIMAL       d;
      DateTimeRecord dt;
   } AttrValues;
   AttrValues AttrVal1, AttrVal2;

   bNull1 = fnAttributeValueNull( 0, lpInstance1, lpViewAttrib1 );
   bNull2 = fnAttributeValueNull( 0, lpInstance2, lpViewAttrib2 );

   if ( bNull1 )
   {
      if ( bNull2 )
         return( 0 );
      else
         return( -1 );
   }
   else
   if ( bNull2 )
   {
      // We know that attrib 1 is NOT null so it is > than attrib 2.
      return( 1 );
   }

   chType1 = lpViewAttrib1->cType;

   // Check to see if we have a context.  If we do, use it to get the attr
   // value.  If not, get a pointer to the internal value.

   if ( pchContextName1 && chType1 != zTYPE_BLOB && chType1 != zTYPE_DATETIME )
   {
      LPVIEWENTITYCSR lpViewEntityCsr;
      zULONG          ulLth;

      // Use the context name to get attribute value.
      lpViewEntityCsr = fnEstablishViewForInstance( lpView1, 0, lpInstance1 );

      // Use default context if pchContextName points to an empty string.
      fnGetVariableFromAttribute( (zPVOID) &AttrVal1, &ulLth,
                                  chType1, (zULONG) sizeof( AttrVal2 ),
                                  lpView1, lpViewEntityCsr,
                                  lpViewAttrib1,
                                  pchContextName1,
                                  lpCurrentTask,
                                  (zSHORT) (*pchContextName1 ? 0 : zUSE_DEFAULT_CONTEXT) );

      pchValue1 = (zPCHAR) &AttrVal1;
   }
   else
      fnGetAddrForAttribute( &pchValue1, 0, 0, lpInstance1, lpViewAttrib1 );

   chType2 = lpViewAttrib2->cType;

   if ( pchContextName2 && chType2 != zTYPE_BLOB && chType2 != zTYPE_DATETIME )
   {
      LPVIEWENTITYCSR lpViewEntityCsr;
      zLONG           uLth;

      // Use the context name to get attribute value.
      lpViewEntityCsr = fnEstablishViewForInstance( lpView2, 0, lpInstance2 );

      // Use default context if pchContextName points to an empty string.
      fnGetVariableFromAttribute( (zPVOID) &AttrVal2, &uLth,
                                  chType2, (zULONG) sizeof( AttrVal2 ),
                                  lpView2, lpViewEntityCsr,
                                  lpViewAttrib2,
                                  pchContextName2,
                                  lpCurrentTask,
                                  (zSHORT) ( *pchContextName2 ? 0 : zUSE_DEFAULT_CONTEXT ) );

      pchValue2 = (zPCHAR) &AttrVal2;
   }
   else
      fnGetAddrForAttribute( &pchValue2, 0, 0, lpInstance2, lpViewAttrib2 );

   switch ( chType1 )
   {
      case zTYPE_STRING:
         if ( lpViewAttrib1->bCaseSens )
            nRC = zstrcmp( pchValue1, pchValue2 );
         else
            nRC = zstrcmpi( pchValue1, pchValue2 );

         if ( nRC < 0 )
            nRC = -1;
         else
         if ( nRC > 0 )
            nRC = 1;

         return( nRC );

      case zTYPE_INTEGER:
         if ( *((zPLONG) pchValue1) == *((zPLONG) pchValue2) )
            nRC = 0;
         else
            nRC = (*((zPLONG) pchValue1) < *((zPLONG) pchValue2)) ? -1 : 1;

         return( nRC );

      case zTYPE_DECIMAL:
         return( SysCompareDecimalToDecimal( (zPDECIMAL) pchValue1,
                                             (zPDECIMAL) pchValue2 ) );

      case zTYPE_DATETIME:
         nRC = fnCompareDateTimeToDateTime( (LPDTINTERNAL) pchValue1,
                                            (LPDTINTERNAL) pchValue2 );
         return( nRC );

      case zTYPE_BLOB:
      {
         zULONG ulLth1, ulLth2, uBlobLth;

         fnGetAttributeLength( &ulLth1, 0, lpInstance1, lpViewAttrib1 );
         fnGetAttributeLength( &ulLth2, 0, lpInstance2, lpViewAttrib2 );

         uBlobLth = min( ulLth1, ulLth2 );

         nRC = zmemcmp( pchValue1, pchValue2, (int) uBlobLth );
         if ( nRC == 0 )
         {
            if ( ulLth1 == ulLth2 )
               return( 0 );
            else
               return( ulLth1 < ulLth2 ? -1 : 1 );
         }
         else
            return( nRC );
      }

   } // end of switch ( lpSrcViewAttrib->cType )

   return( zCALL_ERROR );
}

#define SWAP_EI( a, b ) { LPENTITYINSTANCE t = b; b = a; a = t; }

typedef struct SortDataStruct SortDataRecord;
typedef SortDataRecord *LPSORTDATA;
struct SortDataStruct
{
   LPTASK           lpCurrentTask;
   LPVIEWATTRLIST   lpViewAttrList;
   zVIEW            lpView1;
   zVIEW            lpView2;
};

zSHORT
fnCmprEntities( LPVIEWENTITY hViewEntity1,
                LPVIEWENTITY hViewEntity2 )
{
   LPVIEWENTITY lpViewEntity1 = zGETPTR( hViewEntity1 );
   LPVIEWENTITY lpViewEntity2 = zGETPTR( hViewEntity2 );

#if 0
   TraceLine( "fnSortCmpr Checking Entities: %s : 0x%08x, %s : 0x%08x",
              lpViewEntity1->szName, lpViewEntity1->lEREntTok,
              lpViewEntity2->szName, lpViewEntity2->lEREntTok );
#endif

   // It appears that it is "good enough" for the entity tokens to
   // match when doing the compare.  In such a case, for example,
   // CtrlCtrl matches Control in TZWDLGSO.   dks 2005.12.26
   if ( lpViewEntity1 && lpViewEntity2 &&
        lpViewEntity1->lEREntTok == lpViewEntity2->lEREntTok )
   {
      return( 0 );
   }

   return( 1 );
}

/*
   Compare two EIs and decide if they need to be swapped.

   RETURNS: 1 - Swap entities (they are in correct order).
            0 - Don't swap entities (they are out of order).
*/
zSHORT
fnSortCmpr( LPSORTDATA       lpSortData,
            LPENTITYINSTANCE lpEI1,
            LPENTITYINSTANCE lpEI2 )
{
   LPVIEWATTRLIST   lpAttrListPtr;
   LPENTITYINSTANCE lpCompareEI1;
   LPENTITYINSTANCE lpCompareEI2;
   zSHORT           nComp;

   // Compare sort keys from major to minor.  When an inequality is
   // found, see if an entity swap is needed.
   for ( lpAttrListPtr = lpSortData->lpViewAttrList;
         lpAttrListPtr->lpViewAttrib;
         lpAttrListPtr++ )
   {
      // Check to see if the sort key belongs to the same entity that we are
      // sorting.  If not we need to retrieve the EI for the sort key.
      if ( lpAttrListPtr->lpViewAttrib->hViewEntity != lpEI1->hViewEntity &&
           fnCmprEntities( lpAttrListPtr->lpViewAttrib->hViewEntity,
                           lpEI1->hViewEntity ) != 0 )
      {
         // Sort key is from a different entity than the swap entity.  This
         // could happen if the user is sorting entities using the value of a
         // child entity.  We need to retrieve the EI for the child entity.
         // Since cursor positions are undefined at this point we will assume
         // the first child entity.
         lpCompareEI1 = zGETPTR( lpEI1->hNextHier );
         while ( lpCompareEI1 )
         {
            // Check to see if this is the EI we are looking for.
            if ( lpCompareEI1->hViewEntity ==
                                  lpAttrListPtr->lpViewAttrib->hViewEntity )
            {
               break;  // it is the EI we are looking for
            }

            // Check the next EI.
            lpCompareEI1 = zGETPTR( lpCompareEI1->hNextHier );

            if ( lpCompareEI1 == 0 )
               break;

            // If the level of the current EI is <= the level of the parent
            // EI then we never found a matching child entity ... so break.
            if ( lpCompareEI1->nLevel <= lpEI1->nLevel )
            {
               lpCompareEI1 = 0;
               break;
            }
         }

         // Do the same thing for the second EI.
         lpCompareEI2 = zGETPTR( lpEI2->hNextHier );
         while ( lpCompareEI2 )
         {
            // Check to see if this is the EI we are looking for.
            if ( lpCompareEI2->hViewEntity ==
                                  lpAttrListPtr->lpViewAttrib->hViewEntity )
            {
               break;  // it is the EI we are looking for
            }

            // Check the next EI.
            lpCompareEI2 = zGETPTR( lpCompareEI2->hNextHier );

            if ( lpCompareEI2 == 0 )
               break;

            // If the level of the current EI is <= the level of the parent
            // EI then we never found a matching child entity ... so break.
            if ( lpCompareEI2->nLevel <= lpEI2->nLevel )
            {
               lpCompareEI2 = 0;
               break;
            }
         }

         // If either of the compare entities are 0 then they don't
         // exist so set nComp and break.
         if ( lpCompareEI1 == 0 || lpCompareEI2 == 0 )
         {
            // If they are the same then they are both 0 and we'll assume
            // that they compare equal.
            if ( lpCompareEI1 == lpCompareEI2 )
               nComp = 0;
            else
            if ( lpCompareEI1 ) // EI1 is valid but EI2 is not so we'll assume EI1 > EI2.
               nComp = 1;
            else
               nComp = -1;

            break;
         }
      }
      else
      {
         // We are comparing the same entity we are swapping.
         lpCompareEI1 = lpEI1;
         lpCompareEI2 = lpEI2;
      }

      // Now actually perform the compare.
      nComp = fnCompareEIAttrs( lpSortData->lpCurrentTask,
                                lpSortData->lpView1, lpCompareEI1,
                                lpAttrListPtr->lpViewAttrib,
                                lpAttrListPtr->pszContextName,
                                lpSortData->lpView2, lpCompareEI2,
                                lpAttrListPtr->lpViewAttrib,
                                lpAttrListPtr->pszContextName );

      // If the compare wasn't equal then we don't need to compare any more
      // because we know the EIs are different.
      if ( nComp )
         break;

   } // for...

   // If the EIs are different then find out if they need to be swapped.
   if ( nComp )
   {
      if ( nComp < 0 && lpAttrListPtr->bOrder )
         return( 1 );

      if ( nComp > 0 && lpAttrListPtr->bOrder == FALSE )
         return( 1 );
   }

   // If we get here then the EIs are in correct order.
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// When Heapify is called, it is assumed that the binary trees rooted at   //
// Left( k ) and Right( k ) are heaps, but that A[ k ] may be smaller than //
// its children (a violation).  Heapify lets the value of A[ k ] float     //
// down in the heap so that the subtree rooted at index k becomes a heap.  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

////////////////////////////// Heapify //////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
zULONG
Heapify( LPSORTDATA       lpSortData,
         LPENTITYINSTANCE lpEI[],
         zULONG           ulRecordCnt,
         zULONG           k )
{
// ASSERT_TRACE( "Heapify error", 0, k <= ulRecordCnt );
   zULONG ulLeft = k << 1;
   zULONG ulLargest;

   if ( ulLeft > ulRecordCnt )
   {
      return( 0 );
   }

   ulLargest = k;
// if ( CompareRecords( ulLeft, ulLargest ) > 0 )
   if ( fnSortCmpr( lpSortData, lpEI[ ulLeft - 1 ], lpEI[ ulLargest - 1 ] ) )
   {
      ulLargest = ulLeft;
   }

   ulLeft++;   // ulRight (use ulLeft to conserve stack space)
   if ( ulLeft <= ulRecordCnt )
   {
   // if ( CompareRecords( ulLeft, ulLargest ) > 0 )
      if ( fnSortCmpr( lpSortData, lpEI[ ulLeft - 1 ], lpEI[ ulLargest - 1 ] ) )
      {
         ulLargest = ulLeft;
      }
   }

   if ( k != ulLargest )
   {
      SWAP_EI( lpEI[ k - 1 ], lpEI[ ulLargest - 1 ] );
   // zULONG *p1;
   // zULONG *p2;

   // // Use uLeft to conserve stack.
   // p1 = CSIMP_GETSORTIDX_PTR( k, m_pUseIdx->m_pxIdx );
   // p2 = CSIMP_GETSORTIDX_PTR( ulLargest, m_pUseIdx->m_pxIdx );
   // ulLeft = *p1;
   // *p1 = *p2;
   // *p2 = ulLeft;
      return( ulLargest );
   }

   return( 0 );
}  // end of:  Heapify

////////////////////////////// BuildHeap ////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void
BuildHeap( LPSORTDATA       lpSortData,
           LPENTITYINSTANCE lpEI[],
           zULONG           ulRecordCnt ) // non-recursive
{
   zULONG k;
   zULONG ul;

#ifdef DEBUG_ALL
   OutputDebugString( "\nShowing heap prior to build heap ...\n" );
   ShowHeap( this, m_pUseIdx->m_pxIdx );
#endif

   k = ulRecordCnt / 2;
   while ( k > 0 )
   {
      ul = Heapify( lpSortData, lpEI, ulRecordCnt, k-- );
      while ( ul )
      {
         ul = Heapify( lpSortData, lpEI, ulRecordCnt, ul );
      }
   }
}  // end of:  BuildHeap

////////////////////////////// HeapSort /////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void
fnHeapSort( LPSORTDATA       lpSortData,
            LPENTITYINSTANCE lpEI[],
            zULONG           ulRecordCnt )
{
// zULONG ulHoldCnt = ulRecordCnt;
// zULONG ulHoldMax = ulMaxRecords;
// zULONG *p1;
   zULONG ul;

   BuildHeap( lpSortData, lpEI, ulRecordCnt );

   while ( ulRecordCnt > 1 )
   {
      ulRecordCnt--;
   // ulMaxRecords--;
   //
   // p1 = CSIMP_GETSORTIDX_PTR( ulRecordCnt + 1, m_pUseIdx->m_pxIdx );
   // ul = *p1;
   // *p1 = *(m_pUseIdx->m_pxIdx);
   // *(m_pUseIdx->m_pxIdx) = ul;

   // ul = Heapify( 1 );
      ul = Heapify( lpSortData, lpEI, ulRecordCnt, 1 );
      while ( ul )
      {
      // ul = Heapify( ul );
         ul = Heapify( lpSortData, lpEI, ulRecordCnt, ul );
      }
   }

// ulRecordCnt = ulHoldCnt;
// ulMaxRecords = ulHoldMax;
}

/////////////////////////////// QuickSort ///////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void
fnQuickSort( LPSORTDATA       lpSortData,
             LPENTITYINSTANCE lpEI[],
             zULONG           ulRecordCnt )
{
   zULONG k, j, ulLeft, ulRight;

   while ( ulRecordCnt > 1 )
   {
      SWAP_EI( lpEI[ 0 ], lpEI[ ulRecordCnt / 2 ] );

      for ( k = 0, j = ulRecordCnt; ; )
      {
         // Search for an EI that is "less than" lpEI[ 0 ].
         do
            j--;
         while ( j > 0 && fnSortCmpr( lpSortData, lpEI[ j ], lpEI[ 0 ] ) );

         // Search for an EI that is "less than" lpEI[ 0 ].
         do
            k++;
         while ( k < j && !fnSortCmpr( lpSortData, lpEI[ k ], lpEI[ 0 ] ) );

         if ( k >= j )
            break;

         SWAP_EI( lpEI[ k ], lpEI[ j ] );
      }

      SWAP_EI( lpEI[ j ], lpEI[ 0 ] );

      ulLeft = j;
      ulRight = ulRecordCnt - ++j;
      if ( ulLeft < ulRight )
      {
         fnQuickSort( lpSortData, lpEI, ulLeft );

         lpEI += j;
         ulRecordCnt = ulRight;
      }
      else
      {
         fnQuickSort( lpSortData, lpEI + j, ulRight );
         ulRecordCnt = ulLeft;
      }

   } // while ( ulRecordCnt > 1 )...

} // fnQuickSort

void
fnBubbleSort( LPSORTDATA       lpSortData,
              LPENTITYINSTANCE lpEI[],
              zULONG           ulRecordCnt )
{
   zULONG k, j;
   zBOOL  bSwaps;

   for ( k = ulRecordCnt - 1; k > 0; k-- )
   {
      bSwaps = FALSE;

      for ( j = 0; j < k; j++ )
      {
         // If EI[ j ] is > EI[ j + 1 ] then swap them.
         if ( fnSortCmpr( lpSortData, lpEI[ j ], lpEI[ j + 1 ] ) )
         {
            bSwaps = TRUE;
            SWAP_EI( lpEI[ j ], lpEI[ j + 1 ] );
         }
      }

      // If there were no swaps then everything's in order so get out.
      if ( bSwaps == FALSE )
         break;
   }

} // fnBubbleSort

//./ ADD NAME=fnOrderEntityForView
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:  fnOrderEntityForView
//
//
//  RETURNS:  0            sort successfull
//            zCALL_ERROR  error in call
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT LOCALOPER
fnOrderEntityForView( zVIEW            zView,
                      LPENTITYINSTANCE lpEntityInstance,
                      LPVIEWATTRLIST   lpViewAttrList,
                      zBOOL            bUseBubbleSort )
{
   SortDataRecord    SortData;
   LPVIEWATTRLIST    lpViewAttrListPtr;
   LPENTITYINSTANCE  lpEI1;
   LPENTITYINSTANCE  lpLastChild;
   LPENTITYINSTANCE  lpLastOldChild;
   LPENTITYINSTANCE  *lpEIBuffer;
   LPENTITYINSTANCE  lpFirstEntityInstance;
   LPENTITYINSTANCE  lpLastEntityInstance;
   zULONG            ulEntityCnt;
   zULONG            ulFront, ulBack, k;
   zLONG             hEIBuffer;
   zBOOL             bDerivedAttribPresent = FALSE;
   zSHORT            nRC;

   // Only used with derived attributes ...
   LPTASK            lpCurrentTask;

   // If instance is null, there is nothing to sort ...
   if ( lpEntityInstance == 0 )
      return( 0 );

   // Error if trying to sort "unset".
   if ( lpEntityInstance == UNSET_CSR )
      return( zCALL_ERROR );

   lpCurrentTask = zGETPTR( zView->hTask );
// lpCurrentTask = fnFindTask( 0 );  // dks 2006.04.05  back to 10b

   // Scan through the view attributes for any derived attributes.
   for ( lpViewAttrListPtr = lpViewAttrList;
         lpViewAttrListPtr->lpViewAttrib;
         lpViewAttrListPtr++ )
   {
      LPVIEWATTRIB lpViewAttrib = lpViewAttrListPtr->lpViewAttrib;

      if ( lpViewAttrib->szDerivedOper[ 0 ] )
      {
         bDerivedAttribPresent = TRUE;
         lpViewAttrListPtr->pfObjectOper =
                       fnGetAttribOper( zView, lpViewAttrib, lpCurrentTask );
      }
   }

   // Count the number of entities after lpEntityInstance.
   ulEntityCnt = 1; // account for the current lpEntityInstance
   for ( lpLastEntityInstance = lpEntityInstance;
         lpLastEntityInstance->hNextTwin;
         lpLastEntityInstance = zGETPTR( lpLastEntityInstance->hNextTwin ) )
   {
      ulEntityCnt++;
   }

   // Add the number of entities prior to lpEntityInstance.
   for ( lpFirstEntityInstance = lpEntityInstance;
         lpFirstEntityInstance->hPrevTwin;
         lpFirstEntityInstance = zGETPTR( lpFirstEntityInstance->hPrevTwin ) )
   {
      ulEntityCnt++;
   }

   // If we only have 1 entity then there's nothing to sort.
   if ( ulEntityCnt == 1 )
      return( 0 );

   // Now allocate space to hold all the entity instances.
   hEIBuffer = SysAllocMemory( (zCOREMEM) &lpEIBuffer,
                               sizeof( LPENTITYINSTANCE ) * ulEntityCnt,
                               0, zCOREMEM_ALLOC, 0 );

   // Copy the list of entity pointers into the buffer.  We'll put all the
   // hidden instances at the end because we don't need/want to sort them.
   ulFront = 0;
   ulBack  = ulEntityCnt - 1;
   for ( lpEI1 = lpFirstEntityInstance;
         lpEI1;
         lpEI1 = zGETPTR( lpEI1->hNextTwin ) )
   {
      if ( lpEI1->u.nInd.bHidden )
         lpEIBuffer[ ulBack-- ] = lpEI1;  // put hidden EI at the end
      else
         lpEIBuffer[ ulFront++ ] = lpEI1;
   }

   // ulFront is a count of all the non-hidden EIs.  If there's only one EI
   // then don't bother sorting.
   if ( ulFront <= 1 )
   {
      SysFreeMemory( hEIBuffer );
      return( 0 );
   }

   // If any derived attributes in the order keys, go set them for all of
   // the entities now.
   if ( bDerivedAttribPresent )
   {
      zVIEW lpView;

      if ( (nRC = fnDeclareView( &lpView, lpCurrentTask, zView, 0, 0 )) != 0 )
      {
         SysFreeMemory( hEIBuffer );
         return( nRC );
      }

      fnSetViewFromView( lpView, zView );
      for ( lpEI1 = lpFirstEntityInstance;
            lpEI1;
            lpEI1 = zGETPTR( lpEI1->hNextTwin ) )
      {
         LPVIEWENTITYCSR   lpViewEntityCsr;

         if ( lpEI1->u.nInd.bHidden )
            continue;

         lpViewEntityCsr = fnEstablishViewForInstance( lpView, 0, lpEI1 );

         // Set all of the derived attributes (that are used as sort keys)
         // for the entity instance.
         for ( lpViewAttrListPtr = lpViewAttrList;
               lpViewAttrListPtr->lpViewAttrib;
               lpViewAttrListPtr++ )
         {
            LPVIEWENTITY hViewEntity;
            LPVIEWENTITY lpViewEntity;

            if ( lpViewAttrListPtr->pfObjectOper == 0 )
               continue;

            // If the view entity for the sorting attribute is different
            // from the view entity for the EI we're sorting then the attr
            // must be from a child entity.  Make sure a child EI exists
            // before we call the derived operation.
            hViewEntity = lpViewAttrListPtr->lpViewAttrib->hViewEntity;
            if ( hViewEntity != lpEI1->hViewEntity )
            {
               LPENTITYINSTANCE lpSearch;

               for ( lpSearch = zGETPTR( lpEI1->hNextHier );
                     lpSearch;
                     lpSearch = zGETPTR( lpSearch->hNextHier ) )
               {
                  if ( lpSearch->nLevel <= lpEI1->nLevel )
                  {
                     lpSearch = 0;
                     break;
                  }

                  if ( lpSearch->hViewEntity == hViewEntity )
                     break;
               }

               // If lpSearch is 0 then we didn't find a child EI matching
               // hViewEntity so don't call the derived operation.
               if ( lpSearch == 0 )
                  continue;
               else
               {
                  // Establish cursor position for the child entity. (dks and DonC 2009.12.23)
                  fnEstablishViewForInstance( lpView, 0, lpSearch );
               }
            }

            lpViewEntity = zGETPTR( hViewEntity );

            nRC = (*lpViewAttrListPtr->pfObjectOper)( lpView, lpViewEntity,
                                                      lpViewAttrListPtr->lpViewAttrib,
                                                      zDERIVED_GET );
            if ( nRC )
            {
               SysFreeMemory( hEIBuffer );
               fnDropView( lpView );
               return( nRC );
            }
         }

      } // for each lpEI1...

      fnDropView( lpView );

   } // if ( bDerivedAttribPresent )...

   // Set up information for sorting.
   SortData.lpViewAttrList = lpViewAttrList;
   SortData.lpCurrentTask  = lpCurrentTask;
   CreateViewFromViewForTask( &SortData.lpView1, zView, zView );
   CreateViewFromViewForTask( &SortData.lpView2, zView, zView );

   // Call operation to sort the entity list.  We use ulFront instead of
   // ulEntityCnt because we only want to sort the non-hidden EIs.
   if ( bUseBubbleSort )
      fnBubbleSort( &SortData, lpEIBuffer, ulFront );
   else
      fnQuickSort( &SortData, lpEIBuffer, ulFront );
   // fnHeapSort( &SortData, lpEIBuffer, ulFront );  // does not work (yet)!

   fnDropView( SortData.lpView1 );
   fnDropView( SortData.lpView2 );

   // Subtract 1 from ulEntityCnt so it points to the last EI.  This will
   // save us a little time later on.
   ulEntityCnt--;

   //---------------------------------------------------------------------
   // Re-arrange the EI pointers.
   //---------------------------------------------------------------------

   // If we sorted the root instances then set the root entity instance.
   if ( lpFirstEntityInstance->nLevel == 1 )
   {
      LPVIEWCSR lpViewCsr = zGETPTR( zView->hViewCsr );
      LPVIEWOI  lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

      lpViewOI->hRootEntityInstance = zGETHNDL( lpEIBuffer[ 0 ] );
   }

   // Reset the EI pointer for the entity before the "old" first entity.
   if ( lpFirstEntityInstance->hPrevHier )
   {
      LPENTITYINSTANCE lpPrevHier = zGETPTR( lpFirstEntityInstance->hPrevHier );

      // Change lpPrevHier to point to the "new" first entity.
      lpPrevHier->hNextHier = zGETHNDL( lpEIBuffer[ 0 ] );

      lpEIBuffer[ 0 ]->hPrevHier = lpFirstEntityInstance->hPrevHier;
   }
   else
      lpEIBuffer[ 0 ]->hPrevHier = 0;

   // Get the last child of the last old or "unsorted" entity.
   lpLastOldChild = fnFindLastEntityUnderParent( lpLastEntityInstance, FALSE );

   // Get the last child for the last "sorted" entity.
   lpLastChild = fnFindLastEntityUnderParent( lpEIBuffer[ ulEntityCnt ], FALSE );

   // Reset the EI pointer for the entity after the "old" last entity.
   if ( lpLastOldChild->hNextHier )
   {
      LPENTITYINSTANCE lpNextHier = zGETPTR( lpLastOldChild->hNextHier );

      lpLastChild->hNextHier = lpLastOldChild->hNextHier;
      lpNextHier->hPrevHier = zGETHNDL( lpLastChild );

   }
   else
      lpLastChild->hNextHier = 0;

   // Now we'll loop through ALL the EIs and set the
   // PrevHier/NextHier/PrevTwin/NextTwin pointers.
   for ( k = 0; k <= ulEntityCnt; k++ )
   {
      // If 'k' is > 0 then we need to set up Prev pointers.
      if ( k > 0 )
      {
         lpEIBuffer[ k ]->hPrevHier = zGETHNDL( lpLastChild );
         lpEIBuffer[ k ]->hPrevTwin = zGETHNDL( lpEIBuffer[ k - 1 ] );
      }
      else
         lpEIBuffer[ k ]->hPrevTwin = 0;

      // Find the last child (hierarchically) under the current EI.
      lpLastChild = fnFindLastEntityUnderParent( lpEIBuffer[ k ], FALSE );

      // If 'k' is < ulEntityCnt then we need to set up Next pointers.
      if ( k < ulEntityCnt )
      {
         lpEIBuffer[ k ]->hNextTwin = zGETHNDL( lpEIBuffer[ k + 1 ] );
         lpLastChild->hNextHier     = zGETHNDL( lpEIBuffer[ k + 1 ] );
      }
      else
         lpEIBuffer[ k ]->hNextTwin = 0;
   }

   SysFreeMemory( hEIBuffer );

   return( 0 );
}

//./ ADD NAME=OrderEntityForView
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:  OrderEntityForView
//
//  PARAMETERS:
//            zView         - View of the object to order
//            cpcEntityName - Name of the entity to order
//            cpcOrderKeys  - String of paired 'words', consisting of
//                            "AttributeName x", where x is A for
//                            ascending, or D for descending. i.e.,
//                            "LastName A FirstName A".
//
//                            A context may be specified for the sorting
//                            attribute by putting the context name in square
//                            brackets ("[" and "]" after the sort order:
//                              "LastName A State A [Abbrev]"
//
//  RETURNS:  0            sort successfull
//            zCALL_ERROR  error in call
//
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 4
zSHORT OPERATION
OrderEntityForView( zVIEW     zView,
                    zCPCHAR   cpcEntityName,
                    zCPCHAR   cpcOrderKeys )
{
   LPVIEWENTITY       lpViewEntity;
   LPVIEWENTITY       lpTempViewEntity;
   LPVIEWENTITYCSR    lpViewEntityCsr;
   LPENTITYINSTANCE   lpEntityInstance;
   LPTASK             lpCurrentTask;
   ViewAttrListRecord lpViewAttrList[ 1024 ] = {0};
   LPVIEWATTRLIST     lpViewAttrListPtr = 0;
   zCHAR              szWorkString[ 4096 ];
   zCHAR              chOrder;
   zPCHAR             pchWSPtr = 0;
   zPCHAR             pchWSBuffer = 0;
   zPCHAR             pchEntityName;
   zPCHAR             pchAttrName;
   zPCHAR             pchScan;
   zBOOL              bBubbleSort;
   zBOOL              bAutoSeq = FALSE;
   zLONG              lTemp;
   zSHORT             nRC = zCALL_ERROR;

   // Validate task and entity ... ensure entity cursor is established.

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iOrderEntityForView,
                                          zView, zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

// TraceLine( "OrderEntityForView Entity: %s   OrderKeys: %s",
//            cpcEntityName, cpcOrderKeys );

// SetEntityCursor( zView, cpcEntityName, 0, zPOS_FIRST, 0, 0, 0, 0, 0, 0 ); does nothing

   lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, zView, cpcEntityName, 0 );
   if ( lpViewEntity == 0 )
   {
      fnOperationReturn( iOrderEntityForView, lpCurrentTask );
      return( zCALL_ERROR );
   }

   if ( lpViewEntity->bAutoSeq )  // added dks 2006.07.31 because this entity may be the
      bAutoSeq = TRUE;            // only AutoSeq entity

   lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
   if ( lpEntityInstance == UNSET_CSR )
      lpEntityInstance = fnEstablishCursorForView( lpViewEntityCsr );

   if ( lpEntityInstance == 0 )
      goto EndOfFunction;

#if 0
   lpTempViewEntity = zGETPTR( lpEntityInstance->hViewEntity );
   if ( lpTempViewEntity && lpTempViewEntity != lpViewEntity &&
        lpTempViewEntity->bRecursive )
   {
      LPVIEWENTITY lpTempViewEntityParent = lpTempViewEntity;

      while ( lpTempViewEntityParent->hParent )
      {
         lpTempViewEntityParent = zGETPTR( lpTempViewEntity->hParent );
         if ( lpTempViewEntityParent->lEREntTok == lpTempViewEntity->lEREntTok &&
              lpTempViewEntityParent == lpViewEntity )
         {
#if 0
            // Found same entity at another level.
            fnResetCursorForViewChildren( lpViewEntityCsr );
            lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, zView,
                                              cpcEntityName, 0 );
            lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
#endif
         // lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, zView,
         //                                   lpTempViewEntity->szName, 0 );
            break;
         }
      }
   }
#endif

   // Check to see if user wants a bubble sort instead of the (default)
   // quicksort.  Note that the only reason to use a bubble sort instead of
   // quicksort is to maintain sort order on previously sorted items.
   // Quicksort will switch items that compare equal, bubble sort will not.
   if ( zstrncmpi( cpcOrderKeys, ".bubblesort ", 12 ) == 0 )
   {
      bBubbleSort = TRUE;
      cpcOrderKeys += 12;
   }
   else
      bBubbleSort = FALSE;

   lpViewAttrListPtr = lpViewAttrList;

   lTemp = zstrlen( cpcOrderKeys ) + 1;
   if ( lTemp > zsizeof( szWorkString ) )
   {
      pchWSBuffer = (zPCHAR) fnAllocDataspace( lpCurrentTask->hFirstDataHeader,
                                               lTemp, 0, 0, iBuffer );
      pchWSBuffer = zGETPTR( pchWSBuffer );
      pchWSPtr = pchWSBuffer;
   }
   else
      pchWSPtr = szWorkString;

   strcpy_s( pchWSPtr, lTemp, cpcOrderKeys );

   // Validate each of the attributes in the sort list.
   for ( pchScan = pchWSPtr; *pchScan; )
   {
      // Initialize current AttrList entry ... done above at instantiation
   // lpViewAttrListPtr->bOrder = FALSE; // order ascending by default
   // lpViewAttrListPtr->pfObjectOper = 0;
   // lpViewAttrListPtr->pszContextName = 0;
   // lpViewAttrListPtr->lpViewAttrib = 0;  // this gets set for sure

      while ( *pchScan == ' ' || *pchScan == ',' )
         pchScan++;

      pchAttrName = pchScan;  // save pointer to attr name
      while ( *pchScan != ' ' && *pchScan != 0 )
         pchScan++;

      if ( *pchScan )     // if space is found,
         *pchScan++ = 0;  // null terminate

      if ( *pchAttrName == 0 )
         break;

      // Check to see if the attribute name also has an entity name.  It
      // should be seperated from the attr name by a '.'.
      pchEntityName = zstrchr( pchAttrName, '.' );
      if ( pchEntityName )
      {
         // We have an entity name.
         *pchEntityName = 0;       // change '.' to null
         lpTempViewEntity = fnValidViewEntity( &lpViewEntityCsr, zView,
                                               pchAttrName, 0 );
         if ( lpTempViewEntity == 0 )
            goto EndOfFunction;

         // Change attr pointer to point to beginning of attr name.
         pchAttrName = pchEntityName + 1;
      }
      else
      {
         // No entity name specified so use default entity.
         lpTempViewEntity = lpViewEntity;
      }

   // if ( lpTempViewEntity->bAutoSeq ) // dropped dks/don 2006.07.31 since we
   //    bAutoSeq = TRUE;               // believe only sort entity should be considered

      lpViewAttrListPtr->lpViewAttrib =
                fnValidViewAttrib( zView, lpTempViewEntity, pchAttrName, 0 );
      if ( lpViewAttrListPtr->lpViewAttrib == 0 )
         goto EndOfFunction;

      while ( *pchScan == ' ' || *pchScan == ',' )
         pchScan++;

      // Is there an order character present?
      if ( pchScan && *pchScan )
      {
         chOrder = ztoupper( *pchScan );
         if ( (chOrder == 'A' || chOrder == 'D') &&
              (pchScan[ 1 ] == 0 || pchScan[ 1 ] == ' ' || pchScan[ 1 ] == ',') )
         {
            if ( chOrder == 'D' )
               lpViewAttrListPtr->bOrder = TRUE; // order descending

            pchScan++;
            while ( *pchScan == ' ' || *pchScan == ',' )
               pchScan++;
         }
      }

      // Check for a Context Name.  It should be surrounded by brackets.
      if ( *pchScan == '[' )
      {
         zSHORT idx = 0;

         pchScan++;   // Skip over bracket.
         while ( *pchScan == ' ' )
            pchScan++;

         if ( *pchScan != ']' )
            lpViewAttrListPtr->pszContextName = pchScan;

         while ( *pchScan && *pchScan != ']' )
         {
            // If we find a space we'll convert it into a null-terminator.
            // This will cause us to ignore trailing spaces.
            if ( *pchScan == ' ' )
               *pchScan = 0;

            pchScan++;
         }

         // If we found a closing bracket (only other possiblity is a 0) then
         // change it to a null-terminator and skip to next char.
         if ( *pchScan == ']' )
            *pchScan++ = 0;
      }

      lpViewAttrListPtr++;

   } // for ( pchScan = pchWSPtr; *pchScan; )

   // Initialize last AttrList entry ... done above at instantiation
// lpViewAttrListPtr->lpViewAttrib = 0;

   // Call the actual sort routine.
   nRC = fnOrderEntityForView( zView, lpEntityInstance,
                               lpViewAttrList, bBubbleSort );

   if ( nRC != zCALL_ERROR && bAutoSeq )
   {  // >>> RAD54278-1 BEGIN
      fnSetUpdateIndicator( 0, lpEntityInstance, 0, TRUE, TRUE, TRUE );
   }  // >>> RAD54278-1 END

EndOfFunction:

   if ( pchWSBuffer )
      fnFreeDataspace( pchWSBuffer );   // free work area

   fnOperationReturn( iOrderEntityForView, lpCurrentTask );
   return( nRC );
}

// Finds all attributes in lpViewEntity and adds them to lpAttribList.
//
// Returns: 0 - Attribs added.
//          1 - Attribs added but sorting is using autosequencing field.
//
zSHORT LOCALOPER
fnGetSortAttrsFromEntity( zVIEW          lpView,
                          zPLONG         plAttribCnt,
                          LPVIEWATTRLIST lpAttribList,
                          LPVIEWENTITY   lpViewEntity )
{
   LPVIEWATTRIB lpViewAttrib;

   // Loop through all the view attribs looking for default sorting attribs.
   // When one is found, add it to the attrib list.
   for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
         lpViewAttrib;
         lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
   {
      if ( lpViewAttrib->bAutoSeq )
      {
         *plAttribCnt = 1;
         lpAttribList[ 0 ].lpViewAttrib = lpViewAttrib;
         lpAttribList[ 0 ].bOrder = FALSE;

         // Make sure next attrib is 0.
         lpAttribList[ 1 ].lpViewAttrib = 0;

         return( 1 ); // There is only 1 autoseq attr per entity, so return.
      }
      else
      if ( lpViewAttrib->cSequencing > 0 )
      {
         zSHORT nSeq;

         nSeq = lpViewAttrib->cSequencing;
         if ( nSeq >= MAX_SEQ_ATTS )
         {
            LPTASK lpTask = zGETPTR( lpView->hTask );
            // "KZOEE013 - Internal operation call error"
            TraceLineS( "KZOEE013 - Internal operation call error: ",
                        "Maximum # of order attributes used" );
            fnIssueCoreError( lpTask, lpView, 16, 13, 0,
                              "Maximum # of order attributes used",
                              "fnOrderOI_ByDefaultAttribs" );
            return( zCALL_ERROR );
         }

         if ( *plAttribCnt < nSeq )
            *plAttribCnt = nSeq;

         lpAttribList[ nSeq - 1 ].lpViewAttrib = lpViewAttrib;
         if ( lpViewAttrib->bSequencingD )
            lpAttribList[ nSeq - 1 ].bOrder = TRUE;
      }
   } // for ( lpViewAttrib )...

   return( 0 );
}

//./ ADD NAME=fnOrderOI_ByDefaultAttribs
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnOrderOI_ByDefaultAttribs
//
//  PURPOSE:    To sort all entities that have Ordering attributes or
//              autosequence attributes.
//
//  PARAMETERS: lpView - View to sort.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT
fnOrderOI_ByDefaultAttribs( zVIEW lpView )
{
   struct EntityListStruct
   {
      LPVIEWENTITY   lpViewEntity;
      LPVIEWATTRLIST lpPtr;
   } EntityList[ MAX_SEQ_ENTS ];

   LPVIEWCSR          lpViewCsr;
   LPVIEWOI           lpViewOI;
   LPENTITYINSTANCE   lpEntityInstance;
   LPVIEWENTITY       lpViewEntity;
   ViewAttrListRecord AttribList[ MAX_SEQ_ATTS ];
   zLONG              lEntityCnt;
   zLONG              k;
   zSHORT             nRC;

   // Fill EntityList with zeros.
   zmemset( (zPVOID) EntityList, 0, sizeof( struct EntityListStruct ) * MAX_SEQ_ENTS );
   lEntityCnt = 0;

   lpViewCsr = zGETPTR( lpView->hViewCsr );
   lpViewOI  = zGETPTR( lpViewCsr->hViewOI );

   // For each of the entity instances, sort all groups of twin entities if
   // the entity instance is the first twin.
   for ( lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );
         lpEntityInstance;
         lpEntityInstance = zGETPTR( lpEntityInstance->hNextHier ) )
   {
      LPENTITYINSTANCE lpPrevHier;

      // Sort the group of entity instances if:
      //    o  The entity instance is supposed to be sorted AND
      //    o  The entity instance is the first twin (prev twin == 0) AND
      //    o  There are more than 1 twins (next twin != 0).

      // If EI has a prev twin then it's not the first twin so don't bother
      // sorting.
      if ( lpEntityInstance->hPrevTwin )
         continue;

      // If next twin is NULL then there is only one EI so there's nothing to
      // sort.
      if ( lpEntityInstance->hNextTwin == 0 )
         continue;

      lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

      // If this entity doesn't have sorting attributes then skip it.
      if ( lpViewEntity->bAutoSeq == FALSE && lpViewEntity->bAttrOrder == FALSE )
         continue;

      // If we get here then we're going to sort the twins.  Save the prev
      // hier EI of the current EI.  Once we are done sorting the EIs we can
      // quickly find the first twin by using the prev hier ptr.
      lpPrevHier = zGETPTR( lpEntityInstance->hPrevHier );

      // First check to see if this lpViewEntity has been sorted already.
      // If it has, then we already have the list of default sort attribs.
      k = 0;
      while ( EntityList[ k ].lpViewEntity != lpViewEntity && k < lEntityCnt )
         k++;

      // If k == lEntityCnt, then lpViewEntity has not been sorted yet.
      // Go through each of the lpViewAttribs for the lpViewEntity and
      // find all default sort attributes.
      if ( k == lEntityCnt )
      {
         zLONG  lAttribCnt;

         // If k >= MAX_SEQ_ENTS, then we have run out of space for entities.
         if ( k >= MAX_SEQ_ENTS )
         {
            LPTASK lpTask = zGETPTR( lpView->hTask );
            // "KZOEE013 - Internal operation call error"
            TraceLineS( "KZOEE013 - Internal operation call error: ",
                        "Out of space for entities" );
            fnIssueCoreError( lpTask, lpView, 16, 13, 0,
                              "Maximum # of order entities used",
                              "fnOrderOI_ByDefaultAttribs" );
            return( zCALL_ERROR );
         }

         // Zero out attribute list.
         lAttribCnt = 0;
         zmemset( (zPVOID) AttribList, 0,
                  sizeof( ViewAttrListRecord ) * MAX_SEQ_ATTS );

         // Find all the sorting attributes and add them to AttribList.
         nRC = fnGetSortAttrsFromEntity( lpView, &lAttribCnt, AttribList,
                                         lpViewEntity );

         // If nRC != 0 then sorting is done by using autosequencing fields
         // and there can be only one autoseq field per entity.  Otherwise
         // check to see if the entity is sorted using child attributes and
         // if so then add them to AttribList.
         if ( nRC == 0 && lpViewEntity->bAttrOrderChild )
         {
            LPVIEWENTITY lpSrchViewEntity = zGETPTR( lpViewEntity->hNextHier );

            while ( lpSrchViewEntity &&
                    lpSrchViewEntity->nLevel > lpViewEntity->nLevel )
            {
               // We can only sort using children that have a max cardinality
               // of 1.  If it's greater than 1 then we can ignore it and all
               // it's children.
               if ( lpSrchViewEntity->uCardMax > 1 )
               {
                  zSHORT nChildLevel;

                  // Entity doesn't have a twin so use next hier pointers to
                  // skip the children.
                  nChildLevel = lpSrchViewEntity->nLevel;
                  for ( lpSrchViewEntity = zGETPTR( lpSrchViewEntity->hNextHier );
                        lpSrchViewEntity;
                        lpSrchViewEntity = zGETPTR( lpSrchViewEntity->hNextHier ) )
                  {
                     if ( lpSrchViewEntity->nLevel > nChildLevel )
                        break;
                  }

                  continue;
               }

               // If we get here then the max card is 1.
               fnGetSortAttrsFromEntity( lpView, &lAttribCnt, AttribList,
                                         lpSrchViewEntity );

               lpSrchViewEntity = zGETPTR( lpSrchViewEntity->hNextHier );

            } // while...

         } // if ( nRC == 0 && lpViewEntity->bAttrOrderChild )...

         // Allocate space to hold the attribute list.  We use
         // "lAttribCnt + 1" to allocate space for the NULL attribute.
         EntityList[ k ].lpPtr = (LPVIEWATTRLIST)
                   fnAllocDataspace( ((LPTASK) zGETPTR (lpView->hTask))->hFirstDataHeader,
                                     (sizeof( ViewAttrListRecord ) * (zULONG)
                                        (lAttribCnt + 1)), 0, 0, iBuffer );
         if ( EntityList[ k ].lpPtr == 0 )
            return( zCALL_ERROR );

         EntityList[ k ].lpPtr = zGETPTR( EntityList[ k ].lpPtr );

         // Copy attribute list + NULL attribute to entity list.
         zmemcpy( (zPVOID) EntityList[ k ].lpPtr, (zPVOID) AttribList,
                  sizeof( ViewAttrListRecord ) * (lAttribCnt + 1) );
         EntityList[ k ].lpViewEntity = lpViewEntity;

         lEntityCnt++;

      } // if ( k == lEntityCnt )...

      nRC = fnOrderEntityForView( lpView, lpEntityInstance,
                                  EntityList[ k ].lpPtr, FALSE );
      if ( nRC == zCALL_ERROR )
      {
         for ( k = 0; k < lEntityCnt; k++ )
            fnFreeDataspace( EntityList[ k ].lpPtr );

         return( nRC );
      }

      // Set lpEntityInstance to be the first twin in its particular group.
      if ( lpPrevHier )
         lpEntityInstance = zGETPTR( lpPrevHier->hNextHier );
      else
         lpEntityInstance = zGETPTR( lpViewOI->hRootEntityInstance );

   } // for ( lpEntityInstance )...

   for ( k = 0; k < lEntityCnt; k++ )
      fnFreeDataspace( EntityList[ k ].lpPtr );

   return( 0 );

} // fnOrderOI_ByDefaultAttribs

//./ ADD NAME=OrderOI_ByDefaultAttribs
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      OrderOI_ByDefaultAttribs
//
//  PURPOSE:    To sort all entities that have Ordering attributes or
//              autosequence attributes.
//
//  RETURNS:    0 - Entities sorted OK.
//              1 - No entities with AutoSeq set.
//              zCALL_ERROR - oops.
//
//  PARAMETERS: lpView - View to sort.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
OrderOI_ByDefaultAttribs( zVIEW lpView )
{
   LPTASK            lpCurrentTask;
   LPVIEWOD          lpViewOD;
   zSHORT            nRC;

   // validate some stuff

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iOrderOI_ByDefaultAttribs,
                                           lpView, zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   lpViewOD = zGETPTR( lpView->hViewOD );
   if ( lpViewOD->bAutoSeq == FALSE )
      nRC = 1;
   else
      nRC = fnOrderOI_ByDefaultAttribs( lpView );

   fnOperationReturn( iOrderOI_ByDefaultAttribs, lpCurrentTask );
   return( nRC );

} // OrderOI_ByDefaultAttribs

//./ ADD NAME=fnOrderEntitiesByDefaultAttribs
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      fnOrderEntitiesByDefaultAttribs
//
//  PURPOSE:    To sort the entity instances that are twins of the defined
//              entity instance using the default ordering attributes.
//
//  PARAMETERS: lpView - View to sort.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zSHORT
fnOrderEntitiesByDefaultAttribs( zVIEW            lpView,
                                 LPENTITYINSTANCE lpEntityInstance )
{
   ViewAttrListRecord AttribList[ 40 ]; // Max 40 attribs for sorting.
   LPVIEWENTITY       lpViewEntity;
   LPVIEWENTITY       lpTopViewEntity;
   LPVIEWATTRIB       lpViewAttrib;
   zLONG              lAttribCnt;
   zSHORT             nRC;

   // Find first twin of lpEntityInstance.
   while ( lpEntityInstance->hPrevTwin )
      lpEntityInstance = zGETPTR( lpEntityInstance->hPrevTwin );

   lpTopViewEntity = lpViewEntity = zGETPTR( lpEntityInstance->hViewEntity );

   // Sort the group of entity instances if:
   //   - The entity instance is supposed to be sorted AND
   //   - There are more than 1 twins (next twin != 0).
   if ( lpViewEntity->bAttrOrder == FALSE && lpViewEntity->bAutoSeq == FALSE )
      return( 0 ); // No sorting for entity.

   if ( lpEntityInstance->hNextTwin == 0 )
      return( 0 ); // Nothing to sort.

   zmemset( (zPVOID) AttribList, 0, sizeof( ViewAttrListRecord ) * 40 );
   lAttribCnt = 0;

   // Loop through all the attributes for the current entity and possibly
   // loop through the attrs for child entities.
   for ( ;
         lpViewEntity->nLevel > lpTopViewEntity->nLevel ||
            lpViewEntity == lpTopViewEntity;
         lpViewEntity = zGETPTR( lpViewEntity->hNextHier ) )
   {
      for ( lpViewAttrib = zGETPTR( lpViewEntity->hFirstOD_Attrib );
            lpViewAttrib;
            lpViewAttrib = zGETPTR( lpViewAttrib->hNextOD_Attrib ) )
      {
         zSHORT nSeq;

         // Forget about it if no sequencing value.
         if ( lpViewAttrib->cSequencing == 0 )
            continue;

         nSeq = lpViewAttrib->cSequencing;
         if ( nSeq > 40 )
         {
            LPTASK lpTask = zGETPTR( lpView->hTask );
            // "KZOEE013 - Internal operation call error"
            TraceLineS( "KZOEE013 - Internal operation call error: ",
                        "Sequencing error > 40" );
            fnIssueCoreError( lpTask, lpView, 16, 13, 0,
                              "Maximum # of order attributes used",
                              "fnOrderEntitiesByDefaultAttribs" );
            return( zCALL_ERROR );
         }

         if ( lAttribCnt < nSeq )
            lAttribCnt = nSeq;

         AttribList[ nSeq - 1 ].lpViewAttrib = lpViewAttrib;
         if ( lpViewAttrib->bSequencingD )
            AttribList[ nSeq - 1 ].bOrder = TRUE;

      } // for ( lpViewAttrib )...

      // If the top level entity isn't ordered by child entity attributes then
      // we can break this loop.
      if ( lpTopViewEntity->bAttrOrderChild == FALSE )
         break;

   } // for ( lpViewEntity )...

   if ( lAttribCnt > 0 )
   {
      nRC = fnOrderEntityForView( lpView, lpEntityInstance, AttribList, FALSE );
      if ( nRC == zCALL_ERROR )
         return( nRC );
   }

   return( 0 );

} // fnOrderEntitiesByDefaultAttribs

//./ ADD NAME=OrderEntitiesByDefaultAttribs
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      OrderEntitiesByDefaultAttribs
//
//  PURPOSE:    To sort the entity instances that are twins of the current
//              entity instance using the default ordering attributes.
//
//  PARAMETERS: lpView - View to sort.
//              pchEntityName - Entity to sort under it's parent.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 2
zSHORT OPERATION
OrderEntitiesByDefaultAttribs( zVIEW lpView, zPCHAR pchEntityName )
{
   LPTASK            lpCurrentTask;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPENTITYINSTANCE  lpEntityInstance;
   LPVIEWENTITY      lpViewEntity;
   zSHORT            nRC;

   // validate some stuff

   // If task not active or disabled, or view csr invalid, return zCALL_ERROR.
   if ( (lpCurrentTask = fnOperationCall( iOrderEntitiesByDefaultAttribs,
                                          lpView, zVALID_VIEW_CSR )) == 0 )
   {
      return( zCALL_ERROR );
   }

   lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, lpView, pchEntityName, 0 );
   if ( lpViewEntity == 0 )
   {
      fnOperationReturn( iOrderEntitiesByDefaultAttribs, lpCurrentTask );
      return( zCALL_ERROR );
   }

   lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
   if ( (zLONG) lpEntityInstance == 1 )
   {
      TraceLineS( "Ordering attributes -- resetting entity cursor.", "" );
      fnEstablishCursorForView( lpViewEntityCsr );
      lpViewEntity = fnValidViewEntity( &lpViewEntityCsr, lpView, pchEntityName, 0 );
      if ( lpViewEntity == 0 )
      {
         fnOperationReturn( iOrderEntitiesByDefaultAttribs, lpCurrentTask );
         return( zCALL_ERROR );
      }

      lpEntityInstance = zGETPTR( lpViewEntityCsr->hEntityInstance );
      if ( lpEntityInstance == UNSET_CSR || lpEntityInstance == NULL_CSR )
      {
         // "KZOEE013 - Internal operation call error"
         TraceLineS( "KZOEE013 - Internal operation call error: ",
                     "Unset or Null Cursor" );
         fnIssueCoreError( lpCurrentTask, lpView, 8, 13, 0, "OrderEntities", 0 );
         nRC = zCALL_ERROR;
      }
      else
         nRC = fnOrderEntitiesByDefaultAttribs( lpView, lpEntityInstance );
   }
   else
   if ( lpEntityInstance )
      nRC = fnOrderEntitiesByDefaultAttribs( lpView, lpEntityInstance );
   else
   {
      TraceLineS( "Ordering attributes -- Entity cursor is null!", "" );
      nRC = 0;
   }

   fnOperationReturn( iOrderEntitiesByDefaultAttribs, lpCurrentTask );
   return( nRC );

} // OrderEntitiesByDefaultAttribs

//./ ADD NAME=fnGetObjCnstrntOper
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:    fnGetObjCnstrntOper
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 3
zPOCEOPER
fnGetObjCnstrntOper( zVIEW    lpView,
                     LPTASK   lpCurrentTask )
{
   LPTASK      hCurrentTask = zGETHNDL( lpCurrentTask );
   LPVIEWOD    lpViewOD;
   LPLIBRARY   hLibrary;
   LPTASKOPER  lpTaskOperation;
   zPVOID      hTaskOperation;
   zPCHAR      pchOperLibName;
   zLONG       lProcessID = SysGetProcessID( 0 );

   // No Object Constraint operation pointer, return 0 ==> not found.
   lpViewOD = zGETPTR( lpView->hViewOD );
   if ( lpViewOD->szOCEOpername[ 0 ] == 0 )
      return( 0 );

   for ( lpTaskOperation = zGETPTR( lpViewOD->hFirstTaskOperation );
         lpTaskOperation;
         lpTaskOperation = zGETPTR( lpTaskOperation->hNextTaskOperationForOEA ) )
   {
      if ( lpTaskOperation->hTask == hCurrentTask &&
           lpTaskOperation->lProcessID == lProcessID )
      {
         return( (zPOCEOPER) lpTaskOperation->pfnTaskOper );
      }
   }

   // No task object oper exists yet, create one if possible.
   pchOperLibName = lpViewOD->szOperLibname;
   if ( pchOperLibName == 0 || pchOperLibName[ 0 ] == 0 )
      return( 0 );

   hLibrary = SysLoadLibrary( lpView, pchOperLibName );

   if ( hLibrary )
   {
      zBOOL bMutexLocked;

      hTaskOperation = fnAllocDataspace( AnchorBlock->hMainFirstDataHeader,
                                         sizeof( TaskOperationRecord ), 1, 0,
                                         iTaskOperation );
      if ( hTaskOperation == 0 )
         return( 0 );

      lpTaskOperation              = zGETPTR( hTaskOperation );
      lpTaskOperation->hViewOD     = lpView->hViewOD;
      lpTaskOperation->hTask       = hCurrentTask;
      lpTaskOperation->lProcessID  = lProcessID;

      // Set pointers for TaskOperation chain off of Task structure
      // Note: this is a single linked list
      if ( hCurrentTask == AnchorBlock->hMainTask )
      {
         bMutexLocked = TRUE;
         zLOCK_MUTEX( zMUTEX_ANCHORBLOCK );
      }
      else
         bMutexLocked = FALSE;

      lpTaskOperation->hNextTaskOperationForTask =
                                          lpCurrentTask->hFirstTaskOperation;
      lpCurrentTask->hFirstTaskOperation = hTaskOperation;

      if ( bMutexLocked )
         zUNLOCK_MUTEX( zMUTEX_ANCHORBLOCK );

      lpTaskOperation->pfnTaskOper = SysGetProc( hLibrary,
                                                 lpViewOD->szOCEOpername );

      // Set pointers for TaskOperation chain off of ViewOD structure
      // Note: this is a double linked list
      if ( lpViewOD->hLastTaskOperation )
      {
         LPTASKOPER lpLastTaskOperation =
                                     zGETPTR( lpViewOD->hLastTaskOperation );

         lpLastTaskOperation->hNextTaskOperationForOEA = hTaskOperation;
         lpTaskOperation->hPrevTaskOperationForOEA =
                                                lpViewOD->hLastTaskOperation;
         lpViewOD->hLastTaskOperation = hTaskOperation;
      }
      else
      {
         lpViewOD->hFirstTaskOperation = hTaskOperation;
         lpViewOD->hLastTaskOperation  = hTaskOperation;
      }
   }
   else
      return( 0 );

   return( (zPOCEOPER) lpTaskOperation->pfnTaskOper );
}

//./ ADD NAME=fnInvokeOCEOperation
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:   fnInvokeOCEOperation
//
// PURPOSE: Invoke the Object Constraint operation for a given Object Def
//
// RETURNS:
//                   0 - Constraint handler says okay.
//   zCONSTRAINT_ERROR - Constraint handler detected an error situation.
//         zCALL_ERROR - Operation failed.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT
fnInvokeOCEOperation( zVIEW        lpView,
                      LPTASK       lpCurrentTask,
                      zSHORT       nEvent,
                      zSHORT       nState )
{
   zPOCEOPER   pfn;

   pfn = fnGetObjCnstrntOper( lpView, lpCurrentTask );
   if ( pfn )
      return( (zSHORT) (*pfn)( lpView, nEvent, nState ) );

   return( 0 );
}

void LOCALOPER
fnQualError( zPCHAR pchCommand, zSHORT nErrorNbr )
{
   TraceLineS( "Error occurs after: ", pchCommand );
   SysMessageBox( 0, szlOE_SystemError,
                  "Error parsing command.  See trace for more.", 1 );
}

#define ACTIVATE     1
#define WHERE        2
#define QUAL         3

//./ ADD NAME=CreateQualFromCommand
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
// ENTRY:   CreateQualFromCommand
//
// PURPOSE: Creates a qualification object from an 'ACTIVATE' command.
//          This operation does no checking for valid entity/attr names.
//
// RETURNS:
//                   0 - Qual OI created OK.
//         zCALL_ERROR - Operation failed.
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT VARYOPER
CreateQualFromCommand( zPVIEW pvReturnView,
                       zPCHAR pchOD_Name,
                       zVIEW  vSubtask,
                       zPCHAR pchCommand,
                       zLONG  lControl, ... )
{
   va_list     vaList;
   LPVIEWOD    lpViewOD;
   zVIEW       vQual = 0;
   zPCHAR      pch;
   zCHAR       szActivateView[ zZEIDON_NAME_LTH + 1 ];
   zSHORT      nExpecting = ACTIVATE;
   zSHORT      nRC = zCALL_ERROR;  // We'll assume an error.

   va_start( vaList, lControl );

   lpViewOD = ActivateViewObject( vSubtask, pchOD_Name, FALSE );
   if ( lpViewOD == 0 )
      goto EndOfFunction;

   // Create an empty qualification.
   if ( SfActivateSysEmptyOI( &vQual, "KZDBHQUA", vSubtask, zMULTIPLE ) != 0 )
      goto EndOfFunction;

   pch = pchCommand;
   while ( *pch )
   {
      // skip blanks.
      if ( zisspace( *pch ) )
      {
         pch++;
         continue;
      }

      switch ( ztoupper( *pch ) )
      {
         case 'A':
            if ( zstrncmpi( pch, "ACTIVATE ", 9 ) == 0 )
            {
               zSHORT       k;
               LPVIEWENTITY lpViewEntity;

               if ( nExpecting != ACTIVATE )
               {
                  fnQualError( pch, 0 );
                  goto EndOfFunction;
               }

               // Skip over activate text.
               pch += 9;

               // Get activate view name.
               for ( k = 0; !zisspace( *pch ) && *pch != 0 ; pch++, k++ )
               {
                  if ( k > zZEIDON_NAME_LTH )
                  {
                     fnQualError( pch, 0 );
                     goto EndOfFunction;
                  }

                  szActivateView[ k ] = *pch;
               }

               lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
               CreateEntity( vQual, "EntitySpec", zPOS_NEXT );
               SetAttributeFromString( vQual, "EntitySpec", "EntityName",
                                       lpViewEntity->szName );

               nExpecting = WHERE;
            }
            else
            {
               fnQualError( pch, 0 );
               goto EndOfFunction;
            }

            break;

         case 'W':
            if ( zstrncmpi( pch, "WHERE ", 6 ) == 0 )
            {
               if ( nExpecting != WHERE )
               {
                  fnQualError( pch, 0 );
                  goto EndOfFunction;
               }

               // Skip over where text.
               pch += 6;

               nExpecting = QUAL;
            }
            else
            {
               fnQualError( pch, 0 );
               goto EndOfFunction;
            }

            break;

      } // switch ( ztoupper( *pch ) )...

   } // while ( *pch )...

   // If we get here then everything's good.
   nRC = 0;

EndOfFunction:
   va_end( vaList );

   // We need to clean up a little more if we have an error.
   if ( nRC == zCALL_ERROR )
   {
      if ( vQual )
         DropObjectInstance( vQual );
   }

   return( nRC );
}

//./ ADD NAME=UUENCODE_NextEncodedLine
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UUENCODE_NextEncodedLine
//
//  PURPOSE:    To UUENCODE a buffer by returning lines until the buffer has
//              been completely processed.  In general, the operation is
//              intitally called with a buffer position of zero and then
//              subsequent calls will proceed from the 'current' position.
//
//  PARAMETERS: pchLineOut    - Pointer to line (buffer) for the returned
//                              encoded line.  Must be at least 62 bytes.
//              pchBuffer     - Pointer to buffer being encoded
//              ulBufferLth   - Total length of buffer to be encoded.
//              pulBufferPos  - Offset into the buffer that is to be
//                              encoded in this invocation
//
//  RETURNS:    0 - No more data to be encoded.
//                   (Note: pchLineOut will be "`" and to comply with the
//                          standard, it must be written as terminator)
//              1 - Line has been returned and there is more data in the
//                   buffer to be processed.
//  SAMPLE CODE:
//       while ( UUENCODE_NextEncodedLine( szLine, szBuffer,
//                                         lBufLth, &lBufPos ) == 1)
//         {
//            TraceLineS( "Encoded Line: ", szLine);
//         }
//         TraceLineS( "Terminal Line: ", szLine);
//
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT  OPERATION
UUENCODE_NextEncodedLine( zPCHAR  pchLineOut,
                          zPCHAR  pchBuffer,
                          zULONG  ulBufferLth,
                          zPULONG pulBufferPos )
{

// The encode macro masks the lower 6 bits and adds 32 (a space), but
// it translates a binary zero to a "`" rather than leaving it a space.
// This is the generally accepted current technique (although not in the standard).
#define ENC(c) ((c) ? ((c) & 0x3F) + 0x20: 0x60)

   zSHORT k, nChars;
   zCHAR  c;
   register zPCHAR pchIn;
   register zPCHAR pchOut;

   pchOut = pchLineOut;
   nChars = (zSHORT) (ulBufferLth - *pulBufferPos);
   if ( nChars <= 0 )
   {
      // Buffer encoding complete
      *pchOut++ = '`';
      *pchOut = 0;
      return( 0 );
   }

   if ( nChars > 45 )
      nChars = 45;

   // store the length as the first byte encoded
   *pchOut++ = ENC( nChars );
   pchIn = pchBuffer + *pulBufferPos;
   for ( k = nChars; k > 0; k -= 3, pchIn += 3 )
   {
      c = *pchIn >> 2;
      *pchOut++ = ENC( c );

      if ( k == 1 )
      {
         // only one byte valid - use 0 for next 2 input bytes
         c = (*pchIn << 4) & 0x30;
         *pchOut++ = ENC( c );
         *pchOut++ = ENC( 0 );
         *pchOut++ = ENC( 0 );
      }
      else
      if ( k == 2 )
      {
         // only 2 bytes valid - use 0 for last input byte
         c = ((*pchIn << 4) & 0x30) | ((pchIn[ 1 ] >> 4) & 0x0F);
         *pchOut++ = ENC( c );
         c = (pchIn[ 1 ] << 2) & 0x3C;
         *pchOut++ = ENC( c );
         *pchOut++ = ENC( 0 );
      }
      else
      {
         // all 3 bytes valid - use all 3 input bytes for the 4 output bytes
         c = ((*pchIn << 4) & 0x30) | ((pchIn[ 1 ] >> 4) & 0x0F);
         *pchOut++ = ENC( c );
         c = ((pchIn[ 1 ] << 2) & 0x3C) | ((pchIn[ 2 ] >> 6) & 0x03);
         *pchOut++ = ENC( c );
         c = pchIn[ 2 ] & 0x3F;
         *pchOut++ = ENC( c );
      }
   }

   *pulBufferPos = *pulBufferPos + nChars;
   *pchOut = 0;

   return( 1 );
}

//./ ADD NAME=UUDECODE_NextLineToBuffer
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      UUDECODE_NextLineToBuffer
//
//  PURPOSE:    To UUDECODE a line that was created by UUENCODE into a
//              buffer.  In general, the operation is called intitally
//              with a buffer position of zero and then subsequent calls
//              will decode each new line passed in and add it to the
//              end of the buffer.
//
//  PARAMETERS: pchEncodedLine - Line to be decoded.
//              pchBuffer     - Pointer to buffer being filled with
//                              decoded data.
//              ulBufferLth   - Total length of buffer to be filled.
//              pulBufferPos  - Offset into the buffer for this invocation.
//
//  RETURNS:
//             0 to 45 - Success: Number of bytes added to buffer,
//         zCALL_ERROR - Operation failed
//                       a. no room left in buffer.
//                       b. line is invalid length.
//
//
//  SAMPLE CODE:  Decode one line at a time with minimal 45 byte buffer
//       while ( SysReadLine( lpView, &pchLine, hFile )
//       {
//          uPos = 0;  // keep resetting for small buffer
//          nRC = UUDECODE_NextLineToBuffer( pchLine,
//                                           szDecodeBuffer,
//                                             45, &uPos );
//            if ( nRC < 0 )
//            {
//               TraceLineI( "Error UUDECODE_NextLineToBuffer: ", nRC );
//               break;
//            }
//            if ( nRC == 0 ) // terminating line "`" found
//               break;
//            //TraceLineS( "Decoded Line: ", pchLine);
//          SysWriteLineLth( hFile2, szDecodeBuffer, nRC, FALSE );
//         }
/////////////////////////////////////////////////////////////////////////////
//./ END + 5
zSHORT  OPERATION
UUDECODE_NextLineToBuffer( zPCHAR  pchEncodedLine,
                           zPCHAR  pchBuffer,
                           zULONG  ulBufferLth,
                           zPULONG pulBufferPos )
{

// The decode macro subtracts 32 (a space) and masks the lower 6 bits
#define DEC(c)  (((c) - 0x20) & 0x3F)

   zSHORT k, nChars, nAvail;
   register zPCHAR pchIn;
   register zPCHAR pchOut;

   nAvail = (zSHORT) (ulBufferLth - *pulBufferPos);
   pchIn = pchEncodedLine;
   nChars = DEC( *pchIn );
   if ( nChars == 0 )
      return( 0 );

   if ( nChars > nAvail || nChars > 45 )
   {
      // no room left in buffer or invalid line length.
      return( zCALL_ERROR );
   }

   // check line length is correct
   //    this can be eliminated if it is too much overhead
   if ( (zUSHORT) zstrlen( pchEncodedLine ) != (zUSHORT) (((((nChars - 1) / 3) + 1) * 4) + 1))
   {
      return( zCALL_ERROR );
   }

   // fill the buffer (4 bytes go to 3)
   pchOut = pchBuffer + *pulBufferPos;
   for ( pchIn++, k = nChars; k > 0; pchIn += 4, k -= 3 )
   {
      if ( k >= 3 )
      {
         *pchOut++ = DEC (*pchIn) << 2 | DEC (pchIn[ 1 ]) >> 4;
         *pchOut++ = DEC (pchIn[ 1 ]) << 4 | DEC (pchIn[ 2 ]) >> 2;
         *pchOut++ = DEC (pchIn[ 2 ]) << 6 | DEC (pchIn[ 3 ]);
      }
      else
      {
         if ( k >= 1 )
         {
            *pchOut++ = DEC (*pchIn) << 2 | DEC (pchIn[ 1 ]) >> 4;
         }

         if ( k >= 2 )
         {
            *pchOut++ = DEC (pchIn[ 1 ]) << 4 | DEC (pchIn[ 2 ]) >> 2;
         }
      }
   }

   *pulBufferPos = *pulBufferPos + nChars;

   return( nChars );
}

/////////////////////////////////////////////////////////////////////////////
//
// fnInitViewArrayBlock
//
// initialize ViewArrayBlock
//
// RETURNS:  0 ==> OK
//           zCALL_ERROR otherwise
//
/////////////////////////////////////////////////////////////////////////////
static zSHORT
fnInitViewArrayBlock( VIEWARRAYBLOCK *pViewArrayBlock,
                      zLONG nViewCount )
{
   zPVOID *pv;
   zLONG nViewCount1 = nViewCount + 1; // we need a trailing NULL pointer

   zmemset( pViewArrayBlock, 0, sizeof(VIEWARRAYBLOCK) );

   if ( nViewCount > 1 )
   {
      // allocate 5 PVOID arrays of size nViewCount + 1
      pv = SysMalloc( 5 * nViewCount1 * sizeof( zPVOID ) );
      if ( pv == 0 )
         return( zCALL_ERROR );
   }
   else
   {
      // Usually there is only 1 view in the cluster ... in which case we
      // we do NOT malloc for performance reasons.
      pv = pViewArrayBlock->pvDyn;
   }

   pViewArrayBlock->lCount = nViewCount1;
   pViewArrayBlock->pvArray = (zVIEW *) pv;
   pViewArrayBlock->pViewOI_Array = (LPVIEWOI *)(pv + nViewCount1);
   pViewArrayBlock->pViewOD_Array = (LPVIEWOD *)(pv + 2 * nViewCount1);
   pViewArrayBlock->pbGenkeyNeededArray = (zBOOL *)(pv + 3 * nViewCount1);
   pViewArrayBlock->pbFK_NeededArray    = (zBOOL *)(pv + 4 * nViewCount1);

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// fnFreeViewArayBlock
//
// free ViewArrayBlock memory
//
// RETURNS:  0 ==> OK
//           zCALL_ERROR otherwise
//
/////////////////////////////////////////////////////////////////////////////
static void
fnFreeViewArrayBlock( VIEWARRAYBLOCK *pViewArrayBlock )
{
   if ( pViewArrayBlock->pvArray && pViewArrayBlock->lCount > 2 )
      SysFree( pViewArrayBlock->pvArray );

   zmemset( pViewArrayBlock, 0, sizeof( VIEWARRAYBLOCK ) );
}

//./ ADD NAME=GenerateQualFromEntityList
// Source Module=kzoeoiaa.c
/////////////////////////////////////////////////////////////////////////////
//
//  ENTRY:      GenerateQualFromEntityList
//
//  PURPOSE:    Generates a qualification object to load all the entities in
//              the supplied list of root entities.
//
//  PARAMETERS: pvQual        - Qual view that is passed back.
//              vEntityList   - View containing the entity list.
//              pchEntityName - Name of the entity.
//              pchScoping    - Scoping entity.
//              lControl      - Not currently used.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT  OPERATION
GenerateQualFromEntityList( zPVIEW pvQual,
                            zVIEW  vEntityList,
                            zPCHAR pchEntityName,
                            zPCHAR pchScoping,
                            zLONG  lControl )
{
   LPTASK            lpCurrentTask;
   LPVIEWENTITY      lpViewEntity;
   LPVIEWENTITY      lpScopingViewEntity;
   LPVIEWENTITYCSR   lpViewEntityCsr;
   LPVIEWENTITYCSR   lpScopingViewEntityCsr;
   LPVIEWATTRIB      lpKey;
   zVIEW             vQual;
   zSHORT            nRC;

   // Validate parameters
   if ( (nRC = fnValidateCursorParameters( &lpCurrentTask,
                                           &lpViewEntity,
                                           &lpScopingViewEntity,
                                           &lpViewEntityCsr,
                                           &lpScopingViewEntityCsr,
                                           iGenerateQualFromEntityList,
                                           vEntityList,
                                           pchEntityName,
                                           pchScoping )) != 0 )
   {
      return( nRC );
   }

   // Find the key attribute.
   for ( lpKey = zGETPTR( lpViewEntity->hFirstOD_Attrib );
         lpKey->bKey == FALSE;
         lpKey = zGETPTR( lpKey->hNextOD_Attrib ) )
   {
      // nothing needs to be done here
   }

   SfActivateSysEmptyOI( &vQual, "KZDBHQUA", vEntityList, zMULTIPLE );
   CreateEntity( vQual, "EntitySpec", zPOS_LAST );
   SetAttributeFromString( vQual, "EntitySpec", "EntityName", "*root*" );

   CreateEntity( vQual, "QualAttrib", zPOS_LAST );
   SetAttributeFromString( vQual, "QualAttrib", "EntityName", "*root*" );
   SetAttributeFromString( vQual, "QualAttrib", "AttributeName", lpKey->szName );
   SetAttributeFromString( vQual, "QualAttrib", "Oper", "=" );

   // Loop through the entities and copy the key values to the qual OI.
   for ( nRC = fnSetEntityCursor( vEntityList, lpViewEntity, lpViewEntityCsr,
                                  0, (zLONG) zPOS_FIRST,
                                  0, 0, 0, 0, lpScopingViewEntityCsr, 0,
                                  lpCurrentTask );
         nRC >= zCURSOR_SET;
         nRC = fnSetEntityCursor( vEntityList, lpViewEntity, lpViewEntityCsr,
                                  0, (zLONG) zPOS_NEXT,
                                  0, 0, 0, 0, lpScopingViewEntityCsr, 0,
                                  lpCurrentTask ) )
   {
      CreateEntity( vQual, "KeyList", zPOS_LAST );
      SetAttributeFromAttribute( vQual, "KeyList", "IntegerValue",
                                 vEntityList, pchEntityName, lpKey->szName );
   }

   // Reset the cursor back to the first entity.
   nRC = fnSetEntityCursor( vEntityList, lpViewEntity, lpViewEntityCsr,
                            0, (zLONG) zPOS_FIRST,
                            0, 0, 0, 0, lpScopingViewEntityCsr, 0,
                            lpCurrentTask );

   *pvQual = vQual;

   fnOperationReturn( iGenerateQualFromEntityList, lpCurrentTask );
   return( nRC );
}
