// Connect.h : Declaration of the CConnect

#pragma once
#include "resource.h"       // main symbols
#include "Scripts.h"

using namespace Office;
using namespace AddInDesignerObjects;

// CConnect
class ATL_NO_VTABLE CConnect : 
	public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CConnect, &__uuidof(Connect)>
	, public IDispatchImpl<IRibbonCallbackInterface, &__uuidof(IRibbonCallbackInterface), &__uuidof(MyAddin1Lib)>
	, public IDispatchImpl<_IDTExtensibility2, &__uuidof(_IDTExtensibility2), &__uuidof(__AddInDesignerObjects)>
	, public IDispatchImpl<IRibbonExtensibility, &__uuidof(IRibbonExtensibility), &__uuidof(__Office)>
	, public IReportScriptError
{
public:
	CConnect()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ADDIN)
DECLARE_NOT_AGGREGATABLE(CConnect)

BEGIN_COM_MAP(CConnect)
	COM_INTERFACE_ENTRY2(IDispatch, IRibbonCallbackInterface)
	COM_INTERFACE_ENTRY(IDTExtensibility2)
	COM_INTERFACE_ENTRY(IRibbonExtensibility)
	COM_INTERFACE_ENTRY(IRibbonCallbackInterface)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

	virtual void ReportScriptError(LPCWSTR msg);

public:
	//IDTExtensibility2 implementation:
	STDMETHOD(OnConnection)(IDispatch * Application, ext_ConnectMode ConnectMode, IDispatch *AddInInst, SAFEARRAY **custom);
	STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY **custom );
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY **custom );
	STDMETHOD(OnStartupComplete)(SAFEARRAY **custom );
	STDMETHOD(OnBeginShutdown)(SAFEARRAY **custom );

	//IRibbonExtensibility implementation:
	STDMETHOD(GetCustomUI)(BSTR RibbonID, BSTR * RibbonXml);

	STDMETHOD(OnRibbonButtonClicked)(IDispatch * RibbonControl);
	
	STDMETHOD(OnRibbonLoad)(IDispatch* disp);
	STDMETHOD(OnRibbonLoadImage)(BSTR pbstrImageId, IPictureDisp ** ppdispImage);

	STDMETHOD(IsRibbonButtonEnabled)(IDispatch * RibbonControl, VARIANT_BOOL* pResult);
	STDMETHOD(IsRibbonButtonVisible)(IDispatch * RibbonControl, VARIANT_BOOL* pResult);
	STDMETHOD(GetRibbonLabel)(IDispatch *pControl, BSTR *pbstrLabel);
	STDMETHOD(GetItemCount)(IDispatch *pControl, long *count);
	STDMETHOD(GetRibbonImage)(IDispatch *pControl, IPictureDisp ** ppdispImage);

	CComPtr<IDispatch> m_pApplication;
	CComPtr<IDispatch> m_pAddInInstance;
	CComPtr<IRibbonUI>	m_pRibbonUI;
};

OBJECT_ENTRY_AUTO(__uuidof(Connect), CConnect)
