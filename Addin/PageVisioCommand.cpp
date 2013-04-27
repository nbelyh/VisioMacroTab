// VisioCommandPage.cpp : Implementation of CVisioCommandPage

#include "stdafx.h"
#include "PageVisioCommand.h"


// CVisioCommandPage

LRESULT CPageVisioCommand::OnInitDialog (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	g_xpStyle.EnableThemeDialogTexture(m_hWnd, ETDT_ENABLETAB);

	m_list.Attach(GetDlgItem(IDC_LIST1));

	m_list.ModifyStyleEx(0, LVS_EX_AUTOSIZECOLUMNS|LVS_EX_FULLROWSELECT);

	m_list.AddColumn(L"Icon", 0);
	m_list.AddColumn(L"Command", 1);

	IDispatchPtr cbs_disp;
	m_app->get_CommandBars(&cbs_disp);

	Office::_CommandBarsPtr cbs = cbs_disp;

	Office::CommandBarPtr cb;
	cbs->get_ActiveMenuBar(&cb);
	EnumerateCommandBar(cb);

	int cbs_count = 0;
	cbs->get_Count(&cbs_count);

	for (long i = 1; i <= cbs_count; ++i)
	{
		Office::CommandBarPtr cb;
		cbs->get_Item(variant_t(i), &cb);

		EnumerateCommandBar(cb);
	}

	bHandled = TRUE;
	return 1;  // Let the system set the focus
}

void CPageVisioCommand::EnumerateControls (LPCWSTR parent_caption, Office::CommandBarControlsPtr cbcs)
{
	int cbcs_count = 0;
	cbcs->get_Count(&cbcs_count);

	for (long j = 1; j <= cbcs_count; ++j)
	{
		Office::CommandBarControlPtr cbc;
		cbcs->get_Item(variant_t(j), &cbc);

		Office::MsoControlType type;
		cbc->get_Type(&type);

		switch (type)
		{
		case Office::msoControlButton:
			{
				CComBSTR bstr_caption;
				cbc->get_Caption(&bstr_caption);

				CString caption = static_cast<LPCWSTR>(bstr_caption);

				CString full_caption;
				full_caption.Format(L"%s.%s", parent_caption, caption);

				full_caption.Replace(L"&", L"");
				full_caption.Replace(L"...", L"");

				m_list.AddItem(0, 0, full_caption);
			}
			break;

		case Office::msoControlPopup:
			{
				Office::CommandBarPopupPtr cbc_popup = cbc;
				
				Office::CommandBarControlsPtr cbc_popup_controls;
				cbc_popup->get_Controls(&cbc_popup_controls);

				CComBSTR caption;
				cbc_popup->get_Caption(&caption);

				CString full_caption;
				full_caption.Format(L"%s.%s", parent_caption, caption);

				EnumerateControls(full_caption, cbc_popup_controls);
			}
			break;
		}

	}
}

void CPageVisioCommand::EnumerateCommandBar (Office::CommandBarPtr cb)
{
	Office::CommandBarControlsPtr cbcs;
	cb->get_Controls(&cbcs);

	CComBSTR caption;
	cb->get_Name(&caption);

	EnumerateControls(caption, cbcs);
}