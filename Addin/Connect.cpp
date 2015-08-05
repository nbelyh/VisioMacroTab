// Connect.cpp : Implementation of CConnect

#include "stdafx.h"

#include "Addin.h"
#include "AddIn_i.h"

#include "lib/PictureConvert.h"
#include "lib/Visio.h"
#include "lib/Utils.h"
#include "lib/Language.h"
#include "lib/UI.h"
#include "Connect.h"

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

UINT GetControlCommand(IDispatch* pControl)
{
	IRibbonControlPtr control;
	pControl->QueryInterface(__uuidof(IRibbonControl), (void**)&control);

	CComBSTR tag;
	if (FAILED(control->get_Tag(&tag)))
		return S_OK;

	return StrToInt(tag);
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

struct CConnect::Impl 
	: public VEventHandler
{
	AddinUi m_ui;

	HRESULT HandleVisioEvent(
		IN	IUnknown*	ipSink,			//	ipSink [assert]
		IN	short		nEventCode,		//	code of event that's firing.
		IN	IDispatch*	pSourceObj,		//	object that is firing event.
		IN	long		lEventID,		//	id of event that is firing.
		IN	long		lEventSeqNum,	//	sequence number of event.
		IN	IDispatch*	pSubjectObj,	//	subject of this event.
		IN	VARIANT		vMoreInfo,		//	other info.
		OUT VARIANT*	pvResult)		//	return a value to Visio for query events.
	{
		ENTER_METHOD();

		switch(nEventCode) 
		{
		case (short)(Visio::visEvtCodeWinOnAddonKeyMSG):
			return OnKeystroke(pSubjectObj, pvResult);
			break;

		case (short)(Visio::visEvtApp|Visio::visEvtWinActivate):
			theApp.SetNeedUpdate(true);
			break;

		case (short)(Visio::visEvtWindow|Visio::visEvtDel):
			theApp.SetNeedUpdate(true);
			break;

		case (short)(Visio::visEvtApp|Visio::visEvtIdle):
			OnIdle();
			break;

		case (short)(Visio::visEvtCodeWinSelChange):
			theApp.SetNeedUpdate(true);
			break;
			break;

		}

		return S_OK;

		LEAVE_METHOD();
	}

	void OnIdle()
	{
		if (theApp.NeedUpdate())
		{
			theApp.UpdateButtons();
			theApp.SetNeedUpdate(false);
		}
	}

	/**------------------------------------------------------------------------
		
	-------------------------------------------------------------------------*/

	void Create(IDispatch * pApplication, IDispatch * pAddInInst) 
	{
		Visio::IVApplicationPtr app;
		pApplication->QueryInterface(__uuidof(IDispatch), (LPVOID*)&app);

		pAddInInst->QueryInterface(__uuidof(IDispatch), (LPVOID*)&m_addin);

		Visio::IVEventListPtr evt_list = 
			app->EventList;

		evt_keystroke.Advise(evt_list, Visio::visEvtCodeWinOnAddonKeyMSG, this);

		evt_win_activated.Advise(evt_list, Visio::visEvtApp|Visio::visEvtWinActivate, this);
		evt_win_closed.Advise(evt_list, Visio::visEvtWindow|Visio::visEvtDel, this);

		evt_idle.Advise(evt_list, Visio::visEvtApp|Visio::visEvtIdle, this);

		theApp.SetVisioApp(app);
	}

	/**------------------------------------------------------------------------
		
	-------------------------------------------------------------------------*/

	void Destroy() 
	{
		evt_idle.Unadvise();

		evt_win_activated.Unadvise();
		evt_win_closed.Unadvise();

		theApp.SetVisioApp(NULL);

		m_addin = NULL;
	}

	/**------------------------------------------------------------------------
		
	-------------------------------------------------------------------------*/

	CString GetRibbonLabel(IDispatch* pControl) 
	{
		UINT cmd_id = GetControlCommand(pControl);

		LanguageLock lock(GetAppLanguage(theApp.GetVisioApp()));

		CString result;
		result.LoadString(cmd_id);

		return result;
	}

	IDispatchPtr m_addin;

	Visio::IVApplicationPtr application;
	IDispatchPtr addin;

	CVisioEvent	 evt_keystroke;
	CVisioEvent	 evt_win_activated;
	CVisioEvent	 evt_win_closed;
	CVisioEvent	 evt_idle;

	void OnRibbonCheckboxClicked(IDispatch * pControl, VARIANT_BOOL * pvarfPressed)
	{
		UINT cmd_id = GetControlCommand(pControl);

		if (cmd_id > 0)
			theApp.OnCommand(cmd_id);
	}

	HRESULT OnKeystroke(Visio::IVMSGWrapPtr key_msg, VARIANT* pvResult)
	{
		ASSERT_RETURN_VALUE(key_msg != NULL, E_INVALIDARG);
		ASSERT_RETURN_VALUE(pvResult != NULL, E_INVALIDARG);

		MSG msg;

		msg.hwnd    = reinterpret_cast<HWND>(key_msg->Gethwnd());
		msg.message = key_msg->Getmessage();
		msg.wParam  = key_msg->GetwParam();
		msg.lParam  = key_msg->GetlParam();
		msg.pt.x    = key_msg->Getptx();
		msg.pt.y    = key_msg->Getpty();
		msg.time    = key_msg->Getposttime();

		bool result = false;

		if (CWnd::FromHandlePermanent(msg.hwnd))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			result = true;
		}
		else
		{
			result = CWnd::WalkPreTranslateTree(NULL, &msg) != FALSE;
		}

		*pvResult = variant_t(result);
		return S_OK;
	}

};

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::OnConnection(IDispatch *pApplication, ext_ConnectMode, IDispatch *pAddInInst, SAFEARRAY ** custom)
{
	ENTER_METHOD()

	m_impl->Create(pApplication, pAddInInst);

	return S_OK;

	LEAVE_METHOD()
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::OnDisconnection(ext_DisconnectMode /*RemoveMode*/, SAFEARRAY ** /*custom*/ )
{
	ENTER_METHOD()

	m_impl->Destroy();
	return S_OK;

	LEAVE_METHOD()
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::OnAddInsUpdate (SAFEARRAY ** /*custom*/ )
{
	ENTER_METHOD();

	return S_OK;

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::OnStartupComplete (SAFEARRAY ** /*custom*/ )
{
	ENTER_METHOD();

	return S_OK;

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::OnBeginShutdown (SAFEARRAY ** /*custom*/ )
{
	ENTER_METHOD();

	return S_OK;

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::raw_GetCustomUI(BSTR RibbonID, BSTR * RibbonXml)
{
	ENTER_METHOD();

	return GetRibbonText(RibbonXml);

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::OnRibbonCheckboxClicked(IDispatch *pControl, VARIANT_BOOL *pvarfPressed)
{
	ENTER_METHOD()

	m_impl->OnRibbonCheckboxClicked(pControl, pvarfPressed);
	return S_OK;

	LEAVE_METHOD()
}

STDMETHODIMP CConnect::OnRibbonButtonClicked(IDispatch * disp)
{ 
	ENTER_METHOD();

	UINT cmd_id = GetControlCommand(disp);

	LanguageLock lock(GetAppLanguage(theApp.GetVisioApp()));

	theApp.OnCommand(cmd_id);

	return S_OK; 

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::OnRibbonLoad(IDispatch* disp)
{
	ENTER_METHOD();

	theApp.SetRibbon(disp);
	return S_OK;

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::OnRibbonLoadImage(BSTR bstrID, IPictureDisp ** ppdispImage)
{
	ENTER_METHOD();

	return CustomUiGetPng(MAKEINTRESOURCE(StrToInt(bstrID)), ppdispImage, NULL);

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::IsRibbonButtonPressed(IDispatch * RibbonControl, VARIANT_BOOL* pResult)
{
	ENTER_METHOD();

	UINT cmd_id = GetControlCommand(RibbonControl);

	*pResult = theApp.IsButtonPressed(cmd_id);

	return S_OK;

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::IsRibbonButtonEnabled(IDispatch * RibbonControl, VARIANT_BOOL* pResult)
{
	ENTER_METHOD();

	UINT cmd_id = GetControlCommand(RibbonControl);

	*pResult = theApp.IsButtonEnabled(cmd_id);

	return S_OK;

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::GetRibbonLabel(IDispatch *pControl, BSTR *pbstrLabel)
{
	ENTER_METHOD();

	*pbstrLabel = m_impl->GetRibbonLabel(pControl).AllocSysString();
	return S_OK;

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::GetRibbonImage(IDispatch *pControl, IPictureDisp ** ppdispImage)
{
	return S_OK;
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

STDMETHODIMP CConnect::IsRibbonButtonVisible(IDispatch * RibbonControl, VARIANT_BOOL* pResult)
{
	ENTER_METHOD();

	*pResult = VARIANT_TRUE;

	return S_OK;

	LEAVE_METHOD();
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

HRESULT CConnect::FinalConstruct ()
{
	return S_OK;
}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

void CConnect::FinalRelease ()
{

}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

CConnect::CConnect ()
	: m_impl(new Impl())
{

}

/**------------------------------------------------------------------------
	
-------------------------------------------------------------------------*/

CConnect::~CConnect ()
{
	delete m_impl;
}
