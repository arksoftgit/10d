////////////////////////////////////////////////////////////////////////////
// File:    ZCrystalEditView.h
// Version: 1.0.0.0
// Created: 29-Dec-1998
//
// Author:     Stcherbatchenko Andrei
// E-mail:     windfall@gmx.de
//
// Interface of the ZCrystalEditView class, a part of Crystal Edit -
// syntax coloring text editor.
//
// You are free to use or modify this code to the following restrictions:
// - Acknowledge me somewhere in your about box, simple "Parts of code by.."
// will be enough. If you can't (or don't want to), contact me personally.
// - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

extern "C"
{
AFX_EXT_API
CWnd * OPERATION
EditorControl( ZSubtask *pZSubtask,
               CWnd     *pWndParent,
               ZMapAct  *pzmaComposite,
               zVIEW    vDialog,
               zSHORT   nOffsetX,
               zSHORT   nOffsetY,
               zKZWDLGXO_Ctrl_DEF *pCtrlDef );
}

/////////////////////////////////////////////////////////////////////////////
// Forward class declarations

class ZCrystalEditView;
class ZCrystalTextBuffer;
class ZUpdateContext;
class ZEditDropTargetImpl;


////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView class declaration

// ZCrystalEditView::FindText() flags
enum
{
   FIND_FORWARD      = 0x0000,
   FIND_MATCH_CASE   = 0x0001,
   FIND_WHOLE_WORD   = 0x0002,
   FIND_DIRECTION_UP = 0x0010,
   REPLACE_SELECTION = 0x0100
};

// ZCrystalEditView::UpdateView() flags
enum
{
   UPDATE_HORZRANGE  = 0x0001,      // update horz scrollbar
   UPDATE_VERTRANGE  = 0x0002,      // update vert scrollbar
   UPDATE_SINGLELINE = 0x0100,      // single line has changed
   UPDATE_FLAGSONLY  = 0x0200,      // only line-flags were changed
   UPDATE_RESET      = 0x1000       // document was reloaded, update all!
};

/////////////////////////////////////////////////////////////////////////////
// ZCrystalEditView view

class ZDCTL_CLASS ZCrystalEditView : public CView, public ZMapAct
{
   DECLARE_DYNAMIC(ZCrystalEditView)

public:
   ZCrystalEditView( ZSubtask *pZSubtask,
                     CWnd     *pWndParent,
                     ZMapAct  *pzmaComposite,
                     zVIEW    vDialog,
                     zSHORT   nOffsetX,
                     zSHORT   nOffsetY,
                     zKZWDLGXO_Ctrl_DEF *pCtrlDef );
   ~ZCrystalEditView();
   void CreateZ();
   friend ZEditDropTargetImpl;

private:
   CLIPFORMAT m_cfFormat;
   BOOL   m_bOvrMode;
   BOOL   m_bDropPosVisible;
   CPoint m_ptSavedCaretPos;
   CPoint m_ptDropPos;
   BOOL   m_bSelectionPushed;
   CPoint m_ptSavedSelStart;
   CPoint m_ptSavedSelEnd;
   BOOL   m_bAutoIndent;
   BOOL   m_bDisableBSAtSOL;      // [JRT] Disable Back Space At Start Of Line
   int    m_nHoldArrowXPos;
   UINT   m_uLastKey;

protected:
   ZEditDropTargetImpl *m_pOleDropTarget;
   virtual DROPEFFECT GetDropEffect();
   virtual void OnDropSource(DROPEFFECT de);
   virtual void ResetView();

// Implementation
protected:

private:
   BOOL m_bCursorHidden;

   // Painting caching bitmap
   CBitmap *m_pCacheBitmap;

   // Line/character dimensions
   int m_nLineHeight;
   int m_nCharWidth;
   void CalcLineCharDim();

   // Text attributes
   int m_nTabSize;
   BOOL m_bViewTabs;
   BOOL m_bSelMargin;

   // Amount of lines/characters that completely fits the client area
   int m_nScreenLines;
   int m_nScreenChars;

   int m_nMaxLineLength;
   int m_nIdealCharPos;

   BOOL m_bFocused;
   CPoint m_ptAnchor;
   LOGFONT m_lfBaseFont;
   CFont *m_apFonts[4];

   // Parsing stuff
   DWORD *m_pdwParseCookies;
   int m_nParseArraySize;
   DWORD GetParseCookie(int nLineIndex);

   // Pre-calculated line lengths (in characters)
   int m_nActualLengthArraySize;
   int *m_pnActualLineLength;

   BOOL m_bPreparingToDrag;
   BOOL m_bDraggingText;
   BOOL m_bDragSelection;
   BOOL m_bWordSelection;
   BOOL m_bLineSelection;
   UINT m_nDragSelTimer;
   CPoint WordToRight(CPoint pt);
   CPoint WordToLeft(CPoint pt);

   CPoint m_ptDrawSelStart, m_ptDrawSelEnd;
   CPoint m_ptSelStart, m_ptSelEnd;
   void PrepareSelBounds();

   // Helper functions
   void ExpandChars(LPCTSTR pszChars, int nOffset, int nCount, CString &line);
   BOOL ClipCursorToClient();
   int  ApproxActualOffset(int nLineIndex, int nOffset);
   void AdjustTextPoint(CPoint &point);
   void DrawLineHelperImpl(CDC *pdc, CPoint &ptOrigin, const CRect &rcClip,
                           LPCTSTR pszChars, int nOffset, int nCount);
   BOOL IsInsideSelBlock(CPoint ptTextPos);

   BOOL m_bBookmarkExist;     // More bookmarks

public:
   ZCrystalTextBuffer *m_pTextBuffer;  // moved from protected
   CString m_csLastFindWhat;
   CToolBar m_wndToolBar;
   // Search parameters
   BOOL m_bLastSearch;  // moved from private
   DWORD m_dwLastSearchFlags;  // moved from private
   BOOL m_bMultipleSearch;  // More search ... moved from private
   CPoint m_ptCursorPos;  // moved from private

protected:
   CImageList *m_pIcons;
   HACCEL m_hAccel;
   BOOL m_bVertScrollBarLocked, m_bHorzScrollBarLocked;
   CPoint m_ptDraggedTextBegin, m_ptDraggedTextEnd;
   void SetAnchor(CPoint &ptNewAnchor);
   int GetMarginWidth();

   BOOL m_bShowInactiveSelection;
   // [JRT]
   BOOL m_bDisabledDragAndDrop;

   CPoint ClientToText(CPoint &point);
   CPoint TextToClient(CPoint &point);
   void InvalidateLines(int nLine1, int nLine2, BOOL bInvalidateMargin = FALSE);
   int CalculateActualOffset(int nLineIndex, int nCharIndex);

   // Printing
   int m_nPrintPages;
   int *m_pnPages;
   CFont *m_pPrintFont;
   int m_nPrintLineHeight;
   BOOL m_bPrintHeader, m_bPrintFooter;
   CRect m_ptPageArea, m_rcPrintArea;
   int PrintLineHeight(CDC *pdc, int nLine);
   void RecalcPageLayouts(CDC *pdc, CPrintInfo *pInfo);
   virtual void PrintHeader(CDC *pdc, int nPageNum);
   virtual void PrintFooter(CDC *pdc, int nPageNum);
   virtual void GetPrintHeaderText(int nPageNum, CString &text);
   virtual void GetPrintFooterText(int nPageNum, CString &text);

   // Keyboard handlers
   void MoveLeft(BOOL bSelect);
   void MoveRight(BOOL bSelect);
   void MoveWordLeft(BOOL bSelect);
   void MoveWordRight(BOOL bSelect);
   void MoveUp(BOOL bSelect);
   void MoveDown(BOOL bSelect);
   void MoveHome(BOOL bSelect);
   void MoveEnd(BOOL bSelect);
   void MovePgUp(BOOL bSelect);
   void MovePgDn(BOOL bSelect);
   void MoveCtrlHome(BOOL bSelect);
   void MoveCtrlEnd(BOOL bSelect);

   BOOL IsInsideSelection(CPoint &ptTextPos);

   int m_nTopLine, m_nOffsetChar;
   BOOL m_bSmoothScroll;

   int GetMaxLineLength();
   int GetScreenLines();
   int GetScreenChars();
   CFont *GetFont(CDC *pdc, BOOL bItalic = FALSE, BOOL bBold = FALSE);
   int GetFontSize( CDC *pdc, int nFontHeight );

   void RecalcVertScrollBar(BOOL bPositionOnly = FALSE);
   void RecalcHorzScrollBar(BOOL bPositionOnly = FALSE);

   // Scrolling helpers
   void ScrollToChar(int nNewOffsetChar, BOOL bNoSmoothScroll = FALSE, BOOL bTrackScrollBar = TRUE);
   void ScrollToLine(int nNewTopLine, BOOL bNoSmoothScroll = FALSE, BOOL bTrackScrollBar = TRUE);

   // Splitter support
   virtual void UpdateSiblingScrollPos(BOOL bHorz);
   virtual void OnUpdateSibling(ZCrystalEditView *pUpdateSource, BOOL bHorz);
   ZCrystalEditView *GetSiblingView(int nRow, int nCol);

   virtual int GetLineActualLength(int nLineIndex);
   virtual DWORD GetLineFlags(int nLineIndex);

   // Clipboard overridable
   virtual BOOL TextInClipboard();
   virtual BOOL PutToClipboard(LPCTSTR pszText);
   virtual BOOL GetFromClipboard(CString &text);

   // Drag-n-drop overrideable
   virtual HGLOBAL PrepareDragData();

   BOOL IsDraggingText() const;

   virtual COLORREF GetColor(int nColorIndex);
   virtual void GetLineColors(int nLineIndex, COLORREF &crBkgnd,
                              COLORREF &crText, BOOL &bDrawWhitespace);
   virtual BOOL GetItalic(int nColorIndex);
   virtual BOOL GetBold(int nColorIndex);

   void DrawLineHelper(CDC *pdc, CPoint &ptOrigin, const CRect &rcClip, int nColorIndex,
                       LPCTSTR pszChars, int nOffset, int nCount, CPoint ptTextPos);
   virtual void DrawSingleLine(CDC *pdc, const CRect &rect, int nLineIndex);
   virtual void DrawMargin(CDC *pdc, const CRect &rect, int nLineIndex);

   // Syntax coloring overrides
   struct TEXTBLOCK
   {
      int m_nCharPos;
      int m_nColorIndex;
   };

   virtual DWORD ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems);
   virtual BOOL ZCrystalEditView::IsKeyword(LPCTSTR pszChars, int nLth);
   virtual HINSTANCE GetResourceHandle();

// Operations
public:
   virtual void OnInitialUpdate();   // moved to public ... called first time after construct
   BOOL CanPaste();
   BOOL CanUndo();
   BOOL CanRedo();
   void Cut();  // moved to public
   void Copy();  // moved to public
   void Paste();  // moved to public
   void SelectAllLines();  // moved to public
   virtual int GetLineCount();  // moved to public
   virtual int GetLineLength(int nLineIndex);  // moved to public
   virtual LPCTSTR GetLineChars(int nLineIndex);  // moved to public
   virtual void GetText(CPoint &ptStart, CPoint &ptEnd, CString &text);  // moved to public
   BOOL DeleteCurrentSelection();  // moved to public
   int  GetLineHeight();  // moved to public
   int  GetCharWidth();  // moved to public
   void Delete();
   void Undo();
   void Redo();
   int  EditFind();
   int  EditReplace();
   int  EditRepeat();
   int  EditFindPrevious();
   int  IsInComment(int nLine, int nCol);
   void GoToBookmark( int nBookmarkID );
   void GoToNextBookmark();
   void GoToPreviousBookmark();
   void ToggleBookmark();
   void ToggleBookmark( int nBookmarkID );
   void SetBookmark( int nBookmarkID );
   void ClearAllBookmarks();
   void GetSelection(CPoint &ptStart, CPoint &ptEnd);  // moved to public
   void SetSelection(CPoint &ptStart, CPoint &ptEnd);  // moved to public
   void UpdateCaret();  // moved to public
   void PageUp();
   void PageDown();

   BOOL GetAutoIndent() const;
   void SetAutoIndent(BOOL bAutoIndent);

   // [JRT]
   void SetDisableBSAtSOL(BOOL bDisableBSAtSOL);
   BOOL GetDisableBSAtSOL() const;

   BOOL GetOverwriteMode() const;
   void SetOverwriteMode(BOOL bOvrMode = TRUE);

   void ShowDropIndicator(CPoint &point);
   void HideDropIndicator();

   BOOL DoDropText(COleDataObject *pDataObject, CPoint &ptClient);
   void DoDragScroll(CPoint &point);

   virtual BOOL QueryEditable();
   virtual void UpdateView(ZCrystalEditView *pSource, ZUpdateContext *pContext, DWORD dwFlags, int nLineIndex = -1);

   BOOL ReplaceSelection(LPCTSTR pszNewText);

   // Overridable: an opportunity for Auto-Indent, Smart-Indent etc.
   virtual void OnEditOperation(int nAction, LPCTSTR pszText);

   BOOL IsSelection();  // moved from protected

   BOOL GetViewTabs();
   void SetViewTabs(BOOL bViewTabs);
   int  GetTabSize();
   void SetTabSize(int nTabSize);
   BOOL GetSelectionMargin();
   void SetSelectionMargin(BOOL bSelMargin);
   void GetFont(LOGFONT &lf);
   void SetFont(const LOGFONT &lf);
   BOOL GetSmoothScroll() const;
   void SetSmoothScroll(BOOL bSmoothScroll);
   // [JRT]:
   BOOL GetDisableDragAndDrop() const;
   void SetDisableDragAndDrop(BOOL bDDAD);

   void AttachToBuffer(ZCrystalTextBuffer *pBuf = NULL);
   void DetachFromBuffer();

   // Buffer-view interaction, multiple views
   virtual ZCrystalTextBuffer *LocateTextBuffer();

   // Attributes
   CPoint GetCursorPos();
   void SetCursorPos(CPoint &ptCursorPos);
   void ShowCursor();
   void HideCursor();

   // Operations
   void EnsureVisible(CPoint pt);

   // Text search helpers
   int FindText(LPCTSTR pszText, CPoint &ptStartPos, DWORD dwFlags, BOOL bWrapSearch, CPoint *pptFoundPos);
   int FindTextInBlock(LPCTSTR pszText, CPoint &ptStartPos, CPoint &ptBlockBegin, CPoint &ptBlockEnd,
                       DWORD dwFlags, BOOL bWrapSearch, CPoint *pptFoundPos);
   BOOL HighlightText(CPoint &ptStartPos, int nLth);

   // Default handle to resources
   static HINSTANCE s_hResourceInst;

   enum
   {
      // Base colors
      COLORINDEX_WHITESPACE,
      COLORINDEX_BKGND,
      COLORINDEX_NORMALTEXT,
      COLORINDEX_SELMARGIN,
      COLORINDEX_SELBKGND,
      COLORINDEX_SELTEXT,
      // Syntax colors
      COLORINDEX_KEYWORD,
      COLORINDEX_COMMENT,
      COLORINDEX_NUMBER,
      COLORINDEX_OPERATOR,      // [JRT]:
      COLORINDEX_STRING,
      COLORINDEX_PREPROCESSOR,
      // Compiler/debugger colors
      COLORINDEX_ERRORBKGND,
      COLORINDEX_ERRORTEXT,
      COLORINDEX_EXECUTIONBKGND,
      COLORINDEX_EXECUTIONTEXT,
      COLORINDEX_BREAKPOINTBKGND,
      COLORINDEX_BREAKPOINTTEXT
      // ...
      // Expandable: custom elements are allowed.
   };

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ZCrystalEditView)
public:
   virtual void OnDraw(CDC *pdc);  // overridden to draw this view
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL PreTranslateMessage(MSG *pMsg);
   virtual void OnPrepareDC(CDC *pdc, CPrintInfo *pInfo = NULL);
protected:
   virtual BOOL OnPreparePrinting(CPrintInfo *pInfo);
   virtual void OnBeginPrinting(CDC *pdc, CPrintInfo *pInfo);
   virtual void OnEndPrinting(CDC *pdc, CPrintInfo *pInfo);
   virtual void OnPrint(CDC *pdc, CPrintInfo *pInfo);
   //}}AFX_VIRTUAL

// Implementation
public:

protected:

// Generated message map functions
protected:
#ifdef _DEBUG
   void AssertValidTextPos(CPoint &pt, BOOL bResetInvalid = FALSE);
#endif

   //{{AFX_MSG(ZCrystalEditView)
// afx_msg void OnBnClickedToggleBookmark(NMHDR *n,LRESULT *);
   afx_msg LRESULT OnGetToolTipText( WPARAM wParam, LPARAM lParam );
   afx_msg void OnDestroy();
   afx_msg BOOL OnEraseBkgnd(CDC *pdc);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
   afx_msg BOOL OnMouseWheel( UINT uFlags, short nDelta, CPoint point );
   afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
   afx_msg void OnLButtonDown(UINT uFlags, CPoint point);
   afx_msg void OnSetFocus(CWnd *pOldWnd);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
   afx_msg void OnLButtonUp(UINT uFlags, CPoint point);
   afx_msg void OnMouseMove(UINT uFlags, CPoint point);
   afx_msg void OnTimer(UINT nIDEvent);
   afx_msg void OnKillFocus(CWnd *pNewWnd);
   afx_msg void OnLButtonDblClk(UINT uFlags, CPoint point);
   afx_msg void OnEditCopy();
   afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
   afx_msg void OnEditSelectAll();
   afx_msg void OnUpdateEditSelectAll(CCmdUI *pCmdUI);
   afx_msg void OnRButtonDown(UINT uFlags, CPoint point);
   afx_msg void OnRButtonUp(UINT uFlags, CPoint point);
   afx_msg void OnSysColorChange();
   afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnEditFind();
   afx_msg void OnEditReplace();
   afx_msg void OnEditRepeat();
   afx_msg void OnEditFindPrevious();
   afx_msg void OnUpdateEditRepeat(CCmdUI *pCmdUI);
   afx_msg void OnUpdateEditFindPrevious(CCmdUI *pCmdUI);
   afx_msg void OnEditPaste();
   afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
   afx_msg void OnEditCut();
   afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
   afx_msg void OnEditDelete();
   afx_msg void OnSysKeyDown( UINT uKey, UINT uRepeatCnt, UINT uFlags );
   afx_msg void OnSysKeyUp( UINT uKey, UINT uRepeatCnt, UINT uFlags );
   afx_msg void OnKeyDown( UINT uKey, UINT uRepeatCnt, UINT uFlags );
   afx_msg void OnKeyUp( UINT uKey, UINT uRepeatCnt, UINT uFlags );
   afx_msg void OnChar( UINT nChar, UINT uRepeatCnt, UINT uFlags );
   afx_msg UINT OnGetDlgCode();
   afx_msg void OnEditDeleteBack();
   afx_msg void OnEditUntab();
   afx_msg void OnEditTab();
   afx_msg void OnEditSwitchOvrmode();
   afx_msg void OnUpdateEditSwitchOvrmode(CCmdUI *pCmdUI);

   afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
   afx_msg void OnEditUndo();
   afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
   afx_msg void OnEditRedo();
   //}}AFX_MSG
   afx_msg void OnFileNew();
   afx_msg void OnFileOpen();
   afx_msg void OnFileSave();
   afx_msg void OnFilePageSetup();

   afx_msg void OnCharLeft();
   afx_msg void OnExtCharLeft();
   afx_msg void OnCharRight();
   afx_msg void OnExtCharRight();
   afx_msg void OnWordLeft();
   afx_msg void OnExtWordLeft();
   afx_msg void OnWordRight();
   afx_msg void OnExtWordRight();
   afx_msg void OnLineUp();
   afx_msg void OnExtLineUp();
   afx_msg void OnLineDown();
   afx_msg void OnExtLineDown();
   afx_msg void OnPageUp();
   afx_msg void OnExtPageUp();
   afx_msg void OnPageDown();
   afx_msg void OnExtPageDown();
   afx_msg void OnLineEnd();
   afx_msg void OnExtLineEnd();
   afx_msg void OnHome();
   afx_msg void OnExtHome();
   afx_msg void OnTextBegin();
   afx_msg void OnExtTextBegin();
   afx_msg void OnTextEnd();
   afx_msg void OnExtTextEnd();
   afx_msg void OnUpdateIndicatorCRLF(CCmdUI *pCmdUI);
   afx_msg void OnUpdateIndicatorPosition(CCmdUI *pCmdUI);
   afx_msg void OnToggleBookmarkID(UINT nCmdID);
   afx_msg void OnGoBookmarkID(UINT nCmdID);
   afx_msg void OnClearBookmarks();

   afx_msg void OnToggleBookmark(); // More bookmarks
   afx_msg void OnClearAllBookmarks();
   afx_msg void OnNextBookmark();
   afx_msg void OnPrevBookmark();
   afx_msg void OnUpdateClearAllBookmarks(CCmdUI *pCmdUI);
   afx_msg void OnUpdateNextBookmark(CCmdUI *pCmdUI);
   afx_msg void OnUpdatePrevBookmark(CCmdUI *pCmdUI);

   afx_msg void ScrollUp();
   afx_msg void ScrollDown();
   afx_msg void ScrollLeft();
   afx_msg void ScrollRight();

   afx_msg void OnUpdateIndicatorCol(CCmdUI *pCmdUI);
   afx_msg void OnUpdateIndicatorOvr(CCmdUI *pCmdUI);
   afx_msg void OnUpdateIndicatorRead(CCmdUI *pCmdUI);

   DECLARE_MESSAGE_MAP()
};

#ifdef _DEBUG
#define ASSERT_VALIDTEXTPOS(pt,bResetInvalid)     AssertValidTextPos(pt,bResetInvalid);
#else
#define ASSERT_VALIDTEXTPOS(pt)
#endif

#define UNDO_DESCRIP_BUF        32

enum LINEFLAGS
{
   LF_BOOKMARK_FIRST       = 0x00000001L,
   LF_EXECUTION            = 0x00010000L,
   LF_BREAKPOINT           = 0x00020000L,
   LF_COMPILATION_ERROR    = 0x00040000L,
   LF_BOOKMARKS            = 0x00080000L,
   LF_INVALID_BREAKPOINT   = 0x00100000L,
   LF_ALL_BOOKMARKS        = 0x0008FFFFL
};

#define LF_BOOKMARK(id)    (LF_BOOKMARK_FIRST << id)

enum CRLFSTYLE
{
   CRLF_STYLE_AUTOMATIC = -1,
   CRLF_STYLE_DOS       = 0,
   CRLF_STYLE_UNIX      = 1,
   CRLF_STYLE_MAC       = 2
};

enum
{
   CE_ACTION_UNKNOWN    = 0,
   CE_ACTION_PASTE      = 1,
   CE_ACTION_DELSEL     = 2,
   CE_ACTION_CUT        = 3,
   CE_ACTION_TYPING     = 4,
   CE_ACTION_BACKSPACE  = 5,
   CE_ACTION_INDENT     = 6,
   CE_ACTION_DRAGDROP   = 7,
   CE_ACTION_REPLACE    = 8,
   CE_ACTION_DELETE     = 9,
   CE_ACTION_AUTOINDENT = 10,
   CE_ACTION_INSERT     = 11
   // ...
   // Expandable: user actions allowed
};


/////////////////////////////////////////////////////////////////////////////
// ZUpdateContext class

class ZUpdateContext
{
public:
   virtual void RecalcPoint(CPoint &ptPoint) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// ZCrystalTextBuffer command target

class ZDCTL_CLASS ZCrystalTextBuffer : public CCmdTarget
{
   DECLARE_DYNAMIC(ZCrystalTextBuffer)

private:
   ZCrystalEditView *m_pED_Crystal;
   BOOL m_bInit;
   BOOL m_bNew;
   BOOL m_bReadOnly;
   BOOL m_bModified;
   int  m_nCRLFMode;
   BOOL m_bCreateBackupFile;
   int  m_nUndoBufSize;
   char m_chLang;
   CString m_csFileName;
   CString m_csModifiedFileName;
   int  FindLineWithFlag(DWORD dwFlag);

protected:
#pragma pack(push, 1)
   // Nested class declarations
   struct SLineInfo
   {
      TCHAR *m_pcLine;
      int   m_nLth;
      int   m_nMax;
      DWORD m_dwFlags;

      SLineInfo() { memset(this, 0, sizeof(SLineInfo)); };
   };

   enum
   {
      UNDO_INSERT       = 0x0001,
      UNDO_BEGINGROUP   = 0x0100
   };

   // [JRT] Support For Descriptions On Undo/Redo Actions
   struct SUndoRecord
   {
      DWORD  m_dwFlags;

      CPoint m_ptStartPos;     // Block of text participating start position ...
      CPoint m_ptEndPos;       // ... end position
      int    m_nAction;        // For information only: action type

   private:
      // TCHAR *m_pcText;
      // Since in most cases we have 1 character here,
      // we should invent a better way. Note: 2 * sizeof(WORD) <= sizeof(TCHAR*)
      //
      // Here we will use the following trick: on Win32 platforms high-order word
      // of any pointer will be != 0. So we can store 1 character strings without
      // allocating memory.
      //

      union
      {
         TCHAR *m_pszText;    // For cases when we have > 1 character strings
         TCHAR m_szText[2];   // For single-character strings
      };

   public:
      // constructor/destructor for this struct
      SUndoRecord() { memset(this, 0, sizeof(SUndoRecord)); };

      void SetText(LPCTSTR pszText);
      void FreeText();

      LPCTSTR GetText() const
      {
         if (HIWORD((DWORD) m_pszText) != 0)  // using the above documented trick
            return m_pszText;
         return m_szText;
      };
   };

#pragma pack(pop)

   class ZInsertContext : public ZUpdateContext
   {
   public:
      CPoint m_ptStart, m_ptEnd;
      virtual void RecalcPoint(CPoint &ptPoint);
   };

   class CDeleteContext : public ZUpdateContext
   {
   public:
      CPoint m_ptStart, m_ptEnd;
      virtual void RecalcPoint(CPoint &ptPoint);
   };

   // Lines of text
   CArray <SLineInfo, SLineInfo&> m_aLines;

   // Undo
   CArray <SUndoRecord, SUndoRecord&> m_aUndoBuf;
   int m_nUndoPosition;
   int m_nSyncPosition;
   BOOL m_bUndoGroup, m_bUndoBeginGroup;

   // Connected views
   CList <ZCrystalEditView *, ZCrystalEditView *> m_lpViews;

   // Helper methods
   void InsertLine(LPCTSTR pszLine, int nLth = -1, int nPosition = -1);
   void AppendLine(int nLineIndex, LPCTSTR pszChars, int nLth = -1);

   // Implementation
   BOOL InternalInsertText(ZCrystalEditView *pSource, int nLine, int nPos, LPCTSTR pszText, int &nEndLine, int &nEndChar);
   BOOL InternalDeleteText(ZCrystalEditView *pSource, int nStartLine, int nStartPos, int nEndLine, int nEndPos);

   // [JRT] Support For Descriptions On Undo/Redo Actions
   void AddUndoRecord(BOOL bInsert, const CPoint &ptStartPos, const CPoint &ptEndPos,
                      LPCTSTR pszText, int nActionType = CE_ACTION_UNKNOWN);

   // Overridable: provide action description
   virtual BOOL GetActionDescription(int nAction, CString &desc);

// Operations
public:
   // Construction/destruction code
   ZCrystalTextBuffer(ZCrystalEditView *pED_Crystal);
   ~ZCrystalTextBuffer();

   // Basic functions
   BOOL InitNew(int nCrlfStyle = CRLF_STYLE_DOS);
   BOOL LoadFromFile(LPCTSTR pszFileName, int nCrlfStyle = CRLF_STYLE_AUTOMATIC);
   BOOL SaveToFile(LPCTSTR pszFileName, int nCrlfStyle = CRLF_STYLE_AUTOMATIC, BOOL bClearModifiedFlag = TRUE);
   void SetLanguageType( char chLang );
   char GetLanguageType();
   CString GetFileName();
   void SetFileName(LPCTSTR cpcFileName);
   CString GetModifiedFileName();
   void SetModifiedFileName(LPCTSTR cpcModifiedFileName);
   void FreeAll();

   // 'Dirty' flag
   virtual void SetModified(BOOL bModified = TRUE);
   BOOL IsModified() const;
   BOOL IsNew() const;

   // Connect/disconnect views
   void AddView(ZCrystalEditView *pView);
   void RemoveView(ZCrystalEditView *pView);

   // Text access functions
   int GetLineCount();
   int GetLineLength(int nLine);
   LPTSTR GetLineChars(int nLine);
   DWORD GetLineFlags(int nLine);
   int GetLineWithFlag(DWORD dwFlag);
   void SetLineFlag(int nLine, DWORD dwFlag, BOOL bSet, BOOL bRemoveFromPreviousLine = TRUE);
   void GetText(int nStartLine, int nStartChar, int nEndLine, int nEndChar, CString &text, LPCTSTR pszCRLF = NULL);

   // Attributes
   int GetCRLFMode();
   void SetCRLFMode(int nCRLFMode);
   BOOL GetReadOnly() const;
   void SetReadOnly(BOOL bReadOnly = TRUE);

   // Text modification functions
   BOOL InsertText(ZCrystalEditView *pSource, int nLine, int nPos, LPCTSTR pszText, int &nEndLine, int &nEndChar, int nAction = CE_ACTION_UNKNOWN);
   BOOL DeleteText(ZCrystalEditView *pSource, int nStartLine, int nStartPos, int nEndLine, int nEndPos, int nAction = CE_ACTION_UNKNOWN);

   // Undo/Redo
   BOOL CanUndo();
   BOOL CanRedo();
   BOOL Undo(CPoint &ptCursorPos);
   BOOL Redo(CPoint &ptCursorPos);

   // Undo grouping
   void BeginUndoGroup(BOOL bMergeWithPrevious = FALSE);
   void FlushUndoGroup(ZCrystalEditView *pSource);

   // Browse undo sequence
   POSITION GetUndoDescription(CString &desc, POSITION pos = NULL);
   POSITION GetRedoDescription(CString &desc, POSITION pos = NULL);

   // Notify all connected views about changes in text
   void UpdateViews( ZCrystalEditView *pSource, ZUpdateContext *pContext,
                     DWORD dwUpdateFlags, int nLineIndex = -1 );

   // More bookmarks
   int FindNextBookmarkLine(int nCurrentLine = 0);
   int FindPrevBookmarkLine(int nCurrentLine = 0);

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ZCrystalTextBuffer)
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(ZCrystalTextBuffer)
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

// Registry keys & values
#define REG_FIND_SUBKEY    _T("CrystalEdit\\Find")
#define REG_REPLACE_SUBKEY _T("CrystalEdit\\Replace")
#define REG_MATCH_CASE     _T("MatchCase")
#define REG_WHOLE_WORD     _T("WholeWord")
#define REG_FIND_WHAT      _T("FindWhat")
#define REG_REPLACE_WITH   _T("ReplaceWith")

#define REG_PAGE_SUBKEY    _T("CrystalEdit\\PageSetup")
#define REG_MARGIN_LEFT    _T("LeftMargin")
#define REG_MARGIN_RIGHT   _T("RightMargin")
#define REG_MARGIN_TOP     _T("TopMargin")
#define REG_MARGIN_BOTTOM  _T("BottomMargin")



/////////////////////////////////////////////////////////////////////////////
// ZFindTextDlg dialog

class ZFindTextDlg : public CDialog
{
private:
   ZCrystalEditView *m_pED_Crystal;

   // Construction
public:
   ZFindTextDlg(ZCrystalEditView *pED_Crystal);

   CPoint m_ptCurrentPos;
   // Dialog Data
   //{{AFX_DATA(ZFindTextDlg)
   enum { IDD = IDD_EDIT_FIND };
   int   m_nDirection;
   BOOL  m_bMatchCase;
   BOOL  m_bWholeWord;
   CString  m_csText;
   //}}AFX_DATA

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ZFindTextDlg)
protected:
   virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
                                                       //}}AFX_VIRTUAL

                                                       // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(ZFindTextDlg)
   virtual void OnOK();
   afx_msg void OnChangeEditText();
   virtual BOOL OnInitDialog();
   virtual void OnCancel();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// ZEditReplaceDlg dialog

class ZEditReplaceDlg : public CDialog
{
private:
   ZCrystalEditView *m_pED_Crystal;
   BOOL m_bFound;
   CPoint m_ptFoundAt;
   BOOL DoHighlightText();

   // Construction
public:
   ZEditReplaceDlg(ZCrystalEditView *pED_Crystal);

   BOOL m_bEnableScopeSelection;
   CPoint m_ptCurrentPos;
   CPoint m_ptBlockBegin, m_ptBlockEnd;

   // Dialog Data
   //{{AFX_DATA(ZEditReplaceDlg)
   enum { IDD = IDD_EDIT_REPLACE };
   BOOL  m_bMatchCase;
   BOOL  m_bWholeWord;
   CString  m_csText;
   CString  m_csNewText;
   int      m_nScope;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ZEditReplaceDlg)
protected:
   virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
                                                       //}}AFX_VIRTUAL

                                                       // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(ZEditReplaceDlg)
   afx_msg void OnChangeEditText();
   virtual void OnCancel();
   virtual BOOL OnInitDialog();
   afx_msg void OnEditReplace();
   afx_msg void OnEditReplaceAll();
   afx_msg void OnEditSkip();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

