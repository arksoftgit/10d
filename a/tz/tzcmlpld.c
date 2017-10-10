/////////////////////////////////////////////////////////////////////////////
//
// MODULE NAME:   tzcmlpld.c - Zeidon workstation dialog operations
// DESCRIPTION:   This C file contains global and LOD operations for the
//                Zeidon workstation application.
//
// //////////////////////////////////////////////////////////////////////////
// * Copyright (c) 1995 - 2016 QuinSoft, Inc.   All rights reserved.        *
// * Confidential and Proprietary material subject to license - do not      *
// * reproduce or disclose.  This material is an unpublished work and       *
// * is considered a trade secret belonging to the copyright holder.        *
// //////////////////////////////////////////////////////////////////////////
//
// AUTHOR:        Gig Kirk
// DATE:          1992/09/30
// API:           MicroSoft foundation classes and Windows 3.1 SDK
// ENVIRONMENT:   Windows 3.1
// REVISION:      10B    1995/08/05
//
// LAST MESSAGE ID: CM00299
// LAST MESSAGE ID: CM00711
//
// HISTORY:
//
//    1995/08/05: Beginning of 10B branch
//
/////////////////////////////////////////////////////////////////////////////
//

/*
CHANGE LOG
2002.08.15  RR
   Replace Name of Zeidon Online Manuals by DEFINES
2002.06.06  BL    Repositiory
   modified zwfnTZCMLPLD_RemoveStatus for set ZKey to View (bugfix for
   remove CheckOutState)
2002.04.09  BL    R53829
   modified zwfnTZCMLPLD_CheckXLP_ForRepo for refresh CPLR - ComboBox
2002.01.09  FH
   eliminate SetFocusToCtrl() because of 56237
2002.01.07  HH
   change signature of SysValidDirOrFile so that it can be called from VML.
2001.08.21  BL   Repository
   Fix for AD: If craete a new Workstation, save the User Name in TZCMWIPO
2001.07.30  RG
   Fix: for external LPLR's support of relative pathes only
        if compiler specification exists
2001.07.19  RG
   support of relative pathes in compiler specification
   add operation: zwfnTZCMLPLD_SetCompSpec
2001.07.05  BL   Repository  R55249, R55249, F51302
   maintained Repository, part 2
2001.06.24  BL   Repository
   If save VML or C file, set UpdateInd flag in corresponding
   Meta (R54521, R53835)
2001.04.08  BL
   maintained Repository
2001.03.02 BL
   Always delete all old XLP Files
2001.02.22 BL  F50821
   create ZEIDONOP.H for all OperationGroups and LOD's
2000.12.12 DKS
   Corrected casting and Hungarian notation
2000.11.08  BL
   Modified zwTZCMLPLD_ExternalLPLR: inprove ZKey geneartion for
   renamed lplr
2000.11.01  BL
   Modified zwTZCMLPLD_GetWorkDir for get Workdirectory from Zeidon
   Local directory
2000.10.30 RG  Z2000
    GetViewByName: for parameter zLEVEL_TASK changed View --> 0
2000.10.20  SR  Z2000  Length of path variables
   Modified the size of all filename and path variables in whole module
   because size of attributes ExecDir, MetaSrcDir and PgmSrcDir
   has been changed to 254 in datamodel.
   Adjust the size of messagetext variables.
2000.10.13  BL  Z2000
   Create APP_LOCAL Directory with Environment Strings
2000.10.09  BL  Z2000  TB 50849
   Show APP_LOCAL Directory in New and Main Window for changes
2000.09.13  RG  Z2000
   Fixed crash after message "Zeidon Tools still running.\n"
         "Shut down all Zeidon Tools before running WorkStation "
2000.09.12  DKS Z2000
   Changed hard coded value to define.
2000.09.12  RG  Z2000
   Change of pathnames for Siron Reports only if *.prp-file exists
2000.08.25  RG  Z2000
   Set APP_LOCAL for all LPLRs.
2000.08.17  RG  Z2000
   Get the right pathnames to change the contents or Siron Reports
2000.08.14  RG  Z2000
   Function: oTZRPSRCO_ChangeRepFileContents has two new    parameters
2000.07.28  RG  Z2000
   Modified function zwTZCMLPLD_ExternalLPLR: Change the path and lplr-name
   for Siron Report.
   New local function: zwfnTZCMLPLD_DoChangeReportFiles
2000.07.09  BL
   Modified zwTZCMLPLD_ExternalLPLR: remove read only flag for xlp files
2000.04.26  BL    Repository
   Modified zwTZCMLPLD_CheckOutSnglClk for enable and disable Button by check
   out with multiselection
2000.04.19  BL    Repository
   Modified zwfnTZCMLPLD_CheckOutMeta: if RepositoryClient does not exists in
   database, then create it
2000.04.13  DKS
   Removed static functions.
2000.04.12  HH
   Activate WorkStation with zIGNORE_ATTRIB_ERRORS.
2000.04.03  BL
   Modified zwTZCMLPLD_CheckOutSource: if error by oTZCMLPLO_RefreshLPLR, then
   for set DEqueue-Flag
   Added zwfnTZCMLPLD_CheckCheckInList and modified zwTZCMLPLD_CheckDuplicateName
   for check all components in Check in List
2000.03.13  HH
   call ActivateOI_FromFile with zIGNORE_ATTRIB_ERRORS, needed for refresh
   of old (9j) LPLR's.
2000.03.02  BL  Z10
   Modified zwTZCMLPLD_InitDialog: if error on commit Repository object,
   then do not commit the workstation object
2000.02.28  BL  Z10
   Remove View vTZCMLPLO_Compare, is View is not in use
   Rename zwfnTZCMLPLD_OptionRefreshFromRepository in
   zwTZCMLPLD_OptionRefreshFromRepo ( for reuse code in Dialog tzcmrptd )
   Modified zwTZCMLPLD_InitMenu for refresh user defined
2000.02.21  BL  Z10
   Added zwfnTZCMLPLD_OptionRefreshFromRepository, zwTZCMLPLD_RefreshUserDefined,
   zwfnTZCMLPLD_LoadRefreshList for Refresh
   User defined
   Modified zwTZCMLPLD_OptionRefresh for move in new functions for reuse
   Modified zwTZCMLPLD_LoadLPLR and added zwfnTZCMLPLD_CheckData
   Modified zwTZCMLPLD_CheckDuplicateName: remove zwTZCMLPLD_CheckDuplicatePPE
   for new repository structure
2000.02.17  BL  Z10
   Modified zwTZCMLPLD_CheckInReus, zwTZCMLPLD_ExcludeActive and
   zwTZCMLPLD_OptionRefresh for return by refresh error
   Modified zwTZCMLPLD_CheckDuplicateName, zwTZCMLPLD_CheckDuplicateERD_TE
   and zwTZCMLPLD_CheckDuplicatePPE for reuse Code by Refresh Project
   from Repository
   Drop DB_Mode and #if 0
2000.02.11  BL  Z10 External LPLR
   Modified zwTZCMLPLD_ExternalLPLR for delete all old XLP files
   Added zwTZCMLPLD_SearchOldXLPs for search XLP file
2000.02.10  HH
   remove atomic repository database.
2000.02.08  BL  Z10 Repository
   Modified zwTZCMLPLD_OptionRefresh and zwTZCMLPLD_BuildCI_List: if the
   Workstation Administration is opened, no other Tool can run.
   So this check with zwTZCMLPLD_TaskCountCheck is not necessary
2000.01.31  BL  Z10 Repository
   Replace Aborted with aborted
   Modified zwTZCMLPLD_CheckInMeta for Refresh and Close CheckIn Window
   Modified zwTZCMLPLD_CheckDuplicateName: check duplicate component name between
   LOD's and Dialogs and check duplicate PPE
   Added zwTZCMLPLD_CheckDuplicatePPE for check duplicate PPE
2000.01.30  BL  Z10 Repository
   Added zwTZCMLPLD_CheckDuplicateERD_TE and modified zwTZCMLPLD_CheckDuplicateName
   for check exists a ERD or TE under an other name in Repository
2000.01.26  BL  Z10 Repository
   Modified zwTZCMLPLD_BuildCO_List for Check Out PPE
   Modified zwTZCMLPLD_CheckInReus and insert zwTZCMLPLD_CheckDuplicateName
   for check duplicate component name by Check In
   Modified CheckOutMeta and zwTZCMLPLD_InitCheckOut: Fix for following problem
     User A open the Window "Component Check Out"
     User B open the Window "Component Check Out" and checked out Component XXX
     User A checked out Component XXX
   Modified zwfnTZCMLPLD_SwitchLPLR: delete Message for Default Project
   Modified zwTZCMLPLD_LoadLPLR: Zeidon does not create the Subtaskview
   __CM.taskId, when do you open the active LPLR
   Modified zwTZCMLPLD_ExternalLPLR: was a new External LPLR a Repository LPLR,
   then remove corresponding CPLR from External LPLR
   Modified zwTZCMLPLD_CreateNewLPLR: insert TranslateStringToUpperCase by
   check Project Directories
2000.01.25  BL  Z10 Repository
   Replace "LPLR" with "Project"
   Modified zwTZCMLPLD_CheckOutSource for set comment and CheckOutDate by
   SA and TE
   Modified zwTZCMLPLD_BuildCI_List: Is a Subject Area, TE or ERD updated,
   then set all SubjectAreas, ERD and TE in CheckIn List
   Modified zwfnTZCMLPLD_CheckOutMeta for set Update-Flag = 0 (not updated)
   Modified zwTZCMLPLD_PreBuildCompList:set Option for BuildCheckedOutByUser = 8
2000.01.24  BL  Z10 TB968
   Modified zwTZCMLPLD_AddUser for Bug TB968
2000.01.20  BL  Z10   bugfix Repository
   Modified zwTZCMLPLD_CheckInAll: set Option for BuildCheckedOutByUser = 8
   Modified zwTZCMLPLD_CheckInReus: Is Meta not checked out by current User,
   when no Error Message (oTZCMLPLO_CheckInMetas send a Error Message)
000.01.14  BL   Z10   bugfix Repository
   Modified zwTZCMLPLD_ActivateCPLR for OrderEntitiesByDefaultAttribs
2000.01.13  BL   Z10   new PPE Handling
   Modified zwTZCMLPLD_CreateNewLPLR: no PPE/XPE in a external LPLR
   Modified zwTZCMLPLD_BuildDialogExecs: if PPE not in LPLR directory, then
   load PPE from Zeidon Bin/Sys Directory
2000.01.12  BL   Z10   bugfix Repository
   Modified Operation zwTZCMLPLD_DefaultDir and zwTZCMLPLD_CopyDirs: if Button press,
   then delete Zeidon the CPLR-Name from CPLR-Combobox by Refresh Window
2000.01.07  BL   Z10   bugfix Repositioy
   Modified Operation zwTZCMLPLD_SetLPLR_Type for Refresh Combobox
   Modified zwTZCMLPLD_AddUser for Relink RepositoryClient
   Modified zwTZCMLPLD_SignOnOK fpr set Focus to Control
2000.01.06  BL   Z10   bugfix Repositiory
   Modified Operation zwTZCMLPLD_CheckOutSource: when you cancel the checked
   out for a ERD, then is set the Enqueue flag
1999.12.23  BL   Z10   bugfix Repository
   Modified Operation zwTZCMLPLD_CheckInMeta: close check in window, when does
   not exists components for check in
1999.11.27  BL   Z10   new menu structure
   Modified Operation zwTZCMLPLD_ReturnFromSubWindow and Added Operation
   zwTZCMLPLD_InitMenu for enable or disable Menu Items
1999.09.20  BL   10a   BL new menu structure
   operation zwTZCMLPLD_ReturnFromSubWindow: if not repository LPLR, then
   disable menu option RepositoryComponentStatus
1999.07.12  DC   9J+10A QS999
   Modified zwTZCMLPLD_ExternalLPLR to NOT delete the LPLR entity on an
   error condition.
1999.04.22  DGC  10a
   Removed calls to NetSendBootstrapFile().
05.03.1997  HH
   BuildServerExecs copied from 9E, for short term we have to support
   the "old" distribution method. Port argument in Net-calls removed
10.03.1997  DonC
   Correct processing to eliminate error message on delete of LPLR when
   there is a CorrespondingCPLR entry but it doesn't match the current
   repository (it was an external LPLR that had a CorrespondingCPLR entity).
17.05.1997 Frank H
   - Changed the logic of CheckIn in correspondint to SQL Databases (CommitPoints)
   - Changed CheckInAll to CheckInReus
   - Added a new CheckInAll, which calls CheckInReus...
   - Changed the Component List: if it's empty don't popup a windot, bin Issue a Message.
29.05.1997  DonC
   Added check of return code on NetCommitOI_ToFile in BuildServerExecs.
13.06.1997  RG
   - Merging Version 9F and 9G the second time
     - Sending the *.XSK-Files for Siron-Katalogs inserted in function
       BuildServerExecs
     - For Unix-Systems the application name must be written in
       uppercase literals
15.06.1997  DonC
   Made modifications for handling of Report metas in check out.
15.06.1997  DonC
   Modified the MessagePrompt handling when a refresh occurs during
   Check In or Check Out.
28.07.1997  DonC
   Added InitNonreposWKS so that a workstation could be added without
   a Repository.
05.08.1997  DonC
   Modifified the initialization of nCheckOutFlag so that metas would not
   be accidently removed when something goes wrong.
01.10.1997  DonC
   Corrected message CM00212.
11.10.1997  DonC
   Corrected BuildCI_List to issue ReturnToTopWindow instead of StayOnWindow.
20.10.1997  DonC
   Corrected password compare in AddUser.
22.10.1997  DonC
   Corrected zwTZCMLPLD_ExternalLPLR to give an error message if the operator
   tries to create an external LPLR to a directory that does not have an
   XLP file.
11.11.1997  DonC
   Corrected refresh message during check out.
17.11.1997  DonC
   Ordered CPL/CPLR list by CPL Name and CPLR Name.
17.11.1997  DonC
   Modified ExcludeActive so that it would courrectly remove the check-out
   status for a meta whose status had already been removed from the repository.
26.11.1997  DonC
   Changed CopyFile to SysCopyFile.
08.12.1997  DonC
   Changed ExternalLPLR to create unique LPLR ZKey for a renamed External
   LPLR.  This allows an LPLR to be copied and recreated under a new name.
   Also asked the operator if the W_MetaDef.Status values should be changed
   to updateable.
10.12.1997  DonC
   Modified InitDialog to position LPLR list on first entry.
22.12.1997  DonC
   Created CheckDialogDeps and modified CheckInEdits so that when a Dialog
   is checked in, the only LODs and VORs that must also be checked in are
   those that the Dialog uses.  Also added Reports to CheckInEdits so that
   a Report would properly check in to the Repository.
05.02.1998  DonC
   Corrected use of szComments to increase size of variable and use
   GetVariable... instead of GetString...
18.02.1998  DonC
   Modified use of KZDBHQUA object to not reuse a named view but create it
   empty each time.
17.03.1998  RG
   Corrected function zwfnTZCMLPLD_CheckInEdits
   - Created a view from view before call of zwfnTZCMLPLD_BuildER_List
18.03.1998  DonC
   Modified zwfnTZCMLPLD_CheckOutMeta to include LPLR back into CPLR if it
   somehow got accidently deleted. QS 134
19.03.1998  DonC
   Modified DeleteLPLR so that LPLR would be deleted even if corresponding
   CPLR had already been deleted. QS 179
18.04.1998  DonC
   Modified UpdateUser to use a password validation input value. QS 29
01.07.1998  DonC
   Added HelpOnHelp operation.
10.07.1998  DKS
   Cleanup after implementing Migration operation for 9J in wrong file.
1998/09/18  DC
   Again modified zwTZCMLPLD_UpdateUser to correct changing of Password.
   Hopefully got it correct this time. (Note that LOD TZCMWIPO was also
   changed.
1998/10/06  DC
   Modified zwTZCMLPLD_DeleteLPLR to use TZCMWKSO to check if LPLR is
   defined for CPLR instead of TZCMLPLO. This allows an external LPLR
   defined againts a repository LPLR to be deleted. (TB 338)
1998/10/15  DC
   Modified zwTZCMLPLD_ExternalLPLR so that resetting external LPLRs to
   updateable would work. (TB 267)
*/

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
#include "tzcm_opr.hg"

#define zLoadRefreshList      0
#define zRefreshLPLR          1
#define zRefreshUserDefined   2

/* local prototypes */
static zSHORT
zwfnTZCMLPLD_DoChangeReportFiles( zVIEW  vSubtask,
                                  zVIEW  vTempTZCMLPLO,
                                  zPCHAR szReportPathName);

static zSHORT
zwfnTZCMLPLD_CheckCheckInList( zVIEW  vChkInList,
                               zPCHAR pchTypeLPLR1,
                               zPCHAR pchTypeLPLR2,
                               zPCHAR pchName );

static zSHORT
zwfnTZCMLPLD_ActivateREFO( zVIEW vSubtask, zVIEW  vTZCMLPLO, zPVIEW vTZCMREFO,
                           zPCHAR pchName, zSHORT nRefreshLPLR );
static zSHORT
zwfnTZCMLPLD_LoadRefreshList( zVIEW vSubtask,
                              zVIEW vTZCMLPLO,
                              zVIEW vTZCMCPRO );

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_BuildCPLR_List( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckForSave( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_SaveLPLR( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_TaskCountCheck( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_ActivateCPLR_Meta( zVIEW vSubtask, zVIEW vTZCMCPRO,
                                zLONG Type, zULONG ulZKey );
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_OptionRefreshFromRepo( zVIEW  vSubtask, zPVIEW  vTZCMLPLO,
                                  zPCHAR pchName, zSHORT nRefreshLPLR );

void
zwfnTZCMLPLD_BuildER_List( zVIEW vTZCM_ChkInList, zVIEW vTZCM_ChkInList2 );
zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_CheckInEdits( zVIEW vSubtask );
zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_CheckOutMeta( zVIEW vSubtask, zVIEW vTZCMREPO, zVIEW vTemp,
                           zVIEW vTZCMCPRO, zVIEW vTZCMLPLO, zLONG Type,
                           zULONG ulZKey );
void
zwfnTZCMLPLD_GetAllActiveMetas( zVIEW vTZCM_ChkInList, zVIEW vTZCM_ChkInList2,
                                zLONG Type );
zSHORT
zwfnTZCMLPLD_DeleteChkOutType( zVIEW vSubtask, zVIEW vTZCMCPRO, zLONG Type );
void
zwfnTZCMLPLD_GetSelectedMetas( zVIEW vTZCM_ChkInList, zVIEW vTZCM_ChkInList2,
                               zLONG Type );
static void
zwfnTZCMLPLD_LoadMetaAndMerge( zVIEW vSubtask, zVIEW  vTZCMLPLO, zSHORT nType,
                               zPCHAR szMsgText, zPCHAR szRootEntityName );
static zSHORT
zwfnTZCMLPLD_LoadRepo_CPRO( zVIEW vSubtask, zPVIEW vTZCMREPO, zPVIEW vTZCMCPRO,
                            zVIEW vTZCMCOML );
static zSHORT
zwfnTZCMLPLD_SetDefaultListVaules( zVIEW vTZCMWIPO );
static zSHORT
zwfnTZCMLPLD_InitCheckOutAbort( zVIEW vSubtask, zVIEW vTZCMCOML, zPCHAR szUserEntity );
static zSHORT
zwfnTZCMLPLD_CheckOutRefresh( zVIEW vSubtask, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_CheckOutAskForERD( zVIEW vSubtask, zVIEW vTZCMCOML,
                                zVIEW vTZCMCPRO, zLONG Type );
static zSHORT
zwfnTZCMLPLD_CheckOutERD_SA_TE( zVIEW vSubtask, zVIEW vTZCMREPO, zVIEW vTemp,
                                zVIEW vTZCMCPRO, zVIEW vTZCMCOML, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_CheckOutERD_or_TE( zVIEW vSubtask, zVIEW vTZCMREPO, zVIEW vTemp,
                                zVIEW vTZCMCPRO, zVIEW vTZCMCOML, zVIEW vTZCMLPLO,
                                zLONG lType );
static zSHORT
zwfnTZCMLPLD_CheckOutOtherMeta( zVIEW vSubtask, zVIEW vTZCMREPO, zVIEW vTemp,
                                zVIEW vTZCMCPRO, zVIEW vTZCMCOML, zVIEW vTZCMLPLO,
                                zLONG Type, zULONG ulZKey );
static zSHORT
zwfnTZCMLPLD_CheckOutProcess( zVIEW vSubtask, zVIEW vTZCMLPLO,
                              zVIEW vTZCMCOML, zVIEW vTZCMCPRO );
static zSHORT
zwfnTZCMLPLD_CheckOutCommit( zVIEW vSubtask, zVIEW vTZCMWKSO, zVIEW vTZCMLPLO,
                             zVIEW vTZCMCPRO );
static zSHORT
zwfnTZCMLPLD_ActivateCOMPL( zVIEW vSubtask, zPVIEW vTZCMCOML, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_CommitCPRO( zVIEW vSubtask, zVIEW vTZCMCPRO );
static zSHORT
zwfnTZCMLPLD_RemoveStatus( zVIEW vSubtask, zVIEW vTZCMCOML, zVIEW vTZCMWKSO,
                           zVIEW vTZCMLPLO, zVIEW vTZCMLPLW, zVIEW vTZCMRPTO,
                           zLONG lType );
static zSHORT
zwfnTZCMLPLD_CreateViewForRefresh( zVIEW vSubtask, zPVIEW vTZCMRPTO, zVIEW vTZCMCOML );
static zSHORT
zwfnTZCMLPLD_RefreshAndCommit( zVIEW vSubtask, zVIEW vTZCMRPTO, zVIEW vTZCMCOML,
                               zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_AskForRemove( zVIEW vSubtask, zVIEW vTZCMLPLW );
static zSHORT
zwfnTZCMLPLD_CheckSelectSate( zVIEW vTZCMLPLW, zLONG lSourceType, zLONG lType );
static zSHORT
zwfnTZCMLPLD_AskForRemoveERD_TE_SA( zVIEW vTZCMLPLW, zLONG lSourceType );
static zSHORT
zwfnTZCMLPLD_SelectERD_TE_SA( zVIEW vTZCMLPLW );
static zSHORT
zwfnTZCMLPLD_ActivateLPLR( zVIEW vSubtask, zPVIEW vTZCMLPLR, zULONG ulZKey,
                           zPCHAR szName );
static zSHORT
zwfnTZCMLPLD_CheckProjectName_Type( zVIEW vSubtask, zVIEW vTZCMWKSO,
                                    zPCHAR szLPLR_Name, zPCHAR szLPLR_Type );
static zSHORT
zwfnTZCMLPLD_CheckDuplicateDir( zVIEW vSubtask, zVIEW vTZCMWKSO, zVIEW vTZCMLPLO,
                                zPCHAR pchLPLR_Name );
static zSHORT
zwfnTZCMLPLD_CheckValidDir( zVIEW vSubtask, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_CheckProjectDir( zVIEW vSubtask, zVIEW vTZCMWKSO, zVIEW vTZCMLPLO,
                              zPCHAR pchLPLR_Name );
static zSHORT
zwfnTZCMLPLD_CreateRepositoryProject( zVIEW vSubtask, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_CreateEmptyProject( zVIEW vSubtask, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_ActivateOldXLP( zVIEW vSubtask, zPVIEW vTZCMLPLO, zVIEW vTZCMLPLO1,
                             zVIEW vTZCMWKSO );
static zSHORT
zwfnTZCMLPLD_CheckXLP_ForRepo( zVIEW vSubtask, zVIEW vTZCMLPLO, zVIEW vTZCMWKSO );
static zSHORT
zwfnTZCMLPLD_DeleteAllOldXPL( zVIEW vSubtask, zVIEW vTZCMLPLO1 );
static zSHORT
zwfnTZCMLPLD_ChangeUpdateStatus( zVIEW vSubtask, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_SetNewReportPath( zVIEW vSubtask, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_SetNewDirPath( zVIEW vSubtask, zVIEW vTZCMLPLO1, zVIEW vTZCMLPLO );
static zSHORT
zwfnTZCMLPLD_SetCompSpec( zVIEW vTZCMLPLO,zPCHAR pszOldCompSrcDir, zPCHAR szOldLPLRName);
static zSHORT
zwfnTZCMLPLD_CheckValidPassword( zVIEW vSubtask, zPCHAR szPasswordNew,
                                 zVIEW vTZCMWIPO, zVIEW vTZCMWKSO );
static zSHORT
zwfnTZCMLPLD_CheckPasswordZKey( zVIEW vSubtask, zULONG ulZKey, zVIEW vTZCMREPO );
static zSHORT
zwfnTZCMLPLD_InitDialog( zVIEW vSubtask );
static zSHORT
zwfnTZCMLPLD_EditNewWorkstation( zVIEW vSubtask, zPVIEW vTZCMREPO, zPCHAR szWKS_Desc );
static zSHORT
zwfnTZCMLPLD_SetNewWorkstationValue( zVIEW vSubtask, zVIEW vTZCMREPO, zPCHAR szWKS_Desc );
static zSHORT
zwTZCMLPLD_BuildTZCMLPLW( zVIEW vSubtask, zPVIEW vTZCMLPLW );
static zSHORT
zwfnTZCMLPLD_BuildRemoveCheckedOuts( zVIEW vSubtask, zVIEW vTZCMLPLO, zVIEW vTZCMLPLW,
                                     zVIEW vCompL );
static zSHORT
zwfnTZCMLPLD_ActivateUSER( zVIEW vSubtask, zPVIEW vTZCMUSER, zVIEW vTZCMWIPO );
static zSHORT
zwfnTZCMLPLD_SetRepositoryClient( zVIEW vSubtask, zVIEW vTZCMREPO,
                                  zVIEW vTZCMWKSO, zULONG ulZKey2 );
static zSHORT
zwfnTZCMLPLD_SetCheckOutValues( zVIEW vSubtask, zVIEW vTZCMCPRO,
                                zVIEW vTZCMWKSO, zVIEW vTZCMWIPO );
static zSHORT
zwfnTZCMLPLD_Fill_TZCMRUWK( zVIEW vSubtask, zVIEW vTZCMRUWK, zVIEW vTZCMREPO );
static zSHORT
zwfnTZCMLPLD_ExcludeUser( zVIEW vTZCMRUWK, zVIEW vTZCMWKSO, zVIEW vTZCMREPO );
static zSHORT
zwfnTZCMLPLD_IncludeUser( zVIEW vTZCMRUWK, zVIEW vTempWKSO, zVIEW vTZCMREPO );


zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_SwitchLPLR( zVIEW vSubtask, zVIEW vTZCMLPLO );

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckShadowDirectory( zVIEW vSubtask,
                                 zVIEW vTZCMREPO );
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_OptionRefresh( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_BuildSelectedCompList( zVIEW vSubtask );

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLO_RefreshReusableCPLRs( zVIEW   vSubtask,
                                 zVIEW   vTZCMLPLO,
                                 zVIEW   vTZCMCPRO,
                                 zPCHAR  szTimestamp,
                                 zPCHAR  szPrevLPLR_LastRefreshDate,
                                 zBOOL   bRefreshLPLR );

zOPER_EXPORT zSHORT OPERATION
oTZCMLPLO_RefreshPartial( zVIEW vSubtask,
                          zVIEW vTZCMLPLO,
                          zVIEW vTZCMCPRO );


void OPERATION
SysConvertEnvironmentString( zPCHAR pchTarget, zLONG lMaxLth, zCPCHAR cpcSource );

/*
   This operation is an attempt to clean (ie. drop) all the CM views and
   object instances.  All it does is drop all OIs named at the subtask level
   for the "Zeidon Core Services" task.
*/
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CleanCM_Views( zVIEW vSubtask )
{
   zVIEW vSystem;
   zVIEW vView;
   zCHAR szName[ 200 ];

   // Try to retrieve the CM view that is named in the "Zeidon Core Services" task.
   GetViewByName( &vSystem, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );

   // If the CM system view was found, then drop all the object instances.
   if ( vSystem )
   {
      for ( SfGetFirstNamedView( &vView, szName, vSystem, zLEVEL_SUBTASK );
            vView;
            SfGetFirstNamedView( &vView, szName, vSystem, zLEVEL_SUBTASK ) )
      {
         // Don't drop any view beginning with the chars "__CM.".
         if ( zstrncmp( szName, "__CM.", 5 ) == 0 )
            SfDropSubtask( vView, 0 );
         else
            DropObjectInstance( vView );
      }
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_SetDefaultListVaules( zVIEW vTZCMWIPO )
{
   if ( vTZCMWIPO == 0 )
      return( -1 );

   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ComponentListType", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListDomain", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListERD", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListSA", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListTE", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListLOD", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListVOR", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListPE", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListDialogs", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListUIS", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListGlobalOper", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListHeaders", 0 );
   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ListReports", 0 );

   SetAttributeFromString( vTZCMWIPO, "ROOT", "CheckOutComments", "" );

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_InitNonreposWKS( zVIEW  vSubtask,
                            zPCHAR szWKS_Desc )
{
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMWKSO;
   zVIEW    vZeidonCM;
   zULONG   ulMaxZKey;
   zLONG    lWKS_Id;

   ActivateEmptyObjectInstance( &vTZCMWKSO, "TZCMWKSO", vSubtask, zSINGLE | zLEVEL_APPLICATION );
   CreateEntity( vTZCMWKSO, "RepositoryClient", zPOS_AFTER );

   // Why set this to a constant ... shouldn't it be random?  DKS 2000.12.12
   lWKS_Id = 91;     // Set workstation id to a constant.
   SetAttributeFromInteger( vTZCMWKSO, "RepositoryClient", "WKS_Id", lWKS_Id );
   ulMaxZKey = lWKS_Id * 1000000;
   SetAttributeFromInteger( vTZCMWKSO, "RepositoryClient", "ZKey", ulMaxZKey );
   SetAttributeFromInteger( vTZCMWKSO, "RepositoryClient", "MaxZKey", ++ulMaxZKey );
   SetAttributeFromString( vTZCMWKSO, "RepositoryClient", "Desc", szWKS_Desc );

   // Add a default User named "User"
   CreateEntity( vTZCMWKSO, "User", zPOS_AFTER );
   SetAttributeFromString( vTZCMWKSO, "User", "Name", "User" );
   SetAttributeFromString( vTZCMWKSO, "User", "Password", "user" );
   MessageSend( vSubtask, "CM00202", "Configuration Management",
                "Password for Non-Repository workstation is 'user'.",
                zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );

   ActivateEmptyObjectInstance( &vTZCMWIPO, "TZCMWIPO", vSubtask, zSINGLE );
   CreateEntity( vTZCMWIPO, "ROOT", zPOS_AFTER );
   SetNameForView( vTZCMWIPO,"TZCMWIPO", vSubtask, zLEVEL_TASK );

   zwfnTZCMLPLD_SetDefaultListVaules( vTZCMWIPO );

   if ( InitializeLPLR( vSubtask, "CM New User" ) != 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_ExitDialogTask, 0, 0 );
      return( 0 );
   }

   // Next window in NewLPLR
   SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow, "TZCMLPLD", "NewLPLR" );

   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );
   SetNameForView( vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_InitDialog( zVIEW vSubtask )
{
   zVIEW    vZeidonCM;
   zVIEW    vTZCMWKSO;
   LPTASK   lpTask;

   // Check to make sure that no other tools are up.
   lpTask = 0;
   while ( (lpTask = SfGetNextTask( lpTask )) != 0 )
   {
      zCHAR szDialogName[ 200 ];

      // Check the name of the dialog associated with the task.  If it begins
      // with TZ then it's a Zeidon Tools task.  We allow the object browser
      // to run and we have to ignore the current task.
      SfGetTaskInfo( szDialogName, zsizeof( szDialogName ), zTASK_DIALOG, lpTask );

      // We allow non-Zeidon tasks...
      if ( zstrncmpi( szDialogName, "TZ", 2 ) != 0 )
         continue;

      // We allow the browser...
      if ( zstrcmpi( szDialogName, "TZOBRWAD" ) == 0 )
         continue;

      // We allow the current task.
      if ( lpTask == SfGetCurrentTask( vSubtask ) )
         continue;

      // Uh-oh...some other Zeidon task is running.
      MessageSend( vSubtask, "CM00299", "Configuration Management",
                   "Zeidon Tools still running.\n"
                   "Shut down all Zeidon Tools before running WorkStation "
                   "Manager.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      // Task isn't loaded. Therefore we have to use zWAB_ReturnToParent instead of zWAB_ExitDialogTask
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, 0, 0 );
      return( -1 );
   }

   // Clean up the CM views/object instances that might be lying around.
   zwTZCMLPLD_CleanCM_Views( vSubtask );

   if ( GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION ) >= 0 )
   {
      if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK ) >= 0 )
      {
         SetNameForView( vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
         InitializeDefaultLPL( vSubtask );
         SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow, "TZCMLPLD", "SignOn" );
         return( -1 );
      }
   }

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_EditNewWorkstation( zVIEW vSubtask, zPVIEW vTZCMREPO, zPCHAR szWKS_Desc )
{
   zCHAR    szMsg[ zMAX_MESSAGE_LTH + 1 ];
   zSHORT   nRC;

   strcpy_s( szMsg, zsizeof( szMsg ), "A Workstation was not found.\n" );
   strcat_s( szMsg, zsizeof( szMsg ), "Enter Description to build one." );
   szWKS_Desc[ 0 ] = 0;

   while ( zstrcmp( szWKS_Desc, "" ) == 0 )
   {
      nRC = MessagePromptForInput( vSubtask,   "CM00201",
                                   "Configuration Management",
                                   szMsg, zBEEP, szWKS_Desc, 60 );
      if ( nRC == 2 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_ExitDialogTask, 0, 0 );
         return( -1 );
      }
   }

   nRC = oTZCMREPO_ActivateRepository( vTZCMREPO, vSubtask );
   if ( nRC < 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "The Repository could not be accessed." );
      strcat_s( szMsg, zsizeof( szMsg ), "\nIf you want to create a work station without a Repository, respond OK.\n"
                                        "If you want to abort this process to install a Repository, respond Cancel." );

      if ( MessagePrompt( vSubtask, "CM00203", "Configuration Management",
                           szMsg, zBEEP, zBUTTONS_OKCANCEL,
                           zRESPONSE_CANCEL,  0 ) == zRESPONSE_CANCEL )
      {
         SetWindowActionBehavior( vSubtask, zWAB_ExitDialogTask, 0, 0 );
         return( -1 );
      }
      else
      {
         zwTZCMLPLD_InitNonreposWKS( vSubtask, szWKS_Desc );
         return( -1 );
      }
   }

   // Validate that the workstation description just entered is unique
   // on the Repository. If not unique, go into loop, prompting user
   // for unique name until he enters unique name or quits.
   while ( SetCursorFirstEntityByString( *vTZCMREPO, "RepositoryClient", "Desc", szWKS_Desc, 0 ) >= zCURSOR_SET )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "The Workstation Description was not unique.\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Please enter a new Description." );
      szWKS_Desc[ 0 ] = 0;
      nRC = MessagePromptForInput( vSubtask,   "CM00201",
                                 "Configuration Management",
                                 szMsg, zBEEP, szWKS_Desc, 60 );
      if ( nRC == 2 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_ExitDialogTask, 0, 0 );
         return( -1 );
      }
   }

   SetNameForView( *vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );
   return( 0 );
}



zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_XferToAddUser( zVIEW vSubtask )
{
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMWKSW = 0;
   zVIEW    vTZCMREPO;
   zVIEW    vTZCMREPW;
   zSHORT   ulZKey;
   zSHORT   nRC;

   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) > 0 )
      SetAttributeFromString( vTZCMWIPO, "ROOT", "Password", "" );

   if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) > 0 )
      CreateViewFromViewForTask( &vTZCMWKSW, vTZCMWKSO, 0 );

   if ( GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      if ( oTZCMREPO_ActivateRepository( &vTZCMREPO, vSubtask ) < 0 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( 0 );
      }
      SetNameForView( vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );
   }

   ActivateEmptyObjectInstance( &vTZCMREPW, "TZCMREPO", vSubtask, zSINGLE );
   CreateEntity( vTZCMREPW, "Installation", zPOS_AFTER );

   nRC = SetCursorFirstEntity( vTZCMREPO, "User", "" );
   while ( nRC == zCURSOR_SET )
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMREPO, "User", "ZKey" );
      if ( vTZCMWKSO > 0 )
      {
         if ( SetCursorFirstEntityByInteger( vTZCMWKSW, "User", "ZKey", (zLONG) ulZKey, "" ) != zCURSOR_SET )
         {
            CreateEntity( vTZCMREPW, "User", zPOS_AFTER );
            SetMatchingAttributesByName( vTZCMREPW, "User", vTZCMREPO, "User", zSET_ALL );
         }
      }
      else
      {
         CreateEntity( vTZCMREPW, "User", zPOS_AFTER );
         SetMatchingAttributesByName( vTZCMREPW, "User", vTZCMREPO, "User", zSET_ALL );
      }

      nRC = SetCursorNextEntity( vTZCMREPO, "User", "" );
   }

   SetNameForView( vTZCMREPW, "TZCMREPW", vSubtask, zLEVEL_TASK );

   if ( vTZCMWKSO > 0 )
      DropView( vTZCMWKSW );

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_SetNewWorkstationValue( zVIEW vSubtask, zVIEW vTZCMREPO, zPCHAR szWKS_Desc )
{
   zVIEW   vTZCMWKSO;
   zVIEW   vTZCMWIPO;
   zLONG   lWKS_Id;
   zULONG  ulMaxZKey;

   ActivateEmptyObjectInstance( &vTZCMWKSO, "TZCMWKSO", vSubtask, zSINGLE | zLEVEL_APPLICATION );

   CreateEntity( vTZCMWKSO, "RepositoryClient", zPOS_AFTER );
   CreateEntity( vTZCMREPO, "RepositoryClient", zPOS_AFTER );

   GetIntegerFromAttribute( &lWKS_Id, vTZCMREPO, "Installation", "NextWKS_Id" );
   SetAttributeFromInteger( vTZCMREPO, "Installation", "NextWKS_Id", ++lWKS_Id );
   SetAttributeFromInteger( vTZCMREPO, "RepositoryClient", "WKS_Id", --lWKS_Id );

   ulMaxZKey = lWKS_Id * 1000000;
   SetAttributeFromInteger( vTZCMREPO, "RepositoryClient", "ZKey", ulMaxZKey );
   SetAttributeFromInteger( vTZCMREPO, "RepositoryClient", "MaxZKey", ++ulMaxZKey );
   SetAttributeFromString( vTZCMREPO, "RepositoryClient", "Desc", szWKS_Desc );

   SetMatchingAttributesByName( vTZCMWKSO, "RepositoryClient", vTZCMREPO, "RepositoryClient", zSET_ALL );

   if ( CommitObjectInstance( vTZCMREPO ) < 0 )
   {
      MessageSend( vSubtask, "CM00299", "Configuration Management",
                   "Workstation could not be committed to Repository",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( oTZCMWKSO_CommitWorkstation( vTZCMWKSO ) < 0 )
      return( -1 );

   DropObjectInstance( vTZCMWKSO );

   if ( ActivateEmptyObjectInstance( &vTZCMWIPO, "TZCMWIPO", vSubtask, zSINGLE ) >= 0 )
   {
      if ( CreateEntity( vTZCMWIPO, "ROOT", zPOS_AFTER ) >= 0 )
      {
         SetNameForView( vTZCMWIPO,"TZCMWIPO", vSubtask, zLEVEL_TASK );
         zwfnTZCMLPLD_SetDefaultListVaules( vTZCMWIPO );
      }
   }

   zwTZCMLPLD_XferToAddUser( vSubtask );
   SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow | zWAB_ProcessImmediateAction, "TZCMLPLD", "AddUser" );

   if ( InitializeLPLR( vSubtask, "CM New User" ) != 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_ExitDialogTask, 0, 0 );
      return( -1 );
   }

   return( 0 );
}


#if 0
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_InitDialogoLD( zVIEW vSubtask )
{
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMREPO;
   zVIEW    vZeidonCM;
   zCHAR    szWKS_Desc[61];
   zSHORT   nRC;

   // Check to make sure that no other tools are up.
   if ( zwfnTZCMLPLD_InitDialog( vSubtask ) < 0 )
      return( 0 );

   if ( oTZCMWKSO_ActivateWorkStation( &vTZCMWKSO, vSubtask, zSINGLE | zNOI_OKAY | zIGNORE_ATTRIB_ERRORS ) != 0 )
   {
      if ( zwfnTZCMLPLD_EditNewWorkstation( vSubtask, &vTZCMREPO, szWKS_Desc ) < 0 )
         return( -1 );

      if ( zwfnTZCMLPLD_SetNewWorkstationValue( vSubtask, vTZCMREPO, szWKS_Desc ) < 0 )
         return( -1 );
   }
   else
   {
      InitializeDefaultLPL( vSubtask );
      SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow, "TZCMLPLD", "SignOn" );
   }

   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
   nRC = GetViewByName( &vTZCMWKSO, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );
   SetNameForView( vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   // Position on Default LPLR
   if ( SetCursorFirstEntityByAttr( vTZCMWKSO, "LPLR", "ZKey", vTZCMWKSO, "RepositoryClient", "DefaultLPLR_ZKey", "" ) != zCURSOR_SET )
   {
      SetCursorFirstEntity( vTZCMWKSO, "LPLR", 0 );
   }

   return( 0 );
}
#endif

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_InitDialog( zVIEW vSubtask )
{
   zVIEW    vTZCMWKSO;
   zVIEW    vZeidonCM;
   zCHAR    szZeidonWKS[ 128 ];
   zSHORT   nRC;

   // Check to make sure that no other tools are up.
   if ( zwfnTZCMLPLD_InitDialog( vSubtask ) < 0 )
      return( 0 );

   // Activate the Work Station object, giving an error and exiting if no object has been set up.
   if ( oTZCMWKSO_GetWKS_FileName( szZeidonWKS, zsizeof( szZeidonWKS ) ) == 0 )
      ActivateOI_FromFile( &vTZCMWKSO, "TZCMWKSO", vSubtask, szZeidonWKS, zSINGLE | zNOI_OKAY | zIGNORE_ATTRIB_ERRORS );
   else
   {
      MessageSend( vSubtask, "CM00202", "Configuration Management",
                   "The Workstation object could not be activated.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Make sure that there are no null entries in the list, which could occur if the system was aborted during the creation
   // of a new LPLR.
   for ( nRC = SetCursorFirstEntity( vTZCMWKSO, "LPLR", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vTZCMWKSO, "LPLR", "" ) )
   {
      if ( CompareAttributeToString( vTZCMWKSO, "LPLR", "Name", "" ) == 0 )
          DeleteEntity( vTZCMWKSO, "LPLR", zREPOS_NONE );
   }

   SetNameForView( vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
   SetNameForView( vTZCMWKSO, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );

   SetWindowActionBehavior( vSubtask, zWAB_StartModalSubwindow, "TZCMLPLD", "TZCMLPLL" );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_SignOnPreBuild( zVIEW vSubtask )
{
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMWKSO;


   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      ActivateEmptyObjectInstance( &vTZCMWIPO, "TZCMWIPO", vSubtask, zSINGLE );
      CreateEntity( vTZCMWIPO, "ROOT", zPOS_AFTER );
      SetNameForView( vTZCMWIPO,"TZCMWIPO", vSubtask, zLEVEL_TASK );

      zwfnTZCMLPLD_SetDefaultListVaules( vTZCMWIPO );

      if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) >= 0 )
      {
         SetCursorFirstEntity( vTZCMWKSO, "User","RepositoryClient" );

         if ( SetCursorNextEntity( vTZCMWKSO, "User", "RepositoryClient" ) < zCURSOR_SET )
         {
            // there is just one User assigned to this workstation
            SetAttributeFromAttribute( vTZCMWIPO, "ROOT", "UserName", vTZCMWKSO, "User", "Name" );
            SetAttributeFromAttribute( vTZCMWIPO, "ROOT", "UserDesc", vTZCMWKSO, "User", "Desc" );
         }
      }
   }
   else
      SetWindowCaptionTitle( vSubtask, 0, "  User List" );

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_SignOnPostBuild( zVIEW vSubtask )
{
   zVIEW    vTZCMWIPO;

   GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK );

   // if the Username isn't NULL, then position the Cursor on the password-control
   if ( CompareAttributeToString( vTZCMWIPO, "ROOT", "UserName", "" ) != 0 )
      SetFocusToCtrl( vSubtask, "Password" );

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_XferToUpdateUser( zVIEW vSubtask )
{
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMREPO;
   zCHAR    szUserName[ 33 ];
   zULONG   ulZKey;
   zSHORT   nRC;

   nRC = GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   nRC = GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szUserName, zsizeof( szUserName ), vTZCMWIPO, "ROOT", "UserName" );
   SetCursorFirstEntityByString( vTZCMWKSO, "User", "Name", szUserName, "" );

   if ( GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      if ( oTZCMREPO_ActivateRepository( &vTZCMREPO, vSubtask ) < 0 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( -1 );
      }
   }

   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMWKSO, "User", "ZKey" );
   if ( SetCursorFirstEntityByInteger( vTZCMREPO, "User", "ZKey", (zLONG) ulZKey, "" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00205", "Configuration Management",
                   "Unable to find User on Repository",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_AddUser( zVIEW vSubtask )
{
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMREPO;
   zVIEW    vTZCMREPW;
   zVIEW    vTemp;
   zCHAR    szName[ 33 ];
   zULONG   ulZKey;
   zSHORT   nRC;

   nRC = GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   nRC = GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK );
   nRC = GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );
   nRC = GetViewByName( &vTZCMREPW, "TZCMREPW", vSubtask, zLEVEL_TASK );

   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMREPW, "User", "ZKey" );
   GetStringFromAttribute( szName, zsizeof( szName ), vTZCMREPW, "User", "Name" );

   if ( SetCursorFirstEntityByInteger( vTZCMREPO, "User", "ZKey", (zLONG) ulZKey, "" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00207", "Configuration Management",
                   "Selected User is not found on Repository!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "cbUserName" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   if ( CompareAttributeToAttribute( vTZCMWIPO, "ROOT", "Password", vTZCMREPO, "User", "Password" ) != 0 )
   {
      MessageSend( vSubtask, "CM00208", "Configuration Management",
                   "Password is invalid for selected User!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "Password" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   CreateViewFromViewForTask( &vTemp, vTZCMWKSO, 0 );
   nRC = IncludeSubobjectFromSubobject( vTemp, "User", vTZCMREPO, "User", zPOS_AFTER );

   if ( SetCursorFirstEntityByAttr( vTZCMREPO, "UserRepositoryClient", "ZKey", vTZCMREPO, "RepositoryClient", "ZKey", "" ) >= zCURSOR_SET )
   {
      RelinkInstanceToInstance( vTZCMREPO, "UserRepositoryClient", vTZCMREPO, "RepositoryClient" );
   }

   SetAttributeFromString( vTZCMWIPO, "ROOT", "UserName", szName );
   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );

   if ( ObjectInstanceUpdatedFromFile( vTZCMREPO ) == 1 )
      CommitObjectInstance( vTZCMREPO );

   SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow, "TZCMLPLD", "NewLPLR" );

   DropView( vTemp );
   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CancelAddUser( zVIEW vSubtask )
{
   zVIEW    vTZCMREPW;

   if ( GetViewByName( &vTZCMREPW, "TZCMREPW", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( vTZCMREPW );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_DropRepoView
//
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_DropRepoView( zVIEW vSubtask )
{
   zVIEW vTZCMREPO;

   if ( GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( vTZCMREPO );

    return( 0 );
} // zwTZCMLPLD_DropRepoView


static zSHORT
zwfnTZCMLPLD_CheckValidPassword( zVIEW vSubtask, zPCHAR szPasswordNew,
                                 zVIEW vTZCMWIPO, zVIEW vTZCMWKSO )
{
   // Give an error under the following conditions.
   // 1. The new Password is null.
   // 2. The new Password is the same as the old.
   // 3. The new Password and PasswordValidation values do not match.

   if ( szPasswordNew[ 0 ] == 0 )
   {
      MessageSend( vSubtask, "CM00211", "Configuration Management",
                   "New Password value is null.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "N_Password" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   if ( CompareAttributeToAttribute( vTZCMWIPO, "ROOT", "Password", vTZCMWKSO, "User", "Password" ) == 0 )
   {
      MessageSend( vSubtask, "CM00211", "Configuration Management",
                   "New Password value is the same as current value.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "N_Password" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   if ( CompareAttributeToAttribute( vTZCMWIPO, "ROOT", "Password", vTZCMWIPO, "ROOT", "PasswordValidation" ) != 0 )
   {
      MessageSend( vSubtask, "CM00211", "Configuration Management",
                   "New Password and Verification Password do not match.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "V_Password" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_CheckPasswordZKey( zVIEW vSubtask, zULONG ulZKey, zVIEW vTZCMREPO )
{
   zCHAR szMsg[zSHORT_MESSAGE_LTH + 1];

   if ( ulZKey < 1 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "This User ID is missing a Zeidon Key.\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "To obtain a valid User ID:\n" );
      strcat_s( szMsg, zsizeof( szMsg ), " 1. Cancel from Update User\n" );
      strcat_s( szMsg, zsizeof( szMsg ), " 2. Delete this User from this Workstation\n" );
      strcat_s( szMsg, zsizeof( szMsg ), " 3. Add a new User" );
      MessageSend( vSubtask, "CM00210", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   if ( SetCursorFirstEntityByInteger( vTZCMREPO, "User", "ZKey", (zLONG) ulZKey, "" ) != zCURSOR_SET )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "This User ID was not found on the Repository.\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "To obtain a valid User ID:\n" );
      strcat_s( szMsg, zsizeof( szMsg ), " 1. Cancel from Update User\n" );
      strcat_s( szMsg, zsizeof( szMsg ), " 2. Delete this User from this Workstation\n" );
      strcat_s( szMsg, zsizeof( szMsg ), " 3. Add a new User" );
      MessageSend( vSubtask, "CM00211", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_UpdateUser( zVIEW vSubtask )
{
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMREPO;
   zVIEW    vTZCMWIPO;
   zCHAR    szName[ 33 ];
   zCHAR    szPassword[9];
   zCHAR    szPasswordNew[9];
   zCHAR    szPasswordValidation[9];
   zULONG   ulZKey;
   zSHORT   nRC;

   nRC = GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   nRC = GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      if ( oTZCMREPO_ActivateRepository( &vTZCMREPO, vSubtask ) < 0 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( 0 );
      }
      SetNameForView( vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );
   }

   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMWKSO, "User", "ZKey" );
   GetStringFromAttribute( szPasswordNew, zsizeof( szPasswordNew ), vTZCMWIPO, "ROOT", "Password" );
   GetStringFromAttribute( szPasswordValidation, zsizeof( szPasswordValidation ),
                           vTZCMWIPO, "ROOT", "PasswordValidation" );
   GetStringFromAttribute( szName, zsizeof( szName ), vTZCMWKSO, "User", "Name" );
   GetStringFromAttribute( szPassword, zsizeof( szPassword ), vTZCMWKSO, "User", "Password" );

   if ( zwfnTZCMLPLD_CheckPasswordZKey( vSubtask, ulZKey, vTZCMREPO ) < 0 )
      return( -1 );

   SetAttributeFromAttribute( vTZCMREPO, "User", "Name",
                              vTZCMWKSO, "User", "Name" );

   // Give an error under the following conditions.
   // 1. The new Password is null.
   // 2. The new Password is the same as the old.
   // 3. The new Password and PasswordValidation values do not match.
   if ( zwfnTZCMLPLD_CheckValidPassword( vSubtask, szPasswordNew, vTZCMWIPO, vTZCMWKSO ) < 0 )
   {
      return( -1 );
   }

   // Set the new password value, commit the workstation object and give
   // the user an message indicating password is set.
   SetAttributeFromString( vTZCMREPO, "User", "Password", szPasswordValidation );

   RelinkInstanceToInstance( vTZCMWKSO, "User", vTZCMREPO, "User" );
   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );

   if ( ObjectInstanceUpdatedFromFile( vTZCMREPO ) == 1 )
      CommitObjectInstance( vTZCMREPO );

   MessageSend( vSubtask, "CM00212", "Configuration Management",
                "The new Password has been assigned.",
                zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );

   DropObjectInstance( vTZCMREPO );
   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_SignOnOK( zVIEW vSubtask )
{
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMWKSO;
   int      nRC;

   nRC = GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   nRC = GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK );
   if ( CheckExistenceOfEntity( vTZCMWKSO, "User" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00218", "Configuration Management",
                   "No User assigned to Workstation!",
                    zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   if ( SetCursorFirstSelectedEntity( vTZCMWKSO, "User", "" ) != zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00219", "Configuration Management",
                   "Please select a User for Signon!",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "WKS_User" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   if ( CompareAttributeToAttribute( vTZCMWIPO, "ROOT", "Password", vTZCMWKSO, "User", "Password" ) != 0 )
   {
      MessageSend( vSubtask, "CM00220", "Configuration Management",
                   "Password invalid!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "Password" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   if ( CheckExistenceOfEntity( vTZCMWKSO, "LPLR" ) == zCURSOR_NULL )
      SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow, "TZCMLPLD", "NewLPLR" );
   else
      SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow, "TZCMLPLD", "TZCMLPLL" );

   // Check that there is not already a workstation entry in the Repository
   // by the same name as the entry being added.  The entry name is actually
   // the Desc attribute of TZCMWKSO.

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CancelFromOpen( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      SetWindowActionBehavior( vSubtask, zWAB_ExitDialogTask, 0, 0 );
   else
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, 0, 0 );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CancelFromNewLPLR( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMLPLR;
   zLONG    lZKey;
   zCHAR    szName[ 33 ];

   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );

   DeleteEntity( vTZCMWKSO, "LPLR", zREPOS_NONE );

   if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "CorrespondingCPLR", "ZKey" );
      GetStringFromAttribute( szName, zsizeof( szName ), vTZCMLPLO, "CorrespondingCPLR", "Name" );

      if ( zwfnTZCMLPLD_ActivateLPLR( vSubtask, &vTZCMLPLR, lZKey, szName ) >= 0 )
      {
         GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "LPLR", "ZKey" );
         SetCursorFirstEntityByInteger( vTZCMLPLR, "LPLR", "ZKey", lZKey, "" );
         DeleteEntity( vTZCMLPLR, "LPLR", zREPOS_NONE );
         CommitObjectInstance( vTZCMLPLR );
         DropObjectInstance( vTZCMLPLR );
      }
   }

   DropObjectInstance( vTZCMLPLO );
   SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow, "TZCMLPLD", "TZCMLPLL" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_GetZeidonApp
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
zwTZCMLPLD_GetZeidonApp( zVIEW  vSubtask,
                         zPVIEW pvKZAPPLOO,
                         zPCHAR pchZeidonDirectory,
                         zLONG  lMaxLth )
{
   zSHORT   nLth;
   zSHORT   nZRetCode;

   nZRetCode = SysGetEnvVar( pchZeidonDirectory, "ZEIDON", lMaxLth );
   if ( nZRetCode == -1 )
   {
      MessageSend( vSubtask, "CM00221", "Configuration Management",
                   "Zeidon Environment Variable not set !",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   nLth = (zSHORT) zstrlen( pchZeidonDirectory );
   if ( pchZeidonDirectory[ nLth ] != '\\' )
   {
      pchZeidonDirectory[ nLth ] = '\\';
      pchZeidonDirectory[ nLth + 1 ] = 0;
   }

   strcat_s( pchZeidonDirectory, lMaxLth, "ZEIDON.APP" );

   nZRetCode = SfActivateSysOI_FromFile( pvKZAPPLOO, "KZAPPLOO", vSubtask, pchZeidonDirectory, zSINGLE );

   if ( nZRetCode < 0 )
   {
      MessageSend( vSubtask, "CM00222", "Configuration Management",
                   "Zeidon.App could not be Loaded!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   return( 0 );
} // zwTZCMLPLD_GetZeidonApp

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_GetWorkDir
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_GetWorkDir( zVIEW  vKZAPPLOO,
                       zPCHAR pchPathName )
{
   zVIEW    vKZAPPLTemp;

   // See if APP_LOCAL has a value
   GetStringFromAttribute( pchPathName, zMAX_FILESPEC_LTH + 1, vKZAPPLOO, "ZEIDON", "ZEIDON_LOC" );
   if ( *pchPathName == 0 )
   {
      // There is no path in APP_LOCAL for the actual LPLR We take the path from Zeidon_Tools next
      CreateViewFromViewForTask( &vKZAPPLTemp, vKZAPPLOO, 0 );
      SetCursorFirstEntityByString( vKZAPPLTemp, "APPLICATION", "APP_NAME", "Zeidon_Tools", "");

      GetStringFromAttribute( pchPathName, zMAX_FILESPEC_LTH + 1, vKZAPPLTemp, "APPLICATION", "APP_LOCAL");
      if ( *pchPathName == 0 )
      {
         // Now we know that there is no APP_LOCAL for Zeidon_Tools.
         // We set the TEMP-Variable for Zeidon_Tools too; then we are sure
         // that we have only one file ZDR.INI
         strcpy_s( pchPathName, zMAX_FILESPEC_LTH + 1, "%TEMP%" );
         SetAttributeFromString( vKZAPPLTemp, "APPLICATION", "APP_LOCAL", pchPathName );
      }

      SetAttributeFromString( vKZAPPLOO, "APPLICATION", "APP_LOCAL", pchPathName );
      DropView( vKZAPPLTemp );
   }

   return( 0 );
} // zwTZCMLPLD_GetWorkDir



zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_NewLPLR_Init( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vKZAPPLOO = 0;
   zSHORT   nRC;
   zSHORT   nZRetCode;
   zCHAR    szZeidonDirectory[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szWorkDirectory[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szName[ 33 ];
   zCHAR    szFromFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szToFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szPathName[ zMAX_FILESPEC_LTH + 1 ];

   // This code activates the ZEIDON.APP object containing applications that
   // can be run from this system.  We will then either update an existing
   // entry for the new LPLR or we will create a new entry.

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   szZeidonDirectory[ 0 ] = 0;
   if ( zwTZCMLPLD_GetZeidonApp( vSubtask, &vKZAPPLOO, szZeidonDirectory, zsizeof( szZeidonDirectory ) ) < 0 )
      return( -1 );

   GetStringFromAttribute( szName, zsizeof( szName ), vTZCMLPLO, "LPLR", "Name" );
   if ( SetCursorFirstEntityByString( vKZAPPLOO, "APPLICATION", "APP_NAME", szName, "" ) < zCURSOR_SET )
   {
      nRC = CreateEntity( vKZAPPLOO, "APPLICATION", zPOS_LAST );
   }

   SetAttributeFromAttribute( vKZAPPLOO, "APPLICATION", "APP_NAME", vTZCMLPLO, "LPLR", "Name" );
   SetAttributeFromAttribute( vKZAPPLOO, "APPLICATION", "APP_DLL", vTZCMLPLO, "LPLR", "ExecDir" );
   SetAttributeFromAttribute( vKZAPPLOO, "APPLICATION", "APP_ADOBIN", vTZCMLPLO, "LPLR", "ExecDir" );
   SetAttributeFromAttribute( vKZAPPLOO, "APPLICATION", "APP_SHARED", vKZAPPLOO, "ZEIDON", "ZEIDON_SHR" );
   // get WorkDirectory
   GetCtrlText( vSubtask, "edWorkDirectory", szWorkDirectory, zMAX_FILESPEC_LTH );
   if ( zstrcmp( szWorkDirectory, "" ) != 0 )
   {
      SetAttributeFromString( vKZAPPLOO, "APPLICATION", "APP_LOCAL", szWorkDirectory );
   }

   szPathName[ 0 ] = 0;
   zwTZCMLPLD_GetWorkDir( vKZAPPLOO, szPathName );

   // Commit Zeidon.app
   nZRetCode = CommitOI_ToFile( vKZAPPLOO, szZeidonDirectory, zASCII );
   if ( nZRetCode < 0 )
   {
      MessageSend( vSubtask, "CM00223", "Configuration Management",
                   "Zeidon.App could not be Saved !",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }
   else
   {
      DropView( vKZAPPLOO );
   }

   // Copy the Hotkey file "ZEIDON.HKY" to the new LPLR directory.
   GetStringFromAttribute( szToFileName, zsizeof( szToFileName ), vTZCMLPLO, "LPLR", "ExecDir" );
   strcat_s( szToFileName, zsizeof( szToFileName ), "\\ZEIDON.HKY" );
   zgGetZeidonToolsDir( vSubtask, szFromFileName, zAPPL_DIR_OBJECT );
   strcat_s( szFromFileName, zsizeof( szFromFileName ), "ZEIDON.HKY" );
   SysCopyFile( vSubtask, szFromFileName, szToFileName, TRUE );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_SetLPLR_Type( zVIEW vSubtask )
{
   zVIEW    vLPLR;
   zCHAR    szLPLR_Type[ 2 ];

   // Based on the LPLR.LPLR_Type attribute set by one of the buttons that
   // triggered this operation, modify the CPLR seclection combo box as follows:
   //  Repository LPLR: ungray the combo box.
   //  Non-Repository or External LPLR:  gray the combo box and remove any
   //  selection already made.

   GetViewByName( &vLPLR, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szLPLR_Type, zsizeof( szLPLR_Type ), vLPLR, "LPLR", "LPLR_Type" );
   if ( szLPLR_Type[ 0 ] == '1' ) // If this is Repository type
      SetCtrlState( vSubtask, "SelectCPLR", zCONTROL_STATUS_ENABLED, TRUE );
   else
   {
      SetCtrlState( vSubtask, "SelectCPLR", zCONTROL_STATUS_ENABLED, FALSE );

      if ( CheckExistenceOfEntity( vLPLR, "CorrespondingCPLR" ) >= zCURSOR_SET )
      {
         ExcludeEntity( vLPLR, "CorrespondingCPLR", zREPOS_NONE );
         RefreshCtrl( vSubtask, "SelectCPLR" );
      }
   }

   return( 0 );
}

zSHORT /* LOCAL */  OPERATION
zwTZCMLPLD_SearchOldXLPs( zVIEW  vSubtask,
                          zVIEW  vTZCMLPLO,
                          zPCHAR pchReturnName )
{
   HWND        hWnd;
   HWND        hWndList;
   HINSTANCE   hInst;
   zCHAR       szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zSHORT      nCount;

   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMLPLO, "LPLR", "ExecDir" );
   ofnTZCMWKSO_AppendSlash( szFileName );
   strcat_s( szFileName, zsizeof( szFileName ), "*.xlp" );

   GetWindowHandle( (zPULONG) &hWnd, 0, vSubtask, 0 );
   hInst = (HINSTANCE) GetApplicationInstance( vSubtask );

   hWndList = CreateWindow( "ListBox", NULL, WS_CHILD | LBS_SORT, 1, 1, 1, 1, hWnd, (HMENU) 101, hInst, NULL );

   SendMessage( hWndList, WM_SETREDRAW, FALSE, 0L );
   SendMessage( hWndList, LB_DIR, 0x0000, (LONG)(LPSTR) szFileName );
   nCount = (int) SendMessage( hWndList, LB_GETCOUNT, 0, 0L );

   pchReturnName[ 0 ] = 0;
   SendMessage( hWndList, LB_GETTEXT, 0, (LONG)(LPSTR) pchReturnName );

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_ActivateOldXLP( zVIEW vSubtask, zPVIEW vTZCMLPLO, zVIEW vTZCMLPLO1,
                             zVIEW vTZCMWKSO )
{
   zCHAR    szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ];
   zCHAR    szLPLR_Name[ 33 ];
   zCHAR    szReturnName[ zBASE_FILENAME_LTH + 1 ];
   zLONG    hFile;
   zSHORT   nRC;

   // Determine the file name for the existing LPLR (ie., the XLP), which is:
   // DirectoryName + "/" + FileName + ".XLP"
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMLPLO1, "LPLR", "ExecDir" );
   ofnTZCMWKSO_AppendSlash( szFileName );
   GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vTZCMLPLO1, "LPLR", "Name" );
   strcat_s( szFileName, zsizeof( szFileName ), szLPLR_Name );
   strcat_s( szFileName, zsizeof( szFileName ), ".XLP" );

   // Check to see if the External LPLR name matches the .XLP file.  If it
   // doesn't, ask the user whether the LPLR is to be renamed.  If so,
   // find the original .XLP and load it, then write it out under the new
   // name.  Note that we will end up with two .XLP files, one under the new
   // name and one under the old name.  This will allow the LPLR to be used
   // under its original name elsewhere.
   hFile = SysOpenFile( vSubtask, szFileName, COREFILE_EXIST );
   if ( hFile < 0 )
   {
      TraceLineS( "*** File Name: ", szFileName );
      strcpy_s( szMsg, zsizeof( szMsg ), "The name entered is not correct for the current Project.\n\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Enter OK to use this new name for the Project.\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Enter Cancel to rekey the name." );
      nRC = MessagePrompt( vSubtask, "CM00296", "Configuration Management",
                           szMsg, 0, zBUTTONS_OKCANCEL,
                           zRESPONSE_OK, zICON_QUESTION );

      if ( nRC == zRESPONSE_OK )
      {
         // Locate the original .XLP file and load it.

         // Using the Windows interface, create an invisible window which
         // contains the list of all files in the directory of type *.xlp.
         // The *.xlp is passed to Windows to delineate the files listed.
         // Since the list should be a list of one, we only care about the first
         // one in the list.
         zwTZCMLPLD_SearchOldXLPs( vSubtask, vTZCMLPLO1, szReturnName );

         // If the szReturnName variable is still null, then an XLP file
         // could not be found in the directory.
         if ( szReturnName[ 0 ] == 0 )
         {
            MessageSend( vSubtask, "CM00200", "Configuration Management",
                         "The directory specified is not a valid Project.",
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         // DeleteEntity( vTZCMWKSO, "LPLR", zREPOS_PREV );
            return( -1 );
         }

         GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMLPLO1, "LPLR", "ExecDir" );
         ofnTZCMWKSO_AppendSlash( szFileName );
         strcat_s( szFileName, zsizeof( szFileName ), szReturnName );
      }
      else
      {
         return( -1 );
      }
   }

   // Activate the file name, whether the new one or the old one.
   nRC = ActivateOI_FromFile( vTZCMLPLO, "TZCMLPLO", vSubtask, szFileName, zSINGLE | zLEVEL_APPLICATION | zIGNORE_ERRORS );
   if ( nRC < 0 )
   {
      DeleteEntity( vTZCMWKSO, "LPLR", zREPOS_PREV );
      return( -1 );
   }

   SetNameForView( *vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_CheckXLP_ForRepo( zVIEW vSubtask, zVIEW vTZCMLPLO, zVIEW vTZCMWKSO )
{
   zCHAR    szERR_Msg[ zMAX_MESSAGE_LTH + 1 ];

   // was a new External LPLR a Repository LPLR, then send a MessagePrompt
   if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) >= zCURSOR_SET )
   {
      strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "This Project is a Repository Project.\n" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "Do you really want to create an External Project?" );

      if ( MessagePrompt( vSubtask, "CM00702", "Configuration Management",
                          szERR_Msg, zBEEP, zBUTTONS_YESNO,
                          zRESPONSE_YES, 0 ) == zRESPONSE_YES )
      {
         ExcludeEntity( vTZCMLPLO, "CorrespondingCPLR", zREPOS_PREV );
      }
      else
      {
         //set Repository Type "Repository Projekt"
         SetCtrlState( vSubtask, "SelectCPLR", zCONTROL_STATUS_ENABLED, TRUE );
         SetCtrlState( vSubtask, "Repository", zCONTROL_STATUS_CHECKED, TRUE );
         SetCtrlState( vSubtask, "External", zCONTROL_STATUS_CHECKED, FALSE );
         DeleteEntity( vTZCMWKSO, "LPLR", zREPOS_PREV );
         RefreshCtrl( vSubtask, "SelectCPLR" );
         return( -1 );
      }
   } // endif ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" )...

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_DeleteAllOldXPL( zVIEW vSubtask, zVIEW vTZCMLPLO1 )
{
   zCHAR  szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szFileName1[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szERR_Msg[ zMAX_MESSAGE_LTH + 1 ];
   zCHAR  szReturnName[ zBASE_FILENAME_LTH + 1 ];

   // Always delete all old XLP files
   GetStringFromAttribute( szFileName1, zsizeof( szFileName1 ), vTZCMLPLO1, "LPLR", "ExecDir" );
   ofnTZCMWKSO_AppendSlash( szFileName1 );
   strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "attrib " );
   strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szFileName1 );

   do
   {
      zwTZCMLPLD_SearchOldXLPs( vSubtask, vTZCMLPLO1, szReturnName );
      if ( szReturnName[ 0 ] != 0 )
      {
         strcpy_s( szFileName, zsizeof( szFileName ), szFileName1 );
         strcat_s( szFileName, zsizeof( szFileName ), szReturnName );
         if ( SysOpenFile( vSubtask, szFileName, COREFILE_DELETE ) < 0 )
         {
            // Remove read only flag.
            strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "*.xlp -r" );
            StartTask( vSubtask, szERR_Msg, SW_HIDE );
         }
      }
   } while ( szReturnName[ 0 ] != 0 );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_ChangeUpdateStatus( zVIEW vSubtask, zVIEW vTZCMLPLO )
{
   zVIEW  vTempR;
   zVIEW  vTempS;
   zLONG  lSOURCE, nREFER;
   zSHORT nRC1, nRC2;
   zCHAR  szMsg[ zMAX_MESSAGE_LTH + 1 ];

   // Ask if the operator wants all entries in the LPLR changed to updateable
   // status and if so, change each W_MetaDef.Status entry accordingly and
   // add them all under the updateable W_MetaType entries.  This allows all
   // metas in the new LPLR to be updated.
   strcpy_s( szMsg, zsizeof( szMsg ), "Do you want the status of all metas in the Project changed " );
   strcat_s( szMsg, zsizeof( szMsg ), "\nso that they can be updated in the new Project?" );
   if ( MessagePrompt( vSubtask, "CM00701", "Configuration Management",
                        szMsg, zBEEP, zBUTTONS_YESNO,
                        zRESPONSE_NO,  0 ) == zRESPONSE_YES )
   {
      CreateViewFromViewForTask( &vTempR, vTZCMLPLO, 0 );
      CreateViewFromViewForTask( &vTempS, vTZCMLPLO, 0 );

      // Set the Status values.
      for ( nRC1 = SetCursorFirstEntity( vTempR, "W_MetaDef", "LPLR" );
            nRC1 >= zCURSOR_SET;
            nRC1 = SetCursorNextEntity( vTempR, "W_MetaDef", "LPLR" ) )
      {
         SetAttributeFromInteger( vTempR, "W_MetaDef", "Status", 1 );
      }

      // Add all REFER entries under the SOURCE meta types.
      for ( lSOURCE = 1; lSOURCE <= 15; lSOURCE++ )
      {
         nREFER = lSOURCE + 2000;
         nRC1 = SetCursorFirstEntityByInteger( vTempR, "W_MetaType", "Type", nREFER, "" );
         nRC2 = SetCursorFirstEntityByInteger( vTempS, "W_MetaType", "Type", lSOURCE, "" );

         if ( nRC1 >= zCURSOR_SET && nRC2 >= zCURSOR_SET )
         {
            for ( nRC1 = SetCursorFirstEntity( vTempR, "W_MetaDef", 0 );
                  nRC1 >= zCURSOR_SET;
                  nRC1 = SetCursorNextEntity( vTempR, "W_MetaDef", 0 ) )
            {
               if ( SetCursorFirstEntityByAttr( vTempS, "W_MetaDef", "Name", vTempR, "W_MetaDef", "Name", 0 < zCURSOR_SET ) )
               {
                  // The meta doesn't exist as a source so add it.
                  IncludeSubobjectFromSubobject( vTempS, "W_MetaDef", vTempR, "W_MetaDef", zPOS_AFTER );
               }
            }
         }
      }

      DropView( vTempR );
      DropView( vTempS );
   }

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_SetNewReportPath( zVIEW vSubtask, zVIEW vTZCMLPLO )
{
   zVIEW   vTemp;
   zLONG   lREFER, lSOURCE;
   zSHORT  nRC;
   zCHAR   szReportPathName[ zMAX_FILESPEC_LTH + 1 ];  // for change of siron report files

   // See if there are any reports and change the path and lplr-name in
   // file *.xsq and *.rep
   CreateViewFromViewForTask( &vTemp, vTZCMLPLO, 0 );
   lSOURCE = zSOURCE_DIALOG_META;

   // Get the Pathname of the PRP-File
   GetStringFromAttribute( szReportPathName, zsizeof( szReportPathName ), vTemp, "LPLR", "MetaSrcDir" );
   ofnTZCMWKSO_AppendSlash( szReportPathName );

   nRC = SetCursorFirstEntityByInteger( vTemp, "W_MetaType", "Type", lSOURCE, "" );
   if ( nRC >= zCURSOR_SET )
   {
      zwfnTZCMLPLD_DoChangeReportFiles( vSubtask, vTemp, szReportPathName );
   }

   lREFER  = lSOURCE + 2000;
   nRC = SetCursorFirstEntityByInteger( vTemp, "W_MetaType", "Type", lREFER, "" );
   if ( nRC >= zCURSOR_SET )
   {
      zwfnTZCMLPLD_DoChangeReportFiles( vSubtask, vTemp, szReportPathName );
   }

   DropView( vTemp );
   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_SetNewDirPath( zVIEW vSubtask, zVIEW vTZCMLPLO1, zVIEW vTZCMLPLO )
{
   // Store the new directory information in the LPLR (XLP), because the whole
   // LPLR set of files and the XLP may have been moved from one directory
   // set to another and the current information may be incorrect.
   SetAttributeFromAttribute( vTZCMLPLO,  "LPLR", "ExecDir", vTZCMLPLO1, "LPLR", "ExecDir" );
   SetAttributeFromAttribute( vTZCMLPLO,  "LPLR", "PgmSrcDir", vTZCMLPLO1, "LPLR", "PgmSrcDir" );
   SetAttributeFromAttribute( vTZCMLPLO,  "LPLR", "MetaSrcDir", vTZCMLPLO1, "LPLR", "MetaSrcDir" );
   SetAttributeFromAttribute( vTZCMLPLO,  "LPLR", "Name", vTZCMLPLO1, "LPLR", "Name" );

   // Also set the TempDesc attribute for the update window.
   SetAttributeFromAttribute( vTZCMLPLO,  "LPLR", "TempDesc", vTZCMLPLO,  "LPLR", "Desc" );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_SetCompSpec( zVIEW vTZCMLPLO, zPCHAR pszOldCompSrcDir, zPCHAR pszOldLPLRName)
{
   zCHAR szAktDir[ zMAX_FILESPEC_LTH + 1 ];

   zSHORT RESULT;
   zSHORT sRC;

   if ( CheckExistenceOfEntity( vTZCMLPLO, "Compiler") >= 0)
   {
      // The pathnames in Compilerspecification should be changed.
      GetStringFromAttribute( szAktDir, zsizeof( szAktDir ), vTZCMLPLO, "Compiler", "TargetExecutableDir" );
      sRC = SetCompSpecPaths( vTZCMLPLO, pszOldCompSrcDir, pszOldLPLRName,
                              szAktDir, "Compiler", "TargetExecutableDir",
                              "Target Executable Dir", "Create External LPLR - Compiler Spec", 254 );

      GetStringFromAttribute( szAktDir, zsizeof( szAktDir ), vTZCMLPLO, "Compiler", "TargetObjectDir" );
      sRC = SetCompSpecPaths( vTZCMLPLO, pszOldCompSrcDir, pszOldLPLRName,
                              szAktDir, "Compiler", "TargetObjectDir", "Target Object Dir",
                              "Create External LPLR - Compiler Spec", 254 );

      GetStringFromAttribute( szAktDir, zsizeof( szAktDir ), vTZCMLPLO, "Compiler", "MakefileDir" );
      sRC = SetCompSpecPaths( vTZCMLPLO, pszOldCompSrcDir, pszOldLPLRName,
                              szAktDir, "Compiler", "MakefileDir", "Makefile Dir",
                              "Create External LPLR - Compiler Spec", 254 );

      GetStringFromAttribute( szAktDir, zsizeof( szAktDir ), vTZCMLPLO, "Compiler", "EnvironmentDir" );
      sRC = SetCompSpecPaths( vTZCMLPLO, pszOldCompSrcDir, pszOldLPLRName,
                              szAktDir, "Compiler", "EnvironmentDir", "Resource Dir",
                              "Create External LPLR - Compiler Spec", 254 );
   }  // CheckExistence Compiler

   if ( CheckExistenceOfEntity( vTZCMLPLO, "Include") >= 0)
   {
      // Include-Verzeichnisse
      RESULT = SetCursorFirstEntity( vTZCMLPLO, "Include", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      {
         GetStringFromAttribute( szAktDir, zsizeof( szAktDir ), vTZCMLPLO, "Include", "IncludeDir");
         sRC = SetCompSpecPaths( vTZCMLPLO, pszOldCompSrcDir, pszOldLPLRName, szAktDir,
                                 "Include", "IncludeDir", "Include Dir",
                                 "Create External LPLR - Compiler Spec", 254 );
         RESULT = SetCursorNextEntity( vTZCMLPLO, "Include", "" );
      }
   }  // CheckExistence Include

   if ( CheckExistenceOfEntity( vTZCMLPLO, "Lib") >= 0)
   {
      // Lib-Verzeichnisse
      RESULT = SetCursorFirstEntity( vTZCMLPLO, "Lib", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      {
         GetStringFromAttribute( szAktDir, zsizeof( szAktDir ), vTZCMLPLO, "Lib", "LibDir");
         sRC = SetCompSpecPaths( vTZCMLPLO, pszOldCompSrcDir, pszOldLPLRName, szAktDir,
                                 "Lib", "LibDir", "Lib Dir",
                                 "Create External LPLR - Compiler Spec", 254 );
         RESULT = SetCursorNextEntity( vTZCMLPLO, "Lib", "" );
      }
   }  // CheckExistence Lib

   if ( CheckExistenceOfEntity( vTZCMLPLO, "ExternalTarget") >= 0)
   {
      // External objects and libraries
      RESULT = SetCursorFirstEntity( vTZCMLPLO, "ExternalTarget", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      {
         if ( CheckExistenceOfEntity( vTZCMLPLO, "ExternalObjFile") >= 0)
         {
            RESULT = SetCursorFirstEntity( vTZCMLPLO, "ExternalObjFile", "" );
            while ( RESULT > zCURSOR_UNCHANGED )
            {
               GetStringFromAttribute( szAktDir, zsizeof( szAktDir ), vTZCMLPLO, "ExternalObjFile", "Name");
               sRC = SetCompSpecPaths( vTZCMLPLO, pszOldCompSrcDir, pszOldLPLRName, szAktDir,
                                       "ExternalObjFile", "Name", "External Object Dir",
                                       "Create External LPLR - Compiler Spec", 254 );
               RESULT = SetCursorNextEntity( vTZCMLPLO, "ExternalObjFile", "" );
            }
         }  // CheckExistence ExternalObjFile

         if ( CheckExistenceOfEntity( vTZCMLPLO, "ExternalLibFile") >= 0)
         {
            RESULT = SetCursorFirstEntity( vTZCMLPLO, "ExternalLibFile", "" );
            while ( RESULT > zCURSOR_UNCHANGED )
            {
               GetStringFromAttribute( szAktDir, zsizeof( szAktDir ), vTZCMLPLO, "ExternalLibFile", "Name");
               sRC = SetCompSpecPaths( vTZCMLPLO, pszOldCompSrcDir, pszOldLPLRName, szAktDir,
                                       "ExternalLibFile", "Name", "External Lib Dir",
                                       "Create External LPLR - Compiler Spec", 254);
               RESULT = SetCursorNextEntity( vTZCMLPLO, "ExternalLibFile", "" );
            }
         }  // CheckExistence ExternalLibFile

         RESULT = SetCursorNextEntity( vTZCMLPLO, "ExternalTarget", "" );
      }
   }  // CheckExistence ExternalTarget

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_ExternalLPLR( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMLPLO1;
   zVIEW    vTZCMWKSO;

   zCHAR    szOldCompSrcDir[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szOldLPLRName[ zBASE_FILENAME_LTH + 1 ];

   // This version of creating an LPLR just creates an LPLR entry into an
   // existing external LPLR.  It does this by dropping the LPLR entry
   // created so far and activating the XLP from the LPLR directory.
   GetViewByName( &vTZCMLPLO1, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   // Determine the file name for the existing LPLR (ie., the XLP), which is:
   // DirectoryName + "/" + FileName + ".XLP"
   if ( zwfnTZCMLPLD_ActivateOldXLP( vSubtask, &vTZCMLPLO, vTZCMLPLO1, vTZCMWKSO ) < 0 )
   {
      return( -1 );
   }

   // Get the old Component Source Directory and tho old LPLR-Name to change the
   // pathes in compiler specification
   GetStringFromAttribute( szOldCompSrcDir, zsizeof( szOldCompSrcDir ), vTZCMLPLO, "LPLR", "MetaSrcDir" );
   GetStringFromAttribute( szOldLPLRName, zsizeof( szOldLPLRName ), vTZCMLPLO, "LPLR", "Name" );

   // was a new External LPLR a Repository LPLR, then send a MessagePrompt
   if ( zwfnTZCMLPLD_CheckXLP_ForRepo( vSubtask, vTZCMLPLO, vTZCMWKSO ) < 0 )
      return( -1 );

   // Always delete all old XLP files
   zwfnTZCMLPLD_DeleteAllOldXPL( vSubtask, vTZCMLPLO1 );

   SetAttributeFromAttribute( vTZCMLPLO, "LPLR", "ZKey", vTZCMLPLO1, "LPLR", "ZKey" );

   // Ask if the operator wants all entries in the LPLR changed to updateable
   // status and if so, change each W_MetaDef.Status entry accordingly and
   // add them all under the updateable W_MetaType entries.  This allows all
   // metas in the new LPLR to be updated.
   zwfnTZCMLPLD_ChangeUpdateStatus( vSubtask, vTZCMLPLO );

   // See if there are any reports and change the path and lplr-name in
   // file *.xsq and *.rep
   zwfnTZCMLPLD_SetNewReportPath( vSubtask, vTZCMLPLO );

   // Store the new directory information in the LPLR (XLP), because the whole
   // LPLR set of files and the XLP may have been moved from one directory
   // set to another and the current information may be incorrect.
   zwfnTZCMLPLD_SetNewDirPath( vSubtask, vTZCMLPLO1, vTZCMLPLO );

   // Set the pathnames in Compiler specification
   zwfnTZCMLPLD_SetCompSpec (vTZCMLPLO, szOldCompSrcDir, szOldLPLRName);

   // Now drop the original LPLR in progress since we are done with it.
   DropObjectInstance( vTZCMLPLO1 );

   // Execute the common code to update the ZEIDON.APP object.
   zwTZCMLPLD_NewLPLR_Init( vSubtask );

   // Now write back the tZCMWKS8.POR file after adding the new LPLR entry.
   // But first delete that empty LPLR entity, though we don't know for
   // what purpose it was ever created.
   if ( CheckExistenceOfEntity( vTZCMWKSO, "LPLR" ) == zCURSOR_SET && CompareAttributeToString( vTZCMWKSO, "LPLR", "Name", "" ) == 0 )
   {
      DeleteEntity( vTZCMWKSO, "LPLR", zREPOS_NONE );
   }

   CreateEntity( vTZCMWKSO, "LPLR", zPOS_AFTER );
   SetMatchingAttributesByName( vTZCMWKSO, "LPLR", vTZCMLPLO, "LPLR", zSET_ALL );
   OrderEntityForView( vTZCMWKSO, "LPLR", "Name A" );
   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );

   // Also write back the modified LPLR.
   oTZCMLPLO_CommitLPLR( vTZCMLPLO );

   return( 0 );
}


/////////////////////////////////////////////////////////////////////////////
//
// This function checks for the existence of the specified file/directory.
// If it is a check for a valid file, that's all we do.  For a directory,
// if the directory does not exist (and bCheckCreate is TRUE) the user
// is given an opportunity to permit the directory to be created.
//
// Note that the full path is returned in pchPath (including drive, etc.)
//
// Return:
//   TRUE  - the directory exists (or was created)
//   FALSE - the directory does not exist or was not specified
//           or could not be created
//
/////////////////////////////////////////////////////////////////////////////
zSHORT  LOCALOPER
IsValidDirOrFile( zVIEW  vSubtask,
                  zPCHAR pchPath,
                  zPCHAR pchDirectoryType,
                  zBOOL  bDirectory,
                  zBOOL  bCheckCreate,
                  zSHORT nMaxPathLth )
{
   zSHORT nRC;
   zCHAR  szERR_Msg[ zMAX_MESSAGE_LTH + 1 ];  // directory length + message

   nRC = (zSHORT) SysValidDirOrFile( pchPath, bDirectory, FALSE, nMaxPathLth );

   // If we are dealing with a file OR if the user didn't want the directory
   // created, then exit with return code. Also return if the return code
   // is true.
   if ( !bDirectory || !bCheckCreate || nRC == 1 )
      return( nRC );

   // If we get here then the user wants us to create a directory that
   // doesn't exist.  Create it.
   strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Do you want to create " );
   strcat_s( szERR_Msg, zsizeof( szERR_Msg ), pchDirectoryType );
   strcat_s( szERR_Msg, zsizeof( szERR_Msg ), " Directory:\n " );
   strcat_s( szERR_Msg, zsizeof( szERR_Msg ), pchPath );
   if ( MessagePrompt( vSubtask, "CM00297", "Configuration Management",
                       szERR_Msg, zBEEP, zBUTTONS_YESNO, zRESPONSE_YES,  0 ) == zRESPONSE_YES )
   {
      nRC = (zSHORT) SysValidDirOrFile( pchPath, bDirectory, TRUE, nMaxPathLth );
   }
   else
      return( zRESPONSE_NO );

   return( nRC );
}


static zSHORT
zwfnTZCMLPLD_CheckProjectName_Type( zVIEW vSubtask, zVIEW vTZCMWKSO,
                                    zPCHAR szLPLR_Name, zPCHAR szLPLR_Type )
{
   zVIEW   vTZCMWKSO2;
   zSHORT  nRC;

   // Check that an LPLR_Type has been chosen.
   if ( szLPLR_Type[ 0 ] == 0 )
   {
      MessageSend( vSubtask, "CM00281", "Configuration Management",
                   "Project Type not selected.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
  // we cannot do a SetFocusToCtrl() because of 56237:
  //  SetFocusToCtrl( vSubtask, "RepositoryType" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   // Check that new LPLR name is unique.
   CreateViewFromViewForTask( &vTZCMWKSO2, vTZCMWKSO, 0 );
   nRC = SetCursorFirstEntityByString( vTZCMWKSO2, "LPLR", "Name", szLPLR_Name, 0 );
   DropView( vTZCMWKSO2 );

   if ( nRC >= zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00283", "Configuration Management",
                   "Project Name already exists.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetFocusToCtrl( vSubtask, "edName" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_CheckDuplicateDir( zVIEW vSubtask, zVIEW vTZCMWKSO, zVIEW vTZCMLPLO,
                                zPCHAR pchLPLR_Name )
{
   zVIEW    vTZCMWKSO2;
   zSHORT   nRC;
   zCHAR    szPgmSrcDir[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szExecDir[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szMetaSrcDir[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szPgmSrcDir2[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szExecDir2[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szMetaSrcDir2[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ];

   // Validate that no other LPLR has the same directory.  To do this, we
   // will loop through all the LPLR entities and compare each of the
   // directory names (PgmSrcDir, ExecDir, and MetaSrcDir) from the new
   // LPLR to all the names in existing LPLRs.
   CreateViewFromViewForTask( &vTZCMWKSO2, vTZCMWKSO, 0 );
   SetNameForView( vTZCMWKSO2, "***TZCMWKSO2", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szPgmSrcDir, zsizeof( szPgmSrcDir ), vTZCMLPLO, "LPLR", "PgmSrcDir" );
   GetStringFromAttribute( szExecDir, zsizeof( szExecDir ), vTZCMLPLO, "LPLR", "ExecDir" );
   GetStringFromAttribute( szMetaSrcDir, zsizeof( szMetaSrcDir ), vTZCMLPLO, "LPLR", "MetaSrcDir" );

   nRC = SetCursorFirstEntity( vTZCMWKSO2, "LPLR", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      GetStringFromAttribute( szPgmSrcDir2, zsizeof( szPgmSrcDir2 ), vTZCMWKSO2, "LPLR", "PgmSrcDir" );
      GetStringFromAttribute( szExecDir2, zsizeof( szExecDir2 ), vTZCMWKSO2, "LPLR", "ExecDir" );
      GetStringFromAttribute( szMetaSrcDir2, zsizeof( szMetaSrcDir2 ), vTZCMWKSO2, "LPLR", "MetaSrcDir" );

      if ( zstrcmpi( szPgmSrcDir,  szPgmSrcDir2 ) == 0    ||
           zstrcmpi( szPgmSrcDir,  szExecDir2 ) == 0      ||
           zstrcmpi( szPgmSrcDir,  szMetaSrcDir2 ) == 0   ||
           zstrcmpi( szExecDir,    szPgmSrcDir2 ) == 0    ||
           zstrcmpi( szExecDir,    szExecDir2 ) == 0      ||
           zstrcmpi( szExecDir,    szMetaSrcDir2 ) == 0   ||
           zstrcmpi( szMetaSrcDir, szPgmSrcDir2 ) == 0    ||
           zstrcmpi( szMetaSrcDir, szExecDir2 ) == 0      ||
           zstrcmpi( szMetaSrcDir, szMetaSrcDir2 ) == 0 )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Duplicate Directory on other Project '" );
         GetStringFromAttribute( pchLPLR_Name, 33, vTZCMWKSO2, "LPLR", "Name" );
         strcat_s( szMsg, zsizeof( szMsg ), pchLPLR_Name );
         strcat_s( szMsg, zsizeof( szMsg ), "'." );
         MessageSend( vSubtask, "CM00288", "Configuration Management",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         DropView( vTZCMWKSO2 );
         return( -1 );
      }
      nRC = SetCursorNextEntity( vTZCMWKSO2, "LPLR", 0 );
   }

   DropView( vTZCMWKSO2 );
   return( 0 );
}



static zSHORT
zwfnTZCMLPLD_CheckValidDir( zVIEW vSubtask, zVIEW vTZCMLPLO )
{
   zSHORT   nValid;
   zCHAR    szWorkEnv[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szToFileName[ zMAX_FILESPEC_LTH + 1 ];

   // First validate the directories.  They cannot be empty and must exist.
   //
   // The maximum length of the whole path is restricted by MSVC-Function
   // CreateDirectory. It seems that CreateDirectory accepts
   // strings with a maximum size of 246 characters and not 256!!.
   GetStringFromAttribute( szToFileName, zsizeof( szToFileName ), vTZCMLPLO, "LPLR", "ExecDir" );
   nValid = IsValidDirOrFile( vSubtask, szToFileName, "Executable", TRUE, TRUE, zsizeof( szToFileName ) );
   if ( nValid == 1 )
   {
      // reset the attribute to the full path
      SetAttributeFromString( vTZCMLPLO, "LPLR", "ExecDir", szToFileName );
      GetStringFromAttribute( szToFileName, zsizeof( szToFileName ), vTZCMLPLO, "LPLR", "MetaSrcDir" );
      nValid = IsValidDirOrFile( vSubtask, szToFileName, "Component Source", TRUE, TRUE, zsizeof( szToFileName ) );
      if ( nValid == 1 )
      {
         SetAttributeFromString( vTZCMLPLO, "LPLR", "MetaSrcDir", szToFileName );
         GetStringFromAttribute( szToFileName, zsizeof( szToFileName ), vTZCMLPLO, "LPLR", "PgmSrcDir" );
         nValid = IsValidDirOrFile( vSubtask, szToFileName, "VML / C Source", TRUE, TRUE, zsizeof( szToFileName ) );
         if ( nValid == 1 )
         {
            SetAttributeFromString( vTZCMLPLO, "LPLR", "PgmSrcDir", szToFileName );
            GetCtrlText( vSubtask, "edWorkDirectory", szToFileName, zMAX_FILESPEC_LTH );
            SysConvertEnvironmentString( szWorkEnv, zsizeof( szWorkEnv ), szToFileName );

            if ( zstrcmp( szWorkEnv, "" ) == 0 )
               strcpy_s( szWorkEnv, zsizeof( szWorkEnv ), szToFileName );

            nValid = IsValidDirOrFile( vSubtask, szWorkEnv, "Temporary Work", TRUE, TRUE, zsizeof( szWorkEnv ) );
            if ( nValid == 1 )
            {
               SetCtrlText( vSubtask, "edWorkDirectory", szToFileName );
            }
         }
      }
   }

   if ( nValid != 1 )
   {
      if ( nValid != zRESPONSE_NO )
      {
         zCHAR  szERR_Msg[ zMAX_FILENAME_LTH +  zSHORT_MESSAGE_LTH + 1  ];  // directory length + message

         strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Could not create directory:\n " );
         strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szToFileName );
         MessageSend( vSubtask, "CM00298", "Configuration Management",
                      szERR_Msg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_CheckProjectDir( zVIEW vSubtask, zVIEW vTZCMWKSO, zVIEW vTZCMLPLO,
                              zPCHAR pchLPLR_Name )
{
   zCHAR  szToFileName[ zMAX_FILESPEC_LTH + 1 ];

   // Validate that no other LPLR has the same directory.  To do this, we
   // will loop through all the LPLR entities and compare each of the
   // directory names (PgmSrcDir, ExecDir, and MetaSrcDir) from the new
   // LPLR to all the names in existing LPLRs.
   if ( zwfnTZCMLPLD_CheckDuplicateDir( vSubtask, vTZCMWKSO, vTZCMLPLO,  pchLPLR_Name ) < 0 )
   {
      return( -1 );
   }

   // Check Work Directory
   GetCtrlText( vSubtask, "edWorkDirectory", szToFileName, zMAX_FILESPEC_LTH );
   if ( zstrcmp( szToFileName, "" ) == 0 )
   {
      MessageSend( vSubtask, "CM00288", "Configuration Management",
                   "Temporary Work Directory is required.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      SetFocusToCtrl( vSubtask, "edWorkDirectory" );
      return( -1 );
   }

   // First validate the directories.  They cannot be empty and must exist.
   if ( zwfnTZCMLPLD_CheckValidDir( vSubtask, vTZCMLPLO ) < 0 )
      return( -1 );

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_CreateRepositoryProject( zVIEW vSubtask, zVIEW vTZCMLPLO )
{
   // This version of creating an LPLR is the normal version for initializing it from the Repository.
   if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00281", "Configuration Management",
                   "Repository CPLR not selected.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "SelectCPLR" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   // Execute the common code to update the ZEIDON.APP object.
   if ( zwTZCMLPLD_NewLPLR_Init( vSubtask ) != 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   zwTZCMLPLD_SaveLPLR( vSubtask );
   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_CreateEmptyProject( zVIEW vSubtask, zVIEW vTZCMLPLO )
{
   // This version of creating an LPLR initializes things just like
   // Case 1 above, except that no interface to the Repository has
   // been extablished.  This version also initializes the PPE and XPE
   // objects in their correct directories.

   // Execute the common code to update the ZEIDON.APP object.
   if ( zwTZCMLPLD_NewLPLR_Init( vSubtask ) != 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   zwTZCMLPLD_SaveLPLR( vSubtask );
   oTZCMLPLO_CommitLPLR( vTZCMLPLO );

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CreateNewLPLR( zVIEW vSubtask )
{
   zVIEW    vTaskLPLR;
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMULWO;
   zCHAR    szLPLR_Type[ 2 ];
   zCHAR    szLPLR_Name[ 33 ];
   zCHAR    szUserName[ 33 ];
   zCHAR    szFileName[ 255 ];
   zCHAR    szMetaSrc[ 255 ];
   zLONG    lHighPrefix;
   zLONG    lPrefix;
   zLONG    lStartZKey;
   zSHORT   nRC;

   // This routine creates the new LPLR entry.  It has three versions:
   //   1.  Create normal LPLR under Respository.
   //   2.  Create external LPLR not known to the Repository.  This creates
   //       an empty LPLR except for Hotkey and PPE components.
   //   3.  Create external LPLR not known to the Repository, but having
   //       existing components.  In this case, use the XLP that already
   //       exists in the LPLR directory.  What we are doing here is just
   //       taking that XLP to create our entry in TZCMWKS8.POR.
   // The three versions above are identified below as cases 1, 2 & 3.

   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szLPLR_Type, zsizeof( szLPLR_Type ), vTZCMLPLO, "LPLR", "LPLR_Type" );
   GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vTZCMLPLO, "LPLR", "Name" );

   GetStringFromAttribute( szMetaSrc, zsizeof( szMetaSrc ), vTZCMLPLO, "LPLR", "MetaSrcDir" );
   SetAttributeFromString( vTZCMLPLO, "LPLR", "PgmSrcDir", szMetaSrc );
   ZeidonStringConcat( szMetaSrc, 1, 0, "\\", 1, 0, 514 );
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMLPLO, "LPLR", "wExecutableSubDirectory" );
   ZeidonStringConcat( szMetaSrc, 1, 0, szFileName, 1, 0, 514 );
   SetAttributeFromString( vTZCMLPLO, "LPLR", "ExecDir", szMetaSrc );

   // Check that an LPLR_Type and new LPLR name.
   if ( zwfnTZCMLPLD_CheckProjectName_Type( vSubtask, vTZCMWKSO, szLPLR_Name, szLPLR_Type ) < 0 )
   {
      return( -1 );
   }

   // Check validate the directories
   if ( zwfnTZCMLPLD_CheckProjectDir( vSubtask, vTZCMWKSO, vTZCMLPLO, szLPLR_Name ) < 0 )
   {
      return( -1 );
   }

   // Before doing anything else, copy the description to a temp attribute
   // for use by the Dialog.  This is necessary so that the description in
   // the window does not automatically alter the LPLR Desc field.
   SetAttributeFromAttribute( vTZCMLPLO, "LPLR", "TempDesc", vTZCMLPLO, "LPLR", "Desc" );

   if ( szLPLR_Type[ 0 ] == '1' )
   {
      // Case 1:
      // KJS 05/18/15 - Code dad had in vml...
      //:// LPLR is new existing.
      //:// Activate Installation/Users object (TZCMULWO) and existing XLP (TZCMLPLO).
      //:// Then, update directory information in TZCMLPLO from basic path just entered and executable subdirectory from
      //:// TZCMULWO.

      //:// TZCMULWO
      //:// TZCMLPLO.LPLR.MetaSrcDir value was entered by User.
      //:szFileName = TZCMLPLO.LPLR.MetaSrcDir + "\" + "TZCMULWO.POR"
      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMLPLO, "LPLR", "MetaSrcDir" );
      ZeidonStringConcat( szFileName, 1, 0, "\\", 1, 0, 514 );
      ZeidonStringConcat( szFileName, 1, 0, "TZCMULWO.POR", 1, 0, 514 );
      //:nRC = ActivateOI_FromFile ( vTZCMULWO, "TZCMULWO", vSubtask, szFileName, 512 )
      nRC = ActivateOI_FromFile( &vTZCMULWO, "TZCMULWO", vSubtask, szFileName, 512 );
      //:IF nRC < 0
      if ( nRC < 0 )
      {
         //:MessageSend( ViewToWindow, "", "Configuration Management",
         //:             "An Installation/Users object (TZCMULWO) does not exist in the directory path specified.",
         //:             zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 )
         MessageSend( vSubtask, "", "Configuration Management", "An Installation/Users object (TZCMULWO) does not exist in the directory path specified.", zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
         //:SetWindowActionBehavior( ViewToWindow, zWAB_StayOnWindow, 0, 0 )
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         //:DropView( TZCMULWO )
         DropView( vTZCMULWO );
         //:RETURN -1
         return( -1 );
         //:ELSE
      }
      else
      {
         //:NAME VIEW TZCMULWO "TZCMULWO"
         SetNameForView( vTZCMULWO, "TZCMULWO", 0, zLEVEL_TASK );
      }
     // End of dad's vml code.

      // This version of creating an LPLR is the normal version for
      // initializing it from the Repository.
      if ( zwfnTZCMLPLD_CreateRepositoryProject( vSubtask, vTZCMLPLO ) < 0 )
         return( -1 );
   }
   else
   if ( szLPLR_Type[ 0 ] == '2' )
   {
      // Case 2:
      // KJS 05/18/15 - Code dad had created in vml...
      //:// Create the following.
      //:// 1. Build Installation/Users object (TZCMULWO). It will be completed on next window.
      //:// 2. TZCMLPLO and TZCMWKSO will be updated on next window.

      //:// TZCMULWO
      ActivateEmptyObjectInstance( &vTZCMULWO, "TZCMULWO", vSubtask, zSINGLE );
      SetNameForView( vTZCMULWO, "TZCMULWO", 0, zLEVEL_TASK );
      CreateEntity( vTZCMULWO, "Installation", zPOS_AFTER );
      SetAttributeFromAttribute( vTZCMULWO, "Installation", "Name", vTZCMLPLO, "LPLR", "Name" );
      SetAttributeFromAttribute( vTZCMULWO, "Installation", "ExecutableSubDirectory", vTZCMLPLO, "LPLR", "wExecutableSubDirectory" );
      CreateEntity( vTZCMULWO, "User", zPOS_AFTER );
      SetAttributeFromAttribute( vTZCMULWO, "User", "Name", vTZCMWKSO, "User", "Name" );
     // End of dad's vml code.

      // This version of creating an LPLR initializes things just like
      // Case 1 above, except that no interface to the Repository has
      // been established.  This version also initializes the PPE and XPE
      // objects in their correct directories.
      if ( zwfnTZCMLPLD_CreateEmptyProject( vSubtask, vTZCMLPLO ) < 0 )
         return( -1 );

      // Add the Installation object containing the current User and initial ZKey Prefix.
      ActivateEmptyObjectInstance( &vTZCMULWO, "TZCMULWO", vSubtask, zSINGLE | zLEVEL_TASK );
      CreateEntity( vTZCMULWO, "Installation", zPOS_AFTER );
      SetAttributeFromInteger( vTZCMULWO, "Installation", "ZKey", 1 );
      SetAttributeFromString( vTZCMULWO, "Installation", "Name", szLPLR_Name );

      GetStringFromAttribute( szUserName, zsizeof( szUserName ), vTZCMWKSO, "User", "Name" );
      CreateEntity( vTZCMULWO, "User", zPOS_AFTER );
      SetAttributeFromInteger( vTZCMULWO, "User", "ZKey", 11 );
      SetAttributeFromString( vTZCMULWO, "User", "Name", szUserName );
      SetAttributeFromInteger( vTZCMULWO, "User", "GenerationStartZKeyPrefix", 11 );
      SetAttributeFromInteger( vTZCMULWO, "User", "GenerationStartZKey", 110000000 );

      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMLPLO, "LPLR", "MetaSrcDir" );
      strcat_s( szFileName, zsizeof( szFileName ), "\\TZCMULWO.POR" );
      CommitOI_ToFile( vTZCMULWO, szFileName, zSINGLE );
   }
   else
   if ( szLPLR_Type[ 0 ] == '3' )
   {
      // Case 3:

      // This version handles an existing, external LPLR.
      if ( zwTZCMLPLD_ExternalLPLR( vSubtask ) != 0 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( -1 );
      }

     // Because the previous operation created a new vTZCMLPLO object, we must get its name again here.
     GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );

      // Add this User to the existing Installation Object, if it doesn't already exist there.
      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMLPLO, "LPLR", "MetaSrcDir" );
      strcat_s( szFileName, zsizeof( szFileName ), "\\TZCMULWO.POR" );
      nRC = ActivateOI_FromFile( &vTZCMULWO, "TZCMULWO", vTZCMLPLO, szFileName, zSINGLE | zLEVEL_TASK | zIGNORE_ERRORS );
      if ( nRC < 0 )
      {
         // The file doesn't exist, so create it.
         ActivateEmptyObjectInstance( &vTZCMULWO, "TZCMULWO", vSubtask, zSINGLE | zLEVEL_TASK );
         CreateEntity( vTZCMULWO, "Installation", zPOS_AFTER );
         SetAttributeFromInteger( vTZCMULWO, "Installation", "ZKey", 1 );
         SetAttributeFromString( vTZCMULWO, "Installation", "Name", szLPLR_Name );
      }
      GetStringFromAttribute( szUserName, zsizeof( szUserName ), vTZCMWKSO, "User", "Name" );
      if ( SetCursorFirstEntityByString( vTZCMULWO, "User", "Name", szUserName, "" ) < zCURSOR_SET )
      {
         // User doesn't exist, so add it, making ZKey and the Prefix one higher than the current Prefix.
         lHighPrefix = 0;
         nRC = SetCursorFirstEntity( vTZCMULWO, "User", "" );
         while ( nRC >= zCURSOR_SET )
         {
            GetIntegerFromAttribute( &lPrefix, vTZCMULWO, "User", "GenerationStartZKeyPrefix" );
            if ( lPrefix > lHighPrefix )
               lHighPrefix = lPrefix;
            nRC = SetCursorNextEntity( vTZCMULWO, "User", "" );
         }
         lHighPrefix = lHighPrefix + 1;
         CreateEntity( vTZCMULWO, "User", zPOS_AFTER );
         SetAttributeFromInteger( vTZCMULWO, "User", "ZKey", lHighPrefix );
         SetAttributeFromString( vTZCMULWO, "User", "Name", szUserName );
         SetAttributeFromInteger( vTZCMULWO, "User", "GenerationStartZKeyPrefix", lHighPrefix );
         lStartZKey = lHighPrefix * 10000000;
         SetAttributeFromInteger( vTZCMULWO, "User", "GenerationStartZKey", lStartZKey );
         CommitOI_ToFile( vTZCMULWO, szFileName, zSINGLE );
      }
   }

   // KJS 05/18/15 - Dad's vml code.
   //:// Make sure that the current User is in the TZCMULWO object. Currently, we will just add the User, if he
   //:// isn't already there. Though, we could also return an error for that case and make the person in charge of the
   //:// LPLR enter all valid Users.
   GetStringFromAttribute( szUserName, zsizeof( szUserName ), vTZCMWKSO, "User", "Name" );
   nRC = SetCursorFirstEntityByString( vTZCMULWO, "User", "Name", szUserName, "" );
   if ( nRC < zCURSOR_SET )
   {
     nRC = CreateEntity( vTZCMULWO, "User", zPOS_AFTER );
     SetAttributeFromAttribute( vTZCMULWO, "User", "Name", vTZCMWKSO, "User", "Name" );
   }
   // End dad's vml code.

   // Set the TaskLPLR to the new LPLR and force the TZCMLPLO named view
   // to be the same as the TaskLPLR view.
   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( vTaskLPLR );

   //GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   //DropObjectInstance( vTZCMLPLO );

   InitializeLPLR( vSubtask, szLPLR_Name );

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   SetNameForView( vTaskLPLR, "TZCMLPLOlHighPrefix", vSubtask, zLEVEL_TASK );

   if ( szLPLR_Type[ 0 ] == '1' )
   {
      // Frank H.: reaing a new RepositoryBasedLPLR  --> automatic refresh
       zwTZCMLPLD_OptionRefresh( vSubtask );
       SetWindowActionBehavior( vSubtask, zWAB_ReturnToParentWithRefresh, 0, 0 );
   }

   // Make sure we set the Default ZKey and save the work object.
   SetAttributeFromAttribute( vTZCMWKSO, "LPLR", "MaxZKey", vTZCMULWO, "User", "GenerationStartZKey" );
   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );

   return( 0 );
}



static zSHORT
zwfnTZCMLPLD_ActivateLPLR( zVIEW vSubtask, zPVIEW vTZCMLPLR, zULONG ulZKey,
                           zPCHAR szName )
{
   zVIEW  vKZDBHQUA;
   zSHORT nRC;
   zCHAR  szZKeyValue[ 33 ];
   zCHAR  szERR_Msg[ zSHORT_MESSAGE_LTH + 1 ];

   if ( GetViewByName( vTZCMLPLR, "TZCMLPLR", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( *vTZCMLPLR );

   if ( ActivateEmptyObjectInstance( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) < 0 )
   {
      return( -1 );
   }

   SetNameForView( vKZDBHQUA, "KZDBHQUA", vSubtask, zLEVEL_TASK );
   CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
   CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );

   SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "CPLR" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "CPLR" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "ZKey" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
   zltoa( ulZKey, szZKeyValue, zsizeof( szZKeyValue ) );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", szZKeyValue );

   nRC = ActivateObjectInstance( vTZCMLPLR, "TZCMLPLR", vSubtask, vKZDBHQUA, zSINGLE | zLEVEL_APPLICATION );


   DropObjectInstance( vKZDBHQUA );
   MB_SetMessage( vSubtask, 1, "" );

   if ( nRC < 0 )
   {
      strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Unable to activate CPLR '" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szName );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "' from database! " );
      MessageSend( vSubtask, "CM00277", "Configuration Management",
                   szERR_Msg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   SetNameForView( *vTZCMLPLR, "TZCMLPLR", vSubtask, zLEVEL_TASK );
   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_IncludeCPLR( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMLPLR;
   zVIEW    vTZCMCRWO;
   zLONG    lZKey;
   zLONG    lC_ZKey;
   zCHAR    szName[ 33 ];

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( &vTZCMCRWO, "TZCMCRWO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( SetCursorFirstSelectedEntity( vTZCMCRWO, "CPLR", "User" ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00224", "Configuration Management",
                   "A CPLR must be selected.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      return( 0 );
   }

   if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lC_ZKey, vTZCMLPLO, "CorrespondingCPLR", "ZKey" );
      GetStringFromAttribute( szName, zsizeof( szName ), vTZCMLPLO, "CorrespondingCPLR", "Name" );

      if ( zwfnTZCMLPLD_ActivateLPLR( vSubtask, &vTZCMLPLR, lC_ZKey, szName ) >= 0 )
      {
         GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "LPLR", "ZKey" );
         SetCursorFirstEntityByInteger( vTZCMLPLR, "LPLR", "ZKey", lZKey, "" );
         RelinkInstanceToInstance( vTZCMLPLO, "CorrespondingCPLR", vTZCMLPLR, "CPLR" );
         RelinkInstanceToInstance( vTZCMLPLO, "LPLR", vTZCMLPLR, "LPLR" );
         ExcludeEntity( vTZCMLPLO, "CorrespondingCPLR", zREPOS_NONE );
         CommitObjectInstance( vTZCMLPLR );

         GetIntegerFromAttribute( &lZKey, vTZCMCRWO, "CPLR", "ZKey" );

         if ( lC_ZKey != lZKey )
            DropObjectInstance( vTZCMLPLR );
      }
   }

   GetIntegerFromAttribute( &lZKey, vTZCMCRWO, "CPLR", "ZKey" );
   GetStringFromAttribute( szName, zsizeof( szName ), vTZCMCRWO, "CPLR", "Name" );

   if ( GetViewByName( &vTZCMLPLR, "TZCMLPLR", vSubtask, zLEVEL_TASK ) < 0 )
   {
      if ( zwfnTZCMLPLD_ActivateLPLR( vSubtask, &vTZCMLPLR, lZKey, szName ) < 0 )
      {
         RefreshCtrl( vSubtask, "CPLR_description" );
         RefreshCtrl( vSubtask, "CPL_description" );
         return( -1 );
      }
   }

   IncludeSubobjectFromSubobject( vTZCMLPLO, "CorrespondingCPLR", vTZCMLPLR, "CPLR", zPOS_AFTER );
   SetAttributeFromAttribute( vTZCMLPLO, "CorrespondingCPLR", "DerivedCPL_Description", vTZCMLPLR, "CPL", "Desc" );

   CommitObjectInstance( vTZCMLPLR );

   RefreshCtrl( vSubtask, "CPLR_description" );
   RefreshCtrl( vSubtask, "CPL_description" );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_PrebuildNewLPLR( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zLONG    lZKey;
   zLONG    lHighZKey;
   zSHORT   nRC;

   if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) > 0 )
   // DonC added code on 2/26/2014 to initialize a unique ZKey here. Make it the next high ZKey for all LPLR's.
   {
      lHighZKey = 0;
      nRC = SetCursorFirstEntity( vTZCMWKSO, "LPLR", "" );
      while ( nRC >= zCURSOR_SET )
      {
         GetIntegerFromAttribute( &lZKey, vTZCMWKSO, "LPLR", "ZKey" );
         if ( lZKey > lHighZKey )
            lHighZKey = lZKey;
         nRC = SetCursorNextEntity( vTZCMWKSO, "LPLR", "" );
      }
      lHighZKey = lHighZKey + 1;
      CreateEntity( vTZCMWKSO, "LPLR", zPOS_AFTER );
      SetAttributeFromInteger( vTZCMWKSO, "LPLR", "ZKey", lHighZKey );
   }

   if ( ActivateEmptyObjectInstance( &vTZCMLPLO, "TZCMLPLO", vSubtask, zSINGLE | zLEVEL_APPLICATION ) >= 0 )
   {
      // DonC replaced CreateMetaEntity by CreateEntity on 2/26/2014 because LPLR MetaZKey is not yet initialized.
      CreateEntity( vTZCMLPLO, "LPLR", zPOS_AFTER );
      SetNameForView( vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
      SetAttributeFromInteger( vTZCMLPLO, "LPLR", "ZKey", lHighZKey );
   }

   // KJS 03/22/13 - Temporarily taking this out becuase we don't have a CPLR list (we don't have an
   // ODBC driver for Repos9JA and that is causing issues.)
   //zwTZCMLPLD_BuildCPLR_List( vSubtask );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_DeleteLPLR( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMCPRO;
   zCHAR    szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szSearchFileName[ zMAX_FILESPEC_LTH + 1  ];
   zCHAR    szERR_Msg[ zSHORT_MESSAGE_LTH + 1 ]; // at least length of szName + 89
   zCHAR    szFilePref[ 33 ];
   zCHAR    szName[ 34 ];
   zSHORT   nRC;
   zSHORT   nCount;
   zLONG    hFile;
   HWND     hWndList;
   zLONG    lZKey;
   zLONG    lLPLR_ZKey;
   HWND     hWnd;
   HINSTANCE hInst;

   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szName, zsizeof( szName ), vTZCMWKSO, "LPLR", "Name" );
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMWKSO, "LPLR", "ExecDir" );
   ofnTZCMWKSO_AppendSlash( szFileName );
   strcpy_s( szSearchFileName, zsizeof( szSearchFileName ), szFileName );
   strncpy_s( szFilePref, zsizeof( szFilePref ), szName, zsizeof( szFilePref ) - 1 );
   for ( nRC = 0; nRC < 32; nRC++ )
   {
      if ( !( szFilePref[ nRC ] ) )
         break;

      if ( szFilePref[ nRC ] == ' ' )
         szFilePref[ nRC ] = '_';
   }

   szFilePref[ nRC ] = 0;
   strcat_s( szFileName, zsizeof( szFileName ), szFilePref );
   strcat_s( szFileName, zsizeof( szFileName ), ".XLP" );
   nRC = GetViewByName( &vTZCMLPLO, szName, vSubtask, zLEVEL_APPLICATION );
   if ( nRC > 0 )
   {
      strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Project " );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szName );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), " is currently in use.\n" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "Unable to delete!" );
      MessageSend( vSubtask, "CM00226", "Configuration Management",
                   szERR_Msg,
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( 0 );
   }

   if ( ActivateOI_FromFile( &vTZCMLPLO, "TZCMLPLO", vSubtask, szFileName, zSINGLE | zNOI_OKAY | zIGNORE_ERRORS ) < 0 )
   {
      DeleteEntity( vTZCMWKSO, "LPLR", zREPOS_NONE );
   }
   else
   {
      // If this LPLR is defined against a CPLR in the repository, make sure
      // no components are currently checked out.  If they are, we won't let
      // the LPLR be deleted.
      if ( CheckExistenceOfEntity( vTZCMWKSO, "CorrespondingCPLR" ) >= zCURSOR_SET &&
           CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) >= zCURSOR_SET )
      {
         GetIntegerFromAttribute( &lZKey, vTZCMWKSO, "CorrespondingCPLR", "ZKey" );
         nRC = oTZCMCPRO_ActivateCPLR( &vTZCMCPRO, (zLONG) lZKey, vSubtask );
         if ( nRC >= 0 )
         {
            // To determine if the LPLR has any components checked out,
            // position on the first component in the LPLR that is checked out
            // to the LPLR.  This is first existence of LPLR_CheckOut with a ZKey
            // that matches the LPLR.
            GetIntegerFromAttribute( &lLPLR_ZKey, vTZCMWKSO, "LPLR", "ZKey" );
            if ( SetCursorFirstEntityByInteger( vTZCMCPRO, "LPLR_CheckOut", "ZKey", lLPLR_ZKey, "CPLR" ) >= 0 )
            {
               DropObjectInstance( vTZCMCPRO );
               strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Your Project has components currently checked out.\n" );
               strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "You are not allowed to delete the Project." );
               MessageSend( vSubtask, "CM00287", "Configuration Management",
                            szERR_Msg,
                            zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
               return( 0 );
            }
         }
         else
         if ( nRC = -1 )
         {
            // nRC of -1 means we got to the Repository OK but the CPLR
            // entry has been deleted. Thus we will continue with the delete
            // after giving a warning.
            vTZCMCPRO = 0;   // Set view to zero since the entry could not be accessed properly.
            MessageSend( vSubtask, "CM00708", "Configuration Management",
                         "CPLR has been deleted from Repository. Continuing with Project delete.",
                         zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
         }
         else
         {
            // The repository could not be accessed.  Ask the user if he wants
            // to delete the LPLR anyway. (This might be valid if the repository has been bombed.)
            vTZCMCPRO = 0;   // Set view to zero since the entry could not be accessed properly.
            strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "The Repository cannot be activated.\n" );
            strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "Do you want to continue with the delete?" );
            if ( MessagePrompt( vSubtask, "CM00227", "Configuration Management",
                              szERR_Msg, zBEEP, zBUTTONS_YESNO, zRESPONSE_NO,  0 ) == zRESPONSE_NO )
            {
               return( 0 );
            }
         }
      }

      if ( SetCursorFirstEntity( vTZCMLPLO, "W_MetaDef", "LPLR" ) >= zCURSOR_SET )
      {
         strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Project " );
         strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szName );
         strcat_s( szERR_Msg, zsizeof( szERR_Msg ), " contains Meta definitions.\n" );
         strcat_s( szERR_Msg, zsizeof( szERR_Msg ),
            "Meta files in this Project directories will NOT be deleted.\n" );
         strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "Continue with Delete?" );
      }
      else
      {
         strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Continue with delete of Project " );
         strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szName );
         strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "?" );
      }

      if ( MessagePrompt( vSubtask, "CM00227", "Configuration Management",
                          szERR_Msg, zBEEP, zBUTTONS_YESNO, zRESPONSE_NO,  0 ) == zRESPONSE_NO )
      {
         return( 0 );
      }

      ExcludeEntity( vTZCMWKSO, "LPLR", zREPOS_NONE );

      // As of 4/24/96, we are not removing the xlp file for the initial
      // LPLR.  If an xlp file was created as an external LPLR with a new
      // LPLR name, then we will delete it.  We will determine this by
      // checking to see how many xlp files exist for this LPLR directory.
      // If the count is more than 1, we will delete the file.  Otherwise,
      // we won't.  Another way to look at this is that we will not delete
      // the last xlp file for the LPLR directory.  There will always be
      // one xlp file left with the metas in the lplr.  This will allow an
      // external LPLR to always be defined for that LPLR.

      // Using the Windows interface, create an invisible window which
      // contains the list of all files in the directory of type *.xlp.
      // The *.xlp is passed to Windows to delineate the files listed.
      // Since the list should be a list of one, we only care about the first
      // one in the list.

      strcat_s( szSearchFileName, zsizeof( szSearchFileName ), "*.xlp" );

      GetWindowHandle( (zPULONG) &hWnd, 0, vSubtask, 0 );
      hInst = (HINSTANCE) GetApplicationInstance( vSubtask );

      hWndList = CreateWindow( "ListBox", NULL, WS_CHILD | LBS_SORT, 1, 1, 1, 1, hWnd, (HMENU) 101, hInst, NULL );

      SendMessage( hWndList, WM_SETREDRAW, FALSE, 0L );
      SendMessage( hWndList, LB_DIR, 0x0000, (LONG)(LPSTR) szSearchFileName );
      nCount = ( int )SendMessage( hWndList, LB_GETCOUNT, 0, 0L );
      if ( nCount > 1 )
         hFile = SysOpenFile( vSubtask, szFileName, COREFILE_DELETE );
   }

   if ( vTZCMLPLO != 0 )
   {
      if ( CheckExistenceOfEntity( vTZCMWKSO, "CorrespondingCPLR" ) >= zCURSOR_SET &&
           CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) >= zCURSOR_SET && vTZCMCPRO != 0 )
      {
         GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "LPLR", "ZKey" );
         SetCursorFirstEntityByInteger( vTZCMCPRO, "LPLR", "ZKey", lZKey, "" );
         DeleteEntity( vTZCMCPRO, "LPLR", zREPOS_NONE );
         SetNameForView( vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK );
         CommitObjectInstance( vTZCMCPRO );
         DropObjectInstance( vTZCMCPRO );
      }
      DropObjectInstance( vTZCMLPLO );
   }

   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );
   if ( SetCursorFirstEntity( vTZCMWKSO, "LPLR", "" ) != zCURSOR_SET )
      SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow, "TZCMLPLD", "NewLPLR" );

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_LoadLPLR( zVIEW vSubtask )
{
   zVIEW    vTaskLPLR;
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vZeidonCM;
   zVIEW    vActiveMetas;
   zVIEW    vCompList;
   zSHORT   nRC;
   zCHAR    szMsg[ zLONG_MESSAGE_LTH + 1 ]; // at least length of szFileName plus 20 char
   zCHAR    szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szFilePref[ 33 ];
   zCHAR    szName[ 33 ];
   zLONG    lZKey;

   TraceLineS("*** zwTZCMLPLD_LoadLPLR *** ", "");

   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   if ( vTZCMWKSO <= 0 )
   {
      MessageSend( vSubtask, "CM00228", "Configuration Management",
                   "TZCMWKSO View not found",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   GetStringFromAttribute( szName, zsizeof( szName ), vTZCMWKSO, "LPLR", "Name" );
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMWKSO, "LPLR", "ExecDir" );
   ofnTZCMWKSO_AppendSlash( szFileName );
   strncpy_s( szFilePref, zsizeof( szFilePref ), szName, zsizeof( szFilePref ) - 1 );
   for ( nRC = 0; nRC < 32; nRC++ )
   {
      if ( !( szFilePref[ nRC ] ) )
         break;

      if ( szFilePref[ nRC ] == ' ' )
         szFilePref[ nRC ] = '_';
   }

   szFilePref[ nRC ] = 0;
   strcat_s( szFileName, zsizeof( szFileName ), szFilePref );
   strcat_s( szFileName, zsizeof( szFileName ), ".XLP" );
   nRC = ActivateOI_FromFile( &vTZCMLPLO, "TZCMLPLO", vSubtask, szFileName, zSINGLE | zLEVEL_APPLICATION | zIGNORE_ERRORS | zNOI_OKAY );
   if ( vTZCMLPLO > 0 )
   {
      // Get the ZKey from the LPLR just read and store it in the TZCMWKSO
      // object in both the default ZKey and the LPLR ZKey.
      // The following line of code was replaced by DonC on 12/19/13 because the TZCMLPLO OI doesn't
      // always have the same ZKey as the TZCMWKSO.LPLR entity.
      //GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "LPLR", "ZKey" );
      GetIntegerFromAttribute( &lZKey, vTZCMWKSO, "LPLR", "ZKey" );
      SetAttributeFromInteger( vTZCMWKSO, "RepositoryClient", "DefaultLPLR_ZKey", lZKey );

      // We had an error where a new or imported project wasn't correctly copying the description from TZCMLPLO to TZCMWKSO,
      // so copy.
      SetAttributeFromAttribute( vTZCMWKSO, "LPLR", "Desc", vTZCMLPLO, "LPLR", "Desc" );

      oTZCMWKSO_CommitWorkstation( vTZCMWKSO );

      zwfnTZCMLPLD_SwitchLPLR( vSubtask, vTZCMLPLO );

      SetNameForView( vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
      SetNameForView( vTZCMLPLO, "TaskLPLR", vSubtask, zLEVEL_TASK );

     // DonC hack put in on 5/8/2007. When migrating metas, the OpenCM_Metas object was not
     // always initialized correctly, so I'm forcing it here to match the TaskLPLR.
     GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
     GetViewByName( &vActiveMetas, "OpenCM_Metas", vZeidonCM, zLEVEL_SUBTASK );
     if ( CheckExistenceOfEntity( vActiveMetas, "LPLR" ) < zCURSOR_SET )
        CreateMetaEntity( vSubtask, vActiveMetas, "LPLR", zPOS_AFTER );
     SetMatchingAttributesByName( vActiveMetas, "LPLR", vTZCMLPLO, "LPLR", zSET_ALL );

      // Store the description into the temporary Desc attribute.
      SetAttributeFromAttribute( vTZCMLPLO, "LPLR", "TempDesc", vTZCMLPLO, "LPLR", "Desc" );

      if ( GetViewByName( &vCompList, "CompList", vSubtask, zLEVEL_TASK ) >= 0 )
           RefreshWindow( vCompList );
      // force reactivation of CPLR
      if ( GetViewByName( &vTZCMLPLO, "TZCMCPRO", vSubtask, zLEVEL_TASK ) >= 0 )
         DropObjectInstance( vTZCMLPLO );
   }
   else
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Project File " );
      strcat_s( szMsg, zsizeof( szMsg ), szFileName );
      strcat_s( szMsg, zsizeof( szMsg ), " not found!" );
      MessageSend( vSubtask, "CM00229", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_UpdateWorkDirectory
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*LOCAL */  OPERATION
zwTZCMLPLD_UpdateWorkDirectory( zVIEW vSubtask,
                                zVIEW vTZCMLPLO )
{
   zVIEW    vKZAPPLOO = 0;
   zCHAR    szNewWorkDirectory[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szAppDirectory[ zMAX_FILESPEC_LTH + 1 ];

   // Save Work Directory in Zeidon.app
   szAppDirectory[ 0 ] = 0;
   if ( zwTZCMLPLD_GetZeidonApp( vSubtask, &vKZAPPLOO, szAppDirectory, zsizeof( szAppDirectory ) ) >= 0 )
   {
      if ( SetCursorFirstEntityByAttr( vKZAPPLOO, "APPLICATION", "APP_NAME", vTZCMLPLO, "LPLR", "Name", "" ) >= zCURSOR_SET )
      {
         GetCtrlText( vSubtask, "edWorkDirectory", szNewWorkDirectory, zMAX_FILESPEC_LTH );
         if ( CompareAttributeToString( vKZAPPLOO, "APPLICATION", "APP_LOCAL", szNewWorkDirectory ) != 0 )
         {
            return( 1 );
         }
      }
      DropView( vKZAPPLOO );
   }

   return( 0 );
} // zwTZCMLPLD_UpdateWorkDirectory


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_SaveLPLR_Desc( zVIEW vSubtask )
{
   // Save the LPLR Description (which is in attribute TempDesc) in the LPLR object and also in the TZCMWKSO object.

   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMULWO;
   zVIEW    vKZAPPLOO = 0;
   zCHAR    szWorkDirectory[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szWorkEnv[ zMAX_FILESPEC_LTH + 1  ];
   zCHAR    szAppDirectory[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zSHORT   nValid;

   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   SetAttributeFromAttribute( vTZCMLPLO, "LPLR", "Desc", vTZCMLPLO, "LPLR", "TempDesc" );
   SetAttributeFromAttribute( vTZCMWKSO, "LPLR", "Desc", vTZCMLPLO, "LPLR", "TempDesc" );

   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );
   oTZCMLPLO_CommitLPLR( vTZCMLPLO );

   // Save the TZCMULWO object, if it's been modified.
   //GetViewByName( &vTZCMULWO, "TZCMULWO", vSubtask, zLEVEL_TASK );
   if ( GetViewByName( &vTZCMULWO, "TZCMULWO", vSubtask, zLEVEL_TASK ) > 0 && ObjectInstanceUpdatedFromFile( vTZCMULWO ) == 1 )
   {
      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTZCMLPLO, "LPLR", "MetaSrcDir" );
      strcat_s( szFileName, zsizeof( szFileName ), "\\TZCMULWO.POR" );
      CommitOI_ToFile( vTZCMULWO, szFileName, zSINGLE );
   }

   // Save Work Directory in Zeidon.app
   szWorkDirectory[ 0 ] = 0;
   if ( zwTZCMLPLD_GetZeidonApp( vSubtask, &vKZAPPLOO, szAppDirectory, zsizeof( szAppDirectory ) ) < 0 )
      return( -1 );

   // check Work Directory
   GetCtrlText( vSubtask, "edWorkDirectory", szWorkDirectory, zMAX_FILENAME_LTH );
   if ( zstrcmp( szWorkDirectory, "" ) == 0 )
   {
         MessageSend( vSubtask, "CM00288", "Configuration Management",
                      "Temporary Work Directory is required.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         SetFocusToCtrl( vSubtask, "edWorkDirectory" );
         return( -1 );
   }
   SysConvertEnvironmentString( szWorkEnv, zsizeof( szWorkEnv ), szWorkDirectory );
   nValid = IsValidDirOrFile( vSubtask, szWorkEnv, "Temporary Work", TRUE, TRUE, zsizeof( szWorkEnv ) );
   if ( nValid == 1 )
   {
      if ( SetCursorFirstEntityByAttr( vKZAPPLOO, "APPLICATION", "APP_NAME", vTZCMLPLO, "LPLR", "Name", "" ) >= zCURSOR_SET )
      {
         SetAttributeFromString( vKZAPPLOO, "APPLICATION", "APP_LOCAL", szWorkDirectory );
      }
      // Commit Zeidon.app
      if ( CommitOI_ToFile( vKZAPPLOO, szAppDirectory, zASCII ) < 0 )
      {
         MessageSend( vSubtask, "CM00223", "Configuration Management",
                      "Zeidon.App could not be Saved !",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( -1 );
      }
   }
   else
   {
      if ( nValid != zRESPONSE_NO )
      {
         zCHAR  szERR_Msg[ zMAX_FILENAME_LTH +  zSHORT_MESSAGE_LTH + 1  ];  // directory length + message

         strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Could not create Temporary Work Directory:\n " );
         strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szWorkDirectory );
         MessageSend( vSubtask, "CM00298", "Configuration Management",
                      szERR_Msg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }
      SetFocusToCtrl( vSubtask, "edWorkDirectory" );
      return( -1 );
   }

   DropView( vKZAPPLOO );
   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_SaveLPLR( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMCPRO;
   zVIEW    vCompList;
   int      nRC;
   long     Type;

   // DonC Description, 6/8/97
   // This code creates all the W_MetaDef entries in the LPLR if they don't
   // already exist.
   // If the LPLR entry in TZCMWKSO is empty, it excludes it. It knows this
   // if its ZKey is 0.
   // If includes the LPLR entry into TZCMWKSO and then commits both
   // TZCMWKSO and TZCMLPLO.
   // Finally, it finishes by committing the CPLR object, if one was read
   // from the Repository.

   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   // Make sure TZCMWKSO is positioned on same LPLR entry as TZCMLPLO.
   SetCursorFirstEntityByAttr( vTZCMWKSO, "LPLR", "ZKey", vTZCMLPLO, "LPLR", "ZKey", 0 );

   // Assume here that the TempDesc attribute is correct so copy it to Desc.
   SetAttributeFromAttribute( vTZCMLPLO, "LPLR", "Desc", vTZCMLPLO, "LPLR", "TempDesc" );

   if ( ( vTZCMWKSO > 0 ) && ( vTZCMLPLO > 0 ) )
   {
      // Create the W_MetaType entries if they don't already exist.
      if ( CheckExistenceOfEntity( vTZCMLPLO, "W_MetaType" ) < zCURSOR_SET )
      {
         for ( Type = 0; Type <= zSOURCE_MAX_META; Type++ )
         {
            CreateEntity( vTZCMLPLO, "W_MetaType", zPOS_AFTER );
            SetAttributeFromInteger( vTZCMLPLO, "W_MetaType", "Type", Type );
         }

         for ( Type = 2000; Type <= zREFER_MAX_META; Type++ )
         {
            CreateEntity( vTZCMLPLO, "W_MetaType", zPOS_AFTER );
            SetAttributeFromInteger( vTZCMLPLO, "W_MetaType", "Type", Type );
         }
      }

      // Delete the LPLR entry in the work station object if it is empty.
      if ( CompareAttributeToInteger( vTZCMWKSO, "LPLR", "ZKey", 0 ) == 0 )
         DeleteEntity( vTZCMWKSO, "LPLR", zREPOS_NONE );

      // Add the new LPLR to the work station object and order the entries
      // by name.
      nRC = IncludeSubobjectFromSubobject( vTZCMWKSO, "LPLR", vTZCMLPLO, "LPLR", zPOS_AFTER );
      OrderEntityForView( vTZCMWKSO, "LPLR", "Name A" );

      oTZCMWKSO_CommitWorkstation( vTZCMWKSO );
      oTZCMLPLO_CommitLPLR( vTZCMLPLO );
   }

   GetViewByName( &vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK );
   if ( vTZCMCPRO > 0 )
     nRC = CommitObjectInstance( vTZCMCPRO );

   if ( GetViewByName( &vCompList, "CompList", vSubtask, zLEVEL_TASK ) >= 0 )
        RefreshWindow( vCompList );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_ExitDialog( zVIEW vSubtask )
{
   if ( zwTZCMLPLD_CheckForSave( vSubtask ) >= 0 )
   {
      // Clean up the CM views/object instances.
      zwTZCMLPLD_CleanCM_Views( vSubtask );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckForSave( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zSHORT   nRC;

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      // If the Description has changed, prompt the user to ask if he wants to
      // save it.
      nRC = CompareAttributeToAttribute( vTZCMLPLO, "LPLR", "Desc",  vTZCMLPLO, "LPLR", "TempDesc" );

      if ( nRC || zwTZCMLPLD_UpdateWorkDirectory( vSubtask, vTZCMLPLO ) == 1 )
      {
         if ( MessagePrompt( vSubtask, "CM00282", "Configuration Management", "Save current Project",
                             zBEEP, zBUTTONS_YESNO, zRESPONSE_YES,  0 ) == zRESPONSE_YES )
         {
            if ( zwTZCMLPLD_SaveLPLR_Desc( vSubtask ) < 0 )
            {
               SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, "", "" );
               return( -1 );
            }
         }
      }
   }

   if ( GetViewByName( &vTZCMLPLO, "TaskLPLR", vSubtask, zLEVEL_TASK ) > 0 )
      TerminateLPLR( vSubtask );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_BuildCPLR_List( zVIEW vSubtask )
{
   zVIEW    vTZCMCRWO;
   zVIEW    vTZCMWKSO;
   zVIEW    vKZDBHQUA;
   zULONG   ulZKey;
   zCHAR    szZKey[18];
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ];
   zSHORT   nRC;

   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   if ( ActivateEmptyObjectInstance ( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) >= 0 )
   {
      SetNameForView( vKZDBHQUA, "KZDBHQUA", vSubtask, zLEVEL_TASK );
      CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
      CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );
   }
   else
      return( -1 );

   GetIntegerFromAttribute( (zPLONG)&ulZKey, vTZCMWKSO, "User", "ZKey" );
   SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "User" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "User" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "ZKey" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
   zltoa( ulZKey, szZKey, zsizeof( szZKey ) );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", szZKey );

   // Check to see if we have access to the Repository.  If the return code
   // to the ActivateObjectInstance is good, then we have access to the
   // Repository and all three types of LPLR creation are allowed:
   //   1.  Create normal LPLR under Respository.
   //   2.  Create external LPLR not known to the Repository.  This creates
   //       an empty LPLR except for Hotkey and PPE components.
   //   3.  Create external LPLR not known to the Repository, but having
   //       existing components.  In this case, use the XLP that already
   //       exists in the LPLR directory.  What we are doing here is just
   //       taking that XLP to create our entry in TZCMWKS8.POR.

   nRC = ActivateObjectInstance( &vTZCMCRWO, "TZCMCRWO", vSubtask, vKZDBHQUA, zSINGLE | zLEVEL_APPLICATION );

   DropObjectInstance( vKZDBHQUA );

   if ( nRC >= 0 )
   {
      if ( SetCursorFirstEntity( vTZCMCRWO, "CPLR", "User" ) != zCURSOR_SET )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "User " );
         GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMWKSO, "User", "Name" );
         strcat_s( szMsg, zsizeof( szMsg ), " is not authorized\nfor access to any CPLR's." );
         MessageSend( vSubtask, "CM00230", "Configuration Management",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }

      SetNameForView( vTZCMCRWO, "TZCMCRWO", vSubtask, zLEVEL_TASK );

      // Order the list by CPL and CPLR name.
      OrderEntityForView( vTZCMCRWO, "AccessAuthority", "CPL.Name A CPLR.Name A" );

      return( 0 );
   }

   MessageSend( vSubtask, "CM00231", "Configuration Management",
                "Repository is not active.",
                zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

   // Indicate that the LPLR cannot be of type "Repository", for the DisableRepositoryOK function.
   SetAttributeFromString( vTZCMWKSO, "LPLR", "LPLR_Type", "2" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_DisableRepositoryOK( zVIEW vSubtask )
{
   zVIEW    vTZCMWKSO;
   zVIEW    vKZAPPLOO = 0;
   zCHAR    szLPLR_Type[ 2 ];
   zCHAR    szZeidonDirectory[ zMAX_FILESPEC_LTH + 1 ];

   szZeidonDirectory[ 0 ] = 0;

   // Disable the RepositoryOK action, if the Repository is not active.
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szLPLR_Type, zsizeof( szLPLR_Type ), vTZCMWKSO, "LPLR", "LPLR_Type" );
   if ( szLPLR_Type[ 0 ] == '2' )
      EnableAction( vSubtask, "RepositoryOK", 0 );
   else
      EnableAction( vSubtask, "RepositoryOK", 1 );

   // Set Work Directory
   if ( zwTZCMLPLD_GetZeidonApp( vSubtask, &vKZAPPLOO, szZeidonDirectory, zsizeof( szZeidonDirectory ) ) >= 0 )
   {
      szZeidonDirectory[ 0 ] = 0;
      zwTZCMLPLD_GetWorkDir( vKZAPPLOO, szZeidonDirectory );
      SetCtrlText( vSubtask, "edWorkDirectory", szZeidonDirectory );
      DropView( vKZAPPLOO );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_BuildCI_List( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCM_ChkInList;
   zLONG    lType;
   zLONG    lStatus;
   zLONG    lUpdateInd;
   zSHORT   nRC;
   zSHORT   nChkInERD_Flag; // Used to indicate ERD is in chkin list
   zSHORT   nChkInSA_Flag;  // Used to indicate SA is in chkin list
   zSHORT   nChkInTE_Flag;  // Used to indicate TE is in chkin list
   zSHORT   lFlag;
   zVIEW    vTZCMAUDO;

   lFlag = 0;

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( ActivateEmptyObjectInstance( &vTZCM_ChkInList, "TZCMLPLO", vSubtask, zSINGLE ) >= 0 )
   {
      CreateEntity( vTZCM_ChkInList, "LPLR", zPOS_AFTER );
      SetMatchingAttributesByName( vTZCM_ChkInList, "LPLR", vTZCMLPLO, "LPLR", zSET_ALL );
      SetNameForView( vTZCM_ChkInList, "TZCM_ChkInList", vSubtask, zLEVEL_TASK );
   }

   //BL, 2000.01.25 Is a Subject Area updated, then set all SubjectAreas, ERD
   //               and TE in CheckIn List
   if ( SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaType", "Type", zSOURCE_SA_META, "" ) == zCURSOR_SET )
   {
      if ( (SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 2, "" ) == zCURSOR_SET) ||
           (SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 3, "" ) == zCURSOR_SET) )
         lFlag = 1;
   }

   // Is the TE updated, then set all Subject Areas and ERD in CheckIn List
   if ( SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaType", "Type", zSOURCE_DTE_META, "" ) == zCURSOR_SET )
   {
      if ( (SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 2, "" ) == zCURSOR_SET) ||
           (SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 3, "" ) == zCURSOR_SET) )
         lFlag = 1;
   }
   // Is the ERD updated, then set all Subject Areas and TE in CheckIn List
   if ( SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaType", "Type", zSOURCE_ERD_META, "" ) == zCURSOR_SET )
   {
      if ( (SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 2, "" ) == zCURSOR_SET) ||
           (SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 3, "" ) == zCURSOR_SET) )
      {
         lFlag = 1;
      }
   }

   nChkInERD_Flag = lFlag;
   nChkInSA_Flag  = lFlag;
   nChkInTE_Flag  = lFlag;

   nRC = ofnTZCMLPLO_GetNextCheckInType( vSubtask, vTZCMLPLO, 999 );
   while ( nRC >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lType, vTZCMLPLO, "W_MetaType", "Type" );

      nRC = SetCursorFirstEntity( vTZCMLPLO, "W_MetaDef", "" );

      // We want to temporarily eliminate UI_Specs from the list.  To do this and make it easy to remove later,
      // we will just set the nRC to indicate no W_MetaDefs if the Type is a UI_Spec.
      if ( lType == zSOURCE_UIS_META )
         nRC = -1;

      while ( nRC >= zCURSOR_SET )
      {
         GetIntegerFromAttribute( &lStatus, vTZCMLPLO, "W_MetaDef", "Status" );
         if ( lStatus == 1 )
         {
            if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", lType, "" ) != zCURSOR_SET )
            {
               CreateEntity( vTZCM_ChkInList, "W_MetaType", zPOS_AFTER );
               SetAttributeFromInteger( vTZCM_ChkInList, "W_MetaType", "Type", lType );
            }
            GetIntegerFromAttribute( &lUpdateInd, vTZCMLPLO, "W_MetaDef", "UpdateInd" );

            // Add an entry to the list if:
            //    1. The meta was updated or deleted.or update SourceFile
            // or
            //    2. The meta is a TE or SA or the ERD was updated.
            if ( (lUpdateInd == 2 || lUpdateInd == 3 || lUpdateInd == 4) ||
                 (nChkInSA_Flag  == 1 && lType == zSOURCE_SA_META) ||
                 (nChkInTE_Flag  == 1 && lType == zSOURCE_DTE_META) ||
                 (nChkInERD_Flag == 1 && lType == zSOURCE_ERD_META) )
            {
               CreateEntity( vTZCM_ChkInList, "W_MetaDef", zPOS_AFTER );
               SetMatchingAttributesByName( vTZCM_ChkInList, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zSET_ALL );

               if ( lType == zSOURCE_ERD_META )
               {
                  // Indicate a ERD is in ChkIn list.
                  nChkInERD_Flag = 1;
               }
            }
         }

         nRC = SetCursorNextEntity( vTZCMLPLO, "W_MetaDef", "" );
      }

      nRC = ofnTZCMLPLO_GetNextCheckInType( vSubtask, vTZCMLPLO, lType );
   }

   if ( SetCursorFirstEntity( vTZCM_ChkInList, "W_MetaDef", "LPLR" ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00232", "Configuration Management",
                   "The list of metas Available for Check In is Empty",
                   zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToTopWindow, 0, 0 );
      DropObjectInstance( vTZCM_ChkInList );
      return( 0 );
   }

   // -------
   // Frank H.
   // now build an Object for the AuditTrail.

   nRC = ActivateEmptyObjectInstance( &vTZCMAUDO, "TZCMAUDO", vSubtask, zSINGLE | zLEVEL_APPLICATION );
   CreateEntity( vTZCMAUDO, "AuditTrail", zPOS_AFTER );
   SetNameForView( vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK );

   // -------

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_FillAuditTrail( zVIEW vSubtask )
{
   zVIEW    vTZCML_ChkInList;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMAUDO;
   zVIEW    vTZCMREVO;
   zVIEW    vKZDBHQUA;
   zVIEW    vTZCMCPRO;

   int      nRC;
   zCHAR    szTimestamp[ 22 ];


   GetViewByName( &vTZCML_ChkInList, "TZCM_ChkInList", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );

   MB_SetMessage( vSubtask, 1, "Creating AuditTrail Object" );

   SysGetDateTime( szTimestamp, zsizeof( szTimestamp ) );
   SetAttributeFromString( vTZCMAUDO, "AuditTrail", "Timestamp", szTimestamp );

   GetViewByName( &vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK );

   IncludeSubobjectFromSubobject( vTZCMAUDO, "CPLR", vTZCMCPRO, "CPLR", zPOS_AFTER );

   if ( CheckExistenceOfEntity( vTZCMWKSO, "RepositoryClient" ) >= zCURSOR_SET )
      IncludeSubobjectFromSubobject( vTZCMAUDO, "RepositoryClient", vTZCMWKSO, "RepositoryClient", zPOS_AFTER );

   if ( CheckExistenceOfEntity( vTZCMAUDO, "RepositoryClient" ) >= zCURSOR_SET )
      SetAttributeFromAttribute( vTZCMAUDO, "AuditTrail", "WKS_Id", vTZCMAUDO, "RepositoryClient", "WKS_Id" );

   if ( CheckExistenceOfEntity( vTZCMAUDO, "User" ) >= zCURSOR_SET )
   {
      SetAttributeFromAttribute( vTZCMAUDO, "AuditTrail", "UserName", vTZCMAUDO, "User", "Name" );
      SetAttributeFromAttribute( vTZCMAUDO, "AuditTrail", "UserDesc", vTZCMAUDO, "User", "Desc" );
   }

   if ( ActivateEmptyObjectInstance ( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) >= 0 )
   {
      SetNameForView( vKZDBHQUA, "KZDBHQUA", vSubtask, zLEVEL_TASK );
      CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
      CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );
   }
   else
      return( -1 );

   SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "RevEvent" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "RevEvent" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "Type" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", "0" );

   nRC = ActivateObjectInstance( &vTZCMREVO, "TZCMREVO", vSubtask, vKZDBHQUA, zSINGLE | zLEVEL_APPLICATION | zACTIVATE_ROOTONLY );
   DropObjectInstance( vKZDBHQUA );

   if ( nRC >= 0 )
      IncludeSubobjectFromSubobject( vTZCMAUDO, "RevEvent", vTZCMREVO, "RevEvent", zPOS_AFTER );
   else
      MessageSend( vSubtask, "CM00299", "Check In:",
                   "Review Type 0 not found \n\nPlease resolve the problem with the SystemAdministrator.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CancelCheckIn( zVIEW vSubtask )
{
   zVIEW    vTZCM_ChkInList;
   zVIEW    vTZCMAUDO;

   GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK );

   if ( CompareAttributeToString( vTZCMAUDO, "AuditTrail", "Desc", "" ) != 0 ||
        CompareAttributeToString( vTZCMAUDO, "AuditTrail", "ShortDesc", "" ) != 0 )
   {
      if ( MessagePrompt( vSubtask, "CM00702",
                           "Configuration Management",
                           "Do you really want to abort your description entered below ?",
                           zBEEP, zBUTTONS_YESNO, zRESPONSE_YES,  0 ) == zRESPONSE_NO )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( -1 );
      }
   }

   if ( GetViewByName( &vTZCM_ChkInList, "TZCM_ChkInList", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      DropObjectInstance( vTZCM_ChkInList );
   }

   DropView( vTZCMAUDO );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckDuplicateERD_TE( zVIEW vSubtask,
                                 zVIEW vTZCML_ChkInList,
                                 zVIEW vTZCMCPRO )
{
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ]; //at least length of szName plus 94
   zCHAR    szName[ 33 ];

   // exists a ERD under an other name
   if ( CheckDuplicateComponents( vTZCML_ChkInList, vTZCMCPRO, zSOURCE_ERD_META, szName ) < 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "A component '" );
      strcat_s( szMsg, zsizeof( szMsg ), szName );
      strcat_s( szMsg, zsizeof( szMsg ), "' of type Data Model \nalready exists." );
      strcat_s( szMsg, zsizeof( szMsg ), "\n\nCheck In Processing aborted!" );
      MessageSend( vSubtask, "CM00702", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   //exists a TE under an other name
   if ( CheckDuplicateComponents( vTZCML_ChkInList, vTZCMCPRO,
                                  zSOURCE_DTE_META, szName ) < 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "A component '" );
      strcat_s( szMsg, zsizeof( szMsg ), szName );
      strcat_s( szMsg, zsizeof( szMsg ), "' of type Technical Environment \nalready exists." );
      strcat_s( szMsg, zsizeof( szMsg ), "\n\nCheck In Processing aborted!" );
      MessageSend( vSubtask, "CM00702", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckDuplicatePPE( zVIEW  vSubtask,
                              zVIEW  vTZCML_ChkInList,
                              zVIEW  vTZCMCPRO )
{
   zVIEW  vTZCMCPRO_PPE;
   zVIEW  vKZDBHQUA;
   zVIEW  vTZCML_ChkInList1;
   zSHORT nRC;
   zCHAR  szCPLRName[ 33 ];
   zCHAR  szMsg[ zSHORT_MESSAGE_LTH + 1 ]; // message includes CPLRName

   CreateViewFromViewForTask( &vTZCML_ChkInList1, vTZCML_ChkInList, 0 );

   //Is PPE in the Check In List and not in CPLR?
   if ( SetCursorFirstEntityByInteger( vTZCML_ChkInList1, "W_MetaType", "Type", (zSHORT) zSOURCE_PENV_META, "" ) == zCURSOR_SET &&
        CheckExistenceOfEntity( vTZCML_ChkInList1, "W_MetaDef" ) >= zCURSOR_SET &&
        SetCursorFirstEntityByInteger( vTZCMCPRO, "Z_MetaDef", "Type", (zSHORT) zSOURCE_PENV_META, "" ) != zCURSOR_SET )
   {
      //Activate CPLR with PPE
      SfActivateSysEmptyOI( &vKZDBHQUA, "KZDBHQUA", vSubtask, zMULTIPLE );
      CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
      SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "CPLR" );
      CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );
      SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "Z_MetaDef" );
      SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "Type" );
      SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", "10" );
      SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
      nRC = ActivateObjectInstance( &vTZCMCPRO_PPE, "TZCMCPRO", vSubtask, vKZDBHQUA, zSINGLE );

      DropObjectInstance( vKZDBHQUA );

      if ( nRC >= 0 )
      {
         GetStringFromAttribute( szCPLRName, zsizeof( szCPLRName ), vTZCMCPRO_PPE, "CPLR", "Name" );
         strcpy_s( szMsg, zsizeof( szMsg ), "A PPE already exists in the CPLR \n" );
         strcat_s( szMsg, zsizeof( szMsg ), szCPLRName );
         strcat_s( szMsg, zsizeof( szMsg ), ".\nCheck In Processing aborted!" );
         MessageSend( vSubtask, "CM00702", "Configuration Management",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         DropView( vTZCMCPRO_PPE );
         DropView( vTZCML_ChkInList1 );
         return( -1 );
      }

      DropView( vTZCMCPRO_PPE );
   }

   DropView( vTZCML_ChkInList1 );
   return( 0 );
}

//BL, 2000.04.03  Check current component for duplicate component names
//
//          RETURNS:    - 1   - duplicate component names within component type
//                      - 2   - duplicate component names between LODs and Dialogs
//                      = 0   - no duplicate component names
static zSHORT
zwfnTZCMLPLD_CheckCheckInList( zVIEW  vChkInList,
                               zPCHAR pchTypeLPLR1,
                               zPCHAR pchTypeLPLR2,
                               zPCHAR pchName )
{
   zVIEW         vChkInList_Copy;
   unsigned long ulZKeyLPLR1;
   unsigned long ulZKeyLPLR2;
   zLONG         lTypeLPLR1;
   zLONG         lTypeLPLR2;
   zSHORT        nRC;

   CreateViewFromViewForTask( &vChkInList_Copy, vChkInList, 0 );
   GetStringFromAttribute( pchName, 33, vChkInList, "W_MetaDef", "Name" );

   //exists a component with this name, then check the Key
   if ( SetCursorFirstEntityByString( vChkInList_Copy, "W_MetaDef", "Name", pchName, "LPLR" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKeyLPLR1, vChkInList, "W_MetaDef", "CPLR_ZKey" );
      do
      {
         GetIntegerFromAttribute( (zPLONG) &ulZKeyLPLR2, vChkInList_Copy, "W_MetaDef", "CPLR_ZKey" );
         // is a other component, check the type
         if ( ulZKeyLPLR1 != ulZKeyLPLR2 )
         {
            GetIntegerFromAttribute( &lTypeLPLR1, vChkInList, "W_MetaType", "Type" );
            GetIntegerFromAttribute( &lTypeLPLR2, vChkInList_Copy, "W_MetaType", "Type" );
            if ( lTypeLPLR1 >= 2000 )
               lTypeLPLR1 = lTypeLPLR1 - 2000;
            if ( lTypeLPLR2 >= 2000 )
               lTypeLPLR2 = lTypeLPLR2 - 2000;

            nRC = 0;
            if ( lTypeLPLR1 == lTypeLPLR2 )
               nRC = -1;

            //check duplicate Name between Dialogs and LODs
            if ( (lTypeLPLR2 == zSOURCE_DIALOG_META && lTypeLPLR1 == zSOURCE_LOD_META)  ||
                 (lTypeLPLR2 == zSOURCE_LOD_META && lTypeLPLR1 == zSOURCE_DIALOG_META) )
               nRC = -2;

            if ( nRC < 0 )
            {
               GetVariableFromAttribute( pchTypeLPLR1, 0, zTYPE_STRING, 125, vChkInList, "W_MetaType", "Type", "CM_Type", 0 );
               GetVariableFromAttribute( pchTypeLPLR2, 0, zTYPE_STRING, 125, vChkInList_Copy, "W_MetaType", "Type", "CM_Type", 0 );
               DropView( vChkInList_Copy );
               return( nRC );
            }
         } //endif ( ulZKeyLPLR1 != ulZKeyLPLR2 )
      }
      while ( SetCursorNextEntityByString( vChkInList_Copy, "W_MetaDef", "Name", pchName, "LPLR" ) >= zCURSOR_SET );
   } //endif ( SetCursorFirstEntityByString( vChkInList_Copy, "W_MetaDef"...

   DropView( vChkInList_Copy );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckDuplicateName( zVIEW vSubtask,
                               zVIEW vTZCML_ChkInList,
                               zVIEW vTZCMCPRO )
{
   zCHAR    szTypeCPLR[120];
   zCHAR    szTypeLPLR[120];
   zCHAR    szMsg[ zMAX_MESSAGE_LTH + 1 ]; // message includes twice szName and o. text
   zCHAR    szName[ 33 ];
   zSHORT   nRC;
   zSHORT   nRC1;
   zVIEW    vChkInList;

   //BL, 2000.02.17 check all components for duplicate name
   nRC = CheckAllDuplicateName( vTZCML_ChkInList, vTZCMCPRO, szTypeCPLR, szTypeLPLR, szName );

   // check duplication component names in CheckIn List
   if ( nRC >= 0 )
   {
      CreateViewFromViewForTask( &vChkInList, vTZCML_ChkInList, 0 );
      nRC1 = SetCursorFirstEntity( vChkInList, "W_MetaDef", "LPLR" );
      while ( nRC1 >= zCURSOR_SET )
      {
         nRC = zwfnTZCMLPLD_CheckCheckInList( vChkInList, szTypeCPLR, szTypeLPLR, szName );
         if ( nRC < 0 )
            break;

         nRC1 = SetCursorNextEntity( vChkInList, "W_MetaDef", "LPLR" );
      }

      DropView( vChkInList );
   }

   if ( nRC < 0 )
   {
      if ( nRC == -2 )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "You are trying to add a component '" );
         strcat_s( szMsg, zsizeof( szMsg ), szName );
         strcat_s( szMsg, zsizeof( szMsg ), "' of type " );
         strcat_s( szMsg, zsizeof( szMsg ), szTypeLPLR );
         strcat_s( szMsg, zsizeof( szMsg ), ",\nbut a component '" );
         strcat_s( szMsg, zsizeof( szMsg ), szName );
         strcat_s( szMsg, zsizeof( szMsg ), "' of type " );
         strcat_s( szMsg, zsizeof( szMsg ), szTypeCPLR );
         strcat_s( szMsg, zsizeof( szMsg ), " already exists in CPLR." );
      }
      else
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "You are trying to add a component '" );
         strcat_s( szMsg, zsizeof( szMsg ), szName );
         strcat_s( szMsg, zsizeof( szMsg ), "' of type " );
         strcat_s( szMsg, zsizeof( szMsg ), szTypeLPLR );
         strcat_s( szMsg, zsizeof( szMsg ), ",\nbut this component \nalready exists." );
      }

      strcat_s( szMsg, zsizeof( szMsg ), "\n\nCheck In Processing aborted!" );
      MessageSend( vSubtask, "CM00702", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // exists an ERD and TE under another name in Repository?
   if ( zwTZCMLPLD_CheckDuplicateERD_TE( vSubtask, vTZCML_ChkInList, vTZCMCPRO ) < 0 )
   {
      return( -1 );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
// returns < 0 - error
//         = 0 - nothing has happened ( just refresh)
//         > 0 - metas have been checked in
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckInReus( zVIEW  vSubtask )
{
   zVIEW    vTZCMREPO;
   zVIEW    vTZCMRPTO;
   zVIEW    vTZCMCPRO;
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCML_ChkInList;
   zVIEW    vTZCMAUDO;
   zVIEW    vCompList;
   zVIEW    vMeta;
   zVIEW    vZeidonCM;
   int      iDropInd;
   int      nBackupPerformed = 0;
   unsigned long ulZKey;
   zCHAR    szTaskView[ 33 ];
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ];
   int      nRC_CheckInMeta;
   int      k;
   int      nRC;

   SetNameForView( vSubtask,"TZCM_ChkInWindow", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   GetIntegerFromAttribute( (zPLONG)&ulZKey, vTZCMWKSO, "RepositoryClient", "DefaultLPLR_ZKey" );
   if ( CompareAttributeToInteger( vTZCMLPLO, "LPLR", "ZKey", (zLONG) ulZKey ) != 0 )
   {
      zwfnTZCMLPLD_SwitchLPLR( vSubtask, vTZCMLPLO );
      DropObjectInstance( vTZCMLPLO );
      GetViewByName( &vTZCMLPLO, "TaskLPLR", vSubtask, zLEVEL_TASK );
      SetNameForView( vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   }

   GetViewByName( &vTZCML_ChkInList, "TZCM_ChkInList", vSubtask, zLEVEL_TASK );
   GetIntegerFromAttribute( (zPLONG)&ulZKey, vTZCMLPLO, "CorrespondingCPLR", "ZKey" );

   if ( GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      MB_SetMessage( vSubtask, 1, "Activating Repository" );
      if ( oTZCMREPO_ActivateRepository( &vTZCMREPO, vSubtask ) < 0 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( -1 );
      }
   }

   MB_SetMessage( vSubtask, 1, "Activating CPLR" );
   if ( oTZCMCPRO_ActivateCPLR( &vTZCMCPRO, (zLONG) ulZKey, vSubtask ) >= 0 )
   {
      SetNameForView( vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK );
   }
   else
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "CPLR '" );

      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ),
                              vTZCMLPLO, "CorrespondingCPLR", "Name" );
      strcat_s( szMsg, zsizeof( szMsg ), "' not found on Installation! " );
      MessageSend( vSubtask, "CM00235", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   MB_SetMessage( vSubtask, 1, "" );

   if ( GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK ) > 0 &&
        CompareAttributeToString( vTZCMAUDO, "AuditTrail",  "ShortDesc", "" ) == 0 )
   {
      MessageSend( vSubtask, "CM00241", "Configuration Management",
                   "Please enter a short description for the Check In",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "ShortDescEdit" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );

      return( -1 );
   }

   if ( GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK ) > 0 &&
        CompareAttributeToString( vTZCMAUDO, "AuditTrail",  "Desc", "" ) == 0 )
   {
      MessageSend( vSubtask, "CM00241", "Configuration Management",
                   "Please enter a description for the Check In",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "DescEdit" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );

      return( -1 );
   }

   //BL, 2000.01.27 check duplicate name
   if ( zwTZCMLPLD_CheckDuplicateName( vSubtask, vTZCML_ChkInList, vTZCMCPRO ) != 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   // Test whether the CPLR ist not enqueued and enqueue it.
   if ( oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_ENQUEUE_FOR_CHECK_IN ) < 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   if ( oTZCMLPLO_RefreshLPLR( vSubtask, vTZCMLPLO, vTZCMCPRO ) < 0 )
   {
      oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );
      return( -1 );
   }

   // Delete all the ERD, LOD, and TE object instances under the CM
   // task so that those currently in memory will not be reused.  This
   // makes sure that all the objects are relinked in the proper order
   // and that the include flags are properly reset.
   // Note that, since no other tools are active, there should be
   // problem in deleting the OI's.
   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
   nRC = SfGetFirstNamedView( &vMeta, szTaskView, vZeidonCM, zLEVEL_SUBTASK );
   while ( nRC > 0 )
   {
      iDropInd = 0;
      // Skip past the name prefix to get to the period.
      k = 0;
      while ( (szTaskView[ k ] != '.') && (szTaskView[ k ] != 0) )
         k++;

      if ( szTaskView[ k ] != 0 )
      {
         if ( (zstrncmp( szTaskView + k + 1, "md", 2 ) == 0) ||
              (zstrncmp( szTaskView + k + 1, "te", 2 ) == 0) ||
              (zstrncmp( szTaskView + k + 1, "od", 2 ) == 0) )
         {
            DropObjectInstance( vMeta );
            iDropInd = 1;
         }
      }

      if ( iDropInd == 1 )
         nRC = SfGetFirstNamedView( &vMeta, szTaskView, vZeidonCM, zLEVEL_SUBTASK );
      else
         nRC = SfGetNextNamedView( &vMeta, szTaskView, vZeidonCM, zLEVEL_SUBTASK );
   }

   GetViewByName( &vTZCMRPTO, "TZCMRPTO", vSubtask, zLEVEL_TASK );
   if ( SetEntityCursor( vTZCMRPTO, "Z_MetaDef", 0,
         zQUAL_SCOPE_OI | zPOS_FIRST, 0, 0, 0, 0, 0, 0 ) >= zCURSOR_SET )
   {
      oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );

      strcpy_s( szMsg, zsizeof( szMsg ), "Metas have been refreshed. You may now choose" );
      strcat_s( szMsg, zsizeof( szMsg ), "\nto continue the Check In process( OK ), or " );
      strcat_s( szMsg, zsizeof( szMsg ), "\nto Cancel the Check In process( Cancel ) and" );
      strcat_s( szMsg, zsizeof( szMsg ), "\nreview the Refresh Report." );
      strcat_s( szMsg, zsizeof( szMsg ), "\n\n Continue check in?" );
      nRC = MessagePrompt( vSubtask, "CM00237", "Configuration Management",
                           szMsg, zBEEP, zBUTTONS_OKCANCEL,
                           zRESPONSE_OK, 0 );
      if ( nRC == zRESPONSE_CANCEL )
      {
         SetWindowActionBehavior( vSubtask, zWAB_ReturnToTopWindow, 0, 0 );
         return( -1 );
      }

      // after the RefreshReport:
      // Test whether the CPLR ist not enqueued and enqueue it.
      if (oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_ENQUEUE_FOR_CHECK_IN ) < 0 )
      {
         return( -1 );
      }
   }
   if ( vTZCMRPTO > 0 )
   {
      DropObjectInstance( vTZCMRPTO );
   }

   // Frank H. (29/04/97): here I removed the Enqueueing
   // because I want to Lock just the Transaction.

   // Frank H. (16/05/97): here I removed the ZIPping of the Repository
   // because we now have Transaction security (on the commit).

   // nRC = oTZCMREPO_PreCheckInBackup( vTZCMLPLO, vSubtask );
   if ( nRC == -2 )
   {

      // Frank H. (29/04/97): here I removed the Dequeueing
      // because I want to Lock just the Transaction.

      if ( GetViewByName( &vCompList, "CompList", vSubtask, zLEVEL_TASK ) >= 0 )
         RefreshWindow( vCompList );

      return( -1 );
   }
   else
   {
      if ( nRC == -1 )
      {
         nBackupPerformed = 0;
      }
      else
      {
         nBackupPerformed = 1;
      }
   }

   // Here I am filling the audit Trail (apart from the Metas - this happens in CheckInMetas)
   zwTZCMLPLD_FillAuditTrail( vSubtask );

   nRC_CheckInMeta = oTZCMLPLO_CheckInMetas( vSubtask, vTZCML_ChkInList,
                                             vTZCMCPRO, 1 );

   if ( nRC_CheckInMeta != zCURSOR_SET )
   {
      //BL, 2000.01.20 -2 = Meta is not checked out by current User
      if ( nRC_CheckInMeta != -2 )
         MessageSend( vSubtask, "CM00240", "Configuration Management",
                      "An Error occured during CheckIn -- aborting CheckIn",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

      oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );
      return( -1 );
   }

   oTZCMCPRO_CleanUpER_TE_SA( vTZCMCPRO, vTZCMLPLO );
   SetAttributeFromAttribute( vTZCMLPLO, "LPLR", "LastRefreshDate", vTZCMCPRO, "CPLR", "LastCheckInDate" );
   nRC = CommitObjectInstance( vTZCMCPRO );
   MB_SetMessage( vSubtask, 1, "Committing Project" );
   oTZCMLPLO_CommitLPLR( vTZCMLPLO );

   MB_SetMessage( vSubtask, 1, "" );

   if ( GetViewByName( &vCompList, "CompList", vSubtask, zLEVEL_TASK ) >= 0 )
      RefreshWindow( vCompList );

   if ( nRC_CheckInMeta >= 0 && nRC >= 0 &&
        GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      // now, commit the AuditTrail Object...
      CommitObjectInstance( vTZCMAUDO );
   }

   oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );

   if ( nRC_CheckInMeta >= 0 && nRC >= 0 )
   {
      MessageSend( vSubtask, "CM00242", "Configuration Management",
                   "Check In completed successfully.",
                   zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );
   }

   if ( GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      // Blank out the descriptions for the next window.
      SetAttributeFromString( vTZCMAUDO, "AuditTrail", "Desc", "" );
      SetAttributeFromString( vTZCMAUDO, "AuditTrail", "ShortDesc", "" );
   }

   return( 1 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckInAll( zVIEW vSubtask )
{
   zVIEW vTZCMLPLW;
   zVIEW vTZCMWIPO;

   if ( zwTZCMLPLD_CheckInReus( vSubtask ) > 0 )
   {
      if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) < 0 )
         return( -1 );

      //BL, 2000.01.20 set Option for BuildCheckedOutByUser = 8
      SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ComponentListType", 8 );
      zwTZCMLPLD_BuildSelectedCompList( vSubtask );

      if ( GetViewByName( &vTZCMLPLW, "TZCMLPLW", vSubtask, zLEVEL_TASK ) < 0 )
        return( -1 );

      if ( SetCursorFirstEntity( vTZCMLPLW, "W_MetaDef", "LPLR" ) >= zCURSOR_SET )
      {
         MessageSend( vSubtask, "CM00212", "Configuration Management",
                      "Note:\tYou Choose CheckIn ALL, but there are still components Checked out by you."
                       "\n\t--> see the Component List.",
                      zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );

         SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent | zWAB_ProcessImmediateAction, 0, 0 );
         return( -1 );
      }

   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckInMeta( zVIEW vSubtask )
{
   zVIEW    vTZCM_ChkInList;
   zVIEW    vTZCMAUDO;
   zVIEW    vTZCM_ChkInList2;
   zSHORT   nRC;
   zSHORT   DependentNeeded = 0;
   zLONG    lZKey;
   zCHAR    szERR_Msg[ zSHORT_MESSAGE_LTH + 1 ];

   GetViewByName( &vTZCM_ChkInList, "TZCM_ChkInList", vSubtask, zLEVEL_TASK );
   nRC = SetCursorFirstEntity( vTZCM_ChkInList, "W_MetaDef", "LPLR" );
   if ( nRC < 0 )
      return( -1 );

   nRC = SetCursorNextEntity( vTZCM_ChkInList, "W_MetaDef", "LPLR" );
   if ( nRC < 0 )
   {
      if ( zwTZCMLPLD_CheckInReus( vSubtask ) >= 0 )
         SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, "", "" );

      return( 0 );
   }
   else
   {
      if ( SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "LPLR" ) < zCURSOR_SET )
      {
         strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Please select at least one Component for Check In" );
         MessageSend( vSubtask, "CM00241", "Configuration Management",
                      szERR_Msg, zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
         return( 0 );
      }
   }

   if ( GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK ) > 0 &&
        CompareAttributeToString( vTZCMAUDO, "AuditTrail",  "ShortDesc", "" ) == 0 )
   {
      MessageSend( vSubtask, "CM00241", "Configuration Management",
                   "Please enter a short description for the Check In",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "ShortDescEdit" );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );

      return( -1 );
   }


   if ( GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK ) > 0 &&
        CompareAttributeToString( vTZCMAUDO, "AuditTrail",  "Desc", "" ) == 0 )
   {
      MessageSend( vSubtask, "CM00241", "Configuration Management",
                   "Please enter a description for the Check In",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetFocusToCtrl( vSubtask, "DescEdit" );
      return( 0 );
   }

   nRC =  zwfnTZCMLPLD_CheckInEdits( vSubtask );
   if ( nRC < 0 )
      return( 0 );

   GetViewByName( &vTZCM_ChkInList, "TZCM_ChkInList", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCM_ChkInList2, "TZCM_ChkInList2", vSubtask, zLEVEL_TASK );
   nRC = SetCursorFirstEntity( vTZCM_ChkInList2, "W_MetaDef", "LPLR" );
   while ( ( nRC >= zCURSOR_SET ) && ( !DependentNeeded ) )
   {
      GetIntegerFromAttribute( &lZKey, vTZCM_ChkInList2, "W_MetaDef", "CPLR_ZKey" );
      SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaDef", "CPLR_ZKey", lZKey, "LPLR" );
      if ( GetSelectStateOfEntityForSet( vTZCM_ChkInList, "W_MetaDef", 1 ) )
      {
         nRC = SetCursorNextEntity( vTZCM_ChkInList2, "W_MetaDef", "LPLR" );
      }
      else
      {
         DependentNeeded = 1;
      }
   }

   if ( DependentNeeded )
   {
      DropView( vTZCM_ChkInList2 );

      strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Meta type(s) subordinate to the selected\n" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "Metas are checked out and must be checked\n" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "in with this meta!" );
      MessageSend( vSubtask, "CM00242", "Configuration Management",
                   szERR_Msg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
   }
   else
   {
      SetViewFromView( vTZCM_ChkInList, vTZCM_ChkInList2 );
      DropView( vTZCM_ChkInList2 );
      nRC = zwTZCMLPLD_CheckInReus( vSubtask );
      zwTZCMLPLD_BuildCI_List( vSubtask );
      RefreshWindow( vSubtask );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_CopyMetaEntry( zVIEW  vTZCM_ChkInList,
                            zVIEW  vTZCM_ChkInList2,
                            zLONG  lType )
{
   zSHORT  nRC;

   // Copy the W_MetaDef entry from vTZCM_ChkInList to vTZCM_ChkInList2 and
   // also the W_MetaType entry if needed.
   nRC = SetCursorFirstEntityByInteger( vTZCM_ChkInList2, "W_MetaType", "Type", lType, 0 );
   if ( nRC < zCURSOR_SET )
   {
      CreateEntity( vTZCM_ChkInList2, "W_MetaType", zPOS_AFTER );
      SetAttributeFromInteger( vTZCM_ChkInList2, "W_MetaType", "Type", lType );
   }

   nRC = SetCursorFirstEntityByAttr( vTZCM_ChkInList2, "W_MetaDef", "CPLR_ZKey", vTZCM_ChkInList,  "W_MetaDef", "CPLR_ZKey", 0 );
   if ( nRC < zCURSOR_SET )
   {
      CreateEntity( vTZCM_ChkInList2, "W_MetaDef", zPOS_AFTER );
      SetMatchingAttributesByName( vTZCM_ChkInList2, "W_MetaDef", vTZCM_ChkInList,  "W_MetaDef", zSET_ALL );

      // Returning 0 indicates the entry DIDN'T already exist and WAS copied.
      return( 0 );
   }
   else
   {
      // Returning 1 indicates the entry DID already exist and WAS NOT copied.
      return( 1 );
   }
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_CheckDialogDeps( zVIEW  vSubtask,
                              zVIEW  vTZCM_ChkInList,
                              zVIEW  vTZCM_ChkInList2,
                              zLONG  lType )
{
   zVIEW   vDialog;
   zVIEW   vListDialog;
   zVIEW   vListVOR;
   zVIEW   vListLOD;
   zSHORT  nRC;
   zCHAR   szMsg[ zSHORT_MESSAGE_LTH + 1 ];
   zCHAR   szDialogName[ 33 ];

   // The purpose of this routine is to make sure that any LODs or VORs used
   // by a Dialog that is being checked in are also being checked in, if they
   // are checked out by this user and they have been modified.  We will do
   // this by activating each Dialog being checked in and then for each LOD
   // and VOR referenced in that Dialog we will:
   // 1. See if that LOD or VOR is in check out list (vTZCM_ChkInList) but is
   //    not selected for Check In.  If so, we will give an error message.
   // 2. We will move any of those "dependent" LOD or VOR entries to the new
   //    Check In list (vTZCM_ChkInList2).  This is necessary to trigger the
   //    dependency error message issued by the calling routine.

   // Get position on any VORs or LODs in Check In list.
   CreateViewFromViewForTask( &vListLOD, vTZCM_ChkInList, 0 );
   if ( SetCursorFirstEntityByInteger( vListLOD, "W_MetaType", "Type", zSOURCE_LOD_META, 0 ) < zCURSOR_SET )
   {
      vListLOD = 0;
   }

   CreateViewFromViewForTask( &vListVOR, vTZCM_ChkInList, 0 );
   if ( SetCursorFirstEntityByInteger( vListVOR, "W_MetaType", "Type", zSOURCE_VOR_META, 0 ) < zCURSOR_SET )
   {
      vListVOR = 0;
   }

   CreateViewFromViewForTask( &vListDialog, vTZCM_ChkInList, 0 );
   for ( nRC = SetCursorFirstSelectedEntity( vListDialog, "W_MetaDef", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextSelectedEntity( vListDialog, "W_MetaDef", 0 ) )
   {
      // Process a selected Dialog

      if ( ActivateMetaOI( vSubtask, &vDialog, vListDialog, (zSHORT) lType, zLEVEL_TASK ) < 1 )
      {
         // Error - Dialog could not be activated.
      }
      else
      {
         // Process all VORs and LODs in the Dialog.
         for ( nRC = SetCursorFirstEntity( vDialog, "ViewObjRef", 0 );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntity( vDialog, "ViewObjRef", 0 ) )
         {
            if ( vListVOR > 0 )
            {
               nRC = SetCursorFirstEntityByAttr( vListVOR, "W_MetaDef",  "CPLR_ZKey", vDialog,  "ViewObjRef", "ZKey", 0 );
               if ( nRC >= zCURSOR_SET )
               {
                  // First copy over the entry from List to List2.
                  zwfnTZCMLPLD_CopyMetaEntry( vListVOR, vTZCM_ChkInList2, zSOURCE_VOR_META );

                  // Then give an error message if that entry is not selected.
                  if ( GetSelectStateOfEntityForSet( vListVOR, "W_MetaDef", 1 ) == 0 )
                  {
                     // The entry wasn't selected.
                     GetStringFromAttribute( szMsg, zsizeof( szMsg ), vListVOR, "W_MetaDef", "Name" );
                     strcat_s( szMsg, zsizeof( szMsg ), " is a dependent Named View for Dialog, " );
                     GetStringFromAttribute( szDialogName, zsizeof( szDialogName ), vDialog, "Dialog", "Tag" );
                     strcat_s( szMsg, zsizeof( szMsg ), szDialogName );
                     strcat_s( szMsg, zsizeof( szMsg ), ", and must be checked in with that Dialog." );

                     MessageSend( vSubtask, "CM00706", "Configuration Management",
                                  szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
                  }
               }
            }

            if ( vListLOD > 0 )
            {
               nRC = SetCursorFirstEntityByAttr( vListLOD, "W_MetaDef", "CPLR_ZKey", vDialog,  "LOD", "ZKey", 0 );
               if ( nRC >= zCURSOR_SET )
               {
                  // First copy over the entry from List to List2.
                  nRC = zwfnTZCMLPLD_CopyMetaEntry( vListLOD, vTZCM_ChkInList2, zSOURCE_LOD_META );

                  // Then give an error message if that entry did not already exist (it had not yet been processed) and it is not selected.
                  if ( nRC == 0 && GetSelectStateOfEntityForSet( vListLOD, "W_MetaDef", 1 ) == 0 )
                  {
                     // The entry wasn't selected.
                     GetStringFromAttribute( szMsg, zsizeof( szMsg ), vListLOD, "W_MetaDef", "Name" );
                     strcat_s( szMsg, zsizeof( szMsg ), " is a dependent LOD for Dialog, " );
                     GetStringFromAttribute( szDialogName, zsizeof( szDialogName ), vDialog, "Dialog", "Tag" );
                     strcat_s( szMsg, zsizeof( szMsg ), szDialogName );
                     strcat_s( szMsg, zsizeof( szMsg ), ", and must be checked in with that Dialog." );

                     MessageSend( vSubtask, "CM00707", "Configuration Management",
                                  szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
                  }
               }
            }
         }

         DropView( vDialog );
      }
   }

   if ( vListVOR != 0 )
      DropView( vListVOR );

   if ( vListLOD != 0 )
      DropView( vListLOD );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_CheckInEdits( zVIEW vSubtask )
{
   zVIEW    vTZCM_ChkInList;
   zVIEW    vTZCM_ChkInList2;
   zSHORT   DomainsCopied = 0;
   zSHORT   DomainSelected = 0;
   zSHORT   GO_Selected = 0;
   zSHORT   ER_Copied = 0;
   zSHORT   SRC_Copied = 0;
   zSHORT   TEsCopied = 0;
   zSHORT   SAsCopied = 0;
   zSHORT   LODsCopied = 0;
   zSHORT   VORsCopied = 0;
   zSHORT   PEsCopied = 0;
   zSHORT   UISsCopied = 0;
   zSHORT   HDRsCopied = 0;
   zSHORT   nRC;

   if ( GetViewByName( &vTZCM_ChkInList, "TZCM_ChkInList", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );
   if ( ActivateEmptyObjectInstance( &vTZCM_ChkInList2, "TZCMLPLO", vSubtask, zSINGLE ) >= 0 )
   {
      CreateEntity( vTZCM_ChkInList2, "LPLR", zPOS_AFTER );
      SetMatchingAttributesByName( vTZCM_ChkInList2, "LPLR", vTZCM_ChkInList, "LPLR", zSET_ALL );
      SetNameForView( vTZCM_ChkInList2, "TZCM_ChkInList2", vSubtask, zLEVEL_TASK );
   }

   /* Headers */
   /* Copy all Active Headers */
   zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_HDR_META );

   /* Global Operation Groups */
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", zSOURCE_GOPGRP_META, "" ) == zCURSOR_SET )
   {
      if ( SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" ) == zCURSOR_SET )
      {
         GO_Selected = 1;

         /* Copy all Active Headers */
         if ( HDRsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_HDR_META );
            HDRsCopied = 1;
         }
      }
   }
   zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_GOPGRP_META );

   /* Domain Groups */
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", zSOURCE_DOMAINGRP_META, "" ) == zCURSOR_SET )
   {
      nRC = SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
      if ( nRC == zCURSOR_SET )
      {
         zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_HDR_META );
         HDRsCopied = 1;
         zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_DOMAINGRP_META );
         DomainSelected = 1;
      }
   }

   /* ERD */
   if ( ((SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type",(zLONG) zSOURCE_ERD_META, "" ) == zCURSOR_SET) &&
         (SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" ) == zCURSOR_SET)) ||
        ((SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type",(zLONG) zSOURCE_SA_META, "" ) == zCURSOR_SET) &&
         (SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" ) == zCURSOR_SET)) ||
        ((SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type",(zLONG) zSOURCE_DTE_META, "" ) == zCURSOR_SET) &&
         (SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" ) == zCURSOR_SET )) )
   {
      nRC = SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type",(zLONG) zSOURCE_ERD_META, "" );
      if ( CheckExistenceOfEntity( vTZCM_ChkInList, "W_MetaDef" ) >= zCURSOR_SET )
      {
         /* Copy all Active Domains */
         zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_DOMAINGRP_META );
         DomainsCopied = 1;
         nRC = SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", zSOURCE_ERD_META, "" );
         CreateEntity( vTZCM_ChkInList2, "W_MetaType", zPOS_AFTER );
         SetAttributeFromInteger( vTZCM_ChkInList2, "W_MetaType", "Type",(zLONG) zSOURCE_ERD_META );
         nRC = SetCursorFirstEntity( vTZCM_ChkInList, "W_MetaDef", "" );
         CreateEntity( vTZCM_ChkInList2, "W_MetaDef", zPOS_AFTER );
         SetMatchingAttributesByName( vTZCM_ChkInList2, "W_MetaDef", vTZCM_ChkInList, "W_MetaDef", zSET_ALL );
         ER_Copied = 1;
         /* Copy all Active SAs */
         zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_SA_META );
         SAsCopied = 1;
      }
      nRC = SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type",(zLONG) zSOURCE_DTE_META, "" );
      if ( CheckExistenceOfEntity( vTZCM_ChkInList, "W_MetaDef" ) >= zCURSOR_SET )
      {
         /* Copy all Active TEs */
         zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_DTE_META );
         TEsCopied = 1;
      }
   }

   /* LODS */
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", (zLONG) zSOURCE_LOD_META, "" ) == zCURSOR_SET )
   {
      nRC = SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
      if ( nRC == zCURSOR_SET )
      {
         /* Copy all Active Headers */
         if ( HDRsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_HDR_META );
            HDRsCopied = 1;
         }

         /* Copy all Active Domains */
         if ( DomainsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_DOMAINGRP_META );
            DomainsCopied = 1;
         }

         if ( ER_Copied == 0 )
         {
            zVIEW vTemp;

            nRC = CreateViewFromViewForTask(&vTemp, vTZCM_ChkInList, 0 );
            nRC = SetCursorFirstEntityByInteger( vTemp, "W_MetaType", "Type", (zLONG) zSOURCE_ERD_META, "" );
            if ( CheckExistenceOfEntity( vTemp, "W_MetaDef" ) >= zCURSOR_SET )
            {
               zwfnTZCMLPLD_BuildER_List( vTemp, vTZCM_ChkInList2 );
               ER_Copied = 1;
            }

            DropView( vTemp );
         }

         zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_LOD_META );
      }
   }

   /* VOR */
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", (zLONG) zSOURCE_VOR_META, "" ) == zCURSOR_SET )
   {
      if ( SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" ) == zCURSOR_SET )
      {
         /* Copy all Active LODs */
         if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type",(zLONG) zSOURCE_LOD_META, "" ) == zCURSOR_SET )
         {
            if ( SetCursorFirstEntity( vTZCM_ChkInList, "W_MetaDef", "" ) == zCURSOR_SET )
            {
               if ( DomainsCopied == 0 )
               {
                  zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_DOMAINGRP_META );
                  DomainsCopied = 1;
               }
               if ( ER_Copied == 0 )
               {
                  zwfnTZCMLPLD_BuildER_List( vTZCM_ChkInList, vTZCM_ChkInList2 );
                  ER_Copied = 1;
               }
               zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_LOD_META );
               LODsCopied = 1;
            }
         }
         zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_VOR_META );
      }
   }

   /* PENVs */
   zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_PENV_META );

   /* DIALOGS */
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", (zLONG) zSOURCE_DIALOG_META, "" ) == zCURSOR_SET )
   {
      nRC = SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
      if ( nRC == zCURSOR_SET )
      {
         /* Copy all Active Headers */
         if ( HDRsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_HDR_META );
            HDRsCopied = 1;
         }
         if ( DomainsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_DOMAINGRP_META );
            DomainsCopied = 1;
         }
         if ( ER_Copied == 0 )
         {
            zwfnTZCMLPLD_BuildER_List( vTZCM_ChkInList, vTZCM_ChkInList2 );
            ER_Copied = 1;
         }

         // We used to handle LODs and VORs like the other metas above, but
         // in Dec 1997 we switched so that the only dependent LODs and VORs
         // that would be needed would be those referenced by the Dialogs to
         // be checked in.  This means we must loop through all Dialogs to be
         // checked in and Activate them and then see if any LODs or VORs in
         // the Dialog are in ChkInList but NOT selected.  If so, give an
         // error message.  In any event, if they are in ChkInList (with or
         // without selection), copy them to ChkInList2.
         SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", zSOURCE_DIALOG_META, 0 );
         zwfnTZCMLPLD_CheckDialogDeps( vSubtask, vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_DIALOG_META );


         /* Copy all Active PEs */
         if ( PEsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_PENV_META );
            PEsCopied = 1;
         }

         zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_DIALOG_META );
      }
   }

   /* REPORTS */
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", (zLONG) zSOURCE_REPORT_META, "" ) == zCURSOR_SET )
   {
      nRC = SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
      if ( nRC == zCURSOR_SET )
      {
         /* Copy all Active Headers */
         if ( HDRsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_HDR_META );
            HDRsCopied = 1;
         }
         if ( DomainsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_DOMAINGRP_META );
            DomainsCopied = 1;
         }
         if ( ER_Copied == 0 )
         {
            zwfnTZCMLPLD_BuildER_List( vTZCM_ChkInList, vTZCM_ChkInList2 );
            ER_Copied = 1;
         }

         // The following uses the same logic as for DIALOGS above to check
         // that any dependent LODs are also being checked in.
         SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", zSOURCE_REPORT_META, 0 );
         zwfnTZCMLPLD_CheckDialogDeps( vSubtask, vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_REPORT_META );


         /* Copy all Active PEs */
         if ( PEsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_PENV_META );
            PEsCopied = 1;
         }

         zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_REPORT_META );
      }
   }

   /* XSLT */
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", (zLONG) zSOURCE_XSLT_META, "" ) == zCURSOR_SET )
   {
      nRC = SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
      if ( nRC == zCURSOR_SET )
      {
         /* Copy all Active Headers */
         if ( HDRsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_HDR_META );
            HDRsCopied = 1;
         }
         if ( DomainsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_DOMAINGRP_META );
            DomainsCopied = 1;
         }
         if ( ER_Copied == 0 )
         {
            zwfnTZCMLPLD_BuildER_List( vTZCM_ChkInList, vTZCM_ChkInList2 );
            ER_Copied = 1;
         }

         // The following uses the same logic as for DIALOGS above to check that any dependent LODs are also being checked in.
         SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", zSOURCE_XSLT_META, 0 );
         zwfnTZCMLPLD_CheckDialogDeps( vSubtask, vTZCM_ChkInList, vTZCM_ChkInList2, zSOURCE_XSLT_META );


         /* Copy all Active PEs */
         if ( PEsCopied == 0 )
         {
            zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_PENV_META );
            PEsCopied = 1;
         }

         zwfnTZCMLPLD_GetSelectedMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_XSLT_META );
      }
   }

   return( 0 );
}

void
zwfnTZCMLPLD_GetSelectedMetas( zVIEW vTZCM_ChkInList, zVIEW vTZCM_ChkInList2, zLONG Type )
{
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", Type, "" ) == zCURSOR_SET )
   {
      zSHORT nRC;

      nRC = SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
      if ( nRC == zCURSOR_SET )
      {
         CreateEntity( vTZCM_ChkInList2, "W_MetaType", zPOS_AFTER );
         SetAttributeFromInteger( vTZCM_ChkInList2, "W_MetaType", "Type", Type );
         while ( nRC == zCURSOR_SET )
         {
            CreateEntity( vTZCM_ChkInList2, "W_MetaDef", zPOS_AFTER );
            SetMatchingAttributesByName( vTZCM_ChkInList2, "W_MetaDef", vTZCM_ChkInList, "W_MetaDef", zSET_ALL );
            nRC = SetCursorNextSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
         }
      }
   }
}

// DGC - DOMGRP
// SRC metas no longer valid
#if 0
zSHORT
zwfnTZCMLPLD_Chk4SRC_DependCs( zVIEW vChkInListCmp, zVIEW vTZCM_ChkInList,
                               zVIEW vTZCM_ChkInList2, zLONG lType )
{
   zVIEW    vMeta;
   zVIEW    vMetaCmp;
   zVIEW    vMetaList;
   zVIEW    vTZCMLPLO2;
   zULONG   ulZKey;
   zSHORT   nRC;

   GetViewByName( &vMetaList, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   CreateViewFromViewForTask( &vTZCMLPLO2, vMetaList, 0 );
   SetCursorFirstEntityByInteger( vTZCMLPLO2, "W_MetaType", "Type", zSOURCE_SRC_META, "" );
   SetViewFromView( vChkInListCmp, vTZCM_ChkInList );
   RetrieveViewForMetaList( vSubtask, &vMetaList, (zSHORT) lType );
   SetCursorFirstEntityByInteger( vChkInListCmp, "W_MetaType", "Type", lType, "" );
   nRC = SetCursorFirstSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
   while ( nRC == zCURSOR_SET )
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCM_ChkInList, "W_MetaDef", "CPLR_ZKey" );
      SetCursorFirstEntityByInteger( vMetaList, "W_MetaDef", "CPLR_ZKey", ulZKey, "" );
      if ( ActivateMetaOI( vSubtask, &vMeta, vMetaList, (zSHORT) lType, zLEVEL_TASK ) < 1 )
      {
//PETTIT add error code here later

         break;
      }

      if ( SetCursorFirstEntity( vMeta, "SourceFile", SRC_CMOD[ Type ].szOD_ROOT ) == zCURSOR_SET )
      {
         GetIntegerFromAttribute( (zPLONG) &ulZKey, vMeta, "SourceFile", "ZKey" );
         SetCursorFirstEntityByInteger( vTZCMLPLO2, "W_MetaDef", "CPLR_ZKey", ulZKey, "" );
         SetAttributeFromInteger( vTZCMLPLO2, "W_MetaDef", "UpdateInd", 2 );
         nRC = SetCursorFirstEntity( vChkInListCmp, "W_MetaDef", "" );
         while ( nRC == zCURSOR_SET )
         {
            if ( GetSelectStateOfEntityForSet( vChkInListCmp, "W_MetaDef", 1 ) == 0 )
            {  // Not Selected
               GetIntegerFromAttribute( (zPLONG) &ulZKey, vChkInListCmp, "W_MetaDef", "CPLR_ZKey" );
               SetCursorFirstEntityByInteger( vMetaList, "W_MetaDef", "CPLR_ZKey", ulZKey, "" );
               if ( ActivateMetaOI( vSubtask, &vMetaCmp, vMetaList, (zSHORT) Type, zLEVEL_TASK ) < 1 )
               {
   //PETTIT add error code here later
                  break;
               }
               if ( SetCursorFirstEntity( vMetaCmp, "SourceFile", SRC_CMOD[ Type ].szOD_ROOT ) == zCURSOR_SET )
               {
                  if ( CompareAttributeToAttribute( vMeta, "SourceFile", "ZKey", vMetaCmp, "SourceFile", "ZKey" ) == 0 )
                  {  // Mark it in ChkInList2
                     if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList2, "W_MetaType", "Type", Type, "" ) != zCURSOR_SET )
                     {
                        CreateEntity( vTZCM_ChkInList2, "W_MetaType", zPOS_AFTER );
                        SetAttributeFromInteger( vTZCM_ChkInList2, "W_MetaType", "Type", Type );
                     }
                     CreateEntity( vTZCM_ChkInList2, "W_MetaDef", zPOS_AFTER );
                     SetMatchingAttributesByName( vTZCM_ChkInList2, "W_MetaDef", vChkInListCmp, "W_MetaDef", zSET_ALL );
                  }
               }

               DropMetaOI( vSubtask, vMetaCmp );
            }

            nRC = SetCursorNextEntity( vChkInListCmp, "W_MetaDef", "" );
         }
      }

      DropMetaOI( vSubtask, vMeta );
      nRC = SetCursorNextSelectedEntity( vTZCM_ChkInList, "W_MetaDef", "" );
   }

   DropMetaOI( vSubtask, vMetaList );
   return( 0 );
}
#endif

void
zwfnTZCMLPLD_BuildER_List( zVIEW vTZCM_ChkInList, zVIEW vTZCM_ChkInList2 )
{
   /* Copy Active ER */
   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", (zLONG) zSOURCE_ERD_META, "" ) == zCURSOR_SET )
   {
      if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList2, "W_MetaType", "Type",(zLONG) zSOURCE_ERD_META, "" ) != zCURSOR_SET )
      {
         CreateEntity( vTZCM_ChkInList2, "W_MetaType", zPOS_AFTER );
         SetAttributeFromInteger( vTZCM_ChkInList2, "W_MetaType", "Type", (zLONG) zSOURCE_ERD_META );
         CreateEntity( vTZCM_ChkInList2, "W_MetaDef", zPOS_AFTER );
         SetMatchingAttributesByName( vTZCM_ChkInList2, "W_MetaDef", vTZCM_ChkInList, "W_MetaDef", zSET_ALL );
         /* Copy all Active SAs */
         zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_SA_META );
         /* Copy all Active TEs */
         zwfnTZCMLPLD_GetAllActiveMetas( vTZCM_ChkInList, vTZCM_ChkInList2, (zLONG) zSOURCE_DTE_META );
      }
   }
}

void
zwfnTZCMLPLD_GetAllActiveMetas( zVIEW vTZCM_ChkInList,
                                zVIEW vTZCM_ChkInList2,
                                zLONG Type )
{
   zSHORT nRC;

   if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList, "W_MetaType", "Type", Type, "" ) == zCURSOR_SET )
   {
      if ( SetCursorFirstEntityByInteger( vTZCM_ChkInList2, "W_MetaType", "Type", Type, "" ) != zCURSOR_SET )
      {
         CreateEntity( vTZCM_ChkInList2, "W_MetaType", zPOS_AFTER );
         SetAttributeFromInteger( vTZCM_ChkInList2, "W_MetaType", "Type", Type );
      }
      else
      {
         nRC = SetCursorFirstEntity( vTZCM_ChkInList2, "W_MetaDef", "" );
         while ( nRC == zCURSOR_SET )
         {
            nRC = DeleteEntity( vTZCM_ChkInList2, "W_MetaDef", zREPOS_NEXT );
         }
      }

      nRC = SetCursorFirstEntity( vTZCM_ChkInList, "W_MetaDef", "" );
      while ( nRC == zCURSOR_SET )
      {
         CreateEntity( vTZCM_ChkInList2, "W_MetaDef", zPOS_AFTER );
         SetMatchingAttributesByName( vTZCM_ChkInList2, "W_MetaDef", vTZCM_ChkInList, "W_MetaDef", zSET_ALL );
         nRC = SetCursorNextEntity( vTZCM_ChkInList, "W_MetaDef", "" );
      }
   }
}

static zSHORT
zwfnTZCMLPLD_LoadRepo_CPRO( zVIEW vSubtask, zPVIEW vTZCMREPO,
                            zPVIEW vTZCMCPRO, zVIEW vTZCMCOML )
{
   zCHAR   szERR_Msg[ zMAX_MESSAGE_LTH + 1 ];
   zCHAR   szName[ 33 ];
   zULONG  ulZKey;

   if ( vTZCMCOML == 0 )
      return( -1 );

   if ( GetViewByName( vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( *vTZCMREPO );

   MB_SetMessage( vSubtask, 1, "Activating Repository" );

   if ( oTZCMREPO_ActivateRepository( vTZCMREPO, vSubtask ) < 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, 0, 0 );
      return( -1 );
   }

   SetNameForView( *vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );


   if ( GetViewByName( vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( *vTZCMCPRO );

   MB_SetMessage( vSubtask, 1, "Activating CPLR" );

   GetStringFromAttribute( szName, zsizeof( szName ), vTZCMCOML, "CPLR", "Name" );
   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMCOML, "CPLR", "ZKey" );

   if ( oTZCMCPRO_ActivateCPLR( vTZCMCPRO, (zLONG) ulZKey, vSubtask ) < 0 )
   {
      strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "CPLR '" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szName );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "' not found on Installation!" );
      MessageSend( vSubtask, "CM00245", "Configuration Management",
                   szERR_Msg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, 0, 0 );
      return( -1 );
   }

   SetNameForView( *vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK );

   if ( oTZCMCPRO_CPLR_Enqueue( *vTZCMCPRO, vSubtask, zCPLR_ENQUEUE_FOR_CHECK_OUT ) < 0 )
   {
      return( -1 );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_SetTabSize
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_SetTabSize( zVIEW vSubtask )
{
   zLONG  lWindowSize_X;
   zLONG  lCtrlSize_X;
   zLONG  lCtrlSize_Y;
   zLONG  lCtrlPos_X;
   zLONG  lTabCtrlSize_X;
   zLONG  lTemp;
   zCHAR  szControl[ 33 ];

   // Set new size for Tab Control
   GetCtrlSize( vSubtask, 0, &lWindowSize_X, &lTemp, TRUE );
   GetCtrlSize( vSubtask, "Tab", &lCtrlSize_X, &lCtrlSize_Y, TRUE );
   GetCtrlPosition( vSubtask, "Tab", &lCtrlPos_X, &lTemp, TRUE );

   lTabCtrlSize_X = lWindowSize_X - lCtrlPos_X - 70;
   if ( lTabCtrlSize_X < 247 )
      lTabCtrlSize_X = 247;

   SetCtrlSize( vSubtask, "Tab", lTabCtrlSize_X, lCtrlSize_Y, TRUE );

   // Set new size for Tab SubControl
   GetCtrlSize( vSubtask, "tcComponent", &lTemp, &lCtrlSize_Y, TRUE );
   lTabCtrlSize_X = lTabCtrlSize_X - 5;
   SetCtrlSize( vSubtask, "tcComponent", lTabCtrlSize_X, lCtrlSize_Y, TRUE );

   GetCtrlSize( vSubtask, "tcComments", &lTemp, &lCtrlSize_Y, TRUE );
   SetCtrlSize( vSubtask, "tcComments", lTabCtrlSize_X, lCtrlSize_Y, TRUE );

   // Save current Control with Focus
   GetCtrlWithFocus( vSubtask, szControl );

   // if 2. Tab active, set new size for Controls from 2. Tab SubContol
   if ( SetFocusToCtrl( vSubtask, "edComments" ) >= 0 )
   {
      GetCtrlSize( vSubtask, "edComments", &lCtrlSize_X, &lCtrlSize_Y, TRUE );
      lCtrlSize_X = lTabCtrlSize_X - lCtrlPos_X - 5;
      SetCtrlSize( vSubtask, "edComments", lCtrlSize_X, 72, TRUE );
   }

   // Set new position for Buttons
   GetCtrlSize( vSubtask, "Tab", &lCtrlSize_X, &lTemp, TRUE );
   lCtrlPos_X = lCtrlSize_X + 10;

   SetCtrlPosition( vSubtask, "Close", lCtrlPos_X, 18, TRUE );
   SetCtrlPosition( vSubtask, "CheckOutSource", lCtrlPos_X, 41, TRUE );
   SetCtrlPosition( vSubtask, "Details", lCtrlPos_X, 63, TRUE );
   SetCtrlPosition( vSubtask, "AuditTrail", lCtrlPos_X, 78, TRUE );

   SetFocusToCtrl( vSubtask, szControl );

   return( 0 );
} // zwTZCMLPLD_SetTabSize

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_BuildCO_List( zVIEW vSubtask )
{
   zVIEW    vTZCMCOML;
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMWIPO;

   MB_SetMessage( vSubtask, 1, "" );

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   // Activate a little CPRO Object
   if ( zwfnTZCMLPLD_ActivateCOMPL( vSubtask, &vTZCMCOML, vTZCMLPLO ) < 0 )
      return( -1 );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListDomain", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_DOMAINGRP_META );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListLOD", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_LOD_META );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListERD", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_ERD_META );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListDialogs", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_DIALOG_META );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListGlobalOper", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_GOPGRP_META );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListUIS", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_UIS_META );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListReports", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_REPORT_META );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListXSLT", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_XSLT_META );

   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ListPE", 1 ) != 0 )
      zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_PENV_META );

   // Delete Subject Areas, TE and registered Views from List
   zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_SA_META );
   zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_DTE_META );
   zwfnTZCMLPLD_DeleteChkOutType( vSubtask, vTZCMCOML, (zLONG) zSOURCE_VOR_META );

   ResetView( vTZCMCOML );

   if ( CheckExistenceOfEntity( vTZCMCOML, "Z_MetaDef" ) < zCURSOR_SET )
      MB_SetMessage( vSubtask, 1, "Requested Check Out List is Empty." );
   else
   {
      OrderEntitiesByDefaultAttribs( vTZCMCOML, "Z_MetaDef" );
      TAB_SetActiveTab( vSubtask, "Tab", 2 );
      zwTZCMLPLD_SetTabSize( vSubtask );
      SetFocusToCtrl( vSubtask, "edComments" );
   }

   return( 0 );
}

zSHORT
zwfnTZCMLPLD_DeleteChkOutType( zVIEW vSubtask, zVIEW vTZCMCOML, zLONG Type )
{
   zSHORT nRC;

   nRC = SetCursorFirstEntityByInteger( vTZCMCOML, "Z_MetaDef", "Type", Type, "" );
   if ( nRC != zCURSOR_SET )
      return( -1 );

   while ( nRC == zCURSOR_SET )
   {
      DeleteEntity( vTZCMCOML, "Z_MetaDef", zREPOS_NONE );

      nRC = SetCursorNextEntityByInteger( vTZCMCOML, "Z_MetaDef", "Type", Type, "" );
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_InitCheckOutAbort( zVIEW vSubtask, zVIEW vTZCMCOML, zPCHAR szUserEntity )
{
   zCHAR  szMsg[ zSHORT_MESSAGE_LTH + 1 ];

   if ( CheckExistenceOfEntity( vTZCMCOML, szUserEntity ) < zCURSOR_SET )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Project component '" );
      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMCOML, "Z_MetaDef", "Name" );
      strcat_s( szMsg, zsizeof( szMsg ), "' is currently being checked out.\nAborting Check Out." );
      MessageSend( vSubtask, "CM00249", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }
   else
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Project component '" );
      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMCOML, "Z_MetaDef", "Name" );
      strcat_s( szMsg, zsizeof( szMsg ), "' is checked out by '" );
      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMCOML, "User_1", "Name" );
      strcat_s( szMsg, zsizeof( szMsg ), "'. \nAborting Check Out!" );
      MessageSend( vSubtask, "CM00250", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_InitCheckOut( zVIEW vSubtask )
{
   zVIEW    vTZCMCOML;
   zSHORT   nRC;

   if ( GetViewByName( &vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   // Loop through each selected entity, checking out each member selected.
   nRC = SetCursorFirstSelectedEntity( vTZCMCOML, "Z_MetaDef", "" );
   while ( nRC >= zCURSOR_SET )
   {
      if ( CheckExistenceOfEntity( vTZCMCOML, "UserMetaStatus" ) >= zCURSOR_SET )
      {
         zwfnTZCMLPLD_InitCheckOutAbort( vSubtask, vTZCMCOML, "User" );
         return( -1 );
      }

      nRC = SetCursorNextSelectedEntity( vTZCMCOML, "Z_MetaDef", "" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckOutSnglClk( zVIEW vSubtask )
{
   zVIEW    vTZCMCOML;
   zVIEW    vTZCMCOML_Copy;
   zSHORT   nRC;
   zLONG    lEnableCheckOut;

   if ( GetViewByName( &vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK ) < 0 )
   {
      SetCtrlState( vSubtask, "Details", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "CheckOutSource", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "AuditTrail", zCONTROL_STATUS_ENABLED, FALSE );
      return( -1 );
   }

   if ( SetCursorFirstSelectedEntity( vTZCMCOML, "Z_MetaDef", "" )
                                      != zCURSOR_SET )
   {
      SetCtrlState( vSubtask, "Details", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "CheckOutSource", zCONTROL_STATUS_ENABLED, FALSE );
      SetCtrlState( vSubtask, "AuditTrail", zCONTROL_STATUS_ENABLED, FALSE );
      return( 0 );
   }

   lEnableCheckOut = 1;
   CreateViewFromViewForTask( &vTZCMCOML_Copy, vTZCMCOML, 0 );

   for ( nRC = SetCursorFirstSelectedEntity( vTZCMCOML_Copy, "Z_MetaDef", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextSelectedEntity( vTZCMCOML_Copy, "Z_MetaDef", "" ) )
   {
      if ( CheckExistenceOfEntity( vTZCMCOML_Copy, "UserMetaStatus" ) >= zCURSOR_SET )
      {
         lEnableCheckOut = 0;
         break;
      }
   } // endfor

   DropView( vTZCMCOML_Copy );

   SetCtrlState( vSubtask, "Details", zCONTROL_STATUS_ENABLED, TRUE );
   SetCtrlState( vSubtask, "CheckOutSource", zCONTROL_STATUS_ENABLED, lEnableCheckOut );
   SetCtrlState( vSubtask, "AuditTrail", zCONTROL_STATUS_ENABLED, TRUE );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_DropTZCMCPRL( zVIEW vSubtask )
{
   zVIEW  vTZCMCOML;

   if ( GetViewByName( &vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vTZCMCOML );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_fnCheckOutSourceAbort( zVIEW vSubtask, zVIEW vTZCMCOML, zVIEW vTZCMCPRO )
{
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ];

   if ( CommitObjectInstance( vTZCMCPRO ) < 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Commit of CPLR, " );
      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMCPRO, "CPLR", "Name" );
      strcat_s( szMsg, zsizeof( szMsg ), " failed! " );
      MessageSend( vSubtask, "CM00256", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( 0 );
   }

   SetCtrlState( vSubtask, "Details", zCONTROL_STATUS_ENABLED, FALSE );
   SetCtrlState( vSubtask, "CheckOutSource", zCONTROL_STATUS_ENABLED, FALSE );
   SetCtrlState( vSubtask, "AuditTrail", zCONTROL_STATUS_ENABLED, FALSE );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CheckOutRefresh( zVIEW vSubtask, zVIEW vTZCMLPLO )
{
   zVIEW   vTZCMRPTO;
   zVIEW   vTZCMREFO;
   zSHORT  nRC;
   zCHAR   szName[ 33 ];
   zCHAR   szMsg[ zMAX_MESSAGE_LTH + 1 ];

   if ( zwfnTZCMLPLD_ActivateREFO( vSubtask, vTZCMLPLO, &vTZCMREFO, szName, zRefreshLPLR ) < 0 )
   {
      return( -1 );
   }

   // Test whether the CPLR ist not enqueued and enqueue it.
   if ( oTZCMCPRO_CPLR_Enqueue( vTZCMREFO, vSubtask,
                                zCPLR_ENQUEUE_FOR_REFRESH ) < 0 )
   {
      return( -1 );
   }

   if ( oTZCMLPLO_RefreshLPLR( vSubtask, vTZCMLPLO, vTZCMREFO ) < 0 )
   {
      if ( GetViewByName( &vTZCMRPTO, "TZCMRPTO", vSubtask, zLEVEL_TASK ) > 0 )
         DropObjectInstance( vTZCMRPTO );

      oTZCMCPRO_CPLR_Enqueue( vTZCMREFO, vSubtask, zCPLR_DEQUEUE );
      DropObjectInstance( vTZCMREFO );
      return( -1 );
   }

   oTZCMCPRO_CPLR_Enqueue( vTZCMREFO, vSubtask, zCPLR_DEQUEUE );

   GetViewByName( &vTZCMRPTO, "TZCMRPTO", vSubtask, zLEVEL_TASK );
   nRC = SetEntityCursor( vTZCMRPTO, "Z_MetaDef", 0, zQUAL_SCOPE_OI | zPOS_FIRST, 0, 0, 0, 0, 0, 0 );

   if ( nRC >= zCURSOR_SET )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Metas have been refreshed. You may now choose" );
      strcat_s( szMsg, zsizeof( szMsg ), "\nto continue the Check Out process( OK ), or " );
      strcat_s( szMsg, zsizeof( szMsg ), "\nto Cancel the Check Out process( Cancel ) and" );
      strcat_s( szMsg, zsizeof( szMsg ), "\nreview the Refresh Report." );
      strcat_s( szMsg, zsizeof( szMsg ), "\n\n Continue check out?" );

      nRC = MessagePrompt( vSubtask, "CM00237", "Configuration Management",
                           szMsg, zBEEP, zBUTTONS_OKCANCEL, zRESPONSE_OK, 0 );
      if ( nRC == zRESPONSE_CANCEL )
      {
         DropObjectInstance( vTZCMREFO );
         SetWindowActionBehavior( vSubtask, zWAB_StartModalWindow | zWAB_ProcessImmediateAction, "TZCMRPTD", "RefreshList" );
         return( -1 );
      }
   }

   DropObjectInstance( vTZCMRPTO );
   DropObjectInstance( vTZCMREFO );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CheckOutAskForERD( zVIEW vSubtask, zVIEW vTZCMCOML,
                                zVIEW vTZCMCPRO, zLONG Type )
{
   zCHAR  szMsg[ zMAX_MESSAGE_LTH + 1 ];

   if ( Type == (zLONG) zSOURCE_ERD_META )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Checking Out the Data Model will Check Out all\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Subject Areas and TE with it!" );
   }

   if ( Type == (zLONG) zSOURCE_SA_META )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Checking Out a Subject Area will force\na Check Out of " );
      strcat_s( szMsg, zsizeof( szMsg ), "the ER Model and all Subject Areas\nand TE with it!" );
   }

   if ( Type == (zLONG) zSOURCE_DTE_META )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Checking Out the TE will Check Out all\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Subject Area and Data Model with it!" );
   }

   strcat_s( szMsg, zsizeof( szMsg ), "\n\nContinue with Check Out?" );

   if ( MessagePrompt( vSubtask, "CM00253", "Configuration Management",
                       szMsg, zBEEP, zBUTTONS_YESNO,
                       zRESPONSE_YES, 0 ) == zRESPONSE_NO )
   {
      oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );
      zwTZCMLPLD_fnCheckOutSourceAbort( vSubtask, vTZCMCOML, vTZCMCPRO );
      return( -1 );
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CheckOutERD_or_TE( zVIEW vSubtask, zVIEW vTZCMREPO, zVIEW vTemp,
                                zVIEW vTZCMCPRO, zVIEW vTZCMCOML, zVIEW vTZCMLPLO,
                                zLONG lType )
{
   zULONG  ulZKey;

   if ( SetCursorFirstEntityByInteger( vTZCMCPRO, "Z_MetaDef", "Type", lType, "" ) == zCURSOR_SET )
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );

      if ( zwfnTZCMLPLD_CheckOutMeta( vSubtask, vTZCMREPO, vTemp, vTZCMCPRO, vTZCMLPLO, lType, ulZKey ) != 0 )
      {
         zwTZCMLPLD_fnCheckOutSourceAbort( vSubtask, vTZCMCOML, vTZCMCPRO );
         oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );

         DropObjectInstance( vTZCMCPRO );
         DropObjectInstance( vTZCMREPO );
         return( -1 );
      }
   }

   SetAttributeFromAttribute( vTemp, "W_MetaDef", "CheckOutDate", vTZCMCPRO, "UserMetaStatus", "CheckOutDate" );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CheckOutERD_SA_TE( zVIEW vSubtask, zVIEW vTZCMREPO, zVIEW vTemp,
                                zVIEW vTZCMCPRO, zVIEW vTZCMCOML, zVIEW vTZCMLPLO )
{
   zULONG  ulZKey;
   zSHORT  nRC;

   // ERD
   if ( zwfnTZCMLPLD_CheckOutERD_or_TE( vSubtask, vTZCMREPO, vTemp, vTZCMCPRO, vTZCMCOML, vTZCMLPLO, (zLONG) zSOURCE_ERD_META ) < 0 )
   {
      return( -1 );
   }

   // Subject Area
   nRC = SetCursorFirstEntityByInteger( vTZCMCPRO, "Z_MetaDef", "Type", (zLONG) zSOURCE_SA_META, "" );
   while ( nRC == zCURSOR_SET )
   {
      GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );

      if ( zwfnTZCMLPLD_CheckOutMeta( vSubtask, vTZCMREPO, vTemp, vTZCMCPRO, vTZCMLPLO,(zLONG) zSOURCE_SA_META, ulZKey ) != 0 )
      {
         zwTZCMLPLD_fnCheckOutSourceAbort( vSubtask, vTZCMCOML, vTZCMCPRO );
         oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );

         DropObjectInstance( vTZCMCPRO );
         DropObjectInstance( vTZCMREPO );
         return( -1 );
      }

      // set CheckOutDate.
      SetAttributeFromAttribute( vTemp, "W_MetaDef", "CheckOutDate", vTZCMCPRO, "UserMetaStatus", "CheckOutDate" );

      nRC = SetCursorNextEntityByInteger( vTZCMCPRO, "Z_MetaDef", "Type", (zLONG) zSOURCE_SA_META, "" );
   }

   // TE
   if ( zwfnTZCMLPLD_CheckOutERD_or_TE( vSubtask, vTZCMREPO, vTemp, vTZCMCPRO, vTZCMCOML, vTZCMLPLO, (zLONG) zSOURCE_DTE_META ) < 0 )
   {
      return( -1 );
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CheckOutOtherMeta( zVIEW vSubtask, zVIEW vTZCMREPO, zVIEW vTemp,
                                zVIEW vTZCMCPRO, zVIEW vTZCMCOML, zVIEW vTZCMLPLO,
                                zLONG Type, zULONG ulZKey )
{
   if ( zwfnTZCMLPLD_CheckOutMeta( vSubtask, vTZCMREPO, vTemp, vTZCMCPRO, vTZCMLPLO, Type, ulZKey ) != 0 )
   {
      zwTZCMLPLD_fnCheckOutSourceAbort( vSubtask, vTZCMCOML, vTZCMCPRO );
      oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );

      DropObjectInstance( vTZCMCPRO );
      DropObjectInstance( vTZCMREPO );
      return( -1 );
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CheckOutProcess( zVIEW vSubtask, zVIEW vTZCMLPLO,
                              zVIEW vTZCMCOML, zVIEW vTZCMCPRO )
{
   zVIEW    vTZCMREPO;
   zVIEW    vTemp;
   zULONG   ulZKey;
   zLONG    Type;
   zCHAR    szMsg[ zMAX_MESSAGE_LTH + 1 ];

   GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );

   // Position on the correct CPLR entry and send DIL message for component.
   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMCOML, "Z_MetaDef", "ZKey" );
   SetCursorFirstEntityByInteger( vTZCMCPRO, "Z_MetaDef", "ZKey", ulZKey, "" );

   strcpy_s( szMsg, zsizeof( szMsg ), "Checking out Component: " );
   GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMCPRO, "Z_MetaDef", "Name" );
   MB_SetMessage( vSubtask, 1, szMsg );

   GetIntegerFromAttribute( &Type, vTZCMCPRO, "Z_MetaDef", "Type" );

   // Do special processing for different kinds of metas.
   if ( (Type == (zLONG) zSOURCE_ERD_META) || (Type == (zLONG) zSOURCE_DTE_META) || (Type == (zLONG) zSOURCE_SA_META) )
   {
      if ( zwfnTZCMLPLD_CheckOutAskForERD( vSubtask, vTZCMCOML, vTZCMCPRO, Type ) < 0 )
      {
         return( -1 );
      }
   }

   CreateViewFromViewForTask( &vTemp, vTZCMLPLO, 0 );

   if ( (Type == (zLONG) zSOURCE_ERD_META) || (Type == (zLONG) zSOURCE_DTE_META) || (Type == (zLONG) zSOURCE_SA_META) )
   {
      if ( zwfnTZCMLPLD_CheckOutERD_SA_TE( vSubtask, vTZCMREPO, vTemp, vTZCMCPRO, vTZCMCOML, vTZCMLPLO ) < 0 )
      {
         DropView( vTemp );
         return( -1 );
      }
   }
   else
   {
      if ( zwfnTZCMLPLD_CheckOutOtherMeta( vSubtask, vTZCMREPO, vTemp, vTZCMCPRO, vTZCMCOML, vTZCMLPLO, Type, ulZKey ) < 0 )
      {
         DropView( vTemp );
         return( -1 );
      }
   }

   // Set check out date in LPLR.
   // Use the vTemp view and then drop it at the end.
   // We will set the cursor on the first occurrence by ZKey, which will
   // correctly position on the update side (zSOURCE versus zREFER) of the LPLR.
   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMCOML, "Z_MetaDef", "ZKey" );
   SetCursorFirstEntityByInteger( vTemp, "W_MetaDef", "CPLR_ZKey", ulZKey, "LPLR" );
   SetAttributeFromAttribute( vTemp,     "W_MetaDef", "CheckOutDate", vTZCMCPRO, "UserMetaStatus", "CheckOutDate" );
   DropView( vTemp );
   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CheckOutCommit( zVIEW vSubtask, zVIEW vTZCMWKSO, zVIEW vTZCMLPLO, zVIEW vTZCMCPRO )
{
   zVIEW  vCompList;
   zSHORT nRC;

   nRC = zwfnTZCMLPLD_CommitCPRO( vSubtask, vTZCMCPRO );

   oTZCMCPRO_CPLR_Enqueue( vTZCMCPRO, vSubtask, zCPLR_DEQUEUE );

   if ( nRC < 0 )
      return( nRC );

   MB_SetMessage( vSubtask, 1, "Committing Project" );
   if ( oTZCMWKSO_CommitWorkstation( vTZCMWKSO ) >= 0 )
   {
      MB_SetMessage( vSubtask, 1, "Committing Workstation" );
      oTZCMLPLO_CommitLPLR( vTZCMLPLO );

      if ( GetViewByName( &vCompList, "CompList", vSubtask, zLEVEL_TASK ) >= 0 )
         RefreshWindow( vCompList );

      MessageSend( vSubtask, "CM00242", "Configuration Management",
                   "Check Out completed successfully.",
                   zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckOutSource( zVIEW vSubtask )
{
   zVIEW    vTZCMREPO;
   zVIEW    vTZCMCPRO;
   zVIEW    vTZCMCOML;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMLPLO;
   zSHORT   nRC;

   if ( GetViewByName( &vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( zwTZCMLPLD_InitCheckOut( vSubtask ) < 0 )
      return( -1 );

   SetNameForView( vSubtask, "TZCM_ChkInWindow", vSubtask, zLEVEL_TASK );

///////////////////////////////////////////////////////////////////////
/*       Perform Refresh                                             */
///////////////////////////////////////////////////////////////////////

   if ( zwfnTZCMLPLD_CheckOutRefresh( vSubtask, vTZCMLPLO ) < 0 )
      return( -1 );

///////////////////////////////////////////////////////////////////////
/*       Perform CheckOut                                            */
///////////////////////////////////////////////////////////////////////

   if ( zwfnTZCMLPLD_LoadRepo_CPRO( vSubtask, &vTZCMREPO, &vTZCMCPRO, vTZCMCOML ) < 0 )
   {
      return( -1 );
   }

   // Loop through each selected MetaDef and check in the corresponding UserMetaStatus entity in the CPLR.
   // Then commit the CPLR.
   nRC = SetCursorFirstSelectedEntity( vTZCMCOML, "Z_MetaDef", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      if ( zwfnTZCMLPLD_CheckOutProcess( vSubtask, vTZCMLPLO, vTZCMCOML, vTZCMCPRO ) < 0 )
      {
         return( -1 );
      }

      nRC = SetCursorNextSelectedEntity( vTZCMCOML, "Z_MetaDef", 0 );
   }

   zwfnTZCMLPLD_CheckOutCommit( vSubtask, vTZCMWKSO, vTZCMLPLO, vTZCMCPRO );

   SetCtrlState( vSubtask, "Details", zCONTROL_STATUS_ENABLED, FALSE );
   SetCtrlState( vSubtask, "CheckOutSource", zCONTROL_STATUS_ENABLED, FALSE );
   SetCtrlState( vSubtask, "AuditTrail", zCONTROL_STATUS_ENABLED, FALSE );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_SetRepositoryClient( zVIEW vSubtask, zVIEW vTZCMREPO,
                                  zVIEW vTZCMWKSO, zULONG ulZKey2 )
{
   zSHORT   nRC;
   zCHAR    szMsg[ zMAX_MESSAGE_LTH + 1 ];

   strcpy_s( szMsg, zsizeof( szMsg ), "Your RepositoryClient was not found on the\n " );
   strcat_s( szMsg, zsizeof( szMsg ), "Installation. This is an ERROR situation.\n" );
   strcat_s( szMsg, zsizeof( szMsg ), "However, I'm willing to add your RepoClient.\n" );
   strcat_s( szMsg, zsizeof( szMsg ), "to the Installation if you choose correctly." );

   if ( MessagePrompt( vSubtask, "CM00260", "Configuration Management",
                        szMsg, zBEEP, zBUTTONS_OKCANCEL,
                        zRESPONSE_OK,  0 ) != zRESPONSE_OK )
   {
      MessageSend( vSubtask, "CM00261", "Configuration Management",
                   "Check Out aborted!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // if the RepositoryClient not in Entity UserRepositoryClient, then this RepositoryClient does not exist in database, create this
   nRC = SetCursorFirstEntityByInteger( vTZCMREPO, "UserRepositoryClient", "ZKey",(zLONG) ulZKey2, "Installation" );
   if ( nRC != zCURSOR_SET )
   {
      // check the workstation-ID (NextWKS_Id is greater than WKS_ID)
      if ( CompareAttributeToAttribute( vTZCMREPO, "Installation", "NextWKS_Id", vTZCMWKSO, "RepositoryClient", "WKS_Id" ) == 1 )
      {
         CreateEntity( vTZCMREPO, "RepositoryClient", zPOS_AFTER );
         SetMatchingAttributesByName( vTZCMREPO, "RepositoryClient", vTZCMWKSO, "RepositoryClient", zSET_ALL );
      }
      else
      {
          strcpy_s( szMsg, zsizeof( szMsg ), "Your RepositoryClient cannot be added to \n" );
          strcat_s( szMsg, zsizeof( szMsg ), "the Repository for the following reasons:\n\n" );
          strcat_s( szMsg, zsizeof( szMsg ), "Your Workstation was not set up with the current\n" );
          strcat_s( szMsg, zsizeof( szMsg ), "Repository, so that adding the workstation might\n" );
          strcat_s( szMsg, zsizeof( szMsg ), "destroy the Repository by generating invalid zKeys.\n" );
          strcat_s( szMsg, zsizeof( szMsg ), "Sorry, you have to delete your POR-File and setup \n" );
          strcat_s( szMsg, zsizeof( szMsg ), "a new workstation.\n\n" );
          strcat_s( szMsg, zsizeof( szMsg ), "Check Out aborted!" );
          MessagePrompt( vSubtask, "CM00708", "Configuration Management",
                         szMsg, zBEEP, zBUTTONS_OK,
                         zRESPONSE_OK,  0 );
          return( -1 );
      }
   }
   else  // RepositoryClient exists in database without FK_Zey for Installation
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "This is an error situation. \n\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Your RepositoryClient cannot be added to the Repository\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "because a workstation with the current ID already exists,\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "but not for the current installation. \n\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Sorry, you have to delete your POR-File and setup a new\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "workstation.\n\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "Check Out aborted!" );
      MessagePrompt( vSubtask, "CM00710", "Configuration Management",
                     szMsg, zBEEP, zBUTTONS_OK, zRESPONSE_OK,  0 );
      return( -1 );
   }

   if ( CommitObjectInstance( vTZCMREPO ) < 0 )
   {
      MessageSend( vSubtask, "CM00709", "Configuration Management",
                   "Workstation could not be committed to Repository. \n\nCheck Out aborted!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_SetCheckOutValues( zVIEW vSubtask, zVIEW vTZCMCPRO,
                                zVIEW vTZCMWKSO, zVIEW vTZCMWIPO )
{
   zVIEW    vTZCMCOML;
   zULONG   ulZKey2;
   zCHAR    szTimestamp[ 33 ];

   CreateMetaEntity( vSubtask, vTZCMCPRO, "UserMetaStatus", zPOS_AFTER );

   SetAttributeFromInteger( vTZCMCPRO, "UserMetaStatus", "Status", 1 );
   SetAttributeFromAttribute( vTZCMCPRO, "UserMetaStatus", "Comments", vTZCMWIPO, "ROOT", "CheckOutComments" );

   SysGetDateTime( szTimestamp, zsizeof( szTimestamp ) );
   SetAttributeFromString( vTZCMCPRO, "UserMetaStatus", "CheckOutDate", szTimestamp );


   IncludeSubobjectFromSubobject( vTZCMCPRO, "User_1", vTZCMWKSO, "User", zPOS_AFTER );
   IncludeSubobjectFromSubobject( vTZCMCPRO, "RepositoryClient", vTZCMWKSO, "RepositoryClient", zPOS_AFTER );

   GetIntegerFromAttribute( (zPLONG)&ulZKey2, vTZCMWKSO, "LPLR", "ZKey" );
   if ( SetCursorFirstEntityByInteger( vTZCMCPRO, "LPLR", "ZKey", (zLONG) ulZKey2, "" ) < zCURSOR_SET )
   {
      // This is an error condition that should never occur, so if it does, we are going to put the LPLR entry back into the CPLR.
      IncludeSubobjectFromSubobject( vTZCMCPRO, "LPLR", vTZCMWKSO, "LPLR", zPOS_AFTER );
   }

   IncludeSubobjectFromSubobject( vTZCMCPRO, "LPLR_CheckOut", vTZCMCPRO, "LPLR", zPOS_AFTER );

   if ( GetViewByName( &vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK ) > 0 )
   {
      CreateMetaEntity( vSubtask, vTZCMCOML, "UserMetaStatus", zPOS_AFTER );

      SetMatchingAttributesByName( vTZCMCOML, "UserMetaStatus", vTZCMCPRO, "UserMetaStatus", zSET_ALL );
      IncludeSubobjectFromSubobject( vTZCMCOML, "User", vTZCMWKSO, "User", zPOS_AFTER );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_CheckOutMeta( zVIEW vSubtask, zVIEW vTZCMREPO, zVIEW vTemp,
                           zVIEW vTZCMCPRO, zVIEW vTZCMLPLO, zLONG Type,
                           zULONG ulZKey )
{
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMWIPO;
   zSHORT   nRC;
   zULONG   ulZKey2;

   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK );

   SetCursorFirstEntityByInteger( vTemp, "W_MetaType", "Type", Type, "" );
   SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaType", "Type", Type + 2000, "" );

   nRC = SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "CPLR_ZKey",(zLONG) ulZKey, "" );
   if ( nRC != zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00257", "Configuration Management",
                   "W_MetaDef not found!\nCheck Out aborted!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Check CheckOut Status
   if ( CheckExistenceOfEntity( vTZCMCPRO, "UserMetaStatus" ) == zCURSOR_SET )
   {
      zwfnTZCMLPLD_InitCheckOutAbort( vSubtask, vTZCMCPRO, "User_1" );
      return( -1 );
   }

   // Check RepositoryClient
   GetIntegerFromAttribute( (zPLONG) &ulZKey2, vTZCMWKSO, "RepositoryClient", "ZKey" );
   nRC = SetCursorFirstEntityByInteger( vTZCMREPO, "RepositoryClient", "ZKey",(zLONG) ulZKey2, "" );
   if ( nRC != zCURSOR_SET )
   {
      if ( zwfnTZCMLPLD_SetRepositoryClient( vSubtask, vTZCMREPO, vTZCMWKSO, ulZKey2 ) < 0 )
         return( -1 );
   }

   if ( SetCursorFirstEntityByInteger( vTemp, "W_MetaDef", "CPLR_ZKey", (zLONG) ulZKey, "" ) == zCURSOR_SET )
   {
      // We used to give an error if a meta looked like it was already checked out.
      // But it no longer seems necessary and actually gets in the way if an ER was
      // checked in but its DTE or SA was left hanging.
      // Thus we will now exclude an existing W_MetaDef entry if it is found.
      ExcludeEntity( vTemp, "W_MetaDef", zREPOS_NEXT );
   }

   if ( zwfnTZCMLPLD_ActivateCPLR_Meta( vSubtask, vTZCMCPRO, Type, ulZKey ) != 0 )
      return( -1 );

   // Set UpdateFlag and Check Out Flag
   SetAttributeFromInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 0 );
   SetAttributeFromInteger( vTZCMLPLO, "W_MetaDef", "Status", 1 );

   IncludeSubobjectFromSubobject( vTemp, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zPOS_AFTER );

   zwfnTZCMLPLD_SetCheckOutValues( vSubtask, vTZCMCPRO, vTZCMWKSO, vTZCMWIPO );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_ActivateCPLR_Meta( zVIEW vSubtask, zVIEW vTZCMCPRO,
                                zLONG Type, zULONG ulZKey )
{
   zVIEW    vKZDBHQUA;
   zVIEW    vTZCMLPLO;
   zVIEW    vMetaOI;
   zVIEW    vZeidonCM;
   zVIEW    vTaskLPLR;
   zCHAR    szLPLR_FileSpec[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR    szZKey[ 31 ];
   zCHAR    szName[ 31 ];
   zSHORT   nRC;

   if ( ActivateEmptyObjectInstance ( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) >= 0 )
   {
      CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
      CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );
   }
   else
      return( -1 );

   SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", SRC_CMOD[ Type ].szOD_ROOT );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", SRC_CMOD[ Type ].szOD_ROOT );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "ZKey" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
   zltoa( ulZKey, szZKey, zsizeof( szZKey ) );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", szZKey );
   MB_SetMessage( vSubtask, 1, "Activating Meta from Repository" );

   // We will first try to Activate the meta as a shadow file object.
   // Only if it's not there will we undergo the overhead of reading
   // the meta as a normal object from the database.
   // If we can read the file, we will commit it to the LPLR so that we
   // can turn around and do an ActivateOI_FromFile and then continue as
   // normal.
   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), vTZCMLPLO, "LPLR", "MetaSrcDir" );
   ofnTZCMWKSO_AppendSlash( szLPLR_FileSpec );

   if ( Type == zSOURCE_VOR_META )
      zltoxa( ulZKey, szName );
   else
      GetStringFromAttribute( szName, zsizeof( szName ), vTZCMCPRO, "Z_MetaDef", "Name" );

   strcat_s( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), szName );
   strcat_s( szLPLR_FileSpec, zsizeof( szLPLR_FileSpec ), SRC_CMOD[ Type ].szOD_EXT );

   nRC = oTZCMLPLO_CopyFileFromServerFile( vSubtask, szLPLR_FileSpec, vTZCMCPRO, szName, SRC_CMOD[ Type ].szOD_EXT + 1 );
   if ( nRC >= 0 )
   {
      nRC = ActivateOI_FromFile( &vMetaOI, SRC_CMOD[ Type ].szOD, vTZCMCPRO, szLPLR_FileSpec, zSINGLE | zIGNORE_ATTRIB_ERRORS );
   }

   if ( nRC < 0 )
   {
      MessageSend( vSubtask, "CM00263", "Configuration Management",
                   "Activation of Meta from Repository failed",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Get the view to ZedionCM OI.
   nRC = GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );

   // Get the view to TaskLPLR OI.
   nRC = GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   nRC = cfPostCheckout( (zSHORT) Type, vZeidonCM, vMetaOI, vTaskLPLR, 1 );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_ActivateCOMPL( zVIEW vSubtask, zPVIEW vTZCMCOML, zVIEW vTZCMLPLO )
{
   zVIEW    vKZDBHQUA;
   zULONG   ulZKey;
   zSHORT   nRC;
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ];
   zCHAR    szName[ 33 ];
   zCHAR    szZKeyValue[ 33 ];

   if ( GetViewByName( vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( *vTZCMCOML );

   // Activate Component List
   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMLPLO, "CorrespondingCPLR", "ZKey" );
   if ( ActivateEmptyObjectInstance( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) < 0 )
   {
      return( -1 );
   }

   SetNameForView( vKZDBHQUA, "KZDBHQUA", vSubtask, zLEVEL_TASK );
   CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
   CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );

   SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "CPLR" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "CPLR" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "ZKey" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
   zltoa( ulZKey, szZKeyValue, zsizeof( szZKeyValue ) );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", szZKeyValue );

   nRC = ActivateObjectInstance( vTZCMCOML, "TZCMCOML", vSubtask, vKZDBHQUA, zSINGLE | zLEVEL_APPLICATION );

   DropObjectInstance( vKZDBHQUA );

   if ( nRC < 0 )
   {
      GetStringFromAttribute( szName, zsizeof( szName ), vTZCMLPLO, "CorrespondingCPLR", "Name" );
      strcpy_s( szMsg, zsizeof( szMsg ), "Unable to activate Corresponding CPLR ' " );
      strcat_s( szMsg, zsizeof( szMsg ), szName );
      strcat_s( szMsg, zsizeof( szMsg ), "' from database! " );
      MessageSend( vSubtask, "CM00266", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   SetNameForView( *vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK );
   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_RemoveStatus( zVIEW vSubtask, zVIEW vTZCMCOML, zVIEW vTZCMWKSO,
                           zVIEW vTZCMLPLO, zVIEW vTZCMLPLW, zVIEW vTZCMRPTO,
                           zLONG lType )
{
   zVIEW  vTZCMLPLO2;
   zLONG  lLPLR_ZKey;
   zLONG  lSubType;
   zSHORT nRC;

   // If the meta is marked as checked out (ie., there is a UserMetaStatus
   // subobject), we will delete it.  We will check to make sure that
   // the LPLR we are on is the one that checked out the meta before
   // we remove the check out status.
   // The CheckOutFlag is used to skip Release processing if the
   // operator responds no to the prompt below. It is initialized to
   // 1 to support the case where the check-out status has already been
   // removed by the System Administrator.
   CreateEntity( vTZCMRPTO, "Z_MetaDef", zREPOS_AFTER );
   SetMatchingAttributesByName( vTZCMRPTO, "Z_MetaDef", vTZCMLPLW, "W_MetaDef", zSET_ALL );
   SetAttributeFromAttribute( vTZCMRPTO, "Z_MetaDef", "ZKey", vTZCMLPLW, "W_MetaDef", "CPLR_ZKey" );
   CreateEntity( vTZCMRPTO, "ReportLine", zREPOS_AFTER );
   SetAttributeFromString( vTZCMRPTO, "ReportLine", "ReportLine", "Remove Check Out State" );

   if ( CheckExistenceOfEntity( vTZCMCOML, "UserMetaStatus" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lLPLR_ZKey, vTZCMWKSO, "LPLR", "ZKey" );

      if ( CheckExistenceOfEntity( vTZCMCOML, "LPLR_CheckOut" ) >= zCURSOR_SET &&
           CompareAttributeToInteger( vTZCMCOML, "LPLR_CheckOut", "ZKey", lLPLR_ZKey ) == 0 )
      {
         // Remove meta entries
         DeleteEntity( vTZCMCOML, "UserMetaStatus", zREPOS_AFTER );
      }
   }

   // If the meta is a Domain Group or an Operation Group, remove the associated Domains or
   // Operations from the LPLR.
   if ( lType == zSOURCE_DOMAINGRP_META || lType == zSOURCE_GOPGRP_META )
   {
      if ( lType == zSOURCE_DOMAINGRP_META )
         lSubType = zREFER_DOMAIN_META;
      else
         lSubType = zREFER_GO_META;

      CreateViewFromViewForTask( &vTZCMLPLO2, vTZCMLPLO, 0 );

      nRC = SetCursorFirstEntityByInteger( vTZCMLPLO2, "W_MetaType", "Type", lSubType, 0 );
      nRC = SetCursorFirstEntity( vTZCMLPLO2, "W_MetaDef", 0 );
      while ( nRC >= zCURSOR_SET )
      {
         if ( CompareAttributeToAttribute( vTZCMLPLO2, "W_MetaDef", "GroupName", vTZCMLPLO,  "W_MetaDef", "Name" ) == 0 )
         {
            DeleteEntity( vTZCMLPLO2, "W_MetaDef", zREPOS_NONE );
         }

         nRC = SetCursorNextEntity( vTZCMLPLO2, "W_MetaDef", 0 );
      }

      DropView( vTZCMLPLO2 );
   }

   // Now delete the LPLR entry.
   DeleteEntity( vTZCMLPLO, "W_MetaDef", zREPOS_NONE );

   // Also remove from work list.
   DeleteEntity( vTZCMLPLW, "W_MetaDef", zREPOS_NONE );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CommitCPRO( zVIEW vSubtask, zVIEW vTZCMCPRO )
{
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ];

   MB_SetMessage( vSubtask, 1, "Committing CPLR" );

   if ( CommitObjectInstance( vTZCMCPRO ) < 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Commit of CPLR '" );
      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMCPRO, "CPLR", "Name" );
      strcat_s( szMsg, zsizeof( szMsg ), "' failed! " );
      MessageSend( vSubtask, "CM00256", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CreateViewForRefresh( zVIEW vSubtask, zPVIEW vTZCMRPTO, zVIEW vTZCMCOML )
{
   if ( GetViewByName( vTZCMRPTO, "TZCMRPTO", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( *vTZCMRPTO );

   ActivateEmptyObjectInstance( vTZCMRPTO, "TZCMRPTO", vSubtask, zMULTIPLE );
   SetNameForView( *vTZCMRPTO, "TZCMRPTO", vSubtask, zLEVEL_TASK );

   CreateEntity( *vTZCMRPTO, "CPLR", zPOS_AFTER );
   SetMatchingAttributesByName( *vTZCMRPTO, "CPLR", vTZCMCOML, "CPLR", zSET_ALL );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_RefreshAndCommit( zVIEW vSubtask, zVIEW vTZCMRPTO, zVIEW vTZCMCOML, zVIEW vTZCMLPLO )
{
   zCHAR    szName[ 33 ];

   // Refresh the LPLR.  The refresh routine requires the vSubtask view
   // to be named as follows.
   SetNameForView( vSubtask, "TZCM_ChkInWindow", vSubtask, zLEVEL_TASK );

   // Refresh user defined, the Removed Components only
   if ( CheckExistenceOfEntity( vTZCMRPTO, "Z_MetaDef" ) >= zCURSOR_SET )
   {
      SetAllSelectStatesForEntity( vTZCMRPTO, "ReportLine", TRUE, "CPLR" );
      if ( zwTZCMLPLD_OptionRefreshFromRepo( vSubtask, &vTZCMLPLO, szName, zRefreshUserDefined ) < 0 )
      {
         return( -1 );
      }
   }

   // Finally, commit the CPLR and LPLR.
   if ( zwfnTZCMLPLD_CommitCPRO( vSubtask, vTZCMCOML ) < 0 )
      return( -1 );

   oTZCMLPLO_CommitLPLR( vTZCMLPLO );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_AskForRemoveERD_TE_SA( zVIEW vTZCMLPLW, zLONG lType )
{
   zCHAR  szMsg[ zSHORT_MESSAGE_LTH + 1 ];

   if ( lType == (zLONG) zSOURCE_ERD_META )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Removing Check Out State from Data Model will remove\n"
                                        "Check Out State for all Subject Areas and TE!" );
   }
   else
   if ( lType == (zLONG) zSOURCE_DTE_META )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Removing Check Out State from TE will remove\n"
                                        "Check Out State for Data Model and all Subject Areas!" );
   }
   else
   if ( lType == (zLONG) zSOURCE_SA_META )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Removing Check Out State from a Subject Area will remove\n"
                                        "Check Out State for Data Model, all Subject Areas and TE!" );
   }

   strcat_s( szMsg, zsizeof( szMsg ), "\n\nContinue with Remove Check Out State?" );
   if ( MessagePrompt( vTZCMLPLW, "CM00253", "Configuration Management",
                       szMsg, zBEEP, zBUTTONS_YESNO, zRESPONSE_NO, 0 ) == zRESPONSE_YES )
   {
      return( 1 );
   }
   else
   {
      return( -1 );
   }
}

static zSHORT
zwfnTZCMLPLD_SelectERD_TE_SA( zVIEW vTZCMLPLW )
{
   if ( SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", (zLONG) zSOURCE_ERD_META, "" ) >= zCURSOR_SET )
   {
      SetAllSelectStatesForEntity( vTZCMLPLW, "W_MetaDef", TRUE, "" );
   }

   if ( SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", (zLONG) zSOURCE_DTE_META, "" ) >= zCURSOR_SET )
   {
      SetAllSelectStatesForEntity( vTZCMLPLW, "W_MetaDef", TRUE, "" );
   }

   if ( SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", (zLONG) zSOURCE_SA_META, "" ) >= zCURSOR_SET )
   {
      SetAllSelectStatesForEntity( vTZCMLPLW, "W_MetaDef", TRUE, "" );
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_CheckSelectSate( zVIEW vTZCMLPLW, zLONG lSourceType, zLONG lType )
{
   zVIEW  vTZCMLPLW_Sel;
   zSHORT nRC1;
   zSHORT nRC = 0;

   CreateViewFromViewForTask( &vTZCMLPLW_Sel, vTZCMLPLW, 0 );

   if ( lType == (zLONG) zSOURCE_ERD_META || lType == (zLONG) zSOURCE_DTE_META )
   {
      if ( SetCursorFirstEntityByInteger( vTZCMLPLW_Sel, "W_MetaType", "Type", lType, "" ) >= zCURSOR_SET )
      {
         if ( CheckExistenceOfEntity( vTZCMLPLW_Sel, "W_MetaDef" ) >= zCURSOR_SET &&
              GetSelectStateOfEntity( vTZCMLPLW_Sel, "W_MetaDef" ) == FALSE )
         {
            nRC = zwfnTZCMLPLD_AskForRemoveERD_TE_SA( vTZCMLPLW_Sel, lSourceType );
         }
      }
   }
   else
   if ( lType == (zLONG) zSOURCE_SA_META )
   {
      if ( SetCursorFirstEntityByInteger( vTZCMLPLW_Sel, "W_MetaType", "Type", lType, "" ) >= zCURSOR_SET )
      {
         nRC1 = SetCursorFirstEntity( vTZCMLPLW_Sel, "W_MetaDef", "" );
         while ( nRC1 >= zCURSOR_SET && nRC == 0 )
         {
            if ( CheckExistenceOfEntity( vTZCMLPLW_Sel, "W_MetaDef" ) >= zCURSOR_SET &&
                 GetSelectStateOfEntity( vTZCMLPLW_Sel, "W_MetaDef" ) == FALSE )
            {
               nRC = zwfnTZCMLPLD_AskForRemoveERD_TE_SA( vTZCMLPLW_Sel, lSourceType );
            }

            nRC1 = SetCursorNextEntity( vTZCMLPLW_Sel, "W_MetaDef", "" );
         }
      }
   }

   if ( nRC == 1 )
   {
      zwfnTZCMLPLD_SelectERD_TE_SA( vTZCMLPLW );
   }

   DropView( vTZCMLPLW_Sel );
   return( nRC );
}

static zSHORT
zwfnTZCMLPLD_AskForRemove( zVIEW vSubtask, zVIEW vTZCMLPLW )
{
   zSHORT  nRC1;
   zSHORT  nRC = 0;
   zLONG   lType;

   if ( SetCursorFirstSelectedEntity( vTZCMLPLW, "W_MetaDef", "LPLR" ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00241", "Configuration Management",
                   "Please select a Component for Remove Check Out Status.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      return( -1 );
   }

   if ( MessagePrompt( vSubtask, "CM00269", "Configuration Management",
                       "OK to Remove Check Out Status for selected Components?",
                       zBEEP, zBUTTONS_YESNO, zRESPONSE_NO, 0 ) == zRESPONSE_NO )
   {
      return( -1 );
   }

   nRC1 = SetCursorFirstSelectedEntity( vTZCMLPLW, "W_MetaDef", "LPLR" );
   while ( nRC1 >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lType, vTZCMLPLW, "W_MetaType", "Type" );

      if ( lType == (zLONG) zSOURCE_ERD_META )
      {
         nRC = zwfnTZCMLPLD_CheckSelectSate( vTZCMLPLW, lType, zSOURCE_DTE_META );
         if ( nRC )
            break;

         nRC = zwfnTZCMLPLD_CheckSelectSate( vTZCMLPLW, lType, zSOURCE_SA_META );
         if ( nRC )
            break;
      }
      else
      if ( lType == (zLONG) zSOURCE_DTE_META )
      {
         nRC = zwfnTZCMLPLD_CheckSelectSate( vTZCMLPLW, lType, zSOURCE_ERD_META );
         if ( nRC )
            break;

         nRC = zwfnTZCMLPLD_CheckSelectSate( vTZCMLPLW, lType, zSOURCE_SA_META );
         if ( nRC )
            break;
      }
      else
      if ( lType == (zLONG) zSOURCE_SA_META )
      {
         nRC = zwfnTZCMLPLD_CheckSelectSate( vTZCMLPLW, lType, zSOURCE_ERD_META );
         if ( nRC )
            break;

         nRC = zwfnTZCMLPLD_CheckSelectSate( vTZCMLPLW, lType, zSOURCE_DTE_META );
         if ( nRC )
            break;

         nRC = zwfnTZCMLPLD_CheckSelectSate( vTZCMLPLW, lType, zSOURCE_SA_META );
         if ( nRC )
            break;
      }

      nRC1 = SetCursorNextSelectedEntity( vTZCMLPLW, "W_MetaDef", "LPLR" );
   }

   if ( SetCursorFirstSelectedEntity( vTZCMLPLW, "W_MetaDef", "LPLR" ) < zCURSOR_SET )
      return( -1 );
   else
      return( nRC );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_ExcludeActive( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMLPLW;
   zVIEW    vTZCMCOML;
   zVIEW    vTZCMRPTO;
   zLONG    lType;
   zLONG    lZKey;
   zSHORT   nRC;
   zCHAR    szMsg[ zSHORT_MESSAGE_LTH + 1 ];

   // This routine removes the Check Out status for the metas selected
   // in the LPLR view (TZCMLPLO).  There are two possible conditions:
   // 1. The meta selected has check out status set at both the LPLR and the
   //    CPLR.
   // 2. The meta selected has check out status set at only the LPLR.  This
   //    could occur if the Repository Administrator had removed the Check
   //    Out status on the repository through CPLR functionality.

   // Either of the two above conditions are valid and the status is removed
   // in each case.  A message is sent to the operator in the second case,
   // however, to notify him of the situation.

   // Note that this routine has been modified to process multiple metas as
   // selected.

   // In either case above, the meta itself is logically deleted from the LPLR
   // (though not physically, as explained below).  Since the operator can
   // now remove multiple checkout statuses as a time, we do a refresh of the
   // LPLR at the end.

   // The logical delete of the meta is accomplished by deleting both of the
   // associated zSOURCE and zREFER W_MetaDef entries from the LPLR OI.  This
   // works because Refresh processing will refresh any meta for which there
   // is no corresponding W_MetaDef entry in the LPLR OI.

   // The steps for this routine are:
   // 1. Check if the meta has check out status on the CPLR and if so, remove
   //    it.
   // 2. Remove the meta from the LPLR object for both zSOURCE and zREFER.
   //    o If the meta is a Domain or Operation Group, remove the corresponding
   //      Domain and Operation entries.
   //    o If the meta is a LOD, we will delete the VOR by the same name.  This
   //      may end up being a problem, but we cannot assume that any other VOR
   //      for that LOD wasn't created for a Dialog.

   // We will not concern ourselves at this point with deleting files, either
   // the meta itself or related source files.  This will occur automatically
   // during refresh because the W_MetaDef entry is deleted in the LPLR OI.
   // The only problem would occur if a new file (such as a new source)
   // were created while the meta was checked out.  But this would only leave
   // an unused file around that would do no harm and would be eliminated
   // during the next migration.

   if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );
   if ( GetViewByName( &vTZCMLPLW, "TZCMLPLW", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );
   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) < zCURSOR_SET )
      return( -1 );

   if ( zwfnTZCMLPLD_AskForRemove( vSubtask, vTZCMLPLW ) < 0 )
      return( 0 );

   // Activate the Component List.
   if ( zwfnTZCMLPLD_ActivateCOMPL( vSubtask, &vTZCMCOML, vTZCMLPLO ) < 0 )
      return( -1 );

   zwfnTZCMLPLD_CreateViewForRefresh( vSubtask, &vTZCMRPTO, vTZCMCOML );

   // Loop for each selected meta.
   nRC = SetCursorFirstSelectedEntity( vTZCMLPLW, "W_MetaDef", "LPLR" );
   while ( nRC >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lType, vTZCMLPLW, "W_MetaType", "Type" );
      nRC = SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaType", "Type", lType, "" );

      GetIntegerFromAttribute( &lZKey, vTZCMLPLW, "W_MetaDef", "CPLR_ZKey" );
      nRC = SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "CPLR_ZKey", lZKey, "" );
      if ( nRC < zCURSOR_SET )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Component '" );
         GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMLPLW, "W_MetaDef", "Name" );
         strcat_s( szMsg, zsizeof( szMsg ), "' not found in Project." );
         MessageSend( vSubtask, "CM00256", "Configuration Management",
                      szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
         continue;
      }

      nRC = SetCursorFirstEntityByInteger( vTZCMCOML, "Z_MetaDef", "ZKey", lZKey, "" );
      if ( nRC >= zCURSOR_SET )
         zwfnTZCMLPLD_RemoveStatus( vSubtask, vTZCMCOML, vTZCMWKSO, vTZCMLPLO, vTZCMLPLW, vTZCMRPTO, lType );
      else
         MessageSend( vSubtask, "CM00256", "Configuration Management",
                      "Component cannot be removed, because it is new.",
                      zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );

      nRC = SetCursorNextSelectedEntity( vTZCMLPLW, "W_MetaDef", "LPLR" );
   }

   RefreshWindow( vSubtask );
   nRC = zwfnTZCMLPLD_RefreshAndCommit( vSubtask, vTZCMRPTO, vTZCMCOML, vTZCMLPLO );

   oTZCMLPLO_CommitLPLR( vTZCMLPLO );

   MB_SetMessage( vSubtask, 1, "" );
   return( nRC );
}

static zSHORT
zwfnTZCMLPLD_ActivateREFO( zVIEW vSubtask, zVIEW vTZCMLPLO, zPVIEW vTZCMREFO,
                           zPCHAR pchName, zSHORT nRefreshLPLR )
{
   zVIEW    vKZDBHQUA;
   zULONG   ulZKey;
   zSHORT   nRC;
   zCHAR    szZKeyValue[ 33 ];
   zCHAR    szERR_Msg[zSHORT_MESSAGE_LTH + 1];

   GetStringFromAttribute( pchName, 33, vTZCMLPLO, "CorrespondingCPLR", "Name" );
   GetIntegerFromAttribute( (zPLONG)&ulZKey, vTZCMLPLO, "CorrespondingCPLR", "ZKey" );

   if ( ulZKey <= 0 )
   {
      MessageSend( vSubtask, "CM00274", "Configuration Management",
                   "There is no corresponding CPLR for this Project!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   if ( GetViewByName( vTZCMREFO, "TZCMREFO", vSubtask, zLEVEL_TASK ) >= 0 )
      DropObjectInstance( *vTZCMREFO );

   if ( ActivateEmptyObjectInstance( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) < 0 )
   {
      return( -1 );
   }

   MB_SetMessage( vSubtask, 2, "Activating CPLR" );
   SetNameForView( vKZDBHQUA, "KZDBHQUA", vSubtask, zLEVEL_TASK );
   CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
   CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );

   SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "CPLR" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "CPLR" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "ZKey" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
   zltoa( ulZKey, szZKeyValue, zsizeof( szZKeyValue ) );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", szZKeyValue );

   if ( nRefreshLPLR == zLoadRefreshList )
   {
      nRC = ActivateObjectInstance( vTZCMREFO, "TZCMREFL", vSubtask, vKZDBHQUA, zSINGLE | zLEVEL_APPLICATION );
   }
   else
   {
      nRC = ActivateObjectInstance( vTZCMREFO, "TZCMREFO", vSubtask, vKZDBHQUA, zSINGLE | zLEVEL_APPLICATION );
   }

   DropObjectInstance( vKZDBHQUA );
   MB_SetMessage( vSubtask, 2, "" );

   if ( nRC < 0 )
   {
      strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Unable to activate CPLR '" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), pchName );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "' from database! " );
      MessageSend( vSubtask, "CM00277", "Configuration Management",
                   szERR_Msg, zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   SetNameForView( *vTZCMREFO, "TZCMREFO", vSubtask, zLEVEL_TASK );

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_LoadRefreshList( zVIEW vSubtask,
                              zVIEW vTZCMLPLO,
                              zVIEW vTZCMCPRO )
{
   zVIEW    vTZCMRPTO;
   zCHAR    szTimestamp[ 33 ];
   zCHAR    szPrevLPLR_LastRefreshDate[ 33 ];

   SysGetDateTime( szTimestamp, zsizeof( szTimestamp ) );
   GetStringFromAttribute( szPrevLPLR_LastRefreshDate, zsizeof( szPrevLPLR_LastRefreshDate ), vTZCMLPLO, "LPLR", "LastRefreshDate" );

   // TZCMRPTO is used to build a Refresh Report */
   ActivateEmptyObjectInstance( &vTZCMRPTO, "TZCMRPTO", vTZCMLPLO, zMULTIPLE );
   SetNameForView( vTZCMRPTO, "TZCMRPTO", vTZCMLPLO, zLEVEL_TASK );

   // Refresh the ReusableCPLRs then the rest.
   if ( SetCursorFirstEntity( vTZCMCPRO, "ReusableCPLR", 0 ) == zCURSOR_SET )
   {
      if ( zwTZCMLPLO_RefreshReusableCPLRs( vSubtask, vTZCMLPLO, vTZCMCPRO, szTimestamp, szPrevLPLR_LastRefreshDate, FALSE ) < 0 )
         return( -1 );
   }

   if ( zwTZCMLPLO_LoadRefreshListForCPLR( vSubtask, vTZCMLPLO, vTZCMCPRO, szPrevLPLR_LastRefreshDate ) < 0 )
      return( -1 );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_OptionRefreshFromRepo( zVIEW   vSubtask,
                                  zPVIEW  vTZCMLPLO,
                                  zPCHAR  pchName,
                                  zSHORT  nRefreshLPLR )
{
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMREFO;
   zULONG   ulZKey;
   zSHORT   nRC = 0;

   SetNameForView( vSubtask,"TZCM_ChkInWindow", vSubtask, zLEVEL_TASK );

   if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      MB_SetMessage( vSubtask, 2, "Loading Project" );
      zwTZCMLPLD_LoadLPLR( vSubtask );
      GetViewByName( vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   }

   if ( *vTZCMLPLO <= 0 )
      return( -1 );

   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMWKSO, "RepositoryClient", "DefaultLPLR_ZKey" );
   if ( CompareAttributeToInteger( *vTZCMLPLO, "LPLR", "ZKey", (zLONG) ulZKey ) != 0 )
   {
      zwfnTZCMLPLD_SwitchLPLR( vSubtask,  *vTZCMLPLO );
   }

   if ( zwfnTZCMLPLD_ActivateREFO( vSubtask, *vTZCMLPLO, &vTZCMREFO, pchName, nRefreshLPLR ) < 0 )
   {
      return( -1 );
   }

   // Test whether the CPLR ist not enqueued and enqueue it.
   if ( oTZCMCPRO_CPLR_Enqueue( vTZCMREFO, vSubtask, zCPLR_ENQUEUE_FOR_REFRESH ) < 0 )
   {
      return( -1 );
   }

   if ( nRefreshLPLR == zRefreshLPLR )
      nRC = oTZCMLPLO_RefreshLPLR( vSubtask, *vTZCMLPLO, vTZCMREFO );
   else
   if ( nRefreshLPLR == zLoadRefreshList )
      nRC = zwfnTZCMLPLD_LoadRefreshList( vSubtask, *vTZCMLPLO, vTZCMREFO );
   else
   if ( nRefreshLPLR == zRefreshUserDefined )
      nRC = oTZCMLPLO_RefreshPartial( vSubtask, *vTZCMLPLO, vTZCMREFO );

   // Set DeQueue Flag
   oTZCMCPRO_CPLR_Enqueue( vTZCMREFO, vSubtask, zCPLR_DEQUEUE );
   DropObjectInstance( vTZCMREFO );

   return( nRC );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_RefreshUserDefined( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMRPTO;
   zCHAR    szName[ 33 ];
   zSHORT   nRC;

   if ( zwTZCMLPLD_OptionRefreshFromRepo( vSubtask, &vTZCMLPLO, szName, zLoadRefreshList ) < 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToTopWindow, 0, 0 );
      return( -1 );
   }

   GetViewByName( &vTZCMRPTO, "TZCMRPTO", vSubtask, zLEVEL_TASK );
   if ( SetEntityCursor( vTZCMRPTO, "Z_MetaDef", 0, zQUAL_SCOPE_OI | zPOS_FIRST, 0, 0, 0, 0, 0, 0 ) < zCURSOR_SET )
   {
      MessageSend( vSubtask, "CM00232", "Configuration Management",
                   "The list of metas Available for Refresh is Empty.",
                   zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );
      DropObjectInstance( vTZCMRPTO );
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToTopWindow, 0, 0 );
      return( 1 );
   }
   else
   {
      nRC = SetCursorFirstEntity( vTZCMRPTO, "CPLR", "" );
      while ( nRC >= zCURSOR_SET )
      {
         OrderEntityForView( vTZCMRPTO, "Z_MetaDef", "Type A Name A" );
         nRC = SetCursorNextEntity( vTZCMRPTO, "CPLR", "" );
      }
      SetEntityCursor( vTZCMRPTO, "Z_MetaDef", 0, zQUAL_SCOPE_OI | zPOS_FIRST, 0, 0, 0, 0, 0, 0 );
   }

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_OptionRefresh( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMRPTO;
   zVIEW    vCompList;
   zCHAR    szName[ 33 ];
   zCHAR    szERR_Msg[  zSHORT_MESSAGE_LTH + 1  ];
   zSHORT   nRC;

   if ( zwTZCMLPLD_OptionRefreshFromRepo( vSubtask, &vTZCMLPLO, szName, zRefreshLPLR ) < 0 )
   {
      return( -1 );
   }

   GetViewByName( &vTZCMRPTO, "TZCMRPTO", vSubtask, zLEVEL_TASK );

   if ( SetEntityCursor( vTZCMRPTO, "Z_MetaDef", 0, zQUAL_SCOPE_OI | zPOS_FIRST, 0, 0, 0, 0, 0, 0 ) >= zCURSOR_SET )
   {
      if ( MessagePrompt( vSubtask, "CM00278", "Configuration Management",
                          "Refresh Processing completed. Do you wish to view results?",
                          zBEEP,         zBUTTONS_YESNO,
                          zRESPONSE_YES,  0 ) == zRESPONSE_YES )
      {
         // Frank H. show the RefreshWindow Immediate,
         // b'cause if the refresh is triggered by a creating a LPLR,
         // then the WAB is set to ReturnRefresh...
         // (line 1368; Operation: zwTZCMLPLD_CreateNewLPLR.
         nRC = SetCursorFirstEntity( vTZCMRPTO, "CPLR", "" );
         while ( nRC >= zCURSOR_SET )
         {
            OrderEntityForView( vTZCMRPTO, "Z_MetaDef", "Type A Name A" );
            nRC = SetCursorNextEntity( vTZCMRPTO, "CPLR", "" );
         }

         SetWindowActionBehavior( vSubtask, zWAB_StartModalWindow | zWAB_ProcessImmediateAction, "TZCMRPTD", "RefreshList" );
      }
      else
         DropObjectInstance( vTZCMRPTO );
   }
   else
   {
      strcpy_s( szERR_Msg, zsizeof( szERR_Msg ), "Project '" );
      GetStringFromAttribute( szERR_Msg + zstrlen( szERR_Msg ), zsizeof( szERR_Msg ) - zstrlen( szERR_Msg ), vTZCMLPLO, "LPLR", "Name" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "' has been successfully refreshed \nfrom CPLR '" );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), szName );
      strcat_s( szERR_Msg, zsizeof( szERR_Msg ), "'." );
      MessageSend( vSubtask, "CM00279", "Configuration Management",
                   szERR_Msg, zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );
   }

   if ( GetViewByName( &vCompList, "CompList", vSubtask, zLEVEL_TASK ) >= 0 )
      RefreshWindow( vCompList );

   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_ViewRefreshReport( zVIEW vSubtask )
{
   zVIEW    vTZCMRPTO;
   zVIEW    vTZCMLPLO;
   zCHAR    szFileSpec[ zMAX_FILESPEC_LTH + 1 ];

   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( szFileSpec, zsizeof( szFileSpec ), vTZCMLPLO, "LPLR", "PgmSrcDir" );
   ofnTZCMWKSO_AppendSlash( szFileSpec );
   strcat_s( szFileSpec, zsizeof( szFileSpec ), "ZREFRESH.RPT" );

   if ( ActivateOI_FromFile( &vTZCMRPTO, "TZCMRPTO", vSubtask, szFileSpec, zMULTIPLE | zNOI_OKAY ) < 0 )
   {
      MessageSend( vSubtask, "CM00280", "Configuration Management",
                   "Refresh Report File not found!",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToTopWindow, 0, 0 );
      return( -1 );
   }

   SetNameForView( vTZCMRPTO,"TZCMRPTO", vSubtask, zLEVEL_TASK );
   return( 0 );
}


zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_TaskCountCheck( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTaskLPLR;
   zLONG    TaskCount;
   zCHAR    szMsg[ zMAX_MESSAGE_LTH + 1 ]; // message includes szName
   zCHAR    szName[ 31 ];
   unsigned long ulZKey;
   unsigned long ulSelectedZKey;

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) <= 0 )
      return( -1 );
   if ( GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK ) <= 0 )
      return( -1 );
   GetIntegerFromAttribute( (zPLONG) &ulSelectedZKey, vTZCMLPLO, "LPLR", "ZKey" );
   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTaskLPLR, "LPLR", "ZKey" );
   if ( ulZKey != ulSelectedZKey )
   {
      GetStringFromAttribute( szName, zsizeof( szName ), vTZCMLPLO, "LPLR", "Name" );
      if ( GetViewByName( &vTaskLPLR, szName, vSubtask, zLEVEL_APPLICATION ) <= 0 )
            return( 0 );
   }
   else
      GetIntegerFromAttribute( &TaskCount, vTaskLPLR, "LPLR", "TaskUseCount" );
   if ( TaskCount > 1 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Other Zeidon tools are currently using Project\n" );
      GetStringFromAttribute( szMsg + zstrlen( szMsg ), zsizeof( szMsg ) - zstrlen( szMsg ), vTZCMLPLO, "LPLR", "Name" );
      strcat_s( szMsg, zsizeof( szMsg ), "!\nExecuting the requested function may corrupt\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "any active metas. To continue end any Zeidon\n" );
      strcat_s( szMsg, zsizeof( szMsg ), "tools currently using this Project!" );
      MessageSend( vSubtask, "CM00289", "Configuration Management",
                   szMsg, zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_SwitchLPLR( zVIEW vSubtask, zVIEW vTZCMLPLO )
{
   zULONG ulZKey;
   zVIEW  vZeidonCM;
   zVIEW  vTZCMWKSO;
   zVIEW  vTaskLPLR;
// zCHAR  szMsg[  zSHORT_MESSAGE_LTH + 1  ];

   // This operation is an attempt to clean (ie. drop) all the CM views and
   // object instances.  All it does is drop all OIs named at the subtask level
   // for the "Zeidon Core Services" task.

   GetViewByName( &vZeidonCM, "ZeidonCM", vSubtask, zLEVEL_APPLICATION );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vZeidonCM, zLEVEL_SUBTASK );
   if ( vTZCMWKSO == 0 )  // view isn't there
   {
      MessageSend( vSubtask, "CM00290", "Configuration Management",
                   "Unable to obtain RepositoryClient View",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( -1 );
   }

   // Get and set the new Default LPLR ZKey.
   // The following line of code was replaced by DonC on 12/19/13 because the TZCMLPLO OI doesn't always have the same ZKey as the TZCMWKSO.LPLR entity.
   //GetIntegerFromAttribute((zPLONG) &ulZKey, vTZCMLPLO, "LPLR", "ZKey" );
   GetIntegerFromAttribute((zPLONG) &ulZKey, vTZCMWKSO, "LPLR", "ZKey" );

   GetViewByName( &vTaskLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   if ( vTaskLPLR )  // View is there
   {
      TerminateLPLR( vSubtask );
   }

   // PETTIT - In the future I will check the return code and continue with the switch based upon it.
   SetAttributeFromInteger( vTZCMWKSO, "RepositoryClient", "DefaultLPLR_ZKey", ulZKey );
   SetCursorFirstEntityByInteger( vTZCMWKSO, "LPLR", "ZKey", ulZKey, "" );

   // Establish new position on workstation.
   InitializeDefaultLPL( vSubtask );

   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );

   return( 1 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_BuildAllActive( zVIEW vTZCMLPLW, zVIEW vTZCMLPLO )
{
   zLONG    lType;

   if ( SetCursorFirstEntity( vTZCMLPLO, "W_MetaDef", "LPLR" ) < zCURSOR_SET )
      return( 0 );

   while ( TRUE )
   {
      GetIntegerFromAttribute( &lType, vTZCMLPLO, "W_MetaType", "Type" );
      if ( lType >= 2000 )
         break;

      // DGC - DOMGRP
      // We don't want to show domains and global operations, so just continue loop if the current type is a domain or gop.
      if ( lType == zSOURCE_DOMAIN_META || lType == zSOURCE_GO_META )
      {
         if ( SetCursorNextEntity( vTZCMLPLO, "W_MetaDef", "LPLR" ) < zCURSOR_SET )
         {
            break;
         }

         continue;
      }

      SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );

      CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
      SetMatchingAttributesByName( vTZCMLPLW, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zSET_ALL );

      if ( SetCursorNextEntity( vTZCMLPLO, "W_MetaDef", "LPLR" ) < zCURSOR_SET )
         break;
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_BuildActiveUpdated( zVIEW vTZCMLPLW, zVIEW vTZCMLPLO, zVIEW vTZCMCPRO )
{
   zSHORT   nRC;
   zLONG    lType;
   zLONG    lZKey;

   nRC = SetCursorFirstEntity( vTZCMLPLO, "W_MetaDef", "LPLR" );
   GetIntegerFromAttribute( &lType, vTZCMLPLO, "W_MetaType", "Type" );
   GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "W_MetaDef", "CPLR_ZKey" );
   while ( nRC >= zCURSOR_SET && lType < 2000 )
   {
      // DGC - DOMGRP
      // We don't want to show domains and global operations, so just continue loop if the current type is a domain or gop.
      if ( lType != zSOURCE_DOMAIN_META && lType != zSOURCE_GO_META )
      {
         if ( SetCursorFirstEntityByInteger( vTZCMCPRO, "Z_MetaDef", "ZKey", lZKey, 0 ) >= zCURSOR_SET )
         {
            SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
            CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
            SetMatchingAttributesByName( vTZCMLPLW, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zSET_ALL );
         }
      }

      nRC = SetCursorNextEntity( vTZCMLPLO, "W_MetaDef", "LPLR" );
      GetIntegerFromAttribute( &lType, vTZCMLPLO, "W_MetaType", "Type" );
      GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "W_MetaDef", "CPLR_ZKey" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_BuildActiveNew( zVIEW vTZCMLPLW, zVIEW vTZCMLPLO, zVIEW vTZCMCPRO )
{
   zSHORT   nRC;
   zLONG    lType;
   zLONG    lZKey;

   nRC = SetCursorFirstEntity( vTZCMLPLO, "W_MetaDef", "LPLR" );
   GetIntegerFromAttribute( &lType, vTZCMLPLO, "W_MetaType", "Type" );
   GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "W_MetaDef", "CPLR_ZKey" );

   while (( nRC >= zCURSOR_SET ) && ( lType < 2000 ))
   {
      // DGC - DOMGRP
      // We don't want to show domains and global operations, so just continue loop if the current type is a domain or gop.
      if ( lType != zSOURCE_DOMAIN_META && lType != zSOURCE_GO_META )
      {
         if ( SetCursorFirstEntityByInteger( vTZCMCPRO, "Z_MetaDef", "ZKey", lZKey, "" ) < zCURSOR_SET )
         {
            SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
            CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
            SetMatchingAttributesByName( vTZCMLPLW, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zSET_ALL );
         }
      }

      nRC = SetCursorNextEntity( vTZCMLPLO, "W_MetaDef", "LPLR" );

      GetIntegerFromAttribute( &lType, vTZCMLPLO, "W_MetaType", "Type" );
      GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "W_MetaDef", "CPLR_ZKey" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_BuildRefreshAll( zVIEW vTZCMLPLW, zVIEW vTZCMLPLO, zVIEW vTZCMCPRO )
{
   zSHORT   nRC;
   zLONG    lType = 2000;
   zLONG    lZKey;

   if ( CompareAttributeToAttribute( vTZCMCPRO, "CPLR", "LastCheckInDate", vTZCMLPLO, "LPLR", "LastRefreshDate" ) < 1 )
      return( 0 );

   nRC = SetCursorFirstEntity( vTZCMCPRO, "Z_MetaDef", "" );

   GetIntegerFromAttribute( &lZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );
   GetIntegerFromAttribute( &lType, vTZCMCPRO, "Z_MetaDef", "Type" );

   while ( nRC >= zCURSOR_SET )
   {
      nRC = SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "CPLR_ZKey", lZKey, "LPLR" );
      // DGC - DOMGRP
      // We don't want to show domains and global operations, so just continue loop if the current type is a domain or gop.
      if ( lType != zSOURCE_DOMAIN_META && lType != zSOURCE_GO_META )
      {
         if ( nRC >= zCURSOR_SET )
         {
            if ( CompareAttributeToInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 0 ) < 1 )
            {
               if ( CompareAttributeToAttribute( vTZCMCPRO, "Z_MetaDef", "LastUpdateDate", vTZCMLPLO, "LPLR", "LastRefreshDate" ) == 1 ||
                    CompareAttributeToAttribute( vTZCMCPRO, "Z_MetaDef", "LastCheckInDate", vTZCMLPLO, "LPLR", "LastRefreshDate" ) == 1 )
               {
                  SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
                  CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
                  SetMatchingAttributesByName( vTZCMLPLW, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zSET_ALL );
               }
            }
         }
         else
         {
            SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
            CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
            SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "CPLR_ZKey", vTZCMCPRO, "Z_MetaDef", "ZKey" );
            SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "Name", vTZCMCPRO, "Z_MetaDef", "Name" );
            SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "Desc", vTZCMCPRO, "Z_MetaDef", "Desc" );
            SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "LastUpdateDate", vTZCMCPRO, "Z_MetaDef", "LastUpdateDate" );
         }
      }

      nRC = SetCursorNextEntity( vTZCMCPRO, "Z_MetaDef", "" );
      GetIntegerFromAttribute( &lZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );
      GetIntegerFromAttribute( &lType, vTZCMCPRO, "Z_MetaDef", "Type" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_BuildRefreshUpdate( zVIEW vTZCMLPLW, zVIEW vTZCMLPLO, zVIEW vTZCMCPRO )
{
   zSHORT   nRC;
   zLONG    lType = 2000;
   zLONG    lZKey;

   if ( CompareAttributeToAttribute( vTZCMCPRO, "CPLR", "LastCheckInDate", vTZCMLPLO, "LPLR", "LastRefreshDate" ) < 1 )
      return( 0 );

   nRC = SetCursorFirstEntity( vTZCMCPRO, "Z_MetaDef", "" );

   GetIntegerFromAttribute( &lZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );
   GetIntegerFromAttribute( &lType, vTZCMCPRO, "Z_MetaDef", "Type" );

   while ( nRC >= zCURSOR_SET )
   {
      nRC = SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "CPLR_ZKey", lZKey, "LPLR" );

      // DGC - DOMGRP
      // We don't want to show domains and global operations, so just continue loop if the current type is a domain or gop.
      if ( lType != zSOURCE_DOMAIN_META && lType != zSOURCE_GO_META && nRC >= zCURSOR_SET )
      {
         if ( CompareAttributeToInteger( vTZCMLPLO, "W_MetaDef", "UpdateInd", 0 ) < 1 )
         {
            if ( CompareAttributeToAttribute( vTZCMCPRO, "Z_MetaDef", "LastUpdateDate", vTZCMLPLO, "LPLR", "LastRefreshDate" ) == 1 ||
                 CompareAttributeToAttribute( vTZCMCPRO, "Z_MetaDef", "LastCheckInDate", vTZCMLPLO, "LPLR", "LastRefreshDate" ) == 1 )
            {
               SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
               CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
               SetMatchingAttributesByName( vTZCMLPLW, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zSET_ALL );
            }
         }
      }

      nRC = SetCursorNextEntity( vTZCMCPRO, "Z_MetaDef", "" );

      GetIntegerFromAttribute( &lZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );
      GetIntegerFromAttribute( &lType, vTZCMCPRO, "Z_MetaDef", "Type" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_BuildRefreshNew( zVIEW vTZCMLPLW, zVIEW vTZCMLPLO, zVIEW vTZCMCPRO )
{
   zSHORT   nRC;
   zLONG    lType = 2000;
   zLONG    lZKey;

   if ( CompareAttributeToAttribute( vTZCMCPRO, "CPLR", "LastCheckInDate", vTZCMLPLO, "LPLR", "LastRefreshDate" ) < 1 )
      return( 0 );

   nRC = SetCursorFirstEntity( vTZCMCPRO, "Z_MetaDef", "" );

   GetIntegerFromAttribute( &lZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );
   GetIntegerFromAttribute( &lType, vTZCMCPRO, "Z_MetaDef", "Type" );

   while ( nRC >= zCURSOR_SET )
   {
      nRC = SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "CPLR_ZKey", lZKey, "LPLR" );
      // DGC - DOMGRP
      // We don't want to show domains and global operations, so just continue loop if the current type is a domain or gop.
      if ( lType != zSOURCE_DOMAIN_META && lType != zSOURCE_GO_META &&
           nRC >= zCURSOR_SET )
      {
         SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
         CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
         SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "CPLR_ZKey",  vTZCMCPRO, "Z_MetaDef", "ZKey" );
         SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "Name", vTZCMCPRO, "Z_MetaDef", "Name" );
         SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "Desc", vTZCMCPRO, "Z_MetaDef", "Desc" );
         SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "LastUpdateDate", vTZCMCPRO, "Z_MetaDef", "LastUpdateDate" );
      }
      nRC = SetCursorNextEntity( vTZCMCPRO, "Z_MetaDef", "" );

      GetIntegerFromAttribute( &lZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );
      GetIntegerFromAttribute( &lType, vTZCMCPRO, "Z_MetaDef", "Type" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_BuildCheckedOutAll( zVIEW vTZCMLPLW, zVIEW vTZCMLPLO, zVIEW vTZCMCPRO )
{
   zLONG    lType;
   zLONG    lZKey;
   zSHORT   nRC;

   nRC = SetCursorFirstEntity( vTZCMCPRO, "UserMetaStatus", "CPLR" );
   while ( nRC >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lZKey, vTZCMCPRO, "Z_MetaDef", "ZKey" );
      GetIntegerFromAttribute( &lType, vTZCMCPRO, "Z_MetaDef", "Type" );

      // DGC - DOMGRP
      // We don't want to show domains and global operations, so just continue loop if the current type is a domain or gop.
      if ( lType != zSOURCE_DOMAIN_META && lType != zSOURCE_GO_META )
      {
         nRC = SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "CPLR_ZKey", lZKey, "LPLR" );
         if ( nRC >= zCURSOR_SET )
         {
            SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
            CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
            SetMatchingAttributesByName( vTZCMLPLW, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zSET_ALL );
         }
         else
         {
            SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
            CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
            SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "CPLR_ZKey", vTZCMCPRO, "Z_MetaDef", "ZKey" );
            SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "Name", vTZCMCPRO, "Z_MetaDef", "Name" );
            SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "Desc", vTZCMCPRO, "Z_MetaDef", "Desc" );
            SetAttributeFromAttribute( vTZCMLPLW, "W_MetaDef", "LastUpdateDate", vTZCMCPRO, "Z_MetaDef", "LastUpdateDate" );
         }
      }

      nRC = SetCursorNextEntity( vTZCMCPRO, "UserMetaStatus", "CPLR" );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwfnTZCMLPLD_BuildCheckedOutByUser( zVIEW vSubtask, zVIEW vTZCMLPLW,
                                    zVIEW vTZCMLPLO, zVIEW vTZCMCOML,
                                    zPCHAR pchUserName )
{
   zSHORT   nRC;
   zLONG    lType;
   zLONG    lZKey;
   zLONG    lUserZKey;
   zLONG    lWksZKey;
   zLONG    lLPLR_ZKey;
   zVIEW    vTZCMWKSO;

   if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   GetIntegerFromAttribute( &lUserZKey, vTZCMWKSO, "User", "ZKey" );
   GetIntegerFromAttribute( &lWksZKey, vTZCMWKSO, "RepositoryClient", "ZKey" );
   GetIntegerFromAttribute( &lLPLR_ZKey, vTZCMWKSO, "LPLR", "ZKey" );

   nRC = SetCursorFirstEntityByInteger( vTZCMCOML, "LPLR_CheckOut", "ZKey", lLPLR_ZKey, "CPLR" );
   while ( nRC >= zCURSOR_SET )
   {
      nRC = SetCursorFirstEntityByInteger( vTZCMCOML, "User", "ZKey", lUserZKey, "" );
      if ( nRC >= zCURSOR_SET )
      {
         nRC = SetCursorFirstEntityByInteger( vTZCMCOML, "RepositoryClient", "ZKey", lWksZKey, "" );
         if ( nRC >= zCURSOR_SET )
         {
            GetIntegerFromAttribute( &lZKey, vTZCMCOML, "Z_MetaDef", "ZKey" );
            GetIntegerFromAttribute( &lType, vTZCMCOML, "Z_MetaDef", "Type" );

            // DGC - DOMGRP
            // We don't want to show domains and global operations..
            if ( lType != zSOURCE_DOMAIN_META && lType != zSOURCE_GO_META )
            {
               SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaDef", "CPLR_ZKey", lZKey, "LPLR" );
               SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", lType, "" );
               CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
               SetMatchingAttributesByName( vTZCMLPLW, "W_MetaDef", vTZCMLPLO, "W_MetaDef", zSET_ALL );
            }
         }
      }

      nRC = SetCursorNextEntityByInteger( vTZCMCOML, "LPLR_CheckOut", "ZKey", lLPLR_ZKey, "CPLR" );
   }

   return( 0 );
}

static zSHORT
zwTZCMLPLD_BuildTZCMLPLW( zVIEW vSubtask, zPVIEW vTZCMLPLW )
{
   zLONG  Type;

   if ( ActivateEmptyObjectInstance( vTZCMLPLW, "TZCMLPLO", vSubtask, zSINGLE ) >= 0 )
   {
      SetNameForView( *vTZCMLPLW, "TZCMLPLW", vSubtask, zLEVEL_TASK );

      if ( CreateEntity( *vTZCMLPLW, "LPLR", zPOS_AFTER ) >= 0 )
      {
         for ( Type = 0; Type <= zSOURCE_MAX_META; Type++ )
         {
            CreateEntity( *vTZCMLPLW, "W_MetaType", zPOS_AFTER );
            SetAttributeFromInteger( *vTZCMLPLW, "W_MetaType", "Type", Type );
         }
      }
   }

   return( 0 );
}


static zSHORT
zwfnTZCMLPLD_BuildRemoveCheckedOuts( zVIEW vSubtask, zVIEW vTZCMLPLO,
                                     zVIEW vTZCMLPLW, zVIEW vCompL )
{
   zVIEW   vTZCMLPLO_Copy;
   zVIEW   vTZCMLPLW_Copy;
   zBOOL   bCheckOutBySYSADM = FALSE;
   zSHORT  nRC;

   CreateViewFromViewForTask( &vTZCMLPLO_Copy, vTZCMLPLO, 0 );
   CreateViewFromViewForTask( &vTZCMLPLW_Copy, vTZCMLPLW, 0 );

   nRC = SetCursorFirstEntity( vTZCMLPLO_Copy, "W_MetaDef", "LPLR" );
   while ( nRC >= zCURSOR_SET )
   {
      if ( SetCursorFirstEntityByAttr( vTZCMLPLW_Copy, "W_MetaDef", "CPLR_ZKey", vTZCMLPLO_Copy, "W_MetaDef", "CPLR_ZKey", "LPLR" ) != zCURSOR_SET &&
           CompareAttributeToInteger( vTZCMLPLO_Copy, "W_MetaDef", "Status", 1 ) == 0 )
      {
         if ( SetCursorFirstEntityByAttr( vCompL, "Z_MetaDef", "ZKey", vTZCMLPLO_Copy, "W_MetaDef", "CPLR_ZKey", "" ) >= zCURSOR_SET &&
              CheckExistenceOfEntity( vCompL, "UserMetaStatus" ) != zCURSOR_SET )
         {
            if ( SetCursorFirstEntityByAttr( vTZCMLPLW, "W_MetaType", "Type", vTZCMLPLO_Copy, "W_MetaType", "Type", "" ) >= zCURSOR_SET )
            {
               CreateEntity( vTZCMLPLW, "W_MetaDef", zPOS_AFTER );
               SetMatchingAttributesByName( vTZCMLPLW, "W_MetaDef", vTZCMLPLO_Copy, "W_MetaDef", zSET_ALL );
               SetAttributeFromString( vTZCMLPLW, "W_MetaDef", "SysadmRemoveCheckOutState", "Check Out Removed by SYSADM" );
               bCheckOutBySYSADM = TRUE;
            }
         }
      }

      nRC = SetCursorNextEntity( vTZCMLPLO_Copy, "W_MetaDef", "LPLR" );
   }

   if ( bCheckOutBySYSADM )
   {
      SetWindowActionBehavior( vSubtask, zWAB_ReplaceWindowWithModalWindow, "TZCMLPLD", "CompListWithRemove" );
   }

   DropView( vTZCMLPLO_Copy );
   DropView( vTZCMLPLW_Copy );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_BuildSelectedCompList( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMLPLW;
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMCOML;
   zVIEW    vTemp;
   zVIEW    vCompL = 0;
   zCHAR    szUserName[ 33 ];
   zCHAR    szMsg[ 33 ];
   zLONG    Option;

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( &vTZCMLPLW, "TZCMLPLW", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vTZCMLPLW );

   GetIntegerFromAttribute( &Option, vTZCMWIPO, "ROOT", "ComponentListType" );
   if ( Option > 1 )
   {
      if ( zwfnTZCMLPLD_ActivateCOMPL( vSubtask, &vTZCMCOML, vTZCMLPLO ) < 0 )
         return( -1 );
      CreateViewFromViewForTask( &vCompL, vTZCMCOML, 0 );
   }

   zwTZCMLPLD_BuildTZCMLPLW( vSubtask, &vTZCMLPLW );
   CreateViewFromViewForTask( &vTemp, vTZCMLPLO, 0 );

   switch ( Option )
   {
      case 1:           // All Active
         zwfnTZCMLPLD_BuildAllActive( vTZCMLPLW, vTemp );
         SetWindowCaptionTitle( vSubtask, 0, "Active - All" );
         break;

      case 2:           // Active and Updated
         zwfnTZCMLPLD_BuildActiveUpdated( vTZCMLPLW, vTemp, vCompL );
         SetWindowCaptionTitle( vSubtask, 0, "Active - Updated Only" );
         break;

      case 3:           // Active and New
         zwfnTZCMLPLD_BuildActiveNew( vTZCMLPLW, vTemp, vCompL );
         SetWindowCaptionTitle( vSubtask, 0, "Active - New Only" );
         break;

      case 4:           // Refresh All
         zwfnTZCMLPLD_BuildRefreshAll( vTZCMLPLW, vTemp, vCompL );
         SetWindowCaptionTitle( vSubtask, 0, "Refresh - All" );
         break;

      case 5:           // Refresh and Updated
         zwfnTZCMLPLD_BuildRefreshUpdate( vTZCMLPLW, vTemp, vCompL );
         SetWindowCaptionTitle( vSubtask, 0, "Refresh - Updated Only" );
         break;

      case 6:           // Refresh and New
         zwfnTZCMLPLD_BuildRefreshNew( vTZCMLPLW, vTemp, vCompL );
         SetWindowCaptionTitle( vSubtask, 0, "Refresh - New Only" );
         break;

      case 7:           // Checked Out All
         zwfnTZCMLPLD_BuildCheckedOutAll( vTZCMLPLW, vTemp, vCompL );
         SetWindowCaptionTitle( vSubtask, 0, "Checked Out - All" );
         break;

      case 8:           // Checked Out By Signed On User
         GetStringFromAttribute( szUserName, zsizeof( szUserName ), vTZCMWIPO, "ROOT", "UserName" );
         zwfnTZCMLPLD_BuildCheckedOutByUser( vSubtask, vTZCMLPLW, vTemp, vCompL, szUserName );
         strcpy_s( szMsg, zsizeof( szMsg ), "Checked Out By - " );
         strcat_s( szMsg, zsizeof( szMsg ), szUserName );
         SetWindowCaptionTitle( vSubtask, 0, szMsg );
         break;

      case 9:     // Checked Out By User and Remove Check Out State in SYSADM
         GetStringFromAttribute( szUserName, zsizeof( szUserName ), vTZCMWIPO, "ROOT", "UserName" );
         zwfnTZCMLPLD_BuildCheckedOutByUser( vSubtask, vTZCMLPLW, vTemp, vCompL, szUserName );
         zwfnTZCMLPLD_BuildRemoveCheckedOuts( vSubtask, vTZCMLPLO, vTZCMLPLW, vCompL );
         strcpy_s( szMsg, zsizeof( szMsg ), "Checked Out By - " );
         strcat_s( szMsg, zsizeof( szMsg ), szUserName );
         SetWindowCaptionTitle( vSubtask, 0, szMsg );
         break;

   } // switch ( Option )...

   if ( vCompL != 0 )
      DropView( vCompL );

   DropView( vTemp );

   // We want to temporarily eliminate UI_Specs from the list.  To do this and make it easy to remove later,
   // we will just delete the MetaType zSOURCE_UIS_META, if it exists.
   if ( SetCursorFirstEntityByInteger( vTZCMLPLW, "W_MetaType", "Type", zSOURCE_UIS_META, 0 ) >= zCURSOR_SET )
      DeleteEntity( vTZCMLPLW, "W_MetaType", zREPOS_PREV );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_PreBuildCompList( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLW;
   zVIEW    vTZCMWIPO;

   //BL, 2000.01.25 set Option for BuildCheckedOutByUser = 8
   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) < 0 )
         return( -1 );

   SetAttributeFromInteger( vTZCMWIPO, "ROOT", "ComponentListType", 9 );

   if ( zwTZCMLPLD_BuildSelectedCompList( vSubtask ) < 0 )
   {
      SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, 0, 0 );
      return( -1 );
   }

   if ( GetViewByName( &vTZCMLPLW, "TZCMLPLW", vSubtask, zLEVEL_TASK ) < 0 )
     return( -1 );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_PostBuildCompList( zVIEW vSubtask )
{
   SetNameForView( vSubtask, "CompList", vSubtask, zLEVEL_TASK );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_PreBldCompDetail( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLW;
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMCPRO;
   zLONG    ZKey;

   if ( GetViewByName( &vTZCMLPLW, "TZCMLPLW", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );
   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );
   if ( CompareAttributeToInteger( vTZCMWIPO, "ROOT", "ComponentListType", 6 ) > 0 )
   {
      if ( GetViewByName( &vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK ) < 0 )
      {
         return( -1 );
      }

      GetIntegerFromAttribute( &ZKey, vTZCMLPLW, "W_MetaDef", "CPLR_ZKey" );
      SetCursorFirstEntityByInteger( vTZCMCPRO, "Z_MetaDef", "ZKey", ZKey, "" );
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZCMLPLD_HelpAbout
// PURPOSE:    This Entry does the About
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_HelpAbout( zVIEW vSubtask )
{
   IssueToolAbout( vSubtask, zTOOL_WKSADM, __FILE__, __DATE__, __TIME__ );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZZOLODD_HelpOnHelp
// PURPOSE:    This Entry transfers to HelpOnHelp
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_HelpOnHelp( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, SYSTEM_HELP );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZCMLPLD_HelpBasics
// PURPOSE:    This Entry transfers to basic help
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_HelpBasics( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, BASICS_MANUAL );
   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZCMLPLD_ToolHelp
// PURPOSE:    This Entry transfers to help from the Users Guide
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_ToolHelp( zVIEW vSubtask )
{
   StartZeidonHelp( vSubtask, USERS_GUIDE );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_RetrieveProfile( zVIEW vSubtask )
{
   zVIEW vProfileXFER;
   zVIEW vP;

   oTZ__PRFO_GetViewToProfile( &vProfileXFER, "TZ", vSubtask, zCURRENT_OI );
   CreateViewFromViewForTask( &vP, vProfileXFER, 0 );
   SetNameForView( vP, "ProfileXFER", vSubtask, zLEVEL_TASK );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_OpenMessageTextOI( zVIEW vSubtask )
{
   zVIEW  vMsgText;
   zCHAR  szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zSHORT nRC;

   GetCtrlText( vSubtask, "FileName", szFileName, zMAX_FILESPEC_LTH );
   nRC = ActivateOI_FromFile( &vMsgText, "KZMSGQOO", vSubtask, szFileName, zSINGLE );
   if ( nRC >= 0 )
      SetNameForView( vMsgText, "KZ_OverrideMsg", vSubtask, zLEVEL_TASK );
   else
   {
      MessageSend( vSubtask, "CM00295", "Configuration Management",
                   "Message Object Instance could not be Activated.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_NewMessageTextOI( zVIEW vSubtask )
{
   zVIEW  vMsgText;
   zCHAR  szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zLONG  hFile;

   GetCtrlText( vSubtask, "FileName", szFileName, zMAX_FILESPEC_LTH );
   hFile = SysOpenFile( vSubtask, szFileName, COREFILE_READ );
   if ( hFile < 0 )
   {
      ActivateEmptyObjectInstance( &vMsgText, "KZMSGQOO", vSubtask, zSINGLE );
      CreateEntity( vMsgText, "Task", zPOS_AFTER );
      SetAttributeFromString( vMsgText, "Task", "TemporaryWorkText", szFileName );
      SetNameForView( vMsgText, "KZ_OverrideMsg", vSubtask, zLEVEL_TASK );
   }
   else
   {
      MessageSend( vSubtask, "CM00294", "Configuration Management",
                   "Message Object Instance already exists.",
                   zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CommitMessageTextOI( zVIEW vSubtask )
{
   zVIEW vMsgText;
   zCHAR szFileName[ zMAX_FILESPEC_LTH + 1 ];

   GetViewByName( &vMsgText, "KZ_OverrideMsg", vSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vMsgText, "Task", "TemporaryWorkText" );
   CommitOI_ToFile( vMsgText, szFileName, zASCII );
   DropObjectInstance( vMsgText );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_ReturnFromSubWindow( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWKSO;
   zVIEW    vKZAPPLOO = 0;
   zCHAR    szZeidonDirectory[ zMAX_FILESPEC_LTH + 1 ];

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      // Make sure TZCMWKSO is positioned on same LPLR entry as TZCMLPLO.
      if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) >= 0 )
         SetCursorFirstEntityByAttr( vTZCMWKSO, "LPLR", "ZKey", vTZCMLPLO, "LPLR", "ZKey", 0 );

      // Set Work Directory
      szZeidonDirectory[ 0 ] = 0;
      if ( zwTZCMLPLD_GetZeidonApp( vSubtask, &vKZAPPLOO, szZeidonDirectory, zsizeof( szZeidonDirectory ) ) >= 0 )
      {
         if ( SetCursorFirstEntityByAttr( vKZAPPLOO, "APPLICATION", "APP_NAME", vTZCMLPLO, "LPLR", "Name", "" ) >= zCURSOR_SET )
         {
            GetStringFromAttribute( szZeidonDirectory, zsizeof( szZeidonDirectory ), vKZAPPLOO, "APPLICATION", "APP_LOCAL" );
            SetCtrlText( vSubtask, "edWorkDirectory", szZeidonDirectory );
         }

         DropView( vKZAPPLOO );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CheckShadowDirectory( zVIEW vSubtask,
                                 zVIEW vTZCMREPO )
{
   zCHAR  szShadowDirectory[ zMAX_FILESPEC_LTH + 1 ];
   zSHORT bRC;

   GetStringFromAttribute( szShadowDirectory, zsizeof( szShadowDirectory ), vTZCMREPO, "CPLR", "ExecDir" );
   bRC = SysValidDirOrFile( szShadowDirectory, TRUE, FALSE, zsizeof( szShadowDirectory ) + 1 );
   if ( bRC == 0 )
   {
      MessageSend( vSubtask, "CM00273", "Configuration Management",
                   "Shadow Directory for CPLR does not exist.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
      return( -1 );
   }
   else
      return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZCMLPLD_BuildDialogExecs
// PURPOSE:    This Entry saves all the PWD's that are updatable in the
//             LPLR (that is those of type zSOURCE_DIALOG_META).
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_BuildDialogExecs( zVIEW vSubtask )
{
   zVIEW  vLPLR;
   zVIEW  vMetaList;
   zVIEW  vDialog;
   zVIEW  vPE;
   zCHAR  szMsg[  zSHORT_MESSAGE_LTH + 1 ];
   zCHAR  szDialogName[ 33 ];
   zSHORT nRC;

   // Get the LPLR list and position it on source Dialogs.
   GetViewByName( &vLPLR, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type", zSOURCE_DIALOG_META, 0 );

   // Make sure the PE is available for the XWD build.
   nRC = GetViewByName( &vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );
   if ( nRC < 0 )
   {
      RetrieveViewForMetaList( vSubtask, &vMetaList, zREFER_PENV_META );
      nRC = LoadZeidonPPE( vSubtask, &vPE, zREFER_PENV_META, vMetaList, "Configuration Management", "" );
      if ( nRC < 0 )
         return( -16 );

      SetNameForView( vPE, "TZPESRCO", vSubtask, zLEVEL_TASK );
      DropView( vMetaList );
   }

   // Loop through each dialog and save it.
   nRC = SetCursorFirstEntity( vLPLR, "W_MetaDef", "" );
   while ( nRC >= zCURSOR_SET )
   {
      nRC = ActivateMetaOI( vSubtask, &vDialog, vLPLR, zSOURCE_DIALOG_META, zSINGLE );
      if ( nRC >= 0 )
      {
         GetStringFromAttribute( szDialogName, zsizeof( szDialogName ), vDialog, "Dialog", "Tag" );
         strcpy_s( szMsg, zsizeof( szMsg ), "Building Dialog: " );
         strcat_s( szMsg, zsizeof( szMsg ), szDialogName );
         MB_SetMessage( vSubtask, 1, szMsg );
         CommitMetaOI( vSubtask, vDialog, zSOURCE_DIALOG_META );
         DropMetaOI( vSubtask, vDialog );
      }

      nRC = SetCursorNextEntity ( vLPLR, "W_MetaDef", "" );
   }

   MB_SetMessage( vSubtask, 1, "" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_ActivateCPLR( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMCOML;

   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) >= zCURSOR_SET )
   {
      if ( zwfnTZCMLPLD_ActivateCOMPL( vSubtask, &vTZCMCOML, vTZCMLPLO ) < 0 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_ReturnToParent, 0, 0 );
         return( -1 );
      }

      if ( CheckExistenceOfEntity( vTZCMCOML, "Z_MetaDef" ) >= zCURSOR_SET )
      {
         OrderEntitiesByDefaultAttribs( vTZCMCOML, "Z_MetaDef" );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_SendBootstrapFiles( zVIEW vSubtask )
{
#if 0
   NetStartup( "zeidon", "hzkzoe" );
   NetSendBootstrapFile( "zeidon", "o:\\9c\\w\\bin\\sys\\zeidon.app", "ZEIDON" );
   NetSendBootstrapFile( "zeidon", "o:\\9c\\w\\bin\\sys\\kzomdmoi.xdm", "ZEIDON" );
   NetSendBootstrapFile( "zeidon", "c:\\lplr\\katdb2\\zeidon.xdm", "KATDB2" );
   NetSendBootstrapFile( "zeidon", "c:\\lplr\\katdb2\\gabuzib.xod", "KATDB2" );
   NetSendBootstrapFile( "zeidon", "o:\\9c\\w\\bin\\sys\\zeidon.xdm", "ZEIDON" );
   NetSendBootstrapFile( "zeidon", "o:\\9c\\w\\bin\\sys\\kzapploo.xod", "ZEIDON" );
   NetSendBootstrapFile( "zeidon", "o:\\9c\\w\\bin\\sys\\tzdmxgpo.xod", "ZEIDON" );
   NetSendBootstrapFile( "zeidon", "o:\\9c\\w\\bin\\sys\\tzzoxodo.xod", "ZEIDON" );
   NetSendBootstrapFile( "zeidon", "o:\\9c\\w\\bin\\sys\\kzdbhwob.xod", "ZEIDON" );
   NetSendBootstrapFile( "zeidon", "o:\\9c\\w\\bin\\sys\\kzdbhqua.xod", "ZEIDON" );

#endif

   MB_SetMessage( vSubtask, 1, "Nothing done" );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZCMLPLD_GenerateApplicationShell
// PURPOSE:    This Entry generates a program shell for Domain operations
//             and other LPLR operations for use with Server object engines.
//             The shell allows what are dynamic calls on the windows and
//             OS2 platforms to become static calls on Servers.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_GenApplicationShell( zVIEW vSubtask )
{
   zVIEW vLPLR;
   zSHORT nRC;

   GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );
   nRC = oTZCMLPLO_GenerateCallHeader( vLPLR, vSubtask );

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION:  zwTZCMLPLD_BuildServerExecs
// PURPOSE:    This Entry takes the zeidon.xdm and all xod object instances
//       and sends them to the Server for running the application on
//       the server.
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_BuildServerExecs( zVIEW vSubtask )
{
   zVIEW  vLPLR;
   zVIEW  vMeta;
   zSHORT nRC;
   zCHAR  szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szMetaName[ 13 ];
   zCHAR  szAppName[ 32 ];
   zCHAR  szServerSubDir[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szMsg[64];
   zVIEW  vApplSubtask;
   zCHAR  szServer[ 33 ];

   zCHAR  szDBType[ 2 ];
   zCHAR  szMerkeFileName[ zMAX_FILESPEC_LTH + 1 ];
   zVIEW  vSiron;
   zUSHORT uLV;

   zmemset( szServer, 0, zsizeof( szServer ) );
   GetViewByName( &vLPLR, "TaskLPLR", vSubtask, zLEVEL_TASK );

   // Start the network if necessary.  Use zeidon and hzkzoe as constants for now.
   nRC = NetStatus( vSubtask, "zeidon" );
   if ( nRC == 0 )
   {
      nRC = NetStartup( vSubtask, "zeidon", "hzkzoe" );
      if ( nRC )
      {
         MessageSend( vSubtask, "CM00285", "Configuration Management",
                      "Network cannot be started.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
         return( 0 );
      }
   }

   // First get the application name and make sure it exists in the
   // zeidon.app object on the server.  If it isn't there, add it.
   GetStringFromAttribute( szAppName, zsizeof( szAppName ), vLPLR, "LPLR", "Name" );
   strcpy_s( szFileName, zsizeof( szFileName ), "zeidon.app" );
   SfCreateSubtask( &vApplSubtask, vSubtask, "Zeidon System" );
   nRC = NetActivateOI_FromFile( 0, szServer, &vMeta, "KZAPPLOO", vApplSubtask, szFileName, zSINGLE );
   if ( nRC >= 0 )
   {
      nRC = SetCursorFirstEntityByString( vMeta, "APPLICATION", "APP_NAME", szAppName, 0 );
      if ( nRC >= zCURSOR_SET )
         DropObjectInstance( vMeta );
      else
      {
         CreateEntity( vMeta, "APPLICATION", zPOS_LAST );
         SetAttributeFromString( vMeta, "APPLICATION", "APP_NAME", szAppName );

         // Fuer Unix muss der Verzeichnisname der Applikation in ZEIDON.APP
         // gross geschreiben sein !!!
         for ( uLV = 0; uLV < zstrlen( szAppName ); uLV++ )
            szAppName[ uLV ] = ztoupper( szAppName[ uLV ] );

         strcpy_s( szServerSubDir, zsizeof( szServerSubDir ), szAppName );
         strcat_s( szServerSubDir, zsizeof( szServerSubDir ), "/" );
         SetAttributeFromString( vMeta, "APPLICATION", "APP_DLL", szServerSubDir );
         SetAttributeFromString( vMeta, "APPLICATION", "APP_ADOBIN", szServerSubDir );
         SetAttributeFromString( vMeta, "APPLICATION", "APP_LOCAL", szServerSubDir );
         TraceLineS( "*** Committing server file: ", szFileName );
         strcpy_s( szMsg, zsizeof( szMsg ), "Sending ZEIDON.APP: " );
         MB_SetMessage( vSubtask, 1, szMsg );

         // Send OI to server.
         nRC = NetCommitOI_ToFile( 0, szServer, vMeta, szFileName, zASCII );
         if ( nRC )
         {
            TraceLineI( "NetCommitOI_ToFile nRC: ", nRC );
            TraceLineS( "FileName: ", szFileName );
            IssueError( vSubtask, 0, 0, "Error on NetCommitOI_ToFile" );
         }

         DropObjectInstance( vMeta );
      }
   }
   else
   {
      SfDropSubtask( vApplSubtask, 0 );
      MessageSend( vSubtask, "CM00286", "Configuration Management",
                   "ZEIDON.APP cannot be activated.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      return( 0 );
   }

   SfDropSubtask( vApplSubtask, 0 );

   // Send the XDM before all the xods.
   // First format the file name for activation on the client and then format it for commit on the server.
   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vLPLR, "LPLR", "ExecDir" );
   strcat_s( szFileName, zsizeof( szFileName ), "\\" );
   strcpy_s( szMetaName, zsizeof( szMetaName ), "ZEIDON.XDM" );
   strcat_s( szFileName, zsizeof( szFileName ), szMetaName );
   TraceLineS( "*** Activating client file: ", szFileName );
   nRC = ActivateOI_FromFile( &vMeta, "TZDMXGPO", vSubtask, szFileName, zSINGLE );

   if ( nRC >= 0 )
   {
      // Filename includes Directory-prefix **HH**
      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vLPLR, "LPLR", "Name" );
      strcat_s( szFileName, zsizeof( szFileName ), "/" );
      strcat_s( szFileName, zsizeof( szFileName ), szMetaName );
      TraceLineS( "*** Committing server file: ", szFileName );
      MB_SetMessage( vSubtask, 1, "Sending XDM" );

      // Send OI to server.
      nRC = NetCommitOI_ToFile( 0, szServer, vMeta, szFileName, zASCII );
      if ( nRC )
      {
         TraceLineI( "NetCommitOI_ToFile nRC: ", nRC );
         TraceLineS( "FileName: ", szFileName );
         IssueError( vSubtask, 0, 0, "Error on NetCommitOI_ToFile" );
      }
   }

   // Next loop through all the LODs, activating each XOD and sending
   // it to the server.
   SetCursorFirstEntityByInteger( vLPLR, "W_MetaType", "Type",
                                  zREFER_LOD_META, 0 );
   nRC = SetCursorFirstEntity( vLPLR, "W_MetaDef", 0 );
   while ( nRC >= zCURSOR_SET )
   {
      GetStringFromAttribute( szFileName, zsizeof( szFileName ), vLPLR, "LPLR", "ExecDir" );
      strcat_s( szFileName, zsizeof( szFileName ), "\\" );
      GetStringFromAttribute( szMetaName, zsizeof( szMetaName ), vLPLR, "W_MetaDef", "Name" );
      strcat_s( szFileName, zsizeof( szFileName ), szMetaName );
      strcpy_s( szMerkeFileName, zsizeof( szMerkeFileName ), szFileName);
      strcat_s( szFileName, zsizeof( szFileName ), ".XOD" );
      TraceLineS( "*** Activating client file: ", szFileName );
      nRC = ActivateOI_FromFile( &vMeta, "TZZOXODO", vSubtask, szFileName, zSINGLE );

      if ( nRC >= 0 )
      {
         // Filename includes Directory-prefix **HH**
         GetStringFromAttribute( szFileName, zsizeof( szFileName ), vLPLR, "LPLR", "Name" );
         strcat_s( szFileName, zsizeof( szFileName ), "/" );
         strcat_s( szFileName, zsizeof( szFileName ), szMetaName );
         strcat_s( szFileName, zsizeof( szFileName ), ".XOD" );
         TraceLineS( "*** Committing server file: ", szFileName );
         strcpy_s( szMsg, zsizeof( szMsg ), "Sending XOD: " );
         strcat_s( szMsg, zsizeof( szMsg ), szMetaName );
         MB_SetMessage( vSubtask, 1, szMsg );

         // Send OI to server.
         nRC = NetCommitOI_ToFile( 0, szServer, vMeta, szFileName, zASCII );
         if ( nRC )
         {
            TraceLineI( "NetCommitOI_ToFile nRC: ", nRC );
            TraceLineS( "FileName: ", szFileName );
            IssueError( vSubtask, 0, 0, "Error on NetCommitOI_ToFile" );
         }

         GetStringFromAttribute( szDBType, zsizeof( szDBType ), vMeta, "OBJECT", "SironDB_Type" );
         if ( *szDBType == 'F' )
         {

            // Now we know, that the XOD is for Siron-FlatFiles.
            // Sending the XSK-Files.
            strcat_s( szMerkeFileName, zsizeof( szMerkeFileName ), ".XSK" );
            TraceLineS( "*** Activating client file: ", szMerkeFileName);
            nRC = ActivateOI_FromFile( &vSiron, "KZSIXSKO", vSubtask, szMerkeFileName, zSINGLE );

            GetStringFromAttribute( szFileName, zsizeof( szFileName ), vLPLR, "LPLR", "Name" );
            strcat_s( szFileName, zsizeof( szFileName ), "/" );
            strcat_s( szFileName, zsizeof( szFileName ), szMetaName );
            strcat_s( szFileName, zsizeof( szFileName ), ".XSK" );
            TraceLineS( "*** Committing server file: ", szFileName );
            strcpy_s( szMsg, zsizeof( szMsg ), "Sending XSK: " );
            strcat_s( szMsg, zsizeof( szMsg ), szMetaName );
            MB_SetMessage( vSubtask, 1, szMsg );

            // Send OI to server.
            nRC = NetCommitOI_ToFile( 0, szServer, vSiron, szFileName, zASCII );
            if ( nRC )
            {
               TraceLineI( "NetCommitOI_ToFile nRC: ", nRC );
               TraceLineS( "FileName: ", szFileName );
               IssueError( vSubtask, 0, 0, "Error on NetCommitOI_ToFile" );
            }
         }
      }

      nRC = SetCursorNextEntity( vLPLR, "W_MetaDef", 0 );
   }

   MB_SetMessage( vSubtask, 1, "Transmission Complete" );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CopyDirs( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zCHAR    DirName[ zMAX_FILESPEC_LTH + 1 ];

   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );

   GetStringFromAttribute( DirName, zsizeof( DirName ), vTZCMLPLO, "LPLR", "ExecDir" );
   SetAttributeFromString( vTZCMLPLO, "LPLR", "MetaSrcDir", DirName );
   SetAttributeFromString( vTZCMLPLO, "LPLR", "PgmSrcDir", DirName );

   RefreshCtrl( vSubtask, "MetaSrcDir" );
   RefreshCtrl( vSubtask, "PgmSrcDir" );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_selectUser( zVIEW vSubtask )
{
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMWKSO;

   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) >= 0 )
      {
         SetAttributeFromAttribute( vTZCMWIPO, "ROOT", "UserDesc", vTZCMWKSO, "User", "Desc" );
         RefreshCtrl( vSubtask, "UserDesc" );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_selectUser2( zVIEW vSubtask )
{
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMREPW;

   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      if ( GetViewByName( &vTZCMREPW, "TZCMREPW", vSubtask, zLEVEL_TASK ) >= 0 )
      {
         SetAttributeFromAttribute( vTZCMWIPO, "ROOT", "UserDesc", vTZCMREPW, "User", "Desc" );
         RefreshCtrl( vSubtask, "UserDesc" );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_DefaultDir( zVIEW vSubtask )
{
   zCHAR  szDirName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szLPLR_Name[ 33 ];
   zCHAR  szZeidonDirectory[ zMAX_FILESPEC_LTH + 1 ];

   zVIEW    vKZAPPLOO = 0;
   zVIEW    vTZCMLPLO;

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      // load SystemDrive:
      GetSystemDirectory( szDirName, zsizeof(szDirName) );
      lstrcpyn( szDirName, szDirName, 4);

      strcat( szDirName, "lplr\\" );
      GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vTZCMLPLO, "LPLR", "Name" );
      strcat( szDirName, szLPLR_Name );
      SetAttributeFromString( vTZCMLPLO, "LPLR", "ExecDir",    szDirName );
      SetAttributeFromString( vTZCMLPLO, "LPLR", "MetaSrcDir", szDirName );
      SetAttributeFromString( vTZCMLPLO, "LPLR", "PgmSrcDir",  szDirName );

      RefreshCtrl( vSubtask, "ExecDir" );
      RefreshCtrl( vSubtask, "MetaSrcDir" );
      RefreshCtrl( vSubtask, "PgmSrcDir" );

      // Set Work Directory
      szZeidonDirectory[ 0 ] = 0;
      if ( zwTZCMLPLD_GetZeidonApp( vSubtask, &vKZAPPLOO, szZeidonDirectory, zsizeof( szZeidonDirectory ) ) >= 0 )
      {
         zwTZCMLPLD_GetWorkDir( vKZAPPLOO, szZeidonDirectory );
         SetCtrlText( vSubtask, "edWorkDirectory", szZeidonDirectory );
         DropView( vKZAPPLOO );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_LoadAuditTrailC( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZBRAU2O;
   zVIEW    vKZDBHQUA;
   zULONG   ulZKey;
   zCHAR    szZKey[18];
   zSHORT   nRC;

   if ( GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) == 0 )
      {

         if ( ActivateEmptyObjectInstance( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) >= 0 )
         {
            SetNameForView( vKZDBHQUA, "KZDBHQUA", vSubtask, zLEVEL_TASK );
            CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
            CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );
         }
         else
            return( -1 );

         GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMLPLO, "CorrespondingCPLR", "ZKey" );
         SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "CPLR" );
         SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "CPLR" );
         SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "ZKey" );
         SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
         zltoa( ulZKey, szZKey, zsizeof( szZKey ) );
         SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", szZKey );

         nRC = ActivateObjectInstance( &vTZBRAU2O, "TZBRAU2O", vSubtask, vKZDBHQUA, zSINGLE | zLEVEL_APPLICATION );
         DropObjectInstance( vKZDBHQUA );

         if ( CheckExistenceOfEntity( vTZBRAU2O, "AuditTrail" ) == 0 )
            SetNameForView( vTZBRAU2O, "TZBRAU2O", vSubtask, zLEVEL_TASK );
         else
         {
            MessageSend( vSubtask, "CM00299", "Audit Trail:",
                         "There are no AuditTrail-Information for the corresponding CPLR.",
                         zMSGQ_OBJECT_CONSTRAINT_INFORMATION, zBEEP );
            SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
            return( -1 );
         }
      }
      else
      {
         MessageSend( vSubtask, "CM00299", "Audit Trail:",
                      "There are no AuditTrail-Information for a non-repository Project.",
                      zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( -1 );
      }
   }
   else
      return( -1 );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_LoadAuditTrailM( zVIEW vSubtask )
{

   zVIEW    vTZCMCOML;
   zVIEW    vTZBRAUDO;
   zVIEW    vKZDBHQUA;
   zULONG   ulZKey;
   zCHAR    szZKey[18];
   zSHORT   nRC;

   if ( GetViewByName( &vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if (CheckExistenceOfEntity( vTZCMCOML, "Z_MetaDef" ) == 0 )
      {
         if ( ActivateEmptyObjectInstance( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) >= 0 )
         {
            SetNameForView( vKZDBHQUA, "KZDBHQUA", vSubtask, zLEVEL_TASK );
            CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
            CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );
         }
         else
            return( -1 );

         GetIntegerFromAttribute( (zPLONG)&ulZKey, vTZCMCOML, "Z_MetaDef", "ZKey" );
         SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "Z_MetaDef" );
         SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "Z_MetaDef" );
         SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "ZKey" );
         SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
         zltoa( ulZKey, szZKey, zsizeof( szZKey ) );
         SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", szZKey );

         nRC = ActivateObjectInstance( &vTZBRAUDO, "TZBRAUDO", vSubtask, vKZDBHQUA, zSINGLE | zLEVEL_APPLICATION );
         DropObjectInstance( vKZDBHQUA );

         if ( CheckExistenceOfEntity( vTZBRAUDO, "AuditTrail" ) == 0 )
            SetNameForView( vTZBRAUDO, "TZBRAUDO", vSubtask, zLEVEL_TASK );
      }
      else
      {
         MessageSend( vSubtask, "CM00299", "Audit Trail:",
                      "There are no AuditTrail-Information for the component (2).",
                      zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );

         return( -1 );
      }
   }
   else
      return( -1 );

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_ImportTextFile( zVIEW vSubtask )
{
   zVIEW   vTZCMAUDO;
   zCHAR   szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zLONG   lfFile;
   zLONG   hGlobalHandle;
   zLONG   lLth;
   zLONG   lRC;
   zPCHAR  szBuffer;


   if ( GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      // GetSystemDirectory( szFileName, zsizeof( szFileName ) );

      if ( OperatorPromptForFile( vSubtask, szFileName, zsizeof( szFileName ), "Text Files (*.TXT)|*.txt|", "TXT", TRUE ) == 1 )
      {
         lfFile = SysOpenFile( vSubtask, szFileName, COREFILE_READ );

         // If the File exists, then we need to copy prototypes from the old header file to the new header file.
         if ( lfFile >= 0 )
         {
            // I want to put the File into a description Attribute
            // --> the max available Size is 32000
            lLth = 32000;

            // Get the buffer.
            hGlobalHandle = SysAllocMemory( (zCOREMEM) &szBuffer, lLth + 10, 0, zCOREMEM_ALLOC, 0 );

            lRC = SysReadFile( vSubtask, lfFile, szBuffer, (zUSHORT) (lLth + 5) );

            // Close the import file.
            SysCloseFile( vSubtask, lfFile, 0 );

            // read the file into the buffer
            if ( lRC > lLth &&
                 MessagePrompt( vSubtask, "CM00703",
                                "Configuration Management",
                                "File is larger than 32000 Bytes. Truncate it?",
                                zBEEP, zBUTTONS_YESNO,
                                zRESPONSE_YES, 0 ) == zRESPONSE_NO )
            {
               SysFreeMemory( hGlobalHandle );
               return( -1 );
            }

            if ( CompareAttributeToString( vTZCMAUDO, "AuditTrail", "Desc", "" ) != 0 )
            {
               if ( MessagePrompt( vSubtask, "CM00704",
                                   "Configuration Management",
                                   "Override the current Description ?",
                                   zBEEP, zBUTTONS_YESNO, zRESPONSE_YES, 0 ) == zRESPONSE_NO )
               {
                  SysFreeMemory( hGlobalHandle );
                  return( -1 );
               }
//             else
//                SetAttributeFromString( vTZCMAUDO, "AuditTrail", "Desc", "" );
            }

            // terminate the String:
            szBuffer[ lLth ] = 0;
            SetAttributeFromString( vTZCMAUDO, "AuditTrail", "Desc", szBuffer );
            SysFreeMemory( hGlobalHandle );
            RefreshCtrl( vSubtask, "DescEdit" );
         }
         else
            MessageSend( vSubtask, "CM00299", "Audit Trail:",
                         "The File you specified could not be opened.",
                         zMSGQ_OBJECT_CONSTRAINT_WARNING, zBEEP );
      }
   }

   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_CopyText( zVIEW vSubtask )
{

   zVIEW   vTZCMAUDO;
   zVIEW   vTZCMLPLO;
   zVIEW   vTZCM_ChkInList;
   zVIEW   vTZCM_ChkInList2;
   zVIEW   vTZCMCPRO;
   zLONG   lZKey;

   GetViewByName( &vTZCMAUDO, "TZCMAUDO", vSubtask, zLEVEL_TASK );

   if ( CompareAttributeToString( vTZCMAUDO, "AuditTrail", "Desc", "" ) != 0 &&
        MessagePrompt( vSubtask, "CM00705",
                       "Configuration Management",
                       "Override the current Description ?",
                       zBEEP, zBUTTONS_YESNO,
                       zRESPONSE_YES, 0 ) == zRESPONSE_NO )
   {
      return( -1 );
   }

   GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCM_ChkInList, "TZCM_ChkInList", vSubtask, zLEVEL_TASK );

   if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) >= zCURSOR_SET )
   {
      GetIntegerFromAttribute( &lZKey, vTZCMLPLO, "CorrespondingCPLR", "ZKey" );
      if ( GetViewByName( &vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK ) < 0 || CompareAttributeToInteger( vTZCMCPRO, "CPLR", "ZKey", lZKey ) != 0 )
      {
         MB_SetMessage( vSubtask, 1, "Activating CPLR" );

         if ( oTZCMCPRO_ActivateCPLR( &vTZCMCPRO, (zLONG) lZKey, vSubtask ) < 0 )
            return( -1 );
         else
            SetNameForView( vTZCMCPRO, "TZCMCPRO", vSubtask, zLEVEL_TASK );
      }

      CreateViewFromViewForTask( &vTZCM_ChkInList2, vTZCM_ChkInList, 0 );

      SetCursorFirstSelectedEntity( vTZCM_ChkInList2, "W_MetaDef", "LPLR" );
      if ( SetCursorFirstEntityByAttr( vTZCMCPRO, "Z_MetaDef", "ZKey", vTZCM_ChkInList2, "W_MetaDef", "CPLR_ZKey", "CPLR" ) >= zCURSOR_SET &&
           CheckExistenceOfEntity( vTZCMCPRO, "UserMetaStatus" ) >= zCURSOR_SET )
      {
         SetAttributeFromAttribute( vTZCMAUDO, "AuditTrail", "Desc", vTZCMCPRO, "UserMetaStatus", "Comments" );
         RefreshCtrl( vSubtask, "DescEdit" );
      }
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_ActivateUSER( zVIEW vSubtask, zPVIEW vTZCMUSER, zVIEW vTZCMWIPO )
{
   zVIEW    vKZDBHQUA;
   zSHORT   nRC;
   zCHAR    szName[ 33 ];

   if ( GetViewByName( vTZCMUSER, "TZCMUSER", vSubtask, zLEVEL_TASK ) > 0 )
      return( 0 );

   GetStringFromAttribute( szName, zsizeof( szName ), vTZCMWIPO, "ROOT", "UserName" );
   if ( ActivateEmptyObjectInstance( &vKZDBHQUA, "KZDBHQUA", vSubtask, zSINGLE ) < 0 )
   {
      return( -1 );
   }

   SetNameForView( vKZDBHQUA, "KZDBHQUA", vSubtask, zLEVEL_TASK );
   CreateEntity( vKZDBHQUA, "EntitySpec", zPOS_AFTER );
   CreateEntity( vKZDBHQUA, "QualAttrib", zPOS_AFTER );

   SetAttributeFromString( vKZDBHQUA, "EntitySpec", "EntityName", "User" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "EntityName", "User" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "AttributeName", "Name" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Oper", "=" );
   SetAttributeFromString( vKZDBHQUA, "QualAttrib", "Value", szName );

   nRC = ActivateObjectInstance( vTZCMUSER, "TZCMUSER", vSubtask, vKZDBHQUA, zMULTIPLE | zLEVEL_APPLICATION );

   DropObjectInstance( vKZDBHQUA );

   if ( nRC < 0 )
      return( -1 );

   SetNameForView( *vTZCMUSER, "TZCMUSER", vSubtask, zLEVEL_TASK );
   return( 0 );
}

zOPER_EXPORT zSHORT OPERATION
zwTZCMLPLD_InitMenu( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO;
   zVIEW    vTZCMWIPO;
   zVIEW    vTZCMUSER;
   zSHORT   nEnable = 0;

   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) >= 0 &&
        GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) >= 0 )
   {
      // Gray the CheckIn and CheckOut options if there is no CorrespondingCPLR or Repository User with ReadOnly Authority
      if ( CheckExistenceOfEntity( vTZCMLPLO, "CorrespondingCPLR" ) >= zCURSOR_SET )
      {
         zwfnTZCMLPLD_ActivateUSER( vSubtask, &vTZCMUSER, vTZCMWIPO );

         if ( GetViewByName( &vTZCMUSER, "TZCMUSER", vSubtask, zLEVEL_TASK ) > 0 &&
              SetCursorFirstEntityByAttr( vTZCMUSER, "CPLR", "ZKey", vTZCMLPLO, "CorrespondingCPLR", "ZKey", "User" ) >= zCURSOR_SET )
         {
            if ( CompareAttributeToInteger( vTZCMUSER, "AccessAuthority", "Authority", 0 ) != 0 )
            {
               nEnable = 1;
            }
         }
      }

      SetOptionState( vSubtask, "CheckIn", zOPTION_STATUS_ENABLED, nEnable );
      SetOptionState( vSubtask, "CheckOut", zOPTION_STATUS_ENABLED, nEnable );
   }

   return( 0 );
}

// Change Siron Report Files while defining an external LPLR.
static zSHORT
zwfnTZCMLPLD_DoChangeReportFiles( zVIEW  vSubtask,
                                  zVIEW  vTempTZCMLPLO,
                                  zPCHAR szReportPathName )
{
   zVIEW  ReturnedReport;                     // View: TZRPSRCO
   zCHAR  szReportName[ 34 ];                 // Name of the report
   zLONG  hReport;                            // FileHandle to test, if *.REP or
                                              // *.XSQ file exists
   zCHAR  szFileName[ 2*zMAX_FILESPEC_LTH + 1 ];  // full qualified *.PRP name
   zCHAR  szPathNameREP[ 2*zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szPathNameXSQ[ 2*zMAX_FILESPEC_LTH + 1 ];
   zSHORT nRC1, nRC;

   for( nRC1 = SetCursorFirstEntity( vTempTZCMLPLO, "W_MetaDef", 0 );
        nRC1 >= zCURSOR_SET;
        nRC1 = SetCursorNextEntity( vTempTZCMLPLO, "W_MetaDef", 0 ) )
   {
      // Get the name of the report and see if there are files *.xsq
      // and *.rep
      GetStringFromAttribute( szReportName, zsizeof( szReportName ), vTempTZCMLPLO, "W_MetaDef", "Name" );
      strcpy( szFileName, szReportPathName);
      strcat( szFileName, szReportName );
      strcat( szFileName, ".PRP" );

      hReport = SysOpenFile( vTempTZCMLPLO, szFileName, COREFILE_EXIST );
      if ( hReport >= 0 )
      {
         nRC = ActivateOI_FromFile( &ReturnedReport, "TZRPSRCO", vTempTZCMLPLO, szFileName, zIGNORE_ATTRIB_ERRORS );
         if ( nRC >= 0 )
         {
            GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTempTZCMLPLO, "LPLR", "PgmSrcDir" );
            strcpy( szPathNameREP, szFileName );
            ofnTZCMWKSO_AppendSlash( szFileName );
            strcat( szFileName, szReportName );
            strcat( szFileName, ".REP" );
            hReport = SysOpenFile( vTempTZCMLPLO, szFileName, COREFILE_EXIST );

            GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTempTZCMLPLO, "LPLR", "ExecDir" );
            strcpy( szPathNameXSQ, szFileName );

            if ( hReport >= 0 )
            {
               // The *.REP file exists
               oTZRPSRCO_ChangeRepFileContents( ReturnedReport, vTempTZCMLPLO, szPathNameREP, szPathNameXSQ,
                                                szReportName, "REP", zCHANGE_REP_MIGRATE_EXTERNAL, vSubtask );
            }

            ofnTZCMWKSO_AppendSlash( szFileName );
            strcat( szFileName, szReportName );
            strcat( szFileName, ".XSQ" );
            hReport = SysOpenFile( vTempTZCMLPLO, szFileName, COREFILE_EXIST );
            if ( hReport >= 0 )
            {
               // The *.XSQ file exists
               oTZRPSRCO_ChangeRepFileContents( ReturnedReport, vTempTZCMLPLO, szPathNameREP, szPathNameXSQ,
                                                szReportName, "XSQ", zCHANGE_REP_MIGRATE_EXTERNAL, vSubtask );
            }
         }
      }
   }

   return( 0 );
}

static void
zwfnTZCMLPLD_LoadMetaAndMerge( zVIEW  vSubtask, zVIEW  vTZCMLPLO,
                               zSHORT nType, zPCHAR szMsgText,
                               zPCHAR szRootEntityName )
{
   zVIEW    vMeta;
   zCHAR    szMsg[ 254 ];
   zCHAR    szMetaName[33];
   zSHORT   nRC;

   for ( nRC = SetCursorFirstEntity( vTZCMLPLO, "W_MetaDef", "" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vTZCMLPLO, "W_MetaDef", "" ) )
   {
      GetStringFromAttribute( szMetaName, zsizeof( szMetaName ), vTZCMLPLO, "W_MetaDef", "Name" );
      strcpy_s( szMsg, zsizeof( szMsg ), "Create Prototype for " );
      strcat_s( szMsg, zsizeof( szMsg ), szMsgText );
      strcat_s( szMsg, zsizeof( szMsg ), ": '" );
      strcat_s( szMsg, zsizeof( szMsg ), szMetaName );
      strcat_s( szMsg, zsizeof( szMsg ), "'." );
      MB_SetMessage( vSubtask, 1, szMsg );

      if ( ActivateMetaOI( vSubtask, &vMeta, vTZCMLPLO, nType, zSINGLE | zLEVEL_TASK | zIGNORE_ATTRIB_ERRORS ) != 1 )
      {
         strcpy_s( szMsg, zsizeof( szMsg ), "Could not load " );
         strcat_s( szMsg, zsizeof( szMsg ), szMsgText );
         strcat_s( szMsg, zsizeof( szMsg ), "'" );
         strcat_s( szMsg, zsizeof( szMsg ), szMetaName );
         strcat_s( szMsg, zsizeof( szMsg ), "'." );
         MessageSend( vSubtask, "PN00219", "Configuration Maintenance", szMsg,
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );
      }
      else
      {
         // Now merge operation prototypes into the LPLR header file.
         MergeGlobalPrototypes( vMeta, szMetaName, szRootEntityName, vTZCMLPLO );
         DropMetaOI( vSubtask, vMeta );
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
//
// OPERATION: zwTZCMLPLD_GenerateZeidonOp_h
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_GenerateZeidonOp_h( zVIEW vSubtask )
{
   zVIEW    vTZCMLPLO_Org;
   zVIEW    vTZCMLPLO;
   zCHAR    szMsg[ 254 ];

   if ( GetViewByName( &vTZCMLPLO_Org, "TZCMLPLO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   // Send a Warning
   strcpy_s( szMsg, zsizeof( szMsg ), "This function creates a new ZeidonOp.h for all \nGlobal and LOD " );
   strcat_s( szMsg, zsizeof( szMsg ), "Operations. \n\n Do you want to continue ?" );
   if ( MessagePrompt( vSubtask, "CM00711", "Configuration Management",
                       szMsg, zBEEP, zBUTTONS_YESNO,
                       zRESPONSE_NO,  0 ) == zRESPONSE_NO )
   {
      return( 0 );
   }

   CreateViewFromViewForTask( &vTZCMLPLO, vTZCMLPLO_Org, 0 );

   // 1. Merge Global Operations
   if ( SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaType", "Type", zREFER_GOPGRP_META, "" ) >= zCURSOR_SET )
   {
      if ( CheckExistenceOfEntity( vTZCMLPLO, "W_MetaDef" ) >= zCURSOR_SET )
         OrderEntityForView( vTZCMLPLO, "W_MetaDef", "Name A" );

      zwfnTZCMLPLD_LoadMetaAndMerge( vSubtask, vTZCMLPLO, zREFER_GOPGRP_META, "Global Operation Group", "GlobalOperationGroup" );
   }

   // 2. Merge LOD Operations
   if ( SetCursorFirstEntityByInteger( vTZCMLPLO, "W_MetaType", "Type", zREFER_LOD_META, "" ) >= zCURSOR_SET )
   {
      if ( CheckExistenceOfEntity( vTZCMLPLO, "W_MetaDef" ) >= zCURSOR_SET )
         OrderEntityForView( vTZCMLPLO, "W_MetaDef", "Name A" );

      zwfnTZCMLPLD_LoadMetaAndMerge( vSubtask, vTZCMLPLO, zREFER_LOD_META, "LOD", "LOD" );
   }

   MessagePrompt( vSubtask, "CM00711", "Configuration Management",
                  "Generate ZeidonOp.h completed successfully.",
                  0, 0, 0, zICON_INFORMATION );

   DropView( vTZCMLPLO );
   MB_SetMessage( vSubtask, 1, "" );

   return( 0 );
} // zwTZCMLPLD_GenerateZeidonOp_h


/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_CheckOutPostBuild
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_CheckOutPostBuild( zVIEW vSubtask )
{
   zVIEW  vTZCMWIPO;

   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) >= 0 )
      zwfnTZCMLPLD_SetDefaultListVaules( vTZCMWIPO );

   SetCtrlState( vSubtask, "Details", zCONTROL_STATUS_ENABLED, FALSE );
   SetCtrlState( vSubtask, "CheckOutSource", zCONTROL_STATUS_ENABLED, FALSE );
   SetCtrlState( vSubtask, "AuditTrail", zCONTROL_STATUS_ENABLED, FALSE );

   return( 0 );
} // zwTZCMLPLD_CheckOutPostBuild

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_RefreshParentWindow
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_RefreshParentWindow( zVIEW vSubtask )
{
   zVIEW vTZCMCOML;
   zVIEW vParentWindow;

   if ( GetViewByName( &vTZCMCOML, "TZCMCOML", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   GetParentWindow( &vParentWindow, vSubtask );
   if ( vParentWindow )
   {
      SetAllSelectStatesForEntity( vTZCMCOML, "Z_MetaDef", FALSE, "" );
      SetSelectStateOfEntity( vTZCMCOML, "Z_MetaDef", TRUE );
      RefreshWindow( vParentWindow );
   }

   return( 0 );
} // zwTZCMLPLD_RefreshParentWindow

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_CompListDropViews
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_CompListDropViews( zVIEW vSubtask )
{
   zVIEW  vView;

   if ( GetViewByName( &vView, "TZCMLPLW", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vView );

   if ( GetViewByName( &vView, "TZCMCOML", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vView );

   return( 0 );
} // zwTZCMLPLD_CompListDropViews

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_SetButtonPos
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_SetButtonPos( zVIEW vSubtask )
{
   zLONG  lSize_X;
   zLONG  lSize_Y;
   zLONG  lCtrlPos_X;

   // Set new position for Buttons
   GetCtrlSize( vSubtask, "LPL_List", &lSize_X, &lSize_Y, TRUE );
   lCtrlPos_X = lSize_X + 12;

   SetCtrlPosition( vSubtask, "OK", lCtrlPos_X, 7, TRUE );
   SetCtrlPosition( vSubtask, "Cancel", lCtrlPos_X, 22, TRUE );
   SetCtrlPosition( vSubtask, "New", lCtrlPos_X, 48, TRUE );
   SetCtrlPosition( vSubtask, "Delete", lCtrlPos_X, 63, TRUE );

   return( 0 );
} // zwTZCMLPLD_SetButtonPos

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_LoadCompListPopup
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_LoadCompListPopup( zVIEW vSubtask )
{
   zVIEW  vTZCMUSER;
   zVIEW  vTZCMLPLO;

   if ( GetViewByName( &vTZCMUSER, "TZCMUSER", vSubtask, zLEVEL_TASK ) > 0 &&
        GetViewByName( &vTZCMLPLO, "TZCMLPLO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      if ( SetCursorFirstEntityByAttr( vTZCMUSER, "CPLR", "ZKey", vTZCMLPLO, "CorrespondingCPLR", "ZKey", "User" ) >= zCURSOR_SET &&
           CompareAttributeToInteger( vTZCMUSER, "AccessAuthority", "Authority", 0 ) != 0 )
      {
         CreateTrackingPopupMenu( vSubtask, "RemovePopup", -1, -1, FALSE, FALSE );
      }
   }

   return( 0 );
} // zwTZCMLPLD_LoadCompListPopup

static zSHORT
zwfnTZCMLPLD_Fill_TZCMRUWK( zVIEW vSubtask, zVIEW vTZCMRUWK, zVIEW vTZCMREPO )
{
   zVIEW   vTZCMWKSO;
   zULONG  ulZKey;
   zSHORT  nRC;

   // added all Repository Users
   nRC = SetCursorFirstEntity( vTZCMREPO, "User", "" );
   while ( nRC >= zCURSOR_SET )
   {
      CreateEntity( vTZCMRUWK, "User", zPOS_AFTER );
      SetAttributeFromAttribute( vTZCMRUWK, "User", "Name", vTZCMREPO, "User", "Name" );
      SetAttributeFromAttribute( vTZCMRUWK, "User", "Password", vTZCMREPO, "User", "Password" );
      SetAttributeFromAttribute( vTZCMRUWK, "User", "ZKey", vTZCMREPO, "User", "ZKey" );
      SetAttributeFromAttribute( vTZCMRUWK, "User", "Desc", vTZCMREPO, "User", "Desc" );
      SetAttributeFromString( vTZCMRUWK, "User", "CPLR_User", "N" );

      nRC = SetCursorNextEntity( vTZCMREPO, "User", "" );
   }

   if ( GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK ) > 0 )
   {
      nRC = SetCursorFirstEntity( vTZCMWKSO, "User", "" );
      while ( nRC >= zCURSOR_SET )
      {
         GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMWKSO, "User", "ZKey" );
         nRC = SetCursorFirstEntityByInteger( vTZCMRUWK, "User", "ZKey", ulZKey, "" );
         if ( nRC >= zCURSOR_SET )
         {
            SetAttributeFromString( vTZCMRUWK, "User", "CPLR_User", "Y" );
         }

         nRC = SetCursorNextEntity( vTZCMWKSO, "User", "" );
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_BuildUserWkList
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_BuildUserWkList( zVIEW vSubtask )
{
   zVIEW    vTZCMREPO;
// zVIEW    vTZCMRUWK;
// zSHORT   nRC;

   if ( GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK ) < 0 )
   {
      if ( oTZCMREPO_ActivateRepository( &vTZCMREPO, vSubtask ) < 0 )
      {
         SetWindowActionBehavior( vSubtask, zWAB_StayOnWindow, 0, 0 );
         return( -1 );
      }
      SetNameForView( vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );
   }

   return( 0 );
} // zwTZCMLPLD_BuildUserWkList


/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_CancelUser
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_CancelUser( zVIEW vSubtask )
{
   zVIEW  vView;

   if ( GetViewByName( &vView, "TZCMRUWK", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vView );

   if ( GetViewByName( &vView, "TZCMREPO", vSubtask, zLEVEL_TASK ) > 0 )
      DropObjectInstance( vView );

   return( 0 );
} // zwTZCMLPLD_CancelUser

static zSHORT
zwfnTZCMLPLD_ExcludeUser( zVIEW vTZCMRUWK, zVIEW vTZCMWKSO, zVIEW vTZCMREPO )
{
   zULONG   ulZKey;
   zULONG   ulWKS_ZKey;
   zSHORT   nRC;

   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMWKSO, "User", "ZKey" );
   GetIntegerFromAttribute( (zPLONG) &ulWKS_ZKey, vTZCMWKSO, "RepositoryClient", "ZKey" );

   nRC = SetCursorFirstEntityByInteger( vTZCMRUWK, "User", "ZKey", ulZKey, "" );
   if ( nRC != zCURSOR_SET ||
        CompareAttributeToString( vTZCMRUWK, "User", "CPLR_User", "N" ) == 0 )
   {
      ExcludeEntity( vTZCMWKSO, "User", zREPOS_PREV );

      if ( SetCursorFirstEntityByInteger( vTZCMREPO, "User", "ZKey", ulZKey, "" ) >= zCURSOR_SET &&
           SetCursorFirstEntityByInteger( vTZCMREPO, "UserRepositoryClient", "ZKey", (zLONG) ulWKS_ZKey, "" ) >= zCURSOR_SET )
      {
         ExcludeEntity( vTZCMREPO, "UserRepositoryClient", zREPOS_PREV );
      }
   }

   return( 0 );
}

static zSHORT
zwfnTZCMLPLD_IncludeUser( zVIEW vTZCMRUWK, zVIEW vTempWKSO, zVIEW vTZCMREPO )
{
   zULONG   ulZKey;
   zSHORT   nRC;

   GetIntegerFromAttribute( (zPLONG) &ulZKey, vTZCMRUWK, "User", "ZKey" );
   nRC = SetCursorFirstEntityByInteger( vTempWKSO, "User", "ZKey", ulZKey, "" );
   if ( nRC < zCURSOR_SET )
   {
      if ( SetCursorFirstEntityByInteger( vTZCMREPO, "User", "ZKey", ulZKey, "" ) >= zCURSOR_SET )
      {
         IncludeSubobjectFromSubobject( vTempWKSO, "User", vTZCMREPO, "User", zPOS_AFTER );

         if ( SetCursorFirstEntityByAttr( vTZCMREPO, "UserRepositoryClient", "ZKey", vTZCMREPO, "RepositoryClient", "ZKey", "" ) >= zCURSOR_SET )
         {
            RelinkInstanceToInstance( vTZCMREPO, "UserRepositoryClient", vTZCMREPO, "RepositoryClient" );
         }
      }
   }

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_OKUser
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_OKUser( zVIEW vSubtask )
{
   zVIEW    vTZCMREPO;
   zVIEW    vTZCMWKSO;
   zVIEW    vTZCMRUWK;
   zVIEW    vTempWKSO;
   zSHORT   nRC;

   GetViewByName( &vTZCMRUWK, "TZCMRUWK", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMWKSO, "TZCMWKSO", vSubtask, zLEVEL_TASK );
   GetViewByName( &vTZCMREPO, "TZCMREPO", vSubtask, zLEVEL_TASK );

   // First delete the entries.
   nRC = SetCursorFirstEntity( vTZCMWKSO, "User", "" );
   while ( nRC == zCURSOR_SET )
   {
      zwfnTZCMLPLD_ExcludeUser( vTZCMRUWK, vTZCMWKSO, vTZCMREPO );

      nRC = SetCursorNextEntity( vTZCMWKSO, "User", "" );
   }

   CreateViewFromViewForTask( &vTempWKSO, vTZCMWKSO, 0 );

   // Now add or update the rest of the entries.
   nRC = SetCursorFirstEntity( vTZCMRUWK, "User", "" );
   while ( nRC == zCURSOR_SET )
   {
      if ( CompareAttributeToString( vTZCMRUWK, "User", "CPLR_User", "Y" ) == 0 )
         zwfnTZCMLPLD_IncludeUser( vTZCMRUWK, vTempWKSO, vTZCMREPO );

      nRC = SetCursorNextEntity( vTZCMRUWK, "User", "" );
   }

   oTZCMWKSO_CommitWorkstation( vTZCMWKSO );

   if ( ObjectInstanceUpdatedFromFile( vTZCMREPO ) == 1 )
      CommitObjectInstance( vTZCMREPO );

   DropObjectInstance( vTZCMRUWK );
   DropObjectInstance( vTZCMREPO );
   DropView( vTempWKSO );

   return( 0 );
} // zwTZCMLPLD_OKUser

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_SetCtrlPos_Users
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_SetCtrlPos_Users( zVIEW vSubtask )
{
   zLONG  lSize_X;
   zLONG  lSize_Y;
   zLONG  lCtrlPos_Y;

   GetCtrlSize( vSubtask, "tgUser", &lSize_X, &lSize_Y, TRUE );

   // Set new position for Buttons
   lCtrlPos_Y = lSize_Y + 5;

   if ( lSize_X < 100 )
      lSize_X = 100;

   SetCtrlPosition( vSubtask, "pbOK", lSize_X - 45 - 52, lCtrlPos_Y, TRUE );
   SetCtrlPosition( vSubtask, "pbCancel", lSize_X - 45, lCtrlPos_Y, TRUE );

   return( 0 );
} // zwTZCMLPLD_SetCtrlPos_Users

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_CheckUser
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_CheckUser( zVIEW vSubtask )
{
   zVIEW  vTZCMRUWK;
   zVIEW  vTZCMWIPO;
   zLONG  lRow = -1;
   zLONG  lColumn = -1;

   if ( GetViewByName( &vTZCMWIPO, "TZCMWIPO", vSubtask, zLEVEL_TASK ) < 0 )
      return( -1 );

   if ( GetViewByName( &vTZCMRUWK, "TZCMRUWK", vSubtask, zLEVEL_TASK ) > 0 && CheckExistenceOfEntity( vTZCMRUWK, "User" ) >= zCURSOR_SET )
   {

      TG_GetActiveCell( vSubtask, "tgUser", &lRow, &lColumn );

      // if Click on CheckBox
      if ( lColumn == 0 )
      {
         if ( CompareAttributeToString( vTZCMRUWK, "User", "CPLR_User", "N" ) == 0 )
         {
            if ( CompareAttributeToAttribute( vTZCMWIPO, "ROOT", "UserName", vTZCMRUWK, "User", "Name" ) == 0 )
            {
               MessageSend( vSubtask, "CM00213", "Configuration Management",
                            "Unable to Unregister Signed On User",
                            zMSGQ_OBJECT_CONSTRAINT_ERROR, zBEEP );

               TG_SetCellData( vSubtask, "tgUser", "Y", lRow, 0 );
            }
         }
      }
   }

   return( 0 );
} // zwTZCMLPLD_CheckUser

/////////////////////////////////////////////////////////////////////////////
//
//    OPERATION: zwTZCMLPLD_CheckInSetTabSize
//
/////////////////////////////////////////////////////////////////////////////
zOPER_EXPORT zSHORT /*DIALOG */  OPERATION
zwTZCMLPLD_CheckInSetTabSize( zVIEW vSubtask )
{
   zLONG  lWindowSize_X;
   zLONG  lCtrlSize_X;
   zLONG  lCtrlSize_Y;
   zLONG  lCtrlPos_X;
   zLONG  lTabCtrlSize_X;
   zLONG  lTemp;
   zCHAR  szControl[ 33 ];

   // Set new size for Tab Control
   GetCtrlSize( vSubtask, 0, &lWindowSize_X, &lTemp, TRUE );
   GetCtrlSize( vSubtask, "Tab", &lCtrlSize_X, &lCtrlSize_Y, TRUE );
   GetCtrlPosition( vSubtask, "Tab", &lCtrlPos_X, &lTemp, TRUE );

   lTabCtrlSize_X = lWindowSize_X - lCtrlPos_X - 70;
   if ( lTabCtrlSize_X < 275 )
      lTabCtrlSize_X = 275;

   SetCtrlSize( vSubtask, "Tab", lTabCtrlSize_X, lCtrlSize_Y, TRUE );

   // Set new size for Tab SubControl
   GetCtrlSize( vSubtask, "tcComponent", &lTemp, &lCtrlSize_Y, TRUE );
   lTabCtrlSize_X = lTabCtrlSize_X - 5;
   SetCtrlSize( vSubtask, "tcComponent", lTabCtrlSize_X, lCtrlSize_Y, TRUE );

   GetCtrlSize( vSubtask, "tcComments", &lTemp, &lCtrlSize_Y, TRUE );
   SetCtrlSize( vSubtask, "tcComments", lTabCtrlSize_X, lCtrlSize_Y, TRUE );
   SetCtrlSize( vSubtask, "tcOptions", lTabCtrlSize_X, lCtrlSize_Y, TRUE );
   SetCtrlSize( vSubtask, "tcDisplay", lTabCtrlSize_X, lCtrlSize_Y, TRUE );

   // Save current Control with Focus
   GetCtrlWithFocus( vSubtask, szControl );

   // if 1. Tab active, set new size for Controls from 1.Tab SubContol
   if ( SetFocusToCtrl( vSubtask, "ShortDescEdit" ) >= 0 )
   {
      GetCtrlSize( vSubtask, "edComments", &lCtrlSize_X, &lCtrlSize_Y, TRUE );
      lCtrlSize_X = lTabCtrlSize_X - lCtrlPos_X - 45;
      SetCtrlSize( vSubtask, "ShortDescEdit", lCtrlSize_X, 14, TRUE );
      SetCtrlSize( vSubtask, "DescEdit", lCtrlSize_X, 53, TRUE );

      lCtrlPos_X = lTabCtrlSize_X - 79;
      SetCtrlPosition( vSubtask, "pbComment", lCtrlPos_X, 72, TRUE );
      SetCtrlPosition( vSubtask, "pbImportFile", lCtrlPos_X - 78, 72, TRUE );
   }

   // Set new position for Buttons
   GetCtrlSize( vSubtask, "Tab", &lCtrlSize_X, &lTemp, TRUE );
   lCtrlPos_X = lCtrlSize_X + 10;

   SetCtrlPosition( vSubtask, "Close", lCtrlPos_X, 18, TRUE );
   SetCtrlPosition( vSubtask, "CheckIn", lCtrlPos_X, 39, TRUE );
   SetCtrlPosition( vSubtask, "CheckInAll", lCtrlPos_X, 54, TRUE );

   SetFocusToCtrl( vSubtask, szControl );

   return( 0 );
} // zwTZCMLPLD_CheckInSetTabSize

#ifdef __cplusplus
}
#endif
