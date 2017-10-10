//KZOEINCO.H - Core internal defs that are OS-dependent.

/*
CHANGE LOG

2001.04.06  DGC
   Added zMUTEX_ENTITYKEY.

*/

//========================================================================
//    MISCELLANEOUS STUFF
//========================================================================

// When we write strings to a portable file we have to decide if the string
// contains "special" chars.  If one of the "special" chars appears in the
// string value then the string is stored as a blob.  For WinX and OS/2 any
// character having an ASCII value less than a space is considered "special".
#define CHAR_IS_SPECIAL( c ) ((unsigned) (c) < (unsigned) ' ')

//========================================================================
//    MEMORY MANAGEMENT
//========================================================================

#ifndef zEXTERN
#error zEXTERN is undefined in kzoenico.h
#endif

// zGETPTR is already defined for Zeidon applications but we want to define
// it differently for internal core operations.
#undef zGETPTR

// #define __MUTEX_DEBUG__

// Following used for Core memory allocation.  Description as follows:
//
//    zALIGN_MEM_SIZE - Defines the memory alignment needed for the OS in bytes.
//    zSHARED_ALLOC   - Size (in bytes) of shared memory allocated by Core to
//                      store internal data.
//    zMAX_ALLOC      - Maximum length (in bytes) of dynamically allocated mem.
//
#if defined( __WIN32__ )

   #define zALIGN_MEM_SIZE 4
   #define zSHARED_ALLOC   4000000L
   #define zMAX_ALLOC      4194304L    // No particular reason for this #.
   
   // define zCRITICAL_SECTION same as windows definition in mapiwin.h
   #define zCRITICAL_SECTION           zULONG

   // Set up information for shared memory pages.
   #define zSHR_MAX_PAGES 256

   zEXTERN zPVOID g_ZeidonPageTable[ zSHR_MAX_PAGES ]
   #ifdef zGLOBAL_DATA
         = { 0 }
   #endif
         ;  // end declaration of g_ZeidonPageTable

   zEXTERN zLONG g_FileMappingHandles[ zSHR_MAX_PAGES ]
   #ifdef zGLOBAL_DATA
         = { 0 }
   #endif
         ;  // end declaration of g_FileMappingHandles

   typedef zPVOID (LOCALOPER * zLPFN_GETPTR)( zPVOID );

   zEXTERN zLPFN_GETPTR g_pfnGetPtr;
   zEXTERN zLPFN_GETPTR g_pfnGetHndl;

// #define zGETPTR( a )  (SysGetPointerFromHandle( (zPVOID) (a) ))
   #define zGETPTR( a )  ((*g_pfnGetPtr)( (zPVOID) (a) ))
// #define zGETHNDL( a ) (SysGetHandleFromPointer( (zPVOID) (a) ))
   #define zGETHNDL( a ) ((*g_pfnGetHndl)( (zPVOID) (a) ))

   #define zMAX_PROCESSES 50

   typedef struct ProcessListStruct
   {
      zSHORT  nOE_Request;
      zUSHORT uAppOE_Msg;
      zULONG  hWndAppOE_Msg;
      zULONG  lPageTableIndex;
      zULONG  hMemHandle;
      zLONG   lProcessID;
   } ProcessListRecord, * LPPROCESSLIST;

   // OS-specific information.  This gets added to the AnchorStruct.
   typedef struct AnchorOS_Struct
   {
      zULONG hMainWindow;
      zLONG  lProcessCount;
      ProcessListRecord ProcessList[ zMAX_PROCESSES ];
   } AnchorOS_Record, * LPANCHOROS_RECORD;

   // This is used to check which warnings are to be emitted by the OE.
   zEXTERN zSHORT g_nOE_TraceWarning
   #ifdef zGLOBAL_DATA
         = 0
   #endif
      ;

   // Used to set the real task view (currently used by object browser).
   zEXTERN zVIEW g_vRealTaskView
   #ifdef zGLOBAL_DATA
         = 0
   #endif
      ;

   // Following is used for logic to bridge gap with Process/Task changes.
   // This is the "default" task view for the current process.
   zEXTERN zVIEW g_vDefaultTaskView
   #ifdef zGLOBAL_DATA
         = 0
   #endif
      ;
   zEXTERN zLONG g_lProcessID
   #ifdef zGLOBAL_DATA
         = 0
   #endif
      ;

#elif defined( __OS2__ )

   #define zALIGN_MEM_SIZE 4
   #define zSHARED_ALLOC   4000000L
   #define zMAX_ALLOC      4194304L    // No particular reason for this #.

   #define zGETPTR( a )  (a)
   #define zGETHNDL( a ) (a)

#else

   #define zALIGN_MEM_SIZE 4
   #define zSHARED_ALLOC   4000000L
   #define zMAX_ALLOC      4194304L

   #define zGETPTR( a )  (a)
   #define zGETHNDL( a ) (a)

#endif

//========================================================================
//    MUTEXES
//========================================================================

// Core calls all internal mutexes using the following macros.  To be as
// flexible as possible the name of each mutex is also a macro.  If the macros
// call any functions then the function protoype must be included here.

#if defined( __WIN32__ )

   // Following used to debug mutexes.
   typedef struct ztagLARGE_INTEGER
   {
      zLONG LowPart;
      zLONG HighPart;
   } zLARGE_INTEGER;

   struct DbgMutexTaskInfo
   {
      long           lTaskID;
      char           szLockingFile[ 15 ];
      long           lLockingLine;
      char           cStatus;
      zLARGE_INTEGER lTimeRequest;
   };

   struct DbgMutexInfo
   {
      struct DbgMutexTaskInfo TaskInfo[ 50 ];
      int    nLockCount;
      int    lLastTaskIdx;
   };

   #define MUTEXDBG_NAME    "Zeidon Mutex Debug"
   #define MUTEXDBG_MEMNAME "Zeidon Mutex Memory"

   #define zCREATE_MUTEX( mtx )     fnSysCreateCoreMutex( mtx )
   #define zDESTROY_MUTEX( mtx )    fnSysDestroyCoreMutex( mtx )

   #if defined( __MUTEX_DEBUG__ )
      #define zLOCK_MUTEX( mtx )       fnSysLockCoreMutex( mtx, __FILE__, __LINE__ )
      #define zUNLOCK_MUTEX( mtx )     fnSysUnlockCoreMutex( mtx, __FILE__, __LINE__ )
   #else
      #define zLOCK_MUTEX( mtx )       fnSysLockCoreMutex( mtx )
      #define zUNLOCK_MUTEX( mtx )     fnSysUnlockCoreMutex( mtx )
   #endif

   #define zMUTEX_INITTERM             0
   #define zMUTEX_MEMORY               1
   #define zMUTEX_ANCHORBLOCK          2
   #define zMUTEX_ANCHORINIT           3
   #define zMUTEX_SHAREDMEM            4
   #define zMUTEX_TASKCHAIN            5
   #define zMUTEX_TASKCHAIN_WRITE      6
   #define zMUTEX_MUTEX                7
   #define zMUTEX_DEBUGCHANGE          8
   #define zMUTEX_PESSIMISTICLOCK      9
   #define zMUTEX_APPLA               10
   #define zMUTEX_ENTITYKEY           11
   #define zMUTEX_TASKPROCESS         12
   #define zMUTEX_PROCESSCHAIN        13
   #define zMUTEX_PROCESSCHAIN_WRITE  14
   #define zMUTEX_NETWORKCHAIN        15
   #define zMUTEX_COUNT               16  // # of mutexes used by Win32

   zEXTERN zPVOID g_ZeidonMutexTable[ zMUTEX_COUNT ]
   #ifdef zGLOBAL_DATA
         = { 0 }
   #endif
         ;  // End declaration of g_ZeidonMutexTable

   zEXTERN zPCHAR g_ZeidonMutexName[ zMUTEX_COUNT ]
   #ifdef zGLOBAL_DATA
         = {
              "ZEIDON MUTEX -- INITTERM",
              "ZEIDON MUTEX -- MEMORY ALLOCATION",
              "ZEIDON MUTEX -- ANCHOR BLOCK",
              "ZEIDON MUTEX -- ANCHOR INIT",
              "ZEIDON MUTEX -- SHARED MEM",
              "ZEIDON MUTEX -- TASK CHAIN",
              "ZEIDON MUTEX -- TASK CHAIN WRITE",
              "ZEIDON MUTEX -- MUTEX",
              "ZEIDON MUTEX -- DEBUGCHANGE",
              "ZEIDON MUTEX -- PESSIMISTIC LOCK",
              "ZEIDON MUTEX -- APPLA",
              "ZEIDON MUTEX -- ENTITY KEY",
              "ZEIDON MUTEX -- TASKPROCESS",
              "ZEIDON MUTEX -- PROC CHAIN",
              "ZEIDON MUTEX -- PROC CHAIN WRITE",
              "ZEIDON MUTEX -- NETWORK CHAIN"
           }
   #endif
         ;  // End declaration of g_ZeidonMutexTable

   #if defined( __MUTEX_DEBUG__ )
      zVOID LOCALOPER
      fnSysCreateCoreMutex( zLONG lMutex );
      zVOID LOCALOPER
      fnSysDestroyCoreMutex( zLONG lMutex );
      zVOID LOCALOPER
      fnSysLockCoreMutex( zLONG lMutex, zPCHAR szFile, zLONG lLine );
      zVOID LOCALOPER
      fnSysUnlockCoreMutex( zLONG lMutex, zPCHAR szFile, zLONG lLine );
   #else
      zVOID LOCALOPER
      fnSysCreateCoreMutex( zLONG lMutex );
      zVOID LOCALOPER
      fnSysDestroyCoreMutex( zLONG lMutex );
      zVOID LOCALOPER
      fnSysLockCoreMutex( zLONG lMutex );
      zVOID LOCALOPER
      fnSysUnlockCoreMutex( zLONG lMutex );
   #endif

   // MutexInfo contains all OS-dependent data needed to use application
   // mutexes.  For Win32 this is a handle (which we'll store as a long).
   typedef struct _MutexInfo
   {
      // If TRUE then the mutex is really a critical section, which only
      // works in the current process.
      zBOOL   bCriticalSection;

      // Following is for "Process" mutexes.
      zLONG   hMutexOS;            // Handle for mutex.

      // Following is for "Thread" mutexes.
      zCHAR   CritSection[ 500 ];  // NOTE! Must be larger than Win32 CriticalSection
      LPMUTEX hParentMutex;

   } MutexInfo;

#elif defined( __OS2__ )

   #define zCREATE_MUTEX( mtx )     fnSysCreateCoreMutex( (mtx) )
   #define zDESTROY_MUTEX( mtx )    fnSysDestroyCoreMutex( (mtx) )
   #define zLOCK_MUTEX( mtx )       fnSysLockCoreMutex( (mtx) )
   #define zUNLOCK_MUTEX( mtx )     fnSysUnlockCoreMutex( (mtx) )

   #define zMUTEX_INITTERM          0
   #define zMUTEX_MEMORY            1
   #define zMUTEX_ANCHORBLOCK       2
   #define zMUTEX_ANCHORINIT        3
   #define zMUTEX_SHAREDMEM         4
   #define zMUTEX_TASKCHAIN         5
   #define zMUTEX_TASKCHAIN_WRITE   6
   #define zMUTEX_TRACE             7
   #define zMUTEX_MUTEX             8
   #define zMUTEX_DEBUGCHANGE       9
   #define zMUTEX_PESSIMISTICLOCK  10
   #define zMUTEX_APPLA            11
   #define zMUTEX_ENTITYKEY        12
   #define zMUTEX_COUNT            13  // # of mutexes used by OS/2

#ifdef INCL_DOSSEMAPHORES

   zEXTERN HMTX g_ZeidonMutexTable[ zMUTEX_COUNT ]
   #ifdef zGLOBAL_DATA
         = { 0 }
   #endif
         ;  // End declaration of g_ZeidonMutexTable

#endif

   zEXTERN zPCHAR g_ZeidonMutexName[ zMUTEX_COUNT ]
   #ifdef zGLOBAL_DATA
         = { "\\sem32\\ZeidonInit",
             "\\sem32\\ZeidonMemory",
             "\\sem32\\ZeidonAnchor",
             "\\sem32\\ZeidonA_Init",
             "\\sem32\\ZeidonShared",
             "\\sem32\\ZeidonTaskChain",
             "\\sem32\\ZeidonTaskChainWrite",
             "\\sem32\\ZeidonTrace",
             "\\sem32\\ZeidonMutex",
             "\\sem32\\ZeidonDebugChange",
             "\\sem32\\ZeidonPessimisticLock",
             "\\sem32\\ZeidonApplA" }
   #endif
         ;  // End declaration of g_ZeidonMutexTable

   zSHORT LOCALOPER
   fnSysCreateCoreMutex( zLONG lMutex );
   zSHORT LOCALOPER
   fnSysDestroyCoreMutex( zLONG lMutex );
   zSHORT LOCALOPER
   fnSysLockCoreMutex( zLONG lMutex );
   zSHORT LOCALOPER
   fnSysUnlockCoreMutex( zLONG lMutex );

   // MutexInfo contains all OS-dependent data needed to use application
   // mutexes.  For OS2 this is a mutex handle.
   typedef HMTX MutexInfo;

#else

   // We don't need mutexes for Win 3.x so make it a no-op.
   #define zCREATE_MUTEX( mtx )
   #define zDESTROY_MUTEX( mtx )
   #define zLOCK_MUTEX( mtx )
   #define zUNLOCK_MUTEX( mtx )

   // MutexInfo contains all OS-dependent data needed to use application
   // mutexes.  For Win 3.x this is really ignored so we'll just store it as
   // a char.
   typedef zCHAR MutexInfo;

#endif
