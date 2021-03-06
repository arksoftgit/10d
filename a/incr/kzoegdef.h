#ifndef __kzoegdef_h      // Sentry, use file only if it's not already included
   #define __kzoegdef_h
#else
   #undef  mGLOBAL_DECLARE
   #undef  zEXTERN
#endif   // __kzoegdef_h sentry.

#ifdef zGLOBAL_DATA
#define mGLOBAL_DECLARE( type, variable, value )  type  variable = value
#define zEXTERN
//#pragma message("after kzoegdef.h ---> zEXTERN is ''")
#else
#define mGLOBAL_DECLARE( type, variable, value )  extern  type  variable
#define zEXTERN extern
//#pragma message("after kzoegdef.h ===> " VAR_NAME_VALUE(zEXTERN))
#endif
