
#pragma once

struct IReportScriptError
{
	virtual void ReportScriptError(LPCWSTR msg) = 0;
};

HRESULT RunScript(LPCWSTR script_text, 
				  IDispatch* app,
				  IReportScriptError* callback);
