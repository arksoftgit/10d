/////////////////////////////////////////////////////////////////////////////////
//
// KZHSQLXB.C - SQL DDL generator for all supported databases.
//
///////////////////////////// DEFINES ///////////////////////////////////////

/*
CHANGE LOG

2003.01.28  DGC
   Fixed bug.  Datetime lengths were accidentally being set to 4.

2003.01.02  DGC
   Added code for PostgreSQL.

2002.06.11  BL
   Modified BuildSyncDDL; if View vDB does not exists, return

2002.03.21  FH
    in DDL generation present "success" without a beep (not like an error)

2001.12.12  DGC  Z10
   Added code to create the DDL to alter the current DB to match the TE.

2001.07.05  DGC
   Bug fix reported by Phil: if the JOIN flag was turned on for an entity, all
   entities of the same ER Type also had their flags turned on.  Added a check
   for the rel link type.

2001.06.20  DGC
   Change argument list to SqlInitBoundAttrList( ).

2001.05.10  DGC
   Fixed a bug in BuildHook that was creating an infinite loop.

2001.04.03  DGC Z2000
   Code for Join stuff.

2001.02.06  RG  Z2000
   Fixed Bug R54630: New parameter in function BuildDDL and message
   DDL-file is build at the end of the function

2000.10.25  SR  Z2000 Length of path variables
   Modified the size of all filename and path variables in whole module
   because size of attributes ExecDir, MetaSrcDir and PgmSrcDir
   has been changed to 254 in datamodel.Adjust the size of messagetext
   variables.

2000.09.26  DGC Z2000
   Added ability to drop indexes and control what is being generated in the
   DDL.

2000.08.21  DGC Z2000
   Added logic for generating table owner.

2000.08.14  RG  Z2000
   Backed out previous change for now.

2000.05.15  RG  Z2000
    Bugfixing: Write the CREATE TABLE statement only if there are
               columns in a table
2000.05.12  RG  Z2000
If entityname and/or attributename are in brackets, we have to remove
the brackets for the DDL-command
2000.05.04  DGC  Z10
   Change signature of LoadEntity( ).

1999.10.13  DGC  10a
   Fixed bug in previous change.

1999.09.24  DGC  10a
   Added ability to override default max lengths.

1999.08.25  DGC  10a
   Changed 'MEMO' to 'LONGBINARY' for blob attributes in Access.

1999.03.08  DGC  10a
   Changed previous change to store dates (and just dates) as a date column
   for ODBC.

1999.03.08  DGC
   Made change to Access DB-Handler to store timestamps as a string.

1999.01.19  DGC
   Lot's of stuff for static SQL.

1999.01.11  DGC
   Only first index for table is unique.  All others are not.

*/

#define  KZSYSSVC_INCL
#define  KZMETA_INCL
#include <kzoengaa.h>
#include <zdrvropr.h>
#include "kzhsqlxa.h"
#include <stdio.h>
#include <ctype.h>

// Sqlite is almost exactly the same as MySQL so they share much of the same code.
#if defined( SQLITE )
   #define MYSQL 1
#endif

#if defined( ACCESS )

   #define CONTINUATION_STR      ""
   #define LINE_TERMINATOR       ";"
   #define MAX_TABLENAME_LTH     34
   #define MAX_COLUMNNAME_LTH    34
   #define MAX_DATATYPE_LTH      20
   #define COLUMN_INDENT         10
   #define COMMENT_START         "--"
   #define COMMENT_END           ""
   #define NOT_NULL_FIELD        "NOT NULL"
   #define NULL_FIELD            "        "
   #define ADD_COLUMN_STMT       "ADD COLUMN"
   #define DROP_COLUMN_STMT      "DROP COLUMN"
   #define COMMIT_STR            " "
   #define MAX_LTH_FOR_STRING    254

   // List of words that are reserved in SQLBASE.
   // Note: these MUST be listed in alphabetical order.
   zCHAR  *szReservedName[] =
                           {
                              "ABSOLUTE",           // SQLSERVER
                              "ACTION",             // SQLSERVER
                              "ADD",                // ACCESS
                            //"ADD",                // SQLSERVER
                              "ALL",                // ACCESS
                            //"ALL",                // SQLSERVER
                              "ALLOCATE",           // SQLSERVER
                              "ALPHANUMERIC",       // ACCESS
                              "ALTER",              // ACCESS
                            //"ALTER",              // SQLSERVER
                              "AND",                // ACCESS
                            //"AND",                // SQLSERVER
                              "ANY",                // ACCESS
                            //"ANY",                // SQLSERVER
                              "ARE",                // SQLSERVER
                              "AS",                 // ACCESS
                            //"AS",                 // SQLSERVER
                              "ASC",                // ACCESS
                            //"ASC",                // SQLSERVER
                              "ASSERTION",          // SQLSERVER
                              "AT",                 // SQLSERVER
                              "AUTHORIZATION",      // SQLSERVER
                              "AUTOINCREMENT",      // ACCESS
                              "AVG",                // ACCESS
                            //"AVG",                // SQLSERVER
                              "BEGIN",              // SQLSERVER
                              "BETWEEN",            // ACCESS
                            //"BETWEEN",            // SQLSERVER
                              "BINARY",             // ACCESS
                              "BIT",                // ACCESS
                              "BOOLEAN",            // ACCESS
                              "BOTH",               // SQLSERVER
                              "BREAK",              // SQLSERVER
                              "BROWSE",             // SQLSERVER
                              "BULK",               // SQLSERVER
                              "BY",                 // ACCESS
                            //"BY",                 // SQLSERVER
                              "BYTE",               // ACCESS
                              "CASCADE",            // SQLSERVER
                              "CASCADED",           // SQLSERVER
                              "CASE",               // SQLSERVER
                              "CAST",               // SQLSERVER
                              "CATALOG",            // SQLSERVER
                              "CHAR",               // ACCESS
                              "CHARACTER",          // ACCESS
                            //"CHARACTER",          // SQLSERVER
                              "CHARACTER_LENGTH",   // SQLSERVER
                              "CHAR_LENGTH",        // SQLSERVER
                              "CHECK",              // SQLSERVER
                              "CHECKPOINT",         // SQLSERVER
                              "CLOSE",              // SQLSERVER
                              "CLUSTERED",          // SQLSERVER
                              "COALESCE",           // SQLSERVER
                              "COLLATE",            // SQLSERVER
                              "COLLATION",          // SQLSERVER
                              "COLUMN",             // ACCESS
                            //"COLUMN",             // SQLSERVER
                              "COMMIT",             // SQLSERVER
                              "COMMITTED",          // SQLSERVER
                              "COMPUTE",            // SQLSERVER
                              "CONFIRM",            // SQLSERVER
                              "CONNECT",            // SQLSERVER
                              "CONNECTION",         // SQLSERVER
                              "CONSTRAINT",         // ACCESS
                            //"CONSTRAINT",         // SQLSERVER
                              "CONSTRAINTS",        // SQLSERVER
                              "CONTINUE",           // SQLSERVER
                              "CONTROLROW",         // SQLSERVER
                              "CONVERT",            // SQLSERVER
                              "CORRESPONDING",      // SQLSERVER
                              "COUNT",              // ACCESS
                            //"COUNT",              // SQLSERVER
                              "COUNTER",            // ACCESS
                              "CREATE",             // ACCESS
                            //"CREATE",             // SQLSERVER
                              "CROSS",              // SQLSERVER
                              "CURRENCY",           // ACCESS
                              "CURRENT",            // SQLSERVER
                              "CURRENT_DATE",       // SQLSERVER
                              "CURRENT_TIME",       // SQLSERVER
                              "CURRENT_TIMESTAMP",  // SQLSERVER
                              "CURRENT_USER",       // SQLSERVER
                              "CURSOR",             // SQLSERVER
                              "DATABASE",           // ACCESS
                            //"DATABASE",           // SQLSERVER
                              "DATE",               // ACCESS
                            //"DATE",               // SQLSERVER
                              "DATETIME",           // ACCESS
                            //"DATETIME",           // SQLSERVER
                              "DAY",                // SQLSERVER
                              "DBAREA",             // ACCESS
                              "DBCC",               // SQLSERVER
                              "DEALLOCATE",         // SQLSERVER
                              "DEBUG",              // SQLSERVER
                              "DECLARE",            // SQLSERVER
                              "DEFAULT",            // SQLSERVER
                              "DEFERRABLE",         // SQLSERVER
                              "DEFERRED",           // SQLSERVER
                              "DELETE",             // ACCESS
                            //"DELETE",             // SQLSERVER
                              "DESC",               // ACCESS
                            //"DESC",               // SQLSERVER
                              "DESCRIBE",           // SQLSERVER
                              "DESCRIPTOR",         // SQLSERVER
                              "DIAGNOSTICS",        // SQLSERVER
                              "DISALLOW",           // ACCESS
                              "DISCONNECT",         // SQLSERVER
                              "DISK",               // SQLSERVER
                              "DISTINCT",           // ACCESS
                            //"DISTINCT",           // SQLSERVER
                              "DISTINCTROW",        // ACCESS
                              "DISTRIBUTED",        // SQLSERVER
                              "DOMAIN",             // SQLSERVER
                              "DOUBLE",             // ACCESS
                            //"DOUBLE",             // SQLSERVER
                              "DROP",               // ACCESS
                            //"DROP",               // SQLSERVER
                              "DUMMY",              // SQLSERVER
                              "DUMP",               // SQLSERVER
                              "ELSE",               // SQLSERVER
                              "END",                // SQLSERVER
                              "END_EXEC",           // SQLSERVER
                              "EQV",                // ACCESS
                              "ERRLVL",             // SQLSERVER
                              "ERROREXIT",          // SQLSERVER
                              "ESCAPE",             // SQLSERVER
                              "EXCEPT",             // SQLSERVER
                              "EXCEPTION",          // SQLSERVER
                              "EXEC",               // SQLSERVER
                              "EXECUTE",            // SQLSERVER
                              "EXISTS",             // ACCESS
                            //"EXISTS",             // SQLSERVER
                              "EXIT",               // SQLSERVER
                              "EXPIREDATE",         // SQLSERVER
                              "EXTERNAL",           // SQLSERVER
                              "EXTRACT",            // SQLSERVER
                              "FALSE",              // SQLSERVER
                              "FETCH",              // SQLSERVER
                              "FILE",               // SQLSERVER
                              "FILLFACTOR",         // SQLSERVER
                              "FIRST",              // SQLSERVER
                              "FLOAT",              // ACCESS
                              "FLOAT4",             // ACCESS
                              "FLOAT8",             // ACCESS
                              "FLOPPY",             // SQLSERVER
                              "FOR",                // SQLSERVER
                              "FOREIGN",            // ACCESS
                            //"FOREIGN",            // SQLSERVER
                              "FROM",               // ACCESS
                            //"FROM",               // SQLSERVER
                              "FULL",               // SQLSERVER
                              "GET",                // SQLSERVER
                              "GETDEFAULT",         // SQLSERVER
                              "GLOBAL",             // SQLSERVER
                              "GOTO",               // SQLSERVER
                              "GRANT",              // SQLSERVER
                              "GROUP",              // ACCESS
                            //"GROUP",              // SQLSERVER
                              "GUID",               // ACCESS
                              "HAVING",             // ACCESS
                            //"HAVING",             // SQLSERVER
                              "HOLDLOCK",           // SQLSERVER
                              "HOUR",               // SQLSERVER
                              "IDENTITY",           // SQLSERVER
                              "IDENTITYCOL",        // SQLSERVER
                              "IDENTITY_INSERT",    // SQLSERVER
                              "IEEEDOUBLE",         // ACCESS
                              "IEEESINGLE",         // ACCESS
                              "IF",                 // SQLSERVER
                              "IGNORE",             // ACCESS
                              "IMMEDIATE",          // SQLSERVER
                              "IMP",                // ACCESS
                              "IN",                 // ACCESS
                            //"IN",                 // SQLSERVER
                              "INDEX",              // ACCESS
                            //"INDEX",              // SQLSERVER
                              "INITIALLY",          // SQLSERVER
                              "INNER",              // ACCESS
                            //"INNER",              // SQLSERVER
                              "INPUT",              // SQLSERVER
                              "INSENSITIVE",        // SQLSERVER
                              "INSERT",             // ACCESS
                            //"INSERT",             // SQLSERVER
                              "INT",                // ACCESS
                              "INTEGER",            // ACCESS
                              "INTEGER1",           // ACCESS
                              "INTEGER2",           // ACCESS
                              "INTERSECT",          // SQLSERVER
                              "INTERVAL",           // SQLSERVER
                              "INTO",               // ACCESS
                            //"INTO",               // SQLSERVER
                              "IS",                 // ACCESS
                            //"IS",                 // SQLSERVER
                              "ISOLATION",          // SQLSERVER
                              "JOIN",               // ACCESS
                            //"JOIN",               // SQLSERVER
                              "KEY",                // ACCESS
                            //"KEY",                // SQLSERVER
                              "KILL",               // SQLSERVER
                              "LAST",               // SQLSERVER
                              "LEADING",            // SQLSERVER
                              "LEFT",               // ACCESS
                            //"LEFT",               // SQLSERVER
                              "LEVEL",              // ACCESS
                            //"LEVEL",              // SQLSERVER
                              "LIKE",               // ACCESS
                            //"LIKE",               // SQLSERVER
                              "LINENO",             // SQLSERVER
                              "LOAD",               // SQLSERVER
                              "LOCAL",              // SQLSERVER
                              "LOGICAL",            // ACCESS
                              "LOGICAL1",           // ACCESS
                              "LONG",               // ACCESS
                              "LONGBINARY",         // ACCESS
                              "LONGTEXT",           // ACCESS
                              "MATCH",              // SQLSERVER
                              "MAX",                // ACCESS
                            //"MAX",                // SQLSERVER
                              "MEMO",               // ACCESS
                              "MIN",                // ACCESS
                            //"MIN",                // SQLSERVER
                              "MINUTE",             // SQLSERVER
                              "MIRROREXIT",         // SQLSERVER
                              "MOD",                // ACCESS
                              "MONEY",              // ACCESS
                              "MONTH",              // SQLSERVER
                              "NAMES",              // SQLSERVER
                              "NATIONAL",           // SQLSERVER
                              "NATURAL",            // SQLSERVER
                              "NCHAR",              // SQLSERVER
                              "NEXT",               // SQLSERVER
                              "NEXTLOG",            // ACCESS
                              "NO",                 // ACCESS
                            //"NO",                 // SQLSERVER
                              "NOCHECK",            // SQLSERVER
                              "NONCLUSTERED",       // SQLSERVER
                              "NOT",                // ACCESS
                            //"NOT",                // SQLSERVER
                              "NOTE",               // ACCESS
                              "NULL",               // ACCESS
                            //"NULL",               // SQLSERVER
                              "NULLIF",             // SQLSERVER
                              "NUMBER",             // ACCESS
                              "NUMERIC",            // ACCESS
                              "OCTET_LENGTH",       // SQLSERVER
                              "OF",                 // SQLSERVER
                              "OFF",                // SQLSERVER
                              "OFFSETS",            // SQLSERVER
                              "OLEOBJECT",          // ACCESS
                              "ON",                 // ACCESS
                            //"ON",                 // SQLSERVER
                              "ONCE",               // SQLSERVER
                              "ONLY",               // SQLSERVER
                              "OPEN",               // SQLSERVER
                              "OPTION",             // ACCESS
                            //"OPTION",             // SQLSERVER
                              "OR",                 // ACCESS
                            //"OR",                 // SQLSERVER
                              "ORDER",              // ACCESS
                            //"ORDER",              // SQLSERVER
                              "OUTER",              // ACCESS
                            //"OUTER",              // SQLSERVER
                              "OUTPUT",             // SQLSERVER
                              "OVER",               // SQLSERVER
                              "OVERLAPS",           // SQLSERVER
                              "OWNERACCESS",        // ACCESS
                              "PAD",                // SQLSERVER
                              "PARAMETERS",         // ACCESS
                              "PARTIAL",            // SQLSERVER
                              "PERCENT",            // ACCESS
                              "PERM",               // SQLSERVER
                              "PERMANENT",          // SQLSERVER
                              "PIPE",               // SQLSERVER
                              "PIVOT",              // ACCESS
                              "PLAN",               // SQLSERVER
                              "POSITION",           // SQLSERVER
                              "PRECISION",          // SQLSERVER
                              "PREPARE",            // SQLSERVER
                              "PRESEVE",            // SQLSERVER
                              "PRIMARY",            // ACCESS
                            //"PRIMARY",            // SQLSERVER
                              "PRINT",              // SQLSERVER
                              "PRIOR",              // SQLSERVER
                              "PRIVILEGES",         // SQLSERVER
                              "PROC",               // SQLSERVER
                              "PROCEDURE",          // ACCESS
                            //"PROCEDURE",          // SQLSERVER
                              "PROCESSEXIT",        // SQLSERVER
                              "PUBLIC",             // SQLSERVER
                              "RAISERROR",          // SQLSERVER
                              "READ",               // SQLSERVER
                              "READTEXT",           // SQLSERVER
                              "REAL",               // ACCESS
                              "RECONFIGURE",        // SQLSERVER
                              "REFERENCES",         // ACCESS
                            //"REFERENCES",         // SQLSERVER
                              "RELATIVE",           // SQLSERVER
                              "REPEATABLE",         // SQLSERVER
                              "REPLICATION",        // SQLSERVER
                              "RESTRICT",           // SQLSERVER
                              "RETAINDAY",          // SQLSERVER
                              "RETURN",             // SQLSERVER
                              "REVOKE",             // SQLSERVER
                              "RIGHT",              // ACCESS
                            //"RIGHT",              // SQLSERVER
                              "ROLLBACK",           // SQLSERVER
                              "ROWCOUNT",           // SQLSERVER
                              "ROWS",               // SQLSERVER
                              "RULE",               // SQLSERVER
                              "SAVE",               // SQLSERVER
                              "SCHEMA",             // SQLSERVER
                              "SCROLL",             // SQLSERVER
                              "SECOND",             // SQLSERVER
                              "SELECT",             // ACCESS
                            //"SELECT",             // SQLSERVER
                              "SERIALIZABLE",       // SQLSERVER
                              "SESSION",            // SQLSERVER
                              "SESSION_USER",       // SQLSERVER
                              "SET",                // ACCESS
                            //"SET",                // SQLSERVER
                              "SETUSER",            // SQLSERVER
                              "SHORT",              // ACCESS
                              "SHUTDOWN",           // SQLSERVER
                              "SINGLE",             // ACCESS
                              "SIZE",               // SQLSERVER
                              "SMALLINT",           // ACCESS
                              "SOME",               // ACCESS
                            //"SOME",               // SQLSERVER
                              "SPACE",              // SQLSERVER
                              "SQLSTATE",           // SQLSERVER
                              "STATISTICS",         // SQLSERVER
                              "STDEV",              // ACCESS
                              "STDEVP",             // ACCESS
                              "STRING",             // ACCESS
                              "SUM",                // ACCESS
                            //"SUM",                // SQLSERVER
                              "SYSTEM_USER",        // SQLSERVER
                              "TABLE",              // ACCESS
                            //"TABLE",              // SQLSERVER
                              "TABLEID",            // ACCESS
                              "TAPE",               // SQLSERVER
                              "TEMP",               // SQLSERVER
                              "TEMPORARY",          // SQLSERVER
                              "TEXT",               // ACCESS
                              "TEXTSIZE",           // SQLSERVER
                              "THEN",               // SQLSERVER
                              "TIME",               // ACCESS
                            //"TIME",               // SQLSERVER
                              "TIMESTAMP",          // ACCESS
                            //"TIMESTAMP",          // SQLSERVER
                              "TIMEZONE_HOUR",      // SQLSERVER
                              "TIMEZONE_MINUTE",    // SQLSERVER
                              "TO",                 // ACCESS
                            //"TO",                 // SQLSERVER
                              "TOP",                // ACCESS
                              "TRAILING",           // SQLSERVER
                              "TRAN",               // SQLSERVER
                              "TRANSACTION",        // SQLSERVER
                              "TRANSFORM",          // ACCESS
                              "TRANSLATE",          // SQLSERVER
                              "TRANSLATION",        // SQLSERVER
                              "TRIGGER",            // SQLSERVER
                              "TRUE",               // SQLSERVER
                              "TRUNCATE",           // SQLSERVER
                              "TSEQUAL",            // SQLSERVER
                              "UNCOMMITTED",        // SQLSERVER
                              "UNION",              // ACCESS
                            //"UNION",              // SQLSERVER
                              "UNIQUE",             // ACCESS
                            //"UNIQUE",             // SQLSERVER
                              "UNKNOWN",            // SQLSERVER
                              "UPDATE",             // ACCESS
                            //"UPDATE",             // SQLSERVER
                              "UPDATETEXT",         // SQLSERVER
                              "USAGE",              // SQLSERVER
                              "USE",                // SQLSERVER
                              "USER",               // SQLSERVER
                              "USING",              // SQLSERVER
                              "VALUE",              // ACCESS
                            //"VALUE",              // SQLSERVER
                              "VALUES",             // ACCESS
                            //"VALUES",             // SQLSERVER
                              "VAR",                // ACCESS
                              "VARBINARY",          // ACCESS
                              "VARCHAR",            // ACCESS
                              "VARP",               // ACCESS
                              "VARYING",            // SQLSERVER
                              "VIEW",               // SQLSERVER
                              "VOLUME",             // SQLSERVER
                              "WAITFOR",            // SQLSERVER
                              "WHEN",               // SQLSERVER
                              "WHERE",              // ACCESS
                            //"WHERE",              // SQLSERVER
                              "WHILE",              // SQLSERVER
                              "WITH",               // ACCESS
                            //"WITH",               // SQLSERVER
                              "WORK",               // SQLSERVER
                              "WRITE",              // SQLSERVER
                              "WRITETEXT",          // SQLSERVER
                              "XOR",                // ACCESS
                              "YEAR",               // SQLSERVER
                              "YESNO",              // ACCESS
                              "ZONE",               // SQLSERVER
                              "\0" };     // Must be last -- terminates list.

#elif defined( DB2 )

   #include "kzhsqlgp.h"

   #define CONTINUATION_STR      ""
   #define LINE_TERMINATOR       ";"
   #define MAX_TABLENAME_LTH     18
   #define MAX_COLUMNNAME_LTH    18
   #define MAX_DATATYPE_LTH      20
   #define COLUMN_INDENT         10
   #define COMMENT_START         "--"
   #define COMMENT_END           ""
   #define NOT_NULL_FIELD        " NOT NULL"
   #define NULL_FIELD            "         "
   #define ADD_COLUMN_STMT       "ADD COLUMN"
   #define DROP_COLUMN_STMT      "DROP COLUMN"
   #define COMMIT_STR            "COMMIT;"
   #define CREATE_DB             1
   #define MAX_LTH_FOR_STRING    4000

   // List of words that are reserved in SQLBASE.
   // Note: these MUST be listed in alphabetical order.
   zCHAR  *szReservedName[] =
                           {
                              "ADD",
                              "ADJUSTING",
                              "ALL",
                              "ALTER",
                              "AND",
                              "ANY",
                              "AS",
                              "ASC",
                              "AVG",
                              "BETWEEN",
                              "BY",
                              "CASCADE",
                              "CHAR",
                              "CHARACTER",
                              "CHECK",
                              "CLUSTERED",
                              "COLUMN",
                              "COMMENT",
                              "COMMIT",
                              "COMPUTE",
                              "CONNECT",
                              "COUNT",
                              "CREATE",
                              "CURRENT",
                              "DATABASE",
                              "DATE",
                              "DATETIME",
                              "DAY",
                              "DAYS",
                              "DBA",
                              "DBAREA",
                              "DEC",
                              "DECIMAL",
                              "DEFAULT",
                              "DEINSTALL",
                              "DELETE",
                              "DESC",
                              "DIRECT",
                              "DISTINCT",
                              "DOUBLE",
                              "DROP",
                              "EXISTS",
                              "FLOAT",
                              "FOR",
                              "FOREIGN",
                              "FROM",
                              "GRANT",
                              "GROUP",
                              "HASHED",
                              "HAVING",
                              "HOUR",
                              "HOURS",
                              "IDENTIFIED",
                              "IN",
                              "INDEX",
                              "INSERT",
                              "INSTALL",
                              "INT",
                              "INTEGER",
                              "INTO",
                              "IS",
                              "KEY",
                              "LABEL",
                              "LAST",
                              "LIKE",
                              "LOG",
                              "LONG",
                              "MAX",
                              "MICROSECOND",
                              "MICROSECONDS",
                              "MIN",
                              "MINUTE",
                              "MINUTES",
                              "MODIFY",
                              "MONTH",
                              "MONTHS",
                              "NEXTLOG",
                              "NOT",
                              "NULL",
                              "NUMBER",
                              "OF",
                              "ON",
                              "OPTION",
                              "OR",
                              "ORDER",
                              "PASSWORD",
                              "PCTFREE",
                              "POST",
                              "PRECISION",
                              "PRIMARY",
                              "PUBLIC",
                              "REAL",
                              "REFERENCES",
                              "RENAME",
                              "RESOURCE",
                              "RESTRICT",
                              "REVOKE",
                              "ROLLBACK",
                              "ROWCOUNT",
                              "ROWID",
                              "ROWS",
                              "SAVEPOINT",
                              "SECOND",
                              "SECONDS",
                              "SELECT",
                              "SET",
                              "SIZE",
                              "SMALLINT",
                              "STATISTICS",
                              "STOGROUP",
                              "SUM",
                              "SYNONYM",
                              "SYSDATE",
                              "SYSDATETIME",
                              "SYSTEM",
                              "SYSTIME",
                              "SYSTIMEZONE",
                              "TABLE",
                              "TIME",
                              "TIMESTAMP",
                              "TIMEZONE",
                              "TO",
                              "UNION",
                              "UNIQUE",
                              "UPDATE",
                              "USER",
                              "USERERROR",
                              "USING",
                              "VALUES",
                              "VARCHAR",
                              "VIEW",
                              "WAIT",
                              "WHERE",
                              "WITH",
                              "WORK",
                              "YEAR",
                              "YEARS",
                              "\0" };     // Must be last -- terminates list.

   // Global variable used to determine indentation on SQL commands.
   g_nIndent;

#elif defined( SQLITE ) // This needs to go ahead of MYSQL.

   #define CONTINUATION_STR      ""
   #define LINE_TERMINATOR       ";"
   #define COLUMN_INDENT         10
   #define COMMENT_START         "/*"
   #define COMMENT_END           "*/"
   #define NOT_NULL_FIELD        "NOT NULL"
   #define NULL_FIELD            "NULL    "
   #define ADD_COLUMN_STMT       "ADD"
   #define DROP_COLUMN_STMT      "DROP COLUMN"
   #define MAX_TABLENAME_LTH     64
   #define MAX_COLUMNNAME_LTH    64
   #define MAX_DATATYPE_LTH      20
   #define COMMIT_STR            ""
   #define COLUMN_INDENT         10
   #define CREATE_DB             0
   #define GRANT_ALL             0
   #define MAX_LTH_FOR_STRING    254

   // List of words that are reserved in SQL Server.
   // Note: these MUST be listed in alphabetical order.
   zCHAR  *szReservedName[] =
                           {
                              "ABSOLUTE",           // SQLSERVER
                              "ACTION",             // SQLSERVER
                              "ADD",                // ACCESS
                            //"ADD",                // SQLSERVER
                              "ALL",                // ACCESS
                            //"ALL",                // SQLSERVER
                              "ALLOCATE",           // SQLSERVER
                              "ALPHANUMERIC",       // ACCESS
                              "ALTER",              // ACCESS
                            //"ALTER",              // SQLSERVER
                              "AND",                // ACCESS
                            //"AND",                // SQLSERVER
                              "ANY",                // ACCESS
                            //"ANY",                // SQLSERVER
                              "ARE",                // SQLSERVER
                              "AS",                 // ACCESS
                            //"AS",                 // SQLSERVER
                              "ASC",                // ACCESS
                            //"ASC",                // SQLSERVER
                              "ASSERTION",          // SQLSERVER
                              "AT",                 // SQLSERVER
                              "AUTHORIZATION",      // SQLSERVER
                              "AUTOINCREMENT",      // ACCESS
                              "AVG",                // ACCESS
                            //"AVG",                // SQLSERVER
                              "BEGIN",              // SQLSERVER
                              "BETWEEN",            // ACCESS
                            //"BETWEEN",            // SQLSERVER
                              "BINARY",             // ACCESS
                              "BIT",                // ACCESS
                              "BOOLEAN",            // ACCESS
                              "BOTH",               // SQLSERVER
                              "BREAK",              // SQLSERVER
                              "BROWSE",             // SQLSERVER
                              "BULK",               // SQLSERVER
                              "BY",                 // ACCESS
                            //"BY",                 // SQLSERVER
                              "BYTE",               // ACCESS
                              "CASCADE",            // SQLSERVER
                              "CASCADED",           // SQLSERVER
                              "CASE",               // SQLSERVER
                              "CAST",               // SQLSERVER
                              "CATALOG",            // SQLSERVER
                              "CHAR",               // ACCESS
                              "CHARACTER",          // ACCESS
                            //"CHARACTER",          // SQLSERVER
                              "CHARACTER_LENGTH",   // SQLSERVER
                              "CHAR_LENGTH",        // SQLSERVER
                              "CHECK",              // SQLSERVER
                              "CHECKPOINT",         // SQLSERVER
                              "CLOSE",              // SQLSERVER
                              "CLUSTERED",          // SQLSERVER
                              "COALESCE",           // SQLSERVER
                              "COLLATE",            // SQLSERVER
                              "COLLATION",          // SQLSERVER
                              "COLUMN",             // ACCESS
                            //"COLUMN",             // SQLSERVER
                              "COMMIT",             // SQLSERVER
                              "COMMITTED",          // SQLSERVER
                              "COMPUTE",            // SQLSERVER
                              "CONFIRM",            // SQLSERVER
                              "CONNECT",            // SQLSERVER
                              "CONNECTION",         // SQLSERVER
                              "CONSTRAINT",         // ACCESS
                            //"CONSTRAINT",         // SQLSERVER
                              "CONSTRAINTS",        // SQLSERVER
                              "CONTINUE",           // SQLSERVER
                              "CONTROLROW",         // SQLSERVER
                              "CONVERT",            // SQLSERVER
                              "CORRESPONDING",      // SQLSERVER
                              "COUNT",              // ACCESS
                            //"COUNT",              // SQLSERVER
                              "COUNTER",            // ACCESS
                              "CREATE",             // ACCESS
                            //"CREATE",             // SQLSERVER
                              "CROSS",              // SQLSERVER
                              "CURRENCY",           // ACCESS
                              "CURRENT",            // SQLSERVER
                              "CURRENT_DATE",       // SQLSERVER
                              "CURRENT_TIME",       // SQLSERVER
                              "CURRENT_TIMESTAMP",  // SQLSERVER
                              "CURRENT_USER",       // SQLSERVER
                              "CURSOR",             // SQLSERVER
                              "DATABASE",           // ACCESS
                            //"DATABASE",           // SQLSERVER
                              "DATE",               // ACCESS
                            //"DATE",               // SQLSERVER
                              "DATETIME",           // ACCESS
                            //"DATETIME",           // SQLSERVER
                              "DAY",                // SQLSERVER
                              "DBAREA",             // ACCESS
                              "DBCC",               // SQLSERVER
                              "DEALLOCATE",         // SQLSERVER
                              "DEBUG",              // SQLSERVER
                              "DECLARE",            // SQLSERVER
                              "DEFAULT",            // SQLSERVER
                              "DEFERRABLE",         // SQLSERVER
                              "DEFERRED",           // SQLSERVER
                              "DELETE",             // ACCESS
                            //"DELETE",             // SQLSERVER
                              "DESC",               // ACCESS
                            //"DESC",               // SQLSERVER
                              "DESCRIBE",           // SQLSERVER
                              "DESCRIPTOR",         // SQLSERVER
                              "DIAGNOSTICS",        // SQLSERVER
                              "DISALLOW",           // ACCESS
                              "DISCONNECT",         // SQLSERVER
                              "DISK",               // SQLSERVER
                              "DISTINCT",           // ACCESS
                            //"DISTINCT",           // SQLSERVER
                              "DISTINCTROW",        // ACCESS
                              "DISTRIBUTED",        // SQLSERVER
                              "DOMAIN",             // SQLSERVER
                              "DOUBLE",             // ACCESS
                            //"DOUBLE",             // SQLSERVER
                              "DROP",               // ACCESS
                            //"DROP",               // SQLSERVER
                              "DUMMY",              // SQLSERVER
                              "DUMP",               // SQLSERVER
                              "ELSE",               // SQLSERVER
                              "END",                // SQLSERVER
                              "END_EXEC",           // SQLSERVER
                              "EQV",                // ACCESS
                              "ERRLVL",             // SQLSERVER
                              "ERROREXIT",          // SQLSERVER
                              "ESCAPE",             // SQLSERVER
                              "EXCEPT",             // SQLSERVER
                              "EXCEPTION",          // SQLSERVER
                              "EXEC",               // SQLSERVER
                              "EXECUTE",            // SQLSERVER
                              "EXISTS",             // ACCESS
                            //"EXISTS",             // SQLSERVER
                              "EXIT",               // SQLSERVER
                              "EXPIREDATE",         // SQLSERVER
                              "EXTERNAL",           // SQLSERVER
                              "EXTRACT",            // SQLSERVER
                              "FALSE",              // SQLSERVER
                              "FETCH",              // SQLSERVER
                              "FILE",               // SQLSERVER
                              "FILLFACTOR",         // SQLSERVER
                              "FIRST",              // SQLSERVER
                              "FLOAT",              // ACCESS
                              "FLOAT4",             // ACCESS
                              "FLOAT8",             // ACCESS
                              "FLOPPY",             // SQLSERVER
                              "FOR",                // SQLSERVER
                              "FOREIGN",            // ACCESS
                            //"FOREIGN",            // SQLSERVER
                              "FROM",               // ACCESS
                            //"FROM",               // SQLSERVER
                              "FULL",               // SQLSERVER
                              "GET",                // SQLSERVER
                              "GETDEFAULT",         // SQLSERVER
                              "GLOBAL",             // SQLSERVER
                              "GOTO",               // SQLSERVER
                              "GRANT",              // SQLSERVER
                              "GROUP",              // ACCESS
                            //"GROUP",              // SQLSERVER
                              "GUID",               // ACCESS
                              "HAVING",             // ACCESS
                            //"HAVING",             // SQLSERVER
                              "HOLDLOCK",           // SQLSERVER
                              "HOUR",               // SQLSERVER
                              "IDENTITY",           // SQLSERVER
                              "IDENTITYCOL",        // SQLSERVER
                              "IDENTITY_INSERT",    // SQLSERVER
                              "IEEEDOUBLE",         // ACCESS
                              "IEEESINGLE",         // ACCESS
                              "IF",                 // SQLSERVER
                              "IGNORE",             // ACCESS
                              "IMMEDIATE",          // SQLSERVER
                              "IMP",                // ACCESS
                              "IN",                 // ACCESS
                            //"IN",                 // SQLSERVER
                              "INDEX",              // ACCESS
                            //"INDEX",              // SQLSERVER
                              "INITIALLY",          // SQLSERVER
                              "INNER",              // ACCESS
                            //"INNER",              // SQLSERVER
                              "INPUT",              // SQLSERVER
                              "INSENSITIVE",        // SQLSERVER
                              "INSERT",             // ACCESS
                            //"INSERT",             // SQLSERVER
                              "INT",                // ACCESS
                              "INTEGER",            // ACCESS
                              "INTEGER1",           // ACCESS
                              "INTEGER2",           // ACCESS
                              "INTERSECT",          // SQLSERVER
                              "INTERVAL",           // SQLSERVER
                              "INTO",               // ACCESS
                            //"INTO",               // SQLSERVER
                              "IS",                 // ACCESS
                            //"IS",                 // SQLSERVER
                              "ISOLATION",          // SQLSERVER
                              "JOIN",               // ACCESS
                            //"JOIN",               // SQLSERVER
                              "KEY",                // ACCESS
                            //"KEY",                // SQLSERVER
                              "KILL",               // SQLSERVER
                              "LAST",               // SQLSERVER
                              "LEADING",            // SQLSERVER
                              "LEFT",               // ACCESS
                            //"LEFT",               // SQLSERVER
                              "LEVEL",              // ACCESS
                            //"LEVEL",              // SQLSERVER
                              "LIKE",               // ACCESS
                            //"LIKE",               // SQLSERVER
                              "LINENO",             // SQLSERVER
                              "LOAD",               // SQLSERVER
                              "LOCAL",              // SQLSERVER
                              "LOGICAL",            // ACCESS
                              "LOGICAL1",           // ACCESS
                              "LONG",               // ACCESS
                              "LONGBINARY",         // ACCESS
                              "LONGTEXT",           // ACCESS
                              "MATCH",              // SQLSERVER
                              "MAX",                // ACCESS
                            //"MAX",                // SQLSERVER
                              "MEMO",               // ACCESS
                              "MIN",                // ACCESS
                            //"MIN",                // SQLSERVER
                              "MINUTE",             // SQLSERVER
                              "MIRROREXIT",         // SQLSERVER
                              "MOD",                // ACCESS
                              "MONEY",              // ACCESS
                              "MONTH",              // SQLSERVER
                              "NAMES",              // SQLSERVER
                              "NATIONAL",           // SQLSERVER
                              "NATURAL",            // SQLSERVER
                              "NCHAR",              // SQLSERVER
                              "NEXT",               // SQLSERVER
                              "NEXTLOG",            // ACCESS
                              "NO",                 // ACCESS
                            //"NO",                 // SQLSERVER
                              "NOCHECK",            // SQLSERVER
                              "NONCLUSTERED",       // SQLSERVER
                              "NOT",                // ACCESS
                            //"NOT",                // SQLSERVER
                              "NOTE",               // ACCESS
                              "NULL",               // ACCESS
                            //"NULL",               // SQLSERVER
                              "NULLIF",             // SQLSERVER
                              "NUMBER",             // ACCESS
                              "NUMERIC",            // ACCESS
                              "OCTET_LENGTH",       // SQLSERVER
                              "OF",                 // SQLSERVER
                              "OFF",                // SQLSERVER
                              "OFFSETS",            // SQLSERVER
                              "OLEOBJECT",          // ACCESS
                              "ON",                 // ACCESS
                            //"ON",                 // SQLSERVER
                              "ONCE",               // SQLSERVER
                              "ONLY",               // SQLSERVER
                              "OPEN",               // SQLSERVER
                              "OPTION",             // ACCESS
                            //"OPTION",             // SQLSERVER
                              "OR",                 // ACCESS
                            //"OR",                 // SQLSERVER
                              "ORDER",              // ACCESS
                            //"ORDER",              // SQLSERVER
                              "OUTER",              // ACCESS
                            //"OUTER",              // SQLSERVER
                              "OUTPUT",             // SQLSERVER
                              "OVER",               // SQLSERVER
                              "OVERLAPS",           // SQLSERVER
                              "OWNERACCESS",        // ACCESS
                              "PAD",                // SQLSERVER
                              "PARAMETERS",         // ACCESS
                              "PARTIAL",            // SQLSERVER
                              "PERCENT",            // ACCESS
                              "PERM",               // SQLSERVER
                              "PERMANENT",          // SQLSERVER
                              "PIPE",               // SQLSERVER
                              "PIVOT",              // ACCESS
                              "PLAN",               // SQLSERVER
                              "POSITION",           // SQLSERVER
                              "PRECISION",          // SQLSERVER
                              "PREPARE",            // SQLSERVER
                              "PRESEVE",            // SQLSERVER
                              "PRIMARY",            // ACCESS
                            //"PRIMARY",            // SQLSERVER
                              "PRINT",              // SQLSERVER
                              "PRIOR",              // SQLSERVER
                              "PRIVILEGES",         // SQLSERVER
                              "PROC",               // SQLSERVER
                              "PROCEDURE",          // ACCESS
                            //"PROCEDURE",          // SQLSERVER
                              "PROCESSEXIT",        // SQLSERVER
                              "PUBLIC",             // SQLSERVER
                              "RAISERROR",          // SQLSERVER
                              "READ",               // SQLSERVER
                              "READTEXT",           // SQLSERVER
                              "REAL",               // ACCESS
                              "RECONFIGURE",        // SQLSERVER
                              "REFERENCES",         // ACCESS
                            //"REFERENCES",         // SQLSERVER
                              "RELATIVE",           // SQLSERVER
                              "REPEATABLE",         // SQLSERVER
                              "REPLICATION",        // SQLSERVER
                              "RESTRICT",           // SQLSERVER
                              "RETAINDAY",          // SQLSERVER
                              "RETURN",             // SQLSERVER
                              "REVOKE",             // SQLSERVER
                              "RIGHT",              // ACCESS
                            //"RIGHT",              // SQLSERVER
                              "ROLLBACK",           // SQLSERVER
                              "ROWCOUNT",           // SQLSERVER
                              "ROWS",               // SQLSERVER
                              "RULE",               // SQLSERVER
                              "SAVE",               // SQLSERVER
                              "SCHEMA",             // SQLSERVER
                              "SCROLL",             // SQLSERVER
                              "SECOND",             // SQLSERVER
                              "SELECT",             // ACCESS
                            //"SELECT",             // SQLSERVER
                              "SERIALIZABLE",       // SQLSERVER
                              "SESSION",            // SQLSERVER
                              "SESSION_USER",       // SQLSERVER
                              "SET",                // ACCESS
                            //"SET",                // SQLSERVER
                              "SETUSER",            // SQLSERVER
                              "SHORT",              // ACCESS
                              "SHUTDOWN",           // SQLSERVER
                              "SINGLE",             // ACCESS
                              "SIZE",               // SQLSERVER
                              "SMALLINT",           // ACCESS
                              "SOME",               // ACCESS
                            //"SOME",               // SQLSERVER
                              "SPACE",              // SQLSERVER
                              "SQLSTATE",           // SQLSERVER
                              "STATISTICS",         // SQLSERVER
                              "STDEV",              // ACCESS
                              "STDEVP",             // ACCESS
                              "STRING",             // ACCESS
                              "SUM",                // ACCESS
                            //"SUM",                // SQLSERVER
                              "SYSTEM_USER",        // SQLSERVER
                              "TABLE",              // ACCESS
                            //"TABLE",              // SQLSERVER
                              "TABLEID",            // ACCESS
                              "TAPE",               // SQLSERVER
                              "TEMP",               // SQLSERVER
                              "TEMPORARY",          // SQLSERVER
                              "TEXT",               // ACCESS
                              "TEXTSIZE",           // SQLSERVER
                              "THEN",               // SQLSERVER
                              "TIME",               // ACCESS
                            //"TIME",               // SQLSERVER
                              "TIMESTAMP",          // ACCESS
                            //"TIMESTAMP",          // SQLSERVER
                              "TIMEZONE_HOUR",      // SQLSERVER
                              "TIMEZONE_MINUTE",    // SQLSERVER
                              "TO",                 // ACCESS
                            //"TO",                 // SQLSERVER
                              "TOP",                // ACCESS
                              "TRAILING",           // SQLSERVER
                              "TRAN",               // SQLSERVER
                              "TRANSACTION",        // SQLSERVER
                              "TRANSFORM",          // ACCESS
                              "TRANSLATE",          // SQLSERVER
                              "TRANSLATION",        // SQLSERVER
                              "TRIGGER",            // SQLSERVER
                              "TRUE",               // SQLSERVER
                              "TRUNCATE",           // SQLSERVER
                              "TSEQUAL",            // SQLSERVER
                              "UNCOMMITTED",        // SQLSERVER
                              "UNION",              // ACCESS
                            //"UNION",              // SQLSERVER
                              "UNIQUE",             // ACCESS
                            //"UNIQUE",             // SQLSERVER
                              "UNKNOWN",            // SQLSERVER
                              "UPDATE",             // ACCESS
                            //"UPDATE",             // SQLSERVER
                              "UPDATETEXT",         // SQLSERVER
                              "USAGE",              // SQLSERVER
                              "USE",                // SQLSERVER
                              "USER",               // SQLSERVER
                              "USING",              // SQLSERVER
                              "VALUE",              // ACCESS
                            //"VALUE",              // SQLSERVER
                              "VALUES",             // ACCESS
                            //"VALUES",             // SQLSERVER
                              "VAR",                // ACCESS
                              "VARBINARY",          // ACCESS
                              "VARCHAR",            // ACCESS
                              "VARP",               // ACCESS
                              "VARYING",            // SQLSERVER
                              "VIEW",               // SQLSERVER
                              "VOLUME",             // SQLSERVER
                              "WAITFOR",            // SQLSERVER
                              "WHEN",               // SQLSERVER
                              "WHERE",              // ACCESS
                            //"WHERE",              // SQLSERVER
                              "WHILE",              // SQLSERVER
                              "WITH",               // ACCESS
                            //"WITH",               // SQLSERVER
                              "WORK",               // SQLSERVER
                              "WRITE",              // SQLSERVER
                              "WRITETEXT",          // SQLSERVER
                              "XOR",                // ACCESS
                              "YEAR",               // SQLSERVER
                              "YESNO",              // ACCESS
                              "ZONE",               // SQLSERVER
                              "\0" };     // Must be last -- terminates list.

#elif defined( MYSQL )

   #define CONTINUATION_STR      ""
   #define LINE_TERMINATOR       ";"
   #define COLUMN_INDENT         10
   #define COMMENT_START         "/*"
   #define COMMENT_END           "*/"
   #define NOT_NULL_FIELD        "NOT NULL"
   #define NULL_FIELD            "NULL    "
   #define ADD_COLUMN_STMT       "ADD"
   #define DROP_COLUMN_STMT      "DROP COLUMN"
   #define MAX_TABLENAME_LTH     34
   #define MAX_COLUMNNAME_LTH    34
   #define MAX_DATATYPE_LTH      20
   #define COLUMN_INDENT         10
   #define CREATE_DB             0
   #define COMMIT_STR            "COMMIT;"  // DGC 2007.09.15 "GO"
   #define GRANT_ALL             1
   #define MAX_LTH_FOR_STRING    254

   // List of words that are reserved in SQL Server.
   // Note: these MUST be listed in alphabetical order.
   zCHAR  *szReservedName[] =
                           {
                              "ABSOLUTE",           // SQLSERVER
                              "ACTION",             // SQLSERVER
                              "ADD",                // ACCESS
                            //"ADD",                // SQLSERVER
                              "ALL",                // ACCESS
                            //"ALL",                // SQLSERVER
                              "ALLOCATE",           // SQLSERVER
                              "ALPHANUMERIC",       // ACCESS
                              "ALTER",              // ACCESS
                            //"ALTER",              // SQLSERVER
                              "AND",                // ACCESS
                            //"AND",                // SQLSERVER
                              "ANY",                // ACCESS
                            //"ANY",                // SQLSERVER
                              "ARE",                // SQLSERVER
                              "AS",                 // ACCESS
                            //"AS",                 // SQLSERVER
                              "ASC",                // ACCESS
                            //"ASC",                // SQLSERVER
                              "ASSERTION",          // SQLSERVER
                              "AT",                 // SQLSERVER
                              "AUTHORIZATION",      // SQLSERVER
                              "AUTOINCREMENT",      // ACCESS
                              "AVG",                // ACCESS
                            //"AVG",                // SQLSERVER
                              "BEGIN",              // SQLSERVER
                              "BETWEEN",            // ACCESS
                            //"BETWEEN",            // SQLSERVER
                              "BINARY",             // ACCESS
                              "BIT",                // ACCESS
                              "BOOLEAN",            // ACCESS
                              "BOTH",               // SQLSERVER
                              "BREAK",              // SQLSERVER
                              "BROWSE",             // SQLSERVER
                              "BULK",               // SQLSERVER
                              "BY",                 // ACCESS
                            //"BY",                 // SQLSERVER
                              "BYTE",               // ACCESS
                              "CASCADE",            // SQLSERVER
                              "CASCADED",           // SQLSERVER
                              "CASE",               // SQLSERVER
                              "CAST",               // SQLSERVER
                              "CATALOG",            // SQLSERVER
                              "CHAR",               // ACCESS
                              "CHARACTER",          // ACCESS
                            //"CHARACTER",          // SQLSERVER
                              "CHARACTER_LENGTH",   // SQLSERVER
                              "CHAR_LENGTH",        // SQLSERVER
                              "CHECK",              // SQLSERVER
                              "CHECKPOINT",         // SQLSERVER
                              "CLOSE",              // SQLSERVER
                              "CLUSTERED",          // SQLSERVER
                              "COALESCE",           // SQLSERVER
                              "COLLATE",            // SQLSERVER
                              "COLLATION",          // SQLSERVER
                              "COLUMN",             // ACCESS
                            //"COLUMN",             // SQLSERVER
                              "COMMIT",             // SQLSERVER
                              "COMMITTED",          // SQLSERVER
                              "COMPUTE",            // SQLSERVER
                              "CONFIRM",            // SQLSERVER
                              "CONNECT",            // SQLSERVER
                              "CONNECTION",         // SQLSERVER
                              "CONSTRAINT",         // ACCESS
                            //"CONSTRAINT",         // SQLSERVER
                              "CONSTRAINTS",        // SQLSERVER
                              "CONTINUE",           // SQLSERVER
                              "CONTROLROW",         // SQLSERVER
                              "CONVERT",            // SQLSERVER
                              "CORRESPONDING",      // SQLSERVER
                              "COUNT",              // ACCESS
                            //"COUNT",              // SQLSERVER
                              "COUNTER",            // ACCESS
                              "CREATE",             // ACCESS
                            //"CREATE",             // SQLSERVER
                              "CROSS",              // SQLSERVER
                              "CURRENCY",           // ACCESS
                              "CURRENT",            // SQLSERVER
                              "CURRENT_DATE",       // SQLSERVER
                              "CURRENT_TIME",       // SQLSERVER
                              "CURRENT_TIMESTAMP",  // SQLSERVER
                              "CURRENT_USER",       // SQLSERVER
                              "CURSOR",             // SQLSERVER
                              "DATABASE",           // ACCESS
                            //"DATABASE",           // SQLSERVER
                              "DATE",               // ACCESS
                            //"DATE",               // SQLSERVER
                              "DATETIME",           // ACCESS
                            //"DATETIME",           // SQLSERVER
                              "DAY",                // SQLSERVER
                              "DBAREA",             // ACCESS
                              "DBCC",               // SQLSERVER
                              "DEALLOCATE",         // SQLSERVER
                              "DEBUG",              // SQLSERVER
                              "DECLARE",            // SQLSERVER
                              "DEFAULT",            // SQLSERVER
                              "DEFERRABLE",         // SQLSERVER
                              "DEFERRED",           // SQLSERVER
                              "DELETE",             // ACCESS
                            //"DELETE",             // SQLSERVER
                              "DESC",               // ACCESS
                            //"DESC",               // SQLSERVER
                              "DESCRIBE",           // SQLSERVER
                              "DESCRIPTOR",         // SQLSERVER
                              "DIAGNOSTICS",        // SQLSERVER
                              "DISALLOW",           // ACCESS
                              "DISCONNECT",         // SQLSERVER
                              "DISK",               // SQLSERVER
                              "DISTINCT",           // ACCESS
                            //"DISTINCT",           // SQLSERVER
                              "DISTINCTROW",        // ACCESS
                              "DISTRIBUTED",        // SQLSERVER
                              "DOMAIN",             // SQLSERVER
                              "DOUBLE",             // ACCESS
                            //"DOUBLE",             // SQLSERVER
                              "DROP",               // ACCESS
                            //"DROP",               // SQLSERVER
                              "DUMMY",              // SQLSERVER
                              "DUMP",               // SQLSERVER
                              "ELSE",               // SQLSERVER
                              "END",                // SQLSERVER
                              "END_EXEC",           // SQLSERVER
                              "EQV",                // ACCESS
                              "ERRLVL",             // SQLSERVER
                              "ERROREXIT",          // SQLSERVER
                              "ESCAPE",             // SQLSERVER
                              "EXCEPT",             // SQLSERVER
                              "EXCEPTION",          // SQLSERVER
                              "EXEC",               // SQLSERVER
                              "EXECUTE",            // SQLSERVER
                              "EXISTS",             // ACCESS
                            //"EXISTS",             // SQLSERVER
                              "EXIT",               // SQLSERVER
                              "EXPIREDATE",         // SQLSERVER
                              "EXTERNAL",           // SQLSERVER
                              "EXTRACT",            // SQLSERVER
                              "FALSE",              // SQLSERVER
                              "FETCH",              // SQLSERVER
                              "FILE",               // SQLSERVER
                              "FILLFACTOR",         // SQLSERVER
                              "FIRST",              // SQLSERVER
                              "FLOAT",              // ACCESS
                              "FLOAT4",             // ACCESS
                              "FLOAT8",             // ACCESS
                              "FLOPPY",             // SQLSERVER
                              "FOR",                // SQLSERVER
                              "FOREIGN",            // ACCESS
                            //"FOREIGN",            // SQLSERVER
                              "FROM",               // ACCESS
                            //"FROM",               // SQLSERVER
                              "FULL",               // SQLSERVER
                              "GET",                // SQLSERVER
                              "GETDEFAULT",         // SQLSERVER
                              "GLOBAL",             // SQLSERVER
                              "GOTO",               // SQLSERVER
                              "GRANT",              // SQLSERVER
                              "GROUP",              // ACCESS
                            //"GROUP",              // SQLSERVER
                              "GUID",               // ACCESS
                              "HAVING",             // ACCESS
                            //"HAVING",             // SQLSERVER
                              "HOLDLOCK",           // SQLSERVER
                              "HOUR",               // SQLSERVER
                              "IDENTITY",           // SQLSERVER
                              "IDENTITYCOL",        // SQLSERVER
                              "IDENTITY_INSERT",    // SQLSERVER
                              "IEEEDOUBLE",         // ACCESS
                              "IEEESINGLE",         // ACCESS
                              "IF",                 // SQLSERVER
                              "IGNORE",             // ACCESS
                              "IMMEDIATE",          // SQLSERVER
                              "IMP",                // ACCESS
                              "IN",                 // ACCESS
                            //"IN",                 // SQLSERVER
                              "INDEX",              // ACCESS
                            //"INDEX",              // SQLSERVER
                              "INITIALLY",          // SQLSERVER
                              "INNER",              // ACCESS
                            //"INNER",              // SQLSERVER
                              "INPUT",              // SQLSERVER
                              "INSENSITIVE",        // SQLSERVER
                              "INSERT",             // ACCESS
                            //"INSERT",             // SQLSERVER
                              "INT",                // ACCESS
                              "INTEGER",            // ACCESS
                              "INTEGER1",           // ACCESS
                              "INTEGER2",           // ACCESS
                              "INTERSECT",          // SQLSERVER
                              "INTERVAL",           // SQLSERVER
                              "INTO",               // ACCESS
                            //"INTO",               // SQLSERVER
                              "IS",                 // ACCESS
                            //"IS",                 // SQLSERVER
                              "ISOLATION",          // SQLSERVER
                              "JOIN",               // ACCESS
                            //"JOIN",               // SQLSERVER
                              "KEY",                // ACCESS
                            //"KEY",                // SQLSERVER
                              "KILL",               // SQLSERVER
                              "LAST",               // SQLSERVER
                              "LEADING",            // SQLSERVER
                              "LEFT",               // ACCESS
                            //"LEFT",               // SQLSERVER
                              "LEVEL",              // ACCESS
                            //"LEVEL",              // SQLSERVER
                              "LIKE",               // ACCESS
                            //"LIKE",               // SQLSERVER
                              "LINENO",             // SQLSERVER
                              "LOAD",               // SQLSERVER
                              "LOCAL",              // SQLSERVER
                              "LOGICAL",            // ACCESS
                              "LOGICAL1",           // ACCESS
                              "LONG",               // ACCESS
                              "LONGBINARY",         // ACCESS
                              "LONGTEXT",           // ACCESS
                              "MATCH",              // SQLSERVER
                              "MAX",                // ACCESS
                            //"MAX",                // SQLSERVER
                              "MEMO",               // ACCESS
                              "MIN",                // ACCESS
                            //"MIN",                // SQLSERVER
                              "MINUTE",             // SQLSERVER
                              "MIRROREXIT",         // SQLSERVER
                              "MOD",                // ACCESS
                              "MONEY",              // ACCESS
                              "MONTH",              // SQLSERVER
                              "NAMES",              // SQLSERVER
                              "NATIONAL",           // SQLSERVER
                              "NATURAL",            // SQLSERVER
                              "NCHAR",              // SQLSERVER
                              "NEXT",               // SQLSERVER
                              "NEXTLOG",            // ACCESS
                              "NO",                 // ACCESS
                            //"NO",                 // SQLSERVER
                              "NOCHECK",            // SQLSERVER
                              "NONCLUSTERED",       // SQLSERVER
                              "NOT",                // ACCESS
                            //"NOT",                // SQLSERVER
                              "NOTE",               // ACCESS
                              "NULL",               // ACCESS
                            //"NULL",               // SQLSERVER
                              "NULLIF",             // SQLSERVER
                              "NUMBER",             // ACCESS
                              "NUMERIC",            // ACCESS
                              "OCTET_LENGTH",       // SQLSERVER
                              "OF",                 // SQLSERVER
                              "OFF",                // SQLSERVER
                              "OFFSETS",            // SQLSERVER
                              "OLEOBJECT",          // ACCESS
                              "ON",                 // ACCESS
                            //"ON",                 // SQLSERVER
                              "ONCE",               // SQLSERVER
                              "ONLY",               // SQLSERVER
                              "OPEN",               // SQLSERVER
                              "OPTION",             // ACCESS
                            //"OPTION",             // SQLSERVER
                              "OR",                 // ACCESS
                            //"OR",                 // SQLSERVER
                              "ORDER",              // ACCESS
                            //"ORDER",              // SQLSERVER
                              "OUTER",              // ACCESS
                            //"OUTER",              // SQLSERVER
                              "OUTPUT",             // SQLSERVER
                              "OVER",               // SQLSERVER
                              "OVERLAPS",           // SQLSERVER
                              "OWNERACCESS",        // ACCESS
                              "PAD",                // SQLSERVER
                              "PARAMETERS",         // ACCESS
                              "PARTIAL",            // SQLSERVER
                              "PERCENT",            // ACCESS
                              "PERM",               // SQLSERVER
                              "PERMANENT",          // SQLSERVER
                              "PIPE",               // SQLSERVER
                              "PIVOT",              // ACCESS
                              "PLAN",               // SQLSERVER
                              "POSITION",           // SQLSERVER
                              "PRECISION",          // SQLSERVER
                              "PREPARE",            // SQLSERVER
                              "PRESEVE",            // SQLSERVER
                              "PRIMARY",            // ACCESS
                            //"PRIMARY",            // SQLSERVER
                              "PRINT",              // SQLSERVER
                              "PRIOR",              // SQLSERVER
                              "PRIVILEGES",         // SQLSERVER
                              "PROC",               // SQLSERVER
                              "PROCEDURE",          // ACCESS
                            //"PROCEDURE",          // SQLSERVER
                              "PROCESSEXIT",        // SQLSERVER
                              "PUBLIC",             // SQLSERVER
                              "RAISERROR",          // SQLSERVER
                              "READ",               // SQLSERVER
                              "READTEXT",           // SQLSERVER
                              "REAL",               // ACCESS
                              "RECONFIGURE",        // SQLSERVER
                              "REFERENCES",         // ACCESS
                            //"REFERENCES",         // SQLSERVER
                              "RELATIVE",           // SQLSERVER
                              "REPEATABLE",         // SQLSERVER
                              "REPLICATION",        // SQLSERVER
                              "RESTRICT",           // SQLSERVER
                              "RETAINDAY",          // SQLSERVER
                              "RETURN",             // SQLSERVER
                              "REVOKE",             // SQLSERVER
                              "RIGHT",              // ACCESS
                            //"RIGHT",              // SQLSERVER
                              "ROLLBACK",           // SQLSERVER
                              "ROWCOUNT",           // SQLSERVER
                              "ROWS",               // SQLSERVER
                              "RULE",               // SQLSERVER
                              "SAVE",               // SQLSERVER
                              "SCHEMA",             // SQLSERVER
                              "SCROLL",             // SQLSERVER
                              "SECOND",             // SQLSERVER
                              "SELECT",             // ACCESS
                            //"SELECT",             // SQLSERVER
                              "SERIALIZABLE",       // SQLSERVER
                              "SESSION",            // SQLSERVER
                              "SESSION_USER",       // SQLSERVER
                              "SET",                // ACCESS
                            //"SET",                // SQLSERVER
                              "SETUSER",            // SQLSERVER
                              "SHORT",              // ACCESS
                              "SHUTDOWN",           // SQLSERVER
                              "SINGLE",             // ACCESS
                              "SIZE",               // SQLSERVER
                              "SMALLINT",           // ACCESS
                              "SOME",               // ACCESS
                            //"SOME",               // SQLSERVER
                              "SPACE",              // SQLSERVER
                              "SQLSTATE",           // SQLSERVER
                              "STATISTICS",         // SQLSERVER
                              "STDEV",              // ACCESS
                              "STDEVP",             // ACCESS
                              "STRING",             // ACCESS
                              "SUM",                // ACCESS
                            //"SUM",                // SQLSERVER
                              "SYSTEM_USER",        // SQLSERVER
                              "TABLE",              // ACCESS
                            //"TABLE",              // SQLSERVER
                              "TABLEID",            // ACCESS
                              "TAPE",               // SQLSERVER
                              "TEMP",               // SQLSERVER
                              "TEMPORARY",          // SQLSERVER
                              "TEXT",               // ACCESS
                              "TEXTSIZE",           // SQLSERVER
                              "THEN",               // SQLSERVER
                              "TIME",               // ACCESS
                            //"TIME",               // SQLSERVER
                              "TIMESTAMP",          // ACCESS
                            //"TIMESTAMP",          // SQLSERVER
                              "TIMEZONE_HOUR",      // SQLSERVER
                              "TIMEZONE_MINUTE",    // SQLSERVER
                              "TO",                 // ACCESS
                            //"TO",                 // SQLSERVER
                              "TOP",                // ACCESS
                              "TRAILING",           // SQLSERVER
                              "TRAN",               // SQLSERVER
                              "TRANSACTION",        // SQLSERVER
                              "TRANSFORM",          // ACCESS
                              "TRANSLATE",          // SQLSERVER
                              "TRANSLATION",        // SQLSERVER
                              "TRIGGER",            // SQLSERVER
                              "TRUE",               // SQLSERVER
                              "TRUNCATE",           // SQLSERVER
                              "TSEQUAL",            // SQLSERVER
                              "UNCOMMITTED",        // SQLSERVER
                              "UNION",              // ACCESS
                            //"UNION",              // SQLSERVER
                              "UNIQUE",             // ACCESS
                            //"UNIQUE",             // SQLSERVER
                              "UNKNOWN",            // SQLSERVER
                              "UPDATE",             // ACCESS
                            //"UPDATE",             // SQLSERVER
                              "UPDATETEXT",         // SQLSERVER
                              "USAGE",              // SQLSERVER
                              "USE",                // SQLSERVER
                              "USER",               // SQLSERVER
                              "USING",              // SQLSERVER
                              "VALUE",              // ACCESS
                            //"VALUE",              // SQLSERVER
                              "VALUES",             // ACCESS
                            //"VALUES",             // SQLSERVER
                              "VAR",                // ACCESS
                              "VARBINARY",          // ACCESS
                              "VARCHAR",            // ACCESS
                              "VARP",               // ACCESS
                              "VARYING",            // SQLSERVER
                              "VIEW",               // SQLSERVER
                              "VOLUME",             // SQLSERVER
                              "WAITFOR",            // SQLSERVER
                              "WHEN",               // SQLSERVER
                              "WHERE",              // ACCESS
                            //"WHERE",              // SQLSERVER
                              "WHILE",              // SQLSERVER
                              "WITH",               // ACCESS
                            //"WITH",               // SQLSERVER
                              "WORK",               // SQLSERVER
                              "WRITE",              // SQLSERVER
                              "WRITETEXT",          // SQLSERVER
                              "XOR",                // ACCESS
                              "YEAR",               // SQLSERVER
                              "YESNO",              // ACCESS
                              "ZONE",               // SQLSERVER
                              "\0" };     // Must be last -- terminates list.

#elif defined( ODBC ) || defined( SQLBASE )

   #define CONTINUATION_STR      ""
   #define LINE_TERMINATOR       ";"
   #define MAX_TABLENAME_LTH     18
   #define MAX_COLUMNNAME_LTH    18
   #define MAX_DATATYPE_LTH      20
   #define COLUMN_INDENT         10
   #define COMMENT_START         "--"
   #define COMMENT_END           ""
   #define NOT_NULL_FIELD        " NOT NULL"
   #define NULL_FIELD            "         "
   #define ADD_COLUMN_STMT       "ADD COLUMN"
   #define DROP_COLUMN_STMT      "DROP COLUMN"
   #define COMMIT_STR            "COMMIT;"
   #define MAX_LTH_FOR_STRING    254

   // List of words that are reserved in SQLBASE.
   // Note: these MUST be listed in alphabetical order.
   zCHAR  *szReservedName[] =
                           {
                              "ADD",
                              "ADJUSTING",
                              "ALL",
                              "ALTER",
                              "AND",
                              "ANY",
                              "AS",
                              "ASC",
                              "AVG",
                              "BETWEEN",
                              "BY",
                              "CASCADE",
                              "CHAR",
                              "CHARACTER",
                              "CHECK",
                              "CLUSTERED",
                              "COLUMN",
                              "COMMENT",
                              "COMMIT",
                              "COMPUTE",
                              "CONNECT",
                              "COUNT",
                              "CREATE",
                              "CURRENT",
                              "DATABASE",
                              "DATE",
                              "DATETIME",
                              "DAY",
                              "DAYS",
                              "DBA",
                              "DBAREA",
                              "DEC",
                              "DECIMAL",
                              "DEFAULT",
                              "DEINSTALL",
                              "DELETE",
                              "DESC",
                              "DIRECT",
                              "DISTINCT",
                              "DOUBLE",
                              "DROP",
                              "EXISTS",
                              "FLOAT",
                              "FOR",
                              "FOREIGN",
                              "FROM",
                              "GRANT",
                              "GROUP",
                              "HASHED",
                              "HAVING",
                              "HOUR",
                              "HOURS",
                              "IDENTIFIED",
                              "IN",
                              "INDEX",
                              "INSERT",
                              "INSTALL",
                              "INT",
                              "INTEGER",
                              "INTO",
                              "IS",
                              "KEY",
                              "LABEL",
                              "LAST",
                              "LIKE",
                              "LOG",
                              "LONG",
                              "MAX",
                              "MICROSECOND",
                              "MICROSECONDS",
                              "MIN",
                              "MINUTE",
                              "MINUTES",
                              "MODIFY",
                              "MONTH",
                              "MONTHS",
                              "NEXTLOG",
                              "NOT",
                              "NULL",
                              "NUMBER",
                              "OF",
                              "ON",
                              "OPTION",
                              "OR",
                              "ORDER",
                              "PASSWORD",
                              "PCTFREE",
                              "POST",
                              "PRECISION",
                              "PRIMARY",
                              "PUBLIC",
                              "REAL",
                              "REFERENCES",
                              "RENAME",
                              "RESOURCE",
                              "RESTRICT",
                              "REVOKE",
                              "ROLLBACK",
                              "ROWCOUNT",
                              "ROWID",
                              "ROWS",
                              "SAVEPOINT",
                              "SECOND",
                              "SECONDS",
                              "SELECT",
                              "SET",
                              "SIZE",
                              "SMALLINT",
                              "STATISTICS",
                              "STOGROUP",
                              "SUM",
                              "SYNONYM",
                              "SYSDATE",
                              "SYSDATETIME",
                              "SYSTEM",
                              "SYSTIME",
                              "SYSTIMEZONE",
                              "TABLE",
                              "TIME",
                              "TIMESTAMP",
                              "TIMEZONE",
                              "TO",
                              "UNION",
                              "UNIQUE",
                              "UPDATE",
                              "USER",
                              "USERERROR",
                              "USING",
                              "VALUES",
                              "VARCHAR",
                              "VIEW",
                              "WAIT",
                              "WHERE",
                              "WITH",
                              "WORK",
                              "YEAR",
                              "YEARS",
                              "\0" };     // Must be last -- terminates list.

#elif defined( POSTGRESQL )

   #define CONTINUATION_STR      ""
   #define LINE_TERMINATOR       ";"
   #define MAX_TABLENAME_LTH     34
   #define MAX_COLUMNNAME_LTH    34
   #define MAX_DATATYPE_LTH      20
   #define COLUMN_INDENT         10
   #define COMMENT_START         "--"
   #define COMMENT_END           ""
   #define NOT_NULL_FIELD        " NOT NULL"
   #define NULL_FIELD            " DEFAULT NULL"
   #define ADD_COLUMN_STMT       "ADD COLUMN"
   #define DROP_COLUMN_STMT      "DROP COLUMN"
   #define COMMIT_STR            "COMMIT;"
   #define MAX_LTH_FOR_STRING    254

   // List of words that are reserved in SQLBASE.
   // Note: these MUST be listed in alphabetical order.
   zCHAR  *szReservedName[] =
                           {
                              "ADD",
                              "ADJUSTING",
                              "ALL",
                              "ALTER",
                              "AND",
                              "ANY",
                              "AS",
                              "ASC",
                              "AVG",
                              "BETWEEN",
                              "BY",
                              "CASCADE",
                              "CHAR",
                              "CHARACTER",
                              "CHECK",
                              "CLUSTERED",
                              "COLUMN",
                              "COMMENT",
                              "COMMIT",
                              "COMPUTE",
                              "CONNECT",
                              "COUNT",
                              "CREATE",
                              "CURRENT",
                              "DATABASE",
                              "DATE",
                              "DATETIME",
                              "DAY",
                              "DAYS",
                              "DBA",
                              "DBAREA",
                              "DEC",
                              "DECIMAL",
                              "DEFAULT",
                              "DEINSTALL",
                              "DELETE",
                              "DESC",
                              "DIRECT",
                              "DISTINCT",
                              "DOUBLE",
                              "DROP",
                              "EXISTS",
                              "FLOAT",
                              "FOR",
                              "FOREIGN",
                              "FROM",
                              "GRANT",
                              "GROUP",
                              "HASHED",
                              "HAVING",
                              "HOUR",
                              "HOURS",
                              "IDENTIFIED",
                              "IN",
                              "INDEX",
                              "INSERT",
                              "INSTALL",
                              "INT",
                              "INTEGER",
                              "INTO",
                              "IS",
                              "KEY",
                              "LABEL",
                              "LAST",
                              "LIKE",
                              "LOG",
                              "LONG",
                              "MAX",
                              "MICROSECOND",
                              "MICROSECONDS",
                              "MIN",
                              "MINUTE",
                              "MINUTES",
                              "MODIFY",
                              "MONTH",
                              "MONTHS",
                              "NEXTLOG",
                              "NOT",
                              "NULL",
                              "NUMBER",
                              "OF",
                              "ON",
                              "OPTION",
                              "OR",
                              "ORDER",
                              "PASSWORD",
                              "PCTFREE",
                              "POST",
                              "PRECISION",
                              "PRIMARY",
                              "PUBLIC",
                              "REAL",
                              "REFERENCES",
                              "RENAME",
                              "RESOURCE",
                              "RESTRICT",
                              "REVOKE",
                              "ROLLBACK",
                              "ROWCOUNT",
                              "ROWID",
                              "ROWS",
                              "SAVEPOINT",
                              "SECOND",
                              "SECONDS",
                              "SELECT",
                              "SET",
                              "SIZE",
                              "SMALLINT",
                              "STATISTICS",
                              "STOGROUP",
                              "SUM",
                              "SYNONYM",
                              "SYSDATE",
                              "SYSDATETIME",
                              "SYSTEM",
                              "SYSTIME",
                              "SYSTIMEZONE",
                              "TABLE",
                              "TIME",
                              "TIMESTAMP",
                              "TIMEZONE",
                              "TO",
                              "UNION",
                              "UNIQUE",
                              "UPDATE",
                              "USER",
                              "USERERROR",
                              "USING",
                              "VALUES",
                              "VARCHAR",
                              "VIEW",
                              "WAIT",
                              "WHERE",
                              "WITH",
                              "WORK",
                              "YEAR",
                              "YEARS",
                              "\0" };     // Must be last -- terminates list.

#elif defined( SQLSERVER )

   #define CONTINUATION_STR      ""
   #define LINE_TERMINATOR       ""
   #define MAX_TABLENAME_LTH     34
   #define MAX_COLUMNNAME_LTH    34
   #define MAX_DATATYPE_LTH      20
   #define COLUMN_INDENT         10
   #define COMMENT_START         "/*"
   #define COMMENT_END           "*/"
   #define NOT_NULL_FIELD        "NOT NULL"
   #define NULL_FIELD            "NULL    "
   #define ADD_COLUMN_STMT       "ADD"
   #define DROP_COLUMN_STMT      "DROP COLUMN"
   #define COMMIT_STR            "GO"
   #define CREATE_DB             1     // Causes CREATE DATABASE command.
   #define GRANT_ALL             1     // Causes GRANT ALL command.
   #define COMMIT_EVERY_TABLE    1     // Causes COMMIT after every table.
   #define MAX_LTH_FOR_STRING    254

   // List of words that are reserved in SQL Server.
   // Note: these MUST be listed in alphabetical order.
   zCHAR  *szReservedName[] =
                           {
                              "ABSOLUTE",           // SQLSERVER
                              "ACTION",             // SQLSERVER
                              "ADD",                // ACCESS
                            //"ADD",                // SQLSERVER
                              "ALL",                // ACCESS
                            //"ALL",                // SQLSERVER
                              "ALLOCATE",           // SQLSERVER
                              "ALPHANUMERIC",       // ACCESS
                              "ALTER",              // ACCESS
                            //"ALTER",              // SQLSERVER
                              "AND",                // ACCESS
                            //"AND",                // SQLSERVER
                              "ANY",                // ACCESS
                            //"ANY",                // SQLSERVER
                              "ARE",                // SQLSERVER
                              "AS",                 // ACCESS
                            //"AS",                 // SQLSERVER
                              "ASC",                // ACCESS
                            //"ASC",                // SQLSERVER
                              "ASSERTION",          // SQLSERVER
                              "AT",                 // SQLSERVER
                              "AUTHORIZATION",      // SQLSERVER
                              "AUTOINCREMENT",      // ACCESS
                              "AVG",                // ACCESS
                            //"AVG",                // SQLSERVER
                              "BEGIN",              // SQLSERVER
                              "BETWEEN",            // ACCESS
                            //"BETWEEN",            // SQLSERVER
                              "BINARY",             // ACCESS
                              "BIT",                // ACCESS
                              "BOOLEAN",            // ACCESS
                              "BOTH",               // SQLSERVER
                              "BREAK",              // SQLSERVER
                              "BROWSE",             // SQLSERVER
                              "BULK",               // SQLSERVER
                              "BY",                 // ACCESS
                            //"BY",                 // SQLSERVER
                              "BYTE",               // ACCESS
                              "CASCADE",            // SQLSERVER
                              "CASCADED",           // SQLSERVER
                              "CASE",               // SQLSERVER
                              "CAST",               // SQLSERVER
                              "CATALOG",            // SQLSERVER
                              "CHAR",               // ACCESS
                              "CHARACTER",          // ACCESS
                            //"CHARACTER",          // SQLSERVER
                              "CHARACTER_LENGTH",   // SQLSERVER
                              "CHAR_LENGTH",        // SQLSERVER
                              "CHECK",              // SQLSERVER
                              "CHECKPOINT",         // SQLSERVER
                              "CLOSE",              // SQLSERVER
                              "CLUSTERED",          // SQLSERVER
                              "COALESCE",           // SQLSERVER
                              "COLLATE",            // SQLSERVER
                              "COLLATION",          // SQLSERVER
                              "COLUMN",             // ACCESS
                            //"COLUMN",             // SQLSERVER
                              "COMMIT",             // SQLSERVER
                              "COMMITTED",          // SQLSERVER
                              "COMPUTE",            // SQLSERVER
                              "CONFIRM",            // SQLSERVER
                              "CONNECT",            // SQLSERVER
                              "CONNECTION",         // SQLSERVER
                              "CONSTRAINT",         // ACCESS
                            //"CONSTRAINT",         // SQLSERVER
                              "CONSTRAINTS",        // SQLSERVER
                              "CONTINUE",           // SQLSERVER
                              "CONTROLROW",         // SQLSERVER
                              "CONVERT",            // SQLSERVER
                              "CORRESPONDING",      // SQLSERVER
                              "COUNT",              // ACCESS
                            //"COUNT",              // SQLSERVER
                              "COUNTER",            // ACCESS
                              "CREATE",             // ACCESS
                            //"CREATE",             // SQLSERVER
                              "CROSS",              // SQLSERVER
                              "CURRENCY",           // ACCESS
                              "CURRENT",            // SQLSERVER
                              "CURRENT_DATE",       // SQLSERVER
                              "CURRENT_TIME",       // SQLSERVER
                              "CURRENT_TIMESTAMP",  // SQLSERVER
                              "CURRENT_USER",       // SQLSERVER
                              "CURSOR",             // SQLSERVER
                              "DATABASE",           // ACCESS
                            //"DATABASE",           // SQLSERVER
                              "DATE",               // ACCESS
                            //"DATE",               // SQLSERVER
                              "DATETIME",           // ACCESS
                            //"DATETIME",           // SQLSERVER
                              "DAY",                // SQLSERVER
                              "DBAREA",             // ACCESS
                              "DBCC",               // SQLSERVER
                              "DEALLOCATE",         // SQLSERVER
                              "DEBUG",              // SQLSERVER
                              "DECLARE",            // SQLSERVER
                              "DEFAULT",            // SQLSERVER
                              "DEFERRABLE",         // SQLSERVER
                              "DEFERRED",           // SQLSERVER
                              "DELETE",             // ACCESS
                            //"DELETE",             // SQLSERVER
                              "DESC",               // ACCESS
                            //"DESC",               // SQLSERVER
                              "DESCRIBE",           // SQLSERVER
                              "DESCRIPTOR",         // SQLSERVER
                              "DIAGNOSTICS",        // SQLSERVER
                              "DISALLOW",           // ACCESS
                              "DISCONNECT",         // SQLSERVER
                              "DISK",               // SQLSERVER
                              "DISTINCT",           // ACCESS
                            //"DISTINCT",           // SQLSERVER
                              "DISTINCTROW",        // ACCESS
                              "DISTRIBUTED",        // SQLSERVER
                              "DOMAIN",             // SQLSERVER
                              "DOUBLE",             // ACCESS
                            //"DOUBLE",             // SQLSERVER
                              "DROP",               // ACCESS
                            //"DROP",               // SQLSERVER
                              "DUMMY",              // SQLSERVER
                              "DUMP",               // SQLSERVER
                              "ELSE",               // SQLSERVER
                              "END",                // SQLSERVER
                              "END_EXEC",           // SQLSERVER
                              "EQV",                // ACCESS
                              "ERRLVL",             // SQLSERVER
                              "ERROREXIT",          // SQLSERVER
                              "ESCAPE",             // SQLSERVER
                              "EXCEPT",             // SQLSERVER
                              "EXCEPTION",          // SQLSERVER
                              "EXEC",               // SQLSERVER
                              "EXECUTE",            // SQLSERVER
                              "EXISTS",             // ACCESS
                            //"EXISTS",             // SQLSERVER
                              "EXIT",               // SQLSERVER
                              "EXPIREDATE",         // SQLSERVER
                              "EXTERNAL",           // SQLSERVER
                              "EXTRACT",            // SQLSERVER
                              "FALSE",              // SQLSERVER
                              "FETCH",              // SQLSERVER
                              "FILE",               // SQLSERVER
                              "FILLFACTOR",         // SQLSERVER
                              "FIRST",              // SQLSERVER
                              "FLOAT",              // ACCESS
                              "FLOAT4",             // ACCESS
                              "FLOAT8",             // ACCESS
                              "FLOPPY",             // SQLSERVER
                              "FOR",                // SQLSERVER
                              "FOREIGN",            // ACCESS
                            //"FOREIGN",            // SQLSERVER
                              "FROM",               // ACCESS
                            //"FROM",               // SQLSERVER
                              "FULL",               // SQLSERVER
                              "GET",                // SQLSERVER
                              "GETDEFAULT",         // SQLSERVER
                              "GLOBAL",             // SQLSERVER
                              "GOTO",               // SQLSERVER
                              "GRANT",              // SQLSERVER
                              "GROUP",              // ACCESS
                            //"GROUP",              // SQLSERVER
                              "GUID",               // ACCESS
                              "HAVING",             // ACCESS
                            //"HAVING",             // SQLSERVER
                              "HOLDLOCK",           // SQLSERVER
                              "HOUR",               // SQLSERVER
                              "IDENTITY",           // SQLSERVER
                              "IDENTITYCOL",        // SQLSERVER
                              "IDENTITY_INSERT",    // SQLSERVER
                              "IEEEDOUBLE",         // ACCESS
                              "IEEESINGLE",         // ACCESS
                              "IF",                 // SQLSERVER
                              "IGNORE",             // ACCESS
                              "IMMEDIATE",          // SQLSERVER
                              "IMP",                // ACCESS
                              "IN",                 // ACCESS
                            //"IN",                 // SQLSERVER
                              "INDEX",              // ACCESS
                            //"INDEX",              // SQLSERVER
                              "INITIALLY",          // SQLSERVER
                              "INNER",              // ACCESS
                            //"INNER",              // SQLSERVER
                              "INPUT",              // SQLSERVER
                              "INSENSITIVE",        // SQLSERVER
                              "INSERT",             // ACCESS
                            //"INSERT",             // SQLSERVER
                              "INT",                // ACCESS
                              "INTEGER",            // ACCESS
                              "INTEGER1",           // ACCESS
                              "INTEGER2",           // ACCESS
                              "INTERSECT",          // SQLSERVER
                              "INTERVAL",           // SQLSERVER
                              "INTO",               // ACCESS
                            //"INTO",               // SQLSERVER
                              "IS",                 // ACCESS
                            //"IS",                 // SQLSERVER
                              "ISOLATION",          // SQLSERVER
                              "JOIN",               // ACCESS
                            //"JOIN",               // SQLSERVER
                              "KEY",                // ACCESS
                            //"KEY",                // SQLSERVER
                              "KILL",               // SQLSERVER
                              "LAST",               // SQLSERVER
                              "LEADING",            // SQLSERVER
                              "LEFT",               // ACCESS
                            //"LEFT",               // SQLSERVER
                              "LEVEL",              // ACCESS
                            //"LEVEL",              // SQLSERVER
                              "LIKE",               // ACCESS
                            //"LIKE",               // SQLSERVER
                              "LINENO",             // SQLSERVER
                              "LOAD",               // SQLSERVER
                              "LOCAL",              // SQLSERVER
                              "LOGICAL",            // ACCESS
                              "LOGICAL1",           // ACCESS
                              "LONG",               // ACCESS
                              "LONGBINARY",         // ACCESS
                              "LONGTEXT",           // ACCESS
                              "MATCH",              // SQLSERVER
                              "MAX",                // ACCESS
                            //"MAX",                // SQLSERVER
                              "MEMO",               // ACCESS
                              "MIN",                // ACCESS
                            //"MIN",                // SQLSERVER
                              "MINUTE",             // SQLSERVER
                              "MIRROREXIT",         // SQLSERVER
                              "MOD",                // ACCESS
                              "MONEY",              // ACCESS
                              "MONTH",              // SQLSERVER
                              "NAMES",              // SQLSERVER
                              "NATIONAL",           // SQLSERVER
                              "NATURAL",            // SQLSERVER
                              "NCHAR",              // SQLSERVER
                              "NEXT",               // SQLSERVER
                              "NEXTLOG",            // ACCESS
                              "NO",                 // ACCESS
                            //"NO",                 // SQLSERVER
                              "NOCHECK",            // SQLSERVER
                              "NONCLUSTERED",       // SQLSERVER
                              "NOT",                // ACCESS
                            //"NOT",                // SQLSERVER
                              "NOTE",               // ACCESS
                              "NULL",               // ACCESS
                            //"NULL",               // SQLSERVER
                              "NULLIF",             // SQLSERVER
                              "NUMBER",             // ACCESS
                              "NUMERIC",            // ACCESS
                              "OCTET_LENGTH",       // SQLSERVER
                              "OF",                 // SQLSERVER
                              "OFF",                // SQLSERVER
                              "OFFSETS",            // SQLSERVER
                              "OLEOBJECT",          // ACCESS
                              "ON",                 // ACCESS
                            //"ON",                 // SQLSERVER
                              "ONCE",               // SQLSERVER
                              "ONLY",               // SQLSERVER
                              "OPEN",               // SQLSERVER
                              "OPTION",             // ACCESS
                            //"OPTION",             // SQLSERVER
                              "OR",                 // ACCESS
                            //"OR",                 // SQLSERVER
                              "ORDER",              // ACCESS
                            //"ORDER",              // SQLSERVER
                              "OUTER",              // ACCESS
                            //"OUTER",              // SQLSERVER
                              "OUTPUT",             // SQLSERVER
                              "OVER",               // SQLSERVER
                              "OVERLAPS",           // SQLSERVER
                              "OWNERACCESS",        // ACCESS
                              "PAD",                // SQLSERVER
                              "PARAMETERS",         // ACCESS
                              "PARTIAL",            // SQLSERVER
                              "PERCENT",            // ACCESS
                              "PERM",               // SQLSERVER
                              "PERMANENT",          // SQLSERVER
                              "PIPE",               // SQLSERVER
                              "PIVOT",              // ACCESS
                              "PLAN",               // SQLSERVER
                              "POSITION",           // SQLSERVER
                              "PRECISION",          // SQLSERVER
                              "PREPARE",            // SQLSERVER
                              "PRESEVE",            // SQLSERVER
                              "PRIMARY",            // ACCESS
                            //"PRIMARY",            // SQLSERVER
                              "PRINT",              // SQLSERVER
                              "PRIOR",              // SQLSERVER
                              "PRIVILEGES",         // SQLSERVER
                              "PROC",               // SQLSERVER
                              "PROCEDURE",          // ACCESS
                            //"PROCEDURE",          // SQLSERVER
                              "PROCESSEXIT",        // SQLSERVER
                              "PUBLIC",             // SQLSERVER
                              "RAISERROR",          // SQLSERVER
                              "READ",               // SQLSERVER
                              "READTEXT",           // SQLSERVER
                              "REAL",               // ACCESS
                              "RECONFIGURE",        // SQLSERVER
                              "REFERENCES",         // ACCESS
                            //"REFERENCES",         // SQLSERVER
                              "RELATIVE",           // SQLSERVER
                              "REPEATABLE",         // SQLSERVER
                              "REPLICATION",        // SQLSERVER
                              "RESTRICT",           // SQLSERVER
                              "RETAINDAY",          // SQLSERVER
                              "RETURN",             // SQLSERVER
                              "REVOKE",             // SQLSERVER
                              "RIGHT",              // ACCESS
                            //"RIGHT",              // SQLSERVER
                              "ROLLBACK",           // SQLSERVER
                              "ROWCOUNT",           // SQLSERVER
                              "ROWS",               // SQLSERVER
                              "RULE",               // SQLSERVER
                              "SAVE",               // SQLSERVER
                              "SCHEMA",             // SQLSERVER
                              "SCROLL",             // SQLSERVER
                              "SECOND",             // SQLSERVER
                              "SELECT",             // ACCESS
                            //"SELECT",             // SQLSERVER
                              "SERIALIZABLE",       // SQLSERVER
                              "SESSION",            // SQLSERVER
                              "SESSION_USER",       // SQLSERVER
                              "SET",                // ACCESS
                            //"SET",                // SQLSERVER
                              "SETUSER",            // SQLSERVER
                              "SHORT",              // ACCESS
                              "SHUTDOWN",           // SQLSERVER
                              "SINGLE",             // ACCESS
                              "SIZE",               // SQLSERVER
                              "SMALLINT",           // ACCESS
                              "SOME",               // ACCESS
                            //"SOME",               // SQLSERVER
                              "SPACE",              // SQLSERVER
                              "SQLSTATE",           // SQLSERVER
                              "STATISTICS",         // SQLSERVER
                              "STDEV",              // ACCESS
                              "STDEVP",             // ACCESS
                              "STRING",             // ACCESS
                              "SUM",                // ACCESS
                            //"SUM",                // SQLSERVER
                              "SYSTEM_USER",        // SQLSERVER
                              "TABLE",              // ACCESS
                            //"TABLE",              // SQLSERVER
                              "TABLEID",            // ACCESS
                              "TAPE",               // SQLSERVER
                              "TEMP",               // SQLSERVER
                              "TEMPORARY",          // SQLSERVER
                              "TEXT",               // ACCESS
                              "TEXTSIZE",           // SQLSERVER
                              "THEN",               // SQLSERVER
                              "TIME",               // ACCESS
                            //"TIME",               // SQLSERVER
                              "TIMESTAMP",          // ACCESS
                            //"TIMESTAMP",          // SQLSERVER
                              "TIMEZONE_HOUR",      // SQLSERVER
                              "TIMEZONE_MINUTE",    // SQLSERVER
                              "TO",                 // ACCESS
                            //"TO",                 // SQLSERVER
                              "TOP",                // ACCESS
                              "TRAILING",           // SQLSERVER
                              "TRAN",               // SQLSERVER
                              "TRANSACTION",        // SQLSERVER
                              "TRANSFORM",          // ACCESS
                              "TRANSLATE",          // SQLSERVER
                              "TRANSLATION",        // SQLSERVER
                              "TRIGGER",            // SQLSERVER
                              "TRUE",               // SQLSERVER
                              "TRUNCATE",           // SQLSERVER
                              "TSEQUAL",            // SQLSERVER
                              "UNCOMMITTED",        // SQLSERVER
                              "UNION",              // ACCESS
                            //"UNION",              // SQLSERVER
                              "UNIQUE",             // ACCESS
                            //"UNIQUE",             // SQLSERVER
                              "UNKNOWN",            // SQLSERVER
                              "UPDATE",             // ACCESS
                            //"UPDATE",             // SQLSERVER
                              "UPDATETEXT",         // SQLSERVER
                              "USAGE",              // SQLSERVER
                              "USE",                // SQLSERVER
                              "USER",               // SQLSERVER
                              "USING",              // SQLSERVER
                              "VALUE",              // ACCESS
                            //"VALUE",              // SQLSERVER
                              "VALUES",             // ACCESS
                            //"VALUES",             // SQLSERVER
                              "VAR",                // ACCESS
                              "VARBINARY",          // ACCESS
                              "VARCHAR",            // ACCESS
                              "VARP",               // ACCESS
                              "VARYING",            // SQLSERVER
                              "VIEW",               // SQLSERVER
                              "VOLUME",             // SQLSERVER
                              "WAITFOR",            // SQLSERVER
                              "WHEN",               // SQLSERVER
                              "WHERE",              // ACCESS
                            //"WHERE",              // SQLSERVER
                              "WHILE",              // SQLSERVER
                              "WITH",               // ACCESS
                            //"WITH",               // SQLSERVER
                              "WORK",               // SQLSERVER
                              "WRITE",              // SQLSERVER
                              "WRITETEXT",          // SQLSERVER
                              "XOR",                // ACCESS
                              "YEAR",               // SQLSERVER
                              "YESNO",              // ACCESS
                              "ZONE",               // SQLSERVER
                              "\0" };     // Must be last -- terminates list.

#endif

#define BUFF_SIZE 256
#define MAX_NAME_LTH 254

// function prototypes
static void
RemoveBrackets( zPCHAR pch );

// Change following "if" for debugging.
#if 1
   #define fnWriteLine     SysWriteLine
#else
   int fnWriteLine( zVIEW lpTaskView, zLONG f, zPCHAR pchLine )
   {
      TraceLineS( "(dbh) ", pchLine );
      return( SysWriteLine( lpTaskView, f, pchLine ) );
   }
#endif

zSHORT LOCALOPER
fnBuildDropIndex( zVIEW  lpTaskView,
                  zPCHAR pchIndexName,
                  zPCHAR pchOwner,
                  zPCHAR pchTableName,
                  zLONG  f )
{
   zCHAR szLine[ 500 ];

   #if defined( SQLSERVER )
      sprintf_s( szLine, zsizeof( szLine), "DROP INDEX %s%s.%s %s",
                pchOwner, pchTableName, pchIndexName, LINE_TERMINATOR );
   #else
      sprintf_s( szLine, zsizeof( szLine ), "DROP INDEX %s ON %s%s %s",
                pchIndexName, pchOwner, pchTableName, LINE_TERMINATOR );
   #endif

   if ( fnWriteLine( lpTaskView, f, szLine ) < 0 )
      return( -1 );

   return( 0 );
}

zSHORT LOCALOPER
fnBuildColumn( zVIEW vDTE, zLONG f, zPCHAR pchLine )  // pchLine length is 500
{
   zCHAR    szColName[ MAX_NAME_LTH + 1 ];
   zPCHAR   pchDataType;
   zPCHAR   pchEnd, pch;
   zLONG    lLth;
   zLONG    lEndRemainingLth;
   zUSHORT  nMaxColumnNameLth = MAX_COLUMNNAME_LTH;
   zCHAR    szDBH_DataObjectName[ zZEIDON_NAME_LTH + 1 ];
   zVIEW    vDBH_Data;
   zVIEW    vTZTEDBLO = 0;
   zVIEW    vTZDBHODO = 0;
   zBOOL    bTimestampAsString = FALSE;

   // If it exists get the object that defines the dbhandler type.
   GetViewByName( &vTZTEDBLO, "TZTEDBLO", vDTE, zLEVEL_TASK );
   if ( vTZTEDBLO )
      SetCursorFirstEntityByAttr( vTZTEDBLO, "TE_DBMS_Source", "DBMS", vDTE, "TE_DBMS_Source", "DBMS", 0 );

   // Try to get the OI that contains DBH-specific data.
   SetOI_FromBlob( &vDBH_Data, szDBH_DataObjectName, vDTE, vDTE, "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

#if defined( ACCESS ) || defined( MYSQL ) || defined( ODBC ) || \
    defined( POSTGRESQL ) || defined( SQLSERVER )

   // Try to get the ODBC definition.
   SetOI_FromBlob( &vTZDBHODO, 0, vDTE, vTZTEDBLO, "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

   // Check to see if there is DBH data set in the TE.
   if ( vDBH_Data )
   {
      zLONG l;

      bTimestampAsString = ( CompareAttributeToString( vDBH_Data, "ODBC", "TimestampAsString", "Y" ) == 0 );

      if ( GetIntegerFromAttribute( &l, vDBH_Data, "ODBC", "MaxColumnNameLength" ) != -1 )
      {
         nMaxColumnNameLth = (zSHORT) l;
      }
   }
   else
   // Check to see if there is DBH data set in the DB List object.
   if ( vTZDBHODO )
   {
      bTimestampAsString = (CompareAttributeToString( vTZDBHODO, "ODBC", "TimestampAsString", "Y" ) == 0);
   }
   else
   {
      // If we get here then no info was set for this DBH, so use defaults.
      bTimestampAsString = FALSE;
   }

   if ( vTZDBHODO )
      DropView( vTZDBHODO );

#endif

   if ( vDBH_Data )
      DropView( vDBH_Data );

   GetStringFromAttribute( szColName, zsizeof( szColName ), vDTE, "TE_FieldDataRel", "Name" );
   GetAddrForAttribute( &pchDataType, vDTE, "TE_FieldDataRel", "DataType" );
   RemoveBrackets( szColName );

   lLth = zstrlen( pchLine );
   pchEnd = pchLine + lLth;
   lEndRemainingLth = 500 - lLth;
   sprintf_s( pchEnd, lEndRemainingLth, "%-*s", nMaxColumnNameLth, szColName );
   lLth = zstrlen( pchEnd );
   pchEnd = pchEnd + lLth;
   lEndRemainingLth -= lLth;

#if defined( ACCESS )

   switch ( pchDataType[ 0 ] )
   {
      case zTYPE_STRING:
      case zTYPE_FIXEDCHAR:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " TEXT( %ld )", lLth );

         break;

      case zTYPE_BLOB:
         sprintf_s( pchEnd, lEndRemainingLth, " LONGBINARY" );
         break;

      case zTYPE_INTEGER:
         sprintf_s( pchEnd, lEndRemainingLth, " INTEGER" );
         break;

      case zTYPE_DECIMAL:
         sprintf_s( pchEnd, lEndRemainingLth, " DOUBLE" );
         break;

      case zTYPE_DATETIME:
      case zTYPE_TIME:
         if ( bTimestampAsString )
            sprintf_s( pchEnd, lEndRemainingLth, " TEXT( 25 )" );
         else
         {
            switch ( pchDataType[ 0 ] )
            {
               case zTYPE_DATETIME:
                  sprintf_s( pchEnd, lEndRemainingLth, " DATETIME" );
                  break;

               case zTYPE_TIME:
                  sprintf_s( pchEnd, lEndRemainingLth, " TIME" );
                  break;
            }
         }

         break;

      case zTYPE_DATE:
         sprintf_s( pchEnd, lEndRemainingLth, " DATE" );
         break;

      // ===
      // === Non-standard types follow here.
      // ===

      // Long text fields.
      case 'V':
         sprintf_s( pchEnd, lEndRemainingLth, " MEMO" );
         break;

      // TimeStampEx
      case 'X':
         sprintf_s( pchEnd, lEndRemainingLth, " TEXT( 30 )" );
         break;

      default:
      {
         zCHAR szTableName[ MAX_TABLENAME_LTH + 1 ];
         zCHAR szMsg[ 300 ];

         GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
         sprintf_s( szMsg, zsizeof( szMsg ), "Invalid DataType '%s' for attribute %s.%s",
                    pchDataType, szTableName, szColName );
         SysMessageBox( vDTE, "SQLBASE DDL Generator", szMsg, 1 );
         return( -1 );
      }

   } // switch ( pchDataType[ 0 ] )...

#elif defined( DB2 )

   switch ( pchDataType[ 0 ] )
   {
      case zTYPE_STRING:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " VARCHAR( %ld )", lLth );

         break;

      case zTYPE_FIXEDCHAR:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " CHAR( %ld )", lLth );

         break;

      case zTYPE_BLOB:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " BLOB( %ld )", lLth );
         break;

      case zTYPE_DATETIME:
         sprintf_s( pchEnd, lEndRemainingLth, " TIMESTAMP" );
         break;

      case zTYPE_INTEGER:
         sprintf_s( pchEnd, lEndRemainingLth, " INTEGER" );
         break;

      case zTYPE_DECIMAL:
      {
         zLONG nScale;

         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         if ( lLth > 31 )
            lLth = 31;

         GetIntegerFromAttribute( &nScale, vDTE, "TE_FieldDataRel", "SQL_SCALE" );

         sprintf_s( pchEnd, lEndRemainingLth, " DECIMAL( %ld,%ld )", lLth, nScale );
         break;
      }

      case zTYPE_DATE:
         sprintf_s( pchEnd, lEndRemainingLth, " DATE" );
         break;

      case zTYPE_TIME:
         sprintf_s( pchEnd, lEndRemainingLth, " TIME" );
         break;

      // ===
      // === Non-standard types follow here.
      // ===

      case 'V':
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " CLOB( %ld )", lLth );
         break;

      // TimeStampEx
      case 'X':
         sprintf_s( pchEnd, lEndRemainingLth, " VARCHAR( 30 )" );
         break;

      default:
      {
         zCHAR szTableName[ MAX_TABLENAME_LTH + 1 ];
         zCHAR szMsg[ 300 ];

         GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
         sprintf_s( szMsg, zsizeof( szMsg ), "Invalid DataType '%s' for attribute %s.%s",
                    pchDataType, szTableName, szColName );
         SysMessageBox( vDTE, "SQLBASE DDL Generator", szMsg, 1 );
         return( -1 );
      }

   } // switch ( pchDataType[ 0 ] )...

#elif defined( MYSQL )

   switch ( pchDataType[ 0 ] )
   {
      case zTYPE_STRING:
      case zTYPE_FIXEDCHAR:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " varchar( %ld )", lLth );

         break;

      case zTYPE_BLOB:
         sprintf_s( pchEnd, lEndRemainingLth, " longblob" );
         break;

      case zTYPE_DATETIME:
         sprintf_s( pchEnd, lEndRemainingLth, " datetime" );
         break;

      case zTYPE_INTEGER:
         sprintf_s( pchEnd, lEndRemainingLth, " int" );
         break;

      case zTYPE_DECIMAL:
         sprintf_s( pchEnd, lEndRemainingLth, " double" );
         break;

      case zTYPE_DATE:
         sprintf_s( pchEnd, lEndRemainingLth, " datetime" );
         break;

      case zTYPE_TIME:
         sprintf_s( pchEnd, lEndRemainingLth, " datetime" );
         break;

      // ===
      // === Non-standard types follow here.
      // ===

      case 'V':
         sprintf_s( pchEnd, lEndRemainingLth, " longtext" );
         break;

      case 'A':
      {
         zPCHAR   pchKeyType;

         GetAddrForAttribute( &pchKeyType, vDTE, "TE_FieldDataRel", "DataOrRelfieldOrSet" );
         if ( pchKeyType[ 0 ] == 'D' )
         {
            // The key type is 'D' for data which means it's the main key.
#if defined( SQLITE )
          sprintf_s( pchEnd, lEndRemainingLth, " INTEGER PRIMARY KEY " );
#else
          sprintf_s( pchEnd, lEndRemainingLth, " SERIAL" );
#endif
         }
         else
         {
            // This must be a FK so don't declare it as SERIAL/KEY.
            sprintf_s( pchEnd, lEndRemainingLth, " INTEGER" );
         }

         break;
      }

      // TimeStampEx
      case 'X':
         sprintf_s( pchEnd, lEndRemainingLth, " varchar( 30 )" );
         break;

      default:
      {
         zCHAR szTableName[ MAX_TABLENAME_LTH + 1 ];
         zCHAR szMsg[ 300 ];

         GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
         sprintf_s( szMsg, zsizeof( szMsg ), "Invalid DataType '%s' for attribute %s.%s",
                    pchDataType, szTableName, szColName );
         SysMessageBox( vDTE, "SQL DDL Generator", szMsg, 1 );
         return( -1 );
      }

   } // switch ( pchDataType[ 0 ] )...

#elif defined( SQLBASE ) || defined( ODBC )

   switch ( pchDataType[ 0 ] )
   {
      case zTYPE_STRING:
      case zTYPE_FIXEDCHAR:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " CHAR( %ld )", lLth );

         break;

      case zTYPE_BLOB:
         sprintf_s( pchEnd, lEndRemainingLth, " LONG VARCHAR" );
         break;

      case zTYPE_INTEGER:
         sprintf_s( pchEnd, lEndRemainingLth, " INTEGER" );
         break;

      case zTYPE_DECIMAL:
      {
         zLONG nScale;

         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         GetIntegerFromAttribute( &nScale, vDTE, "TE_FieldDataRel", "SQL_SCALE" );

         sprintf_s( pchEnd, lEndRemainingLth, " DECIMAL( %ld,%ld )", lLth, nScale );
         break;
      }

   #ifdef ODBC

      case zTYPE_DATETIME:
      case zTYPE_TIME:
         if ( bTimestampAsString )
            sprintf_s( pchEnd, lEndRemainingLth, " TEXT( 25 )" );
         else
         {
            switch ( pchDataType[ 0 ] )
            {
               case zTYPE_DATETIME:
                  sprintf_s( pchEnd, lEndRemainingLth, " DATETIME" );
                  break;

               case zTYPE_TIME:
                  sprintf_s( pchEnd, lEndRemainingLth, " TIME" );
                  break;
            }
         }

         break;

      case zTYPE_DATE:
         sprintf_s( pchEnd, lEndRemainingLth, " DATE" );
         break;

   #else
      case zTYPE_DATETIME:
         sprintf_s( pchEnd, lEndRemainingLth, " TIMESTAMP" );
         break;

      case zTYPE_DATE:
         sprintf_s( pchEnd, lEndRemainingLth, " DATE" );
         break;

      case zTYPE_TIME:
         sprintf_s( pchEnd, lEndRemainingLth, " TIME" );
         break;
   #endif

      // ===
      // === Non-standard types follow here.
      // ===

      case 'V':
         sprintf_s( pchEnd, lEndRemainingLth, " LONG VARCHAR" );
         break;

      // TimeStampEx
      case 'X':
         sprintf_s( pchEnd, lEndRemainingLth, " CHAR( 30 )" );
         break;

      default:
      {
         zCHAR szTableName[ MAX_TABLENAME_LTH + 1 ];
         zCHAR szMsg[ 300 ];

         GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
         sprintf_s( szMsg, zsizeof( szMsg ), "Invalid DataType '%s' for attribute %s.%s",
                    pchDataType, szTableName, szColName );
         SysMessageBox( vDTE, "SQLBASE DDL Generator", szMsg, 1 );
         return( -1 );
      }

   } // switch ( pchDataType[ 0 ] )...

#elif defined( POSTGRESQL )

   switch ( pchDataType[ 0 ] )
   {
      case zTYPE_STRING:
      case zTYPE_FIXEDCHAR:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " varchar( %ld )", lLth );

         break;

      case zTYPE_BLOB:
         sprintf_s( pchEnd, lEndRemainingLth, " bytea" );
         //sprintf_s( pchEnd, lEndRemainingLth, " text" );
         break;

      case zTYPE_DATETIME:
         sprintf_s( pchEnd, lEndRemainingLth, " timestamp" );
         break;

      case zTYPE_INTEGER:
         sprintf_s( pchEnd, lEndRemainingLth, " int" );
         break;

      case zTYPE_DECIMAL:
         sprintf_s( pchEnd, lEndRemainingLth, " float4" );
         break;

      case zTYPE_DATE:
         sprintf_s( pchEnd, lEndRemainingLth, " timestamp" );
         break;

      case zTYPE_TIME:
         sprintf_s( pchEnd, lEndRemainingLth, " timestamp" );
         break;

      // ===
      // === Non-standard types follow here.
      // ===

      case 'V':
         sprintf_s( pchEnd, lEndRemainingLth, " text" );
         break;

      // TimeStampEx
      case 'X':
         sprintf_s( pchEnd, lEndRemainingLth, " varchar( 30 )" );
         break;

      default:
      {
         zCHAR szTableName[ MAX_TABLENAME_LTH + 1 ];
         zCHAR szMsg[ 300 ];

         GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
         sprintf_s( szMsg, zsizeof( szMsg ), "Invalid DataType '%s' for attribute %s.%s",
                    pchDataType, szTableName, szColName );
         SysMessageBox( vDTE, "SQL DDL Generator", szMsg, 1 );
         return( -1 );
      }

   } // switch ( pchDataType[ 0 ] )...

#elif defined( SQLSERVER )

   switch ( pchDataType[ 0 ] )
   {
      case zTYPE_STRING:
      case zTYPE_FIXEDCHAR:
         GetIntegerFromAttribute( &lLth, vDTE, "TE_FieldDataRel", "Length" );
         sprintf_s( pchEnd, lEndRemainingLth, " varchar( %ld )", lLth );

         break;

      case zTYPE_BLOB:
         sprintf_s( pchEnd, lEndRemainingLth, " varbinary(max)" );
         break;

      case zTYPE_DATETIME:
         sprintf_s( pchEnd, lEndRemainingLth, " datetime" );
         break;

      case zTYPE_INTEGER:
         sprintf_s( pchEnd, lEndRemainingLth, " int" );
         break;

      case zTYPE_DECIMAL:
         sprintf_s( pchEnd, lEndRemainingLth, " float" );
         break;

      case zTYPE_DATE:
         sprintf_s( pchEnd, lEndRemainingLth, " datetime" );
         break;

      case zTYPE_TIME:
         sprintf_s( pchEnd, lEndRemainingLth, " datetime" );
         break;

      // ===
      // === Non-standard types follow here.
      // ===

      case 'V':
         sprintf_s( pchEnd, lEndRemainingLth, " nvarchar(max)" );
         break;

      // TimeStampEx
      case 'X':
         sprintf_s( pchEnd, lEndRemainingLth, " varchar( 30 )" );
         break;

      default:
      {
         zCHAR szTableName[ MAX_TABLENAME_LTH + 1 ];
         zCHAR szMsg[ 300 ];

         GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
         sprintf_s( szMsg, zsizeof( szMsg ), "Invalid DataType '%s' for attribute %s.%s",
                    pchDataType, szTableName, szColName );
         SysMessageBox( vDTE, "SQL DDL Generator", szMsg, 1 );
         return( -1 );
      }

   } // switch ( pchDataType[ 0 ] )...
#endif

   // Space out the data type string.
   for ( pch = pchEnd + zstrlen( pchEnd );
         pch < pchEnd + MAX_DATATYPE_LTH;
         pch++ )
   {
      *pch = ' ';
   }

   *pch = 0;
   lEndRemainingLth -= (pch - pchEnd);
   pchEnd = pch;

   // Check to see if column can be NULL.
   if ( CompareAttributeToString( vDTE, "TE_FieldDataRel", "SQL_NULLS", "Y" ) == 0  )
   {

      // KJS 02/16/17 - Do I want to check if this is POSTGRES and the system generated key and if so set to 'PRIMARY KEY'??????
#if defined( POSTGRESQL )
      if ( SetCursorFirstEntityByAttr( vDTE, "TE_FieldDataRelKey", "ZKey",
                                       vDTE, "TE_FieldDataRel", "ZKey", "TE_TablRec" ) >= 0 )
      {
         if ( CheckExistenceOfEntity( vDTE, "ER_Entity" ) >= zCURSOR_SET )

         if ( CheckExistenceOfEntity( vDTE, "ER_EntIdentifier" ) >= zCURSOR_SET &&
              CompareAttributeToString( vDTE, "ER_EntIdentifier", "SystemMaintained", "Y" ) == 0  )
         {
             strcat_s( pchEnd, lEndRemainingLth, "PRIMARY KEY" );

         }
         else
            strcat_s( pchEnd, lEndRemainingLth, NOT_NULL_FIELD );
      }
      else
         strcat_s( pchEnd, lEndRemainingLth, NOT_NULL_FIELD );


#else
         strcat_s( pchEnd, lEndRemainingLth, NOT_NULL_FIELD );
#endif
   }
   else
      strcat_s( pchEnd, lEndRemainingLth, NULL_FIELD );

// pchEnd = pchLine + zstrlen( pchLine );  no reason to do this as far as I can see ... dks 2015.11.13

   return( 0 );
}

zSHORT LOCALOPER
fnBuildFK_Index( zVIEW  vDTE, zLONG  f )
{
   zCHAR    szLine[ 500 ];
   zPCHAR   pch;
   zCHAR    szKeyName[ MAX_NAME_LTH + 1 ];
   zCHAR    szOwner[ MAX_TABLENAME_LTH + 1 ];
   zCHAR    szTableName[ MAX_TABLENAME_LTH + 1 ];
   zPCHAR   pchDefaultOwner;
   zCHAR    szWorkIdxName[ BUFF_SIZE * 2 + 1 ];
   zCHAR    szDBH_DataObjectName[ zZEIDON_NAME_LTH + 1 ];
   zUSHORT  nMaxTableNameLth = MAX_TABLENAME_LTH;
   zLONG    lZKey;
   zVIEW    vDBH_Data;
   zVIEW    vTZTEDBLO;
   zVIEW    vTZDBHODO = 0;

   GetAddrForAttribute( &pchDefaultOwner, vDTE, "TE_DBMS_Source",
                        "DefaultOwner" );
   if ( pchDefaultOwner == 0 || pchDefaultOwner[ 0 ] == 0 )
      pchDefaultOwner = 0;

   GetStringFromAttribute( szOwner, zsizeof( szOwner ), vDTE, "TE_TablRec", "SQL_TableOwner" );
   if ( szOwner[ 0 ] == 0 && pchDefaultOwner )
      strcpy_s( szOwner, zsizeof( szOwner ), pchDefaultOwner );

   if ( szOwner[ 0 ] )
      strcat_s( szOwner, zsizeof( szOwner ), "." );

   // If it exists get the object that defines the dbhandler type.
   GetViewByName( &vTZTEDBLO, "TZTEDBLO", vDTE, zLEVEL_TASK );
   if ( vTZTEDBLO )
      SetCursorFirstEntityByAttr( vTZTEDBLO, "TE_DBMS_Source", "DBMS", vDTE, "TE_DBMS_Source", "DBMS", 0 );

   // Try to get the OI that contains DBH-specific data.
   SetOI_FromBlob( &vDBH_Data, szDBH_DataObjectName, vDTE, vDTE, "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

#if defined( ACCESS ) || defined( MYSQL ) || defined( ODBC ) || \
    defined( POSTGRESQL ) || defined( SQLSERVER )

   // Try to get the ODBC definition.
   SetOI_FromBlob( &vTZDBHODO, 0, vDTE, vTZTEDBLO, "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

   // Check to see if there is DBH data set in the TE.
   if ( vDBH_Data )
   {
      zLONG l;

      // Check to see if there is an max length override.
      if ( GetIntegerFromAttribute( &l, vDBH_Data, "ODBC", "MaxTableNameLength" ) != -1 )
      {
         nMaxTableNameLth = (zSHORT) l;
      }
   }

   if ( vTZDBHODO )
      DropView( vTZDBHODO );
#endif

   if ( vDBH_Data )
      DropView( vDBH_Data );

   GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
   RemoveBrackets( szTableName );

   // Generate a comment identifying the relationship.
   GetAddrForAttribute( &pch, vDTE, "TE_FieldDataRel", "Desc" );
   if ( pch && pch[ 0 ] )
   {
      sprintf_s( szLine, zsizeof( szLine ), "%s Index for Relationship - '%s' %s", COMMENT_START, pch, COMMENT_END );

      if ( fnWriteLine( vDTE, f, szLine ) < 0 )
         return( -1 );
   }

   GetIntegerFromAttribute( &lZKey, vDTE, "TE_FieldDataRel", "ZKey" );
   GetStringFromAttribute( szKeyName, zsizeof( szKeyName ), vDTE, "TE_FieldDataRel", "Name" );
   RemoveBrackets( szKeyName );

   // The base name for the index is a concatenation of the table and key name.
   // To ensure that the index name is unique, we also use the zkey value.
   // NOTE: Becaues of a bug in UfCompressName, we tack on a extra '0' to the
   // name so that the zkey does not get truncated.
   sprintf_s( szWorkIdxName, zsizeof( szWorkIdxName ), "%s_%s_%ld0", szTableName, szKeyName, lZKey );

   // Make sure that the index name is a valid length.
   UfCompressName( szWorkIdxName, szWorkIdxName, nMaxTableNameLth, "", "B", "", "B_AEIOUYBCDFGHJKLMNPQRSTVWXZ", 0 );

   sprintf_s( szLine, zsizeof( szLine ), "CREATE INDEX %s%s %s", szOwner, szWorkIdxName, CONTINUATION_STR );
   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      return( -1 );

   sprintf_s( szLine, zsizeof( szLine ), "      ON %s%s ( %s", szOwner, szTableName, CONTINUATION_STR );
   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      return( -1 );

   // Write Key-Name.
   sprintf_s( szLine, zsizeof( szLine ), "%*s %s ) %s", (zSHORT) COLUMN_INDENT, " ", szKeyName, LINE_TERMINATOR );
   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      return( -1 );

   // Write a blank line.
   if ( fnWriteLine( vDTE, f, " " ) < 0 )
      return( -1 );

   return( 0 );
}

zSHORT LOCALOPER
fnBuildIndexFromTablRecKey( zVIEW vDTE, zBOOL bUnique, zLONG f )
{
   zSHORT   nLoop;
   zCHAR    szLine[ 500 ];
   zCHAR    szOwner[ MAX_TABLENAME_LTH + 1 ];
   zPCHAR   pchDefaultOwner;
   zCHAR    szDBH_DataObjectName[ zZEIDON_NAME_LTH + 1 ];
   zUSHORT  nMaxTableNameLth = MAX_TABLENAME_LTH;
   zVIEW    vDBH_Data;
   zVIEW    vTZTEDBLO;
   zVIEW    vTZDBHODO = 0;
   zCHAR    szTableName[ MAX_NAME_LTH + 1 ];
   zCHAR    szName[ MAX_NAME_LTH + 1 ];
   zCHAR    szWorkIdxName[ BUFF_SIZE * 2 + 1 ];


   GetAddrForAttribute( &pchDefaultOwner, vDTE, "TE_DBMS_Source",
                        "DefaultOwner" );
   if ( pchDefaultOwner == 0 || pchDefaultOwner[ 0 ] == 0 )
      pchDefaultOwner = 0;

   GetStringFromAttribute( szOwner, zsizeof( szOwner ), vDTE, "TE_TablRec", "SQL_TableOwner" );
   if ( szOwner[ 0 ] == 0 && pchDefaultOwner )
      strcpy_s( szOwner, zsizeof( szOwner ), pchDefaultOwner );

   if ( szOwner[ 0 ] )
      strcat_s( szOwner, zsizeof( szOwner ), "." );

   // If it exists get the object that defines the dbhandler type.
   GetViewByName( &vTZTEDBLO, "TZTEDBLO", vDTE, zLEVEL_TASK );
   if ( vTZTEDBLO )
      SetCursorFirstEntityByAttr( vTZTEDBLO, "TE_DBMS_Source", "DBMS", vDTE, "TE_DBMS_Source", "DBMS", 0 );

   // Try to get the OI that contains DBH-specific data.
   SetOI_FromBlob( &vDBH_Data, szDBH_DataObjectName, vDTE, vDTE, "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

#if defined( ACCESS ) || defined( MYSQL ) || defined( ODBC ) || defined( POSTGRESQL ) || defined( SQLSERVER )

   // Try to get the ODBC definition.
   SetOI_FromBlob( &vTZDBHODO, 0, vDTE, vTZTEDBLO, "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

   // Check to see if there is DBH data set in the TE.
   if ( vDBH_Data )
   {
      zLONG l;

      // Check to see if there is an max length override.
      if ( GetIntegerFromAttribute( &l, vDBH_Data, "ODBC", "MaxTableNameLength" ) != -1 )
      {
         nMaxTableNameLth = (zSHORT) l;
      }
   }

   if ( vTZDBHODO )
      DropView( vTZDBHODO );
#endif

   if ( vDBH_Data )
      DropView( vDBH_Data );

   // Write comment.
   if ( CheckExistenceOfEntity( vDTE, "ER_Entity" ) >= zCURSOR_SET )
   {
      zPCHAR pch;

      GetAddrForAttribute( &pch, vDTE, "ER_Entity", "Name" );
      sprintf_s( szLine, zsizeof( szLine ), "%s Main key for Entity - %s %s", COMMENT_START, pch, COMMENT_END );

      if ( fnWriteLine( vDTE, f, szLine ) < 0 )
         return( -1 );
   }

   GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
   RemoveBrackets( szTableName );

   // If an IndexName value exists in TE_TablRecKey, use it.  Otherwise use the Name value.
   GetStringFromAttribute( szName, zsizeof( szName ), vDTE, "TE_TablRecKey", "IndexName" );
   if ( szName[ 0 ] == 0 )
   {
      zCHAR  szEntityName[ MAX_NAME_LTH + 1 ];
      zLONG  lZKey;

      GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vDTE, "TE_TablRec", "Name" );
      RemoveBrackets( szEntityName );

      GetStringFromAttribute( szName, zsizeof( szName ), vDTE, "TE_TablRecKey", "Name" );
      RemoveBrackets( szName );

      GetIntegerFromAttribute( &lZKey, vDTE, "TE_FieldDataRelKey", "ZKey" );

      // The base name for the index is a concatenation of the table and key name.
      // To ensure that the index name is unique, we also use the zkey value.
      // NOTE: Becaues of a bug in UfCompressName, we tack on a extra '0' to
      // the name so that the zkey does not get truncated.
      if ( bUnique )
         sprintf_s( szWorkIdxName, zsizeof( szWorkIdxName ), "U%s_%s_%ld0", szEntityName, szName, lZKey );
      else
         sprintf_s( szWorkIdxName, zsizeof( szWorkIdxName ), "%s_%s_%ld0", szEntityName, szName, lZKey );
   }
   else
   {
      RemoveBrackets( szName );
      sprintf_s( szWorkIdxName, zsizeof( szWorkIdxName ), "%s", szName );
   }

   // Make sure that the index name is a valid length.
   UfCompressName( szWorkIdxName, szWorkIdxName, nMaxTableNameLth, "", "B", "", "B_AEIOUYBCDFGHJKLMNPQRSTVWXZ", 0 );

   if ( bUnique )
   {
      sprintf_s( szLine, zsizeof( szLine ), "CREATE UNIQUE INDEX %s%s %s", szOwner, szWorkIdxName, CONTINUATION_STR );
   }
   else
      sprintf_s( szLine, zsizeof( szLine ), "CREATE INDEX %s%s %s", szOwner, szWorkIdxName, CONTINUATION_STR );


   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      return( -1 );

   sprintf_s( szLine, zsizeof( szLine ), "      ON %s%s ( %s", szOwner, szTableName, CONTINUATION_STR );

   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      return( -1 );

   //=================================================================
   //
   // Generate column names for index.
   //
   //=================================================================
   nLoop = SetCursorFirstEntity( vDTE, "TE_FieldDataRelKey", 0 );
   while( nLoop >= zCURSOR_SET )
   {
      GetStringFromAttribute( szName, zsizeof( szName ), vDTE, "TE_FieldDataRelKey", "Name" );
      RemoveBrackets( szName );

      nLoop = SetCursorNextEntity( vDTE, "TE_FieldDataRelKey", 0 );
      if ( nLoop >= zCURSOR_SET  )
      {
         // More keys coming, so print line with continuation stuff.
         sprintf_s( szLine, zsizeof( szLine ), "%*s %s, %s", (zSHORT) COLUMN_INDENT, " ", szName, CONTINUATION_STR );
      }
      else
      {
         // No more keys, so end current command.
         sprintf_s( szLine, zsizeof( szLine ), "%*s %s ) %s", (zSHORT) COLUMN_INDENT, " ", szName, LINE_TERMINATOR );
      }

      if ( fnWriteLine( vDTE, f, szLine ) < 0 )
         return( -1 );

   } // while ( nLoop >= zCURSOR_SET )...

   return( 0 );
}

zSHORT LOCALOPER
fnBuildCreateMainIndex( zVIEW vDTE, zLONG f )
{
   zBOOL    bFirstIndex;
   zSHORT   nLoop;

   // Loop through each of the keys for the current table.
   bFirstIndex = TRUE;
   for ( nLoop = SetCursorFirstEntity( vDTE, "TE_TablRecKey", 0 );
         nLoop >= zCURSOR_SET;
         nLoop = SetCursorNextEntity( vDTE, "TE_TablRecKey", 0 ) )

   {
      if ( fnBuildIndexFromTablRecKey( vDTE, bFirstIndex, f ) == -1 )
         return( -1 );

      bFirstIndex = FALSE;

   } // for ( "TE_TablRecKey"... )...

   // Write a blank line.
   if ( fnWriteLine( vDTE, f, " " ) < 0 )
      return( -1 );

   return( 0 );
}

zSHORT LOCALOPER
fnBuildCreateTable( zVIEW  vDTE, zLONG  f )
{
   zCHAR    szTableName[ MAX_NAME_LTH + 1 ];
   zPCHAR   pch;
   zPCHAR   pchEnd;
   zPCHAR   pchDefaultOwner;
   zCHAR    szLine[ 500 ];
   zCHAR    szOwner[ MAX_TABLENAME_LTH + 1 ];
   zCHAR    szDBH_DataObjectName[ zZEIDON_NAME_LTH + 1 ];
   zSHORT   nLoop;
   zVIEW    vDBH_Data;
   zVIEW    vTZTEDBLO = 0;
   zVIEW    vTZDBHODO = 0;
   zUSHORT  nMaxTableNameLth = MAX_TABLENAME_LTH;

   // If it exists get the object that defines the dbhandler type.
   GetViewByName( &vTZTEDBLO, "TZTEDBLO", vDTE, zLEVEL_TASK );
   if ( vTZTEDBLO )
      SetCursorFirstEntityByAttr( vTZTEDBLO, "TE_DBMS_Source", "DBMS",
                                  vDTE,      "TE_DBMS_Source", "DBMS", 0 );

   // Try to get the OI that contains DBH-specific data.
   SetOI_FromBlob( &vDBH_Data, szDBH_DataObjectName, vDTE, vDTE,
                   "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

#if defined( ACCESS ) || defined( MYSQL ) || defined( ODBC ) || \
    defined( POSTGRESQL ) || defined( SQLSERVER )

   // Try to get the ODBC definition.
   SetOI_FromBlob( &vTZDBHODO, 0, vDTE, vTZTEDBLO,
                   "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

   // Check to see if there is DBH data set in the TE.
   if ( vDBH_Data )
   {
      zLONG l;

      // Check to see if there is an max length override.
      if ( GetIntegerFromAttribute( &l, vDBH_Data, "ODBC",
                                    "MaxTableNameLength" ) != -1 )
      {
         nMaxTableNameLth = (zSHORT) l;
      }
   }

   if ( vTZDBHODO )
      DropView( vTZDBHODO );

#endif

   if ( vDBH_Data )
      DropView( vDBH_Data );

   GetAddrForAttribute( &pchDefaultOwner, vDTE, "TE_DBMS_Source",
                        "DefaultOwner" );
   if ( pchDefaultOwner == 0 || pchDefaultOwner[ 0 ] == 0 )
      pchDefaultOwner = 0;

   GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
   RemoveBrackets( szTableName );

   /* Position on the first column of the table */
   nLoop = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
   if ( nLoop < zCURSOR_SET )
      return( 0 );

   // Write the CREATE TABLE Statement and the comment only if
   // there are columns in a table.
   if ( CheckExistenceOfEntity( vDTE, "ER_Entity" ) >= zCURSOR_SET )
   {
      GetAddrForAttribute( &pch, vDTE, "ER_Entity", "Name" );
      sprintf_s( szLine, zsizeof( szLine ), "%s Entity - %s %s",
                 COMMENT_START, pch, COMMENT_END );

      if ( fnWriteLine( vDTE, f, szLine ) < 0 )
         return( -1 );
   }

   // Determine owner.
   GetStringFromAttribute( szOwner, zsizeof( szOwner ), vDTE, "TE_TablRec", "SQL_TableOwner" );
   if ( szOwner[ 0 ] == 0 && pchDefaultOwner )
      strcpy_s( szOwner, zsizeof( szOwner ), pchDefaultOwner );

   if ( szOwner[ 0 ] )
      strcat_s( szOwner, zsizeof( szOwner ), "." );

   sprintf_s( szLine, zsizeof( szLine ), "CREATE TABLE %s%s ( %s",
              szOwner, szTableName, CONTINUATION_STR );

   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      return( -1 );

   //=================================================================
   //
   // Generate column definitions.
   //
   //=================================================================

   // Loop for each column in the table.
   while ( nLoop >= zCURSOR_SET )
   {
      sprintf_s( szLine, zsizeof( szLine ), "%*s ", (zSHORT) COLUMN_INDENT, " " );
      fnBuildColumn( vDTE, f, szLine );

      pchEnd = &szLine[ zstrlen( szLine ) ];

      nLoop = SetCursorNextEntity( vDTE, "TE_FieldDataRel", 0 );
      if ( nLoop >= zCURSOR_SET )
         // More columns comming, so add continuation stuff.
         sprintf_s( pchEnd, MAX_NAME_LTH - zstrlen( szLine ), ", %s", CONTINUATION_STR );
      else
         // No more columns, so terminate line.
         sprintf_s( pchEnd, MAX_NAME_LTH - zstrlen( szLine ), " ) %s", LINE_TERMINATOR );

      if ( fnWriteLine( vDTE, f, szLine ) < 0 )
         return( -1 );

   } // while ( nLoop >= zCURSOR_SET )...

   // Write a blank line.
   if ( fnWriteLine( vDTE, f, " " ) < 0 )
      return( -1 );

   #if COMMIT_EVERY_TABLE
      if ( fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
         return( -1 );

      if ( fnWriteLine( vDTE, f, " " ) < 0 )
         return( -1 );
   #endif

   return( 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  This routine generates the DDL and is called from the Zeidon
//  Technical Environment Dialog.
//
//  The following describes the standard arguments for DDL generation:
//
//     vDTE - View to Technical Environment we want to build DDL for.
//     vEMD - View to E/R diagram.  Not always used.
//     pchFileName - Pointer to buffer containing the directory we should
//             write the DDL to.  This buffer can be assumed large enough to
//             contain a full file name.  The directory can be changed.
//     vSubtask - View to window, to send a DIL-message or an error message
//
//  Returns: 0           - Everything OK.
//           zCALL_ERROR - DDL not generated.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT OPERATION
BuildDDL( zVIEW  vDTE,
          zVIEW  vEMD,
          zPCHAR pchFileName,
          zLONG  lMaxNameLth,
          zVIEW  vSubtask )
{
   zPCHAR   pchTableName;
   zPCHAR   pchDatabaseName;
   zPCHAR   pch;
   zLONG    f = -1;
   zCHAR    szLine[ 256 ];
   zLONG    lLth;
   zSHORT   nRC = zCALL_ERROR;
   zSHORT   nRCTable;
   zSHORT   nLoop;
   zVIEW    vTZTEDBLO;
   zVIEW    vDBH_Data = 0;
   zCHAR    szDBH_DataObjectName[ zZEIDON_NAME_LTH + 1 ];
   zUSHORT  nMaxTableNameLth = MAX_TABLENAME_LTH;
   zCHAR    szTableName[ MAX_NAME_LTH + 1 ];
   zCHAR    szEntityName[ MAX_NAME_LTH + 1 ];
   zPCHAR   pchDefaultOwner;
   zCHAR    szOwner[ MAX_TABLENAME_LTH + 1 ];
   zPCHAR   pchGenCreateIdxs   = "Y";
   zPCHAR   pchGenDropIdxs     = "N";
   zPCHAR   pchGenCreateTables = "Y";
   zPCHAR   pchGenDropTables   = "Y";

   zCHAR    szMsg[ 512 ];

#if defined( ACCESS ) || defined( MYSQL ) || defined( ODBC ) || \
    defined( POSTGRESQL ) || defined( SQLSERVER )
   zVIEW    vTZDBHODO;
#endif

   // If TE_DBMS_Source entity doesn't exist, then nothing to generate.
   if ( CheckExistenceOfEntity( vDTE, "TE_DBMS_Source" ) != zCURSOR_SET )
      return( zCALL_ERROR );

   // If it exists get the object that defines the dbhandler type.
   GetViewByName( &vTZTEDBLO, "TZTEDBLO", vSubtask, zLEVEL_TASK );
   if ( vTZTEDBLO )
      SetCursorFirstEntityByAttr( vTZTEDBLO, "TE_DBMS_Source", "DBMS",
                                  vDTE,      "TE_DBMS_Source", "DBMS", 0 );

   // Try to get the OI that contains DBH-specific data.
   SetOI_FromBlob( &vDBH_Data, szDBH_DataObjectName, vDTE, vDTE,
                   "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

#if defined( SQLITE )

   pchGenCreateIdxs   = "N";   // Don't generate indexes for Sqlite.

#elif defined( ACCESS ) || defined( MYSQL ) || defined( ODBC ) || defined( POSTGRESQL ) || defined( SQLSERVER )

   // Try to get the ODBC definition.
   SetOI_FromBlob( &vTZDBHODO, 0, vDTE, vTZTEDBLO,
                   "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

   // Check to see if there is DBH data set in the TE.
   if ( vDBH_Data )
   {
      zLONG l;

      // Check to see if there is an max length override.
      if ( GetIntegerFromAttribute( &l, vDBH_Data, "ODBC", "MaxTableNameLength" ) != -1 )
      {
         nMaxTableNameLth = (zSHORT) l;
      }

      // Get the conditional generate values.
      GetAddrForAttribute( &pchGenCreateTables, vDBH_Data, "ODBC", "GenCreateTables" );
      GetAddrForAttribute( &pchGenDropTables, vDBH_Data, "ODBC", "DropTables" );
      GetAddrForAttribute( &pchGenCreateIdxs, vDBH_Data, "ODBC", "GenCreateIdxs" );
      GetAddrForAttribute( &pchGenDropIdxs, vDBH_Data, "ODBC", "GenDropIdxs" );
   }

#endif

   // Create copies of views so we can safely change the cursors.
   CreateViewFromViewForTask( &vDTE, vDTE, 0 );
   CreateViewFromViewForTask( &vEMD, vEMD, 0 );

   //
   // Generate the DDL file name and open it.
   //
   lLth = zstrlen( pchFileName );
   GetStringFromAttribute( pchFileName + lLth, lMaxNameLth - lLth, vDTE, "TE_DBMS_Source", "Name" );

   // Make sure the filename isn't too long.
   if ( zstrlen( pchFileName + lLth ) > zBASE_FILENAME_LTH )
      pchFileName[ lLth + zBASE_FILENAME_LTH ] = 0;

   strcat_s( pchFileName, zMAX_FILENAME_LTH, ".ddl" );
   if ( (f = SysOpenFile( vDTE, pchFileName, COREFILE_WRITE )) < 0 )
      goto EndOfFunction;

   GetAddrForAttribute( &pchDatabaseName, vDTE, "TE_DBMS_Source", "Name" );

#ifdef CREATE_DB
   sprintf_s( szLine, zsizeof( szLine), "%s CREATE DATABASE %s %s %s", COMMENT_START,
              pchDatabaseName, COMMENT_END, LINE_TERMINATOR );
   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      goto EndOfFunction;
#endif

   //
   // Tell SQL processor what database to use.
   //

#if defined( DB2 )

   sprintf_s( szLine, zsizeof( szLine ), "CONNECT TO %s %s", pchDatabaseName, LINE_TERMINATOR );
   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      goto EndOfFunction;

#elif defined( MYSQL) || defined( SQLSERVER )

   #ifdef SQLITE
       // Skip the "USE" statement for SQLITE.
   #else
       sprintf_s( szLine, zsizeof( szLine ), "USE %s %s", pchDatabaseName, LINE_TERMINATOR );
       if ( fnWriteLine( vDTE, f, szLine ) < 0 )
         goto EndOfFunction;
   #endif

#elif defined( POSTGRESQL ) 

       sprintf_s( szLine, zsizeof( szLine ), "SET SCHEMA '%s' %s", pchDatabaseName, LINE_TERMINATOR );
       if ( fnWriteLine( vDTE, f, szLine ) < 0 )
         goto EndOfFunction;

#endif

   GetAddrForAttribute( &pchDefaultOwner, vDTE, "TE_DBMS_Source",
                        "DefaultOwner" );
   if ( pchDefaultOwner == 0 || pchDefaultOwner[ 0 ] == 0 )
      pchDefaultOwner = 0;

   //=================================================================
   //
   // Generate Drop Index statements.
   //
   //=================================================================
   if ( pchGenDropIdxs[ 0 ] != 'N' )
   {
      // Loop for each of the tables.
      for ( nRCTable = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
            nRCTable >= zCURSOR_SET;
            nRCTable = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
      {
         zUSHORT usForeignKeyCntForTable = 0;

         GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
         pchTableName = szTableName;
         RemoveBrackets( pchTableName );

         /* Position on the first column of the table */
         nLoop = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
         if ( nLoop < zCURSOR_SET )
            continue;

         // Write comment.
         if ( CheckExistenceOfEntity( vDTE, "ER_Entity" ) >= zCURSOR_SET )
         {
            GetAddrForAttribute( &pch, vDTE, "ER_Entity", "Name" );
            sprintf_s( szLine, zsizeof( szLine ), "%s Indexes for Entity - %s %s",
                       COMMENT_START, pch, COMMENT_END );

            if ( fnWriteLine( vDTE, f, szLine ) < 0 )
               goto EndOfFunction;
         }

         // Determine owner.
         GetStringFromAttribute( szOwner, zsizeof( szOwner ), vDTE, "TE_TablRec", "SQL_TableOwner" );
         if ( szOwner[ 0 ] == 0 && pchDefaultOwner )
            strcpy_s( szOwner, zsizeof( szOwner ), pchDefaultOwner );

         if ( szOwner[ 0 ] )
            strcat_s( szOwner, zsizeof( szOwner ), "." );

         //=================================================================
         //
         // Drop Unique Index.
         //
         //=================================================================

         // Loop through each of the keys for the current table.
         for ( nLoop = SetCursorFirstEntity( vDTE, "TE_TablRecKey", 0 );
               nLoop >= zCURSOR_SET;
               nLoop = SetCursorNextEntity( vDTE, "TE_TablRecKey", 0 ) )
         {
            zCHAR  szName[ MAX_NAME_LTH + 1 ];
            zCHAR  szWorkIdxName[ BUFF_SIZE * 2 + 1 ];

            // If an IndexName value exists in TE_TablRecKey, use it.  Otherwise
            // us the Name value.
            GetStringFromAttribute( szName, zsizeof( szName ), vDTE, "TE_TablRecKey", "IndexName");
            if ( szName[ 0 ] == 0 )
            {
               GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vDTE, "TE_TablRec", "Name" );
               RemoveBrackets( szEntityName );

               GetStringFromAttribute( szName, zsizeof( szName ), vDTE, "TE_TablRecKey", "Name" );
               RemoveBrackets( szName );

               sprintf_s( szWorkIdxName, zsizeof( szWorkIdxName ), "%s_%s", szEntityName, szName );
            }
            else
            {
               RemoveBrackets( szName );

               sprintf_s( szWorkIdxName, zsizeof( szWorkIdxName ), "%s", szName );
            }

            // Make sure that the index name is a valid length.
            UfCompressName( szWorkIdxName, szWorkIdxName, nMaxTableNameLth,
                            "", "B", "", "B_AEIOU", 1 );

            fnBuildDropIndex( vDTE, szWorkIdxName, szOwner, pchTableName, f );

         } // for ( "TE_TablRecKey"... )...

         //===============================================================
         //
         // Drop Index for ForeignKeys
         //
         //===============================================================

         // Loop through each of the keys for the current table.
         for ( nLoop = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
               nLoop >= zCURSOR_SET;
               nLoop = SetCursorNextEntity( vDTE, "TE_FieldDataRel", 0 ) )

         {
            zCHAR  szKeyName[ MAX_NAME_LTH + 1 ];
            zPCHAR pchKeyType;
            zCHAR  szWorkIdxName[ BUFF_SIZE * 2 + 1 ];

            // If the attribute is not a rel field try the next one.
            GetAddrForAttribute( &pchKeyType, vDTE, "TE_FieldDataRel",
                                 "DataOrRelfieldOrSet" );
            if ( pchKeyType[ 0 ] != 'R' )
               continue;

            // generate a comment identifying the relationship
            GetAddrForAttribute( &pch, vDTE, "TE_FieldDataRel", "Desc" );
            sprintf_s( szLine, zsizeof( szLine ), "%s Index for Relationship - '%s' %s",
                       COMMENT_START, pch, COMMENT_END );

            if ( fnWriteLine( vDTE, f, szLine ) < 0 )
               goto EndOfFunction;

            GetStringFromAttribute( szKeyName, zsizeof( szKeyName ), vDTE, "TE_FieldDataRel", "Name" );
            RemoveBrackets( szKeyName );
            sprintf_s( szWorkIdxName, zsizeof( szWorkIdxName ), "%s_%s", pchTableName, szKeyName );

            // Make sure that the index name is a valid length.
            // MAX_TABLENAME_LTH - 2 because of numbering the indexname
            // in the last two chars.
            UfCompressName( szWorkIdxName, szWorkIdxName, nMaxTableNameLth,
                            "", "B", "", "B_AEIOU", 1 );
            usForeignKeyCntForTable++;
            lLth = zstrlen( szWorkIdxName );
            sprintf_s( &szWorkIdxName[ lLth ], zsizeof( szWorkIdxName ) - lLth, "%02d", usForeignKeyCntForTable );

            fnBuildDropIndex( vDTE, szWorkIdxName, szOwner, pchTableName, f );

         } // for ( "TE_FieldDataRel" )...

         if ( fnWriteLine( vDTE, f, "" ) < 0 )
            goto EndOfFunction;

      } // for ( "TE_TableRec" )...

   } // if ( pchGenDropIdxs[ 0 ] != 'N' )...

   //=================================================================
   //
   // Generate Drop Table statements.
   //
   //=================================================================

   if ( pchGenDropTables[ 0 ] != 'N' )
   {
      for ( nRCTable = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
            nRCTable >= zCURSOR_SET;
            nRCTable = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
      {
         /* Position on the first column of the table */
         /* If the table has no columns no DROP statement */
         nRC = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
         if (nRC < zCURSOR_SET)
            continue;

         // Determine owner.
         GetStringFromAttribute( szOwner, zsizeof( szOwner ), vDTE, "TE_TablRec", "SQL_TableOwner" );
         if ( szOwner[ 0 ] == 0 && pchDefaultOwner )
            strcpy_s( szOwner, zsizeof( szOwner ), pchDefaultOwner );

         if ( szOwner[ 0 ] )
            strcat_s( szOwner, zsizeof( szOwner ), "." );

         GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vDTE, "TE_TablRec", "Name" );
         pch = szEntityName;
         RemoveBrackets( pch );

         #if defined( SQLITE )
            sprintf_s( szLine, zsizeof( szLine ), "DROP TABLE IF EXISTS %s%s %s", szOwner, pch, LINE_TERMINATOR );
         #elif defined( MYSQL )
            sprintf_s( szLine, zsizeof( szLine ), "DROP TABLE %s%s IF EXISTS %s", szOwner, pch, LINE_TERMINATOR );
         #elif defined( POSTGRESQL )
            sprintf_s( szLine, zsizeof( szLine ), "DROP TABLE IF EXISTS %s%s CASCADE%s", szOwner, pch, LINE_TERMINATOR );
         #else
            sprintf_s( szLine, zsizeof( szLine ), "DROP TABLE %s%s %s", szOwner, pch, LINE_TERMINATOR );
    #endif

         if ( fnWriteLine( vDTE, f, szLine ) < 0 )
            nRC = zCALL_ERROR;
      }

   #if defined( COMMIT_EVERY_TABLE )

      if ( fnWriteLine( vDTE, f, "" ) < 0 )
         goto EndOfFunction;

      if ( fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
         goto EndOfFunction;

   #endif

      if ( fnWriteLine( vDTE, f, "" ) < 0 )
         goto EndOfFunction;

   } // if ( pchGenDropTables[ 0 ] != 'N' )...

   //=================================================================
   //
   // Generate Create Table statements.
   //
   //=================================================================

   if ( pchGenCreateTables[ 0 ] != 'N' )
   {
      // Loop for each of the tables.
      for ( nRCTable = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
            nRCTable >= zCURSOR_SET;
            nRCTable = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
      {
         if ( fnBuildCreateTable( vDTE, f ) == -1 )
            goto EndOfFunction;
      } // for ( "TE_TableRec" )...

   } // if ( pchGenCreateTables[ 0 ] != 'N' )...

   //=================================================================
   //
   // Generate Create Index statements.
   //
   //=================================================================

   if ( pchGenCreateIdxs[ 0 ] != 'N' )
   {
      // Loop for each of the tables.
      for ( nRCTable = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
            nRCTable >= zCURSOR_SET;
            nRCTable = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
      {
         GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
         pchTableName = szTableName;
         RemoveBrackets( pchTableName );

         /* Position on the first column of the table */
         nLoop = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
         if ( nLoop < zCURSOR_SET )
            continue;

         if ( fnBuildCreateMainIndex( vDTE, f ) == -1 )
            goto EndOfFunction;

         if ( fnWriteLine( vDTE, f, " " ) < 0 )
            goto EndOfFunction;

         #if COMMIT_EVERY_TABLE
               if ( fnWriteLine( vDTE, f, " " ) < 0 )
                  goto EndOfFunction;

               if ( fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
                  goto EndOfFunction;
         #endif

         //===============================================================
         //
         // Generate Index for ForeignKeys
         //
         //===============================================================

         // Loop through each of the keys for the current table.

         for ( nLoop = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
               nLoop >= zCURSOR_SET;
               nLoop = SetCursorNextEntity( vDTE, "TE_FieldDataRel", 0 ) )

         {
            zPCHAR pchKeyType;

            // If the attribute is not a rel field try the next one.
            GetAddrForAttribute( &pchKeyType, vDTE, "TE_FieldDataRel",
                                 "DataOrRelfieldOrSet" );
            if ( pchKeyType[ 0 ] != 'R' )
               continue;

            if ( fnBuildFK_Index( vDTE, f ) == -1 )
               goto EndOfFunction;

            #if defined( COMMIT_EVERY_TABLE )

               if ( fnWriteLine( vDTE, f, "" ) < 0 )
                  goto EndOfFunction;

               if ( fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
                  goto EndOfFunction;

            #endif

            if ( fnWriteLine( vDTE, f, " " ) < 0 )
               goto EndOfFunction;

         } // for ( "TE_FieldDataRel" )...

   #if COMMIT_EVERY_TABLE
         if ( fnWriteLine( vDTE, f, " " ) < 0 )
            goto EndOfFunction;

          if ( fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
            goto EndOfFunction;
   #endif

      } // for ( "TE_TableRec" )...

   } // if ( pchGenCreateIdxs[ 0 ] != 'N' )...

   //=================================================================
   //
   // Loop through the table names again to create the "GRANT ALL" statements.
   //
   //=================================================================

#ifdef GRANT_ALL
   for ( nLoop = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
         nLoop >= zCURSOR_SET;
         nLoop = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
   {
      /* Position on the first column of the table */
      /* No GRANT if the are no columns in the table */
      nRC = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
      if (nRC < zCURSOR_SET)
         continue;

      // Determine owner.
      GetStringFromAttribute( szOwner, zsizeof( szOwner ), vDTE, "TE_TablRec", "SQL_TableOwner" );
      if ( szOwner[ 0 ] == 0 && pchDefaultOwner )
         strcpy_s( szOwner, zsizeof( szOwner ), pchDefaultOwner );

      if ( szOwner[ 0 ] )
         strcat_s( szOwner, zsizeof( szOwner ), "." );

      GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );
      pchTableName = szTableName;
      RemoveBrackets( pchTableName );
      sprintf_s( szLine, zsizeof( szLine ), "GRANT ALL ON %s%s TO PUBLIC %s",
                 szOwner, pchTableName, CONTINUATION_STR );

      if ( fnWriteLine( vDTE, f, szLine ) < 0 )
         goto EndOfFunction;

   } // for ( "TE_TableRec" )...
#endif

   if ( fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
      goto EndOfFunction;

   // If we get here, then everything is OK.
   nRC = 0;

EndOfFunction:
   if ( f != -1 )
      SysCloseFile( vSubtask, f, 0 );

   DropView( vDTE );
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
      SysMessageBox( vDTE, "Generate DDL", szMsg, 0 );
   }

   return( nRC );

} // BuildDDL

/////////////////////////////////////////////////////////////////////////////
//
//  This routine generates the DDL to synchronize the selected TE with
//  the database.  This assumes the current user can connect to the DB.
//
//  The following describes the standard arguments for DDL generation:
//
//     vDTE - View to Technical Environment we want to build DDL for.
//     vEMD - View to E/R diagram.  Not always used.
//     pchFileName - Pointer to buffer containing the directory we should
//             write the DDL to.  This buffer can be assumed large enough to
//             contain a full file name.  The directory can be changed.
//     vSubtask - View to window, to send a DIL-message or an error message
//
//  Returns: 0           - Everything OK.
//           zCALL_ERROR - DDL not generated.
//
/////////////////////////////////////////////////////////////////////////////
zSHORT OPERATION
BuildSyncDDL( zVIEW  vDTE,
              zVIEW  vEMD,
              zVIEW  vTZTEDBLO,
              zPCHAR pchFileName,
              zLONG  lMaxNameLth,
              zVIEW  vSubtask )
{
   LPLIBRARY hLibrary;
   zLONG     f = -1;
   zSHORT    (POPERATION pfn)( zVIEW, zPVIEW );
   zVIEW     vDB = 0;
   zVIEW     vBoth[ 2 ];
   zCHAR     szDLL[ zMAX_FILENAME_LTH + 1 ];
   zCHAR     szTableName[ MAX_TABLENAME_LTH + 1 ];
   zCHAR     szColumnName[ MAX_TABLENAME_LTH + 1 ];
   zCHAR     szOwner[ MAX_TABLENAME_LTH + 1 ];
   zCHAR     szLine[ 500 ];
   zPCHAR    pchDefaultOwner;
   zPCHAR    pchDBName;
   zPCHAR    pchDBDesc;
   zSHORT    k, nRC;
   zLONG     lLth;
   zSHORT    nReturn = zCALL_ERROR;
   zBOOL     bTableDropped;

   // Make copies of the views so we can safely change the cursors.
   CreateViewFromViewForTask( &vDTE, vDTE, 0 );
   CreateViewFromViewForTask( &vEMD, vEMD, 0 );

   // First thing we have to do is call the SQL DBH to load the current DB schema.
   GetStringFromAttribute( szDLL, zsizeof( szDLL ), vDTE, "TE_DBMS_Source", "Executable" );
   hLibrary = SysLoadLibrary( vSubtask, szDLL );
   if ( hLibrary )
   {
      pfn = SysGetProc( hLibrary, "RetrieveSchema" );
      if ( pfn )
      {
         (*pfn)( vDTE, &vDB );
      }
      else
      {
         MessageSend( vSubtask, "TE00422", "Physical Data Model",
                      "Couldn't find 'BuildSyncDDL' in Generater Executable",
                      zMSGQ_OBJECT_CONSTRAINT_ERROR, 0 );
      }

      SysFreeLibrary( vSubtask, hLibrary );
   }

   if ( vDB == 0 )
      return( -1 );

   //
   // Generate the DDL file name and open it.
   //
   lLth = zstrlen( pchFileName );
   GetStringFromAttribute( pchFileName + lLth, lMaxNameLth - lLth, vDTE, "TE_DBMS_Source", "Name" );
   strcat_s( pchFileName, zMAX_FILENAME_LTH, "_alter" );

   // Make sure the filename isn't too long.
   if ( zstrlen( pchFileName + lLth ) > zBASE_FILENAME_LTH )
      pchFileName[ lLth + zBASE_FILENAME_LTH ] = 0;

   strcat_s( pchFileName, zMAX_FILENAME_LTH, ".ddl" );
   if ( (f = SysOpenFile( vDTE, pchFileName, COREFILE_WRITE )) < 0 )
      goto EndOfFunction;

   GetAddrForAttribute( &pchDBName, vDTE, "TE_DBMS_Source", "Name" );
   GetAddrForAttribute( &pchDBDesc, vDTE, "TE_DBMS_Source", "Desc" );
   sprintf_s( szLine, zsizeof( szLine ), "%s Alter script for %s -- %s %s",
              COMMENT_START, pchDBName, pchDBDesc, COMMENT_END );
   if ( fnWriteLine( vDTE, f, szLine ) < 0 )
      goto EndOfFunction;

   GetAddrForAttribute( &pchDefaultOwner, vDTE,
                        "TE_DBMS_Source", "DefaultOwner" );
   if ( pchDefaultOwner == 0 || pchDefaultOwner[ 0 ] == 0 )
      pchDefaultOwner = 0;

   // Turn off the "MatchFound" flag for all the tables/columns.
   vBoth[ 0 ] = vDTE;
   vBoth[ 1 ] = vDB;
   for ( k = 0; k < 2; k++ )
   {
      for ( nRC = SetCursorFirstEntity( vBoth[ k ], "TE_TablRec", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vBoth[ k ], "TE_TablRec", 0 ) )
      {
         SetAttributeFromString( vBoth[ k ], "TE_TablRec", "MatchFound", "N" );

         for ( nRC = SetCursorFirstEntity( vBoth[ k ], "TE_FieldDataRel", 0 );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntity( vBoth[ k ], "TE_FieldDataRel", 0 ) )
         {
            SetAttributeFromString( vBoth[ k ], "TE_FieldDataRel", "MatchFound", "N" );
         }
      }
   }

   // Now look for matches.
   for ( nRC = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
   {
      zPCHAR pchTableName;

      if ( SetCursorFirstEntityByAttr( vDB, "TE_TablRec", "Name", vDTE, "TE_TablRec", "Name", 0 ) < zCURSOR_SET )
      {
         continue;
      }

      GetAddrForAttribute( &pchTableName, vDB, "TE_TablRec", "Name" );
      SetAttributeFromString( vDTE, "TE_TablRec", "MatchFound", "Y" );
      SetAttributeFromString( vDB,  "TE_TablRec", "MatchFound", "Y" );

      for ( nRC = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDTE, "TE_FieldDataRel", 0 ) )
      {
         zLONG  lDB_Lth;
         zLONG  lDTE_Lth;
         zCHAR  szDB_Type[ 10 ];
         zCHAR  szDTE_Type[ 10 ];
         zPCHAR pchColName;

         // Check to see if there is a field in the DB with the same
         // name.
         if ( SetCursorFirstEntityByAttr( vDB, "TE_FieldDataRel", "Name",
                                          vDTE, "TE_FieldDataRel",
                                          "Name", 0 ) < zCURSOR_SET )
         {
            // Nope.  No match found, continue with the next one.
            continue;
         }

         GetAddrForAttribute( &pchColName, vDB, "TE_FieldDataRel", "Name" );
         GetIntegerFromAttribute( &lDB_Lth,  vDB, "TE_FieldDataRel", "Length" );
         GetIntegerFromAttribute( &lDTE_Lth, vDTE, "TE_FieldDataRel", "Length" );
         GetStringFromAttribute( szDB_Type, zsizeof( szDB_Type ), vDB, "TE_FieldDataRel", "DataType" );
         GetStringFromAttribute( szDTE_Type, zsizeof( szDTE_Type ), vDTE, "TE_FieldDataRel", "DataType" );

         // Some datatypes need to be massaged before we compare them.
         #if defined( ACCESS ) || defined( MYSQL ) || defined( ODBC ) || \
             defined( POSTGRESQL ) || defined( SQLSERVER )

            switch ( szDB_Type[ 0 ] )
            {
               case zTYPE_DATE:
               case zTYPE_TIME:
               case zTYPE_DATETIME:
                  // In access, all date/time/timestamps are stored as the same
                  // datatype, so we need to set things up so they compare the same.
                  szDB_Type[ 0 ] = szDTE_Type[ 0 ];
                  break;
            }

            // We only care about the length for string types.
            if ( szDB_Type[ 0 ] != zTYPE_STRING || szDB_Type[ 0 ] != zTYPE_FIXEDCHAR )
               lDB_Lth = lDTE_Lth;

         #endif

         if ( lDB_Lth != lDTE_Lth || zstrcmp( szDB_Type, szDTE_Type ) != 0 )
         {
            #if 0
               zCHAR sz[ 500 ];

               sprintf_s( sz, zsizeof( sz ), "%s.%s TE Datatype = %s, Length = %d",
                          pchTableName, pchColName, szDTE_Type, lDTE_Lth );
               TraceLineS( sz, "" );
               sprintf_s( sz, zsizeof( sz ), "%s.%s DB Datatype = %s, Length = %d",
                          pchTableName, pchColName, szDB_Type, lDB_Lth );
               TraceLineS( sz, "" );
            #endif

            // Column is different somehow.
            SetAttributeFromString( vDTE, "TE_FieldDataRel", "MatchFound", "D" );
            SetAttributeFromString( vDB,  "TE_FieldDataRel", "MatchFound", "D" );
         }
         else
         {
            SetAttributeFromString( vDTE, "TE_FieldDataRel", "MatchFound", "Y" );
            SetAttributeFromString( vDB,  "TE_FieldDataRel", "MatchFound", "Y" );
         }

      }  // For each TE_FieldDataRel

   }  // For each TE_TablRec

   //
   // Print results.
   //

   // Create tables.
   for ( nRC = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
   {
      GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );

      // If table is in the DB, we don't need to create it.
      if ( CompareAttributeToString( vDTE, "TE_TablRec", "MatchFound", "N" ) != 0 )
         continue;

      if ( fnBuildCreateTable( vDTE, f ) == -1 )
         goto EndOfFunction;

      if ( fnBuildCreateMainIndex( vDTE, f ) == -1 )
         goto EndOfFunction;

      #if COMMIT_EVERY_TABLE
         if ( fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
            return( -1 );
      #endif

      // Create the indexes for the FKs.
      for ( nRC = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDTE, "TE_FieldDataRel", 0 ) )
      {
         zPCHAR pchKeyType;

         GetAddrForAttribute( &pchKeyType, vDTE, "TE_FieldDataRel",
                              "DataOrRelfieldOrSet" );
         if ( pchKeyType[ 0 ] == 'R' )
         {
            if ( fnBuildFK_Index( vDTE, f ) == -1 )
               goto EndOfFunction;
            #if defined( COMMIT_EVERY_TABLE )

               if ( fnWriteLine( vDTE, f, "" ) < 0 )
                  goto EndOfFunction;

               if ( fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
                  goto EndOfFunction;

            #endif
         }

      }  // For each TE_FieldDataRel

   }  // For each TE_TablRec

   // Add columns to tables.
   for ( nRC = SetCursorFirstEntity( vDTE, "TE_TablRec", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vDTE, "TE_TablRec", 0 ) )
   {
      zBOOL bFirstAlterOfTable;

      GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDTE, "TE_TablRec", "Name" );

      if ( CompareAttributeToString( vDTE, "TE_TablRec", "MatchFound", "N" ) == 0 )
      {
         // We alread created the table, so continue with the next one.
         continue;
      }

      bFirstAlterOfTable = TRUE;
      for ( nRC = SetCursorFirstEntity( vDTE, "TE_FieldDataRel", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDTE, "TE_FieldDataRel", 0 ) )
      {
         zPCHAR pchMatchFound;

         GetAddrForAttribute( &pchMatchFound,
                              vDTE, "TE_FieldDataRel", "MatchFound" );

         if ( pchMatchFound[ 0 ] == 'N' )
         {
            zPCHAR pchKeyType;

            // Add a blank line to seperate columns from different tables.
            if ( bFirstAlterOfTable )
            {
               zCHAR szEntityName[ zZEIDON_NAME_LTH + 1 ];

               bFirstAlterOfTable = FALSE;

            // KJS 10/16/14 - When I have selected "Keep Physical Characteristics..." for the datasource, and the
            // rebuild tables/rels and then "Build Sync DDL", I get to this point and have TE_TablRecs where there
            // is no ER_ENTITY. I am not sure why I don't seem to get that when "Keep ..." is not set.
            if ( CheckExistenceOfEntity( vDTE, "ER_Entity" ) == zCURSOR_SET )
            {
               GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vDTE, "ER_Entity", "Name" );

               if ( fnWriteLine( vDTE, f, "" ) < 0 )
                  goto EndOfFunction;

               sprintf_s( szLine, zsizeof( szLine ), "%s Entity %s %s",
                          COMMENT_START, szEntityName, COMMENT_END );
               if ( fnWriteLine( vDTE, f, szLine ) < 0 )
                  goto EndOfFunction;
            }
            }

            GetStringFromAttribute( szColumnName, zsizeof( szColumnName ), vDTE, "TE_FieldDataRel", "Name" );

            sprintf_s( szLine, zsizeof( szLine ), "ALTER TABLE %s " ADD_COLUMN_STMT " ", szTableName );
            fnBuildColumn( vDTE, f, szLine );
            strcat_s( szLine, zsizeof( szLine ), LINE_TERMINATOR );
            if ( fnWriteLine( vDTE, f, szLine ) < 0 )
               goto EndOfFunction;

            // If the attribute is not a rel field try the next one.
            GetAddrForAttribute( &pchKeyType, vDTE, "TE_FieldDataRel",
                                 "DataOrRelfieldOrSet" );
            if ( pchKeyType[ 0 ] != 'R' )
               continue;

            if ( fnBuildFK_Index( vDTE, f ) == -1 )
               goto EndOfFunction;
         }

      }  // For each TE_FieldDataRel

      #if COMMIT_EVERY_TABLE
         // Commit the table if we altered it.
         if ( bFirstAlterOfTable == FALSE && fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
            return( -1 );
      #endif

   }  // For each TE_TablRec

   // Drop tables.
   bTableDropped = FALSE;
   for ( nRC = SetCursorFirstEntity( vDB, "TE_TablRec", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vDB, "TE_TablRec", 0 ) )
   {
      GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDB, "TE_TablRec", "Name" );
      RemoveBrackets( szTableName );

      if ( CompareAttributeToString( vDB, "TE_TablRec", "MatchFound", "Y" ) != 0 )
      {
         sprintf_s( szLine, zsizeof( szLine ), "DROP TABLE %s %s", szTableName, LINE_TERMINATOR );

         if ( fnWriteLine( vDTE, f, szLine ) < 0 )
            goto EndOfFunction;

         bTableDropped = TRUE;
      }

   }  // For each TE_TablRec

   #if COMMIT_EVERY_TABLE
      if ( bTableDropped && fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
         return( -1 );
   #endif

   // Drop/alter columns from tables.
   for ( nRC = SetCursorFirstEntity( vDB, "TE_TablRec", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vDB, "TE_TablRec", 0 ) )
   {
      zBOOL bFirstAlterForTable;

      GetStringFromAttribute( szTableName, zsizeof( szTableName ), vDB, "TE_TablRec", "Name" );
      RemoveBrackets( szTableName );

      if ( CompareAttributeToString( vDB, "TE_TablRec", "MatchFound", "Y" ) != 0 )
      {
         // Table deleted, go on to next one.
         continue;
      }

      // Set the cursor in the TE to match the one in the DB.
      SetCursorFirstEntityByAttr( vDTE, "TE_TablRec", "Name",
                                  vDB,  "TE_TablRec", "Name", 0 );

      GetStringFromAttribute( szOwner, zsizeof( szOwner ), vDTE, "TE_TablRec", "SQL_TableOwner" );
      if ( szOwner[ 0 ] == 0 && pchDefaultOwner )
         strcpy_s( szOwner, zsizeof( szOwner ), pchDefaultOwner );

      if ( szOwner[ 0 ] )
         strcat_s( szOwner, zsizeof( szOwner ), "." );

      bFirstAlterForTable = TRUE;
      for ( nRC = SetCursorFirstEntity( vDB, "TE_FieldDataRel", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vDB, "TE_FieldDataRel", 0 ) )
      {
         zSHORT nIndexDroppedCount;

         // If a match was found for the column, we don't need to do anything.
         if ( CompareAttributeToString( vDB, "TE_FieldDataRel",
                                        "MatchFound", "Y" ) == 0 )
         {
            continue;
         }

         // Print out a comment if this is the first ALTER for the current
         // table.
         if ( bFirstAlterForTable )
         {
            zCHAR szEntityName[ zZEIDON_NAME_LTH + 1 ];

            bFirstAlterForTable = FALSE;
            GetStringFromAttribute( szEntityName, zsizeof( szEntityName ), vDTE, "ER_Entity", "Name" );

            if ( fnWriteLine( vDTE, f, "" ) < 0 )
               goto EndOfFunction;

            sprintf_s( szLine, zsizeof( szLine ), "%s Entity %s %s",
                       COMMENT_START, szEntityName, COMMENT_END );
            if ( fnWriteLine( vDTE, f, szLine ) < 0 )
               goto EndOfFunction;
         }

         GetStringFromAttribute( szColumnName, zsizeof( szColumnName ), vDB, "TE_FieldDataRel", "Name" );

         // Check to see if there is an index on the column.  If there is,
         // then we need to drop it.
         nIndexDroppedCount = 0;
         for ( nRC = SetCursorFirstEntityByString( vDB, "TE_FieldDataRelKey",
                                                   "Name", szColumnName,
                                                   "TE_TablRec" );
               nRC >= zCURSOR_SET;
               nRC = SetCursorNextEntityByString( vDB, "TE_FieldDataRelKey",
                                                  "Name", szColumnName,
                                                  "TE_TablRec" ) )
         {
            zCHAR szIndex[ MAX_TABLENAME_LTH + 1 ];

            GetStringFromAttribute( szIndex, zsizeof( szIndex ), vDB, "TE_TablRecKey", "IndexName" );
            fnBuildDropIndex( vDB, szIndex, szOwner, szTableName, f );
            nIndexDroppedCount++;
         }

         // Check to see if the column needs to be altered or dropped.
         if ( CompareAttributeToString( vDB, "TE_FieldDataRel",
                                        "MatchFound", "N" ) == 0 )
         {
            // Drop the column.
            sprintf_s( szLine, zsizeof( szLine ), "ALTER TABLE %s%s " DROP_COLUMN_STMT " %s %s",
                       szOwner, szTableName, szColumnName, LINE_TERMINATOR );

            if ( fnWriteLine( vDTE, f, szLine ) < 0 )
               goto EndOfFunction;
         }
         else
         if ( CompareAttributeToString( vDB, "TE_FieldDataRel",
                                        "MatchFound", "D" ) == 0 )
         {
            zPCHAR pchKeyType;

            // Alter the column to match the datatype in the TE.
            sprintf_s( szLine, zsizeof( szLine ), "ALTER TABLE %s%-*s ALTER COLUMN ",
                       szOwner, (int) MAX_TABLENAME_LTH, szTableName );

            fnBuildColumn( vDB, f, szLine );
            strcat_s( szLine, zsizeof( szLine ), LINE_TERMINATOR );

            if ( fnWriteLine( vDTE, f, szLine ) < 0 )
               goto EndOfFunction;

            // Check to see if we need to re-create any indexes.
            GetAddrForAttribute( &pchKeyType, vDTE, "TE_FieldDataRel",
                                 "DataOrRelfieldOrSet" );
            if ( pchKeyType[ 0 ] == 'R' )
            {
               if ( fnBuildFK_Index( vDTE, f ) == -1 )
                 goto EndOfFunction;

               // We re-created one of the indexes dropped earlier so decrement
               // count so we'll know if we recreated all the indexes.
               nIndexDroppedCount--;
            }

            // If no more indexes need to be recreated, go on to the next col.
            if ( nIndexDroppedCount == 0 )
               continue;

            // Check to see if the column we altered is contained in the list of
            // identifiers for the table.  If it is we need to recreate
            // the indexes that were dropped above.
            for ( nRC = SetCursorFirstEntityByString( vDTE, "TE_FieldDataRelKey",
                                                      "Name", szColumnName,
                                                      "TE_TablRec" );

                  nRC >= zCURSOR_SET;
                  nRC = SetCursorNextEntityByString( vDTE, "TE_FieldDataRelKey",
                                                     "Name", szColumnName,
                                                      "TE_TablRec" ) )
            {
               if ( fnBuildIndexFromTablRecKey( vDTE, FALSE, f ) == -1 )
                  goto EndOfFunction;

               // We re-created one of the indexes dropped earlier so decrement
               // count so we'll know if we recreated all the indexes.
               nIndexDroppedCount--;
            }

            if ( nIndexDroppedCount )
            {
               zCHAR szMsg[ 1000 ];

               // An index has been dropped for this column because it has been
               // modified but it is not a FK so we don't normally create an
               // index on it.  We'll display a warning and try to create an
               // index for the column.
               sprintf_s( szMsg, zsizeof( szMsg ), "WARNING: The data type for the column %s.%s "
                          "has been changed and therefore had an index deleted.  "
                          "The column is NOT a key and therefore the index was "
                          "added by the DBA.  An attempt has been made to "
                          "recreate the index in the DDL.  Look for 'WARNING' "
                          "in the DDL file",
                          szTableName, szColumnName );
               SysMessageBox( vDTE, "DDL Generationg Warning", szMsg, 0 );

               sprintf_s( szMsg, zsizeof( szMsg ), "%s WARNING--Following index may not have the "
                          " same the columns as the original index: %s",
                          COMMENT_START, COMMENT_END );
               if ( fnWriteLine( vDTE, f, szMsg ) < 0 )
                  goto EndOfFunction;

               if ( fnBuildFK_Index( vDTE, f ) == -1 )
                 goto EndOfFunction;
            }
         }

      }  // For each TE_FieldDataRel

      #if COMMIT_EVERY_TABLE
         // Commit the table if we altered it.
         if ( bFirstAlterForTable == FALSE && fnWriteLine( vDTE, f, COMMIT_STR ) < 0 )
            return( -1 );
      #endif

   }  // For each TE_TablRec

   // If we get here, then everything's ok.
   nReturn = 0;

EndOfFunction:
   if ( f >= 0 )
      SysCloseFile( vSubtask, f, 0 );

   // Drop the view copies.
   DropView( vDTE );
   DropView( vEMD );

   return( nReturn );

} // BuildSyncDDL

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
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "X" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "TimeStampEx" );

#if defined( SQLSERVER ) && !defined( QUINSOFT )
   /*
   ** The ODBC-driver for SqlServer doesn't support SQL_DATE and SQL_TIME
   */
   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "T" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "Date" );

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "T" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "Time" );
#else
   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "D" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "Date" );

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "I" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "Time" );
#endif

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "F" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "FixedChar" );

#if defined( ACCESS )

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "B" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "Blob (Memo)" );     // Blob name.

   //
   // Following are DB-specific types.
   //

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "V" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "Memo" );

#elif defined( DB2 )

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "B" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "Blob" );

   //
   // Following are DB-specific types.
   //

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "V" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "CLOB" );

#elif defined( SQLBASE ) || defined( ODBC )

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "B" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "Blob (VarChar)" );     // Blob name.

   //
   // Following are DB-specific types.
   //

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "V" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "VarChar" );

#elif defined( MYSQL )

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "B" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "Blob (longblob)" );       // Blob name.

   //
   // Following are DB-specific types.
   //

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "V" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "Text (longtext)" );

   // Create a data type that will be autoincrement in MySql
   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "A" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "SERIAL (autoincrement)" );

#elif defined( POSTGRESQL ) || defined( SQLSERVER )

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "B" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName",
                           "Blob (bytea)" );       // Blob name.

   //
   // Following are DB-specific types.
   //

   CreateEntity( vType, "DB_DataTypes", zPOS_LAST );
   SetAttributeFromString( vType, "DB_DataTypes", "InternalName", "V" );
   SetAttributeFromString( vType, "DB_DataTypes", "ExternalName", "Text" );

#endif

   return( 0 );

} // LoadDataTypes

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
   zBOOL  bTimestampAsString = FALSE;

   if ( bSetDefault )
   {
      zPCHAR pchDomainName;
      zVIEW  vTZTEDBLO;
      zVIEW  vTZDBHODO = 0;
      zVIEW  vDBH_Data = 0;
      zCHAR  szDBH_DataObjectName[ zZEIDON_NAME_LTH + 1 ];

      // If it exists get the object that defines the dbhandler type.
      GetViewByName( &vTZTEDBLO, "TZTEDBLO", vDTE, zLEVEL_TASK );  // vDTE added dks 2009.11.11
      if ( vTZTEDBLO )
         SetCursorFirstEntityByAttr( vTZTEDBLO, "TE_DBMS_Source", "DBMS",
                                     vDTE,      "TE_DBMS_Source", "DBMS", 0 );

      // Try to get the OI that contains DBH-specific data.
      SetOI_FromBlob( &vDBH_Data, szDBH_DataObjectName, vDTE, vDTE,
                      "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

      #if defined( ACCESS ) || defined( ODBC )

         // Try to get the ODBC definition.
         SetOI_FromBlob( &vTZDBHODO, 0, vDTE, vTZTEDBLO,
                         "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

         // Check to see if there is DBH data set in the TE.
         if ( vDBH_Data )
         {
            bTimestampAsString =
                         ( CompareAttributeToString( vDBH_Data, "ODBC",
                                                     "TimestampAsString",
                                                     "Y" ) == 0 );
         }
         else
         // Check to see if there is DBH data set in the DB List object.
         if ( vTZDBHODO )
         {
               bTimestampAsString =
                         ( CompareAttributeToString( vTZDBHODO, "ODBC",
                                                     "TimestampAsString",
                                                     "Y" ) == 0 );
         }

      #endif

      // Set the default data type from the ER attribute domain.  If the
      // domain name is "Date" or "Time" then use SqlBase date/time types.
      GetAddrForAttribute( &pchDomainName, vDTE, "Domain", "Name" );

#if defined( SQLSERVER ) && !defined( QUINSOFT )
      if ( zstrcmpi( pchDomainName, "Date" ) == 0 ||
           zstrcmpi( pchDomainName, "Time" ) == 0 )
      {
         SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "T" );
      }
      else
      if ( zstrcmpi( pchDomainName, "TimeStampEx" ) == 0 )
         SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "X" );
      else
         // Domain is not Date or Time, so just set the default data type the
         // same as the domain's data type.
         SetAttributeFromAttribute( vDTE, "TE_FieldDataRel", "DataType",
                                    vDTE, "Domain", "DataType" );
#else
      if ( zstrcmpi( pchDomainName, "Date" ) == 0 )
         SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "D" );
      else
      if ( zstrcmpi( pchDomainName, "Time" ) == 0 )
         SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "I" );
      else
      if ( zstrcmpi( pchDomainName, "TimeStampEx" ) == 0 )
         SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "X" );
#if defined( MYSQL )
      else
      // If domain is GeneratedKey then use "SERIAL" for default datatype.
      if ( zstrcmpi( pchDomainName, "GeneratedKey" ) == 0 )
      {
         SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "A" );
      }
#endif
      else
         // Domain is not Date or Time, so just set the default data type the
         // same as the domain's data type.
         SetAttributeFromAttribute( vDTE, "TE_FieldDataRel", "DataType",
                                    vDTE, "Domain", "DataType" );
#endif

      // Strings with a length > 254 must have a data type of VarChar.
      GetAddrForAttribute( &pchDataType, vDTE, "Domain", "DataType" );
      if ( pchDataType[ 0 ] == zTYPE_STRING )
      {
         GetIntegerFromAttribute( &lLth, vDTE, "ER_Attribute", "Lth" );
         if ( lLth == 0  )
            GetIntegerFromAttribute( &lLth, vDTE, "Domain", "MaxStringLth" );

         if ( lLth > MAX_LTH_FOR_STRING )
            SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "V" );
      }

#if !defined( QUINSOFT) && !defined( SQLSERVER ) && !defined( SQLBASE )
      if ( pchDataType[ 0 ] == zTYPE_BLOB )
         SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "V" );
#endif

   }

   // Get the data type.
   GetAddrForAttribute( &pchDataType, vDTE, "TE_FieldDataRel", "DataType" );

   // Now set the length according to the physical data type.
   switch ( pchDataType[ 0 ] )
   {

      case zTYPE_STRING:
      case 'V':
      case zTYPE_FIXEDCHAR:
         GetIntegerFromAttribute( &lLth, vDTE, "ER_Attribute", "Lth" );
         if ( lLth == 0  )
            GetIntegerFromAttribute( &lLth, vDTE, "Domain", "MaxStringLth" );

         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", lLth );
         break;

      case zTYPE_BLOB:

#if defined( DB2 )
         // DB2 needs a blob length.
         GetIntegerFromAttribute( &lLth, vDTE, "ER_Attribute", "Lth" );
         if ( lLth == 0  )
            GetIntegerFromAttribute( &lLth, vDTE, "Domain", "MaxStringLth" );

         if ( lLth == 0  )
            lLth = 65536;   // Default length for blobs.

         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", lLth );
#else
         SetAttributeFromAttribute( vDTE, "TE_FieldDataRel", "Length",
                                    vDTE, "ER_Attribute",    "Lth" );
#endif

         break;

      case zTYPE_INTEGER:
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 4 );
         break;

      case 'A':                // For SERIAL/AUTOINCREMENT
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 64 );
         break;

      case zTYPE_DECIMAL:
         GetIntegerFromAttribute( &lLth, vDTE, "ER_Attribute", "Lth" );
         if ( lLth == 0  )
         {
            GetIntegerFromAttribute( &lLth, vDTE, "Domain", "MaxStringLth" );
            if ( lLth == 0 )
               lLth = sizeof( zDECIMAL );
         }
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", lLth );
         break;

      case zTYPE_DATETIME:
      case zTYPE_TIME:
         if ( bTimestampAsString )
         {
            // This is only true when we are setting the default value of the
            // data type.  Change the datatype to be a string.
            SetAttributeFromString( vDTE, "TE_FieldDataRel", "DataType", "S" );
            SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 25 );
         }
         else
         {
            switch ( pchDataType[ 0 ] )
            {
               case zTYPE_DATETIME:
                  SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 4 );
                  break;

               case zTYPE_TIME:
                  SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 8 );
                  break;
            }
         }

         break;

      case zTYPE_DATE:
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 4 );
         break;

      case 'X':
         SetAttributeFromInteger( vDTE, "TE_FieldDataRel", "Length", 30 );
         break;

      default:
         TraceLineS( "(TE) Invalid Physical Data type = ", pchDataType );
         SysMessageBox( vDTE, "Zeidon TE", "Invalid Physical Data type.", 1 );
         return( 0 );
   }

   return( 0 );

} // SetDataType

// Make sure that name doesn't match a reserved word.
zVOID LOCALOPER
fnChangeReservedName( zPCHAR pchName, zLONG lMaxLth )
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
         strcpy_s( pchName, lMaxLth, szTemp );
         return;
      }

      // Reserved words are listed in alphabetical order.  If the compare
      // returned a value greater than 0, then pchName comes before the current
      // szReservedName, which means there cannot be a match.
      if ( j > 0 )
         return;
   }
}

//./ ADD NAME=TranslateToUnderscoreCase
/////////////////////////////////////////////////////////////////////////////
//
//   ENTRY:    TranslateToUnderscoreCase
//
//   PROTOTYPE:
//        void OPERATION
//        TranslateToUnderscoreCase( zPCHAR pchSrc,
//                                   zPCHAR pchTarget,
//                                   zSHORT targetLth )
//
//   PURPOSE:  Converts a string from Camel Casing to underscores.  E.g.:
//
//                  ThisIsCamelCase to this_is_camel_case
//                  ThisIsHTTPCase to this_is_http_case
//                  ThisIsHTTP to this_is_http
//                  ThisIsATest to this_is_a_test
//                  nocamel_case to nocamel_case
//                  noLeadingUpper to no_leading_upper
//
//   RETURNS: 0 or zCALL_ERROR
//
//////////////////////////////////////////////////////////////////////////////

//TranslateToUnderscoreCase( zPCHAR pchSrc, zPCHAR pchTarget, zSHORT targetLth )
zSHORT OPERATION
TranslateToUnderscoreCase( zPCHAR pchSrc, zPCHAR pchTarget, zCHAR  cMetaType )
{
   zVIEW  vDBH_Data = 0;
   //zCHAR  szDBH_DataObjectName[ zZEIDON_NAME_LTH + 1 ];
   //zCHAR  szCreateUnderscore[ 2 ];
   zLONG  l;
   zPCHAR targetEnd; // = pchTarget + targetLth - 1; // Point to last char in target buffer.
   zPCHAR original = pchSrc;
   zPCHAR p;
   zCHAR  sz[ 256 ];
   zSHORT nMaxLth = BUFF_SIZE - 1;      // Used to keep track of duplicate names.

   switch ( cMetaType )
   {
      case 'E':      // Meta type is Entity

         // Try getting the max length from the DBH-Specific OI.  If one is not specified use the default length.
         if ( vDBH_Data &&
              GetIntegerFromAttribute( &l, vDBH_Data, "ODBC", "MaxTableNameLength" ) != -1 )
         {
            nMaxLth = (zSHORT) l;
         }
         else
            nMaxLth = MAX_TABLENAME_LTH;

         break;

      case 'A':      // Meta type is Attribute

         // Try getting the max length from the DBH-Specific OI.  If one is
         // not specified use the default length.
         if ( vDBH_Data &&
              GetIntegerFromAttribute( &l, vDBH_Data, "ODBC", "MaxColumnNameLength" ) != -1 )
         {
            nMaxLth = (zSHORT) l;
         }
         else
            nMaxLth = MAX_COLUMNNAME_LTH;

         break;

     default:
        strcpy_s( pchTarget, nMaxLth, pchSrc );
       return 0;
   }

   if ( nMaxLth >= BUFF_SIZE )
      nMaxLth = BUFF_SIZE - 1;

  targetEnd = pchTarget + nMaxLth - 1;

  // Defensive programming...
  *targetEnd = 0;

  if ( (zSHORT) zstrlen( pchSrc ) >= nMaxLth )
     return zCALL_ERROR;

  strcpy_s( sz, zsizeof( sz ), pchSrc );

  //p = pchTarget;
  p = sz;

  // Copy first char to target.
  *p++ = *pchSrc++;
  while ( *pchSrc != 0 )
  {
      // Do we have enough space to add two more chars?
    if ( p + 2 > targetEnd )
     return -16;

    if ( *pchSrc >= 'A' && *pchSrc <= 'Z' )
   {
     // We have a capital letter.  Is previous letter upper?
     if ( *(p-1) < 'A' || *(p-1) > 'Z' )
       // No, so copy _.
       *p++ = '_';
     else
       // Previous letter is also upper.  Insert _ if next char is lower.
       if ( ( *(pchSrc+1) < 'A' || *(pchSrc+1) > 'Z' ) && *(pchSrc+1) != 0 )
         *p++ = '_';
   }
      *p++ = *pchSrc++;
    }
//
  *p++ = 0;

  // Now convert to all lower.
  SysTranslateString( p, 'L' );
  strcpy_s( pchTarget, nMaxLth, sz );

  return 0;
}

/*
   Generates a valid SQLBase table or column name using an entity/attribute
   name as it's base.

   ARGUMENTS:
      vDTE        - View to TE.
      pchName     - Pointer to Name buffer containing original name.  The
                    name might be changed by this routine and then copied
                    back into the buffer.
      cMetaType   - Indicates what type of name we need to generate.

                        'E' - Entity name. For SqlBase this is a table.
                        'A' - Attribute name.  For SqlBase this is a column.
                        'S' - Set name. Not used in relation databases.
                        'X' - Duplicate name.  The previous name generated is
                              a duplicate name.  Generate a new one.

   Note: vDTE not used here.

*/
zSHORT OPERATION
GenerateName( zVIEW  vDTE,
              zPCHAR pchName,
              zLONG  lMaxNameLth,
              zCHAR  cMetaType )
{
   static zSHORT nNameCount;   // Used to keep track of duplicate names.
   static zLONG  lMaxLth;      // Used to keep track of duplicate names.

   zVIEW  vDBH_Data = 0;
   zCHAR  szDBH_DataObjectName[ zZEIDON_NAME_LTH + 1 ];
   zCHAR  szCreateUnderscore[ 2 ];
   zPCHAR pch1;
   zPCHAR pch2;
   zLONG  l;

   // Try to get the OI that contains DBH-specific data.
   SetOI_FromBlob( &vDBH_Data, szDBH_DataObjectName, vDTE, vDTE,
                   "TE_DBMS_Source", "DBH_Data", zNOI_OKAY );

   // Eliminate invalid chars.
   for ( pch1 = pch2 = pchName; *pch2; pch2++ )
   {
      // Even though SQLBase allows '@', '#', and '$' we don't generate them.
      if ( zisalnum( *pch2 ) || *pch2 == '_' )
         *pch1++ = *pch2;  // Copy valid char.
   }

   // Null-terminate string.
   pch1[ 0 ] = 0;

   // KJS 08/07/14 - DG wants to be able to create names Like EntityName to entity_name. This is the ini setting.
   GetStringFromAttribute( szCreateUnderscore, zsizeof( szCreateUnderscore ), vDTE, "TE_DBMS_Source", "TranslateNamesToLowerUnderscore");

   switch ( cMetaType )
   {
      case 'E':      // Meta type is Entity
         nNameCount = 1;

         // Try getting the max length from the DBH-Specific OI.  If one is not specified use the default length.
         if ( vDBH_Data && GetIntegerFromAttribute( &l, vDBH_Data, "ODBC", "MaxTableNameLength" ) != -1 )
         {
            lMaxLth = l;
         }
         else
            lMaxLth = MAX_TABLENAME_LTH;

         if ( lMaxLth > lMaxNameLth )
         {
            lMaxLth = lMaxNameLth;  // cannot be longer than return buffer max length
         }

         break;

      case 'A':      // Meta type is Attribute
         nNameCount = 1;

         // Try getting the max length from the DBH-Specific OI.  If one is not specified use the default length.
         if ( vDBH_Data && GetIntegerFromAttribute( &l, vDBH_Data, "ODBC", "MaxColumnNameLength" ) != -1 )
         {
            lMaxLth = l;
         }
         else
            lMaxLth = MAX_COLUMNNAME_LTH;

         if ( lMaxLth > lMaxNameLth )
         {
            lMaxLth = lMaxNameLth;  // cannot be longer than return buffer max length
         }

         break;

      case 'X':      // pchName is a duplicate, generate a new one.
      {
         zLONG lLth;

         // When generating new names, we just tack on an incrementing number.  For example,
         // "ColName" becomes "ColName02", "ColName02" becomes "ColName03", etc.

         nNameCount++;
         lLth = zstrlen( pchName );
         if ( nNameCount > 2 )
            lLth = lLth - 2;
         else
         if ( lLth > lMaxLth - 2 )
            lLth = lMaxLth - 2;

         sprintf_s( pchName + lLth, lMaxNameLth - lLth, "%02d", nNameCount );

         // We know name is short enough and no reserved words contain numbers, so just return.
         return( 0 );
      }
   }

   if ( lMaxLth >= BUFF_SIZE )
      lMaxLth = BUFF_SIZE - 1;

   if ( lMaxLth > lMaxNameLth )
   {
      lMaxLth = lMaxNameLth;  // cannot be longer than return buffer max length
   }

   // Compress the name if it needs it.
   UfCompressName( pchName,   // Original name.
                   pchName,   // New (shorter) name.
                   lMaxLth,   // Max length of string.
                   "",        // Remove embedded spaces.
                   "",        // Ignore '_' (for now).
                   "Bc",      // Remove lower-case vowels starting from back.
                   "B_",      // Remove '_' starting from back.
                   0 );       // Stop when the name is short enough.

   if ( szCreateUnderscore[ 0 ] == 'Y' )
      // KJS 08/07/14 - Change string to all lower-case if we are creating table/column names with underscore.
      SysTranslateString( pchName, 'L' );
   else
      // Change string to all upper-case.
      SysTranslateString( pchName, 'U' );

   // Make sure generated name doesn't match a reserved word.
   fnChangeReservedName( pchName, lMaxNameLth );

   return( 0 );

} // GenerateName

//====================================================================
//
//  DB-SPECIFIC OPERATIONS.
//
//====================================================================

#if defined ( DB2 )

zCHAR g_szSqlDLLName[ zMAX_FILESPEC_LTH + 1 ] = "";

// This is the size of the structure used to retrieve blobs from DB2.  We set
// it to a string values instead of a integer because we write it to a text file.
#define BLOB_VAR_LTH    "10000"

void LOCALOPER
fnCreateStartFunctions( zVIEW lpTaskView, zLONG f, LPVIEWOD lpViewOD )
{
   zCHAR szLine[ 500 ];

   //
   // Global variables.
   //

   SysWriteLine( lpTaskView, f, "EXEC SQL BEGIN DECLARE SECTION;" );
   SysWriteLine( lpTaskView, f, "   extern sql type is blob( " BLOB_VAR_LTH " ) g_BlobData;" );
   SysWriteLine( lpTaskView, f, "   extern sql type is clob( " BLOB_VAR_LTH " ) g_StringData;" );
   SysWriteLine( lpTaskView, f, "   extern long g_lColumnLth;" );
   SysWriteLine( lpTaskView, f, "EXEC SQL END DECLARE SECTION;" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "extern zPCHAR g_pvBuffer;" );
   SysWriteLine( lpTaskView, f, "extern long   g_lBufferLth;" );
   SysWriteLine( lpTaskView, f, " " );

   //
   // OpenConnection
   //

   SysWriteLine( lpTaskView, f, "zSHORT OPERATION" );
   sprintf_s( szLine, zsizeof( szLine ), "%s_OpenConnection( zPCHAR pchUser, zPCHAR pchPassword, "
                     "zSHORT nTraceLevel )", lpViewOD->szName );
   SysWriteLine( lpTaskView, f, szLine );

   SysWriteLine( lpTaskView, f, "{" );
   SysWriteLine( lpTaskView, f, "   EXEC SQL BEGIN DECLARE SECTION;" );
   SysWriteLine( lpTaskView, f, "      char szLocalUser[ 100 ];" );
   SysWriteLine( lpTaskView, f, "      char szLocalPassword[ 100 ];" );
   SysWriteLine( lpTaskView, f, "   EXEC SQL END DECLARE SECTION;" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   strcpy_s( szLocalUser, zsizeof( szLocalUser ), pchUser );" );
   SysWriteLine( lpTaskView, f, "   strcpy_s( szLocalPassword, zsizeof( szLocalPassword ), pchPassword );" );

   sprintf_s( szLine, zsizeof( szLine ), "  EXEC SQL CONNECT TO %s USER :szLocalUser "
                     "USING :szLocalPassword;", lpViewOD->szDfltDBName );
   SysWriteLine( lpTaskView, f, szLine );

   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( nTraceLevel > 0 )" );
   SysWriteLine( lpTaskView, f, "   {" );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"Executed following static SQL:\", \"\" );" );
   sprintf_s( szLine, zsizeof( szLine ), "     TraceLineS( \"   EXEC SQL CONNECT TO %s USER :szLocalUser "
                     "USING :szLocalPassword;\", \"\" );", lpViewOD->szDfltDBName );
   SysWriteLine( lpTaskView, f, szLine );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"User = \", pchUser );" );
   SysWriteLine( lpTaskView, f, "      TraceLineI( \"RC   = \", (zLONG) SQLCODE );" );
   SysWriteLine( lpTaskView, f, "   }" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( SQLCODE != 0 )" );
   SysWriteLine( lpTaskView, f, "      return( zCALL_ERROR );" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   return( 0 );" );
   SysWriteLine( lpTaskView, f, "}" );
   SysWriteLine( lpTaskView, f, " " );

   //
   // CloseConnection
   //

   SysWriteLine( lpTaskView, f, "zSHORT OPERATION" );
   sprintf_s( szLine, zsizeof( szLine ), "%s_CloseConnection( zSHORT nTraceLevel )",
              lpViewOD->szName );
   SysWriteLine( lpTaskView, f, szLine );

   SysWriteLine( lpTaskView, f, "{" );
   SysWriteLine( lpTaskView, f, "   EXEC SQL CONNECT RESET;" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( nTraceLevel > 0 )" );
   SysWriteLine( lpTaskView, f, "   {" );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"Executed following static SQL:\", \"\" );" );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"   EXEC SQL CONNECT RESET;\", \"\" );" );
   SysWriteLine( lpTaskView, f, "      TraceLineI( \"RC   = \", (zLONG) SQLCODE );" );
   SysWriteLine( lpTaskView, f, "   }" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( SQLCODE != 0 )" );
   SysWriteLine( lpTaskView, f, "      return( zCALL_ERROR );" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   return( 0 );" );
   SysWriteLine( lpTaskView, f, "}" );
   SysWriteLine( lpTaskView, f, " " );

   //
   // Commit
   //

   SysWriteLine( lpTaskView, f, "zSHORT OPERATION" );
   sprintf_s( szLine, zsizeof( szLine ), "%s_Commit( zSHORT nTraceLevel )", lpViewOD->szName );
   SysWriteLine( lpTaskView, f, szLine );

   SysWriteLine( lpTaskView, f, "{" );
   SysWriteLine( lpTaskView, f, "   EXEC SQL COMMIT;" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( nTraceLevel > 0 )" );
   SysWriteLine( lpTaskView, f, "   {" );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"Executed following static SQL:\", \"\" );" );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"   EXEC SQL COMMIT;\", \"\" );" );
   SysWriteLine( lpTaskView, f, "      TraceLineI( \"RC   = \", (zLONG) SQLCODE );" );
   SysWriteLine( lpTaskView, f, "   }" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( SQLCODE != 0 )" );
   SysWriteLine( lpTaskView, f, "      return( zCALL_ERROR );" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   return( 0 );" );
   SysWriteLine( lpTaskView, f, "}" );
   SysWriteLine( lpTaskView, f, " " );

   //
   // Rollback
   //

   SysWriteLine( lpTaskView, f, "zSHORT OPERATION" );
   sprintf_s( szLine, zsizeof( szLine ), "%s_Rollback( zSHORT nTraceLevel )", lpViewOD->szName );
   SysWriteLine( lpTaskView, f, szLine );

   SysWriteLine( lpTaskView, f, "{" );
   SysWriteLine( lpTaskView, f, "   EXEC SQL ROLLBACK;" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( nTraceLevel > 0 )" );
   SysWriteLine( lpTaskView, f, "   {" );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"Executed following static SQL:\", \"\" );" );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"   EXEC SQL ROLLBACK;\", \"\" );" );
   SysWriteLine( lpTaskView, f, "      TraceLineI( \"RC   = \", (zLONG) SQLCODE );" );
   SysWriteLine( lpTaskView, f, "   }" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( SQLCODE != 0 )" );
   SysWriteLine( lpTaskView, f, "      return( zCALL_ERROR );" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   return( 0 );" );
   SysWriteLine( lpTaskView, f, "}" );
   SysWriteLine( lpTaskView, f, " " );
}

#define GEN_QUAL     0x01
#define GEN_NULL     0x02
#define GEN_UNIQUE   0x04

void LOCALOPER
fnGenerateVarName( zPCHAR       pchTarget,
                   LPVIEWENTITY lpViewEntity,
                   LPVIEWENTITY lpBoundViewEntity,
                   LPVIEWATTRIB lpViewAttrib,
                   zSHORT       nGen )
{
   sprintf_s( pchTarget, MAX_NAME_LTH, "%s%d_%ld_%ld", (nGen & GEN_UNIQUE) ? "u" : "v",
              lpViewEntity->nHierNbr,
              lpViewAttrib->lERAttTok, lpBoundViewEntity->lEREntTok );

   if ( nGen & GEN_QUAL )
      strcat_s( pchTarget, MAX_NAME_LTH, "_Qual" );

   if ( nGen & GEN_NULL )
      strcat_s( pchTarget, MAX_NAME_LTH, "_Null" );
}

// Following used by DB2 callback operation.
typedef struct CallbackStruct CallbackRecord;
typedef CallbackRecord *LPCALLBACK;
struct CallbackStruct
{
   zBOOL        bGenerateIntoClause;
   zBOOL        bInsert;
   zBOOL        bGenUnique;
   LPVIEWENTITY lpViewEntity;
};

zSHORT OPERATION
fnDBH_Callback( zULONG      nCommand,
                zVIEW       lpView,
                LPBOUNDLIST lpBoundList,
                LPDATAFIELD lpDataField,
                zPVOID      pInfo,
                zPCHAR      pchTarget )
{
   zSHORT       nGen = 0;
   LPVIEWENTITY lpViewEntity;
   LPVIEWATTRIB lpViewAttrib;
   LPCALLBACK   lpCallback = (LPCALLBACK) lpBoundList->pvPtr;

   if ( lpDataField )
   {
      lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );
      lpViewEntity = zGETPTR( lpViewAttrib->hViewEntity );
   }

   switch ( nCommand )
   {
      // ==========================================================
      case zSQLCALLBACK_INITSELECT:
         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_GETNULLSTRING:
         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_CHECKNULL:
         // We pretend that no attributes are null.
         return( -1 );

      // ==========================================================
      case zSQLCALLBACK_CONVERTSTRING:
         return( FALSE );

      // ==========================================================
      case zSQLCALLBACK_GETATTRVALUE:
         SqlAddBoundAttr( lpBoundList, lpDataField, lpView, (zPVOID) TRUE, 0 );
         strcpy_s( pchTarget, MAX_NAME_LTH, ":" );

         if ( lpCallback->bInsert == FALSE )
            nGen |= GEN_QUAL;

         if ( lpCallback->bGenUnique )
            nGen |= GEN_UNIQUE;

         fnGenerateVarName( pchTarget + 1, lpCallback->lpViewEntity,
                            lpViewEntity, lpViewAttrib, nGen );
         return( TRUE );

      // ==========================================================
      case zSQLCALLBACK_GETCOLUMNNAME:
      {
         zCHAR        szTemp[ 500 ];
         LPVIEWATTRIB lpViewAttrib;

         // If pInfo is 0 then we are getting the column name for a
         // SELECT statement.  We can use the default processing for non
         // SELECT statements.
         if ( pInfo != 0 )
            return( FALSE );

         lpViewAttrib = zGETPTR( lpDataField->hViewAttrib );

         // For the 'COUNT' command we have to insert 'DISTINCT'.
         if ( lpViewAttrib->cDB_Oper == 'C' )
            strcat_s( pchTarget, MAX_NAME_LTH, " DISTINCT " );

         // We'll return FALSE even if we've done something here because we
         // want the dbhandler to tack on the column name.
         if ( lpViewAttrib->cType != zTYPE_DECIMAL )
            return( FALSE );

         // For decimal columns we will convert the number to a string.
         strcat_s( pchTarget, MAX_NAME_LTH, lpDataField->szFldName );
         sprintf_s( szTemp, zsizeof( szTemp ), "CAST( %s AS CHAR( 40 ) )", pchTarget );
         strcpy_s( pchTarget, MAX_NAME_LTH, szTemp );
         return( TRUE );
      }

      // ==========================================================
      case zSQLCALLBACK_USEINTO:
         return( lpCallback->bGenerateIntoClause );

      // ==========================================================
      case zSQLCALLBACK_GETINTONAME:
         // We'll add the datafield to the bound list so we know what columns
         // have variables mapped to them.
         SqlAddBoundAttr( lpBoundList, lpDataField, lpView, 0, 0 );

         if ( lpCallback->bGenUnique )
            nGen |= GEN_UNIQUE;

         strcpy_s( pchTarget, MAX_NAME_LTH, ":" );
         fnGenerateVarName( pchTarget + 1, lpCallback->lpViewEntity, lpViewEntity, lpViewAttrib, nGen );

         if ( lpViewAttrib->bRequired == FALSE )
         {
            zCHAR szNullIndicator[ 100 ];

            fnGenerateVarName( szNullIndicator, lpCallback->lpViewEntity,
                               lpViewEntity, lpViewAttrib,
                               (zSHORT) (nGen | GEN_NULL) );

            sprintf_s( pchTarget + zstrlen( pchTarget ), MAX_NAME_LTH - zstrlen( pchTarget ),
                       " INDICATOR :%s", szNullIndicator );
         }

         return( TRUE );

   } // switch ( nCommand )...

   // If we get here then we didn't handle the request so return FALSE.
   return( FALSE );

} // fnDBH_Callback

void LOCALOPER
fnWriteSql( zVIEW lpTaskView, zPCHAR pchSQL, zPVOID pInfo )
{
   int    nIndent;
   zCHAR  szLine[ 500 ];
   zPCHAR pch;

   nIndent = g_nIndent;

   while ( zstrlen( pchSQL ) > 80 )
   {
      pch = pchSQL + 80;
      while ( pch > pchSQL && *pch != ' ' )
         pch--;

      // If pch == pchSQL then something's screwy so just write and exit.
      if ( pch == pchSQL )
      {
         SysWriteLine( lpTaskView, (zLONG) pInfo, pchSQL );
         return;
      }

      // Change ' ' to null-terminator.
      pch[ 0 ] = 0;

      sprintf_s( szLine, zsizeof( szLine ), "%*s%s", nIndent, " ", pchSQL );
      SysWriteLine( lpTaskView, (zLONG) pInfo, szLine );
      if ( nIndent == g_nIndent )
         nIndent += 7;

      pch[ 0 ] = ' ';

      pchSQL = pch + 1;
   }

   sprintf_s( szLine, zsizeof( szLine ), "%*s%s", nIndent, " ", pchSQL );
   SysWriteLine( lpTaskView, (zLONG) pInfo, szLine );
}

void LOCALOPER
fnWriteSql2( zVIEW lpTaskView, zPCHAR pchSQL, zPVOID pInfo )
{
   int    nIndent;
   zCHAR  szLine[ 500 ];
   zPCHAR pch;
   zPCHAR pchSemiColon = zstrchr( pchSQL, ';' );

   nIndent = g_nIndent;

   while ( zstrlen( pchSQL ) > 80 )
   {
      pch = pchSQL + 80;
      while ( pch > pchSQL && *pch != ' ' )
         pch--;

      // If pch == pchSQL then something's screwy so just write and exit.
      if ( pch == pchSQL )
      {
         SysWriteLine( lpTaskView, (zLONG) pInfo, pchSQL );
         return;
      }

      // Change ' ' to null-terminator.
      pch[ 0 ] = 0;

      sprintf_s( szLine, zsizeof( szLine ), "%*s\"%s \"", nIndent, " ", pchSQL );
      SysWriteLine( lpTaskView, (zLONG) pInfo, szLine );
      if ( nIndent == g_nIndent )
         nIndent += 7;

      pch[ 0 ] = ' ';

      pchSQL = pch + 1;
   }

   if ( pchSemiColon && pchSemiColon[ 1 ] == 0 )
   {
      pchSemiColon[ 0 ] = 0;
      sprintf_s( szLine, zsizeof( szLine ), "%*s\"%s\";", nIndent, " ", pchSQL );
   }
   else
      sprintf_s( szLine, zsizeof( szLine ), "%*s\"%s\"", nIndent, " ", pchSQL );

   SysWriteLine( lpTaskView, (zLONG) pInfo, szLine );
}

// We need to load blobs in chunks because we don't know the length
// until run time.  So we'll generate the following:
//
// --> if ( _null_indicator_ > 0 )
// --> {
// -->    long lIndex = 0;
// -->
// -->    EXEC SQL VALUES ( LENGTH( :_locator_ ) ) INTO g_lColumnLth;
// -->    SDB2_AllocBuffer( &g_pvBuffer, &g_lBufferLth, g_lColumnLth );
// -->    while ( lLth < g_lColumnLth )
// -->    {
// -->       EXEC SQL VALUES ( :_locator_ ) INTO g_BlobData;
// -->       zmemcpy( &g_pvBuffer[ lIndex ], &g_BlobData.data, g_BlobData.length );
// -->       lIndex += 10000;
// -->    }
// --> }
zSHORT LOCALOPER
fnGenerateLargeAttribute( zVIEW        lpTaskView,
                          zLONG        f,
                          LPVIEWENTITY lpViewEntity,
                          LPVIEWATTRIB lpViewAttrib,
                          zSHORT       nGen,
                          zPCHAR       pchLine )
{
   zCHAR  szVar[ 100 ];
   zBOOL  bIsBlob = ( lpViewAttrib->cType == zTYPE_BLOB );
   zPCHAR pchType;

   if ( bIsBlob )
      pchType = "Blob";
   else
      pchType = "String";

   // Set szVar to name of null indicator.
   fnGenerateVarName( szVar, lpViewEntity, lpViewEntity, lpViewAttrib,
                      (zSHORT) (nGen | GEN_NULL) );

   // Ignore NULL blobs.
   // --> if ( _null_indicator_ > 0 )
   // --> {
   // -->    long lIndex = 0;
   sprintf_s( pchLine, 500, "%*sif ( %s >= 0 )", g_nIndent, " ", szVar );
   SysWriteLine( lpTaskView, f, pchLine );
   sprintf_s( pchLine, 500, "%*s{", g_nIndent, " " );
   SysWriteLine( lpTaskView, f, pchLine );
   g_nIndent += 3;
   sprintf_s( pchLine, 500, "%*slong lIndex = 0;", g_nIndent, " " );
   SysWriteLine( lpTaskView, f, pchLine );
   SysWriteLine( lpTaskView, f, " " );

   // Set szVar to name of locator.
   fnGenerateVarName( szVar, lpViewEntity, lpViewEntity, lpViewAttrib,
                      (zSHORT) nGen );

   // Get the length of the blob.
   // -->   EXEC SQL VALUES ( LENGTH( :_locator_ ) ) INTO g_lColumnLth;
   sprintf_s( pchLine, 500, "%*sEXEC SQL VALUES ( LENGTH( :%s ) ) INTO :g_lColumnLth;",
             g_nIndent, " ", szVar );
   SysWriteLine( lpTaskView, f, pchLine );

   // Alloc the buffer.
   // -->   SDB2_AllocBuffer( &g_pvBuffer, &g_lBufferLth, g_lColumnLth );
   sprintf_s( pchLine, 500, "%*sSDB2_AllocBuffer( &g_pvBuffer, "
                     "&g_lBufferLth, g_lColumnLth );",
             g_nIndent, " " );
   SysWriteLine( lpTaskView, f, pchLine );

   // Start a while loop to read the blob in pieces.
   // -->    while ( lLth < g_lColumnLth )
   // -->    {
   sprintf_s( pchLine, 500, "%*swhile ( lIndex < g_lColumnLth )",
              g_nIndent, " " );
   SysWriteLine( lpTaskView, f, pchLine );
   sprintf_s( pchLine, 500, "%*s{", g_nIndent, " " );
   SysWriteLine( lpTaskView, f, pchLine );
   g_nIndent += 3;

   // Retrieve a piece of the blob into buffer.
   // -->      EXEC SQL VALUES ( :_locator_ ) INTO g_Blob/StringData;
   // -->      zmemcpy( &g_pvBuffer[ lIndex ], &g_Blob/StringData.data, g_BlobData.length );
   // -->      lIndex += 10000;
   sprintf_s( pchLine, 500, "%*sEXEC SQL VALUES ( :%s ) INTO :g_%sData;",
              g_nIndent, " ", szVar, pchType );
   SysWriteLine( lpTaskView, f, pchLine );
   sprintf_s( pchLine, 500, "%*szmemcpy( &g_pvBuffer[ lIndex ], "
              "&g_%sData.data, g_%sData.length );", g_nIndent, " ",
             pchType, pchType );
   SysWriteLine( lpTaskView, f, pchLine );
   sprintf_s( pchLine, 500, "%*slIndex += g_%sData.length;",
              g_nIndent, " ", pchType );
   SysWriteLine( lpTaskView, f, pchLine );

   // Close the 'while' loop.
   // --> }
   g_nIndent -= 3;
   sprintf_s( pchLine, 500, "%*s} // while...", g_nIndent, " " );
   SysWriteLine( lpTaskView, f, pchLine );

   // Close 'if' statement.
   // --> }
   g_nIndent -= 3;
   sprintf_s( pchLine, 500, "%*s} // if...", g_nIndent, " " );
   SysWriteLine( lpTaskView, f, pchLine );

   return( 0 );
}

void LOCALOPER
fnBuildSelectFunction( zLONG        f,
                       zVIEW        lpTaskView,
                       LPVIEWOD     lpViewOD,
                       LPVIEWENTITY lpViewEntity,
                       zBOOL        bUniqueQual )
{
   zSHORT           nRC;
   zSHORT           nGen;
   zCHAR            szLine[ 500 ];
   zCHAR            szFreeLocatorsCmd[ 500 ] = "";
   int              nTempIndent;
   zPCHAR           pch;
   LPBOUNDATTR      lpBoundAttr;
   QualEntityRecord QualEntity;
   LPQUALENTITY     lpQualEntity = 0;
   QualAttribRecord QualAttrib;
   LPQUALATTRIB     lpQualAttrib = 0;
   CallbackRecord   Callback;
   LPBOUNDLIST      lpBoundList = 0;
   zCHAR            szSqlCmd[ 10000 ];

   zmemset( &Callback, 0, sizeof( Callback ) );
   Callback.lpViewEntity = lpViewEntity;

   if ( bUniqueQual )
   {
      Callback.bGenUnique = TRUE;
      lpQualEntity = &QualEntity;
      lpQualAttrib = &QualAttrib;

      // We want to build a select statement that performs qualification on
      // the key.  Create a temporary qualification structure.
      zmemset( lpQualEntity, 0, sizeof( QualEntity ) );
      zmemset( lpQualAttrib, 0, sizeof( QualAttrib ) );

      lpQualEntity->lpFirstQualAttrib    = lpQualAttrib;
      lpQualEntity->lpViewEntity         = lpViewEntity;
      lpQualEntity->bContainsIS          = TRUE;
      lpQualEntity->bUniqueQualification = TRUE;

      lpQualAttrib->lpViewEntity         = lpViewEntity;
      lpQualAttrib->lpSourceViewEntity   = lpViewEntity;
      lpQualAttrib->lpSourceView         = lpTaskView;
      lpQualAttrib->lpDataRecord         = zGETPTR( lpViewEntity->hFirstDataRecord );
      lpQualAttrib->szOper               = "IS";
   }

   //
   // =================== Function Name ========================
   //
   SysWriteLine( lpTaskView, f, "zSHORT OPERATION" );
   sprintf_s( szLine, zsizeof( szLine ), "SQL_%s_%s_Select%s( zVIEW       lpView,",
              lpViewOD->szName, lpViewEntity->szName,
              bUniqueQual ? "Unique" : "" );
   SysWriteLine( lpTaskView, f, szLine );

   pch = zstrchr( szLine, '(' ) + 2;
   nTempIndent = (int) ( pch - szLine );
   sprintf_s( szLine, zsizeof( szLine ), "%*sLPVIEWOD    lpViewOD,", nTempIndent, " " );
   SysWriteLine( lpTaskView, f, szLine );
   sprintf_s( szLine, zsizeof( szLine ), "%*sLPVIEWENTITY lpViewEntity,", nTempIndent, " " );
   SysWriteLine( lpTaskView, f, szLine );
   if ( bUniqueQual )
   {
      sprintf_s( szLine, zsizeof( szLine ), "%*sLPQUALENTITY lpQualEntity,", nTempIndent, " " );
      SysWriteLine( lpTaskView, f, szLine );
   }

   sprintf_s( szLine, zsizeof( szLine ), "%*sint         nIndicators,", nTempIndent, " " );
   SysWriteLine( lpTaskView, f, szLine );
   sprintf_s( szLine, zsizeof( szLine ), "%*szSHORT      nTraceLevel )", nTempIndent, " " );
   SysWriteLine( lpTaskView, f, szLine );

   SysWriteLine( lpTaskView, f, "{" );
   SysWriteLine( lpTaskView, f, "   zSHORT nRC       = -1;  // Default is no entities loaded." );
   SysWriteLine( lpTaskView, f, "   zLONG nRowCount  = 0;" );
   SysWriteLine( lpTaskView, f, "   zPCHAR pch       = 0;" );
   SysWriteLine( lpTaskView, f, " " );

   // Call SQL generator to generate the SQL.  We'll set the flag to
   // indicate that we want the 'INTO' clause generated.
   Callback.bGenerateIntoClause = TRUE;
   SqlInitBoundAttrList( &lpBoundList, 0, fnDBH_Callback, 0xFFFFFFFF, &Callback );
   nRC = SqlBuildSelect( lpTaskView, lpViewOD, lpViewEntity, lpQualEntity,
                         szSqlCmd, lpBoundList );

   SysWriteLine( lpTaskView, f, "   EXEC SQL BEGIN DECLARE SECTION;" );

   //
   // =================== Local Variables ========================
   //

   // Before we write the SQL we need to generate the variables.
   for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
         lpBoundAttr;
         lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
   {
      LPVIEWATTRIB lpViewAttrib;
      LPVIEWENTITY lpBoundViewEntity;

      lpViewAttrib      = zGETPTR( lpBoundAttr->lpDataField->hViewAttrib );
      lpBoundViewEntity = zGETPTR( lpViewAttrib->hViewEntity );

      if ( bUniqueQual )
         nGen = GEN_UNIQUE;
      else
         nGen = 0;

      // If lpBoundAttr->pszValue is not NULL then the bound attr is used in
      // the qualification of the SELECT.
      if ( lpBoundAttr->pszValue )
         nGen |= GEN_QUAL;

      if ( bUniqueQual )
         nGen |= GEN_UNIQUE;

      strcpy_s( szLine, zsizeof( szLine ), " " );

      // For supported types see "Supported SQL Data Types" in the "DB2
      // Application Programming" reference.
      switch ( lpViewAttrib->cType )
      {
         case zTYPE_INTEGER:
            strcat_s( szLine, zsizeof( szLine ), "long " );
            break;

         case zTYPE_BLOB:
            strcat_s( szLine, zsizeof( szLine ), "sql type is blob_locator" );
            SysWriteLine( lpTaskView, f, szLine );
            strcpy_s( szLine, zsizeof( szLine ), " " );
            break;

         case zTYPE_STRING:
            if ( lpBoundAttr->lpDataField->cFldType == 'V' )
            {
               strcat_s( szLine, zsizeof( szLine ), "sql type is clob_locator" );
               SysWriteLine( lpTaskView, f, szLine );
               strcpy_s( szLine, zsizeof( szLine ), " " );
            }
            else
               strcat_s( szLine, zsizeof( szLine ), "char " );

            break;

         default:
            strcat_s( szLine, zsizeof( szLine ), "char " );
            break;
      }

      // Generate local variable name.  See comment before this oper for
      // more info on why we use ZKeys instead of names.
      fnGenerateVarName( &szLine[ zstrlen( szLine ) ], lpViewEntity,
                         lpBoundViewEntity, lpViewAttrib, nGen );

      switch ( lpViewAttrib->cType )
      {
         case zTYPE_INTEGER:
            break;

         case zTYPE_BLOB:
            // We need to create the line that frees blob locators.
            if ( szFreeLocatorsCmd[ 0 ] == 0 )
               strcpy_s( szFreeLocatorsCmd, zsizeof( szFreeLocatorsCmd ), "EXEC SQL FREE LOCATOR " );
            else
               strcat_s( szFreeLocatorsCmd, zsizeof( szFreeLocatorsCmd ), ", " );

            strcat_s( szFreeLocatorsCmd, zsizeof( szFreeLocatorsCmd ), ":" );
            fnGenerateVarName( &szFreeLocatorsCmd[ zstrlen( szFreeLocatorsCmd ) ],
                               lpViewEntity,
                               lpBoundViewEntity, lpViewAttrib, nGen );
            break;

         case zTYPE_DATE:
         case zTYPE_TIME:
         case zTYPE_DATETIME:
            strcat_s( szLine, zsizeof( szLine ), " [ 27 ]" );
            break;

         case zTYPE_STRING:
            if ( lpBoundAttr->lpDataField->cFldType == 'V' )
            {
               // We need to create the line that frees blob locators.
               if ( szFreeLocatorsCmd[ 0 ] == 0 )
                  strcpy_s( szFreeLocatorsCmd, zsizeof( szFreeLocatorsCmd ), "EXEC SQL FREE LOCATOR " );
               else
                  strcat_s( szFreeLocatorsCmd, zsizeof( szFreeLocatorsCmd ), ", " );

               strcat_s( szFreeLocatorsCmd, zsizeof( szFreeLocatorsCmd ), ":" );
               fnGenerateVarName( &szFreeLocatorsCmd[ zstrlen( szFreeLocatorsCmd ) ],
                                  lpViewEntity,
                                  lpBoundViewEntity, lpViewAttrib, nGen );
               break;
            }

            // Otherwise FALL THROUGH!!!

         default:
         {
            zCHAR sz[ 10 ];

            strcat_s( szLine, zsizeof( szLine ), "[ " );
            zltoa( lpViewAttrib->ulLth + 1, sz, zsizeof( sz ) );
            strcat_s( szLine, zsizeof( szLine ), sz );
            strcat_s( szLine, zsizeof( szLine ), " ]" );
            break;
         }
      }

      strcat_s( szLine, zsizeof( szLine ), ";" );

      while ( zstrlen( szLine ) < 45 )
         strcat_s( szLine, zsizeof( szLine ), " " );

      if ( lpBoundViewEntity != lpViewEntity )
      {
         zCHAR szTemp[ 100 ];

         sprintf_s( szTemp, zsizeof( szTemp ), "// %s.%s", lpBoundViewEntity->szName,
                    lpViewAttrib->szName );
         strcat_s( szLine, zsizeof( szLine ), szTemp );
      }
      else
      {
         zCHAR szTemp[ 100 ];

         sprintf_s( szTemp, zsizeof( szTemp ), "// %s.%s", lpViewEntity->szName,
                    lpViewAttrib->szName );
         strcat_s( szLine, zsizeof( szLine ), szTemp );
      }

      SysWriteLine( lpTaskView, f, szLine );

      // Generate NULL indicator variable for attributes we are loading.
      // If lpBoundAttr->pszValue is not NULL then the bound attr is used in
      // the qualification of the SELECT.
      if ( lpViewAttrib->bRequired == FALSE && lpBoundAttr->pszValue == 0 )
      {
         zCHAR szNullIndicator[ 100 ];

         fnGenerateVarName( szNullIndicator, lpViewEntity,
                            lpBoundViewEntity, lpViewAttrib,
                            (zSHORT) (nGen | GEN_NULL) );

         sprintf_s( szLine, zsizeof( szLine ), "     short   %s;", szNullIndicator );
         SysWriteLine( lpTaskView, f, szLine );
      }

   } // for ( lpBoundAttr )...

   if ( bUniqueQual )
      nGen = GEN_UNIQUE;
   else
      nGen = 0;

   // We started a DECLARE section so we need to end it.
   SysWriteLine( lpTaskView, f, "   EXEC SQL END DECLARE SECTION;" );
   SysWriteLine( lpTaskView, f, " " );

   //
   // =================== Qualification ========================
   //
   // Retrieve the values for the qualification.
   //
   for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
         lpBoundAttr;
         lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
   {
      int          nIndent;
      zPCHAR       pch;
      LPVIEWATTRIB lpViewAttrib;
      LPVIEWENTITY lpBoundViewEntity;

      // If lpBoundAttr->pszValue is not NULL then the bound attr is used in
      // the qualification of the SELECT.
      if ( lpBoundAttr->pszValue == 0 )
         continue;

      lpViewAttrib      = zGETPTR( lpBoundAttr->lpDataField->hViewAttrib );
      lpBoundViewEntity = zGETPTR( lpViewAttrib->hViewEntity );

      strcpy_s( szLine, zsizeof( szLine ), " " );

      // If the bound entity and the ViewEntity are the same then qualification
      // for the current entity must be coming from a qualification object.
      if ( lpBoundViewEntity == lpViewEntity )
      {
         // For supported types see "Supported SQL Data Types" in the "DB2
         // Application Programming" reference.
         switch ( lpViewAttrib->cType )
         {
            case zTYPE_INTEGER:
               strcat_s( szLine, zsizeof( szLine ), "SDB2_GetIntegerFromQualification( &" );
               break;

            default:
               strcat_s( szLine, zsizeof( szLine ), "SDB2_GetStringFromQualification( " );
               break;
         }

         nIndent = zstrlen( szLine ) - 1;

         // Generate local variable name.  See comment before this oper for
         // more info on why we use ZKeys instead of names.
         pch = szLine + zstrlen( szLine );
         fnGenerateVarName( pch, lpViewEntity,
                            lpBoundViewEntity, lpViewAttrib,
                            (zSHORT) (nGen | GEN_QUAL) );
         strcat_s( pch, zsizeof( szLine ) - (pch - szLine), "," );
         SysWriteLine( lpTaskView, f, szLine );

         sprintf_s( szLine, zsizeof( szLine ), "%*slpViewEntity, \"%s\", lpQualEntity );",
                    nIndent, " ", lpViewAttrib->szName );
         SysWriteLine( lpTaskView, f, szLine );
      }
      else
      {
         // For supported types see "Supported SQL Data Types" in the "DB2
         // Application Programming" reference.
         switch ( lpViewAttrib->cType )
         {
            case zTYPE_INTEGER:
               strcat_s( szLine, zsizeof( szLine ), "SDB2_GetIntegerFromAttribute( &" );
               break;

            default:
               strcat_s( szLine, zsizeof( szLine ), "SDB2_GetStringFromAttribute( " );
               break;
         }

         nIndent = zstrlen( szLine ) - 1;

         // Generate local variable name.  See comment before this oper for
         // more info on why we use ZKeys instead of names.
         pch = szLine + zstrlen( szLine );
         fnGenerateVarName( pch, lpViewEntity, lpBoundViewEntity, lpViewAttrib, (zSHORT) (nGen | GEN_QUAL) );
         strcat_s( pch, zsizeof( szLine ) - (pch - szLine), "," );
         SysWriteLine( lpTaskView, f, szLine );

         sprintf_s( szLine, zsizeof( szLine ), "%*slpView, lpViewOD, \"%s\", \"%s\" );",
                    nIndent, " ", lpBoundViewEntity->szName, lpViewAttrib->szName );
         SysWriteLine( lpTaskView, f, szLine );
      }
   }

   SysWriteLine( lpTaskView, f, " " );

   // If the result of the SELECT statement can have more than 1 row we need to declare a cursor.
   // If we have unique qualification then we know we are only loading 1 entity.
   if ( bUniqueQual == FALSE && (lpViewEntity->hParent == 0 || lpViewEntity->uCardMax > 1) )
   {
      zPCHAR pch;
      zBOOL  bFirstAttr;

      // Free up last generate stuff.
      SqlFreeBoundAttrList( lpBoundList );
   // lpBoundList = 0;

      //
      // =================== Declare Cursor ========================
      //
      // Generate the SQL again but don't create 'INTO' clause.
      Callback.bGenerateIntoClause = FALSE;
      SqlInitBoundAttrList( &lpBoundList, 0, fnDBH_Callback, 0xFFFFFFFF, &Callback );
      nRC = SqlBuildSelect( lpTaskView, lpViewOD, lpViewEntity, lpQualEntity, szSqlCmd, lpBoundList );

      // Now generate the cursor for the SQL statement.
      sprintf_s( szLine, zsizeof( szLine ), "  EXEC SQL DECLARE c%d CURSOR FOR", lpViewEntity->nHierNbr );
      SysWriteLine( lpTaskView, f, szLine );
      strcat_s( szSqlCmd, zsizeof( szSqlCmd ), ";" );
      g_nIndent = 6;
      SqlDisplayCommandEx( szSqlCmd, 0, (zPVOID) fnWriteSql, (zPVOID) f );

      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "   if ( nTraceLevel >= 1 )" );
      SysWriteLine( lpTaskView, f, "   {" );
      SysWriteLine( lpTaskView, f, "      pch = " );
      g_nIndent = 9;
      SqlDisplayCommandEx( szSqlCmd, 0, (zPVOID) fnWriteSql2, (zPVOID) f );
      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "      TraceLineS( \"\", \"\" );" );
      SysWriteLine( lpTaskView, f, "      TraceLineS( \"Executed following static code:\", \"\" );" );
      SysWriteLine( lpTaskView, f, "      SqlDisplayCommand( pch, 0 );" );
      SysWriteLine( lpTaskView, f, "      TraceLineI( \"Return code: \", SQLCODE );" );
      SysWriteLine( lpTaskView, f, "   }" );

      SqlFreeBoundAttrList( lpBoundList );
   // lpBoundList = 0;

      SysWriteLine( lpTaskView, f, " " );
      sprintf_s( szLine, zsizeof( szLine ), "  EXEC SQL OPEN c%d;", lpViewEntity->nHierNbr );
      SysWriteLine( lpTaskView, f, szLine );
      SysWriteLine( lpTaskView, f, "   while ( TRUE )" );
      SysWriteLine( lpTaskView, f, "   {" );

      // Now re-generate the original SELECT statement.
      Callback.bGenerateIntoClause = TRUE;
      SqlInitBoundAttrList( &lpBoundList, 0, fnDBH_Callback, 0xFFFFFFFF, &Callback );
      nRC = SqlBuildSelect( lpTaskView, lpViewOD, lpViewEntity, lpQualEntity, szSqlCmd, lpBoundList );

      //
      // =================== Generate 'INTO' ========================
      //
      sprintf_s( szSqlCmd, zsizeof( szSqlCmd ), "  EXEC SQL FETCH c%d INTO", lpViewEntity->nHierNbr );
      pch = szSqlCmd;
      bFirstAttr = TRUE;
      for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
            lpBoundAttr;
            lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
      {
         LPVIEWATTRIB lpViewAttrib;
         LPVIEWENTITY lpBoundViewEntity;

         // If lpBoundAttr->pszValue is not NULL then the bound attr is used in the qualification of the SELECT.
         if ( lpBoundAttr->pszValue )
            continue;   // This is a qual attrib so skip it.

         lpViewAttrib      = zGETPTR( lpBoundAttr->lpDataField->hViewAttrib );
         lpBoundViewEntity = zGETPTR( lpViewAttrib->hViewEntity );

         if ( bFirstAttr )
            bFirstAttr = FALSE;
         else
            strcat_s( pch, zsizeof( szSqlCmd ) - (pch - szSqlCmd), "," );

         // Find the end of the command.
         strcat_s( pch, zsizeof( szSqlCmd ) - (pch - szSqlCmd), " :" );
         pch = pch + zstrlen( pch );
         fnGenerateVarName( pch, lpViewEntity, lpBoundViewEntity, lpViewAttrib, nGen );

         if ( lpViewAttrib->bRequired == FALSE )
         {
            zCHAR szNullIndicator[ 100 ];
            zLONG lLth;

            fnGenerateVarName( szNullIndicator, lpViewEntity, lpBoundViewEntity,
                               lpViewAttrib, (zSHORT) (nGen | GEN_NULL) );

            lLth =  zstrlen( pch );
            pch = pch + lLth;
            sprintf_s( pch, zsizeof( szSqlCmd ) - (pch - szSqlCmd), " INDICATOR :%s", szNullIndicator );
         }
      }

      strcat_s( szSqlCmd, zsizeof( szSqlCmd ), ";" );
      g_nIndent = 3;
      fnWriteSql( lpTaskView, szSqlCmd, (zPVOID) f );
      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "      if ( nTraceLevel >= 1 )" );
      SysWriteLine( lpTaskView, f, "      {" );
      SysWriteLine( lpTaskView, f, "         pch = " );
      g_nIndent = 12;
      fnWriteSql2( lpTaskView, szSqlCmd, (zPVOID) f );
      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "         TraceLineS( \"\", \"\" );" );
      SysWriteLine( lpTaskView, f, "         TraceLineS( \"Executed following static code:\", \"\" );" );
      SysWriteLine( lpTaskView, f, "         SqlDisplayCommand( pch, 0 );" );
      SysWriteLine( lpTaskView, f, "         TraceLineI( \"Return code: \", SQLCODE );" );
      SysWriteLine( lpTaskView, f, "      }" );
      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "      if ( SQLCODE != 0 )" );
      SysWriteLine( lpTaskView, f, "         break;" );
      SysWriteLine( lpTaskView, f, " " );

      // If the entity is the root entity then check for multiple roots.
      if ( lpViewEntity->hParent == 0 )
      {
         SysWriteLine( lpTaskView, f, "      if ( nRowCount >= 1 )" );
         SysWriteLine( lpTaskView, f, "      {" );
         SysWriteLine( lpTaskView, f, "         nRC = 1;  // Indicate that 1 entity was loaded." );
         SysWriteLine( lpTaskView, f, " " );
         SysWriteLine( lpTaskView, f, "         // If we're not supposed to activate muliple roots then stop loading." );
         SysWriteLine( lpTaskView, f, "         if ( (nIndicators & zMULTIPLE ) == 0 )" );
         SysWriteLine( lpTaskView, f, "            break;" );
         SysWriteLine( lpTaskView, f, "      }" );
         SysWriteLine( lpTaskView, f, "      else" );
         SysWriteLine( lpTaskView, f, "         nRC = 0;  // Indicate that 1 entity was loaded." );
         SysWriteLine( lpTaskView, f, " " );
      }
      else
         SysWriteLine( lpTaskView, f, "      nRC = 0;  // Indicate that 1 entity was loaded." );

      // Check for multi-root limit.
      if ( lpViewEntity->lActivateLimit )
      {
         SysWriteLine( lpTaskView, f, "      if ( nRowCount >= lpViewEntity->lActivateLimit ) " );
         SysWriteLine( lpTaskView, f, "      {" );
         SysWriteLine( lpTaskView, f, "         nRC = 2;" );
         SysWriteLine( lpTaskView, f, "         break;" );
         SysWriteLine( lpTaskView, f, "      }" );
         SysWriteLine( lpTaskView, f, " " );
      }

      SysWriteLine( lpTaskView, f, " " );

      // Set g_nIndent for indentation of the loading of the entity.
      g_nIndent = 6;
   }
   else
   {
      //
      // =================== Generate Single Select ========================
      //
      // We are only expecting 1 result so we don't need a cursor.
      g_nIndent = 3;
      SysWriteLine( lpTaskView, f, "   EXEC SQL" );
      strcat_s( szSqlCmd, zsizeof( szSqlCmd ), ";" );
      SqlDisplayCommandEx( szSqlCmd, 0, (zPVOID) fnWriteSql, (zPVOID) f );
      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "   if ( nTraceLevel >= 1 )" );
      SysWriteLine( lpTaskView, f, "   {" );
      SysWriteLine( lpTaskView, f, "      pch = " );
      g_nIndent = 9;
      SqlDisplayCommandEx( szSqlCmd, 0, (zPVOID) fnWriteSql2, (zPVOID) f );
      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "      TraceLineS( \"\", \"\" );" );
      SysWriteLine( lpTaskView, f, "      TraceLineS( \"Executed following static code:\", \"\" );" );
      SysWriteLine( lpTaskView, f, "      SqlDisplayCommand( pch, 0 );" );
      SysWriteLine( lpTaskView, f, "      TraceLineI( \"Return code: \", SQLCODE );" );
      SysWriteLine( lpTaskView, f, "   }" );
      SysWriteLine( lpTaskView, f, " " );

      // Set g_nIndent for indentation of the loading of the entity.
      g_nIndent = 3;

      SysWriteLine( lpTaskView, f, "   if ( SQLCODE != 0 )" );
      SysWriteLine( lpTaskView, f, "      return( nRC );" );
      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "   nRC = 0;  // We found an entity." );
      SysWriteLine( lpTaskView, f, " " );
   }

   //
   // =================== Load Entity/Attributes ========================
   //
   // Create the Entity and load the attributes.
   sprintf_s( szLine, zsizeof( szLine ), "%*snRowCount++;", g_nIndent, " " );
   SysWriteLine( lpTaskView, f, szLine );
   sprintf_s( szLine, zsizeof( szLine ), "%*sLoadEntity( lpView, \"%s\", zPOS_AFTER, 0 );",
              g_nIndent, " ", lpViewEntity->szName );
   SysWriteLine( lpTaskView, f, szLine );
   SysWriteLine( lpTaskView, f, " " );

   // Load the attrs.
   for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
         lpBoundAttr;
         lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
   {
      zCHAR        szVar[ 100 ];
      LPVIEWATTRIB lpViewAttrib;
      LPVIEWENTITY lpBoundViewEntity;

      lpViewAttrib      = zGETPTR( lpBoundAttr->lpDataField->hViewAttrib );
      lpBoundViewEntity = zGETPTR( lpViewAttrib->hViewEntity );

      // We only care about attributes that are part of the entity we
      // are loading (not qualification attribs).
      // If lpBoundAttr->pszValue is not NULL then the bound attr is used in
      // the qualification of the SELECT.
      if ( lpBoundAttr->pszValue )
         continue;

      sprintf_s( szLine, zsizeof( szLine ), "%*s// %s.%s ", g_nIndent, " ",
                 lpViewEntity->szName, lpViewAttrib->szName );
      SysWriteLine( lpTaskView, f, szLine );

      switch ( lpViewAttrib->cType )
      {
         case zTYPE_INTEGER:
            sprintf_s( szLine, zsizeof( szLine ), "%*sSDB2_SetAttributeFromInteger( lpView, "
                       "lpViewOD, lpViewEntity, \"%s\",", g_nIndent, " ", lpViewAttrib->szName );
            fnGenerateVarName( szVar, lpViewEntity, lpBoundViewEntity, lpViewAttrib, nGen );

            break;

         case zTYPE_BLOB:
         {
            // We need to load blobs in chunks because we don't know the lth
            // until run time.
            fnGenerateLargeAttribute( lpTaskView, f, lpViewEntity,
                                      lpViewAttrib, nGen, szLine );

            // Set the attribute from the retrieved blob.
            // --> SDB2_SetAttributeFromBlob( lpView, lpViewOD, lpViewEntity, "_attr_name_",
            sprintf_s( szLine, zsizeof( szLine ), "%*sSDB2_SetAttributeFromBlob( lpView, "
                       "lpViewOD, lpViewEntity, \"%s\", ",
                       g_nIndent, " ", lpViewAttrib->szName );

            // szVar is the name of the variable we are sending to SDB2_SetAttributeFromBlob( ).
            sprintf_s( szVar, zsizeof( szVar ), "g_pvBuffer %s", lpViewOD->szName );
            break;
         }

         default:
            if ( lpBoundAttr->lpDataField->cFldType == 'V' )
            {
               fnGenerateLargeAttribute( lpTaskView, f, lpViewEntity,
                                         lpViewAttrib, nGen, szLine );
               sprintf_s( szLine, zsizeof( szLine ), "%*sSDB2_SetAttributeFromBlob( lpView, "
                          "lpViewOD, lpViewEntity, \"%s\", ", g_nIndent, " ", lpViewAttrib->szName );
               sprintf_s( szVar, zsizeof( szVar ), "g_pvBuffer %s", lpViewOD->szName );
            }
            else
            {
               sprintf_s( szLine, zsizeof( szLine ), "%*sSDB2_SetAttributeFromString( lpView, "
                          "lpViewOD, lpViewEntity, \"%s\",", g_nIndent, " ", lpViewAttrib->szName );

               fnGenerateVarName( szVar, lpViewEntity, lpBoundViewEntity, lpViewAttrib, nGen );
            }
            break;
      }

      SysWriteLine( lpTaskView, f, szLine );

      sprintf_s( szLine, zsizeof( szLine ), "%*s%s, ", 30 + g_nIndent, " ", szVar );
      if ( lpViewAttrib->bRequired == FALSE )
         fnGenerateVarName( &szLine[ zstrlen( szLine ) ], lpViewEntity,
                            lpBoundViewEntity, lpViewAttrib, (zSHORT) (nGen | GEN_NULL) );
      else
         strcat_s( szLine, zsizeof( szLine ), "0" );

      // Blobs need a lth.
      if ( lpViewAttrib->cType == zTYPE_BLOB )
         strcat_s( szLine, zsizeof( szLine ), ", g_lColumnLth" );

      strcat_s( szLine, zsizeof( szLine ), " );" );

      SysWriteLine( lpTaskView, f, szLine );
   }

   // Free the locators (if there are any).
   if ( szFreeLocatorsCmd[ 0 ] )
   {
      SysWriteLine( lpTaskView, f, " " );
      sprintf_s( szLine, zsizeof( szLine ), "  %s;", szFreeLocatorsCmd );
      fnWriteSql( lpTaskView, szLine, (zPVOID) f );
      SysWriteLine( lpTaskView, f, szLine );
   }

   // Close the 'while ' statement if we have a cursor.
   if ( bUniqueQual == FALSE &&
        (lpViewEntity->hParent == 0 || lpViewEntity->uCardMax > 1) )
   {
      SysWriteLine( lpTaskView, f, " " );
      SysWriteLine( lpTaskView, f, "   } // while ( TRUE )..." );
      SysWriteLine( lpTaskView, f, " " );
      sprintf_s( szLine, zsizeof( szLine ), "  EXEC SQL CLOSE c%d;", lpViewEntity->nHierNbr );
      SysWriteLine( lpTaskView, f, szLine );
   }

   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   return( nRC );" );
   SysWriteLine( lpTaskView, f, "}" );
   SysWriteLine( lpTaskView, f, " " );

   SqlFreeBoundAttrList( lpBoundList );
// lpBoundList = 0;
}

void LOCALOPER
fnBuildInsertFunction( zLONG        f,
                       zVIEW        lpTaskView,
                       LPVIEWOD     lpViewOD,
                       LPVIEWENTITY lpViewEntity )
{
   zSHORT           nRC;
   zCHAR            szLine[ 500 ];
   int              nTempIndent;
   zBOOL            bDeclareSectionStarted = FALSE;
   zPCHAR           pch;
   LPBOUNDATTR      lpBoundAttr;
   CallbackRecord   Callback;
   LPBOUNDLIST      lpBoundList = 0;
   zCHAR            szSqlCmd[ 10000 ];
   zLONG            lLth;

   zmemset( &Callback, 0, sizeof( Callback ) );
   Callback.lpViewEntity = lpViewEntity;
   Callback.bInsert = TRUE;

   //
   // =================== Function Name ========================
   //
   SysWriteLine( lpTaskView, f, "zSHORT OPERATION" );
   sprintf_s( szLine, zsizeof( szLine ), "SQL_%s_%s_Insert( zVIEW       lpView,",
              lpViewOD->szName, lpViewEntity->szName );
   SysWriteLine( lpTaskView, f, szLine );

   pch = zstrchr( szLine, '(' ) + 2;
   nTempIndent = (int) ( pch - szLine );
   sprintf_s( szLine, zsizeof( szLine ), "%*sLPVIEWENTITY lpViewEntity,", nTempIndent, " " );
   SysWriteLine( lpTaskView, f, szLine );
   sprintf_s( szLine, zsizeof( szLine ), "%*szSHORT      nTraceLevel )", nTempIndent, " " );
   SysWriteLine( lpTaskView, f, szLine );

   SysWriteLine( lpTaskView, f, "{" );
   SysWriteLine( lpTaskView, f, "   zPCHAR pch       = 0;" );
   SysWriteLine( lpTaskView, f, " " );

   // We don't need to declare a section for the insert operation because
   // they've already been declared in the Select operation.

   // Call SQL generator to generate the SQL.
   SqlInitBoundAttrList( &lpBoundList, 0, fnDBH_Callback, 0xFFFFFFFF, &Callback );
   nRC = SqlBuildInsert( lpTaskView, lpViewOD, lpViewEntity, szSqlCmd, lpBoundList );

   //
   // =================== Local Variables ========================
   //

   // Before we write the SQL we need to generate the variables.
   for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
         lpBoundAttr;
         lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
   {
      LPVIEWATTRIB lpViewAttrib;
      LPVIEWENTITY lpBoundViewEntity;

      lpViewAttrib      = zGETPTR( lpBoundAttr->lpDataField->hViewAttrib );
      lpBoundViewEntity = zGETPTR( lpViewAttrib->hViewEntity );

      strcpy_s( szLine, zsizeof( szLine ), " " );

      // For supported types see "Supported SQL Data Types" in the "DB2
      // Application Programming" reference.
      switch ( lpViewAttrib->cType )
      {
         case zTYPE_INTEGER:
            strcat_s( szLine, zsizeof( szLine ), "long " );
            break;

         default:
            strcat_s( szLine, zsizeof( szLine ), "char " );
            break;
      }

      // Generate local variable name.  See comment before this oper for
      // more info on why we use ZKeys instead of names.
      fnGenerateVarName( &szLine[ zstrlen( szLine ) ], lpViewEntity,
                         lpBoundViewEntity, lpViewAttrib, 0 );

      switch ( lpViewAttrib->cType )
      {
         case zTYPE_INTEGER:
            break;

         case zTYPE_DATE:
         case zTYPE_TIME:
         case zTYPE_DATETIME:
            strcat_s( szLine, zsizeof( szLine ), " [ 27 ]" );
            break;

         default:
         {
            zCHAR sz[ 10 ];

            strcat_s( szLine, zsizeof( szLine ), "[ " );
            zltoa( lpViewAttrib->ulLth + 1, sz, zsizeof( sz ) );
            strcat_s( szLine, zsizeof( szLine ), sz );
            strcat_s( szLine, zsizeof( szLine ), " ]" );
            break;
         }
      }

      strcat_s( szLine, zsizeof( szLine ), ";" );

      while ( zstrlen( szLine ) < 45 )
         strcat_s( szLine, zsizeof( szLine ), " " );

      lLth = zstrlen( szLine );
      sprintf_s( &szLine[ lLth ], zsizeof( szLine ) - lLth, "// %s.%s",
                 lpViewEntity->szName, lpViewAttrib->szName );

      SysWriteLine( lpTaskView, f, szLine );

   } // for ( lpBoundAttr )...

   SysWriteLine( lpTaskView, f, " " );

   //
   // =================== Get Attr Values ========================
   //
   // Retrieve the values for the qualification.
   //
   for ( lpBoundAttr = lpBoundList->lpFirstBoundAttr;
         lpBoundAttr;
         lpBoundAttr = lpBoundAttr->lpNextBoundAttr )
   {
      int          nIndent;
      zPCHAR       pch;
      LPVIEWATTRIB lpViewAttrib;
      LPVIEWENTITY lpBoundViewEntity;

      lpViewAttrib      = zGETPTR( lpBoundAttr->lpDataField->hViewAttrib );
      lpBoundViewEntity = zGETPTR( lpViewAttrib->hViewEntity );

      strcpy_s( szLine, zsizeof( szLine ), " " );

      // For supported types see "Supported SQL Data Types" in the "DB2
      // Application Programming" reference.
      switch ( lpViewAttrib->cType )
      {
         case zTYPE_INTEGER:
            strcat_s( szLine, zsizeof( szLine ), "fnGetIntegerFromAttribute( &" );
            break;

         default:
            strcat_s( szLine, zsizeof( szLine ), "fnGetStringFromAttribute( " );
            break;
      }

      nIndent = zstrlen( szLine ) - 1;

      // Generate local variable name.  See comment before this oper for
      // more info on why we use ZKeys instead of names.
      pch = szLine + zstrlen( szLine );
      fnGenerateVarName( pch, lpViewEntity,
                         lpBoundViewEntity, lpViewAttrib, 0  );
      strcat_s( pch, zsizeof( szLine ) - (pch - szLine), "," );
      SysWriteLine( lpTaskView, f, szLine );

      sprintf_s( szLine, zsizeof( szLine ), "%*slpView, lpViewOD, \"%s\", \"%s\" );",
                 nIndent, " ",
                 lpBoundViewEntity->szName, lpViewAttrib->szName );
      SysWriteLine( lpTaskView, f, szLine );
   }

   SysWriteLine( lpTaskView, f, " " );

   g_nIndent = 3;
   SysWriteLine( lpTaskView, f, "   EXEC SQL" );
   strcat_s( szSqlCmd, zsizeof( szSqlCmd ), ";" );
   SqlDisplayCommandEx( szSqlCmd, 0, (zPVOID) fnWriteSql, (zPVOID) f );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   if ( nTraceLevel >= 1 )" );
   SysWriteLine( lpTaskView, f, "   {" );
   SysWriteLine( lpTaskView, f, "      pch = " );
   g_nIndent = 9;
   SqlDisplayCommandEx( szSqlCmd, 0, (zPVOID) fnWriteSql2, (zPVOID) f );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"\", \"\" );" );
   SysWriteLine( lpTaskView, f, "      TraceLineS( \"Executed following static code:\", \"\" );" );
   SysWriteLine( lpTaskView, f, "      SqlDisplayCommand( pch, 0 );" );
   SysWriteLine( lpTaskView, f, "      TraceLineI( \"Return code: \", SQLCODE );" );
   SysWriteLine( lpTaskView, f, "   }" );
   SysWriteLine( lpTaskView, f, " " );

   // Set g_nIndent for indentation of the loading of the entity.
   g_nIndent = 3;

   SysWriteLine( lpTaskView, f, "   if ( SQLCODE != 0 )" );
   SysWriteLine( lpTaskView, f, "      return( nRC );" );
   SysWriteLine( lpTaskView, f, " " );
   SysWriteLine( lpTaskView, f, "   nRC = 0;  // We found an entity." );
   SysWriteLine( lpTaskView, f, " " );

   SysWriteLine( lpTaskView, f, "}" );
   SysWriteLine( lpTaskView, f, " " );

   SqlFreeBoundAttrList( lpBoundList );
// lpBoundList = 0;
}

/*

Generate a bind plan for the currently loaded TZZOLODO.

We generate variable names using ZKeys instead of entity/attribute names
because:
o  They have to be less than 31 chars long.
o  They have to be unique for all variables in the file.

NOTE: We pass back the name of the filename through pchFileName.

*/
zSHORT LOCALOPER
fnGenerateBindForLOD( zPCHAR pchReturnFileName,
                      zPCHAR pchReturnDirectory,
                      zVIEW  vTZZOLODO,
                      zVIEW  vTZZOXODO )
{
   zSHORT          nReturn = zCALL_ERROR;
   zVIEW           vTaskLPLR;
   zVIEW           vZeidonSubtask = 0;
   zVIEW           lpView;
   zVIEW           vSubtask;
   zLONG           f = -1;
   zCHAR           szLOD_Name[ zZEIDON_NAME_LTH + 1 ];
   zCHAR           szLPLR_Name[ zZEIDON_NAME_LTH + 1 ];
   zCHAR           szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR           szTempFileName[ zMAX_FILESPEC_LTH + 1 ];
   LPVIEWOD        lpViewOD;
   LPVIEWENTITY    lpViewEntity;

   CreateViewFromViewForTask( &vTZZOLODO, vTZZOLODO, 0 );
   CreateViewFromViewForTask( &vTZZOXODO, vTZZOXODO, 0 );

   GetViewByName( &vTaskLPLR, "TaskLPLR", vZeidonSubtask, zLEVEL_TASK );
   GetStringFromAttribute( szLPLR_Name, zsizeof( szLPLR_Name ), vTaskLPLR, "LPLR", "Name" );
   SfCreateSubtask( &vSubtask, vTZZOLODO, szLPLR_Name );

   GetStringFromAttribute( szFileName, zsizeof( szFileName ), vTaskLPLR, "LPLR", "MetaSrcDir" );
   strcpy_s( pchReturnDirectory, zMAX_FILESPEC_LTH + 1,  szFileName );
   SysAppendcDirSep( szFileName );
   GetStringFromAttribute( szLOD_Name, zsizeof( szLOD_Name ), vTZZOLODO, "LOD", "Name" );
   strcpy_s( pchReturnFileName, zMAX_FILESPEC_LTH + 1, szLOD_Name );
   strcat_s( szFileName, zsizeof( szFileName ), szLOD_Name );
   strcpy_s( szTempFileName, zsizeof( szTempFileName ), szFileName ); // Save temp file name for later.
   strcat_s( pchReturnFileName, zMAX_FILESPEC_LTH + 1, ".sqc" );
   strcat_s( szFileName, zsizeof( szFileName ), ".sqc" );
   f = SysOpenFile( vTZZOLODO, szFileName, COREFILE_WRITE );
   if ( f == -1 )
      goto EndOfFunction;

   SysWriteLine( vTZZOLODO, f, "#define KZSYSSVC_INCL" );
   SysWriteLine( vTZZOLODO, f, "#include \"KZOENGAA.H\" " );
   SysWriteLine( vTZZOLODO, f, "#include \"KZHSQLGP.H\" " );
   SysWriteLine( vTZZOLODO, f, "#include \"KZHSQLDS.H\" // QuinSoft DB2 static functions." );
   SysWriteLine( vTZZOLODO, f, " " );
   SysWriteLine( vTZZOLODO, f, "// Following is a hack to allow multiple files in a DLL." );
   SysWriteLine( vTZZOLODO, f, "#define struct static struct" );
   SysWriteLine( vTZZOLODO, f, "EXEC SQL INCLUDE SQLCA; " );
   SysWriteLine( vTZZOLODO, f, "#undef struct" );
   SysWriteLine( vTZZOLODO, f, " " );
   SysWriteLine( vTZZOLODO, f, "#ifdef __cplusplus " );
   SysWriteLine( vTZZOLODO, f, "extern \"C\" {" );
   SysWriteLine( vTZZOLODO, f, "#endif" );
   SysWriteLine( vTZZOLODO, f, " " );

   // We need to reload the ViewOD to match the current vTZZOXODO.  First
   // write the XOD.
   strcat_s( szTempFileName, zsizeof( szTempFileName ), ".XOD" );
   if ( CommitOI_ToFile( vTZZOXODO, szTempFileName, 0 ) == zCALL_ERROR )
      goto EndOfFunction;

   // Now tell core to drop the current view OD.
   DropViewObject( vSubtask, szLOD_Name, FALSE );
   lpViewOD = ActivateViewObject( vSubtask, szLOD_Name, FALSE );

   // Create OpenConnection, Commit, etc. functions.
   fnCreateStartFunctions( vTZZOLODO, f, lpViewOD );

   // We will create an empty view so that the SQL generator doesn't barf
   // when creating the SQL.
   ActivateEmptyObjectInstance( &lpView, szLOD_Name, vSubtask, zSINGLE );

   // Loop through all the entities in the LOD and generate a simple SELECT
   // statement.
   for ( lpViewEntity = zGETPTR( lpViewOD->hFirstOD_Entity );
         lpViewEntity;
         lpViewEntity = zGETPTR( lpViewEntity->hNextHier ) )
   {
      // If the view entity doesn't have a data record then it must be a work
      // entity of some sort so we don't need a SQL function to activate it.
      if ( lpViewEntity->hFirstDataRecord == 0 ||
           lpViewEntity->bDerived || lpViewEntity->bDerivedPath )
      {
         continue;
      }

      fnBuildSelectFunction( f, lpView, lpViewOD, lpViewEntity, FALSE );

      if ( lpViewEntity->hParent == 0 )
         fnBuildSelectFunction( f, lpView, lpViewOD, lpViewEntity, TRUE );

   // fnBuildInsertFunction( f, lpView, lpViewOD, lpViewEntity );

   } // for ( lpViewEntity )...

   SysWriteLine( vTZZOLODO, f, "#ifdef __cplusplus " );
   SysWriteLine( vTZZOLODO, f, "}" );
   SysWriteLine( vTZZOLODO, f, "#endif" );

   // If we get here then everything's OK.
   nReturn = 0;

EndOfFunction:
   // Clean up.
   DropView( vTZZOLODO );
   DropView( lpView );

   if ( f != -1 )
      SysCloseFile( vSubtask, f, 0 );

   SfDropSubtask( vSubtask, 0 );

   return( nReturn );
}

/*
   This functions "closes" the Static SQL makefile.  It's not really open...
   what we are doing is finishing the writing process.

   This also "closes" the static SQL bat file.
*/
zSHORT LOCALOPER
fnCloseStaticSqlMakefile( zVIEW  vTaskLPLR,
                          zPCHAR pchMakefileDir,
                          zPCHAR pchLine )
{
   zLONG hMakefile;
   zLONG hBatFile;

   // If g_szSqlDLLName is NULL then there is no file to "close".
   if ( *g_szSqlDLLName == 0 )
      return( 0 );

   sprintf_s( pchLine, 500, "%s\\%s.MAK", pchMakefileDir, g_szSqlDLLName );
   hMakefile = SysOpenFile( vTaskLPLR, pchLine, COREFILE_APPEND );
   if ( hMakefile == -1 )
   {
      sprintf_s( pchLine, 500, "Could not re-open file\n  '%s'.\nCheck Compiler "
                 "Specification for valid Makefile Directory", pchLine );
      MessageSend( vTaskLPLR, "LO00107", "Zeidon Tools",
                   pchLine, zMSGQ_SYSTEM_ERROR, TRUE );
      return( zCALL_ERROR );
   }

   SysWriteLine( vTaskLPLR, hMakefile, "    $(OBJ_DIR)\\kzhsqlds.obj" );
   SysWriteLine( vTaskLPLR, hMakefile, " " );
   SysWriteLine( vTaskLPLR, hMakefile, "# Resolve libraries for external operations" );
   SysWriteLine( vTaskLPLR, hMakefile, "LINKDLLS = $(LINKDLLS) db2api.lib kzhsqlga.obj" );
   SysWriteLine( vTaskLPLR, hMakefile, " " );
   SysWriteLine( vTaskLPLR, hMakefile, "# Include makefile to make target." );

   sprintf_s( pchLine, 500, "!include \"%s\\zcompile.hnm\"", pchMakefileDir );
   SysWriteLine( vTaskLPLR, hMakefile, pchLine );

   SysCloseFile( vTaskLPLR, hMakefile, 0 );

   // Close the batch file that pre-compiles all the .SQC files.
   sprintf_s( pchLine, 500, "%s\\%s.BAT", pchMakefileDir, g_szSqlDLLName );
   hBatFile = SysOpenFile( vTaskLPLR, pchLine, COREFILE_APPEND );
   if ( hBatFile == -1 )
   {
      sprintf_s( pchLine, 500, "Could not re-open file\n  '%s'.\nCheck Compiler "
                 "Specification for valid BatFile Directory", pchLine );
      MessageSend( vTaskLPLR, "LO00107", "Zeidon Tools",
                   pchLine, zMSGQ_SYSTEM_ERROR, TRUE );
      return( zCALL_ERROR );
   }

   SysWriteLine( vTaskLPLR, hBatFile, "rem  Close database connection" );
   SysWriteLine( vTaskLPLR, hBatFile, "db2 connect reset" );
   SysCloseFile( vTaskLPLR, hBatFile, 0 );

   return( 0 );
}

zSHORT LOCALOPER
fnProcessApplA( zVIEW            vApSvDisO,
                zVIEW            vTZZOLODO,
                zVIEW            vTZZOXODO,
                LPDB2_OBJECTDATA lpDB2_Data )
{
   zSHORT nRC;
   zSHORT nReturn = zCALL_ERROR;
   zVIEW  TZDBHDBO;
   zVIEW  vTaskLPLR;
   zCHAR  szFileName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szDirName[ zMAX_FILESPEC_LTH + 1 ];
   zCHAR  szLine[ 1000 ];
   zLONG  hMakefile = -1;
   zLONG  hBatFile = -1;
   zPCHAR pch;
   zPCHAR pchOutDir;
   zPCHAR pchTargetName;
   zPCHAR pchMakefileDir;

   // Try to get the DB2 blob from ApplA.  If it doesn't exist then just return.
   nRC = SetOI_FromBlob( &TZDBHDBO, 0, vTZZOLODO, vApSvDisO,
                         "DS_TE_SourceAssignment", "DBH_Data", zNOI_OKAY );
   if ( nRC == -1 )
      return( 0 );

   // If we aren't using static SQL then there's nothing else to do.
   if ( CompareAttributeToString( TZDBHDBO, "ApplA", "UseStaticSQL", "Y" ) != 0 )
      return( 0 );

   // Generate the static SQL in a .SQC file.
   nRC = fnGenerateBindForLOD( szFileName, szDirName, vTZZOLODO, vTZZOXODO );
   if ( nRC == zCALL_ERROR )
      return( zCALL_ERROR );

   // Set flags in DB2 data to indicate we are want to use static SQL when
   // the object is activated.
   lpDB2_Data->bStoreDB2_Data = TRUE;
   lpDB2_Data->bUseStaticSQL  = TRUE;
   GetStringFromAttribute( lpDB2_Data->szStaticSQL_DLL, zsizeof( lpDB2_Data->szStaticSQL_DLL ), TZDBHDBO, "ApplA", "StaticSQL_DLL_Name" );

   // Now add the .SQC file to the vApSvDisO object so that it get's sent
   // to the server.
   CreateEntity( vApSvDisO, "DS_TempFile", zPOS_LAST );
   SetAttributeFromString( vApSvDisO, "DS_TempFile", "LocalDirectory", szDirName );
   SetAttributeFromString( vApSvDisO, "DS_TempFile", "Name", szFileName );

   //=====================================================================
   //
   // Add the object to the makefile for building the static SQL.
   // Add the object to the batch file for precompiling the SQL.
   //
   //=====================================================================

   // Get the task LPLR and set the compiler.  Then retrieve the makefile
   // directory.
   GetViewByName( &vTaskLPLR, "TaskLPLR", vApSvDisO, zLEVEL_TASK );
   SetCursorFirstEntityByAttr( vTaskLPLR, "Compiler", "Name",
                               vTaskLPLR, "LPLR", "CurrentCompilerSpec", 0 );
   GetAddrForAttribute( &pchMakefileDir, vTaskLPLR, "Compiler", "MakefileDir" );
   pchTargetName = lpDB2_Data->szStaticSQL_DLL;

   sprintf_s( szFileName, zsizeof( szFileName ), "%s\\%s.MAK", pchMakefileDir, pchTargetName );

   // Now check to see if the DLL name is the same as the last DLL name.
   // If it is not then we need to create and initialize the make file.  If
   // it's not then we need to open for append.
   if ( zstrcmpi( pchTargetName, g_szSqlDLLName ) != 0 )
   {
      zCHAR  szTime1[ 30 ];
      zCHAR  szTime2[ 30 ];
      zCHAR  szTemp[ zMAX_FILESPEC_LTH + 1 ];

      // Finish writing the previous makefile.
      fnCloseStaticSqlMakefile( vTaskLPLR, pchMakefileDir, szLine );

      hMakefile = SysOpenFile( vTZZOLODO, szFileName, COREFILE_WRITE );
      if ( hMakefile == -1 )
      {
         sprintf_s( szLine, zsizeof( szLine ), "Could not create file\n '%s'\n.Check Compiler "
                    "Specification for valid Makefile Directory", szFileName );
         MessageSend( vTaskLPLR, "LO00107", "Zeidon Tools",
                      szLine, zMSGQ_SYSTEM_ERROR, TRUE );
         goto EndOfFunction;
      }

      // Add the makefile to the list of files we must copy to the server.
      CreateEntity( vApSvDisO, "DS_TempFile", zPOS_FIRST );
      sprintf_s( szTemp, zsizeof( szTemp ), "%s.MAK", pchTargetName );
      SetAttributeFromString( vApSvDisO, "DS_TempFile", "LocalDirectory", pchMakefileDir );
      SetAttributeFromString( vApSvDisO, "DS_TempFile", "Name", szTemp );

      // Add stuff at the beginning.
      SysWriteLine( vTZZOLODO, hMakefile, "#" );
      sprintf_s( szLine, zsizeof( szLine ), "# %s.mak", pchTargetName );
      SysWriteLine( vTZZOLODO, hMakefile, szLine );
      SysWriteLine( vTZZOLODO, hMakefile, "#  Makefile for compiling DB2 static SQL" );
      SysGetDateTime( szTime1, zsizeof( szTime1 ) );
      UfFormatDateTime( szTime2, zsizeof( szTime2 ), szTime1, "DD-MM-YYYY HH:MI:SS" );
      sprintf_s( szLine, zsizeof( szLine ), "# Generated on %s", szTime2 );
      SysWriteLine( vTZZOLODO, hMakefile, szLine );
      SysWriteLine( vTZZOLODO, hMakefile, "#" );
      SysWriteLine( vTZZOLODO, hMakefile, " " );

      SysWriteLine( vTZZOLODO, hMakefile, "# Include makefile to set environment variables." );
      sprintf_s( szLine, zsizeof( szLine ), "!include \"%s\\zenv.hnm\"", pchMakefileDir );
      SysWriteLine( vTZZOLODO, hMakefile, szLine );
      SysWriteLine( vTZZOLODO, hMakefile, " " );

      sprintf_s( szLine, zsizeof( szLine ), "MODULE    = %s", pchTargetName );
      SysWriteLine( vTZZOLODO, hMakefile, szLine );
      GetAddrForAttribute( &pch, TZDBHDBO, "ApplA", "StaticSQL_C_FileDir" );
      sprintf_s( szLine, zsizeof( szLine ), "SRC_DIR   = %s", pch );
      SysWriteLine( vTZZOLODO, hMakefile, szLine );
      sprintf_s( szLine, zsizeof( szLine ), "OBJ_DIR   = %s", pch );
      SysWriteLine( vTZZOLODO, hMakefile, szLine );
      SysWriteLine( vTZZOLODO, hMakefile, " " );

      SysWriteLine( vTZZOLODO, hMakefile, "# The following is a list of all sub-modules that make up" );
      SysWriteLine( vTZZOLODO, hMakefile, "# the Target Executable." );
      SysWriteLine( vTZZOLODO, hMakefile, "OBJS = \\" );

      strcpy_s( g_szSqlDLLName, zsizeof( g_szSqlDLLName ), pchTargetName );

      // Add the batch file to the list of files we must copy to the server.
      CreateEntity( vApSvDisO, "DS_TempFile", zPOS_FIRST );
      sprintf_s( szFileName, zsizeof( szFileName ), "%s.BAT", pchTargetName );
      SetAttributeFromString( vApSvDisO, "DS_TempFile", "LocalDirectory", pchMakefileDir );
      SetAttributeFromString( vApSvDisO, "DS_TempFile", "Name", szFileName );

      // Open the batch file.
      sprintf_s( szFileName, zsizeof( szFileName ), "%s\\%s.BAT", pchMakefileDir, pchTargetName );
      hBatFile = SysOpenFile( vTZZOLODO, szFileName, COREFILE_WRITE );
      if ( hBatFile == -1 )
      {
         sprintf_s( szLine, zsizeof( szLine ), "Could not create file\n '%s'\n.Check Compiler "
                    "Specification for valid Makefile Directory", szFileName );
         MessageSend( vTaskLPLR, "LO00107", "Zeidon Tools",
                      szLine, zMSGQ_SYSTEM_ERROR, TRUE );
         goto EndOfFunction;
      }

      SysWriteLine( vTZZOLODO, hBatFile, "@echo off" );
      SysWriteLine( vTZZOLODO, hBatFile, "rem  Builds all .C files from .SQC files" );
      sprintf_s( szLine, zsizeof( szLine ), "rem Usage: %s.bat <db_name> <userid> <password>", pchTargetName );
      SysWriteLine( vTZZOLODO, hBatFile, szLine );
      SysWriteLine( vTZZOLODO, hBatFile, " " );
      SysWriteLine( vTZZOLODO, hBatFile, "rem  Connect to database." );
      SysWriteLine( vTZZOLODO, hBatFile, "db2 connect to %1 user %2 using %3" );
      SysWriteLine( vTZZOLODO, hBatFile, " " );
   }
   else
   {
      hMakefile = SysOpenFile( vTZZOLODO, szFileName, COREFILE_APPEND );
      if ( hMakefile == -1 )
      {
         sprintf_s( szLine, zsizeof( szLine ), "Could not re-open file\n '%s'.\nCheck Compiler "
                    "Specification for valid Makefile Directory", szFileName );
         MessageSend( vTaskLPLR, "LO00107", "Zeidon Tools",
                      szLine, zMSGQ_SYSTEM_ERROR, TRUE );
         goto EndOfFunction;
      }

      // Open the batch file.
      sprintf_s( szFileName, zsizeof( szFileName ), "%s\\%s.BAT", pchMakefileDir, pchTargetName );
      hBatFile = SysOpenFile( vTZZOLODO, szFileName, COREFILE_APPEND );
      if ( hBatFile == -1 )
      {
         sprintf_s( szLine, zsizeof( szLine ), "Could not re-open file\n '%s'.\nCheck Compiler "
                    "Specification for valid Makefile Directory", szFileName );
         MessageSend( vTaskLPLR, "LO00107", "Zeidon Tools",
                      szLine, zMSGQ_SYSTEM_ERROR, TRUE );
         goto EndOfFunction;
      }
   }

   // Now just add the LOD name to the makefile.
   GetAddrForAttribute( &pch, vApSvDisO, "DS_LOD", "Name" );
   sprintf_s( szLine, zsizeof( szLine ), "   $(OBJ_DIR)\\%s.obj \\", pch );
   SysWriteLine( vTZZOLODO, hMakefile, szLine );

   // Add the the LOD to the precompile/bind batch file.
   GetAddrForAttribute( &pchOutDir, TZDBHDBO, "ApplA", "StaticSQL_C_FileDir" );
   sprintf_s( szLine, zsizeof( szLine ), "db2 prep %s.SQC bindfile disconnect explicit output %s\\%s.c",
              pch, pchOutDir, pch );
   SysWriteLine( vTZZOLODO, hBatFile, szLine );
   sprintf_s( szLine, zsizeof( szLine ), "db2 bind %s.bnd", pch );
   SysWriteLine( vTZZOLODO, hBatFile, szLine );
   SysWriteLine( vTZZOLODO, hBatFile, " " );

   nReturn = 0;

EndOfFunction:

   if ( hMakefile != -1 )
      SysCloseFile( vTZZOLODO, hMakefile, 0 );

   if ( hBatFile != -1 )
      SysCloseFile( vTZZOLODO, hBatFile, 0 );

   return( nReturn );
}

zSHORT OPERATION
PostXOD_BuildHook( zVIEW vTZTEDBLO,
                   zVIEW vTZZOXODO,
                   zVIEW vTZZOLODO,
                   zVIEW vTZEREMDO_REF,
                   zVIEW vTZTENVRO_REF )
{
   zSHORT               nRC;
   zVIEW                vApSvDisO;
   DB2_ObjectDataRecord DB2_Data;

   zmemset( &DB2_Data, 0, sizeof( DB2_Data ) );

   // Check to see if the ApplA Server Distribution Object can be found.
   // If found then we might need to do some extra stuff.
   GetViewByName( &vApSvDisO, "ApplA_ApSvDisO", vTZTEDBLO, zLEVEL_TASK );
   if ( vApSvDisO )
   {
      nRC = fnProcessApplA( vApSvDisO, vTZZOLODO, vTZZOXODO, &DB2_Data );
      if ( nRC == zCALL_ERROR )
         return( zCALL_ERROR );
   }

   // We only want to store Blob data if we need to.
   if ( DB2_Data.bStoreDB2_Data )
      SetAttributeFromBlob( vTZZOXODO, "OBJECT", "DBH_Data",
                            &DB2_Data, sizeof( DB2_Data ) );

   return( 0 );

} // PostXOD_BuildHook

/*
   Following called from ApplA just before pushing application files to the
   data servers.

   Parameters:  bAllConfigurations - If TRUE then we are pushing to all
                     data server configurations.  If FALSE then we're only
                     pushing to the currently selected one.
*/
zSHORT OPERATION
InitDataServerConfigurationHook( zVIEW vApSvDisO,
                                 zBOOL bAllConfigurations )
{
   // Set global variable to keep track of the current SQL DLL name.  We'll
   // initialize it to null string. It is used to help build the makefile.
   *g_szSqlDLLName = 0;

   return( 0 );
}

/*
   Following called from ApplA just before pushing source files to the data
   servers but after the XODs have been built/sent.

   Finishes the static SQL makefiles created during XOD build.

   Parameters:  bAllConfigurations - If TRUE then we are pushing to all
                     data server configurations.  If FALSE then we're only
                     pushing to the currently selected one.
*/
zSHORT OPERATION
MidDataServerConfigurationHook( zVIEW vApSvDisO,
                                zBOOL bAllConfigurations )
{
   zCHAR  szLine[ 1000 ];
   zPCHAR pchMakefileDir;
   zVIEW  vTaskLPLR;

   GetViewByName( &vTaskLPLR, "TaskLPLR", vApSvDisO, zLEVEL_TASK );
   GetAddrForAttribute( &pchMakefileDir, vTaskLPLR, "Compiler", "MakefileDir" );

   // Finish writing the previous makefile.
   fnCloseStaticSqlMakefile( vTaskLPLR, pchMakefileDir, szLine );

   return( 0 );
}

#elif defined( ACCESS ) || defined( MYSQL ) || defined( ODBC ) || \
      defined( POSTGRESQL ) || defined( SQLSERVER )

/*

Sort the datafields in the XOD to put blob/varchar attributes last.

*/
zSHORT LOCALOPER
fnSortDataFields( zVIEW vTZZOXODO )
{
   zUSHORT usReturnLevel;
   zSHORT  nRC;
   zCHAR   szEntityName[ 33 ];
   zVIEW   vXOD;
   zVIEW   vXOD2;

   // If there is no DATARECORD for the root entity then there is nothing
   // to do (this LOD has no physical info).
   if ( CheckExistenceOfEntity( vTZZOXODO, "DATARECORD" ) != zCURSOR_SET )
      return( 0 );

   CreateViewFromViewForTask( &vTZZOXODO, vTZZOXODO, 0 );
   CreateViewFromViewForTask( &vXOD, vTZZOXODO, 0 );
   CreateViewFromViewForTask( &vXOD2, vTZZOXODO, 0 );

   // Initialize DATARECORD into szEntityName so that we reference the first ENTITY.
   strcpy_s( szEntityName, zsizeof( szEntityName ), "DATARECORD" );

   for ( nRC = DefineHierarchicalCursor( vTZZOXODO, "DATARECORD" );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntityHierarchical( &usReturnLevel, szEntityName, vTZZOXODO ) )
   {
      zLONG lPos;

      if ( nRC == zCURSOR_SET_RECURSIVECHILD )
         SetViewToSubobject( vTZZOXODO, "CHILDENTITY" );

      if ( zstrcmp( szEntityName, "DATARECORD" ) != 0 )
         continue;

      GetAbsolutePositionForEntity( &lPos, vTZZOXODO, "DATARECORD" );
      SetCursorAbsolutePosition( szEntityName, vXOD, lPos );

      // Move blob fields to the end.  We'll start at the end and go back
      // to the beginning. We'll skip the very last entity since it's already last.
      SetCursorLastEntity( vXOD, "DATAFIELD", 0 );
      nRC = SetCursorPrevEntity( vXOD, "DATAFIELD", 0 );
      while ( nRC >= zCURSOR_SET )
      {
         SetViewFromView( vXOD2, vXOD );
         nRC = SetCursorPrevEntity( vXOD, "DATAFIELD", 0 );

         if ( CompareAttributeToString( vXOD2, "DATAFIELD", "FLDTYPE", "V" ) == 0 ||
              CompareAttributeToString( vXOD2, "DATAFIELD", "FLDTYPE", "B" ) == 0 )
         {
            // Move current DATAFIELD to the end.
            MoveSubobject( vXOD2, "DATAFIELD", vXOD2, "DATAFIELD", zPOS_LAST, zREPOS_PREV );
         }
      }

      // Move Keys fields to the beginning.  We'll start at the end and go back
      // to the beginning. We'll skip the very first entity since it's already first.
      SetViewFromView( vXOD2, vXOD );
      SetCursorFirstEntity( vXOD, "DATAFIELD", 0 );
      nRC = SetCursorNextEntity( vXOD, "DATAFIELD", 0 );
      while ( nRC >= zCURSOR_SET )
      {
         // Find the correct ATTRIB entity.
         SetCursorFirstEntityByAttr( vXOD, "ATTRIB", "XVAATT_TOK", vXOD, "DATAFIELD", "XVAATT_TOK", 0 );

         SetViewFromView( vXOD2, vXOD );
         nRC = SetCursorNextEntity( vXOD, "DATAFIELD", 0 );

         // If the attribute is a key move it to the beginning.
         if ( CompareAttributeToString( vXOD2, "ATTRIB", "KEY", "Y" ) == 0 )
         {

            // Move current DATAFIELD to the beginning.
            MoveSubobject( vXOD2, "DATAFIELD", vXOD2, "DATAFIELD", zPOS_FIRST, zREPOS_NEXT );
         }
      }
   }

   DropHierarchicalCursor( vTZZOXODO );
   DropView( vXOD );
   DropView( vXOD2 );
   DropView( vTZZOXODO );

   return( 0 );
}

// Goes through the LOD recursively, setting DBMS information for each entity.
void LOCALOPER
fnSetEntityInformation( zVIEW vTZZOLODO, zVIEW vTZZOXODO, zLONG lDBMS_ZKey )
{
   zSHORT nRC;

   // First, make sure we've got an entity with DB information.
   if ( CheckExistenceOfEntity( vTZZOXODO, "DATARECORD" ) < zCURSOR_SET )
      return;

   // Find out if a POD_Entity exists for the DBMS.
   if ( SetCursorFirstEntityByInteger( vTZZOLODO, "TE_DBMS_SourceForEntity",
                                       "ZKey", lDBMS_ZKey, "LOD_EntityParent" ) == zCURSOR_SET )
   {
      // Got a POD_Entity.  Check the JOIN flag.
      if ( CompareAttributeToString( vTZZOLODO, "POD_Entity", "SQL_JoinWithParent", "Y" ) == 0 )
      {
         SetAttributeFromString( vTZZOXODO, "DATARECORD", "JOIN", "Y" );
      }
   }
   else
   if ( CheckExistenceOfEntity( vTZZOLODO, "ER_RelLinkRec" ) == zCURSOR_SET &&
        CompareAttributeToInteger( vTZZOLODO, "ER_RelLinkRec", "CardMax", 1 ) == 0 )
   {
      // Join is defaulted to Y if the entity has a x-to-1 relationship with its parent.
      SetAttributeFromString( vTZZOXODO, "DATARECORD", "JOIN", "Y" );
   }

   // Now do the same thing for any children.
   for ( nRC = SetCursorFirstEntity( vTZZOXODO, "CHILDENTITY", 0 );
         nRC >= zCURSOR_SET;
         nRC = SetCursorNextEntity( vTZZOXODO, "CHILDENTITY", 0 ) )
   {
      zLONG lER_EntTok;
      zLONG lER_RelTok;

      GetIntegerFromAttribute( &lER_EntTok, vTZZOXODO, "CHILDENTITY", "ERENT_TOK" );
      GetIntegerFromAttribute( &lER_RelTok, vTZZOXODO, "CHILDENTITY", "ERREL_TOK" );

      // Find a matching entity in the LOD.
      for ( nRC = SetCursorFirstEntity( vTZZOLODO, "LOD_EntityChild", 0 );
            nRC >= zCURSOR_SET;
            nRC = SetCursorNextEntity( vTZZOLODO, "LOD_EntityChild", 0 ) )
      {
         SetViewToSubobject( vTZZOLODO, "LOD_EntityChild" );

         if ( CheckExistenceOfEntity( vTZZOLODO, "ER_EntityRec" ) == zCURSOR_SET &&
              CompareAttributeToInteger( vTZZOLODO, "ER_EntityRec", "ZKey", lER_EntTok ) == 0 &&
              CheckExistenceOfEntity( vTZZOLODO, "ER_RelLinkRec" ) == zCURSOR_SET &&
              CompareAttributeToInteger( vTZZOLODO, "ER_RelLinkRec", "ZKey", lER_EntTok ) == 0 )
         {
            // We found the child entity that matches the CHILDENTITY in the XOD.  Stop 'for' loop.
            break;
         }

         // That wasn't the right child so reset the subobject.
         ResetViewFromSubobject( vTZZOLODO );
      }

      // Once we get here, "LOD_EntityParent" should match "CHILDENTITY".
      // Move "CHILDENTITY" up and call ourselves recursively.
      SetViewToSubobject( vTZZOXODO, "CHILDENTITY" );
      fnSetEntityInformation( vTZZOLODO, vTZZOXODO, lDBMS_ZKey );

      // Now reset the cursors.
      ResetViewFromSubobject( vTZZOLODO );
      ResetViewFromSubobject( vTZZOXODO );
   }

}

/*

   This function called once after the XOD has been built but before it is
   written.

*/
zSHORT OPERATION
PostXOD_BuildHook( zVIEW vTZTEDBLO,
                   zVIEW vTZZOXODO,
                   zVIEW vTZZOLODO,
                   zVIEW vTZEREMDO_REF,
                   zVIEW vTZTENVRO_REF )
{
   zCHAR szObjectName[ zZEIDON_NAME_LTH + 1 ];
   zVIEW vOI;

   // See if there is a blob stored in DBH_Data for the TE.
   SetOI_FromBlob( &vOI, szObjectName, vTZZOXODO, vTZTENVRO_REF,
                   "TE_DBMS_Source", "DBH_Data", zMULTIPLE );

   if ( vOI == 0 )
       // No blob in the TE.  Get it from the DB list object.
      SetOI_FromBlob( &vOI, szObjectName, vTZZOXODO, vTZTEDBLO,
                      "TE_DBMS_Source", "DBH_Data", zMULTIPLE );

   if ( vOI == 0 )
   {
      return( 0 );

      // DGC 2015-01-07 Removed the following code and just return 0 because this
      // stuff is never used by the JOE and so it's not an error.
#if 0
      // KJS - 08/22/12 - This is being put in because we were getting an 'Invalid View' error on the DropView( vOI ) if
      // a 'Set DBH' hadn't been done on the data source and the db handler was PostgreSQL since TZDBHODO was not ever set.
      // Not actually sure if this is much of an error (should I just put the DropView in the below "If") or if there could
      // be problems if TZDBHODO is not a valid view.
      MessageSend( vTZZOXODO, "PostXOD_BuildHook", "Zeidon Tools",
                   "You need to do a 'Set DBH' for this data source before building the xods.", zMSGQ_SYSTEM_ERROR, TRUE );
      TraceLineS( "*** PostXOD_BuildHook TZDBHODO does not exist. ", "" );
      return( zCALL_ERROR );
#endif
   }

   // Check for ODBC object.
   if ( zstrcmp( szObjectName, "TZDBHODO" ) == 0 )
   {
      zLONG                 lDBMS_ZKey;
      ODBC_ObjectDataRecord sData;

      // For ODBC databases we need to sort the DataFields so that the VarChar
      // fields come last in each table.  We also need to put keys first.
      fnSortDataFields( vTZZOXODO );

      // Set-up ODBC-specific information.
      zmemset( &sData, 0, sizeof( sData ) );
      GetIntegerFromAttribute( &sData.nTimestampPrecision,
                               vOI, "ODBC", "TimestampPrecision" );
      sData.bStoreTimestampAsString = (CompareAttributeToString( vOI, "ODBC", "TimestampAsString", "Y" ) == 0);

      SetAttributeFromBlob( vTZZOXODO, "OBJECT", "DBH_Data", (zPVOID) &sData, sizeof( sData ) );

      // Go through the LOD and set dbh-specific information for each entity.
      ResetView( vTZZOLODO );
      ResetView( vTZZOXODO );

      // Set the cursor to the first non-hidden entity.
      SetCursorFirstEntity( vTZZOXODO, "OBJECT", 0 );

      GetIntegerFromAttribute( &lDBMS_ZKey, vTZTENVRO_REF, "TE_DBMS_Source", "ZKey" );
      fnSetEntityInformation( vTZZOLODO, vTZZOXODO, lDBMS_ZKey );
   }

   DropView( vOI );

   return( 0 );

} // PostXOD_BuildHook

#endif

// The following function removes brackets from entity- and/or
// attributenames
static void
RemoveBrackets( zPCHAR pch )
{
   zPCHAR pchKlammer;

   pchKlammer = strchr( pch, '[' );
   if ( pchKlammer )
   {
      // Klammern [] wegnehmen.
      while ( *(pchKlammer + 1) != ']' && *(pchKlammer + 1) )
      {
         *pchKlammer = *(pchKlammer + 1);
         pchKlammer++;
      }

      *pchKlammer = 0;
   }

} // RemoveBrackets
