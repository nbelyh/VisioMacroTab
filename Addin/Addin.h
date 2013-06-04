
#pragma once

class CVisioFrameWnd;

class CAddinApp : public CWinApp
{
public:
	CAddinApp();
	~CAddinApp();

	void OnCommand(UINT id);

	Visio::IVApplicationPtr GetVisioApp();
	void SetVisioApp(Visio::IVApplicationPtr app);

	Office::IRibbonUIPtr GetRibbon();
	void SetRibbon(Office::IRibbonUIPtr ribbon);

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void UpdateButtons();
	VARIANT_BOOL IsButtonEnabled( UINT cmd_id );
	VARIANT_BOOL IsButtonPressed( UINT cmd_id );

	bool IsCheckbox(UINT cmd_id);

	void SetNeedUpdate( bool set );
	bool NeedUpdate();

	CVisioFrameWnd* GetWindowShapeSheet(HWND hwnd) const;
	void RegisterWindow(HWND hwnd, CVisioFrameWnd* window);
	UINT GetImageId( UINT cmd_id ) const;
private:
	struct Impl;
	Impl* m_impl;
};

extern CAddinApp theApp;
