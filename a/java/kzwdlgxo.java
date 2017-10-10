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

public class DlgImpl implements Dlg
{
   protected String  Tag;
   protected String  DLL;
   protected String  DfltWnd;
   protected Integer PE;


   // ctor
   protected DlgImpl( EntityCursor cursor )
   {
      loadDlgEntityStructure( cursor );
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
    * @return the DfltWnd
    */
   public String getDfltWnd( )
   {
      return DfltWnd;
   }

   /**
    * @param DfltWnd to set 
    */
   public void setDfltWnd( String DfltWnd )
   {
      this.DfltWnd = DfltWnd;
   }

   /**
    * @return the PE
    */
   public Integer getPE( )
   {
      return PE;
   }

   /**
    * @param PE to set 
    */
   public void setPE( Integer PE )
   {
      this.PE = PE;
   }

   public int loadDlgEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      DfltWnd = cursor.getStringFromAttribute( "DfltWnd" );  if ( DfltWnd == null ) DfltWnd = "";
      PE = cursor.getIntegerFromAttribute( "PE" );  if ( PE == null ) PE = 0;

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
   protected Integer REL_X;
   protected Integer REL_Y;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected Integer StyleEx;
   protected Integer Style;
   protected String  DfltBtn;
   protected Integer ResID;
   protected String  DfltMenu;
   protected Integer ActCnt;
   protected Integer CtrlCnt;
   protected Blob    OperCtrl;
   protected Blob    Hotkey;
   protected Integer Subtype;
   protected String  Caption;
   protected String  ProfileView;
   protected Integer GeneralFlag;


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
    * @return the REL_X
    */
   public Integer getREL_X( )
   {
      return REL_X;
   }

   /**
    * @param REL_X to set 
    */
   public void setREL_X( Integer REL_X )
   {
      this.REL_X = REL_X;
   }

   /**
    * @return the REL_Y
    */
   public Integer getREL_Y( )
   {
      return REL_Y;
   }

   /**
    * @param REL_Y to set 
    */
   public void setREL_Y( Integer REL_Y )
   {
      this.REL_Y = REL_Y;
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
    * @return the DfltBtn
    */
   public String getDfltBtn( )
   {
      return DfltBtn;
   }

   /**
    * @param DfltBtn to set 
    */
   public void setDfltBtn( String DfltBtn )
   {
      this.DfltBtn = DfltBtn;
   }

   /**
    * @return the ResID
    */
   public Integer getResID( )
   {
      return ResID;
   }

   /**
    * @param ResID to set 
    */
   public void setResID( Integer ResID )
   {
      this.ResID = ResID;
   }

   /**
    * @return the DfltMenu
    */
   public String getDfltMenu( )
   {
      return DfltMenu;
   }

   /**
    * @param DfltMenu to set 
    */
   public void setDfltMenu( String DfltMenu )
   {
      this.DfltMenu = DfltMenu;
   }

   /**
    * @return the ActCnt
    */
   public Integer getActCnt( )
   {
      return ActCnt;
   }

   /**
    * @param ActCnt to set 
    */
   public void setActCnt( Integer ActCnt )
   {
      this.ActCnt = ActCnt;
   }

   /**
    * @return the CtrlCnt
    */
   public Integer getCtrlCnt( )
   {
      return CtrlCnt;
   }

   /**
    * @param CtrlCnt to set 
    */
   public void setCtrlCnt( Integer CtrlCnt )
   {
      this.CtrlCnt = CtrlCnt;
   }

   /**
    * @return the OperCtrl
    */
   public Blob getOperCtrl( )
   {
      return OperCtrl;
   }

   /**
    * @param OperCtrl to set 
    */
   public void setOperCtrl( Blob OperCtrl )
   {
      this.OperCtrl = OperCtrl;
   }

   /**
    * @return the Hotkey
    */
   public Blob getHotkey( )
   {
      return Hotkey;
   }

   /**
    * @param Hotkey to set 
    */
   public void setHotkey( Blob Hotkey )
   {
      this.Hotkey = Hotkey;
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

   public int loadDfltWndEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      REL_X = cursor.getIntegerFromAttribute( "REL_X" );  if ( REL_X == null ) REL_X = 0;
      REL_Y = cursor.getIntegerFromAttribute( "REL_Y" );  if ( REL_Y == null ) REL_Y = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      StyleEx = cursor.getIntegerFromAttribute( "StyleEx" );  if ( StyleEx == null ) StyleEx = 0;
      Style = cursor.getIntegerFromAttribute( "Style" );  if ( Style == null ) Style = 0;
      DfltBtn = cursor.getStringFromAttribute( "DfltBtn" );  if ( DfltBtn == null ) DfltBtn = "";
      ResID = cursor.getIntegerFromAttribute( "ResID" );  if ( ResID == null ) ResID = 0;
      DfltMenu = cursor.getStringFromAttribute( "DfltMenu" );  if ( DfltMenu == null ) DfltMenu = "";
      ActCnt = cursor.getIntegerFromAttribute( "ActCnt" );  if ( ActCnt == null ) ActCnt = 0;
      CtrlCnt = cursor.getIntegerFromAttribute( "CtrlCnt" );  if ( CtrlCnt == null ) CtrlCnt = 0;
      OperCtrl = cursor.getBlobFromAttribute( "OperCtrl" );
      Hotkey = cursor.getBlobFromAttribute( "Hotkey" );
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;

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

public class WndImpl implements Wnd
{
   protected String  Tag;
   protected Integer REL_X;
   protected Integer REL_Y;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer SZMIN_X;
   protected Integer SZMIN_Y;
   protected Integer SZMAX_X;
   protected Integer SZMAX_Y;
   protected Integer StyleEx;
   protected Integer Style;
   protected String  DfltBtn;
   protected Integer ResID;
   protected String  DfltMenu;
   protected Integer ActCnt;
   protected Integer CtrlCnt;
   protected Blob    OperCtrl;
   protected Blob    Hotkey;
   protected Integer Subtype;
   protected String  D_Caption;
   protected Integer NLS;
   protected String  Caption;
   protected String  ProfileView;
   protected Integer GeneralFlag;


   // ctor
   protected WndImpl( EntityCursor cursor )
   {
      loadWndEntityStructure( cursor );
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
    * @return the REL_X
    */
   public Integer getREL_X( )
   {
      return REL_X;
   }

   /**
    * @param REL_X to set 
    */
   public void setREL_X( Integer REL_X )
   {
      this.REL_X = REL_X;
   }

   /**
    * @return the REL_Y
    */
   public Integer getREL_Y( )
   {
      return REL_Y;
   }

   /**
    * @param REL_Y to set 
    */
   public void setREL_Y( Integer REL_Y )
   {
      this.REL_Y = REL_Y;
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
    * @return the DfltBtn
    */
   public String getDfltBtn( )
   {
      return DfltBtn;
   }

   /**
    * @param DfltBtn to set 
    */
   public void setDfltBtn( String DfltBtn )
   {
      this.DfltBtn = DfltBtn;
   }

   /**
    * @return the ResID
    */
   public Integer getResID( )
   {
      return ResID;
   }

   /**
    * @param ResID to set 
    */
   public void setResID( Integer ResID )
   {
      this.ResID = ResID;
   }

   /**
    * @return the DfltMenu
    */
   public String getDfltMenu( )
   {
      return DfltMenu;
   }

   /**
    * @param DfltMenu to set 
    */
   public void setDfltMenu( String DfltMenu )
   {
      this.DfltMenu = DfltMenu;
   }

   /**
    * @return the ActCnt
    */
   public Integer getActCnt( )
   {
      return ActCnt;
   }

   /**
    * @param ActCnt to set 
    */
   public void setActCnt( Integer ActCnt )
   {
      this.ActCnt = ActCnt;
   }

   /**
    * @return the CtrlCnt
    */
   public Integer getCtrlCnt( )
   {
      return CtrlCnt;
   }

   /**
    * @param CtrlCnt to set 
    */
   public void setCtrlCnt( Integer CtrlCnt )
   {
      this.CtrlCnt = CtrlCnt;
   }

   /**
    * @return the OperCtrl
    */
   public Blob getOperCtrl( )
   {
      return OperCtrl;
   }

   /**
    * @param OperCtrl to set 
    */
   public void setOperCtrl( Blob OperCtrl )
   {
      this.OperCtrl = OperCtrl;
   }

   /**
    * @return the Hotkey
    */
   public Blob getHotkey( )
   {
      return Hotkey;
   }

   /**
    * @param Hotkey to set 
    */
   public void setHotkey( Blob Hotkey )
   {
      this.Hotkey = Hotkey;
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
    * @return the D_Caption
    */
   public String getD_Caption( )
   {
      return D_Caption;
   }

   /**
    * @param D_Caption to set 
    */
   public void setD_Caption( String D_Caption )
   {
      this.D_Caption = D_Caption;
   }

   /**
    * @return the NLS
    */
   public Integer getNLS( )
   {
      return NLS;
   }

   /**
    * @param NLS to set 
    */
   public void setNLS( Integer NLS )
   {
      this.NLS = NLS;
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

   public int loadWndEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      REL_X = cursor.getIntegerFromAttribute( "REL_X" );  if ( REL_X == null ) REL_X = 0;
      REL_Y = cursor.getIntegerFromAttribute( "REL_Y" );  if ( REL_Y == null ) REL_Y = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      SZMIN_X = cursor.getIntegerFromAttribute( "SZMIN_X" );  if ( SZMIN_X == null ) SZMIN_X = 0;
      SZMIN_Y = cursor.getIntegerFromAttribute( "SZMIN_Y" );  if ( SZMIN_Y == null ) SZMIN_Y = 0;
      SZMAX_X = cursor.getIntegerFromAttribute( "SZMAX_X" );  if ( SZMAX_X == null ) SZMAX_X = 0;
      SZMAX_Y = cursor.getIntegerFromAttribute( "SZMAX_Y" );  if ( SZMAX_Y == null ) SZMAX_Y = 0;
      StyleEx = cursor.getIntegerFromAttribute( "StyleEx" );  if ( StyleEx == null ) StyleEx = 0;
      Style = cursor.getIntegerFromAttribute( "Style" );  if ( Style == null ) Style = 0;
      DfltBtn = cursor.getStringFromAttribute( "DfltBtn" );  if ( DfltBtn == null ) DfltBtn = "";
      ResID = cursor.getIntegerFromAttribute( "ResID" );  if ( ResID == null ) ResID = 0;
      DfltMenu = cursor.getStringFromAttribute( "DfltMenu" );  if ( DfltMenu == null ) DfltMenu = "";
      ActCnt = cursor.getIntegerFromAttribute( "ActCnt" );  if ( ActCnt == null ) ActCnt = 0;
      CtrlCnt = cursor.getIntegerFromAttribute( "CtrlCnt" );  if ( CtrlCnt == null ) CtrlCnt = 0;
      OperCtrl = cursor.getBlobFromAttribute( "OperCtrl" );
      Hotkey = cursor.getBlobFromAttribute( "Hotkey" );
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      D_Caption = cursor.getStringFromAttribute( "D_Caption" );  if ( D_Caption == null ) D_Caption = "";
      NLS = cursor.getIntegerFromAttribute( "NLS" );  if ( NLS == null ) NLS = 0;
      Caption = cursor.getStringFromAttribute( "Caption" );  if ( Caption == null ) Caption = "";
      ProfileView = cursor.getStringFromAttribute( "ProfileView" );  if ( ProfileView == null ) ProfileView = "";
      GeneralFlag = cursor.getIntegerFromAttribute( "GeneralFlag" );  if ( GeneralFlag == null ) GeneralFlag = 0;

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

public class CtrlImpl implements Ctrl
{
   protected String  Tag;
   protected String  Text;
   protected Integer Type;
   protected Integer Subtype;
   protected Integer StyleX;
   protected Integer OptionFlags;
   protected Integer IdNbr;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer RELCNT_X;
   protected Integer RELCNT_Y;
   protected Blob    CtrlBOI;
   protected Integer ColorFg;
   protected Integer ColorBk;
   protected Integer DIL;
   protected String  Placeholder;
   protected Blob    EventAct;
   protected Blob    DD_BOI;
   protected String  D_Text;
   protected Integer NLS;
   protected String  TagPE;
   protected String  GUID;
   protected Blob    Properties;
   protected Blob    LKey;
   protected String  Script;
   protected String  ScriptDLL;
   protected String  LangID;


   // ctor
   protected CtrlImpl( EntityCursor cursor )
   {
      loadCtrlEntityStructure( cursor );
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
    * @return the StyleX
    */
   public Integer getStyleX( )
   {
      return StyleX;
   }

   /**
    * @param StyleX to set 
    */
   public void setStyleX( Integer StyleX )
   {
      this.StyleX = StyleX;
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
    * @return the RELCNT_X
    */
   public Integer getRELCNT_X( )
   {
      return RELCNT_X;
   }

   /**
    * @param RELCNT_X to set 
    */
   public void setRELCNT_X( Integer RELCNT_X )
   {
      this.RELCNT_X = RELCNT_X;
   }

   /**
    * @return the RELCNT_Y
    */
   public Integer getRELCNT_Y( )
   {
      return RELCNT_Y;
   }

   /**
    * @param RELCNT_Y to set 
    */
   public void setRELCNT_Y( Integer RELCNT_Y )
   {
      this.RELCNT_Y = RELCNT_Y;
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
    * @return the ColorFg
    */
   public Integer getColorFg( )
   {
      return ColorFg;
   }

   /**
    * @param ColorFg to set 
    */
   public void setColorFg( Integer ColorFg )
   {
      this.ColorFg = ColorFg;
   }

   /**
    * @return the ColorBk
    */
   public Integer getColorBk( )
   {
      return ColorBk;
   }

   /**
    * @param ColorBk to set 
    */
   public void setColorBk( Integer ColorBk )
   {
      this.ColorBk = ColorBk;
   }

   /**
    * @return the DIL
    */
   public Integer getDIL( )
   {
      return DIL;
   }

   /**
    * @param DIL to set 
    */
   public void setDIL( Integer DIL )
   {
      this.DIL = DIL;
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
    * @return the EventAct
    */
   public Blob getEventAct( )
   {
      return EventAct;
   }

   /**
    * @param EventAct to set 
    */
   public void setEventAct( Blob EventAct )
   {
      this.EventAct = EventAct;
   }

   /**
    * @return the DD_BOI
    */
   public Blob getDD_BOI( )
   {
      return DD_BOI;
   }

   /**
    * @param DD_BOI to set 
    */
   public void setDD_BOI( Blob DD_BOI )
   {
      this.DD_BOI = DD_BOI;
   }

   /**
    * @return the D_Text
    */
   public String getD_Text( )
   {
      return D_Text;
   }

   /**
    * @param D_Text to set 
    */
   public void setD_Text( String D_Text )
   {
      this.D_Text = D_Text;
   }

   /**
    * @return the NLS
    */
   public Integer getNLS( )
   {
      return NLS;
   }

   /**
    * @param NLS to set 
    */
   public void setNLS( Integer NLS )
   {
      this.NLS = NLS;
   }

   /**
    * @return the TagPE
    */
   public String getTagPE( )
   {
      return TagPE;
   }

   /**
    * @param TagPE to set 
    */
   public void setTagPE( String TagPE )
   {
      this.TagPE = TagPE;
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
    * @return the Script
    */
   public String getScript( )
   {
      return Script;
   }

   /**
    * @param Script to set 
    */
   public void setScript( String Script )
   {
      this.Script = Script;
   }

   /**
    * @return the ScriptDLL
    */
   public String getScriptDLL( )
   {
      return ScriptDLL;
   }

   /**
    * @param ScriptDLL to set 
    */
   public void setScriptDLL( String ScriptDLL )
   {
      this.ScriptDLL = ScriptDLL;
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

   public int loadCtrlEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      StyleX = cursor.getIntegerFromAttribute( "StyleX" );  if ( StyleX == null ) StyleX = 0;
      OptionFlags = cursor.getIntegerFromAttribute( "OptionFlags" );  if ( OptionFlags == null ) OptionFlags = 0;
      IdNbr = cursor.getIntegerFromAttribute( "IdNbr" );  if ( IdNbr == null ) IdNbr = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      RELCNT_X = cursor.getIntegerFromAttribute( "RELCNT_X" );  if ( RELCNT_X == null ) RELCNT_X = 0;
      RELCNT_Y = cursor.getIntegerFromAttribute( "RELCNT_Y" );  if ( RELCNT_Y == null ) RELCNT_Y = 0;
      CtrlBOI = cursor.getBlobFromAttribute( "CtrlBOI" );
      ColorFg = cursor.getIntegerFromAttribute( "ColorFg" );  if ( ColorFg == null ) ColorFg = 0;
      ColorBk = cursor.getIntegerFromAttribute( "ColorBk" );  if ( ColorBk == null ) ColorBk = 0;
      DIL = cursor.getIntegerFromAttribute( "DIL" );  if ( DIL == null ) DIL = 0;
      Placeholder = cursor.getStringFromAttribute( "Placeholder" );  if ( Placeholder == null ) Placeholder = "";
      EventAct = cursor.getBlobFromAttribute( "EventAct" );
      DD_BOI = cursor.getBlobFromAttribute( "DD_BOI" );
      D_Text = cursor.getStringFromAttribute( "D_Text" );  if ( D_Text == null ) D_Text = "";
      NLS = cursor.getIntegerFromAttribute( "NLS" );  if ( NLS == null ) NLS = 0;
      TagPE = cursor.getStringFromAttribute( "TagPE" );  if ( TagPE == null ) TagPE = "";
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      Properties = cursor.getBlobFromAttribute( "Properties" );
      LKey = cursor.getBlobFromAttribute( "LKey" );
      Script = cursor.getStringFromAttribute( "Script" );  if ( Script == null ) Script = "";
      ScriptDLL = cursor.getStringFromAttribute( "ScriptDLL" );  if ( ScriptDLL == null ) ScriptDLL = "";
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

public class CtrlCtrlImpl implements CtrlCtrl
{
   protected String  Tag;
   protected String  Text;
   protected Integer Type;
   protected Integer Subtype;
   protected Integer StyleX;
   protected Integer OptionFlags;
   protected Integer IdNbr;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Integer RELCNT_X;
   protected Integer RELCNT_Y;
   protected Blob    CtrlBOI;
   protected Integer ColorFg;
   protected Integer ColorBk;
   protected Integer DIL;
   protected String  Placeholder;
   protected Blob    EventAct;
   protected Blob    DD_BOI;
   protected String  D_Text;
   protected Integer NLS;
   protected String  TagPE;
   protected String  GUID;
   protected Blob    Properties;
   protected Blob    LKey;
   protected String  Script;
   protected String  ScriptDLL;
   protected String  LangID;


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
    * @return the StyleX
    */
   public Integer getStyleX( )
   {
      return StyleX;
   }

   /**
    * @param StyleX to set 
    */
   public void setStyleX( Integer StyleX )
   {
      this.StyleX = StyleX;
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
    * @return the RELCNT_X
    */
   public Integer getRELCNT_X( )
   {
      return RELCNT_X;
   }

   /**
    * @param RELCNT_X to set 
    */
   public void setRELCNT_X( Integer RELCNT_X )
   {
      this.RELCNT_X = RELCNT_X;
   }

   /**
    * @return the RELCNT_Y
    */
   public Integer getRELCNT_Y( )
   {
      return RELCNT_Y;
   }

   /**
    * @param RELCNT_Y to set 
    */
   public void setRELCNT_Y( Integer RELCNT_Y )
   {
      this.RELCNT_Y = RELCNT_Y;
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
    * @return the ColorFg
    */
   public Integer getColorFg( )
   {
      return ColorFg;
   }

   /**
    * @param ColorFg to set 
    */
   public void setColorFg( Integer ColorFg )
   {
      this.ColorFg = ColorFg;
   }

   /**
    * @return the ColorBk
    */
   public Integer getColorBk( )
   {
      return ColorBk;
   }

   /**
    * @param ColorBk to set 
    */
   public void setColorBk( Integer ColorBk )
   {
      this.ColorBk = ColorBk;
   }

   /**
    * @return the DIL
    */
   public Integer getDIL( )
   {
      return DIL;
   }

   /**
    * @param DIL to set 
    */
   public void setDIL( Integer DIL )
   {
      this.DIL = DIL;
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
    * @return the EventAct
    */
   public Blob getEventAct( )
   {
      return EventAct;
   }

   /**
    * @param EventAct to set 
    */
   public void setEventAct( Blob EventAct )
   {
      this.EventAct = EventAct;
   }

   /**
    * @return the DD_BOI
    */
   public Blob getDD_BOI( )
   {
      return DD_BOI;
   }

   /**
    * @param DD_BOI to set 
    */
   public void setDD_BOI( Blob DD_BOI )
   {
      this.DD_BOI = DD_BOI;
   }

   /**
    * @return the D_Text
    */
   public String getD_Text( )
   {
      return D_Text;
   }

   /**
    * @param D_Text to set 
    */
   public void setD_Text( String D_Text )
   {
      this.D_Text = D_Text;
   }

   /**
    * @return the NLS
    */
   public Integer getNLS( )
   {
      return NLS;
   }

   /**
    * @param NLS to set 
    */
   public void setNLS( Integer NLS )
   {
      this.NLS = NLS;
   }

   /**
    * @return the TagPE
    */
   public String getTagPE( )
   {
      return TagPE;
   }

   /**
    * @param TagPE to set 
    */
   public void setTagPE( String TagPE )
   {
      this.TagPE = TagPE;
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
    * @return the Script
    */
   public String getScript( )
   {
      return Script;
   }

   /**
    * @param Script to set 
    */
   public void setScript( String Script )
   {
      this.Script = Script;
   }

   /**
    * @return the ScriptDLL
    */
   public String getScriptDLL( )
   {
      return ScriptDLL;
   }

   /**
    * @param ScriptDLL to set 
    */
   public void setScriptDLL( String ScriptDLL )
   {
      this.ScriptDLL = ScriptDLL;
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

   public int loadCtrlCtrlEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      StyleX = cursor.getIntegerFromAttribute( "StyleX" );  if ( StyleX == null ) StyleX = 0;
      OptionFlags = cursor.getIntegerFromAttribute( "OptionFlags" );  if ( OptionFlags == null ) OptionFlags = 0;
      IdNbr = cursor.getIntegerFromAttribute( "IdNbr" );  if ( IdNbr == null ) IdNbr = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      RELCNT_X = cursor.getIntegerFromAttribute( "RELCNT_X" );  if ( RELCNT_X == null ) RELCNT_X = 0;
      RELCNT_Y = cursor.getIntegerFromAttribute( "RELCNT_Y" );  if ( RELCNT_Y == null ) RELCNT_Y = 0;
      CtrlBOI = cursor.getBlobFromAttribute( "CtrlBOI" );
      ColorFg = cursor.getIntegerFromAttribute( "ColorFg" );  if ( ColorFg == null ) ColorFg = 0;
      ColorBk = cursor.getIntegerFromAttribute( "ColorBk" );  if ( ColorBk == null ) ColorBk = 0;
      DIL = cursor.getIntegerFromAttribute( "DIL" );  if ( DIL == null ) DIL = 0;
      Placeholder = cursor.getStringFromAttribute( "Placeholder" );  if ( Placeholder == null ) Placeholder = "";
      EventAct = cursor.getBlobFromAttribute( "EventAct" );
      DD_BOI = cursor.getBlobFromAttribute( "DD_BOI" );
      D_Text = cursor.getStringFromAttribute( "D_Text" );  if ( D_Text == null ) D_Text = "";
      NLS = cursor.getIntegerFromAttribute( "NLS" );  if ( NLS == null ) NLS = 0;
      TagPE = cursor.getStringFromAttribute( "TagPE" );  if ( TagPE == null ) TagPE = "";
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      Properties = cursor.getBlobFromAttribute( "Properties" );
      LKey = cursor.getBlobFromAttribute( "LKey" );
      Script = cursor.getStringFromAttribute( "Script" );  if ( Script == null ) Script = "";
      ScriptDLL = cursor.getStringFromAttribute( "ScriptDLL" );  if ( ScriptDLL == null ) ScriptDLL = "";
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

public class CtrlMapImpl implements CtrlMap
{
   protected String  Tag;
   protected String  VN;
   protected String  EN;
   protected String  AN;
   protected String  Context;
   protected String  Type;


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
    * @return the VN
    */
   public String getVN( )
   {
      return VN;
   }

   /**
    * @param VN to set 
    */
   public void setVN( String VN )
   {
      this.VN = VN;
   }

   /**
    * @return the EN
    */
   public String getEN( )
   {
      return EN;
   }

   /**
    * @param EN to set 
    */
   public void setEN( String EN )
   {
      this.EN = EN;
   }

   /**
    * @return the AN
    */
   public String getAN( )
   {
      return AN;
   }

   /**
    * @param AN to set 
    */
   public void setAN( String AN )
   {
      this.AN = AN;
   }

   /**
    * @return the Context
    */
   public String getContext( )
   {
      return Context;
   }

   /**
    * @param Context to set 
    */
   public void setContext( String Context )
   {
      this.Context = Context;
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

   public int loadCtrlMapEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      VN = cursor.getStringFromAttribute( "VN" );  if ( VN == null ) VN = "";
      EN = cursor.getStringFromAttribute( "EN" );  if ( EN == null ) EN = "";
      AN = cursor.getStringFromAttribute( "AN" );  if ( AN == null ) AN = "";
      Context = cursor.getStringFromAttribute( "Context" );  if ( Context == null ) Context = "";
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";

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
   protected String  Register;


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
    * @return the Register
    */
   public String getRegister( )
   {
      return Register;
   }

   /**
    * @param Register to set 
    */
   public void setRegister( String Register )
   {
      this.Register = Register;
   }

   public int loadEventEntityStructure( EntityCursor cursor )
   {
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Register = cursor.getStringFromAttribute( "Register" );  if ( Register == null ) Register = "";

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
   protected String  DO;
   protected String  DLL;
   protected Integer SB;
   protected String  VN;
   protected String  EN;
   protected String  Scope;
   protected Integer AutoGray;
   protected String  NoMap;
   protected Integer Type;
   protected String  DlgN;
   protected String  WndN;
   protected Integer SyncIdx;
   protected Integer OperCtrl;
   protected String  Popup;
   protected String  Prompt;


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
    * @return the DO
    */
   public String getDO( )
   {
      return DO;
   }

   /**
    * @param DO to set 
    */
   public void setDO( String DO )
   {
      this.DO = DO;
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
    * @return the SB
    */
   public Integer getSB( )
   {
      return SB;
   }

   /**
    * @param SB to set 
    */
   public void setSB( Integer SB )
   {
      this.SB = SB;
   }

   /**
    * @return the VN
    */
   public String getVN( )
   {
      return VN;
   }

   /**
    * @param VN to set 
    */
   public void setVN( String VN )
   {
      this.VN = VN;
   }

   /**
    * @return the EN
    */
   public String getEN( )
   {
      return EN;
   }

   /**
    * @param EN to set 
    */
   public void setEN( String EN )
   {
      this.EN = EN;
   }

   /**
    * @return the Scope
    */
   public String getScope( )
   {
      return Scope;
   }

   /**
    * @param Scope to set 
    */
   public void setScope( String Scope )
   {
      this.Scope = Scope;
   }

   /**
    * @return the AutoGray
    */
   public Integer getAutoGray( )
   {
      return AutoGray;
   }

   /**
    * @param AutoGray to set 
    */
   public void setAutoGray( Integer AutoGray )
   {
      this.AutoGray = AutoGray;
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
    * @return the DlgN
    */
   public String getDlgN( )
   {
      return DlgN;
   }

   /**
    * @param DlgN to set 
    */
   public void setDlgN( String DlgN )
   {
      this.DlgN = DlgN;
   }

   /**
    * @return the WndN
    */
   public String getWndN( )
   {
      return WndN;
   }

   /**
    * @param WndN to set 
    */
   public void setWndN( String WndN )
   {
      this.WndN = WndN;
   }

   /**
    * @return the SyncIdx
    */
   public Integer getSyncIdx( )
   {
      return SyncIdx;
   }

   /**
    * @param SyncIdx to set 
    */
   public void setSyncIdx( Integer SyncIdx )
   {
      this.SyncIdx = SyncIdx;
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
    * @return the Popup
    */
   public String getPopup( )
   {
      return Popup;
   }

   /**
    * @param Popup to set 
    */
   public void setPopup( String Popup )
   {
      this.Popup = Popup;
   }

   /**
    * @return the Prompt
    */
   public String getPrompt( )
   {
      return Prompt;
   }

   /**
    * @param Prompt to set 
    */
   public void setPrompt( String Prompt )
   {
      this.Prompt = Prompt;
   }

   public int loadEventActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      DO = cursor.getStringFromAttribute( "DO" );  if ( DO == null ) DO = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      SB = cursor.getIntegerFromAttribute( "SB" );  if ( SB == null ) SB = 0;
      VN = cursor.getStringFromAttribute( "VN" );  if ( VN == null ) VN = "";
      EN = cursor.getStringFromAttribute( "EN" );  if ( EN == null ) EN = "";
      Scope = cursor.getStringFromAttribute( "Scope" );  if ( Scope == null ) Scope = "";
      AutoGray = cursor.getIntegerFromAttribute( "AutoGray" );  if ( AutoGray == null ) AutoGray = 0;
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      DlgN = cursor.getStringFromAttribute( "DlgN" );  if ( DlgN == null ) DlgN = "";
      WndN = cursor.getStringFromAttribute( "WndN" );  if ( WndN == null ) WndN = "";
      SyncIdx = cursor.getIntegerFromAttribute( "SyncIdx" );  if ( SyncIdx == null ) SyncIdx = 0;
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      Popup = cursor.getStringFromAttribute( "Popup" );  if ( Popup == null ) Popup = "";
      Prompt = cursor.getStringFromAttribute( "Prompt" );  if ( Prompt == null ) Prompt = "";

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
   protected String  Accel;


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
    * @return the Accel
    */
   public String getAccel( )
   {
      return Accel;
   }

   /**
    * @param Accel to set 
    */
   public void setAccel( String Accel )
   {
      this.Accel = Accel;
   }

   public int loadWndEventEntityStructure( EntityCursor cursor )
   {
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Accel = cursor.getStringFromAttribute( "Accel" );  if ( Accel == null ) Accel = "";

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
   protected String  DO;
   protected String  DLL;
   protected Integer SB;
   protected String  VN;
   protected String  EN;
   protected String  Scope;
   protected Integer AutoGray;
   protected String  NoMap;
   protected Integer Type;
   protected String  DlgN;
   protected String  WndN;
   protected Integer SyncIdx;
   protected Integer OperCtrl;
   protected String  Popup;
   protected String  Prompt;


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
    * @return the DO
    */
   public String getDO( )
   {
      return DO;
   }

   /**
    * @param DO to set 
    */
   public void setDO( String DO )
   {
      this.DO = DO;
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
    * @return the SB
    */
   public Integer getSB( )
   {
      return SB;
   }

   /**
    * @param SB to set 
    */
   public void setSB( Integer SB )
   {
      this.SB = SB;
   }

   /**
    * @return the VN
    */
   public String getVN( )
   {
      return VN;
   }

   /**
    * @param VN to set 
    */
   public void setVN( String VN )
   {
      this.VN = VN;
   }

   /**
    * @return the EN
    */
   public String getEN( )
   {
      return EN;
   }

   /**
    * @param EN to set 
    */
   public void setEN( String EN )
   {
      this.EN = EN;
   }

   /**
    * @return the Scope
    */
   public String getScope( )
   {
      return Scope;
   }

   /**
    * @param Scope to set 
    */
   public void setScope( String Scope )
   {
      this.Scope = Scope;
   }

   /**
    * @return the AutoGray
    */
   public Integer getAutoGray( )
   {
      return AutoGray;
   }

   /**
    * @param AutoGray to set 
    */
   public void setAutoGray( Integer AutoGray )
   {
      this.AutoGray = AutoGray;
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
    * @return the DlgN
    */
   public String getDlgN( )
   {
      return DlgN;
   }

   /**
    * @param DlgN to set 
    */
   public void setDlgN( String DlgN )
   {
      this.DlgN = DlgN;
   }

   /**
    * @return the WndN
    */
   public String getWndN( )
   {
      return WndN;
   }

   /**
    * @param WndN to set 
    */
   public void setWndN( String WndN )
   {
      this.WndN = WndN;
   }

   /**
    * @return the SyncIdx
    */
   public Integer getSyncIdx( )
   {
      return SyncIdx;
   }

   /**
    * @param SyncIdx to set 
    */
   public void setSyncIdx( Integer SyncIdx )
   {
      this.SyncIdx = SyncIdx;
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
    * @return the Popup
    */
   public String getPopup( )
   {
      return Popup;
   }

   /**
    * @param Popup to set 
    */
   public void setPopup( String Popup )
   {
      this.Popup = Popup;
   }

   /**
    * @return the Prompt
    */
   public String getPrompt( )
   {
      return Prompt;
   }

   /**
    * @param Prompt to set 
    */
   public void setPrompt( String Prompt )
   {
      this.Prompt = Prompt;
   }

   public int loadWndActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      DO = cursor.getStringFromAttribute( "DO" );  if ( DO == null ) DO = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      SB = cursor.getIntegerFromAttribute( "SB" );  if ( SB == null ) SB = 0;
      VN = cursor.getStringFromAttribute( "VN" );  if ( VN == null ) VN = "";
      EN = cursor.getStringFromAttribute( "EN" );  if ( EN == null ) EN = "";
      Scope = cursor.getStringFromAttribute( "Scope" );  if ( Scope == null ) Scope = "";
      AutoGray = cursor.getIntegerFromAttribute( "AutoGray" );  if ( AutoGray == null ) AutoGray = 0;
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      DlgN = cursor.getStringFromAttribute( "DlgN" );  if ( DlgN == null ) DlgN = "";
      WndN = cursor.getStringFromAttribute( "WndN" );  if ( WndN == null ) WndN = "";
      SyncIdx = cursor.getIntegerFromAttribute( "SyncIdx" );  if ( SyncIdx == null ) SyncIdx = 0;
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      Popup = cursor.getStringFromAttribute( "Popup" );  if ( Popup == null ) Popup = "";
      Prompt = cursor.getStringFromAttribute( "Prompt" );  if ( Prompt == null ) Prompt = "";

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

public class ActImpl implements Act
{
   protected String  Tag;
   protected String  DO;
   protected String  DLL;
   protected Integer SB;
   protected String  VN;
   protected String  EN;
   protected String  Scope;
   protected Integer AutoGray;
   protected String  NoMap;
   protected Integer Type;
   protected String  DlgN;
   protected String  WndN;
   protected Integer SyncIdx;
   protected Integer OperCtrl;
   protected String  Popup;
   protected String  Prompt;


   // ctor
   protected ActImpl( EntityCursor cursor )
   {
      loadActEntityStructure( cursor );
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
    * @return the DO
    */
   public String getDO( )
   {
      return DO;
   }

   /**
    * @param DO to set 
    */
   public void setDO( String DO )
   {
      this.DO = DO;
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
    * @return the SB
    */
   public Integer getSB( )
   {
      return SB;
   }

   /**
    * @param SB to set 
    */
   public void setSB( Integer SB )
   {
      this.SB = SB;
   }

   /**
    * @return the VN
    */
   public String getVN( )
   {
      return VN;
   }

   /**
    * @param VN to set 
    */
   public void setVN( String VN )
   {
      this.VN = VN;
   }

   /**
    * @return the EN
    */
   public String getEN( )
   {
      return EN;
   }

   /**
    * @param EN to set 
    */
   public void setEN( String EN )
   {
      this.EN = EN;
   }

   /**
    * @return the Scope
    */
   public String getScope( )
   {
      return Scope;
   }

   /**
    * @param Scope to set 
    */
   public void setScope( String Scope )
   {
      this.Scope = Scope;
   }

   /**
    * @return the AutoGray
    */
   public Integer getAutoGray( )
   {
      return AutoGray;
   }

   /**
    * @param AutoGray to set 
    */
   public void setAutoGray( Integer AutoGray )
   {
      this.AutoGray = AutoGray;
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
    * @return the DlgN
    */
   public String getDlgN( )
   {
      return DlgN;
   }

   /**
    * @param DlgN to set 
    */
   public void setDlgN( String DlgN )
   {
      this.DlgN = DlgN;
   }

   /**
    * @return the WndN
    */
   public String getWndN( )
   {
      return WndN;
   }

   /**
    * @param WndN to set 
    */
   public void setWndN( String WndN )
   {
      this.WndN = WndN;
   }

   /**
    * @return the SyncIdx
    */
   public Integer getSyncIdx( )
   {
      return SyncIdx;
   }

   /**
    * @param SyncIdx to set 
    */
   public void setSyncIdx( Integer SyncIdx )
   {
      this.SyncIdx = SyncIdx;
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
    * @return the Popup
    */
   public String getPopup( )
   {
      return Popup;
   }

   /**
    * @param Popup to set 
    */
   public void setPopup( String Popup )
   {
      this.Popup = Popup;
   }

   /**
    * @return the Prompt
    */
   public String getPrompt( )
   {
      return Prompt;
   }

   /**
    * @param Prompt to set 
    */
   public void setPrompt( String Prompt )
   {
      this.Prompt = Prompt;
   }

   public int loadActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      DO = cursor.getStringFromAttribute( "DO" );  if ( DO == null ) DO = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      SB = cursor.getIntegerFromAttribute( "SB" );  if ( SB == null ) SB = 0;
      VN = cursor.getStringFromAttribute( "VN" );  if ( VN == null ) VN = "";
      EN = cursor.getStringFromAttribute( "EN" );  if ( EN == null ) EN = "";
      Scope = cursor.getStringFromAttribute( "Scope" );  if ( Scope == null ) Scope = "";
      AutoGray = cursor.getIntegerFromAttribute( "AutoGray" );  if ( AutoGray == null ) AutoGray = 0;
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      DlgN = cursor.getStringFromAttribute( "DlgN" );  if ( DlgN == null ) DlgN = "";
      WndN = cursor.getStringFromAttribute( "WndN" );  if ( WndN == null ) WndN = "";
      SyncIdx = cursor.getIntegerFromAttribute( "SyncIdx" );  if ( SyncIdx == null ) SyncIdx = 0;
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      Popup = cursor.getStringFromAttribute( "Popup" );  if ( Popup == null ) Popup = "";
      Prompt = cursor.getStringFromAttribute( "Prompt" );  if ( Prompt == null ) Prompt = "";

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
   protected String  ChkOn;
   protected String  ChkOff;
   protected String  Separator;
   protected Integer DIL;
   protected String  LangID;
   protected Integer NLS;


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
    * @return the ChkOn
    */
   public String getChkOn( )
   {
      return ChkOn;
   }

   /**
    * @param ChkOn to set 
    */
   public void setChkOn( String ChkOn )
   {
      this.ChkOn = ChkOn;
   }

   /**
    * @return the ChkOff
    */
   public String getChkOff( )
   {
      return ChkOff;
   }

   /**
    * @param ChkOff to set 
    */
   public void setChkOff( String ChkOff )
   {
      this.ChkOff = ChkOff;
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
    * @return the DIL
    */
   public Integer getDIL( )
   {
      return DIL;
   }

   /**
    * @param DIL to set 
    */
   public void setDIL( Integer DIL )
   {
      this.DIL = DIL;
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
    * @return the NLS
    */
   public Integer getNLS( )
   {
      return NLS;
   }

   /**
    * @param NLS to set 
    */
   public void setNLS( Integer NLS )
   {
      this.NLS = NLS;
   }

   public int loadActOptEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      AccelTitle = cursor.getStringFromAttribute( "AccelTitle" );  if ( AccelTitle == null ) AccelTitle = "";
      ChkOn = cursor.getStringFromAttribute( "ChkOn" );  if ( ChkOn == null ) ChkOn = "";
      ChkOff = cursor.getStringFromAttribute( "ChkOff" );  if ( ChkOff == null ) ChkOff = "";
      Separator = cursor.getStringFromAttribute( "Separator" );  if ( Separator == null ) Separator = "";
      DIL = cursor.getIntegerFromAttribute( "DIL" );  if ( DIL == null ) DIL = 0;
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";
      NLS = cursor.getIntegerFromAttribute( "NLS" );  if ( NLS == null ) NLS = 0;

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
   protected String  Register;


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
    * @return the Register
    */
   public String getRegister( )
   {
      return Register;
   }

   /**
    * @param Register to set 
    */
   public void setRegister( String Register )
   {
      this.Register = Register;
   }

   public int loadActEventEntityStructure( EntityCursor cursor )
   {
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Register = cursor.getStringFromAttribute( "Register" );  if ( Register == null ) Register = "";

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
   protected Integer Type;
   protected Integer Subtype;
   protected Integer IdNbr;
   protected Integer PSDLG_X;
   protected Integer PSDLG_Y;
   protected Integer SZDLG_X;
   protected Integer SZDLG_Y;
   protected Blob    CtrlBOI;
   protected Blob    DD_BOI;
   protected Blob    EventAct;
   protected String  GUID;
   protected Integer NLS;
   protected Blob    Properties;
   protected String  Script;
   protected String  ScriptDLL;
   protected Integer StyleX;
   protected String  TagPE;
   protected Integer ColorFg;
   protected Integer ColorBk;
   protected Integer DIL;
   protected Integer OptionFlags;
   protected Integer RELCNT_X;
   protected Integer RELCNT_Y;
   protected String  Placeholder;
   protected Blob    LKey;
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
    * @return the DD_BOI
    */
   public Blob getDD_BOI( )
   {
      return DD_BOI;
   }

   /**
    * @param DD_BOI to set 
    */
   public void setDD_BOI( Blob DD_BOI )
   {
      this.DD_BOI = DD_BOI;
   }

   /**
    * @return the EventAct
    */
   public Blob getEventAct( )
   {
      return EventAct;
   }

   /**
    * @param EventAct to set 
    */
   public void setEventAct( Blob EventAct )
   {
      this.EventAct = EventAct;
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
    * @return the NLS
    */
   public Integer getNLS( )
   {
      return NLS;
   }

   /**
    * @param NLS to set 
    */
   public void setNLS( Integer NLS )
   {
      this.NLS = NLS;
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
    * @return the Script
    */
   public String getScript( )
   {
      return Script;
   }

   /**
    * @param Script to set 
    */
   public void setScript( String Script )
   {
      this.Script = Script;
   }

   /**
    * @return the ScriptDLL
    */
   public String getScriptDLL( )
   {
      return ScriptDLL;
   }

   /**
    * @param ScriptDLL to set 
    */
   public void setScriptDLL( String ScriptDLL )
   {
      this.ScriptDLL = ScriptDLL;
   }

   /**
    * @return the StyleX
    */
   public Integer getStyleX( )
   {
      return StyleX;
   }

   /**
    * @param StyleX to set 
    */
   public void setStyleX( Integer StyleX )
   {
      this.StyleX = StyleX;
   }

   /**
    * @return the TagPE
    */
   public String getTagPE( )
   {
      return TagPE;
   }

   /**
    * @param TagPE to set 
    */
   public void setTagPE( String TagPE )
   {
      this.TagPE = TagPE;
   }

   /**
    * @return the ColorFg
    */
   public Integer getColorFg( )
   {
      return ColorFg;
   }

   /**
    * @param ColorFg to set 
    */
   public void setColorFg( Integer ColorFg )
   {
      this.ColorFg = ColorFg;
   }

   /**
    * @return the ColorBk
    */
   public Integer getColorBk( )
   {
      return ColorBk;
   }

   /**
    * @param ColorBk to set 
    */
   public void setColorBk( Integer ColorBk )
   {
      this.ColorBk = ColorBk;
   }

   /**
    * @return the DIL
    */
   public Integer getDIL( )
   {
      return DIL;
   }

   /**
    * @param DIL to set 
    */
   public void setDIL( Integer DIL )
   {
      this.DIL = DIL;
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
    * @return the RELCNT_X
    */
   public Integer getRELCNT_X( )
   {
      return RELCNT_X;
   }

   /**
    * @param RELCNT_X to set 
    */
   public void setRELCNT_X( Integer RELCNT_X )
   {
      this.RELCNT_X = RELCNT_X;
   }

   /**
    * @return the RELCNT_Y
    */
   public Integer getRELCNT_Y( )
   {
      return RELCNT_Y;
   }

   /**
    * @param RELCNT_Y to set 
    */
   public void setRELCNT_Y( Integer RELCNT_Y )
   {
      this.RELCNT_Y = RELCNT_Y;
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
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      Subtype = cursor.getIntegerFromAttribute( "Subtype" );  if ( Subtype == null ) Subtype = 0;
      IdNbr = cursor.getIntegerFromAttribute( "IdNbr" );  if ( IdNbr == null ) IdNbr = 0;
      PSDLG_X = cursor.getIntegerFromAttribute( "PSDLG_X" );  if ( PSDLG_X == null ) PSDLG_X = 0;
      PSDLG_Y = cursor.getIntegerFromAttribute( "PSDLG_Y" );  if ( PSDLG_Y == null ) PSDLG_Y = 0;
      SZDLG_X = cursor.getIntegerFromAttribute( "SZDLG_X" );  if ( SZDLG_X == null ) SZDLG_X = 0;
      SZDLG_Y = cursor.getIntegerFromAttribute( "SZDLG_Y" );  if ( SZDLG_Y == null ) SZDLG_Y = 0;
      CtrlBOI = cursor.getBlobFromAttribute( "CtrlBOI" );
      DD_BOI = cursor.getBlobFromAttribute( "DD_BOI" );
      EventAct = cursor.getBlobFromAttribute( "EventAct" );
      GUID = cursor.getStringFromAttribute( "GUID" );  if ( GUID == null ) GUID = "";
      NLS = cursor.getIntegerFromAttribute( "NLS" );  if ( NLS == null ) NLS = 0;
      Properties = cursor.getBlobFromAttribute( "Properties" );
      Script = cursor.getStringFromAttribute( "Script" );  if ( Script == null ) Script = "";
      ScriptDLL = cursor.getStringFromAttribute( "ScriptDLL" );  if ( ScriptDLL == null ) ScriptDLL = "";
      StyleX = cursor.getIntegerFromAttribute( "StyleX" );  if ( StyleX == null ) StyleX = 0;
      TagPE = cursor.getStringFromAttribute( "TagPE" );  if ( TagPE == null ) TagPE = "";
      ColorFg = cursor.getIntegerFromAttribute( "ColorFg" );  if ( ColorFg == null ) ColorFg = 0;
      ColorBk = cursor.getIntegerFromAttribute( "ColorBk" );  if ( ColorBk == null ) ColorBk = 0;
      DIL = cursor.getIntegerFromAttribute( "DIL" );  if ( DIL == null ) DIL = 0;
      OptionFlags = cursor.getIntegerFromAttribute( "OptionFlags" );  if ( OptionFlags == null ) OptionFlags = 0;
      RELCNT_X = cursor.getIntegerFromAttribute( "RELCNT_X" );  if ( RELCNT_X == null ) RELCNT_X = 0;
      RELCNT_Y = cursor.getIntegerFromAttribute( "RELCNT_Y" );  if ( RELCNT_Y == null ) RELCNT_Y = 0;
      Placeholder = cursor.getStringFromAttribute( "Placeholder" );  if ( Placeholder == null ) Placeholder = "";
      LKey = cursor.getBlobFromAttribute( "LKey" );
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

public class ActHotImpl implements ActHot
{
   protected String  Tag;
   protected String  Title;


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

   public int loadActHotEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Title = cursor.getStringFromAttribute( "Title" );  if ( Title == null ) Title = "";

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
   protected Integer OptCnt;


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
    * @return the OptCnt
    */
   public Integer getOptCnt( )
   {
      return OptCnt;
   }

   /**
    * @param OptCnt to set 
    */
   public void setOptCnt( Integer OptCnt )
   {
      this.OptCnt = OptCnt;
   }

   public int loadMenuEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      OptCnt = cursor.getIntegerFromAttribute( "OptCnt" );  if ( OptCnt == null ) OptCnt = 0;

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

public class OptImpl implements Opt
{
   protected String  Tag;
   protected String  Text;
   protected String  AccelTitle;
   protected String  ChkOn;
   protected String  ChkOff;
   protected String  Separator;
   protected Integer DIL;
   protected String  D_Text;
   protected Integer NLS;
   protected String  LangID;


   // ctor
   protected OptImpl( EntityCursor cursor )
   {
      loadOptEntityStructure( cursor );
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
    * @return the ChkOn
    */
   public String getChkOn( )
   {
      return ChkOn;
   }

   /**
    * @param ChkOn to set 
    */
   public void setChkOn( String ChkOn )
   {
      this.ChkOn = ChkOn;
   }

   /**
    * @return the ChkOff
    */
   public String getChkOff( )
   {
      return ChkOff;
   }

   /**
    * @param ChkOff to set 
    */
   public void setChkOff( String ChkOff )
   {
      this.ChkOff = ChkOff;
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
    * @return the DIL
    */
   public Integer getDIL( )
   {
      return DIL;
   }

   /**
    * @param DIL to set 
    */
   public void setDIL( Integer DIL )
   {
      this.DIL = DIL;
   }

   /**
    * @return the D_Text
    */
   public String getD_Text( )
   {
      return D_Text;
   }

   /**
    * @param D_Text to set 
    */
   public void setD_Text( String D_Text )
   {
      this.D_Text = D_Text;
   }

   /**
    * @return the NLS
    */
   public Integer getNLS( )
   {
      return NLS;
   }

   /**
    * @param NLS to set 
    */
   public void setNLS( Integer NLS )
   {
      this.NLS = NLS;
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

   public int loadOptEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      AccelTitle = cursor.getStringFromAttribute( "AccelTitle" );  if ( AccelTitle == null ) AccelTitle = "";
      ChkOn = cursor.getStringFromAttribute( "ChkOn" );  if ( ChkOn == null ) ChkOn = "";
      ChkOff = cursor.getStringFromAttribute( "ChkOff" );  if ( ChkOff == null ) ChkOff = "";
      Separator = cursor.getStringFromAttribute( "Separator" );  if ( Separator == null ) Separator = "";
      DIL = cursor.getIntegerFromAttribute( "DIL" );  if ( DIL == null ) DIL = 0;
      D_Text = cursor.getStringFromAttribute( "D_Text" );  if ( D_Text == null ) D_Text = "";
      NLS = cursor.getIntegerFromAttribute( "NLS" );  if ( NLS == null ) NLS = 0;
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
   protected String  ChkOn;
   protected String  ChkOff;
   protected String  Separator;
   protected Integer DIL;
   protected Integer NLS;
   protected String  LangID;
   protected String  D_Text;


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
    * @return the ChkOn
    */
   public String getChkOn( )
   {
      return ChkOn;
   }

   /**
    * @param ChkOn to set 
    */
   public void setChkOn( String ChkOn )
   {
      this.ChkOn = ChkOn;
   }

   /**
    * @return the ChkOff
    */
   public String getChkOff( )
   {
      return ChkOff;
   }

   /**
    * @param ChkOff to set 
    */
   public void setChkOff( String ChkOff )
   {
      this.ChkOff = ChkOff;
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
    * @return the DIL
    */
   public Integer getDIL( )
   {
      return DIL;
   }

   /**
    * @param DIL to set 
    */
   public void setDIL( Integer DIL )
   {
      this.DIL = DIL;
   }

   /**
    * @return the NLS
    */
   public Integer getNLS( )
   {
      return NLS;
   }

   /**
    * @param NLS to set 
    */
   public void setNLS( Integer NLS )
   {
      this.NLS = NLS;
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
    * @return the D_Text
    */
   public String getD_Text( )
   {
      return D_Text;
   }

   /**
    * @param D_Text to set 
    */
   public void setD_Text( String D_Text )
   {
      this.D_Text = D_Text;
   }

   public int loadOptOptEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";
      AccelTitle = cursor.getStringFromAttribute( "AccelTitle" );  if ( AccelTitle == null ) AccelTitle = "";
      ChkOn = cursor.getStringFromAttribute( "ChkOn" );  if ( ChkOn == null ) ChkOn = "";
      ChkOff = cursor.getStringFromAttribute( "ChkOff" );  if ( ChkOff == null ) ChkOff = "";
      Separator = cursor.getStringFromAttribute( "Separator" );  if ( Separator == null ) Separator = "";
      DIL = cursor.getIntegerFromAttribute( "DIL" );  if ( DIL == null ) DIL = 0;
      NLS = cursor.getIntegerFromAttribute( "NLS" );  if ( NLS == null ) NLS = 0;
      LangID = cursor.getStringFromAttribute( "LangID" );  if ( LangID == null ) LangID = "";
      D_Text = cursor.getStringFromAttribute( "D_Text" );  if ( D_Text == null ) D_Text = "";

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
   protected String  DO;
   protected String  DLL;
   protected Integer SB;
   protected String  VN;
   protected String  EN;
   protected String  Scope;
   protected Integer AutoGray;
   protected String  NoMap;
   protected Integer Type;
   protected String  DlgN;
   protected String  WndN;
   protected Integer SyncIdx;
   protected Integer OperCtrl;
   protected String  Popup;
   protected String  Prompt;


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
    * @return the DO
    */
   public String getDO( )
   {
      return DO;
   }

   /**
    * @param DO to set 
    */
   public void setDO( String DO )
   {
      this.DO = DO;
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
    * @return the SB
    */
   public Integer getSB( )
   {
      return SB;
   }

   /**
    * @param SB to set 
    */
   public void setSB( Integer SB )
   {
      this.SB = SB;
   }

   /**
    * @return the VN
    */
   public String getVN( )
   {
      return VN;
   }

   /**
    * @param VN to set 
    */
   public void setVN( String VN )
   {
      this.VN = VN;
   }

   /**
    * @return the EN
    */
   public String getEN( )
   {
      return EN;
   }

   /**
    * @param EN to set 
    */
   public void setEN( String EN )
   {
      this.EN = EN;
   }

   /**
    * @return the Scope
    */
   public String getScope( )
   {
      return Scope;
   }

   /**
    * @param Scope to set 
    */
   public void setScope( String Scope )
   {
      this.Scope = Scope;
   }

   /**
    * @return the AutoGray
    */
   public Integer getAutoGray( )
   {
      return AutoGray;
   }

   /**
    * @param AutoGray to set 
    */
   public void setAutoGray( Integer AutoGray )
   {
      this.AutoGray = AutoGray;
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
    * @return the DlgN
    */
   public String getDlgN( )
   {
      return DlgN;
   }

   /**
    * @param DlgN to set 
    */
   public void setDlgN( String DlgN )
   {
      this.DlgN = DlgN;
   }

   /**
    * @return the WndN
    */
   public String getWndN( )
   {
      return WndN;
   }

   /**
    * @param WndN to set 
    */
   public void setWndN( String WndN )
   {
      this.WndN = WndN;
   }

   /**
    * @return the SyncIdx
    */
   public Integer getSyncIdx( )
   {
      return SyncIdx;
   }

   /**
    * @param SyncIdx to set 
    */
   public void setSyncIdx( Integer SyncIdx )
   {
      this.SyncIdx = SyncIdx;
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
    * @return the Popup
    */
   public String getPopup( )
   {
      return Popup;
   }

   /**
    * @param Popup to set 
    */
   public void setPopup( String Popup )
   {
      this.Popup = Popup;
   }

   /**
    * @return the Prompt
    */
   public String getPrompt( )
   {
      return Prompt;
   }

   /**
    * @param Prompt to set 
    */
   public void setPrompt( String Prompt )
   {
      this.Prompt = Prompt;
   }

   public int loadOptActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      DO = cursor.getStringFromAttribute( "DO" );  if ( DO == null ) DO = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      SB = cursor.getIntegerFromAttribute( "SB" );  if ( SB == null ) SB = 0;
      VN = cursor.getStringFromAttribute( "VN" );  if ( VN == null ) VN = "";
      EN = cursor.getStringFromAttribute( "EN" );  if ( EN == null ) EN = "";
      Scope = cursor.getStringFromAttribute( "Scope" );  if ( Scope == null ) Scope = "";
      AutoGray = cursor.getIntegerFromAttribute( "AutoGray" );  if ( AutoGray == null ) AutoGray = 0;
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      DlgN = cursor.getStringFromAttribute( "DlgN" );  if ( DlgN == null ) DlgN = "";
      WndN = cursor.getStringFromAttribute( "WndN" );  if ( WndN == null ) WndN = "";
      SyncIdx = cursor.getIntegerFromAttribute( "SyncIdx" );  if ( SyncIdx == null ) SyncIdx = 0;
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      Popup = cursor.getStringFromAttribute( "Popup" );  if ( Popup == null ) Popup = "";
      Prompt = cursor.getStringFromAttribute( "Prompt" );  if ( Prompt == null ) Prompt = "";

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
   protected String  VN;
   protected String  EN;
   protected String  AN;
   protected String  Context;
   protected String  Type;


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
    * @return the VN
    */
   public String getVN( )
   {
      return VN;
   }

   /**
    * @param VN to set 
    */
   public void setVN( String VN )
   {
      this.VN = VN;
   }

   /**
    * @return the EN
    */
   public String getEN( )
   {
      return EN;
   }

   /**
    * @param EN to set 
    */
   public void setEN( String EN )
   {
      this.EN = EN;
   }

   /**
    * @return the AN
    */
   public String getAN( )
   {
      return AN;
   }

   /**
    * @param AN to set 
    */
   public void setAN( String AN )
   {
      this.AN = AN;
   }

   /**
    * @return the Context
    */
   public String getContext( )
   {
      return Context;
   }

   /**
    * @param Context to set 
    */
   public void setContext( String Context )
   {
      this.Context = Context;
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

   public int loadOptMapEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      VN = cursor.getStringFromAttribute( "VN" );  if ( VN == null ) VN = "";
      EN = cursor.getStringFromAttribute( "EN" );  if ( EN == null ) EN = "";
      AN = cursor.getStringFromAttribute( "AN" );  if ( AN == null ) AN = "";
      Context = cursor.getStringFromAttribute( "Context" );  if ( Context == null ) Context = "";
      Type = cursor.getStringFromAttribute( "Type" );  if ( Type == null ) Type = "";

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

public class SubtaskImpl implements Subtask
{
   protected Integer CPP;


   // ctor
   protected SubtaskImpl( EntityCursor cursor )
   {
      loadSubtaskEntityStructure( cursor );
   }

   /**
    * @return the CPP
    */
   public Integer getCPP( )
   {
      return CPP;
   }

   /**
    * @param CPP to set 
    */
   public void setCPP( Integer CPP )
   {
      this.CPP = CPP;
   }

   public int loadSubtaskEntityStructure( EntityCursor cursor )
   {
      CPP = cursor.getIntegerFromAttribute( "CPP" );  if ( CPP == null ) CPP = 0;

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
   protected String  Title;


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

   public int loadHotkeyEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      Title = cursor.getStringFromAttribute( "Title" );  if ( Title == null ) Title = "";

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
   protected String  DO;
   protected String  DLL;
   protected Integer SB;
   protected String  VN;
   protected String  EN;
   protected String  Scope;
   protected Integer AutoGray;
   protected String  NoMap;
   protected Integer Type;
   protected String  DlgN;
   protected String  WndN;
   protected Integer SyncIdx;
   protected Integer OperCtrl;
   protected String  Popup;
   protected String  Prompt;


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
    * @return the DO
    */
   public String getDO( )
   {
      return DO;
   }

   /**
    * @param DO to set 
    */
   public void setDO( String DO )
   {
      this.DO = DO;
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
    * @return the SB
    */
   public Integer getSB( )
   {
      return SB;
   }

   /**
    * @param SB to set 
    */
   public void setSB( Integer SB )
   {
      this.SB = SB;
   }

   /**
    * @return the VN
    */
   public String getVN( )
   {
      return VN;
   }

   /**
    * @param VN to set 
    */
   public void setVN( String VN )
   {
      this.VN = VN;
   }

   /**
    * @return the EN
    */
   public String getEN( )
   {
      return EN;
   }

   /**
    * @param EN to set 
    */
   public void setEN( String EN )
   {
      this.EN = EN;
   }

   /**
    * @return the Scope
    */
   public String getScope( )
   {
      return Scope;
   }

   /**
    * @param Scope to set 
    */
   public void setScope( String Scope )
   {
      this.Scope = Scope;
   }

   /**
    * @return the AutoGray
    */
   public Integer getAutoGray( )
   {
      return AutoGray;
   }

   /**
    * @param AutoGray to set 
    */
   public void setAutoGray( Integer AutoGray )
   {
      this.AutoGray = AutoGray;
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
    * @return the DlgN
    */
   public String getDlgN( )
   {
      return DlgN;
   }

   /**
    * @param DlgN to set 
    */
   public void setDlgN( String DlgN )
   {
      this.DlgN = DlgN;
   }

   /**
    * @return the WndN
    */
   public String getWndN( )
   {
      return WndN;
   }

   /**
    * @param WndN to set 
    */
   public void setWndN( String WndN )
   {
      this.WndN = WndN;
   }

   /**
    * @return the SyncIdx
    */
   public Integer getSyncIdx( )
   {
      return SyncIdx;
   }

   /**
    * @param SyncIdx to set 
    */
   public void setSyncIdx( Integer SyncIdx )
   {
      this.SyncIdx = SyncIdx;
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
    * @return the Popup
    */
   public String getPopup( )
   {
      return Popup;
   }

   /**
    * @param Popup to set 
    */
   public void setPopup( String Popup )
   {
      this.Popup = Popup;
   }

   /**
    * @return the Prompt
    */
   public String getPrompt( )
   {
      return Prompt;
   }

   /**
    * @param Prompt to set 
    */
   public void setPrompt( String Prompt )
   {
      this.Prompt = Prompt;
   }

   public int loadHotActEntityStructure( EntityCursor cursor )
   {
      Tag = cursor.getStringFromAttribute( "Tag" );  if ( Tag == null ) Tag = "";
      DO = cursor.getStringFromAttribute( "DO" );  if ( DO == null ) DO = "";
      DLL = cursor.getStringFromAttribute( "DLL" );  if ( DLL == null ) DLL = "";
      SB = cursor.getIntegerFromAttribute( "SB" );  if ( SB == null ) SB = 0;
      VN = cursor.getStringFromAttribute( "VN" );  if ( VN == null ) VN = "";
      EN = cursor.getStringFromAttribute( "EN" );  if ( EN == null ) EN = "";
      Scope = cursor.getStringFromAttribute( "Scope" );  if ( Scope == null ) Scope = "";
      AutoGray = cursor.getIntegerFromAttribute( "AutoGray" );  if ( AutoGray == null ) AutoGray = 0;
      NoMap = cursor.getStringFromAttribute( "NoMap" );  if ( NoMap == null ) NoMap = "";
      Type = cursor.getIntegerFromAttribute( "Type" );  if ( Type == null ) Type = 0;
      DlgN = cursor.getStringFromAttribute( "DlgN" );  if ( DlgN == null ) DlgN = "";
      WndN = cursor.getStringFromAttribute( "WndN" );  if ( WndN == null ) WndN = "";
      SyncIdx = cursor.getIntegerFromAttribute( "SyncIdx" );  if ( SyncIdx == null ) SyncIdx = 0;
      OperCtrl = cursor.getIntegerFromAttribute( "OperCtrl" );  if ( OperCtrl == null ) OperCtrl = 0;
      Popup = cursor.getStringFromAttribute( "Popup" );  if ( Popup == null ) Popup = "";
      Prompt = cursor.getStringFromAttribute( "Prompt" );  if ( Prompt == null ) Prompt = "";

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

public class DILImpl implements DIL
{
   protected String  Msg;
   protected String  D_Msg;


   // ctor
   protected DILImpl( EntityCursor cursor )
   {
      loadDILEntityStructure( cursor );
   }

   /**
    * @return the Msg
    */
   public String getMsg( )
   {
      return Msg;
   }

   /**
    * @param Msg to set 
    */
   public void setMsg( String Msg )
   {
      this.Msg = Msg;
   }

   /**
    * @return the D_Msg
    */
   public String getD_Msg( )
   {
      return D_Msg;
   }

   /**
    * @param D_Msg to set 
    */
   public void setD_Msg( String D_Msg )
   {
      this.D_Msg = D_Msg;
   }

   public int loadDILEntityStructure( EntityCursor cursor )
   {
      Msg = cursor.getStringFromAttribute( "Msg" );  if ( Msg == null ) Msg = "";
      D_Msg = cursor.getStringFromAttribute( "D_Msg" );  if ( D_Msg == null ) D_Msg = "";

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

public class NLS_DIL_TextImpl implements NLS_DIL_Text
{
   protected Integer LI;
   protected String  Text;


   // ctor
   protected NLS_DIL_TextImpl( EntityCursor cursor )
   {
      loadNLS_DIL_TextEntityStructure( cursor );
   }

   /**
    * @return the LI
    */
   public Integer getLI( )
   {
      return LI;
   }

   /**
    * @param LI to set 
    */
   public void setLI( Integer LI )
   {
      this.LI = LI;
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

   public int loadNLS_DIL_TextEntityStructure( EntityCursor cursor )
   {
      LI = cursor.getIntegerFromAttribute( "LI" );  if ( LI == null ) LI = 0;
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";

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

public class NLS_TextImpl implements NLS_Text
{
   protected Integer LI;
   protected String  Text;


   // ctor
   protected NLS_TextImpl( EntityCursor cursor )
   {
      loadNLS_TextEntityStructure( cursor );
   }

   /**
    * @return the LI
    */
   public Integer getLI( )
   {
      return LI;
   }

   /**
    * @param LI to set 
    */
   public void setLI( Integer LI )
   {
      this.LI = LI;
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

   public int loadNLS_TextEntityStructure( EntityCursor cursor )
   {
      LI = cursor.getIntegerFromAttribute( "LI" );  if ( LI == null ) LI = 0;
      Text = cursor.getStringFromAttribute( "Text" );  if ( Text == null ) Text = "";

      return 0;
   }

}


