/////////////////////////////////////////////////////////////////////////////
//
// MODULE NAME:   tzvmp9aa.c - VML SubSystem Activate statement build
// DESCRIPTION:   This is the source file of the optimizing code
//
// //////////////////////////////////////////////////////////////////////////
// * Copyright (c) 1995 - 2016 QuinSoft, Inc.   All rights reserved.        *
// * Confidential and Proprietary material subject to license - do not      *
// * reproduce or disclose.  This material is an unpublished work and       *
// * is considered a trade secret belonging to the copyright holder.        *
// //////////////////////////////////////////////////////////////////////////
//
// AUTHOR:        Jeffrey S. Beam
// DATE:          1993/02/05
// API:           MicroSoft foundation classes and Windows 3.1 SDK
// ENVIRONMENT:   Windows 3.1
// REVISION:      0.9A   1995/08/30
//
// HISTORY:
//
//    1995/08/05: Beginning of 10B branch
//
/////////////////////////////////////////////////////////////////////////////
//

/*
CHANGE LOG
2003.10.19 DonC
   Modified BuildGetView so that the generated GetViewByName would always pass a view
   as the 3rd parameter, instead of a "0".
2002.03.15 HH
   R56501, fatal error if fnLocalBuildQual already there.
2000.09.27 HH
   ACTIVATE WHERE with parens - F50592
2000.09.09 HH
   improve GenerateLocalOperationName (number = ZKey).
2000.09.06 HH
   fix bug in GenerateLocalOperationName.
2000.09.17 HH
   do not show generated operations in list
2000.08.28 HH
   fix problem with operation returncodes.
2000.07.19  HH
   fix bug 51353, GET view xxx NAMED yyy, instead of "yyy" .
2000.06.14  HH
   strip quotes for NAME VIEW and GET VIEW NAMED.

OLD CHANGE LOG

07.06.1997  DonC
   Modified BuildWhereStatements to use a Decimal, Integer or String variables
   as parameters to the call to the build of the qualification object.
   Earlier code always used a String variable which gave erroneous results if
   an integer or decimal attribute was null instead of 0.

30.09.1997  DonC
   Modified SetupActivate to properly handle case where an Activate statement
   immediately follows a FOR statement.

19.06.1997  HH
   Modified fnBuildSetAttributeVariable to fix following bug:
   Given as an example
   ACTIVATE ... WHERE ... V.E.A1 >= xxx AND V.E.A2 <= xxx
   the 2. "xxx" (same variable!) was not handled right,
   because it was "already there" in the TZVSPOOO object.

21.08.1998  DonC
   In operation BuildWhereStatements, I added a statement to reset
   g_lAddNextStatementBefore flag to 0 because the Qual_X routine was being
   generated incorrectly when an ACTIVATE WHERE statement followed a FOR
   statement.

*/

#include "tzlodopr.h"
#include "tz__oprs.h"
#include "tzvsecaa.h"
#include "tzvmpopr.hg"
#include "ZeidonOp.H"

/////////////////////////////////////////////////////////////////////////////
//
// OPERATIONS: PositionAtCallingOperation
//             PositionAtNewOperation
//             SetupActivate
//             GenerateLocalOperationName
//             InsertActivateIntoCurrentOperation
//             InsertActivateNoWhere
//             InsertActivateEmpty
//             BuildCallToLocalFunction
//             BuildDropView
//             BuildActivateEmpty
//             BuildActivateEmptyLocal
//             BuildActivate
//             BuildWhereStatements
//             GetRootEntityName
//             GetStringForSQLOperator
//             BuildGetView
//             BuildNameView
//             BuildCommitView
//
/////////////////////////////////////////////////////////////////////////////

#define ADDEXPRESSIONENTRYTOSTRING( p1, p2, p3, p4, p5, p6 ) AddExpressionEntryToString( szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, p1, p2, p3, p4, p5, p6 )

zCHAR szLocal9Code[ MAXSTRING ];
zCHAR szLocal9Text[ MAXSTRING ];
zLONG lLocal9Code;
zLONG lLocal9Text;

zOPER_EXPORT zLONG OPERATION
BuildResetView( zVOID );

zOPER_EXPORT zLONG OPERATION
BuildSetView( zVOID );

static void
StripQuotes( zPCHAR pchString );

zLONG OPERATION
fnBuildSetAttributeConstant( zVIEW  vSubtask,
                             zPCHAR pchEntityName,
                             zPCHAR pchAttributeName,
                             zPCHAR pchAttributeValue );
static zLONG OPERATION
fnBuildSetAttributeVariable( zVIEW  vSubtask,
                             zPCHAR pchEntityName,
                             zPCHAR pchAttributeName,
                             zLONG  lVarID,
                             zLONG  lVarDataType );
zLONG OPERATION
fnBuildCreateEntity( zVIEW  vSubtask,
                     zPCHAR pchWhichEntity );

//
//   This module contains the code necessary to build an activate statement.
//   The Activate statement in vml is as follows.
//
//   The Activate statement needs to do several things. First, and most
//   obvious,  it must allow the user to fully specify the activation of
//   an object instance including any restrictions on what entities to load.
//   Secondly it must be able to create the code to build the qualifying
//   object. The syntax is as follows:
//
//            Activate_Keyword View_Identifier ( single_multiple }
//                  { Where_clause }
//                  { Restricting_Keyword Entity_Qualifier
//                           to_keyword Where_Clause }
//
//   The Activate_Keyword would be: ACTIVATE. The View_Identifier is the name
//   given to the view in the View declaration that must exist for the OI
//   that is to be activated. The where clause would be a standard VML where
//   clause that would specify the conditions by which to do the Activate.
//   The Restricting phrase would be used to qualify lower level ( child
//   entity ) activate restrictions. The Restricting_Keyword would be:
//   RESTRICTING followed by the entity qualifier that is to be restricted.
//   The where_clause would be a standard  VML where clause ( except that it
//   would use he word TO instead of where ) that would specify the conditions
//   by which to restrict the child.
//
//   The where clause that qualifies the root would be optional as well as the
//   restricting clause. If the first where clause is omitted then the
//   activate would be for a single root instance of the first instance from
//   the list of all available instances of that LOD type. If the restricting
//   clause is omitted, then all of the child entities associated with the
//   loaded root would also be loaded.
//
//   If the root is qualified with a where that is not exact and the keyword
//   zMULTIPLE is used,  then a multiple root load is performed. That is, if
//   the root key is qualified as a condition that could be met by more than
//   one entry, such as key > 32 etc. then the activate could be done as a
//   multiple root activate. Otherwise( if it is zSINGLE ) then only the first
//   instance meeting the criteria is done. This is also done if the root
//   entity is qualified via one of its children's keys.
//
//   One of the keywords single or multiple could be used after the View_name
//   to force that particular activate condition. If the single is used on an
//   activate that would normally be a multiple that the view returned
//   would still be single ( the way activate would return it ).
//
//   The restricting clause would be used to restrict which children of a
//   parent would be loaded with the parent. This could be qualified down to
//   any level as provided for in the Activate code. The restricting clause
//   is optional ( and probably rare ).
//
//   The restricting clause would be RESTRICTING Entity_Qualifier TO ...
//   The Entity_qualifier would be a child entity and the TO phrase would
//   be some conditional where clause.
//
//   All of the code necessary fot the building of the qualification object
//   will be put out into its own local function.
//
//   Algorythm for setting up the Activate Statement statements.
//
//   When we get the keyword ACTIVATE, first we "Freeze" the current PI view
//   to wherever it is currently. This is because all of the code to add
//   variables etc. is relative to the PI view so we need to save it. Once
//   This is done, we need to generate a name for the LocalOperation, create
//   the local operation and begin building the statements.
//
//   Next we create a view identifier that is to be loaded. Put this as the
//   first parameter in the local operation as a pointer to a view. This will
//   be the view to the qual object that gets built and passed back to the
//   calling operation. ( it will later have to be added to the local parms of
//   the calling operation. )
//
//   In the local operation we need an ActivateEmpty for the Qual object. This
//   must be the first statement in the local operation but we cannot put it
//   in untill we have all of the restricting clauses gathered incase it
//   needs to be a multiple load. We also need to create a create entity
//   spec for each entity that is qualified by a where or restrict. We then
//   need to create a QualAttribute for each attribute that is qualified on
//   as well as operators.
//

//
// OPERATION: SetupActivate
//
// DESCRIPTION: SetupActivate does some preliminay stuff. It saves the
//    current program instance counter, creates the name of the local
//    operation etc.
//
zOPER_EXPORT zLONG OPERATION
PositionAtCallingOperation( zVOID )
{
   SetViewFromView( g_lpPIView, g_vSavePIView );
   SetViewFromView( g_lpSGView, g_lpPIView );
   SetViewFromView( g_vStatementView, g_vSaveStmtView );
   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
PositionAtNewOperation( zVOID )
{
   SetViewFromView( g_vSaveStmtView, g_vStatementView );
   SetCursorNextEntity( g_lpSGView, "Operation", "" );
   SetCursorNextEntity( g_lpPIView, "Operation", "" );
   SetViewFromView( g_vStatementView, g_lpPIView );
   SetCursorLastEntity( g_vStatementView, "Statement", "" );
   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
SetupActivate( zVIEW vSubtask, zLONG lIDNumber )
{
   zCHAR  szLocalName[ 33 ];
   zLONG  lSaveParseLimit;
   zLONG  lDataType;
   zLONG  lDefineZKey;
   zLONG  lTempAddNextStatement;
   zLONG  lRC;

   // Need to freeze the current PIview.
   SetCursorFirstEntityByInteger( g_lpPIView, "Variable", "ID", lIDNumber, "" );
   CreateViewFromViewForTask( &g_vSavePIView, g_lpPIView, 0 );
   CreateViewFromViewForTask( &g_vSaveStmtView, g_vStatementView, 0 );

   // Need to create a name for the local operation.
   GenerateLocalOperationName( szLocalName, zsizeof( szLocalName ), "BuildQual" );

   // SetViewFromView( g_lpSGView, g_lpPIView );

   // Add the local operation.
   lSaveParseLimit = g_lParseLimit;
   g_lParseLimit = zPARSE_LIMIT_SIGNATURES;
   PreBuildOperation( qLOCAL, -1 );
   lRC = AddOperationEntityToPI( vSubtask, szLocalName, 0 ); // do not show in list
   if ( lRC < 0 )
   {
      strcpy_s( g_szFatalErrorMsg, zsizeof( g_szFatalErrorMsg ), "found operation with reserved name: " );
      strcat_s( g_szFatalErrorMsg, zsizeof( g_szFatalErrorMsg ), szLocalName );
      longjmp( jbFatalError, -1 ); // Fatal Error exit
   }

   CreateViewFromViewForTask( &g_vStatementView, g_lpPIView, 0 );
   g_lParseLimit = lSaveParseLimit;

   // Add a parameter of view  for the subtask.
   AddVariableEntityToPI( vSubtask, "vSubtask", qTVIEW, 0, -1 );
   SetAttributeFromInteger( g_lpPIView, "Variable", "ParameterFlag", 1 );

   // Add a parameter of pointer to view through which to return the view to the qual object.
   AddVariableEntityToPI( vSubtask, "vQualObject", qTVIEW, 0, -1 );
   SetAttributeFromInteger( g_lpPIView, "Variable", "ParameterFlag", 2 );
   SetAttributeFromString( g_lpPIView, "Variable",
                           "PFlag", "Y" ); // is a parameter and a pointer
   lDefineZKey = GetDefineZKey( vSubtask, &lDataType, "zMULTIPLE" );

   // We must save and restore g_lAddNextStatementBefore around the operation BuildActivateEmpty
   // because that operation builds the Activate function and it destroys that flag.
   lTempAddNextStatement = g_lAddNextStatementBefore;
   g_lAddNextStatementBefore = 0;
   BuildActivateEmpty( vSubtask, lDefineZKey );
   g_lAddNextStatementBefore = lTempAddNextStatement;
   PositionAtCallingOperation( );

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
GenerateLocalOperationName( zPCHAR pchReturnName,
                            zLONG  lMaxLth,
                            zPCHAR pchIncInName )
{
   zVIEW  vSearchView;
   zLONG  lMaxNbr;
   zLONG  lLth;
   zSHORT nRC;

   CreateViewFromViewForTask( &vSearchView, g_lpPIView, 0 );

   // Browse through the operations to find the max number for generated operations.
   // Generated operations are recognized by:
   // - the name begins with "fnLocal"
   // - the name ends with a number (will be used as ZKey)

   lMaxNbr = 0;
   nRC = SetCursorFirstEntity( vSearchView, "Operation", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      zCHAR szOperName[ 33 ];
      zLONG lZKey;
      zLONG lNbr;
      zLONG l;

      GetStringFromAttribute( szOperName, zsizeof( szOperName ), vSearchView, "Operation", "Name" );
      GetIntegerFromAttribute( &lZKey, vSearchView, "Operation", "ZKey" );

      // The C generator accepts operation ZKeys only if they are > MAXSTRING (currently 512).
      // So we added 10000 to get into that range, which is now subtracted.
      lZKey = lZKey - 10000;

      lLth = zstrlen( szOperName );
      if ( lLth > 7 && memcmp( szOperName, "fnLocal", 7 ) == 0 )
      {
         l = 1;
         lNbr = 0;
         while ( isdigit( szOperName[ lLth - 1 ] ) )
         {
            lLth--;
            lNbr += l * ((unsigned) szOperName[ lLth ] - (unsigned) '0');
            l = l * 10;
         }

         if ( lNbr == lZKey )
         {
            // OK, this is a generated operation.
            if ( lMaxNbr <= lNbr )
               lMaxNbr = lNbr + 1;
         }
      }

      nRC = SetCursorNextEntity( vSearchView, "Operation", 0 );
   }

   strcpy_s( pchReturnName, lMaxLth, "fnLocal" );
   strcat_s( pchReturnName, lMaxLth, pchIncInName );
   strcat_s( pchReturnName, lMaxLth, "_" );
   lLth = zstrlen( pchReturnName );
   zltoa( lMaxNbr, pchReturnName + lLth, lMaxLth - lLth );

   return( 0 );
}

// Need to add the call to the local operation just built back into the operation where
// the activate was called.
// 1: create a view variable into which to recieve the built qualification
//    object. This var will be sent is as a pointer to a VIEW.
//    Also send in other parms as were needed.
// 2: add the call
// 3: add a call to the operation ActivateObjectInstance
// 4: add a call to Drop the Qual View
// 5: Reset the PI from Save
//
// REMEMBER: At this point the PI View is pointing to the "local" operation that was just
//    built so Create a view to that. and reset the PI back.

zOPER_EXPORT zLONG OPERATION
InsertActivateIntoCurrentOperation( zVIEW  vSubtask,
                                    zPCHAR pchLoadControl )
{
   zCHAR szLODName[ 33 ];
   zVIEW vLocalView;
   zVIEW lpTempView;
   zLONG lQualID;
   zLONG lDataType;
   zLONG lRetViewID;
   zLONG lDefineZKey;

   PositionAtNewOperation( );

   AddReturnStatement( vSubtask, qCONSTANT, 0, "0", zPOS_AFTER );
   AddStatementEntityToPI( vSubtask, qEND, -1, g_vGlobalView, zPOS_AFTER );

   // Save the local View.
   CreateViewFromViewForTask( &vLocalView, g_lpPIView, 0 );
   PositionAtCallingOperation( );

   // We are positioned on the LOD variable.
   GetIntegerFromAttribute( &lRetViewID, g_lpPIView, "Variable", "ID" );

   GetIntegerFromAttribute( (zPLONG) &lpTempView, g_lpPIView, "Variable", "Value" );
   if ( lpTempView == 0 )
   {
      zCHAR szViewName[ 60 ];

      GetStringFromAttribute( szViewName, zsizeof( szViewName ), g_lpPIView, "Variable", "Name" );
      SyntaxError( vSubtask, eQNOVIEWDEFGIVEN, szViewName );
      return( -1 );
   }

   GetStringFromAttribute( szLODName, zsizeof( szLODName ), lpTempView, "LOD", "Name" );

   // 1: Create the qual View.
   lQualID = GenerateTempVariable( vSubtask, qTVIEW, 0 );

   // 2: Add the call after restoring lAddNextStatementBefore.
   g_lAddNextStatementBefore = g_lAddNextStatementBeforeSave;
   BuildCallToLocalFunction( vSubtask, vLocalView, lQualID );

   // 3: Add a call to the operation ActivateObjectInstance.
   lDefineZKey = GetDefineZKey( vSubtask, &lDataType, pchLoadControl );
   BuildActivate( vSubtask, lRetViewID, szLODName, lQualID, lDefineZKey );

   // 4: Add a call to Drop the Qual View.
   BuildDropView( vSubtask, lQualID );

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
InsertActivateNoWhere( zVIEW  vSubtask,
                       zPCHAR pchLoadControl )
{
   zCHAR szLODName[ 33 ];
   zVIEW lpTempView;
   zLONG lQualID;
   zLONG lDataType;
   zLONG lRetViewID;
   zLONG lDefineZKey;

   PositionAtNewOperation( );
   DeleteEntity( g_lpPIView, "Operation", zREPOS_BEFORE );
   PositionAtCallingOperation( );

   GetIntegerFromAttribute( &lRetViewID, g_lpPIView, "Variable", "ID" );

   GetIntegerFromAttribute( (zPLONG) &lpTempView, g_lpPIView, "Variable", "Value" );
   if ( lpTempView == 0 )
   {
      zCHAR szViewName[ 60 ];

      GetStringFromAttribute( szViewName, zsizeof( szViewName ), g_lpPIView, "Variable", "Name" );
      SyntaxError( vSubtask, eQNOVIEWDEFGIVEN, szViewName );
      return( -1 );
   }

   GetStringFromAttribute( szLODName, zsizeof( szLODName ), lpTempView, "LOD", "Name" );
   lQualID = 0;

   // Add the call to the operation ActivateObjectInstance.
   lDefineZKey = GetDefineZKey( vSubtask, &lDataType, pchLoadControl );

   BuildActivate( vSubtask, lRetViewID, szLODName, lQualID, lDefineZKey );
   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
InsertActivateEmpty( zVIEW  vSubtask,
                     zPCHAR pchLoadControl )
{
   zCHAR szLODName[ 33 ];
   zVIEW lpTempView;
   zLONG lDataType;
   zLONG lRetViewID;
   zLONG lDefineZKey;

   PositionAtNewOperation( );
   DeleteEntity( g_lpPIView, "Operation", zREPOS_BEFORE );
   PositionAtCallingOperation( );

   GetIntegerFromAttribute( &lRetViewID, g_lpPIView, "Variable", "ID" );

   GetIntegerFromAttribute( (zPLONG) &lpTempView, g_lpPIView,
                            "Variable", "Value" );
   if ( lpTempView == 0 )
   {
      zCHAR szViewName[ 60 ];

      GetStringFromAttribute( szViewName, zsizeof( szViewName ), g_lpPIView, "Variable", "Name" );
      SyntaxError( vSubtask, eQNOVIEWDEFGIVEN, szViewName );
      return( -1 );
   }

   GetStringFromAttribute( szLODName, zsizeof( szLODName ), lpTempView, "LOD", "Name" );

   // Add the call to the operation ActivateObjectInstance.
   lDefineZKey = GetDefineZKey( vSubtask, &lDataType, pchLoadControl );

   BuildActivateEmptyLocal( vSubtask, lRetViewID, szLODName, lDefineZKey );
   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
BuildCallToLocalFunction( zVIEW vSubtask,
                          zVIEW vLocalView,
                          zLONG lQualID )
{
   zVIEW  vTemp;
   zLONG  lRCID;
   zLONG  lViewID;
   zCHAR  szLocalName[ 33 ];
   zLONG  lVal;
   zLONG  lLastID;
   zLONG  lDataType;
   zLONG  lZKey;
   zSHORT nFoundFlag;
   zLONG  lRC;

   // Begin building an expression.  Use the string stuff and build it in order
   // since we know what is going down.

   lLocal9Code = 0;
   lLocal9Text = 0;

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Get nZRetCode ID (from PI).
   lRCID = AddRetCode( vSubtask );       // add nZRetCode to the list of variables to be declared

   SetCursorFirstEntity( vLocalView, "Variable", "" );

   // Add the Return code id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "RC", lRCID, 0 );

   // Get the name of the local operation just built and set it.
   GetStringFromAttribute( szLocalName, zsizeof( szLocalName ), vLocalView, "Operation", "Name" );
   GetIntegerFromAttribute( &lZKey, vLocalView, "Operation", "ZKey" );

   // Add the CALL ... 1. "Operation Name"   2. "("
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qLOCALOPERATION, qTSHORT, szLocalName, lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );

   // We must now position on a view passed into the called routine that can be used as the first
   // parm to the Qual operation call.  This view will be used in the Qual operation in a create
   // empty OI call.  It can be any view passed in, so we will position on the first parm that is
   // a view and is passed into this routine (that is it is not passed as a pointer to a view).
   // We will generate an error if there is no such view.
#if 0
   // This is the old code that always passed the first parameter.
   // Add the subtask.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTINTEGER, "View?", 1, 0 );
#endif

   CreateViewFromViewForTask( &vTemp, g_lpPIView, 0 ); // view to operation
   nFoundFlag = 0;
   lRC = SetCursorFirstEntity( vTemp, "Variable", "" );
   while ( lRC >= zCURSOR_SET )
   {
      if ( CompareAttributeToInteger( vTemp, "Variable", "DataType", qTVIEW ) == 0 &&
           CompareAttributeToString( vTemp, "Variable", "PFlag", "Y" ) != 0 &&
           CompareAttributeToInteger( vTemp, "Variable", "ParameterFlag", 0 ) != 0 )
      {
         nFoundFlag = 1;  // we are positioned on such a view
         break;
      }

      lRC = SetCursorNextEntity( vTemp, "Variable", "" );
   }

   if ( nFoundFlag == 1 )
      GetIntegerFromAttribute( &lViewID, vTemp, "Variable", "ID" );
   else
   {
      SyntaxError( vSubtask, eQNOVIEWINPARMLIST, "" );
      return( -1 );
   }

   DropView( vTemp );

   // 3. "Qualifying View"   4. ","
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "ViewID", lViewID, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 5. "Pointer to the Qualifying View"
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lQualID * -1, 0 );  // pointer

   // Skip subtask.   why??? dks 2009.09.15
   SetCursorNextEntity( vLocalView, "Variable", "" );

   // While other parms exist, put them in the call.
   lVal = 0;
   while ( SetEntityCursor( vLocalView, "Variable", "ParameterFlag",
                            zPOS_NEXT | zQUAL_INTEGER | zQUAL_NOT | zQUAL_EQUAL,
                            &lVal, "", "", 0, "", 0 ) >= zCURSOR_SET )
   {
      // ","
      ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

      GetStringFromAttribute( szLocalName, zsizeof( szLocalName ), vLocalView, "Variable", "Name" );
      SetCursorFirstEntityByString( g_lpPIView, "Variable", "Name", szLocalName, "" );

      // Get the ID number to increment.
      GetIntegerFromAttribute( &lLastID, g_lpPIView, "Variable", "ID" );

      // Get the data type.
      GetIntegerFromAttribute( &lDataType, g_lpPIView, "Variable", "DataType" );
      ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, 0, lDataType, "DataType", lLastID, 0 );
   }

   // ")"
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally dump the statement from the stack.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
BuildDropView( zVIEW  vSubtask,
               zLONG  lQualID )
{
   zLONG lRCID;
   zLONG lZKey;

   // Begin building an expression.  Use the string stuff and build it in order
   // since we know what is going down.

   lLocal9Code = 0;
   lLocal9Text = 0;

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Get nZRetCode ID (from PI).
   lRCID = AddRetCode( vSubtask );       // add nZRetCode to the list of variables to be declared

   // Add the Return code id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "nZRetCode", lRCID, 0 );

   // Add the CALL ... 1. "DropView"   2. "("   3. "View"   4. ")"
   lZKey = GetOperationZKey( vSubtask, qZEIDONOPERATION, "DropView" );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qZEIDONOPERATION, qTSHORT, "DropView", lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lQualID, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // 5. Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally dump the statement from the stack.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
BuildActivateEmpty( zVIEW  vSubtask,
                    zLONG  lLoadQual )
{
   zLONG lQualID;
   zLONG lResultID;
   zLONG lZKey;

   // Begin building an expression.  Use the string stuff and build it in order
   // since we know what is going down.

   lLocal9Code = 0;
   lLocal9Text = 0;

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Get RESULT ID (from PI).
   lResultID = AddResult( vSubtask );  // add RESULT to the list of variables to be declared

   GetVariableID( &lQualID, "vQualObject" );  // out of order? No! just needs to be done prior to use below. dks 2009.09.11

   // Add the RESULT id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "RESULT", lResultID, 0 );

   // Add the CALL ... 1. "SfActivateSysEmptyOI"   2. "("   3. "&View"   4. ","
   lZKey = GetOperationZKey( vSubtask, qZEIDONOPERATION, "SfActivateSysEmptyOI" );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qZEIDONOPERATION, qTSHORT, "SfActivateSysEmptyOI", lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lQualID * -1, 0 );  // pointer to view
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 5. "LOD Name" (KZDBHQUA)
   ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qTEXT, qTSTRING, "KZDBHQUA", 0, 0 );

   // 6. ","   // 7. "Qualifying View"   8. ","
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", 1, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 11. "zSINGLE", "MULTIPLE", "READONLY"
   ADDEXPRESSIONENTRYTOSTRING( qDEFINE, qNUMERIC, qTINTEGER, "zSINGLE/MULTIPLE/READONLY", lLoadQual, 0 );
   // 12. ")".
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // 13. Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally dump the statement from the stack.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
BuildActivateEmptyLocal( zVIEW  vSubtask,
                         zLONG  lQualID,
                         zPCHAR pchLODName,
                         zLONG  lLoadQual )
{
   zLONG  lResultID;
   zLONG  lZKey;
   zLONG  lVal;
   zCHAR  szLocalVal[ 2 ];
   zLONG  lRC;

   // Begin building an expression.  Use the string stuff and build it in order
   // since we know what is going down.

   lLocal9Code = 0;
   lLocal9Text = 0;

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Get RESULT ID (from PI).
   lResultID = AddResult( vSubtask );  // add RESULT to the list of variables to be declared

   // Add the RESULT id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "RESULT", lResultID, 0 );

   // Add the CALL ... 1. "ActivateEmptyObjectInstance"   2. "("   3. "&View"   4. ","   5. "LOD"   6. ","
   lZKey = GetOperationZKey( vSubtask, qZEIDONOPERATION, "ActivateEmptyObjectInstance" );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qZEIDONOPERATION, qTSHORT, "ActivateEmptyObjectInstance", lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lQualID * -1, 0 );  // pointer
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qTEXT, qTSTRING, pchLODName, 0, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   lVal = qTVIEW;
   lRC = SetEntityCursor( g_lpSGView, "Variable", "DataType",
                          zPOS_FIRST | zQUAL_INTEGER | zQUAL_EQUAL,
                          &lVal, "", "", 0, "", 0 );

   GetStringFromAttribute( szLocalVal, zsizeof( szLocalVal ), g_lpSGView, "Variable", "PFlag" );
   while ( lRC == zCURSOR_SET && szLocalVal[ 0 ] == 'Y' )
   {
      lRC = SetEntityCursor( g_lpSGView, "Variable", "DataType",
                             zPOS_NEXT | zQUAL_INTEGER | zQUAL_EQUAL,
                             &lVal, "", "", 0, "", 0 );

      GetStringFromAttribute( szLocalVal, zsizeof( szLocalVal ), g_lpSGView, "Variable", "PFlag" );
   }

   // 7. "Qualifying View"
   if ( lRC == zCURSOR_SET && szLocalVal[ 0 ] != 'Y' )
   {
      GetIntegerFromAttribute( &lVal, g_lpSGView, "Variable", "ID" );
      ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lVal, 0 );
   }
   else
   {
      lVal = 0;
      ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qNUMERIC, qTINTEGER, "0", 0, 0 );
   }

   // 8. ","
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 9. "zSINGLE", "MULTIPLE", "READONLY", ...
   ADDEXPRESSIONENTRYTOSTRING( qDEFINE, qNUMERIC, qTINTEGER, "zSINGLE/MULTIPLE/READONLY", lLoadQual, 0 );
   // 10. ")"
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // 11. Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally add the statement.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
BuildActivate( zVIEW  vSubtask,
               zLONG  lRetViewID,
               zPCHAR pchLODName,
               zLONG  lQualViewID,
               zLONG  lControlDefineZKey )
{
   zVIEW  vTemp;
   zLONG  lResultID;
   zLONG  lRCID;
   zLONG  lZKey;
   zSHORT nFoundFlag;
   zLONG  lRC;

   // Begin building an expression.  Use the string stuff and build it in order
   // since we know what is going down.

   lLocal9Code = 0;
   lLocal9Text = 0;

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Get RESULT ID (from PI).
   lResultID = AddResult( vSubtask );  // add RESULT to the list of variables to be declared

   // Add the RESULT id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "RESULT", lResultID, 0 );

   // Add the CALL ... 1. "ActivateObjectInstance"   2. "("   3. "&View"   4. ","   5. "LOD"   6. ","
   lZKey = GetOperationZKey( vSubtask, qZEIDONOPERATION, "ActivateObjectInstance" );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qZEIDONOPERATION, qTSHORT, "ActivateObjectInstance", lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lRetViewID * -1, 0 );  // pointer
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qTEXT, qTSTRING, pchLODName, 0, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // We must now position on a view passed into the called routine that
   // can be used as the first parm to the Qual operation call.  This
   // view will be used in the Qual operation in a create empty OI call.
   // It can be any view passed in, so we will position on the first parm
   // that is a view and is passed into this routine (that is it is not
   // passed as a pointer to a view).  We will generate an error if there
   // is no such view.
   CreateViewFromViewForTask( &vTemp, g_lpPIView, 0 ); // view to operation
   nFoundFlag = 0;
   lRC = SetCursorFirstEntity( vTemp, "Variable", "" );
   while ( lRC >= zCURSOR_SET )
   {
      if ( CompareAttributeToInteger( vTemp, "Variable", "DataType", qTVIEW ) == 0 &&
           CompareAttributeToString( vTemp, "Variable", "PFlag", "Y" ) != 0 &&
           CompareAttributeToInteger( vTemp, "Variable", "ParameterFlag", 0 ) != 0 )
      {
         nFoundFlag = 1;          // we are positioned on such a view
         break;
      }

      lRC = SetCursorNextEntity( vTemp, "Variable", "" );
   }

   if ( nFoundFlag == 1 )
      GetIntegerFromAttribute( &lRCID, vTemp, "Variable", "ID" );
   else
   {
      SyntaxError( vSubtask, eQNOVIEWINPARMLIST, "" );
      return( -1 );
   }

   DropView( vTemp );

   // 7. Add the view to the parm list.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTINTEGER, "RCID", lRCID, 0 );

#if 0
   // The subtask.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE,    //qCONSTANT,
                               qNUMERIC,     //qNUMERIC,
                               qTVIEW,       //qTINTEGER,
                               "1",          //"0",
                               1 );          //0 );
#endif

   // 8. ","
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   if ( lQualViewID != 0 )
      ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "QualView", lQualViewID, 0 );
   else
      ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qNUMERIC, qTINTEGER, "0", 0, 0 );

   // 10. ","
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 11. "SINGLE", "MULTIPLE", ...
   ADDEXPRESSIONENTRYTOSTRING( qDEFINE, qNUMERIC, qTINTEGER, "SINGLE/MULTIPLE", lControlDefineZKey, 0 );

   // 12. ")"
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // 13. Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally add the statement.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   return( 0 );
}

// To add a WHERE to an activate:
// - Create an entity spec for the root of the instance.
// - If there is no WHERE clause, there is no need of an entity spec for the root, but this is
//     the only time we don't need one.
// - For each WHERE clause we need a qual attribute.  In the qual attribute, we need to set
//     the EntityName, AttributeName, Value and Oper.
// - If there is a join, we need to create a Qual attrib for Oper of AND or OR only.
zOPER_EXPORT zLONG OPERATION
BuildWhereStatements( zVIEW  vSubtask,
                      zLONG  lRootOrRestrict )
{
   zCHAR  szRootName[zZEIDON_NAME_LTH + 1];
   zLONG  lTempID;
   zLONG  lLoop;
   zCHAR  szViewName[zZEIDON_NAME_LTH + 1];
   zLONG  lViewID;
   zCHAR  szEntityName[zZEIDON_NAME_LTH + 1];
   zCHAR  szAttributeName[zZEIDON_NAME_LTH + 1];
   zCHAR  szRViewName[zZEIDON_NAME_LTH + 1];
   zLONG  lRViewID;
   zCHAR  szREntityName[zZEIDON_NAME_LTH + 1];
   zLONG  lREntityID;
   zCHAR  szRAttributeName[zZEIDON_NAME_LTH + 1];
   zLONG  lRAttributeID;
   zCHAR  szOperString[ 15 ];
   zLONG  lLth;
   zLONG  lDataType;

   // Force g_lAddNextStatementBefore flag off or the fnBuildCreateEntity below will be
   // positioned incorrectly.
   g_lAddNextStatementBefore = 0;

   if ( lRootOrRestrict == 1 ) // root
   {
      lLoop = 1;
      GetRootEntityName( szRootName, zsizeof( szRootName ) );
      fnBuildCreateEntity( vSubtask, "EntitySpec" );
      fnBuildSetAttributeConstant( vSubtask, "EntitySpec", "EntityName", szRootName );
   }
   else
   if ( lRootOrRestrict == 0 ) // root
   {
      lLoop = 1;
      SplitQualifier( g_sWhereLeft[ 0 ].szText, szViewName, szEntityName, szAttributeName );
      strcpy_s( szRootName, zsizeof( szRootName ), szEntityName );
      fnBuildCreateEntity( vSubtask, "EntitySpec" );
      fnBuildSetAttributeConstant( vSubtask, "EntitySpec", "EntityName", szRootName );
   }

   for ( ; lLoop < g_lWhereIndex; lLoop++ )
   {
      zLONG i;

      SplitQualifier( g_sWhereLeft[ lLoop ].szText, szViewName, szEntityName, szAttributeName );

      GetVariableID( &lViewID, szViewName );

      // need to add codes for unknowns

      // Insert opening parens, if there.
      for ( i = 0; i < g_sWhereLeft[ lLoop ].lLevel; i++ )
      {
         fnBuildCreateEntity( vSubtask, "QualAttrib" );
         fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "Oper", "(" );
      }

      switch( g_sWhereRight[ lLoop ].lElementClass )
      {
         case qVARIABLE:
            fnBuildCreateEntity( vSubtask, "QualAttrib" );

            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "EntityName", szEntityName );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "AttributeName", szAttributeName );
            fnBuildSetAttributeVariable( vSubtask, "QualAttrib", "Value",
                                         g_sWhereRight[ lLoop ].lOffset, g_sWhereRight[ lLoop ].lDataType );
            break;

         case qDEFINE:
            break;

         case qCONSTANT:
            fnBuildCreateEntity( vSubtask, "QualAttrib" );

            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "EntityName", szEntityName );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "AttributeName", szAttributeName );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "Value", g_sWhereRight[ lLoop ].szText );
            break;

         case qATTRIBUTEQUALIFIER:
            AtomizeAQ( g_sWhereRight[ lLoop ].szText, szRViewName, szREntityName, szRAttributeName,
                       &lRViewID, &lREntityID, &lRAttributeID, g_sWhereRight[ lLoop ].lDataClass );

            if ( lREntityID == 0 && lRAttributeID == 0 )
               lLth = GetLengthFromAttribute( lRViewID, szREntityName, szRAttributeName );
            else
               lLth = -1;

            if ( lLth == -1 )
               lLth = 1024;

            if ( g_sWhereLeft[ lLoop ].lDataType == qTDECIMAL )
            {
               strcpy_s( g_szOperationName, zsizeof( g_szOperationName ), "GetDecimalFromAttribute" );
               lDataType = qTDECIMAL;
            }
            else
            {
               if ( g_sWhereLeft[ lLoop ].lDataType == qTINTEGER )
               {
                  strcpy_s( g_szOperationName, zsizeof( g_szOperationName ), "GetIntegerFromAttribute" );
                  lDataType = qTINTEGER;
               }
               else
               {
                  strcpy_s( g_szOperationName, zsizeof( g_szOperationName ), "GetStringFromAttribute" );
                  lDataType = qTSTRING;
               }
            }

            lTempID = GenerateTempVariable( vSubtask, lDataType, lLth );

            // Add a get then a string concat.
            // Handle g_lAddNextStatementBeforeSave here so that the Activate code
            // is generated properly after a FOR statement.
            g_lAddNextStatementBefore = g_lAddNextStatementBeforeSave;
            AddGetOrSetAttribute( vSubtask, g_szOperationName, lRViewID, 0, lDataType, lTempID,
                                  szREntityName, lREntityID, szRAttributeName, lRAttributeID,
                                  0, "", 0, 0 );

            g_lAddNextStatementBeforeSave = g_lAddNextStatementBefore;

            fnBuildCreateEntity( vSubtask, "QualAttrib" );

            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "EntityName", szEntityName );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "AttributeName", szAttributeName );
            fnBuildSetAttributeVariable( vSubtask, "QualAttrib", "Value", lTempID, lDataType );
            break;

         case qENTITYQUALIFIER:
            AtomizeAQ( g_sWhereRight[ lLoop ].szText, szRViewName, szREntityName, szRAttributeName,
                       &lRViewID, &lREntityID, &lRAttributeID, g_sWhereRight[ lLoop ].lDataClass );

            fnBuildCreateEntity( vSubtask, "QualAttrib" );

            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "EntityName", szEntityName );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "AttributeName", "" );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "Value", "" );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "SourceEntityName", szREntityName );
            fnBuildSetAttributeVariable( vSubtask, "QualAttrib", "SourceViewID", lRViewID, qTINTEGER );
            break;

         default: // i.e. 0
            // this
            fnBuildCreateEntity( vSubtask, "QualAttrib" );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "EntityName", szEntityName );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "AttributeName", szAttributeName );
            fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "Value", "" );
            break;
      }

      if ( g_lWhereOp[ lLoop ] == qCONDEQUAL )
         g_lWhereOp[ lLoop ] = qEQUAL; // SQL problem

      // insert comparison operator
      GetStringForSQLOperator( szOperString, zsizeof( szOperString ), g_lWhereOp[ lLoop ] );
      fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "Oper", szOperString );

      // insert closing parens, if there
      for ( i = 0; i < g_sWhereRight[ lLoop ].lLevel; i++ )
      {
         fnBuildCreateEntity( vSubtask, "QualAttrib" );
         fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "Oper", ")" );
      }

      // insert Join operator (AND/OR)
      if ( g_lWhereJoin[ lLoop ] )
      {
         GetStringForSQLOperator( szOperString, zsizeof( szOperString ), g_lWhereJoin[ lLoop ] );
         fnBuildCreateEntity( vSubtask, "QualAttrib" );
         fnBuildSetAttributeConstant( vSubtask, "QualAttrib", "Oper", szOperString );
      }

   } // for lLoop

   return( 0 );
}

static zLONG OPERATION
fnBuildCreateEntity( zVIEW vSubtask, zPCHAR pchWhichEntity )
{
   zLONG lQualID;
   zLONG lRCID;
   zLONG lDataType;
   zLONG lDefineZKey;
   zLONG lZKey;
   zLONG lSaveOperClass;

   lLocal9Code = 0;
   lLocal9Text = 0;

   PositionAtNewOperation( );

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Get nZRetCode ID (from PI).
   lRCID = AddRetCode( vSubtask );       // add nZRetCode to the list of variables to be declared

   GetVariableID( &lQualID, "vQualObject" );

   lSaveOperClass = g_lOperationClass;
   lDefineZKey = GetDefineZKey( vSubtask, &lDataType, "zPOS_AFTER" );
   g_lOperationClass = lSaveOperClass;

   // Add the Return code id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "nZRetCode", lRCID, 0 );

   // Add the CALL ... 1. "CreateEntity"   2. "("   3. "View"   4. ","   5. "Entity"   6. ","
   lZKey = GetOperationZKey( vSubtask, qZEIDONOPERATION, "CreateEntity" );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qZEIDONOPERATION, qTSHORT, "CreateEntity", lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lQualID, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qTEXT, qTSTRING, pchWhichEntity, 0, 0 );

   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 7. "zPOS_AFTER"
   ADDEXPRESSIONENTRYTOSTRING( qDEFINE, qNUMERIC, qTINTEGER, "zPOS_AFTER", lDefineZKey, 0 );

   // 8. ")"
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // 9. "="  Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally add the statement.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   PositionAtCallingOperation( );
// DisplayObjectInstance( g_vStatementView, "", "" );
// MessageSend( g_vStatementView, "???", "fnBuildCreateEntity", "g_vStatementView", 0, 0 );

   return( 0 );
}

zLONG OPERATION
fnBuildSetAttributeConstant( zVIEW  vSubtask,
                             zPCHAR pchEntityName,
                             zPCHAR pchAttributeName,
                             zPCHAR pchAttributeValue )
{
   zLONG lQualID;
   zLONG lRCID;

   lLocal9Code = 0;
   lLocal9Text = 0;


   PositionAtNewOperation( );

   // Insert new bottom of stack.
   // AddOperatorToView( vSubtask, 0, -2 );

   // Get nZRetCode ID (from PI)
   lRCID = AddRetCode( vSubtask );       // add nZRetCode to the list of variables to be declared

   GetVariableID( &lQualID, "vQualObject" );
   AddGetOrSetAttribute( vSubtask, "SetAttributeFromString", lQualID,
                         -1,                   // -1=no, 0=first, 1=last
                         qTSTRING, -1, pchEntityName, -1, pchAttributeName, -1,
                         qTSTRING,             // data type for const
                         pchAttributeValue,     // string constant
                         0, 0 );

   PositionAtCallingOperation( );
   return( 0 );
}

zLONG OPERATION
fnBuildSetAttributeVariable( zVIEW  vSubtask,
                             zPCHAR pchEntityName,
                             zPCHAR pchAttributeName,
                             zLONG  lVarID,
                             zLONG  lVarDataType )
{
   zLONG  lQualID;
   zLONG  lLastID;
   zLONG  lDataType;
   zLONG  lZero;
   zVIEW  vCallingView;
   zCHAR  szOperationName[ 33 ];
   zLONG  lRC;

   lLocal9Code = 0;
   lLocal9Text = 0;

   // We need to create a local copy of the var being used.
   lLastID = 0;

   // Get the name of the var to be sure we do not pass it multiple times.
   // Position on the one being sent in the source operation.
   SetCursorFirstEntityByInteger( g_lpSGView, "Variable", "ID", lVarID, "" );
   CreateViewFromViewForTask( &vCallingView, g_lpSGView, 0 );

   // Get the name since we are using the same name as is being passed.
   GetStringFromAttribute( szOperationName, zsizeof( szOperationName ), vCallingView, "Variable", "Name" );
   PositionAtNewOperation( );

   // See if we can position on it in the target.
   lRC = SetCursorFirstEntityByString( g_lpPIView, "Variable", "Name", szOperationName, "" );

   // Get nZRetCode ID (from PI)
// lRCID = AddRetCode( vSubtask );       // add nZRetCode to the list of variables to be declared

   // If not do this code.
   if ( lRC < zCURSOR_SET )
   {
      // Position on the last Variable in the target.
      //lRC = SetCursorLastEntity( g_lpPIView, "Variable", "" );
      //
      // Get the ID number to increment.
      // GetIntegerFromAttribute( &lLastID, g_lpPIView, "Variable", "ID" );

      // Position at the last parameter.
      lZero = 0;
      SetEntityCursor( g_lpPIView, "Variable", "ParameterFlag",
                       zPOS_LAST | zQUAL_INTEGER | zQUAL_GREATER_THAN,
                       &lZero, "", "", 0, "", "" );
      GetIntegerFromAttribute( &lLastID, g_lpPIView, "Variable", "ID" );

      // Put the new parameter as after the current last parameter.
      CreateEntity( g_lpPIView, "Variable", zPOS_AFTER );

      // Since we are alread position from above, set the matching attributes.
      SetMatchingAttributesByName( g_lpPIView, "Variable", vCallingView, "Variable", zSET_ALL );

      // If type is character, make it a pointer in the list
      GetIntegerFromAttribute( &lDataType, g_lpPIView, "Variable", "DataType" );

      // Increment the ID number in the TARGET.
      if ( lLastID == 2 )
         lLastID = 4; // to skip nZRetCode

      lVarID = lLastID + 1;

      // Set the Attribute valid for the id in the target.
      SetAttributeFromInteger( g_lpPIView, "Variable", "ID", lVarID );

      // Make it a parameter in the target.
      if ( lDataType == qTSTRING )
      {
         SetAttributeFromString( g_lpPIView, "Variable", "PFlag", "Y" ); // is a return parameter
         SetAttributeFromInteger( g_lpPIView, "Variable", "ParameterFlag", 2 );
      }
      else
         SetAttributeFromInteger( g_lpPIView, "Variable", "ParameterFlag", 1 ); // is a parameter
   }
   else
   {
      // The variable was found, and we are positioned on it.  Get the ID. HH,19.6.1998
      GetIntegerFromAttribute( &lVarID, g_lpPIView, "Variable", "ID" );
   }

   // Do everything else now.
   // Insert new bottom of stack.
   // AddOperatorToView( vSubtask, 0, -2 );

   GetVariableID( &lQualID, "vQualObject" );
   strcpy_s( szOperationName, zsizeof( szOperationName ), "SetAttributeFrom" );

   switch( lVarDataType )
   {
      case qTSTRING:
      case qTCHARACTER :
         strcat_s( szOperationName, zsizeof( szOperationName ), "String" );
         break;

      case qTINTEGER:
      case qTSHORT   :
         strcat_s( szOperationName, zsizeof( szOperationName ), "Integer" );
         break;

      case qTDECIMAL:
         strcat_s( szOperationName, zsizeof( szOperationName ), "Decimal" );
         break;

      default :
         strcat_s( szOperationName, zsizeof( szOperationName ), "String" );
         break;
   }

   AddGetOrSetAttribute( vSubtask, szOperationName, lQualID,
                         1,                   // -1=no, 0=first, 1=last
                         lVarDataType, lVarID, pchEntityName, -1,
                         pchAttributeName, -1, 0, "", 0, 0 );

   PositionAtCallingOperation( );
   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
GetRootEntityName( zPCHAR pchReturnEntityName, zLONG lMaxLth )
{
   zLONG  lRC;
   zVIEW  lpViewOfView;;

   GetIntegerFromAttribute( (zPLONG) &lpViewOfView, g_vSavePIView, "Variable", "Value" );
   if ( lpViewOfView == 0 )
      return( -1 );

   lRC = ResetView( lpViewOfView );
   if ( lRC < 0 )
      return( -1 );

   lRC = SetCursorFirstEntity( lpViewOfView, "LOD_EntityParent", "" );
   if ( lRC >= zCURSOR_SET )
      lRC = GetStringFromAttribute( pchReturnEntityName, lMaxLth, lpViewOfView, "LOD_EntityParent", "Name" );

   return( lRC );

}

zOPER_EXPORT zLONG OPERATION
GetStringForSQLOperator( zPCHAR pchOperString,
                         zLONG  lMaxLth,
                         zLONG lOperator )
{
   switch( lOperator )
   {
      case qLPAREN:
      case qOPENOPER:
         strcpy_s( pchOperString, 15, "(" );
         break;

      case qRPAREN:
      case qCLOSEOPER:
         strcpy_s( pchOperString, lMaxLth, ")" );
         break;

      case qGREATERTHANEQUAL:
         strcpy_s( pchOperString, lMaxLth, ">=" );
         break;

      case qLESSTHANEQUAL:
         strcpy_s( pchOperString, lMaxLth, "<=" );
         break;

      case qGREATERTHAN:
         strcpy_s( pchOperString, lMaxLth, ">" );
         break;

      case qLESSTHAN:
         strcpy_s( pchOperString, lMaxLth, "<" );
         break;

      case qMINUS:
         strcpy_s( pchOperString, lMaxLth, "-" );
         break;

      case qADDITION:
         strcpy_s( pchOperString, lMaxLth, "+" );
         break;

      case qMULTIPLICATION:
         strcpy_s( pchOperString, lMaxLth, "*" );
         break;

      case qDIVISION:
         strcpy_s( pchOperString, lMaxLth, "/" );
         break;

      case qEQUAL:
         strcpy_s( pchOperString, lMaxLth, "=" );
         break;

      case qNOTEQUAL:
         strcpy_s( pchOperString, lMaxLth, "!=" );
         break;

      case qCONDEQUAL:
         strcpy_s( pchOperString, lMaxLth, "=" );
         break;

      case qOR:
         strcpy_s( pchOperString, lMaxLth, "OR" );
         break;

      case qAND:
         strcpy_s( pchOperString, lMaxLth, "AND" );
         break;

      case qNOT:
         strcpy_s( pchOperString, lMaxLth, "!" );
         break;

      case qCOMMA:
         strcpy_s( pchOperString, lMaxLth, "," );
         break;

      case qSEMICOLON:
         strcpy_s( pchOperString, lMaxLth, ";" );
         break;

      case qLIKE:
         strcpy_s( pchOperString, lMaxLth, "LIKE" );
         break;

      case qEXISTS:
         strcpy_s( pchOperString, lMaxLth, "EXISTS" );
         break;

      case qNOTEXISTS:
         strcpy_s( pchOperString, lMaxLth, "NOT EXISTS" );
         break;

      case qIS:
         strcpy_s( pchOperString, lMaxLth, "IS" );
         break;

      case qNULL:
         strcpy_s( pchOperString, lMaxLth, "IS NULL" );
         break;

      case qNOTNULL:
         strcpy_s( pchOperString, lMaxLth, "IS NOT NULL" );
         break;

      default:
         strcpy_s( pchOperString, lMaxLth, "@" );
         break;
   }

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
BuildGetView( zVIEW  vSubtask,
              zSHORT lRetViewID,
              zPCHAR pchViewName,
              zLONG  lViewTokenType,
              zSHORT lQualView,
              zPCHAR pchQualLevel )
{
   zLONG  lResultID;
   zLONG  lDataType;
   zLONG  lZKey;
   zLONG  lDefineZKey;
   zLONG  lIDNumber;
   zCHAR  szReturnFlag[ 2 ];
   zLONG  lRC;

   // Begin building an expression.  Use the string stuff and build it in order
   // since we know what is going down.

   lLocal9Code = 0;
   lLocal9Text = 0;

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Strip any enclosing quotes/apostrophes from view name.
   StripQuotes( pchViewName );

   // Get RESULT ID (from PI).
   lResultID = AddResult( vSubtask );  // add RESULT to the list of variables to be declared

   // Add the RESULT id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "RESULT", lResultID, 0 );

   // Add the CALL ... 1. "GetViewByName"   2. "("   3. "&View"   4. ","
   lZKey = GetOperationZKey( vSubtask, qZEIDONOPERATION, "GetViewByName" );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qZEIDONOPERATION, qTSHORT, "GetViewByName", lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lRetViewID * -1, 0 );  // pointer
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 5. "ViewName"
   if ( lViewTokenType == qCONSTANT )
   {
      ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qTEXT, qTSTRING, pchViewName, 0, 0 );
   }
   else
   {
      lRC = GetVariableID( &lIDNumber, pchViewName );
      if ( lRC < 0 || lIDNumber < 0 )
      {
         // This is an error ... the variable is not defined.
         SyntaxError( vSubtask, eQVARIABLEUNDEFINED, pchViewName );
         return( -1 );
      }

      ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qTEXT, qTSTRING, pchViewName, lIDNumber, 0 );
   }

   // 6. ","
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 7. "Passed View"
   if ( lQualView == -1 )
   {
      // DonC code 10/19/2003 to add View to call.
      // Locate a passed view in the operation calling list.  If one isn't there, pass in zero.
      lRC = SetCursorFirstEntityByInteger( g_lpSGView, "Variable", "DataType", qTVIEW, 0 );
      GetStringFromAttribute( szReturnFlag, zsizeof( szReturnFlag ), g_lpSGView, "Variable", "PFlag" );
      while ( lRC >= zCURSOR_SET && szReturnFlag[ 0 ] == 'Y' )
      {
         lRC = SetCursorNextEntityByInteger( g_lpSGView, "Variable", "DataType", qTVIEW, 0 );
         GetStringFromAttribute( szReturnFlag, zsizeof( szReturnFlag ), g_lpSGView, "Variable", "PFlag" );
      }

      if ( lRC < zCURSOR_SET )
      {
         // We didn't find such a view, so generate the operation with a zero.
         ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qNUMERIC, qTINTEGER, "0", 0, 0 );
      }
      else
      {
         // We found the view so use it in the operation.
         GetIntegerFromAttribute( &lIDNumber, g_lpSGView, "Variable", "ID" );
         ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "View", lIDNumber, 0 );
      }
   }
   else
   {
      ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "QualView", lQualView, 0 );
   }

   // 8. ","
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 9. "View Level"
   lDefineZKey = GetDefineZKey( vSubtask, &lDataType, pchQualLevel );
   ADDEXPRESSIONENTRYTOSTRING( qDEFINE, 0, lDataType, "View Level", lDefineZKey, 0 );

   // 10. ")"
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // 11. "="  Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally add the statement.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
BuildNameView( zVIEW  vSubtask,
               zSHORT lViewID,
               zPCHAR pchViewName,
               zSHORT nNameType,
               zSHORT lQualView,
               zPCHAR pchQualLevel )
{
   zLONG  lRCID;
   zLONG  lDataType;
   zLONG  lZKey;
   zLONG  lDefineZKey;

   // Strip any enclosing quotes/apostrophes from view name.
   StripQuotes( pchViewName );

   // Begin building an expression.  Use the string stuff and build it in order
   // since we know what is going down.

   lLocal9Code = 0;
   lLocal9Text = 0;

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Get nZRetCode ID (from PI).
   lRCID = AddRetCode( vSubtask );       // add nZRetCode to the list of variables to be declared

   // Add the Return code id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "nZRetCode", lRCID, 0 );

   // Add the CALL ... 1. "SetNameForView"   2. "("   3. "View"   4. ","
   lZKey = GetOperationZKey( vSubtask, qZEIDONOPERATION, "SetNameForView" );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qZEIDONOPERATION, qTSHORT, "SetNameForView", lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "ViewID", lViewID, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 5. "ViewName"
   if ( nNameType == -1 )
   {
      ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qTEXT, qTSTRING, pchViewName, 0, 0 );
   }
   else
   {
      ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qTEXT, qTSTRING, pchViewName, nNameType, 0 );
   }

   // 6. ","
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 7. Qualifying view
   if ( lQualView == -1 )
   {
      ADDEXPRESSIONENTRYTOSTRING( qCONSTANT, qNUMERIC, qTVIEW, "0", 0, 0 );
   }
   else
   {
      ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "QualView", lQualView, 0 );
   }

   // 8. ","
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ",", qCOMMA, 0 );

   // 9. "View Level"
   lDefineZKey = GetDefineZKey( vSubtask, &lDataType, pchQualLevel );
   ADDEXPRESSIONENTRYTOSTRING( qDEFINE, 0, lDataType, "View Level", lDefineZKey, 0 );

   // 10. ")"
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // 11. "="  Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally add the statement.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   return( 0 );
}

zOPER_EXPORT zLONG OPERATION
BuildCommitView( zVIEW  vSubtask,
                 zSHORT lViewID )
{
   zLONG  lResultID;
   zLONG  lZKey;

   // Begin building an expression.  Use the string stuff and build it in order
   // since we know what is going down.

   lLocal9Code = 0;
   lLocal9Text = 0;

   // Insert new bottom of stack.
   AddOperatorToView( vSubtask, 0, -2 );

   // Get RESULT ID (from PI).
   lResultID = AddResult( vSubtask );  // add RESULT to the list of variables to be declared

   // Add the RESULT id to the operation as a return code.
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTSHORT, "RESULT", lResultID, 0 );

   // Add the CALL ... 1. "CommitObjectInstance"   2. "("   3. "View"   4. ")"
   lZKey = GetOperationZKey( vSubtask, qZEIDONOPERATION, "CommitObjectInstance" );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATIONCALL, qZEIDONOPERATION, qTSHORT, "CommitObjectInstance", lZKey, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "(", qOPENOPER, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qVARIABLE, qNUMERIC, qTVIEW, "ViewID", lViewID, 0 );
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, ")", qCLOSEOPER, 0 );

   // 5. Add the equal so the return code gets set.
   ADDEXPRESSIONENTRYTOSTRING( qOPERATOR, qNUMERIC, qTINTEGER, "=", qEQUAL, 0 );

   // Finally add the statement.
   AddOperatorToView( vSubtask, 0, -1 );
   AddStatementEntityWithStringToPI( vSubtask, qEXPRESSION, qqlineno,
                                     szLocal9Code, &lLocal9Code, szLocal9Text, &lLocal9Text, zPOS_AFTER );

   return( 0 );
}

// Strip any enclosing quotes/apostrophes from string.
static void
StripQuotes( zPCHAR pchString )
{
   int k = zstrlen( pchString );
   if ( k > 1 )
   {
      if ( (pchString[ 0 ] == '\'' &&  pchString[ k - 1 ] == '\'') ||
           (pchString[ 0 ] == '\"' &&  pchString[ k - 1 ] == '\"') )
      {
         pchString[ 0 ] = 0;
         pchString[ k - 1 ] = 0;
         strcpy_s( pchString, k, pchString + 1 );
      }
   }
}
