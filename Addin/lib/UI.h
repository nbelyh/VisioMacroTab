
#pragma once

#include <atlcoll.h>

class ClickEventRedirector;

struct AddinUi
{
	void CreateCommandBarsUi(Visio::IVApplicationPtr app);
	void DestroyCommandBarsUi();

private:
	void InitializeItem( Office::CommandBarControlPtr item, UINT command_id );
	void FillMenuItems( long position, Office::CommandBarControlsPtr menu_items, CMenu* popup_menu );
	void FillMenu( long position, Office::CommandBarControlsPtr cbs, UINT menu_id );
	Office::CommandBarPopupPtr CreateFrameMenu(Office::CommandBarControlsPtr menus);
private:
	CAtlArray<ClickEventRedirector*> m_buttons;
};

HRESULT GetRibbonText(BSTR * RibbonXml);
