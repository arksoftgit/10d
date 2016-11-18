// Change LOG
//
// 2002.11.28 HH
// 2002.09.03 DonC
//    Added operation GetStrFromAttrByContext
//
// 2000.05.30 PAS
//    New Operations for Dimension Hierarcy in TZEREMDO
//
// 2001.01.03 BL
//    Added oTZDMSRCO_CheckDomainType for Domain Tool
//
// 2000.11.07 RG   Z2000
//    Added prototype for operation: SironCreateDataModel
//
// 2000.01.13 BL   Z10  new PPE Handling
//    Insert Operation LoadZeidonPPE
//
// 1998.11.02 TMV
// Adding a new argument to TransferToEditor
// Argument lInvokingCommand
// Purpose: Giving the editor a flag to invoke a command after
//          starting the editor

// DGC 10/17/95 -----------------------------------------------------------
// Added following prototypes.  They should be removed as
// soon as global op prototypes are automatically added to this file.

zOPER_EXPORT zSHORT OPERATION
zgGetZeidonToolsDir( zVIEW  vSubtask,
                     zPCHAR pchFullDir,
                     zSHORT nDirType );

//zOPER_EXPORT zSHORT OPERATION
//oTZZOLODO_LOD_Migrate( zPVIEW   pvNewMainLOD,
//                       zPCHAR   pchLOD_Name,
//                       zVIEW    vSourceLPLR,
//                       zVIEW    vSubtask );

// DGC 10/17/95 -----------------------------------------------------------

//start TZWDLGSO 2016.11.10 14:18:04
zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_ConvertListBoxToGrid( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_CloneCtrlMap( zVIEW vViewToInstance0,
                        zVIEW vNewWC1,
                        zVIEW vOrigW2,
                        zVIEW vOrigWC3,
                        zVIEW vSourceLPLR4,
                        zVIEW vSubtask5 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_CloneOptMap( zVIEW vViewToInstance0,
                       zVIEW vOrigW1,
                       zVIEW vOrigWO2,
                       zVIEW vNewW3,
                       zVIEW vNewWO4,
                       zVIEW vSubtask5 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_CloneWindow( zVIEW vViewToInstance0,
                       zVIEW vOrigW1,
                       zVIEW vSourceLPLR2,
                       zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_MergeWindowComponents( zVIEW vViewToInstance0,
                                 zVIEW vOrigW1,
                                 zVIEW vSourceLPLR2,
                                 zVIEW vPE3,
                                 zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_MergeWebMenus( zVIEW vViewToInstance0,
                         zVIEW vvOrigW1,
                         zVIEW vvSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_PositionOnVOR( zVIEW vViewToInstance0,
                         zVIEW vOrigW1,
                         zVIEW vSourceLPLR2,
                         zPCHAR pchViewName3,
                         zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_BuildWebCtrlPropOpts( zVIEW vViewToInstance0,
                                zVIEW vSourceView1,
                                zPCHAR pchSourceEntityName2,
                                zPCHAR pchSourceAttributeName3 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_BuildMapTypeList( zVIEW vvDialog0,
                            zVIEW vvSourceView1,
                            zPCHAR pchSourceEntityName2,
                            zPCHAR pchSourceAttributeName3 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_BuildCtrlMapByTagList( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_DialogMigrate( zVIEW vViewToInstance0,
                         zPCHAR pchSourceDialogMetaName1,
                         zVIEW vSourceLPLR2,
                         zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_ControlRelinkDelete( zVIEW vViewToInstance0,
                               zVIEW vRecursiveviewforControl1,
                               zPVIEW vViewofLastLODprocessed2,
                               zPLONG lZKeyoflastLODviewproce3,
                               zVIEW vLPLRforLODs4,
                               zVIEW vSubtask5 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_DialogRelinkDelete( zVIEW vViewToInstance0,
                              zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_ConvertCtrlTextToWeb( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_GenerateJSP( zVIEW vViewToInstance0,
                       zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_GenJSP_ProcessFileIn( zVIEW vViewToInstance0,
                                zLONG llFileJSP1,
                                zPCHAR pchszWriteBuffer2 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_GenerateJSPJava( zVIEW vViewToInstance0,
                           zVIEW vvSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_GenerateJSPJavaInc( zVIEW vViewToInstance0,
                              zVIEW vvSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZWDLGSO_GenJSPJ_ProcessFileIn( zVIEW vViewToInstance0,
                                 zLONG llFileJSP1,
                                 zPCHAR pchszWriteBuffer2 );

//end
//start TZWDGRWO 2016.08.23 10:53:36
zOPER_EXPORT zSHORT OPERATION
oTZWDGRWO_ArcActionWindow( zVIEW vV10,
                           zVIEW vV21,
                           zVIEW vV32 );

zOPER_EXPORT zSHORT OPERATION
oTZWDGRWO_ArcGroupEvents( zVIEW vV10,
                          zVIEW vV21,
                          zVIEW vV32,
                          zSHORT nN3 );

zOPER_EXPORT zSHORT OPERATION
oTZWDGRWO_ArcWindowAction( zVIEW vV10,
                           zVIEW vV21,
                           zVIEW vV32,
                           zSHORT nN3 );

zOPER_EXPORT zSHORT OPERATION
oTZWDGRWO_LoadOrInitialize( zPVIEW vvGRW0,
                            zVIEW vvDlg1 );

zOPER_EXPORT zSHORT OPERATION
oTZWDGRWO_NodeActionSync( zVIEW vV10,
                          zVIEW vV21 );

zOPER_EXPORT zSHORT OPERATION
oTZWDGRWO_NodeEntitySync( zVIEW vV10,
                          zVIEW vV21,
                          zSHORT nN2,
                          zPCHAR eE3 );

zOPER_EXPORT zSHORT OPERATION
oTZWDGRWO_NodeWindowSync( zVIEW vV10,
                          zVIEW vV21 );

zOPER_EXPORT zSHORT OPERATION
oTZWDGRWO_ReInit( zVIEW vV10,
                  zVIEW vV21 );

//end
//start TZTENVRO 2016.08.23 10:53:35
zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_SyncTablRecKey( zVIEW vvDTE0,
                          zVIEW vvERD1,
                          zVIEW vvSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_TE_Migrate( zPVIEW vViewToInstance0,
                      zPCHAR pchSourceTEMetaName1,
                      zVIEW vSourceLPLR2,
                      zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_TE_RelinkDelete( zVIEW vViewToInstance0,
                           zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_SetFieldSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_SortFields( zVIEW vViewToInstance0,
                      zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_NewFieldSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_DelFieldFromSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_MoveFieldInSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_SetFieldDataRelKeyFlag( zVIEW vViewtoInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZTENVRO_Accept_FieldDataRelKey( zVIEW vViewtoInstance0,
                                  zPCHAR pchEntityName1,
                                  zSHORT nEvent2,
                                  zSHORT nState3 );

//end
//start TZOGSRCO 2016.08.23 10:53:32
zOPER_EXPORT zSHORT OPERATION
oTZOGSRCO_GlobalOperGrpMigrate( zVIEW vViewToInstance0,
                                zPCHAR pchSourceGlobalOperGrou1,
                                zVIEW vSourceLPLR2,
                                zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZOGSRCO_AcceptParameter( zVIEW vViewtoInstance0,
                           zPCHAR pchEntityName1,
                           zSHORT nEvent2,
                           zSHORT nState3 );

zOPER_EXPORT zSHORT OPERATION
oTZOGSRCO_GenerateXOG( zVIEW vViewToInstance0 );

//end
//start TZERSASO 2016.08.23 10:53:31
zOPER_EXPORT zSHORT OPERATION
oTZERSASO_SA_Migrate( zPVIEW vViewToInstance0,
                      zPCHAR pchSourceSAMetaName1,
                      zVIEW vSourceLPLR2,
                      zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZERSASO_SA_MigrateWithERDs( zPVIEW vViewToInstance0,
                              zVIEW vSourceSAtoMigrate1,
                              zVIEW vNewERD2,
                              zVIEW vSourceERD3,
                              zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZERSASO_SA_RelinkDelete( zVIEW vViewToInstance0,
                           zVIEW vSubtask1 );

//end
//start TZDGSRCO 2016.08.23 10:53:30
zOPER_EXPORT zSHORT OPERATION
oTZDGSRCO_DomainMigrate( zVIEW vViewToInstance0,
                         zPCHAR pchSourceDomainMetaName1,
                         zPCHAR pchSourceDomainGroupMet2,
                         zVIEW vSourceLPLR3,
                         zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZDGSRCO_DomainMigrateReus( zVIEW vViewToInstance0,
                             zVIEW vOldDomainGroup1,
                             zVIEW vvSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZDGSRCO_DomainAddForMerge( zPVIEW vViewToInstance0,
                             zVIEW vSourceLPLR1,
                             zVIEW vCurrentLPLR2,
                             zPCHAR pchSourceDirectoryName3,
                             zPCHAR pchDomainName4,
                             zVIEW vSubtask5 );

zOPER_EXPORT zSHORT OPERATION
oTZDGSRCO_DomainGrpMigrate( zVIEW vViewToInstance0,
                            zPCHAR pchSsourceDomainGroupMe1,
                            zVIEW vSourceLPLR2,
                            zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZDMSRCO_ReplaceOrAddDomToXDM( zVIEW vvSubtask0,
                                zVIEW vViewToInstance1,
                                zSHORT nCommitFlag0or12 );

zOPER_EXPORT zSHORT OPERATION
oTZDMSRCO_CheckDomainType( zVIEW vViewToInstance0 );

//end
//start TZCMREPO 2016.08.23 10:53:28
zOPER_EXPORT zSHORT OPERATION
oTZCMREPO_ObjectConstraints( zVIEW vViewtoInstance0,
                             zSHORT nEvent1,
                             zSHORT nState2 );

//end
//start TZADCSDO 2016.08.23 10:53:25
zOPER_EXPORT zSHORT OPERATION
oTZADCSDO_DS_RelinkDelete( zVIEW vViewToInstance0,
                           zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZADCSDO_DialogSpecMigrate( zPVIEW vViewToInstance0,
                             zPCHAR pchSourceDialogSpecName1,
                             zVIEW vSourceLPLR2,
                             zVIEW vSubtask3 );

//end

//start TZCM_OPR 2015.11.20 15:45:00
zOPER_EXPORT zSHORT OPERATION
InitializeNextZKeyForObject( zVIEW vObjectView0,
                             zPCHAR pchRootEntityName1,
                             zPCHAR pchCurrentEntityName2 );

zOPER_EXPORT zSHORT OPERATION
ActivateEmptyMetaOI( zVIEW vSubtask0,
                     zPVIEW vReturnView1,
                     zSHORT nMetaType2,
                     zLONG lControlFlag3 );

zOPER_EXPORT zSHORT OPERATION
RebuildXDM( zVIEW vvSubtask0 );

zOPER_EXPORT zSHORT OPERATION
RebuildXODs( zVIEW vvSubtask0 );

zOPER_EXPORT zSHORT OPERATION
RebuildMetaLists( zVIEW vvSubtask0 );

zOPER_EXPORT zLONG OPERATION
DropMetaOI_FromList( zLONG llListHandle0 );

zOPER_EXPORT zLONG OPERATION
ActivateMetaOI_KeepList( zVIEW vvSubtask0,
                         zPVIEW vvMOI1,
                         zVIEW vvListView2,
                         zSHORT nnType3,
                         zLONG llControl4,
                         zPCHAR pchpchName5,
                         zLONG llZKey6,
                         zSHORT nnCurrentOrReload7,
                         zSHORT nnNameOrZKey8,
                         zLONG llListHandle9 );

zOPER_EXPORT zLONG OPERATION
SetUpMapLOD( zVIEW vViewtoWindow0,
             zVIEW vViewtoDialogWindow1,
             zVIEW vViewtoDialogCtrl2,
             zPCHAR pchCtrlMapVieworActMapV3 );

zOPER_EXPORT zSHORT OPERATION
SetCompSpecPaths( zVIEW vvTarget0,
                  zPCHAR pchpszSourceCompSrcDir1,
                  zPCHAR pchpszSourceLPLRName2,
                  zPCHAR pchpszSourceAktDir3,
                  zPCHAR pchpszEntityName4,
                  zPCHAR pchpszAttributeName5,
                  zPCHAR pchpszDirName6,
                  zPCHAR pchpszMsgTitle7,
                  zSHORT nMaxLth8 );

zOPER_EXPORT zSHORT OPERATION
IntGenFullQualPathFromRelPath( zVIEW  vSubtask0,
                               zPCHAR pchFileName1,
                               zPCHAR pchBaseDir2,
                               zSHORT nMaxLth3,
                               zPCHAR pchDirTxt4 );

zOPER_EXPORT zSHORT OPERATION
SortComponents( zPVIEW vCM_List0 );

zOPER_EXPORT zSHORT OPERATION
SaveSortOrder( zVIEW vSubtask0,
               zVIEW vCM_List1 );

zOPER_EXPORT zSHORT OPERATION
CheckOutStateForCurrentWindow( zVIEW vSubtask0,
                               zVIEW vToolView1 );

zOPER_EXPORT zSHORT OPERATION
SetTitleWithCheckOutState( zVIEW vSubtask0,
                           zPCHAR pchToolname1,
                           zPCHAR pchLodName2,
                           zVIEW vToolView3,
                           zPCHAR pchEntityname4,
                           zLONG lType5 );

zOPER_EXPORT zSHORT OPERATION
CheckDuplicateNameForRefresh( zVIEW vTZCMLPLO_LPLRView0,
                              zVIEW vTZCMCPRO_CPLRView1,
                              zPCHAR pchReturn_CPLR_Type2,
                              zPCHAR pchReturn_LPLR_Type3,
                              zPCHAR pchReturn_LPLR_Name4,
                              zPULONG lReturn_LPLR_ZKey5 );

zOPER_EXPORT zSHORT OPERATION
CheckDuplicateName( zVIEW vTZCMLPLO_LPLRView0,
                    zVIEW vTZCMCPRO_CPLRView1,
                    zPCHAR pchReturn_CPLR_Type2,
                    zPCHAR pchReturn_LPLR_Type3,
                    zPCHAR pchReturn_CPLR_Name4 );

zOPER_EXPORT zSHORT OPERATION
CheckAllDuplicateName( zVIEW vTZCMLPLO_LPLRView0,
                       zVIEW vTZCMCPRO_CPLRView1,
                       zPCHAR pchReturn_CPLR_Type2,
                       zPCHAR pchReturn_LPLR_Type3,
                       zPCHAR pchReturn_CPLR_Name4 );

zOPER_EXPORT zSHORT OPERATION
CheckDuplicateComponents( zVIEW vTZCMLPLOLPLRView0,
                          zVIEW vTZCMCPROCPLRView1,
                          zLONG lComponentType2,
                          zPCHAR pchReturnNameforduplica3 );

zOPER_EXPORT zSHORT OPERATION
ComponentIsCheckedOut( zVIEW vSubtask0,
                       zVIEW vComponentView1,
                       zLONG lType2 );

zOPER_EXPORT zSHORT OPERATION
LoadZeidonPPE( zVIEW vSubtask0,
               zPVIEW vlpPPEView1,
               zSHORT nType2,
               zVIEW vMetaView3,
               zPCHAR pchMessageTitel4,
               zPCHAR pchMessagetext5 );

zOPER_EXPORT zSHORT OPERATION
zltoxa( zLONG lZkeyasaninteger0,
        zPCHAR pchReturnedmetaname1 );

zOPER_EXPORT zSHORT OPERATION
TerminateLPLR( zVIEW vLPLRView0 );

zOPER_EXPORT zSHORT OPERATION
RetrieveViewForMetaList( zVIEW vSubtask0,
                         zPVIEW vListView1,
                         zSHORT nType2 );

zOPER_EXPORT zSHORT OPERATION
InitializeLPLR( zVIEW vLPLRView0,
                zPCHAR pchLPLRName1 );

zOPER_EXPORT zSHORT OPERATION
InitializeDefaultLPL( zVIEW vView0 );

zOPER_EXPORT zSHORT OPERATION
DropMetaOI( zVIEW vSubtask0,
            zVIEW vMetaView1 );

zOPER_EXPORT zSHORT OPERATION
DeleteMetaOI( zVIEW vSubtask0,
              zVIEW vListView1,
              zSHORT nType2 );

zOPER_EXPORT zSHORT OPERATION
CreateMetaEntity( zVIEW vSubtask0,
                  zVIEW vView1,
                  zPCHAR pchEntity2,
                  zSHORT nPos3 );

zOPER_EXPORT zSHORT OPERATION
CreateFileNameFromZKey( zPCHAR pchFileName0,
                        zLONG  lMaxLth,
                        zVIEW  vView1,
                        zPCHAR pchZKey2 );

zOPER_EXPORT zSHORT OPERATION
CommitMetaOI( zVIEW vTaskView0,
              zVIEW vMOI_View1,
              zSHORT nType2 );

zOPER_EXPORT zSHORT OPERATION
CheckExistenceOfMetaOI_ByZKey( zVIEW vSubtask0,
                               zULONG lZKey1,
                               zSHORT nType2 );

zOPER_EXPORT zSHORT OPERATION
CheckExistenceOfMetaOI( zVIEW vSubtask0,
                        zPCHAR pchszMetaName1,
                        zSHORT nType2 );

zOPER_EXPORT zSHORT OPERATION
AssignZKeyToMetaOI( zVIEW vSubtask0,
                    zVIEW vOI_View1,
                    zSHORT nType2,
                    zSHORT nAssign3 );

zOPER_EXPORT zSHORT OPERATION
ActivateMetaOI_ByZKey( zVIEW vSubtask0,
                       zPVIEW vReturnView1,
                       zVIEW vLPLR_View2,
                       zSHORT nMetaType3,
                       zLONG lControlFlag4,
                       zLONG lZKey5,
                       zSHORT nCurrentOrReload6 );

zOPER_EXPORT zSHORT OPERATION
ActivateMetaOI_ByName( zVIEW vSubtask0,
                       zPVIEW vReturnView1,
                       zVIEW vLPLR_View2,
                       zSHORT nMetaType3,
                       zLONG lControlFlag4,
                       zPCHAR pchName5,
                       zSHORT nCurrentOrReload6 );

zOPER_EXPORT zSHORT OPERATION
ActivateMetaOI( zVIEW vSubtask0,
                zPVIEW vReturnView1,
                zVIEW vLPLR_View2,
                zSHORT nMetaType3,
                zLONG lControlFlag4 );

//end
//start TZCM_OPR 2015.10.27 15:41:07

//end
//start TZEREMDO 2016.08.23 10:53:30
zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_ImportADW_Model( zVIEW vViewToInstance0,
                           zVIEW vADWWorkObject1,
                           zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_ConvertZKeyDomains( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_AttributeConstraints( zVIEW vViewtoInstance0,
                                zPCHAR pchEntityName1,
                                zSHORT nEvent2,
                                zSHORT nState3 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_IdentifierConstraints( zVIEW vViewtoInstance0,
                                 zPCHAR pchNameOfEntity1,
                                 zSHORT nEvent2,
                                 zSHORT nState3 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierConstraints( zVIEW vViewtoInstance0,
                              zPCHAR pchNameOfEntity1,
                              zSHORT nEvent2,
                              zSHORT nState3 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DmHierInitLevels( zVIEW vViewToInstance0,
                            zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_ERD_Migrate( zVIEW vViewToInstance0,
                       zPVIEW vViewToInstance1,
                       zVIEW vSubtaskforDomainMigrate2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_MergeSA_ToER( zVIEW vViewToInstance0,
                        zVIEW vvSourceERD1,
                        zVIEW vSourceSA2,
                        zPCHAR pchMergeType3,
                        zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_CompareDataModels( zVIEW vViewToInstance0,
                             zVIEW vOtherERD1,
                             zVIEW vCurrentLPLR2,
                             zVIEW vOtherLPLR3,
                             zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_SetAttributeSequence( zVIEW vViewtoInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_NewAttributeSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DelAttribFromSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_SortAttributes( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_MoveAttribInSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierInitLevels( zVIEW vViewToInstance0,
                             zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierCopyLevelSub( zVIEW vViewToInstance0,
                               zVIEW vvTZEREMDO_Source1,
                               zVIEW vvTZEREMDOflat2,
                               zLONG lbAsChild3,
                               zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierAddSiblingLevel( zVIEW vViewToInstance0,
                                  zVIEW vvTZEREMDOflat1,
                                  zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierCopyLevel( zVIEW vViewToInstance0,
                            zVIEW vvTZERMDO_Source1,
                            zLONG lbAsChild2,
                            zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierDeleteLevel( zVIEW vViewToInstance0,
                              zVIEW vvTZEREMDOflat1,
                              zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierAddChildLevel( zVIEW vViewToInstance0,
                                zVIEW vvTZEREMDOflat1,
                                zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierRemoveChildLvl( zVIEW vViewToInstance0,
                                 zVIEW vvTZEREMDOflat1,
                                 zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierAddAttribute( zVIEW vViewToInstance0,
                               zSHORT nbUseRecursiveSide1,
                               zSHORT nbIncudeER_ATTRIBUTE2,
                               zVIEW vvERD_ATTR3,
                               zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierSyncLevelsF2R( zVIEW vViewToInstance0,
                                zVIEW vvTZEREMDOrecurs1,
                                zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierSyncLevelsR2F( zVIEW vViewToInstance0,
                                zVIEW vvTZEREMDOflat1,
                                zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierSetCounts( zVIEW vViewToInstance0,
                            zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimSetLevelByZKeys( zVIEW vViewToInstance0,
                              zLONG llZKey1,
                              zLONG llParentZkey2,
                              zPSHORT nbFound3,
                              zVIEW vSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_DimHierRemoveFlatSide( zVIEW vViewToInstance0,
                                 zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_ERD_RelationshipCopy( zVIEW vViewToInstance0,
                                zVIEW vOldERD1,
                                zVIEW vvSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_ERD_Compare( zVIEW vTargetERD0,
                       zVIEW vSourceERD1 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_ERD_Merge( zVIEW vViewToInstance0,
                     zVIEW vSourceERD1,
                     zVIEW vvSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZEREMDO_GenerateID_Identifiers( zVIEW vViewToInstance0 );

//end
//start TZ__OPRS 2007.05.08 17:23:23
zOPER_EXPORT zPCHAR OPERATION
ParseLine4( zPCHAR pchLineToParse0,
            zPCHAR pchParm11,
            zPCHAR pchParm22,
            zPCHAR pchParm33,
            zPCHAR pchParm44 );

zOPER_EXPORT zSHORT OPERATION
CopyOperationCode( zVIEW vApplicationView0,
                   zPCHAR pchTargetFileName1,
                   zPCHAR pchSourceFileName2,
                   zPCHAR pchOperationName3 );

zOPER_EXPORT zSHORT OPERATION
InsertSpacesInPrompt( zPCHAR lpReturnString,
                      zVIEW  vDialog,
                      zPCHAR lpOriginalString,
                      zLONG  lMaxLength );

zOPER_EXPORT zSHORT OPERATION
GetStringFromControlBlob( zPCHAR pchlpReturnedStringLeng0,
                          zVIEW vvDialog1,
                          zLONG llMaxLength2,
                          zPCHAR pchC_VariableName3 );

zOPER_EXPORT zSHORT OPERATION
WL_QC( zVIEW vDialog0,
       zLONG llFile1,
       zPCHAR pchBuffer2,
       zPCHAR pchCharacterToConvert3,
       zSHORT nAddBlankLineCount4 );

zOPER_EXPORT zSHORT OPERATION
GetStrFromAttrByContext( zPCHAR pchReturnedValue0,
                         zLONG lLength1,
                         zVIEW vView2,
                         zPCHAR pchEntityName3,
                         zPCHAR pchAttributeName4,
                         zPCHAR pchContext5 );

zOPER_EXPORT zSHORT OPERATION
DBH_ActivateOI_FromXML( zPVIEW vViewtoread0,
                        zPCHAR pchLODname1,
                        zVIEW vSubtask2,
                        zPCHAR pchFilename3,
                        zLONG lFlags4 );

zOPER_EXPORT zSHORT OPERATION
DBH_WriteOI_ToXML( zVIEW vViewtowrite0,
                   zPCHAR pchFilename1,
                   zLONG lFlags2 );

zOPER_EXPORT zSHORT OPERATION
ConvertStringToQSName( zPCHAR pchInputString0 );

zOPER_EXPORT zLONG OPERATION
zGetTickCount( zLONG ldummyint0 );

zOPER_EXPORT zSHORT OPERATION
StartZeidonHelp( zVIEW vvWindow0,
                 zPCHAR pchTagname1 );

zOPER_EXPORT zSHORT OPERATION
MergeGlobalPrototypes( zVIEW vvMeta0,
                       zPCHAR pchszMetaName1,
                       zPCHAR pchszRootEntityName2,
                       zVIEW vvTaskLPLR3 );

zOPER_EXPORT zSHORT OPERATION
ConvertIntegerToString( zLONG lnIntegerValue0,
                        zPCHAR pchszStringValue1,
                        zLONG lnLength2 );

zOPER_EXPORT zLONG OPERATION
GetStringLength( zPCHAR pchszStringValue0 );

zOPER_EXPORT zSHORT OPERATION
CheckDuplicateEntityByString( zVIEW vView0,
                              zPCHAR pchEntityName1,
                              zPCHAR pchAttributeName2,
                              zPCHAR pchStringValue3,
                              zPCHAR pchScopingEntityName4 );

zOPER_EXPORT zSHORT OPERATION
MiGetObjectNameForViewx( zPCHAR pchszReturnName0,
                         zVIEW vvView1 );

zOPER_EXPORT zSHORT OPERATION
TranslateStringToUpperCase( zPCHAR pchStringToTranslate0 );

zOPER_EXPORT zSHORT OPERATION
zDeleteFile( zPCHAR pchFullyqualifiedfilena0 );

zOPER_EXPORT zSHORT OPERATION
RefreshDiagram( zVIEW vERDWindowview0,
                zPCHAR pchControlNameERD1,
                zLONG lFlag0permitrefresh1bloc2 );

zOPER_EXPORT zSHORT OPERATION
TransferToEditor( zVIEW vSubtask0,
                  zVIEW vMeta1,
                  zPCHAR pchInvokingType2,
                  zLONG lInvokingCommand3 );

zOPER_EXPORT zSHORT OPERATION
zgSortEntityWithinParent4( zVIEW vView0,
                           zPCHAR pchEntityName1,
                           zPCHAR pchAttributeName2,
                           zSHORT nzASCENDINGorzDESCENDIN3,
                           zPCHAR pchAttributeName24,
                           zSHORT nzASCENDINGorzDESCENDIN5,
                           zPCHAR pchAttributeName36,
                           zSHORT nzASCENDINGorzDESCENDIN7,
                           zPCHAR pchAttributeName48,
                           zSHORT nzASCENDINGorzDESCENDIN9 );

zOPER_EXPORT zSHORT OPERATION
zgSortEntityWithinParent( zSHORT nzASCENDINGorzDESCENDIN0,
                          zVIEW vView1,
                          zPCHAR pchEntityName2,
                          zPCHAR pchAttributeName13,
                          zPCHAR pchAttributeName24 );

zOPER_EXPORT zSHORT OPERATION
zgSortEntityWithinGParent4( zVIEW vView0,
                            zPCHAR pchParentEntityName1,
                            zPCHAR pchEntityName2,
                            zPCHAR pchAttributeName3,
                            zSHORT nzASCENDINGorzDESCENDIN4,
                            zPCHAR pchAttributeName25,
                            zSHORT nzASCENDINGorzDESCENDIN6,
                            zPCHAR pchAttributeName37,
                            zSHORT nzASCENDINGorzDESCENDIN8,
                            zPCHAR pchAttributeName49,
                            zSHORT nzASCENDINGorzDESCENDIN10 );

zOPER_EXPORT zSHORT OPERATION
zgCompressName( zPCHAR pchLongName0,
                zPCHAR pchShortName1,
                zSHORT nShortNameLth2,
                zPCHAR pchSpaceReplace3,
                zPCHAR pchUnderscoreMode4,
                zPCHAR pchLowerVowels5,
                zPCHAR pchOtherChars6,
                zSHORT nPhasesToForce7 );

zOPER_EXPORT zSHORT OPERATION
zAnsiUpper( zPCHAR pchStringToConvert0 );

zOPER_EXPORT zSHORT OPERATION
SourceFileReadLine( zVIEW  lpTaskView,
                    zLONG  hFile,
                    zPCHAR pchLine );

//end
//start TZVSECAA 2005.01.14 13:48:19
zOPER_EXPORT zLONG OPERATION
Exec_Go( zVIEW vView0 );

zOPER_EXPORT zSHORT OPERATION
StageBrowser( zVIEW vSubtaskview0,
              zVIEW vViewtodisplay1 );

zOPER_EXPORT zLONG OPERATION
Exec_StepOnce( zVIEW vView0 );

zOPER_EXPORT zLONG OPERATION
Exec_StepForward( zVIEW vView0 );

zOPER_EXPORT zLONG OPERATION
Exec_Skip( zVIEW vView0 );

zOPER_EXPORT zSHORT OPERATION
Exec_ResumeFromDebugger( zVIEW vView0,
                         zPCHAR sString1,
                         zVIEW vAppView2 );

//end


//start TZRPSRCO 2016.08.23 10:53:34
zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_AutodesignReport( zVIEW vViewToInstance0,
                            zVIEW vvUserSpec1,
                            zVIEW vvPE2,
                            zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_CreatePageFooter( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_CreatePageHeader( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_DeleteGroupSet( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_CreateFieldsForGrpSet( zVIEW vvReportDef0,
                                 zVIEW vvDrivingLOD1 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_DeleteNonDisplayEntsR( zVIEW vvReportDefRecurs0 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_CrtePartialLODStructR( zVIEW vViewToInstance0,
                                 zVIEW vvReportDefRecurs1,
                                 zVIEW vvDrivingLOD2 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_CreateEntityGroupSet( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_InitReportStructure( zVIEW vvReportDef0 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_InitReportStructureR( zVIEW vViewToInstance0,
                                zVIEW vvReportDefRecurs1,
                                zVIEW vvDrivingLOD2 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_BuildReportDispObject( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_BuildReportDispObjectR( zVIEW vViewToInstance0,
                                  zVIEW vvReportDefTarget1 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_GenerateXRP( zPVIEW vViewToInstance0,
                       zVIEW vDialogWindowSource1 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_ChangeRepFileContents( zVIEW vViewToInstance0,
                                 zVIEW vCurrentLPLR1,
                                 zPCHAR pchszPathName12,
                                 zPCHAR pchszPathName23,
                                 zPCHAR pchszFileName4,
                                 zPCHAR pchszExtension5,
                                 zSHORT nnFunction6,
                                 zVIEW vSubtask7 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_ReportCopy( zPVIEW vViewToInstance0,
                      zVIEW vSourceReport1,
                      zVIEW vSourceLPLR2,
                      zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_ReportRelinkDelete( zVIEW vViewToInstance0,
                              zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_ReportMigrate( zPVIEW vViewToInstance0,
                         zPCHAR pchSourceReportMetaName1,
                         zVIEW vSourceLPLR2,
                         zVIEW vSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_AutodesignReportEntity( zVIEW vSubtask0,
                                  zVIEW vViewToInstance1,
                                  zVIEW vvUserSpec2,
                                  zVIEW vvUserSpecRoot3,
                                  zVIEW vvPE4 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_FormatDocPage( zVIEW vViewToWindow0,
                         zLONG lPageNbr1,
                         zLONG lPageWidth2,
                         zLONG lPageHeight3 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_FormatSubobjectForDef( zVIEW vViewToInstance0,
                                 zVIEW vvSubtask1,
                                 zVIEW vvSourceOI2,
                                 zPCHAR pchszReportDefName3,
                                 zPCHAR pchszSubobjectEntityNam4,
                                 zLONG llPreviewFlag5,
                                 zLONG llPrintDialogFlag6,
                                 zLONG llPrintFlags7 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_FormatReportGroupSets( zVIEW vViewToInstance0,
                                 zLONG lPageNbr1,
                                 zLONG lPageWidth2,
                                 zLONG lPageHeight3 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_GenerateXSLT_XML( zVIEW vViewToInstance0,
                            zPCHAR pchReportName1,
                            zPCHAR pchXMLFileName2,
                            zPCHAR pchSubobjectEntityName3 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_GenerateXML_LODRecurs( zVIEW vvReportDef0,
                                 zVIEW vvReportDefRecurs1,
                                 zVIEW vvLOD2,
                                 zPCHAR pchszOutputLine3,
                                 zLONG llFileHandle4,
                                 zPCHAR pchszIndentChars5 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_BuildCtrlsInRows( zVIEW vViewToInstance0,
                                 zVIEW vvReportDef1,
                                 zVIEW vvLOD2,
                                 zLONG llFileHandle3,
                                 zPCHAR pchszOutputLine4,
                                 zPCHAR pchszIndentationChars5 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_BuildBlockData( zVIEW vvReportDefRoot0,
                               zVIEW vvReportDef1,
                               zVIEW vvLOD2,
                               zLONG llFileHandle3,
                               zPCHAR pchszOutputLine4,
                               zPCHAR pchszIndentationChars5,
                               zLONG lGroupHierarchicalLevel6 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_BuildControl( zVIEW vViewToInstance0,
                             zVIEW vvReportDef1,
                             zLONG llFileHandle2,
                             zPCHAR pchszOutputLine3,
                             zPCHAR pchszIndentationChars4 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_BuildTable( zVIEW vvReportDefRoot0,
                           zVIEW vvReportDef1,
                           zVIEW vvLOD2,
                           zLONG llFileHandle3,
                           zPCHAR pchszOutputLine4,
                           zPCHAR pchszIndentationChars5,
                           zLONG lGroupHierarchicalLevel6,
                           zLONG lTableMarginTop7,
                           zLONG lTableWidth8 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_EntityRecur( zVIEW vViewToInstance0,
                            zVIEW vvReportRecurs1,
                            zVIEW vvLOD2,
                            zLONG llFileHandle3,
                            zPCHAR pchszOutputFile4,
                            zPCHAR pchIndentationChars5,
                            zPCHAR pchszTopEntityName6 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_GetStyleShape( zVIEW vViewToInstance0,
                              zPCHAR pchszStyle1 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_GetStyleText( zVIEW vViewToInstance0,
                             zPCHAR pchszStyle1 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_GroupRecur( zVIEW vViewToInstance0,
                           zVIEW vvReportDef1,
                           zVIEW vvLOD2,
                           zLONG llFileHandle3,
                           zPCHAR pchszOutputLine4,
                           zPCHAR pchszIndentationChars5,
                           zLONG lGroupHierarchicalLevel6 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_GroupTable( zVIEW vViewToInstance0,
                           zVIEW vvReportDef1,
                           zLONG llFileHandle2,
                           zPCHAR pchszOutputLine3,
                           zPCHAR pchszIndentationChars4,
                           zLONG lRowCount5,
                           zPCHAR pchszForEachName6 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_HeaderFooter( zVIEW vViewToInstance0,
                             zVIEW vvLOD1,
                             zLONG llFileHandle2,
                             zPCHAR pchszOutputLine3,
                             zPCHAR pchszIndentationChars4,
                             zPCHAR pchszForEachName5 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_MainHeader( zVIEW vViewToInstance0,
                           zLONG llFileHandle1,
                           zPCHAR pchszOutputLine2 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_XSLT_BuildCtrlsAsTable( zVIEW vViewToInstance0,
                                  zVIEW vvReportDef1,
                                  zVIEW vvLOD2,
                                  zLONG llFileHandle3,
                                  zPCHAR pchszOutputLine4,
                                  zPCHAR pchszIndentationChars5,
                                  zLONG lGroupHierarchicalLevel6 );

zOPER_EXPORT zSHORT OPERATION
oTZRPSRCO_GenerateXSLT( zVIEW vViewToInstance0 );

//end

//start TZ__PRFO 2016.08.23 10:53:24
zOPER_EXPORT zSHORT OPERATION
oTZ__PRFO_GetViewToProfile( zPVIEW vViewToInstance0,
                            zPCHAR pchToolID1,
                            zVIEW vViewToWindow2,
                            zSHORT nCurrentOrReloadFlag3 );

//end
//start TZZOLODO 2016.08.23 10:53:37
zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_ParseDerivedExpr( zVIEW vViewToInstance0,
                            zVIEW vWindowsubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_DeleteOldPOD_Entities( zVIEW vViewToInstance0,
                                 zVIEW vTZTENVRO1 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_DeleteAllPOD_Entities( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_Constraint( zVIEW vViewToWindow0,
                      zVIEW vViewToInstance1,
                      zSHORT nEvent2,
                      zSHORT nState3 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_ConstraintOperACC( zVIEW vViewtoInstance0,
                             zPCHAR pchNameOfEntity1,
                             zSHORT nEvent2,
                             zSHORT nState3 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_AddEntity( zVIEW vViewToWindow0,
                     zVIEW vViewToInstance1,
                     zPCHAR pchEntityType2 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_LOD_EntityCopy( zVIEW vViewToInstance0,
                          zVIEW vNewRecursiveLOD1,
                          zVIEW vOldMainLOD2,
                          zVIEW vOldRecursiveLOD3,
                          zVIEW vSourceLPLR4,
                          zVIEW vCurrentLPLR5,
                          zVIEW vNewERD6,
                          zVIEW vOrigERD7,
                          zVIEW vNewDTE8,
                          zVIEW vvSubtask9,
                          zPCHAR pchParentName10,
                          zPCHAR pchszAddER_EntityFlag11 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_LOD_CreateER_Attribute( zVIEW vOldRecursiveLOD0,
                                  zVIEW vSourceLPLR1,
                                  zVIEW vCurrentLPLR2,
                                  zVIEW vNewERD3,
                                  zVIEW vvSubtask4 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_LOD_AttributeCopy( zVIEW vViewToInstance0,
                             zVIEW vNewMainLOD1,
                             zVIEW vNewRecursiveLOD2,
                             zVIEW vOldMainLOD3,
                             zVIEW vOldRecursiveLOD4,
                             zVIEW vSourceLPLR5,
                             zVIEW vCurrentLPLR6,
                             zVIEW vNewERD7,
                             zPCHAR pchszAddER_AttributeFla8 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_LOD_OperationCopy( zVIEW vViewToInstance0,
                             zVIEW vViewToNewLOD1,
                             zVIEW vViewToOldLOD2,
                             zVIEW vSourceLPLR3 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_AttributeConstraints( zVIEW vViewtoInstance0,
                                zPCHAR pchNameOfEntity1,
                                zSHORT nEvent2,
                                zSHORT nState3 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_LOD_Migrate( zVIEW vViewToInstance0,
                       zPCHAR pchSourceLODMetaName1,
                       zVIEW vSourceLPLR2,
                       zVIEW vvSubtask3 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_LOD_RelinkDelete( zVIEW vSubtask0,
                            zVIEW vViewToInstance1 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_SetAttributeSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_NewAttributeSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_DelAttribFromSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_SortAttributes( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_MoveAttribInSequence( zVIEW vViewToInstance0 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_LOD_Compare( zVIEW vTargetLOD0,
                       zVIEW vSourceLOD1 );

zOPER_EXPORT zSHORT OPERATION
oTZZOLODO_LOD_Merge( zVIEW vViewToInstance0,
                     zVIEW vSourceLOD1,
                     zVIEW vvSubtask2 );

//end
//start TZTEMPMO 2016.08.23 10:53:35
zOPER_EXPORT zSHORT OPERATION
oTZTEMPMO_Create( zPVIEW vvMPM0,
                  zVIEW vvEMD_in1,
                  zVIEW vvTE_in2 );

//end

zOPER_EXPORT zSHORT OPERATION
oTZCMCPRO_CPLR_Enqueue( zVIEW  vTZCMCPRO,
                        zVIEW  vSubtask,
                        zSHORT EnqueueType );

//start TZCMCPRO 2016.08.23 10:53:27
zOPER_EXPORT zSHORT OPERATION
oTZCMCPRO_ActivateCPLR( zPVIEW vTZCMCPRO0,
                        zLONG llZKey1,
                        zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZCMCPRO_CleanUpER_TE_SA( zVIEW vTZCMCPRO0,
                           zVIEW vTZCMLPLO_In1 );

zOPER_EXPORT zSHORT OPERATION
oTZCMCPRO_CPLR_Enqueue( zVIEW vTZCMCPRO0,
                        zVIEW vSubtask1,
                        zSHORT nEnqueueType2 );

//end
//start TZCMLPLO 2016.08.23 10:53:28
zOPER_EXPORT zSHORT OPERATION
oTZCMLPLO_CheckOI_ForDupZKey( zVIEW vViewToInstance0,
                              zVIEW vViewSubjectOI1,
                              zPCHAR pchszRootEntityName2 );

zOPER_EXPORT zSHORT OPERATION
oTZCMLPLO_GenerateCallHeader( zVIEW vViewToInstance0,
                              zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZCMLPLO_GenerateTransShell( zVIEW vViewToInstance0,
                              zVIEW vSubtask1 );

zOPER_EXPORT zSHORT OPERATION
oTZCMLPLO_CompilerMigrate( zVIEW vViewToInstance0,
                           zVIEW vvSourceLPLR1,
                           zVIEW vSubtask2 );

zOPER_EXPORT zSHORT OPERATION
oTZCMLPLO_HeaderMigrate( zVIEW vViewToInstance0,
                         zPCHAR pchSourceHeaderMetaName1,
                         zPVIEW vReturnedTargetHeader2,
                         zVIEW vSubtask3 );

//end
//start ZDRAPP 2006.12.11 16:03:21
zOPER_EXPORT zSHORT OPERATION
zkCancel( zVIEW vSubtask0 );

zOPER_EXPORT zSHORT OPERATION
SaveActiveCtrlToCSV( zVIEW vvSubtask0 );

zOPER_EXPORT zSHORT OPERATION
zkCtrlInfo( zVIEW vSubtask0 );

zOPER_EXPORT zSHORT OPERATION
zkExitCloseOK( zVIEW vSubtask0 );

zOPER_EXPORT zLONG OPERATION
zkSelectAll( zVIEW vSubtask0 );

zOPER_EXPORT zLONG OPERATION
fnPainterCall( zSHORT nMessageType0,
               zVIEW vSubtaskView1,
               zVIEW vDialogView2,
               zPCHAR pchWindowName3,
               zLONG  lMaxLth );

zOPER_EXPORT zSHORT OPERATION
HotkeyToPainter( zVIEW vViewToWindow0 );

zOPER_EXPORT zSHORT OPERATION
InvokeReportExitCode( zVIEW vSubtask0,
                      zVIEW vReportDef1,
                      zPCHAR pchOperationName2,
                      zSHORT nEvent3,
                      zSHORT nCurrentPage4,
                      zVIEW vDrivingOI5 );

zOPER_EXPORT zSHORT OPERATION
IsValidView( zVIEW vvAny0 );

zOPER_EXPORT zLONG OPERATION
ListSubtasks( zVIEW vSubtask0 );

zOPER_EXPORT zSHORT OPERATION
MakeViewFromInteger( zPVIEW vReturnedView0,
                     zLONG lViewSavedAsInteger1 );

zOPER_EXPORT zLONG OPERATION
MakeIntegerFromView( zVIEW vAnyView0 );

zOPER_EXPORT zSHORT OPERATION
PrintActiveWindow( zVIEW vSubtask0 );

zOPER_EXPORT zSHORT OPERATION
TraceLineHex( zPCHAR pchTitle0,
              zLONG lValue1 );

//end
//start TZSIOPRS 2002.08.23 13:26:37
zOPER_EXPORT zSHORT OPERATION
GetSironWorkObjPathName( zPCHAR pchDirectoryPathNameRetur0,
                         zLONG lLengthofDirectoryPathNa1 );

zOPER_EXPORT zSHORT OPERATION
SironCreateDataModel( zVIEW vViewToWindow0,
                      zPVIEW vERD1 );

zOPER_EXPORT zSHORT OPERATION
SearchSpecialCharacter( zPCHAR pchFieldName0,
                        zPCHAR pchSpecChar1 );

zOPER_EXPORT zSHORT OPERATION
SetWSKInLod( zVIEW vViewToWindow0,
             zVIEW vAktView1,
             zPCHAR pchFilename2 );

zOPER_EXPORT zSHORT OPERATION
LoadSironDLLs( zVIEW vViewToWindow0 );

zOPER_EXPORT zSHORT OPERATION
FreeHZVAFFZ(  void );

zOPER_EXPORT zSHORT OPERATION
BuildWSK( zVIEW vViewToWindow0,
          zVIEW vAktView1,
          zPCHAR pchServerName2,
          zPCHAR pchCatFile3,
          zPCHAR pchCatalogName4,
          zPCHAR pchFilename5 );

zOPER_EXPORT zSHORT OPERATION
GetAllCatalogNames( zVIEW vViewToWindow0,
                    zVIEW vAktView1 );

zOPER_EXPORT zSHORT OPERATION
GetAllServerNames( zVIEW vViewToWindow0,
                   zVIEW vAktView1 );

zOPER_EXPORT zSHORT OPERATION
CreateSironWorkObjectList( zPCHAR pchDirecoryPathforSironwo0,
                           zVIEW vSubtask1 );

//end

//start TZPESRCO 2016.08.23 10:53:33
zOPER_EXPORT zSHORT OPERATION
oTZPESRCO_MigratePPE( zPVIEW vViewToInstance0,
                      zVIEW vSourceLPLR1,
                      zVIEW vTaskView2 );

zOPER_EXPORT zSHORT OPERATION
oTZPESRCO_MergePPE( zVIEW vNewPPE0,
                    zVIEW vSourceLPLR1,
                    zVIEW vvSubtask2 );

//end

//start TZADWEXP 2013.01.30 09:53:24
zOPER_EXPORT zSHORT OPERATION
ADW_Exp_ReplaceHex( zPCHAR pchTarget0,
                    zULONG lTargetLen1,
                    zPCHAR pchSearch2,
                    zPCHAR pchReplace3 );

zOPER_EXPORT zLONG OPERATION
SetRptShapeFromBlob( zVIEW vvReportDef0 );

zOPER_EXPORT zLONG OPERATION
GetBorderLineWidth( zLONG llBorderStyle0,
                    zPCHAR pchszWidth1 );

zOPER_EXPORT zSHORT OPERATION
ReplaceSpecialCharacter( zPCHAR pchTarget0,
                         zULONG lTargetLen1,
                         zPCHAR pchSearch2,
                         zPCHAR pchReplace3 );

//end
//start KZDRVRAA 2006.04.03 19:23:30
zOPER_EXPORT zLONG OPERATION
fnPainterCall( zSHORT nMessageType0,
               zVIEW vSubtaskView1,
               zVIEW vDialogView2,
               zPCHAR pchWindowName3,
               zLONG  lMaxLth );

zOPER_EXPORT zSHORT OPERATION
PrintActiveWindow( zVIEW vSubtask0 );

//end
//start KZRPQUER 2002.08.23 13:26:37
zOPER_EXPORT zSHORT OPERATION
ComputeQueryOperationValue( zVIEW vReportDef0,
                            zVIEW vQueryOI1,
                            zPCHAR pchReturnedString2,
                            zPCHAR pchOperationName3,
                            zPCHAR pchEntityName4,
                            zPCHAR pchAttributeName5 );

//end
//start VIDEOGBL 2002.08.23 13:26:38
zOPER_EXPORT zSHORT OPERATION
AddDaysToDate( zVIEW vViewToInstance0,
               zPCHAR eViewEntityName1,
               zPCHAR aViewAttributeName2,
               zSHORT nNumberOfDays3 );

//end
//start KZXMLPGO 2016.08.23 10:53:24
zOPER_EXPORT zSHORT OPERATION
oKZXMLPGO_InitWebSessionObject( zPVIEW vViewToInstance0,
                                zVIEW vAnyView1,
                                zPCHAR pchUserID2 );

zOPER_EXPORT zSHORT OPERATION
oKZXMLPGO_InitWebPage( zVIEW vvKZXMLWDO0,
                       zPCHAR pchDialogName1,
                       zPCHAR pchWindowName2 );

zOPER_EXPORT zSHORT OPERATION
oKZXMLPGO_AddWebControlSubobject( zVIEW vViewToInstance0,
                                  zPCHAR pchControlName1,
                                  zPCHAR pchControlType2,
                                  zPCHAR pchControlContext3,
                                  zPCHAR pchSourceViewName4,
                                  zPCHAR pchSourceEntity5,
                                  zPCHAR pchSourceAttribute6,
                                  zPCHAR pchAutoComboBoxExternal7 );

//end
//start ACCOUNT 2016.04.08 10:33:54
zOPER_EXPORT zSHORT OPERATION
test( zVIEW vViewtoInstance0,
      zSHORT nEvent1,
      zSHORT nState2 );

//end
//start TZWEBGL1 2012.06.20 15:14:43
zOPER_EXPORT zVOID OPERATION
GenJSP_TableExport( zVIEW vvDialog0,
                    zLONG llFile1,
                    zPCHAR pchszWriteBuffer2,
                    zPCHAR pchszNoPositioning3 );

zOPER_EXPORT zVOID OPERATION
CreateNoPosStyleString( zVIEW vDialog0,
                        zPCHAR pchStyle1,
                        zPCHAR pchStyleExtraParm2 );

zOPER_EXPORT zVOID OPERATION
CreateDisabledString( zVIEW vvSubtask0,
                      zPCHAR pchDisabledString1 );

zOPER_EXPORT zVOID OPERATION
CreateAbsolPosStringTable( zVIEW vView0,
                           zPCHAR pchStyle1,
                           zLONG lX_BASE2,
                           zLONG lY_BASE3 );

zOPER_EXPORT zVOID OPERATION
GenJSP_Action( zVIEW vDialog0,
               zVIEW vDialogRoot1,
               zLONG lFile2,
               zPCHAR pchWriteBuffer3,
               zPCHAR pchFormName4,
               zPCHAR pchActionName5,
               zLONG llTraceLevel6 );

zOPER_EXPORT zSHORT OPERATION
CreateRelPosString( zVIEW vDialog0,
                    zPCHAR pchStyle1,
                    zLONG lX_BASE2,
                    zLONG lY_BASE3 );

zOPER_EXPORT zSHORT OPERATION
CreateAbsolPosString( zVIEW vDialog0,
                      zPCHAR pchStyle1,
                      zLONG lX_BASE2,
                      zLONG lY_BASE3 );

zOPER_EXPORT zSHORT OPERATION
CreateSizeString( zVIEW vDialog0,
                  zPCHAR pchStyle1 );

zOPER_EXPORT zSHORT OPERATION
CreateRelStyleString( zVIEW vDialog0,
                      zPCHAR pchStyle1,
                      zLONG lX_BASE2,
                      zLONG lY_BASE3,
                      zPCHAR pchStyleExtraParm4 );

zOPER_EXPORT zVOID OPERATION
CreateAbsolStyleString( zVIEW vDialog0,
                        zPCHAR pchStyle1,
                        zLONG lX_BASE2,
                        zLONG lY_BASE3,
                        zPCHAR pchStyleExtraParm4 );

zOPER_EXPORT zSHORT OPERATION
FixStyleString( zPCHAR pchStyle0,
                zPCHAR pchS11,
                zPCHAR pchS22,
                zPCHAR pchSE3 );

zOPER_EXPORT zSHORT OPERATION
PIX_PER_DU( zVIEW vDialog0,
            zPDECIMAL mDLUnits1 );

zOPER_EXPORT zVOID OPERATION
GenJSP_OutputMapRecurs( zVIEW vDialog0,
                        zLONG lFile1,
                        zPCHAR pchWriteBuffer2,
                        zPCHAR pchFormName3 );

zOPER_EXPORT zVOID OPERATION
GenJSP_InputMapRecurs( zVIEW vDialog0,
                       zPCHAR pchViewName1,
                       zLONG lFile2,
                       zPCHAR pchWriteBuffer3,
                       zLONG lTableRowCnt4 );

zOPER_EXPORT zLONG OPERATION
GenJSP_CrteCtrlsRecurs( zVIEW vDialog0,
                        zVIEW vGroupParent1,
                        zVIEW vDialogRoot2,
                        zLONG lFile3,
                        zPCHAR pchWriteBuffer4,
                        zPCHAR pchIndent5,
                        zLONG lTableRowCnt6,
                        zPCHAR pchNoPositioning7,
                        zLONG lOffsetX8,
                        zLONG lOffsetY9 );

//end
//start TZWEBGL2 2016.04.21 16:14:14
zOPER_EXPORT zVOID OPERATION
GenJSPJ_OutputMapRecurs( zVIEW vDialog0,
                         zLONG lFile1,
                         zPCHAR pchWriteBuffer2,
                         zPCHAR pchFormName3,
                         zPCHAR pchstrRepeatingGrpKey4 );

zOPER_EXPORT zLONG OPERATION
GenJSPJ_CrteCtrlsRecurs( zVIEW vDialog0,
                         zVIEW vGroupParent1,
                         zVIEW vDialogRoot2,
                         zLONG lFile3,
                         zPCHAR pchWriteBuffer4,
                         zPCHAR pchIndent5,
                         zLONG lTableRowCnt6,
                         zPCHAR pchNoPositioning7,
                         zLONG lOffsetX8,
                         zLONG lOffsetY9,
                         zPCHAR pchstrEntityKey10 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_InputMapRecurs( zVIEW vDialog0,
                        zPCHAR pchViewName1,
                        zLONG lFile2,
                        zPCHAR pchWriteBuffer3,
                        zLONG lTableRowCnt4,
                        zPCHAR pchszRepeatingGrpKey5 );

zOPER_EXPORT zSHORT OPERATION
GenJSPJ_Action( zVIEW vDialog0,
                zVIEW vDialogRoot1,
                zLONG lFile2,
                zPCHAR pchWriteBuffer3,
                zPCHAR pchFormName4,
                zPCHAR pchActionName5,
                zLONG llTraceLevel6 );

//end
//start TZWEBGL3 2012.07.17 16:38:20
zOPER_EXPORT zSHORT OPERATION
BuildMainNavSection( zVIEW vDialog0,
                     zVIEW vDialogRoot1,
                     zLONG lFile2 );

zOPER_EXPORT zVOID OPERATION
GenJSP_CrteJPG( zVIEW vDialog0,
                zLONG lFile1,
                zPCHAR pchWriteBuffer2,
                zPCHAR pchIndent3,
                zPCHAR pchCtrlTag4,
                zPCHAR pchNoPositioning5,
                zLONG lOffsetX6,
                zLONG lOffsetY7 );

zOPER_EXPORT zVOID OPERATION
GenJSP_ChildFunctions( zVIEW vDialog0,
                       zLONG lFile1,
                       zPCHAR pchWriteBuffer2,
                       zPCHAR pchFormName3 );

zOPER_EXPORT zVOID OPERATION
GenJSP_CrteGroupTable( zVIEW vvDialog0,
                       zVIEW vGroupParent1,
                       zVIEW vDialogRoot2,
                       zLONG lFile3,
                       zPCHAR pchWriteBuffer4,
                       zPCHAR pchIndent5,
                       zLONG lTableRowCnt6,
                       zPCHAR pchNoPositioning7 );

zOPER_EXPORT zVOID OPERATION
GenJSP_CrteComboBox( zVIEW vDialog0,
                     zLONG lFile1,
                     zPCHAR pchWriteBuffer2,
                     zPCHAR pchIndent3,
                     zPCHAR pchCtrlTag4,
                     zPCHAR pchTableRowFlag5,
                     zPCHAR pchNoPositioning6,
                     zLONG lOffsetX7,
                     zLONG lOffsetY8 );

zOPER_EXPORT zSHORT OPERATION
GenJSP_CrteEditBox( zVIEW vDialog0,
                    zLONG lFile1,
                    zPCHAR pchWriteBuffer2,
                    zPCHAR pchIndent3,
                    zPCHAR pchCtrlTag4,
                    zPCHAR pchTableRowFlag5,
                    zPCHAR pchJustify6,
                    zPCHAR pchNoPositioning7,
                    zLONG lOffsetX8,
                    zLONG lOffsetY9 );

zOPER_EXPORT zSHORT OPERATION
GenJSP_CrteCheckBox( zVIEW vDialog0,
                     zLONG lFile1,
                     zPCHAR pchWriteBuffer2,
                     zPCHAR pchIndent3,
                     zPCHAR pchCtrlTag4,
                     zPCHAR pchTableRowFlag5,
                     zPCHAR pchJustify6,
                     zPCHAR pchNoPositioning7,
                     zLONG lOffsetX8,
                     zLONG lOffsetY9 );

zOPER_EXPORT zSHORT OPERATION
GenJSP_CrteCtrlsRadio( zVIEW vDialog0,
                       zLONG lFile1,
                       zPCHAR pchWriteBuffer2,
                       zPCHAR pchIndent3,
                       zPCHAR pchRadioGroupName4,
                       zPCHAR pchNoPositioning5,
                       zLONG lOffsetX6,
                       zLONG lOffsetY7 );

zOPER_EXPORT zSHORT OPERATION
GenJSP_CrteText( zVIEW vDialog0,
                 zVIEW vGroupParent1,
                 zVIEW vDialogRoot2,
                 zLONG lFile3,
                 zPCHAR pchWriteBuffer4,
                 zPCHAR pchIndent5,
                 zPCHAR pchCtrlTag6,
                 zPCHAR pchJustify7,
                 zPCHAR pchNoPositioning8,
                 zLONG lOffsetX9,
                 zLONG lOffsetY10 );

zOPER_EXPORT zVOID OPERATION
GenJSP_CrteListBox( zVIEW vDialog0,
                    zLONG lFile1,
                    zPCHAR pchWriteBuffer2,
                    zPCHAR pchIndent3,
                    zPCHAR pchCtrlTag4,
                    zPCHAR pchNoPositioning5,
                    zLONG lOffsetX6,
                    zLONG lOffsetY7 );

zOPER_EXPORT zSHORT OPERATION
GenJSP_EmailEntries( zVIEW vvDialog0,
                     zVIEW vvDialogRoot1,
                     zLONG lFile2,
                     zPCHAR pchWriteBuffer3,
                     zPCHAR pchszFormName4 );

zOPER_EXPORT zVOID OPERATION
GenJSP_CrteCalendar( zVIEW vDialog0,
                     zLONG lFile1,
                     zPCHAR pchWriteBuffer2,
                     zPCHAR pchIndent3,
                     zPCHAR pchCtrlTag4,
                     zPCHAR pchTableRowFlag5,
                     zPCHAR pchJustify6,
                     zPCHAR pchNoPositioning7,
                     zLONG lOffsetX8,
                     zLONG lOffsetY9 );

zOPER_EXPORT zVOID OPERATION
GenJSP_MenuFunctions( zVIEW vDialog0,
                      zVIEW vDialogRoot1,
                      zLONG lFile2,
                      zPCHAR pchWriteBuffer3,
                      zPCHAR pchFormName4,
                      zPCHAR pchActionPrefix5 );

zOPER_EXPORT zSHORT OPERATION
BuildSideNavSection( zVIEW vDialog0,
                     zVIEW vDialogRoot1,
                     zLONG lFile2,
                     zPCHAR pchszReusableMenu3,
                     zVIEW vDialogMenu4 );

zOPER_EXPORT zSHORT OPERATION
CreateTabIndexString( zVIEW vDialog0,
                      zPCHAR pchTabIndex1 );

//end
//start TZWEBGL4 2016.11.10 13:12:41
zOPER_EXPORT zSHORT OPERATION
BuildSideNavSectionJ( zVIEW vvDialog0,
                      zVIEW vvDialogRoot1,
                      zLONG llFile2,
                      zPCHAR pchReusableMenu3,
                      zVIEW vvDialogMenu4 );

zOPER_EXPORT zSHORT OPERATION
GenJSPJ_CrteFileTransferForm( zVIEW vvDialog0,
                              zVIEW vvDialogRoot1,
                              zLONG lFile2,
                              zPCHAR pchWriteBuffer3,
                              zPCHAR pchIndent4,
                              zPCHAR pchNoPositioning5,
                              zLONG lOffsetX6,
                              zLONG lOffsetY7 );

zOPER_EXPORT zSHORT OPERATION
GenJSPJ_CrteListBoxAsList( zVIEW vvDialog0,
                           zLONG llFile1,
                           zPCHAR pchszWriteBuffer2,
                           zPCHAR pchszIndent3,
                           zPCHAR pchszCtrlTag4,
                           zPCHAR pchszNoPositioning5,
                           zLONG llOffsetX6,
                           zLONG llOffsetY7 );

zOPER_EXPORT zSHORT OPERATION
BuildMenuListJ( zVIEW vvDialog0,
                zVIEW vvDialogRoot1,
                zLONG llFile2,
                zPCHAR pchszMenuName3 );

zOPER_EXPORT zSHORT OPERATION
GenJSPJ_CrtePushButton( zVIEW vDialog0,
                        zVIEW vGroupParent1,
                        zLONG lFile2,
                        zPCHAR pchWriteBuffer3,
                        zPCHAR pchIndent4,
                        zPCHAR pchCtrlTag5,
                        zPCHAR pchTableRowFlag6,
                        zPCHAR pchJustify7,
                        zPCHAR pchNoPositioning8,
                        zLONG lOffsetX9,
                        zLONG lOffsetY10,
                        zPCHAR pchRepeatGrpKey11 );

zOPER_EXPORT zSHORT OPERATION
GenJSPJ_CrteMLEdit( zVIEW vvDialog0,
                    zLONG lFile1,
                    zPCHAR pchWriteBuffer2,
                    zPCHAR pchIndent3,
                    zPCHAR pchCtrlTag4,
                    zPCHAR pchTableRowFlag5,
                    zPCHAR pchJustify6,
                    zPCHAR pchNoPositioning7,
                    zLONG lOffsetX8,
                    zLONG lOffsetY9,
                    zPCHAR pchstrRepeatGrpKey10 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteListBox( zVIEW vvDialog0,
                     zLONG lFile1,
                     zPCHAR pchWriteBuffer2,
                     zPCHAR pchIndent3,
                     zPCHAR pchCtrlTag4,
                     zPCHAR pchNoPositioning5,
                     zLONG lOffsetX6,
                     zLONG lOffsetY7 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteJPG( zVIEW vDialog0,
                 zLONG lFile1,
                 zPCHAR pchWriteBuffer2,
                 zPCHAR pchIndent3,
                 zPCHAR pchCtrlTag4,
                 zPCHAR pchNoPositioning5,
                 zLONG lOffsetX6,
                 zLONG lOffsetY7 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteText( zVIEW vDialog0,
                  zVIEW vvGroupParent1,
                  zVIEW vvDialogRoot2,
                  zLONG lFile3,
                  zPCHAR pchWriteBuffer4,
                  zPCHAR pchIndent5,
                  zPCHAR pchCtrlTag6,
                  zPCHAR pchJustify7,
                  zPCHAR pchNoPositioning8,
                  zLONG lOffsetX9,
                  zLONG lOffsetY10,
                  zPCHAR pchszRepeatGrpKey11 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteEditBox( zVIEW vvDialog0,
                     zLONG lFile1,
                     zPCHAR pchWriteBuffer2,
                     zPCHAR pchIndent3,
                     zPCHAR pchCtrlTag4,
                     zPCHAR pchTableRowFlag5,
                     zPCHAR pchJustify6,
                     zPCHAR pchNoPositioning7,
                     zLONG lOffsetX8,
                     zLONG lOffsetY9,
                     zPCHAR pchstrRepeatGrpKey10 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteGroupTable( zVIEW vvDialog0,
                        zVIEW vvGroupParent1,
                        zVIEW vvDialogRoot2,
                        zLONG lFile3,
                        zPCHAR pchWriteBuffer4,
                        zPCHAR pchIndent5,
                        zLONG lTableRowCnt6,
                        zPCHAR pchNoPositioning7,
                        zPCHAR pchszRepeatingGroupKey8 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteCtrlsRadio( zVIEW vvDialog0,
                        zLONG llFile1,
                        zPCHAR pchWriteBuffer2,
                        zPCHAR pchIndent3,
                        zPCHAR pchRadioGroupName4,
                        zPCHAR pchNoPositioning5,
                        zLONG lOffsetX6,
                        zLONG lOffsetY7,
                        zPCHAR pchstrRepeatingGrpKey8 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteComboBox( zVIEW vvDialog0,
                      zLONG lFile1,
                      zPCHAR pchWriteBuffer2,
                      zPCHAR pchIndent3,
                      zPCHAR pchCtrlTag4,
                      zPCHAR pchTableRowFlag5,
                      zPCHAR pchNoPositioning6,
                      zLONG lOffsetX7,
                      zLONG lOffsetY8,
                      zPCHAR pchstrRepeatingGrpKey9 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteCheckBox( zVIEW vvDialog0,
                      zLONG lFile1,
                      zPCHAR pchWriteBuffer2,
                      zPCHAR pchIndent3,
                      zPCHAR pchCtrlTag4,
                      zPCHAR pchTableRowFlag5,
                      zPCHAR pchJustify6,
                      zPCHAR pchNoPositioning7,
                      zLONG lOffsetX8,
                      zLONG lOffsetY9,
                      zPCHAR pchstrRepeatingGrpKey10 );

zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteCalendar( zVIEW vvDialog0,
                      zLONG llFile1,
                      zPCHAR pchWriteBuffer2,
                      zPCHAR pchIndent3,
                      zPCHAR pchCtrlTag4,
                      zPCHAR pchTableRowFlag5,
                      zPCHAR pchJustify6,
                      zPCHAR pchNoPositioning7,
                      zLONG lOffsetX8,
                      zLONG lOffsetY9,
                      zPCHAR pchszRepeatGrpKey10 );

//end
//start KZRPSRCO 2012.06.21 12:41:38
zOPER_EXPORT zSHORT OPERATION
ConvertXML_SpecialCharacters( zVIEW vAnyView0,
                              zPCHAR pchReturnString1,
                              zPCHAR pchSourceString2,
                              zLONG lMaxReturnLth3 );

//end
