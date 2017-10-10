// qstruct  build  v4.54 

/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class DialogImpl implements Dialog
{
   protected String  Tag;
   protected String  DLL_Name;
   protected Integer ZKey;
   protected Integer NextZKeyToAssign;
   protected String  Desc;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_PageHeadInclude;
   protected String  WEB_TopMenuInclude;
   protected String  WEB_TopBannerName;
   protected String  WEB_FooterInclude;
   protected String  WEB_LeftSideInclude;
   protected String  WEB_RelativePositionFlag;
   protected String  WEB_JSPGenerationPositioning;
   protected String  WEB_PageBackgroundInclude;
   protected String  WEB_NoAutoLogOut;
   protected String  WEB_ImportInclude;
   protected String  WEB_Logout;
   protected String  Converted;
   protected String  LastSyncDate;
   protected String  wOriginalViewName;
   protected String  wNewViewName;
   protected String  wReusableSelectEntityName;
   protected String  wWebGridControlProperties;
   protected String  wWebGridSubControlProperties;
   protected String  wWebGroupControlProperties;
   protected String  wWebEditControlProperties;
   protected String  wWebPushControlProperties;
   protected String  wWebTextControlProperties;
   protected String  wWebUsesLanguageConversion;
   protected String  wMapTypeGridColumnControl;
   protected String  wMapTypeTextControl;
   protected String  wOriginalClassName;
   protected String  wNewClassName;
   protected String  wClassNameConvertType;


   // ctor
   protected DialogImpl( EntityCursor cursor )
   {
      loadDialogEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the DLL_Name
    */
   public String getDLL_Name( )
   {
      return DLL_Name;
   }

   /**
    * @param DLL_Name to set 
    */
   public void setDLL_Name( String DLL_Name )
   {
      this.DLL_Name = DLL_Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the NextZKeyToAssign
    */
   public Integer getNextZKeyToAssign( )
   {
      return NextZKeyToAssign;
   }

   /**
    * @param NextZKeyToAssign to set 
    */
   public void setNextZKeyToAssign( Integer NextZKeyToAssign )
   {
      this.NextZKeyToAssign = NextZKeyToAssign;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_PageHeadInclude
    */
   public String getWEB_PageHeadInclude( )
   {
      return WEB_PageHeadInclude;
   }

   /**
    * @param WEB_PageHeadInclude to set 
    */
   public void setWEB_PageHeadInclude( String WEB_PageHeadInclude )
   {
      this.WEB_PageHeadInclude = WEB_PageHeadInclude;
   }

   /**
    * @return the WEB_TopMenuInclude
    */
   public String getWEB_TopMenuInclude( )
   {
      return WEB_TopMenuInclude;
   }

   /**
    * @param WEB_TopMenuInclude to set 
    */
   public void setWEB_TopMenuInclude( String WEB_TopMenuInclude )
   {
      this.WEB_TopMenuInclude = WEB_TopMenuInclude;
   }

   /**
    * @return the WEB_TopBannerName
    */
   public String getWEB_TopBannerName( )
   {
      return WEB_TopBannerName;
   }

   /**
    * @param WEB_TopBannerName to set 
    */
   public void setWEB_TopBannerName( String WEB_TopBannerName )
   {
      this.WEB_TopBannerName = WEB_TopBannerName;
   }

   /**
    * @return the WEB_FooterInclude
    */
   public String getWEB_FooterInclude( )
   {
      return WEB_FooterInclude;
   }

   /**
    * @param WEB_FooterInclude to set 
    */
   public void setWEB_FooterInclude( String WEB_FooterInclude )
   {
      this.WEB_FooterInclude = WEB_FooterInclude;
   }

   /**
    * @return the WEB_LeftSideInclude
    */
   public String getWEB_LeftSideInclude( )
   {
      return WEB_LeftSideInclude;
   }

   /**
    * @param WEB_LeftSideInclude to set 
    */
   public void setWEB_LeftSideInclude( String WEB_LeftSideInclude )
   {
      this.WEB_LeftSideInclude = WEB_LeftSideInclude;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   /**
    * @return the WEB_JSPGenerationPositioning
    */
   public String getWEB_JSPGenerationPositioning( )
   {
      return WEB_JSPGenerationPositioning;
   }

   /**
    * @param WEB_JSPGenerationPositioning to set 
    */
   public void setWEB_JSPGenerationPositioning( String WEB_JSPGenerationPositioning )
   {
      this.WEB_JSPGenerationPositioning = WEB_JSPGenerationPositioning;
   }

   /**
    * @return the WEB_PageBackgroundInclude
    */
   public String getWEB_PageBackgroundInclude( )
   {
      return WEB_PageBackgroundInclude;
   }

   /**
    * @param WEB_PageBackgroundInclude to set 
    */
   public void setWEB_PageBackgroundInclude( String WEB_PageBackgroundInclude )
   {
      this.WEB_PageBackgroundInclude = WEB_PageBackgroundInclude;
   }

   /**
    * @return the WEB_NoAutoLogOut
    */
   public String getWEB_NoAutoLogOut( )
   {
      return WEB_NoAutoLogOut;
   }

   /**
    * @param WEB_NoAutoLogOut to set 
    */
   public void setWEB_NoAutoLogOut( String WEB_NoAutoLogOut )
   {
      this.WEB_NoAutoLogOut = WEB_NoAutoLogOut;
   }

   /**
    * @return the WEB_ImportInclude
    */
   public String getWEB_ImportInclude( )
   {
      return WEB_ImportInclude;
   }

   /**
    * @param WEB_ImportInclude to set 
    */
   public void setWEB_ImportInclude( String WEB_ImportInclude )
   {
      this.WEB_ImportInclude = WEB_ImportInclude;
   }

   /**
    * @return the WEB_Logout
    */
   public String getWEB_Logout( )
   {
      return WEB_Logout;
   }

   /**
    * @param WEB_Logout to set 
    */
   public void setWEB_Logout( String WEB_Logout )
   {
      this.WEB_Logout = WEB_Logout;
   }

   /**
    * @return the Converted
    */
   public String getConverted( )
   {
      return Converted;
   }

   /**
    * @param Converted to set 
    */
   public void setConverted( String Converted )
   {
      this.Converted = Converted;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the wOriginalViewName
    */
   public String getwOriginalViewName( )
   {
      return wOriginalViewName;
   }

   /**
    * @param wOriginalViewName to set 
    */
   public void setwOriginalViewName( String wOriginalViewName )
   {
      this.wOriginalViewName = wOriginalViewName;
   }

   /**
    * @return the wNewViewName
    */
   public String getwNewViewName( )
   {
      return wNewViewName;
   }

   /**
    * @param wNewViewName to set 
    */
   public void setwNewViewName( String wNewViewName )
   {
      this.wNewViewName = wNewViewName;
   }

   /**
    * @return the wReusableSelectEntityName
    */
   public String getwReusableSelectEntityName( )
   {
      return wReusableSelectEntityName;
   }

   /**
    * @param wReusableSelectEntityName to set 
    */
   public void setwReusableSelectEntityName( String wReusableSelectEntityName )
   {
      this.wReusableSelectEntityName = wReusableSelectEntityName;
   }

   /**
    * @return the wWebGridControlProperties
    */
   public String getwWebGridControlProperties( )
   {
      return wWebGridControlProperties;
   }

   /**
    * @param wWebGridControlProperties to set 
    */
   public void setwWebGridControlProperties( String wWebGridControlProperties )
   {
      this.wWebGridControlProperties = wWebGridControlProperties;
   }

   /**
    * @return the wWebGridSubControlProperties
    */
   public String getwWebGridSubControlProperties( )
   {
      return wWebGridSubControlProperties;
   }

   /**
    * @param wWebGridSubControlProperties to set 
    */
   public void setwWebGridSubControlProperties( String wWebGridSubControlProperties )
   {
      this.wWebGridSubControlProperties = wWebGridSubControlProperties;
   }

   /**
    * @return the wWebGroupControlProperties
    */
   public String getwWebGroupControlProperties( )
   {
      return wWebGroupControlProperties;
   }

   /**
    * @param wWebGroupControlProperties to set 
    */
   public void setwWebGroupControlProperties( String wWebGroupControlProperties )
   {
      this.wWebGroupControlProperties = wWebGroupControlProperties;
   }

   /**
    * @return the wWebEditControlProperties
    */
   public String getwWebEditControlProperties( )
   {
      return wWebEditControlProperties;
   }

   /**
    * @param wWebEditControlProperties to set 
    */
   public void setwWebEditControlProperties( String wWebEditControlProperties )
   {
      this.wWebEditControlProperties = wWebEditControlProperties;
   }

   /**
    * @return the wWebPushControlProperties
    */
   public String getwWebPushControlProperties( )
   {
      return wWebPushControlProperties;
   }

   /**
    * @param wWebPushControlProperties to set 
    */
   public void setwWebPushControlProperties( String wWebPushControlProperties )
   {
      this.wWebPushControlProperties = wWebPushControlProperties;
   }

   /**
    * @return the wWebTextControlProperties
    */
   public String getwWebTextControlProperties( )
   {
      return wWebTextControlProperties;
   }

   /**
    * @param wWebTextControlProperties to set 
    */
   public void setwWebTextControlProperties( String wWebTextControlProperties )
   {
      this.wWebTextControlProperties = wWebTextControlProperties;
   }

   /**
    * @return the wWebUsesLanguageConversion
    */
   public String getwWebUsesLanguageConversion( )
   {
      return wWebUsesLanguageConversion;
   }

   /**
    * @param wWebUsesLanguageConversion to set 
    */
   public void setwWebUsesLanguageConversion( String wWebUsesLanguageConversion )
   {
      this.wWebUsesLanguageConversion = wWebUsesLanguageConversion;
   }

   /**
    * @return the wMapTypeGridColumnControl
    */
   public String getwMapTypeGridColumnControl( )
   {
      return wMapTypeGridColumnControl;
   }

   /**
    * @param wMapTypeGridColumnControl to set 
    */
   public void setwMapTypeGridColumnControl( String wMapTypeGridColumnControl )
   {
      this.wMapTypeGridColumnControl = wMapTypeGridColumnControl;
   }

   /**
    * @return the wMapTypeTextControl
    */
   public String getwMapTypeTextControl( )
   {
      return wMapTypeTextControl;
   }

   /**
    * @param wMapTypeTextControl to set 
    */
   public void setwMapTypeTextControl( String wMapTypeTextControl )
   {
      this.wMapTypeTextControl = wMapTypeTextControl;
   }

   /**
    * @return the wOriginalClassName
    */
   public String getwOriginalClassName( )
   {
      return wOriginalClassName;
   }

   /**
    * @param wOriginalClassName to set 
    */
   public void setwOriginalClassName( String wOriginalClassName )
   {
      this.wOriginalClassName = wOriginalClassName;
   }

   /**
    * @return the wNewClassName
    */
   public String getwNewClassName( )
   {
      return wNewClassName;
   }

   /**
    * @param wNewClassName to set 
    */
   public void setwNewClassName( String wNewClassName )
   {
      this.wNewClassName = wNewClassName;
   }

   /**
    * @return the wClassNameConvertType
    */
   public String getwClassNameConvertType( )
   {
      return wClassNameConvertType;
   }

   /**
    * @param wClassNameConvertType to set 
    */
   public void setwClassNameConvertType( String wClassNameConvertType )
   {
      this.wClassNameConvertType = wClassNameConvertType;
   }

   public int loadDialogEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      DLL_Name = cursor.getStringFromAttribute( "DLL_Name" );  if ( DLL_Name == null ) DLL_Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      NextZKeyToAssign = cursor.getIntegerFromAttribute( "NextZKeyToAssign" );  if ( NextZKeyToAssign == null ) NextZKeyToAssign = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_PageHeadInclude = cursor.getStringFromAttribute( "WEB_PageHeadInclude" );  if ( WEB_PageHeadInclude == null ) WEB_PageHeadInclude = "";
      WEB_TopMenuInclude = cursor.getStringFromAttribute( "WEB_TopMenuInclude" );  if ( WEB_TopMenuInclude == null ) WEB_TopMenuInclude = "";
      WEB_TopBannerName = cursor.getStringFromAttribute( "WEB_TopBannerName" );  if ( WEB_TopBannerName == null ) WEB_TopBannerName = "";
      WEB_FooterInclude = cursor.getStringFromAttribute( "WEB_FooterInclude" );  if ( WEB_FooterInclude == null ) WEB_FooterInclude = "";
      WEB_LeftSideInclude = cursor.getStringFromAttribute( "WEB_LeftSideInclude" );  if ( WEB_LeftSideInclude == null ) WEB_LeftSideInclude = "";
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";
      WEB_JSPGenerationPositioning = cursor.getStringFromAttribute( "WEB_JSPGenerationPositioning" );  if ( WEB_JSPGenerationPositioning == null ) WEB_JSPGenerationPositioning = "";
      WEB_PageBackgroundInclude = cursor.getStringFromAttribute( "WEB_PageBackgroundInclude" );  if ( WEB_PageBackgroundInclude == null ) WEB_PageBackgroundInclude = "";
      WEB_NoAutoLogOut = cursor.getStringFromAttribute( "WEB_NoAutoLogOut" );  if ( WEB_NoAutoLogOut == null ) WEB_NoAutoLogOut = "";
      WEB_ImportInclude = cursor.getStringFromAttribute( "WEB_ImportInclude" );  if ( WEB_ImportInclude == null ) WEB_ImportInclude = "";
      WEB_Logout = cursor.getStringFromAttribute( "WEB_Logout" );  if ( WEB_Logout == null ) WEB_Logout = "";
      Converted = cursor.getStringFromAttribute( "Converted" );  if ( Converted == null ) Converted = "";
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      wOriginalViewName = cursor.getStringFromAttribute( "wOriginalViewName" );  if ( wOriginalViewName == null ) wOriginalViewName = "";
      wNewViewName = cursor.getStringFromAttribute( "wNewViewName" );  if ( wNewViewName == null ) wNewViewName = "";
      wReusableSelectEntityName = cursor.getStringFromAttribute( "wReusableSelectEntityName" );  if ( wReusableSelectEntityName == null ) wReusableSelectEntityName = "";
      wWebGridControlProperties = cursor.getStringFromAttribute( "wWebGridControlProperties" );  if ( wWebGridControlProperties == null ) wWebGridControlProperties = "";
      wWebGridSubControlProperties = cursor.getStringFromAttribute( "wWebGridSubControlProperties" );  if ( wWebGridSubControlProperties == null ) wWebGridSubControlProperties = "";
      wWebGroupControlProperties = cursor.getStringFromAttribute( "wWebGroupControlProperties" );  if ( wWebGroupControlProperties == null ) wWebGroupControlProperties = "";
      wWebEditControlProperties = cursor.getStringFromAttribute( "wWebEditControlProperties" );  if ( wWebEditControlProperties == null ) wWebEditControlProperties = "";
      wWebPushControlProperties = cursor.getStringFromAttribute( "wWebPushControlProperties" );  if ( wWebPushControlProperties == null ) wWebPushControlProperties = "";
      wWebTextControlProperties = cursor.getStringFromAttribute( "wWebTextControlProperties" );  if ( wWebTextControlProperties == null ) wWebTextControlProperties = "";
      wWebUsesLanguageConversion = cursor.getStringFromAttribute( "wWebUsesLanguageConversion" );  if ( wWebUsesLanguageConversion == null ) wWebUsesLanguageConversion = "";
      wMapTypeGridColumnControl = cursor.getStringFromAttribute( "wMapTypeGridColumnControl" );  if ( wMapTypeGridColumnControl == null ) wMapTypeGridColumnControl = "";
      wMapTypeTextControl = cursor.getStringFromAttribute( "wMapTypeTextControl" );  if ( wMapTypeTextControl == null ) wMapTypeTextControl = "";
      wOriginalClassName = cursor.getStringFromAttribute( "wOriginalClassName" );  if ( wOriginalClassName == null ) wOriginalClassName = "";
      wNewClassName = cursor.getStringFromAttribute( "wNewClassName" );  if ( wNewClassName == null ) wNewClassName = "";
      wClassNameConvertType = cursor.getStringFromAttribute( "wClassNameConvertType" );  if ( wClassNameConvertType == null ) wClassNameConvertType = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class DfltWndImpl implements DfltWnd
{
   protected String  Tag;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected String  DfltButton;
   protected Integer ZKey;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected Integer Subtype;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected DfltWndImpl( EntityCursor cursor )
   {
      loadDfltWndEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadDfltWndEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WindowImpl implements Window
{
   protected String  Tag;
   protected Integer Subtype;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected String  WEB_RelativePositionFlag;
   protected Integer SZMAX_Y;
   protected String  DfltButton;
   protected Integer ZKey;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_PageHeadInclude;
   protected String  WEB_TopMenuInclude;
   protected String  WEB_ReusableMenuWindow;
   protected String  WEB_NoBannerFlag;
   protected String  WEB_NoTopMenuFlag;
   protected String  WEB_AbsolutePositionFlag;
   protected String  WEB_JSPGenerationPositioning;
   protected String  WEB_RegisterZeidonWindow;
   protected String  WEB_UnregisterZeidonWindow;
   protected String  WEB_Logout;
   protected Integer BarID;
   protected String  CaptionNLS_Text;
   protected Integer ControlTagCounter;
   protected String  wWindowHasTabsFlag;


   // ctor
   protected WindowImpl( EntityCursor cursor )
   {
      loadWindowEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_PageHeadInclude
    */
   public String getWEB_PageHeadInclude( )
   {
      return WEB_PageHeadInclude;
   }

   /**
    * @param WEB_PageHeadInclude to set 
    */
   public void setWEB_PageHeadInclude( String WEB_PageHeadInclude )
   {
      this.WEB_PageHeadInclude = WEB_PageHeadInclude;
   }

   /**
    * @return the WEB_TopMenuInclude
    */
   public String getWEB_TopMenuInclude( )
   {
      return WEB_TopMenuInclude;
   }

   /**
    * @param WEB_TopMenuInclude to set 
    */
   public void setWEB_TopMenuInclude( String WEB_TopMenuInclude )
   {
      this.WEB_TopMenuInclude = WEB_TopMenuInclude;
   }

   /**
    * @return the WEB_ReusableMenuWindow
    */
   public String getWEB_ReusableMenuWindow( )
   {
      return WEB_ReusableMenuWindow;
   }

   /**
    * @param WEB_ReusableMenuWindow to set 
    */
   public void setWEB_ReusableMenuWindow( String WEB_ReusableMenuWindow )
   {
      this.WEB_ReusableMenuWindow = WEB_ReusableMenuWindow;
   }

   /**
    * @return the WEB_NoBannerFlag
    */
   public String getWEB_NoBannerFlag( )
   {
      return WEB_NoBannerFlag;
   }

   /**
    * @param WEB_NoBannerFlag to set 
    */
   public void setWEB_NoBannerFlag( String WEB_NoBannerFlag )
   {
      this.WEB_NoBannerFlag = WEB_NoBannerFlag;
   }

   /**
    * @return the WEB_NoTopMenuFlag
    */
   public String getWEB_NoTopMenuFlag( )
   {
      return WEB_NoTopMenuFlag;
   }

   /**
    * @param WEB_NoTopMenuFlag to set 
    */
   public void setWEB_NoTopMenuFlag( String WEB_NoTopMenuFlag )
   {
      this.WEB_NoTopMenuFlag = WEB_NoTopMenuFlag;
   }

   /**
    * @return the WEB_AbsolutePositionFlag
    */
   public String getWEB_AbsolutePositionFlag( )
   {
      return WEB_AbsolutePositionFlag;
   }

   /**
    * @param WEB_AbsolutePositionFlag to set 
    */
   public void setWEB_AbsolutePositionFlag( String WEB_AbsolutePositionFlag )
   {
      this.WEB_AbsolutePositionFlag = WEB_AbsolutePositionFlag;
   }

   /**
    * @return the WEB_JSPGenerationPositioning
    */
   public String getWEB_JSPGenerationPositioning( )
   {
      return WEB_JSPGenerationPositioning;
   }

   /**
    * @param WEB_JSPGenerationPositioning to set 
    */
   public void setWEB_JSPGenerationPositioning( String WEB_JSPGenerationPositioning )
   {
      this.WEB_JSPGenerationPositioning = WEB_JSPGenerationPositioning;
   }

   /**
    * @return the WEB_RegisterZeidonWindow
    */
   public String getWEB_RegisterZeidonWindow( )
   {
      return WEB_RegisterZeidonWindow;
   }

   /**
    * @param WEB_RegisterZeidonWindow to set 
    */
   public void setWEB_RegisterZeidonWindow( String WEB_RegisterZeidonWindow )
   {
      this.WEB_RegisterZeidonWindow = WEB_RegisterZeidonWindow;
   }

   /**
    * @return the WEB_UnregisterZeidonWindow
    */
   public String getWEB_UnregisterZeidonWindow( )
   {
      return WEB_UnregisterZeidonWindow;
   }

   /**
    * @param WEB_UnregisterZeidonWindow to set 
    */
   public void setWEB_UnregisterZeidonWindow( String WEB_UnregisterZeidonWindow )
   {
      this.WEB_UnregisterZeidonWindow = WEB_UnregisterZeidonWindow;
   }

   /**
    * @return the WEB_Logout
    */
   public String getWEB_Logout( )
   {
      return WEB_Logout;
   }

   /**
    * @param WEB_Logout to set 
    */
   public void setWEB_Logout( String WEB_Logout )
   {
      this.WEB_Logout = WEB_Logout;
   }

   /**
    * @return the BarID
    */
   public Integer getBarID( )
   {
      return BarID;
   }

   /**
    * @param BarID to set 
    */
   public void setBarID( Integer BarID )
   {
      this.BarID = BarID;
   }

   /**
    * @return the CaptionNLS_Text
    */
   public String getCaptionNLS_Text( )
   {
      return CaptionNLS_Text;
   }

   /**
    * @param CaptionNLS_Text to set 
    */
   public void setCaptionNLS_Text( String CaptionNLS_Text )
   {
      this.CaptionNLS_Text = CaptionNLS_Text;
   }

   /**
    * @return the ControlTagCounter
    */
   public Integer getControlTagCounter( )
   {
      return ControlTagCounter;
   }

   /**
    * @param ControlTagCounter to set 
    */
   public void setControlTagCounter( Integer ControlTagCounter )
   {
      this.ControlTagCounter = ControlTagCounter;
   }

   /**
    * @return the wWindowHasTabsFlag
    */
   public String getwWindowHasTabsFlag( )
   {
      return wWindowHasTabsFlag;
   }

   /**
    * @param wWindowHasTabsFlag to set 
    */
   public void setwWindowHasTabsFlag( String wWindowHasTabsFlag )
   {
      this.wWindowHasTabsFlag = wWindowHasTabsFlag;
   }

   public int loadWindowEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_PageHeadInclude = cursor.getStringFromAttribute( "WEB_PageHeadInclude" );  if ( WEB_PageHeadInclude == null ) WEB_PageHeadInclude = "";
      WEB_TopMenuInclude = cursor.getStringFromAttribute( "WEB_TopMenuInclude" );  if ( WEB_TopMenuInclude == null ) WEB_TopMenuInclude = "";
      WEB_ReusableMenuWindow = cursor.getStringFromAttribute( "WEB_ReusableMenuWindow" );  if ( WEB_ReusableMenuWindow == null ) WEB_ReusableMenuWindow = "";
      WEB_NoBannerFlag = cursor.getStringFromAttribute( "WEB_NoBannerFlag" );  if ( WEB_NoBannerFlag == null ) WEB_NoBannerFlag = "";
      WEB_NoTopMenuFlag = cursor.getStringFromAttribute( "WEB_NoTopMenuFlag" );  if ( WEB_NoTopMenuFlag == null ) WEB_NoTopMenuFlag = "";
      WEB_AbsolutePositionFlag = cursor.getStringFromAttribute( "WEB_AbsolutePositionFlag" );  if ( WEB_AbsolutePositionFlag == null ) WEB_AbsolutePositionFlag = "";
      WEB_JSPGenerationPositioning = cursor.getStringFromAttribute( "WEB_JSPGenerationPositioning" );  if ( WEB_JSPGenerationPositioning == null ) WEB_JSPGenerationPositioning = "";
      WEB_RegisterZeidonWindow = cursor.getStringFromAttribute( "WEB_RegisterZeidonWindow" );  if ( WEB_RegisterZeidonWindow == null ) WEB_RegisterZeidonWindow = "";
      WEB_UnregisterZeidonWindow = cursor.getStringFromAttribute( "WEB_UnregisterZeidonWindow" );  if ( WEB_UnregisterZeidonWindow == null ) WEB_UnregisterZeidonWindow = "";
      WEB_Logout = cursor.getStringFromAttribute( "WEB_Logout" );  if ( WEB_Logout == null ) WEB_Logout = "";
      BarID = cursor.getIntegerFromAttribute( "BarID" );  if ( BarID == null ) BarID = 0;
      CaptionNLS_Text = cursor.getStringFromAttribute( "CaptionNLS_Text" );  if ( CaptionNLS_Text == null ) CaptionNLS_Text = "";
      ControlTagCounter = cursor.getIntegerFromAttribute( "ControlTagCounter" );  if ( ControlTagCounter == null ) ControlTagCounter = 0;
      wWindowHasTabsFlag = cursor.getStringFromAttribute( "wWindowHasTabsFlag" );  if ( wWindowHasTabsFlag == null ) wWindowHasTabsFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ControlImpl implements Control
{
   protected String  Tag;
   protected String  Text;
   protected Integer ZKey;
   protected Integer Type;
   protected Integer Subtype;
   protected String  DD_TargetKey;
   protected String  DD_SourceKey;
   protected Integer OptionFlags;
   protected String  DD_Type;
   protected Integer IdNbr;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Blob    CtrlBOI;
   protected Integer Underline;
   protected Integer SyncKey;
   protected String  DIL_Text;
   protected String  Placeholder;
   protected String  ReportGroupType;
   protected String  ForceHeaderPerEntity;
   protected Integer ExtendedStyle;
   protected String  GUID;
   protected Blob    Properties;
   protected Blob    LKey;
   protected Integer BorderWidth;
   protected Integer BorderStyle;
   protected Integer BorderTop;
   protected Integer BorderBottom;
   protected Integer BorderLeft;
   protected Integer BorderRight;
   protected String  TextAlignHorizontal;
   protected String  VisibleBorder;
   protected String  CenterJustify;
   protected String  RightJustify;
   protected String  Disabled;
   protected String  CSS_Class;
   protected String  CSS_Id;
   protected String  CSS_Font;
   protected String  CSS_Position;
   protected String  CSS_Size;
   protected String  JavaScript;
   protected String  RadioOrCheckboxValue;
   protected String  WebFileName;
   protected String  WebCtrlLabelLink;
   protected String  WebSelectSetName;
   protected String  WebCtrlType;
   protected String  WebColumnSpan;
   protected String  WebWrap;
   protected String  WebNoGridDataMessage;
   protected String  WebNoGridDataMsgClass;
   protected String  WebreCAPTCHAPublicKey;
   protected String  WebreCAPTCHAPrivateKey;
   protected String  WebHTML5Attribute;
   protected String  WebPlaceholder;
   protected String  MenuName;
   protected String  DIL_Inherited;
   protected String  NLS_Text;
   protected String  NLS_DIL_Text;
   protected String  LangID;
   protected Integer FontSize;
   protected String  TextBold;
   protected String  TextItalic;
   protected String  TextUnderline;


   // ctor
   protected ControlImpl( EntityCursor cursor )
   {
      loadControlEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the DD_TargetKey
    */
   public String getDD_TargetKey( )
   {
      return DD_TargetKey;
   }

   /**
    * @param DD_TargetKey to set 
    */
   public void setDD_TargetKey( String DD_TargetKey )
   {
      this.DD_TargetKey = DD_TargetKey;
   }

   /**
    * @return the DD_SourceKey
    */
   public String getDD_SourceKey( )
   {
      return DD_SourceKey;
   }

   /**
    * @param DD_SourceKey to set 
    */
   public void setDD_SourceKey( String DD_SourceKey )
   {
      this.DD_SourceKey = DD_SourceKey;
   }

   /**
    * @return the OptionFlags
    */
   public Integer getOptionFlags( )
   {
      return OptionFlags;
   }

   /**
    * @param OptionFlags to set 
    */
   public void setOptionFlags( Integer OptionFlags )
   {
      this.OptionFlags = OptionFlags;
   }

   /**
    * @return the DD_Type
    */
   public String getDD_Type( )
   {
      return DD_Type;
   }

   /**
    * @param DD_Type to set 
    */
   public void setDD_Type( String DD_Type )
   {
      this.DD_Type = DD_Type;
   }

   /**
    * @return the IdNbr
    */
   public Integer getIdNbr( )
   {
      return IdNbr;
   }

   /**
    * @param IdNbr to set 
    */
   public void setIdNbr( Integer IdNbr )
   {
      this.IdNbr = IdNbr;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the CtrlBOI
    */
   public Blob getCtrlBOI( )
   {
      return CtrlBOI;
   }

   /**
    * @param CtrlBOI to set 
    */
   public void setCtrlBOI( Blob CtrlBOI )
   {
      this.CtrlBOI = CtrlBOI;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the SyncKey
    */
   public Integer getSyncKey( )
   {
      return SyncKey;
   }

   /**
    * @param SyncKey to set 
    */
   public void setSyncKey( Integer SyncKey )
   {
      this.SyncKey = SyncKey;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the Placeholder
    */
   public String getPlaceholder( )
   {
      return Placeholder;
   }

   /**
    * @param Placeholder to set 
    */
   public void setPlaceholder( String Placeholder )
   {
      this.Placeholder = Placeholder;
   }

   /**
    * @return the ReportGroupType
    */
   public String getReportGroupType( )
   {
      return ReportGroupType;
   }

   /**
    * @param ReportGroupType to set 
    */
   public void setReportGroupType( String ReportGroupType )
   {
      this.ReportGroupType = ReportGroupType;
   }

   /**
    * @return the ForceHeaderPerEntity
    */
   public String getForceHeaderPerEntity( )
   {
      return ForceHeaderPerEntity;
   }

   /**
    * @param ForceHeaderPerEntity to set 
    */
   public void setForceHeaderPerEntity( String ForceHeaderPerEntity )
   {
      this.ForceHeaderPerEntity = ForceHeaderPerEntity;
   }

   /**
    * @return the ExtendedStyle
    */
   public Integer getExtendedStyle( )
   {
      return ExtendedStyle;
   }

   /**
    * @param ExtendedStyle to set 
    */
   public void setExtendedStyle( Integer ExtendedStyle )
   {
      this.ExtendedStyle = ExtendedStyle;
   }

   /**
    * @return the GUID
    */
   public String getGUID( )
   {
      return GUID;
   }

   /**
    * @param GUID to set 
    */
   public void setGUID( String GUID )
   {
      this.GUID = GUID;
   }

   /**
    * @return the Properties
    */
   public Blob getProperties( )
   {
      return Properties;
   }

   /**
    * @param Properties to set 
    */
   public void setProperties( Blob Properties )
   {
      this.Properties = Properties;
   }

   /**
    * @return the LKey
    */
   public Blob getLKey( )
   {
      return LKey;
   }

   /**
    * @param LKey to set 
    */
   public void setLKey( Blob LKey )
   {
      this.LKey = LKey;
   }

   /**
    * @return the BorderWidth
    */
   public Integer getBorderWidth( )
   {
      return BorderWidth;
   }

   /**
    * @param BorderWidth to set 
    */
   public void setBorderWidth( Integer BorderWidth )
   {
      this.BorderWidth = BorderWidth;
   }

   /**
    * @return the BorderStyle
    */
   public Integer getBorderStyle( )
   {
      return BorderStyle;
   }

   /**
    * @param BorderStyle to set 
    */
   public void setBorderStyle( Integer BorderStyle )
   {
      this.BorderStyle = BorderStyle;
   }

   /**
    * @return the BorderTop
    */
   public Integer getBorderTop( )
   {
      return BorderTop;
   }

   /**
    * @param BorderTop to set 
    */
   public void setBorderTop( Integer BorderTop )
   {
      this.BorderTop = BorderTop;
   }

   /**
    * @return the BorderBottom
    */
   public Integer getBorderBottom( )
   {
      return BorderBottom;
   }

   /**
    * @param BorderBottom to set 
    */
   public void setBorderBottom( Integer BorderBottom )
   {
      this.BorderBottom = BorderBottom;
   }

   /**
    * @return the BorderLeft
    */
   public Integer getBorderLeft( )
   {
      return BorderLeft;
   }

   /**
    * @param BorderLeft to set 
    */
   public void setBorderLeft( Integer BorderLeft )
   {
      this.BorderLeft = BorderLeft;
   }

   /**
    * @return the BorderRight
    */
   public Integer getBorderRight( )
   {
      return BorderRight;
   }

   /**
    * @param BorderRight to set 
    */
   public void setBorderRight( Integer BorderRight )
   {
      this.BorderRight = BorderRight;
   }

   /**
    * @return the TextAlignHorizontal
    */
   public String getTextAlignHorizontal( )
   {
      return TextAlignHorizontal;
   }

   /**
    * @param TextAlignHorizontal to set 
    */
   public void setTextAlignHorizontal( String TextAlignHorizontal )
   {
      this.TextAlignHorizontal = TextAlignHorizontal;
   }

   /**
    * @return the VisibleBorder
    */
   public String getVisibleBorder( )
   {
      return VisibleBorder;
   }

   /**
    * @param VisibleBorder to set 
    */
   public void setVisibleBorder( String VisibleBorder )
   {
      this.VisibleBorder = VisibleBorder;
   }

   /**
    * @return the CenterJustify
    */
   public String getCenterJustify( )
   {
      return CenterJustify;
   }

   /**
    * @param CenterJustify to set 
    */
   public void setCenterJustify( String CenterJustify )
   {
      this.CenterJustify = CenterJustify;
   }

   /**
    * @return the RightJustify
    */
   public String getRightJustify( )
   {
      return RightJustify;
   }

   /**
    * @param RightJustify to set 
    */
   public void setRightJustify( String RightJustify )
   {
      this.RightJustify = RightJustify;
   }

   /**
    * @return the Disabled
    */
   public String getDisabled( )
   {
      return Disabled;
   }

   /**
    * @param Disabled to set 
    */
   public void setDisabled( String Disabled )
   {
      this.Disabled = Disabled;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the CSS_Id
    */
   public String getCSS_Id( )
   {
      return CSS_Id;
   }

   /**
    * @param CSS_Id to set 
    */
   public void setCSS_Id( String CSS_Id )
   {
      this.CSS_Id = CSS_Id;
   }

   /**
    * @return the CSS_Font
    */
   public String getCSS_Font( )
   {
      return CSS_Font;
   }

   /**
    * @param CSS_Font to set 
    */
   public void setCSS_Font( String CSS_Font )
   {
      this.CSS_Font = CSS_Font;
   }

   /**
    * @return the CSS_Position
    */
   public String getCSS_Position( )
   {
      return CSS_Position;
   }

   /**
    * @param CSS_Position to set 
    */
   public void setCSS_Position( String CSS_Position )
   {
      this.CSS_Position = CSS_Position;
   }

   /**
    * @return the CSS_Size
    */
   public String getCSS_Size( )
   {
      return CSS_Size;
   }

   /**
    * @param CSS_Size to set 
    */
   public void setCSS_Size( String CSS_Size )
   {
      this.CSS_Size = CSS_Size;
   }

   /**
    * @return the JavaScript
    */
   public String getJavaScript( )
   {
      return JavaScript;
   }

   /**
    * @param JavaScript to set 
    */
   public void setJavaScript( String JavaScript )
   {
      this.JavaScript = JavaScript;
   }

   /**
    * @return the RadioOrCheckboxValue
    */
   public String getRadioOrCheckboxValue( )
   {
      return RadioOrCheckboxValue;
   }

   /**
    * @param RadioOrCheckboxValue to set 
    */
   public void setRadioOrCheckboxValue( String RadioOrCheckboxValue )
   {
      this.RadioOrCheckboxValue = RadioOrCheckboxValue;
   }

   /**
    * @return the WebFileName
    */
   public String getWebFileName( )
   {
      return WebFileName;
   }

   /**
    * @param WebFileName to set 
    */
   public void setWebFileName( String WebFileName )
   {
      this.WebFileName = WebFileName;
   }

   /**
    * @return the WebCtrlLabelLink
    */
   public String getWebCtrlLabelLink( )
   {
      return WebCtrlLabelLink;
   }

   /**
    * @param WebCtrlLabelLink to set 
    */
   public void setWebCtrlLabelLink( String WebCtrlLabelLink )
   {
      this.WebCtrlLabelLink = WebCtrlLabelLink;
   }

   /**
    * @return the WebSelectSetName
    */
   public String getWebSelectSetName( )
   {
      return WebSelectSetName;
   }

   /**
    * @param WebSelectSetName to set 
    */
   public void setWebSelectSetName( String WebSelectSetName )
   {
      this.WebSelectSetName = WebSelectSetName;
   }

   /**
    * @return the WebCtrlType
    */
   public String getWebCtrlType( )
   {
      return WebCtrlType;
   }

   /**
    * @param WebCtrlType to set 
    */
   public void setWebCtrlType( String WebCtrlType )
   {
      this.WebCtrlType = WebCtrlType;
   }

   /**
    * @return the WebColumnSpan
    */
   public String getWebColumnSpan( )
   {
      return WebColumnSpan;
   }

   /**
    * @param WebColumnSpan to set 
    */
   public void setWebColumnSpan( String WebColumnSpan )
   {
      this.WebColumnSpan = WebColumnSpan;
   }

   /**
    * @return the WebWrap
    */
   public String getWebWrap( )
   {
      return WebWrap;
   }

   /**
    * @param WebWrap to set 
    */
   public void setWebWrap( String WebWrap )
   {
      this.WebWrap = WebWrap;
   }

   /**
    * @return the WebNoGridDataMessage
    */
   public String getWebNoGridDataMessage( )
   {
      return WebNoGridDataMessage;
   }

   /**
    * @param WebNoGridDataMessage to set 
    */
   public void setWebNoGridDataMessage( String WebNoGridDataMessage )
   {
      this.WebNoGridDataMessage = WebNoGridDataMessage;
   }

   /**
    * @return the WebNoGridDataMsgClass
    */
   public String getWebNoGridDataMsgClass( )
   {
      return WebNoGridDataMsgClass;
   }

   /**
    * @param WebNoGridDataMsgClass to set 
    */
   public void setWebNoGridDataMsgClass( String WebNoGridDataMsgClass )
   {
      this.WebNoGridDataMsgClass = WebNoGridDataMsgClass;
   }

   /**
    * @return the WebreCAPTCHAPublicKey
    */
   public String getWebreCAPTCHAPublicKey( )
   {
      return WebreCAPTCHAPublicKey;
   }

   /**
    * @param WebreCAPTCHAPublicKey to set 
    */
   public void setWebreCAPTCHAPublicKey( String WebreCAPTCHAPublicKey )
   {
      this.WebreCAPTCHAPublicKey = WebreCAPTCHAPublicKey;
   }

   /**
    * @return the WebreCAPTCHAPrivateKey
    */
   public String getWebreCAPTCHAPrivateKey( )
   {
      return WebreCAPTCHAPrivateKey;
   }

   /**
    * @param WebreCAPTCHAPrivateKey to set 
    */
   public void setWebreCAPTCHAPrivateKey( String WebreCAPTCHAPrivateKey )
   {
      this.WebreCAPTCHAPrivateKey = WebreCAPTCHAPrivateKey;
   }

   /**
    * @return the WebHTML5Attribute
    */
   public String getWebHTML5Attribute( )
   {
      return WebHTML5Attribute;
   }

   /**
    * @param WebHTML5Attribute to set 
    */
   public void setWebHTML5Attribute( String WebHTML5Attribute )
   {
      this.WebHTML5Attribute = WebHTML5Attribute;
   }

   /**
    * @return the WebPlaceholder
    */
   public String getWebPlaceholder( )
   {
      return WebPlaceholder;
   }

   /**
    * @param WebPlaceholder to set 
    */
   public void setWebPlaceholder( String WebPlaceholder )
   {
      this.WebPlaceholder = WebPlaceholder;
   }

   /**
    * @return the MenuName
    */
   public String getMenuName( )
   {
      return MenuName;
   }

   /**
    * @param MenuName to set 
    */
   public void setMenuName( String MenuName )
   {
      this.MenuName = MenuName;
   }

   /**
    * @return the DIL_Inherited
    */
   public String getDIL_Inherited( )
   {
      return DIL_Inherited;
   }

   /**
    * @param DIL_Inherited to set 
    */
   public void setDIL_Inherited( String DIL_Inherited )
   {
      this.DIL_Inherited = DIL_Inherited;
   }

   /**
    * @return the NLS_Text
    */
   public String getNLS_Text( )
   {
      return NLS_Text;
   }

   /**
    * @param NLS_Text to set 
    */
   public void setNLS_Text( String NLS_Text )
   {
      this.NLS_Text = NLS_Text;
   }

   /**
    * @return the NLS_DIL_Text
    */
   public String getNLS_DIL_Text( )
   {
      return NLS_DIL_Text;
   }

   /**
    * @param NLS_DIL_Text to set 
    */
   public void setNLS_DIL_Text( String NLS_DIL_Text )
   {
      this.NLS_DIL_Text = NLS_DIL_Text;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   /**
    * @return the FontSize
    */
   public Integer getFontSize( )
   {
      return FontSize;
   }

   /**
    * @param FontSize to set 
    */
   public void setFontSize( Integer FontSize )
   {
      this.FontSize = FontSize;
   }

   /**
    * @return the TextBold
    */
   public String getTextBold( )
   {
      return TextBold;
   }

   /**
    * @param TextBold to set 
    */
   public void setTextBold( String TextBold )
   {
      this.TextBold = TextBold;
   }

   /**
    * @return the TextItalic
    */
   public String getTextItalic( )
   {
      return TextItalic;
   }

   /**
    * @param TextItalic to set 
    */
   public void setTextItalic( String TextItalic )
   {
      this.TextItalic = TextItalic;
   }

   /**
    * @return the TextUnderline
    */
   public String getTextUnderline( )
   {
      return TextUnderline;
   }

   /**
    * @param TextUnderline to set 
    */
   public void setTextUnderline( String TextUnderline )
   {
      this.TextUnderline = TextUnderline;
   }

   public int loadControlEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      DD_TargetKey = cursor.getStringFromAttribute( "DD_TargetKey" );  if ( DD_TargetKey == null ) DD_TargetKey = "";
      DD_SourceKey = cursor.getStringFromAttribute( "DD_SourceKey" );  if ( DD_SourceKey == null ) DD_SourceKey = "";
      OptionFlags = cursor.getIntegerFromAttribute( "OptionFlags" );  if ( OptionFlags == null ) OptionFlags = 0;
      DD_Type = cursor.getStringFromAttribute( "DD_Type" );  if ( DD_Type == null ) DD_Type = "";
      IdNbr = cursor.getIntegerFromAttribute( "IdNbr" );  if ( IdNbr == null ) IdNbr = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      CtrlBOI = cursor.getBlobFromAttribute( "CtrlBOI" );
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      SyncKey = cursor.getIntegerFromAttribute( "SyncKey" );  if ( SyncKey == null ) SyncKey = 0;
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      Placeholder = cursor.getStringFromAttribute( "Placeholder" );  if ( Placeholder == null ) Placeholder = "";
      ReportGroupType = cursor.getStringFromAttribute( "ReportGroupType" );  if ( ReportGroupType == null ) ReportGroupType = "";
      ForceHeaderPerEntity = cursor.getStringFromAttribute( "ForceHeaderPerEntity" );  if ( ForceHeaderPerEntity == null ) ForceHeaderPerEntity = "";
      ExtendedStyle = cursor.getIntegerFromAttribute( "ExtendedStyle" );  if ( ExtendedStyle == null ) ExtendedStyle = 0;
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      Properties = cursor.getBlobFromAttribute( "Properties" );
      LKey = cursor.getBlobFromAttribute( "LKey" );
      BorderWidth = cursor.getIntegerFromAttribute( "BorderWidth" );  if ( BorderWidth == null ) BorderWidth = 0;
      BorderStyle = cursor.getIntegerFromAttribute( "BorderStyle" );  if ( BorderStyle == null ) BorderStyle = 0;
      BorderTop = cursor.getIntegerFromAttribute( "BorderTop" );  if ( BorderTop == null ) BorderTop = 0;
      BorderBottom = cursor.getIntegerFromAttribute( "BorderBottom" );  if ( BorderBottom == null ) BorderBottom = 0;
      BorderLeft = cursor.getIntegerFromAttribute( "BorderLeft" );  if ( BorderLeft == null ) BorderLeft = 0;
      BorderRight = cursor.getIntegerFromAttribute( "BorderRight" );  if ( BorderRight == null ) BorderRight = 0;
      TextAlignHorizontal = cursor.getStringFromAttribute( "TextAlignHorizontal" );  if ( TextAlignHorizontal == null ) TextAlignHorizontal = "";
      VisibleBorder = cursor.getStringFromAttribute( "VisibleBorder" );  if ( VisibleBorder == null ) VisibleBorder = "";
      CenterJustify = cursor.getStringFromAttribute( "CenterJustify" );  if ( CenterJustify == null ) CenterJustify = "";
      RightJustify = cursor.getStringFromAttribute( "RightJustify" );  if ( RightJustify == null ) RightJustify = "";
      Disabled = cursor.getStringFromAttribute( "Disabled" );  if ( Disabled == null ) Disabled = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      CSS_Id = cursor.getStringFromAttribute( "CSS_Id" );  if ( CSS_Id == null ) CSS_Id = "";
      CSS_Font = cursor.getStringFromAttribute( "CSS_Font" );  if ( CSS_Font == null ) CSS_Font = "";
      CSS_Position = cursor.getStringFromAttribute( "CSS_Position" );  if ( CSS_Position == null ) CSS_Position = "";
      CSS_Size = cursor.getStringFromAttribute( "CSS_Size" );  if ( CSS_Size == null ) CSS_Size = "";
      JavaScript = cursor.getStringFromAttribute( "JavaScript" );  if ( JavaScript == null ) JavaScript = "";
      RadioOrCheckboxValue = cursor.getStringFromAttribute( "RadioOrCheckboxValue" );  if ( RadioOrCheckboxValue == null ) RadioOrCheckboxValue = "";
      WebFileName = cursor.getStringFromAttribute( "WebFileName" );  if ( WebFileName == null ) WebFileName = "";
      WebCtrlLabelLink = cursor.getStringFromAttribute( "WebCtrlLabelLink" );  if ( WebCtrlLabelLink == null ) WebCtrlLabelLink = "";
      WebSelectSetName = cursor.getStringFromAttribute( "WebSelectSetName" );  if ( WebSelectSetName == null ) WebSelectSetName = "";
      WebCtrlType = cursor.getStringFromAttribute( "WebCtrlType" );  if ( WebCtrlType == null ) WebCtrlType = "";
      WebColumnSpan = cursor.getStringFromAttribute( "WebColumnSpan" );  if ( WebColumnSpan == null ) WebColumnSpan = "";
      WebWrap = cursor.getStringFromAttribute( "WebWrap" );  if ( WebWrap == null ) WebWrap = "";
      WebNoGridDataMessage = cursor.getStringFromAttribute( "WebNoGridDataMessage" );  if ( WebNoGridDataMessage == null ) WebNoGridDataMessage = "";
      WebNoGridDataMsgClass = cursor.getStringFromAttribute( "WebNoGridDataMsgClass" );  if ( WebNoGridDataMsgClass == null ) WebNoGridDataMsgClass = "";
      WebreCAPTCHAPublicKey = cursor.getStringFromAttribute( "WebreCAPTCHAPublicKey" );  if ( WebreCAPTCHAPublicKey == null ) WebreCAPTCHAPublicKey = "";
      WebreCAPTCHAPrivateKey = cursor.getStringFromAttribute( "WebreCAPTCHAPrivateKey" );  if ( WebreCAPTCHAPrivateKey == null ) WebreCAPTCHAPrivateKey = "";
      WebHTML5Attribute = cursor.getStringFromAttribute( "WebHTML5Attribute" );  if ( WebHTML5Attribute == null ) WebHTML5Attribute = "";
      WebPlaceholder = cursor.getStringFromAttribute( "WebPlaceholder" );  if ( WebPlaceholder == null ) WebPlaceholder = "";
      MenuName = cursor.getStringFromAttribute( "MenuName" );  if ( MenuName == null ) MenuName = "";
      DIL_Inherited = cursor.getStringFromAttribute( "DIL_Inherited" );  if ( DIL_Inherited == null ) DIL_Inherited = "";
      NLS_Text = cursor.getStringFromAttribute( "NLS_Text" );  if ( NLS_Text == null ) NLS_Text = "";
      NLS_DIL_Text = cursor.getStringFromAttribute( "NLS_DIL_Text" );  if ( NLS_DIL_Text == null ) NLS_DIL_Text = "";
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";
      FontSize = cursor.getIntegerFromAttribute( "FontSize" );  if ( FontSize == null ) FontSize = 0;
      TextBold = cursor.getStringFromAttribute( "TextBold" );  if ( TextBold == null ) TextBold = "";
      TextItalic = cursor.getStringFromAttribute( "TextItalic" );  if ( TextItalic == null ) TextItalic = "";
      TextUnderline = cursor.getStringFromAttribute( "TextUnderline" );  if ( TextUnderline == null ) TextUnderline = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlCtrlImpl implements CtrlCtrl
{
   protected String  Tag;
   protected String  Text;
   protected Integer ZKey;
   protected Integer Type;
   protected Integer Subtype;
   protected String  DD_TargetKey;
   protected String  DD_SourceKey;
   protected Integer OptionFlags;
   protected String  DD_Type;
   protected Integer IdNbr;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Blob    CtrlBOI;
   protected Integer Underline;
   protected Integer SyncKey;
   protected String  DIL_Text;
   protected String  Placeholder;
   protected String  ReportGroupType;
   protected String  ForceHeaderPerEntity;
   protected Integer ExtendedStyle;
   protected String  GUID;
   protected Blob    Properties;
   protected Blob    LKey;
   protected Integer BorderWidth;
   protected Integer BorderStyle;
   protected Integer BorderTop;
   protected Integer BorderBottom;
   protected Integer BorderLeft;
   protected Integer BorderRight;
   protected String  TextAlignHorizontal;
   protected String  VisibleBorder;
   protected String  CenterJustify;
   protected String  RightJustify;
   protected String  Disabled;
   protected String  CSS_Class;
   protected String  CSS_Id;
   protected String  CSS_Font;
   protected String  CSS_Position;
   protected String  CSS_Size;
   protected String  JavaScript;
   protected String  RadioOrCheckboxValue;
   protected String  WebFileName;
   protected String  WebCtrlLabelLink;
   protected String  WebSelectSetName;
   protected String  WebCtrlType;
   protected String  WebColumnSpan;
   protected String  WebWrap;
   protected String  WebNoGridDataMessage;
   protected String  WebNoGridDataMsgClass;
   protected String  WebreCAPTCHAPublicKey;
   protected String  WebreCAPTCHAPrivateKey;
   protected String  WebHTML5Attribute;
   protected String  WebPlaceholder;
   protected String  MenuName;
   protected String  DIL_Inherited;
   protected String  NLS_Text;
   protected String  NLS_DIL_Text;
   protected String  LangID;
   protected Integer FontSize;
   protected String  TextBold;
   protected String  TextItalic;
   protected String  TextUnderline;


   // ctor
   protected CtrlCtrlImpl( EntityCursor cursor )
   {
      loadCtrlCtrlEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the DD_TargetKey
    */
   public String getDD_TargetKey( )
   {
      return DD_TargetKey;
   }

   /**
    * @param DD_TargetKey to set 
    */
   public void setDD_TargetKey( String DD_TargetKey )
   {
      this.DD_TargetKey = DD_TargetKey;
   }

   /**
    * @return the DD_SourceKey
    */
   public String getDD_SourceKey( )
   {
      return DD_SourceKey;
   }

   /**
    * @param DD_SourceKey to set 
    */
   public void setDD_SourceKey( String DD_SourceKey )
   {
      this.DD_SourceKey = DD_SourceKey;
   }

   /**
    * @return the OptionFlags
    */
   public Integer getOptionFlags( )
   {
      return OptionFlags;
   }

   /**
    * @param OptionFlags to set 
    */
   public void setOptionFlags( Integer OptionFlags )
   {
      this.OptionFlags = OptionFlags;
   }

   /**
    * @return the DD_Type
    */
   public String getDD_Type( )
   {
      return DD_Type;
   }

   /**
    * @param DD_Type to set 
    */
   public void setDD_Type( String DD_Type )
   {
      this.DD_Type = DD_Type;
   }

   /**
    * @return the IdNbr
    */
   public Integer getIdNbr( )
   {
      return IdNbr;
   }

   /**
    * @param IdNbr to set 
    */
   public void setIdNbr( Integer IdNbr )
   {
      this.IdNbr = IdNbr;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the CtrlBOI
    */
   public Blob getCtrlBOI( )
   {
      return CtrlBOI;
   }

   /**
    * @param CtrlBOI to set 
    */
   public void setCtrlBOI( Blob CtrlBOI )
   {
      this.CtrlBOI = CtrlBOI;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the SyncKey
    */
   public Integer getSyncKey( )
   {
      return SyncKey;
   }

   /**
    * @param SyncKey to set 
    */
   public void setSyncKey( Integer SyncKey )
   {
      this.SyncKey = SyncKey;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the Placeholder
    */
   public String getPlaceholder( )
   {
      return Placeholder;
   }

   /**
    * @param Placeholder to set 
    */
   public void setPlaceholder( String Placeholder )
   {
      this.Placeholder = Placeholder;
   }

   /**
    * @return the ReportGroupType
    */
   public String getReportGroupType( )
   {
      return ReportGroupType;
   }

   /**
    * @param ReportGroupType to set 
    */
   public void setReportGroupType( String ReportGroupType )
   {
      this.ReportGroupType = ReportGroupType;
   }

   /**
    * @return the ForceHeaderPerEntity
    */
   public String getForceHeaderPerEntity( )
   {
      return ForceHeaderPerEntity;
   }

   /**
    * @param ForceHeaderPerEntity to set 
    */
   public void setForceHeaderPerEntity( String ForceHeaderPerEntity )
   {
      this.ForceHeaderPerEntity = ForceHeaderPerEntity;
   }

   /**
    * @return the ExtendedStyle
    */
   public Integer getExtendedStyle( )
   {
      return ExtendedStyle;
   }

   /**
    * @param ExtendedStyle to set 
    */
   public void setExtendedStyle( Integer ExtendedStyle )
   {
      this.ExtendedStyle = ExtendedStyle;
   }

   /**
    * @return the GUID
    */
   public String getGUID( )
   {
      return GUID;
   }

   /**
    * @param GUID to set 
    */
   public void setGUID( String GUID )
   {
      this.GUID = GUID;
   }

   /**
    * @return the Properties
    */
   public Blob getProperties( )
   {
      return Properties;
   }

   /**
    * @param Properties to set 
    */
   public void setProperties( Blob Properties )
   {
      this.Properties = Properties;
   }

   /**
    * @return the LKey
    */
   public Blob getLKey( )
   {
      return LKey;
   }

   /**
    * @param LKey to set 
    */
   public void setLKey( Blob LKey )
   {
      this.LKey = LKey;
   }

   /**
    * @return the BorderWidth
    */
   public Integer getBorderWidth( )
   {
      return BorderWidth;
   }

   /**
    * @param BorderWidth to set 
    */
   public void setBorderWidth( Integer BorderWidth )
   {
      this.BorderWidth = BorderWidth;
   }

   /**
    * @return the BorderStyle
    */
   public Integer getBorderStyle( )
   {
      return BorderStyle;
   }

   /**
    * @param BorderStyle to set 
    */
   public void setBorderStyle( Integer BorderStyle )
   {
      this.BorderStyle = BorderStyle;
   }

   /**
    * @return the BorderTop
    */
   public Integer getBorderTop( )
   {
      return BorderTop;
   }

   /**
    * @param BorderTop to set 
    */
   public void setBorderTop( Integer BorderTop )
   {
      this.BorderTop = BorderTop;
   }

   /**
    * @return the BorderBottom
    */
   public Integer getBorderBottom( )
   {
      return BorderBottom;
   }

   /**
    * @param BorderBottom to set 
    */
   public void setBorderBottom( Integer BorderBottom )
   {
      this.BorderBottom = BorderBottom;
   }

   /**
    * @return the BorderLeft
    */
   public Integer getBorderLeft( )
   {
      return BorderLeft;
   }

   /**
    * @param BorderLeft to set 
    */
   public void setBorderLeft( Integer BorderLeft )
   {
      this.BorderLeft = BorderLeft;
   }

   /**
    * @return the BorderRight
    */
   public Integer getBorderRight( )
   {
      return BorderRight;
   }

   /**
    * @param BorderRight to set 
    */
   public void setBorderRight( Integer BorderRight )
   {
      this.BorderRight = BorderRight;
   }

   /**
    * @return the TextAlignHorizontal
    */
   public String getTextAlignHorizontal( )
   {
      return TextAlignHorizontal;
   }

   /**
    * @param TextAlignHorizontal to set 
    */
   public void setTextAlignHorizontal( String TextAlignHorizontal )
   {
      this.TextAlignHorizontal = TextAlignHorizontal;
   }

   /**
    * @return the VisibleBorder
    */
   public String getVisibleBorder( )
   {
      return VisibleBorder;
   }

   /**
    * @param VisibleBorder to set 
    */
   public void setVisibleBorder( String VisibleBorder )
   {
      this.VisibleBorder = VisibleBorder;
   }

   /**
    * @return the CenterJustify
    */
   public String getCenterJustify( )
   {
      return CenterJustify;
   }

   /**
    * @param CenterJustify to set 
    */
   public void setCenterJustify( String CenterJustify )
   {
      this.CenterJustify = CenterJustify;
   }

   /**
    * @return the RightJustify
    */
   public String getRightJustify( )
   {
      return RightJustify;
   }

   /**
    * @param RightJustify to set 
    */
   public void setRightJustify( String RightJustify )
   {
      this.RightJustify = RightJustify;
   }

   /**
    * @return the Disabled
    */
   public String getDisabled( )
   {
      return Disabled;
   }

   /**
    * @param Disabled to set 
    */
   public void setDisabled( String Disabled )
   {
      this.Disabled = Disabled;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the CSS_Id
    */
   public String getCSS_Id( )
   {
      return CSS_Id;
   }

   /**
    * @param CSS_Id to set 
    */
   public void setCSS_Id( String CSS_Id )
   {
      this.CSS_Id = CSS_Id;
   }

   /**
    * @return the CSS_Font
    */
   public String getCSS_Font( )
   {
      return CSS_Font;
   }

   /**
    * @param CSS_Font to set 
    */
   public void setCSS_Font( String CSS_Font )
   {
      this.CSS_Font = CSS_Font;
   }

   /**
    * @return the CSS_Position
    */
   public String getCSS_Position( )
   {
      return CSS_Position;
   }

   /**
    * @param CSS_Position to set 
    */
   public void setCSS_Position( String CSS_Position )
   {
      this.CSS_Position = CSS_Position;
   }

   /**
    * @return the CSS_Size
    */
   public String getCSS_Size( )
   {
      return CSS_Size;
   }

   /**
    * @param CSS_Size to set 
    */
   public void setCSS_Size( String CSS_Size )
   {
      this.CSS_Size = CSS_Size;
   }

   /**
    * @return the JavaScript
    */
   public String getJavaScript( )
   {
      return JavaScript;
   }

   /**
    * @param JavaScript to set 
    */
   public void setJavaScript( String JavaScript )
   {
      this.JavaScript = JavaScript;
   }

   /**
    * @return the RadioOrCheckboxValue
    */
   public String getRadioOrCheckboxValue( )
   {
      return RadioOrCheckboxValue;
   }

   /**
    * @param RadioOrCheckboxValue to set 
    */
   public void setRadioOrCheckboxValue( String RadioOrCheckboxValue )
   {
      this.RadioOrCheckboxValue = RadioOrCheckboxValue;
   }

   /**
    * @return the WebFileName
    */
   public String getWebFileName( )
   {
      return WebFileName;
   }

   /**
    * @param WebFileName to set 
    */
   public void setWebFileName( String WebFileName )
   {
      this.WebFileName = WebFileName;
   }

   /**
    * @return the WebCtrlLabelLink
    */
   public String getWebCtrlLabelLink( )
   {
      return WebCtrlLabelLink;
   }

   /**
    * @param WebCtrlLabelLink to set 
    */
   public void setWebCtrlLabelLink( String WebCtrlLabelLink )
   {
      this.WebCtrlLabelLink = WebCtrlLabelLink;
   }

   /**
    * @return the WebSelectSetName
    */
   public String getWebSelectSetName( )
   {
      return WebSelectSetName;
   }

   /**
    * @param WebSelectSetName to set 
    */
   public void setWebSelectSetName( String WebSelectSetName )
   {
      this.WebSelectSetName = WebSelectSetName;
   }

   /**
    * @return the WebCtrlType
    */
   public String getWebCtrlType( )
   {
      return WebCtrlType;
   }

   /**
    * @param WebCtrlType to set 
    */
   public void setWebCtrlType( String WebCtrlType )
   {
      this.WebCtrlType = WebCtrlType;
   }

   /**
    * @return the WebColumnSpan
    */
   public String getWebColumnSpan( )
   {
      return WebColumnSpan;
   }

   /**
    * @param WebColumnSpan to set 
    */
   public void setWebColumnSpan( String WebColumnSpan )
   {
      this.WebColumnSpan = WebColumnSpan;
   }

   /**
    * @return the WebWrap
    */
   public String getWebWrap( )
   {
      return WebWrap;
   }

   /**
    * @param WebWrap to set 
    */
   public void setWebWrap( String WebWrap )
   {
      this.WebWrap = WebWrap;
   }

   /**
    * @return the WebNoGridDataMessage
    */
   public String getWebNoGridDataMessage( )
   {
      return WebNoGridDataMessage;
   }

   /**
    * @param WebNoGridDataMessage to set 
    */
   public void setWebNoGridDataMessage( String WebNoGridDataMessage )
   {
      this.WebNoGridDataMessage = WebNoGridDataMessage;
   }

   /**
    * @return the WebNoGridDataMsgClass
    */
   public String getWebNoGridDataMsgClass( )
   {
      return WebNoGridDataMsgClass;
   }

   /**
    * @param WebNoGridDataMsgClass to set 
    */
   public void setWebNoGridDataMsgClass( String WebNoGridDataMsgClass )
   {
      this.WebNoGridDataMsgClass = WebNoGridDataMsgClass;
   }

   /**
    * @return the WebreCAPTCHAPublicKey
    */
   public String getWebreCAPTCHAPublicKey( )
   {
      return WebreCAPTCHAPublicKey;
   }

   /**
    * @param WebreCAPTCHAPublicKey to set 
    */
   public void setWebreCAPTCHAPublicKey( String WebreCAPTCHAPublicKey )
   {
      this.WebreCAPTCHAPublicKey = WebreCAPTCHAPublicKey;
   }

   /**
    * @return the WebreCAPTCHAPrivateKey
    */
   public String getWebreCAPTCHAPrivateKey( )
   {
      return WebreCAPTCHAPrivateKey;
   }

   /**
    * @param WebreCAPTCHAPrivateKey to set 
    */
   public void setWebreCAPTCHAPrivateKey( String WebreCAPTCHAPrivateKey )
   {
      this.WebreCAPTCHAPrivateKey = WebreCAPTCHAPrivateKey;
   }

   /**
    * @return the WebHTML5Attribute
    */
   public String getWebHTML5Attribute( )
   {
      return WebHTML5Attribute;
   }

   /**
    * @param WebHTML5Attribute to set 
    */
   public void setWebHTML5Attribute( String WebHTML5Attribute )
   {
      this.WebHTML5Attribute = WebHTML5Attribute;
   }

   /**
    * @return the WebPlaceholder
    */
   public String getWebPlaceholder( )
   {
      return WebPlaceholder;
   }

   /**
    * @param WebPlaceholder to set 
    */
   public void setWebPlaceholder( String WebPlaceholder )
   {
      this.WebPlaceholder = WebPlaceholder;
   }

   /**
    * @return the MenuName
    */
   public String getMenuName( )
   {
      return MenuName;
   }

   /**
    * @param MenuName to set 
    */
   public void setMenuName( String MenuName )
   {
      this.MenuName = MenuName;
   }

   /**
    * @return the DIL_Inherited
    */
   public String getDIL_Inherited( )
   {
      return DIL_Inherited;
   }

   /**
    * @param DIL_Inherited to set 
    */
   public void setDIL_Inherited( String DIL_Inherited )
   {
      this.DIL_Inherited = DIL_Inherited;
   }

   /**
    * @return the NLS_Text
    */
   public String getNLS_Text( )
   {
      return NLS_Text;
   }

   /**
    * @param NLS_Text to set 
    */
   public void setNLS_Text( String NLS_Text )
   {
      this.NLS_Text = NLS_Text;
   }

   /**
    * @return the NLS_DIL_Text
    */
   public String getNLS_DIL_Text( )
   {
      return NLS_DIL_Text;
   }

   /**
    * @param NLS_DIL_Text to set 
    */
   public void setNLS_DIL_Text( String NLS_DIL_Text )
   {
      this.NLS_DIL_Text = NLS_DIL_Text;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   /**
    * @return the FontSize
    */
   public Integer getFontSize( )
   {
      return FontSize;
   }

   /**
    * @param FontSize to set 
    */
   public void setFontSize( Integer FontSize )
   {
      this.FontSize = FontSize;
   }

   /**
    * @return the TextBold
    */
   public String getTextBold( )
   {
      return TextBold;
   }

   /**
    * @param TextBold to set 
    */
   public void setTextBold( String TextBold )
   {
      this.TextBold = TextBold;
   }

   /**
    * @return the TextItalic
    */
   public String getTextItalic( )
   {
      return TextItalic;
   }

   /**
    * @param TextItalic to set 
    */
   public void setTextItalic( String TextItalic )
   {
      this.TextItalic = TextItalic;
   }

   /**
    * @return the TextUnderline
    */
   public String getTextUnderline( )
   {
      return TextUnderline;
   }

   /**
    * @param TextUnderline to set 
    */
   public void setTextUnderline( String TextUnderline )
   {
      this.TextUnderline = TextUnderline;
   }

   public int loadCtrlCtrlEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      DD_TargetKey = cursor.getStringFromAttribute( "DD_TargetKey" );  if ( DD_TargetKey == null ) DD_TargetKey = "";
      DD_SourceKey = cursor.getStringFromAttribute( "DD_SourceKey" );  if ( DD_SourceKey == null ) DD_SourceKey = "";
      OptionFlags = cursor.getIntegerFromAttribute( "OptionFlags" );  if ( OptionFlags == null ) OptionFlags = 0;
      DD_Type = cursor.getStringFromAttribute( "DD_Type" );  if ( DD_Type == null ) DD_Type = "";
      IdNbr = cursor.getIntegerFromAttribute( "IdNbr" );  if ( IdNbr == null ) IdNbr = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      CtrlBOI = cursor.getBlobFromAttribute( "CtrlBOI" );
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      SyncKey = cursor.getIntegerFromAttribute( "SyncKey" );  if ( SyncKey == null ) SyncKey = 0;
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      Placeholder = cursor.getStringFromAttribute( "Placeholder" );  if ( Placeholder == null ) Placeholder = "";
      ReportGroupType = cursor.getStringFromAttribute( "ReportGroupType" );  if ( ReportGroupType == null ) ReportGroupType = "";
      ForceHeaderPerEntity = cursor.getStringFromAttribute( "ForceHeaderPerEntity" );  if ( ForceHeaderPerEntity == null ) ForceHeaderPerEntity = "";
      ExtendedStyle = cursor.getIntegerFromAttribute( "ExtendedStyle" );  if ( ExtendedStyle == null ) ExtendedStyle = 0;
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      Properties = cursor.getBlobFromAttribute( "Properties" );
      LKey = cursor.getBlobFromAttribute( "LKey" );
      BorderWidth = cursor.getIntegerFromAttribute( "BorderWidth" );  if ( BorderWidth == null ) BorderWidth = 0;
      BorderStyle = cursor.getIntegerFromAttribute( "BorderStyle" );  if ( BorderStyle == null ) BorderStyle = 0;
      BorderTop = cursor.getIntegerFromAttribute( "BorderTop" );  if ( BorderTop == null ) BorderTop = 0;
      BorderBottom = cursor.getIntegerFromAttribute( "BorderBottom" );  if ( BorderBottom == null ) BorderBottom = 0;
      BorderLeft = cursor.getIntegerFromAttribute( "BorderLeft" );  if ( BorderLeft == null ) BorderLeft = 0;
      BorderRight = cursor.getIntegerFromAttribute( "BorderRight" );  if ( BorderRight == null ) BorderRight = 0;
      TextAlignHorizontal = cursor.getStringFromAttribute( "TextAlignHorizontal" );  if ( TextAlignHorizontal == null ) TextAlignHorizontal = "";
      VisibleBorder = cursor.getStringFromAttribute( "VisibleBorder" );  if ( VisibleBorder == null ) VisibleBorder = "";
      CenterJustify = cursor.getStringFromAttribute( "CenterJustify" );  if ( CenterJustify == null ) CenterJustify = "";
      RightJustify = cursor.getStringFromAttribute( "RightJustify" );  if ( RightJustify == null ) RightJustify = "";
      Disabled = cursor.getStringFromAttribute( "Disabled" );  if ( Disabled == null ) Disabled = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      CSS_Id = cursor.getStringFromAttribute( "CSS_Id" );  if ( CSS_Id == null ) CSS_Id = "";
      CSS_Font = cursor.getStringFromAttribute( "CSS_Font" );  if ( CSS_Font == null ) CSS_Font = "";
      CSS_Position = cursor.getStringFromAttribute( "CSS_Position" );  if ( CSS_Position == null ) CSS_Position = "";
      CSS_Size = cursor.getStringFromAttribute( "CSS_Size" );  if ( CSS_Size == null ) CSS_Size = "";
      JavaScript = cursor.getStringFromAttribute( "JavaScript" );  if ( JavaScript == null ) JavaScript = "";
      RadioOrCheckboxValue = cursor.getStringFromAttribute( "RadioOrCheckboxValue" );  if ( RadioOrCheckboxValue == null ) RadioOrCheckboxValue = "";
      WebFileName = cursor.getStringFromAttribute( "WebFileName" );  if ( WebFileName == null ) WebFileName = "";
      WebCtrlLabelLink = cursor.getStringFromAttribute( "WebCtrlLabelLink" );  if ( WebCtrlLabelLink == null ) WebCtrlLabelLink = "";
      WebSelectSetName = cursor.getStringFromAttribute( "WebSelectSetName" );  if ( WebSelectSetName == null ) WebSelectSetName = "";
      WebCtrlType = cursor.getStringFromAttribute( "WebCtrlType" );  if ( WebCtrlType == null ) WebCtrlType = "";
      WebColumnSpan = cursor.getStringFromAttribute( "WebColumnSpan" );  if ( WebColumnSpan == null ) WebColumnSpan = "";
      WebWrap = cursor.getStringFromAttribute( "WebWrap" );  if ( WebWrap == null ) WebWrap = "";
      WebNoGridDataMessage = cursor.getStringFromAttribute( "WebNoGridDataMessage" );  if ( WebNoGridDataMessage == null ) WebNoGridDataMessage = "";
      WebNoGridDataMsgClass = cursor.getStringFromAttribute( "WebNoGridDataMsgClass" );  if ( WebNoGridDataMsgClass == null ) WebNoGridDataMsgClass = "";
      WebreCAPTCHAPublicKey = cursor.getStringFromAttribute( "WebreCAPTCHAPublicKey" );  if ( WebreCAPTCHAPublicKey == null ) WebreCAPTCHAPublicKey = "";
      WebreCAPTCHAPrivateKey = cursor.getStringFromAttribute( "WebreCAPTCHAPrivateKey" );  if ( WebreCAPTCHAPrivateKey == null ) WebreCAPTCHAPrivateKey = "";
      WebHTML5Attribute = cursor.getStringFromAttribute( "WebHTML5Attribute" );  if ( WebHTML5Attribute == null ) WebHTML5Attribute = "";
      WebPlaceholder = cursor.getStringFromAttribute( "WebPlaceholder" );  if ( WebPlaceholder == null ) WebPlaceholder = "";
      MenuName = cursor.getStringFromAttribute( "MenuName" );  if ( MenuName == null ) MenuName = "";
      DIL_Inherited = cursor.getStringFromAttribute( "DIL_Inherited" );  if ( DIL_Inherited == null ) DIL_Inherited = "";
      NLS_Text = cursor.getStringFromAttribute( "NLS_Text" );  if ( NLS_Text == null ) NLS_Text = "";
      NLS_DIL_Text = cursor.getStringFromAttribute( "NLS_DIL_Text" );  if ( NLS_DIL_Text == null ) NLS_DIL_Text = "";
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";
      FontSize = cursor.getIntegerFromAttribute( "FontSize" );  if ( FontSize == null ) FontSize = 0;
      TextBold = cursor.getStringFromAttribute( "TextBold" );  if ( TextBold == null ) TextBold = "";
      TextItalic = cursor.getStringFromAttribute( "TextItalic" );  if ( TextItalic == null ) TextItalic = "";
      TextUnderline = cursor.getStringFromAttribute( "TextUnderline" );  if ( TextUnderline == null ) TextUnderline = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlMapImpl implements CtrlMap
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  Type;
   protected Integer SeqNo_DlgCtrl;
   protected Integer SeqNo_DlgAct;


   // ctor
   protected CtrlMapImpl( EntityCursor cursor )
   {
      loadCtrlMapEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the SeqNo_DlgCtrl
    */
   public Integer getSeqNo_DlgCtrl( )
   {
      return SeqNo_DlgCtrl;
   }

   /**
    * @param SeqNo_DlgCtrl to set 
    */
   public void setSeqNo_DlgCtrl( Integer SeqNo_DlgCtrl )
   {
      this.SeqNo_DlgCtrl = SeqNo_DlgCtrl;
   }

   /**
    * @return the SeqNo_DlgAct
    */
   public Integer getSeqNo_DlgAct( )
   {
      return SeqNo_DlgAct;
   }

   /**
    * @param SeqNo_DlgAct to set 
    */
   public void setSeqNo_DlgAct( Integer SeqNo_DlgAct )
   {
      this.SeqNo_DlgAct = SeqNo_DlgAct;
   }

   public int loadCtrlMapEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      SeqNo_DlgCtrl = cursor.getIntegerFromAttribute( "SeqNo_DlgCtrl" );  if ( SeqNo_DlgCtrl == null ) SeqNo_DlgCtrl = 0;
      SeqNo_DlgAct = cursor.getIntegerFromAttribute( "SeqNo_DlgAct" );  if ( SeqNo_DlgAct == null ) SeqNo_DlgAct = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlMapLOD_AttributeImpl implements CtrlMapLOD_Attribute
{
   protected Integer ZKey;
   protected Integer SeqNo_LOD_Entity;
   protected Integer SeqNo_UIS_Entity_M;
   protected Integer SeqNo_UIS_Entity_L;
   protected String  DB_DerivedValue;
   protected String  Work;
   protected String  Update;
   protected String  Init;
   protected String  Hidden;
   protected Integer SeqPriority;
   protected String  SeqOrder;
   protected String  DIL_Text;
   protected String  DIL_TextMsg;
   protected String  DIL_Inherited;
   protected String  XML_Simple;
   protected String  HashkeyType;
   protected String  HashkeyParentEntityName;


   // ctor
   protected CtrlMapLOD_AttributeImpl( EntityCursor cursor )
   {
      loadCtrlMapLOD_AttributeEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the SeqNo_LOD_Entity
    */
   public Integer getSeqNo_LOD_Entity( )
   {
      return SeqNo_LOD_Entity;
   }

   /**
    * @param SeqNo_LOD_Entity to set 
    */
   public void setSeqNo_LOD_Entity( Integer SeqNo_LOD_Entity )
   {
      this.SeqNo_LOD_Entity = SeqNo_LOD_Entity;
   }

   /**
    * @return the SeqNo_UIS_Entity_M
    */
   public Integer getSeqNo_UIS_Entity_M( )
   {
      return SeqNo_UIS_Entity_M;
   }

   /**
    * @param SeqNo_UIS_Entity_M to set 
    */
   public void setSeqNo_UIS_Entity_M( Integer SeqNo_UIS_Entity_M )
   {
      this.SeqNo_UIS_Entity_M = SeqNo_UIS_Entity_M;
   }

   /**
    * @return the SeqNo_UIS_Entity_L
    */
   public Integer getSeqNo_UIS_Entity_L( )
   {
      return SeqNo_UIS_Entity_L;
   }

   /**
    * @param SeqNo_UIS_Entity_L to set 
    */
   public void setSeqNo_UIS_Entity_L( Integer SeqNo_UIS_Entity_L )
   {
      this.SeqNo_UIS_Entity_L = SeqNo_UIS_Entity_L;
   }

   /**
    * @return the DB_DerivedValue
    */
   public String getDB_DerivedValue( )
   {
      return DB_DerivedValue;
   }

   /**
    * @param DB_DerivedValue to set 
    */
   public void setDB_DerivedValue( String DB_DerivedValue )
   {
      this.DB_DerivedValue = DB_DerivedValue;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the Init
    */
   public String getInit( )
   {
      return Init;
   }

   /**
    * @param Init to set 
    */
   public void setInit( String Init )
   {
      this.Init = Init;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the SeqPriority
    */
   public Integer getSeqPriority( )
   {
      return SeqPriority;
   }

   /**
    * @param SeqPriority to set 
    */
   public void setSeqPriority( Integer SeqPriority )
   {
      this.SeqPriority = SeqPriority;
   }

   /**
    * @return the SeqOrder
    */
   public String getSeqOrder( )
   {
      return SeqOrder;
   }

   /**
    * @param SeqOrder to set 
    */
   public void setSeqOrder( String SeqOrder )
   {
      this.SeqOrder = SeqOrder;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the DIL_TextMsg
    */
   public String getDIL_TextMsg( )
   {
      return DIL_TextMsg;
   }

   /**
    * @param DIL_TextMsg to set 
    */
   public void setDIL_TextMsg( String DIL_TextMsg )
   {
      this.DIL_TextMsg = DIL_TextMsg;
   }

   /**
    * @return the DIL_Inherited
    */
   public String getDIL_Inherited( )
   {
      return DIL_Inherited;
   }

   /**
    * @param DIL_Inherited to set 
    */
   public void setDIL_Inherited( String DIL_Inherited )
   {
      this.DIL_Inherited = DIL_Inherited;
   }

   /**
    * @return the XML_Simple
    */
   public String getXML_Simple( )
   {
      return XML_Simple;
   }

   /**
    * @param XML_Simple to set 
    */
   public void setXML_Simple( String XML_Simple )
   {
      this.XML_Simple = XML_Simple;
   }

   /**
    * @return the HashkeyType
    */
   public String getHashkeyType( )
   {
      return HashkeyType;
   }

   /**
    * @param HashkeyType to set 
    */
   public void setHashkeyType( String HashkeyType )
   {
      this.HashkeyType = HashkeyType;
   }

   /**
    * @return the HashkeyParentEntityName
    */
   public String getHashkeyParentEntityName( )
   {
      return HashkeyParentEntityName;
   }

   /**
    * @param HashkeyParentEntityName to set 
    */
   public void setHashkeyParentEntityName( String HashkeyParentEntityName )
   {
      this.HashkeyParentEntityName = HashkeyParentEntityName;
   }

   public int loadCtrlMapLOD_AttributeEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      SeqNo_LOD_Entity = cursor.getIntegerFromAttribute( "SeqNo_LOD_Entity" );  if ( SeqNo_LOD_Entity == null ) SeqNo_LOD_Entity = 0;
      SeqNo_UIS_Entity_M = cursor.getIntegerFromAttribute( "SeqNo_UIS_Entity_M" );  if ( SeqNo_UIS_Entity_M == null ) SeqNo_UIS_Entity_M = 0;
      SeqNo_UIS_Entity_L = cursor.getIntegerFromAttribute( "SeqNo_UIS_Entity_L" );  if ( SeqNo_UIS_Entity_L == null ) SeqNo_UIS_Entity_L = 0;
      DB_DerivedValue = cursor.getStringFromAttribute( "DB_DerivedValue" );  if ( DB_DerivedValue == null ) DB_DerivedValue = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      Init = cursor.getStringFromAttribute( "Init" );  if ( Init == null ) Init = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      SeqPriority = cursor.getIntegerFromAttribute( "SeqPriority" );  if ( SeqPriority == null ) SeqPriority = 0;
      SeqOrder = cursor.getStringFromAttribute( "SeqOrder" );  if ( SeqOrder == null ) SeqOrder = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      DIL_TextMsg = cursor.getStringFromAttribute( "DIL_TextMsg" );  if ( DIL_TextMsg == null ) DIL_TextMsg = "";
      DIL_Inherited = cursor.getStringFromAttribute( "DIL_Inherited" );  if ( DIL_Inherited == null ) DIL_Inherited = "";
      XML_Simple = cursor.getStringFromAttribute( "XML_Simple" );  if ( XML_Simple == null ) XML_Simple = "";
      HashkeyType = cursor.getStringFromAttribute( "HashkeyType" );  if ( HashkeyType == null ) HashkeyType = "";
      HashkeyParentEntityName = cursor.getStringFromAttribute( "HashkeyParentEntityName" );  if ( HashkeyParentEntityName == null ) HashkeyParentEntityName = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlMapRelatedEntityImpl implements CtrlMapRelatedEntity
{
   protected String  Name;
   protected String  IndentName;
   protected Integer IndentLvl;
   protected Integer ZKey;
   protected String  CreateConstraint;
   protected String  DeleteConstraint;
   protected String  IncludeConstraint;
   protected String  ExcludeConstraint;
   protected String  AcceptConstraint;
   protected String  CancelConstraint;
   protected Integer SeqNo;
   protected Integer DataLocking;
   protected Integer MultipleChildLimit;
   protected String  Create;
   protected String  Delete;
   protected String  Update;
   protected String  Include;
   protected String  InclSrc;
   protected String  Exclude;
   protected String  Hidden;
   protected String  Recursive;
   protected String  AutoCreate;
   protected String  Derived;
   protected String  SeqType;
   protected String  Work;
   protected String  ParentDeleteBehave;
   protected String  DupEntityInstance;
   protected String  DupRelationshipInstance;
   protected String  RelLinkIndicator;
   protected String  Desc;
   protected String  Abstract;
   protected String  XML_Name;
   protected String  LazyLoadFlag;
   protected String  ReportDisplayFlag;


   // ctor
   protected CtrlMapRelatedEntityImpl( EntityCursor cursor )
   {
      loadCtrlMapRelatedEntityEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the IndentName
    */
   public String getIndentName( )
   {
      return IndentName;
   }

   /**
    * @param IndentName to set 
    */
   public void setIndentName( String IndentName )
   {
      this.IndentName = IndentName;
   }

   /**
    * @return the IndentLvl
    */
   public Integer getIndentLvl( )
   {
      return IndentLvl;
   }

   /**
    * @param IndentLvl to set 
    */
   public void setIndentLvl( Integer IndentLvl )
   {
      this.IndentLvl = IndentLvl;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the CreateConstraint
    */
   public String getCreateConstraint( )
   {
      return CreateConstraint;
   }

   /**
    * @param CreateConstraint to set 
    */
   public void setCreateConstraint( String CreateConstraint )
   {
      this.CreateConstraint = CreateConstraint;
   }

   /**
    * @return the DeleteConstraint
    */
   public String getDeleteConstraint( )
   {
      return DeleteConstraint;
   }

   /**
    * @param DeleteConstraint to set 
    */
   public void setDeleteConstraint( String DeleteConstraint )
   {
      this.DeleteConstraint = DeleteConstraint;
   }

   /**
    * @return the IncludeConstraint
    */
   public String getIncludeConstraint( )
   {
      return IncludeConstraint;
   }

   /**
    * @param IncludeConstraint to set 
    */
   public void setIncludeConstraint( String IncludeConstraint )
   {
      this.IncludeConstraint = IncludeConstraint;
   }

   /**
    * @return the ExcludeConstraint
    */
   public String getExcludeConstraint( )
   {
      return ExcludeConstraint;
   }

   /**
    * @param ExcludeConstraint to set 
    */
   public void setExcludeConstraint( String ExcludeConstraint )
   {
      this.ExcludeConstraint = ExcludeConstraint;
   }

   /**
    * @return the AcceptConstraint
    */
   public String getAcceptConstraint( )
   {
      return AcceptConstraint;
   }

   /**
    * @param AcceptConstraint to set 
    */
   public void setAcceptConstraint( String AcceptConstraint )
   {
      this.AcceptConstraint = AcceptConstraint;
   }

   /**
    * @return the CancelConstraint
    */
   public String getCancelConstraint( )
   {
      return CancelConstraint;
   }

   /**
    * @param CancelConstraint to set 
    */
   public void setCancelConstraint( String CancelConstraint )
   {
      this.CancelConstraint = CancelConstraint;
   }

   /**
    * @return the SeqNo
    */
   public Integer getSeqNo( )
   {
      return SeqNo;
   }

   /**
    * @param SeqNo to set 
    */
   public void setSeqNo( Integer SeqNo )
   {
      this.SeqNo = SeqNo;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the MultipleChildLimit
    */
   public Integer getMultipleChildLimit( )
   {
      return MultipleChildLimit;
   }

   /**
    * @param MultipleChildLimit to set 
    */
   public void setMultipleChildLimit( Integer MultipleChildLimit )
   {
      this.MultipleChildLimit = MultipleChildLimit;
   }

   /**
    * @return the Create
    */
   public String getCreate( )
   {
      return Create;
   }

   /**
    * @param Create to set 
    */
   public void setCreate( String Create )
   {
      this.Create = Create;
   }

   /**
    * @return the Delete
    */
   public String getDelete( )
   {
      return Delete;
   }

   /**
    * @param Delete to set 
    */
   public void setDelete( String Delete )
   {
      this.Delete = Delete;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the Include
    */
   public String getInclude( )
   {
      return Include;
   }

   /**
    * @param Include to set 
    */
   public void setInclude( String Include )
   {
      this.Include = Include;
   }

   /**
    * @return the InclSrc
    */
   public String getInclSrc( )
   {
      return InclSrc;
   }

   /**
    * @param InclSrc to set 
    */
   public void setInclSrc( String InclSrc )
   {
      this.InclSrc = InclSrc;
   }

   /**
    * @return the Exclude
    */
   public String getExclude( )
   {
      return Exclude;
   }

   /**
    * @param Exclude to set 
    */
   public void setExclude( String Exclude )
   {
      this.Exclude = Exclude;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the Recursive
    */
   public String getRecursive( )
   {
      return Recursive;
   }

   /**
    * @param Recursive to set 
    */
   public void setRecursive( String Recursive )
   {
      this.Recursive = Recursive;
   }

   /**
    * @return the AutoCreate
    */
   public String getAutoCreate( )
   {
      return AutoCreate;
   }

   /**
    * @param AutoCreate to set 
    */
   public void setAutoCreate( String AutoCreate )
   {
      this.AutoCreate = AutoCreate;
   }

   /**
    * @return the Derived
    */
   public String getDerived( )
   {
      return Derived;
   }

   /**
    * @param Derived to set 
    */
   public void setDerived( String Derived )
   {
      this.Derived = Derived;
   }

   /**
    * @return the SeqType
    */
   public String getSeqType( )
   {
      return SeqType;
   }

   /**
    * @param SeqType to set 
    */
   public void setSeqType( String SeqType )
   {
      this.SeqType = SeqType;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the ParentDeleteBehave
    */
   public String getParentDeleteBehave( )
   {
      return ParentDeleteBehave;
   }

   /**
    * @param ParentDeleteBehave to set 
    */
   public void setParentDeleteBehave( String ParentDeleteBehave )
   {
      this.ParentDeleteBehave = ParentDeleteBehave;
   }

   /**
    * @return the DupEntityInstance
    */
   public String getDupEntityInstance( )
   {
      return DupEntityInstance;
   }

   /**
    * @param DupEntityInstance to set 
    */
   public void setDupEntityInstance( String DupEntityInstance )
   {
      this.DupEntityInstance = DupEntityInstance;
   }

   /**
    * @return the DupRelationshipInstance
    */
   public String getDupRelationshipInstance( )
   {
      return DupRelationshipInstance;
   }

   /**
    * @param DupRelationshipInstance to set 
    */
   public void setDupRelationshipInstance( String DupRelationshipInstance )
   {
      this.DupRelationshipInstance = DupRelationshipInstance;
   }

   /**
    * @return the RelLinkIndicator
    */
   public String getRelLinkIndicator( )
   {
      return RelLinkIndicator;
   }

   /**
    * @param RelLinkIndicator to set 
    */
   public void setRelLinkIndicator( String RelLinkIndicator )
   {
      this.RelLinkIndicator = RelLinkIndicator;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Abstract
    */
   public String getAbstract( )
   {
      return Abstract;
   }

   /**
    * @param Abstract to set 
    */
   public void setAbstract( String Abstract )
   {
      this.Abstract = Abstract;
   }

   /**
    * @return the XML_Name
    */
   public String getXML_Name( )
   {
      return XML_Name;
   }

   /**
    * @param XML_Name to set 
    */
   public void setXML_Name( String XML_Name )
   {
      this.XML_Name = XML_Name;
   }

   /**
    * @return the LazyLoadFlag
    */
   public String getLazyLoadFlag( )
   {
      return LazyLoadFlag;
   }

   /**
    * @param LazyLoadFlag to set 
    */
   public void setLazyLoadFlag( String LazyLoadFlag )
   {
      this.LazyLoadFlag = LazyLoadFlag;
   }

   /**
    * @return the ReportDisplayFlag
    */
   public String getReportDisplayFlag( )
   {
      return ReportDisplayFlag;
   }

   /**
    * @param ReportDisplayFlag to set 
    */
   public void setReportDisplayFlag( String ReportDisplayFlag )
   {
      this.ReportDisplayFlag = ReportDisplayFlag;
   }

   public int loadCtrlMapRelatedEntityEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      IndentName = cursor.getStringFromAttribute( "IndentName" );  if ( IndentName == null ) IndentName = "";
      IndentLvl = cursor.getIntegerFromAttribute( "IndentLvl" );  if ( IndentLvl == null ) IndentLvl = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      CreateConstraint = cursor.getStringFromAttribute( "CreateConstraint" );  if ( CreateConstraint == null ) CreateConstraint = "";
      DeleteConstraint = cursor.getStringFromAttribute( "DeleteConstraint" );  if ( DeleteConstraint == null ) DeleteConstraint = "";
      IncludeConstraint = cursor.getStringFromAttribute( "IncludeConstraint" );  if ( IncludeConstraint == null ) IncludeConstraint = "";
      ExcludeConstraint = cursor.getStringFromAttribute( "ExcludeConstraint" );  if ( ExcludeConstraint == null ) ExcludeConstraint = "";
      AcceptConstraint = cursor.getStringFromAttribute( "AcceptConstraint" );  if ( AcceptConstraint == null ) AcceptConstraint = "";
      CancelConstraint = cursor.getStringFromAttribute( "CancelConstraint" );  if ( CancelConstraint == null ) CancelConstraint = "";
      SeqNo = cursor.getIntegerFromAttribute( "SeqNo" );  if ( SeqNo == null ) SeqNo = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      MultipleChildLimit = cursor.getIntegerFromAttribute( "MultipleChildLimit" );  if ( MultipleChildLimit == null ) MultipleChildLimit = 0;
      Create = cursor.getStringFromAttribute( "Create" );  if ( Create == null ) Create = "";
      Delete = cursor.getStringFromAttribute( "Delete" );  if ( Delete == null ) Delete = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      Include = cursor.getStringFromAttribute( "Include" );  if ( Include == null ) Include = "";
      InclSrc = cursor.getStringFromAttribute( "InclSrc" );  if ( InclSrc == null ) InclSrc = "";
      Exclude = cursor.getStringFromAttribute( "Exclude" );  if ( Exclude == null ) Exclude = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      Recursive = cursor.getStringFromAttribute( "Recursive" );  if ( Recursive == null ) Recursive = "";
      AutoCreate = cursor.getStringFromAttribute( "AutoCreate" );  if ( AutoCreate == null ) AutoCreate = "";
      Derived = cursor.getStringFromAttribute( "Derived" );  if ( Derived == null ) Derived = "";
      SeqType = cursor.getStringFromAttribute( "SeqType" );  if ( SeqType == null ) SeqType = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      ParentDeleteBehave = cursor.getStringFromAttribute( "ParentDeleteBehave" );  if ( ParentDeleteBehave == null ) ParentDeleteBehave = "";
      DupEntityInstance = cursor.getStringFromAttribute( "DupEntityInstance" );  if ( DupEntityInstance == null ) DupEntityInstance = "";
      DupRelationshipInstance = cursor.getStringFromAttribute( "DupRelationshipInstance" );  if ( DupRelationshipInstance == null ) DupRelationshipInstance = "";
      RelLinkIndicator = cursor.getStringFromAttribute( "RelLinkIndicator" );  if ( RelLinkIndicator == null ) RelLinkIndicator = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Abstract = cursor.getStringFromAttribute( "Abstract" );  if ( Abstract == null ) Abstract = "";
      XML_Name = cursor.getStringFromAttribute( "XML_Name" );  if ( XML_Name == null ) XML_Name = "";
      LazyLoadFlag = cursor.getStringFromAttribute( "LazyLoadFlag" );  if ( LazyLoadFlag == null ) LazyLoadFlag = "";
      ReportDisplayFlag = cursor.getStringFromAttribute( "ReportDisplayFlag" );  if ( ReportDisplayFlag == null ) ReportDisplayFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlMapER_AttributeImpl implements CtrlMapER_Attribute
{
   protected String  Name;
   protected String  CaseSens;
   protected String  TE_ColumnName;
   protected String  TE_ForeignKeyName;
   protected String  Work;
   protected String  DerivedExpression;
   protected Integer ZKey;
   protected Integer Lth;
   protected String  Key;
   protected String  NotNull;
   protected String  Desc;
   protected String  PromptPaintLit;
   protected Integer PromptPaintLth;
   protected String  ListPaintLit;
   protected Integer ListPaintLth;
   protected String  ADW_Position;
   protected Blob    DerivedExpressionXPG;
   protected Integer Sequence;
   protected Integer SAP_Attribute;
   protected String  XML_SimpleName;
   protected String  XML_NameExternal;


   // ctor
   protected CtrlMapER_AttributeImpl( EntityCursor cursor )
   {
      loadCtrlMapER_AttributeEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the CaseSens
    */
   public String getCaseSens( )
   {
      return CaseSens;
   }

   /**
    * @param CaseSens to set 
    */
   public void setCaseSens( String CaseSens )
   {
      this.CaseSens = CaseSens;
   }

   /**
    * @return the TE_ColumnName
    */
   public String getTE_ColumnName( )
   {
      return TE_ColumnName;
   }

   /**
    * @param TE_ColumnName to set 
    */
   public void setTE_ColumnName( String TE_ColumnName )
   {
      this.TE_ColumnName = TE_ColumnName;
   }

   /**
    * @return the TE_ForeignKeyName
    */
   public String getTE_ForeignKeyName( )
   {
      return TE_ForeignKeyName;
   }

   /**
    * @param TE_ForeignKeyName to set 
    */
   public void setTE_ForeignKeyName( String TE_ForeignKeyName )
   {
      this.TE_ForeignKeyName = TE_ForeignKeyName;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the DerivedExpression
    */
   public String getDerivedExpression( )
   {
      return DerivedExpression;
   }

   /**
    * @param DerivedExpression to set 
    */
   public void setDerivedExpression( String DerivedExpression )
   {
      this.DerivedExpression = DerivedExpression;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Lth
    */
   public Integer getLth( )
   {
      return Lth;
   }

   /**
    * @param Lth to set 
    */
   public void setLth( Integer Lth )
   {
      this.Lth = Lth;
   }

   /**
    * @return the Key
    */
   public String getKey( )
   {
      return Key;
   }

   /**
    * @param Key to set 
    */
   public void setKey( String Key )
   {
      this.Key = Key;
   }

   /**
    * @return the NotNull
    */
   public String getNotNull( )
   {
      return NotNull;
   }

   /**
    * @param NotNull to set 
    */
   public void setNotNull( String NotNull )
   {
      this.NotNull = NotNull;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the PromptPaintLit
    */
   public String getPromptPaintLit( )
   {
      return PromptPaintLit;
   }

   /**
    * @param PromptPaintLit to set 
    */
   public void setPromptPaintLit( String PromptPaintLit )
   {
      this.PromptPaintLit = PromptPaintLit;
   }

   /**
    * @return the PromptPaintLth
    */
   public Integer getPromptPaintLth( )
   {
      return PromptPaintLth;
   }

   /**
    * @param PromptPaintLth to set 
    */
   public void setPromptPaintLth( Integer PromptPaintLth )
   {
      this.PromptPaintLth = PromptPaintLth;
   }

   /**
    * @return the ListPaintLit
    */
   public String getListPaintLit( )
   {
      return ListPaintLit;
   }

   /**
    * @param ListPaintLit to set 
    */
   public void setListPaintLit( String ListPaintLit )
   {
      this.ListPaintLit = ListPaintLit;
   }

   /**
    * @return the ListPaintLth
    */
   public Integer getListPaintLth( )
   {
      return ListPaintLth;
   }

   /**
    * @param ListPaintLth to set 
    */
   public void setListPaintLth( Integer ListPaintLth )
   {
      this.ListPaintLth = ListPaintLth;
   }

   /**
    * @return the ADW_Position
    */
   public String getADW_Position( )
   {
      return ADW_Position;
   }

   /**
    * @param ADW_Position to set 
    */
   public void setADW_Position( String ADW_Position )
   {
      this.ADW_Position = ADW_Position;
   }

   /**
    * @return the DerivedExpressionXPG
    */
   public Blob getDerivedExpressionXPG( )
   {
      return DerivedExpressionXPG;
   }

   /**
    * @param DerivedExpressionXPG to set 
    */
   public void setDerivedExpressionXPG( Blob DerivedExpressionXPG )
   {
      this.DerivedExpressionXPG = DerivedExpressionXPG;
   }

   /**
    * @return the Sequence
    */
   public Integer getSequence( )
   {
      return Sequence;
   }

   /**
    * @param Sequence to set 
    */
   public void setSequence( Integer Sequence )
   {
      this.Sequence = Sequence;
   }

   /**
    * @return the SAP_Attribute
    */
   public Integer getSAP_Attribute( )
   {
      return SAP_Attribute;
   }

   /**
    * @param SAP_Attribute to set 
    */
   public void setSAP_Attribute( Integer SAP_Attribute )
   {
      this.SAP_Attribute = SAP_Attribute;
   }

   /**
    * @return the XML_SimpleName
    */
   public String getXML_SimpleName( )
   {
      return XML_SimpleName;
   }

   /**
    * @param XML_SimpleName to set 
    */
   public void setXML_SimpleName( String XML_SimpleName )
   {
      this.XML_SimpleName = XML_SimpleName;
   }

   /**
    * @return the XML_NameExternal
    */
   public String getXML_NameExternal( )
   {
      return XML_NameExternal;
   }

   /**
    * @param XML_NameExternal to set 
    */
   public void setXML_NameExternal( String XML_NameExternal )
   {
      this.XML_NameExternal = XML_NameExternal;
   }

   public int loadCtrlMapER_AttributeEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      CaseSens = cursor.getStringFromAttribute( "CaseSens" );  if ( CaseSens == null ) CaseSens = "";
      TE_ColumnName = cursor.getStringFromAttribute( "TE_ColumnName" );  if ( TE_ColumnName == null ) TE_ColumnName = "";
      TE_ForeignKeyName = cursor.getStringFromAttribute( "TE_ForeignKeyName" );  if ( TE_ForeignKeyName == null ) TE_ForeignKeyName = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      DerivedExpression = cursor.getStringFromAttribute( "DerivedExpression" );  if ( DerivedExpression == null ) DerivedExpression = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Lth = cursor.getIntegerFromAttribute( "Lth" );  if ( Lth == null ) Lth = 0;
      Key = cursor.getStringFromAttribute( "Key" );  if ( Key == null ) Key = "";
      NotNull = cursor.getStringFromAttribute( "NotNull" );  if ( NotNull == null ) NotNull = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      PromptPaintLit = cursor.getStringFromAttribute( "PromptPaintLit" );  if ( PromptPaintLit == null ) PromptPaintLit = "";
      PromptPaintLth = cursor.getIntegerFromAttribute( "PromptPaintLth" );  if ( PromptPaintLth == null ) PromptPaintLth = 0;
      ListPaintLit = cursor.getStringFromAttribute( "ListPaintLit" );  if ( ListPaintLit == null ) ListPaintLit = "";
      ListPaintLth = cursor.getIntegerFromAttribute( "ListPaintLth" );  if ( ListPaintLth == null ) ListPaintLth = 0;
      ADW_Position = cursor.getStringFromAttribute( "ADW_Position" );  if ( ADW_Position == null ) ADW_Position = "";
      DerivedExpressionXPG = cursor.getBlobFromAttribute( "DerivedExpressionXPG" );
      Sequence = cursor.getIntegerFromAttribute( "Sequence" );  if ( Sequence == null ) Sequence = 0;
      SAP_Attribute = cursor.getIntegerFromAttribute( "SAP_Attribute" );  if ( SAP_Attribute == null ) SAP_Attribute = 0;
      XML_SimpleName = cursor.getStringFromAttribute( "XML_SimpleName" );  if ( XML_SimpleName == null ) XML_SimpleName = "";
      XML_NameExternal = cursor.getStringFromAttribute( "XML_NameExternal" );  if ( XML_NameExternal == null ) XML_NameExternal = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlMapER_DomainImpl implements CtrlMapER_Domain
{
   protected Integer ZKey;
   protected String  Desc;
   protected String  LastSyncDate;
   protected String  DerivedName;
   protected String  DerivedDataType;
   protected Integer DerivedMaxStringLth;
   protected Integer DerivedDecimalFormat;
   protected String  Name;
   protected String  DomainType;
   protected String  DataType;
   protected Integer MaxStringLth;
   protected String  ContextRestriction;
   protected Integer DecimalFormat;
   protected String  ConstraintRule;


   // ctor
   protected CtrlMapER_DomainImpl( EntityCursor cursor )
   {
      loadCtrlMapER_DomainEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the DerivedName
    */
   public String getDerivedName( )
   {
      return DerivedName;
   }

   /**
    * @param DerivedName to set 
    */
   public void setDerivedName( String DerivedName )
   {
      this.DerivedName = DerivedName;
   }

   /**
    * @return the DerivedDataType
    */
   public String getDerivedDataType( )
   {
      return DerivedDataType;
   }

   /**
    * @param DerivedDataType to set 
    */
   public void setDerivedDataType( String DerivedDataType )
   {
      this.DerivedDataType = DerivedDataType;
   }

   /**
    * @return the DerivedMaxStringLth
    */
   public Integer getDerivedMaxStringLth( )
   {
      return DerivedMaxStringLth;
   }

   /**
    * @param DerivedMaxStringLth to set 
    */
   public void setDerivedMaxStringLth( Integer DerivedMaxStringLth )
   {
      this.DerivedMaxStringLth = DerivedMaxStringLth;
   }

   /**
    * @return the DerivedDecimalFormat
    */
   public Integer getDerivedDecimalFormat( )
   {
      return DerivedDecimalFormat;
   }

   /**
    * @param DerivedDecimalFormat to set 
    */
   public void setDerivedDecimalFormat( Integer DerivedDecimalFormat )
   {
      this.DerivedDecimalFormat = DerivedDecimalFormat;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the DomainType
    */
   public String getDomainType( )
   {
      return DomainType;
   }

   /**
    * @param DomainType to set 
    */
   public void setDomainType( String DomainType )
   {
      this.DomainType = DomainType;
   }

   /**
    * @return the DataType
    */
   public String getDataType( )
   {
      return DataType;
   }

   /**
    * @param DataType to set 
    */
   public void setDataType( String DataType )
   {
      this.DataType = DataType;
   }

   /**
    * @return the MaxStringLth
    */
   public Integer getMaxStringLth( )
   {
      return MaxStringLth;
   }

   /**
    * @param MaxStringLth to set 
    */
   public void setMaxStringLth( Integer MaxStringLth )
   {
      this.MaxStringLth = MaxStringLth;
   }

   /**
    * @return the ContextRestriction
    */
   public String getContextRestriction( )
   {
      return ContextRestriction;
   }

   /**
    * @param ContextRestriction to set 
    */
   public void setContextRestriction( String ContextRestriction )
   {
      this.ContextRestriction = ContextRestriction;
   }

   /**
    * @return the DecimalFormat
    */
   public Integer getDecimalFormat( )
   {
      return DecimalFormat;
   }

   /**
    * @param DecimalFormat to set 
    */
   public void setDecimalFormat( Integer DecimalFormat )
   {
      this.DecimalFormat = DecimalFormat;
   }

   /**
    * @return the ConstraintRule
    */
   public String getConstraintRule( )
   {
      return ConstraintRule;
   }

   /**
    * @param ConstraintRule to set 
    */
   public void setConstraintRule( String ConstraintRule )
   {
      this.ConstraintRule = ConstraintRule;
   }

   public int loadCtrlMapER_DomainEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      DerivedName = cursor.getStringFromAttribute( "DerivedName" );  if ( DerivedName == null ) DerivedName = "";
      DerivedDataType = cursor.getStringFromAttribute( "DerivedDataType" );  if ( DerivedDataType == null ) DerivedDataType = "";
      DerivedMaxStringLth = cursor.getIntegerFromAttribute( "DerivedMaxStringLth" );  if ( DerivedMaxStringLth == null ) DerivedMaxStringLth = 0;
      DerivedDecimalFormat = cursor.getIntegerFromAttribute( "DerivedDecimalFormat" );  if ( DerivedDecimalFormat == null ) DerivedDecimalFormat = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      DomainType = cursor.getStringFromAttribute( "DomainType" );  if ( DomainType == null ) DomainType = "";
      DataType = cursor.getStringFromAttribute( "DataType" );  if ( DataType == null ) DataType = "";
      MaxStringLth = cursor.getIntegerFromAttribute( "MaxStringLth" );  if ( MaxStringLth == null ) MaxStringLth = 0;
      ContextRestriction = cursor.getStringFromAttribute( "ContextRestriction" );  if ( ContextRestriction == null ) ContextRestriction = "";
      DecimalFormat = cursor.getIntegerFromAttribute( "DecimalFormat" );  if ( DecimalFormat == null ) DecimalFormat = 0;
      ConstraintRule = cursor.getStringFromAttribute( "ConstraintRule" );  if ( ConstraintRule == null ) ConstraintRule = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlMapLOD_EntityImpl implements CtrlMapLOD_Entity
{
   protected String  Name;
   protected String  IndentName;
   protected Integer IndentLvl;
   protected Integer ZKey;
   protected String  Create;
   protected String  Delete;
   protected String  Update;
   protected String  CreateConstraint;
   protected String  DeleteConstraint;
   protected String  IncludeConstraint;
   protected String  ExcludeConstraint;
   protected String  AcceptConstraint;
   protected String  CancelConstraint;
   protected Integer SeqNo;
   protected Integer DataLocking;
   protected Integer MultipleChildLimit;
   protected String  Include;
   protected String  InclSrc;
   protected String  Exclude;
   protected String  Hidden;
   protected String  Recursive;
   protected String  AutoCreate;
   protected String  Derived;
   protected String  SeqType;
   protected String  Work;
   protected String  ParentDeleteBehave;
   protected String  DupEntityInstance;
   protected String  DupRelationshipInstance;
   protected String  RelLinkIndicator;
   protected String  Desc;
   protected String  Abstract;
   protected String  XML_Name;
   protected String  LazyLoadFlag;
   protected String  ReportDisplayFlag;


   // ctor
   protected CtrlMapLOD_EntityImpl( EntityCursor cursor )
   {
      loadCtrlMapLOD_EntityEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the IndentName
    */
   public String getIndentName( )
   {
      return IndentName;
   }

   /**
    * @param IndentName to set 
    */
   public void setIndentName( String IndentName )
   {
      this.IndentName = IndentName;
   }

   /**
    * @return the IndentLvl
    */
   public Integer getIndentLvl( )
   {
      return IndentLvl;
   }

   /**
    * @param IndentLvl to set 
    */
   public void setIndentLvl( Integer IndentLvl )
   {
      this.IndentLvl = IndentLvl;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Create
    */
   public String getCreate( )
   {
      return Create;
   }

   /**
    * @param Create to set 
    */
   public void setCreate( String Create )
   {
      this.Create = Create;
   }

   /**
    * @return the Delete
    */
   public String getDelete( )
   {
      return Delete;
   }

   /**
    * @param Delete to set 
    */
   public void setDelete( String Delete )
   {
      this.Delete = Delete;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the CreateConstraint
    */
   public String getCreateConstraint( )
   {
      return CreateConstraint;
   }

   /**
    * @param CreateConstraint to set 
    */
   public void setCreateConstraint( String CreateConstraint )
   {
      this.CreateConstraint = CreateConstraint;
   }

   /**
    * @return the DeleteConstraint
    */
   public String getDeleteConstraint( )
   {
      return DeleteConstraint;
   }

   /**
    * @param DeleteConstraint to set 
    */
   public void setDeleteConstraint( String DeleteConstraint )
   {
      this.DeleteConstraint = DeleteConstraint;
   }

   /**
    * @return the IncludeConstraint
    */
   public String getIncludeConstraint( )
   {
      return IncludeConstraint;
   }

   /**
    * @param IncludeConstraint to set 
    */
   public void setIncludeConstraint( String IncludeConstraint )
   {
      this.IncludeConstraint = IncludeConstraint;
   }

   /**
    * @return the ExcludeConstraint
    */
   public String getExcludeConstraint( )
   {
      return ExcludeConstraint;
   }

   /**
    * @param ExcludeConstraint to set 
    */
   public void setExcludeConstraint( String ExcludeConstraint )
   {
      this.ExcludeConstraint = ExcludeConstraint;
   }

   /**
    * @return the AcceptConstraint
    */
   public String getAcceptConstraint( )
   {
      return AcceptConstraint;
   }

   /**
    * @param AcceptConstraint to set 
    */
   public void setAcceptConstraint( String AcceptConstraint )
   {
      this.AcceptConstraint = AcceptConstraint;
   }

   /**
    * @return the CancelConstraint
    */
   public String getCancelConstraint( )
   {
      return CancelConstraint;
   }

   /**
    * @param CancelConstraint to set 
    */
   public void setCancelConstraint( String CancelConstraint )
   {
      this.CancelConstraint = CancelConstraint;
   }

   /**
    * @return the SeqNo
    */
   public Integer getSeqNo( )
   {
      return SeqNo;
   }

   /**
    * @param SeqNo to set 
    */
   public void setSeqNo( Integer SeqNo )
   {
      this.SeqNo = SeqNo;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the MultipleChildLimit
    */
   public Integer getMultipleChildLimit( )
   {
      return MultipleChildLimit;
   }

   /**
    * @param MultipleChildLimit to set 
    */
   public void setMultipleChildLimit( Integer MultipleChildLimit )
   {
      this.MultipleChildLimit = MultipleChildLimit;
   }

   /**
    * @return the Include
    */
   public String getInclude( )
   {
      return Include;
   }

   /**
    * @param Include to set 
    */
   public void setInclude( String Include )
   {
      this.Include = Include;
   }

   /**
    * @return the InclSrc
    */
   public String getInclSrc( )
   {
      return InclSrc;
   }

   /**
    * @param InclSrc to set 
    */
   public void setInclSrc( String InclSrc )
   {
      this.InclSrc = InclSrc;
   }

   /**
    * @return the Exclude
    */
   public String getExclude( )
   {
      return Exclude;
   }

   /**
    * @param Exclude to set 
    */
   public void setExclude( String Exclude )
   {
      this.Exclude = Exclude;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the Recursive
    */
   public String getRecursive( )
   {
      return Recursive;
   }

   /**
    * @param Recursive to set 
    */
   public void setRecursive( String Recursive )
   {
      this.Recursive = Recursive;
   }

   /**
    * @return the AutoCreate
    */
   public String getAutoCreate( )
   {
      return AutoCreate;
   }

   /**
    * @param AutoCreate to set 
    */
   public void setAutoCreate( String AutoCreate )
   {
      this.AutoCreate = AutoCreate;
   }

   /**
    * @return the Derived
    */
   public String getDerived( )
   {
      return Derived;
   }

   /**
    * @param Derived to set 
    */
   public void setDerived( String Derived )
   {
      this.Derived = Derived;
   }

   /**
    * @return the SeqType
    */
   public String getSeqType( )
   {
      return SeqType;
   }

   /**
    * @param SeqType to set 
    */
   public void setSeqType( String SeqType )
   {
      this.SeqType = SeqType;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the ParentDeleteBehave
    */
   public String getParentDeleteBehave( )
   {
      return ParentDeleteBehave;
   }

   /**
    * @param ParentDeleteBehave to set 
    */
   public void setParentDeleteBehave( String ParentDeleteBehave )
   {
      this.ParentDeleteBehave = ParentDeleteBehave;
   }

   /**
    * @return the DupEntityInstance
    */
   public String getDupEntityInstance( )
   {
      return DupEntityInstance;
   }

   /**
    * @param DupEntityInstance to set 
    */
   public void setDupEntityInstance( String DupEntityInstance )
   {
      this.DupEntityInstance = DupEntityInstance;
   }

   /**
    * @return the DupRelationshipInstance
    */
   public String getDupRelationshipInstance( )
   {
      return DupRelationshipInstance;
   }

   /**
    * @param DupRelationshipInstance to set 
    */
   public void setDupRelationshipInstance( String DupRelationshipInstance )
   {
      this.DupRelationshipInstance = DupRelationshipInstance;
   }

   /**
    * @return the RelLinkIndicator
    */
   public String getRelLinkIndicator( )
   {
      return RelLinkIndicator;
   }

   /**
    * @param RelLinkIndicator to set 
    */
   public void setRelLinkIndicator( String RelLinkIndicator )
   {
      this.RelLinkIndicator = RelLinkIndicator;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Abstract
    */
   public String getAbstract( )
   {
      return Abstract;
   }

   /**
    * @param Abstract to set 
    */
   public void setAbstract( String Abstract )
   {
      this.Abstract = Abstract;
   }

   /**
    * @return the XML_Name
    */
   public String getXML_Name( )
   {
      return XML_Name;
   }

   /**
    * @param XML_Name to set 
    */
   public void setXML_Name( String XML_Name )
   {
      this.XML_Name = XML_Name;
   }

   /**
    * @return the LazyLoadFlag
    */
   public String getLazyLoadFlag( )
   {
      return LazyLoadFlag;
   }

   /**
    * @param LazyLoadFlag to set 
    */
   public void setLazyLoadFlag( String LazyLoadFlag )
   {
      this.LazyLoadFlag = LazyLoadFlag;
   }

   /**
    * @return the ReportDisplayFlag
    */
   public String getReportDisplayFlag( )
   {
      return ReportDisplayFlag;
   }

   /**
    * @param ReportDisplayFlag to set 
    */
   public void setReportDisplayFlag( String ReportDisplayFlag )
   {
      this.ReportDisplayFlag = ReportDisplayFlag;
   }

   public int loadCtrlMapLOD_EntityEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      IndentName = cursor.getStringFromAttribute( "IndentName" );  if ( IndentName == null ) IndentName = "";
      IndentLvl = cursor.getIntegerFromAttribute( "IndentLvl" );  if ( IndentLvl == null ) IndentLvl = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Create = cursor.getStringFromAttribute( "Create" );  if ( Create == null ) Create = "";
      Delete = cursor.getStringFromAttribute( "Delete" );  if ( Delete == null ) Delete = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      CreateConstraint = cursor.getStringFromAttribute( "CreateConstraint" );  if ( CreateConstraint == null ) CreateConstraint = "";
      DeleteConstraint = cursor.getStringFromAttribute( "DeleteConstraint" );  if ( DeleteConstraint == null ) DeleteConstraint = "";
      IncludeConstraint = cursor.getStringFromAttribute( "IncludeConstraint" );  if ( IncludeConstraint == null ) IncludeConstraint = "";
      ExcludeConstraint = cursor.getStringFromAttribute( "ExcludeConstraint" );  if ( ExcludeConstraint == null ) ExcludeConstraint = "";
      AcceptConstraint = cursor.getStringFromAttribute( "AcceptConstraint" );  if ( AcceptConstraint == null ) AcceptConstraint = "";
      CancelConstraint = cursor.getStringFromAttribute( "CancelConstraint" );  if ( CancelConstraint == null ) CancelConstraint = "";
      SeqNo = cursor.getIntegerFromAttribute( "SeqNo" );  if ( SeqNo == null ) SeqNo = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      MultipleChildLimit = cursor.getIntegerFromAttribute( "MultipleChildLimit" );  if ( MultipleChildLimit == null ) MultipleChildLimit = 0;
      Include = cursor.getStringFromAttribute( "Include" );  if ( Include == null ) Include = "";
      InclSrc = cursor.getStringFromAttribute( "InclSrc" );  if ( InclSrc == null ) InclSrc = "";
      Exclude = cursor.getStringFromAttribute( "Exclude" );  if ( Exclude == null ) Exclude = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      Recursive = cursor.getStringFromAttribute( "Recursive" );  if ( Recursive == null ) Recursive = "";
      AutoCreate = cursor.getStringFromAttribute( "AutoCreate" );  if ( AutoCreate == null ) AutoCreate = "";
      Derived = cursor.getStringFromAttribute( "Derived" );  if ( Derived == null ) Derived = "";
      SeqType = cursor.getStringFromAttribute( "SeqType" );  if ( SeqType == null ) SeqType = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      ParentDeleteBehave = cursor.getStringFromAttribute( "ParentDeleteBehave" );  if ( ParentDeleteBehave == null ) ParentDeleteBehave = "";
      DupEntityInstance = cursor.getStringFromAttribute( "DupEntityInstance" );  if ( DupEntityInstance == null ) DupEntityInstance = "";
      DupRelationshipInstance = cursor.getStringFromAttribute( "DupRelationshipInstance" );  if ( DupRelationshipInstance == null ) DupRelationshipInstance = "";
      RelLinkIndicator = cursor.getStringFromAttribute( "RelLinkIndicator" );  if ( RelLinkIndicator == null ) RelLinkIndicator = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Abstract = cursor.getStringFromAttribute( "Abstract" );  if ( Abstract == null ) Abstract = "";
      XML_Name = cursor.getStringFromAttribute( "XML_Name" );  if ( XML_Name == null ) XML_Name = "";
      LazyLoadFlag = cursor.getStringFromAttribute( "LazyLoadFlag" );  if ( LazyLoadFlag == null ) LazyLoadFlag = "";
      ReportDisplayFlag = cursor.getStringFromAttribute( "ReportDisplayFlag" );  if ( ReportDisplayFlag == null ) ReportDisplayFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlMapContextImpl implements CtrlMapContext
{
   protected Integer ZKey;
   protected String  Desc;
   protected String  DerivedName;
   protected String  Name;
   protected Integer DecimalFormat;
   protected String  EditString;
   protected String  IsDefault;
   protected String  DIL_Text;


   // ctor
   protected CtrlMapContextImpl( EntityCursor cursor )
   {
      loadCtrlMapContextEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the DerivedName
    */
   public String getDerivedName( )
   {
      return DerivedName;
   }

   /**
    * @param DerivedName to set 
    */
   public void setDerivedName( String DerivedName )
   {
      this.DerivedName = DerivedName;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the DecimalFormat
    */
   public Integer getDecimalFormat( )
   {
      return DecimalFormat;
   }

   /**
    * @param DecimalFormat to set 
    */
   public void setDecimalFormat( Integer DecimalFormat )
   {
      this.DecimalFormat = DecimalFormat;
   }

   /**
    * @return the EditString
    */
   public String getEditString( )
   {
      return EditString;
   }

   /**
    * @param EditString to set 
    */
   public void setEditString( String EditString )
   {
      this.EditString = EditString;
   }

   /**
    * @return the IsDefault
    */
   public String getIsDefault( )
   {
      return IsDefault;
   }

   /**
    * @param IsDefault to set 
    */
   public void setIsDefault( String IsDefault )
   {
      this.IsDefault = IsDefault;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   public int loadCtrlMapContextEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      DerivedName = cursor.getStringFromAttribute( "DerivedName" );  if ( DerivedName == null ) DerivedName = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      DecimalFormat = cursor.getIntegerFromAttribute( "DecimalFormat" );  if ( DecimalFormat == null ) DecimalFormat = 0;
      EditString = cursor.getStringFromAttribute( "EditString" );  if ( EditString == null ) EditString = "";
      IsDefault = cursor.getStringFromAttribute( "IsDefault" );  if ( IsDefault == null ) IsDefault = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlMapViewImpl implements CtrlMapView
{
   protected Integer ZKey;
   protected String  LastSyncDate;
   protected String  Name;
   protected String  Desc;
   protected Integer Level;
   protected String  IsDrivingViewForReportFlag;


   // ctor
   protected CtrlMapViewImpl( EntityCursor cursor )
   {
      loadCtrlMapViewEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Level
    */
   public Integer getLevel( )
   {
      return Level;
   }

   /**
    * @param Level to set 
    */
   public void setLevel( Integer Level )
   {
      this.Level = Level;
   }

   /**
    * @return the IsDrivingViewForReportFlag
    */
   public String getIsDrivingViewForReportFlag( )
   {
      return IsDrivingViewForReportFlag;
   }

   /**
    * @param IsDrivingViewForReportFlag to set 
    */
   public void setIsDrivingViewForReportFlag( String IsDrivingViewForReportFlag )
   {
      this.IsDrivingViewForReportFlag = IsDrivingViewForReportFlag;
   }

   public int loadCtrlMapViewEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Level = cursor.getIntegerFromAttribute( "Level" );  if ( Level == null ) Level = 0;
      IsDrivingViewForReportFlag = cursor.getStringFromAttribute( "IsDrivingViewForReportFlag" );  if ( IsDrivingViewForReportFlag == null ) IsDrivingViewForReportFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class TempMappingContextImpl implements TempMappingContext
{
   protected Integer ZKey;
   protected String  Desc;
   protected String  Name;
   protected Integer DecimalFormat;
   protected String  EditString;
   protected String  IsDefault;
   protected String  DIL_Text;


   // ctor
   protected TempMappingContextImpl( EntityCursor cursor )
   {
      loadTempMappingContextEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the DecimalFormat
    */
   public Integer getDecimalFormat( )
   {
      return DecimalFormat;
   }

   /**
    * @param DecimalFormat to set 
    */
   public void setDecimalFormat( Integer DecimalFormat )
   {
      this.DecimalFormat = DecimalFormat;
   }

   /**
    * @return the EditString
    */
   public String getEditString( )
   {
      return EditString;
   }

   /**
    * @param EditString to set 
    */
   public void setEditString( String EditString )
   {
      this.EditString = EditString;
   }

   /**
    * @return the IsDefault
    */
   public String getIsDefault( )
   {
      return IsDefault;
   }

   /**
    * @param IsDefault to set 
    */
   public void setIsDefault( String IsDefault )
   {
      this.IsDefault = IsDefault;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   public int loadTempMappingContextEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      DecimalFormat = cursor.getIntegerFromAttribute( "DecimalFormat" );  if ( DecimalFormat == null ) DecimalFormat = 0;
      EditString = cursor.getStringFromAttribute( "EditString" );  if ( EditString == null ) EditString = "";
      IsDefault = cursor.getStringFromAttribute( "IsDefault" );  if ( IsDefault == null ) IsDefault = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class EventImpl implements Event
{
   protected Integer Type;
   protected Integer ZKey;


   // ctor
   protected EventImpl( EntityCursor cursor )
   {
      loadEventEntityStructure( cursor );
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadEventEntityStructure( EntityCursor cursor )
   {
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class EventActImpl implements EventAct
{
   protected String  Tag;
   protected String  NoMap;
   protected Integer Type;
   protected String  TypeData;
   protected Integer ZKey;
   protected String  DialogName;
   protected String  WindowName;
   protected String  DLL;
   protected Integer OperCtrl;
   protected Integer SB_SubAction;
   protected Integer SB_NextPrev;
   protected Integer SB_DeleteNull;
   protected Integer SB_ActionDisabling;
   protected String  ActionTypeAssociatedText;
   protected String  PopupMenuName;
   protected String  WebJavaScript;
   protected String  WebJavaScriptLocation;


   // ctor
   protected EventActImpl( EntityCursor cursor )
   {
      loadEventActEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the NoMap
    */
   public String getNoMap( )
   {
      return NoMap;
   }

   /**
    * @param NoMap to set 
    */
   public void setNoMap( String NoMap )
   {
      this.NoMap = NoMap;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the TypeData
    */
   public String getTypeData( )
   {
      return TypeData;
   }

   /**
    * @param TypeData to set 
    */
   public void setTypeData( String TypeData )
   {
      this.TypeData = TypeData;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DialogName
    */
   public String getDialogName( )
   {
      return DialogName;
   }

   /**
    * @param DialogName to set 
    */
   public void setDialogName( String DialogName )
   {
      this.DialogName = DialogName;
   }

   /**
    * @return the WindowName
    */
   public String getWindowName( )
   {
      return WindowName;
   }

   /**
    * @param WindowName to set 
    */
   public void setWindowName( String WindowName )
   {
      this.WindowName = WindowName;
   }

   /**
    * @return the DLL
    */
   public String getDLL( )
   {
      return DLL;
   }

   /**
    * @param DLL to set 
    */
   public void setDLL( String DLL )
   {
      this.DLL = DLL;
   }

   /**
    * @return the OperCtrl
    */
   public Integer getOperCtrl( )
   {
      return OperCtrl;
   }

   /**
    * @param OperCtrl to set 
    */
   public void setOperCtrl( Integer OperCtrl )
   {
      this.OperCtrl = OperCtrl;
   }

   /**
    * @return the SB_SubAction
    */
   public Integer getSB_SubAction( )
   {
      return SB_SubAction;
   }

   /**
    * @param SB_SubAction to set 
    */
   public void setSB_SubAction( Integer SB_SubAction )
   {
      this.SB_SubAction = SB_SubAction;
   }

   /**
    * @return the SB_NextPrev
    */
   public Integer getSB_NextPrev( )
   {
      return SB_NextPrev;
   }

   /**
    * @param SB_NextPrev to set 
    */
   public void setSB_NextPrev( Integer SB_NextPrev )
   {
      this.SB_NextPrev = SB_NextPrev;
   }

   /**
    * @return the SB_DeleteNull
    */
   public Integer getSB_DeleteNull( )
   {
      return SB_DeleteNull;
   }

   /**
    * @param SB_DeleteNull to set 
    */
   public void setSB_DeleteNull( Integer SB_DeleteNull )
   {
      this.SB_DeleteNull = SB_DeleteNull;
   }

   /**
    * @return the SB_ActionDisabling
    */
   public Integer getSB_ActionDisabling( )
   {
      return SB_ActionDisabling;
   }

   /**
    * @param SB_ActionDisabling to set 
    */
   public void setSB_ActionDisabling( Integer SB_ActionDisabling )
   {
      this.SB_ActionDisabling = SB_ActionDisabling;
   }

   /**
    * @return the ActionTypeAssociatedText
    */
   public String getActionTypeAssociatedText( )
   {
      return ActionTypeAssociatedText;
   }

   /**
    * @param ActionTypeAssociatedText to set 
    */
   public void setActionTypeAssociatedText( String ActionTypeAssociatedText )
   {
      this.ActionTypeAssociatedText = ActionTypeAssociatedText;
   }

   /**
    * @return the PopupMenuName
    */
   public String getPopupMenuName( )
   {
      return PopupMenuName;
   }

   /**
    * @param PopupMenuName to set 
    */
   public void setPopupMenuName( String PopupMenuName )
   {
      this.PopupMenuName = PopupMenuName;
   }

   /**
    * @return the WebJavaScript
    */
   public String getWebJavaScript( )
   {
      return WebJavaScript;
   }

   /**
    * @param WebJavaScript to set 
    */
   public void setWebJavaScript( String WebJavaScript )
   {
      this.WebJavaScript = WebJavaScript;
   }

   /**
    * @return the WebJavaScriptLocation
    */
   public String getWebJavaScriptLocation( )
   {
      return WebJavaScriptLocation;
   }

   /**
    * @param WebJavaScriptLocation to set 
    */
   public void setWebJavaScriptLocation( String WebJavaScriptLocation )
   {
      this.WebJavaScriptLocation = WebJavaScriptLocation;
   }

   public int loadEventActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      TypeData = cursor.getStringFromAttribute( "TypeData" );  if ( TypeData == null ) TypeData = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DialogName = cursor.getStringFromAttribute( "DialogName" );  if ( DialogName == null ) DialogName = "";
      WindowName = cursor.getStringFromAttribute( "WindowName" );  if ( WindowName == null ) WindowName = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      SB_SubAction = cursor.getIntegerFromAttribute( "SB_SubAction" );  if ( SB_SubAction == null ) SB_SubAction = 0;
      SB_NextPrev = cursor.getIntegerFromAttribute( "SB_NextPrev" );  if ( SB_NextPrev == null ) SB_NextPrev = 0;
      SB_DeleteNull = cursor.getIntegerFromAttribute( "SB_DeleteNull" );  if ( SB_DeleteNull == null ) SB_DeleteNull = 0;
      SB_ActionDisabling = cursor.getIntegerFromAttribute( "SB_ActionDisabling" );  if ( SB_ActionDisabling == null ) SB_ActionDisabling = 0;
      ActionTypeAssociatedText = cursor.getStringFromAttribute( "ActionTypeAssociatedText" );  if ( ActionTypeAssociatedText == null ) ActionTypeAssociatedText = "";
      PopupMenuName = cursor.getStringFromAttribute( "PopupMenuName" );  if ( PopupMenuName == null ) PopupMenuName = "";
      WebJavaScript = cursor.getStringFromAttribute( "WebJavaScript" );  if ( WebJavaScript == null ) WebJavaScript = "";
      WebJavaScriptLocation = cursor.getStringFromAttribute( "WebJavaScriptLocation" );  if ( WebJavaScriptLocation == null ) WebJavaScriptLocation = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ControlDefImpl implements ControlDef
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  LastSyncDate;
   protected String  Desc;
   protected Integer Key;
   protected Integer Type;
   protected String  RT_DLL_Name;
   protected String  RT_OperationName;
   protected String  PainterDLL_Name;
   protected String  PainterC_OperationName;
   protected String  PainterConvertOperationName;
   protected String  PainterBitmap;
   protected String  MaintenanceDialog;
   protected String  MaintenanceWindow;
   protected String  AcceptsAllParents;
   protected String  AcceptsAllChildren;
   protected String  RequiresParent;
   protected String  ForceUpdateOnCreate;
   protected Integer Id;
   protected String  ActiveX_Script;
   protected String  MapToOI;
   protected String  MapFromOI;
   protected Integer Flags;
   protected Integer Invisible;
   protected String  GUID;
   protected String  ActiveX_ScriptDLL;
   protected String  PlaceHolder;


   // ctor
   protected ControlDefImpl( EntityCursor cursor )
   {
      loadControlDefEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Key
    */
   public Integer getKey( )
   {
      return Key;
   }

   /**
    * @param Key to set 
    */
   public void setKey( Integer Key )
   {
      this.Key = Key;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the RT_DLL_Name
    */
   public String getRT_DLL_Name( )
   {
      return RT_DLL_Name;
   }

   /**
    * @param RT_DLL_Name to set 
    */
   public void setRT_DLL_Name( String RT_DLL_Name )
   {
      this.RT_DLL_Name = RT_DLL_Name;
   }

   /**
    * @return the RT_OperationName
    */
   public String getRT_OperationName( )
   {
      return RT_OperationName;
   }

   /**
    * @param RT_OperationName to set 
    */
   public void setRT_OperationName( String RT_OperationName )
   {
      this.RT_OperationName = RT_OperationName;
   }

   /**
    * @return the PainterDLL_Name
    */
   public String getPainterDLL_Name( )
   {
      return PainterDLL_Name;
   }

   /**
    * @param PainterDLL_Name to set 
    */
   public void setPainterDLL_Name( String PainterDLL_Name )
   {
      this.PainterDLL_Name = PainterDLL_Name;
   }

   /**
    * @return the PainterC_OperationName
    */
   public String getPainterC_OperationName( )
   {
      return PainterC_OperationName;
   }

   /**
    * @param PainterC_OperationName to set 
    */
   public void setPainterC_OperationName( String PainterC_OperationName )
   {
      this.PainterC_OperationName = PainterC_OperationName;
   }

   /**
    * @return the PainterConvertOperationName
    */
   public String getPainterConvertOperationName( )
   {
      return PainterConvertOperationName;
   }

   /**
    * @param PainterConvertOperationName to set 
    */
   public void setPainterConvertOperationName( String PainterConvertOperationName )
   {
      this.PainterConvertOperationName = PainterConvertOperationName;
   }

   /**
    * @return the PainterBitmap
    */
   public String getPainterBitmap( )
   {
      return PainterBitmap;
   }

   /**
    * @param PainterBitmap to set 
    */
   public void setPainterBitmap( String PainterBitmap )
   {
      this.PainterBitmap = PainterBitmap;
   }

   /**
    * @return the MaintenanceDialog
    */
   public String getMaintenanceDialog( )
   {
      return MaintenanceDialog;
   }

   /**
    * @param MaintenanceDialog to set 
    */
   public void setMaintenanceDialog( String MaintenanceDialog )
   {
      this.MaintenanceDialog = MaintenanceDialog;
   }

   /**
    * @return the MaintenanceWindow
    */
   public String getMaintenanceWindow( )
   {
      return MaintenanceWindow;
   }

   /**
    * @param MaintenanceWindow to set 
    */
   public void setMaintenanceWindow( String MaintenanceWindow )
   {
      this.MaintenanceWindow = MaintenanceWindow;
   }

   /**
    * @return the AcceptsAllParents
    */
   public String getAcceptsAllParents( )
   {
      return AcceptsAllParents;
   }

   /**
    * @param AcceptsAllParents to set 
    */
   public void setAcceptsAllParents( String AcceptsAllParents )
   {
      this.AcceptsAllParents = AcceptsAllParents;
   }

   /**
    * @return the AcceptsAllChildren
    */
   public String getAcceptsAllChildren( )
   {
      return AcceptsAllChildren;
   }

   /**
    * @param AcceptsAllChildren to set 
    */
   public void setAcceptsAllChildren( String AcceptsAllChildren )
   {
      this.AcceptsAllChildren = AcceptsAllChildren;
   }

   /**
    * @return the RequiresParent
    */
   public String getRequiresParent( )
   {
      return RequiresParent;
   }

   /**
    * @param RequiresParent to set 
    */
   public void setRequiresParent( String RequiresParent )
   {
      this.RequiresParent = RequiresParent;
   }

   /**
    * @return the ForceUpdateOnCreate
    */
   public String getForceUpdateOnCreate( )
   {
      return ForceUpdateOnCreate;
   }

   /**
    * @param ForceUpdateOnCreate to set 
    */
   public void setForceUpdateOnCreate( String ForceUpdateOnCreate )
   {
      this.ForceUpdateOnCreate = ForceUpdateOnCreate;
   }

   /**
    * @return the Id
    */
   public Integer getId( )
   {
      return Id;
   }

   /**
    * @param Id to set 
    */
   public void setId( Integer Id )
   {
      this.Id = Id;
   }

   /**
    * @return the ActiveX_Script
    */
   public String getActiveX_Script( )
   {
      return ActiveX_Script;
   }

   /**
    * @param ActiveX_Script to set 
    */
   public void setActiveX_Script( String ActiveX_Script )
   {
      this.ActiveX_Script = ActiveX_Script;
   }

   /**
    * @return the MapToOI
    */
   public String getMapToOI( )
   {
      return MapToOI;
   }

   /**
    * @param MapToOI to set 
    */
   public void setMapToOI( String MapToOI )
   {
      this.MapToOI = MapToOI;
   }

   /**
    * @return the MapFromOI
    */
   public String getMapFromOI( )
   {
      return MapFromOI;
   }

   /**
    * @param MapFromOI to set 
    */
   public void setMapFromOI( String MapFromOI )
   {
      this.MapFromOI = MapFromOI;
   }

   /**
    * @return the Flags
    */
   public Integer getFlags( )
   {
      return Flags;
   }

   /**
    * @param Flags to set 
    */
   public void setFlags( Integer Flags )
   {
      this.Flags = Flags;
   }

   /**
    * @return the Invisible
    */
   public Integer getInvisible( )
   {
      return Invisible;
   }

   /**
    * @param Invisible to set 
    */
   public void setInvisible( Integer Invisible )
   {
      this.Invisible = Invisible;
   }

   /**
    * @return the GUID
    */
   public String getGUID( )
   {
      return GUID;
   }

   /**
    * @param GUID to set 
    */
   public void setGUID( String GUID )
   {
      this.GUID = GUID;
   }

   /**
    * @return the ActiveX_ScriptDLL
    */
   public String getActiveX_ScriptDLL( )
   {
      return ActiveX_ScriptDLL;
   }

   /**
    * @param ActiveX_ScriptDLL to set 
    */
   public void setActiveX_ScriptDLL( String ActiveX_ScriptDLL )
   {
      this.ActiveX_ScriptDLL = ActiveX_ScriptDLL;
   }

   /**
    * @return the PlaceHolder
    */
   public String getPlaceHolder( )
   {
      return PlaceHolder;
   }

   /**
    * @param PlaceHolder to set 
    */
   public void setPlaceHolder( String PlaceHolder )
   {
      this.PlaceHolder = PlaceHolder;
   }

   public int loadControlDefEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Key = cursor.getIntegerFromAttribute( "Key" );  if ( Key == null ) Key = 0;
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      RT_DLL_Name = cursor.getStringFromAttribute( "RT_DLL_Name" );  if ( RT_DLL_Name == null ) RT_DLL_Name = "";
      RT_OperationName = cursor.getStringFromAttribute( "RT_OperationName" );  if ( RT_OperationName == null ) RT_OperationName = "";
      PainterDLL_Name = cursor.getStringFromAttribute( "PainterDLL_Name" );  if ( PainterDLL_Name == null ) PainterDLL_Name = "";
      PainterC_OperationName = cursor.getStringFromAttribute( "PainterC_OperationName" );  if ( PainterC_OperationName == null ) PainterC_OperationName = "";
      PainterConvertOperationName = cursor.getStringFromAttribute( "PainterConvertOperationName" );  if ( PainterConvertOperationName == null ) PainterConvertOperationName = "";
      PainterBitmap = cursor.getStringFromAttribute( "PainterBitmap" );  if ( PainterBitmap == null ) PainterBitmap = "";
      MaintenanceDialog = cursor.getStringFromAttribute( "MaintenanceDialog" );  if ( MaintenanceDialog == null ) MaintenanceDialog = "";
      MaintenanceWindow = cursor.getStringFromAttribute( "MaintenanceWindow" );  if ( MaintenanceWindow == null ) MaintenanceWindow = "";
      AcceptsAllParents = cursor.getStringFromAttribute( "AcceptsAllParents" );  if ( AcceptsAllParents == null ) AcceptsAllParents = "";
      AcceptsAllChildren = cursor.getStringFromAttribute( "AcceptsAllChildren" );  if ( AcceptsAllChildren == null ) AcceptsAllChildren = "";
      RequiresParent = cursor.getStringFromAttribute( "RequiresParent" );  if ( RequiresParent == null ) RequiresParent = "";
      ForceUpdateOnCreate = cursor.getStringFromAttribute( "ForceUpdateOnCreate" );  if ( ForceUpdateOnCreate == null ) ForceUpdateOnCreate = "";
      Id = cursor.getIntegerFromAttribute( "Id" );  if ( Id == null ) Id = 0;
      ActiveX_Script = cursor.getStringFromAttribute( "ActiveX_Script" );  if ( ActiveX_Script == null ) ActiveX_Script = "";
      MapToOI = cursor.getStringFromAttribute( "MapToOI" );  if ( MapToOI == null ) MapToOI = "";
      MapFromOI = cursor.getStringFromAttribute( "MapFromOI" );  if ( MapFromOI == null ) MapFromOI = "";
      Flags = cursor.getIntegerFromAttribute( "Flags" );  if ( Flags == null ) Flags = 0;
      Invisible = cursor.getIntegerFromAttribute( "Invisible" );  if ( Invisible == null ) Invisible = 0;
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      ActiveX_ScriptDLL = cursor.getStringFromAttribute( "ActiveX_ScriptDLL" );  if ( ActiveX_ScriptDLL == null ) ActiveX_ScriptDLL = "";
      PlaceHolder = cursor.getStringFromAttribute( "PlaceHolder" );  if ( PlaceHolder == null ) PlaceHolder = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class FontImpl implements Font
{
   protected String  Tag;
   protected Integer ZKey;
   protected Blob    WindowsStructure;
   protected Integer ClrText;
   protected Integer ClrTextBk;
   protected Integer ClrHilite;
   protected Integer ClrBackground;
   protected String  FaceName;
   protected Integer PointSize;
   protected String  Bold;
   protected String  Italic;
   protected String  Strikeout;
   protected String  Underline;
   protected String  MultiLine;
   protected String  VerticalText;
   protected String  BeveledLine;
   protected String  Hilite;
   protected String  UseToolTip;
   protected String  ToolTip;
   protected String  HyperText;
   protected String  JustifyTopCenterBottom;
   protected String  JustifyLeftCenterRight;
   protected Integer BorderStyle;
   protected Integer Escapement;
   protected Integer Type;


   // ctor
   protected FontImpl( EntityCursor cursor )
   {
      loadFontEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the WindowsStructure
    */
   public Blob getWindowsStructure( )
   {
      return WindowsStructure;
   }

   /**
    * @param WindowsStructure to set 
    */
   public void setWindowsStructure( Blob WindowsStructure )
   {
      this.WindowsStructure = WindowsStructure;
   }

   /**
    * @return the ClrText
    */
   public Integer getClrText( )
   {
      return ClrText;
   }

   /**
    * @param ClrText to set 
    */
   public void setClrText( Integer ClrText )
   {
      this.ClrText = ClrText;
   }

   /**
    * @return the ClrTextBk
    */
   public Integer getClrTextBk( )
   {
      return ClrTextBk;
   }

   /**
    * @param ClrTextBk to set 
    */
   public void setClrTextBk( Integer ClrTextBk )
   {
      this.ClrTextBk = ClrTextBk;
   }

   /**
    * @return the ClrHilite
    */
   public Integer getClrHilite( )
   {
      return ClrHilite;
   }

   /**
    * @param ClrHilite to set 
    */
   public void setClrHilite( Integer ClrHilite )
   {
      this.ClrHilite = ClrHilite;
   }

   /**
    * @return the ClrBackground
    */
   public Integer getClrBackground( )
   {
      return ClrBackground;
   }

   /**
    * @param ClrBackground to set 
    */
   public void setClrBackground( Integer ClrBackground )
   {
      this.ClrBackground = ClrBackground;
   }

   /**
    * @return the FaceName
    */
   public String getFaceName( )
   {
      return FaceName;
   }

   /**
    * @param FaceName to set 
    */
   public void setFaceName( String FaceName )
   {
      this.FaceName = FaceName;
   }

   /**
    * @return the PointSize
    */
   public Integer getPointSize( )
   {
      return PointSize;
   }

   /**
    * @param PointSize to set 
    */
   public void setPointSize( Integer PointSize )
   {
      this.PointSize = PointSize;
   }

   /**
    * @return the Bold
    */
   public String getBold( )
   {
      return Bold;
   }

   /**
    * @param Bold to set 
    */
   public void setBold( String Bold )
   {
      this.Bold = Bold;
   }

   /**
    * @return the Italic
    */
   public String getItalic( )
   {
      return Italic;
   }

   /**
    * @param Italic to set 
    */
   public void setItalic( String Italic )
   {
      this.Italic = Italic;
   }

   /**
    * @return the Strikeout
    */
   public String getStrikeout( )
   {
      return Strikeout;
   }

   /**
    * @param Strikeout to set 
    */
   public void setStrikeout( String Strikeout )
   {
      this.Strikeout = Strikeout;
   }

   /**
    * @return the Underline
    */
   public String getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( String Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the MultiLine
    */
   public String getMultiLine( )
   {
      return MultiLine;
   }

   /**
    * @param MultiLine to set 
    */
   public void setMultiLine( String MultiLine )
   {
      this.MultiLine = MultiLine;
   }

   /**
    * @return the VerticalText
    */
   public String getVerticalText( )
   {
      return VerticalText;
   }

   /**
    * @param VerticalText to set 
    */
   public void setVerticalText( String VerticalText )
   {
      this.VerticalText = VerticalText;
   }

   /**
    * @return the BeveledLine
    */
   public String getBeveledLine( )
   {
      return BeveledLine;
   }

   /**
    * @param BeveledLine to set 
    */
   public void setBeveledLine( String BeveledLine )
   {
      this.BeveledLine = BeveledLine;
   }

   /**
    * @return the Hilite
    */
   public String getHilite( )
   {
      return Hilite;
   }

   /**
    * @param Hilite to set 
    */
   public void setHilite( String Hilite )
   {
      this.Hilite = Hilite;
   }

   /**
    * @return the UseToolTip
    */
   public String getUseToolTip( )
   {
      return UseToolTip;
   }

   /**
    * @param UseToolTip to set 
    */
   public void setUseToolTip( String UseToolTip )
   {
      this.UseToolTip = UseToolTip;
   }

   /**
    * @return the ToolTip
    */
   public String getToolTip( )
   {
      return ToolTip;
   }

   /**
    * @param ToolTip to set 
    */
   public void setToolTip( String ToolTip )
   {
      this.ToolTip = ToolTip;
   }

   /**
    * @return the HyperText
    */
   public String getHyperText( )
   {
      return HyperText;
   }

   /**
    * @param HyperText to set 
    */
   public void setHyperText( String HyperText )
   {
      this.HyperText = HyperText;
   }

   /**
    * @return the JustifyTopCenterBottom
    */
   public String getJustifyTopCenterBottom( )
   {
      return JustifyTopCenterBottom;
   }

   /**
    * @param JustifyTopCenterBottom to set 
    */
   public void setJustifyTopCenterBottom( String JustifyTopCenterBottom )
   {
      this.JustifyTopCenterBottom = JustifyTopCenterBottom;
   }

   /**
    * @return the JustifyLeftCenterRight
    */
   public String getJustifyLeftCenterRight( )
   {
      return JustifyLeftCenterRight;
   }

   /**
    * @param JustifyLeftCenterRight to set 
    */
   public void setJustifyLeftCenterRight( String JustifyLeftCenterRight )
   {
      this.JustifyLeftCenterRight = JustifyLeftCenterRight;
   }

   /**
    * @return the BorderStyle
    */
   public Integer getBorderStyle( )
   {
      return BorderStyle;
   }

   /**
    * @param BorderStyle to set 
    */
   public void setBorderStyle( Integer BorderStyle )
   {
      this.BorderStyle = BorderStyle;
   }

   /**
    * @return the Escapement
    */
   public Integer getEscapement( )
   {
      return Escapement;
   }

   /**
    * @param Escapement to set 
    */
   public void setEscapement( Integer Escapement )
   {
      this.Escapement = Escapement;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   public int loadFontEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      WindowsStructure = cursor.getBlobFromAttribute( "WindowsStructure" );
      ClrText = cursor.getIntegerFromAttribute( "ClrText" );  if ( ClrText == null ) ClrText = 0;
      ClrTextBk = cursor.getIntegerFromAttribute( "ClrTextBk" );  if ( ClrTextBk == null ) ClrTextBk = 0;
      ClrHilite = cursor.getIntegerFromAttribute( "ClrHilite" );  if ( ClrHilite == null ) ClrHilite = 0;
      ClrBackground = cursor.getIntegerFromAttribute( "ClrBackground" );  if ( ClrBackground == null ) ClrBackground = 0;
      FaceName = cursor.getStringFromAttribute( "FaceName" );  if ( FaceName == null ) FaceName = "";
      PointSize = cursor.getIntegerFromAttribute( "PointSize" );  if ( PointSize == null ) PointSize = 0;
      Bold = cursor.getStringFromAttribute( "Bold" );  if ( Bold == null ) Bold = "";
      Italic = cursor.getStringFromAttribute( "Italic" );  if ( Italic == null ) Italic = "";
      Strikeout = cursor.getStringFromAttribute( "Strikeout" );  if ( Strikeout == null ) Strikeout = "";
      Underline = cursor.getStringFromAttribute( "Underline" );  if ( Underline == null ) Underline = "";
      MultiLine = cursor.getStringFromAttribute( "MultiLine" );  if ( MultiLine == null ) MultiLine = "";
      VerticalText = cursor.getStringFromAttribute( "VerticalText" );  if ( VerticalText == null ) VerticalText = "";
      BeveledLine = cursor.getStringFromAttribute( "BeveledLine" );  if ( BeveledLine == null ) BeveledLine = "";
      Hilite = cursor.getStringFromAttribute( "Hilite" );  if ( Hilite == null ) Hilite = "";
      UseToolTip = cursor.getStringFromAttribute( "UseToolTip" );  if ( UseToolTip == null ) UseToolTip = "";
      ToolTip = cursor.getStringFromAttribute( "ToolTip" );  if ( ToolTip == null ) ToolTip = "";
      HyperText = cursor.getStringFromAttribute( "HyperText" );  if ( HyperText == null ) HyperText = "";
      JustifyTopCenterBottom = cursor.getStringFromAttribute( "JustifyTopCenterBottom" );  if ( JustifyTopCenterBottom == null ) JustifyTopCenterBottom = "";
      JustifyLeftCenterRight = cursor.getStringFromAttribute( "JustifyLeftCenterRight" );  if ( JustifyLeftCenterRight == null ) JustifyLeftCenterRight = "";
      BorderStyle = cursor.getIntegerFromAttribute( "BorderStyle" );  if ( BorderStyle == null ) BorderStyle = 0;
      Escapement = cursor.getIntegerFromAttribute( "Escapement" );  if ( Escapement == null ) Escapement = 0;
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ControlNLS_TextImpl implements ControlNLS_Text
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected ControlNLS_TextImpl( EntityCursor cursor )
   {
      loadControlNLS_TextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadControlNLS_TextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ControlNLS_DIL_TextImpl implements ControlNLS_DIL_Text
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected ControlNLS_DIL_TextImpl( EntityCursor cursor )
   {
      loadControlNLS_DIL_TextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadControlNLS_DIL_TextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlPropertyImpl implements CtrlProperty
{
   protected String  Name;
   protected String  Value;
   protected String  Type;
   protected Integer ZKey;


   // ctor
   protected CtrlPropertyImpl( EntityCursor cursor )
   {
      loadCtrlPropertyEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Value
    */
   public String getValue( )
   {
      return Value;
   }

   /**
    * @param Value to set 
    */
   public void setValue( String Value )
   {
      this.Value = Value;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadCtrlPropertyEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Value = cursor.getStringFromAttribute( "Value" );  if ( Value == null ) Value = "";
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CtrlPropertyAttributeImpl implements CtrlPropertyAttribute
{
   protected String  Name;
   protected String  Value;
   protected String  Type;
   protected Integer ZKey;


   // ctor
   protected CtrlPropertyAttributeImpl( EntityCursor cursor )
   {
      loadCtrlPropertyAttributeEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Value
    */
   public String getValue( )
   {
      return Value;
   }

   /**
    * @param Value to set 
    */
   public void setValue( String Value )
   {
      this.Value = Value;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadCtrlPropertyAttributeEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Value = cursor.getStringFromAttribute( "Value" );  if ( Value == null ) Value = "";
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WebControlPropertyImpl implements WebControlProperty
{
   protected Integer ZKey;
   protected String  Name;


   // ctor
   protected WebControlPropertyImpl( EntityCursor cursor )
   {
      loadWebControlPropertyEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   public int loadWebControlPropertyEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ListCtrlMapImpl implements ListCtrlMap
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  Type;
   protected Integer SeqNo_DlgCtrl;
   protected Integer SeqNo_DlgAct;


   // ctor
   protected ListCtrlMapImpl( EntityCursor cursor )
   {
      loadListCtrlMapEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the SeqNo_DlgCtrl
    */
   public Integer getSeqNo_DlgCtrl( )
   {
      return SeqNo_DlgCtrl;
   }

   /**
    * @param SeqNo_DlgCtrl to set 
    */
   public void setSeqNo_DlgCtrl( Integer SeqNo_DlgCtrl )
   {
      this.SeqNo_DlgCtrl = SeqNo_DlgCtrl;
   }

   /**
    * @return the SeqNo_DlgAct
    */
   public Integer getSeqNo_DlgAct( )
   {
      return SeqNo_DlgAct;
   }

   /**
    * @param SeqNo_DlgAct to set 
    */
   public void setSeqNo_DlgAct( Integer SeqNo_DlgAct )
   {
      this.SeqNo_DlgAct = SeqNo_DlgAct;
   }

   public int loadListCtrlMapEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      SeqNo_DlgCtrl = cursor.getIntegerFromAttribute( "SeqNo_DlgCtrl" );  if ( SeqNo_DlgCtrl == null ) SeqNo_DlgCtrl = 0;
      SeqNo_DlgAct = cursor.getIntegerFromAttribute( "SeqNo_DlgAct" );  if ( SeqNo_DlgAct == null ) SeqNo_DlgAct = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ListCtrlMapLOD_AttributeImpl implements ListCtrlMapLOD_Attribute
{
   protected Integer ZKey;
   protected String  Work;
   protected String  Update;
   protected String  Init;
   protected String  Hidden;
   protected Integer SeqPriority;
   protected String  SeqOrder;
   protected String  DIL_Text;
   protected Integer SeqNo_LOD_Entity;
   protected Integer SeqNo_UIS_Entity_M;
   protected Integer SeqNo_UIS_Entity_L;
   protected String  DB_DerivedValue;
   protected String  XML_Simple;
   protected String  HashkeyType;
   protected String  HashkeyParentEntityName;


   // ctor
   protected ListCtrlMapLOD_AttributeImpl( EntityCursor cursor )
   {
      loadListCtrlMapLOD_AttributeEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the Init
    */
   public String getInit( )
   {
      return Init;
   }

   /**
    * @param Init to set 
    */
   public void setInit( String Init )
   {
      this.Init = Init;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the SeqPriority
    */
   public Integer getSeqPriority( )
   {
      return SeqPriority;
   }

   /**
    * @param SeqPriority to set 
    */
   public void setSeqPriority( Integer SeqPriority )
   {
      this.SeqPriority = SeqPriority;
   }

   /**
    * @return the SeqOrder
    */
   public String getSeqOrder( )
   {
      return SeqOrder;
   }

   /**
    * @param SeqOrder to set 
    */
   public void setSeqOrder( String SeqOrder )
   {
      this.SeqOrder = SeqOrder;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the SeqNo_LOD_Entity
    */
   public Integer getSeqNo_LOD_Entity( )
   {
      return SeqNo_LOD_Entity;
   }

   /**
    * @param SeqNo_LOD_Entity to set 
    */
   public void setSeqNo_LOD_Entity( Integer SeqNo_LOD_Entity )
   {
      this.SeqNo_LOD_Entity = SeqNo_LOD_Entity;
   }

   /**
    * @return the SeqNo_UIS_Entity_M
    */
   public Integer getSeqNo_UIS_Entity_M( )
   {
      return SeqNo_UIS_Entity_M;
   }

   /**
    * @param SeqNo_UIS_Entity_M to set 
    */
   public void setSeqNo_UIS_Entity_M( Integer SeqNo_UIS_Entity_M )
   {
      this.SeqNo_UIS_Entity_M = SeqNo_UIS_Entity_M;
   }

   /**
    * @return the SeqNo_UIS_Entity_L
    */
   public Integer getSeqNo_UIS_Entity_L( )
   {
      return SeqNo_UIS_Entity_L;
   }

   /**
    * @param SeqNo_UIS_Entity_L to set 
    */
   public void setSeqNo_UIS_Entity_L( Integer SeqNo_UIS_Entity_L )
   {
      this.SeqNo_UIS_Entity_L = SeqNo_UIS_Entity_L;
   }

   /**
    * @return the DB_DerivedValue
    */
   public String getDB_DerivedValue( )
   {
      return DB_DerivedValue;
   }

   /**
    * @param DB_DerivedValue to set 
    */
   public void setDB_DerivedValue( String DB_DerivedValue )
   {
      this.DB_DerivedValue = DB_DerivedValue;
   }

   /**
    * @return the XML_Simple
    */
   public String getXML_Simple( )
   {
      return XML_Simple;
   }

   /**
    * @param XML_Simple to set 
    */
   public void setXML_Simple( String XML_Simple )
   {
      this.XML_Simple = XML_Simple;
   }

   /**
    * @return the HashkeyType
    */
   public String getHashkeyType( )
   {
      return HashkeyType;
   }

   /**
    * @param HashkeyType to set 
    */
   public void setHashkeyType( String HashkeyType )
   {
      this.HashkeyType = HashkeyType;
   }

   /**
    * @return the HashkeyParentEntityName
    */
   public String getHashkeyParentEntityName( )
   {
      return HashkeyParentEntityName;
   }

   /**
    * @param HashkeyParentEntityName to set 
    */
   public void setHashkeyParentEntityName( String HashkeyParentEntityName )
   {
      this.HashkeyParentEntityName = HashkeyParentEntityName;
   }

   public int loadListCtrlMapLOD_AttributeEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      Init = cursor.getStringFromAttribute( "Init" );  if ( Init == null ) Init = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      SeqPriority = cursor.getIntegerFromAttribute( "SeqPriority" );  if ( SeqPriority == null ) SeqPriority = 0;
      SeqOrder = cursor.getStringFromAttribute( "SeqOrder" );  if ( SeqOrder == null ) SeqOrder = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      SeqNo_LOD_Entity = cursor.getIntegerFromAttribute( "SeqNo_LOD_Entity" );  if ( SeqNo_LOD_Entity == null ) SeqNo_LOD_Entity = 0;
      SeqNo_UIS_Entity_M = cursor.getIntegerFromAttribute( "SeqNo_UIS_Entity_M" );  if ( SeqNo_UIS_Entity_M == null ) SeqNo_UIS_Entity_M = 0;
      SeqNo_UIS_Entity_L = cursor.getIntegerFromAttribute( "SeqNo_UIS_Entity_L" );  if ( SeqNo_UIS_Entity_L == null ) SeqNo_UIS_Entity_L = 0;
      DB_DerivedValue = cursor.getStringFromAttribute( "DB_DerivedValue" );  if ( DB_DerivedValue == null ) DB_DerivedValue = "";
      XML_Simple = cursor.getStringFromAttribute( "XML_Simple" );  if ( XML_Simple == null ) XML_Simple = "";
      HashkeyType = cursor.getStringFromAttribute( "HashkeyType" );  if ( HashkeyType == null ) HashkeyType = "";
      HashkeyParentEntityName = cursor.getStringFromAttribute( "HashkeyParentEntityName" );  if ( HashkeyParentEntityName == null ) HashkeyParentEntityName = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ER_AttributeImpl implements ER_Attribute
{
   protected String  Name;
   protected Integer ZKey;
   protected Integer Lth;
   protected String  Key;
   protected String  NotNull;
   protected String  Desc;
   protected String  PromptPaintLit;
   protected Integer PromptPaintLth;
   protected String  ListPaintLit;
   protected Integer ListPaintLth;
   protected String  CaseSens;
   protected String  ADW_Position;
   protected String  TE_ColumnName;
   protected String  TE_ForeignKeyName;
   protected String  Work;
   protected String  DerivedExpression;
   protected Blob    DerivedExpressionXPG;
   protected Integer Sequence;
   protected Integer SAP_Attribute;
   protected String  XML_SimpleName;
   protected String  XML_NameExternal;


   // ctor
   protected ER_AttributeImpl( EntityCursor cursor )
   {
      loadER_AttributeEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Lth
    */
   public Integer getLth( )
   {
      return Lth;
   }

   /**
    * @param Lth to set 
    */
   public void setLth( Integer Lth )
   {
      this.Lth = Lth;
   }

   /**
    * @return the Key
    */
   public String getKey( )
   {
      return Key;
   }

   /**
    * @param Key to set 
    */
   public void setKey( String Key )
   {
      this.Key = Key;
   }

   /**
    * @return the NotNull
    */
   public String getNotNull( )
   {
      return NotNull;
   }

   /**
    * @param NotNull to set 
    */
   public void setNotNull( String NotNull )
   {
      this.NotNull = NotNull;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the PromptPaintLit
    */
   public String getPromptPaintLit( )
   {
      return PromptPaintLit;
   }

   /**
    * @param PromptPaintLit to set 
    */
   public void setPromptPaintLit( String PromptPaintLit )
   {
      this.PromptPaintLit = PromptPaintLit;
   }

   /**
    * @return the PromptPaintLth
    */
   public Integer getPromptPaintLth( )
   {
      return PromptPaintLth;
   }

   /**
    * @param PromptPaintLth to set 
    */
   public void setPromptPaintLth( Integer PromptPaintLth )
   {
      this.PromptPaintLth = PromptPaintLth;
   }

   /**
    * @return the ListPaintLit
    */
   public String getListPaintLit( )
   {
      return ListPaintLit;
   }

   /**
    * @param ListPaintLit to set 
    */
   public void setListPaintLit( String ListPaintLit )
   {
      this.ListPaintLit = ListPaintLit;
   }

   /**
    * @return the ListPaintLth
    */
   public Integer getListPaintLth( )
   {
      return ListPaintLth;
   }

   /**
    * @param ListPaintLth to set 
    */
   public void setListPaintLth( Integer ListPaintLth )
   {
      this.ListPaintLth = ListPaintLth;
   }

   /**
    * @return the CaseSens
    */
   public String getCaseSens( )
   {
      return CaseSens;
   }

   /**
    * @param CaseSens to set 
    */
   public void setCaseSens( String CaseSens )
   {
      this.CaseSens = CaseSens;
   }

   /**
    * @return the ADW_Position
    */
   public String getADW_Position( )
   {
      return ADW_Position;
   }

   /**
    * @param ADW_Position to set 
    */
   public void setADW_Position( String ADW_Position )
   {
      this.ADW_Position = ADW_Position;
   }

   /**
    * @return the TE_ColumnName
    */
   public String getTE_ColumnName( )
   {
      return TE_ColumnName;
   }

   /**
    * @param TE_ColumnName to set 
    */
   public void setTE_ColumnName( String TE_ColumnName )
   {
      this.TE_ColumnName = TE_ColumnName;
   }

   /**
    * @return the TE_ForeignKeyName
    */
   public String getTE_ForeignKeyName( )
   {
      return TE_ForeignKeyName;
   }

   /**
    * @param TE_ForeignKeyName to set 
    */
   public void setTE_ForeignKeyName( String TE_ForeignKeyName )
   {
      this.TE_ForeignKeyName = TE_ForeignKeyName;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the DerivedExpression
    */
   public String getDerivedExpression( )
   {
      return DerivedExpression;
   }

   /**
    * @param DerivedExpression to set 
    */
   public void setDerivedExpression( String DerivedExpression )
   {
      this.DerivedExpression = DerivedExpression;
   }

   /**
    * @return the DerivedExpressionXPG
    */
   public Blob getDerivedExpressionXPG( )
   {
      return DerivedExpressionXPG;
   }

   /**
    * @param DerivedExpressionXPG to set 
    */
   public void setDerivedExpressionXPG( Blob DerivedExpressionXPG )
   {
      this.DerivedExpressionXPG = DerivedExpressionXPG;
   }

   /**
    * @return the Sequence
    */
   public Integer getSequence( )
   {
      return Sequence;
   }

   /**
    * @param Sequence to set 
    */
   public void setSequence( Integer Sequence )
   {
      this.Sequence = Sequence;
   }

   /**
    * @return the SAP_Attribute
    */
   public Integer getSAP_Attribute( )
   {
      return SAP_Attribute;
   }

   /**
    * @param SAP_Attribute to set 
    */
   public void setSAP_Attribute( Integer SAP_Attribute )
   {
      this.SAP_Attribute = SAP_Attribute;
   }

   /**
    * @return the XML_SimpleName
    */
   public String getXML_SimpleName( )
   {
      return XML_SimpleName;
   }

   /**
    * @param XML_SimpleName to set 
    */
   public void setXML_SimpleName( String XML_SimpleName )
   {
      this.XML_SimpleName = XML_SimpleName;
   }

   /**
    * @return the XML_NameExternal
    */
   public String getXML_NameExternal( )
   {
      return XML_NameExternal;
   }

   /**
    * @param XML_NameExternal to set 
    */
   public void setXML_NameExternal( String XML_NameExternal )
   {
      this.XML_NameExternal = XML_NameExternal;
   }

   public int loadER_AttributeEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Lth = cursor.getIntegerFromAttribute( "Lth" );  if ( Lth == null ) Lth = 0;
      Key = cursor.getStringFromAttribute( "Key" );  if ( Key == null ) Key = "";
      NotNull = cursor.getStringFromAttribute( "NotNull" );  if ( NotNull == null ) NotNull = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      PromptPaintLit = cursor.getStringFromAttribute( "PromptPaintLit" );  if ( PromptPaintLit == null ) PromptPaintLit = "";
      PromptPaintLth = cursor.getIntegerFromAttribute( "PromptPaintLth" );  if ( PromptPaintLth == null ) PromptPaintLth = 0;
      ListPaintLit = cursor.getStringFromAttribute( "ListPaintLit" );  if ( ListPaintLit == null ) ListPaintLit = "";
      ListPaintLth = cursor.getIntegerFromAttribute( "ListPaintLth" );  if ( ListPaintLth == null ) ListPaintLth = 0;
      CaseSens = cursor.getStringFromAttribute( "CaseSens" );  if ( CaseSens == null ) CaseSens = "";
      ADW_Position = cursor.getStringFromAttribute( "ADW_Position" );  if ( ADW_Position == null ) ADW_Position = "";
      TE_ColumnName = cursor.getStringFromAttribute( "TE_ColumnName" );  if ( TE_ColumnName == null ) TE_ColumnName = "";
      TE_ForeignKeyName = cursor.getStringFromAttribute( "TE_ForeignKeyName" );  if ( TE_ForeignKeyName == null ) TE_ForeignKeyName = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      DerivedExpression = cursor.getStringFromAttribute( "DerivedExpression" );  if ( DerivedExpression == null ) DerivedExpression = "";
      DerivedExpressionXPG = cursor.getBlobFromAttribute( "DerivedExpressionXPG" );
      Sequence = cursor.getIntegerFromAttribute( "Sequence" );  if ( Sequence == null ) Sequence = 0;
      SAP_Attribute = cursor.getIntegerFromAttribute( "SAP_Attribute" );  if ( SAP_Attribute == null ) SAP_Attribute = 0;
      XML_SimpleName = cursor.getStringFromAttribute( "XML_SimpleName" );  if ( XML_SimpleName == null ) XML_SimpleName = "";
      XML_NameExternal = cursor.getStringFromAttribute( "XML_NameExternal" );  if ( XML_NameExternal == null ) XML_NameExternal = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ListCtrlLOD_EntityImpl implements ListCtrlLOD_Entity
{
   protected String  Name;
   protected Integer ZKey;
   protected String  IndentName;
   protected Integer IndentLvl;
   protected String  Create;
   protected String  Delete;
   protected String  Include;
   protected String  InclSrc;
   protected String  Exclude;
   protected String  Hidden;
   protected String  Recursive;
   protected String  AutoCreate;
   protected String  Derived;
   protected String  Update;
   protected String  SeqType;
   protected String  Work;
   protected String  Abstract;
   protected String  ParentDeleteBehave;
   protected String  DupEntityInstance;
   protected String  DupRelationshipInstance;
   protected String  RelLinkIndicator;
   protected String  Desc;
   protected String  CreateConstraint;
   protected String  DeleteConstraint;
   protected String  IncludeConstraint;
   protected String  ExcludeConstraint;
   protected String  AcceptConstraint;
   protected String  CancelConstraint;
   protected Integer SeqNo;
   protected Integer DataLocking;
   protected Integer MultipleChildLimit;
   protected String  XML_Name;
   protected String  LazyLoadFlag;
   protected String  ReportDisplayFlag;


   // ctor
   protected ListCtrlLOD_EntityImpl( EntityCursor cursor )
   {
      loadListCtrlLOD_EntityEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the IndentName
    */
   public String getIndentName( )
   {
      return IndentName;
   }

   /**
    * @param IndentName to set 
    */
   public void setIndentName( String IndentName )
   {
      this.IndentName = IndentName;
   }

   /**
    * @return the IndentLvl
    */
   public Integer getIndentLvl( )
   {
      return IndentLvl;
   }

   /**
    * @param IndentLvl to set 
    */
   public void setIndentLvl( Integer IndentLvl )
   {
      this.IndentLvl = IndentLvl;
   }

   /**
    * @return the Create
    */
   public String getCreate( )
   {
      return Create;
   }

   /**
    * @param Create to set 
    */
   public void setCreate( String Create )
   {
      this.Create = Create;
   }

   /**
    * @return the Delete
    */
   public String getDelete( )
   {
      return Delete;
   }

   /**
    * @param Delete to set 
    */
   public void setDelete( String Delete )
   {
      this.Delete = Delete;
   }

   /**
    * @return the Include
    */
   public String getInclude( )
   {
      return Include;
   }

   /**
    * @param Include to set 
    */
   public void setInclude( String Include )
   {
      this.Include = Include;
   }

   /**
    * @return the InclSrc
    */
   public String getInclSrc( )
   {
      return InclSrc;
   }

   /**
    * @param InclSrc to set 
    */
   public void setInclSrc( String InclSrc )
   {
      this.InclSrc = InclSrc;
   }

   /**
    * @return the Exclude
    */
   public String getExclude( )
   {
      return Exclude;
   }

   /**
    * @param Exclude to set 
    */
   public void setExclude( String Exclude )
   {
      this.Exclude = Exclude;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the Recursive
    */
   public String getRecursive( )
   {
      return Recursive;
   }

   /**
    * @param Recursive to set 
    */
   public void setRecursive( String Recursive )
   {
      this.Recursive = Recursive;
   }

   /**
    * @return the AutoCreate
    */
   public String getAutoCreate( )
   {
      return AutoCreate;
   }

   /**
    * @param AutoCreate to set 
    */
   public void setAutoCreate( String AutoCreate )
   {
      this.AutoCreate = AutoCreate;
   }

   /**
    * @return the Derived
    */
   public String getDerived( )
   {
      return Derived;
   }

   /**
    * @param Derived to set 
    */
   public void setDerived( String Derived )
   {
      this.Derived = Derived;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the SeqType
    */
   public String getSeqType( )
   {
      return SeqType;
   }

   /**
    * @param SeqType to set 
    */
   public void setSeqType( String SeqType )
   {
      this.SeqType = SeqType;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the Abstract
    */
   public String getAbstract( )
   {
      return Abstract;
   }

   /**
    * @param Abstract to set 
    */
   public void setAbstract( String Abstract )
   {
      this.Abstract = Abstract;
   }

   /**
    * @return the ParentDeleteBehave
    */
   public String getParentDeleteBehave( )
   {
      return ParentDeleteBehave;
   }

   /**
    * @param ParentDeleteBehave to set 
    */
   public void setParentDeleteBehave( String ParentDeleteBehave )
   {
      this.ParentDeleteBehave = ParentDeleteBehave;
   }

   /**
    * @return the DupEntityInstance
    */
   public String getDupEntityInstance( )
   {
      return DupEntityInstance;
   }

   /**
    * @param DupEntityInstance to set 
    */
   public void setDupEntityInstance( String DupEntityInstance )
   {
      this.DupEntityInstance = DupEntityInstance;
   }

   /**
    * @return the DupRelationshipInstance
    */
   public String getDupRelationshipInstance( )
   {
      return DupRelationshipInstance;
   }

   /**
    * @param DupRelationshipInstance to set 
    */
   public void setDupRelationshipInstance( String DupRelationshipInstance )
   {
      this.DupRelationshipInstance = DupRelationshipInstance;
   }

   /**
    * @return the RelLinkIndicator
    */
   public String getRelLinkIndicator( )
   {
      return RelLinkIndicator;
   }

   /**
    * @param RelLinkIndicator to set 
    */
   public void setRelLinkIndicator( String RelLinkIndicator )
   {
      this.RelLinkIndicator = RelLinkIndicator;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the CreateConstraint
    */
   public String getCreateConstraint( )
   {
      return CreateConstraint;
   }

   /**
    * @param CreateConstraint to set 
    */
   public void setCreateConstraint( String CreateConstraint )
   {
      this.CreateConstraint = CreateConstraint;
   }

   /**
    * @return the DeleteConstraint
    */
   public String getDeleteConstraint( )
   {
      return DeleteConstraint;
   }

   /**
    * @param DeleteConstraint to set 
    */
   public void setDeleteConstraint( String DeleteConstraint )
   {
      this.DeleteConstraint = DeleteConstraint;
   }

   /**
    * @return the IncludeConstraint
    */
   public String getIncludeConstraint( )
   {
      return IncludeConstraint;
   }

   /**
    * @param IncludeConstraint to set 
    */
   public void setIncludeConstraint( String IncludeConstraint )
   {
      this.IncludeConstraint = IncludeConstraint;
   }

   /**
    * @return the ExcludeConstraint
    */
   public String getExcludeConstraint( )
   {
      return ExcludeConstraint;
   }

   /**
    * @param ExcludeConstraint to set 
    */
   public void setExcludeConstraint( String ExcludeConstraint )
   {
      this.ExcludeConstraint = ExcludeConstraint;
   }

   /**
    * @return the AcceptConstraint
    */
   public String getAcceptConstraint( )
   {
      return AcceptConstraint;
   }

   /**
    * @param AcceptConstraint to set 
    */
   public void setAcceptConstraint( String AcceptConstraint )
   {
      this.AcceptConstraint = AcceptConstraint;
   }

   /**
    * @return the CancelConstraint
    */
   public String getCancelConstraint( )
   {
      return CancelConstraint;
   }

   /**
    * @param CancelConstraint to set 
    */
   public void setCancelConstraint( String CancelConstraint )
   {
      this.CancelConstraint = CancelConstraint;
   }

   /**
    * @return the SeqNo
    */
   public Integer getSeqNo( )
   {
      return SeqNo;
   }

   /**
    * @param SeqNo to set 
    */
   public void setSeqNo( Integer SeqNo )
   {
      this.SeqNo = SeqNo;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the MultipleChildLimit
    */
   public Integer getMultipleChildLimit( )
   {
      return MultipleChildLimit;
   }

   /**
    * @param MultipleChildLimit to set 
    */
   public void setMultipleChildLimit( Integer MultipleChildLimit )
   {
      this.MultipleChildLimit = MultipleChildLimit;
   }

   /**
    * @return the XML_Name
    */
   public String getXML_Name( )
   {
      return XML_Name;
   }

   /**
    * @param XML_Name to set 
    */
   public void setXML_Name( String XML_Name )
   {
      this.XML_Name = XML_Name;
   }

   /**
    * @return the LazyLoadFlag
    */
   public String getLazyLoadFlag( )
   {
      return LazyLoadFlag;
   }

   /**
    * @param LazyLoadFlag to set 
    */
   public void setLazyLoadFlag( String LazyLoadFlag )
   {
      this.LazyLoadFlag = LazyLoadFlag;
   }

   /**
    * @return the ReportDisplayFlag
    */
   public String getReportDisplayFlag( )
   {
      return ReportDisplayFlag;
   }

   /**
    * @param ReportDisplayFlag to set 
    */
   public void setReportDisplayFlag( String ReportDisplayFlag )
   {
      this.ReportDisplayFlag = ReportDisplayFlag;
   }

   public int loadListCtrlLOD_EntityEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      IndentName = cursor.getStringFromAttribute( "IndentName" );  if ( IndentName == null ) IndentName = "";
      IndentLvl = cursor.getIntegerFromAttribute( "IndentLvl" );  if ( IndentLvl == null ) IndentLvl = 0;
      Create = cursor.getStringFromAttribute( "Create" );  if ( Create == null ) Create = "";
      Delete = cursor.getStringFromAttribute( "Delete" );  if ( Delete == null ) Delete = "";
      Include = cursor.getStringFromAttribute( "Include" );  if ( Include == null ) Include = "";
      InclSrc = cursor.getStringFromAttribute( "InclSrc" );  if ( InclSrc == null ) InclSrc = "";
      Exclude = cursor.getStringFromAttribute( "Exclude" );  if ( Exclude == null ) Exclude = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      Recursive = cursor.getStringFromAttribute( "Recursive" );  if ( Recursive == null ) Recursive = "";
      AutoCreate = cursor.getStringFromAttribute( "AutoCreate" );  if ( AutoCreate == null ) AutoCreate = "";
      Derived = cursor.getStringFromAttribute( "Derived" );  if ( Derived == null ) Derived = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      SeqType = cursor.getStringFromAttribute( "SeqType" );  if ( SeqType == null ) SeqType = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      Abstract = cursor.getStringFromAttribute( "Abstract" );  if ( Abstract == null ) Abstract = "";
      ParentDeleteBehave = cursor.getStringFromAttribute( "ParentDeleteBehave" );  if ( ParentDeleteBehave == null ) ParentDeleteBehave = "";
      DupEntityInstance = cursor.getStringFromAttribute( "DupEntityInstance" );  if ( DupEntityInstance == null ) DupEntityInstance = "";
      DupRelationshipInstance = cursor.getStringFromAttribute( "DupRelationshipInstance" );  if ( DupRelationshipInstance == null ) DupRelationshipInstance = "";
      RelLinkIndicator = cursor.getStringFromAttribute( "RelLinkIndicator" );  if ( RelLinkIndicator == null ) RelLinkIndicator = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      CreateConstraint = cursor.getStringFromAttribute( "CreateConstraint" );  if ( CreateConstraint == null ) CreateConstraint = "";
      DeleteConstraint = cursor.getStringFromAttribute( "DeleteConstraint" );  if ( DeleteConstraint == null ) DeleteConstraint = "";
      IncludeConstraint = cursor.getStringFromAttribute( "IncludeConstraint" );  if ( IncludeConstraint == null ) IncludeConstraint = "";
      ExcludeConstraint = cursor.getStringFromAttribute( "ExcludeConstraint" );  if ( ExcludeConstraint == null ) ExcludeConstraint = "";
      AcceptConstraint = cursor.getStringFromAttribute( "AcceptConstraint" );  if ( AcceptConstraint == null ) AcceptConstraint = "";
      CancelConstraint = cursor.getStringFromAttribute( "CancelConstraint" );  if ( CancelConstraint == null ) CancelConstraint = "";
      SeqNo = cursor.getIntegerFromAttribute( "SeqNo" );  if ( SeqNo == null ) SeqNo = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      MultipleChildLimit = cursor.getIntegerFromAttribute( "MultipleChildLimit" );  if ( MultipleChildLimit == null ) MultipleChildLimit = 0;
      XML_Name = cursor.getStringFromAttribute( "XML_Name" );  if ( XML_Name == null ) XML_Name = "";
      LazyLoadFlag = cursor.getStringFromAttribute( "LazyLoadFlag" );  if ( LazyLoadFlag == null ) LazyLoadFlag = "";
      ReportDisplayFlag = cursor.getStringFromAttribute( "ReportDisplayFlag" );  if ( ReportDisplayFlag == null ) ReportDisplayFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ListCtrlViewObjRefImpl implements ListCtrlViewObjRef
{
   protected Integer ZKey;
   protected String  Name;
   protected String  Desc;
   protected Integer Level;
   protected String  IsDrivingViewForReportFlag;


   // ctor
   protected ListCtrlViewObjRefImpl( EntityCursor cursor )
   {
      loadListCtrlViewObjRefEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Level
    */
   public Integer getLevel( )
   {
      return Level;
   }

   /**
    * @param Level to set 
    */
   public void setLevel( Integer Level )
   {
      this.Level = Level;
   }

   /**
    * @return the IsDrivingViewForReportFlag
    */
   public String getIsDrivingViewForReportFlag( )
   {
      return IsDrivingViewForReportFlag;
   }

   /**
    * @param IsDrivingViewForReportFlag to set 
    */
   public void setIsDrivingViewForReportFlag( String IsDrivingViewForReportFlag )
   {
      this.IsDrivingViewForReportFlag = IsDrivingViewForReportFlag;
   }

   public int loadListCtrlViewObjRefEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Level = cursor.getIntegerFromAttribute( "Level" );  if ( Level == null ) Level = 0;
      IsDrivingViewForReportFlag = cursor.getStringFromAttribute( "IsDrivingViewForReportFlag" );  if ( IsDrivingViewForReportFlag == null ) IsDrivingViewForReportFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ListCtrlContextImpl implements ListCtrlContext
{
   protected Integer ZKey;
   protected String  Name;
   protected String  Desc;
   protected Integer DecimalFormat;
   protected String  EditString;
   protected String  IsDefault;
   protected String  DIL_Text;


   // ctor
   protected ListCtrlContextImpl( EntityCursor cursor )
   {
      loadListCtrlContextEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the DecimalFormat
    */
   public Integer getDecimalFormat( )
   {
      return DecimalFormat;
   }

   /**
    * @param DecimalFormat to set 
    */
   public void setDecimalFormat( Integer DecimalFormat )
   {
      this.DecimalFormat = DecimalFormat;
   }

   /**
    * @return the EditString
    */
   public String getEditString( )
   {
      return EditString;
   }

   /**
    * @param EditString to set 
    */
   public void setEditString( String EditString )
   {
      this.EditString = EditString;
   }

   /**
    * @return the IsDefault
    */
   public String getIsDefault( )
   {
      return IsDefault;
   }

   /**
    * @param IsDefault to set 
    */
   public void setIsDefault( String IsDefault )
   {
      this.IsDefault = IsDefault;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   public int loadListCtrlContextEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      DecimalFormat = cursor.getIntegerFromAttribute( "DecimalFormat" );  if ( DecimalFormat == null ) DecimalFormat = 0;
      EditString = cursor.getStringFromAttribute( "EditString" );  if ( EditString == null ) EditString = "";
      IsDefault = cursor.getStringFromAttribute( "IsDefault" );  if ( IsDefault == null ) IsDefault = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndEventImpl implements WndEvent
{
   protected Integer Type;
   protected String  Accelerator;
   protected Integer ZKey;


   // ctor
   protected WndEventImpl( EntityCursor cursor )
   {
      loadWndEventEntityStructure( cursor );
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the Accelerator
    */
   public String getAccelerator( )
   {
      return Accelerator;
   }

   /**
    * @param Accelerator to set 
    */
   public void setAccelerator( String Accelerator )
   {
      this.Accelerator = Accelerator;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadWndEventEntityStructure( EntityCursor cursor )
   {
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Accelerator = cursor.getStringFromAttribute( "Accelerator" );  if ( Accelerator == null ) Accelerator = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndActImpl implements WndAct
{
   protected String  Tag;
   protected String  ActionTypeAssociatedText;
   protected String  NoMap;
   protected Integer Type;
   protected String  TypeData;
   protected Integer ZKey;
   protected String  DialogName;
   protected String  WindowName;
   protected String  DLL;
   protected String  WebJavaScript;
   protected Integer OperCtrl;
   protected Integer SB_SubAction;
   protected Integer SB_NextPrev;
   protected Integer SB_DeleteNull;
   protected Integer SB_ActionDisabling;
   protected String  PopupMenuName;
   protected String  WebJavaScriptLocation;


   // ctor
   protected WndActImpl( EntityCursor cursor )
   {
      loadWndActEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ActionTypeAssociatedText
    */
   public String getActionTypeAssociatedText( )
   {
      return ActionTypeAssociatedText;
   }

   /**
    * @param ActionTypeAssociatedText to set 
    */
   public void setActionTypeAssociatedText( String ActionTypeAssociatedText )
   {
      this.ActionTypeAssociatedText = ActionTypeAssociatedText;
   }

   /**
    * @return the NoMap
    */
   public String getNoMap( )
   {
      return NoMap;
   }

   /**
    * @param NoMap to set 
    */
   public void setNoMap( String NoMap )
   {
      this.NoMap = NoMap;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the TypeData
    */
   public String getTypeData( )
   {
      return TypeData;
   }

   /**
    * @param TypeData to set 
    */
   public void setTypeData( String TypeData )
   {
      this.TypeData = TypeData;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DialogName
    */
   public String getDialogName( )
   {
      return DialogName;
   }

   /**
    * @param DialogName to set 
    */
   public void setDialogName( String DialogName )
   {
      this.DialogName = DialogName;
   }

   /**
    * @return the WindowName
    */
   public String getWindowName( )
   {
      return WindowName;
   }

   /**
    * @param WindowName to set 
    */
   public void setWindowName( String WindowName )
   {
      this.WindowName = WindowName;
   }

   /**
    * @return the DLL
    */
   public String getDLL( )
   {
      return DLL;
   }

   /**
    * @param DLL to set 
    */
   public void setDLL( String DLL )
   {
      this.DLL = DLL;
   }

   /**
    * @return the WebJavaScript
    */
   public String getWebJavaScript( )
   {
      return WebJavaScript;
   }

   /**
    * @param WebJavaScript to set 
    */
   public void setWebJavaScript( String WebJavaScript )
   {
      this.WebJavaScript = WebJavaScript;
   }

   /**
    * @return the OperCtrl
    */
   public Integer getOperCtrl( )
   {
      return OperCtrl;
   }

   /**
    * @param OperCtrl to set 
    */
   public void setOperCtrl( Integer OperCtrl )
   {
      this.OperCtrl = OperCtrl;
   }

   /**
    * @return the SB_SubAction
    */
   public Integer getSB_SubAction( )
   {
      return SB_SubAction;
   }

   /**
    * @param SB_SubAction to set 
    */
   public void setSB_SubAction( Integer SB_SubAction )
   {
      this.SB_SubAction = SB_SubAction;
   }

   /**
    * @return the SB_NextPrev
    */
   public Integer getSB_NextPrev( )
   {
      return SB_NextPrev;
   }

   /**
    * @param SB_NextPrev to set 
    */
   public void setSB_NextPrev( Integer SB_NextPrev )
   {
      this.SB_NextPrev = SB_NextPrev;
   }

   /**
    * @return the SB_DeleteNull
    */
   public Integer getSB_DeleteNull( )
   {
      return SB_DeleteNull;
   }

   /**
    * @param SB_DeleteNull to set 
    */
   public void setSB_DeleteNull( Integer SB_DeleteNull )
   {
      this.SB_DeleteNull = SB_DeleteNull;
   }

   /**
    * @return the SB_ActionDisabling
    */
   public Integer getSB_ActionDisabling( )
   {
      return SB_ActionDisabling;
   }

   /**
    * @param SB_ActionDisabling to set 
    */
   public void setSB_ActionDisabling( Integer SB_ActionDisabling )
   {
      this.SB_ActionDisabling = SB_ActionDisabling;
   }

   /**
    * @return the PopupMenuName
    */
   public String getPopupMenuName( )
   {
      return PopupMenuName;
   }

   /**
    * @param PopupMenuName to set 
    */
   public void setPopupMenuName( String PopupMenuName )
   {
      this.PopupMenuName = PopupMenuName;
   }

   /**
    * @return the WebJavaScriptLocation
    */
   public String getWebJavaScriptLocation( )
   {
      return WebJavaScriptLocation;
   }

   /**
    * @param WebJavaScriptLocation to set 
    */
   public void setWebJavaScriptLocation( String WebJavaScriptLocation )
   {
      this.WebJavaScriptLocation = WebJavaScriptLocation;
   }

   public int loadWndActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ActionTypeAssociatedText = cursor.getStringFromAttribute( "ActionTypeAssociatedText" );  if ( ActionTypeAssociatedText == null ) ActionTypeAssociatedText = "";
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      TypeData = cursor.getStringFromAttribute( "TypeData" );  if ( TypeData == null ) TypeData = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DialogName = cursor.getStringFromAttribute( "DialogName" );  if ( DialogName == null ) DialogName = "";
      WindowName = cursor.getStringFromAttribute( "WindowName" );  if ( WindowName == null ) WindowName = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      WebJavaScript = cursor.getStringFromAttribute( "WebJavaScript" );  if ( WebJavaScript == null ) WebJavaScript = "";
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      SB_SubAction = cursor.getIntegerFromAttribute( "SB_SubAction" );  if ( SB_SubAction == null ) SB_SubAction = 0;
      SB_NextPrev = cursor.getIntegerFromAttribute( "SB_NextPrev" );  if ( SB_NextPrev == null ) SB_NextPrev = 0;
      SB_DeleteNull = cursor.getIntegerFromAttribute( "SB_DeleteNull" );  if ( SB_DeleteNull == null ) SB_DeleteNull = 0;
      SB_ActionDisabling = cursor.getIntegerFromAttribute( "SB_ActionDisabling" );  if ( SB_ActionDisabling == null ) SB_ActionDisabling = 0;
      PopupMenuName = cursor.getStringFromAttribute( "PopupMenuName" );  if ( PopupMenuName == null ) PopupMenuName = "";
      WebJavaScriptLocation = cursor.getStringFromAttribute( "WebJavaScriptLocation" );  if ( WebJavaScriptLocation == null ) WebJavaScriptLocation = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActionImpl implements Action
{
   protected String  Tag;
   protected String  ActionTypeAssociatedText;
   protected String  NoMap;
   protected Integer Type;
   protected String  TypeData;
   protected Integer ZKey;
   protected String  DialogName;
   protected String  WindowName;
   protected String  DLL;
   protected Integer OperCtrl;
   protected Integer SB_SubAction;
   protected Integer SB_NextPrev;
   protected Integer SB_DeleteNull;
   protected Integer SB_ActionDisabling;
   protected String  PopupMenuName;
   protected String  WebHTML_TransferAddress;
   protected String  WebJavaScript;
   protected String  WebJavaScriptLocation;
   protected String  ParentIsGridOrGrp;


   // ctor
   protected ActionImpl( EntityCursor cursor )
   {
      loadActionEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ActionTypeAssociatedText
    */
   public String getActionTypeAssociatedText( )
   {
      return ActionTypeAssociatedText;
   }

   /**
    * @param ActionTypeAssociatedText to set 
    */
   public void setActionTypeAssociatedText( String ActionTypeAssociatedText )
   {
      this.ActionTypeAssociatedText = ActionTypeAssociatedText;
   }

   /**
    * @return the NoMap
    */
   public String getNoMap( )
   {
      return NoMap;
   }

   /**
    * @param NoMap to set 
    */
   public void setNoMap( String NoMap )
   {
      this.NoMap = NoMap;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the TypeData
    */
   public String getTypeData( )
   {
      return TypeData;
   }

   /**
    * @param TypeData to set 
    */
   public void setTypeData( String TypeData )
   {
      this.TypeData = TypeData;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DialogName
    */
   public String getDialogName( )
   {
      return DialogName;
   }

   /**
    * @param DialogName to set 
    */
   public void setDialogName( String DialogName )
   {
      this.DialogName = DialogName;
   }

   /**
    * @return the WindowName
    */
   public String getWindowName( )
   {
      return WindowName;
   }

   /**
    * @param WindowName to set 
    */
   public void setWindowName( String WindowName )
   {
      this.WindowName = WindowName;
   }

   /**
    * @return the DLL
    */
   public String getDLL( )
   {
      return DLL;
   }

   /**
    * @param DLL to set 
    */
   public void setDLL( String DLL )
   {
      this.DLL = DLL;
   }

   /**
    * @return the OperCtrl
    */
   public Integer getOperCtrl( )
   {
      return OperCtrl;
   }

   /**
    * @param OperCtrl to set 
    */
   public void setOperCtrl( Integer OperCtrl )
   {
      this.OperCtrl = OperCtrl;
   }

   /**
    * @return the SB_SubAction
    */
   public Integer getSB_SubAction( )
   {
      return SB_SubAction;
   }

   /**
    * @param SB_SubAction to set 
    */
   public void setSB_SubAction( Integer SB_SubAction )
   {
      this.SB_SubAction = SB_SubAction;
   }

   /**
    * @return the SB_NextPrev
    */
   public Integer getSB_NextPrev( )
   {
      return SB_NextPrev;
   }

   /**
    * @param SB_NextPrev to set 
    */
   public void setSB_NextPrev( Integer SB_NextPrev )
   {
      this.SB_NextPrev = SB_NextPrev;
   }

   /**
    * @return the SB_DeleteNull
    */
   public Integer getSB_DeleteNull( )
   {
      return SB_DeleteNull;
   }

   /**
    * @param SB_DeleteNull to set 
    */
   public void setSB_DeleteNull( Integer SB_DeleteNull )
   {
      this.SB_DeleteNull = SB_DeleteNull;
   }

   /**
    * @return the SB_ActionDisabling
    */
   public Integer getSB_ActionDisabling( )
   {
      return SB_ActionDisabling;
   }

   /**
    * @param SB_ActionDisabling to set 
    */
   public void setSB_ActionDisabling( Integer SB_ActionDisabling )
   {
      this.SB_ActionDisabling = SB_ActionDisabling;
   }

   /**
    * @return the PopupMenuName
    */
   public String getPopupMenuName( )
   {
      return PopupMenuName;
   }

   /**
    * @param PopupMenuName to set 
    */
   public void setPopupMenuName( String PopupMenuName )
   {
      this.PopupMenuName = PopupMenuName;
   }

   /**
    * @return the WebHTML_TransferAddress
    */
   public String getWebHTML_TransferAddress( )
   {
      return WebHTML_TransferAddress;
   }

   /**
    * @param WebHTML_TransferAddress to set 
    */
   public void setWebHTML_TransferAddress( String WebHTML_TransferAddress )
   {
      this.WebHTML_TransferAddress = WebHTML_TransferAddress;
   }

   /**
    * @return the WebJavaScript
    */
   public String getWebJavaScript( )
   {
      return WebJavaScript;
   }

   /**
    * @param WebJavaScript to set 
    */
   public void setWebJavaScript( String WebJavaScript )
   {
      this.WebJavaScript = WebJavaScript;
   }

   /**
    * @return the WebJavaScriptLocation
    */
   public String getWebJavaScriptLocation( )
   {
      return WebJavaScriptLocation;
   }

   /**
    * @param WebJavaScriptLocation to set 
    */
   public void setWebJavaScriptLocation( String WebJavaScriptLocation )
   {
      this.WebJavaScriptLocation = WebJavaScriptLocation;
   }

   /**
    * @return the ParentIsGridOrGrp
    */
   public String getParentIsGridOrGrp( )
   {
      return ParentIsGridOrGrp;
   }

   /**
    * @param ParentIsGridOrGrp to set 
    */
   public void setParentIsGridOrGrp( String ParentIsGridOrGrp )
   {
      this.ParentIsGridOrGrp = ParentIsGridOrGrp;
   }

   public int loadActionEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ActionTypeAssociatedText = cursor.getStringFromAttribute( "ActionTypeAssociatedText" );  if ( ActionTypeAssociatedText == null ) ActionTypeAssociatedText = "";
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      TypeData = cursor.getStringFromAttribute( "TypeData" );  if ( TypeData == null ) TypeData = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DialogName = cursor.getStringFromAttribute( "DialogName" );  if ( DialogName == null ) DialogName = "";
      WindowName = cursor.getStringFromAttribute( "WindowName" );  if ( WindowName == null ) WindowName = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      SB_SubAction = cursor.getIntegerFromAttribute( "SB_SubAction" );  if ( SB_SubAction == null ) SB_SubAction = 0;
      SB_NextPrev = cursor.getIntegerFromAttribute( "SB_NextPrev" );  if ( SB_NextPrev == null ) SB_NextPrev = 0;
      SB_DeleteNull = cursor.getIntegerFromAttribute( "SB_DeleteNull" );  if ( SB_DeleteNull == null ) SB_DeleteNull = 0;
      SB_ActionDisabling = cursor.getIntegerFromAttribute( "SB_ActionDisabling" );  if ( SB_ActionDisabling == null ) SB_ActionDisabling = 0;
      PopupMenuName = cursor.getStringFromAttribute( "PopupMenuName" );  if ( PopupMenuName == null ) PopupMenuName = "";
      WebHTML_TransferAddress = cursor.getStringFromAttribute( "WebHTML_TransferAddress" );  if ( WebHTML_TransferAddress == null ) WebHTML_TransferAddress = "";
      WebJavaScript = cursor.getStringFromAttribute( "WebJavaScript" );  if ( WebJavaScript == null ) WebJavaScript = "";
      WebJavaScriptLocation = cursor.getStringFromAttribute( "WebJavaScriptLocation" );  if ( WebJavaScriptLocation == null ) WebJavaScriptLocation = "";
      ParentIsGridOrGrp = cursor.getStringFromAttribute( "ParentIsGridOrGrp" );  if ( ParentIsGridOrGrp == null ) ParentIsGridOrGrp = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActMapImpl implements ActMap
{
   protected String  Tag;
   protected Integer ZKey;
   protected Integer SeqNo_DlgAct;
   protected String  Type;
   protected Integer SeqNo_DlgCtrl;


   // ctor
   protected ActMapImpl( EntityCursor cursor )
   {
      loadActMapEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the SeqNo_DlgAct
    */
   public Integer getSeqNo_DlgAct( )
   {
      return SeqNo_DlgAct;
   }

   /**
    * @param SeqNo_DlgAct to set 
    */
   public void setSeqNo_DlgAct( Integer SeqNo_DlgAct )
   {
      this.SeqNo_DlgAct = SeqNo_DlgAct;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the SeqNo_DlgCtrl
    */
   public Integer getSeqNo_DlgCtrl( )
   {
      return SeqNo_DlgCtrl;
   }

   /**
    * @param SeqNo_DlgCtrl to set 
    */
   public void setSeqNo_DlgCtrl( Integer SeqNo_DlgCtrl )
   {
      this.SeqNo_DlgCtrl = SeqNo_DlgCtrl;
   }

   public int loadActMapEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      SeqNo_DlgAct = cursor.getIntegerFromAttribute( "SeqNo_DlgAct" );  if ( SeqNo_DlgAct == null ) SeqNo_DlgAct = 0;
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      SeqNo_DlgCtrl = cursor.getIntegerFromAttribute( "SeqNo_DlgCtrl" );  if ( SeqNo_DlgCtrl == null ) SeqNo_DlgCtrl = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActMapLOD_EntityImpl implements ActMapLOD_Entity
{
   protected String  Name;
   protected String  IndentName;
   protected Integer IndentLvl;
   protected Integer ZKey;
   protected String  Create;
   protected String  Delete;
   protected String  Update;
   protected String  Include;
   protected String  InclSrc;
   protected String  Exclude;
   protected String  Hidden;
   protected String  Recursive;
   protected String  CreateConstraint;
   protected String  DeleteConstraint;
   protected String  IncludeConstraint;
   protected String  ExcludeConstraint;
   protected String  AcceptConstraint;
   protected String  CancelConstraint;
   protected Integer SeqNo;
   protected Integer DataLocking;
   protected Integer MultipleChildLimit;
   protected String  AutoCreate;
   protected String  Derived;
   protected String  SeqType;
   protected String  Work;
   protected String  ParentDeleteBehave;
   protected String  DupEntityInstance;
   protected String  DupRelationshipInstance;
   protected String  RelLinkIndicator;
   protected String  Desc;
   protected String  Abstract;
   protected String  XML_Name;
   protected String  LazyLoadFlag;
   protected String  ReportDisplayFlag;


   // ctor
   protected ActMapLOD_EntityImpl( EntityCursor cursor )
   {
      loadActMapLOD_EntityEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the IndentName
    */
   public String getIndentName( )
   {
      return IndentName;
   }

   /**
    * @param IndentName to set 
    */
   public void setIndentName( String IndentName )
   {
      this.IndentName = IndentName;
   }

   /**
    * @return the IndentLvl
    */
   public Integer getIndentLvl( )
   {
      return IndentLvl;
   }

   /**
    * @param IndentLvl to set 
    */
   public void setIndentLvl( Integer IndentLvl )
   {
      this.IndentLvl = IndentLvl;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Create
    */
   public String getCreate( )
   {
      return Create;
   }

   /**
    * @param Create to set 
    */
   public void setCreate( String Create )
   {
      this.Create = Create;
   }

   /**
    * @return the Delete
    */
   public String getDelete( )
   {
      return Delete;
   }

   /**
    * @param Delete to set 
    */
   public void setDelete( String Delete )
   {
      this.Delete = Delete;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the Include
    */
   public String getInclude( )
   {
      return Include;
   }

   /**
    * @param Include to set 
    */
   public void setInclude( String Include )
   {
      this.Include = Include;
   }

   /**
    * @return the InclSrc
    */
   public String getInclSrc( )
   {
      return InclSrc;
   }

   /**
    * @param InclSrc to set 
    */
   public void setInclSrc( String InclSrc )
   {
      this.InclSrc = InclSrc;
   }

   /**
    * @return the Exclude
    */
   public String getExclude( )
   {
      return Exclude;
   }

   /**
    * @param Exclude to set 
    */
   public void setExclude( String Exclude )
   {
      this.Exclude = Exclude;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the Recursive
    */
   public String getRecursive( )
   {
      return Recursive;
   }

   /**
    * @param Recursive to set 
    */
   public void setRecursive( String Recursive )
   {
      this.Recursive = Recursive;
   }

   /**
    * @return the CreateConstraint
    */
   public String getCreateConstraint( )
   {
      return CreateConstraint;
   }

   /**
    * @param CreateConstraint to set 
    */
   public void setCreateConstraint( String CreateConstraint )
   {
      this.CreateConstraint = CreateConstraint;
   }

   /**
    * @return the DeleteConstraint
    */
   public String getDeleteConstraint( )
   {
      return DeleteConstraint;
   }

   /**
    * @param DeleteConstraint to set 
    */
   public void setDeleteConstraint( String DeleteConstraint )
   {
      this.DeleteConstraint = DeleteConstraint;
   }

   /**
    * @return the IncludeConstraint
    */
   public String getIncludeConstraint( )
   {
      return IncludeConstraint;
   }

   /**
    * @param IncludeConstraint to set 
    */
   public void setIncludeConstraint( String IncludeConstraint )
   {
      this.IncludeConstraint = IncludeConstraint;
   }

   /**
    * @return the ExcludeConstraint
    */
   public String getExcludeConstraint( )
   {
      return ExcludeConstraint;
   }

   /**
    * @param ExcludeConstraint to set 
    */
   public void setExcludeConstraint( String ExcludeConstraint )
   {
      this.ExcludeConstraint = ExcludeConstraint;
   }

   /**
    * @return the AcceptConstraint
    */
   public String getAcceptConstraint( )
   {
      return AcceptConstraint;
   }

   /**
    * @param AcceptConstraint to set 
    */
   public void setAcceptConstraint( String AcceptConstraint )
   {
      this.AcceptConstraint = AcceptConstraint;
   }

   /**
    * @return the CancelConstraint
    */
   public String getCancelConstraint( )
   {
      return CancelConstraint;
   }

   /**
    * @param CancelConstraint to set 
    */
   public void setCancelConstraint( String CancelConstraint )
   {
      this.CancelConstraint = CancelConstraint;
   }

   /**
    * @return the SeqNo
    */
   public Integer getSeqNo( )
   {
      return SeqNo;
   }

   /**
    * @param SeqNo to set 
    */
   public void setSeqNo( Integer SeqNo )
   {
      this.SeqNo = SeqNo;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the MultipleChildLimit
    */
   public Integer getMultipleChildLimit( )
   {
      return MultipleChildLimit;
   }

   /**
    * @param MultipleChildLimit to set 
    */
   public void setMultipleChildLimit( Integer MultipleChildLimit )
   {
      this.MultipleChildLimit = MultipleChildLimit;
   }

   /**
    * @return the AutoCreate
    */
   public String getAutoCreate( )
   {
      return AutoCreate;
   }

   /**
    * @param AutoCreate to set 
    */
   public void setAutoCreate( String AutoCreate )
   {
      this.AutoCreate = AutoCreate;
   }

   /**
    * @return the Derived
    */
   public String getDerived( )
   {
      return Derived;
   }

   /**
    * @param Derived to set 
    */
   public void setDerived( String Derived )
   {
      this.Derived = Derived;
   }

   /**
    * @return the SeqType
    */
   public String getSeqType( )
   {
      return SeqType;
   }

   /**
    * @param SeqType to set 
    */
   public void setSeqType( String SeqType )
   {
      this.SeqType = SeqType;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the ParentDeleteBehave
    */
   public String getParentDeleteBehave( )
   {
      return ParentDeleteBehave;
   }

   /**
    * @param ParentDeleteBehave to set 
    */
   public void setParentDeleteBehave( String ParentDeleteBehave )
   {
      this.ParentDeleteBehave = ParentDeleteBehave;
   }

   /**
    * @return the DupEntityInstance
    */
   public String getDupEntityInstance( )
   {
      return DupEntityInstance;
   }

   /**
    * @param DupEntityInstance to set 
    */
   public void setDupEntityInstance( String DupEntityInstance )
   {
      this.DupEntityInstance = DupEntityInstance;
   }

   /**
    * @return the DupRelationshipInstance
    */
   public String getDupRelationshipInstance( )
   {
      return DupRelationshipInstance;
   }

   /**
    * @param DupRelationshipInstance to set 
    */
   public void setDupRelationshipInstance( String DupRelationshipInstance )
   {
      this.DupRelationshipInstance = DupRelationshipInstance;
   }

   /**
    * @return the RelLinkIndicator
    */
   public String getRelLinkIndicator( )
   {
      return RelLinkIndicator;
   }

   /**
    * @param RelLinkIndicator to set 
    */
   public void setRelLinkIndicator( String RelLinkIndicator )
   {
      this.RelLinkIndicator = RelLinkIndicator;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Abstract
    */
   public String getAbstract( )
   {
      return Abstract;
   }

   /**
    * @param Abstract to set 
    */
   public void setAbstract( String Abstract )
   {
      this.Abstract = Abstract;
   }

   /**
    * @return the XML_Name
    */
   public String getXML_Name( )
   {
      return XML_Name;
   }

   /**
    * @param XML_Name to set 
    */
   public void setXML_Name( String XML_Name )
   {
      this.XML_Name = XML_Name;
   }

   /**
    * @return the LazyLoadFlag
    */
   public String getLazyLoadFlag( )
   {
      return LazyLoadFlag;
   }

   /**
    * @param LazyLoadFlag to set 
    */
   public void setLazyLoadFlag( String LazyLoadFlag )
   {
      this.LazyLoadFlag = LazyLoadFlag;
   }

   /**
    * @return the ReportDisplayFlag
    */
   public String getReportDisplayFlag( )
   {
      return ReportDisplayFlag;
   }

   /**
    * @param ReportDisplayFlag to set 
    */
   public void setReportDisplayFlag( String ReportDisplayFlag )
   {
      this.ReportDisplayFlag = ReportDisplayFlag;
   }

   public int loadActMapLOD_EntityEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      IndentName = cursor.getStringFromAttribute( "IndentName" );  if ( IndentName == null ) IndentName = "";
      IndentLvl = cursor.getIntegerFromAttribute( "IndentLvl" );  if ( IndentLvl == null ) IndentLvl = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Create = cursor.getStringFromAttribute( "Create" );  if ( Create == null ) Create = "";
      Delete = cursor.getStringFromAttribute( "Delete" );  if ( Delete == null ) Delete = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      Include = cursor.getStringFromAttribute( "Include" );  if ( Include == null ) Include = "";
      InclSrc = cursor.getStringFromAttribute( "InclSrc" );  if ( InclSrc == null ) InclSrc = "";
      Exclude = cursor.getStringFromAttribute( "Exclude" );  if ( Exclude == null ) Exclude = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      Recursive = cursor.getStringFromAttribute( "Recursive" );  if ( Recursive == null ) Recursive = "";
      CreateConstraint = cursor.getStringFromAttribute( "CreateConstraint" );  if ( CreateConstraint == null ) CreateConstraint = "";
      DeleteConstraint = cursor.getStringFromAttribute( "DeleteConstraint" );  if ( DeleteConstraint == null ) DeleteConstraint = "";
      IncludeConstraint = cursor.getStringFromAttribute( "IncludeConstraint" );  if ( IncludeConstraint == null ) IncludeConstraint = "";
      ExcludeConstraint = cursor.getStringFromAttribute( "ExcludeConstraint" );  if ( ExcludeConstraint == null ) ExcludeConstraint = "";
      AcceptConstraint = cursor.getStringFromAttribute( "AcceptConstraint" );  if ( AcceptConstraint == null ) AcceptConstraint = "";
      CancelConstraint = cursor.getStringFromAttribute( "CancelConstraint" );  if ( CancelConstraint == null ) CancelConstraint = "";
      SeqNo = cursor.getIntegerFromAttribute( "SeqNo" );  if ( SeqNo == null ) SeqNo = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      MultipleChildLimit = cursor.getIntegerFromAttribute( "MultipleChildLimit" );  if ( MultipleChildLimit == null ) MultipleChildLimit = 0;
      AutoCreate = cursor.getStringFromAttribute( "AutoCreate" );  if ( AutoCreate == null ) AutoCreate = "";
      Derived = cursor.getStringFromAttribute( "Derived" );  if ( Derived == null ) Derived = "";
      SeqType = cursor.getStringFromAttribute( "SeqType" );  if ( SeqType == null ) SeqType = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      ParentDeleteBehave = cursor.getStringFromAttribute( "ParentDeleteBehave" );  if ( ParentDeleteBehave == null ) ParentDeleteBehave = "";
      DupEntityInstance = cursor.getStringFromAttribute( "DupEntityInstance" );  if ( DupEntityInstance == null ) DupEntityInstance = "";
      DupRelationshipInstance = cursor.getStringFromAttribute( "DupRelationshipInstance" );  if ( DupRelationshipInstance == null ) DupRelationshipInstance = "";
      RelLinkIndicator = cursor.getStringFromAttribute( "RelLinkIndicator" );  if ( RelLinkIndicator == null ) RelLinkIndicator = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Abstract = cursor.getStringFromAttribute( "Abstract" );  if ( Abstract == null ) Abstract = "";
      XML_Name = cursor.getStringFromAttribute( "XML_Name" );  if ( XML_Name == null ) XML_Name = "";
      LazyLoadFlag = cursor.getStringFromAttribute( "LazyLoadFlag" );  if ( LazyLoadFlag == null ) LazyLoadFlag = "";
      ReportDisplayFlag = cursor.getStringFromAttribute( "ReportDisplayFlag" );  if ( ReportDisplayFlag == null ) ReportDisplayFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActMapViewImpl implements ActMapView
{
   protected Integer ZKey;
   protected String  LastSyncDate;
   protected String  Name;
   protected String  Desc;
   protected Integer Level;
   protected String  IsDrivingViewForReportFlag;


   // ctor
   protected ActMapViewImpl( EntityCursor cursor )
   {
      loadActMapViewEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Level
    */
   public Integer getLevel( )
   {
      return Level;
   }

   /**
    * @param Level to set 
    */
   public void setLevel( Integer Level )
   {
      this.Level = Level;
   }

   /**
    * @return the IsDrivingViewForReportFlag
    */
   public String getIsDrivingViewForReportFlag( )
   {
      return IsDrivingViewForReportFlag;
   }

   /**
    * @param IsDrivingViewForReportFlag to set 
    */
   public void setIsDrivingViewForReportFlag( String IsDrivingViewForReportFlag )
   {
      this.IsDrivingViewForReportFlag = IsDrivingViewForReportFlag;
   }

   public int loadActMapViewEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Level = cursor.getIntegerFromAttribute( "Level" );  if ( Level == null ) Level = 0;
      IsDrivingViewForReportFlag = cursor.getStringFromAttribute( "IsDrivingViewForReportFlag" );  if ( IsDrivingViewForReportFlag == null ) IsDrivingViewForReportFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActWndEventImpl implements ActWndEvent
{
   protected Integer Type;
   protected String  Accelerator;
   protected Integer ZKey;
   protected String  EventName;


   // ctor
   protected ActWndEventImpl( EntityCursor cursor )
   {
      loadActWndEventEntityStructure( cursor );
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the Accelerator
    */
   public String getAccelerator( )
   {
      return Accelerator;
   }

   /**
    * @param Accelerator to set 
    */
   public void setAccelerator( String Accelerator )
   {
      this.Accelerator = Accelerator;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the EventName
    */
   public String getEventName( )
   {
      return EventName;
   }

   /**
    * @param EventName to set 
    */
   public void setEventName( String EventName )
   {
      this.EventName = EventName;
   }

   public int loadActWndEventEntityStructure( EntityCursor cursor )
   {
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Accelerator = cursor.getStringFromAttribute( "Accelerator" );  if ( Accelerator == null ) Accelerator = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      EventName = cursor.getStringFromAttribute( "EventName" );  if ( EventName == null ) EventName = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActEventImpl implements ActEvent
{
   protected Integer Type;
   protected Integer ZKey;


   // ctor
   protected ActEventImpl( EntityCursor cursor )
   {
      loadActEventEntityStructure( cursor );
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadActEventEntityStructure( EntityCursor cursor )
   {
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActCtrlImpl implements ActCtrl
{
   protected String  Tag;
   protected String  Text;
   protected Integer ZKey;
   protected Integer Type;
   protected Integer Subtype;
   protected Integer IdNbr;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Blob    CtrlBOI;
   protected Integer Underline;
   protected Integer SyncKey;
   protected String  DD_TargetKey;
   protected String  DD_SourceKey;
   protected Integer OptionFlags;
   protected String  DD_Type;
   protected String  DIL_Text;
   protected String  ReportGroupType;
   protected String  ForceHeaderPerEntity;
   protected Integer ExtendedStyle;
   protected String  GUID;
   protected Blob    Properties;
   protected String  WebreCAPTCHAPublicKey;
   protected String  WebreCAPTCHAPrivateKey;
   protected String  Placeholder;
   protected Blob    LKey;
   protected String  VisibleBorder;
   protected String  CenterJustify;
   protected String  RightJustify;
   protected String  CSS_Class;
   protected String  CSS_Id;
   protected String  CSS_Font;
   protected String  CSS_Position;
   protected String  CSS_Size;
   protected String  JavaScript;
   protected String  RadioOrCheckboxValue;
   protected String  WebFileName;
   protected String  WebCtrlType;
   protected String  WebColumnSpan;
   protected String  WebWrap;
   protected Integer BorderWidth;
   protected Integer BorderStyle;
   protected Integer BorderTop;
   protected Integer BorderBottom;
   protected Integer BorderLeft;
   protected Integer BorderRight;
   protected String  TextAlignHorizontal;
   protected Integer FontSize;
   protected String  TextBold;
   protected String  TextItalic;
   protected String  TextUnderline;
   protected String  LangID;


   // ctor
   protected ActCtrlImpl( EntityCursor cursor )
   {
      loadActCtrlEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the IdNbr
    */
   public Integer getIdNbr( )
   {
      return IdNbr;
   }

   /**
    * @param IdNbr to set 
    */
   public void setIdNbr( Integer IdNbr )
   {
      this.IdNbr = IdNbr;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the CtrlBOI
    */
   public Blob getCtrlBOI( )
   {
      return CtrlBOI;
   }

   /**
    * @param CtrlBOI to set 
    */
   public void setCtrlBOI( Blob CtrlBOI )
   {
      this.CtrlBOI = CtrlBOI;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the SyncKey
    */
   public Integer getSyncKey( )
   {
      return SyncKey;
   }

   /**
    * @param SyncKey to set 
    */
   public void setSyncKey( Integer SyncKey )
   {
      this.SyncKey = SyncKey;
   }

   /**
    * @return the DD_TargetKey
    */
   public String getDD_TargetKey( )
   {
      return DD_TargetKey;
   }

   /**
    * @param DD_TargetKey to set 
    */
   public void setDD_TargetKey( String DD_TargetKey )
   {
      this.DD_TargetKey = DD_TargetKey;
   }

   /**
    * @return the DD_SourceKey
    */
   public String getDD_SourceKey( )
   {
      return DD_SourceKey;
   }

   /**
    * @param DD_SourceKey to set 
    */
   public void setDD_SourceKey( String DD_SourceKey )
   {
      this.DD_SourceKey = DD_SourceKey;
   }

   /**
    * @return the OptionFlags
    */
   public Integer getOptionFlags( )
   {
      return OptionFlags;
   }

   /**
    * @param OptionFlags to set 
    */
   public void setOptionFlags( Integer OptionFlags )
   {
      this.OptionFlags = OptionFlags;
   }

   /**
    * @return the DD_Type
    */
   public String getDD_Type( )
   {
      return DD_Type;
   }

   /**
    * @param DD_Type to set 
    */
   public void setDD_Type( String DD_Type )
   {
      this.DD_Type = DD_Type;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the ReportGroupType
    */
   public String getReportGroupType( )
   {
      return ReportGroupType;
   }

   /**
    * @param ReportGroupType to set 
    */
   public void setReportGroupType( String ReportGroupType )
   {
      this.ReportGroupType = ReportGroupType;
   }

   /**
    * @return the ForceHeaderPerEntity
    */
   public String getForceHeaderPerEntity( )
   {
      return ForceHeaderPerEntity;
   }

   /**
    * @param ForceHeaderPerEntity to set 
    */
   public void setForceHeaderPerEntity( String ForceHeaderPerEntity )
   {
      this.ForceHeaderPerEntity = ForceHeaderPerEntity;
   }

   /**
    * @return the ExtendedStyle
    */
   public Integer getExtendedStyle( )
   {
      return ExtendedStyle;
   }

   /**
    * @param ExtendedStyle to set 
    */
   public void setExtendedStyle( Integer ExtendedStyle )
   {
      this.ExtendedStyle = ExtendedStyle;
   }

   /**
    * @return the GUID
    */
   public String getGUID( )
   {
      return GUID;
   }

   /**
    * @param GUID to set 
    */
   public void setGUID( String GUID )
   {
      this.GUID = GUID;
   }

   /**
    * @return the Properties
    */
   public Blob getProperties( )
   {
      return Properties;
   }

   /**
    * @param Properties to set 
    */
   public void setProperties( Blob Properties )
   {
      this.Properties = Properties;
   }

   /**
    * @return the WebreCAPTCHAPublicKey
    */
   public String getWebreCAPTCHAPublicKey( )
   {
      return WebreCAPTCHAPublicKey;
   }

   /**
    * @param WebreCAPTCHAPublicKey to set 
    */
   public void setWebreCAPTCHAPublicKey( String WebreCAPTCHAPublicKey )
   {
      this.WebreCAPTCHAPublicKey = WebreCAPTCHAPublicKey;
   }

   /**
    * @return the WebreCAPTCHAPrivateKey
    */
   public String getWebreCAPTCHAPrivateKey( )
   {
      return WebreCAPTCHAPrivateKey;
   }

   /**
    * @param WebreCAPTCHAPrivateKey to set 
    */
   public void setWebreCAPTCHAPrivateKey( String WebreCAPTCHAPrivateKey )
   {
      this.WebreCAPTCHAPrivateKey = WebreCAPTCHAPrivateKey;
   }

   /**
    * @return the Placeholder
    */
   public String getPlaceholder( )
   {
      return Placeholder;
   }

   /**
    * @param Placeholder to set 
    */
   public void setPlaceholder( String Placeholder )
   {
      this.Placeholder = Placeholder;
   }

   /**
    * @return the LKey
    */
   public Blob getLKey( )
   {
      return LKey;
   }

   /**
    * @param LKey to set 
    */
   public void setLKey( Blob LKey )
   {
      this.LKey = LKey;
   }

   /**
    * @return the VisibleBorder
    */
   public String getVisibleBorder( )
   {
      return VisibleBorder;
   }

   /**
    * @param VisibleBorder to set 
    */
   public void setVisibleBorder( String VisibleBorder )
   {
      this.VisibleBorder = VisibleBorder;
   }

   /**
    * @return the CenterJustify
    */
   public String getCenterJustify( )
   {
      return CenterJustify;
   }

   /**
    * @param CenterJustify to set 
    */
   public void setCenterJustify( String CenterJustify )
   {
      this.CenterJustify = CenterJustify;
   }

   /**
    * @return the RightJustify
    */
   public String getRightJustify( )
   {
      return RightJustify;
   }

   /**
    * @param RightJustify to set 
    */
   public void setRightJustify( String RightJustify )
   {
      this.RightJustify = RightJustify;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the CSS_Id
    */
   public String getCSS_Id( )
   {
      return CSS_Id;
   }

   /**
    * @param CSS_Id to set 
    */
   public void setCSS_Id( String CSS_Id )
   {
      this.CSS_Id = CSS_Id;
   }

   /**
    * @return the CSS_Font
    */
   public String getCSS_Font( )
   {
      return CSS_Font;
   }

   /**
    * @param CSS_Font to set 
    */
   public void setCSS_Font( String CSS_Font )
   {
      this.CSS_Font = CSS_Font;
   }

   /**
    * @return the CSS_Position
    */
   public String getCSS_Position( )
   {
      return CSS_Position;
   }

   /**
    * @param CSS_Position to set 
    */
   public void setCSS_Position( String CSS_Position )
   {
      this.CSS_Position = CSS_Position;
   }

   /**
    * @return the CSS_Size
    */
   public String getCSS_Size( )
   {
      return CSS_Size;
   }

   /**
    * @param CSS_Size to set 
    */
   public void setCSS_Size( String CSS_Size )
   {
      this.CSS_Size = CSS_Size;
   }

   /**
    * @return the JavaScript
    */
   public String getJavaScript( )
   {
      return JavaScript;
   }

   /**
    * @param JavaScript to set 
    */
   public void setJavaScript( String JavaScript )
   {
      this.JavaScript = JavaScript;
   }

   /**
    * @return the RadioOrCheckboxValue
    */
   public String getRadioOrCheckboxValue( )
   {
      return RadioOrCheckboxValue;
   }

   /**
    * @param RadioOrCheckboxValue to set 
    */
   public void setRadioOrCheckboxValue( String RadioOrCheckboxValue )
   {
      this.RadioOrCheckboxValue = RadioOrCheckboxValue;
   }

   /**
    * @return the WebFileName
    */
   public String getWebFileName( )
   {
      return WebFileName;
   }

   /**
    * @param WebFileName to set 
    */
   public void setWebFileName( String WebFileName )
   {
      this.WebFileName = WebFileName;
   }

   /**
    * @return the WebCtrlType
    */
   public String getWebCtrlType( )
   {
      return WebCtrlType;
   }

   /**
    * @param WebCtrlType to set 
    */
   public void setWebCtrlType( String WebCtrlType )
   {
      this.WebCtrlType = WebCtrlType;
   }

   /**
    * @return the WebColumnSpan
    */
   public String getWebColumnSpan( )
   {
      return WebColumnSpan;
   }

   /**
    * @param WebColumnSpan to set 
    */
   public void setWebColumnSpan( String WebColumnSpan )
   {
      this.WebColumnSpan = WebColumnSpan;
   }

   /**
    * @return the WebWrap
    */
   public String getWebWrap( )
   {
      return WebWrap;
   }

   /**
    * @param WebWrap to set 
    */
   public void setWebWrap( String WebWrap )
   {
      this.WebWrap = WebWrap;
   }

   /**
    * @return the BorderWidth
    */
   public Integer getBorderWidth( )
   {
      return BorderWidth;
   }

   /**
    * @param BorderWidth to set 
    */
   public void setBorderWidth( Integer BorderWidth )
   {
      this.BorderWidth = BorderWidth;
   }

   /**
    * @return the BorderStyle
    */
   public Integer getBorderStyle( )
   {
      return BorderStyle;
   }

   /**
    * @param BorderStyle to set 
    */
   public void setBorderStyle( Integer BorderStyle )
   {
      this.BorderStyle = BorderStyle;
   }

   /**
    * @return the BorderTop
    */
   public Integer getBorderTop( )
   {
      return BorderTop;
   }

   /**
    * @param BorderTop to set 
    */
   public void setBorderTop( Integer BorderTop )
   {
      this.BorderTop = BorderTop;
   }

   /**
    * @return the BorderBottom
    */
   public Integer getBorderBottom( )
   {
      return BorderBottom;
   }

   /**
    * @param BorderBottom to set 
    */
   public void setBorderBottom( Integer BorderBottom )
   {
      this.BorderBottom = BorderBottom;
   }

   /**
    * @return the BorderLeft
    */
   public Integer getBorderLeft( )
   {
      return BorderLeft;
   }

   /**
    * @param BorderLeft to set 
    */
   public void setBorderLeft( Integer BorderLeft )
   {
      this.BorderLeft = BorderLeft;
   }

   /**
    * @return the BorderRight
    */
   public Integer getBorderRight( )
   {
      return BorderRight;
   }

   /**
    * @param BorderRight to set 
    */
   public void setBorderRight( Integer BorderRight )
   {
      this.BorderRight = BorderRight;
   }

   /**
    * @return the TextAlignHorizontal
    */
   public String getTextAlignHorizontal( )
   {
      return TextAlignHorizontal;
   }

   /**
    * @param TextAlignHorizontal to set 
    */
   public void setTextAlignHorizontal( String TextAlignHorizontal )
   {
      this.TextAlignHorizontal = TextAlignHorizontal;
   }

   /**
    * @return the FontSize
    */
   public Integer getFontSize( )
   {
      return FontSize;
   }

   /**
    * @param FontSize to set 
    */
   public void setFontSize( Integer FontSize )
   {
      this.FontSize = FontSize;
   }

   /**
    * @return the TextBold
    */
   public String getTextBold( )
   {
      return TextBold;
   }

   /**
    * @param TextBold to set 
    */
   public void setTextBold( String TextBold )
   {
      this.TextBold = TextBold;
   }

   /**
    * @return the TextItalic
    */
   public String getTextItalic( )
   {
      return TextItalic;
   }

   /**
    * @param TextItalic to set 
    */
   public void setTextItalic( String TextItalic )
   {
      this.TextItalic = TextItalic;
   }

   /**
    * @return the TextUnderline
    */
   public String getTextUnderline( )
   {
      return TextUnderline;
   }

   /**
    * @param TextUnderline to set 
    */
   public void setTextUnderline( String TextUnderline )
   {
      this.TextUnderline = TextUnderline;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   public int loadActCtrlEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      IdNbr = cursor.getIntegerFromAttribute( "IdNbr" );  if ( IdNbr == null ) IdNbr = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      CtrlBOI = cursor.getBlobFromAttribute( "CtrlBOI" );
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      SyncKey = cursor.getIntegerFromAttribute( "SyncKey" );  if ( SyncKey == null ) SyncKey = 0;
      DD_TargetKey = cursor.getStringFromAttribute( "DD_TargetKey" );  if ( DD_TargetKey == null ) DD_TargetKey = "";
      DD_SourceKey = cursor.getStringFromAttribute( "DD_SourceKey" );  if ( DD_SourceKey == null ) DD_SourceKey = "";
      OptionFlags = cursor.getIntegerFromAttribute( "OptionFlags" );  if ( OptionFlags == null ) OptionFlags = 0;
      DD_Type = cursor.getStringFromAttribute( "DD_Type" );  if ( DD_Type == null ) DD_Type = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      ReportGroupType = cursor.getStringFromAttribute( "ReportGroupType" );  if ( ReportGroupType == null ) ReportGroupType = "";
      ForceHeaderPerEntity = cursor.getStringFromAttribute( "ForceHeaderPerEntity" );  if ( ForceHeaderPerEntity == null ) ForceHeaderPerEntity = "";
      ExtendedStyle = cursor.getIntegerFromAttribute( "ExtendedStyle" );  if ( ExtendedStyle == null ) ExtendedStyle = 0;
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      Properties = cursor.getBlobFromAttribute( "Properties" );
      WebreCAPTCHAPublicKey = cursor.getStringFromAttribute( "WebreCAPTCHAPublicKey" );  if ( WebreCAPTCHAPublicKey == null ) WebreCAPTCHAPublicKey = "";
      WebreCAPTCHAPrivateKey = cursor.getStringFromAttribute( "WebreCAPTCHAPrivateKey" );  if ( WebreCAPTCHAPrivateKey == null ) WebreCAPTCHAPrivateKey = "";
      Placeholder = cursor.getStringFromAttribute( "Placeholder" );  if ( Placeholder == null ) Placeholder = "";
      LKey = cursor.getBlobFromAttribute( "LKey" );
      VisibleBorder = cursor.getStringFromAttribute( "VisibleBorder" );  if ( VisibleBorder == null ) VisibleBorder = "";
      CenterJustify = cursor.getStringFromAttribute( "CenterJustify" );  if ( CenterJustify == null ) CenterJustify = "";
      RightJustify = cursor.getStringFromAttribute( "RightJustify" );  if ( RightJustify == null ) RightJustify = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      CSS_Id = cursor.getStringFromAttribute( "CSS_Id" );  if ( CSS_Id == null ) CSS_Id = "";
      CSS_Font = cursor.getStringFromAttribute( "CSS_Font" );  if ( CSS_Font == null ) CSS_Font = "";
      CSS_Position = cursor.getStringFromAttribute( "CSS_Position" );  if ( CSS_Position == null ) CSS_Position = "";
      CSS_Size = cursor.getStringFromAttribute( "CSS_Size" );  if ( CSS_Size == null ) CSS_Size = "";
      JavaScript = cursor.getStringFromAttribute( "JavaScript" );  if ( JavaScript == null ) JavaScript = "";
      RadioOrCheckboxValue = cursor.getStringFromAttribute( "RadioOrCheckboxValue" );  if ( RadioOrCheckboxValue == null ) RadioOrCheckboxValue = "";
      WebFileName = cursor.getStringFromAttribute( "WebFileName" );  if ( WebFileName == null ) WebFileName = "";
      WebCtrlType = cursor.getStringFromAttribute( "WebCtrlType" );  if ( WebCtrlType == null ) WebCtrlType = "";
      WebColumnSpan = cursor.getStringFromAttribute( "WebColumnSpan" );  if ( WebColumnSpan == null ) WebColumnSpan = "";
      WebWrap = cursor.getStringFromAttribute( "WebWrap" );  if ( WebWrap == null ) WebWrap = "";
      BorderWidth = cursor.getIntegerFromAttribute( "BorderWidth" );  if ( BorderWidth == null ) BorderWidth = 0;
      BorderStyle = cursor.getIntegerFromAttribute( "BorderStyle" );  if ( BorderStyle == null ) BorderStyle = 0;
      BorderTop = cursor.getIntegerFromAttribute( "BorderTop" );  if ( BorderTop == null ) BorderTop = 0;
      BorderBottom = cursor.getIntegerFromAttribute( "BorderBottom" );  if ( BorderBottom == null ) BorderBottom = 0;
      BorderLeft = cursor.getIntegerFromAttribute( "BorderLeft" );  if ( BorderLeft == null ) BorderLeft = 0;
      BorderRight = cursor.getIntegerFromAttribute( "BorderRight" );  if ( BorderRight == null ) BorderRight = 0;
      TextAlignHorizontal = cursor.getStringFromAttribute( "TextAlignHorizontal" );  if ( TextAlignHorizontal == null ) TextAlignHorizontal = "";
      FontSize = cursor.getIntegerFromAttribute( "FontSize" );  if ( FontSize == null ) FontSize = 0;
      TextBold = cursor.getStringFromAttribute( "TextBold" );  if ( TextBold == null ) TextBold = "";
      TextItalic = cursor.getStringFromAttribute( "TextItalic" );  if ( TextItalic == null ) TextItalic = "";
      TextUnderline = cursor.getStringFromAttribute( "TextUnderline" );  if ( TextUnderline == null ) TextUnderline = "";
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActOptImpl implements ActOpt
{
   protected String  Tag;
   protected String  Text;
   protected String  AccelTitle;
   protected String  CheckMarkValueOn;
   protected String  CheckMarkValueOff;
   protected String  Separator;
   protected Integer ZKey;
   protected Integer Underline;
   protected String  LangID;
   protected String  DIL_Text;
   protected Integer SeqNo_Menu;
   protected Integer SeqNo_Option;


   // ctor
   protected ActOptImpl( EntityCursor cursor )
   {
      loadActOptEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the AccelTitle
    */
   public String getAccelTitle( )
   {
      return AccelTitle;
   }

   /**
    * @param AccelTitle to set 
    */
   public void setAccelTitle( String AccelTitle )
   {
      this.AccelTitle = AccelTitle;
   }

   /**
    * @return the CheckMarkValueOn
    */
   public String getCheckMarkValueOn( )
   {
      return CheckMarkValueOn;
   }

   /**
    * @param CheckMarkValueOn to set 
    */
   public void setCheckMarkValueOn( String CheckMarkValueOn )
   {
      this.CheckMarkValueOn = CheckMarkValueOn;
   }

   /**
    * @return the CheckMarkValueOff
    */
   public String getCheckMarkValueOff( )
   {
      return CheckMarkValueOff;
   }

   /**
    * @param CheckMarkValueOff to set 
    */
   public void setCheckMarkValueOff( String CheckMarkValueOff )
   {
      this.CheckMarkValueOff = CheckMarkValueOff;
   }

   /**
    * @return the Separator
    */
   public String getSeparator( )
   {
      return Separator;
   }

   /**
    * @param Separator to set 
    */
   public void setSeparator( String Separator )
   {
      this.Separator = Separator;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the SeqNo_Menu
    */
   public Integer getSeqNo_Menu( )
   {
      return SeqNo_Menu;
   }

   /**
    * @param SeqNo_Menu to set 
    */
   public void setSeqNo_Menu( Integer SeqNo_Menu )
   {
      this.SeqNo_Menu = SeqNo_Menu;
   }

   /**
    * @return the SeqNo_Option
    */
   public Integer getSeqNo_Option( )
   {
      return SeqNo_Option;
   }

   /**
    * @param SeqNo_Option to set 
    */
   public void setSeqNo_Option( Integer SeqNo_Option )
   {
      this.SeqNo_Option = SeqNo_Option;
   }

   public int loadActOptEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      AccelTitle = cursor.getStringFromAttribute( "AccelTitle" );  if ( AccelTitle == null ) AccelTitle = "";
      CheckMarkValueOn = cursor.getStringFromAttribute( "CheckMarkValueOn" );  if ( CheckMarkValueOn == null ) CheckMarkValueOn = "";
      CheckMarkValueOff = cursor.getStringFromAttribute( "CheckMarkValueOff" );  if ( CheckMarkValueOff == null ) CheckMarkValueOff = "";
      Separator = cursor.getStringFromAttribute( "Separator" );  if ( Separator == null ) Separator = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      SeqNo_Menu = cursor.getIntegerFromAttribute( "SeqNo_Menu" );  if ( SeqNo_Menu == null ) SeqNo_Menu = 0;
      SeqNo_Option = cursor.getIntegerFromAttribute( "SeqNo_Option" );  if ( SeqNo_Option == null ) SeqNo_Option = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActOperImpl implements ActOper
{
   protected String  Name;
   protected Integer ZKey;
   protected String  LastSyncDate;
   protected String  Desc;
   protected Integer Class;
   protected String  Type;
   protected String  ReturnDesc;
   protected String  ReturnDataType;
   protected Integer OrdinalValue;
   protected String  GenerationType;
   protected String  DoNotMergeFlag;
   protected String  ThrowsException;
   protected String  ThrowsExceptionCatchCode;


   // ctor
   protected ActOperImpl( EntityCursor cursor )
   {
      loadActOperEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Class
    */
   public Integer getClass( )
   {
      return Class;
   }

   /**
    * @param Class to set 
    */
   public void setClass( Integer Class )
   {
      this.Class = Class;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the ReturnDesc
    */
   public String getReturnDesc( )
   {
      return ReturnDesc;
   }

   /**
    * @param ReturnDesc to set 
    */
   public void setReturnDesc( String ReturnDesc )
   {
      this.ReturnDesc = ReturnDesc;
   }

   /**
    * @return the ReturnDataType
    */
   public String getReturnDataType( )
   {
      return ReturnDataType;
   }

   /**
    * @param ReturnDataType to set 
    */
   public void setReturnDataType( String ReturnDataType )
   {
      this.ReturnDataType = ReturnDataType;
   }

   /**
    * @return the OrdinalValue
    */
   public Integer getOrdinalValue( )
   {
      return OrdinalValue;
   }

   /**
    * @param OrdinalValue to set 
    */
   public void setOrdinalValue( Integer OrdinalValue )
   {
      this.OrdinalValue = OrdinalValue;
   }

   /**
    * @return the GenerationType
    */
   public String getGenerationType( )
   {
      return GenerationType;
   }

   /**
    * @param GenerationType to set 
    */
   public void setGenerationType( String GenerationType )
   {
      this.GenerationType = GenerationType;
   }

   /**
    * @return the DoNotMergeFlag
    */
   public String getDoNotMergeFlag( )
   {
      return DoNotMergeFlag;
   }

   /**
    * @param DoNotMergeFlag to set 
    */
   public void setDoNotMergeFlag( String DoNotMergeFlag )
   {
      this.DoNotMergeFlag = DoNotMergeFlag;
   }

   /**
    * @return the ThrowsException
    */
   public String getThrowsException( )
   {
      return ThrowsException;
   }

   /**
    * @param ThrowsException to set 
    */
   public void setThrowsException( String ThrowsException )
   {
      this.ThrowsException = ThrowsException;
   }

   /**
    * @return the ThrowsExceptionCatchCode
    */
   public String getThrowsExceptionCatchCode( )
   {
      return ThrowsExceptionCatchCode;
   }

   /**
    * @param ThrowsExceptionCatchCode to set 
    */
   public void setThrowsExceptionCatchCode( String ThrowsExceptionCatchCode )
   {
      this.ThrowsExceptionCatchCode = ThrowsExceptionCatchCode;
   }

   public int loadActOperEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Class = cursor.getIntegerFromAttribute( "Class" );  if ( Class == null ) Class = 0;
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      ReturnDesc = cursor.getStringFromAttribute( "ReturnDesc" );  if ( ReturnDesc == null ) ReturnDesc = "";
      ReturnDataType = cursor.getStringFromAttribute( "ReturnDataType" );  if ( ReturnDataType == null ) ReturnDataType = "";
      OrdinalValue = cursor.getIntegerFromAttribute( "OrdinalValue" );  if ( OrdinalValue == null ) OrdinalValue = 0;
      GenerationType = cursor.getStringFromAttribute( "GenerationType" );  if ( GenerationType == null ) GenerationType = "";
      DoNotMergeFlag = cursor.getStringFromAttribute( "DoNotMergeFlag" );  if ( DoNotMergeFlag == null ) DoNotMergeFlag = "";
      ThrowsException = cursor.getStringFromAttribute( "ThrowsException" );  if ( ThrowsException == null ) ThrowsException = "";
      ThrowsExceptionCatchCode = cursor.getStringFromAttribute( "ThrowsExceptionCatchCode" );  if ( ThrowsExceptionCatchCode == null ) ThrowsExceptionCatchCode = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class SourceFileForOperImpl implements SourceFileForOper
{
   protected Integer ZKey;
   protected String  CM_Managed;
   protected String  OwnerType;
   protected String  LanguageType;
   protected String  DomainAndGlobalOpGroupName;
   protected String  Name;
   protected String  Desc;
   protected String  Extension;
   protected String  Subdirectory;


   // ctor
   protected SourceFileForOperImpl( EntityCursor cursor )
   {
      loadSourceFileForOperEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the CM_Managed
    */
   public String getCM_Managed( )
   {
      return CM_Managed;
   }

   /**
    * @param CM_Managed to set 
    */
   public void setCM_Managed( String CM_Managed )
   {
      this.CM_Managed = CM_Managed;
   }

   /**
    * @return the OwnerType
    */
   public String getOwnerType( )
   {
      return OwnerType;
   }

   /**
    * @param OwnerType to set 
    */
   public void setOwnerType( String OwnerType )
   {
      this.OwnerType = OwnerType;
   }

   /**
    * @return the LanguageType
    */
   public String getLanguageType( )
   {
      return LanguageType;
   }

   /**
    * @param LanguageType to set 
    */
   public void setLanguageType( String LanguageType )
   {
      this.LanguageType = LanguageType;
   }

   /**
    * @return the DomainAndGlobalOpGroupName
    */
   public String getDomainAndGlobalOpGroupName( )
   {
      return DomainAndGlobalOpGroupName;
   }

   /**
    * @param DomainAndGlobalOpGroupName to set 
    */
   public void setDomainAndGlobalOpGroupName( String DomainAndGlobalOpGroupName )
   {
      this.DomainAndGlobalOpGroupName = DomainAndGlobalOpGroupName;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Extension
    */
   public String getExtension( )
   {
      return Extension;
   }

   /**
    * @param Extension to set 
    */
   public void setExtension( String Extension )
   {
      this.Extension = Extension;
   }

   /**
    * @return the Subdirectory
    */
   public String getSubdirectory( )
   {
      return Subdirectory;
   }

   /**
    * @param Subdirectory to set 
    */
   public void setSubdirectory( String Subdirectory )
   {
      this.Subdirectory = Subdirectory;
   }

   public int loadSourceFileForOperEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      CM_Managed = cursor.getStringFromAttribute( "CM_Managed" );  if ( CM_Managed == null ) CM_Managed = "";
      OwnerType = cursor.getStringFromAttribute( "OwnerType" );  if ( OwnerType == null ) OwnerType = "";
      LanguageType = cursor.getStringFromAttribute( "LanguageType" );  if ( LanguageType == null ) LanguageType = "";
      DomainAndGlobalOpGroupName = cursor.getStringFromAttribute( "DomainAndGlobalOpGroupName" );  if ( DomainAndGlobalOpGroupName == null ) DomainAndGlobalOpGroupName = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Extension = cursor.getStringFromAttribute( "Extension" );  if ( Extension == null ) Extension = "";
      Subdirectory = cursor.getStringFromAttribute( "Subdirectory" );  if ( Subdirectory == null ) Subdirectory = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ActHotImpl implements ActHot
{
   protected String  Tag;
   protected Integer ZKey;
   protected Blob    KeyCombo;
   protected String  Title;
   protected Integer Mode;
   protected Integer VKey;


   // ctor
   protected ActHotImpl( EntityCursor cursor )
   {
      loadActHotEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the KeyCombo
    */
   public Blob getKeyCombo( )
   {
      return KeyCombo;
   }

   /**
    * @param KeyCombo to set 
    */
   public void setKeyCombo( Blob KeyCombo )
   {
      this.KeyCombo = KeyCombo;
   }

   /**
    * @return the Title
    */
   public String getTitle( )
   {
      return Title;
   }

   /**
    * @param Title to set 
    */
   public void setTitle( String Title )
   {
      this.Title = Title;
   }

   /**
    * @return the Mode
    */
   public Integer getMode( )
   {
      return Mode;
   }

   /**
    * @param Mode to set 
    */
   public void setMode( Integer Mode )
   {
      this.Mode = Mode;
   }

   /**
    * @return the VKey
    */
   public Integer getVKey( )
   {
      return VKey;
   }

   /**
    * @param VKey to set 
    */
   public void setVKey( Integer VKey )
   {
      this.VKey = VKey;
   }

   public int loadActHotEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      KeyCombo = cursor.getBlobFromAttribute( "KeyCombo" );
      Title = cursor.getStringFromAttribute( "Title" );  if ( Title == null ) Title = "";
      Mode = cursor.getIntegerFromAttribute( "Mode" );  if ( Mode == null ) Mode = 0;
      VKey = cursor.getIntegerFromAttribute( "VKey" );  if ( VKey == null ) VKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class EventListImpl implements EventList
{
   protected String  Name;
   protected Integer ZKey;
   protected String  EventOptionType;


   // ctor
   protected EventListImpl( EntityCursor cursor )
   {
      loadEventListEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the EventOptionType
    */
   public String getEventOptionType( )
   {
      return EventOptionType;
   }

   /**
    * @param EventOptionType to set 
    */
   public void setEventOptionType( String EventOptionType )
   {
      this.EventOptionType = EventOptionType;
   }

   public int loadEventListEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      EventOptionType = cursor.getStringFromAttribute( "EventOptionType" );  if ( EventOptionType == null ) EventOptionType = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class MenuImpl implements Menu
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  CSS_Class;
   protected String  WebHTML5Attribute;


   // ctor
   protected MenuImpl( EntityCursor cursor )
   {
      loadMenuEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WebHTML5Attribute
    */
   public String getWebHTML5Attribute( )
   {
      return WebHTML5Attribute;
   }

   /**
    * @param WebHTML5Attribute to set 
    */
   public void setWebHTML5Attribute( String WebHTML5Attribute )
   {
      this.WebHTML5Attribute = WebHTML5Attribute;
   }

   public int loadMenuEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WebHTML5Attribute = cursor.getStringFromAttribute( "WebHTML5Attribute" );  if ( WebHTML5Attribute == null ) WebHTML5Attribute = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptionImpl implements Option
{
   protected String  Tag;
   protected String  Text;
   protected String  AccelTitle;
   protected String  CheckMarkValueOn;
   protected String  CheckMarkValueOff;
   protected String  Separator;
   protected Integer ZKey;
   protected Integer Underline;
   protected String  DIL_Text;
   protected String  DIL_TextMsg;
   protected String  DIL_Inherited;
   protected Integer SeqNo_Menu;
   protected Integer SeqNo_Option;
   protected String  NLS_Text;
   protected String  CSS_Class;
   protected String  WebHTML5Attribute;
   protected String  LangID;


   // ctor
   protected OptionImpl( EntityCursor cursor )
   {
      loadOptionEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the AccelTitle
    */
   public String getAccelTitle( )
   {
      return AccelTitle;
   }

   /**
    * @param AccelTitle to set 
    */
   public void setAccelTitle( String AccelTitle )
   {
      this.AccelTitle = AccelTitle;
   }

   /**
    * @return the CheckMarkValueOn
    */
   public String getCheckMarkValueOn( )
   {
      return CheckMarkValueOn;
   }

   /**
    * @param CheckMarkValueOn to set 
    */
   public void setCheckMarkValueOn( String CheckMarkValueOn )
   {
      this.CheckMarkValueOn = CheckMarkValueOn;
   }

   /**
    * @return the CheckMarkValueOff
    */
   public String getCheckMarkValueOff( )
   {
      return CheckMarkValueOff;
   }

   /**
    * @param CheckMarkValueOff to set 
    */
   public void setCheckMarkValueOff( String CheckMarkValueOff )
   {
      this.CheckMarkValueOff = CheckMarkValueOff;
   }

   /**
    * @return the Separator
    */
   public String getSeparator( )
   {
      return Separator;
   }

   /**
    * @param Separator to set 
    */
   public void setSeparator( String Separator )
   {
      this.Separator = Separator;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the DIL_TextMsg
    */
   public String getDIL_TextMsg( )
   {
      return DIL_TextMsg;
   }

   /**
    * @param DIL_TextMsg to set 
    */
   public void setDIL_TextMsg( String DIL_TextMsg )
   {
      this.DIL_TextMsg = DIL_TextMsg;
   }

   /**
    * @return the DIL_Inherited
    */
   public String getDIL_Inherited( )
   {
      return DIL_Inherited;
   }

   /**
    * @param DIL_Inherited to set 
    */
   public void setDIL_Inherited( String DIL_Inherited )
   {
      this.DIL_Inherited = DIL_Inherited;
   }

   /**
    * @return the SeqNo_Menu
    */
   public Integer getSeqNo_Menu( )
   {
      return SeqNo_Menu;
   }

   /**
    * @param SeqNo_Menu to set 
    */
   public void setSeqNo_Menu( Integer SeqNo_Menu )
   {
      this.SeqNo_Menu = SeqNo_Menu;
   }

   /**
    * @return the SeqNo_Option
    */
   public Integer getSeqNo_Option( )
   {
      return SeqNo_Option;
   }

   /**
    * @param SeqNo_Option to set 
    */
   public void setSeqNo_Option( Integer SeqNo_Option )
   {
      this.SeqNo_Option = SeqNo_Option;
   }

   /**
    * @return the NLS_Text
    */
   public String getNLS_Text( )
   {
      return NLS_Text;
   }

   /**
    * @param NLS_Text to set 
    */
   public void setNLS_Text( String NLS_Text )
   {
      this.NLS_Text = NLS_Text;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WebHTML5Attribute
    */
   public String getWebHTML5Attribute( )
   {
      return WebHTML5Attribute;
   }

   /**
    * @param WebHTML5Attribute to set 
    */
   public void setWebHTML5Attribute( String WebHTML5Attribute )
   {
      this.WebHTML5Attribute = WebHTML5Attribute;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   public int loadOptionEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      AccelTitle = cursor.getStringFromAttribute( "AccelTitle" );  if ( AccelTitle == null ) AccelTitle = "";
      CheckMarkValueOn = cursor.getStringFromAttribute( "CheckMarkValueOn" );  if ( CheckMarkValueOn == null ) CheckMarkValueOn = "";
      CheckMarkValueOff = cursor.getStringFromAttribute( "CheckMarkValueOff" );  if ( CheckMarkValueOff == null ) CheckMarkValueOff = "";
      Separator = cursor.getStringFromAttribute( "Separator" );  if ( Separator == null ) Separator = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      DIL_TextMsg = cursor.getStringFromAttribute( "DIL_TextMsg" );  if ( DIL_TextMsg == null ) DIL_TextMsg = "";
      DIL_Inherited = cursor.getStringFromAttribute( "DIL_Inherited" );  if ( DIL_Inherited == null ) DIL_Inherited = "";
      SeqNo_Menu = cursor.getIntegerFromAttribute( "SeqNo_Menu" );  if ( SeqNo_Menu == null ) SeqNo_Menu = 0;
      SeqNo_Option = cursor.getIntegerFromAttribute( "SeqNo_Option" );  if ( SeqNo_Option == null ) SeqNo_Option = 0;
      NLS_Text = cursor.getStringFromAttribute( "NLS_Text" );  if ( NLS_Text == null ) NLS_Text = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WebHTML5Attribute = cursor.getStringFromAttribute( "WebHTML5Attribute" );  if ( WebHTML5Attribute == null ) WebHTML5Attribute = "";
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptOptImpl implements OptOpt
{
   protected String  Tag;
   protected String  Text;
   protected String  AccelTitle;
   protected String  CheckMarkValueOn;
   protected String  CheckMarkValueOff;
   protected String  Separator;
   protected Integer ZKey;
   protected Integer Underline;
   protected String  DIL_Text;
   protected String  DIL_TextMsg;
   protected String  DIL_Inherited;
   protected Integer SeqNo_Menu;
   protected Integer SeqNo_Option;
   protected String  NLS_Text;
   protected String  CSS_Class;
   protected String  WebHTML5Attribute;
   protected String  LangID;


   // ctor
   protected OptOptImpl( EntityCursor cursor )
   {
      loadOptOptEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the AccelTitle
    */
   public String getAccelTitle( )
   {
      return AccelTitle;
   }

   /**
    * @param AccelTitle to set 
    */
   public void setAccelTitle( String AccelTitle )
   {
      this.AccelTitle = AccelTitle;
   }

   /**
    * @return the CheckMarkValueOn
    */
   public String getCheckMarkValueOn( )
   {
      return CheckMarkValueOn;
   }

   /**
    * @param CheckMarkValueOn to set 
    */
   public void setCheckMarkValueOn( String CheckMarkValueOn )
   {
      this.CheckMarkValueOn = CheckMarkValueOn;
   }

   /**
    * @return the CheckMarkValueOff
    */
   public String getCheckMarkValueOff( )
   {
      return CheckMarkValueOff;
   }

   /**
    * @param CheckMarkValueOff to set 
    */
   public void setCheckMarkValueOff( String CheckMarkValueOff )
   {
      this.CheckMarkValueOff = CheckMarkValueOff;
   }

   /**
    * @return the Separator
    */
   public String getSeparator( )
   {
      return Separator;
   }

   /**
    * @param Separator to set 
    */
   public void setSeparator( String Separator )
   {
      this.Separator = Separator;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the DIL_TextMsg
    */
   public String getDIL_TextMsg( )
   {
      return DIL_TextMsg;
   }

   /**
    * @param DIL_TextMsg to set 
    */
   public void setDIL_TextMsg( String DIL_TextMsg )
   {
      this.DIL_TextMsg = DIL_TextMsg;
   }

   /**
    * @return the DIL_Inherited
    */
   public String getDIL_Inherited( )
   {
      return DIL_Inherited;
   }

   /**
    * @param DIL_Inherited to set 
    */
   public void setDIL_Inherited( String DIL_Inherited )
   {
      this.DIL_Inherited = DIL_Inherited;
   }

   /**
    * @return the SeqNo_Menu
    */
   public Integer getSeqNo_Menu( )
   {
      return SeqNo_Menu;
   }

   /**
    * @param SeqNo_Menu to set 
    */
   public void setSeqNo_Menu( Integer SeqNo_Menu )
   {
      this.SeqNo_Menu = SeqNo_Menu;
   }

   /**
    * @return the SeqNo_Option
    */
   public Integer getSeqNo_Option( )
   {
      return SeqNo_Option;
   }

   /**
    * @param SeqNo_Option to set 
    */
   public void setSeqNo_Option( Integer SeqNo_Option )
   {
      this.SeqNo_Option = SeqNo_Option;
   }

   /**
    * @return the NLS_Text
    */
   public String getNLS_Text( )
   {
      return NLS_Text;
   }

   /**
    * @param NLS_Text to set 
    */
   public void setNLS_Text( String NLS_Text )
   {
      this.NLS_Text = NLS_Text;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WebHTML5Attribute
    */
   public String getWebHTML5Attribute( )
   {
      return WebHTML5Attribute;
   }

   /**
    * @param WebHTML5Attribute to set 
    */
   public void setWebHTML5Attribute( String WebHTML5Attribute )
   {
      this.WebHTML5Attribute = WebHTML5Attribute;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   public int loadOptOptEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      AccelTitle = cursor.getStringFromAttribute( "AccelTitle" );  if ( AccelTitle == null ) AccelTitle = "";
      CheckMarkValueOn = cursor.getStringFromAttribute( "CheckMarkValueOn" );  if ( CheckMarkValueOn == null ) CheckMarkValueOn = "";
      CheckMarkValueOff = cursor.getStringFromAttribute( "CheckMarkValueOff" );  if ( CheckMarkValueOff == null ) CheckMarkValueOff = "";
      Separator = cursor.getStringFromAttribute( "Separator" );  if ( Separator == null ) Separator = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      DIL_TextMsg = cursor.getStringFromAttribute( "DIL_TextMsg" );  if ( DIL_TextMsg == null ) DIL_TextMsg = "";
      DIL_Inherited = cursor.getStringFromAttribute( "DIL_Inherited" );  if ( DIL_Inherited == null ) DIL_Inherited = "";
      SeqNo_Menu = cursor.getIntegerFromAttribute( "SeqNo_Menu" );  if ( SeqNo_Menu == null ) SeqNo_Menu = 0;
      SeqNo_Option = cursor.getIntegerFromAttribute( "SeqNo_Option" );  if ( SeqNo_Option == null ) SeqNo_Option = 0;
      NLS_Text = cursor.getStringFromAttribute( "NLS_Text" );  if ( NLS_Text == null ) NLS_Text = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WebHTML5Attribute = cursor.getStringFromAttribute( "WebHTML5Attribute" );  if ( WebHTML5Attribute == null ) WebHTML5Attribute = "";
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptActImpl implements OptAct
{
   protected String  Tag;
   protected String  ActionTypeAssociatedText;
   protected String  NoMap;
   protected Integer Type;
   protected String  TypeData;
   protected Integer ZKey;
   protected String  DialogName;
   protected String  WindowName;
   protected String  DLL;
   protected String  WebJavaScript;
   protected Integer OperCtrl;
   protected Integer SB_SubAction;
   protected Integer SB_NextPrev;
   protected Integer SB_DeleteNull;
   protected Integer SB_ActionDisabling;
   protected String  PopupMenuName;
   protected String  WebJavaScriptLocation;


   // ctor
   protected OptActImpl( EntityCursor cursor )
   {
      loadOptActEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ActionTypeAssociatedText
    */
   public String getActionTypeAssociatedText( )
   {
      return ActionTypeAssociatedText;
   }

   /**
    * @param ActionTypeAssociatedText to set 
    */
   public void setActionTypeAssociatedText( String ActionTypeAssociatedText )
   {
      this.ActionTypeAssociatedText = ActionTypeAssociatedText;
   }

   /**
    * @return the NoMap
    */
   public String getNoMap( )
   {
      return NoMap;
   }

   /**
    * @param NoMap to set 
    */
   public void setNoMap( String NoMap )
   {
      this.NoMap = NoMap;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the TypeData
    */
   public String getTypeData( )
   {
      return TypeData;
   }

   /**
    * @param TypeData to set 
    */
   public void setTypeData( String TypeData )
   {
      this.TypeData = TypeData;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DialogName
    */
   public String getDialogName( )
   {
      return DialogName;
   }

   /**
    * @param DialogName to set 
    */
   public void setDialogName( String DialogName )
   {
      this.DialogName = DialogName;
   }

   /**
    * @return the WindowName
    */
   public String getWindowName( )
   {
      return WindowName;
   }

   /**
    * @param WindowName to set 
    */
   public void setWindowName( String WindowName )
   {
      this.WindowName = WindowName;
   }

   /**
    * @return the DLL
    */
   public String getDLL( )
   {
      return DLL;
   }

   /**
    * @param DLL to set 
    */
   public void setDLL( String DLL )
   {
      this.DLL = DLL;
   }

   /**
    * @return the WebJavaScript
    */
   public String getWebJavaScript( )
   {
      return WebJavaScript;
   }

   /**
    * @param WebJavaScript to set 
    */
   public void setWebJavaScript( String WebJavaScript )
   {
      this.WebJavaScript = WebJavaScript;
   }

   /**
    * @return the OperCtrl
    */
   public Integer getOperCtrl( )
   {
      return OperCtrl;
   }

   /**
    * @param OperCtrl to set 
    */
   public void setOperCtrl( Integer OperCtrl )
   {
      this.OperCtrl = OperCtrl;
   }

   /**
    * @return the SB_SubAction
    */
   public Integer getSB_SubAction( )
   {
      return SB_SubAction;
   }

   /**
    * @param SB_SubAction to set 
    */
   public void setSB_SubAction( Integer SB_SubAction )
   {
      this.SB_SubAction = SB_SubAction;
   }

   /**
    * @return the SB_NextPrev
    */
   public Integer getSB_NextPrev( )
   {
      return SB_NextPrev;
   }

   /**
    * @param SB_NextPrev to set 
    */
   public void setSB_NextPrev( Integer SB_NextPrev )
   {
      this.SB_NextPrev = SB_NextPrev;
   }

   /**
    * @return the SB_DeleteNull
    */
   public Integer getSB_DeleteNull( )
   {
      return SB_DeleteNull;
   }

   /**
    * @param SB_DeleteNull to set 
    */
   public void setSB_DeleteNull( Integer SB_DeleteNull )
   {
      this.SB_DeleteNull = SB_DeleteNull;
   }

   /**
    * @return the SB_ActionDisabling
    */
   public Integer getSB_ActionDisabling( )
   {
      return SB_ActionDisabling;
   }

   /**
    * @param SB_ActionDisabling to set 
    */
   public void setSB_ActionDisabling( Integer SB_ActionDisabling )
   {
      this.SB_ActionDisabling = SB_ActionDisabling;
   }

   /**
    * @return the PopupMenuName
    */
   public String getPopupMenuName( )
   {
      return PopupMenuName;
   }

   /**
    * @param PopupMenuName to set 
    */
   public void setPopupMenuName( String PopupMenuName )
   {
      this.PopupMenuName = PopupMenuName;
   }

   /**
    * @return the WebJavaScriptLocation
    */
   public String getWebJavaScriptLocation( )
   {
      return WebJavaScriptLocation;
   }

   /**
    * @param WebJavaScriptLocation to set 
    */
   public void setWebJavaScriptLocation( String WebJavaScriptLocation )
   {
      this.WebJavaScriptLocation = WebJavaScriptLocation;
   }

   public int loadOptActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ActionTypeAssociatedText = cursor.getStringFromAttribute( "ActionTypeAssociatedText" );  if ( ActionTypeAssociatedText == null ) ActionTypeAssociatedText = "";
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      TypeData = cursor.getStringFromAttribute( "TypeData" );  if ( TypeData == null ) TypeData = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DialogName = cursor.getStringFromAttribute( "DialogName" );  if ( DialogName == null ) DialogName = "";
      WindowName = cursor.getStringFromAttribute( "WindowName" );  if ( WindowName == null ) WindowName = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      WebJavaScript = cursor.getStringFromAttribute( "WebJavaScript" );  if ( WebJavaScript == null ) WebJavaScript = "";
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      SB_SubAction = cursor.getIntegerFromAttribute( "SB_SubAction" );  if ( SB_SubAction == null ) SB_SubAction = 0;
      SB_NextPrev = cursor.getIntegerFromAttribute( "SB_NextPrev" );  if ( SB_NextPrev == null ) SB_NextPrev = 0;
      SB_DeleteNull = cursor.getIntegerFromAttribute( "SB_DeleteNull" );  if ( SB_DeleteNull == null ) SB_DeleteNull = 0;
      SB_ActionDisabling = cursor.getIntegerFromAttribute( "SB_ActionDisabling" );  if ( SB_ActionDisabling == null ) SB_ActionDisabling = 0;
      PopupMenuName = cursor.getStringFromAttribute( "PopupMenuName" );  if ( PopupMenuName == null ) PopupMenuName = "";
      WebJavaScriptLocation = cursor.getStringFromAttribute( "WebJavaScriptLocation" );  if ( WebJavaScriptLocation == null ) WebJavaScriptLocation = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptMapImpl implements OptMap
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  Type;
   protected Integer SeqNo_DlgCtrl;
   protected Integer SeqNo_DlgAct;


   // ctor
   protected OptMapImpl( EntityCursor cursor )
   {
      loadOptMapEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the SeqNo_DlgCtrl
    */
   public Integer getSeqNo_DlgCtrl( )
   {
      return SeqNo_DlgCtrl;
   }

   /**
    * @param SeqNo_DlgCtrl to set 
    */
   public void setSeqNo_DlgCtrl( Integer SeqNo_DlgCtrl )
   {
      this.SeqNo_DlgCtrl = SeqNo_DlgCtrl;
   }

   /**
    * @return the SeqNo_DlgAct
    */
   public Integer getSeqNo_DlgAct( )
   {
      return SeqNo_DlgAct;
   }

   /**
    * @param SeqNo_DlgAct to set 
    */
   public void setSeqNo_DlgAct( Integer SeqNo_DlgAct )
   {
      this.SeqNo_DlgAct = SeqNo_DlgAct;
   }

   public int loadOptMapEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      SeqNo_DlgCtrl = cursor.getIntegerFromAttribute( "SeqNo_DlgCtrl" );  if ( SeqNo_DlgCtrl == null ) SeqNo_DlgCtrl = 0;
      SeqNo_DlgAct = cursor.getIntegerFromAttribute( "SeqNo_DlgAct" );  if ( SeqNo_DlgAct == null ) SeqNo_DlgAct = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptMapLOD_AttributeImpl implements OptMapLOD_Attribute
{
   protected Integer ZKey;
   protected String  Work;
   protected String  Update;
   protected String  Init;
   protected String  Hidden;
   protected Integer SeqPriority;
   protected String  SeqOrder;
   protected String  DIL_Text;
   protected Integer SeqNo_LOD_Entity;
   protected Integer SeqNo_UIS_Entity_M;
   protected Integer SeqNo_UIS_Entity_L;
   protected String  DB_DerivedValue;
   protected String  XML_Simple;
   protected String  HashkeyType;
   protected String  HashkeyParentEntityName;


   // ctor
   protected OptMapLOD_AttributeImpl( EntityCursor cursor )
   {
      loadOptMapLOD_AttributeEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the Init
    */
   public String getInit( )
   {
      return Init;
   }

   /**
    * @param Init to set 
    */
   public void setInit( String Init )
   {
      this.Init = Init;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the SeqPriority
    */
   public Integer getSeqPriority( )
   {
      return SeqPriority;
   }

   /**
    * @param SeqPriority to set 
    */
   public void setSeqPriority( Integer SeqPriority )
   {
      this.SeqPriority = SeqPriority;
   }

   /**
    * @return the SeqOrder
    */
   public String getSeqOrder( )
   {
      return SeqOrder;
   }

   /**
    * @param SeqOrder to set 
    */
   public void setSeqOrder( String SeqOrder )
   {
      this.SeqOrder = SeqOrder;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the SeqNo_LOD_Entity
    */
   public Integer getSeqNo_LOD_Entity( )
   {
      return SeqNo_LOD_Entity;
   }

   /**
    * @param SeqNo_LOD_Entity to set 
    */
   public void setSeqNo_LOD_Entity( Integer SeqNo_LOD_Entity )
   {
      this.SeqNo_LOD_Entity = SeqNo_LOD_Entity;
   }

   /**
    * @return the SeqNo_UIS_Entity_M
    */
   public Integer getSeqNo_UIS_Entity_M( )
   {
      return SeqNo_UIS_Entity_M;
   }

   /**
    * @param SeqNo_UIS_Entity_M to set 
    */
   public void setSeqNo_UIS_Entity_M( Integer SeqNo_UIS_Entity_M )
   {
      this.SeqNo_UIS_Entity_M = SeqNo_UIS_Entity_M;
   }

   /**
    * @return the SeqNo_UIS_Entity_L
    */
   public Integer getSeqNo_UIS_Entity_L( )
   {
      return SeqNo_UIS_Entity_L;
   }

   /**
    * @param SeqNo_UIS_Entity_L to set 
    */
   public void setSeqNo_UIS_Entity_L( Integer SeqNo_UIS_Entity_L )
   {
      this.SeqNo_UIS_Entity_L = SeqNo_UIS_Entity_L;
   }

   /**
    * @return the DB_DerivedValue
    */
   public String getDB_DerivedValue( )
   {
      return DB_DerivedValue;
   }

   /**
    * @param DB_DerivedValue to set 
    */
   public void setDB_DerivedValue( String DB_DerivedValue )
   {
      this.DB_DerivedValue = DB_DerivedValue;
   }

   /**
    * @return the XML_Simple
    */
   public String getXML_Simple( )
   {
      return XML_Simple;
   }

   /**
    * @param XML_Simple to set 
    */
   public void setXML_Simple( String XML_Simple )
   {
      this.XML_Simple = XML_Simple;
   }

   /**
    * @return the HashkeyType
    */
   public String getHashkeyType( )
   {
      return HashkeyType;
   }

   /**
    * @param HashkeyType to set 
    */
   public void setHashkeyType( String HashkeyType )
   {
      this.HashkeyType = HashkeyType;
   }

   /**
    * @return the HashkeyParentEntityName
    */
   public String getHashkeyParentEntityName( )
   {
      return HashkeyParentEntityName;
   }

   /**
    * @param HashkeyParentEntityName to set 
    */
   public void setHashkeyParentEntityName( String HashkeyParentEntityName )
   {
      this.HashkeyParentEntityName = HashkeyParentEntityName;
   }

   public int loadOptMapLOD_AttributeEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      Init = cursor.getStringFromAttribute( "Init" );  if ( Init == null ) Init = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      SeqPriority = cursor.getIntegerFromAttribute( "SeqPriority" );  if ( SeqPriority == null ) SeqPriority = 0;
      SeqOrder = cursor.getStringFromAttribute( "SeqOrder" );  if ( SeqOrder == null ) SeqOrder = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      SeqNo_LOD_Entity = cursor.getIntegerFromAttribute( "SeqNo_LOD_Entity" );  if ( SeqNo_LOD_Entity == null ) SeqNo_LOD_Entity = 0;
      SeqNo_UIS_Entity_M = cursor.getIntegerFromAttribute( "SeqNo_UIS_Entity_M" );  if ( SeqNo_UIS_Entity_M == null ) SeqNo_UIS_Entity_M = 0;
      SeqNo_UIS_Entity_L = cursor.getIntegerFromAttribute( "SeqNo_UIS_Entity_L" );  if ( SeqNo_UIS_Entity_L == null ) SeqNo_UIS_Entity_L = 0;
      DB_DerivedValue = cursor.getStringFromAttribute( "DB_DerivedValue" );  if ( DB_DerivedValue == null ) DB_DerivedValue = "";
      XML_Simple = cursor.getStringFromAttribute( "XML_Simple" );  if ( XML_Simple == null ) XML_Simple = "";
      HashkeyType = cursor.getStringFromAttribute( "HashkeyType" );  if ( HashkeyType == null ) HashkeyType = "";
      HashkeyParentEntityName = cursor.getStringFromAttribute( "HashkeyParentEntityName" );  if ( HashkeyParentEntityName == null ) HashkeyParentEntityName = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptMapRelatedEntityImpl implements OptMapRelatedEntity
{
   protected String  Name;
   protected String  IndentName;
   protected Integer IndentLvl;
   protected Integer ZKey;
   protected String  Create;
   protected String  Delete;
   protected String  Update;
   protected String  Include;
   protected String  InclSrc;
   protected String  Exclude;
   protected String  CreateConstraint;
   protected String  DeleteConstraint;
   protected String  IncludeConstraint;
   protected String  ExcludeConstraint;
   protected String  AcceptConstraint;
   protected String  CancelConstraint;
   protected Integer SeqNo;
   protected Integer DataLocking;
   protected Integer MultipleChildLimit;
   protected String  Hidden;
   protected String  Recursive;
   protected String  AutoCreate;
   protected String  Derived;
   protected String  SeqType;
   protected String  Work;
   protected String  ParentDeleteBehave;
   protected String  DupEntityInstance;
   protected String  DupRelationshipInstance;
   protected String  RelLinkIndicator;
   protected String  Desc;
   protected String  Abstract;
   protected String  XML_Name;
   protected String  LazyLoadFlag;
   protected String  ReportDisplayFlag;


   // ctor
   protected OptMapRelatedEntityImpl( EntityCursor cursor )
   {
      loadOptMapRelatedEntityEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the IndentName
    */
   public String getIndentName( )
   {
      return IndentName;
   }

   /**
    * @param IndentName to set 
    */
   public void setIndentName( String IndentName )
   {
      this.IndentName = IndentName;
   }

   /**
    * @return the IndentLvl
    */
   public Integer getIndentLvl( )
   {
      return IndentLvl;
   }

   /**
    * @param IndentLvl to set 
    */
   public void setIndentLvl( Integer IndentLvl )
   {
      this.IndentLvl = IndentLvl;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Create
    */
   public String getCreate( )
   {
      return Create;
   }

   /**
    * @param Create to set 
    */
   public void setCreate( String Create )
   {
      this.Create = Create;
   }

   /**
    * @return the Delete
    */
   public String getDelete( )
   {
      return Delete;
   }

   /**
    * @param Delete to set 
    */
   public void setDelete( String Delete )
   {
      this.Delete = Delete;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the Include
    */
   public String getInclude( )
   {
      return Include;
   }

   /**
    * @param Include to set 
    */
   public void setInclude( String Include )
   {
      this.Include = Include;
   }

   /**
    * @return the InclSrc
    */
   public String getInclSrc( )
   {
      return InclSrc;
   }

   /**
    * @param InclSrc to set 
    */
   public void setInclSrc( String InclSrc )
   {
      this.InclSrc = InclSrc;
   }

   /**
    * @return the Exclude
    */
   public String getExclude( )
   {
      return Exclude;
   }

   /**
    * @param Exclude to set 
    */
   public void setExclude( String Exclude )
   {
      this.Exclude = Exclude;
   }

   /**
    * @return the CreateConstraint
    */
   public String getCreateConstraint( )
   {
      return CreateConstraint;
   }

   /**
    * @param CreateConstraint to set 
    */
   public void setCreateConstraint( String CreateConstraint )
   {
      this.CreateConstraint = CreateConstraint;
   }

   /**
    * @return the DeleteConstraint
    */
   public String getDeleteConstraint( )
   {
      return DeleteConstraint;
   }

   /**
    * @param DeleteConstraint to set 
    */
   public void setDeleteConstraint( String DeleteConstraint )
   {
      this.DeleteConstraint = DeleteConstraint;
   }

   /**
    * @return the IncludeConstraint
    */
   public String getIncludeConstraint( )
   {
      return IncludeConstraint;
   }

   /**
    * @param IncludeConstraint to set 
    */
   public void setIncludeConstraint( String IncludeConstraint )
   {
      this.IncludeConstraint = IncludeConstraint;
   }

   /**
    * @return the ExcludeConstraint
    */
   public String getExcludeConstraint( )
   {
      return ExcludeConstraint;
   }

   /**
    * @param ExcludeConstraint to set 
    */
   public void setExcludeConstraint( String ExcludeConstraint )
   {
      this.ExcludeConstraint = ExcludeConstraint;
   }

   /**
    * @return the AcceptConstraint
    */
   public String getAcceptConstraint( )
   {
      return AcceptConstraint;
   }

   /**
    * @param AcceptConstraint to set 
    */
   public void setAcceptConstraint( String AcceptConstraint )
   {
      this.AcceptConstraint = AcceptConstraint;
   }

   /**
    * @return the CancelConstraint
    */
   public String getCancelConstraint( )
   {
      return CancelConstraint;
   }

   /**
    * @param CancelConstraint to set 
    */
   public void setCancelConstraint( String CancelConstraint )
   {
      this.CancelConstraint = CancelConstraint;
   }

   /**
    * @return the SeqNo
    */
   public Integer getSeqNo( )
   {
      return SeqNo;
   }

   /**
    * @param SeqNo to set 
    */
   public void setSeqNo( Integer SeqNo )
   {
      this.SeqNo = SeqNo;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the MultipleChildLimit
    */
   public Integer getMultipleChildLimit( )
   {
      return MultipleChildLimit;
   }

   /**
    * @param MultipleChildLimit to set 
    */
   public void setMultipleChildLimit( Integer MultipleChildLimit )
   {
      this.MultipleChildLimit = MultipleChildLimit;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the Recursive
    */
   public String getRecursive( )
   {
      return Recursive;
   }

   /**
    * @param Recursive to set 
    */
   public void setRecursive( String Recursive )
   {
      this.Recursive = Recursive;
   }

   /**
    * @return the AutoCreate
    */
   public String getAutoCreate( )
   {
      return AutoCreate;
   }

   /**
    * @param AutoCreate to set 
    */
   public void setAutoCreate( String AutoCreate )
   {
      this.AutoCreate = AutoCreate;
   }

   /**
    * @return the Derived
    */
   public String getDerived( )
   {
      return Derived;
   }

   /**
    * @param Derived to set 
    */
   public void setDerived( String Derived )
   {
      this.Derived = Derived;
   }

   /**
    * @return the SeqType
    */
   public String getSeqType( )
   {
      return SeqType;
   }

   /**
    * @param SeqType to set 
    */
   public void setSeqType( String SeqType )
   {
      this.SeqType = SeqType;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the ParentDeleteBehave
    */
   public String getParentDeleteBehave( )
   {
      return ParentDeleteBehave;
   }

   /**
    * @param ParentDeleteBehave to set 
    */
   public void setParentDeleteBehave( String ParentDeleteBehave )
   {
      this.ParentDeleteBehave = ParentDeleteBehave;
   }

   /**
    * @return the DupEntityInstance
    */
   public String getDupEntityInstance( )
   {
      return DupEntityInstance;
   }

   /**
    * @param DupEntityInstance to set 
    */
   public void setDupEntityInstance( String DupEntityInstance )
   {
      this.DupEntityInstance = DupEntityInstance;
   }

   /**
    * @return the DupRelationshipInstance
    */
   public String getDupRelationshipInstance( )
   {
      return DupRelationshipInstance;
   }

   /**
    * @param DupRelationshipInstance to set 
    */
   public void setDupRelationshipInstance( String DupRelationshipInstance )
   {
      this.DupRelationshipInstance = DupRelationshipInstance;
   }

   /**
    * @return the RelLinkIndicator
    */
   public String getRelLinkIndicator( )
   {
      return RelLinkIndicator;
   }

   /**
    * @param RelLinkIndicator to set 
    */
   public void setRelLinkIndicator( String RelLinkIndicator )
   {
      this.RelLinkIndicator = RelLinkIndicator;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Abstract
    */
   public String getAbstract( )
   {
      return Abstract;
   }

   /**
    * @param Abstract to set 
    */
   public void setAbstract( String Abstract )
   {
      this.Abstract = Abstract;
   }

   /**
    * @return the XML_Name
    */
   public String getXML_Name( )
   {
      return XML_Name;
   }

   /**
    * @param XML_Name to set 
    */
   public void setXML_Name( String XML_Name )
   {
      this.XML_Name = XML_Name;
   }

   /**
    * @return the LazyLoadFlag
    */
   public String getLazyLoadFlag( )
   {
      return LazyLoadFlag;
   }

   /**
    * @param LazyLoadFlag to set 
    */
   public void setLazyLoadFlag( String LazyLoadFlag )
   {
      this.LazyLoadFlag = LazyLoadFlag;
   }

   /**
    * @return the ReportDisplayFlag
    */
   public String getReportDisplayFlag( )
   {
      return ReportDisplayFlag;
   }

   /**
    * @param ReportDisplayFlag to set 
    */
   public void setReportDisplayFlag( String ReportDisplayFlag )
   {
      this.ReportDisplayFlag = ReportDisplayFlag;
   }

   public int loadOptMapRelatedEntityEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      IndentName = cursor.getStringFromAttribute( "IndentName" );  if ( IndentName == null ) IndentName = "";
      IndentLvl = cursor.getIntegerFromAttribute( "IndentLvl" );  if ( IndentLvl == null ) IndentLvl = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Create = cursor.getStringFromAttribute( "Create" );  if ( Create == null ) Create = "";
      Delete = cursor.getStringFromAttribute( "Delete" );  if ( Delete == null ) Delete = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      Include = cursor.getStringFromAttribute( "Include" );  if ( Include == null ) Include = "";
      InclSrc = cursor.getStringFromAttribute( "InclSrc" );  if ( InclSrc == null ) InclSrc = "";
      Exclude = cursor.getStringFromAttribute( "Exclude" );  if ( Exclude == null ) Exclude = "";
      CreateConstraint = cursor.getStringFromAttribute( "CreateConstraint" );  if ( CreateConstraint == null ) CreateConstraint = "";
      DeleteConstraint = cursor.getStringFromAttribute( "DeleteConstraint" );  if ( DeleteConstraint == null ) DeleteConstraint = "";
      IncludeConstraint = cursor.getStringFromAttribute( "IncludeConstraint" );  if ( IncludeConstraint == null ) IncludeConstraint = "";
      ExcludeConstraint = cursor.getStringFromAttribute( "ExcludeConstraint" );  if ( ExcludeConstraint == null ) ExcludeConstraint = "";
      AcceptConstraint = cursor.getStringFromAttribute( "AcceptConstraint" );  if ( AcceptConstraint == null ) AcceptConstraint = "";
      CancelConstraint = cursor.getStringFromAttribute( "CancelConstraint" );  if ( CancelConstraint == null ) CancelConstraint = "";
      SeqNo = cursor.getIntegerFromAttribute( "SeqNo" );  if ( SeqNo == null ) SeqNo = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      MultipleChildLimit = cursor.getIntegerFromAttribute( "MultipleChildLimit" );  if ( MultipleChildLimit == null ) MultipleChildLimit = 0;
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      Recursive = cursor.getStringFromAttribute( "Recursive" );  if ( Recursive == null ) Recursive = "";
      AutoCreate = cursor.getStringFromAttribute( "AutoCreate" );  if ( AutoCreate == null ) AutoCreate = "";
      Derived = cursor.getStringFromAttribute( "Derived" );  if ( Derived == null ) Derived = "";
      SeqType = cursor.getStringFromAttribute( "SeqType" );  if ( SeqType == null ) SeqType = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      ParentDeleteBehave = cursor.getStringFromAttribute( "ParentDeleteBehave" );  if ( ParentDeleteBehave == null ) ParentDeleteBehave = "";
      DupEntityInstance = cursor.getStringFromAttribute( "DupEntityInstance" );  if ( DupEntityInstance == null ) DupEntityInstance = "";
      DupRelationshipInstance = cursor.getStringFromAttribute( "DupRelationshipInstance" );  if ( DupRelationshipInstance == null ) DupRelationshipInstance = "";
      RelLinkIndicator = cursor.getStringFromAttribute( "RelLinkIndicator" );  if ( RelLinkIndicator == null ) RelLinkIndicator = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Abstract = cursor.getStringFromAttribute( "Abstract" );  if ( Abstract == null ) Abstract = "";
      XML_Name = cursor.getStringFromAttribute( "XML_Name" );  if ( XML_Name == null ) XML_Name = "";
      LazyLoadFlag = cursor.getStringFromAttribute( "LazyLoadFlag" );  if ( LazyLoadFlag == null ) LazyLoadFlag = "";
      ReportDisplayFlag = cursor.getStringFromAttribute( "ReportDisplayFlag" );  if ( ReportDisplayFlag == null ) ReportDisplayFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptMapER_AttributeImpl implements OptMapER_Attribute
{
   protected String  Name;
   protected String  CaseSens;
   protected String  TE_ColumnName;
   protected String  TE_ForeignKeyName;
   protected String  Work;
   protected String  DerivedExpression;
   protected Integer ZKey;
   protected Integer Lth;
   protected String  Key;
   protected String  NotNull;
   protected String  Desc;
   protected String  PromptPaintLit;
   protected Integer PromptPaintLth;
   protected String  ListPaintLit;
   protected Integer ListPaintLth;
   protected String  ADW_Position;
   protected Blob    DerivedExpressionXPG;
   protected Integer Sequence;
   protected Integer SAP_Attribute;
   protected String  XML_SimpleName;
   protected String  XML_NameExternal;


   // ctor
   protected OptMapER_AttributeImpl( EntityCursor cursor )
   {
      loadOptMapER_AttributeEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the CaseSens
    */
   public String getCaseSens( )
   {
      return CaseSens;
   }

   /**
    * @param CaseSens to set 
    */
   public void setCaseSens( String CaseSens )
   {
      this.CaseSens = CaseSens;
   }

   /**
    * @return the TE_ColumnName
    */
   public String getTE_ColumnName( )
   {
      return TE_ColumnName;
   }

   /**
    * @param TE_ColumnName to set 
    */
   public void setTE_ColumnName( String TE_ColumnName )
   {
      this.TE_ColumnName = TE_ColumnName;
   }

   /**
    * @return the TE_ForeignKeyName
    */
   public String getTE_ForeignKeyName( )
   {
      return TE_ForeignKeyName;
   }

   /**
    * @param TE_ForeignKeyName to set 
    */
   public void setTE_ForeignKeyName( String TE_ForeignKeyName )
   {
      this.TE_ForeignKeyName = TE_ForeignKeyName;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the DerivedExpression
    */
   public String getDerivedExpression( )
   {
      return DerivedExpression;
   }

   /**
    * @param DerivedExpression to set 
    */
   public void setDerivedExpression( String DerivedExpression )
   {
      this.DerivedExpression = DerivedExpression;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Lth
    */
   public Integer getLth( )
   {
      return Lth;
   }

   /**
    * @param Lth to set 
    */
   public void setLth( Integer Lth )
   {
      this.Lth = Lth;
   }

   /**
    * @return the Key
    */
   public String getKey( )
   {
      return Key;
   }

   /**
    * @param Key to set 
    */
   public void setKey( String Key )
   {
      this.Key = Key;
   }

   /**
    * @return the NotNull
    */
   public String getNotNull( )
   {
      return NotNull;
   }

   /**
    * @param NotNull to set 
    */
   public void setNotNull( String NotNull )
   {
      this.NotNull = NotNull;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the PromptPaintLit
    */
   public String getPromptPaintLit( )
   {
      return PromptPaintLit;
   }

   /**
    * @param PromptPaintLit to set 
    */
   public void setPromptPaintLit( String PromptPaintLit )
   {
      this.PromptPaintLit = PromptPaintLit;
   }

   /**
    * @return the PromptPaintLth
    */
   public Integer getPromptPaintLth( )
   {
      return PromptPaintLth;
   }

   /**
    * @param PromptPaintLth to set 
    */
   public void setPromptPaintLth( Integer PromptPaintLth )
   {
      this.PromptPaintLth = PromptPaintLth;
   }

   /**
    * @return the ListPaintLit
    */
   public String getListPaintLit( )
   {
      return ListPaintLit;
   }

   /**
    * @param ListPaintLit to set 
    */
   public void setListPaintLit( String ListPaintLit )
   {
      this.ListPaintLit = ListPaintLit;
   }

   /**
    * @return the ListPaintLth
    */
   public Integer getListPaintLth( )
   {
      return ListPaintLth;
   }

   /**
    * @param ListPaintLth to set 
    */
   public void setListPaintLth( Integer ListPaintLth )
   {
      this.ListPaintLth = ListPaintLth;
   }

   /**
    * @return the ADW_Position
    */
   public String getADW_Position( )
   {
      return ADW_Position;
   }

   /**
    * @param ADW_Position to set 
    */
   public void setADW_Position( String ADW_Position )
   {
      this.ADW_Position = ADW_Position;
   }

   /**
    * @return the DerivedExpressionXPG
    */
   public Blob getDerivedExpressionXPG( )
   {
      return DerivedExpressionXPG;
   }

   /**
    * @param DerivedExpressionXPG to set 
    */
   public void setDerivedExpressionXPG( Blob DerivedExpressionXPG )
   {
      this.DerivedExpressionXPG = DerivedExpressionXPG;
   }

   /**
    * @return the Sequence
    */
   public Integer getSequence( )
   {
      return Sequence;
   }

   /**
    * @param Sequence to set 
    */
   public void setSequence( Integer Sequence )
   {
      this.Sequence = Sequence;
   }

   /**
    * @return the SAP_Attribute
    */
   public Integer getSAP_Attribute( )
   {
      return SAP_Attribute;
   }

   /**
    * @param SAP_Attribute to set 
    */
   public void setSAP_Attribute( Integer SAP_Attribute )
   {
      this.SAP_Attribute = SAP_Attribute;
   }

   /**
    * @return the XML_SimpleName
    */
   public String getXML_SimpleName( )
   {
      return XML_SimpleName;
   }

   /**
    * @param XML_SimpleName to set 
    */
   public void setXML_SimpleName( String XML_SimpleName )
   {
      this.XML_SimpleName = XML_SimpleName;
   }

   /**
    * @return the XML_NameExternal
    */
   public String getXML_NameExternal( )
   {
      return XML_NameExternal;
   }

   /**
    * @param XML_NameExternal to set 
    */
   public void setXML_NameExternal( String XML_NameExternal )
   {
      this.XML_NameExternal = XML_NameExternal;
   }

   public int loadOptMapER_AttributeEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      CaseSens = cursor.getStringFromAttribute( "CaseSens" );  if ( CaseSens == null ) CaseSens = "";
      TE_ColumnName = cursor.getStringFromAttribute( "TE_ColumnName" );  if ( TE_ColumnName == null ) TE_ColumnName = "";
      TE_ForeignKeyName = cursor.getStringFromAttribute( "TE_ForeignKeyName" );  if ( TE_ForeignKeyName == null ) TE_ForeignKeyName = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      DerivedExpression = cursor.getStringFromAttribute( "DerivedExpression" );  if ( DerivedExpression == null ) DerivedExpression = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Lth = cursor.getIntegerFromAttribute( "Lth" );  if ( Lth == null ) Lth = 0;
      Key = cursor.getStringFromAttribute( "Key" );  if ( Key == null ) Key = "";
      NotNull = cursor.getStringFromAttribute( "NotNull" );  if ( NotNull == null ) NotNull = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      PromptPaintLit = cursor.getStringFromAttribute( "PromptPaintLit" );  if ( PromptPaintLit == null ) PromptPaintLit = "";
      PromptPaintLth = cursor.getIntegerFromAttribute( "PromptPaintLth" );  if ( PromptPaintLth == null ) PromptPaintLth = 0;
      ListPaintLit = cursor.getStringFromAttribute( "ListPaintLit" );  if ( ListPaintLit == null ) ListPaintLit = "";
      ListPaintLth = cursor.getIntegerFromAttribute( "ListPaintLth" );  if ( ListPaintLth == null ) ListPaintLth = 0;
      ADW_Position = cursor.getStringFromAttribute( "ADW_Position" );  if ( ADW_Position == null ) ADW_Position = "";
      DerivedExpressionXPG = cursor.getBlobFromAttribute( "DerivedExpressionXPG" );
      Sequence = cursor.getIntegerFromAttribute( "Sequence" );  if ( Sequence == null ) Sequence = 0;
      SAP_Attribute = cursor.getIntegerFromAttribute( "SAP_Attribute" );  if ( SAP_Attribute == null ) SAP_Attribute = 0;
      XML_SimpleName = cursor.getStringFromAttribute( "XML_SimpleName" );  if ( XML_SimpleName == null ) XML_SimpleName = "";
      XML_NameExternal = cursor.getStringFromAttribute( "XML_NameExternal" );  if ( XML_NameExternal == null ) XML_NameExternal = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptMapER_DomainImpl implements OptMapER_Domain
{
   protected Integer ZKey;
   protected String  DerivedName;
   protected String  DerivedDataType;
   protected Integer DerivedMaxStringLth;
   protected Integer DerivedDecimalFormat;
   protected String  Name;
   protected String  DomainType;
   protected String  DataType;
   protected Integer MaxStringLth;
   protected String  ContextRestriction;
   protected Integer DecimalFormat;
   protected String  Desc;
   protected String  ConstraintRule;


   // ctor
   protected OptMapER_DomainImpl( EntityCursor cursor )
   {
      loadOptMapER_DomainEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DerivedName
    */
   public String getDerivedName( )
   {
      return DerivedName;
   }

   /**
    * @param DerivedName to set 
    */
   public void setDerivedName( String DerivedName )
   {
      this.DerivedName = DerivedName;
   }

   /**
    * @return the DerivedDataType
    */
   public String getDerivedDataType( )
   {
      return DerivedDataType;
   }

   /**
    * @param DerivedDataType to set 
    */
   public void setDerivedDataType( String DerivedDataType )
   {
      this.DerivedDataType = DerivedDataType;
   }

   /**
    * @return the DerivedMaxStringLth
    */
   public Integer getDerivedMaxStringLth( )
   {
      return DerivedMaxStringLth;
   }

   /**
    * @param DerivedMaxStringLth to set 
    */
   public void setDerivedMaxStringLth( Integer DerivedMaxStringLth )
   {
      this.DerivedMaxStringLth = DerivedMaxStringLth;
   }

   /**
    * @return the DerivedDecimalFormat
    */
   public Integer getDerivedDecimalFormat( )
   {
      return DerivedDecimalFormat;
   }

   /**
    * @param DerivedDecimalFormat to set 
    */
   public void setDerivedDecimalFormat( Integer DerivedDecimalFormat )
   {
      this.DerivedDecimalFormat = DerivedDecimalFormat;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the DomainType
    */
   public String getDomainType( )
   {
      return DomainType;
   }

   /**
    * @param DomainType to set 
    */
   public void setDomainType( String DomainType )
   {
      this.DomainType = DomainType;
   }

   /**
    * @return the DataType
    */
   public String getDataType( )
   {
      return DataType;
   }

   /**
    * @param DataType to set 
    */
   public void setDataType( String DataType )
   {
      this.DataType = DataType;
   }

   /**
    * @return the MaxStringLth
    */
   public Integer getMaxStringLth( )
   {
      return MaxStringLth;
   }

   /**
    * @param MaxStringLth to set 
    */
   public void setMaxStringLth( Integer MaxStringLth )
   {
      this.MaxStringLth = MaxStringLth;
   }

   /**
    * @return the ContextRestriction
    */
   public String getContextRestriction( )
   {
      return ContextRestriction;
   }

   /**
    * @param ContextRestriction to set 
    */
   public void setContextRestriction( String ContextRestriction )
   {
      this.ContextRestriction = ContextRestriction;
   }

   /**
    * @return the DecimalFormat
    */
   public Integer getDecimalFormat( )
   {
      return DecimalFormat;
   }

   /**
    * @param DecimalFormat to set 
    */
   public void setDecimalFormat( Integer DecimalFormat )
   {
      this.DecimalFormat = DecimalFormat;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the ConstraintRule
    */
   public String getConstraintRule( )
   {
      return ConstraintRule;
   }

   /**
    * @param ConstraintRule to set 
    */
   public void setConstraintRule( String ConstraintRule )
   {
      this.ConstraintRule = ConstraintRule;
   }

   public int loadOptMapER_DomainEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DerivedName = cursor.getStringFromAttribute( "DerivedName" );  if ( DerivedName == null ) DerivedName = "";
      DerivedDataType = cursor.getStringFromAttribute( "DerivedDataType" );  if ( DerivedDataType == null ) DerivedDataType = "";
      DerivedMaxStringLth = cursor.getIntegerFromAttribute( "DerivedMaxStringLth" );  if ( DerivedMaxStringLth == null ) DerivedMaxStringLth = 0;
      DerivedDecimalFormat = cursor.getIntegerFromAttribute( "DerivedDecimalFormat" );  if ( DerivedDecimalFormat == null ) DerivedDecimalFormat = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      DomainType = cursor.getStringFromAttribute( "DomainType" );  if ( DomainType == null ) DomainType = "";
      DataType = cursor.getStringFromAttribute( "DataType" );  if ( DataType == null ) DataType = "";
      MaxStringLth = cursor.getIntegerFromAttribute( "MaxStringLth" );  if ( MaxStringLth == null ) MaxStringLth = 0;
      ContextRestriction = cursor.getStringFromAttribute( "ContextRestriction" );  if ( ContextRestriction == null ) ContextRestriction = "";
      DecimalFormat = cursor.getIntegerFromAttribute( "DecimalFormat" );  if ( DecimalFormat == null ) DecimalFormat = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      ConstraintRule = cursor.getStringFromAttribute( "ConstraintRule" );  if ( ConstraintRule == null ) ConstraintRule = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptMapContextImpl implements OptMapContext
{
   protected Integer ZKey;
   protected String  DerivedName;
   protected String  Desc;
   protected String  Name;
   protected Integer DecimalFormat;
   protected String  EditString;
   protected String  IsDefault;
   protected String  DIL_Text;


   // ctor
   protected OptMapContextImpl( EntityCursor cursor )
   {
      loadOptMapContextEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DerivedName
    */
   public String getDerivedName( )
   {
      return DerivedName;
   }

   /**
    * @param DerivedName to set 
    */
   public void setDerivedName( String DerivedName )
   {
      this.DerivedName = DerivedName;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the DecimalFormat
    */
   public Integer getDecimalFormat( )
   {
      return DecimalFormat;
   }

   /**
    * @param DecimalFormat to set 
    */
   public void setDecimalFormat( Integer DecimalFormat )
   {
      this.DecimalFormat = DecimalFormat;
   }

   /**
    * @return the EditString
    */
   public String getEditString( )
   {
      return EditString;
   }

   /**
    * @param EditString to set 
    */
   public void setEditString( String EditString )
   {
      this.EditString = EditString;
   }

   /**
    * @return the IsDefault
    */
   public String getIsDefault( )
   {
      return IsDefault;
   }

   /**
    * @param IsDefault to set 
    */
   public void setIsDefault( String IsDefault )
   {
      this.IsDefault = IsDefault;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   public int loadOptMapContextEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DerivedName = cursor.getStringFromAttribute( "DerivedName" );  if ( DerivedName == null ) DerivedName = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      DecimalFormat = cursor.getIntegerFromAttribute( "DecimalFormat" );  if ( DecimalFormat == null ) DecimalFormat = 0;
      EditString = cursor.getStringFromAttribute( "EditString" );  if ( EditString == null ) EditString = "";
      IsDefault = cursor.getStringFromAttribute( "IsDefault" );  if ( IsDefault == null ) IsDefault = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptMapViewImpl implements OptMapView
{
   protected Integer ZKey;
   protected String  Name;
   protected String  Desc;
   protected Integer Level;
   protected String  IsDrivingViewForReportFlag;


   // ctor
   protected OptMapViewImpl( EntityCursor cursor )
   {
      loadOptMapViewEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Level
    */
   public Integer getLevel( )
   {
      return Level;
   }

   /**
    * @param Level to set 
    */
   public void setLevel( Integer Level )
   {
      this.Level = Level;
   }

   /**
    * @return the IsDrivingViewForReportFlag
    */
   public String getIsDrivingViewForReportFlag( )
   {
      return IsDrivingViewForReportFlag;
   }

   /**
    * @param IsDrivingViewForReportFlag to set 
    */
   public void setIsDrivingViewForReportFlag( String IsDrivingViewForReportFlag )
   {
      this.IsDrivingViewForReportFlag = IsDrivingViewForReportFlag;
   }

   public int loadOptMapViewEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Level = cursor.getIntegerFromAttribute( "Level" );  if ( Level == null ) Level = 0;
      IsDrivingViewForReportFlag = cursor.getStringFromAttribute( "IsDrivingViewForReportFlag" );  if ( IsDrivingViewForReportFlag == null ) IsDrivingViewForReportFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptionNLS_TextImpl implements OptionNLS_Text
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected OptionNLS_TextImpl( EntityCursor cursor )
   {
      loadOptionNLS_TextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadOptionNLS_TextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OptionNLS_DIL_TextImpl implements OptionNLS_DIL_Text
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected OptionNLS_DIL_TextImpl( EntityCursor cursor )
   {
      loadOptionNLS_DIL_TextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadOptionNLS_DIL_TextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class DfltMenuImpl implements DfltMenu
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  CSS_Class;


   // ctor
   protected DfltMenuImpl( EntityCursor cursor )
   {
      loadDfltMenuEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   public int loadDfltMenuEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndCaptionMapImpl implements WndCaptionMap
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  Type;
   protected Integer SeqNo_DlgCtrl;
   protected Integer SeqNo_DlgAct;


   // ctor
   protected WndCaptionMapImpl( EntityCursor cursor )
   {
      loadWndCaptionMapEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the SeqNo_DlgCtrl
    */
   public Integer getSeqNo_DlgCtrl( )
   {
      return SeqNo_DlgCtrl;
   }

   /**
    * @param SeqNo_DlgCtrl to set 
    */
   public void setSeqNo_DlgCtrl( Integer SeqNo_DlgCtrl )
   {
      this.SeqNo_DlgCtrl = SeqNo_DlgCtrl;
   }

   /**
    * @return the SeqNo_DlgAct
    */
   public Integer getSeqNo_DlgAct( )
   {
      return SeqNo_DlgAct;
   }

   /**
    * @param SeqNo_DlgAct to set 
    */
   public void setSeqNo_DlgAct( Integer SeqNo_DlgAct )
   {
      this.SeqNo_DlgAct = SeqNo_DlgAct;
   }

   public int loadWndCaptionMapEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      SeqNo_DlgCtrl = cursor.getIntegerFromAttribute( "SeqNo_DlgCtrl" );  if ( SeqNo_DlgCtrl == null ) SeqNo_DlgCtrl = 0;
      SeqNo_DlgAct = cursor.getIntegerFromAttribute( "SeqNo_DlgAct" );  if ( SeqNo_DlgAct == null ) SeqNo_DlgAct = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndCaptionMapLOD_AttributeImpl implements WndCaptionMapLOD_Attribute
{
   protected Integer ZKey;
   protected String  Work;
   protected String  Update;
   protected String  Init;
   protected String  Hidden;
   protected Integer SeqPriority;
   protected String  SeqOrder;
   protected String  DIL_Text;
   protected Integer SeqNo_LOD_Entity;
   protected Integer SeqNo_UIS_Entity_M;
   protected Integer SeqNo_UIS_Entity_L;
   protected String  DB_DerivedValue;
   protected String  XML_Simple;
   protected String  HashkeyType;
   protected String  HashkeyParentEntityName;


   // ctor
   protected WndCaptionMapLOD_AttributeImpl( EntityCursor cursor )
   {
      loadWndCaptionMapLOD_AttributeEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the Init
    */
   public String getInit( )
   {
      return Init;
   }

   /**
    * @param Init to set 
    */
   public void setInit( String Init )
   {
      this.Init = Init;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the SeqPriority
    */
   public Integer getSeqPriority( )
   {
      return SeqPriority;
   }

   /**
    * @param SeqPriority to set 
    */
   public void setSeqPriority( Integer SeqPriority )
   {
      this.SeqPriority = SeqPriority;
   }

   /**
    * @return the SeqOrder
    */
   public String getSeqOrder( )
   {
      return SeqOrder;
   }

   /**
    * @param SeqOrder to set 
    */
   public void setSeqOrder( String SeqOrder )
   {
      this.SeqOrder = SeqOrder;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the SeqNo_LOD_Entity
    */
   public Integer getSeqNo_LOD_Entity( )
   {
      return SeqNo_LOD_Entity;
   }

   /**
    * @param SeqNo_LOD_Entity to set 
    */
   public void setSeqNo_LOD_Entity( Integer SeqNo_LOD_Entity )
   {
      this.SeqNo_LOD_Entity = SeqNo_LOD_Entity;
   }

   /**
    * @return the SeqNo_UIS_Entity_M
    */
   public Integer getSeqNo_UIS_Entity_M( )
   {
      return SeqNo_UIS_Entity_M;
   }

   /**
    * @param SeqNo_UIS_Entity_M to set 
    */
   public void setSeqNo_UIS_Entity_M( Integer SeqNo_UIS_Entity_M )
   {
      this.SeqNo_UIS_Entity_M = SeqNo_UIS_Entity_M;
   }

   /**
    * @return the SeqNo_UIS_Entity_L
    */
   public Integer getSeqNo_UIS_Entity_L( )
   {
      return SeqNo_UIS_Entity_L;
   }

   /**
    * @param SeqNo_UIS_Entity_L to set 
    */
   public void setSeqNo_UIS_Entity_L( Integer SeqNo_UIS_Entity_L )
   {
      this.SeqNo_UIS_Entity_L = SeqNo_UIS_Entity_L;
   }

   /**
    * @return the DB_DerivedValue
    */
   public String getDB_DerivedValue( )
   {
      return DB_DerivedValue;
   }

   /**
    * @param DB_DerivedValue to set 
    */
   public void setDB_DerivedValue( String DB_DerivedValue )
   {
      this.DB_DerivedValue = DB_DerivedValue;
   }

   /**
    * @return the XML_Simple
    */
   public String getXML_Simple( )
   {
      return XML_Simple;
   }

   /**
    * @param XML_Simple to set 
    */
   public void setXML_Simple( String XML_Simple )
   {
      this.XML_Simple = XML_Simple;
   }

   /**
    * @return the HashkeyType
    */
   public String getHashkeyType( )
   {
      return HashkeyType;
   }

   /**
    * @param HashkeyType to set 
    */
   public void setHashkeyType( String HashkeyType )
   {
      this.HashkeyType = HashkeyType;
   }

   /**
    * @return the HashkeyParentEntityName
    */
   public String getHashkeyParentEntityName( )
   {
      return HashkeyParentEntityName;
   }

   /**
    * @param HashkeyParentEntityName to set 
    */
   public void setHashkeyParentEntityName( String HashkeyParentEntityName )
   {
      this.HashkeyParentEntityName = HashkeyParentEntityName;
   }

   public int loadWndCaptionMapLOD_AttributeEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      Init = cursor.getStringFromAttribute( "Init" );  if ( Init == null ) Init = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      SeqPriority = cursor.getIntegerFromAttribute( "SeqPriority" );  if ( SeqPriority == null ) SeqPriority = 0;
      SeqOrder = cursor.getStringFromAttribute( "SeqOrder" );  if ( SeqOrder == null ) SeqOrder = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      SeqNo_LOD_Entity = cursor.getIntegerFromAttribute( "SeqNo_LOD_Entity" );  if ( SeqNo_LOD_Entity == null ) SeqNo_LOD_Entity = 0;
      SeqNo_UIS_Entity_M = cursor.getIntegerFromAttribute( "SeqNo_UIS_Entity_M" );  if ( SeqNo_UIS_Entity_M == null ) SeqNo_UIS_Entity_M = 0;
      SeqNo_UIS_Entity_L = cursor.getIntegerFromAttribute( "SeqNo_UIS_Entity_L" );  if ( SeqNo_UIS_Entity_L == null ) SeqNo_UIS_Entity_L = 0;
      DB_DerivedValue = cursor.getStringFromAttribute( "DB_DerivedValue" );  if ( DB_DerivedValue == null ) DB_DerivedValue = "";
      XML_Simple = cursor.getStringFromAttribute( "XML_Simple" );  if ( XML_Simple == null ) XML_Simple = "";
      HashkeyType = cursor.getStringFromAttribute( "HashkeyType" );  if ( HashkeyType == null ) HashkeyType = "";
      HashkeyParentEntityName = cursor.getStringFromAttribute( "HashkeyParentEntityName" );  if ( HashkeyParentEntityName == null ) HashkeyParentEntityName = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndCaptionMapRelatedEntityImpl implements WndCaptionMapRelatedEntity
{
   protected String  Name;
   protected String  IndentName;
   protected String  CreateConstraint;
   protected String  DeleteConstraint;
   protected String  IncludeConstraint;
   protected String  ExcludeConstraint;
   protected String  AcceptConstraint;
   protected String  CancelConstraint;
   protected Integer SeqNo;
   protected Integer DataLocking;
   protected Integer MultipleChildLimit;
   protected Integer IndentLvl;
   protected Integer ZKey;
   protected String  Create;
   protected String  Delete;
   protected String  Update;
   protected String  Include;
   protected String  InclSrc;
   protected String  Exclude;
   protected String  Hidden;
   protected String  Recursive;
   protected String  AutoCreate;
   protected String  Derived;
   protected String  SeqType;
   protected String  Work;
   protected String  ParentDeleteBehave;
   protected String  DupEntityInstance;
   protected String  DupRelationshipInstance;
   protected String  RelLinkIndicator;
   protected String  Desc;
   protected String  Abstract;
   protected String  XML_Name;
   protected String  LazyLoadFlag;
   protected String  ReportDisplayFlag;


   // ctor
   protected WndCaptionMapRelatedEntityImpl( EntityCursor cursor )
   {
      loadWndCaptionMapRelatedEntityEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the IndentName
    */
   public String getIndentName( )
   {
      return IndentName;
   }

   /**
    * @param IndentName to set 
    */
   public void setIndentName( String IndentName )
   {
      this.IndentName = IndentName;
   }

   /**
    * @return the CreateConstraint
    */
   public String getCreateConstraint( )
   {
      return CreateConstraint;
   }

   /**
    * @param CreateConstraint to set 
    */
   public void setCreateConstraint( String CreateConstraint )
   {
      this.CreateConstraint = CreateConstraint;
   }

   /**
    * @return the DeleteConstraint
    */
   public String getDeleteConstraint( )
   {
      return DeleteConstraint;
   }

   /**
    * @param DeleteConstraint to set 
    */
   public void setDeleteConstraint( String DeleteConstraint )
   {
      this.DeleteConstraint = DeleteConstraint;
   }

   /**
    * @return the IncludeConstraint
    */
   public String getIncludeConstraint( )
   {
      return IncludeConstraint;
   }

   /**
    * @param IncludeConstraint to set 
    */
   public void setIncludeConstraint( String IncludeConstraint )
   {
      this.IncludeConstraint = IncludeConstraint;
   }

   /**
    * @return the ExcludeConstraint
    */
   public String getExcludeConstraint( )
   {
      return ExcludeConstraint;
   }

   /**
    * @param ExcludeConstraint to set 
    */
   public void setExcludeConstraint( String ExcludeConstraint )
   {
      this.ExcludeConstraint = ExcludeConstraint;
   }

   /**
    * @return the AcceptConstraint
    */
   public String getAcceptConstraint( )
   {
      return AcceptConstraint;
   }

   /**
    * @param AcceptConstraint to set 
    */
   public void setAcceptConstraint( String AcceptConstraint )
   {
      this.AcceptConstraint = AcceptConstraint;
   }

   /**
    * @return the CancelConstraint
    */
   public String getCancelConstraint( )
   {
      return CancelConstraint;
   }

   /**
    * @param CancelConstraint to set 
    */
   public void setCancelConstraint( String CancelConstraint )
   {
      this.CancelConstraint = CancelConstraint;
   }

   /**
    * @return the SeqNo
    */
   public Integer getSeqNo( )
   {
      return SeqNo;
   }

   /**
    * @param SeqNo to set 
    */
   public void setSeqNo( Integer SeqNo )
   {
      this.SeqNo = SeqNo;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the MultipleChildLimit
    */
   public Integer getMultipleChildLimit( )
   {
      return MultipleChildLimit;
   }

   /**
    * @param MultipleChildLimit to set 
    */
   public void setMultipleChildLimit( Integer MultipleChildLimit )
   {
      this.MultipleChildLimit = MultipleChildLimit;
   }

   /**
    * @return the IndentLvl
    */
   public Integer getIndentLvl( )
   {
      return IndentLvl;
   }

   /**
    * @param IndentLvl to set 
    */
   public void setIndentLvl( Integer IndentLvl )
   {
      this.IndentLvl = IndentLvl;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Create
    */
   public String getCreate( )
   {
      return Create;
   }

   /**
    * @param Create to set 
    */
   public void setCreate( String Create )
   {
      this.Create = Create;
   }

   /**
    * @return the Delete
    */
   public String getDelete( )
   {
      return Delete;
   }

   /**
    * @param Delete to set 
    */
   public void setDelete( String Delete )
   {
      this.Delete = Delete;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the Include
    */
   public String getInclude( )
   {
      return Include;
   }

   /**
    * @param Include to set 
    */
   public void setInclude( String Include )
   {
      this.Include = Include;
   }

   /**
    * @return the InclSrc
    */
   public String getInclSrc( )
   {
      return InclSrc;
   }

   /**
    * @param InclSrc to set 
    */
   public void setInclSrc( String InclSrc )
   {
      this.InclSrc = InclSrc;
   }

   /**
    * @return the Exclude
    */
   public String getExclude( )
   {
      return Exclude;
   }

   /**
    * @param Exclude to set 
    */
   public void setExclude( String Exclude )
   {
      this.Exclude = Exclude;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the Recursive
    */
   public String getRecursive( )
   {
      return Recursive;
   }

   /**
    * @param Recursive to set 
    */
   public void setRecursive( String Recursive )
   {
      this.Recursive = Recursive;
   }

   /**
    * @return the AutoCreate
    */
   public String getAutoCreate( )
   {
      return AutoCreate;
   }

   /**
    * @param AutoCreate to set 
    */
   public void setAutoCreate( String AutoCreate )
   {
      this.AutoCreate = AutoCreate;
   }

   /**
    * @return the Derived
    */
   public String getDerived( )
   {
      return Derived;
   }

   /**
    * @param Derived to set 
    */
   public void setDerived( String Derived )
   {
      this.Derived = Derived;
   }

   /**
    * @return the SeqType
    */
   public String getSeqType( )
   {
      return SeqType;
   }

   /**
    * @param SeqType to set 
    */
   public void setSeqType( String SeqType )
   {
      this.SeqType = SeqType;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the ParentDeleteBehave
    */
   public String getParentDeleteBehave( )
   {
      return ParentDeleteBehave;
   }

   /**
    * @param ParentDeleteBehave to set 
    */
   public void setParentDeleteBehave( String ParentDeleteBehave )
   {
      this.ParentDeleteBehave = ParentDeleteBehave;
   }

   /**
    * @return the DupEntityInstance
    */
   public String getDupEntityInstance( )
   {
      return DupEntityInstance;
   }

   /**
    * @param DupEntityInstance to set 
    */
   public void setDupEntityInstance( String DupEntityInstance )
   {
      this.DupEntityInstance = DupEntityInstance;
   }

   /**
    * @return the DupRelationshipInstance
    */
   public String getDupRelationshipInstance( )
   {
      return DupRelationshipInstance;
   }

   /**
    * @param DupRelationshipInstance to set 
    */
   public void setDupRelationshipInstance( String DupRelationshipInstance )
   {
      this.DupRelationshipInstance = DupRelationshipInstance;
   }

   /**
    * @return the RelLinkIndicator
    */
   public String getRelLinkIndicator( )
   {
      return RelLinkIndicator;
   }

   /**
    * @param RelLinkIndicator to set 
    */
   public void setRelLinkIndicator( String RelLinkIndicator )
   {
      this.RelLinkIndicator = RelLinkIndicator;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Abstract
    */
   public String getAbstract( )
   {
      return Abstract;
   }

   /**
    * @param Abstract to set 
    */
   public void setAbstract( String Abstract )
   {
      this.Abstract = Abstract;
   }

   /**
    * @return the XML_Name
    */
   public String getXML_Name( )
   {
      return XML_Name;
   }

   /**
    * @param XML_Name to set 
    */
   public void setXML_Name( String XML_Name )
   {
      this.XML_Name = XML_Name;
   }

   /**
    * @return the LazyLoadFlag
    */
   public String getLazyLoadFlag( )
   {
      return LazyLoadFlag;
   }

   /**
    * @param LazyLoadFlag to set 
    */
   public void setLazyLoadFlag( String LazyLoadFlag )
   {
      this.LazyLoadFlag = LazyLoadFlag;
   }

   /**
    * @return the ReportDisplayFlag
    */
   public String getReportDisplayFlag( )
   {
      return ReportDisplayFlag;
   }

   /**
    * @param ReportDisplayFlag to set 
    */
   public void setReportDisplayFlag( String ReportDisplayFlag )
   {
      this.ReportDisplayFlag = ReportDisplayFlag;
   }

   public int loadWndCaptionMapRelatedEntityEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      IndentName = cursor.getStringFromAttribute( "IndentName" );  if ( IndentName == null ) IndentName = "";
      CreateConstraint = cursor.getStringFromAttribute( "CreateConstraint" );  if ( CreateConstraint == null ) CreateConstraint = "";
      DeleteConstraint = cursor.getStringFromAttribute( "DeleteConstraint" );  if ( DeleteConstraint == null ) DeleteConstraint = "";
      IncludeConstraint = cursor.getStringFromAttribute( "IncludeConstraint" );  if ( IncludeConstraint == null ) IncludeConstraint = "";
      ExcludeConstraint = cursor.getStringFromAttribute( "ExcludeConstraint" );  if ( ExcludeConstraint == null ) ExcludeConstraint = "";
      AcceptConstraint = cursor.getStringFromAttribute( "AcceptConstraint" );  if ( AcceptConstraint == null ) AcceptConstraint = "";
      CancelConstraint = cursor.getStringFromAttribute( "CancelConstraint" );  if ( CancelConstraint == null ) CancelConstraint = "";
      SeqNo = cursor.getIntegerFromAttribute( "SeqNo" );  if ( SeqNo == null ) SeqNo = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      MultipleChildLimit = cursor.getIntegerFromAttribute( "MultipleChildLimit" );  if ( MultipleChildLimit == null ) MultipleChildLimit = 0;
      IndentLvl = cursor.getIntegerFromAttribute( "IndentLvl" );  if ( IndentLvl == null ) IndentLvl = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Create = cursor.getStringFromAttribute( "Create" );  if ( Create == null ) Create = "";
      Delete = cursor.getStringFromAttribute( "Delete" );  if ( Delete == null ) Delete = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      Include = cursor.getStringFromAttribute( "Include" );  if ( Include == null ) Include = "";
      InclSrc = cursor.getStringFromAttribute( "InclSrc" );  if ( InclSrc == null ) InclSrc = "";
      Exclude = cursor.getStringFromAttribute( "Exclude" );  if ( Exclude == null ) Exclude = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      Recursive = cursor.getStringFromAttribute( "Recursive" );  if ( Recursive == null ) Recursive = "";
      AutoCreate = cursor.getStringFromAttribute( "AutoCreate" );  if ( AutoCreate == null ) AutoCreate = "";
      Derived = cursor.getStringFromAttribute( "Derived" );  if ( Derived == null ) Derived = "";
      SeqType = cursor.getStringFromAttribute( "SeqType" );  if ( SeqType == null ) SeqType = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      ParentDeleteBehave = cursor.getStringFromAttribute( "ParentDeleteBehave" );  if ( ParentDeleteBehave == null ) ParentDeleteBehave = "";
      DupEntityInstance = cursor.getStringFromAttribute( "DupEntityInstance" );  if ( DupEntityInstance == null ) DupEntityInstance = "";
      DupRelationshipInstance = cursor.getStringFromAttribute( "DupRelationshipInstance" );  if ( DupRelationshipInstance == null ) DupRelationshipInstance = "";
      RelLinkIndicator = cursor.getStringFromAttribute( "RelLinkIndicator" );  if ( RelLinkIndicator == null ) RelLinkIndicator = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Abstract = cursor.getStringFromAttribute( "Abstract" );  if ( Abstract == null ) Abstract = "";
      XML_Name = cursor.getStringFromAttribute( "XML_Name" );  if ( XML_Name == null ) XML_Name = "";
      LazyLoadFlag = cursor.getStringFromAttribute( "LazyLoadFlag" );  if ( LazyLoadFlag == null ) LazyLoadFlag = "";
      ReportDisplayFlag = cursor.getStringFromAttribute( "ReportDisplayFlag" );  if ( ReportDisplayFlag == null ) ReportDisplayFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndCaptionMapER_AttributeImpl implements WndCaptionMapER_Attribute
{
   protected String  Name;
   protected String  CaseSens;
   protected String  TE_ColumnName;
   protected String  TE_ForeignKeyName;
   protected String  Work;
   protected String  DerivedExpression;
   protected Integer ZKey;
   protected Integer Lth;
   protected String  Key;
   protected String  NotNull;
   protected String  Desc;
   protected String  PromptPaintLit;
   protected Integer PromptPaintLth;
   protected String  ListPaintLit;
   protected Integer ListPaintLth;
   protected String  ADW_Position;
   protected Blob    DerivedExpressionXPG;
   protected Integer Sequence;
   protected Integer SAP_Attribute;
   protected String  XML_SimpleName;
   protected String  XML_NameExternal;


   // ctor
   protected WndCaptionMapER_AttributeImpl( EntityCursor cursor )
   {
      loadWndCaptionMapER_AttributeEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the CaseSens
    */
   public String getCaseSens( )
   {
      return CaseSens;
   }

   /**
    * @param CaseSens to set 
    */
   public void setCaseSens( String CaseSens )
   {
      this.CaseSens = CaseSens;
   }

   /**
    * @return the TE_ColumnName
    */
   public String getTE_ColumnName( )
   {
      return TE_ColumnName;
   }

   /**
    * @param TE_ColumnName to set 
    */
   public void setTE_ColumnName( String TE_ColumnName )
   {
      this.TE_ColumnName = TE_ColumnName;
   }

   /**
    * @return the TE_ForeignKeyName
    */
   public String getTE_ForeignKeyName( )
   {
      return TE_ForeignKeyName;
   }

   /**
    * @param TE_ForeignKeyName to set 
    */
   public void setTE_ForeignKeyName( String TE_ForeignKeyName )
   {
      this.TE_ForeignKeyName = TE_ForeignKeyName;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the DerivedExpression
    */
   public String getDerivedExpression( )
   {
      return DerivedExpression;
   }

   /**
    * @param DerivedExpression to set 
    */
   public void setDerivedExpression( String DerivedExpression )
   {
      this.DerivedExpression = DerivedExpression;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Lth
    */
   public Integer getLth( )
   {
      return Lth;
   }

   /**
    * @param Lth to set 
    */
   public void setLth( Integer Lth )
   {
      this.Lth = Lth;
   }

   /**
    * @return the Key
    */
   public String getKey( )
   {
      return Key;
   }

   /**
    * @param Key to set 
    */
   public void setKey( String Key )
   {
      this.Key = Key;
   }

   /**
    * @return the NotNull
    */
   public String getNotNull( )
   {
      return NotNull;
   }

   /**
    * @param NotNull to set 
    */
   public void setNotNull( String NotNull )
   {
      this.NotNull = NotNull;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the PromptPaintLit
    */
   public String getPromptPaintLit( )
   {
      return PromptPaintLit;
   }

   /**
    * @param PromptPaintLit to set 
    */
   public void setPromptPaintLit( String PromptPaintLit )
   {
      this.PromptPaintLit = PromptPaintLit;
   }

   /**
    * @return the PromptPaintLth
    */
   public Integer getPromptPaintLth( )
   {
      return PromptPaintLth;
   }

   /**
    * @param PromptPaintLth to set 
    */
   public void setPromptPaintLth( Integer PromptPaintLth )
   {
      this.PromptPaintLth = PromptPaintLth;
   }

   /**
    * @return the ListPaintLit
    */
   public String getListPaintLit( )
   {
      return ListPaintLit;
   }

   /**
    * @param ListPaintLit to set 
    */
   public void setListPaintLit( String ListPaintLit )
   {
      this.ListPaintLit = ListPaintLit;
   }

   /**
    * @return the ListPaintLth
    */
   public Integer getListPaintLth( )
   {
      return ListPaintLth;
   }

   /**
    * @param ListPaintLth to set 
    */
   public void setListPaintLth( Integer ListPaintLth )
   {
      this.ListPaintLth = ListPaintLth;
   }

   /**
    * @return the ADW_Position
    */
   public String getADW_Position( )
   {
      return ADW_Position;
   }

   /**
    * @param ADW_Position to set 
    */
   public void setADW_Position( String ADW_Position )
   {
      this.ADW_Position = ADW_Position;
   }

   /**
    * @return the DerivedExpressionXPG
    */
   public Blob getDerivedExpressionXPG( )
   {
      return DerivedExpressionXPG;
   }

   /**
    * @param DerivedExpressionXPG to set 
    */
   public void setDerivedExpressionXPG( Blob DerivedExpressionXPG )
   {
      this.DerivedExpressionXPG = DerivedExpressionXPG;
   }

   /**
    * @return the Sequence
    */
   public Integer getSequence( )
   {
      return Sequence;
   }

   /**
    * @param Sequence to set 
    */
   public void setSequence( Integer Sequence )
   {
      this.Sequence = Sequence;
   }

   /**
    * @return the SAP_Attribute
    */
   public Integer getSAP_Attribute( )
   {
      return SAP_Attribute;
   }

   /**
    * @param SAP_Attribute to set 
    */
   public void setSAP_Attribute( Integer SAP_Attribute )
   {
      this.SAP_Attribute = SAP_Attribute;
   }

   /**
    * @return the XML_SimpleName
    */
   public String getXML_SimpleName( )
   {
      return XML_SimpleName;
   }

   /**
    * @param XML_SimpleName to set 
    */
   public void setXML_SimpleName( String XML_SimpleName )
   {
      this.XML_SimpleName = XML_SimpleName;
   }

   /**
    * @return the XML_NameExternal
    */
   public String getXML_NameExternal( )
   {
      return XML_NameExternal;
   }

   /**
    * @param XML_NameExternal to set 
    */
   public void setXML_NameExternal( String XML_NameExternal )
   {
      this.XML_NameExternal = XML_NameExternal;
   }

   public int loadWndCaptionMapER_AttributeEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      CaseSens = cursor.getStringFromAttribute( "CaseSens" );  if ( CaseSens == null ) CaseSens = "";
      TE_ColumnName = cursor.getStringFromAttribute( "TE_ColumnName" );  if ( TE_ColumnName == null ) TE_ColumnName = "";
      TE_ForeignKeyName = cursor.getStringFromAttribute( "TE_ForeignKeyName" );  if ( TE_ForeignKeyName == null ) TE_ForeignKeyName = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      DerivedExpression = cursor.getStringFromAttribute( "DerivedExpression" );  if ( DerivedExpression == null ) DerivedExpression = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Lth = cursor.getIntegerFromAttribute( "Lth" );  if ( Lth == null ) Lth = 0;
      Key = cursor.getStringFromAttribute( "Key" );  if ( Key == null ) Key = "";
      NotNull = cursor.getStringFromAttribute( "NotNull" );  if ( NotNull == null ) NotNull = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      PromptPaintLit = cursor.getStringFromAttribute( "PromptPaintLit" );  if ( PromptPaintLit == null ) PromptPaintLit = "";
      PromptPaintLth = cursor.getIntegerFromAttribute( "PromptPaintLth" );  if ( PromptPaintLth == null ) PromptPaintLth = 0;
      ListPaintLit = cursor.getStringFromAttribute( "ListPaintLit" );  if ( ListPaintLit == null ) ListPaintLit = "";
      ListPaintLth = cursor.getIntegerFromAttribute( "ListPaintLth" );  if ( ListPaintLth == null ) ListPaintLth = 0;
      ADW_Position = cursor.getStringFromAttribute( "ADW_Position" );  if ( ADW_Position == null ) ADW_Position = "";
      DerivedExpressionXPG = cursor.getBlobFromAttribute( "DerivedExpressionXPG" );
      Sequence = cursor.getIntegerFromAttribute( "Sequence" );  if ( Sequence == null ) Sequence = 0;
      SAP_Attribute = cursor.getIntegerFromAttribute( "SAP_Attribute" );  if ( SAP_Attribute == null ) SAP_Attribute = 0;
      XML_SimpleName = cursor.getStringFromAttribute( "XML_SimpleName" );  if ( XML_SimpleName == null ) XML_SimpleName = "";
      XML_NameExternal = cursor.getStringFromAttribute( "XML_NameExternal" );  if ( XML_NameExternal == null ) XML_NameExternal = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndCaptionMapER_DomainImpl implements WndCaptionMapER_Domain
{
   protected Integer ZKey;
   protected String  DerivedName;
   protected String  DerivedDataType;
   protected Integer DerivedMaxStringLth;
   protected Integer DerivedDecimalFormat;
   protected String  Name;
   protected String  Desc;
   protected String  DomainType;
   protected String  DataType;
   protected Integer MaxStringLth;
   protected String  ContextRestriction;
   protected Integer DecimalFormat;
   protected String  ConstraintRule;


   // ctor
   protected WndCaptionMapER_DomainImpl( EntityCursor cursor )
   {
      loadWndCaptionMapER_DomainEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DerivedName
    */
   public String getDerivedName( )
   {
      return DerivedName;
   }

   /**
    * @param DerivedName to set 
    */
   public void setDerivedName( String DerivedName )
   {
      this.DerivedName = DerivedName;
   }

   /**
    * @return the DerivedDataType
    */
   public String getDerivedDataType( )
   {
      return DerivedDataType;
   }

   /**
    * @param DerivedDataType to set 
    */
   public void setDerivedDataType( String DerivedDataType )
   {
      this.DerivedDataType = DerivedDataType;
   }

   /**
    * @return the DerivedMaxStringLth
    */
   public Integer getDerivedMaxStringLth( )
   {
      return DerivedMaxStringLth;
   }

   /**
    * @param DerivedMaxStringLth to set 
    */
   public void setDerivedMaxStringLth( Integer DerivedMaxStringLth )
   {
      this.DerivedMaxStringLth = DerivedMaxStringLth;
   }

   /**
    * @return the DerivedDecimalFormat
    */
   public Integer getDerivedDecimalFormat( )
   {
      return DerivedDecimalFormat;
   }

   /**
    * @param DerivedDecimalFormat to set 
    */
   public void setDerivedDecimalFormat( Integer DerivedDecimalFormat )
   {
      this.DerivedDecimalFormat = DerivedDecimalFormat;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the DomainType
    */
   public String getDomainType( )
   {
      return DomainType;
   }

   /**
    * @param DomainType to set 
    */
   public void setDomainType( String DomainType )
   {
      this.DomainType = DomainType;
   }

   /**
    * @return the DataType
    */
   public String getDataType( )
   {
      return DataType;
   }

   /**
    * @param DataType to set 
    */
   public void setDataType( String DataType )
   {
      this.DataType = DataType;
   }

   /**
    * @return the MaxStringLth
    */
   public Integer getMaxStringLth( )
   {
      return MaxStringLth;
   }

   /**
    * @param MaxStringLth to set 
    */
   public void setMaxStringLth( Integer MaxStringLth )
   {
      this.MaxStringLth = MaxStringLth;
   }

   /**
    * @return the ContextRestriction
    */
   public String getContextRestriction( )
   {
      return ContextRestriction;
   }

   /**
    * @param ContextRestriction to set 
    */
   public void setContextRestriction( String ContextRestriction )
   {
      this.ContextRestriction = ContextRestriction;
   }

   /**
    * @return the DecimalFormat
    */
   public Integer getDecimalFormat( )
   {
      return DecimalFormat;
   }

   /**
    * @param DecimalFormat to set 
    */
   public void setDecimalFormat( Integer DecimalFormat )
   {
      this.DecimalFormat = DecimalFormat;
   }

   /**
    * @return the ConstraintRule
    */
   public String getConstraintRule( )
   {
      return ConstraintRule;
   }

   /**
    * @param ConstraintRule to set 
    */
   public void setConstraintRule( String ConstraintRule )
   {
      this.ConstraintRule = ConstraintRule;
   }

   public int loadWndCaptionMapER_DomainEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DerivedName = cursor.getStringFromAttribute( "DerivedName" );  if ( DerivedName == null ) DerivedName = "";
      DerivedDataType = cursor.getStringFromAttribute( "DerivedDataType" );  if ( DerivedDataType == null ) DerivedDataType = "";
      DerivedMaxStringLth = cursor.getIntegerFromAttribute( "DerivedMaxStringLth" );  if ( DerivedMaxStringLth == null ) DerivedMaxStringLth = 0;
      DerivedDecimalFormat = cursor.getIntegerFromAttribute( "DerivedDecimalFormat" );  if ( DerivedDecimalFormat == null ) DerivedDecimalFormat = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      DomainType = cursor.getStringFromAttribute( "DomainType" );  if ( DomainType == null ) DomainType = "";
      DataType = cursor.getStringFromAttribute( "DataType" );  if ( DataType == null ) DataType = "";
      MaxStringLth = cursor.getIntegerFromAttribute( "MaxStringLth" );  if ( MaxStringLth == null ) MaxStringLth = 0;
      ContextRestriction = cursor.getStringFromAttribute( "ContextRestriction" );  if ( ContextRestriction == null ) ContextRestriction = "";
      DecimalFormat = cursor.getIntegerFromAttribute( "DecimalFormat" );  if ( DecimalFormat == null ) DecimalFormat = 0;
      ConstraintRule = cursor.getStringFromAttribute( "ConstraintRule" );  if ( ConstraintRule == null ) ConstraintRule = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndCaptionMapContextImpl implements WndCaptionMapContext
{
   protected Integer ZKey;
   protected String  DerivedName;
   protected String  Desc;
   protected String  Name;
   protected Integer DecimalFormat;
   protected String  EditString;
   protected String  IsDefault;
   protected String  DIL_Text;


   // ctor
   protected WndCaptionMapContextImpl( EntityCursor cursor )
   {
      loadWndCaptionMapContextEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DerivedName
    */
   public String getDerivedName( )
   {
      return DerivedName;
   }

   /**
    * @param DerivedName to set 
    */
   public void setDerivedName( String DerivedName )
   {
      this.DerivedName = DerivedName;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the DecimalFormat
    */
   public Integer getDecimalFormat( )
   {
      return DecimalFormat;
   }

   /**
    * @param DecimalFormat to set 
    */
   public void setDecimalFormat( Integer DecimalFormat )
   {
      this.DecimalFormat = DecimalFormat;
   }

   /**
    * @return the EditString
    */
   public String getEditString( )
   {
      return EditString;
   }

   /**
    * @param EditString to set 
    */
   public void setEditString( String EditString )
   {
      this.EditString = EditString;
   }

   /**
    * @return the IsDefault
    */
   public String getIsDefault( )
   {
      return IsDefault;
   }

   /**
    * @param IsDefault to set 
    */
   public void setIsDefault( String IsDefault )
   {
      this.IsDefault = IsDefault;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   public int loadWndCaptionMapContextEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DerivedName = cursor.getStringFromAttribute( "DerivedName" );  if ( DerivedName == null ) DerivedName = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      DecimalFormat = cursor.getIntegerFromAttribute( "DecimalFormat" );  if ( DecimalFormat == null ) DecimalFormat = 0;
      EditString = cursor.getStringFromAttribute( "EditString" );  if ( EditString == null ) EditString = "";
      IsDefault = cursor.getStringFromAttribute( "IsDefault" );  if ( IsDefault == null ) IsDefault = "";
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndCaptionMapViewImpl implements WndCaptionMapView
{
   protected Integer ZKey;
   protected String  Name;
   protected String  Desc;
   protected Integer Level;
   protected String  IsDrivingViewForReportFlag;


   // ctor
   protected WndCaptionMapViewImpl( EntityCursor cursor )
   {
      loadWndCaptionMapViewEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Level
    */
   public Integer getLevel( )
   {
      return Level;
   }

   /**
    * @param Level to set 
    */
   public void setLevel( Integer Level )
   {
      this.Level = Level;
   }

   /**
    * @return the IsDrivingViewForReportFlag
    */
   public String getIsDrivingViewForReportFlag( )
   {
      return IsDrivingViewForReportFlag;
   }

   /**
    * @param IsDrivingViewForReportFlag to set 
    */
   public void setIsDrivingViewForReportFlag( String IsDrivingViewForReportFlag )
   {
      this.IsDrivingViewForReportFlag = IsDrivingViewForReportFlag;
   }

   public int loadWndCaptionMapViewEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Level = cursor.getIntegerFromAttribute( "Level" );  if ( Level == null ) Level = 0;
      IsDrivingViewForReportFlag = cursor.getStringFromAttribute( "IsDrivingViewForReportFlag" );  if ( IsDrivingViewForReportFlag == null ) IsDrivingViewForReportFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WndStyleImpl implements WndStyle
{
   protected String  Tag;
   protected Integer ZKey;
   protected Integer Style;
   protected String  Desc;
   protected Integer StyleEx;


   // ctor
   protected WndStyleImpl( EntityCursor cursor )
   {
      loadWndStyleEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Style
    */
   public Integer getStyle( )
   {
      return Style;
   }

   /**
    * @param Style to set 
    */
   public void setStyle( Integer Style )
   {
      this.Style = Style;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the StyleEx
    */
   public Integer getStyleEx( )
   {
      return StyleEx;
   }

   /**
    * @param StyleEx to set 
    */
   public void setStyleEx( Integer StyleEx )
   {
      this.StyleEx = StyleEx;
   }

   public int loadWndStyleEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Style = cursor.getIntegerFromAttribute( "Style" );  if ( Style == null ) Style = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      StyleEx = cursor.getIntegerFromAttribute( "StyleEx" );  if ( StyleEx == null ) StyleEx = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class HotkeyImpl implements Hotkey
{
   protected String  Tag;
   protected Integer ZKey;
   protected Blob    KeyCombo;
   protected String  Title;
   protected Integer Mode;
   protected Integer VKey;


   // ctor
   protected HotkeyImpl( EntityCursor cursor )
   {
      loadHotkeyEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the KeyCombo
    */
   public Blob getKeyCombo( )
   {
      return KeyCombo;
   }

   /**
    * @param KeyCombo to set 
    */
   public void setKeyCombo( Blob KeyCombo )
   {
      this.KeyCombo = KeyCombo;
   }

   /**
    * @return the Title
    */
   public String getTitle( )
   {
      return Title;
   }

   /**
    * @param Title to set 
    */
   public void setTitle( String Title )
   {
      this.Title = Title;
   }

   /**
    * @return the Mode
    */
   public Integer getMode( )
   {
      return Mode;
   }

   /**
    * @param Mode to set 
    */
   public void setMode( Integer Mode )
   {
      this.Mode = Mode;
   }

   /**
    * @return the VKey
    */
   public Integer getVKey( )
   {
      return VKey;
   }

   /**
    * @param VKey to set 
    */
   public void setVKey( Integer VKey )
   {
      this.VKey = VKey;
   }

   public int loadHotkeyEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      KeyCombo = cursor.getBlobFromAttribute( "KeyCombo" );
      Title = cursor.getStringFromAttribute( "Title" );  if ( Title == null ) Title = "";
      Mode = cursor.getIntegerFromAttribute( "Mode" );  if ( Mode == null ) Mode = 0;
      VKey = cursor.getIntegerFromAttribute( "VKey" );  if ( VKey == null ) VKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class HotActImpl implements HotAct
{
   protected String  Tag;
   protected String  ActionTypeAssociatedText;
   protected Integer SB_SubAction;
   protected Integer SB_NextPrev;
   protected Integer SB_DeleteNull;
   protected Integer SB_ActionDisabling;
   protected String  NoMap;
   protected Integer Type;
   protected String  TypeData;
   protected Integer ZKey;
   protected String  DialogName;
   protected String  WindowName;
   protected Integer OperCtrl;
   protected String  DLL;
   protected String  WebJavaScript;
   protected String  PopupMenuName;
   protected String  WebJavaScriptLocation;


   // ctor
   protected HotActImpl( EntityCursor cursor )
   {
      loadHotActEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ActionTypeAssociatedText
    */
   public String getActionTypeAssociatedText( )
   {
      return ActionTypeAssociatedText;
   }

   /**
    * @param ActionTypeAssociatedText to set 
    */
   public void setActionTypeAssociatedText( String ActionTypeAssociatedText )
   {
      this.ActionTypeAssociatedText = ActionTypeAssociatedText;
   }

   /**
    * @return the SB_SubAction
    */
   public Integer getSB_SubAction( )
   {
      return SB_SubAction;
   }

   /**
    * @param SB_SubAction to set 
    */
   public void setSB_SubAction( Integer SB_SubAction )
   {
      this.SB_SubAction = SB_SubAction;
   }

   /**
    * @return the SB_NextPrev
    */
   public Integer getSB_NextPrev( )
   {
      return SB_NextPrev;
   }

   /**
    * @param SB_NextPrev to set 
    */
   public void setSB_NextPrev( Integer SB_NextPrev )
   {
      this.SB_NextPrev = SB_NextPrev;
   }

   /**
    * @return the SB_DeleteNull
    */
   public Integer getSB_DeleteNull( )
   {
      return SB_DeleteNull;
   }

   /**
    * @param SB_DeleteNull to set 
    */
   public void setSB_DeleteNull( Integer SB_DeleteNull )
   {
      this.SB_DeleteNull = SB_DeleteNull;
   }

   /**
    * @return the SB_ActionDisabling
    */
   public Integer getSB_ActionDisabling( )
   {
      return SB_ActionDisabling;
   }

   /**
    * @param SB_ActionDisabling to set 
    */
   public void setSB_ActionDisabling( Integer SB_ActionDisabling )
   {
      this.SB_ActionDisabling = SB_ActionDisabling;
   }

   /**
    * @return the NoMap
    */
   public String getNoMap( )
   {
      return NoMap;
   }

   /**
    * @param NoMap to set 
    */
   public void setNoMap( String NoMap )
   {
      this.NoMap = NoMap;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the TypeData
    */
   public String getTypeData( )
   {
      return TypeData;
   }

   /**
    * @param TypeData to set 
    */
   public void setTypeData( String TypeData )
   {
      this.TypeData = TypeData;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DialogName
    */
   public String getDialogName( )
   {
      return DialogName;
   }

   /**
    * @param DialogName to set 
    */
   public void setDialogName( String DialogName )
   {
      this.DialogName = DialogName;
   }

   /**
    * @return the WindowName
    */
   public String getWindowName( )
   {
      return WindowName;
   }

   /**
    * @param WindowName to set 
    */
   public void setWindowName( String WindowName )
   {
      this.WindowName = WindowName;
   }

   /**
    * @return the OperCtrl
    */
   public Integer getOperCtrl( )
   {
      return OperCtrl;
   }

   /**
    * @param OperCtrl to set 
    */
   public void setOperCtrl( Integer OperCtrl )
   {
      this.OperCtrl = OperCtrl;
   }

   /**
    * @return the DLL
    */
   public String getDLL( )
   {
      return DLL;
   }

   /**
    * @param DLL to set 
    */
   public void setDLL( String DLL )
   {
      this.DLL = DLL;
   }

   /**
    * @return the WebJavaScript
    */
   public String getWebJavaScript( )
   {
      return WebJavaScript;
   }

   /**
    * @param WebJavaScript to set 
    */
   public void setWebJavaScript( String WebJavaScript )
   {
      this.WebJavaScript = WebJavaScript;
   }

   /**
    * @return the PopupMenuName
    */
   public String getPopupMenuName( )
   {
      return PopupMenuName;
   }

   /**
    * @param PopupMenuName to set 
    */
   public void setPopupMenuName( String PopupMenuName )
   {
      this.PopupMenuName = PopupMenuName;
   }

   /**
    * @return the WebJavaScriptLocation
    */
   public String getWebJavaScriptLocation( )
   {
      return WebJavaScriptLocation;
   }

   /**
    * @param WebJavaScriptLocation to set 
    */
   public void setWebJavaScriptLocation( String WebJavaScriptLocation )
   {
      this.WebJavaScriptLocation = WebJavaScriptLocation;
   }

   public int loadHotActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ActionTypeAssociatedText = cursor.getStringFromAttribute( "ActionTypeAssociatedText" );  if ( ActionTypeAssociatedText == null ) ActionTypeAssociatedText = "";
      SB_SubAction = cursor.getIntegerFromAttribute( "SB_SubAction" );  if ( SB_SubAction == null ) SB_SubAction = 0;
      SB_NextPrev = cursor.getIntegerFromAttribute( "SB_NextPrev" );  if ( SB_NextPrev == null ) SB_NextPrev = 0;
      SB_DeleteNull = cursor.getIntegerFromAttribute( "SB_DeleteNull" );  if ( SB_DeleteNull == null ) SB_DeleteNull = 0;
      SB_ActionDisabling = cursor.getIntegerFromAttribute( "SB_ActionDisabling" );  if ( SB_ActionDisabling == null ) SB_ActionDisabling = 0;
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      TypeData = cursor.getStringFromAttribute( "TypeData" );  if ( TypeData == null ) TypeData = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DialogName = cursor.getStringFromAttribute( "DialogName" );  if ( DialogName == null ) DialogName = "";
      WindowName = cursor.getStringFromAttribute( "WindowName" );  if ( WindowName == null ) WindowName = "";
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      WebJavaScript = cursor.getStringFromAttribute( "WebJavaScript" );  if ( WebJavaScript == null ) WebJavaScript = "";
      PopupMenuName = cursor.getStringFromAttribute( "PopupMenuName" );  if ( PopupMenuName == null ) PopupMenuName = "";
      WebJavaScriptLocation = cursor.getStringFromAttribute( "WebJavaScriptLocation" );  if ( WebJavaScriptLocation == null ) WebJavaScriptLocation = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class CaptionNLS_TextImpl implements CaptionNLS_Text
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected CaptionNLS_TextImpl( EntityCursor cursor )
   {
      loadCaptionNLS_TextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadCaptionNLS_TextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ReusableSideWindowImpl implements ReusableSideWindow
{
   protected String  Tag;
   protected Integer ZKey;
   protected Integer Subtype;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected String  DfltButton;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected ReusableSideWindowImpl( EntityCursor cursor )
   {
      loadReusableSideWindowEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadReusableSideWindowEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ReusableSideDialogImpl implements ReusableSideDialog
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  DLL_Name;
   protected String  Desc;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;
   protected String  LastSyncDate;


   // ctor
   protected ReusableSideDialogImpl( EntityCursor cursor )
   {
      loadReusableSideDialogEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DLL_Name
    */
   public String getDLL_Name( )
   {
      return DLL_Name;
   }

   /**
    * @param DLL_Name to set 
    */
   public void setDLL_Name( String DLL_Name )
   {
      this.DLL_Name = DLL_Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   public int loadReusableSideDialogEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DLL_Name = cursor.getStringFromAttribute( "DLL_Name" );  if ( DLL_Name == null ) DLL_Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ReusableMainWindowImpl implements ReusableMainWindow
{
   protected String  Tag;
   protected Integer ZKey;
   protected Integer Subtype;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected String  DfltButton;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected ReusableMainWindowImpl( EntityCursor cursor )
   {
      loadReusableMainWindowEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadReusableMainWindowEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ReusableMainDialogImpl implements ReusableMainDialog
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  DLL_Name;
   protected String  Desc;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;
   protected String  LastSyncDate;


   // ctor
   protected ReusableMainDialogImpl( EntityCursor cursor )
   {
      loadReusableMainDialogEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DLL_Name
    */
   public String getDLL_Name( )
   {
      return DLL_Name;
   }

   /**
    * @param DLL_Name to set 
    */
   public void setDLL_Name( String DLL_Name )
   {
      this.DLL_Name = DLL_Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   public int loadReusableMainDialogEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DLL_Name = cursor.getStringFromAttribute( "DLL_Name" );  if ( DLL_Name == null ) DLL_Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ReusableActionWindowImpl implements ReusableActionWindow
{
   protected String  Tag;
   protected Integer ZKey;
   protected Integer Subtype;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected String  DfltButton;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected ReusableActionWindowImpl( EntityCursor cursor )
   {
      loadReusableActionWindowEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadReusableActionWindowEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ReusableActionDialogImpl implements ReusableActionDialog
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  DLL_Name;
   protected String  Desc;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;
   protected String  LastSyncDate;


   // ctor
   protected ReusableActionDialogImpl( EntityCursor cursor )
   {
      loadReusableActionDialogEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DLL_Name
    */
   public String getDLL_Name( )
   {
      return DLL_Name;
   }

   /**
    * @param DLL_Name to set 
    */
   public void setDLL_Name( String DLL_Name )
   {
      this.DLL_Name = DLL_Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   public int loadReusableActionDialogEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DLL_Name = cursor.getStringFromAttribute( "DLL_Name" );  if ( DLL_Name == null ) DLL_Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ViewObjRefImpl implements ViewObjRef
{
   protected Integer ZKey;
   protected String  LastSyncDate;
   protected String  Name;
   protected String  Desc;
   protected Integer Level;
   protected String  IsDrivingViewForReportFlag;
   protected String  wWindowUseFlag;


   // ctor
   protected ViewObjRefImpl( EntityCursor cursor )
   {
      loadViewObjRefEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Level
    */
   public Integer getLevel( )
   {
      return Level;
   }

   /**
    * @param Level to set 
    */
   public void setLevel( Integer Level )
   {
      this.Level = Level;
   }

   /**
    * @return the IsDrivingViewForReportFlag
    */
   public String getIsDrivingViewForReportFlag( )
   {
      return IsDrivingViewForReportFlag;
   }

   /**
    * @param IsDrivingViewForReportFlag to set 
    */
   public void setIsDrivingViewForReportFlag( String IsDrivingViewForReportFlag )
   {
      this.IsDrivingViewForReportFlag = IsDrivingViewForReportFlag;
   }

   /**
    * @return the wWindowUseFlag
    */
   public String getwWindowUseFlag( )
   {
      return wWindowUseFlag;
   }

   /**
    * @param wWindowUseFlag to set 
    */
   public void setwWindowUseFlag( String wWindowUseFlag )
   {
      this.wWindowUseFlag = wWindowUseFlag;
   }

   public int loadViewObjRefEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Level = cursor.getIntegerFromAttribute( "Level" );  if ( Level == null ) Level = 0;
      IsDrivingViewForReportFlag = cursor.getStringFromAttribute( "IsDrivingViewForReportFlag" );  if ( IsDrivingViewForReportFlag == null ) IsDrivingViewForReportFlag = "";
      wWindowUseFlag = cursor.getStringFromAttribute( "wWindowUseFlag" );  if ( wWindowUseFlag == null ) wWindowUseFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class LODImpl implements LOD
{
   protected Integer ZKey;
   protected String  LastSyncDate;
   protected String  Name;
   protected String  Desc;
   protected String  DLL_Name;
   protected String  ActivateConstraint;
   protected String  ActivateServerConstraint;
   protected String  ActivateEmptyConstraint;
   protected String  CommitConstraint;
   protected String  CommitServerConstraint;
   protected String  DropOIConstraint;
   protected Integer CacheNumberPerEntity;
   protected Integer DataLocking;
   protected String  DoNotMergeFlag;


   // ctor
   protected LODImpl( EntityCursor cursor )
   {
      loadLODEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the DLL_Name
    */
   public String getDLL_Name( )
   {
      return DLL_Name;
   }

   /**
    * @param DLL_Name to set 
    */
   public void setDLL_Name( String DLL_Name )
   {
      this.DLL_Name = DLL_Name;
   }

   /**
    * @return the ActivateConstraint
    */
   public String getActivateConstraint( )
   {
      return ActivateConstraint;
   }

   /**
    * @param ActivateConstraint to set 
    */
   public void setActivateConstraint( String ActivateConstraint )
   {
      this.ActivateConstraint = ActivateConstraint;
   }

   /**
    * @return the ActivateServerConstraint
    */
   public String getActivateServerConstraint( )
   {
      return ActivateServerConstraint;
   }

   /**
    * @param ActivateServerConstraint to set 
    */
   public void setActivateServerConstraint( String ActivateServerConstraint )
   {
      this.ActivateServerConstraint = ActivateServerConstraint;
   }

   /**
    * @return the ActivateEmptyConstraint
    */
   public String getActivateEmptyConstraint( )
   {
      return ActivateEmptyConstraint;
   }

   /**
    * @param ActivateEmptyConstraint to set 
    */
   public void setActivateEmptyConstraint( String ActivateEmptyConstraint )
   {
      this.ActivateEmptyConstraint = ActivateEmptyConstraint;
   }

   /**
    * @return the CommitConstraint
    */
   public String getCommitConstraint( )
   {
      return CommitConstraint;
   }

   /**
    * @param CommitConstraint to set 
    */
   public void setCommitConstraint( String CommitConstraint )
   {
      this.CommitConstraint = CommitConstraint;
   }

   /**
    * @return the CommitServerConstraint
    */
   public String getCommitServerConstraint( )
   {
      return CommitServerConstraint;
   }

   /**
    * @param CommitServerConstraint to set 
    */
   public void setCommitServerConstraint( String CommitServerConstraint )
   {
      this.CommitServerConstraint = CommitServerConstraint;
   }

   /**
    * @return the DropOIConstraint
    */
   public String getDropOIConstraint( )
   {
      return DropOIConstraint;
   }

   /**
    * @param DropOIConstraint to set 
    */
   public void setDropOIConstraint( String DropOIConstraint )
   {
      this.DropOIConstraint = DropOIConstraint;
   }

   /**
    * @return the CacheNumberPerEntity
    */
   public Integer getCacheNumberPerEntity( )
   {
      return CacheNumberPerEntity;
   }

   /**
    * @param CacheNumberPerEntity to set 
    */
   public void setCacheNumberPerEntity( Integer CacheNumberPerEntity )
   {
      this.CacheNumberPerEntity = CacheNumberPerEntity;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the DoNotMergeFlag
    */
   public String getDoNotMergeFlag( )
   {
      return DoNotMergeFlag;
   }

   /**
    * @param DoNotMergeFlag to set 
    */
   public void setDoNotMergeFlag( String DoNotMergeFlag )
   {
      this.DoNotMergeFlag = DoNotMergeFlag;
   }

   public int loadLODEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      DLL_Name = cursor.getStringFromAttribute( "DLL_Name" );  if ( DLL_Name == null ) DLL_Name = "";
      ActivateConstraint = cursor.getStringFromAttribute( "ActivateConstraint" );  if ( ActivateConstraint == null ) ActivateConstraint = "";
      ActivateServerConstraint = cursor.getStringFromAttribute( "ActivateServerConstraint" );  if ( ActivateServerConstraint == null ) ActivateServerConstraint = "";
      ActivateEmptyConstraint = cursor.getStringFromAttribute( "ActivateEmptyConstraint" );  if ( ActivateEmptyConstraint == null ) ActivateEmptyConstraint = "";
      CommitConstraint = cursor.getStringFromAttribute( "CommitConstraint" );  if ( CommitConstraint == null ) CommitConstraint = "";
      CommitServerConstraint = cursor.getStringFromAttribute( "CommitServerConstraint" );  if ( CommitServerConstraint == null ) CommitServerConstraint = "";
      DropOIConstraint = cursor.getStringFromAttribute( "DropOIConstraint" );  if ( DropOIConstraint == null ) DropOIConstraint = "";
      CacheNumberPerEntity = cursor.getIntegerFromAttribute( "CacheNumberPerEntity" );  if ( CacheNumberPerEntity == null ) CacheNumberPerEntity = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      DoNotMergeFlag = cursor.getStringFromAttribute( "DoNotMergeFlag" );  if ( DoNotMergeFlag == null ) DoNotMergeFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class SourceFileImpl implements SourceFile
{
   protected Integer ZKey;
   protected String  Name;
   protected String  Desc;
   protected String  Extension;
   protected String  CM_Managed;
   protected String  OwnerType;
   protected String  LanguageType;
   protected String  Subdirectory;
   protected String  DomainAndGlobalOpGroupName;
   protected String  DerivedName;


   // ctor
   protected SourceFileImpl( EntityCursor cursor )
   {
      loadSourceFileEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Extension
    */
   public String getExtension( )
   {
      return Extension;
   }

   /**
    * @param Extension to set 
    */
   public void setExtension( String Extension )
   {
      this.Extension = Extension;
   }

   /**
    * @return the CM_Managed
    */
   public String getCM_Managed( )
   {
      return CM_Managed;
   }

   /**
    * @param CM_Managed to set 
    */
   public void setCM_Managed( String CM_Managed )
   {
      this.CM_Managed = CM_Managed;
   }

   /**
    * @return the OwnerType
    */
   public String getOwnerType( )
   {
      return OwnerType;
   }

   /**
    * @param OwnerType to set 
    */
   public void setOwnerType( String OwnerType )
   {
      this.OwnerType = OwnerType;
   }

   /**
    * @return the LanguageType
    */
   public String getLanguageType( )
   {
      return LanguageType;
   }

   /**
    * @param LanguageType to set 
    */
   public void setLanguageType( String LanguageType )
   {
      this.LanguageType = LanguageType;
   }

   /**
    * @return the Subdirectory
    */
   public String getSubdirectory( )
   {
      return Subdirectory;
   }

   /**
    * @param Subdirectory to set 
    */
   public void setSubdirectory( String Subdirectory )
   {
      this.Subdirectory = Subdirectory;
   }

   /**
    * @return the DomainAndGlobalOpGroupName
    */
   public String getDomainAndGlobalOpGroupName( )
   {
      return DomainAndGlobalOpGroupName;
   }

   /**
    * @param DomainAndGlobalOpGroupName to set 
    */
   public void setDomainAndGlobalOpGroupName( String DomainAndGlobalOpGroupName )
   {
      this.DomainAndGlobalOpGroupName = DomainAndGlobalOpGroupName;
   }

   /**
    * @return the DerivedName
    */
   public String getDerivedName( )
   {
      return DerivedName;
   }

   /**
    * @param DerivedName to set 
    */
   public void setDerivedName( String DerivedName )
   {
      this.DerivedName = DerivedName;
   }

   public int loadSourceFileEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Extension = cursor.getStringFromAttribute( "Extension" );  if ( Extension == null ) Extension = "";
      CM_Managed = cursor.getStringFromAttribute( "CM_Managed" );  if ( CM_Managed == null ) CM_Managed = "";
      OwnerType = cursor.getStringFromAttribute( "OwnerType" );  if ( OwnerType == null ) OwnerType = "";
      LanguageType = cursor.getStringFromAttribute( "LanguageType" );  if ( LanguageType == null ) LanguageType = "";
      Subdirectory = cursor.getStringFromAttribute( "Subdirectory" );  if ( Subdirectory == null ) Subdirectory = "";
      DomainAndGlobalOpGroupName = cursor.getStringFromAttribute( "DomainAndGlobalOpGroupName" );  if ( DomainAndGlobalOpGroupName == null ) DomainAndGlobalOpGroupName = "";
      DerivedName = cursor.getStringFromAttribute( "DerivedName" );  if ( DerivedName == null ) DerivedName = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OperationImpl implements Operation
{
   protected String  Name;
   protected Integer ZKey;
   protected String  Desc;
   protected String  Type;
   protected String  ReturnDesc;
   protected String  ReturnDataType;
   protected Integer OrdinalValue;
   protected Integer Class;
   protected String  DoNotMergeFlag;
   protected String  GenerationType;
   protected String  ThrowsException;
   protected String  ThrowsExceptionCatchCode;


   // ctor
   protected OperationImpl( EntityCursor cursor )
   {
      loadOperationEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the ReturnDesc
    */
   public String getReturnDesc( )
   {
      return ReturnDesc;
   }

   /**
    * @param ReturnDesc to set 
    */
   public void setReturnDesc( String ReturnDesc )
   {
      this.ReturnDesc = ReturnDesc;
   }

   /**
    * @return the ReturnDataType
    */
   public String getReturnDataType( )
   {
      return ReturnDataType;
   }

   /**
    * @param ReturnDataType to set 
    */
   public void setReturnDataType( String ReturnDataType )
   {
      this.ReturnDataType = ReturnDataType;
   }

   /**
    * @return the OrdinalValue
    */
   public Integer getOrdinalValue( )
   {
      return OrdinalValue;
   }

   /**
    * @param OrdinalValue to set 
    */
   public void setOrdinalValue( Integer OrdinalValue )
   {
      this.OrdinalValue = OrdinalValue;
   }

   /**
    * @return the Class
    */
   public Integer getClass( )
   {
      return Class;
   }

   /**
    * @param Class to set 
    */
   public void setClass( Integer Class )
   {
      this.Class = Class;
   }

   /**
    * @return the DoNotMergeFlag
    */
   public String getDoNotMergeFlag( )
   {
      return DoNotMergeFlag;
   }

   /**
    * @param DoNotMergeFlag to set 
    */
   public void setDoNotMergeFlag( String DoNotMergeFlag )
   {
      this.DoNotMergeFlag = DoNotMergeFlag;
   }

   /**
    * @return the GenerationType
    */
   public String getGenerationType( )
   {
      return GenerationType;
   }

   /**
    * @param GenerationType to set 
    */
   public void setGenerationType( String GenerationType )
   {
      this.GenerationType = GenerationType;
   }

   /**
    * @return the ThrowsException
    */
   public String getThrowsException( )
   {
      return ThrowsException;
   }

   /**
    * @param ThrowsException to set 
    */
   public void setThrowsException( String ThrowsException )
   {
      this.ThrowsException = ThrowsException;
   }

   /**
    * @return the ThrowsExceptionCatchCode
    */
   public String getThrowsExceptionCatchCode( )
   {
      return ThrowsExceptionCatchCode;
   }

   /**
    * @param ThrowsExceptionCatchCode to set 
    */
   public void setThrowsExceptionCatchCode( String ThrowsExceptionCatchCode )
   {
      this.ThrowsExceptionCatchCode = ThrowsExceptionCatchCode;
   }

   public int loadOperationEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      ReturnDesc = cursor.getStringFromAttribute( "ReturnDesc" );  if ( ReturnDesc == null ) ReturnDesc = "";
      ReturnDataType = cursor.getStringFromAttribute( "ReturnDataType" );  if ( ReturnDataType == null ) ReturnDataType = "";
      OrdinalValue = cursor.getIntegerFromAttribute( "OrdinalValue" );  if ( OrdinalValue == null ) OrdinalValue = 0;
      Class = cursor.getIntegerFromAttribute( "Class" );  if ( Class == null ) Class = 0;
      DoNotMergeFlag = cursor.getStringFromAttribute( "DoNotMergeFlag" );  if ( DoNotMergeFlag == null ) DoNotMergeFlag = "";
      GenerationType = cursor.getStringFromAttribute( "GenerationType" );  if ( GenerationType == null ) GenerationType = "";
      ThrowsException = cursor.getStringFromAttribute( "ThrowsException" );  if ( ThrowsException == null ) ThrowsException = "";
      ThrowsExceptionCatchCode = cursor.getStringFromAttribute( "ThrowsExceptionCatchCode" );  if ( ThrowsExceptionCatchCode == null ) ThrowsExceptionCatchCode = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ParameterImpl implements Parameter
{
   protected String  ShortDesc;
   protected String  DataType;
   protected String  PFlag;
   protected String  UFlag;
   protected Integer ZKey;
   protected Integer SeqNo;


   // ctor
   protected ParameterImpl( EntityCursor cursor )
   {
      loadParameterEntityStructure( cursor );
   }

   /**
    * @return the ShortDesc
    */
   public String getShortDesc( )
   {
      return ShortDesc;
   }

   /**
    * @param ShortDesc to set 
    */
   public void setShortDesc( String ShortDesc )
   {
      this.ShortDesc = ShortDesc;
   }

   /**
    * @return the DataType
    */
   public String getDataType( )
   {
      return DataType;
   }

   /**
    * @param DataType to set 
    */
   public void setDataType( String DataType )
   {
      this.DataType = DataType;
   }

   /**
    * @return the PFlag
    */
   public String getPFlag( )
   {
      return PFlag;
   }

   /**
    * @param PFlag to set 
    */
   public void setPFlag( String PFlag )
   {
      this.PFlag = PFlag;
   }

   /**
    * @return the UFlag
    */
   public String getUFlag( )
   {
      return UFlag;
   }

   /**
    * @param UFlag to set 
    */
   public void setUFlag( String UFlag )
   {
      this.UFlag = UFlag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the SeqNo
    */
   public Integer getSeqNo( )
   {
      return SeqNo;
   }

   /**
    * @param SeqNo to set 
    */
   public void setSeqNo( Integer SeqNo )
   {
      this.SeqNo = SeqNo;
   }

   public int loadParameterEntityStructure( EntityCursor cursor )
   {
      ShortDesc = cursor.getStringFromAttribute( "ShortDesc" );  if ( ShortDesc == null ) ShortDesc = "";
      DataType = cursor.getStringFromAttribute( "DataType" );  if ( DataType == null ) DataType = "";
      PFlag = cursor.getStringFromAttribute( "PFlag" );  if ( PFlag == null ) PFlag = "";
      UFlag = cursor.getStringFromAttribute( "UFlag" );  if ( UFlag == null ) UFlag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      SeqNo = cursor.getIntegerFromAttribute( "SeqNo" );  if ( SeqNo == null ) SeqNo = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class DefaultReusableMainWindowImpl implements DefaultReusableMainWindow
{
   protected String  Tag;
   protected Integer ZKey;
   protected Integer Subtype;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected String  DfltButton;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected DefaultReusableMainWindowImpl( EntityCursor cursor )
   {
      loadDefaultReusableMainWindowEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadDefaultReusableMainWindowEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class DefaultReusableMainDialogImpl implements DefaultReusableMainDialog
{
   protected String  Tag;
   protected Integer ZKey;
   protected String  DLL_Name;
   protected String  Desc;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;
   protected String  LastSyncDate;


   // ctor
   protected DefaultReusableMainDialogImpl( EntityCursor cursor )
   {
      loadDefaultReusableMainDialogEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DLL_Name
    */
   public String getDLL_Name( )
   {
      return DLL_Name;
   }

   /**
    * @param DLL_Name to set 
    */
   public void setDLL_Name( String DLL_Name )
   {
      this.DLL_Name = DLL_Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   public int loadDefaultReusableMainDialogEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DLL_Name = cursor.getStringFromAttribute( "DLL_Name" );  if ( DLL_Name == null ) DLL_Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class DefaultReusableActionWindowImpl implements DefaultReusableActionWindow
{
   protected String  Tag;
   protected Integer Subtype;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected String  DfltButton;
   protected Integer ZKey;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected DefaultReusableActionWindowImpl( EntityCursor cursor )
   {
      loadDefaultReusableActionWindowEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadDefaultReusableActionWindowEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class DefaultReusableActionDialogImpl implements DefaultReusableActionDialog
{
   protected String  Tag;
   protected String  DLL_Name;
   protected Integer ZKey;
   protected String  Desc;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  LastSyncDate;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected DefaultReusableActionDialogImpl( EntityCursor cursor )
   {
      loadDefaultReusableActionDialogEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the DLL_Name
    */
   public String getDLL_Name( )
   {
      return DLL_Name;
   }

   /**
    * @param DLL_Name to set 
    */
   public void setDLL_Name( String DLL_Name )
   {
      this.DLL_Name = DLL_Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadDefaultReusableActionDialogEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      DLL_Name = cursor.getStringFromAttribute( "DLL_Name" );  if ( DLL_Name == null ) DLL_Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class Z_MetaDefImpl implements Z_MetaDef
{
   protected String  Name;
   protected Integer ZKey;
   protected Integer Type;
   protected String  LastUpdateDate;
   protected String  LastCheckInDate;
   protected String  Desc;


   // ctor
   protected Z_MetaDefImpl( EntityCursor cursor )
   {
      loadZ_MetaDefEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the LastUpdateDate
    */
   public String getLastUpdateDate( )
   {
      return LastUpdateDate;
   }

   /**
    * @param LastUpdateDate to set 
    */
   public void setLastUpdateDate( String LastUpdateDate )
   {
      this.LastUpdateDate = LastUpdateDate;
   }

   /**
    * @return the LastCheckInDate
    */
   public String getLastCheckInDate( )
   {
      return LastCheckInDate;
   }

   /**
    * @param LastCheckInDate to set 
    */
   public void setLastCheckInDate( String LastCheckInDate )
   {
      this.LastCheckInDate = LastCheckInDate;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   public int loadZ_MetaDefEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      LastUpdateDate = cursor.getStringFromAttribute( "LastUpdateDate" );  if ( LastUpdateDate == null ) LastUpdateDate = "";
      LastCheckInDate = cursor.getStringFromAttribute( "LastCheckInDate" );  if ( LastCheckInDate == null ) LastCheckInDate = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OperationListImpl implements OperationList
{
   protected String  Name;
   protected Integer ZKey;
   protected String  Desc;
   protected String  Type;
   protected String  ReturnDesc;
   protected String  ReturnDataType;
   protected Integer OrdinalValue;
   protected Integer Class;
   protected String  DoNotMergeFlag;
   protected String  GenerationType;
   protected String  ThrowsException;
   protected String  ThrowsExceptionCatchCode;


   // ctor
   protected OperationListImpl( EntityCursor cursor )
   {
      loadOperationListEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Type
    */
   public String getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( String Type )
   {
      this.Type = Type;
   }

   /**
    * @return the ReturnDesc
    */
   public String getReturnDesc( )
   {
      return ReturnDesc;
   }

   /**
    * @param ReturnDesc to set 
    */
   public void setReturnDesc( String ReturnDesc )
   {
      this.ReturnDesc = ReturnDesc;
   }

   /**
    * @return the ReturnDataType
    */
   public String getReturnDataType( )
   {
      return ReturnDataType;
   }

   /**
    * @param ReturnDataType to set 
    */
   public void setReturnDataType( String ReturnDataType )
   {
      this.ReturnDataType = ReturnDataType;
   }

   /**
    * @return the OrdinalValue
    */
   public Integer getOrdinalValue( )
   {
      return OrdinalValue;
   }

   /**
    * @param OrdinalValue to set 
    */
   public void setOrdinalValue( Integer OrdinalValue )
   {
      this.OrdinalValue = OrdinalValue;
   }

   /**
    * @return the Class
    */
   public Integer getClass( )
   {
      return Class;
   }

   /**
    * @param Class to set 
    */
   public void setClass( Integer Class )
   {
      this.Class = Class;
   }

   /**
    * @return the DoNotMergeFlag
    */
   public String getDoNotMergeFlag( )
   {
      return DoNotMergeFlag;
   }

   /**
    * @param DoNotMergeFlag to set 
    */
   public void setDoNotMergeFlag( String DoNotMergeFlag )
   {
      this.DoNotMergeFlag = DoNotMergeFlag;
   }

   /**
    * @return the GenerationType
    */
   public String getGenerationType( )
   {
      return GenerationType;
   }

   /**
    * @param GenerationType to set 
    */
   public void setGenerationType( String GenerationType )
   {
      this.GenerationType = GenerationType;
   }

   /**
    * @return the ThrowsException
    */
   public String getThrowsException( )
   {
      return ThrowsException;
   }

   /**
    * @param ThrowsException to set 
    */
   public void setThrowsException( String ThrowsException )
   {
      this.ThrowsException = ThrowsException;
   }

   /**
    * @return the ThrowsExceptionCatchCode
    */
   public String getThrowsExceptionCatchCode( )
   {
      return ThrowsExceptionCatchCode;
   }

   /**
    * @param ThrowsExceptionCatchCode to set 
    */
   public void setThrowsExceptionCatchCode( String ThrowsExceptionCatchCode )
   {
      this.ThrowsExceptionCatchCode = ThrowsExceptionCatchCode;
   }

   public int loadOperationListEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";
      ReturnDesc = cursor.getStringFromAttribute( "ReturnDesc" );  if ( ReturnDesc == null ) ReturnDesc = "";
      ReturnDataType = cursor.getStringFromAttribute( "ReturnDataType" );  if ( ReturnDataType == null ) ReturnDataType = "";
      OrdinalValue = cursor.getIntegerFromAttribute( "OrdinalValue" );  if ( OrdinalValue == null ) OrdinalValue = 0;
      Class = cursor.getIntegerFromAttribute( "Class" );  if ( Class == null ) Class = 0;
      DoNotMergeFlag = cursor.getStringFromAttribute( "DoNotMergeFlag" );  if ( DoNotMergeFlag == null ) DoNotMergeFlag = "";
      GenerationType = cursor.getStringFromAttribute( "GenerationType" );  if ( GenerationType == null ) GenerationType = "";
      ThrowsException = cursor.getStringFromAttribute( "ThrowsException" );  if ( ThrowsException == null ) ThrowsException = "";
      ThrowsExceptionCatchCode = cursor.getStringFromAttribute( "ThrowsExceptionCatchCode" );  if ( ThrowsExceptionCatchCode == null ) ThrowsExceptionCatchCode = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OperSourceFileImpl implements OperSourceFile
{
   protected Integer ZKey;
   protected String  Name;
   protected String  Desc;
   protected String  Extension;
   protected String  CM_Managed;
   protected String  OwnerType;
   protected String  LanguageType;
   protected String  Subdirectory;
   protected String  DomainAndGlobalOpGroupName;


   // ctor
   protected OperSourceFileImpl( EntityCursor cursor )
   {
      loadOperSourceFileEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Extension
    */
   public String getExtension( )
   {
      return Extension;
   }

   /**
    * @param Extension to set 
    */
   public void setExtension( String Extension )
   {
      this.Extension = Extension;
   }

   /**
    * @return the CM_Managed
    */
   public String getCM_Managed( )
   {
      return CM_Managed;
   }

   /**
    * @param CM_Managed to set 
    */
   public void setCM_Managed( String CM_Managed )
   {
      this.CM_Managed = CM_Managed;
   }

   /**
    * @return the OwnerType
    */
   public String getOwnerType( )
   {
      return OwnerType;
   }

   /**
    * @param OwnerType to set 
    */
   public void setOwnerType( String OwnerType )
   {
      this.OwnerType = OwnerType;
   }

   /**
    * @return the LanguageType
    */
   public String getLanguageType( )
   {
      return LanguageType;
   }

   /**
    * @param LanguageType to set 
    */
   public void setLanguageType( String LanguageType )
   {
      this.LanguageType = LanguageType;
   }

   /**
    * @return the Subdirectory
    */
   public String getSubdirectory( )
   {
      return Subdirectory;
   }

   /**
    * @param Subdirectory to set 
    */
   public void setSubdirectory( String Subdirectory )
   {
      this.Subdirectory = Subdirectory;
   }

   /**
    * @return the DomainAndGlobalOpGroupName
    */
   public String getDomainAndGlobalOpGroupName( )
   {
      return DomainAndGlobalOpGroupName;
   }

   /**
    * @param DomainAndGlobalOpGroupName to set 
    */
   public void setDomainAndGlobalOpGroupName( String DomainAndGlobalOpGroupName )
   {
      this.DomainAndGlobalOpGroupName = DomainAndGlobalOpGroupName;
   }

   public int loadOperSourceFileEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Extension = cursor.getStringFromAttribute( "Extension" );  if ( Extension == null ) Extension = "";
      CM_Managed = cursor.getStringFromAttribute( "CM_Managed" );  if ( CM_Managed == null ) CM_Managed = "";
      OwnerType = cursor.getStringFromAttribute( "OwnerType" );  if ( OwnerType == null ) OwnerType = "";
      LanguageType = cursor.getStringFromAttribute( "LanguageType" );  if ( LanguageType == null ) LanguageType = "";
      Subdirectory = cursor.getStringFromAttribute( "Subdirectory" );  if ( Subdirectory == null ) Subdirectory = "";
      DomainAndGlobalOpGroupName = cursor.getStringFromAttribute( "DomainAndGlobalOpGroupName" );  if ( DomainAndGlobalOpGroupName == null ) DomainAndGlobalOpGroupName = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OperationActionImpl implements OperationAction
{
   protected String  Tag;
   protected Integer SB_SubAction;
   protected Integer SB_NextPrev;
   protected Integer SB_DeleteNull;
   protected Integer SB_ActionDisabling;
   protected String  NoMap;
   protected Integer Type;
   protected String  TypeData;
   protected Integer ZKey;
   protected String  DialogName;
   protected String  WindowName;
   protected Integer OperCtrl;
   protected String  ActionTypeAssociatedText;
   protected String  DLL;
   protected String  WebJavaScript;
   protected String  PopupMenuName;
   protected String  WebJavaScriptLocation;


   // ctor
   protected OperationActionImpl( EntityCursor cursor )
   {
      loadOperationActionEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the SB_SubAction
    */
   public Integer getSB_SubAction( )
   {
      return SB_SubAction;
   }

   /**
    * @param SB_SubAction to set 
    */
   public void setSB_SubAction( Integer SB_SubAction )
   {
      this.SB_SubAction = SB_SubAction;
   }

   /**
    * @return the SB_NextPrev
    */
   public Integer getSB_NextPrev( )
   {
      return SB_NextPrev;
   }

   /**
    * @param SB_NextPrev to set 
    */
   public void setSB_NextPrev( Integer SB_NextPrev )
   {
      this.SB_NextPrev = SB_NextPrev;
   }

   /**
    * @return the SB_DeleteNull
    */
   public Integer getSB_DeleteNull( )
   {
      return SB_DeleteNull;
   }

   /**
    * @param SB_DeleteNull to set 
    */
   public void setSB_DeleteNull( Integer SB_DeleteNull )
   {
      this.SB_DeleteNull = SB_DeleteNull;
   }

   /**
    * @return the SB_ActionDisabling
    */
   public Integer getSB_ActionDisabling( )
   {
      return SB_ActionDisabling;
   }

   /**
    * @param SB_ActionDisabling to set 
    */
   public void setSB_ActionDisabling( Integer SB_ActionDisabling )
   {
      this.SB_ActionDisabling = SB_ActionDisabling;
   }

   /**
    * @return the NoMap
    */
   public String getNoMap( )
   {
      return NoMap;
   }

   /**
    * @param NoMap to set 
    */
   public void setNoMap( String NoMap )
   {
      this.NoMap = NoMap;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the TypeData
    */
   public String getTypeData( )
   {
      return TypeData;
   }

   /**
    * @param TypeData to set 
    */
   public void setTypeData( String TypeData )
   {
      this.TypeData = TypeData;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the DialogName
    */
   public String getDialogName( )
   {
      return DialogName;
   }

   /**
    * @param DialogName to set 
    */
   public void setDialogName( String DialogName )
   {
      this.DialogName = DialogName;
   }

   /**
    * @return the WindowName
    */
   public String getWindowName( )
   {
      return WindowName;
   }

   /**
    * @param WindowName to set 
    */
   public void setWindowName( String WindowName )
   {
      this.WindowName = WindowName;
   }

   /**
    * @return the OperCtrl
    */
   public Integer getOperCtrl( )
   {
      return OperCtrl;
   }

   /**
    * @param OperCtrl to set 
    */
   public void setOperCtrl( Integer OperCtrl )
   {
      this.OperCtrl = OperCtrl;
   }

   /**
    * @return the ActionTypeAssociatedText
    */
   public String getActionTypeAssociatedText( )
   {
      return ActionTypeAssociatedText;
   }

   /**
    * @param ActionTypeAssociatedText to set 
    */
   public void setActionTypeAssociatedText( String ActionTypeAssociatedText )
   {
      this.ActionTypeAssociatedText = ActionTypeAssociatedText;
   }

   /**
    * @return the DLL
    */
   public String getDLL( )
   {
      return DLL;
   }

   /**
    * @param DLL to set 
    */
   public void setDLL( String DLL )
   {
      this.DLL = DLL;
   }

   /**
    * @return the WebJavaScript
    */
   public String getWebJavaScript( )
   {
      return WebJavaScript;
   }

   /**
    * @param WebJavaScript to set 
    */
   public void setWebJavaScript( String WebJavaScript )
   {
      this.WebJavaScript = WebJavaScript;
   }

   /**
    * @return the PopupMenuName
    */
   public String getPopupMenuName( )
   {
      return PopupMenuName;
   }

   /**
    * @param PopupMenuName to set 
    */
   public void setPopupMenuName( String PopupMenuName )
   {
      this.PopupMenuName = PopupMenuName;
   }

   /**
    * @return the WebJavaScriptLocation
    */
   public String getWebJavaScriptLocation( )
   {
      return WebJavaScriptLocation;
   }

   /**
    * @param WebJavaScriptLocation to set 
    */
   public void setWebJavaScriptLocation( String WebJavaScriptLocation )
   {
      this.WebJavaScriptLocation = WebJavaScriptLocation;
   }

   public int loadOperationActionEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      SB_SubAction = cursor.getIntegerFromAttribute( "SB_SubAction" );  if ( SB_SubAction == null ) SB_SubAction = 0;
      SB_NextPrev = cursor.getIntegerFromAttribute( "SB_NextPrev" );  if ( SB_NextPrev == null ) SB_NextPrev = 0;
      SB_DeleteNull = cursor.getIntegerFromAttribute( "SB_DeleteNull" );  if ( SB_DeleteNull == null ) SB_DeleteNull = 0;
      SB_ActionDisabling = cursor.getIntegerFromAttribute( "SB_ActionDisabling" );  if ( SB_ActionDisabling == null ) SB_ActionDisabling = 0;
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      TypeData = cursor.getStringFromAttribute( "TypeData" );  if ( TypeData == null ) TypeData = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      DialogName = cursor.getStringFromAttribute( "DialogName" );  if ( DialogName == null ) DialogName = "";
      WindowName = cursor.getStringFromAttribute( "WindowName" );  if ( WindowName == null ) WindowName = "";
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      ActionTypeAssociatedText = cursor.getStringFromAttribute( "ActionTypeAssociatedText" );  if ( ActionTypeAssociatedText == null ) ActionTypeAssociatedText = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      WebJavaScript = cursor.getStringFromAttribute( "WebJavaScript" );  if ( WebJavaScript == null ) WebJavaScript = "";
      PopupMenuName = cursor.getStringFromAttribute( "PopupMenuName" );  if ( PopupMenuName == null ) PopupMenuName = "";
      WebJavaScriptLocation = cursor.getStringFromAttribute( "WebJavaScriptLocation" );  if ( WebJavaScriptLocation == null ) WebJavaScriptLocation = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class OperationActionWindowImpl implements OperationActionWindow
{
   protected String  Tag;
   protected Integer Subtype;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected String  DfltButton;
   protected Integer ZKey;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected OperationActionWindowImpl( EntityCursor cursor )
   {
      loadOperationActionWindowEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadOperationActionWindowEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class NLS_ControlImpl implements NLS_Control
{
   protected String  Tag;
   protected String  Text;
   protected Integer ZKey;
   protected Integer Type;
   protected Integer Subtype;
   protected Integer OptionFlags;
   protected Integer IdNbr;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Blob    CtrlBOI;
   protected Integer Underline;
   protected Integer SyncKey;
   protected String  DIL_Text;
   protected String  DD_TargetKey;
   protected String  DD_SourceKey;
   protected String  DD_Type;
   protected String  Placeholder;
   protected String  ReportGroupType;
   protected String  ForceHeaderPerEntity;
   protected Integer ExtendedStyle;
   protected String  GUID;
   protected Blob    Properties;
   protected Blob    LKey;
   protected String  VisibleBorder;
   protected String  CenterJustify;
   protected String  RightJustify;
   protected String  CSS_Class;
   protected String  CSS_Id;
   protected String  CSS_Font;
   protected String  CSS_Position;
   protected String  CSS_Size;
   protected String  JavaScript;
   protected String  RadioOrCheckboxValue;
   protected String  WebFileName;
   protected String  WebCtrlType;
   protected String  WebColumnSpan;
   protected String  WebWrap;
   protected Integer BorderWidth;
   protected Integer BorderStyle;
   protected Integer BorderTop;
   protected Integer BorderBottom;
   protected Integer BorderLeft;
   protected Integer BorderRight;
   protected String  TextAlignHorizontal;
   protected Integer FontSize;
   protected String  TextBold;
   protected String  TextItalic;
   protected String  TextUnderline;
   protected String  LangID;


   // ctor
   protected NLS_ControlImpl( EntityCursor cursor )
   {
      loadNLS_ControlEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the OptionFlags
    */
   public Integer getOptionFlags( )
   {
      return OptionFlags;
   }

   /**
    * @param OptionFlags to set 
    */
   public void setOptionFlags( Integer OptionFlags )
   {
      this.OptionFlags = OptionFlags;
   }

   /**
    * @return the IdNbr
    */
   public Integer getIdNbr( )
   {
      return IdNbr;
   }

   /**
    * @param IdNbr to set 
    */
   public void setIdNbr( Integer IdNbr )
   {
      this.IdNbr = IdNbr;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the CtrlBOI
    */
   public Blob getCtrlBOI( )
   {
      return CtrlBOI;
   }

   /**
    * @param CtrlBOI to set 
    */
   public void setCtrlBOI( Blob CtrlBOI )
   {
      this.CtrlBOI = CtrlBOI;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the SyncKey
    */
   public Integer getSyncKey( )
   {
      return SyncKey;
   }

   /**
    * @param SyncKey to set 
    */
   public void setSyncKey( Integer SyncKey )
   {
      this.SyncKey = SyncKey;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the DD_TargetKey
    */
   public String getDD_TargetKey( )
   {
      return DD_TargetKey;
   }

   /**
    * @param DD_TargetKey to set 
    */
   public void setDD_TargetKey( String DD_TargetKey )
   {
      this.DD_TargetKey = DD_TargetKey;
   }

   /**
    * @return the DD_SourceKey
    */
   public String getDD_SourceKey( )
   {
      return DD_SourceKey;
   }

   /**
    * @param DD_SourceKey to set 
    */
   public void setDD_SourceKey( String DD_SourceKey )
   {
      this.DD_SourceKey = DD_SourceKey;
   }

   /**
    * @return the DD_Type
    */
   public String getDD_Type( )
   {
      return DD_Type;
   }

   /**
    * @param DD_Type to set 
    */
   public void setDD_Type( String DD_Type )
   {
      this.DD_Type = DD_Type;
   }

   /**
    * @return the Placeholder
    */
   public String getPlaceholder( )
   {
      return Placeholder;
   }

   /**
    * @param Placeholder to set 
    */
   public void setPlaceholder( String Placeholder )
   {
      this.Placeholder = Placeholder;
   }

   /**
    * @return the ReportGroupType
    */
   public String getReportGroupType( )
   {
      return ReportGroupType;
   }

   /**
    * @param ReportGroupType to set 
    */
   public void setReportGroupType( String ReportGroupType )
   {
      this.ReportGroupType = ReportGroupType;
   }

   /**
    * @return the ForceHeaderPerEntity
    */
   public String getForceHeaderPerEntity( )
   {
      return ForceHeaderPerEntity;
   }

   /**
    * @param ForceHeaderPerEntity to set 
    */
   public void setForceHeaderPerEntity( String ForceHeaderPerEntity )
   {
      this.ForceHeaderPerEntity = ForceHeaderPerEntity;
   }

   /**
    * @return the ExtendedStyle
    */
   public Integer getExtendedStyle( )
   {
      return ExtendedStyle;
   }

   /**
    * @param ExtendedStyle to set 
    */
   public void setExtendedStyle( Integer ExtendedStyle )
   {
      this.ExtendedStyle = ExtendedStyle;
   }

   /**
    * @return the GUID
    */
   public String getGUID( )
   {
      return GUID;
   }

   /**
    * @param GUID to set 
    */
   public void setGUID( String GUID )
   {
      this.GUID = GUID;
   }

   /**
    * @return the Properties
    */
   public Blob getProperties( )
   {
      return Properties;
   }

   /**
    * @param Properties to set 
    */
   public void setProperties( Blob Properties )
   {
      this.Properties = Properties;
   }

   /**
    * @return the LKey
    */
   public Blob getLKey( )
   {
      return LKey;
   }

   /**
    * @param LKey to set 
    */
   public void setLKey( Blob LKey )
   {
      this.LKey = LKey;
   }

   /**
    * @return the VisibleBorder
    */
   public String getVisibleBorder( )
   {
      return VisibleBorder;
   }

   /**
    * @param VisibleBorder to set 
    */
   public void setVisibleBorder( String VisibleBorder )
   {
      this.VisibleBorder = VisibleBorder;
   }

   /**
    * @return the CenterJustify
    */
   public String getCenterJustify( )
   {
      return CenterJustify;
   }

   /**
    * @param CenterJustify to set 
    */
   public void setCenterJustify( String CenterJustify )
   {
      this.CenterJustify = CenterJustify;
   }

   /**
    * @return the RightJustify
    */
   public String getRightJustify( )
   {
      return RightJustify;
   }

   /**
    * @param RightJustify to set 
    */
   public void setRightJustify( String RightJustify )
   {
      this.RightJustify = RightJustify;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the CSS_Id
    */
   public String getCSS_Id( )
   {
      return CSS_Id;
   }

   /**
    * @param CSS_Id to set 
    */
   public void setCSS_Id( String CSS_Id )
   {
      this.CSS_Id = CSS_Id;
   }

   /**
    * @return the CSS_Font
    */
   public String getCSS_Font( )
   {
      return CSS_Font;
   }

   /**
    * @param CSS_Font to set 
    */
   public void setCSS_Font( String CSS_Font )
   {
      this.CSS_Font = CSS_Font;
   }

   /**
    * @return the CSS_Position
    */
   public String getCSS_Position( )
   {
      return CSS_Position;
   }

   /**
    * @param CSS_Position to set 
    */
   public void setCSS_Position( String CSS_Position )
   {
      this.CSS_Position = CSS_Position;
   }

   /**
    * @return the CSS_Size
    */
   public String getCSS_Size( )
   {
      return CSS_Size;
   }

   /**
    * @param CSS_Size to set 
    */
   public void setCSS_Size( String CSS_Size )
   {
      this.CSS_Size = CSS_Size;
   }

   /**
    * @return the JavaScript
    */
   public String getJavaScript( )
   {
      return JavaScript;
   }

   /**
    * @param JavaScript to set 
    */
   public void setJavaScript( String JavaScript )
   {
      this.JavaScript = JavaScript;
   }

   /**
    * @return the RadioOrCheckboxValue
    */
   public String getRadioOrCheckboxValue( )
   {
      return RadioOrCheckboxValue;
   }

   /**
    * @param RadioOrCheckboxValue to set 
    */
   public void setRadioOrCheckboxValue( String RadioOrCheckboxValue )
   {
      this.RadioOrCheckboxValue = RadioOrCheckboxValue;
   }

   /**
    * @return the WebFileName
    */
   public String getWebFileName( )
   {
      return WebFileName;
   }

   /**
    * @param WebFileName to set 
    */
   public void setWebFileName( String WebFileName )
   {
      this.WebFileName = WebFileName;
   }

   /**
    * @return the WebCtrlType
    */
   public String getWebCtrlType( )
   {
      return WebCtrlType;
   }

   /**
    * @param WebCtrlType to set 
    */
   public void setWebCtrlType( String WebCtrlType )
   {
      this.WebCtrlType = WebCtrlType;
   }

   /**
    * @return the WebColumnSpan
    */
   public String getWebColumnSpan( )
   {
      return WebColumnSpan;
   }

   /**
    * @param WebColumnSpan to set 
    */
   public void setWebColumnSpan( String WebColumnSpan )
   {
      this.WebColumnSpan = WebColumnSpan;
   }

   /**
    * @return the WebWrap
    */
   public String getWebWrap( )
   {
      return WebWrap;
   }

   /**
    * @param WebWrap to set 
    */
   public void setWebWrap( String WebWrap )
   {
      this.WebWrap = WebWrap;
   }

   /**
    * @return the BorderWidth
    */
   public Integer getBorderWidth( )
   {
      return BorderWidth;
   }

   /**
    * @param BorderWidth to set 
    */
   public void setBorderWidth( Integer BorderWidth )
   {
      this.BorderWidth = BorderWidth;
   }

   /**
    * @return the BorderStyle
    */
   public Integer getBorderStyle( )
   {
      return BorderStyle;
   }

   /**
    * @param BorderStyle to set 
    */
   public void setBorderStyle( Integer BorderStyle )
   {
      this.BorderStyle = BorderStyle;
   }

   /**
    * @return the BorderTop
    */
   public Integer getBorderTop( )
   {
      return BorderTop;
   }

   /**
    * @param BorderTop to set 
    */
   public void setBorderTop( Integer BorderTop )
   {
      this.BorderTop = BorderTop;
   }

   /**
    * @return the BorderBottom
    */
   public Integer getBorderBottom( )
   {
      return BorderBottom;
   }

   /**
    * @param BorderBottom to set 
    */
   public void setBorderBottom( Integer BorderBottom )
   {
      this.BorderBottom = BorderBottom;
   }

   /**
    * @return the BorderLeft
    */
   public Integer getBorderLeft( )
   {
      return BorderLeft;
   }

   /**
    * @param BorderLeft to set 
    */
   public void setBorderLeft( Integer BorderLeft )
   {
      this.BorderLeft = BorderLeft;
   }

   /**
    * @return the BorderRight
    */
   public Integer getBorderRight( )
   {
      return BorderRight;
   }

   /**
    * @param BorderRight to set 
    */
   public void setBorderRight( Integer BorderRight )
   {
      this.BorderRight = BorderRight;
   }

   /**
    * @return the TextAlignHorizontal
    */
   public String getTextAlignHorizontal( )
   {
      return TextAlignHorizontal;
   }

   /**
    * @param TextAlignHorizontal to set 
    */
   public void setTextAlignHorizontal( String TextAlignHorizontal )
   {
      this.TextAlignHorizontal = TextAlignHorizontal;
   }

   /**
    * @return the FontSize
    */
   public Integer getFontSize( )
   {
      return FontSize;
   }

   /**
    * @param FontSize to set 
    */
   public void setFontSize( Integer FontSize )
   {
      this.FontSize = FontSize;
   }

   /**
    * @return the TextBold
    */
   public String getTextBold( )
   {
      return TextBold;
   }

   /**
    * @param TextBold to set 
    */
   public void setTextBold( String TextBold )
   {
      this.TextBold = TextBold;
   }

   /**
    * @return the TextItalic
    */
   public String getTextItalic( )
   {
      return TextItalic;
   }

   /**
    * @param TextItalic to set 
    */
   public void setTextItalic( String TextItalic )
   {
      this.TextItalic = TextItalic;
   }

   /**
    * @return the TextUnderline
    */
   public String getTextUnderline( )
   {
      return TextUnderline;
   }

   /**
    * @param TextUnderline to set 
    */
   public void setTextUnderline( String TextUnderline )
   {
      this.TextUnderline = TextUnderline;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   public int loadNLS_ControlEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      OptionFlags = cursor.getIntegerFromAttribute( "OptionFlags" );  if ( OptionFlags == null ) OptionFlags = 0;
      IdNbr = cursor.getIntegerFromAttribute( "IdNbr" );  if ( IdNbr == null ) IdNbr = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      CtrlBOI = cursor.getBlobFromAttribute( "CtrlBOI" );
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      SyncKey = cursor.getIntegerFromAttribute( "SyncKey" );  if ( SyncKey == null ) SyncKey = 0;
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      DD_TargetKey = cursor.getStringFromAttribute( "DD_TargetKey" );  if ( DD_TargetKey == null ) DD_TargetKey = "";
      DD_SourceKey = cursor.getStringFromAttribute( "DD_SourceKey" );  if ( DD_SourceKey == null ) DD_SourceKey = "";
      DD_Type = cursor.getStringFromAttribute( "DD_Type" );  if ( DD_Type == null ) DD_Type = "";
      Placeholder = cursor.getStringFromAttribute( "Placeholder" );  if ( Placeholder == null ) Placeholder = "";
      ReportGroupType = cursor.getStringFromAttribute( "ReportGroupType" );  if ( ReportGroupType == null ) ReportGroupType = "";
      ForceHeaderPerEntity = cursor.getStringFromAttribute( "ForceHeaderPerEntity" );  if ( ForceHeaderPerEntity == null ) ForceHeaderPerEntity = "";
      ExtendedStyle = cursor.getIntegerFromAttribute( "ExtendedStyle" );  if ( ExtendedStyle == null ) ExtendedStyle = 0;
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      Properties = cursor.getBlobFromAttribute( "Properties" );
      LKey = cursor.getBlobFromAttribute( "LKey" );
      VisibleBorder = cursor.getStringFromAttribute( "VisibleBorder" );  if ( VisibleBorder == null ) VisibleBorder = "";
      CenterJustify = cursor.getStringFromAttribute( "CenterJustify" );  if ( CenterJustify == null ) CenterJustify = "";
      RightJustify = cursor.getStringFromAttribute( "RightJustify" );  if ( RightJustify == null ) RightJustify = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      CSS_Id = cursor.getStringFromAttribute( "CSS_Id" );  if ( CSS_Id == null ) CSS_Id = "";
      CSS_Font = cursor.getStringFromAttribute( "CSS_Font" );  if ( CSS_Font == null ) CSS_Font = "";
      CSS_Position = cursor.getStringFromAttribute( "CSS_Position" );  if ( CSS_Position == null ) CSS_Position = "";
      CSS_Size = cursor.getStringFromAttribute( "CSS_Size" );  if ( CSS_Size == null ) CSS_Size = "";
      JavaScript = cursor.getStringFromAttribute( "JavaScript" );  if ( JavaScript == null ) JavaScript = "";
      RadioOrCheckboxValue = cursor.getStringFromAttribute( "RadioOrCheckboxValue" );  if ( RadioOrCheckboxValue == null ) RadioOrCheckboxValue = "";
      WebFileName = cursor.getStringFromAttribute( "WebFileName" );  if ( WebFileName == null ) WebFileName = "";
      WebCtrlType = cursor.getStringFromAttribute( "WebCtrlType" );  if ( WebCtrlType == null ) WebCtrlType = "";
      WebColumnSpan = cursor.getStringFromAttribute( "WebColumnSpan" );  if ( WebColumnSpan == null ) WebColumnSpan = "";
      WebWrap = cursor.getStringFromAttribute( "WebWrap" );  if ( WebWrap == null ) WebWrap = "";
      BorderWidth = cursor.getIntegerFromAttribute( "BorderWidth" );  if ( BorderWidth == null ) BorderWidth = 0;
      BorderStyle = cursor.getIntegerFromAttribute( "BorderStyle" );  if ( BorderStyle == null ) BorderStyle = 0;
      BorderTop = cursor.getIntegerFromAttribute( "BorderTop" );  if ( BorderTop == null ) BorderTop = 0;
      BorderBottom = cursor.getIntegerFromAttribute( "BorderBottom" );  if ( BorderBottom == null ) BorderBottom = 0;
      BorderLeft = cursor.getIntegerFromAttribute( "BorderLeft" );  if ( BorderLeft == null ) BorderLeft = 0;
      BorderRight = cursor.getIntegerFromAttribute( "BorderRight" );  if ( BorderRight == null ) BorderRight = 0;
      TextAlignHorizontal = cursor.getStringFromAttribute( "TextAlignHorizontal" );  if ( TextAlignHorizontal == null ) TextAlignHorizontal = "";
      FontSize = cursor.getIntegerFromAttribute( "FontSize" );  if ( FontSize == null ) FontSize = 0;
      TextBold = cursor.getStringFromAttribute( "TextBold" );  if ( TextBold == null ) TextBold = "";
      TextItalic = cursor.getStringFromAttribute( "TextItalic" );  if ( TextItalic == null ) TextItalic = "";
      TextUnderline = cursor.getStringFromAttribute( "TextUnderline" );  if ( TextUnderline == null ) TextUnderline = "";
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class NLS_ControlTextImpl implements NLS_ControlText
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected NLS_ControlTextImpl( EntityCursor cursor )
   {
      loadNLS_ControlTextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadNLS_ControlTextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class NLS_OptionImpl implements NLS_Option
{
   protected String  Tag;
   protected String  Text;
   protected String  AccelTitle;
   protected String  CheckMarkValueOn;
   protected String  CheckMarkValueOff;
   protected String  Separator;
   protected Integer ZKey;
   protected Integer Underline;
   protected String  DIL_Text;
   protected Integer SeqNo_Menu;
   protected Integer SeqNo_Option;
   protected String  LangID;


   // ctor
   protected NLS_OptionImpl( EntityCursor cursor )
   {
      loadNLS_OptionEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the AccelTitle
    */
   public String getAccelTitle( )
   {
      return AccelTitle;
   }

   /**
    * @param AccelTitle to set 
    */
   public void setAccelTitle( String AccelTitle )
   {
      this.AccelTitle = AccelTitle;
   }

   /**
    * @return the CheckMarkValueOn
    */
   public String getCheckMarkValueOn( )
   {
      return CheckMarkValueOn;
   }

   /**
    * @param CheckMarkValueOn to set 
    */
   public void setCheckMarkValueOn( String CheckMarkValueOn )
   {
      this.CheckMarkValueOn = CheckMarkValueOn;
   }

   /**
    * @return the CheckMarkValueOff
    */
   public String getCheckMarkValueOff( )
   {
      return CheckMarkValueOff;
   }

   /**
    * @param CheckMarkValueOff to set 
    */
   public void setCheckMarkValueOff( String CheckMarkValueOff )
   {
      this.CheckMarkValueOff = CheckMarkValueOff;
   }

   /**
    * @return the Separator
    */
   public String getSeparator( )
   {
      return Separator;
   }

   /**
    * @param Separator to set 
    */
   public void setSeparator( String Separator )
   {
      this.Separator = Separator;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the SeqNo_Menu
    */
   public Integer getSeqNo_Menu( )
   {
      return SeqNo_Menu;
   }

   /**
    * @param SeqNo_Menu to set 
    */
   public void setSeqNo_Menu( Integer SeqNo_Menu )
   {
      this.SeqNo_Menu = SeqNo_Menu;
   }

   /**
    * @return the SeqNo_Option
    */
   public Integer getSeqNo_Option( )
   {
      return SeqNo_Option;
   }

   /**
    * @param SeqNo_Option to set 
    */
   public void setSeqNo_Option( Integer SeqNo_Option )
   {
      this.SeqNo_Option = SeqNo_Option;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   public int loadNLS_OptionEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      AccelTitle = cursor.getStringFromAttribute( "AccelTitle" );  if ( AccelTitle == null ) AccelTitle = "";
      CheckMarkValueOn = cursor.getStringFromAttribute( "CheckMarkValueOn" );  if ( CheckMarkValueOn == null ) CheckMarkValueOn = "";
      CheckMarkValueOff = cursor.getStringFromAttribute( "CheckMarkValueOff" );  if ( CheckMarkValueOff == null ) CheckMarkValueOff = "";
      Separator = cursor.getStringFromAttribute( "Separator" );  if ( Separator == null ) Separator = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      SeqNo_Menu = cursor.getIntegerFromAttribute( "SeqNo_Menu" );  if ( SeqNo_Menu == null ) SeqNo_Menu = 0;
      SeqNo_Option = cursor.getIntegerFromAttribute( "SeqNo_Option" );  if ( SeqNo_Option == null ) SeqNo_Option = 0;
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class NLS_OptionTextImpl implements NLS_OptionText
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected NLS_OptionTextImpl( EntityCursor cursor )
   {
      loadNLS_OptionTextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadNLS_OptionTextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class NLS_DIL_ControlImpl implements NLS_DIL_Control
{
   protected String  Tag;
   protected String  Text;
   protected Integer ZKey;
   protected Integer Type;
   protected Integer Subtype;
   protected String  DD_TargetKey;
   protected String  DD_SourceKey;
   protected Integer OptionFlags;
   protected String  DD_Type;
   protected Integer IdNbr;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Blob    CtrlBOI;
   protected Integer Underline;
   protected Integer SyncKey;
   protected String  DIL_Text;
   protected String  Placeholder;
   protected String  ReportGroupType;
   protected String  ForceHeaderPerEntity;
   protected Integer ExtendedStyle;
   protected String  GUID;
   protected Blob    Properties;
   protected Blob    LKey;
   protected String  VisibleBorder;
   protected String  CenterJustify;
   protected String  RightJustify;
   protected String  CSS_Class;
   protected String  CSS_Id;
   protected String  CSS_Font;
   protected String  CSS_Position;
   protected String  CSS_Size;
   protected String  JavaScript;
   protected String  RadioOrCheckboxValue;
   protected String  WebFileName;
   protected String  WebCtrlType;
   protected String  WebColumnSpan;
   protected String  WebWrap;
   protected Integer BorderWidth;
   protected Integer BorderStyle;
   protected Integer BorderTop;
   protected Integer BorderBottom;
   protected Integer BorderLeft;
   protected Integer BorderRight;
   protected String  TextAlignHorizontal;
   protected Integer FontSize;
   protected String  TextBold;
   protected String  TextItalic;
   protected String  TextUnderline;
   protected String  LangID;


   // ctor
   protected NLS_DIL_ControlImpl( EntityCursor cursor )
   {
      loadNLS_DIL_ControlEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Type
    */
   public Integer getType( )
   {
      return Type;
   }

   /**
    * @param Type to set 
    */
   public void setType( Integer Type )
   {
      this.Type = Type;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the DD_TargetKey
    */
   public String getDD_TargetKey( )
   {
      return DD_TargetKey;
   }

   /**
    * @param DD_TargetKey to set 
    */
   public void setDD_TargetKey( String DD_TargetKey )
   {
      this.DD_TargetKey = DD_TargetKey;
   }

   /**
    * @return the DD_SourceKey
    */
   public String getDD_SourceKey( )
   {
      return DD_SourceKey;
   }

   /**
    * @param DD_SourceKey to set 
    */
   public void setDD_SourceKey( String DD_SourceKey )
   {
      this.DD_SourceKey = DD_SourceKey;
   }

   /**
    * @return the OptionFlags
    */
   public Integer getOptionFlags( )
   {
      return OptionFlags;
   }

   /**
    * @param OptionFlags to set 
    */
   public void setOptionFlags( Integer OptionFlags )
   {
      this.OptionFlags = OptionFlags;
   }

   /**
    * @return the DD_Type
    */
   public String getDD_Type( )
   {
      return DD_Type;
   }

   /**
    * @param DD_Type to set 
    */
   public void setDD_Type( String DD_Type )
   {
      this.DD_Type = DD_Type;
   }

   /**
    * @return the IdNbr
    */
   public Integer getIdNbr( )
   {
      return IdNbr;
   }

   /**
    * @param IdNbr to set 
    */
   public void setIdNbr( Integer IdNbr )
   {
      this.IdNbr = IdNbr;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the CtrlBOI
    */
   public Blob getCtrlBOI( )
   {
      return CtrlBOI;
   }

   /**
    * @param CtrlBOI to set 
    */
   public void setCtrlBOI( Blob CtrlBOI )
   {
      this.CtrlBOI = CtrlBOI;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the SyncKey
    */
   public Integer getSyncKey( )
   {
      return SyncKey;
   }

   /**
    * @param SyncKey to set 
    */
   public void setSyncKey( Integer SyncKey )
   {
      this.SyncKey = SyncKey;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the Placeholder
    */
   public String getPlaceholder( )
   {
      return Placeholder;
   }

   /**
    * @param Placeholder to set 
    */
   public void setPlaceholder( String Placeholder )
   {
      this.Placeholder = Placeholder;
   }

   /**
    * @return the ReportGroupType
    */
   public String getReportGroupType( )
   {
      return ReportGroupType;
   }

   /**
    * @param ReportGroupType to set 
    */
   public void setReportGroupType( String ReportGroupType )
   {
      this.ReportGroupType = ReportGroupType;
   }

   /**
    * @return the ForceHeaderPerEntity
    */
   public String getForceHeaderPerEntity( )
   {
      return ForceHeaderPerEntity;
   }

   /**
    * @param ForceHeaderPerEntity to set 
    */
   public void setForceHeaderPerEntity( String ForceHeaderPerEntity )
   {
      this.ForceHeaderPerEntity = ForceHeaderPerEntity;
   }

   /**
    * @return the ExtendedStyle
    */
   public Integer getExtendedStyle( )
   {
      return ExtendedStyle;
   }

   /**
    * @param ExtendedStyle to set 
    */
   public void setExtendedStyle( Integer ExtendedStyle )
   {
      this.ExtendedStyle = ExtendedStyle;
   }

   /**
    * @return the GUID
    */
   public String getGUID( )
   {
      return GUID;
   }

   /**
    * @param GUID to set 
    */
   public void setGUID( String GUID )
   {
      this.GUID = GUID;
   }

   /**
    * @return the Properties
    */
   public Blob getProperties( )
   {
      return Properties;
   }

   /**
    * @param Properties to set 
    */
   public void setProperties( Blob Properties )
   {
      this.Properties = Properties;
   }

   /**
    * @return the LKey
    */
   public Blob getLKey( )
   {
      return LKey;
   }

   /**
    * @param LKey to set 
    */
   public void setLKey( Blob LKey )
   {
      this.LKey = LKey;
   }

   /**
    * @return the VisibleBorder
    */
   public String getVisibleBorder( )
   {
      return VisibleBorder;
   }

   /**
    * @param VisibleBorder to set 
    */
   public void setVisibleBorder( String VisibleBorder )
   {
      this.VisibleBorder = VisibleBorder;
   }

   /**
    * @return the CenterJustify
    */
   public String getCenterJustify( )
   {
      return CenterJustify;
   }

   /**
    * @param CenterJustify to set 
    */
   public void setCenterJustify( String CenterJustify )
   {
      this.CenterJustify = CenterJustify;
   }

   /**
    * @return the RightJustify
    */
   public String getRightJustify( )
   {
      return RightJustify;
   }

   /**
    * @param RightJustify to set 
    */
   public void setRightJustify( String RightJustify )
   {
      this.RightJustify = RightJustify;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the CSS_Id
    */
   public String getCSS_Id( )
   {
      return CSS_Id;
   }

   /**
    * @param CSS_Id to set 
    */
   public void setCSS_Id( String CSS_Id )
   {
      this.CSS_Id = CSS_Id;
   }

   /**
    * @return the CSS_Font
    */
   public String getCSS_Font( )
   {
      return CSS_Font;
   }

   /**
    * @param CSS_Font to set 
    */
   public void setCSS_Font( String CSS_Font )
   {
      this.CSS_Font = CSS_Font;
   }

   /**
    * @return the CSS_Position
    */
   public String getCSS_Position( )
   {
      return CSS_Position;
   }

   /**
    * @param CSS_Position to set 
    */
   public void setCSS_Position( String CSS_Position )
   {
      this.CSS_Position = CSS_Position;
   }

   /**
    * @return the CSS_Size
    */
   public String getCSS_Size( )
   {
      return CSS_Size;
   }

   /**
    * @param CSS_Size to set 
    */
   public void setCSS_Size( String CSS_Size )
   {
      this.CSS_Size = CSS_Size;
   }

   /**
    * @return the JavaScript
    */
   public String getJavaScript( )
   {
      return JavaScript;
   }

   /**
    * @param JavaScript to set 
    */
   public void setJavaScript( String JavaScript )
   {
      this.JavaScript = JavaScript;
   }

   /**
    * @return the RadioOrCheckboxValue
    */
   public String getRadioOrCheckboxValue( )
   {
      return RadioOrCheckboxValue;
   }

   /**
    * @param RadioOrCheckboxValue to set 
    */
   public void setRadioOrCheckboxValue( String RadioOrCheckboxValue )
   {
      this.RadioOrCheckboxValue = RadioOrCheckboxValue;
   }

   /**
    * @return the WebFileName
    */
   public String getWebFileName( )
   {
      return WebFileName;
   }

   /**
    * @param WebFileName to set 
    */
   public void setWebFileName( String WebFileName )
   {
      this.WebFileName = WebFileName;
   }

   /**
    * @return the WebCtrlType
    */
   public String getWebCtrlType( )
   {
      return WebCtrlType;
   }

   /**
    * @param WebCtrlType to set 
    */
   public void setWebCtrlType( String WebCtrlType )
   {
      this.WebCtrlType = WebCtrlType;
   }

   /**
    * @return the WebColumnSpan
    */
   public String getWebColumnSpan( )
   {
      return WebColumnSpan;
   }

   /**
    * @param WebColumnSpan to set 
    */
   public void setWebColumnSpan( String WebColumnSpan )
   {
      this.WebColumnSpan = WebColumnSpan;
   }

   /**
    * @return the WebWrap
    */
   public String getWebWrap( )
   {
      return WebWrap;
   }

   /**
    * @param WebWrap to set 
    */
   public void setWebWrap( String WebWrap )
   {
      this.WebWrap = WebWrap;
   }

   /**
    * @return the BorderWidth
    */
   public Integer getBorderWidth( )
   {
      return BorderWidth;
   }

   /**
    * @param BorderWidth to set 
    */
   public void setBorderWidth( Integer BorderWidth )
   {
      this.BorderWidth = BorderWidth;
   }

   /**
    * @return the BorderStyle
    */
   public Integer getBorderStyle( )
   {
      return BorderStyle;
   }

   /**
    * @param BorderStyle to set 
    */
   public void setBorderStyle( Integer BorderStyle )
   {
      this.BorderStyle = BorderStyle;
   }

   /**
    * @return the BorderTop
    */
   public Integer getBorderTop( )
   {
      return BorderTop;
   }

   /**
    * @param BorderTop to set 
    */
   public void setBorderTop( Integer BorderTop )
   {
      this.BorderTop = BorderTop;
   }

   /**
    * @return the BorderBottom
    */
   public Integer getBorderBottom( )
   {
      return BorderBottom;
   }

   /**
    * @param BorderBottom to set 
    */
   public void setBorderBottom( Integer BorderBottom )
   {
      this.BorderBottom = BorderBottom;
   }

   /**
    * @return the BorderLeft
    */
   public Integer getBorderLeft( )
   {
      return BorderLeft;
   }

   /**
    * @param BorderLeft to set 
    */
   public void setBorderLeft( Integer BorderLeft )
   {
      this.BorderLeft = BorderLeft;
   }

   /**
    * @return the BorderRight
    */
   public Integer getBorderRight( )
   {
      return BorderRight;
   }

   /**
    * @param BorderRight to set 
    */
   public void setBorderRight( Integer BorderRight )
   {
      this.BorderRight = BorderRight;
   }

   /**
    * @return the TextAlignHorizontal
    */
   public String getTextAlignHorizontal( )
   {
      return TextAlignHorizontal;
   }

   /**
    * @param TextAlignHorizontal to set 
    */
   public void setTextAlignHorizontal( String TextAlignHorizontal )
   {
      this.TextAlignHorizontal = TextAlignHorizontal;
   }

   /**
    * @return the FontSize
    */
   public Integer getFontSize( )
   {
      return FontSize;
   }

   /**
    * @param FontSize to set 
    */
   public void setFontSize( Integer FontSize )
   {
      this.FontSize = FontSize;
   }

   /**
    * @return the TextBold
    */
   public String getTextBold( )
   {
      return TextBold;
   }

   /**
    * @param TextBold to set 
    */
   public void setTextBold( String TextBold )
   {
      this.TextBold = TextBold;
   }

   /**
    * @return the TextItalic
    */
   public String getTextItalic( )
   {
      return TextItalic;
   }

   /**
    * @param TextItalic to set 
    */
   public void setTextItalic( String TextItalic )
   {
      this.TextItalic = TextItalic;
   }

   /**
    * @return the TextUnderline
    */
   public String getTextUnderline( )
   {
      return TextUnderline;
   }

   /**
    * @param TextUnderline to set 
    */
   public void setTextUnderline( String TextUnderline )
   {
      this.TextUnderline = TextUnderline;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   public int loadNLS_DIL_ControlEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      DD_TargetKey = cursor.getStringFromAttribute( "DD_TargetKey" );  if ( DD_TargetKey == null ) DD_TargetKey = "";
      DD_SourceKey = cursor.getStringFromAttribute( "DD_SourceKey" );  if ( DD_SourceKey == null ) DD_SourceKey = "";
      OptionFlags = cursor.getIntegerFromAttribute( "OptionFlags" );  if ( OptionFlags == null ) OptionFlags = 0;
      DD_Type = cursor.getStringFromAttribute( "DD_Type" );  if ( DD_Type == null ) DD_Type = "";
      IdNbr = cursor.getIntegerFromAttribute( "IdNbr" );  if ( IdNbr == null ) IdNbr = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      CtrlBOI = cursor.getBlobFromAttribute( "CtrlBOI" );
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      SyncKey = cursor.getIntegerFromAttribute( "SyncKey" );  if ( SyncKey == null ) SyncKey = 0;
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      Placeholder = cursor.getStringFromAttribute( "Placeholder" );  if ( Placeholder == null ) Placeholder = "";
      ReportGroupType = cursor.getStringFromAttribute( "ReportGroupType" );  if ( ReportGroupType == null ) ReportGroupType = "";
      ForceHeaderPerEntity = cursor.getStringFromAttribute( "ForceHeaderPerEntity" );  if ( ForceHeaderPerEntity == null ) ForceHeaderPerEntity = "";
      ExtendedStyle = cursor.getIntegerFromAttribute( "ExtendedStyle" );  if ( ExtendedStyle == null ) ExtendedStyle = 0;
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      Properties = cursor.getBlobFromAttribute( "Properties" );
      LKey = cursor.getBlobFromAttribute( "LKey" );
      VisibleBorder = cursor.getStringFromAttribute( "VisibleBorder" );  if ( VisibleBorder == null ) VisibleBorder = "";
      CenterJustify = cursor.getStringFromAttribute( "CenterJustify" );  if ( CenterJustify == null ) CenterJustify = "";
      RightJustify = cursor.getStringFromAttribute( "RightJustify" );  if ( RightJustify == null ) RightJustify = "";
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      CSS_Id = cursor.getStringFromAttribute( "CSS_Id" );  if ( CSS_Id == null ) CSS_Id = "";
      CSS_Font = cursor.getStringFromAttribute( "CSS_Font" );  if ( CSS_Font == null ) CSS_Font = "";
      CSS_Position = cursor.getStringFromAttribute( "CSS_Position" );  if ( CSS_Position == null ) CSS_Position = "";
      CSS_Size = cursor.getStringFromAttribute( "CSS_Size" );  if ( CSS_Size == null ) CSS_Size = "";
      JavaScript = cursor.getStringFromAttribute( "JavaScript" );  if ( JavaScript == null ) JavaScript = "";
      RadioOrCheckboxValue = cursor.getStringFromAttribute( "RadioOrCheckboxValue" );  if ( RadioOrCheckboxValue == null ) RadioOrCheckboxValue = "";
      WebFileName = cursor.getStringFromAttribute( "WebFileName" );  if ( WebFileName == null ) WebFileName = "";
      WebCtrlType = cursor.getStringFromAttribute( "WebCtrlType" );  if ( WebCtrlType == null ) WebCtrlType = "";
      WebColumnSpan = cursor.getStringFromAttribute( "WebColumnSpan" );  if ( WebColumnSpan == null ) WebColumnSpan = "";
      WebWrap = cursor.getStringFromAttribute( "WebWrap" );  if ( WebWrap == null ) WebWrap = "";
      BorderWidth = cursor.getIntegerFromAttribute( "BorderWidth" );  if ( BorderWidth == null ) BorderWidth = 0;
      BorderStyle = cursor.getIntegerFromAttribute( "BorderStyle" );  if ( BorderStyle == null ) BorderStyle = 0;
      BorderTop = cursor.getIntegerFromAttribute( "BorderTop" );  if ( BorderTop == null ) BorderTop = 0;
      BorderBottom = cursor.getIntegerFromAttribute( "BorderBottom" );  if ( BorderBottom == null ) BorderBottom = 0;
      BorderLeft = cursor.getIntegerFromAttribute( "BorderLeft" );  if ( BorderLeft == null ) BorderLeft = 0;
      BorderRight = cursor.getIntegerFromAttribute( "BorderRight" );  if ( BorderRight == null ) BorderRight = 0;
      TextAlignHorizontal = cursor.getStringFromAttribute( "TextAlignHorizontal" );  if ( TextAlignHorizontal == null ) TextAlignHorizontal = "";
      FontSize = cursor.getIntegerFromAttribute( "FontSize" );  if ( FontSize == null ) FontSize = 0;
      TextBold = cursor.getStringFromAttribute( "TextBold" );  if ( TextBold == null ) TextBold = "";
      TextItalic = cursor.getStringFromAttribute( "TextItalic" );  if ( TextItalic == null ) TextItalic = "";
      TextUnderline = cursor.getStringFromAttribute( "TextUnderline" );  if ( TextUnderline == null ) TextUnderline = "";
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class NLS_ControlDIL_TextImpl implements NLS_ControlDIL_Text
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected NLS_ControlDIL_TextImpl( EntityCursor cursor )
   {
      loadNLS_ControlDIL_TextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadNLS_ControlDIL_TextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class NLS_DIL_OptionImpl implements NLS_DIL_Option
{
   protected String  Tag;
   protected String  Text;
   protected String  AccelTitle;
   protected String  CheckMarkValueOn;
   protected String  CheckMarkValueOff;
   protected String  Separator;
   protected Integer ZKey;
   protected Integer Underline;
   protected String  DIL_Text;
   protected Integer SeqNo_Menu;
   protected Integer SeqNo_Option;
   protected String  LangID;


   // ctor
   protected NLS_DIL_OptionImpl( EntityCursor cursor )
   {
      loadNLS_DIL_OptionEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the AccelTitle
    */
   public String getAccelTitle( )
   {
      return AccelTitle;
   }

   /**
    * @param AccelTitle to set 
    */
   public void setAccelTitle( String AccelTitle )
   {
      this.AccelTitle = AccelTitle;
   }

   /**
    * @return the CheckMarkValueOn
    */
   public String getCheckMarkValueOn( )
   {
      return CheckMarkValueOn;
   }

   /**
    * @param CheckMarkValueOn to set 
    */
   public void setCheckMarkValueOn( String CheckMarkValueOn )
   {
      this.CheckMarkValueOn = CheckMarkValueOn;
   }

   /**
    * @return the CheckMarkValueOff
    */
   public String getCheckMarkValueOff( )
   {
      return CheckMarkValueOff;
   }

   /**
    * @param CheckMarkValueOff to set 
    */
   public void setCheckMarkValueOff( String CheckMarkValueOff )
   {
      this.CheckMarkValueOff = CheckMarkValueOff;
   }

   /**
    * @return the Separator
    */
   public String getSeparator( )
   {
      return Separator;
   }

   /**
    * @param Separator to set 
    */
   public void setSeparator( String Separator )
   {
      this.Separator = Separator;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Underline
    */
   public Integer getUnderline( )
   {
      return Underline;
   }

   /**
    * @param Underline to set 
    */
   public void setUnderline( Integer Underline )
   {
      this.Underline = Underline;
   }

   /**
    * @return the DIL_Text
    */
   public String getDIL_Text( )
   {
      return DIL_Text;
   }

   /**
    * @param DIL_Text to set 
    */
   public void setDIL_Text( String DIL_Text )
   {
      this.DIL_Text = DIL_Text;
   }

   /**
    * @return the SeqNo_Menu
    */
   public Integer getSeqNo_Menu( )
   {
      return SeqNo_Menu;
   }

   /**
    * @param SeqNo_Menu to set 
    */
   public void setSeqNo_Menu( Integer SeqNo_Menu )
   {
      this.SeqNo_Menu = SeqNo_Menu;
   }

   /**
    * @return the SeqNo_Option
    */
   public Integer getSeqNo_Option( )
   {
      return SeqNo_Option;
   }

   /**
    * @param SeqNo_Option to set 
    */
   public void setSeqNo_Option( Integer SeqNo_Option )
   {
      this.SeqNo_Option = SeqNo_Option;
   }

   /**
    * @return the LangID
    */
   public String getLangID( )
   {
      return LangID;
   }

   /**
    * @param LangID to set 
    */
   public void setLangID( String LangID )
   {
      this.LangID = LangID;
   }

   public int loadNLS_DIL_OptionEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      AccelTitle = cursor.getStringFromAttribute( "AccelTitle" );  if ( AccelTitle == null ) AccelTitle = "";
      CheckMarkValueOn = cursor.getStringFromAttribute( "CheckMarkValueOn" );  if ( CheckMarkValueOn == null ) CheckMarkValueOn = "";
      CheckMarkValueOff = cursor.getStringFromAttribute( "CheckMarkValueOff" );  if ( CheckMarkValueOff == null ) CheckMarkValueOff = "";
      Separator = cursor.getStringFromAttribute( "Separator" );  if ( Separator == null ) Separator = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Underline = cursor.getIntegerFromAttribute( "Underline" );  if ( Underline == null ) Underline = 0;
      DIL_Text = cursor.getStringFromAttribute( "DIL_Text" );  if ( DIL_Text == null ) DIL_Text = "";
      SeqNo_Menu = cursor.getIntegerFromAttribute( "SeqNo_Menu" );  if ( SeqNo_Menu == null ) SeqNo_Menu = 0;
      SeqNo_Option = cursor.getIntegerFromAttribute( "SeqNo_Option" );  if ( SeqNo_Option == null ) SeqNo_Option = 0;
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class NLS_OptionDIL_TextImpl implements NLS_OptionDIL_Text
{
   protected String  Text;
   protected Integer LanguageIndex;
   protected Integer ZKey;


   // ctor
   protected NLS_OptionDIL_TextImpl( EntityCursor cursor )
   {
      loadNLS_OptionDIL_TextEntityStructure( cursor );
   }

   /**
    * @return the Text
    */
   public String getText( )
   {
      return Text;
   }

   /**
    * @param Text to set 
    */
   public void setText( String Text )
   {
      this.Text = Text;
   }

   /**
    * @return the LanguageIndex
    */
   public Integer getLanguageIndex( )
   {
      return LanguageIndex;
   }

   /**
    * @param LanguageIndex to set 
    */
   public void setLanguageIndex( Integer LanguageIndex )
   {
      this.LanguageIndex = LanguageIndex;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadNLS_OptionDIL_TextEntityStructure( EntityCursor cursor )
   {
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      LanguageIndex = cursor.getIntegerFromAttribute( "LanguageIndex" );  if ( LanguageIndex == null ) LanguageIndex = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ReusableWindowSelectionImpl implements ReusableWindowSelection
{
   protected String  Tag;
   protected Integer ZKey;
   protected Integer Subtype;
   protected String  Caption;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected String  DfltButton;
   protected Integer ResourceID;
   protected String  DIL_Active;
   protected String  ProfileView;
   protected Integer GeneralFlag;
   protected Blob    WindowBOI;
   protected String  CSS_Class;
   protected Integer WEB_Timeout;
   protected String  WEB_RelativePositionFlag;


   // ctor
   protected ReusableWindowSelectionImpl( EntityCursor cursor )
   {
      loadReusableWindowSelectionEntityStructure( cursor );
   }

   /**
    * @return the Tag
    */
   public String getTag( )
   {
      return Tag;
   }

   /**
    * @param Tag to set 
    */
   public void setTag( String Tag )
   {
      this.Tag = Tag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Subtype
    */
   public Integer getSubtype( )
   {
      return Subtype;
   }

   /**
    * @param Subtype to set 
    */
   public void setSubtype( Integer Subtype )
   {
      this.Subtype = Subtype;
   }

   /**
    * @return the Caption
    */
   public String getCaption( )
   {
      return Caption;
   }

   /**
    * @param Caption to set 
    */
   public void setCaption( String Caption )
   {
      this.Caption = Caption;
   }

   /**
    * @return the PSDLG_X
    */
   public Integer getPSDLG_X( )
   {
      return PSDLG_X;
   }

   /**
    * @param PSDLG_X to set 
    */
   public void setPSDLG_X( Integer PSDLG_X )
   {
      this.PSDLG_X = PSDLG_X;
   }

   /**
    * @return the PSDLG_Y
    */
   public Integer getPSDLG_Y( )
   {
      return PSDLG_Y;
   }

   /**
    * @param PSDLG_Y to set 
    */
   public void setPSDLG_Y( Integer PSDLG_Y )
   {
      this.PSDLG_Y = PSDLG_Y;
   }

   /**
    * @return the SZDLG_X
    */
   public Integer getSZDLG_X( )
   {
      return SZDLG_X;
   }

   /**
    * @param SZDLG_X to set 
    */
   public void setSZDLG_X( Integer SZDLG_X )
   {
      this.SZDLG_X = SZDLG_X;
   }

   /**
    * @return the SZDLG_Y
    */
   public Integer getSZDLG_Y( )
   {
      return SZDLG_Y;
   }

   /**
    * @param SZDLG_Y to set 
    */
   public void setSZDLG_Y( Integer SZDLG_Y )
   {
      this.SZDLG_Y = SZDLG_Y;
   }

   /**
    * @return the SZMIN_X
    */
   public Integer getSZMIN_X( )
   {
      return SZMIN_X;
   }

   /**
    * @param SZMIN_X to set 
    */
   public void setSZMIN_X( Integer SZMIN_X )
   {
      this.SZMIN_X = SZMIN_X;
   }

   /**
    * @return the SZMIN_Y
    */
   public Integer getSZMIN_Y( )
   {
      return SZMIN_Y;
   }

   /**
    * @param SZMIN_Y to set 
    */
   public void setSZMIN_Y( Integer SZMIN_Y )
   {
      this.SZMIN_Y = SZMIN_Y;
   }

   /**
    * @return the SZMAX_X
    */
   public Integer getSZMAX_X( )
   {
      return SZMAX_X;
   }

   /**
    * @param SZMAX_X to set 
    */
   public void setSZMAX_X( Integer SZMAX_X )
   {
      this.SZMAX_X = SZMAX_X;
   }

   /**
    * @return the SZMAX_Y
    */
   public Integer getSZMAX_Y( )
   {
      return SZMAX_Y;
   }

   /**
    * @param SZMAX_Y to set 
    */
   public void setSZMAX_Y( Integer SZMAX_Y )
   {
      this.SZMAX_Y = SZMAX_Y;
   }

   /**
    * @return the DfltButton
    */
   public String getDfltButton( )
   {
      return DfltButton;
   }

   /**
    * @param DfltButton to set 
    */
   public void setDfltButton( String DfltButton )
   {
      this.DfltButton = DfltButton;
   }

   /**
    * @return the ResourceID
    */
   public Integer getResourceID( )
   {
      return ResourceID;
   }

   /**
    * @param ResourceID to set 
    */
   public void setResourceID( Integer ResourceID )
   {
      this.ResourceID = ResourceID;
   }

   /**
    * @return the DIL_Active
    */
   public String getDIL_Active( )
   {
      return DIL_Active;
   }

   /**
    * @param DIL_Active to set 
    */
   public void setDIL_Active( String DIL_Active )
   {
      this.DIL_Active = DIL_Active;
   }

   /**
    * @return the ProfileView
    */
   public String getProfileView( )
   {
      return ProfileView;
   }

   /**
    * @param ProfileView to set 
    */
   public void setProfileView( String ProfileView )
   {
      this.ProfileView = ProfileView;
   }

   /**
    * @return the GeneralFlag
    */
   public Integer getGeneralFlag( )
   {
      return GeneralFlag;
   }

   /**
    * @param GeneralFlag to set 
    */
   public void setGeneralFlag( Integer GeneralFlag )
   {
      this.GeneralFlag = GeneralFlag;
   }

   /**
    * @return the WindowBOI
    */
   public Blob getWindowBOI( )
   {
      return WindowBOI;
   }

   /**
    * @param WindowBOI to set 
    */
   public void setWindowBOI( Blob WindowBOI )
   {
      this.WindowBOI = WindowBOI;
   }

   /**
    * @return the CSS_Class
    */
   public String getCSS_Class( )
   {
      return CSS_Class;
   }

   /**
    * @param CSS_Class to set 
    */
   public void setCSS_Class( String CSS_Class )
   {
      this.CSS_Class = CSS_Class;
   }

   /**
    * @return the WEB_Timeout
    */
   public Integer getWEB_Timeout( )
   {
      return WEB_Timeout;
   }

   /**
    * @param WEB_Timeout to set 
    */
   public void setWEB_Timeout( Integer WEB_Timeout )
   {
      this.WEB_Timeout = WEB_Timeout;
   }

   /**
    * @return the WEB_RelativePositionFlag
    */
   public String getWEB_RelativePositionFlag( )
   {
      return WEB_RelativePositionFlag;
   }

   /**
    * @param WEB_RelativePositionFlag to set 
    */
   public void setWEB_RelativePositionFlag( String WEB_RelativePositionFlag )
   {
      this.WEB_RelativePositionFlag = WEB_RelativePositionFlag;
   }

   public int loadReusableWindowSelectionEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      DfltButton = cursor.getStringFromAttribute( "DfltButton" );  if ( DfltButton == null ) DfltButton = "";
      ResourceID = cursor.getIntegerFromAttribute( "ResourceID" );  if ( ResourceID == null ) ResourceID = 0;
      DIL_Active = cursor.getStringFromAttribute( "DIL_Active" );  if ( DIL_Active == null ) DIL_Active = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;
      WindowBOI = cursor.getBlobFromAttribute( "WindowBOI" );
      CSS_Class = cursor.getStringFromAttribute( "CSS_Class" );  if ( CSS_Class == null ) CSS_Class = "";
      WEB_Timeout = cursor.getIntegerFromAttribute( "WEB_Timeout" );  if ( WEB_Timeout == null ) WEB_Timeout = 0;
      WEB_RelativePositionFlag = cursor.getStringFromAttribute( "WEB_RelativePositionFlag" );  if ( WEB_RelativePositionFlag == null ) WEB_RelativePositionFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ReusableDialogSelectionImpl implements ReusableDialogSelection
{
   protected String  Name;
   protected Integer CPLR_ZKey;
   protected Integer ZKey;
   protected Integer Status;
   protected Integer UpdateInd;
   protected String  Desc;
   protected String  LastSyncDate;
   protected String  LastUpdateDate;


   // ctor
   protected ReusableDialogSelectionImpl( EntityCursor cursor )
   {
      loadReusableDialogSelectionEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the CPLR_ZKey
    */
   public Integer getCPLR_ZKey( )
   {
      return CPLR_ZKey;
   }

   /**
    * @param CPLR_ZKey to set 
    */
   public void setCPLR_ZKey( Integer CPLR_ZKey )
   {
      this.CPLR_ZKey = CPLR_ZKey;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Status
    */
   public Integer getStatus( )
   {
      return Status;
   }

   /**
    * @param Status to set 
    */
   public void setStatus( Integer Status )
   {
      this.Status = Status;
   }

   /**
    * @return the UpdateInd
    */
   public Integer getUpdateInd( )
   {
      return UpdateInd;
   }

   /**
    * @param UpdateInd to set 
    */
   public void setUpdateInd( Integer UpdateInd )
   {
      this.UpdateInd = UpdateInd;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the LastSyncDate
    */
   public String getLastSyncDate( )
   {
      return LastSyncDate;
   }

   /**
    * @param LastSyncDate to set 
    */
   public void setLastSyncDate( String LastSyncDate )
   {
      this.LastSyncDate = LastSyncDate;
   }

   /**
    * @return the LastUpdateDate
    */
   public String getLastUpdateDate( )
   {
      return LastUpdateDate;
   }

   /**
    * @param LastUpdateDate to set 
    */
   public void setLastUpdateDate( String LastUpdateDate )
   {
      this.LastUpdateDate = LastUpdateDate;
   }

   public int loadReusableDialogSelectionEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      CPLR_ZKey = cursor.getIntegerFromAttribute( "CPLR_ZKey" );  if ( CPLR_ZKey == null ) CPLR_ZKey = 0;
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Status = cursor.getIntegerFromAttribute( "Status" );  if ( Status == null ) Status = 0;
      UpdateInd = cursor.getIntegerFromAttribute( "UpdateInd" );  if ( UpdateInd == null ) UpdateInd = 0;
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      LastSyncDate = cursor.getStringFromAttribute( "LastSyncDate" );  if ( LastSyncDate == null ) LastSyncDate = "";
      LastUpdateDate = cursor.getStringFromAttribute( "LastUpdateDate" );  if ( LastUpdateDate == null ) LastUpdateDate = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class WebControlPropertyOptionImpl implements WebControlPropertyOption
{
   protected String  Name;
   protected Integer ZKey;


   // ctor
   protected WebControlPropertyOptionImpl( EntityCursor cursor )
   {
      loadWebControlPropertyOptionEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadWebControlPropertyOptionEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class ComboBoxEntryImpl implements ComboBoxEntry
{
   protected String  Name;
   protected Integer ZKey;


   // ctor
   protected ComboBoxEntryImpl( EntityCursor cursor )
   {
      loadComboBoxEntryEntityStructure( cursor );
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadComboBoxEntryEntityStructure( EntityCursor cursor )
   {
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class DisplayCompareResultImpl implements DisplayCompareResult
{
   protected String  SelectedFlag;
   protected String  TargetControlType;
   protected String  SourceMappingActionName;
   protected String  TargetMappingActionName;
   protected String  SourceControlType;
   protected String  SourceWindowName;
   protected String  TargetWindowName;
   protected String  SourceControlTag;
   protected String  TargetControlTag;


   // ctor
   protected DisplayCompareResultImpl( EntityCursor cursor )
   {
      loadDisplayCompareResultEntityStructure( cursor );
   }

   /**
    * @return the SelectedFlag
    */
   public String getSelectedFlag( )
   {
      return SelectedFlag;
   }

   /**
    * @param SelectedFlag to set 
    */
   public void setSelectedFlag( String SelectedFlag )
   {
      this.SelectedFlag = SelectedFlag;
   }

   /**
    * @return the TargetControlType
    */
   public String getTargetControlType( )
   {
      return TargetControlType;
   }

   /**
    * @param TargetControlType to set 
    */
   public void setTargetControlType( String TargetControlType )
   {
      this.TargetControlType = TargetControlType;
   }

   /**
    * @return the SourceMappingActionName
    */
   public String getSourceMappingActionName( )
   {
      return SourceMappingActionName;
   }

   /**
    * @param SourceMappingActionName to set 
    */
   public void setSourceMappingActionName( String SourceMappingActionName )
   {
      this.SourceMappingActionName = SourceMappingActionName;
   }

   /**
    * @return the TargetMappingActionName
    */
   public String getTargetMappingActionName( )
   {
      return TargetMappingActionName;
   }

   /**
    * @param TargetMappingActionName to set 
    */
   public void setTargetMappingActionName( String TargetMappingActionName )
   {
      this.TargetMappingActionName = TargetMappingActionName;
   }

   /**
    * @return the SourceControlType
    */
   public String getSourceControlType( )
   {
      return SourceControlType;
   }

   /**
    * @param SourceControlType to set 
    */
   public void setSourceControlType( String SourceControlType )
   {
      this.SourceControlType = SourceControlType;
   }

   /**
    * @return the SourceWindowName
    */
   public String getSourceWindowName( )
   {
      return SourceWindowName;
   }

   /**
    * @param SourceWindowName to set 
    */
   public void setSourceWindowName( String SourceWindowName )
   {
      this.SourceWindowName = SourceWindowName;
   }

   /**
    * @return the TargetWindowName
    */
   public String getTargetWindowName( )
   {
      return TargetWindowName;
   }

   /**
    * @param TargetWindowName to set 
    */
   public void setTargetWindowName( String TargetWindowName )
   {
      this.TargetWindowName = TargetWindowName;
   }

   /**
    * @return the SourceControlTag
    */
   public String getSourceControlTag( )
   {
      return SourceControlTag;
   }

   /**
    * @param SourceControlTag to set 
    */
   public void setSourceControlTag( String SourceControlTag )
   {
      this.SourceControlTag = SourceControlTag;
   }

   /**
    * @return the TargetControlTag
    */
   public String getTargetControlTag( )
   {
      return TargetControlTag;
   }

   /**
    * @param TargetControlTag to set 
    */
   public void setTargetControlTag( String TargetControlTag )
   {
      this.TargetControlTag = TargetControlTag;
   }

   public int loadDisplayCompareResultEntityStructure( EntityCursor cursor )
   {
      SelectedFlag = cursor.getStringFromAttribute( "SelectedFlag" );  if ( SelectedFlag == null ) SelectedFlag = "";
      TargetControlType = cursor.getStringFromAttribute( "TargetControlType" );  if ( TargetControlType == null ) TargetControlType = "";
      SourceMappingActionName = cursor.getStringFromAttribute( "SourceMappingActionName" );  if ( SourceMappingActionName == null ) SourceMappingActionName = "";
      TargetMappingActionName = cursor.getStringFromAttribute( "TargetMappingActionName" );  if ( TargetMappingActionName == null ) TargetMappingActionName = "";
      SourceControlType = cursor.getStringFromAttribute( "SourceControlType" );  if ( SourceControlType == null ) SourceControlType = "";
      SourceWindowName = cursor.getStringFromAttribute( "SourceWindowName" );  if ( SourceWindowName == null ) SourceWindowName = "";
      TargetWindowName = cursor.getStringFromAttribute( "TargetWindowName" );  if ( TargetWindowName == null ) TargetWindowName = "";
      SourceControlTag = cursor.getStringFromAttribute( "SourceControlTag" );  if ( SourceControlTag == null ) SourceControlTag = "";
      TargetControlTag = cursor.getStringFromAttribute( "TargetControlTag" );  if ( TargetControlTag == null ) TargetControlTag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class AutoDesignWindowImpl implements AutoDesignWindow
{
   protected Integer ZKey;
   protected String  WindowTag;
   protected String  Style;
   protected String  BaseWindowName;


   // ctor
   protected AutoDesignWindowImpl( EntityCursor cursor )
   {
      loadAutoDesignWindowEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the WindowTag
    */
   public String getWindowTag( )
   {
      return WindowTag;
   }

   /**
    * @param WindowTag to set 
    */
   public void setWindowTag( String WindowTag )
   {
      this.WindowTag = WindowTag;
   }

   /**
    * @return the Style
    */
   public String getStyle( )
   {
      return Style;
   }

   /**
    * @param Style to set 
    */
   public void setStyle( String Style )
   {
      this.Style = Style;
   }

   /**
    * @return the BaseWindowName
    */
   public String getBaseWindowName( )
   {
      return BaseWindowName;
   }

   /**
    * @param BaseWindowName to set 
    */
   public void setBaseWindowName( String BaseWindowName )
   {
      this.BaseWindowName = BaseWindowName;
   }

   public int loadAutoDesignWindowEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      WindowTag = cursor.getStringFromAttribute( "WindowTag" );  if ( WindowTag == null ) WindowTag = "";
      Style = cursor.getStringFromAttribute( "Style" );  if ( Style == null ) Style = "";
      BaseWindowName = cursor.getStringFromAttribute( "BaseWindowName" );  if ( BaseWindowName == null ) BaseWindowName = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class AutoDesignGroupImpl implements AutoDesignGroup
{
   protected Integer ZKey;
   protected Integer UpdateFieldPromptLength;
   protected String  GroupTag;
   protected Integer ControlWidthInPixels;
   protected String  TempControlType;
   protected String  GenerateGroupType;
   protected String  PreviousFunction;
   protected String  Title;
   protected String  BaseWindowName;
   protected String  BaseGroupName;
   protected String  TopLevelEntityName;
   protected String  ActionNameSuffix;


   // ctor
   protected AutoDesignGroupImpl( EntityCursor cursor )
   {
      loadAutoDesignGroupEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the UpdateFieldPromptLength
    */
   public Integer getUpdateFieldPromptLength( )
   {
      return UpdateFieldPromptLength;
   }

   /**
    * @param UpdateFieldPromptLength to set 
    */
   public void setUpdateFieldPromptLength( Integer UpdateFieldPromptLength )
   {
      this.UpdateFieldPromptLength = UpdateFieldPromptLength;
   }

   /**
    * @return the GroupTag
    */
   public String getGroupTag( )
   {
      return GroupTag;
   }

   /**
    * @param GroupTag to set 
    */
   public void setGroupTag( String GroupTag )
   {
      this.GroupTag = GroupTag;
   }

   /**
    * @return the ControlWidthInPixels
    */
   public Integer getControlWidthInPixels( )
   {
      return ControlWidthInPixels;
   }

   /**
    * @param ControlWidthInPixels to set 
    */
   public void setControlWidthInPixels( Integer ControlWidthInPixels )
   {
      this.ControlWidthInPixels = ControlWidthInPixels;
   }

   /**
    * @return the TempControlType
    */
   public String getTempControlType( )
   {
      return TempControlType;
   }

   /**
    * @param TempControlType to set 
    */
   public void setTempControlType( String TempControlType )
   {
      this.TempControlType = TempControlType;
   }

   /**
    * @return the GenerateGroupType
    */
   public String getGenerateGroupType( )
   {
      return GenerateGroupType;
   }

   /**
    * @param GenerateGroupType to set 
    */
   public void setGenerateGroupType( String GenerateGroupType )
   {
      this.GenerateGroupType = GenerateGroupType;
   }

   /**
    * @return the PreviousFunction
    */
   public String getPreviousFunction( )
   {
      return PreviousFunction;
   }

   /**
    * @param PreviousFunction to set 
    */
   public void setPreviousFunction( String PreviousFunction )
   {
      this.PreviousFunction = PreviousFunction;
   }

   /**
    * @return the Title
    */
   public String getTitle( )
   {
      return Title;
   }

   /**
    * @param Title to set 
    */
   public void setTitle( String Title )
   {
      this.Title = Title;
   }

   /**
    * @return the BaseWindowName
    */
   public String getBaseWindowName( )
   {
      return BaseWindowName;
   }

   /**
    * @param BaseWindowName to set 
    */
   public void setBaseWindowName( String BaseWindowName )
   {
      this.BaseWindowName = BaseWindowName;
   }

   /**
    * @return the BaseGroupName
    */
   public String getBaseGroupName( )
   {
      return BaseGroupName;
   }

   /**
    * @param BaseGroupName to set 
    */
   public void setBaseGroupName( String BaseGroupName )
   {
      this.BaseGroupName = BaseGroupName;
   }

   /**
    * @return the TopLevelEntityName
    */
   public String getTopLevelEntityName( )
   {
      return TopLevelEntityName;
   }

   /**
    * @param TopLevelEntityName to set 
    */
   public void setTopLevelEntityName( String TopLevelEntityName )
   {
      this.TopLevelEntityName = TopLevelEntityName;
   }

   /**
    * @return the ActionNameSuffix
    */
   public String getActionNameSuffix( )
   {
      return ActionNameSuffix;
   }

   /**
    * @param ActionNameSuffix to set 
    */
   public void setActionNameSuffix( String ActionNameSuffix )
   {
      this.ActionNameSuffix = ActionNameSuffix;
   }

   public int loadAutoDesignGroupEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      UpdateFieldPromptLength = cursor.getIntegerFromAttribute( "UpdateFieldPromptLength" );  if ( UpdateFieldPromptLength == null ) UpdateFieldPromptLength = 0;
      GroupTag = cursor.getStringFromAttribute( "GroupTag" );  if ( GroupTag == null ) GroupTag = "";
      ControlWidthInPixels = cursor.getIntegerFromAttribute( "ControlWidthInPixels" );  if ( ControlWidthInPixels == null ) ControlWidthInPixels = 0;
      TempControlType = cursor.getStringFromAttribute( "TempControlType" );  if ( TempControlType == null ) TempControlType = "";
      GenerateGroupType = cursor.getStringFromAttribute( "GenerateGroupType" );  if ( GenerateGroupType == null ) GenerateGroupType = "";
      PreviousFunction = cursor.getStringFromAttribute( "PreviousFunction" );  if ( PreviousFunction == null ) PreviousFunction = "";
      Title = cursor.getStringFromAttribute( "Title" );  if ( Title == null ) Title = "";
      BaseWindowName = cursor.getStringFromAttribute( "BaseWindowName" );  if ( BaseWindowName == null ) BaseWindowName = "";
      BaseGroupName = cursor.getStringFromAttribute( "BaseGroupName" );  if ( BaseGroupName == null ) BaseGroupName = "";
      TopLevelEntityName = cursor.getStringFromAttribute( "TopLevelEntityName" );  if ( TopLevelEntityName == null ) TopLevelEntityName = "";
      ActionNameSuffix = cursor.getStringFromAttribute( "ActionNameSuffix" );  if ( ActionNameSuffix == null ) ActionNameSuffix = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class AD_ListBoxEntityImpl implements AD_ListBoxEntity
{
   protected String  EntityName;
   protected String  ActionUpdateFlag;
   protected String  ActionDeleteFlag;
   protected String  ActionSelectFlag;
   protected String  ActionNewFlag;
   protected Integer ZKey;


   // ctor
   protected AD_ListBoxEntityImpl( EntityCursor cursor )
   {
      loadAD_ListBoxEntityEntityStructure( cursor );
   }

   /**
    * @return the EntityName
    */
   public String getEntityName( )
   {
      return EntityName;
   }

   /**
    * @param EntityName to set 
    */
   public void setEntityName( String EntityName )
   {
      this.EntityName = EntityName;
   }

   /**
    * @return the ActionUpdateFlag
    */
   public String getActionUpdateFlag( )
   {
      return ActionUpdateFlag;
   }

   /**
    * @param ActionUpdateFlag to set 
    */
   public void setActionUpdateFlag( String ActionUpdateFlag )
   {
      this.ActionUpdateFlag = ActionUpdateFlag;
   }

   /**
    * @return the ActionDeleteFlag
    */
   public String getActionDeleteFlag( )
   {
      return ActionDeleteFlag;
   }

   /**
    * @param ActionDeleteFlag to set 
    */
   public void setActionDeleteFlag( String ActionDeleteFlag )
   {
      this.ActionDeleteFlag = ActionDeleteFlag;
   }

   /**
    * @return the ActionSelectFlag
    */
   public String getActionSelectFlag( )
   {
      return ActionSelectFlag;
   }

   /**
    * @param ActionSelectFlag to set 
    */
   public void setActionSelectFlag( String ActionSelectFlag )
   {
      this.ActionSelectFlag = ActionSelectFlag;
   }

   /**
    * @return the ActionNewFlag
    */
   public String getActionNewFlag( )
   {
      return ActionNewFlag;
   }

   /**
    * @param ActionNewFlag to set 
    */
   public void setActionNewFlag( String ActionNewFlag )
   {
      this.ActionNewFlag = ActionNewFlag;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadAD_ListBoxEntityEntityStructure( EntityCursor cursor )
   {
      EntityName = cursor.getStringFromAttribute( "EntityName" );  if ( EntityName == null ) EntityName = "";
      ActionUpdateFlag = cursor.getStringFromAttribute( "ActionUpdateFlag" );  if ( ActionUpdateFlag == null ) ActionUpdateFlag = "";
      ActionDeleteFlag = cursor.getStringFromAttribute( "ActionDeleteFlag" );  if ( ActionDeleteFlag == null ) ActionDeleteFlag = "";
      ActionSelectFlag = cursor.getStringFromAttribute( "ActionSelectFlag" );  if ( ActionSelectFlag == null ) ActionSelectFlag = "";
      ActionNewFlag = cursor.getStringFromAttribute( "ActionNewFlag" );  if ( ActionNewFlag == null ) ActionNewFlag = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class AD_MappingAttributeImpl implements AD_MappingAttribute
{
   protected String  EntityName;
   protected String  AttributeName;
   protected String  ContextName;
   protected String  ControlType;
   protected Integer ControlWidth;
   protected Integer DataWidth;
   protected String  PromptValue;
   protected Integer ZKey;


   // ctor
   protected AD_MappingAttributeImpl( EntityCursor cursor )
   {
      loadAD_MappingAttributeEntityStructure( cursor );
   }

   /**
    * @return the EntityName
    */
   public String getEntityName( )
   {
      return EntityName;
   }

   /**
    * @param EntityName to set 
    */
   public void setEntityName( String EntityName )
   {
      this.EntityName = EntityName;
   }

   /**
    * @return the AttributeName
    */
   public String getAttributeName( )
   {
      return AttributeName;
   }

   /**
    * @param AttributeName to set 
    */
   public void setAttributeName( String AttributeName )
   {
      this.AttributeName = AttributeName;
   }

   /**
    * @return the ContextName
    */
   public String getContextName( )
   {
      return ContextName;
   }

   /**
    * @param ContextName to set 
    */
   public void setContextName( String ContextName )
   {
      this.ContextName = ContextName;
   }

   /**
    * @return the ControlType
    */
   public String getControlType( )
   {
      return ControlType;
   }

   /**
    * @param ControlType to set 
    */
   public void setControlType( String ControlType )
   {
      this.ControlType = ControlType;
   }

   /**
    * @return the ControlWidth
    */
   public Integer getControlWidth( )
   {
      return ControlWidth;
   }

   /**
    * @param ControlWidth to set 
    */
   public void setControlWidth( Integer ControlWidth )
   {
      this.ControlWidth = ControlWidth;
   }

   /**
    * @return the DataWidth
    */
   public Integer getDataWidth( )
   {
      return DataWidth;
   }

   /**
    * @param DataWidth to set 
    */
   public void setDataWidth( Integer DataWidth )
   {
      this.DataWidth = DataWidth;
   }

   /**
    * @return the PromptValue
    */
   public String getPromptValue( )
   {
      return PromptValue;
   }

   /**
    * @param PromptValue to set 
    */
   public void setPromptValue( String PromptValue )
   {
      this.PromptValue = PromptValue;
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   public int loadAD_MappingAttributeEntityStructure( EntityCursor cursor )
   {
      EntityName = cursor.getStringFromAttribute( "EntityName" );  if ( EntityName == null ) EntityName = "";
      AttributeName = cursor.getStringFromAttribute( "AttributeName" );  if ( AttributeName == null ) AttributeName = "";
      ContextName = cursor.getStringFromAttribute( "ContextName" );  if ( ContextName == null ) ContextName = "";
      ControlType = cursor.getStringFromAttribute( "ControlType" );  if ( ControlType == null ) ControlType = "";
      ControlWidth = cursor.getIntegerFromAttribute( "ControlWidth" );  if ( ControlWidth == null ) ControlWidth = 0;
      DataWidth = cursor.getIntegerFromAttribute( "DataWidth" );  if ( DataWidth == null ) DataWidth = 0;
      PromptValue = cursor.getStringFromAttribute( "PromptValue" );  if ( PromptValue == null ) PromptValue = "";
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class AD_GroupViewObjRefImpl implements AD_GroupViewObjRef
{
   protected Integer ZKey;
   protected String  Name;
   protected String  Desc;
   protected Integer Level;
   protected String  IsDrivingViewForReportFlag;


   // ctor
   protected AD_GroupViewObjRefImpl( EntityCursor cursor )
   {
      loadAD_GroupViewObjRefEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the Level
    */
   public Integer getLevel( )
   {
      return Level;
   }

   /**
    * @param Level to set 
    */
   public void setLevel( Integer Level )
   {
      this.Level = Level;
   }

   /**
    * @return the IsDrivingViewForReportFlag
    */
   public String getIsDrivingViewForReportFlag( )
   {
      return IsDrivingViewForReportFlag;
   }

   /**
    * @param IsDrivingViewForReportFlag to set 
    */
   public void setIsDrivingViewForReportFlag( String IsDrivingViewForReportFlag )
   {
      this.IsDrivingViewForReportFlag = IsDrivingViewForReportFlag;
   }

   public int loadAD_GroupViewObjRefEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      Level = cursor.getIntegerFromAttribute( "Level" );  if ( Level == null ) Level = 0;
      IsDrivingViewForReportFlag = cursor.getStringFromAttribute( "IsDrivingViewForReportFlag" );  if ( IsDrivingViewForReportFlag == null ) IsDrivingViewForReportFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class AD_GroupViewObjRefLODImpl implements AD_GroupViewObjRefLOD
{
   protected Integer ZKey;
   protected String  Name;
   protected String  DLL_Name;
   protected String  Desc;
   protected String  ActivateConstraint;
   protected String  ActivateServerConstraint;
   protected String  ActivateEmptyConstraint;
   protected String  CommitConstraint;
   protected String  CommitServerConstraint;
   protected String  DropOIConstraint;
   protected Integer CacheNumberPerEntity;
   protected Integer DataLocking;
   protected String  DoNotMergeFlag;


   // ctor
   protected AD_GroupViewObjRefLODImpl( EntityCursor cursor )
   {
      loadAD_GroupViewObjRefLODEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the DLL_Name
    */
   public String getDLL_Name( )
   {
      return DLL_Name;
   }

   /**
    * @param DLL_Name to set 
    */
   public void setDLL_Name( String DLL_Name )
   {
      this.DLL_Name = DLL_Name;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the ActivateConstraint
    */
   public String getActivateConstraint( )
   {
      return ActivateConstraint;
   }

   /**
    * @param ActivateConstraint to set 
    */
   public void setActivateConstraint( String ActivateConstraint )
   {
      this.ActivateConstraint = ActivateConstraint;
   }

   /**
    * @return the ActivateServerConstraint
    */
   public String getActivateServerConstraint( )
   {
      return ActivateServerConstraint;
   }

   /**
    * @param ActivateServerConstraint to set 
    */
   public void setActivateServerConstraint( String ActivateServerConstraint )
   {
      this.ActivateServerConstraint = ActivateServerConstraint;
   }

   /**
    * @return the ActivateEmptyConstraint
    */
   public String getActivateEmptyConstraint( )
   {
      return ActivateEmptyConstraint;
   }

   /**
    * @param ActivateEmptyConstraint to set 
    */
   public void setActivateEmptyConstraint( String ActivateEmptyConstraint )
   {
      this.ActivateEmptyConstraint = ActivateEmptyConstraint;
   }

   /**
    * @return the CommitConstraint
    */
   public String getCommitConstraint( )
   {
      return CommitConstraint;
   }

   /**
    * @param CommitConstraint to set 
    */
   public void setCommitConstraint( String CommitConstraint )
   {
      this.CommitConstraint = CommitConstraint;
   }

   /**
    * @return the CommitServerConstraint
    */
   public String getCommitServerConstraint( )
   {
      return CommitServerConstraint;
   }

   /**
    * @param CommitServerConstraint to set 
    */
   public void setCommitServerConstraint( String CommitServerConstraint )
   {
      this.CommitServerConstraint = CommitServerConstraint;
   }

   /**
    * @return the DropOIConstraint
    */
   public String getDropOIConstraint( )
   {
      return DropOIConstraint;
   }

   /**
    * @param DropOIConstraint to set 
    */
   public void setDropOIConstraint( String DropOIConstraint )
   {
      this.DropOIConstraint = DropOIConstraint;
   }

   /**
    * @return the CacheNumberPerEntity
    */
   public Integer getCacheNumberPerEntity( )
   {
      return CacheNumberPerEntity;
   }

   /**
    * @param CacheNumberPerEntity to set 
    */
   public void setCacheNumberPerEntity( Integer CacheNumberPerEntity )
   {
      this.CacheNumberPerEntity = CacheNumberPerEntity;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the DoNotMergeFlag
    */
   public String getDoNotMergeFlag( )
   {
      return DoNotMergeFlag;
   }

   /**
    * @param DoNotMergeFlag to set 
    */
   public void setDoNotMergeFlag( String DoNotMergeFlag )
   {
      this.DoNotMergeFlag = DoNotMergeFlag;
   }

   public int loadAD_GroupViewObjRefLODEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      DLL_Name = cursor.getStringFromAttribute( "DLL_Name" );  if ( DLL_Name == null ) DLL_Name = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      ActivateConstraint = cursor.getStringFromAttribute( "ActivateConstraint" );  if ( ActivateConstraint == null ) ActivateConstraint = "";
      ActivateServerConstraint = cursor.getStringFromAttribute( "ActivateServerConstraint" );  if ( ActivateServerConstraint == null ) ActivateServerConstraint = "";
      ActivateEmptyConstraint = cursor.getStringFromAttribute( "ActivateEmptyConstraint" );  if ( ActivateEmptyConstraint == null ) ActivateEmptyConstraint = "";
      CommitConstraint = cursor.getStringFromAttribute( "CommitConstraint" );  if ( CommitConstraint == null ) CommitConstraint = "";
      CommitServerConstraint = cursor.getStringFromAttribute( "CommitServerConstraint" );  if ( CommitServerConstraint == null ) CommitServerConstraint = "";
      DropOIConstraint = cursor.getStringFromAttribute( "DropOIConstraint" );  if ( DropOIConstraint == null ) DropOIConstraint = "";
      CacheNumberPerEntity = cursor.getIntegerFromAttribute( "CacheNumberPerEntity" );  if ( CacheNumberPerEntity == null ) CacheNumberPerEntity = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      DoNotMergeFlag = cursor.getStringFromAttribute( "DoNotMergeFlag" );  if ( DoNotMergeFlag == null ) DoNotMergeFlag = "";

      return 0;
   }

}


/**
This file is part of the Zeidon Gui Dynamic Rendering Engine (Zeidon Dr).

Zeidon Dr is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Zeidon Dr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Zeidon Dr.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2011-2012 Arksoft
*/

package com.quinsoft.zeidon.gui;

import com.quinsoft.zeidon.View;
import com.quinsoft.zeidon.EntityCursor;
import com.quinsoft.zeidon.Blob;

public class AD_GroupLOD_EntityImpl implements AD_GroupLOD_Entity
{
   protected Integer ZKey;
   protected String  Name;
   protected String  IndentName;
   protected Integer IndentLvl;
   protected String  Create;
   protected String  Delete;
   protected String  Include;
   protected String  InclSrc;
   protected String  Exclude;
   protected String  Hidden;
   protected String  Recursive;
   protected String  AutoCreate;
   protected String  Derived;
   protected String  Update;
   protected String  SeqType;
   protected String  Work;
   protected String  Abstract;
   protected String  ParentDeleteBehave;
   protected String  DupEntityInstance;
   protected String  DupRelationshipInstance;
   protected String  RelLinkIndicator;
   protected String  Desc;
   protected String  CreateConstraint;
   protected String  DeleteConstraint;
   protected String  IncludeConstraint;
   protected String  ExcludeConstraint;
   protected String  AcceptConstraint;
   protected String  CancelConstraint;
   protected Integer SeqNo;
   protected Integer DataLocking;
   protected Integer MultipleChildLimit;
   protected String  XML_Name;
   protected String  LazyLoadFlag;
   protected String  ReportDisplayFlag;


   // ctor
   protected AD_GroupLOD_EntityImpl( EntityCursor cursor )
   {
      loadAD_GroupLOD_EntityEntityStructure( cursor );
   }

   /**
    * @return the ZKey
    */
   public Integer getZKey( )
   {
      return ZKey;
   }

   /**
    * @param ZKey to set 
    */
   public void setZKey( Integer ZKey )
   {
      this.ZKey = ZKey;
   }

   /**
    * @return the Name
    */
   public String getName( )
   {
      return Name;
   }

   /**
    * @param Name to set 
    */
   public void setName( String Name )
   {
      this.Name = Name;
   }

   /**
    * @return the IndentName
    */
   public String getIndentName( )
   {
      return IndentName;
   }

   /**
    * @param IndentName to set 
    */
   public void setIndentName( String IndentName )
   {
      this.IndentName = IndentName;
   }

   /**
    * @return the IndentLvl
    */
   public Integer getIndentLvl( )
   {
      return IndentLvl;
   }

   /**
    * @param IndentLvl to set 
    */
   public void setIndentLvl( Integer IndentLvl )
   {
      this.IndentLvl = IndentLvl;
   }

   /**
    * @return the Create
    */
   public String getCreate( )
   {
      return Create;
   }

   /**
    * @param Create to set 
    */
   public void setCreate( String Create )
   {
      this.Create = Create;
   }

   /**
    * @return the Delete
    */
   public String getDelete( )
   {
      return Delete;
   }

   /**
    * @param Delete to set 
    */
   public void setDelete( String Delete )
   {
      this.Delete = Delete;
   }

   /**
    * @return the Include
    */
   public String getInclude( )
   {
      return Include;
   }

   /**
    * @param Include to set 
    */
   public void setInclude( String Include )
   {
      this.Include = Include;
   }

   /**
    * @return the InclSrc
    */
   public String getInclSrc( )
   {
      return InclSrc;
   }

   /**
    * @param InclSrc to set 
    */
   public void setInclSrc( String InclSrc )
   {
      this.InclSrc = InclSrc;
   }

   /**
    * @return the Exclude
    */
   public String getExclude( )
   {
      return Exclude;
   }

   /**
    * @param Exclude to set 
    */
   public void setExclude( String Exclude )
   {
      this.Exclude = Exclude;
   }

   /**
    * @return the Hidden
    */
   public String getHidden( )
   {
      return Hidden;
   }

   /**
    * @param Hidden to set 
    */
   public void setHidden( String Hidden )
   {
      this.Hidden = Hidden;
   }

   /**
    * @return the Recursive
    */
   public String getRecursive( )
   {
      return Recursive;
   }

   /**
    * @param Recursive to set 
    */
   public void setRecursive( String Recursive )
   {
      this.Recursive = Recursive;
   }

   /**
    * @return the AutoCreate
    */
   public String getAutoCreate( )
   {
      return AutoCreate;
   }

   /**
    * @param AutoCreate to set 
    */
   public void setAutoCreate( String AutoCreate )
   {
      this.AutoCreate = AutoCreate;
   }

   /**
    * @return the Derived
    */
   public String getDerived( )
   {
      return Derived;
   }

   /**
    * @param Derived to set 
    */
   public void setDerived( String Derived )
   {
      this.Derived = Derived;
   }

   /**
    * @return the Update
    */
   public String getUpdate( )
   {
      return Update;
   }

   /**
    * @param Update to set 
    */
   public void setUpdate( String Update )
   {
      this.Update = Update;
   }

   /**
    * @return the SeqType
    */
   public String getSeqType( )
   {
      return SeqType;
   }

   /**
    * @param SeqType to set 
    */
   public void setSeqType( String SeqType )
   {
      this.SeqType = SeqType;
   }

   /**
    * @return the Work
    */
   public String getWork( )
   {
      return Work;
   }

   /**
    * @param Work to set 
    */
   public void setWork( String Work )
   {
      this.Work = Work;
   }

   /**
    * @return the Abstract
    */
   public String getAbstract( )
   {
      return Abstract;
   }

   /**
    * @param Abstract to set 
    */
   public void setAbstract( String Abstract )
   {
      this.Abstract = Abstract;
   }

   /**
    * @return the ParentDeleteBehave
    */
   public String getParentDeleteBehave( )
   {
      return ParentDeleteBehave;
   }

   /**
    * @param ParentDeleteBehave to set 
    */
   public void setParentDeleteBehave( String ParentDeleteBehave )
   {
      this.ParentDeleteBehave = ParentDeleteBehave;
   }

   /**
    * @return the DupEntityInstance
    */
   public String getDupEntityInstance( )
   {
      return DupEntityInstance;
   }

   /**
    * @param DupEntityInstance to set 
    */
   public void setDupEntityInstance( String DupEntityInstance )
   {
      this.DupEntityInstance = DupEntityInstance;
   }

   /**
    * @return the DupRelationshipInstance
    */
   public String getDupRelationshipInstance( )
   {
      return DupRelationshipInstance;
   }

   /**
    * @param DupRelationshipInstance to set 
    */
   public void setDupRelationshipInstance( String DupRelationshipInstance )
   {
      this.DupRelationshipInstance = DupRelationshipInstance;
   }

   /**
    * @return the RelLinkIndicator
    */
   public String getRelLinkIndicator( )
   {
      return RelLinkIndicator;
   }

   /**
    * @param RelLinkIndicator to set 
    */
   public void setRelLinkIndicator( String RelLinkIndicator )
   {
      this.RelLinkIndicator = RelLinkIndicator;
   }

   /**
    * @return the Desc
    */
   public String getDesc( )
   {
      return Desc;
   }

   /**
    * @param Desc to set 
    */
   public void setDesc( String Desc )
   {
      this.Desc = Desc;
   }

   /**
    * @return the CreateConstraint
    */
   public String getCreateConstraint( )
   {
      return CreateConstraint;
   }

   /**
    * @param CreateConstraint to set 
    */
   public void setCreateConstraint( String CreateConstraint )
   {
      this.CreateConstraint = CreateConstraint;
   }

   /**
    * @return the DeleteConstraint
    */
   public String getDeleteConstraint( )
   {
      return DeleteConstraint;
   }

   /**
    * @param DeleteConstraint to set 
    */
   public void setDeleteConstraint( String DeleteConstraint )
   {
      this.DeleteConstraint = DeleteConstraint;
   }

   /**
    * @return the IncludeConstraint
    */
   public String getIncludeConstraint( )
   {
      return IncludeConstraint;
   }

   /**
    * @param IncludeConstraint to set 
    */
   public void setIncludeConstraint( String IncludeConstraint )
   {
      this.IncludeConstraint = IncludeConstraint;
   }

   /**
    * @return the ExcludeConstraint
    */
   public String getExcludeConstraint( )
   {
      return ExcludeConstraint;
   }

   /**
    * @param ExcludeConstraint to set 
    */
   public void setExcludeConstraint( String ExcludeConstraint )
   {
      this.ExcludeConstraint = ExcludeConstraint;
   }

   /**
    * @return the AcceptConstraint
    */
   public String getAcceptConstraint( )
   {
      return AcceptConstraint;
   }

   /**
    * @param AcceptConstraint to set 
    */
   public void setAcceptConstraint( String AcceptConstraint )
   {
      this.AcceptConstraint = AcceptConstraint;
   }

   /**
    * @return the CancelConstraint
    */
   public String getCancelConstraint( )
   {
      return CancelConstraint;
   }

   /**
    * @param CancelConstraint to set 
    */
   public void setCancelConstraint( String CancelConstraint )
   {
      this.CancelConstraint = CancelConstraint;
   }

   /**
    * @return the SeqNo
    */
   public Integer getSeqNo( )
   {
      return SeqNo;
   }

   /**
    * @param SeqNo to set 
    */
   public void setSeqNo( Integer SeqNo )
   {
      this.SeqNo = SeqNo;
   }

   /**
    * @return the DataLocking
    */
   public Integer getDataLocking( )
   {
      return DataLocking;
   }

   /**
    * @param DataLocking to set 
    */
   public void setDataLocking( Integer DataLocking )
   {
      this.DataLocking = DataLocking;
   }

   /**
    * @return the MultipleChildLimit
    */
   public Integer getMultipleChildLimit( )
   {
      return MultipleChildLimit;
   }

   /**
    * @param MultipleChildLimit to set 
    */
   public void setMultipleChildLimit( Integer MultipleChildLimit )
   {
      this.MultipleChildLimit = MultipleChildLimit;
   }

   /**
    * @return the XML_Name
    */
   public String getXML_Name( )
   {
      return XML_Name;
   }

   /**
    * @param XML_Name to set 
    */
   public void setXML_Name( String XML_Name )
   {
      this.XML_Name = XML_Name;
   }

   /**
    * @return the LazyLoadFlag
    */
   public String getLazyLoadFlag( )
   {
      return LazyLoadFlag;
   }

   /**
    * @param LazyLoadFlag to set 
    */
   public void setLazyLoadFlag( String LazyLoadFlag )
   {
      this.LazyLoadFlag = LazyLoadFlag;
   }

   /**
    * @return the ReportDisplayFlag
    */
   public String getReportDisplayFlag( )
   {
      return ReportDisplayFlag;
   }

   /**
    * @param ReportDisplayFlag to set 
    */
   public void setReportDisplayFlag( String ReportDisplayFlag )
   {
      this.ReportDisplayFlag = ReportDisplayFlag;
   }

   public int loadAD_GroupLOD_EntityEntityStructure( EntityCursor cursor )
   {
      ZKey = cursor.getIntegerFromAttribute( "ZKey" );  if ( ZKey == null ) ZKey = 0;
      Name = cursor.getStringFromAttribute( "Name" );  if ( Name == null ) Name = "";
      IndentName = cursor.getStringFromAttribute( "IndentName" );  if ( IndentName == null ) IndentName = "";
      IndentLvl = cursor.getIntegerFromAttribute( "IndentLvl" );  if ( IndentLvl == null ) IndentLvl = 0;
      Create = cursor.getStringFromAttribute( "Create" );  if ( Create == null ) Create = "";
      Delete = cursor.getStringFromAttribute( "Delete" );  if ( Delete == null ) Delete = "";
      Include = cursor.getStringFromAttribute( "Include" );  if ( Include == null ) Include = "";
      InclSrc = cursor.getStringFromAttribute( "InclSrc" );  if ( InclSrc == null ) InclSrc = "";
      Exclude = cursor.getStringFromAttribute( "Exclude" );  if ( Exclude == null ) Exclude = "";
      Hidden = cursor.getStringFromAttribute( "Hidden" );  if ( Hidden == null ) Hidden = "";
      Recursive = cursor.getStringFromAttribute( "Recursive" );  if ( Recursive == null ) Recursive = "";
      AutoCreate = cursor.getStringFromAttribute( "AutoCreate" );  if ( AutoCreate == null ) AutoCreate = "";
      Derived = cursor.getStringFromAttribute( "Derived" );  if ( Derived == null ) Derived = "";
      Update = cursor.getStringFromAttribute( "Update" );  if ( Update == null ) Update = "";
      SeqType = cursor.getStringFromAttribute( "SeqType" );  if ( SeqType == null ) SeqType = "";
      Work = cursor.getStringFromAttribute( "Work" );  if ( Work == null ) Work = "";
      Abstract = cursor.getStringFromAttribute( "Abstract" );  if ( Abstract == null ) Abstract = "";
      ParentDeleteBehave = cursor.getStringFromAttribute( "ParentDeleteBehave" );  if ( ParentDeleteBehave == null ) ParentDeleteBehave = "";
      DupEntityInstance = cursor.getStringFromAttribute( "DupEntityInstance" );  if ( DupEntityInstance == null ) DupEntityInstance = "";
      DupRelationshipInstance = cursor.getStringFromAttribute( "DupRelationshipInstance" );  if ( DupRelationshipInstance == null ) DupRelationshipInstance = "";
      RelLinkIndicator = cursor.getStringFromAttribute( "RelLinkIndicator" );  if ( RelLinkIndicator == null ) RelLinkIndicator = "";
      Desc = cursor.getStringFromAttribute( "Desc" );  if ( Desc == null ) Desc = "";
      CreateConstraint = cursor.getStringFromAttribute( "CreateConstraint" );  if ( CreateConstraint == null ) CreateConstraint = "";
      DeleteConstraint = cursor.getStringFromAttribute( "DeleteConstraint" );  if ( DeleteConstraint == null ) DeleteConstraint = "";
      IncludeConstraint = cursor.getStringFromAttribute( "IncludeConstraint" );  if ( IncludeConstraint == null ) IncludeConstraint = "";
      ExcludeConstraint = cursor.getStringFromAttribute( "ExcludeConstraint" );  if ( ExcludeConstraint == null ) ExcludeConstraint = "";
      AcceptConstraint = cursor.getStringFromAttribute( "AcceptConstraint" );  if ( AcceptConstraint == null ) AcceptConstraint = "";
      CancelConstraint = cursor.getStringFromAttribute( "CancelConstraint" );  if ( CancelConstraint == null ) CancelConstraint = "";
      SeqNo = cursor.getIntegerFromAttribute( "SeqNo" );  if ( SeqNo == null ) SeqNo = 0;
      DataLocking = cursor.getIntegerFromAttribute( "DataLocking" );  if ( DataLocking == null ) DataLocking = 0;
      MultipleChildLimit = cursor.getIntegerFromAttribute( "MultipleChildLimit" );  if ( MultipleChildLimit == null ) MultipleChildLimit = 0;
      XML_Name = cursor.getStringFromAttribute( "XML_Name" );  if ( XML_Name == null ) XML_Name = "";
      LazyLoadFlag = cursor.getStringFromAttribute( "LazyLoadFlag" );  if ( LazyLoadFlag == null ) LazyLoadFlag = "";
      ReportDisplayFlag = cursor.getStringFromAttribute( "ReportDisplayFlag" );  if ( ReportDisplayFlag == null ) ReportDisplayFlag = "";

      return 0;
   }

}


