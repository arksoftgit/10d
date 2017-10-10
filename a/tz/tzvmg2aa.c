/////////////////////////////////////////////////////////////////////////////
//
// MODULE NAME:   tzvmg2aa.c - VML SubSystem Generator Main Module???
// DESCRIPTION:   This is the source file which contains the main functions
//                for the Generator.
//
// //////////////////////////////////////////////////////////////////////////
// * Copyright (c) 1995 - 2016 QuinSoft, Inc.         All rights reserved.   *
// * Confidential and Proprietary material subject to license - do not      *
// * reproduce or disclose.  This material is an unpublished work and       *
// * is considered a trade secret belonging to the copyright holder.        *
// //////////////////////////////////////////////////////////////////////////
//
// AUTHOR:        Jeffrey S. Beam
// DATE:          1992/07/20
// API:           MicroSoft foundation classes and Windows 3.1 SDK
// ENVIRONMENT:   Windows 3.1
// REVISION:      10B    1995/08/05
//
// HISTORY:
//
//    1995/08/05: Beginning of 10B branch
//
/////////////////////////////////////////////////////////////////////////////

/*
CHANGE LOG

2001.10.08  HH
   generate cast for integer constant/variable as decimal argument.
2001.09.20  HH
   solve the "\\" problem.
2001.02.20  HH
   add a cast operator if necessary (NOT short to long)
   with operation calls.
   Support unary minus operator.
2000.09.21  HH
   added FormatString to tzlodopr.h.
2000.09.18  HH
   support local C operations to be called from VML.
2000.09.06  HH
   generate cast for return "decimal constant".
2000.08.07  HH
   avoid warning.: for an operation parameter generate a cast to (zPLONG)
   if the source variable is NOT integer (zVIEW for instance).

OLD CHANGE LOG
97/22/04    DonC
   Modified AddExprEntryToString operation to handle TCHARACTER types
   corectly.  Needed in changing the generation of GetStringFromAttribute
   operations to GetVariableFromAttribute operations.

20.07.1997  DonC
   Corrected handling of szExprCode and szTextCode so that IF statements
   could handle a larger number of expressions within the IF.

27.10.1997  DonC
   Added SysFreeMemory call to GenerateNewExpression because memory
   allocated at beginning of routine was never freed.

12.06.1998-17.06.1998  HH
   Changed AddExprEntryToString (passing decimal as parameter)
   according to Doug's change "derive ZDecimal from zDECIMAL".
   Changed AddExprEntryToString do generate a ZDecimal cast
   for decimal constants passed as parameter  and
   for assignment of decimal via pointer.

1998.07.08  DGC
   Removed some of my debugging code.

1998.07.17  HH
   Changed AddExprEntryToString to handle unsigned parameters.

11.08.1998  HH
   Improved AddExprEntryToString, so that for the (ZDecimal) cast
   (17.6.98) additional parentheses around the numerical
   expression are generated.

19.08.1998-25.08.1998  HH
   Improved (re-wrote) FormatString,
   especially handling of (zLONG) quoted strings.

16.10.1998  HH
   Fixed bug TB363, cast opreation patrameter to zLONG if it is
   of type VIEW and the function prototype is LONG.

26.10.1998  HH
   Fix bug XC291, cast to (ZDecimal) for functions returning decimal.

03.02.1999  RG
   Add cast for unsigned short in generation
*/

#include <string.h>
#include "tzlodopr.h"
#include "tz__oprs.h"
#include "tzvsecaa.h"
#include "tzvmlopr.hg"
#include "ZeidonOp.h"

zVOID LOCALOPER
InsertLineBreak( zPCHAR pchOutputString,
                 zPCHAR pchInsertPosition,
                 zSHORT nMargin,
                 zPCHAR pchTemp,
                 zBOOL  bQuotes );

zSHORT LOCALOPER
AddExprEntryToString( zVIEW        vSubtask,
                      sQExprStruct *psExpr,
                      zPCHAR       pchOutputString,
                      zPCHAR       pchPFlag,
                      zLONG        lFlagLth,
                      zSHORT       nOutputIdx,
                      zPCHAR       pchExprText,
                      zLONG        lFlag );
zSHORT LOCALOPER
GetStringForOperator( zPCHAR pchOperString,
                      zSHORT nOperator );
zLONG  LOCALOPER
GetOperationNameFromZKey( zVIEW   vSubtask,
                          zPCHAR  pchReturnName,
                          zLONG   lNameLth,
                          zPCHAR  pchReturnHeaderName,
                          zLONG   lHeaderLth,
                          zPCHAR  pchReturnThrowsException,
                          zLONG   lThrowsLth,
                          zPCHAR  pchThrowsExceptionCatchCode,
                          zLONG   lCatchLth,
                          zPCHAR  pchOperationGroup,
                          zLONG   lGroupLth,
                          zLONG   lOperationClass,
                          zLONG   lZKey );
zSHORT LOCALOPER
GetDefineExternalValue( zPCHAR pchExternalValue,
                        zLONG  lMaxLth,
                        zLONG  lOperationClass,
                        zLONG  lDefineZKey );

#define zOPERATION_ARGUMENTS  0x00000001

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: GenerateNewExpression
//
// DESCRIPTION: This function generates the expression associated with a
//    statement entity using two attributes of the statement entity:
//    EXPRESSION and EXPRTEXT. The EXPRESSION entity is a Workstring of
//    some arbitrary length that has the sExprRec encoded into it. EXPRTEXT
//    has any associated text, such as string constants or variable names.
//
//    This operation is designed as follows. The expressions are stored in
//    reverse polish notation. This means that in order to generate the
//    expression, it has to be "parsed".  The method to be used is similar
//    to the stack method in the interpreter. In the interpreter, values
//    are pulled off of the list until there are two values and one operator,
//    at which point the operation can occur. The same basic concept will be
//    used here. A stack will hold the values (actually the pointers to the
//    values) until they are needed. Then, when the expression is ready,
//    it is output.
//
//    First, the expression and the exprtext need to be retrieved into
//    strings. Next, two integers to be used as indexes into the strings
//    need to be defined to One (One being the first record stored in the
//    string). There is also an output string which is the string that is
//    being built to be written out.
//
//    The algorithm is as follows:
//       1 - Get the EXPRESSION string from the statement entity.
//       2 - Get the EXPRTEXT from the statement entity.
//       3 - Set the indexes to the value stored in the first
//           node of the string.
//       4 - get the first sExprRec from the Expression.
//       5 - Build the output string from the end to the beginning.
//          5a-While sExprRecs exist in the string
//                If the Rec contains a VARIABLE or CONSTANT
//                   Push the Value onto the stack
//                If the Rec contains an OPERATOR,
//                   Check to see if it is the first operator
//                   If it is the first operator,
//                      POP the last value and put it at the
//                      end of the output string
//                   in any case:
//                   Put the Text equivalent of the operator in the string
//                    starting from the end and going backwards.
//                   POP a value,
//                   Put the value in the string starting from the
//                    end and going backwards.
//                 Get the next sExprRec
//              End of the while loop
//
//    Data structures used in this operation are as follows:
//       the push/pop value stack is a list of [50] integers which
//       are indexes into the EXPRESSION statement.
//
/////////////////////////////////////////////////////////////////////////////

// Define the macro PUSH to be as follows:
//    Put the index into the EXPRESSION statement onto the value stack and then
//    increment the stack pointer (bump it up by one)
#define PUSH(n) (nValueStack[ nStackIdx++ ] = n)

// Define the macro POP to be as follows:
//    Decrement the stackpointer (bump it down by one) and then
//    return the index into the EXPRESSION statement that was stored there.
//#define POP     (nValueStack[ --nStackIdx ])
#define POP       ((nStackIdx > 0) ? nValueStack[ --nStackIdx ]: -2)

#if 0
// from tzvmlopr.h
#define DBLMAXSTRING 2048
#define EXPRCODE_MAXSTRING 12000
#define EXPRTEXT_MAXSTRING 1200

// from tzlodopr.h
typedef struct sQExprStruct  // must be in sync with ExprNode Entity of TZVSEXPO.LOD
{                            // to check, use: qstruct tzvsexpo.xod -otzvsexpo.hst
   zLONG lElementClass;
   zLONG lDataClass;
   zLONG lDataType;
   zLONG lOffset;
   zLONG lLevel;
   zLONG lCount;
   zLONG lFlags; // *+*
// definitions for lFlags
#define  POINTER_BIT  0x00000001   // future use
#define  UNSIGNED_BIT 0x00000002
#define  SKIP_BIT     0x00010000
#define  QUALVIEW_BIT 0x00020000
#define  RETVIEW_BIT  0x00040000
#define  MUTABLE_BIT  0x00100000
#define  TESTVIEW_BIT 0x00200000
// for nParmType use the next 3 bits , mask = 0x0000001C
#define  NPARM_TYPE_CHAR    0x00000000
#define  NPARM_TYPE_LONG    0x00000004
#define  NPARM_TYPE_SHORT   0x00000008
#define  NPARM_TYPE_DECIMAL 0x0000000C
#define  NPARM_TYPE_VIEW    0x00000010
#define  NPARM_TYPE_DATE    0x00000014
#define  NPARM_TYPE_VOID    0x00000018
#define  NPARM_TYPE_MASK    0x0000001C

   zCHAR szText[ MAXSTRING ];
} sQExprStruct;

#endif

//#define DEBUG_PARSEGEN 1

typedef struct qDefines
{
   zLONG lType;
   zPCHAR pchName;

} qDefines;

qDefines g_qDefines[ ] =
{
   1002, "qAFTER",
   1003, "qEACH",
   1004, "qTATTRIBUTENAME",
   1005, "qBEFORE",
   1006, "qBASED",
   1007, "qCASE",
   1009, "qCONDOPERATOR",
   1010, "qCONSTANT",
   1011, "qCREATE",
   1012, "qCURSOR",
   1013, "qCOMMIT",
   1014, "qDELETE",
   1015, "qELSE",
   1016, "qEND",
   1017, "qENTITY",
   1018, "qTENTITYNAME",
   1019, "qTDATE",
   1020, "qFIRST",
   1021, "qFOR",
   1022, "qIF",
   1024, "qJOIN",
   1025, "qLAST",
   1026, "qACTIVATE",
   1027, "qLOOP",
   1028, "qLOD",
   1029, "qFORIF",
   1030, "qNEXT",
   1032, "qOF",
   1033, "qOPERATION",
   1034, "qOPERATOR",
   1035, "qPREVIOUS",
   1036, "qRETURN",
   1037, "qRETURNEND",
   1038, "qSET",
   1039, "qTDECIMAL",
   1040, "qTINTEGER",
   1041, "qTSHORT",
   1042, "qTSTRING",
   1043, "qUNTIL",
   1044, "qVARIABLE",
   1045, "qTVIEW",
   1046, "qWHERE",
   1047, "qWHILE",
   1048, "qWITHIN",
   1049, "qOTHERWISE",
   1050, "qON",
   1051, "qAND",
   1052, "qOR",
   1053, "qGLOBAL",
   1054, "qLOCAL",
   1055, "qOBJECT",
   1056, "qDIALOG",
   1057, "qDOMAIN",
   1058, "qRETURNED",
   1059, "qBREAK",
   1060, "qDEFINE",
   1061, "qRESTRICTING",
   1062, "qTO",
   1063, "qMULTIPLE",
   1064, "qROOTONLY",
   1065, "qSINGLE",
   1066, "qROOTONLYMULTIPLE",
   1067, "qEMPTY",
   1068, "qLIKE",
   1069, "qEXISTS",
   1070, "qEXIST",
   1071, "qDOES",
   1072, "qTCHARACTER",
   1073, "qIS",
   1074, "qNULL",
   1075, "qATTRIBUTE",
   1076, "qDERIVED",
   1077, "qCONSTRAINT",
   1078, "qTRANSFORMATION",
   1079, "qSHORTCUTKEY",
   1080, "qREGISTERED",
   1081, "qAS",
   1082, "qGET",
   1083, "qAT",
   1084, "qLEVEL",
   1085, "qSUBTASK",
   1086, "qTASK",
   1087, "qAPPLICATION",
   1088, "qSYSTEM",
   1089, "qANY",
   1090, "qNAME",
   1091, "qUSING",
   1092, "qINCLUDE",
   1093, "qEXCLUDE",
   1094, "qFROM",
   1095, "qNONE",
   1096, "qNAMED",
   1100, "qTUNKNOWN",
   1101, "qTVOID",
   1102, "qCONTINUE",
   1103, "qROOTONLYCONTINUE",
   1104, "qSINGLEFORUPDATE",
   2001, "qATTRIBUTEQUALIFIER",
   2002, "qENTITYQUALIFIER",
   2003, "qRESERVEDWORD",
   2004, "qUSERDEFINED",
   2005, "qDELIMITER",
   2006, "qEXPRESSION",
   2007, "qENDFUNC",
   2008, "qOPERATIONCALL",
   2009, "qNUMERIC",
   2010, "qTEXT",
   3001, "qEQUAL",
   3002, "qMINUS",
   3003, "qADDITION",
   3004, "qMULTIPLICATION",
   3005, "qDIVISION",
   3006, "qCONDEQUAL",
   3007, "qLESSTHANEQUAL",
   3008, "qLESSTHAN",
   3009, "qGREATERTHANEQUAL",
   3010, "qGREATERTHAN",
   3011, "qNOTEQUAL",
   3012, "qNOT",
   3013, "qCOMMA",
   3014, "qLPAREN",
   3015, "qRPAREN",
   3016, "qLBRACE",
   3017, "qRBRACE",
   3018, "qOPENOPER",
   3019, "qCLOSEOPER",
   3020, "qSEMICOLON",
   3021, "qCOLON",
   3022, "qNOTEXISTS",
   3023, "qNOTNULL",
   3024, "qPERIOD",
   3031, "qUNKNOWNTOKEN",
   3032, "qUNARYMINUS",
   4001, "qLOCALOPERATION",
   4002, "qGLOBALOPERATION",
   4003, "qOBJECTOPERATION",
   4004, "qDIALOGOPERATION",
   4005, "qDOMAINOPERATION",
   4006, "qZEIDONOPERATION",
   4007, "qCONTROLOPERATION",
   5001, "qBOTHVAR",
   5002, "qCONCATOPERATOR",
   0,    "Not Set",
   -1,   "UNKNOWN"
};

void
fnFindDefine( zPCHAR pchName, zLONG lMaxLth, zLONG lType )
{
   zSHORT k = 0;

   while ( g_qDefines[ k ].lType >= 0 )
   {
      if ( g_qDefines[ k ].lType == lType )
         break;

      k++;
   }

   strcpy_s( pchName, lMaxLth, g_qDefines[ k ].pchName );
}

void
TraceExpressionStruct( sQExprStruct *psExpr, zLONG lExprIdx, zCPCHAR cpcMsg1, zCPCHAR cpcMsg2 )
{
// zCHAR   szMsg[ 1024 ];
   zCHAR   szElementClass[ 32 ];
   zCHAR   szDataClass[ 32 ];
   zCHAR   szDataType[ 32 ];
   zCHAR   szOffset[ 32 ];
   zCHAR   szLevel[ 32 ];

   fnFindDefine( szElementClass, zsizeof( szElementClass ), psExpr->lElementClass );
   fnFindDefine( szDataClass, zsizeof( szDataClass ), psExpr->lDataClass );
   fnFindDefine( szDataType, zsizeof( szDataType ), psExpr->lDataType );
   fnFindDefine( szOffset, zsizeof( szOffset ), psExpr->lOffset );
   fnFindDefine( szLevel, zsizeof( szLevel ), psExpr->lLevel );
   TraceLine( "Expr ECls:%4d:%-16s  DCls:%4d:%-16s  DType:%10d:%-16s  Offset:%8d:%-16s  Lvl:%4d:%-16s  Flg:%x  Cnt:%3d  Idx:%3d  %s%s",
              psExpr->lElementClass, szElementClass, psExpr->lDataClass, szDataClass,
              psExpr->lDataType, szDataType, psExpr->lOffset, szOffset, psExpr->lLevel, szLevel, psExpr->lFlags, psExpr->lCount, lExprIdx, cpcMsg1, cpcMsg2 );
// zsprintf( szMsg, "ExprStruct Element Class: %4d:%16s   Data Class: %4d:%16s   Data Type: %10d:%16s   Offset: %8d:%16s   Level: %4d:%16s   Flags: %x   Idx: %d",
//           psExpr->lElementClass, szElementClass, psExpr->lDataClass, szDataClass,
//           psExpr->lDataType, szDataType, psExpr->lOffset, szOffset, psExpr->lLevel, szLevel, psExpr->lFlags, nExprIdx );
// TraceLineS( szMsg, "" );
}

void
fnAddView( zVIEW vSubtask, zPCHAR pchViewName, zLONG lMaxLth, sQExprStruct *psExpr, zPCHAR pchPFlag, zLONG lFlagLth, zPCHAR pchExprText )
{
   zCHAR  szTemp[ 64 ];
   zSHORT k;

   szTemp[ zsizeof( szTemp ) - 1 ] = 0;
   k = AddExprEntryToString( vSubtask, psExpr, szTemp, pchPFlag, lFlagLth, zsizeof( szTemp ) - 2, pchExprText, 0 ); // get view variable

   pchViewName[ 0 ] = '(';
   pchViewName[ 1 ] = ' ';
   strcpy_s( pchViewName + 2, lMaxLth - 2, szTemp + k + 1 );
   strcat_s( pchViewName, lMaxLth, " );\n" );
}

zOPER_EXPORT zSHORT OPERATION
GenerateNewExpression( zVIEW vSubtask, zPCHAR pchOutputString )
{
   sQExprStruct *psExpr;         // pointer to expression structure within szExprCode
   sQExprStruct sCurrExpr;       // copy of the current expression structure within szExprCode
   zPCHAR  pch;
   zCHAR   szExprCode[ EXPRCODE_MAXSTRING ]; // Expression attribute in Statement entity
   zCHAR   szExprText[ EXPRTEXT_MAXSTRING ]; // ExprText attribute in Statement entity
   zCHAR   szOperationName[ MAXSTRING ];
   zCHAR   szOperationGroup[ 32 ];
   zCHAR   szNewOperationClassStatement[ MAXSTRING ];
   zCHAR   szHeaderName[ 32 ];
   zCHAR   szVarName[ MAXSTRING ];           // plenty big (1024)
   zCHAR   szStringBuilder1[ MAXSTRING * 2 ];
   zCHAR   szStringBuilder2[ MAXSTRING ];
   zCHAR   szPFlag[ 2 ];
   zCHAR   szThrowsException[ 2 ];
   zCHAR   szThrowsExceptionCatchCode[ 256 ];
   zULONG  ulCodeIdx;
   zLONG   lLeftVarType = -1;
   zLONG   lRightVarType = -1;
   zLONG   lFlag = 0;
   zLONG   lDataType;
   zSHORT  nValueStack[ 50 ];     // list of indexes into the Expression
   zSHORT  nStackIdx;             // index into nValueStack
   zSHORT  nExprIdx;              // index into the Expression list (blob)
   zSHORT  nHoldExprIdx;          // keep original nExprIdx
   zSHORT  nFirstViewIdx = -1;
   zSHORT  nQualViewIdx = -1;     // index to qualifying view within Expression list (-1 ==> does not exist)
   zSHORT  nReturnParmIdx[ 200 ];  // index to return parameter within Expression list
   zLONG   lReturnParmType[ 200 ]; // type of return parameter within Expression list
   zSHORT  nReturnParmCnt = 0;
   zSHORT  nReturnStringCnt = 0;
   zSHORT  nReturnIntCnt = 0;
   zSHORT  nReturnDecimalCnt = 0;
   zSHORT  nReturnUnknownCnt = 0;
   zSHORT  nReturnTotalCnt = 0;
   zSHORT  nParmIdx[ 200 ];        // index to parameter within Expression list
   zSHORT  nParmCnt = 0;
   zSHORT  nStringCnt = 0;
   zSHORT  nIntCnt = 0;
   zSHORT  nDecimalCnt = 0;
   zSHORT  nUnknownCnt = 0;
   zSHORT  nTotalCnt = 0;
   zLONG   lOperator = -1;
   zSHORT  nConstantIdx = -1;
   zSHORT  nReturnVarIdx = -1;    // index to return variable within Expression list (-1 ==> does not exist)
   zLONG   lReturnVarType = -1;
   zSHORT  nReturnCodeIdx = -1;   // index to return code variable within Expression list (-1 ==> does not exist)
   zSHORT  nOutputIdx;            // index into pchOutputString
   zSHORT  nTopOfStack;           // receives value from top of nValueStack
   zSHORT  nIndent;
   zBOOL   bUnaryContinue;
   zBOOL   bReturn = FALSE;
   zBOOL   bTestCondition = FALSE;
   zBOOL   bOperation = FALSE;
   zBOOL   bFunctionInString = FALSE;
   zBOOL   bFunctionProcessed;
   zSHORT  nEqual = 0;  // 0 ==> not yet found; 1 ==> found; -1 ==> found and processed
   zBOOL   bDirectOutput = FALSE;
   zBOOL   bDouble = FALSE;
   zSHORT  nViewCnt = 0;
   zSHORT  nCnt;
   zSHORT  nLth;
   zSHORT  k;

#ifdef DEBUG_PARSEGEN
   zBOOL   bDebug = TRUE;
#else
   zBOOL   bDebug = FALSE;
#endif

   // Check for "return".  First eliminate leading blanks.
   pch = pchOutputString + strspn( pchOutputString, " " );
   nIndent = pch - pchOutputString;
   if ( zstrcmp( pch, "return " ) == 0 || zstrcmp( pch, "return( " ) == 0 ) // pch now points to first non-blank character
      bReturn = TRUE;
   else
   {
      if ( zstrcmp( pch, "if " ) == 0 )
         bTestCondition = TRUE;
   }

   // Initialize the stack pointer to be zero.
   nStackIdx = 0;
   nValueStack[ 0 ] = -1;  // initialize to "out of range"

   // Make the index into the output string start at the end since we will be building the statement in reverse ... from end to beginning.
   g_pchOutputExprStr[ VM_MAX_STRING_SIZE - 1 ] = 0;  // null last byte
   nOutputIdx = VM_MAX_STRING_SIZE - 2;  // point to byte prior to null

   // Get the two attributes from the statement entity.
   ulCodeIdx = EXPRCODE_MAXSTRING;   // inform GetBlob of maximum return length (12000)
   GetBlobFromAttribute( szExprCode, &ulCodeIdx, g_vStatementView, "Statement", "Expression" );
   nExprIdx = (zSHORT) ulCodeIdx;             // e.g. 308 or 252 or 196 (some multiple of 28)
   ulCodeIdx = EXPRTEXT_MAXSTRING;   // inform GetBlob of maximum return length (1200)
   GetBlobFromAttribute( szExprText, &ulCodeIdx, g_vStatementView, "Statement", "ExprText" );

   // Initialize the expression index (to be what? ... dks 2004.01.28)
   // It appears that the structures in the blob are are just the portion of sQExprStruct without the "zCHAR szText[ MAXSTRING ];" element. If this
   // turns out not to be the case, will rewrite this comment ... dks 2009.08.23
   // Therefore we are initializing nExprIdx to point to the beginning of the last ExprStruct in the blob.

#ifdef DEBUG_PARSEGEN  // enable just to help figure out what's going on
   {
      zSHORT  nWork;

      nWork = sizeof( sQExprStruct );     // 1058
      nWork -= MAXSTRING;             // 1058 - 1024
      if ( nExprIdx % nWork ) // if it's not a multiple of nWork, we don't understand
         SysMessageBox( vSubtask, "DKS", "Unexpected size of expression blob", 0 );
      else
         TraceLineI( "ExprStruct size: ", nWork );

      nCnt = nExprIdx / (sizeof( sQExprStruct ) - MAXSTRING);
      nExprIdx -= nWork;  // e.g. 336 - 28 = 308 or  252 - 28 = 224  or  224 - 28 = 196
      nHoldExprIdx = nExprIdx;
   }
#else
   nCnt = nExprIdx / (sizeof( sQExprStruct ) - MAXSTRING);
   nExprIdx -= (sizeof( sQExprStruct ) - MAXSTRING); // now point to beginning of last ExprStruct
   nHoldExprIdx = nExprIdx;
#endif

   szThrowsException[ 0 ] = 0;
   szOperationName[ 0 ] = 0;
   szHeaderName[ 0 ] = 0;
   szNewOperationClassStatement[ 0 ] = 0;
   szOperationGroup[ 0 ] = 0;

   // This is code to iterate through the Expression list and sort things out in preparation for Java generation.  We want to modify the
   // flags in the blob, so we use a pointer to get around the Expression list.
   if ( g_szGenLang[ 0 ] == 'J' )
   {
#ifdef DEBUG_PARSEGEN
      TraceLineS( "Expression struct list: ", "GenerateNewExpression" );
#endif

      // Work thru to get the operation name, return counts, and any special Java cast requirements.
      while ( nExprIdx >= 0 )
      {
         psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
//#ifdef DEBUG_PARSEGEN
         if ( bDebug ) // || psExpr->lOffset == 2681057 )  // ZeidonStringCopy
            TraceExpressionStruct( psExpr, nExprIdx, (psExpr->lOffset <= (zLONG) ulCodeIdx) ? szExprText + psExpr->lOffset : "", "" );  // display this expression structure
//#endif

         if ( psExpr->lElementClass == qOPERATIONCALL )
         {
             bOperation = TRUE;  // done here for special case, but will be repeated in next loop
             if ( psExpr->lOffset > MAXSTRING )
               GetOperationNameFromZKey( vSubtask, szOperationName, zsizeof( szOperationName ), szHeaderName, zsizeof( szHeaderName ),
                                         szThrowsException, zsizeof( szThrowsException ), szThrowsExceptionCatchCode, zsizeof( szThrowsExceptionCatchCode ),
                                         szOperationGroup, zsizeof( szOperationGroup ), psExpr->lDataClass, psExpr->lOffset );
            else
               strcpy_s( szOperationName, zsizeof( szOperationName ), szExprText + psExpr->lOffset );

            lRightVarType = -1;
            lLeftVarType = -1;

            if ( szHeaderName[ 0 ] )
            {
               if ( zstrcmp( szHeaderName, "KZOENGAA" ) == 0 || zstrcmp( szHeaderName, "TZVMLIP" ) == 0 )
                  szHeaderName[ 0 ] = 0;
               else
               {
                  // do something like:
                  // import com.quinsoft.zeidon.zeidonoperations.KZOEP1AA;
                  if ( SetCursorFirstEntityByString( g_lpPIView, "ExternalOperationJava", "SourceName", szHeaderName, 0 ) <= zCURSOR_UNCHANGED )
                  {
                     CreateEntity( g_lpPIView, "ExternalOperationJava", zPOS_LAST );
                     SetAttributeFromInteger( g_lpPIView, "ExternalOperationJava", "ZKey", psExpr->lOffset );
                     SetAttributeFromString( g_lpPIView, "ExternalOperationJava", "SourceName", szHeaderName );
                  // SetAttributeFromString( g_lpPIView, "ExternalOperationJava", "SourceType", "?" );
                  }

                  // Change:
                  // SysReadZeidonIni( -1, "App.ePamms", "WebDirectory", sb_szDirectoryName );

                  // To:
                  // {
                  //    KZOEP1AA m_KZOEP1AA = new KZOEP1AA( lAdvisee );
                  //    m_KZOEP1AA.SysReadZeidonIni( -1, "App.ePamms", "WebDirectory", sb_szDirectoryName );
                  // }
               }
            }

         // break;
         }
         else
         if ( psExpr->lElementClass == qVARIABLE )
         {
            nParmIdx[ nParmCnt++ ] = nExprIdx;

            // Other than return View parameters (which we ignore since they should be declared as zVIEW), we will handle
            // multiple "String" and "Int" return parameters, but at most one other type of return parameter.
            if ( psExpr->lDataType == qTVIEW )  // qTVIEW:1045
            {
               if ( psExpr->lOffset >= 0 )  // ==> it's not a pointer ... take the firstmost view
                  nFirstViewIdx = nExprIdx;

               // Ignore return View parameters except for special case of setting View1 = View2.
               nViewCnt++;
            }
            else
            if ( psExpr->lOffset < 0 )  // ==> it's a pointer
            {
               if ( psExpr->lDataType == qTSTRING )  // we don't mind multiple return "string" parameters
               {
                  nReturnStringCnt++;
               }
               else
               if ( psExpr->lDataType == qTSHORT || psExpr->lDataType == qTINTEGER )  // we don't mind multiple return "int" parameters
               {
                  nReturnIntCnt++;
               }
               else
               if ( psExpr->lDataType == qTDECIMAL )  // we don't mind multiple return "decimal" parameters
               {
                  nReturnDecimalCnt++;
               }
               else
               {
                  nReturnUnknownCnt++;
               }
            }
            else
            {
               if ( psExpr->lDataType == qTSTRING )  // we don't mind multiple return "string" parameters
               {
                  nStringCnt++;
               }
               else
               if ( psExpr->lDataType == qTSHORT || psExpr->lDataType == qTINTEGER )
               {
                  nIntCnt++;
                  if ( lRightVarType == -1 )
                     lRightVarType = psExpr->lDataType;
                  else
                  if ( lLeftVarType == -1 )
                     lLeftVarType = psExpr->lDataType;
                  else
                  if ( lRightVarType == qTSHORT || lRightVarType == qTINTEGER )
                  {
                     lRightVarType = lLeftVarType;
                     lLeftVarType = psExpr->lDataType;
                  }
               }
               else
               if ( psExpr->lDataType == qTDECIMAL )
               {
                  nDecimalCnt++;
                  if ( lRightVarType == -1 )
                     lRightVarType = psExpr->lDataType;
                  else
                  if ( lLeftVarType == -1 )
                     lLeftVarType = psExpr->lDataType;
                  else
                  if ( lRightVarType == qTSHORT || lRightVarType == qTINTEGER )
                  {
                     lRightVarType = lLeftVarType;
                     lLeftVarType = psExpr->lDataType;
                  }
               }
               else
               {
                  nUnknownCnt++;
               }
            }
         }
         else
         if ( psExpr->lElementClass == qOPERATOR )
         {
            if ( psExpr->lOffset == qEQUAL )
               nEqual = 1;
            else
               lOperator = psExpr->lOffset;
         }
         else
            if ( psExpr->lElementClass == qCONSTANT )
               nConstantIdx = nExprIdx;

         nExprIdx -= (sizeof( sQExprStruct ) - MAXSTRING);
      }

      nTotalCnt = nStringCnt + nIntCnt + nDecimalCnt + nUnknownCnt;
      nReturnTotalCnt = nReturnStringCnt + nReturnIntCnt + nReturnDecimalCnt + nReturnUnknownCnt;

      // if we found view1 = view2 ...
      if ( bOperation == FALSE && nEqual > 0 )
      {
         sQExprStruct *psExpr1 = 0;
         sQExprStruct *psExpr2 = 0;
         zCHAR   szPFlag1[ 2 ];
         zCHAR   szPFlag2[ 2 ];

         if ( nParmCnt > 1 )
         {
            psExpr2 = (sQExprStruct *) ((zPCHAR) szExprCode + nParmIdx[ 0 ]);  // reverse order to help those of us that happen
            psExpr1 = (sQExprStruct *) ((zPCHAR) szExprCode + nParmIdx[ 1 ]);  // to be Polish Notation challenged
         }
         else
         if ( nParmCnt > 0 )
         {
            psExpr1 = (sQExprStruct *) ((zPCHAR) szExprCode + nParmIdx[ 0 ]);
            if ( nConstantIdx >= 0 )
               psExpr2 = (sQExprStruct *) ((zPCHAR) szExprCode + nConstantIdx);
         }

         if ( psExpr1 && psExpr2 )
         {
            szStringBuilder2[ zsizeof( szStringBuilder2 ) - 1 ] = 0;
            k = AddExprEntryToString( vSubtask, psExpr2, szStringBuilder2, szPFlag2, zsizeof( szPFlag2 ), zsizeof( szStringBuilder2 ) - 2, szExprText, 0 ); // get variable
            strcpy_s( szStringBuilder2, zsizeof( szStringBuilder2 ), szStringBuilder2 + k + 1 );

            szStringBuilder1[ zsizeof( szStringBuilder1 ) - 1 ] = 0;
            k = AddExprEntryToString( vSubtask, psExpr1, szStringBuilder1, szPFlag1, zsizeof( szPFlag1 ), zsizeof( szStringBuilder1 ) - 2, szExprText, 0 ); // get variable
            strcpy_s( szStringBuilder1, zsizeof( szStringBuilder1 ), szStringBuilder1 + k + 1 );

            if ( (pch = zstrstr( szStringBuilder1, ".intValue( )" )) ||
                 (pch = zstrstr( szStringBuilder1, ".doubleValue( )" )) ||
                 (pch = zstrstr( szStringBuilder1, ".toString( )" )) )
            {
               *pch = 0;
            }

            if ( (pch = zstrstr( szStringBuilder2, ".intValue( )" )) ||
                 (pch = zstrstr( szStringBuilder2, ".doubleValue( )" )) ||
                 (pch = zstrstr( szStringBuilder2, ".toString( )" )) )
            {
               *pch = 0;
            }

            if ( nCnt == 5 )
            {
               if (lOperator > 0 && nConstantIdx >= 0 )
               {
                  psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nConstantIdx);
                  if ( psExpr->lElementClass == qCONSTANT && zstrcmp( szExprText + psExpr->lOffset, "1" ) == 0 && zstrcmp( szStringBuilder1, szStringBuilder2 ) == 0 )
                  {
                     if ( ((nDecimalCnt > 0 && psExpr1->lDataType == qTDECIMAL) ||  // qTDECIMAL:1039
                          (nIntCnt > 0 && (psExpr1->lDataType == qTSHORT || psExpr1->lDataType == qTINTEGER))) &&  // qTSHORT:1041  qTINTEGER:1040
                          szPFlag1[ 0 ] == 'Y' )
                     {
                        if ( lOperator == qADDITION || lOperator == qMINUS )
                        {
                           zmemset( pchOutputString, ' ', nIndent );
                           strcpy_s( pchOutputString + nIndent, VM_MAX_STRING_SIZE - nIndent, szStringBuilder1 );
                           if ( lOperator == qADDITION )
                              strcat_s( pchOutputString, VM_MAX_STRING_SIZE, ".increment( )" );
                           else
                              strcat_s( pchOutputString, VM_MAX_STRING_SIZE, ".decrement( )" );

                           goto EXPRESSION_EXIT_label;
                        }
                     }
                  }
               }

               if ( nParmCnt == 3 )
               {
                  psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nParmIdx[ 2 ]);
                  szVarName[ zsizeof( szVarName ) - 1 ] = 0;
                  k = AddExprEntryToString( vSubtask, psExpr, szVarName, szPFlag, zsizeof( szPFlag ), zsizeof( szVarName ) - 2, szExprText, 0 ); // get variable
                  strcpy_s( szVarName, zsizeof( szVarName ), szVarName + k + 1 );
                  if ( szPFlag[ 0 ] == 'Y' && psExpr->lDataType == qTDECIMAL )
                     bDouble = TRUE;
               }
            }

            if ( nCnt == 3 )
            {
               if ( nViewCnt == 2 )
               {
                  zmemset( pchOutputString, ' ', nIndent );
                  strcpy_s( pchOutputString + nIndent, VM_MAX_STRING_SIZE - nIndent, "SetViewFromView( " );
                  strcat_s( pchOutputString, VM_MAX_STRING_SIZE, szStringBuilder1 );
                  strcat_s( pchOutputString, VM_MAX_STRING_SIZE, ", " );
                  strcat_s( pchOutputString, VM_MAX_STRING_SIZE, szStringBuilder2 );
                  strcat_s( pchOutputString, VM_MAX_STRING_SIZE, " )" );
                  goto EXPRESSION_EXIT_label;
               }
               else
               if ( nDecimalCnt > 0 )
               {
                  if ( szPFlag1[ 0 ] == 'Y' && psExpr1->lDataType == qTDECIMAL )
                  {
                     zmemset( pchOutputString, ' ', nIndent );
                     strcpy_s( pchOutputString + nIndent, VM_MAX_STRING_SIZE - nIndent, szStringBuilder1 );
                     strcat_s( pchOutputString, VM_MAX_STRING_SIZE, ".setValue( " );
                     strcat_s( pchOutputString, VM_MAX_STRING_SIZE, szStringBuilder2 );
                     strcat_s( pchOutputString, VM_MAX_STRING_SIZE, " )" );
                     goto EXPRESSION_EXIT_label;
                  }
                  else
                  if ( szPFlag2[ 0 ] == 'Y' && psExpr2->lDataType == qTDECIMAL )
                  {
                     if ( nConstantIdx >= 0 )
                     {
                        zmemset( pchOutputString, ' ', nIndent );
                        strcpy_s( pchOutputString + nIndent, VM_MAX_STRING_SIZE - nIndent, szStringBuilder1 );
                        strcat_s( pchOutputString, VM_MAX_STRING_SIZE, " = " );
                        strcat_s( pchOutputString, VM_MAX_STRING_SIZE, szStringBuilder2 );
                        goto EXPRESSION_EXIT_label;
                     }
                     else
                     {
                        zmemset( pchOutputString, ' ', nIndent );
                        strcpy_s( pchOutputString + nIndent, VM_MAX_STRING_SIZE - nIndent, szStringBuilder2 );
                        strcat_s( pchOutputString, VM_MAX_STRING_SIZE, ".setValue( " );
                        strcat_s( pchOutputString, VM_MAX_STRING_SIZE, szStringBuilder1 );
                        strcat_s( pchOutputString, VM_MAX_STRING_SIZE, " )" );
                        goto EXPRESSION_EXIT_label;
                     }
                  }
               }
               else
               if ( nIntCnt > 0 && szPFlag1[ 0 ] == 'Y' && (psExpr1->lDataType == qTINTEGER || psExpr1->lDataType == qTSHORT) )
               {
                  zmemset( pchOutputString, ' ', nIndent );
                  strcpy_s( pchOutputString + nIndent, VM_MAX_STRING_SIZE - nIndent, szStringBuilder1 );
                  strcat_s( pchOutputString, VM_MAX_STRING_SIZE, ".setValue( " );
                  strcat_s( pchOutputString, VM_MAX_STRING_SIZE, szStringBuilder2 );
                  strcat_s( pchOutputString, VM_MAX_STRING_SIZE, " )" );
                  goto EXPRESSION_EXIT_label;
               }
            }
         }
      }

      bOperation = FALSE;   // repeat operation location processing to find the return code idx
      nExprIdx = nHoldExprIdx;

      // First, process the list looking for (non-string) return arguments so we can determine if there is a return value that needs to replace the
      // return code.  At the same time, determine if there are return string argument(s) that need to be declared as mutable.
      while ( nExprIdx >= 0 )
      {
         psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
         if ( nExprIdx == 0 && psExpr->lElementClass == qCONSTANT && psExpr->lDataClass == qNUMERIC &&
              psExpr->lDataType == qTINTEGER && zstrcmp( szExprText + psExpr->lOffset, "while " ) == 0 )
         {
            bDirectOutput = TRUE;
         }

         if ( psExpr->lElementClass == qOPERATIONCALL )
            bOperation = TRUE;  // need this here for purposes of finding the return code idx
         else
         if ( psExpr->lElementClass == qVARIABLE )
         {
            if ( psExpr->lOffset < 0 )  // ==> it's a pointer
            {
               // Other than return View parameters (which we ignore since they should be declared as zVIEW), we will handle
               // multiple "String" and "Int" return parameters, but at most one other type of return parameter.
               if ( psExpr->lDataType == qTVIEW )  // qTVIEW:1045
                 // psExpr->lDataType == qTENTITYNAME ||     don't know about these yet ... dks 2010.06.29
                 // psExpr->lDataType == qTATTRIBUTENAME )
               {
                  psExpr->lFlags |= MUTABLE_BIT;
               }
               else
               {
                  if ( FALSE && nReturnTotalCnt == 1 )  // not gonna do this nomore me thinks ... dks 2010.07.07
                  {
                     lReturnVarType = psExpr->lDataType;
                     nReturnVarIdx = nExprIdx;
                  }
                  else
                  // qTSTRING:1042  qTSHORT:1041  qTINTEGER:1040  qTDECIMAL:1039
                  if ( psExpr->lDataType == qTSTRING || psExpr->lDataType == qTSHORT || psExpr->lDataType == qTINTEGER || psExpr->lDataType == qTDECIMAL  )
                  {
                     lReturnParmType[ nReturnParmCnt ] = psExpr->lDataType;
                     nReturnParmIdx[ nReturnParmCnt ] = nExprIdx;
                     nReturnParmCnt++;
                  }
                  else
                  if ( nReturnUnknownCnt == 1 )
                  {
                     lReturnVarType = psExpr->lDataType;
                     nReturnVarIdx = nExprIdx;
                  }
                  else
                  {
                     // We have more than one "non-string" return parameter.
                  // SyntaxError( vSubtask, eMULTIPLERETURNARGUMENTS, szOperationName );
                     TraceLine( "Multiple Return Arguments (INVALID %s): would like to put the name of the operation here: ", szOperationName );
                  }
               }
            }

#if 1  // thought about disabling because of new wrapper class, but it looks like we need this  ... dks 2010.03.25
            if ( psExpr->lDataType == qTVIEW )
            {
            // if ( psExpr->lDataClass == qNUMERIC )
               if ( psExpr->lDataClass == qNUMERIC || psExpr->lDataClass == qVARIABLE )
               {
                  if ( 0 && bTestCondition )
                  {
                     // There cannot be a qualifying view if we are testing a condition.
                     sQExprStruct *psTempExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx + (sizeof( sQExprStruct ) - MAXSTRING));
                     psTempExpr->lFlags |= TESTVIEW_BIT;
                  }
                  else
                  {
                     // Take the view closest to the start of the parameter list as the qualifying view unless it is a return view.
                     if ( psExpr->lOffset >= -1 )  // 0 ?  dks 2009.12.30
                     {
                     // if ( nQualViewIdx > -1 )
                     // {
                     //    sQExprStruct *psTempExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nQualViewIdx);
                     //    psTempExpr->lFlags &= ~SKIP_BIT;
                     // }

                        nQualViewIdx = nExprIdx;
                     // psExpr->lFlags |= SKIP_BIT;
                     }
                  }
               }
               else
               {
                  TraceLine( "QualifyingView found for Operation: %s    where DataClass is not NUMERIC and not VARIABLE?", szOperationName );
               }
            }
#endif

            // If we've found an operation, the next variable (if it exists) must be the return code (I hope! dks 2009.10.05).
            if ( bOperation )
            {
               if ( nReturnCodeIdx >= 0 )
                  TraceLineS( "Don't know why we have multiple Return Codes???", "" );

               nReturnCodeIdx = nExprIdx;
            }
         }

         nExprIdx -= (sizeof( sQExprStruct ) - MAXSTRING);
      }

#if 0
      // Second, if this expression contains an operation call, we have to check if there is a
      // qualifying view and if there is a return parameter.  If there is a return parameter, we
      // need to replace the return code with the return parameter.  We still need the real return
      // code, so will generate a call to GetJOE_ReturnCode( ) in order to get the real return code.
      if ( bOperation )
      {
         if ( nQualViewIdx < 0 )
         {
         // SyntaxError( vSubtask, eQUALIFYINGVIEWUNDEFINED, "would like to put the name of the operation here" );
            TraceLine( "QualifyingViewUndefined for Operation: %s    What do we do? ... is there a global view we can use?", szOperationName );
         }
         else
         {
            // There is a qualifying view.  Remove it and associated comma (if any) from the parameter list.
            nExprIdx = nQualViewIdx;
            psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
            psExpr->lFlags |= SKIP_BIT;
            nExprIdx += (sizeof( sQExprStruct ) - MAXSTRING);
            psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
            if ( psExpr->lElementClass == qOPERATOR && psExpr->lOffset == qCOMMA )
               psExpr->lFlags |= SKIP_BIT;
            else
            {
               nExprIdx = nQualViewIdx - (sizeof( sQExprStruct ) - MAXSTRING);
               psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
               if ( psExpr->lElementClass == qOPERATOR && psExpr->lOffset == qCOMMA )
                  psExpr->lFlags |= SKIP_BIT;
            }
         }
      }
      else
#endif
      {
         // Do not want/need a qualifying view or a return code if there is no operation.
      // nQualViewIdx = -1;
      // nReturnVarIdx = -1;
      // nReturnVarIdx2 = -1;
      // nReturnCodeIdx = -1;
      }

      if ( nReturnCodeIdx >= 0 && nReturnVarIdx < 0 )
         nReturnVarIdx = nReturnCodeIdx;

#if 0  // let's leave the parameter so it is in the call twice (once as return code).

      // There is a return variable in the parameter list.  Remove it and associated comma (if any)
      // from the parameter list.
      if ( nReturnVarIdx >= 0 && nReturnVarIdx != nReturnCodeIdx )
      {
         nExprIdx = nReturnVarIdx;
         psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
         psExpr->lFlags |= SKIP_BIT;
         nExprIdx += (sizeof( sQExprStruct ) - MAXSTRING);
         psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
         if ( psExpr->lElementClass == qOPERATOR && psExpr->lOffset == qCOMMA )
            psExpr->lFlags |= SKIP_BIT;
         else
         {
            nExprIdx = nReturnVarIdx - (sizeof( sQExprStruct ) - MAXSTRING);
            psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
            if ( psExpr->lElementClass == qOPERATOR && psExpr->lOffset == qCOMMA )
               psExpr->lFlags |= SKIP_BIT;
         }
      }
#endif

      // If we have an operation call and the return code has been replaced by a return variable, we have to call
      // GetJOE_ReturnCode to get the real return code.  No longer true ... now honoring multiple return parms.  dks 2010.07.15
      zmemset( szStringBuilder1, '*', zsizeof( szStringBuilder1 ) ); // only for debugging
      zmemset( szStringBuilder2, '*', zsizeof( szStringBuilder2 ) ); // only for debugging
      szStringBuilder1[ 0 ] = 0;
      szStringBuilder2[ 0 ] = 0;
      if ( bOperation )
      {
         if ( szThrowsException[ 0 ] == 'Y' )
         {
            g_pchOutputExprStr[ nOutputIdx-- ] = '}';
            nOutputIdx -= nIndent;
            zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent );

            // Borrow szStringBuilder1 for a sec ...
            zmemset( szStringBuilder1, ' ', nIndent + 3 );
            strcpy_s( szStringBuilder1 + nIndent + 3, zsizeof( szStringBuilder1 ) - (nIndent + 3), "throw ZeidonException.wrapException( e );\n" );
            nLth = (zSHORT) zstrlen( szStringBuilder1 );
            nOutputIdx -= nLth;
            zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szStringBuilder1, nLth );
            g_pchOutputExprStr[ nOutputIdx-- ] = '\n';

            if ( szThrowsExceptionCatchCode[ 0 ] )
            {
               nLth = (zSHORT) zstrlen( szThrowsExceptionCatchCode );
               nOutputIdx -= nLth;
               zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szThrowsExceptionCatchCode, nLth );
               nOutputIdx -= nIndent + 3;
               zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent + 3 );
               g_pchOutputExprStr[ nOutputIdx-- ] = '\n';
            }

            g_pchOutputExprStr[ nOutputIdx-- ] = '{';
            nOutputIdx -= nIndent;
            zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent );
            zmemset( szStringBuilder1, ' ', nIndent );
            strcpy_s( szStringBuilder1 + nIndent, zsizeof( szStringBuilder1 ) - nIndent, "catch ( Exception e )\n" );
            nLth = (zSHORT) zstrlen( szStringBuilder1 );
            nOutputIdx -= nLth;
            zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szStringBuilder1, nLth );
            g_pchOutputExprStr[ nOutputIdx-- ] = '\n';

         // nOutputIdx -= nIndent;
         // zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent );

            g_pchOutputExprStr[ nOutputIdx-- ] = '}';

            nOutputIdx -= nIndent;
            zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent );

            g_pchOutputExprStr[ nOutputIdx-- ] = '\n';
            g_pchOutputExprStr[ nOutputIdx-- ] = ';';

            // g_pchOutputExprStr[ nOutputIdx + nIndent + 1 ] = '}'; // reset the brace that was obliterated
            zmemset( szStringBuilder1, '*', zsizeof( szStringBuilder1 ) ); // only for debugging
            szStringBuilder1[ 0 ] = 0;
         }

         if ( szOperationGroup[ 0 ] )
         {
         // g_pchOutputExprStr[ nOutputIdx-- ] = '}';
         // nOutputIdx -= nIndent;
         // zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent );

            // Borrow szStringBuilder1 for a sec ...
            szStringBuilder1[ 0 ] = ';';
            szStringBuilder1[ 1 ] = '\n';
            zmemset( szStringBuilder1 + 2, ' ', nIndent + 1 );
            szStringBuilder1[ nIndent + 3 ] = '/';
            szStringBuilder1[ nIndent + 4 ] = '/';
            szStringBuilder1[ nIndent + 5 ] = ' ';
            szStringBuilder1[ nIndent + 6 ] = 'm';
            szStringBuilder1[ nIndent + 7 ] = '_';
            strcpy_s( szStringBuilder1 + nIndent + 8, zsizeof( szStringBuilder1 ) - (nIndent + 8), szOperationGroup );
            strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), " = null;  // permit gc  (unnecessary)\n" );
            nLth = (zSHORT) zstrlen( szStringBuilder1 );
            zmemset( szStringBuilder1 + nLth, ' ', nIndent );
            nLth += nIndent;
            szStringBuilder1[ nLth++ ] = '}';
            szStringBuilder1[ nLth ] = 0;
            nOutputIdx -= nLth;
            zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szStringBuilder1, nLth );
         // nOutputIdx--;

         // zmemset( szNewOperationClassStatement, ' ', nIndent );
            szNewOperationClassStatement[ 0 ] = '{';
            szNewOperationClassStatement[ 1 ] = '\n';
            zmemset( szNewOperationClassStatement + 2, ' ', nIndent + 1 );
            strcpy_s( szNewOperationClassStatement + nIndent + 3, zsizeof( szNewOperationClassStatement ) - (nIndent + 3), szOperationGroup );
            strcat_s( szNewOperationClassStatement, zsizeof( szNewOperationClassStatement ), " m_" );
            strcat_s( szNewOperationClassStatement, zsizeof( szNewOperationClassStatement ), szOperationGroup );
            strcat_s( szNewOperationClassStatement, zsizeof( szNewOperationClassStatement ), " = new " );
            strcat_s( szNewOperationClassStatement, zsizeof( szNewOperationClassStatement ), szOperationGroup );

            if ( nFirstViewIdx >= 0 )
            {
               fnAddView( vSubtask, szNewOperationClassStatement + zstrlen( szNewOperationClassStatement ),
                          MAXSTRING - zstrlen( szNewOperationClassStatement ),
                          (sQExprStruct *) ((zPCHAR) szExprCode + nFirstViewIdx), szPFlag, zsizeof( szPFlag ), szExprText );
            }
            else
            {
               zCHAR  szName[ 33 ];
               zSHORT nRC;

               SetNameForView( g_lpPIView, "g_lpPIView", vSubtask, zLEVEL_TASK );
               SetNameForView( g_vStatementView, "g_vStatementView", vSubtask, zLEVEL_TASK );

               // Look for qTVIEW:1045
               szName[ 0 ] = 0;
               nRC = SetCursorFirstEntity( g_lpPIView, "Variable", "" );
               while ( nRC >= zCURSOR_SET )
               {
                  GetIntegerFromAttribute( &lDataType, g_lpPIView, "Variable", "DataType" );
                  if ( lDataType == qTVIEW )
                  {
                     GetStringFromAttribute( szPFlag, zsizeof( szPFlag ), g_lpPIView, "Variable", "PFlag" );
                     if ( szPFlag[ 0 ] != 'Y' ) // don't want a return view
                     {
                        GetStringFromAttribute( szName, zsizeof( szName ), g_lpPIView, "Variable", "Name" );
                        break;
                     }
                  }

                  nRC = SetCursorNextEntity( g_lpPIView, "Variable", "" );
               }

               if ( szName[ 0 ] )
               {
                  strcat_s( szNewOperationClassStatement, zsizeof( szNewOperationClassStatement ), "( " );
                  strcat_s( szNewOperationClassStatement, zsizeof( szNewOperationClassStatement ), szName );
                  strcat_s( szNewOperationClassStatement, zsizeof( szNewOperationClassStatement ), " );\n" );
               }
               else
                  strcat_s( szNewOperationClassStatement, zsizeof( szNewOperationClassStatement ), "( task );\n" ); // punt
            }

            nLth = (zSHORT) zstrlen( szNewOperationClassStatement );
            zmemset( szNewOperationClassStatement + nLth, ' ', nIndent );
            szNewOperationClassStatement[ nLth + nIndent ] = 0;
         }

         if ( (/* nReturnCodeIdx >= 0 && */ nReturnVarIdx >= 0 && nReturnCodeIdx != nReturnVarIdx) || nReturnParmCnt > 0 )
         {
            if ( nReturnParmCnt > 0 )  // we at least found one return variable
            {
               zSHORT nIdx = 0;

               nLth = 0;

               // Extra return variables are either of type String or Int or Double.  We will turn them into StringBuilder or MutableInt or MutableDouble.
               while ( nIdx < nReturnParmCnt )
               {
                  nExprIdx = nReturnParmIdx[ nIdx ];
                  psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
                  szVarName[ zsizeof( szVarName ) - 1 ] = 0;
                  k = AddExprEntryToString( vSubtask, psExpr, szVarName, szPFlag, zsizeof( szPFlag ), zsizeof( szVarName ) - 2, szExprText, 0 ); // get return variable
                  while ( TRUE )  // purist's goto
                  {
                     if ( szPFlag[ 0 ] == 'Y' )
                     {
                        // The variable is already a "return" type, so we don't want to make it into a return type.
                        k = nIdx;
                        while ( k < nReturnParmCnt )
                        {
                           nReturnParmIdx[ k ] = nReturnParmIdx[ k + 1 ];
                           lReturnParmType[ k ] = lReturnParmType[ k + 1 ];
                           k++;
                        }

                        nReturnParmCnt--;
                        break;  // out of inner loop
                     }

                     k++;
                     if ( nIdx == 0 )
                     {
                     // szStringBuilder1[ 0 ] = '\n';
                     // zmemset( szStringBuilder1, ' ', nIndent );
                        szStringBuilder1[ 0 ] = '{';
                        szStringBuilder1[ 1 ] = 0;

                        szStringBuilder2[ 0 ] = 0;
                        nLth = 0;
                     }
                     else
                     {
                     }

                     szStringBuilder2[ nLth++ ] = ';';
                     szStringBuilder2[ nLth++ ] = '\n';
                     szStringBuilder2[ nLth ] = 0;

                     if ( lReturnParmType[ nIdx ] == qTSTRING )
                     {
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), "StringBuilder sb_" );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), szVarName + k );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), ";\n" );
                        nLth = (zSHORT) zstrlen( szStringBuilder1 );
                        zmemset( szStringBuilder1 + nLth, ' ', nIndent );
                        nLth += nIndent;
                        szStringBuilder1[ nLth ] = 0;
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), "if ( " );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), szVarName + k );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), " == null )\n" );
                        nLth = (zSHORT) zstrlen( szStringBuilder1 );
                        zmemset( szStringBuilder1 + nLth, ' ', nIndent + 3 );
                        nLth += nIndent + 3;
                        szStringBuilder1[ nLth ] = 0;
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), "sb_" );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), szVarName + k );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), " = new StringBuilder( 32 );\n" );
                        nLth = (zSHORT) zstrlen( szStringBuilder1 );
                        zmemset( szStringBuilder1 + nLth, ' ', nIndent );
                        nLth += nIndent;
                        szStringBuilder1[ nLth ] = 0;
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), "else\n" );
                        nLth = (zSHORT) zstrlen( szStringBuilder1 );
                        zmemset( szStringBuilder1 + nLth, ' ', nIndent + 3 );
                        nLth += nIndent + 3;
                        szStringBuilder1[ nLth ] = 0;
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), "sb_" );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), szVarName + k );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), " = new StringBuilder( " );
                     }
                     else
                     if ( lReturnParmType[ nIdx ] == qTDECIMAL )
                     {
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), "MutableDouble md_" );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), szVarName + k );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), " = new MutableDouble( " );
                     }
                     else
                     {
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), "MutableInt mi_" );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), szVarName + k );
                        strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), " = new MutableInt( " );
                     }

                     strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), szVarName + k );
                     strcat_s( szStringBuilder1, zsizeof( szStringBuilder1 ), " );\n" );
                     nLth = (zSHORT) zstrlen( szStringBuilder1 );
                     zmemset( szStringBuilder1 + nLth, ' ', nIndent );
                     nLth += nIndent;
                     szStringBuilder1[ nLth ] = 0;

                     nLth = (zSHORT) zstrlen( szStringBuilder2 );
                     zmemset( szStringBuilder2 + nLth, ' ', nIndent );
                     strcpy_s( szStringBuilder2 + nLth + nIndent, zsizeof( szStringBuilder2 ) - (nLth + nIndent), szVarName + k );
                     if ( lReturnParmType[ nIdx ] == qTSTRING )
                        strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), " = sb_" );
                     else
                     if ( lReturnParmType[ nIdx ] == qTDECIMAL )
                        strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), " = md_" );
                     else
                        strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), " = mi_" );

                     strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), szVarName + k );
                     if ( lReturnParmType[ nIdx ] == qTSTRING )
                        strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), ".toString( )" );
                     else
                     if ( lReturnParmType[ nIdx ] == qTDECIMAL )
                        strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), ".doubleValue( )" );
                     else
                        strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), ".intValue( )" );

                     nLth = (zSHORT) zstrlen( szStringBuilder2 );
                     nIdx++;
                     break;

                  }  // end of purist's goto
               }

               if ( nReturnParmCnt > 0 )  // we have to check since nReturnParmCnt could have been set to zero in the loop
               {
                  szStringBuilder2[ nLth++ ] = ';';
                  szStringBuilder2[ nLth++ ] = '}';
                  szStringBuilder2[ nLth ] = 0;
                  if ( g_pchOutputExprStr[ nOutputIdx + 1 ] == ';' )
                     nOutputIdx -= nLth - 1;
                  else
                     nOutputIdx -= nLth;

                  zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szStringBuilder2, nLth );
               }
            }

            // Normally would use else here, but nReturnParmCnt could have been set to zero in the loop.
            if ( /* nReturnCodeIdx >= 0 && */ nReturnParmCnt == 0 && nReturnVarIdx >= 0 && nReturnCodeIdx != nReturnVarIdx )
            {
               nExprIdx = nReturnCodeIdx;
               psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
               psExpr->lFlags |= SKIP_BIT;  // remove return code from the list of structures
            }

 #if 0  // this is no longer true with the RESULT implementation
            nOutputIdx = AddExprEntryToString( vSubtask, psExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );

            zCHAR  szJavaRC[ ] = " = GetJOE_ReturnCode( )";

            nLth = zsizeof( szJavaRC ) + 1;

            nOutputIdx = VM_MAX_STRING_SIZE - nLth;
            strcpy_s( g_pchOutputExprStr + nOutputIdx + 1, szJavaRC );

            nOutputIdx -= nIndent;
            zmemset( g_pchOutputExprStr + nOutputIdx, ' ', nIndent );

            g_pchOutputExprStr[ nOutputIdx-- ] = '\n';
            g_pchOutputExprStr[ nOutputIdx-- ] = ';';
#endif
         }
      }

#ifdef DEBUG_PARSEGEN
      // Beginning of REVISED trace for Expression
      TraceLineS( "Trace REVISED Expression List", "" );
      nExprIdx = nHoldExprIdx;

      while ( nExprIdx >= 0 )
      {
         psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);

         if ( psExpr->lElementClass == qOPERATIONCALL )
         {
            if ( psExpr->lOffset > MAXSTRING )
            {
               GetOperationNameFromZKey( vSubtask, szOperationName, zsizeof( szOperationName ), szHeaderName, zsizeof( szHeaderName ),
                                         szThrowsException, zsizeof( szThrowsException ), szThrowsExceptionCatchCode, zsizeof( szThrowsExceptionCatchCode ),
                                         szOperationGroup, zsizeof( szOperationGroup ), psExpr->lDataClass, psExpr->lOffset );
            }
            else
            {
               strcpy_s( szOperationName, zsizeof( szOperationName ), szExprText + psExpr->lOffset );
            }
         }
         else
            szOperationName[ 0 ] = 0;

         TraceExpressionStruct( psExpr, nExprIdx, (psExpr->lOffset <= (zLONG) ulCodeIdx) ? szExprText + psExpr->lOffset : "", szOperationName );  // display this expression structure
         nExprIdx -= (sizeof( sQExprStruct ) - MAXSTRING);
      }
      // End of REVISED trace for Expression

      TraceLineS( "", "" );
#endif
      nExprIdx = nHoldExprIdx;
   }
   else
   {
#ifdef DEBUG_PARSEGEN
      zBOOL  bOperFound = FALSE;

      for ( k = 0; k < 2; k++ )
      {
         if ( k == 1 )
            if ( bOperFound )
               TraceLineS( "Trace C Expression List", "" );
            else
               break;  // nothing to trace

         nExprIdx = nHoldExprIdx;
         while ( nExprIdx >= 0 )
         {
            psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);

            if ( psExpr->lElementClass == qOPERATIONCALL )
            {
               if ( psExpr->lOffset > MAXSTRING )
               {
                  GetOperationNameFromZKey( vSubtask, szOperationName, zsizeof( szOperationName ), szHeaderName, zsizeof( szHeaderName ),
                                            szThrowsException, zsizeof( szThrowsException ), szThrowsExceptionCatchCode, zsizeof( szThrowsExceptionCatchCode ),
                                            szOperationGroup, zsizeof( szOperationGroup ), psExpr->lDataClass, psExpr->lOffset );
               }
               else
               {
                  strcpy_s( szOperationName, zsizeof( szOperationName ), szExprText + psExpr->lOffset );
               }

               if ( zstrcmp( szOperationName, "SetCursorNextEntityHierarchical" ) == 0 )
                  bOperFound = TRUE;
            }
            else
               szOperationName[ 0 ] = 0;


            if ( k == 1 )
               TraceExpressionStruct( psExpr, nExprIdx, (psExpr->lOffset <= (zLONG) ulCodeIdx) ? szExprText + psExpr->lOffset : "", szOperationName );  // display this expression structure

            nExprIdx -= (sizeof( sQExprStruct ) - MAXSTRING);
         }
         // End of REVISED trace for Expression

         if ( k == 1 )
            TraceLineS( "", "" );
      }

      nExprIdx = nHoldExprIdx;
      szOperationName[ 0 ] = 0;
#endif
   }

   nEqual = 0;
   bFunctionProcessed = FALSE;

   // While there are ExprStruct entries to process ...
   while ( nExprIdx >= 0 )
   {
      // Localize the expression record out of the szExprCode blob ... not sure we need to since
      // we could just run through the structures using a pointer (dks 2009.10.01)
      zmemcpy( &sCurrExpr, szExprCode + nExprIdx, sizeof( sQExprStruct ) - MAXSTRING );
      if ( (sCurrExpr.lFlags & SKIP_BIT) == 0 )
      {
         if ( sCurrExpr.lElementClass )  // if the Expression structure retrieved is a value
         {
            // If the WorkExpr contains an operator, add it to the infix (push the "index into expression" onto the values stack).
            if ( sCurrExpr.lElementClass == qOPERATOR ) // 1034
            {
               if ( sCurrExpr.lOffset == qLPAREN    ||  // 3014
                    sCurrExpr.lOffset == qRPAREN    ||  // 3015
                    sCurrExpr.lOffset == qOPENOPER  ||  // 3018
                    sCurrExpr.lOffset == qCLOSEOPER ||  // 3019
                    sCurrExpr.lOffset == qCOMMA     ||  // 3013
                    sCurrExpr.lOffset == qPERIOD )      // 3024
                 // Following statements for AND/OR removed by DonC 6/1/96
                 // sCurrExpr.lOffset == qAND       ||
                 // sCurrExpr.lOffset == qOR )
               {
                  if ( sCurrExpr.lOffset == qPERIOD && g_pchOutputExprStr[ nOutputIdx + 1 ] == ' ' )
                     nOutputIdx++; // eliminate space after period

                  nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );

                  if ( sCurrExpr.lOffset != qOPENOPER && sCurrExpr.lOffset != qCOMMA && sCurrExpr.lOffset != qPERIOD )
                  {
                     g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                  }

                  switch ( sCurrExpr.lOffset )
                  {
                     case qLPAREN:

                        // Copy operator from stack to output.
                        bUnaryContinue = TRUE;
                        while ( bUnaryContinue && (nTopOfStack = POP) > 0 )
                        {
                           // Get the expression record out of szExprCode.
                           zmemcpy( &sCurrExpr, szExprCode + nTopOfStack, sizeof( sQExprStruct ) - MAXSTRING);

                           if ( sCurrExpr.lElementClass != qOPERATOR || // 1034
                                sCurrExpr.lOffset != qUNARYMINUS ) // 3032
                           {
                              bUnaryContinue = FALSE;
                           }

                           nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                        }

                        break;

                     case qRPAREN:
                        PUSH( (zSHORT) (-1 * sCurrExpr.lOffset) );  // push as "applied" (< 0)
                        break;

                     case qCOMMA:
                        PUSH( (zSHORT) (-1 * sCurrExpr.lOffset) );  // push as "applied" (< 0)

                        // DM - Currently we are using the presence of a comma to indicate the presence of a function call in an expression.  Although C allows for
                        // commas inside for loop statements, I am assuming that no such for loop will be generated.
                        bFunctionInString = TRUE;

                        break;

                     case qOPENOPER:
                        nTopOfStack = POP;
                        g_nInParmList = 0;

                        if ( nTopOfStack >= 0 )
                           PUSH( nTopOfStack );
                        else
                        if ( nTopOfStack <= -1000 && (nTopOfStack * -1) != qCLOSEOPER )
                           PUSH( nTopOfStack );

                        // Turn off the flag to indicate that we are no longer "in" an operation call (processing operation arguments).
                        lFlag &= ~zOPERATION_ARGUMENTS;

                        break;

                     case qCLOSEOPER:
                        g_nInParmList = 1;
                        PUSH( (zSHORT) (-1 * sCurrExpr.lOffset) );  // push as "applied" (< 0)

                        // Set flag indicating that we are "in" an operation call (i.e. current expressions are operation arguments).
                        lFlag |= zOPERATION_ARGUMENTS;

                        break;

                  } // switch ...
               }
               else
               {
                  if ( bDirectOutput )
                  {
                     nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                     g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                  }
                  else
                  {
                     // Note that for example, qEQUAL is 3001, qADDITION is 3003, qAND is 1051, qOR is 1052 ... so their indices get pushed here.
                     PUSH( nExprIdx );
                  }
               }
            }
            else
            {
               // The Expression structure retrieved is a variable or constant (not an operator), so we are copying it to the output string (backwards, starting at the end).
               if ( sCurrExpr.lElementClass == qVARIABLE           ||  // 1044
                    sCurrExpr.lElementClass == qDEFINE             ||  // 1060
                    sCurrExpr.lElementClass == qCONSTANT           ||  // 1010
                    sCurrExpr.lElementClass == qATTRIBUTEQUALIFIER ||  // 2001
                    sCurrExpr.lElementClass == qOPERATIONCALL )        // 2008
               {
                  // Output the value.
                  if ( (sCurrExpr.lFlags & TESTVIEW_BIT) != 0 )
                  {
                     if ( sCurrExpr.lElementClass == qCONSTANT )
                     {
                        if ( zstrcmp( szExprText + sCurrExpr.lOffset, "0" ) == 0 )
                        {
                           if ( g_szGenLang[ 0 ] == 'J' )
                           {
                              nOutputIdx -= 3;
                              zmemcpy( g_pchOutputExprStr + nOutputIdx, "null", 4 );
                              nOutputIdx--;
                           }
                        }
                     }
                  }
                  else
                  {
                     if ( g_szGenLang[ 0 ] == 'J' && nExprIdx == 0 && (nTopOfStack = POP) > 0 )
                     {
                        // Point to the expression record in szExprCode.
                        psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nTopOfStack);
                        if ( psExpr->lElementClass == qOPERATOR && psExpr->lOffset == qEQUAL )
                        {
                           psExpr->lFlags |= SKIP_BIT;
                           nOutputIdx = AddExprEntryToString( vSubtask, psExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                        }
                        else
                        {
                           PUSH( nTopOfStack );
                        }
                     }

                     if ( bTestCondition && g_szGenLang[ 0 ] == 'J' && sCurrExpr.lDataType == qTVIEW )
                     {
                        zSHORT re = -1;
                        zSHORT rn = -1;

                        if ( (re = zstrcmp( g_pchOutputExprStr + nOutputIdx + 1, " == null )" )) == 0 ||
                             (rn = zstrcmp( g_pchOutputExprStr + nOutputIdx + 1, " != null )" )) == 0 )
                        {
#if 0
                           // Generate: view != null && view.getView != null
                           g_pchOutputExprStr[ nOutputIdx-- ] = ')';
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                           g_pchOutputExprStr[ nOutputIdx-- ] = '(';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'w';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'e';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'i';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'V';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 't';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'e';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'g';
                           g_pchOutputExprStr[ nOutputIdx-- ] = '.';
                           nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                           if ( re == 0 )
                           {
                              g_pchOutputExprStr[ nOutputIdx-- ] = '|';
                              g_pchOutputExprStr[ nOutputIdx-- ] = '|';
                           }
                           else
                           {
                              g_pchOutputExprStr[ nOutputIdx-- ] = '&';
                              g_pchOutputExprStr[ nOutputIdx-- ] = '&';
                           }

                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'l';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'l';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'u';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'n';
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                           g_pchOutputExprStr[ nOutputIdx-- ] = '=';
                           if ( re == 0 )
                              g_pchOutputExprStr[ nOutputIdx-- ] = '=';
                           else
                              g_pchOutputExprStr[ nOutputIdx-- ] = '!';

                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                           nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
#else
                           // Generate: getView( view ) != null
                           g_pchOutputExprStr[ nOutputIdx-- ] = ')';
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                           nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                           g_pchOutputExprStr[ nOutputIdx-- ] = '(';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'w';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'e';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'i';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'V';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 't';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'e';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'g';
#endif
                        }
                        else
                        {
                           nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                        }

                     }
                     else
                     {
                        nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                     }

                     if ( g_szGenLang[ 0 ] == 'J' && sCurrExpr.lDataType == qTVIEW &&
                          g_pchOutputExprStr[ nOutputIdx + 1 ] == '0' &&
                          (g_pchOutputExprStr[ nOutputIdx + 2 ] == ' ' || g_pchOutputExprStr[ nOutputIdx + 2 ] == ',') )
                     {
                        nOutputIdx++;
                        g_pchOutputExprStr[ nOutputIdx-- ] = 'l';
                        g_pchOutputExprStr[ nOutputIdx-- ] = 'l';
                        g_pchOutputExprStr[ nOutputIdx-- ] = 'u';
                        g_pchOutputExprStr[ nOutputIdx-- ] = 'n';
                     }

                     if ( nReturnParmCnt > 0 && szPFlag[ 0 ] != 'Y' )
                     {
                        for ( k = 0; k < nReturnParmCnt; k++ )
                        {
                           if ( nExprIdx == nReturnParmIdx[ k ] )
                           {
                              g_pchOutputExprStr[ nOutputIdx-- ] = '_';
                              if ( sCurrExpr.lDataType == qTSTRING )
                              {
                                 g_pchOutputExprStr[ nOutputIdx-- ] = 'b';
                                 g_pchOutputExprStr[ nOutputIdx-- ] = 's';
                              }
                              else
                              if ( sCurrExpr.lDataType == qTDECIMAL )
                              {
                                 g_pchOutputExprStr[ nOutputIdx-- ] = 'd';
                                 g_pchOutputExprStr[ nOutputIdx-- ] = 'm';
                              }
                              else
                              {
                                 g_pchOutputExprStr[ nOutputIdx-- ] = 'i';
                                 g_pchOutputExprStr[ nOutputIdx-- ] = 'm';
                              }

                              break;  // out of inner for
                           }
                        }
                     }
                  }

                  // If we are generating a return statement containing a decimal constant, a (ZDecimal) cast must be generated.
                  if ( bReturn && sCurrExpr.lElementClass == qCONSTANT && sCurrExpr.lDataType == qTDECIMAL )
                  {
                     if ( g_szGenLang[ 0 ] == 'J' )
                     {
                        nOutputIdx -= 9;
                        memcpy( g_pchOutputExprStr + nOutputIdx + 1, "(double) ", 9 );
                     }
                     else
                     {
                        nOutputIdx -= 11;
                        memcpy( g_pchOutputExprStr + nOutputIdx + 1, "(ZDecimal) ", 11 );
                     }
                  }

               /* if ( sCurrExpr.lElementClass == qOPERATIONCALL && g_szGenLang[ 0 ] == 'X' && nQualViewIdx >= 0 ) // was looking for 'J', but trying to disable dks 2010.03.12
                  {
                     g_pchOutputExprStr[ nOutputIdx-- ] = '.';

                     psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nQualViewIdx);
                     nOutputIdx = AddExprEntryToString( vSubtask, psExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                  } */

                  if ( sCurrExpr.lElementClass == qOPERATIONCALL && g_szGenLang[ 0 ] == 'J' )
                  {
                     if ( szHeaderName[ 0 ] )
                     {
                        bFunctionProcessed = TRUE;

                        nLth = (zSHORT) zstrlen( szHeaderName );
                        g_pchOutputExprStr[ nOutputIdx-- ] = '.';
                        nOutputIdx -= nLth;
                        zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szHeaderName, nLth );
                        g_pchOutputExprStr[ nOutputIdx-- ] = '_';
                        g_pchOutputExprStr[ nOutputIdx-- ] = 'm';
                     }

                     if ( nStackIdx <= 0 &&
                          ((nReturnVarIdx >= 0 || nReturnParmCnt > 0) && (nReturnCodeIdx < 0 || nReturnCodeIdx == nReturnVarIdx)) )
                     {
                        nHoldExprIdx = nExprIdx;
                        while ( nExprIdx > 0 )
                        {
                           nExprIdx -= (sizeof( sQExprStruct ) - MAXSTRING);
                           psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
                           if ( sCurrExpr.lElementClass != 0 && (sCurrExpr.lFlags & SKIP_BIT) == 0 )
                              break;
                        }

                        if ( nExprIdx == 0 )
                        {
                           if ( nReturnParmCnt <= 0 )
                           {
                              // We need to add the return variable for Java at this point since it won't be done in normal processing.
                              g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                              g_pchOutputExprStr[ nOutputIdx-- ] = '=';
                              g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                              psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nReturnVarIdx);
                              nOutputIdx = AddExprEntryToString( vSubtask, psExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, 0 );
                           }
                           else
                           {
                              nOutputIdx -= nIndent;
                              zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent );
                              nLth = (zSHORT) zstrlen( szStringBuilder1 );
                              nOutputIdx -= nLth;
                              zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szStringBuilder1, nLth );
                           }

                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                        }

                        nExprIdx = nHoldExprIdx;
                     }
                  }

                  g_pchOutputExprStr[ nOutputIdx-- ] = ' ';

                  // Copy operator from stack to output.
                  bUnaryContinue = TRUE;
                  while ( bUnaryContinue && (nTopOfStack = POP) > 0 )
                  {
                     // Get the expression record out of szExprCode.
                     zmemcpy( &sCurrExpr, szExprCode + nTopOfStack, sizeof( sQExprStruct ) - MAXSTRING);

                     if ( sCurrExpr.lElementClass != qOPERATOR || // 1034
                          sCurrExpr.lOffset != qUNARYMINUS ) // 3032
                     {
                        bUnaryContinue = FALSE;
                     }

                     if ( sCurrExpr.lElementClass == qOPERATOR && sCurrExpr.lOffset == qEQUAL )
                        nEqual = 1;

                     if ( nEqual == 0 || bOperation == FALSE || (nReturnVarIdx >= 0 && nReturnParmCnt <= 0) ||
                          (nReturnVarIdx >= 0 && nReturnParmCnt > 0 && nReturnCodeIdx >= 0) )
                     {
                        if ( nEqual > 0 && lLeftVarType >= 0 && lRightVarType >= 0 &&
                             (lLeftVarType == qTSHORT || lLeftVarType == qTINTEGER) && lRightVarType== qTDECIMAL )
                        {
                           g_pchOutputExprStr[ nOutputIdx-- ] = ')';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 't';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'n';
                           g_pchOutputExprStr[ nOutputIdx-- ] = 'i';
                           g_pchOutputExprStr[ nOutputIdx-- ] = '(';
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                        }

                        // Need more information for Java.
                        if ( g_szGenLang[ 0 ] == 'J' && nExprIdx - (sizeof( sQExprStruct ) - MAXSTRING) == 0 && bOperation == FALSE )
                        {
                           psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + 0);
                           szStringBuilder2[ zsizeof( szStringBuilder2 ) - 1 ] = 0;
                           k = AddExprEntryToString( vSubtask, psExpr, szStringBuilder2, szPFlag, zsizeof( szPFlag ), zsizeof( szStringBuilder2 ) - 2, szExprText, 0 ); // get return variable
                           if ( (psExpr->lDataType == qTINTEGER || psExpr->lDataType == qTSHORT) && szPFlag[ 0 ] == 'Y' )  // 1040 || 1041
                           {
                              strcpy_s( szStringBuilder2, zsizeof( szStringBuilder2 ), szStringBuilder2 + k + 1 );
                              k = (zSHORT) zstrlen( g_pchOutputExprStr + nOutputIdx + 1 );
                              if ( k < zsizeof( szStringBuilder2 ) - 36 )
                              {
                                 strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), ".setValue(" );
                                 strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), g_pchOutputExprStr + nOutputIdx + 1 );
                                 strcat_s( szStringBuilder2, zsizeof( szStringBuilder2 ), " )" );
                                 nOutputIdx -= (zSHORT) zstrlen( szStringBuilder2 ) - k; // for the setValue and parens
                                 strcpy_s( g_pchOutputExprStr + nOutputIdx + 1, VM_MAX_STRING_SIZE - (nOutputIdx + 1), szStringBuilder2 );
                                 nExprIdx = 0;
                                 g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                                 break;
                              }
                           }
                        }

                        // Add the equal sign.
                        nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                        g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                     }

                     if ( nEqual > 0 )
                     {
                        if ( nReturnVarIdx >= 0 && nReturnParmCnt <= 0  )
                        {
                           psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nReturnVarIdx);
                           nOutputIdx = AddExprEntryToString( vSubtask, psExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                        }
                        else
                        if ( nReturnCodeIdx >= 0 )
                        {
                           psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nReturnCodeIdx);
                           nOutputIdx = AddExprEntryToString( vSubtask, psExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
                           g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                        }

                        nEqual = -1;
                        if ( g_szGenLang[ 0 ] == 'J' ) // was looking for 'J', but trying to disable dks 2010.03.12
                        {
                           if ( nReturnVarIdx >= 0 )
                           {
                              nExprIdx = 0;  // we really want to get out of the outer while
                              if ( nReturnParmCnt > 0 )
                              {
                                 nOutputIdx -= nIndent;
                                 zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent );
                                 nLth = (zSHORT) zstrlen( szStringBuilder1 );
                                 nOutputIdx -= nLth;
                                 zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szStringBuilder1, nLth );
                                 g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
                              }
                           }
                        // else
                        //    nExprIdx -= (sizeof( sQExprStruct ) - MAXSTRING);
                        }

                        break;
                     }
                  }
               }
               else
               {
                  // This should never happen!!!
                  psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
                  TraceExpressionStruct( psExpr, nExprIdx, (psExpr->lOffset <= (zLONG) ulCodeIdx) ? szExprText + psExpr->lOffset : "", "" );
                  SysMessageBox( vSubtask, "DKS", "Unexpected expression structure", 0 );
               }
            }
         }
      }

#ifdef DEBUG_PARSEGEN
      psExpr = (sQExprStruct *) ((zPCHAR) szExprCode + nExprIdx);
      TraceExpressionStruct( psExpr, nExprIdx, "  OutputX: ", g_pchOutputExprStr + nOutputIdx + 1 );  // display this expression structure
      if ( zstrstr( g_pchOutputExprStr + nOutputIdx + 1, "\"Marketing" ) != 0 )
         TraceLineS( "", "" );
#endif
      // Here we decrement nExprIdx to point to the previous entry of an ExprStruct.
      nExprIdx -= (sizeof( sQExprStruct ) - MAXSTRING);
   }

   while ( nStackIdx > 0 )
   {
      nTopOfStack = POP;
      if ( nTopOfStack > 0 )
      {
         // Get the expression record out of szExprCode.
         zmemcpy( &sCurrExpr, szExprCode + nTopOfStack, sizeof( sQExprStruct ) - MAXSTRING);
         nOutputIdx = AddExprEntryToString( vSubtask, &sCurrExpr, g_pchOutputExprStr, szPFlag, zsizeof( szPFlag ), nOutputIdx, szExprText, lFlag );
         g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
      }
   }

   if ( bOperation )
   {
      if ( szNewOperationClassStatement[ 0 ] )
      {
         nLth = (zSHORT) zstrlen( szNewOperationClassStatement );
         nOutputIdx -= nLth;
         zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, szNewOperationClassStatement, nLth );
         g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
       szNewOperationClassStatement[ 0 ] = 0;
      }

      if ( szThrowsException[ 0 ] == 'Y' )
      {
         nOutputIdx -= nIndent + 3;
         zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent + 3 );
         nOutputIdx -= 2;
         zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, "{\n", 2 );
         nOutputIdx -= nIndent;
         zmemset( g_pchOutputExprStr + nOutputIdx + 1, ' ', nIndent );
         nOutputIdx -= 4;
         zmemcpy( g_pchOutputExprStr + nOutputIdx + 1, "try\n", 4 );
      // g_pchOutputExprStr[ nOutputIdx + 4 + 1 ] = ' '; // reset the blank that was obliterated
         g_pchOutputExprStr[ nOutputIdx-- ] = ' ';
      }
   }

   nOutputIdx++;

   if ( bReturn && g_szGenLang[ 0 ] == 'J' )
   {
      strcpy_s( szStringBuilder1, zsizeof( szStringBuilder1 ), pchOutputString + nIndent );
      strcpy_s( pchOutputString + nIndent, VM_MAX_STRING_SIZE - nIndent, "if(8==8)" );
      strcat_s( pchOutputString, VM_MAX_STRING_SIZE, szStringBuilder1 );
      if ( (pch = zstrstr( szStringBuilder1, "( " )) != 0 && zstrstr( pch + 2, " )" ) != 0 )
      {
         strcpy_s( pch, zsizeof( szStringBuilder1 ) - (pch - szStringBuilder1), pch + 1 );
         pch = zstrstr( pch + 2, " )" );
         strcpy_s( pch, zsizeof( szStringBuilder1 ) - (pch - szStringBuilder1), pch + 2 );
      }
   }

   strcat_s( pchOutputString, VM_MAX_STRING_SIZE, g_pchOutputExprStr + nOutputIdx + 1 );

   if ( g_szGenLang[ 0 ] == 'J' )
   {
      if ( (pch = zstrstr( pchOutputString, " > null" )) != 0 || (pch = zstrstr( pchOutputString, " < null" )) != 0 )
      {
         if ( zstrlen( pch + 2 ) < zsizeof( szStringBuilder1 ) )
         {
            strcpy_s( szStringBuilder1, zsizeof( szStringBuilder1 ), pch + 2 );
            pch++;
            *pch = '!';
            pch++;
            *pch = '=';
            strcpy_s( pch + 1, VM_MAX_STRING_SIZE - (pch - pchOutputString) - 1, szStringBuilder1 );
         }
      }

      if ( bDouble )
      {
         if ( (pch = zstrstr( pchOutputString, "doubleValue( ) = " )) != 0 )
         {
            zmemcpy( pch, "setValue( ", 10 );
            strcpy_s( pch + 10, VM_MAX_STRING_SIZE - (pch - pchOutputString) - 10, pch + 17 );
            strcat_s( pch, VM_MAX_STRING_SIZE - (pch - pchOutputString), " )" );
         }
      }

     // KJS 08/29/12 - I realize this would not be the "correct" place to change this but I am going to just see what happens...
     // DG is now returning an object from set cursor methods so RESULT is not correct if we are to keep the view.cursor("Entity").setFirst...
     // format.  I changed these back to SetCursorFirstEntity etc. when generating java. So I am commenting this out...
     /*
      if ( (pch = zstrstr( pchOutputString, "RESULT >= zCURSOR_SET" )) != 0 )
      //if ( (pch = zstrstr( pchOutputString, "RESULT > zCURSOR_UNCHANGED" )) != 0 )
      {
         zmemcpy( pch, "cr.isSet()", 10 );
         strcpy_s( pch + 10, pch + 21 );
         //zstrcat( pch, " )" );
      }
     */

   }

   if ( bFunctionInString && nReturnParmCnt <= 0 && szThrowsException[ 0 ] != 'Y' && szOperationGroup[ 0 ] == 0 )
      FormatString( pchOutputString );

EXPRESSION_EXIT_label:

   if ( (pch = zstrstr( pchOutputString, "};}" )) != 0 )
      strcpy_s( pch + 1, VM_MAX_STRING_SIZE - (pch - pchOutputString) - 1, pch + 2 );

   if ( (pch = zstrstr( pchOutputString, ".setNextContinue( \"" )) != 0 )
   {
      zPCHAR  pch2 = zstrchr( pch + 18, ')' );
      if ( pch2 )
         strcpy_s( pch + 18, VM_MAX_STRING_SIZE - (pch - pchOutputString) - 18, pch2 );  // eliminate any and all parms on setNextContinue
   }

// if ( (pch = zstrstr( pchOutputString, ".setNextContinue( \"" )) != 0 ) // debugging only
//    TraceLineS( "setNextContinue: ", pchOutputString );

#ifdef DEBUG_PARSEGEN
   TraceLineS( pchOutputString, "" );
   TraceLineS( "", "" );  // end of trace for Expression
#endif
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
// >>>paired_overwrite
//
// overwrite contents of string within paired characters
// example:
// given the string  str = abc"qwertz"uiop
// paired_overwrite( str, "\"", 'x' ) would give us
// str = abc"xxxxxx"uiop
//
/////////////////////////////////////////////////////////////////////////////
static void
paired_overwrite( zPCHAR pchString, zCHAR cPair, zCHAR cOverWrite )
{
   zPCHAR pch;
   zBOOL  bInside = FALSE;

   for ( pch = pchString; *pch; pch++ )
   {
      if ( bInside )
      {
         if ( *pch == cPair )
         {
            bInside = FALSE;
            *pch = cOverWrite;
         }
         else
         if ( *pch == '\\' && *(pch + 1) == '\\' )
         {
            // we must be careful because of "\\"
            *(pch + 1) = *pch = cOverWrite;
            pch++;
         }
         else
         if ( *pch == '\\' && *(pch + 1) == cPair )
         {
            // we have to be aware that there might be an escape sign
            *(pch + 1) = *pch = cOverWrite;
            pch++;
         }
         else
            *pch = cOverWrite;
      }
      else
      {
         if ( *pch == cPair )
         {
            bInside = TRUE;
            *pch = cOverWrite;
         }
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
//
// LOCALOPER: FormatString
//
// DESCRIPTION: This routine is called to format generated c strings that
// contains function calls.
//
// HH:
// The old concept was not ok, I got a string with lots of function calls
// and the output was awful.
//
// The new concept is simpler:
//    Keep an outputline < 254;
//    Insert a line break if possible at a comma, or blank or ...;
//    Make sure, that no break is inserted within ".." or '..'
//    If no good insert position is found (e.g. because of long "strings"),
//       then insert a backslash and don't indent next line. <== This stinks,
//       so changed to more reasonable method ... dks 2009.08.23
//
/////////////////////////////////////////////////////////////////////////////
zVOID
FormatString( zPCHAR pchOutputString )
{
   zPCHAR  pch;
   zPCHAR  pch1;
   zCHAR   szTemp[ 12000 ];
   zSHORT  nMargin = 0;    // size of left margin
// zSHORT k;

   if ( zstrlen( pchOutputString ) < 254 )
      return;

   // Look for the first non-blank in the line.  This position (+3) will define nMargin.
   pch = pchOutputString;
   pch += strspn( pch, " " );
   nMargin = pch - pchOutputString + 3;

   // But we don't want more than a 24 byte margin.
   if ( nMargin > 24 )
      nMargin = 24;

// pch1 = strchr( pch + nMargin, '(' );  // was this, but not great since it forces the next line to have a big margin  dks 2009.10.29
   pch1 = strchr( pch, '(' );
   if ( pch1 )
   {
      nMargin = pch1 - pchOutputString + 2;
      if ( nMargin > 24 )
         nMargin = 24;
   }

   // Loop until there are no more lines in pchOutputString left to process.
   pch = pchOutputString;
   for( ;; )
   {
      // advance to next line break
      pch1 = strchr( pch, '\n' );
      if ( pch1 )
         pch = pch1 + 1;

      if ( zstrlen( pch ) <= 254 )
         break;  // ok, done

      // Now look for a position where a line break can be inserted.  First, change everything inside quotes or apostrophes to 'xff' so we
      // don't find our special break characters within quotes or apostrophes.
      strcpy_s( szTemp, zsizeof( szTemp ), pch ); // create temporary copy for changing everything inside "" and ''.
      paired_overwrite( szTemp, '\"', '\xff'); // change everything inside quotes to 'xff'
      paired_overwrite( szTemp, '\'', '\xff'); // change everything inside apostrophes to 'xff'

      // Now go back from ctemp + 254 and look for a break position.
      // first choice:
      //  - after an operator &&, ||
      //
      // second choice:
      //  - after a comma
      //  - after '=', arithm. operator
      //
      // third choice
      //  - after any blank
      //
      // otherwise
      //  - anywhere, with backslash

      for ( pch1 = szTemp + 253; pch1 > szTemp + nMargin; pch1-- )
      {
         if ( *pch1 != '&' && *(pch1 - 1) == '&' && *(pch1 - 2) == '&' )
            break; // after '&&'

         if ( *pch1 != '|' && *(pch1 - 1) == '|' && *(pch1 - 2) == '|' )
            break; // after '||'
      }

      if ( pch1 <= szTemp + nMargin )
      {
         // No first choice insert position found.
         for ( pch1 = szTemp + 253; pch1 > szTemp + nMargin; pch1-- )
         {
            if ( *(pch1 - 1) == ',' )
               break; // after Comma

            if ( *pch1 != '=' && *(pch1 - 1) == '=' )
               break; // after '=' or '==' or '!='

            if ( *pch1 != '+' && *(pch1 - 1) == '+' && *(pch1 - 2) != '+' )
               break; // after '+' but not '++'

            if ( *pch1 != '-' && *(pch1 - 1) == '-' && *(pch1 - 2) != '-' )
               break; // after '-' but not '--'

            if ( *(pch1 - 1) == '*' )
               break; // after '*'

            if ( *(pch1 - 1) == '/' )
               break; // after '/'

            if ( *(pch1 - 1) == ')' )
               break; // after ')'

            if ( *(pch1 - 1) == '(' )
               break; // after '('
         }
      }

      if ( pch1 <= szTemp + nMargin )
      {
         // No first or second choice insert position found, so take any blank.
         for ( pch1 = szTemp + 253; pch1 > szTemp + nMargin; pch1-- )
         {
            if ( *pch1 == ' ' )
               break; // after Blank
         }
      }

      if ( pch1 <= szTemp + nMargin )
      {
         if ( *pch1 == '\xff' && pch[ nMargin ] == '"' ) // looking at a quoted string
         {
            pch1 = pch + 253;
            if ( *pch1 == '\xff' && *(pch1 + 1) == '\xff' )
               InsertLineBreak( pchOutputString, pch1, nMargin, szTemp, TRUE );
            else
            {
               if ( *pch1 == '\xff' && (*(pch1 + 1) == ',' || *(pch1 + 1) == ' ') )
               {
                  pch1 += 2;
                  InsertLineBreak( pchOutputString, pch1, nMargin, szTemp, FALSE );
               }
               else
               {
                  pch1 -= 1;
                  InsertLineBreak( pchOutputString, pch1, nMargin, szTemp, TRUE );
               }
            }
         }
         else
         {
            zSHORT n255 = 0;

            // We could not find a good insert position so we do it with a backslash (no indentation on following line).
            // Count the xff's following szTemp + 253.  If we are in a very long string, we continue backslash processing until the whole quoted string is done.

#if 1
            while ( szTemp[ 253 + n255 ] == '\xff' )
               n255++;

            strcpy_s( szTemp, zsizeof( szTemp ), pch + 253 );
            *(pch + 253) = '\\';
            *(pch + 254) = '\n';
            strcpy_s( pch + 255, pch - pchOutputString - 255, szTemp );
            pch = pch + 255;

            while ( n255 > 254 )
            {
               strcpy_s( szTemp, zsizeof( szTemp ), pch + 253 );
               *(pch + 253) = '\\';
               *(pch + 254) = '\n';
               strcpy_s( pch + 255, pch - pchOutputString - 255, szTemp );
               pch = pch + 255;
               n255 = n255 - 253;
            }
#else
            while ( szTemp[ 253 + n255 ] == '\xff' )
               n255++;

            strcpy_s( szTemp, zsizeof( szTemp ), pch + 253 );
            *(pch + 253) = '"';
            for ( k = 0; k <= nMargin; k++ )
               pch[ 254 + k ] = ' ';

            *(pch + k + 254) = '"';

            strcpy_s( pch + 255 + k, szTemp );
            pch = pch + 255;

            while ( n255 > 254 )
            {
               strcpy_s( szTemp, zsizeof( szTemp ), pch + 253 );
               *(pch + 253) = '"';
               *(pch + 254) = '"';

               strcpy_s( pch + 255, szTemp );
               pch = pch + 255;
               n255 = n255 - 253;
         }
#endif
            if ( n255 > 0 )
            {
               pch = pch + n255;
               InsertLineBreak( pchOutputString, pch, nMargin, szTemp, FALSE );
            }
         }
      }
      else
      {
         pch1 = pch + (pch1 - szTemp);
         InsertLineBreak( pchOutputString, pch1, nMargin, szTemp, FALSE );
      }
   }
} // End of: FormatString

/////////////////////////////////////////////////////////////////////////////
//
// LOCALOPER: InsertLineBreak
//
// DESCRIPTION: This routine will add a new line character in pchOutputString
// at position nInsertPosition and will pad out the next line in pchOutputString
// so that it starts at nMargin.
//
/////////////////////////////////////////////////////////////////////////////
zVOID LOCALOPER
InsertLineBreak( zPCHAR pchOutputString,
                 zPCHAR pchInsertPosition,
                 zSHORT nMargin,
                 zPCHAR pchSource,
                 zBOOL  bQuotes )
{
   zSHORT i, j;
   zLONG lInsertPosition = pchInsertPosition - pchOutputString;
   strcpy_s( pchSource, 12000, pchOutputString );

   // Count the blanks, starting from insert position.
   i = (zSHORT) strspn( pchInsertPosition, " " );

   if ( bQuotes )
      *pchInsertPosition++ = '"';

   // Insert line break.
   *pchInsertPosition++ = '\n';

   // Insert padding.
   for ( j = 1; j <= nMargin - i; j++ )
   {
      *pchInsertPosition++ = ' ';
   }

   if ( bQuotes )
      *pchInsertPosition++ = '"';

   // Copy rest of line.
   strcpy_s( pchInsertPosition, VM_MAX_STRING_SIZE - (pchInsertPosition - pchOutputString), pchSource + lInsertPosition );

}  //End of: InsertLineBreak

/////////////////////////////////////////////////////////////////////////////
//
// LOCALOPER: StrConcatAndMassage
//
// DESCRIPTION: This routine will concat pchSource (a VML string) to
// pchTarget (a C string) and it will convert any VML special characters
// to their C equivalants. In particular, this routine will
// 1. convert \  (in VML) to \\ (in C)     for BACKSLASHES
// 2. convert "  (in VML) to \" (in C)     for DOUBLE QUOTES
// 3. convert |  (in VML) to \n (in C)     for NEW LINE CHARACTERS
// 4. convert || (in VML) to |  (in C)     for PIPE CHARACTERS.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT LOCALOPER
StrConcatAndMassage( zPCHAR pchTarget,
                     zPCHAR pchSource )
{
   // Loop to the end of pchTarget.
   while ( pchTarget[ 0 ] )
      pchTarget++;

   if ( strchr( pchSource, '|' ) )
      TraceLineS( "StrConcatAndMassage PIPE found: ", pchSource );

   // Do the concatenation and convertion.
   // The following loop is geeky C. Recall that an assignment in the form of a = b returns the
   // value of b. So, the boolean in the following while does the following things in this order:
   // a. first it copies the character at pchSource to pchTarget
   // b. if the character copied was a null terminator, then this is taken as false (recall,
   //    0 is false) and the loop ends.
   // c. if the character copies was not a null terminator, the body of the loop is executed
   //    and the necessary conversions are made.
   while ( *pchTarget = *pchSource )
   {
      if ( *pchTarget == '\\' )
      {
         // If we just copied a "\" add another one to give us "\\".
         pchTarget++;
         *pchTarget = '\\';
      }
      else
      if ( *pchTarget == '\"' )
      {
         // If we just copied a " replace it with a \".
         *pchTarget = '\\';
         pchTarget++;
         *pchTarget = '\"';
      }
      else
      if ( *pchTarget == '|' )
      {
         // If we just copied | ...
         if ( *(pchSource + 1) == '|' )
         {
            // If the | is followed by another | ...
            // convert the || in VML to a | in C by skipping the second | in C source.
            pchSource++;
         }
         else
         if ( *(pchSource + 1) == ' ' )
         {
            // Otherwise, we just copied a single |, so convert the single | to a \n.
            *pchTarget = '\\';
            pchTarget++;
            *pchTarget = 'n';
            pchSource++;
         }
      }

      // Increment loop.
      pchTarget++;
      pchSource++;
   }

   return( 0 );
}

zSHORT LOCALOPER
AddSizeofToOperation( zPCHAR pchOutputExprStr, zSHORT nOutputIdx, zSHORT nParmPosition )
{
   zCHAR  szVarSave[ MAXSTRING ];
   zSHORT nOrigIdx = nOutputIdx + 1;  // nOutputIdx points to the next spot to fill ... + 1 to point to last spot filled
   zPCHAR pchStart = pchOutputExprStr + nOrigIdx;
   zPCHAR pchOpenParen = zstrchr( pchStart, '(' ); // point to open paren

   if ( pchOpenParen ) // we for sure need an open paren
   {
      zPCHAR pchParm = pchOpenParen; // initialize pointer to parameter
      zPCHAR pchComma = pchParm;
      zBOOL  bComma = TRUE;

      while ( nParmPosition > 0 && pchComma )
      {
         nParmPosition--;
         pchParm = pchComma + 2;  // skip comma and space   ... point to parameter
         pchComma = zstrchr( pchParm, ',' );  // point to end of parameter
         if ( pchComma == 0 )
         {
            pchComma = zstrchr( pchParm, ')' );
            if ( pchComma )
            {
               pchComma--;
               bComma = FALSE;
            }
         }
      }

      if ( pchComma ) // everything is kosher up to this point ... apply the hack
      {
         zSHORT nLth = pchComma - pchParm;  // no null terminator

         strncpy_s( szVarSave, zsizeof( szVarSave ), pchParm, nLth ); // hold on to the variable name
      // nLth++;  // add for null terminator ... commented out since we do not null terminate

         if ( bComma )  // not the last parameter
         {
            // now back off nOutputIdx by the length of the variable + 13 bytes for the addition of "zsizeof( ), "
            nLth += 13;
            nOutputIdx -= nLth;
            pchComma += 2;
            zmemcpy( pchOutputExprStr + nOutputIdx + 1, pchStart, pchComma - pchStart );  // get the var + comma + space
            pchStart += (pchComma - pchStart) - nLth;  // start has been moved
            strcpy_s( pchStart, nLth, "zsizeof( " ); // shoehorn in ==> zsizeof( var ), ...
            strcat_s( pchStart, nLth, szVarSave );
            nLth = (zSHORT) zstrlen( pchStart );
            pchStart[ nLth++ ] = ' ';
            pchStart[ nLth++ ] = ')';
            pchStart[ nLth++ ] = ',';
            pchStart[ nLth++ ] = ' '; // ... and that should do it
         }
         else  // otherwise, we are looking at the last parameter, so a close-paren rather than a comma
         {
            // now back off nOutputIdx by the length of the variable + 13 bytes for the addition of ", zsizeof( )"
            nLth += 13;
            nOutputIdx -= nLth;
            zmemcpy( pchOutputExprStr + nOutputIdx + 1, pchStart, pchComma - pchStart );  // get the parameters up to where the comma will go
            pchStart += (pchComma - pchStart) - nLth;  // start has been moved
            strcpy_s( pchStart, nLth, ", zsizeof( " ); // shoehorn in ==> zsizeof( var ) ...
            strcat_s( pchStart, nLth, szVarSave );
            nLth = (zSHORT) zstrlen( pchStart );
            pchStart[ nLth++ ] = ' ';
            pchStart[ nLth++ ] = ')';  // ... and that should do it
         }
      }
   }

   return( nOutputIdx );
}

zSHORT LOCALOPER
AddExprEntryToString( zVIEW          vSubtask,
                      sQExprStruct   *psExpr,
                      zPCHAR         pchOutputExprStr,
                      zPCHAR         pchPFlag,
                      zLONG          lFlagLth,
                      zSHORT         nOutputIdx,
                      zPCHAR         pchExprText,
                      zLONG          lFlag )
{
   zCHAR  szVarName[ MAXSTRING ];
   zCHAR  szVarSave[ MAXSTRING ];
   zCHAR  szThrowsException[ 2 ];
   zCHAR  szThrowsExceptionCatchCode[ 256 ];
   zCHAR  szOperationGroup[ 32 ];
   zLONG  lIsParm = 0;
   zLONG  lDataType = 0;
   zLONG  lOffset = psExpr->lOffset;
   zLONG  lCast = 0;
   zBOOL  bPointer = FALSE;
   zSHORT nVarIndex = 0;
   zSHORT nVarNameLength;
   zSHORT nRC;

   // If the expr struct contains information about a variable, then get the offset since this is the ID number of the variable and must be retrieved.
   switch ( psExpr->lElementClass )
   {
      case qVARIABLE:  // 1044
      // if ( psExpr->lOffset < 0 )  // preserve the structure setting
         if ( lOffset < 0 )
         {
            // DGC 3/19/98
            // If we get here it appears that the current variable is an argument to an operation and the argument is an address to something.
            bPointer = TRUE;
         // psExpr->lOffset *= -1;
            lOffset *= -1;
            SetCursorFirstEntityByInteger( g_lpPIView, "Variable", "ID", lOffset, "" );

            if ( g_szGenLang[ 0 ] != 'J' )  // don't do any of this if generating Java
            {
               // If we are in a parm list and this is already a pointer skip putting in the &.
               GetIntegerFromAttribute( &lIsParm, g_lpPIView, "Variable", "ParameterFlag" );

               // Check to see if variable an argument to a operation and if the arguments changes.  This means that we're passing the argument as a pointer.
               //if ( !(psExpr->lDataClass == qTEXT && lIsParm == 2) ) // is not parm
               //if ( lIsParm != 2 ) // is not parm
               if ( psExpr->lDataClass != qTEXT && lIsParm != 2 )  // qTEXT = 2010
                  szVarName[ nVarIndex++ ] = '&';
            }
         }
         else
         {
            SetCursorFirstEntityByInteger( g_lpPIView, "Variable", "ID", lOffset, "" );
            GetIntegerFromAttribute( &lIsParm, g_lpPIView, "Variable", "ParameterFlag" );

            if ( g_szGenLang[ 0 ] != 'J' )  // don't do any of this if generating Java
            {
               // Check to see if variable is a pointer.  If it is then prepend '*'.
               if ( psExpr->lDataClass != qTEXT && lIsParm == 2 )  // qTEXT = 2010
                  szVarName[ nVarIndex++ ] = '*';
            }
         }

         GetStringFromAttribute( szVarName + nVarIndex, zsizeof( szVarName ) - nVarIndex, g_lpPIView, "Variable", "Name" );
         GetStringFromAttribute( pchPFlag, lFlagLth, g_lpPIView, "Variable", "PFlag" );
      // if ( 0 )
      // {
      //    SetNameForView( g_lpPIView, "g_lpPIView", vSubtask, zLEVEL_TASK );
      //    MessageSend( vSubtask, "VM00405", "VML Parser",
      //                 "Please check View: g_lpPIView for Variable Name",
      //                 zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
      // }

         if ( g_szGenLang[ 0 ] == 'J' )  // if generating Java
         {
            if ( lIsParm == 2 && pchPFlag[ 0 ] == 'Y' && psExpr->lOffset >= 0 )
            {
               if ( psExpr->lDataType == qTSTRING )
               {
                  strcat_s( szVarName + nVarIndex, zsizeof( szVarName ) - nVarIndex, ".toString( )" );
               }
               else
               if ( psExpr->lDataType == qTINTEGER || psExpr->lDataType == qTSHORT )
               {
                  strcat_s( szVarName + nVarIndex, zsizeof( szVarName ) - nVarIndex, ".intValue( )" );
               }
               else
               if ( psExpr->lDataType == qTDECIMAL )
               {
                  strcat_s( szVarName + nVarIndex, zsizeof( szVarName ) - nVarIndex, ".doubleValue( )" );
               }
            }
         }
         else
         {
            if ( psExpr->lDataType == qTCHARACTER )
            {
               if ( g_nInParmList != 1 )
                  strcat_s( szVarName, zsizeof( szVarName ), "[ 0 ]" );
            }

            if ( psExpr->lDataType == qTINTEGER && (lFlag & zOPERATION_ARGUMENTS) && bPointer && (psExpr->lFlags & UNSIGNED_BIT) )
            {
               // We are generating a pointer to a long in an operation call.  As the definition is "unsigned" we have to add a "(zPULONG)" cast.  HH,16.7.1998
               strcpy_s( szVarSave, zsizeof( szVarSave ), szVarName );
               strcpy_s( szVarName, zsizeof( szVarName ), "(zPULONG) ");
               strcat_s( szVarName, zsizeof( szVarName ), szVarSave );
            }

            if ( psExpr->lDataType == qTSHORT && (lFlag & zOPERATION_ARGUMENTS) && bPointer && (psExpr->lFlags & UNSIGNED_BIT) )
            {
               // We are generating a pointer to a short in an operation call.  As the definition is "unsigned" we have to add a "(zPUSHORT)" cast.  RG,03.2.1999
               strcpy_s( szVarSave, zsizeof( szVarSave ), szVarName );
               strcpy_s( szVarName, zsizeof( szVarName ), "(zPUSHORT) ");
               strcat_s( szVarName, zsizeof( szVarName ), szVarSave );
            }
         }

         // Fix bug TB363
         // If an integer attribute is assigned to a VIEW variable (e.g. in GetIntegerFromAttribute or
         // SetAttributeFromInteger) then we must generate a cast in order to avoid compiler warnings
         GetIntegerFromAttribute( &lDataType, g_lpPIView, "Variable", "DataType" );
         if ( (psExpr->lDataType != qTINTEGER || lDataType != qTINTEGER) && (lFlag & zOPERATION_ARGUMENTS) && (psExpr->lFlags & NPARM_TYPE_MASK) == NPARM_TYPE_LONG )
         {
            // Parameter type is long, but variable type is not ... generate cast to zLONG.
            if ( psExpr->lDataType != qTDECIMAL )
            {
               if ( g_szGenLang[ 0 ] != 'J' )  // don't do any of this if generating Java
               {
                  strcpy_s( szVarSave, zsizeof( szVarSave ), szVarName );
                  if ( bPointer )
                  {
                     if ( psExpr->lDataType == qTSHORT )
                        strcpy_s( szVarName, zsizeof( szVarName ), "Invalid Cast (zLONG *) ");
                     else
                        strcpy_s( szVarName, zsizeof( szVarName ), "(zLONG *) ");
                  }
                  else
                     strcpy_s( szVarName, zsizeof( szVarName ), "(zLONG) ");

                  strcat_s( szVarName, zsizeof( szVarName ), szVarSave );
               }
            }

            // Likewise for type decimal.
            if ( (psExpr->lDataType != qTDECIMAL || lDataType != qTDECIMAL) && (lFlag & zOPERATION_ARGUMENTS) &&
                 (psExpr->lFlags & NPARM_TYPE_MASK) == NPARM_TYPE_DECIMAL && bPointer == FALSE )
            {
               // Parameter type is decimal, but variable type is not ... generate cast to ZDecimal.
               strcpy_s( szVarSave, zsizeof( szVarSave ), szVarName );
               if ( g_szGenLang[ 0 ] == 'J' )
                  strcpy_s( szVarName, zsizeof( szVarName ), "(double) ");
               else
                  strcpy_s( szVarName, zsizeof( szVarName ), "(ZDecimal) ");

               strcat_s( szVarName, zsizeof( szVarName ), szVarSave );
            }
         }

         // If we generate an assignment like:   *decimalpointer = something,
         // we must prefix the "something" string with a (ZDecimal) cast.  Otherwise we get a failure if the right side is a numeric constant.  HH,17.6.1998
         if ( psExpr->lDataClass == qNUMERIC && psExpr->lDataType == qTDECIMAL && szVarName[ 0 ] == '*' )
         {
            // If we are right, then we find (after blanks) an '=' sign in pchOutputExprStr
            zSHORT nOutputIdxSave = nOutputIdx;

            nOutputIdx++;
            while ( pchOutputExprStr[ nOutputIdx ] == ' ' )
            {
               nOutputIdx++;
            }

            if ( pchOutputExprStr[ nOutputIdx ] == '=' )
            {
               // We need parens for the cast, we want to generate.
               zSHORT n = nOutputIdx;
               while ( pchOutputExprStr[ n + 1 ] != 0 )
               {
                  pchOutputExprStr[ n ] = pchOutputExprStr[ n + 1 ];
                  n++;
               }

               pchOutputExprStr[ n ] = ')'; // closing paren
               nOutputIdx--;
               pchOutputExprStr[ nOutputIdx-- ] = '('; // opening paren
               if ( g_szGenLang[ 0 ] == 'J' )
                  strcat_s( szVarName, zsizeof( szVarName ), " = (double)");
               else
                  strcat_s( szVarName, zsizeof( szVarName ), " = (ZDecimal)" );
            }
            else
               nOutputIdx = nOutputIdxSave;
         }

         break;

      case qDEFINE:  // 1060
         GetDefineExternalValue( szVarName, zsizeof( szVarName ), psExpr->lDataClass, psExpr->lOffset );
         break;

      case qOPERATIONCALL:  // 2008
         if ( psExpr->lOffset > MAXSTRING )
         {
            GetOperationNameFromZKey( vSubtask, szVarName, zsizeof( szVarName ), szVarSave, zsizeof( szVarSave ),
                                      szThrowsException, zsizeof( szThrowsException ), szThrowsExceptionCatchCode, zsizeof( szThrowsExceptionCatchCode ),
                                      szOperationGroup, zsizeof( szOperationGroup ), psExpr->lDataClass, psExpr->lOffset );
         }
         else
         {
            strcpy_s( szVarName, zsizeof( szVarName ), pchExprText + psExpr->lOffset );
         }

         // The next test handles the case where we need to cast a long (in VML) to a LPVIEWCLUSTER
         if ( strcmp( szVarName, "CommitMultipleOIs" ) == 0 )
         {
            strcat_s( szVarName, zsizeof( szVarName ), "( (LPVIEWCLUSTER)");
            nOutputIdx++;  // remove the open paren ... we are putting in a new one
         }

         lCast = 0;
         if ( psExpr->lFlags && psExpr->lFlags != psExpr->lDataType )
         {
            // Here Flags has a special meaning: it denotes a data type for a cast operator ...
            // NOT for cast from short to long.
            if ( psExpr->lFlags != qTINTEGER || psExpr->lDataType != qTSHORT )
            {
               lCast = psExpr->lFlags;
            }
         }
         else
         if ( psExpr->lDataType == qTDECIMAL )
         {
            // XC291: i = StrToDecimal("123"), cast to (ZDecimal) needed
            lCast = qTDECIMAL;
         }

         if ( g_szGenLang[ 0 ] != 'J' )  // don't do any of this if generating Java
         {
            // This is where we are going to implement the hack to add maximum length as the second parameter to several Zeidon operations including:
            // GetStringFromAttribute, SysConvertEnvironmentString, GetFirstTableEntryForAttribute, GetNextTableEntryForAttribute, UfFormatDateTime, UfEditFormatDateTime
            if ( zstrcmp( szVarName, "GetStringFromAttribute" ) == 0 || zstrcmp( szVarName, "SysConvertEnvironmentString" ) == 0 ||
                 zstrcmp( szVarName, "GetFirstTableEntryForAttribute" ) == 0 || zstrcmp( szVarName, "GetNextTableEntryForAttribute" ) == 0 ||
                 zstrcmp( szVarName, "UfFormatDateTime" ) == 0 || zstrcmp( szVarName, "UfEditFormatDateTime" ) == 0 ||
                 zstrcmp( szVarName, "SysMakeWebFileName" ) == 0 || zstrcmp( szVarName, "SysGetDateTime" ) == 0 ||
                 zstrcmp( szVarName, "SysParseLine" ) == 0 || zstrcmp( szVarName, "SfGetTaskInfo" ) == 0 )
            {
               nOutputIdx = AddSizeofToOperation( pchOutputExprStr, nOutputIdx, 1 );
            }
            else
            if ( zstrcmp( szVarName, "SysGetFileDateTime" ) == 0 || zstrcmp( szVarName, "SysGetServerDateTime" ) == 0 ||
                 zstrcmp( szVarName, "zltoa" ) == 0 || zstrcmp( szVarName, "zltox" ) == 0 )
            {
               nOutputIdx = AddSizeofToOperation( pchOutputExprStr, nOutputIdx, 2 );
            }
            else
            if ( zstrcmp( szVarName, "SysReadZeidonIni" ) == 0 || zstrcmp( szVarName, "SysGetWebBannerName" ) == 0 || zstrcmp( szVarName, "fnPainterCall" ) == 0 )
            {
               nOutputIdx = AddSizeofToOperation( pchOutputExprStr, nOutputIdx, 4 );
            }
            else
            if ( zstrcmp( szVarName, "SysGetUserID" ) == 0 || zstrcmp( szVarName, "SysGetDB_UserID" ) == 0 )
            {
               nOutputIdx = AddSizeofToOperation( pchOutputExprStr, nOutputIdx, 3 );
               nOutputIdx = AddSizeofToOperation( pchOutputExprStr, nOutputIdx, 2 );
            }

            switch ( lCast )
            {
               case qTDECIMAL:
                  strcpy_s( szVarSave, zsizeof( szVarSave ), szVarName );
                  strcpy_s( szVarName, zsizeof( szVarName ), "(ZDecimal) " );
                  strcat_s( szVarName, zsizeof( szVarName ), szVarSave );
                  break;

               case qTINTEGER:
                  strcpy_s( szVarSave, zsizeof( szVarSave ), szVarName );
                  strcpy_s( szVarName, zsizeof( szVarName ), "(zLONG) " );
                  strcat_s( szVarName, zsizeof( szVarName ), szVarSave );
                  break;

               case qTSHORT:
                  strcpy_s( szVarSave, zsizeof( szVarSave ), szVarName );
                  strcpy_s( szVarName, zsizeof( szVarName ), "(zSHORT) " );
                  strcat_s( szVarName, zsizeof( szVarName ), szVarSave );
                  break;
            }
         }

         break;

      case qCONSTANT:  // 1010
         if ( psExpr->lDataClass == qTEXT )
         {
         // if ( g_nInParmList == 1 ||
         //      psExpr->lDataType != qTCHARACTER )
            if ( psExpr->lDataType != qTCHARACTER )
            {
               strcpy_s( szVarName, zsizeof( szVarName ), "\"" );
               StrConcatAndMassage( szVarName, pchExprText + psExpr->lOffset );
               strcat_s( szVarName, zsizeof( szVarName ), "\"" );
            }
            else
            {
               strcpy_s( szVarName, zsizeof( szVarName ), "\'" );
               StrConcatAndMassage( szVarName, pchExprText + psExpr->lOffset );
               strcat_s( szVarName, zsizeof( szVarName ), "\'" );
            }
         }
         else
         {
            szVarName[ 0 ] = 0;
            if ( psExpr->lDataType == qTDECIMAL && (lFlag & zOPERATION_ARGUMENTS) && strchr( pchExprText + psExpr->lOffset, '.' ) != 0 )
            {
               // We are generating a decimal constant in an operation call.  The function prototype normally has a zDECIMAL at the
               // corresponding place. We need a cast to ZDecimal to get working C code.  HH,16.6.1998
               if ( g_szGenLang[ 0 ] == 'J' )
                  strcat_s( szVarName, zsizeof( szVarName ), "(double) ");
               else
                  strcat_s( szVarName, zsizeof( szVarName ), "(ZDecimal) ");
            }
            else
            if ( psExpr->lDataType != qTDECIMAL &&
                 (lFlag & zOPERATION_ARGUMENTS) &&
                 (psExpr->lFlags & NPARM_TYPE_MASK) == NPARM_TYPE_DECIMAL )
            {
               if ( g_szGenLang[ 0 ] != 'J' )  // don't do any of this if generating Java
               {
                  // We are generating a non-decimal constant in an operation call, where the target argument is decimal.  Generate a cast to ZDecimal.
                  if ( g_szGenLang[ 0 ] == 'J' )
                     strcat_s( szVarName, zsizeof( szVarName ), "(double) ");
                  else
                     strcat_s( szVarName, zsizeof( szVarName ), "(ZDecimal) ");
               }
            }

            // The next test is a very specialized case where an unsigned cannot start with a '-'
            if ( psExpr->lElementClass == qCONSTANT && psExpr->lDataClass == qNUMERIC && zstrcmp( pchExprText, "-2147483648" ) == 0 )
               strcat_s( szVarName, zsizeof( szVarName ), "0x80000000" );
            else
               strcat_s( szVarName, zsizeof( szVarName ), pchExprText + psExpr->lOffset );
         }

         break;

      case qATTRIBUTEQUALIFIER:  // 2001
         strcpy_s( szVarName, zsizeof( szVarName ), pchExprText + psExpr->lOffset );
         break;

      case qOPERATOR: // 1034
         nRC = GetStringForOperator( szVarName, (zSHORT) (psExpr->lOffset) );
         break;
   }

   nVarNameLength = (zSHORT) zstrlen( szVarName );

   while ( nVarNameLength > 0 )
   {
      pchOutputExprStr[ nOutputIdx-- ] = szVarName[ --nVarNameLength ];  // add strings in reverse order
   }

   return( nOutputIdx );
}

zSHORT LOCALOPER
GetStringForOperator( zPCHAR szOperString,
                      zSHORT nOperator )
{
   switch( nOperator )
   {
      case qLPAREN:
      case qOPENOPER:
         strcpy_s( szOperString, zsizeof( szOperString ), "(" );
         break;
      case qRPAREN:
      case qCLOSEOPER:
         strcpy_s( szOperString, zsizeof( szOperString ), ")" );
         break;
      case qGREATERTHANEQUAL:
         strcpy_s( szOperString, zsizeof( szOperString ), ">=" );
         break;
      case qLESSTHANEQUAL:
         strcpy_s( szOperString, zsizeof( szOperString ), "<=" );
         break;
      case qGREATERTHAN:
         strcpy_s( szOperString, zsizeof( szOperString ), ">" );
         break;
      case qLESSTHAN:
         strcpy_s( szOperString, zsizeof( szOperString ), "<" );
         break;
      case qMINUS:
         strcpy_s( szOperString, zsizeof( szOperString ), "-" );
         break;
      case qADDITION:
         strcpy_s( szOperString, zsizeof( szOperString ), "+" );
         break;
      case qMULTIPLICATION:
         strcpy_s( szOperString, zsizeof( szOperString ), "*" );
         break;
      case qDIVISION:
         strcpy_s( szOperString, zsizeof( szOperString ), "/" );
         break;
      case qEQUAL:
         strcpy_s( szOperString, zsizeof( szOperString ), "=" );
         break;
      case qNOTEQUAL:
         strcpy_s( szOperString, zsizeof( szOperString ), "!=" );
         break;
      case qCONDEQUAL:
         strcpy_s( szOperString, zsizeof( szOperString ), "==" );
         break;
      case qOR:
         strcpy_s( szOperString, zsizeof( szOperString ), "||" );
         break;
      case qAND:
         strcpy_s( szOperString, zsizeof( szOperString ), "&&" );
         break;
      case qNOT:
         strcpy_s( szOperString, zsizeof( szOperString ), "!" );
         break;
      case qCOMMA:
         strcpy_s( szOperString, zsizeof( szOperString ), "," );
         break;
      case qPERIOD:
         strcpy_s( szOperString, zsizeof( szOperString ), "." );
         break;
      case qSEMICOLON:
         strcpy_s( szOperString, zsizeof( szOperString ), ";" );
         break;
      case qUNARYMINUS:
         strcpy_s( szOperString, zsizeof( szOperString ), "-" );
         break;
      default:
         strcpy_s( szOperString, zsizeof( szOperString ), "@........" );
         TraceLineI( szOperString, nOperator );
         break;
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zLONG  LOCALOPER
GetOperationNameFromZKey( zVIEW   vSubtask,
                          zPCHAR  pchReturnName,
                          zLONG   lNameLth,
                          zPCHAR  pchReturnHeaderName,
                          zLONG   lHeaderLth,
                          zPCHAR  pchReturnThrowsException,
                          zLONG   lThrowsLth,
                          zPCHAR  pchThrowsExceptionCatchCode,
                          zLONG   lCatchLth,
                          zPCHAR  pchOperationGroup,
                          zLONG   lGroupLth,
                          zLONG   lOperationClass,
                          zLONG   lZKey )
{
// g_lpPIView is the TZVSP000 object created by parse.
   zVIEW  vLookupView;
   zCHAR  szType[ 2 ];
   zCHAR  szObjectName[ zZEIDON_NAME_LTH + 1 ];
   zCHAR  szParentEntityName[ zZEIDON_NAME_LTH + 1 ];
   zLONG  lSourceZKey;
   zSHORT nDelIncl = 0;
   zLONG  lRC;                              // temp return code

   pchReturnName[ 0 ] = 0;
   pchReturnHeaderName[ 0 ] = 0;
   pchReturnThrowsException[ 0 ] = 0;
   pchThrowsExceptionCatchCode[ 0 ] = 0;
   pchOperationGroup[ 0 ] = 0;

   switch ( lOperationClass )
   {
      case qLOCALOPERATION:
         // Use source meta (LOD or Dialog) to find out whether a C operation is called from VML ... not for "GLOBAL Operations"
         MiGetObjectNameForView( szObjectName, g_vSourceMeta );
         if ( zstrcmp( szObjectName, "TZOGSRCO") == 0 )
         {
            CreateViewFromViewForTask( &vLookupView, g_lpPIView, 0 );
            break;
         }

         CreateViewFromViewForTask( &vLookupView, g_vSourceMeta, 0 );

         // Find the Operation under the scope of the parent of "SourceFile"
         MiGetParentEntityNameForView( szParentEntityName, vLookupView, "SourceFile" );

         lRC = SetCursorFirstEntityByInteger( vLookupView, "Operation", "ZKey", lZKey, szParentEntityName );

         if ( lRC >= zCURSOR_SET )
         {
            // If it is a C operation, just return the name.  Otherwise, go to the XPG object and get the "C generated" name.
         // szType[ 0 ] = 0;
            GetStringFromAttribute( szType, zsizeof( szType ), vLookupView, "SourceFile", "LanguageType" );

            if ( szType[ 0 ] == 'C' )
            {
               // Source type is C.
               GetStringFromAttribute( pchReturnName, lNameLth, vLookupView, "Operation", "Name" );
               DropView( vLookupView );
               return( 0 );
            }
            else
            {
               nDelIncl = 0;

               // If we split a dialog (and maybe object) vml up into more than one source file
               // and make a call in vml1 to an operation in vml2, the generated code isn't correct
               // because the operation in vml2 does not exist in the current tsvspoo for vml1. I tried
               // the below code to rectify the problem and in a way it works but for some reason
               // the operation gets a wrong return code. I don't understand why this is happening so I am
               // going to comment this out in hopes that we can come back...
               /*
               // If g_lpPIView Name doesn't equal the vLookupView sourcefile name, then
               // this local operation is actually in a different source file. Need to
               // get this so that we can create reference properly.
               // KJS 10/13/15
               // We are temporarily including the Operation into TZVSPOO (xpj), so that the
               // can call the derived operation for C_GeneratedOperationName. But keeping this
               // Operation in TZVSPOO creates errors so we delete it down further in code after we
               // retrieve the operation name and the source file.
               // If the operation is a fnLocalBuildQual... the name can be duplicated in the other files, so
               // lets ignore them.
               // The zkey for fnLocal is the number at the end "_22" plus 10000. So I assume that the zkey for these
               // can't be any more than 19999. Going to try this...
               nDelIncl = 0;
               if ( lZKey > 19999 &&
                    CompareAttributeToAttribute( vLookupView, "SourceFile", "Name",
                                                 g_lpPIView, "VML_XSource",  "Name" ) != 0 )
               {
                  IncludeSubobjectFromSubobject( g_lpPIView, "Operation", vLookupView, "Operation", zPOS_AFTER );
                  // Getting the source file name so that we can use that when building the call for the operation.
                  GetStringFromAttribute( pchOperationGroup, vLookupView,
                                          "SourceFile", "Name" );
                  // Indicate that we need to exclude this operation after retrieving the operation name.
                  nDelIncl = 1;
               }
               */

               // Source type is VML.
               if ( CheckEntityInView( vLookupView, "C_GeneratedOperationName" ) == 0 )
               {
                  GetStringFromAttribute( pchReturnName, lNameLth, vLookupView, "Operation", "C_GeneratedOperationName" );
                  DropView( vLookupView );
                  return( 0 );
               }
            }
         }

         // Not found in source meta ... search in XPG object.
         DropView( vLookupView );
         CreateViewFromViewForTask( &vLookupView, g_lpPIView, 0 );
         break;

      case qOBJECTOPERATION:
         lRC = SetCursorFirstEntityByInteger( g_lpPIView, "ExternalOperation", "ZKey", lZKey, "" );
         if ( lRC >= zCURSOR_SET )
         {
            GetIntegerFromAttribute( &lSourceZKey, g_lpPIView, "ExternalOperation", "SourceZKey" );

            // Activate it from configuration management.
            ActivateMetaOI_ByZKey( vSubtask, &vLookupView, 0, zREFER_LOD_META, zSINGLE, lSourceZKey, zCURRENT_OI );
            lRC = SetCursorFirstEntityByInteger( vLookupView, "Operation", "ZKey", lZKey, "LOD" );
            if ( lRC > zCURSOR_UNCHANGED )    // found
            {
               zSHORT nLth = 0;

               if ( g_szGenLang[ 0 ] == 'J' )
               {
                  pchReturnName[ 0 ] = 'm';
                  pchReturnName[ 1 ] = '_';
               // if ( GetStringFromAttribute( pchOperationGroup, lGroupLth, vLookupView, "LOD", "Name" ) != 0 )
                  // KJS 10/13/15 - I have changed this because if an object is split into different source
                  // files, we need to be looking at the source file where the operation is found.
                  if ( GetStringFromAttribute( pchOperationGroup, lGroupLth, vLookupView, "SourceFile", "Name" ) != 0 )
                  {
                     SetNameForView( vLookupView, "vLookupView", vSubtask, zLEVEL_TASK );
                     MessageSend( vSubtask, "VM00405", "VML Parser",
                                  "Please check View: vLookupView for Operation Data",
                                  zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
                  }

                  strcat_s( pchOperationGroup, lGroupLth, "_Object" );
                  strcpy_s( pchReturnName + 2, lNameLth - 2, pchOperationGroup );
                  nLth = (zSHORT) zstrlen( pchReturnName );
                  pchReturnName[ nLth++ ] = '.';
                  pchReturnName[ nLth ] = 0;
               }

               GetStringFromAttribute( pchReturnName + nLth, lNameLth - nLth, vLookupView, "Operation", "C_GeneratedOperationName" );
               DropMetaOI( vSubtask, vLookupView );
               return( lZKey );
            }

            DropMetaOI( vSubtask, vLookupView );
            return( -1 );
         }

         break;

      case qGLOBALOPERATION:
      {
         zVIEW vTempList;

         SetCursorFirstEntityByInteger( g_lpGOListView, "W_MetaDef", "CPLR_ZKey", lZKey, "" );

         // Save the current meta type cursor by creating a temp view and passing it to ActivateMeta.
         // ActivateMeta will change the meta type to Global Op Group.
         CreateViewFromViewForTask( &vTempList, g_lpGOListView, 0 );
         lRC = ActivateMetaOI( vSubtask, &vLookupView, vTempList, zREFER_GO_META, zSINGLE | zLEVEL_APPLICATION );
         DropView( vTempList );
         break;
      }

      case qZEIDONOPERATION:
         lRC = CreateViewFromViewForTask( &vLookupView, g_lpZOListView, 0 );
         break;

      default:
         return( -1 );
         break;
   }

   if ( vLookupView == 0 )
      return( -1 );

   SetNameForView( vLookupView, "vLookupView", vSubtask, zLEVEL_TASK );
   lRC = SetCursorFirstEntityByInteger( vLookupView, "Operation", "ZKey", lZKey, "" );
   if ( lRC > zCURSOR_UNCHANGED )    // found
   {
      zSHORT nLth = 0;

      GetStringFromAttribute( pchReturnThrowsException, lThrowsLth, vLookupView, "Operation", "ThrowsException" );
      GetStringFromAttribute( pchThrowsExceptionCatchCode, lCatchLth, vLookupView, "Operation", "ThrowsExceptionCatchCode" );
      if ( lOperationClass == qLOCALOPERATION )
      {
         if ( nDelIncl == 1 && g_szGenLang[ 0 ] == 'J' )
         {
         // The source file for this operation is not the current source file, so we need to reference this in our operation call.
            pchReturnName[ 0 ] = 'm';
            pchReturnName[ 1 ] = '_';
         // GetStringFromAttribute( pchOperationGroup, lGroupLth, vLookupView, "Operation", "Name" ) != 0 )

            strcat_s( pchOperationGroup, lGroupLth, "_" );
            strcat_s( pchOperationGroup, lGroupLth, szParentEntityName );
            strcpy_s( pchReturnName + 2, lNameLth - 2, pchOperationGroup );
            nLth = (zSHORT) zstrlen( pchReturnName );
            pchReturnName[ nLth++ ] = '.';
            pchReturnName[ nLth ] = 0;
            GetStringFromAttribute( pchReturnName + nLth, lNameLth - nLth, vLookupView, "Operation", "C_GeneratedOperationName" );

            ExcludeEntity( vLookupView, "Operation", zREPOS_NEXT );
         }
         else
         {
            GetStringFromAttribute( pchReturnName, lNameLth, vLookupView, "Operation", "C_GeneratedOperationName" );
            if ( nDelIncl == 1 )
               ExcludeEntity( vLookupView, "Operation", zREPOS_NEXT );
         }
      }
      else
      {
      // zSHORT nLth = 0;

         if ( g_szGenLang[ 0 ] == 'J' )
         {
            if ( lOperationClass == qZEIDONOPERATION )
            {
               GetStringFromAttribute( pchReturnHeaderName, lHeaderLth, vLookupView, "HeaderFile_Oper", "Name" );
            }
            else
            {
               pchReturnName[ 0 ] = 'm';
               pchReturnName[ 1 ] = '_';
               if ( GetStringFromAttribute( pchOperationGroup, lGroupLth, vLookupView, "GlobalOperationGroup", "Name" ) != 0 )
               {
                  MessageSend( vSubtask, "VM00404", "VML Parser",
                               "Please check View: vLookupView for Operation Data",
                               zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
               }

               strcat_s( pchOperationGroup, lGroupLth, "_Operation" );
               strcpy_s( pchReturnName + 2, lNameLth - 2, pchOperationGroup );
               nLth = (zSHORT) zstrlen( pchReturnName );
               pchReturnName[ nLth++ ] = '.';
               pchReturnName[ nLth ] = 0;
            }
         }

         GetStringFromAttribute( pchReturnName + nLth, lNameLth - nLth, vLookupView, "Operation", "Name" );
      }

      DropView( vLookupView );
      return( lZKey );
   }

   strcpy_s( pchReturnName, lNameLth, "OperZKey_" );
   zltoa( lZKey, pchReturnName + 9, lNameLth - 9 );
   strcat_s( pchReturnName, lNameLth, "_NotFound" );
   MiGetParentEntityNameForView( szParentEntityName, vLookupView, "Operation" );
   TraceLine( "Unable to find ZKey: %d in LookupView 0x%08x under parent: %s ... See OI Display", lZKey, vLookupView, szParentEntityName );
   DisplayObjectInstance( vLookupView, szParentEntityName, "Operation" );
   DropView( vLookupView );
   return( -1 );
}

#if 0
zLONG  LOCALOPER
GetOperationNameFromZKey( zVIEW   vSubtask,
                          zPCHAR  pchReturnName,
                          zPCHAR  pchReturnThrowsException,
                          zPCHAR  pchThrowsExceptionCatchCode,
                          zPCHAR  pchOperationGroup,
                          zLONG   lOperationClass,
                          zLONG   lZKey )
{
   zSHORT lRC;  // temp return code

   if ( lpZOListView == 0 )
      return( -1 );

   lRC = SetCursorFirstEntityByInteger( lpZOListView, "Operation", "ZKey", lZKey, "" );
   if ( lRC > zCURSOR_UNCHANGED )    // found
   {
      GetStringFromAttribute( pchReturnName, ???, lpZOListView, "Operation", "Name" );

      nCheckParms = 0;
      lRC = SetCursorFirstEntity( lpZOListView, "Parameter", "" );
      while ( lRC > zCURSOR_UNCHANGED )
      {
         nCheckParms++;
         lRC = SetCursorNextEntity( lpZOListView, "Parameter", "" );
      }

      SetCursorFirstEntity( lpZOListView, "Parameter", "" );
      return( lZKey );
   }

   return( -1 );
}
#endif

zSHORT LOCALOPER
GetDefineExternalValue( zPCHAR pchExternalValue,
                        zLONG  lMaxLth,
                        zLONG  lOperationClass,
                        zLONG  lDefineZKey )
{
   zLONG lRC;
   zVIEW vLookupView;

   CreateViewFromViewForTask( &vLookupView, g_lpPIView, 0 );
   lRC = SetCursorFirstEntity( vLookupView, "ExternalHeaderFile", "" );
   while ( lRC == zCURSOR_SET )
   {
      lRC = SetCursorFirstEntityByInteger( vLookupView, "DefinedItem", "ZKey", lDefineZKey, "" );
      if ( lRC == zCURSOR_SET )
      {
         GetStringFromAttribute( pchExternalValue, lMaxLth, vLookupView, "DefinedItem", "ExternalValue" );
         DropView( vLookupView );
         return( 0 );
      }

      lRC = SetCursorNextEntity( vLookupView, "ExternalHeaderFile", "" );
   }

   DropView( vLookupView );
   return( 0 );
}
