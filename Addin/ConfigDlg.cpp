// ConfigDlg.cpp : Implementation of CConfigDlg

#include "stdafx.h"
#include "ConfigDlg.h"



#include "PageCustomMacro.h"
#include "PageVisioCommand.h"

// CConfigDlg
LRESULT CConfigDlg::OnInitDialog( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	CAxDialogImpl<CConfigDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);

	for (size_t i = 0; i < MAX_BUTTON_COUNT; ++i)
	{
		const CConfig::ButtonInfo& info = m_config.GetButtonInfo(i);

		CheckDlgButton(IDC_CHECK1+i, info.enabled);
		SetDlgItemText(IDC_EDIT1+i, info.label);
	}

	UpdateButtons();

	bHandled = TRUE;
	return 1;
}

LRESULT CConfigDlg::OnClickedOK( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled )
{
	for (size_t i = 0; i < MAX_BUTTON_COUNT; ++i)
	{
		CConfig::ButtonInfo& info = m_config.GetButtonInfo(i);

		info.enabled = IsDlgButtonChecked(IDC_CHECK1+i);
		GetDlgItemText(IDC_EDIT1+i, info.label);
	}

	EndDialog(wID);
	return 0;
}

LRESULT CConfigDlg::OnClickedCancel( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled )
{
	EndDialog(wID);
	return 0;
}

LRESULT CConfigDlg::OnClickedCheck( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled )
{
	UpdateButtons();
	return 0;
}

void CConfigDlg::UpdateButtons()
{
	for (size_t i = 0; i < MAX_BUTTON_COUNT; ++i)
	{
		BOOL checked = IsDlgButtonChecked(IDC_CHECK1+i);

		::EnableWindow(GetDlgItem(IDC_EDIT1+i), checked);
		::EnableWindow(GetDlgItem(IDC_PICTURE1+i), checked);
		::EnableWindow(GetDlgItem(IDC_MACRO1+i), checked);
	}
}

CConfigDlg::CConfigDlg(IDispatch* app, const CConfig& config)
	: m_app(app), m_config(config)
{
}

CConfigDlg::~CConfigDlg()
{

}

const CConfig& CConfigDlg::GetConfig () const
{
	return m_config;
}

LRESULT CConfigDlg::OnClickedMacro (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int idx = (wID - IDC_MACRO1);

	CConfig::ButtonInfo& info = m_config.GetButtonInfo(idx);

	CPropertySheet sheet(L"Edit action");
	sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;


	CPageVisioCommand pg_cmd(m_app);
	CPageCustomMacro pg_macro(info.macro);

	sheet.AddPage(pg_cmd);
	sheet.AddPage(pg_macro);

	if (sheet.DoModal(m_hWnd) == IDOK)
		pg_macro.GetMacroText(info.macro);

	return 0;
}