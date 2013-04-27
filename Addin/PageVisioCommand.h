// VisioCommandPage.h : Declaration of the CVisioCommandPage

#pragma once

#include "resource.h"       // main symbols

class CPageVisioCommand : 
	public CPropertyPageImpl<CPageVisioCommand>
{
public:
	CPageVisioCommand(Visio::IVApplicationPtr app)
		: m_app(app)
	{
	}

	~CPageVisioCommand()
	{
	}

	enum { IDD = IDD_VISIOCOMMANDPAGE };

	BEGIN_MSG_MAP(CPageVisioCommand)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPageVisioCommand>)
	END_MSG_MAP()

	// Handler prototypes:
	//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void EnumerateCommandBar (Office::CommandBarPtr cb);
	void EnumerateControls (LPCWSTR parent_caption, Office::CommandBarControlsPtr cbcs);
	Visio::IVApplicationPtr m_app;
	CListViewCtrl m_list;
};
