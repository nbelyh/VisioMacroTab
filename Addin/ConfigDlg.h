#pragma once

#include "Config.h"

class CConfigDlg : 
	public CAxDialogImpl<CConfigDlg>
{
public:
	CConfigDlg(IDispatch* app, const CConfig& config);
	~CConfigDlg();

	const CConfig& GetConfig() const;

	enum { IDD = IDD_CONFIGDLG };

	BEGIN_MSG_MAP(CConfigDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
		COMMAND_RANGE_CODE_HANDLER(IDC_CHECK1, IDC_CHECK5, BN_CLICKED, OnClickedCheck)
		COMMAND_RANGE_CODE_HANDLER(IDC_MACRO1, IDC_MACRO5, BN_CLICKED, OnClickedMacro)
		CHAIN_MSG_MAP(CAxDialogImpl<CConfigDlg>)
	END_MSG_MAP()

	// Handler prototypes:
	//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	void UpdateButtons();

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnClickedCheck(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedMacro(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	IDispatch* m_app;
	CConfig m_config;
};
