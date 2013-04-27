// EditMacroDlg.cpp : Implementation of CEditMacroDlg

#include "stdafx.h"
#include "PageCustomMacro.h"

// CEditMacroDlg

void CPageCustomMacro::GetMacroText (CString& result) const
{
	result = m_text;
}

LRESULT CPageCustomMacro::OnInitDialog (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	g_xpStyle.EnableThemeDialogTexture(m_hWnd, ETDT_ENABLETAB);

	m_ctlEditor.SubclassWindow(GetDlgItem(IDC_RICHEDIT21));

	static LPCWSTR keywords[] =
	{
		L"For", 
		L"To", 
		L"Step", 
		L"Next",
		L"If", 
		L"Then", 
		L"Else",
		L"Each",
		L"Select",
		L"Case",
		L"While",
		L"Wend",
		L"End",
		L"Sub",
		L"Function",
		L"Let",
		L"Dim",
		L"Set",
		L"ReDim",
	};

	m_ctlEditor.ClearKeywords();
	for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); ++i)
		m_ctlEditor.AddKeyword(keywords[i]);

	static LPCWSTR constants[] = 
	{
		L"True", 
		L"False", 
		L"Empty", 
		L"Nothing", 
		L"Null"
	};

	m_ctlEditor.ClearConstants();
	for (int i = 0; i < sizeof(constants)/sizeof(constants[0]); ++i)
		m_ctlEditor.AddConstant(constants[i]);

	static LPCWSTR globals[] = 
	{
		L"Application", 
		L"ActiveDocument", 
		L"ActivePage", 
	};

	m_ctlEditor.ClearGlobals();
	for (int i = 0; i < sizeof(globals)/sizeof(globals[0]); ++i)
		m_ctlEditor.AddGlobal(globals[i]);

	m_ctlEditor.SetCaseSensitive(FALSE);
	m_ctlEditor.SetChangeCase(TRUE);
	m_ctlEditor.SetSyntax(SC_COMMENT, L"'");

	SYNTAXCOLOR ic = { 0 };
	ic.clrText = RGB(0,0,240);
	m_ctlEditor.SetSyntaxColor(SC_KEYWORD, ic);
	ic.clrText = RGB(0,100,0);
	m_ctlEditor.SetSyntaxColor(SC_CONSTANT, ic);
	ic.clrText = RGB(0,100,100);
	m_ctlEditor.SetSyntaxColor(SC_GLOBAL, ic);

	m_ctlEditor.SetWindowText(m_text);

	bHandled = TRUE;
	return 1;  // Let the system set the focus
}

CPageCustomMacro::CPageCustomMacro (const CString& text) : m_text(text)
{

}

CPageCustomMacro::~CPageCustomMacro ()
{

}