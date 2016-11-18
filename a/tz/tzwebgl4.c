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
//:BuildSideNavSectionJ( VIEW vDialog,
//:                      VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                      INTEGER lFile,
//:                      STRING (1) szReusableMenu,
//:                      VIEW vDialogMenu BASED ON LOD TZWDLGSO )

//:   STRING ( 10000 ) szWriteBuffer
zOPER_EXPORT zSHORT OPERATION
BuildSideNavSectionJ( zVIEW     vDialog,
                      zVIEW     vDialogRoot,
                      zLONG     lFile,
                      zPCHAR    szReusableMenu,
                      zVIEW     vDialogMenu )
{
   zCHAR     szWriteBuffer[ 10001 ] = { 0 }; 
   //:STRING ( 500 )   szNavigationTitle
   zCHAR     szNavigationTitle[ 501 ] = { 0 }; 
   //:STRING ( 500 )   szText
   zCHAR     szText[ 501 ] = { 0 }; 
   //:STRING ( 5 )     szSrch
   zCHAR     szSrch[ 6 ] = { 0 }; 
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
   //:SHORT            nRC
   zSHORT    nRC = 0; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_0[ 255 ]; 
   zSHORT    RESULT; 
   zCHAR     szTempString_1[ 33 ]; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 255 ]; 
   zLONG     lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zCHAR     szTempString_4[ 255 ]; 
   zCHAR     szTempString_5[ 255 ]; 


   //:// SIDE NAVIGATION BAR
   //://TraceLineS( "*** BuildSideNavSection Window *** ", vDialog.Window.Tag )

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
         GetVariableFromAttribute( szTempString_0, 0, 'S', 255, vDialogRoot, "Menu", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_0, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
      } 

      //:END
   } 

   //:END
   //:szWriteBuffer = "<div id=^sidenavigation^" + szClass + ">"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^sidenavigation^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
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
      //://szNavigationTitle = vDialogRoot.Option.Text
      //:// KJS 09/30/16 - Language Conversion.
      //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
      //:// So for now, I am always using, if the flag is set.
      //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
      { 
         //:szText = vDialogRoot.Option.Text
         GetVariableFromAttribute( szText, 0, 'S', 501, vDialogRoot, "Option", "Text", "", 0 );
         //:zSearchAndReplace( szText, 500, "\", "\\" )
         zSearchAndReplace( szText, 500, "\\", "\\\\" );
         //:szSrch = "\" + QUOTES 
         ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
         ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
         //:zSearchAndReplace( szText, 500, QUOTES, szSrch )
         zSearchAndReplace( szText, 500, QUOTES, szSrch );
         //:szNavigationTitle = "<%=LangConv.getLanguageText(^" + szText + "^)%>" 
         ZeidonStringCopy( szNavigationTitle, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
         ZeidonStringConcat( szNavigationTitle, 1, 0, szText, 1, 0, 501 );
         ZeidonStringConcat( szNavigationTitle, 1, 0, "^)%>", 1, 0, 501 );
         //:ELSE
      } 
      else
      { 
         //:szNavigationTitle = vDialogRoot.Option.Text
         GetVariableFromAttribute( szNavigationTitle, 0, 'S', 501, vDialogRoot, "Option", "Text", "", 0 );
      } 

      //:END

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
         GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialogRoot, "Option", "Tag", "", 0 );
         ZeidonStringCopy( szMenuName, 1, 0, "sm", 1, 0, 51 );
         ZeidonStringConcat( szMenuName, 1, 0, szTempString_1, 1, 0, 51 );
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
            GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialogRoot, "OptAct", "Tag", "", 0 );
            ZeidonStringCopy( szActionName, 1, 0, "sm", 1, 0, 35 );
            ZeidonStringConcat( szActionName, 1, 0, szTempString_2, 1, 0, 35 );
            //:// lLth = zstrlen( szActionName )
            //:// IF lLth > 32
            //://    MessageSend( vDialog, "", "Reusable Menu Action Name Length > 32",
            //://                 szActionName,
            //://                 zMSGQ_OBJECT_CONSTRAINT_WARNING, 0 )
            //:// END
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
         GetVariableFromAttribute( szTempString_3, 0, 'S', 255, vDialogRoot, "Option", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_3, 1, 0, 257 );
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
      //:szWriteBuffer = "   csrRC = vKZXMLPGO.cursor( ^DisableMenuOption^ ).setFirst( ^MenuOptionName^, ^" + szOptionTag + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   csrRC = vKZXMLPGO.cursor( ^DisableMenuOption^ ).setFirst( ^MenuOptionName^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szOptionTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( !csrRC.isSet() ) //if ( nRC < 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( !csrRC.isSet() ) //if ( nRC < 0 )", 1, 0, 10001 );
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

      //://szWriteBuffer = "       <li><a href=^#^ " + szClass + " onclick=^" + szActionName + "( )^>" + szNavigationTitle + "</a></li>"
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

   //:END

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
         //://szNavigationTitle = vDialogMenu.Option.Text
         //:// KJS 09/30/16 - Language Conversion.
         //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
         //:// So for now, I am always using, if the flag is set.
         //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
         if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
         { 
            //:szText = vDialogMenu.Option.Text
            GetVariableFromAttribute( szText, 0, 'S', 501, vDialogMenu, "Option", "Text", "", 0 );
            //:zSearchAndReplace( szText, 500, "\", "\\" )
            zSearchAndReplace( szText, 500, "\\", "\\\\" );
            //:szSrch = "\" + QUOTES 
            ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
            ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
            //:zSearchAndReplace( szText, 500, QUOTES, szSrch )
            zSearchAndReplace( szText, 500, QUOTES, szSrch );
            //:szNavigationTitle = "<%=LangConv.getLanguageText(^" + szText + "^)%>" 
            ZeidonStringCopy( szNavigationTitle, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
            ZeidonStringConcat( szNavigationTitle, 1, 0, szText, 1, 0, 501 );
            ZeidonStringConcat( szNavigationTitle, 1, 0, "^)%>", 1, 0, 501 );
            //:ELSE
         } 
         else
         { 
            //:szNavigationTitle = vDialogMenu.Option.Text
            GetVariableFromAttribute( szNavigationTitle, 0, 'S', 501, vDialogMenu, "Option", "Text", "", 0 );
         } 

         //:END
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
            GetVariableFromAttribute( szTempString_4, 0, 'S', 255, vDialogMenu, "Option", "CSS_Class", "", 0 );
            ZeidonStringCopy( szClass, 1, 0, "class=^", 1, 0, 257 );
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
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );
         //:szOptionTag = vDialogMenu.Option.Tag
         GetVariableFromAttribute( szOptionTag, 0, 'S', 51, vDialogMenu, "Option", "Tag", "", 0 );
         //:szOptionTag = vDialogMenu.Option.Tag
         GetVariableFromAttribute( szOptionTag, 0, 'S', 51, vDialogMenu, "Option", "Tag", "", 0 );
         //:szWriteBuffer = "   csrRC = vKZXMLPGO.cursor( ^DisableMenuOption^ ).setFirst( ^MenuOptionName^, ^" + szOptionTag + "^ );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   csrRC = vKZXMLPGO.cursor( ^DisableMenuOption^ ).setFirst( ^MenuOptionName^, ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szOptionTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialogMenu, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   if ( !csrRC.isSet( ) )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( !csrRC.isSet( ) )", 1, 0, 10001 );
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

         //:szWriteBuffer = "       <li><a href=^#^ " + szClass + " onclick=^" + szActionName + "( )^>" + szNavigationTitle + "</a></li>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "       <li><a href=^#^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^>", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szNavigationTitle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</a></li>", 1, 0, 10001 );
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

      //:END

      //:DropView( vDialogMenu )
      DropView( vDialogMenu );
   } 

   //:END

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
      //://szWriteBuffer = "<%@include file=^./include/leftcontent.inc^ %>"
      //:szWriteBuffer = "<!-- left content include file -->"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<!-- left content include file -->", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "<%@include file=^" + vDialogRoot.Dialog.WEB_LeftSideInclude + "^ %>"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 255, vDialogRoot, "Dialog", "WEB_LeftSideInclude", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%@include file=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
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
//:GenJSPJ_CrteFileTransferForm( VIEW vDialog,
//:                              VIEW vDialogRoot,
//:                              INTEGER lFileJSP,
//:                              STRING ( 10000 ) szWriteBuffer,
//:                              STRING ( 32 ) szIndent,
//:                              STRING ( 1 ) szNoPositioning,
//:                              INTEGER          lOffsetX,
//:                              INTEGER          lOffsetY )

//:   VIEW vDialogTemp  BASED ON LOD TZWDLGSO
zOPER_EXPORT zSHORT OPERATION
GenJSPJ_CrteFileTransferForm( zVIEW     vDialog,
                              zVIEW     vDialogRoot,
                              zLONG     lFileJSP,
                              zPCHAR    szWriteBuffer,
                              zPCHAR    szIndent,
                              zPCHAR    szNoPositioning,
                              zLONG     lOffsetX,
                              zLONG     lOffsetY )
{
   zVIEW     vDialogTemp = 0; 
   //:STRING ( 64 )    szFormName
   zCHAR     szFormName[ 65 ] = { 0 }; 
   //:STRING ( 50 )    szCSS_Class
   zCHAR     szCSS_Class[ 51 ] = { 0 }; 
   //:STRING ( 256 )   szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 32 )    szCtrlTag
   zCHAR     szCtrlTag[ 33 ] = { 0 }; 
   //:STRING ( 1024 )  szStyle
   zCHAR     szStyle[ 1025 ] = { 0 }; 
   //:STRING ( 34 )    szActionTag
   zCHAR     szActionTag[ 35 ] = { 0 }; 
   //:STRING ( 50 )    szControlType
   zCHAR     szControlType[ 51 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szHTML5Attr
   zCHAR     szHTML5Attr[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szPlaceholder
   zCHAR     szPlaceholder[ 257 ] = { 0 }; 
   //:STRING ( 16 )  szWidth
   zCHAR     szWidth[ 17 ] = { 0 }; 
   //:STRING ( 16 )  szHeight
   zCHAR     szHeight[ 17 ] = { 0 }; 
   //:STRING ( 1 )   szGroupBoxAbsPosFlag
   zCHAR     szGroupBoxAbsPosFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szGridGroupingFlag
   zCHAR     szGridGroupingFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szGroupIsTable
   zCHAR     szGroupIsTable[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szIncludeFileFlag
   zCHAR     szIncludeFileFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szNoHeightFlag
   zCHAR     szNoHeightFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szNoWidthFlag
   zCHAR     szNoWidthFlag[ 2 ] = { 0 }; 
   //:INTEGER          lControl
   zLONG     lControl = 0; 
   //:INTEGER          lSizeX
   zLONG     lSizeX = 0; 
   //:INTEGER          lSizeY
   zLONG     lSizeY = 0; 
   //:INTEGER          lTrace
   zLONG     lTrace = 0; 
   //:INTEGER        lHeight
   zLONG     lHeight = 0; 
   //:INTEGER        lWidth
   zLONG     lWidth = 0; 
   //:INTEGER        LastY_Pos
   zLONG     LastY_Pos = 0; 
   //:INTEGER        LastY_Height
   zLONG     LastY_Height = 0; 
   //:INTEGER        LastY_PosGroup
   zLONG     LastY_PosGroup = 0; 
   //:INTEGER        LastX_Pos
   zLONG     LastX_Pos = 0; 
   //:INTEGER        LastX_Width
   zLONG     LastX_Width = 0; 
   //:INTEGER        MaxY_HeightForLine
   zLONG     MaxY_HeightForLine = 0; 
   //:INTEGER        X_Size
   zLONG     X_Size = 0; 
   //:INTEGER        Y_Size
   zLONG     Y_Size = 0; 
   //:INTEGER        X_Pos
   zLONG     X_Pos = 0; 
   //:INTEGER        Y_Pos
   zLONG     Y_Pos = 0; 
   //:SHORT            nRC
   zSHORT    nRC = 0; 

   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   //:STRING ( 100 )  szSize
   zCHAR     szSize[ 101 ] = { 0 }; 
   //:STRING ( 100 )  szPosition
   zCHAR     szPosition[ 101 ] = { 0 }; 
   zSHORT    RESULT; 
   zLONG     lTempInteger_0; 
   zLONG     lTempInteger_1; 
   zCHAR     szTempString_0[ 255 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zSHORT    lTempInteger_2; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zLONG     lTempInteger_3; 
   zCHAR     szTempString_11[ 255 ]; 
   zCHAR     szTempString_12[ 255 ]; 
   zLONG     lTempInteger_4; 
   zLONG     lTempInteger_5; 
   zLONG     lTempInteger_6; 
   zCHAR     szTempString_13[ 255 ]; 
   zSHORT    lTempInteger_7; 
   zCHAR     szTempString_14[ 255 ]; 
   zCHAR     szTempString_15[ 255 ]; 
   zCHAR     szTempString_16[ 33 ]; 



   //:// KJS 11/07/16 - For file transfer, since it doesn't place the controls correctly (if there are more controls than the
   //:// edit and button), we are going to try, closing the previous <form> and creating the form for the upload. Any controls
   //:// that are after the "file upload" groupbox, are going to be placed in this form. Because on the actions, we submit the
   //:// original (first) form, this doesn't seem to be a problem, but we will see...
   //:szWriteBuffer = "</form>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</form>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

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

   //:// A groupbox might want the children to be absolutely positioned.  Allow for this.
   //:szGroupBoxAbsPosFlag = ""
   ZeidonStringCopy( szGroupBoxAbsPosFlag, 1, 0, "", 1, 0, 2 );
   //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Absolute Pos"
   RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Absolute Pos", "" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szGroupBoxAbsPosFlag = "Y"
      ZeidonStringCopy( szGroupBoxAbsPosFlag, 1, 0, "Y", 1, 0, 2 );
   } 

   //:END
   //:  
   //:// There are times when the user wants to paint a div that has no height so it will grow with the
   //:// data within it.  This flags the div will have no height.
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

   //:// There are times when the user wants to paint a div that has no width so it will grow with the
   //:// data within it.  This flags the div will have no width.
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

   //:PIX_PER_DU( vDialog, dDLUnits )
   PIX_PER_DU( vDialog, &dDLUnits );

   //:// FORM GENERATION FOR FILE TRANSFER GROUPS
   //:// Create Form statements for each Group of type "File Transfer to Server".
   //:// Note that each Group requires a subcontrol of type EditBox and another of type PushBtn.
   //:CreateViewFromView( vDialogTemp, vDialog )
   CreateViewFromView( &vDialogTemp, vDialog );
   //:NAME VIEW vDialogTemp "vDialogTemp"
   SetNameForView( vDialogTemp, "vDialogTemp", 0, zLEVEL_TASK );

   //:// Generate Form Statement for Group, with hidden field zAction.
   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szFormName = vDialogTemp.Control.Tag
   GetVariableFromAttribute( szFormName, 0, 'S', 65, vDialogTemp, "Control", "Tag", "", 0 );
   //:szWriteBuffer = "<form name=^" + szFormName + "^  id=^" + szFormName + "^ method=^post^ enctype=^multipart/form-data^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<form name=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^  id=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szFormName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ method=^post^ enctype=^multipart/form-data^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   <input name=^zAction^ id=^zAction^ type=^hidden^ value=^HELP^>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zAction^ id=^zAction^ type=^hidden^ value=^HELP^>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:   //CreateAbsolStyleString( vDialogTemp, szStyle, lSizeX, lSizeY, "" )
   //:   // Initialize the szStyle variable with X and Y values.
   //:   IF szNoPositioning = "Y"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 

      //:   lWidth = vDialog.Control.SZDLG_X * dDLUnits
      GetIntegerFromAttribute( &lTempInteger_0, vDialog, "Control", "SZDLG_X" );
      lWidth = lTempInteger_0 * dDLUnits;
      //:   lHeight = vDialog.Control.SZDLG_Y * dDLUnits
      GetIntegerFromAttribute( &lTempInteger_1, vDialog, "Control", "SZDLG_Y" );
      lHeight = lTempInteger_1 * dDLUnits;
      //:   zIntegerToString( szWidth, 10, lWidth )
      zIntegerToString( szWidth, 10, lWidth );
      //:   zIntegerToString( szHeight, 10, lHeight )
      zIntegerToString( szHeight, 10, lHeight );

      //:   // If szGroupBoxAbsPosFlag = "Y" then we are saying that the children of this group box will
      //:   // be absolutely positioned.
      //:   IF szGroupBoxAbsPosFlag = "Y"
      if ( ZeidonStringCompare( szGroupBoxAbsPosFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 

         //:   //szNoPositioningHold = szNoPositioning
         //:   //szNoPositioning = ""  // we want absolute positioning on all child controls
         //:   
         //:   IF szNoHeightFlag = "Y" // We might not want the groupbox to have a height (so it grows)
         if ( ZeidonStringCompare( szNoHeightFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:   szStyle = "style=^float:left;position:relative; width:" + szWidth + "px;^"
            ZeidonStringCopy( szStyle, 1, 0, "style=^float:left;position:relative; width:", 1, 0, 1025 );
            ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 1025 );
            ZeidonStringConcat( szStyle, 1, 0, "px;^", 1, 0, 1025 );
            //:ELSE
         } 
         else
         { 
            //:   //zIntegerToString( szHeight, 10, lHeight * dDLUnits )
            //:   szStyle = "style=^float:left;position:relative; width:" + szWidth + "px; height:" + szHeight + "px;^"
            ZeidonStringCopy( szStyle, 1, 0, "style=^float:left;position:relative; width:", 1, 0, 1025 );
            ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 1025 );
            ZeidonStringConcat( szStyle, 1, 0, "px; height:", 1, 0, 1025 );
            ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 1025 );
            ZeidonStringConcat( szStyle, 1, 0, "px;^", 1, 0, 1025 );
         } 

         //:   END                      
         //:ELSE 
      } 
      else
      { 
         //:IF szNoHeightFlag = "Y" AND szNoWidthFlag = "Y"
         if ( ZeidonStringCompare( szNoHeightFlag, 1, 0, "Y", 1, 0, 2 ) == 0 && ZeidonStringCompare( szNoWidthFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:szStyle = ""
            ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 1025 );
            //:ELSE
         } 
         else
         { 
            //:IF szNoHeightFlag = "Y"
            if ( ZeidonStringCompare( szNoHeightFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
            { 
               //:// We might not want the groupbox to have a height (so it grows)
               //:szStyle = "style=^width:" + szWidth + "px;^"
               ZeidonStringCopy( szStyle, 1, 0, "style=^width:", 1, 0, 1025 );
               ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 1025 );
               ZeidonStringConcat( szStyle, 1, 0, "px;^", 1, 0, 1025 );
               //:ELSE
            } 
            else
            { 
               //:IF szNoWidthFlag = "Y"
               if ( ZeidonStringCompare( szNoWidthFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
               { 
                  //:// We might not want the groupbox to have a width (so it grows)
                  //:szStyle = "style=^height:" + szHeight + "px;^"
                  ZeidonStringCopy( szStyle, 1, 0, "style=^height:", 1, 0, 1025 );
                  ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 1025 );
                  ZeidonStringConcat( szStyle, 1, 0, "px;^", 1, 0, 1025 );
                  //:ELSE
               } 
               else
               { 
                  //:CreateNoPosStyleString( vDialog, szStyle, "" )
                  CreateNoPosStyleString( vDialog, szStyle, "" );
               } 

               //:END
            } 

            //:END
         } 

         //:END
      } 

      //:   END
      //:ELSE
   } 
   else
   { 
      //:IF  szNoPositioning = "S" // We are not creating any style information.
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = ""
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 1025 );
         //:ELSE
      } 
      else
      { 
         //:CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
         CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" );
      } 

      //:END
   } 

   //:   END

   //:   szClass = ""
   ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
   //:   IF vDialogTemp.Control.CSS_Class != ""
   if ( CompareAttributeToString( vDialogTemp, "Control", "CSS_Class", "" ) != 0 )
   { 
      //:   szClass = " class=^" + vDialogTemp.Control.CSS_Class + "^"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 255, vDialogTemp, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, szTempString_0, 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
   } 

   //:   END
   //:   szWriteBuffer = "<div " + szStyle + szClass + ">  <!-- " + vDialogTemp.Control.Tag + " --> "
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<div ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ">  <!-- ", 1, 0, 10001 );
   GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " --> ", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:   // Get Group positions for adding to subcontrols.
   //:   //lSizeX = vDialogTemp.Control.PSDLG_X * dDLUnits
   //:   //lSizeY = vDialogTemp.Control.PSDLG_Y * dDLUnits

   //:   // Generate hidden field zTargetFileName, with JSP to retrieve name.
   //:   // We are currently positioned on the GroupBox and need to reposition on the subcontrol Button
   //:   // to generate the FileName mapping..
   //:   szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:   szWriteBuffer = "   strErrorMapValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = ^^;", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:   SetViewToSubobject( vDialogTemp, "CtrlCtrl" )
   SetViewToSubobject( vDialogTemp, "CtrlCtrl" );
   //:   FOR EACH vDialogTemp.Control
   RESULT = SetCursorFirstEntity( vDialogTemp, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:   IF vDialogTemp.ControlDef.Tag = "PushBtn"
      if ( CompareAttributeToString( vDialogTemp, "ControlDef", "Tag", "PushBtn" ) == 0 )
      { 
         //:   IF vDialogTemp.CtrlMapER_Attribute EXISTS
         lTempInteger_2 = CheckExistenceOfEntity( vDialogTemp, "CtrlMapER_Attribute" );
         if ( lTempInteger_2 == 0 )
         { 
            //:   // The mapping for the Push Button specifies the attribute that contains the Target File Name (without suffix).

            //:// szWriteBuffer = "   strSessionId = session.getId( );"
            //:// WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )

            //:   szWriteBuffer = "   " + vDialogTemp.CtrlMapView.Name + " = " +
            //:                   "task.getViewByName( ^" + vDialogTemp.CtrlMapView.Name + "^ );"
            GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialogTemp.CtrlMapView.Name + " ) )"
            GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " ) )", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

            //:   szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "      nRC = " + vDialogTemp.CtrlMapView.Name + ".cursor( ^" +
            //:                   vDialogTemp.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
            GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialogTemp, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "      if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "         strErrorMapValue = " +
            //:                   vDialogTemp.CtrlMapView.Name + ".cursor(^" + vDialogTemp.CtrlMapRelatedEntity.Name +
            //:                   "^).getAttribute( ^" +
            //:                   vDialogTemp.CtrlMapER_Attribute.Name + "^ ).getString( ^^ );"
            GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialogTemp, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor(^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialogTemp, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^).getAttribute( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialogTemp, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^^ );", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "   }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

            //:   IF (lTrace = 1)
            if ( lTrace == 1 )
            { 
               //:   szWriteBuffer = "   else"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   else", 1, 0, 10001 );
               //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:   szWriteBuffer = "      task.log().info( ^Invalid View: ^ + ^" + vDialogTemp.Control.Tag + "^ );"
               GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      task.log().info( ^Invalid View: ^ + ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
               //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            } 

            //:   END
         } 


         //:   END
      } 

      RESULT = SetCursorNextEntity( vDialogTemp, "Control", "" );
      //:   END
   } 

   //:   END
   //:   szWriteBuffer = "%>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   //:   szWriteBuffer = "   <input name=^zTargetFileName^ id=^zTargetFileName^ type=^hidden^ value=^<%=strErrorMapValue%>^ >"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^zTargetFileName^ id=^zTargetFileName^ type=^hidden^ value=^<%=strErrorMapValue%>^ >", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

   //:   IF szGroupIsTable = "Y" 
   if ( ZeidonStringCompare( szGroupIsTable, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:   szWriteBuffer = "<table>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<table>", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "<tr>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<tr>", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "<td>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<td>", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
   } 

   //:   END

   //:   // Process EditBox and PushBtn as subcontrols.
   //:   FOR EACH vDialogTemp.Control
   RESULT = SetCursorFirstEntity( vDialogTemp, "Control", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 

      //:   IF vDialogTemp.ControlDef.Tag = "EditBox"
      if ( CompareAttributeToString( vDialogTemp, "ControlDef", "Tag", "EditBox" ) == 0 )
      { 
         //:   szCtrlTag     = vDialogTemp.Control.Tag
         GetVariableFromAttribute( szCtrlTag, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
         //:   szControlType = vDialogTemp.ControlDef.Tag
         GetVariableFromAttribute( szControlType, 0, 'S', 51, vDialogTemp, "ControlDef", "Tag", "", 0 );
         //:   szWriteBuffer = "   <% /* " + szCtrlTag + ":" + szControlType + " */ %>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <% /* ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ":", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szControlType, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " */ %>", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

         //:   //CreateAbsolStyleString( vDialogTemp, szStyle, lSizeX, lSizeY, "" )
         //:   zIntegerToString( szWidth, 10, vDialogTemp.Control.SZDLG_X * dDLUnits )
         GetIntegerFromAttribute( &lTempInteger_3, vDialogTemp, "Control", "SZDLG_X" );
         zIntegerToString( szWidth, 10, lTempInteger_3 * dDLUnits );
         //:   szSize = "width:" + szWidth + "px;"
         ZeidonStringCopy( szSize, 1, 0, "width:", 1, 0, 101 );
         ZeidonStringConcat( szSize, 1, 0, szWidth, 1, 0, 101 );
         ZeidonStringConcat( szSize, 1, 0, "px;", 1, 0, 101 );
         //:   // If zNoPositioning is null then we are using absolute positioning for controls
         //:   IF  szNoPositioning = ""
         if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
         { 
            //:   CreateAbsolPosString( vDialogTemp, szPosition, lOffsetX, lOffsetY )
            CreateAbsolPosString( vDialogTemp, szPosition, lOffsetX, lOffsetY );
         } 

         //:   END
         //:   
         //:   IF szNoPositioning = "S" 
         if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
         { 
            //:   szStyle = ""
            ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 1025 );
            //:ELSE 
         } 
         else
         { 
            //:   FixStyleString( szStyle, szSize, szPosition,  "<%=strErrorColor%>"  )
            FixStyleString( szStyle, szSize, szPosition, "<%=strErrorColor%>" );
         } 

         //:   END
         //:   
         //:   //szStyle = szStyle + szTabIndex
         //:   szTitleHTML = ""
         ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
         //:   szTitle = vDialogTemp.Control.DIL_Text
         GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialogTemp, "Control", "DIL_Text", "", 0 );
         //:   IF szTitle != ""
         if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
         { 
            //:   szTitleHTML = " title=^" + szTitle + "^ "
            ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
            ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
            ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
         } 

         //:   END
         //:   
         //:   szPlaceholder = ""
         ZeidonStringCopy( szPlaceholder, 1, 0, "", 1, 0, 257 );
         //:   IF vDialogTemp.Control.WebPlaceholder != ""
         if ( CompareAttributeToString( vDialogTemp, "Control", "WebPlaceholder", "" ) != 0 )
         { 
            //:   szPlaceholder = " placeholder=^" + vDialogTemp.Control.WebPlaceholder + "^ "
            GetVariableFromAttribute( szTempString_11, 0, 'S', 255, vDialogTemp, "Control", "WebPlaceholder", "", 0 );
            ZeidonStringCopy( szPlaceholder, 1, 0, " placeholder=^", 1, 0, 257 );
            ZeidonStringConcat( szPlaceholder, 1, 0, szTempString_11, 1, 0, 257 );
            ZeidonStringConcat( szPlaceholder, 1, 0, "^ ", 1, 0, 257 );
         } 

         //:   END
         //:   
         //:   szHTML5Attr = ""
         ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
         //:   IF vDialogTemp.Control.WebHTML5Attribute != ""
         if ( CompareAttributeToString( vDialogTemp, "Control", "WebHTML5Attribute", "" ) != 0 )
         { 
            //:   szHTML5Attr = " " + vDialogTemp.Control.WebHTML5Attribute + " "
            GetVariableFromAttribute( szTempString_12, 0, 'S', 255, vDialogTemp, "Control", "WebHTML5Attribute", "", 0 );
            ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
            ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_12, 1, 0, 257 );
            ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
         } 

         //:   END
         //:   
         //:   // For some reason with the <input type="file" control, the width property doesn't
         //:   // seem to size the width correctly.  Use the "size" attribute instead.  The weird thing
         //:   // is that if I don't include the width in style, then the "Browse" button that gets
         //:   // created is not inline with the field that displays the upload file. ???!!!
         //:   zIntegerToString( szWidth, 10, vDialogTemp.Control.SZDLG_X / 3.5 )
         GetIntegerFromAttribute( &lTempInteger_4, vDialogTemp, "Control", "SZDLG_X" );
         zIntegerToString( szWidth, 10, lTempInteger_4 / (ZDecimal) 3.5 );

         //:   szClass = vDialogTemp.Control.CSS_Class
         GetVariableFromAttribute( szClass, 0, 'S', 257, vDialogTemp, "Control", "CSS_Class", "", 0 );
         //:   IF szClass = ""
         if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
         { 
            //:   szWriteBuffer = "   <input name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^" + szWidth + "^ " + szStyle + " type=^file^  >"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " type=^file^  >", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:   szWriteBuffer = "   <input class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^" + szWidth + "^ " + szStyle + " type=^file^  >"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input class=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " type=^file^  >", 1, 0, 10001 );
         } 

         //:   END
         //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );

         //:   LastY_Pos    = vDialogTemp.Control.PSDLG_Y
         GetIntegerFromAttribute( &LastY_Pos, vDialogTemp, "Control", "PSDLG_Y" );
         //:   LastY_Height = vDialogTemp.Control.SZDLG_Y
         GetIntegerFromAttribute( &LastY_Height, vDialogTemp, "Control", "SZDLG_Y" );
         //:   LastX_Pos    = vDialogTemp.Control.PSDLG_X
         GetIntegerFromAttribute( &LastX_Pos, vDialogTemp, "Control", "PSDLG_X" );
         //:   LastX_Width  = vDialogTemp.Control.SZDLG_X
         GetIntegerFromAttribute( &LastX_Width, vDialogTemp, "Control", "SZDLG_X" );
      } 

      //:   END
      //:   // We are just assuming that the "Unload" button is positioned after the edit field.
      //:   IF vDialogTemp.ControlDef.Tag = "PushBtn"
      if ( CompareAttributeToString( vDialogTemp, "ControlDef", "Tag", "PushBtn" ) == 0 )
      { 

         //:   IF szGroupIsTable = "Y" AND ( vDialogTemp.Control.PSDLG_Y > LastY_Pos )
         if ( ZeidonStringCompare( szGroupIsTable, 1, 0, "Y", 1, 0, 2 ) == 0 && ( CompareAttributeToInteger( vDialogTemp, "Control", "PSDLG_Y", LastY_Pos ) > 0 ) )
         { 
            //:   szWriteBuffer = "</td>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "</td>", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "</tr>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "</tr>", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "<tr>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<tr>", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "<td>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<td>", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:ELSE
         } 
         else
         { 
            //:IF szGroupIsTable = "Y" AND ( vDialogTemp.Control.PSDLG_Y <= LastY_Pos ) 
            if ( ZeidonStringCompare( szGroupIsTable, 1, 0, "Y", 1, 0, 2 ) == 0 && ( CompareAttributeToInteger( vDialogTemp, "Control", "PSDLG_Y", LastY_Pos ) <= 0 ) )
            { 
               //:szWriteBuffer = "</td>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "</td>", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "<td>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "<td>", 1, 0, 10001 );
               //:WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )            
               WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            } 

            //:END
         } 

         //:   END

         //:   // Determine if there is blank space in between the y coordinates of the last
         //:   // control and the current control.  If so, then we need to put in a div as a spacer control.
         //:   IF szNoPositioning = "Y" AND szGroupIsTable = "" AND ( vDialogTemp.Control.PSDLG_Y > LastY_Pos )
         if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 && ZeidonStringCompare( szGroupIsTable, 1, 0, "", 1, 0, 2 ) == 0 && ( CompareAttributeToInteger( vDialogTemp, "Control", "PSDLG_Y", LastY_Pos ) > 0 ) )
         { 

            //:      Y_Size = ( vDialogTemp.Control.PSDLG_Y - ( LastY_Pos + LastY_Height ) ) * dDLUnits
            GetIntegerFromAttribute( &lTempInteger_5, vDialogTemp, "Control", "PSDLG_Y" );
            Y_Size = ( lTempInteger_5 - ( LastY_Pos + LastY_Height ) ) * dDLUnits;
            //:      X_Size = 10
            X_Size = 10;
            //:      zIntegerToString( szHeight, 16, Y_Size )
            zIntegerToString( szHeight, 16, Y_Size );
            //:      zIntegerToString( szWidth, 16, X_Size )
            zIntegerToString( szWidth, 16, X_Size );
            //:      szWriteBuffer = ""
            ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
            //:      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:      szWriteBuffer = " <!-- This is added as a line spacer -->"
            ZeidonStringCopy( szWriteBuffer, 1, 0, " <!-- This is added as a line spacer -->", 1, 0, 10001 );
            //:      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:      szWriteBuffer = "<div style=^height:" + szHeight + "px;width:" + szWidth + "px;^></div>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<div style=^height:", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHeight, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "px;width:", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "px;^></div>", 1, 0, 10001 );
            //:      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         } 

         //:   END
         //:   IF szNoPositioning = "Y" AND szGroupIsTable = "" AND ( vDialogTemp.Control.PSDLG_X > 0 )
         if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 && ZeidonStringCompare( szGroupIsTable, 1, 0, "", 1, 0, 2 ) == 0 && ( CompareAttributeToInteger( vDialogTemp, "Control", "PSDLG_X", 0 ) > 0 ) )
         { 

            //:      X_Size = ( vDialogTemp.Control.PSDLG_X ) * dDLUnits
            GetIntegerFromAttribute( &lTempInteger_6, vDialogTemp, "Control", "PSDLG_X" );
            X_Size = ( lTempInteger_6 ) * dDLUnits;
            //:      Y_Size = 1
            Y_Size = 1;
            //:      zIntegerToString( szHeight, 16, Y_Size )
            zIntegerToString( szHeight, 16, Y_Size );
            //:      zIntegerToString( szWidth, 16, X_Size )
            zIntegerToString( szWidth, 16, X_Size );
            //:      szWriteBuffer = ""
            ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
            //:      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:      szWriteBuffer = " <!-- This is added as a width spacer -->"
            ZeidonStringCopy( szWriteBuffer, 1, 0, " <!-- This is added as a width spacer -->", 1, 0, 10001 );
            //:      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:      szWriteBuffer = "<div style=^height:1px;width:" + szWidth + "px;float:left;^></div>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<div style=^height:1px;width:", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "px;float:left;^></div>", 1, 0, 10001 );
            //:      WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         } 

         //:      //szWriteBuffer = "<div style=^height:1px;width:" + szWidth + "px;float:left;^></div>   <!-- Width Spacer -->"
         //:      //WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         //:   END
         //:            
         //:   szCtrlTag     = vDialogTemp.Control.Tag
         GetVariableFromAttribute( szCtrlTag, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
         //:   szControlType = vDialogTemp.ControlDef.Tag
         GetVariableFromAttribute( szControlType, 0, 'S', 51, vDialogTemp, "ControlDef", "Tag", "", 0 );
         //:   szWriteBuffer = "   <% /* " + szCtrlTag + ":" + szControlType + " */ %>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <% /* ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ":", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szControlType, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " */ %>", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

         //:   //CreateAbsolStyleString( vDialogTemp, szStyle, lSizeX, lSizeY, "" )
         //:   IF szNoPositioning = "Y"
         if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:   CreateNoPosStyleString( vDialogTemp, szStyle, "" )
            CreateNoPosStyleString( vDialogTemp, szStyle, "" );
            //:ELSE
         } 
         else
         { 
            //:IF szNoPositioning = "S" // No style information
            if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
            { 
               //:szStyle = "" 
               ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 1025 );
               //:ELSE 
            } 
            else
            { 
               //:CreateAbsolStyleString( vDialogTemp, szStyle, lOffsetX, lOffsetY, "" )
               CreateAbsolStyleString( vDialogTemp, szStyle, lOffsetX, lOffsetY, "" );
            } 

            //:END
         } 

         //:   END
         //:   
         //:   //If we put a title on the control, when the mouse is hovered over the control, this text will display.
         //:   szTitleHTML = ""
         ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
         //:   szTitle = vDialogTemp.Control.DIL_Text
         GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialogTemp, "Control", "DIL_Text", "", 0 );
         //:   IF szTitle != ""
         if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
         { 
            //:   szTitleHTML = " title=^" + szTitle + "^ "
            ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
            ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
            ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
         } 

         //:   END

         //:   szHTML5Attr = ""
         ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
         //:   IF vDialogTemp.Control.WebHTML5Attribute != ""
         if ( CompareAttributeToString( vDialogTemp, "Control", "WebHTML5Attribute", "" ) != 0 )
         { 
            //:   szHTML5Attr = " " + vDialogTemp.Control.WebHTML5Attribute + " "
            GetVariableFromAttribute( szTempString_13, 0, 'S', 255, vDialogTemp, "Control", "WebHTML5Attribute", "", 0 );
            ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
            ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_13, 1, 0, 257 );
            ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
         } 

         //:   END

         //:   szActionTag = ""
         ZeidonStringCopy( szActionTag, 1, 0, "", 1, 0, 35 );
         //:   IF vDialogTemp.EventAct EXISTS
         lTempInteger_7 = CheckExistenceOfEntity( vDialogTemp, "EventAct" );
         if ( lTempInteger_7 == 0 )
         { 
            //:   szActionTag = vDialogTemp.EventAct.Tag
            GetVariableFromAttribute( szActionTag, 0, 'S', 35, vDialogTemp, "EventAct", "Tag", "", 0 );
         } 

         //:   END
         //:   szClass = vDialogTemp.Control.CSS_Class
         GetVariableFromAttribute( szClass, 0, 'S', 257, vDialogTemp, "Control", "CSS_Class", "", 0 );
         //:   //IF szNoPositioning = "Y"
         //:   //   szWriteBuffer = "<div style=^float:left;^>"
         //:   //   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         //:   //END
         //:   IF szClass = ""
         if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
         { 
            //:   //szWriteBuffer = "   <input type=^submit^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " + " value=^" + vDialogTemp.Control.Text + "^" +
            //:   //                " onclick=^" + szActionTag + "()^ " + szStyle + " >"
            //:   szWriteBuffer = "   <button type=^button^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " +
            //:                   " onclick=^" + szActionTag + "()^ " + szStyle + szTitleHTML + szHTML5Attr + " >" + vDialogTemp.Control.Text + "</button>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   <button type=^button^ name=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "()^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " >", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_14, 0, 'S', 255, vDialogTemp, "Control", "Text", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</button>", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:   //szWriteBuffer = "   <input class=^" + szClass + "^ type=^submit^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " + " value=^" + vDialogTemp.Control.Text + "^" +
            //:   //                " onclick=^" + szActionTag + "()^ " + szStyle + " >"
            //:   szWriteBuffer = "   <button type=^button^ class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " +
            //:                   " onclick=^" + szActionTag + "()^ " + szStyle + szTitleHTML + szHTML5Attr + " >" + vDialogTemp.Control.Text + "</button>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   <button type=^button^ class=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "()^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " >", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_15, 0, 'S', 255, vDialogTemp, "Control", "Text", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_15, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</button>", 1, 0, 10001 );
         } 

         //:   END
         //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 );
         //:   //IF szNoPositioning = "Y"
         //:   //   szWriteBuffer = "</div>"
         //:   //   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
         //:   //END
         //:   IF szGroupIsTable = "Y" 
         if ( ZeidonStringCompare( szGroupIsTable, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:   szWriteBuffer = "</td>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "</td>", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "</tr>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "</tr>", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
            //:   szWriteBuffer = "</table>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "</table>", 1, 0, 10001 );
            //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );
         } 

         //:   END
      } 

      RESULT = SetCursorNextEntity( vDialogTemp, "Control", "" );
      //:   END
   } 

   //:   END
   //:   ResetViewFromSubobject( vDialogTemp )
   ResetViewFromSubobject( vDialogTemp );

   //:   szWriteBuffer = "</div>  <!-- " + vDialogTemp.Control.Tag + " --> "
   GetVariableFromAttribute( szTempString_16, 0, 'S', 33, vDialogTemp, "Control", "Tag", "", 0 );
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</div>  <!-- ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_16, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " --> ", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 0 );

   //:   //szWriteBuffer = "</form>"
   //:   //WL_QC( vDialog, lFileJSP, szWriteBuffer, "^", 1 )

   //:   //lControl = zQUAL_STRING + zPOS_NEXT + zRECURS
   //:   //szCtrlTag = "File Transfer to Server"
   //:   //nRC = SetEntityCursor( vDialogTemp, "WebControlProperty", "Name", lControl,
   //:   //                       szCtrlTag, "", "", 0, "Window", "" )
   //://END
   //:DropView( vDialogTemp )
   DropView( vDialogTemp );
   return( 0 );
// END
} 


//:GLOBAL OPERATION
//:GenJSPJ_CrteListBoxAsList( VIEW vDialog,
//:                           INTEGER lFile,
//:                           STRING ( 10000 ) szWriteBuffer,
//:                           STRING ( 50 )    szIndent,
//:                           STRING ( 32 )    szCtrlTag,
//:                           STRING ( 1 )     szNoPositioning,
//:                           INTEGER lOffsetX,
//:                           INTEGER lOffsetY )

//:   VIEW vScope      BASED ON LOD TZWDLGSO  // identifies scoping entity for list entries
zOPER_EXPORT zSHORT OPERATION
GenJSPJ_CrteListBoxAsList( zVIEW     vDialog,
                           zLONG     lFile,
                           zPCHAR    szWriteBuffer,
                           zPCHAR    szIndent,
                           zPCHAR    szCtrlTag,
                           zPCHAR    szNoPositioning,
                           zLONG     lOffsetX,
                           zLONG     lOffsetY )
{
   zVIEW     vScope = 0; 
   //:VIEW vDialogRoot BASED ON LOD TZWDLGSO  // identifies scoping entity for list entries
   zVIEW     vDialogRoot = 0; 
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
   //:STRING ( 32 )  szjMobile
   zCHAR     szjMobile[ 33 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szHTML5Attr
   zCHAR     szHTML5Attr[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) ListBoxDoubleClickAction
   zCHAR     ListBoxDoubleClickAction[ 257 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLength
   zCHAR     szMaxStringLength[ 11 ] = { 0 }; 
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
   //:INTEGER        lMaxStringLength
   zLONG     lMaxStringLength = 0; 
   zCHAR     szTempString_0[ 1026 ]; 
   zCHAR     szTempString_1[ 1026 ]; 
   zLONG     lTempInteger_0; 
   zLONG     lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_4; 
   zSHORT    lTempInteger_5; 
   zCHAR     szTempString_2[ 1026 ]; 
   zCHAR     szTempString_3[ 1026 ]; 
   zCHAR     szTempString_4[ 1026 ]; 
   zSHORT    lTempInteger_6; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 1026 ]; 
   zCHAR     szTempString_7[ 1026 ]; 
   zSHORT    lTempInteger_7; 
   zSHORT    lTempInteger_8; 
   zCHAR     szTempString_8[ 1026 ]; 
   zCHAR     szTempString_9[ 1026 ]; 
   zSHORT    lTempInteger_9; 
   zCHAR     szTempString_10[ 1026 ]; 


   //:szStyle = "width:" + szWidth + "px; height:" + szHeight + "px;"
   ZeidonStringCopy( szStyle, 1, 0, "width:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px; height:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
   //:IF vDialog.Control.CSS_Class = ""
   if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) == 0 )
   { 
      //:szClass = ""
      ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
      //:ELSE
   } 
   else
   { 
      //:szClass = " class=^" + vDialog.Control.CSS_Class + "^"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 1026, vDialog, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, szTempString_0, 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
   } 

   //:END

   //:szHTML5Attr = ""
   ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
   //:IF vDialog.Control.WebHTML5Attribute != ""
   if ( CompareAttributeToString( vDialog, "Control", "WebHTML5Attribute", "" ) != 0 )
   { 
      //:szHTML5Attr = " " + vDialog.Control.WebHTML5Attribute + " "
      GetVariableFromAttribute( szTempString_1, 0, 'S', 1026, vDialog, "Control", "WebHTML5Attribute", "", 0 );
      ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_1, 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
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
   //:szStyle = " style=^width:" + szWidth + "px;height:" + szHeight + "px;"
   ZeidonStringCopy( szStyle, 1, 0, " style=^width:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;height:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );

   //:// If szNoPositioning is null then we are using absolute positioning on controls.
   //:IF szNoPositioning = ""
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
      //://CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
      //:ELSE
   } 
   else
   { 
      //:IF szNoPositioning = "S"
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = "" 
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
      } 

      //:END
   } 

   //:END

   //:IF szStyle != ""
   if ( ZeidonStringCompare( szStyle, 1, 0, "", 1, 0, 257 ) != 0 )
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

   //:szSelectFunction = "OnClick"
   ZeidonStringCopy( szSelectFunction, 1, 0, "OnClick", 1, 0, 11 );

   //:   // Set cursor to the scoping entity if one exists
   //:   CreateViewFromViewForTask( vScope, vDialog, 0 )
   CreateViewFromViewForTask( &vScope, vDialog, 0 );
   //:   SET CURSOR NEXT vScope.CtrlMap
   RESULT = SetCursorNextEntity( vScope, "CtrlMap", "" );
   //:   
   //:// Put in data-role if this is for a jmobile. kkk
   //:GetViewByName( vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK )   
   GetViewByName( &vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK );
   //:IF vDialogRoot.WndStyle.Tag = "jMobile Window"
   if ( CompareAttributeToString( vDialogRoot, "WndStyle", "Tag", "jMobile Window" ) == 0 )
   { 
      //:szjMobile = " data-role=^listview^ "
      ZeidonStringCopy( szjMobile, 1, 0, " data-role=^listview^ ", 1, 0, 33 );
   } 

   //:END      

   //:szWriteBuffer = "   <ul id=^" + szCtrlTag + "^ name=^" + szCtrlTag + "^" + szClass + szjMobile + szHTML5Attr + szStyle + szDisabled + ">"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <ul id=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szjMobile, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:   szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:   IF vDialog.CtrlMapView EXISTS
   lTempInteger_4 = CheckExistenceOfEntity( vDialog, "CtrlMapView" );
   if ( lTempInteger_4 == 0 )
   { 


      //:   // See if a list entity has been specified, and if so, use it.
      //:   // Since this is a listbox I believe this should always be specified.
      //:   IF vDialog.CtrlMapLOD_Entity EXISTS
      lTempInteger_5 = CheckExistenceOfEntity( vDialog, "CtrlMapLOD_Entity" );
      if ( lTempInteger_5 == 0 )
      { 
         //:   szListEntityName = vDialog.CtrlMapLOD_Entity.Name
         GetVariableFromAttribute( szListEntityName, 0, 'S', 33, vDialog, "CtrlMapLOD_Entity", "Name", "", 0 );
      } 

      //:   END




      //:   szWriteBuffer = "   " + vDialog.CtrlMapView.Name + " = " +
      //:                   "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_3, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) )"
      GetVariableFromAttribute( szTempString_4, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) )", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   
      //:         szWriteBuffer = "      long   lEntityKey;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      long   lEntityKey;", 1, 0, 10001 );
      //:         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:         szWriteBuffer = "      String strEntityKey;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      String strEntityKey;", 1, 0, 10001 );
      //:         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   
      //:   
      //:   szWriteBuffer = "      strComboCurrentValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      strComboCurrentValue = ^^;", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      View v" + szCtrlTag + ";"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      View v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ";", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:   szAttributeName = ""
      ZeidonStringCopy( szAttributeName, 1, 0, "", 1, 0, 33 );
      //:   szEntityName = ""
      ZeidonStringCopy( szEntityName, 1, 0, "", 1, 0, 33 );
      //:   szContextName = ""
      ZeidonStringCopy( szContextName, 1, 0, "", 1, 0, 33 );


      //:// Getting view

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
         lTempInteger_6 = CheckExistenceOfEntity( vScope, "CtrlMapLOD_Entity" );
         if ( lTempInteger_6 == 0 )
         { 
            //:   szScopingEntityName = "^" + vScope.CtrlMapLOD_Entity.Name + "^"
            GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vScope, "CtrlMapLOD_Entity", "Name", "", 0 );
            ZeidonStringCopy( szScopingEntityName, 1, 0, "^", 1, 0, 33 );
            ZeidonStringConcat( szScopingEntityName, 1, 0, szTempString_5, 1, 0, 33 );
            ZeidonStringConcat( szScopingEntityName, 1, 0, "^", 1, 0, 33 );
         } 

         //:   END
      } 

      //:   END

      //:   szWriteBuffer = "      v" + szCtrlTag + " = " + vDialog.CtrlMapView.Name + ".newView( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".newView( );", 1, 0, 10001 );
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
         //:   szWriteBuffer = "      csrRC = v" + szCtrlTag + ".cursor( ^" +
         //:                                szListEntityName + "^ ).setFirst( " + szScopingEntityName + " );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      csrRC = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setFirst( ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szScopingEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:   szWriteBuffer = "      csrRC = v" + szCtrlTag + ".cursor( ^" + szListEntityName + "^ ).setFirstWithinOi( );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      csrRC = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setFirstWithinOi( );", 1, 0, 10001 );
      } 

      //:   END

      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      while ( csrRC.isSet() )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      while ( csrRC.isSet() )", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );


      //:         szWriteBuffer = "         lEntityKey = v" + szCtrlTag +
      //:                         ".cursor( ^" + vDialog.CtrlMapLOD_Entity.Name + "^ ).getEntityKey( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         lEntityKey = v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 1026, vDialog, "CtrlMapLOD_Entity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getEntityKey( );", 1, 0, 10001 );
      //:         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:         szWriteBuffer = "         strEntityKey = Long.toString( lEntityKey );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strEntityKey = Long.toString( lEntityKey );", 1, 0, 10001 );
      //:         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //://

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

         //:   szWriteBuffer = "      nRC = v" + szCtrlTag + ".cursor( ^" +
         //:                   szEntityName + "^ ).checkExistenceOfEntity( ).toInt();"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "      if ( nRC >= 0 )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "      {"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
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

         //:   IF vDialog.CtrlMapER_Domain.MaxStringLth > 254
         if ( CompareAttributeToInteger( vDialog, "CtrlMapER_Domain", "MaxStringLth", 254 ) > 0 )
         { 
            //:   lMaxStringLength = vDialog.CtrlMapER_Domain.MaxStringLth
            GetIntegerFromAttribute( &lMaxStringLength, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
            //:   szMaxStringLength = lMaxStringLength
            ZeidonStringConvertFromNumber( szMaxStringLength, 1, 0, 10, lMaxStringLength, (ZDecimal) 0.0, "I" );
            //:ELSE
         } 
         else
         { 
            //:   szMaxStringLength = "254"
            ZeidonStringCopy( szMaxStringLength, 1, 0, "254", 1, 0, 11 );
         } 

         //:   END

         //:   szWriteBuffer = "         strComboCurrentValue = v" + szCtrlTag +
         //:            ".cursor( ^" +
         //:            szEntityName + "^ ).getAttribute( ^" +
         //:            szAttributeName + "^ ).getString( ^" + szContextName + "^ );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strComboCurrentValue = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szAttributeName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:   // KJS 02/15/11 - Thinking I need to add code to change values returned as null to ""
         //:   szWriteBuffer = "         if ( strComboCurrentValue == null )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strComboCurrentValue == null )", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "            strComboCurrentValue = ^^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            strComboCurrentValue = ^^;", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "      }"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );



         //:/****************************************         */

         //://szWriteBuffer = "       <li><a href=^#^ " + szClass + " onclick=^" + szActionName + "( )^>" + szNavigationTitle + "</a></li>"
         //:// In the case of jmobile, I am putting the HTML5 and class on the <a href
         //://IF vDialogRoot.WndStyle.Tag = "jMobile Window"
         //://szWriteBuffer = "       <li id=^" + szCtrlTag + "^ name=^" + szCtrlTag + "^><a href=^#^ " + szHTML5Attr + szClass + " onclick=^" + szActionName + "()^>" + szNavigationTitle + "</a></li>"
         //://ELSE
         //://szWriteBuffer = "       <li id=^" + szCtrlTag + "^ name=^" + szCtrlTag + "^" + szHTML5Attr + szClass + "><a href=^#^ " + " onclick=^" + szActionName + "()^>" + szNavigationTitle + "</a></li>"
         //://END
         //://WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )

         //:   szWriteBuffer = "%>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:   IF vDialog.Control.CSS_Class = ""
         if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) == 0 )
         { 
            //:   szClass = ""
            ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
            //:ELSE
         } 
         else
         { 
            //:   szClass = " class=^" + vDialog.Control.CSS_Class + "^"
            GetVariableFromAttribute( szTempString_8, 0, 'S', 1026, vDialog, "Control", "CSS_Class", "", 0 );
            ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
            ZeidonStringConcat( szClass, 1, 0, szTempString_8, 1, 0, 257 );
            ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
         } 

         //:   END

         //:   szHTML5Attr = ""
         ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
         //:   IF vDialog.Control.WebHTML5Attribute != ""
         if ( CompareAttributeToString( vDialog, "Control", "WebHTML5Attribute", "" ) != 0 )
         { 
            //:   szHTML5Attr = " " + vDialog.Control.WebHTML5Attribute + " "
            GetVariableFromAttribute( szTempString_9, 0, 'S', 1026, vDialog, "Control", "WebHTML5Attribute", "", 0 );
            ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
            ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_9, 1, 0, 257 );
            ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
         } 

         //:   END

         //:   //If we put a title on the control, when the mouse is hovered over the control, this text will display.
         //:   szTitleHTML = ""
         ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
         //:   szTitle = vDialog.Control.DIL_Text
         GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
         //:   IF szTitle != ""
         if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
         { 
            //:   szTitleHTML = " title=^" + szTitle + "^ "
            ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
            ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
            ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
         } 

         //:   END
         //:               
         //:   IF vDialog.EventAct EXISTS
         lTempInteger_9 = CheckExistenceOfEntity( vDialog, "EventAct" );
         if ( lTempInteger_9 == 0 )
         { 
            //:   IF vDialog.EventAct.Type = 45    // Type 45 is Hyperlink Action.
            if ( CompareAttributeToInteger( vDialog, "EventAct", "Type", 45 ) == 0 )
            { 
               //:   // For a Hyperlink in a Grid, we assume there is ALWAYS both "Displayed Text" mapping and
               //:   // "Hyperlink URL" mapping, which have been set above.
               //:   // THIS DOESN"T WORK AT THE MOMENT
               //:   szWriteBuffer = "   <li id=^" + szCtrlTag + "^ name=^" + szCtrlTag + "^" + szHTML5Attr + szClass + "><a href=^<%=str" + szCtrlTag + "_URL%>^ " + szTitleHTML + " target=^_blank^><%=strComboCurrentValue%></a></li>"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   <li id=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "><a href=^<%=str", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "_URL%>^ ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " target=^_blank^><%=strComboCurrentValue%></a></li>", 1, 0, 10001 );
               //:ELSE
            } 
            else
            { 
               //:   //szWriteBuffer = "   <li id=^" + szCtrlTag + "^ name=^" + szCtrlTag + "^" + szHTML5Attr + szClass + "><a href=^#^ onclick=^" + vDialog.EventAct.Tag + "( this.id )^ id=^" + szCtrlTag + "::<%=strEntityKey%>^" + szTitleHTML + "><%=strComb
               //:   // Put the class html5 on <a ref. I know we want this for window style jmobile but not sure we want this all the time? Then we would do above line?
               //:   szWriteBuffer = "   <li id=^" + szCtrlTag + "^ name=^" + szCtrlTag + "^><a href=^#^" + szHTML5Attr + szClass + " onclick=^" + vDialog.EventAct.Tag + "( this.id )^ id=^" + szCtrlTag + "::<%=strEntityKey%>^"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "   <li id=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^><a href=^#^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_10, 0, 'S', 1026, vDialog, "EventAct", "Tag", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "( this.id )^ id=^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "::<%=strEntityKey%>^", 1, 0, 10001 );
               //:   szWriteBuffer = szWriteBuffer + szTitleHTML + "><%=strComboCurrentValue%></a></li>" //  + szTitleHTML + "><%=strComboCurrentValue%></a></li>"
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "><%=strComboCurrentValue%></a></li>", 1, 0, 10001 );
            } 

            //:   END
            //:ELSE
         } 
         else
         { 
            //:   // Regular default Grid subcontrol.
            //:   //szWriteBuffer = "   <li>><%=str" + szCtrlTag + "%></td>"
            //:   szWriteBuffer = "   <li><%=strComboCurrentValue%></li>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   <li><%=strComboCurrentValue%></li>", 1, 0, 10001 );
         } 

         //:   END
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

         //:   szWriteBuffer = "<%"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:/**********************************************/         
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
      //:      szWriteBuffer = "         csrRC =  v" + szCtrlTag +
      //:                      ".cursor( ^" + szListEntityName +
      //:                      "^ ).setNextContinue( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         csrRC =  v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setNextContinue( );", 1, 0, 10001 );
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
   //:   szWriteBuffer = "      v" + szCtrlTag + ".drop( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".drop( );", 1, 0, 10001 );
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

   //:szWriteBuffer = "</ul>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</ul>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return( 0 );
// END
} 


//:GLOBAL OPERATION
//:BuildMenuListJ( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                INTEGER lFile,
//:                STRING (50) szMenuName )

//:   STRING ( 10000 ) szWriteBuffer
zOPER_EXPORT zSHORT OPERATION
BuildMenuListJ( zVIEW     vDialog,
                zVIEW     vDialogRoot,
                zLONG     lFile,
                zPCHAR    szMenuName )
{
   zCHAR     szWriteBuffer[ 10001 ] = { 0 }; 
   //:STRING ( 500 )   szNavigationTitle
   zCHAR     szNavigationTitle[ 501 ] = { 0 }; 
   //:STRING ( 500 )   szText
   zCHAR     szText[ 501 ] = { 0 }; 
   //:STRING ( 5 )     szSrch
   zCHAR     szSrch[ 6 ] = { 0 }; 
   //:STRING ( 50 )    szHTML_Name
   zCHAR     szHTML_Name[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szDialogName
   zCHAR     szDialogName[ 51 ] = { 0 }; 
   //:STRING ( 50 )    szOptionTag
   zCHAR     szOptionTag[ 51 ] = { 0 }; 
   //://STRING ( 50 )    szMenuName
   //:STRING ( 34 )    szActionName
   zCHAR     szActionName[ 35 ] = { 0 }; 
   //:STRING ( 256 )   szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 )   szClass2
   zCHAR     szClass2[ 257 ] = { 0 }; 
   //:STRING ( 256 )   szHTML5Attr
   zCHAR     szHTML5Attr[ 257 ] = { 0 }; 
   //:INTEGER          ActionType
   zLONG     ActionType = 0; 
   //:SHORT            nRC
   zSHORT    nRC = 0; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_0[ 255 ]; 
   zCHAR     szTempString_1[ 255 ]; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_2[ 255 ]; 
   zCHAR     szTempString_3[ 255 ]; 


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

   //:IF vDialogRoot.WndStyle.Tag = "jMobile Window"
   if ( CompareAttributeToString( vDialogRoot, "WndStyle", "Tag", "jMobile Window" ) == 0 )
   { 
      //:szWriteBuffer = "<div data-role=^listview^ id=^div" + szMenuName + "^" + szClass + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div data-role=^listview^ id=^div", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "<div id=^div" + szMenuName + "^" + szClass + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^div", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   } 

   //:END      
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );

   //://szWriteBuffer = "   <ul id=^" + szMenuName + "^ name=^" + szMenuName + "^" + szClass + ">"
   //:szWriteBuffer = "   <ul id=^" + szMenuName + "^ name=^" + szMenuName + "^" + szHTML5Attr + ">"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   <ul id=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );

   //:FOR EACH vDialogRoot.OptAct WITHIN vDialogRoot.Menu
   RESULT = SetCursorFirstEntity( vDialogRoot, "OptAct", "Menu" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //://szNavigationTitle = vDialogRoot.Option.Text
      //:// KJS 09/30/16 - Language Conversion.
      //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
      //:// So for now, I am always using, if the flag is set.
      //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
      { 
         //:szText = vDialogRoot.Option.Text
         GetVariableFromAttribute( szText, 0, 'S', 501, vDialogRoot, "Option", "Text", "", 0 );
         //:zSearchAndReplace( szText, 500, "\", "\\" )
         zSearchAndReplace( szText, 500, "\\", "\\\\" );
         //:szSrch = "\" + QUOTES 
         ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
         ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
         //:zSearchAndReplace( szText, 500, QUOTES, szSrch )
         zSearchAndReplace( szText, 500, QUOTES, szSrch );
         //:szNavigationTitle = "<%=LangConv.getLanguageText(^" + szText + "^)%>" 
         ZeidonStringCopy( szNavigationTitle, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
         ZeidonStringConcat( szNavigationTitle, 1, 0, szText, 1, 0, 501 );
         ZeidonStringConcat( szNavigationTitle, 1, 0, "^)%>", 1, 0, 501 );
         //:ELSE
      } 
      else
      { 
         //:szNavigationTitle = vDialogRoot.Option.Text
         GetVariableFromAttribute( szNavigationTitle, 0, 'S', 501, vDialogRoot, "Option", "Text", "", 0 );
      } 

      //:END
      //:szDialogName = vDialogRoot.OptAct.DialogName
      GetVariableFromAttribute( szDialogName, 0, 'S', 51, vDialogRoot, "OptAct", "DialogName", "", 0 );
      //:IF szDialogName = ""
      if ( ZeidonStringCompare( szDialogName, 1, 0, "", 1, 0, 51 ) == 0 )
      { 
         //:szDialogName = "NoDialogName"
         ZeidonStringCopy( szDialogName, 1, 0, "NoDialogName", 1, 0, 51 );
      } 

      //:END

      //://IF szReusableMenu = "Y"
      //://   szMenuName = "sm" + vDialogRoot.Option.Tag
      //://ELSE
      //:   szMenuName = vDialogRoot.Option.Tag
      GetVariableFromAttribute( szMenuName, 0, 'S', 51, vDialogRoot, "Option", "Tag", "", 0 );
      //://END

      //:// szHTML_Name = szDialogName + vDialogRoot.OptAct.WindowName + ".jsp"
      //:IF vDialogRoot.OptAct EXISTS
      lTempInteger_1 = CheckExistenceOfEntity( vDialogRoot, "OptAct" );
      if ( lTempInteger_1 == 0 )
      { 

         //:szActionName = vDialogRoot.OptAct.Tag
         GetVariableFromAttribute( szActionName, 0, 'S', 35, vDialogRoot, "OptAct", "Tag", "", 0 );
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
      //://IF vDialogRoot.OptAct.WindowName = vDialog.Window.Tag
      //://   szClass2 = " class=^sideselected^ "
      //://ELSE
      //:   szClass2 = ""
      ZeidonStringCopy( szClass2, 1, 0, "", 1, 0, 257 );
      //://END

      //:IF vDialogRoot.Option.CSS_Class != "" 
      if ( CompareAttributeToString( vDialogRoot, "Option", "CSS_Class", "" ) != 0 )
      { 
         //:szClass = " class=^" + vDialogRoot.Option.CSS_Class + "^"
         GetVariableFromAttribute( szTempString_2, 0, 'S', 255, vDialogRoot, "Option", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_2, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:szClass = ""
         ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
      } 

      //:END

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

      //:szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:szOptionTag = vDialogRoot.Option.Tag
      GetVariableFromAttribute( szOptionTag, 0, 'S', 51, vDialogRoot, "Option", "Tag", "", 0 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   csrRC = vKZXMLPGO.cursor( ^DisableMenuOption^ ).setFirst( ^MenuOptionName^, ^" + szOptionTag + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   csrRC = vKZXMLPGO.cursor( ^DisableMenuOption^ ).setFirst( ^MenuOptionName^, ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szOptionTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( !csrRC.isSet() ) //if ( nRC < 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( !csrRC.isSet() ) //if ( nRC < 0 )", 1, 0, 10001 );
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

      //://szWriteBuffer = "       <li><a href=^#^ " + szClass + " onclick=^" + szActionName + "( )^>" + szNavigationTitle + "</a></li>"
      //:// In the case of jmobile, I am putting the HTML5 and class on the <a href
      //:IF vDialogRoot.WndStyle.Tag = "jMobile Window"
      if ( CompareAttributeToString( vDialogRoot, "WndStyle", "Tag", "jMobile Window" ) == 0 )
      { 
         //:szWriteBuffer = "       <li id=^" + szMenuName + "^ name=^" + szMenuName + "^><a href=^#^ " + szHTML5Attr + szClass + szClass2 + " onclick=^" + szActionName + "()^>" + szNavigationTitle + "</a></li>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "       <li id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^><a href=^#^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass2, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "()^>", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szNavigationTitle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</a></li>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "       <li id=^" + szMenuName + "^ name=^" + szMenuName + "^" + szHTML5Attr + szClass + "><a href=^#^ " + szClass2 + " onclick=^" + szActionName + "()^>" + szNavigationTitle + "</a></li>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "       <li id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szMenuName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "><a href=^#^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass2, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "()^>", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szNavigationTitle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</a></li>", 1, 0, 10001 );
      } 

      //:END
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

   //:END

   //:// Division ending for Navigation Bar.
   //:szWriteBuffer = "   </ul>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   </ul>", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "</div> <!-- menu list end -->"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "</div> <!-- menu list end -->", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 1 );
   //:szWriteBuffer = ""
   ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
   //:WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialogRoot, lFile, szWriteBuffer, "^", 0 );
   return( 0 );
// END
} 


//:GLOBAL OPERATION
//:GenJSPJ_CrtePushButton( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                        VIEW vGroupParent BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 20 )    szJustify,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY,
//:                     STRING ( 100 )   szRepeatGrpKey )

//:   // Format an PushButton control.

//:   VIEW vDialogRoot BASED ON LOD TZWDLGSO
zOPER_EXPORT zSHORT OPERATION
GenJSPJ_CrtePushButton( zVIEW     vDialog,
                        zVIEW     vGroupParent,
                        zLONG     lFile,
                        zPCHAR    szWriteBuffer,
                        zPCHAR    szIndent,
                        zPCHAR    szCtrlTag,
                        zPCHAR    szTableRowFlag,
                        zPCHAR    szJustify,
                        zPCHAR    szNoPositioning,
                        zLONG     lOffsetX,
                        zLONG     lOffsetY,
                        zPCHAR    szRepeatGrpKey )
{
   zVIEW     vDialogRoot = 0; 
   //:STRING ( 32 )  szContextName
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 300 ) szValue
   zCHAR     szValue[ 301 ] = { 0 }; 
   //:STRING ( 600 ) szBlob
   zCHAR     szBlob[ 601 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szHTML5Attr
   zCHAR     szHTML5Attr[ 257 ] = { 0 }; 
   //:STRING ( 300 ) szType
   zCHAR     szType[ 301 ] = { 0 }; 
   //:STRING ( 500 ) szText
   zCHAR     szText[ 501 ] = { 0 }; 
   //:STRING ( 500 ) szText2
   zCHAR     szText2[ 501 ] = { 0 }; 
   //:STRING ( 5 )   szSrch
   zCHAR     szSrch[ 6 ] = { 0 }; 
   //:STRING ( 50 )  szParentWebType
   zCHAR     szParentWebType[ 51 ] = { 0 }; 
   //:STRING ( 256 ) szTerm
   zCHAR     szTerm[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szAction
   zCHAR     szAction[ 257 ] = { 0 }; 
   //:STRING ( 600 ) szWidget
   zCHAR     szWidget[ 601 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 600 ) szEditActionCode
   zCHAR     szEditActionCode[ 601 ] = { 0 }; 
   //:STRING ( 32 )  szActionName
   zCHAR     szActionName[ 33 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLength
   zCHAR     szMaxStringLength[ 11 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:STRING ( 1 )   szWCP_Hidden
   zCHAR     szWCP_Hidden[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szCreateSessionVariable
   zCHAR     szCreateSessionVariable[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szBrowseFile
   zCHAR     szBrowseFile[ 2 ] = { 0 }; 
   //:INTEGER        lMaxStringLength
   zLONG     lMaxStringLength = 0; 
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
   zSHORT    lTempInteger_0; 
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
   zCHAR     szTempString_12[ 255 ]; 
   zCHAR     szTempString_13[ 255 ]; 
   zCHAR     szTempString_14[ 255 ]; 


   //:TraceLineS("*** GenJSPJ_CrtePushButton *** ", "")
   TraceLineS( "*** GenJSPJ_CrtePushButton *** ", "" );

   //:GetViewByName( vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK )
   GetViewByName( &vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK );

   //:IF  szNoPositioning = "Y"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:CreateNoPosStyleString( vDialog, szStyle, "" )
      CreateNoPosStyleString( vDialog, szStyle, "" );
      //:ELSE
   } 
   else
   { 
      //:IF szNoPositioning = "S" // No style information
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = "" 
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
         //:ELSE 
      } 
      else
      { 
         //:CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
         CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" );
      } 

      //:END
   } 

   //:END

   //:/********************************** REAL CODE **********************/
   //:         szActionName = ""
   ZeidonStringCopy( szActionName, 1, 0, "", 1, 0, 33 );
   //:         IF vDialog.EventAct EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( vDialog, "EventAct" );
   if ( lTempInteger_0 == 0 )
   { 
      //:         szActionName = vDialog.EventAct.Tag
      GetVariableFromAttribute( szActionName, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
      //:         nRC = zstrcmpi( szActionName, "alt-f4" )
      nRC = zstrcmpi( szActionName, "alt-f4" );
      //:         IF nRC = 0
      if ( nRC == 0 )
      { 
         //:         szActionName = "AltF4"
         ZeidonStringCopy( szActionName, 1, 0, "AltF4", 1, 0, 33 );
      } 

      //:         END
   } 

   //:         END

   //:         CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );
   //:         szStyle = szStyle + szTabIndex
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );
   //:         
   //:         // KJS 10/20/15 - If there is mapping for the button text, we need to use that.kkk
   //:/************************************** NEW CODE *********************************/
   //:SET CURSOR FIRST vDialog.CtrlMapLOD_Attribute WITHIN vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "CtrlMapLOD_Attribute", "Control" );
   //:IF RESULT >= zCURSOR_SET 
   if ( RESULT >= zCURSOR_SET )
   { 
      //:bMapping = 1
      bMapping = 1;
      //:szWriteBuffer = "<%"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name + " = " + "task.getViewByName( ^" +
      //:                vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         task.log( ).debug( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         task.log( ).debug( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
      //:szWriteBuffer = "         nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
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

      //:// Add try/catch
      //:szWriteBuffer = "            try"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            try", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:IF vDialog.CtrlMapER_Domain.MaxStringLth > 254
      if ( CompareAttributeToInteger( vDialog, "CtrlMapER_Domain", "MaxStringLth", 254 ) > 0 )
      { 
         //:lMaxStringLength = vDialog.CtrlMapER_Domain.MaxStringLth
         GetIntegerFromAttribute( &lMaxStringLength, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
         //:szMaxStringLength = lMaxStringLength
         ZeidonStringConvertFromNumber( szMaxStringLength, 1, 0, 10, lMaxStringLength, (ZDecimal) 0.0, "I" );
         //:ELSE
      } 
      else
      { 
         //:szMaxStringLength = "254"
         ZeidonStringCopy( szMaxStringLength, 1, 0, "254", 1, 0, 11 );
      } 

      //:END
      //:szWriteBuffer = "               strErrorMapValue = " +
      //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
      //:                szContextName + "^ );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:IF vDialog.Control.WebCtrlType = "escapeHTML"
      if ( CompareAttributeToString( vDialog, "Control", "WebCtrlType", "escapeHTML" ) == 0 )
      { 
         //:szWriteBuffer = "               task.log().debug( ^" + szCtrlTag + " prior to unescape: ^ + strErrorMapValue );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "               task.log().debug( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " prior to unescape: ^ + strErrorMapValue );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "               strErrorMapValue = StringEscapeUtils.unescapeHtml4( strErrorMapValue );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = StringEscapeUtils.unescapeHtml4( strErrorMapValue );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "               task.log().debug( ^" + szCtrlTag + " after unescape: ^ + strErrorMapValue );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "               task.log().debug( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " after unescape: ^ + strErrorMapValue );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      } 

      //:END

      //:szWriteBuffer = "            }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            catch (Exception e)"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            catch (Exception e)", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "               out.println(^There is an error on " + szCtrlTag + ": ^ + e.getMessage());"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               out.println(^There is an error on ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + e.getMessage());", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "               task.log().error( ^*** Error on ctrl " + szCtrlTag + "^, e );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               task.log().error( ^*** Error on ctrl ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, e );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:/***************** END OF try/catch **********************/

      //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
      //:szWriteBuffer = "            if ( strErrorMapValue == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( strErrorMapValue == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "               strErrorMapValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:szWriteBuffer = "            task.log( ).debug( ^" + vDialog.CtrlMapRelatedEntity.Name + "." +
      //:                vDialog.CtrlMapER_Attribute.Name + ": ^ + strErrorMapValue );"
      GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).debug( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + strErrorMapValue );", 1, 0, 10001 );
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
      //:szWriteBuffer = "            task.log( ).debug( ^Entity does not exist for " + szCtrlTag + ": ^ + ^" +
      //:                vDialog.CtrlMapView.Name +
      //:                "." + vDialog.CtrlMapRelatedEntity.Name + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).debug( ^Entity does not exist for ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );

      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:   szWriteBuffer = "      if ( strErrorMapValue == ^^ )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strErrorMapValue == ^^ )", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "         strErrorMapValue = ^" + vDialog.Control.Text + "^;"
      GetVariableFromAttribute( szTempString_12, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //://szText = "<%=strErrorMapValue%>"

      //:// KJS 09/30/16 - Language Conversion.
      //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
      //:// So for now, I am always using, if the flag is set.
      //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
      { 
         //:szText = "<%=LangConv.getLanguageText(strErrorMapValue)%>" 
         ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(strErrorMapValue)%>", 1, 0, 501 );
         //:ELSE
      } 
      else
      { 
         //:szText = "<%=strErrorMapValue%>"
         ZeidonStringCopy( szText, 1, 0, "<%=strErrorMapValue%>", 1, 0, 501 );
      } 

      //:END
      //:ELSE
   } 
   else
   { 
      //://szText = vDialog.Control.Text
      //:// KJS 09/30/16 - Language Conversion.
      //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
      //:// So for now, I am always using, if the flag is set.
      //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
      { 
         //:szText2 = vDialog.Control.Text
         GetVariableFromAttribute( szText2, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
         //:zSearchAndReplace( szText2, 1000, "\", "\\" )
         zSearchAndReplace( szText2, 1000, "\\", "\\\\" );
         //:szSrch = "\" + QUOTES 
         ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
         ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
         //:zSearchAndReplace( szText2, 1000, QUOTES, szSrch )
         zSearchAndReplace( szText2, 1000, QUOTES, szSrch );
         //:szSrch = ""
         ZeidonStringCopy( szSrch, 1, 0, "", 1, 0, 6 );
         //:szText = "<%=LangConv.getLanguageText(^" + szText2 + "^)%>" 
         ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
         ZeidonStringConcat( szText, 1, 0, szText2, 1, 0, 501 );
         ZeidonStringConcat( szText, 1, 0, "^)%>", 1, 0, 501 );
         //:ELSE
      } 
      else
      { 
         //:szText = vDialog.Control.Text
         GetVariableFromAttribute( szText, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
      } 

      //:END
   } 


   //:END


   //:/************************************** END OF NEW CODE *********************************/

   //:         //szText = vDialog.Control.Text
   //:         // Set Class as either null or with Class value.
   //:         IF vDialog.Control.CSS_Class = ""
   if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) == 0 )
   { 
      //:         szClass = ""
      ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
      //:      ELSE
   } 
   else
   { 
      //:         szClass = "class=^" + vDialog.Control.CSS_Class + "^ "
      GetVariableFromAttribute( szTempString_13, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClass, 1, 0, "class=^", 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, szTempString_13, 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:         END

   //:         //If we put a title on the control, when the mouse is hovered over the control, this text will display.
   //:         szTitleHTML = ""
   ZeidonStringCopy( szTitleHTML, 1, 0, "", 1, 0, 257 );
   //:         szTitle = vDialog.Control.DIL_Text
   GetVariableFromAttribute( szTitle, 0, 'S', 257, vDialog, "Control", "DIL_Text", "", 0 );
   //:         IF szTitle != ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) != 0 )
   { 
      //:         szTitleHTML = " title=^" + szTitle + "^ "
      ZeidonStringCopy( szTitleHTML, 1, 0, " title=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:         END

   //:         szHTML5Attr = ""
   ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
   //:         IF vDialog.Control.WebHTML5Attribute != ""
   if ( CompareAttributeToString( vDialog, "Control", "WebHTML5Attribute", "" ) != 0 )
   { 
      //:         szHTML5Attr = " " + vDialog.Control.WebHTML5Attribute + " "
      GetVariableFromAttribute( szTempString_14, 0, 'S', 255, vDialog, "Control", "WebHTML5Attribute", "", 0 );
      ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_14, 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
   } 

   //:         END

   //:         szWidget = "<button type=^button^ " + szClass + szTitleHTML + szHTML5Attr + "name=^"
   ZeidonStringCopy( szWidget, 1, 0, "<button type=^button^ ", 1, 0, 601 );
   ZeidonStringConcat( szWidget, 1, 0, szClass, 1, 0, 601 );
   ZeidonStringConcat( szWidget, 1, 0, szTitleHTML, 1, 0, 601 );
   ZeidonStringConcat( szWidget, 1, 0, szHTML5Attr, 1, 0, 601 );
   ZeidonStringConcat( szWidget, 1, 0, "name=^", 1, 0, 601 );
   //:         szTerm = szText + "</button>"
   ZeidonStringCopy( szTerm, 1, 0, szText, 1, 0, 257 );
   ZeidonStringConcat( szTerm, 1, 0, "</button>", 1, 0, 257 );
   //:         szText = ""
   ZeidonStringCopy( szText, 1, 0, "", 1, 0, 501 );
   //:            
   //:         // Action is different if this is a repeating group.
   //:         IF szRepeatGrpKey = ""
   if ( ZeidonStringCompare( szRepeatGrpKey, 1, 0, "", 1, 0, 101 ) == 0 )
   { 
      //:         szAction = szActionName + "( )"
      ZeidonStringCopy( szAction, 1, 0, szActionName, 1, 0, 257 );
      ZeidonStringConcat( szAction, 1, 0, "( )", 1, 0, 257 );
      //:      ELSE
   } 
   else
   { 
      //:         szAction = szActionName + "( '" + szCtrlTag + szRepeatGrpKey + "' )"
      ZeidonStringCopy( szAction, 1, 0, szActionName, 1, 0, 257 );
      ZeidonStringConcat( szAction, 1, 0, "( '", 1, 0, 257 );
      ZeidonStringConcat( szAction, 1, 0, szCtrlTag, 1, 0, 257 );
      ZeidonStringConcat( szAction, 1, 0, szRepeatGrpKey, 1, 0, 257 );
      ZeidonStringConcat( szAction, 1, 0, "' )", 1, 0, 257 );
   } 

   //:         END

   //:         szParentWebType = ""
   ZeidonStringCopy( szParentWebType, 1, 0, "", 1, 0, 51 );
   //:         // KJS 01/30/14 - I'm thinking "Relative Positioning" is old. I only use this in one pwd and when I take it
   //:         // out and use "Div/No Height", the results look exactly the same so I am going to take this off grid controls.
   //:         IF vGroupParent != 0
   if ( vGroupParent != 0 )
   { 
      //:         //*
      //:         SET CURSOR FIRST vGroupParent.WebControlProperty WHERE vGroupParent.WebControlProperty.Name = "Relative Positioning"
      RESULT = SetCursorFirstEntityByString( vGroupParent, "WebControlProperty", "Name", "Relative Positioning", "" );
      //:         IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:         szParentWebType = "RelativePos"
         ZeidonStringCopy( szParentWebType, 1, 0, "RelativePos", 1, 0, 51 );
         //:      ELSE
      } 
      else
      { 
         //:         szParentWebType = vGroupParent.Control.WebCtrlType
         GetVariableFromAttribute( szParentWebType, 0, 'S', 51, vGroupParent, "Control", "WebCtrlType", "", 0 );
      } 

      //:         END
   } 

   //:            //*/
   //:            //szParentWebType = vGroupParent.Control.WebCtrlType
   //:         END
   //:         
   //:         IF szParentWebType = "Div" OR szParentWebType = "DivScroll" OR
   //:            szParentWebType = "Span"
   if ( ZeidonStringCompare( szParentWebType, 1, 0, "Div", 1, 0, 51 ) == 0 || ZeidonStringCompare( szParentWebType, 1, 0, "DivScroll", 1, 0, 51 ) == 0 || ZeidonStringCompare( szParentWebType, 1, 0, "Span", 1, 0, 51 ) == 0 )
   { 

      //:         szWriteBuffer = "<p></p>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<p></p>", 1, 0, 10001 );
      //:         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:         CreateSizeString( vDialog, szSize )
      CreateSizeString( vDialog, szSize );
      //:         szWriteBuffer = szWidget + szCtrlTag + "^ id=^" + szCtrlTag + "^ value=^" + szText + "^ onclick=^" +
      //:                         szAction + "^ " + "style=^" + szSize + "^>" + szTerm
      ZeidonStringCopy( szWriteBuffer, 1, 0, szWidget, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ value=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ onclick=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szAction, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "style=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szSize, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^>", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTerm, 1, 0, 10001 );
      //:      ELSE
   } 
   else
   { 
      //:         szWriteBuffer = szWidget + szCtrlTag + "^ id=^" + szCtrlTag + "^ value=^" + szText + "^ onclick=^" +
      //:                         szAction + "^ " + szStyle + ">" + szTerm
      ZeidonStringCopy( szWriteBuffer, 1, 0, szWidget, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ value=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ onclick=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szAction, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTerm, 1, 0, 10001 );
   } 

   //:         END
   //:         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return( 0 );
//    /************************ END OF REAL CODE ********************************************/
// END
} 


//:GLOBAL OPERATION
//:GenJSPJ_CrteMLEdit( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 20 )    szJustify,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY,
//:                     STRING ( 100 )   szRepeatGrpKey )

//:   VIEW vLPLR    BASED ON LOD TZCMLPLO
zOPER_EXPORT zSHORT OPERATION
GenJSPJ_CrteMLEdit( zVIEW     vDialog,
                    zLONG     lFile,
                    zPCHAR    szWriteBuffer,
                    zPCHAR    szIndent,
                    zPCHAR    szCtrlTag,
                    zPCHAR    szTableRowFlag,
                    zPCHAR    szJustify,
                    zPCHAR    szNoPositioning,
                    zLONG     lOffsetX,
                    zLONG     lOffsetY,
                    zPCHAR    szRepeatGrpKey )
{
   zVIEW     vLPLR = 0; 
   //:STRING ( 32 )  szLPLR_Name
   zCHAR     szLPLR_Name[ 33 ] = { 0 }; 
   //:STRING ( 32 )  szContextName
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 50 )  szControlType
   zCHAR     szControlType[ 51 ] = { 0 }; 
   //:STRING ( 50 )  szWidth
   zCHAR     szWidth[ 51 ] = { 0 }; 
   //:STRING ( 50 )  szHeight
   zCHAR     szHeight[ 51 ] = { 0 }; 
   //:STRING ( 256 ) szAbsoluteStyle
   zCHAR     szAbsoluteStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 50 )  szTabIndex
   zCHAR     szTabIndex[ 51 ] = { 0 }; 
   //:STRING ( 50 )  szActionName
   zCHAR     szActionName[ 51 ] = { 0 }; 
   //:STRING ( 500 ) szActionCode
   zCHAR     szActionCode[ 501 ] = { 0 }; 
   //:STRING ( 256 ) szText
   zCHAR     szText[ 257 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLength
   zCHAR     szMaxStringLength[ 11 ] = { 0 }; 
   //:STRING ( 1 )   szTinyMCEFlag
   zCHAR     szTinyMCEFlag[ 2 ] = { 0 }; 
   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   //:INTEGER        X_Size
   zLONG     X_Size = 0; 
   //:INTEGER        Y_Size
   zLONG     Y_Size = 0; 
   //:INTEGER        Size
   zLONG     Size = 0; 
   //:INTEGER        lMaxStringLength
   zLONG     lMaxStringLength = 0; 
   //:INTEGER        lStyleX
   zLONG     lStyleX = 0; 
   //:INTEGER        lTemp
   zLONG     lTemp = 0; 
   //:SHORT          nRC
   zSHORT    nRC = 0; 
   zSHORT    RESULT; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 
   zCHAR     szTempString_12[ 255 ]; 
   zSHORT    lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zCHAR     szTempString_13[ 255 ]; 


   //:TraceLineS("**** GenJSPJ_CrteMLEdit **** ", "")
   TraceLineS( "**** GenJSPJ_CrteMLEdit **** ", "" );

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
      //:szWriteBuffer = "   strErrorMapValue = VmlOperation.CheckError( ^" + szCtrlTag + "^, strError );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = VmlOperation.CheckError( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, strError );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( !StringUtils.isBlank( strErrorMapValue ) )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( !StringUtils.isBlank( strErrorMapValue ) )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( StringUtils.equals( strErrorFlag, ^Y^ ) )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( StringUtils.equals( strErrorFlag, ^Y^ ) )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         strErrorColor = ^color:red;^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorColor = ^color:red;^;", 1, 0, 10001 );
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
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name + " = " + "task.getViewByName( ^" +
      //:                vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         task.log( ).info( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         task.log( ).info( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
      //:szWriteBuffer = "         nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
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

      //:IF vDialog.CtrlMapER_Domain.MaxStringLth > 254
      if ( CompareAttributeToInteger( vDialog, "CtrlMapER_Domain", "MaxStringLth", 254 ) > 0 )
      { 
         //:lMaxStringLength = vDialog.CtrlMapER_Domain.MaxStringLth
         GetIntegerFromAttribute( &lMaxStringLength, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
         //:szMaxStringLength = lMaxStringLength
         ZeidonStringConvertFromNumber( szMaxStringLength, 1, 0, 10, lMaxStringLength, (ZDecimal) 0.0, "I" );
         //:ELSE
      } 
      else
      { 
         //:szMaxStringLength = "254"
         ZeidonStringCopy( szMaxStringLength, 1, 0, "254", 1, 0, 11 );
      } 

      //:END

      //:szWriteBuffer = "            strErrorMapValue = " +
      //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
      //:                szContextName + "^ );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            strErrorMapValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
      //:szWriteBuffer = "            if ( strErrorMapValue == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( strErrorMapValue == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "               strErrorMapValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:szWriteBuffer = "            task.log( ).info( ^" + vDialog.CtrlMapRelatedEntity.Name + "." +
      //:                vDialog.CtrlMapER_Attribute.Name + ": ^ + strErrorMapValue );"
      GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).info( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + strErrorMapValue );", 1, 0, 10001 );
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
      //:szWriteBuffer = "            task.log( ).info( ^Entity does not exist for " + szCtrlTag + ": ^ + ^" +
      //:                vDialog.CtrlMapView.Name +
      //:                "." + vDialog.CtrlMapRelatedEntity.Name + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).info( ^Entity does not exist for ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
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
         GetVariableFromAttribute( szTempString_12, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
      } 

      //:END

      //:// This doesn't work, but something like it may be necessary to remove special characters ... dks 2012.04.25
      //:// strErrorMapValue = strErrorMapValue.replace("/&/g", "&amp;").replace("/>/g", "&gt;").replace("/</g", "&lt;").replace("/\"/g", "&quot;").replace("/%/g", "&#037;");

      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "%>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   } 


   //:END // SET CURSOR FIRST vDialog.CtrlMapLOD_Attribute WITHIN vDialog.Control

   //:// *********************  NEW ******************

   //:// If there is an Event for the MLEdit, build code to insert in <textarea statement.
   //:szActionCode = ""
   ZeidonStringCopy( szActionCode, 1, 0, "", 1, 0, 501 );
   //:FOR EACH vDialog.Event
   RESULT = SetCursorFirstEntity( vDialog, "Event", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:IF vDialog.EventAct EXISTS
      lTempInteger_1 = CheckExistenceOfEntity( vDialog, "EventAct" );
      if ( lTempInteger_1 == 0 )
      { 
         //:szActionName = vDialog.EventAct.Tag
         GetVariableFromAttribute( szActionName, 0, 'S', 51, vDialog, "EventAct", "Tag", "", 0 );
         //:IF vDialog.Event.Type = 32
         if ( CompareAttributeToInteger( vDialog, "Event", "Type", 32 ) == 0 )
         { 
            //:szActionCode = szActionCode + " onfocus=^" + szActionName + "( )^ "
            ZeidonStringConcat( szActionCode, 1, 0, " onfocus=^", 1, 0, 501 );
            ZeidonStringConcat( szActionCode, 1, 0, szActionName, 1, 0, 501 );
            ZeidonStringConcat( szActionCode, 1, 0, "( )^ ", 1, 0, 501 );
            //:ELSE
         } 
         else
         { 
            //:IF vDialog.Event.Type = 64
            if ( CompareAttributeToInteger( vDialog, "Event", "Type", 64 ) == 0 )
            { 
               //:szActionCode = szActionCode + " onblur=^" + szActionName + "( )^ "
               ZeidonStringConcat( szActionCode, 1, 0, " onblur=^", 1, 0, 501 );
               ZeidonStringConcat( szActionCode, 1, 0, szActionName, 1, 0, 501 );
               ZeidonStringConcat( szActionCode, 1, 0, "( )^ ", 1, 0, 501 );
               //:ELSE
            } 
            else
            { 
               //:IF vDialog.Event.Type = 1024
               if ( CompareAttributeToInteger( vDialog, "Event", "Type", 1024 ) == 0 )
               { 
                  //:szActionCode = szActionCode + " onchange=^" + szActionName + "( )^ "
                  ZeidonStringConcat( szActionCode, 1, 0, " onchange=^", 1, 0, 501 );
                  ZeidonStringConcat( szActionCode, 1, 0, szActionName, 1, 0, 501 );
                  ZeidonStringConcat( szActionCode, 1, 0, "( )^ ", 1, 0, 501 );
                  //:ELSE
               } 
               else
               { 
                  //:IF vDialog.Event.Type = 1
                  if ( CompareAttributeToInteger( vDialog, "Event", "Type", 1 ) == 0 )
                  { 
                     //:szActionCode = szActionCode + " onkeydown=^" + szActionName + "( )^ "
                     ZeidonStringConcat( szActionCode, 1, 0, " onkeydown=^", 1, 0, 501 );
                     ZeidonStringConcat( szActionCode, 1, 0, szActionName, 1, 0, 501 );
                     ZeidonStringConcat( szActionCode, 1, 0, "( )^ ", 1, 0, 501 );
                  } 

                  //:END
               } 

               //:END
            } 

            //:END
         } 

         //:END
      } 

      RESULT = SetCursorNextEntity( vDialog, "Event", "" );
      //:END
   } 

   //:END

   //:// *********************  END NEW ******************

   //:CreateAbsolStyleString( vDialog, szAbsoluteStyle, lOffsetX, lOffsetY, "" )
   CreateAbsolStyleString( vDialog, szAbsoluteStyle, lOffsetX, lOffsetY, "" );

   //:// KJS - 08/23/16 - this was the old code... but trying Doug's
   //:/*
   //:X_Size = vDialog.Control.SZDLG_X
   //:Size = X_Size / 4
   //:zIntegerToString( szWidth, 10, Size )
   //:Y_Size = vDialog.Control.SZDLG_Y
   //:Size = Y_Size / 12
   //:zIntegerToString( szHeight, 10, Size )
   //:*/
   //:PIX_PER_DU( vDialog, dDLUnits )
   PIX_PER_DU( vDialog, &dDLUnits );
   //:zIntegerToString( szWidth, 10, vDialog.Control.SZDLG_X * dDLUnits )
   GetIntegerFromAttribute( &lTempInteger_2, vDialog, "Control", "SZDLG_X" );
   zIntegerToString( szWidth, 10, lTempInteger_2 * dDLUnits );
   //:zIntegerToString( szHeight, 10, vDialog.Control.SZDLG_Y * dDLUnits )
   GetIntegerFromAttribute( &lTempInteger_3, vDialog, "Control", "SZDLG_Y" );
   zIntegerToString( szHeight, 10, lTempInteger_3 * dDLUnits );

   //:IF vDialog.Control.VisibleBorder = "Y"
   if ( CompareAttributeToString( vDialog, "Control", "VisibleBorder", "Y" ) == 0 )
   { 
      //:zAppendQuotedString( szAbsoluteStyle, "border:solid;border-width:4px;border-style:groove;", "style=", "^" )
      zAppendQuotedString( szAbsoluteStyle, "border:solid;border-width:4px;border-style:groove;", "style=", "^" );
      //:ELSE
   } 
   else
   { 
      //:zAppendQuotedString( szAbsoluteStyle, "border:solid;border-width:2px;border-style:groove;", "style=", "^" )
      zAppendQuotedString( szAbsoluteStyle, "border:solid;border-width:2px;border-style:groove;", "style=", "^" );
   } 

   //:END

   //:IF szNoPositioning = "S"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
   { 
      //:szAbsoluteStyle = "" // No style information.    
      ZeidonStringCopy( szAbsoluteStyle, 1, 0, "", 1, 0, 257 );
   } 

   //:END

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
   //://szTitle = vDialog.Control.Placeholder
   //:IF szTitle = "" AND vDialog.Control.Placeholder != ""
   if ( ZeidonStringCompare( szTitle, 1, 0, "", 1, 0, 257 ) == 0 && CompareAttributeToString( vDialog, "Control", "Placeholder", "" ) != 0 )
   { 
      //:szTitleHTML = szTitleHTML + " placeholder=^" + szTitle + "^"
      ZeidonStringConcat( szTitleHTML, 1, 0, " placeholder=^", 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, szTitle, 1, 0, 257 );
      ZeidonStringConcat( szTitleHTML, 1, 0, "^", 1, 0, 257 );
   } 

   //:END

   //:IF vDialog.Control.WebCtrlType = "wysiwygEditor" OR szTinyMCEFlag = "Y"
   if ( CompareAttributeToString( vDialog, "Control", "WebCtrlType", "wysiwygEditor" ) == 0 || ZeidonStringCompare( szTinyMCEFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 

      //:// CreateTabIndexString( vDialog, szTabIndex )
      //:// CreateAbsolStyleString( vDialog, szAbsoluteStyle, lOffsetX, lOffsetY, "" )
      //:// szAbsoluteStyle = szAbsoluteStyle + szTabIndex


      //:szClass = vDialog.Control.CSS_Class
      GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
      //:IF szClass = ""
      if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
      { 
         //:GetViewByName( vLPLR, "TaskLPLR", vDialog, zLEVEL_TASK )
         GetViewByName( &vLPLR, "TaskLPLR", vDialog, zLEVEL_TASK );
         //:szText = vLPLR.LPLR.Name
         GetVariableFromAttribute( szText, 0, 'S', 257, vLPLR, "LPLR", "Name", "", 0 );
         //:szLPLR_Name = "[App." + szText + "]"
         ZeidonStringCopy( szLPLR_Name, 1, 0, "[App.", 1, 0, 33 );
         ZeidonStringConcat( szLPLR_Name, 1, 0, szText, 1, 0, 33 );
         ZeidonStringConcat( szLPLR_Name, 1, 0, "]", 1, 0, 33 );
         //:SysReadZeidonIni( -1, szLPLR_Name, "TinyMCEClass", szClass )
         SysReadZeidonIni( -1, szLPLR_Name, "TinyMCEClass", szClass, zsizeof( szClass ) );
         //:IF szClass = ""
         if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
         { 
            //:szClass = "mceSimple"  // "mceSimple" is TinyMCE default
            ZeidonStringCopy( szClass, 1, 0, "mceSimple", 1, 0, 257 );
         } 

         //:END
      } 

      //:END

      //:nRC = zSearchSubString( szClass, "mceSimpleZeidon", "f", 0 )
      nRC = zSearchSubString( szClass, "mceSimpleZeidon", "f", 0 );
      //:IF nRC >= 0
      if ( nRC >= 0 )
      { 
         //:szWriteBuffer = "<div style=^background-color:#eee;border:1px solid #042;width:" + szWidth + "px;height:" + szHeight + "px;position:absolute;left:0px;top:0px;overflow:auto;^>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<div style=^background-color:#eee;border:1px solid #042;width:", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "px;height:", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHeight, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "px;position:absolute;left:0px;top:0px;overflow:auto;^>", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "<div class=^" + szClass + "^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ style=^width:" + szWidth + "px;height:" + szHeight + "px;position:absolute;left:0px;top:0px;^><%=strErrorMapValue%></div></div>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<div class=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ style=^width:", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "px;height:", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHeight, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "px;position:absolute;left:0px;top:0px;^><%=strErrorMapValue%></div></div>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "<textarea name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey +
         //:                "^ class=^" + szClass + "^ " + szTitleHTML + szAbsoluteStyle + szActionCode + ">" +
         //:             // "^ rows="15" cols="80" style="width: 80%">" +
         //:                "<%=strErrorMapValue%></textarea>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<textarea name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ class=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionCode, 1, 0, 10001 );
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
      //:IF vDialog.Control.CSS_Class != ""
      if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) != 0 )
      { 
         //:// szClass = vDialog.Control.CSS_Class
         //:szClass = " class=^" + vDialog.Control.CSS_Class + "^"
         GetVariableFromAttribute( szTempString_13, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_13, 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
      } 

      //:END
      //:CreateTabIndexString( vDialog, szTabIndex )
      CreateTabIndexString( vDialog, szTabIndex );

      //:lTemp = vDialog.Control.Subtype
      GetIntegerFromAttribute( &lTemp, vDialog, "Control", "Subtype" );
      //:lTemp = IsFlagSequenceSet( lTemp, zCONTROL_DISABLED )
      lTemp = IsFlagSequenceSet( lTemp, zCONTROL_DISABLED );
      //:IF lTemp = 0
      if ( lTemp == 0 )
      { 
         //:szWriteBuffer = "<textarea name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ " + szTitleHTML +
         //:                szAbsoluteStyle + szTabIndex + szClass + szActionCode + " wrap=^wrap^>" + "<%=strErrorMapValue%></textarea>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<textarea name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " wrap=^wrap^>", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "<%=strErrorMapValue%></textarea>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:zAppendQuotedString( szAbsoluteStyle, "text-overflow:hidden;background-color:lightgray;", "style=", "^" )
         zAppendQuotedString( szAbsoluteStyle, "text-overflow:hidden;background-color:lightgray;", "style=", "^" );
         //:szWriteBuffer = "<div name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ " + szTitleHTML +
         //:                szAbsoluteStyle + szTabIndex + szClass + szActionCode + " wrap=^wrap^>" + "<%=strErrorMapValue%></div>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<div name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szAbsoluteStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " wrap=^wrap^>", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "<%=strErrorMapValue%></div>", 1, 0, 10001 );
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
//:GenJSPJ_CrteListBox( VIEW vDialog,
//:                    INTEGER lFile,
//:                    STRING ( 10000 ) szWriteBuffer,
//:                    STRING ( 50 )    szIndent,
//:                    STRING ( 32 )    szCtrlTag,
//:                    STRING ( 1 )     szNoPositioning,
//:                    INTEGER lOffsetX,
//:                    INTEGER lOffsetY )

//:   VIEW vScope  BASED ON LOD TZWDLGSO  // identifies scoping entity for list entries
zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteListBox( zVIEW     vDialog,
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
   //:STRING ( 10 )  szMaxStringLength
   zCHAR     szMaxStringLength[ 11 ] = { 0 }; 
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
   //:INTEGER        lMaxStringLength
   zLONG     lMaxStringLength = 0; 
   zCHAR     szTempString_0[ 1026 ]; 
   zLONG     lTempInteger_0; 
   zLONG     lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_4; 
   zCHAR     szTempString_1[ 1026 ]; 
   zSHORT    lTempInteger_5; 
   zSHORT    lTempInteger_6; 
   zCHAR     szTempString_2[ 1026 ]; 
   zCHAR     szTempString_3[ 1026 ]; 
   zCHAR     szTempString_4[ 1026 ]; 
   zSHORT    lTempInteger_7; 
   zCHAR     szTempString_5[ 1026 ]; 
   zSHORT    lTempInteger_8; 
   zCHAR     szTempString_6[ 1026 ]; 
   zSHORT    lTempInteger_9; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 1026 ]; 


   //:szStyle = "width:" + szWidth + "px; height:" + szHeight + "px;"
   ZeidonStringCopy( szStyle, 1, 0, "width:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px; height:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
   //:IF vDialog.Control.CSS_Class = ""
   if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) == 0 )
   { 
      //:szClass = ""
      ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
      //:ELSE
   } 
   else
   { 
      //:szClass = "class=^" + vDialog.Control.CSS_Class + "^"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 1026, vDialog, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClass, 1, 0, "class=^", 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, szTempString_0, 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
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
   //:IF szNoPositioning = ""
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
      //://CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
      //:ELSE
   } 
   else
   { 
      //:IF szNoPositioning = "S"
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = "" 
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
      } 

      //:END
   } 

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
      GetVariableFromAttribute( szTempString_1, 0, 'S', 1026, vDialog, "EventAct", "Tag", "", 0 );
      ZeidonStringCopy( ListBoxDoubleClickAction, 1, 0, " ondblclick=^", 1, 0, 257 );
      ZeidonStringConcat( ListBoxDoubleClickAction, 1, 0, szTempString_1, 1, 0, 257 );
      ZeidonStringConcat( ListBoxDoubleClickAction, 1, 0, "( )^ ", 1, 0, 257 );
   } 

   //:   END


   //:   // Set cursor to the scoping entity if one exists
   //:   CreateViewFromViewForTask( vScope, vDialog, 0 )
   CreateViewFromViewForTask( &vScope, vDialog, 0 );
   //:   SET CURSOR NEXT vScope.CtrlMap
   RESULT = SetCursorNextEntity( vScope, "CtrlMap", "" );

   //:   szWriteBuffer = "<select " + szClass + " name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ size=^4^ " + szTitleHTML +
   //:                   szStyle + szDisabled + " onclick=^" + szCtrlTag + szSelectFunction + "( )^" + ListBoxDoubleClickAction + ">"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<select ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " name=^", 1, 0, 10001 );
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

      //:   szWriteBuffer = "   " + vDialog.CtrlMapView.Name + " = " +
      //:                   "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_3, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) )"
      GetVariableFromAttribute( szTempString_4, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) )", 1, 0, 10001 );
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
      //:   szWriteBuffer = "      View v" + szCtrlTag + ";"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      View v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ";", 1, 0, 10001 );
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

         //:   szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
         //:                   szEntityName + "^ ).checkExistenceOfEntity( ).toInt();"
         GetVariableFromAttribute( szTempString_5, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "      if ( nRC >= 0 )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "      {"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
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

         //:   IF vDialog.CtrlMapER_Domain.MaxStringLth > 254
         if ( CompareAttributeToInteger( vDialog, "CtrlMapER_Domain", "MaxStringLth", 254 ) > 0 )
         { 
            //:   lMaxStringLength = vDialog.CtrlMapER_Domain.MaxStringLth
            GetIntegerFromAttribute( &lMaxStringLength, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
            //:   szMaxStringLength = lMaxStringLength
            ZeidonStringConvertFromNumber( szMaxStringLength, 1, 0, 10, lMaxStringLength, (ZDecimal) 0.0, "I" );
            //:ELSE
         } 
         else
         { 
            //:   szMaxStringLength = "254"
            ZeidonStringCopy( szMaxStringLength, 1, 0, "254", 1, 0, 11 );
         } 

         //:   END


         //:   szWriteBuffer = "         strComboCurrentValue = " + vDialog.CtrlMapView.Name +
         //:            ".cursor( ^" +
         //:            szEntityName + "^ ).getAttribute( ^" +
         //:            szAttributeName + "^ ).getString( ^" + szContextName + "^ );"
         GetVariableFromAttribute( szTempString_6, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strComboCurrentValue = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szAttributeName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:   // KJS 02/15/11 - Thinking I need to add code to change values returned as null to ""
         //:   szWriteBuffer = "         if ( strComboCurrentValue == null )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strComboCurrentValue == null )", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "            strComboCurrentValue = ^^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            strComboCurrentValue = ^^;", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "      }"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
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
            //:   szScopingEntityName = "^" + vScope.CtrlMapLOD_Entity.Name + "^"
            GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vScope, "CtrlMapLOD_Entity", "Name", "", 0 );
            ZeidonStringCopy( szScopingEntityName, 1, 0, "^", 1, 0, 33 );
            ZeidonStringConcat( szScopingEntityName, 1, 0, szTempString_7, 1, 0, 33 );
            ZeidonStringConcat( szScopingEntityName, 1, 0, "^", 1, 0, 33 );
         } 

         //:   END
      } 

      //:   END

      //:   szWriteBuffer = "      v" + szCtrlTag + " = " + vDialog.CtrlMapView.Name + ".newView( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_8, 0, 'S', 1026, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".newView( );", 1, 0, 10001 );
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
         //:   szWriteBuffer = "      csrRC = v" + szCtrlTag + ".cursor( ^" +
         //:                                szListEntityName + "^ ).setFirst( " + szScopingEntityName + " );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      csrRC = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setFirst( ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szScopingEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:   szWriteBuffer = "      csrRC = v" + szCtrlTag + ".cursor( ^" + szListEntityName + "^ ).setFirstWithinOi( );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      csrRC = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setFirstWithinOi( );", 1, 0, 10001 );
      } 

      //:   END

      //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:   szWriteBuffer = "      while ( csrRC.isSet() )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      while ( csrRC.isSet() )", 1, 0, 10001 );
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
         //:                   ".cursor( ^" +
         //:                   szEntityName + "^ ).getAttribute( ^" +
         //:                   szAttributeName + "^ ).getString( ^" +
         //:                   szContextName + "^ );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szAttributeName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:   // KJS 02/15/11 - Thinking I need to add code to change values returned as null to ""
         //:   szWriteBuffer = "         if ( strErrorMapValue == null )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strErrorMapValue == null )", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:   szWriteBuffer = "            strErrorMapValue = ^^;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            strErrorMapValue = ^^;", 1, 0, 10001 );
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      } 


      //:   END

      //:   szWriteBuffer = "         if ( StringUtils.equals( strComboCurrentValue, strErrorMapValue ) )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( StringUtils.equals( strComboCurrentValue, strErrorMapValue ) )", 1, 0, 10001 );
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
      //:   szWriteBuffer = "            <option selected=^selected^><%=strErrorMapValue%></option>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option selected=^selected^><%=strErrorMapValue%></option>", 1, 0, 10001 );
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
      //:   szWriteBuffer = "            <option><%=strErrorMapValue%></option>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option><%=strErrorMapValue%></option>", 1, 0, 10001 );
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
      //:// IF lSubtype = 0  now always do setNextContinue here for performance reasons dks/dgc 2011.05.03
      //:      szWriteBuffer = "         csrRC =  v" + szCtrlTag +
      //:                      ".cursor( ^" + szListEntityName +
      //:                      "^ ).setNextContinue( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         csrRC =  v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setNextContinue( );", 1, 0, 10001 );
      //:                      //"^ ).setNext( " + szScopingEntityName + " );"
      //:// ELSE
      //://    szWriteBuffer = "         nRC =  v" + szCtrlTag +
      //://                    ".cursor( ^" + szListEntityName + "^ ).setNextWithinOi( );"
      //:// END

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
   //:   szWriteBuffer = "      v" + szCtrlTag + ".drop( );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ".drop( );", 1, 0, 10001 );
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
//:GenJSPJ_CrteJPG( VIEW vDialog BASED ON LOD TZWDLGSO,
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
GenJSPJ_CrteJPG( zVIEW     vDialog,
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
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 261 ]; 
   zCHAR     szTempString_12[ 261 ]; 


   //:CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );

   //:// If this window is being generated with no positioning then
   //:// do not create the position in the style.
   //:IF szNoPositioning = "Y"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:CreateNoPosStyleString( vDialog, szStyle, "" )
      CreateNoPosStyleString( vDialog, szStyle, "" );
      //:ELSE
   } 
   else
   { 
      //:IF szNoPositioning = "S"
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = "" // No style information.
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
         //:ELSE 
      } 
      else
      { 
         //:CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
         CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" );
      } 

      //:END
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

      //:szWriteBuffer = "   " + vDialog.CtrlMapView.Name + " = " +
      //:                "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name +
      //:         ".log( ).debug( ^Invalid View: ^, ^" + szCtrlTag + "^ );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".log( ).debug( ^Invalid View: ^, ^", 1, 0, 10001 );
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
      //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         strErrorMapValue = " +
      //:                vDialog.CtrlMapView.Name +
      //:                ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
      //:                szContextName + "^ );"
      GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to ""
      //:szWriteBuffer = "         if ( strErrorMapValue == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strErrorMapValue == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            strErrorMapValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            strErrorMapValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
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
         //:szWriteBuffer = "<img src=^<%=strErrorMapValue%>^ onclick=^" + szActionName + "( )^ " + szStyle + szTitleHTML + szClass + szText + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<img src=^<%=strErrorMapValue%>^ onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^ ", 1, 0, 10001 );
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
            //:// szWriteBuffer = "<a href=^#^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ ><img src=^" +
            //://    vDialog.Control.WebFileName + "^ " + szStyle + szTitleHTML + "></a>"
            //:szWriteBuffer = "<img src=^" + vDialog.Control.WebFileName + "^  name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ " +
            //:                  szStyle + szTitleHTML + szClass + szText + ">"
            GetVariableFromAttribute( szTempString_11, 0, 'S', 261, vDialog, "Control", "WebFileName", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<img src=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
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
            GetVariableFromAttribute( szTempString_12, 0, 'S', 261, vDialog, "Control", "WebFileName", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<img src=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
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

         //:// szWriteBuffer = "<a href=^#^ name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^ ^onclick=^" +
         //://                 szActionName + "( )^><img src=^" + vDialog.Control.WebFileName + "^ " + szStyle + szTitleHTML + "></a>"
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
//:GenJSPJ_CrteText( VIEW vDialog      BASED ON LOD TZWDLGSO,
//:                  VIEW vGroupParent BASED ON LOD TZWDLGSO,
//:                  VIEW vDialogRoot  BASED ON LOD TZWDLGSO,
//:                  INTEGER          lFile,
//:                  STRING ( 10000 ) szWriteBuffer,
//:                  STRING ( 50 )    szIndent,
//:                  STRING ( 32 )    szCtrlTag,
//:                  STRING ( 20 )    szJustify,
//:                  STRING ( 1 )     szNoPositioning,
//:                  INTEGER          lOffsetX,
//:                  INTEGER          lOffsetY,
//:                  STRING ( 100 )   szRepeatGrpKey )

//:   // Format a TEXT control.

//:   STRING ( 32 )  szContextName
zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteText( zVIEW     vDialog,
                  zVIEW     vGroupParent,
                  zVIEW     vDialogRoot,
                  zLONG     lFile,
                  zPCHAR    szWriteBuffer,
                  zPCHAR    szIndent,
                  zPCHAR    szCtrlTag,
                  zPCHAR    szJustify,
                  zPCHAR    szNoPositioning,
                  zLONG     lOffsetX,
                  zLONG     lOffsetY,
                  zPCHAR    szRepeatGrpKey )
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
   //:STRING ( 265 ) szHTML5Attr
   zCHAR     szHTML5Attr[ 266 ] = { 0 }; 
   //:STRING ( 1000 ) szText
   zCHAR     szText[ 1001 ] = { 0 }; 
   //:STRING ( 1000 ) szText2
   zCHAR     szText2[ 1001 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLength
   zCHAR     szMaxStringLength[ 11 ] = { 0 }; 
   //:STRING ( 20 )  szGroupParentType
   zCHAR     szGroupParentType[ 21 ] = { 0 }; 
   //:STRING ( 256 ) szHTMLCtrlID
   zCHAR     szHTMLCtrlID[ 257 ] = { 0 }; 
   //:STRING ( 10 )  szX_Pos
   zCHAR     szX_Pos[ 11 ] = { 0 }; 
   //:STRING ( 10 )  szY_Pos
   zCHAR     szY_Pos[ 11 ] = { 0 }; 
   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   //:INTEGER        lMaxStringLength
   zLONG     lMaxStringLength = 0; 
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
   //:STRING ( 256 ) szLabelFor
   zCHAR     szLabelFor[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szDecoration
   zCHAR     szDecoration[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTempStyle
   zCHAR     szTempStyle[ 257 ] = { 0 }; 
   //:STRING ( 1 )   szIsLabel
   zCHAR     szIsLabel[ 2 ] = { 0 }; 
   //:SHORT          nRC
   zSHORT    nRC = 0; 
   zCHAR     szTempString_0[ 255 ]; 
   zCHAR     szTempString_1[ 255 ]; 
   zSHORT    RESULT; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 
   zCHAR     szTempString_12[ 33 ]; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_13[ 33 ]; 
   zCHAR     szTempString_14[ 33 ]; 
   zCHAR     szTempString_15[ 33 ]; 
   zCHAR     szTempString_16[ 33 ]; 
   zCHAR     szTempString_17[ 33 ]; 
   zSHORT    lTempInteger_2; 
   zCHAR     szTempString_18[ 33 ]; 
   zCHAR     szTempString_19[ 33 ]; 
   zCHAR     szTempString_20[ 33 ]; 
   zCHAR     szTempString_21[ 33 ]; 
   zCHAR     szTempString_22[ 33 ]; 
   zCHAR     szTempString_23[ 33 ]; 
   zLONG     lTempInteger_3; 
   zCHAR     szTempString_24[ 255 ]; 
   zCHAR     szTempString_25[ 33 ]; 
   zCHAR     szTempString_26[ 33 ]; 
   zCHAR     szTempString_27[ 255 ]; 


   //:// KJS 09/30/16 - Language Conversion.
   //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
   //:// So for now, I am always using, if the flag is set.
   //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
   if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
   { 
      //:// Seems like we need to check the text, and if the text has " then we shouldn't use the getLanguageText. Because one example we have
      //:// is where the text is <img src="./images/admi..." border="0".
      //:szText2 = vDialog.Control.Text
      GetVariableFromAttribute( szText2, 0, 'S', 1001, vDialog, "Control", "Text", "", 0 );
      //:zSearchAndReplace( szText2, 1000, "\", "\\" )
      zSearchAndReplace( szText2, 1000, "\\", "\\\\" );
      //:szStyle = "\" + QUOTES 
      ZeidonStringCopy( szStyle, 1, 0, "\\", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, QUOTES, 1, 0, 257 );
      //:zSearchAndReplace( szText2, 1000, QUOTES, szStyle )
      zSearchAndReplace( szText2, 1000, QUOTES, szStyle );
      //:szStyle = ""
      ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
      //:szText = "<%=LangConv.getLanguageText(^" + szText2 + "^)%>" 
      ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 1001 );
      ZeidonStringConcat( szText, 1, 0, szText2, 1, 0, 1001 );
      ZeidonStringConcat( szText, 1, 0, "^)%>", 1, 0, 1001 );
      //:ELSE
   } 
   else
   { 
      //:szText = vDialog.Control.Text
      GetVariableFromAttribute( szText, 0, 'S', 1001, vDialog, "Control", "Text", "", 0 );
   } 

   //:END

   //:CreateTabIndexString( vDialog, szTabIndex )
   CreateTabIndexString( vDialog, szTabIndex );

   //:szHTMLCtrlID = " id=^" + szCtrlTag + szRepeatGrpKey + "^ name=^" + szCtrlTag + szRepeatGrpKey + "^ "
   ZeidonStringCopy( szHTMLCtrlID, 1, 0, " id=^", 1, 0, 257 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, szCtrlTag, 1, 0, 257 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, szRepeatGrpKey, 1, 0, 257 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, "^ name=^", 1, 0, 257 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, szCtrlTag, 1, 0, 257 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, szRepeatGrpKey, 1, 0, 257 );
   ZeidonStringConcat( szHTMLCtrlID, 1, 0, "^ ", 1, 0, 257 );

   //:szHTML5Attr = ""
   ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 266 );
   //:IF vDialog.Control.WebHTML5Attribute != ""
   if ( CompareAttributeToString( vDialog, "Control", "WebHTML5Attribute", "" ) != 0 )
   { 
      //:szHTML5Attr = " " + vDialog.Control.WebHTML5Attribute + " "
      GetVariableFromAttribute( szTempString_0, 0, 'S', 255, vDialog, "Control", "WebHTML5Attribute", "", 0 );
      ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 266 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_0, 1, 0, 266 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 266 );
   } 

   //:END

   //:IF  szNoPositioning = "Y"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:CreateNoPosStyleString( vDialog, szStyle, "" )
      CreateNoPosStyleString( vDialog, szStyle, "" );
      //:ELSE
   } 
   else
   { 
      //:IF szNoPositioning = "S" // No style information
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = "" 
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
         //:ELSE 
      } 
      else
      { 
         //:CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" )
         CreateAbsolStyleString( vDialog, szStyle, lOffsetX, lOffsetY, "" );
      } 

      //:END
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

   //:IF szNoPositioning != "S" 
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) != 0 )
   { 
      //:zAppendQuotedString( szStyle, szDecoration, "style=", "^" )
      zAppendQuotedString( szStyle, szDecoration, "style=", "^" );
   } 

   //:END
   //:szStyle = szStyle + szTabIndex
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );
   //:IF vDialog.Control.CSS_Class != ""
   if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) != 0 )
   { 
      //:szClassHTML = "class=^" + vDialog.Control.CSS_Class + "^ "
      GetVariableFromAttribute( szTempString_1, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClassHTML, 1, 0, "class=^", 1, 0, 257 );
      ZeidonStringConcat( szClassHTML, 1, 0, szTempString_1, 1, 0, 257 );
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
      //:///*
      //:SET CURSOR FIRST vGroupParent.WebControlProperty WHERE vGroupParent.WebControlProperty.Name = "Relative Positioning"
      RESULT = SetCursorFirstEntityByString( vGroupParent, "WebControlProperty", "Name", "Relative Positioning", "" );
      //:IF RESULT >= zCURSOR_SET
      if ( RESULT >= zCURSOR_SET )
      { 
         //:szGroupParentType = "RelativePos"
         ZeidonStringCopy( szGroupParentType, 1, 0, "RelativePos", 1, 0, 21 );
         //:ELSE
      } 
      else
      { 
         //:szGroupParentType = vGroupParent.Control.WebCtrlType
         GetVariableFromAttribute( szGroupParentType, 0, 'S', 21, vGroupParent, "Control", "WebCtrlType", "", 0 );
      } 

      //:END
      //://*/
      //://szGroupParentType = vGroupParent.Control.WebCtrlType
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
      //:szWriteBuffer = "   " + vDialog.CtrlMapView.Name + " = " +
      //:                "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      task.log( ).debug( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      task.log( ).debug( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
      //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
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

      //:/**********************************/
      //:// Add try/catch
      //:szWriteBuffer = "      try"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      try", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:IF vDialog.CtrlMapER_Domain.DataType = "T" OR vDialog.CtrlMapER_Domain.DataType = "D"
      if ( CompareAttributeToString( vDialog, "CtrlMapER_Domain", "DataType", "T" ) == 0 || CompareAttributeToString( vDialog, "CtrlMapER_Domain", "DataType", "D" ) == 0 )
      { 
         //:szWriteBuffer = "         strTextDisplayValue = " +
         //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
         //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
         //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
         //:                szContextName + "^ );"
         GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strTextDisplayValue = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:IF vDialog.CtrlMapER_Domain.MaxStringLth > 254
         if ( CompareAttributeToInteger( vDialog, "CtrlMapER_Domain", "MaxStringLth", 254 ) > 0 )
         { 
            //:lMaxStringLength = vDialog.CtrlMapER_Domain.MaxStringLth
            GetIntegerFromAttribute( &lMaxStringLength, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
            //:szMaxStringLength = lMaxStringLength
            ZeidonStringConvertFromNumber( szMaxStringLength, 1, 0, 10, lMaxStringLength, (ZDecimal) 0.0, "I" );
            //:ELSE
         } 
         else
         { 
            //:szMaxStringLength = "254"
            ZeidonStringCopy( szMaxStringLength, 1, 0, "254", 1, 0, 11 );
         } 

         //:END

         //:szWriteBuffer = "         strTextDisplayValue = " +
         //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
         //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
         //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
         //:                szContextName + "^ );"
         GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strTextDisplayValue = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_12, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      } 

      //:END

      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      catch (Exception e)"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      catch (Exception e)", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //://szWriteBuffer = "         strBuildPageError = e.getMessage();"
      //:szWriteBuffer = "         out.println(^There is an error on " + szCtrlTag + ": ^ + e.getMessage());"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         out.println(^There is an error on ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + e.getMessage());", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         task.log().info( ^*** Error on ctrl " + szCtrlTag + "^ + e.getMessage() );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         task.log().info( ^*** Error on ctrl ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ + e.getMessage() );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:/***************** END OF try/catch **********************/

      //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
      //:szWriteBuffer = "         if ( strTextDisplayValue == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strTextDisplayValue == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            strTextDisplayValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            strTextDisplayValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
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

      //:// KJS 09/30/16 - Language Conversion.
      //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
      //:// So for now, I am always using, if the flag is set.
      //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
      { 
         //:szText = "<%=LangConv.getLanguageText(strTextDisplayValue)%>" 
         ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(strTextDisplayValue)%>", 1, 0, 1001 );
         //:ELSE
      } 
      else
      { 
         //:szText = "<%=strTextDisplayValue%>"
         ZeidonStringCopy( szText, 1, 0, "<%=strTextDisplayValue%>", 1, 0, 1001 );
      } 

      //:END
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
            //:szWriteBuffer = "   " + vDialog.CtrlMapView.Name + " = " +
            //:                "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
            GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_14, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
            GetVariableFromAttribute( szTempString_15, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_15, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      task.log( ).debug( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      task.log( ).debug( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
            //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
            GetVariableFromAttribute( szTempString_16, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_16, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_17, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_17, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
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
               //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
               //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
               //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
               //:                szContextName + "^ );"
               GetVariableFromAttribute( szTempString_18, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         strTextURL_Value = ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_18, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_19, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_19, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_20, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_20, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
               //:ELSE
            } 
            else
            { 
               //:IF vDialog.CtrlMapER_Domain.MaxStringLth > 254
               if ( CompareAttributeToInteger( vDialog, "CtrlMapER_Domain", "MaxStringLth", 254 ) > 0 )
               { 
                  //:lMaxStringLength = vDialog.CtrlMapER_Domain.MaxStringLth
                  GetIntegerFromAttribute( &lMaxStringLength, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
                  //:szMaxStringLength = lMaxStringLength
                  ZeidonStringConvertFromNumber( szMaxStringLength, 1, 0, 10, lMaxStringLength, (ZDecimal) 0.0, "I" );
                  //:ELSE
               } 
               else
               { 
                  //:szMaxStringLength = "254"
                  ZeidonStringCopy( szMaxStringLength, 1, 0, "254", 1, 0, 11 );
               } 

               //:END

               //:szWriteBuffer = "         strTextURL_Value = " +
               //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
               //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
               //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
               //:                szContextName + "^ );"
               GetVariableFromAttribute( szTempString_21, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         strTextURL_Value = ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_21, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_22, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_22, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
               GetVariableFromAttribute( szTempString_23, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_23, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            } 

            //:END

            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
            //:szWriteBuffer = "         if ( strTextURL_Value == null )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strTextURL_Value == null )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            strTextURL_Value = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            strTextURL_Value = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
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
            //:szWriteBuffer = "<a href=^<%=strTextURL_Value%>^  " + szHTMLCtrlID + szClassHTML + szTitleHTML + szStyle + " target=^_blank^>" + szText + "</a>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<a href=^<%=strTextURL_Value%>^  ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
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
            //:szWriteBuffer = "<a href=^" + vDialogRoot.Action.WebHTML_TransferAddress + "^  " + szHTMLCtrlID + szClassHTML + szTitleHTML + szStyle + " target=^_blank^>" + szText + "</a>"
            GetVariableFromAttribute( szTempString_24, 0, 'S', 255, vDialogRoot, "Action", "WebHTML_TransferAddress", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<a href=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_24, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^  ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
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
         //:IF szRepeatGrpKey = ""
         if ( ZeidonStringCompare( szRepeatGrpKey, 1, 0, "", 1, 0, 101 ) == 0 )
         { 
            //:szWriteBuffer = "<a href=^#^" + szHTMLCtrlID + " onclick=^" + vDialog.EventAct.Tag + "( );^ " + szClassHTML + szTitleHTML + szStyle + ">" + szText + "</a>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<a href=^#^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " onclick=^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_25, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_25, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "( );^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</a>", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "<a href=^#^" + szHTMLCtrlID + "  onclick=^" + vDialog.EventAct.Tag + "( '" + szCtrlTag + szRepeatGrpKey + "' );^ " + szClassHTML + szTitleHTML + szStyle + ">" + szText + "</a>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<a href=^#^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "  onclick=^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_26, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_26, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "( '", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "' );^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</a>", 1, 0, 10001 );
         } 

         //:END
      } 

      //:END
      //:ELSE
   } 
   else
   { 
      //:// Regular Text Control (No HotText)
      //:szWriteBuffer = ""
      ZeidonStringCopy( szWriteBuffer, 1, 0, "", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

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
            GetVariableFromAttribute( szTempString_27, 0, 'S', 255, vDialog, "Control", "WebCtrlLabelLink", "", 0 );
            ZeidonStringCopy( szLabelFor, 1, 0, " for=^", 1, 0, 257 );
            ZeidonStringConcat( szLabelFor, 1, 0, szTempString_27, 1, 0, 257 );
            ZeidonStringConcat( szLabelFor, 1, 0, "^ ", 1, 0, 257 );
         } 

         //:END
      } 

      //:END

      //:// If szNoPositioning is null then we are using absolute positioning when creating controls.
      //:IF  szNoPositioning = ""
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
      { 

         //:// PIX_PER_DU( vDialog, dDLUnits )
         //:// zIntegerToString( szX_Pos, 10, vDialog.Control.PSDLG_X * dDLUnits )
         //:// zIntegerToString( szY_Pos, 10, vDialog.Control.PSDLG_Y * dDLUnits )
         //:// szTempStyle = "position:absolute;left:" + szX_Pos + "px;" + "top:" + szY_Pos + "px;^ "
         //:zAppendQuotedString( szStyle, szDecoration, "style=", "^" )
         zAppendQuotedString( szStyle, szDecoration, "style=", "^" );
         //:szWriteBuffer = "<label " + szClassHTML + szHTMLCtrlID + szTitleHTML + szStyle + ">" + szText + "</label>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<label ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</label>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 

         //:// If there is a "Label" web control property than make this a label, otherwise, just use <span>.
         //:IF szIsLabel = "Y"
         if ( ZeidonStringCompare( szIsLabel, 1, 0, "Y", 1, 0, 2 ) == 0 )
         { 
            //:szWriteBuffer = "<label " + szClassHTML + szHTMLCtrlID + szHTML5Attr + szLabelFor + szTitleHTML + szStyle + ">" + szText + "</label>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<label ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
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
            //:szWriteBuffer = "<span " + szClassHTML + szHTMLCtrlID + szTitleHTML + szHTML5Attr + szStyle + ">" + szText + "</span>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<span ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szClassHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</span>", 1, 0, 10001 );
         } 

         //:END
      } 


      //:END
   } 

   //:END

   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSPJ_CrteEditBox( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 20 )    szJustify,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY,
//:                     STRING ( 100 )   szRepeatGrpKey )

//:   // Format an EDITBOX control.

//:   VIEW vDialogRoot BASED ON LOD TZWDLGSO
zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteEditBox( zVIEW     vDialog,
                     zLONG     lFile,
                     zPCHAR    szWriteBuffer,
                     zPCHAR    szIndent,
                     zPCHAR    szCtrlTag,
                     zPCHAR    szTableRowFlag,
                     zPCHAR    szJustify,
                     zPCHAR    szNoPositioning,
                     zLONG     lOffsetX,
                     zLONG     lOffsetY,
                     zPCHAR    szRepeatGrpKey )
{
   zVIEW     vDialogRoot = 0; 
   //:STRING ( 32 )  szContextName
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 300 ) szValue
   zCHAR     szValue[ 301 ] = { 0 }; 
   //:STRING ( 600 ) szBlob
   zCHAR     szBlob[ 601 ] = { 0 }; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szHTML5Attr
   zCHAR     szHTML5Attr[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szPlaceholder
   zCHAR     szPlaceholder[ 257 ] = { 0 }; 
   //:STRING ( 300 ) szType
   zCHAR     szType[ 301 ] = { 0 }; 
   //:STRING ( 64 )  szWidget
   zCHAR     szWidget[ 65 ] = { 0 }; 
   //:STRING ( 16 )  szTabIndex
   zCHAR     szTabIndex[ 17 ] = { 0 }; 
   //:STRING ( 600 ) szEditActionCode
   zCHAR     szEditActionCode[ 601 ] = { 0 }; 
   //:STRING ( 32 )  szActionName
   zCHAR     szActionName[ 33 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLength
   zCHAR     szMaxStringLength[ 11 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:STRING ( 20 )  szAutoCompleteOff
   zCHAR     szAutoCompleteOff[ 21 ] = { 0 }; 
   //:STRING ( 1 )   szWCP_Hidden
   zCHAR     szWCP_Hidden[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szCreateSessionVariable
   zCHAR     szCreateSessionVariable[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szNoOutputMapping
   zCHAR     szNoOutputMapping[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szBrowseFile
   zCHAR     szBrowseFile[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szNumber
   zCHAR     szNumber[ 2 ] = { 0 }; 

   //:INTEGER        lMaxStringLength
   zLONG     lMaxStringLength = 0; 
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
   zCHAR     szTempString_12[ 255 ]; 
   zSHORT    lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zCHAR     szTempString_13[ 255 ]; 
   zCHAR     szTempString_14[ 255 ]; 
   zCHAR     szTempString_15[ 255 ]; 
   zCHAR     szTempString_16[ 255 ]; 
   zCHAR     szTempString_17[ 255 ]; 


   //:TraceLineS("*** GenJSPJ_CrteEditBox *** ", "")
   TraceLineS( "*** GenJSPJ_CrteEditBox *** ", "" );

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

   //:IF szNoPositioning = "S" // No style information but I think we need the error color.
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
   { 
      //:szStyle = "style=^<%=strErrorColor%>^"
      ZeidonStringCopy( szStyle, 1, 0, "style=^<%=strErrorColor%>^", 1, 0, 257 );
      //:ELSE 
   } 
   else
   { 
      //:FixStyleString( szStyle, szSize, szPosition,  "<%=strErrorColor%>"  )
      FixStyleString( szStyle, szSize, szPosition, "<%=strErrorColor%>" );
   } 

   //:END

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

   //:szAutoCompleteOff = "" 
   ZeidonStringCopy( szAutoCompleteOff, 1, 0, "", 1, 0, 21 );
   //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Autocomplete Off"
   RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Autocomplete Off", "" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szAutoCompleteOff = " autocomplete=^off^"
      ZeidonStringCopy( szAutoCompleteOff, 1, 0, " autocomplete=^off^", 1, 0, 21 );
   } 

   //:END

   //:szNumber = "" 
   ZeidonStringCopy( szNumber, 1, 0, "", 1, 0, 2 );
   //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Number"
   RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Number", "" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szNumber = "Y"
      ZeidonStringCopy( szNumber, 1, 0, "Y", 1, 0, 2 );
   } 

   //:END

   //:// We have an Upload file on the group box, but what if we aren't uploading the file, we just want the user
   //:// to be able to select a directory/file name.
   //:szBrowseFile = "" 
   ZeidonStringCopy( szBrowseFile, 1, 0, "", 1, 0, 2 );
   //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Browse File"
   RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Browse File", "" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:TraceLineS("*** Browse File is Y *** ", "" )
      TraceLineS( "*** Browse File is Y *** ", "" );
      //:szBrowseFile = "Y"
      ZeidonStringCopy( szBrowseFile, 1, 0, "Y", 1, 0, 2 );
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
      //:szWriteBuffer = "   strErrorMapValue = VmlOperation.CheckError( ^" + szCtrlTag + "^, strError );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = VmlOperation.CheckError( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, strError );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( !StringUtils.isBlank( strErrorMapValue ) )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( !StringUtils.isBlank( strErrorMapValue ) )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( StringUtils.equals( strErrorFlag, ^Y^ ) )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( StringUtils.equals( strErrorFlag, ^Y^ ) )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         strErrorColor = ^color:red;^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorColor = ^color:red;^;", 1, 0, 10001 );
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
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name + " = " + "task.getViewByName( ^" +
      //:                vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         task.log( ).debug( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         task.log( ).debug( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
      //:szWriteBuffer = "         nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
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

      //:/**********************************/
      //:// Add try/catch
      //:szWriteBuffer = "            try"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            try", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:IF vDialog.CtrlMapER_Domain.MaxStringLth > 254
      if ( CompareAttributeToInteger( vDialog, "CtrlMapER_Domain", "MaxStringLth", 254 ) > 0 )
      { 
         //:lMaxStringLength = vDialog.CtrlMapER_Domain.MaxStringLth
         GetIntegerFromAttribute( &lMaxStringLength, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
         //:szMaxStringLength = lMaxStringLength
         ZeidonStringConvertFromNumber( szMaxStringLength, 1, 0, 10, lMaxStringLength, (ZDecimal) 0.0, "I" );
         //:ELSE
      } 
      else
      { 
         //:szMaxStringLength = "254"
         ZeidonStringCopy( szMaxStringLength, 1, 0, "254", 1, 0, 11 );
      } 

      //:END
      //:szWriteBuffer = "               strErrorMapValue = " +
      //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
      //:                szContextName + "^ );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:IF vDialog.Control.WebCtrlType = "escapeHTML"
      if ( CompareAttributeToString( vDialog, "Control", "WebCtrlType", "escapeHTML" ) == 0 )
      { 
         //:szWriteBuffer = "               task.log().debug( ^" + szCtrlTag + " prior to unescape: ^ + strErrorMapValue );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "               task.log().debug( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " prior to unescape: ^ + strErrorMapValue );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "               strErrorMapValue = StringEscapeUtils.unescapeHtml4( strErrorMapValue );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = StringEscapeUtils.unescapeHtml4( strErrorMapValue );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "               task.log().debug( ^" + szCtrlTag + " after unescape: ^ + strErrorMapValue );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "               task.log().debug( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " after unescape: ^ + strErrorMapValue );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      } 

      //:END

      //:szWriteBuffer = "            }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            catch (Exception e)"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            catch (Exception e)", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            {"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "               out.println(^There is an error on " + szCtrlTag + ": ^ + e.getMessage());"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               out.println(^There is an error on ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + e.getMessage());", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "               task.log().error( ^*** Error on ctrl " + szCtrlTag + "^, e );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               task.log().error( ^*** Error on ctrl ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^, e );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "            }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:/***************** END OF try/catch **********************/

      //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
      //:szWriteBuffer = "            if ( strErrorMapValue == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( strErrorMapValue == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "               strErrorMapValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:szWriteBuffer = "            task.log( ).debug( ^" + vDialog.CtrlMapRelatedEntity.Name + "." +
      //:                vDialog.CtrlMapER_Attribute.Name + ": ^ + strErrorMapValue );"
      GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).debug( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + strErrorMapValue );", 1, 0, 10001 );
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
      //:szWriteBuffer = "            task.log( ).debug( ^Entity does not exist for " + szCtrlTag + ": ^ + ^" +
      //:                vDialog.CtrlMapView.Name +
      //:                "." + vDialog.CtrlMapRelatedEntity.Name + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).debug( ^Entity does not exist for ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
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

         //:szWriteBuffer = "      if ( strErrorMapValue == ^^ )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strErrorMapValue == ^^ )", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "         strErrorMapValue = ^" + vDialog.Control.Text + "^;"
         GetVariableFromAttribute( szTempString_12, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
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

   //:// Get the format for the edit box if specified.
   //:lTemp = 600
   lTemp = 600;
   //:GetBlobFromAttribute( szBlob, lTemp, vDialog, "Control", "CtrlBOI" )
   GetBlobFromAttribute( szBlob, (zPULONG) &lTemp, vDialog, "Control", "CtrlBOI" );
   //:lTemp = lTemp - (3 * zSIZEOFLONG)
   lTemp = lTemp - ( 3 * zSIZEOFLONG );
   //:IF lTemp <= 0
   if ( lTemp <= 0 )
   { 
      //:szBlob = ""
      ZeidonStringCopy( szBlob, 1, 0, "", 1, 0, 601 );
      //:ELSE
   } 
   else
   { 
      //:lTemp = (3 * zSIZEOFLONG) + 1
      lTemp = ( 3 * zSIZEOFLONG ) + 1;
      //:ZeidonCopyWithinString( szBlob, 1, lTemp, 600 )
      ZeidonCopyWithinString( szBlob, 1, lTemp, 600 );
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
      ZeidonStringCopy( szType, 1, 0, " type=^hidden^ ", 1, 0, 301 );
      //:ELSE
   } 
   else
   { 
      //:IF szBrowseFile = "Y"
      if ( ZeidonStringCompare( szBrowseFile, 1, 0, "Y", 1, 0, 2 ) == 0 )
      { 
         //:szType = " type=^file^ "
         ZeidonStringCopy( szType, 1, 0, " type=^file^ ", 1, 0, 301 );
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
            ZeidonStringCopy( szType, 1, 0, " type=^password^ ", 1, 0, 301 );
            //:ELSE
         } 
         else
         { 
            //:IF szNumber = "Y"
            if ( ZeidonStringCompare( szNumber, 1, 0, "Y", 1, 0, 2 ) == 0 )
            { 
               //:szType = " type=^number^"
               ZeidonStringCopy( szType, 1, 0, " type=^number^", 1, 0, 301 );
               //:ELSE
            } 
            else
            { 
               //:szType = " type=^text^ "
               ZeidonStringCopy( szType, 1, 0, " type=^text^ ", 1, 0, 301 );
               //:IF szBlob != ""
               if ( ZeidonStringCompare( szBlob, 1, 0, "", 1, 0, 601 ) != 0 )
               { 
                  //:szType = szType + "mask=^"
                  ZeidonStringConcat( szType, 1, 0, "mask=^", 1, 0, 301 );
                  //:szType = szType + szBlob
                  ZeidonStringConcat( szType, 1, 0, szBlob, 1, 0, 301 );
                  //:szType = szType + "^ onblur=^return onBlurMask(this);^ onfocus=^return onFocusMask(this);^ onkeydown=^return doMask(this);^ "
                  ZeidonStringConcat( szType, 1, 0, "^ onblur=^return onBlurMask(this);^ onfocus=^return onFocusMask(this);^ onkeydown=^return doMask(this);^ ", 1, 0, 301 );
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

   //:// If there is an Event for the EditBox, build code to insert in <input statement.
   //:szEditActionCode = ""
   ZeidonStringCopy( szEditActionCode, 1, 0, "", 1, 0, 601 );
   //:FOR EACH vDialog.Event
   RESULT = SetCursorFirstEntity( vDialog, "Event", "" );
   while ( RESULT > zCURSOR_UNCHANGED )
   { 
      //:IF vDialog.EventAct EXISTS
      lTempInteger_3 = CheckExistenceOfEntity( vDialog, "EventAct" );
      if ( lTempInteger_3 == 0 )
      { 
         //:szActionName = vDialog.EventAct.Tag
         GetVariableFromAttribute( szActionName, 0, 'S', 33, vDialog, "EventAct", "Tag", "", 0 );
         //:IF vDialog.Event.Type = 16
         if ( CompareAttributeToInteger( vDialog, "Event", "Type", 16 ) == 0 )
         { 
            //:szEditActionCode = szEditActionCode + " onfocus=^" + szActionName + "( )^ "
            ZeidonStringConcat( szEditActionCode, 1, 0, " onfocus=^", 1, 0, 601 );
            ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 601 );
            ZeidonStringConcat( szEditActionCode, 1, 0, "( )^ ", 1, 0, 601 );
            //:ELSE
         } 
         else
         { 
            //:IF vDialog.Event.Type = 17
            if ( CompareAttributeToInteger( vDialog, "Event", "Type", 17 ) == 0 )
            { 
               //:szEditActionCode = szEditActionCode + " onblur=^" + szActionName + "( )^ "
               ZeidonStringConcat( szEditActionCode, 1, 0, " onblur=^", 1, 0, 601 );
               ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 601 );
               ZeidonStringConcat( szEditActionCode, 1, 0, "( )^ ", 1, 0, 601 );
               //:ELSE
            } 
            else
            { 
               //:IF vDialog.Event.Type = 18
               if ( CompareAttributeToInteger( vDialog, "Event", "Type", 18 ) == 0 )
               { 
                  //:szEditActionCode = szEditActionCode + " onchange=^" + szActionName + "( )^ "
                  ZeidonStringConcat( szEditActionCode, 1, 0, " onchange=^", 1, 0, 601 );
                  ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 601 );
                  ZeidonStringConcat( szEditActionCode, 1, 0, "( )^ ", 1, 0, 601 );
                  //:ELSE
               } 
               else
               { 
                  //:IF vDialog.Event.Type = 21
                  if ( CompareAttributeToInteger( vDialog, "Event", "Type", 21 ) == 0 )
                  { 
                     //:szEditActionCode = szEditActionCode + " onkeydown=^" + szActionName + "( )^ "
                     ZeidonStringConcat( szEditActionCode, 1, 0, " onkeydown=^", 1, 0, 601 );
                     ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 601 );
                     ZeidonStringConcat( szEditActionCode, 1, 0, "( )^ ", 1, 0, 601 );
                     //:ELSE
                  } 
                  else
                  { 
                     //:IF vDialog.Event.Type = 22
                     if ( CompareAttributeToInteger( vDialog, "Event", "Type", 22 ) == 0 )
                     { 
                        //:szEditActionCode = szEditActionCode + " onkeyup=^" + szActionName + "( )^ "
                        ZeidonStringConcat( szEditActionCode, 1, 0, " onkeyup=^", 1, 0, 601 );
                        ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 601 );
                        ZeidonStringConcat( szEditActionCode, 1, 0, "( )^ ", 1, 0, 601 );
                        //:ELSE
                     } 
                     else
                     { 
                        //:IF vDialog.Event.Type = 24
                        if ( CompareAttributeToInteger( vDialog, "Event", "Type", 24 ) == 0 )
                        { 
                           //:szEditActionCode = szEditActionCode + " onclick=^" + szActionName + "( )^ "
                           ZeidonStringConcat( szEditActionCode, 1, 0, " onclick=^", 1, 0, 601 );
                           ZeidonStringConcat( szEditActionCode, 1, 0, szActionName, 1, 0, 601 );
                           ZeidonStringConcat( szEditActionCode, 1, 0, "( )^ ", 1, 0, 601 );
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
      } 

      RESULT = SetCursorNextEntity( vDialog, "Event", "" );
      //:END
   } 

   //:END

   //:   // If there is a Default button for the window, we must add some characters
   //:   // to the end of the input statement.
   //:   CreateViewFromView( vDialogRoot, vDialog )
   CreateViewFromView( &vDialogRoot, vDialog );
   //:   nRC = ResetViewFromSubobject( vDialogRoot )
   nRC = ResetViewFromSubobject( vDialogRoot );
   //:   LOOP WHILE nRC = 0
   while ( nRC == 0 )
   { 
      //:   nRC = ResetViewFromSubobject( vDialogRoot )
      nRC = ResetViewFromSubobject( vDialogRoot );
   } 

   //:   END
   //:   IF vDialogRoot.Window.DfltButton != ""
   if ( CompareAttributeToString( vDialogRoot, "Window", "DfltButton", "" ) != 0 )
   { 
      //:szEditActionCode = szEditActionCode + " onkeypress=^return _OnEnter( event )^"
      ZeidonStringConcat( szEditActionCode, 1, 0, " onkeypress=^return _OnEnter( event )^", 1, 0, 601 );
   } 

   //:   END
   //:   DropView( vDialogRoot )
   DropView( vDialogRoot );

   //:IF szNoOutputMapping = "Y"
   if ( ZeidonStringCompare( szNoOutputMapping, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:   szValue = " value=^^"
      ZeidonStringCopy( szValue, 1, 0, " value=^^", 1, 0, 301 );
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
         //:szValue = " value=^" + vDialog.Control.Text + "^"
         GetVariableFromAttribute( szTempString_13, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
         ZeidonStringCopy( szValue, 1, 0, " value=^", 1, 0, 301 );
         ZeidonStringConcat( szValue, 1, 0, szTempString_13, 1, 0, 301 );
         ZeidonStringConcat( szValue, 1, 0, "^", 1, 0, 301 );
         //:ELSE
      } 
      else
      { 
         //:szValue = " value=^<%=strErrorMapValue%>^"
         ZeidonStringCopy( szValue, 1, 0, " value=^<%=strErrorMapValue%>^", 1, 0, 301 );
      } 

      //:END
   } 

   //:END

   //:IF szNoOutputMapping = "Y"
   if ( ZeidonStringCompare( szNoOutputMapping, 1, 0, "Y", 1, 0, 2 ) == 0 )
   { 
      //:   szValue = "value=^^"
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
         //:szValue = " value=^" + vDialog.Control.Text + "^"
         GetVariableFromAttribute( szTempString_14, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
         ZeidonStringCopy( szValue, 1, 0, " value=^", 1, 0, 301 );
         ZeidonStringConcat( szValue, 1, 0, szTempString_14, 1, 0, 301 );
         ZeidonStringConcat( szValue, 1, 0, "^", 1, 0, 301 );
         //:ELSE
      } 
      else
      { 
         //:szValue = " value=^<%=strErrorMapValue%>^"
         ZeidonStringCopy( szValue, 1, 0, " value=^<%=strErrorMapValue%>^", 1, 0, 301 );
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
   //:// KJS 08/23/16 - Doug and I both added placeholder. I had added a new attribute to tzwdlgso.lod
   //:// for this (WebPlaceholder) and I've only put this on the input field.
   //:// Doug has his on CommonDetail. For now we will keep both...
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

   //:szPlaceholder = ""
   ZeidonStringCopy( szPlaceholder, 1, 0, "", 1, 0, 257 );
   //:IF vDialog.Control.WebPlaceholder != ""
   if ( CompareAttributeToString( vDialog, "Control", "WebPlaceholder", "" ) != 0 )
   { 
      //:szPlaceholder = " placeholder=^" + vDialog.Control.WebPlaceholder + "^ "
      GetVariableFromAttribute( szTempString_15, 0, 'S', 255, vDialog, "Control", "WebPlaceholder", "", 0 );
      ZeidonStringCopy( szPlaceholder, 1, 0, " placeholder=^", 1, 0, 257 );
      ZeidonStringConcat( szPlaceholder, 1, 0, szTempString_15, 1, 0, 257 );
      ZeidonStringConcat( szPlaceholder, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //:szHTML5Attr = ""
   ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
   //:IF vDialog.Control.WebHTML5Attribute != ""
   if ( CompareAttributeToString( vDialog, "Control", "WebHTML5Attribute", "" ) != 0 )
   { 
      //:szHTML5Attr = " " + vDialog.Control.WebHTML5Attribute + " "
      GetVariableFromAttribute( szTempString_16, 0, 'S', 255, vDialog, "Control", "WebHTML5Attribute", "", 0 );
      ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_16, 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
   } 

   //:END

   //:szClass = ""
   ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
   //:IF vDialog.Control.CSS_Class != ""
   if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) != 0 )
   { 
      //:szClass = " class=^" + vDialog.Control.CSS_Class + "^ "
      GetVariableFromAttribute( szTempString_17, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, szTempString_17, 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, "^ ", 1, 0, 257 );
   } 

   //:END

   //:CreateDisabledString( vDialog, szDisabled )
   CreateDisabledString( vDialog, szDisabled );
   //:szWriteBuffer = "<input" + szClass + " name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ " + szDisabled +
   //:                szAutoCompleteOff + szTitleHTML + szPlaceholder + szStyle + szType + szValue + szEditActionCode + " >"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<input", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " name=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szAutoCompleteOff, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szPlaceholder, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szType, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szValue, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szEditActionCode, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " >", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSPJ_CrteGroupTable( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                        VIEW vGroupParent BASED ON LOD TZWDLGSO,
//:                        VIEW vDialogRoot BASED ON LOD TZWDLGSO,
//:                        INTEGER          lFile,
//:                        STRING ( 10000 ) szWriteBuffer,
//:                        STRING ( 100 )   szIndent,
//:                        INTEGER          lTableRowCnt,
//:                        STRING ( 1 )     szNoPositioning,
//:                        STRING ( 100 )   szRepeatGrpKey )

//:   INTEGER        X_Size
zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteGroupTable( zVIEW     vDialog,
                        zVIEW     vGroupParent,
                        zVIEW     vDialogRoot,
                        zLONG     lFile,
                        zPCHAR    szWriteBuffer,
                        zPCHAR    szIndent,
                        zLONG     lTableRowCnt,
                        zPCHAR    szNoPositioning,
                        zPCHAR    szRepeatGrpKey )
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
   //:INTEGER        lMaxStringLength
   zLONG     lMaxStringLength = 0; 
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
   //:STRING ( 256 ) szHTML5Attr
   zCHAR     szHTML5Attr[ 257 ] = { 0 }; 
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
   //:STRING ( 500 ) szText
   zCHAR     szText[ 501 ] = { 0 }; 
   //:STRING ( 500 ) szText2
   zCHAR     szText2[ 501 ] = { 0 }; 
   //:STRING ( 5 )   szSrch
   zCHAR     szSrch[ 6 ] = { 0 }; 
   //:STRING ( 32 )  szContextName
   zCHAR     szContextName[ 33 ] = { 0 }; 
   //:STRING ( 10 )  szMaxStringLength
   zCHAR     szMaxStringLength[ 11 ] = { 0 }; 
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
   //:STRING ( 1 )   szreCAPTCHAFlag
   zCHAR     szreCAPTCHAFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szTinyMCEFlag
   zCHAR     szTinyMCEFlag[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szWindowIsjMobile
   zCHAR     szWindowIsjMobile[ 2 ] = { 0 }; 
   //:STRING ( 1 )   szToggleFlag
   zCHAR     szToggleFlag[ 2 ] = { 0 }; 
   //:STRING ( 100 ) szIndentGroup
   zCHAR     szIndentGroup[ 101 ] = { 0 }; 
   //:STRING ( 50 )  szWebCtrlType
   zCHAR     szWebCtrlType[ 51 ] = { 0 }; 
   zCHAR     szTempString_0[ 255 ]; 
   zCHAR     szTempString_1[ 255 ]; 
   zSHORT    lTempInteger_0; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_1; 
   zCHAR     szTempString_2[ 255 ]; 
   zLONG     lTempInteger_2; 
   zCHAR     szTempString_3[ 255 ]; 
   zLONG     lTempInteger_3; 
   zLONG     lTempInteger_4; 
   zLONG     lTempInteger_5; 
   zLONG     lTempInteger_6; 
   zSHORT    lTempInteger_7; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 
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
   zCHAR     szTempString_21[ 33 ]; 
   zCHAR     szTempString_22[ 33 ]; 
   zCHAR     szTempString_23[ 33 ]; 
   zCHAR     szTempString_24[ 33 ]; 
   zCHAR     szTempString_25[ 255 ]; 


   //:LastY_Pos = 0
   LastY_Pos = 0;
   //:iColCnt = 0
   iColCnt = 0;
   //:iHighestColCnt = 0
   iHighestColCnt = 0;
   //:szIndent = szIndent + "   "
   ZeidonStringConcat( szIndent, 1, 0, "   ", 1, 0, 101 );

   //:X_Size = vGroupParent.Control.SZDLG_X
   GetIntegerFromAttribute( &X_Size, vGroupParent, "Control", "SZDLG_X" );
   //:Y_Size = vGroupParent.Control.SZDLG_Y
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


   //:IF vDialogRoot.WndStyle.Tag = "jMobile Window"
   if ( CompareAttributeToString( vDialogRoot, "WndStyle", "Tag", "jMobile Window" ) == 0 )
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

   //:   
   //:// KJS 02/23/16 - We have added a field for HTML5 attributes (this could be for jQuery Mobile or whatever extra attributes we want).
   //:// It is simply a string and we will add it to different controls like <div> or <input> etc.
   //:szHTML5Attr = ""
   ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
   //:IF vGroupParent.Control.WebHTML5Attribute != ""
   if ( CompareAttributeToString( vGroupParent, "Control", "WebHTML5Attribute", "" ) != 0 )
   { 
      //:szHTML5Attr = " " + vGroupParent.Control.WebHTML5Attribute + " "
      GetVariableFromAttribute( szTempString_1, 0, 'S', 255, vGroupParent, "Control", "WebHTML5Attribute", "", 0 );
      ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_1, 1, 0, 257 );
      ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
   } 

   //:END

   //:IF vDialog.Control EXISTS
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

      //:IF LastY_Pos < vDialog.Control.PSDLG_Y
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
   //:IF szNoPositioning = "Y"
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
   //:IF szNoPositioning = "S"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "<div id=^" + szParentCtrlTag + "^ name=^" + szParentCtrlTag + "^ "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szParentCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szParentCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "<div id=^" + szParentCtrlTag + "^ name=^" + szParentCtrlTag + "^ style=^float:left;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<div id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szParentCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szParentCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ style=^float:left;", 1, 0, 10001 );
      //:IF szNoWidthFlag = ""
      if ( ZeidonStringCompare( szNoWidthFlag, 1, 0, "", 1, 0, 2 ) == 0 )
      { 
         //:szWriteBuffer = szWriteBuffer + "width:" + szWidth + "px;^"
         ZeidonStringConcat( szWriteBuffer, 1, 0, "width:", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "px;^", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = szWriteBuffer + "^"
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^", 1, 0, 10001 );
      } 

      //:END
   } 

   //:END
   //:// KJS 02/23/16 - We have added a field for HTML5 attributes, but I am not sure whether this should be
   //:// here on the <div> (which surrounds the table) or whether this should be on the <table>. For now since the
   //:// class is here I will also put the HTLM5 attribute here.
   //:szWriteBuffer = szWriteBuffer + szHTML5Attr + " " + szClass + ">"
   ZeidonStringConcat( szWriteBuffer, 1, 0, szHTML5Attr, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, " ", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:// Now create the table with the proper number of columns.
   //://szWriteBuffer = "<table cols=" szColCount + " name=^" + szCtrlTag + "^ id=^" + szCtrlTag + "^>"
   //:IF szWindowIsjMobile = "" 
   if ( ZeidonStringCompare( szWindowIsjMobile, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:szWriteBuffer = "<table cols=" + szColCnt
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<table cols=", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szColCnt, 1, 0, 10001 );
      //:IF szNoWidthFlag = "" AND szNoPositioning != "S"
      if ( ZeidonStringCompare( szNoWidthFlag, 1, 0, "", 1, 0, 2 ) == 0 && ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) != 0 )
      { 
         //:szWriteBuffer = szWriteBuffer + " style=^width:" + szWidth + "px;^ "
         ZeidonStringConcat( szWriteBuffer, 1, 0, " style=^width:", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "px;^ ", 1, 0, 10001 );
      } 

      //:END
      //:szWriteBuffer = szWriteBuffer + " class=^grouptable^>"
      ZeidonStringConcat( szWriteBuffer, 1, 0, " class=^grouptable^>", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:// page is being generated for jmobile, so we don't want the grouptable or columns.
      //:szWriteBuffer = "<table data-role=^table^> "
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<table data-role=^table^> ", 1, 0, 10001 );
      //:szWriteBuffer = "<table data-role=^listview^> " // some reason "table" was causing page to hang.
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<table data-role=^listview^> ", 1, 0, 10001 );
      //:szWriteBuffer = "<table> " // now try nothing
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<table> ", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      //:szWriteBuffer = "<thead></thead>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<thead></thead>", 1, 0, 10001 );
   } 

   //:END
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

   //:szWriteBuffer = "<tr>"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<tr>", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
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


      //:// KJS 02/23/16 - We have added a field for HTML5 attributes (this could be for jQuery Mobile or whatever extra attributes we want).
      //:// It is simply a string and we will add it to different controls like <div> or <input> etc.
      //:szHTML5Attr = ""
      ZeidonStringCopy( szHTML5Attr, 1, 0, "", 1, 0, 257 );
      //:IF vDialog.Control.WebHTML5Attribute != ""
      if ( CompareAttributeToString( vDialog, "Control", "WebHTML5Attribute", "" ) != 0 )
      { 
         //:szHTML5Attr = " " + vDialog.Control.WebHTML5Attribute + " "
         GetVariableFromAttribute( szTempString_2, 0, 'S', 255, vDialog, "Control", "WebHTML5Attribute", "", 0 );
         ZeidonStringCopy( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
         ZeidonStringConcat( szHTML5Attr, 1, 0, szTempString_2, 1, 0, 257 );
         ZeidonStringConcat( szHTML5Attr, 1, 0, " ", 1, 0, 257 );
      } 

      //:END


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
         GetVariableFromAttribute( szTempString_3, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
         ZeidonStringCopy( szClass, 1, 0, " class=^", 1, 0, 257 );
         ZeidonStringConcat( szClass, 1, 0, szTempString_3, 1, 0, 257 );
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
      //:IF szNoPositioning = "S"  // No style information
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szWriteBuffer = "<td valign=^top^ " + szClass + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<td valign=^top^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         //:ELSE 
      } 
      else
      { 
         //:szWriteBuffer = "<td valign=^top^ " + szClass + "style=^width:" + szWidth + "px;^>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<td valign=^top^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "style=^width:", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szWidth, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "px;^>", 1, 0, 10001 );
      } 

      //:END
      //://szWriteBuffer = "<td>"
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //://****************************************************************************

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

         //:szreCAPTCHAFlag = ""
         ZeidonStringCopy( szreCAPTCHAFlag, 1, 0, "", 1, 0, 2 );
         //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "reCAPTCHA"
         RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "reCAPTCHA", "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szreCAPTCHAFlag = "Y"
            ZeidonStringCopy( szreCAPTCHAFlag, 1, 0, "Y", 1, 0, 2 );
         } 

         //:END

         //:szToggleFlag = "" 
         ZeidonStringCopy( szToggleFlag, 1, 0, "", 1, 0, 2 );
         //:SET CURSOR FIRST vDialog.WebControlProperty WHERE vDialog.WebControlProperty.Name = "Show/Hide Toggle"
         RESULT = SetCursorFirstEntityByString( vDialog, "WebControlProperty", "Name", "Show/Hide Toggle", "" );
         //:IF RESULT >= zCURSOR_SET
         if ( RESULT >= zCURSOR_SET )
         { 
            //:szToggleFlag = "Y"
            ZeidonStringCopy( szToggleFlag, 1, 0, "Y", 1, 0, 2 );
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
         //:IF szNoPositioning = "S"
         if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
         { 
            //:szAbsoluteStyle = "" // No style information.
            ZeidonStringCopy( szAbsoluteStyle, 1, 0, "", 1, 0, 257 );
            //:ELSE 
         } 
         else
         { 
            //:CreateAbsolStyleString( vDialog, szAbsoluteStyle, lOffsetX, lOffsetY, "" )
            CreateAbsolStyleString( vDialog, szAbsoluteStyle, lOffsetX, lOffsetY, "" );
         } 

         //:END
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

         //:X_Size = vDialog.Control.SZDLG_X
         GetIntegerFromAttribute( &X_Size, vDialog, "Control", "SZDLG_X" );
         //:Y_Size = vDialog.Control.SZDLG_Y
         GetIntegerFromAttribute( &Y_Size, vDialog, "Control", "SZDLG_Y" );

         //:OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" )
         OrderEntityForView( vDialog, "CtrlCtrl", "PSDLG_Y A PSDLG_X A" );
         //:CreateViewFromView( vGroupParent, vDialog )
         CreateViewFromView( &vGroupParent, vDialog );

         //:// Create view for Group as a parent. This will be used in processing subcontrols to check for WebControlProperty.
         //:SetViewToSubobject( vDialog, "CtrlCtrl" )
         SetViewToSubobject( vDialog, "CtrlCtrl" );
         //:szIndentGroup = szIndent
         ZeidonStringCopy( szIndentGroup, 1, 0, szIndent, 1, 0, 101 );
         //:GenJSPJ_CrteGroupTable( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndent, lTableRowCnt, szNoPositioning, szRepeatGrpKey )
         GenJSPJ_CrteGroupTable( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndent, lTableRowCnt, szNoPositioning, szRepeatGrpKey );
         //:ResetViewFromSubobject( vDialog )
         ResetViewFromSubobject( vDialog );
         //:DropView( vGroupParent )
         DropView( vGroupParent );
         //:vGroupParent = 0
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
            //:GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
            //:                         lTableRowCnt, szNoPositioning, X_Size, Y_Size, szRepeatGrpKey )
            GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, X_Size, Y_Size, szRepeatGrpKey );
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
               //:GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
               //:                      lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY, szRepeatGrpKey )
               GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY, szRepeatGrpKey );
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
                  //:IF szNoPositioning = "Y"
                  if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
                  { 
                     //:zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" )
                     zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" );
                     //:ELSE
                  } 
                  else
                  { 
                     //:IF szNoPositioning = "S"
                     if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
                     { 
                        //:szAbsoluteStyle = "" // No style information.             
                        ZeidonStringCopy( szAbsoluteStyle, 1, 0, "", 1, 0, 257 );
                     } 

                     //:END
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
                  //:GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
                  //:                   lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY, szRepeatGrpKey )
                  GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY, szRepeatGrpKey );
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
                     //:IF szNoPositioning = "Y"
                     if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
                     { 
                        //:zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" )
                        zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" );
                     } 

                     //:END
                     //:IF szNoPositioning = "S"
                     if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
                     { 
                        //:szAbsoluteStyle = "" // No style information.             
                        ZeidonStringCopy( szAbsoluteStyle, 1, 0, "", 1, 0, 257 );
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
                     //:GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
                     //:                lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY, szRepeatGrpKey )
                     GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY, szRepeatGrpKey );
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
                     //:IF szNoPositioning = "Y"
                     if ( ZeidonStringCompare( szNoPositioning, 1, 0, "Y", 1, 0, 2 ) == 0 )
                     { 
                        //:zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" )
                        zAppendQuotedString( szAbsoluteStyle, "float:left;", "style=", "^" );
                        //:ELSE
                     } 
                     else
                     { 
                        //:IF szNoPositioning = "S"
                        if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
                        { 
                           //:szAbsoluteStyle = "" // No style information.             
                           ZeidonStringCopy( szAbsoluteStyle, 1, 0, "", 1, 0, 257 );
                        } 

                        //:END
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

                        //:// KJS 09/30/16 - Language Conversion.
                        //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
                        //:// So for now, I am always using, if the flag is set.
                        //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
                        if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
                        { 
                           //:// Seems like we need to check the text, and if the text has " then we shouldn't use the getLanguageText. Because one example we have
                           //:// is where the text is <img src="./images/admi..." border="0".
                           //:szText2 = vDialog.Control.Text
                           GetVariableFromAttribute( szText2, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
                           //:zSearchAndReplace( szText2, 1000, "\", "\\" )
                           zSearchAndReplace( szText2, 1000, "\\", "\\\\" );
                           //:szSrch = "\" + QUOTES 
                           ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
                           ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
                           //:zSearchAndReplace( szText2, 1000, QUOTES, szSrch )
                           zSearchAndReplace( szText2, 1000, QUOTES, szSrch );
                           //:szSrch = ""
                           ZeidonStringCopy( szSrch, 1, 0, "", 1, 0, 6 );
                           //:szText = "<%=LangConv.getLanguageText(^" + szText2 + "^)%>" 
                           ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
                           ZeidonStringConcat( szText, 1, 0, szText2, 1, 0, 501 );
                           ZeidonStringConcat( szText, 1, 0, "^)%>", 1, 0, 501 );
                           //:ELSE
                        } 
                        else
                        { 
                           //:szText = vDialog.Control.Text
                           GetVariableFromAttribute( szText, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
                        } 

                        //:END

                        //:szWriteBuffer = "<div>" + szText + "</div>"
                        ZeidonStringCopy( szWriteBuffer, 1, 0, "<div>", 1, 0, 10001 );
                        ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
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
                     //:GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup,
                     //:                lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY, szRepeatGrpKey )
                     GenJSPJ_CrteCtrlsRecurs( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndentGroup, lTableRowCnt, szNoPositioning, lOffsetX, lOffsetY, szRepeatGrpKey );
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
         //:GenJSPJ_CrteText( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndent, szCtrlTag,
         //:                  "", szNoPositioning, 0, 0, szRepeatGrpKey )
         GenJSPJ_CrteText( vDialog, vGroupParent, vDialogRoot, lFile, szWriteBuffer, szIndent, szCtrlTag, "", szNoPositioning, 0, 0, szRepeatGrpKey );
      } 

      //:END

      //:IF szControlType = "EditBox"  // EDITBOX
      if ( ZeidonStringCompare( szControlType, 1, 0, "EditBox", 1, 0, 51 ) == 0 )
      { 
         //:GenJSPJ_CrteEditBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag,
         //:                     "", "", szNoPositioning, 0, 0, szRepeatGrpKey )
         GenJSPJ_CrteEditBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, "", "", szNoPositioning, 0, 0, szRepeatGrpKey );
      } 

      //:END

      //:IF szControlType = "Calendar"  // CALENDAR
      if ( ZeidonStringCompare( szControlType, 1, 0, "Calendar", 1, 0, 51 ) == 0 )
      { 
         //:GenJSPJ_CrteCalendar( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag,
         //:                      "", "", szNoPositioning, 0, 0, szRepeatGrpKey )
         GenJSPJ_CrteCalendar( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, "", "", szNoPositioning, 0, 0, szRepeatGrpKey );
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
            //:szWriteBuffer = "   " + vDialog.CtrlMapView.Name + " = " +
            //:                "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
            GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
            GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      task.log( ).debug( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      task.log( ).debug( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
            //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
            GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         strRadioGroupValue = " +
            //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
            //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( );"
            GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strRadioGroupValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( );", 1, 0, 10001 );
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
            //:// KJS 09/30/16 - Language Conversion.
            //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
            //:// So for now, I am always using, if the flag is set.
            //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
            if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
            { 
               //:// Seems like we need to check the text, and if the text has " then we shouldn't use the getLanguageText. Because one example we have
               //:// is where the text is <img src="./images/admi..." border="0".
               //:szText2 = vDialog.Control.Text
               GetVariableFromAttribute( szText2, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
               //:zSearchAndReplace( szText2, 1000, "\", "\\" )
               zSearchAndReplace( szText2, 1000, "\\", "\\\\" );
               //:szSrch = "\" + QUOTES 
               ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
               ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
               //:zSearchAndReplace( szText2, 1000, QUOTES, szSrch )
               zSearchAndReplace( szText2, 1000, QUOTES, szSrch );
               //:szSrch = ""
               ZeidonStringCopy( szSrch, 1, 0, "", 1, 0, 6 );
               //:szText = "<%=LangConv.getLanguageText(^" + szText2 + "^)%>" 
               ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
               ZeidonStringConcat( szText, 1, 0, szText2, 1, 0, 501 );
               ZeidonStringConcat( szText, 1, 0, "^)%>", 1, 0, 501 );
               //:ELSE
            } 
            else
            { 
               //:szText = vDialog.Control.Text
               GetVariableFromAttribute( szText, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
            } 

            //:END
            //:szWriteBuffer = "<div>" + szText + "</div>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<div>", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
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
         //:GenJSPJ_CrteCtrlsRadio( vDialog, lFile, szWriteBuffer, szIndent,
         //:                        szCtrlTag, szNoPositioning, 0, 0, szRepeatGrpKey )
         GenJSPJ_CrteCtrlsRadio( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, szNoPositioning, 0, 0, szRepeatGrpKey );
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
         //:GenJSPJ_CrteCheckBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag,
         //:                      "", "", szNoPositioning, 0, 0, szRepeatGrpKey )
         GenJSPJ_CrteCheckBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, "", "", szNoPositioning, 0, 0, szRepeatGrpKey );
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
         ZeidonStringCopy( szText, 1, 0, "", 1, 0, 501 );
         //:// KJS 09/30/16 - Language Conversion.
         //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
         //:// So for now, I am always using, if the flag is set.
         //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
         if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
         { 
            //:// Seems like we need to check the text, and if the text has " then we shouldn't use the getLanguageText. Because one example we have
            //:// is where the text is <img src="./images/admi..." border="0".
            //:szText2 = vDialog.Control.Text
            GetVariableFromAttribute( szText2, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
            //:zSearchAndReplace( szText2, 1000, "\", "\\" )
            zSearchAndReplace( szText2, 1000, "\\", "\\\\" );
            //:szSrch = "\" + QUOTES 
            ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
            ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
            //:zSearchAndReplace( szText2, 1000, QUOTES, szSrch )
            zSearchAndReplace( szText2, 1000, QUOTES, szSrch );
            //:szSrch = ""
            ZeidonStringCopy( szSrch, 1, 0, "", 1, 0, 6 );
            //:szText = "<%=LangConv.getLanguageText(^" + szText2 + "^)%>" 
            ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
            ZeidonStringConcat( szText, 1, 0, szText2, 1, 0, 501 );
            ZeidonStringConcat( szText, 1, 0, "^)%>", 1, 0, 501 );
            //:ELSE
         } 
         else
         { 
            //:szText = vDialog.Control.Text
            GetVariableFromAttribute( szText, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
         } 

         //:END

         //://szText = vDialog.Control.Text
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
         //:IF szRepeatGrpKey = ""
         if ( ZeidonStringCompare( szRepeatGrpKey, 1, 0, "", 1, 0, 101 ) == 0 )
         { 
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
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = szWriteBuffer + "value=^" + szText + "^ onclick=^" +
            //:                szActionName + "( '" + szCtrlTag + szRepeatGrpKey + "' )^ " + " " + szStyle + ">" + szText + "</button>"
            ZeidonStringConcat( szWriteBuffer, 1, 0, "value=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ onclick=^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szActionName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "( '", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "' )^ ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "</button>", 1, 0, 10001 );
         } 

         //:END

         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
      } 

      //:END  //End of PushBtn

      //:IF szControlType = "ComboBox"  // COMBOBOX
      if ( ZeidonStringCompare( szControlType, 1, 0, "ComboBox", 1, 0, 51 ) == 0 )
      { 
         //:GenJSPJ_CrteComboBox( vDialog, lFile, szWriteBuffer, szIndent,
         //:                      szCtrlTag, "", szNoPositioning, 0, 0, szRepeatGrpKey )
         GenJSPJ_CrteComboBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, "", szNoPositioning, 0, 0, szRepeatGrpKey );
      } 

      //:END

      //:IF szControlType = "Bitmap" OR szControlType = "BitmapBtn"  // BITMAP / JPG
      if ( ZeidonStringCompare( szControlType, 1, 0, "Bitmap", 1, 0, 51 ) == 0 || ZeidonStringCompare( szControlType, 1, 0, "BitmapBtn", 1, 0, 51 ) == 0 )
      { 
         //:GenJSPJ_CrteJPG( vDialog, lFile, szWriteBuffer, szIndent,
         //:                 szCtrlTag, szNoPositioning, 0, 0 )
         GenJSPJ_CrteJPG( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, szNoPositioning, 0, 0 );
      } 

      //:END

      //:IF szControlType = "ListBox"  // LISTBOX
      if ( ZeidonStringCompare( szControlType, 1, 0, "ListBox", 1, 0, 51 ) == 0 )
      { 
         //://IF jquery
         //://ELSE
         //:   GenJSPJ_CrteListBox( vDialog, lFile, szWriteBuffer, szIndent,
         //:                        szCtrlTag, szNoPositioning, 0, 0 )
         GenJSPJ_CrteListBox( vDialog, lFile, szWriteBuffer, szIndent, szCtrlTag, szNoPositioning, 0, 0 );
      } 

      //:   //END                              
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
            //:szWriteBuffer = "   strErrorMapValue = VmlOperation.CheckError( ^" + szCtrlTag + "^, strError );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = VmlOperation.CheckError( ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, strError );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   if ( !StringUtils.isBlank( strErrorMapValue ) )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( !StringUtils.isBlank( strErrorMapValue ) )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "   {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( StringUtils.equals( strErrorFlag, ^Y^ ) )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( StringUtils.equals( strErrorFlag, ^Y^ ) )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         strErrorColor = ^color:red;^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorColor = ^color:red;^;", 1, 0, 10001 );
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
            //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name + " = " + "task.getViewByName( ^" +
            //:                vDialog.CtrlMapView.Name + "^ );"
            GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_14, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
            GetVariableFromAttribute( szTempString_15, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( VmlOperation.isValid( ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_15, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         task.log( ).debug( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         task.log( ).debug( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
            //:szWriteBuffer = "         nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
            GetVariableFromAttribute( szTempString_16, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_16, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_17, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_17, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
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
            lTempInteger_9 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
            if ( lTempInteger_9 == 0 )
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

            //:IF vDialog.CtrlMapER_Domain.MaxStringLth > 254
            if ( CompareAttributeToInteger( vDialog, "CtrlMapER_Domain", "MaxStringLth", 254 ) > 0 )
            { 
               //:lMaxStringLength = vDialog.CtrlMapER_Domain.MaxStringLth
               GetIntegerFromAttribute( &lMaxStringLength, vDialog, "CtrlMapER_Domain", "MaxStringLth" );
               //:szMaxStringLength = lMaxStringLength
               ZeidonStringConvertFromNumber( szMaxStringLength, 1, 0, 10, lMaxStringLength, (ZDecimal) 0.0, "I" );
               //:ELSE
            } 
            else
            { 
               //:szMaxStringLength = "254"
               ZeidonStringCopy( szMaxStringLength, 1, 0, "254", 1, 0, 11 );
            } 

            //:END

            //:szWriteBuffer = "            strErrorMapValue = " +
            //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
            //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
            //:                szContextName + "^ );"
            GetVariableFromAttribute( szTempString_18, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            strErrorMapValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_18, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_19, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_19, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_20, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_20, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:IF vDialog.Control.WebCtrlType = "escapeHTML"
            if ( CompareAttributeToString( vDialog, "Control", "WebCtrlType", "escapeHTML" ) == 0 )
            { 
               //:szWriteBuffer = "               task.log().debug( ^" + szCtrlTag + " prior to unescape: ^ + strErrorMapValue );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "               task.log().debug( ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " prior to unescape: ^ + strErrorMapValue );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "               strErrorMapValue = StringEscapeUtils.unescapeHtml4( strErrorMapValue );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = StringEscapeUtils.unescapeHtml4( strErrorMapValue );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "               task.log().debug( ^" + szCtrlTag + " after unescape: ^ + strErrorMapValue );"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "               task.log().debug( ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " after unescape: ^ + strErrorMapValue );", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            } 

            //:END

            //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
            //:szWriteBuffer = "            if ( strErrorMapValue == null )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( strErrorMapValue == null )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               strErrorMapValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:szWriteBuffer = "            task.log( ).debug( ^" + vDialog.CtrlMapRelatedEntity.Name + "." +
            //:                vDialog.CtrlMapER_Attribute.Name + ": ^ + strErrorMapValue );"
            GetVariableFromAttribute( szTempString_21, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).debug( ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_21, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_22, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_22, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + strErrorMapValue );", 1, 0, 10001 );
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
            //:szWriteBuffer = "            task.log( ).debug( ^Entity does not exist for " + szCtrlTag + ": ^ + ^" +
            //:                vDialog.CtrlMapView.Name +
            //:                "." + vDialog.CtrlMapRelatedEntity.Name + "^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).debug( ^Entity does not exist for ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_23, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_23, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_24, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_24, 1, 0, 10001 );
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
               //:szWriteBuffer = "      if ( strErrorMapValue == ^^ )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strErrorMapValue == ^^ )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "         strErrorMapValue = ^" + vDialog.Control.Text + "^;"
               GetVariableFromAttribute( szTempString_25, 0, 'S', 255, vDialog, "Control", "Text", "", 0 );
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = ^", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_25, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, "^;", 1, 0, 10001 );
            } 

            //:END

            //:// This doesn't work, but something like "escapeHTML" may be necessary to remove special characters ... dks 2012.04.25
            //:// strErrorMapValue = strErrorMapValue.replace("/&/g", "&amp;").replace("/>/g", "&gt;").replace("/</g", "&lt;").replace("/\"/g", "&quot;").replace("/%/g", "&#037;");

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
               //:zAppendQuotedString( szStyle, "border:solid;border-width:4px;border-style:groove;", "style=", "^" )
               zAppendQuotedString( szStyle, "border:solid;border-width:4px;border-style:groove;", "style=", "^" );
               //:ELSE
            } 
            else
            { 
               //:zAppendQuotedString( szStyle, "border:solid;border-width:2px;border-style:groove;", "style=", "^" )
               zAppendQuotedString( szStyle, "border:solid;border-width:2px;border-style:groove;", "style=", "^" );
            } 

            //:END
            //:// zAppendQuotedString( szStyle, szAbsoluteStyle, "style=", "^" ) already in

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

            //:IF vDialog.Control.WebCtrlType = "wysiwygEditor" OR szTinyMCEFlag = "Y"
            if ( CompareAttributeToString( vDialog, "Control", "WebCtrlType", "wysiwygEditor" ) == 0 || ZeidonStringCompare( szTinyMCEFlag, 1, 0, "Y", 1, 0, 2 ) == 0 )
            { 

               //:// CreateTabIndexString( vDialog, szTabIndex )
               //:// CreateAbsolStyleString( vDialog, szAbsoluteStyle, lOffsetX, lOffsetY, "" )
               //:// szAbsoluteStyle = szAbsoluteStyle + szTabIndex

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
                  //:szWriteBuffer = "<div style=^background-color:#eee;border:1px solid #041;width:" + szSize + "px;height:" + szHeight + "px;position:absolute;left:0px;top:0px;overflow:auto;^>"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<div style=^background-color:#eee;border:1px solid #041;width:", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szSize, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "px;height:", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHeight, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "px;position:absolute;left:0px;top:0px;overflow:auto;^>", 1, 0, 10001 );
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
                  //:szWriteBuffer = "<textarea" + szHTMLCtrlID +
                  //:                "class=^" + szClass + "^ " + szTitleHTML + szStyle + ">" +
                  //:             // "^ rows="15" cols="80" style="width: 80%">" +
                  //:                "<%=strErrorMapValue%></textarea>"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<textarea", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
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
               //:szClass = vDialog.Control.CSS_Class
               GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
               //:CreateTabIndexString( vDialog, szTabIndex )
               CreateTabIndexString( vDialog, szTabIndex );
               //:lTemp = vDialog.Control.Subtype
               GetIntegerFromAttribute( &lTemp, vDialog, "Control", "Subtype" );
               //:lTemp = IsFlagSequenceSet( lTemp, zCONTROL_DISABLED )
               lTemp = IsFlagSequenceSet( lTemp, zCONTROL_DISABLED );
               //:IF lTemp = 0
               if ( lTemp == 0 )
               { 
                  //:szWriteBuffer = "<textarea" + szHTMLCtrlID + szTitleHTML +
                  //:                "class=^" + szClass + "^ " + szStyle + szTabIndex + " wrap=^wrap^>" +
                  //:                "<%=strErrorMapValue%></textarea>"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<textarea", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, " wrap=^wrap^>", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "<%=strErrorMapValue%></textarea>", 1, 0, 10001 );
                  //:ELSE
               } 
               else
               { 
                  //:zAppendQuotedString( szStyle, "text-overflow:hidden;background-color:lightgray;", "style=", "^" )
                  zAppendQuotedString( szStyle, "text-overflow:hidden;background-color:lightgray;", "style=", "^" );
                  //:szWriteBuffer = "<div" + szHTMLCtrlID + szTitleHTML +
                  //:                "class=^" + szClass + "^ " + szStyle + szTabIndex + " wrap=^wrap^>" +
                  //:                "<%=strErrorMapValue%></div>"
                  ZeidonStringCopy( szWriteBuffer, 1, 0, "<div", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szHTMLCtrlID, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "class=^", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, " wrap=^wrap^>", 1, 0, 10001 );
                  ZeidonStringConcat( szWriteBuffer, 1, 0, "<%=strErrorMapValue%></div>", 1, 0, 10001 );
               } 

               //:END
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

   //:// If the previous row didn't have as many controls as there are
   //:// table columns, then we need to create a blank column
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
//:GenJSPJ_CrteCtrlsRadio( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                       INTEGER          lFile,
//:                       STRING ( 10000 ) szWriteBuffer,
//:                       STRING ( 50 )    szIndent,
//:                       STRING ( 32 )    szRadioGroupName,
//:                       STRING ( 1 )     szNoPositioning,
//:                       INTEGER          lOffsetX,
//:                       INTEGER          lOffsetY,
//:                       STRING ( 100 )   szRepeatGrpKey )

//:   VIEW vDialogRoot BASED ON LOD TZWDLGSO
zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteCtrlsRadio( zVIEW     vDialog,
                        zLONG     lFile,
                        zPCHAR    szWriteBuffer,
                        zPCHAR    szIndent,
                        zPCHAR    szRadioGroupName,
                        zPCHAR    szNoPositioning,
                        zLONG     lOffsetX,
                        zLONG     lOffsetY,
                        zPCHAR    szRepeatGrpKey )
{
   zVIEW     vDialogRoot = 0; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitle
   zCHAR     szTitle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szCtrlTag
   zCHAR     szCtrlTag[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szTitleHTML
   zCHAR     szTitleHTML[ 257 ] = { 0 }; 
   //:STRING ( 500 ) szText
   zCHAR     szText[ 501 ] = { 0 }; 
   //:STRING ( 500 ) szText2
   zCHAR     szText2[ 501 ] = { 0 }; 
   //:STRING ( 5 )   szSrch
   zCHAR     szSrch[ 6 ] = { 0 }; 
   //:STRING ( 100 ) szDisabled
   zCHAR     szDisabled[ 101 ] = { 0 }; 
   //:STRING ( 16 )  szPosition
   zCHAR     szPosition[ 17 ] = { 0 }; 
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


   //:GetViewByName( vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK )   
   GetViewByName( &vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK );

   //:// KJS 09/02/13 - Adding table around radio buttons. This was already done for C jsps...
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
      //:szWriteBuffer = "   if ( StringUtils.equals( strRadioGroupValue, ^" +
      //:                         vDialog.Control.RadioOrCheckboxValue + "^ ) )"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 51, vDialog, "Control", "RadioOrCheckboxValue", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( StringUtils.equals( strRadioGroupValue, ^", 1, 0, 10001 );
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
      //:IF szNoPositioning = ""
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

      //:IF szNoPositioning = "S"
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = "" // No style information
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
      } 

      //:END

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
         //:szWriteBuffer = "      <td style=^width:15px;border:0px;^><input type=^radio^ name=^" + szRadioGroupName + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey +
         //:                "^ value=^" + vDialog.Control.RadioOrCheckboxValue +
         //:                "^ <%=strErrorMapValue%> " + szStyle + szDisabled + " onclick=^" + szActionName + "( )^  ></td>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td style=^width:15px;border:0px;^><input type=^radio^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRadioGroupName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
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
         //:szWriteBuffer = "      <td style=^width:15px;border:0px;^><input type=^radio^ name=^" + szRadioGroupName + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey +
         //:                "^ value=^" + vDialog.Control.RadioOrCheckboxValue +
         //:                "^ <%=strErrorMapValue%> " + szStyle + szDisabled + " ></td>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td style=^width:15px;border:0px;^><input type=^radio^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRadioGroupName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
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
         //:IF szNoPositioning = "S"
         if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
         { 
            //:szStyle = "" // No style information.
            ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
            //:ELSE
         } 
         else
         { 
            //:CreateAbsolStyleString( vDialog, szStyle, 30 + lOffsetX, lOffsetY, "" )
            CreateAbsolStyleString( vDialog, szStyle, 30 + lOffsetX, lOffsetY, "" );
         } 

         //:END
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

      //:// KJS 09/30/16 - Language Conversion.
      //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
      //:// So for now, I am always using, if the flag is set.
      //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
      if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
      { 
         //:szText2 = vDialog.Control.Text
         GetVariableFromAttribute( szText2, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
         //:zSearchAndReplace( szText2, 1000, "\", "\\" )
         zSearchAndReplace( szText2, 1000, "\\", "\\\\" );
         //:szSrch = "\" + QUOTES 
         ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
         ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
         //:zSearchAndReplace( szText2, 1000, QUOTES, szSrch )
         zSearchAndReplace( szText2, 1000, QUOTES, szSrch );
         //:szSrch = ""
         ZeidonStringCopy( szSrch, 1, 0, "", 1, 0, 6 );
         //:szText = "<%=LangConv.getLanguageText(^" + szText2 + "^)%>" 
         ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
         ZeidonStringConcat( szText, 1, 0, szText2, 1, 0, 501 );
         ZeidonStringConcat( szText, 1, 0, "^)%>", 1, 0, 501 );
         //:ELSE
      } 
      else
      { 
         //:szText = vDialog.Control.Text
         GetVariableFromAttribute( szText, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
      } 

      //:END

      //:szClass = vDialog.Control.CSS_Class
      GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );
      //:IF szClass = ""
      if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
      { 
         //:szWriteBuffer = "      <td nowrap style=^border:0px;^><span " + szTitleHTML + szStyle + ">" + szText + "</span></td>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td nowrap style=^border:0px;^><span ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "</span></td>", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "      <td nowrap style=^border:0px;^><span class=^" + szClass + "^ " + szTitleHTML + szStyle + ">" + szText + "</span></td>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      <td nowrap style=^border:0px;^><span class=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
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
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSPJ_CrteComboBox( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY,
//:                     STRING ( 100 )   szRepeatGrpKey )

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
GenJSPJ_CrteComboBox( zVIEW     vDialog,
                      zLONG     lFile,
                      zPCHAR    szWriteBuffer,
                      zPCHAR    szIndent,
                      zPCHAR    szCtrlTag,
                      zPCHAR    szTableRowFlag,
                      zPCHAR    szNoPositioning,
                      zLONG     lOffsetX,
                      zLONG     lOffsetY,
                      zPCHAR    szRepeatGrpKey )
{
   zVIEW     vList = 0; 
   //:VIEW vEntity BASED ON LOD TZWDLGSO  // identifies entity mapping for list entries
   zVIEW     vEntity = 0; 
   //:VIEW vScope  BASED ON LOD TZWDLGSO  // identifies scoping entity for list entries
   zVIEW     vScope = 0; 
   //:VIEW vDialogRoot BASED ON LOD TZWDLGSO
   zVIEW     vDialogRoot = 0; 
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
   //:STRING ( 100 ) szCtrlTagRG
   zCHAR     szCtrlTagRG[ 101 ] = { 0 }; 
   //:STRING ( 100 ) szInListCtrlTag
   zCHAR     szInListCtrlTag[ 101 ] = { 0 }; 
   //:STRING ( 50 )  szKeyPressCode
   zCHAR     szKeyPressCode[ 51 ] = { 0 }; 
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
   zCHAR     szTempString_0[ 255 ]; 
   zLONG     lTempInteger_0; 
   zLONG     lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zSHORT    lTempInteger_3; 
   zSHORT    lTempInteger_4; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zSHORT    lTempInteger_5; 
   zSHORT    lTempInteger_6; 
   zCHAR     szTempString_4[ 33 ]; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 
   zSHORT    RESULT; 
   zSHORT    lTempInteger_7; 
   zSHORT    lTempInteger_8; 
   zCHAR     szTempString_12[ 33 ]; 
   zCHAR     szTempString_13[ 33 ]; 
   zCHAR     szTempString_14[ 33 ]; 
   zSHORT    lTempInteger_9; 
   zCHAR     szTempString_15[ 33 ]; 
   zCHAR     szTempString_16[ 33 ]; 
   zCHAR     szTempString_17[ 33 ]; 
   zCHAR     szTempString_18[ 33 ]; 
   zCHAR     szTempString_19[ 33 ]; 
   zSHORT    lTempInteger_10; 
   zCHAR     szTempString_20[ 33 ]; 
   zCHAR     szTempString_21[ 33 ]; 
   zCHAR     szTempString_22[ 33 ]; 
   zSHORT    lTempInteger_11; 
   zSHORT    lTempInteger_12; 
   zCHAR     szTempString_23[ 33 ]; 
   zCHAR     szTempString_24[ 33 ]; 
   zSHORT    lTempInteger_13; 
   zSHORT    lTempInteger_14; 
   zCHAR     szTempString_25[ 33 ]; 
   zCHAR     szTempString_26[ 33 ]; 


   //:szStyle = "width:" + szWidth + "px; height:" + szHeight + "px;"
   ZeidonStringCopy( szStyle, 1, 0, "width:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px; height:", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
   //:szClass = ""
   ZeidonStringCopy( szClass, 1, 0, "", 1, 0, 257 );
   //:IF vDialog.Control.CSS_Class != ""
   if ( CompareAttributeToString( vDialog, "Control", "CSS_Class", "" ) != 0 )
   { 
      //:szClass = "class=^" + vDialog.Control.CSS_Class + "^"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 255, vDialog, "Control", "CSS_Class", "", 0 );
      ZeidonStringCopy( szClass, 1, 0, "class=^", 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, szTempString_0, 1, 0, 257 );
      ZeidonStringConcat( szClass, 1, 0, "^", 1, 0, 257 );
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
   //:IF szNoPositioning = ""
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

   //:IF szNoPositioning = "S"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
   { 
      //:szStyle = "" // No style information
      ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
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

      //://szWriteBuffer = "<input name=^h" + szCtrlTag + szRepeatGrpKey + "^ id=^h" + szCtrlTag + szRepeatGrpKey + "^ type=^hidden^ value=^0^ >"
      //://WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )

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

      //:// If there is a Default button for the window, we must add some characters
      //:// to the end of the input statement.
      //:szKeyPressCode = ""
      ZeidonStringCopy( szKeyPressCode, 1, 0, "", 1, 0, 51 );
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
         //:szKeyPressCode = szKeyPressCode + " onkeypress=^return _OnEnter( event )^"
         ZeidonStringConcat( szKeyPressCode, 1, 0, " onkeypress=^return _OnEnter( event )^", 1, 0, 51 );
      } 

      //:END      

      //:CreateDisabledString( vDialog, szDisabled )
      CreateDisabledString( vDialog, szDisabled );
      //:IF szRepeatGrpKey = ""
      if ( ZeidonStringCompare( szRepeatGrpKey, 1, 0, "", 1, 0, 101 ) == 0 )
      { 
         //:szWriteBuffer = "<select " + szClass + " name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ size=^1^ " +
         //:                szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" + szCtrlTag + szSelectFunction + "( )^ " + szKeyPressCode + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<select ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^1^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectAction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectFunction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( )^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szKeyPressCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szCtrlTagRG = szRepeatGrpKey
         ZeidonStringCopy( szCtrlTagRG, 1, 0, szRepeatGrpKey, 1, 0, 101 );
         //://TraceLineS("***** szRepeatGrpKey -----> ", szRepeatGrpKey )
         //:zSearchAndReplace( szCtrlTagRG, 100, "::", "" )
         zSearchAndReplace( szCtrlTagRG, 100, "::", "" );
         //://TraceLineS("***** szCtrlTagRG    -----> ", szCtrlTagRG )
         //:szWriteBuffer = "<select " + szClass + " name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ size=^1^ " +
         //:                szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" + szCtrlTag + szSelectFunction + "( 'h" + szCtrlTag  + szRepeatGrpKey + "', this, '" + 
         //:                szCtrlTagRG + "' )^ " + szKeyPressCode + ">"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "<select ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ size=^1^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectAction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szSelectFunction, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "( 'h", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "', this, '", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTagRG, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "' )^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szKeyPressCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      } 

      //:                   //szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" + szCtrlTag + szSelectFunction + "( 'h" + szCtrlTag  + szRepeatGrpKey + ', this, <%=strEntityKeyRG%> )^" + ">"
      //:END

      //:/*
      //:IF szClass = ""
      //:   szWriteBuffer = "<select name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ size=^1^ " + szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" +
      //:                   szCtrlTag + szSelectFunction + "( )^" + ">"
      //:ELSE
      //:   szWriteBuffer = "<select class=^" + szClass + "^ name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ size=^1^ " +
      //:                   szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" + szCtrlTag + szSelectFunction + "( )^" + ">"
      //:END
      //:*/      
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
         //:// KJS 10/22/14 - If the value from the database is not part of the domain anymore, we will put that option in but
         //:// we will set it as disabled.
         //:szInListCtrlTag = "inList" + szCtrlTag
         ZeidonStringCopy( szInListCtrlTag, 1, 0, "inList", 1, 0, 101 );
         ZeidonStringConcat( szInListCtrlTag, 1, 0, szCtrlTag, 1, 0, 101 );

         //:szWriteBuffer = "   boolean " + szInListCtrlTag + " = false;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   boolean ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szInListCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " = false;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

         //:szWriteBuffer = "   " + vDialog.CtrlMapView.Name + " = " +
         //:             "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
         GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) )"
         GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " ) )", 1, 0, 10001 );
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

            //:szWriteBuffer = "      List<TableEntry> list = JspWebUtils.getTableDomainValues( " + vDialog.CtrlMapView.Name + " , ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^, ^" + vDialog.CtrlMapER_Attribute.Name + "^, ^" + szContextName + "^ );"
            GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      List<TableEntry> list = JspWebUtils.getTableDomainValues( ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " , ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^, ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:         vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
            GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( nRC >= 0 )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:// Get the current value of the combo box.
            //:szWriteBuffer = "         strComboCurrentValue = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:         vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
            //:         vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^^ );"
            GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strComboCurrentValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^^ );", 1, 0, 10001 );
            //:         // KJS 10/22/14 - Right now we are not adding the context name, we only want the default, which
            //:         // I am currently assuming has ALL the values (old and new) of this domain. When we get DGs domain fix
            //:         // I think we need to put this back!!!!!!!
            //:         //vDialog.CtrlMapER_Attribute.Name + "^, ^" + szContextName + "^ );"
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
            //:szWriteBuffer = "         if ( strComboCurrentValue == null )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strComboCurrentValue == null )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            strComboCurrentValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            strComboCurrentValue = ^^;", 1, 0, 10001 );
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
            //:szWriteBuffer = "         strComboCurrentValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strComboCurrentValue = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:IF vDialog.CtrlMapER_Attribute.NotNull != "Y"
            if ( CompareAttributeToString( vDialog, "CtrlMapER_Attribute", "NotNull", "Y" ) != 0 )
            { 
               //:// Generate code when attribute is NOT required.
               //:szWriteBuffer = "      // Code for NOT required attribute, which makes sure a blank entry exists."
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      // Code for NOT required attribute, which makes sure a blank entry exists.", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      if ( strComboCurrentValue == ^^ )"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( strComboCurrentValue == ^^ )", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
               //:szWriteBuffer = "      {"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

               //:szWriteBuffer = "         " + szInListCtrlTag + " = true;"
               ZeidonStringCopy( szWriteBuffer, 1, 0, "         ", 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, szInListCtrlTag, 1, 0, 10001 );
               ZeidonStringConcat( szWriteBuffer, 1, 0, " = true;", 1, 0, 10001 );
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
               //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
               WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            } 

            //:END

            //:szWriteBuffer = "      for ( TableEntry entry : list )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      for ( TableEntry entry : list )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         String internalValue = entry.getInternalValue( );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         String internalValue = entry.getInternalValue( );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         String externalValue = entry.getExternalValue( );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         String externalValue = entry.getExternalValue( );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         // Perhaps getInternalValue and getExternalValue should return an empty string, "
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         // Perhaps getInternalValue and getExternalValue should return an empty string, ", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         // but currently it returns null.  Set to empty string. "
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         // but currently it returns null.  Set to empty string. ", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         if ( externalValue == null )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( externalValue == null )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            internalValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            internalValue = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            externalValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            externalValue = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

            //:// The following if statement eliminates a null value, which would be the second null in the combo box.
            //:szWriteBuffer = "         if ( !StringUtils.isBlank( externalValue ) )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( !StringUtils.isBlank( externalValue ) )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            if ( StringUtils.equals( strComboCurrentValue, externalValue ) )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( StringUtils.equals( strComboCurrentValue, externalValue ) )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:szWriteBuffer = "               " + szInListCtrlTag + " = true;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szInListCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " = true;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:szWriteBuffer = "%>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               <option selected=^selected^ value=^<%=externalValue%>^><%=externalValue%></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               <option selected=^selected^ value=^<%=externalValue%>^><%=externalValue%></option>", 1, 0, 10001 );
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
            //:szWriteBuffer = "               <option value=^<%=externalValue%>^><%=externalValue%></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               <option value=^<%=externalValue%>^><%=externalValue%></option>", 1, 0, 10001 );
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
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      }  // for ( TableEntry entry"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      }  // for ( TableEntry entry", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:// KJS 10/22/14 - Add this value as disabled.
            //:szWriteBuffer = "      // The value from the database isn't in the domain, add it to the list as disabled."
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      // The value from the database isn't in the domain, add it to the list as disabled.", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( !" + szInListCtrlTag + " )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( !", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szInListCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      { "
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      { ", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "%>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "%>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:szWriteBuffer = "         <option disabled selected=^selected^ value=^<%=strComboCurrentValue%>^><%=strComboCurrentValue%></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         <option disabled selected=^selected^ value=^<%=strComboCurrentValue%>^><%=strComboCurrentValue%></option>", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "<%"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:szWriteBuffer = "      }  "
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      }  ", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         } 

         //:   
         //:   
         //:END
      } 

      //:END

      //:szWriteBuffer = "   }  // if view != null"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }  // if view != null", 1, 0, 10001 );
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
      //:szWriteBuffer = "<input name=^h" + szCtrlTag + szRepeatGrpKey + "^ id=^h" + szCtrlTag + szRepeatGrpKey + "^ type=^hidden^ value=^<%=strComboCurrentValue%>^ >"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input name=^h", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^h", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ type=^hidden^ value=^<%=strComboCurrentValue%>^ >", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:ELSE  
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

      //:szWriteBuffer = "<select " + szClass + " name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ size=^1^" +
      //:                szTitleHTML + szStyle + szDisabled + szSelectAction + "=^" + szCtrlTag + szSelectFunction + "( )^" + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<select ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
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
         //:szWriteBuffer = "   " + vList.CtrlMapView.Name + " = " +
         //:                "task.getViewByName( ^" + vList.CtrlMapView.Name + "^ );"
         GetVariableFromAttribute( szTempString_12, 0, 'S', 33, vList, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vList, "CtrlMapView", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "   if ( VmlOperation.isValid( " + vList.CtrlMapView.Name + " ) )"
         GetVariableFromAttribute( szTempString_14, 0, 'S', 33, vList, "CtrlMapView", "Name", "", 0 );
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_14, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " ) )", 1, 0, 10001 );
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
         //:szWriteBuffer = "      View v" + szCtrlTag + ";"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      View v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ";", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

         //:// If mapping is specified, set up the value to be used in selecting
         //:// the correct entry.
         //:IF vDialog.CtrlMapLOD_Attribute EXISTS
         lTempInteger_9 = CheckExistenceOfEntity( vDialog, "CtrlMapLOD_Attribute" );
         if ( lTempInteger_9 == 0 )
         { 
            //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name + " = " +
            //:                "task.getViewByName( ^" + vDialog.CtrlMapView.Name +
            //:                "^ );"
            GetVariableFromAttribute( szTempString_15, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_15, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_16, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_16, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) )"
            GetVariableFromAttribute( szTempString_17, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( VmlOperation.isValid( ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_17, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " ) )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      {"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      {", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
            GetVariableFromAttribute( szTempString_18, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_18, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_19, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_19, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
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
            //:szWriteBuffer = "            strComboCurrentValue = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
            //:         vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
            //:         vDialog.CtrlMapER_Attribute.Name + "^ ).getString( ^" + szContextName + "^ );"
            GetVariableFromAttribute( szTempString_20, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            strComboCurrentValue = ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_20, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_21, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_21, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_22, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_22, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
            //:szWriteBuffer = "            if ( strComboCurrentValue == null )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( strComboCurrentValue == null )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "               strComboCurrentValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "               strComboCurrentValue = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "         }"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         }", 1, 0, 10001 );
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
               //:szScopingEntityName = "^" + vScope.CtrlMapLOD_Entity.Name + "^"
               GetVariableFromAttribute( szTempString_23, 0, 'S', 33, vScope, "CtrlMapLOD_Entity", "Name", "", 0 );
               ZeidonStringCopy( szScopingEntityName, 1, 0, "^", 1, 0, 33 );
               ZeidonStringConcat( szScopingEntityName, 1, 0, szTempString_23, 1, 0, 33 );
               ZeidonStringConcat( szScopingEntityName, 1, 0, "^", 1, 0, 33 );
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

         //:szWriteBuffer = "      v" + szCtrlTag + " = " + vList.CtrlMapView.Name + ".newView( );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_24, 0, 'S', 33, vList, "CtrlMapView", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_24, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".newView( );", 1, 0, 10001 );
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
            //:szWriteBuffer = "      // For Auto Include, always add a null entry to the combo box."
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      // For Auto Include, always add a null entry to the combo box.", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      ComboCount++;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      ComboCount++;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "      if ( StringUtils.isBlank( strComboCurrentValue ) )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( StringUtils.isBlank( strComboCurrentValue ) )", 1, 0, 10001 );
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
            //:szWriteBuffer = "         <option selected=^selected^></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         <option selected=^selected^></option>", 1, 0, 10001 );
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
            //:szWriteBuffer = "         <option></option>"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         <option></option>", 1, 0, 10001 );
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
            //:szWriteBuffer = "      csrRC = v" + szCtrlTag + ".cursor( ^" +
            //:                             szListEntityName + "^ ).setFirst( " + szScopingEntityName + " );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      csrRC = v", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setFirst( ", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szScopingEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
            //:ELSE
         } 
         else
         { 
            //:szWriteBuffer = "      csrRC = v" + szCtrlTag + ".cursor( ^" + szListEntityName + "^ ).setFirstWithinOi( );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "      csrRC = v", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setFirstWithinOi( );", 1, 0, 10001 );
         } 

         //:END

         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:szWriteBuffer = "      while ( csrRC.isSet() )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "      while ( csrRC.isSet() )", 1, 0, 10001 );
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

            //:szWriteBuffer = "         strErrorMapValue = v" + szCtrlTag + ".cursor( ^" +
            //:                vList.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
            //:                vList.CtrlMapER_Attribute.Name + "^ ).getString( ^" +
            //:                szContextName + "^ );"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorMapValue = v", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_25, 0, 'S', 33, vList, "CtrlMapRelatedEntity", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_25, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
            GetVariableFromAttribute( szTempString_26, 0, 'S', 33, vList, "CtrlMapER_Attribute", "Name", "", 0 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_26, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ^", 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
            ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

            //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
            //:szWriteBuffer = "         if ( strErrorMapValue == null )"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( strErrorMapValue == null )", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
            //:szWriteBuffer = "            strErrorMapValue = ^^;"
            ZeidonStringCopy( szWriteBuffer, 1, 0, "            strErrorMapValue = ^^;", 1, 0, 10001 );
            //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
            WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
         } 


         //:END

         //:// KJS 05/20/14 - There were some issues for auto include when the "list view" already had a blank entry, then
         //:// two blank entries were in the list and this caused errors. For auto include check if one of these entries is
         //:// blank, don't add it if it is.
         //:/*
         //:IF vDialog.Control.Subtype >= 20480 AND vDialog.Control.Subtype <= 21252   // IF Auto Include
         //:   szWriteBuffer = "      // For Auto Include, we have already created a blank entry for the combobox, check to make"
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         //:   szWriteBuffer = "         // we don't add another blank entry. That will cause errors. "
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         //:   szWriteBuffer = "         if ( !StringUtils.isBlank( strErrorMapValue ) )"
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         //:   szWriteBuffer = "         {"
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         //:END
         //: */
         //:szWriteBuffer = "         if ( StringUtils.equals( strComboCurrentValue, strErrorMapValue ) )"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         if ( StringUtils.equals( strComboCurrentValue, strErrorMapValue ) )", 1, 0, 10001 );
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
         //:szWriteBuffer = "            <option selected=^selected^><%=strErrorMapValue%></option>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option selected=^selected^><%=strErrorMapValue%></option>", 1, 0, 10001 );
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
         //:szWriteBuffer = "            <option><%=strErrorMapValue%></option>"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "            <option><%=strErrorMapValue%></option>", 1, 0, 10001 );
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

         //:/*
         //:IF vDialog.Control.Subtype >= 20480 AND vDialog.Control.Subtype <= 21252   // IF Auto Include
         //:   szWriteBuffer = "         } // if ( !StringUtils.isBlank( strErrorMapValue ) )"
         //:   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
         //:END
         //:*/
         //:szWriteBuffer = "         ComboCount++;"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         ComboCount++;", 1, 0, 10001 );
         //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
         WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
         //:// IF lSubtype = 0  now always do setNextContinue here for performance reasons dks/dgc 2011.05.03
         //:   szWriteBuffer = "         csrRC =  v" + szCtrlTag +
         //:                   ".cursor( ^" + szListEntityName +
         //:                   "^ ).setNextContinue( );"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "         csrRC =  v", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szListEntityName, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).setNextContinue( );", 1, 0, 10001 );
         //:                   //"^ ).setNext( " + szScopingEntityName + " );"
         //:// ELSE
         //://    szWriteBuffer = "         nRC =  v" + szCtrlTag +
         //://                    ".cursor( ^" + szListEntityName + "^ ).setNextWithinOi( );"
         //:// END

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
      //:szWriteBuffer = "      v" + szCtrlTag + ".drop( );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      v", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".drop( );", 1, 0, 10001 );
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
      //:szWriteBuffer = "<input name=^h" + szCtrlTag + szRepeatGrpKey + "^ id=^h" + szCtrlTag + szRepeatGrpKey + "^ type=^hidden^ value=^<%=strComboSelectedValue%>^ >"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input name=^h", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^h", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ type=^hidden^ value=^<%=strComboSelectedValue%>^ >", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   } 

   //:END
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSPJ_CrteCheckBox( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 20 )    szJustify,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY,
//:                     STRING ( 100 )   szRepeatGrpKey )

//:   // Format an CHECKBOX control.
//:   VIEW vDialogRoot BASED ON LOD TZWDLGSO
zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteCheckBox( zVIEW     vDialog,
                      zLONG     lFile,
                      zPCHAR    szWriteBuffer,
                      zPCHAR    szIndent,
                      zPCHAR    szCtrlTag,
                      zPCHAR    szTableRowFlag,
                      zPCHAR    szJustify,
                      zPCHAR    szNoPositioning,
                      zLONG     lOffsetX,
                      zLONG     lOffsetY,
                      zPCHAR    szRepeatGrpKey )
{
   zVIEW     vDialogRoot = 0; 
   //:STRING ( 256 ) szStyle
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
   //:STRING ( 256 ) szBlob
   zCHAR     szBlob[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szUnChecked
   zCHAR     szUnChecked[ 257 ] = { 0 }; 
   //:STRING ( 500 ) szText
   zCHAR     szText[ 501 ] = { 0 }; 
   //:STRING ( 500 ) szText2
   zCHAR     szText2[ 501 ] = { 0 }; 
   //:STRING ( 5 )   szSrch
   zCHAR     szSrch[ 6 ] = { 0 }; 
   //:INTEGER lTemp
   zLONG     lTemp = 0; 
   //:INTEGER lLen
   zLONG     lLen = 0; 
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


   //:GetViewByName( vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK )   
   GetViewByName( &vDialogRoot, "DialogRoot", vDialog, zLEVEL_TASK );

   //:// See if the checkbox has an unchecked value. The checked value is in attrib RadioOrCheckboxValue but we 
   //:// don't have an attrib for the unchecked value.
   //:/*
   //:lTemp = 256
   //:GetBlobFromAttribute( szBlob, lTemp, vDialog, "Control", "CtrlBOI" )
   //:lLen = zstrlen( szBlob )
   //:szUnChecked = ""
   //:IF lTemp > ( lLen + 2 )
   //:   ZeidonCopyWithinString( szBlob, 1, lLen + 2, 256 )
   //:   szUnChecked = szBlob
   //:END
   //:*/

   //:szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   strErrorMapValue = ^^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = ^^;", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

   //:IF vDialog.CtrlMapView EXISTS
   lTempInteger_0 = CheckExistenceOfEntity( vDialog, "CtrlMapView" );
   if ( lTempInteger_0 == 0 )
   { 
      //:szWriteBuffer = "   " + vDialog.CtrlMapView.Name + " = " +
      //:                "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      task.log( ).debug( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      task.log( ).debug( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
      //:szWriteBuffer = "      nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( nRC >= 0 )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( nRC >= 0 )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         strRadioGroupValue = " +
      //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( );"
      GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         strRadioGroupValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_5, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   }", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   } 

   //:END

   //:szWriteBuffer = "   if ( StringUtils.equals( strRadioGroupValue, ^" +
   //:                vDialog.Control.RadioOrCheckboxValue + "^ ) )"
   GetVariableFromAttribute( szTempString_8, 0, 'S', 51, vDialog, "Control", "RadioOrCheckboxValue", "", 0 );
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( StringUtils.equals( strRadioGroupValue, ^", 1, 0, 10001 );
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
   //:IF szNoPositioning = ""
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
   { 
      //:CreateAbsolPosString( vDialog, szPosition, lOffsetX, lOffsetY )
      CreateAbsolPosString( vDialog, szPosition, lOffsetX, lOffsetY );
   } 

   //:END

   //:IF vDialog.Control.VisibleBorder = "Y"
   if ( CompareAttributeToString( vDialog, "Control", "VisibleBorder", "Y" ) == 0 )
   { 
      //:szPosition = szPosition + "border:solid;border-width:2px;border-style:groove;"
      ZeidonStringConcat( szPosition, 1, 0, "border:solid;border-width:2px;border-style:groove;", 1, 0, 101 );
   } 

   //:END

   //:szStyle = "style=^" + szPosition + "^" + szTabIndex
   ZeidonStringCopy( szStyle, 1, 0, "style=^", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szPosition, 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, "^", 1, 0, 257 );
   ZeidonStringConcat( szStyle, 1, 0, szTabIndex, 1, 0, 257 );

   //:IF szNoPositioning = "S"
   if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
   { 
      //:szStyle = "" // No style
      ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
   } 

   //:END

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
      //:szWriteBuffer = "<input type=^checkbox^ name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ " + szDisabled +
      //:                " value=^" + vDialog.Control.RadioOrCheckboxValue +
      //:                "^ <%=strErrorMapValue%> " + szTitleHTML + szStyle + " onclick=^" + vDialog.EventAct.Tag + "( )^>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input type=^checkbox^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
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
      //:szWriteBuffer = "<input type=^checkbox^ name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ " + szDisabled +
      //:                " value=^" + vDialog.Control.RadioOrCheckboxValue +
      //:                "^ <%=strErrorMapValue%> " + szTitleHTML + szStyle + ">"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<input type=^checkbox^ name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
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
   //:IF szNoPositioning = "Y"
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
      //:IF szNoPositioning = "S"
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = ""  // No style information.
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
         //:szSpaces = ""
         ZeidonStringCopy( szSpaces, 1, 0, "", 1, 0, 21 );
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
   } 

   //:END
   //:szClass = vDialog.Control.CSS_Class
   GetVariableFromAttribute( szClass, 0, 'S', 257, vDialog, "Control", "CSS_Class", "", 0 );


   //:// KJS 09/30/16 - Language Conversion.
   //:// I'm not sure that I want to use language conversion on mapped fields, but then again, I'm thinking maybe we should.
   //:// So for now, I am always using, if the flag is set.
   //:IF vDialogRoot.Dialog.wWebUsesLanguageConversion = "Y"
   if ( CompareAttributeToString( vDialogRoot, "Dialog", "wWebUsesLanguageConversion", "Y" ) == 0 )
   { 
      //:szText2 = vDialog.Control.Text
      GetVariableFromAttribute( szText2, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
      //:zSearchAndReplace( szText2, 1000, "\", "\\" )
      zSearchAndReplace( szText2, 1000, "\\", "\\\\" );
      //:szSrch = "\" + QUOTES 
      ZeidonStringCopy( szSrch, 1, 0, "\\", 1, 0, 6 );
      ZeidonStringConcat( szSrch, 1, 0, QUOTES, 1, 0, 6 );
      //:zSearchAndReplace( szText2, 1000, QUOTES, szSrch )
      zSearchAndReplace( szText2, 1000, QUOTES, szSrch );
      //:szSrch = ""
      ZeidonStringCopy( szSrch, 1, 0, "", 1, 0, 6 );
      //:szText = "<%=LangConv.getLanguageText(^" + szText2 + "^)%>" 
      ZeidonStringCopy( szText, 1, 0, "<%=LangConv.getLanguageText(^", 1, 0, 501 );
      ZeidonStringConcat( szText, 1, 0, szText2, 1, 0, 501 );
      ZeidonStringConcat( szText, 1, 0, "^)%>", 1, 0, 501 );
      //:ELSE
   } 
   else
   { 
      //:szText = vDialog.Control.Text
      GetVariableFromAttribute( szText, 0, 'S', 501, vDialog, "Control", "Text", "", 0 );
   } 

   //:END   

   //:IF szClass = ""
   if ( ZeidonStringCompare( szClass, 1, 0, "", 1, 0, 257 ) == 0 )
   { 
      //:szWriteBuffer = "<span " + szTitleHTML + szStyle + ">" + szSpaces + szText + "</span>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<span ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szSpaces, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "</span>", 1, 0, 10001 );
      //:ELSE
   } 
   else
   { 
      //:szWriteBuffer = "<span class=^" + szClass + "^ " + szTitleHTML + szStyle + ">" + szSpaces + szText + "</span>"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "<span class=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTitleHTML, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szStyle, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ">", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szSpaces, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szText, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "</span>", 1, 0, 10001 );
   } 

   //:END
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );
   return;
// END
} 


//:GLOBAL OPERATION
//:GenJSPJ_CrteCalendar( VIEW vDialog BASED ON LOD TZWDLGSO,
//:                     INTEGER          lFile,
//:                     STRING ( 10000 ) szWriteBuffer,
//:                     STRING ( 50 )    szIndent,
//:                     STRING ( 32 )    szCtrlTag,
//:                     STRING ( 1 )     szTableRowFlag,
//:                     STRING ( 20 )    szJustify,
//:                     STRING ( 1 )     szNoPositioning,
//:                     INTEGER          lOffsetX,
//:                     INTEGER          lOffsetY,
//:                     STRING ( 100 )   szRepeatGrpKey )

//:   // Format a CALENDAR control.

//:   VIEW vDialogRoot BASED ON LOD TZWDLGSO
zOPER_EXPORT zVOID OPERATION
GenJSPJ_CrteCalendar( zVIEW     vDialog,
                      zLONG     lFile,
                      zPCHAR    szWriteBuffer,
                      zPCHAR    szIndent,
                      zPCHAR    szCtrlTag,
                      zPCHAR    szTableRowFlag,
                      zPCHAR    szJustify,
                      zPCHAR    szNoPositioning,
                      zLONG     lOffsetX,
                      zLONG     lOffsetY,
                      zPCHAR    szRepeatGrpKey )
{
   zVIEW     vDialogRoot = 0; 
   //:STRING ( 256 ) szStyle
   zCHAR     szStyle[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szStyleCalendar
   zCHAR     szStyleCalendar[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szClass
   zCHAR     szClass[ 257 ] = { 0 }; 
   //:STRING ( 256 ) szContextName
   zCHAR     szContextName[ 257 ] = { 0 }; 
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
   //:STRING ( 50 )  szActionName
   zCHAR     szActionName[ 51 ] = { 0 }; 
   //:STRING ( 50 )  szKeyPressCode
   zCHAR     szKeyPressCode[ 51 ] = { 0 }; 
   //:STRING ( 500 ) szActionCode
   zCHAR     szActionCode[ 501 ] = { 0 }; 
   //:STRING ( 500 ) szCloseUpCode
   zCHAR     szCloseUpCode[ 501 ] = { 0 }; 
   //:DECIMAL        dDLUnits
   ZDecimal  dDLUnits = 0.0; 
   //:INTEGER nRC
   zLONG     nRC = 0; 
   zSHORT    RESULT; 
   zCHAR     szTempString_0[ 33 ]; 
   zCHAR     szTempString_1[ 33 ]; 
   zCHAR     szTempString_2[ 33 ]; 
   zCHAR     szTempString_3[ 33 ]; 
   zCHAR     szTempString_4[ 33 ]; 
   zSHORT    lTempInteger_0; 
   zCHAR     szTempString_5[ 33 ]; 
   zCHAR     szTempString_6[ 33 ]; 
   zCHAR     szTempString_7[ 33 ]; 
   zCHAR     szTempString_8[ 33 ]; 
   zCHAR     szTempString_9[ 33 ]; 
   zCHAR     szTempString_10[ 33 ]; 
   zCHAR     szTempString_11[ 33 ]; 
   zCHAR     szTempString_12[ 33 ]; 
   zSHORT    lTempInteger_1; 
   zLONG     lTempInteger_2; 
   zLONG     lTempInteger_3; 
   zLONG     lTempInteger_4; 
   zSHORT    lTempInteger_5; 
   zCHAR     szTempString_13[ 33 ]; 


   //:szWriteBuffer = "<%"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "<%", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   strErrorMapValue = VmlOperation.CheckError( ^" + szCtrlTag + "^, strError );"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   strErrorMapValue = VmlOperation.CheckError( ^", 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
   ZeidonStringConcat( szWriteBuffer, 1, 0, "^, strError );", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   if ( !StringUtils.isBlank( strErrorMapValue ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   if ( !StringUtils.isBlank( strErrorMapValue ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "   {"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "   {", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "      if ( StringUtils.equals( strErrorFlag, ^Y^ ) )"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( StringUtils.equals( strErrorFlag, ^Y^ ) )", 1, 0, 10001 );
   //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
   WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
   //:szWriteBuffer = "         strErrorColor = ^color:red;^;"
   ZeidonStringCopy( szWriteBuffer, 1, 0, "         strErrorColor = ^color:red;^;", 1, 0, 10001 );
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


   //:SET CURSOR FIRST vDialog.CtrlMapLOD_Attribute WITHIN vDialog.Control
   RESULT = SetCursorFirstEntity( vDialog, "CtrlMapLOD_Attribute", "Control" );
   //:IF RESULT >= zCURSOR_SET
   if ( RESULT >= zCURSOR_SET )
   { 
      //:szWriteBuffer = "      " + vDialog.CtrlMapView.Name + " = " +
      //:                "task.getViewByName( ^" + vDialog.CtrlMapView.Name + "^ );"
      GetVariableFromAttribute( szTempString_0, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_0, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "task.getViewByName( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_1, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_1, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      if ( VmlOperation.isValid( " + vDialog.CtrlMapView.Name + " ) == false )"
      GetVariableFromAttribute( szTempString_2, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      if ( VmlOperation.isValid( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_2, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " ) == false )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "         task.log( ).debug( ^Invalid View: ^ + ^" + szCtrlTag + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         task.log( ).debug( ^Invalid View: ^ + ^", 1, 0, 10001 );
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
      //:szWriteBuffer = "         nRC = " + vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).checkExistenceOfEntity( ).toInt();"
      GetVariableFromAttribute( szTempString_3, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "         nRC = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_3, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_4, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_4, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).checkExistenceOfEntity( ).toInt();", 1, 0, 10001 );
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
      lTempInteger_0 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
      if ( lTempInteger_0 == 0 )
      { 
         //:szContextName = "^" + vDialog.CtrlMapContext.Name + "^"
         GetVariableFromAttribute( szTempString_5, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
         ZeidonStringCopy( szContextName, 1, 0, "^", 1, 0, 257 );
         ZeidonStringConcat( szContextName, 1, 0, szTempString_5, 1, 0, 257 );
         ZeidonStringConcat( szContextName, 1, 0, "^", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:szContextName = "strDateFormat"
         ZeidonStringCopy( szContextName, 1, 0, "strDateFormat", 1, 0, 257 );
      } 

      //:END      
      //:szWriteBuffer = "            strErrorMapValue = " +
      //:                vDialog.CtrlMapView.Name + ".cursor( ^" +
      //:                vDialog.CtrlMapRelatedEntity.Name + "^ ).getAttribute( ^" +
      //:                vDialog.CtrlMapER_Attribute.Name + "^ ).getString( " + szContextName + " );"
      GetVariableFromAttribute( szTempString_6, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            strErrorMapValue = ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_6, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".cursor( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_7, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_7, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getAttribute( ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_8, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_8, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ).getString( ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szContextName, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, " );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );

      //:// KJS 02/15/11 - Thinking I need to add code to change values returned as null to "".
      //:szWriteBuffer = "            if ( strErrorMapValue == null )"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            if ( strErrorMapValue == null )", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "               strErrorMapValue = ^^;"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "               strErrorMapValue = ^^;", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 1 );

      //:szWriteBuffer = "            task.log( ).debug( ^" + vDialog.CtrlMapRelatedEntity.Name + "." +
      //:                vDialog.CtrlMapER_Attribute.Name + ": ^ + strErrorMapValue );"
      GetVariableFromAttribute( szTempString_9, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).debug( ^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_9, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_10, 0, 'S', 33, vDialog, "CtrlMapER_Attribute", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_10, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + strErrorMapValue );", 1, 0, 10001 );
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
      //:szWriteBuffer = "            task.log( ).debug( ^Entity does not exist for " + szCtrlTag + ": ^ + ^" +
      //:                vDialog.CtrlMapView.Name +
      //:                "." + vDialog.CtrlMapRelatedEntity.Name + "^ );"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "            task.log( ).debug( ^Entity does not exist for ", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ": ^ + ^", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_11, 0, 'S', 33, vDialog, "CtrlMapView", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_11, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, ".", 1, 0, 10001 );
      GetVariableFromAttribute( szTempString_12, 0, 'S', 33, vDialog, "CtrlMapRelatedEntity", "Name", "", 0 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_12, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ );", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "      }"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "      }", 1, 0, 10001 );
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

      //://**************** Get control event actions *********/

      //:// If there is an Event for the MLEdit, build code to insert in <textarea statement.
      //:szActionCode = ""
      ZeidonStringCopy( szActionCode, 1, 0, "", 1, 0, 501 );
      //:szCloseUpCode = ""
      ZeidonStringCopy( szCloseUpCode, 1, 0, "", 1, 0, 501 );
      //:FOR EACH vDialog.Event
      RESULT = SetCursorFirstEntity( vDialog, "Event", "" );
      while ( RESULT > zCURSOR_UNCHANGED )
      { 
         //:IF vDialog.EventAct EXISTS
         lTempInteger_1 = CheckExistenceOfEntity( vDialog, "EventAct" );
         if ( lTempInteger_1 == 0 )
         { 
            //:szActionName = vDialog.EventAct.Tag
            GetVariableFromAttribute( szActionName, 0, 'S', 51, vDialog, "EventAct", "Tag", "", 0 );
            //:IF vDialog.Event.Type = 80 // Event was GetFocus 50 but I have deleted that because it wasn't working correctly.
            if ( CompareAttributeToInteger( vDialog, "Event", "Type", 80 ) == 0 )
            { 
               //:szActionCode = szActionCode + " onfocus=^" + szActionName + "( )^ "
               ZeidonStringConcat( szActionCode, 1, 0, " onfocus=^", 1, 0, 501 );
               ZeidonStringConcat( szActionCode, 1, 0, szActionName, 1, 0, 501 );
               ZeidonStringConcat( szActionCode, 1, 0, "( )^ ", 1, 0, 501 );
               //:ELSE
            } 
            else
            { 
               //:IF vDialog.Event.Type = 48  // Event is LoseFocus 30
               if ( CompareAttributeToInteger( vDialog, "Event", "Type", 48 ) == 0 )
               { 
                  //:szActionCode = szActionCode + " onblur=^" + szActionName + "( )^ "
                  ZeidonStringConcat( szActionCode, 1, 0, " onblur=^", 1, 0, 501 );
                  ZeidonStringConcat( szActionCode, 1, 0, szActionName, 1, 0, 501 );
                  ZeidonStringConcat( szActionCode, 1, 0, "( )^ ", 1, 0, 501 );
                  //:ELSE
               } 
               else
               { 
                  //:IF vDialog.Event.Type = 96  // Event is CloseUp 60
                  if ( CompareAttributeToInteger( vDialog, "Event", "Type", 96 ) == 0 )
                  { 
                     //:szCloseUpCode = szCloseUpCode + "scwNextAction=" + szActionName + ".runsAfterSCW(this);"
                     ZeidonStringConcat( szCloseUpCode, 1, 0, "scwNextAction=", 1, 0, 501 );
                     ZeidonStringConcat( szCloseUpCode, 1, 0, szActionName, 1, 0, 501 );
                     ZeidonStringConcat( szCloseUpCode, 1, 0, ".runsAfterSCW(this);", 1, 0, 501 );
                  } 

                  //:END
               } 

               //:END
            } 

            //:END
         } 

         RESULT = SetCursorNextEntity( vDialog, "Event", "" );
         //:END
      } 

      //:END

      //://***************************************************

      //:// We will set the height to the constant 32 px.
      //:PIX_PER_DU( vDialog, dDLUnits )
      PIX_PER_DU( vDialog, &dDLUnits );
      //:zIntegerToString( szWidth, 10, vDialog.Control.SZDLG_X * dDLUnits )
      GetIntegerFromAttribute( &lTempInteger_2, vDialog, "Control", "SZDLG_X" );
      zIntegerToString( szWidth, 10, lTempInteger_2 * dDLUnits );
      //:szHeight = "32"
      ZeidonStringCopy( szHeight, 1, 0, "32", 1, 0, 11 );
      //:szStyle = "style=^width:" + szWidth + "px;height:" + szHeight + "px;"
      ZeidonStringCopy( szStyle, 1, 0, "style=^width:", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, szWidth, 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "px;height:", 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, szHeight, 1, 0, 257 );
      ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );

      //:// If szNoPositioning is null then we are using absolute positioning when creating controls.
      //:IF szNoPositioning = ""
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "", 1, 0, 2 ) == 0 )
      { 

         //:zIntegerToString( szX_Pos, 10, vDialog.Control.PSDLG_X * dDLUnits )
         GetIntegerFromAttribute( &lTempInteger_3, vDialog, "Control", "PSDLG_X" );
         zIntegerToString( szX_Pos, 10, lTempInteger_3 * dDLUnits );
         //:zIntegerToString( szY_Pos, 10, vDialog.Control.PSDLG_Y * dDLUnits )
         GetIntegerFromAttribute( &lTempInteger_4, vDialog, "Control", "PSDLG_Y" );
         zIntegerToString( szY_Pos, 10, lTempInteger_4 * dDLUnits );
         //:szStyle = szStyle + "position:absolute;left:" + szX_Pos + "px;" + "top:" + szY_Pos + "px;^ "
         ZeidonStringConcat( szStyle, 1, 0, "position:absolute;left:", 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, szX_Pos, 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, "px;", 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, "top:", 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, szY_Pos, 1, 0, 257 );
         ZeidonStringConcat( szStyle, 1, 0, "px;^ ", 1, 0, 257 );
         //:szStyleCalendar = " style=^width:80px^"
         ZeidonStringCopy( szStyleCalendar, 1, 0, " style=^width:80px^", 1, 0, 257 );
         //:ELSE
      } 
      else
      { 
         //:szStyle = szStyle + "^ "
         ZeidonStringConcat( szStyle, 1, 0, "^ ", 1, 0, 257 );
         //:szStyleCalendar = " style=^width:80px^"
         ZeidonStringCopy( szStyleCalendar, 1, 0, " style=^width:80px^", 1, 0, 257 );
      } 

      //:END

      //:IF szNoPositioning = "S"
      if ( ZeidonStringCompare( szNoPositioning, 1, 0, "S", 1, 0, 2 ) == 0 )
      { 
         //:szStyle = "" // No style information
         ZeidonStringCopy( szStyle, 1, 0, "", 1, 0, 257 );
         //:szStyleCalendar = ""
         ZeidonStringCopy( szStyleCalendar, 1, 0, "", 1, 0, 257 );
      } 

      //:END

      //:CreateTabIndexString( vDialog, szTabIndex )
      CreateTabIndexString( vDialog, szTabIndex );

      //:CreateDisabledString( vDialog, szDisabled )
      CreateDisabledString( vDialog, szDisabled );

      //:// If there is a Default button for the window, we must add some characters
      //:// to the end of the input statement.
      //:szKeyPressCode = ""
      ZeidonStringCopy( szKeyPressCode, 1, 0, "", 1, 0, 51 );
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
         //:szKeyPressCode = szKeyPressCode + " onkeypress=^return _OnEnter( event )^"
         ZeidonStringConcat( szKeyPressCode, 1, 0, " onkeypress=^return _OnEnter( event )^", 1, 0, 51 );
      } 

      //:END      


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
         //:szWriteBuffer = "   <input name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ " + szDisabled +
         //:                    szActionCode + szStyleCalendar + " type=^text^ value=^<%=strErrorMapValue%>^ " + szTabIndex + szKeyPressCode + " />"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyleCalendar, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " type=^text^ value=^<%=strErrorMapValue%>^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szKeyPressCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " />", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "   <input class=^" + szClass + "^ name=^" + szCtrlTag + szRepeatGrpKey + "^ id=^" + szCtrlTag + szRepeatGrpKey + "^ " + szDisabled +
         //:                    szActionCode + szStyleCalendar + " type=^text^ value=^<%=strErrorMapValue%>^ " + szTabIndex + szKeyPressCode + " />"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "   <input class=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szClass, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ name=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szDisabled, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szActionCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szStyleCalendar, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " type=^text^ value=^<%=strErrorMapValue%>^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szKeyPressCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " />", 1, 0, 10001 );
      } 

      //:END
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:szWriteBuffer = "   <img src=^images/scw.gif^  name=^" + szCtrlTag + "Img" + szRepeatGrpKey + "^ id=^" + szCtrlTag + "Img" + szRepeatGrpKey + "^ title=^Select Date^ alt=^Select Date^"
      ZeidonStringCopy( szWriteBuffer, 1, 0, "   <img src=^images/scw.gif^  name=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "Img", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ id=^", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "Img", 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
      ZeidonStringConcat( szWriteBuffer, 1, 0, "^ title=^Select Date^ alt=^Select Date^", 1, 0, 10001 );
      //:WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 )
      WL_QC( vDialog, lFile, szWriteBuffer, "^", 0 );
      //:// KJS 03/16/16 - Added scwShowWFormat to scw.js file so that if we have a format on the calendar, then we use that. If no context, I am just calling scwShow, even
      //:// though I could call scwShowWFormat with zDateFormat... which would do that same thing. This is compatible for any jsp pages that are older and don't use a context.
      //:IF vDialog.CtrlMapContext EXISTS
      lTempInteger_5 = CheckExistenceOfEntity( vDialog, "CtrlMapContext" );
      if ( lTempInteger_5 == 0 )
      { 
         //:szWriteBuffer = "        onclick=^" + szCloseUpCode + "scwShowWFormat( document.getElementById( '" + szCtrlTag + szRepeatGrpKey + "' ), this, '" + vDialog.CtrlMapContext.Name + "' );^ " + szTabIndex + " />"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "        onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCloseUpCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "scwShowWFormat( document.getElementById( '", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "' ), this, '", 1, 0, 10001 );
         GetVariableFromAttribute( szTempString_13, 0, 'S', 33, vDialog, "CtrlMapContext", "Name", "", 0 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTempString_13, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "' );^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " />", 1, 0, 10001 );
         //:ELSE
      } 
      else
      { 
         //:szWriteBuffer = "        onclick=^" + szCloseUpCode + "scwShow( document.getElementById( '" + szCtrlTag + szRepeatGrpKey + "' ), this );^ " + szTabIndex + " />"
         ZeidonStringCopy( szWriteBuffer, 1, 0, "        onclick=^", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCloseUpCode, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "scwShow( document.getElementById( '", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szCtrlTag, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szRepeatGrpKey, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, "' ), this );^ ", 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, szTabIndex, 1, 0, 10001 );
         ZeidonStringConcat( szWriteBuffer, 1, 0, " />", 1, 0, 10001 );
      } 

      //:END
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


 
#ifdef __cplusplus
}
#endif
