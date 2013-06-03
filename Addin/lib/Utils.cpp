
#include "stdafx.h"
#include "Utils.h"
#include "TextFile.h"

CString FormatString(LPCWSTR  format, ...)
{
	CString result;

	va_list marker;
	va_start(marker, format);
	result.FormatV(format, marker);
	va_end(marker);

	return result;
}

void ThrowComError(HRESULT hr, LPCWSTR error_msg, LPCWSTR error_source)
{
	ICreateErrorInfoPtr cei;
	CreateErrorInfo(&cei);
	cei->SetGUID(GUID_NULL);

	cei->SetDescription(bstr_t(error_msg));

	cei->SetSource(bstr_t(error_source));

	IErrorInfoPtr ei(cei);
	if (ei == NULL) 
		throw _com_error(hr);

	ei->AddRef();
	throw _com_error(hr, (IErrorInfo*)ei);
}

CString	FormatErrorMessage (LPCWSTR msg, _com_error& e)
{
	CString result = msg;

	if (!result.IsEmpty())
		result += L"\n";

	if (e.Description().length())
		result += static_cast<LPCWSTR >(e.Description());

	result.Trim();

	if (!result.IsEmpty())
		result += L"\n\n";

	CString source = DEFAULT_SOURCE;
	if (e.Source().length())
		source = static_cast<LPCWSTR >(e.Source());

	CString message;
	if (e.ErrorMessage())
		message = e.ErrorMessage();

	message.Trim();

	result += FormatString(L"%s: %s", source, message);

	return result;
}

CString LoadTextFromModule (HMODULE hModule, UINT resource_id)
{
	LPBYTE content = NULL;
	DWORD content_length = 0;

	ASSERT_RETURN_VALUE(LoadResourceFromModule(hModule, MAKEINTRESOURCE(resource_id), L"TEXT", &content, &content_length), CString());

	CMemFile mf(content, content_length);
	CTextFileRead rdr(&mf);

	CString result;
	rdr.Read(result);
	return result;
}

BOOL LoadResourceFromModule(HMODULE hModule, LPCWSTR name, LPCWSTR type, LPBYTE* content, DWORD* content_length)
{
	ASSERT_RETURN_VALUE(content != NULL, FALSE);
	ASSERT_RETURN_VALUE(content_length != NULL, FALSE);

	HRSRC rc = ::FindResource(hModule, name, type);

	ASSERT_RETURN_VALUE(rc != NULL, FALSE);

	*content = static_cast<LPBYTE>(
		::LockResource(::LoadResource(hModule, rc)));

	ASSERT_RETURN_VALUE(*content != NULL, FALSE);

	*content_length = 
		::SizeofResource(hModule, rc);

	ASSERT_RETURN_VALUE(content_length > 0, FALSE);

	return TRUE;
}

/**-----------------------------------------------------------------------------
	Removes quotation from the string. 
	"first" and "last" are quotation marks.
------------------------------------------------------------------------------*/

CString UnquoteString(LPCWSTR src)
{
	CString result = src;

	if (result.GetLength() >= 2 
		&& result.GetAt(0) == '"'
		&& result.GetAt(result.GetLength()-1) == '"') 
	{
		result = result.Mid(1, result.GetLength() - 2);

		// replace double-quotes to single-quotes, see MOD-1945
		result.Replace(L"\"\"", L"\"");
	}

	return result;
}

/**-----------------------------------------------------------------------------
	Adds quotation marks to the string.
------------------------------------------------------------------------------*/

bstr_t QuoteString(LPCWSTR src)
{
	CString result(src);

	// replace quotes to double-quotes, see MOD-1945
	result.Replace(L"\"", L"\"\"");

	return bstr_t('"' + result + '"');
}
