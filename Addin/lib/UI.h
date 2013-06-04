
#pragma once

#include <atlcoll.h>

extern _ATL_FUNC_INFO ClickEventInfo;

// event sink to handle button click events from Visio.
// Finally this simple "click" event is used as the least evil method.
class ClickEventRedirector :
	public IDispEventSimpleImpl<1, ClickEventRedirector, &__uuidof(Office::_CommandBarButtonEvents)>
{
public:
	ClickEventRedirector(Office::CommandBarControlPtr punk, const CString& tag, UINT cmd_id);
	~ClickEventRedirector();

	// the event handler itself. 
	// Just redirect to the global command processor ("parameter" of the button contains the command itself)
	void __stdcall OnClick(IDispatch* pButton, VARIANT_BOOL* pCancel);

	// keep the reference to the item itself, otherwise VISIO destroys it for some unknown reason
	// probably because of it's "double-nature" user interface, and events are never fired.
	CString m_tag;
	UINT m_cmd_id;
	Office::CommandBarControlPtr m_punk;

	BEGIN_SINK_MAP(ClickEventRedirector)
		SINK_ENTRY_INFO(1, __uuidof(Office::_CommandBarButtonEvents), 1, &ClickEventRedirector::OnClick, &ClickEventInfo)
	END_SINK_MAP()
};

struct AddinUi
{
	void InstallToolbar(Visio::IVApplicationPtr app);
	void UninstallToolbar();
	void AddinUi::UpdateButton(Office::_CommandBarButtonPtr button, UINT cmd_id);

	void InstallButtons(Office::CommandBarControlsPtr menu_items, CMenu* popup_menu );
	void UpdateButtons();

private:
	CAtlArray<ClickEventRedirector*> m_buttons;
};

HRESULT GetRibbonText(BSTR * RibbonXml);
