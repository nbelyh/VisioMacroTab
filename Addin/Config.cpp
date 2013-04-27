
#include "stdafx.h"
#include "Config.h"

void CConfig::ReadConfig()
{
}

void CConfig::WriteConfig()
{
}

CConfig::CConfig ()
{
	for (int i = 0; i < MAX_BUTTON_COUNT; ++i)
	{
		ButtonInfo& info = m_buttons[i];

		info.enabled = FALSE;

		wchar_t label[32] = L"";
		swprintf_s(label, L"Button %d", 1+i);
		info.label = label;
	}
}

CConfig::~CConfig ()
{
}

CConfig& CConfig::Instance ()
{
	static CConfig config;
	return config;
}

CConfig::ButtonInfo& CConfig::GetButtonInfo (size_t idx)
{
	return m_buttons[idx];
}
