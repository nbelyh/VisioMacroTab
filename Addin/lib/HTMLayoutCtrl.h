
#pragma once

extern const UINT MSG_HTMLAYOUT_HYPERLINK;
extern const UINT MSG_HTMLAYOUT_BUTTON;

class CHTMLayoutCtrl : public CWnd
{
public:
	CHTMLayoutCtrl();
	~CHTMLayoutCtrl();

	// Generic creator
	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, DWORD dwStyle);

	// Load html from memory buffer
	bool LoadHtml(const BYTE* pb, DWORD nBytes);
	bool LoadHtml(LPCWSTR text);

	UINT GetMinHeight(UINT width) const;
	UINT GetMinWidth() const;

	// load html from file
	bool LoadHtmlFile(LPCWSTR filename);
	
	void SetElementText(const char* id, LPCWSTR text);
	void SetElementAttribute(const char* id, const char* attribute, LPCWSTR text);
	void SetElementEnabled (const char* id, bool set);
	void SetElementValueLong(const char* id, long v);

	CString GetScriptText() const;

protected:
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	virtual LRESULT WindowProc(UINT message,WPARAM wParam,LPARAM lParam );

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CHTMLayoutCtrl)
	void UpdateSize();
private:
	struct Impl;
	Impl* m_impl;
};

#pragma comment(lib, "HTMLayout.lib")