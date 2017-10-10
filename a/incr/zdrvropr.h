/////////////////////////////////////////////////////////////////////////////
// Project ZdCtl
//
// This is a part of the Zeidon Dynamic Rendering of GUI applications package.
// Copyright © 1995 - 2016 QuinSoft, Inc. and TONBELLER AG.
// All Rights Reserved.
//
// SUBSYSTEM:    zdrapp.dll - ZDr Application
// FILE:         zdrvropr.h
// AUTHOR:
//
// OVERVIEW
// ========
// Class definitions for standard Zeidon DR Ctrls.
//

//
// Change log most recent first order:
//
//
// 2002.03.12  DKS
//    Added ED_ operations to get key press event information.
//
// 2002.03.06  DKS
//    Rounding fix for sizing ctrl's in painter.
//
// 2002.02.21  TMV
//    Added operation TG_SetDateCtrlForColumn.
//
// 2001.12.04  DKS
//    Added Push and PopReportTabStops for printing reports.
//
// 2001.10.12  HH
//    Change zFARPROC_INTERP prototype to handle operation return code.
//
// 2001.09.21  PAS
//    Added new operations and defines to support Report Group Exits
//
// 2001.08.14  TMV   Grid
//    introduced a bunch of TG_Functions
//
// 2001.08.06  TMV   Grid
//    changed Operationname TG_SetAllignment to TG_SetAlignment because it
//    was misspelled.
//    Added new operations for BL
//       TG_GetCaption
//       TG_ShowColumn
//      TG_LimitTextLen
//
// 2001.07.16  BL    LRP
//    Added ED_SetCtrlMapping for remapping an Edit Control
//
// 2001.07.09  TMV   TrueGrid
//    Add new global operations for truegrid and actbar
//
// 2001.06.18  BL    TrueGrid
//    Change Parameter in TG_LockColumn
//
// 2001.06.17  BL    TrueGrid
//    Added new functions (TG_GetMouseClick and TG_GetMouseClickWithKey) and
//    defines for TrueGrid Control
//
// 2001.06.01  TMV   2000   webgrid
//    add prototypes for ZWEBGRID_XXX - functions
//
// 2001.05.23  BL    WEB
//    Number of Parameters corrected for Operation GetCtrlRowColText
//
// 2001.04.28  BL    TREE
//    Added Parameter bEnsureVisible to Function OL_SetTextColorForItemText
//
// 2001.04.28  BL    TREE
//    Added new Function OL_RemoveAllTextColorsForItemText
//    Rename OL_RemoveAllTextColorsForItemText to OL_ResetAllTextColorsForItemText
//
// 2001.04.25  BL    TREE
//    Added new Function Added OL_SetTextColorForItemText
//
// 2001.04.17  RS    WEB
//    Changes from DKS for Printout (Doc).
//
// 2001.02.08  BL    TREE
//    Added new prototypes and defines for new Tree Control
//
// 2001.01.31  DKS   WEB
//    Added new defines for Reports.
//
// 2000.11.28  HH
//    const char change OperatorPromptForFile
//
// 2000.08.16  HH
//    set pack level of zCTRLBOI_BMP to 8. This is a workaround, neccessary
//    because driver and Zeidon tools have different pack levels (Zp8,Zp).
//    As long as this ugly situation will persist, we must explicitly set
//    the packlevel for all structures, which are commonly used by driver
//    and tools/engine.
//
// 2000.08.07  RG    Z2000
//    Changed declaration of fontsize from zSHORT to zLONG to remove
//    compiler warnings in Zeidon Tools
//
// 2000.03.14  TMV
//    Added prototype OperatorPromptFindReplace.
//
// 1999.09.07  TMV
//    define macro mReleaseInit for release and initialize COM Interfaces
//
// 1999.09.07  TMV
//    Change macro mMSG because of TB night compile evaluation
//
// 1999.04.19  RS
//    Commentlines required for Rose.
//
// 1999.03.10  DKS
//    Altered the Profile functions to remove name conflict.
//

// Don't remove the following commentlines. They are required for Rose.
//#include <kzoessaa.h> //required for Rose
//#include <kzoengaa.h> //required for Rose

#ifndef __zdrvropr_h__
#define __zdrvropr_h__

/////////////////////////////////////////////////////////////////////////////
//
// Prototypes for Zeidon Driver Operations
// Copyright © 1995 - 2016 QuinSoft, Inc.
//
/////////////////////////////////////////////////////////////////////////////

#ifdef __WIN32__
#else
#define GetCtrlFont                 GetControlFont
#define GetCtrlID                   GetControlID
#define GetCtrlPosition             GetControlPosition
#define GetCtrlSize                 GetControlSize
#define GetCtrlState                GetControlState
#define GetCtrlText                 GetControlText
#define GetCtrlWithFocus            GetControlWithFocus
#define MapCtrl                     MapControl
#define RefreshCtrl                 RefreshControl
#define SetCtrlBorder               SetControlBorder
#define SetCtrlFontBold             SetControlFontBold
#define SetCtrlFontItalic           SetControlFontItalic
#define SetCtrlFontOverstrike       SetControlFontOverstrike
#define SetCtrlFontSize             SetControlFontSize
#define SetCtrlFontTag              SetControlFontTag
#define SetCtrlFontUnderline        SetControlFontUnderline
#define SetCtrlMousePointer         SetControlMousePointer
#define SetCtrlOwner                SetControlOwner
#define SetCtrlParent               SetControlParent
#define SetCtrlPosition             SetControlPosition
#define SetCtrlSize                 SetControlSize
#define SetCtrlState                SetControlState
#define SetCtrlText                 SetControlText
#define SetCtrlTextLth              SetControlTextLth
#define SetFocusToCtrl              SetFocusToControl
#define SetFocusToCtrl              SetFocusToControl
#define SetFocusToNextCtrl          SetFocusToNextControl
#define TX_GetTextRptCtrlBOI        TX_GetTextRptControlBOI
#define TX_SetTextRptCtrlBOI        TX_SetTextRptControlBOI
#define zMSG_GetCtrlState           zMSG_GetControlState
#define zMSG_GetCtrlText            zMSG_GetControlText
#define zMSG_HiliteCtrlItem         zMSG_HiliteControlItem
#define zMSG_RefreshCtrl            zMSG_RefreshControl
#define zMSG_SetCtrlState           zMSG_SetControlState
#define zMSG_SetCtrlText            zMSG_SetControlText
#endif

#ifdef __cplusplus
extern "C"
{
#endif


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define zPOINT  POINT
#define zRGB    RGB

#ifdef __WIN32__
#include <wtypes.h>
#include <richedit.h>
#endif

#define zWAB_SwitchToAction                   -1   // Use SwitchToAction operation
#define zWAB_DeterminedInDialogOperation       0

#define zWAB_StayOnWindow                      1   // PREVENT ACTION
#define zWAB_StayOnWindowWithRefresh           2
#define zWAB_StayOnWindowWebRefresh            3
#define zWAB_StayOnWindowRefreshNP             4  // Same Window / No Position

#define zWAB_StartOrFocusModelessDialog       30
#define zWAB_StartDialogTask                  31
#define zWAB_StartModelessWindow              32
#define zWAB_StartOrFocusModelessWindow       38
#define zWAB_StartModalWindow                 36
#define zWAB_StartModelessSubwindow           33
#define zWAB_StartOrFocusModelessSubwindow    39
#define zWAB_StartModalSubwindow              34
#define zWAB_StartOrFocusModelessApp          37
#define zWAB_StartNewApp                      35  // ReCAPTCHA Subwindow  

#define zWAB_StartPopupMenu                   40
#define zWAB_StartBrowserHTML_Page            41
#define zWAB_StartEmailClient                 42
#define zWAB_StartEmailClientBCC              43
#define zWAB_StartEmailClientCC               44
#define zWAB_LinkToHTML_Address               45
#define zWAB_ProcessDownloadFile              46
#define zWAB_StartBrowserPDF_Page             47
#define zWAB_StartJasperPDF_Page              48
#define zWAB_StartJasperXLS_Page              49

#define zWAB_ReplaceDialogWithDialog          51
#define zWAB_ReplaceWindowWithModelessWindow  52
#define zWAB_ReplaceWindowWithModalWindow     53
#define zWAB_ReplaceCurrentAppWithApp         54
#define zWAB_ReCAPTCHA			      55  // ReCAPTCHA Replace Window

#define zWAB_StartModalSubwindowNP	      57  // Subwindow / No Position

#define zWAB_PrintWindow	              60  // Print Window
#define zWAB_StartSplitWindow                 61
#define zWAB_ReplaceSplitWindow               62
#define zWAB_DeleteSplitWindow                63

#define zWAB_ReturnToParent                   71
#define zWAB_ReturnToParentWithRefresh        72
#define zWAB_ReturnToTopWindow                73
#define zWAB_ReturnToTopWindowWithRefresh     74
#define zWAB_StartTopWindow                   75
#define zWAB_ResetTopWindow                   76
#define zWAB_StartModalWebPopup               78
#define zWAB_StartModelessWebPopup            79

#define zWAB_ReturnFromWebPopupNoRefresh      84
#define zWAB_ReturnFromWebPopupWithRefresh    85

#define zWAB_ExitDialogTask                   99

#define zWAB_SuspendToDebugger               201
#define zWAB_ResumeFromDebugger              202

#define zWAB_TerminateActionForError        9999
#define zWAB_ProcessImmediateAction  0x10000000L
#define zWAB_NoDriverMessageOnError  0x20000000L
#define zWAB_ProcessImmediateReturn  0x40000000L

// Driver State
#define zMSGQ_Action                           1L
#define zMSGQ_Tabbing                          2L
#define zMSGQ_MapToOI                          3L
#define zMSGQ_DialogOperation                  4L

// Report Group Exits
#define zRCONTROL_STATUS_GROUPINACTIVE         0
#define zRCONTROL_STATUS_NOTPRINTED            1
#define zRCONTROL_STATUS_PARTIALPRINT          2
#define zRCONTROL_STATUS_PRINTED               3

#define zRGE_EVENT_PREPRINT                    1
#define zRGE_EVENT_GROUP_CONTINUE              2
#define zRGE_EVENT_GROUP_SPLITING              3
#define zRGE_EVENT_GROUP_SPLITTING             3
#define zRGE_EVENT_POSTPRINT                   4

#define zRGE_RETURN_NORMAL                     0
#define zRGE_RETURN_SUPPRESS                   1
#define zRGE_RETURN_NEWPAGE                    2

// Driver Event Type
#define zMSGQ_AfterAcceptSubobject             1L
#define zMSGQ_AfterCancelSubobject             2L
#define zMSGQ_AfterDeleteEntity                3L
#define zMSGQ_AfterExcludeEntity               4L
#define zMSGQ_AfterTabbing                     5L
#define zMSGQ_AfterMapToOI                     6L
#define zMSGQ_AfterDialogOperation             7L
#define zMSGQ_AfterCreateEntity                8L
#define zMSGQ_AfterCreateTemporalEntity        9L
#define zMSGQ_AfterCreateTemporalSubobject    10L

#if 0
#define zMSG_SetWindowActionBehavior         100L
#define zMSG_StartTask                       110L
#define zMSG_SetNewApplicationSubtask        111L
#define zMSG_SetWindowCaptionTitle           200L
#define zMSG_ActivateWindow                  201L
#define zMSG_RefreshWindow                   203L
#define zMSG_GetCtrlText                     301L
#define zMSG_SetCtrlText                     302L
#define zMSG_HiliteCtrlItem                  303L
#define zMSG_RefreshCtrl                     304L
#define zMSG_GetCtrlState                    305L
#define zMSG_SetCtrlState                    306L
#define zMSG_GetOptionState                  307L
#define zMSG_SetOptionState                  308L
#define zMSG_EnableAction                    309L
#define zMSG_SetDIL_Message                  900L
#define zMSG_InitInterpretor                 990L
#define zMSG_ResumeFromDebugger              995L
#endif

#define mSTR( x )    #x
#define mSTR2( x )   mSTR( x )
#define mMSG( desc ) message( __FILE__ "(" mSTR2( __LINE__ ) ") -> " #desc )

#if 0  // these are defined only in the Ctrl Registration Object ...
       // here for reference only.  These are the actual IDs for the
       // controls in ZEIDON.PPE and cannot be altered.
       // IDs in the range of 1000 to 4000 are reserved for use by
       // Zeidon standard controls.  IDs in the range of 4001 to 8000
       // are reserved for use by third party developers of Zeidon
       // controls (assigned and registered by Zeidon development).
       // "In house" controls must be assigned ZKeys in the range from
       // 8001 to 9999.

#define zTEXT_CONTROL                       1000L
#define zRTE_CONTROL                        1005L
#define zEDITGROUP_CONTROL                  1009L
#define zEDIT_CONTROL                       1010L
#define zMLE_CONTROL                        1015L
#define zPUSHBUTTON_CONTROL                 1020L
#define zTIMER_CONTROL                      1025L
#define zRADIOBUTTONGROUP_CONTROL           1030L
#define zRADIOBUTTON_CONTROL                1031L
#define zCHECKBOX_CONTROL                   1040L
#define zCOMBOBOX_CONTROL                   1050L
#define zCOMBOITEM_CONTROL                  1051L
#define zCALENDAR_CONTROL                   1060L
#define zDAYTIMER_CONTROL                   1065L
#define zCONTROLBAR_CONTROL                 1070L
#define zCONTROLCTL_CONTROL                 1071L
#define zLISTBOX_CONTROL                    1080L
#define zLISTCTL_CONTROL                    1081L
#define zGROUPBOX_CONTROL                   1090L
#define zPAINTER_CONTROL                    1999L
#define zPAINTERTOOLBAR_CONTROL             2000L
#define zER_DIAGRAM_CONTROL                 2005L
#define zGRID_CONTROL                       2010L
#define zGRID_EDIT_CONTROL                  2011L
#define zGRID_COMBO_CONTROL                 2012L
#define zGRID_CHECK_CONTROL                 2013L
#define zGRID_SUB_CONTROL                   2014L
#define zDIL_CONTROL                        2020L
#define zDILITEM_CONTROL                    2021L
#define zOUTLINER_CONTROL                   2030L
#define zOUTLINER_CTL_CONTROL               2031L
#define zPALETTE_CONTROL                    2040L
#define zGRAPH_CONTROL                      2050L
#define zICON_CONTROL                       2060L
#define zHIER_DIAG_CONTROL                  2070L
#define zBITMAP_CONTROL                     2080L
#define zBITMAP_BUTTON_CONTROL              2085L
#define zTAB_CONTROL                        2090L
#define zTABCTL_CONTROL                     2091L
#define zTOOLBAR_CONTROL                    2100L
#define zTOOLITEM_CONTROL                   2101L
#define zGROUPSET_REPORT                    3000L
#define zGROUP_REPORT                       3010L
#define zTEXT_REPORT                        3020L
#define zMLE_REPORT                         3030L
#define zBMP_REPORT                         3040L
#define zSHAPE_REPORT                       3050L
#define zBLOCK_REPORT                       3060L
#define zLISTBOX_REPORT                     3070L
#define zLISTCTL_REPORT                     3071L
#define zACTIVEX                            4000L
#endif

#define zOPTION_STATUS_ENABLED                 1
#define zOPTION_STATUS_CHECKED                 2
#define zOPTION_STATUS_VISIBLE                 3
#define zOPTION_STATUS_TEXT                    4

#define zWINDOW_STATUS                         0
#define zWINDOW_STATUS_ENABLED                 1
#define zWINDOW_STATUS_VISIBLE                 2
#define zWINDOW_STATUS_MINIMIZE                3
#define zWINDOW_STATUS_MAXIMIZE                4
#define zWINDOW_STATUS_RESTORE                 5
#define zWINDOW_STATUS_ASYNC                   6
#define zWINDOW_STATUS_UPDATE                  7
#define zWINDOW_STATUS_SETFOCUS                8
#define zWINDOW_STATUS_DESTROY                 9
#define zWINDOW_STATUS_SHOW_PARENT            10
#define zWINDOW_STATUS_STOP_EVENTS            11
#define zWINDOW_STATUS_SET_NO_ERROR_PROMPT    12
#define zWINDOW_STATUS_ENABLED_VIEW           13
#define zWINDOW_STATUS_INVALIDATE             14
#define zWINDOW_STATUS_NO_REFRESH             15
#define zWINDOW_STATUS_LAST                   16

// These defines are in ascending order.  OR the state with 0x200000
// to determine if the subtask is in a DELETE state.  OR the state with
// 0x0010 to determine if the subtask is in a CONSTRUCTION state.  OR
// the state with 0x010000 to determine if the subtask is WELL_FORMED.

#define zWNDTYPE_INIT                        0x00000000L
#define zWNDTYPE_3D                          0x00000001L
#define zWNDTYPE_MDI                         0x00000002L
#define zWNDTYPE_SINGLE_RELSIZE              0x00000004L

#define zCONTROL_STATUS_ENABLED                1
#define zCONTROL_STATUS_CHECKED                2
#define zCONTROL_STATUS_VISIBLE                3
#define zCONTROL_STATUS_BACKGROUND_COLOR       4
#define zCONTROL_STATUS_TEXT_COLOR             5
#define zCONTROL_STATUS_FONT                   6
#define zCONTROL_STATUS_ENTER                  7
#define zCONTROL_STATUS_ERROR                  8
#define zCONTROL_STATUS_AUTOGRAY               9
#define zCONTROL_STATUS_TOPMOST               10
#define zCONTROL_STATUS_BOTTOMMOST            11
#define zCONTROL_STATUS_HWND                  12
#define zCONTROL_STATUS_AUTOMAP_FROM_OI       13
#define zCONTROL_STATUS_AUTOMAP_TO_OI         14
#define zCONTROL_STATUS_DISABLE_READONLY      15
#define zCONTROL_STATUS_REPAINT               16
#define zCONTROL_STATUS_MARK_READONLY_ENABLED 17
#define zCONTROL_STATUS_ENABLE_TABSTOP        18
#define zCONTROL_STATUS_SELECT_INDEX          19
#define zCONTROL_STATUS_ABSOLUTE_PIXEL_SIZE   20
#define zCONTROL_STATUS_ABSOLUTE_PIXEL_POS    21
#define zCONTROL_STATUS_HASBUTTONS            22
#define zCONTROL_STATUS_HASLINES              23
#define zCONTROL_STATUS_LINESATROOT           24
#define zCONTROL_STATUS_DISABLEDRAGDROP       25
#define zCONTROL_STATUS_NOSHOW_ENTITY         26
#define zCONTROL_STATUS_MULTIPLEROOT          27
#define zCONTROL_STATUS_MULTISELECT           28
#define zCONTROL_STATUS_SINGLEEXPAND          29
#define zCONTROL_STATUS_EXPAND                30
#define zCONTROL_STATUS_EXPANDALL             31
#define zCONTROL_STATUS_MAP_ERROR             32
#define zCONTROL_STATUS_SELECT_ALL            33
#define zCONTROL_STATUS_RESET                 34
#define zCONTROL_STATUS_CREATED               35
#define zCONTROL_STATUS_MAPPED                36

#define zCONTROL_PROPERTY_INTEGER_DATA         1
#define zCONTROL_PROPERTY_STRING_DATA          2
#define zCONTROL_PROPERTY_COLOR_TEXT           3
#define zCONTROL_PROPERTY_COLOR_BACKGROUND     4
#define zCONTROL_PROPERTY_FONT                 6
#define zCONTROL_PROPERTY_SUBCTRL_JUSTIFY      7
#define zCONTROL_PROPERTY_TAG                  8
#define zCONTROL_PROPERTY_COLUMN_COUNT         9

#define zEXPAND                                1
#define zEXPANDALL                             2
#define zCOLLAPSE                              3
#define zCOLLAPSEALL                           4


// for TrueGrid
#define zMOUSE_LEFT                               1
#define zMOUSE_RIGHT                              2
#define zSHIFT                                  1
#define zSTRG                                   2

// common attributes for all controls
#define zCONTROL_RESERVED_UNUSABLE    0x80000000L // <<== cannot use this bit
#define zCONTROL_SIZEABLEBORDER       0x40000000L // since when it is the only
#define zCONTROL_BORDERON             0x00000000L // bit set, Core interprets
#define zCONTROL_BORDEROFF            0x20000000L // it as a null indicator.
#define zCONTROL_FULL_CLIENT          0x10000000L
#define zCONTROL_INVISIBLE            0x08000000L
#define zCONTROL_DISABLED             0x04000000L
#define zCONTROL_CENTERJUSTIFY        0x02000000L
#define zCONTROL_RIGHTJUSTIFY         0x01000000L
#define zCONTROL_LEFTJUSTIFY          0x00000000L
#define zCONTROL_RELATIVE             0x00F00000L
#define zCONTROL_RELATIVE_POSITION    0x00C00000L
#define zCONTROL_RELATIVE_POS_X       0x00800000L
#define zCONTROL_RELATIVE_POS_Y       0x00400000L
#define zCONTROL_RELATIVE_SIZE        0x00300000L
#define zCONTROL_RELATIVE_SIZE_X      0x00200000L
#define zCONTROL_RELATIVE_SIZE_Y      0x00100000L
#define zCONTROL_NOTABSTOP            0x00080000L
#define zCONTROL_SPECIFIC_1           0x00040000L
#define zCONTROL_SPECIFIC_2           0x00020000L
#define zCONTROL_SPECIFIC_3           0x00010000L

#define zCONTROLX_RESERVED_UNUSABLE   0x80000000L // <<== cannot use this bit
#define zCONTROLX_DISABLE_READONLY    0x01000000L // since when it is the only
#define zCONTROLX_ABSOLUTE_PIXEL_SIZE 0x02000000L // bit set, Core interprets
#define zCONTROLX_ABSOLUTE_PIXEL_POS  0x04000000L // it as a null indicator.
#define zCONTROLX_PREFILL             0x08000000L // it as a null indicator.
#define zCONTROLX_SPECIFIC_1          0x00080000L
#define zCONTROLX_SPECIFIC_2          0x00040000L
#define zCONTROLX_SPECIFIC_3          0x00020000L
#define zCONTROLX_SPECIFIC_4          0x00010000L
#define zCONTROLX_SPECIFIC_5          0x00800000L
#define zCONTROLX_SPECIFIC_6          0x00400000L
#define zCONTROLX_SPECIFIC_7          0x00200000L
#define zCONTROLX_SPECIFIC_8          0x00100000L

#define zCOMBOBOX_SCOPE_OI            0x00000100L // 256
#define zLISTBOX_SCOPE_OI             0x00004000L // 16384
#define zGRID_SCOPE_OI                0x00004000L // 16384
#define zSS_SCOPE_OI                  zCONTROLX_SPECIFIC_7

#define zBEEP               0  // used for all internal MessageSends
                               // 0 = no beep   1 = beep

#define zBUTTONS_YESNO                         1
#define zBUTTONS_YESNOCANCEL                   2
#define zBUTTONS_OK                            3
#define zBUTTONS_OKCANCEL                      4
#define zBUTTONS_RETRYCANCEL                   5
#define zBUTTONS_ABORTRETRYIGNORE              6

#define zRESPONSE_YES                          1
#define zRESPONSE_NO                           2
#define zRESPONSE_CANCEL                       3
#define zRESPONSE_OK                           4
#define zRESPONSE_ABORT                        5
#define zRESPONSE_RETRY                        6
#define zRESPONSE_IGNORE                       7

#define zICON_INFORMATION                      1   // TaskModal
#define zICON_QUESTION                         2   // TaskModal
#define zICON_EXCLAMATION                      3   // TaskModal
#define zICON_ERROR                            4   // STOP with SystemModal
#define zICON_STOP                             5   // STOP with TaskModal

#define zREPORT_PRINTPREVIEW          0x00000001
#define zREPORT_PRINTDIALOG           0x00000002
#define zREPORT_IGNORE_OE_PRINTSETTNG 0x00000004
#define zREPORT_MULTIPLE_ROOT         0x00000008
#define zREPORT_CLOSESUBTASK          0x00000010
#define zREPORT_COUNTPAGES            0x00000020
#define zREPORT_DROPVIEW              0x00000040
#define zREPORT_PRINT2CSV             0x00000080
#define zREPORT_PRINT2HTML            0x00000100
#define zREPORT_FIT2PAGE              0x00000200
#define zREPORT_RESETPAGING           0x00000400
#define zREPORT_REVERSE_PARM          0x00000800
#define zREPORT_LANDSCAPE             0x00010000
#define zREPORT_PRINTREMOTE           0x00020000
#define zREPORT_PRINTNAMED            0x00040000
#define zREPORT_RETURNNAME            0x00080000
#define zREPORT_CREATENAME            0x00100000
#define zREPORT_PRINT2PDF             0x00200000
#define zREPORT_PRINT2CTRL            0x00400000
#define zREPORT_USEFOLDER             0x00800000

#define zCOLOR_DEFINITION_DFLT        0xFD000000L     // -50331648L
#define zCOLOR_WINDOW_DFLT            0xFFFFFFFFL     // -1L

#ifdef __OS2__

#define zCOLOR_SCROLLBAR              SYSCLR_SCROLLBAR
#define zCOLOR_BACKGROUND             SYSCLR_BACKGROUND
#define zCOLOR_ACTIVECAPTION          SYSCLR_ACTIVETITLE
#define zCOLOR_INACTIVECAPTION        SYSCLR_INACTIVETITLE
#define zCOLOR_MENU                   SYSCLR_MENU
#define zCOLOR_WINDOW                 SYSCLR_WINDOW
#define zCOLOR_WINDOWFRAME            SYSCLR_WINDOWFRAME
#define zCOLOR_MENUTEXT               SYSCLR_MENUTEXT
#define zCOLOR_WINDOWTEXT             SYSCLR_OUTPUTTEXT
#define zCOLOR_CAPTIONTEXT            SYSCLR_TITLETEXT
#define zCOLOR_ACTIVEBORDER           SYSCLR_ACTIVEBORDER
#define zCOLOR_INACTIVEBORDER         SYSCLR_INACTIVEBORDER
#define zCOLOR_APPWORKSPACE           SYSCLR_APPWORKSPACE
#define zCOLOR_HIGHLIGHT              SYSCLR_HILITEFOREGROUND
#define zCOLOR_HIGHLIGHTTEXT          SYSCLR_WINDOWSTATICTEXT
#define zCOLOR_BTNFACE                SYSCLR_BUTTONMIDDLE
#define zCOLOR_BTNSHADOW              SYSCLR_BUTTONDARK
#define zCOLOR_GRAYTEXT               SYSCLR_SHADOWTEXT
#define zCOLOR_BTNTEXT                SYSCLR_OUTPUTTEXT
#define zCOLOR_INACTIVECAPTIONTEXT    SYSCLR_INACTIVETITLETEXT
#define zCOLOR_BTNHIGHLIGHT           SYSCLR_BUTTONLIGHT

#define zCOLOR_WHITE                  CLR_WHITE
#define zCOLOR_BLACK                  CLR_BLACK
#define zCOLOR_BLUE                   CLR_BLUE
#define zCOLOR_RED                    CLR_RED
#define zCOLOR_PINK                   CLR_PINK
#define zCOLOR_GREEN                  CLR_GREEN
#define zCOLOR_CYAN                   CLR_CYAN
#define zCOLOR_YELLOW                 CLR_YELLOW
#define zCOLOR_NEUTRAL                CLR_NEUTRAL
#define zCOLOR_DARKGRAY               CLR_DARKGRAY
#define zCOLOR_DARKBLUE               CLR_DARKBLUE
#define zCOLOR_DARKRED                CLR_DARKRED
#define zCOLOR_DARKPINK               CLR_DARKPINK
#define zCOLOR_DARKGREEN              CLR_DARKGREEN
#define zCOLOR_DARKCYAN               CLR_DARKCYAN
#define zCOLOR_BROWN                  CLR_BROWN
#define zCOLOR_PALEGRAY               CLR_PALEGRAY

#else

#define zCOLOR_SCROLLBAR              COLOR_SCROLLBAR
#define zCOLOR_BACKGROUND             COLOR_BACKGROUND
#define zCOLOR_ACTIVECAPTION          COLOR_ACTIVECAPTION
#define zCOLOR_INACTIVECAPTION        COLOR_INACTIVECAPTION
#define zCOLOR_MENU                   COLOR_MENU
#define zCOLOR_WINDOW                 COLOR_WINDOW
#define zCOLOR_WINDOWFRAME            COLOR_WINDOWFRAME
#define zCOLOR_MENUTEXT               COLOR_MENUTEXT
#define zCOLOR_WINDOWTEXT             COLOR_WINDOWTEXT
#define zCOLOR_CAPTIONTEXT            COLOR_CAPTIONTEXT
#define zCOLOR_ACTIVEBORDER           COLOR_ACTIVEBORDER
#define zCOLOR_INACTIVEBORDER         COLOR_INACTIVEBORDER
#define zCOLOR_APPWORKSPACE           COLOR_APPWORKSPACE
#define zCOLOR_HIGHLIGHT              COLOR_HIGHLIGHT
#define zCOLOR_HIGHLIGHTTEXT          COLOR_HIGHLIGHTTEXT
#define zCOLOR_BTNFACE                COLOR_BTNFACE
#define zCOLOR_BTNSHADOW              COLOR_BTNSHADOW
#define zCOLOR_GRAYTEXT               COLOR_GRAYTEXT
#define zCOLOR_BTNTEXT                COLOR_BTNTEXT
#define zCOLOR_INACTIVECAPTIONTEXT    COLOR_INACTIVECAPTIONTEXT
#define zCOLOR_BTNHIGHLIGHT           COLOR_BTNHIGHLIGHT

#endif

#define zRGB_DEFAULT                   -1L
#define zRGB_BLACK                     zRGB( 0, 0, 0 )
#define zRGB_BLUE                      zRGB( 0, 0, 255 )
#define zRGB_DARKBLUE                  zRGB( 0, 0, 128 )
#define zRGB_BROWN                     zRGB( 128, 128, 64 )
#define zRGB_DARKBROWN                 zRGB( 128, 128, 0 )
#define zRGB_CYAN                      zRGB( 0, 255, 255 )
#define zRGB_DARKCYAN                  zRGB( 0, 128, 128 )
#define zRGB_GRAY                      zRGB( 192, 192, 192 )
#define zRGB_DARKGRAY                  zRGB( 128, 128, 128 )
#define zRGB_GREEN                     zRGB( 0, 255, 0 )
#define zRGB_DARKGREEN                 zRGB( 0, 128, 0 )
#define zRGB_MAGENTA                   zRGB( 255, 0, 255 )
#define zRGB_DARKMAGENTA               zRGB( 128, 0, 128 )
#define zRGB_YELLOW                    zRGB( 255, 255, 0 )
#define zRGB_DARKYELLOW                zRGB( 128, 128, 0 )
#define zRGB_RED                       zRGB( 255, 0, 0 )
#define zRGB_DARKRED                   zRGB( 128, 0, 0 )
#define zRGB_WHITE                     zRGB( 255, 255, 255 )
#define zRGB_PINK                      zRGB( 255, 0, 255 )
#define zRGB_DARKPINK                  zRGB( 255, 0, 128 )
#define zRGB_PALEGRAY                  zRGB( 192, 192, 192 )
#define zRGB_GREENGRAY                 zRGB( 195, 250, 195 )

#define zOFN_READONLY            0x00000002  //     2
#define zOFN_OVERWRITEPROMPT     0x00000004  //     4
#define zOFN_HIDEREADONLY        0x00000008  //     8
#define zOFN_NOCHANGEDIR         0x00000010  //    16
#define zOFN_SHOWHELP            0x00000020  //    32
#define zOFN_NOVALIDATE          0x00000040  //    64
#define zOFN_ALLOWMULTISELECT    0x00000080  //   128
#define zOFN_EXTENSIONDIFFERENT  0x00000100  //   256
#define zOFN_PATHMUSTEXIST       0x00000200  //   512
#define zOFN_FILEMUSTEXIST       0x00000400  //  1024
#define zOFN_CREATEPROMPT        0x00000800  //  2048
#define zOFN_SHAREAWARE          0x00001000  //  4096
#define zOFN_NOREADONLYRETURN    0x00002000  //  8192
#define zOFN_SAVEAS              0x00004000  // 16384
#define zOFN_GETDIRECTORY        0x00008000

#define zOFN_NOTESTFILECREATE    0x00010000
#define zOFN_NONETWORKBUTTON     0x00020000
#define zOFN_NOLONGNAMES         0x00040000  // force no long names for 4.x modules
#if (WINVER >= 0x0400)
#define zOFN_NODEREFERENCELINKS  0x00100000
#define zOFN_LONGNAMES           0x00200000  // force long names for 3.x modules
#endif // WINVER >= 0x0400

#pragma pack( push, __zdrvropr_h )
#pragma pack( 1 )

typedef struct tagACCEL_DEF
{
   zUSHORT  fCtrl : 1,
            fAlt : 1,
            fShift : 1,
            fNumlock : 1,
            fExtra : 12;
   zUSHORT  uVK;         // virtual key

} zACCEL_DEF;

// The list is terminated by an entry flagged by a -1 in nID.
typedef struct tagACCELERATOR_TABLE
{
   short nID;           // Action rel-nbr/Ctrl ID/Hotkey rel-nbr
   char  chType;        // Action/Ctrl/Hotkey/System
   zACCEL_DEF ac;

} zACCEL_TABLE;
typedef zACCEL_TABLE *LPACCEL_TABLE;

typedef struct tagLABEL_DATA
{
   char   chBold;
   char   chItalic;
   char   chStrikeout;
   char   chUnderline;
   zLONG  lPointSize;
   zLONG  lTextColor;
   char   chMultiLine;        // not used online
   char   chTopLeft;
   char   chCenter;
   char   chBottomRight;
   zLONG  lBorderStyle;       // not used online
   zLONG  lBorderColor;       // not used online
   zLONG  lEscapement;
   zLONG  lType;              // not used online
   char   szFontName[ 20 ];   // LF_FACESIZE
   char   szReserved[ 20 ];
   zLONG  lTextBkColor;
   zLONG  lBackgroundColor;
   zLONG  lHighlightColor;
   char   chBorder;
   char   chBeveledLine;
   char   chVerticalText;
   char   chHighlight;
   char   chUseToolTip;
   char   chHyperText;
   char   szToolTip[ 256 ];

} LABEL_DATA;

// This structure is passed to Zeidon events.
typedef struct tagGRID_CELL
{
   zLONG  lRow;
   zSHORT nCol;
   zPCHAR pchText;

} zGRID_CELL;

#define zACCEL_ACTION           'A'
#define zACCEL_CONTROL          'C'
#define zACCEL_HOTKEY           'H'
#define zACCEL_SYSTEM           'S'

#define zLOUSHORT( l )         ((zUSHORT)(zULONG) ( l ))
#define zHIUSHORT( l )         ((zUSHORT)((((zULONG)( l )) >> 16) & 0xFFFF))
#define zMAKELONG( low, high ) ((zULONG)(((zUSHORT)( low )) | (((zULONG)((zUSHORT)( high ))) << 16)))

#define mConvertDegMinSecToDecimalDeg( dDegrees, dMinutes, dSeconds ) \
   ((double) dDegrees + (dMinutes / 60.0) + (dSeconds / 3600.0))
#define mConvertMapDlgToPixelX( a ) \
   ((zSHORT) ((((zLONG) (a) * g_lMapDlgCharX) + 512) >> 10))// divide by 1024
#define mConvertMapDlgToPixelY( a ) \
   ((zSHORT) ((((zLONG) (a) * g_lMapDlgCharY) + 512) >> 10))// divide by 1024
#define mConvertPixelToMapDlgX( a ) ((zSHORT) ((((zLONG) (a) << 10) + \
   (g_lMapDlgCharX >> 1)) / g_lMapDlgCharX))              // multiply by 1024
#define mConvertPixelToMapDlgY( a ) ((zSHORT) ((((zLONG) (a) << 10) + \
   (g_lMapDlgCharY >> 1)) / g_lMapDlgCharY))              // multiply by 1024

#define mConvertMapDlgToCharX( a )  \
   ((zSHORT) ((((zLONG) (a) * g_lMapDlgCharX) + 8) >> 12))  // divide by 4096
#define mConvertMapDlgToCharY( a )  \
   ((zSHORT) ((((zLONG) (a) * g_lMapDlgCharY) + 32) >> 13)) // divide by 8192
#define mConvertCharXToMapDlg( a )  \
   ((zSHORT) ((((zLONG) (a) << 12)) / g_lMapDlgCharX))    // multiply by 4096
#define mConvertCharYToMapDlg( a )  \
   ((zSHORT) ((((zLONG) (a) << 13)) / g_lMapDlgCharY))    // multiply by 8192

#define mConvertDlgUnitToCharX( a )  \
   ((zSHORT) ((((zLONG) (a) * g_lDlgUnitCharX) + 8) >> 4))    // divide by 16
#define mConvertDlgUnitToCharY( a )  \
   ((zSHORT) ((((zLONG) (a) * g_lDlgUnitCharY) + 32) >> 6))   // divide by 64
#define mConvertCharXToDlgUnit( a )  \
   ((zSHORT) ((((zLONG) (a) << 4)) / g_lDlgUnitCharX))      // multiply by 16
#define mConvertCharYToDlgUnit( a )  \
   ((zSHORT) ((((zLONG) (a) << 6)) / g_lDlgUnitCharY))      // multiply by 64

#define mConvertDlgUnitToPixelX( a ) \
   ((zSHORT) (((zLONG) (a) * g_lDlgUnitCharX) >> 2))           // divide by 4
#define mConvertDlgUnitToPixelY( a ) \
   ((zSHORT) (((zLONG) (a) * g_lDlgUnitCharY) >> 3))           // divide by 8
#define mConvertPixelToDlgUnitX( a ) ((zSHORT) ((((zLONG) (a) << 2) + \
   (g_lDlgUnitCharX >> 1)) / g_lDlgUnitCharX))               // multiply by 4
#define mConvertPixelToDlgUnitY( a ) ((zSHORT) ((((zLONG) (a) << 3) + \
   (g_lDlgUnitCharY >> 1)) / g_lDlgUnitCharY))               // multiply by 8

#define mConvert16thInchToPixelX( sixteenths ) \
   (((sixteenths) * g_lPixelsPerInchX) >> 4)                  // divide by 16
#define mConvert16thInchToPixelY( sixteenths ) \
   (((sixteenths) * g_lPixelsPerInchY) >> 4)                  // divide by 16

// Rounded to nearest 16th.
#define mConvertPixelTo16thInchX( a ) ((((a) << 4) + \
   (g_lPixelsPerInchX >> 1)) / g_lPixelsPerInchX)           // multiply by 16
#define mConvertPixelTo16thInchY( a ) ((((a) << 4) + \
   (g_lPixelsPerInchY >> 1)) / g_lPixelsPerInchY)           // multiply by 16

// Rounded to nearest pixel.
#define mConvert256thInchToPixelX( n256ths ) \
   ((((n256ths) * g_lPixelsPerInchX) + 127) >> 8)            // divide by 256
#define mConvert256thInchToPixelY( n256ths ) \
   ((((n256ths) * g_lPixelsPerInchY) + 127) >> 8)            // divide by 256

// Rounded to nearest 256th.
#define mConvertPixelTo256thInchX( a ) ((((a) << 8) + \
   (g_lPixelsPerInchX >> 1)) / g_lPixelsPerInchX)          // multiply by 256
#define mConvertPixelTo256thInchY( a ) ((((a) << 8) + \
   (g_lPixelsPerInchY >> 1)) / g_lPixelsPerInchY)          // multiply by 256

// Rounded to nearest pixel.
#define mConvertTwipsToPixelX( nTwips ) \
   ((((nTwips) * g_lPixelsPerInchX) + 719) / 1440)          // divide by 1440
#define mConvertTwipsToPixelY( nTwips ) \
   ((((nTwips) * g_lPixelsPerInchY) + 719) / 1440)          // divide by 1440

// Rounded to nearest Twip.
#define mConvertPixelToTwipsX( a ) ((((a) * 1440) + \
   (g_lPixelsPerInchX >> 1)) / g_lPixelsPerInchX)         // multiply by 1440
#define mConvertPixelToTwipsY( a ) ((((a) * 1440) + \
   (g_lPixelsPerInchY >> 1)) / g_lPixelsPerInchY)         // multiply by 1440

#if 0
#define mConvertInchToPixelX( inches, sixteenths ) \
      ( ((inches) * g_lPixelsPerInchX) + \                     // full inches
        ((sixteenths) * g_lPixelsPerInchX) >> 4 )             // divide by 16
#define mConvertInchToPixelY( inches, sixteenths ) \
      ( ((inches) * g_lPixelsPerInchY) + \                     // full inches
        ((sixteenths) * g_lPixelsPerInchY) >> 4 )             // divide by 16
#define mConvertPixelTo16thInchX( a )  \
      ( (short)((((long)(a)) << 4) / g_lPixelsPerInchX) )   // multiply by 16
#define mConvertPixelTo16thInchY( a )  \
      ( (short)((((long)(a)) << 4) / g_lPixelsPerInchY) )   // multiply by 16
#endif

// Release and initialize COM Interfaces.
#define mReleaseInit( p ) { if ( p ) { p->Release(); p = 0; } }

// Delete and initialize memory.
#define mDeleteInit( p ) { if ( p ) { delete( p ); p = 0; } }
#define mDeleteInitA( p ) { if ( p ) { delete [] p; p = 0; } }

#define mDropOI_Init( v ) { if ( v ) { DropObjectInstance( v ); v = 0; } }

#define mIs_hWnd( w ) ((w) && ::IsWindow( w ))
#define mIs_hWndEnabled( w ) ((w) && ::IsWindowEnabled( w ))
#define mIs_hWndVisible( w ) ((w) && ::IsWindowVisible( w ))
#define mIsSHIFT_Pressed( ) ((GetKeyState( VK_SHIFT ) & (1 << (sizeof( SHORT ) * 8 - 1))) != 0)
#define mIsCTRL_Pressed( ) ((GetKeyState( VK_CONTROL ) & (1 << (sizeof( SHORT ) * 8 - 1))) != 0)


// determine number of elements in an array (not bytes)
#define mElementCnt( Array ) (sizeof( Array ) / sizeof( Array[ 0 ] ))

typedef zSHORT (POPERATION zFARPROC_PRINT)( zVIEW, zLONG, zLONG, zLONG );
typedef zSHORT (POPERATION zFARPROC_DRIVER)( zVIEW );
typedef zLONG (POPERATION zFARPROC_INTERP)( zVIEW, zVIEW,
                                            zCPCHAR, zCPCHAR, zPLONG );
typedef HINSTANCE (POPERATION zFARPROC_HINSTANCE)( zVIEW );
typedef zLONG (POPERATION zFARPROC_PAINTER)( zVIEW, zVIEW, zVIEW, zVIEW,
                                             zPVOID, zLONG, zPVOID, zLONG );

zOPER_EXPORT zLONG OPERATION
CallPainterForSelectedControls( zVIEW vSubtask, zCPCHAR cpcDLL,
                                zCPCHAR cpcOperation, zVIEW vDialogReport,
                                zVIEW vExtra, zLONG lType,
                                zPVOID pvData, zLONG lFlags );
zOPER_EXPORT zLONG OPERATION
ShowInplaceControlOverCtrl( zVIEW   vSubtask,
                            zVIEW   vControl,
                            zPVOID  pCtrl,
                            zCPCHAR cpcInplaceTag );
zOPER_EXPORT zSHORT OPERATION
GetNextCtrlAtPoint( zVIEW vSubtask, zSHORT nPos,
                    zPCHAR pchCurrentCtrl, zLONG lFlag );

zOPER_EXPORT zVIEW OPERATION
ZeidonMain( zVIEW   vSubtask,
            HWND    hWndParent,
            zCPCHAR cpcDialogName,
            zCPCHAR cpcWindowName );

zOPER_EXPORT HINSTANCE OPERATION
GetDLL_Instance( zVIEW vSubtask );

zOPER_EXPORT zLONG OPERATION
GenerateRandomStudentId( zPCHAR  pchReturnStudentId,
                         zLONG   lMaxLth,
                         zCPCHAR cpcIpAddress,
                         zLONG   lPort );
zOPER_EXPORT zLONG OPERATION
WindowsShellExecute( zVIEW vSubtask,
                     zPCHAR szFileOrExeName,
                     zPCHAR szFileOpenCommand,
                     zPCHAR szExeParams );

zOPER_EXPORT zLONG OPERATION
GetApplicationInstance( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
GetWindowHandle( zPULONG pWindowReturn,
                 zPULONG pCtrlReturn,
                 zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
GetWindowName( zVIEW  vSubtask,
               zPCHAR pchDlgTag,
               zPCHAR pchWndTag );
zOPER_EXPORT zSHORT OPERATION
GetParentWindow( zPVIEW pParentSubtask,
                 zVIEW  vSubtask );
zOPER_EXPORT zSHORT OPERATION
GetParentWindowName( zVIEW  vSubtask,
                     zPCHAR pchDlgTag,
                     zPCHAR pchWndTag );
zOPER_EXPORT zBOOL OPERATION
GetAppOrWorkstationValue( zVIEW    vSubtask,
                          zCPCHAR  cpcKey,
                          zPCHAR   pchReturnString,
                          zSHORT   nReturnStringLth );
zOPER_EXPORT void OPERATION
GetWorkstationAppValue( zVIEW    vSubtask,
                        zPCHAR   cpcSection,
                        zCPCHAR  cpcKey,
                        zPCHAR   pchReturnString,
                        zSHORT   nReturnStringLth );
zOPER_EXPORT zSHORT OPERATION
GetWorkstationApplicationValues( zVIEW     vSubtask,
                                 zCPCHAR   cpcValueName,
                                 zPCHAR    pchReturnString,
                                 zSHORT    nReturnStringLth,
                                 zPLONG    plVal1,
                                 zPLONG    plVal2,
                                 zPLONG    plVal3,
                                 zPLONG    plVal4,
                                 zPLONG    plVal5,
                                 zPLONG    plVal6,
                                 zPLONG    plVal7,
                                 zPLONG    plVal8,
                                 zPLONG    plVal9,
                                 zPLONG    plVal10 );
zOPER_EXPORT zSHORT OPERATION
SetWindowCaptionTitle( zVIEW   vSubtask,
                       zCPCHAR cpcCaption,
                       zCPCHAR cpcTitle );
zOPER_EXPORT zPVOID OPERATION
GetOperationDynamicCallAddress( zVIEW    vSubtask,
                                LPLPLIBRARY hLibrary,
                                zCPCHAR  cpcDLL_Name,
                                zCPCHAR  cpcOperationName,
                                zCPCHAR  cpcErrorMessagePrefix );
zOPER_EXPORT zSHORT OPERATION
ActivateWindow( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
PutWindowOnTop( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
BuildWindowImmediate( zVIEW  vSubtask,
                      zVIEW  vDialog,
                      zSHORT nWindowBehavior );
zOPER_EXPORT zSHORT OPERATION
MapWindow( zVIEW vSubtask );

// Re-map (from OI to window) all controls within this window
zOPER_EXPORT zSHORT OPERATION
RefreshWindow( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
RefreshWindowExceptForCtrl( zVIEW vSubtask,
                            zCPCHAR cpcCtrlTag );
zOPER_EXPORT zLONG  OPERATION
SplitFrame( zVIEW   vSubtask,
            zCPCHAR cpcSplitTag,
            zSHORT  nPercentX,
            zSHORT  nPercentY,
            zLONG   lFlag );
zOPER_EXPORT zVIEW  OPERATION
AttachSubtaskToPane( zVIEW   vSubtask,
                     zCPCHAR cpcSplitTag,
                     zCPCHAR cpcDlgTag,
                     zCPCHAR cpcWndTag,
                     zLONG   lPane );
zOPER_EXPORT zVIEW  OPERATION
HideGlobalView( zVIEW   vSubtask,
                zCPCHAR cpcDlgTag,
                zCPCHAR cpcWndTag );
zOPER_EXPORT zSHORT OPERATION
SetCtrlError( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag,
              zCPCHAR cpcMsgText );
zOPER_EXPORT zSHORT OPERATION
MapCtrl( zVIEW   vSubtask,
         zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
ValidateMapCtrl( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
RefreshCtrl( zVIEW    vSubtask,
             zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
RefreshVisibleItems( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
HiliteListBoxItem( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zSHORT  bHilite,
                   zLONG   lType );
zOPER_EXPORT zSHORT OPERATION
PlaceWindow( zVIEW   vSubtask,
             zLONG   lPosition );
zOPER_EXPORT zSHORT OPERATION
ResetWindowPlacement( zVIEW   vSubtask,
                      zCPCHAR cpcToDlgTag,
                      zCPCHAR cpcToWndTag,
                      zCPCHAR cpcFromDlgTag,
                      zCPCHAR cpcFromWndTag );
#ifdef __cplusplus
zOPER_EXPORT zSHORT OPERATION
SetRemoteWndAttribute( zVIEW   vSubtask,
                       zCPCHAR cpcAttribute,
                       zCPCHAR cpcValue,
                       zBOOL   bLock = FALSE );
#else
zOPER_EXPORT zSHORT OPERATION
SetRemoteWndAttribute( zVIEW   vSubtask,
                       zCPCHAR cpcAttribute,
                       zCPCHAR cpcValue,
                       zBOOL   bLock );
#endif
zOPER_EXPORT zSHORT OPERATION
SetRemoteCtrlAttribute( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zCPCHAR cpcEntity,
                        zCPCHAR cpcAttribute,
                        zCPCHAR cpcValue );
zOPER_EXPORT zSHORT OPERATION
GetCtrlText( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             zPCHAR pchText,
             zUSHORT uLth );
zOPER_EXPORT zSHORT OPERATION
SetCtrlText( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             zCPCHAR cpcText );
zOPER_EXPORT zSHORT OPERATION
SetCtrlTextLth( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zUSHORT uTextLth );
zOPER_EXPORT zSHORT OPERATION
SetCtrlRowColText( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zLONG   lRow,
                   zLONG   lColumn,
                   zCPCHAR cpcText );
zOPER_EXPORT zSHORT OPERATION
GetCtrlRowColText( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zLONG   lRow,
                   zLONG   lColumn,
                   zPCHAR  pchText,
                   zUSHORT uLth );
zOPER_EXPORT zSHORT OPERATION
TranslateCtrlValue( zVIEW   vSubtask,
                    zCPCHAR cpcCtrlTag,
                    zSHORT  nColumn,
                    zSHORT  bToDisplay,
                    zPCHAR  pchValue,
                    zUSHORT uLth );
zOPER_EXPORT zLONG OPERATION
GetCtrlID( zVIEW    vSubtask,
           zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
SetCtrlPosition( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lX,
                 zLONG   lY,
                 zSHORT  bDlgUnits );
zOPER_EXPORT zSHORT OPERATION
SetCtrlSize( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             zLONG   lCX,
             zLONG   lCY,
             zSHORT  bDlgUnits );
zOPER_EXPORT zSHORT OPERATION
GetCtrlPosition( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zPLONG plX,
                 zPLONG plY,
                 zSHORT  bDlgUnits );
zOPER_EXPORT zSHORT OPERATION
RefreshParentSubwindows( zVIEW  vSubtask,
                         zBOOL  bRefreshParent );
zOPER_EXPORT zSHORT OPERATION
RefreshAllSubwindows( zVIEW  vSubtask );

zOPER_EXPORT zSHORT OPERATION
GetCtrlSize( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             zPLONG plCX,
             zPLONG plCY,
             zSHORT  bDlgUnits );
zOPER_EXPORT zSHORT OPERATION
SetDrawMenuBar( zVIEW  vSubtask,
                zSHORT bSetRedraw );
zOPER_EXPORT zSHORT OPERATION
GetLastPopupMenu( zVIEW  vSubtask,
                  zPCHAR pchReturnPopupTag );
zOPER_EXPORT zSHORT OPERATION
GetLastCommandTag( zVIEW  vSubtask,
                   zPCHAR pchReturnTag );
zOPER_EXPORT zSHORT OPERATION
GetLastCtrlTag( zVIEW  vSubtask,
                zPCHAR pchReturnTag );
zOPER_EXPORT zSHORT OPERATION
ReplacePrimaryMenu( zVIEW   vSubtask,
                    zCPCHAR cpcMenuTag );
zOPER_EXPORT zSHORT OPERATION
AddOptionToMenu( zVIEW   vSubtask,
                 zCPCHAR cpcParentTag,
                 zCPCHAR cpcSiblingTag,
                 zCPCHAR cpcOptionTag,
                 zCPCHAR cpcOptionText,
                 zCPCHAR cpcActionTag,
                 zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
RemoveOptionFromMenu( zVIEW   vSubtask,
                      zCPCHAR cpcOptionTag );
zOPER_EXPORT zSHORT OPERATION
AddOptionToPopupMenu( zVIEW   vSubtask,
                      zCPCHAR cpcParentTag,
                      zCPCHAR cpcSiblingTag,
                      zCPCHAR cpcOptionTag,
                      zCPCHAR cpcOptionText,
                      zCPCHAR cpcActionTag,
                      zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
RemoveOptionFromPopupMenu( zVIEW   vSubtask,
                           zCPCHAR cpcOptionTag );
zOPER_EXPORT zSHORT OPERATION
GetSubtaskForWindowName( zVIEW    vSubtask,  // current subtask within task
                         zVIEW    *pvSubtaskReturn,
                         zCPCHAR  cpcWindowName );
zOPER_EXPORT zVIEW OPERATION
FindDialogWindow( zVIEW    vSubtask,
                  zCPCHAR  cpcDlgTag,
                  zCPCHAR  cpcWndTag );
zOPER_EXPORT zSHORT OPERATION
GetCurrentState( zVIEW  vSubtask,
                 zPCHAR pchDlgTag,
                 zPCHAR pchWndTag,
                 zPCHAR pchOperation );
zOPER_EXPORT zLONG OPERATION
GetWindowState( zVIEW   vSubtask,      // Enable, Visible, Check
                zLONG   lStatusType );
zOPER_EXPORT zSHORT OPERATION
GetDlgWndCtrlNames( zVIEW   vSubtask,
                    zPCHAR pchDlgName,
                    zPCHAR pchWndName,
                    zPCHAR pchCtrlName );
zOPER_EXPORT zLONG OPERATION
SetWindowState( zVIEW   vSubtask,
                zLONG   lStatusType,
                zULONG  ulValue );
zOPER_EXPORT zLONG OPERATION
GetCtrlState( zVIEW   vSubtask,        // Enable, Visible, Check
              zCPCHAR cpcCtrlTag,
              zLONG   lStatusType );
zOPER_EXPORT zLONG OPERATION
SetCtrlState( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag,
              zLONG   lStatusType,
              zULONG  ulValue );
zOPER_EXPORT zLONG OPERATION
GetOptionState( zVIEW   vSubtask,      // Enable, Visible, Check
                zCPCHAR cpcOptionTag,
                zLONG   lStatusType );
zOPER_EXPORT zLONG OPERATION
SetOptionState( zVIEW   vSubtask,
                zCPCHAR cpcOptionTag,
                zLONG   lOptionType,
                zULONG  ulValue );
zOPER_EXPORT zLONG OPERATION
GetPopupOptionState( zVIEW   vSubtask,      // Enable, Visible, Check
                     zCPCHAR cpcOptionTag,
                     zLONG   lStatusType );
zOPER_EXPORT zLONG OPERATION
SetPopupOptionState( zVIEW   vSubtask,
                     zCPCHAR cpcOptionTag,
                     zLONG   lOptionType,
                     zULONG  ulValue );
zOPER_EXPORT zLONG OPERATION
GetCtrlProperty( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lPropertyType,
                 zPULONG pulNumericProperty,
                 zPCHAR  pchStringProperty,
                 zLONG   lMaxLth );
zOPER_EXPORT zLONG OPERATION
SetCtrlProperty( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lPropertyType,
                 zULONG  ulNumericProperty,
                 zCPCHAR cpcStringProperty );
zOPER_EXPORT zSHORT OPERATION
SetFocusToCtrl( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
SetFocusToNextCtrl( zVIEW  vSubtask,
                    zPCHAR pchReturnCtrlTag );
zOPER_EXPORT zSHORT OPERATION
FindCtrlForFocus( zVIEW  vSubtask,
                  zPCHAR pchReturnCtrlTag,
                  zSHORT bBackward,
                  zSHORT bSetFocus );
zOPER_EXPORT zSHORT OPERATION
GetCtrlWithFocus( zVIEW  vSubtask,
                  zPCHAR pchReturnCtrlTag );
zOPER_EXPORT zSHORT OPERATION
SetCtrlFontTag( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zCPCHAR cpcFontTag );
zOPER_EXPORT zSHORT OPERATION
SetCtrlFontBold( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zSHORT  bBold );
zOPER_EXPORT zSHORT OPERATION
SetCtrlFontItalic( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zSHORT  bItalic );
zOPER_EXPORT zSHORT OPERATION
SetCtrlFontOverstrike( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zSHORT  bOverstrike );
zOPER_EXPORT zSHORT OPERATION
SetCtrlFontUnderline( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zSHORT  bUnderline );
zOPER_EXPORT zSHORT OPERATION
SetCtrlFontSize( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zSHORT  nFontSize );
zOPER_EXPORT zSHORT OPERATION
SetCtrlBorder( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zCPCHAR cpcText );
zOPER_EXPORT zSHORT OPERATION
SetCtrlMousePointer( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zUSHORT uPointerID );

zOPER_EXPORT zSHORT OPERATION
TerminateActionForError( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
InvokeAction( zVIEW   vSubtask,
              zCPCHAR cpcActionTag );
zOPER_EXPORT zSHORT OPERATION
SwitchToAction( zVIEW   vSubtask,
                zCPCHAR cpcNewAction );
zOPER_EXPORT zSHORT OPERATION
SetWindowActionBehavior( zVIEW   vSubtask,
                         zLONG   lWindowBehavior,
                         zCPCHAR cpcDlgTag,
                         zCPCHAR cpcWndTag );
zOPER_EXPORT zSHORT OPERATION
InvokeWindowActionBehavior( zVIEW   vSubtask,
                            zLONG   lWindowBehavior,
                            zCPCHAR cpcDlgTag,
                            zCPCHAR cpcWndTag );
zOPER_EXPORT zSHORT OPERATION
EnableAction( zVIEW   vSubtask,
              zCPCHAR cpcActionName,
              zSHORT  bEnable );
zOPER_EXPORT zUSHORT OPERATION
StartTask( zVIEW   vSubtask,
           zCPCHAR cpcCmdLine,
           zUSHORT uCmdShow );
zOPER_EXPORT zSHORT OPERATION
SetNewApplicationSubtask( zVIEW vSubtask,
                          zVIEW vAppSubtask );
zOPER_EXPORT zSHORT OPERATION
GetWebRedirection( zVIEW   vSubtask,
                   zLONG   lWindowBehavior,
                   zPCHAR  pchDlgTag,
                   zPCHAR  pchWndTag );
zOPER_EXPORT zSHORT OPERATION
SetWebRedirection( zVIEW   vSubtask,
                   zLONG   lWindowBehavior,
                   zCPCHAR cpcDlgTag,
                   zCPCHAR cpcWndTag );

zOPER_EXPORT zSHORT OPERATION
CreateTrackingPopupMenu( zVIEW   vSubtask,
                         zCPCHAR cpcPopupTag,
                         zLONG   lXCoord,
                         zLONG   lYCoord,
                         zSHORT  bClientCoords,
                         zSHORT  bDlgUnits );
zOPER_EXPORT HWND OPERATION
GetMDI_Client( zVIEW vSubtask );
zOPER_EXPORT HWND OPERATION
CreateMDI_Child( zVIEW   vSubtask,
                 zCPCHAR cpcTitle );
zOPER_EXPORT HWND OPERATION
GetLastMDI_Child( zVIEW vSubtask );

#if 0
zOPER_EXPORT zSHORT OPERATION
GetCtrlFont( zVIEW    vSubtask,
             zCPCHAR  cpcCtrlTag,
             PCHARSET pFont );

zOPER_EXPORT zSHORT OPERATION
SetCtrlParent( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               PGUIOBJ pParent );
zOPER_EXPORT zSHORT OPERATION
SetCtrlOwner( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag,
              PGUIOBJ pOwner );
#endif

zOPER_EXPORT zSHORT OPERATION
SetClipboardBlob( zPVOID pvData, zLONG lDataLth, zCPCHAR cpcFormat );
zOPER_EXPORT zSHORT OPERATION
GetClipboardBlob( zPVOID pvData, zLONG lDataLth, zCPCHAR cpcFormat );

zOPER_EXPORT zLONG OPERATION
SetRGB( zSHORT nRed, zSHORT nGreen, zSHORT nBlue );

zOPER_EXPORT zSHORT OPERATION
InitInterpretor( zVIEW vSubtask,
                 zVIEW vInterpIn,
                 zFARPROC_INTERP lpfnInterpIn );
zOPER_EXPORT zSHORT OPERATION
ResumeFromDebugger( zVIEW   vDebuggerSubtask,
                    zCPCHAR cpcDebuggerAction,
                    zVIEW   vAppSubtask );
zOPER_EXPORT zSHORT OPERATION
ResumeFromPainter( zVIEW   vPainterSubtask,
                   zCPCHAR cpcPainterAction,
                   zVIEW   vAppSubtask );
zOPER_EXPORT zSHORT OPERATION
CreateWindowSubtask( zVIEW   *pvSubtask,
                     zVIEW   vSubtask,
                     zVIEW   vNewSubtask,
                     zCPCHAR cpcDlgTag,
                     zCPCHAR cpcAppName );

zOPER_EXPORT zSHORT OPERATION
CreateRemoteWindowSubtask( zVIEW   *pvSubtask,
                           zVIEW   vSubtask,
                           zCPCHAR cpcDlgTag,
                           zCPCHAR cpcWndTag );

zOPER_EXPORT zPVOID OPERATION
GetActionParameters( zVIEW  vSubtask );
zOPER_EXPORT zSHORT OPERATION
GetActionName( zVIEW  vSubtask,
               zPCHAR pchActionName );
zOPER_EXPORT zPCHAR OPERATION
GetActionString( zLONG lAction );
zOPER_EXPORT zSHORT OPERATION
SetActionTrace( zVIEW vSubtask, zSHORT nOn );
zOPER_EXPORT zSHORT OPERATION
OperatorSend( zVIEW   vSubtask,
              zCPCHAR cpcTitle,
              zCPCHAR cpcMsgText,
              zSHORT  bBeep );
zOPER_EXPORT zSHORT OPERATION
OperatorConversationalDialog( zVIEW   vSubtask,
                              zPCHAR  pReturnCtrlTag,
                              zCPCHAR cpcDialogName,
                              zCPCHAR cpcWindowName );
zOPER_EXPORT zSHORT OPERATION
OperatorPromptForInput( zVIEW   vSubtask,
                        zCPCHAR cpcTitle,
                        zCPCHAR cpcMsgText,
                        zSHORT  bBeep,
                        zPCHAR lpchReturnBuffer,
                        zUSHORT uBufferLth );
zOPER_EXPORT zSHORT OPERATION
OperatorPrompt( zVIEW   vSubtask,
                zCPCHAR cpcTitle,
                zCPCHAR cpcMsgText,
                zSHORT  bBeep,
                zSHORT  nButtons,
                zSHORT  nDefaultButton,
                zSHORT  nIcon );
zOPER_EXPORT zSHORT OPERATION
OperatorPromptForColor( zVIEW  vSubtask,
                        zPLONG lpColorRef,
                        zPLONG lpaCustColorRef,
                        zSHORT bUpdate );
zOPER_EXPORT zSHORT OPERATION
OperatorPromptForFont( zVIEW  vSubtask,
                       zPVOID lpLogFont,
                       zPLONG lplPointSize,
                       zPLONG lpColorRef,
                       zSHORT bUpdate );
zOPER_EXPORT zSHORT OPERATION
OperatorPromptForFile( zVIEW  vSubtask,
                       zPCHAR pchFileName,
                       zSHORT nFileNameLth,
                       zCPCHAR pchFilter,
                       zCPCHAR pchDefaultExtension,
                       zULONG ulZFlags );
zOPER_EXPORT zSHORT OPERATION
OperatorPromptFindReplace( zVIEW    vSubtask,
                           zPCHAR   pchFindWhat,
                           zPCHAR   pchReplaceWith,
                           zSHORT   bReplace );
zOPER_EXPORT zSHORT OPERATION
ConstructZeidonPrompt( zVIEW    vSubtask,
                       zCPCHAR  cpcTitle,
                       zCPCHAR  cpcPrompt,
                       zPCHAR   pchReturnBuffer,
                       zSHORT   nBufferLth,
                       zPLONG   plFlags,
                       zCPCHAR  cpcCtrlText,
                       zSHORT   chPassword,
                       zLONG    lResId );

#if 0
zSHORT
SetMessageQueueTaskStatus( zVIEW vSubtask,
                           zLONG lStatus );

zSHORT
SetMessageStatusFromTask( zVIEW vSubtask );
#endif

zOPER_EXPORT zSHORT OPERATION
GetLastDlgWnd( zVIEW vSubtask, zPCHAR pchDlgTag, zPCHAR pchWndTag );

zOPER_EXPORT zBOOL OPERATION
PumpMessages( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
GetPressedState( zLONG  lVirtualKey,
                 zSHORT bAsync );
zOPER_EXPORT zSHORT OPERATION
IsKeyQueued( zVIEW   vSubtask,
             zUSHORT uVirtualKey,
             zLONG   bAsync );
zOPER_EXPORT zSHORT OPERATION
IsDoubleClick( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag );
zOPER_EXPORT zBOOL OPERATION
IsNT( );
zOPER_EXPORT zBOOL OPERATION
IsRemoteServer( );
zOPER_EXPORT zSHORT OPERATION
DetermineSystemVersion( zPLONG plMajorVersion,
                        zPLONG plMinorVersion,
                        zPCHAR pchVersion,
                        zLONG  lMaxLth );
zOPER_EXPORT zSHORT OPERATION
DetermineRegKeyValue( zLONG   lKey,
                      zCPCHAR cpcSubKey,
                      zPCHAR  pchReturnValue,
                      zULONG  ulReturnValueLth );

zOPER_EXPORT zLONG  OPERATION
ActiveDirectoryLoginAuthentication( zCPCHAR cpcPathName,
                                    zCPCHAR cpcUserName,
                                    zCPCHAR cpcPassword );

zOPER_EXPORT zLONG  OPERATION
ActiveDirectoryGetProperty( zCPCHAR cpcPathName,
                            zCPCHAR cpcUserName,
                            zCPCHAR cpcPassword,
                            zCPCHAR cpcPropertyName,
                         zPCHAR  pchReturnString );

zOPER_EXPORT zLONG  OPERATION
ActiveDirectorySetProperty( zCPCHAR cpcPathName,
                         zCPCHAR cpcAdminUserName,
                            zCPCHAR cpcAdminUserPassword,
                            zCPCHAR cpcUserName,
                         zCPCHAR cpcPropertyName,
                         zCPCHAR cpcPropertyValue);

zOPER_EXPORT zLONG  OPERATION
ActiveDirectoryAddUser( zCPCHAR cpcPathName, zCPCHAR cpcLoginUserName,
                        zCPCHAR cpcLoginPassword, zCPCHAR cpcNewUserName, zCPCHAR cpcPassword );

zOPER_EXPORT zLONG  OPERATION
ActiveDirectorySetPassword( zCPCHAR cpcPathName, zCPCHAR cpcAdminUserName,
                            zCPCHAR cpcAdminUserPassword, zCPCHAR cpcUserName, zCPCHAR cpcPassword );

zOPER_EXPORT zLONG  OPERATION
ActiveDirectoryChangePassword( zCPCHAR cpcPathName, zCPCHAR cpcAdminUserName, zCPCHAR cpcAdminPassword,
                               zCPCHAR cpcUserName, zCPCHAR cpcOldPassword, zCPCHAR cpcPassword );

zOPER_EXPORT zLONG  OPERATION
ActiveDirectoryRemoveUser( zCPCHAR cpcServerName, zCPCHAR cpcServerPort,
                           zCPCHAR cpcOrganization, zCPCHAR cpcUserName );

#define StartEmailClientL( cpcEmailAddress, cpcSubject, cpcCopyTo,\
                           cpcBlindCopy, cpcBody, cpcAttachment,\
                           cpcEmailClient, lFlags )\
        StartEmailClient( (zCPCHAR) cpcEmailAddress, cpcSubject, cpcCopyTo,\
                           cpcBlindCopy, cpcBody, cpcAttachment,\
                           cpcEmailClient, lFlags )\

zOPER_EXPORT zULONG OPERATION
StartEmailClient( zCPCHAR cpcEmailAddress,  // comma separated list
                  zCPCHAR cpcSubject,
                  zCPCHAR cpcCopyTo,        // comma separated list
                  zCPCHAR cpcBlindCopy,     // comma separated list
                  zCPCHAR cpcBody,
                  zCPCHAR cpcAttachment,
                  zCPCHAR cpcEmailClient,
                  zLONG   lFlags );         // reserved
zOPER_EXPORT void OPERATION
TranslateEmail( zPCHAR pchTgt, zCPCHAR cpcSrc );
zOPER_EXPORT zBOOL OPERATION
GenerateUniqueFileName( zPCHAR  pchReturnFileName,
                        zSHORT  nMaxNameLth,
                        zCPCHAR cpcPathName,
                        zCPCHAR cpcFileName,
                        zCPCHAR cpcExtension );
zOPER_EXPORT zBOOL OPERATION
GenerateUniqueFileNameForWEB( zVIEW   vSubtask,
                              zPCHAR  pchReturnFileName,
                              zSHORT  nMaxNameLth,
                              zCPCHAR cpcFileName,
                              zCPCHAR cpcExtension );
zOPER_EXPORT zSHORT OPERATION
StartBrowserWindowWithURL( zVIEW   vSubtask,
                           zPCHAR  pchReturnFileName,
                           zSHORT  nMaxNameLth,
                           zCPCHAR cpcURL,
                           zCPCHAR cpcFileName,
                           zULONG  ulControlFlag );
zOPER_EXPORT zLONG  OPERATION
PrintReportToCSV( zVIEW   vSubtask,
                  zVIEW   vSourceOI,
                  zCPCHAR cpcSubobjectEntityName,
                  zCPCHAR cpcReportDefName,
                  zPCHAR  pchReportName,
                  zLONG   lFlags );
zOPER_EXPORT zLONG  OPERATION
PrintTextToCSV( zVIEW   vSubtask,
                zCPCHAR cpcText,
                zLONG   lColumnCSV );
zOPER_EXPORT zLONG  OPERATION
GenerateReportToHTML( zVIEW   vSubtask,
                      zVIEW   vSourceOI,
                      zCPCHAR cpcSubobjectEntityName,
                      zCPCHAR cpcReportDefName,
                      zPCHAR  pchReportName,
                      zCPCHAR cpcCSS_FileName,
                      zLONG   lFlags );
zOPER_EXPORT zLONG  OPERATION
PrintReportToHTML( zVIEW   vSubtask,
                   zVIEW   vSourceOI,
                   zCPCHAR cpcSubobjectEntityName,
                   zCPCHAR cpcReportDefName,
                   zPCHAR  pchReportName,
                   zLONG   lFlags );
zOPER_EXPORT zSHORT OPERATION
PrintTextToHTML( zVIEW   vSubtask,
                 zVIEW   vAppOI,
                 zCPCHAR cpcText,
                 zCPCHAR cpcClass,
                 zLONG   nLeftX,
                 zLONG   nTopY,
                 zLONG   nRightX,
                 zLONG   nBottomY,
                 zLONG   lJustification,
                 zLONG   lBorderStyle,
                 zLONG   lBorderColor,
                 zLONG   lEscapement,
                 zLONG   lType );
zOPER_EXPORT zSHORT OPERATION
PrintLineToHTML( zVIEW   vSubtask,
                 zVIEW   vAppOI,
                 zLONG   lLeft256ths,
                 zLONG   lTop256ths,
                 zLONG   lRight256ths,
                 zLONG   lBottom256ths,
                 zLONG   nPenWidth,
                 zLONG   nPenType,
                 zLONG   lPenColor,
                 zSHORT  nLineStyle );
zOPER_EXPORT zSHORT OPERATION
PrintBitmapToHTML( zVIEW   vSubtask,
                   zVIEW   vAppOI,
                   zLONG   lLeft256ths,
                   zLONG   lTop256ths,
                   zLONG   lRight256ths,
                   zLONG   lBottom256ths,
                   zCPCHAR cpcBitmapCtrlBOI );
zOPER_EXPORT zLONG  OPERATION
PrintReportToCtrl( zVIEW   vSubtask,
                   zVIEW   vSourceOI,
                   zCPCHAR cpcSubobjectEntityName,
                   zCPCHAR cpcReportDefName,
                   zPCHAR  pchReportName,
                   zLONG   lFlags,
                   zCPCHAR cpcReportCtrlTag );
zOPER_EXPORT zSHORT OPERATION
PrintTextFile( zVIEW   vSubtask,
               zCPCHAR cpcTitle,
               zCPCHAR cpcFileName,
               zCPCHAR cpcFontFaceName,
               zLONG   lFontPointSize,
               zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
PrintTextBlob( zVIEW   vSubtask,
               zCPCHAR cpcTitle,
               zVIEW   vOI,
               zCPCHAR cpcEntityName,
               zCPCHAR cpcAttribName,
               zCPCHAR cpcFontFaceName,
               zLONG   lFontPointSize );
zOPER_EXPORT zSHORT OPERATION
AcquireTwainImage( zVIEW   vSubtask,
                   zCPCHAR cpcFileName,
                   zPCHAR  pchReturnFileName,
                   zSHORT  nMaxFileNameLth );
zOPER_EXPORT zSHORT OPERATION
CompressFile( zVIEW   vSubtask,
              zCPCHAR cpcSrcFileName,
              zCPCHAR cpcTgtFileName,
              zPCHAR  pchReturnFileName,
              zSHORT  nMaxFileNameLth,
              zBOOL   bCompress );
zOPER_EXPORT zSHORT OPERATION
HotkeyToPainter( zVIEW   vSubtask );
zOPER_EXPORT zSHORT OPERATION
StartPainterForApp( zVIEW vSubtask,
                    zVIEW vDialogReport,
                    zCPCHAR cpcDialogReport,
                    zLONG lFlags );
zOPER_EXPORT zSHORT OPERATION
AddHotkeysToGlobalHotkeys( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
CloseFrame( zVIEW  vSubtask );
zOPER_EXPORT zSHORT OPERATION
EnableAllSubwindows( zVIEW  vSubtask,
                     zSHORT bEnable );
zOPER_EXPORT zSHORT OPERATION
InvokeHelpWithContext( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zCPCHAR cpcHelpFile,
                       zCPCHAR cpcHelpContext,
                       zULONG  ulHelpContextNbr,
                       zUSHORT uHelpType );
zOPER_EXPORT zSHORT OPERATION
PrintActiveWindow( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
PrintWnd( zVIEW   vSubtask,
             zCPCHAR cpcTitle );
zOPER_EXPORT zSHORT OPERATION
PrintCtrl( zVIEW   vSubtask,
           zCPCHAR cpcTitle,
           zCPCHAR cpcCtrlTag,
           zLONG   lFlags,
           zSHORT  nFontSize,
           zCPCHAR cpcFontFace );
zOPER_EXPORT zSHORT OPERATION
PrintCtrlPage( zVIEW  vSubtask,
               zLONG  lPageNbr,
               zLONG  lPageWidth,
               zLONG  lPageHeight );
zOPER_EXPORT zSHORT OPERATION
SetupPrinter( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
SetDefaultPrinterName( zPCHAR pchPrinterName );
zOPER_EXPORT zSHORT OPERATION
GetDefaultPrinterName( zPCHAR pchPrinterName, zPLONG plBufferSize );
zOPER_EXPORT zLONG  OPERATION
OpenRemoteReportFromClient( zVIEW   vSubtask,
                            zCPCHAR cpcSubobjectEntityName,
                            zCPCHAR cpcReportDefName,
                            zPCHAR  pchReportName,
                            zLONG   lFlags,
                            zCPCHAR cpcViewNameList );
zOPER_EXPORT zLONG  OPERATION
OpenReport( zVIEW   vSubtask,
            zCPCHAR cpcDLL_Name,
            zCPCHAR cpcPrintPageFunction,
            zLONG   lPrintFlags,
            zSHORT  bBanding,
            zSHORT  bScale,
            zLONG   bPrompt,
            zCPCHAR cpcReportDefName,
            zPCHAR  pchTitle );
zOPER_EXPORT zSHORT OPERATION
_zCall_PrintReportToPDF( zVIEW  vArgs,
                         zPVIEW pvViewList[] );
zOPER_EXPORT zLONG  OPERATION
GenerateReportToPDF( zVIEW   vSubtask,
                     zVIEW   vSourceOI,
                     zCPCHAR cpcSubobjectEntityName,
                     zCPCHAR cpcReportDefName,
                     zPCHAR  pchReportName,
                     zCPCHAR cpcCSS_FileName,
                     zLONG   lFlags );
zOPER_EXPORT zLONG  OPERATION
PrintReportToPDF( zVIEW   vSubtask,
                  zVIEW   vSourceOI,
                  zCPCHAR cpcSubobjectEntityName,
                  zCPCHAR cpcReportDefName,
                  zPCHAR  pchReportName,
                  zLONG   lFlags );
zOPER_EXPORT zSHORT OPERATION
CloseReport( zVIEW vSubtask, zLONG lFlags );
zOPER_EXPORT zSHORT OPERATION
CreateFontForReport( zVIEW   vSubtask,
                     zCPCHAR cpcFontTag,
                     zLONG   nSize,
                     zSHORT  bBold,
                     zSHORT  bItalic,
                     zSHORT  bUnderline,
                     zSHORT  bStrikeout,
                     zLONG   lTextColor,
                     zLONG   lTextBkColor,
                     zLONG   nEscapement,
                     zCPCHAR cpcFaceName );
zOPER_EXPORT zSHORT OPERATION
GetTextWidth( zVIEW   vSubtask,
              zCPCHAR cpcText );
zOPER_EXPORT zSHORT OPERATION
GetTextHeight( zVIEW   vSubtask,
               zCPCHAR cpcText );
zOPER_EXPORT zLONG OPERATION
HandlePageNumbering( zVIEW  vSubtask,
                     zPCHAR pchPageNumber,
                     zLONG  lEntityKey,
                     zLONG  lPageNbr,
                     zPLONG plTotalPages,
                     zLONG  lFlags );
zOPER_EXPORT zBOOL OPERATION
SetPhantomMode( zVIEW vSubtask,
                zBOOL bPhantom );
zOPER_EXPORT zBOOL OPERATION
GetPhantomMode( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
AddPagePosition( zVIEW   vSubtask,
                 zLONG   lPageNbr,
                 zVIEW   vSourceHierOI,
                 zVIEW   vReportDef,
                 zLONG   lPagePosition,
                 zLONG   lRC,
                 zLONG   lLevel,
                 zLONG   lFlags,
                 zLONG   lMultiLineTextPos,
                 zLONG   lContinuedGroupFlag,
                 zCPCHAR cpcEntityName,
                 zCPCHAR cpcRptGroupSetTag,
                 zCPCHAR cpcRptGroupTag );
zOPER_EXPORT zSHORT OPERATION
GetPagePosition( zVIEW   vSubtask,
                 zLONG   lPageNbr,
                 zVIEW   vSourceHierOI,
                 zVIEW   vReportDef,
                 zPLONG  plPagePosition,
                 zPLONG  plRC,
                 zPLONG  plLevel,
                 zPLONG  plFlags,
                 zPLONG  plMultiLineTextPos,
                 zPLONG  plContinuedGroupFlag,
                 zPCHAR  pchEntityName,
                 zPCHAR  cpcRptGroupSetTag,
                 zPCHAR  cpcRptGroupTag );
zOPER_EXPORT zSHORT OPERATION
SelectFontForReport( zVIEW   vSubtask,
                     zCPCHAR cpcFontTag );
zOPER_EXPORT zSHORT OPERATION
DrawTextToReport( zVIEW   vSubtask,
                  zVIEW   vAppOI,
                  zCPCHAR cpcText,
                  zLONG   nLeftX,
                  zLONG   nTopY,
                  zLONG   nRightX,
                  zLONG   nBottomY,
                  zLONG   lJustification,
                  zLONG   lBorderStyle,
                  zLONG   lBorderColor,
                  zLONG   lEscapement,
                  zLONG   lType );
zOPER_EXPORT zSHORT OPERATION
DrawMultiLineTextToReport( zVIEW   vSubtask,
                           zVIEW   vAppOI,
                           zCPCHAR cpcText,
                           zLONG   lMaxTextLth,
                           zLONG   nLeftX,
                           zLONG   nTopY,
                           zLONG   nRightX,
                           zLONG   nBottomY,
                           zLONG   lJustification,
                           zLONG   lBorderStyle,
                           zLONG   lBorderColor,
                           zLONG   lEscapement,
                           zLONG   lType,
                           zPLONG  pnNewBottomY,
                           zPLONG  pnNextWord );
zOPER_EXPORT zSHORT OPERATION
DrawLineToReport( zVIEW   vSubtask,
                  zVIEW   vAppOI,
                  zLONG   nPosX,
                  zLONG   nPosY,
                  zLONG   nEndX,
                  zLONG   nEndY,
                  zLONG   nPenWidth,
                  zLONG   nPenType,
                  zLONG   lPenColor,
                  zSHORT  nLineStyle );
zOPER_EXPORT zSHORT OPERATION
DrawRectangleToReport( zVIEW   vSubtask,
                       zVIEW   vAppOI,
                       zLONG   lPosX,
                       zLONG   lPosY,
                       zLONG   lWidth,
                       zLONG   lHeight,
                       zLONG   lPenWidth,
                       zLONG   lPenType,
                       zLONG   lPenColor,
                       zLONG   lRounded,
                       zLONG   lShapeColor );
zOPER_EXPORT zSHORT OPERATION
DrawEllipseToReport( zVIEW   vSubtask,
                     zVIEW   vAppOI,
                     zLONG   nPosX,
                     zLONG   nPosY,
                     zLONG   nWidth,
                     zLONG   nHeight,
                     zLONG   nPenWidth,
                     zLONG   nPenType,
                     zLONG   lPenColor,
                     zLONG   lShapeColor );
zOPER_EXPORT zSHORT OPERATION
DrawBitmapToReport( zVIEW   vSubtask,
                    zVIEW   vAppOI,
                    zLONG   nLeft,
                    zLONG   nTop,
                    zLONG   nRight,
                    zLONG   nBottom,
                    zCPCHAR cpcBitmapCtrlBOI );
zOPER_EXPORT zSHORT OPERATION
PushReportTabStops( zVIEW vSubtask, zSHORT nTabStops );
zOPER_EXPORT zSHORT OPERATION
PopReportTabStops( zVIEW vSubtask );
zOPER_EXPORT zLONG OPERATION
PushReportViewPort( zVIEW   vSubtask,
                    zCPCHAR cpcCurrentEntityName,
                    zLONG   lRepeatHorizontal,
                    zLONG   lRepeatHorizontalColumn,
                    zLONG   lRepeatHorizontalIndent,
                    zLONG   lRepeatHorizontalMargin,
                    zLONG   lRepeatHorizontalExtent,
                    zLONG   lRepeatHorizontalFlags,
                    zLONG   lViewPortBottomPrev,
                    zLONG   lViewPortTop,
                    zLONG   lViewPortLeft,
                    zLONG   lViewPortBottom,
                    zLONG   lViewPortRight );
zOPER_EXPORT zLONG OPERATION
PopReportViewPort( zVIEW   vSubtask,
                   zPCHAR  pchCurrentEntityName,
                   zPLONG  plRepeatHorizontal,
                   zPLONG  plRepeatHorizontalColumn,
                   zPLONG  plRepeatHorizontalIndent,
                   zPLONG  plRepeatHorizontalMargin,
                   zPLONG  plRepeatHorizontalExtent,
                   zPLONG  plRepeatHorizontalFlags,
                   zPLONG  plViewPortBottomPrev,
                   zPLONG  plViewPortTop,
                   zPLONG  plViewPortLeft,
                   zPLONG  plViewPortBottom,
                   zPLONG  plViewPortRight );

// Used in VML by Users
zOPER_EXPORT zSHORT OPERATION
GetCtrlPrintStatus( zVIEW    vSubtask,
                    zPCHAR   szGroupSet,
                    zPCHAR   szGroup,
                    zPCHAR   szControl );
zOPER_EXPORT zSHORT OPERATION
GetCtrlPrintText( zVIEW    vSubtask,
                  zPCHAR   szGroupSet,
                  zPCHAR   szGroup,
                  zPCHAR   szControl,
                  zPCHAR   szText,
                  zUSHORT  usLth );
zOPER_EXPORT zSHORT OPERATION
GetCtrlPrintPosition( zVIEW    vSubtask,
                      zPCHAR   szGroupSet,
                      zPCHAR   szGroup,
                      zPCHAR   szControl,
                      zPLONG   plPageNbr,
                      zPLONG   plPageX,
                      zPLONG   plPageY);
zOPER_EXPORT zSHORT OPERATION
GetPrintCurrentEntity( zVIEW   vSubtask,
                       zPCHAR  pchEntityName );
zOPER_EXPORT zLONG OPERATION
GetContinuedGroupFlag( zVIEW   vSubtask );
 // Used for VML in KZRPSRCO (the report generator)
zOPER_EXPORT zSHORT OPERATION
InvokeReportExitCode( zVIEW vSubtask,
                      zVIEW vReportDef,
                      zPCHAR sOperationName,
                      zSHORT nEvent,
                      zSHORT nCurrentPage,
                      zVIEW vDrivingOI );
zOPER_EXPORT zSHORT OPERATION
MakeViewFromInteger( zPVIEW vReturnedView,
                     zLONG lViewSavedAsInteger );
zOPER_EXPORT zLONG OPERATION
MakeIntegerFromView( zVIEW vAnyView );
zOPER_EXPORT zSHORT OPERATION
MakePointerFromInteger( zPCHAR *ppchReturnedPointer,
                        zLONG  lPointerSavedAsInteger );
zOPER_EXPORT zLONG OPERATION
MakeIntegerFromPointer( zPCHAR pchAnyPointer );

// AFX_CDECL is used for rare functions taking variable arguments
#ifndef AFX_CDECL
   #define AFX_CDECL __cdecl
#endif

zOPER_EXPORT zSHORT OPERATION
IsValidView( zVIEW vAny );

zOPER_EXPORT zSHORT OPERATION
SetCtrlMapping( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zCPCHAR cpcViewName,
                zCPCHAR cpcEntityName,
                zCPCHAR cpcAttributeName,
                zCPCHAR cpcContextName,
                zLONG   lColumn );
zOPER_EXPORT zSHORT OPERATION
GetCtrlMapping( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zPCHAR  pchViewName,
                zPCHAR  pchEntityName,
                zPCHAR  pchAttributeName,
                zPCHAR  pchContextName,
                zLONG   lColumn );
zOPER_EXPORT zSHORT OPERATION
SetCtrlTranslationList( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zCPCHAR cpcPairedList,
                        zSHORT  nCol );

zOPER_EXPORT void OPERATION
FindLinks( zVIEW vApp, zCPCHAR cpcEntity, zCPCHAR cpcAttribute );

zOPER_EXPORT zSHORT OPERATION
ParseHTML_TextToZeidonOI( zCPCHAR cpcHTML_Text,
                          zVIEW   vHTML_TgtView,
                          zCPCHAR cpcHTML_TgtDivEntity,
                          zCPCHAR cpcHTML_TgtDivAttribute,
                          zCPCHAR cpcHTML_TgtTagEntity,
                          zCPCHAR cpcHTML_TgtTagName,
                          zCPCHAR cpcHTML_TgtTagValue,
                          zCPCHAR cpcHTML_TgtTagLevel,
                          zCPCHAR cpcHTML_TgtTagYN,
                          zCPCHAR cpcHTML_TgtTagType,
                          zCPCHAR cpcHTML_TgtAttributeEntity,
                          zCPCHAR cpcHTML_TgtAttributeName,
                          zCPCHAR cpcHTML_TgtAttributeValue,
                          zCPCHAR cpcHTML_TgtTagDelimiter );

zOPER_EXPORT zSHORT OPERATION
ParseHTML_AttrToZeidonOI( zVIEW   vHTML_SrcView,
                          zCPCHAR cpcHTML_SrcEntity,
                          zCPCHAR cpcHTML_SrcAttribute,
                          zVIEW   vHTML_TgtView,
                          zCPCHAR cpcHTML_TgtDivEntity,
                          zCPCHAR cpcHTML_TgtDivAttribute,
                          zCPCHAR cpcHTML_TgtTagEntity,
                          zCPCHAR cpcHTML_TgtTagName,
                          zCPCHAR cpcHTML_TgtTagValue,
                          zCPCHAR cpcHTML_TgtTagLevel,
                          zCPCHAR cpcHTML_TgtTagYN,
                          zCPCHAR cpcHTML_TgtTagType,
                          zCPCHAR cpcHTML_TgtAttributeEntity,
                          zCPCHAR cpcHTML_TgtAttributeName,
                          zCPCHAR cpcHTML_TgtAttributeValue,
                          zCPCHAR cpcHTML_TgtTagDelimiter );

zOPER_EXPORT zSHORT OPERATION
ConstructHTML_TextFromZeidonOI( zPCHAR  pchHTML_Text,
                                zULONG  ulMaxLth,
                                zVIEW   vHTML_SrcView,
                                zCPCHAR cpcHTML_SrcDivEntity,
                                zCPCHAR cpcHTML_SrcDivAttribute,
                                zCPCHAR cpcHTML_SrcTagEntity,
                                zCPCHAR cpcHTML_SrcTagName,
                                zCPCHAR cpcHTML_SrcTagValue,
                                zCPCHAR cpcHTML_SrcTagLevel,
                                zCPCHAR cpcHTML_SrcTagYN,
                                zCPCHAR cpcHTML_SrcTagType,
                                zCPCHAR cpcHTML_SrcAttributeEntity,
                                zCPCHAR cpcHTML_SrcAttributeName,
                                zCPCHAR cpcHTML_SrcAttributeValue,
                                zCPCHAR cpcHTML_SrcAttributeDelimiter );
zOPER_EXPORT zSHORT OPERATION
ConstructHTML_AttrFromZeidonOI( zVIEW   vHTML_TgtView,
                                zCPCHAR cpcHTML_TgtEntity,
                                zCPCHAR cpcHTML_TgtAttribute,
                                zVIEW   vHTML_SrcView,
                                zCPCHAR cpcHTML_SrcDivEntity,
                                zCPCHAR cpcHTML_SrcDivAttribute,
                                zCPCHAR cpcHTML_SrcTagEntity,
                                zCPCHAR cpcHTML_SrcTagName,
                                zCPCHAR cpcHTML_SrcTagValue,
                                zCPCHAR cpcHTML_SrcTagLevel,
                                zCPCHAR cpcHTML_SrcTagYN,
                                zCPCHAR cpcHTML_SrcTagType,
                                zCPCHAR cpcHTML_SrcAttributeEntity,
                                zCPCHAR cpcHTML_SrcAttributeName,
                                zCPCHAR cpcHTML_SrcAttributeValue,
                                zCPCHAR cpcHTML_SrcAttributeDelimiter );

zOPER_EXPORT zSHORT OPERATION
RemoveFormattingFromHTML_Text( zVIEW   vTaskView,
                               zPCHAR  pchText,
                               zLONG   lMaxLth,
                               zCPCHAR cpcValidHTML_TagList );
zOPER_EXPORT zSHORT OPERATION
RemoveFormattingFromHTML_Attr( zVIEW   vHTML_SrcView,
                               zCPCHAR cpcHTML_SrcEntity,
                               zCPCHAR cpcHTML_SrcAttribute,
                               zCPCHAR cpcValidHTML_TagList );
zOPER_EXPORT zSHORT OPERATION
AddHTML_TagAttribute( zVIEW   vTaskView,
                      zPCHAR  pchHTML_Text,
                      zLONG   lMaxLth,
                      zCPCHAR cpcHTML_Tag,
                      zCPCHAR cpcHTML_AttributeName,
                      zCPCHAR cpcHTML_AttributeValue,
                      zCPCHAR cpcDelimiter,
                      zLONG   lFlags );
zOPER_EXPORT zSHORT OPERATION
RemoveTagFromHTML( zVIEW   vTaskView,
                   zPCHAR  pchReturnTag,
                   zPCHAR  pchHTML_Text,
                   zCPCHAR cpcTag );

zOPER_EXPORT zLONG OPERATION
CreateMemoryHandle( zLONG lInitialSize );
zOPER_EXPORT void OPERATION
DeleteMemoryHandle( zLONG hMemory );
zOPER_EXPORT zLONG  OPERATION
AddAttributeToMemory( zLONG    hMemory,
                      zVIEW    vApp,
                      zCPCHAR  cpcEntityName,
                      zCPCHAR  cpcAttributeName,
                      zLONG    lFlag );
zOPER_EXPORT zLONG  OPERATION
AddStringToMemory( zLONG    hMemory,
                   zCPCHAR  cpcString,
                   zLONG    lFlag );
zOPER_EXPORT zSHORT OPERATION
SetMemoryToAttribute( zLONG    hMemory,
                      zVIEW    vApp,
                      zCPCHAR  cpcEntityName,
                      zCPCHAR  cpcAttributeName );
zOPER_EXPORT void  OPERATION
ClearMemory( zLONG    hMemory );

zOPER_EXPORT zSHORT OPERATION
ImportCSV_ToZeidonOI( zVIEW vTgt,
                      zCPCHAR cpcCSV_FileName );
zOPER_EXPORT zSHORT OPERATION
BuildCSV_FromEntityAttribute( zVIEW   vTgt,
                              zCPCHAR cpcTgtEntity,
                              zCPCHAR cpcTgtAttribute,
                              zVIEW   vSrc,
                              zCPCHAR cpcSrcListEntity,
                              zCPCHAR cpcSrcEAC,
                              zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
BuildEntityAttributeFromCSV( zVIEW   vSrc,
                             zCPCHAR cpcSrcEntity,
                             zCPCHAR cpcSrcAttribute,
                             zVIEW   vTgt,
                             zCPCHAR cpcTgtListEntity,
                             zCPCHAR cpcTgtEAC,
                             zLONG   lFlag );

/////////////////////////////////////////////////////////////////////////////
// Should be OE operations
/////////////////////////////////////////////////////////////////////////////

#define  zCURSOR_ENTITY_NOT_IN_VIEW -4

zOPER_EXPORT zSHORT OPERATION
CheckEntityExistence( zVIEW v, zCPCHAR cpcEntityName );
zOPER_EXPORT zSHORT OPERATION
GetRealEntityName( zVIEW v, zPCHAR pchEntityName );

/////////////////////////////////////////////////////////////////////////////
//
// Prototypes for Zeidon Custom Ctrl Messages
//
/////////////////////////////////////////////////////////////////////////////

#define  zPRINT_PAGE        0x0001
#define  zPRINT_PERCENT     0x0002
#define  zPRINT_FILLPAGE    0x0004
#define  zPRINT_PORTRAIT    0x0800
#define  zPRINT_LANDSCAPE   0x0400
#define  zPRINT_SHADESELE   0x2000
#define  zPRINT_SHADESELR   0x1000

#define zDRAW_LINES   0x0001
#define zDRAW_TEXT    0x0002
#define zDRAW_NOCARD  0x0004

#pragma pack(8)
typedef struct tagCOMPILE_DIRS
{
   zCHAR  szZeidonExecutableDir[ zMAX_FILENAME_LTH + 1 ];
   zPCHAR pszTargetExecutableDir;
   zPCHAR pszTargetObjectDir;
   zPCHAR pszCompilerDir;
   zPCHAR pszMakefileDir;
   zPCHAR pszEnvironmentDir;
   zPCHAR pszPgmSrcDir;
   zPCHAR pszMetaSrcDir;
   zPCHAR pszExecDir;
   zSHORT nSourceFiles;
   zSHORT nResourceFiles;

} zCOMPILE_DIRS;

typedef struct tagCTRLBOI_BMP
{
   zCHAR  szDLLName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR  szBMPUpOrIconName[ zMAX_FILENAME_LTH + 1 ];
   zLONG  lBMPUpOrIconID;
   zCHAR  szBMPDownName[ zMAX_FILENAME_LTH + 1 ];
   zLONG  lBMPDownID;
   zCHAR  szBMPFocusName[ zMAX_FILENAME_LTH + 1 ];
   zLONG  lBMPFocusID;
   zCHAR  szBMPDisabledName[ zMAX_FILENAME_LTH + 1 ];
   zLONG  lBMPDisabledID;

} zCTRLBOI_BMP;
#pragma pack()

#define zMAX_RES_ID_USER 4096
#define zLINESIZE 4000

#define ZEIDON_RC_START "//{{ZEIDON"
#define ZEIDON_RC_END   "//}}ZEIDON"

zOPER_EXPORT zSHORT OPERATION
SP_GetShapeCtrlBOI( zVIEW    vCtrl,
                    zPSHORT  pbRectangle,
                    zPSHORT  pbRoundRect,
                    zPSHORT  pbEllipse,
                    zPSHORT  pbDiamond,
                    zPSHORT  pbHoriontal,
                    zPSHORT  pbVertical,
                    zPSHORT  pbDiagDescend,
                    zPSHORT  pbDiagAscend,
                    zPLONG   plPenWidth,
                    zPLONG   plPenType,
                    zPLONG   plPenColor,
                    zPLONG   plRoundValue,
                    zPLONG   plBackgroundColor,
                    zPLONG   plFlags );

zOPER_EXPORT zSHORT OPERATION
SP_SetShapeCtrlBOI( zVIEW   vCtrl,
                    zSHORT  bRectangle,
                    zSHORT  bRoundRect,
                    zSHORT  bEllipse,
                    zSHORT  bDiamond,
                    zSHORT  bHoriontal,
                    zSHORT  bVertical,
                    zSHORT  bDiagDescend,
                    zSHORT  bDiagAscend,
                    zLONG   lPenWidth,
                    zLONG   lPenType,
                    zLONG   lPenColor,
                    zLONG   lRoundValue,
                    zLONG   lBackgroundColor,
                    zLONG   lFlags );

zOPER_EXPORT zSHORT OPERATION
TX_GetTextRptCtrlBOI( zVIEW    vCtrl,
                      zPSHORT  pbMultiLine,
                      zPSHORT  pbBold,
                      zPSHORT  pbItalic,
                      zPSHORT  pbStrikeout,
                      zPSHORT  pbUnderline,
                      zPLONG   plJustify,
                      zPLONG   plSize,
                      zPLONG   plTextColor,
                      zPLONG   plTextBkColor,
                      zPLONG   plBorderStyle,
                      zPLONG   plBorderColor,
                      zPLONG   plEscapement,
                      zPLONG   plType,
                      zPCHAR   pchFaceName );
zOPER_EXPORT zSHORT OPERATION
TX_SetTextRptCtrlBOI( zVIEW   vCtrl,
                      zSHORT  bMultiLine,
                      zSHORT  bBold,
                      zSHORT  bItalic,
                      zSHORT  bStrikeout,
                      zSHORT  bUnderline,
                      zLONG   lJustify,
                      zLONG   lSize,
                      zLONG   lTextColor,
                      zLONG   lTextBkColor,
                      zLONG   lBorderStyle,
                      zLONG   lBorderColor,
                      zLONG   lEscapement,
                      zLONG   lType,
                      zCPCHAR cpcFaceName );
zOPER_EXPORT zSHORT OPERATION
TX_SetTextProperties( zVIEW      vSubtask,
                      zCPCHAR    cpcCtrlTag,
                      LABEL_DATA *pLD );
zOPER_EXPORT zSHORT OPERATION
TX_SetBackgroundImage( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zULONG  ulResId,
                       zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
TX_SetColors( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag,
              zLONG   clr,
              zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
TAB_GetActiveTab( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
TAB_GetActiveSubTab( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zPCHAR  pchCtrlSubTab );
zOPER_EXPORT zSHORT OPERATION
TAB_SetActiveTab( zVIEW    vSubtask,
                  zCPCHAR  cpcCtrlTag,
                  zSHORT   nTabToActivate );
zOPER_EXPORT zSHORT OPERATION
TAB_SetActiveSubTab( zVIEW    vSubtask,
                     zCPCHAR  cpcCtrlTag,
                     zCPCHAR  cpcTabToActivate );
zOPER_EXPORT zSHORT OPERATION
TAB_HideTab( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             zSHORT  nTabToHide,
             zSHORT  nHide );
zOPER_EXPORT zSHORT OPERATION
TAB_HideSubTab( zVIEW    vSubtask,
                zCPCHAR  cpcCtrlTag,
                zCPCHAR  cpcTabToHide,
                zSHORT   nHide );
zOPER_EXPORT zSHORT OPERATION
TAB_SetSubTabColors( zVIEW    vSubtask,
                     zCPCHAR  cpcCtrlTag,
                     zCPCHAR  cpcSubTab,
                     zLONG    lClrText,
                     zLONG    lClrTab );
zOPER_EXPORT zSHORT OPERATION
BTN_SetColor( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag,
              zLONG   lClrText,
              zLONG   lClrBack,
              zLONG   lClrBackHigh,
              zLONG   lClrBackDark );
zOPER_EXPORT zSHORT OPERATION
BMP_SetBitmapFileName( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zCPCHAR cpcBitmapFileName );
zOPER_EXPORT zSHORT OPERATION
BMP_SetBitmapResource( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zCPCHAR cpcDLL_Name,
                       zSHORT  nBitmapResId );
zOPER_EXPORT zSHORT OPERATION
DT_SetStartDateRowsCols( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zSHORT  nYear,
                         zSHORT  nMonth,
                         zSHORT  nRows,
                         zSHORT  nCols,
                         zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
DT_SetTimeEntityAttributes( zVIEW   vSubtask,
                            zCPCHAR cpcCtrlTag,
                            zCPCHAR cpcTimeEntity,
                            zCPCHAR cpcSubjectAttribute,
                            zCPCHAR cpcMessageAttribute,
                            zCPCHAR cpcTimeFromAttribute,
                            zCPCHAR cpcTimeToAttribute,
                            zCPCHAR cpcAlarmAttribute,
                            zCPCHAR cpcAppointmentTypeAttribute,
                            zCPCHAR cpcFullDayAttribute );
zOPER_EXPORT zLONG OPERATION
DT_NewAppointment( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zCPCHAR cpcSubject,
                   zCPCHAR cpcMessage,
                   zLONG   lAppointmentType,
                   zSHORT  bFullDay );
zOPER_EXPORT zSHORT OPERATION
DT_UpdateCurrentAppointment( zVIEW   vSubtask,
                             zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
DT_DeleteCurrentAppointment( zVIEW   vSubtask,
                             zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
DT_SetWorkday( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zSHORT  nStartHour,
               zSHORT  nStartMinute,
               zSHORT  nEndHour,
               zSHORT  nEndMinute,
               zLONG   lDayFlag );
zOPER_EXPORT zSHORT OPERATION
DT_SetColorAssociation( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zCPCHAR cpcAttributeValue,
                        zLONG   lClrText,
                        zLONG   lClrBack,
                        zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
DT_DisplayCurrentAppointment( zVIEW   vSubtask,
                              zCPCHAR cpcCtrlTag,
                              zPCHAR  pchMsg,
                              zLONG   lMsgMaxLth );
zOPER_EXPORT zSHORT OPERATION
ED_HiliteText( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zSHORT  nTextStartPos,
               zSHORT  nTextEndPos );
zOPER_EXPORT zSHORT OPERATION
ED_LimitTextLength( zVIEW   vSubtask,
                    zCPCHAR cpcCtrlTag,
                    zSHORT  nTextLth );
zOPER_EXPORT zSHORT OPERATION
ED_FloatSetRange( zVIEW    vSubtask,
                  zCPCHAR  cpcCtrlTag,
                  zDECIMAL dMin,
                  zDECIMAL dMax );
zOPER_EXPORT zSHORT OPERATION
ED_SetCtrlMapping( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zCPCHAR cpcViewName,
                   zCPCHAR cpcEntityName,
                   zCPCHAR cpcAttributeName,
                   zCPCHAR cpcContextName );
zOPER_EXPORT zULONG OPERATION
ED_GetLastKey( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
ED_GetSelText( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zPCHAR  pchSelectedText,
               zSHORT  nMaxTextLth );
zOPER_EXPORT zSHORT OPERATION
ED_SetSelText( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zPCHAR  pchText );
zOPER_EXPORT zSHORT OPERATION
ED_SetPlaceHolder( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zCPCHAR cpcPlaceHolder );
zOPER_EXPORT zSHORT OPERATION
LB_SetDisplaySelectSet( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zSHORT  nSelectSet );
zOPER_EXPORT zSHORT OPERATION
LB_SetSelectSelectSet( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zSHORT  nSelectSet );
zOPER_EXPORT zSHORT OPERATION
LB_SetSelectedPosition( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zLONG   lDisplayPos );
zOPER_EXPORT zSHORT OPERATION
LB_SortByColumn( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zSHORT  nColumn,
                 zSHORT  nAscending );
zOPER_EXPORT zSHORT OPERATION
LB_GetSortOrder( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zPCHAR  pchReturnOrder,
                 zSHORT  nMaxReturnLth );
zOPER_EXPORT zSHORT OPERATION
LB_SetSortOrder( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zCPCHAR cpcNewSortOrder );
zOPER_EXPORT zSHORT OPERATION
LB_SetColorAttributeName( zVIEW   vSubtask,
                          zCPCHAR cpcCtrlTag,
                          zCPCHAR cpcAttributeName,
                          zLONG   lColumn );
zOPER_EXPORT zSHORT OPERATION
LB_SetColorAssociation( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zLONG   lColumn,
                        zCPCHAR cpcAttributeValue,
                        zLONG   lClrText,
                        zLONG   lClrBack,
                        zLONG   lFlags );
zOPER_EXPORT zSHORT OPERATION
LB_RemoveColorAssociations( zVIEW   vSubtask,
                            zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
LB_ReplaceEntityKey( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zULONG  ulOldKey,
                     zULONG  ulNewKey );
zOPER_EXPORT zLONG OPERATION
LB_AutoSizeColumns( zVIEW   vSubtask,
                    zCPCHAR cpcCtrlTag,
                    zLONG   lCol,
                    zLONG   lTgtMinWidth,
                    zLONG   lTgtMaxWidth );
zOPER_EXPORT zSHORT OPERATION
GRID_SetSelectSelectSet( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zSHORT  nSelectSet );
zOPER_EXPORT zSHORT OPERATION
GRID_SetDisplaySelectSet( zVIEW   vSubtask,
                          zCPCHAR cpcCtrlTag,
                          zSHORT  nSelectSet );
zOPER_EXPORT zSHORT OPERATION
GRID_SortByColumn( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zSHORT  lColumn,
                   zSHORT  nAscending );
zOPER_EXPORT zSHORT OPERATION
GRID_GetSortOrder( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zPCHAR  pchReturnOrder,
                   zSHORT  nMaxReturnLth );
zOPER_EXPORT zSHORT OPERATION
GRID_SetSortOrder( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zCPCHAR cpcNewSortOrder );
zOPER_EXPORT zSHORT OPERATION
GRID_SetSelectedPosition( zVIEW   vSubtask,
                          zCPCHAR cpcCtrlTag,
                          zLONG   lDisplayPos );
zOPER_EXPORT zSHORT OPERATION
GRID_SetColorAttributeName( zVIEW   vSubtask,
                            zCPCHAR cpcCtrlTag,
                            zCPCHAR cpcAttributeName,
                            zLONG   lColumn );
zOPER_EXPORT zSHORT OPERATION
GRID_SetColorAssociation( zVIEW   vSubtask,
                          zCPCHAR cpcCtrlTag,
                          zLONG   lColumn,
                          zCPCHAR cpcAttributeValue,
                          zLONG   lClrText,
                          zLONG   lClrBack,
                          zLONG   lFlags );
zOPER_EXPORT zSHORT OPERATION
GRID_RemoveColorAssociations( zVIEW   vSubtask,
                              zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
GRID_SetCheckAttribute( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zLONG   lColumn,
                        zCPCHAR cpcTextEntity,
                        zCPCHAR cpcTextAttribute,
                        zCPCHAR cpcTextContext );
zOPER_EXPORT zSHORT OPERATION
GRID_SetRowColumnColors( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zLONG   lRow,
                         zLONG   lCol,
                         zLONG   clrText,
                         zLONG   clrBack );
zOPER_EXPORT zSHORT OPERATION
GRID_SetColumnCtrl( zVIEW   vSubtask,
                    zCPCHAR cpcCtrlTag,
                    zLONG   lColumn,
                    zCPCHAR cpcSubCtrlTag,
                    zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
GRID_LockColumn( zVIEW    vSubtask,
                 zCPCHAR  cpcCtrlTag,
                 zSHORT   nColNbr,
                 zSHORT   bLock );
zOPER_EXPORT zSHORT OPERATION
GRID_GetActiveCell( zVIEW    vSubtask,
                    zCPCHAR  cpcCtrlTag,
                    zPLONG   plActiveRow,
                    zPLONG   plActiveCol );
zOPER_EXPORT zSHORT OPERATION
GRID_SetActiveCell( zVIEW    vSubtask,
                    zCPCHAR  cpcCtrlTag,
                    zLONG    lActiveRow,
                    zLONG    lActiveCol );
zOPER_EXPORT zLONG OPERATION
GRID_GetPasteCellAndText( zVIEW    vSubtask,
                          zCPCHAR  cpcCtrlTag,
                          zPLONG   plRowNbr,
                          zPLONG   plColNbr,
                          zPCHAR   pchText,
                          zSHORT   nMaxTextLth );
zOPER_EXPORT zLONG OPERATION
GRID_GetCellData( zVIEW    vSubtask,
                  zCPCHAR  cpcCtrlTag,
                  zLONG    lRowNbr,
                  zLONG    lColNbr );
zOPER_EXPORT zSHORT OPERATION
GRID_SetCellData( zVIEW    vSubtask,
                  zCPCHAR  cpcCtrlTag,
                  zPCHAR   pchData,
                  zLONG    lRowNbr,
                  zLONG    lColNbr );
zOPER_EXPORT zSHORT OPERATION
GRID_SetGridLines( zVIEW    vSubtask,
                   zCPCHAR  cpcCtrlTag,
                   zSHORT   bHorizontal,
                   zSHORT   bVertical );
zOPER_EXPORT zSHORT OPERATION
GRID_ReplaceEntityKey( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zULONG  ulOldKey,
                       zULONG  ulNewKey );
zOPER_EXPORT zSHORT OPERATION
PL_AddProperty( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zSHORT  nItemType,
                zCPCHAR cpcPropertyName,
                zCPCHAR cpcInitialValue,
                zCPCHAR cpcComboList,
                zCPCHAR cpcDescription );
zOPER_EXPORT zSHORT OPERATION
CB_SetDisplaySelectSet( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zSHORT  nSelectSet );
zOPER_EXPORT zSHORT OPERATION
CB_SetSelectSelectSet( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zSHORT  nSelectSet );
zOPER_EXPORT zSHORT OPERATION
CB_SetData( zVIEW   vSubtask,
            zCPCHAR cpcCtrlTag,
            zCPCHAR cpcSelectItem,
            zCPCHAR cpcListData,
            zLONG   lFlag );
zOPER_EXPORT zSHORT OPERATION
CB_GetSelectedString( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zPCHAR  pchSelectedString,
                      zLONG   lMaxLth );
zOPER_EXPORT zLONG OPERATION
CB_SelectString( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zCPCHAR cpcSearchString,
                 zLONG   lFlags );
zOPER_EXPORT zSHORT OPERATION
SS_LockColumn( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zSHORT  nColNbr,
               zSHORT  bLock );
zOPER_EXPORT zSHORT OPERATION
SS_GetActiveCell( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  zPLONG  plRowNbr,
                  zPLONG  plColNbr );
zOPER_EXPORT zSHORT OPERATION
SS_GetCellData( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zPCHAR  pchReturnData,
                zLONG   lMaxLth,
                zLONG   lRowNbr,
                zLONG   lColNbr );
zOPER_EXPORT zSHORT OPERATION
SS_SetCellData( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zPCHAR  pchData,
                zLONG   lRowNbr,
                zLONG   lColNbr );
zOPER_EXPORT zSHORT OPERATION
BM_GetPointerCoordinates( zVIEW   vSubtask,
                          zCPCHAR cpcCtrlTag,
                          zPLONG  plXPos,
                          zPLONG  plYPos );
zOPER_EXPORT zSHORT OPERATION
OL_ResetNodeList( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag );
zOPER_EXPORT zLONG OPERATION
OL_SetDefaultBitmap( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zCPCHAR cpcEntityName,
                     zCPCHAR cpcBitmapFileName );
zOPER_EXPORT zLONG OPERATION
OL_GetDefaultBitmap( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zCPCHAR cpcEntityName,
                     zPCHAR  pcBitmapFileName,
                     zULONG  ulMaxReturnBitmapNameLength );
zOPER_EXPORT zLONG OPERATION
OL_GetSelectedBitmap( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zCPCHAR cpcEntityName,
                      zPCHAR  pcBitmapFileName,
                      zULONG  ulMaxReturnBitmapNameLength );
zOPER_EXPORT zLONG OPERATION
OL_SetSelectedBitmap( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zCPCHAR cpcEntityName,
                      zCPCHAR cpcBitmapFileName );
zOPER_EXPORT zSHORT OPERATION
OL_SelectItemAtPosForEntity( zVIEW    vSubtask,
                             zCPCHAR  cpcCtrlTag,
                             zCPCHAR  cpcEntityName,
                             zLONG    lFlags );
zOPER_EXPORT zLONG OPERATION
OL_SetTextForCurrentItem( zVIEW    vSubtask,
                          zCPCHAR  cpcCtrlTag,
                          zCPCHAR  cpcItemText );
zOPER_EXPORT zLONG OPERATION
OL_SetTextColorForItemText( zVIEW    vSubtask,
                            zCPCHAR  cpcCtrlTag,
                            zCPCHAR  cpcItemText,
                            COLORREF clrTextColor,
                            zBOOL    bEnsureVisible );
zOPER_EXPORT zLONG OPERATION
OL_ResetAllTextColorsForItemText( zVIEW    vSubtask,
                                  zCPCHAR  cpcCtrlTag );
zOPER_EXPORT zLONG OPERATION
OL_SelectItem( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zCPCHAR cpcEntityName,
               zULONG  ulEntityKey,
               zULONG  ulValue );
zOPER_EXPORT zLONG OPERATION
OL_FindItemByAttribute( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zCPCHAR cpcEntityName,
                        zCPCHAR cpcAttribName,
                        zCPCHAR cpcFindString,
                        zULONG  ulEntityKey,
                        zULONG  ulFlag );
zOPER_EXPORT zLONG OPERATION
OL_GetExpandState( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zCPCHAR cpcEntityName );
zOPER_EXPORT zLONG OPERATION
OL_ExpandEntity( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zCPCHAR cpcEntityName,
                 zULONG  ulValue );
zOPER_EXPORT zLONG OPERATION
OL_GetLastExpandedEntityName( zVIEW   vSubtask,
                              zCPCHAR cpcCtrlTag,
                              zPCHAR  pReturnEntityName );
zOPER_EXPORT zLONG OPERATION
OL_GetLastCollapsedEntityName( zVIEW   vSubtask,
                               zCPCHAR cpcCtrlTag,
                               zPCHAR  pReturnEntityName );
zOPER_EXPORT zLONG OPERATION
OL_GetExpandingEntityName( zVIEW   vSubtask,
                           zCPCHAR cpcCtrlTag,
                           zPCHAR  pReturnEntityName );
zOPER_EXPORT zLONG OPERATION
OL_GetCollapsingEntityName( zVIEW   vSubtask,
                            zCPCHAR cpcCtrlTag,
                            zPCHAR  pReturnEntityName );
zOPER_EXPORT zLONG OPERATION
OL_GetCurrentEntityName( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zPVIEW  pView,
                         zPCHAR  pReturnEntityName );
zOPER_EXPORT zLONG OPERATION
OL_GetBackgroundColor( zVIEW    vSubtask,
                       zCPCHAR  cpcCtrlTag );
zOPER_EXPORT zLONG OPERATION
OL_SetBackgroundColor( zVIEW    vSubtask,
                       zCPCHAR  cpcCtrlTag,
                       zLONG    lColor );
zOPER_EXPORT zLONG OPERATION
OL_GetTextColorForEntity( zVIEW    vSubtask,
                          zCPCHAR  cpcCtrlTag,
                          zCPCHAR  cpcEntityName );
zOPER_EXPORT zLONG OPERATION
OL_SetTextColorForEntity( zVIEW    vSubtask,
                          zCPCHAR  cpcCtrlTag,
                          zCPCHAR  cpcEntityName,
                          COLORREF clrTextColor );
zOPER_EXPORT zLONG OPERATION
OL_SetTxtFontForEntity( zVIEW    vSubtask,
                        zCPCHAR  cpcCtrlTag,
                        zCPCHAR  cpcEntityName,
                        LOGFONT  fntTextFont );
zOPER_EXPORT zLONG OPERATION
OL_GetTextFontForEntity( zVIEW    vSubtask,
                         zCPCHAR  cpcCtrlTag,
                         zCPCHAR  cpcEntityName,
                         zPLONG   plSize,
                         zPLONG   plBold,
                         zPLONG   plItalic,
                         zPLONG   plUnderline,
                         zPLONG   plStrikeout,
                         zPLONG   plTextColor,
                         zPLONG   plEscapement,
                         zPCHAR   pcFaceName );
zOPER_EXPORT zLONG OPERATION
OL_SetTextFontForEntity( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zCPCHAR cpcEntityName,
                         zLONG   lSize,
                         zLONG   lBold,
                         zLONG   lItalic,
                         zLONG   lUnderline,
                         zLONG   lStrikeout,
                         zLONG   lTextColor,
                         zLONG   lEscapement,
                         zPCHAR  cpcFaceName );
zOPER_EXPORT zLONG OPERATION
OL_SetCtrlState( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lStatusType,
                 zLONG   lValue );
zOPER_EXPORT zLONG OPERATION
OL_GetCtrlState( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lStatusType );
zOPER_EXPORT zLONG OPERATION
OL_EditLabel( zVIEW    vSubtask,
              zCPCHAR  cpcCtrlTag,
              zULONG   ulTextLength );
zOPER_EXPORT zSHORT OPERATION
OL_SetCursorByEntityNumber( zVIEW   vAppOI,
                            zCPCHAR cpcEntity,
                            zULONG  ulEntityNumber );
zOPER_EXPORT zSHORT OPERATION
OL_GetCurrentEntityNumber( zVIEW   vAppOI,
                           zCPCHAR cpcEntity,
                           zPULONG pulEntityNumber );
zOPER_EXPORT zSHORT OPERATION
TB_GetCurrentTag( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  zPCHAR  pReturnTag );
zOPER_EXPORT zLONG  OPERATION
TB_GetLastSelection( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zPCHAR  pchText,
                     zLONG   lMaxTextLth );
zOPER_EXPORT zLONG  OPERATION
TB_GetItemText( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zCPCHAR cpcSubCtrlTag,
                zPCHAR  pchText,
                zLONG   lMaxTextLth );
zOPER_EXPORT zLONG  OPERATION
TB_SetItemText( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zCPCHAR cpcSubCtrlTag,
                zCPCHAR cpcText );
zOPER_EXPORT zSHORT OPERATION
TB_GetTextMode( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
TB_SetTextMode( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zSHORT  bTextMode );
zOPER_EXPORT zSHORT OPERATION
MB_SetMessage( zVIEW   vSubtask,
               zSHORT  nItem,
               zCPCHAR cpcMessage );

// Messages to control for dialog operations to use

/////////////////////////////////////////////////////////////////////////////
//
// Prototypes for Hier Custom Ctrl Messages
//
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT OPERATION
HD_ZoomDiagram( zVIEW    vSubtask,
                zCPCHAR  cpcCtrlTag,
                zSHORT   nPercent,
                zSHORT   nOptions );
zOPER_EXPORT zSHORT OPERATION
HD_PrintDiagram( zVIEW    vSubtask,
                 zCPCHAR  cpcCtrlTag,
                 zSHORT   nPercent,
                 zSHORT   nOptions );
zOPER_EXPORT zSHORT OPERATION
HD_GetPointerCoordinates( zVIEW    vSubtask,
                          zCPCHAR  cpcCtrlTag,
                          zPLONG   plPosX,
                          zPLONG   plPosY );
zOPER_EXPORT zVOID OPERATION
HD_SetColors( zVIEW    vSubtask,
              zCPCHAR  cpcCtrlTag,
              zPULONG  pulColorNormal,
              zULONG   ulColorSelected,
              zULONG   ulColorBox,
              zULONG   ulColorLines,
              zULONG   ulColorText,
              zULONG   ulColorNoUpdate,
              zSHORT   bRedraw );
zOPER_EXPORT zVOID OPERATION
HD_CenterNode( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag );
zOPER_EXPORT zVOID OPERATION
HD_SelectNode( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
HD_IsNodeVisible( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
HD_SetProperties( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  zLONG   lProperties );

zOPER_EXPORT zSHORT OPERATION
OLB_AddImages( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zSHORT  nLargeImageListId,
               zSHORT  nSmallImageListId );
zOPER_EXPORT zSHORT OPERATION
OLB_AddFolder( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zCPCHAR cpcFolderText,
               zSHORT  nFolderNbr );
zOPER_EXPORT zSHORT OPERATION
OLB_AddFolderItem( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zSHORT  nFolderNbr,
                   zSHORT  nItemNbr,
                   zCPCHAR cpcItemText,
                   zSHORT  nImageNbr,
                   zULONG  ulExtraData );
zOPER_EXPORT zSHORT OPERATION
OLB_AddFolderBar( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  zCPCHAR cpcFolderText,
                  zCPCHAR cpcSubCtrlTag,
                  zULONG  ulExtraData );
zOPER_EXPORT zSHORT OPERATION
OLB_SetSelFolder( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  zSHORT  nFolderNbr );
zOPER_EXPORT zSHORT OPERATION
OLB_SetEventCallback( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      LPARAM  lpfnOLB_Event );

#ifdef __WIN32__
/////////////////////////////////////////////////////////////////////////////
//
// Prototypes for Rich Text edit ctrl operations
//
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zLONG OPERATION
RT_GetLineCount( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag );
zOPER_EXPORT zLONG OPERATION
RT_GetLine( zVIEW   vSubtask,
            zCPCHAR cpcCtrlTag,
            zLONG   lLineNbr,
            zPCHAR  pchBuffer,
            zLONG   lMaxLth );
zOPER_EXPORT zLONG OPERATION
RT_GetFirstVisibleLine( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag );
zOPER_EXPORT zLONG OPERATION
RT_LineNumber( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zLONG   lLineNbr );
zOPER_EXPORT zLONG OPERATION
RT_LineFromChar( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lCharPos );
zOPER_EXPORT zLONG OPERATION
RT_LineLength( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zLONG   lLineNbr );
zOPER_EXPORT zLONG OPERATION
RT_LineScroll( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zLONG   lLines,
               zLONG   lCharacters );
zSHORT
RT_CanUndo( zVIEW   vSubtask,
            zCPCHAR cpcCtrlTag );
zSHORT
RT_GetModify( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag );
zSHORT
RT_SetModify( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag,
              zBOOL   bModified );
zSHORT
RT_GetRect( zVIEW   vSubtask,
            zCPCHAR cpcCtrlTag,
            zPLONG  plTop,
            zPLONG  plLeft,
            zPLONG  plBottom,
            zPLONG  plRight );
zSHORT
RT_GetCharPos( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zLONG   lCharPos,
               zPLONG  plX,
               zPLONG  plY );
zSHORT
RT_SetOptions( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zUSHORT uOp,
               zULONG  ulFlags );
zSHORT
RT_CanPaste( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             UINT    nFormat );
zSHORT
RT_GetSel( zVIEW   vSubtask,
           zCPCHAR cpcCtrlTag,
           zPLONG  plStartChar,
           zPLONG  plEndChar );
zSHORT
RT_LimitText( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag,
              zLONG   lChars );
zSHORT
RT_SetSel( zVIEW   vSubtask,
           zCPCHAR cpcCtrlTag,
           zLONG   lStartChar,
           zLONG   lEndChar );
zULONG
RT_GetDefaultCharFormat( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         CHARFORMAT *cf );
zULONG
RT_GetSelectionCharFormat( zVIEW   vSubtask,
                           zCPCHAR cpcCtrlTag,
                           CHARFORMAT *cf );
zLONG
RT_GetEventMask( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag );
zLONG
RT_GetLimitText( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag );
zULONG
RT_GetParaFormat( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  PARAFORMAT *pf );
zLONG
RT_GetSelText( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zPCHAR  pchBuffer,
               zLONG   lMaxLth );
zULONG
RT_GetSelectionType( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag );
zLONG
RT_SetBackgroundColor( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zBOOL   bSysColor,
                       zLONG   lRGB_Color );
zSHORT
RT_SetDefaultCharFormat( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         CHARFORMAT *cf );
zSHORT
RT_SetSelectionCharFormat( zVIEW   vSubtask,
                           zCPCHAR cpcCtrlTag,
                           CHARFORMAT *cf );
zSHORT
RT_SetWordCharFormat( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      CHARFORMAT *cf );
zULONG
RT_SetEventMask( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zULONG  ulEventMask );
zSHORT
RT_SetParaFormat( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  PARAFORMAT *pf );
zBOOL
RT_SetTargetDevice( zVIEW   vSubtask,
                    zCPCHAR cpcCtrlTag,
                    HDC     hDC,
                    zLONG   lLineWidth );
zLONG
RT_GetTextLength( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag );
zSHORT
RT_SetReadOnly( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zBOOL   bReadOnly );
zSHORT
RT_EmptyUndoBuffer( zVIEW   vSubtask,
                    zCPCHAR cpcCtrlTag );
zSHORT
RT_ReplaceSel( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zCPCHAR cpcNewText,
               zBOOL   bCanUndo );
zSHORT
RT_SetRect( zVIEW   vSubtask,
            zCPCHAR cpcCtrlTag,
            LPCRECT lpRect );
zSHORT
RT_DisplayBand( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                LPRECT  pDisplayRect );
zLONG
RT_FindText( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             zULONG  ulFlags,
             FINDTEXTEX *pFindText );
zLONG
RT_FormatRange( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                FORMATRANGE *pfr,
                zBOOL   bDisplay );
zSHORT
RT_HideSelection( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  zBOOL   bHide,
                  zBOOL   bPerm );
zSHORT
RT_PasteSpecial( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zULONG  ulClipFormat,
                 zULONG  dvAspect,
                 HMETAFILE hMF );
zSHORT
RT_RequestResize( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag );
zLONG
RT_StreamIn( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             zLONG   lFormat,
             EDITSTREAM *es );
zLONG
RT_StreamOut( zVIEW   vSubtask,
              zCPCHAR cpcCtrlTag,
              zLONG   lFormat,
              EDITSTREAM *es );
zSHORT
RT_Undo( zVIEW   vSubtask,
         zCPCHAR cpcCtrlTag );
zSHORT
RT_Clear( zVIEW   vSubtask,
          zCPCHAR cpcCtrlTag );
zSHORT
RT_Copy( zVIEW   vSubtask,
         zCPCHAR cpcCtrlTag );
zSHORT
RT_Cut( zVIEW   vSubtask,
        zCPCHAR cpcCtrlTag );
zSHORT
RT_Paste( zVIEW   vSubtask,
          zCPCHAR cpcCtrlTag );
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Prototypes for Zeidon message queue operation prototypes
//
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT OPERATION
MQ_MessageSend( zVIEW   vMsgQ,
                zVIEW   vSubtask,
                zCPCHAR cpcMsgId,
                zCPCHAR cpcTitle,
                zCPCHAR cpcMsgText,
                zLONG   lMsgType,
                zSHORT  bBeep );
zOPER_EXPORT zSHORT OPERATION
MQ_MessagePrompt( zVIEW   vMsgQ,
                  zVIEW   vSubtask,
                  zCPCHAR cpcMsgId,
                  zCPCHAR cpcTitle,
                  zCPCHAR cpcMsgText,
                  zSHORT  bBeep,
                  zSHORT  nButtons,
                  zSHORT  nDefaultButton,
                  zSHORT  nIcon );
zOPER_EXPORT zSHORT OPERATION
MQ_MessagePromptForInput( zVIEW    vMsgQ,
                          zVIEW    vSubtask,
                          zCPCHAR  cpcMsgId,
                          zCPCHAR  cpcTitle,
                          zCPCHAR  cpcMsgText,
                          zSHORT   bBeep,
                          zPCHAR  lpchReturnBuffer,
                          zUSHORT  usBufferLth );
zOPER_EXPORT zSHORT OPERATION
MQ_MessagePresent( zVIEW  vMsgQ,
                   zVIEW  vSubtask,
                   zLONG  lEventType );

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zSHORT OPERATION
GetActiveX_ParameterCount( zVIEW    vSubtask,
                           zCPCHAR  cpcCtrlTag,
                           zLONG    lEventID );
zOPER_EXPORT zSHORT OPERATION
GetActiveX_ParameterValue( zVIEW    vSubtask,
                           zCPCHAR  cpcCtrlTag,
                           zLONG    lEventID,
                           zLONG    lParmID,
                           zPCHAR   pchValue,
                           zSHORT   nMaxLth );

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT void OPERATION
SplitCtrlBOI_BMP( zPCHAR pCtrlBOI,
                  zLONG  lCtrlBOI_Size,
                  zCTRLBOI_BMP *pBMP );
zOPER_EXPORT zLONG OPERATION
BuildCtrlBOI_BMP( zCTRLBOI_BMP *pBMP,
                  zPCHAR pCtrlBOI,
                  zLONG  lCtrlBOI_Size );
zOPER_EXPORT zSHORT OPERATION
SetResourceFileIDs( zVIEW         vSubtask,
                    zVIEW         vTaskLPLR,
                    zLONG         hFile,
                    zCOMPILE_DIRS *pcd,
                    zPCHAR        pszLine,
                    zLONG         lMaxLth,
                    zVIEW         vDialog );

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT zLONG OPERATION
SetFlagBit( zLONG  lFlag,
            zSHORT nFlagPosition,
            zSHORT bSetOn );
zOPER_EXPORT zSHORT OPERATION
GetFlagBit( zLONG  lFlag,
            zSHORT nFlagPosition );
zOPER_EXPORT zLONG OPERATION
SetFlagSequence( zLONG  lFlag,
                 zLONG  lSequenceFlag,
                 zSHORT bSetOn );
zOPER_EXPORT zSHORT OPERATION
IsFlagSequenceSet( zLONG  lFlag,
                   zLONG  lTestFlag );
zOPER_EXPORT zSHORT OPERATION
AreBitsSetInFlag( zLONG  lFlag,
                  zLONG  lTestFlag );
zOPER_EXPORT zSHORT OPERATION
ActivateWindowPlacement( zVIEW   vSubtask,
                         zCPCHAR cpcProfileViewName );
zOPER_EXPORT zSHORT OPERATION
SaveWindowPlacement( zVIEW vSubtask,
                     zVIEW vProfile,
                     zLONG lFlags );
zOPER_EXPORT zSHORT OPERATION
SaveWindowProfile( zCPCHAR cpcDialogName,
                   zCPCHAR cpcWindowName,
                   zVIEW   vProfile,
                   zLONG   lPosX,
                   zLONG   lPosY,
                   zLONG   lSizeX,
                   zLONG   lSizeY,
                   zLONG   lMXN,
                   zLONG   lFlags );
zOPER_EXPORT zLONG OPERATION
RestoreWindowPlacement( zVIEW vSubtask,
                        zVIEW vProfile );
zOPER_EXPORT zLONG OPERATION
RestoreWindowProfile( zCPCHAR cpcDialogName,
                      zCPCHAR cpcWindowName,
                      zVIEW vProfile,
                      HWND  hWnd );

zOPER_EXPORT void OPERATION
GetWindowPreferenceString( zVIEW   vSubtask,
                           zCPCHAR cpcStringKey,
                           zPCHAR  pchReturnString,
                           zLONG   lBufferLth );
zOPER_EXPORT void OPERATION
SetWindowPreferenceString( zVIEW   vSubtask,
                           zCPCHAR cpcStringKey,
                           zCPCHAR cpcString );
zOPER_EXPORT zLONG OPERATION
GetWindowPreferenceInteger( zVIEW   vSubtask,
                            zCPCHAR cpcIntegerKey );
zOPER_EXPORT void OPERATION
SetWindowPreferenceInteger( zVIEW   vSubtask,
                            zCPCHAR cpcIntegerKey,
                            zLONG   lInteger );
zOPER_EXPORT void OPERATION
GetProfileStr( zVIEW    vSubtask,
               zCPCHAR  cpcIniID,
               zCPCHAR  cpcDlgTag,
               zCPCHAR  cpcWndTag,
               zCPCHAR  cpcStringKey,
               zPCHAR   pchReturnBuffer,
               zLONG    lBufferLth );
zOPER_EXPORT void OPERATION
SetProfileStr( zVIEW    vSubtask,
               zCPCHAR  cpcIniID,
               zCPCHAR  cpcDlgTag,
               zCPCHAR  cpcWndTag,
               zCPCHAR  cpcStringKey,
               zCPCHAR  cpcString );
zOPER_EXPORT zLONG OPERATION
GetProfileNbr( zVIEW    vSubtask,
               zCPCHAR  cpcIniID,
               zCPCHAR  cpcDlgTag,
               zCPCHAR  cpcWndTag,
               zCPCHAR  cpcIntegerKey );
zOPER_EXPORT void OPERATION
SetProfileNbr( zVIEW    vSubtask,
               zCPCHAR  cpcIniID,
               zCPCHAR  cpcDlgTag,
               zCPCHAR  cpcWndTag,
               zCPCHAR  cpcIntegerKey,
               zLONG    lInteger );

zOPER_EXPORT zSHORT OPERATION
TG_GetMouseDownParam( zVIEW  vSubtask,
                      zPSHORT psButton,
                      zPSHORT psShift,
                      zPLONG plXPos,
                      zPLONG  plYPos );

zOPER_EXPORT zSHORT OPERATION
TG_GetMouseClick( zVIEW vSubtask, zSHORT nButton );


zOPER_EXPORT zSHORT OPERATION
TG_GetMouseClickWithKey( zVIEW vSubtask,
                         zSHORT nButton,
                         zSHORT nKey );

zOPER_EXPORT zSHORT OPERATION
ITrueDBGridCtrl_SetDataMode( zVIEW vSubtask,
                             zCPCHAR cpcCtrlTag,
                             zLONG nDataMode );

zOPER_EXPORT zSHORT OPERATION
TG_LockColumn( zVIEW    vSubtask,
               zCPCHAR  cpcCtrlTag,
               zSHORT   nIndex,
               zBOOL    bLock );

zOPER_EXPORT zSHORT OPERATION
TG_SetCellData( zVIEW    vSubtask,
                zCPCHAR  cpcCtrlTag,
                zCPCHAR  pchData,
                zLONG    lRowNbr,
                zLONG    lColNbr );

zOPER_EXPORT zSHORT OPERATION
TG_GetCellData( zVIEW    vSubtask,
                zCPCHAR  cpcCtrlTag,
                zPCHAR   pchData,
                zLONG    lMaxLth,
                zLONG    lRowNbr,
                zLONG    lColNbr );

zOPER_EXPORT zSHORT OPERATION
TG_GetActiveCell( zVIEW    vSubtask,
                  zCPCHAR  cpcCtrlTag,
                  zPLONG   lRowNbr,
                  zPLONG   lColNbr );

zOPER_EXPORT zSHORT OPERATION
TG_SetActiveCell( zVIEW    vSubtask,
                  zCPCHAR  cpcCtrlTag,
                  zLONG    lRowNbr,
                  zLONG    lColNbr );

zOPER_EXPORT zSHORT OPERATION
TG_SetCheckBoxTranslation( zVIEW    vSubtask,
                           zCPCHAR  cpcCtrlTag,
                           zSHORT   nColumn,
                           zCPCHAR  cpcTRUE,
                           zCPCHAR  cpcFALSE );

zOPER_EXPORT zSHORT OPERATION
TG_EnableAutosort( zVIEW    vSubtask,
                   zCPCHAR  cpcCtrlTag,
                   zBOOL    propVal );

zOPER_EXPORT zSHORT OPERATION
TG_AllowAddNew( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zBOOL   bAllow );

zOPER_EXPORT zSHORT OPERATION
TG_AllowDelete( zVIEW   vSubtask,
                zCPCHAR cpcCtrlTag,
                zBOOL   bAllow );

zOPER_EXPORT zSHORT OPERATION
TG_LockGrid( zVIEW   vSubtask,
             zCPCHAR cpcCtrlTag,
             zLONG   lSplit,
             zBOOL   bLock );

zOPER_EXPORT zSHORT OPERATION
TG_SetForegroundColor( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zLONG   lColumn,
                       zLONG   lRGBValue );

zOPER_EXPORT zSHORT OPERATION
TG_SetBackgroundColor( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zLONG   lColumn,
                       zLONG   lRGBValue );

zOPER_EXPORT zSHORT OPERATION
TG_SetTextColor( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lColumn,
                 zLONG   lRGBValue );

zOPER_EXPORT zSHORT OPERATION
TG_SetFont( zVIEW   vSubtask,
            zCPCHAR cpcCtrlTag,
            zLONG   lColumn,
            zCPCHAR cpcFontName,
            zLONG   lFontSize,
            zBOOL   bBold,
            zBOOL   bUnderLine,
            zBOOL   bItalic,
            zBOOL   bStrikeThrough );

zOPER_EXPORT zSHORT OPERATION
TG_SetCaption( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zLONG   lColumn,
               zCPCHAR cpcCaption );

zOPER_EXPORT zSHORT OPERATION
TG_SetAlignment( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lColumn,
                 zLONG   lAlignment);

zOPER_EXPORT zSHORT OPERATION
TG_SetColumnWidth( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zLONG   lColumn,
                   zLONG   nWidth);

zOPER_EXPORT zSHORT OPERATION
TG_SetMultiSelect( zVIEW    vSubtask,
                    zCPCHAR cpcCtrlTag,
                    zLONG   lSet );

zOPER_EXPORT zSHORT OPERATION
TG_SetAllowColSelect( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zBOOL   bSet );

zOPER_EXPORT zSHORT OPERATION
TG_SetAllowRowSelect( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zBOOL   bSet );

zOPER_EXPORT zSHORT OPERATION
TG_SetAllowRowSizing( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zBOOL    bSet );

zOPER_EXPORT zSHORT OPERATION
TG_SetAllowFocus( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  zLONG   lColumn,
                  zBOOL    bSet );

zOPER_EXPORT zSHORT OPERATION
TG_SetButtonAlways( zVIEW   vSubtask,
                    zCPCHAR cpcCtrlTag,
                    zLONG   lColumn,
                    zLONG   bSet );

zOPER_EXPORT zSHORT OPERATION
TG_SetInactiveBackColor( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zLONG   nSplit,
                         zLONG   lRGBValue );

zOPER_EXPORT zSHORT OPERATION
TG_SetInactiveForeColor( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zLONG   nSplit,
                         zLONG   lRGBValue );

zOPER_EXPORT zSHORT OPERATION
TG_GetCaption( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zLONG   lColumn,
               zPCHAR  pchCaption,
               zULONG  ulLth );

zOPER_EXPORT zSHORT OPERATION
TG_ShowColumn( zVIEW   vSubtask,
               zCPCHAR cpcCtrlTag,
               zLONG   lColumn,
               zBOOL   bShow );

zOPER_EXPORT zSHORT OPERATION
TG_LimitTextLen( zVIEW   vSubtask,
                 zCPCHAR cpcCtrlTag,
                 zLONG   lColumn,
                 zLONG   lLength );
zOPER_EXPORT zSHORT OPERATION
TG_SetDateCtrlForColumn( zVIEW vSubtask,
                         zCPCHAR  cpcCtrlTag,
                         zLONG nColumn,
                         zBOOL bSet );

#define zDR_MEMORY
#ifdef zDR_MEMORY
#ifdef __cplusplus
zOPER_EXPORT zSHORT OPERATION
DrAllocTaskMemory( zCOREMEM Memory, zLONG lBytes, zLONG lGuard = 0xc8c8c8c8 );
#else
zOPER_EXPORT zSHORT OPERATION
DrAllocTaskMemory( zCOREMEM Memory, zLONG lBytes, zLONG lGuard );
#endif
zOPER_EXPORT zSHORT OPERATION
DrReAllocTaskMemory( zCOREMEM Memory, zLONG lBytes );
zOPER_EXPORT zSHORT OPERATION
DrFreeTaskMemory( zPVOID Address );
zOPER_EXPORT zPVOID OPERATION
DrLockTaskMemory( zPVOID Address );
zOPER_EXPORT zPVOID OPERATION
DrUnlockTaskMemory( zPVOID Address );
#else
#define DrAllocTaskMemory( a, b, c )    SfAllocTaskMemory( a, b )
#define DrReAllocTaskMemory  SfReAllocTaskMemory
#define DrFreeTaskMemory     SfFreeTaskMemory
#define DrLockTaskMemory     SfLockTaskMemory
#define DrUnlockTaskMemory   SfUnlockTaskMemory
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

zOPER_EXPORT void OPERATION
AbortTask( zCPCHAR cpcMessage );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_LockColumn( zVIEW    vSubtask,
                     zCPCHAR  cpcCtrlTag,
                     zSHORT   nIndex,
                     zBOOL    bLock );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetCellData( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zCPCHAR cpcData,
                      zLONG   lRowNbr,
                      zLONG   lColNbr );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_GetCellData( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zPCHAR  pchData,
                      zLONG   lMaxLth,
                      zLONG   lRowNbr,
                      zLONG   lColNbr );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_GetActiveCell( zVIEW    vSubtask,
                        zCPCHAR  cpcCtrlTag,
                        zPLONG   lRowNbr,
                        zPLONG   lColNbr );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetActiveCell( zVIEW    vSubtask,
                        zCPCHAR  cpcCtrlTag,
                        zLONG    lRowNbr,
                        zLONG    lColNbr );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_EnableAutosort( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zBOOL   propVal );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetCheckBoxTranslation( zVIEW vSubtask,
                                 zCPCHAR  cpcCtrlTag,
                                 zSHORT nColumn,
                                 zCPCHAR zcpcTRUE,
                                 zCPCHAR zcpcFALSE );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_AllowAddNew( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zBOOL   bAllow );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_AllowDelete( zVIEW   vSubtask,
                      zCPCHAR cpcCtrlTag,
                      zBOOL   bAllow );


zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_LockGrid( zVIEW   vSubtask,
                   zCPCHAR cpcCtrlTag,
                   zLONG   lSplit,
                   zBOOL   bLock );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetForegroundColor( zVIEW   vSubtask,
                             zCPCHAR cpcCtrlTag,
                             zLONG   lColumn,
                             zLONG   lRGBValue );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetBackgroundColor( zVIEW   vSubtask,
                             zCPCHAR cpcCtrlTag,
                             zLONG   lColumn,
                             zLONG   lRGBValue );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetTextColor( zVIEW   vSubtask,
                       zCPCHAR cpcCtrlTag,
                       zLONG   lColumn,
                       zLONG   lRGBValue );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetFont( zVIEW   vSubtask,
                  zCPCHAR cpcCtrlTag,
                  zLONG   lColumn,
                  zCPCHAR cpcFontName,
                  zLONG   lFontSize,
                  zBOOL   bBold,
                  zBOOL   bUnderLine,
                  zBOOL   bItalic,
                  zBOOL   bStrikeThrough );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetCaption( zVIEW   vSubtask,
                     zCPCHAR cpcCtrlTag,
                     zLONG   lColumn,
                     zCPCHAR cpcCaption );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetAllignment( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zLONG   lColumn,
                        zLONG   lAlignment);

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetColumnWidth( zVIEW   vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zLONG   lColumn,
                         zLONG   lWidth);

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetMultiSelect( zVIEW    vSubtask,
                         zCPCHAR cpcCtrlTag,
                         zLONG   lSet );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetAllowColSelect( zVIEW   vSubtask,
                            zCPCHAR cpcCtrlTag,
                            zBOOL   bSet );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetAllowRowSelect( zVIEW   vSubtask,
                            zCPCHAR cpcCtrlTag,
                            zBOOL   bSet );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetAllowRowSizing( zVIEW   vSubtask,
                            zCPCHAR cpcCtrlTag,
                            zBOOL   bSet );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetAllowFocus( zVIEW   vSubtask,
                        zCPCHAR cpcCtrlTag,
                        zLONG   lColumn,
                        zBOOL   bSet );

zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetButtonAlways( zVIEW   vSubtask,
                          zCPCHAR cpcCtrlTag,
                          zLONG   lColumn,
                          zLONG   bSet );


zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetInactiveBackColor( zVIEW   vSubtask,
                               zCPCHAR cpcCtrlTag,
                               zLONG   nSplit,
                               zLONG   lRGBValue );


zOPER_EXPORT zSHORT OPERATION
ZWEBGRID_SetInactiveForeColor( zVIEW   vSubtask,
                               zCPCHAR cpcCtrlTag,
                               zLONG   nSplit,
                               zLONG   lRGBValue );

// Return 0 for Inactive and 1 for Active.
zOPER_EXPORT zSHORT OPERATION
MapPointIsActive( );

// Launches MapPoint (if not on hold)
zOPER_EXPORT zSHORT OPERATION
MapPointStart( );

// Quit the MapPoint instance lauched by this application.
zOPER_EXPORT zSHORT OPERATION
MapPointStop( );

// Quit the MapPoint instance lauched by this application
// and don't restart MapPoint until HOLD is released.
zOPER_EXPORT zSHORT OPERATION
MapPointStopAndHold( );

// Launches MapPoint even if on hold.
zOPER_EXPORT zSHORT OPERATION
MapPointStartFromHold( );

// Show or hide the MapPoint instance lauched by this application.
zOPER_EXPORT zSHORT OPERATION
MapPointShowApplication( BOOL bShow );

zOPER_EXPORT zSHORT OPERATION
MapPointValidateAddress( zPCHAR pchStreet, zPCHAR pchCity, zPCHAR pchOtherCity,
                         zPCHAR pchRegion, zPCHAR pchPostalCode,
                         zCPCHAR cpcStreetAddress, zLONG lFlag );
zOPER_EXPORT zSHORT OPERATION
MapPointSetPushPin( zCPCHAR cpcStreet, zCPCHAR cpcCity, zCPCHAR cpcOtherCity,
                    zCPCHAR cpcRegion, zCPCHAR cpcPostalCode,
                    zCPCHAR cpcMsg, zSHORT nPushPin, zLONG lFlag );

zOPER_EXPORT zSHORT OPERATION
GetDistanceRectangle( zDECIMAL *pdSouthLatitude,
                      zDECIMAL *pdEastLongitude,
                      zDECIMAL *pdNorthLatitude,
                      zDECIMAL *pdWestLongitude,
                      zDECIMAL dLatitude, zDECIMAL dLongitude,
                      zDECIMAL dDistance, zLONG lFlag );
zOPER_EXPORT zDECIMAL OPERATION
GetDistance( zDECIMAL dLat1, zDECIMAL dLon1,
             zDECIMAL dLat2, zDECIMAL dLon2, zLONG lFlag );
zOPER_EXPORT double OPERATION
GCDistance( double dLat1, double dLon1,
            double dLat2, double dLon2, zLONG lFlag );

zOPER_EXPORT double OPERATION
ApproxDistance( double dLat1, double dLon1,
                double dLat2, double dLon2, zLONG lFlag );

zOPER_EXPORT double OPERATION
EllipsoidDistance( double dLat1, double dLon1,
                   double dLat2, double dLon2, zLONG lFlag );

zOPER_EXPORT double OPERATION
GCAzimuth( double dLat1, double dLon1, double dLat2, double dLon2 );

zOPER_EXPORT double OPERATION
EllipsoidAzimuth( double dLat1, double dLon1,
                  double dLat2, double dLon2 );

zOPER_EXPORT double OPERATION
ApproxAzimuth( double dLat1, double dLon1,
               double dLat2, double dLon2 );

zOPER_EXPORT zLONG OPERATION
CreateSmtpConnection( zPCHAR pchSmtpServer );
zOPER_EXPORT zSHORT OPERATION
CreateSmtpMessage( zLONG  lSmtpConnection,
                   zPCHAR pchSmtpServer,
                   zPCHAR pchFrom,
                   zPCHAR pchTo,
                   zLONG  lRecipientCnt,
                   zPCHAR pchSubject,
                   zLONG  lMimeType,      // 1 - text;  2 - html
                   zPCHAR pchBody,
                   zLONG  lHasAttachment, // 0 - No;  1 - Yes
                   zPCHAR pchAttachFile,
                   zPCHAR pchUserName,
                   zPCHAR pchPassword );
zOPER_EXPORT zVOID OPERATION
CloseSmtpConnection( zLONG lSmtpConnection );

zOPER_EXPORT zLONG OPERATION
CreateSeeConnection( zPCHAR pchSmtpServer,
                     zPCHAR pchSenderEmailAddr,
                     zPCHAR pchSmtpUserName,
                     zPCHAR pchSmtpPassword );

zOPER_EXPORT zSHORT OPERATION
CreateSeeMessage( zLONG  lSeeConnection,
                  zPCHAR pchSmtpServer,
                  zPCHAR pchSender,
                  zPCHAR pchRecipient,
                  zPCHAR pchCC,
                  zPCHAR pchBCC,
                  zPCHAR pchSubject,
                  zLONG  lMimeType,   // 1 - text;  2 - html
                  zPCHAR pchBody,     // if pchBody or pchAltText start
                                      // with '@', a file name is expected
                  zPCHAR pchAltText,  // valid only when sending html
                  zPCHAR pchEmbeddedImages,
                  zLONG  lHasAttachment, // 0 - No;  1 - Yes
                  zPCHAR pchAttachFile,
                  zPCHAR pchUserName,
                  zPCHAR pchPassword );

zOPER_EXPORT zVOID OPERATION
CloseSeeConnection( zLONG lSeeConnection );

zOPER_EXPORT zSHORT OPERATION
ValidateEmailAddressFormat( zCPCHAR cpcEmailAddress );

zOPER_EXPORT zLONG OPERATION
CreateCommaSeparatedList( zVIEW   v,
                          zCPCHAR cpcEntityName,
                          zCPCHAR cpcAttributeName,
                          zCPCHAR cpcContext,
                          zCPCHAR cpcScope,
                          zLONG   lFlags );
zOPER_EXPORT zLONG OPERATION
DeleteCommaSeparatedList( zLONG lpMemory );

zVIEW OPERATION
GetNextSubtaskWithinParent( zVIEW vSubtaskParent,
                            zVIEW vSubtaskLast,
                            zLONG lFlag );

zOPER_EXPORT zLONG OPERATION
CallObjectOperation1Param( zVIEW  vObject,
                           zPCHAR pchOperationName,
                           zPCHAR pchErrorPrefix );

zOPER_EXPORT zSHORT OPERATION
CallDialogOperation( zVIEW  vSubtask,
                     zPCHAR pchDLL_Name,
                     zPCHAR pchOperName );
zOPER_EXPORT zSHORT OPERATION
SetSystemMenuItem( zVIEW vSubtask, zCPCHAR cpcItemText,
                   zCPCHAR cpcAfterItem, zUSHORT uItemId,
                   zCPCHAR cpcDLL_Name, zCPCHAR cpcOperationName );

zOPER_EXPORT zLONG OPERATION
DialPhoneNumber( zVIEW   vSubtask,
                 zCPCHAR cpcPhoneNumber,
                 zCPCHAR cpcCalledParty );

#ifdef __cplusplus
}
#endif

#endif   // #ifndef __zdrvropr_h__
