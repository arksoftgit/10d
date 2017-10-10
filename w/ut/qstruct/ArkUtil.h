#ifndef __ARKSOFT_H__
#define __ARKSOFT_H__

#ifndef __cplusplus
#error a C++ compilation is required (use a .cpp suffix)
#endif

extern "C"
{
#include <conio.h>
#include <ctype.h>
#include <direct.h>
#include <dos.h>
#include <errno.h>
#include <io.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>     // for exit( )
#include <string.h>
#include <sys\stat.h>   // for stat
#include <time.h>
#include <limits.h>
}

#include <iostream>
using namespace std;

#define min( a, b ) ((a) <= (b) ? (a) : (b))
#define max( a, b ) ((a) >= (b) ? (a) : (b))

enum zBOOL { FALSE, TRUE };
#define ERROR       -1
#define SUCCESS      0

#define LARGE    999999
#define EOF_CHAR   0x1a

typedef char           zCHAR;
typedef char           zFLAG;
typedef int            zINT;
typedef long           zLONG;
typedef short          zSHORT;
typedef unsigned char  zUCHAR;
typedef unsigned int   zUINT;
typedef unsigned long  zDWORD;
typedef unsigned long  zULONG;
typedef unsigned short zUSHORT;
typedef unsigned short zWORD;

typedef const char *   zCPCHAR;
typedef char *         zPCHAR;
typedef void *         zPVOID;

#define MAX_LINE_LENGTH         65536
#define OUTPUT_TYPE_NONE        0
#define OUTPUT_TYPE_SCREEN      1
#define OUTPUT_TYPE_FILE        2
#define FILE_COMPARE_BINARY     -2
#define FILE_COMPARE_ERROR      -1
#define FILE_COMPARE_DIFFERENT  0
#define FILE_COMPARE_EQUAL      1
#define FILE_COMPARE_WHITESPACE 2
#define FILE_COMPARE_IGNORE     3

/////////////////////////////////////////////////////////////////////////////
// Diagnostic support
#ifdef _DEBUG

#ifdef MAIN_DOS_VER
void
AssertFailed( zPCHAR lpFile,
              int  nLine )
{
   cerr << "Assertion failed at " << lpFile << "  Line " << nLine << '\n';
   cerr << "Do you want to continue (y/N)?" << endl;
   char ch = cin.get( );
   if ( ch != 'y' && ch != 'Y' )
      exit( 1 );
}
#else
void
AssertFailed( zPCHAR lpFile,
              int  nLine );

#endif  // #ifdef MAIN_DOS_VER

#define THIS_FILE          __FILE__
#define ASSERT(f)          ((f) ? ((void) 0) : \
                           ::AssertFailed( THIS_FILE, __LINE__ ))
#define VERIFY(f)          ASSERT(f)

class CDebugObject
{
public:
   virtual void
   Dump( ){ }
};

#else

#define ASSERT(f)          ((void) 0)
#define VERIFY(f)          ((void) (f))

#endif // _DEBUG

#define  MAXPATTERN 512       // max # characters in find string
#define  ASCIISIZE  256       // # characters in extended ASCII set
#define  MAXLINE  65000       // max length of line (from CRLF to CRLF)

#define  READFILE      "r"    // read only
#define  WRITEFILE     "w"    // write only (overwrite existing file)
#define  APPENDFILE    "a"    // write only (overwrite existing file)
#define  READBINARY    "rb"   // read binary only
#define  RWBINARY      "rb+"  // read/write binary
#define  WRITEBINARY   "wb"   // write binary only (overwrite existing file)
#define  BUFSIZE       MAXLINE + 1

// arbitrarily large constant for FAST/SLOW loop of Boyer-Moore
#define  zLARGE   999999

// grep defines, etc.
typedef /*unsigned*/ char zDFA;

#define zMAXDFA  1024
#define zMAXTAG  10

#define zOKP     1
#define zNOP     0

#define zCHR     1
#define zANY     2
#define zZ2M     3
#define zCCL     4
#define zNCL     5
#define zBOL     6
#define zEOL     7
#define zBOT     8
#define zEOT     9
#define zBOW     10
#define zEOW     11
#define zREF     12
#define zCLO     13
#define zOR      14
#define zJMP     15

#define zEND     0

// The following defines are not meant to be changeable.
// They are for readability only.
#define zMAXCHR   128
#define zCHRBIT   8
#define zBITBLK   zMAXCHR / zCHRBIT
#define zBLKIND   0170
#define zBITIND   07

#define zASCIIB   0177

#define mLoWord( l )         ((zUSHORT)(zULONG) ( l ))
#define mHiWord( l )         ((zUSHORT)((((zULONG)( l )) >> 16) & 0xFFFF))
#define mMakeLong( low, high ) ((zLONG)(((zUSHORT)(low)) | (((zULONG)((zUSHORT)(high))) << 16)))
#define mDeleteInit( p ) { if ( p ) { delete( p ); p = 0; } }
#define mDeleteInitA( p ) { if ( p ) { delete [] p; p = 0; } }

struct DTFilters
{
   zUSHORT usDateBegin;
   zUSHORT usTimeBegin;
   zUSHORT usDateEnd;
   zUSHORT usTimeEnd;
};

//////////////////
// Paul DiLascia Class to to navigate files that match a spec with wildcards
//
class CFileSpec : public _finddata_t
{
public:
   CFileSpec( )
   {
      m_hfile = -1;
   }

   ~CFileSpec( )
   {
      if ( m_hfile >= 0 )
         _findclose( m_hfile );
   }

   zBOOL First( const char *filespec )
   {
      if ( m_hfile >= 0 )
         _findclose( m_hfile );

      return( ((m_hfile = _findfirst( (char *) filespec, this )) != -1) ? TRUE : FALSE );
   }

   zBOOL Next( )
   {
      return( (m_hfile >= 0 && _findnext( m_hfile, this ) == 0) ? TRUE : FALSE );
   }

private:
   long     m_hfile;    // handle from findfirst
};

class CSList;
class CSLink;
class CFileData;
class CDirData;

typedef zSHORT (* fnDirBegin)( CDirData *, zPCHAR, zSHORT );
typedef zSHORT (* fnDirTroll)( CFileData *, CDirData *, zCPCHAR );
typedef void (* fnDirEnd)( CDirData *, zCPCHAR );

/////////////////////////////////////////////////////////////////////////////
// Class definition for CSList (simple single-linked list).
//
// a simpleton single-link list
class CSLink
{
public:
   CSLink( zCPCHAR cpcName );
   ~CSLink( );

   zPCHAR m_pchName;
   zSHORT m_nNameLth;
   CSLink *m_pNext;
};

// manage a simpleton single-link list
class CSList
{
public:
   CSList( );
   ~CSList( );

   CSLink * Add( zCPCHAR cpcName );    // return ptr if added ... 0 otw
   CSLink * AddIgnoreDup( zCPCHAR cpcName ); // return ptr if added ... 0 otw
   CSLink * Find( zCPCHAR cpcName );   // return ptr if found ... 0 otw
   CSLink * Remove( zCPCHAR cpcName ); // return ptr if found ... 0 otw
   zBOOL FindFile( zCPCHAR cpcName );  // return TRUE if found ... FALSE otw
   zBOOL IsEmpty( );
   zLONG GetCount( );
   CSLink * GetFirstLink( );
   void  AddToList( zCPCHAR cpcList );
   void  AddToListIgnoreDup( zCPCHAR cpcList );
   void  ExpandResponseFile( zCPCHAR cpcFileName );

private:
   CSLink *m_pHead;
   zLONG  m_lCnt;
};

class CFileData
{
public:
   CFileData( zCPCHAR cpcName,
              zCPCHAR cpcTimestamp = 0 );
   CFileData( zCPCHAR cpcName,
              time_t  DateTime,
              zLONG   lSize );
   ~CFileData( );

   void
   SetDate( zCPCHAR cpcTimestamp );

   zPCHAR    m_pchName;
   zSHORT    m_nNameLth;
   zPCHAR    m_pchTimestamp;
   zLONG     m_lTimestampLth;
   time_t    m_DateTime;
   zLONG     m_lSize;
   zSHORT    m_nState;
   CFileData *m_pFileNext;
};

class CDirData
{
public:
   CDirData( zCPCHAR  cpcName,
             CDirData *pDirParent = 0 );
   ~CDirData( );

   CDirData * AddDir( zPCHAR pchDir );
   CDirData * SeekDir( zPCHAR pchDir,
                       zSHORT nDirLth,
                       zSHORT nOrigDirLth );
   CDirData * AddSubDir( zPCHAR pchDir );
   CFileData * AddFile( CFileData *pFileData );
   CFileData * SeekFile( zCPCHAR cpcFileName );
   CFileData * RemoveFile( zCPCHAR cpcFileName );

   zPCHAR    m_pchName;
   zSHORT    m_nNameLth;
   CDirData  *m_pDirParent;
   CDirData  *m_pDirNext;
   CDirData  *m_pSubDir;
   CFileData *m_pFileHead;
};

enum fname_errors
{
    FN_OK,
    FN_BADDRIVE = 340,
    FN_BADCOLON,
    FN_PTOOLONG,
    FN_DTOOLONG,
    FN_NTOOLONG,
    FN_XTOOLONG,
    FN_BADCHAR,
    FN_INVALIDPATH,
    FN_NULL
};

class CFileName
{
   // there are three constructors, a default constructor (no arguments),
   // one which takes a filename string as an argument, and optionally
   // allows characters to be excluded from the filename.  The default
   // value for this second parameter is the list of characters which
   // are officially prohibited from a DOS file name or extension.
   // The final constructor is a copy constructor.

public:
   // ctor
   CFileName( );

   // ctor
   CFileName( zCPCHAR cpcPathSpec,
              zBOOL   bExpectFileName = FALSE,
              zBOOL   bAcceptSpecial = FALSE,
              zCPCHAR cpcInvalidCharSet = "*=[]:;\",?/" );
           // zCPCHAR cpcInvalidCharSet = "*+=[]:;\",?/" );
           // zCPCHAR cpcInvalidCharSet = "*+=[]:;\",.?/" );

   // ctor
   CFileName( const CFileName& );

   // dtor
   ~CFileName( );

   CFileName& operator=( const CFileName& );

   // the next set of functions give access to the constituent parts of
   // the filename.
   char    GetDrive( ) const { return m_cDrive; }
   zCPCHAR GetPath( ) const { return m_pchPath; }
   zCPCHAR GetName( ) const { return m_pchName; }
   zCPCHAR GetExt( ) const { return m_pchExt; }

   // this function returns the requested concatenation in the location
   // specified.  the concatenated length is the return code.
   zSHORT GetDrivePathFilenameExt( zPCHAR pchConcatName,
                                   zBOOL  bDrive,
                                   zBOOL  bPath,
                                   zBOOL  bFilename,
                                   zBOOL  bExt );

   // The next three functions modify the CFileName object.  The action
   // of the build function is determined by its defaulted final argument.
   // If this is zero, then the effect is to modify only the components
   // of the filename for which there are non-zero arguments.  If the final
   // argument is non-zero, then the arguments override the existing values
   // unconditionally.
   zSHORT Update( char    cDrive,
                  zCPCHAR cpcPathName,
                  zCPCHAR cpcName,
                  zCPCHAR cpcExt,
                  zBOOL   bOverride = FALSE );

   // operator( ) returns the complete filename
   zPCHAR operator( )( );

   // The parse function parses the supplied string, and determines whether or not it is a legal filename.
   zSHORT Parse( zCPCHAR cpcFileName,
                 zBOOL   bExpectFileName = FALSE,
                 zBOOL   bAcceptSpecial = FALSE );

   zLONG  GetFullNameLth( );
   zSHORT GetDriveDirLth( );

   zSHORT GetError( );

private:

   char   m_cErr;
   zPCHAR m_pchFullName;
   zSHORT m_nFullNameLth;
   zPCHAR m_pchPath;
   zSHORT m_nPathLth;
   zPCHAR m_pchInvalidNameSet;
   zLONG  m_lInvalidNameSetLth;
   char   m_cDrive;
   zPCHAR m_pchName;
   zSHORT m_nNameLth;
   zPCHAR m_pchExt;
   zSHORT m_nExtLth;
   zBOOL  m_bSpecial;
};

//============================================================================
// C function prototypes
//============================================================================

#ifdef __cplusplus
extern "C"
{

#endif
zBOOL
MatchFilenameToWildcard( zCPCHAR cpcWildcardSpec,
                         zCPCHAR cpcFileName );
// search prototypes
void
qbldelta( zSHORT  nPatternLth,      // pattern length
          zCPCHAR cpcPattern,       // pattern to locate
          zLONG   *plDelta1Table,   // Boyer-Moore Delta1 Table
          zLONG   *plDelta2Table ); // Boyer-Moore Delta2 Table
zLONG
qfind( zSHORT  nPatternLth,         // pattern length
       zCPCHAR cpcPattern,          // pattern to locate
       zLONG   lBufferLth,          // length of buffer to be searched
       zPCHAR  pchBuffer,           // buffer to be searched for pattern
       zLONG   *plDelta1Table,      // Boyer-Moore Delta1 Table
       zLONG   *plDelta2Table );    // Boyer-Moore Delta2 Table
zLONG
qfindr( zSHORT  nPatternLth,        //  pattern length
        zCPCHAR cpcPattern,         //  pattern to locate
        zLONG   lBufferLth,         //  length of buffer to be searched
        zPCHAR  pchBuffer,          //  buffer to be searched for pattern
        zLONG   *plDelta1Table,     //  Boyer-Moore Delta1 Table
        zLONG   *plDelta2Table );   //  Boyer-Moore Delta2 Table
zLONG
qchange( zLONG   lCurrentPos,       //  current position at which to repl
         zSHORT  nPatternLth,       //  pattern length
         zCPCHAR cpcPattern,        //  pattern to locate
         zSHORT  nReplaceLth,       //  replace string length
         zPCHAR  pchReplace,        //  replace string
         zLONG   *lBufferLth,       //  length of buffer to be searched
         zPCHAR  pchBuffer,         //  buffer to be searched for pattern
         zLONG   *plDelta1Table,    //  Boyer-Moore Delta1 Table
         zLONG   *plDelta2Table,    //  Boyer-Moore Delta2 Table
         zLONG   lMaxLth );         //  Maximum lth of resultant string

#ifdef __cplusplus
}
#endif

zLONG
fnLoadDirList( CDirData *pParentDir,
               zPCHAR   pchParentPath,
               zBOOL    bSubdir,
               zBOOL    bLoadFiles,
               zCPCHAR  cpcFileMask,
               zSHORT   nAttrib );
zLONG
fnLoadFileList( CDirData *pDir,
                zPCHAR   pchParentPath,
                zCPCHAR  cpcFileMask,
                zSHORT   nAttrib );
void
fnTraverseDirList( CDirData *pDir,
                   zPCHAR   pchDrivePath,
                   zSHORT   nDrivePathLth,
                   zCPCHAR  cpcFileMask,
                   zSHORT   nAttrib,
                   zBOOL    bLoadFiles,
                   zSHORT   nRootLth );
#ifdef DEBUG
void
fnDisplayLinkList( CSLink *pLink );
#endif

zBOOL
fnDirExcluded( zPCHAR pchDirName, zSHORT nRootLth );
char
fnGetY_N( zPCHAR pchValidResponse,
          zPCHAR pchPrompt );
void
fnRotateAction( zBOOL bRestart );
zUSHORT
fnEstablishDate( zPCHAR pchDate,
                 zSHORT rgnDate[ ] );
zUSHORT
fnEstablishTime( zPCHAR pchTime,
                 zSHORT rgnTime[ ] );
zDWORD
fnSTimeToDirtime( time_t atime,
                  zWORD  *pwDate,
                  zWORD  *pwTime );
void
fnDirtimeToTimestamp( zULONG ulDirDateTime,
                      zPCHAR pchTimestamp,
                      zLONG  lTimestampLth );
zBOOL
fnWithinInterval( time_t dwDirDateTime1,
                  time_t dwDirDateTime2,
                  zLONG  lInterval,
                  short  nTimeZoneOffset,
                  FILE   *pRptFile,
                  zPCHAR pchSrcFile );
zBOOL
fnCompareFiles( zPCHAR pchSrcDir,
                zPCHAR pchTgtDir,
                FILE   *pRptFile );
zSHORT
CompareTextFiles( zPCHAR pchFirstFile,
                  zPCHAR pchSecondFile,
                  zLONG  lFirstFileLth,
                  zSHORT nOutputType,
                  FILE   *pRptFile,
                  zBOOL  bIgnoreWhiteSpace,
                  CSList *pListIgnore );

zLONG
qreads( zPCHAR pchReturnBuffer,
        zLONG  lMaxReturnBufferSize,
        FILE   *pSrcFile );
void
qwrites( zPCHAR pchLineBuffer,
         zLONG  lLineBufferSize,
         FILE   *pTgtFile );

void
RE_Fail( zPCHAR pchMessage,
         zCHAR  chOp );
void
RE_CharSet( zCHAR ch );
zPCHAR
RE_Compile( zPCHAR pchPattern );
zBOOL
RE_Match( zPCHAR pchString );
zPCHAR
RE_PatternMatch( zPCHAR pchString,
                 zDFA *ap );
void
RE_ModWord( zPCHAR pch );
zSHORT
RE_Substitute( zPCHAR pchSrc,
               zPCHAR pchTgt );
void
RegexHelp( );

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

typedef void (*FARPROC_ELEMSWAP)( char *pItem1, char *pItem2 );
typedef int  (*FARPROC_ELEMCOMPARE)( char *pItem1, char *pItem2 );

void
fnSwapInt( int *pn1,             // swap integers
           int *pn2 );

void
fnSwapChar( char *pch1,          // swap characters
            char *pch2 );

void
qqsort( char  *pchBaseArray,            // base address of array to sort
        zLONG lElements,                // number of elements to sort
        zLONG lElementBytes,            // size of element to sort
        FARPROC_ELEMCOMPARE pfnCmpr );  // compare function

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// True for output styles that are robust,
// i.e. can handle a file that ends in a non-newline.
#define ROBUST_OUTPUT_STYLE( S ) ((S) != OUTPUT_ED && (S) != OUTPUT_FORWARD_ED)
#define STAT_BLOCKSIZE( s ) (8 * 1024)
#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)

#ifndef ISPRINT
#define ISPRINT(c) (isascii(c) && isprint(c))
#endif
#ifndef ISSPACE
#define ISSPACE( c )    (isspace (c))
#endif
#ifndef ISUPPER
#define ISUPPER( c )    (isupper (c))
#endif
#ifndef ISDIGIT
#define ISDIGIT( c )    ((unsigned) (c) - '0' <= 9)
#endif

#define TAB_WIDTH  3

#ifndef GUTTER_WIDTH_MINIMUM
#define GUTTER_WIDTH_MINIMUM 3
#endif

#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 76
#endif

#define mInitZero( s, n )  memset( (s), 0, (n) )

char * xmalloc( zLONG lLth );
//char * xrealloc( char *ptr, size_t size );

enum output_style
{
   OUTPUT_NORMAL,     // default output style.
   OUTPUT_CONTEXT,    // diff with lines of context before and after (-c)
   OUTPUT_UNIFIED,    // diff in a unified context diff format (-u)
   OUTPUT_ED,         // diff as commands suitable for `ed' (-e)
   OUTPUT_FORWARD_ED, // diff as a forward ed script (-f)
   OUTPUT_RCS,        // like -f, but output cnt of chged lines in each "command" (-n)
   OUTPUT_IFDEF,      // output merged #ifdef'd file (-D)
   OUTPUT_SDIFF       // output sdiff style (-y)
};

struct change
{
   struct change *link;  // Previous or next edit command
   zLONG inserted;       // # lines of file 1 changed here.
   zLONG deleted;        // # lines of file 0 changed here.
   zLONG line0;          // Line number of 1st deleted line.
   zLONG line1;          // Line number of 1st inserted line.
   char  ignore;         // Flag used in context.c
};

struct file_data
{
   int          fd;    // File descriptor
   char const   *name; // File name
   struct _stat stat;  // File status from fstat()

   // Buffer in which text of file is read.
   char *buffer;
   // Allocated size of buffer.
   size_t bufsize;
   // Number of valid characters now in the buffer.
   size_t buffered_chars;

   // Array of pointers to lines in the file.
   char const **linbuf;

   // linbuf_base <= buffered_lines <= valid_lines <= alloc_lines.
   // linebuf[linbuf_base ... buffered_lines - 1] are possibly differing.
   // linebuf[linbuf_base ... valid_lines - 1] contain valid data.
   // linebuf[linbuf_base ... alloc_lines - 1] are allocated.
   zLONG linbuf_base, buffered_lines, valid_lines, alloc_lines;

   // Pointer to end of prefix of this file to ignore when hashing.
   char const *prefix_end;

   // Count of lines in the prefix.
   // There are this many lines in the file before linbuf[ 0 ].
   zLONG prefix_lines;

   // Pointer to start of suffix of this file to ignore when hashing.
   char const *suffix_begin;

   // Vector, indexed by line number, containing an equivalence code for
   // each line.  It is this vector that is actually compared with that
   // of another file to generate differences.
   zLONG *equivs;

   // Vector, like the previous one except that
   // the elements for discarded lines have been squeezed out.
   zLONG *undiscarded;

   // Vector mapping virtual line numbers (not counting discarded lines)
   // to real ones (counting those lines).  Both are origin-0.
   zLONG *realindexes;

   // Total number of nondiscarded lines.
   zLONG nondiscarded_lines;

   // Vector, indexed by real origin-0 line number,
   // containing 1 for a line that is an insertion or a deletion.
   // The results of comparison are stored here.
   char *changed_flag;

   // 1 if file ends in a line with no final newline.
   zLONG missing_newline;

   // 1 more than the maximum equivalence value used for this or its
   // sibling file.
   zLONG equiv_max;
};

#endif  // #ifndef __ARKSOFT_H__
/////////////////////////////// end of file /////////////////////////////////
