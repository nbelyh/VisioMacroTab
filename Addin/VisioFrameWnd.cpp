
/*******************************************************************************

	@file Implementation of a Visio frame window.

*******************************************************************************/

#include "stdafx.h"
#include "VisioFrameWnd.h"
#include "lib/Visio.h"
#include "lib/Utils.h"
#include "lib/HTMLayoutCtrl.h"
#include "lib/TextFile.h"
#include "Addin.h"
#include "Scripts.h"

using namespace Visio;

/**-----------------------------------------------------------------------------
	Message map
------------------------------------------------------------------------------*/

BEGIN_MESSAGE_MAP(CVisioFrameWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(MSG_HTMLAYOUT_HYPERLINK, OnHtmlayoutHyperlink)
	ON_REGISTERED_MESSAGE(MSG_HTMLAYOUT_BUTTON, OnMsgHtmlayoutButton)
END_MESSAGE_MAP()


struct CVisioFrameWnd::Impl : public VEventHandler
{
	/**-----------------------------------------------------------------------------
	Visio event handler callback
	------------------------------------------------------------------------------*/

	virtual HRESULT HandleVisioEvent(
		IN      IUnknown*       ipSink,
		IN      short           nEventCode,
		IN      IDispatch*      pSourceObj,
		IN      long            lEventID,
		IN      long            lEventSeqNum,
		IN      IDispatch*      pSubjectObj,
		IN      VARIANT         vMoreInfo,
		OUT VARIANT*    pvResult)
	{
		ENTER_METHOD();

		switch(nEventCode) 
		{
		case (short)(visEvtCodeWinSelChange):
			Reload();
			break;
		}

		return S_OK;

		LEAVE_METHOD()
	}

	void Reload()
	{
		m_html.LoadHtmlFile(L"D:\\Projects\\github\\VisioMacroTab\\Addin\\res\\Window.html");
		m_html.UpdateSize();
	}

	void Run() 
	{
		CString text = m_html.GetScriptText();

		RunScript(text, theApp.GetVisioApp(), NULL);
	}

	CHTMLayoutCtrl m_html;

	Visio::IVWindowPtr	visio_window;
	Visio::IVWindowPtr	this_window;

	CVisioEvent	evt_sel_changed;
};

/**------------------------------------------------------------------------------
	Creates and initializes a new Visio (top-level) window, and subclasses the 
	"client area" of that parent Visio window (this "client area" is actually 
	a special window provided by visio for sub-classing).
-------------------------------------------------------------------------------*/

void CVisioFrameWnd::Create(IVWindowPtr window)
{
	m_impl->visio_window = window;

	HWND hwnd_parent = 
		::GetParent(GetVisioWindowHandle(window));

	CWnd* parent_window = 
		CWnd::FromHandle(hwnd_parent);

	CRect parent_rect;
	parent_window->GetClientRect(&parent_rect);

	// Construct Visio window. Make this window size a half of Visio's size
	m_impl->this_window = window->GetWindows()->Add(
		bstr_t(L"VisioMacroTab"), 
		static_cast<long>(visWSVisible | visWSAnchorRight | visWSAnchorTop), 
		static_cast<long>(visAnchorBarAddon), 
		static_cast<long>(parent_rect.Width()), 
		static_cast<long>(parent_rect.Height()), 
		static_cast<long>(parent_rect.Width() / 3), 
		static_cast<long>(parent_rect.Height() / 2), 
		vtMissing, vtMissing, vtMissing);

	HWND client = GetVisioWindowHandle(m_impl->this_window);
	SubclassWindow(client);

	IVEventListPtr event_list = window->GetEventList();
	m_impl->evt_sel_changed.Advise(event_list, visEvtCodeWinSelChange, m_impl);

	CRect rect;
	GetClientRect(rect);

	m_impl->m_html.Create(rect, this, 1, WS_CHILD|WS_VISIBLE);
	m_impl->Reload();
}

void CVisioFrameWnd::Destroy()
{
	GetParent()->SendMessage(WM_CLOSE);
}

/**-----------------------------------------------------------------------------
	Called when window size is changed.
------------------------------------------------------------------------------*/

void CVisioFrameWnd::OnSize(UINT nType, int cx, int cy)
{
	m_impl->m_html.MoveWindow(0, 0, cx, cy);
}

/**-----------------------------------------------------------------------------
	All background is filled with child frame - nothing to erase.
------------------------------------------------------------------------------*/

BOOL CVisioFrameWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

/**-----------------------------------------------------------------------------
	Called when window is about destroying - save window position.
------------------------------------------------------------------------------*/

void CVisioFrameWnd::OnDestroy()
{
	m_impl->evt_sel_changed.Unadvise();
	theApp.RegisterWindow(GetVisioWindowHandle(m_impl->visio_window), NULL);

	CWnd::OnDestroy();
}

CVisioFrameWnd::CVisioFrameWnd()
{
	m_impl = new Impl();
}

CVisioFrameWnd::~CVisioFrameWnd()
{
	delete m_impl;
}

LRESULT CVisioFrameWnd::OnMsgHtmlayoutButton(WPARAM wp, LPARAM lp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LPCWSTR id = reinterpret_cast<LPCWSTR>(wp);

	if (!StrCmp(id, L"run"))
		m_impl->Run();

	return 0;
}

LRESULT CVisioFrameWnd::OnHtmlayoutHyperlink(WPARAM wp, LPARAM lp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// LPCWSTR id = reinterpret_cast<LPCWSTR>(wp);

	return 0;
}
