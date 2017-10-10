/////////////////////////////////////////////////////////////////////////////
//
// Prototypes for Zeidon Custom Controls
// Copyright © 1995 - 2016 QuinSoft, Inc.
//
/////////////////////////////////////////////////////////////////////////////

//
/* CHANGE LOG
2002.07.25  FH
   define zMSG_REPAINTALLZEIDONWINDOWS for resize of dialog in dialog painter
2000.09.21  BL   Z10   RAD 53746
   Added defines for Menu Format in Dialog Painter (= Format Controls)

1999.11.11  TMV  10  ActiveX
   changed GenerateActiveX_Code to have an additional parameter
   szScriptOper

1999.04.24  DC
   Added zLISTBOX_SORTEDHEADERS definition.

1998.07.19   RG
   Quinsoft removed the definition of zMSG_SETTOOLBOX and added the
   definition of zMSG_SETGRID

1999.04.19  RS
   Commentlines required for Rose.
*/

// Don't remove the following commentlines. They are required for Rose.
//#include <kzoengaa.h> //required for Rose
//#include <zdrapp.h> //required for Rose

#ifndef __tzctlopr_h__
#define __tzctlopr_h__

#define zMSG_DELETEALLPAINTERWINDOWS      1
#define zMSG_CREATEZEIDONWINDOW           2
#define zMSG_REPAINTZEIDONCONTROL         3
#define zMSG_UPDATEZEIDONWINDOW           4
#define zMSG_UPDATEALLZEIDONWINDOWS       5
#define zMSG_DELETETOOLBAR                6
#define zMSG_ACTIVATEPAINTERWINDOW        7
#define zMSG_REPAINTZEIDONWINDOW          8
#define zMSG_DELETECURRENTPAINTERWINDOW   9
#define zMSG_REPAINTACTIONBAR             10
#define zMSG_UPDATEWINDOWBYNAME           11
#define zMSG_GETACTIVEWINDOWNAME          12
#define zMSG_UPDATEACTIVEWINDOWNAME       13
#define zMSG_ENABLEPAINTERWINDOWS         14
#define zMSG_CHANGESELECTEDCONTROLS       15
#define zMSG_SYSTEMMINIMIZE               16
#define zMSG_SYSTEMRESTORE                17
#define zMSG_SELECTMODALPOINTER           18
#define zMSG_REPLACETOOLBARBUTTONS        19
#define zMSG_SHOWTABBING                  20
#define zMSG_GETTABBING                   21
#define zMSG_REMOVETABBING                22
#define zMSG_BUILDTZPNEVWO                23
#define zMSG_PUTTOOLBOXONTOP              24
#define zMSG_INITPAINTER                  25
#define zMSG_SETSCROLLBARS                26
#define zMSG_SETGRID                      27
#define zMSG_RESTORE_PLACEMENT            28
#define zMSG_SAVE_PLACEMENT               29
#define zMSG_TERMPAINTER                  30
#define zMSG_PAINTERINITIALIZED           31
#define zMSG_REFRESHWINDOWLIST            32
#define zMSG_GETCONTROLBAR                33
#define zMSG_GETCURRPAINTER               34
#define zMSG_GETCURRCTRL                  35
#define zMSG_GETCURRCTRLWND               36
#define zMSG_ISREPORT                     37
#define zMSG_UNDO                         38
#define zMSG_REDO                         39
#define zMSG_CLIPBOARD_COPY               40
#define zMSG_CLIPBOARD_PASTE              41
#define zMSG_GET_COMMON_DETAIL_FLAGS      42
#define zMSG_UPDATE_COMMON_DETAIL         43
#define zMSG_SETCURRCTRL                  44
#define zMSG_ALIGN_LEFT                   45
#define zMSG_ALIGN_RIGHT                  46
#define zMSG_ALIGN_TOP                    47
#define zMSG_ALIGN_BOTTOM                 48
#define zMSG_SIZE_HEIGHT                  49
#define zMSG_SIZE_WIDTH                   50
#define zMSG_SIZE_WIDTH_HEIGHT            51
#define zMSG_EQUAL_SPACE_VERTICAL         52
#define zMSG_EQUAL_SPACE_HORIZONTAL       53
#define zMSG_ABUT_VERTICAL                54
#define zMSG_ABUT_HORIZONTAL              55
#define zMSG_DELETE_SELECTED              56
#define zMSG_GET_NEXT_SELECTED_CTRL       57
#define zMSG_REPAINTALLZEIDONWINDOWS      58
#define zMSG_CLIPBOARD_COPY_MENU          59
#define zMSG_CLIPBOARD_PASTE_MENU         60
#define zMSG_GETWINDOWBYNAME              61
#define zMSG_EMPTYALLPAINTERWINDOWS       62
#define zMSG_GENERATEJAVAJSP              63
#define zMSG_SAVEDIALOG                   64
#define zMSG_GENERATEALLJAVAJSP           65

#define zLISTBOX_SORTEDHEADERS            zCONTROL_SPECIFIC_2

// CONTROL MESSAGES
#define zCTRLMSG_CREATE_GUI               1
#define zCTRLMSG_MOVE                     2
#define zCTRLMSG_SIZE                     3
#define zCTRLMSG_ACCEPT_CHILD             4
#define zCTRLMSG_ACCEPT_PARENT            5
#define zCTRLMSG_CREATE_ZEIDON            6
#define zCTRLMSG_CHANGE_TYPE              7
#define zCTRLMSG_NOTIFY_PARENT            8

#define zCTRL_COMMON_INVISIBLE            0x00000001
#define zCTRL_COMMON_DISABLED             0x00000002
#define zCTRL_COMMON_DISABLED_READONLY    0x00000004
#define zCTRL_COMMON_BORDER               0x00000010
#define zCTRL_COMMON_SIZE_BORDER          0x00000020
#define zCTRL_COMMON_PREFILL              0x00000040
#define zCTRL_COMMON_LEFT_JUSTIFY         0x00000100
#define zCTRL_COMMON_RIGHT_JUSTIFY        0x00000200
#define zCTRL_COMMON_CENTER_JUSTIFY       0x00000400
#define zCTRL_COMMON_NO_TAB               0x00001000
#define zCTRL_COMMON_ABSOLUTE_PIXEL_SIZE  0x00002000
#define zCTRL_COMMON_ABSOLUTE_PIXEL_POS   0x00004000

#ifdef __cplusplus
extern "C"
{
#endif


zOPER_EXPORT zSHORT OPERATION
AcceptEntity( zVIEW    vSubtask,
              zPCHAR   cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
ERD_SelectEntity( zVIEW    vSubtask,
                  zPCHAR   cpcCtrlTag,
                  zBOOL    bSelect,
                  zBOOL    bClear );
zOPER_EXPORT zSHORT OPERATION
AdjustRelPortsForSelectedEnt( zVIEW    vSubtask,
                              zPCHAR   cpcCtrlTag,
                              zSHORT   bIncrement );
zOPER_EXPORT zSHORT OPERATION
RecalculateAllRelationships( zVIEW    vSubtask,
                             zPCHAR   cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
ERD_ExpandDiagram( zVIEW    vSubtask,
                   zPCHAR   cpcCtrlTag,
                   zSHORT   nPercent );
zOPER_EXPORT zSHORT OPERATION
ERD_ContractDiagram( zVIEW    vSubtask,
                     zPCHAR   cpcCtrlTag,
                     zSHORT   nPercent );
zOPER_EXPORT zBOOL OPERATION
ERD_IsEntityVisible( zVIEW    vSubtask,
                     zPCHAR   cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
SelectEntityNeighbors( zVIEW    vSubtask,
                       zPCHAR   cpcCtrlTag,
                       zBOOL    bSelect,
                       zSHORT   nSelectRels,
                       zBOOL    bClear );
zOPER_EXPORT zSHORT OPERATION
AcceptRelationship( zVIEW    vSubtask,
                    zPCHAR   cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
RemoveEntity( zVIEW    vSubtask,
              zPCHAR   cpcCtrlTag,
              zBOOL    bPending,
              zLONG    lZKey );
zOPER_EXPORT zSHORT OPERATION
RemoveRelationship( zVIEW    vSubtask,
                    zPCHAR   cpcCtrlTag,
                    zBOOL    bPending,
                    zLONG    lZKey );
zOPER_EXPORT zSHORT OPERATION
ZoomDiagram( zVIEW    vSubtask,
             zPCHAR   cpcCtrlTag,
             zSHORT   nPercent,
             zSHORT   nOptions );
zOPER_EXPORT zSHORT OPERATION
PrintDiagram( zVIEW    vSubtask,
              zPCHAR   cpcCtrlTag,
              zSHORT   nPercent,
              zSHORT   nOptions );
zOPER_EXPORT zSHORT OPERATION
RefreshEntity( zVIEW    vSubtask,
               zPCHAR   cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
CenterEntity( zVIEW    vSubtask,
              zPCHAR   cpcCtrlTag );
zOPER_EXPORT zSHORT OPERATION
ValidNewEntityPosition( zVIEW    vSubtask,
                        zPCHAR   cpcCtrlTag,
                        zLONG    lPosX,
                        zLONG    lPosY );
zOPER_EXPORT zSHORT OPERATION
RefreshRelationship( zVIEW    vSubtask,
                     zPCHAR   cpcCtrlTag,
                     zLONG    lFlag );
zOPER_EXPORT zSHORT OPERATION
RefreshDiagram( zVIEW    vSubtask,
                zPCHAR   cpcCtrlTag,
                zLONG    lFlag );
zOPER_EXPORT zSHORT OPERATION
GetPointerCoordinates( zVIEW    vSubtask,
                       zPCHAR   cpcCtrlTag,
                       zPSHORT  pnPosX,
                       zPSHORT  pnPosY );
zOPER_EXPORT zSHORT OPERATION
SetDrawOptions( zVIEW    vSubtask,
                zPCHAR   cpcCtrlTag,
                zUSHORT  uOptions );
zOPER_EXPORT void OPERATION
SetColors( zVIEW    vSubtask,
           zPCHAR   cpcCtrlTag,
           zULONG   ulColorNormal,
           zULONG   ulColorSelected,
           zULONG   ulColorBox,
           zULONG   ulColorLines,
           zULONG   ulColorText,
           zULONG   ulColorNoUpdate,
           zBOOL    bRedraw );

zOPER_EXPORT zLONG  OPERATION
fnPainterCall( zSHORT nMsg,
               zVIEW  vSubtask,
               zVIEW  vDialog,
               zPCHAR szParm,
               zLONG  lMaxLth );

zOPER_EXPORT zLONG OPERATION
BuildTZEDWRKO( zVIEW  vTZEDWRKO,
               zPCHAR pchOperation,
               zSHORT nMaxOperLth );

zOPER_EXPORT zLONG OPERATION
BuildTZPEAXWO( zVIEW vTZPEAXWO, zCPCHAR cpcGUID, zBOOL bEvents );

zOPER_EXPORT zSHORT OPERATION
GenerateActiveX_Code( zVIEW vSubtask, zCPCHAR cpcTypeLib,
                      zCPCHAR cpcScriptOper,
                      zCPCHAR cpcClassName, zCPCHAR cpcDLL_Name,
                      zCPCHAR cpcPathName, zCPCHAR cpcGUID );

zOPER_EXPORT zSHORT OPERATION
CtrlValidate( zVIEW  vCtrl,
              zVIEW  vParent,
              zVIEW  vChgCtrl,
              zSHORT nValidate );

zOPER_EXPORT zLONG OPERATION
CreateFlatCtrlList( zVIEW vSubtask, zCPCHAR cpcWndTag,
                    zLONG lMultX, zLONG lDivX,
                    zLONG lMultY, zLONG lDivY );

zOPER_EXPORT zLONG OPERATION
GetNextWebListCtrl( zVIEW vSubtask, zPCHAR pchListCtrlTag,
                    zPLONG plHeight, zPLONG plWidth );

zOPER_EXPORT zLONG OPERATION
GetNextWebCtrlOffset( zVIEW   vSubtask,
                      zCPCHAR cpcListCtrlTag,
                      zPCHAR  pchFloatCtrlTag,
                      zSHORT  bVertical );

#ifdef __cplusplus
}
#endif


#endif  // __tzctlopr_h__
