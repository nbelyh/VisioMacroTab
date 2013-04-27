// Connect.cpp : Implementation of CConnect
#include "stdafx.h"
#include "AddIn_i.h"
#include "Connect.h"
#include "ConfigDlg.h"
#include "PictureConvert.h"

namespace {

	CString GetRibbonControlId(IRibbonControlPtr ctrl)
	{
		CComBSTR result;
		ctrl->get_Id(&result);
		return static_cast<LPCWSTR>(result);
	}

	CString GetButtonId(int idx)
	{
		CString result;
		result.Format(L"button%d", idx);
		return result ;
	}

	int GetButtonNo(IRibbonControlPtr ctrl)
	{
		CString button_id = GetRibbonControlId(ctrl);

		for (int i = 0; i < MAX_BUTTON_COUNT; ++i)
		{
			if (button_id == GetButtonId(i))
				return i;
		}
		return -1;
	}

} // 


// CConnect
STDMETHODIMP CConnect::OnConnection(IDispatch *pApplication, ext_ConnectMode, IDispatch *pAddInInst, SAFEARRAY ** custom)
{
	pApplication->QueryInterface(__uuidof(IDispatch), (LPVOID*)&m_pApplication);
	pAddInInst->QueryInterface(__uuidof(IDispatch), (LPVOID*)&m_pAddInInstance);

	return S_OK;
}

STDMETHODIMP CConnect::OnDisconnection(ext_DisconnectMode /*RemoveMode*/, SAFEARRAY ** /*custom*/ )
{
	m_pApplication = NULL;
	m_pAddInInstance = NULL;
	m_pRibbonUI = NULL;
	return S_OK;
}

STDMETHODIMP CConnect::OnAddInsUpdate (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnStartupComplete (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnBeginShutdown (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::GetCustomUI(BSTR RibbonID, BSTR * RibbonXml)
{
	HMODULE hResources = _AtlModule.GetResourceInstance();

	HRSRC rc = ::FindResource(
		hResources, MAKEINTRESOURCE(IDR_RIBBON), L"XML");

	LPSTR content = static_cast<LPSTR>(
		::LockResource(::LoadResource(hResources, rc)));

	DWORD content_length = 
		::SizeofResource(hResources, rc);

	*RibbonXml = CComBSTR(content_length, content).Detach();

	return S_OK;
}

STDMETHODIMP CConnect::OnRibbonButtonClicked(IDispatch * disp)
{ 
	CString bstr_id = GetRibbonControlId(disp);

	if (bstr_id == L"Configure")
	{
		CConfigDlg dlg(m_pApplication, CConfig::Instance());

		if (dlg.DoModal() == IDOK)
		{
			CConfig::Instance() = dlg.GetConfig();
			m_pRibbonUI->Invalidate();
		}
	}
	else
	{
		int idx = GetButtonNo(disp);
		if (idx < 0)
			return E_INVALIDARG;

		const CConfig::ButtonInfo& info = CConfig::Instance().GetButtonInfo(idx);

		RunScript(info.macro, m_pApplication, this);
	}

	return S_OK; 
}

STDMETHODIMP CConnect::OnRibbonLoad(IDispatch* disp)
{
	disp->QueryInterface(__uuidof(IRibbonUI), (LPVOID*)&m_pRibbonUI);
	return S_OK;
}

STDMETHODIMP CConnect::OnRibbonLoadImage(BSTR bstrID, IPictureDisp ** ppdispImage)
{
	return CustomUiGetPng(bstrID, ppdispImage, NULL);
}

STDMETHODIMP CConnect::IsRibbonButtonEnabled(IDispatch * RibbonControl, VARIANT_BOOL* pResult)
{
	return IsRibbonButtonVisible(RibbonControl, pResult);
}


STDMETHODIMP CConnect::GetRibbonLabel(IDispatch *pControl, BSTR *pbstrLabel)
{
	int idx = GetButtonNo(pControl);
	if (idx < 0)
		return E_INVALIDARG;

	const CConfig::ButtonInfo& info = CConfig::Instance().GetButtonInfo(idx);
	*pbstrLabel = info.label.AllocSysString();
	return S_OK;
}

STDMETHODIMP CConnect::GetRibbonImage(IDispatch *pControl, IPictureDisp ** ppdispImage)
{
	return S_OK;
}

STDMETHODIMP CConnect::IsRibbonButtonVisible(IDispatch * RibbonControl, VARIANT_BOOL* pResult)
{
	int idx = GetButtonNo(RibbonControl);
	if (idx < 0)
		return E_INVALIDARG;

	const CConfig::ButtonInfo& info = CConfig::Instance().GetButtonInfo(idx);
	*pResult = info.enabled ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CConnect::GetItemCount(IDispatch *pControl, long *count)
{
	*count = 4;
	return S_OK;
}

void CConnect::ReportScriptError (LPCWSTR msg)
{
	MessageBox(NULL, msg, L"Unable to run script", MB_ICONEXCLAMATION);
}