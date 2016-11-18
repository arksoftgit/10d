#define KZSYSSVC_INCL
#include "KZOENGAA.H" 
#include "TZVMLIP.H" 
#include "ZDRVROPR.H" 
 
#ifdef __cplusplus
extern "C"
{
#endif
 
#include "ZEIDONOP.H"

//:GLOBAL OPERATION
//:BuildMainNavSection( VIEW vDialog,
//:                     VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                     INTEGER lFile )

//:   STRING ( 10000 ) szWriteBuffer
zOPER_EXPORT zSHORT OPERATION
BuildMainNavSection( zVIEW     vDialog,
                     zVIEW     vDialogRoot,
                     zLONG     lFile )
{
   zCHAR     szWriteBuffer[ 10001 ] = { 0 }; 
   //:STRING ( 50 )    szNavigationTitle
   zCHAR     szNavigationTitle[ 51 ] = { 0 }; 
   //:STRING ( 256 )   szHTML_Address
   zCHAR     szHTML_Address[ 257 ] = { 0 }; 
   //:STRING ( 256 )   szHTML5Attr
   zCHAR     szHTML5Attr[ 257 ] = { 0 }; 
   //:STRING ( 256 )   szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 50 )    szDialogName
   zCHAR     szDialogName[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szMenuName
   zCHAR     szMenuName[ 51 ] = { 0 }; 
   //:STRING ( 34 )    szActionName
   zCHAR     szActionName[ 35 ] = { 0 }; 
   //:STRING ( 1 )     szWindowIsjMobile
   zCHAR     szWindowIsjMobile[ 2 ] = { 0 }; 
   //:INTEGER          ActionType
   zLONG     ActionType = 0; 
   //:SHORT            nRC
   zSHORT    nRC = 0; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_0[ 255 ]; 
   zCHAR     szTempString_1[ 255 ]; 
   zSHORT    RESULT; 
   zCHAR     szTempString_2[ 255 ]; 
   zCHAR     szTempString_3[ 255 ]; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_4[ 33 ]; 
   zSHORT    lTempInteger_2; 
   zLONG     lTempInteger_3; 


   //:IF vDialog.WndStyle.Tag = "jMobile Window"
   if ( CompareAttributeToString( vDialog, "WndStyle", "Tag", "jMobile Window" ) == 0 )
   { 
      //:szWindowIsjMobile = "Y"
      ZeidonStringCopy( szWindowIsjMobile, 1, 0, "Y", 1, 0, 2 );
      //:ELSE
   } 
   else
   { 
      //:szWindowIsjMobile = ""
      ZeidonStringCopy( szWindowIsjMobile, 1, 0, "", 1, 0, 2 );
   } 

   //:END      

   //:// MAIN NAVIGATION BAR

   //:szWriteBuffer = "<!-- Main Navigation *********************** -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- Main Navigation *********************** -->", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //:IF vDialogRoot.Menu EXISTS 
   lTempInteger_0 = CheckExistenceOfEntity( vDialogRoot, "Menu" );
   if ( lTempInteger_0 == 0 )
   { 
      //:szMenuName = vDialogRoot.Menu.Tag 
      GetVariableFromAttribute( szMenuName, 0, 'S', 51, vDialogRoot, "Menu", "Tag", "", 0 );
      //:IF vDialogRoot.Menu.CSS_Class != ""
      if ( CompareAttributeToString( vDialogRoot, "Menu", "CSS_Class", "" ) != 0 )
      { 
         //:szClass = " class=^" + vDialogRoot.Menu.CSS_Class + "^ " 
         GetVariableFromAttribute( szTempString_0, 0, 'S', 255, vDialogRoot, "Menu", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_0, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
      } 

      //:END
   } 

   //:END

   //:// KJS 02/23/16 - We have added a field for HTML5 attributes (this could be for jQuery Mobile or whatever extra attributes we want).
   //:// It is simply a string and we will add it to different controls like <div> or <input> etc.
   //:szHTML5Attr = ""
   ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
   //:IF vDialogRoot.Menu.WebHTML5Attribute != ""
   if ( CompareAttributeToString( vDialogRoot, "Menu", "WebHTML5Attribute", "" ) != 0 )
   { 
      //:szHTML5Attr = " " + vDialogRoot.Menu.WebHTML5Attribute + " "
      GetVariableFromAttribute( szTempString_1, 0, 'S', 255, vDialogRoot, "Menu", "WebHTML5Attribute", "", 0 );
      ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_1, 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
   } 

   //:END
   //:  
   //:IF szWindowIsjMobile = "Y"
   if ( ZeidonStringCompare( szWindowIsjMobile, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "<div data-role=^navbar^ id=^div" + szMenuName + "^ " + szClass + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div data-role=^navbar^ id=^div", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      //:ELSE 
   } 
   else
   { 
      //:szWriteBuffer = "<div id=^mainnavigation^" + szHTML5Attr + szClass + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^mainnavigation^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   } 

   //:END
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //://szWriteBuffer = "   <ul id=^" + szMenuName + "^ name=^" + szMenuName + "^" + szClass + ">"
   //:szWriteBuffer = "   <ul id=^" + szMenuName + "^ name=^" + szMenuName + "^" + szHTML5Attr + " >"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <ul id=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " >", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );

   //:FOR EACH vDialogRoot.OptAct WITHIN vDialogRoot.Menu
   RESULT = SetCursorFirstEntity( vDialogRoot, "OptAct", "Menu" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:szNavigationTitle = vDialogRoot.Option.Text
      GetVariableFromAttribute( szNavigationTitle, 0, 'S', 51, vDialogRoot, "Option", "Text", "", 0 );
      //:szDialogName = vDialogRoot.OptAct.DialogName
      GetVariableFromAttribute( szDialogName, 0, 'S', 51, vDialogRoot, "OptAct", "DialogName", "", 0 );
      //:IF szDialogName = ""
      if ( ZeidonStringCompare( szDialogName, 1, 0, "", 1, 0, 51 ) == 0 )
      { 
         //:szDialogName = "NoDialogName"
         ZeidonStringCopy( szDialogName, 1, 0, "NoDialogName", 1, 0, 51 );
      } 

      //:END

      //:IF vDialogRoot.Option.CSS_Class != ""
      if ( CompareAttributeToString( vDialogRoot, "Option", "CSS_Class", "" ) != 0 )
      { 
         //:szClass = " class=^" + vDialogRoot.Option.CSS_Class + "^ "
         GetVariableFromAttribute( szTempString_2, 0, 'S', 255, vDialogRoot, "Option", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_2, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:szClass = ""
         ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
      } 

      //:END

      //:// KJS 02/23/16 - We have added a field for HTML5 attributes (this could be for jQuery Mobile or whatever extra attributes we want).
      //:// It is simply a string and we will add it to different controls like <div> or <input> etc.
      //:szHTML5Attr = ""
      ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
      //:IF vDialogRoot.Option.WebHTML5Attribute != ""
      if ( CompareAttributeToString( vDialogRoot, "Option", "WebHTML5Attribute", "" ) != 0 )
      { 
         //:szHTML5Attr = " " + vDialogRoot.Option.WebHTML5Attribute + " "
         GetVariableFromAttribute( szTempString_3, 0, 'S', 255, vDialogRoot, "Option", "WebHTML5Attribute", "", 0 );
         ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
         ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_3, 1, 0, 257 );
         ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
      } 

      //:END

      //:IF vDialogRoot.OptAct EXISTS
      lTempInteger_1 = CheckExistenceOfEntity( vDialogRoot, "OptAct" );
      if ( lTempInteger_1 == 0 )
      { 
         //://Because the menu actions can be created on separate windows from the control
         //://actions, we need to make sure these actions are unique.  We will prefix a
         //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
         //:szActionName = "m" + vDialogRoot.OptAct.Tag
         GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialogRoot, "OptAct", "Tag", "", 0 );
         ZeidonStringCopy( szActionName, 1, 0, "m", 1, 0, 35 );
         ZeidonStringConcat( szActionName, 1, 0, szTempString_4, 1, 0, 35 );
         //:ActionType = vDialogRoot.OptAct.Type
         GetIntegerFromAttribute( &ActionType, vDialogRoot, "OptAct", "Type" );
         //:ELSE
      } 
      else
      { 
         //:szActionName = ""
         ZeidonStringCopy( szActionName, 1, 0, "", 1, 0, 35 );
         //:ActionType = 0
         ActionType = 0;
      } 

      //:END

      //:IF ActionType = zWAB_LinkToHTML_Address
      if ( ActionType == zWAB_LinkToHTML_Address )
      { 
         //:szHTML_Address = ""
         ZeidonStringCopy( szHTML_Address, 1, 0, "", 1, 0, 257 );
         //:IF vDialogRoot.OptAct EXISTS
         lTempInteger_2 = CheckExistenceOfEntity( vDialogRoot, "OptAct" );
         if ( lTempInteger_2 == 0 )
         { 
            //:SET CURSOR FIRST vDialogRoot.Action WHERE vDialogRoot.Action.ZKey = vDialogRoot.OptAct.ZKey
            GetIntegerFromAttribute( &lTempInteger_3, vDialogRoot, "OptAct", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( vDialogRoot, "Action", "ZKey", lTempInteger_3, "" );
            //:szHTML_Address = vDialogRoot.Action.WebHTML_TransferAddress
            GetVariableFromAttribute( szHTML_Address, 0, 'S', 257, vDialogRoot, "Action", "WebHTML_TransferAddress", "", 0 );
         } 

         //:END
         //:szWriteBuffer = "       <li id=^l" + szActionName + "^ name=^l" + szActionName + "^ " + szHTML5Attr + szClass + "><a href=^" + szHTML_Address + "^ target=^_blank^>" + szNavigationTitle + "</a></li>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "       <li id=^l", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^l", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "><a href=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML_Address, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ target=^_blank^>", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szNavigationTitle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</a></li>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:// Regular Action
         //:// I know in the case of jMobile, we want the class and szHTML5Attr to be on the <a href not the <li. So I am going to change that in this instance...
         //:IF szWindowIsjMobile = "Y"
         if ( ZeidonStringCompare( szWindowIsjMobile, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:szWriteBuffer = "       <li id=^l" + szActionName + "^ name=^l" + szActionName + "^ ><a href=^#^ " + szHTML5Attr + szClass + " onclick=^" + szActionName + "()^>" + szNavigationTitle + "</a></li>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "       <li id=^l", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^l", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ><a href=^#^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "()^>", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szNavigationTitle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</a></li>", 1, 0, 10001 );
            //:ELSE 
         } 
         else
         { 
            //:szWriteBuffer = "       <li id=^l" + szActionName + "^ name=^l" + szActionName + "^ " + szHTML5Attr + szClass + "><a href=^#^ onclick=^" + szActionName + "()^>" + szNavigationTitle + "</a></li>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "       <li id=^l", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^l", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "><a href=^#^ onclick=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "()^>", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szNavigationTitle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</a></li>", 1, 0, 10001 );
         } 

         //:END
      } 

      //:END
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      RESULT = SetCursorNextEntity( vDialogRoot, "OptAct", "Menu" );
   } 

   //:END

   //:// Division ending for Navigation Bar
   //:szWriteBuffer = "   </ul>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   </ul>", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "</div>  <!-- end Navigation Bar -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- end Navigation Bar -->", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );

   //:// Include the banner at the bottom of the menu options.
   //://szWriteBuffer = "<div class=^noprint^>"
   //://WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   //:IF szWindowIsjMobile = ""
   if ( ZeidonStringCompare( szWindowIsjMobile, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "<%@include file=^./include/topmenuend.inc^ %>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@include file=^./include/topmenuend.inc^ %>", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   } 

   //:END
   return( 0 );
//    // KJS 07/31/08 - I am taking out the following inc file.  I am
//    // currently thinking that anything in this inc file could simply
//    // be put in topmenuend.inc and that might seem a little simpler.
//    // Not sure...
//    //szWriteBuffer = "<%@include file=^Left_Nav_Background.inc^ %>"
//    //WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
//    //szWriteBuffer = "</div>"
//    //WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteJPG( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                INTEGER          lFile,
//:                STRING ( 10000 ) szWriteBuffer,
//:                STRING ( 50 )    szIndent,
//:                STRING ( 32 )    szCtrlTag,
//:                STRING ( 1 )     szNoPositioning,
//:                INTEGER          lOffsetX,
//:                INTEGER          lOffsetY )

//:   // Format a BITMAP or JPG control.

//:   STRING ( 32 )  szContextName
zOPER_EXPORT zVOID OPERATION
GenJSP_CrteJPG( zVIEW     vDialog,
                zLONG     lFile,
                zPCHAR    szWriteBuffer,
                zPCHAR    szIndent,
                zPCHAR    szCtrlTag,
                zPCHAR    szNoPositioning,
                zLONG     lOffsetX,
                zLONG     lOffsetY )
{
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szText
   zCHAR     szText[ 257 ] = { 0 }; 
   //:STRING ( 32 )  szActionName
   zCHAR     szActionName[ 33 ] = { 0 }; 
   //:INTEGER        nRC
   zLONG     nRC = 0; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_0[ 255 ]; 
   zCHAR     szTempString_1[ 255 ]; 
   zSHORT    RESULT; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 261 ]; 
   zCHAR     szTempString_11[ 261 ]; 


   //:CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );

   //:// If this window is being generated with no positioning then
   //:// do not create the position in the style.
   //:IF  szNoPositioning = "Y"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:CreateNoPosStyleString( vDialog, szStyle, "" )
      CreateNoPosStyleString( vDialog, szStyle, "" );
      //:ELSE
   } 
   else
   { 
      //:CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
      CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" );
   } 

   //:END

   //://CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
   //:szStyle = szStyle + szTabIndex
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );

   //:szActionName = ""
   ZeidonStringCopy( szActionName, 1, 0, "", 1, 0, 33 );
   //:IF vDialog.EventAct EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( vDialog, "EventAct" );
   if ( lTempInteger_0 == 0 )
   { 
      //:szActionName = vDialog.EventAct.Tag
      GetVariableFromAttribute( szActionName, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
      //:nRC = zstrcmpi( szActionName, "alt-f4" )
      nRC = zstrcmpi( szActionName, "alt-f4" );
      //:IF nRC = 0
      if ( nRC == 0 )
      { 
         //:szActionName = "AltF4"
         ZeidonStringCopy( szActionName, 1, 0, "AltF4", 1, 0, 33 );
      } 

      //:END
   } 

   //:END

   //:szClass = ""
   ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
   //:IF vDialog.Control.CSS_Class != ""
   if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) != 0 )
   { 
      //:szClass = " class=^" + vDialog.Control.CSS_Class + "^ "
      GetVariableFromAttribute( szTempString_0, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, szTempString_0, 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //://If we put a title on the control, when the mouse is hovered over the control, this text will display.
   //:szTitleHTML = ""
   ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
   //:szTitle = vDialog.Control.DIL_Text
   GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
   //:IF szTitle != ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
   { 
      //:szTitleHTML = " title=^" + szTitle + "^ "
      ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END
   //:szText = ""
   ZeidonStringCopy( szText, 1, 0, "", 1, 0, 257 );
   //:IF  vDialog.Control.Text != ""
   if ( CompareAttributeToString( vDialog, "Control", "Text", "" ) != 0 )
   { 
      //:szText = " alt=^" + vDialog.Control.Text + "^ "
      GetVariableFromAttribute( szTempString_1, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
      ZeidonStringCopy( szText, 1, 0, " alt=^", 1, 0, 257 );
      ZeidonStringConcat( szText, 1, 0, szTempString_1, 1, 0, 257 );
      ZeidonStringConcat( szText, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //://There might be mapping for this control which means we should get the
   //://image from the mapping, or there might be an image file name, so we wouldn't
   //://use the mapping.
   //:SET CURSOR FIRST vDialog.CtrlMapLOD_Attribute WITHIN vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "CtrlMapLOD_Attribute", "Control" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 

      //:szWriteBuffer = "<% strErrorMapValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<% strErrorMapValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name +
      //:                ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name + "^, vAppSubtask );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( nRC <= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC <= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name +
      //:         ".TraceLine( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".CheckExistenceOfEntity( strSessionId, ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         strErrorMapValue = " +
      //:                vDialog.CtrlMapView.Name +
      //:                ".GetStringFromAttributeByContext( strSessionId, ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^, ^" +
      //:                szContextName + "^, 2000 );"
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 2000 );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:IF  szActionName = ""
      if ( ZeidonStringCompare( szActionName, 1, 0, "", 1, 0, 33 ) == 0 )
      { 
         //:szWriteBuffer = "<img src=^<%=strErrorMapValue%>^ " + szStyle + szTitleHTML + szClass + szText + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<img src=^<%=strErrorMapValue%>^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "<img src=^<%=strErrorMapValue%>^ onclick=^" + szActionName + "()^ " + szStyle + szTitleHTML + szClass + szText + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<img src=^<%=strErrorMapValue%>^ onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "()^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      } 

      //:END
      //:ELSE
   } 
   else
   { 
      //://Not getting image from mapping, a file name has been specified.
      //:IF vDialog.Control.WebFileName != ""
      if ( CompareAttributeToString( vDialog, "Control", "WebFileName", "" ) != 0 )
      { 
         //:IF szActionName = ""
         if ( ZeidonStringCompare( szActionName, 1, 0, "", 1, 0, 33 ) == 0 )
         { 
            //://szWriteBuffer = "<a href=^#^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ ><img src=^" +
            //://   vDialog.Control.WebFileName + "^ " + szStyle + szTitleHTML + "></a>"
            //:szWriteBuffer = "<img src=^" + vDialog.Control.WebFileName + "^  name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " +
            //:                  szStyle + szTitleHTML + szClass + szText + ">"
            GetVariableFromAttribute( szTempString_10, 0, 'S', 261, vDialog, "Control", "WebFileName", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<img src=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^  name=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "<img src=^" + vDialog.Control.WebFileName + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ onclick=^" +
            //:                szActionName + "( )^ " + szStyle + szTitleHTML + szClass + szText + ">"
            GetVariableFromAttribute( szTempString_11, 0, 'S', 261, vDialog, "Control", "WebFileName", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<img src=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ onclick=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         } 

         //:   //szWriteBuffer = "<a href=^#^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ ^onclick=^" +
         //:   //                szActionName + "( )^><img src=^" + vDialog.Control.WebFileName + "^ " + szStyle + szTitleHTML + "></a>"
         //:END
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         //:ELSE
      } 
      else
      { 
         //://Neither mapping nor filename was specified.
         //:szWriteBuffer = "//There was no information on where to get the image.  Nothing created."
         ZeidonStringCopy( szWriteBuffer, 1, 0, "//There was no information on where to get the image.  Nothing created.", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      } 

      //:END
   } 

   //:END
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSP_ChildFunctions( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                       INTEGER          lFile,
//:                       STRING ( 10000 ) szWriteBuffer,
//:                       STRING ( 255 )   szFormName )

//:   STRING ( 50 ) szCtrlTag
zOPER_EXPORT zVOID OPERATION
GenJSP_ChildFunctions( zVIEW     vDialog,
                       zLONG     lFile,
                       zPCHAR    szWriteBuffer,
                       zPCHAR    szFormName )
{
   zCHAR     szCtrlTag[ 51 ] = { 0 }; 

   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteGroupTable(  VIEW vDialog BASED ON LOD TZWDLGSO,
//:                        VIEW vGroupParent BASED ON LOD TZWDLGSO,
//:                        VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                        INTEGER          lFile,
//:                        STRING ( 10000 ) szWriteBuffer,
//:                        STRING ( 100 )   szIndent,
//:                        INTEGER          lTableRowCnt,
//:                        STRING ( 1 )     szNoPositioning )

//:   INTEGER        X_Size
zOPER_EXPORT zVOID OPERATION
GenJSP_CrteGroupTable( zVIEW     vDialog,
                       zVIEW     vGroupParent,
                       zVIEW     vDialogRoot,
                       zLONG     lFile,
                       zPCHAR    szWriteBuffer,
                       zPCHAR    szIndent,
                       zLONG     lTableRowCnt,
                       zPCHAR    szNoPositioning )
{
   zLONG     X_Size = 0; 
   //:INTEGER        Y_Size
   zLONG     Y_Size = 0; 
   //:INTEGER        X_Pos
   zLONG     X_Pos = 0; 
   //:INTEGER        Y_Pos
   zLONG     Y_Pos = 0; 
   //:INTEGER        LastY_Pos
   zLONG     LastY_Pos = 0; 
   //:INTEGER        iHighestColCnt
   zLONG     iHighestColCnt = 0; 
   //:INTEGER        iColCnt
   zLONG     iColCnt = 0; 
   //:INTEGER        nRC
   zLONG     nRC = 0; 
   //:INTEGER        iColWidth
   zLONG     iColWidth = 0; 
   //:INTEGER        lMaxStringLth
   zLONG     lMaxStringLth = 0; 
   //:INTEGER        lTemp
   zLONG     lTemp = 0; 
   //:INTEGER        lStyleX
   zLONG     lStyleX = 0; 
   //:INTEGER        Size
   zLONG     Size = 0; 
   //:INTEGER        lOffsetX
   zLONG     lOffsetX = 0; 
   //:INTEGER        lOffsetY
   zLONG     lOffsetY = 0; 
   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   //:STRING ( 10 )  szColCnt
   zCHAR     szColCnt[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szWidth
   zCHAR     szWidth[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szHeight
   zCHAR     szHeight[ 11 ] = { 0 }; 
   //:STRING ( 50 )  szCtrlTag
   zCHAR     szCtrlTag[ 51 ] = { 0 }; 
   //:STRING ( 50 )  szParentCtrlTag
   zCHAR     szParentCtrlTag[ 51 ] = { 0 }; 
   //:STRING ( 85 )  szHTMLCtrlID
   zCHAR     szHTMLCtrlID[ 86 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 32 )  szActionName
   zCHAR     szActionName[ 33 ] = { 0 }; 
   //:STRING ( 50 )  szControlType
   zCHAR     szControlType[ 51 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 256 ) szText
   zCHAR     szText[ 257 ] = { 0 }; 
   //:STRING ( 32 )  szContextName
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLth
   zCHAR     szMaxStringLth[ 11 ] = { 0 }; 
   //:STRING ( 32 )  szSize
   zCHAR     szSize[ 33 ] = { 0 }; 
   //:STRING ( 256 ) szAbsoluteStyle
   zCHAR     szAbsoluteStyle[ 257 ] = { 0 }; 

   //:STRING ( 1 )   szNoHeightFlag
   zCHAR     szNoHeightFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szNoWidthFlag
   zCHAR     szNoWidthFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szSpanFlag
   zCHAR     szSpanFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szDivFlag
   zCHAR     szDivFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szScrollableFlag
   zCHAR     szScrollableFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szScrollingTable
   zCHAR     szScrollingTable[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szGroupIsTable
   zCHAR     szGroupIsTable[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szTinyMCEFlag
   zCHAR     szTinyMCEFlag[ 2 ] = { 0 }; 
   //:STRING ( 100 ) szIndentGroup
   zCHAR     szIndentGroup[ 101 ] = { 0 }; 
   //:STRING ( 50 )  szWebCtrlType
   zCHAR     szWebCtrlType[ 51 ] = { 0 }; 
   zCHAR     szTempString_0[ 255 ]; 
   zSHORT    lTempInteger_0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zCHAR     szTempString_1[ 255 ]; 
   zLONG     lTempInteger_3; 
   zLONG     lTempInteger_4; 
   zLONG     lTempInteger_5; 
   zLONG     lTempInteger_6; 
   zCHAR     szTempString_2[ 255 ]; 
   zSHORT    lTempInteger_7; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 255 ]; 
   zSHORT    lTempInteger_8; 
   zCHAR     szTempString_12[ 255 ]; 
   zCHAR     szTempString_13[ 33 ]; 
   zCHAR     szTempString_14[ 33 ]; 
   zCHAR     szTempString_15[ 33 ]; 
   zCHAR     szTempString_16[ 33 ]; 
   zCHAR     szTempString_17[ 33 ]; 
   zSHORT    lTempInteger_9; 
   zCHAR     szTempString_18[ 33 ]; 
   zCHAR     szTempString_19[ 33 ]; 
   zCHAR     szTempString_20[ 33 ]; 
   zCHAR     szTempString_21[ 255 ]; 


   //:LastY_Pos = 0
   LastY_Pos = 0;
   //:iColCnt = 0
   iColCnt = 0;
   //:iHighestColCnt = 0
   iHighestColCnt = 0;
   //:szIndent = szIndent + "   "
   ZeidonStringConcat( szIndent, 1, 0, "   ", 1, 0, 101 );

   //:X_Size  = vGroupParent.Control.SZDLG_X
   GetIntegerFromAttribute( &X_Size, vGroupParent, "Control", "SZDLG_X" );
   //:Y_Size  = vGroupParent.Control.SZDLG_Y
   GetIntegerFromAttribute( &Y_Size, vGroupParent, "Control", "SZDLG_Y" );
   //:szParentCtrlTag = vGroupParent.Control.Tag
   GetVariableFromAttribute( szParentCtrlTag, 0, 'S', 51, vGroupParent, "Control", "Tag", "", 0 );

   //:IF vGroupParent.Control.CSS_Class != ""
   if ( CompareAttributeToString( vGroupParent, "Control", "CSS_Class", "" ) != 0 )
   { 
      //:szClass = " class=^" + vGroupParent.Control.CSS_Class + "^"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 255, vGroupParent, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, szTempString_0, 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
      //:ELSE
   } 
   else
   { 
      //:szClass = ""
      ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
   } 

   //:END

   //:IF  vDialog.Control EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( vDialog, "Control" );
   if ( lTempInteger_0 == 0 )
   { 
      //:SET CURSOR  FIRST vDialog.Control
      RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
      //:LastY_Pos = vDialog.Control.PSDLG_Y
      GetIntegerFromAttribute( &LastY_Pos, vDialog, "Control", "PSDLG_Y" );
   } 

   //:END

   //:// Loop through each Control within this group.  Determine what row has the largest
   //:// number of controls.  This will determine how many columns our table will have.
   //:FOR EACH vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 

      //:IF  LastY_Pos < vDialog.Control.PSDLG_Y
      if ( CompareAttributeToInteger( vDialog, "Control", "PSDLG_Y", LastY_Pos ) > 0 )
      { 

         //:IF  iColCnt > iHighestColCnt
         if ( iColCnt > iHighestColCnt )
         { 
            //:iHighestColCnt = iColCnt
            iHighestColCnt = iColCnt;
         } 

         //:END
         //:iColCnt = 0
         iColCnt = 0;
      } 

      //:END

      //:iColCnt = iColCnt + 1
      iColCnt = iColCnt + 1;

      //:LastY_Pos = vDialog.Control.PSDLG_Y
      GetIntegerFromAttribute( &LastY_Pos, vDialog, "Control", "PSDLG_Y" );
      RESULT = SetCursorNextEntity( vDialog, "Control", "" );
   } 

   //:END

   //://TraceLineI("**** Highest Col Count *** ", iHighestColCnt )
   //:zIntegerToString( szColCnt, 10, iHighestColCnt )
   zIntegerToString( szColCnt, 10, iHighestColCnt );
   //:PIX_PER_DU( vDialog, dDLUnits )
   PIX_PER_DU( vDialog, &dDLUnits );
   //:zIntegerToString( szWidth, 10, X_Size * dDLUnits )
   zIntegerToString( szWidth, 10, X_Size * dDLUnits );
   //:zIntegerToString( szHeight, 10, Y_Size * dDLUnits )
   zIntegerToString( szHeight, 10, Y_Size * dDLUnits );

   //:// 05/27/09 - Currently, we never put in a height.  Would we want to do this?????!!!.
   //:IF  szNoPositioning = "Y"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 

      //:szNoWidthFlag = ""
      ZeidonStringCopy( szNoWidthFlag, 1, 0, "", 1, 0, 2 );
      //:SET CURSOR FIRST vGroupParent.WebControlProperty WHERE vGroupParent.WebControlProperty.Name = "No Width"
      RESULT = SetCursorFirstEntityByString( vGroupParent, "WebControlProperty", "Name", "No Width", "" );
      //:IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:szNoWidthFlag = "Y"
         ZeidonStringCopy( szNoWidthFlag, 1, 0, "Y", 1, 0, 2 );
      } 

      //:END
   } 

   //:END

   //:// Create a div around the whole table.  This should probably be float.
   //://szWriteBuffer = "<div style=^float:left;width:" + szWidth + "px;height:" + szHeight + "px;^" + szClass + ">"
   //:// KJS 09/11/09 - Neither the table or the div had an id or name.  I am not sure whether I should put the
   //:// id on the <table we create or on the <div> but I will put it on the div.
   //:szWriteBuffer = "<div id=^" + szParentCtrlTag + "^ name=^" + szParentCtrlTag + "^ style=^float:left;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szParentCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szParentCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ style=^float:left;", 1, 0, 10001 );
   //:IF szNoWidthFlag = ""
   if ( ZeidonStringCompare( szNoWidthFlag, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = szWriteBuffer + "width:" + szWidth + "px;"
      ZeidonStringConcat( szWriteBuffer, 1, 0, "width:", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "px;", 1, 0, 10001 );
   } 

   //:END
   //:szWriteBuffer = szWriteBuffer + "^ " + szClass + ">"
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:// Now create the table with the proper number of columns.
   //://szWriteBuffer = "<table cols=" szColCount + " name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^>"
   //:szWriteBuffer = "<table cols=" + szColCnt
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<table cols=", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szColCnt, 1, 0, 10001 );
   //:IF szNoWidthFlag = ""
   if ( ZeidonStringCompare( szNoWidthFlag, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = szWriteBuffer + " style=^width:" + szWidth + "px;^ "
      ZeidonStringConcat( szWriteBuffer, 1, 0, " style=^width:", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "px;^ ", 1, 0, 10001 );
   } 

   //:END
   //:szWriteBuffer = szWriteBuffer + " class=^grouptable^>"
   ZeidonStringConcat( szWriteBuffer, 1, 0, " class=^grouptable^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:      szWriteBuffer = "<tr>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<tr>", 1, 0, 10001 );
   //:      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

   //:LastY_Pos = 0
   LastY_Pos = 0;
   //:IF  vDialog.Control EXISTS
   lTempInteger_1 = CheckExistenceOfEntity( vDialog, "Control" );
   if ( lTempInteger_1 == 0 )
   { 
      //:SET CURSOR  FIRST vDialog.Control
      RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
      //:LastY_Pos = vDialog.Control.PSDLG_Y
      GetIntegerFromAttribute( &LastY_Pos, vDialog, "Control", "PSDLG_Y" );
   } 

   //:END


   //:// Loop through the controls, placing each control in a different column.
   //:// When the Y_Pos has changed, we need to create a new row in the table.
   //:FOR EACH vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 

      //:// We are onto a new row
      //:IF  LastY_Pos < vDialog.Control.PSDLG_Y
      if ( CompareAttributeToInteger( vDialog, "Control", "PSDLG_Y", LastY_Pos ) > 0 )
      { 

         //:// If LastY_Pos is 0 then we are on the first control.
         //:// If this wasn't the very first row, then
         //:// create the end tag for the last row.
         //://IF  LastY_Pos != 0
         //:   // If the previous row didn't have as many controls as there are
         //:   // table columns, then we need to create a blank column
         //:   LOOP  WHILE iColCnt < iHighestColCnt
         while ( iColCnt < iHighestColCnt )
         { 
            //:   szWriteBuffer = "<td>&nbsp</td>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<td>&nbsp</td>", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:   iColCnt = iColCnt + 1
            iColCnt = iColCnt + 1;
         } 

         //:   END
         //:   szWriteBuffer = "</tr>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "</tr>", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //://END

         //:szWriteBuffer = "<tr>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<tr>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:// Since we are on a new row, reset the column count.
         //:iColCnt = 0
         iColCnt = 0;
      } 

      //:END

      //:szCtrlTag = vDialog.Control.Tag
      GetVariableFromAttribute( szCtrlTag, 0, 'S', 51, vDialog, "Control", "Tag", "", 0 );
      //:szHTMLCtrlID = " id=^" + szCtrlTag + "^ name=^" + szCtrlTag + "^ "
      ZeidonStringCopy( szHTMLCtrlID, 1, 0, " id=^", 1, 0, 86 );
      ZeidonStringConcat( szHTMLCtrlID, 1, 0, szCtrlTag, 1, 0, 86 );
      ZeidonStringConcat( szHTMLCtrlID, 1, 0, "^ name=^", 1, 0, 86 );
      ZeidonStringConcat( szHTMLCtrlID, 1, 0, szCtrlTag, 1, 0, 86 );
      ZeidonStringConcat( szHTMLCtrlID, 1, 0, "^ ", 1, 0, 86 );
      //:szControlType = vDialog.ControlDef.Tag
      GetVariableFromAttribute( szControlType, 0, 'S', 51, vDialog, "ControlDef", "Tag", "", 0 );
      //:CreateNoPosStyleString( vDialog, szStyle, "" )
      CreateNoPosStyleString( vDialog, szStyle, "" );

      //:X_Pos = vDialog.Control.PSDLG_X
      GetIntegerFromAttribute( &X_Pos, vDialog, "Control", "PSDLG_X" );
      //://TraceLineI("*** Control Start position *** ", vDialog.Control.PSDLG_X )
      //:LastY_Pos = vDialog.Control.PSDLG_Y
      GetIntegerFromAttribute( &LastY_Pos, vDialog, "Control", "PSDLG_Y" );

      //:// We want to find out how wide this column should bed
      //:nRC = SetCursorNextEntity( vDialog, "Control", "" )
      nRC = SetCursorNextEntity( vDialog, "Control", "" );
      //:iColWidth = 0
      iColWidth = 0;
      //:IF  nRC >= zCURSOR_SET AND LastY_Pos = vDialog.Control.PSDLG_Y
      if ( nRC >= zCURSOR_SET && CompareAttributeToInteger( vDialog, "Control", "PSDLG_Y", LastY_Pos ) == 0 )
      { 
         //://TraceLineI("*** Next Control Start position *** ", vDialog.Control.PSDLG_X )
         //:iColWidth = vDialog.Control.PSDLG_X - X_Pos
         GetIntegerFromAttribute( &lTempInteger_2, vDialog, "Control", "PSDLG_X" );
         iColWidth = lTempInteger_2 - X_Pos;
      } 

      //:END

      //:IF  nRC >= zCURSOR_SET
      if ( nRC >= zCURSOR_SET )
      { 
         //:nRC = SetCursorPrevEntity( vDialog, "Control", "" )
         nRC = SetCursorPrevEntity( vDialog, "Control", "" );
      } 

      //:END

      //:IF  iColWidth = 0
      if ( iColWidth == 0 )
      { 
         //://TraceLineI("*** Width is width of control *** ", vDialog.Control.SZDLG_X )
         //:iColWidth = vDialog.Control.SZDLG_X
         GetIntegerFromAttribute( &iColWidth, vDialog, "Control", "SZDLG_X" );
      } 

      //:END

      //:szClass = vDialog.Control.CSS_Class
      GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
      //:IF vDialog.Control.CSS_Class != ""
      if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) != 0 )
      { 
         //:szClass = " class=^" + vDialog.Control.CSS_Class + "^ "
         GetVariableFromAttribute( szTempString_1, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_1, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:szClass = ""
         ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
      } 

      //:END

      //://KELLY0210
      //:zIntegerToString( szWidth, 10, iColWidth * dDLUnits )
      zIntegerToString( szWidth, 10, iColWidth * dDLUnits );
      //:szWriteBuffer = "<td valign=^top^ " + szClass + "style=^width:" + szWidth + "px;^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<td valign=^top^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "style=^width:", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "px;^>", 1, 0, 10001 );
      //://szWriteBuffer = "<td>"
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //://****************************************************************************

      //:/*
      //:IF szControlType = "GroupBox"  // Grid or Table
      //:   OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
      //:   // Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
      //:   CreateViewFromView( vGroupParent, vDialog )
      //:   SetViewToSubobject( vDialog, "CtrlCtrl" )
      //:   TraceLineS("**** GroupBox in Table ", " Before Recurs ")
      //:   GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, lFile, szWriteBuffer, szIndent,
      //:                           lTableRowCnt, szNoPositioning, 0, 0 )
      //:   TraceLineS("**** GroupBox in Table ", " After Recurs ")
      //:   ResetViewFromSubobject( vDialog )
      //:   DropView( vGroupParent )
      //:   vGroupParent = 0
      //:END
      //:*/

      //:IF szControlType = "GroupBox"
      if ( ZeidonStringCompare( szControlType, 1, 0, "GroupBox", 1, 0, 51 ) == 0 )
      { 

         //:// Do I need to check if this is a groupbox and we are not using absolute positioning, then I want to
         //:// check if there are other groupboxes at this same PSDLG_Y.  If so, then these groups would need to
         //:// have a float:left applied to them.
         //:// Would I only want to do this once for the row?
         //:// Or, do I want to put a float on every div created and then create a <div style="clear:both;"</div> after
         //:// every row?
         //://IF  szNoPositioning = "Y" AND szCheckedRowForGroups         //END


         //:// InitializeRepeatingGroup for GroupBox

         //:// Check to see if this GroupBox has a WebControlProperty of "Table".  If so, then we will create this
         //:// as a table and try and position what is in this group box as a table.
         //:szGroupIsTable = ""
         ZeidonStringCopy( szGroupIsTable, 1, 0, "", 1, 0, 2 );
         //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Table"
         RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Table", "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szGroupIsTable = "Y"
            ZeidonStringCopy( szGroupIsTable, 1, 0, "Y", 1, 0, 2 );
         } 

         //:END

         //:szNoHeightFlag = ""
         ZeidonStringCopy( szNoHeightFlag, 1, 0, "", 1, 0, 2 );
         //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "No Height"
         RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "No Height", "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szNoHeightFlag = "Y"
            ZeidonStringCopy( szNoHeightFlag, 1, 0, "Y", 1, 0, 2 );
         } 

         //:END

         //:szNoWidthFlag = ""
         ZeidonStringCopy( szNoWidthFlag, 1, 0, "", 1, 0, 2 );
         //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "No Width"
         RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "No Width", "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szNoWidthFlag = "Y"
            ZeidonStringCopy( szNoWidthFlag, 1, 0, "Y", 1, 0, 2 );
         } 

         //:END
      } 


      //:END

      //:// Initialize the szAbsoluteStyle variable with X and Y values.
      //:IF  szNoPositioning = "Y"
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 
         //:IF szControlType = "GroupBox" AND szNoHeightFlag = "Y" AND szNoWidthFlag = "Y"
         if ( ZeidonStringCompare( szControlType, 1, 0, "GroupBox", 1, 0, 51 ) == 0 && ZeidonStringCompare( szNoHeightFlag, 1, 0, "Y", 1, 0, 2 ) == 0 && ZeidonStringCompare( szNoWidthFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:szAbsoluteStyle = ""
            ZeidonStringCopy( szAbsoluteStyle, 1, 0, "", 1, 0, 257 );
            //:ELSE
         } 
         else
         { 
            //:IF szControlType = "GroupBox" AND szNoHeightFlag = "Y"
            if ( ZeidonStringCompare( szControlType, 1, 0, "GroupBox", 1, 0, 51 ) == 0 && ZeidonStringCompare( szNoHeightFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
            { 
               //:// We might not want the groupbox to have a height (so it grows)
               //:zIntegerToString( szWidth, 10, vDialog.Control.SZDLG_X * dDLUnits )
               GetIntegerFromAttribute( &lTempInteger_3, vDialog, "Control", "SZDLG_X" );
               zIntegerToString( szWidth, 10, lTempInteger_3 * dDLUnits );
               //:szAbsoluteStyle = "style=^width:" + szWidth + ";^"
               ZeidonStringCopy( szAbsoluteStyle, 1, 0, "style=^width:", 1, 0, 257 );
               ZeidonStringConcat( szAbsoluteStyle, 1, 0, szWidth, 1, 0, 257 );
               ZeidonStringConcat( szAbsoluteStyle, 1, 0, ";^", 1, 0, 257 );
               //:ELSE
            } 
            else
            { 
               //:IF szControlType = "GroupBox" AND szNoWidthFlag = "Y"
               if ( ZeidonStringCompare( szControlType, 1, 0, "GroupBox", 1, 0, 51 ) == 0 && ZeidonStringCompare( szNoWidthFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
               { 
                  //:// We might not want the groupbox to have a width (so it grows)
                  //:zIntegerToString( szHeight, 10, vDialog.Control.SZDLG_Y * dDLUnits )
                  GetIntegerFromAttribute( &lTempInteger_4, vDialog, "Control", "SZDLG_Y" );
                  zIntegerToString( szHeight, 10, lTempInteger_4 * dDLUnits );
                  //:szAbsoluteStyle = "style=^height:" + szHeight + ";^"
                  ZeidonStringCopy( szAbsoluteStyle, 1, 0, "style=^height:", 1, 0, 257 );
                  ZeidonStringConcat( szAbsoluteStyle, 1, 0, szHeight, 1, 0, 257 );
                  ZeidonStringConcat( szAbsoluteStyle, 1, 0, ";^", 1, 0, 257 );
                  //:ELSE
               } 
               else
               { 
                  //:CreateNoPosStyleString( vDialog, szAbsoluteStyle, "" )
                  CreateNoPosStyleString( vDialog, szAbsoluteStyle, "" );
               } 

               //:END
            } 

            //:END
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:CreateAbsolStyleString( vDialog, szAbsoluteStyle, lOffsetX, lOffsetY, "" )
         CreateAbsolStyleString( vDialog, szAbsoluteStyle, lOffsetX, lOffsetY, "" );
      } 

      //:END

      //:szWriteBuffer = "<% /* " + szCtrlTag + ":" + szControlType + " */ %>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<% /* ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ":", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szControlType, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " */ %>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:// Check to see if this GroupBox has a WebControlProperty of "Table".  If so, then we will create this
      //:// as a table and try and position what is in this group box as a table.
      //:IF szControlType = "GroupBox" AND szGroupIsTable = "Y"
      if ( ZeidonStringCompare( szControlType, 1, 0, "GroupBox", 1, 0, 51 ) == 0 && ZeidonStringCompare( szGroupIsTable, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 

         //:   X_Size = vDialog.Control.SZDLG_X
         GetIntegerFromAttribute( &X_Size, vDialog, "Control", "SZDLG_X" );
         //:   Y_Size = vDialog.Control.SZDLG_Y
         GetIntegerFromAttribute( &Y_Size, vDialog, "Control", "SZDLG_Y" );

         //:   OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
         OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" );
         //:   CreateViewFromView( vGroupParent, vDialog )
         CreateViewFromView( &vGroupParent, vDialog );
         //:   // Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
         //:   SetViewToSubobject( vDialog, "CtrlCtrl" )
         SetViewToSubobject( vDialog, "CtrlCtrl" );
         //:   szIndentGroup = szIndent
         ZeidonStringCopy( szIndentGroup, 1, 0, szIndent, 1, 0, 101 );
         //:   GenJSP_CrteGroupTable( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndent, lTableRowCnt, szNoPositioning )
         GenJSP_CrteGroupTable( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndent, lTableRowCnt, szNoPositioning );
         //:   ResetViewFromSubobject( vDialog )
         ResetViewFromSubobject( vDialog );
         //:   DropView( vGroupParent )
         DropView( vGroupParent );
         //:   vGroupParent = 0
         vGroupParent = 0;
      } 

      //:END

      //:IF szControlType = "GroupBox" AND szGroupIsTable = ""
      if ( ZeidonStringCompare( szControlType, 1, 0, "GroupBox", 1, 0, 51 ) == 0 && ZeidonStringCompare( szGroupIsTable, 1, 0, "", 1, 0, 2 ) == 0 )
      { 

         //:// Set Group flags either from old szWebCtrlType or new WebControlProperty.
         //:IF szWebCtrlType = "Scrollable"
         if ( ZeidonStringCompare( szWebCtrlType, 1, 0, "Scrollable", 1, 0, 51 ) == 0 )
         { 
            //:szScrollableFlag = "Y"
            ZeidonStringCopy( szScrollableFlag, 1, 0, "Y", 1, 0, 2 );
            //:ELSE
         } 
         else
         { 
            //:szScrollableFlag = ""
            ZeidonStringCopy( szScrollableFlag, 1, 0, "", 1, 0, 2 );
            //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Scrollable"
            RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Scrollable", "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:szScrollableFlag = "Y"
               ZeidonStringCopy( szScrollableFlag, 1, 0, "Y", 1, 0, 2 );
            } 

            //:END
         } 

         //:END
         //:IF szWebCtrlType = "Span"
         if ( ZeidonStringCompare( szWebCtrlType, 1, 0, "Span", 1, 0, 51 ) == 0 )
         { 
            //:szSpanFlag = "Y"
            ZeidonStringCopy( szSpanFlag, 1, 0, "Y", 1, 0, 2 );
            //:ELSE
         } 
         else
         { 
            //:szSpanFlag = ""
            ZeidonStringCopy( szSpanFlag, 1, 0, "", 1, 0, 2 );
            //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Span"
            RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Span", "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:szSpanFlag = "Y"
               ZeidonStringCopy( szSpanFlag, 1, 0, "Y", 1, 0, 2 );
            } 

            //:END
         } 

         //:END
         //:IF szWebCtrlType = "Div"
         if ( ZeidonStringCompare( szWebCtrlType, 1, 0, "Div", 1, 0, 51 ) == 0 )
         { 
            //:szDivFlag = "Y"
            ZeidonStringCopy( szDivFlag, 1, 0, "Y", 1, 0, 2 );
            //:ELSE
         } 
         else
         { 
            //:szDivFlag = ""
            ZeidonStringCopy( szDivFlag, 1, 0, "", 1, 0, 2 );
            //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Div"
            RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Div", "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:szDivFlag = "Y"
               ZeidonStringCopy( szDivFlag, 1, 0, "Y", 1, 0, 2 );
            } 

            //:END
         } 

         //:END


         //:// Is this clear even working???!!!
         //:IF szWebCtrlType = "Clear"
         if ( ZeidonStringCompare( szWebCtrlType, 1, 0, "Clear", 1, 0, 51 ) == 0 )
         { 
            //:szWriteBuffer = "<div id='clear'></div>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id='clear'></div>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
            //:X_Size = vDialog.Control.PSDLG_X * dDLUnits + lOffsetX  // borrow these for a second
            GetIntegerFromAttribute( &lTempInteger_5, vDialog, "Control", "PSDLG_X" );
            X_Size = lTempInteger_5 * dDLUnits + lOffsetX;
            //:Y_Size = vDialog.Control.PSDLG_Y * dDLUnits + lOffsetY
            GetIntegerFromAttribute( &lTempInteger_6, vDialog, "Control", "PSDLG_Y" );
            Y_Size = lTempInteger_6 * dDLUnits + lOffsetY;
            //:OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
            OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" );
            //:// Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
            //:CreateViewFromView( vGroupParent, vDialog )
            CreateViewFromView( &vGroupParent, vDialog );
            //:SetViewToSubobject( vDialog, "CtrlCtrl" )
            SetViewToSubobject( vDialog, "CtrlCtrl" );
            //:szIndentGroup = szIndent
            ZeidonStringCopy( szIndentGroup, 1, 0, szIndent, 1, 0, 101 );
            //:GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
            //:                        lTableRowCnt, szNoPositioning, X_Size, Y_Size )
            GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, X_Size, Y_Size );
            //:ResetViewFromSubobject( vDialog )
            ResetViewFromSubobject( vDialog );
            //:DropView( vGroupParent )
            DropView( vGroupParent );
            //:vGroupParent = 0
            vGroupParent = 0;
            //:szWriteBuffer = ""
            ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:ELSE
         } 
         else
         { 
            //:IF szSpanFlag = "Y"
            if ( ZeidonStringCompare( szSpanFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
            { 

               //:// Div on a Group Control requests that all the controls inside the group line up one under the other.
               //:szClass = vDialog.Control.CSS_Class
               GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
               //:IF szClass = ""
               if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
               { 
                  //:szWriteBuffer = "<span" + szHTMLCtrlID + szAbsoluteStyle + ">"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<span", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
                  //:ELSE
               } 
               else
               { 
                  //:szWriteBuffer = "<span" + szHTMLCtrlID + "class=^" + szClass + "^ " + szAbsoluteStyle + ">"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<span", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
               } 

               //:END
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

               //:OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
               OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" );
               //:// Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
               //:CreateViewFromView( vGroupParent, vDialog )
               CreateViewFromView( &vGroupParent, vDialog );
               //:SetViewToSubobject( vDialog, "CtrlCtrl" )
               SetViewToSubobject( vDialog, "CtrlCtrl" );
               //:szIndentGroup = szIndent
               ZeidonStringCopy( szIndentGroup, 1, 0, szIndent, 1, 0, 101 );
               //:GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
               //:                     lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY )
               GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY );
               //:ResetViewFromSubobject( vDialog )
               ResetViewFromSubobject( vDialog );
               //:DropView( vGroupParent )
               DropView( vGroupParent );
               //:vGroupParent = 0
               vGroupParent = 0;
               //:szWriteBuffer = "</span>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "</span>", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:ELSE
            } 
            else
            { 
               //:IF szDivFlag = "Y"
               if ( ZeidonStringCompare( szDivFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
               { 

                  //:// Add Scrollable if requested.
                  //:IF szScrollableFlag = "Y"
                  if ( ZeidonStringCompare( szScrollableFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
                  { 
                     //:zAppendQuotedString( szAbsoluteStyle, "overflow:auto;", "style=", "^" )
                     zAppendQuotedString( szAbsoluteStyle, "overflow:auto;", "style=", "^" );
                  } 

                  //:END

                  //:// If we are not using absolute positioning, then make all the divs
                  //:// float left.
                  //:IF  szNoPositioning = "Y"
                  if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
                  { 
                     //:zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" )
                     zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" );
                  } 

                  //:END

                  //:// Div on a Group Control requests that all the controls inside the group line up one under the other.
                  //:szClass = vDialog.Control.CSS_Class
                  GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
                  //:IF szClass = ""
                  if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
                  { 
                     //:szWriteBuffer = "<div" + szHTMLCtrlID + szAbsoluteStyle + ">"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "<div", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
                     //:ELSE
                  } 
                  else
                  { 
                     //:szWriteBuffer = "<div" + szHTMLCtrlID + "class=^" + szClass + "^ " + szAbsoluteStyle + ">"
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "<div", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
                  } 

                  //:END
                  //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
                  WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

                  //:OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
                  OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" );
                  //:// Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
                  //:CreateViewFromView( vGroupParent, vDialog )
                  CreateViewFromView( &vGroupParent, vDialog );
                  //:SetViewToSubobject( vDialog, "CtrlCtrl" )
                  SetViewToSubobject( vDialog, "CtrlCtrl" );
                  //:szIndentGroup = szIndent
                  ZeidonStringCopy( szIndentGroup, 1, 0, szIndent, 1, 0, 101 );
                  //:GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
                  //:                  lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY )
                  GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY );
                  //:ResetViewFromSubobject( vDialog )
                  ResetViewFromSubobject( vDialog );
                  //:DropView( vGroupParent )
                  DropView( vGroupParent );
                  //:vGroupParent = 0
                  vGroupParent = 0;
                  //:szWriteBuffer = "</div>  <!-- " + szCtrlTag + " --> "
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- ", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, " --> ", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
                  //:ELSE
               } 
               else
               { 
                  //:IF szWebCtrlType = "DivScroll"
                  if ( ZeidonStringCompare( szWebCtrlType, 1, 0, "DivScroll", 1, 0, 51 ) == 0 )
                  { 
                     //:// Div on a Group Control requests that all the controls inside the group line up one under the other.
                     //:zAppendQuotedString( szAbsoluteStyle, "overflow:auto;", "style=", "^" )
                     zAppendQuotedString( szAbsoluteStyle, "overflow:auto;", "style=", "^" );

                     //:// If we are not using absolute positioning, then make all the divs
                     //:// float left.
                     //:IF  szNoPositioning = "Y"
                     if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
                     { 
                        //:zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" )
                        zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" );
                     } 

                     //:END
                     //:szClass = vDialog.Control.CSS_Class
                     GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
                     //:IF szClass = ""
                     if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
                     { 
                        //:szWriteBuffer = "<div" + szHTMLCtrlID + szAbsoluteStyle + ">"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "<div", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
                        //:ELSE
                     } 
                     else
                     { 
                        //:szWriteBuffer = "<div" + szHTMLCtrlID + "class=^" + szClass + "^ " + szAbsoluteStyle + ">"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "<div", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
                     } 

                     //:END
                     //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
                     WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

                     //:OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
                     OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" );
                     //:// Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
                     //:CreateViewFromView( vGroupParent, vDialog )
                     CreateViewFromView( &vGroupParent, vDialog );
                     //:SetViewToSubobject( vDialog, "CtrlCtrl" )
                     SetViewToSubobject( vDialog, "CtrlCtrl" );
                     //:szIndentGroup = szIndent
                     ZeidonStringCopy( szIndentGroup, 1, 0, szIndent, 1, 0, 101 );
                     //:GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
                     //:               lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY )
                     GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY );
                     //:ResetViewFromSubobject( vDialog )
                     ResetViewFromSubobject( vDialog );
                     //:DropView( vGroupParent )
                     DropView( vGroupParent );
                     //:vGroupParent = 0
                     vGroupParent = 0;
                     //:szWriteBuffer = "</div>  <!-- " + szCtrlTag + " --> "
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- ", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, " --> ", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
                     //:ELSE
                  } 
                  else
                  { 
                     //:// Default Group is div for now

                     //:// If we are not using absolute positioning, then make all the divs float left.
                     //:IF  szNoPositioning = "Y"
                     if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
                     { 
                        //:zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" )
                        zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" );
                     } 

                     //:END

                     //:szClass = vDialog.Control.CSS_Class
                     GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
                     //:IF szClass = ""
                     if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
                     { 
                        //:szWriteBuffer = "<div" + szHTMLCtrlID + szAbsoluteStyle + ">"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "<div", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
                        //:ELSE
                     } 
                     else
                     { 
                        //:szWriteBuffer = "<div" + szHTMLCtrlID + "class=^" + szClass + "^ " + szAbsoluteStyle + ">"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "<div", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
                     } 

                     //:END
                     //:/*IF szClass = ""
                     //:szWriteBuffer = "<fieldset " + szAbsoluteStyle + ">"
                     //:ELSE
                     //:szWriteBuffer = "<fieldset class=^" + szClass + "^ " + szAbsoluteStyle + ">"
                     //:END*/
                     //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
                     //:IF vDialog.Control.Text != ""
                     if ( CompareAttributeToString( vDialog, "Control", "Text", "" ) != 0 )
                     { 
                        //:szWriteBuffer = "<div>" + vDialog.Control.Text + "</div>"
                        GetVariableFromAttribute( szTempString_2, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "<div>", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, "</div>", 1, 0, 10001 );
                        //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
                        WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
                     } 

                     //:END

                     //:OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
                     OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" );
                     //:// Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
                     //:CreateViewFromView( vGroupParent, vDialog )
                     CreateViewFromView( &vGroupParent, vDialog );
                     //:SetViewToSubobject( vDialog, "CtrlCtrl" )
                     SetViewToSubobject( vDialog, "CtrlCtrl" );
                     //:szIndentGroup = szIndent + "   "
                     ZeidonStringCopy( szIndentGroup, 1, 0, szIndent, 1, 0, 101 );
                     ZeidonStringConcat( szIndentGroup, 1, 0, "   ", 1, 0, 101 );
                     //:GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
                     //:               lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY )
                     GenJSP_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY );
                     //:ResetViewFromSubobject( vDialog )
                     ResetViewFromSubobject( vDialog );
                     //:DropView( vGroupParent )
                     DropView( vGroupParent );
                     //:vGroupParent = 0
                     vGroupParent = 0;

                     //:szWriteBuffer = "</div>  <!-- " + szCtrlTag + " --> "
                     ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- ", 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
                     ZeidonStringConcat( szWriteBuffer, 1, 0, " --> ", 1, 0, 10001 );
                     //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
                     WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
                  } 

                  //:END
               } 

               //:END
            } 

            //:END
         } 

         //:END
      } 


      //:END  // Control is groupbox

      //:IF szControlType = "Text"  // TEXT
      if ( ZeidonStringCompare( szControlType, 1, 0, "Text", 1, 0, 51 ) == 0 )
      { 
         //:GenJSP_CrteText( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndent, szCtrlTag,
         //:                 "", szNoPositioning, 0, 0 )
         GenJSP_CrteText( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndent, szCtrlTag, "", szNoPositioning, 0, 0 );
      } 

      //:END

      //:IF szControlType = "EditBox"  // EDITBOX
      if ( ZeidonStringCompare( szControlType, 1, 0, "EditBox", 1, 0, 51 ) == 0 )
      { 
         //:GenJSP_CrteEditBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag,
         //:                    "", "", szNoPositioning, 0, 0 )
         GenJSP_CrteEditBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, "", "", szNoPositioning, 0, 0 );
      } 

      //:END

      //:IF szControlType = "Calendar"  // CALENDAR
      if ( ZeidonStringCompare( szControlType, 1, 0, "Calendar", 1, 0, 51 ) == 0 )
      { 
         //:GenJSP_CrteCalendar( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag,
         //:                     "", "", szNoPositioning, 0, 0 )
         GenJSP_CrteCalendar( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, "", "", szNoPositioning, 0, 0 );
      } 

      //:END

      //:IF szControlType = "RadioGrp" // RADIO BUTTON GROUP
      if ( ZeidonStringCompare( szControlType, 1, 0, "RadioGrp", 1, 0, 51 ) == 0 )
      { 
         //:szWriteBuffer = "<% strErrorMapValue = ^^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<% strErrorMapValue = ^^;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:IF vDialog.CtrlMapView EXISTS
         lTempInteger_7 = CheckExistenceOfEntity( vDialog, "CtrlMapView" );
         if ( lTempInteger_7 == 0 )
         { 
            //:szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name +
            //:                ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name + "^, vAppSubtask );"
            GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   if ( nRC <= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC <= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name +
            //:                ".TraceLine( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
            GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name +
            //:                ".CheckExistenceOfEntity( strSessionId, ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
            GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         strRadioGroupValue = " +
            //:                vDialog.CtrlMapView.Name + ".GetString( strSessionId, ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
            //:                vDialog.CtrlMapER_Attribute.Name + "^ );"
            GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strRadioGroupValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetString( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         } 

         //:END

         //:szWriteBuffer = "%>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

         //://KJS 11/14/07 - I don't think there should always be a box around radio buttons.
         //://I'm going to do this like the way group box is (or was).  If there is text
         //://to go on the box then we will create <fieldset.  If there is no text then
         //://we will create a div.
         //://KJS 10/07/09 - I added the id to this <div but then realized that the radio buttons also have this
         //://id, so I am adding "gb" in front of the control tag.  Not sure how much we care that this div has
         //://an id and name but think it should.
         //:IF vDialog.Control.Text = ""
         if ( CompareAttributeToString( vDialog, "Control", "Text", "" ) == 0 )
         { 
            //://szWriteBuffer = "<div " + szStyle + ">"
            //:szWriteBuffer = "<div id=^gb" + szCtrlTag + "^ name=^gb" + szCtrlTag + "^ " + szStyle + ">"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^gb", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^gb", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "<fieldset " + szStyle + ">"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<fieldset ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         } 

         //:END
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:IF vDialog.Control.Text != ""
         if ( CompareAttributeToString( vDialog, "Control", "Text", "" ) != 0 )
         { 
            //:szWriteBuffer = "<div>" + vDialog.Control.Text + "</div>"
            GetVariableFromAttribute( szTempString_11, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<div>", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</div>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         } 

         //:END

         //:OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
         OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" );
         //:SetViewToSubobject( vDialog, "CtrlCtrl" )
         SetViewToSubobject( vDialog, "CtrlCtrl" );
         //:szIndent = szIndent + "   "
         ZeidonStringConcat( szIndent, 1, 0, "   ", 1, 0, 101 );
         //:GenJSP_CrteCtrlsRadio( vDialog, lFile, szWriteBuffer, szIndent,
         //:                       szCtrlTag, szNoPositioning, 0, 0 )
         GenJSP_CrteCtrlsRadio( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, szNoPositioning, 0, 0 );
         //:ResetViewFromSubobject( vDialog )
         ResetViewFromSubobject( vDialog );
         //:IF vDialog.Control.Text = ""
         if ( CompareAttributeToString( vDialog, "Control", "Text", "" ) == 0 )
         { 
            //:szWriteBuffer = "</div>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "</fieldset>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "</fieldset>", 1, 0, 10001 );
         } 

         //:END
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      } 


      //:END

      //:IF szControlType = "CheckBox"  // CHECKBOX
      if ( ZeidonStringCompare( szControlType, 1, 0, "CheckBox", 1, 0, 51 ) == 0 )
      { 
         //:GenJSP_CrteCheckBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag,
         //:                     "", "", szNoPositioning, 0, 0 )
         GenJSP_CrteCheckBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, "", "", szNoPositioning, 0, 0 );
      } 

      //:END

      //:IF szControlType = "PushBtn"  // PUSH BUTTON
      if ( ZeidonStringCompare( szControlType, 1, 0, "PushBtn", 1, 0, 51 ) == 0 )
      { 
         //:szActionName = ""
         ZeidonStringCopy( szActionName, 1, 0, "", 1, 0, 33 );
         //:IF vDialog.EventAct EXISTS
         lTempInteger_8 = CheckExistenceOfEntity( vDialog, "EventAct" );
         if ( lTempInteger_8 == 0 )
         { 
            //:szActionName = vDialog.EventAct.Tag
            GetVariableFromAttribute( szActionName, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
            //:nRC = zstrcmpi( szActionName, "alt-f4" )
            nRC = zstrcmpi( szActionName, "alt-f4" );
            //:IF nRC = 0
            if ( nRC == 0 )
            { 
               //:szActionName = "AltF4"
               ZeidonStringCopy( szActionName, 1, 0, "AltF4", 1, 0, 33 );
            } 

            //:END
         } 

         //:END

         //:CreateTabIndexString( vDialog, szTabIndex )
         CreateTabIndexString( vDialog, szTabIndex );
         //:szStyle = szStyle + szTabIndex
         ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );

         //:szText = ""
         ZeidonStringCopy( szText, 1, 0, "", 1, 0, 257 );
         //:szText = vDialog.Control.Text
         GetVariableFromAttribute( szText, 0, 'S', 257, vDialog, "Control", "Text", "", 0 );
         //:// Set Class as either null or with Class value.
         //:IF vDialog.Control.CSS_Class = ""
         if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) == 0 )
         { 
            //:szClass = ""
            ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
            //:ELSE
         } 
         else
         { 
            //:szClass = "class=^" + vDialog.Control.CSS_Class + "^ "
            GetVariableFromAttribute( szTempString_12, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
            ZeidonStringCopy( szClass, 1, 0, "class=^", 1, 0, 257 );
            ZeidonStringConcat( szClass, 1, 0, szTempString_12, 1, 0, 257 );
            ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
         } 

         //:END

         //://If we put a title on the control, when the mouse is hovered over the control, this text will display.
         //:szTitleHTML = ""
         ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
         //:szTitle = vDialog.Control.DIL_Text
         GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
         //:IF szTitle != ""
         if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
         { 
            //:szTitleHTML = " title=^" + szTitle + "^ "
            ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
            ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
            ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
         } 

         //:END

         //:szWriteBuffer = "<button type=^button^ " + szClass + szTitleHTML + szHTMLCtrlID
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<button type=^button^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );

         //:szWriteBuffer = szWriteBuffer + "value=^" + szText + "^ onclick=^" +
         //:                szActionName + "( )^ " + " " + szStyle + ">" + szText + "</button>"
         ZeidonStringConcat( szWriteBuffer, 1, 0, "value=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</button>", 1, 0, 10001 );

         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      } 

      //:END  //End of PushBtn

      //:IF szControlType = "ComboBox"  // COMBOBOX
      if ( ZeidonStringCompare( szControlType, 1, 0, "ComboBox", 1, 0, 51 ) == 0 )
      { 
         //:GenJSP_CrteComboBox( vDialog, lFile, szWriteBuffer, szIndent,
         //:                     szCtrlTag, "", szNoPositioning, 0, 0 )
         GenJSP_CrteComboBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, "", szNoPositioning, 0, 0 );
      } 

      //:END

      //:IF szControlType = "Bitmap" OR szControlType = "BitmapBtn"  // BITMAP or JPG
      if ( ZeidonStringCompare( szControlType, 1, 0, "Bitmap", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "BitmapBtn", 1, 0, 51 ) == 0 )
      { 
         //:GenJSP_CrteJPG( vDialog, lFile, szWriteBuffer, szIndent,
         //:                szCtrlTag, szNoPositioning, 0, 0 )
         GenJSP_CrteJPG( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, szNoPositioning, 0, 0 );
      } 

      //:END

      //:IF szControlType = "ListBox"  // LISTBOX
      if ( ZeidonStringCompare( szControlType, 1, 0, "ListBox", 1, 0, 51 ) == 0 )
      { 
         //:GenJSP_CrteListBox( vDialog, lFile, szWriteBuffer, szIndent,
         //:                    szCtrlTag, szNoPositioning, 0, 0 )
         GenJSP_CrteListBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, szNoPositioning, 0, 0 );
      } 

      //:END  // IF szControlType = "ListBox"

      //:IF szControlType = "MLEdit"  // MLEDIT
      if ( ZeidonStringCompare( szControlType, 1, 0, "MLEdit", 1, 0, 51 ) == 0 )
      { 
         //:SET CURSOR FIRST vDialog.CtrlMapLOD_Attribute WITHIN vDialog.Control
         RESULT = SetCursorFirstEntity( vDialog, "CtrlMapLOD_Attribute", "Control" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szWriteBuffer = "<%"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   // " + szControlType + ": " + szCtrlTag
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   // ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szControlType, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ": ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   strErrorMapValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name + ".GetView( strSessionId, ^" +
            //:                vDialog.CtrlMapView.Name + "^, vAppSubtask );"
            GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_14, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   if ( nRC <= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC <= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name +
            //:                ".TraceLine( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
            GetVariableFromAttribute( szTempString_15, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_15, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name +
            //:                ".CheckExistenceOfEntity( strSessionId, ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
            GetVariableFromAttribute( szTempString_16, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_16, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_17, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_17, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:szContextName = ""
            ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );
            //:IF vDialog.CtrlMapContext EXISTS
            lTempInteger_9 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
            if ( lTempInteger_9 == 0 )
            { 
               //:szContextName = vDialog.CtrlMapContext.Name
               GetVariableFromAttribute( szContextName, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
            } 

            //:END

            //:lMaxStringLth = vDialog.CtrlMapER_Domain.MaxStringLth
            GetIntegerFromAttribute( &lMaxStringLth, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
            //:IF lMaxStringLth <= 0
            if ( lMaxStringLth <= 0 )
            { 
               //:szMaxStringLth = "254"
               ZeidonStringCopy( szMaxStringLth, 1, 0, "254", 1, 0, 11 );
               //:ELSE
            } 
            else
            { 
               //:szMaxStringLth = lMaxStringLth
               ZeidonStringConvertFromNumber( szMaxStringLth, 1, 0, 10, lMaxStringLth, (ZDecimal) 0.0, "I" );
            } 

            //:END

            //:szWriteBuffer = "         strErrorMapValue = " +
            //:                vDialog.CtrlMapView.Name +
            //:                ".GetStringFromAttributeByContext( strSessionId, ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
            //:                vDialog.CtrlMapER_Attribute.Name + "^, ^" +
            //:                szContextName + "^, " + szMaxStringLth + " );"
            GetVariableFromAttribute( szTempString_18, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_18, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_19, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_19, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_20, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_20, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szMaxStringLth, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );

            //:lStyleX = vDialog.Control.ExtendedStyle
            GetIntegerFromAttribute( &lStyleX, vDialog, "Control", "ExtendedStyle" );
            //:lTemp = IsFlagSequenceSet( lStyleX, zCONTROLX_PREFILL )
            lTemp = IsFlagSequenceSet( lStyleX, zCONTROLX_PREFILL );
            //:IF lTemp != 0
            if ( lTemp != 0 )
            { 
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
               //:szWriteBuffer = "      if ( strErrorMapValue.length( ) == 0 )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strErrorMapValue.length( ) == 0 )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "         strErrorMapValue = ^" + vDialog.Control.Text + "^;"
               GetVariableFromAttribute( szTempString_21, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_21, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
            } 

            //:END

            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:szWriteBuffer = "%>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
            //:X_Size = vDialog.Control.SZDLG_X
            GetIntegerFromAttribute( &X_Size, vDialog, "Control", "SZDLG_X" );
            //:Size = X_Size / 4
            Size = X_Size / 4;
            //:zIntegerToString( szSize, 10, Size )
            zIntegerToString( szSize, 10, Size );
            //:Y_Size = vDialog.Control.SZDLG_Y
            GetIntegerFromAttribute( &Y_Size, vDialog, "Control", "SZDLG_Y" );
            //:Size = Y_Size / 12
            Size = Y_Size / 12;
            //:zIntegerToString( szHeight, 10, Size )
            zIntegerToString( szHeight, 10, Size );

            //:IF vDialog.Control.VisibleBorder = "Y"
            if ( CompareAttributeToString( vDialog, "Control", "VisibleBorder", "Y" ) == 0 )
            { 
               //:zAppendQuotedString( szStyle, "border:'4px solid';border-style:'groove';", "style=", "^" )
               zAppendQuotedString( szStyle, "border:'4px solid';border-style:'groove';", "style=", "^" );
               //:ELSE
            } 
            else
            { 
               //:zAppendQuotedString( szStyle, "border:'2px solid';border-style:'groove';", "style=", "^" )
               zAppendQuotedString( szStyle, "border:'2px solid';border-style:'groove';", "style=", "^" );
            } 

            //:END
            //:zAppendQuotedString( szStyle, szAbsoluteStyle, "style=", "^" )
            zAppendQuotedString( szStyle, szAbsoluteStyle, "style=", "^" );

            //:szTinyMCEFlag = ""
            ZeidonStringCopy( szTinyMCEFlag, 1, 0, "", 1, 0, 2 );
            //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "wysiwyg TinyMCE"
            RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "wysiwyg TinyMCE", "" );
            //:IF RESULT >= zCURSOR_SET
            if ( RESULT >= zCURSOR_SET )
            { 
               //:szTinyMCEFlag = "Y"
               ZeidonStringCopy( szTinyMCEFlag, 1, 0, "Y", 1, 0, 2 );
            } 

            //:END

            //:// dks 2016.04.08 - trying placeholder
            //:// If we put a title on the control, when the mouse is hovered over the control, this text will display.
            //:szTitleHTML = ""
            ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
            //:szTitle = vDialog.Control.DIL_Text
            GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
            //:IF szTitle != ""
            if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
            { 
               //:szTitleHTML = " title=^" + szTitle + "^"
               ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
               ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
               ZeidonStringConcat( szTitleHTML, 1, 0, "^", 1, 0, 257 );
            } 

            //:END
            //:szTitle = vDialog.Control.Placeholder
            GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "Placeholder", "", 0 );
            //:IF szTitle != ""
            if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
            { 
               //:szTitleHTML = szTitleHTML + " placeholder=^" + szTitle + "^"
               ZeidonStringConcat( szTitleHTML, 1, 0, " placeholder=^", 1, 0, 257 );
               ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
               ZeidonStringConcat( szTitleHTML, 1, 0, "^", 1, 0, 257 );
            } 

            //:END

            //:IF lMaxStringLth <= 0
            if ( lMaxStringLth <= 0 )
            { 
               //:szMaxStringLth = "20"
               ZeidonStringCopy( szMaxStringLth, 1, 0, "20", 1, 0, 11 );
               //:ELSE
            } 
            else
            { 
               //:szMaxStringLth = lMaxStringLth
               ZeidonStringConvertFromNumber( szMaxStringLth, 1, 0, 10, lMaxStringLth, (ZDecimal) 0.0, "I" );
            } 

            //:END
            //:IF vDialog.Control.WebCtrlType = "wysiwygEditor" OR szTinyMCEFlag = "Y"
            if ( CompareAttributeToString( vDialog, "Control", "WebCtrlType", "wysiwygEditor" ) == 0 || ZeidonStringCompare( szTinyMCEFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
            { 

               //:szClass = vDialog.Control.CSS_Class
               GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
               //:IF szClass = ""
               if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
               { 
                  //:szClass = "mceSimple" // "mceSimple" is TinyMCE default
                  ZeidonStringCopy( szClass, 1, 0, "mceSimple", 1, 0, 257 );
               } 

               //:END

               //:nRC = zSearchSubString( szClass, "mceSimpleZeidon", "f", 0 )
               nRC = zSearchSubString( szClass, "mceSimpleZeidon", "f", 0 );
               //:IF nRC >= 0
               if ( nRC >= 0 )
               { 
                  //:szWriteBuffer = "<div style=^background-color:#eed;border:1px solid #031;width:" + szSize + "px;height:" + szHeight + "px;position:absolute;left:0px;top:0px;^>"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<div style=^background-color:#eed;border:1px solid #031;width:", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szSize, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "px;height:", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHeight, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "px;position:absolute;left:0px;top:0px;^>", 1, 0, 10001 );
                  //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
                  WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
                  //:szWriteBuffer = "<div class=^" + szClass + "^ " + szTitleHTML + " style=^width:" + szSize + "px;height:" + szHeight + "px;position:absolute;left:0px;top:0px;^><%=strErrorMapValue%></div></div>"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<div class=^", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, " style=^width:", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szSize, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "px;height:", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHeight, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "px;position:absolute;left:0px;top:0px;^><%=strErrorMapValue%></div></div>", 1, 0, 10001 );
                  //:ELSE
               } 
               else
               { 
                  //:szWriteBuffer = "<textarea" + szHTMLCtrlID + "class=^" + szClass + "^ maxlength=^" + szMaxStringLth + "^ " + szTitleHTML + szStyle + ">" + "<%=strErrorMapValue%></textarea>"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<textarea", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "^ maxlength=^", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szMaxStringLth, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "<%=strErrorMapValue%></textarea>", 1, 0, 10001 );
               } 

               //:END
               //:ELSE
            } 
            else
            { 
               //:szClass = ""
               ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
               //:szClass = vDialog.Control.CSS_Class
               GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
               //:CreateTabIndexString( vDialog, szTabIndex )
               CreateTabIndexString( vDialog, szTabIndex );
               //:szWriteBuffer = "<textarea" + szHTMLCtrlID + szTitleHTML + "class=^" + szClass + "^ maxlength=^" + szMaxStringLth + "^ " +
               //:                szStyle + szTabIndex + " wrap=^wrap^>" + "<%=strErrorMapValue%></textarea>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "<textarea", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ maxlength=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szMaxStringLth, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " wrap=^wrap^>", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "<%=strErrorMapValue%></textarea>", 1, 0, 10001 );
            } 


            //:END
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         } 

         //:END
      } 

      //:END   //IF szControlType = "MLEdit"

      //://****************************************************************************

      //:szWriteBuffer = "</td>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "</td>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:iColCnt = iColCnt + 1
      iColCnt = iColCnt + 1;
      RESULT = SetCursorNextEntity( vDialog, "Control", "" );
   } 

   //:END

   //:// If the previous row didn't have as many controls as there are table columns, then we need to create a blank column
   //:LOOP  WHILE iColCnt < iHighestColCnt
   while ( iColCnt < iHighestColCnt )
   { 
      //:szWriteBuffer = "<td>&nbsp</td>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<td>&nbsp</td>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:iColCnt = iColCnt + 1
      iColCnt = iColCnt + 1;
   } 

   //:END

   //:szWriteBuffer = "</tr>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</tr>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "</table>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</table>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "</div>  <!-- " + szParentCtrlTag + " --> "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szParentCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " --> ", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteComboBox( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY )

//:   // Combo boxes on OUTPUT

//:   // There are two kinds of combo boxes on output.
//:   // 1. Domain combo boxes, which need to get the individual table values
//:   //    from core calls.
//:   // 2. Select combo boxes (e.g.  Automatic Include, Set Foreign Key, etc.)
//:   //    which read the data values from an object, the same as a list box.
//:   // These two conditions are handled quite separately below, even though
//:   // the resulting HTML is basically the same.

//:   VIEW vList   BASED ON LOD TZWDLGSO  // identifies attribute mapping for list entries
zOPER_EXPORT zVOID OPERATION
GenJSP_CrteComboBox( zVIEW     vDialog,
                     zLONG     lFile,
                     zPCHAR    szWriteBuffer,
                     zPCHAR    szIndent,
                     zPCHAR    szCtrlTag,
                     zPCHAR    szTableRowFlag,
                     zPCHAR    szNoPositioning,
                     zLONG     lOffsetX,
                     zLONG     lOffsetY )
{
   zVIEW     vList = 0; 
   //:VIEW vEntity BASED ON LOD TZWDLGSO  // identifies entity mapping for list entries
   zVIEW     vEntity = 0; 
   //:VIEW vScope  BASED ON LOD TZWDLGSO  // identifies scoping entity for list entries
   zVIEW     vScope = 0; 
   //:STRING ( 32 )  szContextName
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 32 )  szScopingEntityName
   zCHAR     szScopingEntityName[ 33 ] = { 0 }; 
   //:STRING ( 32 )  szListEntityName
   zCHAR     szListEntityName[ 33 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 10 )  szWidth
   zCHAR     szWidth[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szSelectAction
   zCHAR     szSelectAction[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szSelectFunction
   zCHAR     szSelectFunction[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szHeight
   zCHAR     szHeight[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szX_Pos
   zCHAR     szX_Pos[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szY_Pos
   zCHAR     szY_Pos[ 11 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   //:INTEGER        lSubtype
   zLONG     lSubtype = 0; 
   //:SHORT          nRC
   zSHORT    nRC = 0; 
   zLONG     lTempInteger_0; 
   zLONG     lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zSHORT    lTempInteger_4; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zSHORT    lTempInteger_5; 
   zSHORT    lTempInteger_6; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_7; 
   zSHORT    lTempInteger_8; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 
   zSHORT    lTempInteger_9; 
   zCHAR     szTempString_12[ 33 ]; 
   zCHAR     szTempString_13[ 33 ]; 
   zCHAR     szTempString_14[ 33 ]; 
   zCHAR     szTempString_15[ 33 ]; 
   zSHORT    lTempInteger_10; 
   zCHAR     szTempString_16[ 33 ]; 
   zCHAR     szTempString_17[ 33 ]; 
   zCHAR     szTempString_18[ 33 ]; 
   zSHORT    lTempInteger_11; 
   zSHORT    lTempInteger_12; 
   zCHAR     szTempString_19[ 33 ]; 
   zSHORT    lTempInteger_13; 
   zSHORT    lTempInteger_14; 
   zCHAR     szTempString_20[ 33 ]; 
   zCHAR     szTempString_21[ 33 ]; 


   //:szStyle = "width:" + szWidth + "px; height:" + szHeight + "px;"
   ZeidonStringCopy( szStyle, 1, 0, "width:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px; height:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
   //:szClass = vDialog.Control.CSS_Class
   GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );

   //://If we put a title on the control, when the mouse is hovered over the control, this text will display.
   //:szTitleHTML = ""
   ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
   //:szTitle = vDialog.Control.DIL_Text
   GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
   //:IF szTitle != ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
   { 
      //:szTitleHTML = " title=^" + szTitle + "^ "
      ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //:CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );
   //:// We will set the height to the constant 20 px.
   //:PIX_PER_DU( vDialog, dDLUnits )
   PIX_PER_DU( vDialog, &dDLUnits );
   //:zIntegerToString( szWidth, 10, vDialog.Control.SZDLG_X * dDLUnits )
   GetIntegerFromAttribute( &lTempInteger_0, vDialog, "Control", "SZDLG_X" );
   zIntegerToString( szWidth, 10, lTempInteger_0 * dDLUnits );
   //:szHeight = "20"
   ZeidonStringCopy( szHeight, 1, 0, "20", 1, 0, 11 );
   //:// The height used to be hard coded but we took that out!!!
   //://szStyle = "style=^width:" + szWidth + "px;height:" + szHeight + "px;"
   //:szStyle = "style=^width:" + szWidth + "px;"
   ZeidonStringCopy( szStyle, 1, 0, "style=^width:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );

   //:// If szNoPositioning is null then we are using absolute positioning.
   //:IF  szNoPositioning = ""
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
   { 

      //:zIntegerToString( szX_Pos, 10, vDialog.Control.PSDLG_X * dDLUnits )
      GetIntegerFromAttribute( &lTempInteger_1, vDialog, "Control", "PSDLG_X" );
      zIntegerToString( szX_Pos, 10, lTempInteger_1 * dDLUnits );
      //:zIntegerToString( szY_Pos, 10, vDialog.Control.PSDLG_Y * dDLUnits )
      GetIntegerFromAttribute( &lTempInteger_2, vDialog, "Control", "PSDLG_Y" );
      zIntegerToString( szY_Pos, 10, lTempInteger_2 * dDLUnits );

      //:szStyle = szStyle + "position:absolute;" + "left:" + szX_Pos + "px;" + "top:" + szY_Pos + "px;^ "
      ZeidonStringConcat( szStyle, 1, 0, "position:absolute;", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "left:", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, szX_Pos, 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "top:", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, szY_Pos, 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "px;^ ", 1, 0, 257 );
      //:// CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
      //:ELSE
   } 
   else
   { 
      //:szStyle = szStyle + "^ "
      ZeidonStringConcat( szStyle, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //:szStyle = szStyle + szTabIndex
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );

   //:szWriteBuffer = "<% strErrorMapValue = ^^;  %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<% strErrorMapValue = ^^;  %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:lSubtype = vDialog.Control.Subtype
   GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "Subtype" );
   //:nRC = AreBitsSetInFlag( lSubtype, 61440 ) // 0x0000F000
   nRC = AreBitsSetInFlag( lSubtype, 61440 );
   //:IF nRC = 0   // IF vDialog.Control.Subtype < 12000  ==> Domain Combobox
   if ( nRC == 0 )
   { 

      //:// Domain type combo box

      //:szWriteBuffer = "<input name=^h" + szCtrlTag + "^ id=^h" + szCtrlTag + "^ type=^hidden^ value=^0^ >"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input name=^h", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^h", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ type=^hidden^ value=^0^ >", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:// The Select Action is either onfocusout or onchange depending on the following.
      //:// 1. If no Action, use onchange because this allows using keystrokes in the control.
      //:// 2. If Action is SelectChange, use onchange.
      //:// 3. If Action is SelectEnd, use onblur
      //:IF vDialog.Event EXISTS
      lTempInteger_3 = CheckExistenceOfEntity( vDialog, "Event" );
      if ( lTempInteger_3 == 0 )
      { 
         //:IF vDialog.Event.Type = 1
         if ( CompareAttributeToInteger( vDialog, "Event", "Type", 1 ) == 0 )
         { 
            //:szSelectAction   = "onchange"
            ZeidonStringCopy( szSelectAction, 1, 0, "onchange", 1, 0, 11 );
            //:szSelectFunction = "OnChange"
            ZeidonStringCopy( szSelectFunction, 1, 0, "OnChange", 1, 0, 11 );
            //:ELSE
         } 
         else
         { 
            //:szSelectAction   = "onblur"
            ZeidonStringCopy( szSelectAction, 1, 0, "onblur", 1, 0, 11 );
            //:szSelectFunction = "OnBlur"
            ZeidonStringCopy( szSelectFunction, 1, 0, "OnBlur", 1, 0, 11 );
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:szSelectAction   = "onchange"
         ZeidonStringCopy( szSelectAction, 1, 0, "onchange", 1, 0, 11 );
         //:szSelectFunction = "OnChange"
         ZeidonStringCopy( szSelectFunction, 1, 0, "OnChange", 1, 0, 11 );
      } 

      //:END

      //:CreateDisabledString( vDialog, szDisabled )
      CreateDisabledString( vDialog, szDisabled );

      //:IF szClass = ""
      if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
      { 
         //:szWriteBuffer = "<select name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^1^ " + szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" +
         //:                szCtrlTag + szSelectFunction + "( )^" + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<select name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^1^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectAction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectFunction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "<select class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^1^ " + szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" +
         //:                szCtrlTag + szSelectFunction + "( )^" + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<select class=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^1^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectAction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectFunction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      } 

      //:END
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:IF vDialog.CtrlMapView EXISTS
      lTempInteger_4 = CheckExistenceOfEntity( vDialog, "CtrlMapView" );
      if ( lTempInteger_4 == 0 )
      { 
         //:szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name +
         //:             ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name + "^, vAppSubtask );"
         GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   if ( nRC > 0 )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC > 0 )", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   {"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:// We get each table value from a core call.
         //:IF vDialog.CtrlMapLOD_Attribute EXISTS
         lTempInteger_5 = CheckExistenceOfEntity( vDialog, "CtrlMapLOD_Attribute" );
         if ( lTempInteger_5 == 0 )
         { 
            //:szWriteBuffer = "      int    nRowCnt= 0;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      int    nRowCnt= 0;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      Vector ComboVector;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      Vector ComboVector;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:IF vDialog.CtrlMapContext EXISTS
            lTempInteger_6 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
            if ( lTempInteger_6 == 0 )
            { 
               //:szContextName = vDialog.CtrlMapContext.Name
               GetVariableFromAttribute( szContextName, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
               //:ELSE
            } 
            else
            { 
               //:szContextName = ""
               ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );
            } 

            //:END
            //:/***** 04/26/11 */
            //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name +
            //:         ".CheckExistenceOfEntity( strSessionId, ^" +
            //:         vDialog.CtrlMapRelatedEntity.Name + "^ );"
            GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         strComboCurrentValue = " + vDialog.CtrlMapView.Name +
            //:         ".GetStringFromAttributeByContext( strSessionId, ^" +
            //:         vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
            //:         vDialog.CtrlMapER_Attribute.Name + "^, ^" + szContextName + "^, 254 );"
            GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strComboCurrentValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 254 );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:/*****/
            //://szWriteBuffer = "      strComboCurrentValue = " + vDialog.CtrlMapView.Name +
            //://         ".GetStringFromAttributeByContext( strSessionId, ^" +
            //://         vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
            //://         vDialog.CtrlMapER_Attribute.Name + "^, ^" + szContextName + "^, 200 );"
            //://WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )

            //:szWriteBuffer = "      ComboVector = " + vDialog.CtrlMapView.Name +
            //:         ".GetTableListForAttribute( strSessionId, ^" + vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
            //:         vDialog.CtrlMapER_Attribute.Name + "^, ^" + szContextName + "^ );"
            GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ComboVector = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetTableListForAttribute( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      nRowCnt = (int) ComboVector.size( );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRowCnt = (int) ComboVector.size( );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      int k;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      int k;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      int nFirst;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      int nFirst;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:szWriteBuffer = "      if ( nRowCnt > 0 ) "
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRowCnt > 0 ) ", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:IF vDialog.CtrlMapER_Attribute.NotNull = "Y"
            if ( CompareAttributeToString( vDialog, "CtrlMapER_Attribute", "NotNull", "Y" ) == 0 )
            { 
               //:// Generate code when attribute IS required.
               //:szWriteBuffer = "      // Code for required attribute, which doesn't allow a blank entry."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Code for required attribute, which doesn't allow a blank entry.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "         nFirst = (ComboVector.elementAt( 0 ) == ^^) ? 1 : 0;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         nFirst = (ComboVector.elementAt( 0 ) == ^^) ? 1 : 0;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

               //:ELSE
            } 
            else
            { 
               //:// Generate code when attribute is NOT required.
               //:szWriteBuffer = "      // Code for NOT required attribute, which makes sure a blank entry exists."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Code for NOT required attribute, which makes sure a blank entry exists.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      if ( ComboVector.elementAt( 0 ) != ^^ )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( ComboVector.elementAt( 0 ) != ^^ )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      {"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "            if ( strComboCurrentValue == ^^ )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( strComboCurrentValue == ^^ )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "            {"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "%>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "            <option selected=^selected^ value=^^></option>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option selected=^selected^ value=^^></option>", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "<%"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "            }"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "            else"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "            else", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "            {"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "%>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "            <option value=^^></option>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option value=^^></option>", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "<%"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "            }"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "         }"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

               //:szWriteBuffer = "         nFirst = 0;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         nFirst = 0;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            } 

            //:END

            //:szWriteBuffer = "         for ( k = nFirst; k < nRowCnt; k++ )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         for ( k = nFirst; k < nRowCnt; k++ )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            strErrorMapValue = (String) ComboVector.elementAt( k );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            strErrorMapValue = (String) ComboVector.elementAt( k );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:// The following if statement eliminates a null value, which would be the second null in the combo box.
            //:szWriteBuffer = "            if ( strErrorMapValue.length( ) != 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( strErrorMapValue.length( ) != 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               if ( strComboCurrentValue.equals( strErrorMapValue ) )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               if ( strComboCurrentValue.equals( strErrorMapValue ) )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "%>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "                  <option selected=^selected^ value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "                  <option selected=^selected^ value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "<%"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "%>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "                  <option value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "                  <option value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "<%"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         } 

         //:END
      } 

      //:END

      //:szWriteBuffer = "         }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      } //if ( nRowCnt > 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      } //if ( nRowCnt > 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "</select>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "</select>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:ELSE  //kelly1
   } 
   else
   { 
      //:// Select type combo box
      //:CreateViewFromViewForTask( vList, vDialog, 0 )
      CreateViewFromViewForTask( &vList, vDialog, 0 );
      //:SET CURSOR NEXT vList.CtrlMap
      RESULT = SetCursorNextEntity( vList, "CtrlMap", "" );
      //:CreateViewFromViewForTask( vEntity, vList, 0 )
      CreateViewFromViewForTask( &vEntity, vList, 0 );
      //:SET CURSOR NEXT vEntity.CtrlMap
      RESULT = SetCursorNextEntity( vEntity, "CtrlMap", "" );
      //:CreateViewFromViewForTask( vScope, vEntity, 0 )
      CreateViewFromViewForTask( &vScope, vEntity, 0 );
      //:SET CURSOR NEXT vScope.CtrlMap
      RESULT = SetCursorNextEntity( vScope, "CtrlMap", "" );

      //:// The Select Action is either onblur or onchange depending on the following.
      //:// 1. If no Action, use onchange because this allows using keystrokes in the control.
      //:// 2. If Action is SelectChange, use onchange.
      //:// 3. If Action is SelectEnd, use onfocusout.
      //:IF vDialog.Event EXISTS
      lTempInteger_7 = CheckExistenceOfEntity( vDialog, "Event" );
      if ( lTempInteger_7 == 0 )
      { 
         //:IF vDialog.Event.Type = 1
         if ( CompareAttributeToInteger( vDialog, "Event", "Type", 1 ) == 0 )
         { 
            //:szSelectAction   = "onchange"
            ZeidonStringCopy( szSelectAction, 1, 0, "onchange", 1, 0, 11 );
            //:szSelectFunction = "OnChange"
            ZeidonStringCopy( szSelectFunction, 1, 0, "OnChange", 1, 0, 11 );
            //:ELSE
         } 
         else
         { 
            //:szSelectAction   = "onblur"
            ZeidonStringCopy( szSelectAction, 1, 0, "onblur", 1, 0, 11 );
            //:szSelectFunction = "OnBlur"
            ZeidonStringCopy( szSelectFunction, 1, 0, "OnBlur", 1, 0, 11 );
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:szSelectAction = "onchange"
         ZeidonStringCopy( szSelectAction, 1, 0, "onchange", 1, 0, 11 );
         //:szSelectFunction = "OnChange"
         ZeidonStringCopy( szSelectFunction, 1, 0, "OnChange", 1, 0, 11 );
      } 

      //:END
      //:IF szClass = ""
      if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
      { 
         //:szWriteBuffer = "<select name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^1^" + szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" +
         //:                szCtrlTag + szSelectFunction + "( )^" + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<select name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^1^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectAction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectFunction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "<select class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^1^" + szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" +
         //:                szCtrlTag + szSelectFunction + "( )^" + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<select class=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^1^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectAction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectFunction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      } 

      //:END
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:IF vDialog.CtrlMapView EXISTS
      lTempInteger_8 = CheckExistenceOfEntity( vDialog, "CtrlMapView" );
      if ( lTempInteger_8 == 0 )
      { 
         //:szWriteBuffer = "   nRC = " + vList.CtrlMapView.Name +
         //:                ".GetView( strSessionId, ^" + vList.CtrlMapView.Name + "^, vAppSubtask );"
         GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vList, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vList, "CtrlMapView", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   if ( nRC > 0 )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC > 0 )", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   {"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         strComboCurrentValue = ^^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strComboCurrentValue = ^^;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "      zeidon.zView v" + szCtrlTag + " = new zeidon.zView( strSessionId );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      zeidon.zView v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " = new zeidon.zView( strSessionId );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:// If mapping is specified, set up the value to be used in selecting
         //:// the correct entry.
         //:IF vDialog.CtrlMapLOD_Attribute EXISTS
         lTempInteger_9 = CheckExistenceOfEntity( vDialog, "CtrlMapLOD_Attribute" );
         if ( lTempInteger_9 == 0 )
         { 
            //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name +
            //:                ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name +
            //:                "^, vAppSubtask );"
            GetVariableFromAttribute( szTempString_12, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( nRC > 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC > 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         nRC = " + vDialog.CtrlMapView.Name + ".CheckExistenceOfEntity( strSessionId, ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
            GetVariableFromAttribute( szTempString_14, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_15, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_15, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( nRC >= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:IF vDialog.CtrlMapContext EXISTS
            lTempInteger_10 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
            if ( lTempInteger_10 == 0 )
            { 
               //:szContextName = vDialog.CtrlMapContext.Name
               GetVariableFromAttribute( szContextName, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
               //:ELSE
            } 
            else
            { 
               //:szContextName = ""
               ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );
            } 

            //:END
            //:szWriteBuffer = "            strComboCurrentValue = " + vDialog.CtrlMapView.Name +
            //:         ".GetStringFromAttributeByContext( strSessionId, ^" +
            //:         vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
            //:         vDialog.CtrlMapER_Attribute.Name + "^, ^" + szContextName + "^, 254 );"
            GetVariableFromAttribute( szTempString_16, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            strComboCurrentValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_16, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_17, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_17, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_18, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_18, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 254 );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "      strComboCurrentValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      strComboCurrentValue = ^^;", 1, 0, 10001 );
         } 

         //:END
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:// See if a list entity has been specified, and if so, use it.
         //:IF vEntity.CtrlMapLOD_Entity EXISTS
         lTempInteger_11 = CheckExistenceOfEntity( vEntity, "CtrlMapLOD_Entity" );
         if ( lTempInteger_11 == 0 )
         { 
            //:szListEntityName = vEntity.CtrlMapLOD_Entity.Name
            GetVariableFromAttribute( szListEntityName, 0, 'S', 33, vEntity, "CtrlMapLOD_Entity", "Name", "", 0 );
            //:ELSE
         } 
         else
         { 
            //:szListEntityName = vList.CtrlMapRelatedEntity.Name
            GetVariableFromAttribute( szListEntityName, 0, 'S', 33, vList, "CtrlMapRelatedEntity", "Name", "", 0 );
         } 

         //:END

         //:// See if a scoping entity has been specified, and if so, use it.
         //:lSubtype = vDialog.Control.Subtype
         GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "Subtype" );
         //:lSubtype = IsFlagSequenceSet( lSubtype, zCOMBOBOX_SCOPE_OI )
         lSubtype = IsFlagSequenceSet( lSubtype, zCOMBOBOX_SCOPE_OI );
         //:IF lSubtype = 0
         if ( lSubtype == 0 )
         { 
            //:IF vScope.CtrlMapLOD_Entity EXISTS
            lTempInteger_12 = CheckExistenceOfEntity( vScope, "CtrlMapLOD_Entity" );
            if ( lTempInteger_12 == 0 )
            { 
               //:szScopingEntityName = vScope.CtrlMapLOD_Entity.Name
               GetVariableFromAttribute( szScopingEntityName, 0, 'S', 33, vScope, "CtrlMapLOD_Entity", "Name", "", 0 );
               //:ELSE
            } 
            else
            { 
               //:szScopingEntityName = ""
               ZeidonStringCopy( szScopingEntityName, 1, 0, "", 1, 0, 33 );
            } 

            //:END
         } 

         //:END

         //:szWriteBuffer = "      v" + szCtrlTag + ".CreateViewFromView( strSessionId, " + vList.CtrlMapView.Name + " );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".CreateViewFromView( strSessionId, ", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_19, 0, 'S', 33, vList, "CtrlMapView", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_19, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "      ComboCount = 0;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      ComboCount = 0;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "      strComboSelectedValue = ^0^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      strComboSelectedValue = ^0^;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:// Auto Include
         //:IF vDialog.Control.Subtype >= 20480 AND vDialog.Control.Subtype <= 21252   // IF Auto Include
         if ( CompareAttributeToInteger( vDialog, "Control", "Subtype", 20480 ) >= 0 && CompareAttributeToInteger( vDialog, "Control", "Subtype", 21252 ) <= 0 )
         { 
            //:szWriteBuffer = ""
            ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:// For Auto Include, we are automatically putting a blank entry as the first entry in the
            //:// combobox.  With this in mind, there is code in DoInputMapping that assumes the first
            //:// entry in a combobox is null (or blank).  What if the user doesn't want a blank entry?
            //:// and wants to use the "No null in list" checkbox in the painter.  I would need to
            //:// change this code but I'm not sure how because I can't tell from DoInputMapping what
            //:// the value of combobox.selectedindex[0] is, I only know they selected the index 0.
            //:szWriteBuffer = "      // For Auto Include, always add a null entry to the combo box.s"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      // For Auto Include, always add a null entry to the combo box.s", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      ComboCount++;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ComboCount++;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( strComboCurrentValue == null )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strComboCurrentValue == null )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "%>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         <option selected=^selected^ value=^^></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         <option selected=^selected^ value=^^></option>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "<%"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "%>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         <option value=^^></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         <option value=^^></option>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "<%"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         } 

         //:END

         //:IF lSubtype = 0
         if ( lSubtype == 0 )
         { 
            //:szWriteBuffer = "      nRC = v" + szCtrlTag + ".SetCursorFirst( strSessionId, ^" +
            //:                             szListEntityName + "^, ^" + szScopingEntityName + "^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = v", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorFirst( strSessionId, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szScopingEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "      nRC = v" + szCtrlTag + ".SetCursorScopeOI( strSessionId, ^" +
            //:                             szListEntityName + "^, 1 ); // first" // zPOS_FIRST
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = v", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorScopeOI( strSessionId, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 1 ); // first", 1, 0, 10001 );
         } 

         //:END

         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "      while ( nRC >= 0 )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      while ( nRC >= 0 )", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "      {"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:IF vList.CtrlMapLOD_Attribute EXISTS
         lTempInteger_13 = CheckExistenceOfEntity( vList, "CtrlMapLOD_Attribute" );
         if ( lTempInteger_13 == 0 )
         { 
            //:IF vList.CtrlMapContext EXISTS
            lTempInteger_14 = CheckExistenceOfEntity( vList, "CtrlMapContext" );
            if ( lTempInteger_14 == 0 )
            { 
               //:szContextName = vList.CtrlMapContext.Name
               GetVariableFromAttribute( szContextName, 0, 'S', 33, vList, "CtrlMapContext", "Name", "", 0 );
               //:ELSE
            } 
            else
            { 
               //:szContextName = ""
               ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );
            } 

            //:END

            //:szWriteBuffer = "         strErrorMapValue = v" + szCtrlTag +
            //:                ".GetStringFromAttributeByContext( strSessionId, ^" +
            //:                vList.CtrlMapRelatedEntity.Name + "^, ^" +
            //:                vList.CtrlMapER_Attribute.Name + "^, ^" +
            //:                szContextName + "^, 254 );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = v", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_20, 0, 'S', 33, vList, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_20, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_21, 0, 'S', 33, vList, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_21, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 254 );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         } 

         //:END


         //:// KJS 05/20/14 - There were some issues for auto include when the "list view" already had a blank entry, then
         //:// two blank entries were in the list and this caused errors. For auto include check if one of these entries is
         //:// blank, don't add it if it is.
         //:IF vDialog.Control.Subtype >= 20480 AND vDialog.Control.Subtype <= 21252   // IF Auto Include
         if ( CompareAttributeToInteger( vDialog, "Control", "Subtype", 20480 ) >= 0 && CompareAttributeToInteger( vDialog, "Control", "Subtype", 21252 ) <= 0 )
         { 
            //:szWriteBuffer = "         // For Auto Include, we have already created a blank entry for the combobox, check to make "
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         // For Auto Include, we have already created a blank entry for the combobox, check to make ", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         // we don't add another blank entry. That will cause errors. "
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         // we don't add another blank entry. That will cause errors. ", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         if ( !StringUtils.isBlank( strErrorMapValue ) )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( !StringUtils.isBlank( strErrorMapValue ) )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         } 

         //:END

         //:szWriteBuffer = "         if ( strComboCurrentValue.equals( strErrorMapValue ) )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strComboCurrentValue.equals( strErrorMapValue ) )", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         {"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "%>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "            <option selected=^selected^ value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option selected=^selected^ value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "<%"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "            strComboSelectedValue = Integer.toString( ComboCount );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            strComboSelectedValue = Integer.toString( ComboCount );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         }"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         else"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         else", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         {"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "%>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "            <option value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "<%"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         }"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

         //:IF vDialog.Control.Subtype >= 20480 AND vDialog.Control.Subtype <= 21252   // IF Auto Include
         if ( CompareAttributeToInteger( vDialog, "Control", "Subtype", 20480 ) >= 0 && CompareAttributeToInteger( vDialog, "Control", "Subtype", 21252 ) <= 0 )
         { 
            //:szWriteBuffer = "         } // if ( !StringUtils.isBlank( strErrorMapValue ) )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         } // if ( !StringUtils.isBlank( strErrorMapValue ) )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         } 

         //:END

         //:szWriteBuffer = "         ComboCount++;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         ComboCount++;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:IF lSubtype = 0
         if ( lSubtype == 0 )
         { 
            //:szWriteBuffer = "         nRC =  v" + szCtrlTag +
            //:                ".SetCursorNext( strSessionId, ^" + szListEntityName +
            //:                "^, ^" + szScopingEntityName + "^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC =  v", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorNext( strSessionId, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szScopingEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "         nRC =  v" + szCtrlTag +
            //:                ".SetCursorScopeOI( strSessionId, ^" + szListEntityName + "^, 3 ); // next" // zPOS_NEXT
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC =  v", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorScopeOI( strSessionId, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 3 ); // next", 1, 0, 10001 );
         } 

         //:END

         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:DropView( vList )
         DropView( vList );
         //:DropView( vEntity )
         DropView( vEntity );
         //:DropView( vScope )
         DropView( vScope );
      } 

      //:END

      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:szWriteBuffer = "      v" + szCtrlTag + ".DropView( strSessionId );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".DropView( strSessionId );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "</select>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "</select>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "<input name=^h" + szCtrlTag + "^ id=^h" + szCtrlTag + "^ type=^hidden^ value=^<%=strComboSelectedValue%>^ >"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input name=^h", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^h", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ type=^hidden^ value=^<%=strComboSelectedValue%>^ >", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   } 

   //:END
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteEditBox( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                    INTEGER          lFile,
//:                    STRING ( 10000 ) szWriteBuffer,
//:                    STRING ( 50 )    szIndent,
//:                    STRING ( 32 )    szCtrlTag,
//:                    STRING ( 1 )     szTableRowFlag,
//:                    STRING ( 20 )    szJustify,
//:                    STRING ( 1 )     szNoPositioning,
//:                    INTEGER          lOffsetX,
//:                    INTEGER          lOffsetY )

//:   // Format an EDITBOX control.

//:   VIEW vDialogRoot BASED ON LOD TZWDLGSO
zOPER_EXPORT zSHORT OPERATION
GenJSP_CrteEditBox( zVIEW     vDialog,
                    zLONG     lFile,
                    zPCHAR    szWriteBuffer,
                    zPCHAR    szIndent,
                    zPCHAR    szCtrlTag,
                    zPCHAR    szTableRowFlag,
                    zPCHAR    szJustify,
                    zPCHAR    szNoPositioning,
                    zLONG     lOffsetX,
                    zLONG     lOffsetY )
{
   zVIEW     vDialogRoot = 0; 
   //:STRING ( 32 )  szContextName
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 300 ) szValue
   zCHAR     szValue[ 301 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 64 )  szType
   zCHAR     szType[ 65 ] = { 0 }; 
   //:STRING ( 64 )  szWidget
   zCHAR     szWidget[ 65 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 50 )  szEditActionCode
   zCHAR     szEditActionCode[ 51 ] = { 0 }; 
   //:STRING ( 32 )  szActionName
   zCHAR     szActionName[ 33 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLth
   zCHAR     szMaxStringLth[ 11 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:STRING ( 1 )   szWCP_Hidden
   zCHAR     szWCP_Hidden[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szCreateSessionVariable
   zCHAR     szCreateSessionVariable[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szNoOutputMapping
   zCHAR     szNoOutputMapping[ 2 ] = { 0 }; 
   //:INTEGER        lMaxStringLth
   zLONG     lMaxStringLth = 0; 
   //:INTEGER        lStyleX
   zLONG     lStyleX = 0; 
   //:INTEGER        lTemp
   zLONG     lTemp = 0; 
   //:SHORT          bMapping
   zSHORT    bMapping = 0; 
   //:SHORT          nRC
   zSHORT    nRC = 0; 

   //:// For testing no height on input boxes
   //:STRING ( 10 )  szWidth
   zCHAR     szWidth[ 11 ] = { 0 }; 
   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   //:STRING ( 100 )  szSize
   zCHAR     szSize[ 101 ] = { 0 }; 
   //:STRING ( 100 )  szPosition
   zCHAR     szPosition[ 101 ] = { 0 }; 
   zLONG     lTempInteger_0; 
   zSHORT    RESULT; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 
   zCHAR     szTempString_12[ 33 ]; 
   zCHAR     szTempString_13[ 33 ]; 
   zCHAR     szTempString_14[ 255 ]; 
   zSHORT    lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zCHAR     szTempString_15[ 255 ]; 


   //:CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );
   //://CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "<%=strErrorColor%>" )
   //:// KJS 07/08 - We placed DOCTYPE at the top of our html pages now.  For some reason, because of this
   //:// even though the pixel height is exactly the same as before, it shows up higher in the browser.
   //:// Because of this we have taken out the height for now and the input height will be determined in the
   //:// CSS.
   //:PIX_PER_DU( vDialog, dDLUnits )
   PIX_PER_DU( vDialog, &dDLUnits );
   //:zIntegerToString( szWidth, 10, vDialog.Control.SZDLG_X * dDLUnits )
   GetIntegerFromAttribute( &lTempInteger_0, vDialog, "Control", "SZDLG_X" );
   zIntegerToString( szWidth, 10, lTempInteger_0 * dDLUnits );
   //:szSize = "width:" + szWidth + "px;"
   ZeidonStringCopy( szSize, 1, 0, "width:", 1, 0, 101 );
   ZeidonStringConcat( szSize, 1, 0, szWidth, 1, 0, 101 );
   ZeidonStringConcat( szSize, 1, 0, "px;", 1, 0, 101 );
   //:// If zNoPositioning is null then we are using absolute positioning for controls
   //:IF  szNoPositioning = ""
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:CreateAbsolPosString( vDialog, szPosition, lOffsetX, lOffsetY )
      CreateAbsolPosString( vDialog, szPosition, lOffsetX, lOffsetY );
   } 

   //:END

   //:FixStyleString( szStyle, szSize, szPosition,  "<%=strErrorColor%>"  )
   FixStyleString( szStyle, szSize, szPosition, "<%=strErrorColor%>" );

   //:szStyle = szStyle + szTabIndex
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );

   //:// If there is a WebControlProperty for "Create Session Variable", then create a session variable
   //:// with the value of this edit box with the Control Tag as the name.
   //:szCreateSessionVariable = ""
   ZeidonStringCopy( szCreateSessionVariable, 1, 0, "", 1, 0, 2 );
   //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Create Session Variable"
   RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Create Session Variable", "" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szCreateSessionVariable = "Y"
      ZeidonStringCopy( szCreateSessionVariable, 1, 0, "Y", 1, 0, 2 );
   } 

   //:END

   //:// There may be times when we do not want to show the mapping of a field.  Like for instance a password field.  If the user types
   //:// in the wrong password, then we don't want to leave what was already typed we want the edit box to be blank.  This is
   //:// for xss problems (cross-scripting attacks).
   //:szNoOutputMapping = ""
   ZeidonStringCopy( szNoOutputMapping, 1, 0, "", 1, 0, 2 );
   //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "No Output Mapping"
   RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "No Output Mapping", "" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szNoOutputMapping = "Y"
      ZeidonStringCopy( szNoOutputMapping, 1, 0, "Y", 1, 0, 2 );
   } 

   //:END

   //:// szWriteBuffer = "<% strErrorMapValue = ^^; %>"  extraneous???
   //:// WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )           dks 2005.01.11

   //:SET CURSOR FIRST vDialog.CtrlMapLOD_Attribute WITHIN vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "CtrlMapLOD_Attribute", "Control" );
   //:IF RESULT >= zCURSOR_SET AND szNoOutputMapping = ""
   if ( RESULT >= zCURSOR_SET && ZeidonStringCompare( szNoOutputMapping, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:bMapping = 1
      bMapping = 1;
      //:szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   strErrorMapValue = vAppSubtask.CheckError( strSessionId, ^" + szCtrlTag + "^, strErrorTitle );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = vAppSubtask.CheckError( strSessionId, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, strErrorTitle );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( strErrorMapValue.length( ) > 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( strErrorMapValue.length( ) > 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      strErrorColor = ^color:red;^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strErrorColor = ^color:red;^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      strErrorColor = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strErrorColor = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".GetView( strSessionId, ^" +
      //:                vDialog.CtrlMapView.Name + "^, vAppSubtask );"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( nRC <= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC <= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         " + vDialog.CtrlMapView.Name +
      //:                ".TraceLine( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         nRC = " + vDialog.CtrlMapView.Name +
      //:                ".CheckExistenceOfEntity( strSessionId, ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         if ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( nRC >= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:IF vDialog.CtrlMapContext EXISTS
      lTempInteger_1 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
      if ( lTempInteger_1 == 0 )
      { 
         //:szContextName = vDialog.CtrlMapContext.Name
         GetVariableFromAttribute( szContextName, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
         //:ELSE
      } 
      else
      { 
         //:szContextName = ""
         ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );
      } 

      //:END

      //:lMaxStringLth = vDialog.CtrlMapER_Domain.MaxStringLth
      GetIntegerFromAttribute( &lMaxStringLth, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
      //:IF lMaxStringLth <= 0
      if ( lMaxStringLth <= 0 )
      { 
         //:szMaxStringLth = "254"
         ZeidonStringCopy( szMaxStringLth, 1, 0, "254", 1, 0, 11 );
         //:ELSE
      } 
      else
      { 
         //:szMaxStringLth = lMaxStringLth
         ZeidonStringConvertFromNumber( szMaxStringLth, 1, 0, 10, lMaxStringLth, (ZDecimal) 0.0, "I" );
      } 

      //:END

      //:szWriteBuffer = "            strErrorMapValue = " +
      //:                vDialog.CtrlMapView.Name + ".GetStringFromAttributeByContext( strSessionId, ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^, ^" +
      //:                szContextName + "^, " + szMaxStringLth + " );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            strErrorMapValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szMaxStringLth, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            " + vDialog.CtrlMapView.Name +
      //:                ".TraceLine( ^" + vDialog.CtrlMapRelatedEntity.Name + "." +
      //:                vDialog.CtrlMapER_Attribute.Name + ": ^, strErrorMapValue );"
      GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^, strErrorMapValue );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:// If there is a WebControlProperty for "Create Session Variable", then create a session variable
      //:// with the value of this edit box with the Control Tag as the name.
      //:IF szCreateSessionVariable = "Y"
      if ( ZeidonStringCompare( szCreateSessionVariable, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 
         //:szWriteBuffer = "            session.setAttribute(^" + szCtrlTag + "^, strErrorMapValue); "
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            session.setAttribute(^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, strErrorMapValue); ", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      } 

      //:END
      //:szWriteBuffer = "         }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            " + vDialog.CtrlMapView.Name +
      //:                ".TraceLine( ^Entity does not exist: ^, ^" +
      //:                vDialog.CtrlMapView.Name +
      //:                "." + vDialog.CtrlMapRelatedEntity.Name + "^ );"
      GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Entity does not exist: ^, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_12, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );

      //:lStyleX = vDialog.Control.ExtendedStyle
      GetIntegerFromAttribute( &lStyleX, vDialog, "Control", "ExtendedStyle" );
      //:lTemp = IsFlagSequenceSet( lStyleX, zCONTROLX_PREFILL )
      lTemp = IsFlagSequenceSet( lStyleX, zCONTROLX_PREFILL );
      //:IF lTemp != 0
      if ( lTemp != 0 )
      { 
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         //:szWriteBuffer = "      if ( strErrorMapValue.length( ) == 0 )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strErrorMapValue.length( ) == 0 )", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         strErrorMapValue = ^" + vDialog.Control.Text + "^;"
         GetVariableFromAttribute( szTempString_14, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
      } 

      //:END
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:ELSE
   } 
   else
   { 
      //:bMapping = 0
      bMapping = 0;
   } 

   //:END

   //://KJS 07/25/07
   //://See if there is a WebControlProperty for "Hidden"
   //://I don't think "hidden" is a webcontrolproperty for the editbox yet
   //://but since I don't think this hurts I'm going to keep it in.
   //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Hidden"
   RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Hidden", "" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szWCP_Hidden = "Y"
      ZeidonStringCopy( szWCP_Hidden, 1, 0, "Y", 1, 0, 2 );
      //:ELSE
   } 
   else
   { 
      //:szWCP_Hidden = "N"
      ZeidonStringCopy( szWCP_Hidden, 1, 0, "N", 1, 0, 2 );
   } 

   //:END

   //:IF vDialog.Control.WebCtrlType = "Hidden" OR szWCP_Hidden = "Y"
   if ( CompareAttributeToString( vDialog, "Control", "WebCtrlType", "Hidden" ) == 0 || ZeidonStringCompare( szWCP_Hidden, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szType = " type=^hidden^ "
      ZeidonStringCopy( szType, 1, 0, " type=^hidden^ ", 1, 0, 65 );
      //:ELSE
   } 
   else
   { 
      //://IF vDialog.CtrlMapER_Domain EXISTS AND vDialog.CtrlMapER_Domain.Name = "Password"
      //:IF vDialog.CtrlMapER_Domain EXISTS AND vDialog.Control.Subtype = 4
      lTempInteger_2 = CheckExistenceOfEntity( vDialog, "CtrlMapER_Domain" );
      if ( lTempInteger_2 == 0 && CompareAttributeToInteger( vDialog, "Control", "Subtype", 4 ) == 0 )
      { 
         //:szType = " type=^password^ "
         ZeidonStringCopy( szType, 1, 0, " type=^password^ ", 1, 0, 65 );
         //:ELSE
      } 
      else
      { 
         //:szType = " type=^text^ "
         ZeidonStringCopy( szType, 1, 0, " type=^text^ ", 1, 0, 65 );
      } 

      //:END
   } 

   //:END

   //:// If there is an Event for the EditBox, build code to insert in <input statement.
   //:szEditActionCode = ""
   ZeidonStringCopy( szEditActionCode, 1, 0, "", 1, 0, 51 );
   //:IF vDialog.EventAct EXISTS
   lTempInteger_3 = CheckExistenceOfEntity( vDialog, "EventAct" );
   if ( lTempInteger_3 == 0 )
   { 
      //:szActionName = vDialog.EventAct.Tag
      GetVariableFromAttribute( szActionName, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
      //:IF vDialog.Event.Type = 16
      if ( CompareAttributeToInteger( vDialog, "Event", "Type", 16 ) == 0 )
      { 
         //:szEditActionCode = " onfocus=^" + szActionName + "()^ "
         ZeidonStringCopy( szEditActionCode, 1, 0, " onfocus=^", 1, 0, 51 );
         ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 51 );
         ZeidonStringConcat( szEditActionCode, 1, 0, "()^ ", 1, 0, 51 );
         //:ELSE
      } 
      else
      { 
         //:IF vDialog.Event.Type = 17
         if ( CompareAttributeToInteger( vDialog, "Event", "Type", 17 ) == 0 )
         { 
            //:szEditActionCode = " onblur=^" + szActionName + "()^ "
            ZeidonStringCopy( szEditActionCode, 1, 0, " onblur=^", 1, 0, 51 );
            ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 51 );
            ZeidonStringConcat( szEditActionCode, 1, 0, "()^ ", 1, 0, 51 );
            //:ELSE
         } 
         else
         { 
            //:IF vDialog.Event.Type = 18
            if ( CompareAttributeToInteger( vDialog, "Event", "Type", 18 ) == 0 )
            { 
               //:szEditActionCode = " onchange=^" + szActionName + "()^ "
               ZeidonStringCopy( szEditActionCode, 1, 0, " onchange=^", 1, 0, 51 );
               ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 51 );
               ZeidonStringConcat( szEditActionCode, 1, 0, "()^ ", 1, 0, 51 );
               //:ELSE
            } 
            else
            { 
               //:IF vDialog.Event.Type = 21
               if ( CompareAttributeToInteger( vDialog, "Event", "Type", 21 ) == 0 )
               { 
                  //:szEditActionCode = " onkeydown=^" + szActionName + "()^ "
                  ZeidonStringCopy( szEditActionCode, 1, 0, " onkeydown=^", 1, 0, 51 );
                  ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 51 );
                  ZeidonStringConcat( szEditActionCode, 1, 0, "()^ ", 1, 0, 51 );
                  //:ELSE
               } 
               else
               { 
                  //:IF vDialog.Event.Type = 22
                  if ( CompareAttributeToInteger( vDialog, "Event", "Type", 22 ) == 0 )
                  { 
                     //:szEditActionCode = " onkeyup=^" + szActionName + "()^ "
                     ZeidonStringCopy( szEditActionCode, 1, 0, " onkeyup=^", 1, 0, 51 );
                     ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 51 );
                     ZeidonStringConcat( szEditActionCode, 1, 0, "()^ ", 1, 0, 51 );
                     //:ELSE
                  } 
                  else
                  { 
                     //:IF vDialog.Event.Type = 24
                     if ( CompareAttributeToInteger( vDialog, "Event", "Type", 24 ) == 0 )
                     { 
                        //:szEditActionCode = " onclick=^" + szActionName + "()^ "
                        ZeidonStringCopy( szEditActionCode, 1, 0, " onclick=^", 1, 0, 51 );
                        ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 51 );
                        ZeidonStringConcat( szEditActionCode, 1, 0, "()^ ", 1, 0, 51 );
                     } 

                     //:END
                  } 

                  //:END
               } 

               //:END
            } 

            //:END
         } 

         //:END
      } 

      //:END
      //:ELSE
   } 
   else
   { 
      //:// If there is a Default button for the window, we must add some characters
      //:// to the end of the input statement.
      //:CreateViewFromView( vDialogRoot, vDialog )
      CreateViewFromView( &vDialogRoot, vDialog );
      //:nRC = ResetViewFromSubobject( vDialogRoot )
      nRC = ResetViewFromSubobject( vDialogRoot );
      //:LOOP WHILE nRC = 0
      while ( nRC == 0 )
      { 
         //:nRC = ResetViewFromSubobject( vDialogRoot )
         nRC = ResetViewFromSubobject( vDialogRoot );
      } 

      //:END
      //:IF vDialogRoot.Window.DfltButton != ""
      if ( CompareAttributeToString( vDialogRoot, "Window", "DfltButton", "" ) != 0 )
      { 
         //:szEditActionCode = " onKeyPress=^return _OnEnter( event )^"
         ZeidonStringCopy( szEditActionCode, 1, 0, " onKeyPress=^return _OnEnter( event )^", 1, 0, 51 );
         //:ELSE
      } 
      else
      { 
         //:szEditActionCode = ""
         ZeidonStringCopy( szEditActionCode, 1, 0, "", 1, 0, 51 );
      } 

      //:END
      //:DropView( vDialogRoot )
      DropView( vDialogRoot );
   } 

   //:END

   //:IF szNoOutputMapping = "Y"
   if ( ZeidonStringCompare( szNoOutputMapping, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:szValue = "value=^^"
      ZeidonStringCopy( szValue, 1, 0, "value=^^", 1, 0, 301 );
      //:ELSE
   } 
   else
   { 
      //:lStyleX = vDialog.Control.ExtendedStyle
      GetIntegerFromAttribute( &lStyleX, vDialog, "Control", "ExtendedStyle" );
      //:lTemp = IsFlagSequenceSet( lStyleX, zCONTROLX_PREFILL )
      lTemp = IsFlagSequenceSet( lStyleX, zCONTROLX_PREFILL );
      //:IF lTemp != 0 AND bMapping = 0
      if ( lTemp != 0 && bMapping == 0 )
      { 
         //:szValue = "value=^" + vDialog.Control.Text + "^"
         GetVariableFromAttribute( szTempString_15, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
         ZeidonStringCopy( szValue, 1, 0, "value=^", 1, 0, 301 );
         ZeidonStringConcat( szValue, 1, 0, szTempString_15, 1, 0, 301 );
         ZeidonStringConcat( szValue, 1, 0, "^", 1, 0, 301 );
         //:ELSE
      } 
      else
      { 
         //:szValue = "value=^<%=strErrorMapValue%>^"
         ZeidonStringCopy( szValue, 1, 0, "value=^<%=strErrorMapValue%>^", 1, 0, 301 );
      } 

      //:END
   } 

   //:END

   //://KJS 10/19/07 - Added title.
   //://If we put a title on the control, when the mouse is hovered over the control, this text will display.
   //:szTitleHTML = ""
   ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
   //:szTitle = vDialog.Control.DIL_Text
   GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
   //:IF szTitle != ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
   { 
      //:szTitleHTML = " title=^" + szTitle + "^"
      ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^", 1, 0, 257 );
   } 

   //:END
   //:// dks 2016.04.08 - trying placeholder
   //:szTitle = vDialog.Control.Placeholder
   GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "Placeholder", "", 0 );
   //:IF szTitle != ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
   { 
      //:szTitleHTML = szTitleHTML + " placeholder=^" + szTitle + "^"
      ZeidonStringConcat( szTitleHTML, 1, 0, " placeholder=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^", 1, 0, 257 );
   } 

   //:END
   //:// Doug and I both added a placeholder attribute. Not sure what to do since I know that Aadit uses WebPlaceholder.
   //:IF szTitle = ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) == 0 )
   { 
      //:szTitle = vDialog.Control.WebPlaceholder
      GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "WebPlaceholder", "", 0 );
      //:IF szTitle != ""
      if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
      { 
         //:szTitleHTML = szTitleHTML + " placeholder=^" + szTitle + "^"
         ZeidonStringConcat( szTitleHTML, 1, 0, " placeholder=^", 1, 0, 257 );
         ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
         ZeidonStringConcat( szTitleHTML, 1, 0, "^", 1, 0, 257 );
      } 

      //:END
   } 

   //:END

   //:CreateDisabledString( vDialog, szDisabled )
   CreateDisabledString( vDialog, szDisabled );
   //:szClass = vDialog.Control.CSS_Class
   GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
   //:IF szClass = ""
   if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
   { 
      //:szWriteBuffer = "<input name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " + szDisabled + szTitleHTML + szStyle + szType +
      //:                szValue + szEditActionCode + " >"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szType, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szValue, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szEditActionCode, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " >", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "<input class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " + szDisabled +
      //:                szTitleHTML + szStyle + szType + szValue + szEditActionCode + " >"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input class=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szType, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szValue, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szEditActionCode, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " >", 1, 0, 10001 );
   } 

   //:END
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return( 0 );
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteCheckBox( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 20 )    szJustify,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY )

//:   // Format an CHECKBOX control.
//:   STRING ( 256 ) szStyle
zOPER_EXPORT zSHORT OPERATION
GenJSP_CrteCheckBox( zVIEW     vDialog,
                     zLONG     lFile,
                     zPCHAR    szWriteBuffer,
                     zPCHAR    szIndent,
                     zPCHAR    szCtrlTag,
                     zPCHAR    szTableRowFlag,
                     zPCHAR    szJustify,
                     zPCHAR    szNoPositioning,
                     zLONG     lOffsetX,
                     zLONG     lOffsetY )
{
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:STRING ( 100 ) szPosition
   zCHAR     szPosition[ 101 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 20 )  szSpaces
   zCHAR     szSpaces[ 21 ] = { 0 }; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 51 ]; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_9[ 51 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 51 ]; 
   zCHAR     szTempString_12[ 255 ]; 
   zCHAR     szTempString_13[ 255 ]; 


   //:szWriteBuffer = "<%   strErrorMapValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%   strErrorMapValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

   //:IF vDialog.CtrlMapView EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( vDialog, "CtrlMapView" );
   if ( lTempInteger_0 == 0 )
   { 
      //:szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name +
      //:                ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name + "^, vAppSubtask );"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( nRC <= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC <= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name +
      //:                ".TraceLine( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name +
      //:                ".CheckExistenceOfEntity( strSessionId, ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         strRadioGroupValue = " +
      //:                vDialog.CtrlMapView.Name + ".GetString( strSessionId, ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^ );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strRadioGroupValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetString( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:szWriteBuffer = "   if ( strRadioGroupValue.equals( ^" +
   //:                vDialog.Control.RadioOrCheckboxValue + "^ ) )"
   GetVariableFromAttribute( szTempString_8, 0, 'S', 51, vDialog, "Control", "RadioOrCheckboxValue", "", 0 );
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( strRadioGroupValue.equals( ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      strErrorMapValue = ^checked=\^checked\^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      strErrorMapValue = ^checked=\\^checked\\^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );

   //:// If this window is being generated with no positioning then
   //:// do not create the position in the style.
   //:IF  szNoPositioning = ""
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:CreateAbsolPosString( vDialog, szPosition, lOffsetX, lOffsetY )
      CreateAbsolPosString( vDialog, szPosition, lOffsetX, lOffsetY );
   } 

   //:END

   //:IF vDialog.Control.VisibleBorder = "Y"
   if ( CompareAttributeToString( vDialog, "Control", "VisibleBorder", "Y" ) == 0 )
   { 
      //:szPosition = szPosition + "border:'2px solid';border-style:'groove';"
      ZeidonStringConcat( szPosition, 1, 0, "border:'2px solid';border-style:'groove';", 1, 0, 101 );
   } 

   //:END

   //:szStyle = "style=^" + szPosition + "^" + szTabIndex
   ZeidonStringCopy( szStyle, 1, 0, "style=^", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szPosition, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "^", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );

   //:CreateDisabledString( vDialog, szDisabled )
   CreateDisabledString( vDialog, szDisabled );

   //://If we put a title on the control, when the mouse is hovered over the control, this text will display.
   //:szTitleHTML = ""
   ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
   //:szTitle = vDialog.Control.DIL_Text
   GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
   //:IF szTitle = ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) == 0 )
   { 
      //:szTitleHTML = ""
      ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
      //:ELSE
   } 
   else
   { 
      //:szTitleHTML = " title=^" + szTitle + "^ "
      ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //:IF vDialog.EventAct EXISTS
   lTempInteger_1 = CheckExistenceOfEntity( vDialog, "EventAct" );
   if ( lTempInteger_1 == 0 )
   { 
      //:szWriteBuffer = "<input type=^checkbox^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " + szDisabled +
      //:                " value=^" + vDialog.Control.RadioOrCheckboxValue +
      //:                "^ <%=strErrorMapValue%> " + szTitleHTML + szStyle + " onclick=^" + vDialog.EventAct.Tag + "( )^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input type=^checkbox^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " value=^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_9, 0, 'S', 51, vDialog, "Control", "RadioOrCheckboxValue", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ <%=strErrorMapValue%> ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^>", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "<input type=^checkbox^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " + szDisabled +
      //:                " value=^" + vDialog.Control.RadioOrCheckboxValue +
      //:                "^ <%=strErrorMapValue%> " + szTitleHTML + szStyle + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input type=^checkbox^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " value=^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_11, 0, 'S', 51, vDialog, "Control", "RadioOrCheckboxValue", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ <%=strErrorMapValue%> ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   } 

   //:END
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

   //:// If this window is being generated with no positioning then
   //:// do not create the position in the style.
   //:IF  szNoPositioning = "Y"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:CreateNoPosStyleString( vDialog, szStyle, "" )
      CreateNoPosStyleString( vDialog, szStyle, "" );
      //:// If we aren't putting in absolute positioning, make sure that there is a little space between
      //:// the checkbox and the text.
      //:szSpaces = "&nbsp "
      ZeidonStringCopy( szSpaces, 1, 0, "&nbsp ", 1, 0, 21 );
      //:ELSE
   } 
   else
   { 
      //:CreateAbsolStyleString( vDialog, szStyle, 30 + lOffsetX, lOffsetY, "" )
      CreateAbsolStyleString( vDialog, szStyle, 30 + lOffsetX, lOffsetY, "" );
      //:szSpaces = ""
      ZeidonStringCopy( szSpaces, 1, 0, "", 1, 0, 21 );
   } 

   //:END
   //:szClass = vDialog.Control.CSS_Class
   GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );

   //:IF szClass = ""
   if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
   { 
      //:szWriteBuffer = "<span " + szTitleHTML + szStyle + ">" + szSpaces + vDialog.Control.Text + "</span>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<span ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szSpaces, 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_12, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "</span>", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "<span class=^" + szClass + "^ " + szTitleHTML + szStyle + ">" + szSpaces + vDialog.Control.Text + "</span>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<span class=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szSpaces, 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_13, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "</span>", 1, 0, 10001 );
   } 

   //:END
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return( 0 );
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteCtrlsRadio( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                       INTEGER          lFile,
//:                       STRING ( 10000 ) szWriteBuffer,
//:                       STRING ( 50 )    szIndent,
//:                       STRING ( 32 )    szRadioGroupName,
//:                       STRING ( 1 )     szNoPositioning,
//:                       INTEGER          lOffsetX,
//:                       INTEGER          lOffsetY )

//:   STRING ( 256 ) szStyle
zOPER_EXPORT zSHORT OPERATION
GenJSP_CrteCtrlsRadio( zVIEW     vDialog,
                       zLONG     lFile,
                       zPCHAR    szWriteBuffer,
                       zPCHAR    szIndent,
                       zPCHAR    szRadioGroupName,
                       zPCHAR    szNoPositioning,
                       zLONG     lOffsetX,
                       zLONG     lOffsetY )
{
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szCtrlTag
   zCHAR     szCtrlTag[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:STRING ( 100 ) szPosition
   zCHAR     szPosition[ 101 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 32 )  szActionName
   zCHAR     szActionName[ 33 ] = { 0 }; 
   //:STRING ( 1 )   szFirstTimeThru
   zCHAR     szFirstTimeThru[ 2 ] = { 0 }; 
   //:INTEGER        nRC
   zLONG     nRC = 0; 
   //:INTEGER        LastY_Pos
   zLONG     LastY_Pos = 0; 
   zSHORT    lTempInteger_0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_0[ 51 ]; 
   zCHAR     szTempString_1[ 51 ]; 
   zCHAR     szTempString_2[ 51 ]; 
   zCHAR     szTempString_3[ 255 ]; 
   zCHAR     szTempString_4[ 255 ]; 


   //:LastY_Pos = 0
   LastY_Pos = 0;
   //:szFirstTimeThru = "Y"
   ZeidonStringCopy( szFirstTimeThru, 1, 0, "Y", 1, 0, 2 );
   //:IF vDialog.Control EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( vDialog, "Control" );
   if ( lTempInteger_0 == 0 )
   { 
      //:LastY_Pos = vDialog.Control.PSDLG_Y
      GetIntegerFromAttribute( &LastY_Pos, vDialog, "Control", "PSDLG_Y" );
   } 

   //:END
   //:szWriteBuffer = "   <table style=^margin:0px;padding:0px;^  name=^tbl" + szRadioGroupName + "^ id=tbl^" + szRadioGroupName + "^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <table style=^margin:0px;padding:0px;^  name=^tbl", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szRadioGroupName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=tbl^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szRadioGroupName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <tr style=^border:0px^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <tr style=^border:0px^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

   //:// Process the individual Radio Buttons for a Radio Button Group.
   //:FOR EACH vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:szActionName = ""
      ZeidonStringCopy( szActionName, 1, 0, "", 1, 0, 33 );
      //:IF vDialog.EventAct EXISTS
      lTempInteger_1 = CheckExistenceOfEntity( vDialog, "EventAct" );
      if ( lTempInteger_1 == 0 )
      { 
         //:szActionName = vDialog.EventAct.Tag
         GetVariableFromAttribute( szActionName, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
         //:nRC = zstrcmpi( szActionName, "alt-f4" )
         nRC = zstrcmpi( szActionName, "alt-f4" );
         //:IF nRC = 0
         if ( nRC == 0 )
         { 
            //:szActionName = "AltF4"
            ZeidonStringCopy( szActionName, 1, 0, "AltF4", 1, 0, 33 );
         } 

         //:END
      } 

      //:END

      //:szCtrlTag = vDialog.Control.Tag
      GetVariableFromAttribute( szCtrlTag, 0, 'S', 257, vDialog, "Control", "Tag", "", 0 );

      //:szWriteBuffer = "<% strErrorMapValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<% strErrorMapValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( strRadioGroupValue.equals( ^" +
      //:                         vDialog.Control.RadioOrCheckboxValue + "^ ) )"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 51, vDialog, "Control", "RadioOrCheckboxValue", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( strRadioGroupValue.equals( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ) )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      strErrorMapValue = ^checked=\^checked\^^;  %>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strErrorMapValue = ^checked=\\^checked\\^^;  %>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:CreateTabIndexString( vDialog, szTabIndex )
      CreateTabIndexString( vDialog, szTabIndex );

      //:// If this window is being generated with no positioning then
      //:// do not create the position in the style.
      //:IF  szNoPositioning = ""
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
      { 
         //:CreateAbsolPosString( vDialog, szPosition, lOffsetX, lOffsetY )
         CreateAbsolPosString( vDialog, szPosition, lOffsetX, lOffsetY );
      } 

      //:END
      //://CreateAbsolPosString( vDialog, szPosition, 0, 0 )
      //:CreateDisabledString( vDialog, szDisabled )
      CreateDisabledString( vDialog, szDisabled );
      //:FixStyleString( szStyle, szPosition, "", "" )
      FixStyleString( szStyle, szPosition, "", "" );

      //:// If LastY_Pos = -100 then this is the first time thru...
      //:IF ( ( LastY_Pos < vDialog.Control.PSDLG_Y ) )
      if ( ( CompareAttributeToInteger( vDialog, "Control", "PSDLG_Y", LastY_Pos ) > 0 ) )
      { 
         //:szWriteBuffer = "   </tr>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   </tr>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   <tr style=^border:0px^>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <tr style=^border:0px^>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:ELSE
      } 
      else
      { 
         //:// KJS 07/22/10 - Currently for relative positioning, the radio buttons are being created one right after the other
         //:// (on the same line), no matter how I paint them on the screen).  Really to look at that but since we hardly ever
         //:// use them, I am for a fast fix going to append "&nbsp&nbsp&nbsp" after each button, to give some spacing.
         //:IF szNoPositioning = "Y" AND szFirstTimeThru = "N"
         if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 && ZeidonStringCompare( szFirstTimeThru, 1, 0, "N", 1, 0, 2 ) == 0 )
         { 
            //:szWriteBuffer = "      <td nowrap style=^border:0px;^>&nbsp&nbsp&nbsp</td>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td nowrap style=^border:0px;^>&nbsp&nbsp&nbsp</td>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         } 

         //:END
      } 

      //:END

      //:szStyle = szStyle + szTabIndex
      ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );
      //:// szStyle = " style=^position:absolute;LEFT:" + szX + ";TOP:" + szY + ";^ "
      //:IF  szActionName != ""
      if ( ZeidonStringCompare( szActionName, 1, 0, "", 1, 0, 33 ) != 0 )
      { 
         //:szWriteBuffer = "      <td style=^width:15px;border:0px;^><input type=^radio^ name=^" + szRadioGroupName + "^ id=^" + szCtrlTag +
         //:                "^ value=^" + vDialog.Control.RadioOrCheckboxValue +
         //:                "^ <%=strErrorMapValue%> " + szStyle + szDisabled + " onclick=^" + szActionName + "( )^  ></td>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td style=^width:15px;border:0px;^><input type=^radio^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRadioGroupName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ value=^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_1, 0, 'S', 51, vDialog, "Control", "RadioOrCheckboxValue", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ <%=strErrorMapValue%> ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^  ></td>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "      <td style=^width:15px;border:0px;^><input type=^radio^ name=^" + szRadioGroupName + "^ id=^" + szCtrlTag +
         //:                "^ value=^" + vDialog.Control.RadioOrCheckboxValue +
         //:                "^ <%=strErrorMapValue%> " + szStyle + szDisabled + " ></td>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td style=^width:15px;border:0px;^><input type=^radio^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRadioGroupName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ value=^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_2, 0, 'S', 51, vDialog, "Control", "RadioOrCheckboxValue", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ <%=strErrorMapValue%> ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " ></td>", 1, 0, 10001 );
      } 

      //:END

      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:IF szNoPositioning = "Y"
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 
         //:CreateNoPosStyleString( vDialog, szStyle, "")
         CreateNoPosStyleString( vDialog, szStyle, "" );
         //:ELSE
      } 
      else
      { 
         //:CreateAbsolStyleString( vDialog, szStyle, 30 + lOffsetX, lOffsetY, "" )
         CreateAbsolStyleString( vDialog, szStyle, 30 + lOffsetX, lOffsetY, "" );
      } 

      //:END

      //://If we put a title on the control, when the mouse is hovered over the control, this text will display.
      //:szTitleHTML = ""
      ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
      //:szTitle = vDialog.Control.DIL_Text
      GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
      //:IF szTitle != ""
      if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
      { 
         //:szTitleHTML = " title=^" + szTitle + "^ "
         ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
         ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
         ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
      } 

      //:END

      //:szClass = vDialog.Control.CSS_Class
      GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
      //:IF szClass = ""
      if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
      { 
         //:szWriteBuffer = "      <td nowrap style=^border:0px;^><span " + szTitleHTML + ">" + vDialog.Control.Text + "</span></td>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td nowrap style=^border:0px;^><span ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_3, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</span></td>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "      <td nowrap style=^border:0px;^><span class=^" + szClass + "^ " + szTitleHTML + ">" + vDialog.Control.Text + "</span></td>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td nowrap style=^border:0px;^><span class=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_4, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</span></td>", 1, 0, 10001 );
      } 

      //:END

      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:LastY_Pos = vDialog.Control.PSDLG_Y
      GetIntegerFromAttribute( &LastY_Pos, vDialog, "Control", "PSDLG_Y" );
      //:szFirstTimeThru = "N"
      ZeidonStringCopy( szFirstTimeThru, 1, 0, "N", 1, 0, 2 );
      RESULT = SetCursorNextEntity( vDialog, "Control", "" );
   } 

   //:END
   //:szWriteBuffer = "   </tr>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   </tr>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   </table>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   </table>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   return( 0 );
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteText( VIEW vDialog      BASED ON LOD TZWDLGSO,
//:                 VIEW vGroupParent BASED ON LOD TZWDLGSO,
//:                 VIEW vDialogRoot  BASED ON LOD TZWDLGSO,
//:                 INTEGER          lFile,
//:                 STRING ( 10000 ) szWriteBuffer,
//:                 STRING ( 50 )    szIndent,
//:                 STRING ( 32 )    szCtrlTag,
//:                 STRING ( 20 )    szJustify,
//:                 STRING ( 1 )     szNoPositioning,
//:                 INTEGER          lOffsetX,
//:                 INTEGER          lOffsetY )

//:   // Format a TEXT control.

//:   STRING ( 32 )  szContextName
zOPER_EXPORT zSHORT OPERATION
GenJSP_CrteText( zVIEW     vDialog,
                 zVIEW     vGroupParent,
                 zVIEW     vDialogRoot,
                 zLONG     lFile,
                 zPCHAR    szWriteBuffer,
                 zPCHAR    szIndent,
                 zPCHAR    szCtrlTag,
                 zPCHAR    szJustify,
                 zPCHAR    szNoPositioning,
                 zLONG     lOffsetX,
                 zLONG     lOffsetY )
{
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClassHTML
   zCHAR     szClassHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 1000 ) szText
   zCHAR     szText[ 1001 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLth
   zCHAR     szMaxStringLth[ 11 ] = { 0 }; 
   //:STRING ( 20 )  szGroupParentType
   zCHAR     szGroupParentType[ 21 ] = { 0 }; 
   //:STRING ( 85 )  szHTMLCtrlID
   zCHAR     szHTMLCtrlID[ 86 ] = { 0 }; 
   //:INTEGER        lMaxStringLth
   zLONG     lMaxStringLth = 0; 
   //:INTEGER        lSubtypeX
   zLONG     lSubtypeX = 0; 
   //:INTEGER        lSubtype
   zLONG     lSubtype = 0; 
   //:INTEGER        lTemp
   zLONG     lTemp = 0; 
   //:SHORT          nMultiLineFlag
   zSHORT    nMultiLineFlag = 0; 
   //:SHORT          nBoldFlag
   zSHORT    nBoldFlag = 0; 
   //:SHORT          nItalicFlag
   zSHORT    nItalicFlag = 0; 
   //:SHORT          nStrikeoutFlag
   zSHORT    nStrikeoutFlag = 0; 
   //:SHORT          nUnderlineFlag
   zSHORT    nUnderlineFlag = 0; 
   //:INTEGER        lJustify
   zLONG     lJustify = 0; 
   //:INTEGER        lFontSize
   zLONG     lFontSize = 0; 
   //:INTEGER        lTextColor
   zLONG     lTextColor = 0; 
   //:INTEGER        lTextBkColor
   zLONG     lTextBkColor = 0; 
   //:INTEGER        lBorderStyle
   zLONG     lBorderStyle = 0; 
   //:INTEGER        lBorderColor
   zLONG     lBorderColor = 0; 
   //:INTEGER        lEscapement
   zLONG     lEscapement = 0; 
   //:INTEGER        lType
   zLONG     lType = 0; 
   //:STRING ( 32 )  szFaceName
   zCHAR     szFaceName[ 33 ] = { 0 }; 
   //:STRING ( 256 ) szDecoration
   zCHAR     szDecoration[ 257 ] = { 0 }; 
   //:STRING ( 1 )   szIsLabel
   zCHAR     szIsLabel[ 2 ] = { 0 }; 
   //:STRING ( 256 ) szLabelFor
   zCHAR     szLabelFor[ 257 ] = { 0 }; 
   //:SHORT          nRC
   zSHORT    nRC = 0; 
   zCHAR     szTempString_0[ 255 ]; 
   zSHORT    RESULT; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_12[ 33 ]; 
   zCHAR     szTempString_13[ 33 ]; 
   zCHAR     szTempString_14[ 33 ]; 
   zCHAR     szTempString_15[ 33 ]; 
   zCHAR     szTempString_16[ 33 ]; 
   zSHORT    lTempInteger_2; 
   zCHAR     szTempString_17[ 33 ]; 
   zCHAR     szTempString_18[ 33 ]; 
   zCHAR     szTempString_19[ 33 ]; 
   zCHAR     szTempString_20[ 33 ]; 
   zCHAR     szTempString_21[ 33 ]; 
   zCHAR     szTempString_22[ 33 ]; 
   zLONG     lTempInteger_3; 
   zCHAR     szTempString_23[ 255 ]; 
   zCHAR     szTempString_24[ 33 ]; 
   zCHAR     szTempString_25[ 255 ]; 


   //:szText = vDialog.Control.Text
   GetVariableFromAttribute( szText, 0, 'S', 1001, vDialog, "Control", "Text", "", 0 );
   //:CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );

   //:szHTMLCtrlID = " id=^" + szCtrlTag + "^ name=^" + szCtrlTag + "^ "
   ZeidonStringCopy( szHTMLCtrlID, 1, 0, " id=^", 1, 0, 86 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, szCtrlTag, 1, 0, 86 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, "^ name=^", 1, 0, 86 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, szCtrlTag, 1, 0, 86 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, "^ ", 1, 0, 86 );

   //:IF  szNoPositioning = "Y"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:CreateNoPosStyleString( vDialog, szStyle, "" )
      CreateNoPosStyleString( vDialog, szStyle, "" );
      //:ELSE
   } 
   else
   { 
      //:CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
      CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" );
   } 

   //:END

   //:nRC = TX_GetTextRptCtrlBOI( vDialog, nMultiLineFlag, nBoldFlag,
   //:                            nItalicFlag, nStrikeoutFlag,
   //:                            nUnderlineFlag, lJustify,
   //:                            lFontSize, lTextColor, lTextBkColor,
   //:                            lBorderStyle, lBorderColor,
   //:                            lEscapement, lType, szFaceName )
   nRC = TX_GetTextRptCtrlBOI( vDialog, &nMultiLineFlag, &nBoldFlag, &nItalicFlag, &nStrikeoutFlag, &nUnderlineFlag, &lJustify, &lFontSize, &lTextColor, &lTextBkColor, &lBorderStyle, &lBorderColor, &lEscapement, &lType, szFaceName );

   //:// If the return code is <= 0, the CtrlBOI is null.
   //:szDecoration = ""
   ZeidonStringCopy( szDecoration, 1, 0, "", 1, 0, 257 );
   //:IF nRC > 0
   if ( nRC > 0 )
   { 

      //:IF nItalicFlag != 0
      if ( nItalicFlag != 0 )
      { 
         //:szDecoration = szDecoration + "font-style:italic;"
         ZeidonStringConcat( szDecoration, 1, 0, "font-style:italic;", 1, 0, 257 );
      } 

      //:END

      //:IF nBoldFlag != 0
      if ( nBoldFlag != 0 )
      { 
         //:szDecoration = szDecoration + "font-weight:bold;"
         ZeidonStringConcat( szDecoration, 1, 0, "font-weight:bold;", 1, 0, 257 );
      } 

      //:END

      //:IF lJustify != 0
      if ( lJustify != 0 )
      { 
         //:nRC = IsFlagSequenceSet( lJustify, 2 )
         nRC = IsFlagSequenceSet( lJustify, 2 );
         //:IF nRC != 0
         if ( nRC != 0 )
         { 
            //:szDecoration = szDecoration + "text-align:center;"
            ZeidonStringConcat( szDecoration, 1, 0, "text-align:center;", 1, 0, 257 );
            //:ELSE
         } 
         else
         { 
            //:nRC = IsFlagSequenceSet( lJustify, 4 )
            nRC = IsFlagSequenceSet( lJustify, 4 );
            //:IF nRC != 0
            if ( nRC != 0 )
            { 
               //:szDecoration = szDecoration + "text-align:right;"
               ZeidonStringConcat( szDecoration, 1, 0, "text-align:right;", 1, 0, 257 );
            } 

            //:END
         } 

         //:END
      } 

      //:END

      //:IF nUnderlineFlag != 0 AND nStrikeoutFlag != 0
      if ( nUnderlineFlag != 0 && nStrikeoutFlag != 0 )
      { 
         //:szDecoration = szDecoration + "text-decoration:underline line-through;"
         ZeidonStringConcat( szDecoration, 1, 0, "text-decoration:underline line-through;", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:IF nUnderlineFlag != 0
         if ( nUnderlineFlag != 0 )
         { 
            //:szDecoration = szDecoration + "text-decoration:underline;"
            ZeidonStringConcat( szDecoration, 1, 0, "text-decoration:underline;", 1, 0, 257 );
         } 

         //:END

         //:IF nStrikeoutFlag != 0
         if ( nStrikeoutFlag != 0 )
         { 
            //:szDecoration = szDecoration + "text-decoration:line-through;"
            ZeidonStringConcat( szDecoration, 1, 0, "text-decoration:line-through;", 1, 0, 257 );
         } 

         //:END
      } 

      //:END
   } 

   //:END

   //://KJS 10/19/07 - Added title.
   //://If we put a title on the control, when the mouse is hovered over the control, this text will display.
   //:szTitleHTML = ""
   ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
   //:szTitle = vDialog.Control.DIL_Text
   GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
   //:IF szTitle != ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
   { 
      //:szTitleHTML = " title=^" + szTitle + "^ "
      ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //:zAppendQuotedString( szStyle, szDecoration, "style=", "^" )
   zAppendQuotedString( szStyle, szDecoration, "style=", "^" );
   //:szStyle = szStyle + szTabIndex
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );
   //:IF vDialog.Control.CSS_Class != ""
   if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) != 0 )
   { 
      //:szClassHTML = "class=^" + vDialog.Control.CSS_Class + "^ "
      GetVariableFromAttribute( szTempString_0, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClassHTML, 1, 0, "class=^", 1, 0, 257 );
      ZeidonStringConcat( szClassHTML, 1, 0, szTempString_0, 1, 0, 257 );
      ZeidonStringConcat( szClassHTML, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //:// Check if a Group control as parent of this control requests relative postioning either through the
   //:// older "Span" setting or the newer "RelativePos" request.
   //:szGroupParentType = ""
   ZeidonStringCopy( szGroupParentType, 1, 0, "", 1, 0, 21 );
   //:IF vGroupParent != 0
   if ( vGroupParent != 0 )
   { 
      //:// Override Style if parent group requests relative positioning
      //:// KJS 01/30/14 - I'm thinking "Relative Positioning" is old. I only use this in one pwd and when I take it
      //:// out and use "Div/No Height", the results look exactly the same so I am going to take this off grid controls.
      //:/*
      //:SET CURSOR FIRST vGroupParent.WebControlProperty WHERE vGroupParent.WebControlProperty.Name = "Relative Positioning"
      //:IF RESULT >= zCURSOR_SET
      //:   szGroupParentType = "RelativePos"
      //:ELSE
      //:   szGroupParentType = vGroupParent.Control.WebCtrlType
      //:END
      //:*/
      //:szGroupParentType = vGroupParent.Control.WebCtrlType
      GetVariableFromAttribute( szGroupParentType, 0, 'S', 21, vGroupParent, "Control", "WebCtrlType", "", 0 );
      //:IF szGroupParentType = "RelativePos" OR szGroupParentType = "Span"
      if ( ZeidonStringCompare( szGroupParentType, 1, 0, "RelativePos", 1, 0, 21 ) == 0 || ZeidonStringCompare( szGroupParentType, 1, 0, "Span", 1, 0, 21 ) == 0 )
      { 
         //:szStyle = "style=^position:relative;^"
         ZeidonStringCopy( szStyle, 1, 0, "style=^position:relative;^", 1, 0, 257 );
      } 

      //:END
   } 

   //:END

   //:// Process variable Text mapping.
   //:SET CURSOR FIRST vDialog.CtrlMap WHERE vDialog.CtrlMap.Tag = "Displayed Text"
   RESULT = SetCursorFirstEntityByString( vDialog, "CtrlMap", "Tag", "Displayed Text", "" );
   //:IF RESULT < zCURSOR_SET
   if ( RESULT < zCURSOR_SET )
   { 
      //:SET CURSOR FIRST vDialog.CtrlMapLOD_Attribute WITHIN vDialog.Control
      //:           WHERE vDialog.CtrlMap.Tag = ""
      RESULT = SetCursorFirstEntity( vDialog, "CtrlMapLOD_Attribute", "Control" );
      if ( RESULT > zCURSOR_UNCHANGED )
      { 
         while ( RESULT > zCURSOR_UNCHANGED && ( CompareAttributeToString( vDialog, "CtrlMap", "Tag", "" ) != 0 ) )
         { 
            RESULT = SetCursorNextEntity( vDialog, "CtrlMapLOD_Attribute", "Control" );
         } 

      } 

   } 

   //:END
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:// There is mapping of the Display Text value.
      //:szWriteBuffer = "<% strTextDisplayValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<% strTextDisplayValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name +
      //:                ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name + "^, vAppSubtask );"
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( nRC <= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC <= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name +
      //:         ".TraceLine( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".CheckExistenceOfEntity( strSessionId, ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:IF vDialog.CtrlMapContext EXISTS
      lTempInteger_0 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
      if ( lTempInteger_0 == 0 )
      { 
         //:szContextName = vDialog.CtrlMapContext.Name
         GetVariableFromAttribute( szContextName, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
         //:ELSE
      } 
      else
      { 
         //:szContextName = ""
         ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );
      } 

      //:END

      //:IF vDialog.CtrlMapER_Domain.DataType = "T" OR vDialog.CtrlMapER_Domain.DataType = "D"
      if ( CompareAttributeToString( vDialog, "CtrlMapER_Domain", "DataType", "T" ) == 0 || CompareAttributeToString( vDialog, "CtrlMapER_Domain", "DataType", "D" ) == 0 )
      { 
         //:szWriteBuffer = "         strTextDisplayValue = " +
         //:                vDialog.CtrlMapView.Name +
         //:                ".GetStringFromAttributeByContext( strSessionId, ^" +
         //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
         //:                vDialog.CtrlMapER_Attribute.Name + "^, ^" +
         //:                szContextName + "^, 20 );"
         GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strTextDisplayValue = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 20 );", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 

         //:lMaxStringLth = vDialog.CtrlMapER_Domain.MaxStringLth
         GetIntegerFromAttribute( &lMaxStringLth, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
         //:IF lMaxStringLth <= 0
         if ( lMaxStringLth <= 0 )
         { 
            //:szMaxStringLth = "254"
            ZeidonStringCopy( szMaxStringLth, 1, 0, "254", 1, 0, 11 );
            //:ELSE
         } 
         else
         { 
            //:szMaxStringLth = lMaxStringLth
            ZeidonStringConvertFromNumber( szMaxStringLth, 1, 0, 10, lMaxStringLth, (ZDecimal) 0.0, "I" );
         } 

         //:END

         //:szWriteBuffer = "         strTextDisplayValue = " +
         //:                vDialog.CtrlMapView.Name +
         //:                ".GetStringFromAttributeByContext( strSessionId, ^" +
         //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
         //:                vDialog.CtrlMapER_Attribute.Name + "^, ^" +
         //:                szContextName + "^, " + szMaxStringLth + " );"
         GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strTextDisplayValue = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMaxStringLth, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
      } 

      //:END

      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:szText = "<%=strTextDisplayValue%>"
      ZeidonStringCopy( szText, 1, 0, "<%=strTextDisplayValue%>", 1, 0, 1001 );
   } 


   //:END

   //:IF vDialog.EventAct EXISTS    // There is only one EventAct, which is HotText.
   lTempInteger_1 = CheckExistenceOfEntity( vDialog, "EventAct" );
   if ( lTempInteger_1 == 0 )
   { 
      //:IF vDialog.EventAct.Type = 45    // Type 45 is Hyperlink Action.
      if ( CompareAttributeToInteger( vDialog, "EventAct", "Type", 45 ) == 0 )
      { 
         //:// The Text triggers a Hyperlink to a constant or variable URL address
         //:SET CURSOR FIRST vDialog.CtrlMap WHERE vDialog.CtrlMap.Tag = "Hyperlink URL"
         RESULT = SetCursorFirstEntityByString( vDialog, "CtrlMap", "Tag", "Hyperlink URL", "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:// There is mapping of the Hyperlink URL value.
            //:szWriteBuffer = "<% strTextURL_Value = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<% strTextURL_Value = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name +
            //:                ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name + "^, vAppSubtask );"
            GetVariableFromAttribute( szTempString_12, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   if ( nRC <= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC <= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name +
            //:         ".TraceLine( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
            GetVariableFromAttribute( szTempString_14, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   else"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".CheckExistenceOfEntity( strSessionId, ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
            GetVariableFromAttribute( szTempString_15, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_15, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_16, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_16, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:IF vDialog.CtrlMapContext EXISTS
            lTempInteger_2 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
            if ( lTempInteger_2 == 0 )
            { 
               //:szContextName = vDialog.CtrlMapContext.Name
               GetVariableFromAttribute( szContextName, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
               //:ELSE
            } 
            else
            { 
               //:szContextName = ""
               ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );
            } 

            //:END

            //:IF vDialog.CtrlMapER_Domain.DataType = "T" OR vDialog.CtrlMapER_Domain.DataType = "D"
            if ( CompareAttributeToString( vDialog, "CtrlMapER_Domain", "DataType", "T" ) == 0 || CompareAttributeToString( vDialog, "CtrlMapER_Domain", "DataType", "D" ) == 0 )
            { 
               //:szWriteBuffer = "         strTextURL_Value = " +
               //:                vDialog.CtrlMapView.Name +
               //:                ".GetStringFromAttributeByContext( strSessionId, ^" +
               //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
               //:                vDialog.CtrlMapER_Attribute.Name + "^, ^" +
               //:                szContextName + "^, 20 );"
               GetVariableFromAttribute( szTempString_17, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         strTextURL_Value = ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_17, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_18, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_18, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_19, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_19, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 20 );", 1, 0, 10001 );
               //:ELSE
            } 
            else
            { 

               //:lMaxStringLth = vDialog.CtrlMapER_Domain.MaxStringLth
               GetIntegerFromAttribute( &lMaxStringLth, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
               //:IF lMaxStringLth <= 0
               if ( lMaxStringLth <= 0 )
               { 
                  //:szMaxStringLth = "254"
                  ZeidonStringCopy( szMaxStringLth, 1, 0, "254", 1, 0, 11 );
                  //:ELSE
               } 
               else
               { 
                  //:szMaxStringLth = lMaxStringLth
                  ZeidonStringConvertFromNumber( szMaxStringLth, 1, 0, 10, lMaxStringLth, (ZDecimal) 0.0, "I" );
               } 

               //:END

               //:szWriteBuffer = "         strTextURL_Value = " +
               //:                vDialog.CtrlMapView.Name +
               //:                ".GetStringFromAttributeByContext( strSessionId, ^" +
               //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
               //:                vDialog.CtrlMapER_Attribute.Name + "^, ^" +
               //:                szContextName + "^, " + szMaxStringLth + " );"
               GetVariableFromAttribute( szTempString_20, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         strTextURL_Value = ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_20, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_21, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_21, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_22, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_22, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szMaxStringLth, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
            } 

            //:END

            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "%>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = ""
            ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //://KJS 10/19/07 - Added title.

            //:// The Hyperlink URL value is a variable.
            //:   szWriteBuffer = "<a href=^<%=strTextURL_Value%>^  " + szClassHTML + szTitleHTML + szStyle + " target=^_blank^>" + szText + "</a>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<a href=^<%=strTextURL_Value%>^  ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " target=^_blank^>", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</a>", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 

            //:// The Hyperlink URL value is a constant in the Action.
            //:SET CURSOR FIRST vDialogRoot.Action WHERE vDialogRoot.Action.ZKey = vDialog.EventAct.ZKey
            GetIntegerFromAttribute( &lTempInteger_3, vDialog, "EventAct", "ZKey" );
            RESULT = SetCursorFirstEntityByInteger( vDialogRoot, "Action", "ZKey", lTempInteger_3, "" );
            //:IF vDialogRoot.Action.WebHTML_TransferAddress = ""
            if ( CompareAttributeToString( vDialogRoot, "Action", "WebHTML_TransferAddress", "" ) == 0 )
            { 
               //:MessageSend( vDialog, "", "XSL Generation",
               //:             "A Hyperlink Action without URL mapping requires a 'Link to HTML Address' value.",
               //:             zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
               MessageSend( vDialog, "", "XSL Generation", "A Hyperlink Action without URL mapping requires a 'Link to HTML Address' value.", zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
            } 

            //:END

            //:szWriteBuffer = ""
            ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //://KJS 10/19/07 - Added title.
            //:szWriteBuffer = "<a href=^" + vDialogRoot.Action.WebHTML_TransferAddress + "^  " + szClassHTML + szTitleHTML + szStyle + " target=^_blank^>" + szText + "</a>"
            GetVariableFromAttribute( szTempString_23, 0, 'S', 255, vDialogRoot, "Action", "WebHTML_TransferAddress", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<a href=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_23, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^  ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " target=^_blank^>", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</a>", 1, 0, 10001 );
         } 

         //:END
         //:ELSE
      } 
      else
      { 
         //:// This is HotText with regular Action, rather than HyperLink.
         //:szWriteBuffer = ""
         ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //://KJS 10/17/2007 Jeff says we need "javascript:" before the action name for href actions.  I think this
         //://is the place to put it but I confess I'm not exactly sure...
         //://KJS 10/19/07 - Added title.
         //://KJS 09/24/10 - Now realizing that Jeff was incorrect about the javascript: and it shouldn't be used (http://jibbering.com/faq/#FAQ4_24).
         //://Changing them to use the # and onclick.
         //:// szWriteBuffer = "<a href=^javascript:" + vDialog.EventAct.Tag + "( );^ class=^" + szClass + "^ " + szTitleHTML + szStyle + ">" + szText + "</a>"
         //:szWriteBuffer = "<a href=^#^ onclick=^" + vDialog.EventAct.Tag + "( );^ " + szClassHTML + szTitleHTML + szStyle + ">" + szText + "</a>"
         GetVariableFromAttribute( szTempString_24, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<a href=^#^ onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_24, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( );^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</a>", 1, 0, 10001 );
      } 

      //:END
      //:ELSE
   } 
   else
   { 
      //:// Regular Text Control (No HotText)


      //:// Check to see if this GroupBox has a WebControlProperty of "Table".  If so, then we will create this
      //:// as a table and try and position what is in this group box as a table.
      //:szIsLabel = ""
      ZeidonStringCopy( szIsLabel, 1, 0, "", 1, 0, 2 );
      //:szLabelFor = ""
      ZeidonStringCopy( szLabelFor, 1, 0, "", 1, 0, 257 );
      //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Label"
      RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Label", "" );
      //:IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:szIsLabel = "Y"
         ZeidonStringCopy( szIsLabel, 1, 0, "Y", 1, 0, 2 );
         //:IF vDialog.Control.WebCtrlLabelLink != ""
         if ( CompareAttributeToString( vDialog, "Control", "WebCtrlLabelLink", "" ) != 0 )
         { 
            //:// Tie the label to an input control.
            //:szLabelFor = " for=^" + vDialog.Control.WebCtrlLabelLink + "^ "
            GetVariableFromAttribute( szTempString_25, 0, 'S', 255, vDialog, "Control", "WebCtrlLabelLink", "", 0 );
            ZeidonStringCopy( szLabelFor, 1, 0, " for=^", 1, 0, 257 );
            ZeidonStringConcat( szLabelFor, 1, 0, szTempString_25, 1, 0, 257 );
            ZeidonStringConcat( szLabelFor, 1, 0, "^ ", 1, 0, 257 );
         } 

         //:END
      } 

      //:END

      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:// If there is a "Label" web control property than make this a label, otherwise, just use <span>.
      //:IF szIsLabel = "Y"
      if ( ZeidonStringCompare( szIsLabel, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 
         //:   szWriteBuffer = "<label " + szClassHTML + szHTMLCtrlID + szLabelFor + szTitleHTML + szStyle + ">" + szText + "</label>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<label ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szLabelFor, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</label>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "<span " + szClassHTML + szHTMLCtrlID + szTitleHTML + szStyle + ">" + szText + "</span>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<span ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</span>", 1, 0, 10001 );
      } 

      //:END
   } 

   //:END

   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return( 0 );
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteListBox( VIEW vDialog,
//:                    INTEGER lFile,
//:                    STRING ( 10000 ) szWriteBuffer,
//:                    STRING ( 50 )    szIndent,
//:                    STRING ( 32 )    szCtrlTag,
//:                    STRING ( 1 )     szNoPositioning,
//:                    INTEGER lOffsetX,
//:                    INTEGER lOffsetY )

//:   VIEW vScope  BASED ON LOD TZWDLGSO  // identifies scoping entity for list entries
zOPER_EXPORT zVOID OPERATION
GenJSP_CrteListBox( zVIEW     vDialog,
                    zLONG     lFile,
                    zPCHAR    szWriteBuffer,
                    zPCHAR    szIndent,
                    zPCHAR    szCtrlTag,
                    zPCHAR    szNoPositioning,
                    zLONG     lOffsetX,
                    zLONG     lOffsetY )
{
   zVIEW     vScope = 0; 
   //:STRING ( 32 )  szContextName
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 32 )  szScopingEntityName
   zCHAR     szScopingEntityName[ 33 ] = { 0 }; 
   //:STRING ( 32 )  szListEntityName
   zCHAR     szListEntityName[ 33 ] = { 0 }; 
   //:STRING ( 32 )  szAttributeName
   zCHAR     szAttributeName[ 33 ] = { 0 }; 
   //:STRING ( 32 )  szEntityName
   zCHAR     szEntityName[ 33 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) ListBoxDoubleClickAction
   zCHAR     ListBoxDoubleClickAction[ 257 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLth
   zCHAR     szMaxStringLth[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szWidth
   zCHAR     szWidth[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szSelectAction
   zCHAR     szSelectAction[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szSelectFunction
   zCHAR     szSelectFunction[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szHeight
   zCHAR     szHeight[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szX_Pos
   zCHAR     szX_Pos[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szY_Pos
   zCHAR     szY_Pos[ 11 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   //:INTEGER        lSubtype
   zLONG     lSubtype = 0; 
   //:INTEGER        lMaxStringLth
   zLONG     lMaxStringLth = 0; 
   zLONG     lTempInteger_0; 
   zLONG     lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_4; 
   zCHAR     szTempString_0[ 1026 ]; 
   zSHORT    lTempInteger_5; 
   zSHORT    lTempInteger_6; 
   zCHAR     szTempString_1[ 1026 ]; 
   zCHAR     szTempString_2[ 1026 ]; 
   zSHORT    lTempInteger_7; 
   zCHAR     szTempString_3[ 1026 ]; 
   zSHORT    lTempInteger_8; 
   zCHAR     szTempString_4[ 1026 ]; 
   zSHORT    lTempInteger_9; 
   zCHAR     szTempString_5[ 1026 ]; 


   //:szStyle = "width:" + szWidth + "px; height:" + szHeight + "px;"
   ZeidonStringCopy( szStyle, 1, 0, "width:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px; height:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
   //:szClass = vDialog.Control.CSS_Class
   GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );

   //://If we put a title on the control, when the mouse is hovered over the control, this text will display.
   //:szTitleHTML = ""
   ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
   //:szTitle = vDialog.Control.DIL_Text
   GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
   //:IF szTitle != ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
   { 
      //:szTitleHTML = " title=^" + szTitle + "^ "
      ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //:CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );
   //:// We will set the height to the constant 20 px.
   //:PIX_PER_DU( vDialog, dDLUnits )
   PIX_PER_DU( vDialog, &dDLUnits );
   //:zIntegerToString( szWidth, 10, vDialog.Control.SZDLG_X * dDLUnits )
   GetIntegerFromAttribute( &lTempInteger_0, vDialog, "Control", "SZDLG_X" );
   zIntegerToString( szWidth, 10, lTempInteger_0 * dDLUnits );
   //:zIntegerToString( szHeight, 10, vDialog.Control.SZDLG_Y * dDLUnits )
   GetIntegerFromAttribute( &lTempInteger_1, vDialog, "Control", "SZDLG_Y" );
   zIntegerToString( szHeight, 10, lTempInteger_1 * dDLUnits );
   //:szStyle = "style=^width:" + szWidth + "px;height:" + szHeight + "px;"
   ZeidonStringCopy( szStyle, 1, 0, "style=^width:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;height:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );

   //:// If szNoPositioning is null then we are using absolute positioning on controls.
   //:IF  szNoPositioning = ""
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
   { 

      //:zIntegerToString( szX_Pos, 10, vDialog.Control.PSDLG_X * dDLUnits )
      GetIntegerFromAttribute( &lTempInteger_2, vDialog, "Control", "PSDLG_X" );
      zIntegerToString( szX_Pos, 10, lTempInteger_2 * dDLUnits );
      //:zIntegerToString( szY_Pos, 10, vDialog.Control.PSDLG_Y * dDLUnits )
      GetIntegerFromAttribute( &lTempInteger_3, vDialog, "Control", "PSDLG_Y" );
      zIntegerToString( szY_Pos, 10, lTempInteger_3 * dDLUnits );
      //:szStyle = szStyle + "position:absolute;" + "left:" + szX_Pos + "px;" + "top:" + szY_Pos + "px;"
      ZeidonStringConcat( szStyle, 1, 0, "position:absolute;", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "left:", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, szX_Pos, 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "top:", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, szY_Pos, 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
   } 

   //:   //CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
   //:END

   //:szStyle = szStyle + "^ " + szTabIndex
   ZeidonStringConcat( szStyle, 1, 0, "^ ", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );

   //:szWriteBuffer = "<% strErrorMapValue = ^^;  %>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<% strErrorMapValue = ^^;  %>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:szSelectFunction = "OnClick"
   ZeidonStringCopy( szSelectFunction, 1, 0, "OnClick", 1, 0, 11 );


   //:   // Check if DoubleClick Event and Action exist and handle accordingly.
   //:   ListBoxDoubleClickAction = ""
   ZeidonStringCopy( ListBoxDoubleClickAction, 1, 0, "", 1, 0, 257 );
   //:   SET CURSOR FIRST vDialog.Event WHERE vDialog.Event.Type = 2
   RESULT = SetCursorFirstEntityByInteger( vDialog, "Event", "Type", 2, "" );
   //:   IF RESULT >= zCURSOR_SET AND vDialog.EventAct EXISTS
   lTempInteger_4 = CheckExistenceOfEntity( vDialog, "EventAct" );
   if ( RESULT >= zCURSOR_SET && lTempInteger_4 == 0 )
   { 
      //:   ListBoxDoubleClickAction = " ondblclick=^" + vDialog.EventAct.Tag + "( )^ "
      GetVariableFromAttribute( szTempString_0, 0, 'S', 1026, vDialog, "EventAct", "Tag", "", 0 );
      ZeidonStringCopy( ListBoxDoubleClickAction, 1, 0, " ondblclick=^", 1, 0, 257 );
      ZeidonStringConcat( ListBoxDoubleClickAction, 1, 0, szTempString_0, 1, 0, 257 );
      ZeidonStringConcat( ListBoxDoubleClickAction, 1, 0, "( )^ ", 1, 0, 257 );
   } 

   //:   END


   //:   // Set cursor to the scoping entity if one exists
   //:   CreateViewFromViewForTask( vScope, vDialog, 0 )
   CreateViewFromViewForTask( &vScope, vDialog, 0 );
   //:   SET CURSOR NEXT vScope.CtrlMap
   RESULT = SetCursorNextEntity( vScope, "CtrlMap", "" );

   //:   IF szClass = ""
   if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
   { 
      //:   szWriteBuffer = "<select name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^4^ " + szTitleHTML + szStyle + szDisabled + " onclick=^" +
      //:                   szCtrlTag + szSelectFunction + "( )^" + ListBoxDoubleClickAction + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<select name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^4^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectFunction, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ListBoxDoubleClickAction, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:   szWriteBuffer = "<select class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^4^ " + szTitleHTML + szStyle + szDisabled + " onclick=^" +
      //:                   szCtrlTag + szSelectFunction + "( )^" + ListBoxDoubleClickAction + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<select class=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^4^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectFunction, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ListBoxDoubleClickAction, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   } 

   //:   END
   //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:   szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:   IF vDialog.CtrlMapView EXISTS
   lTempInteger_5 = CheckExistenceOfEntity( vDialog, "CtrlMapView" );
   if ( lTempInteger_5 == 0 )
   { 


      //:   // See if a list entity has been specified, and if so, use it.
      //:   // Since this is a listbox I believe this should always be specified.
      //:   IF vDialog.CtrlMapLOD_Entity EXISTS
      lTempInteger_6 = CheckExistenceOfEntity( vDialog, "CtrlMapLOD_Entity" );
      if ( lTempInteger_6 == 0 )
      { 
         //:   szListEntityName = vDialog.CtrlMapLOD_Entity.Name
         GetVariableFromAttribute( szListEntityName, 0, 'S', 33, vDialog, "CtrlMapLOD_Entity", "Name", "", 0 );
      } 

      //:   END

      //:   szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name +
      //:                   ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name + "^, vAppSubtask );"
      GetVariableFromAttribute( szTempString_1, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_2, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "   if ( nRC > 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC > 0 )", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      strComboCurrentValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strComboCurrentValue = ^^;", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      zeidon.zView v" + szCtrlTag + " = new zeidon.zView( strSessionId );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      zeidon.zView v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = new zeidon.zView( strSessionId );", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:   szAttributeName = ""
      ZeidonStringCopy( szAttributeName, 1, 0, "", 1, 0, 33 );
      //:   szEntityName = ""
      ZeidonStringCopy( szEntityName, 1, 0, "", 1, 0, 33 );
      //:   szContextName = ""
      ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );

      //:   // Set position on the text field inside the listbox.
      //:   SetViewToSubobject( vDialog, "CtrlCtrl" )
      SetViewToSubobject( vDialog, "CtrlCtrl" );
      //:   IF vDialog.CtrlMapLOD_Attribute EXISTS
      lTempInteger_7 = CheckExistenceOfEntity( vDialog, "CtrlMapLOD_Attribute" );
      if ( lTempInteger_7 == 0 )
      { 

         //:   szAttributeName = vDialog.CtrlMapER_Attribute.Name
         GetVariableFromAttribute( szAttributeName, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
         //:   szEntityName = vDialog.CtrlMapRelatedEntity.Name
         GetVariableFromAttribute( szEntityName, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );

         //:   szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".CheckExistenceOfEntity( strSessionId, ^" +
         //:                   szEntityName + "^ );"
         GetVariableFromAttribute( szTempString_3, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "      if ( nRC >= 0 )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   IF vDialog.CtrlMapContext EXISTS
         lTempInteger_8 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
         if ( lTempInteger_8 == 0 )
         { 
            //:   szContextName = vDialog.CtrlMapContext.Name
            GetVariableFromAttribute( szContextName, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
         } 

         //:   END

         //:   lMaxStringLth = vDialog.CtrlMapER_Domain.MaxStringLth
         GetIntegerFromAttribute( &lMaxStringLth, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
         //:   IF lMaxStringLth <= 0
         if ( lMaxStringLth <= 0 )
         { 
            //:   szMaxStringLth = "254"
            ZeidonStringCopy( szMaxStringLth, 1, 0, "254", 1, 0, 11 );
            //:ELSE
         } 
         else
         { 
            //:   szMaxStringLth = lMaxStringLth
            ZeidonStringConvertFromNumber( szMaxStringLth, 1, 0, 10, lMaxStringLth, (ZDecimal) 0.0, "I" );
         } 

         //:   END

         //:   szWriteBuffer = "         strComboCurrentValue = " + vDialog.CtrlMapView.Name +
         //:            ".GetStringFromAttributeByContext( strSessionId, ^" +
         //:            szEntityName + "^, ^" +
         //:            szAttributeName + "^, ^" + szContextName + "^, " + szMaxStringLth + " );"
         GetVariableFromAttribute( szTempString_4, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strComboCurrentValue = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szAttributeName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMaxStringLth, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         //:ELSE
      } 
      else
      { 
         //:   szWriteBuffer = "      strComboCurrentValue = ^^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      strComboCurrentValue = ^^;", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      } 

      //:   END
      //:   ResetViewFromSubobject( vDialog )
      ResetViewFromSubobject( vDialog );

      //:   // See if a scoping entity has been specified, and if so, use it.
      //:   szScopingEntityName = ""
      ZeidonStringCopy( szScopingEntityName, 1, 0, "", 1, 0, 33 );
      //:   lSubtype = vDialog.Control.Subtype
      GetIntegerFromAttribute( &lSubtype, vDialog, "Control", "Subtype" );
      //:   lSubtype = IsFlagSequenceSet( lSubtype, zLISTBOX_SCOPE_OI )
      lSubtype = IsFlagSequenceSet( lSubtype, zLISTBOX_SCOPE_OI );
      //:   IF lSubtype = 0
      if ( lSubtype == 0 )
      { 
         //:   IF vScope.CtrlMapLOD_Entity EXISTS
         lTempInteger_9 = CheckExistenceOfEntity( vScope, "CtrlMapLOD_Entity" );
         if ( lTempInteger_9 == 0 )
         { 
            //:   szScopingEntityName = vScope.CtrlMapLOD_Entity.Name
            GetVariableFromAttribute( szScopingEntityName, 0, 'S', 33, vScope, "CtrlMapLOD_Entity", "Name", "", 0 );
         } 

         //:   END
      } 

      //:   END

      //:   szWriteBuffer = "      v" + szCtrlTag + ".CreateViewFromView( strSessionId, " + vDialog.CtrlMapView.Name + " );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".CreateViewFromView( strSessionId, ", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_5, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:   szWriteBuffer = "      ComboCount = 0;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ComboCount = 0;", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      strComboSelectedValue = ^0^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strComboSelectedValue = ^0^;", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:   IF lSubtype = 0
      if ( lSubtype == 0 )
      { 
         //:   szWriteBuffer = "      nRC = v" + szCtrlTag + ".SetCursorFirst( strSessionId, ^" +
         //:                                szListEntityName + "^, ^" + szScopingEntityName + "^ );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorFirst( strSessionId, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szScopingEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:   szWriteBuffer = "      nRC = v" + szCtrlTag + ".SetCursorScopeOI( strSessionId, ^" +
         //:                                szListEntityName + "^, 1 ); // first" // zPOS_FIRST
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorScopeOI( strSessionId, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 1 ); // first", 1, 0, 10001 );
      } 

      //:   END

      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      while ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      while ( nRC >= 0 )", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:   IF szAttributeName != ""
      if ( ZeidonStringCompare( szAttributeName, 1, 0, "", 1, 0, 33 ) != 0 )
      { 

         //:   szWriteBuffer = "         strErrorMapValue = v" + szCtrlTag +
         //:                   ".GetStringFromAttributeByContext( strSessionId, ^" +
         //:                   szEntityName + "^, ^" +
         //:                   szAttributeName + "^, ^" +
         //:                   szContextName + "^, " + szMaxStringLth + " );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szAttributeName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMaxStringLth, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      } 

      //:   END

      //:   szWriteBuffer = "         if ( strComboCurrentValue.equals( strErrorMapValue ) )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strComboCurrentValue.equals( strErrorMapValue ) )", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "         {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "            <option selected=^selected^ value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option selected=^selected^ value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "            strComboSelectedValue = Integer.toString( ComboCount );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            strComboSelectedValue = Integer.toString( ComboCount );", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "         }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "         else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         else", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "         {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "            <option value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option value=^<%=strErrorMapValue%>^><%=strErrorMapValue%></option>", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "         }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:   szWriteBuffer = "         ComboCount++;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         ComboCount++;", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   IF lSubtype = 0
      if ( lSubtype == 0 )
      { 
         //:   szWriteBuffer = "         nRC =  v" + szCtrlTag +
         //:                   ".SetCursorNext( strSessionId, ^" + szListEntityName +
         //:                   "^, ^" + szScopingEntityName + "^ );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC =  v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorNext( strSessionId, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szScopingEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:   szWriteBuffer = "         nRC =  v" + szCtrlTag +
         //:                   ".SetCursorScopeOI( strSessionId, ^" + szListEntityName + "^, 3 ); // next" // zPOS_NEXT
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC =  v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".SetCursorScopeOI( strSessionId, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, 3 ); // next", 1, 0, 10001 );
      } 

      //:   END

      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   DropView( vScope )
      DropView( vScope );
   } 

   //:   END

   //:   szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   //:   szWriteBuffer = "      v" + szCtrlTag + ".DropView( strSessionId );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".DropView( strSessionId );", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:   szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:   szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:   szWriteBuffer = "<input name=^h" + szCtrlTag + "^ id=^h" + szCtrlTag + "^ type=^hidden^ value=^<%=strComboSelectedValue%>^ >"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<input name=^h", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^h", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ type=^hidden^ value=^<%=strComboSelectedValue%>^ >", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = "</select>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</select>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSP_EmailEntries( VIEW vDialog     BASED ON LOD TZWDLGSO,
//:                     VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 255 )   szFormName )

//:   VIEW vDialogTemp BASED ON LOD TZWDLGSO
zOPER_EXPORT zSHORT OPERATION
GenJSP_EmailEntries( zVIEW     vDialog,
                     zVIEW     vDialogRoot,
                     zLONG     lFile,
                     zPCHAR    szWriteBuffer,
                     zPCHAR    szFormName )
{
   zVIEW     vDialogTemp = 0; 
   //:STRING ( 32 ) szCtrlWebCtrlType
   zCHAR     szCtrlWebCtrlType[ 33 ] = { 0 }; 
   //:STRING ( 32 ) szActionName
   zCHAR     szActionName[ 33 ] = { 0 }; 
   //:INTEGER       lControl
   zLONG     lControl = 0; 
   //:INTEGER       lActionType
   zLONG     lActionType = 0; 
   //:SHORT         nRC
   zSHORT    nRC = 0; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zSHORT    lTempInteger_0; 


   //:// Generate statements for formatting an email to be sent to all email addresses in a list.

   //:szWriteBuffer = "   // This is for indicating whether the user hit the window close box."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   // This is for indicating whether the user hit the window close box.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   isWindowClosing = false;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   isWindowClosing = false;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "   if ( _IsDocDisabled( ) == false )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( _IsDocDisabled( ) == false )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      var szEmailList = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var szEmailList = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      var tds;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var tds;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      var thisTd;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var thisTd;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      var k;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      var k;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      // Generates list of email addresses from td entries with class ^Email^."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Generates list of email addresses from td entries with class ^Email^.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      tds = document.getElementsByTagName( ^td^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      tds = document.getElementsByTagName( ^td^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      for ( k = 0; k < tds.length; k++ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      for ( k = 0; k < tds.length; k++ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         thisTd = tds[ k ];"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         thisTd = tds[ k ];", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if ( thisTd.className == ^Email^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( thisTd.className == ^Email^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            if ( szEmailList != ^^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( szEmailList != ^^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "               szEmailList += ^,^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "               szEmailList += ^,^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "            szEmailList += thisTd.innerHTML;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            szEmailList += thisTd.innerHTML;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "      if ( szEmailList != ^^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( szEmailList != ^^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         // Put together the email components and send them."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Put together the email components and send them.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         // Note that problems may occur if the client computer has no default email program specified."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Note that problems may occur if the client computer has no default email program specified.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         var thisMLE;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         var thisMLE;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         var mle;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         var mle;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         var eml;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         var eml;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         var subject;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         var subject;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         var bcc;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         var bcc;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         var sub;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         var sub;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         var bod;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         var bod;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         var mle1;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         var mle1;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:// Email Recipient
   //:// Email Recipient is one of three options.
   //:// 1. If event is Start Email Client, the list of email addresses.
   //:// 2. If event is Start Email BCC or Start Email CC AND an Email Recipient control exists on the page, the
   //://    Email Recipient control value.
   //:// 3. If event is Start Email BCC or Start Email CC AND an Email Recipient control DOES NOT EXIST on the page,
   //://    a null value.
   //:// Generate JSP statements if an email recipient was requested. (A control with WebCtrlType = "EmailRecipient")
   //:szWriteBuffer = "         // Email Recipient."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Email Recipient.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:lActionType = vDialog.Action.Type
   GetIntegerFromAttribute( &lActionType, vDialog, "Action", "Type" );
   //:IF lActionType = zWAB_StartEmailClient
   if ( lActionType == zWAB_StartEmailClient )
   { 
      //:// Case 1 above
      //:szWriteBuffer = "         eml = szEmailList;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         eml = szEmailList;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:ELSE
   } 
   else
   { 

      //:szCtrlWebCtrlType = "EmailRecipient"
      ZeidonStringCopy( szCtrlWebCtrlType, 1, 0, "EmailRecipient", 1, 0, 33 );
      //:CreateViewFromViewForTask( vDialogTemp, vDialogRoot, 0 )
      CreateViewFromViewForTask( &vDialogTemp, vDialogRoot, 0 );
      //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
      lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
      //:nRC = SetEntityCursor( vDialogTemp, "Control", "WebCtrlType", lControl, szCtrlWebCtrlType, "", "", 0, "Window", "" )
      nRC = SetEntityCursor( vDialogTemp, "Control", "WebCtrlType", lControl, szCtrlWebCtrlType, "", "", 0, "Window", "" );
      //:IF nRC >= zCURSOR_SET
      if ( nRC >= zCURSOR_SET )
      { 
         //:// Case 2 above
         //:szWriteBuffer = "         eml = document." + vDialogRoot.Dialog.Tag + vDialogRoot.Window.Tag +
         //:                "." + vDialogTemp.Control.Tag + ".value;"
         GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialogRoot, "Dialog", "Tag", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         eml = document.", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialogRoot, "Window", "Tag", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".value;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         //:ELSE
      } 
      else
      { 
         //:// Case 3 above
         //:szWriteBuffer = "         eml = ^^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         eml = ^^;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      } 

      //:END
      //:DropView( vDialogTemp )
      DropView( vDialogTemp );
   } 

   //:END


   //:// Email Subject
   //:// Generate JSP statements if an email subject was requested. (A control with WebCtrlType = "EmailSubject")
   //:szWriteBuffer = "         // Email Subject."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Email Subject.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szCtrlWebCtrlType = "EmailSubject"
   ZeidonStringCopy( szCtrlWebCtrlType, 1, 0, "EmailSubject", 1, 0, 33 );
   //:CreateViewFromViewForTask( vDialogTemp, vDialogRoot, 0 )
   CreateViewFromViewForTask( &vDialogTemp, vDialogRoot, 0 );
   //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
   lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
   //:nRC = SetEntityCursor( vDialogTemp, "Control", "WebCtrlType", lControl, szCtrlWebCtrlType, "", "", 0, "Window", "" )
   nRC = SetEntityCursor( vDialogTemp, "Control", "WebCtrlType", lControl, szCtrlWebCtrlType, "", "", 0, "Window", "" );
   //:IF nRC >= zCURSOR_SET
   if ( nRC >= zCURSOR_SET )
   { 
      //:szWriteBuffer = "         subject = document." + vDialogRoot.Dialog.Tag + vDialogRoot.Window.Tag +
      //:                "." + vDialogTemp.Control.Tag + ".value;"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialogRoot, "Dialog", "Tag", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         subject = document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialogRoot, "Window", "Tag", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".value;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   } 

   //:END
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );
   //:szWriteBuffer = "         if ( subject == ^^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( subject == ^^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            sub = ^?subject=&nbsp^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            sub = ^?subject=&nbsp^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            sub = ^?subject=^ + subject;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            sub = ^?subject=^ + subject;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:// Email Body
   //:// Generate JSP statements if an email body was requested. (A control with WebCtrlType = "EmailMessage")
   //:szWriteBuffer = "         // Email Body."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Email Body.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szCtrlWebCtrlType = "EmailMessage"
   ZeidonStringCopy( szCtrlWebCtrlType, 1, 0, "EmailMessage", 1, 0, 33 );
   //:CreateViewFromViewForTask( vDialogTemp, vDialogRoot, 0 )
   CreateViewFromViewForTask( &vDialogTemp, vDialogRoot, 0 );
   //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
   lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
   //:nRC = SetEntityCursor( vDialogTemp, "Control", "WebCtrlType", lControl, szCtrlWebCtrlType, "", "", 0, "Window", "" )
   nRC = SetEntityCursor( vDialogTemp, "Control", "WebCtrlType", lControl, szCtrlWebCtrlType, "", "", 0, "Window", "" );
   //:IF nRC >= zCURSOR_SET
   if ( nRC >= zCURSOR_SET )
   { 
      //:szWriteBuffer = "         mle = document.getElementById( ^" + vDialogTemp.Control.Tag + "^ ).value;"
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         mle = document.getElementById( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).value;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   } 

   //:END
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );
   //:szWriteBuffer = "         while ( mle.search( ^\n^ ) >= 0 )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         while ( mle.search( ^\\n^ ) >= 0 )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            mle1=mle.replace( ^\n^, ^%0a^ );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            mle1=mle.replace( ^\\n^, ^%0a^ );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            mle=mle1;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            mle=mle1;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         if ( mle == ^^ )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( mle == ^^ )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            bod = ^&body=&nbsp^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            bod = ^&body=&nbsp^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         else"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         else", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "            bod = ^&body=^ + mle;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "            bod = ^&body=^ + mle;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:// Email BCC or CC.
   //:szWriteBuffer = "         // Email BCC/CC."
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Email BCC/CC.", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:IF lActionType = zWAB_StartEmailClientBCC
   if ( lActionType == zWAB_StartEmailClientBCC )
   { 
      //:szWriteBuffer = "         bcc = ^&bcc=^ + szEmailList;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         bcc = ^&bcc=^ + szEmailList;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:szWriteBuffer = "         location.href=^mailto:^ + eml + sub + bcc + bod;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         location.href=^mailto:^ + eml + sub + bcc + bod;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:ELSE
   } 
   else
   { 
      //:IF lActionType = zWAB_StartEmailClientCC
      if ( lActionType == zWAB_StartEmailClientCC )
      { 
         //:szWriteBuffer = "         bcc = ^&cc=^ + szEmailList;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         bcc = ^&cc=^ + szEmailList;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         //:szWriteBuffer = "         location.href=^mailto:^ + eml + sub + bcc + bod;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         location.href=^mailto:^ + eml + sub + bcc + bod;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "         bcc = ^^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         bcc = ^^;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         location.href=^mailto:^ + eml + sub + bcc + bod;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         location.href=^mailto:^ + eml + sub + bcc + bod;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      } 

      //:END
   } 

   //:END

   //:// If the Action has an operation, we must also set up the code to trigger the Action and Operation at the
   //:// Application Server.
   //:IF vDialog.ActOper EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( vDialog, "ActOper" );
   if ( lTempInteger_0 == 0 )
   { 
      //:szActionName = vDialog.Action.Tag
      GetVariableFromAttribute( szActionName, 0, 'S', 33, vDialog, "Action", "Tag", "", 0 );
      //:szWriteBuffer = "         document." + szFormName + ".zAction.value = ^" + szActionName + "^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         document." + szFormName + ".submit( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         document.", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   } 

   //:END

   //:szWriteBuffer = "      }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   }"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   return( 0 );
// END
} 


//:GLOBAL OPERATION
//:GenJSP_CrteCalendar( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 20 )    szJustify,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY )

//:   // Format a CALENDAR control.

//:   STRING ( 256 ) szStyle
zOPER_EXPORT zVOID OPERATION
GenJSP_CrteCalendar( zVIEW     vDialog,
                     zLONG     lFile,
                     zPCHAR    szWriteBuffer,
                     zPCHAR    szIndent,
                     zPCHAR    szCtrlTag,
                     zPCHAR    szTableRowFlag,
                     zPCHAR    szJustify,
                     zPCHAR    szNoPositioning,
                     zLONG     lOffsetX,
                     zLONG     lOffsetY )
{
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:STRING ( 10 )  szWidth
   zCHAR     szWidth[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szHeight
   zCHAR     szHeight[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szX_Pos
   zCHAR     szX_Pos[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szY_Pos
   zCHAR     szY_Pos[ 11 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   zSHORT    RESULT; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zLONG     lTempInteger_0; 
   zLONG     lTempInteger_1; 
   zLONG     lTempInteger_2; 


   //:szWriteBuffer = "<% strErrorMapValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<% strErrorMapValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:SET CURSOR FIRST vDialog.CtrlMapLOD_Attribute WITHIN vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "CtrlMapLOD_Attribute", "Control" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szWriteBuffer = "   nRC = " + vDialog.CtrlMapView.Name +
      //:                ".GetView( strSessionId, ^" + vDialog.CtrlMapView.Name + "^, vAppSubtask );"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetView( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, vAppSubtask );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( nRC <= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC <= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name +
      //:         ".TraceLine( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".TraceLine( ^Invalid View: ^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   else"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name +
      //:                ".CheckExistenceOfEntity( strSessionId, ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ );"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".CheckExistenceOfEntity( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         strErrorMapValue = " +
      //:                vDialog.CtrlMapView.Name +
      //:                ".GetStringFromAttributeByContext( strSessionId, ^" +
      //:         vDialog.CtrlMapRelatedEntity.Name + "^, ^" +
      //:         vDialog.CtrlMapER_Attribute.Name + "^, strDateFormat, 10 );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".GetStringFromAttributeByContext( strSessionId, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, strDateFormat, 10 );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:// We will set the height to the constant 32 px.
      //:PIX_PER_DU( vDialog, dDLUnits )
      PIX_PER_DU( vDialog, &dDLUnits );
      //:zIntegerToString( szWidth, 10, vDialog.Control.SZDLG_X * dDLUnits )
      GetIntegerFromAttribute( &lTempInteger_0, vDialog, "Control", "SZDLG_X" );
      zIntegerToString( szWidth, 10, lTempInteger_0 * dDLUnits );
      //:szHeight = "32"
      ZeidonStringCopy( szHeight, 1, 0, "32", 1, 0, 11 );
      //:szStyle = "style=^width:" + szWidth + "px;height:" + szHeight + "px;"
      ZeidonStringCopy( szStyle, 1, 0, "style=^width:", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "px;height:", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );

      //:// If szNoPositioning is null then we are using absolute positioning when creating controls.
      //:IF  szNoPositioning = ""
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
      { 

         //:zIntegerToString( szX_Pos, 10, vDialog.Control.PSDLG_X * dDLUnits )
         GetIntegerFromAttribute( &lTempInteger_1, vDialog, "Control", "PSDLG_X" );
         zIntegerToString( szX_Pos, 10, lTempInteger_1 * dDLUnits );
         //:zIntegerToString( szY_Pos, 10, vDialog.Control.PSDLG_Y * dDLUnits )
         GetIntegerFromAttribute( &lTempInteger_2, vDialog, "Control", "PSDLG_Y" );
         zIntegerToString( szY_Pos, 10, lTempInteger_2 * dDLUnits );
         //:szStyle = szStyle + "position:absolute;left:" + szX_Pos + "px;" + "top:" + szY_Pos + "px;^ "
         ZeidonStringConcat( szStyle, 1, 0, "position:absolute;left:", 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, szX_Pos, 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, "top:", 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, szY_Pos, 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, "px;^ ", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:szStyle = szStyle + "^ "
         ZeidonStringConcat( szStyle, 1, 0, "^ ", 1, 0, 257 );
      } 

      //:END

      //:CreateTabIndexString( vDialog, szTabIndex )
      CreateTabIndexString( vDialog, szTabIndex );

      //:CreateDisabledString( vDialog, szDisabled )
      CreateDisabledString( vDialog, szDisabled );

      //:// Multiple class names must be separated by white space characters.
      //:szClass = vDialog.Control.CSS_Class
      GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );

      //:szWriteBuffer = "<span " + szStyle + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<span ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:IF szClass = ""
      if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
      { 
         //:szWriteBuffer = "   <input name=^" + szCtrlTag + "^ id='" + szCtrlTag + "' " + szDisabled +
         //:                    "style=^width:80px^ type=^text^ value=^<%=strErrorMapValue%>^ " + szTabIndex + " />"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id='", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "' ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "style=^width:80px^ type=^text^ value=^<%=strErrorMapValue%>^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " />", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "   <input class=^" + szClass + "^ name=^" + szCtrlTag + "^ id='" + szCtrlTag + "' " + szDisabled +
         //:                    "style=^width:80px^ type=^text^ value=^<%=strErrorMapValue%>^ " + szTabIndex + " />"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input class=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id='", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "' ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "style=^width:80px^ type=^text^ value=^<%=strErrorMapValue%>^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " />", 1, 0, 10001 );
      } 

      //:END
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   <img src=^images/scw.gif^  name=^" + szCtrlTag + "Img^ id=^" + szCtrlTag + "Img^ title=^Select Date^ alt=^Select Date^"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <img src=^images/scw.gif^  name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "Img^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "Img^ title=^Select Date^ alt=^Select Date^", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "        onclick=^scwShow( document.getElementById( '" + szCtrlTag + "' ), this );^ " + szTabIndex + " />"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "        onclick=^scwShow( document.getElementById( '", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "' ), this );^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " />", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "</span>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "</span>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   } 


   //:END
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSP_MenuFunctions( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                      VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                      INTEGER          lFile,
//:                      STRING ( 10000 ) szWriteBuffer,
//:                      STRING ( 255 )   szFormName,
//:                      STRING ( 2 )     szActionPrefix )

//:   VIEW vDialog2 BASED ON LOD TZWDLGSO
zOPER_EXPORT zVOID OPERATION
GenJSP_MenuFunctions( zVIEW     vDialog,
                      zVIEW     vDialogRoot,
                      zLONG     lFile,
                      zPCHAR    szWriteBuffer,
                      zPCHAR    szFormName,
                      zPCHAR    szActionPrefix )
{
   zVIEW     vDialog2 = 0; 
   //:STRING ( 34 )    szActionName
   zCHAR     szActionName[ 35 ] = { 0 }; 
   //:STRING ( 32 )    szCtrlTag
   zCHAR     szCtrlTag[ 33 ] = { 0 }; 
   //:STRING ( 10000 ) szJavaScript
   zCHAR     szJavaScript[ 10001 ] = { 0 }; 
   //:INTEGER          lControl
   zLONG     lControl = 0; 
   //:SHORT            bListButton
   zSHORT    bListButton = 0; 
   //:SHORT            nRC
   zSHORT    nRC = 0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_0[ 33 ]; 
   zSHORT    lTempInteger_1; 
   zSHORT    lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zSHORT    lTempInteger_4; 


   //:FOR EACH vDialog.Option
   RESULT = SetCursorFirstEntity( vDialog, "Option", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:IF vDialog.OptAct EXISTS
      lTempInteger_0 = CheckExistenceOfEntity( vDialog, "OptAct" );
      if ( lTempInteger_0 == 0 )
      { 
         //:SET CURSOR FIRST vDialog.Action WHERE vDialog.Action.Tag = vDialog.OptAct.Tag
         GetStringFromAttribute( szTempString_0, zsizeof( szTempString_0 ), vDialog, "OptAct", "Tag" );
         RESULT = SetCursorFirstEntityByString( vDialog, "Action", "Tag", szTempString_0, "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //://Because the menu actions can be created on separate windows from the control
            //://actions, we need to make sure these actions are unique.  We will prefix a
            //://"m" to the main menu actions and prefix a "sm" to the side menu actions.
            //:szActionName = szActionPrefix + vDialog.Action.Tag
            GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "Action", "Tag", "", 0 );
            ZeidonStringCopy( szActionName, 1, 0, szActionPrefix, 1, 0, 35 );
            ZeidonStringConcat( szActionName, 1, 0, szTempString_0, 1, 0, 35 );
            //:nRC = zstrcmpi( szActionName, "alt-f4" )
            nRC = zstrcmpi( szActionName, "alt-f4" );
            //:IF nRC = 0
            if ( nRC == 0 )
            { 
               //:szActionName = "AltF4"
               ZeidonStringCopy( szActionName, 1, 0, "AltF4", 1, 0, 35 );
            } 

            //:END

            //:bListButton = 0
            bListButton = 0;
            //:IF vDialog.ActEvent EXISTS AND vDialog.ActCtrl EXISTS
            lTempInteger_1 = CheckExistenceOfEntity( vDialog, "ActEvent" );
            lTempInteger_2 = CheckExistenceOfEntity( vDialog, "ActCtrl" );
            if ( lTempInteger_1 == 0 && lTempInteger_2 == 0 )
            { 

               //:szCtrlTag = vDialog.ActCtrl.Tag
               GetVariableFromAttribute( szCtrlTag, 0, 'S', 33, vDialog, "ActCtrl", "Tag", "", 0 );
               //:CreateViewFromViewForTask( vDialog2, vDialogRoot, 0 )
               CreateViewFromViewForTask( &vDialog2, vDialogRoot, 0 );

               //:lControl = zQUAL_STRING + zPOS_FIRST + zRECURS
               lControl = zQUAL_STRING + zPOS_FIRST + zRECURS;
               //:IF SetEntityCursor( vDialog2, "Control", "Tag", lControl,
               //:                    szCtrlTag, "", "", 0,
               //:                    "Window", "" ) >= zCURSOR_SET AND
               //:   vDialog2.ControlDef.Key = 1020
               lTempInteger_3 = SetEntityCursor( vDialog2, "Control", "Tag", lControl, szCtrlTag, "", "", 0, "Window", "" );
               if ( lTempInteger_3 >= zCURSOR_SET && CompareAttributeToInteger( vDialog2, "ControlDef", "Key", 1020 ) == 0 )
               { 

                  //:IF ResetViewFromSubobject( vDialog2 ) = 0 AND
                  //:   vDialog2.ControlDef.Key = 2010
                  lTempInteger_4 = ResetViewFromSubobject( vDialog2 );
                  if ( lTempInteger_4 == 0 && CompareAttributeToInteger( vDialog2, "ControlDef", "Key", 2010 ) == 0 )
                  { 

                     //:bListButton = 1
                     bListButton = 1;
                  } 


                  //:END
               } 

               //:END

               //:DropView( vDialog2 )
               DropView( vDialog2 );
            } 


            //:END

            //:IF bListButton = 1
            if ( bListButton == 1 )
            { 
               //:szWriteBuffer = "function " + szActionName + "( strEntityKey )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "function ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "( strEntityKey )", 1, 0, 10001 );
               //:ELSE
            } 
            else
            { 
               //:szWriteBuffer = "function " + szActionName + "( )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "function ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "( )", 1, 0, 10001 );
            } 

            //:END

            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "{"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "{", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:szWriteBuffer = "   // This is for indicating whether the user hit the window close box."
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   // This is for indicating whether the user hit the window close box.", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   isWindowClosing = false;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   isWindowClosing = false;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:szWriteBuffer = "   if ( _IsDocDisabled( ) == false )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( _IsDocDisabled( ) == false )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //://KJS 11/16/2007 - We want to insert any javascript code that the
            //://user has entered for this action.  This will be put before the action
            //://generated code for submitting.
            //:szJavaScript = vDialog.Action.WebJavaScript
            GetVariableFromAttribute( szJavaScript, 0, 'S', 10001, vDialog, "Action", "WebJavaScript", "", 0 );
            //:IF szJavaScript != ""
            if ( ZeidonStringCompare( szJavaScript, 1, 0, "", 1, 0, 10001 ) != 0 )
            { 
               //:szWriteBuffer = ""
               ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      // Javascript code entered by user."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Javascript code entered by user.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
               //:szWriteBuffer = szJavaScript
               ZeidonStringCopy( szWriteBuffer, 1, 0, szJavaScript, 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
               //:szWriteBuffer = "      // END of Javascript code entered by user."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      // END of Javascript code entered by user.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
            } 

            //:END

            //:   // KJS 10/28/10 - Testing this to see how using an hourglass would work while
            //:   // the user is waiting for something to happen.
            //:   //szWriteBuffer = "      document.body.style.cursor = ^wait^;"
            //:   //WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )

            //:szWriteBuffer = "      _DisableFormElements( true );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      _DisableFormElements( true );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:IF bListButton = 1
            if ( bListButton == 1 )
            { 
               //:szWriteBuffer = "      document." + szFormName + ".zTableRowSelect.value = strEntityKey;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".zTableRowSelect.value = strEntityKey;", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            } 

            //:END

            //:IF vDialog.Action.Type = zWAB_ExitDialogTask
            if ( CompareAttributeToInteger( vDialog, "Action", "Type", zWAB_ExitDialogTask ) == 0 )
            { 
               //:// For exiting the Dialog (ie., Session), the Action is OnUnload.
               //:szWriteBuffer = "      document." + szFormName + ".zAction.value = ^_OnUnload^;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^_OnUnload^;", 1, 0, 10001 );
               //:ELSE
            } 
            else
            { 
               //:szWriteBuffer = "      document." + szFormName + ".zAction.value = ^" + szActionName + "^;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".zAction.value = ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
            } 

            //:END
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      document." + szFormName + ".submit( );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      document.", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".submit( );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "}"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "}", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         } 

         //:END
      } 

      RESULT = SetCursorNextEntity( vDialog, "Option", "" );
      //:END
   } 

   //:END
   return;
// END
} 


//:GLOBAL OPERATION
//:BuildSideNavSection( VIEW vDialog,
//:                     VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                     INTEGER lFile,
//:                     STRING (1) szReusableMenu,
//:                     VIEW vDialogMenu BASED ON LOD TZWDLGSO )

//:   STRING ( 10000 ) szWriteBuffer
zOPER_EXPORT zSHORT OPERATION
BuildSideNavSection( zVIEW     vDialog,
                     zVIEW     vDialogRoot,
                     zLONG     lFile,
                     zPCHAR    szReusableMenu,
                     zVIEW     vDialogMenu )
{
   zCHAR     szWriteBuffer[ 10001 ] = { 0 }; 
   //:STRING ( 50 )    szNavigationTitle
   zCHAR     szNavigationTitle[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szHTML_Name
   zCHAR     szHTML_Name[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szDialogName
   zCHAR     szDialogName[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szOptionTag
   zCHAR     szOptionTag[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szMenuName
   zCHAR     szMenuName[ 51 ] = { 0 }; 
   //:STRING ( 34 )    szActionName
   zCHAR     szActionName[ 35 ] = { 0 }; 
   //:STRING ( 256 )   szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 )   szClass2
   zCHAR     szClass2[ 257 ] = { 0 }; 
   //:INTEGER          ActionType
   zLONG     ActionType = 0; 
   //:INTEGER          lLth
   zLONG     lLth = 0; 
   //:SHORT            nRC
   zSHORT    nRC = 0; 
   zCHAR     szTempString_0[ 1026 ]; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_1[ 255 ]; 
   zSHORT    RESULT; 
   zCHAR     szTempString_2[ 33 ]; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 255 ]; 
   zLONG     lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zCHAR     szTempString_5[ 255 ]; 
   zCHAR     szTempString_6[ 255 ]; 


   //:// SIDE NAVIGATION BAR
   //:TraceLineS( "*** BuildSideNavSection Window! *** ", vDialog.Window.Tag )
   GetStringFromAttribute( szTempString_0, zsizeof( szTempString_0 ), vDialog, "Window", "Tag" );
   TraceLineS( "*** BuildSideNavSection Window! *** ", szTempString_0 );

   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "<div id=^leftcontent^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^leftcontent^>", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = "<!-- Side Navigation *********************** -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- Side Navigation *********************** -->", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //:IF vDialogRoot.Menu EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( vDialogRoot, "Menu" );
   if ( lTempInteger_0 == 0 )
   { 
      //:szMenuName = vDialogRoot.Menu.Tag
      GetVariableFromAttribute( szMenuName, 0, 'S', 51, vDialogRoot, "Menu", "Tag", "", 0 );
      //:IF vDialogRoot.Menu.CSS_Class != ""
      if ( CompareAttributeToString( vDialogRoot, "Menu", "CSS_Class", "" ) != 0 )
      { 
         //:szClass = " class=^" + vDialogRoot.Menu.CSS_Class + "^ "
         GetVariableFromAttribute( szTempString_1, 0, 'S', 255, vDialogRoot, "Menu", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_1, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
      } 

      //:END
   } 

   //:END
   //:szWriteBuffer = "<div id=^sidenavigation^" + szClass + ">"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^sidenavigation^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   //://szWriteBuffer = "<div id=^sidenavigation^>"
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //://szWriteBuffer = "   <ul id=^" + szMenuName + "^ name=^" + szMenuName + "^" + szClass + ">"
   //:szWriteBuffer = "   <ul id=^" + szMenuName + "^ name=^" + szMenuName + "^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <ul id=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^>", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );

   //:FOR EACH vDialogRoot.OptAct WITHIN vDialogRoot.Menu
   RESULT = SetCursorFirstEntity( vDialogRoot, "OptAct", "Menu" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:szNavigationTitle = vDialogRoot.Option.Text
      GetVariableFromAttribute( szNavigationTitle, 0, 'S', 51, vDialogRoot, "Option", "Text", "", 0 );
      //:szDialogName = vDialogRoot.OptAct.DialogName
      GetVariableFromAttribute( szDialogName, 0, 'S', 51, vDialogRoot, "OptAct", "DialogName", "", 0 );
      //:IF szDialogName = ""
      if ( ZeidonStringCompare( szDialogName, 1, 0, "", 1, 0, 51 ) == 0 )
      { 
         //:szDialogName = "NoDialogName"
         ZeidonStringCopy( szDialogName, 1, 0, "NoDialogName", 1, 0, 51 );
      } 

      //:END

      //:IF szReusableMenu = "Y"
      if ( ZeidonStringCompare( szReusableMenu, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 
         //:szMenuName = "sm" + vDialogRoot.Option.Tag
         GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialogRoot, "Option", "Tag", "", 0 );
         ZeidonStringCopy( szMenuName, 1, 0, "sm", 1, 0, 51 );
         ZeidonStringConcat( szMenuName, 1, 0, szTempString_2, 1, 0, 51 );
         //:ELSE
      } 
      else
      { 
         //:szMenuName = vDialogRoot.Option.Tag
         GetVariableFromAttribute( szMenuName, 0, 'S', 51, vDialogRoot, "Option", "Tag", "", 0 );
      } 

      //:END

      //:// szHTML_Name = szDialogName + vDialogRoot.OptAct.WindowName + ".jsp"
      //:IF vDialogRoot.OptAct EXISTS
      lTempInteger_1 = CheckExistenceOfEntity( vDialogRoot, "OptAct" );
      if ( lTempInteger_1 == 0 )
      { 

         //:// Because the menu actions can be created on separate windows from the control
         //:// actions, we need to make sure these actions are unique.  We will prefix a
         //:// "m" to the main menu actions and prefix a "sm" to the side menu actions.
         //:IF szReusableMenu = "Y"
         if ( ZeidonStringCompare( szReusableMenu, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:szActionName = "sm" + vDialogRoot.OptAct.Tag
            GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialogRoot, "OptAct", "Tag", "", 0 );
            ZeidonStringCopy( szActionName, 1, 0, "sm", 1, 0, 35 );
            ZeidonStringConcat( szActionName, 1, 0, szTempString_3, 1, 0, 35 );
            //:lLth = zstrlen( szActionName )
            lLth = zstrlen( szActionName );
            //:IF lLth > 32
            if ( lLth > 32 )
            { 
               //:MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32",
               //:             szActionName,
               //:             zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
               MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32", szActionName, zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 );
            } 

            //:END
            //:ELSE
         } 
         else
         { 
            //:szActionName = vDialogRoot.OptAct.Tag
            GetVariableFromAttribute( szActionName, 0, 'S', 35, vDialogRoot, "OptAct", "Tag", "", 0 );
         } 

         //:END
         //:ActionType = vDialogRoot.OptAct.Type
         GetIntegerFromAttribute( &ActionType, vDialogRoot, "OptAct", "Type" );
         //:ELSE
      } 
      else
      { 
         //:szActionName = ""
         ZeidonStringCopy( szActionName, 1, 0, "", 1, 0, 35 );
         //:ActionType = 0
         ActionType = 0;
      } 

      //:END

      //:// If the window we are currently generating is the same window that this
      //:// side menu points to, then we want to set a class on this option.  The
      //:// reason is so that we can tell which side menu option the user has selected.
      //:IF vDialogRoot.OptAct.WindowName = vDialog.Window.Tag
      if ( CompareAttributeToAttribute( vDialogRoot, "OptAct", "WindowName", vDialog, "Window", "Tag" ) == 0 )
      { 
         //:szClass2 = " class=^sideselected^ "
         ZeidonStringCopy( szClass2, 1, 0, " class=^sideselected^ ", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:szClass2 = ""
         ZeidonStringCopy( szClass2, 1, 0, "", 1, 0, 257 );
      } 

      //:END

      //:IF vDialogRoot.Option.CSS_Class != ""
      if ( CompareAttributeToString( vDialogRoot, "Option", "CSS_Class", "" ) != 0 )
      { 
         //:szClass = " class=^" + vDialogRoot.Option.CSS_Class + "^"
         GetVariableFromAttribute( szTempString_4, 0, 'S', 255, vDialogRoot, "Option", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_4, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:szClass = ""
         ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
      } 

      //:END

      //:szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:szOptionTag = vDialogRoot.Option.Tag
      GetVariableFromAttribute( szOptionTag, 0, 'S', 51, vDialogRoot, "Option", "Tag", "", 0 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   nRC = vKZXMLPGO.SetCursorFirst( strSessionId, ^DisableMenuOption^, ^MenuOptionName^, ^" + szOptionTag + "^, ^^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = vKZXMLPGO.SetCursorFirst( strSessionId, ^DisableMenuOption^, ^MenuOptionName^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szOptionTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^^ );", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( nRC < 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC < 0 )", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "       <li id=^" + szMenuName + "^ name=^" + szMenuName + "^" + szClass + "><a href=^#^ " + szClass2 + " onclick=^" + szActionName + "()^>" + szNavigationTitle + "</a></li>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "       <li id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "><a href=^#^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "()^>", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szNavigationTitle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "</a></li>", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 );
      RESULT = SetCursorNextEntity( vDialogRoot, "OptAct", "Menu" );
   } 

   //:END  // FOR EACH

   //:// This is for building a default menu?
   //:// Trying to get this file to compile.
   //:IF vDialogMenu != 0
   if ( vDialogMenu != 0 )
   { 
      //:CreateViewFromViewForTask( vDialogMenu, vDialogMenu, 0 )
      CreateViewFromViewForTask( &vDialogMenu, vDialogMenu, 0 );
      //:SET CURSOR FIRST vDialogMenu.Menu WHERE vDialogMenu.Menu.ZKey = vDialogMenu.DfltMenu.ZKey
      GetIntegerFromAttribute( &lTempInteger_2, vDialogMenu, "DfltMenu", "ZKey" );
      RESULT = SetCursorFirstEntityByInteger( vDialogMenu, "Menu", "ZKey", lTempInteger_2, "" );
      //:FOR EACH vDialogMenu.OptAct WITHIN vDialogMenu.Menu
      RESULT = SetCursorFirstEntity( vDialogMenu, "OptAct", "Menu" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:szNavigationTitle = vDialogMenu.Option.Text
         GetVariableFromAttribute( szNavigationTitle, 0, 'S', 51, vDialogMenu, "Option", "Text", "", 0 );
         //:szDialogName = vDialogMenu.OptAct.DialogName
         GetVariableFromAttribute( szDialogName, 0, 'S', 51, vDialogMenu, "OptAct", "DialogName", "", 0 );
         //:IF szDialogName = ""
         if ( ZeidonStringCompare( szDialogName, 1, 0, "", 1, 0, 51 ) == 0 )
         { 
            //:szDialogName = "NoDialogName"
            ZeidonStringCopy( szDialogName, 1, 0, "NoDialogName", 1, 0, 51 );
         } 

         //:END

         //:// szHTML_Name = szDialogName + vDialogMenu.OptAct.WindowName + ".jsp"
         //:IF vDialogMenu.OptAct EXISTS
         lTempInteger_3 = CheckExistenceOfEntity( vDialogMenu, "OptAct" );
         if ( lTempInteger_3 == 0 )
         { 
            //:szActionName = vDialogMenu.OptAct.Tag
            GetVariableFromAttribute( szActionName, 0, 'S', 35, vDialogMenu, "OptAct", "Tag", "", 0 );
            //:ActionType = vDialogMenu.OptAct.Type
            GetIntegerFromAttribute( &ActionType, vDialogMenu, "OptAct", "Type" );
            //:ELSE
         } 
         else
         { 
            //:szActionName = ""
            ZeidonStringCopy( szActionName, 1, 0, "", 1, 0, 35 );
            //:ActionType = 0
            ActionType = 0;
         } 

         //:END

         //:szMenuName = vDialogRoot.Option.Tag
         GetVariableFromAttribute( szMenuName, 0, 'S', 51, vDialogRoot, "Option", "Tag", "", 0 );

         //:// If the window we are currently generating is the same window that this
         //:// side menu points to, then we want to set a class on this option.  The
         //:// reason is so that we can tell which side menu option the user has selected.
         //:IF vDialogMenu.OptAct.WindowName = vDialog.Window.Tag
         if ( CompareAttributeToAttribute( vDialogMenu, "OptAct", "WindowName", vDialog, "Window", "Tag" ) == 0 )
         { 
            //:szClass2 = "class=^sideselected^ "
            ZeidonStringCopy( szClass2, 1, 0, "class=^sideselected^ ", 1, 0, 257 );
            //:ELSE
         } 
         else
         { 
            //:szClass2 = ""
            ZeidonStringCopy( szClass2, 1, 0, "", 1, 0, 257 );
         } 

         //:END

         //:IF vDialogMenu.Option.CSS_Class != ""
         if ( CompareAttributeToString( vDialogMenu, "Option", "CSS_Class", "" ) != 0 )
         { 
            //:szClass = "class=^" + vDialogMenu.Option.CSS_Class + "^"
            GetVariableFromAttribute( szTempString_5, 0, 'S', 255, vDialogMenu, "Option", "CSS_Class", "", 0 );
            ZeidonStringCopy( szClass, 1, 0, "class=^", 1, 0, 257 );
            ZeidonStringConcat( szClass, 1, 0, szTempString_5, 1, 0, 257 );
            ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
            //:ELSE
         } 
         else
         { 
            //:szClass = ""
            ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
         } 

         //:END

         //:szWriteBuffer = "<%"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );
         //:szOptionTag = vDialogMenu.Option.Tag
         GetVariableFromAttribute( szOptionTag, 0, 'S', 51, vDialogMenu, "Option", "Tag", "", 0 );
         //:szOptionTag = vDialogMenu.Option.Tag
         GetVariableFromAttribute( szOptionTag, 0, 'S', 51, vDialogMenu, "Option", "Tag", "", 0 );
         //:szWriteBuffer = "   nRC = vKZXMLPGO.SetCursorFirst( strSessionId, ^DisableMenuOption^, ^MenuOptionName^, ^" + szOptionTag + "^, ^^ );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   nRC = vKZXMLPGO.SetCursorFirst( strSessionId, ^DisableMenuOption^, ^MenuOptionName^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szOptionTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^^ );", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   if ( nRC < 0 )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( nRC < 0 )", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   {"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "%>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );

         //:szWriteBuffer = "       <li id=^" + szMenuName + "^ name=^" + szMenuName + "^" + szClass + "><a href=^#^ " + szClass2 + " onclick=^" + szActionName + "()^>" + szNavigationTitle + "</a></li>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "       <li id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "><a href=^#^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass2, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "()^>", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szNavigationTitle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</a></li>", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );

         //:szWriteBuffer = "<%"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   }"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "%>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 1 );
         RESULT = SetCursorNextEntity( vDialogMenu, "OptAct", "Menu" );
      } 

      //:END  // FOR EACH

      //:DropView( vDialogMenu )
      DropView( vDialogMenu );
   } 

   //:END  // vDialogMenu != 0

   //:// Division ending for Navigation Bar.
   //:szWriteBuffer = "   </ul>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   </ul>", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "</div> <!-- sidenavigation -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</div> <!-- sidenavigation -->", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 );
   //:IF vDialogRoot.Dialog.WEB_LeftSideInclude != ""
   if ( CompareAttributeToString( vDialogRoot, "Dialog", "WEB_LeftSideInclude", "" ) != 0 )
   { 
      //://szWriteBuffer = "<%@ include file=^./include/leftcontent.inc^ %>"
      //:szWriteBuffer = "<!-- left content include file -->"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- left content include file -->", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "<%@ include file=^" + vDialogRoot.Dialog.WEB_LeftSideInclude + "^ %>"
      GetVariableFromAttribute( szTempString_6, 0, 'S', 255, vDialogRoot, "Dialog", "WEB_LeftSideInclude", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@ include file=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ %>", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 );
   } 

   //:END
   //:szWriteBuffer = "</div>  <!-- leftcontent -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- leftcontent -->", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   return( 0 );
//    /*
//    szCSS_Class = vDialog.Window.CSS_Class
//    IF szCSS_Class = ""
//       // Begin the division for the main body content.
//       szWriteBuffer = "<div id=^content^>"
//       WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 )
//    END
//    */
// END
} 


//:GLOBAL OPERATION
//:CreateTabIndexString( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                      STRING ( 16 ) szTabIndex )

//:   VIEW vDialogRoot BASED ON LOD TZWDLGSO
zOPER_EXPORT zSHORT OPERATION
CreateTabIndexString( zVIEW     vDialog,
                      zPCHAR    szTabIndex )
{
   zVIEW     vDialogRoot = 0; 
   //:STRING ( 8 ) szWork
   zCHAR     szWork[ 9 ] = { 0 }; 
   //:INTEGER      lTabIndex
   zLONG     lTabIndex = 0; 
   zSHORT    RESULT; 


   //:TraceLineS("In CreateTabIndexString ---- ", "")
   TraceLineS( "In CreateTabIndexString ---- ", "" );

   //:GET VIEW vDialogRoot NAMED "vDialogRoot"
   RESULT = GetViewByName( &vDialogRoot, "vDialogRoot", vDialog, zLEVEL_TASK );
   //:lTabIndex = vDialog.Control.SyncKey
   GetIntegerFromAttribute( &lTabIndex, vDialog, "Control", "SyncKey" );
   //:IF lTabIndex > 0 AND lTabIndex < 9999
   if ( lTabIndex > 0 && lTabIndex < 9999 )
   { 
      //:zIntegerToString( szWork, 8, lTabIndex )
      zIntegerToString( szWork, 8, lTabIndex );
      //:szTabIndex = " tabindex=" + szWork + " "
      ZeidonStringCopy( szTabIndex, 1, 0, " tabindex=", 1, 0, 17 );
      ZeidonStringConcat( szTabIndex, 1, 0, szWork, 1, 0, 17 );
      ZeidonStringConcat( szTabIndex, 1, 0, " ", 1, 0, 17 );
      //:ELSE
   } 
   else
   { 
      //:GET VIEW vDialogRoot NAMED "DialogRoot"
      RESULT = GetViewByName( &vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK );
      //:IF vDialogRoot.Window.wWindowHasTabsFlag = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Window", "wWindowHasTabsFlag", "Y" ) == 0 )
      { 
         //:szTabIndex = " tabindex=-1 "    // Since tabs are used on the Window, this Control will be marked "no tab".
         ZeidonStringCopy( szTabIndex, 1, 0, " tabindex=-1 ", 1, 0, 17 );
         //:ELSE
      } 
      else
      { 
         //:szTabIndex = ""
         ZeidonStringCopy( szTabIndex, 1, 0, "", 1, 0, 17 );
      } 

      //:END
   } 

   //:END

   //:RETURN( lTabIndex )
   return( ( lTabIndex ) );
// END
} 


 
#ifdef __cplusplus
}
#endif
