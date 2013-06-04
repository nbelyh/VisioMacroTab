// AddIn.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "Addin.h"

#include "AddIn_i.h"
#include "AddIn_i.c"
#include "lib/UI.h"
#include "lib/Visio.h"
#include "VisioFrameWnd.h"

CComModule _Module;

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	return _Module.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	HRESULT hr = _Module.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _Module.DllUnregisterServer();
	return hr;
}

STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	// MSVC will call "regsvr32 /i:user" if "per-user registration" is set as a
	// linker option - so handle that here (its also handle for anyone else to
	// be able to manually install just for themselves.)
	static const wchar_t szUserSwitch[] = L"user";
	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			AtlSetPerUserRegistration(true);
			// But ATL still barfs if you try and register a COM category, so
			// just arrange to not do that.
			_AtlComModule.m_ppAutoObjMapFirst = _AtlComModule.m_ppAutoObjMapLast;
		}
	}
	if (bInstall)
	{
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}
	return hr;
}

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

BOOL CAddinApp::InitInstance()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Initialize COM stuff
	if (FAILED(_Module.Init(ObjectMap, AfxGetInstanceHandle(), &LIBID_VisioMacroTabAddin)))
		return FALSE;

	return TRUE;
}

int CAddinApp::ExitInstance() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	_Module.Term();

	return CWinApp::ExitInstance();
}

struct CAddinApp::Impl
{
	Impl()
	{
		captured = 0;
		command = 0;
		need_update = true;
	}

	CSimpleMap<HWND, CVisioFrameWnd*> shown_windows;
	Visio::IVApplicationPtr app;
	Office::IRibbonUIPtr	ribbon;

	struct Point
	{
		Visio::IVShapePtr shape;
		short row;

		bstr_t formula_x;
		bstr_t formula_y;
		bstr_t formula_dir_x;
		bstr_t formula_dir_y;
	};

	Point points[2];

	UINT command;
	int captured;

	bool need_update;

	void SetNeedUpdate(bool set)
	{
		if (ribbon)
			ribbon->Invalidate();
		else
			need_update = set;
	}

	void OnClick(UINT cmd_id)
	{
		while (captured > 0)
			RemovePoint();

		if (cmd_id == command)
		{
			app->DoCmd(Visio::visCmdDRPointerTool);
			command = 0;
		}
		else
		{
			if (command == 0)
				app->DoCmd(Visio::visCmdDRConnectionTool);

			command = cmd_id;
		}

		SetNeedUpdate(true);
	}

	void RemovePoint()
	{
		if (captured > 0)
		{
			Point& point = points[--captured];

			point.shape->DeleteRow(Visio::visSectionConnectionPts, point.row);
			point.shape = NULL;
		}
	}

	void AddPoint(Point point)
	{
		short rows = point.shape->GetRowCount(Visio::visSectionConnectionPts);
		point.row = point.shape->AddRow(Visio::visSectionConnectionPts, rows, 0);

		Visio::IVCellPtr cell_x = point.shape->CellsSRC[Visio::visSectionConnectionPts][point.row][0];
		cell_x->FormulaForceU = point.formula_x;

		Visio::IVCellPtr cell_y = point.shape->CellsSRC[Visio::visSectionConnectionPts][point.row][1];
		cell_y->FormulaForceU = point.formula_y;

		Visio::IVCellPtr cell_dir_x = point.shape->CellsSRC[Visio::visSectionConnectionPts][point.row][2];
		cell_dir_x->FormulaForceU = point.formula_dir_x;

		Visio::IVCellPtr cell_dir_y = point.shape->CellsSRC[Visio::visSectionConnectionPts][point.row][3];
		cell_dir_y->FormulaForceU = point.formula_dir_y;

		captured = 1;
		points[0] = point;
	}

	AddinUi m_ui;

	void SetVisioApp( Visio::IVApplicationPtr app ) 
	{
		this->app = app;

		if (app != NULL)
		{
			if (GetVisioVersion(app) < 14)
				m_ui.InstallToolbar(app);
		}

		if (app == NULL)
		{
			m_ui.UninstallToolbar();
		}
	}

};

void CAddinApp::OnCommand(UINT id)
{
	switch (id)
	{
	case ID_SHOW_DOCKED_WINDOW:
		{
			Visio::IVWindowPtr window = theApp.GetVisioApp()->GetActiveWindow();

			HWND hwnd = GetVisioWindowHandle(window);

			CVisioFrameWnd* wnd = GetWindowShapeSheet(hwnd);
			if (wnd)
			{
				wnd->Destroy();
				RegisterWindow(hwnd, NULL);
			}
			else
			{
				wnd = new CVisioFrameWnd();
				wnd->Create(window);
				RegisterWindow(hwnd, wnd);
			}
		}
	}
}

Visio::IVApplicationPtr CAddinApp::GetVisioApp()
{
	return m_impl->app;
}

void CAddinApp::SetVisioApp( Visio::IVApplicationPtr app )
{
	m_impl->SetVisioApp(app);
}

Office::IRibbonUIPtr CAddinApp::GetRibbon()
{
	return m_impl->ribbon;
}

void CAddinApp::SetRibbon(Office::IRibbonUIPtr ribbon)
{
	m_impl->ribbon = ribbon;
}

CAddinApp::CAddinApp()
{
	m_impl = new Impl();
}

CAddinApp::~CAddinApp()
{
	delete m_impl;
}

void CAddinApp::UpdateButtons()
{
	m_impl->m_ui.UpdateButtons();
}

VARIANT_BOOL CAddinApp::IsButtonEnabled( UINT cmd_id )
{
	switch (cmd_id)
	{
	case ID_SHOW_DOCKED_WINDOW:
		{
			Visio::IVDocumentPtr doc;
			if (FAILED(m_impl->app->get_ActiveDocument(&doc)) || doc == NULL)
				return VARIANT_FALSE;
			
			Visio::VisDocumentTypes doc_type = Visio::visDocTypeInval;
			if (FAILED(doc->get_Type(&doc_type)) || doc_type == Visio::visDocTypeInval)
				return VARIANT_FALSE;
			
			return VARIANT_TRUE;
		}

	default:
		return VARIANT_TRUE;
	}
}

bool CAddinApp::IsCheckbox( UINT cmd_id )
{
	switch (cmd_id)
	{
	case ID_SHOW_DOCKED_WINDOW:
		return true;

	default:
		return false;
	}
}

VARIANT_BOOL CAddinApp::IsButtonPressed( UINT cmd_id )
{
	switch (cmd_id)
	{
	case ID_SHOW_DOCKED_WINDOW:
		{
			Visio::IVWindowPtr window;
			if (FAILED(m_impl->app->get_ActiveWindow(&window)) || window == NULL)
				return VARIANT_FALSE;

			return GetWindowShapeSheet(GetVisioWindowHandle(window)) != NULL ? VARIANT_TRUE : VARIANT_FALSE;
		}

	default:
		return VARIANT_FALSE;
	}
}

void CAddinApp::SetNeedUpdate( bool set )
{
	m_impl->SetNeedUpdate(set);
}

bool CAddinApp::NeedUpdate()
{
	return m_impl->need_update;
}

CAddinApp theApp;

CVisioFrameWnd* CAddinApp::GetWindowShapeSheet(HWND hwnd) const
{
	int idx = m_impl->shown_windows.FindKey(hwnd);

	if (idx < 0)
		return NULL;
	return
		m_impl->shown_windows.GetValueAt(idx);
}

void CAddinApp::RegisterWindow(HWND hwnd, CVisioFrameWnd* window)
{
	if (window)
		m_impl->shown_windows.Add(hwnd, window);
	else
		m_impl->shown_windows.Remove(hwnd);

	SetNeedUpdate(true);
}

UINT CAddinApp::GetImageId( UINT cmd_id ) const
{
	switch (cmd_id)
	{
	case ID_SHOW_DOCKED_WINDOW:
		return ID_SHOW_DOCKED_WINDOW_16;
	default:
		return -1;
	}
}
