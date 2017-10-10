/////////////////////////////////////////////////////////////////////////////
//
// MODULE NAME:   tzvmp1aa.c - VML SubSystem Parser ActionQ Module
// DESCRIPTION:   This is the source file which contains the ActionQ Function
//                for the parser. It calls all of the functions needed to
//                create the parsed object.
//
// //////////////////////////////////////////////////////////////////////////
// * Copyright (c) 1995 - 2016 QuinSoft, Inc.   All rights reserved.        *
// * Confidential and Proprietary material subject to license - do not      *
// * reproduce or disclose.  This material is an unpublished work and       *
// * is considered a trade secret belonging to the copyright holder.        *
// //////////////////////////////////////////////////////////////////////////
//
// AUTHOR:        Jeffrey S. Beam
// DATE:          1992/07/17
// API:           MicroSoft foundation classes and Windows 3.1 SDK
// ENVIRONMENT:   Windows 3.1
// REVISION:      0.9A   1995/08/30
//
// LAST MESSAGE ID: VM00101
//
// HISTORY:
//
//    1995/08/05: Beginning of 10B branch
//
/////////////////////////////////////////////////////////////////////////////
//
#include "tzlodopr.h"
#include "tzvmpopr.hg"
#include "tz__oprs.h"
#include "tzvsecaa.h"
#include "ZeidonOp.H"

/*
CHANGE LOG
2002.03.06  HH
   improve OperationNameValid.
2002.01.18  HH
   fix for R053855, allow any attribute as string parameter in a function.
2001.11.29  HH
   improve last fix, max length depends on LOD name.
2001.11.15  HH
   R55920, improve operation name validation.
2001.10.09  HH
   support using integer constant as decimal argument.
2001.09.27  HH
   R53977,F50592, support parens in WHERE
2001.09.03  HH
   fix bug R55548, Parameter Checking.
2001.08.29  HH
   fix bug: for each ... while function()
2001.07.27  HH
   stop parsing if an invalid OPERATION definition is encontered.
2001.04.18 HH
   set default return value, if none specified.
2001.04.10 HH
   Correct generation of RETURN for return type void.
2001.02.19 HH
   allow return value integer for a function returning string.
2001.02.12 HH
   Grammar change.
   implement Set Cursor with Object Scope.
2001.01.05 HH
   R54458, raise error message if variable not defined in WHERE.
2000.11.29 HH
   improve setting pointer flag for string variables.
2000.09.29 HH
   improve parameter check for functions with no parms.
2000.09.26 HH
   improve parameter check, so that an integer attribute must not be
   mapped onto a string parameter.
2000.09.26 HH
   support old data types 'E' and 'A' with last change.
2000.09.25 HH
   improve parameter check on function definition.
2000.09.17 HH
   do not show generated operations in list
2000.09.05 HH
   improved parameter check, fix for R053723.
2000.08.28 HH
   fix problem with operation returncodes.
2000.08.28 HH
   R53652, set RESULT on DELETE ENTITY.
2000.08.23 HH
   parameters are not "return" if the function is added from
   source file.
2000.08.16 HH
   improved parameter check for function calls.
2000.06.23 HH
   fix for "FOR integer VIEW.ENTITY".
2000.06.16 HH
   fix for "UNTIL".

OLD CHANGE LOG
24.04.1997 DonC
   Modified aQLOADDEFFROMVOR to properly handle return code on
   ActivateMetaOI.  The result of error was an invalid temporary variable
   when the view used in a WHERE clause was defined with a REGISTERED AS
   declaration.  Also changed an Activate by ZKey to an Activate by Name
   as a part of the same problem.

27.06.1997  DonC
   Modified case aQADDOPENOPERTOEXPR to drop a temporary view that was left
   hanging.

12.07.1997  DonC
   Corrected case aQSAVEACTIVATECONTINUE to use define zACTIVATE_MULTIPLE_CONTINUE
   instead of just zACTIVATE_CONTINUE.

01.08.1997  DonC
   Modified case aQINSERTEXPRESSIONSTMT to set g_lTargetDataType variable to
   qTUNKNOWN.  Sometimes a prior assignment statement had set this variable
   to a value that was not triggering a syntax error.

22.08.1997  DonC
   Modified case aQMARKLASTVARASPARM to set Parameter.ShortDesc value when
   an operation is created by the parser.

22.09.1997  DonC
   Modified case aQADDNAMEVIEW to give syntax error if the view name was
   not defined as a variable.

12.10.1997  DonC
   Modified case aQINSERTOPERATIONCALL to give syntax error if a parameter
   contained a compount expression.

14.11.1997  DonC
   Added constraint to not allow single quotes to be used as string delimiters.

22.11.1997  DonC
   Added processing of g_lOperationUnknownFlag so that an unknown operation
   would not be processed.

05.02.1998  DonC
   Modified aQMARKLASTVARASPARM to work correctly on a new Operation without
   Parameter entities.

14.02.1998  DonC
   Made modifications to give error message when left AQ has a view name
   that doesn't match the Activate view name. (QS 139)

15.02.1998  DonC
   Modified case aQADDOPERATORTOEXPR to give error message when an operation
   is part of a compound expression. (QS 146)

01.04.1998  DonC
   Modified case aQADDCONSTANTTOEXPR so that setting an attribute to a null
   string would not trigger a syntax error.

26.04.1998  DonC
   Added validation for view in aQADDCOMMIT and aQVERIFYACTIVATEOBJECT.

13.05.1998  DonC
    Modified aADDCONSTANTTOEXPR and aADDDEFINETOEXPR to initialize nRetCode
    because it was being used inside the code and was not always being set.

16.05.1998  DonC
   Modified case aQADDOPERATORTOEXPR so that a simple numerical expression is
   allowed in an operation.

04.06.1998  DonC
   Modified case aQADDDEFINETOEXPR to correct the DataClass specification for
   a Define value.

17.06.1998  HH
   Copy Unsigned Flag from operation definition to parse object.
   Necessary in 9J, because the C++ compiler is very strict and does not
   allow differences in prototype and declaration (zSHORT vs. zUSHORT) .
   See corresponding change in TZVMG1AA.C .

1998.07.10 RG
   Several changes from Quinsoft without change log

17.07.1998  HH
   Handle unsigned parameters, global parm list extension .
   took out the change:
   "15.02.1998  DonC : Modified case aQADDOPERATORTOEXPR ..."

30.07.1998  HH
   Set g_bActivate = FALSE in case of aQADDACTIVATESTMTNOWHERE
   or aQADDACTIVATESTMTEMPTY (Don's request) .

19.08.1998  HH
   fixed stupid bug in last change :-(

07.09.1998  HH
   bug 284, loop while function()=x

26.10.1998  HH
   bug TB369, on CASE statement call CaseExpression.

10.11.1998  HH
   bug TB370, no exception for string parameters, if a constant is return.

23.11.1998  HH
   bug XC284, now fixed for "IF" too.

1999.01.06  DGC
   For GO's we don't correctly set MetaDLL_Name in the XPG.  Look for
   "DomainAndGlobalOpGroupName" for the change.

15.01.1999  HH
   bug XC284, new variant, more than one temp variable generated.
   bug occurred on: LOOP WHILE f1( x ) == 0 AND f2 ( x ) == 0.

*/

#define ERROR_ON_UNARY_MINUS( x )\
   lUnaryOperator = lGlbUnaryOperator;\
   lGlbUnaryOperator = 0;\
   if ( lUnaryOperator ) {\
       SyntaxError( vSubtask, eQINVALIDUNARYOPERATOR, x );\
       break; }

// Global Variables
zSHORT nParameterErrorMessage; // Prevent multiple error messages
zSHORT nParameterCount;        // Check # of params ok
zSHORT nCheckParameterCount;   // switch check # of params
static zLONG lGlbUnaryOperator = 0;
static zCHAR szGlbVariable[ 64 ] = { 0 };

static zLONG ForceExprIntoParens( zVIEW vExpression );
static void ResetExprView( void );
static zSHORT ParameterCheck( zVIEW lpExprView, zPLONG plErrorPara );
static zSHORT CheckParaWithSource( void );
static zVOID fnAddDefaultReturn( zVIEW vExpression );
static zSHORT OperationNameValid( zPCHAR szToken );
static zSHORT UnaryOperatorConstant( zVIEW vSubtask );
static void SetCursorNoWhere( zVIEW vSubtask );
static void ForNoWhere( zVIEW vSubtask );

/////////////////////////////////////////////////////////////////////////////
//
// OPERATIONS: ActionQ
//             ForceExprIntoParens
//
/////////////////////////////////////////////////////////////////////////////

//
// OPERATION: ActionQ
//
// DESCRIPTION: For every "production" recognized by the parser, one of two events is
//    spawned.  Either an Action is performed or a syntax error is raised.  Everything
//    done as a result of parsing is passed through here.  This function (ActionQ) and
//    SyntaxError are the only callback functions invoked by yyparse.  All Actions are
//    mutually exclusive.
//
zOPER_EXPORT zLONG OPERATION
ActionQ( zVIEW vSubtask, zLONG lActionRequested ) // number of the action requested
{
   zLONG  lType;
   zLONG  lResultID;
   zLONG  lVarDataType;
   zLONG  lIDNumber;
   zLONG  lDefineZKey;
   zLONG  lTempID;
   zLONG  lDataClass;
   zLONG  lOperType;
   zLONG  lSearchOrder;
   zLONG  lStatement, lStatement2;
   zLONG  lVariable, lVariable2;
   zLONG  lError;
   zVIEW  lpLODTempView;
   zVIEW  lpTempView;
   zVIEW  vTempView;
   zVIEW  vTargetView;
   zVIEW  vSource;
   zVIEW  vProgram;
   zCHAR  szType[ 2 ];
   zCHAR  szWorkPFlag[ 2 ];
   zCHAR  szTempViewName[ 33 ];
   zCHAR  szErrorMsg[ 256 ];
   zLONG  lUnaryOperator;
   zLONG  lRC;
   static zLONG lBreakFlag = 1;  // to determine if a BREAK should be generated (not immediately after a RETURN)

   if ( g_lOperationFlag != 3 )  // if not position, check to see if we want to do work
   {
      if ( g_lOperationFlag == 2 )  // update
      {
         switch( lActionRequested )
         {
            case aQSETOPERATIONTYPE:              // 199
            case aQADDOPERATIONBYNAME:            // 100
            case aQINSERTOPERATIONENDSTMT:        // 211
            case aQTURNOFFTEXTSAVE:               // 226
               break;

            // anything else
            default:
               return( 0 );
         }
      }
      else  // create
      {
         switch( lActionRequested )
         {
            case aQSETOPERATIONTYPE:              // 199
            case aQADDOPERATIONBYNAME:            // 100
            case aQMARKLASTVARASPARM:             // 173
            case aQMARKLASTVARASPARMPTR:          // 200

            case aQSETLASTDATATYPEINTEGER:        // 103
            case aQSETLASTDATATYPEDECIMAL:        // 104
            case aQSETLASTDATATYPESTRING:         // 105
            case aQSETLASTDATATYPEENTITYNAME:     // 106
            case aQSETLASTDATATYPEATTRIBUTENAME:  // 107
            case aQSETLASTDATATYPESHORT:          // 219
            case aQSETLASTDATATYPECHARACTER:      // 220

            case aQDECLARELOCALVARIABLE:          // 108
            case aQADDVIEWVARIABLE:               // 109
            case aQLOADDEFASINSTANCE:             // 111
            case aQSETSTRINGDEFINEDLENGTH:        // 113
            case aQINSERTOPERATIONENDSTMT:        // 211
            case aQTURNOFFTEXTSAVE:               // 226
            case aQLOADDEFFROMVOR:                // 227

            case aQBEGINPARMLIST:                 // 212
            case aQENDPARMLIST:                   // 213
               break;

            // anything else
            default:
               return( 0 );
         }
      }
   }

   if ( lBreakFlag < 2 )
      lBreakFlag++;

   switch( lActionRequested )
   {
      // This global is used to hold the qualifying type of operation the user is attempting to
      // create.  The current operation types are: GLOBAL (1053), LOCAL (1054), OBJECT (1055),
      // DIALOG (1056) and DOMAIN (1057).
      case aQSETOPERATIONTYPE:

         g_lAddToSrc = 0;
         nParameterErrorMessage = 0;
         nParameterCount = 0;
         nCheckParameterCount = 0;

         // All statements will be stored as relative to this line.
         g_lRelativeLineNumber = qqlineno;

         // If it is to position or update the operation, we don't really need to be here
         if ( g_lOperationFlag == 3 || g_lOperationFlag == 2 )  // position or update
            break;

         // If called for create but there was no Prebuild operation, then prebuild it.
         if ( g_lOperationFlag == 1 )  // create
         {
            // prebuild but set only some attributes
            //if ( sQToken.lToken == qLOCAL )
            PreBuildOperation( sQToken.lToken, qqlineno ); // does nothing at this time
         }

         // If the type has a fixed format parameter list, we need to identify this here.
         g_lOperationType = sQToken.lToken;
         break;

      // This is the case where the name of the operation is known as well as the operation type, but not the parm list.  What needs to be done is to
      // update the operation name in the program object and initialize values as necessary.
      case aQADDOPERATIONBYNAME:
         // Call to the add the operation.  If this was called to only position on this operation, then simply do a set cursor first entity by operation name.

         // If called to position only ...
         if ( g_lOperationFlag == 3 ) // position
         {
            lRC = ResetOperation( sQToken.szToken );

            // If it is there and good, return.
            if ( lRC == 0 )
               break;
            else
               SyntaxError( vSubtask, eQNOOPERATIONNAMEGIVEN, sQToken.szToken );
         }
         else
         if ( g_lOperationFlag == 2 ) // update
         {
            // If called to update the operation ...
            lRC = ResetOperation( sQToken.szToken );

            // If it is there, update the line number, otherwise add the signature.
            if ( lRC == 0 )
            {
               SetAttributeFromInteger( g_lpPIView, "OperationSource", "LineNumber", g_lRelativeLineNumber );
               break;
            }
         }

         // If it was not there, we need to add it from scratch.
         if ( g_lOperationFlag == 1 ) // create
         {
            nCheckParameterCount = 1;
            if ( OperationNameValid( sQToken.szToken ) )
               AddOperationEntityToPI( vSubtask, sQToken.szToken, 1 ); // show in list
            else
               SyntaxError( vSubtask, eQNOOPERATIONNAMEGIVEN, sQToken.szToken );
         }

         //g_lOperationType = 0;
         break;

      // Set a flag to indicate that the locals about to be declared are in a parameter list. If they are, then we need to update them here.
      // If they are not in the parameter list, then we need to add them later.
      case aQBEGINPARMLIST:
         g_lFlag = 1;
         break;

      // Turn off above mentioned flag since we are done with the parameter list.
      case aQENDPARMLIST:
         if ( nCheckParameterCount )
         {
            nCheckParameterCount = 0;
            if ( nParameterCount != CountEntitiesForView( g_vSourceMeta, "Parameter" ) )
            {
               SyntaxError( vSubtask, eQINVALIDFUNCTIONDEF, " - wrong number of params" );
            }
         }

         g_lFlag = 0;
         break;

      // Since we are positioned on a local var, mark it as being a parameter.
      case aQMARKLASTVARASPARM:
         // If we are not creating the operation entity, get out now.
         if ( g_lOperationFlag != 1 ) // not create
            break;

         szWorkPFlag[ 0 ] = 0;
         nParameterCount++;

         // If the Operation already exists in the source meta, then we want to check that the parameter definition is in sync with the
         // parameters defined in the source meta.  Otherwise an error is raised.
         if ( g_lAddToSrc == 0 )
         {
            // NOT a new operation.
            if ( CheckParaWithSource( ) )
            {
                if ( nParameterErrorMessage == 0 )
                   SyntaxError( vSubtask, eQINVALIDFUNCTIONPARAM, "" );

                nParameterErrorMessage++;
                break;
            }

            // Copy the unsigned flag to the TZVSPOOO object. HH,17.06.1998
            if ( g_lLastTypeDeclared == qTINTEGER || g_lLastTypeDeclared == qTSHORT || g_lLastTypeDeclared == qTDECIMAL )
            {
               zCHAR szUFlag[ 2 ];

               szUFlag[ 0 ] = 0;
               GetStringFromAttribute( szUFlag, zsizeof( szUFlag ), g_vSourceMeta, "Parameter", "UFlag" );
               SetAttributeFromString( g_lpPIView, "Variable", "UFlag", szUFlag );
            }

            GetStringFromAttribute( szWorkPFlag, zsizeof( szWorkPFlag ), g_vSourceMeta, "Parameter", "PFlag" ); // pointer flag
         }

         // If the parameter was a string, it is always a pointer ... however, the "pointer" flag for a string indicates, that
         // it is "return" (writable or mutable in javaspeak).
         if ( g_lLastTypeDeclared == qTSTRING || g_lLastTypeDeclared == qTENTITYNAME || g_lLastTypeDeclared == qTATTRIBUTENAME || szWorkPFlag[ 0 ] == 'Y' )
         {
            SetAttributeFromInteger( g_lpPIView, "Variable", "ParameterFlag", 2 ); // parameter and pointer

            // Pointer flag is taken from parameter definition.
            if ( szWorkPFlag[ 0 ] == 'Y' )
               SetAttributeFromString( g_lpPIView, "Variable", "PFlag", "Y" );
         }
         else
         {
            SetAttributeFromInteger( g_lpPIView, "Variable", "ParameterFlag", 1 );  // parameter
         }

         // Need to add the parms to source.
         if ( g_lAddToSrc )
         {
            zCHAR cZeidonType[ 2 ];

            CreateMetaEntity( vSubtask, g_vSourceMeta, "Parameter", zPOS_AFTER );
            ConvertVMLTypeToZeidonType( cZeidonType, g_lLastTypeDeclared );
            SetAttributeFromString( g_vSourceMeta, "Parameter", "DataType", cZeidonType );
            SetMatchingAttributesByName( g_vSourceMeta, "Parameter", g_lpPIView, "Variable", zSET_NULL );

            // If we are adding the operation to the source file, we do not know whether the parameter is return (pointer) or not.  Therefore,
            // the PointerFlag is cleared.  If a parameter is designed to be "update", it must be manually changed.
            SetAttributeFromString( g_vSourceMeta, "Parameter", "PFlag", "" );
            SetAttributeFromAttribute( g_vSourceMeta, "Parameter", "ShortDesc", g_lpPIView, "Variable", "Name" );
         }
         else
         {
            // Set cursor to next parameter in g_vSourceMeta for the next time into this code.
            SetCursorNextEntity( g_vSourceMeta, "Parameter", "" );
         }

         break;

      // Since we are positioned on a local var, mark it as being a parameter and a pointer.
      case aQMARKLASTVARASPARMPTR:
         // HH: we never come here !?
         // If we are not creating the operation entity, get out now
         if ( g_lOperationFlag != 1 ) // not create
            break;

         SetAttributeFromInteger( g_lpPIView, "Variable", "ParameterFlag", 2 ); // parameter and pointer

         SetAttributeFromString( g_lpPIView, "Variable", "PFlag", "Y" ); // is a parameter and a pointer
         if ( g_lAddToSrc )
         {
            zCHAR cZeidonType[ 2 ];

            CreateMetaEntity( vSubtask, g_vSourceMeta, "Parameter", zPOS_AFTER );
            ConvertVMLTypeToZeidonType( cZeidonType, g_lLastTypeDeclared );
            SetAttributeFromString( g_vSourceMeta, "Parameter", "DataType", cZeidonType );
            SetAttributeFromString( g_vSourceMeta, "Parameter", "PFlag", "Y" );
            SetMatchingAttributesByName( g_vSourceMeta, "Parameter", g_lpPIView, "Variable", zSET_NULL );
         }

         break;

      // The last datatype keyword encountered was INTEGER.
      case aQSETLASTDATATYPEINTEGER:
         g_lDeclaredStringLength = 0;
         g_lLastTypeDeclared = qTINTEGER;
         break;

      // The last datatype keyword encountered was DECIMAL.
      case aQSETLASTDATATYPEDECIMAL:
         g_lDeclaredStringLength = 0;
         g_lLastTypeDeclared = qTDECIMAL;
         break;

      // The last datatype keyword encountered was STRING.
      case aQSETLASTDATATYPESTRING:
         //g_lDeclaredStringLength = 0;
         g_lLastTypeDeclared = qTSTRING;
         break;

      // The last datatype keyword encountered was SHORT.
      case aQSETLASTDATATYPESHORT:
         //g_lDeclaredStringLength = 0;
         g_lLastTypeDeclared = qTSHORT;
         break;

      // The last datatype keyword encountered was CHARACTER.
      case aQSETLASTDATATYPECHARACTER:
         g_lDeclaredStringLength = 2;
         g_lLastTypeDeclared = qTCHARACTER;
         break;

      // The last datatype keyword encountered was ENTITYNAME.
      case aQSETLASTDATATYPEENTITYNAME:
         g_lDeclaredStringLength = 0;
         g_lLastTypeDeclared = qTENTITYNAME;
         break;

      // The last datatype keyword encountered was ATTRIBUTENAME.
      case aQSETLASTDATATYPEATTRIBUTENAME:
         g_lDeclaredStringLength = 0;
         g_lLastTypeDeclared = qTATTRIBUTENAME;
         break;

      // This is the action called to declare a local variable that is either in the declaration list or is in the parameter list.
      case aQDECLARELOCALVARIABLE:
         // If we are creating the operation signature where this declaration is not part of a parameter list, then break because
         // this will be declared in the body on the next pass.
         //   g_lFlag == 1 implies variable is in a parmlist
         if ( g_lOperationFlag == 1 && g_lFlag != 1 ) // create
            break;

         // If we are just positioning and we are in a parameter list, then position on the correct parm.
         //   g_lFlag == 1 implies variable is in a parmlist
         if ( g_lOperationFlag == 3 && g_lFlag == 1 ) // position
         {
            SetCursorFirstEntityByString( g_lpPIView, "Variable", "Name", sQToken.szToken, "" );
            break;
         }

         // If this is a local declaration within the body of the operation, then do the actual declaration here.
         AddVariableEntityToPI( vSubtask, sQToken.szToken,  // var name
                                g_lLastTypeDeclared,        // data type
                                g_lDeclaredStringLength,    // strlen if applicable
                     //jeff2    qqlineno );                 // line defined on
                                qqlineno - g_lRelativeLineNumber );

         break;

      // Sets the defined length of the declared string.
      case aQSETSTRINGDEFINEDLENGTH:
         // If we are in a create situation and this string is not a parameter, get out.
         //   g_lFlag == 1 implies variable is in a parmlist
         if ( g_lOperationFlag == 1 && g_lFlag != 1 ) // create
            break;

         // If we are positioning then just position.
         //   g_lFlag == 1 implies variable is in a parmlist
         if ( g_lOperationFlag == 3 && g_lFlag == 1 ) // position
            break;

         // Otherwise, translate the string to a number.
         if ( sQToken.lTokenClass == qCONSTANT )
         {
            g_lDeclaredStringLength = zatol( sQToken.szToken );  // text of number in .szToken
         }
         else
         {
            lDefineZKey = GetDefineZKey( vSubtask, &lVarDataType, sQToken.szLastToken );
         }

         break;

      // This is called when attempting to add a new view.
      case  aQADDVIEWVARIABLE:
         // If we are in a create situation and this view is not a parameter, get out.
         //   nOperation == 1 implies we are creating not updating
         //   g_lFlag == 1 implies variable is in a parmlist
         if ( g_lOperationFlag == 1 && g_lFlag != 1 ) // create
            break;

         // strcpy_s( g_szViewName, zsizeof( g_szViewName ), sQToken.szToken );
         g_lLastTypeDeclared = qTVIEW;

         // If we are trying to establish position, then do it.
         //   g_lFlag == 1 implies variable is in a parmlist
         if ( g_lOperationFlag == 3 && g_lFlag == 1 ) // position
         {
            SetCursorFirstEntityByString( g_lpPIView, "Variable", "Name", sQToken.szToken, "" );
            break;
         }

         // Otherwise, create a variable of type VIEW.
         AddVariableEntityToPI( vSubtask, sQToken.szToken, qTVIEW, 0, qqlineno - g_lRelativeLineNumber );
         break;

      // When a view is declared, the def of the view is loaded as an instance of the object object.  The view to this object
      // is then stored as the value of the view variable for faster retrieval during the parse.
      case  aQLOADDEFASINSTANCE:
         // If we are in a create situation and this view is not a parameter, get out.
         //   nOperation == 1 implies we are creating not updating
         //   g_lFlag == 1 implies variable is in a parmlist
         if ( g_lOperationFlag == 1 && g_lFlag != 1 ) // create
            break;

         // Check that we have access to the LOD via the view name.  If this is the first time the LOD will be loaded, then
         // do an activate from the meta for the OI.
         lRC = SetCursorFirstEntityByString( g_vLODList, "W_MetaDef", "Name", sQToken.szToken, "" );

         // If the LOD is in the MetaList, activate it.
         if ( lRC == zCURSOR_SET )
         {
            GetIntegerFromAttribute( (zPLONG) &lpTempView, g_lpPIView, "Variable", "Value" );
            if ( lpTempView == 0 )
            {
               // activate the meta
               lRC = ActivateMetaOI( vSubtask, &lpTempView, g_vLODList, zREFER_LOD_META, zSINGLE );
               if ( lRC == 1 )
               {
                  // Set the value of the view variable to be the view pointer so we can get access later without having to
                  // know the def name (since it will be overwritten as parsing continues).
                  SetAttributeFromInteger( g_lpPIView, "Variable", "Value", (zLONG) lpTempView );
               }
            }

            break;
         }

         SyntaxError( vSubtask, eQLODCOULDNTBELOADED, "" );
         break;

      // When a view is declared, the def of the view is loaded as an instance of the object object.  The view to this object
      // is then stored as the value of the view variable for faster retrieval during the parse.
      case  aQLOADDEFFROMVOR:
         // If we are in a create situation and this view is not a parameter, get out.
         //   nOperation == 1 implies we are creating not updating
         //   g_lFlag == 1 implies variable is in a parmlist
         if ( g_lOperationFlag == 1 && g_lFlag != 1 )  // create
            break;

         // Check that we have access to the VOR via the view name.
         // If this is the first time the VOR will be loaded, then do an activate from the meta for the OI.
         lRC = SetCursorFirstEntityByString( g_vVORList, "W_MetaDef", "Name", sQToken.szToken, "" );

         // If the VOR is in the MetaList, activate it.
         if ( lRC >= zCURSOR_SET )
         {
            // activate the meta
            lRC = ActivateMetaOI( vSubtask, &lpTempView, g_vVORList, zREFER_VOR_META, zSINGLE );
            if ( lRC >= 0 )
            {
               lRC = SetCursorFirstEntityByAttr( g_vLODList, "W_MetaDef", "Name", lpTempView, "LOD", "Name", "" );

               if ( lRC < 0 )
               {
                  // There's something wrong with the VOR list.
                  MessageSend( vSubtask, "VM00101", "VML Parser",
                               "Error in Named View list.  Call System Support.",
                               zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
               }
               else
               {
                  // activate the meta
                  lRC = ActivateMetaOI( vSubtask, &lpLODTempView, g_vLODList, zREFER_LOD_META, zSINGLE );
                  if ( lRC == 1 )
                  {
                     // Set the value of the view variable to be the view pointer so we can get access later without having to
                     // know the def name (since it will be overwritten as parsing continues).
                     SetAttributeFromInteger( g_lpPIView, "Variable", "Value", (zLONG) lpLODTempView );
                  }
               }

               DropMetaOI( vSubtask, lpTempView );
            }

            // Stop here if already done.
            //   g_lFlag == 1 implies variable is in a parmlist
            if ( g_lOperationFlag == 3 && g_lFlag == 1 ) // position
               break;

            GetIntegerFromAttribute( &lTempID, g_lpPIView, "Variable", "ID" );
            BuildGetView( vSubtask, (zSHORT) lTempID, sQToken.szToken, qCONSTANT, -1, "zLEVEL_TASK" );
            break;
         }

         SyntaxError( vSubtask, eQVORCOULDNTBELOADED, "" );
         break;

      // STOPPED HERE
      // To put in an IF statement after the condition is gathered.
      case aQINSERTIFSTMT:
         // Dump the stack and output the if statement
         AddOperatorToView( vSubtask, g_vGlobalView, -1 );
         ForceExprIntoParens( g_vGlobalView );
         CreateEntity( g_lpExprView, "Expression", zPOS_AFTER );
         CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );

         // Don C Remarks - 11/10/96
         // OptimizeComplexExpression is not working correctly for
         // arithmetic expressions in an IF statement.  At this time, I do
         // not want to try and correct the problem because the code is also
         // used to process assign statements and since I don't really
         // understand what is required here, I am as likely to create new
         // problems as correct the old.  It also does not appear very
         // important to allow arithmetic expressions in IF statements, since
         // none have been used up to this point.  I am thus adding code to
         // return an error if an arithmetic operator is used in an IF statement.

         // Loop through all statements and check for any arithmetic operators (Offset = 3002, 3003, 3004 or 3005) are used.
         lRC = SetCursorFirstEntityByInteger( g_vGlobalView, "ExprNode", "ElementClass", qOPERATOR, 0 );
         while ( lRC >= zCURSOR_SET )
         {
            GetIntegerFromAttribute( &lOperType, g_vGlobalView, "ExprNode", "Offset" );
            if ( lOperType == 3002 || lOperType == 3003 || lOperType == 3004 || lOperType == 3005 )
            {
               SyntaxError( vSubtask, eQINVALIDARITHMETICEXPRINIF, "" );
               break;
            }

            lRC = SetCursorNextEntityByInteger( g_vGlobalView, "ExprNode", "ElementClass", qOPERATOR, 0 );
         }

         OptimizeExpression( vSubtask, vTargetView, g_vGlobalView );
         AddStatementEntityToPI( vSubtask, qIF, sQToken.lLastLineNo, vTargetView, zPOS_AFTER );
         ResetExprView();
         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;

         break;

      // To put in an else statement.
      case aQINSERTELSESTMT:
         AddStatementEntityToPI( vSubtask, qELSE, qqlineno, g_vGlobalView, zPOS_AFTER );
         break;

      case aQTURNOFFTEXTSAVE:
         g_lSaveText = 0;
         break;

      case aQINSERTOPERATIONENDSTMT:

         if ( g_lOperationFlag != 1 && g_lOperationFlag != 2 ) // not create and not update
         {
            // We need to see if a return statement exists.  If there is a return anywhere here, then we should be fine,
            // otherwise we will need to generate one.
            if ( SetCursorFirstEntityByInteger( g_vStatementView, "Statement", "Class", qRETURN, "" ) == zCURSOR_SET ||
                 SetCursorFirstEntityByInteger( g_vStatementView, "Statement", "Class", qRETURNEND, "" ) == zCURSOR_SET )
            {
            // SetNameForView( g_vStatementView, "g_vStatementView", vSubtask, zLEVEL_TASK );
            // MessageSend( g_vStatementView, "", "Before Do Something Here", "g_StatementView Check Statement.Offset", 0, 0 );
               SetAttributeFromInteger( g_vStatementView, "Statement", "Class", qRETURNEND );
            // MessageSend( g_vStatementView, "", "After Do Something Here", "g_StatementView Check Statement.Offset", 0, 0 );
            }
            else
            {
               // no RETURN found, generate one
               zCHAR szReturnType[ 2 ] = { 0 };
               GetStringFromAttribute( szReturnType, zsizeof( szReturnType ), g_vStatementView, "Operation", "ReturnDataType" );
               SetCursorLastEntity( g_vStatementView, "Statement", "" );
               if ( szReturnType[ 0 ] == 0 || szReturnType[ 0 ] == 'O' )
               {
                  // The return type is void ... add a simple dummy return.  The -1 as the third parameter signifies that this is the last return.
                  AddReturnStatement( vSubtask, qCONSTANT, -1, NULL, zPOS_BEFORE );
               }
               else
               {
                  // The return type is not void ... add a dummy return( 0 ).  The -1 as the third parameter signifies that this is the last return.
                  AddReturnStatement( vSubtask, qCONSTANT, -1, "0", zPOS_BEFORE );
               }
            }

            lRC = SetCursorFirstEntityByInteger( g_lpPIView, "Variable", "DataType", qTVIEW, "" );
            while ( lRC == zCURSOR_SET )
            {
               lRC = GetIntegerFromAttribute( (zPLONG) &lpTempView, g_lpPIView, "Variable", "Value" );
               if ( lpTempView > 0 )
               {
                  DropMetaOI( vSubtask, lpTempView );
               }

               lRC = SetCursorNextEntityByInteger( g_lpPIView, "Variable", "DataType", qTVIEW, "" );
            }
         }

         g_lOperationType = 0;               // reinit
         g_lSaveText = 0;

         if ( g_lParseLimit == zPARSE_LIMIT_OPERATION )  // == 2
         {
            // If we finished the end of the operation we may need to update the beginning line numbers of the opers that follow.
            if ( g_lOperationFlag == 1 )  // create
               g_lOperationFlag++;

            if ( g_lOperationFlag == 3 )  // position
               SkipRemainingFile( );
         }

         break;

      // To put in an end statement
      case aQINSERTENDSTMT:

         // Skip creating END statement if it already exists.  Also, if a FORIF statement exists, delete it, add an END statement
         // and return an additional subobject level.
         lRC = CheckExistenceOfEntity( g_vStatementView, "Statement" );
         if ( lRC != zCURSOR_SET )
         {
            AddStatementEntityToPI( vSubtask, qEND, qqlineno, g_vGlobalView, zPOS_AFTER );
            break;
         }

         GetIntegerFromAttribute( &lDataClass, g_vStatementView, "Statement", "Class" );
         if ( lDataClass == qEND )
         {
            ResetViewFromSubobject( g_vStatementView );
            CreateViewFromViewForTask( &vTempView, g_vStatementView, 0 );
            SetCursorNextEntity( vTempView, "Statement", "" );
            GetIntegerFromAttribute( &lDataClass, vTempView, "Statement", "Class" );
            if ( lDataClass == qFORIF )
            {
               DeleteEntity( vTempView, "Statement", zREPOS_NONE );
               SetCursorLastEntity( g_vStatementView, "Statement", "" );
               AddStatementEntityToPI( vSubtask, qEND, qqlineno, g_vGlobalView, zPOS_AFTER );
            }

            DropView ( vTempView );

         }
         else
            AddStatementEntityToPI( vSubtask, qEND, qqlineno, g_vGlobalView, zPOS_AFTER );

         break;

      // To put in an until statement after condition is gathered.
      case aQINSERTUNTILSTMT:
         // Dump the stack and output the until statement
         AddOperatorToView( vSubtask, g_vGlobalView, -1 );
         ForceExprIntoParens( g_vGlobalView );

         // Add NOT to the end of the expression ... another set of parens is required.
         SetCursorLastEntity( g_vGlobalView, "ExprNode", "" );
         InsertExprNodeValuesToEntity( g_vGlobalView, qOPERATOR, 0, qTINTEGER, qNOT, 0, "", 0, zPOS_AFTER );

         // Another set of parens is required.
         ForceExprIntoParens( g_vGlobalView );
         CreateEntity( g_lpExprView, "Expression", zPOS_AFTER );
         CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );
         OptimizeExpression( vSubtask, vTargetView, g_vGlobalView );
         AddStatementEntityToPI( vSubtask, qUNTIL, sQToken.lLastLineNo, vTargetView, zPOS_AFTER );
         ResetExprView( );
         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;
         break;

      // To put in an while statement after condition is gathered.
      case aQINSERTWHILESTMT:
         // Dump the stack
         AddOperatorToView( vSubtask, g_vGlobalView, -1 );
         ForceExprIntoParens( g_vGlobalView );
         CreateEntity( g_lpExprView, "Expression", zPOS_AFTER );
         CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );

         // bug XC284
         // prepare to check, whether OptimizeExpression generates another statement and a temp variable.
         //   For checking the statements, we must use g_vStatementView, which handles the recursive stuff. If there was an,
         //   for example, the view has been set one level down.
         CreateViewFromViewForTask( &vProgram, g_lpPIView, 0 );
         lStatement = CountEntitiesForView( g_vStatementView, "Statement" );
         lVariable = CountEntitiesForView( vProgram, "Variable" );
         OptimizeExpression( vSubtask, vTargetView, g_vGlobalView );
         lStatement2 = CountEntitiesForView( g_vStatementView, "Statement" );
         lVariable2 = CountEntitiesForView( vProgram, "Variable" );
         AddStatementEntityToPI( vSubtask, qWHILE, sQToken.lLastLineNo, vTargetView, zPOS_AFTER );

         if ( g_lWhereIndex >= 0 && (g_lWhereOp[ g_lWhereIndex ] == qEXISTS || g_lWhereOp[ g_lWhereIndex ] == qNOTEXISTS) )
         {
            AddEntityOperWithNoScope( vSubtask, "CheckExistenceOfEntity", g_lViewID, g_szEntityName, g_lEntityID, 0, "", g_lScopeViewID );
            g_lAddNextStatementBefore++;
         }
         else
         if ( lStatement2 > lStatement && lVariable2 > lVariable )
         {
            // Did OptimizeExpression generate a temp variable and a statement to set it?
            // if yes, then we have something similar to following situation:
            // VML : LOOP WHILE function = x
            // C : TempVariable = function();
            //     while ( TempVariable == x )
            //     { Body of while }
            // In that case, the setting of tempvariable must be copied into the body of the while loop.
            //  It is done in the statement(s), before WHILE.
            //
            //  Duplicate statements into WHILE body
            //  The number of variables generated (and statements to set the variables) is
            //  lStatement2 - lStatement, or lVariable2 - lVariable (should be the same).
            zLONG l;
            zSHORT zPOS = zPOS_AFTER;

            // g_vStatementView is on Statement = Substatement under WHILE
            CreateViewFromViewForTask( &vTempView, g_vStatementView, 0 );
            ResetViewFromSubobject( vTempView );
            // vTempView is on Statement = WHILE

            // Position on the first statement generated new and copy statements to the end of the loop body backward.
            for ( l = lStatement2; l > lStatement; l-- )
            {
               SetCursorPrevEntity( vTempView, "Statement", "" );

               // g_vStatementView is positioned on "Substatement" underneath "while"
               CreateEntity( g_vStatementView, "Statement", zPOS );
               zPOS = zPOS_BEFORE;

               // copy the statement
               SetMatchingAttributesByName( g_vStatementView, "Statement", vTempView, "Statement", zSET_ALL );
            // DisplayObjectInstance( g_vStatementView, "", "" );
            // MessageSend( g_vStatementView, "???", "Title1", "StatementView", 0, 0 );
            }

            g_lAddNextStatementBefore++;
            DropView( vTempView );
         }

         DropView( vProgram );
         ResetExprView( );

         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;

         break;

      // Insert the loop statement
      case aQINSERTLOOPSTMT:

         // Reset g_lWhereIndex to 0, so that its check in aQINSERTWHILESTMT is done correctly if the loop does not have a WHERE clause.
         g_lWhereIndex = 0;
         g_lWhereOp[ g_lWhereIndex ] = 0;
         AddStatementEntityToPI( vSubtask, qLOOP, qqlineno, g_vGlobalView, zPOS_AFTER );
         break;

      // Need to delete the loop since we have a while statement.  Having both is redundant.
      //
      case aQDELETELOOPSTMT:
         ResetViewFromSubobject( g_vStatementView );
         DeleteEntity( g_vStatementView, "Statement", zPOS_BEFORE );
      // DisplayObjectInstance( g_vStatementView, "", "" );
      // MessageSend( g_vStatementView, "???", "Title2", "StatementView", 0, 0 );
         break;

      // add a case statement
      case aQINSERTCASESTMT:
         // Dump the stack
         AddOperatorToView( vSubtask, g_vGlobalView, -1 );
         CreateEntity( g_lpExprView, "Expression", zPOS_AFTER );
         CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );
//       OptimizeExpression( vSubtask, vTargetView, g_vGlobalView );
         CaseExpression( vSubtask, vTargetView, g_vGlobalView );  //**HH**

         AddStatementEntityToPI( vSubtask, qCASE, qqlineno, vTargetView, zPOS_AFTER );
         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;
         ResetExprView( );
         break;

      // to add a simple set cursor XXXX statement
      case aQSETCURSORLASTCONTROL:
         // break the entity qualifier up into its two component parts the View and the Entity Name
         SplitQualifier( sQToken.szLastToken, // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         g_sWhereLeft[ 0 ].lDataClass = VerifyQualifier( vSubtask, qENTITYQUALIFIER,
                                                         g_szViewName, &g_lViewID,
                                                         g_szEntityName, &g_lEntityID,
                                                         g_szAttributeName, &g_lAttributeID );
         break;

      // for use with an under clause
      case aQSETSCOPE:
         SplitQualifier( sQToken.szToken,          // token to be split
                         g_szScopeViewName,        // string to store view in
                         g_szScopeEntityName,
                         g_szScopeAttributeName ); // String to store attr

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szScopeViewName, &g_lScopeViewID,
                          g_szScopeEntityName, &g_lScopeEntityID, g_szScopeAttributeName, &g_lScopeAttributeID );
         break;

      case aQSETOBJECTSCOPE:
         g_szScopeEntityName[ 0 ] = '\1';
         break;

      case aQSAVENAMEVIEWNAME:
         strcpy_s( g_szViewName, zsizeof( g_szViewName ), sQToken.szLastToken );
         g_szEntityName[ 0 ] = 0;
         break;

      case aQSAVENAMEVIEWCONSTANT:
         strcpy_s( g_szScopeViewName, zsizeof( g_szScopeViewName ), sQToken.szToken );
         g_lScopeViewID = -1;
         break;

      case aQSAVENAMEVIEWVARIABLE:
         strcpy_s( g_szScopeViewName, zsizeof( g_szScopeViewName ), sQToken.szToken );
         GetVariableID( &g_lScopeViewID, sQToken.szToken );
         break;

      case aQADDNAMEVIEW:
         lRC = GetVariableID( &lIDNumber, g_szViewName );
         if ( lRC == -1 )
         {
            SyntaxError( vSubtask, eQVARIABLEUNDEFINED, g_szViewName );
            break;
         }

         if ( g_szEntityName[ 0 ] == 0 )
            strcpy_s( g_szEntityName, zsizeof( g_szEntityName ), "zLEVEL_TASK" );

         BuildNameView( vSubtask, (zSHORT) lIDNumber, g_szScopeViewName, (zSHORT) g_lScopeViewID, -1, g_szEntityName ); //level

         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         g_szScopeViewName[ 0 ] = 0;
         break;

      case aQADDNAMEVIEWWITHVIEW:
         GetVariableID( &lIDNumber, g_szViewName );

         GetVariableID( &lTempID, sQToken.szToken );

         if ( g_szEntityName[ 0 ] == 0 )
            strcpy_s( g_szEntityName, zsizeof( g_szEntityName ), "zLEVEL_TASK" );

         BuildNameView( vSubtask, (zSHORT) lIDNumber, g_szScopeViewName, (zSHORT) g_lScopeViewID, (zSHORT) lTempID, g_szEntityName ); //level

         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         g_szScopeViewName[ 0 ] = 0;
         break;

      case aQSAVEGETVIEWID:
         lRC = GetVariableID( &g_lGetViewID, sQToken.szToken );
         if ( lRC == -1 )
            SyntaxError( vSubtask, eQVARIABLEUNDEFINED, sQToken.szToken );

         break;

      case aQSAVEGETVIEWNAME:
         strcpy_s( g_szViewName, zsizeof( g_szViewName ), sQToken.szToken );
         g_lViewID = qVARIABLE;
         break;

      case aQSAVEGETVIEWCONSTANT:
         strcpy_s( g_szViewName, zsizeof( g_szViewName ), sQToken.szToken );
         g_lViewID = qCONSTANT;
         break;

      case aQADDGETVIEW:
         GetVariableID( &lIDNumber, g_szViewName );
         BuildGetView( vSubtask, (zSHORT) g_lGetViewID, g_szViewName, (zSHORT) g_lViewID, -1, "zLEVEL_TASK" );
         g_szViewName[ 0 ] = 0;
         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;
         break;

      case aQADDGETVIEWATLEVEL:
         switch( sQToken.lToken )
         {
            case qSUBTASK:
               strcpy_s( g_szEntityName, zsizeof( g_szEntityName ), "zLEVEL_SUBTASK" );
               break;
            case qTASK:
               strcpy_s( g_szEntityName, zsizeof( g_szEntityName ), "zLEVEL_TASK" );
               break;
            case qAPPLICATION:
               strcpy_s( g_szEntityName, zsizeof( g_szEntityName ), "zLEVEL_APPLICATION" );
               break;
            case qSYSTEM:
               strcpy_s( g_szEntityName, zsizeof( g_szEntityName ), "zLEVEL_SYSTEM" );
               break;
            case qANY:
            default:
               strcpy_s( g_szEntityName, zsizeof( g_szEntityName ), "zLEVEL_ANY" );
               break;
         }
         break;

      case aQADDGETVIEWATLEVELU:
         GetVariableID( &lIDNumber, g_szViewName );
         BuildGetView( vSubtask, (zSHORT) g_lGetViewID, g_szViewName, (zSHORT) g_lViewID, -1, g_szEntityName );
         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;
         break;

      case aQADDGETVIEWATLEVELFROMLEVEL:
         GetVariableID( &lIDNumber, g_szViewName );
         GetVariableID( &lTempID, sQToken.szToken );

         BuildGetView( vSubtask, (zSHORT) g_lGetViewID, g_szViewName, (zSHORT) g_lViewID, (zSHORT) lTempID, g_szEntityName );
         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;
         break;

      case aQSETINCLUDETARGET:
         SplitQualifier( sQToken.szToken,     // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         break;

      case aQSETINCLUDESOURCE:
         SplitQualifier( sQToken.szToken,          // token to be split
                         g_szScopeViewName,        // string to store view in
                         g_szScopeEntityName,
                         g_szScopeAttributeName ); // String to store attr
         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szScopeViewName, &g_lScopeViewID,
                          g_szScopeEntityName, &g_lScopeEntityID, g_szScopeAttributeName, &g_lScopeAttributeID );
         break;

      case aQADDINCLUDEBEFORE:
         lDefineZKey = GetDefineZKey( vSubtask, &lVarDataType, "zPOS_BEFORE" );
         AddEntityOperWithEntity( vSubtask, "IncludeSubobjectFromSubobject", g_lViewID, g_szEntityName, g_lEntityID, g_szScopeViewName, g_lScopeViewID,
                                  g_szScopeEntityName, g_lScopeEntityID, qDEFINE, "zPOS_BEFORE", lDefineZKey );
         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         g_szScopeViewName[ 0 ] = 0;
         g_szScopeEntityName[ 0 ] = 0;
         g_lScopeEntityID = 0;
         break;

      case aQADDINCLUDE:
         lDefineZKey = GetDefineZKey( vSubtask, &lVarDataType, "zPOS_AFTER" );
         AddEntityOperWithEntity( vSubtask, "IncludeSubobjectFromSubobject", g_lViewID, g_szEntityName, g_lEntityID, g_szScopeViewName, g_lScopeViewID,
                                  g_szScopeEntityName, g_lScopeEntityID, qDEFINE, "zPOS_AFTER", lDefineZKey );
         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         g_szScopeViewName[ 0 ] = 0;
         g_szScopeEntityName[ 0 ] = 0;
         g_lScopeEntityID = 0;
         break;

      case aQADDEXCLUDE:
         lDefineZKey = GetDefineZKey( vSubtask, &lVarDataType, "zREPOS_AFTER" );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "ExcludeEntity", g_lViewID, g_szEntityName, g_lEntityID, qDEFINE, "zREPOS_AFTER", lResultID );
         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         break;

      case aQADDEXCLUDEBEFORE:
         lDefineZKey = GetDefineZKey( vSubtask, &lVarDataType, "zREPOS_BEFORE" );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "ExcludeEntity", g_lViewID, g_szEntityName, g_lEntityID, qDEFINE, "zREPOS_BEFORE", lResultID );
         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         break;

      case aQADDEXCLUDENONE:
         lDefineZKey = GetDefineZKey( vSubtask, &lVarDataType, "zREPOS_NONE" );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "ExcludeEntity", g_lViewID, g_szEntityName, g_lEntityID, qDEFINE, "zREPOS_NONE", lResultID );
         g_szViewName[ 0 ] = 0;
         g_szEntityName[ 0 ] = 0;
         break;

      case aQSETCURSORNOWHERE:
         SetCursorNoWhere( vSubtask );
         break;

      // to add a set cursor XXXX statement that had a where
      case aQSETCURSORWITHWHERE:
         InsertSetCursorWithWhere( vSubtask );
         g_szScopeViewName[ 0 ] = 0;
         g_szScopeEntityName[ 0 ] = 0;
         g_szScopeAttributeName[ 0 ] = 0;
         g_lScopeEntityID = 0;

         // Reset g_lWhereIndex to 0, so that its check in aQINSERTWHILESTMT is done correctly if
         // the loop does not have a WHERE clause.
         g_lWhereIndex = 0;
         g_lWhereOp[ g_lWhereIndex ] = 0;

         break;

      // add DELETE marked as AFTER
      case aQADDCREATESTMTAFTER:
         // break the entity qualifier up into its two component parts the View and the Entity Name
         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute
         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "CreateEntity", g_lViewID, g_szEntityName, g_lEntityID, qTINTEGER, "zPOS_AFTER", /*"3",*/ lResultID );
         break;

      // add create marked as BEFORE
      case aQADDCREATESTMTBEFORE:

         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "CreateEntity", g_lViewID, g_szEntityName, g_lEntityID, qTINTEGER, "zPOS_BEFORE", lResultID );
         break;

      // add create marked as FIRST
      case aQADDCREATESTMTFIRST:

         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "CreateEntity", g_lViewID, g_szEntityName, g_lEntityID, qTINTEGER, "zPOS_FIRST", lResultID );
         break;

      // add create marked as LAST
      case aQADDCREATESTMTLAST:

         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "CreateEntity", g_lViewID, g_szEntityName, g_lEntityID, qTINTEGER, "zPOS_LAST", lResultID );
         break;

      // add delete statement
      case aQADDDELETESTMT:
         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "DeleteEntity", g_lViewID, g_szEntityName, g_lEntityID, /*0,*/ qTINTEGER, /*"",*/ "zPOS_AFTER", lResultID );
         break;

      case aQADDDELETESTMTFIRST:
         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "DeleteEntity", g_lViewID, g_szEntityName, g_lEntityID, /*0,*/ qTINTEGER, /*"",*/ "zREPOS_FIRST", lResultID );
         break;

      case aQADDDELETESTMTLAST:
         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID,
                          g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "DeleteEntity", g_lViewID, g_szEntityName, g_lEntityID, /*0,*/ qTINTEGER, /*"",*/ "zREPOS_LAST", lResultID );
         break;

      case aQADDDELETESTMTPREVIOUS:
         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "DeleteEntity", g_lViewID, g_szEntityName, g_lEntityID, /*0,*/ qTINTEGER, /*"",*/ "zREPOS_PREV", lResultID );
         break;

      case aQADDDELETESTMTNONE:
         SplitQualifier( sQToken.szLastToken, // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "DeleteEntity", g_lViewID, g_szEntityName, g_lEntityID, /*0,*/ qTINTEGER, /*"",*/ "zREPOS_NONE", lResultID );
         break;

      case aQADDDELETESTMTNEXT:
         SplitQualifier( sQToken.szLastToken,  // token to be split
                         g_szViewName,         // string to store view in
                         g_szEntityName,       // string to store Entity
                         g_szAttributeName );  // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         lResultID = AddResult( vSubtask );
         AddEntityOperWithNoScope( vSubtask, "DeleteEntity", g_lViewID, g_szEntityName, g_lEntityID, /*0,*/ qTINTEGER, /*"",*/ "zPOS_NEXT", lResultID );
         break;

      case aQSETEACHFLAG:
         g_lSetFNPL = qEACH;
         break;

      case aQSETNOEACHFLAG:
         // Per request by Don/Kelly, ignore situation with no EACH qualifier.  dks ... 2012.03.29
      // g_lSetFNPL = qNOEACH;
         g_lSetFNPL = qEACH;
         break;

      case aQSETVARIABLEFLAG:
         g_lSetFNPL = qVARIABLE;

         // Need to create loop control.
         g_lLoopControlID = CreateLoopControlWithView( vSubtask, qVARIABLE, sQToken.szToken );
         ResetExprView();
         break;

      case aQSETCONSTANTFLAG:
         g_lSetFNPL = qCONSTANT;

         // Need to create loop control.
         g_lLoopControlID = CreateLoopControlWithView( vSubtask, qCONSTANT, sQToken.szToken );
         ResetExprView();
         break;

      case aQVERIFYLOADOBJECT:
         break;

      case aQADDFORNOWHERE:
         ForNoWhere( vSubtask );
         break;

      case aQADDFORWITHWHERE:
         InsertForWithWhere( vSubtask );
         g_szScopeViewName[ 0 ] = 0;
         g_szScopeEntityName[ 0 ] = 0;
         g_szScopeAttributeName[ 0 ] = 0;
         g_lScopeEntityID = 0;
         break;

      // Insert a load statement
      case aQADDLOADSTMT:

         AddStatementEntityToPI( vSubtask, qEXPRESSION, sQToken.lLastLineNo, // ??? qqlineno,
                                 g_vGlobalView, zPOS_AFTER );
         break;

      // add a stand alone expression as an operation
      case aQINSERTOPERATIONCALL:

         lRC = ParameterCheck( g_vGlobalView, &lError );
         switch ( lRC )
         {
            case 0:
               // everything fine
               break;

            case 1:
               sprintf_s( szErrorMsg, zsizeof( szErrorMsg ), " Parameter Number %ld", lError );
               SyntaxError( vSubtask, eQINVALIDFUNCTIONPARAM, szErrorMsg );
               break;

            default:
               SyntaxError( vSubtask, eQINVALIDFUNCTIONDEF, "" );
         }

         SetCursorFirstEntity( g_lpExprView, "ExprNode", 0 );

         // Dump the stack and output the operation call.
         AddOperatorToView( vSubtask, g_vGlobalView, -1 );
         CreateEntity( g_lpExprView, "Expression", zPOS_AFTER );
         CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );

         // Skip creating the expresssion if the operation being processed is unknown.
         if ( g_lOperationUnknownFlag == 1 )
         {
            g_lOperationUnknownFlag = 0;
            lRC = -1;
         }
         else
            lRC = OptimizeExpression( vSubtask, vTargetView, g_vGlobalView );

         if ( lRC == 0 )
            AddStatementEntityToPI( vSubtask, qEXPRESSION, sQToken.lLastLineNo, vTargetView, zPOS_AFTER );

         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;

         ResetExprView( );
         break;

      // found an equal sign
      case aQADDASSIGNMENTOPERATOR:
         // Insert the equal sign
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 );  // actual operator
         break;

      // add a stand alone expression as a statement
      case aQINSERTEXPRESSIONSTMT:
      {
         zVIEW vError;
         zLONG lCountErrors;

         // First we want to Dump the stack to be sure all of the operators have been placed in the expression.
         AddOperatorToView( vSubtask, g_vGlobalView, -1 );

         // Create another expression entity off of the global g_lpExprView, this is so that we have an expression to optimize into.
         CreateEntity( g_lpExprView, "Expression", zPOS_AFTER );

         // Get a view to the new expression called target view so that we have a view to the source and target expressions.
         CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );

         // Get the error object.
         GetViewByName( &vError, "TZVMEROO", vSubtask, zLEVEL_TASK );

         // Count the number of Error entities in the error object. If there are more than zero, then errors have occurred in the current parse.
         // If there are errors, then there is no need to build the current expression and put it into the XPG.
         //
         // NOTE:  This is probably slow.  When making changing for performance, maybe this logic should be changed.
         lCountErrors = CountEntitiesForView( vError, "Error" );
         if ( lCountErrors == 0 )
         {
            // No errors, so build the expression.

            // Optimize from vGlobal into vTarget.
            lRC = OptimizeExpression( vSubtask, vTargetView, g_vGlobalView );

            // If the optimize was ok and an expression node exists for view target, then add the expression statement using target as the expression for this statement.
            if ( lRC == 0 &&
                 CheckExistenceOfEntity( vTargetView, "ExprNode" ) == zCURSOR_SET )
            {
               AddStatementEntityToPI( vSubtask, qEXPRESSION, sQToken.lLastLineNo, vTargetView, zPOS_AFTER );
            }
         }

         // Now we need to be sure the expression is all cleaned up and set up for the new expression that could be built based on the upcoming parse.
         // First, drop the old one.
         DropObjectInstance( g_lpExprView );

         // Now set up a new one into vGlobal.
         InitExpressionObject( );

         // Zero the left so no trash is left hanging around.
         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;
         g_lTargetDataType = qTUNKNOWN;

         break;
      }

      // Add the name of an operation to an expression.  At this point we have the name of an operation that needs to be verified.
      // Operations need to be looked up in a particular order. First we look for a LOCALOPERATION (i.e. an operation that has been
      // defined within the same source member that we are parsing).  If it is not a LOCALOPERATION, then in order we look for OBJECT,
      // GLOBAL, and ZEIDON operations.  Get Operation Class does all of this for us.
      case aQADDOPERATIONNAMETOEXPR:
      // if ( zstrcmp( g_szOperationName, "SetCursorNextEntityHierarchical" ) == 0 )
      //    TraceLineS( "", "" );

         strcpy_s( g_szOperationName, zsizeof( g_szOperationName ), sQToken.szLastToken );
         ERROR_ON_UNARY_MINUS( "operation call" );
         break;

      // The left of an expression is an attribute qualifier.
      // DM - OCEA means Object.Class.Entity.Attribute perhaps?
      case aQADDOCEATOEXPRASTARGET:
         // split the qualifier into its parts
         SplitQualifier( sQToken.szToken, g_szViewName, g_szEntityName, g_szAttributeName );

         // Verify that the parts given are valid within the view given.  Note that if all of the "parts" are literal, then we can determine the
         // data type that we need to deal with.  It will be passed back as a side effect through AttributeID.
         lDataClass = VerifyQualifier( vSubtask, qATTRIBUTEQUALIFIER, g_szViewName, &g_lViewID,
                                       g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );

         // If all the parts are literal, then AttributeID was set to the data type of the attribute.
         if ( lDataClass == qENTITYANDATTRIBUTEARECONSTANT )
            g_lLeftDataType = g_lAttributeID;
         else
         if ( lDataClass > 0 )
            g_lLeftDataType = qTUNKNOWN;
         else
         {
            SyntaxError( vSubtask, eQATTRIBUTEQUALIFIERUNDEFINED, sQToken.szLastToken );

            // Be sure no garbage is hanging around.
            g_lLeftDataType = qTUNKNOWN;
            g_lLeftDataClass = qTUNKNOWN;
            break;
         }

         // Get the class if possible.
         g_lLeftDataClass = GetClassBasedOnType( g_lLeftDataType );
         g_lTargetDataType = g_lLeftDataType;

         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qATTRIBUTEQUALIFIER, g_lLeftDataClass, g_lLeftDataType, sQToken.szToken, 0, 0 );
         break;

      case aQADDNOTOPERATORTOEXPR:
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 );  // actual operator

         break;

      // add the left element of an expression ( like: x = ... )
      case aQADDVARIABLEASTARGET:
         // try to get the VariableID
         GetVariableID( &lIDNumber, sQToken.szLastToken );

         // If we don't get one then that's an error.  We cannot have a define for a target of an expression.
         if ( lIDNumber < 0 )
         {
            // Try to get a define id for it anyway to give a better error message.  If an attempt was made to use the define, give an error: not allowed.
            lIDNumber = GetDefineZKey( vSubtask, &g_lLeftDataType, sQToken.szLastToken );

            // If the define was found ...
            if ( lIDNumber >= 0 )
               SyntaxError( vSubtask, eQDEFINEPUTWHEREVARIABLEMUSTBE, sQToken.szLastToken );
            else
               SyntaxError( vSubtask, eQVARIABLEUNDEFINED, sQToken.szLastToken );

            // Be sure no garbage is hanging around.
            g_lLeftDataType = qTUNKNOWN;
            g_lLeftDataClass = qTUNKNOWN;
            g_lTargetDataType = qTUNKNOWN;
            break;
         }

         // Get the data type off of the variable entity.
         g_lLeftDataType = GetVariableDataType( lIDNumber );
         g_lTargetDataType = g_lLeftDataType;

         // Set the left data class.
         g_lLeftDataClass = GetClassBasedOnType( g_lLeftDataType );

         // Add the var to the expression.
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qVARIABLE, g_lLeftDataClass, g_lLeftDataType, "", lIDNumber, 0 );
         break;

      // Add the left element of an expression (like: x = ...) which must be a string.  Otherwise, we would not have the "offset".
      // If we do then the problem is that we have a bad data type for this variable.
      case aQADDVARIABLEOFFSETASTARGET:
         // get the ID of the variable
         GetVariableID( &lIDNumber, sQToken.szLastToken );

         // If the ID does not exist
         if ( lIDNumber < 0 )
         {
            // Try to get a define id for it anyway to give a better error message.  If an
            // attempt was made to use the define, give an error: not allowed.
            lIDNumber = GetDefineZKey( vSubtask, &g_lLeftDataType, sQToken.szLastToken );

            // If the define was found ...
            if ( lIDNumber >= 0 )
               SyntaxError( vSubtask, eQDEFINEPUTWHEREVARIABLEMUSTBE, sQToken.szLastToken );
            else
               SyntaxError( vSubtask, eQVARIABLEUNDEFINED, sQToken.szLastToken );

            g_lLeftDataType = qTUNKNOWN;
            g_lLeftDataClass = qTUNKNOWN;
            g_lTargetDataType = qTUNKNOWN;
            break;
         }

         // Get the data type of the variable to be sure it is a string type.
         g_lLeftDataType = GetVariableDataType( lIDNumber );
         g_lTargetDataType = g_lLeftDataType;

         // Get the data class.
         g_lLeftDataClass = GetClassBasedOnType( g_lLeftDataType );

         // Do a consistency check against string or text.  If the parm type is void, we won't do the check.
         if ( g_lLeftDataType != qTVOID )
         {
            lRC = CompareDataTypesForConsistency( g_lLeftDataType, g_lLeftDataClass, qTSTRING, qTEXT );

            // If the class is not compatible ... then error.
            if ( lRC == qNOMATCHONTYPE )
            {
               SyntaxError( vSubtask, eQVARIABLENOTSTRINGTYPE, "" );
               break;
            }
         }

         // Add the variable as is.  Optimization will happen later.
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qVARIABLE, g_lLeftDataClass, g_lLeftDataType, "", lIDNumber, 0 );
         break;

      // found a conditional operator
      case aQADDCONDOPERATORTOEXPR:
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lLastToken, 0 );  // actual operator

         break;

      // found an equal that is ==
      case aQADDCONDEQUALTOEXPR:
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", qCONDEQUAL, 0 );  // actual operator

         break;

      case aQCHECKSTOREDOCEA:
         // reinit the data type

         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;

         break; /* break supposed to be here */

      // add an and or an OR
      case aQADDJOINTOEXPR:
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 );  // actual operator

         break;

      // got an LPAREN ( as part of an expression
      case aQADDLPARENTOEXPR:
         lUnaryOperator = lGlbUnaryOperator;
         lGlbUnaryOperator = 0;
         if ( lUnaryOperator == qMINUS )
         {
            AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", qUNARYMINUS, 0 );
         }

         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 );  // actual operator

         break;

      // got an LBRACE [ as part of an expression
      case aQADDLBRACETOEXPR:
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 ); // actual operator

         // Must be an integer index, this will force it.
         g_lLeftDataType = qTINTEGER;
         g_lLeftDataClass = qNUMERIC;
         break;

      // got an RPAREN ) as part of an expression
      case aQADDRPARENTOEXPR:
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 );  // actual operator
         break;

      // got an RBRACE ] as part of an expression
      case aQADDRBRACETOEXPR:
         // Get the mini-expression that is the string and offset and copy it into a temp string replacing it with a temp id.
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 );

         // Set left type back since we are doing a string.
         g_lLeftDataType = qTSTRING;
         g_lLeftDataClass = qTEXT;
         break;

      // Add an OF statement.
      case aQINSERTOFSTMT:
         // Dump the stack
         AddOperatorToView( vSubtask, g_vGlobalView, -1 );
         CreateEntity( g_lpExprView, "Expression", zPOS_AFTER );
         CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );
         OptimizeExpression( vSubtask, vTargetView, g_vGlobalView );
         AddStatementEntityToPI( vSubtask, qOF, sQToken.lLastLineNo, vTargetView, zPOS_AFTER );

         ResetExprView( );

         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;
         break;

      // Insert an otherwise in a case.
      case aQINSERTOTHERWISESTMT:
         AddStatementEntityToPI( vSubtask, qOTHERWISE, qqlineno, g_vGlobalView, zPOS_AFTER );
         break;

      // Set cursor first.
      case aQSETFIRSTCURSOR:
         g_lSetFNPL = qFIRST;
         break;

      // Set cursor next.
      case aQSETNEXTCURSOR:
         g_lSetFNPL = qNEXT;
         break;

      // Set cursor previous.
      case aQSETPREVIOUSCURSOR:
         g_lSetFNPL = qPREVIOUS;
         break;

      // Set cursor last.
      case aQSETLASTCURSOR:
         g_lSetFNPL = qLAST;
         break;

      // Add a return statement.
      case aQADDRETURNSTATEMENT: // dks ... RETURN
         // Dump the stack and output the return statement.
         AddOperatorToView( vSubtask, g_vGlobalView, -1 );

         lRC = ForceExprIntoParens( g_vGlobalView );
         if ( lRC == -1 )
         {
            // RETURN without value ... so add a default return value according to the function type.
            fnAddDefaultReturn( g_vGlobalView );
         }

         CreateEntity( g_lpExprView, "Expression", zPOS_AFTER );
         CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );
         OptimizeExpression( vSubtask, vTargetView, g_vGlobalView );
         AddStatementEntityToPI( vSubtask, qRETURN, sQToken.lLastLineNo, vTargetView, zPOS_AFTER );
         ResetExprView();

         g_lLeftDataType = qTUNKNOWN;
         g_lLeftDataClass = qTUNKNOWN;
         lBreakFlag = 0;
         break;

      case aQSETUPWHERE:
      {
         zLONG k;

         strcpy_s( g_sWhereLeft[ 0 ].szText, zsizeof( g_sWhereLeft[0].szText ), g_szViewName );
         strcat_s( g_sWhereLeft[ 0 ].szText, zsizeof( g_sWhereLeft[0].szText ), "." );
         strcat_s( g_sWhereLeft[ 0 ].szText, zsizeof( g_sWhereLeft[0].szText ), g_szEntityName );

         // Store the length of the EQ in the offset since it is not used otherwise.
         g_sWhereLeft[ 0 ].lElementClass = qENTITYQUALIFIER;

         // The next line was set in SETCURSORLASTCONTROL, don't overwrite.
         g_sWhereLeft[ 0 ].lOffset = zstrlen( g_sWhereLeft[ 0 ].szText );
         g_lWhereIndex = 1;
         for ( k = 0; k < WHERE_ARRAY_SIZE; k++ )
         {
            g_sWhereLeft[ k ].lLevel = 0;
            g_sWhereRight[ k ].lLevel = 0;
         }

         break;
      }

      // We are using g_sWhereLeft.lLevel/g_sWhereRight.lLevel to store the number of opening/closing parens.  Thus we get the
      // effect that unnecessary parens, like (( V.E.A = 123 )) are optimized away.
      case aQSETWHERELEFTPAREN:
         g_sWhereLeft[ g_lWhereIndex ].lLevel++;
         break;

      case aQSETWHERERIGHTPAREN:
         g_sWhereRight[ g_lWhereIndex -1 ].lLevel++;
         break;

      case aQADDWHEREJOIN:
         g_lWhereJoin[ g_lWhereIndex - 1 ] = sQToken.lToken;
         break;

      case aQINCREMENTWHEREINDEX:
         g_lWhereJoin[ g_lWhereIndex ] = 0;
         g_lWhereIndex++;
         break;

      case aQADDWHERECONDOPER:
         //g_lWhereOp[ g_lWhereIndex ] = sQToken.lLastToken;
         g_lWhereOp[ g_lWhereIndex ] = sQToken.lToken;
         break;

      case aQADDWHERECONDEQUAL:
         g_lWhereOp[ g_lWhereIndex ] = qCONDEQUAL;
         break;

      case aQADDWHERELIKE:
         g_lWhereOp[ g_lWhereIndex ] = qLIKE;
         break;

      case aQADDWHEREEXISTS:
         g_lWhereOp[ g_lWhereIndex ] = qEXISTS;
         g_sWhereRight[ g_lWhereIndex ].lElementClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataType = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0;
         break;

      case aQADDWHEREIS:
         g_lWhereOp[ g_lWhereIndex ] = qIS;
         g_sWhereRight[ g_lWhereIndex ].lElementClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataType = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0;
         break;

      case aQADDWHEREISNOTNULL:
         g_lWhereOp[ g_lWhereIndex ] = qNOTNULL;
         g_sWhereRight[ g_lWhereIndex ].lElementClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataType = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0;
         break;

      case aQADDWHEREISNULL:
         g_lWhereOp[ g_lWhereIndex ] = qNULL;
         g_sWhereRight[ g_lWhereIndex ].lElementClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataType = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0;
         break;

      case aQADDWHERENOTEXIST:
         g_lWhereOp[ g_lWhereIndex ] = qNOTEXISTS;
         g_sWhereRight[ g_lWhereIndex ].lElementClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataType = 0;
         g_sWhereRight[ g_lWhereIndex ].lDataClass = 0;
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0;
         break;

      case aQADDWHEREVARIABLE:
         lRC = GetVariableID( &g_sWhereRight[ g_lWhereIndex ].lOffset, sQToken.szToken );
         if ( lRC < 0 )
         {
            SyntaxError( vSubtask, eQVARIABLEUNDEFINED, sQToken.szToken );
            break;
         }

         g_sWhereRight[ g_lWhereIndex ].lElementClass = qVARIABLE;
         g_sWhereRight[ g_lWhereIndex ].lDataType = GetVariableDataType( g_sWhereRight[ g_lWhereIndex ].lOffset );
         g_sWhereRight[ g_lWhereIndex ].lDataClass = GetClassBasedOnType( g_sWhereRight[ g_lWhereIndex ].lDataType );
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0; // dks added 2015.12.08
         break;

      case aQADDWHERECONSTANT:
         if ( lGlbUnaryOperator && UnaryOperatorConstant( vSubtask ) )
            break;

         g_sWhereRight[ g_lWhereIndex ].lElementClass = qCONSTANT;
         g_sWhereRight[ g_lWhereIndex ].lDataType = sQToken.lToken;
         g_sWhereRight[ g_lWhereIndex ].lDataClass = GetClassBasedOnType( g_sWhereRight[ g_lWhereIndex ].lDataType );
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0; // dks added 2015.12.08
         strcpy_s( g_sWhereRight[ g_lWhereIndex ].szText, zsizeof( g_sWhereRight[g_lWhereIndex].szText ), sQToken.szToken );
         break;

      case aQADDWHERELEFTAQ:
         // Get the WhereLeft view name for the Syntax check below.
         SplitQualifier( g_sWhereLeft[ 0 ].szText, // token to be split
                         szTempViewName,         // string to store view in
                         g_szEntityName,         // string to store Entity
                         g_szAttributeName );    // String to store attribute

         SplitQualifier( sQToken.szLastToken, // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         // Check that the ViewName of the AQ is the same as the ViewName of the Activate ViewName, which was stored in first entry of g_sWhereLeft.
         // This is only valid for Activate operations, so also check if it is an Activate and then turn off the indicator.
         if ( g_bActivate )
         {
            g_bActivate = FALSE;
            if ( zstrcmp( szTempViewName, g_szViewName ) != 0 )
            {
               SyntaxError( vSubtask, eQINVALIDLEFTWHEREAQ, g_szViewName );
               break;
            }
         }

         lRC = VerifyQualifier( vSubtask, qATTRIBUTEQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         g_sWhereLeft[ g_lWhereIndex ].lElementClass = qATTRIBUTEQUALIFIER;
         if ( lRC == qENTITYANDATTRIBUTEARECONSTANT )
         {
            // If a valid attribute, the type was stored in AttributeID as a side effect for performance
            g_sWhereLeft[ g_lWhereIndex ].lDataType = g_lAttributeID;
         }
         else
         {
            g_sWhereLeft[ g_lWhereIndex ].lDataType = qTUNKNOWN;
         }

         g_sWhereLeft[ g_lWhereIndex ].lDataClass = lRC; // from verify
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0; // dks added 2015.12.08
         g_sWhereLeft[ g_lWhereIndex ].lOffset = 0;
         strcpy_s( g_sWhereLeft[ g_lWhereIndex ].szText, zsizeof( g_sWhereLeft[ g_lWhereIndex ].szText ), sQToken.szLastToken );
         break;

      case aQADDWHERELEFTEQCOND:
         SplitQualifier( sQToken.szToken,     // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );

         g_sWhereLeft[ g_lWhereIndex ].lElementClass = qENTITYQUALIFIER;
         g_sWhereLeft[ g_lWhereIndex ].lDataClass = 0; // from verify ... not really! (dks)
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0; // dks added 2015.12.08
         g_sWhereLeft[ g_lWhereIndex ].lOffset = 0;
         strcpy_s( g_sWhereLeft[ g_lWhereIndex ].szText, zsizeof( g_sWhereLeft[g_lWhereIndex].szText ), sQToken.szToken );
         break;

      case aQADDWHERELEFTEQ:
         SplitQualifier( sQToken.szLastToken, // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID,
                          g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );

         g_sWhereLeft[ g_lWhereIndex ].lElementClass = qENTITYQUALIFIER;
         g_sWhereLeft[ g_lWhereIndex ].lDataClass = 0; // from verify ... not really! (dks)
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0; // dks added 2015.12.08
         g_sWhereLeft[ g_lWhereIndex ].lOffset = 0;
         strcpy_s( g_sWhereLeft[ g_lWhereIndex ].szText, zsizeof( g_sWhereLeft[ g_lWhereIndex ].szText ), sQToken.szLastToken );
         break;

      case aQADDWHERERIGHTAQ:
         SplitQualifier( sQToken.szToken,     // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         lRC = VerifyQualifier( vSubtask, qATTRIBUTEQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );
         g_sWhereRight[ g_lWhereIndex ].lElementClass = qATTRIBUTEQUALIFIER;
         if ( lRC == qENTITYANDATTRIBUTEARECONSTANT )
         {
            // If a valid attribute, the type was stored in AttributeID as a side effect for performance
            g_sWhereRight[ g_lWhereIndex ].lDataType = g_lAttributeID;
         }
         else
         {
            g_sWhereRight[ g_lWhereIndex ].lDataType = qTUNKNOWN;
         }

         g_sWhereRight[ g_lWhereIndex ].lDataClass = lRC; // from verify
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0; // dks added 2015.12.08
         g_sWhereRight[ g_lWhereIndex ].lOffset = 0;
         strcpy_s( g_sWhereRight[ g_lWhereIndex ].szText, zsizeof( g_sWhereRight[g_lWhereIndex].szText ), sQToken.szToken );
         break;

      case aQADDWHERERIGHTEQ:
         SplitQualifier( sQToken.szToken,     // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         lRC = VerifyQualifier( vSubtask, qENTITYQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );

         g_sWhereRight[ g_lWhereIndex ].lElementClass = qENTITYQUALIFIER;
         g_sWhereRight[ g_lWhereIndex ].lDataClass = lRC; // from verify
         g_sWhereRight[ g_lWhereIndex ].lFlags = 0; // dks added 2015.12.08
         g_sWhereRight[ g_lWhereIndex ].lOffset = 0;
         strcpy_s( g_sWhereRight[ g_lWhereIndex ].szText, zsizeof( g_sWhereRight[g_lWhereIndex].szText ), sQToken.szToken );

         g_lWhereJoin[ g_lWhereIndex ] = 0;
         g_lWhereIndex++;
         break;

      // an operator was found
      case aQADDOPERATORTOEXPR:
         // just send it on through
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 );
         break;

      // A comma was found. This is a comma to separate parameters in an operation call.  It adds the operator, then increments the global
      // parm index pointer to the next type to be sure that types are correct.
      case aQADDCOMMATOEXPR:
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 );

         // If we are in a parm list ...
         if ( g_lParmListIndex > 0 )
         {
            g_lParmListIndex++;        // increment the pointer

            // See if it is a pointer.  If it is "un"pointer to to get just the data type.
            if ( g_lParmList[ g_lParmListIndex ] < 0 )
               g_lLeftDataType = g_lParmList[ g_lParmListIndex ] * -1;

            // else just get the data type.
            else
            if ( g_lParmList[ g_lParmListIndex ] > 0 )
               g_lLeftDataType = g_lParmList[ g_lParmListIndex ];

            // If Zero, then we do not know what type as the operation that is being called has yet to be defined so we have to assume that
            // the type given is unknown.
            else
            if ( g_lParmList[ g_lParmListIndex ] == 0 )
               g_lLeftDataType = qTUNKNOWN;
         }

         break;

      // to add a variable to an expression
      case aQADDVARIABLEOFFSETTOEXPR:

         ERROR_ON_UNARY_MINUS( "indexed variable" );

         // Try to get the ID number of the variable which will be in the .LastToken
         lRC = GetVariableID( &lIDNumber, sQToken.szLastToken );

         // If there was no variable of this name then it must be an error define values cannot be indexed, therefore, this cannot be a define.
         if ( lIDNumber < 0 )
         {
            // Try to get a define id for it anyway to give a better error message.  If an attempt was made to index it, this is not allowed.
            lIDNumber = GetDefineZKey( vSubtask, &lVarDataType, sQToken.szLastToken );

            // If the define was found
            if ( lIDNumber >= 0 )
               SyntaxError( vSubtask, eQDEFINECANTBEINDEXED, sQToken.szLastToken );
            else
               // the define was not found
               SyntaxError( vSubtask, eQVARIABLEUNDEFINED, sQToken.szLastToken );

            break;
         }

         // Otherwise it was found as a variable.  Make sure that the data type is textual.
         lVarDataType = GetVariableDataType( lIDNumber );

         // get the class
         lDataClass = GetClassBasedOnType( lVarDataType );

         // If the class is not QTEXT we cannot index it.
         if ( lDataClass != qTEXT )
         {
            SyntaxError( vSubtask, eQONLYSTRINGSCANBEINDEXED, sQToken.szLastToken );
            break;
         }

         // Compare the data types for consistency.  If the parm type is void, we won't do the check.
         if ( g_lLeftDataType != qTVOID )
         {
            lRC = CompareDataTypesForConsistency( g_lLeftDataType, g_lLeftDataClass, lVarDataType, lDataClass );
            if ( lRC == qNOMATCHONTYPE )
            {
               SyntaxError( vSubtask, eQINCOMPATIBLETYPES, "" );
               break;
            }
         }

         if ( lRC == qSETTARGETTOSOURCE )
         {
            g_lLeftDataType = lVarDataType;
            g_lLeftDataClass = lDataClass;
         }

         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qVARIABLE, 0, lVarDataType, "", lIDNumber, 0 );
         break;

      // To add a variable to an expression.
      case aQADDDEFINETOEXPR:

         ERROR_ON_UNARY_MINUS( "DEFINE" );

         // get the define ZKey, if < 0 then it was not found
         lRC = qTYPEEXACTMATCH;
         lDefineZKey = GetDefineZKey( vSubtask, &lVarDataType, sQToken.szToken );

         // It was not a define either so we cannot deal with it.  Therefore this is an error.
         if ( lDefineZKey < 0 )
         {
            SyntaxError( vSubtask, eQVARIABLEUNDEFINED, sQToken.szToken );
            break;
         }

         // If this is in a paramter list the g_lParmListIndex will be set greater than zero.
         if ( g_lParmListIndex > 0 )
         {
            // If the entry at index is negative, then we have a pointer to some data type, but a define cannot be negative ... so give an error.
            if ( g_lParmList[ g_lParmListIndex ] < 0 )
            {
               SyntaxError( vSubtask, eQDEFINEPUTWHEREVARIABLEMUSTBE, sQToken.szToken );
               break;
            }
            // else, if we are building an unknown paramter list, put this entry in and assume it is correct.
            else
            if ( g_lParmList[ g_lParmListIndex ] == 0 )
            {
               g_lParmList[ g_lParmListIndex ] = lVarDataType;
            }
         }

         // get
         lDataClass = GetClassBasedOnType( lVarDataType );

         // Compare the data types for consistency.  If the parm type is void, we won't do the check.
         if ( g_lLeftDataType != qTVOID )
         {
            lRC = CompareDataTypesForConsistency( g_lLeftDataType, g_lLeftDataClass, lVarDataType, lDataClass );

            // If they do not match at all, generate an error.
            if ( lRC == qNOMATCHONTYPE )
            {
               SyntaxError( vSubtask, eQINCOMPATIBLETYPES, "" );
               break;
            }
         }

         // If the lefts are unknown, set them to this.
         if ( lRC == qSETTARGETTOSOURCE )
         {
            g_lLeftDataType = lVarDataType;
            g_lLeftDataClass = lDataClass;
         }

         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qDEFINE, lDataClass, lVarDataType, sQToken.szToken, lDefineZKey, 0 );
         break;

      case aQADDVARIABLETOEXPR:
         // lRC was not initialized in any sensible way ... dks 2009.09.10
         lRC = 0;
         lUnaryOperator = lGlbUnaryOperator;
         lGlbUnaryOperator = 0;

         // Start by getting the variable ID.
         GetVariableID( &lIDNumber, szGlbVariable ); // szLastToken

         // If an id was not found, try to find it as a define in a header file.
         if ( lIDNumber < 0 )
         {
            // Do not allow unary minus with define.
            if ( lUnaryOperator )
            {
               SyntaxError( vSubtask, eQINVALIDUNARYOPERATOR, "- not valid with DEFINE" );
               break;
            }

            // Get the define ZKey.  If < 0, then it was not found.
            lIDNumber = GetDefineZKey( vSubtask, &lVarDataType, szGlbVariable ); // szLastToken

            // It was not a define either, so we cannot deal with it.  Therefore this is an error.
            if ( lIDNumber < 0 )
            {
               SyntaxError( vSubtask, eQVARIABLEUNDEFINED, szGlbVariable ); // szLastToken
               break;
            }

            // If this is in a parameter list, the g_lParmListIndex will be greater than zero.
            if ( g_lParmListIndex > 0 )
            {
               // If the entry at index is negative, then we have a pointer to some data type, but a define cannot be negative so give an error.
               if ( g_lParmList[ g_lParmListIndex ] < 0 )
               {
                  SyntaxError( vSubtask, eQDEFINEPUTWHEREVARIABLEMUSTBE, szGlbVariable ); // szLastToken
                  break;
               }

               // Otherwise, if we are building an unknown paramter list, put this entry in and assume it is correct.
               else
               if ( g_lParmList[ g_lParmListIndex ] == 0 )
               {
                  g_lParmList[ g_lParmListIndex ] = lVarDataType;
               }
            }

            // Get the data class.
            lDataClass = GetClassBasedOnType( lVarDataType );

            // Compare the data types for consistency. If the parm type is void, we won't do the check.
            if ( g_lLeftDataType != qTVOID )
            {
               lRC = CompareDataTypesForConsistency( g_lLeftDataType, g_lLeftDataClass, lVarDataType, lDataClass );

               // If they do not match at all, generate an error.
               if ( lRC == qNOMATCHONTYPE )
               {
                  SyntaxError( vSubtask, eQINCOMPATIBLETYPES, szGlbVariable ); // szLastToken
                  break;
               }
            }

            // If the lefts are unknown, set them to this.
            if ( lRC == qSETTARGETTOSOURCE )
            {
               g_lLeftDataType = lVarDataType;
               g_lLeftDataClass = lDataClass;
            }

            AddExprNodeEntityToView( vSubtask, g_vGlobalView, qDEFINE, g_lOperationClass,
                                     lVarDataType, szGlbVariable, // szLastToken
                                     lIDNumber, 0 );
         }
         else  // it was a variable after all
         {
            zLONG lParmFlags = 0;

            // Get the data type.
            lVarDataType = GetVariableDataType( lIDNumber );

            // If this is in a parameter list, g_lParmListIndex will be greater than zero.
            if ( g_lParmListIndex > 0 )
            {
               // If the entry at index is negative, then we have a pointer to some data type.  Set the id to negative to encode this information.
               if ( g_lParmList[ g_lParmListIndex ] < 0 )
               {
                  // If it is a void pointer and we have a string or view do nothing.
                  if ( g_lParmList[ g_lParmListIndex ] == (qTVOID * -1) )
                  {
                     if ( lVarDataType == qTVIEW || lVarDataType == qTSTRING )
                     {
                        ; // lIDNumber *= -1;
                     }
                     else
                       lIDNumber *= -1;
                  }
                  else
                     lIDNumber *= -1;
               }
               else // Otherwise, if we are building an unknown paramter list, put this entry in and assume it is correct.
               if ( g_lParmList[ g_lParmListIndex ] == 0 )
               {
                  g_lParmList[ g_lParmListIndex ] = lVarDataType;
               }

               // If the Parameter List is expecting a BYTE (character), then we do not alter the type.  If however, the parameter wants a string,
               // we need to change the type to string here.  5/20/93
               if ( lVarDataType == qTCHARACTER &&
                    (g_lParmList[ g_lParmListIndex ] == qTSTRING ||
                     g_lParmList[ g_lParmListIndex ] == -qTSTRING) )              // do it for negative as well??? dks 2010.04.30
               {
                  lVarDataType = qTSTRING;
               }

               // If parm list is expecting a VIEW and we got an INTEGER, then we accept it by altering it to a VIEW.
               if ( lVarDataType == qTINTEGER &&
                    (g_lParmList[ g_lParmListIndex ] == qTVIEW ||
                     g_lParmList[ g_lParmListIndex ] == -qTVIEW) )              // do it for negative as well??? dks 2010.04.30
               {
                  lVarDataType = qTVIEW;
               }

               // Take flags from parm list extension (unsigned, pointer, ..., view, long, short, ...)
               lParmFlags = g_lParmListExt[ g_lParmListIndex ];
            }

            // Get the data class.
            lDataClass = GetClassBasedOnType( lVarDataType );

            // Compare the data types for consistency.  If the parm type is void, we won't do the check.
            if ( g_lLeftDataType != qTVOID )  // qTVOID:1101  qTINTEGER:1040  qTVIEW:1045  qTUNKNOWN:1100  qTSTRING:1042
            {
               lRC = CompareTargetTypeForConsistency( g_lTargetDataType, g_lLeftDataType, g_lLeftDataClass, lVarDataType, lDataClass );

               // If they do not match at all, generate an error.
               if ( lRC == qNOMATCHONTYPE )
               {
                  SyntaxError( vSubtask, eQINCOMPATIBLETYPES, szGlbVariable ); // szLastToken
               // break;
               }
            }

            // If the lefts are unknown, set them to this.
            if ( lRC == qSETTARGETTOSOURCE )
            {
               g_lLeftDataType = lVarDataType;
               g_lLeftDataClass = lDataClass;
            }

            // Add the entry.
            AddExprNodeEntityToView( vSubtask, g_vGlobalView, qVARIABLE, 0, lVarDataType,
                                     "", lIDNumber, lParmFlags );  // lParmFlags for parameter is from g_lParmListExt
            if ( lUnaryOperator == qMINUS )
            {
               // Error if data type not numeric.
               if ( lVarDataType == qTINTEGER || lVarDataType == qTDECIMAL )
                  AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", qUNARYMINUS, 0 );
               else
                  SyntaxError( vSubtask, eQINVALIDUNARYOPERATOR, "- data type must be INTEGER or DECIMAL" );
            }
         }

         break;

      // to add an attribute qualifier to an expression.
      case aQADDAQTOEXPR:

         ERROR_ON_UNARY_MINUS( "attribute qualifier" );

         // Split the text into its component parts
         SplitQualifier( sQToken.szToken,     // token to be split
                         g_szViewName,        // string to store view in
                         g_szEntityName,      // string to store Entity
                         g_szAttributeName ); // String to store attribute

         // Verify that the components exist in the LOD.
         lRC = VerifyQualifier( vSubtask, qATTRIBUTEQUALIFIER, g_szViewName, &g_lViewID, g_szEntityName, &g_lEntityID, g_szAttributeName, &g_lAttributeID );

         // If the return code says what the parts are.
         if ( lRC == qATTRIBUTEISCONSTANT || lRC == qENTITYANDATTRIBUTEARECONSTANT )
         {
            // If a valid attribute, the type was stored in AttributeID as a side effect for performance.
            lType = g_lAttributeID;
         }
         else
         if ( lRC > 0 )
         {
            lType = g_lLeftDataType;
         }

         lDataClass = GetClassBasedOnType( lType );  // lDataType

         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qATTRIBUTEQUALIFIER, lDataClass, lType, sQToken.szToken, 0, 0 );

//       // The following Compare and SytaxError code was commented out by DonC on 11/10/94, because consistency should be left up
//       // to the Domain of the Attribute Qualifier.
//       // compare the data types for consistency
//       lRC = CompareDataTypesForConsistency( g_lLeftDataType, g_lLeftDataClass, lType, lDataClass );
//
//       // If they do not match at all, generate an error.
//       if ( lRC == qNOMATCHONTYPE )
//          SyntaxError( vSubtask, eQINCOMPATIBLETYPES, "" );
//
//         // If the lefts are unknown setthem to this
//         if ( lRC == qSETTARGETTOSOURCE )
//         {
//            g_lLeftDataType = lType;
//            g_lLeftDataClass = lDataClass;
//         }
         break;

      // Add a constant to an expression.
      case aQADDCONSTANTTOEXPR:
         if ( lGlbUnaryOperator && UnaryOperatorConstant( vSubtask ) )
            break;

         // If we are adding a numeric constant to a parameter list, do a little fudge work.
         lRC = qTYPEEXACTMATCH;
         if ( g_lParmListIndex > 0 )
         {
            // If the parameter is to be returned, it is an error, since we are dealing here with a constant.  A parameter is
            // to be returned if its value is negative.
            // The only exception is for a string constant (-1042).  This shouldn't really be, but at present all our Zeidon operation
            // definitions use the returned flag.  Later only when the operations are corrected, this exception can be removed.
            //
            // HH, 10.11.98
            // I went trough all the Zeidon Operations and checked the string parameters, so that a string parameter would
            // only have "Return" flagged, if it *IS* a return parameter.  As a consequence, the following code is taken out,
            // according to Don's comment right above. (bug TB370)

            if ( g_lParmList[ g_lParmListIndex ] < 0 )
 //              && g_lParmList[ g_lParmListIndex ] != -1042 )
            {
              SyntaxError( vSubtask, eQINCOMPATIBLETYPES, sQToken.szToken );
              break;
            }

            // If it expects a short, then change INTEGER to SHORT first.
            if ( g_lParmList[ g_lParmListIndex ] == qTSHORT && sQToken.lToken == qTINTEGER )
            {
               sQToken.lToken = qTSHORT;
            }

            // If it expects a VIEW and we received an INTEGER, then change it to a VIEW.
            if ( g_lParmList[ g_lParmListIndex ] == qTVIEW && sQToken.lToken == qTINTEGER )
            {
               sQToken.lToken = qTVIEW;
            }
         }

         lDataClass = GetClassBasedOnType( sQToken.lToken );

         // Don't allow character types, meaning all single characters must be defined as strings with double quotes.
         if ( sQToken.lToken == qTCHARACTER )
         {
            SyntaxError( vSubtask, eQINVALIDSTRINGCONSTANT,  sQToken.szToken );
            break;
         }

         // Compare the data types for consistency.  If the parm type is void, we won't do the check.  Also if the constant is
         // null (""), we won't do the check.
         if ( g_lLeftDataType != qTVOID && sQToken.szToken[ 0 ] != '"' && sQToken.szToken[ 1 ] != '"' )
         {
            lRC = CompareTargetTypeForConsistency( g_lTargetDataType, g_lLeftDataType, g_lLeftDataClass, sQToken.lToken, lDataClass );

            // If they do not match at all, generate an error.
            if ( lRC == qNOMATCHONTYPE )
            {
               SyntaxError( vSubtask, eQINCOMPATIBLETYPES,  sQToken.szToken );
               break;
            }
         }

         // If the lefts are unknown, set them to this.
         if ( lRC == qSETTARGETTOSOURCE )
         {
            g_lLeftDataType = sQToken.lToken;
            g_lLeftDataClass = lDataClass;
         }

         // add to expression ... qTINTEGER 1040   qTVIEW 1045
         if ( g_szGenLang[ 0 ] == 'J' && sQToken.lToken == qTINTEGER && g_lLeftDataType == qTVIEW && zstrcmp( sQToken.szToken, "0" ) == 0 )
         {
            strcpy_s( sQToken.szToken, zsizeof( sQToken.szToken ), "null" ); // we cannot compare a view to 0
            AddExprNodeEntityToView( vSubtask, g_vGlobalView, qCONSTANT, 0, sQToken.lToken, sQToken.szToken, 0, g_lParmListExt[ g_lParmListIndex ] );
         }
         else
         {
            AddExprNodeEntityToView( vSubtask, g_vGlobalView, qCONSTANT, 0, sQToken.lToken, sQToken.szToken, 0, g_lParmListExt[ g_lParmListIndex ] );
         }

         break;

      // simple add a colon separator
      case aQADDCOLONTOEXPR:
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", sQToken.lToken, 0 ); // COLON
         break;

      // This is to add a Left paren to an Operation Call.  Add the name of the operation to an expression.
      // At this point we have the name of an operation that needs to be verified.  Operations need to be looked up in a particular order.
      // First we look for a LOCALOPERATION. That is, an operation that has been defined within the same source member that we are parsing.
      // If it is not a LOCALOPERATION, then in order we look for OBJECT GLOBAL ZEIDON. Get Operation Class does all of this.  Once we are here,
      // we need to check the first parameter to see what the look up order is.
      // 1: If there is no parameter, or it is not a variable
      //    then we look up locally first, then to the global list, then Zeidon.
      // 2: If there is a variable as the first parameter, and the parameter is
      //    a view to a known lod, then we look up locally first, then to the src
      //    for the lod of the view, then globally, then Zeidon.
      // 3: If there is a variable as the first parameter and the parameter is a
      //    view (to a window), then we look up locally first, then to the src
      //    for the dialog of the view, then globally, then Zeidon.
      case aQADDOPENOPERTOEXPR:
      {
         zCHAR szReturnVarName[ 33 ];
         zLONG lReturnType;

         // Default the search order to one since this is what will be used in any error situation.
         lSearchOrder = 1;

         // Determine the lookup order. The first parm in is szToken.  If it is not a variable, then use search order 1.
         if ( sQToken.lToken == qVARIABLE )
         {
            zLONG lID;

            // Get the variable id.  If the variable does not exist, then don't bother reporting it since the next phase of inserting
            // the variable will handle this.
            lRC = GetVariableID( &lID, sQToken.szToken );

            // If it is a valid variable, go on.  If not, use search order 1, then report the error.
            if ( lRC != -1 )
            {
               // See if it is a view.
               lRC = GetVariableDataType( lID );
               if ( lRC == qTVIEW )
               {
                  // OK, we have a view.  See if it is a known view.  If the value parameter contains a view ptr, then this is a known view.
                  GetIntegerFromAttribute( (zPLONG) &lpTempView, g_lpSGView, "Variable", "Value" );

                  // If this is a known LOD then we use search order 2.
                  if ( lpTempView != 0 )
                     lSearchOrder = 2;  // we have a known LOD
                  else
                     lSearchOrder = 3;  // view to something else ... use 3
               }
            }
         }

         // Now pass this info along to get the operation information.  The OperationClass returned may be:
         // qLOCALOPERATION:4001, qGLOBALOPERATION:4002, qOBJECTOPERATION:4003, qDIALOGOPERATION:4004,
         // qDOMAINOPERATION:4005, qZEIDONOPERATION:4006, qCONTROLOPERATION:4007, error:-1
      // if ( zstrstr( g_szOperationName, "SetCursorNextEntityHierarchical" ) != 0 )
      //    TraceLineS( "", "" );

         SetNameForView( g_lpPIView, "g_lpPIView", vSubtask, zLEVEL_TASK );
         SetNameForView( g_vGlobalView, "g_vGlobalView", vSubtask, zLEVEL_TASK );

         GetOperationInformation( vSubtask,
                                  &g_lOperationClass, // class to return
                                  &g_lOperationZKey,  // ZKey of oper
                                  &lType, szType, zsizeof( szType ), // type of oper
                                  &vSource,           // view to assoc. src
                                  g_szOperationName,  // name (sending in)
                                  lSearchOrder,       // (from above)
                                  (zLONG) lpTempView ); // LODview if needed

         // If the operation could not be located, then we have an error since all operations should be known at this point.
         if ( g_lOperationClass < 0 )
         {
            SyntaxError( vSubtask, eQUNKNOWNOPERATION, g_szOperationName );

            // Set the flag that indicates an unknown operation has been encountered so that the aQINSERTOPERATIONCALL function
            // will not try to create the operation.
            g_lOperationUnknownFlag = 1;

            // add it anyway to avoid errors
            // AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATIONCALL, 0, 0, g_szOperationName, 0, 0 );
            break;
         }

         g_lOperationUnknownFlag = 0;

         // If all is well, get the parameter list.  If lReturnType > 0, it is the parameter type of the
         // return parameter (e.g. qTSTRING == 1042).
         lReturnType = GetOperationParmListFromSource( g_lParmList, g_lParmListExt, szReturnVarName, zsizeof( szReturnVarName ), vSource );

      // if ( lReturnType > 0 && szReturnVarName[ 0 ] != 0 )  // don't do this anymore ... multiple return
      //    lType = lReturnType;                              // parms implemented!  dks 2010.07.14

         // DGC 10/23/95
         // Added check for Global Operation.  If the op is a global op, then create an ExternalOperation entity.
         // This is for creating make files later on.  As of yet the parser and generator do NOT use this info.

         // Do header file stuff based on type of operation.
         if ( g_lOperationClass == qOBJECTOPERATION )  // 4003
         {
            // Include the operation but do nothing about the header file since it was already
            // included when the LOD was declared.
            lRC = SetCursorFirstEntityByInteger( g_lpSGView, "ExternalOperation", "ZKey", g_lOperationZKey, "" );

            if ( lRC != zCURSOR_SET )
            {
               IncludeSubobjectFromSubobject( g_lpPIView, "ExternalOperation", vSource,  "Operation", zPOS_AFTER );
               SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "SourceZKey", vSource, "LOD", "ZKey" );

               // Set the MetaDLL_Name to the LOD.DLL_Name if that attribute is not null, or to LOD.Name if the DLL_Name attribute is null.
               if ( g_szGenLang[ 0 ] == 'J' ) // we can't do this in the C environment ... dks  2013.04.05
               {
                  lRC = CompareAttributeToString( vSource, "SourceFile", "Name", "" );
                  if ( lRC == 0 )
                  {
                     lRC = CompareAttributeToString( vSource, "LOD", "DLL_Name", "" );
                     if ( lRC == 0 )
                        SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "MetaDLL_Name", vSource, "LOD", "Name" );
                     else
                        SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "MetaDLL_Name", vSource, "LOD", "DLL_Name" );
                  }
                  else
                  {
                    SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "MetaDLL_Name", vSource, "SourceFile", "Name" );
                  }

                  SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "SourceName", g_lpPIView, "ExternalOperation", "MetaDLL_Name" );
               }
               else
               {
                  lRC = CompareAttributeToString( vSource, "LOD", "DLL_Name", "" );
                  if ( lRC == 0 )
                  {
                     lRC = CompareAttributeToString( vSource, "SourceFile", "Name", "" );
                     if ( lRC == 0 )
                        SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "MetaDLL_Name", vSource, "LOD", "Name" );
                     else
                        SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "MetaDLL_Name", vSource, "SourceFile", "Name" );
                  }
                  else
                  {
                     SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "MetaDLL_Name", vSource, "LOD", "DLL_Name" );
               }

                  SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "SourceName", vSource, "LOD", "Name" );
              }

               SetAttributeFromString( g_lpPIView, "ExternalOperation", "SourceType", "Object" );
            }
         }
         else
         if ( g_lOperationClass == qGLOBALOPERATION )  // 4002
         {
            // Include the operation but do nothing about the header file since it was already
            // included when the LOD was declared.
            lRC = SetCursorFirstEntityByInteger( g_lpSGView, "ExternalOperation", "ZKey", g_lOperationZKey, "" );
            if ( lRC != zCURSOR_SET )
            {
               IncludeSubobjectFromSubobject( g_lpPIView, "ExternalOperation", vSource, "Operation", zPOS_AFTER );
               SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "SourceZKey", vSource, "GlobalOperationGroup", "ZKey" );
               SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "MetaDLL_Name", vSource, "GlobalOperationGroup", "DomainAndGlobalOpGroupName" );
               SetAttributeFromAttribute( g_lpPIView, "ExternalOperation", "SourceName", vSource, "GlobalOperationGroup", "Name" );
               SetAttributeFromString( g_lpPIView, "ExternalOperation", "SourceType", "Operation" );
            }

         // if ( 0 )
         // {
         //    SetNameForView( vSource, "vSource", vSubtask, zLEVEL_TASK );
         //    MessageSend( vSubtask, "VM00403", g_szOperationName,
         //                 "case aQADDOPENOPERTOEXPR: - Please check View: vSource and g_lpPIView for Operation Data",
         //                 zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
         // }
         }
         else
         if ( g_lOperationClass != qLOCALOPERATION &&   // 4001
              g_lOperationClass != qZEIDONOPERATION &&  // 4006
              g_lOperationClass != qDIALOGOPERATION &&  // 4004
              g_lOperationClass != qDOMAINOPERATION )   // 4005
         {
            TraceLineI( "Operation Class UNKNOWN: ", g_lOperationClass );
         }

         // Drop the source view.
         if ( g_lOperationClass == qZEIDONOPERATION || g_lOperationClass == qLOCALOPERATION )
         {
            DropView( vSource );
         }
         else
         if ( vSource )
            DropMetaOI( vSubtask, vSource );

         // After all of this, create the operation call in an expression.
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATIONCALL, g_lOperationClass, lType, sQToken.szLastToken, g_lOperationZKey, 0 );
         lDataClass = GetClassBasedOnType( lType );  // qTSHORT:1041 ==> qNUMERIC:2009 ... qTSTRING:1042 ==> qTEXT:2010

         // Check that the data types match.  If the parm type is void, we won't do the check.
         if ( g_lLeftDataType != qTVOID && lType != qTVOID )  // qTVOID:1101 ... dks 2010.07.01  added lType check
         {
            lRC = CompareDataTypesForConsistency( g_lLeftDataType, g_lLeftDataClass, lType, lDataClass );

            // Allow return type string to be cast to an integer variable so that a pointer would be assigned to an integer.
            if ( lRC == qNOMATCHONTYPE &&
                 !(lType == qTSTRING && g_lLeftDataType == qTINTEGER) )  // qTSTRING:1042  qTINTEGER:1040  qTEXT:2010  qTSHORT:1041
            {
               SyntaxError( vSubtask, eQINCOMPATIBLETYPES, "" );
               break;
            }
         }

         if ( lRC == qSETTARGETTOSOURCE )
         {
            g_lLeftDataType = lType;
            g_lLeftDataClass = lDataClass;
         }

         // Finally do the OPEN oper addition.
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", qOPENOPER, 0 );
         g_lParmListIndex = 1;

         // See if the parm is a pointer ... if it is "un"pointer to get just the data type.
         if ( g_lParmList[ g_lParmListIndex ] < 0 )
            g_lLeftDataType = g_lParmList[ g_lParmListIndex ] * -1;
         else
         {
            // else just get the data type
            if ( g_lParmList[ g_lParmListIndex ] > 0 )
               g_lLeftDataType = g_lParmList[ g_lParmListIndex ];
            else
            {
               // If Zero, then we do not know what type as the operation that is being called has
               // yet to be defined, so we have to assume that the type given is unknown.
            // if ( g_lParmList[ g_lParmListIndex ] == 0 )              // this must be true at this point!
                  g_lLeftDataType = qTUNKNOWN;
            }
         }

         break;
      }

      // This is to add the right paren to an Operation Call.
      case aQADDCLOSEOPERTOEXPR:
         // Skip processing the expresssion if the operation being processed is unknown.
         if ( g_lOperationUnknownFlag == 0 )
         {
            AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", qCLOSEOPER, 0 );
            if ( g_lParmList[ 0 ] > 1 && g_lParmListIndex != g_lParmList[ 0 ] - 1 )
            {
               if ( g_lParmListIndex < g_lParmList[ 0 ] - 1 )
                  SyntaxError( vSubtask, eQTOOFEWPARAMETERS, sQToken.szToken );
               else
                  SyntaxError( vSubtask, eQTOOMANYPARAMETERS, sQToken.szToken );
            }
         }

         // Zero out a few globals.
         g_lOperationZKey = 0;
         g_lOperationClass = 0;
         g_lParmListIndex = 0;

         g_lLeftDataType = qTINTEGER;  // set the data type back
         g_lLeftDataClass = qNUMERIC;  // hard code and save a call to get class

         break;

      case aQSETNEXT:
         SetCursorNextEntity( g_vStatementView, "Statement", "" );

         if ( g_lAddNextStatementBefore > 0 )
            g_lAddNextStatementBefore--;

         if ( g_lNeedExtraEnd > 0 )
         {
            g_lNeedExtraEnd--;
            AddStatementEntityToPI( vSubtask, qEND, qqlineno, g_vGlobalView, zPOS_AFTER );
         }

         break;

      case aQADDLONEDEFAULT:
         AddStatementEntityToPI( vSubtask, qOTHERWISE, qqlineno, g_vGlobalView, zPOS_AFTER );
         SetCursorNextEntity( g_lpPIView, "Statement", "" );

         break;

      case aQEXTRAENDNEEDED:
         if ( lBreakFlag == 1 )
            ResetViewFromSubobject( g_vStatementView );
         else
            AddStatementEntityToPI( vSubtask, qBREAK, qqlineno, g_vGlobalView, zPOS_AFTER ); // dks ... BREAK

         break;

      case aQADDRESTRICTACTIVATEWHERE:
         BuildWhereStatements( vSubtask, 0 ); // use restrict
         break;

      case aQADDACTIVATEWHERE:
         BuildWhereStatements( vSubtask, 1 ); // use root
         break;

      case aQADDACTIVATESTMT:
         InsertActivateIntoCurrentOperation( vSubtask, g_szLoadControl );
         ResetExprView( );

         break;

      case aQADDACTIVATESTMTNOWHERE:
         g_bActivate = FALSE;
         InsertActivateNoWhere( vSubtask, g_szLoadControl );

         break;

      case aQADDACTIVATESTMTEMPTY:
         g_bActivate = FALSE;
         InsertActivateEmpty( vSubtask, g_szLoadControl );

         break;

      case aQVERIFYACTIVATEOBJECT:
         lRC = GetVariableID( &lIDNumber, sQToken.szLastToken );  // just do this to position
         if ( lRC == -1 )
         {
            SyntaxError( vSubtask, eQVARIABLEUNDEFINED, sQToken.szLastToken );
         }

         strcpy_s( g_szViewName, zsizeof( g_szViewName ), sQToken.szLastToken );

         // Save g_lAddNextStatementBefore, because it will be altered during Activate processing.  It is restored in InsertActivateIntoCurrentOperation.
         g_lAddNextStatementBeforeSave = g_lAddNextStatementBefore;
         lRC = SetupActivate( vSubtask, lIDNumber );
         g_bActivate = TRUE;
         break;

      case aQSAVEACTIVATESINGLE:
         strcpy_s( g_szLoadControl, zsizeof( g_szLoadControl ), "zSINGLE" );
         break;

      case aQSAVEACTIVATEMULTIPLE:
         strcpy_s( g_szLoadControl, zsizeof( g_szLoadControl ), "zMULTIPLE" );
         break;

      case aQSAVEACTIVATEROOTONLY:
         strcpy_s( g_szLoadControl, zsizeof( g_szLoadControl ), "zACTIVATE_ROOTONLY" );
         break;

      case aQSAVEACTIVATEROOTONLYMULTIPLE:
         strcpy_s( g_szLoadControl, zsizeof( g_szLoadControl ), "zACTIVATE_ROOTONLY_MULTIPLE" );
         break;

      case aQSAVEACTIVATECONTINUE:
         strcpy_s( g_szLoadControl, zsizeof( g_szLoadControl ), "zACTIVATE_MULTIPLE_CONTINUE" );
         break;

      case aQSAVEACTIVATEROOTONLYCONTINUE:
         strcpy_s( g_szLoadControl, zsizeof( g_szLoadControl ), "zACTIVATE_ROOTONLY_CONTINUE" );
         break;

      case aQSAVEACTIVATESINGLEFORUPDATE:
         strcpy_s( g_szLoadControl, zsizeof( g_szLoadControl ), "zSINGLE_FOR_UPDATE" );
         break;

      case aQSETRESTRICTION:
      {
         zLONG k;

         strcpy_s( g_sWhereLeft[ 0 ].szText, zsizeof( g_sWhereLeft[0].szText ), sQToken.szToken );

         // Store the length of the EQ in the offset as it is not used otherwise.
         g_sWhereLeft[ 0 ].lElementClass = qENTITYQUALIFIER;
         g_sWhereLeft[ 0 ].lOffset = zstrlen( g_sWhereLeft[ 0 ].szText );
         g_lWhereIndex = 1;
         for ( k = 0; k < WHERE_ARRAY_SIZE; k++ )
         {
            g_sWhereLeft[ k ].lLevel = 0;
            g_sWhereRight[ k ].lLevel = 0;
         }
         break;
      }

      case aQADDCOMMIT:
         lRC = GetVariableID( &lTempID, sQToken.szToken );
         if ( lRC == -1 )
         {
            SyntaxError( vSubtask, eQVARIABLEUNDEFINED, sQToken.szToken );
            break;
         }

         BuildCommitView( vSubtask, (zSHORT) lTempID );
         break;

      case aQADDCHECKEXIST:
         g_lWhereIndex--;
         g_lScopeViewID = GenerateTempVariable( vSubtask, qTINTEGER, 2 );

         AddEntityOperWithNoScope( vSubtask, "CheckExistenceOfEntity", g_lViewID, g_szEntityName, g_lEntityID, 0, "", g_lScopeViewID );

         // Get the data type.
         lVarDataType = GetVariableDataType( g_lScopeViewID );

         // Get the data class.
         lDataClass = GetClassBasedOnType( lVarDataType );

         // Add the entry.
         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qVARIABLE, lDataClass, lVarDataType, "", g_lScopeViewID, 0 );
         if ( g_lWhereOp[ g_lWhereIndex ] == qEXISTS )
            AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", qCONDEQUAL, 0 );
         else
            AddExprNodeEntityToView( vSubtask, g_vGlobalView, qOPERATOR, 0, qTINTEGER, "", qNOTEQUAL, 0 );

         AddExprNodeEntityToView( vSubtask, g_vGlobalView, qCONSTANT, qNUMERIC, qTINTEGER, "0", 0, 0 );
         //g_lWhereIndex = 1;
         break;

      case aQADDUNARYOPERATOR:
         // Unary MINUS encountered.
         lGlbUnaryOperator = qMINUS;
         break;

      case aQSETVARIABLETEXT:
         // Remember the name of an operation or variable or other symbol.
         strncpy_s( szGlbVariable, zsizeof( szGlbVariable ), sQToken.szToken, zsizeof( szGlbVariable ) - 1 );
         break;

      default:
         break;
   }

   return( 0 );
} // end of ActionQ

static zLONG
ForceExprIntoParens( zVIEW vExpression )
{
   zLONG lMaxLevel = 9; // priority of RPAREN
   zLONG lRC;

   // Try and find an expression entry with a Level less than 9. If found, then we need to
   // enclose the expression in parens.  Start at the first expression node and check for
   // the NEXT node whose priority is less that that of a first level RPAREN.  If we just
   // did set first, we could find an LPAREN as the first node and erroneously put in more
   // parens when this would really signal that the expression is already in parens.
   lRC = SetCursorFirstEntity( vExpression, "ExprNode", "" );

   // If no nodes exist, get out
   if ( lRC < zCURSOR_SET )
      return( -1 );

   // try a SetEntity cursor where the level is less than RPAREN
   lRC = SetEntityCursor( vExpression,  "ExprNode", "Level", zPOS_NEXT | zQUAL_INTEGER | zQUAL_LESS_THAN, &lMaxLevel, "", "", 0, "", 0 );

   // If we did not find one, this means that the expression is enclosed in parens and we can just get out now as it is in acceptable form
   if ( lRC < zCURSOR_SET )
      return( 0 );

   // If we found one, this means that the expression is NOT enclosed in parens and it needs to be.  Go back to the beginning!
   SetCursorFirstEntity( vExpression, "ExprNode", "" );

   // Insert and LPAREN "BEFORE" the first operand.
   InsertExprNodeValuesToEntity( vExpression, qOPERATOR, 0, qTINTEGER, qLPAREN, 0, "", 0, zPOS_BEFORE );

   // Now, loop throught the rest of the expression and increment the priorities by 10 so that they are set as they would be if the expr
   // was coded with ( ) in the first place.

   // Increment nodes by 10 ...
   lRC = SetCursorNextEntity( vExpression, "ExprNode", "" );

   // ... til we get to the end.
   while ( lRC == zCURSOR_SET )
   {
      AddToAttributeFromInteger( vExpression, "ExprNode", "Level", 10 );
      lRC = SetCursorNextEntity( vExpression, "ExprNode", "" );  // dks added lRC = ???  2009.09.09
   }

   // Now insert the RPAREN as the very last operator.
   InsertExprNodeValuesToEntity( vExpression, qOPERATOR, 0, qTINTEGER, qRPAREN, 9, "", 0, zPOS_AFTER );

   return( 0 );  // we are all done now
}

// >>>ResetExprView

static void
ResetExprView( void )
{
   DropObjectInstance( g_lpExprView );

   ActivateEmptyObjectInstance( &g_lpExprView, "TZVSEXPO", lpGlobalSubtask, zSINGLE );

   CreateViewFromViewForTask( &g_vGlobalView, g_lpExprView, 0 );
   CreateEntity( g_vGlobalView, "Root", zPOS_AFTER );
   CreateEntity( g_vGlobalView, "Expression", zPOS_AFTER );
}

// >>>ParameterCheck

static zSHORT
ParameterCheck( zVIEW g_lpExprView, zPLONG plErrorPara )
{
   zVIEW  lpExView;
   zLONG  lOffset = 0;
   zLONG  lElementClass = 0;
   zLONG  lDataClass = 0;
   zLONG  lDataType = 0;
   zLONG  lParmListType = 0;
   zLONG  lParm = 0;
   zSHORT nRC;

   CreateViewFromViewForTask( &lpExView, g_lpExprView, 0 );

   // Find the OPEN paren.
   nRC = SetCursorFirstEntityByInteger( lpExView, "ExprNode", "ElementClass", qOPERATOR, 0 );

   // Sometimes we get an empty view with no expressions.  In that case, return 0.  Don't question why.
   if ( nRC < zCURSOR_SET )
      return( 0 );

   while ( nRC >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lOffset, lpExView, "ExprNode", "Offset" );
      if ( lOffset == qOPENOPER )
         break;

      nRC = SetCursorNextEntityByInteger( lpExView, "ExprNode", "ElementClass", qOPERATOR, 0 );
   }

   if ( nRC < zCURSOR_SET )
      return( -1 );

   while ( nRC >= zCURSOR_SET )
   {
      lParm++; // parmList starts with index 1
      nRC = SetCursorNextEntity( lpExView, "ExprNode", 0 );
      if ( nRC < zCURSOR_SET )
         return( -1 );

      GetIntegerFromAttribute( &lElementClass, lpExView, "ExprNode", "ElementClass" );
      GetIntegerFromAttribute( &lDataClass, lpExView, "ExprNode", "DataClass" );
      GetIntegerFromAttribute( &lDataType, lpExView, "ExprNode", "DataType" );
      if ( lElementClass == qOPERATOR )
      {
         // Check for function with no parms.
         if ( lParm <= 1 && g_lParmList[ 0 ] <= 1 )
         {
            GetIntegerFromAttribute( &lOffset, lpExView, "ExprNode", "Offset" );
            if ( lOffset == qCLOSEOPER )
               return( 0 ); // ok, no parameter declared
         }

         return( -1 ); // every thing else is an error
      }

      // If we got a CONSTANT, the parameter must not be of type pointer.
      if ( (lElementClass != qVARIABLE) && ((g_lParmListExt[ lParm ] & POINTER_BIT) != 0) )
      {
         *plErrorPara = lParm;
         return( 1 );
      }

      lParmListType = g_lParmList[ lParm ];
      if ( lParmListType < 0 )
         lParmListType = -lParmListType;

      // A type of VIEW in the parameter definition or as the parameter matches only type VIEW or INTEGER.
      if ( lParmListType == qTVIEW )
      {
         switch ( lDataType )
         {
            case qTVIEW:
               // If the parameter is a CONSTANT, only 0 is valid.
               if ( lElementClass == qCONSTANT )
               {
                  zPCHAR pchInteger;

                  if ( GetAddrForAttribute( &pchInteger, lpExView, "ExprNode", "Text" ) == 0 )
                  {
                     if ( atol( pchInteger ) != 0 )
                     {
                        *plErrorPara = lParm;
                        return( 1 );
                     }
                  }
               }

               break;

            case qTINTEGER:
               if ( lElementClass != qCONSTANT )
                  break;
               // otherwise fall trough

            default:
               *plErrorPara = lParm;
               return( 1 );
         }
      }

      if ( (lDataType == qTVIEW) && (lParmListType != qTVIEW) && (lParmListType != qTINTEGER) )

      {
         *plErrorPara = lParm;
         return( 1 );
      }

      // If the target type is numeric and the source type is string, we fire an error message.
      if ( (lParmListType == qTINTEGER || lParmListType == qTSHORT || lParmListType == qTDECIMAL) && lDataType == qTSTRING )
      {
         *plErrorPara = lParm;
         return( 1 );
      }

      // If the target type is string and the source type is short or decimal, we fire an error message.  We allow source type integer
      // variable (NOT constant), because sometimes it is used as an address in VML (ugly but real).  Integer Constant with value 0 is ok.
      // Any Attribute mapped to a string is ok (GetStringFromAttribute).
      if ( lParmListType == qTSTRING && lElementClass != qATTRIBUTEQUALIFIER )
      {
         switch ( lDataType )
         {
            case qTSHORT:
            case qTDECIMAL:
               *plErrorPara = lParm;
               return( 1 );

            case qTINTEGER:
               if ( lElementClass == qCONSTANT )
               {
                  // If the parameter is a CONSTANT, only 0 is valid.
                  zPCHAR pchInteger;

                  if ( GetAddrForAttribute( &pchInteger, lpExView, "ExprNode", "Text" ) == 0 )
                  {
                     if ( atol( pchInteger ) != 0 )
                     {
                        *plErrorPara = lParm;
                        return( 1 );
                     }
                  }
               }

            // An integer variable is allowed, because sometimes it is used to hold a pointer.

         }  // end of switch
      }

      // Advance to the end of the parameter, marked by a comma or a closing paren.
      nRC = SetCursorNextEntity( lpExView, "ExprNode", 0 );
      lElementClass = 0;
      while ( nRC >= zCURSOR_SET )
      {
         zLONG lDataClass2;
         GetIntegerFromAttribute( &lElementClass, lpExView, "ExprNode", "ElementClass" );
         if ( lElementClass == qOPERATOR )
         {
            GetIntegerFromAttribute( &lOffset, lpExView, "ExprNode", "Offset" );
            if ( lOffset == qCLOSEOPER || lOffset == qCOMMA )
               break;

            // We found an Operator, not Comma or CloseParen, so the parameter is an expression.  Then the parameter definiton must not be of pointer type.
            if ( (g_lParmListExt[ lParm ] & POINTER_BIT) != 0 )
            {
               *plErrorPara = lParm;
               return( 1 );
            }
         }
         else
         {
            // When we get here, we have found anything different from qOPERATOR, so we got an expression.  Check for parameter definition NOT being of type pointer.
            if ( (g_lParmListExt[ lParm ] & POINTER_BIT) != 0 )
            {
               *plErrorPara = lParm;
               return( 1 );
            }

            // Check for matching dataclass.  Parameters allow only simple numeric expressions.
            GetIntegerFromAttribute( &lDataClass2, lpExView, "ExprNode", "DataClass" );
            if ( lDataClass != qNUMERIC || lDataClass2 != qNUMERIC )
            {
               *plErrorPara = lParm;
               return( 1 );
            }
         }

         nRC = SetCursorNextEntity( lpExView, "ExprNode", 0 );
      }

      if ( nRC < zCURSOR_SET )
         return( -1 );

      if ( lOffset == qCLOSEOPER )
         break;
   }

   return( 0 );
}

// >>>CheckParaWithSource
// Check, whether the parameter matches with source meta.
static zSHORT
CheckParaWithSource( void )
{
   zCHAR cZeidonType[ 2 ];
   zCHAR cMetaType[ 2 ];

   if ( CheckExistenceOfEntity( g_vSourceMeta, "Parameter" ) < zCURSOR_SET )
      return( 1 ); // error

   // Make sure that parameter type matches.
   ConvertVMLTypeToZeidonType( cZeidonType, g_lLastTypeDeclared );
   cMetaType[ 0 ] = 0;
   GetStringFromAttribute( cMetaType, zsizeof( cMetaType ), g_vSourceMeta, "Parameter", "DataType" );
// DisplayObjectInstance( g_vSourceMeta, "", "" );
// MessageSend( g_vSourceMeta, "???", "Title9", "StatementView", 0, 0 );
   if ( cMetaType[ 0 ] == cZeidonType[ 0 ] )
      return( 0 );

   // Check for old data types 'E' and 'A'.
   if ( cZeidonType[ 0 ] == 'S' && (cMetaType[ 0 ] == 'E' || cMetaType[ 0 ] == 'A') )
      return( 0 ); // ok

   return( 2 ); // error
}

// >>>fnAddDefaultReturn
// Add default RETURN value according to function type.
static zVOID
fnAddDefaultReturn( zVIEW vExpression )
{
   zCHAR szReturnType[ 2 ];

   // Get the Return Type of the current operation for which the RETURN is currently built.
   GetStringFromAttribute( szReturnType, zsizeof( szReturnType ), g_lpPIView, "Operation", "ReturnDataType" );
   if ( szReturnType[ 0 ] == 0 || szReturnType[ 0 ] == 'O' )
      return;  // void operation, nothing has to be done

   // Insert an LPAREN
   InsertExprNodeValuesToEntity( vExpression, qOPERATOR, 0, qTINTEGER, qLPAREN, 0, "", 0, zPOS_AFTER );

   switch ( szReturnType[ 0 ] )
   {
      case 'L':
         // Return LONG value 0.
         InsertExprNodeValuesToEntity( vExpression, qCONSTANT, qNUMERIC, qTINTEGER, 0, 10, "0", 0, zPOS_AFTER );
         break;

      case 'M':
         // Return decimal value 0.0.
         InsertExprNodeValuesToEntity( vExpression, qCONSTANT, qNUMERIC, qTDECIMAL, 0, 10, "0.0", 0, zPOS_AFTER );
         break;

      case 'N':
      default:
         // Return SHORT value 0.
         InsertExprNodeValuesToEntity( vExpression, qCONSTANT, qNUMERIC, qTSHORT, 0, 10, "0", 0, zPOS_AFTER );
   }

   // now insert the RPAREN
   InsertExprNodeValuesToEntity( vExpression, qOPERATOR, 0, qTINTEGER, qRPAREN, 9, "", 0, zPOS_AFTER );
}

// >>>OperationNameValid
// Check for a valid Operation name ... return 1 if OK.
static zSHORT
OperationNameValid( zPCHAR szToken )
{
   int    k;

   if ( zstrcmp( g_szSourceMetaObjectName, "TZZOLODO" ) == 0 )
   {
      //zCHAR szLodName[ 9 ] = { 0 };
      // KJS 01/30/17
      zCHAR szLodName[ 33 ] = { 0 };

      // The source meta is a LOD.  For a LOD Operation, the length is restricted to 22 chars to
      // allow for a LOD name length of 8 characters. (o_LODNAME_).
      GetStringFromAttribute( szLodName, zsizeof( szLodName ), g_lpPIView, "VML_XSource", "MetaName" );
      //if ( zstrlen( szToken ) + zstrlen( szLodName ) > 30 )
      // KJS 01/30/17
      if ( zstrlen( szToken ) + zstrlen( szLodName ) > 54 )
         return( 0 );
   }
   else
   if ( zstrlen( szToken ) > 32 )
      return( 0 );

   // Names must be valid "C" names - letters, digits, and '_' ... first zCHAR must not be digit.
   // Unfortunately this is not checked by the parser.  Check it here, to prevent a domain error.
   for ( k = 0; szToken[ k ]; k++ )
   {
      if ( szToken[ k ] != '_' && !isalnum( szToken[ k ] ) )
         return( 0 );
   }

   if ( isdigit( szToken[ 0 ] ) )
      return( 0 );

   return( 1 );
}

// Handle unary operator preceding a constant ... return 0 if OK.
static zSHORT
UnaryOperatorConstant( zVIEW vSubtask )
{
   zCHAR szSave[ 1024 ];

   // If we got an unary operator preceding the constant, then the constant must be of type INTEGER or DECIMAL.
   if ( sQToken.lToken != qTINTEGER && sQToken.lToken != qTDECIMAL )
   {
      SyntaxError( vSubtask, eQINVALIDCONSTANTDEF, sQToken.szToken );
      return( 1 );
   }

   lGlbUnaryOperator = 0;

   // Just add the MINUS to the token.  Admittedly not a beautiful solution, but otherwise we would have to rewrite too much.
   // To handle the unary operator as qUNARYMINUS as with a variable would not be sufficient, because unary minus as a function
   // parameter would not work any more.  Note, that the old (erroneous) grammer handled unary operators in the lex part.
   strcpy_s( szSave, zsizeof( szSave ), sQToken.szToken );
   strcpy_s( sQToken.szToken, zsizeof( sQToken.szToken ), "-" );
   strncat_s( sQToken.szToken, zsizeof( sQToken.szToken ), szSave, zsizeof( sQToken.szToken ) - 1 );
   return( 0 );
}

static void
SetCursorNoWhere( zVIEW vSubtask )
{
   // Add result to be sure it is in the variable list.
   AddResult( vSubtask );

   if ( g_lSetFNPL == qFIRST )
      GenerateSetCursorWithScope( vSubtask, zPOS_FIRST );
   else
   if ( g_lSetFNPL == qLAST )
      GenerateSetCursorWithScope( vSubtask, zPOS_LAST );
   /* KJS 09/14/12
   else
   if ( g_szGenLang[ 0 ] == 'J' )
   {
      if ( g_lSetFNPL == qNEXT )
         GenerateSetCursorWithScope( vSubtask, -zPOS_NEXT );  // in the case of a straight "SET CURSOR NEXT" or "SET CURSOR PREV" with no parms,
      else                                                    // we need to do a setNext rather than a setNextContinue because we may have done
      if ( g_lSetFNPL == qPREVIOUS )                          // a qualified SET CURSOR FIRST/LAST and then want to continue on through the list
         GenerateSetCursorWithScope( vSubtask, -zPOS_PREV );  // of entities without qualification ... dks 2012.01.30
   }
   */
   else
   {
      if ( g_lSetFNPL == qNEXT )
         GenerateSetCursorWithScope( vSubtask, zPOS_NEXT );
      else
      if ( g_lSetFNPL == qPREVIOUS )
         GenerateSetCursorWithScope( vSubtask, zPOS_PREV );
   }

   g_szScopeViewName[ 0 ] = 0;
   g_szScopeEntityName[ 0 ] = 0;
   g_szScopeAttributeName[ 0 ] = 0;
   g_lScopeEntityID = 0;
   g_lSetFNPL = 0;
}

static void
ForNoWhere( zVIEW vSubtask )
{
   zLONG  lResultID;

    // If the EACH was used, we need to add a reset here.
   if ( g_lSetFNPL == qEACH )
   {
      // Add the call to Reset using result.
      GenerateSetCursorWithScope( vSubtask, zPOS_FIRST );
   }
   else // is qNOEACH || qCONSTANT || qVARIABLE
   {
      // Add the call to Reset using result.
      lResultID = AddResult( vSubtask );

      AddEntityOperWithNoScope( vSubtask, "CheckExistenceOfEntity", g_lViewID, g_szEntityName, g_lEntityID, 0, "", lResultID );
   }

   // If the loop was for each or noeach, we need to add an expression of 'while result == 1' and
   // put a set cursor next at the end.  If it was a for a variable or for a constant, the loop
   // needs to be 'while result == 1 and tempvar > 0.  At the end put a set cursor next and
   // a temp = temp - 1.
   if ( g_lSetFNPL == qEACH || g_lSetFNPL == qNOEACH )
   {
      AddResultCondEqual( vSubtask, qWHILE,        // type of statement
                          "zCURSOR_UNCHANGED" );   // what to compare result to
   }
   else
   {
      zVIEW vTargetView;
      CreateViewFromViewForTask( &vTargetView, g_lpExprView, 0 );
      CreateEntity( vTargetView, "Expression", zPOS_AFTER );
      AddExprNodeEntityToView( vSubtask, vTargetView, qOPERATOR, 0, qTINTEGER, "", qLPAREN, 0 );

      AddResultAndLoopControlToView( vSubtask, vTargetView,
                                     "zCURSOR_SET",    // what to compare result to
                                     g_lLoopControlID, // id of loop var
                                     qGREATERTHAN,     // comparison oper
                                     "0" );            // comparator value

      AddExprNodeEntityToView( vSubtask, vTargetView, qOPERATOR, 0, qTINTEGER, "", qRPAREN, 0 );

      // Dump the expression from the stack.
      AddOperatorToView( vSubtask, vTargetView, -1 );

      AddStatementEntityToPI( vSubtask, qWHILE, sQToken.lLastLineNo,
                              /// ???  qqlineno,
                              vTargetView, zPOS_AFTER );

      DeleteEntity( vTargetView, "Expression", zREPOS_NONE );
      DropView( vTargetView );
   }

   GenerateSetCursorWithScope( vSubtask, zPOS_NEXT );

   if ( g_lSetFNPL == qCONSTANT || g_lSetFNPL == qVARIABLE )
   {
      CreateIntegerExpression( vSubtask, g_lLoopControlID, qEQUAL, qVARIABLE, g_lLoopControlID, qMINUS, qCONSTANT, "1" );
      SetCursorPrevEntity( g_vStatementView, "Statement", 0 );
   }

   ResetExprView( );
   g_szScopeEntityName[ 0 ] = 0;
   g_lScopeEntityID = 0;
   g_lAddNextStatementBefore++;
}

zVOID OPERATION
GenerateSetCursorWithScope( zVIEW vSubtask, zLONG lScope )  // java???
{
   zPCHAR pchFunction = "";
   zBOOL  bSetNextJava = FALSE;

   // KJS 08/30/12 - I am currently commenting out the Java code because DG has made a change to the return code of the
   // "set" cursor methods and they now return an object instead of an int.  Ultimately, I think we want to come back with
   // this with a different return code but for now this is what we will do...
   // Should be something like the following:
   // CursorResult cr = vComboBox3.cursor( "CollegeYear" ).setFirst(  );
   // while ( cr.isSet() )

   /*
   if ( g_szGenLang[ 0 ] == 'J' )
   {
      // In the case of a straight "SET CURSOR NEXT" or "SET CURSOR PREV" with no parms, we need to do a setNext rather than a
      // setNextContinue because we may have done a qualified SET CURSOR FIRST/LAST and then want to continue on through the list
      // of entities without qualification ... dks 2012.01.30
      switch ( lScope )
      {
         case zPOS_FIRST:
            pchFunction = "setFirst";
            break;

         case zPOS_LAST:
            pchFunction = "setLast";
            break;

         case zPOS_NEXT:
         // if ( g_szScopeEntityName && g_szScopeEntityName[ 0 ] )
         // {
               bSetNextJava = TRUE;
               pchFunction = "setNextContinue";  // always do setNextContinue ... dks 2011.10.06
         // }
         // else
         //    pchFunction = "setNext";

            break;

         case zPOS_PREV:
         // if ( g_szScopeEntityName && g_szScopeEntityName[ 0 ] )
         // {
               bSetNextJava = TRUE;
               pchFunction = "setPrevContinue";  // always do setPrevContinue ... dks 2011.10.06
         // }
         // else
         //    pchFunction = "setPrev";

            break;

         case -zPOS_NEXT:
            lScope = zPOS_NEXT;
            pchFunction = "setNext";
            break;

         case -zPOS_PREV:
            lScope = zPOS_PREV;
            pchFunction = "setPrev";
            break;
      }
   }
   else
   {
   */
      switch ( lScope )
      {
         case zPOS_FIRST:
            pchFunction = "SetCursorFirstEntity";
            break;

         case zPOS_LAST:
            pchFunction = "SetCursorLastEntity";
            break;

         case zPOS_NEXT:
            pchFunction = "SetCursorNextEntity";
            break;

         case zPOS_PREV:
            pchFunction = "SetCursorPrevEntity";
            break;
      }
   /*
   }
   */

   if ( g_szScopeEntityName[ 0 ] == '\1' )
      AddSetEntityCursor( vSubtask, g_lViewID, g_szEntityName, g_lEntityID, lScope + zQUAL_SCOPE_OI );
   else
      AddEntityOperWithScope( vSubtask, pchFunction, g_lViewID, g_szEntityName, g_lEntityID, 0, "", 0,
                              bSetNextJava ? "" : g_szScopeEntityName,
                              bSetNextJava ? 0 : g_lScopeEntityID, 0, "", 0 );
}
