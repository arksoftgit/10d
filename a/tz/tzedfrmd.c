// CHANGE LOG most recent first order
//
// 2016.02.02    DKS
//    Start of new editor (without ActiveX)
//

#define _NOANCHOR
#include <zstdafx.h>
#define zGLOBAL_DATA
#define ZDRAPP_CLASS AFX_EXT_CLASS
#include "..\zdr\Zdr.h"
#include "..\zdr\TzCtl.h"

#define zGLOBAL_DATA
#define KZSYSSVC_INCL
#include "KZOENGAA.H"
#include "stdlib.h"
#include <ctype.h>
#include <string.h>

#include "tz__oprs.h"
#include "tzlodopr.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "ZeidonOp.H"


#define mGetProfileView( pv, v )   GetViewByName( (pv), szlProfileXFER, v, zLEVEL_TASK )
#define mGetWorkView( pvView, v )  GetViewByName( (pvView), szlTZEDWRKO, v, zLEVEL_SUBTASK )

// Editor related Macros
// for cursor positioning purpose
#define MovRight(n)   EDT_GetCursorPosition( vSubtask, &lMoveBaseLine, &lMoveBaseColumn );    \
                      EDT_SetCursorPositionByLineCol( vSubtask, lMoveBaseLine, lMoveBaseColumn + n )

#define MovUp( n )    EDT_GetCursorPosition( vSubtask, &lMoveBaseLine, &lMoveBaseColumn );    \
                      EDT_SetCursorPositionByLineCol( vSubtask, lMoveBaseLine - n, lMoveBaseColumn )

#define MovEOF( )     lMoveBaseLine = EDT_GetLineCount( vSubtask ) - 1; \
                      EDT_SetCursorPositionByLineCol( vSubtask, lMoveBaseLine, EDT_GetLineLength( vSubtask, lMoveBaseLine ) )

/*
#define MovEOL( )    {  zCHAR Buffer[ 2 ];\
                        EDT_GetCursorPosition( vSubtask, &lMoveBaseLine, &lMoveBaseColumn );    \
                        lMoveBaseColumn = pzma->GetActualTextLine( Buffer, 1 ); \
                        EDT_SetCursorPositionByLineCol( vSubtask, lMoveBaseLine, lMoveBaseColumn );     \
                     }
*/

#define MAIN_DIL             1
#define FILECHANGED_DIL      2
#define LINECOL_DIL          3
#define INSERTMODE_DIL       4
#define EDIT_CONTROL_NAME    "_ZeidonEditor"
#define MAX_TOKEN_LTH        100
#define BUFFER_SIZE          512

#define TZEDFRMD_EDIT_CONTEXT_MENU_TAG       "EditContext"
#define TZEDFRMD_EDIT_CONTEXT_MENU_UNDO      "EditContextUndo"
#define TZEDFRMD_EDIT_CONTEXT_MENU_REDO      "EditContextRedo"
#define TZEDFRMD_EDIT_CONTEXT_MENU_CUT       "EditContextCut"
#define TZEDFRMD_EDIT_CONTEXT_MENU_COPY      "EditContextCopy"
#define TZEDFRMD_EDIT_CONTEXT_MENU_PASTE     "EditContextPaste"
#define TZEDFRMD_EDIT_CONTEXT_MENU_DELETE    "EditContextDelete"
#define TZEDFRMD_EDIT_CONTEXT_MENU_SELECTALL "EditContextSelectAll"

#define TZEDFRMD_ACTION_EDIT_UNDO      "EditUndo"
#define TZEDFRMD_ACTION_EDIT_REDO      "EditRedo"
#define TZEDFRMD_ACTION_EDIT_CUT       "EditCut"
#define TZEDFRMD_ACTION_EDIT_COPY      "EditCopy"
#define TZEDFRMD_ACTION_EDIT_PASTE     "EditPaste"
#define TZEDFRMD_ACTION_EDIT_DELETE    "EditDelete"
#define TZEDFRMD_ACTION_EDIT_SELECTALL "EditSelectAll"

// Used when pasting V.E.A
#define PASTE_VIEW_VARIABLE  0x0001
#define PASTE_ENTITY         0x0002
#define PASTE_ATTRIBUTE      0x0004
#define PASTE_WITH_QUOTE     TRUE
#define PASTE_WITHOUT_QUOTE  FALSE

#define FILE_NO_PARSE        0
#define PARSE_FILE           1

// Editor string values.
char szlSysEditorActivate[]  = "__SysEditorActivate";
char szlActiveStatus[]       = "ActiveStatus";
char szlAEQ_PasteSubtask[]   = "AEQ_PasteSubtask";
char szlAttribute[]          = "Attribute";
char szlAttributeName[]      = "AttributeName";
char szlBuffer[]             = "Buffer";
char szlBufferSaveList[]     = "BufferSaveList";
char szlC_File[]             = "C";
char szlCompilerSpecification[] = "CompilerSpecification";
char szlDesc[]               = "Desc";
char szlED[]                 = "ED";
char szlEditor[]             = "Editor";
char szlEditorProfile[]      = "EditorProfile";
char szlEntity[]             = "Entity";
char szlEntityName[]         = "EntityName";
char szlErrorList[]          = "ErrorList";
char szlExtension[]          = "Extension";
char szlFileName[]           = "FileName";
char szlFileOpenSubtask[]    = "FileOpenSubtask";
char szlHeight[]             = "Height";
char szlInsertWithQuote[]    = "InsertWithQuote";
char szlInsertText[]         = "InsertText";
char szlInsertTextFull[]     = "InsertTextFull";
char szlLanguageType[]       = "LanguageType";
char szlLOD[]                = "LOD";
char szlLPLR[]               = "LPLR";
char szlLPLR_Name[]          = "LPLR_Name";
char szlMetaType[]           = "MetaType";
char szlName[]               = "Name";
char szlNone[]               = "None";
char szlObjectName[]         = "ObjectName";
char szlObjectSelAQ[]        = "ObjectSelAQ";
char szlOper[]               = "Oper";
char szlOperation[]          = "Operation";
char szlOperationsList[]     = "OperationsList";
char szlOpIns_InsertDescription[] = "OpIns_InsertDescription";
char szlOperListType[]       = "OperListType";
char szlParentCount[]        = "ParentCount";
char szlParentSubtask[]      = "ParentSubtask";
char szlParentSubtaskName[]  = "ParentSubtaskName";
char szlPasteObjectName[]    = "PasteObjectName";
char szlPasteObjectOption[]  = "PasteObjectOption";
char szlPasteVorOption[]     = "PasteVorOption";
char szlPgmSrcDir[]          = "PgmSrcDir";
char szlPosX[]               = "PosX";
char szlPosY[]               = "PosY";
char szlProfileXFER[]        = "ProfileXFER";
char szlSaveBuffers[]        = "SaveBuffers";
char szlSaveBuffersReturnCode[] = "SaveBuffersReturnCode";
char szlSourceFile[]         = "SourceFile";
char szlSourceFileName[]     = "SourceFileName";
char szlSourceMetaCount[]    = "SourceMetaCount";
char szlSourceMetaName[]     = "SourceMetaName";
char szlSourceViewID[]       = "SourceViewID";
char szlSubdirectory[]       = "Subdirectory";
char szlSubwindow[]          = "Subwindow";
char szlSubwindowActive[]    = "SubwindowActive";
char szlSubwindowSubtask[]   = "SubwindowSubtask";
char szlTargetSpecification[] = "TargetSpecification";
char szlTaskLPLR[]           = "TaskLPLR";
char szlText[]               = "Text";
char szlType[]               = "Type";
char szlTZEDCMPD[]           = "TZEDCMPD";
char szlTZEDFRMD[]           = "TZEDFRMD";
char szlTZCMLPLO_List[]      = "TZEDFRMD_TZCMLPLO_List";
char szlTZEDWRKO[]           = "TZEDWRKO";
char szlTZOPSIGK[]           = "TZOPSIGK";
char szlTZOPSRCO[]           = "TZOPSRCO";
char szlVML_File[]           = "V";
char szlVML_FileExtension[]  = "VML";
char szlVML_Insert[]         = "VML_Insert";
char szlVML_InsertFull[]     = "VML_InsertFull";
char szlVML_Subtask[]        = "VML_Subtask";
char szlVML_Text[]           = "VML_Text";
char szlVariableName[]       = "VariableName";
char szlView[]               = "View";
char szlMETAOPERATIONS[]     = "vMETAOPERATIONS";
char szlSubtask[]            = "vSubtask";
char szlReadOnly[]           = "ReadOnly";
char szlW_MetaDef[]          = "W_MetaDef";
char szlW_MetaType[]         = "W_MetaType";
char szlWidth[]              = "Width";
char szlZeidon[]             = "Zeidon";
char szlZeidonEditor[]       = "Zeidon Editor";
char szlZeidonEditorSubtask[] = "_ZeidonEditorSubtask";
char szlZeidonInitialized[]  = "ZeidonInitialized";
char szlZeidonRestoreState[] = "ZeidonRestoreState";
char szlZKey[]               = "ZKey";

long lMoveBaseLine, lMoveBaseColumn;

//zBOOL   g_bIsFileNew = FALSE; // to handle "File New" menu command
FINDREPLACE g_fr;
CString g_csFindWhat = "";
// CString g_strFindWhat = "";
zBOOL   g_bMatchCase = FALSE;

/////////////////////////////////////////////////////////////////////////////
// Operation declarations

zOPER_EXPORT zSHORT OPERATION
GetWindowAndCtrl( ZSubtask **pWndReturn,
                  ZMapAct  **pzmaReturn,
                  zVIEW    vSubtask,
                  zCPCHAR  cpcCtrlTag );

zOPER_EXPORT zSHORT OPERATION
SystemClose( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
InsertComment( zVIEW vSubtask, LPSTR szOperName, LPSTR szOperComment );
zOPER_EXPORT zSHORT OPERATION
OpIns_BuildOperList( zVIEW vSubtask );

zSHORT LOCALOPER
fnInsertVML_Text( zVIEW    vSubtask,
                  zVIEW    vEdWrk,
                  zVIEW    vProfileXFER );
zOPER_EXPORT zSHORT OPERATION
SaveAndParse( zVIEW vSubtask, zCPCHAR cpcGenLang, zBOOL bMsg );
zOPER_EXPORT zSHORT OPERATION
SaveAndParseC( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
SaveAndParseJava( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_MoveOperationCode( zVIEW  vSubtask,
                            zSHORT nCopyOrMoveFlag );

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_DropOperationFromSource( zVIEW  vSubtask );

zOPER_EXPORT zSHORT OPERATION
AEQ_SelectView( zVIEW vSubtask );

zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_DisableActions( zVIEW vSubtask );

zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_EnableEditMenuActions( zVIEW vSubtask );

zLONG
FindBeginOfOperation( zVIEW    vSubtask,
                      LPCSTR   szOperationName,
                      ZMapAct  *pzma );
zLONG
FindEndOfOperation( zVIEW    vSubtask,
                    LPCSTR   szOperationName,
                    ZMapAct  *pzma );
zBOOL
FileIsEmpty( ZMapAct *pzma );

void
BufInsertStr( zVIEW    vSubtask,
              zCPCHAR  cpc );
static zSHORT
CreateFileInfo( zVIEW    vSubtask,
                zPCHAR   pchName );
static zSHORT
CreateSourceFile( zVIEW    vSubtask,
                  zVIEW    vSource,
                  zBOOL    bCFile,
                  zPCHAR   szSourceFileEntityName );
static zSHORT
GotoCurrentOperation( zVIEW    vSubtask,
                      zVIEW    vSource,
                      zPCHAR   szOperSrch,
                      zPCHAR   szMetaName,
                      zBOOL    bCFile );
static zSHORT
SetTargetExecutableName( zVIEW  vSource,
                         zVIEW  vEdWrk,
                         zPCHAR pchInvokingTool,
                         zPCHAR pchMetaName,
                         zPLONG plMetaType );
static zSHORT
CheckFileAttribute( zPCHAR  pchFileName,
                    zPBOOL  bReadOnly );
static zSHORT
CreateFileName( zVIEW   vTaskLPLR,
                zVIEW   vSource,
                zPCHAR  pchFileName,
                zLONG   lMaxLth,
                zPCHAR  pchInvokingTool,
                zPCHAR  pchSourceFileEntityName,
                zLONG   lEntityNameLth,
                zPBOOL  pbFileExists );
static zSHORT
DeleteOperationFromCurrentFile( zVIEW    vSubtask,
                                zVIEW    vSource,
                                zVIEW    vDeleteOp,
                                zVIEW    vEdWrk,
                                zVIEW    vProfileXFER,
                                ZMapAct  *pzma,
                                zPCHAR   pchFileName );
static zSHORT
InitEditorForMoveAndDelete( ZMapAct *pzma,
                            zVIEW    vSubtask,
                            zPVIEW   pvDeleteOp,
                            zPVIEW   pvSource,
                            zPVIEW   pvEdWrk,
                            zPVIEW   pvProfileXFER,
                            zPCHAR   pchFileName,
                            zLONG    lMaxLth );
static zSHORT
OpenFileForMoveAndDelete( ZMapAct *pzma,
                          zVIEW    vDeleteOp,
                          zVIEW    vEdWrk,
                          zVIEW    vSource,
                          zVIEW    vProfileXFER,
                          zPCHAR   pchFileName,
                          zPCHAR   pchSourceFileName,
                          zBOOL    bCreateFile );
static zSHORT
DropViewsForMoveAndDelete( zVIEW vSubtask,
                           zVIEW vDeleteOp,
                           zVIEW vEdWrk );
static zBOOL
GetOperationPosition( zVIEW    vSubtask,
                      ZMapAct  *pzma,
                      zVIEW    vDeleteOp,
                      zPLONG   plOpStartIndex,
                      zPLONG   plOpEndIndex );
static zLONG
CopyOperationToNewFile( zVIEW    vSubtask,
                        zVIEW    vEdWrk,
                        zPCHAR   pchBuffer );
static zSHORT
GetPositionForNextInsert( zVIEW    vSubtask,
                          zPLONG   plLine,
                          zPLONG   plCol );
static zSHORT /*LOCAL */
fnTZEDFRMD_SaveFile( zVIEW    vSubtask,
                     zPCHAR   pchFileName,
                     zLONG    lMaxLth,
                     zSHORT   nAskForParse );
static zSHORT
CreateErrorMessage( zVIEW  vSubtask,
                    zPCHAR szMsgText );
static zSHORT
RenameOperation( ZMapAct  *pzma,
                 zVIEW    vSubtask,
                 zLONG    lPosition );
static zSHORT
SetUpdateFlagInMeta( zVIEW vSubtask );

zSHORT
fnSaveWithCheckForParse( zVIEW vSubtask );

// From ZCrystalEditView
#define FIND_FORWARD       0x0000
#define FIND_MATCH_CASE    0x0001
#define FIND_WHOLE_WORD    0x0002
#define FIND_DIRECTION_UP  0x0010
#define REPLACE_SELECTION  0x0100

zOPER_EXPORT zBOOL OPERATION
EDT_CanCopy( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_CanPaste( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_CanRedo( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_CanUndo( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_Undo( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_Redo( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_CopyText( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_TabText( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_UntabText( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_CutText( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_DeleteText( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_DeleteTextRange( zVIEW vSubtask, zLONG lStartLine, zLONG lStartCol, zLONG lEndLine, zLONG lEndCol );
zOPER_EXPORT zBOOL OPERATION
EDT_Deselect( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_FindTextPosition( zVIEW vSubtask, zCPCHAR cpcFind, zPLONG plLine, zPLONG plCol, DWORD dwFlags );
zOPER_EXPORT zSHORT OPERATION
EDT_GetActualTextLine( zVIEW vSubtask, zPCHAR pchCurrentLine, zLONG lMaxLth, zLONG lLine );
zOPER_EXPORT zBOOL OPERATION
EDT_GetCursorPosition( zVIEW vSubtask, zPLONG plLine, zPLONG plCol );
zOPER_EXPORT zLONG OPERATION
EDT_GetLineCount( zVIEW vSubtask );
zOPER_EXPORT zLONG OPERATION
EDT_GetLineLength( zVIEW vSubtask, zLONG lLine );
zOPER_EXPORT zBOOL OPERATION
EDT_CloseObject( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_CloseSubWindow( zVIEW vSubtask );
zOPER_EXPORT zCHAR OPERATION
EDT_GetObjectName( zVIEW vSubtask, zPCHAR pchFileName, zLONG lMaxLth );
zOPER_EXPORT zBOOL OPERATION
EDT_GetPositionByIndex( zVIEW vSubtask, zPLONG plLine, zPLONG plColumn );
zOPER_EXPORT zBOOL OPERATION
EDT_GetSelectedText( zVIEW vSubtask, zPCHAR pchText, zLONG lMaxLth );
zOPER_EXPORT zLONG OPERATION
EDT_GetSelectedTextLength( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_GetTextFromLineOfIndex( zVIEW vSubtask, zPCHAR pchBuffer, zLONG lMaxLth, zLONG lLine );
zOPER_EXPORT zLONG OPERATION
EDT_GetTextFromRange( zVIEW vSubtask, zPCHAR pchBuffer, zLONG lMaxLth, zLONG lStartLine, zLONG lStartCol, zLONG lEndLine, zLONG lEndCol );
zOPER_EXPORT zBOOL OPERATION
EDT_GotoWindow( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_InsertItem( zVIEW vSubtask, zCPCHAR cpcInsertText, zBOOL bResetPos );
zOPER_EXPORT zBOOL OPERATION
EDT_IsCommentAtIndex( zVIEW vSubtask, zLONG lLine, zLONG lCol );
zOPER_EXPORT zBOOL OPERATION
EDT_IsFileChanged( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_IsFileNew( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_IsReadOnly( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_OpenObject( zVIEW vSubtask, zCPCHAR cpcFileName );
zOPER_EXPORT zBOOL OPERATION
EDT_OpenNewObject( zVIEW vSubtask, zCPCHAR cpcFileName );
zOPER_EXPORT zBOOL OPERATION
EDT_PasteText( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_PrintObject( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_PropertyDialog( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_ReadOnlyMode( zVIEW vSubtask, zBOOL bReadOnly );
zOPER_EXPORT zBOOL OPERATION
EDT_SaveFile( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_SaveFileAs( zVIEW vSubtask, zCPCHAR cpcFileName );
zOPER_EXPORT zBOOL OPERATION
EDT_SelectAll( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_SelectItem( zVIEW vSubtask, zLONG lLine, zLONG lCol, zCPCHAR cpcText );
zOPER_EXPORT zBOOL OPERATION
EDT_SelectRange( zVIEW vSubtask, zLONG lLine, zLONG lCol, zLONG lCharCnt );
zOPER_EXPORT zBOOL OPERATION
EDT_SetCursorPositionByLineCol( zVIEW vSubtask, zLONG lLine, zLONG lCol );
zOPER_EXPORT zBOOL OPERATION
EDT_WantKeystrokes( zVIEW vSubtask, zBOOL bOn );
zOPER_EXPORT zBOOL OPERATION
EDT_ZeidonSyntaxOn( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_SyntaxOff( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_OnSize( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_FindDialog( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_ReplaceDialog( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
EDT_FindPrevious( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
EDT_RepeatFind( zVIEW vSubtask );
zOPER_EXPORT zCPCHAR OPERATION
EDT_GetLastFindString( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_SetBookmark( zVIEW vSubtask, int nTag );
zOPER_EXPORT zBOOL OPERATION
EDT_GoToBookmark( zVIEW vSubtask, int nTag );
zOPER_EXPORT zBOOL OPERATION
EDT_GoToNextBookmark( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_GoToPreviousBookmark( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_ToggleBookmark( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_ClearAllBookmarks( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
EDT_ReplaceAll( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_SearchSelectedText( zVIEW vSubtask );
zOPER_EXPORT zBOOL OPERATION
EDT_PageUp(zVIEW vSubtask);
zOPER_EXPORT zBOOL OPERATION
EDT_PageDown(zVIEW vSubtask);

/////////////////////////////////////////////////////////////////////////////
// Setup a comment in the current editor instance
//
// Parameter :
//    zV8EW vSubtask           Editor window subtask
//    LPSTR szOperName         Operation Name
//    LPSTR szOperComment      Comment
//
// Return :
//    zShort number of lines inserted as a comment
//
zOPER_EXPORT zSHORT OPERATION
InsertComment( zVIEW vSubtask, LPSTR szOperName, LPSTR szOperComment )
{
// zCHAR       szCommentType[ 256 ];
   CStringList sl;
   POSITION    pos = NULL;
   CString     csSource;
   CString     csLine;
   CString     csText;
   CString     csCommentStart = "//";
   CString     csLineStart = "//  ";
   CString     csCommentStop = "//";
   CString     csNewLine = "\r\n";
   zPCHAR      pchBuffer = 0;
   zLONG       lCommentLength = 0;
   zLONG       lLineLength = 79;
   zLONG       k = 0;
   zLONG       j = 0;

   // A line containing the beginning of Operation Documentation like "///////////..."
   CString csBegin( '/', lLineLength - csCommentStart.GetLength( ) - csCommentStop.GetLength( ) );

   // A line which contains only blanks.
   CString csBlanks( ' ', lLineLength - csCommentStart.GetLength( ) - csCommentStop.GetLength( ) );
   csSource = szOperComment;

   // Setting up a list of strings which are part of the Comment.
   csLine = csNewLine + csCommentStart + csBegin + csNewLine;
   sl.AddTail( csLine );
   sl.AddTail( csCommentStart + csNewLine ); // insert an empty comment line

   // Add operation name.
   csLine = csLineStart + "OPERATION: " + szOperName + csNewLine;
   sl.AddTail( csLine );

// csLine = csLineStart + csNewLine;  // insert an empty comment line
// sl.AddTail( csLine );

   lCommentLength = csSource.GetLength( );
   pchBuffer = csSource.GetBufferSetLength( lCommentLength );

   // replace \r and \n by spaces
   while ( *pchBuffer )
   {
      if ( *pchBuffer == '\r' || *pchBuffer == '\n' )
         *pchBuffer = ' ';

      pchBuffer++;
   }

   csSource.ReleaseBuffer( );

   csSource.TrimLeft( );     // ensure there is no blank at the beginning
   lCommentLength = csSource.GetLength( );

   j = k = 0;
   while ( lCommentLength > 0 )
   {
      csText = csSource.Mid( k, lLineLength ); // take the first 100 bytes

      csText.TrimLeft( ); // make sure there is no blank at the beginning

      // Find a previous blank to have no linefeed within a word.
      if ( csText.GetLength( ) >= lLineLength )
         j = csText.ReverseFind( ' ' );
      else
         j= -1;

      if ( j > -1 )
      {
         csText = csText.Left( j );
      }

      if ( !csText.IsEmpty( ) )
      {
         k += csText.GetLength( );    // The next 100 bytes we want to proceed with
                                      // start at k + length of current line
         lCommentLength = lCommentLength - csText.GetLength( );
         csText.TrimRight( );
         csLine = csLineStart;
         csLine = csLine + csText + csNewLine;
         sl.AddTail( csLine );
      }
      else
      {
         k++;
         lCommentLength--;
      }
   }

   csLine = csCommentStart + csNewLine;  // insert an empty comment line
   sl.AddTail(csLine );

   csLine = csBegin + csCommentStop + csNewLine;
   sl.AddTail( csLine );

   // inserting the strings stored in the stringlist
   pos = sl.GetHeadPosition( );  // get the beginning of the list

   while ( pos )
   {
      csText = sl.GetAt( pos );
      MovEOF( );
     // KJS 11/11/16 - The last parameter is whether we should reset the position of the cursor, not sure why it's
     // FALSE because we always set the cursor position to after what we've pasted. So I'm changing to TRUE.
     EDT_InsertItem( vSubtask, csText, TRUE ); // send string to Editor control
      sl.GetNext( pos );  // get next list entry
   }

   return( sl.GetCount( ) );
}

/////////////////////////////////////////////////////////////////////////////
// check whether a file contains whitespaces only
// Parameter :
//    ZMapAct *pzma     Pointer to the Editor Instance
//
// Return : TRUE if whitespace only otherwise FALSE
//
zBOOL
FileIsEmpty( ZMapAct *pzma )
{
   zBOOL bIsSpace = TRUE;
   zCHAR szHelp[ BUFFER_SIZE + 1 ];
   zCHAR szFileName[ MAX_PATH + 1 ];

   memset( szFileName, ' ', MAX_PATH );
   szFileName[ MAX_PATH ] = 0;

   if ( pzma )
   {
      zLONG lByteCount = 1;
      zLONG lStartLine = 0;
      zLONG lStartCol = 0;
      zLONG lEndLine = EDT_GetLineCount( pzma->m_pZSubtask->m_vDialog ) - 1;
      zLONG lEndCol = EDT_GetLineLength( pzma->m_pZSubtask->m_vDialog, lEndLine );
      if ( lEndLine == 0 && lEndCol == 0 )
         return TRUE;

      while ( bIsSpace && lByteCount > 0 )
      {
         lByteCount = EDT_GetTextFromRange( pzma->m_pZSubtask->m_vDialog, szHelp, zsizeof( szHelp ), lStartLine, lStartCol, lEndLine, lEndCol );
         for ( zLONG k = 0; k < lByteCount && bIsSpace; k++ )
         {
            if ( !isspace( szHelp[ k ]) )
               bIsSpace = FALSE;
         }

         lStartCol = lEndCol;
         lEndCol = lStartLine + BUFFER_SIZE;
      }
   }
   else
      bIsSpace = FALSE;

   return( bIsSpace );
}

zBOOL
fnIsCommentAtIndex( zVIEW vSubtask, zLONG lLine, zLONG lCol )
{
   return FALSE;  // not yet implemented
}

/////////////////////////////////////////////////////////////////////////////
// Search the source for the first occurrence of a requested Operation
// which is not part of a comment
//
// Parameter :
//    LPCSTR szOperationNameName of the requestet operation
//    ZMapAct *pzma     Pointer to the Editor instance
//
// Return :
//    zLONG a zero-based index which represents the position of
//          the operation within the source
//
zLONG
FindBeginOfOperation( zVIEW vSubtask, LPCSTR szOperationName, ZMapAct *pzma )
{
   zLONG   lEndLine, lEndCol, lLine = 0, lLastLine = 0, lCol = 0;
   zCHAR   szOperSrch[ 256 ];
   DWORD   dwTBEDTDefaultSearchBehavior = FIND_MATCH_CASE | FIND_WHOLE_WORD;
   zCHAR   szExtension[ 3 ];
   CString csENDString;
   zLONG   lKeyWordLength = 0;
   zVIEW   vEdWrk = 0;
   zLONG   lDefaultLineLength = 255;

   mGetWorkView( &vEdWrk, vSubtask );

   GetStringFromAttribute( szExtension, zsizeof( szExtension ), vEdWrk, szlBuffer, szlLanguageType );

   // If current file is a C-Source the end of an operation is "}" otherwise it is END
   if ( zstrcmp( szExtension, szlC_File ) == 0 )
   {
      csENDString = "} *";
      lKeyWordLength = 1; // }
   }
   else
   {
      csENDString = "\\bEND[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+";
      lKeyWordLength = 3; // END
   }

   // Set up search string.
   sprintf_s( szOperSrch, zsizeof( szOperSrch ), "\\bOPERATION[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+%s[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]*(", szOperationName );

   EDT_FindTextPosition( vSubtask, szOperSrch, &lLine, &lCol, dwTBEDTDefaultSearchBehavior );

   // Skipping lines where the search text is part of a comment.
   while ( fnIsCommentAtIndex( vSubtask, lLine, lCol ) && lLine > -1 )
   {
      lLine++;
      EDT_FindTextPosition( vSubtask, szOperSrch, &lLine, &lCol, dwTBEDTDefaultSearchBehavior );
   }

   // Now we are at the position which looks like this "OPERATION MyOperation ("
   // to find the real begin of the operation we step back until we find
   // the keyword "END" of the previous operation in order to drop all comments
   // between the beginning of an operation to the end of the previous Operation.
   if ( lLine > -1 )
   {
      lEndLine = lLine;
      EDT_FindTextPosition( vSubtask, csENDString, &lEndLine, &lEndCol, 0 );

      while ( fnIsCommentAtIndex( vSubtask, lEndLine, lEndCol ) && lEndLine > -1 )
      {
         lEndLine--;
         EDT_FindTextPosition( vSubtask, csENDString, &lEndLine, &lEndCol, 0 );
      }

      if ( lEndLine > -1 )
      {
         lLine = lEndLine + lKeyWordLength; // add 3 for keyword length

         // Setting index to the first column of the next line
         lLastLine = EDT_GetLineCount( vSubtask ) - 1;
         EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
         while ( lLine < lLastLine && lCol > 0 )
         {
            lLine++;
            EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
         }
      }
      else
      {
         // a Value of -1 tells us there is no previous END Keyword
         // therefore we have to search for an empty line
         // the function GetTextFromLineOfIndex retrieves the text and the text-length
         // we are still at the position which looks like this "OPERATION MyOperation ("
         zLONG lReturnedBuffSize = 0;
         BOOL bIsSpace = FALSE;
         CString csBuffer;
         LPSTR szBuffer;
         szBuffer = csBuffer.GetBufferSetLength( lDefaultLineLength );

         lEndLine = lLine;

         EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
         lEndLine -= lCol;  // set index to begin of line
         lEndLine --;       // set index to end of previous line

         // Get the text of the current line.
         lReturnedBuffSize = EDT_GetTextFromLineOfIndex( vSubtask, szBuffer, lDefaultLineLength, lEndLine );
         while ( lReturnedBuffSize > 0 && bIsSpace == FALSE )
         {
            LPSTR p = szBuffer;

            // Check whether the buffer contains only whitespaces.
            while (isspace(*p) && ((zLONG)(p - szBuffer) < lDefaultLineLength ))
            {
               p++;
            }

            if ( (lReturnedBuffSize - ((zLONG)(p - szBuffer))) == 0 )
            {
               // Ignore empty lines in a comment.
               if ( !fnIsCommentAtIndex( vSubtask, lEndLine, lEndCol ) )
               {
                  bIsSpace = TRUE;
               }
               else
               {
                  EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
                  lEndLine -= lCol;  // set index to begin of line
                  lEndLine --;       // set index to end of previous line

                  // Get the text of the now current line.
                  lReturnedBuffSize = EDT_GetTextFromLineOfIndex( vSubtask, szBuffer, lDefaultLineLength, lEndLine );
               }
            }
            else
            {
               EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
               lEndLine -= lCol;  // set index to begin of line
               lEndLine --;       // set index to end of previous line

               // Get the text of the now current line.
               lReturnedBuffSize = EDT_GetTextFromLineOfIndex( vSubtask, szBuffer, lDefaultLineLength, lEndLine );
            }
         }

         // There is a chance that there is no space leading a comment.
         // If so we are at the beginning of the file.
         if ( lEndLine < 0 )
         {
            long l = lLine - lCol;  // set index to line preceeding "OPERATION......"
            while ( fnIsCommentAtIndex( vSubtask, lLine, lCol ) && l > 0 )
            {
               l--;
            }
            if ( l == 0 )// we are at BOF
            {
                bIsSpace = TRUE;
                lEndLine = 0;
            }
         }

         if ( lReturnedBuffSize == 0 || bIsSpace == TRUE )
         {
            lLine = lEndLine;
         }
         else
         {
            lLine = -1;
         }

         // If the Source File is a C-File and do you want to search the first
         // operation, search for position of ";" (semicolon for Prototypes) or
         // "#" (for defines, includes).
         if ( zstrcmp(szExtension, szlC_File) == 0 )
         {
            csENDString = "[#;]";

            EDT_FindTextPosition( vSubtask, szOperSrch, &lEndLine, &lEndCol, dwTBEDTDefaultSearchBehavior );
            EDT_FindTextPosition( vSubtask, csENDString, &lEndLine, &lEndCol, 0 );
            if ( lEndLine > -1 )
            {
               // Setting index to the first column of the next line.
               EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
               EDT_SetCursorPositionByLineCol( vSubtask, lLine + 1, 0 );
               EDT_GetCursorPosition( vSubtask, &lEndLine, &lCol );
            }
            if ( lEndLine > 0 && lEndLine > lLine )
               lLine = lEndLine;
         }

      } // End of search for an empty line
   } // End of search for the end of the previous operation

   return( lLine );
}

/////////////////////////////////////////////////////////////////////////////
// Search the source for the end of a requested Operation which is not part of a comment
//
// Parameter :
//    LPCSTR szOperationName    Name of the requested operation the operation
//                              within the source where we start the search
//    ZMapAct *pzma    Pointer to the Editor instance
//
// Return :
//    zLONG a zero based index which represents the position of
//          the end of an operation within the source
//
zLONG
FindEndOfOperation( zVIEW    vSubtask,
                    LPCSTR   szOperationName,
                    ZMapAct  *pzma )
{
   zLONG    lLine = 0, lCol = 0, lKeyWordLength = 0;
   static   zCHAR szOperationString[] = "\\bOPERATION[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+";
   zVIEW    vEdWrk = 0;
   zCHAR    szOperSrch[ 256 ];
   DWORD    dwTBEDTDefaultSearchBehavior = FIND_MATCH_CASE | FIND_WHOLE_WORD;
   zCHAR    szExtension[ 3 ];
   CString  csENDString;

   mGetWorkView( &vEdWrk, vSubtask );
   GetStringFromAttribute( szExtension, zsizeof( szExtension ), vEdWrk, szlBuffer, szlLanguageType );

   if ( zstrcmp( szExtension, szlC_File ) == 0 )
   {
      csENDString = "} *";
      lKeyWordLength = 1; // }
   }
   else
   {
      csENDString = "\\bEND[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+";
      lKeyWordLength = 3; // END
   }

   // setup search string "OPERATION OperationName ("
   sprintf_s( szOperSrch, zsizeof( szOperSrch ), "\\bOPERATION[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+%s[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]*(", szOperationName );
   EDT_FindTextPosition( vSubtask, szOperSrch, &lLine, &lCol, dwTBEDTDefaultSearchBehavior );

   // Skipping lines where the search text is part of a comment
   while ( fnIsCommentAtIndex( vSubtask, lLine, lCol ) && lLine > -1 )
   {
      lLine++;
      EDT_FindTextPosition( vSubtask, szOperSrch, &lLine, &lCol, dwTBEDTDefaultSearchBehavior );
      TraceLineI( "(xxx) Return line from search = ", lLine );
   }

   if ( lLine < 0 )
      return( lLine );

   lLine++; // prevent from finding the same token ("OPERATION") which we already have

   // Find the end of the current operation by searching for the beginning
   // of the next operation.  Since we want to ignore any operations that
   // might be commented out, keep searching until we are not in a comment.

   EDT_FindTextPosition( vSubtask, szOperationString, &lLine, &lCol, FIND_FORWARD );
   while ( fnIsCommentAtIndex( vSubtask, lLine, lCol ) && lLine > -1 )
   {
      lLine++;
      EDT_FindTextPosition( vSubtask, szOperationString, &lLine, &lCol, FIND_FORWARD );
   }

   // Now we should have the begin of the next operation.
   // With this information we can search backwards until we find
   // the keyword END to skip important comments
   //
   if ( lLine > -1 )
   {
      EDT_FindTextPosition( vSubtask, csENDString, &lLine, &lCol, 0 );
      while ( fnIsCommentAtIndex( vSubtask, lLine, lCol ) && lLine > -1 )
      {
         lLine--;
         EDT_FindTextPosition( vSubtask, csENDString, &lLine, &lCol, 0 );
      }

      // Right now we have the startposition of the keyword "END" which
      // ends the operation add 3 for keyword length
      if ( lLine > -1 )
      {
         lLine += lKeyWordLength;

         // Setting index to the first column of the next line
         // assuming that comments in the same line as the closing END
         // belong to the operation
         zLONG lLastLine = 0, lLine = 0, lCol = 0;
         lLastLine = EDT_GetLineCount( vSubtask ) - 1;
         EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
         while ( lLine < lLastLine && lCol > 0 )
         {
            lLine++;
            EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
         }
      }
   }
   else
   {
      // an index of -1 means there is no next Operation so delete anything to the end of file
      if ( zstrcmp( szExtension, szlC_File ) == 0 )
      {
         // in c-files search for #ifdef __cplusplus (from end to begin)
         // to get the position where to insert new operation
         static zCHAR szSearchString[] = "\\bifdef __cplusplus[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+";

         zLONG lLine = 0;
         // set cursor to the last line
         lLine = EDT_GetLineCount( vSubtask ) - 1;
         EDT_SetCursorPositionByLineCol( vSubtask, lLine, 0 );
         EDT_FindTextPosition( vSubtask, szSearchString, &lLine, &lCol, FIND_DIRECTION_UP );
         lLine--;
         zLONG lOpStartLine = -1;
         lOpStartLine = FindBeginOfOperation( vSubtask, szOperationName, pzma );

         // if end position < start position, set end of file
         if ( lOpStartLine >= 0 && lLine < 0 || lOpStartLine >= lLine )
            lLine =  1048576; // this is a Megabyte I never saw a single source file

      }
      else
         lLine =  1048576; // this is a Megabyte I never saw a single source file with that size
   }

   return( lLine );
}

static zSHORT
DeleteOperationFromCurrentFile( zVIEW    vSubtask,
                                zVIEW    vSource,
                                zVIEW    vDeleteOp,
                                zVIEW    vEdWrk,
                                zVIEW    vProfileXFER,
                                ZMapAct  *pzma,
                                zPCHAR   pchFileName )
{
   zCHAR      szSourceFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR      szOperName[ 33 ];
   zBOOL      bReturn = FALSE;
   zLONG      lOpStartLine;
   zLONG      lOpStartCol;
   zLONG      lOpEndLine;
   zLONG      lOpEndCol;
   zSHORT     nRC;

   if ( OpenFileForMoveAndDelete( pzma, vDeleteOp, vEdWrk, vSource, vProfileXFER,
                                  pchFileName, szSourceFileName, FALSE ) >= 0 )
   {
      bReturn = FALSE;

      for ( nRC = SetCursorFirstEntity( vDeleteOp, "Operation", "" );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDeleteOp, "Operation", "" ) )
      {
         bReturn = FALSE;
         lOpStartLine  = -1;
         lOpStartCol   = -1;
         lOpEndLine    = -1;
         lOpEndCol     = -1;
         GetStringFromAttribute( szOperName, zsizeof( szOperName ), vDeleteOp, "Operation", "Name" );

         // 1. find begin and end for the requestet operation
         lOpStartLine = FindBeginOfOperation( vSubtask, szOperName, pzma );

         if ( lOpStartLine >= 0 )
            lOpEndLine = FindEndOfOperation( vSubtask, szOperName, pzma );

         // 2. delete code within the range of lOpStartLine and lOpEndLine
         if ( lOpStartLine >= 0 && lOpEndLine >= 0 && lOpStartLine < lOpEndLine )
         {
            bReturn = EDT_DeleteTextRange( vSubtask, lOpStartLine, lOpStartCol, lOpEndLine, lOpEndCol );
            if ( bReturn == FALSE )
               bReturn = TRUE;
         }
      } // endfor ( nRC = SetCursorFirstEntity( vDeleteOp, "Operation", "" )

      if ( bReturn == TRUE )
      {
         EDT_SaveFile( vSubtask );
      }

      // if source file empty, delete it
      if ( FileIsEmpty( pzma ) )
         SysOpenFile( vSubtask, szSourceFileName, COREFILE_DELETE );

      DeleteEntity( vEdWrk, "Buffer", zREPOS_NEXT );
   } // endif ( OpenFileForMoveAndDelete( pzma, vDeleteOp, vEdWrk, vSource,...

   return( (zSHORT) bReturn );
}


zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_DropOperationFromSource( zVIEW vSubtask )
{
   zSHORT     nReturn = 0;
   zSHORT     nRC;
   zCHAR      szFileName[ zMAX_FILENAME_LTH + 1 ];
   zVIEW      vEdWrk  = 0;
   zVIEW      vSource = 0;
   zVIEW      vProfileXFER = 0;
   zVIEW      vDeleteOp = 0;
   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;
   GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME );

   if ( InitEditorForMoveAndDelete( pzma, vSubtask, &vDeleteOp, &vSource,
                                    &vEdWrk, &vProfileXFER, szFileName, zsizeof( szFileName ) ) < 0 )
   {
      return( -1 );
   }


   for ( nRC = SetCursorFirstEntity( vDeleteOp, "SourceFile", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vDeleteOp, "SourceFile", "" ) )
   {
      nReturn = DeleteOperationFromCurrentFile( vSubtask, vSource, vDeleteOp,
                                                vEdWrk, vProfileXFER, pzma, szFileName );
   }

   DropViewsForMoveAndDelete( vSubtask, vDeleteOp, vEdWrk );

   return( nReturn );
}

// The new editor doesn't support a case-sensitive search
// the same way as the old one does. To do a case sensitive search,
// we have to format the search string the following way
// Source string : View
// Target string : [Vv][Ii][Ee][Ww]
// This function formats every character in the source, regardless of
// escape sequences. So be aware of passing incorrect search strings.
zLONG
BuildCaseSensitiveSearchString( LPCSTR lpSource, CString &csTarget )
{
   CString csLower = lpSource;
   CString csUpper = lpSource;
   CString csHelp;
   CString csFormatHelp = "[%c%c]";
   zLONG lLength;

   csTarget.Empty( );      // clean Target
   csUpper.MakeUpper( );   // Conversion so I don't have to do
   csLower.MakeLower( );   // thus c stuff isupper(*lpx)?*lpx:*lpx += 32;

   lLength = csLower.GetLength( );
   for ( zLONG k = 0; k < lLength; k++ )
   {
      if ( csUpper.GetAt( k ) != ' ' )// skip formating if blank occurs
      {
         csHelp.Format( csFormatHelp, csUpper.GetAt( k ), csLower.GetAt( k ) );
      }
      else
      {
         csHelp = " ";
      }

      csTarget += csHelp;
   }

   return( csTarget.GetLength( ) );
}

// Get the Numer of Tabs in the current line up to the given position.
int
GetTabsInLine( zVIEW vSubtask, zLONG lUpToPosition )
{
   CString  csCurrentLine;
   LPSTR    pchCurrentLine;
   zLONG    lBuffSize;
   zLONG    lPosition;
   zLONG    lLine;
   zLONG    lCol;
   int      k = 0;

   EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
   lBuffSize = EDT_GetLineLength( vSubtask, lLine ) + 1;
   if ( lBuffSize > 1 )
   {
      // Get the text of the current line.
      pchCurrentLine = csCurrentLine.GetBufferSetLength( lBuffSize );
      EDT_GetActualTextLine( vSubtask, pchCurrentLine, lBuffSize, lLine );

      // Count the Number of TABS.
      for ( lPosition = 0;
            *pchCurrentLine && lPosition <= lUpToPosition;
            pchCurrentLine++, lPosition++ )
      {
         if ( *pchCurrentLine == '\t' )
         {
            k++;
         }
      }
   }

   return( k );
}

void
BufInsertStr( zVIEW vSubtask, zCPCHAR cpc )
{
   // Set cursor to the last line.
   MovEOF( );
   EDT_InsertItem( vSubtask, cpc, FALSE );
}

int
OperTemplate( zVIEW vSubtask, zVIEW vSource )
{
   zVIEW    vLOD   = 0;
   zVIEW    vEdWrk = 0;
   LPSTR    szLOD  = 0;
   LPSTR    szOperName;
   LPSTR    szType;
   LPSTR    szReturnDataType;
   LPSTR    szDataType;
   zBOOL    bPointer;
   zBOOL    bUnsigned;
   zBOOL    bFileC;
   zSHORT   nParam;
   zCHAR    szParam[ 65 ];
   zCHAR    szParamCase[ 65 ];
   zCHAR    szLine[ 65 ];
   LPSTR    szOperComment;
   LPSTR    szTab = "   ";
   CString  csFormat;
   CString  csInsertBuffer;
   zSHORT   nRC;
   zSHORT   nLth;

   mGetWorkView( &vEdWrk, vSubtask );

   GetAddrForAttribute( &szOperName, vSource, szlOperation, szlName );
   GetAddrForAttribute( &szOperComment, vSource, szlOperation, "Desc" );
   GetAddrForAttribute( &szType, vSource, szlOperation, "Type" );
   GetAddrForAttribute( &szReturnDataType, vSource, szlOperation, "ReturnDataType" );
   bFileC = CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlC_File ) == 0;

   // First of all set up comment for the Operation.
   InsertComment( vSubtask, szOperName, szOperComment );

   if ( szType )
   {
      if ( bFileC )
      {
         csFormat = "zOPER_EXPORT %s /* ";
         switch ( szReturnDataType[ 0 ] )
         {
            case 'V':
               csInsertBuffer.Format( csFormat, "zVIEW" );
               break;

            case 'N':
               csInsertBuffer.Format( csFormat, "zSHORT" );
               break;

            case 'M':
               csInsertBuffer.Format( csFormat, "zDECIMAL" );
               break;

            case 'Y':
               csInsertBuffer.Format( csFormat, "zCHAR" );
               break;

            case 'L':
               csInsertBuffer.Format( csFormat, "zLONG" );
               break;

            case 'O':
            case 0: // empty data type is handled as void
               csInsertBuffer.Format( csFormat, "zVOID" );
               break;

            default:
               csInsertBuffer.Format( csFormat, "zSHORT" );
         }
         //BufInsertStr( vSubtask, csInsertBuffer );
      }

      switch ( szType[0] )
      {
         case 'D':
            bFileC ? csInsertBuffer += "DIALOG */  OPERATION\r\n"
                   : csInsertBuffer += "DIALOG OPERATION\r\n";
            break;

         case 'E':
            bFileC ? csInsertBuffer += "ENTITY CONSTRAINT */  OPERATION\r\n"
                   : csInsertBuffer += "ENTITY CONSTRAINT OPERATION\r\n";
            break;

         case 'C':
         case 'O':
            bFileC ? csInsertBuffer += "OBJECT CONSTRAINT */  OPERATION\r\n"
                   : csInsertBuffer += "OBJECT CONSTRAINT OPERATION\r\n";
            break;

         case 'T':
            bFileC ? csInsertBuffer += "TRANSFORMATION */  OPERATION\r\n"
                   : csInsertBuffer += "TRANSFORMATION OPERATION\r\n";
            break;

         case 'A':
            bFileC ? csInsertBuffer += "DERIVED ATTRIBUTE */  OPERATION\r\n"
                   : csInsertBuffer += "DERIVED ATTRIBUTE OPERATION\r\n";
            break;

         case 'M':
            bFileC ? csInsertBuffer += "DOMAIN */  OPERATION\r\n"
                   : csInsertBuffer += "DOMAIN OPERATION\r\n";
            break;

         case 'G':
            bFileC ? csInsertBuffer += "GLOBAL */  OPERATION\r\n"
                   : csInsertBuffer += "GLOBAL OPERATION\r\n";
            break;

         case 'L':
         default:
            bFileC ? csInsertBuffer += "LOCAL */  OPERATION\r\n"
                   : csInsertBuffer += "LOCAL OPERATION\r\n";
         }
   }
   else
      bFileC ? csInsertBuffer += "LOCAL */  OPERATION\r\n"
             : csInsertBuffer += "LOCAL OPERATION\r\n";

   nLth = lstrlen( szOperName ) + 2;
   csInsertBuffer +=  szOperName;
   csInsertBuffer += "( ";

   CString csParamIndent( ' ', nLth );

   // Insert parameter list.
   nParam = 0;
   for ( nRC = SetCursorFirstEntity( vSource, "Parameter", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vSource, "Parameter", "" ) )
   {
      if ( nParam > 0 )
      {
         csInsertBuffer += ",\r\n";
         csInsertBuffer += csParamIndent;
         //MovRight( nLth );
      }

      nParam++;
      bPointer  = CompareAttributeToString( vSource, "Parameter", "PFlag", "Y" ) == 0;
      bUnsigned = CompareAttributeToString( vSource, "Parameter", "UFlag", "Y" ) == 0;
      GetAddrForAttribute( &szDataType, vSource, "Parameter", "DataType" );

      // Create prefix for parameter name.
      strcpy_s( szParam, zsizeof( szParam ), "");
      if (bFileC)
      {
         if ( bPointer && szDataType[0] != 'S' )
           strcat_s( szParam, zsizeof( szParam ), "p");

         if ( bUnsigned && szDataType[0] == 'N' || szDataType[0] == 'L' )
           strcat_s( szParam, zsizeof( szParam ), "u" );

         switch ( szDataType[0] )
         {
            case 'V':
               strcat_s( szParam, zsizeof( szParam ), "v");
               break;

            case 'N':
               strcat_s( szParam, zsizeof( szParam ), "n");
               break;

            case 'M':
               strcat_s( szParam, zsizeof( szParam ), "d");
               break;

            case 'Y':
               strcat_s( szParam, zsizeof( szParam ), "c");
               break;

            case 'L':
               strcat_s( szParam, zsizeof( szParam ), "l");
               break;

            case 'I':
               strcat_s( szParam, zsizeof( szParam ), "lpI");
               break;

            case 'O':
               // no prefix for void pointers
               break;

            default:
               strcat_s( szParam, zsizeof( szParam ), "sz");
         }
      }

      // create parameter name
      nLth = (zSHORT) zstrlen( szParam );
      GetStringFromAttribute( szParam + nLth, zsizeof( szParam ) - nLth, vSource, "Parameter", "ShortDesc" );
      UfCompressName( szParam + nLth, szParam + nLth, 32 - nLth, "", "BL", "", "B_", 1 );

      strcpy_s( szLine, zsizeof( szLine ), "");
      if ( bFileC )
      {
         // create prefix for "C"
         strcat_s( szLine, zsizeof( szLine ), "z");

         if ( bPointer && szDataType[0] != 'S' ) // not for String
           strcat_s( szLine, zsizeof( szLine ), "P");

         if ( bUnsigned )
         {
            switch ( szDataType[0] )
            {
//               case 'Y':
               case 'N':
               case 'L':
                  strcat_s( szLine, zsizeof( szLine ), "U");
                  break;
            }
         }
      }

      switch ( szDataType[0] )
      {
         case 'V':
            strcat_s( szLine, zsizeof( szLine ), "VIEW ");
            strcat_s( szLine, zsizeof( szLine ), szParam );

            if ( nParam == 1 &&
                 (szType[0] == 'A' || szType[0] == 'E' || szType[0] == 'T' || szType[0] == 'C' || szType[0] == 'O') )
            {
               zLONG ZKey;

               if ( !szLOD )
               {
                  GetIntegerFromAttribute( &ZKey, vSource, "LOD", szlZKey );
                  nRC = ActivateMetaOI_ByZKey( vSubtask, &vLOD, 0, zREFER_LOD_META,
                                               zSINGLE | zACTIVATE_ROOTONLY, ZKey, 0 );
                  if ( nRC < 0 )
                  {
                     MessagePrompt( vEdWrk, "ED0001",szlZeidonEditor,
                                    "Internal Error -- Couldn't find LOD to go with Source Meta", 1, 0, 0, 0 );
                     szLOD = "error";
                  }
                  else
                     GetAddrForAttribute( &szLOD, vLOD, "LOD", szlName );
               }

               if ( bFileC )
                  strcat_s( szLine, zsizeof( szLine ), " /* " );

               strcat_s( szLine, zsizeof( szLine ), " BASED ON LOD " );
               strcat_s( szLine, zsizeof( szLine ), szLOD );
               if ( bFileC )
                  strcat_s( szLine, zsizeof( szLine ), " */" );
            }

            break;

         case 'N':
            strcat_s( szLine, zsizeof( szLine ), "SHORT ");
            strcat_s( szLine, zsizeof( szLine ), szParam );
            break;

         case 'M':
            strcat_s( szLine, zsizeof( szLine ), "DECIMAL ");
            strcat_s( szLine, zsizeof( szLine ), szParam );
            break;

         case 'Y':
            strcat_s( szLine, zsizeof( szLine ), "CHAR ");
            strcat_s( szLine, zsizeof( szLine ), szParam );
            break;

         case 'L':
            bFileC ? strcat_s( szLine, zsizeof( szLine ), "LONG " )
                   : strcat_s( szLine, zsizeof( szLine ), "INTEGER " );
            strcat_s( szLine, zsizeof( szLine ), szParam );
            break;

         case 'O':
            bFileC ? strcat_s( szLine, zsizeof( szLine ), "VOID " )
                   : strcat_s( szLine, zsizeof( szLine ), "VOID " );
            strcat_s( szLine, zsizeof( szLine ), szParam );
            break;

         case 'I':
            bFileC ? strcpy_s( szLine, zsizeof( szLine ), "LPDOMAINDATA " )
                   : strcpy_s( szLine, zsizeof( szLine ), "STRING ( 32 ) " );
            strcat_s( szLine, zsizeof( szLine ), szParam );
            break;

         case 'A':
         case 'E':
         default:
            if ( bFileC )
            {
               if ( !bPointer && GetVMLConstChar( ) )
                  strcat_s( szLine, zsizeof( szLine ), "CPCHAR " );
               else
                  strcat_s( szLine, zsizeof( szLine ), "PCHAR " );
            }
            else
               strcat_s( szLine, zsizeof( szLine ), "STRING ( 32 ) " );

            strcat_s( szLine, zsizeof( szLine ), szParam );
            break;
      }

      csInsertBuffer += szLine;

      // Store parameters for CASE in VML function prototype.
      switch ( nParam )
      {
         case 1:
            if ( szType[0] == 'M' )
               strcpy_s( szParamCase, zsizeof( szParamCase ), szParam );

            break;

         case 2:
            if ( szType[0] == 'C' || szType[0] == 'O' )
               strcpy_s( szParamCase, zsizeof( szParamCase ), szParam );

            break;

         case 3:
            if ( szType[0] == 'E' )
               strcpy_s( szParamCase, zsizeof( szParamCase ), szParam );

            break;

         case 4:
            if ( szType[0] == 'A' )
               strcpy_s( szParamCase, zsizeof( szParamCase ), szParam );

            break;
      }

   }  // End FOR EACH Parameter

   if ( bFileC )
   {
      // Use dummy parameter, to avoid compiler warnings.
      if ( nParam == 0 )
         csInsertBuffer += "void";

      csInsertBuffer += " )\r\n";
   }
   else
   {
      csInsertBuffer += " )\r\n\r\n";
   }

   if ( bFileC == FALSE )
   {
      switch ( szType[0] )
      {
         case 'E':
            //MovRight( 3 );
            csInsertBuffer += szTab;
            csInsertBuffer +=  "CASE ";
            csInsertBuffer +=  szParamCase;
            csInsertBuffer +=  "\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zECE_ACCEPT:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zECE_ACCEPT\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zECE_CANCEL:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zECE_CANCEL\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zECE_CREATE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zECE_CREATE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zECE_DELETE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zECE_DELETE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zECE_EXCLUDE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zECE_EXCLUDE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zECE_INCLUDE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zECE_INCLUDE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "END  // case\r\n";
            break;

         case 'C':
         case 'O':
            csInsertBuffer += szTab;
            csInsertBuffer +=  "CASE ";
            csInsertBuffer +=  szParamCase;
            csInsertBuffer +=  "\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zOCE_ACTIVATE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zOCE_ACTIVATE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zOCE_ACTIVATE_EMPTY:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zOCE_ACTIVATE_EMPTY\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zOCE_COMMIT:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zOCE_COMMIT\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zOCE_DROPOI:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zOCE_DROPOI\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "END  // case\r\n";
            break;

         case 'A':
            csInsertBuffer += szTab;
            csInsertBuffer +=  "CASE ";
            csInsertBuffer +=  szParamCase;
            csInsertBuffer +=  "\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDERIVED_GET:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDERIVED_GET\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDERIVED_SET:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDERIVED_SET\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "END  // case\r\n";
            break;

         case 'M':
            csInsertBuffer += szTab;
            csInsertBuffer +=  "CASE ";
            csInsertBuffer +=  szParamCase;
            csInsertBuffer +=  "\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_SET_ATTRIBUTE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_SET_ATTRIBUTE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_GET_VARIABLE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_GET_VARIABLE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_COMPARE_ATTRIBUTE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_COMPARE_ATTRIBUTE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_GET_FIRST_TBL_ENT_FOR_ATTR:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_GET_FIRST_TBL_ENT_FOR_ATTR\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_GET_NEXT_TBL_ENT_FOR_ATTR:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_GET_NEXT_TBL_ENT_FOR_ATTR\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_SET_ATTRIBUTE_VALUE_NEXT:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_SET_ATTRIBUTE_VALUE_NEXT\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_SET_ATTRIBUTE_VALUE_PREV:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_SET_ATTRIBUTE_VALUE_PREV\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_ADD_TO_ATTRIBUTE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_ADD_TO_ATTRIBUTE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_GET_COMPARE_VALUE:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_GET_COMPARE_VALUE\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "OF   zDME_VALIDATE_LPDATA:\r\n\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "     // end zDME_VALIDATE_LPDATA\r\n";
            csInsertBuffer += szTab;
            csInsertBuffer +=  "END  // case\r\n";
            break;

         case 'T':
         case 'G':
         case 'D':
         case 'L':
         default:
            csInsertBuffer +=  "\r\n";
            break;
      }
   }

   if ( bFileC )
   {
      strcpy_s( szLine, zsizeof( szLine ), "{\r\n" );
      if ( szReturnDataType[ 0 ] == 'O' || szReturnDataType[ 0 ] == 0 ) // empty data type handled as void
         strcat_s( szLine, zsizeof( szLine ), "\treturn;\r\n" );
      else
         strcat_s( szLine, zsizeof( szLine ), "\treturn( 0 );\r\n" );

      strcat_s( szLine, zsizeof( szLine ), "} // ");
      strcat_s( szLine, zsizeof( szLine ), szOperName );
      strcat_s( szLine, zsizeof( szLine ), "\r\n" );
   }
   else
   {
      strcpy_s( szLine, zsizeof( szLine ), "\r\nEND\r\n" );
   }

   csInsertBuffer += szLine;

   // insert a single string
   BufInsertStr( vSubtask, csInsertBuffer );
   if ( bFileC )
      BufInsertStr( vSubtask, "\r\n" );

   if ( vLOD )
      DropView( vLOD );

   return( 0 );
} // OperTemplate

// Operation: fnCursorInCommentOrQuote
// Returns:  TRUE if index is in comment or quotes.
zSHORT
fnCursorInCommentOrQuote( zVIEW vSubtask, long lLine, long lCol )
{
   CString csBuffer;
   LPSTR  szBuffer;
   zLONG  lReturnedBuffSize = MAX_TOKEN_LTH;
   zBOOL  bReturn = FALSE;

   bReturn = fnIsCommentAtIndex( vSubtask, lLine, lCol );

   // If cursor is not in a comment, check to see if it is in quotes.
   if ( bReturn == FALSE )
   {
      // Read line.
      szBuffer = csBuffer.GetBufferSetLength( lReturnedBuffSize );
      lReturnedBuffSize = EDT_GetTextFromLineOfIndex( vSubtask, szBuffer, lReturnedBuffSize, lLine );
      // in Case of an editor error
      if ( lReturnedBuffSize >= MAX_TOKEN_LTH )
      {
         lReturnedBuffSize++;
         szBuffer = csBuffer.GetBufferSetLength( lReturnedBuffSize );
         lReturnedBuffSize = EDT_GetTextFromLineOfIndex( vSubtask, szBuffer, lReturnedBuffSize, lLine );
      }

      csBuffer.ReleaseBuffer( );

      // Check to see if the original cursor position is inside quotes.  To
      // do this, we first go to the beginning of the line and then start
      // counting quotes until we get to the original cursor position.
      // Once we've done this, if the number of quotes is odd, then the
      // cursor is in quotes, otherwise it isn't.  This assumes that quoted
      // strings must be contained on one line e.g. they cannot be continued
      // on to multiple lines.

      // Reset the charactercount (lCol) relative to the begin of line.
      EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );

      // Set bReturn to false.  bReturn is an indicator that
      // specifies whether the last quote found is an open quote.
      bReturn = FALSE;
      for ( long l = 0;l < lReturnedBuffSize; l++ )
      {
         // If quote is before the original cursor position, then toggle
         // bReturn, otherwise break out of loop.
         if ( csBuffer.GetAt( l ) == '\"' )
            if ( l <= lCol )
               bReturn = !bReturn;
            else
               break;
      }
   }

   return( bReturn );

} // fnCursorInCommentOrQuote

// We're about to open a sub-window.  We need to name the subtask view for
// the the current editor so that the subwindow can retrieve it.
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_OpenSubwindow( zVIEW vSubtask )
{
   zVIEW vEdWrk;

   mGetWorkView( &vEdWrk, vSubtask );
   SetNameForView( vEdWrk, "__EditorSubtask", vSubtask, zLEVEL_TASK );
   return( 0 );
}

int
fnShowSubwindows( zVIEW  vSubtask )
{
   zSHORT nRC;
   zVIEW  vProfileXFER;

   // Call dialog op to indicate we're about to open some subwindows.
   TZEDFRMD_OpenSubwindow( vSubtask );

   mGetProfileView( &vProfileXFER, vSubtask );
   if ( vProfileXFER )
   {
      for ( nRC = SetCursorFirstEntity( vProfileXFER, szlSubwindow, 0 );
            nRC == zCURSOR_SET;
            nRC = SetCursorNextEntity( vProfileXFER, szlSubwindow, 0 ) )
      {
         zPCHAR pchWindowName;

         if ( CompareAttributeToString( vProfileXFER, szlSubwindow,
                                        szlSubwindowActive, "Y" ) != 0 )
            continue;

         GetAddrForAttribute( &pchWindowName, vProfileXFER, szlSubwindow, szlName );
         SetWindowActionBehavior( vSubtask, zWAB_StartOrFocusModelessSubwindow | zWAB_ProcessImmediateAction,
                                  szlTZEDFRMD, pchWindowName );
      }
   }

   // set Focus to Editor Window
// SetWindowState( vSubtask, zWINDOW_STATUS_SETFOCUS, TRUE );
   EDT_GotoWindow( vSubtask );
   return( 0 );

} // fnShowSubwindows


static zSHORT
CreateFileInfo( zVIEW    vSubtask,
                zPCHAR   pchName )

{
   zCHAR    szDateRaw[ 20 ];
   zCHAR    szDateFormatted[ 20 ];

   SysGetDateTime( szDateRaw, zsizeof( szDateRaw ) );
   UfFormatDateTime( szDateFormatted, zsizeof( szDateFormatted ), szDateRaw, "YYYY.DD.MM" );

   BufInsertStr( vSubtask, "////////////////////////////////////////////////////////////////////////////\r\n//\r\n// .Name:         " );
   BufInsertStr( vSubtask, pchName );
   BufInsertStr( vSubtask, ".c\r\n//\r\n// .Version:      1.0\r\n//\r\n// .Last change:  " );
   BufInsertStr( vSubtask, szDateFormatted );
   BufInsertStr( vSubtask, "\r\n//\r\n// .Description:  Zeidon operations\r\n//\r\n"
                           "////////////////////////////////////////////////////////////////////////////\r\n"
                           "// .Change notes\r\n//\r\n//  1.0  = New  " );
   BufInsertStr( vSubtask, szDateFormatted );
   BufInsertStr( vSubtask, " Zeidon\r\n//\r\n////////////////////////////////////////////////////////////////////////////\r\n\r\n\r\n" );

   BufInsertStr( vSubtask, "#define KZSYSSVC_INCL\r\n"
                           "#include <KZOENGAA.H>\r\n"
                           "#include <ZDRVROPR.H>\r\n"
                           "#ifdef __cplusplus\r\n"
                           "extern \"C\"\r\n"
                           "{\r\n"
                           "#endif\r\n"
                           "#include \"ZEIDONOP.H\"\r\n\r\n"
                           "#ifdef __cplusplus\r\n"
                           "}\r\n"
                           "#endif\r\n\r\n" );

   return( 0 );
} // CreateFileInfo

static zSHORT
CreateSourceFile( zVIEW    vSubtask,
                  zVIEW    vSource,
                  zBOOL    bCFile,
                  zPCHAR   szSourceFileEntityName )
{
   zVIEW    vTmp;
   zPCHAR   pchName;
   zLONG    lLine = 0, lCol = 0;
   zSHORT   nRC;

   EDT_SetCursorPositionByLineCol( vSubtask, 0, 0 );

   if ( bCFile )
   {
      // Create a "C" source header.
      GetAddrForAttribute( &pchName, vSource, szSourceFileEntityName, szlName );

      CreateFileInfo( vSubtask, pchName );

      // In c-files search for #ifdef __cplusplus (from end to begin)
      // to get the position where to insert new operation.
      static zCHAR szSearchString[] = "\\bifdef __cplusplus[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+";

      // Set cursor to the last line.
      MovEOF( );
      EDT_GetCursorPosition( vSubtask, &lLine, &lCol );

      // Something found so insert two blank lines and reposition the cursor
      // to one of the blank lines.
      if (EDT_FindTextPosition(vSubtask, szSearchString, &lLine, &lCol, FIND_DIRECTION_UP))
      {
         // Set cursor to begin of line
         EDT_GetPositionByIndex( vSubtask, &lLine, &lCol );
         EDT_SetCursorPositionByLineCol( vSubtask, lLine, 0 );
         BufInsertStr( vSubtask, "\r\n\r\n" );
         EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
         EDT_SetCursorPositionByLineCol( vSubtask, lLine - 1, lCol );
      }
   }

   CreateViewFromViewForTask( &vTmp, vSource, 0 );
   for ( nRC = SetCursorFirstEntity( vTmp, szlOperation, "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vTmp, szlOperation, "" ) )
   {
      OperTemplate( vSubtask, vTmp );
/*
      // reposition cursor for next insert
      if ( bCFile )
      {
         lLine = EDT_GetLineCount( vSubtask ) - 1;
         EDT_SetCursorPositionByLineCol( vSubtask, lLine, 0 );
         EDT_InsertItem( vSubtask, "\r\n\r\n", FALSE );
         lLine = EDT_GetLineCount( vSubtask ) - 1;
         EDT_SetCursorPositionByLineCol( vSubtask, lLine, 0 );
      }
*/
   } // End for each Operation

   DropView( vTmp );
   return( 0 );

} // CreateSourceFile

static zSHORT
CreateErrorMessage( zVIEW  vSubtask,
                    zPCHAR szMsgText )
{
   zVIEW      vProfileXFER;
   zPCHAR     pchInvokingTool;
   zCHAR      szComponentType[ 33 ];
   zCHAR      szMsg[ 100 ];

   mGetProfileView( &vProfileXFER, vSubtask );

   GetAddrForAttribute( &pchInvokingTool, vProfileXFER, szlED, "InvokingTool" );

   if ( zstrcmp( pchInvokingTool, "GO" ) == 0 )
      strcpy_s( szComponentType, zsizeof( szComponentType ), "Global Operation Group" );
   else
   if ( zstrcmp( pchInvokingTool, "DM" ) == 0 )
      strcpy_s( szComponentType, zsizeof( szComponentType ), "Domain Group" );
   else
   if ( zstrcmp( pchInvokingTool, "ZO" ) == 0 )
      strcpy_s( szComponentType, zsizeof( szComponentType ), "LOD" );
   else
      strcpy_s( szComponentType, zsizeof( szComponentType ), "Dialog" );

   strcpy_s( szMsg, zsizeof( szMsg ), "Cannot create " );
   strcat_s( szMsg, zsizeof( szMsg ), szMsgText );
   strcat_s( szMsg, zsizeof( szMsg ), ", because " );
   strcat_s( szMsg, zsizeof( szMsg ), szComponentType );
   strcat_s( szMsg, zsizeof( szMsg ), " is not checked out." );

   MessagePrompt( vSubtask, "ED0002", szlZeidonEditor,
                  szMsg,
                  FALSE, zBUTTONS_OK, 0, zICON_EXCLAMATION );
   return( 0 );
}

static zSHORT
GotoCurrentOperation( zVIEW    vSubtask,
                      zVIEW    vSource,
                      zPCHAR   szOperSrch,
                      zPCHAR   szMetaName,
                      zBOOL    bCFile )
{
   zLONG  lLine = 0;
   zLONG  lCol = 0;
   DWORD  dwTBEDTDefaultSearchBehavior = FIND_MATCH_CASE | FIND_WHOLE_WORD;
   zBOOL  bTextFound;

   EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );
   bTextFound = EDT_FindTextPosition( vSubtask, szOperSrch, &lLine, &lCol, dwTBEDTDefaultSearchBehavior );
   if ( bTextFound )
   {
      EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );
      TraceLine( "(xxx) Return from search line: %d  col: %d", lLine, lCol );

      // Skipping lines where the search text is part of a comment
      while ( fnIsCommentAtIndex( vSubtask, lLine, lCol ) && lLine > -1 ) // 1998.10.15  TMV check lLine
      {
         lLine++;
         EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );
         bTextFound = EDT_FindTextPosition( vSubtask, szOperSrch, &lLine, &lCol, dwTBEDTDefaultSearchBehavior );
         EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );
      }
   }

   // New operation code?
   if ( bTextFound == FALSE )
   {
      // set cursor to the last line
      MovEOF( );
      if ( bCFile )
      {
         // in c-files search for #ifdef __cplusplus (from end to begin)
         // to get the position where to insert new operation
         GetPositionForNextInsert( vSubtask, &lLine, &lCol );
      }

      // if file read only, do not create operation
      if ( EDT_IsReadOnly( vSubtask ) )
         CreateErrorMessage( vSubtask, "Operation" );
      else
      {
         OperTemplate( vSubtask, vSource );
         EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
         zLONG lLineCnt = EDT_GetLineCount( vSubtask ) - 4;
         if (lLine < lLineCnt)
         {
            MovUp( -3 );
            EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
         }
      }
   }
   else
   {
      // Find end of parm list.
      EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
   }

// EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
// sprintf_s( szMetaName, zsizeof( szMetaName ), "(%ld,%ld)", lLine + 1, lCol + 1 );

   // Move cursor to beginning of next line.
   EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );

// MB_SetMessage( vSubtask, LINECOL_DIL, szMetaName );
   return( 0 );

} //GotoCurrentOperation

static zSHORT
SetTargetExecutableName( zVIEW  vSource,
                         zVIEW  vEdWrk,
                         zPCHAR pchInvokingTool,
                         zPCHAR pchMetaName,
                         zPLONG plMetaType )
{
   // Global Operations
   if ( zstrcmp( pchInvokingTool, "GO" ) == 0 )
   {
      SetAttributeFromAttribute( vEdWrk, szlBuffer, "TargetExecutableName",
                                 vSource, "GlobalOperationGroup",
                                 "DomainAndGlobalOpGroupName" );
      SetAttributeFromInteger( vEdWrk, szlBuffer, szlMetaType, zREFER_GOPGRP_META );
      *plMetaType = zSOURCE_GOPGRP_META;
      GetStringFromAttribute( pchMetaName, 33, vSource, "GlobalOperationGroup", "Name" );
   }
   else
   // Domains
   if ( zstrcmp( pchInvokingTool, "DM" ) == 0 )
   {
      SetAttributeFromAttribute( vEdWrk, szlBuffer, "TargetExecutableName",
                                 vSource, "DomainGroup", "DomainAndGlobalOpGroupName" );
      SetAttributeFromInteger( vEdWrk, szlBuffer, szlMetaType, zREFER_DOMAINGRP_META );
      *plMetaType = zSOURCE_DOMAINGRP_META;
      GetStringFromAttribute( pchMetaName, 33, vSource, "DomainGroup", "Name" );
   }
   else
   // LOD's
   if ( zstrcmp( pchInvokingTool, "ZO" ) == 0 )
   {
      SetAttributeFromAttribute( vEdWrk, szlBuffer, "TargetExecutableName",
                                 vSource, "LOD", "DLL_Name" );
      SetAttributeFromInteger( vEdWrk, szlBuffer, szlMetaType, zREFER_LOD_META );
      *plMetaType = zSOURCE_LOD_META;
      GetStringFromAttribute( pchMetaName, 33, vSource, "LOD", "Name" );
   }
   else
   if ( zstrcmp( pchInvokingTool, "WD" ) == 0 ||
        zstrcmp( pchInvokingTool, "PN" ) == 0 )
   {
      SetAttributeFromAttribute( vEdWrk, szlBuffer, szlSourceFileName,
                                 vSource, szlSourceFile, szlName );

      SetAttributeFromAttribute( vEdWrk, szlBuffer, "TargetExecutableName",
                                 vSource, "Dialog", "DLL_Name" );
      SetAttributeFromInteger( vEdWrk, szlBuffer, szlMetaType, zREFER_DIALOG_META );

      // If there is no DLL name for the window, then assume the DLL name is
      // the window name.
      if ( CompareAttributeToString( vEdWrk, szlBuffer, "TargetExecutableName",
                                     "" ) == 0 )
      {
         SetAttributeFromAttribute( vEdWrk, szlBuffer, "TargetExecutableName",
                                    vSource, "Dialog", "Tag" );
      }

      *plMetaType = zSOURCE_DIALOG_META;
      GetStringFromAttribute( pchMetaName, 33, vSource, "Dialog", "Tag" );
   }

   return( 0 );

} // SetTargetExecutableName

static zSHORT
CheckFileAttribute( zPCHAR  pchFileName,
                    zPBOOL  pbReadOnly )
{
   *pbReadOnly = FALSE;
   DWORD dwAttribute = ::GetFileAttributes(pchFileName);
   if (dwAttribute == 0xFFFFFFFF) //call of function GetFileAttributes failed
   {
      LPSTR lpMsgBuf = NULL;
      MessageBox( NULL, pchFileName, "File Not Found", MB_OK | MB_ICONINFORMATION );
   }
   else
   {
      if ( dwAttribute & FILE_ATTRIBUTE_READONLY )
         *pbReadOnly = TRUE;
   }

   return( 0 );

} // CheckFileAttribute

static zSHORT
CreateFileName( zVIEW   vTaskLPLR,
                zVIEW   vSource,
                zPCHAR  pchFileName,
                zLONG   lMaxLth,
                zPCHAR  pchInvokingTool,
                zPCHAR  pchSourceFileEntityName,
                zLONG   lEntityNameLth,
                zPBOOL  pbFileExists )
{
   zCHAR szFileName[ zMAX_FILENAME_LTH + 1 ];

   //
   // Create the name of the file.
   //
   if ( zstrcmp( pchInvokingTool, "GO" ) == 0 )
      strcpy_s( pchSourceFileEntityName, lEntityNameLth, "GlobalOperationGroup" );
   else
   if ( zstrcmp( pchInvokingTool, "DM" ) == 0 )
      strcpy_s( pchSourceFileEntityName, lEntityNameLth, "DomainGroup" );
   else
      strcpy_s( pchSourceFileEntityName, lEntityNameLth, szlSourceFile );

   // Get the source dir from the lplr view.
   GetStringFromAttribute( pchFileName, lMaxLth, vTaskLPLR, szlLPLR, szlPgmSrcDir );
   SysAppendcDirSep( pchFileName );

   // Get the subdir from the source file entity.  If GetString... returns < 0
   // then the subdir attribute is null, so nothing was retrieved.  If subdir
   // is set, then we need to add a '\'.
   if ( GetStringFromAttribute( pchFileName + zstrlen( pchFileName ), lMaxLth - zstrlen( pchFileName ),
                                vSource, pchSourceFileEntityName, szlSubdirectory ) >= 0 )
   {
      SysAppendcDirSep( pchFileName );
   }

   // Get the file name and extension.
   GetStringFromAttribute( pchFileName + zstrlen( pchFileName ), lMaxLth - zstrlen( pchFileName ),
                           vSource, pchSourceFileEntityName, szlName );
   strcat_s( pchFileName, zMAX_FILENAME_LTH + 1, "." );
   GetStringFromAttribute( pchFileName + zstrlen( pchFileName ), lMaxLth - zstrlen( pchFileName ),
                           vSource, pchSourceFileEntityName, szlExtension );
   strcpy_s( szFileName, zsizeof( szFileName ), pchFileName );
   SysConvertEnvironmentString( pchFileName, lMaxLth, szFileName );

   if ( SysOpenFile( vTaskLPLR, pchFileName, COREFILE_EXIST ) == -1 )
   {
      zLONG hFile;

      // Create an empty file.
      *pbFileExists = FALSE;
      if ( !MiGetUpdateForView( vSource ) )
         return( -1 );
      else
      {
         hFile = SysOpenFile( vTaskLPLR, pchFileName, COREFILE_CREATE );
         SysCloseFile( vTaskLPLR, hFile, 0 );
      }
   }
   else
      *pbFileExists = TRUE;

   return( 0 );

} // CreateFileName

// Sets the line,col DIL message.  Since the line,col values are 0-based we add 1 before displaying them.
// Also checks to see if the file has been changed.
zSHORT
InitSession( zVIEW  vSubtask )
{
   zPCHAR   pchOperName = 0;
   zPCHAR   pchInvokingTool = 0;
   zCHAR    szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR    szSourceFileEntityName[ 33 ];
   zCHAR    szOperSrch[ 256 ];
   zLONG    lMetaType = 0;
   zCHAR    szMetaName[ 33 ];
   zBOOL    bFileExists = FALSE;
   zBOOL    bCFile = FALSE;
   zVIEW    vEdWrk=0;
   zVIEW    vSource = 0;
   zVIEW    vTaskLPLR = 0;
   zVIEW    vProfileXFER = 0;
   zLONG    lLine = -1;
   zBOOL    bReadOnly = FALSE;

   // Flag which says that the Object is created by Menu-Command 'File New'.
   EDT_WantKeystrokes( vSubtask, TRUE );
   mGetWorkView( &vEdWrk, vSubtask );
   mGetProfileView( &vProfileXFER, vSubtask );
   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   GetAddrForAttribute( &pchInvokingTool, vProfileXFER, szlED, "InvokingTool" );

   // Retrieve the source file name and open a buffer.
   GetViewByName( &vSource, "METAOPERATIONS", vSubtask, zLEVEL_TASK );
   if ( vSource )
   {
      // Clean up a little by dropping the name.
      DropNameForView( vSource, "METAOPERATIONS", vSubtask, zLEVEL_TASK );
      if ( CreateFileName( vTaskLPLR, vSource, szFileName, zsizeof( szFileName ), pchInvokingTool,
                           szSourceFileEntityName, zsizeof( szSourceFileEntityName ), &bFileExists ) < 0 )
      {
         CreateErrorMessage( vSubtask, "Source File" );
         return( -1 );
      }
   }
   else
   {
      // If there is no vSource, the editor is invoked by another editor instance.
      // There is no meta view so we must be opening the current file using the Open/File menu command.
      // Get the file name.
      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vEdWrk, szlEditor, "OpenFileName" );
      if ( CompareAttributeToString( vEdWrk, szlEditor, "OpenReadOnly", "Y" ) == 0 )
      {
         bReadOnly = TRUE;
      }

      SetAttributeFromString( vEdWrk, szlEditor, "OpenReadOnly", "" );
   }

   // Check whether the file is marked as readonly.
   CheckFileAttribute( szFileName, &bReadOnly );

   CreateEntity( vEdWrk, szlBuffer, zPOS_LAST );
   SetAttributeFromString( vEdWrk, szlBuffer, szlFileName, szFileName );
   SetMatchingAttributesByName( vEdWrk, szlBuffer, vProfileXFER, "ED", zSET_ALL );

   EDT_OpenObject( vSubtask, szFileName );
   if ( bReadOnly )
   {
      // Set file read only.
      EDT_ReadOnlyMode( vSubtask, bReadOnly );
      SetAttributeFromString( vEdWrk, szlBuffer, szlReadOnly, "Y" );
      MB_SetMessage( vSubtask, MAIN_DIL, "File is write protected");
   }

   // If vSource is 0 then we must have been started via a File/Open command and therefore
   // we don't have a meta.  We've done all we need to do ... so exit.
   if ( vSource == 0 )
   {
      // Extension checking is the only way to find out whether syntax coloring can occur.
      CString csExtension = szFileName;
      int iPoint = csExtension.ReverseFind( '.' );
      CString csHelp = csExtension.Mid( iPoint + 1 );
      if ( csHelp.CompareNoCase( "VML" ) == 0 )
      {
         bCFile = FALSE;
         EDT_ZeidonSyntaxOn( vSubtask );
      }
      else
      {
         bCFile = TRUE;
         EDT_SyntaxOff( vSubtask );  // no syntax coloring in C-Sources
      }

      return( 0 );
   }

   SetAttributeFromInteger( vEdWrk, szlBuffer, szlSourceViewID, (zLONG) vSource );

   // Set the target executable name from the source meta.
   // Also set the MetaType and MetaName to be used further on.
   SetTargetExecutableName( vSource, vEdWrk, pchInvokingTool, szMetaName, &lMetaType );

   // If the source meta view is not updateable, then make sure that the edit buffer is not
   // updateable.  There is a chance that the souce meta properties conflict with the readonly
   // attribute setting of the file itself (checked above).
   if ( bReadOnly == FALSE )
   {
      if ( MiGetUpdateForView( vSource ) )
      {
         // Source view is updateable
         SetAttributeFromString( vEdWrk, szlBuffer, szlActiveStatus, "Y" );
         // set ReadOnly off;
         EDT_ReadOnlyMode( vSubtask, FALSE );
      }
      else
      {
         // Source view is NOT updateable
         SetAttributeFromString( vEdWrk, szlBuffer, szlActiveStatus, "N" );
         // ReadOnly on;
         EDT_ReadOnlyMode( vSubtask, TRUE );
      }
   }

   // Set the LanguageType for the current buffer.
   SetAttributeFromAttribute( vEdWrk, szlBuffer, szlLanguageType,
                              vSource, szSourceFileEntityName, szlLanguageType );

   // If source file is of type "VML" || "C" ...
   if  ( CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) == 0 )
   {
      bCFile = FALSE;
      EDT_ZeidonSyntaxOn( vSubtask );
   }
   else
   if  ( CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlC_File ) == 0 )
   {
      bCFile = TRUE;
      EDT_ZeidonSyntaxOn( vSubtask );
   }
   else
   {
      bCFile = FALSE;
      EDT_SyntaxOff( vSubtask );  // no syntax coloring otherwise
   }

   // If the file did not previously exist or if it's empty then init all operations in Meta.
   lLine = EDT_GetLineCount( vSubtask ) - 1;
   if ( bFileExists == FALSE || lLine <= 0 )
      CreateSourceFile( vSubtask, vSource, bCFile, szSourceFileEntityName );

   // Determine if the operation is in the file or we should create a template
   GetAddrForAttribute( &pchOperName, vSource, szlOperation, szlName );
// sprintf_s( szOperSrch, zsizeof( szOperSrch ), "\\bOPERATION[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+%s[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]*(", pchOperName );
   sprintf_s( szOperSrch, zsizeof( szOperSrch ), "%s", pchOperName );

   GotoCurrentOperation( vSubtask, vSource, szOperSrch, szMetaName, bCFile );
   return( 0 );

} // InitSession

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_ZeidonMenuSelected( zVIEW vSubtask )
{
   zVIEW      vEdWrk;

   mGetWorkView( &vEdWrk, vSubtask );

   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) == 0 )
   {
      // We're editing a VML file so enable certain items.
      SetOptionState( vSubtask, "ParseVML", zCONTROL_STATUS_ENABLED, TRUE );
      SetOptionState( vSubtask, "GenerateC",  zCONTROL_STATUS_ENABLED, TRUE );
   }
   else
   {
      // We're editing something that is not a VML file so disable items.
      SetOptionState( vSubtask, "ParseVML", zCONTROL_STATUS_ENABLED, FALSE );
      SetOptionState( vSubtask, "GenerateC", zCONTROL_STATUS_ENABLED, FALSE );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_OnSize( zVIEW vSubtask )
{
   return EDT_OnSize( vSubtask );
}

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_InitMenu( zVIEW vSubtask )
{
   zVIEW    vEdWrk;
   zBOOL    bEnable   = FALSE;
   zBOOL    bReadOnly = TRUE;

   mGetWorkView( &vEdWrk, vSubtask );

   if ( EDT_IsReadOnly( vSubtask ) )
   {
      bReadOnly = FALSE;
   }

   BOOL bCanCopy  = EDT_CanCopy( vSubtask );
   BOOL bCanPaste = EDT_CanPaste( vSubtask );
   BOOL bCanUndo  = EDT_CanUndo( vSubtask );
   BOOL bCanRedo  = EDT_CanRedo( vSubtask );

   SetOptionState( vSubtask, "SaveFile", zCONTROL_STATUS_ENABLED, bReadOnly );
   SetOptionState( vSubtask, "EditReplace", zCONTROL_STATUS_ENABLED, bReadOnly );

   SetOptionState( vSubtask, "EditCopy", zCONTROL_STATUS_ENABLED, bCanCopy );
   SetOptionState( vSubtask, "EditUndo", zCONTROL_STATUS_ENABLED, bReadOnly ? bCanUndo : FALSE );
   SetOptionState( vSubtask, "EditRedo", zCONTROL_STATUS_ENABLED, bReadOnly ? bCanRedo : FALSE );
   SetOptionState( vSubtask, "EditCut",  zCONTROL_STATUS_ENABLED, bReadOnly ? bCanCopy : FALSE );
   SetOptionState( vSubtask, "EditPaste", zCONTROL_STATUS_ENABLED, bReadOnly ? bCanPaste : FALSE );
   SetOptionState( vSubtask, "EditDelete", zCONTROL_STATUS_ENABLED, bReadOnly ? bCanCopy : FALSE );
   SetOptionState( vSubtask, "EditSelectAll", zCONTROL_STATUS_ENABLED, EDT_GetLineCount( vSubtask ) > 0 );

   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) == 0 )
   {
      bEnable = TRUE;
   }

   SetOptionState( vSubtask, "ParseVML", zCONTROL_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "GenerateC", zCONTROL_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "EntityInsert", zCONTROL_STATUS_ENABLED, bEnable );
   SetOptionState( vSubtask, "KeyWordInsert", zCONTROL_STATUS_ENABLED, bEnable );

   return( 0 );
}

// When the editor window gets focus we need to do a few things:
// o Check to see if the editor work view is available yet.  If not, then skip the rest of the function.
// o Lastly, set focus to the editor control.
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_ReceiveFocus( zVIEW vSubtask )
{
#if 1
   zVIEW    vEdWrk;

   TraceLineS( "Setting focus to control1: ", EDIT_CONTROL_NAME );
   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
      return( 0 );

   TraceLineS( "Setting focus to control2: ", EDIT_CONTROL_NAME );
   SetFocusToCtrl( vSubtask, EDIT_CONTROL_NAME );
#endif
   return( 0 );
}

// The user just typed a space.  Check to see if we should perform command completion.
// Returns: TRUE  - Command completion performed.
//          FALSE - Nothing done.
//
zSHORT LOCALOPER
fnCommandCompletion( zVIEW vSubtask )
{
   zVIEW    vEdWrk;
   zVIEW    vProfileXFER;
   zLONG    lLine = 0;
   zLONG    lCol = 0;
   zLONG    lLth = 0;
   zCHAR    szBuffer[ 300 ];
   zPCHAR   pchToken;
   zCHAR    szFileName[ MAX_PATH + 1 ];
   zCHAR    chType;
   CString  csHelp;

   mGetWorkView( &vEdWrk, vSubtask );

   // If current File is a C-Source then don't do command completion.
   zmemset( szFileName, 0, MAX_PATH + 1 );
   zmemset( szFileName, ' ', MAX_PATH );
   chType = EDT_GetObjectName( vSubtask, szFileName, MAX_PATH );

   CString csExtension = szFileName;
   int iPoint = csExtension.ReverseFind( '.' );
   csHelp = csExtension.Mid( iPoint + 1 );
   if ( csHelp.CompareNoCase( "VML" ) != 0 )
   {
      return( FALSE );
   }

   EDT_GetCursorPosition( vSubtask, &lLine, &lCol );

   // No command completion if we are in the first col.
   if ( lCol == 0 )
   {
      return( FALSE );
   }

   // If we're in a comment or quote then don't do command completion.
   if ( fnCursorInCommentOrQuote( vSubtask, lLine, lCol ) )
      return( FALSE );

   zmemset( szBuffer, 0, zsizeof( szBuffer ) );
   lLth = EDT_GetActualTextLine( vSubtask, szBuffer, zsizeof( szBuffer ), lLine );

   // If the previous character to the space that was just entered is also a space then skip command completion.
   if ( lLth < 2 || isspace( szBuffer[ lCol - 1 ]) )
      return( FALSE );

   // Check to see if anything comes after the space.  If there is and it's not a white space then skip command completion.
   if ( lLth > lCol + 1 )
   {
      for ( pchToken = &szBuffer[ lCol + 1 ]; pchToken < szBuffer + lLth && *pchToken; pchToken++ )
      {
         if ( isspace( *pchToken ) == FALSE )
            return( FALSE );
      }
   }

   // Change the ' ' to a null-term.
   szBuffer[ lCol ] = 0;

   // Find the last token before what was the space.
   for ( pchToken = szBuffer + lCol - 1;
         pchToken >= szBuffer && !isspace( *pchToken );
         pchToken--)
   {
      // Nothing needs to be done here.
   }

   // Set pchToken to point to the first char of the token.
   pchToken++;

   // Create a temp view so we don't mess up cursors.
   mGetProfileView( &vProfileXFER, vSubtask );
   CreateViewFromViewForTask( &vProfileXFER, vProfileXFER, 0 );

   // Now try to find the token in the list of commands.
   if ( SetCursorFirstEntityByString( vProfileXFER, "VML_Text", "CC_Code",
                                      pchToken, 0 ) != zCURSOR_SET )
   {
      DropView( vProfileXFER );     // Drop temp copy of vProfileXFER.
      return( FALSE );              // Code not found so exit.
   }

   // Check to see if we only perform command completion for this token if it is the first token on the line.
   if ( CompareAttributeToString( vProfileXFER, "VML_Text", "CC_FirstChar", "Y" ) == 0 )
   {
      zPCHAR pch;

      // Scan the current line before the token to see if there is a non-space.
      // If there is then we don't perform command completion ... so exit.
      for ( pch = pchToken - 1; pch >= szBuffer; pch-- )
      {
         if ( isspace( *pch ) == FALSE )
         {
            DropView( vProfileXFER );  // drop temp copy of vProfileXFER.
            return( FALSE );
         }
      }
   }

   // OK...we are about to do command completion so we need to remove the token from the current line.
   EDT_DeleteTextRange( vSubtask, lLine, lCol - zstrlen( pchToken ), lLine, lCol );
   csHelp = pchToken;
   EDT_SelectItem( vSubtask, lLine + 1, 0, csHelp );
   EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol - zstrlen( pchToken ) );

   // Call operation to insert currently selected keyword in profile OI.
   fnInsertVML_Text( vSubtask, vEdWrk, vProfileXFER );

   DropView( vProfileXFER );     // drop temp copy of vProfileXFER.
   return( TRUE );

} // fnCommandCompletion

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_Keystroke( zVIEW vSubtask )
{
#if 0  // we only get here if the character is a space
   zCTRL_EVENT *pCE;
   zSHORT      nRC;
   zCHAR       cKey;
   zVIEW       vEdWrk;
   zVIEW       vProfileXFER;

   //TraceLineS( "(tzedfrmd)", "Keystroke" );

   mGetWorkView( &vEdWrk, vSubtask );
   mGetProfileView( &vProfileXFER, vSubtask );

   pCE = (zCTRL_EVENT *) GetActionParameters( vSubtask );
   cKey = (zCHAR) pCE->m_pEvent->m_pDispParams->rgvarg[ 1 ].iVal;

   // Check to see if the key is a space.  If it is then we might need to
   // perform command completion.
   if ( cKey == ' ' )
      nRC = fnCommandCompletion( vSubtask );
      pCE->m_ulRC = 0x00000001;

   pCE->m_ulRC = 0x00000001;
   return( 0 );
#else
   return( fnCommandCompletion( vSubtask ) );
#endif
}

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_LineChange( zVIEW vSubtask )
{
   zCTRL_EVENT *pCE;
   zLONG       lLine, lCol;
   zCHAR       szData[ 30 ];

// TraceLineS( "(tzedfrmd)", "LineChange" );
   szData[ 0 ] = 0;
   pCE = (zCTRL_EVENT *) GetActionParameters( vSubtask );
   if ( pCE->m_pEvent->m_pDispParams->cArgs >= 2 )
   {
      // 1998.7.15   TMV
      // Get parameters in reverse order.
      // Refer to typelib for more information about the event interface
      // of the current control.
      lLine = pCE->m_pEvent->m_pDispParams->rgvarg[ 1 ].iVal;
      lCol  = pCE->m_pEvent->m_pDispParams->rgvarg[ 0 ].iVal;
      sprintf_s( szData, zsizeof( szData ), "(%ld,%ld)", lLine, lCol);
   }

   MB_SetMessage( vSubtask, LINECOL_DIL, szData );

   lLine = EDT_IsFileChanged( vSubtask );
   if ( lLine )
      strcpy_s( szData, zsizeof( szData ), "*" );
   else
      strcpy_s( szData, zsizeof( szData ), "" );

   MB_SetMessage( vSubtask, FILECHANGED_DIL, szData );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
PostBuild( zVIEW vSubtask )
{
   zVIEW   vTaskLPLR;
// zVIEW   vProfileXFER;
   zVIEW   vEdWrk;
   zCHAR   szMsg[ 300 ];

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
// mGetProfileView( &vProfileXFER, vSubtask );
// if ( vProfileXFER )
// {
//    // Set a couple of attributes to NULL.  We don't need them anymore and someday we'll want to get rid of them.
//    SetAttributeFromString( vProfileXFER, "ED", "SearchFlags", "" ); dks 2016.02.15
//    SetAttributeFromString( vProfileXFER, "ED", "FontString", "" );
// }

   // First thing - create an editor work object instance.
   GetViewByName( &vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_SUBTASK );

   if ( vEdWrk == 0 )
   {
      GetViewByName( &vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_TASK );
      if ( vEdWrk == 0 )
      {
         ActivateEmptyObjectInstance( &vEdWrk, szlTZEDWRKO, vTaskLPLR, zSINGLE );

         // Create empty root.
         CreateEntity( vEdWrk, "Editor", zPOS_FIRST );
         SetNameForView( vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_TASK );
      }

      CreateViewFromViewForTask( &vEdWrk, vEdWrk, 0 );
      SetNameForView( vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_SUBTASK );
   }

   // If InitSession returns a value of 1,the editor has been used for
   // dropping an operation from source code.  If so all the work is done.
   if ( InitSession( vSubtask ) == 0 )
   {
      SetAttributeFromInteger( vEdWrk, szlBuffer, "vSubtask", (zLONG) vSubtask );
      GetStringFromAttribute( szMsg, zsizeof( szMsg ), vEdWrk, szlBuffer, szlFileName );
      // Set checked out state in title
      if ( CompareAttributeToString( vEdWrk, szlBuffer, szlActiveStatus, "N" ) == 0 )
         strcat_s( szMsg, zsizeof( szMsg ), " < not checked out >" );
      else
      if ( CompareAttributeToString( vEdWrk, szlBuffer, szlReadOnly, "Y" ) == 0 )
         strcat_s( szMsg, zsizeof( szMsg ), " < Read-Only mode >" );

      SetWindowCaptionTitle( vSubtask, "Zeidon Editor", szMsg );
      fnShowSubwindows( vSubtask );
   }
   else
   {
      // Operation dropped ... go back to the parent.
      DropView( vEdWrk );
      GetViewByName( &vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_TASK );
      if ( vEdWrk )
         DropView( vEdWrk );

      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParentWithRefresh, "", "" );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////

zSHORT g_nTrace;

zOPER_EXPORT zSHORT OPERATION
PreBuild( zVIEW vSubtask )
{
   SetWindowState( vSubtask, zWINDOW_STATUS_VISIBLE, FALSE );
   g_nTrace = SetActionTrace( vSubtask, 0 );
   return( 0 );
} // PreBuild

zOPER_EXPORT zSHORT OPERATION
SystemClose( zVIEW vSubtask )
{
   zVIEW      vEdWrk = 0;
   zVIEW      vLastEdWrk = 0;
   zVIEW      vProfileXFER = 0;

   if ( EDT_IsFileChanged( vSubtask ) )
   {
      if ( fnSaveWithCheckForParse( vSubtask ) < 0 )
         return( -1 );
   }

   // Are there any Subwindows of the control which have to be closed.
   if ( EDT_CloseSubWindow( vSubtask ) )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( 0 );
   }

   ZSubtask   *pZSubtask;
   ZMapAct    *pzma;

   GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME );
   if ( pZSubtask->m_pZMIXCtrl )
      pZSubtask->m_pZMIXCtrl->RemoveNode( pzma );

   // Save the current options values in the editor to the profile.
   mGetProfileView( &vProfileXFER, vSubtask );
   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk )
   {
      if ( vProfileXFER )
         SetMatchingAttributesByName( vProfileXFER, "ED", vEdWrk, szlBuffer, zSET_ALL );

      // Since we're closing the editor delete the buffer entry.
      DeleteEntity( vEdWrk, "Buffer", zREPOS_NEXT );

      // If an other Editor open, do not drop vEdWrk
      GetViewByName( &vLastEdWrk, "__EditorSubtask", vSubtask, zLEVEL_TASK );
      if ( vLastEdWrk == 0 )
         DropView( vEdWrk );
   }

   if ( g_nTrace )
      SetActionTrace( vSubtask, g_nTrace );

   SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent | zWAB_ProcessImmediateAction | zWAB_ProcessImmediateReturn, 0, 0 );

   return( 0 );

} // SystemClose

// Save the current position of the subwindow in the Profile object.
zSHORT
fnSaveSubwindowPosition( zVIEW  vSubtask,
                         zPCHAR pchName )
{
   zSHORT nRC;
   zVIEW  vProfileXFER;
   zLONG  lPosX, nPosY;
   zVIEW  vEdWrk;
   zPCHAR pchWindowActive;

   // If we can't find the editor work view for the parent editor subtask
   // then we are shutting down the editor (as opposed to just closing the
   // subwindow).

   // Get the work view for the current subtask.
   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
   {
      // We're closing down the editor so set flag so that we the subwindow
      // comes back up when we open the next editor.
      pchWindowActive = "Y";
   }
   else
      pchWindowActive = "N";

   mGetProfileView( &vProfileXFER, vSubtask );
   if ( vProfileXFER )
   {
      nRC = SetCursorFirstEntityByString( vProfileXFER, szlSubwindow, szlName, pchName, "" );
      if ( nRC != zCURSOR_SET )
      {
         CreateEntity( vProfileXFER, szlSubwindow, zPOS_LAST );
         SetAttributeFromString( vProfileXFER, szlSubwindow, szlName, pchName );
      }
   }

   GetCtrlPosition( vSubtask, 0, &lPosX, &nPosY, TRUE );
   SetAttributeFromInteger( vProfileXFER, szlSubwindow, szlPosX, lPosX );
   SetAttributeFromInteger( vProfileXFER, szlSubwindow, szlPosY, nPosY );

   GetCtrlSize( vSubtask, 0, &lPosX, &nPosY, TRUE );
   SetAttributeFromInteger( vProfileXFER, szlSubwindow, szlWidth, lPosX );
   SetAttributeFromInteger( vProfileXFER, szlSubwindow, szlHeight, nPosY );

   SetAttributeFromString( vProfileXFER, szlSubwindow, szlSubwindowActive, pchWindowActive );
   return( 0 );
}

// Set the position of a subwindow determined by vSubtask.
// Return TRUE  if window was repositioned,
//        FALSE if window was not.
zSHORT
fnSetSubwindowPosition( zVIEW  vSubtask,
                        zPCHAR szName )
{
   zSHORT nRC;
   zVIEW  vProfileXFER;

   mGetProfileView( &vProfileXFER, vSubtask );
   nRC = SetCursorFirstEntityByString( vProfileXFER, szlSubwindow, szlName, szName, 0 );
   if ( nRC != zCURSOR_SET )
      return( FALSE );

// Currently handled by 32-bit driver.
#ifndef __WIN32__
   {
      zLONG  lPosX, lPosY;

      GetIntegerFromAttribute( &lPosX, vProfileXFER, szlSubwindow, szlPosX );
      GetIntegerFromAttribute( &lPosY, vProfileXFER, szlSubwindow, szlPosY );
      SetCtrlPosition( vSubtask, 0, lPosX, lPosY, TRUE );

      GetIntegerFromAttribute( &lPosX, vProfileXFER, szlSubwindow, szlWidth );
      GetIntegerFromAttribute( &lPosY, vProfileXFER, szlSubwindow, szlHeight );
      SetCtrlSize( vSubtask, 0, (zSHORT) lPosX, (zSHORT) lPosY, TRUE );

   }
#endif

   return( TRUE );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_Postbuild( zVIEW vSubtask )
{
   zVIEW  vEdWrk;
   zBOOL  bReadOnly = TRUE;
   zVIEW  vParent;

   GetParentWindow( &vParent, vSubtask );
   if ( vParent )
   {
      mGetWorkView( &vEdWrk, vParent );

      if ( CompareAttributeToString( vEdWrk, szlBuffer, szlReadOnly, "Y" ) == 0 ||
           CompareAttributeToString( vEdWrk, szlBuffer, szlActiveStatus, "N" ) == 0 )
      {
         bReadOnly = FALSE;
      }
   }

   SetOptionState( vSubtask, "PasteObjectName", zCONTROL_STATUS_ENABLED, bReadOnly );
   SetOptionState( vSubtask, "PasteVOR_Name", zCONTROL_STATUS_ENABLED, bReadOnly );
   EnableAction( vSubtask, "PasteView", bReadOnly );
   EnableAction( vSubtask, "PasteEQ", bReadOnly );
   EnableAction( vSubtask, "PasteEQ_Quoted", bReadOnly );
   EnableAction( vSubtask, "PasteAQ", bReadOnly );
   EnableAction( vSubtask, "PasteAQ_Quoted", bReadOnly );

   // Get the subtask view for the parent editor window and give it another
   // name at the current subtask level so we can easily retrieve it.
   GetViewByName( &vEdWrk, "__EditorSubtask", vSubtask, zLEVEL_TASK );
   SetNameForView( vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_SUBTASK );

   fnSetSubwindowPosition( vSubtask, szlObjectSelAQ );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_Close( zVIEW vSubtask )
{
   fnSaveSubwindowPosition( vSubtask, szlObjectSelAQ );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_RefreshAEQ( zVIEW vSubtask )
{
   RefreshCtrl( vSubtask, "ViewList" );
   RefreshCtrl( vSubtask, "EntityList" );
   RefreshCtrl( vSubtask, "AttributeList" );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_RefreshAEQ_AttrList( zVIEW vSubtask )
{
   RefreshCtrl( vSubtask, "AttributeList" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_ClearViews( zVIEW vSubtask )
{
   zVIEW  vEdWrk;
   zSHORT nRC;

   mGetWorkView( &vEdWrk, vSubtask );
   nRC = SetCursorFirstEntity( vEdWrk, "View", "" );
   while ( nRC == zCURSOR_SET )
      nRC = DeleteEntity( vEdWrk, "View", zREPOS_NEXT );

   AEQ_RefreshAEQ( vSubtask );
   return( 0 );
}

// OPERATION:  fnGetNextTokenFromBuffer
// PURPOSE:    Reads the current line in the current buffer starting at the
//             current cursor position and returns the first token found.
//
zSHORT LOCALOPER
fnGetNextTokenFromBuffer( ZMapAct *pzma, LPSTR pchToken, zLONG lLine, zLONG lCol )
{
   CString csLine;
   LPSTR   szBuffer;
   zLONG   lReturnedBuffSize = MAX_TOKEN_LTH;
   CString csDelimiter = "\t,)( ";

   pchToken[ 0 ] = 0;

   // Read line from Editor.
   szBuffer = csLine.GetBufferSetLength( lReturnedBuffSize );
   lReturnedBuffSize = EDT_GetTextFromLineOfIndex( pzma->m_pZSubtask->m_vDialog, szBuffer, lReturnedBuffSize, lLine );

   // In Case of an editor error (Buffer too small) ...
   if ( lReturnedBuffSize >= MAX_TOKEN_LTH )
   {
      lReturnedBuffSize++;
      csLine.ReleaseBuffer( );
      szBuffer = csLine.GetBufferSetLength( lReturnedBuffSize );
      lReturnedBuffSize = EDT_GetTextFromLineOfIndex( pzma->m_pZSubtask->m_vDialog, szBuffer, lReturnedBuffSize, lLine );
   }

   csLine.ReleaseBuffer( );

   // Since we retrieved the whole line we need to start where the cursor is.
   EDT_GetPositionByIndex( pzma->m_pZSubtask->m_vDialog, &lLine, &lCol );
   csLine = csLine.Mid( lCol, csLine.GetLength( ) - lCol );

   // Remove obsolete whitespaces.
   csLine.TrimLeft( );
   csLine.TrimRight( );

   int iTokenLength = csLine.FindOneOf( csDelimiter );
   if ( iTokenLength >= 0 )
   {
      csLine = csLine.Mid( 0, iTokenLength );
   }

   strcpy_s( pchToken, MAX_TOKEN_LTH, csLine );
   return( TRUE );
}

void fnTextTokenizer(zCPCHAR cpcTextLine, CStringArray &arrToken, zCPCHAR cpcDelimiters)
{
   arrToken.RemoveAll();

   if ( cpcDelimiters == 0 || cpcDelimiters == "" )
      cpcDelimiters = " ,()\r\n\t";

   // Do not process empty strings.
   if (cpcTextLine != 0 && cpcTextLine != "")
   {
      zPCHAR pchContext = 0;

      int nTotalTokens = 0;
      int nLth = strlen( cpcTextLine ) + 1;
      char *pchTextLine = new char[nLth];

      strcpy_s(pchTextLine, nLth, cpcTextLine);
      char *pchToken = strtok_s( pchTextLine, cpcDelimiters, &pchContext );
      while ( pchToken ) // while there are tokens in pchTextLine
      {
         if ( pchToken[0] )
            arrToken.SetAtGrow(nTotalTokens++, pchToken);

         pchToken = strtok_s( 0, cpcDelimiters, &pchContext );
      }
   }
}

// VIEW wWebXfer REGISTERED AS wWebXfer
// VIEW mSubreg  BASED ON LOD  mSubreg

#define zTokenView                  0x0001
#define zTokenName1                 0x1000
#define zTokenRegistered            0x0010
#define zTokenAs                    0x0020
#define zTokenBased                 0x0100
#define zTokenOn                    0x0200
#define zTokenLod                   0x0400
#define zTokenName2                 0x2000
#define zTokenViewName              0x1001
#define zTokenRegisteredAs          0x1031
#define zTokenBasedOnLod            0x1701
#define zTokenRegisteredAsComplete  0x3031
#define zTokenBasedOnLodComplete    0x3701

zBOOL fnLocateViewName( int &nFlags, CStringArray &arrToken, CString &csViewName, CString &csLodName, int &nPos, BOOL &bContinuedComment )
{
// TODO:  check for comments
   int nCnt = arrToken.GetCount();
   CString cs;

   while ( nPos < nCnt )
   {
      cs = arrToken[nPos];
      if ( cs.CompareNoCase( "VIEW" ) == 0 )
      {
         nFlags = zTokenView;
         csViewName = "";
         csLodName = "";
      }
      else
      if ( cs.CompareNoCase( "REGISTERED" ) == 0 )
      {
         if ( nFlags == zTokenViewName )
         {
            nFlags |= zTokenRegistered;
         }
         else
         {
            nFlags = 0;
         }
      }
      else
      if ( cs.CompareNoCase( "AS" ) == 0 )
      {
         if ( nFlags == (zTokenViewName | zTokenRegistered) )
         {
            nFlags |= zTokenAs;
         }
         else
         {
            nFlags = 0;
         }
      }
      else
      if ( cs.CompareNoCase( "BASED" ) == 0 )
      {
         if ( nFlags == zTokenViewName )
         {
            nFlags |= zTokenBased;
         }
         else
         {
            nFlags = 0;
         }
      }
      else
      if ( cs.CompareNoCase( "ON" ) == 0 )
      {
         if ( nFlags == (zTokenViewName | zTokenBased) )
         {
            nFlags |= zTokenOn;
         }
         else
         {
            nFlags = 0;
         }
      }
      else
      if ( cs.CompareNoCase( "LOD" ) == 0 )
      {
         if ( nFlags == (zTokenViewName | zTokenBased | zTokenOn) )
         {
            nFlags |= zTokenLod;
         }
         else
         {
            nFlags = 0;
         }
      }
      else
      if ( nFlags == zTokenView )
      {
         nFlags |= zTokenViewName;
         csViewName = cs;
      }
      else
      {
         if ( (nFlags == zTokenRegisteredAs) || (nFlags == zTokenBasedOnLod) )
         {
            nFlags |= zTokenName2;
            csLodName = cs;
            nPos++;
            return TRUE;
         }
      }
      nPos++;
   }
   return FALSE;
}

zOPER_EXPORT zSHORT OPERATION
AEQ_GetViews( zVIEW vSubtask )
{
   static zCHAR szOperationString[] = "\\bOPERATION[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+";
   zVIEW    vEdWrk;
   zVIEW    vVor;
   zVIEW    vEditorSubtask;
   zLONG    lLineCnt;
   zLONG    lLineLth;
   zLONG    lLine = 0, lCol = 0;
   zLONG    lOrigLine = 0, lOrigCol = 0;
   zLONG    lOperationEndLine = -1, lOperationStartLine = -1;
   zLONG    lIndexAfterObjectName = 0;
   zCHAR    szMsg[ 100 ];
   CString  csCurrentLine;
   LPSTR    pchCurrentLine;
   zSHORT   nRC;

   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "TZEDWRKO not Available at GetViews." );
      OperatorPrompt( vSubtask, "ED - Error", szMsg, 0, zBUTTONS_OK, 0, 0 );
      return( zCALL_ERROR );
   }

   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) != 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "'Get Views' only works on VML Files." );
      OperatorPrompt( vSubtask, "ED - Error", szMsg, 0, zBUTTONS_OK, 0, 0 );
      return( zCALL_ERROR );
   }

   GetIntegerFromAttribute( (zPLONG) &vEditorSubtask, vEdWrk, szlBuffer, "vSubtask" );

   // Find the end of the current operation by searching for the beginning
   // of the next operation.  Since we want to ignore any operations that
   // might be commented out, keep searching until we are not in a comment.
   lLineCnt = EDT_GetLineCount( vEditorSubtask ) - 1;
   EDT_GetCursorPosition( vEditorSubtask, &lLine, &lCol );
   lOrigLine = lLine;
   lOrigCol = lCol;
   lOperationEndLine = lLine;
   lCol = 0;
   while ( lOperationEndLine <= lLineCnt )
   {
      if ( EDT_FindTextPosition( vEditorSubtask, "OPERATION", &lOperationEndLine, &lCol, FIND_FORWARD ) == FALSE )
      {
         // OPERATION not found, so set lLastLine to some ridiculously high number
         // (this number indicates the last line of the current op) and stop searching
         lOperationEndLine = lLineCnt;
         break;
      }

      if ( EDT_IsCommentAtIndex( vEditorSubtask, lOperationEndLine, lCol ) )
         lOperationEndLine++;
      else
         break;
   }

   // From the end of the current operation, search back to the beginning of current operation.
   lOperationStartLine = lLine + 1;
   lCol = 0;
   while ( lOperationStartLine >= 0 )
   {
      if ( EDT_FindTextPosition( vEditorSubtask, "OPERATION", &lOperationStartLine, &lCol, FIND_DIRECTION_UP ) == FALSE )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Couldn't find beginning of operation" );
         OperatorPrompt( vSubtask, szlZeidonEditor, szMsg, 0, zBUTTONS_OK, 0, 0 );
         return( zCALL_ERROR );
      }

      if ( EDT_IsCommentAtIndex( vEditorSubtask, lOperationStartLine, lCol ) )
         lOperationStartLine--;
      else
         break;
   }

   // Search for 'BASED ON LOD' and 'REGISTERED AS' and retrieve the object name and view variable name.
   // e.g.  VIEW wWebXfer REGISTERED AS wWebXfer
   //       VIEW mSubreg  BASED ON LOD  mSubreg

   CString  csViewName = "";
   CString  csLodName = "";
   CStringArray arrToken;
   BOOL     bContinuedComment = FALSE;
   int      nFlags = 0;
   int      nPos;

   lLine = lOperationStartLine;
   while ( lLine < lOperationEndLine )
   {
      lLineLth = EDT_GetLineLength( vEditorSubtask, lLine ) + 1;
      pchCurrentLine = csCurrentLine.GetBufferSetLength( lLineLth );
      EDT_GetActualTextLine( vEditorSubtask, pchCurrentLine, lLineLth, lLine );
      fnTextTokenizer(pchCurrentLine, arrToken, 0);
      nPos = 0;
      while (fnLocateViewName( nFlags, arrToken, csViewName, csLodName, nPos, bContinuedComment ))
      {
         // Add the view name.
         // If we are searching for registered views, then csLodName is really the VOR name.  Get the object name.
         if ( (nFlags & zTokenRegisteredAsComplete) == zTokenRegisteredAsComplete )
         {
            // Add view variable and Object name to editor work object.
            // First, get the VOR by name.
            nRC = ActivateMetaOI_ByName( vSubtask, &vVor, 0, zREFER_VOR_META,
                                         zSINGLE | zLEVEL_APPLICATION, (zPCHAR) csLodName.GetString(), 0 );
            if ( nRC < 0 )
            {
               strcpy_s( szMsg, zsizeof( szMsg ), "Can't find Registered View with name " );
               strcat_s( szMsg, zsizeof( szMsg ), csLodName );
               OperatorPrompt( vSubtask, szlZeidonEditor, szMsg, 0, zBUTTONS_OK, 0, 0 );
               continue;
            }

            // Get Object name from VOR.
            zPCHAR pchLodName;
            GetAddrForAttribute( &pchLodName, vVor, "LOD", szlName );
            csLodName = pchLodName;
            DropMetaOI( vSubtask, vVor );
         }

         // Add view variable and Object name to editor work object.

         // If entity with csViewName does NOT exist, create it.
         // If the variable name is the same but the object name is different,
         // delete the old View and replace it with a new View.  If variable
         // name and object name are the same, then don't do anything.
         nRC = SetCursorFirstEntityByString( vEdWrk, szlView, szlVariableName, csViewName, "" );
         if ( nRC != zCURSOR_SET )
         {
            CreateEntity( vEdWrk, szlView, zPOS_LAST );
            SetAttributeFromString( vEdWrk, szlView, szlObjectName, csLodName );
            SetAttributeFromString( vEdWrk, szlView, szlVariableName, csViewName );
         }
         else
         if ( CompareAttributeToString( vEdWrk, szlView, szlObjectName, csLodName ) != 0 )
         {
            // We must do a delete to get rid of all Entity/Attribute entities.
            DeleteEntity( vEdWrk, szlView, zREPOS_FIRST );

            CreateEntity( vEdWrk, szlView, zPOS_LAST );
            SetAttributeFromString( vEdWrk, szlView, szlObjectName, csLodName );
            SetAttributeFromString( vEdWrk, szlView, szlVariableName, csViewName );
         }

         nFlags = 0;
         csViewName = "";
         csLodName = "";
         continue;
      }
      lLine++;
   }

   if ( CheckExistenceOfEntity( vEdWrk, szlView ) >= zCURSOR_SET )
      AEQ_SelectView( vSubtask );

   // KJS 11/11/16 - Need to set back to where the cursor was originally.
   EDT_SetCursorPositionByLineCol(vEditorSubtask, lOrigLine, lOrigCol);

   return( 0 );

} // AEQ_GetViews

zSHORT LOCALOPER
fnPasteQualifier( zVIEW  vSubtask,
                  zSHORT nPasteCtl,
                  zBOOL  bInsertWithQuote )
{
   zVIEW  vEdWrk;
   zVIEW  vEditorSubtask;
   zPCHAR pchEntityName;
   zPCHAR pchAttribName;
   zCHAR  szMsg[ 400 ];

   mGetWorkView( &vEdWrk, vSubtask );
   GetParentWindow( &vEditorSubtask, vSubtask );

   if ( vEdWrk == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "TZEDWRKO not Available at PasteQualifier." );
      OperatorPrompt( vSubtask, "ED - Error", szMsg, 0, zBUTTONS_OK, 0, 0 );
      return( zCALL_ERROR );
   }

   if ( CheckExistenceOfEntity( vEdWrk, szlView ) != zCURSOR_SET )
      return( zCALL_ERROR );

   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) != 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Paste only works for VML Files." );
      OperatorPrompt( vSubtask, szlZeidonEditor, szMsg, 0, zBUTTONS_OK, 0, 0 );
      return( zCALL_ERROR );
   }

   szMsg[0] = 0;

   if ( nPasteCtl & PASTE_VIEW_VARIABLE && CheckExistenceOfEntity( vEdWrk, szlView ) == zCURSOR_SET )
   {
      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vEdWrk, szlView, "VariableName" );
   }

   if ( nPasteCtl & PASTE_ENTITY && CheckExistenceOfEntity( vEdWrk, szlEntity ) == zCURSOR_SET )
   {
      GetAddrForAttribute( &pchEntityName, vEdWrk, szlEntity, szlEntityName );
      if ( pchEntityName )
      {
         if ( szMsg[0] )
         {
            if ( bInsertWithQuote )
               strcat_s( szMsg, zsizeof( szMsg ), ", " );
            else
               strcat_s( szMsg, zsizeof( szMsg ), "." );
         }

         if ( bInsertWithQuote )
            strcat_s( szMsg, zsizeof( szMsg ), "\"" );

         // Get rid of any leading spaces.
         while ( *pchEntityName == ' ' )
            pchEntityName++;
         strcat_s( szMsg, zsizeof( szMsg ), pchEntityName );

         if ( bInsertWithQuote )
            strcat_s( szMsg, zsizeof( szMsg ), "\"" );
      }
   }

   if ( nPasteCtl & PASTE_ATTRIBUTE && CheckExistenceOfEntity( vEdWrk, szlAttribute ) == zCURSOR_SET )
   {
      GetAddrForAttribute( &pchAttribName, vEdWrk, szlAttribute, szlAttributeName );
      if ( pchAttribName )
      {
         if ( szMsg[0] )
         {
            if ( bInsertWithQuote )
               strcat_s( szMsg, zsizeof( szMsg ), ", " );
            else
               strcat_s( szMsg, zsizeof( szMsg ), "." );
         }

         if ( bInsertWithQuote )
            strcat_s( szMsg, zsizeof( szMsg ), "\"" );

         strcat_s( szMsg, zsizeof( szMsg ), pchAttribName );

         if ( bInsertWithQuote )
            strcat_s( szMsg, zsizeof( szMsg ), "\"" );
      }
   }

   if ( szMsg[0] )
   {
      CString csStringToInsert;

      strcat_s( szMsg, zsizeof( szMsg ), " " );
      csStringToInsert = szMsg;
     // KJS 11/11/16 - The last parameter is whether we should reset the position of the cursor, not sure why it's
     // FALSE because we always set the cursor position to after what we've pasted. So I'm changing to TRUE.
      EDT_InsertItem( vEditorSubtask, csStringToInsert, TRUE );
      SetFocusToCtrl( vEditorSubtask, EDIT_CONTROL_NAME );
   }

   return( 0 );

} // fnPasteQualifier

zOPER_EXPORT zSHORT OPERATION
AEQ_PasteView( zVIEW vSubtask )
{
   fnPasteQualifier( vSubtask, PASTE_VIEW_VARIABLE, PASTE_WITHOUT_QUOTE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_PasteViewEntity( zVIEW vSubtask )
{
   fnPasteQualifier( vSubtask, PASTE_VIEW_VARIABLE | PASTE_ENTITY, PASTE_WITHOUT_QUOTE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_PasteViewEntity_Quoted( zVIEW vSubtask )
{
   fnPasteQualifier( vSubtask, PASTE_VIEW_VARIABLE | PASTE_ENTITY, PASTE_WITH_QUOTE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_PasteViewEntityAttr( zVIEW vSubtask )
{
   fnPasteQualifier( vSubtask, PASTE_VIEW_VARIABLE | PASTE_ENTITY | PASTE_ATTRIBUTE, PASTE_WITHOUT_QUOTE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_PasteViewEntityAttr_Quoted( zVIEW vSubtask )
{
   fnPasteQualifier( vSubtask, PASTE_VIEW_VARIABLE | PASTE_ENTITY | PASTE_ATTRIBUTE, PASTE_WITH_QUOTE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_SelectView( zVIEW vSubtask )
{
   zSHORT nRC;
   zVIEW  vList;
   zVIEW  vLOD;
   zVIEW  vEdWrk;
   zPCHAR szLOD_Name;
   zPCHAR szName;

   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
   {
      zCHAR szMsg[ 200 ];

      strcpy_s( szMsg, zsizeof( szMsg ), "TZEDWRKO not Available at ObjSelAQ_ObjSelView." );
      OperatorPrompt( vSubtask, "ED - Error", szMsg, 0, zBUTTONS_OK, 0, zICON_STOP );
      return( zCALL_ERROR );
   }

   // If Entity entity exists, then the LOD has already been loaded for
   // for this view.  Exit because nothing else needs to be done.
   if ( CheckExistenceOfEntity( vEdWrk, "Entity" ) == zCURSOR_SET )
   {
      AEQ_RefreshAEQ( vSubtask );
      return( 0 );
   }

   // Activate the LOD specified by vEdWrk.View.ObjectName
   GetAddrForAttribute( &szLOD_Name, vEdWrk, "View", "ObjectName" );
   nRC = RetrieveViewForMetaList( vSubtask, &vList, zREFER_LOD_META );
   nRC = SetCursorFirstEntity( vList, "W_MetaDef", "" );
   while ( nRC == zCURSOR_SET )
   {
      GetAddrForAttribute( &szName, vList, "W_MetaDef", "Name" );
      if ( zstrcmpi( szName, szLOD_Name ) == 0 )
         break;

      nRC = SetCursorNextEntity( vList, "W_MetaDef", "" );
   }

   if ( nRC != zCURSOR_SET )
   {
      zCHAR szMsg[ 200 ];

      DropView( vList );
      strcpy_s( szMsg, zsizeof( szMsg ), "LOD " );
      strcat_s( szMsg, zsizeof( szMsg ), szLOD_Name );
      strcat_s( szMsg, zsizeof( szMsg ), " not found. Possibly wrong LPLR?" );
      OperatorPrompt( vSubtask, "ZeidonEditor", szMsg, 0, 0, 1, zICON_STOP );
      return( zCALL_ERROR );
   }

   nRC = ActivateMetaOI( vSubtask, &vLOD, vList, zREFER_LOD_META, zSINGLE | zLEVEL_APPLICATION );
   DropView( vList );

   // Copy Entity and Attribute names from LOD to vEdWrk.
   nRC = SetCursorFirstEntity( vLOD, "LOD_Entity", "" );
   while ( nRC == zCURSOR_SET )
   {
      CreateEntity( vEdWrk, "Entity", zPOS_LAST );
      GetAddrForAttribute( &szName, vLOD, "LOD_Entity", "IndentName" );
      TraceLineS( "LOD_Entity IndentName: ", szName );
      SetAttributeFromAttribute( vEdWrk, "Entity", "EntityName", vLOD, "LOD_Entity", "IndentName" );

      nRC = SetCursorFirstEntity( vLOD, "LOD_Attribute", "" );
      while ( nRC == zCURSOR_SET )
      {
         CreateEntity( vEdWrk, "Attribute", zPOS_LAST );
         SetAttributeFromAttribute( vEdWrk, "Attribute", "AttributeName", vLOD, "ER_Attribute", "Name" );

         nRC = SetCursorNextEntity( vLOD, "LOD_Attribute", "" );
      }

      nRC = SetCursorNextEntity( vLOD, "LOD_Entity", "" );
   }

   DropMetaOI( vSubtask, vLOD );
   nRC = SetCursorFirstEntity( vEdWrk, "Entity", "" );
   SetSelectStateOfEntity( vEdWrk, "Entity", 1 );

   if ( CheckExistenceOfEntity( vEdWrk, "Attribute" ) >= zCURSOR_SET )
      SetSelectStateOfEntity( vEdWrk, "Attribute", 1 );

   AEQ_RefreshAEQ( vSubtask );
   return( 0 );

} // AEQ_SelectView

zOPER_EXPORT zSHORT OPERATION
AEQ_ViewPopup( zVIEW vSubtask )
{
// POINT  pt;
   CPoint pt( GetMessagePos( ) );
// pt.x = pt.y = -1;
   CreateTrackingPopupMenu( vSubtask, "ViewPopup", pt.x, pt.y, FALSE, FALSE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_EntityPopup( zVIEW vSubtask )
{
// POINT  pt;
   CPoint pt( GetMessagePos( ) );
// pt.x = pt.y = -1;
   CreateTrackingPopupMenu( vSubtask, "EntityPopup", pt.x, pt.y, FALSE, FALSE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
AEQ_AttributePopup( zVIEW vSubtask )
{
// POINT  pt;
   CPoint pt( GetMessagePos( ) );
// pt.x = pt.y = -1;
   CreateTrackingPopupMenu( vSubtask, "AttributePopup", pt.x, pt.y, FALSE, FALSE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
OpIns_Postbuild( zVIEW vSubtask )
{
   zVIEW vEdWrk;

   TZEDFRMD_DisableActions( vSubtask );

   // Get the subtask view for the parent editor window and give it another
   // name at the current subtask level so we can easily retrieve it.
   GetViewByName( &vEdWrk, "__EditorSubtask", vSubtask, zLEVEL_TASK );
   SetNameForView( vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_SUBTASK );

   fnSetSubwindowPosition( vSubtask, szlOperationsList );
   OpIns_BuildOperList( vSubtask );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION OpIns_Close( zVIEW vSubtask )
{
   fnSaveSubwindowPosition( vSubtask, szlOperationsList );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
OpIns_RefreshSelectButton( zVIEW vSubtask )
{
   zVIEW  vEdWrk;
   zCHAR  szCurrentType[ 5 ];

   mGetWorkView( &vEdWrk, vSubtask );
   GetStringFromAttribute( szCurrentType, zsizeof( szCurrentType ), vEdWrk, "OperListType", "Type" );
   if ( zstrcmp( szCurrentType, "Z" ) == 0 )
      MB_SetMessage( vSubtask, 0, "Press F1 for Help on the operation." );

   RefreshCtrl( vSubtask, "SelectButton" );
   return( 0 );
}

zSHORT LOCALOPER
PasteOperation( zVIEW vSubtask, zVIEW vOp )
{
   zSHORT     nRC;
   zVIEW      vEdWrk;
   zPCHAR     szStr;
   zBOOL      bInsertComment = FALSE;
   zBOOL      bVML_File;
   zVIEW      vEditorSubtask;
   zLONG      lOperationNameLength = 0,
              lLine = 0, lCol = 0;
   zLONG      lTabSize = 3; // Today a fixed length, in future this has to be queried
                            // from the edit-control
   CString    csNewLine = "\r\n";
   CString    csComment;
   CString    csIndent;
   CString    csTemp;

   if ( lTabSize > 1 )  // Don't ask why ... it's hard to explain
      lTabSize--;

   // Get the c++ object handle for the editor control.
   mGetWorkView( &vEdWrk, vSubtask );
   GetIntegerFromAttribute( (zPLONG) &vEditorSubtask, vEdWrk, szlBuffer, "vSubtask" );
   bVML_File = (CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) == 0);
   bInsertComment = (CompareAttributeToString( vEdWrk, szlBuffer, szlOpIns_InsertDescription, "Y" ) == 0);
   GetAddrForAttribute( &szStr, vOp, szlOperation, szlName );
   if ( bInsertComment )
   {
      zPCHAR  pchComment;
      zLONG   lCommentLength = 0;
      GetAddrForAttribute( &pchComment, vOp, szlOperation, szlDesc );

      lCommentLength = zstrlen( pchComment );
      if ( lCommentLength > 0 )
      {
         csComment = csNewLine;
         csComment = "//" + csNewLine;
         csComment += "// ";
         csComment += pchComment + csNewLine;
         csComment += "//" + csNewLine;
      }
   }

   csIndent = "   ";
   csTemp = csIndent + szStr;
   csTemp += "( ";

   // Get length of operation name and add position within current line.
   lOperationNameLength = zstrlen( csTemp );
   //EDT_GetCursorPosition( vEditorSubtask, &lLine, &lCol );
   //lOperationNameLength += lCol;
   //lCol = GetTabsInLine( vEditorSubtask, lCol ); // Get number of tabs until current Cursor position
   //lOperationNameLength -= lCol;  // Control interprets tab as a single character
   //lCol = lCol * lTabSize;    // remove single char and add multiple
   //lCol = 5; // hardwired for the moment ... dks - 2016.04.29
// lOperationNameLength += 2; // add two for "( "

   // Set up a string which contains a number of tabs and blanks depending
   // on operation name and position, to format the operation insert frame.

   // insert several tabs
   // while ( lOperationNameLength > lTabSize )
   // {
   //   csIndent += "\t";
   //   lOperationNameLength -= lTabSize;
   // }

   // insert spaces to "( "
   csIndent.Empty();
   while ( lOperationNameLength > 0 )
   {
      csIndent += " ";
      lOperationNameLength--;
   }

   nRC = SetCursorFirstEntity( vOp, "Parameter", "" );
   while ( nRC == zCURSOR_SET )
   {
      GetAddrForAttribute( &szStr, vOp, "Parameter", "PFlag" );
      if ( bVML_File == FALSE && szStr[0] == 'Y' )
         csTemp += "PTR ";

      GetAddrForAttribute( &szStr, vOp, "Parameter", "UFlag" );
      if ( bVML_File == FALSE  && szStr[0] == 'Y' )
         csTemp += "UNSIGNED ";

      GetAddrForAttribute( &szStr, vOp, "Parameter", "DataType" );
      if ( szStr[0] )
      {
         if ( bVML_File )
         {
            switch ( szStr[0] )
            {
               case 'A':
                  csTemp += "\"ATTRIBUTE_NAME\"";
                  break;

               case 'E':
                  csTemp += "\"ENTITY_NAME\"";
                  break;

               case 'L':
                  csTemp += "INTEGER";
                  break;

               case 'M':
                  csTemp += "DOUBLE";
                  break;

               case 'N':
                  csTemp += "INTEGER";
                  break;

               case 'O':
                  csTemp += "VOID";
                  break;

               case 'S':
                  csTemp += "STRING";
                  break;

               case 'V':
                  csTemp += "VIEW";
                  break;

               case 'Y':
                  csTemp += "STRING";
                  break;

               default :
                  csTemp += szStr;
                  break;

            } // switch
         }
         else
         {
            switch ( szStr[0] )
            {
               case 'A':
                  csTemp += "\"ATTRIBUTE_NAME\"";
                  break;

               case 'E':
                  csTemp += "\"ENTITY_NAME\"";
                  break;

               case 'L':
                  csTemp +="zLONG";
                  break;

               case 'M':
                  csTemp += "DOUBLE";
                  break;

               case 'N':
                  csTemp += "zSHORT";
                  break;

               case 'O':
                  csTemp += "void";
                  break;

               case 'S':
                  csTemp += "zCHAR";
                  break;

               case 'V':
                  csTemp += "zVIEW";
                  break;

               case 'Y':
                  csTemp += "zCHAR";
                  break;

               default :
                  csTemp += szStr;
                  break;

            } // switch
         } // if ( bVML_File )...else...
      }

      GetAddrForAttribute( &szStr, vOp, "Parameter", "ShortDesc" );
      if ( szStr[0] )
      {
         csTemp += " /* ";
         csTemp += szStr;
         csTemp += " */";
      }

      nRC = SetCursorNextEntity( vOp, "Parameter", "" );
      if ( nRC == zCURSOR_SET )
      {
         csTemp += "," + csNewLine + csIndent;
      }
      else
         csTemp += " ";
   }

   csTemp += ")";
   if ( bVML_File == FALSE )
      csTemp += ";";

   csTemp += csNewLine;
   // KJS 11/11/16 - The last parameter is whether we should reset the position of the cursor, not sure why it's
   // FALSE because we always set the cursor position to after what we've pasted. So I'm changing to TRUE.
   EDT_InsertItem( vEditorSubtask, csTemp, TRUE );
   return( 0 );

} // PasteOperation

zOPER_EXPORT zSHORT OPERATION
OpIns_InsertOperation( zVIEW vSubtask )
{
   zCHAR  szType[ 5 ];
   zVIEW  vEdWrk;
   zVIEW  vTemp;

   mGetWorkView( &vEdWrk, vSubtask );
   GetStringFromAttribute( szType, zsizeof( szType ), vEdWrk, szlOperListType, szlType );
   switch ( szType[0] )
   {
      case 'Z':
      {
         zVIEW vTZOPSIGK;

         // User wants to insert a Zeidon operation.  Retrieve the view that
         // contains the list of Zeidon operations and past the operation.
         GetViewByName( &vTZOPSIGK, szlTZOPSIGK, vSubtask, zLEVEL_TASK );
         SetCursorFirstEntityByAttr( vTZOPSIGK, szlOperation, szlName, vEdWrk, szlOper, szlName, 0 );
         PasteOperation( vSubtask, vTZOPSIGK );
         break;
      }

      case 'G':
      {
         zVIEW vOp;
         zCHAR  szOpName[ 255 ];

         // User wants to insert a Global operation.  Retrieve the Global
         // Operations Group view that contains the operation.

         GetStringFromAttribute( szOpName, zsizeof( szOpName ), vEdWrk, szlOper, szlName );
         ActivateMetaOI_ByName( vSubtask, &vOp, 0, zREFER_GO_META, zSINGLE | zLEVEL_APPLICATION, szOpName, zCURRENT_OI );
         PasteOperation( vSubtask, vOp );
         break;
      }

      case 'L':
      {
         zVIEW vMeta;
         zLONG lMetaType;

         // User wants to insert a "Local"operation.  Retrieve the meta
         // and paste.

         GetIntegerFromAttribute( (zPLONG) &vMeta, vEdWrk, szlBuffer, szlSourceViewID );
         GetIntegerFromAttribute( &lMetaType, vEdWrk, szlBuffer, szlMetaType );

         // Create a temp view so that we can muck around with cursors.
         CreateViewFromViewForTask( &vMeta, vMeta, 0 );

         if ( lMetaType == zREFER_DIALOG_META || lMetaType == zREFER_LOD_META )
         {
            // Dialog and LOD meta's can have multiple source files for one meta.
            // Make sure we are dealing with the opertions for the correct source file.
            SetCursorFirstEntityByAttr( vMeta, szlSourceFile, szlName, vEdWrk, szlBuffer, szlSourceFileName, 0 );
         }

         SetCursorFirstEntityByAttr( vMeta, szlOperation, szlName, vEdWrk, szlOper, szlName, 0 );

         PasteOperation( vSubtask, vMeta );

         DropView( vMeta );
         break;

      } // case 'L'...

      case 'O':
      {
         zVIEW  vObj;
         zCHAR  szObjectName[ 50 ];
         zCHAR  szOperName[ 255 ];
         zPCHAR pch;

         // User wants to insert an Object Operation.
         GetStringFromAttribute( szObjectName, zsizeof( szObjectName ), vEdWrk, szlOper, szlName );

         // Look for the period between the Object name and the Oper name.
         for ( pch = szObjectName; *pch && *pch != '.'; pch++ )
            ; // Nothing needs to be done here.

         // Change the period to a null-term and bump up the pointer to point to the oper name.
         *pch++ = 0;

         // Copy the oper name.
         strcpy_s( szOperName, zsizeof( szOperName ), pch );

         // Activate the object meta.
         ActivateMetaOI_ByName( vSubtask, &vObj, 0, zREFER_LOD_META, zSINGLE | zLEVEL_APPLICATION, szObjectName, zFORCE_RELOAD );

         // Set the cursor to the operation.
         SetCursorFirstEntityByString( vObj, szlOperation, szlName, szOperName, szlLOD );

         PasteOperation( vSubtask, vObj );

         DropMetaOI( vSubtask, vObj );
         break;

      } // case 'O'...

      case 'X':
      {
         CString    csIndent;
         zVIEW      vEditorSubtask;
         zCHAR      szBuffer[ 1024 ];
         zLONG      lOperationNameLth = 0,
                    lLine = 0, lCol = 0;
         zLONG      lTabSize = 4; // Today a fixed length, in future this has to be queried from the edit-control
         zBOOL      bVML_File;
         ZSubtask   *pZSubtask;
         ZMapAct    *pzma;

         GetStringFromAttribute( szBuffer, zsizeof( szBuffer ), vEdWrk, szlOper, szlName );
         BuildTZEDWRKO( vEdWrk, szBuffer, zsizeof( szBuffer ) );

         if ( lTabSize > 1 )  // Don't ask why ... it's hard to explain
            lTabSize--;

         // Get the C++ object handle for the editor control.
         GetIntegerFromAttribute( (zPLONG) &vEditorSubtask, vEdWrk, szlBuffer, "vSubtask" );
         GetWindowAndCtrl( &pZSubtask, &pzma, vEditorSubtask, EDIT_CONTROL_NAME );
         if ( pzma == 0 )
         {
            SysMessageBox( vSubtask, "Zeidon Error", "Couldn't find Editor control.", 1 );
            return( 0 );
         }

         bVML_File = (CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) == 0);

         // Get length of operation name and add position within current line
         lOperationNameLth = zstrlen( szBuffer );
         EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
         lOperationNameLth += lCol;
         lCol = GetTabsInLine( vSubtask, lCol ); // Get number of tabs until current Cursorposition
         lOperationNameLth -=lCol;  // Control interprets tab as a single character
         lCol = lCol * lTabSize;    // remove single char and add multiple
         lOperationNameLth += lCol; // (virtual) characters depending on tabsize

         // Set up a string which contains a number of tabs and blanks depending
         // on operation name and position, to format the operation insert frame.

         // insert several tabs
         while ( lOperationNameLth > 1 )
         {
            csIndent += " ";
            lOperationNameLth--;
         }

         if ( bVML_File == FALSE )
            strcat_s( szBuffer, zsizeof( szBuffer ), ";" );

         csIndent += szBuffer;
       // KJS 11/11/16 - The last parameter is whether we should reset the position of the cursor, not sure why it's
       // FALSE because we always set the cursor position to after what we've pasted. So I'm changing to TRUE.
       EDT_InsertItem( vSubtask, csIndent, TRUE );
         break;
      }

      default:
         SysMessageBox( vSubtask, "Zeidon Internal", "This operation type not yet supported", 0 );
         break;

   } // switch ( szType[0] )...

   // Set Focus to Editor
   GetParentWindow( &vTemp, vSubtask );
   SetFocusToCtrl( vTemp, EDIT_CONTROL_NAME );
   return( 0 );
}

// This operation builds the operation list for the OperationList window.
// Depending on what the value is for vEdWrk.Buffer.OpIns_CurrentType
// we build different operations lists.
zOPER_EXPORT zSHORT OPERATION
OpIns_BuildOperList( zVIEW vSubtask )
{
#define DISP_SELECT_SET    1
#define SEL_SELECT_SET     2

   zCHAR  szCurrentType[ 5 ];
   zVIEW  vEdWrk;
   zSHORT nRC;
   zCHAR  szKeyword[ 255 ];
   zLONG  lSelectCount = 0;

   mGetWorkView( &vEdWrk, vSubtask );

   LB_SetDisplaySelectSet( vSubtask, "OperationList", DISP_SELECT_SET );
   LB_SetSelectSelectSet( vSubtask, "OperationList", SEL_SELECT_SET );
   SetAllSelStatesForEntityForSet( vEdWrk, "Oper", FALSE, DISP_SELECT_SET, 0 );
   SetAllSelStatesForEntityForSet( vEdWrk, "Oper", FALSE, SEL_SELECT_SET, 0 );

   GetStringFromAttribute( szCurrentType, zsizeof( szCurrentType ), vEdWrk, szlBuffer, "OpIns_CurrentType" );

   // Default of CurrentType is 'Z'...
   if ( szCurrentType[ 0 ] == 0 )
   {
      strcpy_s( szCurrentType, zsizeof( szCurrentType ), "Z" );
      SetAttributeFromString( vEdWrk, szlBuffer, "OpIns_CurrentType", szCurrentType );
   }

   // Check to see if the operations for the current type are already
   // loaded. If they are, then we obviously don't need to load them again.
   if ( SetCursorFirstEntityByString( vEdWrk, "OperListType", "Type", szCurrentType, 0 ) != zCURSOR_SET )
   {
      // Operations haven't been loaded yet, so load 'em up.

      CreateEntity( vEdWrk, "OperListType", zPOS_LAST );
      SetAttributeFromString( vEdWrk, "OperListType", "Type", szCurrentType );

      switch ( szCurrentType[ 0 ] )
      {
         case 'A':
         case 'Z':
         {
            zVIEW vTZOPSIGK;

            // Get list of Zeidon operations.

            // Check to see if we've already activated the Zeidon opers list.
            // If not, activate it and save the view.
            GetViewByName( &vTZOPSIGK, "TZOPSIGK", vSubtask, zLEVEL_TASK );
            if ( !vTZOPSIGK )
            {
               oTZOPGRPO_GetViewForXGO( vSubtask, &vTZOPSIGK, zSYS_CURRENT_OI );
               SetNameForView( vTZOPSIGK, "TZOPSIGK", vSubtask, zLEVEL_TASK );
            }

            // Now copy each of the operations to the editor work object.
            for ( nRC = SetCursorFirstEntity( vTZOPSIGK, "Operation", 0 );
                  nRC == zCURSOR_SET;
                  nRC = SetCursorNextEntity( vTZOPSIGK, "Operation", 0 ) )
            {
               CreateEntity( vEdWrk, "Oper", zPOS_LAST );
               SetMatchingAttributesByName( vEdWrk, "Oper", vTZOPSIGK, "Operation", zSET_ALL );
            }

            if ( szCurrentType[ 0 ] != 'A' )
               break;
         } // Case 'Z'...

         case 'G':
         {
            zVIEW vOp;

            // Get list of Global operations.

            RetrieveViewForMetaList( vSubtask, &vOp, zREFER_GO_META );

            // Now copy each of the operations to the editor work object.
            for ( nRC = SetCursorFirstEntity( vOp, "W_MetaDef", 0 );
                  nRC == zCURSOR_SET;
                  nRC = SetCursorNextEntity( vOp, "W_MetaDef", 0 ) )
            {
               CreateEntity( vEdWrk, "Oper", zPOS_LAST );
               SetMatchingAttributesByName( vEdWrk, "Oper", vOp, "W_MetaDef", zSET_ALL );
            }

            DropView( vOp );

            if ( szCurrentType[ 0 ] != 'A' )
               break;
         } // Case 'G'...

         case 'L':
         {
            zVIEW vMeta;
            zLONG lMetaType;

            // Get list of "Local" operations.  "Local" operations in this
            // case mean all operations that are for the current meta.
            // For example, if the current meta is a Dialog, then the "Local"
            // operations include local and Dialog operations.

            // Get the source view and the meta type.
            GetIntegerFromAttribute( (zPLONG) &vMeta, vEdWrk, "Buffer", "SourceViewID" );
            GetIntegerFromAttribute( &lMetaType, vEdWrk, "Buffer", "MetaType" );

            // Create a new, temp view of the meta so that we can muck around with the cursors.
            CreateViewFromViewForTask( &vMeta, vMeta, 0 );

            //
            // Now copy the "Local" meta operations to vEdWrk.
            //

            if ( lMetaType == zREFER_DIALOG_META || lMetaType == zREFER_LOD_META )
            {
               // Make sure we are reading the "Local" operations for the current source file.
               SetCursorFirstEntityByAttr( vMeta, "SourceFile", "Name", vEdWrk, "Buffer",  "SourceFileName", 0 );
            }

            // Copy all the operations to vEdWrk
            for ( nRC = SetCursorFirstEntity( vMeta, "Operation", 0 );
                  nRC == zCURSOR_SET;
                  nRC = SetCursorNextEntity( vMeta, "Operation", 0 ) )
            {
               CreateEntity( vEdWrk, "Oper", zPOS_LAST );
               SetMatchingAttributesByName( vEdWrk, "Oper", vMeta, "Operation", zSET_ALL );
            }

            DropView( vMeta );
            break;

         } // Case 'L'...

         case 'O':
         {
            // Since we load the object operations by object, we don't have to do anything here.
            break;

         } // Case 'O'...

         case 'X':  // ActiveX operations
         {
            BuildTZEDWRKO( vEdWrk, 0, 0 );
            break;
         }

         default:
            SysMessageBox( vSubtask, "Zeidon Internal", "This operation type not yet supported", 0 );
            break;

      } // switch ( szCurrentType[ 0 ] )...

      // Now that we've loaded the operations, sort them.
      OrderEntityForView( vEdWrk, "Oper", "Name A" );

   } // if ( SetCursor...)...

   // Disable the "Objects" button unless we are showing object operations.
   if ( szCurrentType[ 0 ] == 'O' )
      SetCtrlState( vSubtask, "ListObjects", zCONTROL_STATUS_ENABLED, TRUE );
   else
      SetCtrlState( vSubtask, "ListObjects", zCONTROL_STATUS_ENABLED, FALSE );

   // Now set the select states depending on the keyword values.
   GetStringFromAttribute( szKeyword, zsizeof( szKeyword ), vEdWrk, szlBuffer, "OpIns_Keyword" );
   if ( szKeyword[0] &&
        CompareAttributeToString( vEdWrk, szlBuffer, "OpIns_UseKeyword", "Y" ) == 0 )
   {
      zCHAR  szIgnoreCase[ 5 ];
      zPCHAR pchKeyword;
      zBOOL  bStartColOne;
      zSHORT nKeywordLth;

      // De-select all operations.
      SetAllSelStatesForEntityForSet( vEdWrk, "Oper", FALSE, DISP_SELECT_SET, 0 );
      SetAllSelStatesForEntityForSet( vEdWrk, "Oper", FALSE, SEL_SELECT_SET, 0 );

      GetStringFromAttribute( szIgnoreCase, zsizeof( szIgnoreCase ), vEdWrk, szlBuffer, "OpIns_KeywordIgnoreCase" );
      if ( szIgnoreCase[0] == 'Y' )
      {
         for ( pchKeyword = szKeyword; *pchKeyword; pchKeyword++ )
            *pchKeyword = ztoupper( *pchKeyword );
      }

      // If the keyword starts with a "*", then the keyword search starts with the first char (e.g. column) ONLY.
      pchKeyword = szKeyword;
      if ( *pchKeyword == '*' || *pchKeyword == '/' )
      {
         pchKeyword++;
         bStartColOne = FALSE;
      }
      else
         bStartColOne = TRUE;

      nKeywordLth = (zSHORT) zstrlen( pchKeyword );

      for ( nRC = SetCursorFirstEntity( vEdWrk, "Oper", 0 );
            nRC == zCURSOR_SET;
            nRC = SetCursorNextEntity( vEdWrk, "Oper", 0 ) )
      {
         zCHAR  szOperName[ 255 ];

         GetStringFromAttribute( szOperName, zsizeof( szOperName ), vEdWrk, "Oper", "Name" );
         if ( szIgnoreCase[0] == 'Y' )
         {
            zPCHAR pchOperName;

            pchOperName = zstrupr( szOperName );
         }

         if ( bStartColOne )
         {
            if ( zstrncmp( szOperName, pchKeyword, nKeywordLth ) == 0 )
            {
               SetSelectStateOfEntityForSet( vEdWrk, "Oper", TRUE, DISP_SELECT_SET );
               lSelectCount++;
            }
         }
         else
         {
            if ( strstr( szOperName, pchKeyword ) )
            {
               SetSelectStateOfEntityForSet( vEdWrk, "Oper", TRUE, DISP_SELECT_SET );
               lSelectCount++;
            }
         }
      } // for...
   }
   else
   {
      // Select all operations.
      SetAllSelStatesForEntityForSet( vEdWrk, "Oper", TRUE, DISP_SELECT_SET, 0 );
      lSelectCount = CountEntitiesForView( vEdWrk, "Oper" );
   }

   SetSelectSetForView(   vEdWrk, DISP_SELECT_SET );
   SetCursorFirstSelectedEntity( vEdWrk, "Oper", 0 );

   // Re-use szKeyword to set the message...
   sprintf( szKeyword, "%d Operations listed", lSelectCount );
   MB_SetMessage( vSubtask, 0, szKeyword );

   RefreshCtrl( vSubtask, "OperationList" );
   TZEDFRMD_DisableActions( vSubtask );
   return( 0 );

} // OpIns_BuildOperList

zOPER_EXPORT zSHORT OPERATION
OpIns_RebuildOperList( zVIEW vSubtask )
{
   zCHAR  szCurrentType[ 5 ];
   zVIEW  vEdWrk;

   mGetWorkView( &vEdWrk, vSubtask );
   GetStringFromAttribute( szCurrentType, zsizeof( szCurrentType ), vEdWrk, szlBuffer, "OpIns_CurrentType" );

   // Default of CurrentType is 'Z'...
   if ( szCurrentType[ 0 ] == 0 )
   {
      strcpy_s( szCurrentType, zsizeof( szCurrentType ), "Z" );
      SetAttributeFromString( vEdWrk, szlBuffer, "OpIns_CurrentType", szCurrentType );
   }

   // Check to see if the operations for the current type are already loaded. If they are, then delete the list.
   if ( SetCursorFirstEntityByString( vEdWrk, "OperListType", "Type", szCurrentType, 0 ) == zCURSOR_SET )
   {
      DeleteEntity( vEdWrk, "OperListType", zREPOS_FIRST );
   } // if ( SetCursor...)...

   // Now call BuildOperList to rebuild the oper list.
   OpIns_BuildOperList( vSubtask );
   return( 0 );

} // OpIns_RebuildOperList

// Loads a list of Objects (LODs) for the current lplr.
zOPER_EXPORT zSHORT OPERATION
ObjList_Prebuild( zVIEW vSubtask )
{
   zVIEW vObjList;

   GetViewByName( &vObjList, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );
   if ( vObjList )
      DropView( vObjList );

   RetrieveViewForMetaList( vSubtask, &vObjList, zREFER_LOD_META );
   SetNameForView( vObjList, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );
   return( 0 );
}

// The user selected a LOD in the Object list.  Load the LOD meta and copy
// all object operations to the editor work object.
zOPER_EXPORT zSHORT OPERATION
ObjList_AddObjOpersToWorkList( zVIEW vSubtask )
{
   zVIEW  vObjList;
   zVIEW  vLOD;
   zVIEW  vEdWrk;
   zVIEW  vParentSubtask;
   zSHORT nRC;
   zSHORT nLth;
   zCHAR  szOpName[ 255 ];

   // We need to get the parent subtask view so that we can retrieve the work view.
   GetParentWindow( &vParentSubtask, vSubtask );
   mGetWorkView( &vEdWrk, vParentSubtask );

   GetViewByName( &vObjList, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );
   ActivateMetaOI( vSubtask, &vLOD, vObjList, zREFER_LOD_META, 0 );
   GetStringFromAttribute( szOpName, zsizeof( szOpName ), vObjList, "W_MetaDef", "Name" );
   strcat_s( szOpName, zsizeof( szOpName ), "." );
   nLth = (zSHORT) zstrlen( szOpName );

   for ( nRC = SetCursorFirstEntity( vLOD, "OperationList", 0 );
         nRC == zCURSOR_SET;
         nRC = SetCursorNextEntity( vLOD, "OperationList", 0 ) )
   {
      GetStringFromAttribute( szOpName + nLth, zsizeof( szOpName ) - nLth, vLOD, "OperationList", "Name" );

      CreateEntity( vEdWrk, "Oper", zPOS_LAST );
      SetAttributeFromString( vEdWrk, "Oper", "Name", szOpName );
   }

   DropMetaOI( vSubtask, vLOD );
   DropView( vObjList );
   return( 0 );

} // ObjList_AddObjOpersToWorkList

zOPER_EXPORT zSHORT OPERATION
ObjList_RefreshSelectButton( zVIEW vSubtask )
{
   RefreshCtrl( vSubtask, "LoadObjOperations" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
SortMetaListByName( zVIEW vSubtask )
{
   zVIEW  vMetaList;

   GetViewByName( &vMetaList, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );
   OrderEntityForView( vMetaList, "W_MetaDef", "Name" );
   RefreshCtrl( vSubtask, "ListObjects" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
SortMetaListByDate ( zVIEW vSubtask )
{
   zVIEW  vMetaList;

   GetViewByName( &vMetaList, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );
   OrderEntityForView( vMetaList, "W_MetaDef", "LastUpdateDate D" );
   RefreshCtrl( vSubtask, "ListObjects" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
VOR_Prebuild( zVIEW vSubtask )
{
   zVIEW  vEdWrk;
   zVIEW  vParentSubtask;
   zVIEW  vList;

   // We need to get the parent subtask view so that we can retrieve the work view.
   GetParentWindow( &vParentSubtask, vSubtask );
   mGetWorkView( &vEdWrk, vParentSubtask );

   GetViewByName( &vList, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );
   if ( vList )
      DropView( vList );

   RetrieveViewForMetaList( vSubtask, &vList, zREFER_VOR_META );
   SetNameForView( vList, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
VOR_PasteName( zVIEW vSubtask )
{
   zVIEW    vList;
   zVIEW    vEdWrk;
   zVIEW    vTemp;
   zVIEW    vEditorSubtask;
   zPCHAR   szOption;
   zPCHAR   pchName;
   zCHAR    szMsg[ 200 ];

   GetViewByName( &vList, szlTZCMLPLO_List, vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vList, szlW_MetaDef ) != zCURSOR_SET )
      return( 0 );

   // Get the subtask for the editor window.
   GetParentWindow( &vTemp, vSubtask );
   GetParentWindow( &vEditorSubtask, vTemp );
   mGetWorkView( &vEdWrk, vEditorSubtask );

   GetAddrForAttribute( &szOption, vEdWrk, szlBuffer, szlPasteVorOption );
   GetAddrForAttribute( &pchName, vList, szlW_MetaDef, szlName );

   switch ( szOption[0] )
   {
      case 'N':
         strcpy_s( szMsg, zsizeof( szMsg ), pchName );
         break;

      case 'R':
         sprintf_s( szMsg, zsizeof( szMsg ), "VIEW %s REGISTERED AS %s", pchName, pchName );
         break;

      case 'G':
         sprintf_s( szMsg, zsizeof( szMsg ), "GET VIEW %s NAMED \"%s\"", pchName, pchName );
         break;

      case 'S':
         sprintf_s( szMsg, zsizeof( szMsg ), "NAME VIEW %s \"%s\"", pchName, pchName );
         break;

      case 'B':
      {
         zVIEW  vVOR;
         zPCHAR pchLOD_Name;

         ActivateMetaOI_ByName( vSubtask, &vVOR, 0, zREFER_VOR_META, zSINGLE | zLEVEL_APPLICATION, pchName, zCURRENT_OI );

         GetAddrForAttribute( &pchLOD_Name, vVOR, "LOD", "Name" );
         sprintf_s( szMsg, zsizeof( szMsg ), "VIEW %s BASED ON LOD %s", pchName, pchLOD_Name );

         DropMetaOI( vSubtask, vVOR );
         break;
      }
   }

// CString zs = szMsg;
// BSTR bstr = zs.AllocSysString( );
// KJS 11/11/16 - The last parameter is whether we should reset the position of the cursor, not sure why it's
// FALSE because we always set the cursor position to after what we've pasted. So I'm changing to TRUE.
   EDT_InsertItem( vSubtask, szMsg, TRUE );
   DropView( vList );


   //> fnSetFocusEditor( );
   //x pzma->SetFocus( );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
// Following structure contains a list of all standard VML insert strings.
// It is used only by VML_BuildTextList
/////////////////////////////////////////////////////////////////////////////
typedef struct _VML_TextStringRecord
{
   zPCHAR  pchText;
   zPCHAR  pchType;
   zPCHAR  pchInsertText;
   zPCHAR  pchInsertTextFull;
   zPCHAR  pchCC_Code;
   zPCHAR  pchCC_FirstChar;
} VML_TextStringRecord;

VML_TextStringRecord g_VML_TextStrings[] =
{
   "VIEW var-name BASED ON LOD lod-name", "D",
   "VIEW & BASED ON LOD ",
   "VIEW &var-name BASED ON LOD lod-name",
   "BOL", "Y",

   "VIEW var-name REGISTERED AS", "D",
   "VIEW & REGISTERED AS ",
   "VIEW &var-name REGISTERED AS regv-name",
   "VIEW", "Y",

   "INTEGER var-name", "D",
   "INTEGER &",
   "INTEGER &var-name",
   "", "",

   "SHORT var-name", "D",
   "SHORT &",
   "SHORT &var-name",
   "", "",

   "STRING ( lth ) var-name", "D",
   "STRING ( & ) ",
   "STRING ( &lth ) var-name",
   "STRING", "Y",

   "DECIMAL var-name", "D",
   "DECIMAL &",
   "DECIMAL &var-name",
   "", "",

   "CHARACTER var-name", "D",
   "CHARACTER &",
   "CHARACTER &var-name",
   "", "",

   "VIEW var-name", "D",
   "VIEW &",
   "VIEW &var-name",
   "", "",

   "ENTITYNAME var-name", "D",
   "ENTITYNAME &",
   "ENTITYNAME &var-name",
   "", "",

   "ATTRIBUTENAME var-name", "D",
   "ATTRIBUTENAME &",
   "ATTRIBUTENAME &var-name",
   "", "",

   "ACTIVATE view WHERE", "V",
   "ACTIVATE & WHERE ",
   "ACTIVATE &view [ FOR UPDATE ][ SINGLE | MULTIPLE | ROOTONLY | ROOTONLYMULTIPLE | EMPTY ]\r\n"
   "   [ WHERE Condition [ RESTRICTING Entity TO Condition ] ]",
   "ACTIVATE", "Y",

   "CASE int-var...", "C",
   "CASE &\r\n   OF :\r\nEND",
   "CASE &int-var\r\n   OF int-constant:\r\n   OTHERWISE:\r\nEND",
   "CASE", "Y",


   "COMMIT view", "V",
   "COMMIT &",
   "COMMIT &view",
   "", "",

   "CREATE ENTITY view.entity", "E",
   "CREATE ENTITY &",
   "CREATE ENTITY &view.entity [ AFTER | BEFORE | FIRST | LAST ]",
   "CREATE", "",

   "DELETE ENTITY view.entity", "E",
   "DELETE ENTITY &",
   "DELETE ENTITY &view.entity [ NEXT | PREVIOUS | FIRST | LAST | NONE ]",
   "DELETE", "Y",

   "EXCLUDE view.entity", "E",
   "EXCLUDE &",
   "EXCLUDE &view.entity [ AFTER | BEFORE | NONE ]",
   "EXCLUDE", "Y",

   "FOR view.entity ... END", "E",
   "FOR &\r\nEND",
   "FOR &[ EACH ] [ integer ] view.entity\r\n"
   "    [ WITHIN scoping-view.entity ]\r\n"
   "    [ WHERE condition ]\r\n"
   "END",
   "FOR", "Y",

   "GET VIEW view NAMED view-name", "V",
   "GET VIEW & NAMED \"\"",
   "GET VIEW &view NAMED \"view-name\"\r\n"
   "    [ AT LEVEL { TASK | SUBTASK | APPLICATION | SYSTEM | ANY } ] [ USING Subtask ]",
   "GET", "Y",

   "IF condition... END", "C",
   "IF &\r\nEND",
   "IF &condition\r\n[ ELSE ]\r\nEND",
   "IF", "Y",

   "IF condition... ELSE...END", "C",
   "IF &\r\nELSE\r\nEND",
   "IF &condition\r\nELSE\r\nEND",
   "IFE", "Y",

   "INCLUDE target-view.entity FROM source-view.entity", "E",
   "INCLUDE & FROM ",
   "INCLUDE &target-view.entity FROM source-view.entity [ AFTER | BEFORE ]",
   "INCLUDE", "Y",

   "LOOP ... END", "C",
   "LOOP &\r\nEND",
   "LOOP &[ WHILE condition ]\r\n{ END | UNTIL condition }",
   "LOOP", "Y",

   "LOOP WHILE condition... END", "C",
   "LOOP WHILE &\r\nEND",
   "LOOP WHILE &condition ]\r\nEND",
   "LOOPW", "Y",

   "LOOP ... UNTIL condition", "C",
   "LOOP\r\nUNTIL &",
   "LOOP\r\nUNTIL &condition",
   "LOOPU", "Y",

   "NAME VIEW view view-name", "V",
   "NAME VIEW & \"\"",
   "NAME VIEW &view \"view-name\"\r\n"
   "   [ AT LEVEL { TASK | SUBTASK | APPLICATION | SYSTEM | ANY } ] [ USING Subtask ]",
   "NAME", "Y",

   "SET CURSOR view.entity", "E",
   "SET CURSOR &",
   "SET CURSOR &[ FIRST | LAST | NEXT | PREVIOUS ] view.entity\r\n"
   "    [ WITHIN scoping-view.entity ]\r\n"
   "    [ WHERE condition ]",
   "SET", "Y",

   "SET CURSOR FIRST view.entity WHERE", "E",
   "SET CURSOR FIRST &\r\n    WHERE ",
   "SET CURSOR FIRST &view.entity\r\n"
   "    [ WITHIN scoping-view.entity ]\r\n"
   "    [ WHERE condition ]",
   "SETF", "Y",

   "SET CURSOR NEXT view.entity WHERE", "E",
   "SET CURSOR NEXT &\r\n    WHERE ",
   "SET CURSOR NEXT &view.entity\r\n"
   "    [ WITHIN scoping-view.entity ]\r\n"
   "    [ WHERE condition ]",
   "SETN", "Y",

   "=",  "O", "= ",  0, 0, 0,
   "!=", "O", "!= ", 0, 0, 0,
   "<=", "O", "<= ", 0, 0, 0,
   ">=", "O", ">= ", 0, 0, 0,
   "<",  "O", "< ",  0, 0, 0,
   ">",  "O", "> ",  0, 0, 0,
   "+",  "O", "+ ",  0, 0, 0,
   "-",  "O", "- ",  0, 0, 0,
   "*",  "O", "* ",  0, 0, 0,
   "/",  "O", "/ ",  0, 0, 0,
   "(",  "O", "( ",  0, 0, 0,
   ")",  "O", ") ",  0, 0, 0,

   "OR",  "O", "OR ",  0, 0, 0,
   "AND", "O", "AND ",  0, 0, 0,

   "space",     "?", " ",     0, 0, 0,
   "backspace", "?", "%ml1",  0, 0, 0,
   "newline",   "?", "\n&",   0, 0, 0,

   // Following indicates the end of the list:
   0, 0, 0, 0, 0, 0
};

/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT OPERATION
VML_DisplayList( zVIEW vSubtask )
{
   zVIEW  vProfileXFER;
   zVIEW  vEdWrk;
   zCHAR  szShowStr[ 10 ];
   zSHORT nRC;
   zLONG  lEntityCount, lSelectedCount;
   zCHAR  szMsg[ 100 ];

   mGetWorkView( &vEdWrk, vSubtask );
   mGetProfileView( &vProfileXFER, vSubtask );
   szShowStr[ 0 ] = 0;

   // Build a string that contains each of the VML types that the user wants shown.

   if ( CompareAttributeToString( vEdWrk, szlBuffer, "VML_ShowDeclarations", "Y" ) == 0 )
   {
      strcat_s( szShowStr, zsizeof( szShowStr ), "D" );
   }

   if ( CompareAttributeToString( vEdWrk, szlBuffer, "VML_ShowControlStatements", "Y" ) == 0 )
   {
      strcat_s( szShowStr, zsizeof( szShowStr ), "C" );
   }

   if ( CompareAttributeToString( vEdWrk, szlBuffer, "VML_ShowViewStatements", "Y" ) == 0 )
   {
      strcat_s( szShowStr, zsizeof( szShowStr ), "V" );
   }

   if ( CompareAttributeToString( vEdWrk, szlBuffer, "VML_ShowEntityStatements", "Y" ) == 0 )
   {
      strcat_s( szShowStr, zsizeof( szShowStr ), "E" );
   }

   if ( CompareAttributeToString( vEdWrk, szlBuffer, "VML_ShowOperators", "Y" ) == 0 )
   {
      strcat_s( szShowStr, zsizeof( szShowStr ), "O" );
   }

   if ( CompareAttributeToString( vEdWrk, szlBuffer, "VML_ShowOther", "Y" ) == 0 )
   {
      strcat_s( szShowStr, zsizeof( szShowStr ), "?" );
   }

   lEntityCount = 0;
   lSelectedCount = 0;

   // szShowStr lists all the types that the user wants shown. eg "CV?" means
   // that the user wants all control, view, and 'other' vml statements
   // shown.
   for ( nRC = SetCursorFirstEntity( vProfileXFER, "VML_Text", 0 );
         nRC == zCURSOR_SET;
         nRC = SetCursorNextEntity( vProfileXFER, "VML_Text", 0 ) )
   {
      zCHAR szType[ 5 ];

      lEntityCount++;

      GetStringFromAttribute( szType, zsizeof( szType ), vProfileXFER, "VML_Text", "Type" );
      if ( zstrchr( szShowStr, szType[0] ) )
      {
         SetSelectStateOfEntity( vProfileXFER, "VML_Text", TRUE );
         lSelectedCount++;
      }
      else
         SetSelectStateOfEntity( vProfileXFER, "VML_Text", FALSE );
   }

   SetCursorFirstSelectedEntity( vProfileXFER, "VML_Text", 0 );
   LB_SetDisplaySelectSet( vSubtask, "TextList", DISP_SELECT_SET );
   LB_SetSelectSelectSet( vSubtask, "TextList", SEL_SELECT_SET );

   sprintf_s( szMsg, zsizeof( szMsg ), "Listing %ld of %ld", lSelectedCount, lEntityCount );
   MB_SetMessage( vSubtask, 0, szMsg );
   return( 0 );

} // VML_DisplayList

zOPER_EXPORT zSHORT OPERATION
VML_BuildTextList( zVIEW vSubtask )
{
   zSHORT k;
   zVIEW  vProfileXFER;

   mGetProfileView( &vProfileXFER, vSubtask );

   // Add each of the 'standard' VML statements to the text list.
   for ( k = 0; g_VML_TextStrings[ k ].pchText != 0; k++ )
   {
      if ( SetCursorFirstEntityByString( vProfileXFER, "VML_Text", "Text", g_VML_TextStrings[ k ].pchText, 0 ) != zCURSOR_SET )
      {
         // Text doesn't exist, so create it.
         CreateEntity( vProfileXFER, "VML_Text", zPOS_LAST );

         SetAttributeFromString( vProfileXFER, "VML_Text", "Text", g_VML_TextStrings[ k ].pchText );
         SetAttributeFromString( vProfileXFER, "VML_Text", "Type", g_VML_TextStrings[ k ].pchType );
         SetAttributeFromString( vProfileXFER, "VML_Text", "UserDefined", "N" );

         if ( g_VML_TextStrings[ k ].pchInsertText )
            SetAttributeFromString( vProfileXFER, "VML_Text", "InsertText", g_VML_TextStrings[ k ].pchInsertText );

         if ( g_VML_TextStrings[ k ].pchInsertTextFull )
            SetAttributeFromString( vProfileXFER, "VML_Text", "InsertTextFull", g_VML_TextStrings[ k ].pchInsertTextFull );

         if ( g_VML_TextStrings[ k ].pchCC_Code )
            SetAttributeFromString( vProfileXFER, "VML_Text", "CC_Code", g_VML_TextStrings[ k ].pchCC_Code );

         if ( g_VML_TextStrings[ k ].pchCC_FirstChar )
            SetAttributeFromString( vProfileXFER, "VML_Text", "CC_FirstChar", g_VML_TextStrings[ k ].pchCC_FirstChar );
      }
   }

   OrderEntityForView( vProfileXFER, "VML_Text", "Text A" );
   VML_DisplayList( vSubtask );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
VML_Postbuild( zVIEW vSubtask )
{
   zVIEW vEdWrk;

   // Get the subtask view for the parent editor window and give it another
   // name at the current subtask level so we can easily retrieve it.
   GetViewByName( &vEdWrk, "__EditorSubtask", vSubtask, zLEVEL_TASK );
   SetNameForView( vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_SUBTASK );

   VML_DisplayList( vSubtask );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
VML_Close( zVIEW vSubtask )
{
   fnSaveSubwindowPosition( vSubtask, szlVML_Insert );
   return( 0 );
}

// Insert the currently selected text.
zSHORT LOCALOPER
fnInsertVML_Text( zVIEW      vSubtask,
                  zVIEW      vEdWrk,
                  zVIEW      vProfileXFER )
{
   zCHAR      szInsertString[ 1000 ];
   zPCHAR     pchStrBegin;
   zPCHAR     pchStrEnd;
   zLONG      lOriginalCol = 0;
   zLONG      lOriginalLine = 0;
   zLONG      lTabCount = 0, lTabSize = 4;
   zLONG      lPositionCursor;
   CString    csCompleteCommand;

   szInsertString[ 0 ] = 0;

   if ( lTabSize > 1 ) // don't ask why ... it's hard to explain
      lTabSize--;

   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlVML_InsertFull, "Y" ) == 0 )
   {
      GetStringFromAttribute( szInsertString, zsizeof( szInsertString ), vProfileXFER, szlVML_Text, szlInsertTextFull );
   }

   if ( szInsertString[ 0 ] == 0 )
   {
      GetStringFromAttribute( szInsertString, zsizeof( szInsertString ), vProfileXFER, szlVML_Text, szlInsertText );
   }

   if ( szInsertString[ 0 ] == 0 )
   {
      GetStringFromAttribute( szInsertString, zsizeof( szInsertString ), vProfileXFER, szlVML_Text, szlText );
   }

   if ( szInsertString[ 0 ] == 0 )
      return( 0 );

   lPositionCursor = (zstrchr( szInsertString, '&' ) != NULL);
   EDT_GetCursorPosition( vSubtask, &lOriginalLine, &lOriginalCol );

   // Tabs have to be replaced by a number of blanks.
   lTabCount = GetTabsInLine( vSubtask, lOriginalCol );

   lOriginalCol -= lTabCount;
   lOriginalCol += (lTabCount * lTabSize);

   // Insert each line seperately.  Setup insert string line by line.
   csCompleteCommand.Empty( );
   for ( pchStrBegin = szInsertString; *pchStrBegin; pchStrBegin = pchStrEnd )
   {
      zBOOL bMoreLines;

      // Find the end of the current line by looking for the '\n' char or the null terminator.
      for ( pchStrEnd = pchStrBegin;
            *pchStrEnd != '\n' && *pchStrEnd != '\r' && *pchStrEnd != 0;
            pchStrEnd++ )
      {
         ;  // nothing needs to be done here
      }

      // If we found a newline char, then change it to a null-terminator and
      // bump up pchStrEnd to point to the next char.
      if ( *pchStrEnd )
      {
         // If we found a carriage return, then a line feed is sure to follow, so skip both chars.
         if ( *pchStrEnd == '\r' )
            *pchStrEnd++ = 0;

         *pchStrEnd++ = 0;
         bMoreLines = TRUE;
      }
      else
         bMoreLines = FALSE;

      // Setup the string that has to be inserted
      csCompleteCommand += pchStrBegin;
      //pzma->InsertItem( pchStrBegin );

      if ( bMoreLines )
      {
         zCHAR  szTemp[ 100 ] = "\r\n";
         zSHORT k = (zSHORT) zstrlen( szTemp );

         // We need to add the new-line and then spaces to match original column position.
         zmemset( &szTemp[ k ], ' ', lOriginalCol );
         szTemp[ k + lOriginalCol ] = 0;

         csCompleteCommand += szTemp;
         //pzma->InsertItem( szTemp );
      }
   } // for...

   lPositionCursor = csCompleteCommand.Find( _T( "&" ) );
   if ( lPositionCursor > 0 )
   {
      // Get rid of that "&" so we don't have to call DeleteTextRange
      CString csLeft = csCompleteCommand.Left( lPositionCursor - 1 );
      CString csRight = csCompleteCommand.Right( csCompleteCommand.GetLength() - (lPositionCursor + 1) );
      csLeft.TrimRight();
      csCompleteCommand = csLeft + csRight;
      lPositionCursor--;
   }

   // KJS 11/11/16 - The last parameter is whether we should reset the position of the cursor, not sure why it's
   // FALSE because we always set the cursor position to after what we've pasted. So I'm changing to TRUE.
   EDT_InsertItem( vSubtask, csCompleteCommand, TRUE );

   if ( lPositionCursor >= 0 )
   {
      EDT_SetCursorPositionByLineCol( vSubtask, lOriginalLine, lOriginalCol + lPositionCursor );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
VML_InsertText( zVIEW vSubtask )
{
   zVIEW      vEdWrk;
   zVIEW      vEditorSubtask;
   zVIEW      vProfileXFER;

   mGetProfileView( &vProfileXFER, vSubtask );
   mGetWorkView( &vEdWrk, vSubtask );
   GetParentWindow( &vEditorSubtask, vSubtask );

   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlReadOnly, "Y" ) != 0 &&
        CompareAttributeToString( vEdWrk, szlBuffer, szlActiveStatus, "N" ) != 0 )
   {
      fnInsertVML_Text( vEditorSubtask, vEdWrk, vProfileXFER );
   }

   // Set Focus to Editor
   SetFocusToCtrl( vEditorSubtask, EDIT_CONTROL_NAME );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
VML_ShowPopupMenu( zVIEW vSubtask )
{
// POINT  pt;
   CPoint pt( GetMessagePos( ) );
// pt.x = pt.y = -1;
   CreateTrackingPopupMenu( vSubtask, "Popup", pt.x, pt.y, FALSE, FALSE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
VML_CreateText_Exit( zVIEW vSubtask )
{
   zVIEW  vProfileXFER;

   mGetProfileView( &vProfileXFER, vSubtask );
   OrderEntityForView( vProfileXFER, "VML_Text", "Text A" );
   return( 0 );

} // VML_CreateText_Exit

zOPER_EXPORT zSHORT OPERATION
VML_CreateText_DeleteAll( zVIEW vSubtask )
{
   zVIEW  vProfileXFER;
   zSHORT nRC;

   if ( MessagePrompt( vSubtask, "ED0101", "Zeidon Editor",
                       "Delete All VML Keywords?", 0, zBUTTONS_YESNO,
                       zRESPONSE_NO, zICON_QUESTION ) == zRESPONSE_NO )
   {
      return( 0 );
   }

   mGetProfileView( &vProfileXFER, vSubtask );
   for ( nRC = SetCursorFirstEntity( vProfileXFER, "VML_Text", 0 );
         nRC == zCURSOR_SET;
         nRC = SetCursorNextEntity( vProfileXFER, "VML_Text", 0 ) )
   {
      DeleteEntity( vProfileXFER, "VML_Text", zREPOS_NONE );
   }

   return( 0 );

} // VML_CreateText_DeleteAll

zOPER_EXPORT zSHORT OPERATION
VML_SelectItem( zVIEW vSubtask )
{
   MB_SetMessage( vSubtask, 0, "Press F1 for Help on this item." );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
VML_StartHelp( zVIEW vSubtask )
{

   zCHAR  szBuffer[60];
   zPCHAR pchText;

   zSHORT nRC;
   zSHORT k;
   zSHORT j;

   zVIEW  vProfileXFER;

   // GET ADDRESS OF THE STRING FOR THE TEXT IN THE LIST BOX
   mGetProfileView( &vProfileXFER, vSubtask );
   GetAddrForAttribute( &pchText,       // Return Address
                        vProfileXFER,  // View Id
                        "VML_Text",    // Entity name
                        "Text" ); // Attribute Name

   // EXTRACT FIRST ALL CAP WORD FROM pchText
   k = 0;
   j = 0;

   // look for first cap
   while ( !isupper( pchText[ k ] ) &&  // not upper case
           pchText[ k ] != 0 )          // not null terminator
   {
      k++;
   }

   // if no cap is found, no help is available. get out now.
   if ( pchText[ k ] == 0)
   {
      MB_SetMessage( vSubtask, 0, "Help for this operation is not currently available." );
      return( 0 );
   }

   // copy first all cap word into the buffer
   while ( isupper( pchText[ k ] )  &&      // upper case
           pchText[ k ] != 0 &&             // not null terminator
           j < 59 )                         // room left in buffer
   {
      szBuffer[ j++ ] = pchText[ k++ ];
   }

   szBuffer[ j ] = 0;

   // CALL HELP
   nRC = StartZeidonHelp( vSubtask, szBuffer );

   // IF HELP WAS NOT FOUND, NOTIFY THE USER.
   if ( nRC == zCALL_ERROR )
   {
      MB_SetMessage( vSubtask, 0, "Help for this item is not available." );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ErrList_GetFocus( zVIEW vSubtask )
{
   zVIEW  vEdWrk;
   zLONG  hFile;
   zCHAR  szFileName[ zMAX_FILENAME_LTH + 1 ];
   zPCHAR pch;

   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
      return( 0 );         // We haven't built the window yet so exit.

   if ( CheckExistenceOfEntity( vEdWrk, "ErrorList" ) == zCURSOR_SET )
      // Error list is OK so exit.
      return( 0 );

   CreateEntity( vEdWrk, "ErrorList", zPOS_LAST );

   // Create the error file name.
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vEdWrk, szlBuffer, szlFileName );
   pch = szFileName + zstrlen( szFileName ) - 3;
   strcpy_s( pch, zsizeof( szFileName ) - zstrlen( szFileName ) + 3, "ERR" );     // Change ".VML" to ".ERR".

   hFile = SysOpenFile( vSubtask, szFileName, COREFILE_READ );
   if ( hFile == -1 )
      return( 0 );         // No error file means no error messages.

   // Parse each line into seperate messages.
   while ( SysReadLine( vSubtask, &pch, hFile ) == 1 )
   {
      zPCHAR pch2;

      // Sample error message:
      // c:\9j\a\tz\TZDBHTSD.VML(425) : error 539: An operation blah blah...

      // Look for open paren.  If none found skip the line.
      pch2 = strchr( pch, '(' );
      if ( pch2 == 0 )
         continue;

      // Find close paren.
      pch2++;  // Skip open paren.
      pch = strchr( pch2, ')' );
      if ( pch == 0 )
         continue;

      *pch++ = 0; // Set close paren to 0 and bump up pointer.

      // Is line number numeric???
      // When no compilation is needed compiler generates a message "Skipping (no relevant changes detected)"
      zBOOL bIsNumeric = TRUE;
      zPCHAR pch3 = pch2;

      while ( *pch3 && bIsNumeric == TRUE )
      {
         if ( isdigit( *pch3 ) == 0 )
         {
            bIsNumeric = FALSE;
         }
         pch3++;
      }

      if ( !bIsNumeric )
         continue;

      // We have an error message so create entity.
      CreateEntity( vEdWrk, "Error", zPOS_LAST );

      SetAttributeFromString( vEdWrk, "Error", "LineNumber", pch2 );

      // Skip first ':'.
      pch = strchr( pch, ':' );
      if ( pch == 0 )
         continue;

      // Skip second ':'.
      pch = strchr( ++pch, ':' );
      if ( pch == 0 )
         continue;

      pch += 2;  // Skip ": ".
      SetAttributeFromString( vEdWrk, "Error", "ErrorText", pch );
   }

   SysCloseFile( vSubtask, hFile, 0 );
   RefreshCtrl( vSubtask, "ErrorList" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ErrList_Postbuild( zVIEW vSubtask )
{
   zVIEW vEdWrk;

   // Get the subtask view for the parent editor window and give it another
   // name at the current subtask level so we can easily retrieve it.
   GetViewByName( &vEdWrk, "__EditorSubtask", vSubtask, zLEVEL_TASK );
   SetNameForView( vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_SUBTASK );

   // Call the GetFocus code to build the error list.
   ErrList_GetFocus( vSubtask );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ErrList_Close( zVIEW vSubtask )
{
   fnSaveSubwindowPosition( vSubtask, szlErrorList );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ErrList_ShowError( zVIEW vSubtask )
{
   zVIEW    vEdWrk;
   zVIEW    vEditorSubtask;
   zLONG    lErrorLine, lLine, lCol;

   lLine = lCol = lLine = 0;

   mGetWorkView( &vEdWrk, vSubtask );
   GetParentWindow( &vEditorSubtask, vSubtask );

   GetIntegerFromAttribute( &lErrorLine, vEdWrk, "Error", "LineNumber" );
   lErrorLine--;

   // Set cursor only if it is not already there, otherwise the Editctrl will scroll up for
   // one line and this will drive "evil" crazy.
   EDT_GetCursorPosition( vEditorSubtask, &lLine, &lCol );
   if ( lErrorLine != lLine )
   {
      EDT_SetCursorPositionByLineCol( vEditorSubtask, lErrorLine, 0 );
   }

   SetFocusToCtrl( vEditorSubtask, EDIT_CONTROL_NAME );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT OPERATION
SaveFile( zVIEW vSubtask )
{
   //if ( fnTZEDFRMD_SaveFile( vSubtask, pzma, szFileName, PARSE_FILE ) < 0 )
   // KJS 06/19/12 - I would like SaveFile to only save the file not prompt for parsing.  This is
   // because then everytime the user "saves" it prompts to parse either c or vml and always parses
   // one of them.  I don't want to always parse.
   return( EDT_SaveFile( vSubtask ) );
}

zSHORT
fnParseIt( zVIEW vSubtask, zVIEW vEdWrk, zVIEW vSource, zPCHAR pchFileName, zCPCHAR cpcGenLang, zBOOL bMsg )
{
   zCHAR  szMsg[ 300 ];
   zVIEW  vWindow;
   zLONG  lParseAction = zPARSE_ACTION_FULL;
   zLONG  lParseLimit  = zPARSE_LIMIT_SOURCE;
   zLONG  lParseSource = zPARSE_SOURCE_FILE;
   zLONG  lMetaType;
   zBOOL  bReadOnly = FALSE;
   zSHORT nRC;
   zPCHAR pch = strrchr( pchFileName, '\\' );
   if ( pch )
      pch++;
   else
      pch = pchFileName;

   sprintf( szMsg, "Parsing File '%s'...", pchFileName );
   MB_SetMessage( vSubtask, MAIN_DIL, szMsg );

   if ( !MiGetUpdateForView( vSource ) )
   {
      bReadOnly = TRUE;
      SetViewUpdate( vSource );
   }

   GetIntegerFromAttribute( &lMetaType, vEdWrk, szlBuffer, szlMetaType );

   zPCHAR pchDot = strrchr( pchFileName, '.' );
   if ( pchDot )
      *pchDot = 0;

   nRC = (zSHORT) ParseSource( vSubtask, vSource, lParseAction, lParseLimit, lParseSource,
                               pch, "", lMetaType, 0, cpcGenLang );
   if ( pchDot )
      *pchDot = '.';

   if ( bReadOnly )
      SetViewReadOnly( vSource );

   // If we get here then we want to make sure that the error list needs to be reloaded.
   if ( CheckExistenceOfEntity( vEdWrk, "ErrorList" ) == zCURSOR_SET )
      DeleteEntity( vEdWrk, "ErrorList", zREPOS_FIRST );

   if ( nRC < 0 )
   {
      SetCursorFirstEntity( vEdWrk, "Error", 0 );

      // Fire up the error list window.
      TZEDFRMD_OpenSubwindow( vSubtask );
      SetWindowActionBehavior( vSubtask, zWAB_StartOrFocusModelessSubwindow | zWAB_ProcessImmediateAction,
                               szlTZEDFRMD, "ErrorList" );

      sprintf_s( szMsg, zsizeof( szMsg ), "Error parsing File '%s'", pchFileName );
      MB_SetMessage( vSubtask, MAIN_DIL, szMsg );

      // There is a parse error.  If performing exit, then show one message,
      // otherwise show message that allows user to go directly to the error file.
      if ( FALSE ) //> performing exit.
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Parse completed with Errors.\n\nSee Error File for list of errors." );
         nRC = MessagePrompt( vSubtask, "ED0003", szlZeidonEditor, szMsg, 1, 0, 0, zICON_ERROR );
      }

      nRC = 1;
   }
   else
   {
      // Close Error List
      if ( GetSubtaskForWindowName( vSubtask, &vWindow, "ErrorList" ) >= 0 )
         SetWindowActionBehavior( vWindow, zWAB_ReturnToParent | zWAB_ProcessImmediateAction | zWAB_ProcessImmediateReturn, 0, 0 );

      sprintf_s( szMsg, zsizeof( szMsg ), "Parse completed successfully for: '%s'", pchFileName );
      MB_SetMessage( vSubtask, MAIN_DIL, szMsg );
      if ( bMsg )
         MessagePrompt( vSubtask, "ED0004", szlZeidonEditor, szMsg, 0, 0, 0, zICON_INFORMATION );
      nRC = 0;
   }

   return( nRC );
}

zOPER_EXPORT zSHORT OPERATION
SaveAndParse( zVIEW vSubtask, zCPCHAR cpcGenLang, zBOOL bMsg )
{
   zCHAR  szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR  szMsg[ 300 ];
   zVIEW  vEdWrk;
   zVIEW  vSource;
   zSHORT nRC = 0;

   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "TZEDWRKO not Available at SaveAndParse." );
      MessagePrompt( vSubtask, "ED0005", szlZeidonEditor, szMsg, 1, 0, 0, zICON_EXCLAMATION );
      return( 0 );
   }

   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) != 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Parse only valid with VML Files." );
      MessagePrompt( vSubtask, "ED0006", szlZeidonEditor,
                     szMsg, 1, 0, 0, zICON_EXCLAMATION );
      return( 1 );
   }

   // Get the Source Meta for the current buffer.
   GetIntegerFromAttribute( (zPLONG) &vSource, vEdWrk, szlBuffer, szlSourceViewID );
   if ( vSource == 0 )
   {
      MessagePrompt( vSubtask, "ED0106", szlZeidonEditor,
                     "Cannot parse VML that has been opened via File/Open",
                     TRUE, zBUTTONS_OK, 0, zICON_ERROR );
      return( 1 );
   }

   // Check if anything has changed
   if ( EDT_IsFileChanged( vSubtask ) )
   {
      EDT_SaveFile( vSubtask );
      SetUpdateFlagInMeta( vSubtask );
   }

   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vEdWrk, szlBuffer, szlFileName );
   nRC = fnParseIt( vSubtask, vEdWrk, vSource, szFileName, cpcGenLang, bMsg );
   return( nRC );
}

zOPER_EXPORT zSHORT OPERATION
SaveAndParseC( zVIEW vSubtask )
{
   return( SaveAndParse( vSubtask, "C", TRUE ) );
}

zOPER_EXPORT zSHORT OPERATION
SaveAndParseJava( zVIEW vSubtask )
{
   return( SaveAndParse( vSubtask, "Java", TRUE ) );
}

zOPER_EXPORT zSHORT OPERATION
Generate( zVIEW vSubtask, zCPCHAR cpcGenLang, zBOOL bMsg )
{
   zVIEW    vEdWrk;
   zVIEW    vSource;
   zCHAR    szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR    szMsg[ 100 ];
   zPCHAR   pch;
   zLONG    lChanged = 0;
   zLONG    lType = 0;
   zSHORT   nRC;

   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "TZEDWRKO not Available at _zfGenerateCFile." );
      SysMessageBox( vSubtask, szlZeidonEditor, szMsg, 1 );
      return( 0 );
   }

   // Get the Source Meta for the current buffer.
   GetIntegerFromAttribute( (zPLONG) &vSource, vEdWrk, szlBuffer, szlSourceViewID );
   if ( vSource == 0 )
   {
      MessagePrompt( vSubtask, "ED0107", szlZeidonEditor,
                     "Cannot generate VML that has been opened via File/Open",
                     TRUE, zBUTTONS_OK, 0, zICON_ERROR );
      return( 1 );
   }

   //>SetUserFlagsOn( zUF_CurrentlyParsing );

   lChanged = EDT_IsFileChanged( vSubtask );
   if ( lChanged )
   {
      MB_SetMessage( vSubtask, MAIN_DIL, "Saving file..." );
      EDT_SaveFile( vSubtask );
      SetUpdateFlagInMeta( vSubtask );
   }

   GetIntegerFromAttribute( &lType, vEdWrk, szlBuffer, szlMetaType );
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vEdWrk, szlBuffer, szlFileName );

   // Drop the '.VML' from the file name.
   pch = szFileName + zstrlen( szFileName );
   pch -= 4;
   *pch = 0;

   // Now set up pch to point to the beginning of the filename.
   while ( pch > szFileName && *pch != '\\' )
      pch--;

   pch++;

   nRC = Generate3GL( vSubtask, vSubtask, vSource, pch, cpcGenLang, lType );

   if ( nRC < 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Errors in Generate." );
      strcat_s( szMsg, zsizeof( szMsg ), "\n\nSee Messages in Error Box" );
      SysMessageBox( vSubtask, szlZeidonEditor, szMsg, 1 );
      nRC = 1;
   }
   else
   {
      if ( bMsg )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Generate completed successfully." );
         MessagePrompt( vSubtask, "ED0007", szlZeidonEditor, szMsg, 0, 0, 0, zICON_INFORMATION );
      }
      nRC = 0;
   }

   //> SetUserFlagsOff( zUF_CurrentlyParsing );
   return( nRC );
}

zOPER_EXPORT zSHORT OPERATION
GenerateC( zVIEW vSubtask )
{
   return( Generate( vSubtask, "C", TRUE ) );
}

zOPER_EXPORT zSHORT OPERATION
GenerateJava( zVIEW vSubtask )
{
   return( Generate( vSubtask, "Java", TRUE ) );
}

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: GenerateCompileJava
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
GenerateCompileJava( zVIEW vSubtask )
{
   zVIEW    vLPLR;
   zSHORT   nRC;
   zCHAR    szSystemApp[ 65 ] = { 0 };
   zCHAR    szJavaCompileBat[ 256 ] = { 0 };
   zCHAR    szLPLR_Name[ 33 ] = { 0 };

   nRC = Generate( vSubtask, "Java", TRUE );

   if ( nRC )
      return( nRC );

   // KJS 08/21/14
   GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   GetVariableFromAttribute( szLPLR_Name, 0, 'S', 33, vLPLR, "LPLR", "Name", "", 0 );
   ZeidonStringCopy( szSystemApp, 1, 0, "[App.", 1, 0, 65 );
   ZeidonStringConcat( szSystemApp, 1, 0, szLPLR_Name, 1, 0, 65 );
   ZeidonStringConcat( szSystemApp, 1, 0, "]", 1, 0, 65 );

   // KJS 08/21/14 - Get JavaCompileBat from the zeidon.ini and run it (currently we are using maven for compile).
   SysReadZeidonIni( -1, szSystemApp, "JavaCompileBat", szJavaCompileBat, zsizeof( szJavaCompileBat ) );
   if ( szJavaCompileBat[ 0 ] )
      system( szJavaCompileBat );
   else
      MessageBox( NULL, "Generate/Compile Java", "Unable to locate JavaCompileBat in Zeidon.ini", MB_OK | MB_ICONINFORMATION );

   return nRC;

} // GenerateCompileJava

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: CompileJava
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
CompileJava( zVIEW vSubtask )
{
   zVIEW    vLPLR;
   zCHAR    szSystemApp[ 65 ] = { 0 };
   zCHAR    szJavaCompileBat[ 256 ] = { 0 };
   zCHAR    szLPLR_Name[ 33 ] = { 0 };

   // KJS 08/21/14
   GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   GetVariableFromAttribute( szLPLR_Name, 0, 'S', 33, vLPLR, "LPLR", "Name", "", 0 );
   ZeidonStringCopy( szSystemApp, 1, 0, "[App.", 1, 0, 65 );
   ZeidonStringConcat( szSystemApp, 1, 0, szLPLR_Name, 1, 0, 65 );
   ZeidonStringConcat( szSystemApp, 1, 0, "]", 1, 0, 65 );

   // KJS 08/21/14 - Get JavaCompileBat from the zeidon.ini and run it (currently we are using maven for compile).
   SysReadZeidonIni( -1, szSystemApp, "JavaCompileBat", szJavaCompileBat, zsizeof( szJavaCompileBat ) );
   system( szJavaCompileBat );

   return 0;

} // CompileJava

static zSHORT /*LOCAL */
fnTZEDFRMD_SaveFile( zVIEW    vSubtask,
                     zPCHAR   pchFileName,
                     zLONG    lMaxLth,
                     zSHORT   nAskForParse )
{
   zULONG  ulZFlags   = 0;
   BOOL    bFileSaved = FALSE;

   if ( EDT_IsFileChanged( vSubtask ) )
   {
      ulZFlags = zOFN_OVERWRITEPROMPT | zOFN_CREATEPROMPT | zOFN_SAVEAS;
      if ( OperatorPromptForFile( vSubtask, pchFileName, (zSHORT) lMaxLth,
                                  "VML files|*.VML|Source Files|*.VML;*.C|All files|*.*||", 0, ulZFlags ) != 1 )
      {
         return( -1 );
      }

      bFileSaved = EDT_SaveFileAs( vSubtask, pchFileName );
      if ( bFileSaved == TRUE )
      {
         SetWindowCaptionTitle( vSubtask, "Zeidon Editor", pchFileName);
      }
   }
   else
   {
      zVIEW vEdWrk;

      mGetWorkView( &vEdWrk, vSubtask );
      if ( vEdWrk == 0 )
      {
         MessagePrompt( vSubtask, "ED0008", szlZeidonEditor,
                        "TZEDWRKO not Available at SaveFile.", 1,
                        0, 0, zICON_EXCLAMATION );
         return( -1 );
      }

      bFileSaved = EDT_SaveFile( vSubtask );

      // Parse only valid for VML-Files.
      if ( nAskForParse == PARSE_FILE &&
         CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlVML_File ) == 0 )
      {
         CString csMsg;

         GetStringFromAttribute( pchFileName, lMaxLth, vEdWrk, szlBuffer, szlFileName );
         csMsg.Format("Do you want to parse '%s' for C (Yes) or Java (No)?",pchFileName);
         zLONG lRC = OperatorPrompt( vSubtask, szlZeidonEditor, csMsg, TRUE,
                                     zBUTTONS_YESNOCANCEL, zRESPONSE_YES, zICON_EXCLAMATION );

         if ( lRC == zRESPONSE_YES )
         {
            if ( SaveAndParse( vSubtask, "C", TRUE ) != 0 )
               return( -1 );
         }
         else
            if ( lRC == zRESPONSE_NO )
            {
               if ( SaveAndParse( vSubtask, "Java", TRUE ) != 0 )
                  return( -1 );
            }
      }
   } // end if ( EDT_IsFileChanged )

   if ( bFileSaved )
      MB_SetMessage( vSubtask, MAIN_DIL, "File saved." );
   else
      MB_SetMessage( vSubtask, MAIN_DIL, "File not changed." );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_AskForSaveWithParse
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
TZEDFRMD_AskForSaveWithParse( zVIEW vSubtask,
                              zSHORT nAskForParse )
{
   zVIEW    vEdWrk;
   zCHAR    szFileName[ zMAX_FILENAME_LTH + 1 ];
   zULONG   ulZFlags = 0;

   mGetWorkView( &vEdWrk, vSubtask );

   // Check if file changed.
   if ( EDT_IsFileChanged( vSubtask ) == FALSE )
      return( 0 );

   zSHORT nRC = 0;
   zCHAR  szMsg[ zMAX_FILENAME_LTH + 200 ];

   if ( EDT_IsFileChanged( vSubtask ) == FALSE)
   {
      // Get current file name.
      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vEdWrk, szlBuffer, szlFileName );
   }
   else
   {
      // This is a good name for a new source.
      strcpy_s( szFileName, zsizeof( szFileName ), "Noname.vml" );
   }

   sprintf_s( szMsg, zsizeof( szMsg ), "File '%s' has changed. Do you want to save it?", szFileName );
   nRC = OperatorPrompt( vSubtask, szlZeidonEditor, szMsg, TRUE,
                         zBUTTONS_YESNOCANCEL, zRESPONSE_YES, zICON_EXCLAMATION );

   if ( nRC == zRESPONSE_CANCEL )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }
   else
      if ( nRC == zRESPONSE_YES )
      {
         if ( fnTZEDFRMD_SaveFile( vSubtask, szFileName, zsizeof( szFileName ), nAskForParse ) < 0 )
         {
            SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
            return( -1 );
         }

         SetUpdateFlagInMeta( vSubtask );
      }

   return( 0 );
} // TZEDFRMD_AskForSaveWithParse

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: TZEDFRMD_AskForSave
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_AskForSave( zVIEW vSubtask )
{
   zVIEW        vEdWrk;
   zVIEW        vSource;
   zVIEW        vMeta;
   zVIEW        vTaskLPLR;
   zLONG        lMetaZKey;
   zSHORT       nRC = zCALL_ERROR;
   LPVIEWOD     lpViewOD;
   LPVIEWENTITY lpViewEntity;


   if ( TZEDFRMD_AskForSaveWithParse( vSubtask, FILE_NO_PARSE ) < 0 )
      return( nRC );

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) < 0 )
      return( nRC );

   // if no selection found, select current meta
   if ( CheckExistenceOfEntity( vTaskLPLR, "TargetExecutable" ) != zCURSOR_SET ||
      SetCursorFirstSelectedEntity( vTaskLPLR, "TargetExecutable", "" ) >= zCURSOR_SET )
   {
      return( 0 );
   }

   // get current Meta
   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
      return( nRC );

   // Get the Source Meta for the current buffer.
   GetIntegerFromAttribute( (zPLONG) &vSource, vEdWrk, szlBuffer, szlSourceViewID );

   if ( vSource == 0 ||
      CompareAttributeToString( vEdWrk, szlBuffer, szlMetaType, "" ) == 0 )
   {
      return( nRC );
   }

   CreateViewFromViewForTask( &vMeta, vSource, 0 );
   ResetView( vMeta );

   // Get Root Entity Name
   lpViewOD = (LPVIEWOD) MiGetViewEntityForView( vMeta, 0 );
   if ( !lpViewOD )
      return( nRC );

   lpViewEntity = (LPVIEWENTITY) SysGetPointerFromHandle( lpViewOD->hFirstOD_Entity );

   GetIntegerFromAttribute( &lMetaZKey, vMeta, lpViewEntity->szName, "ZKey" );

   if ( SetCursorFirstEntityByInteger( vTaskLPLR, "Meta", "ZKey",
      lMetaZKey, "LPLR" ) >= zCURSOR_SET )
   {
      SetSelectStateOfEntity( vTaskLPLR, "TargetExecutable", TRUE );
   }

   DropView( vMeta );

   return( 0 );
} // TZEDFRMD_AskForSave

zOPER_EXPORT zSHORT OPERATION
FileSaveAs( zVIEW vSubtask )
{
   zVIEW      vEdWrk;
   zCHAR      szMsg[ zMAX_FILENAME_LTH + 40 ];
   zCHAR      szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR      szExtension[ 4 ];
   zULONG     ulZFlags = 0;

   mGetWorkView( &vEdWrk, vSubtask );

   if ( EDT_IsFileChanged( vSubtask ) )
   {
      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vEdWrk, szlBuffer, szlFileName );
   }
   else
   {
      GetStringFromAttribute( szExtension, zsizeof( szExtension ), vEdWrk, szlBuffer, szlLanguageType);
      strcpy_s( szFileName, zsizeof( szFileName ), "NONAME." );
      if ( zstrcmp( szExtension, szlC_File ) != 0 )
         strcpy_s( szExtension, zsizeof( szExtension ), szlVML_FileExtension );

      strcat_s( szFileName, zsizeof( szFileName ), szExtension );
   }

   ulZFlags = zOFN_OVERWRITEPROMPT | zOFN_CREATEPROMPT | zOFN_SAVEAS;

   if ( OperatorPromptForFile( vSubtask, szFileName, zMAX_FILENAME_LTH + 1,
                               "VML files|*.VML|Source Files|*.VML;*.C|All files|*.*||", 0, ulZFlags ) != 1 )
   {
      return( -1 );
   }

   if ( EDT_SaveFileAs( vSubtask, szFileName ) )
   {
      sprintf_s( szMsg, zsizeof( szMsg ), "File saved as '%s'.", szFileName );
      MB_SetMessage( vSubtask, MAIN_DIL, szMsg );
      SetAttributeFromString( vEdWrk, szlBuffer, szlFileName, szFileName );
      SetWindowCaptionTitle( vSubtask, "Zeidon Editor", szFileName );
   }

   return( 0 );
}

zSHORT
fnSaveWithCheckForParse( zVIEW vSubtask )
{
   zCHAR  szMsg[ 300 ];
   zVIEW   vEdWrk;
   zVIEW   vSource;

   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "TZEDWRKO not Available at SaveAndParse." );
      MessagePrompt( vSubtask, "ED0009", szlZeidonEditor, szMsg, 1, 0, 0, zICON_EXCLAMATION );
      return( 0 );
   }

   // Get the Source Meta for the current buffer.
   GetIntegerFromAttribute( (zPLONG) &vSource, vEdWrk, szlBuffer, szlSourceViewID );
   if ( vSource == 0 )
   {
      MessagePrompt( vSubtask, "ED0106", szlZeidonEditor,
                     "Cannot parse VML that has been opened via File/Open",
                     TRUE, zBUTTONS_OK, 0, zICON_ERROR );
      return( 1 );
   }

   if ( EDT_IsFileChanged( vSubtask ) )
   {
      zSHORT nRC = OperatorPrompt( vSubtask, szlZeidonEditor, "Do you want to save the changes?", TRUE,
                                   zBUTTONS_YESNOCANCEL, zRESPONSE_YES, zICON_EXCLAMATION );
      if ( nRC == zRESPONSE_CANCEL )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( -1 );  // should probably be staying put on the editor
      }
      else
      if ( nRC == zRESPONSE_YES)
      {
         zCHAR  szFileName[ zMAX_FILENAME_LTH + 1 ];
         zCHAR chType = EDT_GetObjectName( vSubtask, szFileName, zsizeof( szFileName ) );
         zBOOL bNew = EDT_IsFileNew( vSubtask );
         if ( bNew )
         {
            nRC = FileSaveAs( vSubtask );
         }
         else
         {
            nRC = EDT_SaveFile( vSubtask );
         }

         if ( nRC >= 0 && chType == 'V' )  // parse only valid for VML-Files.
         {
            CString csMsg;

            csMsg.Format( "Do you want to parse '%s' for C (Yes) or Java (No)?", szFileName );
            zLONG lRC = OperatorPrompt( vSubtask, szlZeidonEditor, csMsg, TRUE,
                                        zBUTTONS_YESNOCANCEL, zRESPONSE_YES, zICON_EXCLAMATION );
            if ( lRC == zRESPONSE_YES )
            {
               nRC = fnParseIt( vSubtask, vEdWrk, vSource, szFileName, "C", TRUE );
            }
            else
            if ( lRC == zRESPONSE_NO )
            {
               nRC = fnParseIt( vSubtask, vEdWrk, vSource, szFileName, "Java", TRUE );
            }
         }
         return( nRC );
      }
   }

   return( 0 );  // don't need to do anything
}

zOPER_EXPORT zSHORT OPERATION
FileNew( zVIEW vSubtask )
{
   zBOOL bNew = EDT_IsFileNew( vSubtask );

   if ( EDT_IsFileChanged( vSubtask ) )
   {
      if ( fnSaveWithCheckForParse( vSubtask ) < 0 )
         return( -1 );
   }

   zVIEW  vEdWrk;
   zCHAR  szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR  szExtension[ zMAX_FILENAME_LTH + 1 ];
   EDT_CloseObject( vSubtask );

   mGetWorkView( &vEdWrk, vSubtask );
   GetStringFromAttribute( szExtension, zsizeof( szExtension ), vEdWrk, szlBuffer, szlLanguageType );
   strcpy_s( szFileName, zsizeof( szFileName ), "NONAME." );
   if ( zstrcmp( szExtension, szlC_File ) != 0 )
      strcpy_s( szExtension, zsizeof( szExtension ), szlVML_FileExtension );
   else
      strcpy_s( szExtension, zsizeof( szExtension ), szlVML_FileExtension );

   strcat_s( szFileName, zsizeof( szFileName ), szExtension );
   SetAttributeFromString( vEdWrk, szlBuffer, szlFileName, szFileName );
   EDT_OpenNewObject( vSubtask, szFileName );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zTZEDFRMD_OpenFile( zVIEW vSubtask )
{
   zVIEW  vEdWrk;
// zVIEW  vParentSubtask;
   zSHORT nRC;
   zCHAR  szFileName[ zMAX_FILENAME_LTH + 1 ];
   zULONG ulZFlags = zOFN_OVERWRITEPROMPT | zOFN_CREATEPROMPT;

   if ( EDT_IsFileChanged( vSubtask ) )
   {
      if ( fnSaveWithCheckForParse( vSubtask ) < 0 )
         return( -1 );
   }

   mGetWorkView( &vEdWrk, vSubtask );
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vEdWrk, szlBuffer, szlFileName );

   if ( OperatorPromptForFile( vSubtask, szFileName, zMAX_FILENAME_LTH + 1,
                               "VML files|*.VML|Source Files|*.VML;*.C|All files|*.*||", 0, ulZFlags) != 1 )
   {
      return( 0 );
   }

// EDT_CloseObject( vSubtask );

// CreateViewFromViewForTask( &vTempEdWrk, vEdWrk ); why??? dks 2004.12.06
   nRC = SetCursorFirstEntityByString( vEdWrk, szlBuffer, szlFileName, szFileName, 0 );
   if ( nRC == zCURSOR_SET )
   {
      zCHAR szMsg[ zMAX_FILENAME_LTH + 100 ];

      sprintf_s( szMsg, zsizeof( szMsg ), "File '%s' is already being edited.  Open new window in Read-Only mode?", szFileName );
      nRC = OperatorPrompt( vSubtask, szlZeidonEditor, szMsg, TRUE,
                            zBUTTONS_YESNOCANCEL, zRESPONSE_NO, zICON_EXCLAMATION );

      if ( nRC == zRESPONSE_CANCEL )
      {
      // DropView( vTempEdWrk );
         return( 0 );
      }

      if ( nRC == zRESPONSE_NO )
      {
      // GetIntegerFromAttribute( (zPLONG) &vEditorSubtask, vEdWrk, szlBuffer, "vSubtask" );
      // DropView( vTempEdWrk );
         SetFocusToCtrl( vSubtask, EDIT_CONTROL_NAME );
         return( 0 );
      }

      // Indicate that file file should be read-only.
      SetAttributeFromString( vEdWrk, szlEditor, "OpenReadOnly", "Y" );
   }

   EDT_CloseObject( vSubtask );
   SetAttributeFromString( vEdWrk, szlBuffer, szlFileName, szFileName );
   EDT_OpenNewObject( vSubtask, szFileName );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_SetInsert( zVIEW vSubtask )
{
   //SysMessageBox( "dgc", "SetInsert", 0 );
   //TraceLineS( "(tzedfrmd)", "SetInsert" );
   MB_SetMessage( vSubtask, INSERTMODE_DIL, "Ins" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_SetOverstrike( zVIEW vSubtask )
{
   //SysMessageBox( "dgc", "SetOver", 0 );
   //TraceLineS( "(tzedfrmd)", "SetOverstrike" );
   MB_SetMessage( vSubtask, INSERTMODE_DIL, "Ovr" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zPrint( zVIEW vSubtask )
{
   EDT_PrintObject( vSubtask );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ActivateBasicsHelp( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, BASICS_MANUAL );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ActivateUsersGuide( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, USERS_GUIDE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ActivateProgrammersRef( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, PROG_REF );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
ActivateOperationsRef( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, OPER_REF );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
OBJ_Prebuild( zVIEW vSubtask )
{
   zSHORT   nRC;
   zVIEW    vOp;
   zVIEW    vSource;

   nRC = GetViewByName( &vOp, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );
   if ( nRC > 0 )
      DropView( vOp );

   RetrieveViewForMetaList( vSubtask, &vOp, zREFER_LOD_META );
   OrderEntityForView( vOp, "W_MetaDef", "Name A" );
   SetNameForView( vOp, "TZEDFRMD_TZCMLPLO_List", vSubtask, zLEVEL_TASK );

   // Make sure that there is no TZOPSRCO.
   nRC = GetViewByName( &vSource, "TZOPSRCO", vSubtask, zLEVEL_TASK );
   if ( vSource )
      DropMetaOI( vSubtask, vSource );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
OBJ_PasteObjectName( zVIEW vSubtask )
{
   zVIEW    vList;
   zVIEW    vTemp;
   zVIEW    vEdWrk;
   zVIEW    vEditorSubtask;
   zPCHAR   szOption;
   zPCHAR   szName;
   CString  zs;

   GetViewByName( &vList, szlTZCMLPLO_List, vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vList, szlW_MetaDef ) != zCURSOR_SET )
      return( 0 );

   // Get the subtask for the editor window.
   GetParentWindow( &vTemp, vSubtask );
   GetParentWindow( &vEditorSubtask, vTemp );
   mGetWorkView( &vEdWrk, vEditorSubtask );

   GetAddrForAttribute( &szOption, vEdWrk, szlBuffer, szlPasteObjectOption );
   GetAddrForAttribute( &szName, vList, szlW_MetaDef, szlName );

   switch ( szOption[0] )
   {
      case 'N':
         zs = szName;
         EDT_InsertItem( vEditorSubtask, zs, TRUE );
         break;

      case 'B':
         zs = "VIEW ";
         zs += szName;
         zs += " BASED ON LOD ";
         zs += szName;
         EDT_InsertItem( vEditorSubtask, zs, TRUE );
         break;

      case 'G':
         zs = "GET VIEW ";
         zs += szName;
         zs += " NAMED \"";
         zs += szName;
         zs += "\"";
         EDT_InsertItem( vEditorSubtask, zs, TRUE );
         break;

      case 'S':
         zs = "NAME VIEW ";
         zs += szName;
         zs += " \"";
         zs += szName;
         zs += "\"";
         EDT_InsertItem( vEditorSubtask, zs, TRUE );
         break;
   }

   DropView( vList );
   return( 0 );
}

//
// Handles a pressed ESC-Key
// There are cases which must be handled
// 1. There is a Modeless Dialog which is owned by the ocx. If so close it
// 2. User wants to deselect current selection
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_Cancel( zVIEW vSubtask )
{
   zSHORT   bSubwindowOpen = EDT_CloseSubWindow( vSubtask );

   if ( bSubwindowOpen == FALSE )
   {
      EDT_Deselect( vSubtask );
   }

   return( 0 );
}

//
// Handles a pressed F1-Key in the operation-insert-dialog
//
zOPER_EXPORT zSHORT OPERATION
OpIns_StartOperationHelp( zVIEW vSubtask )
{

   zVIEW  vEdWrk;
   zCHAR  szOperName[ 40 ];
   zCHAR  szOperTag[ 40 ];
   zCHAR  szOperType[ 5 ];
   zSHORT nRC;

   // Find out what type of operation list is currently displayed.
   mGetWorkView( &vEdWrk,vSubtask );
   GetStringFromAttribute( szOperType, zsizeof( szOperType ), vEdWrk, "OperListType", "Type" );

   // If it's not a zeidon oper list, get out.  No Help is available.
   if ( szOperType[ 0 ] != 'Z' )
   {
      return( 0 );
   }

   // Get the operation tag for the current cursor position.
   GetStringFromAttribute( szOperName, zsizeof( szOperName ), vEdWrk, "Oper", "Name" );
   strcpy_s( szOperTag, zsizeof( szOperTag ), "fn " );
   strcat_s( szOperTag, zsizeof( szOperTag ), szOperName );

   // Call Help
   nRC = StartZeidonHelp( vSubtask, szOperTag );

   // If help was not found, notify the user.
   if ( nRC == zCALL_ERROR )
   {
      MB_SetMessage( vSubtask, 0, "Help for this operation is not currently available." );
   }

   return( 0 );
}

// Handles a pressed Ctrl+F3 in the Editor.
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_SearchSelectedText( zVIEW vSubtask )
{
#if 0
   CString  csMsg;
   CString  csMsgFormat = "Could not find requested string\"%s\"!";
   CString  csStringToFind = "";
   zLONG    lStartLine = 0, lStartCol = 0, lEndLine = 0, lEndCol = 0, lLine = 0, lCol = 0;
   zLONG    lSearchBehavior = lDirectionFlag;

   EDT_GetCursorPosition( vSubtask, &lLine, &lCol );

   zLONG lCharCount = g_csFindWhat.GetLength( );
   csStringToFind = g_csFindWhat;

   if ( g_fr.Flags & FR_WHOLEWORD )
   {
      csStringToFind = "\\b";
      CString csUpper = g_csFindWhat;
      CString csLower = g_csFindWhat;
      csUpper.MakeUpper( );
      csLower.MakeLower( );
      for( int k = 0; k < csUpper.GetLength( ); k++ )
      {
         csStringToFind += "[";
         csStringToFind += csUpper[ k ];
         csStringToFind += csLower[ k ];
         csStringToFind += "]";
      }

      csStringToFind += "[^a-zA-Z_0-9]";
      if ( EDT_CanCopy( vSubtask ) )
      {
         CString csHelp;
         LPSTR pchBuffer = csHelp.GetBufferSetLength( lCharCount );
         EDT_GetTextFromRange( vSubtask, pchBuffer, lCharCount, lStartLine, lStartCol, lEndLine, lEndCol );
         csHelp.ReleaseBuffer( );
         if ( csHelp.CompareNoCase( g_csFindWhat ) == 0 && g_fr.Flags & FR_DOWN )
         {
            lStartLine += lCharCount;
            EDT_SetCursorPositionByLineCol( vSubtask, lStartLine, lStartCol );
         }
      }
   }

   if ( g_fr.Flags & FR_MATCHCASE )
   {
      lSearchBehavior |= FIND_MATCH_CASE;
      g_bMatchCase = TRUE;
   // csStringToFind = "\\b";
      csStringToFind = g_csFindWhat;
   // csStringToFind += "[^a-zA-Z_0-9]";
   }

   EDT_FindTextPosition( vSubtask, csStringToFind, &lStartLine, &lStartCol, lSearchBehavior );
   if ( lStartLine > -1 )
   {
      EDT_SelectRange( vSubtask, lStartLine, lStartCol, g_csFindWhat.GetLength( ) );
   }
   else
   {
      csMsg.Format( csMsgFormat, g_csFindWhat );
      MB_SetMessage( vSubtask, MAIN_DIL, csMsg );
   }
#endif
   zSHORT nRC = EDT_SearchSelectedText( vSubtask );
   CString csLast = EDT_GetLastFindString( vSubtask );
   CString csMsg;
   if ( nRC == 0 )
   {
      csMsg = "Selected text NOT found: ";
   }
   else
   if ( nRC < 0 )
   {
      csMsg = "Found past the end of the document: ";
   }
   else
   {
      csMsg = "Selected text found: ";
   }
   csMsg += csLast;
   MB_SetMessage( vSubtask, MAIN_DIL, csMsg );
   return nRC;
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: TZEDFRMD_GotoOperation
//
// Searches current source file for the operation that is referenced by
// cursor position (Cursor in this case means the indicator within the editor).
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_GotoOperation( zVIEW vSubtask )
{
   zLONG    lLine = 0, lCol = 0;
   zLONG    lReturnedBuffSize = MAX_TOKEN_LTH;
   CString  csBuffer;
   CString  csOperSrch = "\\bOPERATION[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+%s[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]*(";
   DWORD    dwTBEDTDefaultSearchBehavior = FIND_MATCH_CASE | FIND_WHOLE_WORD;
   LPSTR    szBuffer = NULL;
   CString  csDelimiter = "\t,)( ";

   // This isn't working correctly at the moment, so we will return doing nothing.
   return(0);

   EDT_GetCursorPosition( vSubtask, &lLine, &lCol );

   // return if we are within a comment
   if ( fnIsCommentAtIndex( vSubtask, lLine, lCol ) )
   {
      return( 0 );
   }

   szBuffer = csBuffer.GetBufferSetLength( lReturnedBuffSize );
   lReturnedBuffSize = EDT_GetTextFromLineOfIndex( vSubtask, szBuffer, lReturnedBuffSize, lLine );

   // In Case of an editor error (e.g. Buffer to small), retry with new buffersize.
   if ( lReturnedBuffSize >= MAX_TOKEN_LTH )
   {
      lReturnedBuffSize++;
      szBuffer = csBuffer.GetBufferSetLength( lReturnedBuffSize );
      lReturnedBuffSize = EDT_GetTextFromLineOfIndex( vSubtask, szBuffer, lReturnedBuffSize, lLine );
   }

   csBuffer.ReleaseBuffer( );
   zLONG lBufferLth = csBuffer.GetLength( );
   if ( lBufferLth == 0 )
   {
      return( 0 );
   }

   // If positioned on a whitespace go to the next token.
   TCHAR c = 0;

   if ( lCol < lBufferLth )
   {
      for ( c = csBuffer.GetAt( lCol );
            isspace( c ) && lCol < lBufferLth;
            lCol++ )
      {
         c = csBuffer.GetAt( lCol );
      }
   }

   // Now extract the operation name from current column going back and
   // forth to detect the token that seems to be an operation name.
   zLONG lTokenStart    =  0;
   zLONG lTokenEnd      =  0;
   zLONG lCurrentColumn = lCol;

   // Get beginning of operation name.
   while ( lTokenStart == 0 &&
           lCurrentColumn >= 0 &&        // iterate only between lower
           lCurrentColumn < lBufferLth ) // and upper bounds
   {
      c = csBuffer.GetAt(lCurrentColumn);
      if ( !__iscsym( c )) // Alphanumeric + digits + underscore
      {
         lTokenStart = lCurrentColumn + 1;
      }
      else
      {
         lCurrentColumn--;
      }
   }

   // Get the end of the operation name.
   lCurrentColumn = lCol;
   while ( lTokenEnd == 0 &&
           lCurrentColumn >= 0  &&                   // iterate only between lower
           lCurrentColumn < csBuffer.GetLength( ) ) // and upper bounds
   {
      c = csBuffer.GetAt( lCurrentColumn );
      if ( !__iscsym( c ) )  // alphanumeric + digits + underscore
      {
         lTokenEnd = lCurrentColumn;
      }
      else
      {
         lCurrentColumn++;
      }
   }

   if ( lTokenEnd == 0 )
      lTokenEnd = csBuffer.GetLength( );

   // Extract OperationName.
   csBuffer = csBuffer.Mid( lTokenStart, (lTokenEnd - lTokenStart) );

   if ( csBuffer.GetLength( ) == 0 )
      return( 0 );

   CString csSearchString;
   csSearchString.Format( csOperSrch, csBuffer );

   lLine = 0; // search from begin of file
   lCol = 0;

   // KJS 11/14/16 - The problem we are having is finding the string using csOperSrch. Wondering if maybe we should look for OPERATION, then look for ")" which would be
   // the close of the operation and search that???? Or maybe I should be looking for "Operation" then look if the operation name is on the same line or the next line
   // that isn't blank.
   //EDT_FindTextPosition(vSubtask, csSearchString, &lLine, &lCol, dwTBEDTDefaultSearchBehavior);
   EDT_FindTextPosition(vSubtask, "Operation", &lLine, &lCol, dwTBEDTDefaultSearchBehavior);

   // Skipping lines where the search text is part of a comment
   while ( fnIsCommentAtIndex( vSubtask, lLine, lCol ) && lLine > -1 )
   {
      lLine++;
     EDT_FindTextPosition(vSubtask, "Operation", &lLine, &lCol, dwTBEDTDefaultSearchBehavior);
     //EDT_FindTextPosition(vSubtask, csSearchString, &lLine, &lCol, dwTBEDTDefaultSearchBehavior);
   }

   if ( lLine >= 0 ) // we found something so place the cursor onto it
   {
      EDT_SetCursorPositionByLineCol( vSubtask, lLine + 12, 0 );
      return( 1 );
   }
   else
   {
      csSearchString.Format( "Operation \'%s\' could not be located", csBuffer );
      MB_SetMessage( vSubtask, MAIN_DIL, csSearchString );
   }

   return( 0 );

} // TZEDFRMD_GotoOperation


/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditFind
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_PageUp( zVIEW vSubtask )
{
   /*
   zLONG    lLine = 0, lCol = 0;

   EDT_GetCursorPosition(vSubtask, &lLine, &lCol);

   if (lLine >= 25) // we found something so place the cursor onto it
   {
      EDT_SetCursorPositionByLineCol(vSubtask, lLine - 25, lCol);
      return(1);
   }
   */
   return EDT_PageUp( vSubtask );

} // TZEDFRMD_PageUp

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_PageDown
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_PageDown( zVIEW vSubtask )
{
   return EDT_PageDown( vSubtask );
   //return(0);

}

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditCut
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditCut( zVIEW vSubtask )
{
   if ( EDT_CanCopy( vSubtask ) )
      EDT_CutText( vSubtask );

   return( 0 );

}// TZEDFRMD_EditCut

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditPaste
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditPaste( zVIEW vSubtask )
{
   if ( EDT_CanPaste( vSubtask ) )
      EDT_PasteText( vSubtask );

   return( 0 );

}// TZEDFRMD_EditPaste

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditTab
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditTab( zVIEW vSubtask )
{
   EDT_TabText( vSubtask );

   return( 0 );

}// TZEDFRMD_EditTab

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditUntab
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditUntab( zVIEW vSubtask )
{
   EDT_UntabText( vSubtask );

   return( 0 );

}// TZEDFRMD_EditUntab

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditCopy
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditCopy( zVIEW vSubtask )
{
   if ( EDT_CanCopy( vSubtask ) )
      EDT_CopyText( vSubtask );

   return( 0 );

} // TZEDFRMD_EditCopy

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditSelectAll
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditSelectAll( zVIEW vSubtask )
{
   EDT_SelectAll( vSubtask );

   return( 0 );

} // TZEDFRMD_EditSelectAll

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditDelete
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditDelete( zVIEW vSubtask )
{
   if ( EDT_CanCopy( vSubtask ) )
      EDT_DeleteText( vSubtask );

   return( 0 );

} // TZEDFRMD_EditDelete

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditUndo
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditUndo( zVIEW vSubtask )
{
   if ( EDT_CanUndo( vSubtask ) )
      EDT_Undo( vSubtask );

   return( 0 );

} // TZEDFRMD_EditUndo

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditRedo
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditRedo( zVIEW vSubtask )
{
   if ( EDT_CanRedo( vSubtask ) )
      EDT_Redo( vSubtask );

   return( 0 );

} // TZEDFRMD_EditRedo

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditFind
//
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditFind( zVIEW vSubtask )
{
   /*
   zPCHAR   pch = 0;
   CString  strBuffer;
   zLONG    lBufferLth = 512;
   ZDrTBEdt *oEditor =
      (ZDrTBEdt *)GetActiveX_WrapperInstance(vSubtask, EDIT_CONTROL_NAME);

   if (oEditor)
   {
      if (oEditor->CanCopy()) // something is selected
      {
         pch = strBuffer.GetBufferSetLength(lBufferLth);
         zLONG lReturn = oEditor->GetSelectedText(pch, lBufferLth);
         while (lReturn > lBufferLth)
         {
            lBufferLth = lReturn + 1;
            lReturn = oEditor->GetSelectedText(pch, lBufferLth);
         }
      }
   }
   else
   {
      return(-1);
   }

   if (pch == 0)
      pch = g_strFindWhat.GetBufferSetLength(g_strFindWhat.GetLength());
   */
   return EDT_FindDialog( vSubtask );

} // TZEDFRMD_EditFind

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_RepeatFind
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditRepeatFind( zVIEW vSubtask )
{
   zSHORT nRC = EDT_RepeatFind( vSubtask );
   CString csLast = EDT_GetLastFindString( vSubtask );
   CString csMsg;
   if (nRC == 0)
   {
      csMsg = "Requested text NOT found: ";
   }
   else
   if (nRC < 0)
   {
      csMsg = "Found past the end of the document: ";
   }
   else
   {
      csMsg = "Requested text found: ";
   }
   csMsg += csLast;
   MB_SetMessage( vSubtask, MAIN_DIL, csMsg );
   return nRC;
}

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_FindPrevious
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditFindPrevious( zVIEW vSubtask )
{
   zSHORT nRC = EDT_FindPrevious( vSubtask );
   CString csLast = EDT_GetLastFindString( vSubtask );
   CString csMsg;
   if (nRC == 0)
   {
      csMsg = "Requested text NOT found: ";
   }
   else
   if (nRC < 0)
   {
      csMsg = "Found past the end of the document: ";
   }
   else
   {
      csMsg = "Requested text found: ";
   }
   csMsg += csLast;
   MB_SetMessage( vSubtask, MAIN_DIL, csMsg );
   return nRC;
}

#if 0
/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_OnEditFind
//
//  Handles the edit find event
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_OnEditFind( zVIEW vSubtask )
{
   CString  csMsg, csMsgFormat = "Could not find requested string\"%s\"!";
   zLONG    lSearchBehavior = 0, lPosition = 0;
   zLONG    lCharCount = 0;
   zLONG    lStartLine = 0, lStartCol = 0, lEndLine = 0, lEndCol = 0;
   FINDREPLACE *pfr = (FINDREPLACE *) GetActionParameters( vSubtask );

   memcpy( &g_fr, pfr, zsizeof( FINDREPLACE ) );
   EDT_GetCursorPosition( vSubtask, &lStartLine, &lStartCol );

   if ( zstrlen( pfr->lpstrFindWhat ) == 0 )
      return( 0 );

   // store search string for F3 / Shift+F3 use
   g_csFindWhat = pfr->lpstrFindWhat;
   lCharCount = g_csFindWhat.GetLength( );
   CString csStringToFind = g_csFindWhat;

   // Check if currently selected text already matches search text. If so,
   // set cursor to the end of the selected text but only in FR_DOWN mode.
   if ( pfr->Flags & FR_WHOLEWORD )
   {
      lSearchBehavior = 0;
      csStringToFind = "\\b";
      CString csUpper = g_csFindWhat;
      CString csLower = g_csFindWhat;
      csUpper.MakeUpper( );
      csLower.MakeLower( );
      for( int k = 0; k < csUpper.GetLength( ); k++ )
      {
         csStringToFind += "[";
         csStringToFind += csUpper[ k ];
         csStringToFind += csLower[ k ];
         csStringToFind += "]";
      }

      csStringToFind += "[^a-zA-Z_0-9]";
      if ( EDT_CanCopy( vSubtask ) )
      {
         CString csHelp;
         LPSTR pchBuffer = csHelp.GetBufferSetLength( lCharCount );
         EDT_GetTextFromRange( vSubtask, pchBuffer, lCharCount, lStartLine, lStartCol, lEndLine, lEndCol );
         csHelp.ReleaseBuffer( );
         if ( csHelp.CompareNoCase( g_csFindWhat ) == 0 && pfr->Flags & FR_DOWN )
         {
            lPosition += lCharCount;
            EDT_SetCursorPositionByLineCol( vSubtask, lPosition, 0 );
         }
      }
   }

   if ( pfr->Flags & FR_MATCHCASE )
   {
      lSearchBehavior |= FIND_MATCH_CASE;
      g_bMatchCase = TRUE;
   // csStringToFind = "\\b";
      csStringToFind = g_csFindWhat;
   // csStringToFind += "[^a-zA-Z_0-9]";
   }

   if ( pfr->Flags & FR_DOWN )
      lSearchBehavior |= FIND_FORWARD;

   EDT_FindTextPosition( vSubtask, csStringToFind, &lStartLine, &lStartCol, lSearchBehavior );
   if ( lPosition > -1 )
   {
      EDT_SelectRange( vSubtask, lPosition, 0, lCharCount );
   }
   else
   {
      csMsg.Format( csMsgFormat, pfr->lpstrFindWhat );
      MB_SetMessage( vSubtask, MAIN_DIL, csMsg );
   }

   return( 0 );

} // TZEDFRMD_OnEditFind

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_OnEditFindNext
//
//  handles the EditFindNext event
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_OnEditFindNext( zVIEW vSubtask )
{
   TZEDFRMD_OnEditFind( vSubtask );
   return( 0 );

} // TZEDFRMD_OnEditFindNext
#endif

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditReplace
//
//  Repeat Replace
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_EditReplace( zVIEW vSubtask )
{
   return EDT_ReplaceDialog( vSubtask );

} // TZEDFRMD_EditReplace

#if 0
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_EditReplace( zVIEW vSubtask )
{
   return( OperatorPromptFindReplace( vSubtask, "","", TRUE ) );
}
#endif

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: OptionSettings
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
OptionSettings( zVIEW vSubtask )
{
   EDT_PropertyDialog( vSubtask );

   return( 0 );

} // OptionSettings

zOPER_EXPORT zSHORT OPERATION
GotoWindow( zVIEW vSubtask )
{
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME );

   if ( pzma )
      pzma->ResetFocus( );

   return( 0 );

} // GotoWindow

static zBOOL
GetOperationPosition( zVIEW   vSubtask,
                      ZMapAct *pzma,
                      zVIEW   vDeleteOp,
                      zPLONG  plOpStartIndex,
                      zPLONG  plOpEndIndex )
{
   zCHAR      szOperName[ 33 ];
   zBOOL      bReturn = FALSE;

   *plOpStartIndex  = -1;
   *plOpEndIndex    = -1;

   GetStringFromAttribute( szOperName, zsizeof( szOperName ), vDeleteOp, "Operation", "Name" );

   // 1. find begin and end for the requestet operation
   *plOpStartIndex = FindBeginOfOperation( vSubtask, szOperName, pzma );

   if ( *plOpStartIndex >= 0 )
      *plOpEndIndex = FindEndOfOperation( vSubtask, szOperName, pzma );

   // 2. delete code within the range of plOpStartIndex and plOpEndIndex
   if ( *plOpStartIndex >= 0 && *plOpEndIndex >= 0 && *plOpStartIndex < *plOpEndIndex )
      bReturn = TRUE;

   return( bReturn );
}

static zSHORT
GetPositionForNextInsert( zVIEW   vSubtask,
                          zPLONG  plLine,
                          zPLONG  plCol )
{
   zLONG lLine  = -1;
   zLONG lCol   = -1;

   // set cursor to the last line
   lLine = EDT_GetLineCount( vSubtask ) - 1;
   EDT_SetCursorPositionByLineCol( vSubtask, lLine, 0 );

   // in c-files search for #ifdef __cplusplus (from end to begin)
   static zCHAR szSearchString[] = "\\bifdef[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+__cplusplus[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]+";

   EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
   EDT_FindTextPosition( vSubtask, szSearchString, &lLine, &lCol, FIND_DIRECTION_UP );
   lLine--;

   if ( lLine > -1 )
   {
      zLONG  lLine_1 = 0;
      zLONG  lCol_1 = 0;
      zLONG  lLine_2 = 0;
      zLONG  lCol_2 = 0;

      //set cursor to #ifdef __cplusplus
      EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );

      // search for } ( from #ifdef __cplusplus to end )
      static zCHAR szSearchString_1[] = "} *";
      EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
      EDT_FindTextPosition( vSubtask, szSearchString_1, &lLine_1, &lCol_1, FIND_FORWARD );

      if ( lLine_1 >= 0 && lLine_1 > lLine )
      {
         //set cursor to #ifdef __cplusplus
         EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );

         // search for #endif (from #ifdef __cplusplus to end)
         static zCHAR szSearchString_2[] = "\\bendif[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]*";

         EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
         EDT_FindTextPosition( vSubtask, szSearchString_2, &lLine_2, &lCol_2, FIND_FORWARD );
         if ( lLine_2 < 0 || lLine_2 <= lLine_1 )
            lLine =  1048576; // end of file
      }
      else
      {
         lLine =  1048576; // end of file
      }
   }
   else
   {
      lLine =  1048576; // end of file
   }

   *plLine = lLine;
   *plCol = lCol;
   return( 0 );
}

static zLONG
CopyOperationToNewFile( zVIEW    vSubtask,
                        zVIEW    vEdWrk,
                        zPCHAR   pchBuffer )
{
   zLONG    lReturnedBuffSize = -1;
   zLONG    lLine, lCol;
   CString  csBuffer;
   zPCHAR   szBuffer = NULL;

   // if source file is of type "C"
   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlLanguageType, szlC_File ) == 0 )
   {
      // in c-files search for #ifdef __cplusplus (from end to begin)
      GetPositionForNextInsert( vSubtask, &lLine, &lCol );
      EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );
   }
   else
   {
      // set cursor to the last line
      lLine = EDT_GetLineCount( vSubtask ) - 1;
      EDT_SetCursorPositionByLineCol( vSubtask, lLine, 0 );
      EDT_GetCursorPosition( vSubtask, &lLine, &lCol );
      szBuffer = csBuffer.GetBufferSetLength( 64004 );   // 255
      lReturnedBuffSize = EDT_GetTextFromLineOfIndex( vSubtask, szBuffer, 64000, lLine );
      EDT_SetCursorPositionByLineCol( vSubtask, lLine, lReturnedBuffSize );
   }

   EDT_GetCursorPosition( vSubtask, &lLine, &lCol );

   // insert Operation
   BufInsertStr( vSubtask, "\r\n\r\n" );
   BufInsertStr( vSubtask, pchBuffer );

   EDT_SaveFile( vSubtask );
   return( lLine );
}

zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_MoveOperationCode( zVIEW  vSubtask,
                            zSHORT nCopyOrMoveFlag )
{
   zPCHAR   pchBuffer = NULL;
   CString  csBuffer;
   zCHAR    szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR    szSourceFileName[ zMAX_FILENAME_LTH + 1 ];
   zVIEW    vEdWrk  = 0;
   zVIEW    vSource = 0;
   zVIEW    vProfileXFER  = 0;
   zVIEW    vDeleteOp     = 0;
   zLONG    lStartLine = -1;
   zLONG    lStartCol  = -1;
   zLONG    lEndLine   = -1;
   zLONG    lEndCol    = -1;
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME );

   if ( InitEditorForMoveAndDelete( pzma, vSubtask, &vDeleteOp, &vSource,
                                    &vEdWrk, &vProfileXFER, szFileName, zsizeof( szFileName ) ) < 0 )
   {
      return( -1 );
   }

   // copy Operation Code from 1. Source File
   if ( SetCursorFirstEntity( vDeleteOp, "SourceFile", "" ) < zCURSOR_SET ||
        OpenFileForMoveAndDelete( pzma, vDeleteOp, vEdWrk, vSource, vProfileXFER,
                                  szFileName, szSourceFileName, FALSE ) < 0 )
   {
      DropViewsForMoveAndDelete( vSubtask, vDeleteOp, vEdWrk );
      return( -1 );
   }

   if ( SetCursorFirstEntity( vDeleteOp, "Operation", "" ) >= zCURSOR_SET )
   {
      if ( GetOperationPosition( vSubtask, pzma, vDeleteOp, &lStartLine, &lEndLine ) == TRUE )
      {
         // get Operation Code
         pchBuffer = csBuffer.GetBufferSetLength( lEndLine - lStartLine + 1 );
      // EDT_GetTextFromRange( vSubtask, pchBuffer, lStartLine, lEndLine );
         EDT_GetTextFromRange( vSubtask, pchBuffer, lEndLine - lStartLine + 1, lStartLine, lStartCol, lEndLine, lEndCol );

         if ( *pchBuffer )
         {
            // paste Operation Code to 2. Source File
            if ( SetCursorNextEntity( vDeleteOp, "SourceFile", "" ) < zCURSOR_SET ||
                 OpenFileForMoveAndDelete( pzma, vDeleteOp, vEdWrk, vSource,
                                           vProfileXFER, szFileName,
                                           szSourceFileName, TRUE ) < 0 )
            {
               DropViewsForMoveAndDelete( vSubtask, vDeleteOp, vEdWrk );
               return( -1 );
            }

            // set cursor to last line and insert operation
            CopyOperationToNewFile( vSubtask, vEdWrk, pchBuffer );
            DeleteEntity( vEdWrk, "Buffer", zREPOS_NEXT );

            if ( nCopyOrMoveFlag == zMOVE_OPERATION )
            {
               // Drop 2. Source File from Delete LOD (do not delete in this file)
               DeleteEntity( vDeleteOp, "SourceFile", zREPOS_PREV );

               // Drop Operation Code from 1. Source File
               DeleteOperationFromCurrentFile( vSubtask, vSource, vDeleteOp, vEdWrk,
                                               vProfileXFER, pzma, szFileName );
            }
         } // endif ( *pchBuffer )
      } // endif ( GetOperationPosition( vSubtask, pzma, vDeleteOp, ...
   } // endif ( SetCursorFirstEntity( vDeleteOp, "Operation", "" ) >= zCURSOR_SET )

   DeleteEntity( vEdWrk, "Buffer", zREPOS_NEXT );
   DropViewsForMoveAndDelete( vSubtask, vDeleteOp, vEdWrk );
   return( 0 );
}

static zSHORT
RenameOperation( ZMapAct  *pzma,
                 zVIEW    vSubtask,
                 zLONG    lPosition )
{
   zVIEW   vDeleteOp;
   zCHAR   szSearchText[ 256 ];
   zCHAR   szReplaceText[ 33 ];
   zCHAR   szOperation[ 33 ];
   zLONG   lLine = lPosition;
   zLONG   lCol = 0;

   GetViewByName( &vDeleteOp, "DeleteOp", vSubtask, zLEVEL_TASK );

   SetCursorFirstEntity( vDeleteOp, "SourceFile", "" );
   SetCursorFirstEntity( vDeleteOp, "Operation", "" );
   GetStringFromAttribute( szOperation, zsizeof( szOperation ), vDeleteOp, "Operation", "Name" );

   SetCursorNextEntity( vDeleteOp, "SourceFile", "" );
   if ( SetCursorFirstEntity( vDeleteOp, "Operation", "" ) < zCURSOR_SET )
      return( 0 );

   GetStringFromAttribute( szReplaceText, zsizeof( szReplaceText ), vDeleteOp, "Operation", "Name" );

   // replace Operation name in comments
   sprintf_s( szSearchText, zsizeof( szSearchText ), "\\b%s\\W", szOperation );
   EDT_SetCursorPositionByLineCol( vSubtask, lPosition, lCol );
   EDT_FindTextPosition( vSubtask, szSearchText, &lLine, &lCol, FIND_FORWARD );
   while ( lPosition > -1 )
   {
      if ( fnCursorInCommentOrQuote( vSubtask, lPosition, lCol ) == 1 )
      {
         EDT_SelectRange( vSubtask, lPosition, 0, zstrlen( szOperation ) );
         if ( EDT_CanCopy( vSubtask ) ) // is something selected?
            EDT_InsertItem( vSubtask, szReplaceText, FALSE );
      }
      lPosition++;
      EDT_FindTextPosition( vSubtask, szSearchText, &lLine, &lCol, FIND_FORWARD );
   }

   // replace Operation name
   sprintf_s( szSearchText, zsizeof( szSearchText ), "\\b%s[^!-~∞ß≤≥¥ﬂ‰ˆ¸ƒ÷‹]*(", szOperation );
   EDT_SetCursorPositionByLineCol( vSubtask, lLine, lCol );
   EDT_FindTextPosition( vSubtask, szSearchText, &lLine, &lCol, FIND_FORWARD );
   while ( lLine > -1 )
   {
      EDT_SelectRange( vSubtask, lLine, 0, zstrlen( szOperation ) );
      if ( EDT_CanCopy( vSubtask ) ) // is something selected?
         EDT_InsertItem( vSubtask, szReplaceText, FALSE );

      EDT_FindTextPosition( vSubtask, szSearchText, &lLine, &lCol, FIND_FORWARD );
   }

   EDT_SaveFile( vSubtask );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_CopyOperationCode
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
TZEDFRMD_CopyOperationCode( zVIEW vSubtask,
                            zSHORT nRenameOperation )
{
   zPCHAR   pchBuffer = NULL;
   CString  csBuffer;
   zCHAR    szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR    szSourceFileName[ zMAX_FILENAME_LTH + 1 ];
   zVIEW    vEdWrk  = 0;
   zVIEW    vSource = 0;
   zVIEW    vProfileXFER  = 0;
   zVIEW    vDeleteOp     = 0;
   zLONG    lStartLine = -1;
   zLONG    lStartCol  = -1;
   zLONG    lEndLine   = -1;
   zLONG    lEndCol    = -1;
   ZSubtask *pZSubtask;
   ZMapAct  *pzma;
   GetWindowAndCtrl( &pZSubtask, &pzma, vSubtask, EDIT_CONTROL_NAME );

   if ( InitEditorForMoveAndDelete( pzma, vSubtask, &vDeleteOp, &vSource,
                                    &vEdWrk, &vProfileXFER, szFileName, zsizeof( szFileName ) ) < 0 )
   {
      return( -1 );
   }

   // copy Operation Code from 1. Source File
   if ( SetCursorFirstEntity( vDeleteOp, "SourceFile", "" ) < zCURSOR_SET ||
        OpenFileForMoveAndDelete( pzma, vDeleteOp, vEdWrk, vSource, vProfileXFER,
                                  szFileName, szSourceFileName, FALSE ) < 0 )
   {
      DropViewsForMoveAndDelete( vSubtask, vDeleteOp, vEdWrk );
      return( -1 );
   }

   if ( SetCursorFirstEntity( vDeleteOp, "Operation", "" ) >= zCURSOR_SET )
   {
      if ( GetOperationPosition( vSubtask, pzma, vDeleteOp, &lStartLine, &lEndLine ) == TRUE )
      {
         // get Operation Code
         pchBuffer = csBuffer.GetBufferSetLength( lEndLine - lStartLine + 1 );
      // EDT_GetTextFromRange( vSubtask, pchBuffer, lStartLine, lEndLine );
         EDT_GetTextFromRange( vSubtask, pchBuffer, lEndLine - lStartLine + 1, lStartLine, lStartCol, lEndLine, lEndCol );

         if ( *pchBuffer )
         {
            // paste Operation Code to 2. Source File
            if ( SetCursorNextEntity( vDeleteOp, "SourceFile", "" ) < zCURSOR_SET ||
                 OpenFileForMoveAndDelete( pzma, vDeleteOp, vEdWrk, vSource,
                                           vProfileXFER, szFileName, szSourceFileName, TRUE ) < 0 )
            {
               DropViewsForMoveAndDelete( vSubtask, vDeleteOp, vEdWrk );
               return( -1 );
            }

            // set cursor to last line and insert operation
            lStartLine = CopyOperationToNewFile( vSubtask, vEdWrk, pchBuffer );

            // Rename Operation
            if ( nRenameOperation == zRENAME_OPERATION )
               RenameOperation( pzma, vSubtask, lStartLine );

            DeleteEntity( vEdWrk, "Buffer", zREPOS_NEXT );

         } // endif ( *pchBuffer )
      } // endif ( GetOperationPosition( vSubtask, pzma, vDeleteOp, ...
   } // endif ( SetCursorFirstEntity( vDeleteOp, "Operation", "" ) >= zCURSOR_SET )

   DeleteEntity( vEdWrk, "Buffer", zREPOS_NEXT );
   DropViewsForMoveAndDelete( vSubtask, vDeleteOp, vEdWrk );
   return( 0 );

} // TZEDFRMD_CopyOperationCode

static zSHORT
InitEditorForMoveAndDelete( ZMapAct *pzma,
                            zVIEW   vSubtask,
                            zPVIEW  pvDeleteOp,
                            zPVIEW  pvSource,
                            zPVIEW  pvEdWrk,
                            zPVIEW  pvProfileXFER,
                            zPCHAR  pchFileName,
                            zLONG   lMaxLth )
{
   zVIEW      vTaskLPLR;
   zCHAR      szInvokingTool[ 33 ];
   zCHAR      szSourceFileEntityName[ 33 ];

   // registry problem. Don't know if this is the best way to do that but it's better than an access-violation
   if ( pzma == 0 )
      return( -1 );

   if ( GetViewByName( pvDeleteOp, "DeleteOp", vSubtask, zLEVEL_TASK ) < 0 ||
        GetViewByName( pvSource, "METAOPERATIONS", vSubtask, zLEVEL_TASK ) < 0 )
   {
      return( -1 );
   }

   mGetWorkView( pvEdWrk, vSubtask );
   mGetProfileView( pvProfileXFER, vSubtask );

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szInvokingTool, zsizeof( szInvokingTool ), *pvProfileXFER, szlED, "InvokingTool" );

   // Clean up a little by dropping the name.
   DropNameForView( *pvSource, "METAOPERATIONS", vSubtask, zLEVEL_TASK );

   // Create the name of the file.
   if ( zstrcmp( szInvokingTool, "GO" ) == 0 )
      strcpy_s( szSourceFileEntityName, zsizeof( szSourceFileEntityName ), "GlobalOperationGroup" );
   else
      if ( zstrcmp( szInvokingTool, "DM" ) == 0 )
         strcpy_s( szSourceFileEntityName, zsizeof( szSourceFileEntityName ), "DomainGroup" );
      else
         strcpy_s( szSourceFileEntityName, zsizeof( szSourceFileEntityName ), szlSourceFile );

   // Get the source dir from the lplr view.
   GetStringFromAttribute( pchFileName, lMaxLth, vTaskLPLR, szlLPLR, szlPgmSrcDir );
   SysAppendcDirSep( pchFileName );

   return( 0 );
}

static zSHORT
OpenFileForMoveAndDelete( ZMapAct  *pzma,
                          zVIEW    vDeleteOp,
                          zVIEW    vEdWrk,
                          zVIEW    vSource,
                          zVIEW    vProfileXFER,
                          zPCHAR   pchFileName,
                          zPCHAR   pchSourceFileName,
                          zBOOL    bCreateFile )
{
   zCHAR  szName[33];
   zLONG  hFile;
   zBOOL  bCreateFileInfo = FALSE;

   strcpy_s( pchSourceFileName, zMAX_FILENAME_LTH + 1, pchFileName );

   // Get the subdir from the source file entity.  If GetString... returns < 0
   // then the subdir attribute is null, so nothing was retrieved.  If subdir
   // is set, then we need to add a '\'.
   if ( GetStringFromAttribute( pchSourceFileName + zstrlen( pchSourceFileName ), zMAX_FILENAME_LTH + 1 - zstrlen( pchSourceFileName ),
                                vDeleteOp, "SourceFile", "Subdirectory" ) >= 0 )
   {
      SysAppendcDirSep( pchSourceFileName );
   }

   // Get the file name and extension.
   GetStringFromAttribute( pchSourceFileName + zstrlen( pchSourceFileName ),
                           zMAX_FILENAME_LTH + 1 - zstrlen( pchSourceFileName ),
                           vDeleteOp, "SourceFile", "Name" );
   strcat_s( pchSourceFileName, zMAX_FILENAME_LTH + 1, "." );
   GetStringFromAttribute( pchSourceFileName + zstrlen( pchSourceFileName ),
                           zMAX_FILENAME_LTH + 1 - zstrlen( pchSourceFileName ),
                           vDeleteOp, "SourceFile", "Extension" );

   if ( SysOpenFile( vDeleteOp, pchSourceFileName, COREFILE_EXIST ) == -1 )
   {
      if ( !bCreateFile )
         return( -1 );
      else
      {
         // Create an empty file.
         hFile = SysOpenFile( vDeleteOp, pchSourceFileName, COREFILE_CREATE );
         SysCloseFile( vDeleteOp, hFile, 0 );
         bCreateFileInfo = TRUE;
      }
   } //endif ( SysOpenFile( vDeleteOp, pchSourceFileName, COREFILE_EXIST ) == -1 )

   EDT_OpenObject( pzma->m_pZSubtask->m_vDialog, pchSourceFileName );

   CreateEntity( vEdWrk, szlBuffer, zPOS_LAST );
   SetAttributeFromString( vEdWrk, szlBuffer, szlFileName, pchSourceFileName );
   SetMatchingAttributesByName( vEdWrk, szlBuffer, vProfileXFER, "ED", zSET_ALL );
   SetAttributeFromInteger( vEdWrk, szlBuffer, szlSourceViewID, (zLONG) vSource );

   // Set the LanguageType for the current buffer.
   SetAttributeFromAttribute( vEdWrk, szlBuffer, szlLanguageType, vDeleteOp, "SourceFile", "LanguageType" );

   // if a new C File ?
   if ( bCreateFileInfo &&
        CompareAttributeToString( vDeleteOp, "SourceFile", "LanguageType", szlC_File ) == 0 )
   {
      GetStringFromAttribute( szName, zsizeof( szName ), vDeleteOp, "SourceFile", "Name" );
      CreateFileInfo( pzma->m_pZSubtask->m_vDialog, szName );
   }

   return( 0 );
}

static zSHORT
DropViewsForMoveAndDelete( zVIEW vSubtask,
                           zVIEW vDeleteOp,
                           zVIEW vEdWrk )
{
   DropView( vDeleteOp );
   DropView( vEdWrk );

   GetViewByName( &vEdWrk, szlTZEDWRKO, vSubtask, zLEVEL_TASK );

   if ( vEdWrk )
      DropView( vEdWrk );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_DisableActions
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_DisableActions( zVIEW vSubtask )
{
   zBOOL  bReadOnly = TRUE;
   zVIEW  vEdWrk;
   zVIEW  vWindow;

   GetParentWindow( &vWindow, vSubtask );
   if ( vWindow )
   {
      mGetWorkView( &vEdWrk, vWindow );

      if ( SetCursorFirstSelectedEntity( vEdWrk, "Oper", 0 ) < zCURSOR_SET ||
           CompareAttributeToString( vEdWrk, szlBuffer, szlReadOnly, "Y" ) == 0 ||
           CompareAttributeToString( vEdWrk, szlBuffer, szlActiveStatus, "N" ) == 0 )
      {
         bReadOnly = FALSE;
      }
   }

   EnableAction( vSubtask, "InsertOperation", bReadOnly );

   return( 0 );

} // TZEDFRMD_DisableActions

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_CreateContextMenue
//
//  Creates a Context menu for Editor
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_CreateContextMenue( zVIEW vSubtask )
{
// POINT  pt;
   CPoint pt( GetMessagePos( ) );
// pt.x = pt.y = -1;
   TZEDFRMD_EnableEditMenuActions( vSubtask );

   CreateTrackingPopupMenu( vSubtask, TZEDFRMD_EDIT_CONTEXT_MENU_TAG, pt.x, pt.y, FALSE, FALSE );

   return( 0 );

} // TZEDFRMD_CreateContextMenue

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EnableEditMenuActions
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_EnableEditMenuActions( zVIEW vSubtask )
{
   BOOL bEnable = TRUE;
   BOOL bCanCopy  = EDT_CanCopy( vSubtask );
   BOOL bCanPaste = EDT_CanPaste( vSubtask );
   BOOL bCanUndo  = EDT_CanUndo( vSubtask );
   BOOL bCanRedo  = EDT_CanRedo( vSubtask );

   if ( EDT_IsReadOnly( vSubtask ) )
      bEnable = FALSE;

   EnableAction( vSubtask, TZEDFRMD_EDIT_CONTEXT_MENU_UNDO, bEnable ? bCanUndo : FALSE );
   EnableAction( vSubtask, TZEDFRMD_EDIT_CONTEXT_MENU_REDO, bEnable ? bCanRedo : FALSE );
   EnableAction( vSubtask, TZEDFRMD_EDIT_CONTEXT_MENU_CUT, bEnable ? bCanCopy : FALSE );
   EnableAction( vSubtask, TZEDFRMD_EDIT_CONTEXT_MENU_COPY, bCanCopy );
   EnableAction( vSubtask, TZEDFRMD_EDIT_CONTEXT_MENU_PASTE, bEnable ? bCanPaste : FALSE );
   EnableAction( vSubtask, TZEDFRMD_EDIT_CONTEXT_MENU_DELETE, bEnable ? bCanCopy : FALSE );
   EnableAction( vSubtask, TZEDFRMD_EDIT_CONTEXT_MENU_SELECTALL, EDT_GetLineCount( vSubtask ) > 0 );

   return( 0 );

} // TZEDFRMD_EnableEditMenuActions

static zSHORT
SetUpdateFlagInMeta( zVIEW vSubtask )
{
   zVIEW        vEdWrk;
   zVIEW        vSource;
   zVIEW        vMeta;
   zVIEW        vTaskLPLR;
   zVIEW        vZeidonCM;
   zVIEW        vActiveMetas;
   zLONG        lMetaType;
   zLONG        lMetaZKey;
   zSHORT       nRC = zCALL_ERROR;
   zCHAR        szTimestamp[ 33 ];
   zCHAR        szUpdateInd[ 5 ];
   LPVIEWOD     lpViewOD;
   LPVIEWENTITY lpViewEntity;

   mGetWorkView( &vEdWrk, vSubtask );
   if ( vEdWrk == 0 )
   {
      return( nRC );
   }

   // Get the Source Meta for the current buffer.
   GetIntegerFromAttribute( (zPLONG) &vSource, vEdWrk, szlBuffer, szlSourceViewID );

   if ( vSource == 0 || MiGetUpdateForView( vSource ) == 0 )
   {
      return( nRC );
   }

   if ( CompareAttributeToString( vEdWrk, szlBuffer, szlMetaType, "" ) == 0 )
   {
      return( 0 );
   }

   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) < 0 ||
        GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION ) < 0 ||
        GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK ) < 0 )
   {
      return( nRC );
   }

   GetIntegerFromAttribute( &lMetaType, vEdWrk, szlBuffer, szlMetaType );
   if ( lMetaType >= 2000 )
      lMetaType -= 2000;

   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaType", "Type", lMetaType, "" ) < zCURSOR_SET )
   {
      return( nRC );
   }

   CreateViewFromViewForTask( &vMeta, vSource, 0 );
   ResetView( vMeta );

   // Get Root Entity Name
   lpViewOD = (LPVIEWOD) MiGetViewEntityForView( vMeta, 0 );
   if ( lpViewOD == 0 )
      return( nRC );

   lpViewEntity = (LPVIEWENTITY) SysGetPointerFromHandle( lpViewOD->hFirstOD_Entity );

   GetIntegerFromAttribute( &lMetaZKey, vMeta, lpViewEntity->szName, "ZKey" );

   if ( SetCursorFirstEntityByInteger( vActiveMetas, "W_MetaDef", "CPLR_ZKey", lMetaZKey, "" ) >= zCURSOR_SET &&
        CompareAttributeToInteger( vActiveMetas, "W_MetaDef", "Status", 1 ) == 0 )
   {
      GetStringFromAttribute( szUpdateInd, zsizeof( szUpdateInd ), vActiveMetas, "W_MetaDef", "UpdateInd" );

      if ( CompareAttributeToInteger( vActiveMetas, "W_MetaDef", "UpdateInd", 0 ) == 0 ||
           zstrcmp( szUpdateInd, "" ) == 0 )
      {
         // Set Update Indicator to update = Yes ( Implicit, SourceFile )
         SetAttributeFromInteger( vActiveMetas, "W_MetaDef", "UpdateInd", 4 );
         nRC = 1;
      }

      if ( CompareAttributeToInteger( vActiveMetas, "W_MetaDef", "UpdateInd", 4 ) == 0 )
      {
         SysGetDateTime( szTimestamp, zsizeof( szTimestamp ) );
         SetAttributeFromString( vActiveMetas, "W_MetaDef", "LastUpdateDate", szTimestamp );
         SetAttributeFromString( vActiveMetas, "W_MetaDef", "LastSyncDate", szTimestamp );
      }
   }

   DropView( vMeta );
   return( nRC );
}

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_SetBookmark
//
//  Sets a bookmark at the current location in the editor
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_SetBookmark( zVIEW vSubtask )
{
   zCHAR szOptionTag[ 65 ];
   int nTag;

   GetLastCommandTag( vSubtask, szOptionTag );
   if ( strlen( szOptionTag ) > 8 )
   {
      nTag = atoi( szOptionTag + 8 );
      EDT_SetBookmark( vSubtask, nTag );
   }
   return( 0 );

} // TZEDFRMD_SetBookmark

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_GoToBookmark
//
//  Sets position to the specified bookmark in the editor
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_GoToBookmark( zVIEW vSubtask )
{
   zCHAR szOptionTag[ 65 ];
   int nTag;

   GetLastCommandTag( vSubtask, szOptionTag );
   if ( strlen( szOptionTag ) > 12 )
   {
      nTag = atoi( szOptionTag + 12 );
      EDT_GoToBookmark( vSubtask, nTag );
   }
   return( 0 );

} // TZEDFRMD_GoToBookmark

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_ToggleBookmark
//
//  Toggles a bookmark at the current location in the editor
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_ToggleBookmark( zVIEW vSubtask )
{
   EDT_ToggleBookmark( vSubtask );
   return( 0 );

} // TZEDFRMD_ToggleBookmark

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_ClearAllBookmarks
//
//  Clears all bookmarks in the editor
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_ClearAllBookmarks( zVIEW vSubtask )
{
   zCHAR szOptionTag[ 65 ];
   int nTag;

   GetLastCommandTag( vSubtask, szOptionTag );
   if ( strlen( szOptionTag ) > 8 )
   {
      nTag = atoi( szOptionTag + 8 );
      EDT_ClearAllBookmarks( vSubtask );
   }
   return( 0 );

} // TZEDFRMD_ClearAllBookmarks

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_GoToNextBookmark
//
//  Go to next bookmark in the editor
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_GoToNextBookmark( zVIEW vSubtask )
{
   zCHAR szOptionTag[ 65 ];
   int nTag;

   GetLastCommandTag( vSubtask, szOptionTag );
   if ( strlen( szOptionTag ) > 8 )
   {
      nTag = atoi( szOptionTag + 8 );
      EDT_GoToNextBookmark( vSubtask );
   }
   return( 0 );

} // TZEDFRMD_GoToNextBookmark

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_GoToPreviousBookmark
//
//  Go to previous bookmark in the editor
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_GoToPreviousBookmark( zVIEW vSubtask )
{
   zCHAR szOptionTag[ 65 ];
   int nTag;

   GetLastCommandTag( vSubtask, szOptionTag );
   if ( strlen( szOptionTag ) > 8 )
   {
      nTag = atoi( szOptionTag + 8 );
      EDT_GoToPreviousBookmark( vSubtask );
   }
   return( 0 );

} // TZEDFRMD_GoToNextBookmark

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: TZEDFRMD_EditReplaceAll
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
TZEDFRMD_EditReplaceAll( zVIEW vSubtask )
{
   zCHAR szMsg[ 256 ];

   zLONG lChanged =  EDT_ReplaceAll( vSubtask );
   if ( lChanged > 0 )
      sprintf_s( szMsg, sizeof( szMsg ), "Specified text changed %d times", lChanged );
   else
      sprintf_s( szMsg, sizeof( szMsg ), "Specified text not found" );

   MB_SetMessage( vSubtask, MAIN_DIL, szMsg );
   return( (zSHORT) lChanged );

} // TZEDFRMD_EditReplaceAll

/////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: ParseGenerateJava
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /* DIALOG */  OPERATION
ParseGenerateJava( zVIEW vSubtask )
{
   zSHORT nRC = SaveAndParse( vSubtask, "Java", FALSE );
   if ( nRC == 0 )
   {
      nRC = Generate( vSubtask, "Java", FALSE );
      if ( nRC == 0 )
      {
         MessagePrompt( vSubtask, "ED0010", szlZeidonEditor, "Parse/Generate completed successfully.", 0, 0, 0, zICON_INFORMATION );
      }
   }
   return( nRC );

} // ParseGenerateJava


#ifdef __cplusplus
}
#endif

