// MyScriptSite.h

#include "StdAfx.h"

#include "import/activdbg.h"

#include "Scripts.h"
#include "AddIn_i.h"

_COM_SMARTPTR_TYPEDEF(IActiveScript, __uuidof(IActiveScript));
_COM_SMARTPTR_TYPEDEF(IActiveScriptParse, __uuidof(IActiveScriptParse));

#define Object_Name	L"_Globals"

class CScriptContext :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfoImpl<&__uuidof(_IScriptSiteContext)>,
	public IDispatchImpl<_IScriptSiteContext, &__uuidof(_IScriptSiteContext), &LIBID_VisioMacroTabAddin>
{
public:
	BEGIN_COM_MAP(CScriptContext)
		COM_INTERFACE_ENTRY(_IScriptSiteContext)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	IDispatchPtr m_application;
	void SetApplication(IDispatchPtr pVal)
	{
		m_application = pVal;
	}

	STDMETHOD(get_Application)(IDispatch **pVal)
	{
		if (m_application == NULL)
		{
			*pVal = NULL;
			return S_FALSE;
		}

		return m_application->QueryInterface(IID_IDispatch, (void**)pVal);
	}

	IDispatchPtr m_active_page;
	void SetActivePage(IDispatchPtr pVal)
	{
		m_active_page = pVal;
	}

	STDMETHOD(get_ActivePage)(IDispatch* *pVal)
	{
		if (m_active_page == NULL)
		{
			*pVal = NULL;
			return S_FALSE;
		}

		return m_active_page->QueryInterface(IID_IDispatch, (void**)pVal);
	}

	IDispatchPtr m_active_document;
	void SetActiveDocument(IDispatchPtr pVal)
	{
		m_active_document = pVal;
	}

	STDMETHOD(get_ActiveDocument)(IDispatch* *pVal)
	{
		if (m_active_document == NULL)
		{
			*pVal = NULL;
			return S_FALSE;
		}

		return m_active_document->QueryInterface(IID_IDispatch, (void**)pVal);
	}

	IDispatchPtr m_active_shape;
	void SetActiveShape(IDispatchPtr pVal)
	{
		m_active_shape = pVal;

	}
	STDMETHOD(get_ActiveShape)(IDispatch* *pVal)
	{
		if (m_active_shape == NULL)
		{
			*pVal = NULL;
			return S_FALSE;
		}

		return m_active_shape->QueryInterface(IID_IDispatch, (void**)pVal);
	}
};

#include <InitGuid.h>
DEFINE_GUID(CLSID_VBScript, 0xb54f3741, 0x5b07, 0x11cf, 0xa4, 0xb0, 0x0,
			0xaa, 0x0, 0x4a, 0x55, 0xe8); 

class CP4BScriptSite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IActiveScriptSite,
	public IActiveScriptSiteWindow,
	public IActiveScriptSiteDebug
{
public:

	CP4BScriptSite()
		: m_globals(NULL), m_callback(NULL)
	{
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CP4BScriptSite)
		COM_INTERFACE_ENTRY(IActiveScriptSite)
		COM_INTERFACE_ENTRY(IActiveScriptSiteWindow)
		COM_INTERFACE_ENTRY(IActiveScriptSiteDebug)
	END_COM_MAP()

	STDMETHOD(GetLCID)(LCID *plcid)
	{
		return S_OK;
	}

	STDMETHOD(GetItemInfo)(LPCOLESTR pstrName, DWORD dwReturnMask, 
		IUnknown **ppunkItem, ITypeInfo **ppti)
	{
		if (ppti) 
		{
			*ppti = NULL;

			// if we are asked for ITypeInfo...
			if(dwReturnMask & SCRIPTINFO_ITYPEINFO) 
			{
				if (!lstrcmp(pstrName, Object_Name))
					return SUCCEEDED(m_globals->GetTypeInfo(0, 0, ppti));
				else
					return TYPE_E_ELEMENTNOTFOUND;
			}
		}

		// If windows scripting created ppunkItem...
		if (ppunkItem)
		{
			*ppunkItem = NULL;

			// If windows scripting asks for IUnknown of our object...
			if (dwReturnMask & SCRIPTINFO_IUNKNOWN) 
			{
				if (!lstrcmp(pstrName, Object_Name))
					return SUCCEEDED(m_globals->QueryInterface(IID_IUnknown, (void**) ppunkItem));
				else
					return TYPE_E_ELEMENTNOTFOUND;
			}
		}
		return S_OK;
	}

	STDMETHOD(GetDocVersionString)(BSTR *pbstrVersion)
	{
		return S_OK;
	}

	STDMETHOD(OnScriptTerminate)(const VARIANT *pvarResult, const EXCEPINFO *pexcepInfo)
	{
		return S_OK;
	}

	STDMETHOD(OnStateChange)(SCRIPTSTATE ssScriptState)
	{
		return S_OK;
	}

	void LogScriptError(IActiveScriptError *pscriptError)
	{
		if (m_callback)
		{
			EXCEPINFO ei;
			pscriptError->GetExceptionInfo(&ei);

			DWORD context = 0;
			ULONG line = 0;
			LONG pos = 0;
			pscriptError->GetSourcePosition(&context, &line, &pos);

			CString msg;
			msg.Format(L"Unable to execute the script (error at line %d)\n%s"
				, 1 + line
				, ei.bstrDescription);

			m_callback->ReportScriptError(msg);
		}
	}

	STDMETHOD(OnScriptError)(IActiveScriptError *pscriptError)
	{
		LogScriptError(pscriptError);
		return DISP_E_EXCEPTION;
	}

	STDMETHOD(OnEnterScript)(void)
	{
		return S_OK;
	}

	STDMETHOD(OnLeaveScript)(void)
	{
		return S_OK;
	}

	STDMETHOD(GetDocumentContextFromPosition)(DWORD, ULONG, ULONG, IDebugDocumentContext**)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetApplication)(IDebugApplication**)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetRootApplicationNode)(IDebugApplicationNode**)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnScriptErrorDebug)(IActiveScriptErrorDebug* pscriptErrorDebug, BOOL*,BOOL*)
	{
		LogScriptError(pscriptErrorDebug);
		return DISP_E_EXCEPTION;
	}

	STDMETHOD(GetWindow)(HWND *phwnd)
	{
		*phwnd = NULL;
		return S_OK;
	}

	STDMETHOD(EnableModeless)(BOOL fEnable)
	{
		return E_NOTIMPL;
	}

	void Init(CScriptContext* globals, IReportScriptError* callback)
	{
		m_globals = globals;
		m_callback = callback;
	}

	CScriptContext* m_globals;
	IReportScriptError* m_callback;
}; 

/**-----------------------------------------------------------------------------
	Executes given script
------------------------------------------------------------------------------*/

HRESULT RunScript(LPCWSTR script_text, 
				  IDispatch* app,
				  IReportScriptError* callback)
{
	struct Holder
	{
		IActiveScriptPtr active_script;
		CComObject<CP4BScriptSite> * pSite;
		CComObject<CScriptContext> *pGlobals;

		Holder()
		{
			CComObject<CP4BScriptSite>::CreateInstance(&pSite);
			pSite->AddRef();

			CComObject<CScriptContext>::CreateInstance(&pGlobals);
			pGlobals->AddRef();
		}

		~Holder()
		{
			if (active_script)
				active_script->Close();
			pSite->Release();
			pGlobals->Release();
		}

	} holder;

	holder.pGlobals->SetApplication(app);

	CComDispatchDriver app_disp(app);

	CComVariant v_active_page;
	if (SUCCEEDED(app_disp.GetPropertyByName(L"ActivePage", &v_active_page)))
		holder.pGlobals->SetActivePage(V_DISPATCH(&v_active_page));

	CComVariant v_active_document;
	if (SUCCEEDED(app_disp.GetPropertyByName(L"ActiveDocument", &v_active_document)))
		holder.pGlobals->SetActiveDocument(V_DISPATCH(&v_active_document));

	holder.pSite->Init(holder.pGlobals, callback);

	HRESULT hr;

	hr = holder.active_script.CreateInstance(CLSID_VBScript);
	if (FAILED(hr))
		return hr;

	hr = holder.active_script->SetScriptSite(holder.pSite);
	if (FAILED(hr))
		return hr;

	IActiveScriptParsePtr spASP = holder.active_script;
	hr = spASP->InitNew();
	if (FAILED(hr))
		return hr;

	holder.active_script->AddNamedItem(Object_Name, SCRIPTITEM_ISVISIBLE | SCRIPTITEM_GLOBALMEMBERS);

	// parse script text
	EXCEPINFO ei;
	hr = spASP->ParseScriptText(script_text, NULL, NULL, NULL, 0, 0, 0L, NULL, &ei);

	if (FAILED(hr))
		return hr;

	hr = holder.active_script->SetScriptState(SCRIPTSTATE_CONNECTED);

	if (FAILED(hr))
		return hr;

	return S_OK;
}
