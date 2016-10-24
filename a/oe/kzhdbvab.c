/////////////////////////////////////////////////////////////////////////////

   KZHDBVAB.C - DDL generator for Raima Data Manager

///////////////////////////// DEFINES ///////////////////////////////////////
/*
CHANGE LOG
2002.03.21  FH
    in DDL generation present "success" without a beep (not like an error)

2001.02.06  RG  Z2000
    - Fixed Bug R54630: New parameter in function BuildDDL and message
      DDL-file is build at the end of the function
*/

#define  KZSYSSVC_INCL
#define  KZMETA_INCL
#include <kzoengaa.h>
#include <zdrvropr.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_TABLENAME_LTH     34
#define MAX_COLUMNNAME_LTH    34
#define MAX_DATATYPE_LTH      20
#define COLUMN_INDENT         10
#define COMMENT_START         "/*"
#define COMMENT_END           "*/"

// List of words that are reserved in databases supported by Zeidon.
// Note: these MUST be listed in alphabetical order.
zCHAR  *szReservedName[] =
{
   "ASC",
   "ASCENDING",
   "BY",
   "CHAR",
   "COMPOUND",
   "CONTAINS",
   "DATA",
   "DATABASE",
   "DB_ADDR",
   "DESC",
   "DESCENDING",
   "DOUBLE",
   "FILE",
   "FIRST",
   "FLOAT",
   "INT",
   "KEY",
   "LAST",
   "LOCAL",
   "LONG",
   "MEMBER",
   "NEXT",
   "OPT",
   "OPTIONAL",
   "ORDER",
   "OWNER",
   "RECORD",
   "RECORDS",
   "SET",
   "SETS",
   "SHORT",
   "STATIC",
   "STRUCT",
   "TIMESTAMP",
   "UNIQUE",
   "UNSIGNED",
   "\0"       // Must be last -- terminates list.
};

// The following defines should match what is in RaimaDM.
// NOTE: We cannot just include raima .h files.

#define FILENMLEN       48
#define MAXDIMS   3

/* The following defines MUST match db_VISTA's */
/* Dictionary table typedefs */

typedef struct    /* File table */
{
   zCHAR ft_name[ FILENMLEN ];          /* Name of file */
   short ft_desc;                       /* File descriptor */
   unsigned char ft_status;             /* File status */
   zCHAR ft_type;                       /* File type */
   short ft_slots;                      /* Slots per page */
   short ft_slsize;                     /* Slot size */
   short ft_pgsize;                     /* Page size */
   short ft_flags;                      /* File flags */
} FILE_ENTRY;

typedef struct    /* Record table */
{
   short rt_file;                       /* File table reference */
   short rt_len;                        /* Length of record */
   short rt_data;                       /* offset to first field */
   short rt_fields;                     /* Field table reference */
   short rt_fdtot;                      /* # of fields in record */
   short rt_flags;                      /* Record flags */
} RECORD_ENTRY;

typedef struct    /* Field table */
{
   zCHAR fd_key;                        /* Key type of field */
   unsigned char fd_type;               /* Type of field */
   short fd_len;                        /* Length of field */
   short fd_dim[ MAXDIMS ];             /* Dimensions of field */
   short fd_keyfile;                    /* Key table reference */
   short fd_keyno;                      /* Key prefix # */
   short fd_ptr;                        /* Offset to this field */
   short fd_rec;                        /* Reference to record table */
   short fd_flags;                      /* Field flags */
} FIELD_ENTRY;

typedef struct    /* Set table */
{
   short st_order;                      /* Set ordering */
   short st_own_rt;                     /* Reference to owner record tbl */
   short st_own_ptr;                    /* Offset to set pointer */
   short st_members;                    /* Reference to member table */
   short st_memtot;                     /* # of members of set */
   short st_flags;                      /* Set flags */
} SET_ENTRY;

typedef struct    /* Member table */
{
   short mt_record;                     /* Reference to member record tbl */
   short mt_mem_ptr;                    /* Offset to member pointer */
   short mt_sort_fld;                   /* Reference to sort table */
   short mt_totsf;                      /* # of sort fields */
} MEMBER_ENTRY;

typedef struct    /* Sort table */
{
   short se_fld;                        /* Reference to sort field table */
   short se_set;                        /* Reference to set table */
} SORT_ENTRY;

typedef struct    /* Compound key table */
{
   short kt_key;                        /* Reference to field table */
   short kt_field;                      /* Reference to field table */
   short kt_ptr;                        /* Offset in key for this field */
   short kt_sort;                       /* Sorting order of this field */
} KEY_ENTRY;

/*  Structures that holds the header info from the dictionary */
typedef struct
{
   zCHAR dbver[ 6 ];            /* Version of dictionary(Vn.nn) */
   short page_size;     /* Size of page */
   short size_ft;               /* # of file table entries */
   short size_rt;               /* # of record table entries */
   short size_fd;               /* # of field table entries */
   short size_st;               /* # of set table entries */
   short size_mt;               /* # of member table entries */
   short size_srt;      /* # of sort table entries */
   short size_kt;               /* # of key table entries */
} HeaderType;

/* End of definitions that MUST match db_VISTA's definitions */

/*****************************************************************
*
*   This routine generates the DDL for RDM and is called from the Zeidon
*   Technical Environment Dialog.
*
*   The following describes the standard arguments for DDL generation:
*
*      vDTE - View to Technical Environment we want to build DDL for.
*      vEMD - View to E/R diagram.  Not currently used for SQLBASE generation.
*      pchFileName - Pointer to buffer containing the directory we should
*              write the DDL to.  This buffer can be assumed large enough to
*              contain a full file name.  The directory can be changed.
*      vSubtask - View to window, to send a DIL-message or an error message
*
*   Returns: 0           - Everything OK.
*            zCALL_ERROR - DDL not generated.
*
/////////////////////////////////////////////////////////////////////////////
zSHORT OPERATION
BuildDDL( zVIEW  vDTE,
          zVIEW  vEMD,
          zPCHAR pchFileName,
          zVIEW  vSubtask )
{
   zVIEW    vDTE2;
   zPCHAR   pchName;
   zLONG    f = -1;
   zPCHAR   pch;
   zPCHAR   pch2;
   zCHAR    szLine[ 256 ];
   zLONG    nLth;
   zSHORT   RESULT;
   zSHORT   nRC;
   zLONG    lAttrLth;
   zLONG    lMaxFixedAttrLth;
   zLONG    lOverflowAttrLth;

   zCHAR    szMsg[ 512 ];

   // If TE_DBMS_Source entity doesn't exist, then nothing to generate.
   if ( CheckExistenceOfEntity( vDTE, "TE_DBMS_Source" ) != zCURSOR_SET )
      return( zCALL_ERROR );

   // Create copies of views so we can safely change the cursors.
   CreateViewFromViewForTask( &vDTE, vDTE, 0 );
   CreateViewFromViewForTask( &vDTE2, vDTE, 0 );
   CreateViewFromViewForTask( &vEMD, vEMD, 0 );

   GetIntegerFromAttribute( &lOverflowAttrLth, vDTE,
                            "TE_DBMS_Source", "OverflowAttrLth" );
   GetIntegerFromAttribute( &lMaxFixedAttrLth, vDTE,
                            "TE_DBMS_Source", "MaxFixedAttrLth" );
   if ( lMaxFixedAttrLth == 0 )
      lMaxFixedAttrLth = 32;

   // Generate the DDL file name and open it.
   GetStringFromAttribute( pchFileName + zstrlen( pchFileName ),
                           vDTE, "TE_DBMS_Source", "Name" );
   strcat_s( pchFileName, ".ddl" );
   if ( (f = SysOpenFile( vSubtask, pchFileName, COREFILE_WRITE )) < 0 )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   //=================================================================
   //
   // Generate Header information.
   //
   //=================================================================

   GetAddrForAttribute( &pchName, vDTE, "TE_DBMS_Source", "Name" );
   sprintf_s( szLine, "database %s [2048] {", pchName );

   SysWriteLine( vSubtask, f, szLine );
   SysWriteLine( vSubtask, f, "/*" );

   GetAddrForAttribute( &pch, vDTE, "TE_DBMS_Source", "Desc" );
   sprintf_s( szLine, "  %s", pch );
   SysWriteLine( vSubtask, f, szLine );
   SysWriteLine( vSubtask, f, "*/" );
   SysWriteLine( vSubtask, f, "" );

   sprintf_s( szLine, "  data file \"%s.d01\" contains", pchName );
   SysWriteLine( vSubtask, f, szLine );

   // If we have an Overflow length, then create an overflow record.
   if ( lOverflowAttrLth )
   {
      sprintf_s( szLine, "%*s %-*s,",
                (zSHORT) COLUMN_INDENT, " ",
                (zSHORT) MAX_COLUMNNAME_LTH, "ZOF_REC0" );
      SysWriteLine( vSubtask, f, szLine );
   }

   //=================================================================
   //
   // Generate Table names.
   //
   //=================================================================
   RESULT = SetCursorFirstEntity( vDTE, "TE_TablRec", "" );
   while ( RESULT >= zCURSOR_SET )
   {
      zPCHAR pchEntityName;

      GetAddrForAttribute( &pch, vDTE, "TE_TablRec", "Name" );
      if ( CheckExistenceOfEntity( vDTE, "ER_Entity" ) == zCURSOR_SET )
         GetAddrForAttribute( &pchEntityName, vDTE, "ER_Entity",  "Name" );
      else
         pchEntityName = "M-M correspondence table";

      RESULT = SetCursorNextEntity( vDTE, "TE_TablRec", "" );
      if ( RESULT >= zCURSOR_SET )
         sprintf_s( szLine, "%*s %-*s, %s %s %s",
                   (zSHORT) COLUMN_INDENT, " ",
                   (zSHORT) MAX_COLUMNNAME_LTH, pch,
                   COMMENT_START, pchEntityName, COMMENT_END );
      else
         sprintf_s( szLine, "%*s %-*s; %s %s %s",
                   (zSHORT) COLUMN_INDENT, " ",
                   (zSHORT) MAX_COLUMNNAME_LTH, pch,
                   COMMENT_START, pchEntityName, COMMENT_END );

      if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }
   }

   //=================================================================
   //
   // Generate Key file.
   //
   //=================================================================

   SysWriteLine( vSubtask, f, "" );
   sprintf_s( szLine, "  key  file \"%s.k01\" contains", pchName );
   SysWriteLine( vSubtask, f, szLine );

   szLine[ 0 ] = 0;
   RESULT = SetCursorFirstEntityByString( vDTE, "TE_TablRec", "DataOrRel",
                                          "D", 0 );
   while ( RESULT >= zCURSOR_SET )
   {
      RESULT = SetCursorFirstEntityByString( vDTE, "TE_FieldDataRel",
                                             "DataOrRelfieldOrSet", "D", 0 );
      while ( RESULT > zCURSOR_UNCHANGED  &&
              CompareAttributeToString( vDTE, "TE_FieldDataRel",
                                        "Key", "Y" ) != 0 )
      {
         RESULT = SetCursorNextEntityByString( vDTE, "TE_FieldDataRel",
                                               "DataOrRelfieldOrSet", "D", 0 );
      }

      if ( RESULT >= zCURSOR_SET  )
      {
         if ( szLine[ 0 ] )
         {
            strcat_s( szLine, zsizeof( szLine ), "," );
            if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
            {
               nRC = zCALL_ERROR;
               goto EndOfFunction;
            }
         }

         GetAddrForAttribute( &pch,  vDTE, "TE_TablRec",      "Name" );
         GetAddrForAttribute( &pch2, vDTE, "TE_FieldDataRel", "Name" );
         sprintf_s( szLine, "%*s %s.%s",
                   (zSHORT) COLUMN_INDENT, " ", pch, pch2 );
      }

      RESULT = SetCursorNextEntityByString( vDTE, "TE_TablRec",
                                            "DataOrRel", "D", 0 );
   }

   if ( szLine[ 0 ] )
   {
      strcat_s( szLine, zsizeof( szLine ), ";" );
      if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      SysWriteLine( vSubtask, f, "" );
   }

   //=================================================================
   //
   // Generate Overflow record.
   //
   //=================================================================
   if ( lOverflowAttrLth )
   {
      SysWriteLine( vSubtask, f, "record ZOF_REC0 {" );

      sprintf_s( szLine, "%*s db_addr ZOF_DBADDR;",
                (zSHORT) COLUMN_INDENT, " " );
      SysWriteLine( vSubtask, f, szLine );

      sprintf_s( szLine, "%*s char  ZOF_Data[ %ld ];",
                (zSHORT) COLUMN_INDENT, " ", lOverflowAttrLth );
      SysWriteLine( vSubtask, f, szLine );

      SysWriteLine( vSubtask, f, "}  /* Generated Overflow Record */" );
      SysWriteLine( vSubtask, f, "" );
   }

   //=================================================================
   //
   // Generate Entity records.
   //
   //=================================================================
   for ( RESULT = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
         RESULT > zCURSOR_UNCHANGED;
         RESULT = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
   {
      GetAddrForAttribute( &pch,  vDTE, "TE_TablRec", "Name" );

      if ( CheckExistenceOfEntity( vDTE, "ER_Entity" ) == zCURSOR_SET )
         GetAddrForAttribute( &pch2, vDTE, "ER_Entity",  "Name" );
      else
         pch2 = "M-M correspondence table";

      sprintf_s( szLine, "record %s %s For Entity %s %s {", pch,
                COMMENT_START, pch2, COMMENT_END );
      if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      //=================================================================
      //
      // Generate field statements.
      //
      //=================================================================
      for ( RESULT = SetCursorFirstEntityByString( vDTE, "TE_FieldDataRel",
                                                   "DataOrRelfieldOrSet",
                                                   "D", 0 );
            RESULT > zCURSOR_UNCHANGED;
            RESULT = SetCursorNextEntityByString( vDTE, "TE_FieldDataRel",
                                                  "DataOrRelfieldOrSet",
                                                  "D", 0 ) )
      {
         zCHAR  szDataType[ MAX_DATATYPE_LTH + 1 ];
         zPCHAR pchFieldName;

         GetAddrForAttribute( &pchFieldName, vDTE, "TE_FieldDataRel", "Name" );
         if ( CompareAttributeToString( vDTE, "TE_FieldDataRel",
                                        "Key", "Y" ) == 0 )
            strcpy_s( szDataType, zsizeof( szDataType ), "unique key " );
         else
            szDataType[ 0 ] = 0;

         GetAddrForAttribute( &pch, vDTE, "TE_FieldDataRel", "DataType" );
         switch ( *pch )
         {
            case zTYPE_STRING:
               strcat_s( szDataType, zsizeof( szDataType ), "char" );

               GetIntegerFromAttribute( &nLth, vDTE, "TE_FieldDataRel",
                                        "Length" );
               GetIntegerFromAttribute( &lAttrLth, vDTE, "ER_Attribute",
                                        "Lth" );
               if ( nLth > lMaxFixedAttrLth )
                  nLth = lMaxFixedAttrLth;

               sprintf_s( szLine, "%*s %*s %s[ %ld ]",
                         (zSHORT) COLUMN_INDENT, " ",
                         MAX_DATATYPE_LTH, szDataType, pchFieldName, nLth );

               // Raima treats a char field as a null-terminated string, i.e.
               // it ignores chars after the 0 byte.  If the length of the
               // current string is greater than the max length of strings,
               // then the string is stored as a blob which means the field
               // could contain a 0 byte.  To get Raima to read the entire
               // char field (as opposed to everything before the 0 byte) we
               // tell Raima the field is a 2-dim array where the 2nd
               // dimension is 1.  This doesn't change the storage size of the
               // char array but does force Raima to load the entire field.
               if ( lAttrLth >= lMaxFixedAttrLth )
                  strcat_s( szLine, zsizeof( szLine ), " [ 1 ]" );

               strcat_s( szLine, zsizeof( szLine ), ";" );
               break;

            case zTYPE_BLOB:
               sprintf_s( szLine, "%*s %*s %s[ %ld ] [ 1 ];",
                         (zSHORT) COLUMN_INDENT, " ",
                         MAX_DATATYPE_LTH, "char", pchFieldName,
                         lMaxFixedAttrLth );
               break;

            case zTYPE_DATETIME:
               strcat_s( szDataType, zsizeof( szDataType ), "int" );
               sprintf_s( szLine, "%*s %*s %s[ 3 ];",
                         (zSHORT) COLUMN_INDENT, " ",
                         MAX_DATATYPE_LTH, szDataType, pchFieldName );
               break;

            case zTYPE_INTEGER:
               strcat_s( szDataType, zsizeof( szDataType ), "long" );
               sprintf_s( szLine, "%*s %*s %s;",
                         (zSHORT) COLUMN_INDENT, " ",
                         MAX_DATATYPE_LTH, szDataType, pchFieldName );
               break;

            case zTYPE_DECIMAL:
               strcat_s( szDataType, zsizeof( szDataType ), "long double" );
               sprintf_s( szLine, "%*s %*s %s;",
                         (zSHORT) COLUMN_INDENT, " ",
                         MAX_DATATYPE_LTH, szDataType, pchFieldName );
               break;

            case 'N':
            case 'H':
               strcat_s( szDataType, zsizeof( szDataType ), "int" );
               sprintf_s( szLine, "%*s %*s %s;",
                         (zSHORT) COLUMN_INDENT, " ",
                         MAX_DATATYPE_LTH, szDataType, pchFieldName );
               break;
         }

         if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
         {
            nRC = zCALL_ERROR;
            goto EndOfFunction;
         }

      } // for each TE_FieldDataRel...

      SysWriteLine( vSubtask, f, "}" );
      SysWriteLine( vSubtask, f, "" );
   }

   //=================================================================
   //
   // Generate Set records.
   //
   //=================================================================
   for ( RESULT = SetCursorFirstEntityByString( vDTE, "TE_FieldDataRel",
                                                "DataOrRelfieldOrSet", "S",
                                                "TE_DBMS_Source" );
         RESULT > zCURSOR_UNCHANGED;
         RESULT = SetCursorNextEntityByString( vDTE, "TE_FieldDataRel",
                                               "DataOrRelfieldOrSet", "S",
                                               "TE_DBMS_Source" ) )
   {
      GetAddrForAttribute( &pch, vDTE, "TE_FieldDataRel", "Name" );
      sprintf_s( szLine, "set %s {", pch );
      if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      sprintf_s( szLine, "%*s order last;", (zSHORT) COLUMN_INDENT, " " );
      if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      SetCursorFirstEntityByEntityCsr( vEMD, "ER_RelLink",
                                       vDTE, "ER_RelLink", "EntpER_Model" );
      SetCursorFirstEntityByEntityCsr( vDTE2, "ER_Entity",
                                       vEMD, "ER_Entity", "TE_DBMS_Source" );

      GetAddrForAttribute( &pch, vDTE2, "TE_TablRec", "Name" );
      sprintf_s( szLine, "%*s owner %s;", (zSHORT) COLUMN_INDENT, " ", pch );
      if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      GetAddrForAttribute( &pch, vDTE, "TE_TablRec", "Name" );
      sprintf_s( szLine, "%*s member %s;", (zSHORT) COLUMN_INDENT, " ", pch );
      if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
      {
         nRC = zCALL_ERROR;
         goto EndOfFunction;
      }

      SysWriteLine( vSubtask, f, "}" );
      SysWriteLine( vSubtask, f, "" );
   }

   sprintf_s( szLine, "} %s database %s %s",
             COMMENT_START, pchName, COMMENT_END );

   if ( SysWriteLine( vSubtask, f, szLine ) < 0 )
   {
      nRC = zCALL_ERROR;
      goto EndOfFunction;
   }

   // If we get here, then everything is OK.
   nRC = 0;

EndOfFunction:
   if ( f != -1 )
      SysCloseFile( vDTE, f, 0 );

   DropView( vDTE );
   DropView( vDTE2 );
   DropView( vEMD );

   if ( nRC == 0 )
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "File " );
      strcat_s( szMsg, zsizeof( szMsg ), pchFileName );
      strcat_s( szMsg, zsizeof( szMsg ), " is created successfully!" );
     MB_SetMessage( vSubtask, 0, szMsg );
   }
   else
   {
      strcpy_s( szMsg, zsizeof( szMsg ), "Couldn't create file " );
      strcat_s( szMsg, zsizeof( szMsg ), pchFileName );
      SysMessageBox( "Generate DDL", szMsg, 0 );
   }

   return( nRC );
}

/*

   Sets the physical data type and lth for the current TE_FieldDataRel.  The
   Entity hierarchy looks like:

      TE_DBMS_Source
         TE_TableRec
            TE_FieldDataRel
               ER_Attribute
                  Domain

   If bSetDefault is TRUE, then we need to set the default data type depending
   on the data type for ER_Attribute/ER_Domain.

   If bSetDefault is FALSE, then we only need to set the length depending on
   the data type in TE_FieldDataRel.

*/
zSHORT OPERATION
SetDataType( zVIEW vDTE, zBOOL bSetDefault )
{
   zPCHAR pchDataType;
   zLONG  lLth;
   zLONG  lTemp;

   if ( bSetDefault )
   {
      // Set the default data type from the ER attribute domain.
      SetAttributeFromAttribute( vDTE, "TE_FieldDataRel", "DataType",
                                 vDTE, "Domain", "DataType" );
   }

   // Get the data type.
   GetAddrForAttribute( &pchDataType, vDTE, "TE_FieldDataRel", "DataType" );

   // Now set the length according to the physical data type.
   switch ( *pchDataType )
   {
      case zTYPE_STRING:
         // Get the length of the string.
         GetIntegerFromAttribute( &lLth, vDTE, "ER_Attribute", "Lth" );

         // If no length, then get the max length for the domain.
         if ( lLth == 0  )
            GetIntegerFromAttribute( &lLth, vDTE, "Domain", "MaxStringLth" );

         // Raima needs to store the null-terminator so...
         lLth += 1;

         // Find out what the maximum length for any field is.  If it's less
         // then the length of the current field, then reset the length of the
         // current field.  This will cause the db-handler to store these
         // strings as blobs.
         //
         // Note: someday we should change this to use a different value for
         // DataType.
         GetIntegerFromAttribute( &lTemp, vDTE, "TE_DBMS_Source",
                                  "MaxFixedAttrLth" );
         if ( lTemp == 0 )
            lTemp = 32;

         if ( lLth > lTemp )
            lLth = lTemp;

         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", lLth );

         break;

      case zTYPE_INTEGER:
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 4 );
         break;

      case zTYPE_DECIMAL:
         GetIntegerFromAttribute( &lLth, vDTE, "ER_Attribute", "Lth" );
         if ( lLth == 0  )
            lLth = sizeof( zDECIMAL );
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", lLth );
         break;

      case zTYPE_BLOB:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_DBMS_Source",
                                  "MaxFixedAttrLth" );
         if ( lLth == 0 )
            lLth = 32;
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", lLth );
         break;

      case zTYPE_DATETIME:
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 6 );
         break;

      default:
         TraceLineS( "(TE) Invalid Physical Data type = ", pchDataType );
         SysMessageBox( "Zeidon TE", "Invalid Physical Data type.", 1 );
         return( 0 );
   }

   return( 0 );

} // SetDataType

zSHORT OPERATION
LoadDataTypes( zVIEW vType )
{
   //
   // Following are standard types.
   //
   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "S" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "String" );

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "L" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "Integer" );

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "M" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "Decimal" );

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "T" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "Timestamp" );

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "B" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "Blob (Char array)" );

#if 0
   //
   // Following are DB-specific types.
   //
   CreateEntity( vType, "TE_DB_DataType", zPOS_LAST );
   SetAttributeFromString( vType, "TE_DB_DataType", "InternalValue", "V" );
   SetAttributeFromString( vType, "TE_DB_DataType", "ExternalValue",
                           "VarChar" );
#endif

   return( 0 );

} // LoadDataTypes

// Make sure that name doesn't match a reserved word.
zVOID LOCALOPER
ChangeReservedName( zPCHAR pchName )
{
   zSHORT   k, j;

   // List of reserved names is terminated by a empty string.
   for ( k = 0; szReservedName[ k ][ 0 ]; k++ )
   {
      j = zstrcmpi( szReservedName[ k ], pchName );
      if ( j == 0 )
      {
         zCHAR szTemp[ 100 ] = "z_";

         // Since we know that all the reserved words are at least 2 chars
         // shorter then the max column/table length, then don't worry about
         // compressing the name.
         strcat_s( szTemp, zsizeof( szTemp ), pchName );
         strcpy_s( pchName, szTemp );
         return;
      }

      // Reserved words are listed in alphabetical order.  If the compare
      // returned a value greater than 0, then pchName comes before the current
      // szReservedName, which means there cannot be a match.
      if ( j > 0 )
         return;
   }
}

/*
   Generates a valid SQLBase table or column name using an entity/attribute
   name as it's base.

   Note: vDTE not used in this implementation.
*/
zSHORT OPERATION
GenerateName( zVIEW  vDTE,
              zPCHAR pchName,
              zCHAR  cMetaType )
{
   static zSHORT nNameCount;   // Used to keep track of duplicate names.
   static zSHORT nMaxLth;      // Used to keep track of duplicate names.
   zCHAR szTemp[ 300 ];

   zPCHAR pch1;
   zPCHAR pch2;

   strcpy_s( szTemp, zsizeof( szTemp ), pchName );

   // Eliminate invalid chars.
   for ( pch1 = pch2 = pchName; *pch2; pch2++ )
   {
      // Ramia only allows alpha-numeric and '_'.
      if ( zisalnum( *pch2 ) || *pch2 == '_' )
         *pch1++ = *pch2;  // Copy valid char.
   }

   // Null-terminate string.
   *pch1 = 0;

   switch ( cMetaType )
   {
      case 'E':      // Meta type is Entity
         nNameCount = 1;
         nMaxLth = MAX_TABLENAME_LTH;
         break;

      case 'A':      // Meta type is Attribute
         nNameCount = 1;
         nMaxLth = MAX_COLUMNNAME_LTH;
         break;

      case 'S':      // Meta type is Relationship ('S' for Set).
         nNameCount = 1;
         nMaxLth = MAX_TABLENAME_LTH;
         break;

      case 'X':      // pchName is a duplicate, generate a new one.
      {
         zSHORT nLth;

         // When generating new names, we just tack on an incrementing
         // number.  For example, "ColName" becomes "ColName01", "ColName01"
         // becomes "ColName02", etc.

         nNameCount++;
         nLth = zstrlen( pchName );
         if ( nNameCount > 2 )
            nLth = nLth - 2;
         else
         if ( nLth > nMaxLth - 2 )
            nLth = nMaxLth - 2;

         sprintf_s( pchName + nLth, "%02d", nNameCount );

         if ( zstrlen( pchName ) == 1 )
         {
            TraceLineS( "Old name = ", szTemp );
            TraceLineS( "New name = ", pchName );
            SysMessageBox( "DGC", "Bad name", 1 );
         }

         // We know name is short enough and no reserved words contain numbers
         // so just return.
         return( 0 );
      }
   }

   // Compress the name if it needs it.
   UfCompressName( pchName,   // Original name.
                   pchName,   // New (shorter) name.
                   nMaxLth,   // Max length of string.
                   "",        // Remove embedded spaces.
                   "",        // Ignore '_' (for now).
                   "Ac",      // Remove all lower-case vowels.
                   "B_",      // Remove all '_' starting from back.
                   0 );       // Stop when the name is short enough.

   // Make sure generated name doesn't match a reserved word.
   ChangeReservedName( pchName );

   return( 0 );

} // GenerateName

/////////////////////////////////////////////////////////////////////////////

      ReadName

      Read a name from the db-Vista database dictionary file.  This function
      reads characters one at a time until:

         o The end of the name( a '\n' is encountered )
         o The end of the file.

      If EOF, then there is an error.  Otherwise return the name found.
      Note that SysReadLine cannot be used because it expects '\r\n' to
      terminate a line.

/////////////////////////////////////////////////////////////////////////////
zLONG LOCALOPER
ReadName( zLONG  hFile,
          zPCHAR pchName,
          zPLONG lPosition,
          zVIEW  vSubtask )
{
   zLONG nb;
   zLONG lCharCount = 0;

   // Read the next char from the dictionary file.
   nb = SysPositionFile( vSubtask, hFile, *lPosition );
   nb = SysReadFile( vSubtask, hFile, pchName + CharCount, 1 );

   // Loop until a '\n' is found or EOF occurs.
   while ( (nb == 1) && (pchName[ lCharCount ] != '\n') )
   {
      // Read the next char.
      nb = SysReadFile( vSubtask, hFile, pchName + (++CharCount), 1 );
     (*lPosition)++;
   }

   // If a char was not read on the last Read, then EOF was found--and it
   // shouldn't have been found.
   if ( nb != 1 )
   {
      MessageSend( vSubtask, "TE00110", "Technical Environment",
                   "Unexpected EOF while reading names.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
      SysCloseFile( vSubtask, hFile, 0 );
      return( zCALL_ERROR );
   }

   pchName[ CharCount ] = 0;
   (*lPosition)++;
   return( lCharCount );  // Return the length of the name found.

}  /* ReadName */

/*********************************************************************

      ImportDB_Data

      Open the database dictionary and read the RaimaDM information.  Only
      a few items are needed from the dictionary.  Info such as file tables,
      key tables, etc. are ignored.

      Note: In this implementation vEMD is not used.

/////////////////////////////////////////////////////////////////////////////
zSHORT OPERATION
ImportDB_Data( zVIEW vTE_View, zVIEW vEMD )
{
   zSHORT nRC;
   zCHAR  szDictionaryFile[ 100 ], szPath[ 200 ];
   zPCHAR pchDatabaseName;
   zCHAR  szWork[ 200 ], szName[ 50 ];
   zLONG  lNbrBytes;
   zLONG  hFile;
   zLONG  nb;
   zLONG  lFieldCnt;
   zLONG  k;
   zLONG  lRecId, lLastRecId;
   zLONG  lFieldPosition, lNamePosition;
   short  nOffsetToFirstField;
   zPCHAR szRecordName;

   // Raima datatypes:
   HeaderType  Header;
   FIELD_ENTRY Field;

   // Get the database name from KZOMEROO.
   GetAddrForAttribute( &pchDatabaseName, vTE_View, "TE_DBMS_Source", "Name" );

   // DictionaryFile = DatabaseName + ".DBD".
   strcpy_s( szDictionaryFile, zsizeof( szDictionaryFile ), pchDatabaseName );
   strcat_s( szDictionaryFile, zsizeof( szDictionaryFile ), ".DBD" );

   // Get the db-Vista database path from zeidon.ini.
   szPath[ 0 ] = 0;
   SysReadZeidonIni( -1, "[RaimaDM_dir]", pchDatabaseName, szPath );
   if ( szPath[ 0 ] == 0 )
   {
      MessageSend( vTE_View, "TE00111", "Technical Environment",
                   "Path for RaimaDM databases not specified in ZEIDON.INI",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
      return( zCALL_ERROR );
   }

   SysAppendcDirSep( szPath );
   strcat_s( szPath, szDictionaryFile );

   // Open db-vista database dictionary.
   hFile = SysOpenFile( vTE_View, szPath, COREFILE_READ );
   if ( hFile == -1 )
   {
      strcpy_s( szWork, zsizeof( szWork ), "DBVista Dictionary not found for database " );
      strcat_s( szWork, zsizeof( szWork ), pchDatabaseName );
      strcat_s( szWork, zsizeof( szWork ), ".\n \'" );
      strcat_s( szWork, zsizeof( szWork ), szPath );
      strcat_s( szWork, zsizeof( szWork ), "\' cannot be opened." );
      MessageSend( vTE_View, "TE00112", "Technical Environment",
                   szWork, zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
      return( zCALL_ERROR );
   }

   // Read header information from dictionary.
   lNbrBytes = SysReadFile( vTE_View, hFile,(zPCHAR) &Header, zsizeof( HeaderType ) );

   // Check to make sure that the correct # of bytes were read.
   if ( lNbrBytes != (zLONG) zsizeof( HeaderType ) )
   {
      MessageSend( vTE_View, "TE00113", "Technical Environment",
                   "Error reading header information.",
                   zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
      SysCloseFile( vTE_View, hFile, 0 );
      return( zCALL_ERROR );
   }

   // Check dbvista version.
   if ( zmemcmp( Header.dbver, "V3.00", 5 ) != 0 )
      MessageSend( vTE_View, "TE00114", "Technical Environment",
                   "db-Vista version other than V3.xx opened.\nPossible"
                   "compatability problems.  Proceed with caution.",
                    zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );

   // Skip over bytes to get to name information.
   lFieldPosition = zsizeof( HeaderType ) +
                   Header.size_ft  * zsizeof( FILE_ENTRY ) +
                   Header.size_rt  * zsizeof( RECORD_ENTRY );
   lNamePosition = zsizeof( HeaderType ) +
                   Header.size_ft  * zsizeof( FILE_ENTRY )   +
                   Header.size_rt  * zsizeof( RECORD_ENTRY ) +
                   Header.size_fd  * zsizeof( FIELD_ENTRY )  +
                   Header.size_st  * zsizeof( SET_ENTRY )    +
                   Header.size_mt  * zsizeof( MEMBER_ENTRY ) +
                   Header.size_srt * zsizeof( SORT_ENTRY )   +
                   Header.size_kt  * zsizeof( KEY_ENTRY );

   // Zero all record id's
   for ( nRC = SetCursorFirstEntity( vTE_View, "TE_TablRec", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vTE_View, "TE_TablRec", 0 ) )
   {
      SetAttributeFromInteger( vTE_View, "TE_TablRec", "DBMS_ID", 0 );
   }

   // Read record names.
   for ( k = 0; k < Header.size_rt; k++ )
   {
      // Read the next name from the dictionary file.
      nb = ReadName( hFile, szName, &lNamePosition, vTE_View );
      if ( nb > 0 && zstrcmp( szName, "ZOF_REC0" ) != 0 )
      {
         nRC = SetCursorFirstEntityByString( vTE_View, "TE_TablRec", "Name",
                                             szName, "TE_DBMS_Source" );
         if ( nRC < zCURSOR_SET )
         {
            strcpy_s( szWork, zsizeof( szWork ), "Record " );
            strcat_s( szWork, zsizeof( szWork ), szName );
            strcat_s( szWork, zsizeof( szWork ), " has no corresponding TE_TablRec.\n" );
            strcat_s( szWork, zsizeof( szWork ), "Import aborted." );
            MessageSend( vTE_View, "TE00115", "Technical Environment",
                         szWork,
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
            SysCloseFile( vTE_View, hFile, 0 );
            return( zCALL_ERROR );
         }

         SetAttributeFromInteger( vTE_View, "TE_TablRec", "DBMS_ID",
                                  (zLONG) (k + 10000) );
      }
      else
      {
         if ( zstrcmp( szName, "ZOF_REC0" ) != 0 )
         {
            return( zCALL_ERROR );     // Error reading names.
         }
      }
   }

   // Read field names and ids.
   lLastRecId = 0;
   for ( k = 0; k < Header.size_fd; k++ )
   {
      // Read the next name from the dictionary file.
      nb = ReadName( hFile, szName, &lNamePosition, vTE_View );
      if ( nb <= 0 )
         return( zCALL_ERROR );

      // Read Field record from dictionary.
      nb = SysPositionFile( vTE_View, hFile, lFieldPosition );
      nb = SysReadFile( vTE_View, hFile,
                        (zPCHAR) &Field, zsizeof( FIELD_ENTRY ) );
      lFieldPosition = lFieldPosition + zsizeof( FIELD_ENTRY );
      if ( nb != (zLONG) zsizeof( FIELD_ENTRY ) )
      {
         SysCloseFile( vTE_View, hFile, 0 );
         MessageSend( vTE_View, "TE00116", "Technical Environment",
                      "Error reading fields.",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
         return( zCALL_ERROR );
      }

      // If the record id for the field just read is not the same as the
      // record id of the last field, then position cursor on the new
      // TE_TablRec.
      lRecId = Field.fd_rec + 10000;
      TraceLineI( "fd_rec for field just read = ", lRecId );
      if ( lRecId != lLastRecId  &&
           zstrcmp( szName, "ZOF_DBADDR" ) != 0 &&
           zstrcmp( szName, "ZOF_DATA" ) != 0 )
      {
         SetCursorFirstEntityByInteger( vTE_View, "TE_TablRec",
                                        "DBMS_ID", lRecId, 0 );
         lLastRecId = lRecId;
         nOffsetToFirstField = Field.fd_ptr;
         lFieldCnt = 0;
         GetAddrForAttribute( &szRecordName, vTE_View, "TE_TablRec", "Name" );
      }

      if ( zstrcmp( szName, "ZOF_DBADDR" ) != 0 &&
           zstrcmp( szName, "ZOF_DATA" ) != 0 )
      {
         nRC = SetCursorFirstEntityByString( vTE_View, "TE_FieldDataRel",
                                             "Name", szName, 0 );
         if ( nRC < zCURSOR_SET )
         {
            sprintf_s( szWork, "Field \"%s.%s\" has no corresponding "
                      "TE_FieldDataRel.", szRecordName, szName );
            MessageSend( vTE_View, "TE00117", "Technical Environment",
                         szWork, zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
         }
         else
         {
            zLONG nLogicalLth;

            GetIntegerFromAttribute( &nLogicalLth, vTE_View,
                                     "TE_FieldDataRel", "Length" );
            // If the logical length is greater than the physical length, then
            // the field is considered a variable length field and may be
            // contained in the overflow record.  To do this, however, the field
            // must be at least 10 bytes to hold the overflow flag(4 bytes),
            // the field length(2 bytes) and the database pointer(4 bytes).
            // If the field is not 10 bytes, then issue error message and return.
            if ( nLogicalLth > Field.fd_len && Field.fd_len < 10 )
            {
               strcpy_s( szWork, zsizeof( szWork ), "Field \"" );
               strcat_s( szWork, zsizeof( szWork ), szRecordName );
               strcat_s( szWork, zsizeof( szWork ), "." );
               strcat_s( szWork, zsizeof( szWork ), szName );
               strcat_s( szWork, zsizeof( szWork ), "\" has a different length from it's "
                        "corresponding attribute and therefore must be at "
                        "least 10 bytes." );
               MessageSend( vTE_View, "TE00118", "Technical Environment",
                            szWork,
                            zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
               return( zCALL_ERROR );
            }

            SetAttributeFromInteger( vTE_View, "TE_FieldDataRel", "DBMS_ID",
                                     Field.fd_rec * 1000L + lFieldCnt );
            SetAttributeFromInteger( vTE_View, "TE_FieldDataRel", "Length",
                                     Field.fd_len );
            SetAttributeFromInteger( vTE_View, "TE_FieldDataRel", "Offset",
                                     Field.fd_ptr - nOffsetToFirstField );
         }
      }

      lFieldCnt++;

   }  // for (...)...

   // Read set names.
   for ( k = 0; k < Header.size_st; k++ )
   {
      // Read the next name from the dictionary file.
      nb = ReadName( hFile, szName, &lNamePosition, vTE_View );
      if ( nb > 0 )
      {
         nRC = SetCursorFirstEntityByString( vTE_View, "TE_FieldDataRel",
                                             "Name", szName, "TE_DBMS_Source" );
         if ( nRC < zCURSOR_SET )
         {
            strcpy_s( szWork, zsizeof( szWork ), "Set " );
            strcat_s( szWork, zsizeof( szWork ), szName );
            strcat_s( szWork, zsizeof( szWork ), " has no corresponding TE_FieldDataRel.\n" );
            strcat_s( szWork, zsizeof( szWork ), "Import aborted." );
            MessageSend( vTE_View, "TE00119", "Technical Environment",
                         szWork,
                         zMSGQ_OBJECT_CONSTRAINT_ERROR, 1 );
            SysCloseFile( vTE_View, hFile, 0 );
            return( zCALL_ERROR );
         }

         SetAttributeFromInteger( vTE_View, "TE_FieldDataRel", "DBMS_ID",
                                  k + 20000 );
      }
      else
         return( zCALL_ERROR );     // Error reading names.
   }

   SysCloseFile( vTE_View, hFile, 0 );

   return( 0 );

}  // ImportDB_Data
