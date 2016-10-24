//KZOEMIAA.H - Structures for internal meta def's

/*
CHANGE LOG

2001.08.07  DGC  10b
   Doubled the valid length of a mutex name.

2001.07.31  HH
   Added Entity version updated flags.

2001.05.30  DGC  10b
   Added stuff for NetA changes.

2001.04.06 DGC
   Added stuff for Entity keys.

2001.03.30 HH
   Change NetConnectionStruct to fix multithreading problem in kzoeneta.

2001.02.08 DGC
   Changed cursor listener stuff to use a linked list.

2001.01.28 HH
   Added CursorListener to ViewStruct.

2000.12.07 DGC  Z2000
   Added a switch to keep from calling message functions recursively.

2000.11.08 RG   Z2000
   - Added Hartmut's changes again.
   - ppvConn --> pvConn

2000.10.03 DGC  10b
   Added szContextName to struct ViewAttrListStruct.

2000.08.18 DGC  10b
   Backed out Hartmut's changes.

2000.07.18 HH
   Hold connection.

2000.04.27 DGC  10b
   Added code to allow user to query mutex status.

2000.03.07  DGC  10b
   Added a flag to EntityInstanceStruct to handle a bug in AcceptSubobject().

2000.03.07  DKS  10b
   Doubled length of ViewNameStruct's szName to 64 + 1.

1999.11.16  US   10a
   FreespaceStruct and DataHeaderStruct changed according to changes in
   Module kzoemmaa.c

1999.10.08  DGC  10a
   Added bFlagDropView to ViewStruct.

1999.06.03  DGC  10a
   Changed bDBHProcessed to bDBHCreated, etc.

1999.06.03  DGC  10a
   Added tracing flags.

1999.04.19  DGC  10a  ApplA
   Changed mutex logic to use use-counts.
   Added info to TaskStruct.

1999.04.19  RS
   Comment lines required for Rose.

1999.02.12  DGC
   Started adding (and removing) stuff for attribute flags.
*/

// Don't remove the following commentlines. They are required for Rose.
//#include <kzoep1aa.h> //required for Rose
//#include <kzoemeaa.h> //required for Rose
//#include <kzoetdaa.h> //required for Rose
//#include <kzoeinco.h> //required for Rose

//#define ALLOC_FREE_TRACE 128000
//#define LOAD_FREE_TRACE  128000

// If __RECLAIM__ is defined then we'll try to reclaim dead entity instances
// after certain operations e.g. DeleteEntity().
#define __RECLAIM__

// Reclaim limit:  after an operation such as DeleteEntity we'll call
// fnReclaimHiddenInstances only if the number of current hidden instances
// exceeds the limit.
#ifdef ALLOC_FREE_TRACE
#define __RECLAIM_LIMIT__ 0
#else
#define __RECLAIM_LIMIT__ 20
#endif

// Freespace link structure
// NOTE: this structure exists for each freespace chunk in a dataspace
//       area. In addition, each used space contains the
//       Header address in lpNextFreeChunk as well as the TableID and
//       nFreeLth integer fields prior to the used address for
//       validating freespace requests.
//       (US 1999/10/20) the order of the variables has been altered to get
//       nTableID first as usual. Secondly:  a pointer at the end of the
//       struct causes every compiler to ensure that the struct ends on a
//       boundary border.
struct FreespaceStruct
{
   zSHORT                  nTableID;
   zSHORT                  nPrevTableID;
   zSHORT                  nUsedTableID;     // ID of used memory block.
#ifdef ALLOC_FREE_TRACE
   zULONG                  ulDebugID;        // Sequential debug ID
#endif
   zULONG                  ulFreeLth;
   zPVOID                  hFreespace;       // Handle for the freespace struct.
   LPFREESPACE             hNextFreespace;
};

// Dataspace Header definition
struct DataHeaderStruct
{
   zSHORT                  nTableID;
// zLONG                   lTaskID;
   LPTASK                  hTask;
   zLONG                   hDataHandle;
   zULONG                  ulUseableSize;       // initial useable size
   zULONG                  ulCntUsedEntries;    // used memory spaces
   zULONG                  ulUsedSpace;         // total amount of used memory
   zULONG                  ulCntFreeSpaces;     // count of FreeSpaces in chain
   zULONG                  ulMaxEmptyBlockSize; // Max size of free block
   zULONG                  ulFreedMemSize;      // Amount of Memory that is freed
                                                // but not yet in Free memory chain
   zLONG                   lNextDataHandle;
   LPDATAHEADER            hNextDataHeader;
   LPDATAHEADER            hPrevDataHeader;
   FreespaceRecord         Freespace;
};

struct MutexStruct
{
   zSHORT               nTableID;
   LPMUTEX              hNextMutex;
   zCHAR                szName[ zZEIDON_NAME_LTH * 2 + 1 ];
   zLONG                lNameHash;
   zSHORT               nLockCount;    // # of concurrent locks by process
   LPMUTEX              hSysMutex;
   zLONG                lLockedTaskID; // ID of task that currently has mutex locked.
   unsigned int         bWaiting : 1;
   zLONG                lProcessID;

   MutexInfo            Info;          // OS-dependent data.  MUST BE LAST!
};

struct DebugChangeStruct
{
   zSHORT               nTableID;
   LPDEBUGCHANGE        hNextDebugChange;
   LPVIEWATTRIB         hViewAttrib;
   LPVIEWOD             hViewOD;
   LPENTITYINSTANCE     hEntityInstance;
   zLONG                lLastValue;
   zULONG               ulLth;
   unsigned int         bCompare    : 1,
                        bInProgress : 1;
};

#ifndef _NOANCHOR
// Anchor block definition
struct AnchorStruct
{
   DataHeaderRecord     DataHeader;
   FreespaceRecord      Freespace;
   zSHORT               nTableID;
   zSHORT               nStatus;

#ifdef ALLOC_FREE_TRACE

   zBOOL  bTraceMem;
   zPVOID pvMemId[ ALLOC_FREE_TRACE ];
   zLONG  lMemSize[ ALLOC_FREE_TRACE ];
   zPVOID pvMemTask[ ALLOC_FREE_TRACE ];
   zLONG  lMemMax;
   zULONG ulAllocCnt;

#endif // #ifdef ALLOC_FREE_TRACE

#ifdef LOAD_FREE_TRACE

   zBOOL  bTraceLib
   zPVOID pvLibId[ LOAD_FREE_TRACE ];
   zCHAR  szLibName[ LOAD_FREE_TRACE ][ 9 ];
   zPVOID pvLibTask[ LOAD_FREE_TRACE ];
   zLONG  lLibMax;
   zULONG ulLibraryCnt;

#endif // #ifdef LOAD_FREE_TRACE

// zLONG                lMainTaskID;
   zLONG                lTaskAllocSize;
   zLONG                lHab;
   zLONG                lOE_hMainWnd;
   zLONG                lOE_hListWnd;
   zLONG                lOE_Msg;
   LPTASK               hMainTask;
   LPAPP                hSystemApp;
   LPDATAHEADER         hMainFirstDataHeader; // first Dataspace for main task
   LPPROCESS            hFirstProcess;
   LPNETWORK            hFirstNetwork;
   LPAPP                hFirstApp;
   LPTASK               hFirstTask;
   zSHORT               nMemoryTraceThreshold;
   zSHORT               nMemoryCeiling;
   zCHAR                szZeidonLocal[ zMAX_FILENAME_LTH + 1 ];
   zCHAR                szZeidonBin[ zMAX_FILENAME_LTH + 1 ];
   zCHAR                szZeidonSys[ zMAX_FILENAME_LTH + 1 ];
   zCHAR                szZeidonLoc[ zMAX_FILENAME_LTH + 1 ];
   zCHAR                szZeidonShr[ zMAX_FILENAME_LTH + 1 ];
   zCHAR                szUserID[ zZEIDON_NAME_LTH + 1 ];
   zCHAR                szPassword[ zZEIDON_NAME_LTH + 1 ];
   LPVIEWNAME           hFirstViewName;   // first named view for System
   zUSHORT              nBrowseTaskListCounter;
   unsigned int         bShowTaskID           : 1,
                        bTraceCnt             : 1,
                        bDropEngineIfNoTasks  : 1,
                        bDebugLeak            : 1,
                        bDeleteTaskInProgress : 1;

   // Following long is made 'volatile' because it's used in locking.
   // The value of the long must be re-loaded every time it gets used.
   volatile zLONG       hTaskChainWriteLockTaskID;

   // OS-specific data.
   AnchorOS_Record      OS_Data;

   // When creating a thread task we may need to know the parent task before
   // the thread task is fully initialized (needed at the moment by Win32
   // shared memory allocation).
   LPTASK               lpParentTask;

   LPINTERNATIONAL      hInternational;
   LPMUTEX              hFirstSysMutex;
   LPDEBUGCHANGE        hFirstDebugChange;
   TracingFlagsRecord   TraceFlags;
};
#endif

// Anchor block status states
#define   AnchorUninitialized  0
#define   AnchorInitialized   10
#define   AnchorCorrupt       20

// File Header definition
struct FileHeaderStruct
{
   zCHAR                chTypeIndicator[ 6 ];
   zCHAR                szZeidon[ 10 ];
   zCHAR                szFileName[ zZEIDON_NAME_LTH + 1 ];
   zCHAR                szObjectType[ zZEIDON_NAME_LTH + 1 ];
   zCHAR                szDate[ 11 ];
   zCHAR                szTime[ 9 ];
   zCHAR                szRelease[ 9 ];
   zSHORT               nEntityInstanceRecordSize;
   zLONG                lOI_EntityTableSize;
   zLONG                lDataspaceSize;
};

// Internal DateTime structure
struct DateTimeInternalStruct
{
   zULONG   ulDateMinutes;    // Minutes since year zero
   zUSHORT  usTSeconds;       // Thousandths of seconds
};
//typedef struct DateTimeInternalStruct DateTimeInternalRecord;

// Following defines a function that is to be called by Core to set the server
// in a LAD right before activating or commiting an OI.
typedef zSHORT (POPERATION PFN_APPLA_LAD_OI)( zVIEW, zVIEW, zPCHAR, zPCHAR,
                                              zVIEW, zULONG, zULONG, zPVOID );

// Following defines a function that is to be called by Core to set the server
// in a LAD right before calling an operation/transformation.
typedef zSHORT (POPERATION PFN_APPLA_LAD_OPER)( zVIEW, zVIEW, zPCHAR, zPCHAR,
                                                zPCHAR, zULONG, zPVOID );

// Process Structure
struct ProcessStruct
{
   zSHORT               nTableID;
   LPPROCESS            hNextProcess;
   zLONG                lProcessID;        // System Dependent Process Identifier
};

// Task Structure
struct TaskStruct
{
   zSHORT               nTableID;
   LPTASK               hNextTask;
   LPSUBTASK            hFirstSubtask;
   LPAPP                hApp;              // Application owning this task
   zLONG                lHab;              // System Dependent Task Block
// LPPROCESS            hProcess;          // Most recent process associated with this task
// zLONG                lTaskID;           // System Dependent Task Identifier
   zLONG                lOrigMainWnd;      // Client task main window (OS2)
   zLONG                hMainWnd;          // Client task main window
   zUSHORT              uAppOE_Msg;        // Task main window user msg
   zVIEW                vWebSubtask;       // View defining the WEB subtask
   zPCHAR               hUserID;           // Task UserID
   zPCHAR               hPassword;         // Task Password
   zPCHAR               hDBUserID;         // Task database UserID
   zPCHAR               hDBPassword;       // Task database Password
   zLONG                lOE_Return;        // Object Engine Parameter2
   zLONG                hFirstDataHandle;  // Handle for First Dataspace
   zSHORT               nRecurse;          // Validates error calls.
   zSHORT               nOperIdx;          // Operation call index
   zSHORT               nOper[ 16 ];       // Operation call table
   zSHORT               nDBHandlerTraceLevel; // Trace level for db-handlers
   LPDATAHEADER         hFirstDataHeader;  // First Dataspace for Obj Data
   LPVIEWOI             hFirstViewOI;      // First View Object Instance
   LPTASKAPP            hFirstTaskApp;     // First Task App area
   zVIEW                hFirstView;        // First view for task
   LPVIEWNAME           hFirstViewName;    // First named view for task
   zPVOID               hFirstAppMem;      // Appl allocated memory chain
   LPOPENFILE           hFirstOpenFile;    // First File Open Entry
   LPLIBRARY            hFirstLibrary;     // First Library
   LPTASKDOMAIN         hFirstTaskDomain;  // First Domain Library
   LPTASKOPER           hFirstTaskOperation; // First OEA operation
   LPTASKDBHANDLER      hFirstTaskDBHandler; // First DBHandler
   LPTASKGKHANDLER      hFirstTaskGKHandler; // First GKHandler
   zPCHAR               hCommand;          // Command line input
   zPCHAR               hCountBuf;         // Operation call counting buffer
   LPMUTEX              hFirstMutex;
   zULONG               ulCurrentEntityKey;// Used to generate entity kyes.
   zULONG               ulDebugChgCount;   // Used by DEBUGCHG code.
   zULONG               ulTrackTaskMemory;

   // ApplA info.
   PFN_APPLA_LAD_OI     pfnSetLAD_ForOI;
   PFN_APPLA_LAD_OPER   pfnSetLAD_ForOper;

   zCHAR                szTimeStamp[ 20 ]; // WEB TimeStamp / Server TimeStamp
   zCHAR                szSessionId[ 50 ]; // Tomcat Session ID
   zCHAR                szUserId[ 34 ];    // User Id associated with Task (set by application)
   zCHAR                szDialog[ zZEIDON_NAME_LTH + 1 ]; // Dialog name
   zCHAR                szTaskTitle[ 128 ];// Task Title
   zPVOID               pcsCriticalSection;
   unsigned int         bAudit    : 1,     // Operation auditing enabled
                        bDebug    : 1,     // Debug level parameter checking
                        bTrace    : 1,     // Task Tracing enabled
                        bDisable  : 1,     // Task Disabled
                        bCount    : 1,     // Operation counting active
                        bShutdown : 1,     // Shutdown in progress
                        bServer   : 1,     // 1 while task is handling a client.
                        bThreadTask : 1,   // 1 if thread is Zeidon task.
                        bPessimisticLockingSet : 1, // See KZOEOIAA.C for info.
                        bDeleteWnd : 1,    // hMainWnd created by OE - OE must delete
                        bTransientTask : 1, // Task is a transient task.
                        bTaskInUseByWeb : 1, // Web is using the task
                        bWebTrace : 1,     // Web Tracing enabled
                        bApplicationTask : 1, // Task alive as long as app
                        bLoadAllocLimit : 1, // Task memory allocation limit reached
                        bOE_TaskShutdown : 1; // OE Task being shut down
};

// Task messaging requests
#define                 TASKREQ_ALLOC     1
#define                 TASKREQ_SHARE     2
#define                 TASKREQ_SHAREALL  3
#define                 TASKREQ_FREE      4
#define                 TASKREQ_FREEALL   5
#define                 TASKREQ_FREELIB   6
#define                 TASKREQ_FREEMUTEX 7

// Library Structure
struct LibraryStruct
{
   zSHORT               nTableID;
   LPLIBRARY            hNextLibrary;
   zCHAR                szName[ zMAX_FILENAME_LTH + 1 ];
   zLONG                hLibrary;       // system handle, not an OE handle
   zLONG                lFlag;
   zLONG                lProcessID;     // permit quick recognition of
                                        // whether library is for proper
                                        // process
   zULONG               ulUseCnt;       // Number of times lib has been
};                                      // loaded for the process.

// DGC 6/24/97
// Removed task share stuff because all memory is always shared.  I'm leaving
// the structure definition here so that if we ever need it...
#if 0
// Task Share Structure - for memory data sharing
struct TaskShareStruct
{
   zSHORT            nTableID;
   LPTASKSHARE       hNextTaskShare;
   LPTASK            hSharingTask;
   LPTASK            hSharedTask;
};
#endif

// Subtask Structure
struct SubtaskStruct
{
   zSHORT            nTableID;
   LPSUBTASK         hNextSubtask;
   LPTASK            hTask;
   LPAPP             hApp;            // Application owning this task
   zVIEW             hSubtaskView;    // View defining the subtask
   LPVIEWNAME        hFirstViewName;  // View visible to subtask
};

// DBHandler Structure
struct DBHandlerStruct
{
   zSHORT            nTableID;
   LPDBHANDLER       hNextDBHandler;
   LPAPP             hApp;           // App owning DBHandler
   zCHAR             cClass;         // Hierarchical, Network, etc
   zCHAR             szName[ zZEIDON_NAME_LTH + 1 ]; // DB Handler Library name
};

// Task DBHandler Structure
struct TaskDBHandlerStruct
{
   zSHORT            nTableID;
   LPTASKDBHANDLER   hNextTaskDBHandler;
   LPDBHANDLER       hDBHandler;
   LPLIBRARY         hLibrary;
   zPDBHOPER         pfDBHandlerOper;
   zPVOID            lpConnection;
   zLONG             lProcessID;
   unsigned int      bTranStarted : 1; // Tran started for current task/DB.
};

// GKHandler Structure
struct GKHandlerStruct
{
   zSHORT            nTableID;
   LPGKHANDLER       hNextGKHandler;
   LPAPP             hApp;           // App owning GKHandler
   zCHAR             szName[ zZEIDON_NAME_LTH + 1 ]; // GK Handler Library name
};

// Task GKHandler Structure
struct TaskGKHandlerStruct
{
   zSHORT            nTableID;
   LPTASKGKHANDLER   hNextTaskGKHandler;
   LPGKHANDLER       hGKHandler;
   LPLIBRARY         hLibrary;
   zPGKHOPER         pfGKHandlerOper;
   zPVOID            lpConnection;
   zLONG             lProcessID;
};

// Task Domain Structure
struct TaskDomainStruct
{
   zSHORT            nTableID;
   LPTASKDOMAIN      hNextTaskDomainForTask;
   LPTASKDOMAIN      hNextTaskDomainForDomain;
   LPTASKDOMAIN      hPrevTaskDomainForDomain;
   LPDOMAIN          hDomain;
   LPTASK            hTask;
   zLONG             lProcessID;
   LPLIBRARY         hLibrary;
   zPDMOPER          pfDomainOper;
};

// Task App Structure
struct TaskAppStruct
{
   zSHORT            nTableID;
   LPTASKAPP         hNextTaskApp;
   LPAPP             hApp;
   LPTASK            hTask;
   zLONG             lProcessID;
   LPLIBRARY         hLibrary;
   LPMQINTERFACE     hMQInterface;    // Used in Interfacing w/ MQ
};

// View Object Instance Structure
struct ViewOI_Struct
{
   zSHORT               nTableID;
   LPVIEWOI             hNextViewOI;
   LPVIEWOD             hViewOD;
   LPVIEWCSR            hFirstViewCsr;
   LPTASK               hTask;                   // Owning task
   LPTASK               hAllocTask;              // Data Allocation task
   zSHORT               nVersionedInstances;
   zSHORT               nHiddenCount;            // For space reclamation
   LPENTITYINSTANCE     hRootEntityInstance;     // Root of OI
   DateTimeInternalRecord DateTime;               // when the oi was built
   unsigned int         bMultipleRootLevels    : 1, // View has mult. roots.
                        bRootOnly              : 1, // OI activated root only
                        bReadOnly              : 1, // OI is readonly
                        bEnqueued              : 1, // OI is enqueued
                        bUpdated               : 1, // OI has been updated
                        bUpdatedFile           : 1, // Up'd after Act/file
                        bDropConstraintInvoked : 1,
                        bIsLocked              : 1; // Currently has pessimistic lock.

   // Following information is used by the locking apparatus.
   zVIEW                vOriginalOI;         // Copy of OI after it's loaded.
   zVIEW                vQualOI;             // Copy of last qualification OI
   zLONG                lActivateControl;    // Activate flags
   zLONG                lTag;                // OI Tag.

   zCHAR                szRelease[ 9 ];          // OI release
};

// View Structure
// the view structure contains a pointer to a view cursor structure and
// and optionally subtask structure
//
// If bOrigView is 1 then the view is the "original" view as part of
// optimistic locking.  lpMainOI points to the "main" OI.
typedef struct CursorListenerStruct CursorListenerRecord;
typedef CursorListenerRecord *LPCURSORLISTENER;
struct CursorListenerStruct
{
   LPCURSORLISTENER     hNextCursorListener;
   CURSORLISTENER       lpfnCursorListener;
   zPVOID               pvListenerInstance;
   zLONG                lListenerProcess;
   LPTASK               hListenerTask;

};

struct ViewStruct
{
   zSHORT               nTableID;
   zVIEW                hNextView;
   LPVIEWOD             hViewOD;     // Object def associated with view
   LPVIEWCSR            hViewCsr;    // Instance cursors for view
   LPTASK               hTask;       // Task Owning the View
   LPSUBTASK            hSubtask;    // Only set if view is subtask view
   zSHORT               nViewNames;  // Number of names given the view
   zSHORT               nAutoDropNames;  // Number of names which can be
                                         // dropped when a subtask is
                                         // dropped - usually 0!
   LPVIEWOI             hMainOI;     // See note above.
   unsigned int         bTaskNamed        : 1, // V named at task level
                        bApplicationNamed : 1, // V named at App Lvl
                        bSystemNamed      : 1, // V named at System Level
                        bApplicationView  : 1, // V is part of app obj
                        bInvalidMainOI    : 1, // hMainOI is invalid
                        bViewLocked       : 1, // V not deleted
                        bReadOnly         : 1, // V is read only
                        bOrigView         : 1, // See note above.
                        bQualView         : 1, // See note above.
                        bTraceDropView    : 1, // If true trace msg when dropped.
                        bFlagDropView     : 1; // If true show msg when dropped.
   LPCURSORLISTENER     hFirstCursorListener;
};

// View Name Structure
// the view structure contains a pointer to a view cursor structure and
// a subtask structure
struct ViewNameStruct
{
   zSHORT               nTableID;
   zVIEW                hView;           // View which is named
   LPVIEWNAME           hNextViewName;   // Next name in chain
   zCHAR                szName[ 2 * zZEIDON_NAME_LTH + 1 ]; // Name for view
};

// View Cursor Structure
// Since the View cursor structure and view entity structure is combined and
// sub-allocated together, their size should be a multiple of 4.
struct ViewCsrStruct
{
   zSHORT               nTableID;
   LPVIEWCSR            hNextViewCsr;
   zVIEW                hView;                   // View for view csr
   LPVIEWOI             hViewOI;
   LPVIEWENTITYCSR      hFirstOD_EntityCsr;
   LPVIEWENTITYCSR      hRootViewEntityCsr;
   LPENTITYINSTANCE     hHierRootEntityInstance; // Hier start position
   LPENTITYINSTANCE     hHierEntityInstance;     // Hier curr  position
   LPVIEWSUBOBJECT      hFirstViewSubobject;
   zUSHORT              uEntities;  // Number of Entity cursors in view
   zSHORT               nCurrentSelectSet; // Current Select Set

   // hViewParentEntityInstance set for subobject views below the OI root
   LPENTITYINSTANCE     hViewParentEntityInstance;  // Parent of view
   LPSELECTEDINSTANCE   hFirstSelectedInstance;  // Select Instance
};

#define NULL_CSR  0
#define UNSET_CSR (LPENTITYINSTANCE) 1

// View Entity Csr Structure
// Since the View structure and view entity structure is combined and
// sub-allocated together, their size should be a multiple of 4.
struct ViewEntityCsrStruct
{
   zSHORT               nTableID;
   LPVIEWENTITYCSR      hNextHier;
   LPVIEWENTITYCSR      hPrevHier;
   LPVIEWENTITYCSR      hParent;
   LPVIEWENTITY         hViewEntity;
   LPVIEWCSR            hViewCsr;
   zSHORT               nLevel;
   zSHORT               nHierNbr;
   LPENTITYINSTANCE     hEntityInstance;
};

// Selected Instance Struct
struct SelectedInstanceStruct
{
   zSHORT               nTableID;
   LPSELECTEDINSTANCE   hNextSelectedInstance;
   zSHORT               nSelectSet;
   LPVIEWENTITY         hViewEntity;
   LPENTITYINSTANCE     xEntityInstance;  // NOTE--------------
                                          // This is used for pointer
                                          // comparison purposes only!!!!
                                          // Do not use this item to
                                          // point at an entity instance
};

// ViewSubobjectStruct  for recursive subobject views
struct ViewSubobjectStruct
{
   zSHORT               nTableID;
   LPVIEWSUBOBJECT      hNextViewSubobject;
   LPVIEWSUBOBJECT      hPrevViewSubobject;
   LPVIEWENTITYCSR      hViewRootParentCsr;  // Parent Csr to new root
   LPVIEWENTITYCSR      hRootCsr;        // subobject root cursor
   zSHORT               nRootHierNbr;     // Hier number of root csr
   LPVIEWENTITYCSR      hLastDescCsr;    // last descendent cursor
   zSHORT               nLastDescHierNbr; // Hier number of last desc
   LPENTITYINSTANCE     hViewParentEntityInstance;  // Parent of view

   // hRootEntityInstance is set for all subordinate subobject roots
   // at the point in time a subobject view is established which
   // folds up the structure on a recursive view entity type. This
   // is done so the cursor can be re-established on a reset.
   LPENTITYINSTANCE     hRootEntityInstance;  // Root at set subobj

   // recursive subobject info
   zSHORT               nLevelChg;        // Recursive level adjustment
   LPVIEWENTITY         hRecursViewEntity; // Subobject recurs view ent
   LPVIEWENTITYCSR      hRecursViewEntityCsr; // Subobject recurs ent csr
   LPENTITYINSTANCE     hRecursParentEntityInstance;  // recurs parent
};

struct EntityInstanceInd
{
   unsigned int         bHangingEntity : 1, // Entity is a hanging entity.
                        bCreated       : 1, // Has been created
                        bUpdated       : 1, // Has been updated
                        bDeleted       : 1, // Has been deleted
                        bExcluded      : 1, // Has been excluded
                        bIncluded      : 1, // Has been included
                        bRecordOwner   : 1, // Used during ComOI to stream.
                        xRelOwner      : 1, // Owner of shared relationship
                        bPrevVersion   : 1, // Instance is a prev version
                        bPrevVsnRoot   : 1, // Instance is a prev vsn Root
                        bHidden        : 1, // Instance is hidden from csrs
                        bTemporal      : 1, // Instance is temp entity

                        // Used during WriteOI_ToStream.
                        bWritten       : 1,

                        // Following are used during DBH processing.
                        bDBHCreated    : 1, // EI was created on DB
                        bDBHDeleted    : 1, // EI was deleted on DB
                        bDBHIncluded   : 1, // EI was included on DB
                        bDBHExcluded   : 1, // EI was excluded on DB
                        bDBHUpdated    : 1, // EI was updated on DB
                        bDBHDeleteAll  : 1, // Delete all sibling EI's on DB
                        bSequenceUpdt  : 1, // Used during Commit processing
                        bGenKeyNeeded  : 1, // This EI needs a genkey
                        bNoGenKey      : 1, // Do not create a genkey for this
                                            // EI. If TRUE then another linked
                                            // EI has bGenKeyNeeded = TRUE;
                        bForeignKeys   : 1, // EI needs a FK set.
                        bDelByAccept   : 1, // EI is about to removed as part of an Accept()

                        // Following flags for versioned entites
                        bVersionUpdated: 1, // EI version is updated (persist)
                        bVersionUpdFile: 1; // EI version is updated (file)
};

// Entity Instance Structure
struct EntityInstanceStruct
{
   zSHORT               nTableID;
   LPVIEWENTITY         hViewEntity;

   // Indicators
   union  { zULONG    nIndicators;
            struct EntityInstanceInd nInd; } u; // Entity instance indicators

   LPVIEWOI             hViewOI;
   LPENTITYINSTANCE     hNextHier;
   LPENTITYINSTANCE     hPrevHier;
   LPENTITYINSTANCE     hNextTwin;
   LPENTITYINSTANCE     hPrevTwin;
   LPENTITYINSTANCE     hParent;
   LPENTITYINSTANCE     hNextVsn;
   LPENTITYINSTANCE     hPrevVsn;
   LPENTITYINSTANCE     hNextLinked;
   zLONG                lTag;              // Used by NetCommit processing.
   zULONG               ulKey;             // Entity key.
   zLONG                lHierCount;        // Hier # for ent.--not always current!
   zSHORT               nLevel;            // Level of this instance
   zPVOID               hPersistRecord;    // Persistent data record
   zPVOID               hNonPersistRecord; // Non-persistent data record
};

// OpenFile Structure
struct OpenFileStruct
{
   zSHORT               nTableID;
   zLONG                lProcessID;
   LPOPENFILE           hNextOpenFile;
   zSHORT               nFlags;
   zLONG                lFileHandle;
   zCHAR                szFileName[ zMAX_FILENAME_LTH + 1 ];
   zCHAR                szTempFileName[ zMAX_FILENAME_LTH + 1 ];
   zULONG               uReadBufferSize;
   zULONG               uReadBufferUsed;
   zULONG               uReadBufferPos;
   zPCHAR               hReadBuffer;
   zULONG               uWriteBufferSize;
   zULONG               uWriteBufferPos;
   zPCHAR               hWriteBuffer;
};

// Error Structure
struct ErrorStruct
{
   zSHORT               nTableID;
   zSHORT               nSeverity;
   zSHORT               nID;
   zPCHAR               hText;
};

// Structures and defines for binary objects
#define zBinEntityInstance     1
#define zBinInstanceRecord     2
#define zBinExternalAttribute  3
#define zBinLinkInstance       4

struct BinEntityInstanceStruct
{
   zSHORT               nLevel;
   zSHORT               nHierNbr;
   zBOOL                bIsNextTwin;
   int                  nIndicators;
   zCHAR                chNextType;
};
typedef struct BinEntityInstanceStruct BinEntityInstanceRecord;

struct BinInstanceRecordStruct
{
   zUSHORT              uLth;
   zBOOL                bPersistent;
};
typedef struct BinInstanceRecordStruct BinInstanceRecordRecord;

struct BinExternalAttributeStruct
{
   zUSHORT              uLth;
   zUSHORT              uRecordOffset;
};
typedef struct BinExternalAttributeStruct BinExternalAttributeRecord;

struct BinLinkInstanceStruct
{
   zUSHORT              usSource;
   zUSHORT              usTarget;
   zBOOL                bRelOwner;
   zCHAR                chNextType;
};
typedef struct BinLinkInstanceStruct BinLinkInstanceRecord;

// used in sorting entities
struct ViewAttrListStruct
{
   LPVIEWATTRIB         lpViewAttrib;
   zPOBJOPER            pfObjectOper;  // pointer object oper for derived attrs
   zBOOL                bOrder;        // 0 - ascending,  1 - descending
   zPCHAR               pszContextName;
};
typedef struct ViewAttrListStruct ViewAttrListRecord;
typedef ViewAttrListRecord * LPVIEWATTRLIST;

// Use to hold the entry points for external operations;
// Object constraint handlers, Entity contraint handlers, and Derived
// attributes.
struct TaskOperationStruct
{
   zSHORT               nTableID;
   LPTASKOPER           hNextTaskOperationForTask; // DLL off Task struct
   LPTASKOPER           hNextTaskOperationForOEA;  // DLL off OD/Entity/Attr
   LPTASKOPER           hPrevTaskOperationForOEA;  // DLL off OD/Entity/Attr
   LPTASK               hTask;

   // Only one of the following pointers will be set, depending
   // upon where the double link list is chained from.
   LPVIEWOD             hViewOD;                   // chain off Object def
   LPVIEWENTITY         hViewEntity;               // chain off view entity
   LPVIEWATTRIB         hViewAttrib;               // chain off attr

   zPVOID               pfnTaskOper;               // pointer to function entry
   zLONG                lProcessID;                // permit quick recognition
                                                   // of whether library is for
                                                   // proper process
};

struct ZKeyStruct
{
   zCHAR                ch1;     // \xff ZKeyStruct indicator
   zLONG                lZKey;   // ZKey
   zCHAR                ch2;     // \x00
};

typedef struct ZKeyStruct ZKeyRecord;
typedef ZKeyRecord *LPZKEY;

#define     MAX_CORE_MQ_INT   4
struct MQInterfaceStruct
{
   zSHORT               nTableID;
   unsigned int         bRecursiveCall : 1; // TRUE if currently calling a msg func.
   zPVOID               pfnMQ[ MAX_CORE_MQ_INT ];
};

struct InternationalStruct
{
   zSHORT               nTableID;
   zSHORT               nCountry;      // Country code
   zCHAR                szCountry[ zZEIDON_NAME_LTH + 1 ]; // Selected country name
   zCHAR                szLanguage[ zZEIDON_NAME_LTH + 1 ];// National language code
   zSHORT               nLanguage;     // Selected Language code
   zCHAR                szList[ 5 ];   // List separator
   zSHORT               nMeasure;      // Measuring system; 0-metric, 1-english
   zSHORT               nTime;         // Time format; 0-12 hour, 1-24 hour
   zCHAR                szTime[ 5 ];   // Time separator
   zCHAR                sz1159[ 5 ];   // Trailing string for AM
   zCHAR                sz2359[ 5 ];   // Trailing string for PM
   zSHORT               nTLZero;       // Display leading 0 for Hours; 0-no, 1-yes
   zPCHAR               hShortDate;    // Date picture for short date format
   zPCHAR               hLongDate;     // Date picture for long date format
   zPCHAR               hTimeFmt;      // zeidon intl constructed from other info
   zCHAR                szCurrency[ 10 ];  // Currency symbol
   zSHORT               nCurrency;     // Currency format code
   zSHORT               nCurrDigits;   // Nbr digits for fractional currency
   zSHORT               nNegCurr;      // Negative currency format code
   zCHAR                szThousand[ 5 ]; // Symbol used in separating thousands
   zCHAR                szDecimal[ 5 ];  // Symbol used for integer/fraction sep.
   zSHORT               nDigits;       // Nbr of digits to use in decimal number
   zSHORT               nLZero;        // Leading zeros in dec; 0-no, 1-yes
};

// Following used by fnCompareOI_ToOI
#define zCOMPAREOI_IGNOREINC   0x00000001  // Only comp keys of includable ents.
#define zCOMPAREOI_RETURN      0x00000002  // Return as soon as a change is found.
#define zCOMPAREOI_PERSISTONLY 0x00000002  // Compare only persistent ent/attr

// Locking levels used in the XOD
#define zLL_NONE                    0
#define zLL_OPTIMISTIC_NOINC        1
#define zLL_OPTIMISTIC_CMPRALL      2
#define zLL_PESSIMISTIC             3
#define zLL_PESSIMISTIC_WITHREAD    4
#define zLL_PESSIMISTIC_NOREAD      5

// Following used by network operations.
#define MAX_LEN_APPLADDRESS 200
struct NetConnectionStruct
{
   zPVOID               pvConn; // connection pointer
   LPNETCONN            hNextNetConn;
   LPTASK               hTask;  // reuse connection only in the same task
   unsigned int         bClientConn  : 1; // Connection opened as Client
   zCHAR                szApplAddress[ MAX_LEN_APPLADDRESS ];
};

struct NetworkStruct
{
   LPNETWORK            hNextNetwork;
   zLONG                lProcessID;
   LPLIBRARY            hLibrary;
   zPVOID               pNetworkHandle;
   zPVOID               pvServDirData;
   zCHAR                szNetworkName[ 60 ];
   zCHAR                szExecutable[ 60 ];
   zSHORT               nTraceLevel;
   zSHORT               nServerCoreTraceLevel;  // Core Trace level on Server
   zSHORT               nServerNetTraceLevel;   // Net Trace level on Server
   zSHORT               nServerDBHTraceLevel;   // DB Handler Trace level on Server
   zSHORT               nConnCount;
   LPNETCONN            hFirstNetConn;

   unsigned int         bListen         : 1, // Current task is listening.
                        bLAD_Loaded     : 1, // An attempt was made to load the LAD.
                        bHoldConnection : 1; // Hold the connection til end of task

   // Function pointers into network DLL.
   zLPFN_NETCLOSE       lpfnClose;
   zLPFN_NETLISTEN      lpfnListen;
   zLPFN_NETCLOSE       lpfnStopListen;
   zLPFN_NETIO          lpfnSend;
   zLPFN_NETIO          lpfnReceive;
   zLPFN_NETOPCONN      lpfnOpenConn;
   zLPFN_NETCLCONN      lpfnCloseConn;
   zLPFN_NETCLCONN      lpfnBufferEnd;
   zLPFN_NETGETADDR     lpfnGetAddress;
   zLPFN_NETSETM        lpfnSetMode;
   zLPFN_NETSENDPKT     lpfnSendPacket;
   zLPFN_NETRECVPKT     lpfnRecvPacket;

   // Function pointers for Server directory services.
   LPLIBRARY            hServDirLib;
   zLPFN_SERVDIRINIT    lpfnServDirInit;
   zLPFN_SERVDIRCLOSE   lpfnServDirClose;
   zLPFN_SERVDIRADDR    lpfnServDirGetAddr;
   zCHAR                szFileName[ zMAX_FILENAME_LTH + 1 ];
};
