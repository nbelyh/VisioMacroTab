// EditMacroDlg.h : Declaration of the CEditMacroDlg

#pragma once

#include "RtfScriptEditor.h"

// CEditMacroDlg

class CPageCustomMacro : 
	public CPropertyPageImpl<CPageCustomMacro>
{
public:
	CPageCustomMacro(const CString& text);

	~CPageCustomMacro();

	void GetMacroText(CString& result) const;

	enum { IDD = IDD_EDITMACRODLG };

protected:

	BEGIN_MSG_MAP(CPageCustomMacro)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPageCustomMacro>)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	// Handler prototypes:
	//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	CString m_text;
	CRtfScriptEditorCtrl m_ctlEditor;
};


