
#include "stdafx.h"

#include "Language.h"
#include "Utils.h"
#include "TextFile.h"
#include "UI.h"
#include "PictureConvert.h"

#include "../Addin.h"

#define ADDON_NAME	L"TwoPoints"

_ATL_FUNC_INFO ClickEventInfo = { CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_BOOL|VT_BYREF } };


ClickEventRedirector::ClickEventRedirector(Office::CommandBarControlPtr punk, const CString& tag, UINT cmd_id) 
	: m_punk(punk)
	, m_tag(tag)
	, m_cmd_id(cmd_id)
{
	DispEventAdvise(punk);
}

ClickEventRedirector::~ClickEventRedirector()
{
	DispEventUnadvise(m_punk);
}

void __stdcall ClickEventRedirector::OnClick(IDispatch* pButton, VARIANT_BOOL* pCancel)
{
	try
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		LanguageLock lock(GetAppLanguage(theApp.GetVisioApp()));

		Office::_CommandBarButtonPtr button;
		pButton->QueryInterface(__uuidof(Office::_CommandBarButton), (void**)&button);

		CComBSTR parameter;
		button->get_Parameter(&parameter);
		UINT cmd_id = StrToInt(parameter);

		theApp.OnCommand(cmd_id);

	}
	catch (_com_error)
	{
		// 
	}
}

void AddinUi::UpdateButton(Office::_CommandBarButtonPtr button, UINT cmd_id)
{
	VARIANT_BOOL enabled = theApp.IsButtonEnabled(cmd_id);
	button->put_Enabled(enabled);

	if (theApp.IsCheckbox(cmd_id))
	{
		VARIANT_BOOL pressed = theApp.IsButtonPressed(cmd_id);
		button->put_State(pressed ? Office::msoButtonDown : Office::msoButtonUp);
	}

	UINT image_id = theApp.GetImageId(cmd_id);

	if (image_id < 0)
		return;

	IPictureDispPtr picture;
	IPictureDispPtr mask;
	if (SUCCEEDED(CustomUiGetPng(MAKEINTRESOURCE(image_id), &picture, &mask)))
	{
		try
		{
			button->put_Picture(picture);
			button->put_Mask(mask);
		}
		catch (_com_error)
		{
			// There Some problems; hope to never get here.
		}
	}
}

void AddinUi::InstallButtons(Office::CommandBarControlsPtr menu_items, CMenu* popup_menu )
{
	// For each items in the menu,

	for (UINT i = 0; i < popup_menu->GetMenuItemCount(); ++i)
	{
		CMenu* sub_menu = popup_menu->GetSubMenu(i);

		// set item caption
		CString item_caption;
		popup_menu->GetMenuString(i, item_caption, MF_BYPOSITION);

		// create new menu item.
		Office::CommandBarControlPtr item;
		menu_items->Add(
			variant_t(long(Office::msoControlButton)), 
			vtMissing, 
			vtMissing, 
			vtMissing, 
			variant_t(true),
			&item);

		// obtain command id from menu
		UINT command_id = popup_menu->GetMenuItemID(i);

		CString caption;
		caption.LoadString(command_id);
		item->put_Caption(bstr_t(caption));

		CString parameter;
		parameter.Format(L"%d", command_id);
		item->put_Parameter(bstr_t(parameter));

		// Set unique tag, so that the command is not lost
		CString tag;
		tag.Format(L"%s_%d", ADDON_NAME, command_id);
		item->put_Tag(bstr_t(tag));

		UpdateButton(item, command_id);

		m_buttons.Add(new ClickEventRedirector(item, tag, command_id));
	}
}

void AddinUi::InstallToolbar(Visio::IVApplicationPtr app)
{
	LanguageLock lock(GetAppLanguage(app));

	Office::_CommandBarsPtr cbs = app->CommandBars;

	CMenu menu;
	menu.LoadMenu(IDR_MENU);

	Office::CommandBarPtr cb;
	if (FAILED(cbs->get_Item(variant_t(ADDON_NAME), &cb)) || cb == NULL)
	{
		if (SUCCEEDED(cbs->Add(variant_t(ADDON_NAME), vtMissing, vtMissing, vtMissing, &cb)))
			cb->put_Visible(VARIANT_TRUE);
	}

	if (cb != NULL)
	{
		Office::CommandBarControlsPtr controls;
		cb->get_Controls(&controls);

		InstallButtons(controls, menu.GetSubMenu(0));
	}
}

void AddinUi::UninstallToolbar()
{
	for (size_t i = 0; i < m_buttons.GetCount(); ++i)
		delete m_buttons[i];

	m_buttons.RemoveAll();
}

void AddinUi::UpdateButtons()
{
	Office::_CommandBarsPtr cbs = theApp.GetVisioApp()->CommandBars;

	for (size_t i = 0; i < m_buttons.GetCount(); ++i)
	{
		ClickEventRedirector* button = m_buttons[i];

		Office::CommandBarControlPtr control;
		cbs->FindControl(vtMissing, vtMissing, variant_t(button->m_tag), vtMissing, &control);

		if (control != button->m_punk)
		{
			button->DispEventUnadvise(button->m_punk);
			button->m_punk = control;
			button->DispEventAdvise(button->m_punk);
		}

		UpdateButton(control, button->m_cmd_id);
	}
}

HRESULT GetRibbonText(BSTR * RibbonXml)
{
	LPBYTE content = NULL;
	DWORD content_length = 0;

	ASSERT_RETURN_VALUE(LoadResourceFromModule(
		AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_RESOURCE_H), L"TEXT", &content, &content_length), S_FALSE);

	CMemFile mf(content, content_length);
	CTextFileRead rdr(&mf);

	CMapStringToString replacements;

	CString line;
	while (rdr.ReadLine(line))
	{
		CSimpleArray<CString> tokens;

		CString token;
		token.Preallocate(30);

		for (LPCWSTR pos = line; *pos; ++pos)
		{
			if (*pos == ' ' || *pos == '\t')
			{
				if (!token.IsEmpty())
				{
					tokens.Add(token);
					token = CString();
				}
			}
			else
			{
				token += *pos;
			}
		}

		if (!token.IsEmpty())
			tokens.Add(token);

		if (tokens.GetSize() != 3)
			continue;

		if (tokens[0] != "#define")
			continue;

		replacements[tokens[1]] = tokens[2];
	}

	CString ribbon = LoadTextFromModule(AfxGetInstanceHandle(), IDR_RIBBON);

	for (int pos = 0; pos < ribbon.GetLength(); ++pos)
	{
		if (ribbon[pos] != '{')
			continue;

		int endpos = ribbon.Find('}', pos);
		ASSERT_CONTINUE(endpos != -1);

		CString token = ribbon.Mid(pos+1, endpos-pos-1);
		CString token_found;

		ASSERT_CONTINUE(replacements.Lookup(token, token_found));	

		ribbon.Delete(pos, endpos-pos+1);
		ribbon.Insert(pos, token_found);

		pos += (token_found.GetLength()-1);
	}

	*RibbonXml = ribbon.AllocSysString();
	return S_OK;
}
