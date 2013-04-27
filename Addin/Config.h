#pragma once

#define MAX_BUTTON_COUNT 5

class CConfig
{
public:
	CConfig();
	~CConfig();

	struct ButtonInfo
	{
		BOOL enabled;
		CString label;
		CSimpleArray<BYTE> image;
		CString macro;
	};

	ButtonInfo& GetButtonInfo(size_t idx);

	static CConfig& Instance();

	static void ReadConfig();
	static void WriteConfig();

private:
	ButtonInfo m_buttons[MAX_BUTTON_COUNT];
};
